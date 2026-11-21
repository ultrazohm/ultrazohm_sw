//! Recording storage contract. Positions address contiguous recorded rows, [start, stop); time retains acquisition gaps.
//! Backends receive typed columns, never device frames or GUI requests.
use anyhow::{Context, Result, ensure};
use polars::prelude::*;
use serde::{Deserialize, Serialize};
use serde_json::Value;
use std::{
    fs::{self, File},
    path::{Path, PathBuf},
    sync::{Arc, Mutex},
};

/// Rows per Parquet row group in parts, and per slice when finalization and
/// CSV export read them back, so each row group is decoded about once.
pub const ROW_GROUP_ROWS: usize = 65_536;

#[derive(Clone, Copy, Debug, Default, Serialize, Deserialize, clap::ValueEnum)]
#[serde(rename_all = "snake_case")]
pub enum BackendKind {
    #[default]
    Parquet,
}

#[derive(Clone, Debug, Serialize, Deserialize)]
pub struct Field {
    pub name: String,
    pub dtype: String,
}

#[derive(Clone, Debug, Serialize, Deserialize)]
pub struct RecordingInfo {
    pub schema_version: u32,
    pub backend: String,
    pub recording_id: String,
    pub stream: String,
    pub sample_period_us: f64,
    #[serde(default = "acquisition_positions")]
    pub position_basis: String,
    pub fields: Vec<Field>,
    pub start: Option<u64>,
    pub stop: Option<u64>,
    pub complete: bool,
}
fn acquisition_positions() -> String {
    "acquisition_samples".into()
}
impl RecordingInfo {
    pub fn empty(&self) -> Result<DataFrame> {
        self.empty_projected(None)
    }

    pub fn empty_projected(&self, projection: Option<&[String]>) -> Result<DataFrame> {
        let mut columns = Vec::new();
        let fields = match projection {
            None => self.fields.iter().collect::<Vec<_>>(),
            Some(names) => {
                ensure!(
                    !names.is_empty(),
                    "projection must select at least one column"
                );
                names
                    .iter()
                    .map(|name| {
                        self.fields
                            .iter()
                            .find(|f| f.name == *name)
                            .with_context(|| format!("unknown recording column {name}"))
                    })
                    .collect::<Result<Vec<_>>>()?
            }
        };
        for field in fields {
            let dtype = match field.dtype.as_str() {
                "f32" => DataType::Float32,
                "f64" => DataType::Float64,
                "u32" => DataType::UInt32,
                "str" => DataType::String,
                other => anyhow::bail!("unsupported recording type {other}"),
            };
            columns.push(Series::new_empty(field.name.clone().into(), &dtype).into_column());
        }
        Ok(DataFrame::new(columns)?)
    }
}

/// Public queries always retain time/status and preserve requested channel order.
pub fn query_projection(
    fields: &[Field],
    channels: Option<&[String]>,
) -> Result<Option<Vec<String>>> {
    channels
        .map(|channels| {
            let mut names = vec!["time".to_owned(), "status".to_owned()];
            for name in channels {
                if !names.contains(name) {
                    names.push(name.clone());
                }
            }
            for name in &names {
                ensure!(
                    fields.iter().any(|f| f.name == *name),
                    "unknown recording column {name}"
                );
            }
            Ok(names)
        })
        .transpose()
}

pub struct SampleBatch {
    pub start: u64,
    pub data: DataFrame,
}

/// Readers may run concurrently with appends/finalization. Published data is immutable.
pub trait RecordingReader: Send + Sync {
    fn info(&self) -> Result<RecordingInfo>;
    fn read_range(&self, start: u64, stop: u64) -> Result<DataFrame> {
        self.read_projected_range(start, stop, None)
    }
    /// Read exactly these columns in this order; None requests the complete schema.
    fn read_projected_range(
        &self,
        start: u64,
        stop: u64,
        projection: Option<&[String]>,
    ) -> Result<DataFrame>;
}
pub trait RecordingBackend: Send {
    /// Return only after this batch and its index have been published successfully.
    fn append(&mut self, batch: SampleBatch) -> Result<()>;
    fn reader(&self) -> Arc<dyn RecordingReader>;
    fn finish(&mut self) -> Result<()>;
    /// After `finish`, replace the canonical segments by one merged file holding
    /// exactly the same rows and schema, then remove the superseded segments.
    fn consolidate(&mut self, _merged: &Path) -> Result<()> {
        Ok(())
    }
    /// Store recording metadata (settings, row count, completion) with the index.
    fn set_metadata(&mut self, _metadata: Value) -> Result<()> {
        Ok(())
    }
}

#[derive(Clone, Debug, Serialize, Deserialize)]
struct Segment {
    start: u64,
    stop: u64,
    file: String,
}
#[derive(Clone, Debug, Serialize, Deserialize)]
struct Index {
    info: RecordingInfo,
    segments: Vec<Segment>,
    /// Recording settings and result, maintained by the recording writer.
    #[serde(default, skip_serializing_if = "Option::is_none")]
    metadata: Option<Value>,
}

#[derive(Clone)]
pub struct ParquetReaderHandle {
    dir: PathBuf,
    path: PathBuf,
    index: Arc<Mutex<Index>>,
}
pub struct ParquetBackend {
    reader: ParquetReaderHandle,
    index_path: PathBuf,
}

fn publish(path: &Path, index: &Index) -> Result<()> {
    let tmp = path.with_extension("json.partial");
    let file = File::create(&tmp)?;
    serde_json::to_writer_pretty(&file, index)?;
    file.sync_all()?;
    drop(file);
    // Replace the previous index with one complete publication.
    replace_file(&tmp, path)?;
    Ok(())
}

/// Atomically replace `target` by `source`. Windows refuses the replacement
/// while another process (a Python reader, a virus scanner, the indexer) has
/// `target` open without delete sharing, so retry for up to one second.
pub(crate) fn replace_file(source: &Path, target: &Path) -> std::io::Result<()> {
    let attempts = if cfg!(windows) { 20 } else { 1 };
    for attempt in 1..=attempts {
        match fs::rename(source, target) {
            Err(error) if attempt < attempts && error.kind() != std::io::ErrorKind::NotFound => {
                std::thread::sleep(std::time::Duration::from_millis(50));
            }
            result => return result,
        }
    }
    unreachable!("the last attempt returns")
}

/// Publish `source` as `target` only if `target` does not exist yet. Hard links
/// make this atomic; file systems without them (FAT, exFAT, some network
/// shares) use an exclusive OS rename.
pub(crate) fn publish_new(source: &Path, target: &Path) -> std::io::Result<()> {
    publish_new_with(source, target, |source, target| {
        fs::hard_link(source, target)
    })
}

fn publish_new_with(
    source: &Path,
    target: &Path,
    link: impl Fn(&Path, &Path) -> std::io::Result<()>,
) -> std::io::Result<()> {
    match link(source, target) {
        Ok(()) => Ok(()),
        Err(error) if error.kind() == std::io::ErrorKind::AlreadyExists => Err(error),
        Err(_) => rename_new(source, target),
    }
}

// OS-level exclusive rename also works on filesystems without hard links.
#[cfg(unix)]
fn rename_new(source: &Path, target: &Path) -> std::io::Result<()> {
    use std::os::unix::ffi::OsStrExt;
    let source = std::ffi::CString::new(source.as_os_str().as_bytes())?;
    let target = std::ffi::CString::new(target.as_os_str().as_bytes())?;
    #[cfg(target_os = "linux")]
    let result = {
        unsafe extern "C" {
            fn renameat2(
                a: i32,
                source: *const std::ffi::c_char,
                b: i32,
                target: *const std::ffi::c_char,
                flags: u32,
            ) -> i32;
        }
        unsafe { renameat2(-100, source.as_ptr(), -100, target.as_ptr(), 1) }
    };
    #[cfg(target_os = "macos")]
    let result = {
        unsafe extern "C" {
            fn renamex_np(
                source: *const std::ffi::c_char,
                target: *const std::ffi::c_char,
                flags: u32,
            ) -> i32;
        }
        unsafe { renamex_np(source.as_ptr(), target.as_ptr(), 4) }
    };
    #[cfg(not(any(target_os = "linux", target_os = "macos")))]
    return Err(std::io::Error::from(std::io::ErrorKind::Unsupported));
    #[cfg(any(target_os = "linux", target_os = "macos"))]
    if result == 0 {
        Ok(())
    } else {
        Err(std::io::Error::last_os_error())
    }
}

#[cfg(windows)]
fn rename_new(source: &Path, target: &Path) -> std::io::Result<()> {
    use std::os::windows::ffi::OsStrExt;
    let source: Vec<u16> = source.as_os_str().encode_wide().chain(Some(0)).collect();
    let target: Vec<u16> = target.as_os_str().encode_wide().chain(Some(0)).collect();
    #[link(name = "kernel32")]
    unsafe extern "system" {
        fn MoveFileExW(source: *const u16, target: *const u16, flags: u32) -> i32;
    }
    if unsafe { MoveFileExW(source.as_ptr(), target.as_ptr(), 0) } != 0 {
        Ok(())
    } else {
        Err(std::io::Error::last_os_error())
    }
}

pub fn create(
    kind: BackendKind,
    dir: &Path,
    id: &str,
    slow: bool,
    period: f64,
    schema: &DataFrame,
) -> Result<Box<dyn RecordingBackend>> {
    match kind {
        BackendKind::Parquet => Ok(Box::new(ParquetBackend::create(
            dir, id, slow, period, schema,
        )?)),
    }
}
pub fn index_path(dir: &Path, id: &str) -> PathBuf {
    dir.join(format!("{id}.recording.json"))
}

impl ParquetBackend {
    pub fn create(
        dir: &Path,
        id: &str,
        slow: bool,
        period: f64,
        schema: &DataFrame,
    ) -> Result<Self> {
        ensure!(dir.is_dir(), "recording directory does not exist");
        ensure!(
            Path::new(id).components().count() == 1
                && !id.contains(['/', '\\'])
                && id != "."
                && id != "..",
            "invalid recording identifier"
        );
        let path = index_path(dir, id);
        let fields = schema
            .get_columns()
            .iter()
            .map(|c| Field {
                name: c.name().to_string(),
                dtype: c.dtype().to_string(),
            })
            .collect();
        let index = Index {
            info: RecordingInfo {
                schema_version: 1,
                backend: "parquet".into(),
                recording_id: id.into(),
                stream: if slow { "slow" } else { "fast" }.into(),
                sample_period_us: period,
                position_basis: "recorded_samples".into(),
                fields,
                start: None,
                stop: None,
                complete: false,
            },
            segments: Vec::new(),
            metadata: None,
        };
        index.info.empty()?;
        // Reserve the handle exclusively; a failed append never overwrites a run.
        // Write the first index aside and publish it whole, so readers that
        // open the handle right after it appears never see a partial file.
        let tmp = path.with_extension("json.creating");
        let written = (|| -> Result<()> {
            let file = File::create(&tmp)?;
            serde_json::to_writer_pretty(&file, &index)?;
            file.sync_all()?;
            drop(file);
            publish_new(&tmp, &path)?;
            Ok(())
        })();
        let _ = fs::remove_file(&tmp);
        written?;
        Ok(Self {
            reader: ParquetReaderHandle {
                dir: dir.into(),
                path: path.clone(),
                index: Arc::new(Mutex::new(index)),
            },
            index_path: path,
        })
    }
}
impl RecordingBackend for ParquetBackend {
    fn append(&mut self, batch: SampleBatch) -> Result<()> {
        let mut next = self.reader.index.lock().unwrap().clone();
        ensure!(!next.info.complete, "recording is already complete");
        ensure!(batch.data.height() > 0, "cannot append an empty batch");
        ensure!(
            batch.data.schema() == next.info.empty()?.schema(),
            "recording schema mismatch"
        );
        ensure!(
            next.info.stop.is_none_or(|stop| stop == batch.start),
            "missing or out-of-order samples"
        );
        let stop = batch
            .start
            .checked_add(batch.data.height() as u64)
            .context("sample position overflow")?;
        let name = format!(
            "{}-part-{:08}.parquet",
            next.info.recording_id,
            next.segments.len()
        );
        let target = self.reader.dir.join(&name);
        ensure!(!target.exists(), "refusing to overwrite log segment");
        let tmp = target.with_extension("parquet.partial");
        let mut file = File::create_new(&tmp)?;
        // Row groups start at multiples of ROW_GROUP_ROWS from the recording
        // start, the slices in which finalization and `Recording` reads them.
        let offset = batch.start - next.info.start.unwrap_or(batch.start);
        let mut writer = ParquetWriter::new(&mut file).batched(batch.data.schema())?;
        let mut first = 0;
        let mut rows = ROW_GROUP_ROWS - (offset % ROW_GROUP_ROWS as u64) as usize;
        while first < batch.data.height() {
            // A single-chunk slice becomes exactly one row group.
            let mut group = batch.data.slice(first as i64, rows);
            group.as_single_chunk_par();
            writer.write_batch(&group)?;
            first += rows;
            rows = ROW_GROUP_ROWS;
        }
        writer.finish()?;
        drop(writer);
        file.sync_all()?;
        drop(file);
        fs::rename(tmp, target)?;
        next.info.start.get_or_insert(batch.start);
        next.info.stop = Some(stop);
        next.segments.push(Segment {
            start: batch.start,
            stop,
            file: name,
        });
        publish(&self.index_path, &next)?;
        *self.reader.index.lock().unwrap() = next;
        Ok(())
    }
    fn reader(&self) -> Arc<dyn RecordingReader> {
        Arc::new(self.reader.clone())
    }
    fn finish(&mut self) -> Result<()> {
        let mut next = self.reader.index.lock().unwrap().clone();
        next.info.complete = true;
        publish(&self.index_path, &next)?;
        *self.reader.index.lock().unwrap() = next;
        Ok(())
    }
    fn consolidate(&mut self, merged: &Path) -> Result<()> {
        let mut next = self.reader.index.lock().unwrap().clone();
        ensure!(
            next.info.complete,
            "only a finished recording can be consolidated"
        );
        let (Some(start), Some(stop)) = (next.info.start, next.info.stop) else {
            return Ok(()); // An empty recording has no segments to replace.
        };
        ensure!(
            merged.parent() == Some(self.reader.dir.as_path()),
            "merged recording must be in the recording directory"
        );
        let name = merged
            .file_name()
            .and_then(|name| name.to_str())
            .context("invalid merged recording name")?
            .to_owned();
        // Verify before the index refers to it: same rows, same schema.
        let mut reader = ParquetReader::new(File::open(merged)?);
        ensure!(
            reader.num_rows()? as u64 == stop - start,
            "merged recording row count mismatch"
        );
        let schema = reader.with_slice(Some((0, 0))).finish()?;
        ensure!(
            schema.schema() == next.info.empty()?.schema(),
            "merged recording schema mismatch"
        );
        let superseded: Vec<String> = next
            .segments
            .iter()
            .map(|segment| segment.file.clone())
            .filter(|file| *file != name)
            .collect();
        next.segments = vec![Segment {
            start,
            stop,
            file: name,
        }];
        publish(&self.index_path, &next)?;
        *self.reader.index.lock().unwrap() = next;
        // Windows refuses to delete a file that another handle (a reader, a
        // virus scanner or the indexer) has open, so retry briefly. A segment
        // that still cannot be removed is no longer referenced by the index.
        for file in superseded {
            remove_with_retry(&self.reader.dir.join(file));
        }
        Ok(())
    }
    fn set_metadata(&mut self, metadata: Value) -> Result<()> {
        let mut next = self.reader.index.lock().unwrap().clone();
        next.metadata = Some(metadata);
        publish(&self.index_path, &next)?;
        *self.reader.index.lock().unwrap() = next;
        Ok(())
    }
}
impl RecordingReader for ParquetReaderHandle {
    fn info(&self) -> Result<RecordingInfo> {
        Ok(self.index.lock().unwrap().info.clone())
    }
    fn read_projected_range(
        &self,
        start: u64,
        stop: u64,
        projection: Option<&[String]>,
    ) -> Result<DataFrame> {
        let index = self.index.lock().unwrap().clone();
        match self.read_index_range(&index, start, stop, projection) {
            // Finalization may have replaced the segments by one merged file
            // since this handle loaded its index: reload once and retry. Any IO
            // error qualifies: on Windows a segment pending deletion fails to
            // open with "access denied" rather than "not found".
            Err(error) if error.downcast_ref::<std::io::Error>().is_some() => {
                let current = load_index(&self.path)?;
                *self.index.lock().unwrap() = current.clone();
                self.read_index_range(&current, start, stop, projection)
            }
            result => result,
        }
    }
}

impl ParquetReaderHandle {
    fn read_index_range(
        &self,
        index: &Index,
        start: u64,
        stop: u64,
        projection: Option<&[String]>,
    ) -> Result<DataFrame> {
        let mut result = index.info.empty_projected(projection)?;
        let first = index.info.start.unwrap_or(0);
        let end = index.info.stop.unwrap_or(0);
        ensure!(
            start <= stop && start >= first && stop <= end,
            "range [{start}, {stop}) unavailable; persisted range [{first}, {end})"
        );
        let mut next = start;
        for segment in &index.segments {
            if segment.stop <= start {
                continue;
            }
            if segment.start >= stop {
                break;
            }
            let lo = start.max(segment.start);
            let hi = stop.min(segment.stop);
            ensure!(lo == next, "recording index contains a gap");
            let df = ParquetReader::new(File::open(self.dir.join(&segment.file))?)
                .with_columns(projection.map(|names| names.to_vec()))
                .with_slice(Some(((lo - segment.start) as usize, (hi - lo) as usize)))
                .finish()?;
            ensure!(
                df.height() as u64 == hi - lo && df.schema() == result.schema(),
                "recording segment is truncated or has an invalid schema"
            );
            result.vstack_mut(&df)?;
            next = hi;
        }
        ensure!(next == stop, "recording index contains a gap");
        result.as_single_chunk_par();
        Ok(result)
    }
}

fn remove_with_retry(path: &Path) {
    for attempt in 0..20 {
        match fs::remove_file(path) {
            Ok(()) => return,
            Err(error) if error.kind() == std::io::ErrorKind::NotFound => return,
            Err(_) if attempt < 19 => std::thread::sleep(std::time::Duration::from_millis(50)),
            Err(error) => eprintln!(
                "Could not remove merged segment {}: {error}",
                path.display()
            ),
        }
    }
}

/// Recording metadata stored with the index (settings, rows, completion, error).
pub fn read_metadata(path: &Path) -> Result<Option<Value>> {
    Ok(load_index(path)?.metadata)
}

/// Open a durable handle without a running acquisition service.
pub fn open(path: &Path) -> Result<Arc<dyn RecordingReader>> {
    let index = load_index(path)?;
    Ok(Arc::new(ParquetReaderHandle {
        dir: path
            .parent()
            .context("index has no parent directory")?
            .into(),
        path: path.into(),
        index: Arc::new(Mutex::new(index)),
    }))
}

fn load_index(path: &Path) -> Result<Index> {
    let index: Index = serde_json::from_slice(&fs::read(path)?)?;
    ensure!(
        index.info.schema_version == 1 && index.info.backend == "parquet",
        "unsupported recording backend or index version"
    );
    index.info.empty()?;
    let mut stop = index.info.start;
    for segment in &index.segments {
        ensure!(
            Path::new(&segment.file)
                .components()
                .all(|c| matches!(c, std::path::Component::Normal(_)))
                && !segment.file.contains(['/', '\\']),
            "invalid segment path"
        );
        ensure!(
            Some(segment.start) == stop && segment.stop > segment.start,
            "invalid recording range index"
        );
        stop = Some(segment.stop);
    }
    ensure!(stop == index.info.stop, "invalid recording end position");
    Ok(index)
}

#[cfg(test)]
mod tests {
    use super::*;
    struct Run(PathBuf);
    impl Run {
        fn new() -> Self {
            // Parallel tests can observe the same clock tick, even in nanoseconds.
            static NEXT_ID: std::sync::atomic::AtomicUsize = std::sync::atomic::AtomicUsize::new(0);
            let path = std::env::temp_dir().join(format!(
                "uz-backend-{}-{}-{}",
                std::process::id(),
                std::time::SystemTime::now()
                    .duration_since(std::time::UNIX_EPOCH)
                    .unwrap()
                    .as_nanos(),
                NEXT_ID.fetch_add(1, std::sync::atomic::Ordering::Relaxed)
            ));
            fs::create_dir(&path).unwrap();
            Self(path)
        }
    }
    impl Drop for Run {
        fn drop(&mut self) {
            let _ = fs::remove_dir_all(&self.0);
        }
    }
    fn batch(start: u64, rows: usize) -> Result<SampleBatch> {
        Ok(SampleBatch {
            start,
            data: DataFrame::new(vec![Column::new(
                "signal".into(),
                (start..start + rows as u64)
                    .map(|v| v as f32)
                    .collect::<Vec<_>>(),
            )])?,
        })
    }
    #[test]
    fn part_row_groups_align_to_the_recording_start() -> Result<()> {
        let run = Run::new();
        let mut backend = ParquetBackend::create(&run.0, "data", false, 100., &batch(0, 0)?.data)?;
        backend.append(batch(100, 70_000)?)?;
        backend.append(batch(70_100, 70_000)?)?;
        let groups = |part: &str| -> Result<Vec<usize>> {
            let mut reader = ParquetReader::new(File::open(run.0.join(part))?);
            Ok(reader
                .get_metadata()?
                .row_groups
                .iter()
                .map(|group| group.num_rows())
                .collect())
        };
        assert_eq!(groups("data-part-00000000.parquet")?, [65_536, 4_464]);
        // 70,000 rows in: the next boundary is 131,072 rows after the start.
        assert_eq!(groups("data-part-00000001.parquet")?, [61_072, 8_928]);
        assert!(
            backend
                .reader()
                .read_range(100, 140_100)?
                .equals_missing(&batch(100, 140_000)?.data)
        );
        Ok(())
    }
    #[test]
    fn backend_ranges_survive_finalize_and_reopen() -> Result<()> {
        let run = Run::new();
        let mut backend = ParquetBackend::create(&run.0, "data", false, 100., &batch(0, 0)?.data)?;
        let reader = backend.reader();
        backend.append(batch(100, 15)?)?;
        backend.append(batch(115, 15)?)?;
        let expected = batch(103, 24)?.data;
        assert!(reader.read_range(103, 127)?.equals_missing(&expected));
        assert!(backend.append(batch(131, 1)?).is_err());
        backend.finish()?;
        assert!(reader.info()?.complete);
        assert!(backend.append(batch(130, 1)?).is_err());
        drop(backend);
        assert!(
            open(&index_path(&run.0, "data"))?
                .read_range(103, 127)?
                .equals_missing(&expected)
        );
        assert!(reader.read_range(99, 100).is_err());
        assert!(reader.read_range(120, 131).is_err());
        assert!(reader.read_range(120, 119).is_err());
        Ok(())
    }
    #[test]
    fn publication_without_hard_links_still_refuses_to_replace() -> Result<()> {
        let run = Run::new();
        let (source, target) = (run.0.join("source"), run.0.join("target"));
        let unsupported = |_: &Path, _: &Path| -> std::io::Result<()> {
            Err(std::io::Error::new(
                std::io::ErrorKind::Unsupported,
                "no hard links",
            ))
        };
        fs::write(&source, "first")?;
        publish_new_with(&source, &target, unsupported)?;
        assert_eq!(fs::read_to_string(&target)?, "first");
        assert!(!source.exists());
        fs::write(&source, "second")?;
        let error = publish_new_with(&source, &target, unsupported).unwrap_err();
        assert_eq!(error.kind(), std::io::ErrorKind::AlreadyExists);
        assert_eq!(fs::read_to_string(&target)?, "first");
        Ok(())
    }
    #[test]
    fn creation_publishes_a_complete_index_and_never_replaces_one() -> Result<()> {
        let run = Run::new();
        let mut backend = ParquetBackend::create(&run.0, "data", false, 100., &batch(0, 0)?.data)?;
        let path = index_path(&run.0, "data");
        assert!(!path.with_extension("json.creating").exists());
        backend.append(batch(100, 15)?)?;
        let published = fs::read(&path)?;
        assert!(ParquetBackend::create(&run.0, "data", false, 100., &batch(0, 0)?.data).is_err());
        assert_eq!(fs::read(&path)?, published);
        assert!(!path.with_extension("json.creating").exists());
        Ok(())
    }
    #[test]
    fn failed_publication_does_not_advance_committed_position() -> Result<()> {
        let run = Run::new();
        let mut backend = ParquetBackend::create(&run.0, "data", false, 100., &batch(0, 0)?.data)?;
        backend.append(batch(100, 15)?)?;
        fs::create_dir(index_path(&run.0, "data").with_extension("json.partial"))?;
        assert!(backend.append(batch(115, 15)?).is_err());
        assert_eq!(backend.reader().info()?.stop, Some(115));
        assert_eq!(open(&index_path(&run.0, "data"))?.info()?.stop, Some(115));
        assert!(
            backend
                .reader()
                .read_range(100, 115)?
                .equals_missing(&batch(100, 15)?.data)
        );
        Ok(())
    }
    #[test]
    fn empty_recording_and_invalid_handles() -> Result<()> {
        let run = Run::new();
        let mut backend = ParquetBackend::create(&run.0, "empty", false, 100., &batch(0, 0)?.data)?;
        backend.finish()?;
        let path = index_path(&run.0, "empty");
        assert_eq!(open(&path)?.read_range(0, 0)?.height(), 0);
        let mut index: Index = serde_json::from_slice(&fs::read(&path)?)?;
        index.info.backend = "unknown".into();
        fs::write(&path, serde_json::to_vec(&index)?)?;
        assert!(open(&path).is_err());
        assert!(
            ParquetBackend::create(&run.0, "../outside", false, 100., &batch(0, 0)?.data).is_err()
        );
        Ok(())
    }

    #[test]
    fn projected_ranges_preserve_order_schema_and_segment_boundaries() -> Result<()> {
        let run = Run::new();
        let make_batch = |start: u64, rows: usize| -> Result<SampleBatch> {
            Ok(SampleBatch {
                start,
                data: DataFrame::new(vec![
                    Column::new(
                        "time".into(),
                        (start..start + rows as u64)
                            .map(|i| i as f64)
                            .collect::<Vec<_>>(),
                    ),
                    Column::new("status".into(), vec![u32::MAX; rows]),
                    Column::new(
                        "first".into(),
                        (start..start + rows as u64)
                            .map(|i| i as f32)
                            .collect::<Vec<_>>(),
                    ),
                    Column::new("second".into(), vec![f32::NAN; rows]),
                ])?,
            })
        };
        let mut backend =
            ParquetBackend::create(&run.0, "data", false, 100., &make_batch(0, 0)?.data)?;
        backend.append(make_batch(100, 15)?)?;
        backend.append(make_batch(115, 15)?)?;
        let reader = backend.reader();
        for channels in [
            vec!["second".into(), "first".into(), "second".into()],
            Vec::new(),
        ] {
            let names = query_projection(&reader.info()?.fields, Some(&channels))?.unwrap();
            let projected = reader.read_projected_range(103, 127, Some(&names))?;
            let expected = reader.read_range(103, 127)?.select(names.clone())?;
            assert!(projected.equals_missing(&expected));
            assert_eq!(
                reader
                    .read_projected_range(115, 115, Some(&names))?
                    .schema(),
                projected.schema()
            );
            backend.finish()?;
            assert!(
                open(&index_path(&run.0, "data"))?
                    .read_projected_range(103, 127, Some(&names))?
                    .equals_missing(&expected)
            );
        }
        assert!(query_projection(&reader.info()?.fields, Some(&["missing".into()])).is_err());
        assert!(
            reader
                .read_projected_range(100, 100, Some(&["missing".into()]))
                .is_err()
        );
        Ok(())
    }

    #[test]
    fn projection_skips_unrequested_column_pages() -> Result<()> {
        use std::io::{Seek, SeekFrom, Write};
        let run = Run::new();
        let mut data = batch(0, 10000)?.data;
        data.with_column(Column::new(
            "ignored".into(),
            (0..10000u32)
                .map(|i| i.wrapping_mul(1664525).wrapping_add(1013904223) as f32)
                .collect::<Vec<_>>(),
        ))?;
        let mut backend = ParquetBackend::create(&run.0, "data", false, 100., &data.clear())?;
        backend.append(SampleBatch { start: 0, data })?;
        let path = run.0.join("data-part-00000000.parquet");
        let mut parquet = ParquetReader::new(File::open(&path)?);
        let metadata = parquet.get_metadata()?.clone();
        let bytes = metadata.row_groups[0].parquet_columns()[1].byte_range();
        drop(parquet);
        // Leave the page header intact and damage only the excluded column body.
        assert!(bytes.end - bytes.start > 128);
        let mut file = std::fs::OpenOptions::new().write(true).open(path)?;
        file.seek(SeekFrom::Start(bytes.start + 64))?;
        file.write_all(&vec![0xff; (bytes.end - bytes.start - 64) as usize])?;
        file.sync_all()?;
        drop(file);
        let reader = backend.reader();
        let projected = reader.read_projected_range(10, 30, Some(&["signal".into()]))?;
        assert!(projected.equals_missing(&batch(10, 20)?.data));
        assert!(
            reader.read_range(10, 30).is_err(),
            "full decoding must encounter the damaged column"
        );
        Ok(())
    }
}
