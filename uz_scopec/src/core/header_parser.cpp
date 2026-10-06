#include "core/header_parser.hpp"

#include <algorithm>
#include <cctype>
#include <fstream>
#include <sstream>

namespace uz {
namespace {

struct Section {
    std::vector<std::string> HeaderConfig::* attr;
    const char* start;
    const char* end;
    bool identifier;  // identifier mode vs compact-text mode
};

const Section SECTIONS[] = {
    {&HeaderConfig::observables, "JSO_ZEROVALUE", "JSO_ENDMARKER", true},
    {&HeaderConfig::slowdata, "JSSD_ZEROVALUE", "JSSD_ENDMARKER", true},
    {&HeaderConfig::buttons, "GUI_BTN_ZEROVALUE", "GUI_BTN_ENDMARKER", true},
    {&HeaderConfig::send_field_names, "SND_FLD_ZEROVALUE", "SND_FLD_ENDMARKER", false},
    {&HeaderConfig::send_field_units, "SND_LABELS_ZEROVALUE", "SND_LABELS_ENDMARKER", false},
    {&HeaderConfig::receive_field_names, "RCV_FLD_ZEROVALUE", "RCV_FLD_ENDMARKER", false},
    {&HeaderConfig::receive_field_units, "RCV_LABELS_ZEROVALUE", "RCV_LABELS_ENDMARKER", false},
    {&HeaderConfig::mybutton_labels, "MYBUTTONS_LABELS_ZEROVALUE",
     "MYBUTTONS_LABELS_ENDMARKER", false},
    {&HeaderConfig::slowdata_display, "SLOWDAT_DISPLAY_ZEROVALUE",
     "SLOWDAT_DISPLAY_ENDMARKER", true},
};

std::string strip_comments(std::string line) {
    if (auto pos = line.find("//"); pos != std::string::npos) line.resize(pos);
    for (;;) {
        auto start = line.find("/*");
        if (start == std::string::npos) break;
        auto end = line.find("*/", start + 2);
        if (end == std::string::npos) {
            line.resize(start);
            break;
        }
        line = line.substr(0, start) + line.substr(end + 2);
    }
    return line;
}

std::string strip(const std::string& s) {
    auto a = s.find_first_not_of(" \t\r\n");
    if (a == std::string::npos) return "";
    auto b = s.find_last_not_of(" \t\r\n");
    return s.substr(a, b - a + 1);
}

std::string remove_trailing_delimiters(std::string token) {
    token = strip(token);
    while (!token.empty() && (token.back() == ',' || token.back() == ';'))
        token.pop_back();
    return strip(token);
}

std::string remove_whitespace(const std::string& s) {
    std::string out;
    out.reserve(s.size());
    for (char c : s)
        if (!std::isspace(static_cast<unsigned char>(c))) out += c;
    return out;
}

std::string identifier_part(const std::string& token) {
    return token.substr(0, token.find('='));
}

std::string normalize_marker(const std::string& line) {
    return remove_whitespace(remove_trailing_delimiters(strip(strip_comments(line))));
}

bool is_identifier(const std::string& token) {
    if (token.empty()) return false;
    if (!(std::isalpha(static_cast<unsigned char>(token[0])) || token[0] == '_'))
        return false;
    return std::all_of(token.begin(), token.end(), [](char c) {
        return std::isalnum(static_cast<unsigned char>(c)) || c == '_';
    });
}

std::string sanitize(const std::string& line, bool identifier_mode) {
    std::string token = strip(strip_comments(line));
    if (token.empty()) return "";
    token = remove_whitespace(remove_trailing_delimiters(token));
    if (identifier_mode) {
        token = remove_trailing_delimiters(identifier_part(token));
        // Drop structural junk ('}', '};', ...) that an unterminated section
        // would otherwise sweep up.
        if (!is_identifier(token)) return "";
        return token;
    }
    // compact-text mode: a literal "=0" is removed from labels/units.
    if (auto pos = token.find("=0"); pos != std::string::npos)
        token = token.substr(0, pos) + token.substr(pos + 2);
    return remove_trailing_delimiters(token);
}

}  // namespace

std::optional<int> lookup(const std::vector<std::string>& v, const std::string& name) {
    auto it = std::find(v.begin(), v.end(), name);
    if (it == v.end()) return std::nullopt;
    return static_cast<int>(it - v.begin());
}

std::optional<int> HeaderConfig::observable_index(const std::string& name) const {
    return lookup(observables, name);
}
std::optional<int> HeaderConfig::button_id(const std::string& name) const {
    return lookup(buttons, name);
}
std::optional<int> HeaderConfig::slowdata_index(const std::string& name) const {
    return lookup(slowdata, name);
}

HeaderConfig parse_header_text(const std::string& text, const std::string& source) {
    std::vector<std::string> lines;
    {
        std::istringstream in(text);
        std::string line;
        while (std::getline(in, line)) lines.push_back(line);
    }
    HeaderConfig cfg;
    cfg.source = source;
    for (const Section& sec : SECTIONS) {
        std::vector<std::string> entries;
        int starts = 0, ends = 0;
        bool in_section = false;
        for (const std::string& line : lines) {
            std::string candidate = normalize_marker(line);
            if (!candidate.empty() && identifier_part(candidate) == sec.start) {
                ++starts;
                in_section = true;
                std::string entry = sanitize(line, sec.identifier);
                if (!entry.empty()) entries.push_back(entry);
                continue;
            }
            if (!candidate.empty() && identifier_part(candidate) == sec.end) {
                ++ends;
                in_section = false;
                continue;
            }
            if (!in_section) continue;
            std::string entry = sanitize(line, sec.identifier);
            if (!entry.empty()) entries.push_back(entry);
        }
        cfg.*(sec.attr) = entries;
        if (starts != 1 || ends != 1) {
            cfg.warnings.push_back("section " + std::string(sec.start) + ".." +
                                   sec.end + ": expected exactly one start/end marker, found " +
                                   std::to_string(starts) + "/" + std::to_string(ends));
        } else if (entries.empty()) {
            cfg.warnings.push_back("section " + std::string(sec.start) + ".." + sec.end +
                                   ": empty");
        }
    }
    // Entry 0 of the display mapping is the section marker itself.
    for (size_t i = 1; i < cfg.slowdata_display.size(); ++i) {
        const std::string& name = cfg.slowdata_display[i];
        if (name != "JSSD_FLOAT_ZEROVALUE" && !cfg.slowdata_index(name)) {
            cfg.warnings.push_back("SLOWDAT_DISPLAY entry '" + name +
                                   "' is not in the JS_SlowData enum");
        }
    }
    return cfg;
}

HeaderConfig parse_header(const std::filesystem::path& path) {
    std::ifstream in(path, std::ios::binary);
    std::ostringstream buf;
    buf << in.rdbuf();
    return parse_header_text(buf.str(), path.string());
}

std::optional<std::filesystem::path> find_header(const std::filesystem::path& start_dir) {
    std::error_code ec;
    auto dir = std::filesystem::absolute(start_dir, ec);
    if (ec) return std::nullopt;
    for (;;) {
        auto candidate = dir / DEFAULT_HEADER_RELPATH;
        if (std::filesystem::is_regular_file(candidate, ec)) return candidate;
        auto parent = dir.parent_path();
        if (parent == dir) return std::nullopt;
        dir = parent;
    }
}

}  // namespace uz
