/*
 * File Name:         hdl_prj\ipcore\PWM_and_SS_control_ip_v1_0\include\PWM_and_SS_control_ip_addr.h
 * Description:       C Header File
 * Created:           2018-11-23 21:50:32
*/

#ifndef PWM_AND_SS_CONTROL_IP_H_
#define PWM_AND_SS_CONTROL_IP_H_

#define  IPCore_Reset_PWM_and_SS_control_ip                      0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_PWM_and_SS_control_ip                     0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_PWM_and_SS_control_ip                  0x8  //contains unique IP timestamp (yymmddHHMM): 1811232150
#define  PWM_en_AXI_Data_PWM_and_SS_control_ip                   0x100  //data register for Inport PWM_en_AXI
#define  Mode_AXI_Data_PWM_and_SS_control_ip                     0x104  //data register for Inport Mode_AXI
#define  PWM_f_carrier_kHz_AXI_Data_PWM_and_SS_control_ip        0x108  //data register for Inport PWM_f_carrier_kHz_AXI
#define  PWM_T_carrier_us_AXI_Data_PWM_and_SS_control_ip         0x10C  //data register for Inport PWM_T_carrier_us_AXI
#define  PWM_min_pulse_wiidth_AXI_Data_PWM_and_SS_control_ip     0x110  //data register for Inport PWM_min_pulse_wiidth_AXI
#define  m_u1_norm_AXI_Data_PWM_and_SS_control_ip                0x114  //data register for Inport m_u1_norm_AXI
#define  m_u2_norm_AXI_Data_PWM_and_SS_control_ip                0x118  //data register for Inport m_u2_norm_AXI
#define  m_u3_norm_AXI_Data_PWM_and_SS_control_ip                0x11C  //data register for Inport m_u3_norm_AXI
#define  PWM_en_rd_AXI_Data_PWM_and_SS_control_ip                0x120  //data register for Outport PWM_en_rd_AXI
#define  PWM_f_carrier_kHz_rd_AXI_Data_PWM_and_SS_control_ip     0x124  //data register for Outport PWM_f_carrier_kHz_rd_AXI
#define  PWM_T_carrier_us_rd_AXI_Data_PWM_and_SS_control_ip      0x128  //data register for Outport PWM_T_carrier_us_rd_AXI
#define  PWM_min_pulse_width_rd_AXI_Data_PWM_and_SS_control_ip   0x12C  //data register for Outport PWM_min_pulse_width_rd_AXI
#define  Mode_rd_AXI_Data_PWM_and_SS_control_ip                  0x130  //data register for Outport Mode_rd_AXI

#endif /* PWM_AND_SS_CONTROL_IP_H_ */
