// Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// --------------------------------------------------------------------------------
// Tool Version: Vivado v.2020.1.1 (win64) Build 2960000 Wed Aug  5 22:57:20 MDT 2020
// Date        : Fri Jan 28 14:45:31 2022
// Host        : enc177112 running 64-bit major release  (build 9200)
// Command     : write_verilog -force -mode synth_stub
//               c:/GIT/UltraZohm/software/ultrazohm_sw_develop/vivado/zusys/ip/zusys_clk_wiz_0_0/zusys_clk_wiz_0_0_stub.v
// Design      : zusys_clk_wiz_0_0
// Purpose     : Stub declaration of top-level module interface
// Device      : xczu9eg-ffvc900-1-e
// --------------------------------------------------------------------------------

// This empty module with port declaration file causes synthesis tools to infer a black box for IP.
// The synthesis directives are for Synopsys Synplify support to prevent IO buffer insertion.
// Please paste the declaration into a Verilog source file or add the file as an additional source.
module zusys_clk_wiz_0_0(clk_50MHz, clk_10MHz, clk_25MHz, resetn, clk_in1)
/* synthesis syn_black_box black_box_pad_pin="clk_50MHz,clk_10MHz,clk_25MHz,resetn,clk_in1" */;
  output clk_50MHz;
  output clk_10MHz;
  output clk_25MHz;
  input resetn;
  input clk_in1;
endmodule
