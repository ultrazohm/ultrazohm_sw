###Analog Adapter Board D2 
# Author: Eyke Ligemann
# Date: 19.08.2020
set_property PACKAGE_PIN W4 	[get_ports Dig_Ch2[0]]
set_property PACKAGE_PIN U10 	[get_ports Dig_Ch2[1]]
set_property PACKAGE_PIN U11 	[get_ports Dig_Ch2[2]]
set_property PACKAGE_PIN U6 	[get_ports Dig_Ch2[3]]
set_property PACKAGE_PIN V11 	[get_ports Dig_Ch2[4]]
set_property PACKAGE_PIN U7 	[get_ports Dig_Ch2[5]]
set_property PACKAGE_PIN Y3 	[get_ports Dig_Ch2[6]]
set_property PACKAGE_PIN N11 	[get_ports Dig_Ch2[7]]
set_property PACKAGE_PIN Y4 	[get_ports Dig_Ch2[8]]
set_property PACKAGE_PIN Y10 	[get_ports Dig_Ch2[9]]
set_property PACKAGE_PIN Y7 	[get_ports Dig_Ch2[10]]
set_property PACKAGE_PIN Y8 	[get_ports Dig_Ch2[11]]
set_property PACKAGE_PIN V3 	[get_ports Dig_Ch2[12]]
set_property PACKAGE_PIN Y9 	[get_ports Dig_Ch2[13]]
set_property PACKAGE_PIN AE1 	[get_ports Dig_Ch2[14]]
set_property PACKAGE_PIN AE7 	[get_ports Dig_Ch2[15]]
set_property PACKAGE_PIN AE8 	[get_ports Dig_Ch2[16]] 
set_property PACKAGE_PIN AC12 	[get_ports Dig_Ch2[17]] 
set_property PACKAGE_PIN AA1 	[get_ports Dig_Ch2[18]]
set_property PACKAGE_PIN AB1 	[get_ports Dig_Ch2[19]]
set_property PACKAGE_PIN AC1 	[get_ports Dig_Ch2[20]]
set_property PACKAGE_PIN AD1 	[get_ports Dig_Ch2[21]]
set_property PACKAGE_PIN AA2 	[get_ports Dig_Ch2[22]]
set_property PACKAGE_PIN AA3 	[get_ports Dig_Ch2[23]]
set_property PACKAGE_PIN W10 	[get_ports Dig_Ch2[24]]
set_property PACKAGE_PIN T10 	[get_ports Dig_Ch2[25]]


# Possible Inputs
#set_property PACKAGE_PIN AE1 [get_ports Dig_15_Ch2]
#set_property PACKAGE_PIN AE7 [get_ports Dig_16_Ch2]
#set_property PACKAGE_PIN AE8 [get_ports Dig_17_Ch2]
#set_property PACKAGE_PIN AC12 [get_ports Dig_18_Ch2]


#Digital_27_Ch2 = B66_L16_P
set_property PACKAGE_PIN W11 [get_ports Dig_27_Ch2]
#Digital_28_Ch2 = B66_L19_P
set_property PACKAGE_PIN R10 [get_ports Dig_28_Ch2]
#Digital_29_Ch2 = B66_L8_P
set_property PACKAGE_PIN V4 [get_ports Dig_29_Ch2]
#Digital_30_Ch2 = B66_L18_P
set_property PACKAGE_PIN T11 [get_ports Dig_30_Ch2]


set_property IOSTANDARD LVCMOS18 [get_ports Dig_*]
set_property PULLDOWN true [get_ports {Dig_Ch2}]
