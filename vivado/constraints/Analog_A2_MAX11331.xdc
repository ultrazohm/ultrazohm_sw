# Analog MAX11331 Board A2 for carrierboard version 2v00
# Author: Thomas Kreppel
# Date: 21.02.2021
# All ADC-Pins are 1,8 Volt on Bank64 and Bank65
# Bank64 and Bank65 are High-Performance Banks (HP), only HP pins have the internal 100R termination resistors and support therefore LVDS

# single-ended FPGA pins with 1.8V signal level

###################################################
#MAX11331 Daughterboard 1: ANL_01-ANL_04
#Analog_01 - MISO1 1/3
#ANL_01_P_Ch2 = B64_L11_P
set_property PACKAGE_PIN AH7 [get_ports MISO_1[0]]
#ANL_01_N_Ch2 = B64_L11_N
set_property PACKAGE_PIN AJ7 [get_ports MISO_1[2]]

#Analog_02 - MISO1 2/4
#ANL_02_P_Ch2 = B64_L10_P
set_property PACKAGE_PIN AK9 [get_ports MISO_1[1]]
#ANL_02_N_Ch2 = B64_L10_N 
set_property PACKAGE_PIN AK8 [get_ports MISO_1[3]]

#Analog_03 - SCLK1, CS1
#ANL_03_P_Ch2 = B64_L16_P
set_property PACKAGE_PIN AF6 [get_ports SCLK_1]
#ANL_03_N_Ch2 = B64_L16_N 
set_property PACKAGE_PIN AF5 [get_ports CS_1]

#Analog_04 - MOSI1, SCKLRTN1
#ANL_04_P_Ch2 = B64_L6_P
set_property PACKAGE_PIN AJ10 [get_ports MOSI_1]
#ANL_04_N_Ch2 = B64_L6_N 
#set_property PACKAGE_PIN AK10 [get_ports SCLKRTN_1]

###################################################
#MAX11331 Daughterboard 2: ANL_05-ANL_08
#Analog_05 - MISO2 1/3
#ANL_05_P_Ch2 = B64_L20_P
set_property PACKAGE_PIN AH3 [get_ports MISO_2[0]]
#ANL_05_N_Ch2 = B64_L20_N
set_property PACKAGE_PIN AH2 [get_ports MISO_2[2]]

#Analog_06 - MISO2 2/4
#ANL_06_P_Ch2 = B64_L13_P
set_property PACKAGE_PIN AG6 [get_ports MISO_2[1]]
#ANL_06_N_Ch2 = B64_L13_N
set_property PACKAGE_PIN AG5 [get_ports MISO_2[3]]

#Analog_07 - SCLK2, CS2
#ANL_07_P_Ch2 = B64_L17_P
set_property PACKAGE_PIN AJ5 [get_ports SCLK_2]
#ANL_07_N_Ch2 = B64_L17_N
set_property PACKAGE_PIN AK5 [get_ports CS_2]

#Analog_08 - MOSI2, SCLKRTN2
#ANL_08_P_Ch2 = B64_L18_P
set_property PACKAGE_PIN AH4 [get_ports MOSI_2]
#ANL_08_N_Ch2 = B64_L18_N 
#set_property PACKAGE_PIN AJ4 [get_ports SCLKRTN_2]

###################################################
#MAX11331 Daughterboard 3: ANL_09-ANL_10, Shared SPI
#Analog_09 - MISO3 1/3
#ANL_09_P_Ch2 = B65_L18_P 
set_property PACKAGE_PIN AB4 [get_ports MISO_3[0]]
#ANL_09_N_Ch2 = B65_L18_N
set_property PACKAGE_PIN AC4 [get_ports MISO_3[2]]

##Analog_10 - MISO3 2/4NL_10_P_Ch2 = B64_L14_P
set_property PACKAGE_PIN AH6 [get_ports MISO_3[1]]
#ANL_10_N_Ch2 = B64_L14_N
set_property PACKAGE_PIN AJ6 [get_ports MISO_3[3]]

#Shared SPI across all slots
#SPI_SCK (single-ended) = B64_T0
set_property PACKAGE_PIN AH11 [get_ports SCLK_3]
#SPI_CS (single-ended) = B64_T2
set_property PACKAGE_PIN AG4 [get_ports CS_3]
#SPI_MOSI (single-ended) = B64_T1
set_property PACKAGE_PIN AG9 [get_ports MOSI_3]
##Free/reserve = B66_L23_N
#set_property PACKAGE_PIN L11 [get_ports SCLKRTN_3]

#######################################################################################################################################
#Set voltage level (IOSTANDARD LVCMOS18 = IOSTANDARD 1.8V single ended at UltraScale)

#SPI Master In Slave Out
set_property IOSTANDARD LVCMOS18 [get_ports MISO_*]
#SPI SClock
set_property IOSTANDARD LVCMOS18 [get_ports SCLK_*]
#SPI Chip Select
set_property IOSTANDARD LVCMOS18 [get_ports CS_*]
#SPI Master Out Slave In
set_property IOSTANDARD LVCMOS18 [get_ports MOSI_*]
#SPI SCLK return
#set_property IOSTANDARD LVCMOS18 [get_ports SCLKRTN_*]