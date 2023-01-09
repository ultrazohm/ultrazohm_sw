/*
 * File Name:         C:\Users\valen\Documents\repos\UZ\ultrazohm_sw_pr\ip_cores\uz_pmsm_model_3ph_dq\hdl_prj\ipcore\uz_pmsm_model_3ph_dq_v1_0\include\uz_pmsm_model_3ph_dq_addr.h
 * Description:       C Header File
 * Created:           2023-01-09 10:41:31
*/

#ifndef UZ_PMSM_MODEL_3PH_DQ_H_
#define UZ_PMSM_MODEL_3PH_DQ_H_

#define  IPCore_Reset_uz_pmsm_model_3ph_dq                         0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_uz_pmsm_model_3ph_dq                        0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_uz_pmsm_model_3ph_dq                     0x8  //contains unique IP timestamp (yymmddHHMM): 2301091041
#define  reset_integrators_Data_uz_pmsm_model_3ph_dq               0x100  //data register for Inport reset_integrators
#define  simulate_mechanical_Data_uz_pmsm_model_3ph_dq             0x104  //data register for Inport simulate_mechanical
#define  reciprocal_J_Data_uz_pmsm_model_3ph_dq                    0x108  //data register for Inport reciprocal_J
#define  mu_Data_uz_pmsm_model_3ph_dq                              0x10C  //data register for Inport mu
#define  M_n0_Data_uz_pmsm_model_3ph_dq                            0x110  //data register for Inport M_n0
#define  reciprocal_L_d_Data_uz_pmsm_model_3ph_dq                  0x114  //data register for Inport reciprocal_L_d
#define  reciprocal_L_q_Data_uz_pmsm_model_3ph_dq                  0x118  //data register for Inport reciprocal_L_q
#define  R1_Data_uz_pmsm_model_3ph_dq                              0x11C  //data register for Inport R1
#define  polepairs_Data_uz_pmsm_model_3ph_dq                       0x120  //data register for Inport polepairs
#define  psi_pm_Data_uz_pmsm_model_3ph_dq                          0x124  //data register for Inport psi_pm
#define  use_axi_input_Data_uz_pmsm_model_3ph_dq                   0x128  //data register for Inport use_axi_input
#define  inputs_Data_uz_pmsm_model_3ph_dq                          0x130  //data register for Inport inputs, vector with 4 elements, address ends at 0x13C
#define  inputs_Strobe_uz_pmsm_model_3ph_dq                        0x140  //strobe register for port inputs
#define  outputs_Data_uz_pmsm_model_3ph_dq                         0x1A0  //data register for Outport outputs, vector with 5 elements, address ends at 0x1B0
#define  outputs_Strobe_uz_pmsm_model_3ph_dq                       0x1C0  //strobe register for port outputs
#define  voltage_input_dq_out_axi_fb_Data_uz_pmsm_model_3ph_dq     0x280  //data register for Outport voltage_input_dq_out_axi_fb, vector with 2 elements, address ends at 0x284
#define  voltage_input_dq_out_axi_fb_Strobe_uz_pmsm_model_3ph_dq   0x288  //strobe register for port voltage_input_dq_out_axi_fb

#endif /* UZ_PMSM_MODEL_3PH_DQ_H_ */
