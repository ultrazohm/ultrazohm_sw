### Digital Adapter Board D3
# Author: Andreas Geiger
# Date: 10.09.2025

# D3_00 - D3_05
set_property PACKAGE_PIN K10    [get_ports {D3_OUT_PWM[0]}]
set_property PACKAGE_PIN U2     [get_ports {D3_OUT_PWM[1]}]
set_property PACKAGE_PIN L10    [get_ports {D3_OUT_PWM[2]}]
set_property PACKAGE_PIN U3     [get_ports {D3_OUT_PWM[3]}]
set_property PACKAGE_PIN U8     [get_ports {D3_OUT_PWM[4]}]
set_property PACKAGE_PIN V1     [get_ports {D3_OUT_PWM[5]}]

# D3_06
set_property PACKAGE_PIN V8     [get_ports D3_06_OUT_RESET_UVW]

# D3_07 - D3_12
set_property PACKAGE_PIN V2     [get_ports {D3_IN_FLT[0]}]
set_property PACKAGE_PIN V6     [get_ports {D3_IN_FLT[1]}]
set_property PACKAGE_PIN W1     [get_ports {D3_IN_FLT[2]}]
set_property PACKAGE_PIN V7     [get_ports {D3_IN_FLT[3]}]
set_property PACKAGE_PIN W2     [get_ports {D3_IN_FLT[4]}]
set_property PACKAGE_PIN W5     [get_ports {D3_IN_FLT[5]}]

# D3_13 - D3_18
set_property PACKAGE_PIN Y1     [get_ports {D3_IN_RDY[0]}]
set_property PACKAGE_PIN Y5     [get_ports {D3_IN_RDY[1]}]
set_property PACKAGE_PIN Y2     [get_ports {D3_IN_RDY[2]}]
set_property PACKAGE_PIN M12    [get_ports {D3_IN_RDY[3]}]
set_property PACKAGE_PIN U9     [get_ports {D3_IN_RDY[4]}]
set_property PACKAGE_PIN N12    [get_ports {D3_IN_RDY[5]}]

# D3_19 - D3_21
set_property PACKAGE_PIN V9     [get_ports {D3_IN_NTC[0]}]
set_property PACKAGE_PIN P10    [get_ports {D3_IN_NTC[1]}]
set_property PACKAGE_PIN P11    [get_ports {D3_IN_NTC[2]}]

# D3_22
set_property PACKAGE_PIN W6     [get_ports D3_22_OUT_TEMP_MCLK]

# D3_23
set_property PACKAGE_PIN W7     [get_ports D3_23_OUT_TEMP_MOSI]

# D3_24
set_property PACKAGE_PIN F10    [get_ports D3_24_IN_TEMP_MISO]

# D3_25
set_property PACKAGE_PIN D10    [get_ports D3_25_OUT_TEMP_CS]

# D3_26
set_property PACKAGE_PIN U5     [get_ports D3_26_IN_TEMP_VOB]

# D3_27
set_property PACKAGE_PIN T1     [get_ports D3_27_IN_TEMP_DCLK]

# D3_28
set_property PACKAGE_PIN U4     [get_ports D3_28_OUT_TEMP_VIA]

# D3_29
#set_property PACKAGE_PIN U1   [get_ports {D3_OUT_29[0]}]


set_property IOSTANDARD LVCMOS18 [get_ports D3_*]
set_property PULLDOWN true [get_ports {D3_OUT_PWM[5]}]
set_property PULLDOWN true [get_ports {D3_OUT_PWM[4]}]
set_property PULLDOWN true [get_ports {D3_OUT_PWM[3]}]
set_property PULLDOWN true [get_ports {D3_OUT_PWM[2]}]
set_property PULLDOWN true [get_ports {D3_OUT_PWM[1]}]
set_property PULLDOWN true [get_ports {D3_OUT_PWM[0]}]

