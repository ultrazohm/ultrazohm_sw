###Analog Adapter Board D4
# Author: Eyke Ligemann
# Date: 19.08.2020

set_property PACKAGE_PIN A15 [get_ports Dig_00_Ch4]
set_property PACKAGE_PIN J14 [get_ports Dig_01_Ch4]
set_property PACKAGE_PIN J12 [get_ports Dig_02_Ch4]
set_property PACKAGE_PIN E12 [get_ports Dig_03_Ch4]
set_property PACKAGE_PIN H11 [get_ports Dig_04_Ch4]
set_property PACKAGE_PIN D12 [get_ports Dig_05_Ch4]
set_property PACKAGE_PIN H12 [get_ports Dig_06_Ch4]
set_property PACKAGE_PIN A12 [get_ports Dig_07_Ch4]
set_property PACKAGE_PIN G11 	[get_ports Dig_08_Ch4]
set_property PACKAGE_PIN A11 	[get_ports Dig_09_Ch4]
set_property PACKAGE_PIN F12 	[get_ports Dig_10_Ch4]
set_property PACKAGE_PIN C12 	[get_ports Dig_11_Ch4]
set_property PACKAGE_PIN F11 	[get_ports Dig_12_Ch4]
set_property PACKAGE_PIN B11 	[get_ports Dig_13_Ch4]
set_property PACKAGE_PIN J11 	[get_ports Dig_14_Ch4]
set_property PACKAGE_PIN D11 	[get_ports Dig_15_Ch4]
set_property PACKAGE_PIN J10 	[get_ports Dig_16_Ch4]
set_property PACKAGE_PIN C11 	[get_ports Dig_17_Ch4]
set_property PACKAGE_PIN K13 	[get_ports Dig_18_Ch4]
set_property PACKAGE_PIN B10 	[get_ports Dig_19_Ch4]
set_property PACKAGE_PIN K12 	[get_ports Dig_20_Ch4]
set_property PACKAGE_PIN A10 	[get_ports Dig_21_Ch4]
set_property PACKAGE_PIN G10 	[get_ports Dig_22_Ch4]
set_property PACKAGE_PIN E10 	[get_ports Dig_23_Ch4]
set_property PACKAGE_PIN C14 	[get_ports Dig_24_Ch4]
set_property PACKAGE_PIN H14 	[get_ports Dig_25_Ch4]

# changed to zero-based numbering, starting from 00 to 29 on 24.03.2022
#Digital_27_Ch4 = B47_L4_N
set_property PACKAGE_PIN C13 [get_ports {D4_OUT_26[0]}]
#Digital_28_Ch4 = B47_L12_N
set_property PACKAGE_PIN H13 [get_ports {D4_OUT_27[0]}]
#Digital_29_Ch4 = B47_L1_P
set_property PACKAGE_PIN B15 [get_ports {D4_OUT_28[0]}]
#Digital_30_Ch4 = B47_L11_P
set_property PACKAGE_PIN K14 [get_ports {D4_OUT_29[0]}]

set_property IOSTANDARD LVCMOS18 [get_ports D4_*]
set_property PULLDOWN true [get_ports {D4_OUT[7]}]
set_property PULLDOWN true [get_ports {D4_OUT[6]}]
set_property PULLDOWN true [get_ports {D4_OUT[5]}]
set_property PULLDOWN true [get_ports {D4_OUT[4]}]
set_property PULLDOWN true [get_ports {D4_OUT[3]}]
set_property PULLDOWN true [get_ports {D4_OUT[2]}]
set_property PULLDOWN true [get_ports {D4_OUT[1]}]
set_property PULLDOWN true [get_ports {D4_OUT[0]}]

