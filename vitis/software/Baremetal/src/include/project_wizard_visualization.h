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
    float viz_adc_max11331_a3_ch0;
    float viz_adc_max11331_a3_ch1;
    float viz_adc_max11331_a3_ch2;
    float viz_adc_max11331_a3_ch3;
    float viz_adc_max11331_a3_ch4;
    float viz_adc_max11331_a3_ch5;
    float viz_adc_max11331_a3_ch6;
    float viz_adc_max11331_a3_ch7;
    float viz_adc_max11331_a3_ch8;
    float viz_adc_max11331_a3_ch9;
    float viz_adc_max11331_a3_ch10;
    float viz_adc_max11331_a3_ch11;
    float viz_adc_max11331_a3_ch12;
    float viz_adc_max11331_a3_ch13;
    float viz_adc_max11331_a3_ch14;
    float viz_adc_max11331_a3_ch15;
    float viz_adc_max11331_a3_ch16;
    float viz_adc_max11331_a3_ch17;
    float viz_adc_max11331_a3_ch18;
    float viz_adc_max11331_a3_ch19;
    float viz_adc_max11331_a3_ch20;
    float viz_adc_max11331_a3_ch21;
    float viz_adc_max11331_a3_ch22;
    float viz_adc_max11331_a3_ch23;
    float viz_incremental_encoder_d1_1_theta_el;
    float viz_incremental_encoder_d1_2_theta_el;
    float viz_incremental_encoder_d1_3_theta_el;
    float viz_inverter_adapter_d3_chip_temp_h1;
    float viz_inverter_adapter_d3_chip_temp_l1;
    float viz_inverter_adapter_d3_chip_temp_h2;
    float viz_inverter_adapter_d3_chip_temp_l2;
    float viz_inverter_adapter_d3_chip_temp_h3;
    float viz_inverter_adapter_d3_chip_temp_l3;
    float viz_temp_d4_a_4;
    float viz_temp_d4_a_5;
    float viz_temp_d4_a_19;
    float viz_endat_encoder_d5_1_position_raw_single_turn;
    float viz_endat_encoder_d5_1_position_raw_multi_turn;
    float viz_endat_encoder_d5_1_position_mech_si_single_turn;
    float viz_endat_encoder_d5_1_position_el_si_single_turn;
    float viz_ssi_encoder_d5_2_position_mech_si_single_turn;
    float viz_ssi_encoder_d5_2_position_el_si_single_turn;
    float viz_ssi_encoder_d5_3_position_mech_si_single_turn;
    float viz_ssi_encoder_d5_3_position_el_si_single_turn;
    float viz_incremental_encoder_d1_1_position;
    float viz_incremental_encoder_d1_2_position;
    float viz_incremental_encoder_d1_3_position;
    float viz_inverter_adapter_d3_oc;
    float viz_inverter_adapter_d3_oc_h1;
    float viz_inverter_adapter_d3_oc_l1;
    float viz_inverter_adapter_d3_oc_h2;
    float viz_inverter_adapter_d3_oc_l2;
    float viz_inverter_adapter_d3_oc_h3;
    float viz_inverter_adapter_d3_oc_l3;
    float viz_inverter_adapter_d3_fault;
} project_wizard_visualization_data_t;

extern project_wizard_visualization_data_t project_wizard_visualization_data;

void project_wizard_visualization_update(struct _DS_Data_* data);
