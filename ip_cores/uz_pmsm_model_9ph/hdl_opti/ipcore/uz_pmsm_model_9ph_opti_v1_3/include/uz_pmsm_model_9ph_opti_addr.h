/*
 * File Name:         C:\Users\valen\Documents\repos\UZ\ultrazohm_sw\ip_cores\uz_pmsm_model_9ph\hdl_opti\ipcore\uz_pmsm_model_9ph_opti_v1_3\include\uz_pmsm_model_9ph_opti_addr.h
 * Description:       C Header File
 * Created:           2022-05-03 11:24:14
*/

#ifndef UZ_PMSM_MODEL_9PH_OPTI_H_
#define UZ_PMSM_MODEL_9PH_OPTI_H_

#define  IPCore_Reset_uz_pmsm_model_9ph_opti                               0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_uz_pmsm_model_9ph_opti                              0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_uz_pmsm_model_9ph_opti                           0x8  //contains unique IP timestamp (yymmddHHMM): 2205031124
#define  input_Data_uz_pmsm_model_9ph_opti                                 0x180  //data register for Inport input, vector with 4 elements, address ends at 0x18C
#define  input_Strobe_uz_pmsm_model_9ph_opti                               0x190  //strobe register for port input
#define  outputs_Data_uz_pmsm_model_9ph_opti                               0x200  //data register for Outport outputs, vector with 3 elements, address ends at 0x208
#define  outputs_Strobe_uz_pmsm_model_9ph_opti                             0x210  //strobe register for port outputs
#define  i_dq_ps_Data_uz_pmsm_model_9ph_opti                               0x400  //data register for Outport i_dq_ps, vector with 9 elements, address ends at 0x420
#define  i_dq_ps_Strobe_uz_pmsm_model_9ph_opti                             0x440  //strobe register for port i_dq_ps
#define  Model_Parameter_reset_integrators_Data_uz_pmsm_model_9ph_opti     0x100  //data register for Inport Model_Parameter_reset_integrators
#define  Model_Parameter_simulate_mechanical_Data_uz_pmsm_model_9ph_opti   0x104  //data register for Inport Model_Parameter_simulate_mechanical
#define  Model_Parameter_switch_pspl_Data_uz_pmsm_model_9ph_opti           0x108  //data register for Inport Model_Parameter_switch_pspl
#define  Model_Parameter_control_dq_abc_Data_uz_pmsm_model_9ph_opti        0x10C  //data register for Inport Model_Parameter_control_dq_abc
#define  physical_parameters_mu_Data_uz_pmsm_model_9ph_opti                0x110  //data register for Inport physical_parameters_mu
#define  physical_parameters_M_R0_Data_uz_pmsm_model_9ph_opti              0x114  //data register for Inport physical_parameters_M_R0
#define  physical_parameters_1_L_d_Data_uz_pmsm_model_9ph_opti             0x118  //data register for Inport physical_parameters_1_L_d
#define  physical_parameters_1_L_q_Data_uz_pmsm_model_9ph_opti             0x11C  //data register for Inport physical_parameters_1_L_q
#define  physical_parameters_R_1_Data_uz_pmsm_model_9ph_opti               0x120  //data register for Inport physical_parameters_R_1
#define  physical_parameters_1_J_Data_uz_pmsm_model_9ph_opti               0x124  //data register for Inport physical_parameters_1_J
#define  physical_parameters_polepair_Data_uz_pmsm_model_9ph_opti          0x128  //data register for Inport physical_parameters_polepair
#define  physical_parameters_psi_pm_Data_uz_pmsm_model_9ph_opti            0x12C  //data register for Inport physical_parameters_psi_pm
#define  physical_parameters_L_z1_Data_uz_pmsm_model_9ph_opti              0x130  //data register for Inport physical_parameters_L_z1
#define  physical_parameters_L_z2_Data_uz_pmsm_model_9ph_opti              0x134  //data register for Inport physical_parameters_L_z2
#define  physical_parameters_L_x1_Data_uz_pmsm_model_9ph_opti              0x138  //data register for Inport physical_parameters_L_x1
#define  physical_parameters_L_y1_Data_uz_pmsm_model_9ph_opti              0x13C  //data register for Inport physical_parameters_L_y1
#define  physical_parameters_L_x2_Data_uz_pmsm_model_9ph_opti              0x140  //data register for Inport physical_parameters_L_x2
#define  physical_parameters_L_y2_Data_uz_pmsm_model_9ph_opti              0x144  //data register for Inport physical_parameters_L_y2
#define  physical_parameters_L_z3_Data_uz_pmsm_model_9ph_opti              0x148  //data register for Inport physical_parameters_L_z3

#endif /* UZ_PMSM_MODEL_9PH_OPTI_H_ */
