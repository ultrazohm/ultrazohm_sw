ipx::package_project -force -vendor {fau.de} -taxonomy {/HSA} -import_files -root_dir "[get_property DIRECTORY [current_project]]/ip"

set_property vendor              {fau.de}                 [ipx::current_core]
set_property library             {hsa}                    [ipx::current_core]
set_property taxonomy            {{/HSA}}                 [ipx::current_core]
set_property vendor_display_name {FAU Erlangen-Nuremberg} [ipx::current_core]
set_property company_url         {https://fau.de}         [ipx::current_core]

#####################################
# Actual IP Settings

set_property name {board_design_graybox} [ipx::current_core]
set_property display_name {FAU CS3 Graybox} [ipx::current_core]
set_property description {FAU accelerator backend interface template} [ipx::current_core]

ipx::infer_bus_interface HOST_PP_IRQ xilinx.com:signal:interrupt_rtl:1.0 [ipx::current_core]
ipx::associate_bus_interfaces -clock CORE_CLK -reset CORE_RSTN [ipx::current_core]
ipx::associate_bus_interfaces -clock CMD_AXI_CLK -reset CMD_AXI_RSTN [ipx::current_core]
ipx::associate_bus_interfaces -clock DATA_AXI_CLK -reset DATA_AXI_RSTN [ipx::current_core]


ipx::remove_bus_parameter ASSOCIATED_BUSIF [ipx::get_bus_interfaces CORE_CLK -of_objects [ipx::current_core]]
ipx::associate_bus_interfaces -clock CMD_AXI_CLK -busif CMD_AXI [ipx::current_core]

ipx::add_bus_parameter NUM_READ_OUTSTANDING [ipx::get_bus_interfaces CMD_AXI -of_objects [ipx::current_core]]
ipx::add_bus_parameter NUM_WRITE_OUTSTANDING [ipx::get_bus_interfaces CMD_AXI -of_objects [ipx::current_core]]
ipx::add_bus_parameter MAX_BURST_LENGTH [ipx::get_bus_interfaces CMD_AXI -of_objects [ipx::current_core]]
ipx::add_bus_parameter SUPPORTS_NARROW_BURST [ipx::get_bus_interfaces CMD_AXI -of_objects [ipx::current_core]]

set_property value 2 [ipx::get_bus_parameters NUM_READ_OUTSTANDING -of_objects [ipx::get_bus_interfaces CMD_AXI -of_objects [ipx::current_core]]]
set_property value 2 [ipx::get_bus_parameters NUM_WRITE_OUTSTANDING -of_objects [ipx::get_bus_interfaces CMD_AXI -of_objects [ipx::current_core]]]
set_property value 256 [ipx::get_bus_parameters MAX_BURST_LENGTH -of_objects [ipx::get_bus_interfaces CMD_AXI -of_objects [ipx::current_core]]]
set_property value 0 [ipx::get_bus_parameters SUPPORTS_NARROW_BURST -of_objects [ipx::get_bus_interfaces CMD_AXI -of_objects [ipx::current_core]]]

for {set i 0} {$i < 1} {incr i} {
	set bus [format "DATA_AXI%02s" $i]
	ipx::associate_bus_interfaces -clock DATA_AXI_CLK -busif $bus [ipx::current_core]

	ipx::add_bus_parameter NUM_READ_OUTSTANDING [ipx::get_bus_interfaces $bus -of_objects [ipx::current_core]]
	ipx::add_bus_parameter NUM_WRITE_OUTSTANDING [ipx::get_bus_interfaces $bus -of_objects [ipx::current_core]]
	ipx::add_bus_parameter MAX_BURST_LENGTH [ipx::get_bus_interfaces $bus -of_objects [ipx::current_core]]
	ipx::add_bus_parameter SUPPORTS_NARROW_BURST [ipx::get_bus_interfaces $bus -of_objects [ipx::current_core]]

	set_property value 16 [ipx::get_bus_parameters NUM_READ_OUTSTANDING -of_objects [ipx::get_bus_interfaces $bus -of_objects [ipx::current_core]]]
	set_property value 16 [ipx::get_bus_parameters NUM_WRITE_OUTSTANDING -of_objects [ipx::get_bus_interfaces $bus -of_objects [ipx::current_core]]]
	set_property value 16 [ipx::get_bus_parameters MAX_BURST_LENGTH -of_objects [ipx::get_bus_interfaces $bus -of_objects [ipx::current_core]]]
	set_property value 0 [ipx::get_bus_parameters SUPPORTS_NARROW_BURST -of_objects [ipx::get_bus_interfaces $bus -of_objects [ipx::current_core]]]
}

# End of Actual IP Settings
#####################################

ipx::create_xgui_files [ipx::current_core]
ipx::update_checksums  [ipx::current_core]
ipx::save_core         [ipx::current_core]

