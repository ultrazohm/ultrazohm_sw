// Wire protocol of the UltraZohm JavaScope TCP stream (GUI-free).
//
// The device streams fixed-size little-endian frames with no framing header.
// With C scope channels and N samples per packet, one frame is:
//
//   uint32  status          state-machine / LED / MyButton / ext-log bits
//   uint32  slow_raw[N]     slowdata payload bits, one round-robin value per sample
//   float32 ch[C][N]        channel-major fast-sample block
//   float32 slow_id[N]      JS_SlowData enum index of each slow_raw entry (as float)
//
// Frame size = 4 * (1 + (C + 2) * N) bytes — 1324 bytes at C=20, N=15.
// The uplink command is 8 bytes: <uint32 id><float32 value>.
#pragma once

#include <array>
#include <cstdint>
#include <cstring>
#include <string>

namespace uz {

inline constexpr int STATUS_BIT_READY = 0;
inline constexpr int STATUS_BIT_RUNNING = 1;
inline constexpr int STATUS_BIT_ERROR = 2;
inline constexpr int STATUS_BIT_USER = 3;
inline constexpr int STATUS_BIT_MYBUTTON_BASE = 4;  // bits 4..11 -> MyButton 1..8
inline constexpr int STATUS_BIT_EXT_LOG = 12;

inline constexpr uint32_t CHANNEL_SELECT_BASE = 201;
inline constexpr uint32_t ZERO_ACK_ID = 0;

struct FrameGeometry {
    int channels = 20;
    int samples_per_packet = 15;

    int words() const { return 1 + (channels + 2) * samples_per_packet; }
    int frame_bytes() const { return 4 * words(); }
    bool operator==(const FrameGeometry&) const = default;
};

// Zero-copy view of k consecutive frames in a receive buffer.  All accessors
// assume the host is little-endian (x86/ARM desktops — same as the Python
// client's "<u4"/"<f4" dtypes).
struct FrameView {
    const uint8_t* base = nullptr;
    int k = 0;
    FrameGeometry geom;

    const uint8_t* frame(int i) const { return base + size_t(i) * geom.frame_bytes(); }
    uint32_t status(int i) const {
        uint32_t v;
        std::memcpy(&v, frame(i), 4);
        return v;
    }
    uint32_t slow_raw(int i, int j) const {
        uint32_t v;
        std::memcpy(&v, frame(i) + 4 * (1 + j), 4);
        return v;
    }
    // Pointer to channel c's N contiguous float32 samples of frame i.
    const float* channel(int i, int c) const {
        return reinterpret_cast<const float*>(
            frame(i) + 4 * (1 + geom.samples_per_packet * (1 + c)));
    }
    int32_t slow_id(int i, int j) const {
        float v;
        std::memcpy(&v,
                    frame(i) + 4 * (1 + geom.samples_per_packet * (1 + geom.channels) + j),
                    4);
        // Garbage/NaN slow ids (possible on geometry mismatch) must not trap;
        // they surface via range checks downstream.
        if (!(v >= -2.0e9f && v <= 2.0e9f)) return -1;
        return static_cast<int32_t>(v);
    }
};

using Command = std::array<uint8_t, 8>;

Command encode_command(uint32_t cmd_id, float value = 0.0f);
Command encode_channel_select(int slot, int observable_index);
void decode_command(const uint8_t* data, uint32_t& cmd_id, float& value);
inline Command zero_ack() { return encode_command(ZERO_ACK_ID, 0.0f); }

inline bool status_bit(uint32_t status, int bit) { return (status >> bit) & 1u; }
inline bool mybutton_indicator(uint32_t status, int button /*1..8*/) {
    return status_bit(status, STATUS_BIT_MYBUTTON_BASE + button - 1);
}

// A slowdata value is float32 iff its JS_SlowData enum name contains "FLOAT_".
bool slow_is_float(const std::string& name);
double decode_slow_value(const std::string& name, uint32_t raw);

}  // namespace uz
