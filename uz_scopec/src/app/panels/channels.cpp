// Channel table: visibility, observable mapping, scale/offset; every row is
// a drag source for the plot windows.
#include <imgui.h>

#include <cstdio>
#include <cstring>

#include "app/panels/panels.hpp"

namespace uz {

void ChannelsPanel::render(ScopeAppState& state) {
    if (ImGui::Button("Show all")) state.commands.execute(state, "enable_all", {"on"});
    ImGui::SameLine();
    if (ImGui::Button("Hide all")) state.commands.execute(state, "enable_all", {"off"});
    ImGui::SameLine();
    ImGui::TextDisabled("(drag a row into any plot)");

    ImGuiTableFlags flags = ImGuiTableFlags_RowBg | ImGuiTableFlags_BordersInnerV |
                            ImGuiTableFlags_ScrollY | ImGuiTableFlags_SizingStretchProp;
    if (!ImGui::BeginTable("##channels", 5, flags)) return;
    ImGui::TableSetupColumn("", ImGuiTableColumnFlags_WidthFixed, 22);
    ImGui::TableSetupColumn("CH", ImGuiTableColumnFlags_WidthFixed, 34);
    ImGui::TableSetupColumn("Observable");
    ImGui::TableSetupColumn("Scale", ImGuiTableColumnFlags_WidthFixed, 64);
    ImGui::TableSetupColumn("Offset", ImGuiTableColumnFlags_WidthFixed, 64);
    ImGui::TableSetupScrollFreeze(0, 1);
    ImGui::TableHeadersRow();

    ImGuiListClipper clipper;
    clipper.Begin(int(state.config.channel_settings.size()));
    while (clipper.Step()) {
        for (int slot = clipper.DisplayStart; slot < clipper.DisplayEnd; ++slot) {
            ChannelSettings& ch = state.config.channel_settings[size_t(slot)];
            ImGui::TableNextRow();
            ImGui::PushID(slot);

            ImGui::TableNextColumn();
            bool visible = ch.visible;
            if (ImGui::Checkbox("##vis", &visible))
                state.commands.execute(state, "ch_visible",
                                       {std::to_string(slot + 1), visible ? "on" : "off"});

            ImGui::TableNextColumn();
            char chlabel[16];
            std::snprintf(chlabel, sizeof(chlabel), "%d", slot + 1);
            ImGui::Selectable(chlabel, false, ImGuiSelectableFlags_AllowOverlap);
            if (ImGui::BeginDragDropSource()) {
                ImGui::SetDragDropPayload(DND_CHANNEL, &slot, sizeof(int));
                std::string name = state.observable_name(ch.observable);
                if (name.rfind("JSO_", 0) == 0) name = name.substr(4);
                ImGui::Text("CH%d %s", slot + 1, name.c_str());
                ImGui::EndDragDropSource();
            }

            ImGui::TableNextColumn();
            std::string name = state.observable_name(ch.observable);
            if (name.rfind("JSO_", 0) == 0) name = name.substr(4);
            ImGui::SetNextItemWidth(-1);
            if (ImGui::BeginCombo("##obs", name.c_str())) {
                ImGui::SetNextItemWidth(-1);
                ImGui::InputTextWithHint("##filter", "filter...", filter_,
                                         sizeof(filter_));
                std::string needle = filter_;
                for (auto& c : needle) c = char(std::tolower((unsigned char)c));
                if (state.header) {
                    for (size_t idx = 0; idx < state.header->observables.size(); ++idx) {
                        std::string obs = state.header->observables[idx];
                        if (obs.rfind("JSO_", 0) == 0) obs = obs.substr(4);
                        if (!needle.empty()) {
                            std::string hay = obs;
                            for (auto& c : hay) c = char(std::tolower((unsigned char)c));
                            if (hay.find(needle) == std::string::npos) continue;
                        }
                        if (ImGui::Selectable(obs.c_str(), int(idx) == ch.observable))
                            state.commands.execute(state, "ch_select",
                                                   {std::to_string(slot + 1),
                                                    std::to_string(idx)});
                    }
                }
                ImGui::EndCombo();
            }

            // Continuous drags apply live and echo one command when the drag
            // ends, keeping the console log replayable without a line per px.
            ImGui::TableNextColumn();
            ImGui::SetNextItemWidth(-1);
            float scale = ch.scale;
            if (ImGui::DragFloat("##scale", &scale, 0.01f, 0.0f, 0.0f, "%.3g") &&
                scale != 0.0f)
                ch.scale = scale;
            if (ImGui::IsItemDeactivatedAfterEdit())
                state.commands.echo(state, "ch_scale",
                                    {std::to_string(slot + 1), std::to_string(ch.scale)});

            ImGui::TableNextColumn();
            ImGui::SetNextItemWidth(-1);
            float offset = ch.offset;
            if (ImGui::DragFloat("##offset", &offset, 0.01f, 0.0f, 0.0f, "%.3g"))
                ch.offset = offset;
            if (ImGui::IsItemDeactivatedAfterEdit())
                state.commands.echo(state, "ch_offset",
                                    {std::to_string(slot + 1), std::to_string(ch.offset)});

            ImGui::PopID();
        }
    }
    ImGui::EndTable();
}

}  // namespace uz
