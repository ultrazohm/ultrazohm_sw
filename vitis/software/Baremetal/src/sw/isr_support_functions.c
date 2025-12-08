#include "../include/isr_support_functions.h"

static float TEMP_VSI_largest(float H1, float L1, float H2, float L2, float H3, float L3);

void update_current_measurements(AnalogAdapters* aa, uz_3ph_abc_t* i_abc_inverter1, uz_3ph_abc_t* i_abc_inverter2, uz_3ph_abc_t* i_abc_inverter3) {
	*i_abc_inverter1 = ((uz_3ph_abc_t) {
		.a = aa->A1.me.ADC_A4 * PHASE_CURRENT_CONV_A1 + PHASE_CURRENT_OFFSET_A1,
		.b = aa->A1.me.ADC_A3 * PHASE_CURRENT_CONV_B1 + PHASE_CURRENT_OFFSET_B1,
		.c = aa->A1.me.ADC_A2 * PHASE_CURRENT_CONV_C1 + PHASE_CURRENT_OFFSET_C1,
	});
	*i_abc_inverter2 = ((uz_3ph_abc_t) {
		.a = aa->A2.me.ADC_A4 * PHASE_CURRENT_CONV_A2 + PHASE_CURRENT_OFFSET_A2,
		.b = aa->A2.me.ADC_A3 * PHASE_CURRENT_CONV_B2 + PHASE_CURRENT_OFFSET_B2,
		.c = aa->A2.me.ADC_A2 * PHASE_CURRENT_CONV_C2 + PHASE_CURRENT_OFFSET_C2,
	});
	*i_abc_inverter3 = ((uz_3ph_abc_t) {
		.a = aa->A3.me.ADC_A4 * PHASE_CURRENT_CONV_A3 + PHASE_CURRENT_OFFSET_A3,
		.b = aa->A3.me.ADC_A3 * PHASE_CURRENT_CONV_B3 + PHASE_CURRENT_OFFSET_B3,
		.c = aa->A3.me.ADC_A2 * PHASE_CURRENT_CONV_C3 + PHASE_CURRENT_OFFSET_C3,
	});
}

void update_dc_current_measurements(AnalogAdapters* aa, float* i_dc1, float* i_dc2, float* i_dc3) {
	*i_dc1 = aa->A1.me.ADC_B5 * PHASE_CURRENT_CONV;
	*i_dc2 = aa->A2.me.ADC_B5 * PHASE_CURRENT_CONV;
	*i_dc3 = aa->A3.me.ADC_B5 * PHASE_CURRENT_CONV;
}

void update_voltage_measurements(AnalogAdapters* aa, uz_3ph_abc_t* u_abc_inverter1, uz_3ph_abc_t* u_abc_inverter2, uz_3ph_abc_t* u_abc_inverter3) {
	*u_abc_inverter1 = ((uz_3ph_abc_t) {
		.a = aa->A1.me.ADC_B8 * PHASE_VOLT_CONV_A1 + PHASE_VOLT_OFFSET_A1,
		.b = aa->A1.me.ADC_B7 * PHASE_VOLT_CONV_B1 + PHASE_VOLT_OFFSET_B1,
		.c = aa->A1.me.ADC_B6 * PHASE_VOLT_CONV_C1 + PHASE_VOLT_OFFSET_C1,
	});
	*u_abc_inverter2 = ((uz_3ph_abc_t) {
		.a = aa->A2.me.ADC_B8 * PHASE_VOLT_CONV_A2 + PHASE_VOLT_OFFSET_A2,
		.b = aa->A2.me.ADC_B7 * PHASE_VOLT_CONV_B2 + PHASE_VOLT_OFFSET_B2,
		.c = aa->A2.me.ADC_B6 * PHASE_VOLT_CONV_C2 + PHASE_VOLT_OFFSET_C2,
	});
	*u_abc_inverter3 = ((uz_3ph_abc_t) {
		.a = aa->A3.me.ADC_B8 * PHASE_VOLT_CONV_A3 + PHASE_VOLT_OFFSET_A3,
		.b = aa->A3.me.ADC_B7 * PHASE_VOLT_CONV_B3 + PHASE_VOLT_OFFSET_B3,
		.c = aa->A3.me.ADC_B6 * PHASE_VOLT_CONV_C3 + PHASE_VOLT_OFFSET_C3,
	});
}

void update_dc_voltage_measurements(AnalogAdapters* aa, float* u_dc1, float* u_dc2, float* u_dc3) {
	*u_dc1 = aa->A1.me.ADC_A1 * PHASE_VOLT_CONV;
	*u_dc2 = aa->A2.me.ADC_A1 * PHASE_VOLT_CONV;
	*u_dc3 = aa->A3.me.ADC_A1 * PHASE_VOLT_CONV;
}

float read_highest_inverter_temperature(struct uz_inverter_adapter_outputs_t* inv) {
	return (
		TEMP_VSI_largest(inv->ChipTempDegreesCelsius_H1, inv->ChipTempDegreesCelsius_L1,
						 inv->ChipTempDegreesCelsius_H2, inv->ChipTempDegreesCelsius_L2,
						 inv->ChipTempDegreesCelsius_H3, inv->ChipTempDegreesCelsius_L3)
	);
}

static float TEMP_VSI_largest(float H1, float L1, float H2, float L2, float H3, float L3) {
    float output = H1;
    if(L1 > output) output = L1;
    if(H2 > output) output = H2;
    if(L2 > output) output = L2;
    if(H3 > output) output = H3;
    if(L3 > output) output = L3;
    return output;
}






