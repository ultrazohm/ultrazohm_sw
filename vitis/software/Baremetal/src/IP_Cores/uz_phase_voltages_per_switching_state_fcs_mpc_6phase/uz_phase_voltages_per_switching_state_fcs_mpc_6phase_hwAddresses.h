#pragma once

#define  IPCore_Reset_Phase_voltages_per_switching_state_MPC_6Phase                             0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_Phase_voltages_per_switching_state_MPC_6Phase                            0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_Phase_voltages_per_switching_state_MPC_6Phase                         0x8  //contains unique IP timestamp (yymmddHHMM): 2209011037
#define  theta_el_offset_AXI_Data_Phase_voltages_per_switching_state_MPC_6Phase                 0x100  //data register for Inport theta_el_offset_AXI
#define  u_dc_link_voltage_AXI_Data_Phase_voltages_per_switching_state_MPC_6Phase               0x104  //data register for Inport u_dc_link_voltage_AXI
#define  use_AXI_Data_Phase_voltages_per_switching_state_MPC_6Phase                             0x108  //data register for Inport use_AXI
#define  theta_el_AXI_Data_Phase_voltages_per_switching_state_MPC_6Phase                        0x10C  //data register for Inport theta_el_AXI
#define  Index_AXI_Data_Phase_voltages_per_switching_state_MPC_6Phase                           0x110  //data register for Inport Index_AXI
#define  d_voltage_per_switching_state_AXI_Data_Phase_voltages_per_switching_state_MPC_6Phase   0x114  //data register for Outport d_voltage_per_switching_state_AXI
#define  q_voltage_per_switching_state_AXI_Data_Phase_voltages_per_switching_state_MPC_6Phase   0x118  //data register for Outport q_voltage_per_switching_state_AXI
#define  x_voltage_per_switching_state_AXI_Data_Phase_voltages_per_switching_state_MPC_6Phase   0x11C  //data register for Outport x_voltage_per_switching_state_AXI
#define  y_voltage_per_switching_state_AXI_Data_Phase_voltages_per_switching_state_MPC_6Phase   0x120  //data register for Outport y_voltage_per_switching_state_AXI