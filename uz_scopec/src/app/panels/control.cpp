// Control tab: state machine, LEDs, MyButtons, send fields, receive fields,
// error handling — the JavaScope Control tab.
#include <imgui.h>

#include <cstdio>

#include "app/panels/panels.hpp"

namespace uz {
namespace {

const ImVec4 LED_ON_GREEN(0.20f, 0.85f, 0.25f, 1.0f);
const ImVec4 LED_ON_RED(0.90f, 0.20f, 0.20f, 1.0f);
const ImVec4 LED_ON_BLUE(0.25f, 0.55f, 0.95f, 1.0f);
const ImVec4 LED_OFF(0.28f, 0.30f, 0.33f, 1.0f);

void led(const char* label, bool on, const ImVec4& on_color) {
    ImGui::PushStyleColor(ImGuiCol_Button, on ? on_color : LED_OFF);
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, on ? on_color : LED_OFF);
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, on ? on_color : LED_OFF);
    ImGui::Button(label);
    ImGui::PopStyleColor(3);
}

std::string entry(const std::vector<std::string>& v, size_t i,
                  const std::string& fallback) {
    return i < v.size() ? v[i] : fallback;
}

}  // namespace

void ControlPanel::render(ScopeAppState& state) {
    if (send_values_.size() != 20) send_values_.assign(20, 0.0f);
    uint32_t status = state.last_status.load();
    bool connected = state.connected();

    // --- LEDs + state machine --------------------------------------------
    led("Ready", status_bit(status, STATUS_BIT_READY), LED_ON_GREEN);
    ImGui::SameLine();
    led("Running", status_bit(status, STATUS_BIT_RUNNING), LED_ON_GREEN);
    ImGui::SameLine();
    led("Error", status_bit(status, STATUS_BIT_ERROR), LED_ON_RED);
    ImGui::SameLine();
    led("User", status_bit(status, STATUS_BIT_USER), LED_ON_BLUE);

    ImGui::BeginDisabled(!connected);
    if (ImGui::Button("Enable System"))
        state.commands.execute(state, "enable_system", {});
    ImGui::SameLine();
    if (ImGui::Button("Enable Control"))
        state.commands.execute(state, "enable_control", {});
    ImGui::SameLine();
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.65f, 0.15f, 0.15f, 1.0f));
    if (ImGui::Button("STOP")) state.commands.execute(state, "stop_system", {});
    ImGui::PopStyleColor();
    ImGui::SameLine(0, 30);
    if (ImGui::Button("Error Reset")) state.commands.execute(state, "error_reset", {});
    ImGui::EndDisabled();
    ImGui::SameLine();
    {
        // Error code source: SLOWDAT_DISPLAY entry 21 (after the 20 fields).
        std::string source = "JSSD_FLOAT_Error_Code";
        if (state.header && state.header->slowdata_display.size() > 21)
            source = state.header->slowdata_display[21];
        double code = 0.0;
        state.slowdata.get_by_name(source, code);
        ImGui::Text("error code: %g", code);
    }

    ImGui::Separator();

    // --- MyButtons with indicator LEDs -----------------------------------
    ImGui::TextDisabled("MyButtons");
    ImGui::BeginDisabled(!connected);
    for (int n = 1; n <= 8; ++n) {
        std::string label = "My_Button_" + std::to_string(n);
        if (state.header)
            label = entry(state.header->mybutton_labels, size_t(n), label);
        ImGui::PushID(n);
        bool indicator = mybutton_indicator(status, n);
        ImGui::PushStyleColor(ImGuiCol_Text,
                              indicator ? LED_ON_GREEN
                                        : ImGui::GetStyleColorVec4(ImGuiCol_Text));
        if (ImGui::Button(label.c_str(), ImVec2(150, 0)))
            state.commands.execute(state, "my_button", {std::to_string(n)});
        ImGui::PopStyleColor();
        ImGui::PopID();
        if (n % 4 != 0) ImGui::SameLine();
    }
    ImGui::EndDisabled();

    ImGui::Separator();

    // --- send + receive fields side by side ------------------------------
    if (ImGui::BeginTable("##fields", 2, ImGuiTableFlags_SizingStretchSame)) {
        ImGui::TableNextRow();
        ImGui::TableNextColumn();
        ImGui::TextDisabled("Send fields");
        if (ImGui::BeginTable("##send", 3,
                              ImGuiTableFlags_RowBg | ImGuiTableFlags_ScrollY,
                              ImVec2(0, 320))) {
            ImGui::TableSetupColumn("field");
            ImGui::TableSetupColumn("value", ImGuiTableColumnFlags_WidthFixed, 110);
            ImGui::TableSetupColumn("", ImGuiTableColumnFlags_WidthFixed, 40);
            ImGui::TableSetupScrollFreeze(0, 1);
            ImGui::TableHeadersRow();
            for (int n = 1; n <= 20; ++n) {
                ImGui::TableNextRow();
                ImGui::PushID(n);
                ImGui::TableNextColumn();
                std::string label = "send_field_" + std::to_string(n);
                std::string unit;
                if (state.header) {
                    label = entry(state.header->send_field_names, size_t(n), label);
                    unit = entry(state.header->send_field_units, size_t(n), "");
                }
                if (!unit.empty() && unit != "-") label += " [" + unit + "]";
                ImGui::AlignTextToFramePadding();
                ImGui::TextUnformatted(label.c_str());
                ImGui::TableNextColumn();
                ImGui::SetNextItemWidth(-1);
                bool entered = ImGui::InputFloat("##v", &send_values_[size_t(n - 1)],
                                                 0.0f, 0.0f, "%g",
                                                 ImGuiInputTextFlags_EnterReturnsTrue);
                ImGui::TableNextColumn();
                ImGui::BeginDisabled(!connected);
                if (ImGui::Button("Set") || (entered && connected))
                    state.commands.execute(
                        state, "send_field",
                        {std::to_string(n), std::to_string(send_values_[size_t(n - 1)])});
                ImGui::EndDisabled();
                ImGui::PopID();
            }
            ImGui::EndTable();
        }

        ImGui::TableNextColumn();
        ImGui::TextDisabled("Receive fields");
        if (ImGui::BeginTable("##recv", 2,
                              ImGuiTableFlags_RowBg | ImGuiTableFlags_ScrollY,
                              ImVec2(0, 320))) {
            ImGui::TableSetupColumn("field");
            ImGui::TableSetupColumn("value", ImGuiTableColumnFlags_WidthFixed, 130);
            ImGui::TableSetupScrollFreeze(0, 1);
            ImGui::TableHeadersRow();
            for (int n = 1; n <= 20; ++n) {
                ImGui::TableNextRow();
                ImGui::TableNextColumn();
                std::string label = "receive_field_" + std::to_string(n);
                std::string unit, source;
                if (state.header) {
                    label = entry(state.header->receive_field_names, size_t(n), label);
                    unit = entry(state.header->receive_field_units, size_t(n), "");
                    source = entry(state.header->slowdata_display, size_t(n), "");
                }
                ImGui::TextUnformatted(label.c_str());
                ImGui::TableNextColumn();
                double value = 0.0;
                bool have = !source.empty() && source != "JSSD_FLOAT_ZEROVALUE" &&
                            state.slowdata.get_by_name(source, value);
                if (have) {
                    if (!unit.empty() && unit != "-")
                        ImGui::Text("%.6g %s", value, unit.c_str());
                    else
                        ImGui::Text("%.6g", value);
                } else {
                    ImGui::TextDisabled("-");
                }
            }
            ImGui::EndTable();
        }
        ImGui::EndTable();
    }
}

}  // namespace uz
