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
    float viz_resolver_pl_interface_d4_1_position_mech_2pi;
    float viz_resolver_pl_interface_d4_1_position_el_2pi;
    float viz_resolver_pl_interface_d4_1_omega_mech_rad_s;
    float viz_resolver_pl_interface_d4_1_n_mech_rpm;
    float viz_resolver_pl_interface_d4_1_omega_el_rad_s;
    float viz_resolver_pl_interface_d4_1_revolution_counter;
    float viz_resolver_pl_interface_d4_2_position_mech_2pi;
    float viz_resolver_pl_interface_d4_2_position_el_2pi;
    float viz_resolver_pl_interface_d4_2_omega_mech_rad_s;
    float viz_resolver_pl_interface_d4_2_n_mech_rpm;
    float viz_resolver_pl_interface_d4_2_omega_el_rad_s;
    float viz_resolver_pl_interface_d4_2_revolution_counter;
    float viz_resolver_pl_interface_d4_3_position_mech_2pi;
    float viz_resolver_pl_interface_d4_3_position_el_2pi;
    float viz_resolver_pl_interface_d4_3_omega_mech_rad_s;
    float viz_resolver_pl_interface_d4_3_n_mech_rpm;
    float viz_resolver_pl_interface_d4_3_omega_el_rad_s;
    float viz_resolver_pl_interface_d4_3_revolution_counter;
    float viz_resolver_pl_interface_d5_1_position_mech_2pi;
    float viz_resolver_pl_interface_d5_1_position_el_2pi;
    float viz_resolver_pl_interface_d5_1_omega_mech_rad_s;
    float viz_resolver_pl_interface_d5_1_n_mech_rpm;
    float viz_resolver_pl_interface_d5_1_omega_el_rad_s;
    float viz_resolver_pl_interface_d5_1_revolution_counter;
    float viz_resolver_pl_interface_d5_2_position_mech_2pi;
    float viz_resolver_pl_interface_d5_2_position_el_2pi;
    float viz_resolver_pl_interface_d5_2_omega_mech_rad_s;
    float viz_resolver_pl_interface_d5_2_n_mech_rpm;
    float viz_resolver_pl_interface_d5_2_omega_el_rad_s;
    float viz_resolver_pl_interface_d5_2_revolution_counter;
} project_wizard_visualization_data_t;

extern project_wizard_visualization_data_t project_wizard_visualization_data;

void project_wizard_visualization_update(struct _DS_Data_* data);
