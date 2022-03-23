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


# Port A3_OUT_CLK[0] = B65_L12_P (J4:67)
set_property PACKAGE_PIN L3 [get_ports A3_OUT_CLK[0]]
set_property IOSTANDARD LVDS [get_ports A3_OUT_CLK[0]]

# Port A3_OUT_CLK[1] = B65_L12_N (J4:65)
set_property PACKAGE_PIN L2 [get_ports A3_OUT_CLK[1]]
set_property IOSTANDARD LVDS [get_ports A3_OUT_CLK[1]]

# Port A3_OUT_CNV_0[0] = B64_L22_P (J4:42)
set_property PACKAGE_PIN AE2 [get_ports A3_OUT_CNV_0[0]]
set_property IOSTANDARD LVCMOS18 [get_ports A3_OUT_CNV_0[0]]

# Port A3_OUT_CNV_1[0] = B64_L22_N (J4:44)
set_property PACKAGE_PIN AF2 [get_ports A3_OUT_CNV_1[0]]
set_property IOSTANDARD LVCMOS18 [get_ports A3_OUT_CNV_1[0]]

# Port A3_IN[7] = B64_L16_N (J4:36)
set_property PACKAGE_PIN AD1 [get_ports A3_IN[7]]
set_property DIFF_TERM_ADV TERM_100 [get_ports A3_IN[7]]
set_property IOSTANDARD LVDS [get_ports A3_IN[7]]
# WARNING: Differential signals are inverted in respect to TE0808 9EG device. 
# Take care to invert the signal inside the PL! 

# Port A3_IN[6] = B64_L16_P (J4:38)
set_property PACKAGE_PIN AD2 [get_ports A3_IN[6]]
set_property DIFF_TERM_ADV TERM_100 [get_ports A3_IN[6]]
set_property IOSTANDARD LVDS [get_ports A3_IN[6]]
# WARNING: Differential signals are inverted in respect to TE0808 9EG device. 
# Take care to invert the signal inside the PL! 

# Port A3_IN[14] = B65_L15_P (J4:37)
set_property PACKAGE_PIN N7 [get_ports A3_IN[14]]
set_property DIFF_TERM_ADV TERM_100 [get_ports A3_IN[14]]
set_property IOSTANDARD LVDS [get_ports A3_IN[14]]

# Port A3_IN[15] = B65_L15_N (J4:35)
set_property PACKAGE_PIN N6 [get_ports A3_IN[15]]
set_property DIFF_TERM_ADV TERM_100 [get_ports A3_IN[15]]
set_property IOSTANDARD LVDS [get_ports A3_IN[15]]

# Port A3_IN[5] = B64_L6_N (J4:32)
set_property PACKAGE_PIN AC6 [get_ports A3_IN[5]]
set_property DIFF_TERM_ADV TERM_100 [get_ports A3_IN[5]]
set_property IOSTANDARD LVDS [get_ports A3_IN[5]]
# WARNING: Differential signals are inverted in respect to TE0808 9EG device. 
# Take care to invert the signal inside the PL! 

# Port A3_IN[4] = B64_L6_P (J4:30)
set_property PACKAGE_PIN AB6 [get_ports A3_IN[4]]
set_property DIFF_TERM_ADV TERM_100 [get_ports A3_IN[4]]
set_property IOSTANDARD LVDS [get_ports A3_IN[4]]
# WARNING: Differential signals are inverted in respect to TE0808 9EG device. 
# Take care to invert the signal inside the PL! 

# Port A3_IN[12] = B65_L19_P (J4:29)
set_property PACKAGE_PIN J5 [get_ports A3_IN[12]]
set_property DIFF_TERM_ADV TERM_100 [get_ports A3_IN[12]]
set_property IOSTANDARD LVDS [get_ports A3_IN[12]]

# Port A3_IN[13] = B65_L19_N (J4:31)
set_property PACKAGE_PIN J4 [get_ports A3_IN[13]]
set_property DIFF_TERM_ADV TERM_100 [get_ports A3_IN[13]]
set_property IOSTANDARD LVDS [get_ports A3_IN[13]]

# Port A3_IN[2] = B64_L18_P (J4:24)
set_property PACKAGE_PIN AB1 [get_ports A3_IN[2]]
set_property DIFF_TERM_ADV TERM_100 [get_ports A3_IN[2]]
set_property IOSTANDARD LVDS [get_ports A3_IN[2]]

# Port A3_IN[3] = B64_L18_N (J4:26)
set_property PACKAGE_PIN AC1 [get_ports A3_IN[3]]
set_property DIFF_TERM_ADV TERM_100 [get_ports A3_IN[3]]
set_property IOSTANDARD LVDS [get_ports A3_IN[3]]

# Port A3_IN[10] = B64_L17_P (J4:18)
set_property PACKAGE_PIN AB2 [get_ports A3_IN[10]]
set_property DIFF_TERM_ADV TERM_100 [get_ports A3_IN[10]]
set_property IOSTANDARD LVDS [get_ports A3_IN[10]]

# Port A3_IN[11] = B64_L17_N (J4:20)
set_property PACKAGE_PIN AC2 [get_ports A3_IN[11]]
set_property DIFF_TERM_ADV TERM_100 [get_ports A3_IN[11]]
set_property IOSTANDARD LVDS [get_ports A3_IN[11]]

# Port A3_IN[1] = B65_L20_N (J4:19)
set_property PACKAGE_PIN H6 [get_ports A3_IN[1]]
set_property DIFF_TERM_ADV TERM_100 [get_ports A3_IN[1]]
set_property IOSTANDARD LVDS [get_ports A3_IN[1]]
# WARNING: Differential signals are inverted in respect to TE0808 9EG device. 
# Take care to invert the signal inside the PL! 

# Port A3_IN[0] = B65_L20_P (J4:17)
set_property PACKAGE_PIN J6 [get_ports A3_IN[0]]
set_property DIFF_TERM_ADV TERM_100 [get_ports A3_IN[0]]
set_property IOSTANDARD LVDS [get_ports A3_IN[0]]
# WARNING: Differential signals are inverted in respect to TE0808 9EG device. 
# Take care to invert the signal inside the PL! 

# Port A3_IN[8] = B65_L11_P (J4:79)
set_property PACKAGE_PIN K4 [get_ports A3_IN[8]]
set_property DIFF_TERM_ADV TERM_100 [get_ports A3_IN[8]]
set_property IOSTANDARD LVDS [get_ports A3_IN[8]]

# Port A3_IN[9] = B65_L11_N (J4:77)
set_property PACKAGE_PIN K3 [get_ports A3_IN[9]]
set_property DIFF_TERM_ADV TERM_100 [get_ports A3_IN[9]]
set_property IOSTANDARD LVDS [get_ports A3_IN[9]]

