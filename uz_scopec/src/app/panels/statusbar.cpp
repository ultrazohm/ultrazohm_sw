// Footer: connection, alive indicator, status word, rate, throughput, log.
#include <imgui.h>

#include "app/panels/panels.hpp"

namespace uz {
namespace {
const ImVec4 GREEN(0.30f, 0.85f, 0.35f, 1.0f);
const ImVec4 RED(1.0f, 0.35f, 0.35f, 1.0f);
const ImVec4 GRAY(0.5f, 0.5f, 0.5f, 1.0f);
}  // namespace

void StatusBar::render(ScopeAppState& state) {
    bool connected = state.connected();
    if (!connected) {
        if (ImGui::SmallButton("connect")) state.commands.execute(state, "connect", {});
    } else {
        if (ImGui::SmallButton("disconnect"))
            state.commands.execute(state, "disconnect", {});
    }
    ImGui::SameLine();
    ImGui::Text("%s:%d", state.config.ip.c_str(), state.config.port);

    ImGui::SameLine(0, 16);
    // Alive dot: green when a packet arrived within the last 500 ms.
    ImGui::TextColored(state.alive() ? GREEN : (connected ? RED : GRAY), "*");
    ImGui::SameLine();
    uint32_t status = state.last_status.load();
    ImGui::Text("status 0x%08X", status);

    ImGui::SameLine(0, 16);
    ImGui::Text("rate %g Hz%s", state.sample_rate(),
                state.detected_rate > 0 ? " (detected)" : "");

    // Throughput: received sample rate vs nominal over ~1 s windows.
    ImGui::SameLine(0, 16);
    if (state.client && connected) {
        double now = monotonic_seconds();
        int64_t samples = state.client->stats.samples.load();
        if (window_t0_ <= 0.0) {
            window_t0_ = now;
            window_samples_ = samples;
        } else if (now - window_t0_ >= 1.0) {
            sample_rate_measured_ = double(samples - window_samples_) / (now - window_t0_);
            window_t0_ = now;
            window_samples_ = samples;
        }
        double expected = state.sample_rate();
        double pct = expected > 0 ? 100.0 * sample_rate_measured_ / expected : 0.0;
        double mbps = sample_rate_measured_ *
                      double(state.config.geometry().frame_bytes()) /
                      double(state.config.samples_per_packet) / 1e6;
        ImGui::TextColored(pct < 95.0 ? RED : GREEN, "%.1f%% (%.2f MB/s)", pct, mbps);
    } else {
        ImGui::TextDisabled("--%%");
        window_t0_ = 0.0;
        sample_rate_measured_ = 0.0;
    }

    ImGui::SameLine(0, 16);
    if (state.logging()) {
        LoggerStats s = state.logger_stats();
        ImGui::TextColored(GREEN, "LOG %lld rows", (long long)s.rows_written);
    } else {
        ImGui::TextDisabled("log off");
    }
}

}  // namespace uz
