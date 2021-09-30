#pragma once

#ifndef PWM_AND_SS_CONTROL_V4_IP_H_
#define PWM_AND_SS_CONTROL_V4_IP_H_

#define  IPCore_Reset_PWM_and_SS_control_V4_ip                      0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_PWM_and_SS_control_V4_ip                     0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_PWM_and_SS_control_V4_ip                  0x8  //contains unique IP timestamp (yymmddHHMM): 2109291448
#define  PWM_en_AXI_Data_PWM_and_SS_control_V4_ip                   0x100  //data register for Inport PWM_en_AXI
#define  Mode_AXI_Data_PWM_and_SS_control_V4_ip                     0x104  //data register for Inport Mode_AXI
#define  Scal_f_carrier_AXI_Data_PWM_and_SS_control_V4_ip           0x108  //data register for Inport Scal_f_carrier_AXI
#define  Scal_T_carrier_AXI_Data_PWM_and_SS_control_V4_ip           0x10C  //data register for Inport Scal_T_carrier_AXI
#define  PWM_min_pulse_width_AXI_Data_PWM_and_SS_control_V4_ip      0x110  //data register for Inport PWM_min_pulse_width_AXI
#define  m_u1_norm_AXI_Data_PWM_and_SS_control_V4_ip                0x114  //data register for Inport m_u1_norm_AXI
#define  m_u2_norm_AXI_Data_PWM_and_SS_control_V4_ip                0x118  //data register for Inport m_u2_norm_AXI
#define  m_u3_norm_AXI_Data_PWM_and_SS_control_V4_ip                0x11C  //data register for Inport m_u3_norm_AXI
#define  TriState_HB1_AXI_Data_PWM_and_SS_control_V4_ip             0x120  //data register for Inport TriState_HB1_AXI
#define  TriState_HB2_AXI_Data_PWM_and_SS_control_V4_ip             0x124  //data register for Inport TriState_HB2_AXI
#define  TriState_HB3_AXI_Data_PWM_and_SS_control_V4_ip             0x128  //data register for Inport TriState_HB3_AXI
#define  count_src_ext_AXI_Data_PWM_and_SS_control_V4_ip            0x130  //data register for Inport count_src_ext_AXI
#define  PWM_en_rd_AXI_Data_PWM_and_SS_control_V4_ip                0x134  //data register for Outport PWM_en_rd_AXI
#define  PWM_f_carrier_kHz_rd_AXI_Data_PWM_and_SS_control_V4_ip     0x138  //data register for Outport PWM_f_carrier_kHz_rd_AXI
#define  PWM_T_carrier_us_rd_AXI_Data_PWM_and_SS_control_V4_ip      0x13C  //data register for Outport PWM_T_carrier_us_rd_AXI
#define  PWM_min_pulse_width_rd_AXI_Data_PWM_and_SS_control_V4_ip   0x140  //data register for Outport PWM_min_pulse_width_rd_AXI
#define  Mode_rd_AXI_Data_PWM_and_SS_control_V4_ip                  0x144  //data register for Outport Mode_rd_AXI

#endif /* PWM_AND_SS_CONTROL_V4_IP_H_ */
