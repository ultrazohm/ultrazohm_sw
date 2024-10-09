# Definitional proc to organize widgets for parameters.
proc init_gui { IPINST } {
  ipgui::add_param $IPINST -name "Component_Name"
  #Adding Page
  set Page_0 [ipgui::add_page $IPINST -name "Page 0"]
  ipgui::add_param $IPINST -name "C_ANSWER_DELAY" -parent ${Page_0}
  ipgui::add_param $IPINST -name "C_CMD_AXI_DATA_WIDTH" -parent ${Page_0}
  ipgui::add_param $IPINST -name "C_DATA_AXI_DATA_WIDTH" -parent ${Page_0}
  ipgui::add_param $IPINST -name "C_DUMMY_LOGIC_FACTOR" -parent ${Page_0}


}

proc update_PARAM_VALUE.C_ANSWER_DELAY { PARAM_VALUE.C_ANSWER_DELAY } {
	# Procedure called to update C_ANSWER_DELAY when any of the dependent parameters in the arguments change
}

proc validate_PARAM_VALUE.C_ANSWER_DELAY { PARAM_VALUE.C_ANSWER_DELAY } {
	# Procedure called to validate C_ANSWER_DELAY
	return true
}

proc update_PARAM_VALUE.C_CMD_AXI_DATA_WIDTH { PARAM_VALUE.C_CMD_AXI_DATA_WIDTH } {
	# Procedure called to update C_CMD_AXI_DATA_WIDTH when any of the dependent parameters in the arguments change
}

proc validate_PARAM_VALUE.C_CMD_AXI_DATA_WIDTH { PARAM_VALUE.C_CMD_AXI_DATA_WIDTH } {
	# Procedure called to validate C_CMD_AXI_DATA_WIDTH
	return true
}

proc update_PARAM_VALUE.C_DATA_AXI_DATA_WIDTH { PARAM_VALUE.C_DATA_AXI_DATA_WIDTH } {
	# Procedure called to update C_DATA_AXI_DATA_WIDTH when any of the dependent parameters in the arguments change
}

proc validate_PARAM_VALUE.C_DATA_AXI_DATA_WIDTH { PARAM_VALUE.C_DATA_AXI_DATA_WIDTH } {
	# Procedure called to validate C_DATA_AXI_DATA_WIDTH
	return true
}

proc update_PARAM_VALUE.C_DUMMY_LOGIC_FACTOR { PARAM_VALUE.C_DUMMY_LOGIC_FACTOR } {
	# Procedure called to update C_DUMMY_LOGIC_FACTOR when any of the dependent parameters in the arguments change
}

proc validate_PARAM_VALUE.C_DUMMY_LOGIC_FACTOR { PARAM_VALUE.C_DUMMY_LOGIC_FACTOR } {
	# Procedure called to validate C_DUMMY_LOGIC_FACTOR
	return true
}


proc update_MODELPARAM_VALUE.C_CMD_AXI_DATA_WIDTH { MODELPARAM_VALUE.C_CMD_AXI_DATA_WIDTH PARAM_VALUE.C_CMD_AXI_DATA_WIDTH } {
	# Procedure called to set VHDL generic/Verilog parameter value(s) based on TCL parameter value
	set_property value [get_property value ${PARAM_VALUE.C_CMD_AXI_DATA_WIDTH}] ${MODELPARAM_VALUE.C_CMD_AXI_DATA_WIDTH}
}

proc update_MODELPARAM_VALUE.C_DATA_AXI_DATA_WIDTH { MODELPARAM_VALUE.C_DATA_AXI_DATA_WIDTH PARAM_VALUE.C_DATA_AXI_DATA_WIDTH } {
	# Procedure called to set VHDL generic/Verilog parameter value(s) based on TCL parameter value
	set_property value [get_property value ${PARAM_VALUE.C_DATA_AXI_DATA_WIDTH}] ${MODELPARAM_VALUE.C_DATA_AXI_DATA_WIDTH}
}

proc update_MODELPARAM_VALUE.C_ANSWER_DELAY { MODELPARAM_VALUE.C_ANSWER_DELAY PARAM_VALUE.C_ANSWER_DELAY } {
	# Procedure called to set VHDL generic/Verilog parameter value(s) based on TCL parameter value
	set_property value [get_property value ${PARAM_VALUE.C_ANSWER_DELAY}] ${MODELPARAM_VALUE.C_ANSWER_DELAY}
}

proc update_MODELPARAM_VALUE.C_DUMMY_LOGIC_FACTOR { MODELPARAM_VALUE.C_DUMMY_LOGIC_FACTOR PARAM_VALUE.C_DUMMY_LOGIC_FACTOR } {
	# Procedure called to set VHDL generic/Verilog parameter value(s) based on TCL parameter value
	set_property value [get_property value ${PARAM_VALUE.C_DUMMY_LOGIC_FACTOR}] ${MODELPARAM_VALUE.C_DUMMY_LOGIC_FACTOR}
}

