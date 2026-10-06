#include <doctest/doctest.h>

#include <numeric>
#include <vector>

#include "core/ring.hpp"

using namespace uz;

namespace {

// Feed m samples of a single-channel ramp starting at value v0.
void feed_ramp(ChannelRing& ring, int channels, int64_t m, float v0) {
    std::vector<float> block(size_t(channels) * size_t(m));
    for (int c = 0; c < channels; ++c)
        for (int64_t i = 0; i < m; ++i)
            block[size_t(c) * m + i] = v0 + float(i) + float(c) * 10000.0f;
    ring.append(block.data(), m);
}

}  // namespace

TEST_CASE("append and snapshot chronological order") {
    ChannelRing ring(2, 100);
    feed_ramp(ring, 2, 30, 0.0f);
    auto snap = ring.snapshot(10, {0, 1});
    CHECK(snap.count == 10);
    CHECK(snap.start == 20);
    CHECK(snap.row(0)[0] == doctest::Approx(20.0f));
    CHECK(snap.row(0)[9] == doctest::Approx(29.0f));
    CHECK(snap.row(1)[0] == doctest::Approx(10020.0f));
}

TEST_CASE("wraparound keeps order and indices") {
    ChannelRing ring(1, 64);
    for (int rep = 0; rep < 5; ++rep) feed_ramp(ring, 1, 30, float(rep * 30));
    CHECK(ring.total_written() == 150);
    auto snap = ring.snapshot(64, {0});
    CHECK(snap.count == 64);
    CHECK(snap.start == 150 - 64);
    // Values are the global sample index (feed blocks were consecutive ramps).
    for (int64_t i = 0; i < snap.count; ++i)
        CHECK(snap.row(0)[i] == doctest::Approx(float(snap.start + i)));
}

TEST_CASE("snapshot_range clips to what the ring still holds") {
    ChannelRing ring(1, 50);
    feed_ramp(ring, 1, 120, 0.0f);  // ramp restarts per append; one big append
    auto snap = ring.snapshot_range(0, 10, {0});
    CHECK(snap.count == 0);  // oldest surviving index is 70
    snap = ring.snapshot_range(100, 30, {0});
    CHECK(snap.start == 100);
    CHECK(snap.count == 20);  // clipped at total_written
    CHECK(snap.row(0)[0] == doctest::Approx(100.0f));
}

TEST_CASE("append larger than capacity keeps the tail") {
    ChannelRing ring(1, 16);
    feed_ramp(ring, 1, 100, 0.0f);
    CHECK(ring.total_written() == 100);
    auto snap = ring.snapshot(16, {0});
    CHECK(snap.row(0)[15] == doctest::Approx(99.0f));
    CHECK(snap.row(0)[0] == doctest::Approx(84.0f));
}

TEST_CASE("append_frames layout matches the wire") {
    FrameGeometry g{3, 4};
    std::vector<uint8_t> buf(size_t(g.frame_bytes()) * 2);
    auto put = [&](size_t word, float v) { std::memcpy(buf.data() + word * 4, &v, 4); };
    for (int frame = 0; frame < 2; ++frame) {
        size_t base = size_t(frame) * g.words();
        for (int c = 0; c < 3; ++c)
            for (int j = 0; j < 4; ++j)
                put(base + 1 + 4 * (1 + c) + j, float(frame * 4 + j + c * 100));
    }
    ChannelRing ring(3, 32);
    ring.append_frames({buf.data(), 2, g});
    CHECK(ring.total_written() == 8);
    auto snap = ring.snapshot(8, {0, 1, 2});
    for (int64_t i = 0; i < 8; ++i) {
        CHECK(snap.row(0)[i] == doctest::Approx(float(i)));
        CHECK(snap.row(2)[i] == doctest::Approx(float(i) + 200.0f));
    }
}

TEST_CASE("ring capacity clamps by bytes") {
    CHECK(ring_capacity(20, 10000.0, 10.0, 512ll << 20) == 100000);
    CHECK(ring_capacity(200, 100000.0, 10.0, 512ll << 20) == (512ll << 20) / (4 * 200));
}
