// Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// --------------------------------------------------------------------------------
// Tool Version: Vivado v.2020.1.1 (win64) Build 2960000 Wed Aug  5 22:57:20 MDT 2020
// Date        : Fri Jan 28 14:43:25 2022
// Host        : enc177112 running 64-bit major release  (build 9200)
// Command     : write_verilog -force -mode synth_stub -rename_top zusys_PWM_and_SS_control_V_0_2 -prefix
//               zusys_PWM_and_SS_control_V_0_2_ zusys_PWM_and_SS_control_V_0_0_stub.v
// Design      : zusys_PWM_and_SS_control_V_0_0
// Purpose     : Stub declaration of top-level module interface
// Device      : xczu9eg-ffvc900-1-e
// --------------------------------------------------------------------------------

// This empty module with port declaration file causes synthesis tools to infer a black box for IP.
// The synthesis directives are for Synopsys Synplify support to prevent IO buffer insertion.
// Please paste the declaration into a Verilog source file or add the file as an additional source.
(* x_core_info = "PWM_and_SS_control_V3_ip,Vivado 2020.1.1" *)
module zusys_PWM_and_SS_control_V_0_2(IPCORE_CLK, IPCORE_RESETN, m_u1_norm, 
  m_u2_norm, m_u3_norm, SS0_IN_External, SS1_IN_External, SS2_IN_External, SS3_IN_External, 
  SS4_IN_External, SS5_IN_External, AXI4_Lite_ACLK, AXI4_Lite_ARESETN, AXI4_Lite_AWADDR, 
  AXI4_Lite_AWVALID, AXI4_Lite_WDATA, AXI4_Lite_WSTRB, AXI4_Lite_WVALID, AXI4_Lite_BREADY, 
  AXI4_Lite_ARADDR, AXI4_Lite_ARVALID, AXI4_Lite_RREADY, SS0_OUT, SS1_OUT, SS2_OUT, SS3_OUT, 
  SS4_OUT, SS5_OUT, PWM_enb_out, Triangular_Max, Triangular_Min, AXI4_Lite_AWREADY, 
  AXI4_Lite_WREADY, AXI4_Lite_BRESP, AXI4_Lite_BVALID, AXI4_Lite_ARREADY, AXI4_Lite_RDATA, 
  AXI4_Lite_RRESP, AXI4_Lite_RVALID)
/* synthesis syn_black_box black_box_pad_pin="IPCORE_CLK,IPCORE_RESETN,m_u1_norm[13:0],m_u2_norm[13:0],m_u3_norm[13:0],SS0_IN_External,SS1_IN_External,SS2_IN_External,SS3_IN_External,SS4_IN_External,SS5_IN_External,AXI4_Lite_ACLK,AXI4_Lite_ARESETN,AXI4_Lite_AWADDR[15:0],AXI4_Lite_AWVALID,AXI4_Lite_WDATA[31:0],AXI4_Lite_WSTRB[3:0],AXI4_Lite_WVALID,AXI4_Lite_BREADY,AXI4_Lite_ARADDR[15:0],AXI4_Lite_ARVALID,AXI4_Lite_RREADY,SS0_OUT,SS1_OUT,SS2_OUT,SS3_OUT,SS4_OUT,SS5_OUT,PWM_enb_out,Triangular_Max,Triangular_Min,AXI4_Lite_AWREADY,AXI4_Lite_WREADY,AXI4_Lite_BRESP[1:0],AXI4_Lite_BVALID,AXI4_Lite_ARREADY,AXI4_Lite_RDATA[31:0],AXI4_Lite_RRESP[1:0],AXI4_Lite_RVALID" */;
  input IPCORE_CLK;
  input IPCORE_RESETN;
  input [13:0]m_u1_norm;
  input [13:0]m_u2_norm;
  input [13:0]m_u3_norm;
  input SS0_IN_External;
  input SS1_IN_External;
  input SS2_IN_External;
  input SS3_IN_External;
  input SS4_IN_External;
  input SS5_IN_External;
  input AXI4_Lite_ACLK;
  input AXI4_Lite_ARESETN;
  input [15:0]AXI4_Lite_AWADDR;
  input AXI4_Lite_AWVALID;
  input [31:0]AXI4_Lite_WDATA;
  input [3:0]AXI4_Lite_WSTRB;
  input AXI4_Lite_WVALID;
  input AXI4_Lite_BREADY;
  input [15:0]AXI4_Lite_ARADDR;
  input AXI4_Lite_ARVALID;
  input AXI4_Lite_RREADY;
  output SS0_OUT;
  output SS1_OUT;
  output SS2_OUT;
  output SS3_OUT;
  output SS4_OUT;
  output SS5_OUT;
  output PWM_enb_out;
  output Triangular_Max;
  output Triangular_Min;
  output AXI4_Lite_AWREADY;
  output AXI4_Lite_WREADY;
  output [1:0]AXI4_Lite_BRESP;
  output AXI4_Lite_BVALID;
  output AXI4_Lite_ARREADY;
  output [31:0]AXI4_Lite_RDATA;
  output [1:0]AXI4_Lite_RRESP;
  output AXI4_Lite_RVALID;
endmodule
