/*
 * File Name:         hdl_prj\ipcore\Incremental_Encoder_v25_0\include\Incremental_Encoder_addr.h
 * Description:       C Header File
 * Created:           2022-04-20 12:43:31
*/

#ifndef INCREMENTAL_ENCODER_H_
#define INCREMENTAL_ENCODER_H_

#define  IPCore_Reset_Incremental_Encoder                  0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_Incremental_Encoder                 0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_Incremental_Encoder              0x8  //contains unique IP timestamp (yymmddHHMM): 2204201243
#define  omega_MA_N4_AXI_Data_Incremental_Encoder          0x100  //data register for Outport omega_MA_N4_AXI
#define  Timer_FPGA_ms_AXI4_Data_Incremental_Encoder       0x104  //data register for Inport Timer_FPGA_ms_AXI4
#define  PI2_Inc_AXI4_Data_Incremental_Encoder             0x108  //data register for Inport PI2_Inc_AXI4
#define  IncPerTurn_mech_AXI4_Data_Incremental_Encoder     0x10C  //data register for Inport IncPerTurn_mech_AXI4
#define  IncPerTurn_elek_AXI4_Data_Incremental_Encoder     0x114  //data register for Inport IncPerTurn_elek_AXI4
#define  omega_AXI4_Data_Incremental_Encoder               0x118  //data register for Outport omega_AXI4
#define  direction_AXI4_Data_Incremental_Encoder           0x11C  //data register for Outport direction_AXI4
#define  theta_el_AXI4_Data_Incremental_Encoder            0x120  //data register for Outport theta_el_AXI4
#define  position_AXI4_Data_Incremental_Encoder            0x124  //data register for Outport position_AXI4
#define  OmegaPerOverSampl_AXI4_Data_Incremental_Encoder   0x128  //data register for Inport OmegaPerOverSampl_AXI4
#define  countPerPeriod_AXI4_Data_Incremental_Encoder      0x12C  //data register for Outport countPerPeriod_AXI4
#define  timeout_value_AXI4_Data_Incremental_Encoder       0x130  //data register for Inport timeout_value_AXI4

#endif /* INCREMENTAL_ENCODER_H_ */
