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
    project_wizard_visualization_data.viz_ssi_encoder_d4_1_position_mech_si_single_turn = data->av.ssi_encoder_d4_1_position_mech_si_single_turn;
    project_wizard_visualization_data.viz_ssi_encoder_d4_1_position_el_si_single_turn = data->av.ssi_encoder_d4_1_position_el_si_single_turn;
    project_wizard_visualization_data.viz_resolver_pl_interface_d5_1_position_mech_2pi = data->av.resolver_pl_interface_d5_1_position_mech_2pi;
    project_wizard_visualization_data.viz_resolver_pl_interface_d5_1_position_el_2pi = data->av.resolver_pl_interface_d5_1_position_el_2pi;
    project_wizard_visualization_data.viz_resolver_pl_interface_d5_2_position_mech_2pi = data->av.resolver_pl_interface_d5_2_position_mech_2pi;
    project_wizard_visualization_data.viz_resolver_pl_interface_d5_2_position_el_2pi = data->av.resolver_pl_interface_d5_2_position_el_2pi;
    project_wizard_visualization_data.viz_inverter_adapter_d1_chip_temp_h1 = data->av.inverter_adapter_d1.ChipTempDegreesCelsius_H1;
    project_wizard_visualization_data.viz_inverter_adapter_d1_chip_temp_l1 = data->av.inverter_adapter_d1.ChipTempDegreesCelsius_L1;
    project_wizard_visualization_data.viz_inverter_adapter_d1_chip_temp_h2 = data->av.inverter_adapter_d1.ChipTempDegreesCelsius_H2;
    project_wizard_visualization_data.viz_inverter_adapter_d1_chip_temp_l2 = data->av.inverter_adapter_d1.ChipTempDegreesCelsius_L2;
    project_wizard_visualization_data.viz_inverter_adapter_d1_chip_temp_h3 = data->av.inverter_adapter_d1.ChipTempDegreesCelsius_H3;
    project_wizard_visualization_data.viz_inverter_adapter_d1_chip_temp_l3 = data->av.inverter_adapter_d1.ChipTempDegreesCelsius_L3;
    project_wizard_visualization_data.viz_inverter_adapter_d1_oc = ((float)data->av.inverter_adapter_d1.OC);
    project_wizard_visualization_data.viz_inverter_adapter_d1_fault = ((float)data->av.inverter_adapter_d1.FAULT);
    project_wizard_visualization_data.viz_inverter_adapter_d2_chip_temp_h1 = data->av.inverter_adapter_d2.ChipTempDegreesCelsius_H1;
    project_wizard_visualization_data.viz_inverter_adapter_d2_chip_temp_l1 = data->av.inverter_adapter_d2.ChipTempDegreesCelsius_L1;
    project_wizard_visualization_data.viz_inverter_adapter_d2_chip_temp_h2 = data->av.inverter_adapter_d2.ChipTempDegreesCelsius_H2;
    project_wizard_visualization_data.viz_inverter_adapter_d2_chip_temp_l2 = data->av.inverter_adapter_d2.ChipTempDegreesCelsius_L2;
    project_wizard_visualization_data.viz_inverter_adapter_d2_chip_temp_h3 = data->av.inverter_adapter_d2.ChipTempDegreesCelsius_H3;
    project_wizard_visualization_data.viz_inverter_adapter_d2_chip_temp_l3 = data->av.inverter_adapter_d2.ChipTempDegreesCelsius_L3;
    project_wizard_visualization_data.viz_inverter_adapter_d2_oc = ((float)data->av.inverter_adapter_d2.OC);
    project_wizard_visualization_data.viz_inverter_adapter_d2_fault = ((float)data->av.inverter_adapter_d2.FAULT);
    project_wizard_visualization_data.viz_id_pmsm_cil = data->av.pmsm_cil_outputs.i_d_A;
    project_wizard_visualization_data.viz_iq_pmsm_cil = data->av.pmsm_cil_outputs.i_q_A;
    project_wizard_visualization_data.viz_torque_pmsm_cil = data->av.pmsm_cil_outputs.torque_Nm;
    project_wizard_visualization_data.viz_omega_mech_1_s_cil = data->av.pmsm_cil_outputs.omega_mech_1_s;
}
