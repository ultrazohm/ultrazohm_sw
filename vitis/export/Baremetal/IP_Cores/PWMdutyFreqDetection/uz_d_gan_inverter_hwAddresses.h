/*
 * File Name:         C:\IPcoreTest\ipcore\PWMdutyFreqDetection_v1_0\include\PWMdutyFreqDetection_addr.h
 * Description:       C Header File
 * Created:           2021-04-27 12:03:32
*/

#ifndef PWMDUTYFREQDETECTION_H_
#define PWMDUTYFREQDETECTION_H_

#define  IPCore_Reset_PWMdutyFreqDetection        0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_PWMdutyFreqDetection       0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_PWMdutyFreqDetection    0x8  //contains unique IP timestamp (yymmddHHMM): 2104271203
#define  AXI_freq_Data_PWMdutyFreqDetection       0x100  //data register for Outport AXI_freq
#define  AXI_hightime_Data_PWMdutyFreqDetection   0x104  //data register for Outport AXI_hightime
#define  AXI_lowtime_Data_PWMdutyFreqDetection    0x108  //data register for Outport AXI_lowtime
#define  AXI_dutycyc_Data_PWMdutyFreqDetection    0x10C  //data register for Outport AXI_dutycyc

#endif /* PWMDUTYFREQDETECTION_H_ */
