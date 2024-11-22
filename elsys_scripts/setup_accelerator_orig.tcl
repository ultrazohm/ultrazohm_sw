set script_dir "[file dirname "[file normalize "[info script]"]"]"

set design_dir [lindex $argv 0]
set kernel_name [lindex $argv 1]
set num_accelerators [lindex $argv 2]
set databus_width [lindex $argv 3]
set vaddr_bits [lindex $argv 4]
set use_hard_float [lindex $argv 5]
set dsp_a_width [lindex $argv 6]
set dsp_b_width [lindex $argv 7]
set num_cus [lindex $argv 8]
set wf_size [lindex $argv 9]
set grid_bits [lindex $argv 10]
set secure_txn [lindex $argv 11]

set cache_line_size [expr {16 * ($databus_width / 8)}]

set system_dir $design_dir/system
set checkpoint_dir $design_dir/checkpoints
set bitstream_dir $design_dir/bitstream

set accel_dir $system_dir/$kernel_name

set proj_path $accel_dir/build/${kernel_name}.xpr
set top ${kernel_name}_unit

set pr_sites [list]
for {set i 0} {$i < $num_accelerators} {incr i} {
	lappend pr_sites board_design_i/accelerator_backend/graybox_$i
}

source "${system_dir}/board_config.tcl" 
open_project $proj_path
synth_design -flatten_hierarchy rebuilt -top $top -part $PART_NAME -mode out_of_context \
             -generic C_WAVEFRONT_SIZE=$wf_size -generic C_USABLE_ADDR_BITS=$vaddr_bits -generic C_NUM_COMPUTE_UNITS=$num_cus \
             -generic C_DATA_AXI_DATA_WIDTH=$databus_width -generic C_L2_CACHE_LINE_SIZE=$cache_line_size \
             -generic C_HARD_FLOAT=$use_hard_float -generic C_DSP_A_WIDTH=$dsp_a_width -generic C_DSP_B_WIDTH=$dsp_b_width \
             -generic C_MAX_GRID_SIZE_BITS=$grid_bits -generic C_SECURE_TRANSACTION=$secure_txn -quiet
write_checkpoint -force $checkpoint_dir/trial_synth_${kernel_name}_cu${num_cus}_wf${wf_size}.dcp
close_project

open_checkpoint $checkpoint_dir/static_route_design.dcp
for {set i 0} {$i < $num_accelerators} {incr i} {
	read_checkpoint -cell [lindex $pr_sites $i] $checkpoint_dir/trial_synth_${kernel_name}_cu${num_cus}_wf${wf_size}.dcp
}

set iterations 5
set threshold 0.0

set argv [list $iterations $threshold]
set argc 2
set ret_val [catch {source "${script_dir}/../place_and_route.tcl"} ret_msg]

if { $ret_val } {
	set update_run [file exists "$checkpoint_dir/synth_${kernel_name}.dcp"]
	if { $update_run } {
		file delete -force $checkpoint_dir/trial_synth_${kernel_name}_cu${num_cus}_wf${wf_size}.dcp
	} else {
		write_checkpoint -force $checkpoint_dir/${kernel_name}_route_error.dcp
	}
	error $ret_msg
}

file rename -force $checkpoint_dir/trial_synth_${kernel_name}_cu${num_cus}_wf${wf_size}.dcp $checkpoint_dir/synth_${kernel_name}.dcp
write_checkpoint -force $checkpoint_dir/${kernel_name}_route_design.dcp
pr_verify $checkpoint_dir/init_route_design.dcp $checkpoint_dir/${kernel_name}_route_design.dcp
set_property BITSTREAM.GENERAL.COMPRESS TRUE [current_design]
for {set i 0} {$i < $num_accelerators} {incr i} {
	write_bitstream -force -cell [lindex $pr_sites $i] -file $bitstream_dir/${kernel_name}_core_${i}_partial.bit
}
close_project

