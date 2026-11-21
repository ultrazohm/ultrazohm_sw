"""Detached node evaluation with application-thread publication."""

import itertools
from copy import copy, deepcopy
from types import MethodType, SimpleNamespace

from . import nodes
from .console import Console
from .state import AppState


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
    registry = copy(state.registry)
    registry._ids = itertools.count(max(state.registry._runs, default=0) + 1)
    registry._runs = {}
    for key, original in state.registry._runs.items():
        run = copy(original)
        run.signals = {name: copy(signal) for name, signal in original.signals.items()}
        # ArraySource.validator is mutable; detached publication must not
        # replace the live source's validation closure.
        run.source = copy(original.source)
        registry._runs[key] = run
    snapshot = SimpleNamespace(
        nodes=graph,
        registry=registry,
        console=Console(),
        cells=[],
        plot_x_ranges={},
        fft=SimpleNamespace(sources=[]),
        histogram=SimpleNamespace(sources=[]),
    )
    snapshot.upsert_derived_run = MethodType(AppState.upsert_derived_run, snapshot)
    return snapshot


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
