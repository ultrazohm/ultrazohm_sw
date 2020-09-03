#	cd [get_property DIRECTORY [current_project]]
#	source {./vivado_export_xsa.tcl}

set work_directory [get_property DIRECTORY [current_project]] ; 
cd $work_directory ; 
write_hw_platform -fixed -force -include_bit -file {../vitis/vivado_exported_xsa/zusys_wrapper.xsa}
