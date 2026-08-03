/*
 * File Name:         C:\Users\jonat\Documents\ultrazohm_sw\ip_cores\uz_JL_SigmaDelta_Interface\ipcore\uz_JL_SigmaDelta_Interface_v1_0\include\uz_JL_SigmaDelta_Interface_addr.h
 * Description:       C Header File
 * Created:           2026-08-03 19:23:16
*/

#ifndef UZ_JL_SIGMADELTA_INTERFACE_H_
#define UZ_JL_SIGMADELTA_INTERFACE_H_

#define  IPCore_Reset_uz_JL_SigmaDelta_Interface            0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_uz_JL_SigmaDelta_Interface           0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_uz_JL_SigmaDelta_Interface        0x8  //contains unique IP timestamp (yymmddHHMM): 2608031923
#define  clk_ratio_Data_uz_JL_SigmaDelta_Interface          0x100  //data register for Inport clk_ratio
#define  switch_edge_Data_uz_JL_SigmaDelta_Interface        0x104  //data register for Inport switch_edge
#define  Dezimation_Data_uz_JL_SigmaDelta_Interface         0x108  //data register for Inport Dezimation
#define  filt_input_delay_Data_uz_JL_SigmaDelta_Interface   0x10C  //data register for Inport filt_input_delay
#define  DSW_clk_en_Data_uz_JL_SigmaDelta_Interface         0x110  //data register for Inport DSW_clk_en
#define  clk_dutycycle_Data_uz_JL_SigmaDelta_Interface      0x114  //data register for Inport clk_dutycycle
#define  data_out_ps_Data_uz_JL_SigmaDelta_Interface        0x120  //data register for Outport data_out_ps. Vector with 5 elements. Register is split across a total of 5 addresses, last address is 0x130.
#define  data_out_ps_Strobe_uz_JL_SigmaDelta_Interface      0x140  //strobe register for port data_out_ps

#endif /* UZ_JL_SIGMADELTA_INTERFACE_H_ */
