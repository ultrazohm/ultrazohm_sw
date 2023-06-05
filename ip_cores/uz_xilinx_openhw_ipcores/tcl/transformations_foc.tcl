update_ip_catalog -rebuild

startgroup
create_bd_cell -type hier uz_user/transformation_and_control
create_bd_cell -type ip -vlnv xilinx.com:hls:uz_VSD_6ph_asym:1.0 uz_user/transformation_and_control/uz_VSD_6ph_asym_0
create_bd_cell -type ip -vlnv xilinx.com:hls:uz_VSDinv_6ph_asym:1.0 uz_user/transformation_and_control/uz_VSDinv_6ph_asym_0
create_bd_cell -type ip -vlnv xilinx.com:hls:uz_Park:1.0 uz_user/transformation_and_control/uz_Park_0
create_bd_cell -type ip -vlnv xilinx.com:hls:uz_FOC:1.0 uz_user/transformation_and_control/uz_FOC_0
create_bd_cell -type ip -vlnv xilinx.com:hls:uz_SPWM_3ph:1.0 uz_user/transformation_and_control/uz_SPWM_3ph_0
create_bd_cell -type ip -vlnv xilinx.com:hls:uz_SPWM_3ph:1.0 uz_user/transformation_and_control/uz_SPWM_3ph_1
endgroup

startgroup
create_bd_pin -dir I uz_user/transformation_and_control/in_a1
create_bd_pin -dir I uz_user/transformation_and_control/in_b1
create_bd_pin -dir I uz_user/transformation_and_control/in_c1
create_bd_pin -dir I uz_user/transformation_and_control/in_a2
create_bd_pin -dir I uz_user/transformation_and_control/in_b2
create_bd_pin -dir I uz_user/transformation_and_control/in_c2
connect_bd_net [get_bd_pins uz_user/transformation_and_control/in_a1] [get_bd_pins uz_user/transformation_and_control/uz_VSD_6ph_asym_0/in_a1]
connect_bd_net [get_bd_pins uz_user/transformation_and_control/in_b1] [get_bd_pins uz_user/transformation_and_control/uz_VSD_6ph_asym_0/in_b1]
connect_bd_net [get_bd_pins uz_user/transformation_and_control/in_c1] [get_bd_pins uz_user/transformation_and_control/uz_VSD_6ph_asym_0/in_c1]
connect_bd_net [get_bd_pins uz_user/transformation_and_control/in_a2] [get_bd_pins uz_user/transformation_and_control/uz_VSD_6ph_asym_0/in_a2]
connect_bd_net [get_bd_pins uz_user/transformation_and_control/in_b2] [get_bd_pins uz_user/transformation_and_control/uz_VSD_6ph_asym_0/in_b2]
connect_bd_net [get_bd_pins uz_user/transformation_and_control/in_c2] [get_bd_pins uz_user/transformation_and_control/uz_VSD_6ph_asym_0/in_c2]

create_bd_pin -dir I uz_user/transformation_and_control/in_theta_el
connect_bd_net [get_bd_pins uz_user/transformation_and_control/in_theta_el] [get_bd_pins uz_user/transformation_and_control/uz_Park_0/theta_el]
endgroup

startgroup
create_bd_pin -dir I uz_user/transformation_and_control/ap_clk
connect_bd_net [get_bd_pins uz_user/transformation_and_control/ap_clk] [get_bd_pins uz_user/transformation_and_control/uz_VSD_6ph_asym_0/ap_clk]
connect_bd_net [get_bd_pins uz_user/transformation_and_control/uz_VSD_6ph_asym_0/ap_clk] [get_bd_pins uz_user/transformation_and_control/uz_Park_0/ap_clk]
connect_bd_net [get_bd_pins uz_user/transformation_and_control/uz_Park_0/ap_clk] [get_bd_pins uz_user/transformation_and_control/uz_FOC_0/ap_clk]
connect_bd_net [get_bd_pins uz_user/transformation_and_control/uz_FOC_0/ap_clk] [get_bd_pins uz_user/transformation_and_control/uz_VSDinv_6ph_asym_0/ap_clk]
connect_bd_net [get_bd_pins uz_user/transformation_and_control/uz_VSDinv_6ph_asym_0/ap_clk] [get_bd_pins uz_user/transformation_and_control/uz_SPWM_3ph_0/ap_clk]
connect_bd_net [get_bd_pins uz_user/transformation_and_control/uz_SPWM_3ph_0/ap_clk] [get_bd_pins uz_user/transformation_and_control/uz_SPWM_3ph_1/ap_clk]

create_bd_pin -dir I uz_user/transformation_and_control/ap_rst
connect_bd_net [get_bd_pins uz_user/transformation_and_control/ap_rst] [get_bd_pins uz_user/transformation_and_control/uz_VSD_6ph_asym_0/ap_rst]
connect_bd_net [get_bd_pins uz_user/transformation_and_control/uz_VSD_6ph_asym_0/ap_rst] [get_bd_pins uz_user/transformation_and_control/uz_Park_0/ap_rst]
connect_bd_net [get_bd_pins uz_user/transformation_and_control/uz_Park_0/ap_rst] [get_bd_pins uz_user/transformation_and_control/uz_VSDinv_6ph_asym_0/ap_rst]
connect_bd_net [get_bd_pins uz_user/transformation_and_control/uz_VSDinv_6ph_asym_0/ap_rst] [get_bd_pins uz_user/transformation_and_control/uz_SPWM_3ph_0/ap_rst]
connect_bd_net [get_bd_pins uz_user/transformation_and_control/uz_SPWM_3ph_1/ap_rst] [get_bd_pins uz_user/transformation_and_control/uz_SPWM_3ph_0/ap_rst]

create_bd_pin -dir I uz_user/transformation_and_control/ap_start
connect_bd_net [get_bd_pins uz_user/transformation_and_control/ap_start] [get_bd_pins uz_user/transformation_and_control/uz_VSD_6ph_asym_0/ap_start]
connect_bd_net [get_bd_pins uz_user/transformation_and_control/uz_VSD_6ph_asym_0/ap_done] [get_bd_pins uz_user/transformation_and_control/uz_Park_0/ap_start]
connect_bd_net [get_bd_pins uz_user/transformation_and_control/uz_Park_0/ap_done] [get_bd_pins uz_user/transformation_and_control/uz_FOC_0/ap_start]
connect_bd_net [get_bd_pins uz_user/transformation_and_control/uz_FOC_0/ap_done] [get_bd_pins uz_user/transformation_and_control/uz_VSDinv_6ph_asym_0/ap_start]
connect_bd_net [get_bd_pins uz_user/transformation_and_control/uz_VSDinv_6ph_asym_0/ap_done] [get_bd_pins uz_user/transformation_and_control/uz_SPWM_3ph_0/ap_start]
connect_bd_net [get_bd_pins uz_user/transformation_and_control/uz_SPWM_3ph_1/ap_start] [get_bd_pins uz_user/transformation_and_control/uz_VSDinv_6ph_asym_0/ap_done]

create_bd_pin -dir I uz_user/transformation_and_control/ap_rst_n
connect_bd_net [get_bd_pins uz_user/transformation_and_control/ap_rst_n] [get_bd_pins uz_user/transformation_and_control/uz_FOC_0/ap_rst_n]

create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:aximm_rtl:1.0 uz_user/transformation_and_control/AXI_FOC
connect_bd_intf_net [get_bd_intf_pins uz_user/transformation_and_control/AXI_FOC] [get_bd_intf_pins uz_user/transformation_and_control/uz_FOC_0/s_axi_control]

create_bd_pin -dir O uz_user/transformation_and_control/ap_done
connect_bd_net [get_bd_pins uz_user/transformation_and_control/ap_done] [get_bd_pins uz_user/transformation_and_control/uz_SPWM_3ph_0/ap_done]
endgroup

startgroup
create_bd_pin -dir O uz_user/transformation_and_control/out_dc_a1
create_bd_pin -dir O uz_user/transformation_and_control/out_dc_b1
create_bd_pin -dir O uz_user/transformation_and_control/out_dc_c1
create_bd_pin -dir O uz_user/transformation_and_control/out_dc_a2
create_bd_pin -dir O uz_user/transformation_and_control/out_dc_b2
create_bd_pin -dir O uz_user/transformation_and_control/out_dc_c2
connect_bd_net [get_bd_pins uz_user/transformation_and_control/out_dc_a1] [get_bd_pins uz_user/transformation_and_control/uz_SPWM_3ph_0/DC_a]
connect_bd_net [get_bd_pins uz_user/transformation_and_control/out_dc_b1] [get_bd_pins uz_user/transformation_and_control/uz_SPWM_3ph_0/DC_b]
connect_bd_net [get_bd_pins uz_user/transformation_and_control/out_dc_c1] [get_bd_pins uz_user/transformation_and_control/uz_SPWM_3ph_0/DC_c]
connect_bd_net [get_bd_pins uz_user/transformation_and_control/out_dc_a2] [get_bd_pins uz_user/transformation_and_control/uz_SPWM_3ph_1/DC_a]
connect_bd_net [get_bd_pins uz_user/transformation_and_control/out_dc_b2] [get_bd_pins uz_user/transformation_and_control/uz_SPWM_3ph_1/DC_b]
connect_bd_net [get_bd_pins uz_user/transformation_and_control/out_dc_c2] [get_bd_pins uz_user/transformation_and_control/uz_SPWM_3ph_1/DC_c]
endgroup 

startgroup
connect_bd_net [get_bd_pins uz_user/transformation_and_control/uz_Park_0/in_trafo_alpha] [get_bd_pins uz_user/transformation_and_control/uz_VSD_6ph_asym_0/out_alpha]
connect_bd_net [get_bd_pins uz_user/transformation_and_control/uz_VSD_6ph_asym_0/out_beta] [get_bd_pins uz_user/transformation_and_control/uz_Park_0/in_trafo_beta]
connect_bd_net [get_bd_pins uz_user/transformation_and_control/uz_FOC_0/ref_ud] [get_bd_pins uz_user/transformation_and_control/uz_Park_0/in_inv_d]
connect_bd_net [get_bd_pins uz_user/transformation_and_control/uz_FOC_0/ref_uq] [get_bd_pins uz_user/transformation_and_control/uz_Park_0/in_inv_q]
connect_bd_net [get_bd_pins uz_user/transformation_and_control/uz_Park_0/out_inv_alpha] [get_bd_pins uz_user/transformation_and_control/uz_VSDinv_6ph_asym_0/in_alpha]
connect_bd_net [get_bd_pins uz_user/transformation_and_control/uz_Park_0/out_inv_beta] [get_bd_pins uz_user/transformation_and_control/uz_VSDinv_6ph_asym_0/in_beta]
connect_bd_net [get_bd_pins uz_user/transformation_and_control/uz_VSDinv_6ph_asym_0/out_a1] [get_bd_pins uz_user/transformation_and_control/uz_SPWM_3ph_0/u_a]
connect_bd_net [get_bd_pins uz_user/transformation_and_control/uz_VSDinv_6ph_asym_0/out_b1] [get_bd_pins uz_user/transformation_and_control/uz_SPWM_3ph_0/u_b]
connect_bd_net [get_bd_pins uz_user/transformation_and_control/uz_VSDinv_6ph_asym_0/out_c1] [get_bd_pins uz_user/transformation_and_control/uz_SPWM_3ph_0/u_c]
connect_bd_net [get_bd_pins uz_user/transformation_and_control/uz_VSDinv_6ph_asym_0/out_a2] [get_bd_pins uz_user/transformation_and_control/uz_SPWM_3ph_1/u_a]
connect_bd_net [get_bd_pins uz_user/transformation_and_control/uz_VSDinv_6ph_asym_0/out_b2] [get_bd_pins uz_user/transformation_and_control/uz_SPWM_3ph_1/u_b]
connect_bd_net [get_bd_pins uz_user/transformation_and_control/uz_VSDinv_6ph_asym_0/out_c2] [get_bd_pins uz_user/transformation_and_control/uz_SPWM_3ph_1/u_c]
endgroup

startgroup
create_bd_cell -type ip -vlnv xilinx.com:ip:xlconstant:1.1 uz_user/transformation_and_control/u_dc
set_property -dict [list \
  CONFIG.CONST_VAL {0x42c80000} \
  CONFIG.CONST_WIDTH {32} \
] [get_bd_cells uz_user/transformation_and_control/u_dc]
connect_bd_net [get_bd_pins uz_user/transformation_and_control/u_dc/dout] [get_bd_pins uz_user/transformation_and_control/uz_SPWM_3ph_0/u_dc]
connect_bd_net [get_bd_pins uz_user/transformation_and_control/uz_SPWM_3ph_1/u_dc] [get_bd_pins uz_user/transformation_and_control/u_dc/dout]
endgroup