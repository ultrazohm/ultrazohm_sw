// Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// --------------------------------------------------------------------------------
// Tool Version: Vivado v.2020.1.1 (win64) Build 2960000 Wed Aug  5 22:57:20 MDT 2020
// Date        : Fri Jan 28 14:48:00 2022
// Host        : enc177112 running 64-bit major release  (build 9200)
// Command     : write_verilog -force -mode synth_stub
//               c:/GIT/UltraZohm/software/ultrazohm_sw_develop/vivado/zusys/ip/zusys_top_npc_state_machine_0_0/zusys_top_npc_state_machine_0_0_stub.v
// Design      : zusys_top_npc_state_machine_0_0
// Purpose     : Stub declaration of top-level module interface
// Device      : xczu9eg-ffvc900-1-e
// --------------------------------------------------------------------------------

// This empty module with port declaration file causes synthesis tools to infer a black box for IP.
// The synthesis directives are for Synopsys Synplify support to prevent IO buffer insertion.
// Please paste the declaration into a Verilog source file or add the file as an additional source.
(* x_core_info = "top_npc_state_machine,Vivado 2020.1.1" *)
module zusys_top_npc_state_machine_0_0(clock, enable, switching_signals, deadtime, A_S1, 
  A_S2, A_S3, A_S4, B_S1, B_S2, B_S3, B_S4, C_S1, C_S2, C_S3, C_S4, A_phase_off, B_phase_off, C_phase_off)
/* synthesis syn_black_box black_box_pad_pin="clock,enable,switching_signals[5:0],deadtime[9:0],A_S1,A_S2,A_S3,A_S4,B_S1,B_S2,B_S3,B_S4,C_S1,C_S2,C_S3,C_S4,A_phase_off,B_phase_off,C_phase_off" */;
  input clock;
  input enable;
  input [5:0]switching_signals;
  input [9:0]deadtime;
  output A_S1;
  output A_S2;
  output A_S3;
  output A_S4;
  output B_S1;
  output B_S2;
  output B_S3;
  output B_S4;
  output C_S1;
  output C_S2;
  output C_S3;
  output C_S4;
  output A_phase_off;
  output B_phase_off;
  output C_phase_off;
endmodule
