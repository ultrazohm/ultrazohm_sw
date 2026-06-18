# Large logs in the web build (the wasm32 memory limit)

> Status: **analysis / design note, not built.** Part of the [roadmap](ROADMAP.md). This is
> **separate** from the cloud-data feature ([REMOTE_DATA.md](REMOTE_DATA.md)) — it is purely
> about why the *browser* build can't open very large logs and what could fix it. The
> implementation approach is intentionally left open.

## The problem (concrete)

`Log_2026-06-16_10-46-24.csv`: **~4.6 GB text, 21 columns** (`time` + 20 channels,
`;`-delimited), **~55M rows**. Parsed to numbers:

- `time` `float64` (8 B) + 20 channels `float32` (80 B) = **88 B/row × 55M ≈ ~4.8 GB numeric.**

The web build cannot hold that, so today it either decimates `1:stride` on load (lossy overview;
see `build/gen_web.py` `MEM_BUDGET`) or the tab runs out of memory. Native opens it fine (it uses
the PC's RAM).

## Why it's hard: the wasm32 ceiling

Pyodide is a **wasm32** runtime: it has **one linear memory** — a single contiguous
`ArrayBuffer` addressed by 32-bit pointers → **~4 GiB maximum, ~2–3 GB in practice** once you
leave headroom. **Everything** Python touches lives in it: numpy arrays, Apache Arrow's parse
buffers, the CSV text while parsing, and all Python objects. The current loader materializes the
**whole** dataset (`time` + every channel) and then builds the min/max pyramid in that same
memory — so ~4.8 GB simply doesn't fit in a ~4 GB address space.

The crucial point: **this cap is on linear memory (RAM), not on what the tab can store overall.**
That distinction is the whole answer to "would a database help?"

## Mitigations

| Option | Helps? | Cost |
|---|---|---|
| **Decimate-on-load** (current) | Loads a coarse *overview* only — no full-res zoom | already done; lossy |
| **Shrink the footprint** (load only selected channels; store `y` as `float16`/`int16`) | ~2–4× more headroom | cheap, partial; precision loss |
| **Out-of-core via OPFS** (embedded DB or on-disk pyramid) | **Real fix** — data on disk, not in the 4 GB RAM | significant change |
| **wasm64 / memory64** | Raises the address space past 4 GB | needs a memory64 Pyodide + imgui_bundle build and broad browser support — not practical yet, and still bounded by device RAM |
| **Web Workers / SharedArrayBuffer** | **No** — still 32-bit linear memory per module | only improves responsiveness, not capacity |

## Why an embedded database resolves it — even in the same browser tab

A natural objection: *the data still lives in the same browser window, so how does a DB help?*
Because a tab has **two separate memory pools**, and the 4 GB cap applies to only one:

1. **wasm linear memory (RAM)** — the single ~4 GB `ArrayBuffer`. This is the wall.
2. **OPFS (Origin Private File System)** — large, persistent, **disk-backed** storage for the
   origin (many GB, up to a big fraction of free disk). It is **not** part of linear memory and
   is **not** addressed by wasm pointers.

An embedded database compiled to wasm — **DuckDB-wasm**, or **SQLite-wasm** with the OPFS VFS —
keeps its tables/files in **OPFS (disk)** and runs queries **out-of-core**: it pages only the
data it currently needs into a **bounded buffer** in linear memory, scans, and frees it; the
result it returns is **small** (~`max_points` per signal). So:

- the full ~4.8 GB dataset lives **on disk** (OPFS) in the same browser, and
- only a **bounded working set** ever occupies the 4 GB RAM, flowing through it in small pages.

Hence the dataset can be **far larger than 4 GB** even though it's the same tab — the database is
the bridge between disk-resident data and RAM-bounded compute. "Same window" is true; "same 4 GB
RAM" is not — the data sits on disk and only streams through RAM.

### The catch (the real work)

This only works if the app **never materializes the whole dataset in RAM**. Today we do the
equivalent of `SELECT *` into numpy. To go out-of-core the data path must switch to **query the
visible window per view**:

- zoomed in → a **range** query (few rows) → exact;
- zoomed out → a **min/max-per-bucket** query for the overview (can't pull all raw rows into RAM);
- fetched **async + cached**, debounced on pan/zoom settle (the same idea as the zoom echo in
  `panels/plots.py`).

The zoomed-out overview min/max therefore has to be computed **out-of-core** — by the engine, not
by loading everything.

## Do pandas / Polars already solve this? And isn't native also RAM-bound?

- **Native is also bound by RAM today.** The current loader (native *and* web) reads the
  **whole** log into in-memory numpy arrays + pyramid. Native just has a far higher ceiling (the
  PC's RAM — tens of GB), so a ~4.8 GB log is comfortable, but a much larger one (e.g. 50 GB)
  would still exhaust native RAM. "Bound by RAM" holds on both; only the ceiling differs (machine
  RAM vs ~4 GB wasm).
- **…and the current loader wastes memory at load (a separate fix — partially DONE).** Loading
  the 4.6 GB example uses **~24 GB**. One cause: `pyarrow.csv.read_csv`
  ([loader.py](../src/uz_dataviewer/loader.py)) inferred channels as **float64**, then
  `_table_to_run` did `to_numpy(...).astype(float32)` per column (a float64 *and* a float32 copy).
  **Fixed:** channels are now parsed **directly as float32** (time stays float64) via
  `ConvertOptions(column_types=…)`. Measured saving scales as `4 B × n_channels × rows` (≈0.2 GB
  at 2M rows → **≈4–5 GB at ~55M rows**), i.e. **~24 GB → ~19–20 GB** — real but **not** a
  halving. The dominant remaining cost is that Arrow still materialises the **whole table** in RAM
  alongside the output arrays. To actually cut the peak you must avoid holding the whole table:
  **stream-parse** (Arrow batch reader → convert each batch to float32 into preallocated arrays,
  the same shape as the web JS loader) or load from **Parquet** (smaller input, float32 columns,
  no inference). Those are the bigger levers; the out-of-core work below is only for logs that
  exceed RAM entirely.
- **pandas** is in-memory only — it loads the whole frame into RAM. It can read in fixed
  `chunksize` passes, but has no random-access "read just the visible window" model for
  interactive use. Not an out-of-core fix by itself.
- **Polars** *can* do it: its **lazy + streaming** mode (`scan_parquet`/`scan_csv` →
  `collect(streaming=…)`) is out-of-core. Over **Parquet** it does **predicate + projection
  pushdown** — it skips row groups outside the time range and reads only the needed columns,
  streaming in bounded-memory batches — so a min/max-per-bucket over a window reads only what it
  needs. **DuckDB over Parquet** does the same. So this capability genuinely exists.
- **The catch is *where* it runs.** Those engines help only if (a) they run in the target and
  (b) the data sits on **disk** they can stream from. On **native**, both hold → Polars/DuckDB
  over Parquet is the easy out-of-core path, and it would **lift the native RAM bound too**. In
  the **browser**, the Python builds of Polars/pandas aren't set up for Pyodide + OPFS streaming
  (and a file in Pyodide's in-memory FS counts against the same 4 GB), so the practical engine
  there is **DuckDB-wasm** (the JS/wasm package) reading from **OPFS** — i.e. approach A below.

So the out-of-core idea is engine-agnostic: on native you'd reach for Polars/DuckDB over Parquet
(easy, and removes the native RAM bound); in the browser you'd use DuckDB-wasm + OPFS, or our own
on-disk pyramid in OPFS.

---

## Native large logs (up to ~100M points) — **SHIPPED**

This is the realistic target (native, both **CSV and Parquet**, up to ~100M points). The data
stays **in RAM** so FFT / node transforms / histogram keep working — they each need the full
window's raw samples in RAM (a full-record `rfft` even adds ~2–3 GB transient at 100M). Going
out-of-core here would force a segmented/Welch FFT + a nodes rework — much larger effort. At 100M
the ~8.8 GB resident fits native RAM; the only real problem is the **load peak**, so we just load
leanly. (Out-of-core, below, is reserved for the web/larger-than-RAM case.)

Key simplification: **cap CSV at ~10M rows and require Parquet above that.** This removes the
hard part of streaming (assembling in-memory arrays from a CSV with no row count) — only Parquet
needs streaming, and Parquet is the easy case.

**Status: implemented in `loader.py`** (all four pieces below). The data stays in RAM, so FFT /
histogram / node transforms keep working on the full record.

1. **CSV — bulk loader, guarded by footprint. ✅**
   - Channels parse **directly to float32**, time to float64, via
     `ConvertOptions(column_types=_csv_column_types(...))` — no float64 intermediate copy.
   - `_guard_csv_size` estimates the resident footprint from file size × column count and **refuses**
     a CSV above `MAX_CSV_NUMERIC_BYTES` (~10 GB, ~110M rows at 20 channels) with a message pointing at
     `convert(...)`.
   - **Caveat:** the budget is measured against the *resident* footprint, **not** the bulk-parse
     peak. Arrow's `read_csv` transiently uses ~2–3× the resident size, so a CSV just under the
     limit can still peak well above 10 GB during parsing. `MAX_CSV_NUMERIC_BYTES` is thus a
     deliberately high ceiling that blocks only extreme files — not a guarantee the bulk parse fits
     in 10 GB. Lower it if you want a more conservative guard.

2. **Parquet — streaming load (up to ~100M). ✅**
   - `pq.ParquetFile(path).metadata.num_rows` gives the exact row count → arrays are **preallocated**
     exactly (no grow-and-trim).
   - `iter_batches(columns=…)` streams row groups; each batch is cast to float32 / float64 into the
     preallocated slices and discarded. Files below `PARQUET_STREAM_MIN_ROWS` keep the simple bulk
     path. Measured peak ≈ ~1.5× resident (vs ~2.1× for bulk) and the gap widens with size.

3. **CSV→Parquet converter. ✅**
   - `convert_csv_to_parquet(src, dst=None)`: streaming `pa_csv.open_csv(...)` → per-batch
     `ParquetWriter.write_batch(...)`, dropping JavaScope's empty trailing column and keeping raw
     headers so the `.parquet` round-trips through the same name parsing on load.

4. **Triggering the converter — refuse with guidance (chosen UX). ✅**
   - The size guard refuses and points the user to convert once; conversion is **explicit**, not
     auto-on-open. Exposed both as the scriptable `convert(src, [dst])` console command and the
     headless `uz-dataviewer convert <file.csv>` CLI subcommand.

**Web is unchanged by this:** even as Parquet, 100M (~8.8 GB) can't fit Pyodide's 4 GB heap
(Arrow builds the whole table), so web large logs still need the out-of-core route below. This
work is **native-only**.

**Touch points (as built):** `loader.load_csv` (float32 types + `_guard_csv_size`),
`loader.load_parquet` / `_load_parquet_streaming` (streaming + preallocation), `convert_csv_to_parquet`,
the `convert` command in `commands.py`, and the `convert` CLI branch in `app.main`. Verified by
`tests/test_loader.py` (dtypes, guard message, converter round-trip, streaming-vs-bulk parity) and a
manual RSS check on an 8M-row Parquet.

---

## Two implementation approaches (presented, not chosen) — for the web/out-of-core case

**A. DuckDB-wasm + OPFS.** Store the log as Parquet/tables in OPFS; do range filters and
min/max-per-bucket in SQL. Least bespoke code, but adds a large second wasm runtime (~tens of MB
to download) and moves the decimation math into the DB (still in-browser, but no longer our
pyramid).

**B. On-disk pyramid in OPFS (no DB).** A one-time **streaming ingest** reads the user's file in
chunks via the browser File API (never holding it all in RAM) and writes columnar data plus our
min/max [`Pyramid`](../src/uz_dataviewer/downsample.py) levels into OPFS; the client then reads
small levels/ranges per view. Keeps our existing decimation and needs no heavy dependency, but is
more bespoke out-of-core file code.

**Shared to both:**
- a one-time **ingest pass** is required to get the data into OPFS (time + disk space, subject to
  the browser's OPFS quota);
- the in-app **"windowed run"** abstraction (a run whose arrays are fetched per visible window,
  async + cached, instead of held whole) is the **same** plumbing the cloud feature would use —
  only the *source* differs (local OPFS here vs a remote URL there). The two features are kept
  separate, but this part is worth building once.

## Scope

Substantial: a new run type in [model.py](../src/uz_dataviewer/model.py) and a shift in
[panels/plots.py](../src/uz_dataviewer/panels/plots.py) from per-frame in-memory decimation to an
async windowed fetch + cache. The **native path is unaffected**. The A-vs-B choice is deferred
until this is actually scheduled.
