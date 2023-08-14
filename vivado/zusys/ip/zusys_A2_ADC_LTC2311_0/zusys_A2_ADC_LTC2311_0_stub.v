// Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// --------------------------------------------------------------------------------
// Tool Version: Vivado v.2020.1.1 (win64) Build 2960000 Wed Aug  5 22:57:20 MDT 2020
// Date        : Fri Jan 28 14:50:37 2022
// Host        : enc177112 running 64-bit major release  (build 9200)
// Command     : write_verilog -force -mode synth_stub -rename_top zusys_A2_ADC_LTC2311_0 -prefix
//               zusys_A2_ADC_LTC2311_0_ zusys_A3_ADC_LTC2311_0_stub.v
// Design      : zusys_A3_ADC_LTC2311_0
// Purpose     : Stub declaration of top-level module interface
// Device      : xczu9eg-ffvc900-1-e
// --------------------------------------------------------------------------------

// This empty module with port declaration file causes synthesis tools to infer a black box for IP.
// The synthesis directives are for Synopsys Synplify support to prevent IO buffer insertion.
// Please paste the declaration into a Verilog source file or add the file as an additional source.
(* x_core_info = "ADC_LTC2311_v3_0,Vivado 2020.1.1" *)
module zusys_A2_ADC_LTC2311_0(RAW_VALUE, RAW_VALID, SI_VALUE, SI_VALID, 
  TRIGGER_CNV, SAMPLE_COUNTER, SS_N, SCLK_DIFF, MISO_DIFF, s00_axi_aclk, s00_axi_aresetn, 
  s00_axi_awaddr, s00_axi_awprot, s00_axi_awvalid, s00_axi_awready, s00_axi_wdata, 
  s00_axi_wstrb, s00_axi_wvalid, s00_axi_wready, s00_axi_bresp, s00_axi_bvalid, 
  s00_axi_bready, s00_axi_araddr, s00_axi_arprot, s00_axi_arvalid, s00_axi_arready, 
  s00_axi_rdata, s00_axi_rresp, s00_axi_rvalid, s00_axi_rready)
/* synthesis syn_black_box black_box_pad_pin="RAW_VALUE[127:0],RAW_VALID[0:0],SI_VALUE[279:0],SI_VALID[0:0],TRIGGER_CNV[0:0],SAMPLE_COUNTER[31:0],SS_N[0:0],SCLK_DIFF[1:0],MISO_DIFF[15:0],s00_axi_aclk,s00_axi_aresetn,s00_axi_awaddr[5:0],s00_axi_awprot[2:0],s00_axi_awvalid,s00_axi_awready,s00_axi_wdata[31:0],s00_axi_wstrb[3:0],s00_axi_wvalid,s00_axi_wready,s00_axi_bresp[1:0],s00_axi_bvalid,s00_axi_bready,s00_axi_araddr[5:0],s00_axi_arprot[2:0],s00_axi_arvalid,s00_axi_arready,s00_axi_rdata[31:0],s00_axi_rresp[1:0],s00_axi_rvalid,s00_axi_rready" */;
  output [127:0]RAW_VALUE;
  output [0:0]RAW_VALID;
  output [279:0]SI_VALUE;
  output [0:0]SI_VALID;
  input [0:0]TRIGGER_CNV;
  output [31:0]SAMPLE_COUNTER;
  output [0:0]SS_N;
  output [1:0]SCLK_DIFF;
  input [15:0]MISO_DIFF;
  input s00_axi_aclk;
  input s00_axi_aresetn;
  input [5:0]s00_axi_awaddr;
  input [2:0]s00_axi_awprot;
  input s00_axi_awvalid;
  output s00_axi_awready;
  input [31:0]s00_axi_wdata;
  input [3:0]s00_axi_wstrb;
  input s00_axi_wvalid;
  output s00_axi_wready;
  output [1:0]s00_axi_bresp;
  output s00_axi_bvalid;
  input s00_axi_bready;
  input [5:0]s00_axi_araddr;
  input [2:0]s00_axi_arprot;
  input s00_axi_arvalid;
  output s00_axi_arready;
  output [31:0]s00_axi_rdata;
  output [1:0]s00_axi_rresp;
  output s00_axi_rvalid;
  input s00_axi_rready;
endmodule
