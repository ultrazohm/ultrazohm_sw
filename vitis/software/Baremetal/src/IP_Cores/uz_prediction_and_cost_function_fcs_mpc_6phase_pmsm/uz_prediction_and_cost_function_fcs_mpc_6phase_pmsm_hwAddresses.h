#pragma once

#define  IPCore_Reset_Prediction_and_cost_FCS_MPC_6Phase_PMSM                             0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_Prediction_and_cost_FCS_MPC_6Phase_PMSM                            0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_Prediction_and_cost_FCS_MPC_6Phase_PMSM                         0x8  //contains unique IP timestamp (yymmddHHMM): 2208250951: 2208250954
#define  Lq_AXI_Data_Prediction_and_cost_FCS_MPC_6Phase_PMSM                              0x100  //data register for Inport Lq_AXI
#define  Ld_AXI_Data_Prediction_and_cost_FCS_MPC_6Phase_PMSM                              0x104  //data register for Inport Ld_AXI
#define  SampleTime_div_Ld_AXI_Data_Prediction_and_cost_FCS_MPC_6Phase_PMSM               0x108  //data register for Inport SampleTime_div_Ld_AXI
#define  SampleTime_div_Lq_AXI_Data_Prediction_and_cost_FCS_MPC_6Phase_PMSM               0x10C  //data register for Inport SampleTime_div_Lq_AXI
#define  SampleTime_div_Lx_AXI_Data_Prediction_and_cost_FCS_MPC_6Phase_PMSM               0x110  //data register for Inport SampleTime_div_Lx_AXI
#define  pole_pairs_AXI_Data_Prediction_and_cost_FCS_MPC_6Phase_PMSM                      0x114  //data register for Inport pole_pairs_AXI
#define  SampleTime_div_Ly_AXI_Data_Prediction_and_cost_FCS_MPC_6Phase_PMSM               0x118  //data register for Inport SampleTime_div_Ly_AXI
#define  Rs_AXI_Data_Prediction_and_cost_FCS_MPC_6Phase_PMSM                              0x11C  //data register for Inport Rs_AXI
#define  psiPM_AXI_Data_Prediction_and_cost_FCS_MPC_6Phase_PMSM                           0x120  //data register for Inport psiPM_AXI
#define  id_ref_AXI_Data_Prediction_and_cost_FCS_MPC_6Phase_PMSM                          0x124  //data register for Inport id_ref_AXI
#define  iq_ref_AXI_Data_Prediction_and_cost_FCS_MPC_6Phase_PMSM                          0x128  //data register for Inport iq_ref_AXI
#define  ix_ref_AXI_Data_Prediction_and_cost_FCS_MPC_6Phase_PMSM                          0x12C  //data register for Inport ix_ref_AXI
#define  iy_ref_AXI_Data_Prediction_and_cost_FCS_MPC_6Phase_PMSM                          0x130  //data register for Inport iy_ref_AXI
#define  use_AXI_Data_Prediction_and_cost_FCS_MPC_6Phase_PMSM                             0x134  //data register for Inport use_AXI
#define  id_k_1_AXI_Data_Prediction_and_cost_FCS_MPC_6Phase_PMSM                          0x138  //data register for Inport id_k_1_AXI
#define  iq_k_1_AXI_Data_Prediction_and_cost_FCS_MPC_6Phase_PMSM                          0x13C  //data register for Inport iq_k_1_AXI
#define  ix_k_1_AXI_Data_Prediction_and_cost_FCS_MPC_6Phase_PMSM                          0x140  //data register for Inport ix_k_1_AXI
#define  iy_k_1_AXI_Data_Prediction_and_cost_FCS_MPC_6Phase_PMSM                          0x144  //data register for Inport iy_k_1_AXI
#define  omega_m_measured_AXI_Data_Prediction_and_cost_FCS_MPC_6Phase_PMSM                0x148  //data register for Inport omega_m_measured_AXI
#define  d_voltage_per_switching_state_AXI_Data_Prediction_and_cost_FCS_MPC_6Phase_PMSM   0x14C  //data register for Inport d_voltage_per_switching_state_AXI
#define  q_voltage_per_switching_state_AXI_Data_Prediction_and_cost_FCS_MPC_6Phase_PMSM   0x150  //data register for Inport q_voltage_per_switching_state_AXI
#define  x_voltage_per_switching_state_AXI_Data_Prediction_and_cost_FCS_MPC_6Phase_PMSM   0x154  //data register for Inport x_voltage_per_switching_state_AXI
#define  y_volatge_per_switching_state_AXI_Data_Prediction_and_cost_FCS_MPC_6Phase_PMSM   0x158  //data register for Inport y_volatge_per_switching_state_AXI
#define  J_AXI_Data_Prediction_and_cost_FCS_MPC_6Phase_PMSM                               0x15C  //data register for Outport J_AXI