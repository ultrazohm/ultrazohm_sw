//! Independent recording lifetimes. Disk finalization never blocks device control.
use crate::{
    data::{History, Stream},
    live::{DataOptions, selected_columns},
    profile::Profile,
    protocol::Frame,
    storage::{Format, LogWriter},
};
use anyhow::{Context, Result, ensure};
use serde::Serialize;
use serde_json::{Value, json};
use std::{
    fs,
    path::PathBuf,
    sync::{
        Arc, Mutex,
        mpsc::{self, SyncSender},
    },
    thread,
    time::{Duration, Instant},
};

type Batch = (u64, u64, Arc<Frame>);
pub struct Route {
    paused: bool,
    tx: SyncSender<Batch>,
    history: Arc<Mutex<History>>,
}
impl Route {
    pub fn send(&self, index: u64, frame: Arc<Frame>) -> Result<()> {
        if self.paused {
            return Ok(());
        }
        let mut history = self.history.lock().unwrap();
        // Positions remain contiguous for paging; timestamps retain acquisition time.
        let position = history.stop.unwrap_or(index);
        ensure!(
            history.pending_samples + frame.slow_raw.len() <= history.max_pending_samples,
            "pending recording memory limit exceeded"
        );
        self.tx.try_send((position, index, frame.clone())).context(
            "logger queue full or failed; acquisition stopped, samples not silently discarded",
        )?;
        history.accepted(position, index, frame)
    }
}
pub type Routes = Arc<Mutex<[Option<Route>; 2]>>;

// Leave headroom while a large segment is encoded and synced. With 15 samples
// per frame at 10 kHz this holds 3.072 seconds, independently of live history.
const LOGGER_QUEUE_FRAMES: usize = 2048;

#[derive(Clone, Serialize)]
pub struct RecordingState {
    pub phase: &'static str,
    pub parquet: Option<PathBuf>,
    pub error: Option<String>,
    pub handle: Option<PathBuf>,
    pub backend: &'static str,
}
impl Default for RecordingState {
    fn default() -> Self {
        Self {
            phase: "idle",
            parquet: None,
            error: None,
            handle: None,
            backend: "parquet",
        }
    }
}

pub struct Recordings {
    options: DataOptions,
    histories: std::collections::BTreeMap<(bool, u64), Arc<Mutex<History>>>,
    pub routes: Routes,
    states: Arc<Mutex<[RecordingState; 2]>>,
    workers: [Option<thread::JoinHandle<()>>; 2],
    counts: [u64; 2],
    dir: Option<PathBuf>,
    profile: Profile,
    format: Format,
}
impl Recordings {
    pub fn new(
        dir: Option<PathBuf>,
        profile: Profile,
        format: Format,
        options: DataOptions,
    ) -> Self {
        Self {
            options,
            histories: Default::default(),
            routes: Arc::new(Mutex::new([None, None])),
            states: Arc::new(Mutex::new(Default::default())),
            workers: [None, None],
            counts: [0, 0],
            dir,
            profile,
            format,
        }
    }
    pub fn status(&self) -> Value {
        let s = self.states.lock().unwrap();
        json!({"fast":s[0], "slow":s[1]})
    }
    pub fn history(&self, stream: &Stream, recording: u64) -> Result<Arc<Mutex<History>>> {
        self.histories
            .get(&(*stream == Stream::Slow, recording))
            .cloned()
            .context("recording does not exist")
    }
    pub fn sources(&self) -> Vec<crate::data::Source> {
        self.histories
            .keys()
            .map(|(slow, n)| crate::data::Source {
                stream: if *slow { Stream::Slow } else { Stream::Fast },
                recording: Some(*n),
            })
            .collect()
    }
    pub fn active(&self) -> bool {
        self.routes.lock().unwrap().iter().any(Option::is_some)
    }
    pub fn error(&self) -> Option<String> {
        self.states
            .lock()
            .unwrap()
            .iter()
            .find_map(|s| s.error.clone())
    }
    pub fn start(&mut self, slow: bool, selections: &Value) -> Result<()> {
        let slot = usize::from(slow);
        ensure!(
            !matches!(
                self.states.lock().unwrap()[slot].phase,
                "recording" | "paused" | "finalizing"
            ),
            "this recording is already active or still finalizing; check status"
        );
        if let Some(worker) = self.workers[slot].take() {
            worker
                .join()
                .map_err(|_| anyhow::anyhow!("recording worker panicked"))?;
        }
        let dir = self
            .dir
            .as_ref()
            .context("logging needs an output directory; start serve with --output DIRECTORY")?;
        let n = self.counts[slot] + 1;
        let base = if n == 1 {
            "data".to_string()
        } else {
            format!("data_{n:04}")
        };
        let stem = if slow {
            format!("{base}_slow_data")
        } else {
            base
        };
        let dir = dir.clone();
        let profile = self.profile.clone();
        let format = self.format;
        let options = self.options.clone();
        let selections = selections.clone();
        let metadata_path = dir.join(format!("{stem}.json"));
        let metadata = json!({"schema_version":5, "stream":if slow {"slow"} else {"fast"},
            "requested_observables":selections, "mapping_confirmed":false,
            "position_basis":"contiguous recorded samples; time retains acquisition gaps",
            "slow_layout": if slow {Some("wide_forward_filled")} else {None},
            "slow_initial_values": if slow {Some("rows_omitted_until_all_observables_received")} else {None},
            "time_basis":"seconds from acquisition start, configured sample period; gaps unknown",
            "parquet":format!("{stem}.parquet"), "csv":!matches!(self.format, Format::Parquet)});
        let (tx, rx) = mpsc::sync_channel::<Batch>(LOGGER_QUEUE_FRAMES);
        let history = Arc::new(Mutex::new(History {
            reader: None,
            start: None,
            stop: None,
            persisted_stop: None,
            pending: Default::default(),
            pending_samples: 0,
            max_pending_samples: self
                .options
                .segment_rows
                .saturating_add((LOGGER_QUEUE_FRAMES + 2) * self.profile.samples_per_packet),
            columns: if slow {
                Vec::new()
            } else {
                selected_columns(&self.profile, &selections)?
            },
            slow,
        }));
        self.histories.insert((slow, n), history.clone());
        self.states.lock().unwrap()[slot] = RecordingState {
            phase: "recording",
            parquet: Some(dir.join(format!("{stem}.parquet"))),
            error: None,
            handle: Some(crate::backend::index_path(&dir, &stem)),
            backend: "parquet",
        };
        let writer_history = history.clone();
        let states = self.states.clone();
        let flush_interval = Duration::from_millis(self.options.flush_interval_ms);
        self.workers[slot] = Some(thread::spawn(move || {
            let mut rows = 0u64;
            let result: Result<()> = (|| {
                // Disk initialization runs on the writer, never the control loop.
                // Frames accepted meanwhile remain in the bounded recording queue.
                let mut log = LogWriter::new_for_backend(
                    dir,
                    profile,
                    format,
                    stem,
                    slow,
                    &selections,
                    options.recording_backend,
                )?;
                log.segment_rows = options.segment_rows;
                writer_history.lock().unwrap().reader = Some(log.reader());
                let file = fs::File::create_new(&metadata_path)?;
                serde_json::to_writer_pretty(file, &metadata)?;
                let mut last_flush = Instant::now();
                loop {
                    match rx.recv_timeout(flush_interval.saturating_sub(last_flush.elapsed())) {
                        Ok((position, index, frame)) => {
                            rows += frame.slow_raw.len() as u64;
                            if log.push_recorded(position, index, frame)? {
                                writer_history.lock().unwrap().committed()?;
                                last_flush = Instant::now();
                            } else if last_flush.elapsed() >= flush_interval {
                                log.flush()?;
                                writer_history.lock().unwrap().committed()?;
                                last_flush = Instant::now();
                            }
                        }
                        Err(mpsc::RecvTimeoutError::Timeout) => {
                            log.flush()?;
                            writer_history.lock().unwrap().committed()?;
                            last_flush = Instant::now();
                        }
                        Err(mpsc::RecvTimeoutError::Disconnected) => break,
                    }
                }
                log.flush()?;
                writer_history.lock().unwrap().committed()?;
                log.finish()
            })();
            let mut error = result.err().map(|e| format!("logging: {e:#}"));
            let summary =
                json!({"recording":metadata,"rows":rows,"complete":error.is_none(),"error":error});
            if let Err(e) = fs::write(metadata_path, serde_json::to_vec_pretty(&summary).unwrap()) {
                error.get_or_insert_with(|| format!("recording metadata: {e}"));
            }
            let mut s = states.lock().unwrap();
            s[slot].phase = if error.is_some() {
                "failed"
            } else {
                "complete"
            };
            s[slot].error = error;
        }));
        // Receiver uses the same lock: the recording starts at a complete frame boundary.
        self.routes.lock().unwrap()[slot] = Some(Route {
            tx,
            history,
            paused: false,
        });
        self.counts[slot] = n;
        Ok(())
    }
    pub fn pause(&mut self, slow: bool, paused: bool) -> Result<()> {
        let slot = usize::from(slow);
        let mut routes = self.routes.lock().unwrap();
        let route = routes[slot]
            .as_mut()
            .context("this recording is not active")?;
        let mut states = self.states.lock().unwrap();
        let expected = if paused { "recording" } else { "paused" };
        ensure!(
            states[slot].phase == expected,
            "recording must be {expected} before this operation"
        );
        route.paused = paused;
        states[slot].phase = if paused { "paused" } else { "recording" };
        Ok(())
    }
    pub fn stop(&mut self, slow: bool) -> Result<()> {
        let slot = usize::from(slow);
        let mut routes = self.routes.lock().unwrap();
        ensure!(routes[slot].is_some(), "this recording is not active");
        {
            let mut states = self.states.lock().unwrap();
            if matches!(states[slot].phase, "recording" | "paused") {
                states[slot].phase = "finalizing";
            }
        }
        routes[slot] = None; // Worker drains already accepted frames, then finalizes.
        Ok(())
    }
    pub fn finish(&mut self) -> Result<()> {
        for slow in [false, true] {
            if self.routes.lock().unwrap()[usize::from(slow)].is_some() {
                self.stop(slow)?;
            }
        }
        let mut panic = false;
        for worker in &mut self.workers {
            if let Some(w) = worker.take() {
                panic |= w.join().is_err();
            }
        }
        ensure!(!panic, "recording worker panicked");
        if let Some(e) = self.error() {
            anyhow::bail!("{e}");
        }
        Ok(())
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn pause_before_first_frame_and_finalize_without_resume() -> Result<()> {
        let dir = std::env::temp_dir().join(format!(
            "uz-empty-pause-{}-{}",
            std::process::id(),
            std::time::SystemTime::now()
                .duration_since(std::time::UNIX_EPOCH)?
                .as_nanos()
        ));
        fs::create_dir(&dir)?;
        let result = (|| -> Result<()> {
            let profile = Profile::load(None)?;
            let selections = serde_json::to_value(&profile.initial_channels)?;
            let mut recordings = Recordings::new(
                Some(dir.clone()),
                profile,
                Format::Parquet,
                DataOptions::default(),
            );
            assert!(recordings.pause(false, true).is_err());
            recordings.start(false, &selections)?;
            assert!(recordings.pause(false, false).is_err());
            recordings.pause(false, true)?;
            assert!(recordings.active());
            assert!(recordings.start(false, &selections).is_err());
            assert!(recordings.pause(false, true).is_err());
            recordings.pause(false, false)?;
            recordings.pause(false, true)?;
            recordings.finish()?;
            assert_eq!(recordings.status()["fast"]["phase"], "complete");
            assert!(dir.join("data.parquet").is_file());
            let info = crate::backend::open(&crate::backend::index_path(&dir, "data"))?.info()?;
            assert!(info.complete && info.start.is_none() && info.stop.is_none());
            Ok(())
        })();
        let _ = fs::remove_dir_all(dir);
        result
    }
}
