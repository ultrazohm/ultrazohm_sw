/*
 * File Name:         hdl_prj\ipcore\uz_pmsm_model_6ph_dqxy_v1_0\include\uz_pmsm_model_6ph_dqxy_addr.h
 * Description:       C Header File
 * Created:           2026-01-21 15:31:16
*/

#ifndef UZ_PMSM_MODEL_6PH_DQXY_H_
#define UZ_PMSM_MODEL_6PH_DQXY_H_

#define  IPCore_Reset_uz_pmsm_model_6ph_dqxy               0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_uz_pmsm_model_6ph_dqxy              0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_uz_pmsm_model_6ph_dqxy           0x8  //contains unique IP timestamp (yymmddHHMM): 2601211531
#define  reset_integrators_Data_uz_pmsm_model_6ph_dqxy     0x100  //data register for Inport reset_integrators
#define  simulate_mechanical_Data_uz_pmsm_model_6ph_dqxy   0x104  //data register for Inport simulate_mechanical
#define  reciprocal_J_Data_uz_pmsm_model_6ph_dqxy          0x108  //data register for Inport reciprocal_J
#define  mu_Data_uz_pmsm_model_6ph_dqxy                    0x10C  //data register for Inport mu
#define  M_n0_Data_uz_pmsm_model_6ph_dqxy                  0x110  //data register for Inport M_n0
#define  reciprocal_L_d_Data_uz_pmsm_model_6ph_dqxy        0x114  //data register for Inport reciprocal_L_d
#define  reciprocal_L_q_Data_uz_pmsm_model_6ph_dqxy        0x118  //data register for Inport reciprocal_L_q
#define  R1_Data_uz_pmsm_model_6ph_dqxy                    0x11C  //data register for Inport R1
#define  polepairs_Data_uz_pmsm_model_6ph_dqxy             0x120  //data register for Inport polepairs
#define  psi_pm_Data_uz_pmsm_model_6ph_dqxy                0x124  //data register for Inport psi_pm
#define  reciprocal_L_x_Data_uz_pmsm_model_6ph_dqxy        0x128  //data register for Inport reciprocal_L_x
#define  reciprocal_L_y_Data_uz_pmsm_model_6ph_dqxy        0x12C  //data register for Inport reciprocal_L_y
#define  inputs_Data_uz_pmsm_model_6ph_dqxy                0x140  //data register for Inport inputs. Vector with 6 elements. Register is split across a total of 6 addresses, last address is 0x154.
#define  inputs_Strobe_uz_pmsm_model_6ph_dqxy              0x160  //strobe register for port inputs
#define  outputs_Data_uz_pmsm_model_6ph_dqxy               0x180  //data register for Outport outputs. Vector with 6 elements. Register is split across a total of 6 addresses, last address is 0x194.
#define  outputs_Strobe_uz_pmsm_model_6ph_dqxy             0x1A0  //strobe register for port outputs

#endif /* UZ_PMSM_MODEL_6PH_DQXY_H_ */
