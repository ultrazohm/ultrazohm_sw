#pragma once

#define  IPCore_Reset_FCS_MPC_3Phase_SPMSM_IP_Core          0x0U  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_FCS_MPC_3Phase_SPMSM_IP_Core         0x4U  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_FCS_MPC_3Phase_SPMSM_IP_Core      0x8U  //contains unique IP timestamp (yymmddHHMM): 2206091023
#define  u_dc_link_AXI_Data_FCS_MPC_3Phase_SPMSM_IP_Core    0x100U  //data register for Inport u_dc_link_AXI
#define  SampleTime_AXI_Data_FCS_MPC_3Phase_SPMSM_IP_Core   0x104U  //data register for Inport SampleTime_AXI
#define  Rs_AXI_Data_FCS_MPC_3Phase_SPMSM_IP_Core           0x108U  //data register for Inport Rs_AXI
#define  Ld_AXI_Data_FCS_MPC_3Phase_SPMSM_IP_Core           0x10CU  //data register for Inport Ld_AXI
#define  Lq_AXI_Data_FCS_MPC_3Phase_SPMSM_IP_Core           0x110U  //data register for Inport Lq_AXI
#define  psiPM_AXI_Data_FCS_MPC_3Phase_SPMSM_IP_Core        0x114U  //data register for Inport psiPM_AXI