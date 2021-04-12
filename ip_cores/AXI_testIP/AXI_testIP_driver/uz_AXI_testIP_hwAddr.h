/*
 * File Name:         AXI_testIP/ipcore/AXI_testI_ip_v1_0/include/AXI_testI_ip_addr.h
 * Description:       C Header File
 * Created:           2021-03-21 19:14:31
*/

#ifndef AXI_TESTI_IP_H_
#define AXI_TESTI_IP_H_

#define  IPCore_Reset_AXI_testI_ip       0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_AXI_testI_ip      0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_AXI_testI_ip   0x8  //contains unique IP timestamp (yymmddHHMM): 2103211914
#define  A_float_Data_AXI_testI_ip       0x100  //data register for Inport A_float, vector with 4 elements, address ends at 0x10C
#define  A_float_Strobe_AXI_testI_ip     0x110  //strobe register for port A_float
#define  C_int32_Data_AXI_testI_ip       0x114  //data register for Outport C_int32
#define  C_uint32_Data_AXI_testI_ip      0x118  //data register for Outport C_uint32
#define  B_float_Data_AXI_testI_ip       0x120  //data register for Inport B_float, vector with 4 elements, address ends at 0x12C
#define  B_float_Strobe_AXI_testI_ip     0x130  //strobe register for port B_float
#define  A_uint32_Data_AXI_testI_ip      0x140  //data register for Inport A_uint32
#define  B_uint32_Data_AXI_testI_ip      0x160  //data register for Inport B_uint32
#define  A_int32_Data_AXI_testI_ip       0x180  //data register for Inport A_int32
#define  B_int32_Data_AXI_testI_ip       0x1A0  //data register for Inport B_int32
#define  A_fx_1_16_5_Data_AXI_testI_ip   0x1C0  //data register for Inport A_fx_1_16_5
#define  B_fx_1_16_5_Data_AXI_testI_ip   0x1E0  //data register for Inport B_fx_1_16_5
#define  C_float_Data_AXI_testI_ip       0x200  //data register for Outport C_float, vector with 4 elements, address ends at 0x20C
#define  C_float_Strobe_AXI_testI_ip     0x210  //strobe register for port C_float
#define  C_fx_1_16_5_Data_AXI_testI_ip   0x260  //data register for Outport C_fx_1_16_5

#endif /* AXI_TESTI_IP_H_ */
