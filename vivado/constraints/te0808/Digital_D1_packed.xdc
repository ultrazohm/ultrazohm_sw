###Digital Adapter Board D1: uz_inverter_adapter
# Author: Michael Hoerner
# Date: 11.02.2022

# DIG_IO_0
set_property PACKAGE_PIN AC9    [get_ports D1_pwm_h1]
# DIG_IO_1
set_property PACKAGE_PIN AB9 	[get_ports D1_pwm_l1]
# DIG_IO_2
set_property PACKAGE_PIN AB10 	[get_ports D1_pwm_h2]
# DIG_IO_3
set_property PACKAGE_PIN AB11 	[get_ports D1_pwm_l2]
# DIG_IO_4
set_property PACKAGE_PIN AJ11 	[get_ports D1_pwm_h3]
# DIG_IO_5
set_property PACKAGE_PIN AK11 	[get_ports D1_pwm_l3]
# DIG_IO_6
set_property PACKAGE_PIN AA7 	[get_ports D1_i1_diag]
# DIG_IO_7
set_property PACKAGE_PIN AA8 	[get_ports D1_h1_temp]
# DIG_IO_8
set_property PACKAGE_PIN AE9 	[get_ports D1_i2_diag]
# DIG_IO_9
set_property PACKAGE_PIN AD9 	[get_ports D1_l1_temp]
# DIG_IO_10
set_property PACKAGE_PIN AD11 	[get_ports D1_i3_diag]
# DIG_IO_11
set_property PACKAGE_PIN AC11 	[get_ports D1_l1_oc]
# DIG_IO_12
set_property PACKAGE_PIN AD6 	[get_ports D1_i_diag]
# DIG_IO_13
set_property PACKAGE_PIN AC6 	[get_ports D1_l1_fault]
# DIG_IO_14
set_property PACKAGE_PIN AD10 	[get_ports D1_pwm_en]
# DIG_IO_15
set_property PACKAGE_PIN AE10 	[get_ports D1_h1_oc]
# DIG_IO_16
set_property PACKAGE_PIN AF13 	[get_ports D1_DIG_IO_17]
# DIG_IO_17
set_property PACKAGE_PIN AE13 	[get_ports D1_h1_fault]
# DIG_IO_18
set_property PACKAGE_PIN AE12 	[get_ports D1_h3_temp]
# DIG_IO_19
set_property PACKAGE_PIN AD12 	[get_ports D1_h2_temp]
# DIG_IO_20
set_property PACKAGE_PIN AB13 	[get_ports D1_l3_temp]
# DIG_IO_21
set_property PACKAGE_PIN AC13 	[get_ports D1_l2_temp]
# DIG_IO_22
set_property PACKAGE_PIN AA12 	[get_ports D1_l3_oc]
# DIG_IO_23
set_property PACKAGE_PIN AA11 	[get_ports D1_l2_oc]
# DIG_IO_24
set_property PACKAGE_PIN AF1 	[get_ports D1_l3_fault]
# DIG_IO_25
set_property PACKAGE_PIN AF2 	[get_ports D1_l2_fault]
# DIG_IO_26
set_property PACKAGE_PIN AC3    [get_ports D1_h3_oc]
# DIG_IO_27
set_property PACKAGE_PIN AB3    [get_ports D1_h2_oc]
# DIG_IO_28
set_property PACKAGE_PIN AA5    [get_ports D1_h3_fault]
# DIG_IO_29
set_property PACKAGE_PIN AA6    [get_ports D1_h2_fault]

set_property IOSTANDARD LVCMOS18 	[get_ports {D1_*}]
set_property PULLDOWN true 			[get_ports D1_PWM_*]