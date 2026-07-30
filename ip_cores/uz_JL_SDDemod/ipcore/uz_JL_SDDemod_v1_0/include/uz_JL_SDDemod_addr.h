/*
 * File Name:         C:\Users\jonat\Documents\ultrazohm_sw\ip_cores\uz_JL_SDDemod\ipcore\uz_JL_SDDemod_v1_0\include\uz_JL_SDDemod_addr.h
 * Description:       C Header File
 * Created:           2026-07-29 08:54:38
*/

#ifndef UZ_JL_SDDEMOD_H_
#define UZ_JL_SDDEMOD_H_

#define  IPCore_Reset_uz_JL_SDDemod            0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_uz_JL_SDDemod           0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_uz_JL_SDDemod        0x8  //contains unique IP timestamp (yymmddHHMM): 2607290854
#define  Dezimation_U_Data_uz_JL_SDDemod       0x100  //data register for Inport Dezimation_U
#define  Dezimation_I_Data_uz_JL_SDDemod       0x104  //data register for Inport Dezimation_I
#define  clk_ratio_Data_uz_JL_SDDemod          0x108  //data register for Inport clk_ratio
#define  switch_edge_Data_uz_JL_SDDemod        0x10C  //data register for Inport switch_edge
#define  data_out_ps_U_Data_uz_JL_SDDemod      0x110  //data register for Outport data_out_ps_U
#define  data_out_ps_PH1_Data_uz_JL_SDDemod    0x114  //data register for Outport data_out_ps_PH1
#define  data_out_ps_PH2_Data_uz_JL_SDDemod    0x118  //data register for Outport data_out_ps_PH2
#define  data_out_ps_PH3_Data_uz_JL_SDDemod    0x11C  //data register for Outport data_out_ps_PH3
#define  data_out_ps_PH4_Data_uz_JL_SDDemod    0x120  //data register for Outport data_out_ps_PH4
#define  filt_input_delay_Data_uz_JL_SDDemod   0x124  //data register for Inport filt_input_delay
#define  calibration_en_Data_uz_JL_SDDemod     0x128  //data register for Inport calibration_en
#define  DSW_clk_en_Data_uz_JL_SDDemod         0x12C  //data register for Inport DSW_clk_en
#define  clk_dutycycle_Data_uz_JL_SDDemod      0x130  //data register for Inport clk_dutycycle

#endif /* UZ_JL_SDDEMOD_H_ */
