### Digital Adapter Board D1
# Author: Andreas Geiger
# Date: 09.04.2025

# D1_00 - D1_05
set_property PACKAGE_PIN AC9    [get_ports {D1_OUT_PWM[0]}]
set_property PACKAGE_PIN AB9    [get_ports {D1_OUT_PWM[1]}]
set_property PACKAGE_PIN AB10   [get_ports {D1_OUT_PWM[2]}]
set_property PACKAGE_PIN AB11   [get_ports {D1_OUT_PWM[3]}]
set_property PACKAGE_PIN AJ11   [get_ports {D1_OUT_PWM[4]}]
set_property PACKAGE_PIN AK11   [get_ports {D1_OUT_PWM[5]}]

# D1_06
set_property PACKAGE_PIN AA7  	[get_ports D1_06_OUT_RESET_UVW]

# D1_07 - D1_12
set_property PACKAGE_PIN AA8  	[get_ports {D1_IN_FLT[0]}]
set_property PACKAGE_PIN AE9  	[get_ports {D1_IN_FLT[1]}]
set_property PACKAGE_PIN AD9  	[get_ports {D1_IN_FLT[2]}]
set_property PACKAGE_PIN AD11 	[get_ports {D1_IN_FLT[3]}]
set_property PACKAGE_PIN AC11 	[get_ports {D1_IN_FLT[4]}]
set_property PACKAGE_PIN AD6  	[get_ports {D1_IN_FLT[5]}]

# D1_13 - D1_18
set_property PACKAGE_PIN AC6  	[get_ports {D1_IN_RDY[0]}]
set_property PACKAGE_PIN AD10 	[get_ports {D1_IN_RDY[1]}]
set_property PACKAGE_PIN AE10 	[get_ports {D1_IN_RDY[2]}]
set_property PACKAGE_PIN AF13 	[get_ports {D1_IN_RDY[3]}]
set_property PACKAGE_PIN AE13 	[get_ports {D1_IN_RDY[4]}]
set_property PACKAGE_PIN AE12 	[get_ports {D1_IN_RDY[5]}]

# D1_19 - D1_21
set_property PACKAGE_PIN AD12  	[get_ports {D1_IN_NTC[0]}]
set_property PACKAGE_PIN AB13  	[get_ports {D1_IN_NTC[1]}]
set_property PACKAGE_PIN AC13  	[get_ports {D1_IN_NTC[2]}]

# D1_22
set_property PACKAGE_PIN AA12  	[get_ports D1_22_OUT_KL15]

# D1_23
set_property PACKAGE_PIN AA11  	[get_ports D1_23_IN_KL15_PG]

# D1_24
set_property PACKAGE_PIN AF1  	[get_ports D1_24_OUT_PYRO_TRIGGER]

# D1_25
set_property PACKAGE_PIN AF2  	[get_ports D1_25_IN_IGNITION_SUCCESS]

# D1_26
set_property PACKAGE_PIN AC3    [get_ports D1_26_OUT_RELAY2_CLOSE]

# D1_27
set_property PACKAGE_PIN AB3    [get_ports D1_27_IN_RELAY2_NOT_CLOSED]

# D1_28
set_property PACKAGE_PIN AA5    [get_ports D1_28_OUT_RELAY3_CLOSE]

# D1_29
set_property PACKAGE_PIN AA6    [get_ports D1_29_IN_RELAY3_NOT_CLOSED]


set_property IOSTANDARD LVCMOS18 [get_ports D1_*]
set_property PULLDOWN true [get_ports {D1_OUT_PWM[5]}]
set_property PULLDOWN true [get_ports {D1_OUT_PWM[4]}]
set_property PULLDOWN true [get_ports {D1_OUT_PWM[3]}]
set_property PULLDOWN true [get_ports {D1_OUT_PWM[2]}]
set_property PULLDOWN true [get_ports {D1_OUT_PWM[1]}]
set_property PULLDOWN true [get_ports {D1_OUT_PWM[0]}]

