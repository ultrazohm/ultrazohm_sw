//! Unified bounded queries over recent RAM, pending recording data, and a backend.
use crate::{
    backend::{Field, RecordingReader, query_projection},
    live::{LiveBuffer, MAX_SNAPSHOT_BYTES, selected_columns},
    profile::Profile,
    protocol::Frame,
    storage::frames_dataframe,
};
use anyhow::{Context, Result, ensure};
use polars::prelude::*;
use serde::{Deserialize, Serialize};
use std::{
    collections::VecDeque,
    sync::{Arc, Mutex},
};

// Recording position, acquisition position (for timestamps), and samples.
pub type Frames = Vec<(u64, u64, Arc<Frame>)>;

/// Pending samples are bounded by one writer batch plus its bounded queue.
pub struct History {
    pub reader: Option<Arc<dyn RecordingReader>>,
    pub start: Option<u64>,
    pub stop: Option<u64>,
    pub persisted_stop: Option<u64>,
    pub pending: VecDeque<(u64, u64, Arc<Frame>)>,
    pub columns: Vec<(usize, String)>,
    pub slow: bool,
    pub max_pending_samples: usize,
    pub pending_samples: usize,
}
impl History {
    pub fn accepted(
        &mut self,
        index: u64,
        acquisition_index: u64,
        frame: Arc<Frame>,
    ) -> Result<()> {
        ensure!(
            self.stop.is_none_or(|end| end == index),
            "recording sample gap"
        );
        ensure!(
            self.pending_samples + frame.slow_raw.len() <= self.max_pending_samples,
            "pending recording memory limit exceeded"
        );
        self.start.get_or_insert(index);
        self.stop = Some(index + frame.slow_raw.len() as u64);
        self.pending_samples += frame.slow_raw.len();
        self.pending.push_back((index, acquisition_index, frame));
        Ok(())
    }
    pub fn committed(&mut self) -> Result<()> {
        self.persisted_stop = self
            .reader
            .as_ref()
            .context("recording is initializing")?
            .info()?
            .stop;
        if let Some(end) = self.persisted_stop {
            while self
                .pending
                .front()
                .is_some_and(|(first, _, f)| first + f.slow_raw.len() as u64 <= end)
            {
                self.pending_samples -= self.pending.pop_front().unwrap().2.slow_raw.len();
            }
        }
        Ok(())
    }
}

#[derive(Clone, Debug, Default, PartialEq, Eq, Serialize, Deserialize, clap::ValueEnum)]
#[serde(rename_all = "snake_case")]
pub enum Stream {
    #[default]
    Fast,
    Slow,
}

#[derive(Clone, Debug, Default, Serialize, Deserialize)]
#[serde(deny_unknown_fields)]
pub struct Source {
    #[serde(default)]
    pub stream: Stream,
    pub recording: Option<u64>,
}
#[derive(Clone, Debug, PartialEq, Eq, Serialize, Deserialize)]
#[serde(deny_unknown_fields)]
pub struct Cursor {
    pub run_id: String,
    pub stream: Stream,
    pub recording: Option<u64>,
    pub generation: u64,
    pub next_sample: Option<u64>,
}
#[derive(Clone, Debug, Serialize, Deserialize)]
#[serde(tag = "kind", rename_all = "snake_case", deny_unknown_fields)]
pub enum Selection {
    Tail {
        count: usize,
    },
    Range {
        start: u64,
        stop: u64,
    },
    Since {
        cursor: Option<Cursor>,
        limit: usize,
    },
}
#[derive(Clone, Debug, Serialize, Deserialize)]
#[serde(deny_unknown_fields)]
pub struct Query {
    pub source: Source,
    pub selection: Selection,
    pub channels: Option<Vec<String>>,
}
#[derive(Clone, Debug, Serialize, Deserialize)]
pub struct DataInfo {
    pub run_id: String,
    pub stream: Stream,
    pub recording: Option<u64>,
    pub generation: u64,
    pub start: Option<u64>,
    pub stop: Option<u64>,
    pub persisted_stop: Option<u64>,
    pub complete: bool,
    pub fields: Vec<Field>,
    pub layout: String,
    pub sample_period_us: f64,
    pub position_basis: String,
}
impl DataInfo {
    pub fn cursor(&self, next_sample: Option<u64>) -> Cursor {
        Cursor {
            run_id: self.run_id.clone(),
            stream: self.stream.clone(),
            recording: self.recording,
            generation: self.generation,
            next_sample,
        }
    }
    fn validate_cursor(&self, cursor: &Cursor) -> Result<()> {
        ensure!(
            *cursor == self.cursor(cursor.next_sample),
            "cursor belongs to a different run, stream, recording, or observable generation"
        );
        Ok(())
    }
}

/// A query captures positions and references under a short lock. File I/O and
/// column construction happen after the acquisition locks have been released.
pub struct DataView {
    pub info: DataInfo,
    frames: Frames,
    columns: Vec<(usize, String)>,
    reader: Option<Arc<dyn RecordingReader>>,
    profile: Profile,
}
fn slow_names(profile: &Profile) -> Vec<String> {
    let mut names = vec![String::new(); profile.slow_signals.len()];
    for (name, &id) in &profile.slow_signals {
        names[id as usize] = name.clone();
    }
    names
}
fn from_frames(
    frames: &[(u64, u64, Arc<Frame>)],
    start: u64,
    stop: u64,
    profile: &Profile,
    columns: &[(usize, String)],
    slow: bool,
) -> Result<DataFrame> {
    let selected: Frames = frames
        .iter()
        .filter(|(first, _, f)| *first < stop && first + f.slow_raw.len() as u64 > start)
        .cloned()
        .collect();
    let mut next = selected.first().map_or(start, |(first, _, _)| *first);
    for (first, _, frame) in &selected {
        ensure!(*first == next, "sample history contains a gap");
        next += frame.slow_raw.len() as u64;
    }
    ensure!(
        start <= stop
            && (start == stop
                || selected
                    .first()
                    .is_some_and(|(first, _, _)| *first <= start)
                    && next >= stop),
        "requested RAM samples are unavailable"
    );
    let rows = selected.iter().map(|(_, _, f)| f.slow_raw.len()).sum();
    let df = frames_dataframe(
        &selected
            .iter()
            .map(|(_, acquisition, frame)| (*acquisition, frame.clone()))
            .collect::<Vec<_>>(),
        rows,
        profile,
        columns,
        &slow_names(profile),
        slow,
    )?;
    let offset = selected.first().map_or(0, |(first, _, _)| start - first);
    Ok(df.slice(offset as i64, (stop - start) as usize))
}
impl DataView {
    pub fn live(
        run_id: &str,
        source: &Source,
        ring: &Mutex<LiveBuffer>,
        profile: &Profile,
        selections: &serde_json::Value,
        selection: Option<&Selection>,
    ) -> Result<Self> {
        let columns = if source.stream == Stream::Fast {
            selected_columns(profile, selections)?
        } else {
            Vec::new()
        };
        let ring = ring.lock().unwrap();
        let (start, stop) = ring.range();
        let empty = from_frames(&[], 0, 0, profile, &columns, source.stream == Stream::Slow)?;
        let mut view = Self {
            info: DataInfo {
                run_id: run_id.into(),
                stream: source.stream.clone(),
                recording: None,
                position_basis: "acquisition_samples".into(),
                generation: ring.generation,
                start,
                stop,
                persisted_stop: None,
                complete: false,
                fields: empty
                    .get_columns()
                    .iter()
                    .map(|c| Field {
                        name: c.name().to_string(),
                        dtype: c.dtype().to_string(),
                    })
                    .collect(),
                layout: if source.stream == Stream::Slow {
                    "slow_updates"
                } else {
                    "fast_samples"
                }
                .into(),
                sample_period_us: profile.sample_period_us,
            },
            frames: Vec::new(),
            columns,
            reader: None,
            profile: profile.clone(),
        };
        if let Some(selection) = selection {
            let (start, stop) = view.bounds(selection)?;
            view.frames = ring
                .frames(start, stop)
                .into_iter()
                .map(|(index, frame)| (index, index, frame))
                .collect();
        }
        Ok(view)
    }
    pub fn recorded(
        run_id: &str,
        source: &Source,
        history: &Mutex<History>,
        profile: &Profile,
        selection: Option<&Selection>,
    ) -> Result<Self> {
        let h = history.lock().unwrap();
        let reader = h.reader.as_ref().context("recording is initializing")?;
        let persisted = reader.info()?;
        let mut view = Self {
            info: DataInfo {
                run_id: run_id.into(),
                stream: source.stream.clone(),
                recording: source.recording,
                position_basis: persisted.position_basis,
                generation: 0,
                start: h.start,
                stop: h.stop,
                persisted_stop: h.persisted_stop,
                complete: persisted.complete,
                fields: persisted.fields,
                layout: if h.slow {
                    "slow_updates"
                } else {
                    "fast_samples"
                }
                .into(),
                sample_period_us: profile.sample_period_us,
            },
            frames: Vec::new(),
            columns: h.columns.clone(),
            reader: Some(reader.clone()),
            profile: profile.clone(),
        };
        if let Some(selection) = selection {
            let (start, stop) = view.bounds(selection)?;
            let start = start.max(h.persisted_stop.unwrap_or(start));
            view.frames = h
                .pending
                .iter()
                .filter(|(first, _, f)| *first < stop && first + f.slow_raw.len() as u64 > start)
                .cloned()
                .collect();
        }
        Ok(view)
    }
    fn bounds(&self, selection: &Selection) -> Result<(u64, u64)> {
        let first = self.info.start.unwrap_or(0);
        let end = self.info.stop.unwrap_or(0);
        let (start, stop) = match selection {
            Selection::Tail { count } => {
                ensure!(
                    *count > 0 && *count as u64 <= end - first,
                    "requested tail unavailable; only {} available; range [{first}, {end})",
                    end - first
                );
                (end - *count as u64, end)
            }
            Selection::Range { start, stop } => (*start, *stop),
            Selection::Since { cursor, limit } => {
                ensure!(*limit > 0, "limit must be positive");
                if let Some(cursor) = cursor {
                    self.info.validate_cursor(cursor)?;
                }
                let start = cursor.as_ref().and_then(|c| c.next_sample).unwrap_or(first);
                (start, start.saturating_add(*limit as u64).min(end))
            }
        };
        ensure!(
            start <= stop && start >= first && stop <= end,
            "range [{start}, {stop}) unavailable; available [{first}, {end}); cursor may have expired"
        );
        // Bound transient allocation before constructing any columns, including slow names.
        let per_row: usize = self
            .info
            .fields
            .iter()
            .map(|f| match f.dtype.as_str() {
                "f64" => 8,
                "str" => self
                    .profile
                    .slow_signals
                    .keys()
                    .map(|s| s.len() + 16)
                    .max()
                    .unwrap_or(16),
                _ => 4,
            })
            .sum();
        ensure!(
            stop - start <= ((MAX_SNAPSHOT_BYTES - 65536) / per_row.max(1)) as u64,
            "snapshot exceeds response limit; request a smaller range"
        );
        Ok((start, stop))
    }
    pub fn read(&self, query: &Query) -> Result<(DataFrame, Cursor, u64, u64)> {
        let (start, stop) = self.bounds(&query.selection)?;
        let projection = query_projection(&self.info.fields, query.channels.as_deref())?;
        let boundary = self
            .info
            .persisted_stop
            .unwrap_or(start)
            .max(start)
            .min(stop);
        let slow = self.info.stream == Stream::Slow;
        let read_ram = |start, stop| -> Result<DataFrame> {
            let data = from_frames(
                &self.frames,
                start,
                stop,
                &self.profile,
                &self.columns,
                slow,
            )?;
            Ok(match &projection {
                Some(names) => data.select(names.clone())?,
                None => data,
            })
        };
        let mut data = if let Some(reader) = &self.reader {
            if boundary > start {
                reader.read_projected_range(start, boundary, projection.as_deref())?
            } else {
                read_ram(start, start)?
            }
        } else {
            read_ram(start, start)?
        };
        if boundary < stop {
            data.vstack_mut(&read_ram(boundary, stop)?)?;
        }
        ensure!(
            data.height() as u64 == stop - start,
            "data query contains a gap"
        );
        Ok((
            data,
            self.info.cursor(self.info.stop.map(|_| stop)),
            start,
            stop,
        ))
    }
}
