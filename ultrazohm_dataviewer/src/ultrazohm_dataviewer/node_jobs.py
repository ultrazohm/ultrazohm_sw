"""Detached node evaluation with application-thread publication."""

from copy import copy, deepcopy
from dataclasses import dataclass, field

from . import nodes
from .console import Console
from .model import DataRegistry


@dataclass
class EvaluationState:
    """Detached graph inputs and computed outputs, with no GUI runtime state."""

    nodes: nodes.NodeGraph
    registry: DataRegistry
    console: Console = field(default_factory=Console)

    def upsert_derived_run(self, label, time, signal_y, unit="", *, run_id=None):
        return self.registry.upsert_derived_run(
            label, time, signal_y, unit, run_id=run_id
        )

    def derived_domain_changed(self, run_id):
        # View changes are applied only when publishing to the application.
        pass


def fingerprint(state):
    """Include computational inputs, not presentation-only edits or plot layout."""
    return tuple(
        (
            node.id,
            id(node),
            node.kind,
            deepcopy(node.params),
            tuple(node.inputs),
            node.ref,
            node.version,
            node.out_run_id,
            nodes._source_signature(state.registry, node)
            if node.kind == "source"
            else None,
        )
        for node in state.nodes.nodes.values()
    )


def capture(state):
    graph = copy(state.nodes)
    graph.nodes = {}
    for key, original in state.nodes.nodes.items():
        node = copy(original)
        node.params = deepcopy(original.params)
        node.inputs = list(original.inputs)
        graph.nodes[key] = node
    return EvaluationState(graph, state.registry.detached())


def publish(state, snapshot):
    computed = 0
    for nid in nodes._topo_order(snapshot.nodes):
        result = snapshot.nodes.nodes[nid]
        node = state.nodes.nodes[nid]
        if not node.is_transform:
            continue
        node.error, node.info = result.error, result.info
        if node.error:
            state.console.error(f"{node.name}: {node.error}")
        if node.version == result.version:
            continue
        node.out_time, node.out_y = result.out_time, result.out_y
        node.version = result.version
        node.eval_key = nodes.node_key(state.registry, state.nodes, node)
        run = snapshot.registry.get(result.out_run_id)
        nodes.publish_output(
            state, node, run.signals["out"].unit, domain=run.axis_domain
        )
        state.registry.get(
            node.out_run_id
        ).timestamp_resolution = run.timestamp_resolution
        computed += 1
    return computed
