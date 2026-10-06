// Command registry + console model (GUI-free).
//
// Every UI action routes through a named command that is echoed to the
// console, so a session reads as a replayable log — the uz_dataviewer /
// uz_scope pattern.  Lines are "name" or "name(arg1, arg2)".
#pragma once

#include <deque>
#include <functional>
#include <map>
#include <stdexcept>
#include <string>
#include <vector>

namespace uz {

struct ScopeAppState;  // defined in core/state.hpp

struct CommandError : std::runtime_error {
    using std::runtime_error::runtime_error;
};

struct ConsoleEntry {
    std::string level;  // "INFO", "WARN", "ERROR", "CMD"
    std::string message;
};

// UI-thread only; worker threads post through ScopeAppState's event queue.
class Console {
public:
    void info(const std::string& m) { push("INFO", m); }
    void warn(const std::string& m) { push("WARN", m); }
    void error(const std::string& m) { push("ERROR", m); }
    void command(const std::string& m) { push("CMD", m); }
    void clear() { entries_.clear(); }
    const std::deque<ConsoleEntry>& entries() const { return entries_; }

private:
    void push(const char* level, const std::string& m) {
        entries_.push_back({level, m});
        while (entries_.size() > 2000) entries_.pop_front();
    }
    std::deque<ConsoleEntry> entries_;
};

// Argument conversion helpers (throw CommandError with a readable message).
int arg_int(const std::vector<std::string>& args, size_t i);
double arg_float(const std::vector<std::string>& args, size_t i);
bool arg_bool(const std::vector<std::string>& args, size_t i);
std::string arg_str(const std::vector<std::string>& args, size_t i,
                    const std::string& fallback = "");

std::string format_call(const std::string& name, const std::vector<std::string>& args);

class CommandRegistry {
public:
    using Fn = std::function<std::string(ScopeAppState&, const std::vector<std::string>&)>;

    void add(const std::string& name, const std::string& params_doc, Fn fn,
             const std::string& help);
    bool has(const std::string& name) const { return commands_.count(name) > 0; }

    // Parse and run one console line; echoes the line and the result.
    void dispatch(ScopeAppState& state, const std::string& line);
    // Run a named command with pre-split args (UI widgets), echoing the call.
    void execute(ScopeAppState& state, const std::string& name,
                 const std::vector<std::string>& args);
    // Echo only (used after live drags that already applied their value).
    void echo(ScopeAppState& state, const std::string& name,
              const std::vector<std::string>& args);

    std::vector<std::string> help_lines() const;

private:
    struct Def {
        std::string params_doc;
        Fn fn;
        std::string help;
    };
    void run(ScopeAppState& state, const std::string& name,
             const std::vector<std::string>& args, const std::string& echo_line);
    std::map<std::string, Def> commands_;
};

// Parse "name(a, b)" / "name a b"-style lines into name + raw string args.
void parse_call(const std::string& line, std::string& name,
                std::vector<std::string>& args);

}  // namespace uz
