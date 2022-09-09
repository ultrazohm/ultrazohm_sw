###Digital Adapter Board D4: UZ_D_GaN_Inverter
# Author: Michael Hoerner
# Date: 08.04.2021
# DIG_IO_1
set_property PACKAGE_PIN A15    [get_ports D4_pwm_h1]
# DIG_IO_2
set_property PACKAGE_PIN J14 	[get_ports D4_pwm_l1]
# DIG_IO_3
set_property PACKAGE_PIN J12 	[get_ports D4_pwm_h2]
# DIG_IO_4
set_property PACKAGE_PIN E12 	[get_ports D4_pwm_l2]
# DIG_IO_5
set_property PACKAGE_PIN H11 	[get_ports D4_pwm_h3]
# DIG_IO_6
set_property PACKAGE_PIN D12 	[get_ports D4_pwm_l3]
# DIG_IO_7
set_property PACKAGE_PIN H12 	[get_ports D4_i1_diag]
# DIG_IO_8
set_property PACKAGE_PIN A12 	[get_ports D4_gan_h1_temp]
# DIG_IO_9
set_property PACKAGE_PIN G11 	[get_ports D4_i2_diag]
# DIG_IO_10
set_property PACKAGE_PIN A11 	[get_ports D4_gan_l1_temp]
# DIG_IO_11
set_property PACKAGE_PIN F12 	[get_ports D4_i3_diag]
# DIG_IO_12
set_property PACKAGE_PIN C12 	[get_ports D4_gan_l1_oc]
# DIG_IO_13
set_property PACKAGE_PIN F11 	[get_ports D4_i_diag]
# DIG_IO_14
set_property PACKAGE_PIN B11 	[get_ports D4_gan_l1_fault]
# DIG_IO_15
set_property PACKAGE_PIN J11 	[get_ports D4_pwm_en]
# DIG_IO_16
set_property PACKAGE_PIN D11 	[get_ports D4_gan_h1_oc]
# DIG_IO_17
set_property PACKAGE_PIN J10 	[get_ports D4_DIG_IO_17]
# DIG_IO_18
set_property PACKAGE_PIN C11 	[get_ports D4_gan_h1_fault]
# DIG_IO_19
set_property PACKAGE_PIN K13 	[get_ports D4_gan_h3_temp]
# DIG_IO_20
set_property PACKAGE_PIN B10 	[get_ports D4_gan_h2_temp]
# DIG_IO_21
set_property PACKAGE_PIN K12 	[get_ports D4_gan_l3_temp]
# DIG_IO_22
set_property PACKAGE_PIN A10 	[get_ports D4_gan_l2_temp]
# DIG_IO_23
set_property PACKAGE_PIN G10 	[get_ports D4_gan_l3_oc]
# DIG_IO_24
set_property PACKAGE_PIN E10 	[get_ports D4_gan_l2_oc]
# DIG_IO_25
set_property PACKAGE_PIN C14 	[get_ports D4_gan_l3_fault]
# DIG_IO_26
set_property PACKAGE_PIN H14 	[get_ports D4_gan_l2_fault]
# DIG_IO_27
set_property PACKAGE_PIN C13    [get_ports D4_gan_h3_oc]
# DIG_IO_28
set_property PACKAGE_PIN H13    [get_ports D4_gan_h2_oc]
# DIG_IO_29
set_property PACKAGE_PIN B15    [get_ports D4_gan_h3_fault]
# DIG_IO_30
set_property PACKAGE_PIN K14    [get_ports D4_gan_h2_fault]
set_property IOSTANDARD LVCMOS18 	[get_ports {D4_*}]
set_property PULLDOWN true 			[get_ports D4_PWM_*]
