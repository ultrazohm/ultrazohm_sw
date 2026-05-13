/*
 * File Name:         C:\UltraZohm\ultrazohm_fpga_control\ultrazohm_sw\ip_cores\uz_Deadbeat\hdj_prj\ipcore\uz_Deadbeat_ip_v1_0\include\uz_Deadbeat_ip_addr.h
 * Description:       C Header File
 * Created:           2026-05-11 11:24:51
*/

#ifndef UZ_DEADBEAT_IP_H_
#define UZ_DEADBEAT_IP_H_

#define  IPCore_Reset_uz_Deadbeat_ip       0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_uz_Deadbeat_ip      0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_uz_Deadbeat_ip   0x8  //contains unique IP timestamp (yymmddHHMM): 2605111124
#define  id_ref_Data_uz_Deadbeat_ip        0x100  //data register for Inport id_ref
#define  iq_ref_Data_uz_Deadbeat_ip        0x104  //data register for Inport iq_ref
#define  id_Data_uz_Deadbeat_ip            0x108  //data register for Inport id
#define  iq_Data_uz_Deadbeat_ip            0x10C  //data register for Inport iq
#define  theta_Data_uz_Deadbeat_ip         0x110  //data register for Inport theta
#define  theta_0_Data_uz_Deadbeat_ip       0x114  //data register for Inport theta_0
#define  w_e_Data_uz_Deadbeat_ip           0x118  //data register for Inport w_e
#define  ua_0_input_Data_uz_Deadbeat_ip    0x11C  //data register for Inport ua_0_input
#define  ub_0_input_Data_uz_Deadbeat_ip    0x120  //data register for Inport ub_0_input
#define  uc_0_input_Data_uz_Deadbeat_ip    0x124  //data register for Inport uc_0_input
#define  ua_0_Data_uz_Deadbeat_ip          0x128  //data register for Outport ua_0
#define  ub_o_Data_uz_Deadbeat_ip          0x12C  //data register for Outport ub_o
#define  uc_0_Data_uz_Deadbeat_ip          0x130  //data register for Outport uc_0

#endif /* UZ_DEADBEAT_IP_H_ */
