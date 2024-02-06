/*
 * File Name:         C:\Users\ELSYS_PC\Documents\repos\ultrazohm_sw\ip_cores\uz_EnDat_IPCore\hdl_prj\ipcore\uz_EnDat_v9_0\include\uz_EnDat_addr.h
 * Description:       C Header File
 * Created:           2024-02-04 21:04:24
*/

#ifndef UZ_ENDAT_H_
#define UZ_ENDAT_H_

#define  IPCore_Reset_uz_EnDat              0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_uz_EnDat             0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_uz_EnDat          0x8  //contains unique IP timestamp (yymmddHHMM): 2402041744: 2402042104
#define  divider_Data_uz_EnDat              0x800  //data register for Inport divider
#define  FKT1DATAFLOW_Data_uz_EnDat         0x804  //data register for Inport FKT1DATAFLOW
#define  controlword_Data_uz_EnDat          0x808  //data register for Inport controlword
#define  FKT2RECOVERYTIME_Data_uz_EnDat     0x80C  //data register for Inport FKT2RECOVERYTIME
#define  FKT3INITIALOFF_Data_uz_EnDat       0x810  //data register for Inport FKT3INITIALOFF
#define  FKT4DATACLKSYNC_Data_uz_EnDat      0x814  //data register for Inport FKT4DATACLKSYNC
#define  FKT5TELEGRAMLEN_Data_uz_EnDat      0x818  //data register for Inport FKT5TELEGRAMLEN
#define  POS2BUS_Data_uz_EnDat              0x824  //data register for Outport POS2BUS
#define  POS1BUS_Data_uz_EnDat              0x828  //data register for Outport POS1BUS
#define  POS0BUS_Data_uz_EnDat              0x82C  //data register for Outport POS0BUS
#define  statusword_Data_uz_EnDat           0x844  //data register for Outport statusword
#define  CRCFFSTORED_Data_uz_EnDat          0x848  //data register for Outport CRCFFSTORED
#define  TIMEELASPEDT0T1BUS_Data_uz_EnDat   0x850  //data register for Outport TIMEELASPEDT0T1BUS
#define  TIMEELASPEDT0T2BUS_Data_uz_EnDat   0x860  //data register for Outport TIMEELASPEDT0T2BUS
#define  FKT6SYNCRESPONSE_Data_uz_EnDat     0x890  //data register for Inport FKT6SYNCRESPONSE
#define  FKT7EXTRASHIFT_Data_uz_EnDat       0x894  //data register for Inport FKT7EXTRASHIFT
#define  RESPONSELENBUS_Data_uz_EnDat       0x898  //data register for Outport RESPONSELENBUS
#define  DIFT0T1BUS_Data_uz_EnDat           0x8A0  //data register for Outport DIFT0T1BUS
#define  DIFT0T2BUS_Data_uz_EnDat           0x8B0  //data register for Outport DIFT0T2BUS

#endif /* UZ_ENDAT_H_ */
