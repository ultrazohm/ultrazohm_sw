"""Bottom status bar: runtime performance and cache usage."""

from imgui_bundle import imgui, imgui_ctx

from .base import SessionPanel


class StatusPanel(SessionPanel):
    def render(self, state):
        with imgui_ctx.begin_horizontal(
            "status", imgui.ImVec2(imgui.get_content_region_avail().x, 0)
        ):
            imgui.align_text_to_frame_padding()
            cache = state.registry.cache.status()
            fps = imgui.get_io().framerate
            used = cache["bytes"] / 1024**2
            label = f"FPS: {fps:.1f}  |  RAM cache: {used:.1f} / {cache['limit'] / 1024**2:.0f} MiB"
            if cache["limit_hit"]:
                label += "  |  cache limit hit"
            # Keep runtime usage readable in narrow windows.
            if imgui.calc_text_size(label).x > imgui.get_content_region_avail().x:
                label = f"FPS: {fps:.0f} | RAM: {used:.0f} MiB"
            imgui.spring()
            if cache["limit_hit"]:
                imgui.text_colored(imgui.ImVec4(1.0, 0.72, 0.25, 1.0), label)
            else:
                imgui.text_unformatted(label)
            if imgui.is_item_hovered():
                imgui.set_tooltip(
                    f"RAM cache: {used:.1f} / {cache['limit'] / 1024**2:.0f} MiB; not total application memory.\n"
                    "Limit hit is highlighted for 5 seconds after eviction or an oversized result.\n"
                    f"Since cache clear: {cache['evictions']} entries evicted; "
                    f"{cache['oversized']} oversized results not retained.\n"
                    "Evicted data is reread or recomputed when needed; no measurement data is lost."
                )
