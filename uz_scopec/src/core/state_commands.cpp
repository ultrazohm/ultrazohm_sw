// Built-in command set — the uz_scope command names, same semantics.
#include <algorithm>
#include <cstdio>

#include "core/state.hpp"

namespace uz {
namespace {

int channel_arg(ScopeAppState& s, const std::vector<std::string>& args, size_t i) {
    int ch = arg_int(args, i);
    if (ch < 1 || ch > s.config.channels)
        throw CommandError("channel must be 1.." + std::to_string(s.config.channels));
    return ch;
}

std::string fmt(double v) {
    char buf[32];
    std::snprintf(buf, sizeof(buf), "%g", v);
    return buf;
}

}  // namespace

void ScopeAppState::register_builtins() {
    auto& reg = commands;

    // --- connection -------------------------------------------------------
    reg.add("connect", "ip?", [](ScopeAppState& s, const auto& args) {
        std::string ip = arg_str(args, 0);
        // An explicit ip becomes the new default (same as set_ip + connect).
        if (!ip.empty()) s.config.ip = ip;
        s.connect();
        return "connecting to " + s.config.ip + ":" + std::to_string(s.config.port);
    }, "Connect to the device (optional ip overrides and saves the default)");

    reg.add("disconnect", "", [](ScopeAppState& s, const auto&) {
        s.disconnect();
        return std::string("disconnected");
    }, "Close the connection");

    reg.add("set_ip", "ip", [](ScopeAppState& s, const auto& args) {
        s.config.ip = arg_str(args, 0);
        return "ip " + s.config.ip;
    }, "Set the device IP address");

    reg.add("set_port", "port", [](ScopeAppState& s, const auto& args) {
        s.config.port = arg_int(args, 0);
        return "port " + std::to_string(s.config.port);
    }, "Set the device TCP port");

    reg.add("ack_pacing", "on|off", [](ScopeAppState& s, const auto& args) {
        bool on = arg_bool(args, 0);
        s.config.ack_pacing = on;
        if (s.client) s.client->set_ack_pacing(on);
        return std::string("ack pacing ") + (on ? "on" : "off");
    }, "One 8-byte (zero-)ack per received frame (lock-step servers need this)");

    reg.add("set_geometry", "channels, samples", [](ScopeAppState& s, const auto& args) {
        s.set_geometry(arg_int(args, 0), arg_int(args, 1));
        return "geometry " + std::to_string(s.config.channels) + " channels x " +
               std::to_string(s.config.samples_per_packet) + " samples/packet";
    }, "Set the frame geometry (must match the firmware; disconnect first)");

    reg.add("set_timestep", "usec", [](ScopeAppState& s, const auto& args) {
        s.set_timestep(arg_float(args, 0));
        return "timestep " + fmt(s.config.timestep_usec) + " us (" +
               fmt(s.sample_rate()) + " Hz)";
    }, "Set the sample timestep in microseconds (disconnect first)");

    reg.add("detect_rate", "", [](ScopeAppState& s, const auto&) {
        if (!s.connected()) throw CommandError("not connected");
        s.start_rate_probe();
        return "measuring the sample rate over " + fmt(RATE_DETECT_WINDOW_S) + " s";
    }, "Measure the actual sample rate now");

    // --- display ----------------------------------------------------------
    reg.add("run", "", [](ScopeAppState& s, const auto&) {
        s.frozen = false;
        return std::string("running");
    }, "Resume the rolling display");

    reg.add("stop_scope", "", [](ScopeAppState& s, const auto&) {
        s.frozen = true;
        return std::string("display frozen (ingest continues)");
    }, "Freeze the display (ingest continues)");

    reg.add("set_window", "seconds", [](ScopeAppState& s, const auto& args) {
        double w = arg_float(args, 0);
        if (w <= 0) throw CommandError("window must be > 0 seconds");
        s.config.window_seconds = w;
        s.rearm_if_armed();
        return "window " + fmt(w) + " s";
    }, "Visible time window of the rolling display");

    reg.add("fix_axis", "on|off", [](ScopeAppState& s, const auto& args) {
        s.fix_axis = arg_bool(args, 0);
        return std::string("fix axis ") + (s.fix_axis ? "on" : "off");
    }, "Disable y-axis auto-fit");

    reg.add("set_refresh", "hz", [](ScopeAppState& s, const auto& args) {
        double hz = arg_float(args, 0);
        if (hz < 1 || hz > 120) throw CommandError("refresh must be 1..120 Hz");
        s.config.refresh_hz = hz;
        return "refresh " + fmt(hz) + " Hz";
    }, "Plot data refresh rate");

    // --- channels ---------------------------------------------------------
    reg.add("ch_select", "ch, observable", [](ScopeAppState& s, const auto& args) {
        int ch = channel_arg(s, args, 0);
        std::string obs = arg_str(args, 1);
        int index = -1;
        try {
            index = std::stoi(obs);
        } catch (const std::exception&) {
            if (s.header) {
                auto found = s.header->observable_index(obs);
                if (!found) found = s.header->observable_index("JSO_" + obs);
                if (found) index = *found;
            }
        }
        if (index < 0 ||
            (s.header && index >= int(s.header->observables.size())))
            throw CommandError("unknown observable: " + obs);
        s.select_observable(ch - 1, index);
        return "CH" + std::to_string(ch) + " observes " + s.observable_name(index);
    }, "Map a scope channel onto an observable (index or name)");

    reg.add("ch_visible", "ch, on|off", [](ScopeAppState& s, const auto& args) {
        int ch = channel_arg(s, args, 0);
        bool on = arg_bool(args, 1);
        s.config.channel_settings[size_t(ch - 1)].visible = on;
        return "CH" + std::to_string(ch) + (on ? " shown" : " hidden");
    }, "Show/hide a channel in plot window 1");

    reg.add("enable_all", "on|off", [](ScopeAppState& s, const auto& args) {
        bool on = arg_bool(args, 0);
        for (auto& c : s.config.channel_settings) c.visible = on;
        return std::string(on ? "all channels shown" : "all channels hidden");
    }, "Show/hide all channels");

    reg.add("ch_scale", "ch, scale", [](ScopeAppState& s, const auto& args) {
        int ch = channel_arg(s, args, 0);
        double v = arg_float(args, 1);
        if (v == 0.0) throw CommandError("scale must be non-zero");
        s.config.channel_settings[size_t(ch - 1)].scale = float(v);
        return "CH" + std::to_string(ch) + " scale " + fmt(v);
    }, "Display scale: shown value = (y + offset) / scale");

    reg.add("ch_offset", "ch, offset", [](ScopeAppState& s, const auto& args) {
        int ch = channel_arg(s, args, 0);
        double v = arg_float(args, 1);
        s.config.channel_settings[size_t(ch - 1)].offset = float(v);
        return "CH" + std::to_string(ch) + " offset " + fmt(v);
    }, "Display offset: shown value = (y + offset) / scale");

    reg.add("ch_color", "ch, #rrggbb", [](ScopeAppState& s, const auto& args) {
        int ch = channel_arg(s, args, 0);
        s.config.channel_settings[size_t(ch - 1)].color = arg_str(args, 1);
        return "CH" + std::to_string(ch) + " color " + arg_str(args, 1);
    }, "Line color (empty for the auto palette)");

    // --- trigger ----------------------------------------------------------
    reg.add("trig_arm", "on|off", [](ScopeAppState& s, const auto& args) {
        if (arg_bool(args, 0)) {
            s.arm_trigger();
            return std::string("trigger armed");
        }
        s.disarm_trigger();
        return std::string("trigger disarmed");
    }, "Arm/disarm the trigger");

    reg.add("trig_mode", "auto|normal|single", [](ScopeAppState& s, const auto& args) {
        std::string mode = arg_str(args, 0);
        if (mode != "auto" && mode != "normal" && mode != "single")
            throw CommandError("mode must be auto, normal or single");
        s.config.trigger.mode = mode;
        s.rearm_if_armed();
        return "trigger mode " + mode;
    }, "Trigger mode");

    reg.add("trig_source", "ch", [](ScopeAppState& s, const auto& args) {
        int n = arg_int(args, 0);
        if (n < 0 || n > s.config.channels)
            throw CommandError("source must be 0 (auto) or 1.." +
                               std::to_string(s.config.channels));
        s.config.trigger.channel = n;
        s.rearm_if_armed();
        return "trigger source " + (n == 0 ? std::string("auto")
                                           : "CH" + std::to_string(n));
    }, "Trigger source channel (0 = first visible)");

    reg.add("trig_edge", "rising|falling", [](ScopeAppState& s, const auto& args) {
        std::string edge = arg_str(args, 0);
        if (edge != "rising" && edge != "falling")
            throw CommandError("edge must be rising or falling");
        s.config.trigger.edge = edge;
        s.rearm_if_armed();
        return "trigger edge " + edge;
    }, "Trigger edge");

    reg.add("trig_level", "level", [](ScopeAppState& s, const auto& args) {
        s.config.trigger.level = float(arg_float(args, 0));
        s.rearm_if_armed();
        return "trigger level " + fmt(s.config.trigger.level);
    }, "Trigger level (raw signal units)");

    reg.add("trig_pretrigger", "fraction", [](ScopeAppState& s, const auto& args) {
        double p = arg_float(args, 0);
        if (p < 0 || p > 1) throw CommandError("pretrigger must be in 0..1");
        s.config.trigger.pretrigger = float(p);
        s.rearm_if_armed();
        return "pretrigger " + fmt(p);
    }, "Fraction of the window before the trigger (0..1)");

    reg.add("export_capture", "path?", [](ScopeAppState& s, const auto& args) {
        return "exported " + s.export_capture(arg_str(args, 0));
    }, "Write the frozen trigger capture to a CSV file");

    // --- logging ----------------------------------------------------------
    reg.add("log_start", "", [](ScopeAppState& s, const auto&) {
        return "logging to " + s.start_log();
    }, "Start streaming samples to disk");

    reg.add("log_stop", "", [](ScopeAppState& s, const auto&) { return s.stop_log(); },
            "Stop logging and close the file");

    reg.add("log_format", "csv|bin", [](ScopeAppState& s, const auto& args) {
        std::string f = arg_str(args, 0);
        if (f != "csv" && f != "bin")
            throw CommandError("format must be csv or bin "
                               "(parquet: use the Python uz_scope)");
        s.config.logging.format = f;
        return "log format " + f;
    }, "Log file format");

    reg.add("log_every", "n", [](ScopeAppState& s, const auto& args) {
        int n = arg_int(args, 0);
        if (n < 1) throw CommandError("n must be >= 1");
        s.config.logging.every_n = n;
        return "logging every " + std::to_string(n) + ". sample";
    }, "Decimate before writing: log every N-th sample");

    reg.add("log_dir", "path", [](ScopeAppState& s, const auto& args) {
        s.config.logging.directory = arg_str(args, 0, "logs");
        return "log directory " + s.config.logging.directory;
    }, "Directory for log files");

    reg.add("ext_log", "on|off", [](ScopeAppState& s, const auto& args) {
        s.config.logging.ext_trigger = arg_bool(args, 0);
        return std::string("external log trigger ") +
               (s.config.logging.ext_trigger ? "armed" : "off");
    }, "Start/stop the log from the device via status bit 12");

    // --- device state machine --------------------------------------------
    reg.add("enable_system", "", [](ScopeAppState& s, const auto&) {
        s.send_button("Enable_System");
        return std::string("Enable_System sent");
    }, "State machine: enable system");

    reg.add("enable_control", "", [](ScopeAppState& s, const auto&) {
        s.send_button("Enable_Control");
        return std::string("Enable_Control sent");
    }, "State machine: enable control");

    reg.add("stop_system", "", [](ScopeAppState& s, const auto&) {
        s.send_button("Stop");
        return std::string("Stop sent");
    }, "State machine: stop (wire command 3)");

    reg.add("error_reset", "", [](ScopeAppState& s, const auto&) {
        s.send_button("Error_Reset");
        return std::string("Error_Reset sent");
    }, "Reset a latched device error");

    reg.add("my_button", "n", [](ScopeAppState& s, const auto& args) {
        int n = arg_int(args, 0);
        if (n < 1 || n > 8) throw CommandError("MyButton index must be 1..8");
        s.send_button("My_Button_" + std::to_string(n));
        return "My_Button_" + std::to_string(n) + " sent";
    }, "Press MyButton n (1..8)");

    reg.add("send_field", "n, value", [](ScopeAppState& s, const auto& args) {
        int n = arg_int(args, 0);
        if (n < 1 || n > 20) throw CommandError("send field index must be 1..20");
        double v = arg_float(args, 1);
        s.send_field(n, float(v));
        return "send field " + std::to_string(n) + " = " + fmt(v);
    }, "Transmit a send-field value to the device");

    // --- plot windows -----------------------------------------------------
    reg.add("plot_add", "", [](ScopeAppState& s, const auto&) {
        s.plot_add();
        return "added " + s.config.plots.back().title;
    }, "Open another independent plot window");

    reg.add("plot_grid", "window, rows, cols", [](ScopeAppState& s, const auto& args) {
        PlotWindowConfig& p = s.plot(arg_int(args, 0));
        p.rows = std::clamp(arg_int(args, 1), 1, 4);
        p.cols = std::clamp(arg_int(args, 2), 1, 4);
        p.ensure_cells();
        return p.title + " grid " + std::to_string(p.rows) + "x" +
               std::to_string(p.cols);
    }, "Subplot grid of a plot window (1x1 .. 4x4)");

    reg.add("plot_assign", "window, cell, ch", [](ScopeAppState& s, const auto& args) {
        PlotWindowConfig& p = s.plot(arg_int(args, 0));
        int cell = arg_int(args, 1);
        if (cell < 1 || cell > int(p.cells.size()))
            throw CommandError("cell must be 1.." + std::to_string(p.cells.size()));
        int ch = channel_arg(s, args, 2);
        auto& slots = p.cells[size_t(cell - 1)].slots;
        if (std::find(slots.begin(), slots.end(), ch - 1) == slots.end())
            slots.push_back(ch - 1);
        return "CH" + std::to_string(ch) + " -> " + p.title + " cell " +
               std::to_string(cell);
    }, "Add a channel to a subplot cell (also via drag && drop)");

    reg.add("plot_remove", "window, cell, ch", [](ScopeAppState& s, const auto& args) {
        PlotWindowConfig& p = s.plot(arg_int(args, 0));
        int cell = arg_int(args, 1);
        if (cell < 1 || cell > int(p.cells.size()))
            throw CommandError("cell must be 1.." + std::to_string(p.cells.size()));
        int ch = channel_arg(s, args, 2);
        std::erase(p.cells[size_t(cell - 1)].slots, ch - 1);
        return "CH" + std::to_string(ch) + " removed from " + p.title + " cell " +
               std::to_string(cell);
    }, "Remove a channel from a subplot cell");

    reg.add("plot_open", "window, on|off", [](ScopeAppState& s, const auto& args) {
        PlotWindowConfig& p = s.plot(arg_int(args, 0));
        p.open = arg_bool(args, 1);
        return p.title + (p.open ? " opened" : " closed");
    }, "Show/hide a plot window");

    // --- misc -------------------------------------------------------------
    reg.add("help", "", [](ScopeAppState& s, const auto&) {
        for (const auto& line : s.commands.help_lines()) s.console.info(line);
        return std::string();
    }, "List all commands");

    reg.add("clear", "", [](ScopeAppState& s, const auto&) {
        s.console.clear();
        return std::string();
    }, "Clear the console");
}

}  // namespace uz
