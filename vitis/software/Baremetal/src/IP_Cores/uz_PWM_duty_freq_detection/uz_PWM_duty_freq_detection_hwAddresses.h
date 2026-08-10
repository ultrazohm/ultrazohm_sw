/*
 * File Name:         hdl_prj\ipcore\uz_pwmdutyfreqdetection_v1_0\include\uz_pwmdutyfreqdetection_addr.h
 * Description:       C Header File
 * Created:           2025-10-16 10:55:54
*/

#ifndef UZ_PWMDUTYFREQDETECTION_H_
#define UZ_PWMDUTYFREQDETECTION_H_


#define  IPCore_Reset_uz_pwmdutyfreqdetection        0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_uz_pwmdutyfreqdetection       0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_uz_pwmdutyfreqdetection    0x8  //contains unique IP timestamp (yymmddHHMM): 2602251004
#define  AXI_output_Data_uz_pwmdutyfreqdetection     0x100  //data register for Outport AXI_output. Vector with 3 elements. Register is split across a total of 3 addresses, last address is 0x108.
#define  AXI_period_Data_uz_pwmdutyfreqdetection     0x100  //data register for Outport AXI_period
#define  AXI_hightime_Data_uz_pwmdutyfreqdetection   0x100+0x4  //data register for Outport AXI_hightime
#define  AXI_lowtime_Data_uz_pwmdutyfreqdetection    0x100+0x8  //data register for Outport AXI_lowtime
#define  AXI_output_Strobe_uz_pwmdutyfreqdetection   0x110  //strobe register for port AXI_output

#endif /* UZ_PWMDUTYFREQDETECTION_H_ */