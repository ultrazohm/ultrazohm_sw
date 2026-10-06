// Persistent scope configuration (JSON, forward-compatible load).
//
// Field names match uz_scope's uz_scope_settings.json where the features
// overlap; uz_scopec adds the "plots" section (multiple plot windows with a
// rows x cols subplot grid, each cell holding a list of channel slots).
#pragma once

#include <algorithm>
#include <optional>
#include <string>
#include <vector>

#include "core/protocol.hpp"

namespace uz {

inline constexpr const char* SETTINGS_FILENAME = "uz_scopec_settings.json";

struct ChannelSettings {
    int observable = 0;   // index into the JS_OberservableData enum
    bool visible = false; // shown in plot window 1, cell 0 (JavaScope parity)
    float scale = 1.0f;
    float offset = 0.0f;
    std::string color;    // "#RRGGBB" or empty for auto palette
};

struct TriggerSettings {
    int channel = 0;  // scope channel slot, 1-based; 0 = auto (first visible)
    std::string edge = "rising";
    float level = 0.0f;
    float pretrigger = 0.5f;  // fraction of the capture window before the trigger
    std::string mode = "auto";
    bool enabled = false;
};

struct LoggingSettings {
    std::string directory = "logs";
    std::string format = "csv";  // "csv" or "bin" (parquet needs the Python scope)
    int every_n = 1;
    bool ext_trigger = false;  // arm logging on status bit 12
};

// One plot window: a rows x cols ImPlot subplot grid; each cell plots the
// channel slots dropped into it.  Window 0 cell 0 additionally mirrors the
// classic per-channel "visible" flags.
struct PlotCell {
    std::vector<int> slots;
};

struct PlotWindowConfig {
    std::string title = "Scope 1";
    int rows = 1;
    int cols = 1;
    bool open = true;
    std::vector<PlotCell> cells;  // rows * cols entries

    void ensure_cells() {
        cells.resize(size_t(std::max(1, rows)) * size_t(std::max(1, cols)));
    }
};

struct ScopeConfig {
    int version = 1;
    // connection
    std::string ip = "192.168.1.233";
    int port = 1000;
    bool auto_connect = false;
    bool ack_pacing = true;  // one 8-byte (zero-)ack per received frame
    // frame geometry / timing (must match the firmware build)
    int channels = 20;
    int samples_per_packet = 15;
    double timestep_usec = 100.0;
    bool auto_detect_rate = true;
    std::string header_path;
    // acquisition / display
    double ring_seconds = 10.0;
    int64_t max_ring_bytes = 512ll * 1024 * 1024;
    double refresh_hz = 30.0;
    double window_seconds = 0.5;
    // sub-configs
    std::vector<ChannelSettings> channel_settings;
    TriggerSettings trigger;
    LoggingSettings logging;
    std::vector<PlotWindowConfig> plots;

    ScopeConfig();

    FrameGeometry geometry() const { return {channels, samples_per_packet}; }
    void ensure_channel_count();
    void ensure_plots();

    std::string to_json() const;
    void save(const std::string& path) const;
    static ScopeConfig from_json(const std::string& text);  // ignores unknown keys
    static std::optional<ScopeConfig> load(const std::string& path);
};

}  // namespace uz
