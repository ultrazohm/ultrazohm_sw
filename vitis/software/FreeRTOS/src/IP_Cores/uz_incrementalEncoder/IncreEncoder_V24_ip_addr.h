/*
 * File Name:         hdl_prj\ipcore\IncreEncoder_V24_ip_v24_0\include\IncreEncoder_V24_ip_addr.h
 * Description:       C Header File
 * Created:           2020-06-13 11:16:30
*/

#ifndef INCREENCODER_V24_IP_H_
#define INCREENCODER_V24_IP_H_

#define  IPCore_Reset_IncreEncoder_V24_ip                  0x0U  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_IncreEncoder_V24_ip                 0x4U  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_IncreEncoder_V24_ip              0x8U  //contains unique IP timestamp (yymmddHHMM): 2006131116
#define  Timer_FPGA_ms_AXI4_Data_IncreEncoder_V24_ip       0x104U  //data register for Inport Timer_FPGA_ms_AXI4
#define  PI2_Inc_AXI4_Data_IncreEncoder_V24_ip             0x108U  //data register for Inport PI2_Inc_AXI4
#define  IncPerTurn_mech_AXI4_Data_IncreEncoder_V24_ip     0x10CU  //data register for Inport IncPerTurn_mech_AXI4
#define  IncPerTurn_elek_AXI4_Data_IncreEncoder_V24_ip     0x114U  //data register for Inport IncPerTurn_elek_AXI4
#define  omega_AXI4_Data_IncreEncoder_V24_ip               0x118U  //data register for Outport omega_AXI4
#define  direction_AXI4_Data_IncreEncoder_V24_ip           0x11CU  //data register for Outport direction_AXI4
#define  theta_el_AXI4_Data_IncreEncoder_V24_ip            0x120U  //data register for Outport theta_el_AXI4
#define  position_AXI4_Data_IncreEncoder_V24_ip            0x124U  //data register for Outport position_AXI4
#define  OmegaPerOverSampl_AXI4_Data_IncreEncoder_V24_ip   0x128U  //data register for Inport OmegaPerOverSampl_AXI4
#define  countPerPeriod_AXI4_Data_IncreEncoder_V24_ip      0x12CU  //data register for Outport countPerPeriod_AXI4

#endif /* INCREENCODER_V24_IP_H_ */
