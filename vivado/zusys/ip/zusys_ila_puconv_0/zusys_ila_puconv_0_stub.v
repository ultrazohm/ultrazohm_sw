// Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// --------------------------------------------------------------------------------
// Tool Version: Vivado v.2020.1.1 (win64) Build 2960000 Wed Aug  5 22:57:20 MDT 2020
// Date        : Mon Feb 28 11:26:01 2022
// Host        : enc177112 running 64-bit major release  (build 9200)
// Command     : write_verilog -force -mode synth_stub
//               c:/GIT/UltraZohm/software/ultrazohm_sw_develop/vivado/zusys/ip/zusys_ila_puconv_0/zusys_ila_puconv_0_stub.v
// Design      : zusys_ila_puconv_0
// Purpose     : Stub declaration of top-level module interface
// Device      : xczu9eg-ffvc900-1-e
// --------------------------------------------------------------------------------

// This empty module with port declaration file causes synthesis tools to infer a black box for IP.
// The synthesis directives are for Synopsys Synplify support to prevent IO buffer insertion.
// Please paste the declaration into a Verilog source file or add the file as an additional source.
(* x_core_info = "ila,Vivado 2020.1.1" *)
module zusys_ila_puconv_0(clk, probe0, probe1, probe2, probe3, probe4, probe5, 
  probe6, probe7, probe8, probe9)
/* synthesis syn_black_box black_box_pad_pin="clk,probe0[17:0],probe1[17:0],probe2[17:0],probe3[17:0],probe4[17:0],probe5[17:0],probe6[17:0],probe7[17:0],probe8[0:0],probe9[0:0]" */;
  input clk;
  input [17:0]probe0;
  input [17:0]probe1;
  input [17:0]probe2;
  input [17:0]probe3;
  input [17:0]probe4;
  input [17:0]probe5;
  input [17:0]probe6;
  input [17:0]probe7;
  input [0:0]probe8;
  input [0:0]probe9;
endmodule
