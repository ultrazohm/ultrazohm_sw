// Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// --------------------------------------------------------------------------------
// Tool Version: Vivado v.2020.1.1 (win64) Build 2960000 Wed Aug  5 22:57:20 MDT 2020
// Date        : Fri Jan 28 14:49:00 2022
// Host        : enc177112 running 64-bit major release  (build 9200)
// Command     : write_verilog -force -mode synth_stub
//               c:/GIT/UltraZohm/software/ultrazohm_sw_develop/vivado/zusys/ip/zusys_delay_trigger_0_0/zusys_delay_trigger_0_0_stub.v
// Design      : zusys_delay_trigger_0_0
// Purpose     : Stub declaration of top-level module interface
// Device      : xczu9eg-ffvc900-1-e
// --------------------------------------------------------------------------------

// This empty module with port declaration file causes synthesis tools to infer a black box for IP.
// The synthesis directives are for Synopsys Synplify support to prevent IO buffer insertion.
// Please paste the declaration into a Verilog source file or add the file as an additional source.
(* x_core_info = "delay_trigger,Vivado 2020.1.1" *)
module zusys_delay_trigger_0_0(clk, delay_cycles, a_in, a_out)
/* synthesis syn_black_box black_box_pad_pin="clk,delay_cycles[10:0],a_in,a_out" */;
  input clk;
  input [10:0]delay_cycles;
  input a_in;
  output a_out;
endmodule
