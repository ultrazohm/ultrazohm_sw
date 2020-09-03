# Definitional proc to organize widgets for parameters.
proc init_gui { IPINST } {
  ipgui::add_param $IPINST -name "Component_Name"
  #Adding Page
  set Page_0 [ipgui::add_page $IPINST -name "Page 0"]
  set C_S00_AXI_DATA_WIDTH [ipgui::add_param $IPINST -name "C_S00_AXI_DATA_WIDTH" -parent ${Page_0} -widget comboBox]
  set_property tooltip {Width of S_AXI data bus} ${C_S00_AXI_DATA_WIDTH}
  set C_S00_AXI_ADDR_WIDTH [ipgui::add_param $IPINST -name "C_S00_AXI_ADDR_WIDTH" -parent ${Page_0}]
  set_property tooltip {Width of S_AXI address bus} ${C_S00_AXI_ADDR_WIDTH}
  ipgui::add_param $IPINST -name "C_S00_AXI_BASEADDR" -parent ${Page_0}
  ipgui::add_param $IPINST -name "C_S00_AXI_HIGHADDR" -parent ${Page_0}

  ipgui::add_param $IPINST -name "INPUT_CLK_FREQUENCY"
  ipgui::add_param $IPINST -name "PRE_DELAY"
  ipgui::add_param $IPINST -name "SPI_CLK_FREQUENCY"
  ipgui::add_param $IPINST -name "POST_DELAY"
  ipgui::add_param $IPINST -name "CONV_DELAY"
  ipgui::add_param $IPINST -name "W_LENGTH"
  set CONTINUOUS_TRIGGERED_MODE [ipgui::add_param $IPINST -name "CONTINUOUS_TRIGGERED_MODE"]
  set_property tooltip {0: Continuous Mode; 1: Triggered Mode} ${CONTINUOUS_TRIGGERED_MODE}

}

proc update_PARAM_VALUE.CONTINUOUS_TRIGGERED_MODE { PARAM_VALUE.CONTINUOUS_TRIGGERED_MODE } {
	# Procedure called to update CONTINUOUS_TRIGGERED_MODE when any of the dependent parameters in the arguments change
}

proc validate_PARAM_VALUE.CONTINUOUS_TRIGGERED_MODE { PARAM_VALUE.CONTINUOUS_TRIGGERED_MODE } {
	# Procedure called to validate CONTINUOUS_TRIGGERED_MODE
	return true
}

proc update_PARAM_VALUE.CONV_DELAY { PARAM_VALUE.CONV_DELAY } {
	# Procedure called to update CONV_DELAY when any of the dependent parameters in the arguments change
}

proc validate_PARAM_VALUE.CONV_DELAY { PARAM_VALUE.CONV_DELAY } {
	# Procedure called to validate CONV_DELAY
	return true
}

proc update_PARAM_VALUE.INPUT_CLK_FREQUENCY { PARAM_VALUE.INPUT_CLK_FREQUENCY } {
	# Procedure called to update INPUT_CLK_FREQUENCY when any of the dependent parameters in the arguments change
}

proc validate_PARAM_VALUE.INPUT_CLK_FREQUENCY { PARAM_VALUE.INPUT_CLK_FREQUENCY } {
	# Procedure called to validate INPUT_CLK_FREQUENCY
	return true
}


proc update_PARAM_VALUE.POST_DELAY { PARAM_VALUE.POST_DELAY } {
	# Procedure called to update POST_DELAY when any of the dependent parameters in the arguments change
}

proc validate_PARAM_VALUE.POST_DELAY { PARAM_VALUE.POST_DELAY } {
	# Procedure called to validate POST_DELAY
	return true
}

proc update_PARAM_VALUE.PRE_DELAY { PARAM_VALUE.PRE_DELAY } {
	# Procedure called to update PRE_DELAY when any of the dependent parameters in the arguments change
}

proc validate_PARAM_VALUE.PRE_DELAY { PARAM_VALUE.PRE_DELAY } {
	# Procedure called to validate PRE_DELAY
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

proc update_PARAM_VALUE.C_S00_AXI_DATA_WIDTH { PARAM_VALUE.C_S00_AXI_DATA_WIDTH } {
	# Procedure called to update C_S00_AXI_DATA_WIDTH when any of the dependent parameters in the arguments change
}

proc validate_PARAM_VALUE.C_S00_AXI_DATA_WIDTH { PARAM_VALUE.C_S00_AXI_DATA_WIDTH } {
	# Procedure called to validate C_S00_AXI_DATA_WIDTH
	return true
}

proc update_PARAM_VALUE.C_S00_AXI_ADDR_WIDTH { PARAM_VALUE.C_S00_AXI_ADDR_WIDTH } {
	# Procedure called to update C_S00_AXI_ADDR_WIDTH when any of the dependent parameters in the arguments change
}

proc validate_PARAM_VALUE.C_S00_AXI_ADDR_WIDTH { PARAM_VALUE.C_S00_AXI_ADDR_WIDTH } {
	# Procedure called to validate C_S00_AXI_ADDR_WIDTH
	return true
}

proc update_PARAM_VALUE.C_S00_AXI_BASEADDR { PARAM_VALUE.C_S00_AXI_BASEADDR } {
	# Procedure called to update C_S00_AXI_BASEADDR when any of the dependent parameters in the arguments change
}

proc validate_PARAM_VALUE.C_S00_AXI_BASEADDR { PARAM_VALUE.C_S00_AXI_BASEADDR } {
	# Procedure called to validate C_S00_AXI_BASEADDR
	return true
}

proc update_PARAM_VALUE.C_S00_AXI_HIGHADDR { PARAM_VALUE.C_S00_AXI_HIGHADDR } {
	# Procedure called to update C_S00_AXI_HIGHADDR when any of the dependent parameters in the arguments change
}

proc validate_PARAM_VALUE.C_S00_AXI_HIGHADDR { PARAM_VALUE.C_S00_AXI_HIGHADDR } {
	# Procedure called to validate C_S00_AXI_HIGHADDR
	return true
}


proc update_MODELPARAM_VALUE.C_S00_AXI_DATA_WIDTH { MODELPARAM_VALUE.C_S00_AXI_DATA_WIDTH PARAM_VALUE.C_S00_AXI_DATA_WIDTH } {
	# Procedure called to set VHDL generic/Verilog parameter value(s) based on TCL parameter value
	set_property value [get_property value ${PARAM_VALUE.C_S00_AXI_DATA_WIDTH}] ${MODELPARAM_VALUE.C_S00_AXI_DATA_WIDTH}
}

proc update_MODELPARAM_VALUE.C_S00_AXI_ADDR_WIDTH { MODELPARAM_VALUE.C_S00_AXI_ADDR_WIDTH PARAM_VALUE.C_S00_AXI_ADDR_WIDTH } {
	# Procedure called to set VHDL generic/Verilog parameter value(s) based on TCL parameter value
	set_property value [get_property value ${PARAM_VALUE.C_S00_AXI_ADDR_WIDTH}] ${MODELPARAM_VALUE.C_S00_AXI_ADDR_WIDTH}
}

proc update_MODELPARAM_VALUE.INPUT_CLK_FREQUENCY { MODELPARAM_VALUE.INPUT_CLK_FREQUENCY PARAM_VALUE.INPUT_CLK_FREQUENCY } {
	# Procedure called to set VHDL generic/Verilog parameter value(s) based on TCL parameter value
	set_property value [get_property value ${PARAM_VALUE.INPUT_CLK_FREQUENCY}] ${MODELPARAM_VALUE.INPUT_CLK_FREQUENCY}
}

proc update_MODELPARAM_VALUE.SPI_CLK_FREQUENCY { MODELPARAM_VALUE.SPI_CLK_FREQUENCY PARAM_VALUE.SPI_CLK_FREQUENCY } {
	# Procedure called to set VHDL generic/Verilog parameter value(s) based on TCL parameter value
	set_property value [get_property value ${PARAM_VALUE.SPI_CLK_FREQUENCY}] ${MODELPARAM_VALUE.SPI_CLK_FREQUENCY}
}

proc update_MODELPARAM_VALUE.PRE_DELAY { MODELPARAM_VALUE.PRE_DELAY PARAM_VALUE.PRE_DELAY } {
	# Procedure called to set VHDL generic/Verilog parameter value(s) based on TCL parameter value
	set_property value [get_property value ${PARAM_VALUE.PRE_DELAY}] ${MODELPARAM_VALUE.PRE_DELAY}
}

proc update_MODELPARAM_VALUE.POST_DELAY { MODELPARAM_VALUE.POST_DELAY PARAM_VALUE.POST_DELAY } {
	# Procedure called to set VHDL generic/Verilog parameter value(s) based on TCL parameter value
	set_property value [get_property value ${PARAM_VALUE.POST_DELAY}] ${MODELPARAM_VALUE.POST_DELAY}
}

proc update_MODELPARAM_VALUE.CONV_DELAY { MODELPARAM_VALUE.CONV_DELAY PARAM_VALUE.CONV_DELAY } {
	# Procedure called to set VHDL generic/Verilog parameter value(s) based on TCL parameter value
	set_property value [get_property value ${PARAM_VALUE.CONV_DELAY}] ${MODELPARAM_VALUE.CONV_DELAY}
}

proc update_MODELPARAM_VALUE.W_LENGTH { MODELPARAM_VALUE.W_LENGTH PARAM_VALUE.W_LENGTH } {
	# Procedure called to set VHDL generic/Verilog parameter value(s) based on TCL parameter value
	set_property value [get_property value ${PARAM_VALUE.W_LENGTH}] ${MODELPARAM_VALUE.W_LENGTH}
}

proc update_MODELPARAM_VALUE.CONTINUOUS_TRIGGERED_MODE { MODELPARAM_VALUE.CONTINUOUS_TRIGGERED_MODE PARAM_VALUE.CONTINUOUS_TRIGGERED_MODE } {
	# Procedure called to set VHDL generic/Verilog parameter value(s) based on TCL parameter value
	set_property value [get_property value ${PARAM_VALUE.CONTINUOUS_TRIGGERED_MODE}] ${MODELPARAM_VALUE.CONTINUOUS_TRIGGERED_MODE}
}

