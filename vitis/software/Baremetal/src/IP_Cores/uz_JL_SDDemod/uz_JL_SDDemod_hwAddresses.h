#pragma once

#define  IPCore_Reset_uz_JL_SDDemod       0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_uz_JL_SDDemod      0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_uz_JL_SDDemod   0x8  //contains unique IP timestamp (yymmddHHMM): 2606030121
#define  R_axi_Data_uz_JL_SDDemod         0x100  //data register for Inport R_axi
#define  data_out_ps_Data_uz_JL_SDDemod   0x104  //data register for Outport data_out_ps