/*
 * File Name:         hdl_prj/ipcore/uz_pmsm_model_v1_0/include/uz_pmsm_model_addr.h
 * Description:       C Header File
 * Created:           2021-07-23 16:46:03
*/

#ifndef UZ_PMSM_MODEL_H_
#define UZ_PMSM_MODEL_H_

#define  IPCore_Reset_uz_pmsm_model               0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_uz_pmsm_model              0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_uz_pmsm_model           0x8  //contains unique IP timestamp (yymmddHHMM): 2401301415
#define  reset_integrators_Data_uz_pmsm_model     0x100  //data register for Inport reset_integrators
#define  simulate_mechanical_Data_uz_pmsm_model   0x104  //data register for Inport simulate_mechanical
#define  simulate_nonlinear_Data_uz_pmsm_model    0x108  //data register for Inport simulate_nonlinear
#define  reciprocal_J_Data_uz_pmsm_model          0x10C  //data register for Inport reciprocal_J
#define  mu_Data_uz_pmsm_model                    0x110  //data register for Inport mu
#define  M_n0_Data_uz_pmsm_model                  0x114  //data register for Inport M_n0
#define  Ld_Data_uz_pmsm_model                    0x118  //data register for Inport Ld
#define  Lq_Data_uz_pmsm_model                    0x11C  //data register for Inport Lq
#define  R1_Data_uz_pmsm_model                    0x120  //data register for Inport R1
#define  polepairs_Data_uz_pmsm_model             0x124  //data register for Inport polepairs
#define  psi_pm_Data_uz_pmsm_model                0x128  //data register for Inport psi_pm
#define  inputs_Data_uz_pmsm_model                0x130  //data register for Inport inputs. Vector with 4 elements. Register is split across a total of 4 addresses, last address is 0x13C.
#define  v_d_Data_uz_pmsm_model                   0x130
#define  v_q_Data_uz_pmsm_model                   0x130+0x4
#define  in_omega_mech_Data_uz_pmsm_model         0x130+0x8
#define  load_torque_Data_uz_pmsm_model           0x130+0xC
#define  inputs_Strobe_uz_pmsm_model              0x140  //strobe register for port inputs
#define  outputs_Data_uz_pmsm_model               0x150  //data register for Outport outputs. Vector with 4 elements. Register is split across a total of 4 addresses, last address is 0x15C.
#define  i_d_Data_uz_pmsm_model                   0x150  // i_d
#define  i_q_Data_uz_pmsm_model                   0x150+0x4 // i_q output, offset by 0x4 due to vector port
#define  torque_Data_uz_pmsm_model                0x150+0x8 // torque data register, offset due to vector port
#define  out_omega_mech_Data_uz_pmsm_model        0x150+0xC // omega mech output signal, offset due to vector port
#define  outputs_Strobe_uz_pmsm_model             0x160  //strobe register for port outputs
#define  fitting_parameter_Data_uz_pmsm_model     0x180  //data register for Inport fitting_parameter. Vector with 23 elements. Register is split across a total of 23 addresses, last address is 0x1D8.
#define  ad1_Data_uz_pmsm_model                   0x180 // ad1 input
#define  ad2_Data_uz_pmsm_model                   0x180+0x4 // offset by 0x4 due to vector port
#define  ad3_Data_uz_pmsm_model                   0x180+0x8 // offset due to vector port
#define  ad4_Data_uz_pmsm_model                   0x180+0xC // offset due to vector port
#define  ad5_Data_uz_pmsm_model                   0x180+0x10 // offset due to vector port
#define  ad6_Data_uz_pmsm_model                   0x180+0x14 // offset due to vector port
#define  aq1_Data_uz_pmsm_model                   0x180+0x18 // offset due to vector port
#define  aq2_Data_uz_pmsm_model                   0x180+0x1C // offset due to vector port
#define  aq3_Data_uz_pmsm_model                   0x180+0x20 // offset due to vector port
#define  aq4_Data_uz_pmsm_model                   0x180+0x24 // offset due to vector port
#define  aq5_Data_uz_pmsm_model                   0x180+0x28 // offset due to vector port
#define  aq6_Data_uz_pmsm_model                   0x180+0x2C // offset due to vector port
#define  reciprocal_F1G1_Data_uz_pmsm_model       0x180+0x30 // offset due to vector port
#define  reciprocal_F2G2_Data_uz_pmsm_model       0x180+0x34 // offset due to vector port
#define  ad4_mul_ad5_Data_uz_pmsm_model           0x180+0x38 // offset due to vector port
#define  ad1_mul_ad2_Data_uz_pmsm_model           0x180+0x3C // offset due to vector port
#define  aq4_mul_aq5_Data_uz_pmsm_model           0x180+0x40 // offset due to vector port
#define  aq1_mul_aq2_Data_uz_pmsm_model           0x180+0x44 // offset due to vector port
#define  aq4_div_aq5_Data_uz_pmsm_model           0x180+0x48 // offset due to vector port
#define  aq1_div_aq2_Data_uz_pmsm_model           0x180+0x4C // offset due to vector port
#define  ad4_div_ad5_Data_uz_pmsm_model           0x180+0x50 // offset due to vector port
#define  ad1_div_ad2_Data_uz_pmsm_model           0x180+0x54 // offset due to vector port
#define  aq3_min_aq6_Data_uz_pmsm_model           0x180+0x58 // offset due to vector port
#define  fitting_parameter_Strobe_uz_pmsm_model   0x200  //strobe register for port fitting_parameter

#endif /* UZ_PMSM_MODEL_H_ */