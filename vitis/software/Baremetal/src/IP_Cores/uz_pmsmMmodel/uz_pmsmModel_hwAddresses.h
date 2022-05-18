/*
 * File Name:         hdl_prj/ipcore/uz_pmsm_model_v1_0/include/uz_pmsm_model_addr.h
 * Description:       C Header File
 * Created:           2021-07-23 16:46:03
*/

#ifndef UZ_PMSM_MODEL_H_
#define UZ_PMSM_MODEL_H_

#define  IPCore_Reset_uz_pmsm_model               0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_uz_pmsm_model              0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_uz_pmsm_model           0x8  //contains unique IP timestamp (yymmddHHMM): 2107231645
#define  reset_integrators_Data_uz_pmsm_model     0x100  //data register for Inport reset_integrators
#define  simulate_mechanical_Data_uz_pmsm_model   0x104  //data register for Inport simulate_mechanical
#define  reciprocal_J_Data_uz_pmsm_model          0x108  //data register for Inport reciprocal_J
#define  mu_Data_uz_pmsm_model                    0x10C  //data register for Inport mu
#define  M_n0_Data_uz_pmsm_model                  0x110  //data register for Inport M_n0
#define  reciprocal_L_d_Data_uz_pmsm_model        0x114  //data register for Inport reciprocal_L_d
#define  reciprocal_L_q_Data_uz_pmsm_model        0x118  //data register for Inport reciprocal_L_q
#define  R1_Data_uz_pmsm_model                    0x11C  //data register for Inport R1
#define  polepairs_Data_uz_pmsm_model             0x120  //data register for Inport polepairs
#define  psi_pm_Data_uz_pmsm_model                0x124  //data register for Inport psi_pm
#define  inputs_Data_uz_pmsm_model                0x130  //data register for Inport inputs, vector with 4 elements, address ends at 0x13C
#define v_d_Data_uz_pmsm_model                    0x130
#define v_q_Data_uz_pmsm_model                    0x130+0x4
#define in_omega_mech_Data_uz_pmsm_model          0x130+0x8
#define load_torque_Data_uz_pmsm_model            0x130+0xC
#define  inputs_Strobe_uz_pmsm_model              0x140  //strobe register for port inputs
#define  outputs_Data_uz_pmsm_model               0x150  //data register for Outport outputs, vector with 4 elements, address ends at 0x15C
#define i_d_Data_uz_pmsm_model                    0x150  // i_d
#define i_q_Data_uz_pmsm_model                    0x150+0x4 // i_q output, offset by 0x4 due to vector port
#define torque_Data_uz_pmsm_model                 0x150+0x8 // torque data register, offset due to vector port
#define out_omega_mech_Data_uz_pmsm_model         0x150+0xC // omega mech output signal, offset due to vector port
#define  outputs_Strobe_uz_pmsm_model             0x160  //strobe register for port outputs

#endif /* UZ_PMSM_MODEL_H_ */
