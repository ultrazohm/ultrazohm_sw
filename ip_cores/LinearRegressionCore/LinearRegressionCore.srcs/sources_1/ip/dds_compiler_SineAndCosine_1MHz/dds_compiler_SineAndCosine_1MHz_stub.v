// Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// --------------------------------------------------------------------------------
// Tool Version: Vivado v.2020.1.1_AR75502 (win64) Build 2960000 Wed Aug  5 22:57:20 MDT 2020
// Date        : Wed Feb  8 12:07:11 2023
// Host        : HPC running 64-bit major release  (build 9200)
// Command     : write_verilog -force -mode synth_stub
//               e:/01_Repos/06_Ultrazohm_HADEK/ip_cores/LinearRegressionCore/LinearRegressionCore.srcs/sources_1/ip/dds_compiler_SineAndCosine_1MHz/dds_compiler_SineAndCosine_1MHz_stub.v
// Design      : dds_compiler_SineAndCosine_1MHz
// Purpose     : Stub declaration of top-level module interface
// Device      : xczu9eg-ffvc900-1-e
// --------------------------------------------------------------------------------

// This empty module with port declaration file causes synthesis tools to infer a black box for IP.
// The synthesis directives are for Synopsys Synplify support to prevent IO buffer insertion.
// Please paste the declaration into a Verilog source file or add the file as an additional source.
(* x_core_info = "dds_compiler_v6_0_20,Vivado 2020.1.1_AR75502" *)
module dds_compiler_SineAndCosine_1MHz(aclk, m_axis_data_tvalid, m_axis_data_tdata)
/* synthesis syn_black_box black_box_pad_pin="aclk,m_axis_data_tvalid,m_axis_data_tdata[31:0]" */;
  input aclk;
  output m_axis_data_tvalid;
  output [31:0]m_axis_data_tdata;
endmodule
