/*
 * File Name:         C:\Users\valen\Documents\repos\UZ\ultrazohm_sw_working\ip_cores\uz_pmsm_model_9ph\hdl_prj\ipcore\uz_pmsm_model_9ph_v1_0\include\uz_pmsm_model_9ph_addr.h
 * Description:       C Header File
 * Created:           2021-03-31 13:59:23
*/

#ifndef UZ_PMSM_MODEL_9PH_H_
#define UZ_PMSM_MODEL_9PH_H_

// Automated stuff
#define  IPCore_Reset_uz_pmsm_model_9ph                               0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_uz_pmsm_model_9ph                              0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_uz_pmsm_model_9ph                           0x8  //contains unique IP timestamp (yymmddHHMM): 2103311359

// Inputs general
#define  inputs_general_Data_uz_pmsm_model_9ph                        0x180  //data register for Inport inputs, vector with 2 elements, address ends at 0x184
#define  load_torque_Data_uz_pmsm_model_9ph                           0x180+0x00
#define  in_omega_mech_Data_uz_pmsm_model_9ph                         0x180+0x04
#define  inputs_general_Strobe_uz_pmsm_model_9ph                      0x188  //strobe register for port inputs

// Outputs general
#define  output_general_Data_uz_pmsm_model_9ph                        0x200  //data register for Outport outputs, vector with 5 elements, address ends at 0x210
#define  torque_Data_uz_pmsm_model_9ph                                0x200+0x00 // torque data register, offset due to vector port
#define  out_omega_mech_Data_uz_pmsm_model_9ph                        0x200+0x04 // omega mech output signal, offset due to vector port
#define  out_theta_el_Data_uz_pmsm_model_9ph                          0x200+0x08
#define  u_d_Data_uz_pmsm_model_9ph                                   0x200+0x0C 
#define  u_q_Data_uz_pmsm_model_9ph                                   0x200+0x10 
#define  output_general_Strobe_uz_pmsm_model_9ph                      0x220  //strobe register for port outputs

// Outputs currents dq
#define  output_currents_dq_Data_uz_pmsm_model_9ph                    0x400  //data register for Outport currents_dq, vector with 9 elements, address ends at 0x260
#define  i_a1_Data_uz_pmsm_model_9ph                                  0x400+0x00 
#define  i_b1_Data_uz_pmsm_model_9ph                                  0x400+0x04 
#define  i_c1_Data_uz_pmsm_model_9ph                                  0x400+0x08 
#define  i_a2_Data_uz_pmsm_model_9ph                                  0x400+0x0C 
#define  i_b2_Data_uz_pmsm_model_9ph                                  0x400+0x10 
#define  i_c2_Data_uz_pmsm_model_9ph                                  0x400+0x14
#define  i_a3_Data_uz_pmsm_model_9ph                                  0x400+0x18 
#define  i_b3_Data_uz_pmsm_model_9ph                                  0x400+0x1C
#define  i_c3_Data_uz_pmsm_model_9ph                                  0x400+0x20
#define  output_currents_Strobe_uz_pmsm_model_9ph                  0x440  //strobe register for port currents_dq

// Model parameter
#define  Model_Parameter_reset_integrators_Data_uz_pmsm_model_9ph     0x100  //data register for Inport Model_Parameter_reset_integrators
#define  Model_Parameter_simulate_mechanical_Data_uz_pmsm_model_9ph   0x104  //data register for Inport Model_Parameter_simulate_mechanical
#define  Model_Parameter_switch_pspl_Data_uz_pmsm_model_9ph           0x108  //data register for Inport Model_Parameter_switch_pspl
#define  Model_Parameter_control_dq_abc_Data_uz_pmsm_model_9ph        0x10C  //data register for Inport Model_Parameter_control_dq_abc

// Physical parameter
#define  Physical_Parameter_mu_Data_uz_pmsm_model_9ph                 0x110  //data register for Inport Physical_Parameter_mu
#define  Physical_Parameter_M_R0_Data_uz_pmsm_model_9ph               0x114 //data register for Inport Physical_Parameter_M_n0
#define  Physical_Parameter_reciprocal_L_d_Data_uz_pmsm_model_9ph     0x118  //data register for Inport Physical_Parameter_reciprocal_L_d
#define  Physical_Parameter_reciprocal_L_q_Data_uz_pmsm_model_9ph     0x11C  //data register for Inport Physical_Parameter_reciprocal_L_q
#define  Physical_Parameter_R1_Data_uz_pmsm_model_9ph                 0x120  //data register for Inport Physical_Parameter_R1
#define  Physical_Parameter_1_J_Data_uz_pmsm_model_9ph			      0x124  //data register for Inport Physical_Parameter_reciprocal_J
#define  Physical_Parameter_polepairs_Data_uz_pmsm_model_9ph          0x128  //data register for Inport Physical_Parameter_polepairs
#define  Physical_Parameter_psi_pm_Data_uz_pmsm_model_9ph             0x12C  //data register for Inport Physical_Parameter_psi_pm
#define  Physical_Parameter_L_z1_Data_uz_pmsm_model_9ph               0x130  //data register for Inport Physical_Parameter_L_o1
#define  Physical_Parameter_L_z2_Data_uz_pmsm_model_9ph               0x134  //data register for Inport Physical_Parameter_L_o2
#define  Physical_Parameter_L_x1_Data_uz_pmsm_model_9ph               0x138  //data register for Inport Physical_Parameter_L_x1
#define  Physical_Parameter_L_y1_Data_uz_pmsm_model_9ph               0x13C  //data register for Inport Physical_Parameter_L_y1
#define  Physical_Parameter_L_x2_Data_uz_pmsm_model_9ph               0x140  //data register for Inport Physical_Parameter_L_x2
#define  Physical_Parameter_L_y2_Data_uz_pmsm_model_9ph               0x144  //data register for Inport Physical_Parameter_L_y2
#define  Physical_Parameter_L_z3_Data_uz_pmsm_model_9ph               0x148  //data register for Inport Physical_Parameter_L_zero

#endif /* UZ_PMSM_MODEL_9PH_H_ */