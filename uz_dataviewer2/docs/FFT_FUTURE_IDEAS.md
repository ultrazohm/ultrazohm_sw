# FFT — future ideas (not yet implemented)

Captured 2026-06-15. **Part 0 below is already done** (it was the real cause of the
"15M-sample FFT drops to ~15 fps" report). Parts 1–2 are deferred ideas for *deliberate*
resolution control and for the one-time compute cost — open until someone needs them.

## Background / measurements (15M-sample window, one core)
- One-time `rfft` + magnitude on *Compute*: **~512 ms** → 7,500,001 bins (60 MB float32).
- Spectrum pyramid build: ~35 ms.
- Per-frame plotting (pyramid-backed `decimate_range`): ~0.3 ms.
- So the *display* was never inherently expensive; see Part 0.

## Part 0 — DONE: the actual FPS fix (dtype landmine)
The ~70 ms/frame display cost was **not** the bin count. `AnalysisPanel._plot_decimated`
calls `visible_slice(freqs, …)` every frame, and the FFT `freqs` array is **float32**.
`np.searchsorted(float32_array, python_float)` **up-casts the entire 7.5M-point array to
float64** every call (~31 ms × 2 calls = ~62 ms/frame) — the same landmine the architecture
doc already documents for `np.interp` cursors.

**Fix shipped:** `visible_slice` now coerces the search scalars to `time.dtype` before
`searchsorted` (`downsample.py`). Result: **70 ms → 0.15 ms/frame**, full 7.5M-bin resolution
kept, no math change. Regression guard: `tests/test_downsample.py::test_visible_slice_is_fast_on_float32`.

> Lesson for the future: any `searchsorted` / `interp` / comparison of a Python-`float`
> scalar against a **float32 signal array** up-casts the whole array. Always pass a
> dtype-matched scalar. Worth a grep before adding new per-frame array math.

---

## Part 1 — Power-of-2 (zero) padding? → recommendation: don't
- 15M = 2⁶·3·5⁷ is already **5-smooth**, so NumPy's pocketfft is not badly mis-factored; the
  512 ms is mostly size, not factoring.
- Padding **up** to the next power of two (2²⁴ = 16.7M) makes it *more* points → ~8.4M bins →
  worse memory/display. Zero-padding only **sinc-interpolates** the spectrum (finer-looking
  bins, no new real resolution) and adds minor leakage bias.
- The only legitimate speed use is a window length with a **large prime factor**. The robust
  form is to snap the FFT length to a nearby **5-smooth** size and **truncate down** (fewer
  points, faster), accepting that the window tail is dropped — *not* a power-of-2 knob.
- **Verdict:** padding is the wrong lever for "too expensive / too many bins." Reducing input
  samples (Part 2) is the real lever. At most, an internal "round FFT length down to 5-smooth"
  micro-opt, off by default.

## Part 2 — Fixed number of frequency bins (resample / Welch)
Goal: a user-set cap on bin count so huge windows compute cheaply and the spectrum stays small.
Two **dual** approaches with opposite trade-offs:

| Mode | Bins | Bin spacing `Δf` | Max freq (Nyquist) | Notes |
|---|---|---|---|---|
| **Resample to `N_fft`** (the "resample at a lower rate" idea) | fixed `N_fft/2+1` | `1/T` — fine, **kept** | **lowered** to `N_fft/(2T)` | needs an anti-alias low-pass first |
| **Welch (`N_seg` segments, averaged)** | fixed `N_seg/2+1` | `fs/N_seg` — **coarser** | full `fs/2`, **kept** | reduces noise variance (smoother PSD); pure NumPy |

### Key math (so the trade-off is explicit)
For a window of duration `T` with `M` raw samples (`fs = M/T`):
- `Δf = fs/N = 1/T` — depends only on `T`, so **resampling does not change frequency
  resolution**, only the frequency *range*.
- Resampling the window from `M` → `N_fft` samples sets `fs' = N_fft/T`, Nyquist `= fs'/2`.
  Choosing `N_fft` therefore picks the bin count *and* the max visible frequency; you keep fine
  low-frequency resolution but **lose everything above `fs'/2`**.
- Welch keeps `fs` (full range) but fixes resolution at `Δf = fs/N_seg` and averages
  `~M/N_seg` periodograms → lower variance.

### Implementation sketch
- New optional control + command `fft_max_bins(n)` (default `0` = full resolution, today's
  behavior unchanged). Possibly a mode enum {full, resample, welch}.
- **Resample mode:** when the window has > `N_fft` samples, **anti-alias resample** to `N_fft`
  before `rfft`. The low-pass is mandatory — naive stride decimation aliases high-freq energy
  into fake peaks, and the **min/max pyramid must never feed the FFT** (nonlinear → spurious
  harmonics).
- **Welch mode:** split into `N_seg`-length segments (Hann each, 50% overlap optional), average
  `|rfft|`. Trivial in pure NumPy.
- Output is tens of k bins → **no spectrum pyramid needed**; memory 60 MB → ~256 KB.

### Open decisions before building
1. **Which mode(s)** — resample (keep `Δf`, lose high freq), Welch (keep range, coarser, smoother),
   or both selectable. *Leaning: Welch as the default cap (pure NumPy, keeps full range,
   smoother), resample as a second mode.*
2. **Anti-alias implementation** — add `scipy` (it's installed locally, **not** in
   `requirements.txt`/`pyproject.toml`, and is a heavy Pyodide wheel) and use
   `scipy.signal.decimate`/`resample_poly`; **or** hand-roll a small NumPy FIR/polyphase
   decimator to keep native + web on one dependency-free path (consistent with dropping
   `tsdownsample`). *Leaning: NumPy decimator.*
3. **Move the one-time `rfft` off the render thread?** — independent of the above; kills the
   ~0.5 s *Compute* freeze on native (reuse the existing `ThreadPoolExecutor`) without changing
   the math. Web has no worker threads, so it would still stall there.

### Related touch-points when implemented
- Transform: `compute_fft` in [src/uz_dataviewer/analysis.py](../src/uz_dataviewer/analysis.py).
- Window/panel + controls: [src/uz_dataviewer/panels/fft.py](../src/uz_dataviewer/panels/fft.py)
  and the shared [panels/analysis.py](../src/uz_dataviewer/panels/analysis.py).
- Command registration + stale-key (`_options_key`): [src/uz_dataviewer/commands.py](../src/uz_dataviewer/commands.py).
- Session round-trip + USAGE/ARCHITECTURE docs.
