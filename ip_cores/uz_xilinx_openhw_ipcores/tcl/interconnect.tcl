connect_bd_net [get_bd_pins uz_user/fix_to_float_current/out_0] [get_bd_pins uz_user/transformation_and_control/in_a1] -boundary_type upper
connect_bd_net [get_bd_pins uz_user/fix_to_float_current/out_1] [get_bd_pins uz_user/transformation_and_control/in_b1] -boundary_type upper
connect_bd_net [get_bd_pins uz_user/fix_to_float_current/out_2] [get_bd_pins uz_user/transformation_and_control/in_c1] -boundary_type upper
connect_bd_net [get_bd_pins uz_user/fix_to_float_current/out_3] [get_bd_pins uz_user/transformation_and_control/in_a2] -boundary_type upper
connect_bd_net [get_bd_pins uz_user/fix_to_float_current/out_4] [get_bd_pins uz_user/transformation_and_control/in_b2] -boundary_type upper
connect_bd_net [get_bd_pins uz_user/fix_to_float_current/out_5] [get_bd_pins uz_user/transformation_and_control/in_c2] -boundary_type upper
connect_bd_net [get_bd_pins uz_user/fix_to_float_current/ap_done] [get_bd_pins uz_user/transformation_and_control/ap_start] -boundary_type upper

connect_bd_net [get_bd_pins uz_user/transformation_and_control/out_dc_a1] [get_bd_pins uz_user/float_to_fix_dutycycle/in_0] -boundary_type upper
connect_bd_net [get_bd_pins uz_user/transformation_and_control/out_dc_b1] [get_bd_pins uz_user/float_to_fix_dutycycle/in_1] -boundary_type upper
connect_bd_net [get_bd_pins uz_user/transformation_and_control/out_dc_c1] [get_bd_pins uz_user/float_to_fix_dutycycle/in_2] -boundary_type upper
connect_bd_net [get_bd_pins uz_user/transformation_and_control/out_dc_a2] [get_bd_pins uz_user/float_to_fix_dutycycle/in_3] -boundary_type upper
connect_bd_net [get_bd_pins uz_user/transformation_and_control/out_dc_b2] [get_bd_pins uz_user/float_to_fix_dutycycle/in_4] -boundary_type upper
connect_bd_net [get_bd_pins uz_user/transformation_and_control/out_dc_c2] [get_bd_pins uz_user/float_to_fix_dutycycle/in_5] -boundary_type upper

connect_bd_net [get_bd_pins uz_user/transformation_and_control/ap_done] [get_bd_pins uz_user/float_to_fix_dutycycle/sp_start] -boundary_type upper
connect_bd_net [get_bd_pins uz_user/fix_to_float_current/rst] [get_bd_pins uz_user/transformation_and_control/ap_rst] -boundary_type upper
connect_bd_net [get_bd_pins uz_user/transformation_and_control/ap_rst] [get_bd_pins uz_user/float_to_fix_dutycycle/rst] -boundary_type upper
connect_bd_net [get_bd_pins uz_user/fix_to_float_current/clk] [get_bd_pins uz_user/transformation_and_control/ap_clk] -boundary_type upper
connect_bd_net [get_bd_pins uz_user/transformation_and_control/ap_clk] [get_bd_pins uz_user/float_to_fix_dutycycle/clk] -boundary_type upper