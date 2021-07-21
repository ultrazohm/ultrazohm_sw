###Analog Adapter Board D3
# Author: Eyke Ligemann
# Date: 19.08.2020

set_property PACKAGE_PIN K10 [get_ports {D3_OUT[0]}]
set_property PACKAGE_PIN U2 [get_ports {D3_OUT[1]}]
set_property PACKAGE_PIN L10 [get_ports {D3_OUT[2]}]
set_property PACKAGE_PIN U3 [get_ports {D3_OUT[3]}]
set_property PACKAGE_PIN U8 [get_ports {D3_OUT[4]}]
set_property PACKAGE_PIN V1 [get_ports {D3_OUT[5]}]
set_property PACKAGE_PIN V8 [get_ports {D3_OUT[6]}]
set_property PACKAGE_PIN V2 [get_ports {D3_OUT[7]}]
set_property PACKAGE_PIN V6 [get_ports {D3_OUT[8]}]
set_property PACKAGE_PIN W1 [get_ports {D3_OUT[9]}]
set_property PACKAGE_PIN V7 [get_ports {D3_OUT[10]}]
set_property PACKAGE_PIN W2 [get_ports {D3_OUT[11]}]
set_property PACKAGE_PIN W5 [get_ports {D3_OUT[12]}]
set_property PACKAGE_PIN Y1 [get_ports {D3_OUT[13]}]
set_property PACKAGE_PIN Y5 [get_ports {D3_OUT[14]}]
set_property PACKAGE_PIN Y2 [get_ports {D3_OUT[15]}]
set_property PACKAGE_PIN M12 [get_ports {D3_OUT[16]}]
set_property PACKAGE_PIN U9 [get_ports {D3_OUT[17]}]
set_property PACKAGE_PIN N12 [get_ports {D3_OUT[18]}]
set_property PACKAGE_PIN V9 [get_ports {D3_OUT[19]}]
set_property PACKAGE_PIN P10 [get_ports {D3_OUT[20]}]
set_property PACKAGE_PIN P11 [get_ports {D3_OUT[21]}]
set_property PACKAGE_PIN W6 [get_ports {D3_OUT[22]}]
set_property PACKAGE_PIN W7 [get_ports {D3_OUT[23]}]
set_property PACKAGE_PIN F10 [get_ports {D3_OUT[24]}]
set_property PACKAGE_PIN D10 [get_ports {D3_OUT[25]}]


# Possible Inputs
#set_property PACKAGE_PIN Y5 	[get_ports Dig_15_Ch3]
#set_property PACKAGE_PIN Y2 	[get_ports Dig_16_Ch3]
#set_property PACKAGE_PIN M12 	[get_ports Dig_17_Ch3]
#set_property PACKAGE_PIN U9 	[get_ports Dig_18_Ch3]

#Digital_27_Ch3 = B66_L9_P
set_property PACKAGE_PIN U5 [get_ports {D3_OUT_27[0]}]
#Digital_28_Ch3 = B66_L6_P
set_property PACKAGE_PIN T1 [get_ports {D3_OUT_28[0]}]
#Digital_29_Ch3 = B66_L9_N
set_property PACKAGE_PIN U4 [get_ports {D3_OUT_29[0]}]
#Digital_30_Ch3 = B66_L6_N
set_property PACKAGE_PIN U1 [get_ports {D3_OUT_30[0]}]



set_property IOSTANDARD LVCMOS18 [get_ports D3_*]
set_property PULLDOWN true [get_ports {D3_OUT[25]}]
set_property PULLDOWN true [get_ports {D3_OUT[24]}]
set_property PULLDOWN true [get_ports {D3_OUT[23]}]
set_property PULLDOWN true [get_ports {D3_OUT[22]}]
set_property PULLDOWN true [get_ports {D3_OUT[21]}]
set_property PULLDOWN true [get_ports {D3_OUT[20]}]
set_property PULLDOWN true [get_ports {D3_OUT[19]}]
set_property PULLDOWN true [get_ports {D3_OUT[18]}]
set_property PULLDOWN true [get_ports {D3_OUT[17]}]
set_property PULLDOWN true [get_ports {D3_OUT[16]}]
set_property PULLDOWN true [get_ports {D3_OUT[15]}]
set_property PULLDOWN true [get_ports {D3_OUT[14]}]
set_property PULLDOWN true [get_ports {D3_OUT[13]}]
set_property PULLDOWN true [get_ports {D3_OUT[12]}]
set_property PULLDOWN true [get_ports {D3_OUT[11]}]
set_property PULLDOWN true [get_ports {D3_OUT[10]}]
set_property PULLDOWN true [get_ports {D3_OUT[9]}]
set_property PULLDOWN true [get_ports {D3_OUT[8]}]
set_property PULLDOWN true [get_ports {D3_OUT[7]}]
set_property PULLDOWN true [get_ports {D3_OUT[6]}]
set_property PULLDOWN true [get_ports {D3_OUT[5]}]
set_property PULLDOWN true [get_ports {D3_OUT[4]}]
set_property PULLDOWN true [get_ports {D3_OUT[3]}]
set_property PULLDOWN true [get_ports {D3_OUT[2]}]
set_property PULLDOWN true [get_ports {D3_OUT[1]}]
set_property PULLDOWN true [get_ports {D3_OUT[0]}]


