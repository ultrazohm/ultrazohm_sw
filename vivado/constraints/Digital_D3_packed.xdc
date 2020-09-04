###Analog Adapter Board D3
# Author: Eyke Ligemann
# Date: 19.08.2020

set_property PACKAGE_PIN K10 	[get_ports Dig_Ch3[0]]
set_property PACKAGE_PIN U2 	[get_ports Dig_Ch3[1]]
set_property PACKAGE_PIN L10 	[get_ports Dig_Ch3[2]]
set_property PACKAGE_PIN U3 	[get_ports Dig_Ch3[3]]
set_property PACKAGE_PIN U8 	[get_ports Dig_Ch3[4]]
set_property PACKAGE_PIN V1 	[get_ports Dig_Ch3[5]]
set_property PACKAGE_PIN V8 	[get_ports Dig_Ch3[6]]
set_property PACKAGE_PIN V2 	[get_ports Dig_Ch3[7]]
set_property PACKAGE_PIN V6 	[get_ports Dig_Ch3[8]]
set_property PACKAGE_PIN W1 	[get_ports Dig_Ch3[9]]
set_property PACKAGE_PIN V7 	[get_ports Dig_Ch3[10]]
set_property PACKAGE_PIN W2 	[get_ports Dig_Ch3[11]]
set_property PACKAGE_PIN W5 	[get_ports Dig_Ch3[12]]
set_property PACKAGE_PIN Y1 	[get_ports Dig_Ch3[13]]
set_property PACKAGE_PIN Y5 	[get_ports Dig_Ch3[14]]
set_property PACKAGE_PIN Y2 	[get_ports Dig_Ch3[15]]
set_property PACKAGE_PIN M12 	[get_ports Dig_Ch3[16]]
set_property PACKAGE_PIN U9 	[get_ports Dig_Ch3[17]]
set_property PACKAGE_PIN N12 	[get_ports Dig_Ch3[18]]
set_property PACKAGE_PIN V9 	[get_ports Dig_Ch3[19]]
set_property PACKAGE_PIN P10 	[get_ports Dig_Ch3[20]]
set_property PACKAGE_PIN P11 	[get_ports Dig_Ch3[21]]
set_property PACKAGE_PIN W6 	[get_ports Dig_Ch3[22]]
set_property PACKAGE_PIN W7 	[get_ports Dig_Ch3[23]]
set_property PACKAGE_PIN F10 	[get_ports Dig_Ch3[24]]
set_property PACKAGE_PIN D10 	[get_ports Dig_Ch3[25]]


# Possible Inputs
#set_property PACKAGE_PIN Y5 	[get_ports Dig_15_Ch3]
#set_property PACKAGE_PIN Y2 	[get_ports Dig_16_Ch3]
#set_property PACKAGE_PIN M12 	[get_ports Dig_17_Ch3]
#set_property PACKAGE_PIN U9 	[get_ports Dig_18_Ch3]

#Digital_27_Ch3 = B66_L9_P
set_property PACKAGE_PIN U5 	[get_ports Dig_27_Ch3]
#Digital_28_Ch3 = B66_L6_P
set_property PACKAGE_PIN T1 	[get_ports Dig_28_Ch3]
#Digital_29_Ch3 = B66_L9_N
set_property PACKAGE_PIN U4 	[get_ports Dig_29_Ch3]
#Digital_30_Ch3 = B66_L6_N
set_property PACKAGE_PIN U1 	[get_ports Dig_30_Ch3]


set_property IOSTANDARD LVCMOS18 	[get_ports Dig_*]
set_property PULLDOWN true 			[get_ports {Dig_Ch3}]