/*
 * File Name:         hdl_prj\ipcore\delay_comp_v1_1\include\delay_comp_addr.h
 * Description:       C Header File
 * Created:           2023-07-20 18:53:00
*/

#ifndef DELAY_COMP_H_
#define DELAY_COMP_H_

#define  IPCore_Reset_delay_comp                   0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_delay_comp                  0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_delay_comp               0x8  //contains unique IP timestamp (yymmddHHMM): 2307201852
#define  id_delay_pu_AXI_Data_delay_comp           0x104  //data register for Outport id_delay_pu_AXI
#define  iq_delay_pu_AXI_Data_delay_comp           0x108  //data register for Outport iq_delay_pu_AXI
#define  ix_delay_pu_AXI_Data_delay_comp           0x10C  //data register for Outport ix_delay_pu_AXI
#define  iy_delay_pu_AXI_Data_delay_comp           0x110  //data register for Outport iy_delay_pu_AXI
#define  Rs_over_ZB_AXI_Data_delay_comp            0x118  //data register for Inport Rs_over_ZB_AXI
#define  Ts_times_ZB_over_Ld_AXI_Data_delay_comp   0x11C  //data register for Inport Ts_times_ZB_over_Ld_AXI
#define  Ts_times_ZB_over_Lq_AXI_Data_delay_comp   0x120  //data register for Inport Ts_times_ZB_over_Lq_AXI
#define  Ts_times_ZB_over_Lx_AXI_Data_delay_comp   0x124  //data register for Inport Ts_times_ZB_over_Lx_AXI
#define  Ts_times_ZB_over_Ly_AXI_Data_delay_comp   0x128  //data register for Inport Ts_times_ZB_over_Ly_AXI
#define  Ld_over_LB_AXI_Data_delay_comp            0x12C  //data register for Inport Ld_over_LB_AXI
#define  Lq_over_LB_AXI_Data_delay_comp            0x130  //data register for Inport Lq_over_LB_AXI
#define  psi_pm_over_psiB_AXI_Data_delay_comp      0x138  //data register for Inport psi_pm_over_psiB_AXI
#define  polepairs_AXI_Data_delay_comp             0x13C  //data register for Inport polepairs_AXI

#endif /* DELAY_COMP_H_ */
