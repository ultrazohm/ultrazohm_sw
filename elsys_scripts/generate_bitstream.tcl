set accel_site zusys_i/uz_user/graybox_0
set checkpoint_dir ./checkpoints
set bitstream_dir ./bitstream
mkdir $bitstream_dir
# TODO parameter for accel and project  name
set project_cp_name $checkpoint_dir/init_route_design.dcp
set accel_cp_name $checkpoint_dir/vector_add_graybox.dcp

open_checkpoint $project_cp_name
read_checkpoint -cell $accel_site $accel_cp_name


opt_design 
place_design
if {[get_property SLACK [get_timing_paths -quiet -max_paths 1 -nworst 1 -setup]] < 0.0} {
	phys_opt_design 
}
route_design

set_property BITSTREAM.GENERAL.COMPRESS TRUE [current_design]

set bitstream_name $bitstream_dir/vector_add_test.bit
write_bitstream -force -file $bitstream_name
close_project
