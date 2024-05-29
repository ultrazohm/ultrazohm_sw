###Digital Adapter Board D2: uz_inverter_adapter
# Author: Michael Hoerner
# Date: 11.02.2022

# DIG_IO_0
set_property PACKAGE_PIN W4    	[get_ports D2_pwm_h1]
# DIG_IO_1
set_property PACKAGE_PIN U10 	[get_ports D2_pwm_l1]
# DIG_IO_2
set_property PACKAGE_PIN U11 	[get_ports D2_pwm_h2]
# DIG_IO_3
set_property PACKAGE_PIN U6 	[get_ports D2_pwm_l2]
# DIG_IO_4
set_property PACKAGE_PIN V11 	[get_ports D2_pwm_h3]
# DIG_IO_5
set_property PACKAGE_PIN U7		[get_ports D2_pwm_l3]
# DIG_IO_6
set_property PACKAGE_PIN Y3 	[get_ports D2_i1_diag]
# DIG_IO_7
set_property PACKAGE_PIN N11 	[get_ports D2_h1_temp]
# DIG_IO_8
set_property PACKAGE_PIN Y4 	[get_ports D2_i2_diag]
# DIG_IO_9
set_property PACKAGE_PIN Y10 	[get_ports D2_l1_temp]
# DIG_IO_10
set_property PACKAGE_PIN Y7 	[get_ports D2_i3_diag]
# DIG_IO_11
set_property PACKAGE_PIN Y8 	[get_ports D2_l1_oc]
# DIG_IO_12
set_property PACKAGE_PIN V3 	[get_ports D2_i_diag]
# DIG_IO_13
set_property PACKAGE_PIN Y9 	[get_ports D2_l1_fault]
# DIG_IO_14
set_property PACKAGE_PIN AE1 	[get_ports D2_pwm_en]
# DIG_IO_15
set_property PACKAGE_PIN AE7 	[get_ports D2_h1_oc]
# DIG_IO_16
set_property PACKAGE_PIN AE8 	[get_ports D2_DIG_IO_17]
# DIG_IO_17
set_property PACKAGE_PIN AC12 	[get_ports D2_h1_fault]
# DIG_IO_18
set_property PACKAGE_PIN AA1 	[get_ports D2_h3_temp]
# DIG_IO_19
set_property PACKAGE_PIN AB1 	[get_ports D2_h2_temp]
# DIG_IO_20
set_property PACKAGE_PIN AC1 	[get_ports D2_l3_temp]
# DIG_IO_21
set_property PACKAGE_PIN AD1 	[get_ports D2_l2_temp]
# DIG_IO_22
set_property PACKAGE_PIN AA2 	[get_ports D2_l3_oc]
# DIG_IO_23
set_property PACKAGE_PIN AA3 	[get_ports D2_l2_oc]
# DIG_IO_24
set_property PACKAGE_PIN W10 	[get_ports D2_l3_fault]
# DIG_IO_25
set_property PACKAGE_PIN T10 	[get_ports D2_l2_fault]
# DIG_IO_26
set_property PACKAGE_PIN W11    [get_ports D2_h3_oc]
# DIG_IO_27
set_property PACKAGE_PIN R10    [get_ports D2_h2_oc]
# DIG_IO_28
set_property PACKAGE_PIN V4     [get_ports D2_h3_fault]
# DIG_IO_29
set_property PACKAGE_PIN T11    [get_ports D2_h2_fault]

set_property IOSTANDARD LVCMOS18 	[get_ports {D2_*}]
set_property PULLDOWN true 			[get_ports D2_OUT_*]

