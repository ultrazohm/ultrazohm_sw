// Trigger engine: edge detection and windowed capture on the live stream.
//
// Runs on the reader thread (fed one block of the trigger channel at a time);
// the UI polls capture().  All positions are absolute int64 sample indices —
// the ring wraps, indices don't.
//
// Edge detection is the JavaScope's three-point test (rising:
// y[k] >= level && y[k-1] <= level && y[k-2] < level), with the last two
// samples carried across block boundaries so no edge is lost between packets.
//
// Auto mode only ever captures on real edges; the display falls back to
// rolling when the newest capture is older than auto_timeout samples.
#pragma once

#include <cstdint>
#include <memory>
#include <mutex>
#include <string>

#include "core/ring.hpp"

namespace uz {

enum class TrigState { Idle, WaitPretrigger, Armed, Triggered, Stopped };
enum class TrigEdge { Rising, Falling };
enum class TrigMode { Auto, Normal, Single };

const char* to_string(TrigState s);

struct Capture {
    Snapshot window;       // all channels, W columns
    int64_t trigger_index; // absolute index of the trigger sample
    int sequence;          // increments per capture (UI change detection)
};

class AcquisitionEngine {
public:
    AcquisitionEngine(ChannelRing& ring, int channel, TrigEdge edge, float level,
                      double pretrigger, int64_t window, TrigMode mode,
                      int64_t auto_timeout = 0);

    void arm();
    void disarm();
    // Feed the trigger channel's samples of one parsed block (reader thread).
    void on_block(const float* values, int64_t count, int64_t start_index);

    std::shared_ptr<const Capture> capture() const {
        std::lock_guard lock(mutex_);
        return capture_;
    }
    TrigState state() const {
        std::lock_guard lock(mutex_);
        return state_;
    }
    // Auto mode only: the newest capture is older than auto_timeout samples.
    bool capture_is_stale() const;

    const int channel;
    const TrigEdge edge;
    const float level;
    const int64_t window;
    const int64_t pre;
    const TrigMode mode;
    const int64_t auto_timeout;

private:
    int64_t detect(const float* values, int64_t count, int64_t start_index);
    void try_capture();

    ChannelRing& ring_;
    TrigState state_ = TrigState::Idle;
    std::shared_ptr<const Capture> capture_;
    int64_t trigger_index_ = -1;
    float carry_[2] = {0, 0};
    int carry_size_ = 0;
    int64_t armed_at_ = 0;
    int sequence_ = 0;
    mutable std::mutex mutex_;
};

}  // namespace uz
