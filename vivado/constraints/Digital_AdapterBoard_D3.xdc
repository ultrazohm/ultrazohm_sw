###Digital Adapter Board D3
# Author: Sebastian Wendel
# Date: 16.07.2019
# 30 I/Os are available
# All Digital-Pins are 1,8 Volt on Bank48 and Bank66
# Bank48 are High-Density Banks (HD). HD pins have NOT the internal 100R termination resistors and support NO LVDS
# Bank66 are High-Performance Banks (HP). HP pins have the internal 100R termination resistors and support LVDS

# single-ended FPGA pins with 1.8V signal level

#Digital_01_Ch3 = B66_L24_N
set_property PACKAGE_PIN K10 [get_ports Dig_01_Ch3]
#Digital_02_Ch3 = B66_L5_P
set_property PACKAGE_PIN U2 [get_ports Dig_02_Ch3]
#Digital_03_Ch3 = B66_L24_P
set_property PACKAGE_PIN L10 [get_ports Dig_03_Ch3]
#Digital_04_Ch3 = B66_L5_N
set_property PACKAGE_PIN U3 [get_ports Dig_04_Ch3]
#Digital_05_Ch3 = B66_L13_P
set_property PACKAGE_PIN U8 [get_ports Dig_05_Ch3]
#Digital_06_Ch3 = B66_L4_N
set_property PACKAGE_PIN V1 [get_ports Dig_06_Ch3]
#Digital_07_Ch3 = B66_L13_N
set_property PACKAGE_PIN V8 [get_ports Dig_07_Ch3]
#Digital_08_Ch3 = B66_L4_P
set_property PACKAGE_PIN V2 [get_ports Dig_08_Ch3]
#Digital_09_Ch3 = B66_L11_N
set_property PACKAGE_PIN V6 [get_ports Dig_09_Ch3]
#Digital_10_Ch3 = B66_L3_N
set_property PACKAGE_PIN W1 [get_ports Dig_10_Ch3]
#Digital_11_Ch3 = B66_L11_P
set_property PACKAGE_PIN V7 [get_ports Dig_11_Ch3]
#Digital_12_Ch3 = B66_L3_P
set_property PACKAGE_PIN W2 [get_ports Dig_12_Ch3]
#Digital_13_Ch3 = B66_L7_P
set_property PACKAGE_PIN W5 [get_ports Dig_13_Ch3]
#Digital_14_Ch3 = B66_L2_N
set_property PACKAGE_PIN Y1 [get_ports Dig_14_Ch3]
#Digital_15_Ch3 = B66_L7_N
set_property PACKAGE_PIN Y5 [get_ports Dig_15_Ch3]
#Digital_16_Ch3 = B66_L2_P
set_property PACKAGE_PIN Y2 [get_ports Dig_16_Ch3]
#Digital_17_Ch3 = B66_L21_N
set_property PACKAGE_PIN M12 [get_ports Dig_17_Ch3]
#Digital_18_Ch3 = B66_L17_P
set_property PACKAGE_PIN U9 [get_ports Dig_18_Ch3]
#Digital_19_Ch3 = B66_L21_P
set_property PACKAGE_PIN N12 [get_ports Dig_19_Ch3]
#Digital_20_Ch3 = B66_L17_N
set_property PACKAGE_PIN V9 [get_ports Dig_20_Ch3]
#Digital_21_Ch3 = B66_L20_N
set_property PACKAGE_PIN P10 [get_ports Dig_21_Ch3]
#Digital_22_Ch3 = B66_L20_P
set_property PACKAGE_PIN P11 [get_ports Dig_22_Ch3]
#Digital_23_Ch3 = B66_L12_N
set_property PACKAGE_PIN W6 [get_ports Dig_23_Ch3]
#Digital_24_Ch3 = B66_L12_P
set_property PACKAGE_PIN W7 [get_ports Dig_24_Ch3]
#Digital_25_Ch3 = B48_L8_N
set_property PACKAGE_PIN F10 [get_ports Dig_25_Ch3]
#Digital_26_Ch3 = B48_L6_N
set_property PACKAGE_PIN D10 [get_ports Dig_26_Ch3]
#Digital_27_Ch3 = B66_L9_P
set_property PACKAGE_PIN U5 [get_ports Dig_27_Ch3]
#Digital_28_Ch3 = B66_L6_P
set_property PACKAGE_PIN T1 [get_ports Dig_28_Ch3]
#Digital_29_Ch3 = B66_L9_N
set_property PACKAGE_PIN U4 [get_ports Dig_29_Ch3]
#Digital_30_Ch3 = B66_L6_N
set_property PACKAGE_PIN U1 [get_ports Dig_30_Ch3]

#######################################################################################################################################

##Set voltage level
##Set Pin in CMOS Mode for single-ended Signal

set_property IOSTANDARD LVCMOS18 [get_ports Dig_01_Ch3]
set_property IOSTANDARD LVCMOS18 [get_ports Dig_02_Ch3]
set_property IOSTANDARD LVCMOS18 [get_ports Dig_03_Ch3]
set_property IOSTANDARD LVCMOS18 [get_ports Dig_04_Ch3]
set_property IOSTANDARD LVCMOS18 [get_ports Dig_05_Ch3]
set_property IOSTANDARD LVCMOS18 [get_ports Dig_06_Ch3]
set_property IOSTANDARD LVCMOS18 [get_ports Dig_07_Ch3]
set_property IOSTANDARD LVCMOS18 [get_ports Dig_08_Ch3]
set_property IOSTANDARD LVCMOS18 [get_ports Dig_09_Ch3]
set_property IOSTANDARD LVCMOS18 [get_ports Dig_10_Ch3]
set_property IOSTANDARD LVCMOS18 [get_ports Dig_11_Ch3]
set_property IOSTANDARD LVCMOS18 [get_ports Dig_12_Ch3]
set_property IOSTANDARD LVCMOS18 [get_ports Dig_13_Ch3]
set_property IOSTANDARD LVCMOS18 [get_ports Dig_14_Ch3]
set_property IOSTANDARD LVCMOS18 [get_ports Dig_15_Ch3]
set_property IOSTANDARD LVCMOS18 [get_ports Dig_16_Ch3]
set_property IOSTANDARD LVCMOS18 [get_ports Dig_17_Ch3]
set_property IOSTANDARD LVCMOS18 [get_ports Dig_18_Ch3]
set_property IOSTANDARD LVCMOS18 [get_ports Dig_19_Ch3]
set_property IOSTANDARD LVCMOS18 [get_ports Dig_20_Ch3]
set_property IOSTANDARD LVCMOS18 [get_ports Dig_21_Ch3]
set_property IOSTANDARD LVCMOS18 [get_ports Dig_22_Ch3]
set_property IOSTANDARD LVCMOS18 [get_ports Dig_23_Ch3]
set_property IOSTANDARD LVCMOS18 [get_ports Dig_24_Ch3]
set_property IOSTANDARD LVCMOS18 [get_ports Dig_25_Ch3]
set_property IOSTANDARD LVCMOS18 [get_ports Dig_26_Ch3]
set_property IOSTANDARD LVCMOS18 [get_ports Dig_27_Ch3]
set_property IOSTANDARD LVCMOS18 [get_ports Dig_28_Ch3]
set_property IOSTANDARD LVCMOS18 [get_ports Dig_29_Ch3]
set_property IOSTANDARD LVCMOS18 [get_ports Dig_30_Ch3]