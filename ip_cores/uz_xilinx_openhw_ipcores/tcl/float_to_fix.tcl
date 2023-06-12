update_ip_catalog -rebuild
create_bd_cell -type hier uz_user/float_to_fix_dutycycle
startgroup
create_bd_cell -type ip -vlnv xilinx.com:hls:uz_float_to_sfixdt:1.0 uz_user/float_to_fix_dutycycle/uz_float_to_sfixdt_0
create_bd_cell -type ip -vlnv xilinx.com:hls:uz_float_to_sfixdt:1.0 uz_user/float_to_fix_dutycycle/uz_float_to_sfixdt_1
create_bd_cell -type ip -vlnv xilinx.com:hls:uz_float_to_sfixdt:1.0 uz_user/float_to_fix_dutycycle/uz_float_to_sfixdt_2
create_bd_cell -type ip -vlnv xilinx.com:hls:uz_float_to_sfixdt:1.0 uz_user/float_to_fix_dutycycle/uz_float_to_sfixdt_3
create_bd_cell -type ip -vlnv xilinx.com:hls:uz_float_to_sfixdt:1.0 uz_user/float_to_fix_dutycycle/uz_float_to_sfixdt_4
create_bd_cell -type ip -vlnv xilinx.com:hls:uz_float_to_sfixdt:1.0 uz_user/float_to_fix_dutycycle/uz_float_to_sfixdt_5
connect_bd_net [get_bd_pins uz_user/float_to_fix_dutycycle/uz_float_to_sfixdt_0/ap_clk] [get_bd_pins uz_user/float_to_fix_dutycycle/uz_float_to_sfixdt_1/ap_clk]
connect_bd_net [get_bd_pins uz_user/float_to_fix_dutycycle/uz_float_to_sfixdt_1/ap_clk] [get_bd_pins uz_user/float_to_fix_dutycycle/uz_float_to_sfixdt_2/ap_clk]
connect_bd_net [get_bd_pins uz_user/float_to_fix_dutycycle/uz_float_to_sfixdt_2/ap_clk] [get_bd_pins uz_user/float_to_fix_dutycycle/uz_float_to_sfixdt_3/ap_clk]
connect_bd_net [get_bd_pins uz_user/float_to_fix_dutycycle/uz_float_to_sfixdt_3/ap_clk] [get_bd_pins uz_user/float_to_fix_dutycycle/uz_float_to_sfixdt_4/ap_clk]
connect_bd_net [get_bd_pins uz_user/float_to_fix_dutycycle/uz_float_to_sfixdt_4/ap_clk] [get_bd_pins uz_user/float_to_fix_dutycycle/uz_float_to_sfixdt_5/ap_clk]

connect_bd_net [get_bd_pins uz_user/float_to_fix_dutycycle/uz_float_to_sfixdt_0/ap_rst] [get_bd_pins uz_user/float_to_fix_dutycycle/uz_float_to_sfixdt_1/ap_rst]
connect_bd_net [get_bd_pins uz_user/float_to_fix_dutycycle/uz_float_to_sfixdt_1/ap_rst] [get_bd_pins uz_user/float_to_fix_dutycycle/uz_float_to_sfixdt_2/ap_rst]
connect_bd_net [get_bd_pins uz_user/float_to_fix_dutycycle/uz_float_to_sfixdt_2/ap_rst] [get_bd_pins uz_user/float_to_fix_dutycycle/uz_float_to_sfixdt_3/ap_rst]
connect_bd_net [get_bd_pins uz_user/float_to_fix_dutycycle/uz_float_to_sfixdt_3/ap_rst] [get_bd_pins uz_user/float_to_fix_dutycycle/uz_float_to_sfixdt_4/ap_rst]
connect_bd_net [get_bd_pins uz_user/float_to_fix_dutycycle/uz_float_to_sfixdt_4/ap_rst] [get_bd_pins uz_user/float_to_fix_dutycycle/uz_float_to_sfixdt_5/ap_rst]

connect_bd_net [get_bd_pins uz_user/float_to_fix_dutycycle/uz_float_to_sfixdt_0/ap_start] [get_bd_pins uz_user/float_to_fix_dutycycle/uz_float_to_sfixdt_1/ap_start]
connect_bd_net [get_bd_pins uz_user/float_to_fix_dutycycle/uz_float_to_sfixdt_1/ap_start] [get_bd_pins uz_user/float_to_fix_dutycycle/uz_float_to_sfixdt_2/ap_start]
connect_bd_net [get_bd_pins uz_user/float_to_fix_dutycycle/uz_float_to_sfixdt_2/ap_start] [get_bd_pins uz_user/float_to_fix_dutycycle/uz_float_to_sfixdt_3/ap_start]
connect_bd_net [get_bd_pins uz_user/float_to_fix_dutycycle/uz_float_to_sfixdt_3/ap_start] [get_bd_pins uz_user/float_to_fix_dutycycle/uz_float_to_sfixdt_4/ap_start]
connect_bd_net [get_bd_pins uz_user/float_to_fix_dutycycle/uz_float_to_sfixdt_4/ap_start] [get_bd_pins uz_user/float_to_fix_dutycycle/uz_float_to_sfixdt_5/ap_start]
endgroup

startgroup
create_bd_cell -type ip -vlnv xilinx.com:ip:xlconstant:1.1 uz_user/float_to_fix_dutycycle/dutycycle_fraction
set_property -dict [list \
  CONFIG.CONST_VAL {12} \
  CONFIG.CONST_WIDTH {8} \
] [get_bd_cells uz_user/float_to_fix_dutycycle/dutycycle_fraction]
connect_bd_net [get_bd_pins uz_user/float_to_fix_dutycycle/dutycycle_fraction/dout] [get_bd_pins uz_user/float_to_fix_dutycycle/uz_float_to_sfixdt_0/fraction]
connect_bd_net [get_bd_pins uz_user/float_to_fix_dutycycle/dutycycle_fraction/dout] [get_bd_pins uz_user/float_to_fix_dutycycle/uz_float_to_sfixdt_1/fraction]
connect_bd_net [get_bd_pins uz_user/float_to_fix_dutycycle/dutycycle_fraction/dout] [get_bd_pins uz_user/float_to_fix_dutycycle/uz_float_to_sfixdt_2/fraction]
connect_bd_net [get_bd_pins uz_user/float_to_fix_dutycycle/dutycycle_fraction/dout] [get_bd_pins uz_user/float_to_fix_dutycycle/uz_float_to_sfixdt_3/fraction]
connect_bd_net [get_bd_pins uz_user/float_to_fix_dutycycle/dutycycle_fraction/dout] [get_bd_pins uz_user/float_to_fix_dutycycle/uz_float_to_sfixdt_4/fraction]
connect_bd_net [get_bd_pins uz_user/float_to_fix_dutycycle/dutycycle_fraction/dout] [get_bd_pins uz_user/float_to_fix_dutycycle/uz_float_to_sfixdt_5/fraction]
endgroup

startgroup
create_bd_pin -dir O uz_user/float_to_fix_dutycycle/out_0
create_bd_pin -dir O uz_user/float_to_fix_dutycycle/out_1
create_bd_pin -dir O uz_user/float_to_fix_dutycycle/out_2
create_bd_pin -dir O uz_user/float_to_fix_dutycycle/out_3
create_bd_pin -dir O uz_user/float_to_fix_dutycycle/out_4
create_bd_pin -dir O uz_user/float_to_fix_dutycycle/out_5
connect_bd_net [get_bd_pins uz_user/float_to_fix_dutycycle/out_0] [get_bd_pins uz_user/float_to_fix_dutycycle/uz_float_to_sfixdt_0/out_sfix]
connect_bd_net [get_bd_pins uz_user/float_to_fix_dutycycle/out_1] [get_bd_pins uz_user/float_to_fix_dutycycle/uz_float_to_sfixdt_1/out_sfix]
connect_bd_net [get_bd_pins uz_user/float_to_fix_dutycycle/out_2] [get_bd_pins uz_user/float_to_fix_dutycycle/uz_float_to_sfixdt_2/out_sfix]
connect_bd_net [get_bd_pins uz_user/float_to_fix_dutycycle/out_3] [get_bd_pins uz_user/float_to_fix_dutycycle/uz_float_to_sfixdt_3/out_sfix]
connect_bd_net [get_bd_pins uz_user/float_to_fix_dutycycle/out_4] [get_bd_pins uz_user/float_to_fix_dutycycle/uz_float_to_sfixdt_4/out_sfix]
connect_bd_net [get_bd_pins uz_user/float_to_fix_dutycycle/out_5] [get_bd_pins uz_user/float_to_fix_dutycycle/uz_float_to_sfixdt_5/out_sfix]


create_bd_pin -dir I uz_user/float_to_fix_dutycycle/in_0
create_bd_pin -dir I uz_user/float_to_fix_dutycycle/in_1
create_bd_pin -dir I uz_user/float_to_fix_dutycycle/in_2
create_bd_pin -dir I uz_user/float_to_fix_dutycycle/in_3
create_bd_pin -dir I uz_user/float_to_fix_dutycycle/in_4
create_bd_pin -dir I uz_user/float_to_fix_dutycycle/in_5
connect_bd_net [get_bd_pins uz_user/float_to_fix_dutycycle/in_0] [get_bd_pins uz_user/float_to_fix_dutycycle/uz_float_to_sfixdt_0/in_float]
connect_bd_net [get_bd_pins uz_user/float_to_fix_dutycycle/in_1] [get_bd_pins uz_user/float_to_fix_dutycycle/uz_float_to_sfixdt_1/in_float]
connect_bd_net [get_bd_pins uz_user/float_to_fix_dutycycle/in_2] [get_bd_pins uz_user/float_to_fix_dutycycle/uz_float_to_sfixdt_2/in_float]
connect_bd_net [get_bd_pins uz_user/float_to_fix_dutycycle/in_3] [get_bd_pins uz_user/float_to_fix_dutycycle/uz_float_to_sfixdt_3/in_float]
connect_bd_net [get_bd_pins uz_user/float_to_fix_dutycycle/in_4] [get_bd_pins uz_user/float_to_fix_dutycycle/uz_float_to_sfixdt_4/in_float]
connect_bd_net [get_bd_pins uz_user/float_to_fix_dutycycle/in_5] [get_bd_pins uz_user/float_to_fix_dutycycle/uz_float_to_sfixdt_5/in_float]

create_bd_pin -dir I uz_user/float_to_fix_dutycycle/clk
create_bd_pin -dir I uz_user/float_to_fix_dutycycle/rst
create_bd_pin -dir I uz_user/float_to_fix_dutycycle/sp_start
connect_bd_net [get_bd_pins uz_user/float_to_fix_dutycycle/clk] [get_bd_pins uz_user/float_to_fix_dutycycle/uz_float_to_sfixdt_0/ap_clk]
connect_bd_net [get_bd_pins uz_user/float_to_fix_dutycycle/rst] [get_bd_pins uz_user/float_to_fix_dutycycle/uz_float_to_sfixdt_0/ap_rst]
connect_bd_net [get_bd_pins uz_user/float_to_fix_dutycycle/sp_start] [get_bd_pins uz_user/float_to_fix_dutycycle/uz_float_to_sfixdt_0/ap_start]
endgroup