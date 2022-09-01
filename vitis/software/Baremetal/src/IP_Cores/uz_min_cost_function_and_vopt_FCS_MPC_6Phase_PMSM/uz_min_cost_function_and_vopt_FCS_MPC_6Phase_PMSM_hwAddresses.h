#pragma once

#define  IPCore_Reset_min_cost_function_and_vopt_FCS_MPC_6Phase                                    0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_min_cost_function_and_vopt_FCS_MPC_6Phase                                   0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_min_cost_function_and_vopt_FCS_MPC_6Phase                                0x8  //contains unique IP timestamp (yymmddHHMM): 2209010959
#define  use_AXI_Data_min_cost_function_and_vopt_FCS_MPC_6Phase                                    0x100  //data register for Inport use_AXI
#define  J_in_AXI_Data_min_cost_function_and_vopt_FCS_MPC_6Phase                                   0x104  //data register for Inport J_in_AXI
#define  Index_in_AXI_Data_min_cost_function_and_vopt_FCS_MPC_6Phase                               0x108  //data register for Inport Index_in_AXI
#define  d_phase_voltage_per_switchimng_state_AXI_Data_min_cost_function_and_vopt_FCS_MPC_6Phase   0x10C  //data register for Inport d_phase_voltage_per_switchimng_state_AXI
#define  q_phase_voltage_per_switchimng_state_AXI_Data_min_cost_function_and_vopt_FCS_MPC_6Phase   0x110  //data register for Inport q_phase_voltage_per_switchimng_state_AXI
#define  x_phase_voltage_per_switchimng_state_AXI_Data_min_cost_function_and_vopt_FCS_MPC_6Phase   0x114  //data register for Inport x_phase_voltage_per_switchimng_state_AXI
#define  y_phase_voltage_per_switchimng_state_AXI_Data_min_cost_function_and_vopt_FCS_MPC_6Phase   0x118  //data register for Inport y_phase_voltage_per_switchimng_state_AXI
#define  valid_in_AXI_Data_min_cost_function_and_vopt_FCS_MPC_6Phase                               0x11C  //data register for Inport valid_in_AXI
#define  last_applied_optimal_voltage_uy_AXI_Data_min_cost_function_and_vopt_FCS_MPC_6Phase        0x120  //data register for Outport last_applied_optimal_voltage_uy_AXI
#define  last_applied_optimal_voltage_ux_AXI_Data_min_cost_function_and_vopt_FCS_MPC_6Phase        0x124  //data register for Outport last_applied_optimal_voltage_ux_AXI
#define  last_applied_optimal_voltage_uq_AXI_Data_min_cost_function_and_vopt_FCS_MPC_6Phase        0x128  //data register for Outport last_applied_optimal_voltage_uq_AXI
#define  last_applied_optimal_voltage_ud_AXI_Data_min_cost_function_and_vopt_FCS_MPC_6Phase        0x12C  //data register for Outport last_applied_optimal_voltage_ud_AXI
#define  done_complete_AXI_Data_min_cost_function_and_vopt_FCS_MPC_6Phase                          0x130  //data register for Outport done_complete_AXI
#define  Index_out_AXI_Data_min_cost_function_and_vopt_FCS_MPC_6Phase                              0x134  //data register for Outport Index_out_AXI