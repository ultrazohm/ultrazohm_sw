/*
 * File Name:         C:\Users\Philipp\ultrazohm\ultrazohm_sw\ip_cores\uz_pmsm_model_nonlinear_6LUT\hdl_prj\ipcore\uz_pmsm_6LUT_approx_v1_0\include\uz_pmsm_6LUT_approx_addr.h
 * Description:       C Header File
 * Created:           2023-12-12 13:10:45
*/

#ifndef UZ_PMSM_6LUT_APPROX_H_
#define UZ_PMSM_6LUT_APPROX_H_

#define  IPCore_Reset_uz_pmsm_6LUT_approx                          0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_uz_pmsm_6LUT_approx                         0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_uz_pmsm_6LUT_approx                      0x8  //contains unique IP timestamp (yymmddHHMM): 2312121310
#define  reset_integrators_Data_uz_pmsm_6LUT_approx                0x100  //data register for Inport reset_integrators
#define  simulate_mechanical_Data_uz_pmsm_6LUT_approx              0x104  //data register for Inport simulate_mechanical
#define  simulate_nonlinear_Data_uz_pmsm_6LUT_approx               0x108  //data register for Inport simulate_nonlinear
#define  reciprocal_J_Data_uz_pmsm_6LUT_approx                     0x10C  //data register for Inport reciprocal_J
#define  mu_Data_uz_pmsm_6LUT_approx                               0x110  //data register for Inport mu
#define  M_n0_Data_uz_pmsm_6LUT_approx                             0x114  //data register for Inport M_n0
#define  Ld_Data_uz_pmsm_6LUT_approx                               0x118  //data register for Inport Ld
#define  Lq_Data_uz_pmsm_6LUT_approx                               0x11C  //data register for Inport Lq
#define  R1_Data_uz_pmsm_6LUT_approx                               0x120  //data register for Inport R1
#define  polepairs_Data_uz_pmsm_6LUT_approx                        0x124  //data register for Inport polepairs
#define  psi_pm_Data_uz_pmsm_6LUT_approx                           0x128  //data register for Inport psi_pm
#define  inputs_Data_uz_pmsm_6LUT_approx                           0x190  //data register for Inport inputs. Vector with 4 elements. Register is split across a total of 4 addresses, last address is 0x19C.
#define  inputs_Strobe_uz_pmsm_6LUT_approx                         0x1A0  //strobe register for port inputs
#define  outputs_Data_uz_pmsm_6LUT_approx                          0x1B0  //data register for Outport outputs. Vector with 4 elements. Register is split across a total of 4 addresses, last address is 0x1BC.
#define  outputs_Strobe_uz_pmsm_6LUT_approx                        0x1C0  //strobe register for port outputs
#define  fitting_parameters_ad2_Data_uz_pmsm_6LUT_approx           0x12C  //data register for Inport fitting_parameters_ad2
#define  fitting_parameters_ad3_Data_uz_pmsm_6LUT_approx           0x130  //data register for Inport fitting_parameters_ad3
#define  fitting_parameters_ad4_Data_uz_pmsm_6LUT_approx           0x134  //data register for Inport fitting_parameters_ad4
#define  fitting_parameters_ad5_Data_uz_pmsm_6LUT_approx           0x138  //data register for Inport fitting_parameters_ad5
#define  fitting_parameters_ad6_Data_uz_pmsm_6LUT_approx           0x13C  //data register for Inport fitting_parameters_ad6
#define  fitting_parameters_aq1_Data_uz_pmsm_6LUT_approx           0x140  //data register for Inport fitting_parameters_aq1
#define  fitting_parameters_aq2_Data_uz_pmsm_6LUT_approx           0x144  //data register for Inport fitting_parameters_aq2
#define  fitting_parameters_aq3_Data_uz_pmsm_6LUT_approx           0x148  //data register for Inport fitting_parameters_aq3
#define  fitting_parameters_aq4_Data_uz_pmsm_6LUT_approx           0x14C  //data register for Inport fitting_parameters_aq4
#define  fitting_parameters_aq5_Data_uz_pmsm_6LUT_approx           0x150  //data register for Inport fitting_parameters_aq5
#define  fitting_parameters_aq6_Data_uz_pmsm_6LUT_approx           0x154  //data register for Inport fitting_parameters_aq6
#define  fitting_parameters_1_Fid1_Giq1_Data_uz_pmsm_6LUT_approx   0x158  //data register for Inport fitting_parameters_1_Fid1_Giq1
#define  fitting_parameters_1_Fid2_Giq2_Data_uz_pmsm_6LUT_approx   0x15C  //data register for Inport fitting_parameters_1_Fid2_Giq2
#define  fitting_parameters_ad4ad5_Data_uz_pmsm_6LUT_approx        0x160  //data register for Inport fitting_parameters_ad4ad5
#define  fitting_parameters_ad1ad2_Data_uz_pmsm_6LUT_approx        0x164  //data register for Inport fitting_parameters_ad1ad2
#define  fitting_parameters_aq4aq5_Data_uz_pmsm_6LUT_approx        0x168  //data register for Inport fitting_parameters_aq4aq5
#define  fitting_parameters_aq1aq2_Data_uz_pmsm_6LUT_approx        0x16C  //data register for Inport fitting_parameters_aq1aq2
#define  fitting_parameters_aq4_aq5_Data_uz_pmsm_6LUT_approx       0x170  //data register for Inport fitting_parameters_aq4_aq5
#define  fitting_parameters_aq1_aq2_Data_uz_pmsm_6LUT_approx       0x174  //data register for Inport fitting_parameters_aq1_aq2
#define  fitting_parameters_ad4_ad5_Data_uz_pmsm_6LUT_approx       0x178  //data register for Inport fitting_parameters_ad4_ad5
#define  fitting_parameters_ad1_ad2_Data_uz_pmsm_6LUT_approx       0x17C  //data register for Inport fitting_parameters_ad1_ad2
#define  fitting_parameters_ad1_Data_uz_pmsm_6LUT_approx           0x180  //data register for Inport fitting_parameters_ad1
#define  fitting_parameters_aq3_aq6_Data_uz_pmsm_6LUT_approx       0x184  //data register for Inport fitting_parameters_aq3_aq6

#endif /* UZ_PMSM_6LUT_APPROX_H_ */
