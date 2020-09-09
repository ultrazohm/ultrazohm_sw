/*
 * File Name:         hdl_prj\ipcore\IncreEncoder_V24_ip_v24_0\include\IncreEncoder_V24_ip_addr.h
 * Description:       C Header File
 * Created:           2020-06-13 11:16:30
*/

#ifndef INCREENCODER_V24_IP_H_
#define INCREENCODER_V24_IP_H_

#define  IPCore_Reset_IncreEncoder_V24_ip                  0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_IncreEncoder_V24_ip                 0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_IncreEncoder_V24_ip              0x8  //contains unique IP timestamp (yymmddHHMM): 2006131116
#define  Timer_FPGA_ms_AXI4_Data_IncreEncoder_V24_ip       0x104  //data register for Inport Timer_FPGA_ms_AXI4
#define  PI2_Inc_AXI4_Data_IncreEncoder_V24_ip             0x108  //data register for Inport PI2_Inc_AXI4
#define  IncPerTurn_mech_AXI4_Data_IncreEncoder_V24_ip     0x10C  //data register for Inport IncPerTurn_mech_AXI4
#define  IncPerTurn_elek_AXI4_Data_IncreEncoder_V24_ip     0x114  //data register for Inport IncPerTurn_elek_AXI4
#define  omega_AXI4_Data_IncreEncoder_V24_ip               0x118  //data register for Outport omega_AXI4
#define  direction_AXI4_Data_IncreEncoder_V24_ip           0x11C  //data register for Outport direction_AXI4
#define  theta_el_AXI4_Data_IncreEncoder_V24_ip            0x120  //data register for Outport theta_el_AXI4
#define  position_AXI4_Data_IncreEncoder_V24_ip            0x124  //data register for Outport position_AXI4
#define  OmegaPerOverSampl_AXI4_Data_IncreEncoder_V24_ip   0x128  //data register for Inport OmegaPerOverSampl_AXI4
#define  countPerPeriod_AXI4_Data_IncreEncoder_V24_ip      0x12C  //data register for Outport countPerPeriod_AXI4

#endif /* INCREENCODER_V24_IP_H_ */
