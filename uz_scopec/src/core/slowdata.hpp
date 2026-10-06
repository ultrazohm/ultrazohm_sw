// SlowData store: latest value per JS_SlowData entry, typed via the header.
//
// One slowdata value arrives per sample, round-robin over the enum; the raw
// u32 is reinterpreted as float32 iff the enum name contains "FLOAT_".
// Updated on the reader thread, read by the UI (mutex-protected, tiny).
#pragma once

#include <cstdint>
#include <map>
#include <mutex>
#include <string>
#include <vector>

namespace uz {

class SlowDataStore {
public:
    explicit SlowDataStore(std::vector<std::string> names = {});

    void rename(std::vector<std::string> names);
    std::string name(int slow_id) const;

    // Feed one parsed block's ids and raw payload words (reader thread).
    void on_block(const int32_t* ids, const uint32_t* raw, int64_t count);

    struct Item {
        int id;
        std::string name;
        double value;
        bool is_float;
    };
    std::vector<Item> items() const;
    bool get_by_name(const std::string& name, double& out) const;
    int64_t updates() const {
        std::lock_guard lock(mutex_);
        return updates_;
    }

private:
    std::vector<std::string> names_;
    std::vector<bool> is_float_;  // cached per enum index
    std::map<int, double> values_;
    int64_t updates_ = 0;
    mutable std::mutex mutex_;
};

}  // namespace uz
