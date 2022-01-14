#pragma once

#ifndef UZ_AXI_TESTIP_H_
#define UZ_AXI_TESTIP_H_

#define  IPCore_Reset_uz_axi_testIP       0x0U  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_uz_axi_testIP      0x4U  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_uz_axi_testIP   0x8U  //contains unique IP timestamp (yymmddHHMM): 2104181321
#define  A_float_Data_uz_axi_testIP       0x100U  //data register for Inport A_float, vector with 4 elements, address ends at 0x10C
#define  A_float_Strobe_uz_axi_testIP     0x110U  //strobe register for port A_float
#define  C_int32_Data_uz_axi_testIP       0x114U  //data register for Outport C_int32
#define  C_uint32_Data_uz_axi_testIP      0x118U  //data register for Outport C_uint32
#define  B_float_Data_uz_axi_testIP       0x120U  //data register for Inport B_float, vector with 4 elements, address ends at 0x12C
#define  B_float_Strobe_uz_axi_testIP     0x130U  //strobe register for port B_float
#define  A_uint32_Data_uz_axi_testIP      0x140U  //data register for Inport A_uint32
#define  B_uint32_Data_uz_axi_testIP      0x160U  //data register for Inport B_uint32
#define  A_int32_Data_uz_axi_testIP       0x180U  //data register for Inport A_int32
#define  B_int32_Data_uz_axi_testIP       0x1A0U  //data register for Inport B_int32
#define  A_fx_1_16_5_Data_uz_axi_testIP   0x1C0U  //data register for Inport A_fx_1_16_5
#define  B_fx_1_16_5_Data_uz_axi_testIP   0x1E0U  //data register for Inport B_fx_1_16_5
#define  C_float_Data_uz_axi_testIP       0x200U  //data register for Outport C_float, vector with 4 elements, address ends at 0x20C
#define  C_float_Strobe_uz_axi_testIP     0x210U  //strobe register for port C_float
#define  C_fx_1_16_5_Data_uz_axi_testIP   0x260U  //data register for Outport C_fx_1_16_5

#define  RESCON_Data_uz_axi_testIP        0x00U  //data register for RESCON
#define  RESDAT_Data_uz_axi_testIP        0x04U  //data register for RESDAT
#define  RESADR_Data_uz_axi_testIP        0x08U  //data register for RESADR
#define  RESRDA_Data_uz_axi_testIP        0x0CU  //data register for RESADR

#endif /* UZ_AXI_TESTIP_H_ */
