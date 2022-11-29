############################################################
## This file is generated automatically by Vitis HLS.
## Please DO NOT edit it.
## Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
############################################################
open_project fcs_mpc
set_top ctrl_wrapper
add_files pred_controller_hw.h
add_files fcsmpc_n1.cpp
add_files define_symbols.h
add_files controller_wrapper.h
add_files controller_wrapper.cpp
add_files -tb tb_fcsmpc_n1.cpp -cflags "-Wno-unknown-pragmas -Wno-unknown-pragmas" -csimflags "-Wno-unknown-pragmas"
open_solution "uz_9eg" -flow_target vivado
set_part {xczu9eg-ffvc900-1-e}
create_clock -period 10 -name default
config_interface -m_axi_latency 0 -register_io scalar_all
config_compile -no_signed_zeros -unsafe_math_optimizations
config_export -description fcsmpc_n1 -format ip_catalog -rtl vhdl -vendor ultrazohm
source "./fcs_mpc/uz_9eg/directives.tcl"
csim_design -O
csynth_design
cosim_design -rtl vhdl
export_design -format ip_catalog
