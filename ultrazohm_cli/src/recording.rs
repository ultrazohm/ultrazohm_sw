//! Independent recording lifetimes. Disk finalization never blocks device control.
use crate::service::Selections;
use crate::{
    data::{History, Stream},
    live::{DataOptions, selected_columns},
    profile::Profile,
    protocol::Frame,
    storage::{Format, LogWriter},
};
use anyhow::{Context, Result, ensure};
use serde::Serialize;
use serde_json::json;
use std::{
    path::PathBuf,
    sync::{
        Arc, Mutex,
        mpsc::{self, SyncSender, TrySendError},
    },
    thread,
    time::{Duration, Instant},
};

type Batch = (u64, u64, Arc<Frame>);
pub struct Route {
    paused: bool,
    tx: SyncSender<Batch>,
    history: Arc<Mutex<History>>,
    states: Arc<Mutex<[RecordingState; 2]>>,
    slot: usize,
}
impl Route {
    /// Queue a frame. `Ok(false)` means this recording ended (its writer failed or
    /// its queue overflowed) and the route must be removed. Overflow ends only this
    /// recording at a frame boundary: acquisition, device control and the other
    /// stream continue, and samples are never silently skipped inside a recording.
    pub fn send(&self, index: u64, frame: Arc<Frame>) -> Result<bool> {
        let mut history = self.history.lock().unwrap();
        // Pending samples can fail to flush while paused. Retire that route
        // before the pause shortcut so it no longer locks channel assignments.
        if history.error.is_some() || history.overflow.is_some() {
            return Ok(false);
        }
        if self.paused {
            return Ok(true);
        }
        // Positions remain contiguous for paging; timestamps retain acquisition time.
        let position = history.stop.unwrap_or(index);
        let overflow =
            if history.pending_samples + frame.slow_raw.len() > history.max_pending_samples {
                "pending recording memory limit exceeded"
            } else {
                match self.tx.try_send((position, index, frame.clone())) {
                    Ok(()) => {
                        history.accepted(position, index, frame)?;
                        return Ok(true);
                    }
                    Err(TrySendError::Disconnected(_)) => return Ok(false),
                    Err(TrySendError::Full(_)) => "logger queue full",
                }
            };
        history.overflow = Some(format!(
            "{overflow} at acquisition sample {index} (disk too slow); recording ended \
             there, accepted samples are kept, acquisition continues"
        ));
        drop(history);
        // The writer drains accepted frames and finalizes as after a stop.
        self.states.lock().unwrap()[self.slot].begin_finalizing();
        Ok(false)
    }
}
pub type Routes = Arc<Mutex<[Option<Route>; 2]>>;

#[derive(Clone, Copy, Debug, Default, PartialEq, Eq, Serialize)]
#[serde(rename_all = "snake_case")]
pub enum RecordingPhase {
    #[default]
    Idle,
    Recording,
    Paused,
    /// Stopped or overflowed; accepted frames drain and finalize.
    Finalizing,
    Complete,
    Failed,
}
impl RecordingPhase {
    fn active(self) -> bool {
        matches!(self, Self::Recording | Self::Paused)
    }
}

#[derive(Clone, Serialize)]
pub struct RecordingState {
    pub phase: RecordingPhase,
    pub parquet: Option<PathBuf>,
    pub error: Option<String>,
    pub handle: Option<PathBuf>,
    pub backend: &'static str,
}
impl Default for RecordingState {
    fn default() -> Self {
        Self {
            phase: RecordingPhase::Idle,
            parquet: None,
            error: None,
            handle: None,
            backend: "parquet",
        }
    }
}
impl RecordingState {
    fn begin_finalizing(&mut self) {
        if self.phase.active() {
            self.phase = RecordingPhase::Finalizing;
        }
    }
}

/// Fast and slow recording state, as reported by `status`.
#[derive(Clone, Serialize)]
pub struct RecordingsStatus {
    pub fast: RecordingState,
    pub slow: RecordingState,
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
    pub fn status(&self) -> RecordingsStatus {
        let [fast, slow] = self.states.lock().unwrap().clone();
        RecordingsStatus { fast, slow }
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
        let errors: Vec<_> = self
            .histories
            .iter()
            .filter_map(|((slow, number), history)| {
                history.lock().unwrap().error.as_ref().map(|error| {
                    let stream = if *slow { "slow" } else { "fast" };
                    format!("{stream} recording {number}: {error}")
                })
            })
            .collect();
        (!errors.is_empty()).then(|| errors.join("; "))
    }
    pub fn start(&mut self, slow: bool, selections: &Selections) -> Result<()> {
        let slot = usize::from(slow);
        ensure!(
            !matches!(
                self.states.lock().unwrap()[slot].phase,
                RecordingPhase::Recording | RecordingPhase::Paused | RecordingPhase::Finalizing
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
        let metadata = json!({"schema_version":5, "stream":if slow {"slow"} else {"fast"},
            "requested_observables":selections, "mapping_confirmed":false,
            "position_basis":"contiguous recorded samples; time retains acquisition gaps",
            "slow_layout": if slow {Some("wide_forward_filled")} else {None},
            "slow_initial_values": if slow {Some("rows_omitted_until_all_observables_received")} else {None},
            "time_basis":"seconds from acquisition start, configured sample period; gaps unknown",
            "parquet":format!("{stem}.parquet"),
            "updates": if slow {Some(format!("{stem}.updates.parquet"))} else {None},
            "csv":!matches!(self.format, Format::Parquet)});
        // Headroom while a large segment is encoded and synced; independent of
        // live history. See DataOptions::queue_seconds.
        let queue_frames = self.options.queue_frames(
            self.profile.sample_period_us,
            self.profile.samples_per_packet,
        );
        let (tx, rx) = mpsc::sync_channel::<Batch>(queue_frames);
        let history = Arc::new(Mutex::new(History {
            reader: None,
            error: None,
            overflow: None,
            start: None,
            stop: None,
            persisted_stop: None,
            pending: Default::default(),
            pending_samples: 0,
            max_pending_samples: self
                .options
                .segment_rows
                .saturating_add((queue_frames + 2) * self.profile.samples_per_packet),
            columns: if slow {
                Vec::new()
            } else {
                selected_columns(&self.profile, &selections)?
            },
            slow,
        }));
        self.histories.insert((slow, n), history.clone());
        self.states.lock().unwrap()[slot] = RecordingState {
            phase: RecordingPhase::Recording,
            parquet: Some(dir.join(format!("{stem}.parquet"))),
            error: None,
            // Reported once the writer has created the index (see below).
            handle: None,
            backend: "parquet",
        };
        let writer_history = history.clone();
        let states = self.states.clone();
        let route_states = self.states.clone();
        let flush_interval = Duration::from_millis(self.options.flush_interval_ms);
        self.workers[slot] = Some(thread::spawn(move || {
            let mut rows = 0u64;
            // Kept outside the closure to store the final summary in the index.
            let mut writer: Option<LogWriter> = None;
            let result: Result<()> = (|| {
                // Disk initialization runs on the writer, never the control loop.
                // Frames accepted meanwhile remain in the bounded recording queue.
                let handle = crate::backend::index_path(&dir, &stem);
                let log = writer.insert(LogWriter::new_for_backend(
                    dir,
                    profile,
                    format,
                    stem,
                    slow,
                    &selections,
                    options.recording_backend,
                )?);
                log.segment_rows = options.segment_rows;
                writer_history.lock().unwrap().reader = Some(log.reader());
                // The index now exists, so a client can open the handle right away.
                states.lock().unwrap()[slot].handle = Some(handle);
                log.set_metadata(
                    json!({"recording":metadata,"rows":0,"complete":false,"error":null}),
                )?;
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
            let overflow = writer_history.lock().unwrap().overflow.clone();
            let writer_error = result.err().map(|e| format!("logging: {e:#}"));
            let mut error = match (overflow, writer_error) {
                (Some(overflow), Some(writer)) => Some(format!("{overflow}; {writer}")),
                (overflow, writer) => overflow.or(writer),
            };
            let summary =
                json!({"recording":metadata,"rows":rows,"complete":error.is_none(),"error":error});
            if let Some(log) = writer.as_mut()
                && let Err(e) = log.set_metadata(summary)
            {
                error.get_or_insert_with(|| format!("recording metadata: {e:#}"));
            }
            writer_history.lock().unwrap().error = error.clone();
            let mut s = states.lock().unwrap();
            s[slot].phase = if error.is_some() {
                RecordingPhase::Failed
            } else {
                RecordingPhase::Complete
            };
            s[slot].error = error;
        }));
        // Receiver uses the same lock: the recording starts at a complete frame boundary.
        self.routes.lock().unwrap()[slot] = Some(Route {
            tx,
            history,
            paused: false,
            states: route_states,
            slot,
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
        let (expected, next) = if paused {
            (RecordingPhase::Recording, RecordingPhase::Paused)
        } else {
            (RecordingPhase::Paused, RecordingPhase::Recording)
        };
        ensure!(
            states[slot].phase == expected,
            "recording must be {} before this operation",
            if paused { "recording" } else { "paused" }
        );
        route.paused = paused;
        states[slot].phase = next;
        Ok(())
    }
    pub fn stop(&mut self, slow: bool) -> Result<()> {
        let slot = usize::from(slow);
        let mut routes = self.routes.lock().unwrap();
        ensure!(routes[slot].is_some(), "this recording is not active");
        self.states.lock().unwrap()[slot].begin_finalizing();
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
    use std::fs;

    fn frame() -> Arc<Frame> {
        Arc::new(Frame {
            status: 0,
            slow_raw: vec![0; 15],
            slow_ids: vec![0; 15],
            channels: vec![vec![0.0; 15]; crate::protocol::CHANNELS],
        })
    }

    fn route(capacity: usize, max_pending_samples: usize) -> (Route, mpsc::Receiver<Batch>) {
        let (tx, rx) = mpsc::sync_channel(capacity);
        let history = Arc::new(Mutex::new(History {
            reader: None,
            error: None,
            overflow: None,
            start: None,
            stop: None,
            persisted_stop: None,
            pending: Default::default(),
            pending_samples: 0,
            max_pending_samples,
            columns: Vec::new(),
            slow: false,
        }));
        let states: Arc<Mutex<[RecordingState; 2]>> = Default::default();
        states.lock().unwrap()[0].phase = RecordingPhase::Recording;
        let route = Route {
            paused: false,
            tx,
            history,
            states,
            slot: 0,
        };
        (route, rx)
    }

    #[test]
    fn full_queue_ends_only_this_recording() -> Result<()> {
        let (route, rx) = route(1, 1_000);
        assert!(route.send(0, frame())?);
        // The writer has not drained: the next frame overflows. No error is
        // returned, so the receiver keeps acquiring and only drops this route.
        assert!(!route.send(15, frame())?);
        let history = route.history.lock().unwrap();
        assert!(
            history
                .overflow
                .as_deref()
                .unwrap()
                .contains("logger queue full at acquisition sample 15")
        );
        // Accepted samples stay; the rejected frame is not part of the recording.
        assert_eq!((history.start, history.stop), (Some(0), Some(15)));
        drop(history);
        assert_eq!(
            route.states.lock().unwrap()[0].phase,
            RecordingPhase::Finalizing
        );
        assert!(
            !route.send(30, frame())?,
            "an overflowed route stays retired"
        );
        assert_eq!(rx.try_iter().count(), 1);
        Ok(())
    }

    #[test]
    fn pending_memory_limit_ends_only_this_recording() -> Result<()> {
        let (route, _rx) = route(16, 20);
        assert!(route.send(0, frame())?);
        assert!(!route.send(15, frame())?);
        let history = route.history.lock().unwrap();
        assert!(
            history
                .overflow
                .as_deref()
                .unwrap()
                .contains("pending recording memory limit")
        );
        Ok(())
    }

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
            let selections = profile.initial_channels.clone();
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
            assert_eq!(recordings.status().fast.phase, RecordingPhase::Complete);
            assert!(dir.join("data.parquet").is_file());
            let info = crate::backend::open(&crate::backend::index_path(&dir, "data"))?.info()?;
            assert!(info.complete && info.start.is_none() && info.stop.is_none());
            Ok(())
        })();
        let _ = fs::remove_dir_all(dir);
        result
    }
}
