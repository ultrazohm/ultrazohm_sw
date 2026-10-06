// SlowData table: latest typed value per JS_SlowData entry.
#include <imgui.h>

#include "app/panels/panels.hpp"

namespace uz {

void SlowDataPanel::render(ScopeAppState& state) {
    auto items = state.slowdata.items();
    ImGui::TextDisabled("%zu entries, %lld updates", items.size(),
                        (long long)state.slowdata.updates());
    ImGuiTableFlags flags = ImGuiTableFlags_RowBg | ImGuiTableFlags_BordersInnerV |
                            ImGuiTableFlags_ScrollY;
    if (!ImGui::BeginTable("##slowdata", 3, flags)) return;
    ImGui::TableSetupColumn("id", ImGuiTableColumnFlags_WidthFixed, 36);
    ImGui::TableSetupColumn("name");
    ImGui::TableSetupColumn("value", ImGuiTableColumnFlags_WidthFixed, 140);
    ImGui::TableSetupScrollFreeze(0, 1);
    ImGui::TableHeadersRow();
    for (const auto& item : items) {
        ImGui::TableNextRow();
        ImGui::TableNextColumn();
        ImGui::Text("%d", item.id);
        ImGui::TableNextColumn();
        ImGui::TextUnformatted(item.name.c_str());
        ImGui::TableNextColumn();
        if (item.is_float)
            ImGui::Text("%.6g", item.value);
        else
            ImGui::Text("%.0f", item.value);
    }
    ImGui::EndTable();
}

}  // namespace uz
