############################################################
## This file is generated automatically by Vitis HLS.
## Please DO NOT edit it.
## Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
############################################################
open_project HLS_Project
set_top MatrixMultiplication
add_files HLS_Project/matrix_multiply.h
add_files HLS_Project/matrix_multiply.cpp
add_files -tb HLS_Project/tb_matrix_multiply.cpp -cflags "-Wno-unknown-pragmas -Wno-unknown-pragmas -Wno-unknown-pragmas" -csimflags "-Wno-unknown-pragmas"
open_solution "solution1" -flow_target vitis
set_part {xczu9eg-ffvc900-1-e}
create_clock -period 10 -name default
source "./HLS_Project/solution1/directives.tcl"
csim_design
csynth_design
cosim_design
export_design -rtl verilog -format ip_catalog
