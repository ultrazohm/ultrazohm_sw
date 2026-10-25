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

from ..nodes import REGISTRY, is_stale, transform_kinds
from ..state import AppState
from ..transforms import MATH_BINARY
from .base import SessionPanel
from .navigation import SIGNAL_DND_TYPE

# Editor IDs use two tag bits: node=0, output=1, input=2, link=3.
# Pairing node/slot indices avoids fixed limits and overlapping input slots.
from ..validation import parse_bool


def _pair(a: int, b: int) -> int:
    return (a + b) * (a + b + 1) // 2 + b


def _unpair(value: int) -> tuple[int, int]:
    from math import isqrt
    total = (isqrt(8 * value + 1) - 1) // 2
    b = value - total * (total + 1) // 2
    return total - b, b


def _out_pin(node_id: int) -> int:
    return node_id * 4 + 1


def _in_pin(node_id: int, slot: int) -> int:
    return _pair(node_id, slot) * 4 + 2


def _decode_pin(pid: int) -> tuple[str, int, int | None]:
    if pid % 4 == 1:
        return "out", pid // 4, None
    if pid % 4 == 2:
        node, slot = _unpair(pid // 4)
        return "in", node, slot
    return "?", 0, None


def _link_id(dst: int, slot: int) -> int:
    return _pair(dst, slot) * 4 + 3


def _decode_link(lid: int) -> tuple[int, int]:
    return _unpair(lid // 4)


def _b(params: dict, key: str, default: bool) -> bool:
    try:
        return parse_bool(params.get(key, default))
    except ValueError:
        # Preserve malformed session/plugin values for repair; evaluation reports them.
        return default


def _input_pin_count(node) -> int:
    """How many input pins to draw: the kind's arity, but never fewer than the
    links already attached (so existing links always have a pin to render to)."""
    if node.kind == "source":
        base = 0
    elif node.kind == "math":  # op-dependent: unary vs binary
        base = 2 if str(node.params.get("op", "scale")) in MATH_BINARY else 1
    else:
        spec = REGISTRY.get(node.kind)
        base = spec.inputs[1] if spec is not None else 1  # max arity (unknown -> 1)
    return max(base, len(node.inputs))


class NodesPanel(SessionPanel):
    def __init__(self) -> None:
        self._positioned: set[int] = set()
        self._model_positions: dict[int, tuple[float, float]] = {}
        self._last_pos: dict[int, tuple[float, float]] = {}
        self._renaming: int | None = None   # node whose name is being edited inline
        self._rename_buf: str = ""
        self._rename_focus: bool = False

    # -- toolbar ------------------------------------------------------------
    def _toolbar(self, state: AppState) -> None:
        imgui.text_disabled("drag a signal onto the canvas to add a source")
        imgui.same_line()
        imgui.text("|")
        for kind in transform_kinds():
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
        if nid not in self._positioned or self._model_positions.get(nid) != node.pos:
            self._model_positions[nid] = node.pos
            px, py = node.pos
            ed.set_node_position(ed.NodeId(nid * 4), imgui.ImVec2(px, py))
            self._positioned.add(nid)
            self._last_pos[nid] = (px, py)

        ed.begin_node(ed.NodeId(nid * 4))
        imgui.push_id(nid)
        if self._renaming == nid:
            self._rename_field(state)
        else:
            imgui.text(f"{node.name}  ({node.kind})")
            if is_stale(state.registry, state.nodes, node):
                imgui.same_line()
                imgui.text_colored((0.95, 0.75, 0.25, 1.0), "(stale)")

        n_in = _input_pin_count(node)
        for slot in range(n_in):
            ed.begin_pin(ed.PinId(_in_pin(nid, slot)), ed.PinKind.input)
            imgui.text("-> in" if n_in == 1 else f"-> in{slot + 1}")
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

        pos = ed.get_node_position(ed.NodeId(nid * 4))
        self._maybe_echo_pos(state, nid, float(pos.x), float(pos.y))

    # -- inline rename (double-click a node) --------------------------------
    def _rename_field(self, state: AppState) -> None:
        if self._rename_focus:
            imgui.set_keyboard_focus_here()
            self._rename_focus = False
        imgui.set_next_item_width(150)
        changed, self._rename_buf = imgui.input_text(
            "##rename", self._rename_buf, imgui.InputTextFlags_.enter_returns_true
        )
        if changed:  # Enter committed
            self._commit_rename(state)
        elif imgui.is_item_deactivated():  # clicked away / Escape
            self._commit_rename(state)

    def _commit_rename(self, state: AppState) -> None:
        nid, name = self._renaming, self._rename_buf.strip()
        self._renaming = None
        self._rename_focus = False
        node = state.nodes.get(nid) if nid is not None else None
        if node is not None and name and name != node.name:
            self._emit(state, "node_rename", nid, name)

    def _begin_rename(self, state: AppState) -> None:
        dc = ed.get_double_clicked_node()
        if dc.id() != 0 and state.nodes.get(dc.id() // 4) is not None:
            self._renaming = dc.id() // 4
            self._rename_buf = state.nodes.get(dc.id() // 4).name
            self._rename_focus = True

    def _params(self, state: AppState, node) -> None:
        imgui.push_item_width(120)
        if node.kind == "source":
            self._source_window(state, node)
        elif node.kind in REGISTRY:
            self._transform_params(state, node)
        else:
            imgui.text_colored((0.95, 0.4, 0.4, 1.0), "missing plugin")
        imgui.pop_item_width()

    def _transform_params(self, state: AppState, node) -> None:
        """Generic renderer for built-in and plugin parameter declarations."""
        spec = REGISTRY.get(node.kind)
        for ps in (spec.ui if spec is not None else ()):
            if node.kind == "math" and ps.key == "k" and node.params.get("op") not in ("scale", "offset"):
                continue
            if node.kind == "filter" and ps.key == "cutoff2" and node.params.get("type") != "band":
                continue
            if ps.kind == "bool":
                ch, on = imgui.checkbox(ps.label, _b(node.params, ps.key, False))
                if ch:
                    self._emit(state, "node_set", node.id, ps.key, "true" if on else "false")
            elif ps.kind == "int":
                self._int(state, node, ps.key, ps.label)
            elif ps.kind == "enum":
                self._combo(state, node, ps.key, f"##{ps.key}", list(ps.options))
            elif ps.kind == "str":
                self._text(state, node, ps.key, ps.label)
            else:  # float (default)
                self._float(state, node, ps.key, ps.label)

    def _source_window(self, state: AppState, node) -> None:
        """Optional tmin/tmax crop on a source node (empty params = full record)."""
        p = node.params
        active = bool(p.get("tmin", "")) or bool(p.get("tmax", ""))
        changed, on = imgui.checkbox("crop time", active)
        if changed:
            if on:  # seed with the run's full extent so the fields are meaningful
                run = state.registry.get(node.ref[0]) if node.ref else None
                lo = float(run.time[0]) if run is not None and run.n_rows else 0.0
                hi = float(run.time[-1]) if run is not None and run.n_rows else 0.0
                self._emit(state, "node_set", node.id, "tmin", repr(lo))
                self._emit(state, "node_set", node.id, "tmax", repr(hi))
            else:
                self._emit(state, "node_set", node.id, "tmin", "")
                self._emit(state, "node_set", node.id, "tmax", "")
        if active:
            self._float(state, node, "tmin", "t min")
            self._float(state, node, "tmax", "t max")

    # -- param widgets (each emits node_set) --------------------------------
    def _combo(self, state, node, key, label, options) -> None:
        cur = str(node.params.get(key, options[0]))
        idx = options.index(cur) if cur in options else 0
        changed, idx = imgui.combo(label, idx, options)
        if changed:
            self._emit(state, "node_set", node.id, key, options[idx])

    def _float(self, state, node, key, label) -> None:
        try:
            from ..nodes import validate_parameter
            validate_parameter(node.kind, key, node.params.get(key, 0.0))
            val = float(node.params.get(key, 0.0))
        except (ValueError, TypeError, OverflowError):
            val = 0.0
        changed, val = imgui.input_double(label, val, 0.0, 0.0, "%.17g")
        if changed:
            self._emit(state, "node_set", node.id, key, repr(val))

    def _int(self, state, node, key, label) -> None:
        try:
            from ..nodes import validate_parameter
            validate_parameter(node.kind, key, node.params.get(key, 0))
            val = int(float(node.params.get(key, 0)))
        except (ValueError, TypeError, OverflowError):
            val = 0
        changed, val = imgui.input_int(label, val)
        if changed:
            self._emit(state, "node_set", node.id, key, str(val))

    def _text(self, state, node, key, label) -> None:
        changed, val = imgui.input_text(
            label, str(node.params.get(key, "")), imgui.InputTextFlags_.enter_returns_true
        )
        if changed:
            self._emit(state, "node_set", node.id, key, val)

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
            self._model_positions[nid] = (x, y)

    # -- link create / delete ----------------------------------------------
    def _handle_create(self, state: AppState) -> None:
        if ed.begin_create():
            a, b = ed.PinId(), ed.PinId()
            if ed.query_new_link(a, b) and a and b:
                if ed.accept_new_item():
                    self._try_link(state, a.id(), b.id())
            ed.end_create()

    def _try_link(self, state: AppState, pa: int, pb: int) -> None:
        ka, na, sa = _decode_pin(pa)
        kb, nb, sb = _decode_pin(pb)
        if ka == "out" and kb == "in":
            self._emit(state, "node_link", na, nb, sb)
        elif ka == "in" and kb == "out":
            self._emit(state, "node_link", nb, na, sa)

    def _handle_delete(self, state: AppState) -> None:
        if ed.begin_delete():
            lid = ed.LinkId()
            while ed.query_deleted_link(lid):
                if ed.accept_deleted_item():
                    dst, slot = _decode_link(lid.id())
                    node = state.nodes.get(dst)
                    if node is not None and slot < len(node.inputs):
                        src = node.inputs[slot]
                        if src is not None:
                            self._emit(state, "node_unlink", src, dst, slot)
            nid = ed.NodeId()
            while ed.query_deleted_node(nid):
                if ed.accept_deleted_item():
                    self._emit(state, "node_remove", nid.id() // 4)
                    self._positioned.discard(nid.id() // 4)
            ed.end_delete()

    # -- panel --------------------------------------------------------------
    def render(self, state: AppState) -> None:
        replaced = self._sync_session(state)
        live = set(state.nodes.nodes)
        self._positioned.intersection_update(live)
        self._model_positions = {key: value for key, value in self._model_positions.items() if key in live}
        self._last_pos = {key: value for key, value in self._last_pos.items() if key in live}
        self._toolbar(state)
        imgui.separator()
        ed.begin("##nodes", imgui.ImVec2(0.0, 0.0))
        if replaced:
            ed.clear_selection()
        for node in state.nodes.ordered():
            self._draw_node(state, node)
        for node in state.nodes.ordered():
            for slot, in_id in enumerate(node.inputs):
                if in_id in state.nodes.nodes:
                    ed.link(ed.LinkId(_link_id(node.id, slot)),
                            ed.PinId(_out_pin(in_id)), ed.PinId(_in_pin(node.id, slot)))
        self._handle_create(state)
        self._handle_delete(state)
        self._begin_rename(state)
        ed.end()
        self._handle_drop(state)

    # -- drag a signal onto the canvas -> source node at the drop point -----
    def _handle_drop(self, state: AppState) -> None:
        # After ed.end() the editor's child counts as the last item, so it can be
        # a drag-drop target for the Navigation signal payload.
        if not imgui.begin_drag_drop_target():
            return
        if imgui.accept_drag_drop_payload_py_id(SIGNAL_DND_TYPE) is not None:
            ref = getattr(state, "dragged_ref", None)
            if ref is not None:
                before = set(state.nodes.nodes)
                self._emit(state, "node_source", ref[0], ref[1])
                new = set(state.nodes.nodes) - before
                if new:
                    nid = new.pop()
                    c = ed.screen_to_canvas(imgui.get_mouse_pos())
                    self._emit(state, "node_pos", nid, float(c.x), float(c.y))
        imgui.end_drag_drop_target()
