"""Node graph: a small dataflow engine that turns signals into *derived signals*.

A node is either a **source** (wraps an existing ``(run, signal)`` reference) or a
**transform** (``fft`` / ``math`` / ``filter``). Transforms pull arrays from their
inputs, compute, and -- on explicit evaluation -- **materialize their result as a
new run** in the registry (``derived=True``), so it shows up in Navigation and can
be dragged into plots / FFT / Histogram exactly like a loaded signal. This is the
"derived-signal factory" design: nodes produce data, the rest of the app consumes
it unchanged.

GUI-free and import-light (no GUI, no ``commands``) so the whole engine is driven
and tested from command strings without a window. The canvas UI (``panels/nodes``)
is a thin layer on top that only issues ``node_*`` commands.
"""

from __future__ import annotations

import itertools
from dataclasses import dataclass, field
from typing import Callable

import numpy as np

from .sources import shift_time

from . import transforms
from .analysis import compute_fft

from .validation import parse_bool as _as_bool


# -- transform registry -------------------------------------------------------
# Every transform (builtin *or* plugin) is a TransformSpec in REGISTRY. The engine
# is entirely data-driven from it: available kinds, default params, input arity and
# the compute function are all looked up here, so a plugin that registers a spec is
# indistinguishable from a builtin. "source" is special (not a transform) and is
# never in the registry.
@dataclass
class ParamSpec:
    """Declares one editable parameter so the canvas can render a generic widget
    for built-in and plugin nodes."""

    key: str
    kind: str  # 'float' | 'int' | 'bool' | 'enum' | 'str'
    label: str = ""
    options: tuple[str, ...] = ()  # for 'enum'

    @staticmethod
    def float(key, label=""):
        return ParamSpec(key, "float", label or key)

    @staticmethod
    def int(key, label=""):
        return ParamSpec(key, "int", label or key)

    @staticmethod
    def bool(key, label=""):
        return ParamSpec(key, "bool", label or key)

    @staticmethod
    def enum(key, options, label=""):
        return ParamSpec(key, "enum", label or key, tuple(options))

    @staticmethod
    def str(key, label=""):
        return ParamSpec(key, "str", label or key)


@dataclass
class TransformSpec:
    kind: str
    compute: "Callable"           # (inputs:list[(t,y)], params:dict) -> (t_out, y_out, info)
    params: dict = field(default_factory=dict)  # default params
    inputs: tuple[int, int] = (1, 1)             # (min, max) arity
    ui: tuple = ()                # ParamSpec list (for the generic plugin UI)
    unit: str = ""               # output unit for the derived run


REGISTRY: dict[str, TransformSpec] = {}


def register_transform(spec: TransformSpec) -> None:
    """Register a transform kind (used by builtins at import and by plugins)."""
    if not spec.kind or spec.kind == "source":
        raise ValueError(f"invalid transform kind {spec.kind!r}")
    if spec.kind in REGISTRY:
        raise ValueError(f"Transform {spec.kind!r} is already registered; restart to load a changed plugin")
    REGISTRY[spec.kind] = spec


def transform_kinds() -> tuple[str, ...]:
    """The transform kinds currently available (builtins + loaded plugins)."""
    return tuple(REGISTRY)


def default_params(kind: str) -> dict:
    spec = REGISTRY.get(kind)
    return dict(spec.params) if spec is not None else {}


# -- builtin transforms (registered at import) --------------------------------
def _fft_compute(inputs, params):
    time, y = inputs[0]
    res = compute_fft(
        np.asarray(time, np.float64), np.asarray(y, np.float64),
        float(time[0]), float(time[-1]),
        remove_dc=_as_bool(params.get("remove_dc", True)),
        window=_as_bool(params.get("window", True)),
    )
    if not res.ok:
        raise ValueError(res.info)
    return np.asarray(res.freqs, np.float64), np.asarray(res.mag, np.float64), res.info


def _math_compute(inputs, params):
    return transforms.math_node(inputs, params)


def _filter_compute(inputs, params):
    time, y = inputs[0]
    return transforms.filter_node(time, y, params)


def _shift_compute(inputs, params):
    time, y = inputs[0]
    by = float(params.get("by", 0.0))
    return np.asarray(time, np.float64) + by, np.asarray(y, np.float64), f"shift {by:+g} s"


register_transform(TransformSpec("fft", _fft_compute,
    {"remove_dc": "true", "window": "true"}, (1, 1),
    (ParamSpec.bool("remove_dc", "remove DC"), ParamSpec.bool("window", "Hann"))))
register_transform(TransformSpec("math", _math_compute,
    {"op": "scale", "k": "1.0"}, (1, 2),
    (ParamSpec.enum("op", transforms.MATH_OPS), ParamSpec.float("k"))))
register_transform(TransformSpec("filter", _filter_compute,
    {"type": "low", "cutoff": "0", "cutoff2": "0", "taps": "101"}, (1, 1),
    (ParamSpec.enum("type", transforms.FILTER_TYPES), ParamSpec.float("cutoff", "cutoff Hz"),
     ParamSpec.float("cutoff2", "cutoff2 Hz"), ParamSpec.int("taps"))))
register_transform(TransformSpec("shift", _shift_compute, {"by": "0"}, (1, 1),
    (ParamSpec.float("by", "by (s)"),)))


def validate_parameter(kind, key, value):
    """Share declared parameter validation across commands, evaluation and UI.

    Undeclared plugin parameters remain available to compute-only plugins.
    Empty source crop bounds select the full recording.
    """
    if kind == "source" and key in ("tmin", "tmax"):
        if value == "":
            return
        parameter = ParamSpec.float(key)
    else:
        spec = REGISTRY.get(kind)
        parameter = next((p for p in spec.ui if p.key == key), None) if spec else None
    if parameter is None:
        return
    try:
        if parameter.kind in ("float", "int"):
            number = float(value)
            if not np.isfinite(number):
                raise ValueError("must be finite")
            if parameter.kind == "int" and (not number.is_integer() or not -(2**31) <= number < 2**31):
                raise ValueError("must be a 32-bit integer")
        elif parameter.kind == "bool":
            _as_bool(value)
        elif parameter.kind == "enum" and str(value) not in parameter.options:
            raise ValueError(f"must be one of {parameter.options}")
    except (ValueError, TypeError, OverflowError) as exc:
        raise ValueError(f"{kind}.{key}: invalid value {value!r} ({exc})") from exc


@dataclass
class Node:
    id: int
    kind: str
    name: str
    params: dict = field(default_factory=dict)
    inputs: list[int | None] = field(default_factory=list)  # indexed input slots; None = disconnected
    ref: tuple | None = None  # source nodes only: (run_id, signal_name)
    pos: tuple[float, float] = (0.0, 0.0)

    # -- evaluation caches (never serialised) --
    out_time: np.ndarray | None = field(default=None, repr=False, compare=False)
    out_y: np.ndarray | None = field(default=None, repr=False, compare=False)
    out_run_id: int | None = field(default=None, compare=False)
    version: int = field(default=0, compare=False)  # bumped each recompute
    eval_key: tuple | None = field(default=None, compare=False)
    info: str = field(default="", compare=False)
    error: str = field(default="", compare=False)

    @property
    def is_transform(self) -> bool:
        # Anything that is not a source is a transform -- including an unknown kind
        # from a missing plugin, which then evaluates to a clear error rather than
        # being silently skipped.
        return self.kind != "source"


class NodeGraph:
    """Owns the nodes and hands out stable integer ids (persisted in sessions)."""

    def __init__(self) -> None:
        self.nodes: dict[int, Node] = {}
        self._ids = itertools.count(1)

    # -- mutation ---------------------------------------------------------
    def add(self, kind: str, *, name: str | None = None, ref: tuple | None = None,
            node_id: int | None = None, allow_unknown: bool = False) -> Node:
        # ``allow_unknown`` lets session restore keep a node whose plugin is not
        # installed (a placeholder) instead of dropping it; interactive node_add
        # rejects unknown kinds.
        if kind != "source" and kind not in REGISTRY and not allow_unknown:
            known = ", ".join(("source",) + transform_kinds())
            raise ValueError(f"Unknown node kind {kind!r}; one of {known}")
        nid = node_id if node_id is not None else next(self._ids)
        if nid <= 0 or nid in self.nodes:
            raise ValueError(f"Invalid or duplicate node id: {nid}")
        if name is not None and self.by_name(name) is not None:
            raise ValueError(f"Duplicate node name: {name}")
        if name is None:
            name = f"node_{nid}"
            suffix = 2
            while self.by_name(name) is not None:
                name = f"node_{nid}_{suffix}"
                suffix += 1
        if node_id is not None:  # keep the counter ahead of restored ids
            self._ids = itertools.count(max(nid + 1, self._next_peek()))
        node = Node(id=nid, kind=kind, name=name or f"node_{nid}",
                    params=default_params(kind), ref=ref)
        slot = len(self.nodes)
        node.pos = (30.0 + (slot % 6) * 190.0, 30.0 + (slot // 6) * 150.0)
        self.nodes[nid] = node
        return node

    def _next_peek(self) -> int:
        existing = [n for n in self.nodes] or [0]
        return max(existing) + 1

    def remove(self, node_id: int) -> Node | None:
        node = self.nodes.pop(node_id, None)
        if node is not None:
            for other in self.nodes.values():
                self.unlink(node_id, other.id)
        return node

    def link(self, src_id: int, dst_id: int, slot: int | None = None) -> None:
        if src_id not in self.nodes or dst_id not in self.nodes:
            raise ValueError("link references a node that does not exist")
        dst = self.nodes[dst_id]
        if not dst.is_transform:
            raise ValueError(f"{dst.name} is a source node and takes no inputs")
        if src_id == dst_id or self._reaches(dst_id, src_id):
            raise ValueError("link would create a cycle")
        if slot is None:
            slot = next((i for i, value in enumerate(dst.inputs) if value is None), len(dst.inputs))
        spec = REGISTRY.get(dst.kind)
        if slot < 0 or (spec is not None and slot >= spec.inputs[1]):
            raise ValueError("Input slot is outside the node's input range")
        if slot < len(dst.inputs) and dst.inputs[slot] not in (None, src_id):
            raise ValueError("Input slot is already connected; disconnect it first")
        dst.inputs.extend([None] * (slot + 1 - len(dst.inputs)))
        dst.inputs[slot] = src_id

    def unlink(self, src_id: int, dst_id: int, slot: int | None = None) -> None:
        dst = self.nodes.get(dst_id)
        if dst is not None:
            for i, value in enumerate(dst.inputs):
                if value == src_id and (slot is None or i == slot):
                    dst.inputs[i] = None
            while dst.inputs and dst.inputs[-1] is None:
                dst.inputs.pop()

    def _reaches(self, start: int, target: int) -> bool:
        """True if ``target`` is downstream of ``start`` (follows inputs backwards)."""
        seen: set[int] = set()
        stack = [start]
        while stack:
            cur = stack.pop()
            for other in self.nodes.values():
                if cur in other.inputs and other.id not in seen:
                    if other.id == target:
                        return True
                    seen.add(other.id)
                    stack.append(other.id)
        return False

    # -- lookup -----------------------------------------------------------
    def get(self, node_id: int) -> Node | None:
        return self.nodes.get(node_id)

    def by_name(self, name: str) -> Node | None:
        for node in self.nodes.values():
            if node.name == name:
                return node
        return None

    def ordered(self) -> list[Node]:
        return [self.nodes[i] for i in sorted(self.nodes)]


# -- topology -----------------------------------------------------------------
def _topo_order(graph: NodeGraph) -> list[int]:
    indeg = {nid: 0 for nid in graph.nodes}
    for node in graph.nodes.values():
        for inp in set(node.inputs):
            if inp in graph.nodes:
                indeg[node.id] += 1
    queue = [nid for nid, d in indeg.items() if d == 0]
    order: list[int] = []
    while queue:
        nid = queue.pop(0)
        order.append(nid)
        for other in graph.nodes.values():
            if nid in other.inputs:
                indeg[other.id] -= 1
                if indeg[other.id] == 0:
                    queue.append(other.id)
    if len(order) != len(graph.nodes):
        raise ValueError("node graph has a cycle")
    return order


def _upstream(graph: NodeGraph, node_id: int, acc: set[int]) -> None:
    acc.add(node_id)
    node = graph.nodes.get(node_id)
    if node is None:
        return
    for inp in node.inputs:
        if inp in graph.nodes and inp not in acc:
            _upstream(graph, inp, acc)


# -- output resolution --------------------------------------------------------
def _node_output(state, node: Node) -> tuple[np.ndarray, np.ndarray]:
    """The (time, y) a node exposes: a source reads the registry, a transform
    returns its cached result. Raises if unavailable."""
    if node.kind == "source":
        if node.ref is None:
            raise ValueError(f"{node.name}: no source signal")
        run = state.registry.get(node.ref[0])
        sig = state.registry.get_signal(node.ref[0], node.ref[1])
        if run is None or sig is None:
            raise ValueError(f"{node.name}: source signal is not loaded")
        if run.derived:
            raise ValueError("Derived signals must be connected with node_link, not source nodes")
        source = run.data_source()
        tmin, tmax = node.params.get("tmin", ""), node.params.get("tmax", "")
        lo = float(tmin) if tmin != "" else shift_time(source.metadata.time_range[0], run.time_offset)
        hi = float(tmax) if tmax != "" else shift_time(source.metadata.time_range[1], run.time_offset)
        t, values = run.read_window([node.ref[1]], lo, hi)
        return t, values[node.ref[1]]
    if node.error or is_stale(state.registry, state.nodes, node):
        raise ValueError(f"{node.name}: upstream result is not current")
    if node.out_time is None or node.out_y is None:
        raise ValueError(f"{node.name}: not evaluated yet")
    return node.out_time, node.out_y


def _source_signature(registry, node: Node):
    """Identity of a source's underlying signal (incl. its crop window), for stale
    detection of downstream nodes."""
    window = (node.params.get("tmin", ""), node.params.get("tmax", ""))
    if node.ref is None:
        return ("ref", None, window)
    run = registry.get(node.ref[0])
    signal = registry.get_signal(*node.ref)
    sig = None if run is None or signal is None else (run.time_version, signal.version)
    from .sources import validation_error
    error = validation_error([run.data_source()]) if run is not None else 'Source is missing'
    return ("ref", node.ref, sig, window, error)


def node_key(registry, graph: NodeGraph, node: Node) -> tuple:
    """A hashable key of everything that affects a node's output; a change since
    the last evaluation marks the node stale (UI badge)."""
    parts: list = [node.kind, tuple(sorted(node.params.items()))]
    for in_id in node.inputs:
        up = graph.nodes.get(in_id)
        if up is None:
            parts.append((in_id, "missing"))
        elif up.kind == "source":
            parts.append(_source_signature(registry, up))
        else:
            parts.append((in_id, up.version))
    return tuple(parts)


def is_stale(registry, graph: NodeGraph, node: Node) -> bool:
    """A transform is stale if its own key changed *or* anything upstream is stale.

    Upstream traversal matters: editing a filter's cutoff makes the filter stale, but the
    FFT fed by it is still showing results computed from the *old* filter output -- so
    it must read stale too, even though the filter's version hasn't bumped yet."""
    # Shared upstream nodes must be checked only once per call. Keep the visited
    # set local so edits and source-file changes are visible on the next call.
    pending, visited = [node], set()
    while pending:
        current = pending.pop()
        if current.id in visited or not current.is_transform:
            continue
        visited.add(current.id)
        if current.error or current.eval_key is None or current.eval_key != node_key(registry, graph, current):
            return True
        pending.extend(graph.nodes[i] for i in current.inputs if i in graph.nodes)
    return False


# -- computation --------------------------------------------------------------
def compute_node(node: Node, inputs: list[tuple[np.ndarray, np.ndarray]]
             ) -> tuple[np.ndarray, np.ndarray, str, str]:
    """Dispatch to the node's registered transform. Returns ``(out_time, out_y,
    info, unit)``; raises a clear error if the kind has no spec (missing plugin)."""
    spec = REGISTRY.get(node.kind)
    if spec is None:
        raise ValueError(f"unknown node kind {node.kind!r} -- is its plugin installed?")
    for key, value in node.params.items():
        validate_parameter(node.kind, key, value)
    lo, hi = spec.inputs
    if not (lo <= len(inputs) <= hi):
        want = f"{lo}" if lo == hi else f"{lo}..{hi}"
        raise ValueError(f"{node.kind} needs {want} input(s), got {len(inputs)}")
    # Views protect shared recordings and upstream caches against accidental writes.
    def readonly(array):
        view = np.asarray(array).view()
        view.flags.writeable = False
        return view
    protected = [(readonly(t), readonly(y)) for t, y in inputs]
    out_time, out_y, info = spec.compute(protected, dict(node.params))
    # Own the published buffers: plugins may return aliases or retain references.
    out_time = np.array(out_time, dtype=np.float64, order="C", copy=True)
    out_y = np.array(out_y, dtype=np.float32, order="C", copy=True)
    if out_time.ndim != 1 or out_y.ndim != 1 or out_time.shape != out_y.shape:
        raise ValueError("Node output must contain equal-length one-dimensional time and value arrays")
    from .loader import validate_time_axis
    validate_time_axis(out_time, node.name)
    return out_time, out_y, info, spec.unit


def output_domain(graph, node):
    """Built-in FFT changes domains; other transforms preserve their input axis."""
    if node.kind == "fft":
        return "frequency"
    if node.kind == "source":
        return "time"
    domains = {output_domain(graph, graph.nodes[i]) for i in node.inputs if i in graph.nodes}
    if len(domains) > 1:
        raise ValueError("Cannot combine time and frequency axes")
    return next(iter(domains), "time")


def publish_output(state, node: Node, unit: str = "") -> None:
    """Create/refresh a stable output, including an unavailable empty placeholder."""
    domain = output_domain(state.nodes, node)
    existing = state.registry.get(node.out_run_id) if node.out_run_id is not None else None
    if existing is not None and existing.axis_domain != domain:
        existing.time_origin = None
        existing.axis_domain = domain
        for index, cell in enumerate(state.cells, 1):
            if any(ref[0] == existing.id for ref in cell.signals):
                cell.signals = [ref for ref in cell.signals if ref[0] != existing.id]
                cell.y2_signals = [ref for ref in cell.y2_signals if ref[0] != existing.id]
                cell.x_lim = cell.pending_x_lim = None
                state.plot_x_ranges.pop(index, None)
            if cell.xy_source and cell.xy_source[0] == existing.id:
                cell.xy_source = None
        for cfg in (state.fft, state.histogram):
            cfg.sources = [ref for ref in cfg.sources if ref[0] != existing.id]
    time = node.out_time if node.out_time is not None else np.empty(0, np.float64)
    values = node.out_y if node.out_y is not None else np.empty(0, np.float32)
    node.out_run_id = state.upsert_derived_run(node.name, time, values, unit, run_id=node.out_run_id)
    graph, registry = state.nodes, state.registry

    def validate_output():
        if is_stale(registry, graph, node):
            raise ValueError(f"{node.name}: derived output is not current; evaluate the node ({node.error or 'inputs changed'})")

    run = state.registry.get(node.out_run_id)
    run.axis_domain = output_domain(graph, node)
    run.output_validator = validate_output


def evaluate(state, node_id: int | None = None) -> int:
    """Evaluate the graph (or just ``node_id`` and its upstream), materializing
    each transform's output as a derived run. Returns the number of nodes computed.
    Per-node errors are logged and skipped so one bad node doesn't abort the rest.
    """
    graph: NodeGraph = state.nodes
    order = _topo_order(graph)
    if node_id is not None:
        wanted: set[int] = set()
        _upstream(graph, node_id, wanted)
        order = [nid for nid in order if nid in wanted]

    computed = 0
    for nid in order:
        node = graph.nodes[nid]
        if not node.is_transform:
            continue
        # Skip work that is already up to date. Safe because we go in topo order:
        # if an upstream was just recomputed its version bumps, so this node reads
        # stale (via node_key) and is recomputed; only genuinely-current nodes skip.
        if node.out_y is not None and not is_stale(state.registry, graph, node):
            continue
        try:
            if any(i is None for i in node.inputs):
                raise ValueError("Connect all input slots before evaluating")
            domains = {output_domain(graph, graph.nodes[i]) for i in node.inputs}
            if len(domains) > 1:
                raise ValueError("Cannot combine time and frequency axes")
            requires_time = node.kind in {"fft", "filter", "shift"} or (
                node.kind == "math" and node.params.get("op") in {"derivative", "integral"})
            if requires_time and domains != {"time"}:
                raise ValueError(f"{node.kind} requires time-domain inputs")
            inputs = [_node_output(state, graph.nodes[i]) for i in node.inputs]
            out_time, out_y, info, unit = compute_node(node, inputs)
        except Exception as exc:  # noqa: BLE001 - surfaced to the console
            node.error = str(exc)
            node.info = ""
            state.console.error(f"{node.name}: {exc}")
            continue
        node.out_time = out_time
        node.out_y = out_y
        node.version += 1
        node.info = info
        node.error = ""
        node.eval_key = node_key(state.registry, graph, node)
        publish_output(state, node, unit)
        computed += 1
    return computed
