# Scope 2 architecture

Scope 2 preserves the JavaScope wire contract and replaces the desktop application layer. The GUI and command surface borrow interaction patterns and reusable data utilities from `uz_dataviewer`, while live acquisition remains a separate package.

## Data path

```text
UltraZohm TCP frames
        |
        v
protocol parser -> channel-major float32 block
        |                 |                 |
        v                 v                 v
bounded raw ring     RAM envelope       async logger
        |                 |
        +--------+--------+
                 v
       remap-safe segment query
                 |
                 v
       workspace plot renderer
```

The reader thread parses a frame batch once and makes one channel-major block. The same immutable block feeds the ring, history envelope, trigger engine, lifecheck/slowdata handling, and the bounded logger queue. GUI work stays on the main thread.

Absolute 64-bit sample indices are the time authority. Seconds are calculated only at query/export boundaries, avoiding long-run floating-point drift.

## Acquisition segments

A hardware slot is only transport storage; it is not a permanent signal identity. `SegmentRegistry` records each uninterrupted mapping as:

```text
segment id -> slot, observable, [start sample, stop sample), display style
```

Remapping first closes the old segment and then starts a new one. Every query is clamped to that interval and to the resident ring range. Archived segments are removed when their stop index is older than the ring's oldest sample. This prevents samples recorded under one observable from ever being displayed under another name.

On reconnect, active mappings receive new segment IDs and workspace references are rebound. Saved sessions use observable IDs instead of transient segment IDs.

## Bounded history and rendering

`ChannelRing` is a preallocated `(channels, samples)` float32 ring capped by both duration and bytes. It is the source for exact raw export.

`LivePyramid` incrementally stores min/max envelopes and coarsens itself under a configured RAM limit. Wide plot queries use it; narrow queries use the raw ring and `uz_dataviewer.downsample.decimate_range`. No disk history backend is exposed.

`PlotWorkspace` owns windows and subplot state independently of ImGui. `WorkspacePlotPanel` renders that state, caches visible queries per refresh frame, and records visible X ranges for export. Live-follow state belongs to each window, so navigating one window does not stop the others.

## Commands and persistence

Every meaningful GUI operation routes through `ScopeCommandRegistry`. `workspace_commands.py` adds acquisition, window/grid, plot type, XY, axis, tool, limit, follow, and export commands.

Session JSON uses schema version 2:

```text
{
  "version": 2,
  "config": { ... },
  "workspace": { ... }
}
```

Version-1 plain configuration files remain loadable. Replay scripts serialize stable observable assignments and omit automatic connection. Visible-range CSV export reads the raw ring rather than the plotted envelope.

## Isolation

`uz_scope2` has its own Python package, `uz-scope2` executable, settings filename, layout filename, native-build identity, and localhost single-instance guard port. The source projects `uz_scope`, `uz_dataviewer`, and JavaScope are read-only references for this implementation.
