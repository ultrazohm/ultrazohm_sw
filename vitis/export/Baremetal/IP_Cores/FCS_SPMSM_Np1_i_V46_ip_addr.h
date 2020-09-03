/*
 * File Name:         hdl_prj\ipcore\FCS_SPMSM_Np1_i_V46_ip_v1_0\include\FCS_SPMSM_Np1_i_V46_ip_addr.h
 * Description:       C Header File
 * Created:           2018-11-23 15:32:34
*/

#ifndef FCS_SPMSM_NP1_I_V46_IP_H_
#define FCS_SPMSM_NP1_I_V46_IP_H_

#define  IPCore_Reset_FCS_SPMSM_Np1_i_V46_ip              0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_FCS_SPMSM_Np1_i_V46_ip             0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_FCS_SPMSM_Np1_i_V46_ip          0x8  //contains unique IP timestamp (yymmddHHMM): 1811231532
#define  n_ist_AXI_Data_FCS_SPMSM_Np1_i_V46_ip            0x100  //data register for Inport n_ist_AXI
#define  i_soll_AXI_Data_FCS_SPMSM_Np1_i_V46_ip           0x104  //data register for Inport i_soll_AXI
#define  M_L_AXI_Data_FCS_SPMSM_Np1_i_V46_ip              0x108  //data register for Inport M_L_AXI
#define  q_fiq_AXI_Data_FCS_SPMSM_Np1_i_V46_ip            0x10C  //data register for Inport q_fiq_AXI
#define  q_fid_AXI_Data_FCS_SPMSM_Np1_i_V46_ip            0x110  //data register for Inport q_fid_AXI
#define  u_dc_AXI_Data_FCS_SPMSM_Np1_i_V46_ip             0x114  //data register for Inport u_dc_AXI
#define  M_Reib_AXI_Data_FCS_SPMSM_Np1_i_V46_ip           0x118  //data register for Inport M_Reib_AXI
#define  Enable_Control_AXI_Data_FCS_SPMSM_Np1_i_V46_ip   0x11C  //data register for Inport Enable_Control_AXI
#define  Imax_AXI_Data_FCS_SPMSM_Np1_i_V46_ip             0x120  //data register for Inport Imax_AXI
#define  Imin_AXI_Data_FCS_SPMSM_Np1_i_V46_ip             0x124  //data register for Inport Imin_AXI
#define  Rph_AXI_Data_FCS_SPMSM_Np1_i_V46_ip              0x128  //data register for Inport Rph_AXI
#define  Scal_t_AXI_Data_FCS_SPMSM_Np1_i_V46_ip           0x12C  //data register for Inport Scal_t_AXI
#define  Scal_nq_AXI_Data_FCS_SPMSM_Np1_i_V46_ip          0x130  //data register for Inport Scal_nq_AXI
#define  Scal_nd_AXI_Data_FCS_SPMSM_Np1_i_V46_ip          0x134  //data register for Inport Scal_nd_AXI
#define  Scal_t_out_AXI_Data_FCS_SPMSM_Np1_i_V46_ip       0x138  //data register for Outport Scal_t_out_AXI
#define  Scal_nq_out_AXI1_Data_FCS_SPMSM_Np1_i_V46_ip     0x13C  //data register for Outport Scal_nq_out_AXI1
#define  Scal_nd_out_AXI2_Data_FCS_SPMSM_Np1_i_V46_ip     0x140  //data register for Outport Scal_nd_out_AXI2
#define  Rph_out_AXI_Data_FCS_SPMSM_Np1_i_V46_ip          0x144  //data register for Outport Rph_out_AXI
#define  Imin_out_AXI_Data_FCS_SPMSM_Np1_i_V46_ip         0x148  //data register for Outport Imin_out_AXI
#define  Imax_out_AXI_Data_FCS_SPMSM_Np1_i_V46_ip         0x14C  //data register for Outport Imax_out_AXI

#endif /* FCS_SPMSM_NP1_I_V46_IP_H_ */
