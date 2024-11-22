set script_dir "[file dirname "[file normalize "[info script]"]"]"

set design_dir [lindex $argv 0]
set num_accelerators [lindex $argv 1]

set system_dir $design_dir/system
set checkpoint_dir $design_dir/checkpoints
set bitstream_dir $design_dir/bitstream

set proj_path $system_dir/board_design/build_design/board_design.xpr
set top board_design_wrapper

set pr_sites [list]
for {set i 0} {$i < $num_accelerators} {incr i} {
	lappend pr_sites board_design_i/accelerator_backend/graybox_$i
}

source "${system_dir}/board_config.tcl"
open_project $proj_path
synth_design -flatten_hierarchy none -top $top -part $PART_NAME -quiet

set argv [list $num_accelerators]
set argc 1
source "${design_dir}/pr_regions.tcl"

for {set i 0} {$i < $num_accelerators} {incr i} {
	# configure pblock
	set_property HD.RECONFIGURABLE TRUE [get_cells [lindex $pr_sites $i]]
	add_cells_to_pblock core_$i [get_cells [list [lindex $pr_sites $i]]] -clear_locs
	if { ! $PART_IS_ULTRASCALE } {
		set_property RESET_AFTER_RECONFIG true [get_pblocks core_$i]
	}
	set_property SNAPPING_MODE ON [get_pblocks core_$i]
	set_property PARTPIN_SPREADING 5 [get_pblocks core_$i]
	update_design -cell [lindex $pr_sites $i] -black_box
	update_design -cell [lindex $pr_sites $i] -buffer_ports
}

set pr_boundary_file $system_dir/board_design/pr_boundary.xdc
read_xdc -no_add $pr_boundary_file

set iterations 10
set threshold 0.0

set argv [list $iterations $threshold]
set argc 2
set ret_val [catch {source "${script_dir}/../place_and_route.tcl"} ret_msg]
if { $ret_val } {
	write_checkpoint -force $checkpoint_dir/init_route_error.dcp
	error $ret_msg
}

write_checkpoint -force $checkpoint_dir/init_route_design.dcp
set_property BITSTREAM.GENERAL.COMPRESS TRUE [current_design]
write_bitstream -force -no_partial_bitfile -file $bitstream_dir/static.bit

for {set i 0} {$i < $num_accelerators} {incr i} {
	update_design -cell [lindex $pr_sites $i] -black_box
}
lock_design -level routing
write_checkpoint -force $checkpoint_dir/static_route_design.dcp
close_project
