#include <cstdio>
#include <cstring>
#include <string>

#include "app/app.hpp"
#include "core/state.hpp"

// Shared by main() and the Windows WinMain shim (calling main() directly is
// not portable C++).
int uz_scopec_main(int argc, char** argv) {
    bool connect_on_start = false;
    std::string ip_override, port_override;
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        auto next = [&](const char* flag) -> std::string {
            if (i + 1 >= argc) {
                std::fprintf(stderr, "%s needs a value\n", flag);
                std::exit(2);
            }
            return argv[++i];
        };
        if (arg == "--ip") {
            ip_override = next("--ip");
        } else if (arg == "--port") {
            port_override = next("--port");
        } else if (arg == "--connect") {
            connect_on_start = true;
        } else if (arg == "--help" || arg == "-h") {
            std::printf(
                "uz_scopec — UltraZohm live scope (C++)\n"
                "  --ip <addr>    override the saved device IP\n"
                "  --port <port>  override the saved device port\n"
                "  --connect      connect on startup (not persisted)\n");
            return 0;
        } else {
            std::fprintf(stderr, "unknown argument: %s (see --help)\n", arg.c_str());
            return 2;
        }
    }

    uz::ScopeAppState state;
    // --ip/--port are one-off overrides; only explicit set_ip/connect(ip)
    // change the saved default.
    if (!ip_override.empty()) state.config.ip = ip_override;
    if (!port_override.empty()) state.config.port = std::stoi(port_override);
    return uz::run_app(state, connect_on_start);
}

#ifndef _WIN32
int main(int argc, char** argv) { return uz_scopec_main(argc, argv); }
#endif
// On Windows the entry point is WinMain in win32_main_shim.cpp (GUI
// subsystem: no console window behind the scope).
