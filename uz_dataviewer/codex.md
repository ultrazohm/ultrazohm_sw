# Codex Review Findings for uz_dataviewer

Date: 2026-06-18

Scope: read-only robustness, performance, and correctness review of the
`uz_dataviewer` application, with special attention to FFT behavior.

## Baseline

Existing tests passed:

```text
117 passed
```

Command used:

```sh
PYTHONDONTWRITEBYTECODE=1 pytest -q -p no:cacheprovider
```

The codebase already has useful regression coverage for FFT amplitude
normalization, DC/Nyquist handling, fast-length zero padding, min/max
downsampling, ImPlot dtype matching, command replay, session restore, and node
graph behavior.

## What Looks Solid

- FFT amplitude normalization is intentionally handled: Hann coherent gain is
  used, DC and Nyquist bins are not double-counted, and zero padding uses the
  original window normalization.
- FFT computation is GUI-free and covered by focused tests in
  `tests/test_analysis.py`.
- Downsampling uses a range-aware min/max envelope and a pyramid path for large
  signals, with tests that verify spike preservation and stable output budgets.
- Plotting avoids known ImPlot dtype pitfalls by passing matching float64 arrays.
- Analysis windows compute on demand rather than every frame.
- Session and command replay coverage is fairly broad.

## Findings and Remediation Plan

### 1. Harden the time-axis contract

Files:

- `src/uz_dataviewer/downsample.py`
- `src/uz_dataviewer/analysis.py`
- `src/uz_dataviewer/loader.py`
- `src/uz_dataviewer/model.py`

`visible_slice` assumes monotonically increasing time, and much of the app
inherits that assumption. FFT, plotting, cursor interpolation, export windows,
and node transforms can all return misleading results if a log has duplicate,
decreasing, empty, NaN, or Inf timestamps.

Plan:

- Add a single validation helper for time arrays.
- Apply it when loading/registering runs and derived runs.
- Decide whether invalid time should be rejected, sorted, or repaired. Rejection
  with a clear console error is the safest first step.
- Add tests for empty time, duplicate timestamps, decreasing timestamps, NaN,
  and Inf.

### 2. Make FFT sampling correctness explicit

File:

- `src/uz_dataviewer/analysis.py`

`compute_fft` derives `dt` from total span divided by sample count. That is fast
and correct for uniformly sampled JavaScope logs, but it silently accepts jittered
or nonuniform time axes. The resulting frequency axis and amplitudes can be
wrong.

Plan:

- Guard empty `time` before using `time[0]` or `time[-1]`.
- Add a cheap uniformity check for the selected window, possibly sampled for very
  large windows.
- Return a clear `FftResult` error if the selected time axis is not sufficiently
  uniform.
- Add tests for valid uniform data, jittered time, duplicate time, decreasing
  time, and too-short windows.

### 3. Fix mixed-sample-rate FFT CSV export

File:

- `src/uz_dataviewer/session.py`

The FFT plot stores each result as its own `(freqs, mag)` pair, which is correct.
CSV export uses the first signal's `frequency` column for all signals and then
trims all columns to the shortest length. For mixed sample rates or different
window lengths, amplitudes can be paired with the wrong frequency bins.

Plan:

- Change FFT export to one of these formats:
  - long format: `signal, frequency, amplitude`;
  - wide format with per-signal frequency and amplitude columns;
  - explicit interpolation onto a shared frequency grid.
- Prefer long format for correctness and simplicity.
- Add a mixed-rate export test that proves frequencies remain paired with the
  correct amplitudes.

### 4. Define a NaN/Inf policy

Files:

- `src/uz_dataviewer/analysis.py`
- `src/uz_dataviewer/panels/histogram.py`
- `src/uz_dataviewer/panels/plots.py`
- `src/uz_dataviewer/downsample.py`

Current behavior with NaN/Inf values is inconsistent. FFT can produce NaN
spectra, histograms can fail or become meaningless, downsampling extrema can be
affected by NaNs, and auto-fit handles some NaNs but not all-NaN signals robustly.

Plan:

- Decide whether non-finite signal values are rejected at load or masked per
  analysis.
- For plotting, consider preserving NaNs as gaps but exclude them from fit and
  decimation extrema.
- For FFT and histogram, return clear errors or ignore non-finite samples with
  an info message.
- Add tests for all-NaN, mixed finite/NaN, and Inf signals.

### 5. Add signal/time versioning for stale caches

Files:

- `src/uz_dataviewer/model.py`
- `src/uz_dataviewer/state.py`
- `src/uz_dataviewer/panels/plots.py`
- `src/uz_dataviewer/panels/analysis.py`

Plot decimation cache keys include `id(signal.y)` but not a run time version.
If time normalization changes the X axis while `signal.y` remains the same, a
cached decimated X array can be reused incorrectly. Analysis stale checks also
do not fully account for underlying signal data changes after derived runs are
refreshed in place.

Plan:

- Add a version counter to `Run` and/or `Signal`.
- Increment it whenever time or signal arrays are replaced or normalized.
- Include versions in plot decimation cache keys and analysis stale keys.
- Add tests for time normalization after plotting and derived-run reevaluation
  after analysis computation.

### 6. Move registry mutation back to the main thread

File:

- `src/uz_dataviewer/state.py`

Desktop async loading submits `load_file(path, self.registry)` to a worker. That
means the worker mutates `DataRegistry` while the UI may read it. In practice it
may often work, but it is an unnecessary concurrency risk.

Plan:

- Change loaders to parse into an intermediate object without touching the
  registry.
- Register the parsed run on the main thread inside `poll_pending_loads`.
- Keep synchronous command loading behavior intact.
- Add a test around pending loads if feasible, or isolate the new parse/register
  split with unit tests.

### 7. Validate transform time-base correctness

File:

- `src/uz_dataviewer/transforms.py`

Binary math checks equal signal lengths but does not check whether the time axes
match. Same-length signals from different runs can be added, subtracted, or
divided as if they shared a time base. Derivative, integral, and filter nodes also
assume finite increasing time.

Plan:

- For binary math, require matching time arrays within tolerance or explicitly
  document and warn that it is index-aligned.
- Validate finite increasing time for derivative, integral, and filter.
- Add tests for equal-length but shifted time axes.

### 8. Bound FFT window cache memory

File:

- `src/uz_dataviewer/analysis.py`

The Hann window cache is keyed by length and unbounded. Repeated large FFTs over
slightly different window lengths can retain large arrays for the lifetime of the
process.

Plan:

- Replace the dict with a small LRU cache, or cap by total cached sample count.
- Add a simple unit test around cache eviction if the cache becomes observable.

### 9. Add focused regression tests

Recommended new tests:

- Empty log and empty FFT window.
- Non-monotonic, duplicate, NaN, and Inf time axes.
- Jittered time axis rejected by FFT.
- FFT export with mixed sample rates.
- Plot cache invalidation after time normalization.
- Analysis stale indicator after derived signal refresh.
- Binary math with equal length but mismatched time axes.
- All-NaN and mixed-NaN signal behavior in fit, downsample, histogram, and FFT.

## Overall Assessment

The core implementation is in good shape, especially for the intended uniformly
sampled JavaScope use case. The most important remaining risks are boundary
correctness issues around time axes, non-finite data, mixed-rate FFT export, and
cache invalidation after in-place data changes.
