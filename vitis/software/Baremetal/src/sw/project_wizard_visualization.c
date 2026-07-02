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
    project_wizard_visualization_data.viz_adc_max11331_a3_ch0 = data->av.adc_max11331_a3_ch0;
    project_wizard_visualization_data.viz_adc_max11331_a3_ch1 = data->av.adc_max11331_a3_ch1;
    project_wizard_visualization_data.viz_adc_max11331_a3_ch2 = data->av.adc_max11331_a3_ch2;
    project_wizard_visualization_data.viz_adc_max11331_a3_ch3 = data->av.adc_max11331_a3_ch3;
    project_wizard_visualization_data.viz_adc_max11331_a3_ch4 = data->av.adc_max11331_a3_ch4;
    project_wizard_visualization_data.viz_adc_max11331_a3_ch5 = data->av.adc_max11331_a3_ch5;
    project_wizard_visualization_data.viz_adc_max11331_a3_ch6 = data->av.adc_max11331_a3_ch6;
    project_wizard_visualization_data.viz_adc_max11331_a3_ch7 = data->av.adc_max11331_a3_ch7;
    project_wizard_visualization_data.viz_adc_max11331_a3_ch8 = data->av.adc_max11331_a3_ch8;
    project_wizard_visualization_data.viz_adc_max11331_a3_ch9 = data->av.adc_max11331_a3_ch9;
    project_wizard_visualization_data.viz_adc_max11331_a3_ch10 = data->av.adc_max11331_a3_ch10;
    project_wizard_visualization_data.viz_adc_max11331_a3_ch11 = data->av.adc_max11331_a3_ch11;
    project_wizard_visualization_data.viz_adc_max11331_a3_ch12 = data->av.adc_max11331_a3_ch12;
    project_wizard_visualization_data.viz_adc_max11331_a3_ch13 = data->av.adc_max11331_a3_ch13;
    project_wizard_visualization_data.viz_adc_max11331_a3_ch14 = data->av.adc_max11331_a3_ch14;
    project_wizard_visualization_data.viz_adc_max11331_a3_ch15 = data->av.adc_max11331_a3_ch15;
    project_wizard_visualization_data.viz_adc_max11331_a3_ch16 = data->av.adc_max11331_a3_ch16;
    project_wizard_visualization_data.viz_adc_max11331_a3_ch17 = data->av.adc_max11331_a3_ch17;
    project_wizard_visualization_data.viz_adc_max11331_a3_ch18 = data->av.adc_max11331_a3_ch18;
    project_wizard_visualization_data.viz_adc_max11331_a3_ch19 = data->av.adc_max11331_a3_ch19;
    project_wizard_visualization_data.viz_adc_max11331_a3_ch20 = data->av.adc_max11331_a3_ch20;
    project_wizard_visualization_data.viz_adc_max11331_a3_ch21 = data->av.adc_max11331_a3_ch21;
    project_wizard_visualization_data.viz_adc_max11331_a3_ch22 = data->av.adc_max11331_a3_ch22;
    project_wizard_visualization_data.viz_adc_max11331_a3_ch23 = data->av.adc_max11331_a3_ch23;
    project_wizard_visualization_data.viz_resolver_pl_interface_d4_1_position_mech_2pi = data->av.resolver_pl_interface_d4_1_position_mech_2pi;
    project_wizard_visualization_data.viz_resolver_pl_interface_d4_1_position_el_2pi = data->av.resolver_pl_interface_d4_1_position_el_2pi;
    project_wizard_visualization_data.viz_resolver_pl_interface_d4_1_n_mech_rpm = data->av.resolver_pl_interface_d4_1_n_mech_rpm;
    project_wizard_visualization_data.viz_endat_encoder_d5_1_position_mech_si_single_turn = data->av.endat_encoder_d5_1_position_mech_si_single_turn;
    project_wizard_visualization_data.viz_endat_encoder_d5_1_position_el_si_single_turn = data->av.endat_encoder_d5_1_position_el_si_single_turn;
    project_wizard_visualization_data.viz_endat_encoder_d5_1_speed_mech_rpm = data->av.endat_encoder_d5_1_speed_mech_rpm;
    project_wizard_visualization_data.viz_inverter_adapter_d2_chip_temp_h1 = data->av.inverter_adapter_d2.ChipTempDegreesCelsius_H1;
    project_wizard_visualization_data.viz_inverter_adapter_d3_chip_temp_h1 = data->av.inverter_adapter_d3.ChipTempDegreesCelsius_H1;
}
