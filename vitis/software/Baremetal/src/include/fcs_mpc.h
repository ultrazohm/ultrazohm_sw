#include "../main.h"

// uz_sel_currents
#define  IPCore_Reset_uz_sel_currents             0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_uz_sel_currents            0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_uz_sel_currents         0x8  //contains unique IP timestamp (yymmddHHMM): 2310041956
#define  right_or_left_AXI_Data_uz_sel_currents   0x124  //data register for Inport right_or_left_AXI

// uz_sel_resolver
#define  IPCore_Reset_uz_sel_resolver             0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_uz_sel_resolver            0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_uz_sel_resolver         0x8  //contains unique IP timestamp (yymmddHHMM): 2310041727
#define  right_or_left_AXI_Data_uz_sel_resolver   0x124  //data register for Inport right_or_left_AXI

// uz_debug_ip
#define  IPCore_Reset_uz_debug_ip             0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_uz_debug_ip            0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_uz_debug_ip         0x8  //contains unique IP timestamp (yymmddHHMM): 2310041504
#define  in0_AXI_Data_uz_debug_ip             0x100  //data register for Inport in0_AXI
#define  in0_AXI1_Data_uz_debug_ip            0x104  //data register for Inport in0_AXI1
#define  in0_AXI2_Data_uz_debug_ip            0x108  //data register for Inport in0_AXI2
#define  in0_AXI3_Data_uz_debug_ip            0x10C  //data register for Inport in0_AXI3
#define  in0_AXI4_Data_uz_debug_ip            0x110  //data register for Inport in0_AXI4
#define  in0_AXI5_Data_uz_debug_ip            0x114  //data register for Inport in0_AXI5
#define  in0_AXI6_Data_uz_debug_ip            0x118  //data register for Inport in0_AXI6
#define  in0_AXI7_Data_uz_debug_ip            0x11C  //data register for Inport in0_AXI7
#define  in0_AXI8_Data_uz_debug_ip            0x120  //data register for Inport in0_AXI8
#define  real_or_debug_AXI_Data_uz_debug_ip   0x124  //data register for Inport real_or_debug_AXI

// uz_pu_conversion_ip
#define  IPCore_Reset_uz_pu_con_ip           0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_uz_pu_con_ip          0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_uz_pu_con_ip       0x8  //contains unique IP timestamp (yymmddHHMM): 2310041536
#define  AXI_pu_conv_in0_Data_uz_pu_con_ip   0x100  //data register for Inport AXI_pu_conv_in0
#define  AXI_pu_conv_in1_Data_uz_pu_con_ip   0x104  //data register for Inport AXI_pu_conv_in1
#define  AXI_pu_conv_in2_Data_uz_pu_con_ip   0x108  //data register for Inport AXI_pu_conv_in2
#define  AXI_pu_conv_in3_Data_uz_pu_con_ip   0x10C  //data register for Inport AXI_pu_conv_in3
#define  out0_AXI_Data_uz_pu_con_ip          0x180  //data register for Outport out0_AXI
#define  out1_AXI_Data_uz_pu_con_ip          0x184  //data register for Outport out1_AXI
#define  out2_AXI_Data_uz_pu_con_ip          0x188  //data register for Outport out2_AXI
#define  out3_AXI_Data_uz_pu_con_ip          0x18C  //data register for Outport out3_AXI

// uz_park_transform
#define  IPCore_Reset_uz_park_transform_ip               0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_uz_park_transform_ip              0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_uz_park_transform_ip           0x8  //contains unique IP timestamp (yymmddHHMM): 2310041543
#define  factor_angle_el_AXI_Data_uz_park_transform_ip   0x100  //data register for Inport factor_angle_el_AXI
#define  offset_angle_el_AXI_Data_uz_park_transform_ip   0x104  //data register for Inport offset_angle_el_AXI
#define  y1_AXI_Data_uz_park_transform_ip                0x108  //data register for Outport y1_AXI
#define  y2_AXI_Data_uz_park_transform_ip                0x10C  //data register for Outport y2_AXI

// uz_mpc_state_machine
#define  IPCore_Reset_mpc_state_ma_ip                0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_mpc_state_ma_ip               0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_mpc_state_ma_ip            0x8  //contains unique IP timestamp (yymmddHHMM): 2310041541
#define  AXI_no_of_iterations_Data_mpc_state_ma_ip   0x100  //data register for Inport AXI_no_of_iterations

// uz_pu_voltages
#define  IPCore_Reset_pu_voltages_vsd            0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_pu_voltages_vsd           0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_pu_voltages_vsd        0x8  //contains unique IP timestamp (yymmddHHMM): 2310041550
#define  index_select_AXI_Data_pu_voltages_vsd   0x100  //data register for Inport index_select_AXI
#define  index_AXI_Data_pu_voltages_vsd          0x104  //data register for Inport index_AXI
#define  pu_vd_AXI_Data_pu_voltages_vsd          0x108  //data register for Outport pu_vd_AXI
#define  pu_vq_AXI_Data_pu_voltages_vsd          0x10C  //data register for Outport pu_vq_AXI
#define  v_DC_pu_AXI_Data_pu_voltages_vsd        0x118  //data register for Inport v_DC_pu_AXI
#define  v_dc_select_AXI_Data_pu_voltages_vsd    0x11C  //data register for Inport v_dc_select_AXI

// uz_pu_omega_m
#define  IPCore_Reset_pu_omega_m          0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_pu_omega_m         0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_pu_omega_m      0x8  //contains unique IP timestamp (yymmddHHMM): 2310041545
#define  AXI_pu_conv_in_Data_pu_omega_m   0x17C  //data register for Inport AXI_pu_conv_in
#define  out1_AXI_Data_pu_omega_m         0x1FC  //data register for Outport out1_AXI

// delay_comp
#define  IPCore_Reset_delay_comp                   0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_delay_comp                  0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_delay_comp               0x8  //contains unique IP timestamp (yymmddHHMM): 2310041548
#define  id_delay_pu_AXI_Data_delay_comp           0x104  //data register for Outport id_delay_pu_AXI
#define  iq_delay_pu_AXI_Data_delay_comp           0x108  //data register for Outport iq_delay_pu_AXI
#define  Rs_over_ZB_AXI_Data_delay_comp            0x118  //data register for Inport Rs_over_ZB_AXI
#define  Ts_times_ZB_over_Ld_AXI_Data_delay_comp   0x11C  //data register for Inport Ts_times_ZB_over_Ld_AXI
#define  Ts_times_ZB_over_Lq_AXI_Data_delay_comp   0x120  //data register for Inport Ts_times_ZB_over_Lq_AXI
#define  Ld_over_LB_AXI_Data_delay_comp            0x12C  //data register for Inport Ld_over_LB_AXI
#define  Lq_over_LB_AXI_Data_delay_comp            0x130  //data register for Inport Lq_over_LB_AXI
#define  psi_pm_over_psiB_AXI_Data_delay_comp      0x138  //data register for Inport psi_pm_over_psiB_AXI
#define  polepairs_AXI_Data_delay_comp             0x13C  //data register for Inport polepairs_AXI

// prediciton model
#define  IPCore_Reset_prediction                   0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_prediction                  0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_prediction               0x8  //contains unique IP timestamp (yymmddHHMM): 2310041552
#define  id_pred_pu_AXI_Data_prediction            0x104  //data register for Outport id_pred_pu_AXI
#define  iq_pred_pu_AXI_Data_prediction            0x108  //data register for Outport iq_pred_pu_AXI
#define  Rs_over_ZB_AXI_Data_prediction            0x118  //data register for Inport Rs_over_ZB_AXI
#define  Ts_times_ZB_over_Ld_AXI_Data_prediction   0x11C  //data register for Inport Ts_times_ZB_over_Ld_AXI
#define  Ts_times_ZB_over_Lq_AXI_Data_prediction   0x120  //data register for Inport Ts_times_ZB_over_Lq_AXI
#define  Ld_over_LB_AXI_Data_prediction            0x12C  //data register for Inport Ld_over_LB_AXI
#define  Lq_over_LB_AXI_Data_prediction            0x130  //data register for Inport Lq_over_LB_AXI
#define  psi_pm_over_psiB_AXI_Data_prediction      0x138  //data register for Inport psi_pm_over_psiB_AXI
#define  polepairs_AXI_Data_prediction             0x13C  //data register for Inport polepairs_AXI

//cost function
#define  IPCore_Reset_cost_opt              0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_cost_opt             0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_cost_opt          0x8  //contains unique IP timestamp (yymmddHHMM): 2310041554
#define  id_ref_pu_AXI_Data_cost_opt        0x100  //data register for Inport id_ref_pu_AXI
#define  iq_ref_pu_AXI_Data_cost_opt        0x104  //data register for Inport iq_ref_pu_AXI
#define  max_current_pu_AXI_Data_cost_opt   0x110  //data register for Inport max_current_pu_AXI
#define  lambda_d_AXI_Data_cost_opt         0x114  //data register for Inport lambda_d_AXI
#define  lambda_q_AXI_Data_cost_opt         0x118  //data register for Inport lambda_q_AXI
#define  lambda_u_AXI_Data_cost_opt         0x124  //data register for Inport lambda_u_AXI


void fcs_mpc_select_current_source(bool right_or_left);
void fcs_mpc_select_resolver_source(bool right_or_left);
void fcs_mpc_real_or_debug_inputs(bool debug_or_real);
void fcs_mpc_init_pu_conversion_ip(void);
void fcs_mpc_init_park_transform(void);
void fcs_mpc_init_state_machine(uint32_t no_of_iterations);
void fcs_mpc_init_pu_voltages(bool index_from_axi_or_pl, bool v_dc_from_axi_or_pl, float v_dc_axi);
void fcs_mpc_init_omega_m_pu_conversion(void);
void fcs_mpc_init_delay_comp(void);
void fcs_mpc_init_prediction_model(void);
void fcs_mpc_init_cost_function(void);
void fcs_mpc_write_axi_v_dc(void);
