# This file was auto-generated using the python script process_xdc.py
# The script has as input the original constraints. Pinout info is extracted from
# Trenz pinout sheet (obtained from https://shop.trenz-electronic.de/Download/?path=Trenz_Electronic/Pinout) 
# into csv files with the C-PIN, C-NAME, FPGA Pin Name, and Module Net Name columns.
# Obs.: Column order is not important, but names need to be strictly followed.
#
# Constraints ported from TE0808_REV02.csv to TE0803_REV01.csv.
#
# Script author: Tomas P. Correa
# Date: check GIT repo


# Port SPI_CS[0] = B64_T2 (J4:2)
set_property PACKAGE_PIN AB5 [get_ports SPI_CS[0]]
set_property IOSTANDARD LVCMOS18 [get_ports SPI_CS[0]]

# Port ADC_ConvStart[0] = B64_T3 (J4:4)
set_property PACKAGE_PIN AE4 [get_ports ADC_ConvStart[0]]
set_property IOSTANDARD LVCMOS18 [get_ports ADC_ConvStart[0]]

# Port SPI_MOSI[0] = B64_T1 (J4:6)
set_property PACKAGE_PIN AH6 [get_ports SPI_MOSI[0]]
set_property IOSTANDARD LVCMOS18 [get_ports SPI_MOSI[0]]

# Port SPI_SCK[0] = B64_T0 (J4:8)
set_property PACKAGE_PIN AD6 [get_ports SPI_SCK[0]]
set_property IOSTANDARD LVCMOS18 [get_ports SPI_SCK[0]]

# Port Reserve[0] = B66_L3_N (J1:110)
set_property PACKAGE_PIN E2 [get_ports Reserve[0]]
set_property IOSTANDARD LVCMOS18 [get_ports Reserve[0]]

