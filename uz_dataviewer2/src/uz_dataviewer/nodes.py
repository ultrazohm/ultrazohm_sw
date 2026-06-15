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

import numpy as np

from . import transforms
from .analysis import compute_fft

NODE_KINDS = ("source", "fft", "math", "filter")
TRANSFORM_KINDS = ("fft", "math", "filter")

# Per-kind default parameters so a freshly added node has something to compute.
DEFAULT_PARAMS: dict[str, dict] = {
    "source": {},
    "fft": {"remove_dc": "true", "window": "true"},
    "math": {"op": "scale", "k": "1.0"},
    "filter": {"type": "low", "cutoff": "0", "taps": "101"},
}

_TRUE = {"1", "true", "on", "yes"}


def _as_bool(v) -> bool:
    return str(v).strip().lower() in _TRUE


@dataclass
class Node:
    id: int
    kind: str
    name: str
    params: dict = field(default_factory=dict)
    inputs: list[int] = field(default_factory=list)  # upstream node ids
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
        return self.kind in TRANSFORM_KINDS


class NodeGraph:
    """Owns the nodes and hands out stable integer ids (persisted in sessions)."""

    def __init__(self) -> None:
        self.nodes: dict[int, Node] = {}
        self._ids = itertools.count(1)

    # -- mutation ---------------------------------------------------------
    def add(self, kind: str, *, name: str | None = None, ref: tuple | None = None,
            node_id: int | None = None) -> Node:
        if kind not in NODE_KINDS:
            raise ValueError(f"Unknown node kind {kind!r}; one of {', '.join(NODE_KINDS)}")
        nid = node_id if node_id is not None else next(self._ids)
        if node_id is not None:  # keep the counter ahead of restored ids
            self._ids = itertools.count(max(nid + 1, self._next_peek()))
        node = Node(id=nid, kind=kind, name=name or f"node_{nid}",
                    params=dict(DEFAULT_PARAMS.get(kind, {})), ref=ref)
        self.nodes[nid] = node
        return node

    def _next_peek(self) -> int:
        existing = [n for n in self.nodes] or [0]
        return max(existing) + 1

    def remove(self, node_id: int) -> Node | None:
        node = self.nodes.pop(node_id, None)
        if node is not None:
            for other in self.nodes.values():
                other.inputs = [i for i in other.inputs if i != node_id]
        return node

    def link(self, src_id: int, dst_id: int) -> None:
        if src_id not in self.nodes or dst_id not in self.nodes:
            raise ValueError("link references a node that does not exist")
        dst = self.nodes[dst_id]
        if not dst.is_transform:
            raise ValueError(f"{dst.name} is a source node and takes no inputs")
        if src_id == dst_id or self._reaches(dst_id, src_id):
            raise ValueError("link would create a cycle")
        if src_id not in dst.inputs:
            dst.inputs.append(src_id)

    def unlink(self, src_id: int, dst_id: int) -> None:
        dst = self.nodes.get(dst_id)
        if dst is not None:
            dst.inputs = [i for i in dst.inputs if i != src_id]

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
        for inp in node.inputs:
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
        return run.time, sig.y
    if node.out_time is None or node.out_y is None:
        raise ValueError(f"{node.name}: not evaluated yet")
    return node.out_time, node.out_y


def _source_signature(state, node: Node):
    """Identity of a source's underlying signal, for stale detection."""
    if node.ref is None:
        return ("ref", None)
    run = state.registry.get(node.ref[0])
    return ("ref", node.ref, None if run is None else (run.n_rows, run.time_origin))


def node_key(state, graph: NodeGraph, node: Node) -> tuple:
    """A hashable key of everything that affects a node's output; a change since
    the last evaluation marks the node stale (UI badge)."""
    parts: list = [node.kind, tuple(sorted(node.params.items()))]
    for in_id in node.inputs:
        up = graph.nodes.get(in_id)
        if up is None:
            parts.append((in_id, "missing"))
        elif up.kind == "source":
            parts.append(_source_signature(state, up))
        else:
            parts.append((in_id, up.version))
    return tuple(parts)


def is_stale(state, graph: NodeGraph, node: Node) -> bool:
    return node.is_transform and node.eval_key != node_key(state, graph, node)


# -- computation --------------------------------------------------------------
def _compute(node: Node, inputs: list[tuple[np.ndarray, np.ndarray]]
             ) -> tuple[np.ndarray, np.ndarray, str, str]:
    """Returns ``(out_time, out_y, info, unit)`` for a transform node."""
    if node.kind == "fft":
        if len(inputs) != 1:
            raise ValueError(f"fft needs exactly 1 input, got {len(inputs)}")
        time, y = inputs[0]
        res = compute_fft(
            np.asarray(time, np.float64), np.asarray(y, np.float64),
            float(time[0]), float(time[-1]),
            remove_dc=_as_bool(node.params.get("remove_dc", True)),
            window=_as_bool(node.params.get("window", True)),
        )
        if not res.ok:
            raise ValueError(res.info)
        return (np.asarray(res.freqs, np.float64), np.asarray(res.mag, np.float64),
                res.info, "")
    if node.kind == "math":
        t, y, info = transforms.math_node(inputs, node.params)
        return t, y, info, ""
    if node.kind == "filter":
        if len(inputs) != 1:
            raise ValueError(f"filter needs exactly 1 input, got {len(inputs)}")
        time, y = inputs[0]
        t, out, info = transforms.filter_node(time, y, node.params)
        return t, out, info, ""
    raise ValueError(f"{node.name}: kind {node.kind!r} is not computable")


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
        try:
            inputs = [_node_output(state, graph.nodes[i]) for i in node.inputs]
            out_time, out_y, info, unit = _compute(node, inputs)
        except Exception as exc:  # noqa: BLE001 - surfaced to the console
            node.error = str(exc)
            node.info = ""
            state.console.error(f"{node.name}: {exc}")
            continue
        node.out_time = np.ascontiguousarray(out_time, np.float64)
        node.out_y = np.ascontiguousarray(out_y, np.float32)
        node.version += 1
        node.info = info
        node.error = ""
        node.eval_key = node_key(state, graph, node)
        node.out_run_id = state.upsert_derived_run(node.name, node.out_time, node.out_y, unit)
        computed += 1
    return computed
