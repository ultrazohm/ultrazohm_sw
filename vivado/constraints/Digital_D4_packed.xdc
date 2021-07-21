###Analog Adapter Board D4
# Author: Eyke Ligemann
# Date: 19.08.2020

set_property PACKAGE_PIN A15 [get_ports {D4_OUT[0]}]
set_property PACKAGE_PIN J14 [get_ports {D4_OUT[1]}]
set_property PACKAGE_PIN J12 [get_ports {D4_OUT[2]}]
set_property PACKAGE_PIN E12 [get_ports {D4_OUT[3]}]
set_property PACKAGE_PIN H11 [get_ports {D4_OUT[4]}]
set_property PACKAGE_PIN D12 [get_ports {D4_OUT[5]}]
set_property PACKAGE_PIN H12 [get_ports {D4_OUT[6]}]
set_property PACKAGE_PIN A12 [get_ports {D4_OUT[7]}]
set_property PACKAGE_PIN G11 	[get_ports D4_OUT[8]]
set_property PACKAGE_PIN A11 	[get_ports D4_OUT[9]]
set_property PACKAGE_PIN F12 	[get_ports D4_OUT[10]]
set_property PACKAGE_PIN C12 	[get_ports D4_OUT[11]]
set_property PACKAGE_PIN F11 	[get_ports D4_OUT[12]]
set_property PACKAGE_PIN B11 	[get_ports D4_OUT[13]]
set_property PACKAGE_PIN J11 	[get_ports D4_OUT[14]]
set_property PACKAGE_PIN D11 	[get_ports D4_OUT[15]]
set_property PACKAGE_PIN J10 	[get_ports D4_OUT[16]]
set_property PACKAGE_PIN C11 	[get_ports D4_OUT[17]]
set_property PACKAGE_PIN K13 	[get_ports D4_OUT[18]]
set_property PACKAGE_PIN B10 	[get_ports D4_OUT[19]]
set_property PACKAGE_PIN K12 	[get_ports D4_OUT[20]]
set_property PACKAGE_PIN A10 	[get_ports D4_OUT[21]]
set_property PACKAGE_PIN G10 	[get_ports D4_OUT[22]]
set_property PACKAGE_PIN E10 	[get_ports D4_OUT[23]]
set_property PACKAGE_PIN C14 	[get_ports D4_OUT[24]]
set_property PACKAGE_PIN H14 	[get_ports D4_OUT[25]]

# possible inputs
#set_property PACKAGE_PIN J11 	[get_ports Dig_15_Ch4]
#set_property PACKAGE_PIN D11 	[get_ports Dig_16_Ch4]
#set_property PACKAGE_PIN J10 	[get_ports Dig_17_Ch4]
#set_property PACKAGE_PIN C11 	[get_ports Dig_18_Ch4]

#Digital_27_Ch4 = B47_L4_N
set_property PACKAGE_PIN C13 [get_ports {D4_OUT_27[0]}]
#Digital_28_Ch4 = B47_L12_N
set_property PACKAGE_PIN H13 [get_ports {D4_OUT_28[0]}]
#Digital_29_Ch4 = B47_L1_P
set_property PACKAGE_PIN B15 [get_ports {D4_OUT_29[0]}]
#Digital_30_Ch4 = B47_L11_P
set_property PACKAGE_PIN K14 [get_ports {D4_OUT_30[0]}]

#set_property IOSTANDARD LVCMOS18 	[get_ports Dig_*]
#set_property PULLDOWN true 			[get_ports {Dig_Ch4}]

set_property IOSTANDARD LVCMOS18 [get_ports D4_*]
set_property PULLDOWN true [get_ports {D4_OUT[7]}]
set_property PULLDOWN true [get_ports {D4_OUT[6]}]
set_property PULLDOWN true [get_ports {D4_OUT[5]}]
set_property PULLDOWN true [get_ports {D4_OUT[4]}]
set_property PULLDOWN true [get_ports {D4_OUT[3]}]
set_property PULLDOWN true [get_ports {D4_OUT[2]}]
set_property PULLDOWN true [get_ports {D4_OUT[1]}]
set_property PULLDOWN true [get_ports {D4_OUT[0]}]


