############################################################
## This file is generated automatically by Vitis HLS.
## Please DO NOT edit it.
## Copyright (C) 1986-2020 Xilinx, Inc. All Rights Reserved.
############################################################
open_project PID_controller
set_top uz_PI_Controller_sample
add_files PID_controller/default_uz_global_configuration.h
add_files PID_controller/uz_AXI.h
add_files PID_controller/uz_HAL.h
add_files PID_controller/uz_piController.c
add_files PID_controller/uz_piController.h
add_files PID_controller/uz_signals.h
add_files PID_controller/xbasic_types.h
add_files PID_controller/xil_assert.h
add_files PID_controller/xil_printf.h
add_files PID_controller/xil_types.h
add_files PID_controller/xparameters.h
add_files PID_controller/xstatus.h
open_solution "solution1" -flow_target vivado
set_part {xqzu9eg-ffrc900-1-i}
create_clock -period 10 -name default
source "./PID_controller/solution1/directives.tcl"
#csim_design
csynth_design
#cosim_design
export_design -rtl vhdl -format ip_catalog
