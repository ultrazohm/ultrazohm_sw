/*
 * File Name:         hdl_prj\ipcore\cost_opt_v1_1\include\cost_opt_addr.h
 * Description:       C Header File
 * Created:           2023-10-04 15:54:50
*/

#ifndef COST_OPT_H_
#define COST_OPT_H_

#define  IPCore_Reset_cost_opt              0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_cost_opt             0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_cost_opt          0x8  //contains unique IP timestamp (yymmddHHMM): 2310041554
#define  id_ref_pu_AXI_Data_cost_opt        0x100  //data register for Inport id_ref_pu_AXI
#define  iq_ref_pu_AXI_Data_cost_opt        0x104  //data register for Inport iq_ref_pu_AXI
#define  max_current_pu_AXI_Data_cost_opt   0x110  //data register for Inport max_current_pu_AXI
#define  lambda_d_AXI_Data_cost_opt         0x114  //data register for Inport lambda_d_AXI
#define  lambda_q_AXI_Data_cost_opt         0x118  //data register for Inport lambda_q_AXI
#define  lambda_u_AXI_Data_cost_opt         0x124  //data register for Inport lambda_u_AXI

#endif /* COST_OPT_H_ */
