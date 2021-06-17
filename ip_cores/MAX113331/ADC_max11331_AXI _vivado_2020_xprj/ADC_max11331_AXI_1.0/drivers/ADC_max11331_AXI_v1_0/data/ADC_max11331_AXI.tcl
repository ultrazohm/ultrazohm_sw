

proc generate {drv_handle} {
	xdefine_include_file $drv_handle "xparameters.h" "ADC_max11331_AXI" "NUM_INSTANCES" "DEVICE_ID"  "C_S0_AXI_Lite_BASEADDR" "C_S0_AXI_Lite_HIGHADDR"
}
