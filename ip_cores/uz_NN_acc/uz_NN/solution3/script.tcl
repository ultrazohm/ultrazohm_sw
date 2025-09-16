############################################################
## This file is generated automatically by Vitis HLS.
## Please DO NOT edit it.
## Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
############################################################
open_project uz_NN
set_top uz_NN_acc
add_files uz_NN/uz_layers.h
add_files uz_NN/uz_layers.cpp
add_files uz_NN/uz_dense_relu.h
add_files uz_NN/uz_dense_relu.cpp
add_files uz_NN/uz_dense.h
add_files uz_NN/uz_dense.cpp
add_files uz_NN/uz_copy_L_Output_Weights.h
add_files uz_NN/uz_copy_L_Output_Weights.cpp
add_files uz_NN/uz_NN_acc.h
add_files uz_NN/uz_NN_acc.cpp
add_files uz_NN/uz_MMult_MaxSize.h
add_files -tb uz_NN/tb_uz_NN_acc.cpp -cflags "-Wno-unknown-pragmas -Wno-unknown-pragmas -Wno-unknown-pragmas -Wno-unknown-pragmas -Wno-unknown-pragmas -Wno-unknown-pragmas -Wno-unknown-pragmas -Wno-unknown-pragmas -Wno-unknown-pragmas -Wno-unknown-pragmas -Wno-unknown-pragmas -Wno-unknown-pragmas -Wno-unknown-pragmas -Wno-unknown-pragmas -Wno-unknown-pragmas -Wno-unknown-pragmas" -csimflags "-Wno-unknown-pragmas"
open_solution "solution3" -flow_target vitis
set_part {xczu9eg-ffvc900-1-e}
create_clock -period 10 -name default
config_interface -m_axi_addr64=0 -m_axi_alignment_byte_size 32 -m_axi_latency 64 -m_axi_max_bitwidth 32 -m_axi_max_widen_bitwidth 32
config_rtl -register_reset_num 3
config_array_partition -complete_threshold 2
config_compile -no_signed_zeros -unsafe_math_optimizations
config_export -format ip_catalog -rtl verilog -version 1.0 -description XxYYY_setup -display_name uz_NN_X_YYY_acc -ipname uz_NN_X_YYY
source "./uz_NN/solution3/directives.tcl"
csynth_design
export_design -format ip_catalog
