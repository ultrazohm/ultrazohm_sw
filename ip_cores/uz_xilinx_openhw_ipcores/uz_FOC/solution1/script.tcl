############################################################
## This file is generated automatically by Vitis HLS.
## Please DO NOT edit it.
## Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
############################################################
open_project uz_FOC
set_top uz_FOC
add_files uz_FOC/uz_FOC.cpp
add_files uz_FOC/uz_FOC.h
add_files -tb uz_FOC/testbench.cpp -cflags "-Wno-unknown-pragmas -Wno-unknown-pragmas -Wno-unknown-pragmas -Wno-unknown-pragmas" -csimflags "-Wno-unknown-pragmas"
open_solution "solution1" -flow_target vivado
set_part {xczu9eg-ffvc900-1-e}
create_clock -period 100MHz -name default
config_export -flow syn -format ip_catalog -rtl vhdl -vivado_clock 100MHz
source "./uz_FOC/solution1/directives.tcl"
csim_design
csynth_design
cosim_design
export_design -flow syn -rtl vhdl -format ip_catalog
