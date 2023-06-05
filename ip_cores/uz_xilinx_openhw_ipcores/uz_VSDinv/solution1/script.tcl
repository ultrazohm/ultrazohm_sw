############################################################
## This file is generated automatically by Vitis HLS.
## Please DO NOT edit it.
## Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
############################################################
open_project uz_VSDinv
set_top uz_VSDinv_6ph_asym
add_files uz_VSDinv/uz_VSDinv.h
add_files uz_VSDinv/uz_VSDinv.cpp
add_files -tb uz_VSDinv/test_uz_VSDinv.cpp -cflags "-Wno-unknown-pragmas -Wno-unknown-pragmas -Wno-unknown-pragmas -Wno-unknown-pragmas -Wno-unknown-pragmas" -csimflags "-Wno-unknown-pragmas"
open_solution "solution1" -flow_target vivado
set_part {xczu7eg-ffvf1517-2-e}
create_clock -period 100MHz -name default
config_export -flow syn -format ip_catalog -rtl verilog -vivado_clock 100MHz
source "./uz_VSDinv/solution1/directives.tcl"
csim_design
csynth_design
cosim_design
export_design -flow syn -rtl verilog -format ip_catalog
