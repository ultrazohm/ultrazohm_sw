### Digital Adapter Board D5
# Author: Andreas Geiger
# Date: 14.11.2025
# 
# 16 I/Os are available
# All Digital-Pins are 1.8 Volt on Bank47 and Bank66
# Bank47 are High-Density Banks (HD). HD pins have NOT the internal 100R termination resistors and support NO LVDS
# Bank66 are High-Performance Banks (HP).

# single-ended FPGA pins with 1.8V signal level
# zero-based numbering, starting from 00 to 29.

#Digital_23_Ch5 = B47_L8_N                  
set_property PACKAGE_PIN F13 [get_ports D5_23]
#Digital_22_Ch5 = B47_L6_N                  
set_property PACKAGE_PIN E13 [get_ports D5_22]
#Digital_21_Ch5 = B47_L8_P                  
set_property PACKAGE_PIN G13 [get_ports D5_21]
#Digital_20_Ch5 = B47_L6_P                  
set_property PACKAGE_PIN E14 [get_ports D5_20]
#Digital_19_Ch5 = B47_L10_N                 
set_property PACKAGE_PIN J15 [get_ports D5_19]
#Digital_18_Ch5 = B47_L3_N                  
set_property PACKAGE_PIN A13 [get_ports D5_18]
#Digital_17_Ch5 = B47_L10_P                 
set_property PACKAGE_PIN K15 [get_ports D5_17]
#Digital_16_Ch5 = B47_L3_P                  
set_property PACKAGE_PIN B13 [get_ports D5_16]
#Digital_15_Ch5 = B47_L9_N                  
set_property PACKAGE_PIN G14 [get_ports D5_15]
#Digital_14_Ch5 = B47_L2_N                  
set_property PACKAGE_PIN A14 [get_ports D5_14]
#Digital_13_Ch5 = B47_L9_P                  
set_property PACKAGE_PIN G15 [get_ports D5_13]
#Digital_12_Ch5 = B47_L2_P                  
set_property PACKAGE_PIN B14 [get_ports D5_12]
#Digital_11_Ch5 = B47_L7_N                  
set_property PACKAGE_PIN E15 [get_ports D5_11]
#Digital_10_Ch5 = B47_L5_N                  
set_property PACKAGE_PIN D14 [get_ports D5_10]
#Digital_09_Ch5 = B47_L7_P                  
set_property PACKAGE_PIN F15 [get_ports D5_09]
#Digital_08_Ch5 = B47_L5_P
set_property PACKAGE_PIN D15 [get_ports D5_08]
#Digital_07_Ch5 = B66_L22_N
set_property PACKAGE_PIN M10 [get_ports D5_07]
#Digital_06_Ch5 = B66_L22_P
set_property PACKAGE_PIN N10 [get_ports D5_06]
#######################################################################################################################################

##Set voltage level
##All digital pins are 1.8V CMOS single-ended signals

set_property IOSTANDARD LVCMOS18 [get_ports D5_*]


