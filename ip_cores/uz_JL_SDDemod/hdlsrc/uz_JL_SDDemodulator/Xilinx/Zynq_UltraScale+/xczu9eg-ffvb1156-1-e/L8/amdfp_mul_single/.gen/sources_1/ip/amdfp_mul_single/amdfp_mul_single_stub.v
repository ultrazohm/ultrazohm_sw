// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// --------------------------------------------------------------------------------
// Tool Version: Vivado v.2022.2 (win64) Build 3671981 Fri Oct 14 05:00:03 MDT 2022
// Date        : Wed Jul 22 12:41:23 2026
// Host        : Jonathan-Link running 64-bit major release  (build 9200)
// Command     : write_verilog -force -mode synth_stub
//               c:/Users/jonat/Documents/ultrazohm_sw/ip_cores/uz_JL_SDDemod/hdlsrc/uz_JL_SDDemodulator/Xilinx/Zynq_UltraScale+/xczu9eg-ffvb1156-1-e/L8/amdfp_mul_single/.gen/sources_1/ip/amdfp_mul_single/amdfp_mul_single_stub.v
// Design      : amdfp_mul_single
// Purpose     : Stub declaration of top-level module interface
// Device      : xczu9eg-ffvb1156-1-e
// --------------------------------------------------------------------------------

// This empty module with port declaration file causes synthesis tools to infer a black box for IP.
// The synthesis directives are for Synopsys Synplify support to prevent IO buffer insertion.
// Please paste the declaration into a Verilog source file or add the file as an additional source.
(* X_CORE_INFO = "floating_point_v7_1_15,Vivado 2022.2" *)
module amdfp_mul_single(aclk, aclken, aresetn, s_axis_a_tvalid, 
  s_axis_a_tdata, s_axis_b_tvalid, s_axis_b_tdata, m_axis_result_tvalid, 
  m_axis_result_tdata)
/* synthesis syn_black_box black_box_pad_pin="aclk,aclken,aresetn,s_axis_a_tvalid,s_axis_a_tdata[31:0],s_axis_b_tvalid,s_axis_b_tdata[31:0],m_axis_result_tvalid,m_axis_result_tdata[31:0]" */;
  input aclk;
  input aclken;
  input aresetn;
  input s_axis_a_tvalid;
  input [31:0]s_axis_a_tdata;
  input s_axis_b_tvalid;
  input [31:0]s_axis_b_tdata;
  output m_axis_result_tvalid;
  output [31:0]m_axis_result_tdata;
endmodule
