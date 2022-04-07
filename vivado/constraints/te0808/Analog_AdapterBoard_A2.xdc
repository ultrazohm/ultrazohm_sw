###Analog Adapter Board A2 for version 2v00 since there was a PIN swap
# Author: Sebastian Wendel
# Date: 07.11.2019
# All ADC-Pins are 1,8 Volt on Bank64 and Bank65
# Bank64 and Bank65 are High-Performance Banks (HP), only HP pins have the internal 100R termination resistors and support therefore LVDS

# differential FPGA pins with 1.8V signal level

##Analog_10
#ANL_10_N_Ch2 = B64_L14_N
set_property PACKAGE_PIN AJ6 [get_ports ANL_10_N_Ch2]
#ANL_10_P_Ch2 = B64_L14_P
set_property PACKAGE_PIN AH6 [get_ports ANL_10_P_Ch2]

#Analog_09
#ANL_09_P_Ch2 = B65_L18_P 
set_property PACKAGE_PIN AB4 [get_ports ANL_09_P_Ch2]
#ANL_09_N_Ch2 = B65_L18_N
set_property PACKAGE_PIN AC4 [get_ports ANL_09_N_Ch2]

#Analog_08
#ANL_08_P_Ch2 = B64_L18_P
set_property PACKAGE_PIN AH4 [get_ports ANL_08_P_Ch2]
#ANL_08_N_Ch2 = B64_L18_N 
set_property PACKAGE_PIN AJ4 [get_ports ANL_08_N_Ch2]

#Analog_07
#ANL_07_P_Ch2 = B64_L17_P
set_property PACKAGE_PIN AJ5 [get_ports ANL_07_P_Ch2]
#ANL_07_N_Ch2 = B64_L17_N
set_property PACKAGE_PIN AK5 [get_ports ANL_07_N_Ch2]

#Analog_06
#ANL_06_N_Ch2 = B64_L13_N
set_property PACKAGE_PIN AG5 [get_ports ANL_06_N_Ch2]
#ANL_06_P_Ch2 = B64_L13_P
set_property PACKAGE_PIN AG6 [get_ports ANL_06_P_Ch2]

#Analog_05
#ANL_05_N_Ch2 = B64_L20_N
set_property PACKAGE_PIN AH2 [get_ports ANL_05_N_Ch2]
#ANL_05_P_Ch2 = B64_L20_P
set_property PACKAGE_PIN AH3 [get_ports ANL_05_P_Ch2]

#Analog_04
#ANL_04_N_Ch2 = B64_L6_N 
set_property PACKAGE_PIN AK10 [get_ports ANL_04_N_Ch2]
#ANL_04_P_Ch2 = B64_L6_P
set_property PACKAGE_PIN AJ10 [get_ports ANL_04_P_Ch2]

#Analog_03
#ANL_03_N_Ch2 = B64_L16_N 
set_property PACKAGE_PIN AF5 [get_ports ANL_03_N_Ch2]
#ANL_03_P_Ch2 = B64_L16_P
set_property PACKAGE_PIN AF6 [get_ports ANL_03_P_Ch2]

#Analog_02
#ANL_02_N_Ch2 = B64_L10_N 
set_property PACKAGE_PIN AK8 [get_ports ANL_02_N_Ch2]
#ANL_02_P_Ch2 = B64_L10_P
set_property PACKAGE_PIN AK9 [get_ports ANL_02_P_Ch2]

#Analog_01
#ANL_01_P_Ch2 = B64_L11_P
set_property PACKAGE_PIN AH7 [get_ports ANL_01_P_Ch2]
#ANL_01_N_Ch2 = B64_L11_N
set_property PACKAGE_PIN AJ7 [get_ports ANL_01_N_Ch2]



#######################################################################################################################################
#Set voltage level (IOSTANDARD LVDS_18 = IOSTANDARD LVDS at UltraScale)
#Set Pin in LVDS Mode for differential Signal

#Analog_10
set_property IOSTANDARD LVDS [get_ports ANL_10_P_Ch2]
#set_property IOSTANDARD LVDS [get_ports ANL_10_N_Ch2]
set_property DIFF_TERM TRUE  [get_ports ANL_10_P_Ch2]

#Analog_09
set_property IOSTANDARD LVDS [get_ports ANL_09_P_Ch2]
#set_property IOSTANDARD LVDS [get_ports ANL_09_N_Ch2]
set_property DIFF_TERM TRUE  [get_ports ANL_09_P_Ch2]

#Analog_08
set_property IOSTANDARD LVDS [get_ports ANL_08_P_Ch2]
#set_property IOSTANDARD LVDS [get_ports ANL_08_N_Ch2]
set_property DIFF_TERM TRUE  [get_ports ANL_08_P_Ch2]

#Analog_07
set_property IOSTANDARD LVDS [get_ports ANL_07_P_Ch2]
#set_property IOSTANDARD LVDS [get_ports ANL_07_N_Ch2]
set_property DIFF_TERM TRUE  [get_ports ANL_07_P_Ch2]

#Analog_06
set_property IOSTANDARD LVDS [get_ports ANL_06_P_Ch2]
#set_property IOSTANDARD LVDS [get_ports ANL_06_N_Ch2]
set_property DIFF_TERM TRUE  [get_ports ANL_06_P_Ch2]

#Analog_05
set_property IOSTANDARD LVDS [get_ports ANL_05_P_Ch2]
#set_property IOSTANDARD LVDS [get_ports ANL_05_N_Ch2]
set_property DIFF_TERM TRUE  [get_ports ANL_05_P_Ch2]

#Analog_04
set_property IOSTANDARD LVDS [get_ports ANL_04_P_Ch2]
#set_property IOSTANDARD LVDS [get_ports ANL_04_N_Ch2]
set_property DIFF_TERM TRUE  [get_ports ANL_04_P_Ch2]

#Analog_03
set_property IOSTANDARD LVDS [get_ports ANL_03_P_Ch2]
#set_property IOSTANDARD LVDS [get_ports ANL_03_N_Ch2
set_property DIFF_TERM TRUE  [get_ports ANL_03_P_Ch2]

#Analog_02
set_property IOSTANDARD LVDS [get_ports ANL_02_P_Ch2]
#set_property IOSTANDARD LVDS [get_ports ANL_02_N_Ch2]
#Pins L8 are the clock, therefore, no termination resistor!
#set_property DIFF_TERM TRUE  [get_ports ANL_02_P_Ch2]

#Analog_01
set_property IOSTANDARD LVDS [get_ports ANL_01_P_Ch2]
#set_property IOSTANDARD LVDS [get_ports ANL_01_N_Ch2]
#Pins L7 are the clock, therefore, no termination resistor!
#set_property DIFF_TERM TRUE  [get_ports ANL_01_P_Ch2]


