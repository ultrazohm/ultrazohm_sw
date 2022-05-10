#ifndef UZ_INVERTER_3PH_H
#define UZ_INVERTER_3PH_H

#include <stdint.h>
#include <stdbool.h>

//Switches
void uz_inverter_3ph_hw_write_switch_pspl_abc(uint32_t base_address, float switch_pspl_abc);
void uz_inverter_3ph_hw_write_switch_pspl_gate(uint32_t base_address, float switch_pspl_gate);

// Model Outputs
float uz_inverter_3ph_hw_read_u_ab_ps(uint32_t base_address);
float uz_inverter_3ph_hw_read_u_bc_ps(uint32_t base_address);
float uz_inverter_3ph_hw_read_u_ca_ps(uint32_t base_address);
void uz_inverter_3ph_hw_trigger_u_abc_ps_strobe(uint32_t base_address);

// Model Inputs Iabc
void uz_inverter_3ph_hw_write_i_a_ps(uint32_t base_address, float i_a_ps);
void uz_inverter_3ph_hw_write_i_b_ps(uint32_t base_address, float i_b_ps);
void uz_inverter_3ph_hw_write_i_c_ps(uint32_t base_address, float i_c_ps);
void uz_inverter_3ph_hw_trigger_i_abc_ps_strobe(uint32_t base_address);

// Model Inputs Gate Signals
void uz_inverter_3ph_hw_write_gate1(uint32_t base_address, float gate1);
void uz_inverter_3ph_hw_write_gate2(uint32_t base_address, float gate2);
void uz_inverter_3ph_hw_write_gate3(uint32_t base_address, float gate3);
void uz_inverter_3ph_hw_write_gate4(uint32_t base_address, float gate4);
void uz_inverter_3ph_hw_write_gate5(uint32_t base_address, float gate5);
void uz_inverter_3ph_hw_write_gate6(uint32_t base_address, float gate6);
void uz_inverter_3ph_hw_trigger_gate_ps_strobe(uint32_t base_address);

#endif // uz_inverter_3ph_HW_H
