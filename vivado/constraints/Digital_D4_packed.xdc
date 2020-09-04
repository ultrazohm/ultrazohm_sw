###Analog Adapter Board D4
# Author: Eyke Ligemann
# Date: 19.08.2020

set_property PACKAGE_PIN A15 	[get_ports Dig_Ch4[0]]
set_property PACKAGE_PIN J14 	[get_ports Dig_Ch4[1]]
set_property PACKAGE_PIN J12 	[get_ports Dig_Ch4[2]]
set_property PACKAGE_PIN E12 	[get_ports Dig_Ch4[3]]
set_property PACKAGE_PIN H11 	[get_ports Dig_Ch4[4]]
set_property PACKAGE_PIN D12 	[get_ports Dig_Ch4[5]]
set_property PACKAGE_PIN H12 	[get_ports Dig_Ch4[6]]
set_property PACKAGE_PIN A12 	[get_ports Dig_Ch4[7]]
set_property PACKAGE_PIN G11 	[get_ports Dig_Ch4[8]]
set_property PACKAGE_PIN A11 	[get_ports Dig_Ch4[9]]
set_property PACKAGE_PIN F12 	[get_ports Dig_Ch4[10]]
set_property PACKAGE_PIN C12 	[get_ports Dig_Ch4[11]]
set_property PACKAGE_PIN F11 	[get_ports Dig_Ch4[12]]
set_property PACKAGE_PIN B11 	[get_ports Dig_Ch4[13]]
set_property PACKAGE_PIN J11 	[get_ports Dig_Ch4[14]]
set_property PACKAGE_PIN D11 	[get_ports Dig_Ch4[15]]
set_property PACKAGE_PIN J10 	[get_ports Dig_Ch4[16]]
set_property PACKAGE_PIN C11 	[get_ports Dig_Ch4[17]]
set_property PACKAGE_PIN K13 	[get_ports Dig_Ch4[18]]
set_property PACKAGE_PIN B10 	[get_ports Dig_Ch4[19]]
set_property PACKAGE_PIN K12 	[get_ports Dig_Ch4[20]]
set_property PACKAGE_PIN A10 	[get_ports Dig_Ch4[21]]
set_property PACKAGE_PIN G10 	[get_ports Dig_Ch4[22]]
set_property PACKAGE_PIN E10 	[get_ports Dig_Ch4[23]]
set_property PACKAGE_PIN C14 	[get_ports Dig_Ch4[24]]
set_property PACKAGE_PIN H14 	[get_ports Dig_Ch4[25]]

# possible inputs
#set_property PACKAGE_PIN J11 	[get_ports Dig_15_Ch4]
#set_property PACKAGE_PIN D11 	[get_ports Dig_16_Ch4]
#set_property PACKAGE_PIN J10 	[get_ports Dig_17_Ch4]
#set_property PACKAGE_PIN C11 	[get_ports Dig_18_Ch4]

#Digital_27_Ch4 = B47_L4_N
set_property PACKAGE_PIN C13 	[get_ports Dig_27_Ch4]
#Digital_28_Ch4 = B47_L12_N
set_property PACKAGE_PIN H13 	[get_ports Dig_28_Ch4]
#Digital_29_Ch4 = B47_L1_P
set_property PACKAGE_PIN B15 	[get_ports Dig_29_Ch4]
#Digital_30_Ch4 = B47_L11_P
set_property PACKAGE_PIN K14 	[get_ports Dig_30_Ch4]

set_property IOSTANDARD LVCMOS18 	[get_ports Dig_*]
set_property PULLDOWN true 			[get_ports {Dig_Ch4}]