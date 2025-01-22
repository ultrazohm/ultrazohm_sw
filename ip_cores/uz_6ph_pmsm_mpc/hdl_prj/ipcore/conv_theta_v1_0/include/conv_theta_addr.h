/*
 * File Name:         hdl_prj\ipcore\conv_theta_v1_0\include\conv_theta_addr.h
 * Description:       C Header File
 * Created:           2025-01-21 10:19:34
*/

#ifndef CONV_THETA_H_
#define CONV_THETA_H_

#define  IPCore_Reset_conv_theta            0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_conv_theta           0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_conv_theta        0x8  //contains unique IP timestamp (yymmddHHMM): 2501211019
#define  theta_el_out_AXI_Data_conv_theta   0x1FC  //data register for Outport theta_el_out_AXI

#endif /* CONV_THETA_H_ */
