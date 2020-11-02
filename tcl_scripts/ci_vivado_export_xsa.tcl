open_project vivado/project/ultrazohm.xpr
set work_directory [get_property DIRECTORY [current_project]] ; 
cd $work_directory ; 
write_hw_platform -fixed -force -include_bit -file {../../vitis/vivado_exported_xsa/zusys_wrapper.xsa}
