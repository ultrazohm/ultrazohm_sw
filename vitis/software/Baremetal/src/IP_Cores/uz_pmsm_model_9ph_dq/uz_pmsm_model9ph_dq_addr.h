/*
 * File Name:         hdl_prj123/ipcore/uz_pmsm_model9ph_dq_v1_0/include/uz_pmsm_model9ph_dq_addr.h
 * Description:       C Header File
 * Created:           2022-06-05 23:10:16
*/

#ifndef uz_pmsm_model9ph_dq_H_
#define uz_pmsm_model9ph_dq_H_

// Auto generated
#define  IPCore_Reset_uz_pmsm_model_9ph_dq                         0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_uz_pmsm_model_9ph_dq                        0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_uz_pmsm_model_9ph_dq                     0x8  //contains unique IP timestamp (yymmddHHMM): 2207040950

// Model settings
#define  reset_integrators_Data_uz_pmsm_model_9ph_dq               0x100  //data register for Inport reset_integrators
#define  use_axi_input_Data_uz_pmsm_model_9ph_dq                   0x104  //data register for Inport use_axi_input
#define  simulate_mechanical_Data_uz_pmsm_model_9ph_dq             0x108  //data register for Inport simulate_mechanical

// General inputs
#define  load_torque_Data_uz_pmsm_model_9ph_dq                     0x10C  //data register for Inport load_torque
#define  omega_mech_Data_uz_pmsm_model_9ph_dq                      0x110  //data register for Inport omega_mech

// General outputs
#define  theta_el_out_axi_Data_uz_pmsm_model_9ph_dq                0x14C  //data register for Outport theta_el_out_axi
#define  M_Mi_out_axi_Data_uz_pmsm_model_9ph_dq                    0x174  //data register for Outport M_Mi_out_axi
#define  omega_mech_out_axi_Data_uz_pmsm_model_9ph_dq              0x178  //data register for Outport omega_mech_out_axi

// Voltage input
#define  voltage_input_dq_axi_Data_uz_pmsm_model_9ph_dq            0x180  //data register for Inport voltage_input_dq_axi, vector with 9 elements, address ends at 0x1A0
#define  voltage_input_dq_axi_Strobe_uz_pmsm_model_9ph_dq          0x1C0  //strobe register for port voltage_input_dq_axi

// Current and voltage output
#define  currents_dq_out_axi_Data_uz_pmsm_model_9ph_dq             0x200  //data register for Outport currents_dq_out_axi, vector with 9 elements, address ends at 0x220
#define  currents_dq_out_axi_Strobe_uz_pmsm_model_9ph_dq           0x240  //strobe register for port currents_dq_out_axi
#define  voltage_input_dq_out_axi_fb_Data_uz_pmsm_model_9ph_dq     0x280  //data register for Outport voltage_input_dq_out_axi_fb, vector with 9 elements, address ends at 0x2A0
#define  voltage_input_dq_out_axi_fb_Strobe_uz_pmsm_model_9ph_dq   0x2C0  //strobe register for port voltage_input_dq_out_axi_fb

// Parameters
#define  physical_parameters_mu_Data_uz_pmsm_model_9ph_dq          0x114  //data register for Inport physical_parameters_mu
#define  physical_parameters_M_R0_Data_uz_pmsm_model_9ph_dq        0x118  //data register for Inport physical_parameters_M_R0
#define  physical_parameters_1_L_d_Data_uz_pmsm_model_9ph_dq       0x11C  //data register for Inport physical_parameters_1_L_d
#define  physical_parameters_1_L_q_Data_uz_pmsm_model_9ph_dq       0x120  //data register for Inport physical_parameters_1_L_q
#define  physical_parameters_R_1_Data_uz_pmsm_model_9ph_dq         0x124  //data register for Inport physical_parameters_R_1
#define  physical_parameters_polepair_Data_uz_pmsm_model_9ph_dq    0x128  //data register for Inport physical_parameters_polepair
#define  physical_parameters_psi_pm_Data_uz_pmsm_model_9ph_dq      0x12C  //data register for Inport physical_parameters_psi_pm
#define  physical_parameters_L_x1_Data_uz_pmsm_model_9ph_dq        0x130  //data register for Inport physical_parameters_L_x1
#define  physical_parameters_L_y1_Data_uz_pmsm_model_9ph_dq        0x134  //data register for Inport physical_parameters_L_y1
#define  physical_parameters_L_x2_Data_uz_pmsm_model_9ph_dq        0x138  //data register for Inport physical_parameters_L_x2
#define  physical_parameters_L_y2_Data_uz_pmsm_model_9ph_dq        0x13C  //data register for Inport physical_parameters_L_y2
#define  physical_parameters_L_x3_Data_uz_pmsm_model_9ph_dq        0x140  //data register for Inport physical_parameters_L_x3
#define  physical_parameters_L_y3_Data_uz_pmsm_model_9ph_dq        0x144  //data register for Inport physical_parameters_L_y3
#define  physical_parameters_L_zero_Data_uz_pmsm_model_9ph_dq      0x148  //data register for Inport physical_parameters_L_zero
#define  physical_parameters_1_J_Data_uz_pmsm_model_9ph_dq         0x170  //data register for Inport physical_parameters_1_J






#endif /* uz_pmsm_model9ph_dq_H_ */
