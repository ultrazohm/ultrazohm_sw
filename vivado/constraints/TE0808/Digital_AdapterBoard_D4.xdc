###Digital Adapter Board D4
# Author: Sebastian Wendel
# Date: 21.03.2019
# 30 I/Os are available
# All Digital-Pins are 1,8 Volt on Bank47 and Bank48
# Bank47 and Bank48 are High-Density Banks (HD). HD pins have NOT the internal 100R termination resistors and support NO LVDS

# single-ended FPGA pins with 1.8V signal level

#Digital_01_Ch4 = B47_L1_N
set_property PACKAGE_PIN A15 [get_ports Dig_01_Ch4]
#Digital_02_Ch4 = B47_L11_N
set_property PACKAGE_PIN J14 [get_ports Dig_02_Ch4]
#Digital_03_Ch4 = B48_L11_P
set_property PACKAGE_PIN J12 [get_ports Dig_03_Ch4]
#Digital_04_Ch4 = B48_L5_P
set_property PACKAGE_PIN E12 [get_ports Dig_04_Ch4]
#Digital_05_Ch4 = B48_L11_N
set_property PACKAGE_PIN H11 [get_ports Dig_05_Ch4]
#Digital_06_Ch4 = B48_L5_N
set_property PACKAGE_PIN D12 [get_ports Dig_06_Ch4]
#Digital_07_Ch4 = B48_L10_P
set_property PACKAGE_PIN H12 [get_ports Dig_07_Ch4]
#Digital_08_Ch4 = B48_L2_P
set_property PACKAGE_PIN A12 [get_ports Dig_08_Ch4]
#Digital_09_Ch4 = B48_L10_N
set_property PACKAGE_PIN G11 [get_ports Dig_09_Ch4]
#Digital_10_Ch4 = B48_L2_N
set_property PACKAGE_PIN A11 [get_ports Dig_10_Ch4]
#Digital_11_Ch4 = B48_L7_P
set_property PACKAGE_PIN F12 [get_ports Dig_11_Ch4]
#Digital_12_Ch4 = B48_L1_P
set_property PACKAGE_PIN C12 [get_ports Dig_12_Ch4]
#Digital_13_Ch4 = B48_L7_N
set_property PACKAGE_PIN F11 [get_ports Dig_13_Ch4]
#Digital_14_Ch4 = B48_L1_N
set_property PACKAGE_PIN B11 [get_ports Dig_14_Ch4]
#Digital_15_Ch4 = B48_L12_P
set_property PACKAGE_PIN J11 [get_ports Dig_15_Ch4]
#Digital_16_Ch4 = B48_L4_P
set_property PACKAGE_PIN D11 [get_ports Dig_16_Ch4]
#Digital_17_Ch4 = B48_L12_N
set_property PACKAGE_PIN J10 [get_ports Dig_17_Ch4]
#Digital_18_Ch4 = B48_L4_N
set_property PACKAGE_PIN C11 [get_ports Dig_18_Ch4]
#Digital_19_Ch4 = B48_L9_P
set_property PACKAGE_PIN K13 [get_ports Dig_19_Ch4]
#Digital_20_Ch4 = B48_L3_P
set_property PACKAGE_PIN B10 [get_ports Dig_20_Ch4]
#Digital_21_Ch4 = B48_L9_N
set_property PACKAGE_PIN K12 [get_ports Dig_21_Ch4]
#Digital_22_Ch4 = B48_L3_N
set_property PACKAGE_PIN A10 [get_ports Dig_22_Ch4]
#Digital_23_Ch4 = B48_L8_P
set_property PACKAGE_PIN G10 [get_ports Dig_23_Ch4]
#Digital_24_Ch4 = B48_L6_P
set_property PACKAGE_PIN E10 [get_ports Dig_24_Ch4]
#Digital_25_Ch4 = B47_L4_P
set_property PACKAGE_PIN C14 [get_ports Dig_25_Ch4]
#Digital_26_Ch4 = B47_L12_P
set_property PACKAGE_PIN H14 [get_ports Dig_26_Ch4]
#Digital_27_Ch4 = B47_L4_N
set_property PACKAGE_PIN C13 [get_ports Dig_27_Ch4]
#Digital_28_Ch4 = B47_L12_N
set_property PACKAGE_PIN H13 [get_ports Dig_28_Ch4]
#Digital_29_Ch4 = B47_L1_P
set_property PACKAGE_PIN B15 [get_ports Dig_29_Ch4]
#Digital_30_Ch4 = B47_L11_P
set_property PACKAGE_PIN K14 [get_ports Dig_30_Ch4]

#######################################################################################################################################

##Set voltage level
##Set Pin in CMOS Mode for single-ended Signal

set_property IOSTANDARD LVCMOS18 [get_ports Dig_01_Ch4]
set_property IOSTANDARD LVCMOS18 [get_ports Dig_02_Ch4]
set_property IOSTANDARD LVCMOS18 [get_ports Dig_03_Ch4]
set_property IOSTANDARD LVCMOS18 [get_ports Dig_04_Ch4]
set_property IOSTANDARD LVCMOS18 [get_ports Dig_05_Ch4]
set_property IOSTANDARD LVCMOS18 [get_ports Dig_06_Ch4]
set_property IOSTANDARD LVCMOS18 [get_ports Dig_07_Ch4]
set_property IOSTANDARD LVCMOS18 [get_ports Dig_08_Ch4]
set_property IOSTANDARD LVCMOS18 [get_ports Dig_09_Ch4]
set_property IOSTANDARD LVCMOS18 [get_ports Dig_10_Ch4]
set_property IOSTANDARD LVCMOS18 [get_ports Dig_11_Ch4]
set_property IOSTANDARD LVCMOS18 [get_ports Dig_12_Ch4]
set_property IOSTANDARD LVCMOS18 [get_ports Dig_13_Ch4]
set_property IOSTANDARD LVCMOS18 [get_ports Dig_14_Ch4]
set_property IOSTANDARD LVCMOS18 [get_ports Dig_15_Ch4]
set_property IOSTANDARD LVCMOS18 [get_ports Dig_16_Ch4]
set_property IOSTANDARD LVCMOS18 [get_ports Dig_17_Ch4]
set_property IOSTANDARD LVCMOS18 [get_ports Dig_18_Ch4]
set_property IOSTANDARD LVCMOS18 [get_ports Dig_19_Ch4]
set_property IOSTANDARD LVCMOS18 [get_ports Dig_20_Ch4]
set_property IOSTANDARD LVCMOS18 [get_ports Dig_21_Ch4]
set_property IOSTANDARD LVCMOS18 [get_ports Dig_22_Ch4]
set_property IOSTANDARD LVCMOS18 [get_ports Dig_23_Ch4]
set_property IOSTANDARD LVCMOS18 [get_ports Dig_24_Ch4]
set_property IOSTANDARD LVCMOS18 [get_ports Dig_25_Ch4]
set_property IOSTANDARD LVCMOS18 [get_ports Dig_26_Ch4]
set_property IOSTANDARD LVCMOS18 [get_ports Dig_27_Ch4]
set_property IOSTANDARD LVCMOS18 [get_ports Dig_28_Ch4]
set_property IOSTANDARD LVCMOS18 [get_ports Dig_29_Ch4]
set_property IOSTANDARD LVCMOS18 [get_ports Dig_30_Ch4]