//! Bounded sample history and independent, columnar snapshots.
use crate::{profile::Profile, protocol::Frame};
use anyhow::{Result, ensure};
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
    /// Seconds of acquisition each logger queue can buffer while its writer is busy
    /// (never fewer than 2,048 frames). Overflow ends only that recording.
    #[arg(long, default_value_t = DEFAULT_QUEUE_SECONDS)]
    #[serde(default = "default_queue_seconds")]
    pub queue_seconds: f64,
}

pub const DEFAULT_QUEUE_SECONDS: f64 = 3.0;
/// Upper bound of `queue_seconds`; queued frames stay in RAM.
pub const MAX_QUEUE_SECONDS: f64 = 600.0;
/// Lower bound of the logger queue, matching the previous fixed capacity.
pub const MIN_QUEUE_FRAMES: usize = 2048;
fn default_queue_seconds() -> f64 {
    DEFAULT_QUEUE_SECONDS
}

impl Default for DataOptions {
    fn default() -> Self {
        Self {
            recording_backend: Default::default(),
            buffer_samples: None,
            segment_rows: 1_000_000,
            flush_interval_ms: 60_000,
            queue_seconds: DEFAULT_QUEUE_SECONDS,
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
        ensure!(
            self.queue_seconds.is_finite()
                && self.queue_seconds > 0.0
                && self.queue_seconds <= MAX_QUEUE_SECONDS,
            "queue_seconds must be greater than 0 and at most {MAX_QUEUE_SECONDS}"
        );
        Ok(())
    }

    /// Logger queue capacity in frames for this sample period and frame size.
    pub fn queue_frames(&self, sample_period_us: f64, samples_per_packet: usize) -> usize {
        let frame_seconds = sample_period_us * 1e-6 * samples_per_packet.max(1) as f64;
        let frames = (self.queue_seconds / frame_seconds).ceil();
        if frames.is_finite() && frames < usize::MAX as f64 {
            (frames as usize).max(MIN_QUEUE_FRAMES)
        } else {
            MIN_QUEUE_FRAMES
        }
    }
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

    pub fn clear_channel(&mut self, channel: usize) {
        // Invalidate cursors so clients refresh their schema and retained data.
        // Copy shared frames before editing: existing query snapshots stay valid.
        self.generation += 1;
        for (_, frame) in &mut self.frames {
            Arc::make_mut(frame).channels[channel].fill(f32::NAN);
        }
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

#[cfg(test)]
mod tests {
    use super::*;
    use crate::data::{DataView, Query, Selection};
    use polars::prelude::*;
    use std::sync::Mutex;

    fn snapshot(ring: &LiveBuffer, count: usize, name: &str) -> Result<(DataView, Query)> {
        let mut profile = Profile::load(None)?;
        profile.observables.insert(name.into(), 0);
        let query = Query {
            source: Default::default(),
            selection: Selection::Tail { count },
            channels: None,
        };
        // Copy the ring references so the test can mutate the original after capturing a view.
        let mut copy = LiveBuffer::new(ring.capacity);
        for (index, frame) in &ring.frames {
            copy.push(*index, frame.clone());
        }
        let view = DataView::live(
            "test",
            &query.source,
            &Mutex::new(copy),
            &profile,
            &serde_json::json!({"1": name}),
            Some(&query.selection),
        )?;
        Ok((view, query))
    }

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
    fn clearing_one_channel_preserves_other_history_and_snapshots() {
        let mut ring = LiveBuffer::new(17);
        ring.push(0, frame(0, 10));
        let snapshot = ring.frames(0, 10);
        ring.clear_channel(1);
        assert_eq!(ring.generation, 1);
        assert_eq!(ring.range(), (Some(0), Some(10)));
        let retained = ring.frames(0, 10);
        assert!(retained[0].1.channels[1].iter().all(|value| value.is_nan()));
        assert_eq!(retained[0].1.channels[0], snapshot[0].1.channels[0]);
        assert_eq!(snapshot[0].1.channels[1], snapshot[0].1.channels[0]);
        ring.push(10, frame(10, 5));
        assert_eq!(
            ring.frames(10, 15)[0].1.channels[1],
            vec![10., 11., 12., 13., 14.]
        );
    }

    #[test]
    fn exact_capacity_partial_frames_and_independent_snapshot() -> Result<()> {
        let mut ring = LiveBuffer::new(17);
        ring.push(0, frame(0, 15));
        ring.push(15, frame(15, 15));
        ring.push(30, frame(30, 15));
        assert_eq!(ring.available(), 17);
        assert!(snapshot(&ring, 18, "signal").is_err());
        assert!(snapshot(&ring, 0, "signal").is_err());
        let (view, query) = snapshot(&ring, 17, "signal")?;
        ring.clear();
        ring.push(45, frame(45, 15));
        let (df, _, _, _) = view.read(&query)?;
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
        let (view, query) = snapshot(&ring, 1, "last")?;
        let (df, _, _, _) = view.read(&query)?;
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
        let (view, query) = snapshot(&ring, 3, "signal")?;
        let (mut df, _, _, _) = view.read(&query)?;
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
    fn logger_queue_is_sized_by_time_with_a_floor() {
        let options = DataOptions::default();
        // 10 kHz, 15 samples/frame: 3 s is 2,000 frames, so the floor applies.
        assert_eq!(options.queue_frames(100.0, 15), 2048);
        // 100 kHz: 3 s is 20,000 frames.
        assert_eq!(options.queue_frames(10.0, 15), 20_000);
        let longer = DataOptions {
            queue_seconds: 10.0,
            ..Default::default()
        };
        assert_eq!(longer.queue_frames(100.0, 15), 6_667);
        for seconds in [0.0, -1.0, f64::NAN, f64::INFINITY, MAX_QUEUE_SECONDS + 1.0] {
            let options = DataOptions {
                queue_seconds: seconds,
                ..Default::default()
            };
            assert!(options.validate().is_err(), "{seconds}");
        }
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
