/*
 * File Name:         C:\Users\ELSYS_PC\Documents\repos\ultrazohm_sw\ip_cores\uz_EnDat_IPCore\hdl_prj\ipcore\uz_EnDat_v1_5\include\uz_EnDat_addr.h
 * Description:       C Header File
 * Created:           2023-11-15 14:01:45
*/

#ifndef UZ_ENDAT_H_
#define UZ_ENDAT_H_

#define  IPCore_Reset_uz_EnDat            0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_uz_EnDat           0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_uz_EnDat        0x8  //contains unique IP timestamp (yymmddHHMM): 2311151401
#define  divider_Data_uz_EnDat            0x100  //data register for Inport divider
#define  FKT1DATAFLOW_Data_uz_EnDat       0x104  //data register for Inport FKT1DATAFLOW
#define  controlword_Data_uz_EnDat        0x108  //data register for Inport controlword
#define  FKT2RECOVERYTIME_Data_uz_EnDat   0x10C  //data register for Inport FKT2RECOVERYTIME
#define  FKT3INITIALOFF_Data_uz_EnDat     0x110  //data register for Inport FKT3INITIALOFF
#define  FKT4DATACLKSYNC_Data_uz_EnDat    0x114  //data register for Inport FKT4DATACLKSYNC
#define  FKT5TELEGRAMLEN_Data_uz_EnDat    0x118  //data register for Inport FKT5TELEGRAMLEN
#define  POS4BUS0_Data_uz_EnDat           0x11C  //data register for Outport POS4BUS0
#define  POS3BUS0_Data_uz_EnDat           0x120  //data register for Outport POS3BUS0
#define  POS2BUS0_Data_uz_EnDat           0x124  //data register for Outport POS2BUS0
#define  POS1BUS0_Data_uz_EnDat           0x128  //data register for Outport POS1BUS0
#define  POS0BUS_Data_uz_EnDat            0x12C  //data register for Outport POS0BUS
#define  statusword_Data_uz_EnDat         0x144  //data register for Outport statusword
#define  CRCDEBUG_Data_uz_EnDat           0x148  //data register for Outport CRCDEBUG

#endif /* UZ_ENDAT_H_ */
