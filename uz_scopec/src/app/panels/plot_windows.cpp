// The plot windows: rolling live display, trigger capture overlay, subplot
// grids, drag&drop targets, multi-window.
//
// Data refresh (default 30 Hz) is decoupled from the render rate: each
// refresh takes a wrap-aware ring snapshot of the plotted channels and
// decimates it with a min/max envelope to ~2x the plot's pixel width, so the
// per-frame cost is independent of the ring size.  The display transform
// (y + offset) / scale is applied to the decimated points only.
#include <imgui.h>
#include <implot.h>

#include <algorithm>
#include <cmath>

#include "app/panels/panels.hpp"

namespace uz {
namespace {

constexpr double WINDOW_PRESETS_S[] = {0.05, 0.1, 0.5, 1.0, 2.5, 5.0, 10.0, 25.0, 50.0};

bool parse_color(const std::string& hex, ImVec4& out) {
    if (hex.size() != 7 || hex[0] != '#') return false;
    auto nib = [](char c) -> int {
        if (c >= '0' && c <= '9') return c - '0';
        if (c >= 'a' && c <= 'f') return c - 'a' + 10;
        if (c >= 'A' && c <= 'F') return c - 'A' + 10;
        return -1;
    };
    int v[6];
    for (int i = 0; i < 6; ++i) {
        v[i] = nib(hex[1 + i]);
        if (v[i] < 0) return false;
    }
    out = ImVec4(float(v[0] * 16 + v[1]) / 255.0f, float(v[2] * 16 + v[3]) / 255.0f,
                 float(v[4] * 16 + v[5]) / 255.0f, 1.0f);
    return true;
}

// Min/max envelope decimation: never hides a spike, output ~n_out points.
void decimate(const float* y, int64_t m, int64_t start_index, double dt,
              double offset, double scale, int n_out, std::vector<double>& xs,
              std::vector<double>& ys) {
    xs.clear();
    ys.clear();
    if (m <= 0) return;
    const double inv_scale = 1.0 / (scale != 0.0 ? scale : 1.0);
    if (m <= n_out) {
        xs.reserve(size_t(m));
        ys.reserve(size_t(m));
        for (int64_t i = 0; i < m; ++i) {
            xs.push_back(double(start_index + i) * dt);
            ys.push_back((double(y[i]) + offset) * inv_scale);
        }
        return;
    }
    int buckets = std::max(1, n_out / 2);
    xs.reserve(size_t(buckets) * 2);
    ys.reserve(size_t(buckets) * 2);
    for (int b = 0; b < buckets; ++b) {
        int64_t i0 = m * b / buckets;
        int64_t i1 = std::max(i0 + 1, m * (b + 1) / buckets);
        int64_t imin = i0, imax = i0;
        float vmin = y[i0], vmax = y[i0];
        for (int64_t i = i0 + 1; i < i1; ++i) {
            if (y[i] < vmin) { vmin = y[i]; imin = i; }
            if (y[i] > vmax) { vmax = y[i]; imax = i; }
        }
        int64_t first = std::min(imin, imax), second = std::max(imin, imax);
        xs.push_back(double(start_index + first) * dt);
        ys.push_back((double(y[first]) + offset) * inv_scale);
        if (second != first) {
            xs.push_back(double(start_index + second) * dt);
            ys.push_back((double(y[second]) + offset) * inv_scale);
        }
    }
}

}  // namespace

std::vector<int> PlotWindows::cell_slots(const ScopeAppState& state, int win,
                                         int cell) const {
    const PlotWindowConfig& p = state.config.plots[size_t(win)];
    std::vector<int> slots = p.cells[size_t(cell)].slots;
    if (win == 0 && cell == 0) {
        // The classic scope view: the channel table's visible flags.
        for (size_t i = 0; i < state.config.channel_settings.size(); ++i) {
            if (state.config.channel_settings[i].visible &&
                std::find(slots.begin(), slots.end(), int(i)) == slots.end())
                slots.push_back(int(i));
        }
    }
    std::erase_if(slots, [&](int s) { return s < 0 || s >= state.config.channels; });
    return slots;
}

void PlotWindows::rebuild(ScopeAppState& state) {
    const double dt = state.timestep_s();
    auto engine = state.engine();
    std::shared_ptr<const Capture> cap = engine ? engine->capture() : nullptr;
    if (engine && engine->capture_is_stale()) cap = nullptr;  // auto mode: roll again

    level_valid_ = engine != nullptr;
    trigger_slot_ = engine ? engine->channel : -1;
    if (engine) {
        // Level in display coordinates of the source channel — the line must
        // sit on the plotted waveform (JavaScope parity); comparison is raw.
        double offset = 0.0, scale = 1.0;
        if (engine->channel < int(state.config.channel_settings.size())) {
            const auto& ch = state.config.channel_settings[size_t(engine->channel)];
            offset = ch.offset;
            scale = std::abs(ch.scale) > 1e-12 ? ch.scale : 1.0;
        }
        level_display_ = (double(engine->level) + offset) / scale;
    }

    showing_capture_ = cap != nullptr;
    trigger_time_ = cap ? double(cap->trigger_index) * dt : -1.0;
    if (cap && cap->sequence != capture_seq_) {
        capture_seq_ = cap->sequence;
        capture_fit_ = true;  // pin the x-axis once per fresh capture
    }
    if (!cap) capture_seq_ = 0;  // a re-armed engine restarts its sequence

    data_.assign(state.config.plots.size(), {});
    const int n_out = 2 * 1600;  // ~2x a wide plot; cheap enough to keep fixed
    for (size_t win = 0; win < state.config.plots.size(); ++win) {
        const PlotWindowConfig& p = state.config.plots[win];
        if (!p.open) continue;
        data_[win].cells.resize(p.cells.size());
        for (size_t cell = 0; cell < p.cells.size(); ++cell) {
            std::vector<int> slots = cell_slots(state, int(win), int(cell));
            CellData& cd = data_[win].cells[cell];
            for (int slot : slots) {
                const auto& ch = state.config.channel_settings[size_t(slot)];
                Series s;
                s.slot = slot;
                std::string name = state.observable_name(ch.observable);
                if (name.rfind("JSO_", 0) == 0) name = name.substr(4);
                s.label = "CH" + std::to_string(slot + 1) + " " + name;
                if (cap) {
                    decimate(cap->window.row(slot), cap->window.count,
                             cap->window.start, dt, ch.offset, ch.scale, n_out,
                             s.xs, s.ys);
                } else {
                    int64_t count = std::max<int64_t>(
                        2, int64_t(state.config.window_seconds * state.sample_rate()));
                    Snapshot snap = state.ring->snapshot(count, {slot});
                    decimate(snap.row(0), snap.count, snap.start, dt, ch.offset,
                             ch.scale, n_out, s.xs, s.ys);
                }
                cd.series.push_back(std::move(s));
            }
        }
    }

    if (cap) {
        x_min_ = double(cap->window.start) * dt;
        x_max_ = double(cap->window.start + cap->window.count) * dt;
    } else {
        double end = double(state.ring->total_written()) * dt;
        x_min_ = end - state.config.window_seconds;
        x_max_ = end;
    }
}

void PlotWindows::render(ScopeAppState& state) {
    double now = ImGui::GetTime();
    bool frozen_hold = state.frozen && !showing_capture_;
    if (now >= next_refresh_ && !frozen_hold) {
        next_refresh_ = now + 1.0 / std::max(1.0, state.config.refresh_hz);
        rebuild(state);
    }
    if (data_.size() != state.config.plots.size()) rebuild(state);
    for (size_t i = 0; i < state.config.plots.size(); ++i)
        render_window(state, int(i));
}

void PlotWindows::render_window(ScopeAppState& state, int index) {
    PlotWindowConfig& p = state.config.plots[size_t(index)];
    if (!p.open) return;
    if (index > 0)
        ImGui::SetNextWindowSize(ImVec2(700, 450), ImGuiCond_FirstUseEver);
    bool open = p.open;
    // Index-stable ID so renames/reorders don't lose the dock slot.
    std::string id = p.title + "###plot" + std::to_string(index);
    if (!ImGui::Begin(id.c_str(), index > 0 ? &open : nullptr)) {
        ImGui::End();
        return;
    }
    if (index > 0 && open != p.open) {
        std::vector<std::string> args = {std::to_string(index + 1), "off"};
        state.commands.execute(state, "plot_open", args);
    }

    // --- toolbar ---------------------------------------------------------
    if (index == 0) {
        if (ImGui::Button(state.frozen ? "Run" : "Stop"))
            state.commands.execute(state, state.frozen ? "run" : "stop_scope", {});
        ImGui::SameLine();
        ImGui::SetNextItemWidth(90);
        char label[32];
        std::snprintf(label, sizeof(label), "%g s", state.config.window_seconds);
        if (ImGui::BeginCombo("##window", label)) {
            for (double preset : WINDOW_PRESETS_S) {
                std::snprintf(label, sizeof(label), "%g s", preset);
                if (ImGui::Selectable(label, preset == state.config.window_seconds))
                    state.commands.execute(state, "set_window", {std::to_string(preset)});
            }
            ImGui::EndCombo();
        }
        ImGui::SameLine();
        bool fix = state.fix_axis;
        if (ImGui::Checkbox("Fix axis", &fix))
            state.commands.execute(state, "fix_axis", {fix ? "on" : "off"});
        ImGui::SameLine();
    }
    ImGui::SetNextItemWidth(70);
    char grid_label[16];
    std::snprintf(grid_label, sizeof(grid_label), "%dx%d", p.rows, p.cols);
    if (ImGui::BeginCombo("##grid", grid_label)) {
        for (int r = 1; r <= 4; ++r) {
            for (int c = 1; c <= 4; ++c) {
                if (r * c > 8 && !(r == 4 && c == 4)) continue;
                std::snprintf(grid_label, sizeof(grid_label), "%dx%d", r, c);
                if (ImGui::Selectable(grid_label, r == p.rows && c == p.cols)) {
                    state.commands.execute(
                        state, "plot_grid",
                        {std::to_string(index + 1), std::to_string(r), std::to_string(c)});
                }
            }
        }
        ImGui::EndCombo();
    }
    if (index == 0) {
        ImGui::SameLine();
        if (ImGui::Button("+ Plot window")) state.commands.execute(state, "plot_add", {});
    }

    // --- subplot grid ----------------------------------------------------
    if (index >= int(data_.size())) {
        ImGui::End();
        return;
    }
    bool fresh_capture_fit = capture_fit_;
    if (ImPlot::BeginSubplots("##subplots", p.rows, p.cols, ImVec2(-1, -1))) {
        for (int cell = 0; cell < p.rows * p.cols; ++cell) {
            std::vector<int> slots = cell_slots(state, index, cell);
            render_cell(state, index, cell, slots, showing_capture_);
        }
        ImPlot::EndSubplots();
    }
    if (fresh_capture_fit && index == int(state.config.plots.size()) - 1)
        capture_fit_ = false;  // consumed by every window this frame
    ImGui::End();
}

void PlotWindows::render_cell(ScopeAppState& state, int win, int cell,
                              const std::vector<int>& slots, bool has_capture) {
    std::string plot_id = "##cell" + std::to_string(win) + "_" + std::to_string(cell);
    if (!ImPlot::BeginPlot(plot_id.c_str(), ImVec2(-1, -1))) return;
    ImPlotAxisFlags y_flags = state.fix_axis ? 0 : ImPlotAxisFlags_AutoFit;
    ImPlot::SetupAxes("time [s]", nullptr, 0, y_flags);
    if (has_capture ? capture_fit_ : !state.frozen)
        ImPlot::SetupAxisLimits(ImAxis_X1, x_min_, x_max_, ImPlotCond_Always);
    ImPlot::SetupFinish();

    const CellData* cd = nullptr;
    if (win < int(data_.size()) && cell < int(data_[size_t(win)].cells.size()))
        cd = &data_[size_t(win)].cells[size_t(cell)];
    if (cd) {
        for (const Series& s : cd->series) {
            const auto& ch = state.config.channel_settings[size_t(s.slot)];
            ImVec4 color;
            if (parse_color(ch.color, color)) ImPlot::SetNextLineStyle(color);
            ImPlot::PlotLine(s.label.c_str(), s.xs.data(), s.ys.data(),
                             int(s.xs.size()));
        }
    }
    // Trigger overlay: level line in cells that plot the source channel,
    // time crosshair everywhere while a capture is shown.
    bool has_source = std::find(slots.begin(), slots.end(), trigger_slot_) != slots.end();
    if (level_valid_ && has_source) {
        double level = level_display_;
        ImPlot::PlotInfLines("##trig_lvl", &level, 1, ImPlotInfLinesFlags_Horizontal);
    }
    if (has_capture && trigger_time_ >= 0.0) {
        double t = trigger_time_;
        ImPlot::PlotInfLines("##trig_t", &t, 1);
    }
    // Drag&drop: accept a channel from the channel table.
    if (ImPlot::BeginDragDropTargetPlot()) {
        if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload(DND_CHANNEL)) {
            int slot = *static_cast<const int*>(payload->Data);
            if (win == 0 && cell == 0) {
                state.commands.execute(state, "ch_visible",
                                       {std::to_string(slot + 1), "on"});
            } else {
                state.commands.execute(state, "plot_assign",
                                       {std::to_string(win + 1),
                                        std::to_string(cell + 1),
                                        std::to_string(slot + 1)});
            }
        }
        ImPlot::EndDragDropTarget();
    }
    // Right-click a legend entry to remove the channel from this cell.
    if (cd) {
        for (const Series& s : cd->series) {
            if (ImPlot::BeginLegendPopup(s.label.c_str())) {
                if (ImGui::MenuItem("Remove from this plot")) {
                    if (win == 0 && cell == 0 &&
                        state.config.channel_settings[size_t(s.slot)].visible) {
                        state.commands.execute(state, "ch_visible",
                                               {std::to_string(s.slot + 1), "off"});
                    }
                    state.commands.execute(state, "plot_remove",
                                           {std::to_string(win + 1),
                                            std::to_string(cell + 1),
                                            std::to_string(s.slot + 1)});
                }
                ImPlot::EndLegendPopup();
            }
        }
    }
    ImPlot::EndPlot();
}

}  // namespace uz
