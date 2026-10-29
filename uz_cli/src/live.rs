//! Bounded sample history and independent, columnar snapshots.
use crate::{profile::Profile, protocol::Frame};
use anyhow::{Result, ensure};
use polars::prelude::*;
use serde::{Deserialize, Serialize};
use serde_json::Value;
use std::{collections::VecDeque, sync::Arc};

// Bound an individual response independently of the configured history capacity.
pub const MAX_SNAPSHOT_BYTES: usize = 128 * 1024 * 1024;

#[derive(Clone, Debug, clap::Args, Serialize, Deserialize)]
pub struct DataOptions {
    /// Durable recording implementation, independent of CSV/Parquet export options.
    #[arg(long, value_enum, default_value = "parquet")]
    pub recording_backend: crate::backend::BackendKind,
    /// Recent samples retained in RAM; defaults to 30 seconds at the profile's sample rate.
    #[arg(long)]
    pub buffer_samples: Option<usize>,
    /// Target rows per Parquet segment (rounded up to a complete frame).
    #[arg(long, default_value_t = 1_000_000)]
    pub segment_rows: usize,
    /// Maximum batch wait between flushes, excluding queue and disk delays.
    #[arg(long, default_value_t = 60_000)]
    pub flush_interval_ms: u64,
}

impl Default for DataOptions {
    fn default() -> Self {
        Self {
            recording_backend: Default::default(),
            buffer_samples: None,
            segment_rows: 1_000_000,
            flush_interval_ms: 60_000,
        }
    }
}

impl DataOptions {
    pub fn resolve(&mut self, sample_period_us: f64) -> Result<()> {
        ensure!(
            sample_period_us.is_finite() && sample_period_us > 0.0,
            "invalid sample period"
        );
        if self.buffer_samples.is_none() {
            let samples = (30_000_000.0 / sample_period_us).ceil();
            ensure!(
                samples.is_finite() && samples >= 1.0 && samples < usize::MAX as f64,
                "30-second buffer capacity exceeds supported sample count"
            );
            self.buffer_samples = Some(samples as usize);
        }
        self.validate()
    }

    pub fn validate(&self) -> Result<()> {
        ensure!(
            self.buffer_samples != Some(0),
            "buffer_samples must be positive"
        );
        ensure!(self.segment_rows > 0, "segment_rows must be positive");
        ensure!(
            self.flush_interval_ms > 0,
            "flush_interval_ms must be positive"
        );
        Ok(())
    }
}

#[derive(Clone)]
pub struct Snapshot {
    frames: Vec<(u64, Arc<Frame>)>,
    skip: usize,
    pub rows: usize,
}

pub struct LiveBuffer {
    capacity: usize,
    frames: VecDeque<(u64, Arc<Frame>)>,
    rows: usize,
    pub generation: u64,
}

impl LiveBuffer {
    pub fn new(capacity: usize) -> Self {
        Self {
            capacity,
            frames: VecDeque::new(),
            rows: 0,
            generation: 0,
        }
    }

    pub fn clear(&mut self) {
        self.generation += 1;
        self.frames.clear();
        self.rows = 0;
    }

    pub fn available(&self) -> usize {
        self.rows.min(self.capacity)
    }

    pub fn push(&mut self, index: u64, frame: impl Into<Arc<Frame>>) {
        let frame = frame.into();
        self.rows += frame.slow_raw.len();
        self.frames.push_back((index, frame));
        // Retain at most one partial extra frame; queries expose exactly capacity rows.
        while let Some((_, first)) = self.frames.front() {
            if self.rows - first.slow_raw.len() < self.capacity {
                break;
            }
            self.rows -= first.slow_raw.len();
            self.frames.pop_front();
        }
    }

    pub fn range(&self) -> (Option<u64>, Option<u64>) {
        let stop = self
            .frames
            .back()
            .map(|(first, f)| first + f.slow_raw.len() as u64);
        (stop.map(|end| end - self.available() as u64), stop)
    }
    pub fn frames(&self, start: u64, stop: u64) -> Vec<(u64, Arc<Frame>)> {
        self.frames
            .iter()
            .filter(|(first, f)| *first < stop && first + f.slow_raw.len() as u64 > start)
            .cloned()
            .collect()
    }
    pub fn snapshot(&self, count: usize) -> Result<Snapshot> {
        ensure!(count > 0, "last_n_samples must be positive");
        ensure!(
            count <= self.available(),
            "requested {count} samples, but only {} available (buffer capacity {})",
            self.available(),
            self.capacity
        );
        let mut remaining = count;
        let mut frames = Vec::new();
        for (index, frame) in self.frames.iter().rev() {
            frames.push((*index, frame.clone()));
            if frame.slow_raw.len() >= remaining {
                let skip = frame.slow_raw.len() - remaining;
                frames.reverse();
                return Ok(Snapshot {
                    frames,
                    skip,
                    rows: count,
                });
            }
            remaining -= frame.slow_raw.len();
        }
        unreachable!("available rows must be retained")
    }
}

/// Canonical names in channel order, deduplicated by observable ID like recording columns.
pub fn selected_columns(profile: &Profile, selections: &Value) -> Result<Vec<(usize, String)>> {
    let columns = profile.selected_columns(selections)?;
    ensure!(
        !columns.is_empty(),
        "select at least one observable before requesting live data"
    );
    Ok(columns)
}

impl Snapshot {
    pub fn dataframe(&self, period_us: f64, columns: &[(usize, String)]) -> Result<DataFrame> {
        crate::storage::fast_dataframe(&self.frames, period_us, columns, self.skip, self.rows)
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    fn frame(first: usize, rows: usize) -> Frame {
        Frame {
            status: 7,
            slow_raw: vec![0; rows],
            slow_ids: vec![0; rows],
            channels: (0..20)
                .map(|_| (first..first + rows).map(|x| x as f32).collect())
                .collect(),
        }
    }

    #[test]
    fn exact_capacity_partial_frames_and_independent_snapshot() -> Result<()> {
        let mut ring = LiveBuffer::new(17);
        ring.push(0, frame(0, 15));
        ring.push(15, frame(15, 15));
        ring.push(30, frame(30, 15));
        assert_eq!(ring.available(), 17);
        assert!(ring.snapshot(18).is_err());
        assert!(ring.snapshot(0).is_err());
        let snapshot = ring.snapshot(17)?;
        ring.clear();
        ring.push(45, frame(45, 15));
        let df = snapshot.dataframe(100., &[(0, "signal".into())])?;
        assert_eq!(df.height(), 17);
        assert_eq!(df.column("signal")?.f32()?.get(0), Some(28.));
        assert_eq!(df.column("signal")?.f32()?.get(16), Some(44.));
        assert!((df.column("time")?.f64()?.get(0).unwrap() - 0.0028).abs() < 1e-12);
        Ok(())
    }

    #[test]
    fn buffer_smaller_than_a_frame() -> Result<()> {
        let mut ring = LiveBuffer::new(1);
        ring.push(0, frame(0, 15));
        ring.push(15, frame(15, 15));
        assert_eq!(ring.available(), 1);
        assert_eq!(ring.frames.len(), 1);
        let df = ring.snapshot(1)?.dataframe(100., &[(19, "last".into())])?;
        assert_eq!(df.column("last")?.f32()?.get(0), Some(29.));
        Ok(())
    }

    #[test]
    fn arrow_preserves_nonfinite_samples_and_status() -> Result<()> {
        let mut f = frame(0, 3);
        f.channels[0] = vec![f32::NAN, f32::INFINITY, f32::NEG_INFINITY];
        f.status = u32::MAX;
        let mut ring = LiveBuffer::new(3);
        ring.push(0, f);
        let mut df = ring.snapshot(3)?.dataframe(100., &[(0, "signal".into())])?;
        let mut bytes = Vec::new();
        IpcStreamWriter::new(&mut bytes).finish(&mut df)?;
        let read = IpcStreamReader::new(std::io::Cursor::new(bytes)).finish()?;
        let values = read.column("signal")?.f32()?;
        assert!(values.get(0).unwrap().is_nan());
        assert_eq!(values.get(1), Some(f32::INFINITY));
        assert_eq!(values.get(2), Some(f32::NEG_INFINITY));
        assert_eq!(read.column("status")?.u32()?.get(0), Some(u32::MAX));
        Ok(())
    }

    #[test]
    fn canonical_columns_deduplicate_and_reject_reserved_names() -> Result<()> {
        let mut profile = Profile::load(None)?;
        let columns = selected_columns(
            &profile,
            &serde_json::json!({"1":"lifecheck", "2":"JSO_lifecheck"}),
        )?;
        assert_eq!(columns, vec![(0, "JSO_lifecheck".into())]);
        profile.observables.insert("time".into(), 100);
        assert!(selected_columns(&profile, &serde_json::json!({"1":"time"})).is_err());
        Ok(())
    }

    #[test]
    fn default_history_is_thirty_seconds_at_configured_rate() -> Result<()> {
        for (period, expected) in [
            (100.0, 300_000),
            (50.0, 600_000),
            (10.0, 3_000_000),
            (333.0, 90_091),
        ] {
            let mut options = DataOptions::default();
            options.resolve(period)?;
            assert_eq!(options.buffer_samples, Some(expected));
        }
        let mut explicit = DataOptions {
            buffer_samples: Some(17),
            ..Default::default()
        };
        explicit.resolve(10.0)?;
        assert_eq!(explicit.buffer_samples, Some(17));
        for period in [0.0, f64::NAN, f64::INFINITY, f64::MIN_POSITIVE] {
            assert!(DataOptions::default().resolve(period).is_err());
        }
        Ok(())
    }

    #[test]
    fn zero_limits_are_rejected() {
        for options in [
            DataOptions {
                buffer_samples: Some(0),
                ..Default::default()
            },
            DataOptions {
                segment_rows: 0,
                ..Default::default()
            },
            DataOptions {
                flush_interval_ms: 0,
                ..Default::default()
            },
        ] {
            assert!(options.validate().is_err());
        }
    }
}
