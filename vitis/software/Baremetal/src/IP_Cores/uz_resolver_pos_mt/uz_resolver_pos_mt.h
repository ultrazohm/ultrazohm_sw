#ifndef UZ_RESOLVER_POS_MT_H
#define UZ_RESOLVER_POS_MT_H
#include <stdint.h>
#include <stdbool.h>

/**
 * @brief Data type for object uz_resolver_pos_mt
 *
 */
typedef struct uz_resolver_pos_mt_t uz_resolver_pos_mt_t;

/**
 * @brief Configuration struct for uz_resolver_pos_mt
 *
 */
struct uz_resolver_pos_mt_config_t {
    uint32_t base_address; /**< Base address of the IP-Core */
    uint32_t ip_clk_frequency_Hz; /**< Clock frequency of the IP-Core */
};

/**
 * @brief Output struct for uz_resolver_pos_mt
 *
 * The raw multiturn_position equals turns*65536 + singleturn_raw (integer, En0).
 * turns and singleturn_raw are the decomposition of that value.
 */
struct uz_resolver_pos_mt_outputs_t {
    int64_t multiturn_position; /**< Raw multiturn position (turns*65536 + singleturn_raw) */
    int32_t turns_cnt; /**< Revolution counter read from the IP-Core */
    bool pos_mt_valid; /**< true once the multiturn position has a valid reference */
    int32_t turns; /**< turns decomposed from multiturn_position (multiturn_position >> 16) */
    uint16_t singleturn_raw; /**< singleturn raw position 0..65535 (multiturn_position & 0xFFFF) */
};

/**
 * @brief Initializes an instance of the uz_resolver_pos_mt driver
 *
 * @param config Configuration values for the IP-Core
 * @return Pointer to initialized instance
 */
uz_resolver_pos_mt_t* uz_resolver_pos_mt_init(struct uz_resolver_pos_mt_config_t config);

/**
 * @brief Reads and returns the AXI outputs of the IP-Core, including the decomposed turns/singleturn.
 *
 * @param self Pointer to the instance
 * @return Output struct
 */
struct uz_resolver_pos_mt_outputs_t uz_resolver_pos_mt_get_outputs(uz_resolver_pos_mt_t *self);

/**
 * @brief Resets the internal multiturn counter of the IP-Core (turns=0, waits for next valid value).
 *
 * @param self Pointer to the instance
 */
void uz_resolver_pos_mt_reset(uz_resolver_pos_mt_t *self);

/**
 * @brief Loads a preset multiturn position into the IP-Core.
 *
 * Writes the preset value, then pulses the load_position Inport so the counter adopts it.
 *
 * @param self Pointer to the instance
 * @param pos_mt_preset Preset multiturn position (turns*65536 + singleturn)
 */
void uz_resolver_pos_mt_load_preset(uz_resolver_pos_mt_t *self, int64_t pos_mt_preset);

#endif // UZ_RESOLVER_POS_MT_H
