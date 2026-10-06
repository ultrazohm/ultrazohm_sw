// Preallocated channel-major ring buffer for the live sample stream.
//
// Layout is (channels, capacity) float32 — one contiguous row per channel, so
// both the hot append and per-channel display snapshots are cache-friendly.
// Time is never stored: the absolute int64 sample counter total_written()
// converts to seconds only at the display/logging edges.
#pragma once

#include <cstdint>
#include <mutex>
#include <vector>

#include "core/protocol.hpp"

namespace uz {

struct Snapshot {
    std::vector<float> data;  // rows * count, row-major
    int rows = 0;
    int64_t count = 0;
    int64_t start = 0;  // absolute index of column 0

    const float* row(int r) const { return data.data() + size_t(r) * count; }
};

class ChannelRing {
public:
    ChannelRing(int channels, int64_t capacity);

    int channels() const { return channels_; }
    int64_t capacity() const { return capacity_; }
    int64_t total_written() const {
        std::lock_guard lock(mutex_);
        return total_written_;
    }
    int64_t filled() const {
        std::lock_guard lock(mutex_);
        return std::min(total_written_, capacity_);
    }

    // Append a wire block of k frames (channel-major inside each frame).
    void append_frames(const FrameView& view);
    // Append a channel-major block (rows = channels, m columns, row stride m).
    void append(const float* block, int64_t m);

    // Newest `count` samples (fewer if not filled) of the given channel rows.
    Snapshot snapshot(int64_t count, const std::vector<int>& channel_rows) const;
    // `count` samples from absolute index `start`, clipped to what is held.
    Snapshot snapshot_range(int64_t start, int64_t count,
                            const std::vector<int>& channel_rows) const;
    Snapshot snapshot_range_all(int64_t start, int64_t count) const;

private:
    Snapshot copy_out(int64_t start, int64_t count,
                      const std::vector<int>& rows) const;  // mutex_ held

    int channels_;
    int64_t capacity_;
    std::vector<float> data_;
    int64_t total_written_ = 0;
    mutable std::mutex mutex_;
};

int64_t ring_capacity(int channels, double sample_rate, double ring_seconds,
                      int64_t max_ring_bytes);

}  // namespace uz
