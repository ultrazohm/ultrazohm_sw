/*
 * File Name:         C:\Users\jonat\Documents\ultrazohm_sw\ip_cores\uz_JL_SigmaDelta_Interface\ipcore\uz_JL_SigmaDelta_Interface_v1_0\include\uz_JL_SigmaDelta_Interface_addr.h
 * Description:       C Header File
 * Created:           2026-08-26 00:24:58
*/

#ifndef UZ_JL_SIGMADELTA_INTERFACE_H_
#define UZ_JL_SIGMADELTA_INTERFACE_H_

#define  IPCore_Reset_uz_JL_SigmaDelta_Interface               0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_uz_JL_SigmaDelta_Interface              0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_uz_JL_SigmaDelta_Interface           0x8  //contains unique IP timestamp (yymmddHHMM): 2608260024
#define  clk_ratio_Data_uz_JL_SigmaDelta_Interface             0x100  //data register for Inport clk_ratio
#define  switch_edge_Data_uz_JL_SigmaDelta_Interface           0x104  //data register for Inport switch_edge
#define  Dezimation_Data_uz_JL_SigmaDelta_Interface            0x108  //data register for Inport Dezimation
#define  filt_input_delay_Data_uz_JL_SigmaDelta_Interface      0x10C  //data register for Inport filt_input_delay
#define  switch_cont_disc_Data_uz_JL_SigmaDelta_Interface      0x110  //data register for Inport switch_cont_disc
#define  clk_dutycycle_Data_uz_JL_SigmaDelta_Interface         0x114  //data register for Inport clk_dutycycle
#define  start_time_us_Data_uz_JL_SigmaDelta_Interface         0x118  //data register for Inport start_time_us
#define  delay_data_valid_Data_uz_JL_SigmaDelta_Interface      0x11C  //data register for Inport delay_data_valid
#define  data_out_ps_Data_uz_JL_SigmaDelta_Interface           0x120  //data register for Outport data_out_ps. Vector with 5 elements. Register is split across a total of 5 addresses, last address is 0x130.
#define  data_out_ps_Strobe_uz_JL_SigmaDelta_Interface         0x140  //strobe register for port data_out_ps
#define  Data_valid_Data_uz_JL_SigmaDelta_Interface            0x144  //data register for Outport Data_valid
#define  sinc_sample_periods_Data_uz_JL_SigmaDelta_Interface   0x148  //data register for Inport sinc_sample_periods
#define  use_clk_ext_Data_uz_JL_SigmaDelta_Interface           0x14C  //data register for Inport use_clk_ext
#define  rst_data_valid_cnt_Data_uz_JL_SigmaDelta_Interface    0x150  //data register for Inport rst_data_valid_cnt
#define  data_valid_cnt_Data_uz_JL_SigmaDelta_Interface        0x154  //data register for Outport data_valid_cnt

#endif /* UZ_JL_SIGMADELTA_INTERFACE_H_ */
