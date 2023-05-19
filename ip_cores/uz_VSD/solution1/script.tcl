############################################################
## This file is generated automatically by Vitis HLS.
## Please DO NOT edit it.
## Copyright (C) 1986-2020 Xilinx, Inc. All Rights Reserved.
############################################################
open_project uz_VSD
set_top uz_VSD_6ph_asym
add_files uz_VSD/uz_VSD.cpp
add_files -tb uz_VSD/test_uz_VSD.cpp
open_solution "solution1" -flow_target vivado
set_part {xczu19eg-ffve1924-2-e}
create_clock -period 100MHz -name default
source "./uz_VSD/solution1/directives.tcl"
csim_design
csynth_design
cosim_design
export_design -format ip_catalog
