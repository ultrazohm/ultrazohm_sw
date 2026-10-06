#include "core/protocol.hpp"

namespace uz {

Command encode_command(uint32_t cmd_id, float value) {
    Command out{};
    std::memcpy(out.data(), &cmd_id, 4);
    std::memcpy(out.data() + 4, &value, 4);
    return out;
}

Command encode_channel_select(int slot, int observable_index) {
    return encode_command(CHANNEL_SELECT_BASE + static_cast<uint32_t>(slot),
                          static_cast<float>(observable_index));
}

void decode_command(const uint8_t* data, uint32_t& cmd_id, float& value) {
    std::memcpy(&cmd_id, data, 4);
    std::memcpy(&value, data + 4, 4);
}

bool slow_is_float(const std::string& name) {
    return name.find("FLOAT_") != std::string::npos;
}

double decode_slow_value(const std::string& name, uint32_t raw) {
    if (slow_is_float(name)) {
        float v;
        std::memcpy(&v, &raw, 4);
        return static_cast<double>(v);
    }
    return static_cast<double>(raw);
}

}  // namespace uz
