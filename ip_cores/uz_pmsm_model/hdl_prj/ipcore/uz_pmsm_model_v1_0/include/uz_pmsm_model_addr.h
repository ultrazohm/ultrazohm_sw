/*
 * File Name:         hdl_prj/ipcore/uz_pmsm_model_v1_0/include/uz_pmsm_model_addr.h
 * Description:       C Header File
 * Created:           2021-07-23 14:37:04
*/

#ifndef UZ_PMSM_MODEL_H_
#define UZ_PMSM_MODEL_H_

#define  IPCore_Reset_uz_pmsm_model               0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_uz_pmsm_model              0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_uz_pmsm_model           0x8  //contains unique IP timestamp (yymmddHHMM): 2107231428: 2107231433: 2107231437
#define  simulate_mechanical_Data_uz_pmsm_model   0x100  //data register for Inport simulate_mechanical
#define  reciprocal_J_Data_uz_pmsm_model          0x104  //data register for Inport reciprocal_J
#define  reset_integrators_Data_uz_pmsm_model     0x108  //data register for Inport reset_integrators
#define  mu_Data_uz_pmsm_model                    0x10C  //data register for Inport mu
#define  reciprocal_L_d_Data_uz_pmsm_model        0x110  //data register for Inport reciprocal_L_d
#define  reciprocal_L_q_Data_uz_pmsm_model        0x114  //data register for Inport reciprocal_L_q
#define  M_n0_Data_uz_pmsm_model                  0x118  //data register for Inport M_n0
#define  R1_Data_uz_pmsm_model                    0x11C  //data register for Inport R1
#define  polepairs_Data_uz_pmsm_model             0x120  //data register for Inport polepairs
#define  psi_pm_Data_uz_pmsm_model                0x124  //data register for Inport psi_pm
#define  u_d_Data_uz_pmsm_model                   0x128  //data register for Inport u_d
#define  u_q_Data_uz_pmsm_model                   0x12C  //data register for Inport u_q
#define  in_omega_mech_Data_uz_pmsm_model         0x130  //data register for Inport in_omega_mech
#define  load_torque_Data_uz_pmsm_model           0x134  //data register for Inport load_torque
#define  i_d_Data_uz_pmsm_model                   0x138  //data register for Outport i_d
#define  i_q_Data_uz_pmsm_model                   0x13C  //data register for Outport i_q
#define  torque_Data_uz_pmsm_model                0x140  //data register for Outport torque
#define  out_omega_mech_Data_uz_pmsm_model        0x144  //data register for Outport out_omega_mech

#endif /* UZ_PMSM_MODEL_H_ */
