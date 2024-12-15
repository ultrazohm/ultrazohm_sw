/*
 * File Name:         hdl_prj/ipcore/IncEnc_V2_ip_v1_0/include/IncEnc_V2_ip_addr.h
 * Description:       C Header File
 * Created:           2024-12-15 21:07:26
*/

#ifndef INCENC_V2_IP_H_
#define INCENC_V2_IP_H_

#define  IPCore_Reset_IncEnc_V2_ip                  0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_IncEnc_V2_ip                 0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_IncEnc_V2_ip              0x8  //contains unique IP timestamp (yymmddHHMM): 2412152107
#define  Position_offset_AXI4_Data_IncEnc_V2_ip     0x100  //data register for Inport Position_offset_AXI4
#define  Timer_FPGA_ms_AXI4_Data_IncEnc_V2_ip       0x104  //data register for Inport Timer_FPGA_ms_AXI4
#define  PI2_Inc_AXI4_Data_IncEnc_V2_ip             0x108  //data register for Inport PI2_Inc_AXI4
#define  IncPerTurn_mech_AXI4_Data_IncEnc_V2_ip     0x10C  //data register for Inport IncPerTurn_mech_AXI4
#define  theta_el_offset_AXI4_Data_IncEnc_V2_ip     0x110  //data register for Inport theta_el_offset_AXI4
#define  IncPerTurn_elek_AXI4_Data_IncEnc_V2_ip     0x114  //data register for Inport IncPerTurn_elek_AXI4
#define  d_axis_Hit_Compare_AXI_Data_IncEnc_V2_ip   0x118  //data register for Inport d-axis-Hit-Compare_AXI
#define  omega_AXI4_Data_IncEnc_V2_ip               0x11C  //data register for Outport omega_AXI4
#define  theta_el_AXI4_Data_IncEnc_V2_ip            0x120  //data register for Outport theta_el_AXI4
#define  position_AXI4_Data_IncEnc_V2_ip            0x124  //data register for Outport position_AXI4
#define  OmegaPerOverSampl_AXI4_Data_IncEnc_V2_ip   0x128  //data register for Inport OmegaPerOverSampl_AXI4
#define  direction_AXI4_Data_IncEnc_V2_ip           0x12C  //data register for Outport direction_AXI4
#define  timeout_value_AXI4_Data_IncEnc_V2_ip       0x130  //data register for Inport timeout_value_AXI4
#define  countPerPeriod_AXI4_Data_IncEnc_V2_ip      0x134  //data register for Outport countPerPeriod_AXI4
#define  omega_MA_N4_AXI_Data_IncEnc_V2_ip          0x138  //data register for Outport omega_MA_N4_AXI
#define  position_wOffset_AXI4_Data_IncEnc_V2_ip    0x13C  //data register for Outport position_wOffset_AXI4
#define  CW_CCW_Switch_AXI4_Data_IncEnc_V2_ip       0x140  //data register for Inport CW_CCW_Switch_AXI4
#define  Index_found_AXI4_Data_IncEnc_V2_ip         0x144  //data register for Outport Index_found_AXI4

#endif /* INCENC_V2_IP_H_ */
