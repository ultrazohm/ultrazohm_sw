#include "core/commands.hpp"

#include <algorithm>
#include <cctype>

#include "core/state.hpp"

namespace uz {
namespace {

std::string strip(const std::string& s) {
    auto a = s.find_first_not_of(" \t\r\n");
    if (a == std::string::npos) return "";
    auto b = s.find_last_not_of(" \t\r\n");
    return s.substr(a, b - a + 1);
}

std::string lower(std::string s) {
    std::transform(s.begin(), s.end(), s.begin(),
                   [](unsigned char c) { return char(std::tolower(c)); });
    return s;
}

}  // namespace

int arg_int(const std::vector<std::string>& args, size_t i) {
    try {
        return std::stoi(args.at(i));
    } catch (const std::exception&) {
        throw CommandError("argument " + std::to_string(i + 1) + " must be an integer");
    }
}

double arg_float(const std::vector<std::string>& args, size_t i) {
    try {
        return std::stod(args.at(i));
    } catch (const std::exception&) {
        throw CommandError("argument " + std::to_string(i + 1) + " must be a number");
    }
}

bool arg_bool(const std::vector<std::string>& args, size_t i) {
    if (i >= args.size()) throw CommandError("missing boolean argument");
    std::string v = lower(strip(args[i]));
    if (v == "on" || v == "true" || v == "1" || v == "yes") return true;
    if (v == "off" || v == "false" || v == "0" || v == "no") return false;
    throw CommandError("argument " + std::to_string(i + 1) + " must be on/off");
}

std::string arg_str(const std::vector<std::string>& args, size_t i,
                    const std::string& fallback) {
    if (i >= args.size()) return fallback;
    return strip(args[i]);
}

std::string format_call(const std::string& name, const std::vector<std::string>& args) {
    if (args.empty()) return name;
    std::string out = name + "(";
    for (size_t i = 0; i < args.size(); ++i) {
        if (i) out += ", ";
        out += args[i];
    }
    return out + ")";
}

void parse_call(const std::string& line, std::string& name,
                std::vector<std::string>& args) {
    std::string s = strip(line);
    name.clear();
    args.clear();
    auto paren = s.find('(');
    if (paren == std::string::npos) {
        name = s;
        return;
    }
    name = strip(s.substr(0, paren));
    auto close = s.rfind(')');
    std::string inner = (close != std::string::npos && close > paren)
                            ? s.substr(paren + 1, close - paren - 1)
                            : s.substr(paren + 1);
    size_t start = 0;
    while (start <= inner.size()) {
        auto comma = inner.find(',', start);
        std::string piece = (comma == std::string::npos)
                                ? inner.substr(start)
                                : inner.substr(start, comma - start);
        piece = strip(piece);
        if (!piece.empty() || comma != std::string::npos) args.push_back(piece);
        if (comma == std::string::npos) break;
        start = comma + 1;
    }
    // A lone "name()" with nothing inside is a zero-arg call.
    while (!args.empty() && args.back().empty()) args.pop_back();
}

void CommandRegistry::add(const std::string& name, const std::string& params_doc,
                          Fn fn, const std::string& help) {
    commands_[name] = {params_doc, std::move(fn), help};
}

void CommandRegistry::dispatch(ScopeAppState& state, const std::string& line) {
    std::string name;
    std::vector<std::string> args;
    parse_call(line, name, args);
    if (name.empty()) return;
    run(state, name, args, strip(line));
}

void CommandRegistry::execute(ScopeAppState& state, const std::string& name,
                              const std::vector<std::string>& args) {
    run(state, name, args, format_call(name, args));
}

void CommandRegistry::echo(ScopeAppState& state, const std::string& name,
                           const std::vector<std::string>& args) {
    state.console.command(format_call(name, args));
}

void CommandRegistry::run(ScopeAppState& state, const std::string& name,
                          const std::vector<std::string>& args,
                          const std::string& echo_line) {
    state.console.command(echo_line);
    auto it = commands_.find(name);
    if (it == commands_.end()) {
        state.console.error("unknown command: " + name + " (try `help`)");
        return;
    }
    try {
        std::string result = it->second.fn(state, args);
        if (!result.empty()) state.console.info(result);
    } catch (const CommandError& exc) {
        state.console.error(name + ": " + exc.what());
    } catch (const std::exception& exc) {
        state.console.error(name + " failed: " + std::string(exc.what()));
    }
}

std::vector<std::string> CommandRegistry::help_lines() const {
    std::vector<std::string> out;
    for (const auto& [name, def] : commands_) {
        std::string line = name;
        if (!def.params_doc.empty()) line += "(" + def.params_doc + ")";
        line += " — " + def.help;
        out.push_back(std::move(line));
    }
    return out;
}

}  // namespace uz
