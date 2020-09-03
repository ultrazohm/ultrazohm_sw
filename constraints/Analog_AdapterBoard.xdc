###Overall and shared Analog Adapter Pins
# Author: Sebastian Wendel
# Date: 21.03.2019
# All ADC-Pins are 1,8 Volt on Bank64 and Bank66
# Bank64 and Bank66 are High-Performance Banks (HP), only HP pins have the internal 100R termination resistors and support therefore LVDS

# single-ended FPGA pins with 1.8V signal level

#SPI_CS (single-ended) = B64_T2
set_property PACKAGE_PIN AG4 [get_ports SPI_CS]
#ADC_ConvStart for LVDS = B64_T3
set_property PACKAGE_PIN AJ1 [get_ports ADC_ConvStart]
#SPI_MOSI (single-ended) = B64_T1
set_property PACKAGE_PIN AG9 [get_ports SPI_MOSI]
#SPI_SCK (single-ended) = B64_T0
set_property PACKAGE_PIN AH11 [get_ports SPI_SCK]


##Free/reserve = B66_L23_N
set_property PACKAGE_PIN L11 [get_ports Reserve]

##Collective_Fault = B66_L23_P
#set_property PACKAGE_PIN L12 [get_ports Collective_Fault]

##I2C_shared_SDA = B66_L22_N
#set_property PACKAGE_PIN M10 [get_ports I2C_shared_SDA]

##I2C_shared_SCL = B66_L22_P
#set_property PACKAGE_PIN N10 [get_ports I2C_shared_SCL]


########################################################################################################################################
##Set voltage level
##Set Pin in CMOS-Level
#SPI_CS (single-ended)
set_property IOSTANDARD LVCMOS18 [get_ports SPI_CS]
#ADC_ConvStart for LVDS
set_property IOSTANDARD LVCMOS18 [get_ports ADC_ConvStart]
#SPI_MOSI (single-ended)
set_property IOSTANDARD LVCMOS18 [get_ports SPI_MOSI]
#SPI_SCK (single-ended)
set_property IOSTANDARD LVCMOS18 [get_ports SPI_SCK]

##Free/reserve = B66_L23_N
set_property IOSTANDARD LVCMOS18 [get_ports Reserve]
##Collective_Fault = B66_L23_P
#set_property IOSTANDARD LVCMOS18 [get_ports Collective_Fault]
##I2C_shared_SDA = B66_L22_N
#set_property IOSTANDARD LVCMOS18 [get_ports I2C_shared_SDA]
##I2C_shared_SCL = B66_L22_P
#set_property IOSTANDARD LVCMOS18 [get_ports I2C_shared_SCL]


