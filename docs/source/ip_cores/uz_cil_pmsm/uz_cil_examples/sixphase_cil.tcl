update_ip_catalog -rebuild

delete_bd_objs [get_bd_intf_nets uz_user/smartconnect_1_M00_AXI] [get_bd_cells uz_user/uz_axi_testIP_0]

startgroup
create_bd_cell -type ip -vlnv xilinx.com:ip:PWM_and_SS_control_V4_ip:4.1 uz_user/PWM_and_SS_control_V_0
create_bd_cell -type ip -vlnv xilinx.com:ip:PWM_and_SS_control_V4_ip:4.1 uz_user/PWM_and_SS_control_V_1
create_bd_cell -type ip -vlnv xilinx.com:ip:xlconcat:2.1 uz_user/xlconcat_0
create_bd_cell -type ip -vlnv xilinx.com:ip:xlconcat:2.1 uz_user/xlconcat_1
create_bd_cell -type ip -vlnv xilinx.com:ip:uz_inverter_3ph:1.0 uz_user/uz_inverter_3ph_0
create_bd_cell -type ip -vlnv xilinx.com:ip:uz_inverter_3ph:1.0 uz_user/uz_inverter_3ph_1
create_bd_cell -type ip -vlnv xilinx.com:ip:uz_rs_flip_flop:1.0 uz_user/uz_rs_flip_flop_0
create_bd_cell -type ip -vlnv xilinx.com:ip:uz_pmsm_model_6ph_dq:1.0 uz_user/uz_pmsm_model_6ph_dq_0
create_bd_cell -type ip -vlnv xilinx.com:ip:uz_sixphase_VSD_transformation:1.0 uz_user/uz_sixphase_VSD_tran_0
endgroup

startgroup
set_property CONFIG.NUM_PORTS {6} [get_bd_cells uz_user/xlconcat_0]
set_property CONFIG.NUM_PORTS {6} [get_bd_cells uz_user/xlconcat_1]
set_property CONFIG.NUM_MI {6} [get_bd_cells uz_user/smartconnect_1]
endgroup

startgroup
connect_bd_net [get_bd_pins uz_user/aclk] [get_bd_pins uz_user/PWM_and_SS_control_V_0/IPCORE_CLK]
connect_bd_net [get_bd_pins uz_user/aclk] [get_bd_pins uz_user/PWM_and_SS_control_V_1/IPCORE_CLK]
connect_bd_net [get_bd_pins uz_user/aclk] [get_bd_pins uz_user/uz_inverter_3ph_0/IPCORE_CLK]
connect_bd_net [get_bd_pins uz_user/aclk] [get_bd_pins uz_user/uz_inverter_3ph_1/IPCORE_CLK]
connect_bd_net [get_bd_pins uz_user/aclk] [get_bd_pins uz_user/uz_sixphase_VSD_tran_0/IPCORE_CLK]
connect_bd_net [get_bd_pins uz_user/aclk] [get_bd_pins uz_user/uz_pmsm_model_6ph_dq_0/IPCORE_CLK]
connect_bd_net [get_bd_pins uz_user/aclk] [get_bd_pins uz_user/uz_rs_flip_flop_0/IPCORE_CLK]
connect_bd_net [get_bd_pins uz_user/aclk] [get_bd_pins uz_user/PWM_and_SS_control_V_0/AXI4_Lite_ACLK]
connect_bd_net [get_bd_pins uz_user/aclk] [get_bd_pins uz_user/PWM_and_SS_control_V_1/AXI4_Lite_ACLK]
connect_bd_net [get_bd_pins uz_user/aclk] [get_bd_pins uz_user/uz_inverter_3ph_0/AXI4_ACLK]
connect_bd_net [get_bd_pins uz_user/aclk] [get_bd_pins uz_user/uz_inverter_3ph_1/AXI4_ACLK]
connect_bd_net [get_bd_pins uz_user/aclk] [get_bd_pins uz_user/uz_sixphase_VSD_tran_0/AXI4_ACLK]
connect_bd_net [get_bd_pins uz_user/aclk] [get_bd_pins uz_user/uz_pmsm_model_6ph_dq_0/AXI4_ACLK]
connect_bd_net [get_bd_pins uz_user/aresetn] [get_bd_pins uz_user/PWM_and_SS_control_V_0/IPCORE_RESETN]
connect_bd_net [get_bd_pins uz_user/aresetn] [get_bd_pins uz_user/PWM_and_SS_control_V_1/IPCORE_RESETN]
connect_bd_net [get_bd_pins uz_user/aresetn] [get_bd_pins uz_user/uz_inverter_3ph_0/IPCORE_RESETN]
connect_bd_net [get_bd_pins uz_user/aresetn] [get_bd_pins uz_user/uz_inverter_3ph_1/IPCORE_RESETN]
connect_bd_net [get_bd_pins uz_user/aresetn] [get_bd_pins uz_user/uz_rs_flip_flop_0/IPCORE_RESETN]
connect_bd_net [get_bd_pins uz_user/aresetn] [get_bd_pins uz_user/uz_pmsm_model_6ph_dq_0/IPCORE_RESETN]
connect_bd_net [get_bd_pins uz_user/aresetn] [get_bd_pins uz_user/uz_sixphase_VSD_tran_0/IPCORE_RESETN]
connect_bd_net [get_bd_pins uz_user/aresetn] [get_bd_pins uz_user/PWM_and_SS_control_V_0/AXI4_Lite_ARESETN]
connect_bd_net [get_bd_pins uz_user/aresetn] [get_bd_pins uz_user/PWM_and_SS_control_V_1/AXI4_Lite_ARESETN]
connect_bd_net [get_bd_pins uz_user/aresetn] [get_bd_pins uz_user/uz_pmsm_model_6ph_dq_0/AXI4_ARESETN]
connect_bd_net [get_bd_pins uz_user/aresetn] [get_bd_pins uz_user/uz_sixphase_VSD_tran_0/AXI4_ARESETN]
connect_bd_net [get_bd_pins uz_user/aresetn] [get_bd_pins uz_user/uz_inverter_3ph_1/AXI4_ARESETN]
connect_bd_net [get_bd_pins uz_user/aresetn] [get_bd_pins uz_user/uz_inverter_3ph_0/AXI4_ARESETN]
endgroup

startgroup
connect_bd_net [get_bd_pins uz_user/PWM_and_SS_control_V_0/SS0_OUT] [get_bd_pins uz_user/xlconcat_0/In0]
connect_bd_net [get_bd_pins uz_user/PWM_and_SS_control_V_0/SS1_OUT] [get_bd_pins uz_user/xlconcat_0/In1]
connect_bd_net [get_bd_pins uz_user/PWM_and_SS_control_V_0/SS2_OUT] [get_bd_pins uz_user/xlconcat_0/In2]
connect_bd_net [get_bd_pins uz_user/PWM_and_SS_control_V_0/SS3_OUT] [get_bd_pins uz_user/xlconcat_0/In3]
connect_bd_net [get_bd_pins uz_user/PWM_and_SS_control_V_0/SS4_OUT] [get_bd_pins uz_user/xlconcat_0/In4]
connect_bd_net [get_bd_pins uz_user/PWM_and_SS_control_V_0/SS5_OUT] [get_bd_pins uz_user/xlconcat_0/In5]
connect_bd_net [get_bd_pins uz_user/PWM_and_SS_control_V_1/SS0_OUT] [get_bd_pins uz_user/xlconcat_1/In0]
connect_bd_net [get_bd_pins uz_user/PWM_and_SS_control_V_1/SS1_OUT] [get_bd_pins uz_user/xlconcat_1/In1]
connect_bd_net [get_bd_pins uz_user/PWM_and_SS_control_V_1/SS2_OUT] [get_bd_pins uz_user/xlconcat_1/In2]
connect_bd_net [get_bd_pins uz_user/PWM_and_SS_control_V_1/SS3_OUT] [get_bd_pins uz_user/xlconcat_1/In3]
connect_bd_net [get_bd_pins uz_user/PWM_and_SS_control_V_1/SS4_OUT] [get_bd_pins uz_user/xlconcat_1/In4]
connect_bd_net [get_bd_pins uz_user/PWM_and_SS_control_V_1/SS5_OUT] [get_bd_pins uz_user/xlconcat_1/In5]
endgroup

startgroup
connect_bd_net [get_bd_pins uz_user/xlconcat_0/dout] [get_bd_pins uz_user/uz_inverter_3ph_0/gate_pl_0]
connect_bd_net [get_bd_pins uz_user/xlconcat_1/dout] [get_bd_pins uz_user/uz_inverter_3ph_1/gate_pl_0]
endgroup

startgroup
connect_bd_intf_net [get_bd_intf_pins uz_user/smartconnect_1/M00_AXI] [get_bd_intf_pins uz_user/uz_pmsm_model_6ph_dq_0/AXI4]
connect_bd_intf_net [get_bd_intf_pins uz_user/smartconnect_1/M01_AXI] [get_bd_intf_pins uz_user/uz_sixphase_VSD_tran_0/AXI4]
connect_bd_intf_net [get_bd_intf_pins uz_user/smartconnect_1/M02_AXI] [get_bd_intf_pins uz_user/uz_inverter_3ph_0/AXI4]
connect_bd_intf_net [get_bd_intf_pins uz_user/smartconnect_1/M03_AXI] [get_bd_intf_pins uz_user/uz_inverter_3ph_1/AXI4]
connect_bd_intf_net [get_bd_intf_pins uz_user/smartconnect_1/M04_AXI] [get_bd_intf_pins uz_user/PWM_and_SS_control_V_0/AXI4_Lite]
connect_bd_intf_net [get_bd_intf_pins uz_user/smartconnect_1/M05_AXI] [get_bd_intf_pins uz_user/PWM_and_SS_control_V_1/AXI4_Lite]
endgroup

startgroup
connect_bd_net [get_bd_pins uz_user/uz_inverter_3ph_0/u_abc_pl_0] [get_bd_pins uz_user/uz_sixphase_VSD_tran_0/x_abc1_ll_pl_0]
connect_bd_net [get_bd_pins uz_user/uz_inverter_3ph_1/u_abc_pl_0] [get_bd_pins uz_user/uz_sixphase_VSD_tran_0/x_abc2_ll_pl_0]
connect_bd_net [get_bd_pins uz_user/uz_pmsm_model_6ph_dq_0/currents_dq_out_0] [get_bd_pins uz_user/uz_sixphase_VSD_tran_0/x_in_dq_0]
connect_bd_net [get_bd_pins uz_user/uz_pmsm_model_6ph_dq_0/theta_el_out] [get_bd_pins uz_user/uz_sixphase_VSD_tran_0/theta_el]
connect_bd_net [get_bd_pins uz_digital_adapter/D1_adapter/Gates/PWM_and_SS_control_V_0/triangle_out] [get_bd_pins uz_user/PWM_and_SS_control_V_1/triangle_in]
connect_bd_net [get_bd_pins uz_digital_adapter/D1_adapter/Gates/PWM_and_SS_control_V_0/triangle_out] [get_bd_pins uz_user/PWM_and_SS_control_V_0/triangle_in]
connect_bd_net [get_bd_pins uz_system/trigger_converesions] [get_bd_pins uz_user/uz_rs_flip_flop_0/ff_set]
connect_bd_net [get_bd_pins uz_user/uz_sixphase_VSD_tran_0/x_abc_1_0] [get_bd_pins uz_user/uz_inverter_3ph_0/i_abc_pl_0]
connect_bd_net [get_bd_pins uz_user/uz_sixphase_VSD_tran_0/x_abc_2_0] [get_bd_pins uz_user/uz_inverter_3ph_1/i_abc_pl_0]
connect_bd_net [get_bd_pins uz_user/uz_rs_flip_flop_0/ff_out] [get_bd_pins uz_user/uz_sixphase_VSD_tran_0/trigger_new_values]
connect_bd_net [get_bd_pins uz_user/uz_rs_flip_flop_0/ff_reset] [get_bd_pins uz_user/uz_sixphase_VSD_tran_0/refresh_values]
connect_bd_net [get_bd_pins uz_user/uz_pmsm_model_6ph_dq_0/voltage_input_dq_0] [get_bd_pins uz_user/uz_sixphase_VSD_tran_0/x_out_dq_0]
endgroup

regenerate_bd_layout