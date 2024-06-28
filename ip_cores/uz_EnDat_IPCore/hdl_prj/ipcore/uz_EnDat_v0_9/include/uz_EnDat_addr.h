/*
 * File Name:         C:\Users\ELSYS_PC\Documents\repos\ultrazohm_sw\ip_cores\uz_EnDat_IPCore\hdl_prj\ipcore\uz_EnDat_v0_9\include\uz_EnDat_addr.h
 * Description:       C Header File
 * Created:           2023-10-05 16:42:59
*/

#ifndef UZ_ENDAT_H_
#define UZ_ENDAT_H_

#define  IPCore_Reset_uz_EnDat       0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_uz_EnDat      0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_uz_EnDat   0x8  //contains unique IP timestamp (yymmddHHMM): 2310051359: 2310051637: 2310051642
#define  divider_Data_uz_EnDat       0x100  //data register for Inport divider
#define  OD1_Data_uz_EnDat           0x104  //data register for Outport OD1
#define  controlword_Data_uz_EnDat   0x108  //data register for Inport controlword
#define  CRCDEBUG_Data_uz_EnDat      0x10C  //data register for Outport CRCDEBUG
#define  POS_Data_uz_EnDat           0x110  //data register for Outport POS. Data width is wider than the register width, so data is split into 2 32-bit sections.. Register is split across a total of 2 addresses, last address is 0x114.
#define  POS_Strobe_uz_EnDat         0x118  //strobe register for port POS
#define  OD2_Data_uz_EnDat           0x11C  //data register for Outport OD2
#define  1_min_Data_uz_EnDat         0x120  //data register for Outport 1//min. Data width is wider than the register width, so data is split into 2 32-bit sections.. Register is split across a total of 2 addresses, last address is 0x124.
#define  1_min_Strobe_uz_EnDat       0x128  //strobe register for port 1_min
#define  statusword_Data_uz_EnDat    0x12C  //data register for Outport statusword
#define  rad_s_Data_uz_EnDat         0x130  //data register for Outport rad//s. Data width is wider than the register width, so data is split into 2 32-bit sections.. Register is split across a total of 2 addresses, last address is 0x134.
#define  rad_s_Strobe_uz_EnDat       0x138  //strobe register for port rad_s

#endif /* UZ_ENDAT_H_ */
