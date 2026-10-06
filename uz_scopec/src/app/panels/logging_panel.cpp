// Logging tab: stream incoming samples to disk while you work.
#include <imgui.h>

#include <cstring>

#include "app/panels/panels.hpp"

namespace uz {

void LoggingPanel::render(ScopeAppState& state) {
    LoggingSettings& cfg = state.config.logging;
    bool active = state.logging();

    if (!dir_init_) {
        std::snprintf(dir_, sizeof(dir_), "%s", cfg.directory.c_str());
        dir_init_ = true;
    }

    ImGui::BeginDisabled(active);
    ImGui::SetNextItemWidth(120);
    if (ImGui::BeginCombo("Format", cfg.format.c_str())) {
        for (const char* f : {"csv", "bin"})
            if (ImGui::Selectable(f, cfg.format == f))
                state.commands.execute(state, "log_format", {f});
        ImGui::EndCombo();
    }
    ImGui::SameLine();
    ImGui::TextDisabled(cfg.format == "bin"
                            ? "raw float32 + sidecar (guaranteed rate)"
                            : "text, opens in the Data Viewer / Excel / MATLAB");

    ImGui::SetNextItemWidth(120);
    int every = cfg.every_n;
    if (ImGui::InputInt("Log every N-th sample", &every) && every >= 1)
        state.commands.execute(state, "log_every", {std::to_string(every)});

    ImGui::SetNextItemWidth(300);
    if (ImGui::InputText("Directory", dir_, sizeof(dir_),
                         ImGuiInputTextFlags_EnterReturnsTrue))
        state.commands.execute(state, "log_dir", {dir_});
    ImGui::EndDisabled();

    bool ext = cfg.ext_trigger;
    if (ImGui::Checkbox("External trigger (device status bit 12)", &ext))
        state.commands.execute(state, "ext_log", {ext ? "on" : "off"});

    ImGui::Separator();
    if (!active) {
        if (ImGui::Button("Start logging", ImVec2(140, 0)))
            state.commands.execute(state, "log_start", {});
    } else {
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.65f, 0.15f, 0.15f, 1.0f));
        if (ImGui::Button("Stop logging", ImVec2(140, 0)))
            state.commands.execute(state, "log_stop", {});
        ImGui::PopStyleColor();
        LoggerStats s = state.logger_stats();
        ImGui::SameLine();
        ImGui::Text("%lld rows", (long long)s.rows_written);
        if (s.chunks_dropped) {
            ImGui::SameLine();
            ImGui::TextColored(ImVec4(1.0f, 0.35f, 0.35f, 1.0f),
                               "%lld samples dropped (disk too slow)",
                               (long long)s.samples_dropped);
        }
    }
    if (!state.last_log_path.empty()) {
        ImGui::TextDisabled("last log: %s", state.last_log_path.c_str());
    }
}

}  // namespace uz
