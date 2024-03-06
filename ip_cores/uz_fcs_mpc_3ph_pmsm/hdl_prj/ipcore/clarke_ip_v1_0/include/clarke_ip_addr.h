/*
 * File Name:         hdl_prj\ipcore\clarke_ip_v1_0\include\clarke_ip_addr.h
 * Description:       C Header File
 * Created:           2023-10-04 15:38:06
*/

#ifndef CLARKE_IP_H_
#define CLARKE_IP_H_

#define  IPCore_Reset_clarke_ip       0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_clarke_ip      0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_clarke_ip   0x8  //contains unique IP timestamp (yymmddHHMM): 2310041538
#define  alpha_AXI_Data_clarke_ip     0x100  //data register for Outport alpha_AXI
#define  beta_AXI_Data_clarke_ip      0x104  //data register for Outport beta_AXI

#endif /* CLARKE_IP_H_ */
