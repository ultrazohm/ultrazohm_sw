# Definitional proc to organize widgets for parameters.
proc init_gui { IPINST } {
  ipgui::add_param $IPINST -name "Component_Name"
  #Adding Page
  set Page_0 [ipgui::add_page $IPINST -name "Page 0"]
  #Adding Group
  set Data [ipgui::add_group $IPINST -name "Data" -parent ${Page_0} -display_name {IO-Behavior}]
  set_property tooltip {Datawidth} ${Data}
  ipgui::add_static_text $IPINST -name "Datawidth" -parent ${Data} -text {Set the Wordwidth and specification of the fixed point for the Input-Signal and the Output-Signal}
  ipgui::add_param $IPINST -name "DataWidth" -parent ${Data}
  ipgui::add_param $IPINST -name "Fracbits" -parent ${Data}
  set Channels [ipgui::add_param $IPINST -name "Channels" -parent ${Data}]
  set_property tooltip {Specify the Amout of LR-Channels} ${Channels}

  #Adding Group
  set Filter_Behavior [ipgui::add_group $IPINST -name "Filter Behavior" -parent ${Page_0}]
  set_property tooltip {Filter Behavior} ${Filter_Behavior}
  ipgui::add_static_text $IPINST -name "Tabs" -parent ${Filter_Behavior} -text {Specify the amount of samples used for the linear regression}
  ipgui::add_param $IPINST -name "Tabs" -parent ${Filter_Behavior}

  #Adding Group
  set Core_Options [ipgui::add_group $IPINST -name "Core Options" -parent ${Page_0}]
  ipgui::add_static_text $IPINST -name "Alpha_Output_Enable" -parent ${Core_Options} -text {Enables the Output of the Alpha-Factors from the linear Regression}
  ipgui::add_param $IPINST -name "Set_AB_Out" -parent ${Core_Options}



}

proc update_PARAM_VALUE.C_S_AXI_ADDR_WIDTH { PARAM_VALUE.C_S_AXI_ADDR_WIDTH } {
	# Procedure called to update C_S_AXI_ADDR_WIDTH when any of the dependent parameters in the arguments change
}

proc validate_PARAM_VALUE.C_S_AXI_ADDR_WIDTH { PARAM_VALUE.C_S_AXI_ADDR_WIDTH } {
	# Procedure called to validate C_S_AXI_ADDR_WIDTH
	return true
}

proc update_PARAM_VALUE.C_S_AXI_DATA_WIDTH { PARAM_VALUE.C_S_AXI_DATA_WIDTH } {
	# Procedure called to update C_S_AXI_DATA_WIDTH when any of the dependent parameters in the arguments change
}

proc validate_PARAM_VALUE.C_S_AXI_DATA_WIDTH { PARAM_VALUE.C_S_AXI_DATA_WIDTH } {
	# Procedure called to validate C_S_AXI_DATA_WIDTH
	return true
}

proc update_PARAM_VALUE.Channels { PARAM_VALUE.Channels } {
	# Procedure called to update Channels when any of the dependent parameters in the arguments change
}

proc validate_PARAM_VALUE.Channels { PARAM_VALUE.Channels } {
	# Procedure called to validate Channels
	return true
}

proc update_PARAM_VALUE.DataWidth { PARAM_VALUE.DataWidth } {
	# Procedure called to update DataWidth when any of the dependent parameters in the arguments change
}

proc validate_PARAM_VALUE.DataWidth { PARAM_VALUE.DataWidth } {
	# Procedure called to validate DataWidth
	return true
}

proc update_PARAM_VALUE.Fracbits { PARAM_VALUE.Fracbits } {
	# Procedure called to update Fracbits when any of the dependent parameters in the arguments change
}

proc validate_PARAM_VALUE.Fracbits { PARAM_VALUE.Fracbits } {
	# Procedure called to validate Fracbits
	return true
}

proc update_PARAM_VALUE.Set_AB_Out { PARAM_VALUE.Set_AB_Out } {
	# Procedure called to update Set_AB_Out when any of the dependent parameters in the arguments change
}

proc validate_PARAM_VALUE.Set_AB_Out { PARAM_VALUE.Set_AB_Out } {
	# Procedure called to validate Set_AB_Out
	return true
}

proc update_PARAM_VALUE.Tabs { PARAM_VALUE.Tabs } {
	# Procedure called to update Tabs when any of the dependent parameters in the arguments change
}

proc validate_PARAM_VALUE.Tabs { PARAM_VALUE.Tabs } {
	# Procedure called to validate Tabs
	return true
}


proc update_MODELPARAM_VALUE.DataWidth { MODELPARAM_VALUE.DataWidth PARAM_VALUE.DataWidth } {
	# Procedure called to set VHDL generic/Verilog parameter value(s) based on TCL parameter value
	set_property value [get_property value ${PARAM_VALUE.DataWidth}] ${MODELPARAM_VALUE.DataWidth}
}

proc update_MODELPARAM_VALUE.Tabs { MODELPARAM_VALUE.Tabs PARAM_VALUE.Tabs } {
	# Procedure called to set VHDL generic/Verilog parameter value(s) based on TCL parameter value
	set_property value [get_property value ${PARAM_VALUE.Tabs}] ${MODELPARAM_VALUE.Tabs}
}

proc update_MODELPARAM_VALUE.Fracbits { MODELPARAM_VALUE.Fracbits PARAM_VALUE.Fracbits } {
	# Procedure called to set VHDL generic/Verilog parameter value(s) based on TCL parameter value
	set_property value [get_property value ${PARAM_VALUE.Fracbits}] ${MODELPARAM_VALUE.Fracbits}
}

proc update_MODELPARAM_VALUE.C_S_AXI_DATA_WIDTH { MODELPARAM_VALUE.C_S_AXI_DATA_WIDTH PARAM_VALUE.C_S_AXI_DATA_WIDTH } {
	# Procedure called to set VHDL generic/Verilog parameter value(s) based on TCL parameter value
	set_property value [get_property value ${PARAM_VALUE.C_S_AXI_DATA_WIDTH}] ${MODELPARAM_VALUE.C_S_AXI_DATA_WIDTH}
}

proc update_MODELPARAM_VALUE.C_S_AXI_ADDR_WIDTH { MODELPARAM_VALUE.C_S_AXI_ADDR_WIDTH PARAM_VALUE.C_S_AXI_ADDR_WIDTH } {
	# Procedure called to set VHDL generic/Verilog parameter value(s) based on TCL parameter value
	set_property value [get_property value ${PARAM_VALUE.C_S_AXI_ADDR_WIDTH}] ${MODELPARAM_VALUE.C_S_AXI_ADDR_WIDTH}
}

proc update_MODELPARAM_VALUE.Channels { MODELPARAM_VALUE.Channels PARAM_VALUE.Channels } {
	# Procedure called to set VHDL generic/Verilog parameter value(s) based on TCL parameter value
	set_property value [get_property value ${PARAM_VALUE.Channels}] ${MODELPARAM_VALUE.Channels}
}

