/*
 * File Name:         hdl_prj/ipcore/uz_pmsm_model_v1_0/include/uz_pmsm_model_addr.h
 * Description:       C Header File
 * Created:           2021-07-23 16:46:03
*/

#ifndef UZ_PMSM_MODEL_H_
#define UZ_PMSM_MODEL_H_

#define  IPCore_Reset_uz_pmsm_model                       0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_uz_pmsm_model                      0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_uz_pmsm_model                   0x8  //contains unique IP timestamp (yymmddHHMM): 2401251612
#define  reset_integrators_Data_uz_pmsm_model             0x100  //data register for Inport reset_integrators
#define  simulate_mechanical_Data_uz_pmsm_model           0x104  //data register for Inport simulate_mechanical
#define  simulate_nonlinear_Data_uz_pmsm_model            0x108  //data register for Inport simulate_nonlinear
#define  reciprocal_J_Data_uz_pmsm_model                  0x10C  //data register for Inport reciprocal_J
#define  mu_Data_uz_pmsm_model                            0x110  //data register for Inport mu
#define  M_n0_Data_uz_pmsm_model                          0x114  //data register for Inport M_n0
#define  Ld_Data_uz_pmsm_model                            0x118  //data register for Inport Ld
#define  Lq_Data_uz_pmsm_model                            0x11C  //data register for Inport Lq
#define  R1_Data_uz_pmsm_model                            0x120  //data register for Inport R1
#define  polepairs_Data_uz_pmsm_model                     0x124  //data register for Inport polepairs
#define  psi_pm_Data_uz_pmsm_model                        0x128  //data register for Inport psi_pm
#define  inputs_Data_uz_pmsm_model                        0x130  //data register for Inport inputs. Vector with 4 elements. Register is split across a total of 4 addresses, last address is 0x13C.
#define  v_d_Data_uz_pmsm_model                           0x130
#define  v_q_Data_uz_pmsm_model                           0x130+0x4
#define  in_omega_mech_Data_uz_pmsm_model                 0x130+0x8
#define  load_torque_Data_uz_pmsm_model                   0x130+0xC
#define  inputs_Strobe_uz_pmsm_model                      0x140  //strobe register for port inputs
#define  outputs_Data_uz_pmsm_model                       0x150  //data register for Outport outputs. Vector with 4 elements. Register is split across a total of 4 addresses, last address is 0x15C.
#define  i_d_Data_uz_pmsm_model                           0x150  // i_d
#define  i_q_Data_uz_pmsm_model                           0x150+0x4 // i_q output, offset by 0x4 due to vector port
#define  torque_Data_uz_pmsm_model                        0x150+0x8 // torque data register, offset due to vector port
#define  out_omega_mech_Data_uz_pmsm_model                0x150+0xC // omega mech output signal, offset due to vector port
#define  outputs_Strobe_uz_pmsm_model                     0x160  //strobe register for port outputs
#define  ad1_Data_uz_pmsm_model                           0x180  //data register for Inport ad1
#define  ad2_Data_uz_pmsm_model                           0x184  //data register for Inport ad2
#define  ad3_Data_uz_pmsm_model                           0x188  //data register for Inport ad3
#define  ad4_Data_uz_pmsm_model                           0x18C  //data register for Inport ad4
#define  ad5_Data_uz_pmsm_model                           0x190  //data register for Inport ad5
#define  ad6_Data_uz_pmsm_model                           0x194  //data register for Inport ad6
#define  aq1_Data_uz_pmsm_model                           0x198  //data register for Inport aq1
#define  aq2_Data_uz_pmsm_model                           0x19C  //data register for Inport aq2
#define  aq3_Data_uz_pmsm_model                           0x1A0  //data register for Inport aq3
#define  aq4_Data_uz_pmsm_model                           0x1A4  //data register for Inport aq4
#define  aq5_Data_uz_pmsm_model                           0x1A8  //data register for Inport aq5
#define  aq6_Data_uz_pmsm_model                           0x1AC  //data register for Inport aq6
#define  reciprocal_F1G1_Data_uz_pmsm_model               0x1B0  //data register for Inport reciprocal_F1G1
#define  reciprocal_F2G2_Data_uz_pmsm_model               0x1B4  //data register for Inport reciprocal_F2G2
#define  ad4_mul_ad5_Data_uz_pmsm_model                   0x1B8  //data register for Inport ad4_mul_ad5
#define  ad1_mul_ad2_Data_uz_pmsm_model                   0x1BC  //data register for Inport ad1_mul_ad2
#define  aq4_mul_aq5_Data_uz_pmsm_model                   0x1C0  //data register for Inport aq4_mul_aq5
#define  aq1_mul_aq2_Data_uz_pmsm_model                   0x1C4  //data register for Inport aq1_mul_aq2
#define  aq4_div_aq5_Data_uz_pmsm_model                   0x1C8  //data register for Inport aq4_div_aq5
#define  aq1_div_aq2_Data_uz_pmsm_model                   0x1CC  //data register for Inport aq1_div_aq2
#define  ad4_div_ad5_Data_uz_pmsm_model                   0x1D0  //data register for Inport ad4_div_ad5
#define  ad1_div_ad2_Data_uz_pmsm_model                   0x1D4  //data register for Inport ad1_div_ad2
#define  aq3_min_aq6_Data_uz_pmsm_model                   0x1D8  //data register for Inport aq3_min_aq6
#define  outputs_fitting_parameter_Data_uz_pmsm_model     0x200  //data register for Outport outputs_fitting_parameter. Vector with 23 elements. Register is split across a total of 23 addresses, last address is 0x258.
#define  out_ad1_Data_uz_pmsm_model                       0x200  //data register for Inport ad1
#define  out_ad2_Data_uz_pmsm_model                       0x200+0x4 //data register for Inport ad2
#define  out_ad3_Data_uz_pmsm_model                       0x200+0x8    //data register for Inport ad3
#define  out_ad4_Data_uz_pmsm_model                       0x200+0xC    //data register for Inport ad4
#define  out_ad5_Data_uz_pmsm_model                       0x200+0x10   //data register for Inport ad5
#define  out_ad6_Data_uz_pmsm_model                       0x200+0x14   //data register for Inport ad6
#define  out_aq1_Data_uz_pmsm_model                       0x200+0x18   //data register for Inport aq1
#define  out_aq2_Data_uz_pmsm_model                       0x200+0x1C   //data register for Inport aq2
#define  out_aq3_Data_uz_pmsm_model                       0x200+0x20   //data register for Inport aq3
#define  out_aq4_Data_uz_pmsm_model                       0x200+0x24   //data register for Inport aq4
#define  out_aq5_Data_uz_pmsm_model                       0x200+0x28   //data register for Inport aq5
#define  out_aq6_Data_uz_pmsm_model                       0x200+0x2C   //data register for Inport aq6
#define  out_reciprocal_F1G1_Data_uz_pmsm_model           0x200+0x30   //data register for Inport reciprocal_F1G1
#define  out_reciprocal_F2G2_Data_uz_pmsm_model           0x200+0x34   //data register for Inport reciprocal_F2G2
#define  out_ad4_mul_ad5_Data_uz_pmsm_model               0x200+0x38   //data register for Inport ad4_mul_ad5
#define  out_ad1_mul_ad2_Data_uz_pmsm_model               0x200+0x3C   //data register for Inport ad1_mul_ad2
#define  out_aq4_mul_aq5_Data_uz_pmsm_model               0x200+0x40   //data register for Inport aq4_mul_aq5
#define  out_aq1_mul_aq2_Data_uz_pmsm_model               0x200+0x44   //data register for Inport aq1_mul_aq2
#define  out_aq4_div_aq5_Data_uz_pmsm_model               0x200+0x48   //data register for Inport aq4_div_aq5
#define  out_aq1_div_aq2_Data_uz_pmsm_model               0x200+0x4C   //data register for Inport aq1_div_aq2
#define  out_ad4_div_ad5_Data_uz_pmsm_model               0x200+0x50   //data register for Inport ad4_div_ad5
#define  out_ad1_div_ad2_Data_uz_pmsm_model               0x200+0x54   //data register for Inport ad1_div_ad2
#define  out_aq3_min_aq6_Data_uz_pmsm_model               0x200+0x58   //data register for Inport aq3_min_aq6
#define  outputs_fitting_parameter_Strobe_uz_pmsm_model   0x280  //strobe register for port outputs_fitting_parameter

#endif /* UZ_PMSM_MODEL_H_ */







//OLD Defines (still here for naming)
// #define  IPCore_Reset_uz_pmsm_model               0x0  //write 0x1 to bit 0 to reset IP core
// #define  IPCore_Enable_uz_pmsm_model              0x4  //enabled (by default) when bit 0 is 0x1
// #define  IPCore_Timestamp_uz_pmsm_model           0x8  //contains unique IP timestamp (yymmddHHMM): 2107231645
// #define  reset_integrators_Data_uz_pmsm_model     0x100  //data register for Inport reset_integrators
// #define  simulate_mechanical_Data_uz_pmsm_model   0x104  //data register for Inport simulate_mechanical
// #define  reciprocal_J_Data_uz_pmsm_model          0x108  //data register for Inport reciprocal_J
// #define  mu_Data_uz_pmsm_model                    0x10C  //data register for Inport mu
// #define  M_n0_Data_uz_pmsm_model                  0x110  //data register for Inport M_n0
// #define  reciprocal_L_d_Data_uz_pmsm_model        0x114  //data register for Inport reciprocal_L_d
// #define  reciprocal_L_q_Data_uz_pmsm_model        0x118  //data register for Inport reciprocal_L_q
// #define  R1_Data_uz_pmsm_model                    0x11C  //data register for Inport R1
// #define  polepairs_Data_uz_pmsm_model             0x120  //data register for Inport polepairs
// #define  psi_pm_Data_uz_pmsm_model                0x124  //data register for Inport psi_pm

