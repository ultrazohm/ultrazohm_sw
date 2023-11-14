###Digital Adapter Board D3: uz_inverter_adapter
# Author: Michael Hoerner
# Date: 11.02.2022

# DIG_IO_0
set_property PACKAGE_PIN K10    [get_ports D3_pwm_h1]
# DIG_IO_1
set_property PACKAGE_PIN U2 	[get_ports D3_pwm_l1]
# DIG_IO_2
set_property PACKAGE_PIN L10 	[get_ports D3_pwm_h2]
# DIG_IO_3
set_property PACKAGE_PIN U3 	[get_ports D3_pwm_l2]
# DIG_IO_4
set_property PACKAGE_PIN U8 	[get_ports D3_pwm_h3]
# DIG_IO_5
set_property PACKAGE_PIN V1 	[get_ports D3_pwm_l3]
# DIG_IO_6
set_property PACKAGE_PIN V8 	[get_ports D3_i1_diag]
# DIG_IO_7
set_property PACKAGE_PIN V2 	[get_ports D3_h1_temp]
# DIG_IO_8
set_property PACKAGE_PIN V6 	[get_ports D3_i2_diag]
# DIG_IO_9
set_property PACKAGE_PIN W1 	[get_ports D3_l1_temp]
# DIG_IO_10
set_property PACKAGE_PIN V7 	[get_ports D3_i3_diag]
# DIG_IO_11
set_property PACKAGE_PIN W2 	[get_ports D3_l1_oc]
# DIG_IO_12
set_property PACKAGE_PIN W5 	[get_ports D3_i_diag]
# DIG_IO_13
set_property PACKAGE_PIN Y1 	[get_ports D3_l1_fault]
# DIG_IO_14
set_property PACKAGE_PIN Y5 	[get_ports D3_pwm_en]
# DIG_IO_15
set_property PACKAGE_PIN Y2 	[get_ports D3_h1_oc]
# DIG_IO_16
set_property PACKAGE_PIN M12 	[get_ports D3_DIG_IO_17]
# DIG_IO_17
set_property PACKAGE_PIN U9 	[get_ports D3_h1_fault]
# DIG_IO_18
set_property PACKAGE_PIN N12 	[get_ports D3_h3_temp]
# DIG_IO_19
set_property PACKAGE_PIN V9 	[get_ports D3_h2_temp]
# DIG_IO_20
set_property PACKAGE_PIN P10 	[get_ports D3_l3_temp]
# DIG_IO_21
set_property PACKAGE_PIN P11 	[get_ports D3_l2_temp]
# DIG_IO_22
set_property PACKAGE_PIN W6 	[get_ports D3_l3_oc]
# DIG_IO_23
set_property PACKAGE_PIN W7 	[get_ports D3_l2_oc]
# DIG_IO_24
set_property PACKAGE_PIN F10 	[get_ports D3_l3_fault]
# DIG_IO_25
set_property PACKAGE_PIN D10 	[get_ports D3_l2_fault]
# DIG_IO_26
set_property PACKAGE_PIN U5    [get_ports D3_h3_oc]
# DIG_IO_27
set_property PACKAGE_PIN T1    [get_ports D3_h2_oc]
# DIG_IO_28
set_property PACKAGE_PIN U4    [get_ports D3_h3_fault]
# DIG_IO_29
set_property PACKAGE_PIN U1    [get_ports D3_h2_fault]

set_property IOSTANDARD LVCMOS18 	[get_ports {D3_*}]
set_property PULLDOWN true 			[get_ports D3_PWM_*]