
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
 * checked with a bitwise AND. UZ_JL_FLT_DIS_FAULT_NONE (0) means no fault is active.
 *
 * Bit encoding per HDL (uz_JL_flt_ip_src_uz_JL_flt_dis.vhd): FLT_ps is a ufix11 output built
 * from the sum of five latched fault flags (five S-R flip-flops), i.e. bits 0..4 are meaningful:
 *   bit0..bit3 = FLT_1..FLT_4 (PL-wired hardware fault inputs of the power stage),
 *   bit4       = FLT_PS       (AXI-written aggregated fault set via uz_JL_flt_dis_set_FLT_PS,
 *                              e.g. forwarded from the OCP path).
 *
 * TODO: the exact physical meaning of FLT_1..FLT_4 (which gate driver / signal) follows from the
 * Vivado block-design wiring; refine the comments once confirmed. The bit positions are fixed.
 */
enum uz_JL_flt_dis_fault {
    UZ_JL_FLT_DIS_FAULT_NONE   = 0,
    UZ_JL_FLT_DIS_FAULT_FLT_1  = 1,   // PL-HW-Fehlereingang FLT_1 (Endstufe)
    UZ_JL_FLT_DIS_FAULT_FLT_2  = 2,   // PL-HW-Fehlereingang FLT_2
    UZ_JL_FLT_DIS_FAULT_FLT_3  = 4,   // PL-HW-Fehlereingang FLT_3
    UZ_JL_FLT_DIS_FAULT_FLT_4  = 8,   // PL-HW-Fehlereingang FLT_4
    UZ_JL_FLT_DIS_FAULT_FLT_PS = 16,  // per set_FLT_PS gesetzter aggregierter Fehler (z. B. OCP)
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
