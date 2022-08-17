#pragma once

#define  IPCore_Reset_VSD_and_Park_transformation            0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_VSD_and_Park_transformation           0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_VSD_and_Park_transformation        0x8  //contains unique IP timestamp (yymmddHHMM): 2208171005
#define  theta_el_offset__Data_VSD_and_Park_transformation   0x100  //data register for Inport theta_el_offset_
#define  i_alpha_axi_Data_VSD_and_Park_transformation        0x104  //data register for Outport i_alpha_axi
#define  i_beta_axi_Data_VSD_and_Park_transformation         0x108  //data register for Outport i_beta_axi
#define  i_d_axi_Data_VSD_and_Park_transformation            0x10C  //data register for Outport i_d_axi
#define  i_q_axi_Data_VSD_and_Park_transformation            0x110  //data register for Outport i_q_axi
#define  i_x_axi_Data_VSD_and_Park_transformation            0x114  //data register for Outport i_x_axi
#define  i_y_axi_Data_VSD_and_Park_transformation            0x118  //data register for Outport i_y_axi
#define  i_0_plus_axi_Data_VSD_and_Park_transformation       0x11C  //data register for Outport i_0_plus_axi
#define  i_0_minus_axi_Data_VSD_and_Park_transformation      0x120  //data register for Outport i_0_minus_axi
#define  i_a1_axi_Data_VSD_and_Park_transformation           0x124  //data register for Outport i_a1_axi
#define  i_b1_axi_Data_VSD_and_Park_transformation           0x128  //data register for Outport i_b1_axi
#define  i_c1_axi_Data_VSD_and_Park_transformation           0x12C  //data register for Outport i_c1_axi
#define  i_a2_axi_Data_VSD_and_Park_transformation           0x130  //data register for Outport i_a2_axi
#define  i_b2_axi_Data_VSD_and_Park_transformation           0x134  //data register for Outport i_b2_axi
#define  i_c2_axi_Data_VSD_and_Park_transformation           0x138  //data register for Outport i_c2_axi