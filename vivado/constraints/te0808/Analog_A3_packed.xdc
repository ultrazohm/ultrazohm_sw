###Analog Adapter Board A3 for version 2v00 since there was a PIN swap
# Author: Eyke Ligemann
# Date: 19.08.2020
# All ADC-Pins are 1,8 Volt on Bank64 and Bank65
# Bank64 and Bank65 are High-Performance Banks (HP), only HP pins have the internal 100R termination resistors and support therefore LVDS

# differential FPGA pins with 1.8V signal level

## output clock pins

#Analog_01
#ANL_01_P_Ch3 = B65_L12_P
set_property PACKAGE_PIN AB8 [get_ports {A3_OUT_CLK[0]}]
set_property PACKAGE_PIN AC8 [get_ports {A3_OUT_CLK[1]}]
#ANL_01_N_Ch3 = B65_L12_N

#Analog_02
set_property PACKAGE_PIN AJ2 [get_ports {A3_OUT_CNV_0[0]}]
#ANL_02_P_Ch3 = B64_L21_P
set_property PACKAGE_PIN AK2 [get_ports {A3_OUT_CNV_1[0]}]
#ANL_02_N_Ch3 = B64_L21_N

###############################################

## input pins from ADC

#Analog_03
#ANL_03_P_Ch3 = B64_L15_P
set_property PACKAGE_PIN AK7 [get_ports {A3_IN[6]}]
set_property PACKAGE_PIN AK6 [get_ports {A3_IN[7]}]
#ANL_03_N_Ch3 = B64_L15_N

#Analog_04
#ANL_04_P_Ch3 = B65_L20_P
set_property PACKAGE_PIN AE3 [get_ports {A3_IN[14]}]
set_property PACKAGE_PIN AE2 [get_ports {A3_IN[15]}]
#ANL_04_N_Ch3 = B65_L20_N

#Analog_05
#ANL_05_P_Ch3 = B64_L19_P
set_property PACKAGE_PIN AK4 [get_ports {A3_IN[4]}]
set_property PACKAGE_PIN AK3 [get_ports {A3_IN[5]}]
#ANL_05_N_Ch3 = B64_L19_N

#Analog_06
#ANL_06_P_Ch3 = B65_L21_P
set_property PACKAGE_PIN AC2 [get_ports {A3_IN[12]}]
set_property PACKAGE_PIN AD2 [get_ports {A3_IN[13]}]
#ANL_06_N_Ch3 = B65_L21_N

#Analog_07
#ANL_07_P_Ch3 = B64_L23_P
set_property PACKAGE_PIN AF3 [get_ports {A3_IN[2]}]
set_property PACKAGE_PIN AG3 [get_ports {A3_IN[3]}]
#ANL_07_N_Ch3 = B64_L23_N

#Analog_08
#ANL_08_P_Ch3 = B64_L22_P
set_property PACKAGE_PIN AG1 [get_ports {A3_IN[10]}]
set_property PACKAGE_PIN AH1 [get_ports {A3_IN[11]}]
#ANL_08_N_Ch3 = B64_L22_N

#Analog_09
#ANL_09_P_Ch3 = B65_L17_P
set_property PACKAGE_PIN AD4 [get_ports {A3_IN[0]}]
set_property PACKAGE_PIN AE4 [get_ports {A3_IN[1]}]
#ANL_09_N_Ch3 = B65_L17_N

#Analog_10
#ANL_10_P_Ch3 = B65_L11_P
set_property PACKAGE_PIN AC7 [get_ports {A3_IN[8]}]
set_property PACKAGE_PIN AD7 [get_ports {A3_IN[9]}]
#ANL_10_N_Ch3 = B65_L11_N


############################################

## input standards
set_property IOSTANDARD LVDS [get_ports {A3_OUT_CLK[1]}]
set_property IOSTANDARD LVDS [get_ports {A3_OUT_CLK[0]}]
set_property IOSTANDARD LVCMOS18 [get_ports {A3_OUT_CNV_0[0]}]
set_property IOSTANDARD LVCMOS18 [get_ports {A3_OUT_CNV_1[0]}]
set_property IOSTANDARD LVDS [get_ports {A3_IN[15]}]
set_property IOSTANDARD LVDS [get_ports {A3_IN[14]}]
set_property IOSTANDARD LVDS [get_ports {A3_IN[13]}]
set_property IOSTANDARD LVDS [get_ports {A3_IN[12]}]
set_property IOSTANDARD LVDS [get_ports {A3_IN[11]}]
set_property IOSTANDARD LVDS [get_ports {A3_IN[10]}]
set_property IOSTANDARD LVDS [get_ports {A3_IN[9]}]
set_property IOSTANDARD LVDS [get_ports {A3_IN[8]}]
set_property IOSTANDARD LVDS [get_ports {A3_IN[7]}]
set_property IOSTANDARD LVDS [get_ports {A3_IN[6]}]
set_property IOSTANDARD LVDS [get_ports {A3_IN[5]}]
set_property IOSTANDARD LVDS [get_ports {A3_IN[4]}]
set_property IOSTANDARD LVDS [get_ports {A3_IN[3]}]
set_property IOSTANDARD LVDS [get_ports {A3_IN[2]}]
set_property IOSTANDARD LVDS [get_ports {A3_IN[1]}]
set_property IOSTANDARD LVDS [get_ports {A3_IN[0]}]
set_property DIFF_TERM_ADV TERM_100 [get_ports {A3_IN[15]}]
set_property DIFF_TERM_ADV TERM_100 [get_ports {A3_IN[14]}]
set_property DIFF_TERM_ADV TERM_100 [get_ports {A3_IN[13]}]
set_property DIFF_TERM_ADV TERM_100 [get_ports {A3_IN[12]}]
set_property DIFF_TERM_ADV TERM_100 [get_ports {A3_IN[11]}]
set_property DIFF_TERM_ADV TERM_100 [get_ports {A3_IN[10]}]
set_property DIFF_TERM_ADV TERM_100 [get_ports {A3_IN[9]}]
set_property DIFF_TERM_ADV TERM_100 [get_ports {A3_IN[8]}]
set_property DIFF_TERM_ADV TERM_100 [get_ports {A3_IN[7]}]
set_property DIFF_TERM_ADV TERM_100 [get_ports {A3_IN[6]}]
set_property DIFF_TERM_ADV TERM_100 [get_ports {A3_IN[5]}]
set_property DIFF_TERM_ADV TERM_100 [get_ports {A3_IN[4]}]
set_property DIFF_TERM_ADV TERM_100 [get_ports {A3_IN[3]}]
set_property DIFF_TERM_ADV TERM_100 [get_ports {A3_IN[2]}]
set_property DIFF_TERM_ADV TERM_100 [get_ports {A3_IN[1]}]
set_property DIFF_TERM_ADV TERM_100 [get_ports {A3_IN[0]}]

