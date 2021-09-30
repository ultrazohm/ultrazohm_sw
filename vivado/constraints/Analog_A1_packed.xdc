###Analog Adapter Board A1 for version 2v00 since there was a PIN swap
# Author: Eyke Ligemann
# Date: 19.08.2020
# All ADC-Pins are 1,8 Volt on Bank64 and Bank65
# Bank64 and Bank65 are High-Performance Banks (HP), only HP pins have the internal 100R termination resistors and support therefore LVDS

# differential FPGA pins with 1.8V signal level

## output clock pins

#Analog_01
#ANL_01_P_Ch1 = B64_L12_P
set_property PACKAGE_PIN AG8 [get_ports {A1_OUT_0[0]}]
set_property PACKAGE_PIN AH8 [get_ports {A1_OUT_1[0]}]
#ANL_01_N_Ch1 = B64_L12_N

#Analog_02
set_property PACKAGE_PIN AF10 [get_ports 	 A1_OUT_2]
#ANL_02_P_Ch1 = B64_L8_P
set_property PACKAGE_PIN AG10 [get_ports 	 A1_OUT_3]
#ANL_02_N_Ch1 = B64_L8_N

####################################

## input pins from ADC

#Analog_03
#ANL_03_P_Ch1 = B64_L1_P
set_property PACKAGE_PIN AF11 [get_ports {A1_IN[6]}]
set_property PACKAGE_PIN AG11 [get_ports {A1_IN[7]}]
#ANL_03_N_Ch1 = B64_L1_N

#Analog_04
#ANL_04_P_Ch1 = B64_L2_P
set_property PACKAGE_PIN AG13 [get_ports {A1_IN[14]}]
set_property PACKAGE_PIN AH13 [get_ports {A1_IN[15]}]
#ANL_04_N_Ch1 = B64_L2_N

#Analog_05
#ANL_05_P_Ch1 = B65_L16_P
set_property PACKAGE_PIN AD5 [get_ports {A1_IN[4]}]
set_property PACKAGE_PIN AE5 [get_ports {A1_IN[5]}]
#ANL_05_N_Ch1 = B65_L16_N

#Analog_06
#ANL_06_P_Ch1 = B64_L7_P
set_property PACKAGE_PIN AF8 [get_ports {A1_IN[12]}]
set_property PACKAGE_PIN AF7 [get_ports {A1_IN[13]}]
#ANL_06_N_Ch1 = B64_L7_N

#Analog_07
#ANL_07_P_Ch1 = B64_L3_P
set_property PACKAGE_PIN AH12 [get_ports {A1_IN[2]}]
set_property PACKAGE_PIN AJ12 [get_ports {A1_IN[3]}]
#ANL_07_N_Ch1 = B64_L3_N

#Analog_08
#ANL_08_P_Ch1 = B64_L4_P
set_property PACKAGE_PIN AK13 [get_ports {A1_IN[10]}]
set_property PACKAGE_PIN AK12 [get_ports {A1_IN[11]}]
#ANL_08_N_Ch1 = B64_L4_N

#Analog_09
#ANL_09_P_Ch1 = B64_L9_P
set_property PACKAGE_PIN AH9 [get_ports {A1_IN[0]}]
set_property PACKAGE_PIN AJ9 [get_ports {A1_IN[1]}]
#ANL_09_N_Ch1 = B64_L9_N

#Analog_10
#ANL_10_P_Ch1  = B65_L13_P
set_property PACKAGE_PIN AB6 [get_ports {A1_IN[8]}]
set_property PACKAGE_PIN AB5 [get_ports {A1_IN[9]}]
#ANL_10_N_Ch1 = B65_L13_N

#####################################

## input standards
set_property IOSTANDARD LVDS [get_ports {A1_OUT_0[0]}]
set_property IOSTANDARD LVDS [get_ports {A1_OUT_1[0]}]
#set_property IOSTANDARD LVCMOS18 [get_ports A1_OUT2]
set_property IOSTANDARD LVDS [get_ports {A1_IN[15]}]
set_property IOSTANDARD LVDS [get_ports {A1_IN[14]}]
set_property IOSTANDARD LVDS [get_ports {A1_IN[13]}]
set_property IOSTANDARD LVDS [get_ports {A1_IN[12]}]
set_property IOSTANDARD LVDS [get_ports {A1_IN[11]}]
set_property IOSTANDARD LVDS [get_ports {A1_IN[10]}]
set_property IOSTANDARD LVDS [get_ports {A1_IN[9]}]
set_property IOSTANDARD LVDS [get_ports {A1_IN[8]}]
set_property IOSTANDARD LVDS [get_ports {A1_IN[7]}]
set_property IOSTANDARD LVDS [get_ports {A1_IN[6]}]
set_property IOSTANDARD LVDS [get_ports {A1_IN[5]}]
set_property IOSTANDARD LVDS [get_ports {A1_IN[4]}]
set_property IOSTANDARD LVDS [get_ports {A1_IN[3]}]
set_property IOSTANDARD LVDS [get_ports {A1_IN[2]}]
set_property IOSTANDARD LVDS [get_ports {A1_IN[1]}]
set_property IOSTANDARD LVDS [get_ports {A1_IN[0]}]
set_property DIFF_TERM_ADV TERM_100 [get_ports {A1_IN[15]}]
set_property DIFF_TERM_ADV TERM_100 [get_ports {A1_IN[14]}]
set_property DIFF_TERM_ADV TERM_100 [get_ports {A1_IN[13]}]
set_property DIFF_TERM_ADV TERM_100 [get_ports {A1_IN[12]}]
set_property DIFF_TERM_ADV TERM_100 [get_ports {A1_IN[11]}]
set_property DIFF_TERM_ADV TERM_100 [get_ports {A1_IN[10]}]
set_property DIFF_TERM_ADV TERM_100 [get_ports {A1_IN[9]}]
set_property DIFF_TERM_ADV TERM_100 [get_ports {A1_IN[8]}]
set_property DIFF_TERM_ADV TERM_100 [get_ports {A1_IN[7]}]
set_property DIFF_TERM_ADV TERM_100 [get_ports {A1_IN[6]}]
set_property DIFF_TERM_ADV TERM_100 [get_ports {A1_IN[5]}]
set_property DIFF_TERM_ADV TERM_100 [get_ports {A1_IN[4]}]
set_property DIFF_TERM_ADV TERM_100 [get_ports {A1_IN[3]}]
set_property DIFF_TERM_ADV TERM_100 [get_ports {A1_IN[2]}]
set_property DIFF_TERM_ADV TERM_100 [get_ports {A1_IN[1]}]
set_property DIFF_TERM_ADV TERM_100 [get_ports {A1_IN[0]}]

