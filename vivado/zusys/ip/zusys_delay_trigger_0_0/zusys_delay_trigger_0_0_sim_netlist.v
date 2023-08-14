// Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// --------------------------------------------------------------------------------
// Tool Version: Vivado v.2020.1.1 (win64) Build 2960000 Wed Aug  5 22:57:20 MDT 2020
// Date        : Fri Jan 28 14:49:00 2022
// Host        : enc177112 running 64-bit major release  (build 9200)
// Command     : write_verilog -force -mode funcsim
//               c:/GIT/UltraZohm/software/ultrazohm_sw_develop/vivado/zusys/ip/zusys_delay_trigger_0_0/zusys_delay_trigger_0_0_sim_netlist.v
// Design      : zusys_delay_trigger_0_0
// Purpose     : This verilog netlist is a functional simulation representation of the design and should not be modified
//               or synthesized. This netlist cannot be used for SDF annotated simulation.
// Device      : xczu9eg-ffvc900-1-e
// --------------------------------------------------------------------------------
`timescale 1 ps / 1 ps

(* CHECK_LICENSE_TYPE = "zusys_delay_trigger_0_0,delay_trigger,{}" *) (* downgradeipidentifiedwarnings = "yes" *) (* ip_definition_source = "module_ref" *) 
(* x_core_info = "delay_trigger,Vivado 2020.1.1" *) 
(* NotValidForBitStream *)
module zusys_delay_trigger_0_0
   (clk,
    delay_cycles,
    a_in,
    a_out);
  (* x_interface_info = "xilinx.com:signal:clock:1.0 clk CLK" *) (* x_interface_parameter = "XIL_INTERFACENAME clk, FREQ_HZ 100000000, FREQ_TOLERANCE_HZ 0, PHASE 0.000, CLK_DOMAIN zusys_zynq_ultra_ps_e_0_0_pl_clk0, INSERT_VIP 0" *) input clk;
  input [10:0]delay_cycles;
  input a_in;
  output a_out;

  wire a_in;
  wire a_out;
  wire clk;
  wire [10:0]delay_cycles;

  zusys_delay_trigger_0_0_delay_trigger U0
       (.a_in(a_in),
        .a_out(a_out),
        .clk(clk),
        .delay_cycles(delay_cycles));
endmodule

(* ORIG_REF_NAME = "delay_trigger" *) 
module zusys_delay_trigger_0_0_delay_trigger
   (a_out,
    a_in,
    delay_cycles,
    clk);
  output a_out;
  input a_in;
  input [10:0]delay_cycles;
  input clk;

  wire a_in;
  wire a_out;
  wire a_out0;
  wire a_out_i_4_n_0;
  wire a_out_i_5_n_0;
  wire a_out_i_6_n_0;
  wire a_out_i_7_n_0;
  wire a_out_reg_i_2_n_0;
  wire a_out_reg_i_3_n_0;
  wire \a_store_reg[0]_mux__0_n_0 ;
  wire \a_store_reg[0]_mux__10_n_0 ;
  wire \a_store_reg[0]_mux__11_n_0 ;
  wire \a_store_reg[0]_mux__12_n_0 ;
  wire \a_store_reg[0]_mux__13_n_0 ;
  wire \a_store_reg[0]_mux__14_n_0 ;
  wire \a_store_reg[0]_mux__15_n_0 ;
  wire \a_store_reg[0]_mux__16_n_0 ;
  wire \a_store_reg[0]_mux__17_n_0 ;
  wire \a_store_reg[0]_mux__18_n_0 ;
  wire \a_store_reg[0]_mux__19_n_0 ;
  wire \a_store_reg[0]_mux__1_n_0 ;
  wire \a_store_reg[0]_mux__20_n_0 ;
  wire \a_store_reg[0]_mux__21_n_0 ;
  wire \a_store_reg[0]_mux__22_n_0 ;
  wire \a_store_reg[0]_mux__23_n_0 ;
  wire \a_store_reg[0]_mux__24_n_0 ;
  wire \a_store_reg[0]_mux__25_n_0 ;
  wire \a_store_reg[0]_mux__26_n_0 ;
  wire \a_store_reg[0]_mux__27_n_0 ;
  wire \a_store_reg[0]_mux__28_n_0 ;
  wire \a_store_reg[0]_mux__29_n_0 ;
  wire \a_store_reg[0]_mux__2_n_0 ;
  wire \a_store_reg[0]_mux__30_n_0 ;
  wire \a_store_reg[0]_mux__31_n_0 ;
  wire \a_store_reg[0]_mux__32_n_0 ;
  wire \a_store_reg[0]_mux__33_n_0 ;
  wire \a_store_reg[0]_mux__34_n_0 ;
  wire \a_store_reg[0]_mux__35_n_0 ;
  wire \a_store_reg[0]_mux__36_n_0 ;
  wire \a_store_reg[0]_mux__37_n_0 ;
  wire \a_store_reg[0]_mux__38_n_0 ;
  wire \a_store_reg[0]_mux__39_n_0 ;
  wire \a_store_reg[0]_mux__3_n_0 ;
  wire \a_store_reg[0]_mux__40_n_0 ;
  wire \a_store_reg[0]_mux__41_n_0 ;
  wire \a_store_reg[0]_mux__42_n_0 ;
  wire \a_store_reg[0]_mux__43_n_0 ;
  wire \a_store_reg[0]_mux__44_n_0 ;
  wire \a_store_reg[0]_mux__45_n_0 ;
  wire \a_store_reg[0]_mux__46_n_0 ;
  wire \a_store_reg[0]_mux__4_n_0 ;
  wire \a_store_reg[0]_mux__5_n_0 ;
  wire \a_store_reg[0]_mux__6_n_0 ;
  wire \a_store_reg[0]_mux__7_n_0 ;
  wire \a_store_reg[0]_mux__8_n_0 ;
  wire \a_store_reg[0]_mux__9_n_0 ;
  wire \a_store_reg[0]_mux_n_0 ;
  wire \a_store_reg[0]_srl32__0_n_0 ;
  wire \a_store_reg[0]_srl32__0_n_1 ;
  wire \a_store_reg[0]_srl32__10_n_0 ;
  wire \a_store_reg[0]_srl32__10_n_1 ;
  wire \a_store_reg[0]_srl32__11_n_0 ;
  wire \a_store_reg[0]_srl32__11_n_1 ;
  wire \a_store_reg[0]_srl32__12_n_0 ;
  wire \a_store_reg[0]_srl32__12_n_1 ;
  wire \a_store_reg[0]_srl32__13_n_0 ;
  wire \a_store_reg[0]_srl32__13_n_1 ;
  wire \a_store_reg[0]_srl32__14_n_0 ;
  wire \a_store_reg[0]_srl32__14_n_1 ;
  wire \a_store_reg[0]_srl32__15_n_0 ;
  wire \a_store_reg[0]_srl32__15_n_1 ;
  wire \a_store_reg[0]_srl32__16_n_0 ;
  wire \a_store_reg[0]_srl32__16_n_1 ;
  wire \a_store_reg[0]_srl32__17_n_0 ;
  wire \a_store_reg[0]_srl32__17_n_1 ;
  wire \a_store_reg[0]_srl32__18_n_0 ;
  wire \a_store_reg[0]_srl32__18_n_1 ;
  wire \a_store_reg[0]_srl32__19_n_0 ;
  wire \a_store_reg[0]_srl32__19_n_1 ;
  wire \a_store_reg[0]_srl32__1_n_0 ;
  wire \a_store_reg[0]_srl32__1_n_1 ;
  wire \a_store_reg[0]_srl32__20_n_0 ;
  wire \a_store_reg[0]_srl32__20_n_1 ;
  wire \a_store_reg[0]_srl32__21_n_0 ;
  wire \a_store_reg[0]_srl32__21_n_1 ;
  wire \a_store_reg[0]_srl32__22_n_0 ;
  wire \a_store_reg[0]_srl32__22_n_1 ;
  wire \a_store_reg[0]_srl32__23_n_0 ;
  wire \a_store_reg[0]_srl32__23_n_1 ;
  wire \a_store_reg[0]_srl32__24_n_0 ;
  wire \a_store_reg[0]_srl32__24_n_1 ;
  wire \a_store_reg[0]_srl32__25_n_0 ;
  wire \a_store_reg[0]_srl32__25_n_1 ;
  wire \a_store_reg[0]_srl32__26_n_0 ;
  wire \a_store_reg[0]_srl32__26_n_1 ;
  wire \a_store_reg[0]_srl32__27_n_0 ;
  wire \a_store_reg[0]_srl32__27_n_1 ;
  wire \a_store_reg[0]_srl32__28_n_0 ;
  wire \a_store_reg[0]_srl32__28_n_1 ;
  wire \a_store_reg[0]_srl32__29_n_0 ;
  wire \a_store_reg[0]_srl32__29_n_1 ;
  wire \a_store_reg[0]_srl32__2_n_0 ;
  wire \a_store_reg[0]_srl32__2_n_1 ;
  wire \a_store_reg[0]_srl32__30_n_0 ;
  wire \a_store_reg[0]_srl32__30_n_1 ;
  wire \a_store_reg[0]_srl32__31_n_0 ;
  wire \a_store_reg[0]_srl32__31_n_1 ;
  wire \a_store_reg[0]_srl32__32_n_0 ;
  wire \a_store_reg[0]_srl32__32_n_1 ;
  wire \a_store_reg[0]_srl32__33_n_0 ;
  wire \a_store_reg[0]_srl32__33_n_1 ;
  wire \a_store_reg[0]_srl32__34_n_0 ;
  wire \a_store_reg[0]_srl32__34_n_1 ;
  wire \a_store_reg[0]_srl32__35_n_0 ;
  wire \a_store_reg[0]_srl32__35_n_1 ;
  wire \a_store_reg[0]_srl32__36_n_0 ;
  wire \a_store_reg[0]_srl32__36_n_1 ;
  wire \a_store_reg[0]_srl32__37_n_0 ;
  wire \a_store_reg[0]_srl32__37_n_1 ;
  wire \a_store_reg[0]_srl32__38_n_0 ;
  wire \a_store_reg[0]_srl32__38_n_1 ;
  wire \a_store_reg[0]_srl32__39_n_0 ;
  wire \a_store_reg[0]_srl32__39_n_1 ;
  wire \a_store_reg[0]_srl32__3_n_0 ;
  wire \a_store_reg[0]_srl32__3_n_1 ;
  wire \a_store_reg[0]_srl32__40_n_0 ;
  wire \a_store_reg[0]_srl32__40_n_1 ;
  wire \a_store_reg[0]_srl32__41_n_0 ;
  wire \a_store_reg[0]_srl32__41_n_1 ;
  wire \a_store_reg[0]_srl32__42_n_0 ;
  wire \a_store_reg[0]_srl32__42_n_1 ;
  wire \a_store_reg[0]_srl32__43_n_0 ;
  wire \a_store_reg[0]_srl32__43_n_1 ;
  wire \a_store_reg[0]_srl32__44_n_0 ;
  wire \a_store_reg[0]_srl32__44_n_1 ;
  wire \a_store_reg[0]_srl32__45_n_0 ;
  wire \a_store_reg[0]_srl32__45_n_1 ;
  wire \a_store_reg[0]_srl32__46_n_0 ;
  wire \a_store_reg[0]_srl32__46_n_1 ;
  wire \a_store_reg[0]_srl32__47_n_0 ;
  wire \a_store_reg[0]_srl32__47_n_1 ;
  wire \a_store_reg[0]_srl32__48_n_0 ;
  wire \a_store_reg[0]_srl32__48_n_1 ;
  wire \a_store_reg[0]_srl32__49_n_0 ;
  wire \a_store_reg[0]_srl32__49_n_1 ;
  wire \a_store_reg[0]_srl32__4_n_0 ;
  wire \a_store_reg[0]_srl32__4_n_1 ;
  wire \a_store_reg[0]_srl32__50_n_0 ;
  wire \a_store_reg[0]_srl32__50_n_1 ;
  wire \a_store_reg[0]_srl32__51_n_0 ;
  wire \a_store_reg[0]_srl32__51_n_1 ;
  wire \a_store_reg[0]_srl32__52_n_0 ;
  wire \a_store_reg[0]_srl32__52_n_1 ;
  wire \a_store_reg[0]_srl32__53_n_0 ;
  wire \a_store_reg[0]_srl32__53_n_1 ;
  wire \a_store_reg[0]_srl32__54_n_0 ;
  wire \a_store_reg[0]_srl32__54_n_1 ;
  wire \a_store_reg[0]_srl32__55_n_0 ;
  wire \a_store_reg[0]_srl32__55_n_1 ;
  wire \a_store_reg[0]_srl32__56_n_0 ;
  wire \a_store_reg[0]_srl32__56_n_1 ;
  wire \a_store_reg[0]_srl32__57_n_0 ;
  wire \a_store_reg[0]_srl32__57_n_1 ;
  wire \a_store_reg[0]_srl32__58_n_0 ;
  wire \a_store_reg[0]_srl32__58_n_1 ;
  wire \a_store_reg[0]_srl32__59_n_0 ;
  wire \a_store_reg[0]_srl32__59_n_1 ;
  wire \a_store_reg[0]_srl32__5_n_0 ;
  wire \a_store_reg[0]_srl32__5_n_1 ;
  wire \a_store_reg[0]_srl32__60_n_0 ;
  wire \a_store_reg[0]_srl32__60_n_1 ;
  wire \a_store_reg[0]_srl32__61_n_0 ;
  wire \a_store_reg[0]_srl32__61_n_1 ;
  wire \a_store_reg[0]_srl32__62_n_0 ;
  wire \a_store_reg[0]_srl32__6_n_0 ;
  wire \a_store_reg[0]_srl32__6_n_1 ;
  wire \a_store_reg[0]_srl32__7_n_0 ;
  wire \a_store_reg[0]_srl32__7_n_1 ;
  wire \a_store_reg[0]_srl32__8_n_0 ;
  wire \a_store_reg[0]_srl32__8_n_1 ;
  wire \a_store_reg[0]_srl32__9_n_0 ;
  wire \a_store_reg[0]_srl32__9_n_1 ;
  wire \a_store_reg[0]_srl32_n_0 ;
  wire \a_store_reg[0]_srl32_n_1 ;
  wire clk;
  wire [10:0]delay_cycles;
  wire \NLW_a_store_reg[0]_srl32__62_Q31_UNCONNECTED ;

  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    a_out_i_4
       (.I0(\a_store_reg[0]_mux__34_n_0 ),
        .I1(\a_store_reg[0]_mux__33_n_0 ),
        .I2(delay_cycles[8]),
        .I3(\a_store_reg[0]_mux__32_n_0 ),
        .I4(delay_cycles[7]),
        .I5(\a_store_reg[0]_mux__31_n_0 ),
        .O(a_out_i_4_n_0));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    a_out_i_5
       (.I0(\a_store_reg[0]_mux__38_n_0 ),
        .I1(\a_store_reg[0]_mux__37_n_0 ),
        .I2(delay_cycles[8]),
        .I3(\a_store_reg[0]_mux__36_n_0 ),
        .I4(delay_cycles[7]),
        .I5(\a_store_reg[0]_mux__35_n_0 ),
        .O(a_out_i_5_n_0));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    a_out_i_6
       (.I0(\a_store_reg[0]_mux__42_n_0 ),
        .I1(\a_store_reg[0]_mux__41_n_0 ),
        .I2(delay_cycles[8]),
        .I3(\a_store_reg[0]_mux__40_n_0 ),
        .I4(delay_cycles[7]),
        .I5(\a_store_reg[0]_mux__39_n_0 ),
        .O(a_out_i_6_n_0));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    a_out_i_7
       (.I0(\a_store_reg[0]_mux__46_n_0 ),
        .I1(\a_store_reg[0]_mux__45_n_0 ),
        .I2(delay_cycles[8]),
        .I3(\a_store_reg[0]_mux__44_n_0 ),
        .I4(delay_cycles[7]),
        .I5(\a_store_reg[0]_mux__43_n_0 ),
        .O(a_out_i_7_n_0));
  FDRE #(
    .INIT(1'b0)) 
    a_out_reg
       (.C(clk),
        .CE(1'b1),
        .D(a_out0),
        .Q(a_out),
        .R(1'b0));
  MUXF8 a_out_reg_i_1
       (.I0(a_out_reg_i_2_n_0),
        .I1(a_out_reg_i_3_n_0),
        .O(a_out0),
        .S(delay_cycles[10]));
  MUXF7 a_out_reg_i_2
       (.I0(a_out_i_4_n_0),
        .I1(a_out_i_5_n_0),
        .O(a_out_reg_i_2_n_0),
        .S(delay_cycles[9]));
  MUXF7 a_out_reg_i_3
       (.I0(a_out_i_6_n_0),
        .I1(a_out_i_7_n_0),
        .O(a_out_reg_i_3_n_0),
        .S(delay_cycles[9]));
  MUXF7 \a_store_reg[0]_mux 
       (.I0(\a_store_reg[0]_srl32_n_0 ),
        .I1(\a_store_reg[0]_srl32__0_n_0 ),
        .O(\a_store_reg[0]_mux_n_0 ),
        .S(delay_cycles[5]));
  MUXF7 \a_store_reg[0]_mux__0 
       (.I0(\a_store_reg[0]_srl32__1_n_0 ),
        .I1(\a_store_reg[0]_srl32__2_n_0 ),
        .O(\a_store_reg[0]_mux__0_n_0 ),
        .S(delay_cycles[5]));
  MUXF7 \a_store_reg[0]_mux__1 
       (.I0(\a_store_reg[0]_srl32__3_n_0 ),
        .I1(\a_store_reg[0]_srl32__4_n_0 ),
        .O(\a_store_reg[0]_mux__1_n_0 ),
        .S(delay_cycles[5]));
  MUXF7 \a_store_reg[0]_mux__10 
       (.I0(\a_store_reg[0]_srl32__21_n_0 ),
        .I1(\a_store_reg[0]_srl32__22_n_0 ),
        .O(\a_store_reg[0]_mux__10_n_0 ),
        .S(delay_cycles[5]));
  MUXF7 \a_store_reg[0]_mux__11 
       (.I0(\a_store_reg[0]_srl32__23_n_0 ),
        .I1(\a_store_reg[0]_srl32__24_n_0 ),
        .O(\a_store_reg[0]_mux__11_n_0 ),
        .S(delay_cycles[5]));
  MUXF7 \a_store_reg[0]_mux__12 
       (.I0(\a_store_reg[0]_srl32__25_n_0 ),
        .I1(\a_store_reg[0]_srl32__26_n_0 ),
        .O(\a_store_reg[0]_mux__12_n_0 ),
        .S(delay_cycles[5]));
  MUXF7 \a_store_reg[0]_mux__13 
       (.I0(\a_store_reg[0]_srl32__27_n_0 ),
        .I1(\a_store_reg[0]_srl32__28_n_0 ),
        .O(\a_store_reg[0]_mux__13_n_0 ),
        .S(delay_cycles[5]));
  MUXF7 \a_store_reg[0]_mux__14 
       (.I0(\a_store_reg[0]_srl32__29_n_0 ),
        .I1(\a_store_reg[0]_srl32__30_n_0 ),
        .O(\a_store_reg[0]_mux__14_n_0 ),
        .S(delay_cycles[5]));
  MUXF7 \a_store_reg[0]_mux__15 
       (.I0(\a_store_reg[0]_srl32__31_n_0 ),
        .I1(\a_store_reg[0]_srl32__32_n_0 ),
        .O(\a_store_reg[0]_mux__15_n_0 ),
        .S(delay_cycles[5]));
  MUXF7 \a_store_reg[0]_mux__16 
       (.I0(\a_store_reg[0]_srl32__33_n_0 ),
        .I1(\a_store_reg[0]_srl32__34_n_0 ),
        .O(\a_store_reg[0]_mux__16_n_0 ),
        .S(delay_cycles[5]));
  MUXF7 \a_store_reg[0]_mux__17 
       (.I0(\a_store_reg[0]_srl32__35_n_0 ),
        .I1(\a_store_reg[0]_srl32__36_n_0 ),
        .O(\a_store_reg[0]_mux__17_n_0 ),
        .S(delay_cycles[5]));
  MUXF7 \a_store_reg[0]_mux__18 
       (.I0(\a_store_reg[0]_srl32__37_n_0 ),
        .I1(\a_store_reg[0]_srl32__38_n_0 ),
        .O(\a_store_reg[0]_mux__18_n_0 ),
        .S(delay_cycles[5]));
  MUXF7 \a_store_reg[0]_mux__19 
       (.I0(\a_store_reg[0]_srl32__39_n_0 ),
        .I1(\a_store_reg[0]_srl32__40_n_0 ),
        .O(\a_store_reg[0]_mux__19_n_0 ),
        .S(delay_cycles[5]));
  MUXF7 \a_store_reg[0]_mux__2 
       (.I0(\a_store_reg[0]_srl32__5_n_0 ),
        .I1(\a_store_reg[0]_srl32__6_n_0 ),
        .O(\a_store_reg[0]_mux__2_n_0 ),
        .S(delay_cycles[5]));
  MUXF7 \a_store_reg[0]_mux__20 
       (.I0(\a_store_reg[0]_srl32__41_n_0 ),
        .I1(\a_store_reg[0]_srl32__42_n_0 ),
        .O(\a_store_reg[0]_mux__20_n_0 ),
        .S(delay_cycles[5]));
  MUXF7 \a_store_reg[0]_mux__21 
       (.I0(\a_store_reg[0]_srl32__43_n_0 ),
        .I1(\a_store_reg[0]_srl32__44_n_0 ),
        .O(\a_store_reg[0]_mux__21_n_0 ),
        .S(delay_cycles[5]));
  MUXF7 \a_store_reg[0]_mux__22 
       (.I0(\a_store_reg[0]_srl32__45_n_0 ),
        .I1(\a_store_reg[0]_srl32__46_n_0 ),
        .O(\a_store_reg[0]_mux__22_n_0 ),
        .S(delay_cycles[5]));
  MUXF7 \a_store_reg[0]_mux__23 
       (.I0(\a_store_reg[0]_srl32__47_n_0 ),
        .I1(\a_store_reg[0]_srl32__48_n_0 ),
        .O(\a_store_reg[0]_mux__23_n_0 ),
        .S(delay_cycles[5]));
  MUXF7 \a_store_reg[0]_mux__24 
       (.I0(\a_store_reg[0]_srl32__49_n_0 ),
        .I1(\a_store_reg[0]_srl32__50_n_0 ),
        .O(\a_store_reg[0]_mux__24_n_0 ),
        .S(delay_cycles[5]));
  MUXF7 \a_store_reg[0]_mux__25 
       (.I0(\a_store_reg[0]_srl32__51_n_0 ),
        .I1(\a_store_reg[0]_srl32__52_n_0 ),
        .O(\a_store_reg[0]_mux__25_n_0 ),
        .S(delay_cycles[5]));
  MUXF7 \a_store_reg[0]_mux__26 
       (.I0(\a_store_reg[0]_srl32__53_n_0 ),
        .I1(\a_store_reg[0]_srl32__54_n_0 ),
        .O(\a_store_reg[0]_mux__26_n_0 ),
        .S(delay_cycles[5]));
  MUXF7 \a_store_reg[0]_mux__27 
       (.I0(\a_store_reg[0]_srl32__55_n_0 ),
        .I1(\a_store_reg[0]_srl32__56_n_0 ),
        .O(\a_store_reg[0]_mux__27_n_0 ),
        .S(delay_cycles[5]));
  MUXF7 \a_store_reg[0]_mux__28 
       (.I0(\a_store_reg[0]_srl32__57_n_0 ),
        .I1(\a_store_reg[0]_srl32__58_n_0 ),
        .O(\a_store_reg[0]_mux__28_n_0 ),
        .S(delay_cycles[5]));
  MUXF7 \a_store_reg[0]_mux__29 
       (.I0(\a_store_reg[0]_srl32__59_n_0 ),
        .I1(\a_store_reg[0]_srl32__60_n_0 ),
        .O(\a_store_reg[0]_mux__29_n_0 ),
        .S(delay_cycles[5]));
  MUXF7 \a_store_reg[0]_mux__3 
       (.I0(\a_store_reg[0]_srl32__7_n_0 ),
        .I1(\a_store_reg[0]_srl32__8_n_0 ),
        .O(\a_store_reg[0]_mux__3_n_0 ),
        .S(delay_cycles[5]));
  MUXF7 \a_store_reg[0]_mux__30 
       (.I0(\a_store_reg[0]_srl32__61_n_0 ),
        .I1(\a_store_reg[0]_srl32__62_n_0 ),
        .O(\a_store_reg[0]_mux__30_n_0 ),
        .S(delay_cycles[5]));
  MUXF8 \a_store_reg[0]_mux__31 
       (.I0(\a_store_reg[0]_mux_n_0 ),
        .I1(\a_store_reg[0]_mux__0_n_0 ),
        .O(\a_store_reg[0]_mux__31_n_0 ),
        .S(delay_cycles[6]));
  MUXF8 \a_store_reg[0]_mux__32 
       (.I0(\a_store_reg[0]_mux__1_n_0 ),
        .I1(\a_store_reg[0]_mux__2_n_0 ),
        .O(\a_store_reg[0]_mux__32_n_0 ),
        .S(delay_cycles[6]));
  MUXF8 \a_store_reg[0]_mux__33 
       (.I0(\a_store_reg[0]_mux__3_n_0 ),
        .I1(\a_store_reg[0]_mux__4_n_0 ),
        .O(\a_store_reg[0]_mux__33_n_0 ),
        .S(delay_cycles[6]));
  MUXF8 \a_store_reg[0]_mux__34 
       (.I0(\a_store_reg[0]_mux__5_n_0 ),
        .I1(\a_store_reg[0]_mux__6_n_0 ),
        .O(\a_store_reg[0]_mux__34_n_0 ),
        .S(delay_cycles[6]));
  MUXF8 \a_store_reg[0]_mux__35 
       (.I0(\a_store_reg[0]_mux__7_n_0 ),
        .I1(\a_store_reg[0]_mux__8_n_0 ),
        .O(\a_store_reg[0]_mux__35_n_0 ),
        .S(delay_cycles[6]));
  MUXF8 \a_store_reg[0]_mux__36 
       (.I0(\a_store_reg[0]_mux__9_n_0 ),
        .I1(\a_store_reg[0]_mux__10_n_0 ),
        .O(\a_store_reg[0]_mux__36_n_0 ),
        .S(delay_cycles[6]));
  MUXF8 \a_store_reg[0]_mux__37 
       (.I0(\a_store_reg[0]_mux__11_n_0 ),
        .I1(\a_store_reg[0]_mux__12_n_0 ),
        .O(\a_store_reg[0]_mux__37_n_0 ),
        .S(delay_cycles[6]));
  MUXF8 \a_store_reg[0]_mux__38 
       (.I0(\a_store_reg[0]_mux__13_n_0 ),
        .I1(\a_store_reg[0]_mux__14_n_0 ),
        .O(\a_store_reg[0]_mux__38_n_0 ),
        .S(delay_cycles[6]));
  MUXF8 \a_store_reg[0]_mux__39 
       (.I0(\a_store_reg[0]_mux__15_n_0 ),
        .I1(\a_store_reg[0]_mux__16_n_0 ),
        .O(\a_store_reg[0]_mux__39_n_0 ),
        .S(delay_cycles[6]));
  MUXF7 \a_store_reg[0]_mux__4 
       (.I0(\a_store_reg[0]_srl32__9_n_0 ),
        .I1(\a_store_reg[0]_srl32__10_n_0 ),
        .O(\a_store_reg[0]_mux__4_n_0 ),
        .S(delay_cycles[5]));
  MUXF8 \a_store_reg[0]_mux__40 
       (.I0(\a_store_reg[0]_mux__17_n_0 ),
        .I1(\a_store_reg[0]_mux__18_n_0 ),
        .O(\a_store_reg[0]_mux__40_n_0 ),
        .S(delay_cycles[6]));
  MUXF8 \a_store_reg[0]_mux__41 
       (.I0(\a_store_reg[0]_mux__19_n_0 ),
        .I1(\a_store_reg[0]_mux__20_n_0 ),
        .O(\a_store_reg[0]_mux__41_n_0 ),
        .S(delay_cycles[6]));
  MUXF8 \a_store_reg[0]_mux__42 
       (.I0(\a_store_reg[0]_mux__21_n_0 ),
        .I1(\a_store_reg[0]_mux__22_n_0 ),
        .O(\a_store_reg[0]_mux__42_n_0 ),
        .S(delay_cycles[6]));
  MUXF8 \a_store_reg[0]_mux__43 
       (.I0(\a_store_reg[0]_mux__23_n_0 ),
        .I1(\a_store_reg[0]_mux__24_n_0 ),
        .O(\a_store_reg[0]_mux__43_n_0 ),
        .S(delay_cycles[6]));
  MUXF8 \a_store_reg[0]_mux__44 
       (.I0(\a_store_reg[0]_mux__25_n_0 ),
        .I1(\a_store_reg[0]_mux__26_n_0 ),
        .O(\a_store_reg[0]_mux__44_n_0 ),
        .S(delay_cycles[6]));
  MUXF8 \a_store_reg[0]_mux__45 
       (.I0(\a_store_reg[0]_mux__27_n_0 ),
        .I1(\a_store_reg[0]_mux__28_n_0 ),
        .O(\a_store_reg[0]_mux__45_n_0 ),
        .S(delay_cycles[6]));
  MUXF8 \a_store_reg[0]_mux__46 
       (.I0(\a_store_reg[0]_mux__29_n_0 ),
        .I1(\a_store_reg[0]_mux__30_n_0 ),
        .O(\a_store_reg[0]_mux__46_n_0 ),
        .S(delay_cycles[6]));
  MUXF7 \a_store_reg[0]_mux__5 
       (.I0(\a_store_reg[0]_srl32__11_n_0 ),
        .I1(\a_store_reg[0]_srl32__12_n_0 ),
        .O(\a_store_reg[0]_mux__5_n_0 ),
        .S(delay_cycles[5]));
  MUXF7 \a_store_reg[0]_mux__6 
       (.I0(\a_store_reg[0]_srl32__13_n_0 ),
        .I1(\a_store_reg[0]_srl32__14_n_0 ),
        .O(\a_store_reg[0]_mux__6_n_0 ),
        .S(delay_cycles[5]));
  MUXF7 \a_store_reg[0]_mux__7 
       (.I0(\a_store_reg[0]_srl32__15_n_0 ),
        .I1(\a_store_reg[0]_srl32__16_n_0 ),
        .O(\a_store_reg[0]_mux__7_n_0 ),
        .S(delay_cycles[5]));
  MUXF7 \a_store_reg[0]_mux__8 
       (.I0(\a_store_reg[0]_srl32__17_n_0 ),
        .I1(\a_store_reg[0]_srl32__18_n_0 ),
        .O(\a_store_reg[0]_mux__8_n_0 ),
        .S(delay_cycles[5]));
  MUXF7 \a_store_reg[0]_mux__9 
       (.I0(\a_store_reg[0]_srl32__19_n_0 ),
        .I1(\a_store_reg[0]_srl32__20_n_0 ),
        .O(\a_store_reg[0]_mux__9_n_0 ),
        .S(delay_cycles[5]));
  (* srl_bus_name = "\U0/a_store_reg " *) 
  (* srl_name = "\U0/a_store_reg[0]_srl32 " *) 
  SRLC32E #(
    .INIT(32'h00000000)) 
    \a_store_reg[0]_srl32 
       (.A(delay_cycles[4:0]),
        .CE(1'b1),
        .CLK(clk),
        .D(a_in),
        .Q(\a_store_reg[0]_srl32_n_0 ),
        .Q31(\a_store_reg[0]_srl32_n_1 ));
  (* srl_bus_name = "\U0/a_store_reg " *) 
  (* srl_name = "\U0/a_store_reg[0]_srl32__0 " *) 
  SRLC32E #(
    .INIT(32'h00000000)) 
    \a_store_reg[0]_srl32__0 
       (.A(delay_cycles[4:0]),
        .CE(1'b1),
        .CLK(clk),
        .D(\a_store_reg[0]_srl32_n_1 ),
        .Q(\a_store_reg[0]_srl32__0_n_0 ),
        .Q31(\a_store_reg[0]_srl32__0_n_1 ));
  (* srl_bus_name = "\U0/a_store_reg " *) 
  (* srl_name = "\U0/a_store_reg[0]_srl32__1 " *) 
  SRLC32E #(
    .INIT(32'h00000000)) 
    \a_store_reg[0]_srl32__1 
       (.A(delay_cycles[4:0]),
        .CE(1'b1),
        .CLK(clk),
        .D(\a_store_reg[0]_srl32__0_n_1 ),
        .Q(\a_store_reg[0]_srl32__1_n_0 ),
        .Q31(\a_store_reg[0]_srl32__1_n_1 ));
  (* srl_bus_name = "\U0/a_store_reg " *) 
  (* srl_name = "\U0/a_store_reg[0]_srl32__10 " *) 
  SRLC32E #(
    .INIT(32'h00000000)) 
    \a_store_reg[0]_srl32__10 
       (.A(delay_cycles[4:0]),
        .CE(1'b1),
        .CLK(clk),
        .D(\a_store_reg[0]_srl32__9_n_1 ),
        .Q(\a_store_reg[0]_srl32__10_n_0 ),
        .Q31(\a_store_reg[0]_srl32__10_n_1 ));
  (* srl_bus_name = "\U0/a_store_reg " *) 
  (* srl_name = "\U0/a_store_reg[0]_srl32__11 " *) 
  SRLC32E #(
    .INIT(32'h00000000)) 
    \a_store_reg[0]_srl32__11 
       (.A(delay_cycles[4:0]),
        .CE(1'b1),
        .CLK(clk),
        .D(\a_store_reg[0]_srl32__10_n_1 ),
        .Q(\a_store_reg[0]_srl32__11_n_0 ),
        .Q31(\a_store_reg[0]_srl32__11_n_1 ));
  (* srl_bus_name = "\U0/a_store_reg " *) 
  (* srl_name = "\U0/a_store_reg[0]_srl32__12 " *) 
  SRLC32E #(
    .INIT(32'h00000000)) 
    \a_store_reg[0]_srl32__12 
       (.A(delay_cycles[4:0]),
        .CE(1'b1),
        .CLK(clk),
        .D(\a_store_reg[0]_srl32__11_n_1 ),
        .Q(\a_store_reg[0]_srl32__12_n_0 ),
        .Q31(\a_store_reg[0]_srl32__12_n_1 ));
  (* srl_bus_name = "\U0/a_store_reg " *) 
  (* srl_name = "\U0/a_store_reg[0]_srl32__13 " *) 
  SRLC32E #(
    .INIT(32'h00000000)) 
    \a_store_reg[0]_srl32__13 
       (.A(delay_cycles[4:0]),
        .CE(1'b1),
        .CLK(clk),
        .D(\a_store_reg[0]_srl32__12_n_1 ),
        .Q(\a_store_reg[0]_srl32__13_n_0 ),
        .Q31(\a_store_reg[0]_srl32__13_n_1 ));
  (* srl_bus_name = "\U0/a_store_reg " *) 
  (* srl_name = "\U0/a_store_reg[0]_srl32__14 " *) 
  SRLC32E #(
    .INIT(32'h00000000)) 
    \a_store_reg[0]_srl32__14 
       (.A(delay_cycles[4:0]),
        .CE(1'b1),
        .CLK(clk),
        .D(\a_store_reg[0]_srl32__13_n_1 ),
        .Q(\a_store_reg[0]_srl32__14_n_0 ),
        .Q31(\a_store_reg[0]_srl32__14_n_1 ));
  (* srl_bus_name = "\U0/a_store_reg " *) 
  (* srl_name = "\U0/a_store_reg[0]_srl32__15 " *) 
  SRLC32E #(
    .INIT(32'h00000000)) 
    \a_store_reg[0]_srl32__15 
       (.A(delay_cycles[4:0]),
        .CE(1'b1),
        .CLK(clk),
        .D(\a_store_reg[0]_srl32__14_n_1 ),
        .Q(\a_store_reg[0]_srl32__15_n_0 ),
        .Q31(\a_store_reg[0]_srl32__15_n_1 ));
  (* srl_bus_name = "\U0/a_store_reg " *) 
  (* srl_name = "\U0/a_store_reg[0]_srl32__16 " *) 
  SRLC32E #(
    .INIT(32'h00000000)) 
    \a_store_reg[0]_srl32__16 
       (.A(delay_cycles[4:0]),
        .CE(1'b1),
        .CLK(clk),
        .D(\a_store_reg[0]_srl32__15_n_1 ),
        .Q(\a_store_reg[0]_srl32__16_n_0 ),
        .Q31(\a_store_reg[0]_srl32__16_n_1 ));
  (* srl_bus_name = "\U0/a_store_reg " *) 
  (* srl_name = "\U0/a_store_reg[0]_srl32__17 " *) 
  SRLC32E #(
    .INIT(32'h00000000)) 
    \a_store_reg[0]_srl32__17 
       (.A(delay_cycles[4:0]),
        .CE(1'b1),
        .CLK(clk),
        .D(\a_store_reg[0]_srl32__16_n_1 ),
        .Q(\a_store_reg[0]_srl32__17_n_0 ),
        .Q31(\a_store_reg[0]_srl32__17_n_1 ));
  (* srl_bus_name = "\U0/a_store_reg " *) 
  (* srl_name = "\U0/a_store_reg[0]_srl32__18 " *) 
  SRLC32E #(
    .INIT(32'h00000000)) 
    \a_store_reg[0]_srl32__18 
       (.A(delay_cycles[4:0]),
        .CE(1'b1),
        .CLK(clk),
        .D(\a_store_reg[0]_srl32__17_n_1 ),
        .Q(\a_store_reg[0]_srl32__18_n_0 ),
        .Q31(\a_store_reg[0]_srl32__18_n_1 ));
  (* srl_bus_name = "\U0/a_store_reg " *) 
  (* srl_name = "\U0/a_store_reg[0]_srl32__19 " *) 
  SRLC32E #(
    .INIT(32'h00000000)) 
    \a_store_reg[0]_srl32__19 
       (.A(delay_cycles[4:0]),
        .CE(1'b1),
        .CLK(clk),
        .D(\a_store_reg[0]_srl32__18_n_1 ),
        .Q(\a_store_reg[0]_srl32__19_n_0 ),
        .Q31(\a_store_reg[0]_srl32__19_n_1 ));
  (* srl_bus_name = "\U0/a_store_reg " *) 
  (* srl_name = "\U0/a_store_reg[0]_srl32__2 " *) 
  SRLC32E #(
    .INIT(32'h00000000)) 
    \a_store_reg[0]_srl32__2 
       (.A(delay_cycles[4:0]),
        .CE(1'b1),
        .CLK(clk),
        .D(\a_store_reg[0]_srl32__1_n_1 ),
        .Q(\a_store_reg[0]_srl32__2_n_0 ),
        .Q31(\a_store_reg[0]_srl32__2_n_1 ));
  (* srl_bus_name = "\U0/a_store_reg " *) 
  (* srl_name = "\U0/a_store_reg[0]_srl32__20 " *) 
  SRLC32E #(
    .INIT(32'h00000000)) 
    \a_store_reg[0]_srl32__20 
       (.A(delay_cycles[4:0]),
        .CE(1'b1),
        .CLK(clk),
        .D(\a_store_reg[0]_srl32__19_n_1 ),
        .Q(\a_store_reg[0]_srl32__20_n_0 ),
        .Q31(\a_store_reg[0]_srl32__20_n_1 ));
  (* srl_bus_name = "\U0/a_store_reg " *) 
  (* srl_name = "\U0/a_store_reg[0]_srl32__21 " *) 
  SRLC32E #(
    .INIT(32'h00000000)) 
    \a_store_reg[0]_srl32__21 
       (.A(delay_cycles[4:0]),
        .CE(1'b1),
        .CLK(clk),
        .D(\a_store_reg[0]_srl32__20_n_1 ),
        .Q(\a_store_reg[0]_srl32__21_n_0 ),
        .Q31(\a_store_reg[0]_srl32__21_n_1 ));
  (* srl_bus_name = "\U0/a_store_reg " *) 
  (* srl_name = "\U0/a_store_reg[0]_srl32__22 " *) 
  SRLC32E #(
    .INIT(32'h00000000)) 
    \a_store_reg[0]_srl32__22 
       (.A(delay_cycles[4:0]),
        .CE(1'b1),
        .CLK(clk),
        .D(\a_store_reg[0]_srl32__21_n_1 ),
        .Q(\a_store_reg[0]_srl32__22_n_0 ),
        .Q31(\a_store_reg[0]_srl32__22_n_1 ));
  (* srl_bus_name = "\U0/a_store_reg " *) 
  (* srl_name = "\U0/a_store_reg[0]_srl32__23 " *) 
  SRLC32E #(
    .INIT(32'h00000000)) 
    \a_store_reg[0]_srl32__23 
       (.A(delay_cycles[4:0]),
        .CE(1'b1),
        .CLK(clk),
        .D(\a_store_reg[0]_srl32__22_n_1 ),
        .Q(\a_store_reg[0]_srl32__23_n_0 ),
        .Q31(\a_store_reg[0]_srl32__23_n_1 ));
  (* srl_bus_name = "\U0/a_store_reg " *) 
  (* srl_name = "\U0/a_store_reg[0]_srl32__24 " *) 
  SRLC32E #(
    .INIT(32'h00000000)) 
    \a_store_reg[0]_srl32__24 
       (.A(delay_cycles[4:0]),
        .CE(1'b1),
        .CLK(clk),
        .D(\a_store_reg[0]_srl32__23_n_1 ),
        .Q(\a_store_reg[0]_srl32__24_n_0 ),
        .Q31(\a_store_reg[0]_srl32__24_n_1 ));
  (* srl_bus_name = "\U0/a_store_reg " *) 
  (* srl_name = "\U0/a_store_reg[0]_srl32__25 " *) 
  SRLC32E #(
    .INIT(32'h00000000)) 
    \a_store_reg[0]_srl32__25 
       (.A(delay_cycles[4:0]),
        .CE(1'b1),
        .CLK(clk),
        .D(\a_store_reg[0]_srl32__24_n_1 ),
        .Q(\a_store_reg[0]_srl32__25_n_0 ),
        .Q31(\a_store_reg[0]_srl32__25_n_1 ));
  (* srl_bus_name = "\U0/a_store_reg " *) 
  (* srl_name = "\U0/a_store_reg[0]_srl32__26 " *) 
  SRLC32E #(
    .INIT(32'h00000000)) 
    \a_store_reg[0]_srl32__26 
       (.A(delay_cycles[4:0]),
        .CE(1'b1),
        .CLK(clk),
        .D(\a_store_reg[0]_srl32__25_n_1 ),
        .Q(\a_store_reg[0]_srl32__26_n_0 ),
        .Q31(\a_store_reg[0]_srl32__26_n_1 ));
  (* srl_bus_name = "\U0/a_store_reg " *) 
  (* srl_name = "\U0/a_store_reg[0]_srl32__27 " *) 
  SRLC32E #(
    .INIT(32'h00000000)) 
    \a_store_reg[0]_srl32__27 
       (.A(delay_cycles[4:0]),
        .CE(1'b1),
        .CLK(clk),
        .D(\a_store_reg[0]_srl32__26_n_1 ),
        .Q(\a_store_reg[0]_srl32__27_n_0 ),
        .Q31(\a_store_reg[0]_srl32__27_n_1 ));
  (* srl_bus_name = "\U0/a_store_reg " *) 
  (* srl_name = "\U0/a_store_reg[0]_srl32__28 " *) 
  SRLC32E #(
    .INIT(32'h00000000)) 
    \a_store_reg[0]_srl32__28 
       (.A(delay_cycles[4:0]),
        .CE(1'b1),
        .CLK(clk),
        .D(\a_store_reg[0]_srl32__27_n_1 ),
        .Q(\a_store_reg[0]_srl32__28_n_0 ),
        .Q31(\a_store_reg[0]_srl32__28_n_1 ));
  (* srl_bus_name = "\U0/a_store_reg " *) 
  (* srl_name = "\U0/a_store_reg[0]_srl32__29 " *) 
  SRLC32E #(
    .INIT(32'h00000000)) 
    \a_store_reg[0]_srl32__29 
       (.A(delay_cycles[4:0]),
        .CE(1'b1),
        .CLK(clk),
        .D(\a_store_reg[0]_srl32__28_n_1 ),
        .Q(\a_store_reg[0]_srl32__29_n_0 ),
        .Q31(\a_store_reg[0]_srl32__29_n_1 ));
  (* srl_bus_name = "\U0/a_store_reg " *) 
  (* srl_name = "\U0/a_store_reg[0]_srl32__3 " *) 
  SRLC32E #(
    .INIT(32'h00000000)) 
    \a_store_reg[0]_srl32__3 
       (.A(delay_cycles[4:0]),
        .CE(1'b1),
        .CLK(clk),
        .D(\a_store_reg[0]_srl32__2_n_1 ),
        .Q(\a_store_reg[0]_srl32__3_n_0 ),
        .Q31(\a_store_reg[0]_srl32__3_n_1 ));
  (* srl_bus_name = "\U0/a_store_reg " *) 
  (* srl_name = "\U0/a_store_reg[0]_srl32__30 " *) 
  SRLC32E #(
    .INIT(32'h00000000)) 
    \a_store_reg[0]_srl32__30 
       (.A(delay_cycles[4:0]),
        .CE(1'b1),
        .CLK(clk),
        .D(\a_store_reg[0]_srl32__29_n_1 ),
        .Q(\a_store_reg[0]_srl32__30_n_0 ),
        .Q31(\a_store_reg[0]_srl32__30_n_1 ));
  (* srl_bus_name = "\U0/a_store_reg " *) 
  (* srl_name = "\U0/a_store_reg[0]_srl32__31 " *) 
  SRLC32E #(
    .INIT(32'h00000000)) 
    \a_store_reg[0]_srl32__31 
       (.A(delay_cycles[4:0]),
        .CE(1'b1),
        .CLK(clk),
        .D(\a_store_reg[0]_srl32__30_n_1 ),
        .Q(\a_store_reg[0]_srl32__31_n_0 ),
        .Q31(\a_store_reg[0]_srl32__31_n_1 ));
  (* srl_bus_name = "\U0/a_store_reg " *) 
  (* srl_name = "\U0/a_store_reg[0]_srl32__32 " *) 
  SRLC32E #(
    .INIT(32'h00000000)) 
    \a_store_reg[0]_srl32__32 
       (.A(delay_cycles[4:0]),
        .CE(1'b1),
        .CLK(clk),
        .D(\a_store_reg[0]_srl32__31_n_1 ),
        .Q(\a_store_reg[0]_srl32__32_n_0 ),
        .Q31(\a_store_reg[0]_srl32__32_n_1 ));
  (* srl_bus_name = "\U0/a_store_reg " *) 
  (* srl_name = "\U0/a_store_reg[0]_srl32__33 " *) 
  SRLC32E #(
    .INIT(32'h00000000)) 
    \a_store_reg[0]_srl32__33 
       (.A(delay_cycles[4:0]),
        .CE(1'b1),
        .CLK(clk),
        .D(\a_store_reg[0]_srl32__32_n_1 ),
        .Q(\a_store_reg[0]_srl32__33_n_0 ),
        .Q31(\a_store_reg[0]_srl32__33_n_1 ));
  (* srl_bus_name = "\U0/a_store_reg " *) 
  (* srl_name = "\U0/a_store_reg[0]_srl32__34 " *) 
  SRLC32E #(
    .INIT(32'h00000000)) 
    \a_store_reg[0]_srl32__34 
       (.A(delay_cycles[4:0]),
        .CE(1'b1),
        .CLK(clk),
        .D(\a_store_reg[0]_srl32__33_n_1 ),
        .Q(\a_store_reg[0]_srl32__34_n_0 ),
        .Q31(\a_store_reg[0]_srl32__34_n_1 ));
  (* srl_bus_name = "\U0/a_store_reg " *) 
  (* srl_name = "\U0/a_store_reg[0]_srl32__35 " *) 
  SRLC32E #(
    .INIT(32'h00000000)) 
    \a_store_reg[0]_srl32__35 
       (.A(delay_cycles[4:0]),
        .CE(1'b1),
        .CLK(clk),
        .D(\a_store_reg[0]_srl32__34_n_1 ),
        .Q(\a_store_reg[0]_srl32__35_n_0 ),
        .Q31(\a_store_reg[0]_srl32__35_n_1 ));
  (* srl_bus_name = "\U0/a_store_reg " *) 
  (* srl_name = "\U0/a_store_reg[0]_srl32__36 " *) 
  SRLC32E #(
    .INIT(32'h00000000)) 
    \a_store_reg[0]_srl32__36 
       (.A(delay_cycles[4:0]),
        .CE(1'b1),
        .CLK(clk),
        .D(\a_store_reg[0]_srl32__35_n_1 ),
        .Q(\a_store_reg[0]_srl32__36_n_0 ),
        .Q31(\a_store_reg[0]_srl32__36_n_1 ));
  (* srl_bus_name = "\U0/a_store_reg " *) 
  (* srl_name = "\U0/a_store_reg[0]_srl32__37 " *) 
  SRLC32E #(
    .INIT(32'h00000000)) 
    \a_store_reg[0]_srl32__37 
       (.A(delay_cycles[4:0]),
        .CE(1'b1),
        .CLK(clk),
        .D(\a_store_reg[0]_srl32__36_n_1 ),
        .Q(\a_store_reg[0]_srl32__37_n_0 ),
        .Q31(\a_store_reg[0]_srl32__37_n_1 ));
  (* srl_bus_name = "\U0/a_store_reg " *) 
  (* srl_name = "\U0/a_store_reg[0]_srl32__38 " *) 
  SRLC32E #(
    .INIT(32'h00000000)) 
    \a_store_reg[0]_srl32__38 
       (.A(delay_cycles[4:0]),
        .CE(1'b1),
        .CLK(clk),
        .D(\a_store_reg[0]_srl32__37_n_1 ),
        .Q(\a_store_reg[0]_srl32__38_n_0 ),
        .Q31(\a_store_reg[0]_srl32__38_n_1 ));
  (* srl_bus_name = "\U0/a_store_reg " *) 
  (* srl_name = "\U0/a_store_reg[0]_srl32__39 " *) 
  SRLC32E #(
    .INIT(32'h00000000)) 
    \a_store_reg[0]_srl32__39 
       (.A(delay_cycles[4:0]),
        .CE(1'b1),
        .CLK(clk),
        .D(\a_store_reg[0]_srl32__38_n_1 ),
        .Q(\a_store_reg[0]_srl32__39_n_0 ),
        .Q31(\a_store_reg[0]_srl32__39_n_1 ));
  (* srl_bus_name = "\U0/a_store_reg " *) 
  (* srl_name = "\U0/a_store_reg[0]_srl32__4 " *) 
  SRLC32E #(
    .INIT(32'h00000000)) 
    \a_store_reg[0]_srl32__4 
       (.A(delay_cycles[4:0]),
        .CE(1'b1),
        .CLK(clk),
        .D(\a_store_reg[0]_srl32__3_n_1 ),
        .Q(\a_store_reg[0]_srl32__4_n_0 ),
        .Q31(\a_store_reg[0]_srl32__4_n_1 ));
  (* srl_bus_name = "\U0/a_store_reg " *) 
  (* srl_name = "\U0/a_store_reg[0]_srl32__40 " *) 
  SRLC32E #(
    .INIT(32'h00000000)) 
    \a_store_reg[0]_srl32__40 
       (.A(delay_cycles[4:0]),
        .CE(1'b1),
        .CLK(clk),
        .D(\a_store_reg[0]_srl32__39_n_1 ),
        .Q(\a_store_reg[0]_srl32__40_n_0 ),
        .Q31(\a_store_reg[0]_srl32__40_n_1 ));
  (* srl_bus_name = "\U0/a_store_reg " *) 
  (* srl_name = "\U0/a_store_reg[0]_srl32__41 " *) 
  SRLC32E #(
    .INIT(32'h00000000)) 
    \a_store_reg[0]_srl32__41 
       (.A(delay_cycles[4:0]),
        .CE(1'b1),
        .CLK(clk),
        .D(\a_store_reg[0]_srl32__40_n_1 ),
        .Q(\a_store_reg[0]_srl32__41_n_0 ),
        .Q31(\a_store_reg[0]_srl32__41_n_1 ));
  (* srl_bus_name = "\U0/a_store_reg " *) 
  (* srl_name = "\U0/a_store_reg[0]_srl32__42 " *) 
  SRLC32E #(
    .INIT(32'h00000000)) 
    \a_store_reg[0]_srl32__42 
       (.A(delay_cycles[4:0]),
        .CE(1'b1),
        .CLK(clk),
        .D(\a_store_reg[0]_srl32__41_n_1 ),
        .Q(\a_store_reg[0]_srl32__42_n_0 ),
        .Q31(\a_store_reg[0]_srl32__42_n_1 ));
  (* srl_bus_name = "\U0/a_store_reg " *) 
  (* srl_name = "\U0/a_store_reg[0]_srl32__43 " *) 
  SRLC32E #(
    .INIT(32'h00000000)) 
    \a_store_reg[0]_srl32__43 
       (.A(delay_cycles[4:0]),
        .CE(1'b1),
        .CLK(clk),
        .D(\a_store_reg[0]_srl32__42_n_1 ),
        .Q(\a_store_reg[0]_srl32__43_n_0 ),
        .Q31(\a_store_reg[0]_srl32__43_n_1 ));
  (* srl_bus_name = "\U0/a_store_reg " *) 
  (* srl_name = "\U0/a_store_reg[0]_srl32__44 " *) 
  SRLC32E #(
    .INIT(32'h00000000)) 
    \a_store_reg[0]_srl32__44 
       (.A(delay_cycles[4:0]),
        .CE(1'b1),
        .CLK(clk),
        .D(\a_store_reg[0]_srl32__43_n_1 ),
        .Q(\a_store_reg[0]_srl32__44_n_0 ),
        .Q31(\a_store_reg[0]_srl32__44_n_1 ));
  (* srl_bus_name = "\U0/a_store_reg " *) 
  (* srl_name = "\U0/a_store_reg[0]_srl32__45 " *) 
  SRLC32E #(
    .INIT(32'h00000000)) 
    \a_store_reg[0]_srl32__45 
       (.A(delay_cycles[4:0]),
        .CE(1'b1),
        .CLK(clk),
        .D(\a_store_reg[0]_srl32__44_n_1 ),
        .Q(\a_store_reg[0]_srl32__45_n_0 ),
        .Q31(\a_store_reg[0]_srl32__45_n_1 ));
  (* srl_bus_name = "\U0/a_store_reg " *) 
  (* srl_name = "\U0/a_store_reg[0]_srl32__46 " *) 
  SRLC32E #(
    .INIT(32'h00000000)) 
    \a_store_reg[0]_srl32__46 
       (.A(delay_cycles[4:0]),
        .CE(1'b1),
        .CLK(clk),
        .D(\a_store_reg[0]_srl32__45_n_1 ),
        .Q(\a_store_reg[0]_srl32__46_n_0 ),
        .Q31(\a_store_reg[0]_srl32__46_n_1 ));
  (* srl_bus_name = "\U0/a_store_reg " *) 
  (* srl_name = "\U0/a_store_reg[0]_srl32__47 " *) 
  SRLC32E #(
    .INIT(32'h00000000)) 
    \a_store_reg[0]_srl32__47 
       (.A(delay_cycles[4:0]),
        .CE(1'b1),
        .CLK(clk),
        .D(\a_store_reg[0]_srl32__46_n_1 ),
        .Q(\a_store_reg[0]_srl32__47_n_0 ),
        .Q31(\a_store_reg[0]_srl32__47_n_1 ));
  (* srl_bus_name = "\U0/a_store_reg " *) 
  (* srl_name = "\U0/a_store_reg[0]_srl32__48 " *) 
  SRLC32E #(
    .INIT(32'h00000000)) 
    \a_store_reg[0]_srl32__48 
       (.A(delay_cycles[4:0]),
        .CE(1'b1),
        .CLK(clk),
        .D(\a_store_reg[0]_srl32__47_n_1 ),
        .Q(\a_store_reg[0]_srl32__48_n_0 ),
        .Q31(\a_store_reg[0]_srl32__48_n_1 ));
  (* srl_bus_name = "\U0/a_store_reg " *) 
  (* srl_name = "\U0/a_store_reg[0]_srl32__49 " *) 
  SRLC32E #(
    .INIT(32'h00000000)) 
    \a_store_reg[0]_srl32__49 
       (.A(delay_cycles[4:0]),
        .CE(1'b1),
        .CLK(clk),
        .D(\a_store_reg[0]_srl32__48_n_1 ),
        .Q(\a_store_reg[0]_srl32__49_n_0 ),
        .Q31(\a_store_reg[0]_srl32__49_n_1 ));
  (* srl_bus_name = "\U0/a_store_reg " *) 
  (* srl_name = "\U0/a_store_reg[0]_srl32__5 " *) 
  SRLC32E #(
    .INIT(32'h00000000)) 
    \a_store_reg[0]_srl32__5 
       (.A(delay_cycles[4:0]),
        .CE(1'b1),
        .CLK(clk),
        .D(\a_store_reg[0]_srl32__4_n_1 ),
        .Q(\a_store_reg[0]_srl32__5_n_0 ),
        .Q31(\a_store_reg[0]_srl32__5_n_1 ));
  (* srl_bus_name = "\U0/a_store_reg " *) 
  (* srl_name = "\U0/a_store_reg[0]_srl32__50 " *) 
  SRLC32E #(
    .INIT(32'h00000000)) 
    \a_store_reg[0]_srl32__50 
       (.A(delay_cycles[4:0]),
        .CE(1'b1),
        .CLK(clk),
        .D(\a_store_reg[0]_srl32__49_n_1 ),
        .Q(\a_store_reg[0]_srl32__50_n_0 ),
        .Q31(\a_store_reg[0]_srl32__50_n_1 ));
  (* srl_bus_name = "\U0/a_store_reg " *) 
  (* srl_name = "\U0/a_store_reg[0]_srl32__51 " *) 
  SRLC32E #(
    .INIT(32'h00000000)) 
    \a_store_reg[0]_srl32__51 
       (.A(delay_cycles[4:0]),
        .CE(1'b1),
        .CLK(clk),
        .D(\a_store_reg[0]_srl32__50_n_1 ),
        .Q(\a_store_reg[0]_srl32__51_n_0 ),
        .Q31(\a_store_reg[0]_srl32__51_n_1 ));
  (* srl_bus_name = "\U0/a_store_reg " *) 
  (* srl_name = "\U0/a_store_reg[0]_srl32__52 " *) 
  SRLC32E #(
    .INIT(32'h00000000)) 
    \a_store_reg[0]_srl32__52 
       (.A(delay_cycles[4:0]),
        .CE(1'b1),
        .CLK(clk),
        .D(\a_store_reg[0]_srl32__51_n_1 ),
        .Q(\a_store_reg[0]_srl32__52_n_0 ),
        .Q31(\a_store_reg[0]_srl32__52_n_1 ));
  (* srl_bus_name = "\U0/a_store_reg " *) 
  (* srl_name = "\U0/a_store_reg[0]_srl32__53 " *) 
  SRLC32E #(
    .INIT(32'h00000000)) 
    \a_store_reg[0]_srl32__53 
       (.A(delay_cycles[4:0]),
        .CE(1'b1),
        .CLK(clk),
        .D(\a_store_reg[0]_srl32__52_n_1 ),
        .Q(\a_store_reg[0]_srl32__53_n_0 ),
        .Q31(\a_store_reg[0]_srl32__53_n_1 ));
  (* srl_bus_name = "\U0/a_store_reg " *) 
  (* srl_name = "\U0/a_store_reg[0]_srl32__54 " *) 
  SRLC32E #(
    .INIT(32'h00000000)) 
    \a_store_reg[0]_srl32__54 
       (.A(delay_cycles[4:0]),
        .CE(1'b1),
        .CLK(clk),
        .D(\a_store_reg[0]_srl32__53_n_1 ),
        .Q(\a_store_reg[0]_srl32__54_n_0 ),
        .Q31(\a_store_reg[0]_srl32__54_n_1 ));
  (* srl_bus_name = "\U0/a_store_reg " *) 
  (* srl_name = "\U0/a_store_reg[0]_srl32__55 " *) 
  SRLC32E #(
    .INIT(32'h00000000)) 
    \a_store_reg[0]_srl32__55 
       (.A(delay_cycles[4:0]),
        .CE(1'b1),
        .CLK(clk),
        .D(\a_store_reg[0]_srl32__54_n_1 ),
        .Q(\a_store_reg[0]_srl32__55_n_0 ),
        .Q31(\a_store_reg[0]_srl32__55_n_1 ));
  (* srl_bus_name = "\U0/a_store_reg " *) 
  (* srl_name = "\U0/a_store_reg[0]_srl32__56 " *) 
  SRLC32E #(
    .INIT(32'h00000000)) 
    \a_store_reg[0]_srl32__56 
       (.A(delay_cycles[4:0]),
        .CE(1'b1),
        .CLK(clk),
        .D(\a_store_reg[0]_srl32__55_n_1 ),
        .Q(\a_store_reg[0]_srl32__56_n_0 ),
        .Q31(\a_store_reg[0]_srl32__56_n_1 ));
  (* srl_bus_name = "\U0/a_store_reg " *) 
  (* srl_name = "\U0/a_store_reg[0]_srl32__57 " *) 
  SRLC32E #(
    .INIT(32'h00000000)) 
    \a_store_reg[0]_srl32__57 
       (.A(delay_cycles[4:0]),
        .CE(1'b1),
        .CLK(clk),
        .D(\a_store_reg[0]_srl32__56_n_1 ),
        .Q(\a_store_reg[0]_srl32__57_n_0 ),
        .Q31(\a_store_reg[0]_srl32__57_n_1 ));
  (* srl_bus_name = "\U0/a_store_reg " *) 
  (* srl_name = "\U0/a_store_reg[0]_srl32__58 " *) 
  SRLC32E #(
    .INIT(32'h00000000)) 
    \a_store_reg[0]_srl32__58 
       (.A(delay_cycles[4:0]),
        .CE(1'b1),
        .CLK(clk),
        .D(\a_store_reg[0]_srl32__57_n_1 ),
        .Q(\a_store_reg[0]_srl32__58_n_0 ),
        .Q31(\a_store_reg[0]_srl32__58_n_1 ));
  (* srl_bus_name = "\U0/a_store_reg " *) 
  (* srl_name = "\U0/a_store_reg[0]_srl32__59 " *) 
  SRLC32E #(
    .INIT(32'h00000000)) 
    \a_store_reg[0]_srl32__59 
       (.A(delay_cycles[4:0]),
        .CE(1'b1),
        .CLK(clk),
        .D(\a_store_reg[0]_srl32__58_n_1 ),
        .Q(\a_store_reg[0]_srl32__59_n_0 ),
        .Q31(\a_store_reg[0]_srl32__59_n_1 ));
  (* srl_bus_name = "\U0/a_store_reg " *) 
  (* srl_name = "\U0/a_store_reg[0]_srl32__6 " *) 
  SRLC32E #(
    .INIT(32'h00000000)) 
    \a_store_reg[0]_srl32__6 
       (.A(delay_cycles[4:0]),
        .CE(1'b1),
        .CLK(clk),
        .D(\a_store_reg[0]_srl32__5_n_1 ),
        .Q(\a_store_reg[0]_srl32__6_n_0 ),
        .Q31(\a_store_reg[0]_srl32__6_n_1 ));
  (* srl_bus_name = "\U0/a_store_reg " *) 
  (* srl_name = "\U0/a_store_reg[0]_srl32__60 " *) 
  SRLC32E #(
    .INIT(32'h00000000)) 
    \a_store_reg[0]_srl32__60 
       (.A(delay_cycles[4:0]),
        .CE(1'b1),
        .CLK(clk),
        .D(\a_store_reg[0]_srl32__59_n_1 ),
        .Q(\a_store_reg[0]_srl32__60_n_0 ),
        .Q31(\a_store_reg[0]_srl32__60_n_1 ));
  (* srl_bus_name = "\U0/a_store_reg " *) 
  (* srl_name = "\U0/a_store_reg[0]_srl32__61 " *) 
  SRLC32E #(
    .INIT(32'h00000000)) 
    \a_store_reg[0]_srl32__61 
       (.A(delay_cycles[4:0]),
        .CE(1'b1),
        .CLK(clk),
        .D(\a_store_reg[0]_srl32__60_n_1 ),
        .Q(\a_store_reg[0]_srl32__61_n_0 ),
        .Q31(\a_store_reg[0]_srl32__61_n_1 ));
  (* srl_bus_name = "\U0/a_store_reg " *) 
  (* srl_name = "\U0/a_store_reg[0]_srl32__62 " *) 
  SRLC32E #(
    .INIT(32'h00000000)) 
    \a_store_reg[0]_srl32__62 
       (.A(delay_cycles[4:0]),
        .CE(1'b1),
        .CLK(clk),
        .D(\a_store_reg[0]_srl32__61_n_1 ),
        .Q(\a_store_reg[0]_srl32__62_n_0 ),
        .Q31(\NLW_a_store_reg[0]_srl32__62_Q31_UNCONNECTED ));
  (* srl_bus_name = "\U0/a_store_reg " *) 
  (* srl_name = "\U0/a_store_reg[0]_srl32__7 " *) 
  SRLC32E #(
    .INIT(32'h00000000)) 
    \a_store_reg[0]_srl32__7 
       (.A(delay_cycles[4:0]),
        .CE(1'b1),
        .CLK(clk),
        .D(\a_store_reg[0]_srl32__6_n_1 ),
        .Q(\a_store_reg[0]_srl32__7_n_0 ),
        .Q31(\a_store_reg[0]_srl32__7_n_1 ));
  (* srl_bus_name = "\U0/a_store_reg " *) 
  (* srl_name = "\U0/a_store_reg[0]_srl32__8 " *) 
  SRLC32E #(
    .INIT(32'h00000000)) 
    \a_store_reg[0]_srl32__8 
       (.A(delay_cycles[4:0]),
        .CE(1'b1),
        .CLK(clk),
        .D(\a_store_reg[0]_srl32__7_n_1 ),
        .Q(\a_store_reg[0]_srl32__8_n_0 ),
        .Q31(\a_store_reg[0]_srl32__8_n_1 ));
  (* srl_bus_name = "\U0/a_store_reg " *) 
  (* srl_name = "\U0/a_store_reg[0]_srl32__9 " *) 
  SRLC32E #(
    .INIT(32'h00000000)) 
    \a_store_reg[0]_srl32__9 
       (.A(delay_cycles[4:0]),
        .CE(1'b1),
        .CLK(clk),
        .D(\a_store_reg[0]_srl32__8_n_1 ),
        .Q(\a_store_reg[0]_srl32__9_n_0 ),
        .Q31(\a_store_reg[0]_srl32__9_n_1 ));
endmodule
`ifndef GLBL
`define GLBL
`timescale  1 ps / 1 ps

module glbl ();

    parameter ROC_WIDTH = 100000;
    parameter TOC_WIDTH = 0;
    parameter GRES_WIDTH = 10000;
    parameter GRES_START = 10000;

//--------   STARTUP Globals --------------
    wire GSR;
    wire GTS;
    wire GWE;
    wire PRLD;
    wire GRESTORE;
    tri1 p_up_tmp;
    tri (weak1, strong0) PLL_LOCKG = p_up_tmp;

    wire PROGB_GLBL;
    wire CCLKO_GLBL;
    wire FCSBO_GLBL;
    wire [3:0] DO_GLBL;
    wire [3:0] DI_GLBL;
   
    reg GSR_int;
    reg GTS_int;
    reg PRLD_int;
    reg GRESTORE_int;

//--------   JTAG Globals --------------
    wire JTAG_TDO_GLBL;
    wire JTAG_TCK_GLBL;
    wire JTAG_TDI_GLBL;
    wire JTAG_TMS_GLBL;
    wire JTAG_TRST_GLBL;

    reg JTAG_CAPTURE_GLBL;
    reg JTAG_RESET_GLBL;
    reg JTAG_SHIFT_GLBL;
    reg JTAG_UPDATE_GLBL;
    reg JTAG_RUNTEST_GLBL;

    reg JTAG_SEL1_GLBL = 0;
    reg JTAG_SEL2_GLBL = 0 ;
    reg JTAG_SEL3_GLBL = 0;
    reg JTAG_SEL4_GLBL = 0;

    reg JTAG_USER_TDO1_GLBL = 1'bz;
    reg JTAG_USER_TDO2_GLBL = 1'bz;
    reg JTAG_USER_TDO3_GLBL = 1'bz;
    reg JTAG_USER_TDO4_GLBL = 1'bz;

    assign (strong1, weak0) GSR = GSR_int;
    assign (strong1, weak0) GTS = GTS_int;
    assign (weak1, weak0) PRLD = PRLD_int;
    assign (strong1, weak0) GRESTORE = GRESTORE_int;

    initial begin
	GSR_int = 1'b1;
	PRLD_int = 1'b1;
	#(ROC_WIDTH)
	GSR_int = 1'b0;
	PRLD_int = 1'b0;
    end

    initial begin
	GTS_int = 1'b1;
	#(TOC_WIDTH)
	GTS_int = 1'b0;
    end

    initial begin 
	GRESTORE_int = 1'b0;
	#(GRES_START);
	GRESTORE_int = 1'b1;
	#(GRES_WIDTH);
	GRESTORE_int = 1'b0;
    end

endmodule
`endif
