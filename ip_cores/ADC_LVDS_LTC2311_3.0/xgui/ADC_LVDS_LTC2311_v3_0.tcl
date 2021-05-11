# Definitional proc to organize widgets for parameters.
proc init_gui { IPINST } {
  ipgui::add_param $IPINST -name "Component_Name"
  #Adding Page
  set Page_0 [ipgui::add_page $IPINST -name "Page 0"]
  ipgui::add_param $IPINST -name "C_S00_AXI_BASEADDR" -parent ${Page_0}
  ipgui::add_param $IPINST -name "C_S00_AXI_HIGHADDR" -parent ${Page_0}

  ipgui::add_param $IPINST -name "DATA_WIDTH"
  ipgui::add_param $IPINST -name "CHANNELS_PER_MASTER"
  ipgui::add_param $IPINST -name "SPI_MASTER"
  ipgui::add_param $IPINST -name "OFFSET_WIDTH"
  ipgui::add_param $IPINST -name "CONVERSION_WIDTH"
  ipgui::add_param $IPINST -name "RES_LSB"
  ipgui::add_param $IPINST -name "RES_MSB"
  ipgui::add_param $IPINST -name "DIFFERENTIAL"
  ipgui::add_param $IPINST -name "C_S00_AXI_DATA_WIDTH"
  ipgui::add_param $IPINST -name "C_S00_AXI_ADDR_WIDTH"

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

proc update_MODELPARAM_VALUE.C_S00_AXI_DATA_WIDTH { MODELPARAM_VALUE.C_S00_AXI_DATA_WIDTH PARAM_VALUE.C_S00_AXI_DATA_WIDTH } {
	# Procedure called to set VHDL generic/Verilog parameter value(s) based on TCL parameter value
	set_property value [get_property value ${PARAM_VALUE.C_S00_AXI_DATA_WIDTH}] ${MODELPARAM_VALUE.C_S00_AXI_DATA_WIDTH}
}

proc update_MODELPARAM_VALUE.C_S00_AXI_ADDR_WIDTH { MODELPARAM_VALUE.C_S00_AXI_ADDR_WIDTH PARAM_VALUE.C_S00_AXI_ADDR_WIDTH } {
	# Procedure called to set VHDL generic/Verilog parameter value(s) based on TCL parameter value
	set_property value [get_property value ${PARAM_VALUE.C_S00_AXI_ADDR_WIDTH}] ${MODELPARAM_VALUE.C_S00_AXI_ADDR_WIDTH}
}

