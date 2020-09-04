###Output GPIO Pins and Reserve PWM-Pins
## Author: Sebastian Wendel
## Date: 01.06.2018
## All Pins are 1,8 Volt on Bank33


##[get_ports B66_L6_P]
##set_property PACKAGE_PIN T1 [get_ports {gpio_io_o[0]}]
#set_property PACKAGE_PIN T1 [get_ports TestPWM] 
##[get_ports B66_L6_N]
##set_property PACKAGE_PIN U1 [get_ports {gpio_io_o[1]}] 
#set_property PACKAGE_PIN U1 [get_ports CurrentValid] 
##[get_ports B66_L5_P]
##set_property PACKAGE_PIN U2 [get_ports {gpio_io_o[2]}] 
#set_property PACKAGE_PIN U2 [get_ports Start_ADC] 
##[get_ports B66_L5_N]
##set_property PACKAGE_PIN U3 [get_ports {gpio_io_o[3]}] 
#set_property PACKAGE_PIN U3 [get_ports ip2intc_irpt] 
##[get_ports B66_L4_P] 
#set_property PACKAGE_PIN V2 [get_ports f_cf]
##[get_ports B66_L4_N] 
#set_property PACKAGE_PIN V1 [get_ports f_cc] 



####Set voltage level for GPIO Pins
##set_property IOSTANDARD LVCMOS33 [get_ports {gpio_io_o[0]}]
#set_property IOSTANDARD LVCMOS18 [get_ports TestPWM]
##set_property IOSTANDARD LVCMOS33 [get_ports {gpio_io_o[1]}]
#set_property IOSTANDARD LVCMOS18 [get_ports CurrentValid]
##set_property IOSTANDARD LVCMOS33 [get_ports {gpio_io_o[2]}]
#set_property IOSTANDARD LVCMOS18 [get_ports Start_ADC]
##set_property IOSTANDARD LVCMOS33 [get_ports {gpio_io_o[3]}]
#set_property IOSTANDARD LVCMOS18 [get_ports ip2intc_irpt]
#set_property IOSTANDARD LVCMOS18 [get_ports f_cf]
#set_property IOSTANDARD LVCMOS18 [get_ports f_cc]












