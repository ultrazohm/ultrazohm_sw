#include "core/acquisition.hpp"

#include <algorithm>
#include <cmath>
#include <stdexcept>
#include <vector>

namespace uz {

const char* to_string(TrigState s) {
    switch (s) {
        case TrigState::Idle: return "idle";
        case TrigState::WaitPretrigger: return "filling";
        case TrigState::Armed: return "armed";
        case TrigState::Triggered: return "triggered";
        case TrigState::Stopped: return "stopped";
    }
    return "?";
}

AcquisitionEngine::AcquisitionEngine(ChannelRing& ring, int channel_, TrigEdge edge_,
                                     float level_, double pretrigger, int64_t window_,
                                     TrigMode mode_, int64_t auto_timeout_)
    : channel(channel_),
      edge(edge_),
      level(level_),
      window(window_),
      pre(static_cast<int64_t>(std::llround(pretrigger * double(window_ - 1)))),
      mode(mode_),
      auto_timeout(auto_timeout_ > 0 ? auto_timeout_ : 2 * window_),
      ring_(ring) {
    if (pretrigger < 0.0 || pretrigger > 1.0)
        throw std::invalid_argument("pretrigger must be in [0, 1]");
    if (window < 2) throw std::invalid_argument("window must be >= 2 samples");
    if (window > ring.capacity())
        throw std::invalid_argument("window exceeds ring capacity");
}

void AcquisitionEngine::arm() {
    std::lock_guard lock(mutex_);
    state_ = TrigState::WaitPretrigger;
    trigger_index_ = -1;
    carry_size_ = 0;
    armed_at_ = ring_.total_written();
}

void AcquisitionEngine::disarm() {
    std::lock_guard lock(mutex_);
    state_ = TrigState::Idle;
    trigger_index_ = -1;
}

bool AcquisitionEngine::capture_is_stale() const {
    std::shared_ptr<const Capture> cap = capture();
    if (!cap || mode != TrigMode::Auto) return false;
    int64_t age = ring_.total_written() - (cap->window.start + cap->window.count);
    return age > auto_timeout;
}

void AcquisitionEngine::on_block(const float* values, int64_t count,
                                 int64_t start_index) {
    std::lock_guard lock(mutex_);
    if (state_ == TrigState::Idle || state_ == TrigState::Stopped) return;
    if (state_ == TrigState::WaitPretrigger) {
        int64_t written = ring_.total_written();
        if (written - armed_at_ >= pre || written >= pre) {
            state_ = TrigState::Armed;
            armed_at_ = start_index;
        } else {
            return;
        }
    }
    if (state_ == TrigState::Armed) {
        int64_t trig = detect(values, count, start_index);
        if (trig >= 0) {
            trigger_index_ = trig;
            state_ = TrigState::Triggered;
        }
    }
    if (state_ == TrigState::Triggered) try_capture();
}

int64_t AcquisitionEngine::detect(const float* values, int64_t count,
                                  int64_t start_index) {
    // Combined stream = carried 2 samples + this block.
    std::vector<float> y;
    y.reserve(size_t(carry_size_) + size_t(count));
    for (int i = 0; i < carry_size_; ++i) y.push_back(carry_[i]);
    y.insert(y.end(), values, values + count);
    int64_t first_abs = start_index - carry_size_;
    // Carry from the *combined* stream: with a 1-sample block, taking the
    // carry from `values` alone would drop the older boundary sample.
    int m = static_cast<int>(std::min<int64_t>(2, int64_t(y.size())));
    for (int i = 0; i < m; ++i) carry_[i] = y[y.size() - m + i];
    carry_size_ = m;
    if (y.size() < 3) return -1;
    const float lvl = level;
    for (size_t k = 2; k < y.size(); ++k) {
        bool hit = (edge == TrigEdge::Rising)
                       ? (y[k] >= lvl && y[k - 1] <= lvl && y[k - 2] < lvl)
                       : (y[k] <= lvl && y[k - 1] >= lvl && y[k - 2] > lvl);
        if (hit) {
            int64_t trig = first_abs + int64_t(k);
            if (trig - pre >= 0) return trig;  // need full pretrigger history
        }
    }
    return -1;
}

void AcquisitionEngine::try_capture() {
    int64_t trig = trigger_index_;
    int64_t start = trig - pre;
    if (ring_.total_written() < start + window)
        return;  // window tail not produced yet; try again next block
    auto cap = std::make_shared<Capture>();
    cap->window = ring_.snapshot_range_all(start, window);
    cap->trigger_index = trig;
    cap->sequence = ++sequence_;
    capture_ = std::move(cap);
    trigger_index_ = -1;
    if (mode == TrigMode::Single) {
        state_ = TrigState::Stopped;
    } else {
        state_ = TrigState::Armed;
        armed_at_ = start + window;
    }
}

}  // namespace uz
