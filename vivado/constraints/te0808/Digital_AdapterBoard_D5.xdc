###Digital Adapter Board D5
# Author: Sebastian Wendel
# Date: 21.03.2019
# Updated: 10.02.2022, Eyke Liegmann
# Updated: 02.11.2022, Michael Hoerner
# 16 I/Os are available
# All Digital-Pins are 1,8 Volt on Bank47 and Bank66
# Bank47 are High-Density Banks (HD). HD pins have NOT the internal 100R termination resistors and support NO LVDS
# Bank66 are High-Performance Banks (HP).

# single-ended FPGA pins with 1.8V signal level
# zero-based numbering, starting from 00 to 29.

### The 15 "non-encoder" (cf. below) D5-I/Os are grouped into a vector to be used as "merged output" to verify the inputs from D4
#Digital_23_Ch5 = B47_L8_N                  
set_property PACKAGE_PIN F13 [get_ports D5_15OUT[14]]
#Digital_22_Ch5 = B47_L6_N                  
set_property PACKAGE_PIN E13 [get_ports D5_15OUT[13]]
#Digital_21_Ch5 = B47_L8_P                  
set_property PACKAGE_PIN G13 [get_ports D5_15OUT[12]]
#Digital_20_Ch5 = B47_L6_P                  
set_property PACKAGE_PIN E14 [get_ports D5_15OUT[11]]
#Digital_19_Ch5 = B47_L10_N                 
set_property PACKAGE_PIN J15 [get_ports D5_15OUT[10]]
#Digital_18_Ch5 = B47_L3_N                  
set_property PACKAGE_PIN A13 [get_ports D5_15OUT[9]]
#Digital_17_Ch5 = B47_L10_P                 
set_property PACKAGE_PIN K15 [get_ports D5_15OUT[8]]
#Digital_16_Ch5 = B47_L3_P                  
set_property PACKAGE_PIN B13 [get_ports D5_15OUT[7]]
#Digital_15_Ch5 = B47_L9_N                  
set_property PACKAGE_PIN G14 [get_ports D5_15OUT[6]]
#Digital_14_Ch5 = B47_L2_N                  
set_property PACKAGE_PIN A14 [get_ports D5_15OUT[5]]


### D5-I/O 13 to 11 used for incremental encoder...
#Digital_13_Ch5 = B47_L9_P                  
set_property PACKAGE_PIN G15 [get_ports Dig_13_Ch5]
#Digital_12_Ch5 = B47_L2_P                  
set_property PACKAGE_PIN B14 [get_ports Dig_12_Ch5]
#Digital_11_Ch5 = B47_L7_N                  
set_property PACKAGE_PIN E15 [get_ports Dig_11_Ch5]
### End of encoder


### Cont'd from above
#Digital_10_Ch5 = B47_L5_N                  
set_property PACKAGE_PIN D14 [get_ports D5_15OUT[4]]
#Digital_09_Ch5 = B47_L7_P                  
set_property PACKAGE_PIN F15 [get_ports D5_15OUT[3]]
#Digital_08_Ch5 = B47_L5_P
set_property PACKAGE_PIN D15 [get_ports D5_15OUT[2]]
#Digital_07_Ch5 = B66_L22_N
set_property PACKAGE_PIN M10 [get_ports D5_15OUT[1]]
#Digital_06_Ch5 = B66_L22_P
set_property PACKAGE_PIN N10 [get_ports D5_15OUT[0]]
#######################################################################################################################################

##Set voltage level
##All digital pins are 1.8V CMOS single-ended signals

set_property IOSTANDARD LVCMOS18 [get_ports Dig*]
set_property IOSTANDARD LVCMOS18 [get_ports D5_15OUT*]


