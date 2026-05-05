/*
 * File Name:         C:\UltraZohm\ultrazohm_test\ip_cores\uz_Deadbeat\hdl_prj\ipcore\uz_Deadbe_ip_v1_0\include\uz_Deadbe_ip_addr.h
 * Description:       C Header File
 * Created:           2026-04-27 14:06:58
*/

#ifndef UZ_DEADBE_IP_H_
#define UZ_DEADBE_IP_H_

#define  IPCore_Reset_uz_Deadbe_ip        0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_uz_Deadbe_ip       0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_uz_Deadbe_ip    0x8  //contains unique IP timestamp (yymmddHHMM): 2604271406
#define  id_ref_Data_uz_Deadbe_ip         0x100  //data register for Inport id_ref
#define  iq_ref_Data_uz_Deadbe_ip         0x104  //data register for Inport iq_ref
#define  i_d_Data_uz_Deadbe_ip            0x108  //data register for Inport i_d
#define  i_q_Data_uz_Deadbe_ip            0x10C  //data register for Inport i_q
#define  sin_e_Data_uz_Deadbe_ip          0x110  //data register for Inport sin_e
#define  cos_e_Data_uz_Deadbe_ip          0x114  //data register for Inport cos_e
#define  sin_k1_Data_uz_Deadbe_ip         0x118  //data register for Inport sin_k1
#define  cos_k1_Data_uz_Deadbe_ip         0x11C  //data register for Inport cos_k1
#define  w_r_Data_uz_Deadbe_ip            0x120  //data register for Inport w_r
#define  rs_pm_Data_uz_Deadbe_ip          0x124  //data register for Inport rs_pm
#define  psi_pm_Data_uz_Deadbe_ip         0x128  //data register for Inport psi_pm
#define  inv_half_Vdc_Data_uz_Deadbe_ip   0x12C  //data register for Inport inv_half_Vdc
#define  Ts_Ld_Data_uz_Deadbe_ip          0x130  //data register for Inport Ts_Ld
#define  ld_pm_Data_uz_Deadbe_ip          0x134  //data register for Inport ld_pm
#define  lq_pm_Data_uz_Deadbe_ip          0x138  //data register for Inport lq_pm
#define  Ts_Lq_Data_uz_Deadbe_ip          0x13C  //data register for Inport Ts_Lq
#define  RsTs_Ld_Data_uz_Deadbe_ip        0x140  //data register for Inport RsTs_Ld
#define  RsTs_Lq_Data_uz_Deadbe_ip        0x144  //data register for Inport RsTs_Lq
#define  LqLdTs_Data_uz_Deadbe_ip         0x148  //data register for Inport LqLdTs
#define  LdLqTs_Data_uz_Deadbe_ip         0x14C  //data register for Inport LdLqTs
#define  TsPsi_Lq_Data_uz_Deadbe_ip       0x150  //data register for Inport TsPsi_Lq
#define  v_dc_half_Data_uz_Deadbe_ip      0x154  //data register for Inport v_dc_half
#define  Ld_Ts_Data_uz_Deadbe_ip          0x158  //data register for Inport Ld_Ts
#define  Lq_Ts_Data_uz_Deadbe_ip          0x15C  //data register for Inport Lq_Ts
#define  d_a_Data_uz_Deadbe_ip            0x160  //data register for Outport d_a
#define  d_b_Data_uz_Deadbe_ip            0x164  //data register for Outport d_b
#define  d_c_Data_uz_Deadbe_ip            0x168  //data register for Outport d_c

#endif /* UZ_DEADBE_IP_H_ */
