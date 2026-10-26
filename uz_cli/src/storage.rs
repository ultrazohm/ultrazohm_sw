//! Finalized Parquet segments during acquisition; separate fast/slow Parquet and optional CSV at close.
use crate::{profile::Profile, protocol::Frame};
use anyhow::{Context, Result, ensure};
use polars::prelude::*;
use serde::{Deserialize, Serialize};
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
    dir: PathBuf,
    profile: Profile,
    format: Format,
    batch: Vec<(u64, Frame)>,
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
            slow_names[id as usize] = name.clone();
        }
        ensure!(dir.is_dir(), "recording directory does not exist");
        ensure!(
            !dir.join(format!("{stem}.parquet")).exists(),
            "recording already exists"
        );
        Ok(Self {
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
    pub fn push(&mut self, index: u64, frame: Frame) -> Result<()> {
        ensure!(
            self.next_index.is_none_or(|next| next == index),
            "missing or out-of-order samples"
        );
        self.first_index.get_or_insert(index);
        self.next_index = Some(index + frame.slow_raw.len() as u64);
        self.rows += frame.slow_raw.len();
        self.batch.push((index, frame));
        if self.rows >= 4096 {
            self.flush()?;
        }
        Ok(())
    }
    fn dataframe(&self) -> Result<DataFrame> {
        let mut time = Vec::with_capacity(self.rows);
        let mut status = Vec::with_capacity(self.rows);
        let mut slow_id = Vec::with_capacity(self.rows);
        let mut slow_name = Vec::with_capacity(self.rows);
        let mut slow_raw = Vec::with_capacity(self.rows);
        let mut slow_value = Vec::with_capacity(self.rows);
        let mut channels: Vec<Vec<f32>> = (0..20).map(|_| Vec::with_capacity(self.rows)).collect();
        for (first, f) in &self.batch {
            for i in 0..f.slow_raw.len() {
                time.push((first + i as u64) as f64 * self.profile.sample_period_us * 1e-6);
                status.push(f.status);
                if self.slow {
                    slow_id.push(f.slow_ids[i]);
                    slow_name.push(self.slow_names[f.slow_ids[i] as usize].as_str());
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
        if self.slow {
            cols.extend([
                Column::new("observable".into(), slow_name),
                Column::new("slow_id".into(), slow_id),
                Column::new("slow_raw".into(), slow_raw),
                Column::new("slow_value".into(), slow_value),
            ]);
        } else {
            for (index, name) in &self.fast_columns {
                cols.push(Column::new(
                    name.clone().into(),
                    std::mem::take(&mut channels[*index]),
                ));
            }
        }
        Ok(DataFrame::new(cols)?)
    }

    /// Commit a complete, independently readable Parquet segment for every format.
    pub fn flush(&mut self) -> Result<()> {
        if self.rows == 0 {
            return Ok(());
        }
        {
            let mut df = self.dataframe()?;
            let target = self.segment(self.part);
            ensure!(!target.exists(), "refusing to overwrite log segment");
            let tmp = target.with_extension("parquet.partial");
            let mut file = File::create_new(&tmp)?;
            ParquetWriter::new(&mut file).finish(&mut df)?;
            file.sync_all()?;
            drop(file);
            fs::rename(tmp, target)?;
        }
        self.part += 1;
        self.written_rows += self.rows;
        self.rows = 0;
        self.batch.clear();
        Ok(())
    }

    fn segment(&self, part: u64) -> PathBuf {
        self.dir
            .join(format!("{}-part-{part:08}.parquet", self.stem))
    }

    /// Finalize before deleting any segments. Conversion failures retain the final
    /// Parquet and all source segments; merge failures retain the source segments.
    pub fn finish(mut self) -> Result<()> {
        self.flush()?;
        self.merge()?;
        if !matches!(self.format, Format::Parquet) {
            let stem = &self.stem;
            export_csv(
                &self.dir.join(format!("{stem}.parquet")),
                &self.dir.join(format!("{stem}.csv")),
            )
            .context("CSV export failed; final Parquet and segments retained")?;
        }
        for part in 0..self.part {
            fs::remove_file(self.segment(part))
                .context("final files ready but segment cleanup failed")?;
        }
        Ok(())
    }

    fn merge(&self) -> Result<()> {
        let stem = &self.stem;
        let target = self.dir.join(format!("{stem}.parquet"));
        ensure!(!target.exists(), "refusing to overwrite final Parquet");
        let tmp = self.dir.join(format!("{stem}.parquet.partial"));
        let mut file = File::create_new(&tmp)?;
        let empty = self.dataframe()?;
        let mut writer = ParquetWriter::new(&mut file).batched(empty.schema())?;
        let mut merged_rows = 0usize;
        for part in 0..self.part {
            // Each segment is bounded by the acquisition batch limit, not run length.
            let df = ParquetReader::new(File::open(self.segment(part))?)
                .finish()
                .with_context(|| format!("reading segment {part}"))?;
            ensure!(
                df.schema() == empty.schema(),
                "segment {part} schema mismatch"
            );
            let times = df.column("time")?.f64()?;
            let first = self.first_index.unwrap_or(0) + merged_rows as u64;
            ensure!(
                times.null_count() == 0
                    && times
                        .into_no_null_iter()
                        .eq((first..first + df.height() as u64)
                            .map(|i| i as f64 * self.profile.sample_period_us * 1e-6)),
                "segment {part} has missing or out-of-order samples"
            );
            merged_rows += df.height();
            writer.write_batch(&df)?;
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
                check.num_rows()? == self.written_rows,
                "final Parquet row count mismatch"
            );
            let schema = check.with_slice(Some((0, 0))).finish()?;
            ensure!(
                schema.schema() == empty.schema(),
                "final Parquet schema mismatch"
            );
        }
        fs::rename(tmp, &target)?;
        Ok(())
    }
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
            slow_ids: vec![1; count],
            channels: vec![(start..start + count).map(|i| i as f32).collect(); 20],
        }
    }
    fn read(path: PathBuf) -> Result<DataFrame> {
        Ok(ParquetReader::new(File::open(path)?).finish()?)
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
            assert_eq!(slow.shape(), (df.height(), 6));
            assert!(df.column("slow_id").is_err());
            assert!(slow.column("ch_1").is_err());
            for column in ["time", "status"] {
                assert_eq!(df.column(column)?, slow.column(column)?);
            }
            assert!(
                slow.column("slow_id")?
                    .u32()?
                    .into_no_null_iter()
                    .all(|v| v == 1)
            );
            assert!(
                slow.column("slow_raw")?
                    .u32()?
                    .into_no_null_iter()
                    .all(|v| v == 2.5f32.to_bits())
            );
            assert!(
                slow.column("slow_value")?
                    .f32()?
                    .into_no_null_iter()
                    .all(|v| v == 2.5)
            );
            let csv_enabled = !matches!(format, Format::Parquet);
            assert_eq!(
                fs::read_dir(&run.0)?.count(),
                if csv_enabled { 4 } else { 2 }
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
                assert!(
                    slow_csv
                        .lines()
                        .last()
                        .unwrap()
                        .ends_with(",1,1075838976,2.5")
                );
            }
        }
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
        assert_eq!(read(run.0.join("data_slow_data.parquet"))?.shape(), (0, 6));
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
}
