/*
 * Project Wizard generated file.
 *
 * This file is fully owned by Project Wizard code generation.
 * Manual changes may be overwritten the next time software files are generated.
 */

#pragma once

struct _DS_Data_;

typedef struct {
    float viz_adc_ltc2311_a1_ch0;
    float viz_adc_ltc2311_a1_ch1;
    float viz_adc_ltc2311_a1_ch2;
    float viz_adc_ltc2311_a1_ch3;
    float viz_adc_ltc2311_a1_ch4;
    float viz_adc_ltc2311_a1_ch5;
    float viz_adc_ltc2311_a1_ch6;
    float viz_adc_ltc2311_a1_ch7;
    float viz_adc_ltc2311_a2_ch0;
    float viz_adc_ltc2311_a2_ch1;
    float viz_adc_ltc2311_a2_ch2;
    float viz_adc_ltc2311_a2_ch3;
    float viz_adc_ltc2311_a2_ch4;
    float viz_adc_ltc2311_a2_ch5;
    float viz_adc_ltc2311_a2_ch6;
    float viz_adc_ltc2311_a2_ch7;
    float viz_ssi_encoder_d4_1_position_mech_si_single_turn;
    float viz_ssi_encoder_d4_1_position_el_si_single_turn;
    float viz_resolver_pl_interface_d5_1_position_mech_2pi;
    float viz_resolver_pl_interface_d5_1_position_el_2pi;
    float viz_resolver_pl_interface_d5_2_position_mech_2pi;
    float viz_resolver_pl_interface_d5_2_position_el_2pi;
    float viz_inverter_adapter_d1_chip_temp_h1;
    float viz_inverter_adapter_d1_chip_temp_l1;
    float viz_inverter_adapter_d1_chip_temp_h2;
    float viz_inverter_adapter_d1_chip_temp_l2;
    float viz_inverter_adapter_d1_chip_temp_h3;
    float viz_inverter_adapter_d1_chip_temp_l3;
    float viz_inverter_adapter_d1_oc;
    float viz_inverter_adapter_d1_fault;
    float viz_inverter_adapter_d2_chip_temp_h1;
    float viz_inverter_adapter_d2_chip_temp_l1;
    float viz_inverter_adapter_d2_chip_temp_h2;
    float viz_inverter_adapter_d2_chip_temp_l2;
    float viz_inverter_adapter_d2_chip_temp_h3;
    float viz_inverter_adapter_d2_chip_temp_l3;
    float viz_inverter_adapter_d2_oc;
    float viz_inverter_adapter_d2_fault;
    float viz_id_pmsm_cil;
    float viz_iq_pmsm_cil;
    float viz_torque_pmsm_cil;
    float viz_omega_mech_1_s_cil;
} project_wizard_visualization_data_t;

extern project_wizard_visualization_data_t project_wizard_visualization_data;

void project_wizard_visualization_update(struct _DS_Data_* data);
