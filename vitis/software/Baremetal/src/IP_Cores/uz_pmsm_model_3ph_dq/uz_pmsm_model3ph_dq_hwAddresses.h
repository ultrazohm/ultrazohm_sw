/*
 * File Name:         hdl_prj/ipcore/uz_pmsm_model3ph_v1_0/include/uz_pmsm_model3ph_addr.h
 * Description:       C Header File
 * Created:           2021-07-23 16:46:03
*/

#ifndef UZ_PMSM_MODEL_3PH_H_
#define UZ_PMSM_MODEL_3PH_H_

#define  IPCore_Reset_uz_pmsm_model3ph                         0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_uz_pmsm_model3ph                        0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_uz_pmsm_model3ph                     0x8  //contains unique IP timestamp (yymmddHHMM): 2210311014: 2210311018: 2210311020
#define  reset_integrators_Data_uz_pmsm_model3ph               0x100  //data register for Inport reset_integrators
#define  simulate_mechanical_Data_uz_pmsm_model3ph             0x104  //data register for Inport simulate_mechanical
#define  reciprocal_J_Data_uz_pmsm_model3ph                    0x108  //data register for Inport reciprocal_J
#define  mu_Data_uz_pmsm_model3ph                              0x10C  //data register for Inport mu
#define  M_n0_Data_uz_pmsm_model3ph                            0x110  //data register for Inport M_n0
#define  reciprocal_L_d_Data_uz_pmsm_model3ph                  0x114  //data register for Inport reciprocal_L_d
#define  reciprocal_L_q_Data_uz_pmsm_model3ph                  0x118  //data register for Inport reciprocal_L_q
#define  R1_Data_uz_pmsm_model3ph                              0x11C  //data register for Inport R1
#define  polepairs_Data_uz_pmsm_model3ph                       0x120  //data register for Inport polepairs
#define  psi_pm_Data_uz_pmsm_model3ph                          0x124  //data register for Inport psi_pm
#define  use_axi_input_Data_uz_pmsm_model3ph                   0x128  //data register for Inport use_axi_input
#define  inputs_Data_uz_pmsm_model3ph                          0x130  //data register for Inport inputs, vector with 4 elements, address ends at 0x13C
#define  v_d_Data_uz_pmsm_model3ph                             0x130
#define  v_q_Data_uz_pmsm_model3ph                             0x130+0x4
#define  in_omega_mech_Data_uz_pmsm_model3ph                   0x130+0x8
#define  load_torque_Data_uz_pmsm_model3ph                     0x130+0xC
#define  inputs_Strobe_uz_pmsm_model3ph                        0x140  //strobe register for port inputs
#define  outputs_Data_uz_pmsm_model3ph                         0x1A0  //data register for Outport outputs, vector with 5 elements, address ends at 0x1B0
#define  i_d_Data_uz_pmsm_model3ph                             0x1A0  // i_d
#define  i_q_Data_uz_pmsm_model3ph                             0x1A0+0x04 // i_q output, offset by 0x4 due to vector port
#define  torque_Data_uz_pmsm_model3ph                          0x1A0+0x08 // torque data register, offset due to vector port
#define  out_omega_mech_Data_uz_pmsm_model3ph                  0x1A0+0x0C // omega mech output signal, offset due to vector port
#define  theta_el_Data_uz_pmsm_model3ph                        0x1A0+0x10 // theta el output signal, offset due to vector port
#define  outputs_Strobe_uz_pmsm_model3ph                       0x1C0  //strobe register for port outputs
#define  voltage_input_dq_out_axi_fb_Data_uz_pmsm_model3ph     0x280  //data register for Outport voltage_input_dq_out_axi_fb, vector with 2 elements, address ends at 0x284
#define  voltage_input_dq_out_axi_fb_Strobe_uz_pmsm_model3ph   0x288  //strobe register for port voltage_input_dq_out_axi_fb

#endif /* uz_pmsm_model3ph_H_ */
