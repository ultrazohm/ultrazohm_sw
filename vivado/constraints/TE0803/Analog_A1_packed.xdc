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


# Port A1_OUT_CLK[0] = B64_L11_P (J4:128)
set_property PACKAGE_PIN AF7 [get_ports A1_OUT_CLK[0]]
set_property IOSTANDARD LVDS [get_ports A1_OUT_CLK[0]]

# Port A1_OUT_CLK[1] = B64_L11_N (J4:126)
set_property PACKAGE_PIN AF6 [get_ports A1_OUT_CLK[1]]
set_property IOSTANDARD LVDS [get_ports A1_OUT_CLK[1]]

# Port A1_OUT_CNV_1[0] = B64_L1_N (J4:144)
set_property PACKAGE_PIN AD9 [get_ports A1_OUT_CNV_1[0]]
set_property IOSTANDARD LVCMOS18 [get_ports A1_OUT_CNV_1[0]]

# Port A1_OUT_CNV_0[0] = B64_L1_P (J4:146)
set_property PACKAGE_PIN AC9 [get_ports A1_OUT_CNV_0[0]]
set_property IOSTANDARD LVCMOS18 [get_ports A1_OUT_CNV_0[0]]

# Port A1_IN[6] = B64_L4_P (J4:140)
set_property PACKAGE_PIN AD7 [get_ports A1_IN[6]]
set_property DIFF_TERM_ADV TERM_100 [get_ports A1_IN[6]]
set_property IOSTANDARD LVDS [get_ports A1_IN[6]]

# Port A1_IN[7] = B64_L4_N (J4:138)
set_property PACKAGE_PIN AE7 [get_ports A1_IN[7]]
set_property DIFF_TERM_ADV TERM_100 [get_ports A1_IN[7]]
set_property IOSTANDARD LVDS [get_ports A1_IN[7]]

# Port A1_IN[14] = B64_L2_P (J4:134)
set_property PACKAGE_PIN AE9 [get_ports A1_IN[14]]
set_property DIFF_TERM_ADV TERM_100 [get_ports A1_IN[14]]
set_property IOSTANDARD LVDS [get_ports A1_IN[14]]

# Port A1_IN[15] = B64_L2_N (J4:132)
set_property PACKAGE_PIN AE8 [get_ports A1_IN[15]]
set_property DIFF_TERM_ADV TERM_100 [get_ports A1_IN[15]]
set_property IOSTANDARD LVDS [get_ports A1_IN[15]]

# Port A1_IN[4] = B65_L10_P (J4:131)
set_property PACKAGE_PIN H4 [get_ports A1_IN[4]]
set_property DIFF_TERM_ADV TERM_100 [get_ports A1_IN[4]]
set_property IOSTANDARD LVDS [get_ports A1_IN[4]]

# Port A1_IN[5] = B65_L10_N (J4:133)
set_property PACKAGE_PIN H3 [get_ports A1_IN[5]]
set_property DIFF_TERM_ADV TERM_100 [get_ports A1_IN[5]]
set_property IOSTANDARD LVDS [get_ports A1_IN[5]]

# Port A1_IN[13] = B64_L3_N (J4:150)
set_property PACKAGE_PIN AC8 [get_ports A1_IN[13]]
set_property DIFF_TERM_ADV TERM_100 [get_ports A1_IN[13]]
set_property IOSTANDARD LVDS [get_ports A1_IN[13]]
# WARNING: Differential signals are inverted in respect to TE0808 9EG device. 
# Take care to invert the signal inside the PL! 

# Port A1_IN[12] = B64_L3_P (J4:152)
set_property PACKAGE_PIN AB8 [get_ports A1_IN[12]]
set_property DIFF_TERM_ADV TERM_100 [get_ports A1_IN[12]]
set_property IOSTANDARD LVDS [get_ports A1_IN[12]]
# WARNING: Differential signals are inverted in respect to TE0808 9EG device. 
# Take care to invert the signal inside the PL! 

# Port A1_IN[2] = B64_L7_P (J4:122)
set_property PACKAGE_PIN AG9 [get_ports A1_IN[2]]
set_property DIFF_TERM_ADV TERM_100 [get_ports A1_IN[2]]
set_property IOSTANDARD LVDS [get_ports A1_IN[2]]

# Port A1_IN[3] = B64_L7_N (J4:120)
set_property PACKAGE_PIN AH9 [get_ports A1_IN[3]]
set_property DIFF_TERM_ADV TERM_100 [get_ports A1_IN[3]]
set_property IOSTANDARD LVDS [get_ports A1_IN[3]]

# Port A1_IN[11] = B64_L8_N (J4:114)
set_property PACKAGE_PIN AG8 [get_ports A1_IN[11]]
set_property DIFF_TERM_ADV TERM_100 [get_ports A1_IN[11]]
set_property IOSTANDARD LVDS [get_ports A1_IN[11]]
# WARNING: Differential signals are inverted in respect to TE0808 9EG device. 
# Take care to invert the signal inside the PL! 

# Port A1_IN[10] = B64_L8_P (J4:116)
set_property PACKAGE_PIN AF8 [get_ports A1_IN[10]]
set_property DIFF_TERM_ADV TERM_100 [get_ports A1_IN[10]]
set_property IOSTANDARD LVDS [get_ports A1_IN[10]]
# WARNING: Differential signals are inverted in respect to TE0808 9EG device. 
# Take care to invert the signal inside the PL! 

# Port A1_IN[0] = B64_L9_P (J4:110)
set_property PACKAGE_PIN AH8 [get_ports A1_IN[0]]
set_property DIFF_TERM_ADV TERM_100 [get_ports A1_IN[0]]
set_property IOSTANDARD LVDS [get_ports A1_IN[0]]

# Port A1_IN[1] = B64_L9_N (J4:108)
set_property PACKAGE_PIN AH7 [get_ports A1_IN[1]]
set_property DIFF_TERM_ADV TERM_100 [get_ports A1_IN[1]]
set_property IOSTANDARD LVDS [get_ports A1_IN[1]]

# Port A1_IN[8] = B65_L13_P (J4:89)
set_property PACKAGE_PIN L7 [get_ports A1_IN[8]]
set_property DIFF_TERM_ADV TERM_100 [get_ports A1_IN[8]]
set_property IOSTANDARD LVDS [get_ports A1_IN[8]]

# Port A1_IN[9] = B65_L13_N (J4:91)
set_property PACKAGE_PIN L6 [get_ports A1_IN[9]]
set_property DIFF_TERM_ADV TERM_100 [get_ports A1_IN[9]]
set_property IOSTANDARD LVDS [get_ports A1_IN[9]]

