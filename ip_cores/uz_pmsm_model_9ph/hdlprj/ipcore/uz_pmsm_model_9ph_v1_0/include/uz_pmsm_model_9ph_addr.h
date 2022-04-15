/*
 * File Name:         C:\Users\valen\Documents\repos\UZ\ultrazohm_sw\ip_cores\uz_pmsm_model_9ph\hdlprj\ipcore\uz_pmsm_model_9ph_v1_0\include\uz_pmsm_model_9ph_addr.h
 * Description:       C Header File
 * Created:           2022-04-15 14:19:50
*/

#ifndef UZ_PMSM_MODEL_9PH_H_
#define UZ_PMSM_MODEL_9PH_H_

#define  IPCore_Reset_uz_pmsm_model_9ph                              0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_uz_pmsm_model_9ph                             0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_uz_pmsm_model_9ph                          0x8  //contains unique IP timestamp (yymmddHHMM): 2204151419
#define  inputs_general_Data_uz_pmsm_model_9ph                       0x180  //data register for Inport inputs_general, vector with 2 elements, address ends at 0x184
#define  inputs_general_Strobe_uz_pmsm_model_9ph                     0x188  //strobe register for port inputs_general
#define  input_voltages_dq_Data_uz_pmsm_model_9ph                    0x1C0  //data register for Inport input_voltages_dq, vector with 9 elements, address ends at 0x1E0
#define  input_voltages_dq_Strobe_uz_pmsm_model_9ph                  0x200  //strobe register for port input_voltages_dq
#define  input_voltages_abc_Data_uz_pmsm_model_9ph                   0x240  //data register for Inport input_voltages_abc, vector with 9 elements, address ends at 0x260
#define  input_voltages_abc_Strobe_uz_pmsm_model_9ph                 0x280  //strobe register for port input_voltages_abc
#define  output_general_Data_uz_pmsm_model_9ph                       0x2A0  //data register for Outport output_general, vector with 5 elements, address ends at 0x2B0
#define  output_general_Strobe_uz_pmsm_model_9ph                     0x2C0  //strobe register for port output_general
#define  output_currents_dq_Data_uz_pmsm_model_9ph                   0x300  //data register for Outport output_currents_dq, vector with 9 elements, address ends at 0x320
#define  output_currents_dq_Strobe_uz_pmsm_model_9ph                 0x340  //strobe register for port output_currents_dq
#define  output_currents_abc_Data_uz_pmsm_model_9ph                  0x380  //data register for Outport output_currents_abc, vector with 9 elements, address ends at 0x3A0
#define  output_currents_abc_Strobe_uz_pmsm_model_9ph                0x3C0  //strobe register for port output_currents_abc
#define  Model_Parameter_reset_integrators_Data_uz_pmsm_model_9ph    0x100  //data register for Inport Model_Parameter_reset_integrators
#define  Model_Parameter_simulate_mechanics_Data_uz_pmsm_model_9ph   0x104  //data register for Inport Model_Parameter_simulate_mechanics
#define  Model_Parameter_switch_pspl_Data_uz_pmsm_model_9ph          0x108  //data register for Inport Model_Parameter_switch_pspl
#define  Model_Parameter_control_dq_abc_Data_uz_pmsm_model_9ph       0x10C  //data register for Inport Model_Parameter_control_dq_abc
#define  Physical_Parameter_1_J_Data_uz_pmsm_model_9ph               0x110  //data register for Inport Physical_Parameter_1_J
#define  Physical_Parameter_mu_Data_uz_pmsm_model_9ph                0x114  //data register for Inport Physical_Parameter_mu
#define  Physical_Parameter_M_R0_Data_uz_pmsm_model_9ph              0x118  //data register for Inport Physical_Parameter_M_R0
#define  Physical_Parameter_1_L_d_Data_uz_pmsm_model_9ph             0x11C  //data register for Inport Physical_Parameter_1_L_d
#define  Physical_Parameter_1_L_q_Data_uz_pmsm_model_9ph             0x120  //data register for Inport Physical_Parameter_1_L_q
#define  Physical_Parameter_R_1_Data_uz_pmsm_model_9ph               0x124  //data register for Inport Physical_Parameter_R_1
#define  Physical_Parameter_polepair_Data_uz_pmsm_model_9ph          0x128  //data register for Inport Physical_Parameter_polepair
#define  Physical_Parameter_psi_pm_Data_uz_pmsm_model_9ph            0x12C  //data register for Inport Physical_Parameter_psi_pm
#define  Physical_Parameter_L_o1_Data_uz_pmsm_model_9ph              0x130  //data register for Inport Physical_Parameter_L_o1
#define  Physical_Parameter_L_o2_Data_uz_pmsm_model_9ph              0x134  //data register for Inport Physical_Parameter_L_o2
#define  Physical_Parameter_L_x1_Data_uz_pmsm_model_9ph              0x138  //data register for Inport Physical_Parameter_L_x1
#define  Physical_Parameter_L_y1_Data_uz_pmsm_model_9ph              0x13C  //data register for Inport Physical_Parameter_L_y1
#define  Physical_Parameter_L_x2_Data_uz_pmsm_model_9ph              0x140  //data register for Inport Physical_Parameter_L_x2
#define  Physical_Parameter_L_y2_Data_uz_pmsm_model_9ph              0x144  //data register for Inport Physical_Parameter_L_y2
#define  Physical_Parameter_L_zero_Data_uz_pmsm_model_9ph            0x148  //data register for Inport Physical_Parameter_L_zero

#endif /* UZ_PMSM_MODEL_9PH_H_ */
