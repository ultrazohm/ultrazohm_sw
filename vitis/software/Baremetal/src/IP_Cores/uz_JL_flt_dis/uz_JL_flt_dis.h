
#ifndef UZ_JL_FLT_DIS_H
#define UZ_JL_FLT_DIS_H

#include <stdint.h>
#include <stdbool.h>

/**
 * @brief Object definition of the fault-disable (flt_dis) IP Core
 *
 */
typedef struct uz_JL_flt_dis_t uz_JL_flt_dis_t;

/**
 * @brief Fault cause reported by the FLT_ps output. The values are bit flags, so multiple
 * causes can be active at once. Single faults match directly via ==, combined faults can be
 * checked with a bitwise AND.
 *
 * NOTE: The concrete bit meanings are placeholders and must be matched to the actual HDL
 * encoding of the uz_JL_flt_ip core. Only the bit positions / data type are fixed here.
 */
enum uz_JL_flt_dis_fault {
    UZ_JL_FLT_DIS_FAULT_NONE = 0,
    UZ_JL_FLT_DIS_FAULT_BIT0 = 1,
    UZ_JL_FLT_DIS_FAULT_BIT1 = 2,
    UZ_JL_FLT_DIS_FAULT_BIT2 = 4,
    UZ_JL_FLT_DIS_FAULT_BIT3 = 8,
};

/**
 * @brief Configuration struct for the flt_dis IP-Core
 *
 */
struct uz_JL_flt_dis_config_t
{
    uint32_t base_address;          /**< Base address of IP-Core instance */
    uint32_t ip_core_frequency_Hz;  /**< Clock frequency of IP-Core */
    bool use_flt_dis;               /**< Initial state of the use_flt_dis input (enable fault-disable logic) */
};

/**
 * @brief Initialize an instance of the driver
 *
 * @param config Configuration struct
 * @return uz_JL_flt_dis_t* Pointer to initialized instance of driver
 */
uz_JL_flt_dis_t *uz_JL_flt_dis_init(struct uz_JL_flt_dis_config_t config);

/**
 * @brief Set the FLT_PS input of the IP-Core.
 *
 * @param self Pointer to driver instance
 * @param flt_ps FLT_PS value
 */
void uz_JL_flt_dis_set_FLT_PS(uz_JL_flt_dis_t *self, bool flt_ps);

/**
 * @brief Enable or disable the fault-disable logic (use_flt_dis input).
 *
 * @param self Pointer to driver instance
 * @param use_flt_dis true to use the fault-disable feature, false otherwise
 */
void uz_JL_flt_dis_set_use_flt_dis(uz_JL_flt_dis_t *self, bool use_flt_dis);

/**
 * @brief Reset (acknowledge) the latched fault state of the IP core.
 *
 * Pulses the FLT_RST input (true then false).
 *
 * @param self Pointer to driver instance
 */
void uz_JL_flt_dis_reset_fault(uz_JL_flt_dis_t *self);

/**
 * @brief Read the current fault cause from the FLT_ps output.
 *
 * The returned value is a bit mask (see enum uz_JL_flt_dis_fault); multiple causes can be
 * combined. UZ_JL_FLT_DIS_FAULT_NONE (0) means no fault is active.
 *
 * @param self Pointer to driver instance
 * @return enum uz_JL_flt_dis_fault Active fault cause(s)
 */
enum uz_JL_flt_dis_fault uz_JL_flt_dis_get_fault(uz_JL_flt_dis_t *self);

#endif // UZ_JL_FLT_DIS_H
