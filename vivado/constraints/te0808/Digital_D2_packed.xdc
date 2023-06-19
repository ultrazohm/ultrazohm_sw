###Analog Adapter Board D2
# Author: Eyke Ligemann
# Date: 19.08.2020
set_property PACKAGE_PIN W4 [get_ports Dig_00_Ch2]
set_property PACKAGE_PIN U10 [get_ports Dig_01_Ch2]
set_property PACKAGE_PIN U11 [get_ports Dig_02_Ch2]
set_property PACKAGE_PIN U6 [get_ports Dig_03_Ch2]
set_property PACKAGE_PIN V11 [get_ports Dig_04_Ch2]
set_property PACKAGE_PIN U7 [get_ports Dig_05_Ch2]
set_property PACKAGE_PIN Y3 [get_ports Dig_06_Ch2]
set_property PACKAGE_PIN N11 [get_ports Dig_07_Ch2]
set_property PACKAGE_PIN Y4 [get_ports Dig_08_Ch2]
set_property PACKAGE_PIN Y10 [get_ports Dig_09_C2]
set_property PACKAGE_PIN Y7 [get_ports Dig_10_Ch2]
set_property PACKAGE_PIN Y8 [get_ports Dig_11_Ch2]
set_property PACKAGE_PIN V3 	[get_ports Dig_12_Ch2]
set_property PACKAGE_PIN Y9 	[get_ports Dig_13_Ch2]
set_property PACKAGE_PIN AE1 	[get_ports Dig_14_Ch2]
set_property PACKAGE_PIN AE7 	[get_ports Dig_15_Ch2]
set_property PACKAGE_PIN AE8 	[get_ports Dig_16_Ch2]
set_property PACKAGE_PIN AC12 	[get_ports Dig_17_Ch2]
set_property PACKAGE_PIN AA1 	[get_ports Dig_18_Ch2]
set_property PACKAGE_PIN AB1 	[get_ports Dig_19_Ch2]
set_property PACKAGE_PIN AC1 	[get_ports Dig_20_Ch2]
set_property PACKAGE_PIN AD1 	[get_ports Dig_21_Ch2]
set_property PACKAGE_PIN AA2 	[get_ports Dig_22_Ch2]
set_property PACKAGE_PIN AA3 	[get_ports Dig_23_Ch2]
set_property PACKAGE_PIN W10 	[get_ports Dig_24_Ch2]
set_property PACKAGE_PIN T10 	[get_ports Dig_25_Ch2]


# changed to zero-based numbering, starting from 00 to 29 on 24.03.2022
#Digital_27_Ch2 = B66_L16_P
set_property PACKAGE_PIN W11 [get_ports {D2_OUT_26[0]}]
#Digital_28_Ch2 = B66_L19_P
set_property PACKAGE_PIN R10 [get_ports {D2_OUT_27[0]}]
#Digital_29_Ch2 = B66_L8_P
set_property PACKAGE_PIN V4 [get_ports {D2_OUT_28[0]}]
#Digital_30_Ch2 = B66_L18_P
set_property PACKAGE_PIN T11 [get_ports {D2_OUT_29[0]}]


set_property IOSTANDARD LVCMOS18 [get_ports D2_*]
set_property PULLDOWN true [get_ports {D2_OUT[11]}]
set_property PULLDOWN true [get_ports {D2_OUT[10]}]
set_property PULLDOWN true [get_ports {D2_OUT[9]}]
set_property PULLDOWN true [get_ports {D2_OUT[8]}]
set_property PULLDOWN true [get_ports {D2_OUT[7]}]
set_property PULLDOWN true [get_ports {D2_OUT[6]}]
set_property PULLDOWN true [get_ports {D2_OUT[5]}]
set_property PULLDOWN true [get_ports {D2_OUT[4]}]
set_property PULLDOWN true [get_ports {D2_OUT[3]}]
set_property PULLDOWN true [get_ports {D2_OUT[2]}]
set_property PULLDOWN true [get_ports {D2_OUT[1]}]
set_property PULLDOWN true [get_ports {D2_OUT[0]}]

