###Digital Adapter Board D5
# Author: Sebastian Wendel
# Date: 21.03.2019
# 16 I/Os are available 
# All Digital-Pins are 1,8 Volt on Bank47
# Bank47 are High-Density Banks (HD). HD pins have NOT the internal 100R termination resistors and support NO LVDS

# single-ended FPGA pins with 1.8V signal level

#Digital_24_Ch5 = B47_L8_N
set_property PACKAGE_PIN F13 [get_ports Dig_24_Ch5]
#Digital_23_Ch5 = B47_L6_N
set_property PACKAGE_PIN E13 [get_ports Dig_23_Ch5]
#Digital_22_Ch5 = B47_L8_P
set_property PACKAGE_PIN G13 [get_ports Dig_22_Ch5]
#Digital_21_Ch5 = B47_L6_P
set_property PACKAGE_PIN E14 [get_ports Dig_21_Ch5]
#Digital_20_Ch5 = B47_L10_N
set_property PACKAGE_PIN J15 [get_ports Dig_20_Ch5]
#Digital_19_Ch5 = B47_L3_N = I-Line of incremental encoder
set_property PACKAGE_PIN A13 [get_ports Dig_19_Ch5]
#Digital_18_Ch5 = B47_L10_P
set_property PACKAGE_PIN K15 [get_ports Dig_18_Ch5]
#Digital_17_Ch5 = B47_L3_P = B-Line of incremental encoder
set_property PACKAGE_PIN B13 [get_ports Dig_17_Ch5]
#Digital_16_Ch5 = B47_L9_N
set_property PACKAGE_PIN G14 [get_ports Dig_16_Ch5]
#Digital_15_Ch5 = B47_L2_N = A-Line of incremental encoder
set_property PACKAGE_PIN A14 [get_ports Dig_15_Ch5]
#Digital_14_Ch5 = B47_L9_P
set_property PACKAGE_PIN G15 [get_ports Dig_14_Ch5]
#Digital_13_Ch5 = B47_L2_P
set_property PACKAGE_PIN B14 [get_ports Dig_13_Ch5]
#Digital_12_Ch5 = B47_L7_N
set_property PACKAGE_PIN E15 [get_ports Dig_12_Ch5]
#Digital_11_Ch5 = B47_L5_N
set_property PACKAGE_PIN D14 [get_ports Dig_11_Ch5]
#Digital_10_Ch5 = B47_L7_P
set_property PACKAGE_PIN F15 [get_ports Dig_10_Ch5]
#Digital_09_Ch5 = B47_L5_P
set_property PACKAGE_PIN D15 [get_ports Dig_09_Ch5]

#######################################################################################################################################

##Set voltage level
##Set Pin in CMOS Mode for single-ended Signal

set_property IOSTANDARD LVCMOS18 [get_ports Dig_24_Ch5]
set_property IOSTANDARD LVCMOS18 [get_ports Dig_23_Ch5]
set_property IOSTANDARD LVCMOS18 [get_ports Dig_22_Ch5]
set_property IOSTANDARD LVCMOS18 [get_ports Dig_21_Ch5]
set_property IOSTANDARD LVCMOS18 [get_ports Dig_20_Ch5]
set_property IOSTANDARD LVCMOS18 [get_ports Dig_19_Ch5]
set_property IOSTANDARD LVCMOS18 [get_ports Dig_18_Ch5]
set_property IOSTANDARD LVCMOS18 [get_ports Dig_17_Ch5]
set_property IOSTANDARD LVCMOS18 [get_ports Dig_16_Ch5]
set_property IOSTANDARD LVCMOS18 [get_ports Dig_15_Ch5]
set_property IOSTANDARD LVCMOS18 [get_ports Dig_14_Ch5]
set_property IOSTANDARD LVCMOS18 [get_ports Dig_13_Ch5]
set_property IOSTANDARD LVCMOS18 [get_ports Dig_12_Ch5]
set_property IOSTANDARD LVCMOS18 [get_ports Dig_11_Ch5]
set_property IOSTANDARD LVCMOS18 [get_ports Dig_10_Ch5]
set_property IOSTANDARD LVCMOS18 [get_ports Dig_09_Ch5]