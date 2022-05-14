#include "uz_inverter_3ph_hw.h"
#include "uz_inverter_3ph_hwAddresses.h"
#include "../../uz/uz_AXI.h"
#include "../../uz/uz_fixedpoint/uz_fixedpoint.h"

struct uz_fixedpoint_definition_t def={
    .is_signed=false,
    .fractional_bits=0,
    .integer_bits=1
};

void uz_inverter_3ph_hw_write_switch_pspl_abc(uint32_t base_address,  float switch_pspl_abc){
    uz_assert_not_zero(base_address);
    return uz_axi_write_float(base_address + switch_pspl_abc_Data_uz_inverter_3ph, switch_pspl_abc);
}

void uz_inverter_3ph_hw_write_switch_pspl_gate(uint32_t base_address,  float switch_pspl_gate){
    uz_assert_not_zero(base_address);
    return uz_axi_write_float(base_address + switch_pspl_gate_Data_uz_inverter_3ph, switch_pspl_gate);
}

void uz_inverter_3ph_hw_write_udc(uint32_t base_address, float udc){
    uz_assert_not_zero(base_address);
    return uz_axi_write_float(base_address + u_dc_Data_uz_inverter_3ph, udc);
}

// Outport for phase voltages
float uz_inverter_3ph_hw_read_u_ab_ps(uint32_t base_address){
    uz_assert_not_zero(base_address);
    return uz_axi_read_float(base_address + u_ab_ps_Data_uz_inverter_3ph);
}

float uz_inverter_3ph_hw_read_u_bc_ps(uint32_t base_address){
    uz_assert_not_zero(base_address);
    return uz_axi_read_float(base_address + u_bc_ps_Data_uz_inverter_3ph);
}

float uz_inverter_3ph_hw_read_u_ca_ps(uint32_t base_address){
    uz_assert_not_zero(base_address);
    return uz_axi_read_float(base_address + u_ca_ps_Data_uz_inverter_3ph);
}

void uz_inverter_3ph_hw_trigger_u_abc_ps_strobe(uint32_t base_address){
    uz_assert_not_zero_uint32(base_address);
    uz_axi_write_bool(base_address+u_abc_ps_Strobe_uz_inverter_3ph,true);
    uz_axi_write_bool(base_address+u_abc_ps_Strobe_uz_inverter_3ph,false);
}

void uz_inverter_3ph_hw_write_i_a_ps(uint32_t base_address, float i_a_ps){
    uz_assert_not_zero(base_address);
    return uz_axi_write_float(base_address + i_a_ps_Data_uz_inverter_3ph, i_a_ps);
}

void uz_inverter_3ph_hw_write_i_b_ps(uint32_t base_address, float i_b_ps){
    uz_assert_not_zero(base_address);
    return uz_axi_write_float(base_address + i_b_ps_Data_uz_inverter_3ph, i_b_ps);
}

void uz_inverter_3ph_hw_write_i_c_ps(uint32_t base_address, float i_c_ps){
    uz_assert_not_zero(base_address);
    return uz_axi_write_float(base_address + i_c_ps_Data_uz_inverter_3ph, i_c_ps);
}

void uz_inverter_3ph_hw_trigger_i_abc_ps_strobe(uint32_t base_address){
    uz_assert_not_zero_uint32(base_address);
    uz_axi_write_bool(base_address+i_abc_ps_Strobe_uz_inverter_3ph,true);
    uz_axi_write_bool(base_address+i_abc_ps_Strobe_uz_inverter_3ph,false);
}

void uz_inverter_3ph_hw_write_gate1(uint32_t base_address,  float gate1){
    uz_assert_not_zero(base_address);
    return uz_axi_write_float(base_address + gate1_ps_Data_uz_inverter_3ph, gate1);
}

void uz_inverter_3ph_hw_write_gate2(uint32_t base_address,  float gate2){
    uz_assert_not_zero(base_address);
    return uz_axi_write_float(base_address + gate2_ps_Data_uz_inverter_3ph, gate2);
}

void uz_inverter_3ph_hw_write_gate3(uint32_t base_address,  float gate3){
    uz_assert_not_zero(base_address);
    return uz_axi_write_float(base_address + gate3_ps_Data_uz_inverter_3ph, gate3);
}

void uz_inverter_3ph_hw_write_gate4(uint32_t base_address,  float gate4){
    uz_assert_not_zero(base_address);
    return uz_axi_write_float(base_address + gate4_ps_Data_uz_inverter_3ph, gate4);
}

void uz_inverter_3ph_hw_write_gate5(uint32_t base_address, float gate5){
    uz_assert_not_zero(base_address);
    return uz_axi_write_float(base_address + gate5_ps_Data_uz_inverter_3ph, gate5);
}

void uz_inverter_3ph_hw_write_gate6(uint32_t base_address, float gate6){
    uz_assert_not_zero(base_address);
    return uz_axi_write_float(base_address + gate6_ps_Data_uz_inverter_3ph, gate6);
}

void uz_inverter_3ph_hw_trigger_gate_ps_strobe(uint32_t base_address){
    uz_assert_not_zero_uint32(base_address);
    uz_axi_write_bool(base_address+gate_ps_Strobe_uz_inverter_3ph,true);
    uz_axi_write_bool(base_address+gate_ps_Strobe_uz_inverter_3ph,false);
}
















