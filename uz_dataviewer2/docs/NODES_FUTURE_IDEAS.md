# Nodes — known limitations & future ideas

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

---

## Plugin system (external transform nodes) — ✅ IMPLEMENTED (2026-06)

**Built — see [PLUGINS.md](PLUGINS.md).** Option B shipped: a transform `REGISTRY` in `nodes.py`
(builtins + plugins), the `@transform` / `ParamSpec` API and a tolerant loader in `plugins.py`
(`$UZ_DATAVIEWER_PLUGINS` + `~/.uz_dataviewer/nodes/`, plus a `load_plugins([dir])` command), a
generic `ParamSpec` UI for plugin nodes, and unknown-kind placeholders on restore. The design
sketch below is kept for context. *(Option A, inline-code nodes, remains a future idea.)*

### Original design sketch (Option B)

Goal: a user drops a `.py` file in a folder and a new transform node type appears, fully working
through the canvas, commands, evaluation, and sessions — with **no change** to the command grammar
or save format.

### The enabling refactor: a transform registry
Today `nodes.py` hardcodes transforms in four places (`TRANSFORM_KINDS`, `DEFAULT_PARAMS`,
`_INPUTS`/arity, and the `if node.kind == …` chain in `_compute`), plus bespoke widgets in
`NodesPanel._params`. Replace those with **one registry** that builtins and plugins both populate:

```python
# nodes.py (sketch)
@dataclass
class TransformSpec:
    kind: str                       # unique id, e.g. "fft", "movavg"
    compute: Callable               # (inputs:list[(t,y)], params:dict) -> (t_out, y_out, info)
    params: dict                    # default params, e.g. {"window": "101"}
    inputs: tuple[int, int]         # (min, max) arity, e.g. (1, 1) or (2, 2)
    ui: list[ParamSpec] = ()        # optional: how the canvas renders each param
    unit: str = "passthrough"       # output unit policy

REGISTRY: dict[str, TransformSpec] = {}
def register_transform(spec): REGISTRY[spec.kind] = spec
```

The builtins (`fft`/`math`/`filter`/`shift`) register themselves at import. `_compute`,
`TRANSFORM_KINDS`, `DEFAULT_PARAMS`, and arity all become lookups into `REGISTRY`. Once this is
data-driven, a plugin that calls `register_transform(...)` is indistinguishable from a builtin.

### Plugin file contract
A plugin is a `.py` module that registers one or more transforms via a tiny public API:

```python
# ~/.uz_dataviewer/nodes/movavg.py
import numpy as np
from uz_dataviewer.plugins import transform, ParamSpec, API_VERSION   # stable, documented surface

@transform(
    kind="movavg",
    params={"width": "51"},
    inputs=(1, 1),
    ui=[ParamSpec.int("width", "window (samples)", min=1)],
)
def moving_average(inputs, params):
    t, y = inputs[0]
    w = max(1, int(float(params["width"])))
    k = np.ones(w) / w
    return t, np.convolve(np.asarray(y, float), k, mode="same"), f"moving avg {w}"
```

The contract mirrors `transforms.math_node` exactly, so existing transforms could even be expressed
as plugins. `API_VERSION` lets a plugin declare compatibility; loader skips mismatches with a notice.

### Discovery & loading
At startup (after the core registers builtins, before the first frame): scan, in order,
`$UZ_DATAVIEWER_PLUGINS` (colon-separated), `~/.uz_dataviewer/nodes/`, and a `plugins/` folder next
to the executable / CWD. For each `.py`, `importlib`-load it in a try/except so **one broken plugin
logs an error and is skipped** rather than taking down startup. Reject a `kind` that clashes with a
builtin or an already-loaded plugin (first wins, warn). Log "Loaded N plugin transform(s)" to the
console. numpy (and pyarrow) are already bundled, so plugins relying on them work in the frozen app.

### Generic param UI
`NodesPanel._params` gains a fallback that renders from `spec.ui` (a list of typed `ParamSpec`:
`float` / `int` / `bool` / `enum(options)` / `str`), each emitting `node_set` like today. Builtins
can migrate to `ParamSpec` or keep their bespoke widgets; plugins always use the generic path. No
plugin UI code needed beyond declaring its params.

### Commands, evaluation, sessions — unchanged
- `node_add(<kind>)` validates against the registry, so any plugin kind just works; `node_set`
  already carries arbitrary params; `node_eval` dispatches through `REGISTRY[kind].compute`.
- **Serialization references the kind name only** — `.uzscript` and JSON round-trip with zero
  changes. The one new rule: on **load with a missing plugin**, don't drop the node — keep it as a
  greyed-out *unknown(kind)* placeholder that **preserves its params and links**, so re-installing
  the plugin and re-evaluating restores it. (Add an `unknown` render path + an "N nodes need plugin
  X" console warning.)

### Native vs web
- **Native:** works directly (disk dirs + `importlib`).
- **Web (Pyodide):** no real FS for user files. Later options: fetch a configured list of plugin
  URLs, or a paste/upload box that writes into the Pyodide FS before `importlib`. v1 = native-only;
  the registry refactor is platform-agnostic so web can follow.

### Security
Plugins are code the user deliberately installed (same trust level as `pip install <pkg>`), and a
shared **session never contains code** (only kind names + params), so opening someone else's graph
is still data-only. Document the trust model; optionally a `--no-plugins` / settings switch to skip
loading. (This is the key advantage over inline-code nodes, which embed executable code in sessions.)

### Rough effort & order
1. Registry refactor of the four builtins (no behaviour change) — the bulk of the work, and a good
   cleanup on its own.
2. `uz_dataviewer.plugins` public API (`transform` decorator, `ParamSpec`, `API_VERSION`).
3. Discovery/loader with per-file error isolation.
4. Generic `ParamSpec` UI renderer + `unknown`-kind placeholder on load.
5. Docs: a "Writing a node plugin" page with the example above; ship one sample plugin.
