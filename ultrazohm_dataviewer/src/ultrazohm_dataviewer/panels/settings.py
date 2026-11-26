"""Non-blocking application Settings window."""

from imgui_bundle import em_size, imgui

from ..preferences import SECTIONS


class SettingsPanel:
    def __init__(self, preferences):
        self.preferences = preferences
        self.visible = False
        self.section = "General"
        self.directory = preferences.values["log_directory"]
        self.error = preferences.error

    def change(self, name, value):
        try:
            self.preferences.update({name: value})
            self.error = ""
        except Exception as exc:
            self.error = str(exc)

    def render(self):
        if not self.visible:
            return
        imgui.set_next_window_size(
            imgui.ImVec2(em_size(45), em_size(28)), imgui.Cond_.first_use_ever
        )
        opened, self.visible = imgui.begin("Settings", self.visible)
        if opened:
            if imgui.begin_table(
                "settings-sections", 2, imgui.TableFlags_.borders_inner_v
            ):
                imgui.table_setup_column(
                    "Category", imgui.TableColumnFlags_.width_fixed, em_size(10)
                )
                imgui.table_setup_column("Options")
                imgui.table_next_column()
                for section in SECTIONS:
                    if imgui.selectable(section, self.section == section)[0]:
                        self.section = section
                imgui.table_next_column()
                self.render_section()
                imgui.separator()
                if imgui.button("Reset this section"):
                    try:
                        self.preferences.reset(self.section)
                        self.directory = self.preferences.values["log_directory"]
                        self.error = ""
                    except Exception as exc:
                        self.error = str(exc)
                imgui.end_table()
            if self.error:
                imgui.text_wrapped(self.error)
        imgui.end()

    def render_section(self):
        prefs = self.preferences
        values, state = prefs.values, prefs.state
        imgui.text_unformatted(self.section)
        imgui.separator()
        if self.section == "General":
            _, self.directory = imgui.input_text("Log directory", self.directory)
            if imgui.is_item_deactivated_after_edit():
                self.change("log_directory", self.directory)
            imgui.text_wrapped(
                "Leave empty to browse the firmware checkout’s artifacts directory."
            )
            for name, label in [
                ("show_application_log", "Show Application log at startup"),
                ("show_python", "Show Python at startup"),
            ]:
                changed, value = imgui.checkbox(label, values[name])
                if changed:
                    self.change(name, value)
            imgui.text_wrapped(
                "Startup visibility applies next time you launch the viewer."
            )
        elif self.section == "Data loading":
            for name, label, options, labels in [
                ("loading_mode", "Loading", ["memory", "lazy"], ["In memory", "Lazy"]),
            ]:
                changed, index = imgui.combo(
                    label, options.index(getattr(state, name)), labels
                )
                if changed:
                    self.change(name, options[index])
            changed, enabled = imgui.checkbox("Disk cache", state.disk_cache)
            if changed:
                self.change("disk_cache", enabled)
            imgui.text_wrapped(
                "Applies to recordings opened from now on. Existing recordings keep their settings."
            )
        else:
            changed, budget = imgui.input_int(
                "RAM cache (MiB)", state.registry.cache.limit // 1024**2
            )
            if changed:
                self.change("cache_budget", budget)
            changed, points = imgui.input_int(
                "Display points per signal", state.max_points
            )
            if changed:
                self.change("max_points", points)
            imgui.text_wrapped(
                "Cache limits do not limit total application memory. Changes apply immediately."
            )
        imgui.spacing()
        imgui.text_wrapped(
            "Edits are saved as application defaults. Loading a session restores its own data and plot settings."
        )
