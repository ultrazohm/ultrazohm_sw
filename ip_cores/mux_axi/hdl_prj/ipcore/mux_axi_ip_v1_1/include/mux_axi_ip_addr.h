/*
 * File Name:         hdl_prj\ipcore\mux_axi_ip_v1_1\include\mux_axi_ip_addr.h
 * Description:       C Header File
 * Created:           2020-09-18 11:26:15
*/

#ifndef MUX_AXI_IP_H_
#define MUX_AXI_IP_H_

#define  IPCore_Reset_mux_axi_ip       0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_mux_axi_ip      0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_mux_axi_ip   0x8  //contains unique IP timestamp (yymmddHHMM): 2009181126
#define  select_AXI_Data_mux_axi_ip    0x100  //data register for Inport select_AXI

#endif /* MUX_AXI_IP_H_ */
