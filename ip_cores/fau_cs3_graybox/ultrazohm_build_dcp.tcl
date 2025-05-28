set accel_backend zusys_i/uz_user/board_design_graybox_0
set checkpoint_dir ./checkpoints


synth_design -flatten_hierarchy none

if { ![get_property IS_BLACKBOX [get_cells $accel_backend]] } {
	update_design -cell $accel_backend -black_box
}

write_checkpoint -force $checkpoint_dir/ultrazohm_base.dcp



