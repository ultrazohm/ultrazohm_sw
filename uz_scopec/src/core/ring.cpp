#include "core/ring.hpp"

#include <algorithm>
#include <cstring>
#include <stdexcept>

namespace uz {

ChannelRing::ChannelRing(int channels, int64_t capacity)
    : channels_(channels), capacity_(capacity) {
    if (channels < 1 || capacity < 1)
        throw std::invalid_argument("channels and capacity must be >= 1");
    data_.assign(size_t(channels) * size_t(capacity), 0.0f);
}

void ChannelRing::append_frames(const FrameView& view) {
    const int n = view.geom.samples_per_packet;
    const int c = view.geom.channels;
    if (c != channels_) throw std::invalid_argument("channel count mismatch");
    std::lock_guard lock(mutex_);
    for (int i = 0; i < view.k; ++i) {
        int64_t pos = total_written_ % capacity_;
        int64_t first = std::min<int64_t>(n, capacity_ - pos);
        for (int ch = 0; ch < c; ++ch) {
            const float* src = view.channel(i, ch);
            float* row = data_.data() + size_t(ch) * capacity_;
            std::memcpy(row + pos, src, size_t(first) * 4);
            if (first < n) std::memcpy(row, src + first, size_t(n - first) * 4);
        }
        total_written_ += n;
    }
}

void ChannelRing::append(const float* block, int64_t m) {
    std::lock_guard lock(mutex_);
    int64_t skipped = 0;
    if (m > capacity_) {  // only the last `capacity` samples can survive anyway
        skipped = m - capacity_;
        m = capacity_;
    }
    int64_t pos = (total_written_ + skipped) % capacity_;
    int64_t first = std::min(m, capacity_ - pos);
    for (int ch = 0; ch < channels_; ++ch) {
        const float* src = block + size_t(ch) * (m + skipped) + skipped;
        float* row = data_.data() + size_t(ch) * capacity_;
        std::memcpy(row + pos, src, size_t(first) * 4);
        if (first < m) std::memcpy(row, src + first, size_t(m - first) * 4);
    }
    total_written_ += m + skipped;
}

Snapshot ChannelRing::snapshot(int64_t count, const std::vector<int>& rows) const {
    std::lock_guard lock(mutex_);
    int64_t avail = std::min(total_written_, capacity_);
    count = std::min(count, avail);
    return copy_out(total_written_ - count, count, rows);
}

Snapshot ChannelRing::snapshot_range(int64_t start, int64_t count,
                                     const std::vector<int>& rows) const {
    std::lock_guard lock(mutex_);
    int64_t filled = std::min(total_written_, capacity_);
    int64_t oldest = total_written_ - filled;
    int64_t end = std::min(start + count, total_written_);
    start = std::max(start, oldest);
    count = std::max<int64_t>(0, end - start);
    return copy_out(start, count, rows);
}

Snapshot ChannelRing::snapshot_range_all(int64_t start, int64_t count) const {
    std::vector<int> rows(channels_);
    for (int i = 0; i < channels_; ++i) rows[i] = i;
    return snapshot_range(start, count, rows);
}

Snapshot ChannelRing::copy_out(int64_t start, int64_t count,
                               const std::vector<int>& rows) const {
    Snapshot out;
    out.rows = static_cast<int>(rows.size());
    out.count = count;
    out.start = start;
    out.data.resize(rows.size() * size_t(count));
    if (count == 0) return out;
    int64_t pos = start % capacity_;
    int64_t first = std::min(count, capacity_ - pos);
    for (size_t i = 0; i < rows.size(); ++i) {
        const float* row = data_.data() + size_t(rows[i]) * capacity_;
        float* dst = out.data.data() + i * size_t(count);
        std::memcpy(dst, row + pos, size_t(first) * 4);
        if (count > first) std::memcpy(dst + first, row, size_t(count - first) * 4);
    }
    return out;
}

int64_t ring_capacity(int channels, double sample_rate, double ring_seconds,
                      int64_t max_ring_bytes) {
    int64_t wanted = std::max<int64_t>(1, int64_t(ring_seconds * sample_rate + 0.5));
    int64_t cap_by_bytes = std::max<int64_t>(1, max_ring_bytes / (4 * int64_t(channels)));
    return std::min(wanted, cap_by_bytes);
}

}  // namespace uz
