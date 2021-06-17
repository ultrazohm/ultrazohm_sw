# Definitional proc to organize widgets for parameters.
proc init_gui { IPINST } {
  ipgui::add_param $IPINST -name "Component_Name"
  #Adding Page
  set Page_0 [ipgui::add_page $IPINST -name "Page 0"]
  ipgui::add_param $IPINST -name "clk_div" -parent ${Page_0}
  ipgui::add_param $IPINST -name "OUTPUT_WORD_WIDTH" -parent ${Page_0} -widget comboBox
  ipgui::add_param $IPINST -name "full_ch_mode" -parent ${Page_0}


}

proc update_PARAM_VALUE.OUTPUT_WORD_WIDTH { PARAM_VALUE.OUTPUT_WORD_WIDTH } {
	# Procedure called to update OUTPUT_WORD_WIDTH when any of the dependent parameters in the arguments change
}

proc validate_PARAM_VALUE.OUTPUT_WORD_WIDTH { PARAM_VALUE.OUTPUT_WORD_WIDTH } {
	# Procedure called to validate OUTPUT_WORD_WIDTH
	return true
}

proc update_PARAM_VALUE.clk_div { PARAM_VALUE.clk_div } {
	# Procedure called to update clk_div when any of the dependent parameters in the arguments change
}

proc validate_PARAM_VALUE.clk_div { PARAM_VALUE.clk_div } {
	# Procedure called to validate clk_div
	return true
}

proc update_PARAM_VALUE.full_ch_mode { PARAM_VALUE.full_ch_mode } {
	# Procedure called to update full_ch_mode when any of the dependent parameters in the arguments change
}

proc validate_PARAM_VALUE.full_ch_mode { PARAM_VALUE.full_ch_mode } {
	# Procedure called to validate full_ch_mode
	return true
}

proc update_PARAM_VALUE.C_S0_AXI_Lite_DATA_WIDTH { PARAM_VALUE.C_S0_AXI_Lite_DATA_WIDTH } {
	# Procedure called to update C_S0_AXI_Lite_DATA_WIDTH when any of the dependent parameters in the arguments change
}

proc validate_PARAM_VALUE.C_S0_AXI_Lite_DATA_WIDTH { PARAM_VALUE.C_S0_AXI_Lite_DATA_WIDTH } {
	# Procedure called to validate C_S0_AXI_Lite_DATA_WIDTH
	return true
}

proc update_PARAM_VALUE.C_S0_AXI_Lite_ADDR_WIDTH { PARAM_VALUE.C_S0_AXI_Lite_ADDR_WIDTH } {
	# Procedure called to update C_S0_AXI_Lite_ADDR_WIDTH when any of the dependent parameters in the arguments change
}

proc validate_PARAM_VALUE.C_S0_AXI_Lite_ADDR_WIDTH { PARAM_VALUE.C_S0_AXI_Lite_ADDR_WIDTH } {
	# Procedure called to validate C_S0_AXI_Lite_ADDR_WIDTH
	return true
}

proc update_PARAM_VALUE.C_S0_AXI_Lite_BASEADDR { PARAM_VALUE.C_S0_AXI_Lite_BASEADDR } {
	# Procedure called to update C_S0_AXI_Lite_BASEADDR when any of the dependent parameters in the arguments change
}

proc validate_PARAM_VALUE.C_S0_AXI_Lite_BASEADDR { PARAM_VALUE.C_S0_AXI_Lite_BASEADDR } {
	# Procedure called to validate C_S0_AXI_Lite_BASEADDR
	return true
}

proc update_PARAM_VALUE.C_S0_AXI_Lite_HIGHADDR { PARAM_VALUE.C_S0_AXI_Lite_HIGHADDR } {
	# Procedure called to update C_S0_AXI_Lite_HIGHADDR when any of the dependent parameters in the arguments change
}

proc validate_PARAM_VALUE.C_S0_AXI_Lite_HIGHADDR { PARAM_VALUE.C_S0_AXI_Lite_HIGHADDR } {
	# Procedure called to validate C_S0_AXI_Lite_HIGHADDR
	return true
}


proc update_MODELPARAM_VALUE.C_S0_AXI_Lite_DATA_WIDTH { MODELPARAM_VALUE.C_S0_AXI_Lite_DATA_WIDTH PARAM_VALUE.C_S0_AXI_Lite_DATA_WIDTH } {
	# Procedure called to set VHDL generic/Verilog parameter value(s) based on TCL parameter value
	set_property value [get_property value ${PARAM_VALUE.C_S0_AXI_Lite_DATA_WIDTH}] ${MODELPARAM_VALUE.C_S0_AXI_Lite_DATA_WIDTH}
}

proc update_MODELPARAM_VALUE.C_S0_AXI_Lite_ADDR_WIDTH { MODELPARAM_VALUE.C_S0_AXI_Lite_ADDR_WIDTH PARAM_VALUE.C_S0_AXI_Lite_ADDR_WIDTH } {
	# Procedure called to set VHDL generic/Verilog parameter value(s) based on TCL parameter value
	set_property value [get_property value ${PARAM_VALUE.C_S0_AXI_Lite_ADDR_WIDTH}] ${MODELPARAM_VALUE.C_S0_AXI_Lite_ADDR_WIDTH}
}

proc update_MODELPARAM_VALUE.clk_div { MODELPARAM_VALUE.clk_div PARAM_VALUE.clk_div } {
	# Procedure called to set VHDL generic/Verilog parameter value(s) based on TCL parameter value
	set_property value [get_property value ${PARAM_VALUE.clk_div}] ${MODELPARAM_VALUE.clk_div}
}

proc update_MODELPARAM_VALUE.OUTPUT_WORD_WIDTH { MODELPARAM_VALUE.OUTPUT_WORD_WIDTH PARAM_VALUE.OUTPUT_WORD_WIDTH } {
	# Procedure called to set VHDL generic/Verilog parameter value(s) based on TCL parameter value
	set_property value [get_property value ${PARAM_VALUE.OUTPUT_WORD_WIDTH}] ${MODELPARAM_VALUE.OUTPUT_WORD_WIDTH}
}

proc update_MODELPARAM_VALUE.full_ch_mode { MODELPARAM_VALUE.full_ch_mode PARAM_VALUE.full_ch_mode } {
	# Procedure called to set VHDL generic/Verilog parameter value(s) based on TCL parameter value
	set_property value [get_property value ${PARAM_VALUE.full_ch_mode}] ${MODELPARAM_VALUE.full_ch_mode}
}

