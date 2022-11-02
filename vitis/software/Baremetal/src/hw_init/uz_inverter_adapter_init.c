#include "../include/uz_inverter_adapter_init.h"
#include "../uz/uz_HAL.h"
#include "../uz/uz_global_configuration.h"
#include "xparameters.h"

static struct uz_inverter_adapter_config_t uz_inverter_adapter_config_d1 = {
               .base_address = XPAR_UZ_USER_UZ_D_INVERTER_ADAPTER_0_BASEADDR,
               .ip_clk_frequency_Hz = 100000000,
               .linear_interpolation_params = {162.35f, 20.107f}
};

static struct uz_inverter_adapter_config_t uz_inverter_adapter_config_d2 = {
               .base_address = XPAR_UZ_USER_UZ_D_INVERTER_ADAPTER_1_BASEADDR,
               .ip_clk_frequency_Hz = 100000000,
               .linear_interpolation_params = {162.35f, 20.107f}
};

static struct uz_inverter_adapter_outputs_t uz_inverter_adapter_outputs_d1 = {
   .PWMdutyCycNormalized_H1 = 0.0f,
   .PWMdutyCycNormalized_L1 = 0.0f,
   .PWMdutyCycNormalized_H2 = 0.0f,
   .PWMdutyCycNormalized_L2 = 0.0f,
   .PWMdutyCycNormalized_H3 = 0.0f,
   .PWMdutyCycNormalized_L3 = 0.0f,
   .ChipTempDegreesCelsius_H1 = 0.0f, /**< Chip temperature of H1 in degrees celsius */
   .ChipTempDegreesCelsius_L1 = 0.0f, /**< Chip temperature of L1 in degrees celsius */
   .ChipTempDegreesCelsius_H2 = 0.0f, /**< Chip temperature of H2 in degrees celsius */
   .ChipTempDegreesCelsius_L2 = 0.0f, /**< Chip temperature of L2 in degrees celsius */
   .ChipTempDegreesCelsius_H3 = 0.0f, /**< Chip temperature of H3 in degrees celsius */
   .ChipTempDegreesCelsius_L3 = 0.0f, /**< Chip temperature of L3 in degrees celsius */
   .OC = 0U,
   .OC_H1 = 0U, /**< Over current OC fault signal of H1 */
   .OC_L1 = 0U, /**< Over current OC fault signal of L1 */
   .OC_H2 = 0U, /**< Over current OC fault signal of H2 */
   .OC_L2 = 0U, /**< Over current OC fault signal of L2 */
   .OC_H3 = 0U, /**< Over current OC fault signal of H3 */
   .OC_L3 = 0U, /**< Over current OC fault signal of L3 */
   .FAULT = 0U,
   .FAULT_H1 = 0U, /**< FAULT signal of H1 */
   .FAULT_L1 = 0U, /**< FAULT signal of L1 */
   .FAULT_H2 = 0U, /**< FAULT signal of H2 */
   .FAULT_L2 = 0U, /**< FAULT signal of L2 */
   .FAULT_H3 = 0U, /**< FAULT signal of H3 */
   .FAULT_L3 = 0U, /**< FAULT signal of L3 */
   .I_DIAG = 0U,
   .I_DC_DIAG = 0U, /**< Diagnostic signal of current amplifier for DC current */
   .I1_DIAG = 0U, /**< Diagnostic signal of current amplifier for phase a current */
   .I2_DIAG = 0U, /**< Diagnostic signal of current amplifier for phase b current */
   .I3_DIAG = 0U /**< Diagnostic signal of current amplifier for phase c current */
};

static struct uz_inverter_adapter_outputs_t uz_inverter_adapter_outputs_d2 = {
   .PWMdutyCycNormalized_H1 = 0.0f,
   .PWMdutyCycNormalized_L1 = 0.0f,
   .PWMdutyCycNormalized_H2 = 0.0f,
   .PWMdutyCycNormalized_L2 = 0.0f,
   .PWMdutyCycNormalized_H3 = 0.0f,
   .PWMdutyCycNormalized_L3 = 0.0f,
   .ChipTempDegreesCelsius_H1 = 0.0f, /**< Chip temperature of H1 in degrees celsius */
   .ChipTempDegreesCelsius_L1 = 0.0f, /**< Chip temperature of L1 in degrees celsius */
   .ChipTempDegreesCelsius_H2 = 0.0f, /**< Chip temperature of H2 in degrees celsius */
   .ChipTempDegreesCelsius_L2 = 0.0f, /**< Chip temperature of L2 in degrees celsius */
   .ChipTempDegreesCelsius_H3 = 0.0f, /**< Chip temperature of H3 in degrees celsius */
   .ChipTempDegreesCelsius_L3 = 0.0f, /**< Chip temperature of L3 in degrees celsius */
   .OC = 0U,
   .OC_H1 = 0U, /**< Over current OC fault signal of H1 */
   .OC_L1 = 0U, /**< Over current OC fault signal of L1 */
   .OC_H2 = 0U, /**< Over current OC fault signal of H2 */
   .OC_L2 = 0U, /**< Over current OC fault signal of L2 */
   .OC_H3 = 0U, /**< Over current OC fault signal of H3 */
   .OC_L3 = 0U, /**< Over current OC fault signal of L3 */
   .FAULT = 0U,
   .FAULT_H1 = 0U, /**< FAULT signal of H1 */
   .FAULT_L1 = 0U, /**< FAULT signal of L1 */
   .FAULT_H2 = 0U, /**< FAULT signal of H2 */
   .FAULT_L2 = 0U, /**< FAULT signal of L2 */
   .FAULT_H3 = 0U, /**< FAULT signal of H3 */
   .FAULT_L3 = 0U, /**< FAULT signal of L3 */
   .I_DIAG = 0U,
   .I_DC_DIAG = 0U, /**< Diagnostic signal of current amplifier for DC current */
   .I1_DIAG = 0U, /**< Diagnostic signal of current amplifier for phase a current */
   .I2_DIAG = 0U, /**< Diagnostic signal of current amplifier for phase b current */
   .I3_DIAG = 0U /**< Diagnostic signal of current amplifier for phase c current */
};

uz_inverter_adapter_t* initialize_uz_inverter_adapter_on_D1(void) {
       return(uz_inverter_adapter_init(uz_inverter_adapter_config_d1, uz_inverter_adapter_outputs_d1));
}

uz_inverter_adapter_t* initialize_uz_inverter_adapter_on_D2(void) {
       return(uz_inverter_adapter_init(uz_inverter_adapter_config_d2, uz_inverter_adapter_outputs_d2));
}
