############################################################
## This file is generated automatically by Vitis HLS.
## Please DO NOT edit it.
## Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
############################################################
open_project uz_VSD
set_top uz_VSD_6ph_asym
add_files uz_VSD/uz_VSD.cpp
add_files uz_VSD/uz_VSD.h
add_files -tb uz_VSD/test_uz_VSD.cpp -cflags "-Wno-unknown-pragmas -Wno-unknown-pragmas -Wno-unknown-pragmas -Wno-unknown-pragmas -Wno-unknown-pragmas -Wno-unknown-pragmas -Wno-unknown-pragmas -Wno-unknown-pragmas -Wno-unknown-pragmas" -csimflags "-Wno-unknown-pragmas"
open_solution "solution1" -flow_target vivado
set_part {xczu9eg-ffvb1156-1-e}
create_clock -period 100MHz -name default
config_export -flow syn -format ip_catalog -rtl verilog -vivado_clock 100MHz
source "./uz_VSD/solution1/directives.tcl"
csim_design
csynth_design
cosim_design
export_design -flow syn -rtl verilog -format ip_catalog
