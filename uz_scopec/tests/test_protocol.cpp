#include <doctest/doctest.h>

#include <cstring>
#include <vector>

#include "core/protocol.hpp"

using namespace uz;

namespace {

// Build one golden frame exactly like the firmware/test server packs it.
std::vector<uint8_t> golden_frame(const FrameGeometry& g, uint32_t status,
                                  float base) {
    std::vector<uint8_t> buf(size_t(g.frame_bytes()));
    uint8_t* p = buf.data();
    std::memcpy(p, &status, 4);
    p += 4;
    for (int j = 0; j < g.samples_per_packet; ++j) {
        uint32_t raw = 1000u + uint32_t(j);
        std::memcpy(p, &raw, 4);
        p += 4;
    }
    for (int c = 0; c < g.channels; ++c) {
        for (int j = 0; j < g.samples_per_packet; ++j) {
            float v = base + float(c) * 100.0f + float(j);
            std::memcpy(p, &v, 4);
            p += 4;
        }
    }
    for (int j = 0; j < g.samples_per_packet; ++j) {
        float id = float(j % 5);
        std::memcpy(p, &id, 4);
        p += 4;
    }
    return buf;
}

}  // namespace

TEST_CASE("frame geometry sizes") {
    FrameGeometry g;
    CHECK(g.frame_bytes() == 1324);  // C=20, N=15
    FrameGeometry big{200, 15};
    CHECK(big.frame_bytes() == 12124);
}

TEST_CASE("golden frame parses") {
    FrameGeometry g;
    auto f1 = golden_frame(g, 0b1011, 0.0f);
    auto f2 = golden_frame(g, 5, 5000.0f);
    std::vector<uint8_t> buf;
    buf.insert(buf.end(), f1.begin(), f1.end());
    buf.insert(buf.end(), f2.begin(), f2.end());

    FrameView view{buf.data(), 2, g};
    CHECK(view.status(0) == 0b1011);
    CHECK(view.status(1) == 5);
    CHECK(view.slow_raw(0, 3) == 1003);
    CHECK(view.channel(0, 0)[0] == doctest::Approx(0.0f));
    CHECK(view.channel(0, 2)[7] == doctest::Approx(207.0f));
    CHECK(view.channel(1, 19)[14] == doctest::Approx(5000.0f + 1914.0f));
    CHECK(view.slow_id(0, 4) == 4);
    CHECK(view.slow_id(1, 6) == 1);
}

TEST_CASE("garbage slow id decodes to -1") {
    FrameGeometry g{1, 1};
    std::vector<uint8_t> buf(size_t(g.frame_bytes()), 0xFF);  // NaN floats
    FrameView view{buf.data(), 1, g};
    CHECK(view.slow_id(0, 0) == -1);
}

TEST_CASE("command encode/decode roundtrip") {
    Command c = encode_command(32, 1.0f);
    uint32_t id;
    float value;
    decode_command(c.data(), id, value);
    CHECK(id == 32);
    CHECK(value == doctest::Approx(1.0f));

    Command sel = encode_channel_select(7, 42);
    decode_command(sel.data(), id, value);
    CHECK(id == 208);  // 201 + 7
    CHECK(value == doctest::Approx(42.0f));

    Command ack = zero_ack();
    decode_command(ack.data(), id, value);
    CHECK(id == 0);
}

TEST_CASE("status bits") {
    uint32_t status = (1u << 0) | (1u << 3) | (1u << 8) | (1u << 12);
    CHECK(status_bit(status, STATUS_BIT_READY));
    CHECK_FALSE(status_bit(status, STATUS_BIT_RUNNING));
    CHECK(status_bit(status, STATUS_BIT_USER));
    CHECK(mybutton_indicator(status, 5));  // bit 8
    CHECK_FALSE(mybutton_indicator(status, 1));
    CHECK(status_bit(status, STATUS_BIT_EXT_LOG));
}

TEST_CASE("slowdata float reinterpretation") {
    CHECK(slow_is_float("JSSD_FLOAT_Error_Code"));
    CHECK_FALSE(slow_is_float("JSSD_Milliseconds"));
    float v = 3.25f;
    uint32_t raw;
    std::memcpy(&raw, &v, 4);
    CHECK(decode_slow_value("JSSD_FLOAT_x", raw) == doctest::Approx(3.25));
    CHECK(decode_slow_value("JSSD_count", 1234) == doctest::Approx(1234.0));
}
