//! Finalized Parquet segments during acquisition; separate fast/slow Parquet and optional CSV at close.
use crate::{
    backend::{self, BackendKind, RecordingBackend, RecordingReader, SampleBatch},
    profile::Profile,
    protocol::Frame,
};
use anyhow::{Context, Result, ensure};
use polars::prelude::*;
use serde::{Deserialize, Serialize};
use std::sync::Arc;
use std::{
    fs::{self, File},
    path::{Path, PathBuf},
};

#[derive(Clone, Copy, Debug, Serialize, Deserialize, clap::ValueEnum)]
#[serde(rename_all = "snake_case")]
pub enum Format {
    /// Record Parquet, then export CSV; retain both final files.
    Csv,
    /// Record Parquet and retain a final Parquet file for each stream.
    Parquet,
    /// Same behavior as csv (retained for compatibility).
    Both,
}

pub struct LogWriter {
    pub segment_rows: usize,
    dir: PathBuf,
    profile: Profile,
    format: Format,
    batch: Vec<(u64, Arc<Frame>)>,
    backend: Box<dyn RecordingBackend>,
    fast_columns: Vec<(usize, String)>,
    slow_names: Vec<String>,
    stem: String,
    slow: bool,
    first_index: Option<u64>,
    next_index: Option<u64>,
    rows: usize,
    part: u64,
    written_rows: usize,
}
impl LogWriter {
    pub fn new(
        dir: PathBuf,
        profile: Profile,
        format: Format,
        stem: String,
        slow: bool,
        selections: &serde_json::Value,
    ) -> Result<Self> {
        Self::new_for_backend(
            dir,
            profile,
            format,
            stem,
            slow,
            selections,
            BackendKind::Parquet,
        )
    }
    pub fn new_for_backend(
        dir: PathBuf,
        profile: Profile,
        format: Format,
        stem: String,
        slow: bool,
        selections: &serde_json::Value,
        kind: BackendKind,
    ) -> Result<Self> {
        Self::new_with_factory(
            dir,
            profile,
            format,
            stem,
            slow,
            selections,
            move |dir, id, slow, period, schema| {
                backend::create(kind, dir, id, slow, period, schema)
            },
        )
    }
    /// Inject a storage implementation without changing acquisition or query code.
    pub fn new_with_factory(
        dir: PathBuf,
        profile: Profile,
        format: Format,
        stem: String,
        slow: bool,
        selections: &serde_json::Value,
        factory: impl FnOnce(&Path, &str, bool, f64, &DataFrame) -> Result<Box<dyn RecordingBackend>>,
    ) -> Result<Self> {
        let mut fast_columns = Vec::new();
        let mut seen = std::collections::BTreeSet::new();
        for channel in 1..=profile.channels {
            if let Some(requested) = selections[channel.to_string()].as_str() {
                let (name, id) = profile
                    .observables
                    .get_key_value(requested)
                    .or_else(|| {
                        profile
                            .observables
                            .get_key_value(&format!("JSO_{requested}"))
                    })
                    .with_context(|| format!("unknown selected observable {requested}"))?;
                if seen.insert(*id) {
                    ensure!(
                        name != "time" && name != "status",
                        "observable name {name} conflicts with a reserved log column"
                    );
                    fast_columns.push((channel - 1, name.clone()));
                }
            }
        }
        ensure!(
            slow || !fast_columns.is_empty(),
            "select at least one observable before starting fast logging"
        );
        let mut slow_names = vec![String::new(); profile.slow_signals.len()];
        for (name, &id) in &profile.slow_signals {
            ensure!(
                !slow || (name != "time" && name != "status"),
                "slow observable name {name} conflicts with a reserved log column"
            );
            slow_names[id as usize] = name.clone();
        }
        ensure!(dir.is_dir(), "recording directory does not exist");
        ensure!(
            !dir.join(format!("{stem}.parquet")).exists(),
            "recording already exists"
        );
        let empty = frames_dataframe(&[], 0, &profile, &fast_columns, &slow_names, slow)?;
        let backend = factory(&dir, &stem, slow, profile.sample_period_us, &empty)?;
        Ok(Self {
            backend,
            segment_rows: crate::live::DataOptions::default().segment_rows,
            dir,
            profile,
            format,
            batch: Vec::new(),
            fast_columns,
            slow_names,
            stem,
            slow,
            first_index: None,
            next_index: None,
            rows: 0,
            part: 0,
            written_rows: 0,
        })
    }
    /// Return whether this push committed a segment, to reset the flush timer.
    pub fn push(&mut self, index: u64, frame: impl Into<Arc<Frame>>) -> Result<bool> {
        let frame = frame.into();
        ensure!(
            self.next_index.is_none_or(|next| next == index),
            "missing or out-of-order samples"
        );
        self.first_index.get_or_insert(index);
        self.next_index = Some(index + frame.slow_raw.len() as u64);
        self.rows += frame.slow_raw.len();
        self.batch.push((index, frame));
        if self.rows >= self.segment_rows {
            self.flush()?;
            return Ok(true);
        }
        Ok(false)
    }
    pub fn reader(&self) -> Arc<dyn RecordingReader> {
        self.backend.reader()
    }
    fn dataframe(&self) -> Result<DataFrame> {
        frames_dataframe(
            &self.batch,
            self.rows,
            &self.profile,
            &self.fast_columns,
            &self.slow_names,
            self.slow,
        )
    }
    /// Commit a complete, independently readable Parquet segment for every format.
    pub fn flush(&mut self) -> Result<()> {
        if self.rows == 0 {
            return Ok(());
        }
        self.backend.append(SampleBatch {
            start: self.first_index.unwrap() + self.written_rows as u64,
            data: self.dataframe()?,
        })?;
        self.part += 1;
        self.written_rows += self.rows;
        self.rows = 0;
        self.batch.clear();
        Ok(())
    }

    #[cfg(test)]
    fn segment(&self, part: u64) -> PathBuf {
        self.dir
            .join(format!("{}-part-{part:08}.parquet", self.stem))
    }

    /// Finish the canonical recording, then create the requested compatibility exports.
    pub fn finish(&mut self) -> Result<()> {
        self.finish_recording()?;
        self.export()
    }

    /// Storage completion is independent of any optional local export.
    pub fn finish_recording(&mut self) -> Result<()> {
        self.flush()?;
        self.backend.finish()
    }

    pub fn export(&self) -> Result<()> {
        self.merge()?;
        if !matches!(self.format, Format::Parquet) {
            let stem = &self.stem;
            export_csv(
                &self.dir.join(format!("{stem}.parquet")),
                &self.dir.join(format!("{stem}.csv")),
            )
            .context("CSV export failed; final Parquet and segments retained")?;
        }
        Ok(())
    }

    /// Expand received updates while retaining the last value across segment boundaries.
    /// None means this observable has not yet been sampled in this recording.
    fn wide_slow(&self, df: &DataFrame, last: &mut [Option<f32>]) -> Result<DataFrame> {
        let ids = df.column("slow_id")?.u32()?;
        let values = df.column("slow_value")?.f32()?;
        ensure!(
            ids.null_count() == 0
                && values.null_count() == 0
                && ids.into_no_null_iter().all(|id| (id as usize) < last.len()),
            "invalid slow update in segment"
        );
        let mut columns = vec![df.column("time")?.clone(), df.column("status")?.clone()];
        for (id, name) in self.slow_names.iter().enumerate() {
            let mut output = Vec::with_capacity(df.height());
            for (received_id, value) in ids.into_no_null_iter().zip(values.into_no_null_iter()) {
                if received_id as usize == id {
                    last[id] = Some(value);
                }
                output.push(last[id]);
            }
            columns.push(Column::new(name.clone().into(), output));
        }
        Ok(DataFrame::new(columns)?.drop_nulls::<String>(None)?)
    }

    fn merge(&self) -> Result<()> {
        let stem = &self.stem;
        let target = self.dir.join(format!("{stem}.parquet"));
        ensure!(!target.exists(), "refusing to overwrite final Parquet");
        let tmp = self.dir.join(format!("{stem}.parquet.partial"));
        let mut file = File::create_new(&tmp)?;
        let empty = self.dataframe()?;
        let mut last = vec![None; self.slow_names.len()];
        let final_empty = if self.slow {
            self.wide_slow(&empty, &mut last)?
        } else {
            empty.clone()
        };
        let mut writer = ParquetWriter::new(&mut file).batched(final_empty.schema())?;
        let mut merged_rows = 0usize;
        let mut output_rows = 0usize;
        for offset in (0..self.written_rows).step_by(65536) {
            let first = self.first_index.unwrap_or(0) + offset as u64;
            let stop =
                self.first_index.unwrap_or(0) + (offset + 65536).min(self.written_rows) as u64;
            let df = self.backend.reader().read_range(first, stop)?;
            ensure!(df.schema() == empty.schema(), "recording schema mismatch");
            let times = df.column("time")?.f64()?;
            let first = self.first_index.unwrap_or(0) + merged_rows as u64;
            ensure!(
                times.null_count() == 0
                    && times
                        .into_no_null_iter()
                        .eq((first..first + df.height() as u64)
                            .map(|i| i as f64 * self.profile.sample_period_us * 1e-6)),
                "recording has missing or out-of-order samples"
            );
            merged_rows += df.height();
            let output = if self.slow {
                self.wide_slow(&df, &mut last)?
            } else {
                df
            };
            output_rows += output.height();
            writer.write_batch(&output)?;
        }
        ensure!(
            merged_rows == self.written_rows,
            "merged row count mismatch"
        );
        writer.finish()?;
        drop(writer);
        file.sync_all()?;
        drop(file);
        // Validate the final footer and schema before publication or source deletion.
        {
            let mut check = ParquetReader::new(File::open(&tmp)?);
            ensure!(
                check.num_rows()? == output_rows,
                "final Parquet row count mismatch"
            );
            let schema = check.with_slice(Some((0, 0))).finish()?;
            ensure!(
                schema.schema() == final_empty.schema(),
                "final Parquet schema mismatch"
            );
        }
        fs::rename(tmp, &target)?;
        Ok(())
    }
}

pub(crate) fn frames_dataframe(
    frames: &[(u64, Arc<Frame>)],
    rows: usize,
    profile: &Profile,
    fast_columns: &[(usize, String)],
    slow_names: &[String],
    slow: bool,
) -> Result<DataFrame> {
    let mut time = Vec::with_capacity(rows);
    let mut status = Vec::with_capacity(rows);
    let mut slow_id = Vec::with_capacity(rows);
    let mut slow_name = Vec::with_capacity(rows);
    let mut slow_raw = Vec::with_capacity(rows);
    let mut slow_value = Vec::with_capacity(rows);
    let mut channels: Vec<Vec<f32>> = (0..20).map(|_| Vec::with_capacity(rows)).collect();
    for (first, f) in frames {
        for i in 0..f.slow_raw.len() {
            time.push((first + i as u64) as f64 * profile.sample_period_us * 1e-6);
            status.push(f.status);
            if slow {
                slow_id.push(f.slow_ids[i]);
                slow_name.push(slow_names[f.slow_ids[i] as usize].as_str());
                slow_raw.push(f.slow_raw[i]);
                slow_value.push(f32::from_bits(f.slow_raw[i]));
            } else {
                for (dest, source) in channels.iter_mut().zip(&f.channels) {
                    dest.push(source[i]);
                }
            }
        }
    }
    let mut cols = vec![
        Column::new("time".into(), time),
        Column::new("status".into(), status),
    ];
    if slow {
        cols.extend([
            Column::new("observable".into(), slow_name),
            Column::new("slow_id".into(), slow_id),
            Column::new("slow_raw".into(), slow_raw),
            Column::new("slow_value".into(), slow_value),
        ]);
    } else {
        for (index, name) in fast_columns {
            cols.push(Column::new(
                name.clone().into(),
                std::mem::take(&mut channels[*index]),
            ));
        }
    }
    Ok(DataFrame::new(cols)?)
}

/// Convert the completed Parquet file in bounded slices; no CSV is written at ingest.
fn export_csv(parquet: &Path, target: &Path) -> Result<()> {
    ensure!(!target.exists(), "refusing to overwrite final CSV");
    let tmp = target.with_extension("csv.partial");
    let mut output = File::create_new(&tmp)?;
    let mut source = ParquetReader::new(File::open(parquet)?);
    let rows = source.num_rows()?;
    let metadata = source.get_metadata()?.clone();
    drop(source);
    // Include an empty slice for a header-only recording. Metadata is reused.
    for offset in (0..rows.max(1)).step_by(65536) {
        let mut reader = ParquetReader::new(File::open(parquet)?)
            .with_slice(Some((offset, (rows - offset).min(65536))))
            .read_parallel(ParallelStrategy::None);
        reader.set_metadata(metadata.clone());
        let mut df = reader.finish()?;
        ensure!(
            df.height() == (rows - offset).min(65536),
            "CSV source slice truncated"
        );
        CsvWriter::new(&mut output)
            .include_header(offset == 0)
            .finish(&mut df)?;
    }
    output.sync_all()?;
    drop(output);
    fs::rename(tmp, target)?;
    Ok(())
}

#[cfg(test)]
mod tests {
    use super::*;
    struct Run(PathBuf);
    impl Run {
        fn new() -> Self {
            let run = Self(std::env::temp_dir().join(format!(
                    "uz-segments-{}-{}",
                    std::process::id(),
                    std::time::SystemTime::now()
                        .duration_since(std::time::UNIX_EPOCH)
                        .unwrap()
                        .as_nanos()
                )));
            fs::create_dir(&run.0).unwrap();
            run
        }
    }
    impl Drop for Run {
        fn drop(&mut self) {
            let _ = fs::remove_dir_all(&self.0);
        }
    }
    fn frame(start: usize, count: usize) -> Frame {
        Frame {
            status: 7,
            slow_raw: vec![2.5f32.to_bits(); count],
            slow_ids: (start..start + count).map(|i| (i % 17) as u32).collect(),
            channels: vec![(start..start + count).map(|i| i as f32).collect(); 20],
        }
    }
    fn read(path: PathBuf) -> Result<DataFrame> {
        Ok(ParquetReader::new(File::open(path)?).finish()?)
    }

    #[test]
    fn default_segment_limit_preserves_full_frames_and_final_tail() -> Result<()> {
        let run = Run::new();
        let profile = Profile::load(None)?;
        let mut log = LogWriter::new(
            run.0.clone(),
            profile.clone(),
            Format::Parquet,
            "data".into(),
            false,
            &serde_json::to_value(&profile.initial_channels)?,
        )?;
        let frame_rows = profile.samples_per_packet;
        let segment_rows = log.segment_rows.div_ceil(frame_rows) * frame_rows;
        for first in (0..segment_rows - frame_rows).step_by(frame_rows) {
            assert!(!log.push(first as u64, frame(first, frame_rows))?);
        }
        assert!(!log.segment(0).exists());
        let started = std::time::Instant::now();
        assert!(log.push(
            (segment_rows - frame_rows) as u64,
            frame(segment_rows - frame_rows, frame_rows),
        )?);
        eprintln!("default-size segment flush: {:?}", started.elapsed());
        assert_eq!(read(log.segment(0))?.height(), segment_rows);
        assert!(!log.push(segment_rows as u64, frame(segment_rows, frame_rows))?);
        log.finish()?;
        let df = read(run.0.join("data.parquet"))?;
        assert_eq!(df.height(), segment_rows + frame_rows);
        assert!(
            df.column("time")?
                .f64()?
                .into_no_null_iter()
                .eq((0..df.height()).map(|i| i as f64 * profile.sample_period_us * 1e-6))
        );
        Ok(())
    }

    #[test]
    fn segments_merge_and_csv_is_exported_from_final_parquet() -> Result<()> {
        for format in [Format::Parquet, Format::Csv, Format::Both] {
            let run = Run::new();
            let mut log = LogWriter::new(
                run.0.clone(),
                Profile::load(None)?,
                format,
                "data".into(),
                false,
                &serde_json::to_value(Profile::load(None)?.initial_channels)?,
            )?;
            let mut slow_log = LogWriter::new(
                run.0.clone(),
                Profile::load(None)?,
                format,
                "data_slow_data".into(),
                true,
                &serde_json::to_value(Profile::load(None)?.initial_channels)?,
            )?;
            log.segment_rows = 4096;
            slow_log.segment_rows = 4096;
            // Cross the CSV export slice boundary as well as recording batch boundaries.
            for i in 0..17 {
                log.push(i * 4096, frame(i as usize * 4096, 4096))?;
                slow_log.push(i * 4096, frame(i as usize * 4096, 4096))?;
            }
            log.push(17 * 4096, frame(17 * 4096, 3))?;
            slow_log.push(17 * 4096, frame(17 * 4096, 3))?; // Final partial batch.
            assert!(!run.0.join("data.parquet").exists());
            assert!(!run.0.join("data.csv").exists());
            assert_eq!(read(log.segment(0))?.height(), 4096);
            log.finish()?;
            slow_log.finish()?;
            let df = read(run.0.join("data.parquet"))?;
            assert_eq!(df.height(), 17 * 4096 + 3);
            assert!(
                df.column("time")?
                    .f64()?
                    .into_no_null_iter()
                    .eq((0..df.height()).map(|i| i as f64 * 100.0 * 1e-6))
            );
            assert!(
                df.column("JSO_Theta_el")?
                    .f32()?
                    .into_no_null_iter()
                    .eq((0..df.height()).map(|i| i as f32))
            );
            let slow = read(run.0.join("data_slow_data.parquet"))?;
            assert_eq!(df.width(), 22);
            assert_eq!(slow.shape(), (df.height() - 16, 19));
            assert!(df.column("slow_id").is_err());
            assert!(slow.column("ch_1").is_err());
            for column in ["time", "status"] {
                assert_eq!(
                    &df.column(column)?.slice(16, slow.height()),
                    slow.column(column)?
                );
            }
            assert!(slow.column("slow_id").is_err());
            assert!(
                slow.get_columns()
                    .iter()
                    .all(|column| column.null_count() == 0)
            );
            assert!(
                slow.column("JSSD_FLOAT_SecondsSinceSystemStart")?
                    .f32()?
                    .into_no_null_iter()
                    .all(|v| v == 2.5)
            );
            let csv_enabled = !matches!(format, Format::Parquet);
            assert!(backend::index_path(&run.0, "data").is_file());
            assert!(backend::index_path(&run.0, "data_slow_data").is_file());
            assert_eq!(
                backend::open(&backend::index_path(&run.0, "data"))?
                    .read_range(0, df.height() as u64)?
                    .height(),
                df.height()
            );
            if csv_enabled {
                let csv = fs::read_to_string(run.0.join("data.csv"))?;
                assert_eq!(csv.lines().count(), df.height() + 1);
                assert_eq!(csv.matches("time,").count(), 1);
                let rows: Vec<_> = csv.lines().skip(1).collect();
                assert_eq!(
                    rows[65536].split(',').next().unwrap().parse::<f64>()?,
                    65536.0 * 100.0 * 1e-6
                );
                assert_eq!(
                    rows.last()
                        .unwrap()
                        .split(',')
                        .next()
                        .unwrap()
                        .parse::<f64>()?,
                    69634.0 * 100.0 * 1e-6
                );
                let slow_csv = fs::read_to_string(run.0.join("data_slow_data.csv"))?;
                assert_eq!(slow_csv.lines().count(), slow.height() + 1);
                let fields: Vec<_> = slow_csv.lines().last().unwrap().split(',').collect();
                assert_eq!(fields.len(), 19);
                assert_eq!(fields[2], "2.5");
                assert_eq!(fields[3], "2.5");
            }
        }
        Ok(())
    }

    #[test]
    fn slow_forward_fill_crosses_segments_and_resets_for_each_recording() -> Result<()> {
        let run = Run::new();
        let mut profile = Profile::load(None)?;
        profile.slow_signals = [
            ("zero".into(), 0),
            ("voltage".into(), 1),
            ("current".into(), 2),
        ]
        .into();
        for stem in ["data_slow_data", "data_0002_slow_data"] {
            let mut log = LogWriter::new(
                run.0.clone(),
                profile.clone(),
                Format::Both,
                stem.into(),
                true,
                &serde_json::json!({}),
            )?;
            let mut first = frame(0, 2);
            first.slow_ids = vec![1, 2];
            first.slow_raw = vec![12.0f32.to_bits(), 3.0f32.to_bits()];
            log.push(150, first)?;
            log.flush()?;
            let segment = read(log.segment(0))?;
            assert_eq!(segment.width(), 6); // Ingest remains raw, not wide or filled.
            assert_eq!(segment.column("slow_id")?.u32()?.get(0), Some(1));
            let mut second = frame(0, 3);
            second.status = 9;
            second.slow_ids = vec![0, 1, 2];
            second.slow_raw = vec![0.0f32.to_bits(), 14.0f32.to_bits(), f32::NAN.to_bits()];
            log.push(152, second)?;
            log.finish()?;
            let df = read(run.0.join(format!("{stem}.parquet")))?;
            assert_eq!(
                df.column("voltage")?.f32()?.into_iter().collect::<Vec<_>>(),
                vec![Some(12.0), Some(14.0), Some(14.0)]
            );
            let current = df.column("current")?.f32()?;
            assert_eq!(current.get(0), Some(3.0));
            assert_eq!(current.get(1), Some(3.0));
            assert!(current.get(2).unwrap().is_nan()); // Real NaN updates are not missing updates.
            assert_eq!(
                df.column("zero")?.f32()?.into_iter().collect::<Vec<_>>(),
                vec![Some(0.0), Some(0.0), Some(0.0)]
            );
            assert_eq!(
                df.column("status")?
                    .u32()?
                    .into_no_null_iter()
                    .collect::<Vec<_>>(),
                vec![9, 9, 9]
            );
            assert!(
                df.column("time")?
                    .f64()?
                    .into_no_null_iter()
                    .eq((152..155).map(|i| i as f64 * 100.0 * 1e-6))
            );
            let csv = fs::read_to_string(run.0.join(format!("{stem}.csv")))?;
            let lines: Vec<_> = csv.lines().collect();
            assert_eq!(lines[0], "time,status,zero,voltage,current");
            assert_eq!(lines.len(), 4);
            assert!(lines[1].ends_with(",9,0.0,12.0,3.0"));
        }
        let mut incomplete = LogWriter::new(
            run.0.clone(),
            profile.clone(),
            Format::Both,
            "incomplete".into(),
            true,
            &serde_json::json!({}),
        )?;
        incomplete.push(0, frame(0, 1))?;
        incomplete.finish()?;
        assert_eq!(read(run.0.join("incomplete.parquet"))?.shape(), (0, 5));
        assert_eq!(
            fs::read_to_string(run.0.join("incomplete.csv"))?
                .lines()
                .count(),
            1
        );
        // A custom mapping must not overwrite the shared time/status columns.
        profile.slow_signals = [("time".into(), 0)].into();
        assert!(
            LogWriter::new(
                run.0.clone(),
                profile,
                Format::Both,
                "invalid".into(),
                true,
                &serde_json::json!({})
            )
            .is_err()
        );
        Ok(())
    }

    #[test]
    fn empty_recording_has_typed_parquet_and_csv_header() -> Result<()> {
        let run = Run::new();
        LogWriter::new(
            run.0.clone(),
            Profile::load(None)?,
            Format::Csv,
            "data".into(),
            false,
            &serde_json::to_value(Profile::load(None)?.initial_channels)?,
        )?
        .finish()?;
        LogWriter::new(
            run.0.clone(),
            Profile::load(None)?,
            Format::Csv,
            "data_slow_data".into(),
            true,
            &serde_json::to_value(Profile::load(None)?.initial_channels)?,
        )?
        .finish()?;
        let df = read(run.0.join("data.parquet"))?;
        assert_eq!(df.shape(), (0, 22));
        assert_eq!(read(run.0.join("data_slow_data.parquet"))?.shape(), (0, 19));
        assert_eq!(
            fs::read_to_string(run.0.join("data_slow_data.csv"))?
                .lines()
                .count(),
            1
        );
        assert_eq!(df.column("time")?.dtype(), &DataType::Float64);
        assert_eq!(
            fs::read_to_string(run.0.join("data.csv"))?.lines().count(),
            1
        );
        Ok(())
    }

    #[test]
    fn failed_merge_or_export_preserves_sources() -> Result<()> {
        for blocked in [
            "data.parquet.partial",
            "data_slow_data.parquet.partial",
            "data.csv.partial",
            "data_slow_data.csv.partial",
        ] {
            let run = Run::new();
            let slow = blocked.contains("slow_data");
            let stem = if slow { "data_slow_data" } else { "data" };
            let mut log = LogWriter::new(
                run.0.clone(),
                Profile::load(None)?,
                Format::Csv,
                stem.into(),
                slow,
                &serde_json::to_value(Profile::load(None)?.initial_channels)?,
            )?;
            log.push(150, frame(0, 15))?;
            log.flush()?;
            fs::create_dir(run.0.join(blocked))?;
            assert!(log.finish().is_err());
            // Optional export failure does not invalidate committed measurement data.
            let canonical = backend::open(&backend::index_path(&run.0, stem))?;
            assert!(canonical.info()?.complete);
            assert_eq!(canonical.read_range(150, 165)?.height(), 15);
            assert_eq!(
                read(run.0.join(format!("{stem}-part-00000000.parquet")))?.height(),
                15
            );
            assert_eq!(
                run.0.join(format!("{stem}.parquet")).exists(),
                blocked.ends_with("csv.partial")
            );
            assert!(!run.0.join(format!("{stem}.csv")).exists());
        }
        Ok(())
    }

    #[test]
    fn unfinished_recording_keeps_readable_segments() -> Result<()> {
        let run = Run::new();
        let mut log = LogWriter::new(
            run.0.clone(),
            Profile::load(None)?,
            Format::Csv,
            "data".into(),
            false,
            &serde_json::to_value(Profile::load(None)?.initial_channels)?,
        )?;
        log.push(0, frame(0, 15))?;
        log.flush()?;
        drop(log);
        assert_eq!(read(run.0.join("data-part-00000000.parquet"))?.height(), 15);
        assert!(!run.0.join("data.parquet").exists());
        assert!(!run.0.join("data.csv").exists());
        Ok(())
    }

    // A second backend used only in tests proves the recording/export code uses
    // the storage contract rather than reaching into Parquet segment files.
    #[derive(Clone)]
    struct MemoryBackend(Arc<std::sync::Mutex<(backend::RecordingInfo, DataFrame)>>);
    impl RecordingReader for MemoryBackend {
        fn info(&self) -> Result<backend::RecordingInfo> {
            Ok(self.0.lock().unwrap().0.clone())
        }
        fn read_projected_range(
            &self,
            start: u64,
            stop: u64,
            projection: Option<&[String]>,
        ) -> Result<DataFrame> {
            let state = self.0.lock().unwrap();
            let first = state.0.start.unwrap_or(0);
            ensure!(
                start >= first && start <= stop && stop <= state.0.stop.unwrap_or(0),
                "unavailable memory range"
            );
            let data = state
                .1
                .slice((start - first) as i64, (stop - start) as usize);
            Ok(match projection {
                Some(names) => data.select(names.to_vec())?,
                None => data,
            })
        }
    }
    impl RecordingBackend for MemoryBackend {
        fn append(&mut self, batch: SampleBatch) -> Result<()> {
            let mut state = self.0.lock().unwrap();
            ensure!(
                !state.0.complete && state.0.stop.is_none_or(|end| end == batch.start),
                "invalid append"
            );
            state.0.start.get_or_insert(batch.start);
            state.0.stop = Some(batch.start + batch.data.height() as u64);
            state.1.vstack_mut(&batch.data)?;
            Ok(())
        }
        fn reader(&self) -> Arc<dyn RecordingReader> {
            Arc::new(self.clone())
        }
        fn finish(&mut self) -> Result<()> {
            self.0.lock().unwrap().0.complete = true;
            Ok(())
        }
    }
    #[test]
    fn alternate_backend_uses_same_recording_and_export_pipeline() -> Result<()> {
        let run = Run::new();
        let profile = Profile::load(None)?;
        let mut log = LogWriter::new_with_factory(
            run.0.clone(),
            profile.clone(),
            Format::Parquet,
            "custom".into(),
            false,
            &serde_json::to_value(&profile.initial_channels)?,
            |_dir, id, _slow, period, schema| {
                Ok(Box::new(MemoryBackend(Arc::new(std::sync::Mutex::new((
                    backend::RecordingInfo {
                        schema_version: 1,
                        backend: "test_memory".into(),
                        recording_id: id.into(),
                        stream: "fast".into(),
                        sample_period_us: period,
                        fields: schema
                            .get_columns()
                            .iter()
                            .map(|c| backend::Field {
                                name: c.name().to_string(),
                                dtype: c.dtype().to_string(),
                            })
                            .collect(),
                        start: None,
                        stop: None,
                        complete: false,
                    },
                    schema.clone(),
                ))))))
            },
        )?;
        log.segment_rows = 15;
        log.push(100, frame(100, 15))?;
        log.push(115, frame(115, 15))?;
        let reader = log.reader();
        let middle = reader.read_range(103, 127)?;
        assert_eq!(middle.height(), 24);
        assert_eq!(reader.info()?.backend, "test_memory");
        log.finish()?;
        assert!(reader.info()?.complete);
        assert!(
            read(run.0.join("custom.parquet"))?
                .slice(3, 24)
                .equals_missing(&middle)
        );
        assert!(!run.0.join("custom-part-00000000.parquet").exists());
        Ok(())
    }
}
