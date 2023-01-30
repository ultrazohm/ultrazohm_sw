#pragma once

/*
 * File Name:         hdl_prj\ipcore\uz_d_inverter_adapter_v1_0\include\uz_d_inverter_adapter_addr.h
 * Description:       C Header File
 * Created:           2022-05-31 17:55:13
*/

#ifndef UZ_D_INVERTER_ADAPTER_H_
#define UZ_D_INVERTER_ADAPTER_H_

#define  IPCore_Reset_uz_d_inverter_adapter               0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_uz_d_inverter_adapter              0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_uz_d_inverter_adapter           0x8  //contains unique IP timestamp (yymmddHHMM): 2205311755
#define  AXI_en_in_Data_uz_d_inverter_adapter             0x100  //data register for Inport AXI_en_in
#define  AXI_Temp_1_period_Data_uz_d_inverter_adapter     0x104  //data register for Outport AXI_Temp_1_period
#define  AXI_Temp_1_hightime_Data_uz_d_inverter_adapter   0x108  //data register for Outport AXI_Temp_1_hightime
#define  AXI_Temp_1_lowtime_Data_uz_d_inverter_adapter    0x10C  //data register for Outport AXI_Temp_1_lowtime
#define  AXI_Temp_1_dutycyc_Data_uz_d_inverter_adapter    0x110  //data register for Outport AXI_Temp_1_dutycyc
#define  AXI_Temp_2_period_Data_uz_d_inverter_adapter     0x114  //data register for Outport AXI_Temp_2_period
#define  AXI_Temp_2_hightime_Data_uz_d_inverter_adapter   0x118  //data register for Outport AXI_Temp_2_hightime
#define  AXI_Temp_2_lowtime_Data_uz_d_inverter_adapter    0x11C  //data register for Outport AXI_Temp_2_lowtime
#define  AXI_Temp_2_dutycyc_Data_uz_d_inverter_adapter    0x120  //data register for Outport AXI_Temp_2_dutycyc
#define  AXI_Temp_3_period_Data_uz_d_inverter_adapter     0x124  //data register for Outport AXI_Temp_3_period
#define  AXI_Temp_3_hightime_Data_uz_d_inverter_adapter   0x128  //data register for Outport AXI_Temp_3_hightime
#define  AXI_Temp_3_lowtime_Data_uz_d_inverter_adapter    0x12C  //data register for Outport AXI_Temp_3_lowtime
#define  AXI_Temp_3_dutycyc_Data_uz_d_inverter_adapter    0x130  //data register for Outport AXI_Temp_3_dutycyc
#define  AXI_Temp_4_period_Data_uz_d_inverter_adapter     0x134  //data register for Outport AXI_Temp_4_period
#define  AXI_Temp_4_hightime_Data_uz_d_inverter_adapter   0x138  //data register for Outport AXI_Temp_4_hightime
#define  AXI_Temp_4_lowtime_Data_uz_d_inverter_adapter    0x13C  //data register for Outport AXI_Temp_4_lowtime
#define  AXI_Temp_4_dutycyc_Data_uz_d_inverter_adapter    0x140  //data register for Outport AXI_Temp_4_dutycyc
#define  AXI_Temp_5_period_Data_uz_d_inverter_adapter     0x144  //data register for Outport AXI_Temp_5_period
#define  AXI_Temp_5_hightime_Data_uz_d_inverter_adapter   0x148  //data register for Outport AXI_Temp_5_hightime
#define  AXI_Temp_5_lowtime_Data_uz_d_inverter_adapter    0x14C  //data register for Outport AXI_Temp_5_lowtime
#define  AXI_Temp_5_dutycyc_Data_uz_d_inverter_adapter    0x150  //data register for Outport AXI_Temp_5_dutycyc
#define  AXI_Temp_6_period_Data_uz_d_inverter_adapter     0x154  //data register for Outport AXI_Temp_6_period
#define  AXI_Temp_6_hightime_Data_uz_d_inverter_adapter   0x158  //data register for Outport AXI_Temp_6_hightime
#define  AXI_Temp_6_lowtime_Data_uz_d_inverter_adapter    0x15C  //data register for Outport AXI_Temp_6_lowtime
#define  AXI_Temp_6_dutycyc_Data_uz_d_inverter_adapter    0x160  //data register for Outport AXI_Temp_6_dutycyc
#define  AXI_FAULT_Data_uz_d_inverter_adapter             0x164  //data register for Outport AXI_FAULT
#define  AXI_OC_Data_uz_d_inverter_adapter                0x178  //data register for Outport AXI_OC
#define  AXI_I_DIAG_Data_uz_d_inverter_adapter            0x190  //data register for Outport AXI_I_DIAG
#define  AXI_PWM_Enable_Data_uz_d_inverter_adapter        0x1A0  //data register for Inport AXI_PWM_Enable

#endif /* UZ_D_INVERTER_ADAPTER_H_ */
