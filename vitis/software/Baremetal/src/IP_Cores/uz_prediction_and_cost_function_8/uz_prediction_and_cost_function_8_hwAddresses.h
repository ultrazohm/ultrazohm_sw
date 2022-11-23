#pragma once

#define  IPCore_Reset_parallel_8_sim_prediction_and_cost_function                                 0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_parallel_8_sim_prediction_and_cost_function                                0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_parallel_8_sim_prediction_and_cost_function                             0x8  //contains unique IP timestamp (yymmddHHMM): 2211191354
#define  Lq_AXI_Data_parallel_8_sim_prediction_and_cost_function                                  0x100  //data register for Inport Lq_AXI
#define  Ld_AXI_Data_parallel_8_sim_prediction_and_cost_function                                  0x104  //data register for Inport Ld_AXI
#define  SampleTime_div_Ld_AXI_Data_parallel_8_sim_prediction_and_cost_function                   0x108  //data register for Inport SampleTime_div_Ld_AXI
#define  SampleTime_div_Lq_AXI_Data_parallel_8_sim_prediction_and_cost_function                   0x10C  //data register for Inport SampleTime_div_Lq_AXI
#define  SampleTime_div_Lx_AXI_Data_parallel_8_sim_prediction_and_cost_function                   0x110  //data register for Inport SampleTime_div_Lx_AXI
#define  pole_pairs_AXI_Data_parallel_8_sim_prediction_and_cost_function                          0x114  //data register for Inport pole_pairs_AXI
#define  SampleTime_div_Ly_AXI_Data_parallel_8_sim_prediction_and_cost_function                   0x118  //data register for Inport SampleTime_div_Ly_AXI
#define  Rs_AXI_Data_parallel_8_sim_prediction_and_cost_function                                  0x11C  //data register for Inport Rs_AXI
#define  psiPM_AXI_Data_parallel_8_sim_prediction_and_cost_function                               0x120  //data register for Inport psiPM_AXI
#define  id_ref_AXI_Data_parallel_8_sim_prediction_and_cost_function                              0x124  //data register for Inport id_ref_AXI
#define  iq_ref_AXI_Data_parallel_8_sim_prediction_and_cost_function                              0x128  //data register for Inport iq_ref_AXI
#define  ix_ref_AXI_Data_parallel_8_sim_prediction_and_cost_function                              0x12C  //data register for Inport ix_ref_AXI
#define  iy_ref_AXI_Data_parallel_8_sim_prediction_and_cost_function                              0x130  //data register for Inport iy_ref_AXI
#define  Index_AXI_Data_parallel_8_sim_prediction_and_cost_function                               0x134  //data register for Outport Index_AXI
#define  done_vsd_and_park_Data_parallel_8_sim_prediction_and_cost_function                       0x13C  //data register for Inport done_vsd_and_park
#define  current_valid_in_Data_parallel_8_sim_prediction_and_cost_function                        0x140  //data register for Inport current_valid_in
#define  done_prediction_and_cost_function_AXI_Data_parallel_8_sim_prediction_and_cost_function   0x144  //data register for Outport done_prediction_and_cost_function_AXI
