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

/// Query metadata and Arrow payload together so cursors describe exactly these rows.
#[pyfunction]
fn data_query<'py>(
    py: Python<'py>,
    endpoint: String,
    command_json: String,
) -> PyResult<(String, Bound<'py, PyBytes>)> {
    let (reply, bytes) = py.detach(move || -> PyResult<_> {
        let op: Operation = serde_json::from_str(&command_json).map_err(error)?;
        if !matches!(op, Operation::ReadData { .. }) {
            return Err(error("expected read_data operation"));
        }
        service::exchange(&endpoint, op, true).map_err(error)
    })?;
    Ok((
        serde_json::to_string(&reply).map_err(error)?,
        PyBytes::new(py, &bytes),
    ))
}
#[pyfunction]
fn recording_info(py: Python<'_>, path: String) -> PyResult<String> {
    py.detach(move || {
        let reader = crate::backend::open(std::path::Path::new(&path)).map_err(error)?;
        serde_json::to_string(&reader.info().map_err(error)?).map_err(error)
    })
}
#[pyfunction]
#[pyo3(signature=(path, start, stop, channels=None))]
fn recording_data(
    py: Python<'_>,
    path: String,
    start: u64,
    stop: u64,
    channels: Option<Vec<String>>,
) -> PyResult<Bound<'_, PyBytes>> {
    let bytes = py.detach(move || -> PyResult<Vec<u8>> {
        use polars::prelude::*;
        let reader = crate::backend::open(std::path::Path::new(&path)).map_err(error)?;
        let info = reader.info().map_err(error)?;
        let projection =
            crate::backend::query_projection(&info.fields, channels.as_deref()).map_err(error)?;
        let per_row: usize = info
            .fields
            .iter()
            .map(|f| match f.dtype.as_str() {
                "f64" => 8,
                "str" => 256,
                _ => 4,
            })
            .sum();
        if start > stop
            || stop - start > ((crate::live::MAX_SNAPSHOT_BYTES - 65536) / per_row) as u64
        {
            return Err(error(
                "range is invalid or exceeds response limit; use iter_batches",
            ));
        }
        let mut df = reader
            .read_projected_range(start, stop, projection.as_deref())
            .map_err(error)?;
        let mut bytes = Vec::new();
        IpcStreamWriter::new(&mut bytes)
            .finish(&mut df)
            .map_err(error)?;
        if bytes.len() > crate::live::MAX_SNAPSHOT_BYTES {
            return Err(error("snapshot exceeds response limit"));
        }
        Ok(bytes)
    })?;
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
    #[pyo3(signature=(device=None, endpoint="127.0.0.1:19740".to_string(), output=None, profile=None, format="both".to_string(), ack=false, channel_mapping=None, *, buffer_samples=None, segment_rows=1_000_000, flush_interval_ms=60_000, recording_backend="parquet"))]
    fn new(
        py: Python<'_>,
        device: Option<String>,
        endpoint: String,
        output: Option<String>,
        profile: Option<String>,
        format: String,
        ack: bool,
        channel_mapping: Option<String>,
        buffer_samples: Option<usize>,
        segment_rows: usize,
        flush_interval_ms: u64,
        recording_backend: &str,
    ) -> PyResult<Self> {
        if recording_backend != "parquet" {
            return Err(error("unsupported recording backend"));
        }
        let data = DataOptions {
            recording_backend: Default::default(),
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
    #[pyo3(signature=(stream="fast", recording=1))]
    fn recording_handle_path(&self, stream: &str, recording: u64) -> PyResult<String> {
        if self.worker.is_some() {
            return Err(error("call acquisition.close() before reading recordings"));
        }
        if !matches!(stream, "fast" | "slow") || recording == 0 {
            return Err(error(
                "stream must be fast or slow; recording must be positive",
            ));
        }
        let base = if recording == 1 {
            "data".to_string()
        } else {
            format!("data_{recording:04}")
        };
        let id = if stream == "slow" {
            format!("{base}_slow_data")
        } else {
            base
        };
        let path = crate::backend::index_path(&self.output, &id);
        let reader = crate::backend::open(&path).map_err(error)?;
        if !reader.info().map_err(error)?.complete {
            return Err(error(
                "recording is not complete; inspect its metadata for errors",
            ));
        }
        Ok(path.to_string_lossy().into_owned())
    }
    /// Resolve only a successfully completed compatibility export from this acquisition.
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
    m.add_function(wrap_pyfunction!(data_query, m)?)?;
    m.add_function(wrap_pyfunction!(recording_info, m)?)?;
    m.add_function(wrap_pyfunction!(recording_data, m)?)?;
    m.add_function(wrap_pyfunction!(cli_main, m)?)?;
    m.add_class::<Acquisition>()?;
    Ok(())
}
