#ifndef UZ_PHASE_VOLTAGES_8_H
#define UZ_PHASE_VOLTAGES_8_H
#include <stdint.h>
#include "../../uz/uz_Transformation/uz_Transformation.h"

/**
 * @brief Object data type definition of the PHASE_VOLTAGES_8 IP-Core driver
 *
 */
typedef struct uz_phase_voltages_8_t uz_phase_voltages_8_t;

struct uz_phase_voltages_8_config_t{
    uint32_t base_address; /**< Base address of the IP-Core */
    uint32_t ip_clk_frequency_Hz; /**< Clock frequency of the IP-Core */
    float theta_el_offset; /**< Offset of theta_el */
    float u_dc_link_voltage; /**< link voltage of the 6-Phase 2-level inverter */
};

/**
 * @brief Initialize an instance of the driver for the PHASE_VOLTAGES_8 IP-Core
 *
 * @param config Configuration struct for the instance
 * @return uz_phase_voltages_8_t* Pointer to an initialized instance of the driver
 */
uz_phase_voltages_8_t* uz_phase_voltages_8_init(struct uz_phase_voltages_8_config_t config);

/**
 * @brief Read the value of Index_in from the PHASE_VOLTAGES_8 IP-Core
 *
 * @param self Pointer to driver instance
 * @return Value of Index_in
 */
//int32_t uz_phase_voltages_8_read_Index_in(uz_phase_voltages_8_t* self);

/**
 * @brief Set the value of done_delay_compensation_AXI from the Phase_voltages_8 IP-Core
 *
 * @param self Pointer to driver instance
 * @param done_delay_compensation_AXI Value
 */
//void uz_phase_voltages_8_set_set_done_delay_compensation_AXI(uz_phase_voltages_8_t* self, _Bool done_delay_compensation_AXI);


#endif // UZ_PHASE_VOLTAGES_8_H
