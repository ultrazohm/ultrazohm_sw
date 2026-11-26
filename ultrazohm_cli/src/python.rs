use crate::{
    live::DataOptions,
    profile::{ChannelMapping, Profile, ProfileSettings},
    service::{self, Config, Operation},
    storage::Format,
};
use pyo3::{
    exceptions::{PyRuntimeError, PyValueError},
    prelude::*,
    types::PyBytes,
};
use serde::{Serialize, de::DeserializeOwned};
use std::{
    path::{Path, PathBuf},
    sync::{
        Arc, Mutex,
        atomic::{AtomicBool, Ordering},
        mpsc,
    },
    thread,
};
fn error(e: impl std::fmt::Display) -> PyErr {
    PyRuntimeError::new_err(e.to_string())
}
/// Invalid user input or configuration.
fn invalid(e: anyhow::Error) -> PyErr {
    PyValueError::new_err(format!("{e:#}"))
}
/// RuntimeError carrying a stable error `code`: the service's code, or
/// `connection_refused`, `timeout` or `transport` (None when uncoded).
fn api_error(py: Python<'_>, e: anyhow::Error) -> PyErr {
    let err = PyRuntimeError::new_err(format!("{e:#}"));
    let _ = err
        .value(py)
        .setattr("code", service::client_error_code(&e));
    err
}

/// Convert a Python object into a Rust value through Python's JSON encoder, the
/// same rules as the wire format: NaN, infinity and circular references are
/// rejected, and integer dictionary keys become strings.
fn from_py<T: DeserializeOwned>(value: &Bound<'_, PyAny>) -> PyResult<T> {
    let py = value.py();
    let options = pyo3::types::PyDict::new(py);
    options.set_item("allow_nan", false)?;
    let text: String = py
        .import("json")?
        .call_method("dumps", (value,), Some(&options))
        .map_err(|e| PyValueError::new_err(format!("value is not JSON-compatible: {e}")))?
        .extract()?;
    serde_json::from_str(&text).map_err(|e| PyValueError::new_err(e.to_string()))
}

fn to_py<'py>(py: Python<'py>, value: &impl Serialize) -> PyResult<Bound<'py, PyAny>> {
    let value = serde_json::to_value(value).map_err(error)?;
    pythonize::pythonize(py, &value).map_err(error)
}

/// One persistent connection to an acquisition service; requests are sequential.
#[pyclass]
struct Connection(Mutex<service::Connection>);

impl Connection {
    fn operation(op: &str, args: Option<&Bound<'_, PyAny>>) -> PyResult<Operation> {
        let args = match args {
            Some(args) => from_py(args)?,
            None => serde_json::Map::new(),
        };
        Operation::from_wire(op, args).map_err(invalid)
    }
}

#[pymethods]
impl Connection {
    #[new]
    fn new(endpoint: String) -> Self {
        Self(Mutex::new(service::Connection::new(&endpoint)))
    }

    /// Send operation `op` with `args`; return the reply's result.
    #[pyo3(signature=(op, args=None))]
    fn request<'py>(
        &self,
        py: Python<'py>,
        op: &str,
        args: Option<&Bound<'py, PyAny>>,
    ) -> PyResult<Bound<'py, PyAny>> {
        let op = Self::operation(op, args)?;
        if matches!(op, Operation::ReadData { .. }) {
            return Err(error("use data_query for binary sample responses"));
        }
        let (result, _) = py
            .detach(|| self.0.lock().unwrap().exchange(op, false))
            .map_err(|e| api_error(py, e))?;
        to_py(py, &result)
    }

    /// Query metadata and Arrow payload together so cursors describe exactly these rows.
    fn data_query<'py>(
        &self,
        py: Python<'py>,
        args: &Bound<'py, PyAny>,
    ) -> PyResult<(Bound<'py, PyAny>, Bound<'py, PyBytes>)> {
        let op = Self::operation("read_data", Some(args))?;
        let (result, bytes) = py
            .detach(|| self.0.lock().unwrap().exchange(op, true))
            .map_err(|e| api_error(py, e))?;
        Ok((to_py(py, &result)?, PyBytes::new(py, &bytes)))
    }

    /// Drop the socket; the next request reconnects.
    fn close(&self) {
        self.0.lock().unwrap().reset();
    }
}
#[pyfunction]
fn recording_info(py: Python<'_>, path: PathBuf) -> PyResult<Bound<'_, PyAny>> {
    let info = py.detach(move || {
        let reader = crate::backend::open(&path).map_err(error)?;
        reader.info().map_err(error)
    })?;
    to_py(py, &info)
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
        let reader = crate::backend::open(Path::new(&path)).map_err(error)?;
        let info = reader.info().map_err(error)?;
        let projection =
            crate::backend::query_projection(&info.fields, channels.as_deref()).map_err(error)?;
        if start > stop || stop - start > crate::data::max_rows(&info.fields, 256) {
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

/// One interactive-prompt command against a running service; returns its output.
#[pyfunction]
fn console_command(py: Python<'_>, endpoint: String, line: String) -> PyResult<String> {
    py.detach(move || crate::cli::console_command(&endpoint, &line))
        .map_err(|e| api_error(py, e))
}

/// Run the same CLI as the standalone binary, without requiring that binary.
#[pyfunction]
fn cli_main(py: Python<'_>, argv: Vec<String>) -> i32 {
    py.detach(move || crate::cli::run(argv))
}

/// Optional embedded Rust service. External `ultrazohm_cli serve` survives Python exit.
#[pyclass(subclass)]
struct Acquisition {
    output: Arc<Mutex<PathBuf>>,
    stop: Arc<AtomicBool>,
    worker: Option<thread::JoinHandle<anyhow::Result<()>>>,
}
#[pymethods]
impl Acquisition {
    #[new]
    #[allow(clippy::too_many_arguments)] // Python keyword options plus the GIL token.
    #[pyo3(signature=(device=None, endpoint="127.0.0.1:19740".to_string(), output=None, profile=None, format="parquet".to_string(), ack=false, channel_mapping=None, *, repo=None, xsct=None, buffer_samples=None, segment_rows=1_000_000, flush_interval_ms=60_000, recording_backend="parquet", queue_seconds=crate::live::DEFAULT_QUEUE_SECONDS))]
    fn new(
        py: Python<'_>,
        device: Option<String>,
        endpoint: String,
        output: Option<String>,
        profile: Option<String>,
        format: String,
        ack: bool,
        channel_mapping: Option<String>,
        repo: Option<String>,
        xsct: Option<String>,
        buffer_samples: Option<usize>,
        segment_rows: usize,
        flush_interval_ms: u64,
        recording_backend: &str,
        queue_seconds: f64,
    ) -> PyResult<Self> {
        if recording_backend != "parquet" {
            return Err(error("unsupported recording backend"));
        }
        let data = DataOptions {
            recording_backend: Default::default(),
            buffer_samples,
            segment_rows,
            flush_interval_ms,
            queue_seconds,
        };
        data.validate().map_err(error)?;
        let repo = repo
            .map(PathBuf::from)
            .map(|path| crate::vitis::repository(Some(&path)))
            .transpose()
            .map_err(error)?;
        let xsct = xsct
            .map(PathBuf::from)
            .map(|path| crate::preferences::validate_xsct(&path))
            .transpose()
            .map_err(error)?;
        let profile = Profile::load_repository(
            profile.as_deref().map(std::path::Path::new),
            channel_mapping.as_deref().map(std::path::Path::new),
            repo.as_deref(),
        )
        .map_err(error)?;
        let format = match format.as_str() {
            "csv" => Format::Csv,
            "parquet" => Format::Parquet,
            _ => return Err(error("format must be csv or parquet")),
        };
        let output =
            service::session_output_for_repository(output.map(PathBuf::from), repo.as_deref())
                .map_err(error)?;
        let output = Arc::new(Mutex::new(output));
        let worker_output = output.lock().unwrap().clone();
        let current_output = output.clone();
        let (ready_tx, ready_rx) = mpsc::sync_channel(1);
        let stop = Arc::new(AtomicBool::new(false));
        let signal = stop.clone();
        let worker = thread::spawn(move || {
            service::serve_with_ready(
                Config {
                    launch_id: None,
                    current_output: Some(current_output),
                    repo,
                    xsct,
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
        self.output.lock().unwrap().to_string_lossy().into_owned()
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
        let path = crate::backend::index_path(&self.output.lock().unwrap(), &id);
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
        let summary = crate::backend::read_metadata(&crate::backend::index_path(
            &self.output.lock().unwrap(),
            &stem,
        ))
        .map_err(error)?
        .unwrap_or_default();
        if summary["complete"] != true {
            return Err(error(
                "recording is not complete; inspect its metadata for errors",
            ));
        }
        let path = self.output.lock().unwrap().join(format!("{stem}.parquet"));
        if !path.is_file() {
            return Err(error("completed recording file is missing"));
        }
        Ok(path.to_string_lossy().into_owned())
    }
}
impl Drop for Acquisition {
    /// An acquisition that is garbage collected without close() still sends
    /// device Stop and finalizes its recordings before the object goes away;
    /// the service thread never needs the GIL, so joining it cannot deadlock.
    fn drop(&mut self) {
        self.stop.store(true, Ordering::SeqCst);
        if let Some(worker) = self.worker.take() {
            match worker.join() {
                Ok(Ok(())) => {}
                Ok(Err(error)) => {
                    eprintln!("UltraZohm acquisition closed with an error: {error:#}")
                }
                Err(_) => eprintln!("UltraZohm acquisition thread panicked"),
            }
        }
    }
}
// Offline configuration helpers share validation with service startup.
// Invalid input or configuration raises ValueError.

/// Parse the checkout's firmware headers without contacting a device.
#[pyfunction]
fn channel_mapping(py: Python<'_>, repo: PathBuf) -> PyResult<Bound<'_, PyAny>> {
    let mapping = py
        .detach(|| ChannelMapping::load_repository(None, Some(&repo)))
        .map_err(invalid)?;
    to_py(py, &mapping)
}

/// Built-in startup preferences, filtered for a checkout if supplied.
#[pyfunction]
#[pyo3(signature=(repo=None))]
fn default_profile(py: Python<'_>, repo: Option<PathBuf>) -> PyResult<Bound<'_, PyAny>> {
    let settings = py
        .detach(|| match &repo {
            Some(repo) => {
                let mapping = ChannelMapping::load_repository(None, Some(repo))?;
                ProfileSettings::for_mapping(None, &mapping)
            }
            None => ProfileSettings::load(None),
        })
        .map_err(invalid)?;
    to_py(py, &settings)
}

/// Validate runtime preference structure; return normalized preferences.
#[pyfunction]
fn validate_profile<'py>(
    py: Python<'py>,
    profile: &Bound<'py, PyAny>,
) -> PyResult<Bound<'py, PyAny>> {
    let settings: ProfileSettings = from_py(profile)?;
    settings.validate().map_err(invalid)?;
    to_py(py, &settings)
}

/// Return (effective preferences, removed names) for a firmware mapping.
#[pyfunction]
fn remap_profile<'py>(
    py: Python<'py>,
    mapping: &Bound<'py, PyAny>,
    profile: &Bound<'py, PyAny>,
) -> PyResult<(Bound<'py, PyAny>, Vec<String>)> {
    let mapping: ChannelMapping = from_py(mapping)?;
    let settings: ProfileSettings = from_py(profile)?;
    let (settings, removed) = settings.remap(&mapping).map_err(invalid)?;
    Profile::from_mapping(settings.clone(), mapping).map_err(invalid)?;
    Ok((to_py(py, &settings)?, removed))
}

/// The shared preferences directory; nothing is created.
#[pyfunction]
#[pyo3(signature=(repo=None))]
fn preferences_directory(repo: Option<PathBuf>) -> PyResult<PathBuf> {
    crate::preferences::directory(repo.as_deref()).map_err(invalid)
}

/// Resolve an explicit launcher, then the saved selection, then PATH.
#[pyfunction]
#[pyo3(signature=(path=None, repo=None))]
fn resolve_xsct(path: Option<PathBuf>, repo: Option<PathBuf>) -> PyResult<PathBuf> {
    crate::preferences::resolve_xsct(path.as_deref(), repo.as_deref()).map_err(invalid)
}

#[pyfunction]
#[pyo3(signature=(repo=None))]
fn saved_xsct(repo: Option<PathBuf>) -> PyResult<Option<PathBuf>> {
    crate::preferences::saved_xsct(repo.as_deref()).map_err(invalid)
}

#[pyfunction]
#[pyo3(signature=(path, repo=None))]
fn save_xsct(path: PathBuf, repo: Option<PathBuf>) -> PyResult<PathBuf> {
    crate::preferences::save_xsct(&path, repo.as_deref()).map_err(invalid)
}

/// Atomically seed missing defaults; preserve existing preferences.
#[pyfunction]
fn load_or_seed_profile<'py>(
    py: Python<'py>,
    path: PathBuf,
    mapping: &Bound<'py, PyAny>,
) -> PyResult<Bound<'py, PyAny>> {
    let mapping: ChannelMapping = from_py(mapping)?;
    let settings = crate::preferences::load_or_seed(&path, &mapping).map_err(invalid)?;
    to_py(py, &settings)
}

/// Validate against a firmware mapping before atomically replacing preferences.
#[pyfunction]
fn save_profile(
    path: PathBuf,
    profile: &Bound<'_, PyAny>,
    mapping: &Bound<'_, PyAny>,
) -> PyResult<()> {
    let settings: ProfileSettings = from_py(profile)?;
    let mapping: ChannelMapping = from_py(mapping)?;
    crate::preferences::save_profile(&path, &settings, &mapping).map_err(invalid)
}

/// Follower progress of a `job` reply polled from `offset`.
#[pyfunction]
fn job_progress<'py>(
    py: Python<'py>,
    offset: u64,
    reply: &Bound<'py, PyAny>,
) -> PyResult<Bound<'py, PyAny>> {
    let reply: serde_json::Value = from_py(reply)?;
    let progress = crate::jobs::progress(offset, &reply).map_err(invalid)?;
    to_py(py, &progress)
}

#[pymodule]
fn _native(m: &Bound<'_, PyModule>) -> PyResult<()> {
    for function in [
        wrap_pyfunction!(channel_mapping, m)?,
        wrap_pyfunction!(default_profile, m)?,
        wrap_pyfunction!(validate_profile, m)?,
        wrap_pyfunction!(remap_profile, m)?,
        wrap_pyfunction!(preferences_directory, m)?,
        wrap_pyfunction!(resolve_xsct, m)?,
        wrap_pyfunction!(saved_xsct, m)?,
        wrap_pyfunction!(save_xsct, m)?,
        wrap_pyfunction!(load_or_seed_profile, m)?,
        wrap_pyfunction!(save_profile, m)?,
        wrap_pyfunction!(job_progress, m)?,
    ] {
        m.add_function(function)?;
    }
    m.add_class::<Connection>()?;
    m.add_function(wrap_pyfunction!(recording_info, m)?)?;
    m.add_function(wrap_pyfunction!(recording_data, m)?)?;
    m.add_function(wrap_pyfunction!(cli_main, m)?)?;
    m.add_function(wrap_pyfunction!(console_command, m)?)?;
    m.add_class::<Acquisition>()?;
    Ok(())
}
