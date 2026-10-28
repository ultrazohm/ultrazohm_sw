#include "uz_resolver_pos_mt_hw.h"
#include "uz_resolver_pos_mt_hwAddresses.h"
#include "../../uz/uz_AXI.h"

void uz_resolver_pos_mt_hw_write_reset(uint32_t base_address, bool reset) {
    uz_assert_not_zero(base_address);
    uz_axi_write_bool(base_address + reset_Data_uz_resolver_pos_mt, reset);
}

void uz_resolver_pos_mt_hw_write_load_position(uint32_t base_address, bool load) {
    uz_assert_not_zero(base_address);
    uz_axi_write_bool(base_address + load_position_Data_uz_resolver_pos_mt, load);
}

void uz_resolver_pos_mt_hw_write_pos_mt_preset(uint32_t base_address, int64_t preset) {
    uz_assert_not_zero(base_address);
    // 64-bit port is split across two 32-bit registers, data first, then strobe to latch atomically
    uz_axi_write_uint32(base_address + pos_mt_preset_Data_uz_resolver_pos_mt, (uint32_t)((uint64_t)preset));
    uz_axi_write_uint32(base_address + pos_mt_preset_Data_hi_uz_resolver_pos_mt, (uint32_t)((uint64_t)preset >> 32));
    uz_axi_write_bool(base_address + pos_mt_preset_Strobe_uz_resolver_pos_mt, true);
    uz_axi_write_bool(base_address + pos_mt_preset_Strobe_uz_resolver_pos_mt, false);
}

int32_t uz_resolver_pos_mt_hw_read_turns_cnt(uint32_t base_address) {
    uz_assert_not_zero(base_address);
    return (uz_axi_read_int32(base_address + turns_cnt_Data_uz_resolver_pos_mt));
}

int64_t uz_resolver_pos_mt_hw_read_multiturn_position(uint32_t base_address) {
    uz_assert_not_zero(base_address);
    // Pulse the strobe first to latch a coherent 64-bit snapshot, then read both 32-bit words
    uz_axi_write_bool(base_address + multiturn_position_Strobe_uz_resolver_pos_mt, true);
    uz_axi_write_bool(base_address + multiturn_position_Strobe_uz_resolver_pos_mt, false);
    uint32_t lo = uz_axi_read_uint32(base_address + multiturn_position_Data_uz_resolver_pos_mt);
    uint32_t hi = uz_axi_read_uint32(base_address + multiturn_position_Data_hi_uz_resolver_pos_mt);
    return ((int64_t)(((uint64_t)hi << 32) | (uint64_t)lo));
}

bool uz_resolver_pos_mt_hw_read_pos_mt_valid(uint32_t base_address) {
    uz_assert_not_zero(base_address);
    return (uz_axi_read_bool(base_address + pos_mt_valid_Data_uz_resolver_pos_mt));
}
