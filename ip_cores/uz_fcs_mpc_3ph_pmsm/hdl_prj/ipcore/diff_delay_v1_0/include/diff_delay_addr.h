/*
 * File Name:         hdl_prj\ipcore\diff_delay_v1_0\include\diff_delay_addr.h
 * Description:       C Header File
 * Created:           2024-03-28 11:44:23
*/

#ifndef DIFF_DELAY_H_
#define DIFF_DELAY_H_

#define  IPCore_Reset_diff_delay       0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_diff_delay      0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_diff_delay   0x8  //contains unique IP timestamp (yymmddHHMM): 2403281144
#define  d_diff_AXI_Data_diff_delay    0x100  //data register for Outport d_diff_AXI
#define  q_diff_AXI_Data_diff_delay    0x104  //data register for Outport q_diff_AXI

#endif /* DIFF_DELAY_H_ */
