"""Nodes window: a visual canvas over the dataflow engine (:mod:`uz_dataviewer.nodes`).

Drag a signal from Navigation onto the drop target to add a **source** node; add
**fft / math / filter** transforms from the toolbar; wire outputs to inputs; press
**Evaluate** to materialize each transform's result as a derived signal (it appears
in Navigation, draggable into any plot). Built on ``imgui_node_editor`` following the
bundled ``demo_node_editor_basic`` pattern.

Like every panel, this one only **issues commands** (``node_*``) -- it never mutates
the graph directly -- so the canvas, the console and ``.uzscript`` stay in lock-step.
"""

from __future__ import annotations

from imgui_bundle import imgui
from imgui_bundle import imgui_node_editor as ed

from ..nodes import TRANSFORM_KINDS, is_stale
from ..state import AppState
from ..transforms import FILTER_TYPES, MATH_OPS, MATH_UNARY
from .navigation import SIGNAL_DND_TYPE

# Disjoint id ranges so node / pin / link ids never collide in the editor.
_OUT_BASE = 1_000_000
_IN_BASE = 2_000_000
_LINK_BASE = 3_000_000
_INPUTS = {"source": 0, "fft": 1, "filter": 1, "math": 2}
_TRUE = {"1", "true", "on", "yes"}


def _out_pin(node_id: int) -> int:
    return _OUT_BASE + node_id


def _in_pin(node_id: int, slot: int) -> int:
    return _IN_BASE + node_id * 10 + slot


def _decode_pin(pid: int) -> tuple[str, int]:
    if _OUT_BASE <= pid < _IN_BASE:
        return "out", pid - _OUT_BASE
    if pid >= _IN_BASE:
        return "in", (pid - _IN_BASE) // 10
    return "?", 0


def _link_id(src: int, dst: int) -> int:
    return _LINK_BASE + src * 1000 + dst


def _decode_link(lid: int) -> tuple[int, int]:
    v = lid - _LINK_BASE
    return v // 1000, v % 1000


def _b(params: dict, key: str, default: bool) -> bool:
    return str(params.get(key, default)).strip().lower() in _TRUE


class NodesPanel:
    def __init__(self) -> None:
        self._positioned: set[int] = set()
        self._last_pos: dict[int, tuple[float, float]] = {}

    # -- command helper -----------------------------------------------------
    def _emit(self, state: AppState, name: str, *args) -> None:
        try:
            state.commands.execute(state, name, list(args))
        except Exception as exc:  # noqa: BLE001 - surfaced to the console
            state.console.error(str(exc))

    # -- toolbar ------------------------------------------------------------
    def _toolbar(self, state: AppState) -> None:
        imgui.button("[ drop signal here -> +source ]")
        if imgui.begin_drag_drop_target():
            if imgui.accept_drag_drop_payload_py_id(SIGNAL_DND_TYPE) is not None:
                ref = getattr(state, "dragged_ref", None)
                if ref is not None:
                    self._emit(state, "node_source", ref[0], ref[1])
            imgui.end_drag_drop_target()

        for kind in TRANSFORM_KINDS:
            imgui.same_line()
            if imgui.button(f"+ {kind}"):
                self._emit(state, "node_add", kind)

        imgui.same_line()
        imgui.text("|")
        imgui.same_line()
        if imgui.button("Evaluate"):
            self._emit(state, "node_eval")
        imgui.same_line()
        if imgui.button("Clear") and state.nodes.nodes:
            for nid in list(state.nodes.nodes):
                self._emit(state, "node_remove", nid)
            self._positioned.clear()
        imgui.same_line()
        imgui.text_disabled(f"{len(state.nodes.nodes)} node(s)")

    # -- one node -----------------------------------------------------------
    def _draw_node(self, state: AppState, node) -> None:
        nid = node.id
        if nid not in self._positioned:
            px, py = node.pos
            if (px, py) == (0.0, 0.0):  # fresh node: cascade so they don't stack
                slot = len(self._positioned)
                px, py = 30.0 + (slot % 6) * 190.0, 30.0 + (slot // 6) * 150.0
            ed.set_node_position(ed.NodeId(nid), imgui.ImVec2(px, py))
            self._positioned.add(nid)

        ed.begin_node(ed.NodeId(nid))
        imgui.push_id(nid)
        imgui.text(f"{node.name}  ({node.kind})")
        if is_stale(state, state.nodes, node):
            imgui.same_line()
            imgui.text_colored((0.95, 0.75, 0.25, 1.0), "(stale)")

        for slot in range(_INPUTS.get(node.kind, 1)):
            ed.begin_pin(ed.PinId(_in_pin(nid, slot)), ed.PinKind.input)
            imgui.text("-> in" if _INPUTS[node.kind] == 1 else f"-> in{slot + 1}")
            ed.end_pin()

        self._params(state, node)

        ed.begin_pin(ed.PinId(_out_pin(nid)), ed.PinKind.output)
        if node.kind == "source":
            imgui.text(f"{node.ref[1] if node.ref else '?'}  out ->")
        else:
            imgui.text("out ->")
        ed.end_pin()

        if node.error:
            imgui.text_colored((0.95, 0.4, 0.4, 1.0), node.error[:40])
        elif node.info:
            imgui.text_disabled(node.info[:40])
        if node.kind != "source" and imgui.small_button("eval"):
            self._emit(state, "node_eval", nid)

        imgui.pop_id()
        ed.end_node()

        pos = ed.get_node_position(ed.NodeId(nid))
        self._maybe_echo_pos(state, nid, float(pos.x), float(pos.y))

    def _params(self, state: AppState, node) -> None:
        imgui.push_item_width(120)
        p = node.params
        if node.kind == "fft":
            ch, on = imgui.checkbox("remove DC", _b(p, "remove_dc", True))
            if ch:
                self._emit(state, "node_set", node.id, "remove_dc", "true" if on else "false")
            ch, on = imgui.checkbox("Hann", _b(p, "window", True))
            if ch:
                self._emit(state, "node_set", node.id, "window", "true" if on else "false")
        elif node.kind == "math":
            self._combo(state, node, "op", "##op", list(MATH_OPS))
            if str(p.get("op", "scale")) in ("scale", "offset"):
                self._float(state, node, "k", "k")
        elif node.kind == "filter":
            self._combo(state, node, "type", "##ft", list(FILTER_TYPES))
            self._float(state, node, "cutoff", "cutoff Hz")
            if str(p.get("type", "low")) == "band":
                self._float(state, node, "cutoff2", "cutoff2 Hz")
            self._int(state, node, "taps", "taps")
        imgui.pop_item_width()

    # -- param widgets (each emits node_set) --------------------------------
    def _combo(self, state, node, key, label, options) -> None:
        cur = str(node.params.get(key, options[0]))
        idx = options.index(cur) if cur in options else 0
        changed, idx = imgui.combo(label, idx, options)
        if changed:
            self._emit(state, "node_set", node.id, key, options[idx])

    def _float(self, state, node, key, label) -> None:
        try:
            val = float(node.params.get(key, 0.0))
        except ValueError:
            val = 0.0
        changed, val = imgui.input_float(label, val)
        if changed:
            self._emit(state, "node_set", node.id, key, f"{val:g}")

    def _int(self, state, node, key, label) -> None:
        try:
            val = int(float(node.params.get(key, 0)))
        except ValueError:
            val = 0
        changed, val = imgui.input_int(label, val)
        if changed:
            self._emit(state, "node_set", node.id, key, str(val))

    # -- position echo (settle on mouse-up, like zoom) ----------------------
    def _maybe_echo_pos(self, state: AppState, nid: int, x: float, y: float) -> None:
        if imgui.is_mouse_down(0):
            return
        last = self._last_pos.get(nid)
        if last is not None and abs(last[0] - x) < 1.0 and abs(last[1] - y) < 1.0:
            return
        first = last is None
        self._last_pos[nid] = (x, y)
        if not first:  # don't log the initial placement
            self._emit(state, "node_pos", nid, x, y)

    # -- link create / delete ----------------------------------------------
    def _handle_create(self, state: AppState) -> None:
        if ed.begin_create():
            a, b = ed.PinId(), ed.PinId()
            if ed.query_new_link(a, b) and a and b:
                if ed.accept_new_item():
                    self._try_link(state, a.id(), b.id())
            ed.end_create()

    def _try_link(self, state: AppState, pa: int, pb: int) -> None:
        ka, na = _decode_pin(pa)
        kb, nb = _decode_pin(pb)
        if ka == "out" and kb == "in":
            self._emit(state, "node_link", na, nb)
        elif ka == "in" and kb == "out":
            self._emit(state, "node_link", nb, na)

    def _handle_delete(self, state: AppState) -> None:
        if ed.begin_delete():
            lid = ed.LinkId()
            while ed.query_deleted_link(lid):
                if ed.accept_deleted_item():
                    src, dst = _decode_link(lid.id())
                    self._emit(state, "node_unlink", src, dst)
            nid = ed.NodeId()
            while ed.query_deleted_node(nid):
                if ed.accept_deleted_item():
                    self._emit(state, "node_remove", nid.id())
                    self._positioned.discard(nid.id())
            ed.end_delete()

    # -- panel --------------------------------------------------------------
    def render(self, state: AppState) -> None:
        self._toolbar(state)
        imgui.separator()
        ed.begin("##nodes", imgui.ImVec2(0.0, 0.0))
        for node in state.nodes.ordered():
            self._draw_node(state, node)
        for node in state.nodes.ordered():
            for slot, in_id in enumerate(node.inputs):
                if in_id in state.nodes.nodes:
                    ed.link(ed.LinkId(_link_id(in_id, node.id)),
                            ed.PinId(_out_pin(in_id)), ed.PinId(_in_pin(node.id, slot)))
        self._handle_create(state)
        self._handle_delete(state)
        ed.end()
