/*
 * File Name:         hdl_prj\ipcore\delay_com_ip_v1_0\include\delay_com_ip_addr.h
 * Description:       C Header File
 * Created:           2022-08-23 18:41:57
*/

#ifndef DELAY_COM_IP_H_
#define DELAY_COM_IP_H_

#define  IPCore_Reset_delay_com_ip                   0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_delay_com_ip                  0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_delay_com_ip               0x8  //contains unique IP timestamp (yymmddHHMM): 2208231841
#define  omega_m_pu_Data_delay_com_ip                0x100  //data register for Inport omega_m_pu
#define  id_pred_pu_AXI_Data_delay_com_ip            0x104  //data register for Outport id_pred_pu_AXI
#define  iq_pred_pu_AXI_Data_delay_com_ip            0x108  //data register for Outport iq_pred_pu_AXI
#define  ix_pred_pu_AXI_Data_delay_com_ip            0x10C  //data register for Outport ix_pred_pu_AXI
#define  iy_pred_pu_AXI_Data_delay_com_ip            0x110  //data register for Outport iy_pred_pu_AXI
#define  Rs_over_ZB_AXI_Data_delay_com_ip            0x118  //data register for Inport Rs_over_ZB_AXI
#define  Ts_times_ZB_over_Ld_AXI_Data_delay_com_ip   0x11C  //data register for Inport Ts_times_ZB_over_Ld_AXI
#define  Ts_times_ZB_over_Lq_AXI_Data_delay_com_ip   0x120  //data register for Inport Ts_times_ZB_over_Lq_AXI
#define  Ts_times_ZB_over_Lx_AXI_Data_delay_com_ip   0x124  //data register for Inport Ts_times_ZB_over_Lx_AXI
#define  Ts_times_ZB_over_Ly_AXI_Data_delay_com_ip   0x128  //data register for Inport Ts_times_ZB_over_Ly_AXI
#define  Ld_over_LB_AXI_Data_delay_com_ip            0x12C  //data register for Inport Ld_over_LB_AXI
#define  Lq_over_LB_AXI_Data_delay_com_ip            0x130  //data register for Inport Lq_over_LB_AXI
#define  psi_pm_over_psiB_AXI_Data_delay_com_ip      0x138  //data register for Inport psi_pm_over_psiB_AXI
#define  polepairs_AXI_Data_delay_com_ip             0x13C  //data register for Inport polepairs_AXI

#endif /* DELAY_COM_IP_H_ */
