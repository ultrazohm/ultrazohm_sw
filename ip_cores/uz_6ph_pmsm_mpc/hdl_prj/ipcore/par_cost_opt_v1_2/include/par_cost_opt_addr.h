/*
 * File Name:         hdl_prj\ipcore\par_cost_opt_v1_2\include\par_cost_opt_addr.h
 * Description:       C Header File
 * Created:           2025-01-21 10:32:27
*/

#ifndef PAR_COST_OPT_H_
#define PAR_COST_OPT_H_

#define  IPCore_Reset_par_cost_opt              0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_par_cost_opt             0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_par_cost_opt          0x8  //contains unique IP timestamp (yymmddHHMM): 2501211032
#define  max_current_pu_AXI_Data_par_cost_opt   0x110  //data register for Inport max_current_pu_AXI
#define  lambda_d_AXI_Data_par_cost_opt         0x114  //data register for Inport lambda_d_AXI
#define  lambda_q_AXI_Data_par_cost_opt         0x118  //data register for Inport lambda_q_AXI
#define  lambda_x_AXI_Data_par_cost_opt         0x11C  //data register for Inport lambda_x_AXI
#define  lambda_y_AXI_Data_par_cost_opt         0x120  //data register for Inport lambda_y_AXI
#define  lambda_u_AXI_Data_par_cost_opt         0x124  //data register for Inport lambda_u_AXI
#define  index_offset_AXI_Data_par_cost_opt     0x128  //data register for Inport index_offset_AXI
#define  index_limit_AXI_Data_par_cost_opt      0x12C  //data register for Inport index_limit_AXI

#endif /* PAR_COST_OPT_H_ */
