###Analog Adapter Board D1
# Author: Eyke Ligemann
# Date: 19.08.2020
set_property PACKAGE_PIN AC9 [get_ports Dig_00_Ch1]
set_property PACKAGE_PIN AB9 [get_ports Dig_01_Ch1]
set_property PACKAGE_PIN AB10 [get_ports Dig_02_Ch1]
set_property PACKAGE_PIN AB11 [get_ports Dig_03_Ch1]
set_property PACKAGE_PIN AJ11 [get_ports Dig_04_Ch1]
set_property PACKAGE_PIN AK11 [get_ports Dig_05_Ch1]
set_property PACKAGE_PIN AA7  	[get_ports Dig_06_Ch1]
set_property PACKAGE_PIN AA8  	[get_ports Dig_07_Ch1]
set_property PACKAGE_PIN AE9  	[get_ports Dig_08_Ch1]
set_property PACKAGE_PIN AD9  	[get_ports Dig_09_Ch1]
set_property PACKAGE_PIN AD11 	[get_ports Dig_10_Ch1]
set_property PACKAGE_PIN AC11 	[get_ports Dig_11_Ch1]
set_property PACKAGE_PIN AD6  	[get_ports Dig_12_Ch1]
set_property PACKAGE_PIN AC6  	[get_ports Dig_13_Ch1]
set_property PACKAGE_PIN AD10 	[get_ports Dig_14_Ch1]
set_property PACKAGE_PIN AE10 	[get_ports Dig_15_Ch1]
set_property PACKAGE_PIN AF13 	[get_ports Dig_16_Ch1]
set_property PACKAGE_PIN AE13 	[get_ports Dig_17_Ch1]
set_property PACKAGE_PIN AE12 	[get_ports Dig_18_Ch1]
set_property PACKAGE_PIN AD12  	[get_ports Dig_19_Ch1]
set_property PACKAGE_PIN AB13  	[get_ports Dig_20_Ch1]
set_property PACKAGE_PIN AC13  	[get_ports Dig_21_Ch1]
set_property PACKAGE_PIN AA12  	[get_ports Dig_22_Ch1]
set_property PACKAGE_PIN AA11  	[get_ports Dig_23_Ch1]
set_property PACKAGE_PIN AF1  	[get_ports Dig_24_Ch1]
set_property PACKAGE_PIN AF2  	[get_ports Dig_25_Ch1]


# changed to zero-based numbering, starting from 00 to 29 on 24.03.2022
#Digital_27_Ch1 = B65_L19_N
set_property PACKAGE_PIN AC3 [get_ports {D1_OUT_26[0]}]
#Digital_28_Ch1= B65_L19_P
set_property PACKAGE_PIN AB3 [get_ports {D1_OUT_27[0]}]
#Digital_29_Ch1 = B65_L15_N
set_property PACKAGE_PIN AA5 [get_ports {D1_OUT_28[0]}]
#Digital_30_Ch1 = B65_L15_P
set_property PACKAGE_PIN AA6 [get_ports {D1_OUT_29[0]}]


set_property IOSTANDARD LVCMOS18 [get_ports D1_*]
set_property PULLDOWN true [get_ports {D1_OUT[5]}]
set_property PULLDOWN true [get_ports {D1_OUT[4]}]
set_property PULLDOWN true [get_ports {D1_OUT[3]}]
set_property PULLDOWN true [get_ports {D1_OUT[2]}]
set_property PULLDOWN true [get_ports {D1_OUT[1]}]
set_property PULLDOWN true [get_ports {D1_OUT[0]}]

