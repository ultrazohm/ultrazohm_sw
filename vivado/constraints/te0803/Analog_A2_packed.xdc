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


# Port A2_OUT_CLK[0] = B64_L12_P (J4:78)
set_property PACKAGE_PIN AE5 [get_ports A2_OUT_CLK[0]]
set_property IOSTANDARD LVDS [get_ports A2_OUT_CLK[0]]

# Port A2_OUT_CLK[1] = B64_L12_N (J4:80)
set_property PACKAGE_PIN AF5 [get_ports A2_OUT_CLK[1]]
set_property IOSTANDARD LVDS [get_ports A2_OUT_CLK[1]]

# Port A2_OUT_CNV_0[0] = B64_L19_P (J4:92)
set_property PACKAGE_PIN AG4 [get_ports A2_OUT_CNV_0[0]]
set_property IOSTANDARD LVCMOS18 [get_ports A2_OUT_CNV_0[0]]

# Port A2_OUT_CNV_1[0] = B64_L19_N (J4:90)
set_property PACKAGE_PIN AH4 [get_ports A2_OUT_CNV_1[0]]
set_property IOSTANDARD LVCMOS18 [get_ports A2_OUT_CNV_1[0]]

# Port A2_IN[6] = B64_L20_P (J4:86)
set_property PACKAGE_PIN AG3 [get_ports A2_IN[6]]
set_property DIFF_TERM_ADV TERM_100 [get_ports A2_IN[6]]
set_property IOSTANDARD LVDS [get_ports A2_IN[6]]

# Port A2_IN[7] = B64_L20_N (J4:84)
set_property PACKAGE_PIN AH3 [get_ports A2_IN[7]]
set_property DIFF_TERM_ADV TERM_100 [get_ports A2_IN[7]]
set_property IOSTANDARD LVDS [get_ports A2_IN[7]]

# Port A2_IN[14] = B64_L10_P (J4:98)
set_property PACKAGE_PIN AG6 [get_ports A2_IN[14]]
set_property DIFF_TERM_ADV TERM_100 [get_ports A2_IN[14]]
set_property IOSTANDARD LVDS [get_ports A2_IN[14]]

# Port A2_IN[15] = B64_L10_N (J4:96)
set_property PACKAGE_PIN AG5 [get_ports A2_IN[15]]
set_property DIFF_TERM_ADV TERM_100 [get_ports A2_IN[15]]
set_property IOSTANDARD LVDS [get_ports A2_IN[15]]

# Port A2_IN[5] = B64_L24_N (J4:50)
set_property PACKAGE_PIN AG1 [get_ports A2_IN[5]]
set_property DIFF_TERM_ADV TERM_100 [get_ports A2_IN[5]]
set_property IOSTANDARD LVDS [get_ports A2_IN[5]]
# WARNING: Differential signals are inverted in respect to TE0808 9EG device. 
# Take care to invert the signal inside the PL! 

# Port A2_IN[4] = B64_L24_P (J4:48)
set_property PACKAGE_PIN AF1 [get_ports A2_IN[4]]
set_property DIFF_TERM_ADV TERM_100 [get_ports A2_IN[4]]
set_property IOSTANDARD LVDS [get_ports A2_IN[4]]
# WARNING: Differential signals are inverted in respect to TE0808 9EG device. 
# Take care to invert the signal inside the PL! 

# Port A2_IN[12] = B64_L14_P (J4:68)
set_property PACKAGE_PIN AC4 [get_ports A2_IN[12]]
set_property DIFF_TERM_ADV TERM_100 [get_ports A2_IN[12]]
set_property IOSTANDARD LVDS [get_ports A2_IN[12]]

# Port A2_IN[13] = B64_L14_N (J4:66)
set_property PACKAGE_PIN AC3 [get_ports A2_IN[13]]
set_property DIFF_TERM_ADV TERM_100 [get_ports A2_IN[13]]
set_property IOSTANDARD LVDS [get_ports A2_IN[13]]

# Port A2_IN[3] = B64_L23_N (J4:60)
set_property PACKAGE_PIN AH1 [get_ports A2_IN[3]]
set_property DIFF_TERM_ADV TERM_100 [get_ports A2_IN[3]]
set_property IOSTANDARD LVDS [get_ports A2_IN[3]]
# WARNING: Differential signals are inverted in respect to TE0808 9EG device. 
# Take care to invert the signal inside the PL! 

# Port A2_IN[2] = B64_L23_P (J4:62)
set_property PACKAGE_PIN AH2 [get_ports A2_IN[2]]
set_property DIFF_TERM_ADV TERM_100 [get_ports A2_IN[2]]
set_property IOSTANDARD LVDS [get_ports A2_IN[2]]
# WARNING: Differential signals are inverted in respect to TE0808 9EG device. 
# Take care to invert the signal inside the PL! 

# Port A2_IN[10] = B64_L21_P (J4:54)
set_property PACKAGE_PIN AE3 [get_ports A2_IN[10]]
set_property DIFF_TERM_ADV TERM_100 [get_ports A2_IN[10]]
set_property IOSTANDARD LVDS [get_ports A2_IN[10]]

# Port A2_IN[11] = B64_L21_N (J4:56)
set_property PACKAGE_PIN AF3 [get_ports A2_IN[11]]
set_property DIFF_TERM_ADV TERM_100 [get_ports A2_IN[11]]
set_property IOSTANDARD LVDS [get_ports A2_IN[11]]

# Port A2_IN[1] = B65_L9_N (J4:53)
set_property PACKAGE_PIN J2 [get_ports A2_IN[1]]
set_property DIFF_TERM_ADV TERM_100 [get_ports A2_IN[1]]
set_property IOSTANDARD LVDS [get_ports A2_IN[1]]
# WARNING: Differential signals are inverted in respect to TE0808 9EG device. 
# Take care to invert the signal inside the PL! 

# Port A2_IN[0] = B65_L9_P (J4:55)
set_property PACKAGE_PIN K2 [get_ports A2_IN[0]]
set_property DIFF_TERM_ADV TERM_100 [get_ports A2_IN[0]]
set_property IOSTANDARD LVDS [get_ports A2_IN[0]]
# WARNING: Differential signals are inverted in respect to TE0808 9EG device. 
# Take care to invert the signal inside the PL! 

# Port A2_IN[8] = B64_L13_P (J4:74)
set_property PACKAGE_PIN AD5 [get_ports A2_IN[8]]
set_property DIFF_TERM_ADV TERM_100 [get_ports A2_IN[8]]
set_property IOSTANDARD LVDS [get_ports A2_IN[8]]

# Port A2_IN[9] = B64_L13_N (J4:72)
set_property PACKAGE_PIN AD4 [get_ports A2_IN[9]]
set_property DIFF_TERM_ADV TERM_100 [get_ports A2_IN[9]]
set_property IOSTANDARD LVDS [get_ports A2_IN[9]]

