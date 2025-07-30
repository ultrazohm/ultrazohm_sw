#pragma once

#include "../globalData.h"

struct uz_6ph_dq_t uz_CurrentControl_sample_6ph(uz_CurrentControl_t* self1, uz_CurrentControl_t* self2, uz_6ph_dq_t i_dq_6ph_ref, uz_6ph_dq_t i_dq_6ph_meas, float u_dc1, float u_dc2, float omega_el_rad_per_sec);

void update_current_measurements(AnalogAdapters* aa, uz_3ph_abc_t* i_abc_inverter1, uz_3ph_abc_t* i_abc_inverter2, uz_3ph_abc_t* i_abc_inverter3);
void update_dc_current_measurements(AnalogAdapters* aa, float* i_dc1, float* i_dc2, float* i_dc3);

void update_voltage_measurements(AnalogAdapters* aa, uz_3ph_abc_t* u_abc_inverter1, uz_3ph_abc_t* u_abc_inverter2, uz_3ph_abc_t* u_abc_inverter3);
void update_dc_voltage_measurements(AnalogAdapters* aa, float* u_dc1, float* u_dc2, float* u_dc3);

float read_highest_inverter_temperature(struct uz_inverter_adapter_outputs_t* inv);



//Offset from Valentin
//float theta_offset = 5.93f;
#define PHASE_CURRENT_CONV 12.5f
#define PHASE_VOLT_CONV	12.0f

#define PHASE_CURRENT_CONV_A1	12.803f
#define PHASE_CURRENT_CONV_B1	12.663f
#define PHASE_CURRENT_CONV_C1	12.652f
#define PHASE_CURRENT_CONV_A2	12.67f
#define PHASE_CURRENT_CONV_B2	12.69f
#define PHASE_CURRENT_CONV_C2	12.643f
#define PHASE_CURRENT_CONV_A3	12.513f
#define PHASE_CURRENT_CONV_B3	12.583f
#define PHASE_CURRENT_CONV_C3	12.461f

#define PHASE_CURRENT_OFFSET_A1	0.012f
#define PHASE_CURRENT_OFFSET_B1	0.004f
#define PHASE_CURRENT_OFFSET_C1	0.006f
#define PHASE_CURRENT_OFFSET_A2	-0.012f
#define PHASE_CURRENT_OFFSET_B2	-0.01f
#define PHASE_CURRENT_OFFSET_C2	0.019f
#define PHASE_CURRENT_OFFSET_A3	-0.008f
#define PHASE_CURRENT_OFFSET_B3	-0.015f
#define PHASE_CURRENT_OFFSET_C3	0.008f

#define PHASE_VOLT_CONV_A1	11.963f
#define PHASE_VOLT_CONV_B1	11.959f
#define PHASE_VOLT_CONV_C1	11.954f
#define PHASE_VOLT_CONV_A2	11.959f
#define PHASE_VOLT_CONV_B2	11.959f
#define PHASE_VOLT_CONV_C2	11.961f
#define PHASE_VOLT_CONV_A3	12.000f // Javascope = ripple between 40.021V and 40.038V & Voltage Source = 40V
#define PHASE_VOLT_CONV_B3	12.000f // Javascope = ripple between 40.020V and 40.036V & Voltage Source = 40V
#define PHASE_VOLT_CONV_C3	12.000f // Javascope = ripple between 40.046V and 40.062V & Voltage Source = 40V

#define PHASE_VOLT_OFFSET_A1	-0.09f
#define PHASE_VOLT_OFFSET_B1	0.002f
#define PHASE_VOLT_OFFSET_C1	-0.065f
#define PHASE_VOLT_OFFSET_A2	-0.038f
#define PHASE_VOLT_OFFSET_B2	-0.049f
#define PHASE_VOLT_OFFSET_C2	-0.02f
#define PHASE_VOLT_OFFSET_A3	0.053f
#define PHASE_VOLT_OFFSET_B3	0.066f
#define PHASE_VOLT_OFFSET_C3	0.092f


