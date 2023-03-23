# Definitional proc to organize widgets for parameters.
proc init_gui { IPINST } {
  ipgui::add_param $IPINST -name "Component_Name"
  #Adding Page
  set Page_0 [ipgui::add_page $IPINST -name "Page 0"]
  #Adding Group
  set enable_FPGA_Pots [ipgui::add_group $IPINST -name "enable_FPGA_Pots" -parent ${Page_0} -display_name {enable_FPGA_Pots}]
  ipgui::add_static_text $IPINST -name "Enable_FPGA_Ports" -parent ${enable_FPGA_Pots} -text {Enables or Disables ports to get the temperature values inside the FPGA}
  ipgui::add_param $IPINST -name "enable_FPGA_Ports" -parent ${enable_FPGA_Pots}



}

proc update_PARAM_VALUE.C_S00_AXI_ADDR_WIDTH { PARAM_VALUE.C_S00_AXI_ADDR_WIDTH } {
	# Procedure called to update C_S00_AXI_ADDR_WIDTH when any of the dependent parameters in the arguments change
}

proc validate_PARAM_VALUE.C_S00_AXI_ADDR_WIDTH { PARAM_VALUE.C_S00_AXI_ADDR_WIDTH } {
	# Procedure called to validate C_S00_AXI_ADDR_WIDTH
	return true
}

proc update_PARAM_VALUE.C_S00_AXI_DATA_WIDTH { PARAM_VALUE.C_S00_AXI_DATA_WIDTH } {
	# Procedure called to update C_S00_AXI_DATA_WIDTH when any of the dependent parameters in the arguments change
}

proc validate_PARAM_VALUE.C_S00_AXI_DATA_WIDTH { PARAM_VALUE.C_S00_AXI_DATA_WIDTH } {
	# Procedure called to validate C_S00_AXI_DATA_WIDTH
	return true
}

proc update_PARAM_VALUE.SPI_clk_div { PARAM_VALUE.SPI_clk_div } {
	# Procedure called to update SPI_clk_div when any of the dependent parameters in the arguments change
}

proc validate_PARAM_VALUE.SPI_clk_div { PARAM_VALUE.SPI_clk_div } {
	# Procedure called to validate SPI_clk_div
	return true
}

proc update_PARAM_VALUE.enable_FPGA_Ports { PARAM_VALUE.enable_FPGA_Ports } {
	# Procedure called to update enable_FPGA_Ports when any of the dependent parameters in the arguments change
}

proc validate_PARAM_VALUE.enable_FPGA_Ports { PARAM_VALUE.enable_FPGA_Ports } {
	# Procedure called to validate enable_FPGA_Ports
	return true
}


proc update_MODELPARAM_VALUE.SPI_clk_div { MODELPARAM_VALUE.SPI_clk_div PARAM_VALUE.SPI_clk_div } {
	# Procedure called to set VHDL generic/Verilog parameter value(s) based on TCL parameter value
	set_property value [get_property value ${PARAM_VALUE.SPI_clk_div}] ${MODELPARAM_VALUE.SPI_clk_div}
}

proc update_MODELPARAM_VALUE.C_S00_AXI_DATA_WIDTH { MODELPARAM_VALUE.C_S00_AXI_DATA_WIDTH PARAM_VALUE.C_S00_AXI_DATA_WIDTH } {
	# Procedure called to set VHDL generic/Verilog parameter value(s) based on TCL parameter value
	set_property value [get_property value ${PARAM_VALUE.C_S00_AXI_DATA_WIDTH}] ${MODELPARAM_VALUE.C_S00_AXI_DATA_WIDTH}
}

proc update_MODELPARAM_VALUE.C_S00_AXI_ADDR_WIDTH { MODELPARAM_VALUE.C_S00_AXI_ADDR_WIDTH PARAM_VALUE.C_S00_AXI_ADDR_WIDTH } {
	# Procedure called to set VHDL generic/Verilog parameter value(s) based on TCL parameter value
	set_property value [get_property value ${PARAM_VALUE.C_S00_AXI_ADDR_WIDTH}] ${MODELPARAM_VALUE.C_S00_AXI_ADDR_WIDTH}
}

