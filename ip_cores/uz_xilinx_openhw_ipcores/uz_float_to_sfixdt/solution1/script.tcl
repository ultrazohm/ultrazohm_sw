############################################################
## This file is generated automatically by Vitis HLS.
## Please DO NOT edit it.
## Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
############################################################
open_project uz_float_to_sfixdt
set_top uz_float_to_sfixdt
add_files uz_float_to_sfixdt/uz_float_to_sfixdt.h
add_files uz_float_to_sfixdt/uz_float_to_sfixdt.cpp
add_files uz_HLS_test.h
add_files uz_HLS_test.c
add_files -tb uz_float_to_sfixdt/testbench.cpp -cflags "-Wno-unknown-pragmas" -csimflags "-Wno-unknown-pragmas"
open_solution "solution1" -flow_target vivado
set_part {xczu9eg-ffvc900-1-e}
create_clock -period 100MHz -name default
config_export -format ip_catalog -output C:/Users/valen/Documents/repos/UZ/ultrazohm_sw/ip_cores/uz_xilinx_openhw_ipcores/uz_float_to_sfixdt -rtl verilog -vivado_clock 100MHz
source "./uz_float_to_sfixdt/solution1/directives.tcl"
csim_design
csynth_design
cosim_design
export_design -flow syn -rtl verilog -format ip_catalog -output C:/Users/valen/Documents/repos/UZ/ultrazohm_sw/ip_cores/uz_xilinx_openhw_ipcores/uz_float_to_sfixdt
