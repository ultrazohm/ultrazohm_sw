// All UI panels.  Each render() runs once per frame on the UI thread.
#pragma once

#include <string>
#include <vector>

#include "core/state.hpp"

namespace uz {

// ImGui drag&drop payload type: an int channel slot dragged from the
// channel table into any plot cell.
inline constexpr const char* DND_CHANNEL = "UZ_CHANNEL";

// The plot windows: window 0 is the classic scope (cell 0 additionally shows
// the per-channel `visible` flags); every window is an independent dockable
// ImGui window with a rows x cols ImPlot subplot grid.  With multi-viewport
// enabled a window dragged outside the main window becomes an OS window.
class PlotWindows {
public:
    void render(ScopeAppState& state);

private:
    struct Series {
        std::string label;
        std::vector<double> xs, ys;
        int slot;
    };
    struct CellData {
        std::vector<Series> series;
    };
    struct WindowData {
        std::vector<CellData> cells;
    };

    void render_window(ScopeAppState& state, int index);
    void render_cell(ScopeAppState& state, int win, int cell,
                     const std::vector<int>& slots, bool has_capture);
    void rebuild(ScopeAppState& state);
    std::vector<int> cell_slots(const ScopeAppState& state, int win, int cell) const;

    std::vector<WindowData> data_;
    double next_refresh_ = 0.0;
    double x_min_ = 0.0, x_max_ = 1.0;
    int capture_seq_ = 0;
    bool capture_fit_ = false;
    bool showing_capture_ = false;
    double trigger_time_ = -1.0;  // < 0: none
    double level_display_ = 0.0;
    bool level_valid_ = false;
    int trigger_slot_ = -1;
};

class ChannelsPanel {
public:
    void render(ScopeAppState& state);

private:
    char filter_[64] = {};
};

class ControlPanel {
public:
    void render(ScopeAppState& state);

private:
    std::vector<float> send_values_;
};

class TriggerPanel {
public:
    void render(ScopeAppState& state);

private:
    float level_input_ = 0.0f;
    bool level_init_ = false;
};

class SlowDataPanel {
public:
    void render(ScopeAppState& state);
};

class LoggingPanel {
public:
    void render(ScopeAppState& state);

private:
    char dir_[256] = {};
    bool dir_init_ = false;
};

class DiagnosticsPanel {
public:
    void render(ScopeAppState& state);

private:
    double window_t0_ = 0.0;
    int64_t window_bytes_ = 0;
    double rate_mbps_ = 0.0;
};

class ConsolePanel {
public:
    void render(ScopeAppState& state);

private:
    char input_[512] = {};
    bool scroll_to_bottom_ = false;
};

class StatusBar {
public:
    void render(ScopeAppState& state);

private:
    double window_t0_ = 0.0;
    int64_t window_samples_ = 0;
    double sample_rate_measured_ = 0.0;
};

}  // namespace uz
