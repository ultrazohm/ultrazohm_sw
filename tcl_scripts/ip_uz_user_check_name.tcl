puts "Starting script"
cd [ get_property DIRECTORY [current_project] ]

if { [string match "uz_user/uz_d_inverter_adapter_0" [expr {[get_property NAME [get_bd_cells uz_user/uz_d_inverter_adapter_0]] }]] } {
  puts "is true"
}