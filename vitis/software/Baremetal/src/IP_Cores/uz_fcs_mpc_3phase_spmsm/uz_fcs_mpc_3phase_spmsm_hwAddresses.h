#pragma once

#define  IPCore_Reset_FCS_MPC_3Phase_SPMSM_IP_Core          0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_FCS_MPC_3Phase_SPMSM_IP_Core         0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_FCS_MPC_3Phase_SPMSM_IP_Core      0x8  //contains unique IP timestamp (yymmddHHMM): 2206091023
#define  u_dc_link_AXI_Data_FCS_MPC_3Phase_SPMSM_IP_Core    0x100  //data register for Inport u_dc_link_AXI
#define  SampleTime_AXI_Data_FCS_MPC_3Phase_SPMSM_IP_Core   0x104  //data register for Inport SampleTime_AXI
#define  Rs_AXI_Data_FCS_MPC_3Phase_SPMSM_IP_Core           0x108  //data register for Inport Rs_AXI
#define  Ld_AXI_Data_FCS_MPC_3Phase_SPMSM_IP_Core           0x10C  //data register for Inport Ld_AXI
#define  Lq_AXI_Data_FCS_MPC_3Phase_SPMSM_IP_Core           0x110  //data register for Inport Lq_AXI
#define  psiPM_AXI_Data_FCS_MPC_3Phase_SPMSM_IP_Core        0x114  //data register for Inport psiPM_AXI