/*
 * File Name:         hdl_prj\ipcore\PWM_3Level_control_v1_0\include\PWM_3Level_control_addr.h
 * Description:       C Header File
 * Created:           2025-11-17 13:37:14
*/

#ifndef PWM_3LEVEL_CONTROL_H_
#define PWM_3LEVEL_CONTROL_H_

#define  IPCore_Reset_PWM_3Level_control                      0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_PWM_3Level_control                     0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_PWM_3Level_control                  0x8  //contains unique IP timestamp (yymmddHHMM): 2511171337
#define  PWM_en_AXI_Data_PWM_3Level_control                   0x100  //data register for Inport PWM_en_AXI
#define  SS0_OUT_Data_PWM_3Level_control                      0x104  //data register for Outport SS0_OUT
#define  Scal_f_carrier_AXI_Data_PWM_3Level_control           0x108  //data register for Inport Scal_f_carrier_AXI
#define  Scal_T_carrier_AXI_Data_PWM_3Level_control           0x10C  //data register for Inport Scal_T_carrier_AXI
#define  Scal_carrier_arrangement_Data_PWM_3Level_control     0x110  //data register for Inport Scal_carrier_arrangement. Data width is wider than the register width, so data is split into 2 32-bit sections.. Register is split across a total of 2 addresses, last address is 0x114.
#define  Scal_carrier_arrangement_Strobe_PWM_3Level_control   0x118  //strobe register for port Scal_carrier_arrangement
#define  SS1_OUT_Data_PWM_3Level_control                      0x11C  //data register for Outport SS1_OUT
#define  m_u1_norm_Data_PWM_3Level_control                    0x120  //data register for Inport m_u1_norm. Data width is wider than the register width, so data is split into 2 32-bit sections.. Register is split across a total of 2 addresses, last address is 0x124.
#define  m_u1_norm_Strobe_PWM_3Level_control                  0x128  //strobe register for port m_u1_norm
#define  SS2_OUT_Data_PWM_3Level_control                      0x12C  //data register for Outport SS2_OUT
#define  SS3_OUT_Data_PWM_3Level_control                      0x130  //data register for Outport SS3_OUT

#endif /* PWM_3LEVEL_CONTROL_H_ */
