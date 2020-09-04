###Digital Adapter Board D1 for version 2v00 since there was a PIN swap
# Author: Sebastian Wendel
# Date: 07.11.2019
# 30 I/Os are available
# All Digital-Pins are 1,8 Volt on Bank65
# Bank65 are High-Performance Banks (HP). HP pins have the internal 100R termination resistors and support LVDS

# single-ended FPGA pins with 1.8V signal level

#Digital_01_Ch1 = B65_L7_N
set_property PACKAGE_PIN AC9 [get_ports Dig_01_Ch1]
#Digital_02_Ch1 = B65_L7_P
set_property PACKAGE_PIN AB9 [get_ports Dig_02_Ch1]
#Digital_03_Ch1 = B65_L6_N
set_property PACKAGE_PIN AB10 [get_ports Dig_03_Ch1]
#Digital_04_Ch1 = B65_L6_P
set_property PACKAGE_PIN AB11 [get_ports Dig_04_Ch1]
#Digital_05_Ch1 = B64_L5_P
set_property PACKAGE_PIN AJ11 [get_ports Dig_05_Ch1]
#Digital_06_Ch1 = B64_L5_N
set_property PACKAGE_PIN AK11 [get_ports Dig_06_Ch1]
##Digital_07_Ch1 = B65_L10_N
#set_property PACKAGE_PIN AA7 [get_ports Dig_07_Ch1]
##Digital_08_Ch1 = B65_L10_P]
#set_property PACKAGE_PIN AA8 [get_ports Dig_08_Ch1]
##Digital_09_Ch1 = B65_L9_N
#set_property PACKAGE_PIN AE9 [get_ports Dig_09_Ch1]
##Digital_10_Ch1 = B65_L9_P
#set_property PACKAGE_PIN AD9 [get_ports Dig_10_Ch1]
##Digital_11_Ch1 = B65_L4_N
#set_property PACKAGE_PIN AD11 [get_ports Dig_11_Ch1]
##Digital_12_Ch1 = B65_L4_P
#set_property PACKAGE_PIN AC11 [get_ports Dig_12_Ch1]
##Digital_13_Ch1 = B65_L14_N
#set_property PACKAGE_PIN AD6 [get_ports Dig_13_Ch1]
##Digital_14_Ch1 = B65_L14_P
#set_property PACKAGE_PIN AC6 [get_ports Dig_14_Ch1]
##Digital_15_Ch1 = B65_L8_P
#set_property PACKAGE_PIN AD10 [get_ports Dig_15_Ch1]
##Digital_16_Ch1 = B65_L8_N
#set_property PACKAGE_PIN AE10 [get_ports Dig_16_Ch1]
##Digital_17_Ch1 = B65_L2_N
#set_property PACKAGE_PIN AF13 [get_ports Dig_17_Ch1]
##Digital_18_Ch1 = 65_L2_P
#set_property PACKAGE_PIN AE13 [get_ports Dig_18_Ch1]
##Digital_19_Ch1 = B65_L3_N
#set_property PACKAGE_PIN AE12 [get_ports Dig_19_Ch1]
#Digital_20_Ch1 = B65_L3_P
set_property PACKAGE_PIN AD12 [get_ports Dig_20_Ch1]
#Digital_21_Ch1 = B65_L1_P
set_property PACKAGE_PIN AB13 [get_ports Dig_21_Ch1]
#Digital_22_Ch1 = B65_L1_N
set_property PACKAGE_PIN AC13 [get_ports Dig_22_Ch1]
#Digital_23_Ch1 = B65_L5_P
set_property PACKAGE_PIN AA12 [get_ports Dig_23_Ch1]
#Digital_24_Ch1 = B65_L5_N
set_property PACKAGE_PIN AA11 [get_ports Dig_24_Ch1]
#Digital_25_Ch1 = B64_L24_N
set_property PACKAGE_PIN AF1 [get_ports Dig_25_Ch1]
#Digital_26_Ch1 = B64_L24_P
set_property PACKAGE_PIN AF2 [get_ports Dig_26_Ch1]
#Digital_27_Ch1 = B65_L19_N
set_property PACKAGE_PIN AC3 [get_ports Dig_27_Ch1]
#Digital_28_Ch1= B65_L19_P
set_property PACKAGE_PIN AB3 [get_ports Dig_28_Ch1]
#Digital_29_Ch1 = B65_L15_N
set_property PACKAGE_PIN AA5 [get_ports Dig_29_Ch1]
#Digital_30_Ch1 = B65_L15_P
set_property PACKAGE_PIN AA6 [get_ports Dig_30_Ch1]

#######################################################################################################################################

##Set voltage level
##Set Pin in CMOS Mode for single-ended Signal

set_property IOSTANDARD LVCMOS18 [get_ports Dig_01_Ch1]
set_property IOSTANDARD LVCMOS18 [get_ports Dig_02_Ch1]
set_property IOSTANDARD LVCMOS18 [get_ports Dig_03_Ch1]
set_property IOSTANDARD LVCMOS18 [get_ports Dig_04_Ch1]
set_property IOSTANDARD LVCMOS18 [get_ports Dig_05_Ch1]
set_property IOSTANDARD LVCMOS18 [get_ports Dig_06_Ch1]
#set_property IOSTANDARD LVCMOS18 [get_ports Dig_07_Ch1]
#set_property IOSTANDARD LVCMOS18 [get_ports Dig_08_Ch1]
#set_property IOSTANDARD LVCMOS18 [get_ports Dig_09_Ch1]
#set_property IOSTANDARD LVCMOS18 [get_ports Dig_10_Ch1]
#set_property IOSTANDARD LVCMOS18 [get_ports Dig_11_Ch1]
#set_property IOSTANDARD LVCMOS18 [get_ports Dig_12_Ch1]
#set_property IOSTANDARD LVCMOS18 [get_ports Dig_13_Ch1]
#set_property IOSTANDARD LVCMOS18 [get_ports Dig_14_Ch1]
#set_property IOSTANDARD LVCMOS18 [get_ports Dig_15_Ch1]
#set_property IOSTANDARD LVCMOS18 [get_ports Dig_16_Ch1]
#set_property IOSTANDARD LVCMOS18 [get_ports Dig_17_Ch1]
#set_property IOSTANDARD LVCMOS18 [get_ports Dig_18_Ch1]
#set_property IOSTANDARD LVCMOS18 [get_ports Dig_19_Ch1]
set_property IOSTANDARD LVCMOS18 [get_ports Dig_20_Ch1]
set_property IOSTANDARD LVCMOS18 [get_ports Dig_21_Ch1]
set_property IOSTANDARD LVCMOS18 [get_ports Dig_22_Ch1]
set_property IOSTANDARD LVCMOS18 [get_ports Dig_23_Ch1]
set_property IOSTANDARD LVCMOS18 [get_ports Dig_24_Ch1]
set_property IOSTANDARD LVCMOS18 [get_ports Dig_25_Ch1]
set_property IOSTANDARD LVCMOS18 [get_ports Dig_26_Ch1]
set_property IOSTANDARD LVCMOS18 [get_ports Dig_27_Ch1]
set_property IOSTANDARD LVCMOS18 [get_ports Dig_28_Ch1]
set_property IOSTANDARD LVCMOS18 [get_ports Dig_29_Ch1]
set_property IOSTANDARD LVCMOS18 [get_ports Dig_30_Ch1]