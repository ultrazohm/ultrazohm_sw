/*
 * File Name:         hdl_prj\ipcore\PWM_and_SS_control_V4_ip_v4_0\include\PWM_and_SS_control_V4_ip_addr.h
 * Description:       C Header File
 * Created:           2021-09-21 17:38:02
*/

#ifndef PWM_AND_SS_CONTROL_V4_IP_H_
#define PWM_AND_SS_CONTROL_V4_IP_H_

#define  IPCore_Reset_PWM_and_SS_control_V4_ip                      0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_PWM_and_SS_control_V4_ip                     0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_PWM_and_SS_control_V4_ip                  0x8  //contains unique IP timestamp (yymmddHHMM): 2109211737
#define  PWM_en_AXI_Data_PWM_and_SS_control_V4_ip                   0x100  //data register for Inport PWM_en_AXI
#define  Mode_AXI_Data_PWM_and_SS_control_V4_ip                     0x104  //data register for Inport Mode_AXI
#define  Scal_f_carrier_AXI_Data_PWM_and_SS_control_V4_ip           0x108  //data register for Inport Scal_f_carrier_AXI
#define  Scal_T_carrier_AXI_Data_PWM_and_SS_control_V4_ip           0x10C  //data register for Inport Scal_T_carrier_AXI
#define  PWM_min_pulse_width_AXI_Data_PWM_and_SS_control_V4_ip      0x110  //data register for Inport PWM_min_pulse_width_AXI
#define  m_u1_norm_AXI_Data_PWM_and_SS_control_V4_ip                0x114  //data register for Inport m_u1_norm_AXI
#define  m_u2_norm_AXI_Data_PWM_and_SS_control_V4_ip                0x118  //data register for Inport m_u2_norm_AXI
#define  m_u3_norm_AXI_Data_PWM_and_SS_control_V4_ip                0x11C  //data register for Inport m_u3_norm_AXI
#define  m_u4_norm_AXI_Data_PWM_and_SS_control_V4_ip                0x120  //data register for Inport m_u4_norm_AXI
#define  m_u5_norm_AXI_Data_PWM_and_SS_control_V4_ip                0x124  //data register for Inport m_u5_norm_AXI
#define  m_u6_norm_AXI_Data_PWM_and_SS_control_V4_ip                0x128  //data register for Inport m_u6_norm_AXI
#define  m_u7_norm_AXI_Data_PWM_and_SS_control_V4_ip                0x12C  //data register for Inport m_u7_norm_AXI
#define  m_u8_norm_AXI_Data_PWM_and_SS_control_V4_ip                0x130  //data register for Inport m_u8_norm_AXI
#define  m_u9_norm_AXI_Data_PWM_and_SS_control_V4_ip                0x134  //data register for Inport m_u9_norm_AXI
#define  m_u10_norm_AXI_Data_PWM_and_SS_control_V4_ip               0x138  //data register for Inport m_u10_norm_AXI
#define  m_u11_norm_AXI_Data_PWM_and_SS_control_V4_ip               0x13C  //data register for Inport m_u11_norm_AXI
#define  m_u12_norm_AXI_Data_PWM_and_SS_control_V4_ip               0x140  //data register for Inport m_u12_norm_AXI
#define  TriState_HB1_AXI_Data_PWM_and_SS_control_V4_ip             0x144  //data register for Inport TriState_HB1_AXI
#define  TriState_HB2_AXI_Data_PWM_and_SS_control_V4_ip             0x148  //data register for Inport TriState_HB2_AXI
#define  TriState_HB3_AXI_Data_PWM_and_SS_control_V4_ip             0x14C  //data register for Inport TriState_HB3_AXI
#define  TriState_HB4__AXI_Data_PWM_and_SS_control_V4_ip            0x150  //data register for Inport TriState_HB4	_AXI
#define  TriState_HB5_AXI_Data_PWM_and_SS_control_V4_ip             0x154  //data register for Inport TriState_HB5_AXI
#define  TriState_HB6_AXI_Data_PWM_and_SS_control_V4_ip             0x158  //data register for Inport TriState_HB6_AXI
#define  TriState_HB7__AXI_Data_PWM_and_SS_control_V4_ip            0x15C  //data register for Inport TriState_HB7	_AXI
#define  TriState_HB8_AXI_Data_PWM_and_SS_control_V4_ip             0x160  //data register for Inport TriState_HB8_AXI
#define  TriState_HB9_AXI_Data_PWM_and_SS_control_V4_ip             0x164  //data register for Inport TriState_HB9_AXI
#define  TriState_HB10_AXI_Data_PWM_and_SS_control_V4_ip            0x168  //data register for Inport TriState_HB10_AXI
#define  TriState_HB11_AXI_Data_PWM_and_SS_control_V4_ip            0x16C  //data register for Inport TriState_HB11_AXI
#define  TriState_HB12_AXI_Data_PWM_and_SS_control_V4_ip            0x170  //data register for Inport TriState_HB12_AXI
#define  PWM_en_rd_AXI_Data_PWM_and_SS_control_V4_ip                0x174  //data register for Outport PWM_en_rd_AXI
#define  PWM_f_carrier_kHz_rd_AXI_Data_PWM_and_SS_control_V4_ip     0x178  //data register for Outport PWM_f_carrier_kHz_rd_AXI
#define  PWM_T_carrier_us_rd_AXI_Data_PWM_and_SS_control_V4_ip      0x17C  //data register for Outport PWM_T_carrier_us_rd_AXI
#define  PWM_min_pulse_width_rd_AXI_Data_PWM_and_SS_control_V4_ip   0x180  //data register for Outport PWM_min_pulse_width_rd_AXI
#define  Mode_rd_AXI_Data_PWM_and_SS_control_V4_ip                  0x184  //data register for Outport Mode_rd_AXI

#endif /* PWM_AND_SS_CONTROL_V4_IP_H_ */
