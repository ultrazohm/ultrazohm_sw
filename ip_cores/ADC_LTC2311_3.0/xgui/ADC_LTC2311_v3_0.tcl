# Definitional proc to organize widgets for parameters.
proc init_gui { IPINST } {
  ipgui::add_param $IPINST -name "Component_Name"
  set DATA_WIDTH [ipgui::add_param $IPINST -name "DATA_WIDTH"]
  set_property tooltip {Width of the result output by the ADC} ${DATA_WIDTH}
  set CHANNELS_PER_MASTER [ipgui::add_param $IPINST -name "CHANNELS_PER_MASTER"]
  set_property tooltip {Number of synchronously controlled ADCs per SPI Master} ${CHANNELS_PER_MASTER}
  set SPI_MASTER [ipgui::add_param $IPINST -name "SPI_MASTER"]
  set_property tooltip {Number of individual SPI Masters} ${SPI_MASTER}
  set OFFSET_WIDTH [ipgui::add_param $IPINST -name "OFFSET_WIDTH"]
  set_property tooltip {Bit width of the offset added to the raw ADC value. Must be less or equal to the data width from the ADC} ${OFFSET_WIDTH}
  set CONVERSION_WIDTH [ipgui::add_param $IPINST -name "CONVERSION_WIDTH"]
  set_property tooltip {Width of the factor, the ADC result is multiplied with} ${CONVERSION_WIDTH}
  set RES_LSB [ipgui::add_param $IPINST -name "RES_LSB"]
  set_property tooltip {LSB of the result from the multiplier that is shown at the SI_VALUE port} ${RES_LSB}
  set RES_MSB [ipgui::add_param $IPINST -name "RES_MSB"]
  set_property tooltip {LSB of the result from the multiplier that is shown at the SI_VALUE port} ${RES_MSB}
  set DIFFERENTIAL [ipgui::add_param $IPINST -name "DIFFERENTIAL"]
  set_property tooltip {If true, the differential interface for SCLK and MISO is used} ${DIFFERENTIAL}
  #Adding Page
  set AXI4_Lite_Addresses [ipgui::add_page $IPINST -name "AXI4 Lite Addresses"]
  set_property tooltip {Set the high address and the base address here} ${AXI4_Lite_Addresses}
  ipgui::add_param $IPINST -name "C_S00_AXI_BASEADDR" -parent ${AXI4_Lite_Addresses}
  ipgui::add_param $IPINST -name "C_S00_AXI_HIGHADDR" -parent ${AXI4_Lite_Addresses}


}

proc update_PARAM_VALUE.CHANNELS_PER_MASTER { PARAM_VALUE.CHANNELS_PER_MASTER } {
	# Procedure called to update CHANNELS_PER_MASTER when any of the dependent parameters in the arguments change
}

proc validate_PARAM_VALUE.CHANNELS_PER_MASTER { PARAM_VALUE.CHANNELS_PER_MASTER } {
	# Procedure called to validate CHANNELS_PER_MASTER
	return true
}

proc update_PARAM_VALUE.CONVERSION_WIDTH { PARAM_VALUE.CONVERSION_WIDTH } {
	# Procedure called to update CONVERSION_WIDTH when any of the dependent parameters in the arguments change
}

proc validate_PARAM_VALUE.CONVERSION_WIDTH { PARAM_VALUE.CONVERSION_WIDTH } {
	# Procedure called to validate CONVERSION_WIDTH
	return true
}

proc update_PARAM_VALUE.DATA_WIDTH { PARAM_VALUE.DATA_WIDTH } {
	# Procedure called to update DATA_WIDTH when any of the dependent parameters in the arguments change
}

proc validate_PARAM_VALUE.DATA_WIDTH { PARAM_VALUE.DATA_WIDTH } {
	# Procedure called to validate DATA_WIDTH
	return true
}

proc update_PARAM_VALUE.DIFFERENTIAL { PARAM_VALUE.DIFFERENTIAL } {
	# Procedure called to update DIFFERENTIAL when any of the dependent parameters in the arguments change
}

proc validate_PARAM_VALUE.DIFFERENTIAL { PARAM_VALUE.DIFFERENTIAL } {
	# Procedure called to validate DIFFERENTIAL
	return true
}

proc update_PARAM_VALUE.OFFSET_WIDTH { PARAM_VALUE.OFFSET_WIDTH } {
	# Procedure called to update OFFSET_WIDTH when any of the dependent parameters in the arguments change
}

proc validate_PARAM_VALUE.OFFSET_WIDTH { PARAM_VALUE.OFFSET_WIDTH } {
	# Procedure called to validate OFFSET_WIDTH
	return true
}

proc update_PARAM_VALUE.RES_LSB { PARAM_VALUE.RES_LSB } {
	# Procedure called to update RES_LSB when any of the dependent parameters in the arguments change
}

proc validate_PARAM_VALUE.RES_LSB { PARAM_VALUE.RES_LSB } {
	# Procedure called to validate RES_LSB
	return true
}

proc update_PARAM_VALUE.RES_MSB { PARAM_VALUE.RES_MSB } {
	# Procedure called to update RES_MSB when any of the dependent parameters in the arguments change
}

proc validate_PARAM_VALUE.RES_MSB { PARAM_VALUE.RES_MSB } {
	# Procedure called to validate RES_MSB
	return true
}

proc update_PARAM_VALUE.SPI_MASTER { PARAM_VALUE.SPI_MASTER } {
	# Procedure called to update SPI_MASTER when any of the dependent parameters in the arguments change
}

proc validate_PARAM_VALUE.SPI_MASTER { PARAM_VALUE.SPI_MASTER } {
	# Procedure called to validate SPI_MASTER
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


proc update_MODELPARAM_VALUE.DATA_WIDTH { MODELPARAM_VALUE.DATA_WIDTH PARAM_VALUE.DATA_WIDTH } {
	# Procedure called to set VHDL generic/Verilog parameter value(s) based on TCL parameter value
	set_property value [get_property value ${PARAM_VALUE.DATA_WIDTH}] ${MODELPARAM_VALUE.DATA_WIDTH}
}

proc update_MODELPARAM_VALUE.CHANNELS_PER_MASTER { MODELPARAM_VALUE.CHANNELS_PER_MASTER PARAM_VALUE.CHANNELS_PER_MASTER } {
	# Procedure called to set VHDL generic/Verilog parameter value(s) based on TCL parameter value
	set_property value [get_property value ${PARAM_VALUE.CHANNELS_PER_MASTER}] ${MODELPARAM_VALUE.CHANNELS_PER_MASTER}
}

proc update_MODELPARAM_VALUE.SPI_MASTER { MODELPARAM_VALUE.SPI_MASTER PARAM_VALUE.SPI_MASTER } {
	# Procedure called to set VHDL generic/Verilog parameter value(s) based on TCL parameter value
	set_property value [get_property value ${PARAM_VALUE.SPI_MASTER}] ${MODELPARAM_VALUE.SPI_MASTER}
}

proc update_MODELPARAM_VALUE.OFFSET_WIDTH { MODELPARAM_VALUE.OFFSET_WIDTH PARAM_VALUE.OFFSET_WIDTH } {
	# Procedure called to set VHDL generic/Verilog parameter value(s) based on TCL parameter value
	set_property value [get_property value ${PARAM_VALUE.OFFSET_WIDTH}] ${MODELPARAM_VALUE.OFFSET_WIDTH}
}

proc update_MODELPARAM_VALUE.CONVERSION_WIDTH { MODELPARAM_VALUE.CONVERSION_WIDTH PARAM_VALUE.CONVERSION_WIDTH } {
	# Procedure called to set VHDL generic/Verilog parameter value(s) based on TCL parameter value
	set_property value [get_property value ${PARAM_VALUE.CONVERSION_WIDTH}] ${MODELPARAM_VALUE.CONVERSION_WIDTH}
}

proc update_MODELPARAM_VALUE.RES_LSB { MODELPARAM_VALUE.RES_LSB PARAM_VALUE.RES_LSB } {
	# Procedure called to set VHDL generic/Verilog parameter value(s) based on TCL parameter value
	set_property value [get_property value ${PARAM_VALUE.RES_LSB}] ${MODELPARAM_VALUE.RES_LSB}
}

proc update_MODELPARAM_VALUE.RES_MSB { MODELPARAM_VALUE.RES_MSB PARAM_VALUE.RES_MSB } {
	# Procedure called to set VHDL generic/Verilog parameter value(s) based on TCL parameter value
	set_property value [get_property value ${PARAM_VALUE.RES_MSB}] ${MODELPARAM_VALUE.RES_MSB}
}

proc update_MODELPARAM_VALUE.DIFFERENTIAL { MODELPARAM_VALUE.DIFFERENTIAL PARAM_VALUE.DIFFERENTIAL } {
	# Procedure called to set VHDL generic/Verilog parameter value(s) based on TCL parameter value
	set_property value [get_property value ${PARAM_VALUE.DIFFERENTIAL}] ${MODELPARAM_VALUE.DIFFERENTIAL}
}

proc update_MODELPARAM_VALUE.C_S00_AXI_DATA_WIDTH { MODELPARAM_VALUE.C_S00_AXI_DATA_WIDTH } {
	# Procedure called to set VHDL generic/Verilog parameter value(s) based on TCL parameter value
	# WARNING: There is no corresponding user parameter named "C_S00_AXI_DATA_WIDTH". Setting updated value from the model parameter.
set_property value 32 ${MODELPARAM_VALUE.C_S00_AXI_DATA_WIDTH}
}

proc update_MODELPARAM_VALUE.C_S00_AXI_ADDR_WIDTH { MODELPARAM_VALUE.C_S00_AXI_ADDR_WIDTH } {
	# Procedure called to set VHDL generic/Verilog parameter value(s) based on TCL parameter value
	# WARNING: There is no corresponding user parameter named "C_S00_AXI_ADDR_WIDTH". Setting updated value from the model parameter.
set_property value 6 ${MODELPARAM_VALUE.C_S00_AXI_ADDR_WIDTH}
}

