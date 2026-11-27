/*
 * File Name:         /home/ts/Documents/compare_repo/ultrazohm_sw/ip_cores/uz_sogipll/hdl_prj/ipcore/uz_sogipl_ip_v1_0/include/uz_sogipl_ip_addr.h
 * Description:       C Header File
 * Created:           2026-11-27 12:04:19
*/

#ifndef UZ_SOGIPL_IP_H_
#define UZ_SOGIPL_IP_H_

#define  IPCore_Reset_uz_sogipl_ip         0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_uz_sogipl_ip        0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_uz_sogipl_ip     0x8  //contains unique IP timestamp (yymmddHHMM): 2611271204
#define  in_rst_Data_uz_sogipl_ip          0x100  //data register for Inport in_rst
#define  in_v_Data_uz_sogipl_ip            0x104  //data register for Inport in_v
#define  in_omega_ff_Data_uz_sogipl_ip     0x108  //data register for Inport in_omega_ff
#define  in_k_Data_uz_sogipl_ip            0x10C  //data register for Inport in_k
#define  in_kp_Data_uz_sogipl_ip           0x110  //data register for Inport in_kp
#define  in_ki_Data_uz_sogipl_ip           0x114  //data register for Inport in_ki
#define  in_t_sample_Data_uz_sogipl_ip     0x118  //data register for Inport in_t_sample
#define  in_v_scaling_Data_uz_sogipl_ip    0x11C  //data register for Inport in_v_scaling
#define  out_v_est_Data_uz_sogipl_ip       0x120  //data register for Outport out_v_est
#define  out_qv_est_Data_uz_sogipl_ip      0x124  //data register for Outport out_qv_est
#define  out_v_d_Data_uz_sogipl_ip         0x128  //data register for Outport out_v_d
#define  out_v_q_Data_uz_sogipl_ip         0x12C  //data register for Outport out_v_q
#define  out_theta_est_Data_uz_sogipl_ip   0x130  //data register for Outport out_theta_est
#define  out_omega_est_Data_uz_sogipl_ip   0x134  //data register for Outport out_omega_est

#endif /* UZ_SOGIPL_IP_H_ */
