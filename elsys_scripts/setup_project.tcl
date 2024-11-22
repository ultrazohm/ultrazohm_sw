set accel_site zusys_i/uz_user/graybox_0
set checkpoint_dir ./checkpoints


synth_design -flatten_hierarchy none
update_design -cell $accel_site -black_box

write_checkpoint -force $checkpoint_dir/init_route_design.dcp
