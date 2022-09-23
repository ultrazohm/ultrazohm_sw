/*
 * File Name:         hdl_prj\ipcore\uz_6ph_cost_ip_v1_0\include\uz_6ph_cost_ip_addr.h
 * Description:       C Header File
 * Created:           2022-09-23 18:23:43
*/

#ifndef UZ_6PH_COST_IP_H_
#define UZ_6PH_COST_IP_H_

#define  IPCore_Reset_uz_6ph_cost_ip              0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_uz_6ph_cost_ip             0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_uz_6ph_cost_ip          0x8  //contains unique IP timestamp (yymmddHHMM): 2209231823
#define  id_ref_pu_AXI_Data_uz_6ph_cost_ip        0x100  //data register for Inport id_ref_pu_AXI
#define  iq_ref_pu_AXI_Data_uz_6ph_cost_ip        0x104  //data register for Inport iq_ref_pu_AXI
#define  ix_ref_pu_AXI_Data_uz_6ph_cost_ip        0x108  //data register for Inport ix_ref_pu_AXI
#define  iy_ref_pu_AXI_Data_uz_6ph_cost_ip        0x10C  //data register for Inport iy_ref_pu_AXI
#define  max_current_pu_AXI_Data_uz_6ph_cost_ip   0x110  //data register for Inport max_current_pu_AXI
#define  lambda_d_AXI_Data_uz_6ph_cost_ip         0x114  //data register for Inport lambda_d_AXI
#define  lambda_q_AXI_Data_uz_6ph_cost_ip         0x118  //data register for Inport lambda_q_AXI
#define  lambda_x_AXI_Data_uz_6ph_cost_ip         0x11C  //data register for Inport lambda_x_AXI
#define  lambda_y_AXI_Data_uz_6ph_cost_ip         0x120  //data register for Inport lambda_y_AXI
#define  lambda_u_AXI_Data_uz_6ph_cost_ip         0x124  //data register for Inport lambda_u_AXI

#endif /* UZ_6PH_COST_IP_H_ */
