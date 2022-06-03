
set PATH=
call C:/Xilinx/Vivado/2020.1/bin/xelab xil_defaultlib.apatb_uz_FOC_sample_top glbl -prj uz_FOC_sample.prj -L smartconnect_v1_0 -L axi_protocol_checker_v1_1_12 -L axi_protocol_checker_v1_1_13 -L axis_protocol_checker_v1_1_11 -L axis_protocol_checker_v1_1_12 -L xil_defaultlib -L unisims_ver -L xpm  --lib "ieee_proposed=./ieee_proposed" -s uz_FOC_sample 
call C:/Xilinx/Vivado/2020.1/bin/xsim --noieeewarnings uz_FOC_sample -tclbatch uz_FOC_sample.tcl

