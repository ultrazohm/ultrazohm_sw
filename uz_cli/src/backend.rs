//! Recording storage contract. Sample positions are acquisition indices, [start, stop).
//! Backends receive typed columns, never device frames or GUI requests.
use anyhow::{Context, Result, ensure};
use polars::prelude::*;
use serde::{Deserialize, Serialize};
use std::{
    fs::{self, File},
    path::{Path, PathBuf},
    sync::{Arc, Mutex},
};

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
    pub fields: Vec<Field>,
    pub start: Option<u64>,
    pub stop: Option<u64>,
    pub complete: bool,
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
}

#[derive(Clone)]
pub struct ParquetReaderHandle {
    dir: PathBuf,
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
    fs::rename(tmp, path)?;
    Ok(())
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
                fields,
                start: None,
                stop: None,
                complete: false,
            },
            segments: Vec::new(),
        };
        index.info.empty()?;
        // Reserve the handle exclusively; a failed append never overwrites a run.
        let file = File::create_new(&path)?;
        serde_json::to_writer_pretty(&file, &index)?;
        file.sync_all()?;
        Ok(Self {
            reader: ParquetReaderHandle {
                dir: dir.into(),
                index: Arc::new(Mutex::new(index)),
            },
            index_path: path,
        })
    }
}
impl RecordingBackend for ParquetBackend {
    fn append(&mut self, mut batch: SampleBatch) -> Result<()> {
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
        ParquetWriter::new(&mut file).finish(&mut batch.data)?;
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

/// Open a durable handle without a running acquisition service.
pub fn open(path: &Path) -> Result<Arc<dyn RecordingReader>> {
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
    Ok(Arc::new(ParquetReaderHandle {
        dir: path
            .parent()
            .context("index has no parent directory")?
            .into(),
        index: Arc::new(Mutex::new(index)),
    }))
}

#[cfg(test)]
mod tests {
    use super::*;
    struct Run(PathBuf);
    impl Run {
        fn new() -> Self {
            let path = std::env::temp_dir().join(format!(
                "uz-backend-{}-{}",
                std::process::id(),
                std::time::SystemTime::now()
                    .duration_since(std::time::UNIX_EPOCH)
                    .unwrap()
                    .as_nanos()
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
