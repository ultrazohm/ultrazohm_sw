# Definitional proc to organize widgets for parameters.
proc init_gui { IPINST } {
  ipgui::add_param $IPINST -name "Component_Name"
  #Adding Page
  set Page_0 [ipgui::add_page $IPINST -name "Page 0"]
  ipgui::add_param $IPINST -name "CONVERSION_RATE_ADC" -parent ${Page_0}
  ipgui::add_param $IPINST -name "C_S00_AXI_ADDR_WIDTH" -parent ${Page_0}
  ipgui::add_param $IPINST -name "C_S00_AXI_DATA_WIDTH" -parent ${Page_0}
  ipgui::add_param $IPINST -name "INPUT_CLK_FREQUENCY" -parent ${Page_0}
  ipgui::add_param $IPINST -name "Number_of_ADCs" -parent ${Page_0}
  ipgui::add_param $IPINST -name "SPI_CLK_FREQUENCY" -parent ${Page_0}
  ipgui::add_param $IPINST -name "W_LENGTH" -parent ${Page_0}


}

proc update_PARAM_VALUE.CONVERSION_RATE_ADC { PARAM_VALUE.CONVERSION_RATE_ADC } {
	# Procedure called to update CONVERSION_RATE_ADC when any of the dependent parameters in the arguments change
}

proc validate_PARAM_VALUE.CONVERSION_RATE_ADC { PARAM_VALUE.CONVERSION_RATE_ADC } {
	# Procedure called to validate CONVERSION_RATE_ADC
	return true
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

proc update_PARAM_VALUE.INPUT_CLK_FREQUENCY { PARAM_VALUE.INPUT_CLK_FREQUENCY } {
	# Procedure called to update INPUT_CLK_FREQUENCY when any of the dependent parameters in the arguments change
}

proc validate_PARAM_VALUE.INPUT_CLK_FREQUENCY { PARAM_VALUE.INPUT_CLK_FREQUENCY } {
	# Procedure called to validate INPUT_CLK_FREQUENCY
	return true
}

proc update_PARAM_VALUE.Number_of_ADCs { PARAM_VALUE.Number_of_ADCs } {
	# Procedure called to update Number_of_ADCs when any of the dependent parameters in the arguments change
}

proc validate_PARAM_VALUE.Number_of_ADCs { PARAM_VALUE.Number_of_ADCs } {
	# Procedure called to validate Number_of_ADCs
	return true
}

proc update_PARAM_VALUE.SPI_CLK_FREQUENCY { PARAM_VALUE.SPI_CLK_FREQUENCY } {
	# Procedure called to update SPI_CLK_FREQUENCY when any of the dependent parameters in the arguments change
}

proc validate_PARAM_VALUE.SPI_CLK_FREQUENCY { PARAM_VALUE.SPI_CLK_FREQUENCY } {
	# Procedure called to validate SPI_CLK_FREQUENCY
	return true
}

proc update_PARAM_VALUE.W_LENGTH { PARAM_VALUE.W_LENGTH } {
	# Procedure called to update W_LENGTH when any of the dependent parameters in the arguments change
}

proc validate_PARAM_VALUE.W_LENGTH { PARAM_VALUE.W_LENGTH } {
	# Procedure called to validate W_LENGTH
	return true
}


proc update_MODELPARAM_VALUE.Number_of_ADCs { MODELPARAM_VALUE.Number_of_ADCs PARAM_VALUE.Number_of_ADCs } {
	# Procedure called to set VHDL generic/Verilog parameter value(s) based on TCL parameter value
	set_property value [get_property value ${PARAM_VALUE.Number_of_ADCs}] ${MODELPARAM_VALUE.Number_of_ADCs}
}

proc update_MODELPARAM_VALUE.INPUT_CLK_FREQUENCY { MODELPARAM_VALUE.INPUT_CLK_FREQUENCY PARAM_VALUE.INPUT_CLK_FREQUENCY } {
	# Procedure called to set VHDL generic/Verilog parameter value(s) based on TCL parameter value
	set_property value [get_property value ${PARAM_VALUE.INPUT_CLK_FREQUENCY}] ${MODELPARAM_VALUE.INPUT_CLK_FREQUENCY}
}

proc update_MODELPARAM_VALUE.SPI_CLK_FREQUENCY { MODELPARAM_VALUE.SPI_CLK_FREQUENCY PARAM_VALUE.SPI_CLK_FREQUENCY } {
	# Procedure called to set VHDL generic/Verilog parameter value(s) based on TCL parameter value
	set_property value [get_property value ${PARAM_VALUE.SPI_CLK_FREQUENCY}] ${MODELPARAM_VALUE.SPI_CLK_FREQUENCY}
}

proc update_MODELPARAM_VALUE.W_LENGTH { MODELPARAM_VALUE.W_LENGTH PARAM_VALUE.W_LENGTH } {
	# Procedure called to set VHDL generic/Verilog parameter value(s) based on TCL parameter value
	set_property value [get_property value ${PARAM_VALUE.W_LENGTH}] ${MODELPARAM_VALUE.W_LENGTH}
}

proc update_MODELPARAM_VALUE.CONVERSION_RATE_ADC { MODELPARAM_VALUE.CONVERSION_RATE_ADC PARAM_VALUE.CONVERSION_RATE_ADC } {
	# Procedure called to set VHDL generic/Verilog parameter value(s) based on TCL parameter value
	set_property value [get_property value ${PARAM_VALUE.CONVERSION_RATE_ADC}] ${MODELPARAM_VALUE.CONVERSION_RATE_ADC}
}

proc update_MODELPARAM_VALUE.C_S00_AXI_DATA_WIDTH { MODELPARAM_VALUE.C_S00_AXI_DATA_WIDTH PARAM_VALUE.C_S00_AXI_DATA_WIDTH } {
	# Procedure called to set VHDL generic/Verilog parameter value(s) based on TCL parameter value
	set_property value [get_property value ${PARAM_VALUE.C_S00_AXI_DATA_WIDTH}] ${MODELPARAM_VALUE.C_S00_AXI_DATA_WIDTH}
}

proc update_MODELPARAM_VALUE.C_S00_AXI_ADDR_WIDTH { MODELPARAM_VALUE.C_S00_AXI_ADDR_WIDTH PARAM_VALUE.C_S00_AXI_ADDR_WIDTH } {
	# Procedure called to set VHDL generic/Verilog parameter value(s) based on TCL parameter value
	set_property value [get_property value ${PARAM_VALUE.C_S00_AXI_ADDR_WIDTH}] ${MODELPARAM_VALUE.C_S00_AXI_ADDR_WIDTH}
}

