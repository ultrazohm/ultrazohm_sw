###Digital Adapter Board D2
# Author: Sebastian Wendel
# Date: 21.03.2019
# 30 I/Os are available
# All Digital-Pins are 1,8 Volt on Bank65 and Bank66
# Bank65 and Bank66 are High-Performance Banks (HP). HP pins have the internal 100R termination resistors and support LVDS

# single-ended FPGA pins with 1.8V signal level
# zero-based numbering, starting from 00 to 29.

#Digital_01_Ch2 = B66_L8_N
set_property PACKAGE_PIN W4   [get_ports Dig_00_Ch2]
#Digital_02_Ch2 = B66_L18_N   
set_property PACKAGE_PIN U10  [get_ports Dig_01_Ch2]
#Digital_03_Ch2 = B66_L15_P                  
set_property PACKAGE_PIN U11  [get_ports Dig_02_Ch2]
#Digital_04_Ch2 = B66_L10_N                  
set_property PACKAGE_PIN U6   [get_ports Dig_03_Ch2]
#Digital_05_Ch2 = B66_L15_N                  
set_property PACKAGE_PIN V11  [get_ports Dig_04_Ch2]
#Digital_06_Ch2 = B66_L10_P                  
set_property PACKAGE_PIN U7   [get_ports Dig_05_Ch2]
#Digital_07_Ch2 = B66_L1_N                   
set_property PACKAGE_PIN Y3   [get_ports Dig_06_Ch2]
#Digital_08_Ch2 = B66_T3                     
set_property PACKAGE_PIN N11  [get_ports Dig_07_Ch2]
#Digital_09_Ch2 = B66_L1_P                   
set_property PACKAGE_PIN Y4   [get_ports Dig_08_Ch2]
#Digital_10_Ch2 = B66_T2                     
set_property PACKAGE_PIN Y10  [get_ports Dig_09_Ch2]
#Digital_11_Ch2 = B66_T1                     
set_property PACKAGE_PIN Y7   [get_ports Dig_10_Ch2]
#Digital_12_Ch2 = B66_L14_N                  
set_property PACKAGE_PIN Y8   [get_ports Dig_11_Ch2]
#Digital_13_Ch2 = B66_T0                     
set_property PACKAGE_PIN V3   [get_ports Dig_12_Ch2]
#Digital_14_Ch2 = B66_L14_P                  
set_property PACKAGE_PIN Y9   [get_ports Dig_13_Ch2]
#Digital_15_Ch2 = B65_T3                     
set_property PACKAGE_PIN AE1  [get_ports Dig_14_Ch2]
#Digital_16_Ch2 = B65_T2                     
set_property PACKAGE_PIN AE7  [get_ports Dig_15_Ch2]
#Digital_17_Ch2 = B65_T1                     
set_property PACKAGE_PIN AE8  [get_ports Dig_16_Ch2]
#Digital_18_Ch2 = B65_T0                     
set_property PACKAGE_PIN AC12 [get_ports Dig_17_Ch2]
#Digital_19_Ch2 = B65_L24_P                  
set_property PACKAGE_PIN AA1  [get_ports Dig_18_Ch2]
#Digital_20_Ch2 = B65_L24_N                  
set_property PACKAGE_PIN AB1  [get_ports Dig_19_Ch2]
#Digital_21_Ch2 = B65_L22_P                  
set_property PACKAGE_PIN AC1  [get_ports Dig_20_Ch2]
#Digital_22_Ch2 = B65_L22_N                  
set_property PACKAGE_PIN AD1  [get_ports Dig_21_Ch2]
#Digital_23_Ch2 = B65_L23_N                  
set_property PACKAGE_PIN AA2  [get_ports Dig_22_Ch2]
#Digital_24_Ch2 = B65_L23_P                  
set_property PACKAGE_PIN AA3  [get_ports Dig_23_Ch2]
#Digital_25_Ch2 = B66_L16_N                  
set_property PACKAGE_PIN W10  [get_ports Dig_24_Ch2]
#Digital_26_Ch2 = B66_L19_N                  
set_property PACKAGE_PIN T10  [get_ports Dig_25_Ch2]
#Digital_27_Ch2 = B66_L16_P                  
set_property PACKAGE_PIN W11  [get_ports Dig_26_Ch2]
#Digital_28_Ch2 = B66_L19_P                  
set_property PACKAGE_PIN R10  [get_ports Dig_27_Ch2]
#Digital_29_Ch2 = B66_L8_P                   
set_property PACKAGE_PIN V4   [get_ports Dig_28_Ch2]
#Digital_30_Ch2 = B66_L18_P                  
set_property PACKAGE_PIN T11  [get_ports Dig_29_Ch2]
                                             
#######################################################################################################################################

##Set voltage level
##All digital pins are 1.8V CMOS single-ended signals

set_property IOSTANDARD LVCMOS18 [get_ports Dig*]