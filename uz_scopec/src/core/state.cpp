#include "core/state.hpp"

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <ctime>
#include <filesystem>

namespace uz {
namespace {

std::string strip_jso(const std::string& name) {
    if (name.rfind("JSO_", 0) == 0) return name.substr(4);
    return name;
}

std::string format_float(double v) {
    char buf[32];
    std::snprintf(buf, sizeof(buf), "%g", v);
    return buf;
}

TrigEdge parse_edge(const std::string& s) {
    if (s == "rising") return TrigEdge::Rising;
    if (s == "falling") return TrigEdge::Falling;
    throw CommandError("edge must be rising or falling");
}

TrigMode parse_mode(const std::string& s) {
    if (s == "auto") return TrigMode::Auto;
    if (s == "normal") return TrigMode::Normal;
    if (s == "single") return TrigMode::Single;
    throw CommandError("mode must be auto, normal or single");
}

}  // namespace

ScopeAppState::ScopeAppState(std::string settings_path_)
    : settings_path(std::move(settings_path_)) {
    if (auto loaded = ScopeConfig::load(settings_path)) config = std::move(*loaded);
    // An armed trigger never survives a restart — the engine is gone.
    config.trigger.enabled = false;
    load_header();
    if (header) slowdata.rename(header->slowdata);
    rebuild_ring();
    refresh_lifecheck_slot();
    register_builtins();
}

ScopeAppState::~ScopeAppState() { disconnect(); }

std::string ScopeAppState::observable_name(int index) const {
    if (header && index >= 0 && index < int(header->observables.size()))
        return header->observables[index];
    return "observable_" + std::to_string(index);
}

void ScopeAppState::load_header() {
    namespace fs = std::filesystem;
    fs::path path = config.header_path;
    if (config.header_path.empty() || !fs::is_regular_file(path)) {
        if (auto found = find_header()) path = *found;
    }
    if (fs::is_regular_file(path)) {
        header = parse_header(path);
        for (const auto& w : header->warnings) console.warn("javascope.h: " + w);
        console.info("header " + path.string() + ": " +
                     std::to_string(header->observables.size()) + " observables, " +
                     std::to_string(header->slowdata.size()) + " slowdata");
    } else {
        console.warn("javascope.h not found; observable names and command ids "
                     "unavailable");
    }
}

void ScopeAppState::rebuild_ring() {
    int64_t capacity = ring_capacity(config.channels, sample_rate(),
                                     config.ring_seconds, config.max_ring_bytes);
    ring = std::make_unique<ChannelRing>(config.channels, capacity);
    lifecheck.reset();
}

void ScopeAppState::refresh_lifecheck_slot() {
    int slot = -1;
    if (header) {
        if (auto idx = header->observable_index("JSO_lifecheck")) {
            for (size_t i = 0; i < config.channel_settings.size(); ++i) {
                if (config.channel_settings[i].observable == *idx) {
                    slot = int(i);
                    break;
                }
            }
        }
    }
    lifecheck_slot_.store(slot);
}

// --- connection -----------------------------------------------------------

void ScopeAppState::connect() {
    if (client) throw CommandError("already connected (disconnect first)");
    ClientCallbacks cbs;
    cbs.on_frames = [this](const FrameView& v) { on_frames(v); };
    cbs.on_connect = [this](ScopeClient& c) {
        // Full channel-select burst so device and config agree (JavaScope
        // does the same).  With pacing on these ride the first ack slots.
        for (size_t slot = 0; slot < config.channel_settings.size(); ++slot) {
            int obs = config.channel_settings[slot].observable;
            c.send_command(encode_channel_select(int(slot), obs));
            trace(CHANNEL_SELECT_BASE + uint32_t(slot), float(obs),
                  "select CH" + std::to_string(slot + 1));
        }
        lifecheck.reset();
        post_event("ok", "connected to " + c.ip + ":" + std::to_string(c.port));
    };
    cbs.on_disconnect = [this](const std::string& reason) {
        post_event("warn", "connection lost: " + reason + " (reconnecting)");
    };
    client = std::make_unique<ScopeClient>(config.geometry(), config.ip, config.port,
                                           config.ack_pacing, std::move(cbs));
    client->start();
}

void ScopeAppState::disconnect() {
    std::unique_ptr<ScopeClient> c = std::move(client);
    if (c) c->stop();
}

// --- reader-thread ingest -------------------------------------------------

void ScopeAppState::on_frames(const FrameView& view) {
    const int n = view.geom.samples_per_packet;
    const int c = view.geom.channels;
    const int64_t block = int64_t(view.k) * n;
    int64_t start_index = ring->total_written();
    ring->append_frames(view);
    last_status.store(view.status(view.k - 1));

    std::shared_ptr<AcquisitionEngine> engine;
    std::shared_ptr<CaptureLogger> logger;
    {
        std::lock_guard lock(ptr_mutex_);
        engine = engine_;
        logger = logger_;
    }
    if (engine && engine->channel < c) {
        scratch_.resize(size_t(block));
        for (int i = 0; i < view.k; ++i)
            std::memcpy(scratch_.data() + size_t(i) * n,
                        view.channel(i, engine->channel), size_t(n) * 4);
        engine->on_block(scratch_.data(), block, start_index);
    }
    int lc_slot = lifecheck_slot_.load();
    if (lc_slot >= 0 && lc_slot < c) {
        scratch_.resize(size_t(block));
        for (int i = 0; i < view.k; ++i)
            std::memcpy(scratch_.data() + size_t(i) * n, view.channel(i, lc_slot),
                        size_t(n) * 4);
        lifecheck.update(scratch_.data(), block);
    }
    {
        std::vector<int32_t> ids(static_cast<size_t>(block));
        std::vector<uint32_t> raw(static_cast<size_t>(block));
        for (int i = 0; i < view.k; ++i) {
            for (int j = 0; j < n; ++j) {
                ids[size_t(i) * n + j] = view.slow_id(i, j);
                raw[size_t(i) * n + j] = view.slow_raw(i, j);
            }
        }
        slowdata.on_block(ids.data(), raw.data(), block);
    }
    if (config.logging.ext_trigger)
        ext_log_edge(status_bit(last_status.load(), STATUS_BIT_EXT_LOG));
    {
        std::lock_guard lock(ptr_mutex_);
        logger = logger_;  // ext_log_edge may have started/stopped a log
    }
    if (logger) {
        std::vector<float> chunk(size_t(c) * size_t(block));
        for (int ch = 0; ch < c; ++ch)
            for (int i = 0; i < view.k; ++i)
                std::memcpy(chunk.data() + size_t(ch) * block + size_t(i) * n,
                            view.channel(i, ch), size_t(n) * 4);
        logger->submit(chunk.data(), c, block, start_index);
    }
}

// --- device commands ------------------------------------------------------

int ScopeAppState::button_id(const std::string& name) const {
    if (header) {
        if (auto id = header->button_id(name)) return *id;
    }
    // Canonical gui_button_mapping fallback (header unavailable).
    if (name == "Enable_System") return 1;
    if (name == "Enable_Control") return 2;
    if (name == "Stop") return 3;
    if (name == "Error_Reset") return 32;
    if (name.rfind("My_Button_", 0) == 0) return 23 + std::stoi(name.substr(10));
    if (name.rfind("Set_Send_Field_", 0) == 0) return 3 + std::stoi(name.substr(15));
    throw CommandError("unknown button: " + name);
}

void ScopeAppState::trace(uint32_t cmd_id, float value, const std::string& label) {
    std::lock_guard lock(trace_mutex_);
    cmd_trace_.push_back({monotonic_seconds(), cmd_id, value, label});
    while (cmd_trace_.size() > 200) cmd_trace_.pop_front();
}

std::vector<SentCommand> ScopeAppState::cmd_trace_snapshot() const {
    std::lock_guard lock(trace_mutex_);
    return {cmd_trace_.begin(), cmd_trace_.end()};
}

void ScopeAppState::send_button(const std::string& name, float value) {
    if (!client) throw CommandError("not connected");
    int id = button_id(name);
    client->send_command(encode_command(uint32_t(id), value));
    trace(uint32_t(id), value, name);
}

void ScopeAppState::send_field(int n, float value) {
    if (!client) throw CommandError("not connected");
    int id = button_id("Set_Send_Field_" + std::to_string(n));
    client->send_command(encode_command(uint32_t(id), value));
    trace(uint32_t(id), value, "Set_Send_Field_" + std::to_string(n));
}

void ScopeAppState::select_observable(int slot, int observable) {
    config.channel_settings.at(size_t(slot)).observable = observable;
    refresh_lifecheck_slot();
    if (client) {
        client->send_command(encode_channel_select(slot, observable));
        trace(CHANNEL_SELECT_BASE + uint32_t(slot), float(observable),
              "select CH" + std::to_string(slot + 1));
    }
}

// --- trigger --------------------------------------------------------------

void ScopeAppState::arm_trigger() {
    const TriggerSettings& cfg = config.trigger;
    int slot;
    if (cfg.channel >= 1) {
        slot = cfg.channel - 1;
    } else {  // auto: first visible channel
        slot = 0;
        for (size_t i = 0; i < config.channel_settings.size(); ++i) {
            if (config.channel_settings[i].visible) {
                slot = int(i);
                break;
            }
        }
    }
    if (slot >= config.channels)
        throw CommandError("trigger channel out of range: CH" + std::to_string(slot + 1));
    int64_t window = int64_t(config.window_seconds * sample_rate());
    window = std::clamp<int64_t>(window, 2, ring->capacity());
    auto engine = std::make_shared<AcquisitionEngine>(
        *ring, slot, parse_edge(cfg.edge), cfg.level, cfg.pretrigger, window,
        parse_mode(cfg.mode));
    engine->arm();
    {
        std::lock_guard lock(ptr_mutex_);
        engine_ = std::move(engine);
    }
    config.trigger.enabled = true;
}

void ScopeAppState::disarm_trigger() {
    std::lock_guard lock(ptr_mutex_);
    engine_.reset();
    config.trigger.enabled = false;
}

void ScopeAppState::rearm_if_armed() {
    if (config.trigger.enabled) arm_trigger();
}

// --- logging --------------------------------------------------------------

std::string ScopeAppState::start_log() {
    {
        std::lock_guard lock(ptr_mutex_);
        if (logger_) throw CommandError("already logging (log_stop first)");
    }
    std::vector<std::string> names;
    for (const auto& ch : config.channel_settings)
        names.push_back(observable_name(ch.observable));
    auto logger = std::make_shared<CaptureLogger>(
        config.logging.directory, config.logging.format, make_column_names(names),
        timestep_s(), config.logging.every_n);
    std::string path = logger->path().string();
    std::lock_guard lock(ptr_mutex_);
    logger_ = std::move(logger);
    return path;
}

std::string ScopeAppState::stop_log() {
    std::shared_ptr<CaptureLogger> logger;
    {
        std::lock_guard lock(ptr_mutex_);
        logger = std::move(logger_);
    }
    if (!logger) throw CommandError("not logging");
    std::string path = logger->close().string();
    last_log_path = path;
    LoggerStats s = logger->stats();
    std::string msg = "closed " + path + " (" + std::to_string(s.rows_written) + " rows)";
    if (s.chunks_dropped) {
        msg += " — WARNING: " + std::to_string(s.chunks_dropped) + " chunks (" +
               std::to_string(s.samples_dropped) +
               " samples) dropped; use bin format for guaranteed rate";
    }
    if (!logger->error().empty()) msg += " — ERROR: " + logger->error();
    return msg;
}

void ScopeAppState::ext_log_edge(bool bit) {
    // Status bit 12 (reader thread): rising -> start log, falling -> stop.
    if (bit && !prev_ext_log_ && !logging()) {
        try {
            post_event("ok", "external trigger: logging to " + start_log());
        } catch (const std::exception& exc) {
            post_event("error", std::string("external log start failed: ") + exc.what());
        }
    } else if (!bit && prev_ext_log_ && logging()) {
        try {
            post_event("ok", "external trigger: " + stop_log());
        } catch (const std::exception& exc) {
            post_event("error", std::string("external log stop failed: ") + exc.what());
        }
    }
    prev_ext_log_ = bit;
}

std::string ScopeAppState::export_capture(const std::string& path_arg) {
    std::shared_ptr<AcquisitionEngine> engine = this->engine();
    std::shared_ptr<const Capture> cap = engine ? engine->capture() : nullptr;
    if (!cap) throw CommandError("no trigger capture to export");
    namespace fs = std::filesystem;
    fs::path path = path_arg;
    if (path_arg.empty()) {
        fs::create_directories(config.logging.directory);
        std::time_t t = std::time(nullptr);
        std::tm tm{};
#ifdef _WIN32
        localtime_s(&tm, &t);
#else
        localtime_r(&t, &tm);
#endif
        char buf[64];
        std::strftime(buf, sizeof(buf), "Capture_%Y-%m-%d_%H-%M-%S.csv", &tm);
        path = fs::path(config.logging.directory) / buf;
    }
    std::vector<std::string> names;
    for (const auto& ch : config.channel_settings)
        names.push_back(observable_name(ch.observable));
    write_capture(path, make_column_names(names), cap->window.data.data(),
                  cap->window.rows, cap->window.count, cap->window.start, timestep_s());
    last_log_path = path.string();
    return path.string();
}

// --- geometry / timing ----------------------------------------------------

void ScopeAppState::set_geometry(int channels, int samples_per_packet) {
    if (client) throw CommandError("disconnect before changing the frame geometry");
    if (logging()) throw CommandError("stop logging before changing the frame geometry");
    if (channels < 1 || samples_per_packet < 1)
        throw CommandError("channels and samples per packet must be >= 1");
    config.channels = channels;
    config.samples_per_packet = samples_per_packet;
    config.ensure_channel_count();
    config.ensure_plots();
    disarm_trigger();
    rebuild_ring();
    refresh_lifecheck_slot();
}

void ScopeAppState::set_timestep(double usec) {
    if (client) throw CommandError("disconnect before changing the timestep");
    if (logging()) throw CommandError("stop logging before changing the timestep");
    if (usec <= 0) throw CommandError("timestep must be > 0 microseconds");
    config.timestep_usec = usec;
    detected_rate = 0.0;
    disarm_trigger();
    rebuild_ring();
}

// --- events / rate detect -------------------------------------------------

void ScopeAppState::post_event(const std::string& level, const std::string& message) {
    std::lock_guard lock(events_mutex_);
    events_.emplace_back(level, message);
    while (events_.size() > 64) events_.pop_front();
}

void ScopeAppState::poll_events() {
    std::deque<std::pair<std::string, std::string>> drained;
    {
        std::lock_guard lock(events_mutex_);
        drained.swap(events_);
    }
    for (const auto& [level, message] : drained) {
        if (level == "warn")
            console.warn(message);
        else if (level == "error")
            console.error(message);
        else
            console.info(message);
    }
    poll_rate_detect();
}

void ScopeAppState::start_rate_probe() {
    detected_rate = 0.0;
    rate_probe_t0_ = -1.0;
    rate_probe_manual_ = true;
}

void ScopeAppState::poll_rate_detect() {
    if (!client || !client->connected()) {
        rate_probe_t0_ = -1.0;
        return;
    }
    bool wanted = rate_probe_manual_ ||
                  (config.auto_detect_rate && detected_rate <= 0.0);
    if (!wanted) return;
    double now = monotonic_seconds();
    if (rate_probe_t0_ < 0) {
        double delay = rate_probe_manual_ ? 0.0 : RATE_DETECT_DELAY_S;
        if (now - client->stats.connected_since.load() >= delay) {
            rate_probe_t0_ = now;
            rate_probe_samples_ = client->stats.samples.load();
        }
        return;
    }
    if (now - rate_probe_t0_ < RATE_DETECT_WINDOW_S) return;
    double raw = double(client->stats.samples.load() - rate_probe_samples_) /
                 (now - rate_probe_t0_);
    rate_probe_t0_ = -1.0;
    rate_probe_manual_ = false;
    if (raw <= 0) return;
    double nominal = 1e6 / config.timestep_usec;
    double rate;
    if (std::abs(raw - nominal) <= RATE_SNAP_FRACTION * nominal)
        rate = nominal;
    else
        rate = std::min(std::max(1.0, std::round(raw / 1000.0)) * 1000.0, RATE_MAX_HZ);
    detected_rate = rate;
    if (rate == nominal) {
        console.info("sample rate confirmed: " + format_float(rate) + " Hz (measured " +
                     format_float(raw) + " Hz)");
    } else {
        console.warn("detected sample rate " + format_float(rate) +
                     " Hz differs from the configured " + format_float(nominal) +
                     " Hz (measured " + format_float(raw) +
                     " Hz); the time axis now uses the detected rate — check "
                     "timestep/geometry if unexpected");
    }
}

bool ScopeAppState::alive() const {
    return client && client->connected() &&
           monotonic_seconds() - client->stats.last_rx_monotonic.load() < 0.5;
}

void ScopeAppState::shutdown() {
    if (logging()) {
        try {
            console.info(stop_log());
        } catch (const std::exception&) {
        }
    }
    disconnect();
    config.save(settings_path);
}

// --- plot windows ---------------------------------------------------------

void ScopeAppState::plot_add() {
    PlotWindowConfig p;
    p.title = "Scope " + std::to_string(config.plots.size() + 1);
    p.ensure_cells();
    config.plots.push_back(std::move(p));
}

PlotWindowConfig& ScopeAppState::plot(int window_1based) {
    if (window_1based < 1 || window_1based > int(config.plots.size()))
        throw CommandError("plot window must be 1.." +
                           std::to_string(config.plots.size()));
    return config.plots[size_t(window_1based - 1)];
}

}  // namespace uz
