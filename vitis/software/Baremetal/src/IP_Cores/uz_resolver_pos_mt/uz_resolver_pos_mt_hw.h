#ifndef UZ_RESOLVER_POS_MT_HW_H
#define UZ_RESOLVER_POS_MT_HW_H
#include <stdint.h>
#include <stdbool.h>

/**
 * @brief Writes the reset Inport of the IP-Core (resets the internal multiturn counter).
 *
 * @param base_address Base address of the IP-Core
 * @param reset true/false
 */
void uz_resolver_pos_mt_hw_write_reset(uint32_t base_address, bool reset);

/**
 * @brief Writes the load_position Inport of the IP-Core (loads the preset position).
 *
 * @param base_address Base address of the IP-Core
 * @param load true/false
 */
void uz_resolver_pos_mt_hw_write_load_position(uint32_t base_address, bool load);

/**
 * @brief Writes the 64-bit pos_mt_preset Inport (two 32-bit words + strobe).
 *
 * @param base_address Base address of the IP-Core
 * @param preset Preset multiturn position (turns*65536 + singleturn)
 */
void uz_resolver_pos_mt_hw_write_pos_mt_preset(uint32_t base_address, int64_t preset);

/**
 * @brief Reads the turns_cnt Outport (revolution counter).
 *
 * @param base_address Base address of the IP-Core
 * @return int32_t
 */
int32_t uz_resolver_pos_mt_hw_read_turns_cnt(uint32_t base_address);

/**
 * @brief Reads the 64-bit multiturn_position Outport (strobe + two 32-bit words).
 *
 * @param base_address Base address of the IP-Core
 * @return int64_t
 */
int64_t uz_resolver_pos_mt_hw_read_multiturn_position(uint32_t base_address);

/**
 * @brief Reads the pos_mt_valid Outport (validity flag).
 *
 * @param base_address Base address of the IP-Core
 * @return bool
 */
bool uz_resolver_pos_mt_hw_read_pos_mt_valid(uint32_t base_address);

#endif // UZ_RESOLVER_POS_MT_HW_H
