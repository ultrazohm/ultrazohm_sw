# Definitional proc to organize widgets for parameters.
proc init_gui { IPINST } {
  ipgui::add_param $IPINST -name "Component_Name"
  #Adding Page
  set Page_0 [ipgui::add_page $IPINST -name "Page 0"]
  ipgui::add_param $IPINST -name "C_S_AXI_Lite_ADDR_WIDTH" -parent ${Page_0}
  ipgui::add_param $IPINST -name "C_S_AXI_Lite_DATA_WIDTH" -parent ${Page_0}
  ipgui::add_param $IPINST -name "DEBUG_MESSAGE_INCLUDED" -parent ${Page_0}
  ipgui::add_param $IPINST -name "DIFFERENTIAL_SAMPLING" -parent ${Page_0}
  ipgui::add_param $IPINST -name "NUMBER_OF_ADCS" -parent ${Page_0}
  ipgui::add_param $IPINST -name "OUTPUT_WORD_WIDTH" -parent ${Page_0}
  ipgui::add_param $IPINST -name "SIMULATION_DEBUG" -parent ${Page_0}


}

proc update_PARAM_VALUE.C_S_AXI_Lite_ADDR_WIDTH { PARAM_VALUE.C_S_AXI_Lite_ADDR_WIDTH } {
	# Procedure called to update C_S_AXI_Lite_ADDR_WIDTH when any of the dependent parameters in the arguments change
}

proc validate_PARAM_VALUE.C_S_AXI_Lite_ADDR_WIDTH { PARAM_VALUE.C_S_AXI_Lite_ADDR_WIDTH } {
	# Procedure called to validate C_S_AXI_Lite_ADDR_WIDTH
	return true
}

proc update_PARAM_VALUE.C_S_AXI_Lite_DATA_WIDTH { PARAM_VALUE.C_S_AXI_Lite_DATA_WIDTH } {
	# Procedure called to update C_S_AXI_Lite_DATA_WIDTH when any of the dependent parameters in the arguments change
}

proc validate_PARAM_VALUE.C_S_AXI_Lite_DATA_WIDTH { PARAM_VALUE.C_S_AXI_Lite_DATA_WIDTH } {
	# Procedure called to validate C_S_AXI_Lite_DATA_WIDTH
	return true
}

proc update_PARAM_VALUE.DEBUG_MESSAGE_INCLUDED { PARAM_VALUE.DEBUG_MESSAGE_INCLUDED } {
	# Procedure called to update DEBUG_MESSAGE_INCLUDED when any of the dependent parameters in the arguments change
}

proc validate_PARAM_VALUE.DEBUG_MESSAGE_INCLUDED { PARAM_VALUE.DEBUG_MESSAGE_INCLUDED } {
	# Procedure called to validate DEBUG_MESSAGE_INCLUDED
	return true
}

proc update_PARAM_VALUE.DIFFERENTIAL_SAMPLING { PARAM_VALUE.DIFFERENTIAL_SAMPLING } {
	# Procedure called to update DIFFERENTIAL_SAMPLING when any of the dependent parameters in the arguments change
}

proc validate_PARAM_VALUE.DIFFERENTIAL_SAMPLING { PARAM_VALUE.DIFFERENTIAL_SAMPLING } {
	# Procedure called to validate DIFFERENTIAL_SAMPLING
	return true
}

proc update_PARAM_VALUE.NUMBER_OF_ADCS { PARAM_VALUE.NUMBER_OF_ADCS } {
	# Procedure called to update NUMBER_OF_ADCS when any of the dependent parameters in the arguments change
}

proc validate_PARAM_VALUE.NUMBER_OF_ADCS { PARAM_VALUE.NUMBER_OF_ADCS } {
	# Procedure called to validate NUMBER_OF_ADCS
	return true
}

proc update_PARAM_VALUE.OUTPUT_WORD_WIDTH { PARAM_VALUE.OUTPUT_WORD_WIDTH } {
	# Procedure called to update OUTPUT_WORD_WIDTH when any of the dependent parameters in the arguments change
}

proc validate_PARAM_VALUE.OUTPUT_WORD_WIDTH { PARAM_VALUE.OUTPUT_WORD_WIDTH } {
	# Procedure called to validate OUTPUT_WORD_WIDTH
	return true
}

proc update_PARAM_VALUE.SIMULATION_DEBUG { PARAM_VALUE.SIMULATION_DEBUG } {
	# Procedure called to update SIMULATION_DEBUG when any of the dependent parameters in the arguments change
}

proc validate_PARAM_VALUE.SIMULATION_DEBUG { PARAM_VALUE.SIMULATION_DEBUG } {
	# Procedure called to validate SIMULATION_DEBUG
	return true
}


proc update_MODELPARAM_VALUE.OUTPUT_WORD_WIDTH { MODELPARAM_VALUE.OUTPUT_WORD_WIDTH PARAM_VALUE.OUTPUT_WORD_WIDTH } {
	# Procedure called to set VHDL generic/Verilog parameter value(s) based on TCL parameter value
	set_property value [get_property value ${PARAM_VALUE.OUTPUT_WORD_WIDTH}] ${MODELPARAM_VALUE.OUTPUT_WORD_WIDTH}
}

proc update_MODELPARAM_VALUE.NUMBER_OF_ADCS { MODELPARAM_VALUE.NUMBER_OF_ADCS PARAM_VALUE.NUMBER_OF_ADCS } {
	# Procedure called to set VHDL generic/Verilog parameter value(s) based on TCL parameter value
	set_property value [get_property value ${PARAM_VALUE.NUMBER_OF_ADCS}] ${MODELPARAM_VALUE.NUMBER_OF_ADCS}
}

proc update_MODELPARAM_VALUE.DIFFERENTIAL_SAMPLING { MODELPARAM_VALUE.DIFFERENTIAL_SAMPLING PARAM_VALUE.DIFFERENTIAL_SAMPLING } {
	# Procedure called to set VHDL generic/Verilog parameter value(s) based on TCL parameter value
	set_property value [get_property value ${PARAM_VALUE.DIFFERENTIAL_SAMPLING}] ${MODELPARAM_VALUE.DIFFERENTIAL_SAMPLING}
}

proc update_MODELPARAM_VALUE.DEBUG_MESSAGE_INCLUDED { MODELPARAM_VALUE.DEBUG_MESSAGE_INCLUDED PARAM_VALUE.DEBUG_MESSAGE_INCLUDED } {
	# Procedure called to set VHDL generic/Verilog parameter value(s) based on TCL parameter value
	set_property value [get_property value ${PARAM_VALUE.DEBUG_MESSAGE_INCLUDED}] ${MODELPARAM_VALUE.DEBUG_MESSAGE_INCLUDED}
}

proc update_MODELPARAM_VALUE.SIMULATION_DEBUG { MODELPARAM_VALUE.SIMULATION_DEBUG PARAM_VALUE.SIMULATION_DEBUG } {
	# Procedure called to set VHDL generic/Verilog parameter value(s) based on TCL parameter value
	set_property value [get_property value ${PARAM_VALUE.SIMULATION_DEBUG}] ${MODELPARAM_VALUE.SIMULATION_DEBUG}
}

proc update_MODELPARAM_VALUE.C_S_AXI_Lite_DATA_WIDTH { MODELPARAM_VALUE.C_S_AXI_Lite_DATA_WIDTH PARAM_VALUE.C_S_AXI_Lite_DATA_WIDTH } {
	# Procedure called to set VHDL generic/Verilog parameter value(s) based on TCL parameter value
	set_property value [get_property value ${PARAM_VALUE.C_S_AXI_Lite_DATA_WIDTH}] ${MODELPARAM_VALUE.C_S_AXI_Lite_DATA_WIDTH}
}

proc update_MODELPARAM_VALUE.C_S_AXI_Lite_ADDR_WIDTH { MODELPARAM_VALUE.C_S_AXI_Lite_ADDR_WIDTH PARAM_VALUE.C_S_AXI_Lite_ADDR_WIDTH } {
	# Procedure called to set VHDL generic/Verilog parameter value(s) based on TCL parameter value
	set_property value [get_property value ${PARAM_VALUE.C_S_AXI_Lite_ADDR_WIDTH}] ${MODELPARAM_VALUE.C_S_AXI_Lite_ADDR_WIDTH}
}

