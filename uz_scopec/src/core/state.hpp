// Single application state for uz_scopec (GUI-free, unit-testable).
//
// Owns the config, the network client, the sample ring, the logger and the
// console/command registry.  The reader thread only touches the ring, the
// engine, the slowdata store and the event queue; everything UI-facing
// happens on the main thread (poll_events drains reader-thread events).
#pragma once

#include <atomic>
#include <deque>
#include <memory>
#include <mutex>
#include <optional>
#include <string>
#include <vector>

#include "core/acquisition.hpp"
#include "core/capture_log.hpp"
#include "core/commands.hpp"
#include "core/config.hpp"
#include "core/header_parser.hpp"
#include "core/lifecheck.hpp"
#include "core/netclient.hpp"
#include "core/protocol.hpp"
#include "core/ring.hpp"
#include "core/slowdata.hpp"

namespace uz {

// Rate auto-detect (ported from the JavaScope): wait for the stream to
// settle, measure over a window, snap to nominal when close, else round to
// the nearest kHz, clamped.
inline constexpr double RATE_DETECT_DELAY_S = 5.0;
inline constexpr double RATE_DETECT_WINDOW_S = 5.0;
inline constexpr double RATE_SNAP_FRACTION = 0.05;
inline constexpr double RATE_MAX_HZ = 200000.0;

struct SentCommand {
    double timestamp;
    uint32_t cmd_id;
    float value;
    std::string label;
};

struct ScopeAppState {
    explicit ScopeAppState(std::string settings_path = SETTINGS_FILENAME);
    ~ScopeAppState();

    // --- derived ---------------------------------------------------------
    double sample_rate() const {
        return detected_rate > 0 ? detected_rate : 1e6 / config.timestep_usec;
    }
    double timestep_s() const { return 1.0 / sample_rate(); }
    std::string observable_name(int index) const;
    bool connected() const { return client && client->connected(); }

    // --- connection ------------------------------------------------------
    void connect();
    void disconnect();

    // --- device commands -------------------------------------------------
    int button_id(const std::string& name) const;  // throws CommandError
    void send_button(const std::string& name, float value = 1.0f);
    void send_field(int n, float value);
    void select_observable(int slot, int observable);

    // --- trigger ---------------------------------------------------------
    void arm_trigger();  // throws CommandError
    void disarm_trigger();
    void rearm_if_armed();
    std::shared_ptr<AcquisitionEngine> engine() const {
        std::lock_guard lock(ptr_mutex_);
        return engine_;
    }

    // --- logging ---------------------------------------------------------
    std::string start_log();  // returns path; throws CommandError
    std::string stop_log();   // returns summary; throws CommandError
    bool logging() const {
        std::lock_guard lock(ptr_mutex_);
        return logger_ != nullptr;
    }
    LoggerStats logger_stats() const {
        std::lock_guard lock(ptr_mutex_);
        return logger_ ? logger_->stats() : LoggerStats{};
    }
    std::string export_capture(const std::string& path = "");  // returns path

    // --- geometry / timing (require disconnect) --------------------------
    void set_geometry(int channels, int samples_per_packet);
    void set_timestep(double usec);
    void rebuild_ring();

    // --- per-frame housekeeping (UI thread) ------------------------------
    void poll_events();
    void start_rate_probe();  // manual detect_rate: measure now
    bool alive() const;
    void shutdown();

    // --- plot windows ----------------------------------------------------
    void plot_add();
    PlotWindowConfig& plot(int window_1based);  // throws CommandError

    // reader-thread entry (public for tests: feed synthetic FrameViews)
    void on_frames(const FrameView& view);

    std::vector<SentCommand> cmd_trace_snapshot() const;

    // --- public state (UI thread unless noted) ---------------------------
    std::string settings_path;
    ScopeConfig config;
    Console console;
    CommandRegistry commands;
    std::optional<HeaderConfig> header;
    std::unique_ptr<ScopeClient> client;
    std::unique_ptr<ChannelRing> ring;
    Lifecheck lifecheck;  // reader thread writes, UI reads counters (int64)
    SlowDataStore slowdata;
    bool frozen = false;
    bool fix_axis = false;
    double detected_rate = 0.0;
    std::atomic<uint32_t> last_status{0};
    std::string last_log_path;

private:
    void load_header();
    void refresh_lifecheck_slot();
    void trace(uint32_t cmd_id, float value, const std::string& label);
    void post_event(const std::string& level, const std::string& message);
    void ext_log_edge(bool bit);
    void poll_rate_detect();
    void register_builtins();
    void on_connect_burst();

    std::shared_ptr<AcquisitionEngine> engine_;
    std::shared_ptr<CaptureLogger> logger_;
    mutable std::mutex ptr_mutex_;

    std::deque<std::pair<std::string, std::string>> events_;
    std::mutex events_mutex_;
    std::deque<SentCommand> cmd_trace_;
    mutable std::mutex trace_mutex_;

    std::atomic<int> lifecheck_slot_{-1};
    bool prev_ext_log_ = false;  // reader thread only
    // Rate probe: (start time, samples at start); active when start >= 0.
    double rate_probe_t0_ = -1.0;
    int64_t rate_probe_samples_ = 0;
    bool rate_probe_manual_ = false;

    std::vector<float> scratch_;  // reader thread: gather buffers
};

}  // namespace uz
