### Digital Adapter Board D2
# Author: Andreas Geiger
# Date: 09.04.2025

# D2_00 - D2_05
set_property PACKAGE_PIN W4 	[get_ports {D2_OUT_PWM[0]}]
set_property PACKAGE_PIN U10 	[get_ports {D2_OUT_PWM[1]}]
set_property PACKAGE_PIN U11 	[get_ports {D2_OUT_PWM[2]}]
set_property PACKAGE_PIN U6 	[get_ports {D2_OUT_PWM[3]}]
set_property PACKAGE_PIN V11 	[get_ports {D2_OUT_PWM[4]}]
set_property PACKAGE_PIN U7 	[get_ports {D2_OUT_PWM[5]}]

# D2_06
set_property PACKAGE_PIN Y3  	[get_ports D2_06_OUT_RESET_UVW]

# D2_07 - D2_12
set_property PACKAGE_PIN N11  	[get_ports {D2_IN_FLT[0]}]
set_property PACKAGE_PIN Y4  	[get_ports {D2_IN_FLT[1]}]
set_property PACKAGE_PIN Y10  	[get_ports {D2_IN_FLT[2]}]
set_property PACKAGE_PIN Y7 	[get_ports {D2_IN_FLT[3]}]
set_property PACKAGE_PIN Y8 	[get_ports {D2_IN_FLT[4]}]
set_property PACKAGE_PIN V3  	[get_ports {D2_IN_FLT[5]}]

# D2_13 - D2_18
set_property PACKAGE_PIN Y9 	[get_ports {D2_IN_RDY[0]}]
set_property PACKAGE_PIN AE1 	[get_ports {D2_IN_RDY[1]}]
set_property PACKAGE_PIN AE7 	[get_ports {D2_IN_RDY[2]}]
set_property PACKAGE_PIN AE8 	[get_ports {D2_IN_RDY[3]}]
set_property PACKAGE_PIN AC12 	[get_ports {D2_IN_RDY[4]}]
set_property PACKAGE_PIN AA1 	[get_ports {D2_IN_RDY[5]}]

# D2_19 - D2_21
set_property PACKAGE_PIN AB1 	[get_ports {D2_IN_NTC[0]}]
set_property PACKAGE_PIN AC1 	[get_ports {D2_IN_NTC[1]}]
set_property PACKAGE_PIN AD1 	[get_ports {D2_IN_NTC[2]}]

# D2_22
set_property PACKAGE_PIN AA2 	[get_ports D2_22_OUT_PYRO_RESET]

# D2_23
set_property PACKAGE_PIN AA3 	[get_ports D2_23_OUT_PYRO_ENABLE]

# D2_24
set_property PACKAGE_PIN W10 	[get_ports D2_24_IN_IGNITION_SUCCESS2]

# D2_25
set_property PACKAGE_PIN T10 	[get_ports D2_25_IN_IGNITION_SUCCESS3]

# D2_26
set_property PACKAGE_PIN W11    [get_ports D2_26_OUT_CS_SQUIB1]

# D2_27
set_property PACKAGE_PIN R10    [get_ports D2_27_OUT_CS_SQUIB2]

# D2_28
set_property PACKAGE_PIN V4     [get_ports D2_28_OUT_CS_SQUIB3]

# D2_29
#set_property PACKAGE_PIN T11    [get_ports {D2_OUT_29[0]}]


set_property IOSTANDARD LVCMOS18 [get_ports D2_*]
set_property PULLDOWN true [get_ports {D2_OUT_PWM[5]}]
set_property PULLDOWN true [get_ports {D2_OUT_PWM[4]}]
set_property PULLDOWN true [get_ports {D2_OUT_PWM[3]}]
set_property PULLDOWN true [get_ports {D2_OUT_PWM[2]}]
set_property PULLDOWN true [get_ports {D2_OUT_PWM[1]}]
set_property PULLDOWN true [get_ports {D2_OUT_PWM[0]}]

