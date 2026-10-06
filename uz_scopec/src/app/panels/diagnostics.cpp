// Developer diagnostics: link stats, ack pacing, lifecheck, rate detection,
// sent-command trace.
#include <imgui.h>

#include "app/panels/panels.hpp"

namespace uz {
namespace {
const ImVec4 GREEN(0.30f, 0.85f, 0.35f, 1.0f);
const ImVec4 RED(1.0f, 0.35f, 0.35f, 1.0f);
}  // namespace

void DiagnosticsPanel::render(ScopeAppState& state) {
    ImGui::TextDisabled("Link");
    if (state.client) {
        const NetStats& s = state.client->stats;
        double now = monotonic_seconds();
        if (window_t0_ <= 0.0) {
            window_t0_ = now;
            window_bytes_ = s.bytes_received.load();
        } else if (now - window_t0_ >= 1.0) {
            rate_mbps_ = double(s.bytes_received.load() - window_bytes_) /
                         (now - window_t0_) / 1e6;
            window_t0_ = now;
            window_bytes_ = s.bytes_received.load();
        }
        ImGui::Text("%.2f MB/s  |  %lld frames  |  %lld samples", rate_mbps_,
                    (long long)s.frames.load(), (long long)s.samples.load());
        ImGui::Text("%lld commands sent, %d queued  |  %lld connects",
                    (long long)s.commands_sent.load(), state.client->pending_commands(),
                    (long long)s.connects.load());
        std::string err = s.last_error();
        if (!err.empty()) ImGui::TextColored(RED, "last error: %s", err.c_str());
        bool pacing = state.client->ack_pacing();
        if (ImGui::Checkbox("Ack pacing (lock-step test server needs this)", &pacing))
            state.commands.execute(state, "ack_pacing", {pacing ? "on" : "off"});
    } else {
        ImGui::TextDisabled("not connected");
        window_t0_ = 0.0;
    }

    ImGui::Separator();
    ImGui::TextDisabled("Lifecheck (sample continuity)");
    // The slot is auto-tracked whenever a channel observes JSO_lifecheck.
    bool monitoring = false;
    if (state.header) {
        if (auto idx = state.header->observable_index("JSO_lifecheck")) {
            for (size_t i = 0; i < state.config.channel_settings.size(); ++i) {
                if (state.config.channel_settings[i].observable == *idx) {
                    ImGui::Text("monitoring CH%zu: %lld samples checked", i + 1,
                                (long long)state.lifecheck.checked.load());
                    monitoring = true;
                    break;
                }
            }
        }
    }
    if (!monitoring) {
        ImGui::Text("select JSO_lifecheck on a channel to monitor for drops");
    } else {
        int64_t gaps = state.lifecheck.gaps.load();
        ImGui::TextColored(gaps == 0 ? GREEN : RED, "%lld gaps, %lld samples missing",
                           (long long)gaps, (long long)state.lifecheck.missing.load());
        if (ImGui::SmallButton("Reset counters")) state.lifecheck.reset();
    }

    ImGui::Separator();
    ImGui::TextDisabled("Sample rate");
    double nominal = 1e6 / state.config.timestep_usec;
    ImGui::Text("configured: %g Hz", nominal);
    if (state.detected_rate > 0)
        ImGui::Text("detected: %g Hz (time axis uses this)", state.detected_rate);
    bool auto_detect = state.config.auto_detect_rate;
    if (ImGui::Checkbox("Auto-detect after connect", &auto_detect))
        state.config.auto_detect_rate = auto_detect;
    ImGui::SameLine();
    ImGui::BeginDisabled(!state.connected());
    if (ImGui::Button("Detect now")) state.commands.execute(state, "detect_rate", {});
    ImGui::EndDisabled();

    ImGui::Separator();
    ImGui::TextDisabled("Sent commands (newest first)");
    ImGuiTableFlags flags = ImGuiTableFlags_RowBg | ImGuiTableFlags_ScrollY;
    if (ImGui::BeginTable("##trace", 3, flags, ImVec2(0, 160))) {
        ImGui::TableSetupColumn("id", ImGuiTableColumnFlags_WidthFixed, 44);
        ImGui::TableSetupColumn("value", ImGuiTableColumnFlags_WidthFixed, 80);
        ImGui::TableSetupColumn("label");
        ImGui::TableSetupScrollFreeze(0, 1);
        ImGui::TableHeadersRow();
        auto trace = state.cmd_trace_snapshot();
        for (auto it = trace.rbegin(); it != trace.rend(); ++it) {
            ImGui::TableNextRow();
            ImGui::TableNextColumn();
            ImGui::Text("%u", it->cmd_id);
            ImGui::TableNextColumn();
            ImGui::Text("%g", it->value);
            ImGui::TableNextColumn();
            ImGui::TextUnformatted(it->label.c_str());
        }
        ImGui::EndTable();
    }
}

}  // namespace uz
