#include "../IP_Cores/uz_resolverIP/uz_resolverIP.h"
#include "../IP_Cores/uz_resolver_pl_interface/uz_resolver_pl_interface.h"
#include "../IP_Cores/uz_resolver_pos_mt/uz_resolver_pos_mt.h"

uz_resolverIP_t* initialize_resolver(void);

uz_resolver_pl_interface_t* initialize_resolver_pl_interface(void);

uz_resolver_pos_mt_t* initialize_resolver_pos_mt(void);

/**
 * @brief Multiturn position reading in all supported units plus decomposed turns/singleturn.
 *
 * Assumption: one 16-bit singleturn equals one mechanical revolution
 * (counts per revolution = position_intmax + 1 = 65536 => 2*pi rad = 360 deg).
 */
struct resolver_pos_mt_reading_t {
    int64_t  multiturn_position_counts; /**< raw (int64, = turns*65536 + singleturn) */
    double   multiturn_position_rad;    /**< continuous shaft angle in rad */
    double   multiturn_position_deg;    /**< continuous shaft angle in deg */
    int32_t  turns;                     /**< revolution counter */
    uint16_t singleturn_counts;         /**< singleturn raw position 0..65535 */
    bool     valid;                     /**< pos_mt_valid */
};

/**
 * @brief Reads the multiturn position and returns it in counts, rad and deg.
 *
 * @param self Pointer to the uz_resolver_pos_mt instance
 * @return Reading struct with all unit representations
 */
struct resolver_pos_mt_reading_t resolver_pos_mt_read_position(uz_resolver_pos_mt_t *self);

/**
 * @brief Writes the preset multiturn position given in counts.
 *
 * @param self Pointer to the uz_resolver_pos_mt instance
 * @param counts Preset position in counts (turns*65536 + singleturn)
 */
void resolver_pos_mt_write_preset_counts(uz_resolver_pos_mt_t *self, int64_t counts);

/**
 * @brief Writes the preset multiturn position given in radians.
 *
 * @param self Pointer to the uz_resolver_pos_mt instance
 * @param rad Preset shaft angle in rad
 */
void resolver_pos_mt_write_preset_rad(uz_resolver_pos_mt_t *self, double rad);

/**
 * @brief Writes the preset multiturn position given in degrees.
 *
 * @param self Pointer to the uz_resolver_pos_mt instance
 * @param deg Preset shaft angle in deg
 */
void resolver_pos_mt_write_preset_deg(uz_resolver_pos_mt_t *self, double deg);
