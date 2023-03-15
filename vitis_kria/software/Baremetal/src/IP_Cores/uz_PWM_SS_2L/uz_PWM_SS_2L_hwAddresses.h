#pragma once

#ifndef PWM_AND_SS_CONTROL_V4_IP_H_
#define PWM_AND_SS_CONTROL_V4_IP_H_

#define  IPCore_Reset_PWM_and_SS_control_V4_ip                      0x0U  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_PWM_and_SS_control_V4_ip                     0x4U  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_PWM_and_SS_control_V4_ip                  0x8U  //contains unique IP timestamp (yymmddHHMM): 2109291448
#define  PWM_en_AXI_Data_PWM_and_SS_control_V4_ip                   0x100U  //data register for Inport PWM_en_AXI
#define  Mode_AXI_Data_PWM_and_SS_control_V4_ip                     0x104U  //data register for Inport Mode_AXI
#define  Scal_f_carrier_AXI_Data_PWM_and_SS_control_V4_ip           0x108U  //data register for Inport Scal_f_carrier_AXI
#define  Scal_T_carrier_AXI_Data_PWM_and_SS_control_V4_ip           0x10CU  //data register for Inport Scal_T_carrier_AXI
#define  PWM_min_pulse_width_AXI_Data_PWM_and_SS_control_V4_ip      0x110U  //data register for Inport PWM_min_pulse_width_AXI
#define  m_u1_norm_AXI_Data_PWM_and_SS_control_V4_ip                0x114U  //data register for Inport m_u1_norm_AXI
#define  m_u2_norm_AXI_Data_PWM_and_SS_control_V4_ip                0x118U  //data register for Inport m_u2_norm_AXI
#define  m_u3_norm_AXI_Data_PWM_and_SS_control_V4_ip                0x11CU  //data register for Inport m_u3_norm_AXI
#define  TriState_HB1_AXI_Data_PWM_and_SS_control_V4_ip             0x120U  //data register for Inport TriState_HB1_AXI
#define  TriState_HB2_AXI_Data_PWM_and_SS_control_V4_ip             0x124U  //data register for Inport TriState_HB2_AXI
#define  TriState_HB3_AXI_Data_PWM_and_SS_control_V4_ip             0x128U  //data register for Inport TriState_HB3_AXI
#define  triangle_shift_HB1_AXI_Data_PWM_and_SS_control_V4_ip       0x12CU  //data register for Inport triangle_shift
#define  count_src_ext_AXI_Data_PWM_and_SS_control_V4_ip            0x130U  //data register for Inport count_src_ext_AXI
#define  triangle_shift_HB2_AXI_Data_PWM_and_SS_control_V4_ip       0x134U  //data register for Inport triangle_shift_HB2
#define  triangle_shift_HB3_AXI_Data_PWM_and_SS_control_V4_ip       0x138U  //data register for Inport triangle_shift_HB3
#define  PWM_en_rd_AXI_Data_PWM_and_SS_control_V4_ip                0x13CU  //data register for Outport PWM_en_rd_AXI
#define  PWM_f_carrier_kHz_rd_AXI_Data_PWM_and_SS_control_V4_ip     0x140U  //data register for Outport PWM_f_carrier_kHz_rd_AXI
#define  PWM_T_carrier_us_rd_AXI_Data_PWM_and_SS_control_V4_ip      0x144U  //data register for Outport PWM_T_carrier_us_rd_AXI
#define  PWM_min_pulse_width_rd_AXI_Data_PWM_and_SS_control_V4_ip   0x148U  //data register for Outport PWM_min_pulse_width_rd_AXI
#define  Mode_rd_AXI_Data_PWM_and_SS_control_V4_ip                  0x14CU  //data register for Outport Mode_rd_AXI

#endif /* PWM_AND_SS_CONTROL_V4_IP_H_ */
