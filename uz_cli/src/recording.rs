//! Independent recording lifetimes. Disk finalization never blocks device control.
use crate::{
    live::DataOptions,
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

type Batch = (u64, Frame);
pub type Routes = Arc<Mutex<[Option<SyncSender<Batch>>; 2]>>;

// Leave headroom while a large segment is encoded and synced. With 15 samples
// per frame at 10 kHz this holds 3.072 seconds, independently of live history.
const LOGGER_QUEUE_FRAMES: usize = 2048;

#[derive(Clone, Serialize)]
pub struct RecordingState {
    pub phase: &'static str,
    pub parquet: Option<PathBuf>,
    pub error: Option<String>,
}
impl Default for RecordingState {
    fn default() -> Self {
        Self {
            phase: "idle",
            parquet: None,
            error: None,
        }
    }
}

pub struct Recordings {
    options: DataOptions,
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
                "recording" | "finalizing"
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
        let mut log = LogWriter::new(
            dir.clone(),
            self.profile.clone(),
            self.format,
            stem.clone(),
            slow,
            selections,
        )?;
        log.segment_rows = self.options.segment_rows;
        let metadata_path = dir.join(format!("{stem}.json"));
        let metadata = json!({"schema_version":5, "stream":if slow {"slow"} else {"fast"},
            "requested_observables":selections, "mapping_confirmed":false,
            "slow_layout": if slow {Some("wide_forward_filled")} else {None},
            "slow_initial_values": if slow {Some("rows_omitted_until_all_observables_received")} else {None},
            "time_basis":"seconds from acquisition start, configured sample period; gaps unknown",
            "parquet":format!("{stem}.parquet"), "csv":!matches!(self.format, Format::Parquet)});
        // Exclusive creation also reserves empty recordings before the first segment.
        let file = fs::File::create_new(&metadata_path)?;
        serde_json::to_writer_pretty(file, &metadata)?;
        let (tx, rx) = mpsc::sync_channel::<Batch>(LOGGER_QUEUE_FRAMES);
        self.states.lock().unwrap()[slot] = RecordingState {
            phase: "recording",
            parquet: Some(dir.join(format!("{stem}.parquet"))),
            error: None,
        };
        let states = self.states.clone();
        let flush_interval = Duration::from_millis(self.options.flush_interval_ms);
        self.workers[slot] = Some(thread::spawn(move || {
            let mut rows = 0u64;
            let result: Result<()> = (|| {
                let mut last_flush = Instant::now();
                loop {
                    match rx.recv_timeout(flush_interval.saturating_sub(last_flush.elapsed())) {
                        Ok((index, frame)) => {
                            rows += frame.slow_raw.len() as u64;
                            if log.push(index, frame)? {
                                last_flush = Instant::now();
                            } else if last_flush.elapsed() >= flush_interval {
                                log.flush()?;
                                last_flush = Instant::now();
                            }
                        }
                        Err(mpsc::RecvTimeoutError::Timeout) => {
                            log.flush()?;
                            last_flush = Instant::now();
                        }
                        Err(mpsc::RecvTimeoutError::Disconnected) => break,
                    }
                }
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
        self.routes.lock().unwrap()[slot] = Some(tx);
        self.counts[slot] = n;
        Ok(())
    }
    pub fn stop(&mut self, slow: bool) -> Result<()> {
        let slot = usize::from(slow);
        let mut routes = self.routes.lock().unwrap();
        ensure!(routes[slot].is_some(), "this recording is not active");
        {
            let mut states = self.states.lock().unwrap();
            if states[slot].phase == "recording" {
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
