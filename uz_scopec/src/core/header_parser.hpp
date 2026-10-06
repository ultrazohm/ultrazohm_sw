// Parser for javascope.h — the client's configuration source (GUI-free).
//
// Port of uz_scope/javascope_header.py (itself a port of the Java
// JavascopeHeaderParser): the header is scanned line by line for
// marker-delimited sections.  A section starts at its *_ZEROVALUE line (which
// itself becomes entry 0, so vector index == enum index == wire id) and ends
// before its *_ENDMARKER line.
#pragma once

#include <filesystem>
#include <map>
#include <optional>
#include <string>
#include <vector>

namespace uz {

struct HeaderConfig {
    std::string source;
    std::vector<std::string> observables;
    std::vector<std::string> slowdata;
    std::vector<std::string> buttons;
    std::vector<std::string> send_field_names;
    std::vector<std::string> send_field_units;
    std::vector<std::string> receive_field_names;
    std::vector<std::string> receive_field_units;
    std::vector<std::string> mybutton_labels;
    std::vector<std::string> slowdata_display;
    std::vector<std::string> warnings;

    std::optional<int> observable_index(const std::string& name) const;
    std::optional<int> button_id(const std::string& name) const;
    std::optional<int> slowdata_index(const std::string& name) const;
};

HeaderConfig parse_header_text(const std::string& text,
                               const std::string& source = "<string>");
HeaderConfig parse_header(const std::filesystem::path& path);

// Walk up from start_dir looking for vitis/software/Baremetal/src/include/javascope.h.
std::optional<std::filesystem::path> find_header(
    const std::filesystem::path& start_dir = std::filesystem::current_path());

inline constexpr const char* DEFAULT_HEADER_RELPATH =
    "vitis/software/Baremetal/src/include/javascope.h";

}  // namespace uz
