/*
 * File Name:         C:\ultrazohm_sw\ip_cores\parallel_phase_voltages_6Phase\ipcore\Parallel_phase_voltages_6Phase_v1_0\include\Parallel_phase_voltages_6Phase_addr.h
 * Description:       C Header File
 * Created:           2022-09-29 14:34:51
*/

#ifndef PARALLEL_PHASE_VOLTAGES_6PHASE_H_
#define PARALLEL_PHASE_VOLTAGES_6PHASE_H_

#define  IPCore_Reset_Parallel_phase_voltages_6Phase                                0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_Parallel_phase_voltages_6Phase                               0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_Parallel_phase_voltages_6Phase                            0x8  //contains unique IP timestamp (yymmddHHMM): 2209291434
#define  theta_el_offset_AXI_Data_Parallel_phase_voltages_6Phase                    0x100  //data register for Inport theta_el_offset_AXI
#define  u_dc_link_voltage_AXI_Data_Parallel_phase_voltages_6Phase                  0x104  //data register for Inport u_dc_link_voltage_AXI
#define  use_AXI_Data_Parallel_phase_voltages_6Phase                                0x108  //data register for Inport use_AXI
#define  theta_el_AXI_Data_Parallel_phase_voltages_6Phase                           0x10C  //data register for Inport theta_el_AXI
#define  Index_AXI_Data_Parallel_phase_voltages_6Phase                              0x110  //data register for Inport Index_AXI
#define  d_voltage_per_switching_state_AXI_1_Data_Parallel_phase_voltages_6Phase    0x114  //data register for Outport d_voltage_per_switching_state_AXI_1
#define  q_voltage_per_switching_state_AXI_1_Data_Parallel_phase_voltages_6Phase    0x118  //data register for Outport q_voltage_per_switching_state_AXI_1
#define  x_voltage_per_switching_state_AXI_1_Data_Parallel_phase_voltages_6Phase    0x11C  //data register for Outport x_voltage_per_switching_state_AXI_1
#define  y_voltage_per_switching_state_AXI_1_Data_Parallel_phase_voltages_6Phase    0x120  //data register for Outport y_voltage_per_switching_state_AXI_1
#define  d_voltage_per_switching_state_AXI_2_Data_Parallel_phase_voltages_6Phase    0x124  //data register for Outport d_voltage_per_switching_state_AXI_2
#define  q_voltage_per_switching_state_AXI_2_Data_Parallel_phase_voltages_6Phase    0x128  //data register for Outport q_voltage_per_switching_state_AXI_2
#define  x_voltage_per_switching_state_AXI_2_Data_Parallel_phase_voltages_6Phase    0x12C  //data register for Outport x_voltage_per_switching_state_AXI_2
#define  y_voltage_per_switching_state_AXI_2_Data_Parallel_phase_voltages_6Phase    0x130  //data register for Outport y_voltage_per_switching_state_AXI_2
#define  d_voltage_per_switching_state_AXI_3_Data_Parallel_phase_voltages_6Phase    0x134  //data register for Outport d_voltage_per_switching_state_AXI_3
#define  q_voltage_per_switching_state_AXI_3_Data_Parallel_phase_voltages_6Phase    0x138  //data register for Outport q_voltage_per_switching_state_AXI_3
#define  x_voltage_per_switching_state_AXI_3_Data_Parallel_phase_voltages_6Phase    0x13C  //data register for Outport x_voltage_per_switching_state_AXI_3
#define  y_voltage_per_switching_state_AXI_3_Data_Parallel_phase_voltages_6Phase    0x140  //data register for Outport y_voltage_per_switching_state_AXI_3
#define  d_voltage_per_switching_state_AXI_4_Data_Parallel_phase_voltages_6Phase    0x144  //data register for Outport d_voltage_per_switching_state_AXI_4
#define  q_voltage_per_switching_state_AXI_4_Data_Parallel_phase_voltages_6Phase    0x148  //data register for Outport q_voltage_per_switching_state_AXI_4
#define  x_voltage_per_switching_state_AXI_4_Data_Parallel_phase_voltages_6Phase    0x14C  //data register for Outport x_voltage_per_switching_state_AXI_4
#define  y_voltage_per_switching_state_AXI_4_Data_Parallel_phase_voltages_6Phase    0x150  //data register for Outport y_voltage_per_switching_state_AXI_4
#define  d_voltage_per_switching_state_AXI_5_Data_Parallel_phase_voltages_6Phase    0x154  //data register for Outport d_voltage_per_switching_state_AXI_5
#define  q_voltage_per_switching_state_AXI_5_Data_Parallel_phase_voltages_6Phase    0x158  //data register for Outport q_voltage_per_switching_state_AXI_5
#define  x_voltage_per_switching_state_AXI_5_Data_Parallel_phase_voltages_6Phase    0x15C  //data register for Outport x_voltage_per_switching_state_AXI_5
#define  y_voltage_per_switching_state_AXI_5_Data_Parallel_phase_voltages_6Phase    0x160  //data register for Outport y_voltage_per_switching_state_AXI_5
#define  d_voltage_per_switching_state_AXI_6_Data_Parallel_phase_voltages_6Phase    0x164  //data register for Outport d_voltage_per_switching_state_AXI_6
#define  q_voltage_per_switching_state_AXI_6_Data_Parallel_phase_voltages_6Phase    0x168  //data register for Outport q_voltage_per_switching_state_AXI_6
#define  x_voltage_per_switching_state_AXI_6_Data_Parallel_phase_voltages_6Phase    0x16C  //data register for Outport x_voltage_per_switching_state_AXI_6
#define  y_voltage_per_switching_state_AXI_6_Data_Parallel_phase_voltages_6Phase    0x170  //data register for Outport y_voltage_per_switching_state_AXI_6
#define  d_voltage_per_switching_state_AXI_7_Data_Parallel_phase_voltages_6Phase    0x174  //data register for Outport d_voltage_per_switching_state_AXI_7
#define  q_voltage_per_switching_state_AXI_7_Data_Parallel_phase_voltages_6Phase    0x178  //data register for Outport q_voltage_per_switching_state_AXI_7
#define  x_voltage_per_switching_state_AXI_7_Data_Parallel_phase_voltages_6Phase    0x17C  //data register for Outport x_voltage_per_switching_state_AXI_7
#define  y_voltage_per_switching_state_AXI_7_Data_Parallel_phase_voltages_6Phase    0x180  //data register for Outport y_voltage_per_switching_state_AXI_7
#define  d_voltage_per_switching_state_AXI_8_Data_Parallel_phase_voltages_6Phase    0x184  //data register for Outport d_voltage_per_switching_state_AXI_8
#define  q_voltage_per_switching_state_AXI_8_Data_Parallel_phase_voltages_6Phase    0x188  //data register for Outport q_voltage_per_switching_state_AXI_8
#define  x_voltage_per_switching_state_AXI_8_Data_Parallel_phase_voltages_6Phase    0x18C  //data register for Outport x_voltage_per_switching_state_AXI_8
#define  y_voltage_per_switching_state_AXI_8_Data_Parallel_phase_voltages_6Phase    0x190  //data register for Outport y_voltage_per_switching_state_AXI_8
#define  d_voltage_per_switching_state_AXI_9_Data_Parallel_phase_voltages_6Phase    0x194  //data register for Outport d_voltage_per_switching_state_AXI_9
#define  q_voltage_per_switching_state_AXI_9_Data_Parallel_phase_voltages_6Phase    0x198  //data register for Outport q_voltage_per_switching_state_AXI_9
#define  x_voltage_per_switching_state_AXI_9_Data_Parallel_phase_voltages_6Phase    0x19C  //data register for Outport x_voltage_per_switching_state_AXI_9
#define  y_voltage_per_switching_state_AXI_9_Data_Parallel_phase_voltages_6Phase    0x1A0  //data register for Outport y_voltage_per_switching_state_AXI_9
#define  d_voltage_per_switching_state_AXI_10_Data_Parallel_phase_voltages_6Phase   0x1A4  //data register for Outport d_voltage_per_switching_state_AXI_10
#define  q_voltage_per_switching_state_AXI_10_Data_Parallel_phase_voltages_6Phase   0x1A8  //data register for Outport q_voltage_per_switching_state_AXI_10
#define  x_voltage_per_switching_state_AXI_10_Data_Parallel_phase_voltages_6Phase   0x1AC  //data register for Outport x_voltage_per_switching_state_AXI_10
#define  y_voltage_per_switching_state_AXI_10_Data_Parallel_phase_voltages_6Phase   0x1B0  //data register for Outport y_voltage_per_switching_state_AXI_10
#define  d_voltage_per_switching_state_AXI_11_Data_Parallel_phase_voltages_6Phase   0x1B4  //data register for Outport d_voltage_per_switching_state_AXI_11
#define  q_voltage_per_switching_state_AXI_11_Data_Parallel_phase_voltages_6Phase   0x1B8  //data register for Outport q_voltage_per_switching_state_AXI_11
#define  x_voltage_per_switching_state_AXI_11_Data_Parallel_phase_voltages_6Phase   0x1BC  //data register for Outport x_voltage_per_switching_state_AXI_11
#define  y_voltage_per_switching_state_AXI_11_Data_Parallel_phase_voltages_6Phase   0x1C0  //data register for Outport y_voltage_per_switching_state_AXI_11
#define  d_voltage_per_switching_state_AXI_12_Data_Parallel_phase_voltages_6Phase   0x1C4  //data register for Outport d_voltage_per_switching_state_AXI_12
#define  q_voltage_per_switching_state_AXI_12_Data_Parallel_phase_voltages_6Phase   0x1C8  //data register for Outport q_voltage_per_switching_state_AXI_12
#define  x_voltage_per_switching_state_AXI_12_Data_Parallel_phase_voltages_6Phase   0x1CC  //data register for Outport x_voltage_per_switching_state_AXI_12
#define  y_voltage_per_switching_state_AXI_12_Data_Parallel_phase_voltages_6Phase   0x1D0  //data register for Outport y_voltage_per_switching_state_AXI_12
#define  d_voltage_per_switching_state_AXI_13_Data_Parallel_phase_voltages_6Phase   0x1D4  //data register for Outport d_voltage_per_switching_state_AXI_13
#define  q_voltage_per_switching_state_AXI_13_Data_Parallel_phase_voltages_6Phase   0x1D8  //data register for Outport q_voltage_per_switching_state_AXI_13
#define  x_voltage_per_switching_state_AXI_13_Data_Parallel_phase_voltages_6Phase   0x1DC  //data register for Outport x_voltage_per_switching_state_AXI_13
#define  y_voltage_per_switching_state_AXI_13_Data_Parallel_phase_voltages_6Phase   0x1E0  //data register for Outport y_voltage_per_switching_state_AXI_13
#define  d_voltage_per_switching_state_AXI_14_Data_Parallel_phase_voltages_6Phase   0x1E4  //data register for Outport d_voltage_per_switching_state_AXI_14
#define  q_voltage_per_switching_state_AXI_14_Data_Parallel_phase_voltages_6Phase   0x1E8  //data register for Outport q_voltage_per_switching_state_AXI_14
#define  x_voltage_per_switching_state_AXI_14_Data_Parallel_phase_voltages_6Phase   0x1EC  //data register for Outport x_voltage_per_switching_state_AXI_14
#define  y_voltage_per_switching_state_AXI_14_Data_Parallel_phase_voltages_6Phase   0x1F0  //data register for Outport y_voltage_per_switching_state_AXI_14
#define  d_voltage_per_switching_state_AXI_15_Data_Parallel_phase_voltages_6Phase   0x1F4  //data register for Outport d_voltage_per_switching_state_AXI_15
#define  q_voltage_per_switching_state_AXI_15_Data_Parallel_phase_voltages_6Phase   0x1F8  //data register for Outport q_voltage_per_switching_state_AXI_15
#define  x_voltage_per_switching_state_AXI_15_Data_Parallel_phase_voltages_6Phase   0x1FC  //data register for Outport x_voltage_per_switching_state_AXI_15
#define  y_voltage_per_switching_state_AXI_15_Data_Parallel_phase_voltages_6Phase   0x200  //data register for Outport y_voltage_per_switching_state_AXI_15
#define  d_voltage_per_switching_state_AXI_16_Data_Parallel_phase_voltages_6Phase   0x204  //data register for Outport d_voltage_per_switching_state_AXI_16
#define  q_voltage_per_switching_state_AXI_16_Data_Parallel_phase_voltages_6Phase   0x208  //data register for Outport q_voltage_per_switching_state_AXI_16
#define  x_voltage_per_switching_state_AXI_16_Data_Parallel_phase_voltages_6Phase   0x20C  //data register for Outport x_voltage_per_switching_state_AXI_16
#define  y_voltage_per_switching_state_AXI_16_Data_Parallel_phase_voltages_6Phase   0x210  //data register for Outport y_voltage_per_switching_state_AXI_16

#endif /* PARALLEL_PHASE_VOLTAGES_6PHASE_H_ */
