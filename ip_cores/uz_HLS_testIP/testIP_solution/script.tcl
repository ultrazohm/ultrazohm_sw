############################################################
## Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
############################################################
open_project uz_HLS_testIP
set_top uz_HLS_testIP
add_files ./uz_HLS_testIP.cpp
add_files ./uz_HLS_testIP.h
add_files -tb ./tb_uz_HLS_testIP.cpp
open_solution "testIP_solution" -flow_target vivado
set_part {xczu9eg-ffvc900-1-e}
create_clock -period 10 -name default
config_export -format ip_catalog -rtl verilog
#source "./testIP_solution/directives.tcl"
csim_design
csynth_design
export_design -rtl verilog -format ip_catalog
