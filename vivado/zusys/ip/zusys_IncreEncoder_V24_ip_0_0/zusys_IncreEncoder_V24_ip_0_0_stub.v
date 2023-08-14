// Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// --------------------------------------------------------------------------------
// Tool Version: Vivado v.2020.1.1 (win64) Build 2960000 Wed Aug  5 22:57:20 MDT 2020
// Date        : Fri Jan 28 14:50:25 2022
// Host        : enc177112 running 64-bit major release  (build 9200)
// Command     : write_verilog -force -mode synth_stub
//               c:/GIT/UltraZohm/software/ultrazohm_sw_develop/vivado/zusys/ip/zusys_IncreEncoder_V24_ip_0_0/zusys_IncreEncoder_V24_ip_0_0_stub.v
// Design      : zusys_IncreEncoder_V24_ip_0_0
// Purpose     : Stub declaration of top-level module interface
// Device      : xczu9eg-ffvc900-1-e
// --------------------------------------------------------------------------------

// This empty module with port declaration file causes synthesis tools to infer a black box for IP.
// The synthesis directives are for Synopsys Synplify support to prevent IO buffer insertion.
// Please paste the declaration into a Verilog source file or add the file as an additional source.
(* x_core_info = "IncreEncoder_V24_ip,Vivado 2020.1.1" *)
module zusys_IncreEncoder_V24_ip_0_0(IPCORE_CLK, IPCORE_RESETN, A, B, I, PeriodEnd, 
  AXI4_Lite_ACLK, AXI4_Lite_ARESETN, AXI4_Lite_AWADDR, AXI4_Lite_AWVALID, AXI4_Lite_WDATA, 
  AXI4_Lite_WSTRB, AXI4_Lite_WVALID, AXI4_Lite_BREADY, AXI4_Lite_ARADDR, AXI4_Lite_ARVALID, 
  AXI4_Lite_RREADY, omega, theta_el, position, edge_rsvd, count, OverSamplFactor, 
  AXI4_Lite_AWREADY, AXI4_Lite_WREADY, AXI4_Lite_BRESP, AXI4_Lite_BVALID, 
  AXI4_Lite_ARREADY, AXI4_Lite_RDATA, AXI4_Lite_RRESP, AXI4_Lite_RVALID)
/* synthesis syn_black_box black_box_pad_pin="IPCORE_CLK,IPCORE_RESETN,A,B,I,PeriodEnd,AXI4_Lite_ACLK,AXI4_Lite_ARESETN,AXI4_Lite_AWADDR[15:0],AXI4_Lite_AWVALID,AXI4_Lite_WDATA[31:0],AXI4_Lite_WSTRB[3:0],AXI4_Lite_WVALID,AXI4_Lite_BREADY,AXI4_Lite_ARADDR[15:0],AXI4_Lite_ARVALID,AXI4_Lite_RREADY,omega[23:0],theta_el[23:0],position[15:0],edge_rsvd,count,OverSamplFactor[15:0],AXI4_Lite_AWREADY,AXI4_Lite_WREADY,AXI4_Lite_BRESP[1:0],AXI4_Lite_BVALID,AXI4_Lite_ARREADY,AXI4_Lite_RDATA[31:0],AXI4_Lite_RRESP[1:0],AXI4_Lite_RVALID" */;
  input IPCORE_CLK;
  input IPCORE_RESETN;
  input A;
  input B;
  input I;
  input PeriodEnd;
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
  output [23:0]omega;
  output [23:0]theta_el;
  output [15:0]position;
  output edge_rsvd;
  output count;
  output [15:0]OverSamplFactor;
  output AXI4_Lite_AWREADY;
  output AXI4_Lite_WREADY;
  output [1:0]AXI4_Lite_BRESP;
  output AXI4_Lite_BVALID;
  output AXI4_Lite_ARREADY;
  output [31:0]AXI4_Lite_RDATA;
  output [1:0]AXI4_Lite_RRESP;
  output AXI4_Lite_RVALID;
endmodule
