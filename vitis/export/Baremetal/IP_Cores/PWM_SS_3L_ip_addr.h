/*
 * File Name:         hdl_prj\ipcore\PWM_SS_3L_ip_v1_4\include\PWM_SS_3L_ip_addr.h
 * Description:       C Header File
 * Created:           2020-04-06 17:35:20
*/

#ifndef PWM_SS_3L_IP_H_
#define PWM_SS_3L_IP_H_

#define  IPCore_Reset_PWM_SS_3L_ip                         0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_PWM_SS_3L_ip                        0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_PWM_SS_3L_ip                     0x8  //contains unique IP timestamp (yymmddHHMM): 2004061735
#define  PWM_en_AXI_Data_PWM_SS_3L_ip                      0x100  //data register for Inport PWM_en_AXI
#define  Mode_AXI_Data_PWM_SS_3L_ip                        0x104  //data register for Inport Mode_AXI
#define  PWM_counter_max_value_int_AXI_Data_PWM_SS_3L_ip   0x10C  //data register for Inport PWM_counter_max_value_int_AXI
#define  PWM_min_pulse_width_0to1_AXI_Data_PWM_SS_3L_ip    0x110  //data register for Inport PWM_min_pulse_width_0to1_AXI
#define  m_u1_norm_AXI_Data_PWM_SS_3L_ip                   0x114  //data register for Inport m_u1_norm_AXI
#define  m_u2_norm_AXI_Data_PWM_SS_3L_ip                   0x118  //data register for Inport m_u2_norm_AXI
#define  m_u3_norm_AXI_Data_PWM_SS_3L_ip                   0x11C  //data register for Inport m_u3_norm_AXI
#define  TriState_HB1_AXI_Data_PWM_SS_3L_ip                0x120  //data register for Inport TriState_HB1_AXI
#define  TriState_HB2_AXI_Data_PWM_SS_3L_ip                0x124  //data register for Inport TriState_HB2_AXI
#define  TriState_HB3_AXI_Data_PWM_SS_3L_ip                0x128  //data register for Inport TriState_HB3_AXI

#endif /* PWM_SS_3L_IP_H_ */
