#include <doctest/doctest.h>

#include <filesystem>

#include "core/header_parser.hpp"

using namespace uz;

namespace {
std::filesystem::path real_header() {
    return std::filesystem::path(UZ_REPO_ROOT) / DEFAULT_HEADER_RELPATH;
}
}  // namespace

TEST_CASE("real javascope.h parses with the canonical ids") {
    REQUIRE(std::filesystem::is_regular_file(real_header()));
    HeaderConfig cfg = parse_header(real_header());
    CHECK(cfg.observables.size() > 3);
    CHECK(cfg.observables[0] == "JSO_ZEROVALUE");
    // Wire ids the whole client depends on:
    REQUIRE(cfg.observable_index("JSO_lifecheck"));
    CHECK(*cfg.observable_index("JSO_lifecheck") == 3);
    REQUIRE(cfg.button_id("Error_Reset"));
    CHECK(*cfg.button_id("Error_Reset") == 32);
    REQUIRE(cfg.button_id("Enable_System"));
    CHECK(*cfg.button_id("Enable_System") == 1);
    REQUIRE(cfg.button_id("My_Button_1"));
    CHECK(*cfg.button_id("My_Button_1") == 24);
    REQUIRE(cfg.button_id("Set_Send_Field_1"));
    CHECK(*cfg.button_id("Set_Send_Field_1") == 4);
    CHECK(cfg.slowdata.size() > 1);
    CHECK(cfg.send_field_names.size() == 21);   // marker + 20 fields
    CHECK(cfg.receive_field_names.size() == 21);
    CHECK(cfg.mybutton_labels.size() == 9);     // marker + 8 buttons
    CHECK(cfg.slowdata_display.size() == 22);   // marker + 20 fields + error code
}

TEST_CASE("marker line is entry zero; comments stripped") {
    const char* text =
        "enum X {\n"
        "  JSO_ZEROVALUE = 0, // comment\n"
        "  JSO_a, /* inline */\n"
        "  JSO_b = 5,\n"
        "  JSO_ENDMARKER\n"
        "};\n";
    HeaderConfig cfg = parse_header_text(text);
    REQUIRE(cfg.observables.size() == 3);
    CHECK(cfg.observables[0] == "JSO_ZEROVALUE");
    CHECK(cfg.observables[1] == "JSO_a");
    CHECK(cfg.observables[2] == "JSO_b");
    CHECK(*cfg.observable_index("JSO_b") == 2);
}

TEST_CASE("unterminated section drops structural junk and warns") {
    const char* text =
        "JSO_ZEROVALUE = 0,\n"
        "JSO_x,\n"
        "};\n";  // no end marker
    HeaderConfig cfg = parse_header_text(text);
    CHECK(cfg.observables == std::vector<std::string>{"JSO_ZEROVALUE", "JSO_x"});
    CHECK(!cfg.warnings.empty());
}

TEST_CASE("compact text mode removes =0 and whitespace") {
    const char* text =
        "SND_FLD_ZEROVALUE = 0,\n"
        "  dut_n_ref_rpm = 0,\n"
        "  i  d  ref,\n"
        "SND_FLD_ENDMARKER\n";
    HeaderConfig cfg = parse_header_text(text);
    REQUIRE(cfg.send_field_names.size() == 3);
    CHECK(cfg.send_field_names[1] == "dut_n_ref_rpm");
    CHECK(cfg.send_field_names[2] == "idref");
}
