#include "uz_prediction_and_cost_function_8_hw.h"
#include "../../uz/uz_HAL.h"
#include "uz_prediction_and_cost_function_8_hwAddresses.h"
#include "../../uz/uz_fixedpoint/uz_fixedpoint.h"

void uz_prediction_and_cost_function_8_hw_set_Lq(uint32_t base_address, float Lq)
{
    uz_assert_not_zero_uint32(base_address);
    //single
    uz_axi_write_float(base_address + Lq_AXI_Data_parallel_8_prediction_and_cost_function, Lq);
}

void uz_prediction_and_cost_function_8_hw_set_Ld(uint32_t base_address, float Ld)
{
    uz_assert_not_zero_uint32(base_address);
    //single
    uz_axi_write_float(base_address + Ld_AXI_Data_parallel_8_prediction_and_cost_function, Ld);
}

void uz_prediction_and_cost_function_8_hw_set_SampleTime_div_Ld(uint32_t base_address, float SampleTime, float Ld)
{
    uz_assert_not_zero_uint32(base_address);
    //single
    float SampleTime_div_Ld = SampleTime/Ld;
    uz_axi_write_float(base_address + SampleTime_div_Ld_AXI_Data_parallel_8_prediction_and_cost_function, SampleTime_div_Ld);
}

void uz_prediction_and_cost_function_8_hw_set_SampleTime_div_Lq(uint32_t base_address, float SampleTime, float Lq)
{
    uz_assert_not_zero_uint32(base_address);
    //single
    float SampleTime_div_Lq = SampleTime/Lq;
    uz_axi_write_float(base_address + SampleTime_div_Lq_AXI_Data_parallel_8_prediction_and_cost_function, SampleTime_div_Lq);
}

void uz_prediction_and_cost_function_8_hw_set_SampleTime_div_Lx(uint32_t base_address, float SampleTime, float Lx)
{
    uz_assert_not_zero_uint32(base_address);
    //single
    float SampleTime_div_Lx = SampleTime/Lx;
    uz_axi_write_float(base_address + SampleTime_div_Lx_AXI_Data_parallel_8_prediction_and_cost_function, SampleTime_div_Lx);
}

void uz_prediction_and_cost_function_8_hw_set_pole_pairs(uint32_t base_address, float pole_pairs)
{
    uz_assert_not_zero_uint32(base_address);
    //single
    uz_axi_write_float(base_address + pole_pairs_AXI_Data_parallel_8_prediction_and_cost_function, pole_pairs);
}

void uz_prediction_and_cost_function_8_hw_set_SampleTime_div_Ly(uint32_t base_address, float SampleTime, float Ly)
{
    uz_assert_not_zero_uint32(base_address);
    //single
    float SampleTime_div_Ly = SampleTime/Ly;
    uz_axi_write_float(base_address + SampleTime_div_Ly_AXI_Data_parallel_8_prediction_and_cost_function, SampleTime_div_Ly);
}

void uz_prediction_and_cost_function_8_hw_set_Rs(uint32_t base_address, float Rs)
{
    uz_assert_not_zero_uint32(base_address);
    //single
    uz_axi_write_float(base_address + Rs_AXI_Data_parallel_8_prediction_and_cost_function, Rs);
}

void uz_prediction_and_cost_function_8_hw_set_psiPM(uint32_t base_address, float psiPM)
{
    uz_assert_not_zero_uint32(base_address);
    //single
    uz_axi_write_float(base_address + psiPM_AXI_Data_parallel_8_prediction_and_cost_function, psiPM);
}

void uz_prediction_and_cost_function_8_hw_set_id_ref(uint32_t base_address, float id_ref)
{
    uz_assert_not_zero_uint32(base_address);
    //single
    uz_axi_write_float(base_address + id_ref_AXI_Data_parallel_8_prediction_and_cost_function, id_ref);
}

void uz_prediction_and_cost_function_8_hw_set_iq_ref(uint32_t base_address, float iq_ref)
{
    uz_assert_not_zero_uint32(base_address);
    //single
    uz_axi_write_float(base_address + iq_ref_AXI_Data_parallel_8_prediction_and_cost_function, iq_ref);
}

void uz_prediction_and_cost_function_8_hw_set_ix_ref(uint32_t base_address, float ix_ref)
{
    uz_assert_not_zero_uint32(base_address);
    //single
    uz_axi_write_float(base_address + ix_ref_AXI_Data_parallel_8_prediction_and_cost_function, ix_ref);
}

void uz_prediction_and_cost_function_8_hw_set_iy_ref(uint32_t base_address, float iy_ref)
{
    uz_assert_not_zero_uint32(base_address);
    //single
    uz_axi_write_float(base_address + iy_ref_AXI_Data_parallel_8_prediction_and_cost_function, iy_ref);
}