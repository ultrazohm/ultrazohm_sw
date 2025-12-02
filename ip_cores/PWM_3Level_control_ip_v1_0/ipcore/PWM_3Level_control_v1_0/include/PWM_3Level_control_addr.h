/*
 * File Name:         C:\Ultrazohm\ultrazohm_sw\ip_cores\PWM_3Level_control_ip_v1_0\ipcore\PWM_3Level_control_v1_0\include\PWM_3Level_control_addr.h
 * Description:       C Header File
 * Created:           2025-12-01 21:43:52
*/

#ifndef PWM_3LEVEL_CONTROL_H_
#define PWM_3LEVEL_CONTROL_H_

#define  IPCore_Reset_PWM_3Level_control                       0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_PWM_3Level_control                      0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_PWM_3Level_control                   0x8  //contains unique IP timestamp (yymmddHHMM): 2512012143
#define  PWM_en_AXI_Data_PWM_3Level_control                    0x100  //data register for Inport PWM_en_AXI
#define  Mode_AXI_Data_PWM_3Level_control                      0x104  //data register for Inport Mode_AXI
#define  PWM_en_AXI_readback_Data_PWM_3Level_control           0x108  //data register for Outport PWM_en_AXI_readback
#define  Scal_T_carrier_AXI_Data_PWM_3Level_control            0x10C  //data register for Inport Scal_T_carrier_AXI
#define  Scal_T_carrier_AXI_readback_Data_PWM_3Level_control   0x110  //data register for Outport Scal_T_carrier_AXI_readback
#define  m_u1_norm_readback_Data_PWM_3Level_control            0x114  //data register for Outport m_u1_norm_readback
#define  Carrier_OUT_AXI_Data_PWM_3Level_control               0x118  //data register for Outport Carrier_OUT_AXI
#define  Sampling_AXI_Data_PWM_3Level_control                  0x11C  //data register for Inport Sampling_AXI
#define  m_u1_norm_AXI_Data_PWM_3Level_control                 0x124  //data register for Inport m_u1_norm_AXI
#define  SS0_OUT_Data_PWM_3Level_control                       0x128  //data register for Outport SS0_OUT
#define  SS1_OUT_Data_PWM_3Level_control                       0x138  //data register for Outport SS1_OUT
#define  SS2_OUT_Data_PWM_3Level_control                       0x148  //data register for Outport SS2_OUT
#define  SS3_OUT_Data_PWM_3Level_control                       0x158  //data register for Outport SS3_OUT

#endif /* PWM_3LEVEL_CONTROL_H_ */
