/*
 * File Name:         hdl_prj123/ipcore/uz_pmsm_model_9ph_only_dq2_v1_0/include/uz_pmsm_model_9ph_only_dq2_addr.h
 * Description:       C Header File
 * Created:           2022-06-05 23:10:16
*/

#ifndef UZ_PMSM_MODEL_9PH_ONLY_DQ2_H_
#define UZ_PMSM_MODEL_9PH_ONLY_DQ2_H_

#define  IPCore_Reset_uz_pmsm_model_9ph_only_dq2                        0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_uz_pmsm_model_9ph_only_dq2                       0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_uz_pmsm_model_9ph_only_dq2                    0x8  //contains unique IP timestamp (yymmddHHMM): 2206052310

#define  load_torque_Data_uz_pmsm_model_9ph_only_dq2                    0x100  //data register for Inport load_torque
#define  reset_integrators__Data_uz_pmsm_model_9ph_only_dq2            0x104  //data register for Inport <reset_integrators>
#define  simulate_mechanical_Data_uz_pmsm_model_9ph_only_dq2            0x108  //data register for Inport simulate_mechanical
#define  omega_mech_Data_uz_pmsm_model_9ph_only_dq2                     0x10C  //data register for Inport omega_mech
#define  M_Mi_axi_Data_uz_pmsm_model_9ph_only_dq2                       0x14C  //data register for Outport M_Mi_axi
#define  omega_out_axi_Data_uz_pmsm_model_9ph_only_dq2                  0x150  //data register for Outport omega_out_axi
#define  use_axi_input_Data_uz_pmsm_model_9ph_only_dq2                  0x154  //data register for Inport use_axi_input

#define  theta_el_axi_Data_uz_pmsm_model_9ph_only_dq2                   0x190  //data register for Outport theta_el_axi

#define  voltage_input_dq_axi_Data_uz_pmsm_model_9ph_only_dq2           0x1C0  //data register for Inport voltage_input_dq_axi, vector with 9 elements, address ends at 0x1E0
#define  voltage_input_dq_axi_Strobe_uz_pmsm_model_9ph_only_dq2         0x200  //strobe register for port voltage_input_dq_axi

#define  currents_dq_output_axi_Data_uz_pmsm_model_9ph_only_dq2         0x240  //data register for Outport currents_dq_output_axi, vector with 9 elements, address ends at 0x260
#define  currents_dq_output_axi_Strobe_uz_pmsm_model_9ph_only_dq2       0x280  //strobe register for port currents_dq_output_axi

#define  voltage_input_dq_axi_fb_Data_uz_pmsm_model_9ph_only_dq2        0x340  //data register for Outport voltage_input_dq_axi_fb, vector with 9 elements, address ends at 0x360
#define  voltage_input_dq_axi_fb_Strobe_uz_pmsm_model_9ph_only_dq2      0x380  //strobe register for port voltage_input_dq_axi_fb


#define  physical_parameters_1_J_Data_uz_pmsm_model_9ph_only_dq2        0x110  //data register for Inport physical_parameters_1_J
#define  physical_parameters_mu_Data_uz_pmsm_model_9ph_only_dq2         0x114  //data register for Inport physical_parameters_mu
#define  physical_parameters_M_R0_Data_uz_pmsm_model_9ph_only_dq2       0x118  //data register for Inport physical_parameters_M_R0
#define  physical_parameters_1_L_d_Data_uz_pmsm_model_9ph_only_dq2      0x11C  //data register for Inport physical_parameters_1_L_d
#define  physical_parameters_1_L_q_Data_uz_pmsm_model_9ph_only_dq2      0x120  //data register for Inport physical_parameters_1_L_q
#define  physical_parameters_R_1_Data_uz_pmsm_model_9ph_only_dq2        0x124  //data register for Inport physical_parameters_R_1
#define  physical_parameters_polepair_Data_uz_pmsm_model_9ph_only_dq2   0x128  //data register for Inport physical_parameters_polepair
#define  physical_parameters_psi_pm_Data_uz_pmsm_model_9ph_only_dq2     0x12C  //data register for Inport physical_parameters_psi_pm
#define  physical_parameters_L_z1_Data_uz_pmsm_model_9ph_only_dq2       0x130  //data register for Inport physical_parameters_L_z1
#define  physical_parameters_L_z2_Data_uz_pmsm_model_9ph_only_dq2       0x134  //data register for Inport physical_parameters_L_z2
#define  physical_parameters_L_x1_Data_uz_pmsm_model_9ph_only_dq2       0x138  //data register for Inport physical_parameters_L_x1
#define  physical_parameters_L_y1_Data_uz_pmsm_model_9ph_only_dq2       0x13C  //data register for Inport physical_parameters_L_y1
#define  physical_parameters_L_x2_Data_uz_pmsm_model_9ph_only_dq2       0x140  //data register for Inport physical_parameters_L_x2
#define  physical_parameters_L_y2_Data_uz_pmsm_model_9ph_only_dq2       0x144  //data register for Inport physical_parameters_L_y2
#define  physical_parameters_L_z3_Data_uz_pmsm_model_9ph_only_dq2       0x148  //data register for Inport physical_parameters_L_z3

#endif /* UZ_PMSM_MODEL_9PH_ONLY_DQ2_H_ */
