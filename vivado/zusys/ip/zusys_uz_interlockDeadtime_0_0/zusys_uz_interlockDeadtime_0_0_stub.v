// Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// --------------------------------------------------------------------------------
// Tool Version: Vivado v.2020.1.1 (win64) Build 2960000 Wed Aug  5 22:57:20 MDT 2020
// Date        : Fri Jan 28 14:44:28 2022
// Host        : enc177112 running 64-bit major release  (build 9200)
// Command     : write_verilog -force -mode synth_stub
//               c:/GIT/UltraZohm/software/ultrazohm_sw_develop/vivado/zusys/ip/zusys_uz_interlockDeadtime_0_0/zusys_uz_interlockDeadtime_0_0_stub.v
// Design      : zusys_uz_interlockDeadtime_0_0
// Purpose     : Stub declaration of top-level module interface
// Device      : xczu9eg-ffvc900-1-e
// --------------------------------------------------------------------------------

// This empty module with port declaration file causes synthesis tools to infer a black box for IP.
// The synthesis directives are for Synopsys Synplify support to prevent IO buffer insertion.
// Please paste the declaration into a Verilog source file or add the file as an additional source.
(* x_core_info = "uz_interlockDeadtime2L,Vivado 2020.1.1" *)
module zusys_uz_interlockDeadtime_0_0(IPCORE_CLK, IPCORE_RESETN, S0, S1, S2, S3, S4, S5, 
  AXI4_ACLK, AXI4_ARESETN, AXI4_AWID, AXI4_AWADDR, AXI4_AWLEN, AXI4_AWSIZE, AXI4_AWBURST, 
  AXI4_AWLOCK, AXI4_AWCACHE, AXI4_AWPROT, AXI4_AWVALID, AXI4_WDATA, AXI4_WSTRB, AXI4_WLAST, 
  AXI4_WVALID, AXI4_BREADY, AXI4_ARID, AXI4_ARADDR, AXI4_ARLEN, AXI4_ARSIZE, AXI4_ARBURST, 
  AXI4_ARLOCK, AXI4_ARCACHE, AXI4_ARPROT, AXI4_ARVALID, AXI4_RREADY, s0_out, s1_out, s2_out, 
  s3_out, s4_out, s5_out, enableFB, AXI4_AWREADY, AXI4_WREADY, AXI4_BID, AXI4_BRESP, AXI4_BVALID, 
  AXI4_ARREADY, AXI4_RID, AXI4_RDATA, AXI4_RRESP, AXI4_RLAST, AXI4_RVALID)
/* synthesis syn_black_box black_box_pad_pin="IPCORE_CLK,IPCORE_RESETN,S0,S1,S2,S3,S4,S5,AXI4_ACLK,AXI4_ARESETN,AXI4_AWID[11:0],AXI4_AWADDR[15:0],AXI4_AWLEN[7:0],AXI4_AWSIZE[2:0],AXI4_AWBURST[1:0],AXI4_AWLOCK,AXI4_AWCACHE[3:0],AXI4_AWPROT[2:0],AXI4_AWVALID,AXI4_WDATA[31:0],AXI4_WSTRB[3:0],AXI4_WLAST,AXI4_WVALID,AXI4_BREADY,AXI4_ARID[11:0],AXI4_ARADDR[15:0],AXI4_ARLEN[7:0],AXI4_ARSIZE[2:0],AXI4_ARBURST[1:0],AXI4_ARLOCK,AXI4_ARCACHE[3:0],AXI4_ARPROT[2:0],AXI4_ARVALID,AXI4_RREADY,s0_out,s1_out,s2_out,s3_out,s4_out,s5_out,enableFB,AXI4_AWREADY,AXI4_WREADY,AXI4_BID[11:0],AXI4_BRESP[1:0],AXI4_BVALID,AXI4_ARREADY,AXI4_RID[11:0],AXI4_RDATA[31:0],AXI4_RRESP[1:0],AXI4_RLAST,AXI4_RVALID" */;
  input IPCORE_CLK;
  input IPCORE_RESETN;
  input S0;
  input S1;
  input S2;
  input S3;
  input S4;
  input S5;
  input AXI4_ACLK;
  input AXI4_ARESETN;
  input [11:0]AXI4_AWID;
  input [15:0]AXI4_AWADDR;
  input [7:0]AXI4_AWLEN;
  input [2:0]AXI4_AWSIZE;
  input [1:0]AXI4_AWBURST;
  input AXI4_AWLOCK;
  input [3:0]AXI4_AWCACHE;
  input [2:0]AXI4_AWPROT;
  input AXI4_AWVALID;
  input [31:0]AXI4_WDATA;
  input [3:0]AXI4_WSTRB;
  input AXI4_WLAST;
  input AXI4_WVALID;
  input AXI4_BREADY;
  input [11:0]AXI4_ARID;
  input [15:0]AXI4_ARADDR;
  input [7:0]AXI4_ARLEN;
  input [2:0]AXI4_ARSIZE;
  input [1:0]AXI4_ARBURST;
  input AXI4_ARLOCK;
  input [3:0]AXI4_ARCACHE;
  input [2:0]AXI4_ARPROT;
  input AXI4_ARVALID;
  input AXI4_RREADY;
  output s0_out;
  output s1_out;
  output s2_out;
  output s3_out;
  output s4_out;
  output s5_out;
  output enableFB;
  output AXI4_AWREADY;
  output AXI4_WREADY;
  output [11:0]AXI4_BID;
  output [1:0]AXI4_BRESP;
  output AXI4_BVALID;
  output AXI4_ARREADY;
  output [11:0]AXI4_RID;
  output [31:0]AXI4_RDATA;
  output [1:0]AXI4_RRESP;
  output AXI4_RLAST;
  output AXI4_RVALID;
endmodule
