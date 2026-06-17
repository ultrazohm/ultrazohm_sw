#pragma once

#define  IPCore_Reset_uz_JL_SDDemod       0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_uz_JL_SDDemod      0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_uz_JL_SDDemod   0x8  //contains unique IP timestamp (yymmddHHMM): 2606151507
#define  Dezimation_Data_uz_JL_SDDemod    0x100  //data register for Inport Dezimation
#define  data_out_ps_Data_uz_JL_SDDemod   0x104  //data register for Outport data_out_ps
#define  clk_ratio_Data_uz_JL_SDDemod     0x108  //data register for Inport clk_ratio
#define  switch_clk_Data_uz_JL_SDDemod    0x10C  //data register for Inport switch_clk