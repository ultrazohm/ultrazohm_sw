#pragma once

#define  IPCore_Reset_Delay_compensation_FCS_MPC_6Phase_PMSM                               0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_Delay_compensation_FCS_MPC_6Phase_PMSM                              0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_Delay_compensation_FCS_MPC_6Phase_PMSM                           0x8  //contains unique IP timestamp (yymmddHHMM): 2209010914
#define  psiPM_AXI_Data_Delay_compensation_FCS_MPC_6Phase_PMSM                             0x100  //data register for Inport psiPM_AXI
#define  Lq_AXI_Data_Delay_compensation_FCS_MPC_6Phase_PMSM                                0x104  //data register for Inport Lq_AXI
#define  Ld_AXI_Data_Delay_compensation_FCS_MPC_6Phase_PMSM                                0x108  //data register for Inport Ld_AXI
#define  Rs_AXI_Data_Delay_compensation_FCS_MPC_6Phase_PMSM                                0x10C  //data register for Inport Rs_AXI
#define  SampleTime_div_Ld_AXI_Data_Delay_compensation_FCS_MPC_6Phase_PMSM                 0x110  //data register for Inport SampleTime_div_Ld_AXI
#define  pole_pairs_AXI_Data_Delay_compensation_FCS_MPC_6Phase_PMSM                        0x114  //data register for Inport pole_pairs_AXI
#define  SampleTime_div_Lq_AXI_Data_Delay_compensation_FCS_MPC_6Phase_PMSM                 0x118  //data register for Inport SampleTime_div_Lq_AXI
#define  SampleTime_div_Lx_AXI_Data_Delay_compensation_FCS_MPC_6Phase_PMSM                 0x11C  //data register for Inport SampleTime_div_Lx_AXI
#define  SampleTime_div_Ly_AXI_Data_Delay_compensation_FCS_MPC_6Phase_PMSM                 0x120  //data register for Inport SampleTime_div_Ly_AXI
#define  last_applied_optimal_voltage_ud_AXI_Data_Delay_compensation_FCS_MPC_6Phase_PMSM   0x124  //data register for Inport last_applied_optimal_voltage_ud_AXI
#define  last_applied_optimal_volatge_uq_AXI_Data_Delay_compensation_FCS_MPC_6Phase_PMSM   0x128  //data register for Inport last_applied_optimal_volatge_uq_AXI
#define  last_applied_optimal_voltage_ux_AXI_Data_Delay_compensation_FCS_MPC_6Phase_PMSM   0x12C  //data register for Inport last_applied_optimal_voltage_ux_AXI
#define  last_applied_optimal_voltage_uy_AXI_Data_Delay_compensation_FCS_MPC_6Phase_PMSM   0x130  //data register for Inport last_applied_optimal_voltage_uy_AXI
#define  id_measured_AXI_Data_Delay_compensation_FCS_MPC_6Phase_PMSM                       0x134  //data register for Inport id_measured_AXI
#define  iq_measured_AXI_Data_Delay_compensation_FCS_MPC_6Phase_PMSM                       0x138  //data register for Inport iq_measured_AXI
#define  ix_measured_AXI_Data_Delay_compensation_FCS_MPC_6Phase_PMSM                       0x13C  //data register for Inport ix_measured_AXI
#define  iy_measured_AXI_Data_Delay_compensation_FCS_MPC_6Phase_PMSM                       0x140  //data register for Inport iy_measured_AXI
#define  omega_m_measured_AXI_Data_Delay_compensation_FCS_MPC_6Phase_PMSM                  0x144  //data register for Inport omega_m_measured_AXI
#define  use_AXI_Data_Delay_compensation_FCS_MPC_6Phase_PMSM                               0x148  //data register for Inport use_AXI
#define  id_k_1_AXI_Data_Delay_compensation_FCS_MPC_6Phase_PMSM                            0x14C  //data register for Outport id_k_1_AXI
#define  iq_k_1_AXI_Data_Delay_compensation_FCS_MPC_6Phase_PMSM                            0x150  //data register for Outport iq_k_1_AXI
#define  ix_k_1_AXI_Data_Delay_compensation_FCS_MPC_6Phase_PMSM                            0x154  //data register for Outport ix_k_1_AXI
#define  iy_k_1_AXI_Data_Delay_compensation_FCS_MPC_6Phase_PMSM                            0x158  //data register for Outport iy_k_1_AXI