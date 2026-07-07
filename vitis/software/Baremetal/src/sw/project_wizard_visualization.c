/*
 * Project Wizard generated file.
 *
 * This file is fully owned by Project Wizard code generation.
 * Manual changes may be overwritten the next time software files are generated.
 */

#include "../include/project_wizard_visualization.h"
#include "../globalData.h"

project_wizard_visualization_data_t project_wizard_visualization_data = {0};

void project_wizard_visualization_update(struct _DS_Data_* data)
{
    project_wizard_visualization_data.viz_adc_ltc2311_a1_ch0 = data->av.adc_ltc2311_a1_ch0;
    project_wizard_visualization_data.viz_adc_ltc2311_a1_ch1 = data->av.adc_ltc2311_a1_ch1;
    project_wizard_visualization_data.viz_adc_ltc2311_a1_ch2 = data->av.adc_ltc2311_a1_ch2;
    project_wizard_visualization_data.viz_adc_ltc2311_a1_ch3 = data->av.adc_ltc2311_a1_ch3;
    project_wizard_visualization_data.viz_adc_ltc2311_a1_ch4 = data->av.adc_ltc2311_a1_ch4;
    project_wizard_visualization_data.viz_adc_ltc2311_a1_ch5 = data->av.adc_ltc2311_a1_ch5;
    project_wizard_visualization_data.viz_adc_ltc2311_a1_ch6 = data->av.adc_ltc2311_a1_ch6;
    project_wizard_visualization_data.viz_adc_ltc2311_a1_ch7 = data->av.adc_ltc2311_a1_ch7;
    project_wizard_visualization_data.viz_adc_ltc2311_a2_ch0 = data->av.adc_ltc2311_a2_ch0;
    project_wizard_visualization_data.viz_adc_ltc2311_a2_ch1 = data->av.adc_ltc2311_a2_ch1;
    project_wizard_visualization_data.viz_adc_ltc2311_a2_ch2 = data->av.adc_ltc2311_a2_ch2;
    project_wizard_visualization_data.viz_adc_ltc2311_a2_ch3 = data->av.adc_ltc2311_a2_ch3;
    project_wizard_visualization_data.viz_adc_ltc2311_a2_ch4 = data->av.adc_ltc2311_a2_ch4;
    project_wizard_visualization_data.viz_adc_ltc2311_a2_ch5 = data->av.adc_ltc2311_a2_ch5;
    project_wizard_visualization_data.viz_adc_ltc2311_a2_ch6 = data->av.adc_ltc2311_a2_ch6;
    project_wizard_visualization_data.viz_adc_ltc2311_a2_ch7 = data->av.adc_ltc2311_a2_ch7;
    project_wizard_visualization_data.viz_adc_ltc2311_a3_ch0 = data->av.adc_ltc2311_a3_ch0;
    project_wizard_visualization_data.viz_adc_ltc2311_a3_ch1 = data->av.adc_ltc2311_a3_ch1;
    project_wizard_visualization_data.viz_adc_ltc2311_a3_ch2 = data->av.adc_ltc2311_a3_ch2;
    project_wizard_visualization_data.viz_adc_ltc2311_a3_ch3 = data->av.adc_ltc2311_a3_ch3;
    project_wizard_visualization_data.viz_adc_ltc2311_a3_ch4 = data->av.adc_ltc2311_a3_ch4;
    project_wizard_visualization_data.viz_adc_ltc2311_a3_ch5 = data->av.adc_ltc2311_a3_ch5;
    project_wizard_visualization_data.viz_adc_ltc2311_a3_ch6 = data->av.adc_ltc2311_a3_ch6;
    project_wizard_visualization_data.viz_adc_ltc2311_a3_ch7 = data->av.adc_ltc2311_a3_ch7;
    project_wizard_visualization_data.viz_resolver_pl_interface_d4_1_position_mech_2pi = data->av.resolver_pl_interface_d4_1_position_mech_2pi;
    project_wizard_visualization_data.viz_resolver_pl_interface_d4_1_position_el_2pi = data->av.resolver_pl_interface_d4_1_position_el_2pi;
    project_wizard_visualization_data.viz_resolver_pl_interface_d4_1_omega_mech_rad_s = data->av.resolver_pl_interface_d4_1_omega_mech_rad_s;
    project_wizard_visualization_data.viz_resolver_pl_interface_d4_1_n_mech_rpm = data->av.resolver_pl_interface_d4_1_n_mech_rpm;
    project_wizard_visualization_data.viz_resolver_pl_interface_d4_1_omega_el_rad_s = data->av.resolver_pl_interface_d4_1_omega_el_rad_s;
    project_wizard_visualization_data.viz_resolver_pl_interface_d4_1_revolution_counter = ((float)data->av.resolver_pl_interface_d4_1_revolution_counter);
    project_wizard_visualization_data.viz_resolver_pl_interface_d4_2_position_mech_2pi = data->av.resolver_pl_interface_d4_2_position_mech_2pi;
    project_wizard_visualization_data.viz_resolver_pl_interface_d4_2_position_el_2pi = data->av.resolver_pl_interface_d4_2_position_el_2pi;
    project_wizard_visualization_data.viz_resolver_pl_interface_d4_2_omega_mech_rad_s = data->av.resolver_pl_interface_d4_2_omega_mech_rad_s;
    project_wizard_visualization_data.viz_resolver_pl_interface_d4_2_n_mech_rpm = data->av.resolver_pl_interface_d4_2_n_mech_rpm;
    project_wizard_visualization_data.viz_resolver_pl_interface_d4_2_omega_el_rad_s = data->av.resolver_pl_interface_d4_2_omega_el_rad_s;
    project_wizard_visualization_data.viz_resolver_pl_interface_d4_2_revolution_counter = ((float)data->av.resolver_pl_interface_d4_2_revolution_counter);
    project_wizard_visualization_data.viz_resolver_pl_interface_d4_3_position_mech_2pi = data->av.resolver_pl_interface_d4_3_position_mech_2pi;
    project_wizard_visualization_data.viz_resolver_pl_interface_d4_3_position_el_2pi = data->av.resolver_pl_interface_d4_3_position_el_2pi;
    project_wizard_visualization_data.viz_resolver_pl_interface_d4_3_omega_mech_rad_s = data->av.resolver_pl_interface_d4_3_omega_mech_rad_s;
    project_wizard_visualization_data.viz_resolver_pl_interface_d4_3_n_mech_rpm = data->av.resolver_pl_interface_d4_3_n_mech_rpm;
    project_wizard_visualization_data.viz_resolver_pl_interface_d4_3_omega_el_rad_s = data->av.resolver_pl_interface_d4_3_omega_el_rad_s;
    project_wizard_visualization_data.viz_resolver_pl_interface_d4_3_revolution_counter = ((float)data->av.resolver_pl_interface_d4_3_revolution_counter);
}
