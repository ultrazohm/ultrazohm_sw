use crate::{
    live::DataOptions,
    profile::Profile,
    service::{self, Config, Operation},
    storage::Format,
};
use pyo3::{exceptions::PyRuntimeError, prelude::*, types::PyBytes};
use std::{
    path::PathBuf,
    sync::{
        Arc,
        atomic::{AtomicBool, Ordering},
        mpsc,
    },
    thread,
};
fn error(e: impl std::fmt::Display) -> PyErr {
    PyRuntimeError::new_err(e.to_string())
}
#[pyfunction]
fn request(py: Python<'_>, endpoint: String, command_json: String) -> PyResult<String> {
    py.detach(move || {
        let op: Operation = serde_json::from_str(&command_json).map_err(error)?;
        let result = service::request(&endpoint, op).map_err(error)?;
        serde_json::to_string(&result).map_err(error)
    })
}
#[pyfunction]
fn live_data(
    py: Python<'_>,
    endpoint: String,
    last_n_samples: usize,
) -> PyResult<Bound<'_, PyBytes>> {
    let bytes = py
        .detach(move || service::get_live_data(&endpoint, last_n_samples))
        .map_err(error)?;
    Ok(PyBytes::new(py, &bytes))
}

/// Run the same CLI as the standalone binary, without requiring that binary.
#[pyfunction]
fn cli_main(py: Python<'_>, argv: Vec<String>) -> i32 {
    py.detach(move || crate::cli::run(argv))
}

/// Optional embedded Rust service. External `ultrazohm serve` survives Python exit.
#[pyclass(subclass)]
struct Acquisition {
    output: PathBuf,
    stop: Arc<AtomicBool>,
    worker: Option<thread::JoinHandle<anyhow::Result<()>>>,
}
#[pymethods]
impl Acquisition {
    #[new]
    #[allow(clippy::too_many_arguments)] // Python keyword options plus the GIL token.
    #[pyo3(signature=(device=None, endpoint="127.0.0.1:19740".to_string(), output=None, profile=None, format="both".to_string(), ack=false, channel_mapping=None, *, buffer_samples=960, segment_rows=1_000_000, flush_interval_ms=60_000))]
    fn new(
        py: Python<'_>,
        device: Option<String>,
        endpoint: String,
        output: Option<String>,
        profile: Option<String>,
        format: String,
        ack: bool,
        channel_mapping: Option<String>,
        buffer_samples: usize,
        segment_rows: usize,
        flush_interval_ms: u64,
    ) -> PyResult<Self> {
        let data = DataOptions {
            buffer_samples,
            segment_rows,
            flush_interval_ms,
        };
        data.validate().map_err(error)?;
        let profile = Profile::load_files(
            profile.as_deref().map(std::path::Path::new),
            channel_mapping.as_deref().map(std::path::Path::new),
        )
        .map_err(error)?;
        let format = match format.as_str() {
            "csv" => Format::Csv,
            "parquet" => Format::Parquet,
            "both" => Format::Both,
            _ => return Err(error("format must be csv, parquet or both")),
        };
        let output = service::session_output(output.map(PathBuf::from)).map_err(error)?;
        let worker_output = output.clone();
        let (ready_tx, ready_rx) = mpsc::sync_channel(1);
        let stop = Arc::new(AtomicBool::new(false));
        let signal = stop.clone();
        let worker = thread::spawn(move || {
            service::serve_with_ready(
                Config {
                    data,
                    device,
                    endpoint,
                    output: Some(worker_output),
                    profile,
                    format,
                    ack,
                },
                signal,
                move || {
                    let _ = ready_tx.send(());
                },
            )
        });
        // Dropping the readiness sender on an early return/panic wakes the
        // constructor too. Surface startup failures here, not on a later close().
        if py.detach(move || ready_rx.recv()).is_err() {
            let result = py
                .detach(move || worker.join())
                .map_err(|_| error("acquisition thread panicked during startup"))?;
            return match result {
                Err(e) => Err(error(format!("{e:#}"))),
                Ok(()) => Err(error("acquisition ended before startup completed")),
            };
        }
        Ok(Self {
            output,
            stop,
            worker: Some(worker),
        })
    }
    /// The session directory, including automatically generated defaults.
    #[getter]
    fn output(&self) -> String {
        self.output.to_string_lossy().into_owned()
    }
    fn close(&mut self, py: Python<'_>) -> PyResult<()> {
        self.stop.store(true, Ordering::SeqCst);
        if let Some(worker) = self.worker.take() {
            py.detach(move || {
                worker
                    .join()
                    .map_err(|_| error("acquisition thread panicked"))?
                    .map_err(error)
            })?;
        }
        Ok(())
    }
    fn is_finished(&self) -> bool {
        self.worker.as_ref().is_none_or(|w| w.is_finished())
    }
    /// Resolve only a successfully finalized recording from this acquisition.
    #[pyo3(signature=(stream="fast", recording=1))]
    fn recording_path(&self, stream: &str, recording: u32) -> PyResult<String> {
        if self.worker.is_some() {
            return Err(error("call acquisition.close() before reading recordings"));
        }
        if !matches!(stream, "fast" | "slow") || recording == 0 {
            return Err(error(
                "stream must be fast or slow; recording must be positive",
            ));
        }
        let base = if recording == 1 {
            "data".into()
        } else {
            format!("data_{recording:04}")
        };
        let stem = if stream == "slow" {
            format!("{base}_slow_data")
        } else {
            base
        };
        let sidecar: serde_json::Value = serde_json::from_slice(
            &std::fs::read(self.output.join(format!("{stem}.json"))).map_err(error)?,
        )
        .map_err(error)?;
        if sidecar["complete"] != true {
            return Err(error(
                "recording is not complete; inspect its metadata for errors",
            ));
        }
        let path = self.output.join(format!("{stem}.parquet"));
        if !path.is_file() {
            return Err(error("completed recording file is missing"));
        }
        Ok(path.to_string_lossy().into_owned())
    }
}
impl Drop for Acquisition {
    fn drop(&mut self) {
        self.stop.store(true, Ordering::SeqCst);
    }
}
#[pymodule]
fn _native(m: &Bound<'_, PyModule>) -> PyResult<()> {
    m.add_function(wrap_pyfunction!(request, m)?)?;
    m.add_function(wrap_pyfunction!(live_data, m)?)?;
    m.add_function(wrap_pyfunction!(cli_main, m)?)?;
    m.add_class::<Acquisition>()?;
    Ok(())
}
