/*
 * File Name:         hdl_prj\ipcore\delay_comp_sum4_2724_v1_0\include\delay_comp_sum4_2724_addr.h
 * Description:       C Header File
 * Created:           2024-03-28 16:29:21
*/

#ifndef DELAY_COMP_SUM4_2724_H_
#define DELAY_COMP_SUM4_2724_H_

#define  IPCore_Reset_delay_comp_sum4_2724                   0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_delay_comp_sum4_2724                  0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_delay_comp_sum4_2724               0x8  //contains unique IP timestamp (yymmddHHMM): 2403281629
#define  id_delay_pu_AXI_Data_delay_comp_sum4_2724           0x104  //data register for Outport id_delay_pu_AXI
#define  iq_delay_pu_AXI_Data_delay_comp_sum4_2724           0x108  //data register for Outport iq_delay_pu_AXI
#define  Rs_over_ZB_AXI_Data_delay_comp_sum4_2724            0x118  //data register for Inport Rs_over_ZB_AXI
#define  Ts_times_ZB_over_Ld_AXI_Data_delay_comp_sum4_2724   0x11C  //data register for Inport Ts_times_ZB_over_Ld_AXI
#define  Ts_times_ZB_over_Lq_AXI_Data_delay_comp_sum4_2724   0x120  //data register for Inport Ts_times_ZB_over_Lq_AXI
#define  Ld_over_LB_AXI_Data_delay_comp_sum4_2724            0x12C  //data register for Inport Ld_over_LB_AXI
#define  Lq_over_LB_AXI_Data_delay_comp_sum4_2724            0x130  //data register for Inport Lq_over_LB_AXI
#define  psi_pm_over_psiB_AXI_Data_delay_comp_sum4_2724      0x138  //data register for Inport psi_pm_over_psiB_AXI
#define  polepairs_AXI_Data_delay_comp_sum4_2724             0x13C  //data register for Inport polepairs_AXI

#endif /* DELAY_COMP_SUM4_2724_H_ */
