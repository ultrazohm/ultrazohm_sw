###Analog Adapter Board D1
# Author: Eyke Ligemann
# Date: 19.08.2020
set_property PACKAGE_PIN AC9  	[get_ports D1_OUT[0]]
set_property PACKAGE_PIN AB9  	[get_ports D1_OUT[1]]
set_property PACKAGE_PIN AB10  	[get_ports D1_OUT[2]]
set_property PACKAGE_PIN AB11  	[get_ports D1_OUT[3]]
set_property PACKAGE_PIN AJ11  	[get_ports D1_OUT[4]]
set_property PACKAGE_PIN AK11  	[get_ports D1_OUT[5]]
#set_property PACKAGE_PIN AA7  	[get_ports D1_OUT[6]]
#set_property PACKAGE_PIN AA8  	[get_ports D1_OUT[7]]
#set_property PACKAGE_PIN AE9  	[get_ports D1_OUT[8]]
#set_property PACKAGE_PIN AD9  	[get_ports D1_OUT[9]]
#set_property PACKAGE_PIN AD11 	[get_ports D1_OUT[10]]
#set_property PACKAGE_PIN AC11 	[get_ports D1_OUT[11]]
set_property PACKAGE_PIN AD6  	[get_ports D1_OUT[6]]
set_property PACKAGE_PIN AC6  	[get_ports D1_OUT[7]]
set_property PACKAGE_PIN AD10 	[get_ports D1_OUT[8]]
set_property PACKAGE_PIN AE10 	[get_ports D1_OUT[9]]
set_property PACKAGE_PIN AF13 	[get_ports D1_OUT[10]]
set_property PACKAGE_PIN AE13 	[get_ports D1_OUT[11]]
set_property PACKAGE_PIN AE12 	[get_ports D1_OUT[12]]
set_property PACKAGE_PIN AD12  	[get_ports D1_OUT[13]]
set_property PACKAGE_PIN AB13  	[get_ports D1_OUT[14]]
set_property PACKAGE_PIN AC13  	[get_ports D1_OUT[15]]
set_property PACKAGE_PIN AA12  	[get_ports D1_OUT[16]]
set_property PACKAGE_PIN AA11  	[get_ports D1_OUT[17]]
set_property PACKAGE_PIN AF1  	[get_ports D1_OUT[18]]
set_property PACKAGE_PIN AF2  	[get_ports D1_OUT[19]]

set_property PACKAGE_PIN AA7  	[get_ports D1_OUT2[0]]
set_property PACKAGE_PIN AA8  	[get_ports D1_OUT2[1]]
set_property PACKAGE_PIN AE9  	[get_ports D1_OUT2[2]]
set_property PACKAGE_PIN AD9  	[get_ports D1_OUT2[3]]
set_property PACKAGE_PIN AD11 	[get_ports D1_OUT2[4]]
set_property PACKAGE_PIN AC11 	[get_ports D1_OUT2[5]]


#Digital_27_Ch1 = B65_L19_N
set_property PACKAGE_PIN AC3  	[get_ports D1_OUT_27]
#Digital_28_Ch1= B65_L19_P
set_property PACKAGE_PIN AB3  	[get_ports D1_OUT_28]
#Digital_29_Ch1 = B65_L15_N
set_property PACKAGE_PIN AA5  	[get_ports D1_OUT_29]
#Digital_30_Ch1 = B65_L15_P
set_property PACKAGE_PIN AA6  	[get_ports D1_OUT_30]


set_property IOSTANDARD LVCMOS18 	[get_ports {D1_*}]
set_property PULLDOWN true 			[get_ports D1_OUT]
set_property PULLDOWN true 			[get_ports D1_OUT2]
