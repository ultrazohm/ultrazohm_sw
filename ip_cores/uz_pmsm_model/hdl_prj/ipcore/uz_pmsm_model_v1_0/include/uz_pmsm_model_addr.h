/*
 * File Name:         hdl_prj\ipcore\uz_pmsm_model_v1_0\include\uz_pmsm_model_addr.h
 * Description:       C Header File
 * Created:           2024-05-23 13:51:12
*/

#ifndef UZ_PMSM_MODEL_H_
#define UZ_PMSM_MODEL_H_

#define  IPCore_Reset_uz_pmsm_model               0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_uz_pmsm_model              0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_uz_pmsm_model           0x8  //contains unique IP timestamp (yymmddHHMM): 2405231350
#define  reset_integrators_Data_uz_pmsm_model     0x100  //data register for Inport reset_integrators
#define  simulate_mechanical_Data_uz_pmsm_model   0x104  //data register for Inport simulate_mechanical
#define  simulate_nonlinear_Data_uz_pmsm_model    0x108  //data register for Inport simulate_nonlinear
#define  reciprocal_J_Data_uz_pmsm_model          0x10C  //data register for Inport reciprocal_J
#define  mu_Data_uz_pmsm_model                    0x110  //data register for Inport mu
#define  M_n0_Data_uz_pmsm_model                  0x114  //data register for Inport M_n0
#define  L_d_Data_uz_pmsm_model                   0x118  //data register for Inport L_d
#define  L_q_Data_uz_pmsm_model                   0x11C  //data register for Inport L_q
#define  R1_Data_uz_pmsm_model                    0x120  //data register for Inport R1
#define  polepairs_Data_uz_pmsm_model             0x124  //data register for Inport polepairs
#define  psi_pm_Data_uz_pmsm_model                0x128  //data register for Inport psi_pm
#define  inputs_Data_uz_pmsm_model                0x130  //data register for Inport inputs. Vector with 4 elements. Register is split across a total of 4 addresses, last address is 0x13C.
#define  inputs_Strobe_uz_pmsm_model              0x140  //strobe register for port inputs
#define  outputs_Data_uz_pmsm_model               0x150  //data register for Outport outputs. Vector with 4 elements. Register is split across a total of 4 addresses, last address is 0x15C.
#define  outputs_Strobe_uz_pmsm_model             0x160  //strobe register for port outputs
#define  fitting_parameter_Data_uz_pmsm_model     0x180  //data register for Inport fitting_parameter. Vector with 23 elements. Register is split across a total of 23 addresses, last address is 0x1D8.
#define  fitting_parameter_Strobe_uz_pmsm_model   0x200  //strobe register for port fitting_parameter

#endif /* UZ_PMSM_MODEL_H_ */
