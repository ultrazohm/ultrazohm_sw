use crate::{
    profile::Profile,
    service::{self, Config, Operation},
    storage::Format,
};
use pyo3::{exceptions::PyRuntimeError, prelude::*};
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
/// Run the same CLI as the standalone binary, without requiring that binary.
#[pyfunction]
fn cli_main(py: Python<'_>, argv: Vec<String>) -> i32 {
    py.detach(move || crate::cli::run(argv))
}

/// Optional embedded Rust service. External `ultrazohm serve` survives Python exit.
#[pyclass]
struct Acquisition {
    output: PathBuf,
    stop: Arc<AtomicBool>,
    worker: Option<thread::JoinHandle<anyhow::Result<()>>>,
}
#[pymethods]
impl Acquisition {
    #[new]
    #[allow(clippy::too_many_arguments)] // Python keyword options plus the GIL token.
    #[pyo3(signature=(device=None, endpoint="127.0.0.1:19740".to_string(), output=None, profile=None, format="both".to_string(), ack=false, channel_mapping=None))]
    fn new(
        py: Python<'_>,
        device: Option<String>,
        endpoint: String,
        output: Option<String>,
        profile: Option<String>,
        format: String,
        ack: bool,
        channel_mapping: Option<String>,
    ) -> PyResult<Self> {
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
}
impl Drop for Acquisition {
    fn drop(&mut self) {
        self.stop.store(true, Ordering::SeqCst);
    }
}
#[pymodule]
fn _native(m: &Bound<'_, PyModule>) -> PyResult<()> {
    m.add_function(wrap_pyfunction!(request, m)?)?;
    m.add_function(wrap_pyfunction!(cli_main, m)?)?;
    m.add_class::<Acquisition>()?;
    Ok(())
}
