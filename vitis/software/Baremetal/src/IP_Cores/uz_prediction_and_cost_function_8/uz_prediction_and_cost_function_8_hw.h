#ifndef UZ_PREDICTION_AND_COST_FUNCTION_8_HW_H
#define UZ_PREDICTION_AND_COST_FUNCTION_8_HW_H
#include "stdint.h"

void uz_prediction_and_cost_function_8_hw_set_Lq(uint32_t base_address, float Lq);
void uz_prediction_and_cost_function_8_hw_set_Ld(uint32_t base_address, float Ld);
void uz_prediction_and_cost_function_8_hw_set_SampleTime_div_Ld(uint32_t base_address, float SampleTime, float Ld);
void uz_prediction_and_cost_function_8_hw_set_SampleTime_div_Lq(uint32_t base_address, float SampleTime, float Lq);
void uz_prediction_and_cost_function_8_hw_set_SampleTime_div_Lx(uint32_t base_address, float SampleTime, float Lx);
void uz_prediction_and_cost_function_8_hw_set_pole_pairs(uint32_t base_address, float pole_pairs);
void uz_prediction_and_cost_function_8_hw_set_SampleTime_div_Ly(uint32_t base_address, float SampleTime, float Ly);
void uz_prediction_and_cost_function_8_hw_set_Rs(uint32_t base_address, float Rs);
void uz_prediction_and_cost_function_8_hw_set_psiPM(uint32_t base_address, float psiPM);
void uz_prediction_and_cost_function_8_hw_set_id_ref(uint32_t base_address, float id_ref);
void uz_prediction_and_cost_function_8_hw_set_iq_ref(uint32_t base_address, float iq_ref);
void uz_prediction_and_cost_function_8_hw_set_ix_ref(uint32_t base_address, float ix_ref);
void uz_prediction_and_cost_function_8_hw_set_iy_ref(uint32_t base_address, float iy_ref);
//int32_t uz_prediction_and_cost_function_8_hw_get_Index(uint32_t base_address);
//void uz_prediction_and_cost_function_8_hw_set_done_phase_voltages(uint32_t base_address, _Bool done_phase_voltages);
//void uz_prediction_and_cost_function_8_hw_set_done_vsd_and_park(uint32_t base_address, _Bool done_vsd_and_park);
//void uz_prediction_and_cost_function_8_hw_set_current_valid_in(uint32_t base_address, _Bool current_valid_in);
//_Bool uz_prediction_and_cost_function_8_hw_get_done_prediction_and_cost_function(uint32_t base_address);



#endif // UZ_PREDICTION_AND_COST_FUNCTION_8_HW_H