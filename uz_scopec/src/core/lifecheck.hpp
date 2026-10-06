// Sample-continuity monitor.
//
// Watches a monotonically incrementing counter channel (firmware:
// JSO_lifecheck) and counts discontinuities — the ground truth for "did we
// drop anything" at any ingest rate.
//
// The firmware wraps the counter at 1000 (javascope.c:
// lifecheck = uz_SystemTime_GetInterruptCounter() % 1000), so the check runs
// modulo the same value — a wrap 999 -> 0 is continuity, not a gap.
#pragma once

#include <atomic>
#include <cmath>
#include <cstdint>
#include <optional>

namespace uz {

inline constexpr int64_t LIFECHECK_DEFAULT_MODULO = 1000;

// update() runs on the reader thread; the UI reads the atomic counters.
class Lifecheck {
public:
    explicit Lifecheck(int64_t modulo = LIFECHECK_DEFAULT_MODULO) : modulo_(modulo) {}

    void update(const float* counters, int64_t count) {
        if (count <= 0) return;
        for (int64_t i = 0; i < count; ++i) {
            int64_t v = static_cast<int64_t>(std::llround(double(counters[i])));
            if (last_) {
                int64_t step = ((v - *last_) % modulo_ + modulo_) % modulo_;
                if (step != 1) {
                    gaps.fetch_add(1, std::memory_order_relaxed);
                    missing.fetch_add(((step - 1) % modulo_ + modulo_) % modulo_,
                                      std::memory_order_relaxed);
                }
            }
            last_ = v;
        }
        checked.fetch_add(count, std::memory_order_relaxed);
    }

    void reset() {
        gaps.store(0);
        missing.store(0);
        checked.store(0);
        last_.reset();
    }

    std::atomic<int64_t> gaps{0};     // number of non-+1 steps observed
    std::atomic<int64_t> missing{0};  // samples skipped over (modulo the wrap)
    std::atomic<int64_t> checked{0};

private:
    int64_t modulo_;
    std::optional<int64_t> last_;  // reader thread only
};

}  // namespace uz
