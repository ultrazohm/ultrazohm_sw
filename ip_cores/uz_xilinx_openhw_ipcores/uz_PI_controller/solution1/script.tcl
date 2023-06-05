############################################################
## This file is generated automatically by Vitis HLS.
## Please DO NOT edit it.
## Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
############################################################
open_project uz_PI_controller
set_top uz_PI_controller
add_files uz_PI_controller/uz_PI_controller.cpp
add_files uz_PI_controller/uz_PI_controller.h
add_files -tb uz_PI_controller/testbench.cpp
open_solution "solution1" -flow_target vivado
set_part {xck26-sfvc784-2LV-c}
create_clock -period 100MHz -name default
config_export -format ip_catalog -rtl verilog -vivado_clock 100MHz
source "./uz_PI_controller/solution1/directives.tcl"
csim_design
csynth_design
cosim_design
export_design -flow syn -rtl verilog -format ip_catalog
