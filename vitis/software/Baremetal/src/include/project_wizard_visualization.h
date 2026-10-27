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
    float viz_adc_ltc2311_a3_ch0;
    float viz_adc_ltc2311_a3_ch1;
    float viz_adc_ltc2311_a3_ch2;
    float viz_adc_ltc2311_a3_ch3;
    float viz_adc_ltc2311_a3_ch4;
    float viz_adc_ltc2311_a3_ch5;
    float viz_adc_ltc2311_a3_ch6;
    float viz_adc_ltc2311_a3_ch7;
    float viz_io_card_d2_pin_16;
    float viz_io_card_d2_pin_17;
    float viz_io_card_d2_pin_18;
    float viz_io_card_d2_pin_19;
    float viz_io_card_d2_pin_20;
    float viz_io_card_d2_pin_21;
    float viz_io_card_d2_pin_22;
    float viz_io_card_d2_pin_23;
    float viz_io_card_d2_pin_24;
    float viz_io_card_d2_pin_25;
    float viz_io_card_d2_pin_26;
    float viz_io_card_d2_pin_27;
    float viz_io_card_d2_pin_28;
    float viz_io_card_d2_pin_29;
    float viz_incremental_encoder_d5_1_theta_el;
    float viz_incremental_encoder_d5_1_omega_mech;
    float viz_incremental_encoder_d5_2_theta_el;
    float viz_incremental_encoder_d5_2_omega_mech;
    float viz_incremental_encoder_d5_3_theta_el;
    float viz_incremental_encoder_d5_3_omega_mech;
} project_wizard_visualization_data_t;

extern project_wizard_visualization_data_t project_wizard_visualization_data;

void project_wizard_visualization_update(struct _DS_Data_* data);
