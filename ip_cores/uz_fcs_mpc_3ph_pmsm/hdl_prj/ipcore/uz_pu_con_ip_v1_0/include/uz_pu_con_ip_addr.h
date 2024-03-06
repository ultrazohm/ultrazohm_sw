/*
 * File Name:         hdl_prj\ipcore\uz_pu_con_ip_v1_0\include\uz_pu_con_ip_addr.h
 * Description:       C Header File
 * Created:           2023-10-04 15:36:04
*/

#ifndef UZ_PU_CON_IP_H_
#define UZ_PU_CON_IP_H_

#define  IPCore_Reset_uz_pu_con_ip           0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_uz_pu_con_ip          0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_uz_pu_con_ip       0x8  //contains unique IP timestamp (yymmddHHMM): 2310041536
#define  AXI_pu_conv_in0_Data_uz_pu_con_ip   0x100  //data register for Inport AXI_pu_conv_in0
#define  AXI_pu_conv_in1_Data_uz_pu_con_ip   0x104  //data register for Inport AXI_pu_conv_in1
#define  AXI_pu_conv_in2_Data_uz_pu_con_ip   0x108  //data register for Inport AXI_pu_conv_in2
#define  AXI_pu_conv_in3_Data_uz_pu_con_ip   0x10C  //data register for Inport AXI_pu_conv_in3
#define  out0_AXI_Data_uz_pu_con_ip          0x180  //data register for Outport out0_AXI
#define  out1_AXI_Data_uz_pu_con_ip          0x184  //data register for Outport out1_AXI
#define  out2_AXI_Data_uz_pu_con_ip          0x188  //data register for Outport out2_AXI
#define  out3_AXI_Data_uz_pu_con_ip          0x18C  //data register for Outport out3_AXI

#endif /* UZ_PU_CON_IP_H_ */
