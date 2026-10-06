// Trigger controls: arm, mode, source, edge, level, pretrigger, export.
#include <imgui.h>

#include "app/panels/panels.hpp"

namespace uz {

void TriggerPanel::render(ScopeAppState& state) {
    TriggerSettings& cfg = state.config.trigger;
    auto engine = state.engine();

    bool armed = cfg.enabled;
    if (ImGui::Checkbox("Armed", &armed))
        state.commands.execute(state, "trig_arm", {armed ? "on" : "off"});
    if (engine) {
        ImGui::SameLine(0, 20);
        ImGui::TextDisabled("state: %s", to_string(engine->state()));
        auto cap = engine->capture();
        if (cap) {
            ImGui::SameLine(0, 20);
            ImGui::TextDisabled("capture #%d", cap->sequence);
        }
    }

    ImGui::SetNextItemWidth(120);
    if (ImGui::BeginCombo("Mode", cfg.mode.c_str())) {
        for (const char* mode : {"auto", "normal", "single"})
            if (ImGui::Selectable(mode, cfg.mode == mode))
                state.commands.execute(state, "trig_mode", {mode});
        ImGui::EndCombo();
    }

    ImGui::SetNextItemWidth(120);
    std::string source = cfg.channel == 0 ? "auto" : "CH" + std::to_string(cfg.channel);
    if (ImGui::BeginCombo("Source", source.c_str())) {
        if (ImGui::Selectable("auto", cfg.channel == 0))
            state.commands.execute(state, "trig_source", {"0"});
        for (int n = 1; n <= state.config.channels; ++n) {
            std::string label = "CH" + std::to_string(n);
            if (ImGui::Selectable(label.c_str(), cfg.channel == n))
                state.commands.execute(state, "trig_source", {std::to_string(n)});
        }
        ImGui::EndCombo();
    }

    ImGui::SetNextItemWidth(120);
    if (ImGui::BeginCombo("Edge", cfg.edge.c_str())) {
        for (const char* edge : {"rising", "falling"})
            if (ImGui::Selectable(edge, cfg.edge == edge))
                state.commands.execute(state, "trig_edge", {edge});
        ImGui::EndCombo();
    }

    if (!level_init_) {
        level_input_ = cfg.level;
        level_init_ = true;
    }
    ImGui::SetNextItemWidth(120);
    if (ImGui::InputFloat("Level", &level_input_, 0.0f, 0.0f, "%.6g",
                          ImGuiInputTextFlags_EnterReturnsTrue))
        state.commands.execute(state, "trig_level", {std::to_string(level_input_)});
    ImGui::SameLine();
    ImGui::TextDisabled("(raw units, applies on Enter)");

    ImGui::SetNextItemWidth(200);
    float pre = cfg.pretrigger;
    if (ImGui::SliderFloat("Pretrigger", &pre, 0.0f, 1.0f)) cfg.pretrigger = pre;
    if (ImGui::IsItemDeactivatedAfterEdit())
        state.commands.execute(state, "trig_pretrigger",
                               {std::to_string(cfg.pretrigger)});

    ImGui::Separator();
    bool has_capture = engine && engine->capture() != nullptr;
    ImGui::BeginDisabled(!has_capture);
    if (ImGui::Button("Export capture"))
        state.commands.execute(state, "export_capture", {});
    ImGui::EndDisabled();
    if (!has_capture) {
        ImGui::SameLine();
        ImGui::TextDisabled("(waiting for a trigger event)");
    }
}

}  // namespace uz
