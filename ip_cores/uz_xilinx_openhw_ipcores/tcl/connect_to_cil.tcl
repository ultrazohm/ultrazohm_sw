startgroup
create_bd_cell -type ip -vlnv xilinx.com:ip:xlslice:1.0 uz_user/xlslice_0
set_property -dict [list \
  CONFIG.DIN_FROM {26} \
  CONFIG.DIN_WIDTH {81} \
] [get_bd_cells uz_user/xlslice_0]

create_bd_cell -type ip -vlnv xilinx.com:ip:xlslice:1.0 uz_user/xlslice_1
set_property -dict [list \
  CONFIG.DIN_FROM {53} \
  CONFIG.DIN_TO {27} \
  CONFIG.DIN_WIDTH {81} \
] [get_bd_cells uz_user/xlslice_1]

create_bd_cell -type ip -vlnv xilinx.com:ip:xlslice:1.0 uz_user/xlslice_2
set_property -dict [list \
  CONFIG.DIN_FROM {80} \
  CONFIG.DIN_TO {54} \
  CONFIG.DIN_WIDTH {81} \
] [get_bd_cells uz_user/xlslice_2]

connect_bd_net [get_bd_pins uz_user/xlslice_0/Din] [get_bd_pins uz_user/uz_sixphase_VSD_tran_0/x_abc_1_0]
connect_bd_net [get_bd_pins uz_user/xlslice_1/Din] [get_bd_pins uz_user/uz_sixphase_VSD_tran_0/x_abc_1_0]
connect_bd_net [get_bd_pins uz_user/xlslice_2/Din] [get_bd_pins uz_user/uz_sixphase_VSD_tran_0/x_abc_1_0]
connect_bd_net [get_bd_pins uz_user/xlslice_0/Dout] [get_bd_pins uz_user/fix_to_float_current/in_0]
connect_bd_net [get_bd_pins uz_user/xlslice_1/Dout] [get_bd_pins uz_user/fix_to_float_current/in_1]
connect_bd_net [get_bd_pins uz_user/xlslice_2/Dout] [get_bd_pins uz_user/fix_to_float_current/in_2]
endgroup

startgroup
create_bd_cell -type ip -vlnv xilinx.com:ip:xlslice:1.0 uz_user/xlslice_3
set_property -dict [list \
  CONFIG.DIN_FROM {26} \
  CONFIG.DIN_WIDTH {81} \
] [get_bd_cells uz_user/xlslice_3]

create_bd_cell -type ip -vlnv xilinx.com:ip:xlslice:1.0 uz_user/xlslice_4
set_property -dict [list \
  CONFIG.DIN_FROM {53} \
  CONFIG.DIN_TO {27} \
  CONFIG.DIN_WIDTH {81} \
] [get_bd_cells uz_user/xlslice_4]

create_bd_cell -type ip -vlnv xilinx.com:ip:xlslice:1.0 uz_user/xlslice_5
set_property -dict [list \
  CONFIG.DIN_FROM {80} \
  CONFIG.DIN_TO {54} \
  CONFIG.DIN_WIDTH {81} \
] [get_bd_cells uz_user/xlslice_5]

connect_bd_net [get_bd_pins uz_user/xlslice_3/Din] [get_bd_pins uz_user/uz_sixphase_VSD_tran_0/x_abc_2_0]
connect_bd_net [get_bd_pins uz_user/xlslice_4/Din] [get_bd_pins uz_user/uz_sixphase_VSD_tran_0/x_abc_2_0]
connect_bd_net [get_bd_pins uz_user/xlslice_5/Din] [get_bd_pins uz_user/uz_sixphase_VSD_tran_0/x_abc_2_0]
connect_bd_net [get_bd_pins uz_user/xlslice_3/Dout] [get_bd_pins uz_user/fix_to_float_current/in_3]
connect_bd_net [get_bd_pins uz_user/xlslice_4/Dout] [get_bd_pins uz_user/fix_to_float_current/in_4]
connect_bd_net [get_bd_pins uz_user/xlslice_5/Dout] [get_bd_pins uz_user/fix_to_float_current/in_5]
endgroup

startgroup
create_bd_cell -type ip -vlnv xilinx.com:hls:uz_fixdt_to_float:1.0 uz_user/uz_fixdt_to_float_theta
connect_bd_net [get_bd_pins uz_user/uz_fixdt_to_float_theta/ap_clk] [get_bd_pins uz_user/fix_to_float_current/clk]
connect_bd_net [get_bd_pins uz_user/uz_fixdt_to_float_theta/ap_rst] [get_bd_pins uz_user/fix_to_float_current/rst]
connect_bd_net [get_bd_pins uz_user/uz_fixdt_to_float_theta/ap_start] [get_bd_pins uz_user/fix_to_float_current/sp_start]
connect_bd_net [get_bd_pins uz_user/uz_fixdt_to_float_theta/out_float] [get_bd_pins uz_user/transformation_and_control/in_theta_el]
create_bd_cell -type ip -vlnv xilinx.com:ip:xlconstant:1.1 uz_user/theta_word
set_property -dict [list \
  CONFIG.CONST_VAL {18} \
  CONFIG.CONST_WIDTH {8} \
] [get_bd_cells uz_user/theta_word]
create_bd_cell -type ip -vlnv xilinx.com:ip:xlconstant:1.1 uz_user/theta_fraction
set_property -dict [list \
  CONFIG.CONST_VAL {14} \
  CONFIG.CONST_WIDTH {8} \
] [get_bd_cells uz_user/theta_fraction]
create_bd_cell -type ip -vlnv xilinx.com:ip:xlconstant:1.1 uz_user/theta_sign
connect_bd_net [get_bd_pins uz_user/theta_sign/dout] [get_bd_pins uz_user/uz_fixdt_to_float_theta/sign]
connect_bd_net [get_bd_pins uz_user/theta_word/dout] [get_bd_pins uz_user/uz_fixdt_to_float_theta/word]
connect_bd_net [get_bd_pins uz_user/theta_fraction/dout] [get_bd_pins uz_user/uz_fixdt_to_float_theta/fraction]
connect_bd_net [get_bd_pins uz_user/uz_fixdt_to_float_theta/in_fixed] [get_bd_pins uz_user/uz_pmsm_model_6ph_dq_0/theta_el_out]
endgroup

startgroup
set_property CONFIG.NUM_MI {7} [get_bd_cells uz_user/smartconnect_1]
connect_bd_intf_net -boundary_type upper [get_bd_intf_pins uz_user/transformation_and_control/AXI_FOC] [get_bd_intf_pins uz_user/smartconnect_1/M06_AXI]
connect_bd_net [get_bd_pins uz_user/aresetn] [get_bd_pins uz_user/transformation_and_control/ap_rst_n]
connect_bd_net [get_bd_pins uz_user/aclk] [get_bd_pins uz_user/transformation_and_control/ap_clk]
create_bd_cell -type ip -vlnv xilinx.com:ip:xlconstant:1.1 uz_user/xlconstant_0
set_property CONFIG.CONST_VAL {0} [get_bd_cells uz_user/xlconstant_0]
connect_bd_net [get_bd_pins uz_user/xlconstant_0/dout] [get_bd_pins uz_user/fix_to_float_current/rst]
create_bd_cell -type ip -vlnv xilinx.com:ip:sim_clk_gen:1.0 uz_user/sim_clk_gen_0
set_property CONFIG.FREQ_HZ {100000} [get_bd_cells uz_user/sim_clk_gen_0]
connect_bd_net [get_bd_pins uz_user/sim_clk_gen_0/clk] [get_bd_pins uz_user/uz_fixdt_to_float_theta/ap_start]
connect_bd_net [get_bd_pins uz_user/float_to_fix_dutycycle/out_0] [get_bd_pins uz_user/PWM_and_SS_control_V_0/m_u1_norm]
connect_bd_net [get_bd_pins uz_user/float_to_fix_dutycycle/out_1] [get_bd_pins uz_user/PWM_and_SS_control_V_0/m_u2_norm]
connect_bd_net [get_bd_pins uz_user/float_to_fix_dutycycle/out_2] [get_bd_pins uz_user/PWM_and_SS_control_V_0/m_u3_norm]
connect_bd_net [get_bd_pins uz_user/float_to_fix_dutycycle/out_3] [get_bd_pins uz_user/PWM_and_SS_control_V_1/m_u1_norm]
connect_bd_net [get_bd_pins uz_user/float_to_fix_dutycycle/out_4] [get_bd_pins uz_user/PWM_and_SS_control_V_1/m_u2_norm]
connect_bd_net [get_bd_pins uz_user/float_to_fix_dutycycle/out_5] [get_bd_pins uz_user/PWM_and_SS_control_V_1/m_u3_norm]