###Analog Adapter Board A2 for version 2v00 since there was a PIN swap
# Author: Eyke Ligemann
# Date: 19.08.2020
# All ADC-Pins are 1,8 Volt on Bank64 and Bank65
# Bank64 and Bank65 are High-Performance Banks (HP), only HP pins have the internal 100R termination resistors and support therefore LVDS

# differential FPGA pins with 1.8V signal level

## output clock pins
#Analog_01
set_property PACKAGE_PIN AH7 [get_ports A2_OUT[0]]
#ANL_01_P_Ch2 = B64_L11_P
set_property PACKAGE_PIN AJ7 [get_ports A2_OUT[1]]
#ANL_01_N_Ch2 = B64_L11_N

#Analog_02
set_property PACKAGE_PIN AK9 [get_ports A2_OUT[2]]
#ANL_02_P_Ch2 = B64_L10_P
set_property PACKAGE_PIN AK8 [get_ports A2_OUT[3]]
#ANL_02_N_Ch2 = B64_L10_N 

####################################

## input pins from ADC
#Analog_03
set_property PACKAGE_PIN AF6 [get_ports A2_IN[0] ]
#ANL_03_P_Ch2 = B64_L16_P
set_property PACKAGE_PIN AF5 [get_ports A2_IN[1] ]
#ANL_03_N_Ch2 = B64_L16_N 

#Analog_04
set_property PACKAGE_PIN AJ10 [get_ports A2_IN[2] ]
#ANL_04_P_Ch2 = B64_L6_P
set_property PACKAGE_PIN AK10 [get_ports A2_IN[3] ]
#ANL_04_N_Ch2 = B64_L6_N 

#Analog_05
set_property PACKAGE_PIN AH3 [get_ports A2_IN[4] ]
#ANL_05_P_Ch2 = B64_L20_P
set_property PACKAGE_PIN AH2 [get_ports A2_IN[5] ]
#ANL_05_N_Ch2 = B64_L20_N

#Analog_06
set_property PACKAGE_PIN AG6 [get_ports A2_IN[6] ]
#ANL_06_P_Ch2 = B64_L13_P
set_property PACKAGE_PIN AG5 [get_ports A2_IN[7] ]
#ANL_06_N_Ch2 = B64_L13_N

#Analog_07
set_property PACKAGE_PIN AJ5 [get_ports A2_IN[8] ]
#ANL_07_P_Ch2 = B64_L17_P
set_property PACKAGE_PIN AK5 [get_ports A2_IN[9] ]
#ANL_07_N_Ch2 = B64_L17_N

#Analog_08
set_property PACKAGE_PIN AH4 [get_ports A2_IN[10] ]
#ANL_08_P_Ch2 = B64_L18_P
set_property PACKAGE_PIN AJ4 [get_ports A2_IN[11] ]
#ANL_08_N_Ch2 = B64_L18_N 

#Analog_09
set_property PACKAGE_PIN AB4 [get_ports A2_IN[12] ]
#ANL_09_P_Ch2 = B65_L18_P 
set_property PACKAGE_PIN AC4 [get_ports A2_IN[13] ]
#ANL_09_N_Ch2 = B65_L18_N

##Analog_10
set_property PACKAGE_PIN AH6 [get_ports A2_IN[14] ]
#ANL_10_P_Ch2 = B64_L14_P
set_property PACKAGE_PIN AJ6 [get_ports A2_IN[15] ]
#ANL_10_N_Ch2 = B64_L14_N

##################################

## input standards
set_property IOSTANDARD LVDS [get_ports A2_OUT]
set_property IOSTANDARD LVDS [get_ports A2_IN]
set_property DIFF_TERM_ADV = TERM_100 [get_ports A2_IN]
