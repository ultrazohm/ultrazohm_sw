############################################################
## This file is generated automatically by Vitis HLS.
## Please DO NOT edit it.
## Copyright (C) 1986-2020 Xilinx, Inc. All Rights Reserved.
############################################################
open_project FOC_hls
set_top uz_FOC_sample
add_files foc/uz_space_vector_limitation.h
add_files foc/uz_space_vector_limitation.c
add_files foc/uz_signals.h
add_files foc/uz_signals.c
add_files foc/uz_piController.h
add_files foc/uz_piController.c
add_files foc/uz_linear_decoupling.h
add_files foc/uz_linear_decoupling.c
add_files foc/uz_Transformation.h
add_files foc/uz_Transformation.c
add_files foc/uz_FOC.h
add_files foc/uz_FOC.c
add_files -tb foc/tb_foc.c -cflags "-Wno-unknown-pragmas" -csimflags "-Wno-unknown-pragmas"
open_solution "solution1" -flow_target vivado
set_part {xczu9eg-ffvb1156-2-e}
create_clock -period 10 -name default
config_export -display_name uz_FOC -format ip_catalog -output C:/Users/ponpr/Desktop/Intenship/uz_FOC/uz_FOC_sample.zip -rtl verilog -vivado_optimization_level 0 -vivado_phys_opt none -vivado_report_level 0
source "./FOC_hls/solution1/directives.tcl"
csim_design
csynth_design
cosim_design
export_design -rtl verilog -format ip_catalog -display_name "uz_FOC" -output C:/Users/ponpr/Desktop/Intenship/uz_FOC/uz_FOC_sample.zip
