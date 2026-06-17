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

## Decided plan for **native** large logs (up to ~100M points) — for later implementation

This is the realistic target (native, both **CSV and Parquet**, up to ~100M points). The data
stays **in RAM** so FFT / node transforms / histogram keep working — they each need the full
window's raw samples in RAM (a full-record `rfft` even adds ~2–3 GB transient at 100M). Going
out-of-core here would force a segmented/Welch FFT + a nodes rework — much larger effort. At 100M
the ~8.8 GB resident fits native RAM; the only real problem is the **load peak**, so we just load
leanly. (Out-of-core, below, is reserved for the web/larger-than-RAM case.)

Key simplification: **cap CSV at ~10M rows and require Parquet above that.** This removes the
hard part of streaming (assembling in-memory arrays from a CSV with no row count) — only Parquet
needs streaming, and Parquet is the easy case.

**Status:** float32 channel parsing is **DONE** (`_csv_column_types` in `loader.py`). The rest is
pending.

1. **CSV — keep the simple bulk loader, guarded to ~10M rows.**
   - ≤10M CSV ≈ 0.88 GB numeric; bulk `pyarrow.csv.read_csv` + float32 peaks ~2–3 GB — fine, no
     streaming.
   - Add a guard in `load_csv`: if the file is too large (size proxy, ~1 GB ≈ ~10M rows at ~99 B/
     row for 20 channels), refuse with a clear message and route to Parquet / the converter
     (prevents OOM on, e.g., a 50M-row CSV).

2. **Parquet — streaming load (the easy case), up to ~100M.**
   - `pyarrow.parquet.ParquetFile(path).metadata.num_rows` gives the **exact** row count for free
     → preallocate the output arrays exactly (no grow-and-trim).
   - `iter_batches(columns=…)` streams row groups; cast each batch column to **float32** (time →
     float64) into the preallocated arrays; discard the batch.
   - Peak ≈ resident + one batch (~1×). Replaces the bulk `pq.read_table` → `_table_to_run` path
     for large files (bulk is fine to keep for small Parquet).

3. **CSV→Parquet converter (because JavaScope only emits CSV).**
   - Streaming, bounded memory, ~15 lines: `pyarrow.csv.open_csv(...)` → for each batch cast to
     float32 → `pyarrow.parquet.ParquetWriter.write_batch(...)`. No row count, no preallocation.
   - **Open UX decision (lean: auto-convert on open).** Either auto-convert a big CSV when opened
     ("large CSV — converting to Parquet once…", cache the `.parquet` beside the source and load
     that), or a separate `uz-dataviewer convert` script/command. Keep it scriptable either way.

**Web is unchanged by this:** even as Parquet, 100M (~8.8 GB) can't fit Pyodide's 4 GB heap
(Arrow builds the whole table), so web large logs still need the out-of-core route below. This
plan is **native-only**.

**Touch points:** `loader.load_csv` (size guard), `loader.load_parquet` (streaming +
preallocation + per-batch float32), a new converter helper, and `state.request_load` /
`panels/navigation.py` for the auto-convert UX + a command. `_table_to_run` / `_csv_column_types`
already do the float32 / time-float64 split. Verify with: a generated ~20–50M Parquet loads at
~1× peak (measure RSS vs `num_rows × 88 B`), FFT over the full record still works, and an oversize
CSV is refused (or auto-converted) rather than OOM-ing.

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
