/*
 * File Name:         hdl_prj/ipcore/uz_pmsm_model_v1_0/include/uz_pmsm_model_addr.h
 * Description:       C Header File
 * Created:           2021-07-08 22:13:44
*/

#ifndef UZ_PMSM_MODEL_H_
#define UZ_PMSM_MODEL_H_

#define  IPCore_Reset_uz_pmsm_model               0x0U  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_uz_pmsm_model              0x4U  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_uz_pmsm_model           0x8U  //contains unique IP timestamp (yymmddHHMM): 2107082213
#define  input_signals_Data_uz_pmsm_model         0x100U  //data register for Inport input_signals, vector with 4 elements, address ends at 0x10C
#define  input_signals_Strobe_uz_pmsm_model       0x110U  //strobe register for port input_signals
#define  u_d_Data_uz_pmsm_model                   0x100U  //data register for Inport u_d
#define  u_q_Data_uz_pmsm_model                   0x104U  //data register for Inport u_q
#define  load_torque_Data_uz_pmsm_model           0x108U  //data register for Inport load_torque
#define  in_omega_mech_Data_uz_pmsm_model         0x10CU  //data register for Inport in_omega_mech
#define  reset_integrators_Data_uz_pmsm_model     0x114U  //data register for Inport reset_integrators
#define  simulate_mechanical_Data_uz_pmsm_model   0x118U  //data register for Inport simulate_mechanical
#define  reciprocal_J_Data_uz_pmsm_model          0x11CU  //data register for Inport reciprocal_J
#define  mu_Data_uz_pmsm_model                    0x120U  //data register for Inport mu
#define  M_n0_Data_uz_pmsm_model                  0x124U  //data register for Inport M_n0
#define  reciprocal_L_d_Data_uz_pmsm_model        0x128U  //data register for Inport reciprocal_L_d
#define  reciprocal_L_q_Data_uz_pmsm_model        0x12CU  //data register for Inport reciprocal_L_q
#define  R1_Data_uz_pmsm_model                    0x130U  //data register for Inport R1
#define  polepairs_Data_uz_pmsm_model             0x134U  //data register for Inport polepairs
#define  psi_pm_Data_uz_pmsm_model                0x138U  //data register for Inport psi_pm
#define  output_signals_Data_uz_pmsm_model        0x140U  //data register for Outport output_signals, vector with 4 elements, address ends at 0x14C
#define  output_signals_Strobe_uz_pmsm_model      0x150U  //strobe register for port output_signals
#define  i_d_Data_uz_pmsm_model                   0x140U  //data register for Outport i_d
#define  i_q_Data_uz_pmsm_model                   0x144U  //data register for Outport i_q
#define  torque_Data_uz_pmsm_model                0x148U  //data register for Outport torque
#define  omega_mech_Data_uz_pmsm_model            0x14CU  //data register for Outport omega_mech
#endif /* UZ_PMSM_MODEL_H_ */
