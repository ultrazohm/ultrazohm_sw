# Nodes — known limitations & future ideas

> Part of the [roadmap](ROADMAP.md). The deep dive for the node graph's open edges.

Captured 2026-06-15 from a critical review of the node-graph feature (engine in
[nodes.py](../src/uz_dataviewer/nodes.py) / [transforms.py](../src/uz_dataviewer/transforms.py),
canvas in [panels/nodes.py](../src/uz_dataviewer/panels/nodes.py)). The review **fixed** three
items before this list: transitive staleness (a downstream node now reads `(stale)` when an
upstream changes), op-aware input-pin count on `math` nodes, and skip-fresh evaluation
(`node_eval` only recomputes stale nodes). The items below are **not** core-path bugs — they are
edges and polish, left as documented follow-ups.

## A. Binary math input order is implicit (connection order)
`A-B` / `A/B` take `inputs[0]` and `inputs[1]` in the order the links were **created**, not by
which input pin (`in1`/`in2`) the user dropped onto. The editor *does* tell us the target slot in
`query_new_link`, but `NodesPanel._try_link` currently ignores it and `node_link` just appends.
- **Severity:** low–medium (wrong order silently swaps A and B).
- **Fix:** decode the dropped input slot and have `node_link` place the source at that index
  (needs `node_link` to carry an optional slot → small command-grammar change).

## B. FFT-derived run's x-axis is frequency but plots label it "time"
An `fft` node's derived run uses `time = freqs`, so dropping it into a time-series cell shows a
spectrum under an x-axis labelled "time", and **Link X** would couple a frequency axis to time
axes.
- **Severity:** low (cosmetic / semantic).
- **Fix:** tag derived runs with an x-axis kind/label; have `PlotsPanel` honour it and exclude
  frequency-axis runs from link-X. (Or simply view FFT-derived signals on their own.)

## C. Units are not propagated to derived signals
Every derived signal is created with unit `""`. For `filter` and `offset` the physical unit is
unchanged and could be carried over; `scale`/`derivative`/`integral` change it.
- **Severity:** low.
- **Fix:** pass the input unit through for unit-preserving ops in `nodes._compute` /
  `upsert_derived_run`.

## D. Name / label collisions
Derived runs are labelled by node name (`node_<id>` by default). If a loaded file is named like a
node, or two nodes are renamed to the same label, `_label_to_run_id` resolves to the first match.
`node_rename` checks other **node** names but not loaded **run** labels.
- **Severity:** low (needs a deliberate clash).
- **Fix:** validate node names against `registry` labels too; reject duplicates.

## E. Source-on-derived chaining is fragile across restore/script
Making a **source** node that wraps *another node's* derived run works at runtime (the run id is
valid) but may not survive save/restore or `.uzscript` replay, because the derived run does not
exist until its producing node is evaluated. Chaining is meant to go through `node_link`
(transform → transform), which is robust.
- **Severity:** low.
- **Fix:** either resolve such source refs lazily at eval time, or block creating a source from a
  derived run and steer users to `node_link`.

---

## Implemented after this review (for the record)
- **Double-click a node to rename** its output signal (the derived run takes the new name).
- **Drag a signal from Navigation straight onto the canvas** to add a source node at the drop point.
- **math `add`** (A+B) alongside sub/div; **`shift` node** (offset the time axis by a constant);
  **source `crop time`** (optional `tmin`/`tmax` so a source uses only a window of its record).

---

## Custom-code nodes (planned — feasibility assessment)

**Question:** can a node run user-written Python (typed at runtime, or supplied externally after
build)? **Answer: yes, and it's reasonable** — the app already *is* CPython at runtime (native:
the PyInstaller-frozen interpreter; web: Pyodide/CPython-in-WASM), so `exec`/`importlib` work on
both targets without bundling a second interpreter. The transform contract is already a pure
function `(inputs, params) -> (out_time, out_y, info)`, so a code node is "just another transform
whose body is user-supplied." Two designs, with the trade-offs that actually matter here:

### Option B (recommended): external plugin files
Load `.py` files from a known directory (e.g. `~/.uz_dataviewer/nodes/` or a `plugins/` folder next
to the binary) at startup; each registers a transform (a function + a small metadata dict: kind
name, default params). `nodes._compute` dispatches to it by kind.
- **Native:** works directly — a frozen PyInstaller app can `importlib` arbitrary `.py` from disk
  as long as their imports (numpy) are bundled.
- **Web:** no real FS; a plugin would have to be fetched/uploaded then `exec`'d — possible but less
  natural; could be a later addition.
- **Serialization:** clean — the graph references a *kind name*, never embeds code, so `.uzscript`
  and JSON round-trip unchanged.
- **Security:** plugins are files the user deliberately installed (same trust as `pip install`); a
  shared *session* stays data-only.
- **Effort:** small-to-medium. Fits the documented "add a transform" extension path exactly.

### Option A: inline code typed into the node
A `code` node kind with a multiline text field; the body runs in a namespace with `t`, `y`
(inputs) and `np`, returning `(t_out, y_out)`.
- **Feasible** and great for quick experiments, but two real frictions:
  1. **Grammar:** the command layer is flat `name(a, b, …)` calls split on commas — it cannot carry
     multiline code. So `node_set(node, code, …)` and `.uzscript` replay would need a special
     code-block mechanism; only the **JSON snapshot** stores it cleanly. I.e. inline-code nodes
     would be **JSON-session-only, not fully console-scriptable** in v1.
  2. **Trust:** a saved session would now contain *executable* code; loading someone else's session
     becomes "run their code." Needs a load-time warning and/or a "disable code nodes from untrusted
     sessions" switch. (On web the Pyodide sandbox limits the blast radius; on native it's full
     local privileges.)
- **Effort:** medium, mostly the grammar/serialization special-case and the trust UX.

### Recommendation
Do **Option B first** (plugin files): clean serialization, proper multiline code, opt-in security,
and it slots straight into the existing transform model. Add **Option A** later as an "advanced"
feature, scoped as JSON-session-only with an explicit trust warning, if interactive in-app scripting
proves worth the grammar/security work. Neither requires a new interpreter — just a registration
hook in `nodes.py` and (for A) a code-carrying param path that bypasses the flat command grammar.

> **Update:** Option B (external plugin files) **shipped** — a transform `REGISTRY` in
> `nodes.py`, the `@transform` / `ParamSpec` API, a tolerant loader (`plugins.py`,
> `$UZ_DATAVIEWER_PLUGINS` + `~/.uz_dataviewer/nodes/` + `load_plugins([dir])`), a generic
> param UI, and unknown-kind placeholders on restore. See **[PLUGINS.md](PLUGINS.md)**.
> Option A (inline-code nodes) above remains the open idea.
