############################################################
## This file is generated automatically by Vitis HLS.
## Please DO NOT edit it.
## Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
############################################################
open_project uz_fixdt_to_float
set_top uz_fixdt_to_float
add_files uz_fixdt_to_float/uz_fixdt_to_float.h
add_files uz_fixdt_to_float/uz_fixdt_to_float.cpp
add_files -tb uz_fixdt_to_float/testbench.cpp -cflags "-Wno-unknown-pragmas" -csimflags "-Wno-unknown-pragmas"
open_solution "solution1" -flow_target vivado
set_part {xczu9eg-ffvb1156-2-e}
create_clock -period 100MHz -name default
config_export -format ip_catalog -rtl verilog -vivado_clock 100MHz
source "./uz_fixdt_to_float/solution1/directives.tcl"
csim_design
csynth_design
cosim_design
export_design -flow syn -rtl verilog -format ip_catalog
