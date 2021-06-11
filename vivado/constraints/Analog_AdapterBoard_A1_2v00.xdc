###Analog Adapter Board A1 for version 2v00 since there was a PIN swap
# Author: Sebastian Wendel
# Date: 07.11.2019
# All ADC-Pins are 1,8 Volt on Bank64
# Bank64 are High-Performance Banks (HP), only HP pins have the internal 100R termination resistors and support therefore LVDS

# differential FPGA pins with 1.8V signal level

#Analog_10
#ANL_10_P_Ch1  = B65_L13_P
#ANL_10_N_Ch1 = B65_L13_N
set_property PACKAGE_PIN AB6 [get_ports ANL_10_P_Ch1]
set_property PACKAGE_PIN AB5 [get_ports ANL_10_N_Ch1]

#Analog_09
#ANL_09_N_Ch1 = B64_L9_N
#ANL_09_P_Ch1 = B64_L9_P
set_property PACKAGE_PIN AH9 [get_ports ANL_09_P_Ch1]
set_property PACKAGE_PIN AJ9 [get_ports ANL_09_N_Ch1]

#Analog_08
#ANL_08_P_Ch1 = B64_L4_P
#ANL_08_N_Ch1 = B64_L4_N
set_property PACKAGE_PIN AK13 [get_ports ANL_08_P_Ch1]
set_property PACKAGE_PIN AK12 [get_ports ANL_08_N_Ch1]

#Analog_07
#ANL_07_N_Ch1 = B64_L3_N
#ANL_07_P_Ch1 = B64_L3_P
set_property PACKAGE_PIN AH12 [get_ports ANL_07_P_Ch1]
set_property PACKAGE_PIN AJ12 [get_ports ANL_07_N_Ch1]

#Analog_06
#ANL_06_P_Ch1 = B64_L7_P
#ANL_06_N_Ch1 = B64_L7_N
set_property PACKAGE_PIN AF8 [get_ports ANL_06_P_Ch1]
set_property PACKAGE_PIN AF7 [get_ports ANL_06_N_Ch1]

#Analog_05
#ANL_05_P_Ch1 = B65_L16_P
#ANL_05_N_Ch1 = B65_L16_N
set_property PACKAGE_PIN AD5 [get_ports ANL_05_P_Ch1]
set_property PACKAGE_PIN AE5 [get_ports ANL_05_N_Ch1]

#Analog_04
#ANL_04_N_Ch1 = B64_L2_N
#ANL_04_P_Ch1 = B64_L2_P
set_property PACKAGE_PIN AG13 [get_ports ANL_04_P_Ch1]
set_property PACKAGE_PIN AH13 [get_ports ANL_04_N_Ch1]

#Analog_03
#ANL_03_N_Ch1 = B64_L1_N
#ANL_03_P_Ch1 = B64_L1_P
set_property PACKAGE_PIN AF11 [get_ports ANL_03_P_Ch1]
set_property PACKAGE_PIN AG11 [get_ports ANL_03_N_Ch1]

#Analog_02
#ANL_02_N_Ch1 = B64_L8_N
set_property PACKAGE_PIN AG10 [get_ports {ANL_02_N_Ch1[0]}]
#ANL_02_P_Ch1 = B64_L8_P
set_property PACKAGE_PIN AF10 [get_ports {ANL_02_P_Ch1[0]}]

#Analog_01
#ANL_01_N_Ch1 = B64_L12_N
#ANL_01_P_Ch1 = B64_L12_P
set_property PACKAGE_PIN AG8 [get_ports {ANL_01_P_Ch1[0]}]
set_property PACKAGE_PIN AH8 [get_ports {ANL_01_N_Ch1[0]}]



#######################################################################################################################################
#Set voltage level (IOSTANDARD LVDS_18 = IOSTANDARD LVDS at UltraScale)
#Set Pin in LVDS Mode for differential Signal

#Analog_10
set_property IOSTANDARD LVDS [get_ports ANL_10_P_Ch1]
set_property IOSTANDARD LVDS [get_ports ANL_10_N_Ch1]
set_property DIFF_TERM_ADV TERM_100 [get_ports ANL_10_P_Ch1]
set_property DIFF_TERM_ADV TERM_100 [get_ports ANL_10_N_Ch1]

#Analog_09
set_property IOSTANDARD LVDS [get_ports ANL_09_P_Ch1]
set_property IOSTANDARD LVDS [get_ports ANL_09_N_Ch1]
set_property DIFF_TERM_ADV TERM_100 [get_ports ANL_09_P_Ch1]
set_property DIFF_TERM_ADV TERM_100 [get_ports ANL_09_N_Ch1]

#Analog_08
set_property IOSTANDARD LVDS [get_ports ANL_08_P_Ch1]
set_property IOSTANDARD LVDS [get_ports ANL_08_N_Ch1]
set_property DIFF_TERM_ADV TERM_100 [get_ports ANL_08_P_Ch1]
set_property DIFF_TERM_ADV TERM_100 [get_ports ANL_08_N_Ch1]

#Analog_07
set_property IOSTANDARD LVDS [get_ports ANL_07_P_Ch1]
set_property IOSTANDARD LVDS [get_ports ANL_07_N_Ch1]
set_property DIFF_TERM_ADV TERM_100 [get_ports ANL_07_P_Ch1]
set_property DIFF_TERM_ADV TERM_100 [get_ports ANL_07_N_Ch1]

#Analog_06
set_property IOSTANDARD LVDS [get_ports ANL_06_P_Ch1]
set_property IOSTANDARD LVDS [get_ports ANL_06_N_Ch1]
set_property DIFF_TERM_ADV TERM_100 [get_ports ANL_06_P_Ch1]
set_property DIFF_TERM_ADV TERM_100 [get_ports ANL_06_N_Ch1]

#Analog_05
set_property IOSTANDARD LVDS [get_ports ANL_05_P_Ch1]
set_property IOSTANDARD LVDS [get_ports ANL_05_N_Ch1]
set_property DIFF_TERM_ADV TERM_100 [get_ports ANL_05_P_Ch1]
set_property DIFF_TERM_ADV TERM_100 [get_ports ANL_05_N_Ch1]

#Analog_04
set_property IOSTANDARD LVDS [get_ports ANL_04_P_Ch1]
set_property IOSTANDARD LVDS [get_ports ANL_04_N_Ch1]
set_property DIFF_TERM_ADV TERM_100 [get_ports ANL_04_P_Ch1]
set_property DIFF_TERM_ADV TERM_100 [get_ports ANL_04_N_Ch1]

#Analog_03
set_property IOSTANDARD LVDS [get_ports ANL_03_P_Ch1]
set_property IOSTANDARD LVDS [get_ports ANL_03_N_Ch1]
set_property DIFF_TERM_ADV TERM_100 [get_ports ANL_03_P_Ch1]
set_property DIFF_TERM_ADV TERM_100 [get_ports ANL_03_N_Ch1]

#Analog_02
set_property IOSTANDARD LVCMOS18 [get_ports {ANL_02_P_Ch1[0]}]
set_property IOSTANDARD LVCMOS18 [get_ports {ANL_02_N_Ch1[0]}]
#Pins L8 are the clock, therefore, no termination resistor!
#set_property DIFF_TERM TRUE  [get_ports ANL_02_P_Ch1]

#Analog_01
set_property IOSTANDARD LVDS [get_ports {ANL_01_P_Ch1[0]}]
set_property IOSTANDARD LVDS [get_ports {ANL_01_N_Ch1[0]}]
#Pins L7 are the clock, therefore, no termination resistor!
#set_property DIFF_TERM TRUE  [get_ports ANL_01_P_Ch1]




