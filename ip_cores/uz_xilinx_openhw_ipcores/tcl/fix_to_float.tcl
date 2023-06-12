update_ip_catalog -rebuild
create_bd_cell -type hier uz_user/fix_to_float_current
startgroup
create_bd_cell -type ip -vlnv xilinx.com:hls:uz_fixdt_to_float:1.0 uz_user/fix_to_float_current/uz_fixdt_to_float_0
create_bd_cell -type ip -vlnv xilinx.com:hls:uz_fixdt_to_float:1.0 uz_user/fix_to_float_current/uz_fixdt_to_float_1
create_bd_cell -type ip -vlnv xilinx.com:hls:uz_fixdt_to_float:1.0 uz_user/fix_to_float_current/uz_fixdt_to_float_2
create_bd_cell -type ip -vlnv xilinx.com:hls:uz_fixdt_to_float:1.0 uz_user/fix_to_float_current/uz_fixdt_to_float_3
create_bd_cell -type ip -vlnv xilinx.com:hls:uz_fixdt_to_float:1.0 uz_user/fix_to_float_current/uz_fixdt_to_float_4
create_bd_cell -type ip -vlnv xilinx.com:hls:uz_fixdt_to_float:1.0 uz_user/fix_to_float_current/uz_fixdt_to_float_5
connect_bd_net [get_bd_pins uz_user/fix_to_float_current/uz_fixdt_to_float_0/ap_clk] [get_bd_pins uz_user/fix_to_float_current/uz_fixdt_to_float_1/ap_clk]
connect_bd_net [get_bd_pins uz_user/fix_to_float_current/uz_fixdt_to_float_0/ap_rst] [get_bd_pins uz_user/fix_to_float_current/uz_fixdt_to_float_1/ap_rst]
connect_bd_net [get_bd_pins uz_user/fix_to_float_current/uz_fixdt_to_float_1/ap_clk] [get_bd_pins uz_user/fix_to_float_current/uz_fixdt_to_float_2/ap_clk]
connect_bd_net [get_bd_pins uz_user/fix_to_float_current/uz_fixdt_to_float_2/ap_rst] [get_bd_pins uz_user/fix_to_float_current/uz_fixdt_to_float_1/ap_rst]
connect_bd_net [get_bd_pins uz_user/fix_to_float_current/uz_fixdt_to_float_3/ap_clk] [get_bd_pins uz_user/fix_to_float_current/uz_fixdt_to_float_2/ap_clk]
connect_bd_net [get_bd_pins uz_user/fix_to_float_current/uz_fixdt_to_float_3/ap_rst] [get_bd_pins uz_user/fix_to_float_current/uz_fixdt_to_float_2/ap_rst]
connect_bd_net [get_bd_pins uz_user/fix_to_float_current/uz_fixdt_to_float_4/ap_clk] [get_bd_pins uz_user/fix_to_float_current/uz_fixdt_to_float_3/ap_clk]
connect_bd_net [get_bd_pins uz_user/fix_to_float_current/uz_fixdt_to_float_4/ap_rst] [get_bd_pins uz_user/fix_to_float_current/uz_fixdt_to_float_3/ap_rst]
connect_bd_net [get_bd_pins uz_user/fix_to_float_current/uz_fixdt_to_float_5/ap_clk] [get_bd_pins uz_user/fix_to_float_current/uz_fixdt_to_float_4/ap_clk]
connect_bd_net [get_bd_pins uz_user/fix_to_float_current/uz_fixdt_to_float_5/ap_rst] [get_bd_pins uz_user/fix_to_float_current/uz_fixdt_to_float_4/ap_rst]
connect_bd_net [get_bd_pins uz_user/fix_to_float_current/uz_fixdt_to_float_0/ap_start] [get_bd_pins uz_user/fix_to_float_current/uz_fixdt_to_float_1/ap_start]
connect_bd_net [get_bd_pins uz_user/fix_to_float_current/uz_fixdt_to_float_1/ap_start] [get_bd_pins uz_user/fix_to_float_current/uz_fixdt_to_float_2/ap_start]
connect_bd_net [get_bd_pins uz_user/fix_to_float_current/uz_fixdt_to_float_2/ap_start] [get_bd_pins uz_user/fix_to_float_current/uz_fixdt_to_float_3/ap_start]
connect_bd_net [get_bd_pins uz_user/fix_to_float_current/uz_fixdt_to_float_3/ap_start] [get_bd_pins uz_user/fix_to_float_current/uz_fixdt_to_float_4/ap_start]
connect_bd_net [get_bd_pins uz_user/fix_to_float_current/uz_fixdt_to_float_4/ap_start] [get_bd_pins uz_user/fix_to_float_current/uz_fixdt_to_float_5/ap_start]

create_bd_cell -type ip -vlnv xilinx.com:ip:xlconstant:1.1 uz_user/fix_to_float_current/current_word
set_property -dict [list \
  CONFIG.CONST_VAL {27} \
  CONFIG.CONST_WIDTH {8} \
] [get_bd_cells uz_user/fix_to_float_current/current_word]
create_bd_cell -type ip -vlnv xilinx.com:ip:xlconstant:1.1 uz_user/fix_to_float_current/current_fraction
set_property -dict [list \
  CONFIG.CONST_VAL {18} \
  CONFIG.CONST_WIDTH {8} \
] [get_bd_cells uz_user/fix_to_float_current/current_fraction]
create_bd_cell -type ip -vlnv xilinx.com:ip:xlconstant:1.1 uz_user/fix_to_float_current/current_sign
connect_bd_net [get_bd_pins uz_user/fix_to_float_current/current_sign/dout] [get_bd_pins uz_user/fix_to_float_current/uz_fixdt_to_float_2/sign]
connect_bd_net [get_bd_pins uz_user/fix_to_float_current/current_sign/dout] [get_bd_pins uz_user/fix_to_float_current/uz_fixdt_to_float_3/sign]
connect_bd_net [get_bd_pins uz_user/fix_to_float_current/uz_fixdt_to_float_1/sign] [get_bd_pins uz_user/fix_to_float_current/current_sign/dout]
connect_bd_net [get_bd_pins uz_user/fix_to_float_current/uz_fixdt_to_float_5/sign] [get_bd_pins uz_user/fix_to_float_current/current_sign/dout]
connect_bd_net [get_bd_pins uz_user/fix_to_float_current/uz_fixdt_to_float_4/sign] [get_bd_pins uz_user/fix_to_float_current/current_sign/dout]
connect_bd_net [get_bd_pins uz_user/fix_to_float_current/uz_fixdt_to_float_0/sign] [get_bd_pins uz_user/fix_to_float_current/current_sign/dout]
connect_bd_net [get_bd_pins uz_user/fix_to_float_current/current_fraction/dout] [get_bd_pins uz_user/fix_to_float_current/uz_fixdt_to_float_2/fraction]
connect_bd_net [get_bd_pins uz_user/fix_to_float_current/current_fraction/dout] [get_bd_pins uz_user/fix_to_float_current/uz_fixdt_to_float_3/fraction]
connect_bd_net [get_bd_pins uz_user/fix_to_float_current/uz_fixdt_to_float_1/fraction] [get_bd_pins uz_user/fix_to_float_current/current_fraction/dout]
connect_bd_net [get_bd_pins uz_user/fix_to_float_current/uz_fixdt_to_float_5/fraction] [get_bd_pins uz_user/fix_to_float_current/current_fraction/dout]
connect_bd_net [get_bd_pins uz_user/fix_to_float_current/uz_fixdt_to_float_4/fraction] [get_bd_pins uz_user/fix_to_float_current/current_fraction/dout]
connect_bd_net [get_bd_pins uz_user/fix_to_float_current/current_word/dout] [get_bd_pins uz_user/fix_to_float_current/uz_fixdt_to_float_2/word]
connect_bd_net [get_bd_pins uz_user/fix_to_float_current/current_word/dout] [get_bd_pins uz_user/fix_to_float_current/uz_fixdt_to_float_0/word]
connect_bd_net [get_bd_pins uz_user/fix_to_float_current/uz_fixdt_to_float_0/fraction] [get_bd_pins uz_user/fix_to_float_current/current_fraction/dout]
connect_bd_net [get_bd_pins uz_user/fix_to_float_current/uz_fixdt_to_float_4/word] [get_bd_pins uz_user/fix_to_float_current/current_word/dout]
connect_bd_net [get_bd_pins uz_user/fix_to_float_current/uz_fixdt_to_float_5/word] [get_bd_pins uz_user/fix_to_float_current/uz_fixdt_to_float_1/word]
connect_bd_net [get_bd_pins uz_user/fix_to_float_current/uz_fixdt_to_float_1/word] [get_bd_pins uz_user/fix_to_float_current/uz_fixdt_to_float_3/word]
connect_bd_net [get_bd_pins uz_user/fix_to_float_current/uz_fixdt_to_float_3/word] [get_bd_pins uz_user/fix_to_float_current/current_word/dout]
endgroup

startgroup
create_bd_pin -dir O uz_user/fix_to_float_current/out_0
create_bd_pin -dir O uz_user/fix_to_float_current/out_1
create_bd_pin -dir O uz_user/fix_to_float_current/out_2
create_bd_pin -dir O uz_user/fix_to_float_current/out_3
create_bd_pin -dir O uz_user/fix_to_float_current/out_4
create_bd_pin -dir O uz_user/fix_to_float_current/out_5
connect_bd_net [get_bd_pins uz_user/fix_to_float_current/out_0] [get_bd_pins uz_user/fix_to_float_current/uz_fixdt_to_float_0/out_float]
connect_bd_net [get_bd_pins uz_user/fix_to_float_current/out_1] [get_bd_pins uz_user/fix_to_float_current/uz_fixdt_to_float_1/out_float]
connect_bd_net [get_bd_pins uz_user/fix_to_float_current/out_2] [get_bd_pins uz_user/fix_to_float_current/uz_fixdt_to_float_2/out_float]
connect_bd_net [get_bd_pins uz_user/fix_to_float_current/out_3] [get_bd_pins uz_user/fix_to_float_current/uz_fixdt_to_float_3/out_float]
connect_bd_net [get_bd_pins uz_user/fix_to_float_current/out_4] [get_bd_pins uz_user/fix_to_float_current/uz_fixdt_to_float_4/out_float]
connect_bd_net [get_bd_pins uz_user/fix_to_float_current/out_5] [get_bd_pins uz_user/fix_to_float_current/uz_fixdt_to_float_5/out_float]

create_bd_pin -dir I uz_user/fix_to_float_current/in_0
create_bd_pin -dir I uz_user/fix_to_float_current/in_1
create_bd_pin -dir I uz_user/fix_to_float_current/in_2
create_bd_pin -dir I uz_user/fix_to_float_current/in_3
create_bd_pin -dir I uz_user/fix_to_float_current/in_4
create_bd_pin -dir I uz_user/fix_to_float_current/in_5
connect_bd_net [get_bd_pins uz_user/fix_to_float_current/in_0] [get_bd_pins uz_user/fix_to_float_current/uz_fixdt_to_float_0/in_fixed]
connect_bd_net [get_bd_pins uz_user/fix_to_float_current/in_1] [get_bd_pins uz_user/fix_to_float_current/uz_fixdt_to_float_1/in_fixed]
connect_bd_net [get_bd_pins uz_user/fix_to_float_current/in_2] [get_bd_pins uz_user/fix_to_float_current/uz_fixdt_to_float_2/in_fixed]
connect_bd_net [get_bd_pins uz_user/fix_to_float_current/in_3] [get_bd_pins uz_user/fix_to_float_current/uz_fixdt_to_float_3/in_fixed]
connect_bd_net [get_bd_pins uz_user/fix_to_float_current/in_4] [get_bd_pins uz_user/fix_to_float_current/uz_fixdt_to_float_4/in_fixed]
connect_bd_net [get_bd_pins uz_user/fix_to_float_current/in_5] [get_bd_pins uz_user/fix_to_float_current/uz_fixdt_to_float_5/in_fixed]

create_bd_pin -dir I uz_user/fix_to_float_current/clk
create_bd_pin -dir I uz_user/fix_to_float_current/rst
create_bd_pin -dir I uz_user/fix_to_float_current/sp_start
connect_bd_net [get_bd_pins uz_user/fix_to_float_current/clk] [get_bd_pins uz_user/fix_to_float_current/uz_fixdt_to_float_0/ap_clk]
connect_bd_net [get_bd_pins uz_user/fix_to_float_current/rst] [get_bd_pins uz_user/fix_to_float_current/uz_fixdt_to_float_0/ap_rst]
connect_bd_net [get_bd_pins uz_user/fix_to_float_current/sp_start] [get_bd_pins uz_user/fix_to_float_current/uz_fixdt_to_float_0/ap_start]

create_bd_pin -dir O uz_user/fix_to_float_current/ap_done
connect_bd_net [get_bd_pins uz_user/fix_to_float_current/ap_done] [get_bd_pins uz_user/fix_to_float_current/uz_fixdt_to_float_0/ap_done]
endgroup