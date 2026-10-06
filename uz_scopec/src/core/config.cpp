#include "core/config.hpp"

#include <algorithm>
#include <fstream>
#include <nlohmann/json.hpp>
#include <sstream>

namespace uz {

using nlohmann::json;

ScopeConfig::ScopeConfig() {
    ensure_channel_count();
    ensure_plots();
}

void ScopeConfig::ensure_channel_count() {
    channel_settings.resize(size_t(std::max(1, channels)));
}

void ScopeConfig::ensure_plots() {
    if (plots.empty()) plots.push_back({});
    for (size_t i = 0; i < plots.size(); ++i) {
        if (plots[i].title.empty()) plots[i].title = "Scope " + std::to_string(i + 1);
        plots[i].rows = std::clamp(plots[i].rows, 1, 4);
        plots[i].cols = std::clamp(plots[i].cols, 1, 4);
        plots[i].ensure_cells();
        for (auto& cell : plots[i].cells) {
            std::erase_if(cell.slots, [&](int s) { return s < 0 || s >= channels; });
        }
    }
}

namespace {

template <typename T>
void get_to(const json& j, const char* key, T& out) {
    if (auto it = j.find(key); it != j.end()) {
        try {
            out = it->get<T>();
        } catch (const json::exception&) {
            // tolerate wrong-typed keys (forward compatibility)
        }
    }
}

json channel_to_json(const ChannelSettings& c) {
    json j;
    j["observable"] = c.observable;
    j["visible"] = c.visible;
    j["scale"] = c.scale;
    j["offset"] = c.offset;
    if (!c.color.empty()) j["color"] = c.color;
    return j;
}

json plot_to_json(const PlotWindowConfig& p) {
    json j;
    j["title"] = p.title;
    j["rows"] = p.rows;
    j["cols"] = p.cols;
    j["open"] = p.open;
    json cells = json::array();
    for (const auto& cell : p.cells) cells.push_back(cell.slots);
    j["cells"] = cells;
    return j;
}

}  // namespace

std::string ScopeConfig::to_json() const {
    json j;
    j["version"] = version;
    j["ip"] = ip;
    j["port"] = port;
    j["auto_connect"] = auto_connect;
    j["ack_pacing"] = ack_pacing;
    j["channels"] = channels;
    j["samples_per_packet"] = samples_per_packet;
    j["timestep_usec"] = timestep_usec;
    j["auto_detect_rate"] = auto_detect_rate;
    j["header_path"] = header_path;
    j["ring_seconds"] = ring_seconds;
    j["max_ring_bytes"] = max_ring_bytes;
    j["refresh_hz"] = refresh_hz;
    j["window_seconds"] = window_seconds;
    json chs = json::array();
    for (const auto& c : channel_settings) chs.push_back(channel_to_json(c));
    j["channel_settings"] = chs;
    j["trigger"] = {{"channel", trigger.channel}, {"edge", trigger.edge},
                    {"level", trigger.level},     {"pretrigger", trigger.pretrigger},
                    {"mode", trigger.mode},       {"enabled", trigger.enabled}};
    j["logging"] = {{"directory", logging.directory},
                    {"format", logging.format},
                    {"every_n", logging.every_n},
                    {"ext_trigger", logging.ext_trigger}};
    json ps = json::array();
    for (const auto& p : plots) ps.push_back(plot_to_json(p));
    j["plots"] = ps;
    return j.dump(2);
}

void ScopeConfig::save(const std::string& path) const {
    std::ofstream out(path, std::ios::binary);
    out << to_json() << "\n";
}

ScopeConfig ScopeConfig::from_json(const std::string& text) {
    ScopeConfig cfg;
    json j = json::parse(text, nullptr, /*allow_exceptions=*/true);
    get_to(j, "version", cfg.version);
    get_to(j, "ip", cfg.ip);
    get_to(j, "port", cfg.port);
    get_to(j, "auto_connect", cfg.auto_connect);
    get_to(j, "ack_pacing", cfg.ack_pacing);
    get_to(j, "channels", cfg.channels);
    get_to(j, "samples_per_packet", cfg.samples_per_packet);
    get_to(j, "timestep_usec", cfg.timestep_usec);
    get_to(j, "auto_detect_rate", cfg.auto_detect_rate);
    get_to(j, "header_path", cfg.header_path);
    get_to(j, "ring_seconds", cfg.ring_seconds);
    get_to(j, "max_ring_bytes", cfg.max_ring_bytes);
    get_to(j, "refresh_hz", cfg.refresh_hz);
    get_to(j, "window_seconds", cfg.window_seconds);
    if (auto it = j.find("channel_settings"); it != j.end() && it->is_array()) {
        cfg.channel_settings.clear();
        for (const auto& e : *it) {
            ChannelSettings c;
            if (e.is_object()) {
                get_to(e, "observable", c.observable);
                get_to(e, "visible", c.visible);
                get_to(e, "scale", c.scale);
                get_to(e, "offset", c.offset);
                get_to(e, "color", c.color);
            }
            cfg.channel_settings.push_back(std::move(c));
        }
    }
    if (auto it = j.find("trigger"); it != j.end() && it->is_object()) {
        get_to(*it, "channel", cfg.trigger.channel);
        get_to(*it, "edge", cfg.trigger.edge);
        get_to(*it, "level", cfg.trigger.level);
        get_to(*it, "pretrigger", cfg.trigger.pretrigger);
        get_to(*it, "mode", cfg.trigger.mode);
        get_to(*it, "enabled", cfg.trigger.enabled);
    }
    if (auto it = j.find("logging"); it != j.end() && it->is_object()) {
        get_to(*it, "directory", cfg.logging.directory);
        get_to(*it, "format", cfg.logging.format);
        get_to(*it, "every_n", cfg.logging.every_n);
        get_to(*it, "ext_trigger", cfg.logging.ext_trigger);
    }
    if (auto it = j.find("plots"); it != j.end() && it->is_array()) {
        cfg.plots.clear();
        for (const auto& e : *it) {
            PlotWindowConfig p;
            if (e.is_object()) {
                get_to(e, "title", p.title);
                get_to(e, "rows", p.rows);
                get_to(e, "cols", p.cols);
                get_to(e, "open", p.open);
                if (auto c = e.find("cells"); c != e.end() && c->is_array()) {
                    for (const auto& cell : *c) {
                        PlotCell pc;
                        if (cell.is_array()) {
                            for (const auto& s : cell)
                                if (s.is_number_integer()) pc.slots.push_back(s.get<int>());
                        }
                        p.cells.push_back(std::move(pc));
                    }
                }
            }
            cfg.plots.push_back(std::move(p));
        }
    }
    cfg.ensure_channel_count();
    cfg.ensure_plots();
    return cfg;
}

std::optional<ScopeConfig> ScopeConfig::load(const std::string& path) {
    std::ifstream in(path, std::ios::binary);
    if (!in) return std::nullopt;
    std::ostringstream buf;
    buf << in.rdbuf();
    try {
        return from_json(buf.str());
    } catch (const json::exception&) {
        return std::nullopt;
    }
}

}  // namespace uz
