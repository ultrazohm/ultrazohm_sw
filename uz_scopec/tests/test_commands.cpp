#include <doctest/doctest.h>

#include <cstring>
#include <filesystem>
#include <fstream>
#include <vector>

#include "core/state.hpp"

using namespace uz;
namespace fs = std::filesystem;

namespace {

fs::path temp_settings(const char* name) {
    fs::path dir = fs::temp_directory_path() / "uz_scopec_tests" / name;
    fs::remove_all(dir);
    fs::create_directories(dir);
    fs::path settings = dir / "settings.json";
    // Pin the header path so the test is independent of the working directory.
    std::ofstream out(settings);
    std::string header = (fs::path(UZ_REPO_ROOT) / DEFAULT_HEADER_RELPATH).string();
    for (auto& c : header)
        if (c == '\\') c = '/';
    out << "{\"header_path\": \"" << header << "\"}\n";
    out.close();
    return settings;
}

// One synthetic wire block: k frames, channel `ch` filled with `value`.
struct FakeFrames {
    std::vector<uint8_t> buf;
    FrameView view;

    FakeFrames(const FrameGeometry& g, int k, int ch, float value,
               uint32_t status = 0) {
        buf.assign(size_t(g.frame_bytes()) * size_t(k), 0);
        for (int i = 0; i < k; ++i) {
            uint8_t* frame = buf.data() + size_t(i) * g.frame_bytes();
            std::memcpy(frame, &status, 4);
            float* chan = reinterpret_cast<float*>(
                frame + 4 * (1 + g.samples_per_packet * (1 + ch)));
            for (int j = 0; j < g.samples_per_packet; ++j) chan[j] = value;
        }
        view = FrameView{buf.data(), k, g};
    }
};

std::vector<std::string> errors(const ScopeAppState& s) {
    std::vector<std::string> out;
    for (const auto& e : s.console.entries())
        if (e.level == "ERROR") out.push_back(e.message);
    return out;
}

}  // namespace

TEST_CASE("state loads the real header") {
    ScopeAppState s(temp_settings("header").string());
    REQUIRE(s.header);
    CHECK(s.header->observables.size() > 3);
    CHECK(s.button_id("Error_Reset") == 32);
    CHECK(s.observable_name(3) == "JSO_lifecheck");
}

TEST_CASE("ch_select by index and by name") {
    ScopeAppState s(temp_settings("chsel").string());
    s.commands.dispatch(s, "ch_select(1, 4)");
    CHECK(s.config.channel_settings[0].observable == 4);
    s.commands.dispatch(s, "ch_select(2, JSO_lifecheck)");
    CHECK(s.config.channel_settings[1].observable == 3);
    s.commands.dispatch(s, "ch_select(3, lifecheck)");  // JSO_ prefix optional
    CHECK(s.config.channel_settings[2].observable == 3);
    CHECK(errors(s).empty());
    s.commands.dispatch(s, "ch_select(1, JSO_NOPE)");
    CHECK(!errors(s).empty());
}

TEST_CASE("visibility, scale, offset, window, freeze") {
    ScopeAppState s(temp_settings("vis").string());
    s.commands.dispatch(s, "ch_visible(5, on)");
    s.commands.dispatch(s, "ch_scale(5, 2.5)");
    s.commands.dispatch(s, "ch_offset(5, -1.5)");
    const auto& ch = s.config.channel_settings[4];
    CHECK(ch.visible);
    CHECK(ch.scale == doctest::Approx(2.5f));
    CHECK(ch.offset == doctest::Approx(-1.5f));
    s.commands.dispatch(s, "enable_all(off)");
    CHECK_FALSE(s.config.channel_settings[4].visible);
    s.commands.dispatch(s, "stop_scope");
    CHECK(s.frozen);
    s.commands.dispatch(s, "run");
    CHECK_FALSE(s.frozen);
    s.commands.dispatch(s, "set_window(2.5)");
    CHECK(s.config.window_seconds == doctest::Approx(2.5));
    CHECK(errors(s).empty());
}

TEST_CASE("geometry rebuild while disconnected") {
    ScopeAppState s(temp_settings("geom").string());
    s.commands.dispatch(s, "set_geometry(200, 15)");
    CHECK(s.config.channels == 200);
    CHECK(s.config.channel_settings.size() == 200);
    CHECK(s.ring->channels() == 200);
    s.commands.dispatch(s, "set_timestep(10)");  // 100 kHz
    CHECK(s.sample_rate() == doctest::Approx(1e5));
    CHECK(errors(s).empty());
}

TEST_CASE("trigger capture through on_frames") {
    ScopeAppState s(temp_settings("trig").string());
    s.config.channel_settings[0].visible = true;
    s.commands.dispatch(s, "trig_mode(single)");
    s.commands.dispatch(s, "trig_level(0.5)");
    s.commands.dispatch(s, "trig_pretrigger(0)");
    s.commands.dispatch(s, "set_window(0.001)");  // 10 samples at 10 kHz
    s.commands.dispatch(s, "trig_arm(on)");
    REQUIRE(s.engine());
    FrameGeometry g = s.config.geometry();
    for (int rep = 0; rep < 2; ++rep) {
        FakeFrames zeros(g, 1, 0, 0.0f);
        s.on_frames(zeros.view);
    }
    for (int rep = 0; rep < 4; ++rep) {
        FakeFrames ones(g, 1, 0, 1.0f);
        s.on_frames(ones.view);
    }
    auto cap = s.engine()->capture();
    REQUIRE(cap);
    CHECK(cap->trigger_index == 30);
    s.commands.dispatch(s, "trig_arm(off)");
    CHECK_FALSE(s.engine());
    CHECK(errors(s).empty());
}

TEST_CASE("ext log trigger on status bit 12") {
    ScopeAppState s(temp_settings("extlog").string());
    fs::path dir = fs::temp_directory_path() / "uz_scopec_tests" / "extlog_out";
    fs::remove_all(dir);
    s.config.logging.directory = dir.string();
    s.commands.dispatch(s, "ext_log(on)");
    FrameGeometry g = s.config.geometry();
    FakeFrames off(g, 1, 0, 0.0f, 0);
    FakeFrames on(g, 1, 0, 0.0f, 1u << 12);
    s.on_frames(off.view);
    CHECK_FALSE(s.logging());
    s.on_frames(on.view);  // rising edge -> start
    CHECK(s.logging());
    s.on_frames(on.view);  // level, no change
    CHECK(s.logging());
    s.on_frames(off.view);  // falling edge -> stop
    CHECK_FALSE(s.logging());
    s.poll_events();
    int files = 0;
    for (auto& e : fs::directory_iterator(dir)) {
        (void)e;
        ++files;
    }
    CHECK(files == 1);
}

TEST_CASE("logging through commands writes a csv") {
    ScopeAppState s(temp_settings("log").string());
    fs::path dir = fs::temp_directory_path() / "uz_scopec_tests" / "log_out";
    fs::remove_all(dir);
    s.config.logging.directory = dir.string();
    s.commands.dispatch(s, "log_format(csv)");
    s.commands.dispatch(s, "log_start");
    CHECK(s.logging());
    FrameGeometry g = s.config.geometry();
    FakeFrames data(g, 2, 0, 3.5f, 5);
    s.on_frames(data.view);
    CHECK(s.last_status.load() == 5);
    s.commands.dispatch(s, "log_stop");
    CHECK_FALSE(s.logging());
    int csv_files = 0;
    for (auto& e : fs::directory_iterator(dir))
        if (e.path().extension() == ".csv") ++csv_files;
    CHECK(csv_files == 1);
    CHECK(errors(s).empty());
}

TEST_CASE("plot window commands") {
    ScopeAppState s(temp_settings("plots").string());
    CHECK(s.config.plots.size() == 1);
    s.commands.dispatch(s, "plot_add");
    REQUIRE(s.config.plots.size() == 2);
    CHECK(s.config.plots[1].title == "Scope 2");
    s.commands.dispatch(s, "plot_grid(2, 2, 2)");
    CHECK(s.config.plots[1].rows == 2);
    REQUIRE(s.config.plots[1].cells.size() == 4);
    s.commands.dispatch(s, "plot_assign(2, 3, 7)");
    CHECK(s.config.plots[1].cells[2].slots == std::vector<int>{6});
    s.commands.dispatch(s, "plot_assign(2, 3, 7)");  // idempotent
    CHECK(s.config.plots[1].cells[2].slots.size() == 1);
    s.commands.dispatch(s, "plot_remove(2, 3, 7)");
    CHECK(s.config.plots[1].cells[2].slots.empty());
    s.commands.dispatch(s, "plot_grid(2, 9, 1)");  // clamped to 4
    CHECK(s.config.plots[1].rows == 4);
    CHECK(errors(s).empty());
}

TEST_CASE("unknown command and bad args surface as console errors") {
    ScopeAppState s(temp_settings("errs").string());
    s.commands.dispatch(s, "frobnicate(1)");
    s.commands.dispatch(s, "ch_visible(99, on)");
    s.commands.dispatch(s, "my_button(9)");
    CHECK(errors(s).size() == 3);
}

TEST_CASE("settings persist through shutdown") {
    fs::path settings = temp_settings("persist");
    {
        ScopeAppState s(settings.string());
        s.config.ip = "10.1.2.3";
        s.shutdown();
    }
    ScopeAppState reloaded(settings.string());
    CHECK(reloaded.config.ip == "10.1.2.3");
}

TEST_CASE("lifecheck slot follows channel select and wraps cleanly") {
    ScopeAppState s(temp_settings("lc").string());
    s.commands.dispatch(s, "ch_select(7, JSO_lifecheck)");
    FrameGeometry g = s.config.geometry();
    // Stream a firmware-style % 1000 counter on slot 6 across a wrap.
    std::vector<uint8_t> buf(size_t(g.frame_bytes()) * 2, 0);
    for (int i = 0; i < 2; ++i) {
        uint8_t* frame = buf.data() + size_t(i) * g.frame_bytes();
        float* chan = reinterpret_cast<float*>(
            frame + 4 * (1 + g.samples_per_packet * (1 + 6)));
        for (int j = 0; j < g.samples_per_packet; ++j)
            chan[j] = float((985 + i * g.samples_per_packet + j) % 1000);
    }
    s.on_frames(FrameView{buf.data(), 2, g});
    CHECK(s.lifecheck.checked == 30);
    CHECK(s.lifecheck.gaps == 0);
}
