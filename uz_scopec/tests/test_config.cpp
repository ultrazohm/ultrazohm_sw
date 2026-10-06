#include <doctest/doctest.h>

#include "core/config.hpp"

using namespace uz;

TEST_CASE("defaults") {
    ScopeConfig cfg;
    CHECK(cfg.ip == "192.168.1.233");
    CHECK(cfg.port == 1000);
    CHECK(cfg.channels == 20);
    CHECK(cfg.channel_settings.size() == 20);
    CHECK(cfg.geometry().frame_bytes() == 1324);
    REQUIRE(cfg.plots.size() == 1);
    CHECK(cfg.plots[0].rows == 1);
    CHECK(cfg.plots[0].cells.size() == 1);
}

TEST_CASE("json roundtrip incl. plots") {
    ScopeConfig cfg;
    cfg.ip = "10.0.0.9";
    cfg.channel_settings[3].observable = 7;
    cfg.channel_settings[3].visible = true;
    cfg.channel_settings[3].scale = 2.5f;
    cfg.trigger.mode = "single";
    cfg.trigger.level = 0.75f;
    cfg.logging.format = "bin";
    cfg.plots[0].rows = 2;
    cfg.plots[0].cols = 2;
    cfg.plots[0].ensure_cells();
    cfg.plots[0].cells[1].slots = {3, 5};
    ScopeConfig back = ScopeConfig::from_json(cfg.to_json());
    CHECK(back.ip == "10.0.0.9");
    CHECK(back.channel_settings[3].observable == 7);
    CHECK(back.channel_settings[3].visible);
    CHECK(back.channel_settings[3].scale == doctest::Approx(2.5f));
    CHECK(back.trigger.mode == "single");
    CHECK(back.trigger.level == doctest::Approx(0.75f));
    CHECK(back.logging.format == "bin");
    REQUIRE(back.plots.size() == 1);
    CHECK(back.plots[0].rows == 2);
    REQUIRE(back.plots[0].cells.size() == 4);
    CHECK(back.plots[0].cells[1].slots == std::vector<int>{3, 5});
}

TEST_CASE("unknown keys and wrong types are ignored") {
    ScopeConfig cfg = ScopeConfig::from_json(
        R"({"ip": "1.2.3.4", "future_flag": true, "port": "not a number"})");
    CHECK(cfg.ip == "1.2.3.4");
    CHECK(cfg.port == 1000);  // bad type -> default kept
}

TEST_CASE("plot slots outside the channel count are clipped") {
    ScopeConfig cfg = ScopeConfig::from_json(
        R"({"channels": 4, "plots": [{"rows": 1, "cols": 1, "cells": [[0, 3, 17]]}]})");
    CHECK(cfg.plots[0].cells[0].slots == std::vector<int>{0, 3});
}
