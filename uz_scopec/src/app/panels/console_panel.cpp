// Console: command echo log + input line (every UI action lands here too).
#include <imgui.h>

#include <cstring>

#include "app/panels/panels.hpp"

namespace uz {

void ConsolePanel::render(ScopeAppState& state) {
    float footer = ImGui::GetFrameHeightWithSpacing();
    if (ImGui::BeginChild("##log", ImVec2(0, -footer))) {
        for (const ConsoleEntry& e : state.console.entries()) {
            if (e.level == "ERROR")
                ImGui::TextColored(ImVec4(1.0f, 0.35f, 0.35f, 1.0f), "%s",
                                   e.message.c_str());
            else if (e.level == "WARN")
                ImGui::TextColored(ImVec4(1.0f, 0.75f, 0.25f, 1.0f), "%s",
                                   e.message.c_str());
            else if (e.level == "CMD")
                ImGui::TextColored(ImVec4(0.55f, 0.75f, 1.0f, 1.0f), "> %s",
                                   e.message.c_str());
            else
                ImGui::TextUnformatted(e.message.c_str());
        }
        if (scroll_to_bottom_ ||
            ImGui::GetScrollY() >= ImGui::GetScrollMaxY() - 4.0f)
            ImGui::SetScrollHereY(1.0f);
        scroll_to_bottom_ = false;
    }
    ImGui::EndChild();

    ImGui::SetNextItemWidth(-70);
    bool entered = ImGui::InputTextWithHint(
        "##cmd", "command... (help lists all)", input_, sizeof(input_),
        ImGuiInputTextFlags_EnterReturnsTrue);
    ImGui::SameLine();
    if (ImGui::Button("Run##cmd") || entered) {
        if (input_[0]) {
            state.commands.dispatch(state, input_);
            input_[0] = '\0';
            scroll_to_bottom_ = true;
        }
        ImGui::SetKeyboardFocusHere(-1);
    }
}

}  // namespace uz
