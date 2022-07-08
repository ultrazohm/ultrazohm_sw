/*
 * File Name:         C:\ultrazohm_sw\ip_cores\FCS_MPC_3Phase_SPMSM\test_ipcore\ipcore\Test_FCS_MPC_3Phase_SPMSM_IP_Core_v1_0\include\Test_FCS_MPC_3Phase_SPMSM_IP_Core_addr.h
 * Description:       C Header File
 * Created:           2022-07-08 11:04:11
*/

#ifndef TEST_FCS_MPC_3PHASE_SPMSM_IP_CORE_H_
#define TEST_FCS_MPC_3PHASE_SPMSM_IP_CORE_H_

#define  IPCore_Reset_Test_FCS_MPC_3Phase_SPMSM_IP_Core             0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_Test_FCS_MPC_3Phase_SPMSM_IP_Core            0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_Test_FCS_MPC_3Phase_SPMSM_IP_Core         0x8  //contains unique IP timestamp (yymmddHHMM): 2207081104
#define  u_dc_link_AXI_Data_Test_FCS_MPC_3Phase_SPMSM_IP_Core       0x100  //data register for Inport u_dc_link_AXI
#define  SampleTime_AXI_Data_Test_FCS_MPC_3Phase_SPMSM_IP_Core      0x104  //data register for Inport SampleTime_AXI
#define  Rs_AXI_Data_Test_FCS_MPC_3Phase_SPMSM_IP_Core              0x108  //data register for Inport Rs_AXI
#define  reciprocal_Ls_AXI_Data_Test_FCS_MPC_3Phase_SPMSM_IP_Core   0x10C  //data register for Inport reciprocal_Ls_AXI
#define  psiPM_AXI_Data_Test_FCS_MPC_3Phase_SPMSM_IP_Core           0x114  //data register for Inport psiPM_AXI
#define  pole_pairs_AXI_Data_Test_FCS_MPC_3Phase_SPMSM_IP_Core      0x118  //data register for Inport pole_pairs_AXI

#endif /* TEST_FCS_MPC_3PHASE_SPMSM_IP_CORE_H_ */
