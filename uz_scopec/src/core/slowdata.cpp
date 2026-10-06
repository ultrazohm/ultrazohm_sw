#include "core/slowdata.hpp"

#include "core/protocol.hpp"

namespace uz {

SlowDataStore::SlowDataStore(std::vector<std::string> names) {
    rename(std::move(names));
}

void SlowDataStore::rename(std::vector<std::string> names) {
    std::lock_guard lock(mutex_);
    names_ = std::move(names);
    is_float_.clear();
    is_float_.reserve(names_.size());
    for (const auto& n : names_) is_float_.push_back(slow_is_float(n));
    values_.clear();
}

std::string SlowDataStore::name(int slow_id) const {
    std::lock_guard lock(mutex_);
    if (slow_id >= 0 && slow_id < int(names_.size())) return names_[slow_id];
    return "slowdata_" + std::to_string(slow_id);
}

void SlowDataStore::on_block(const int32_t* ids, const uint32_t* raw, int64_t count) {
    std::lock_guard lock(mutex_);
    for (int64_t i = 0; i < count; ++i) {
        int32_t id = ids[i];
        if (id < 0) continue;
        bool flt = id < int(is_float_.size()) ? is_float_[id] : false;
        double value;
        if (flt) {
            float f;
            static_assert(sizeof(f) == sizeof(raw[i]));
            std::memcpy(&f, &raw[i], 4);
            value = double(f);
        } else {
            value = double(raw[i]);
        }
        values_[id] = value;
    }
    ++updates_;
}

std::vector<SlowDataStore::Item> SlowDataStore::items() const {
    std::lock_guard lock(mutex_);
    std::vector<Item> out;
    out.reserve(values_.size());
    for (const auto& [id, value] : values_) {
        std::string n = (id >= 0 && id < int(names_.size()))
                            ? names_[id]
                            : "slowdata_" + std::to_string(id);
        bool flt = id < int(is_float_.size()) ? is_float_[id] : false;
        out.push_back({id, std::move(n), value, flt});
    }
    return out;
}

bool SlowDataStore::get_by_name(const std::string& name, double& out) const {
    std::lock_guard lock(mutex_);
    for (size_t i = 0; i < names_.size(); ++i) {
        if (names_[i] == name) {
            auto it = values_.find(int(i));
            if (it == values_.end()) return false;
            out = it->second;
            return true;
        }
    }
    return false;
}

}  // namespace uz
