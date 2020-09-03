/*
 * File Name:         hdl_prj\ipcore\IncreEncoder_V22_ipcore_v1_0\include\IncreEncoder_V22_ipcore_addr.h
 * Description:       C Header File
 * Created:           2018-09-05 17:30:30
*/

#ifndef INCREENCODER_V22_IPCORE_H_
#define INCREENCODER_V22_IPCORE_H_

#define  IPCore_Reset_IncreEncoder_V22_ipcore                       0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_IncreEncoder_V22_ipcore                      0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_IncreEncoder_V22_ipcore                   0x8  //contains unique IP timestamp (yymmddHHMM): 1809051730
#define  OverSamplFactor_AXI4_Data_IncreEncoder_V22_ipcore          0x100  //data register for Inport OverSamplFactor_AXI4
#define  Timer_FPGA_ms_AXI4_Data_IncreEncoder_V22_ipcore            0x104  //data register for Inport Timer_FPGA_ms_AXI4
#define  PI2_Inc_AXI4_Data_IncreEncoder_V22_ipcore                  0x108  //data register for Inport PI2_Inc_AXI4
#define  IncPerTurn_mech_AXI4_Data_IncreEncoder_V22_ipcore          0x10C  //data register for Inport IncPerTurn_mech_AXI4
#define  Inc_PerTurn_mech_2PI_AXI4_Data_IncreEncoder_V22_ipcore     0x110  //data register for Inport Inc_PerTurn_mech_2PI_AXI4
#define  IncrementePerTurn_elek_AXI4_Data_IncreEncoder_V22_ipcore   0x114  //data register for Inport IncrementePerTurn_elek_AXI4
#define  omega_AXI4_Data_IncreEncoder_V22_ipcore                    0x118  //data register for Outport omega_AXI4
#define  direction_AXI4_Data_IncreEncoder_V22_ipcore                0x11C  //data register for Outport direction_AXI4
#define  theta_el_AXI4_Data_IncreEncoder_V22_ipcore                 0x120  //data register for Outport theta_el_AXI4
#define  theta_mech_AXI4_Data_IncreEncoder_V22_ipcore               0x124  //data register for Outport theta_mech_AXI4
#define  OverSamplFactorInv_AXI4_Data_IncreEncoder_V22_ipcore       0x128  //data register for Inport OverSamplFactorInv_AXI4
#define  countPerPeriod_AXI4_Data_IncreEncoder_V22_ipcore           0x12C  //data register for Outport countPerPeriod_AXI4

#endif /* INCREENCODER_V22_IPCORE_H_ */
