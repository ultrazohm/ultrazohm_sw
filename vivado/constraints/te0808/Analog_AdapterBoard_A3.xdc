###Analog Adapter Board A3
# Author: Sebastian Wendel
# Date: 15.07.2019
# All ADC-Pins are 1,8 Volt on Bank64 and Bank65
# Bank64 and Bank65 are High-Performance Banks (HP), only HP pins have the internal 100R termination resistors and support therefore LVDS

# differential FPGA pins with 1.8V signal level

#Analog_10
#ANL_10_N_Ch3 = B64_L24_N
set_property PACKAGE_PIN AF1 [get_ports ANL_10_N_Ch3]
#ANL_10_P_Ch3 = B64_L24_P
set_property PACKAGE_PIN AF2 [get_ports ANL_10_P_Ch3]

#Analog_09
#ANL_09_P_Ch3 = B65_L17_P 
set_property PACKAGE_PIN AD4 [get_ports ANL_09_P_Ch3]
#ANL_09_N_Ch3 = B65_L17_N
set_property PACKAGE_PIN AE4 [get_ports ANL_09_N_Ch3]

#Analog_08
#ANL_08_P_Ch3 = B64_L22_P
set_property PACKAGE_PIN AG1 [get_ports ANL_08_P_Ch3]
#ANL_08_N_Ch3 = B64_L22_N
set_property PACKAGE_PIN AH1 [get_ports ANL_08_N_Ch3]

#Analog_07
#ANL_07_P_Ch3 = B64_L23_P
set_property PACKAGE_PIN AF3 [get_ports ANL_07_P_Ch3]
#ANL_07_N_Ch3 = B64_L23_N
set_property PACKAGE_PIN AG3 [get_ports ANL_07_N_Ch3]

#Analog_06
#ANL_06_N_Ch3 = B65_L21_N
set_property PACKAGE_PIN AD2 [get_ports ANL_06_N_Ch3]
#ANL_06_P_Ch3 = B65_L21_P
set_property PACKAGE_PIN AC2 [get_ports ANL_06_P_Ch3]

#Analog_05
#ANL_05_N_Ch3 = B64_L19_N
set_property PACKAGE_PIN AK3 [get_ports ANL_05_N_Ch3]
#ANL_05_P_Ch3 = B64_L19_P
set_property PACKAGE_PIN AK4 [get_ports ANL_05_P_Ch3]

#Analog_04
#ANL_04_P_Ch3 = B65_L20_P
set_property PACKAGE_PIN AE3 [get_ports ANL_04_P_Ch3]
#ANL_04_N_Ch3 = B65_L20_N
set_property PACKAGE_PIN AE2 [get_ports ANL_04_N_Ch3]

#Analog_03
#ANL_03_N_Ch3 = B64_L15_N
set_property PACKAGE_PIN AK6 [get_ports ANL_03_N_Ch3]
#ANL_03_P_Ch3 = B64_L15_P
set_property PACKAGE_PIN AK7 [get_ports ANL_03_P_Ch3]

#Analog_02
#ANL_02_N_Ch3 = B64_L21_N
set_property PACKAGE_PIN AK2 [get_ports ANL_02_N_Ch3]
#ANL_02_P_Ch3 = B64_L21_P
set_property PACKAGE_PIN AJ2 [get_ports ANL_02_P_Ch3]

#Analog_01
#ANL_01_N_Ch3 = B65_L19_N
set_property PACKAGE_PIN AC3 [get_ports ANL_01_N_Ch3]
#ANL_01_P_Ch3 = B65_L19_P
set_property PACKAGE_PIN AB3 [get_ports ANL_01_P_Ch3]


#######################################################################################################################################
#Set voltage level (IOSTANDARD LVDS_18 = IOSTANDARD LVDS at UltraScale)
#Set Pin in LVDS Mode for differential Signal

#Analog_10
set_property IOSTANDARD LVDS [get_ports ANL_10_P_Ch3]
#set_property IOSTANDARD LVDS [get_ports ANL_10_N_Ch3]
set_property DIFF_TERM TRUE  [get_ports ANL_10_P_Ch3]

#Analog_09
set_property IOSTANDARD LVDS [get_ports ANL_09_P_Ch3]
#set_property IOSTANDARD LVDS [get_ports ANL_09_N_Ch3]
set_property DIFF_TERM TRUE  [get_ports ANL_09_P_Ch3]

#Analog_08
set_property IOSTANDARD LVDS [get_ports ANL_08_P_Ch3]
#set_property IOSTANDARD LVDS [get_ports ANL_08_N_Ch3]
set_property DIFF_TERM TRUE  [get_ports ANL_08_P_Ch3]

#Analog_07
set_property IOSTANDARD LVDS [get_ports ANL_07_P_Ch3]
#set_property IOSTANDARD LVDS [get_ports ANL_07_N_Ch3]
set_property DIFF_TERM TRUE  [get_ports ANL_07_P_Ch3]

#Analog_06
set_property IOSTANDARD LVDS [get_ports ANL_06_P_Ch3]
#set_property IOSTANDARD LVDS [get_ports ANL_06_N_Ch3]
set_property DIFF_TERM TRUE  [get_ports ANL_06_P_Ch3]

#Analog_05
set_property IOSTANDARD LVDS [get_ports ANL_05_P_Ch3]
#set_property IOSTANDARD LVDS [get_ports ANL_05_N_Ch3]
set_property DIFF_TERM TRUE  [get_ports ANL_05_P_Ch3]

#Analog_04
set_property IOSTANDARD LVDS [get_ports ANL_04_P_Ch3]
#set_property IOSTANDARD LVDS [get_ports ANL_04_N_Ch3]
set_property DIFF_TERM TRUE  [get_ports ANL_04_P_Ch3]

#Analog_03
set_property IOSTANDARD LVDS [get_ports ANL_03_P_Ch3]
#set_property IOSTANDARD LVDS [get_ports ANL_03_N_Ch3
set_property DIFF_TERM TRUE  [get_ports ANL_03_P_Ch3]

#Analog_02
set_property IOSTANDARD LVDS [get_ports ANL_02_P_Ch3]
#set_property IOSTANDARD LVDS [get_ports ANL_02_N_Ch3]
#Pins L8 are the clock, therefore, no termination resistor!
#set_property DIFF_TERM TRUE  [get_ports ANL_02_P_Ch3]

#Analog_01
set_property IOSTANDARD LVDS [get_ports ANL_01_P_Ch3]
#set_property IOSTANDARD LVDS [get_ports ANL_01_N_Ch3]
#Pins L7 are the clock, therefore, no termination resistor!
#set_property DIFF_TERM TRUE  [get_ports ANL_01_P_Ch3]


