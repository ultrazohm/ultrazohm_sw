/*
 * File Name:         C:\ultrazohm_sw\ip_cores\parallel_8_vsd_and_park\ipcore\parallel_8_sim_vsd_and_park_v1_0\include\parallel_8_sim_vsd_and_park_addr.h
 * Description:       C Header File
 * Created:           2022-12-22 15:28:11
*/

#ifndef PARALLEL_8_SIM_VSD_AND_PARK_H_
#define PARALLEL_8_SIM_VSD_AND_PARK_H_

#define  IPCore_Reset_parallel_8_sim_vsd_and_park               0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_parallel_8_sim_vsd_and_park              0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_parallel_8_sim_vsd_and_park           0x8  //contains unique IP timestamp (yymmddHHMM): 2212221528
#define  theta_el_offset_AXI_Data_parallel_8_sim_vsd_and_park   0x100  //data register for Inport theta_el_offset_AXI
#define  i_d_AXI_Data_parallel_8_sim_vsd_and_park               0x104  //data register for Outport i_d_AXI
#define  i_q_AXI_Data_parallel_8_sim_vsd_and_park               0x108  //data register for Outport i_q_AXI
#define  i_x_AXI_Data_parallel_8_sim_vsd_and_park               0x10C  //data register for Outport i_x_AXI
#define  i_y_AXI_Data_parallel_8_sim_vsd_and_park               0x110  //data register for Outport i_y_AXI
#define  i_a1_axi_Data_parallel_8_sim_vsd_and_park              0x124  //data register for Outport i_a1_axi
#define  i_b1_axi_Data_parallel_8_sim_vsd_and_park              0x128  //data register for Outport i_b1_axi
#define  i_c1_axi_Data_parallel_8_sim_vsd_and_park              0x12C  //data register for Outport i_c1_axi
#define  i_a2_axi_Data_parallel_8_sim_vsd_and_park              0x130  //data register for Outport i_a2_axi
#define  i_b2_axi_Data_parallel_8_sim_vsd_and_park              0x134  //data register for Outport i_b2_axi
#define  i_c2_axi_Data_parallel_8_sim_vsd_and_park              0x138  //data register for Outport i_c2_axi

#endif /* PARALLEL_8_SIM_VSD_AND_PARK_H_ */
