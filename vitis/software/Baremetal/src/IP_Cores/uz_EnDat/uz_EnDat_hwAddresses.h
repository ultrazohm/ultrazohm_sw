#pragma once

#ifndef UZ_AXI_TESTIP_H_
#define UZ_AXI_TESTIP_H_

#define  IPCore_Reset_uz_EnDat            0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_uz_EnDat           0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_uz_EnDat        0x8  //contains unique IP timestamp (yymmddHHMM): 2311152215: 2311152219
#define  divider_Data_uz_EnDat            0x800  //data register for Inport divider
#define  FKT1DATAFLOW_Data_uz_EnDat       0x804  //data register for Inport FKT1DATAFLOW
#define  controlword_Data_uz_EnDat        0x808  //data register for Inport controlword
#define  FKT2RECOVERYTIME_Data_uz_EnDat   0x80C  //data register for Inport FKT2RECOVERYTIME
#define  FKT3INITIALOFF_Data_uz_EnDat     0x810  //data register for Inport FKT3INITIALOFF
#define  FKT4DATACLKSYNC_Data_uz_EnDat    0x814  //data register for Inport FKT4DATACLKSYNC
#define  FKT5TELEGRAMLEN_Data_uz_EnDat    0x818  //data register for Inport FKT5TELEGRAMLEN
#define  POS4BUS0_Data_uz_EnDat           0x81C  //data register for Outport POS4BUS0
#define  POS3BUS0_Data_uz_EnDat           0x820  //data register for Outport POS3BUS0
#define  POS2BUS0_Data_uz_EnDat           0x824  //data register for Outport POS2BUS0
#define  POS1BUS0_Data_uz_EnDat           0x828  //data register for Outport POS1BUS0
#define  POS0BUS_Data_uz_EnDat            0x82C  //data register for Outport POS0BUS
#define  statusword_Data_uz_EnDat         0x844  //data register for Outport statusword
#define  CRCDEBUG_Data_uz_EnDat           0x848  //data register for Outport CRCDEBUG

#endif /* UZ_AXI_TESTIP_H_ */
