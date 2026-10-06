#include <doctest/doctest.h>

#include <vector>

#include "core/acquisition.hpp"

using namespace uz;

namespace {

// Push a 1-channel stream through ring + engine in `block`-sized chunks.
void feed(AcquisitionEngine& eng, ChannelRing& ring, const std::vector<float>& values,
          int block = 7) {
    for (size_t i = 0; i < values.size(); i += size_t(block)) {
        int64_t m = std::min<int64_t>(block, int64_t(values.size() - i));
        int64_t start = ring.total_written();
        ring.append(values.data() + i, m);
        eng.on_block(values.data() + i, m, start);
    }
}

// 0.0 for n0 samples, then 1.0 for n1 samples (one rising edge at n0).
std::vector<float> step_signal(int n0, int n1) {
    std::vector<float> v(size_t(n0), 0.0f);
    v.insert(v.end(), size_t(n1), 1.0f);
    return v;
}

}  // namespace

TEST_CASE("rising edge exact index") {
    ChannelRing ring(1, 1000);
    AcquisitionEngine eng(ring, 0, TrigEdge::Rising, 0.5f, 0.0, 10, TrigMode::Single);
    eng.arm();
    feed(eng, ring, step_signal(50, 50));
    CHECK(eng.state() == TrigState::Stopped);
    auto cap = eng.capture();
    REQUIRE(cap);
    CHECK(cap->trigger_index == 50);
    CHECK(cap->window.start == 50);
    for (int64_t i = 0; i < 10; ++i)
        CHECK(cap->window.row(0)[i] == doctest::Approx(1.0f));
}

TEST_CASE("falling edge") {
    ChannelRing ring(1, 1000);
    AcquisitionEngine eng(ring, 0, TrigEdge::Falling, 0.5f, 0.0, 4, TrigMode::Single);
    eng.arm();
    std::vector<float> inv = step_signal(30, 30);
    for (auto& v : inv) v = 1.0f - v;
    feed(eng, ring, inv);
    REQUIRE(eng.capture());
    CHECK(eng.capture()->trigger_index == 30);
}

TEST_CASE("edge across block boundary and 1-sample blocks") {
    for (int block : {7, 1}) {
        ChannelRing ring(1, 1000);
        AcquisitionEngine eng(ring, 0, TrigEdge::Rising, 0.5f, 0.0, 4, TrigMode::Single);
        eng.arm();
        feed(eng, ring, step_signal(21, 21), block);
        REQUIRE(eng.capture());
        CHECK(eng.capture()->trigger_index == 21);
    }
}

TEST_CASE("pretrigger window content") {
    ChannelRing ring(1, 1000);
    AcquisitionEngine eng(ring, 0, TrigEdge::Rising, 0.5f, 0.5, 11, TrigMode::Single);
    eng.arm();
    feed(eng, ring, step_signal(100, 100));
    auto cap = eng.capture();
    REQUIRE(cap);
    CHECK(cap->trigger_index == 100);
    CHECK(cap->window.start == 95);  // pre = round(0.5 * 10) = 5
    for (int64_t i = 0; i < 5; ++i)
        CHECK(cap->window.row(0)[i] == doctest::Approx(0.0f));
    for (int64_t i = 5; i < 11; ++i)
        CHECK(cap->window.row(0)[i] == doctest::Approx(1.0f));
}

TEST_CASE("trigger before full pretrigger history is skipped") {
    ChannelRing ring(1, 1000);
    AcquisitionEngine eng(ring, 0, TrigEdge::Rising, 0.5f, 1.0, 50, TrigMode::Single);
    eng.arm();
    feed(eng, ring, step_signal(10, 20));  // too early: needs 49 history samples
    CHECK_FALSE(eng.capture());
}

TEST_CASE("normal mode re-arms") {
    ChannelRing ring(1, 10000);
    AcquisitionEngine eng(ring, 0, TrigEdge::Rising, 0.5f, 0.0, 5, TrigMode::Normal);
    eng.arm();
    std::vector<float> pulses;
    for (int rep = 0; rep < 3; ++rep) {
        auto p = step_signal(20, 20);
        pulses.insert(pulses.end(), p.begin(), p.end());
    }
    feed(eng, ring, pulses);
    auto cap = eng.capture();
    REQUIRE(cap);
    CHECK(cap->sequence >= 2);
    CHECK(eng.state() == TrigState::Armed);
}

TEST_CASE("auto mode: no fake captures, staleness when edges stop") {
    ChannelRing ring(1, 10000);
    AcquisitionEngine eng(ring, 0, TrigEdge::Rising, 0.5f, 0.0, 10, TrigMode::Auto, 50);
    eng.arm();
    std::vector<float> flat(200, 0.0f);
    feed(eng, ring, flat);
    CHECK_FALSE(eng.capture());  // hunts real edges only
    CHECK(eng.state() == TrigState::Armed);
    CHECK_FALSE(eng.capture_is_stale());

    feed(eng, ring, step_signal(20, 30));
    REQUIRE(eng.capture());
    CHECK_FALSE(eng.capture_is_stale());
    std::vector<float> quiet(100, 1.0f);
    feed(eng, ring, quiet);
    CHECK(eng.capture_is_stale());
}

TEST_CASE("single mode stops; disarm") {
    ChannelRing ring(1, 1000);
    AcquisitionEngine eng(ring, 0, TrigEdge::Rising, 0.5f, 0.0, 5, TrigMode::Single);
    eng.arm();
    feed(eng, ring, step_signal(20, 100));
    CHECK(eng.state() == TrigState::Stopped);
    int seq = eng.capture()->sequence;
    feed(eng, ring, step_signal(20, 100));  // further edges ignored
    CHECK(eng.capture()->sequence == seq);
    eng.disarm();
    CHECK(eng.state() == TrigState::Idle);
}

TEST_CASE("window larger than ring rejected") {
    ChannelRing ring(1, 100);
    CHECK_THROWS(AcquisitionEngine(ring, 0, TrigEdge::Rising, 0.5f, 0.0, 200,
                                   TrigMode::Single));
}

TEST_CASE("slow ramp crosses level at the right sample") {
    ChannelRing ring(1, 1000);
    AcquisitionEngine eng(ring, 0, TrigEdge::Rising, 5.0f, 0.0, 4, TrigMode::Single);
    eng.arm();
    std::vector<float> ramp;
    for (int i = 0; i < 40; ++i) ramp.push_back(float(i) * 0.5f);
    feed(eng, ring, ramp);
    REQUIRE(eng.capture());
    // y[10] = 5.0 >= lvl, y[9] = 4.5 <= lvl, y[8] = 4.0 < lvl -> index 10
    CHECK(eng.capture()->trigger_index == 10);
}
