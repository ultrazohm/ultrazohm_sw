############################################################
## This file is generated automatically by Vitis HLS.
## Please DO NOT edit it.
## Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
############################################################
open_project uz_Park
set_top uz_Park
add_files uz_Park/uz_Park.h
add_files uz_Park/uz_Park.cpp
add_files -tb uz_Park/test_uz_Park.cpp -cflags "-Wno-unknown-pragmas -Wno-unknown-pragmas -Wno-unknown-pragmas" -csimflags "-Wno-unknown-pragmas"
open_solution "solution1" -flow_target vivado
set_part {xczu9eg-ffvc900-2-e}
create_clock -period 100MHz -name default
config_export -format ip_catalog -output C:/Users/valen/Documents/repos/UZ/ultrazohm_sw/ip_cores/uz_xilinx_openhw_ipcores/uz_Park -rtl verilog -vivado_clock 100MHz
source "./uz_Park/solution1/directives.tcl"
csim_design
csynth_design
cosim_design
export_design -flow syn -rtl verilog -format ip_catalog -output C:/Users/valen/Documents/repos/UZ/ultrazohm_sw/ip_cores/uz_xilinx_openhw_ipcores/uz_Park
