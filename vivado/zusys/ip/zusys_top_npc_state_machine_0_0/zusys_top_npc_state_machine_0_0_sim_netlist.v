// Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// --------------------------------------------------------------------------------
// Tool Version: Vivado v.2020.1.1 (win64) Build 2960000 Wed Aug  5 22:57:20 MDT 2020
// Date        : Fri Jan 28 14:48:00 2022
// Host        : enc177112 running 64-bit major release  (build 9200)
// Command     : write_verilog -force -mode funcsim
//               c:/GIT/UltraZohm/software/ultrazohm_sw_develop/vivado/zusys/ip/zusys_top_npc_state_machine_0_0/zusys_top_npc_state_machine_0_0_sim_netlist.v
// Design      : zusys_top_npc_state_machine_0_0
// Purpose     : This verilog netlist is a functional simulation representation of the design and should not be modified
//               or synthesized. This netlist cannot be used for SDF annotated simulation.
// Device      : xczu9eg-ffvc900-1-e
// --------------------------------------------------------------------------------
`timescale 1 ps / 1 ps

(* CHECK_LICENSE_TYPE = "zusys_top_npc_state_machine_0_0,top_npc_state_machine,{}" *) (* downgradeipidentifiedwarnings = "yes" *) (* ip_definition_source = "module_ref" *) 
(* x_core_info = "top_npc_state_machine,Vivado 2020.1.1" *) 
(* NotValidForBitStream *)
module zusys_top_npc_state_machine_0_0
   (clock,
    enable,
    switching_signals,
    deadtime,
    A_S1,
    A_S2,
    A_S3,
    A_S4,
    B_S1,
    B_S2,
    B_S3,
    B_S4,
    C_S1,
    C_S2,
    C_S3,
    C_S4,
    A_phase_off,
    B_phase_off,
    C_phase_off);
  (* x_interface_info = "xilinx.com:signal:clock:1.0 clock CLK" *) (* x_interface_parameter = "XIL_INTERFACENAME clock, FREQ_HZ 100000000, FREQ_TOLERANCE_HZ 0, PHASE 0.000, CLK_DOMAIN zusys_zynq_ultra_ps_e_0_0_pl_clk0, INSERT_VIP 0" *) input clock;
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

  wire A_S1;
  wire A_S2;
  wire A_S3;
  wire A_S4;
  wire A_phase_off;
  wire B_S1;
  wire B_S2;
  wire B_S3;
  wire B_S4;
  wire B_phase_off;
  wire C_S1;
  wire C_S2;
  wire C_S3;
  wire C_S4;
  wire C_phase_off;
  wire clock;
  wire [9:0]deadtime;
  wire enable;
  wire [5:0]switching_signals;

  zusys_top_npc_state_machine_0_0_top_npc_state_machine U0
       (.A_S1(A_S1),
        .A_S2(A_S2),
        .A_S3(A_S3),
        .A_S4(A_S4),
        .A_phase_off(A_phase_off),
        .B_S1(B_S1),
        .B_S2(B_S2),
        .B_S3(B_S3),
        .B_S4(B_S4),
        .B_phase_off(B_phase_off),
        .C_S1(C_S1),
        .C_S2(C_S2),
        .C_S3(C_S3),
        .C_S4(C_S4),
        .C_phase_off(C_phase_off),
        .clock(clock),
        .deadtime(deadtime),
        .enable(enable),
        .switching_signals(switching_signals));
endmodule

(* ORIG_REF_NAME = "npc_phase_state_machine" *) 
module zusys_top_npc_state_machine_0_0_npc_phase_state_machine
   (Q,
    A_S2,
    A_S3,
    switching_signals,
    enable,
    deadtime,
    clock);
  output [2:0]Q;
  output A_S2;
  output A_S3;
  input [1:0]switching_signals;
  input enable;
  input [9:0]deadtime;
  input clock;

  wire A_S2;
  wire A_S3;
  wire \FSM_onehot_phase_state[0]_i_1_n_0 ;
  wire \FSM_onehot_phase_state[0]_i_2_n_0 ;
  wire \FSM_onehot_phase_state[1]_i_1_n_0 ;
  wire \FSM_onehot_phase_state[1]_i_2_n_0 ;
  wire \FSM_onehot_phase_state[2]_i_1_n_0 ;
  wire \FSM_onehot_phase_state[2]_i_2_n_0 ;
  wire \FSM_onehot_phase_state[3]_i_1_n_0 ;
  wire \FSM_onehot_phase_state[3]_i_2_n_0 ;
  wire \FSM_onehot_phase_state[3]_i_3_n_0 ;
  wire \FSM_onehot_phase_state[4]_i_1_n_0 ;
  wire \FSM_onehot_phase_state[5]_i_1_n_0 ;
  wire \FSM_onehot_phase_state[5]_i_2_n_0 ;
  wire \FSM_onehot_phase_state_reg_n_0_[0] ;
  wire [2:0]Q;
  wire clock;
  wire [9:0]counter;
  wire \counter[0]_i_1_n_0 ;
  wire \counter[1]_i_1_n_0 ;
  wire \counter[2]_i_1_n_0 ;
  wire \counter[3]_i_1_n_0 ;
  wire \counter[3]_i_2_n_0 ;
  wire \counter[4]_i_1_n_0 ;
  wire \counter[4]_i_2_n_0 ;
  wire \counter[5]_i_1_n_0 ;
  wire \counter[5]_i_2_n_0 ;
  wire \counter[6]_i_1_n_0 ;
  wire \counter[6]_i_2_n_0 ;
  wire \counter[7]_i_1_n_0 ;
  wire \counter[7]_i_2_n_0 ;
  wire \counter[8]_i_1_n_0 ;
  wire \counter[8]_i_2_n_0 ;
  wire \counter[9]_i_2_n_0 ;
  wire \counter[9]_i_3_n_0 ;
  wire \counter[9]_i_4_n_0 ;
  wire \counter[9]_i_5_n_0 ;
  wire \counter[9]_i_6_n_0 ;
  wire \counter[9]_i_7_n_0 ;
  wire counter_0;
  wire [9:0]deadtime;
  wire enable;
  wire p_1_in;
  wire p_2_in;
  wire [1:0]switching_signals;

  (* SOFT_HLUTNM = "soft_lutpair7" *) 
  LUT3 #(
    .INIT(8'hFE)) 
    A_S2_INST_0
       (.I0(Q[2]),
        .I1(p_1_in),
        .I2(\FSM_onehot_phase_state_reg_n_0_[0] ),
        .O(A_S2));
  (* SOFT_HLUTNM = "soft_lutpair7" *) 
  LUT3 #(
    .INIT(8'hFE)) 
    A_S3_INST_0
       (.I0(Q[1]),
        .I1(p_1_in),
        .I2(p_2_in),
        .O(A_S3));
  LUT5 #(
    .INIT(32'hFFD8D8D8)) 
    \FSM_onehot_phase_state[0]_i_1 
       (.I0(\FSM_onehot_phase_state[0]_i_2_n_0 ),
        .I1(Q[2]),
        .I2(\FSM_onehot_phase_state[3]_i_3_n_0 ),
        .I3(\FSM_onehot_phase_state_reg_n_0_[0] ),
        .I4(\FSM_onehot_phase_state[5]_i_2_n_0 ),
        .O(\FSM_onehot_phase_state[0]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair0" *) 
  LUT3 #(
    .INIT(8'h7F)) 
    \FSM_onehot_phase_state[0]_i_2 
       (.I0(switching_signals[1]),
        .I1(switching_signals[0]),
        .I2(enable),
        .O(\FSM_onehot_phase_state[0]_i_2_n_0 ));
  LUT5 #(
    .INIT(32'hFFD8D8D8)) 
    \FSM_onehot_phase_state[1]_i_1 
       (.I0(\FSM_onehot_phase_state[1]_i_2_n_0 ),
        .I1(Q[1]),
        .I2(\FSM_onehot_phase_state[3]_i_3_n_0 ),
        .I3(p_2_in),
        .I4(\FSM_onehot_phase_state[5]_i_2_n_0 ),
        .O(\FSM_onehot_phase_state[1]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair4" *) 
  LUT3 #(
    .INIT(8'hEF)) 
    \FSM_onehot_phase_state[1]_i_2 
       (.I0(switching_signals[1]),
        .I1(switching_signals[0]),
        .I2(enable),
        .O(\FSM_onehot_phase_state[1]_i_2_n_0 ));
  LUT6 #(
    .INIT(64'h44F4F44444444444)) 
    \FSM_onehot_phase_state[2]_i_1 
       (.I0(\FSM_onehot_phase_state[5]_i_2_n_0 ),
        .I1(\FSM_onehot_phase_state[2]_i_2_n_0 ),
        .I2(\FSM_onehot_phase_state[3]_i_3_n_0 ),
        .I3(switching_signals[1]),
        .I4(switching_signals[0]),
        .I5(enable),
        .O(\FSM_onehot_phase_state[2]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair0" *) 
  LUT5 #(
    .INIT(32'hF7E00000)) 
    \FSM_onehot_phase_state[2]_i_2 
       (.I0(switching_signals[1]),
        .I1(switching_signals[0]),
        .I2(p_2_in),
        .I3(\FSM_onehot_phase_state_reg_n_0_[0] ),
        .I4(enable),
        .O(\FSM_onehot_phase_state[2]_i_2_n_0 ));
  LUT6 #(
    .INIT(64'h0000FFFF00004440)) 
    \FSM_onehot_phase_state[3]_i_1 
       (.I0(\FSM_onehot_phase_state[3]_i_2_n_0 ),
        .I1(counter[0]),
        .I2(\FSM_onehot_phase_state_reg_n_0_[0] ),
        .I3(p_2_in),
        .I4(enable),
        .I5(\FSM_onehot_phase_state[3]_i_3_n_0 ),
        .O(\FSM_onehot_phase_state[3]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair2" *) 
  LUT4 #(
    .INIT(16'hFFFE)) 
    \FSM_onehot_phase_state[3]_i_2 
       (.I0(counter[8]),
        .I1(\counter[7]_i_2_n_0 ),
        .I2(counter[7]),
        .I3(counter[9]),
        .O(\FSM_onehot_phase_state[3]_i_2_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair1" *) 
  LUT5 #(
    .INIT(32'hFFFF0001)) 
    \FSM_onehot_phase_state[3]_i_3 
       (.I0(\FSM_onehot_phase_state_reg_n_0_[0] ),
        .I1(p_2_in),
        .I2(Q[1]),
        .I3(Q[2]),
        .I4(Q[0]),
        .O(\FSM_onehot_phase_state[3]_i_3_n_0 ));
  LUT6 #(
    .INIT(64'h000F000000040000)) 
    \FSM_onehot_phase_state[4]_i_1 
       (.I0(\FSM_onehot_phase_state[5]_i_2_n_0 ),
        .I1(p_2_in),
        .I2(switching_signals[1]),
        .I3(switching_signals[0]),
        .I4(enable),
        .I5(Q[1]),
        .O(\FSM_onehot_phase_state[4]_i_1_n_0 ));
  LUT6 #(
    .INIT(64'hF000000040000000)) 
    \FSM_onehot_phase_state[5]_i_1 
       (.I0(\FSM_onehot_phase_state[5]_i_2_n_0 ),
        .I1(\FSM_onehot_phase_state_reg_n_0_[0] ),
        .I2(switching_signals[1]),
        .I3(switching_signals[0]),
        .I4(enable),
        .I5(Q[2]),
        .O(\FSM_onehot_phase_state[5]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair2" *) 
  LUT5 #(
    .INIT(32'hFFFEFFFF)) 
    \FSM_onehot_phase_state[5]_i_2 
       (.I0(counter[9]),
        .I1(counter[7]),
        .I2(\counter[7]_i_2_n_0 ),
        .I3(counter[8]),
        .I4(counter[0]),
        .O(\FSM_onehot_phase_state[5]_i_2_n_0 ));
  (* FSM_ENCODED_STATES = "pos_state:100000,neg_state:010000,int_low:000010,int_high:000001,off_state:001000,iSTATE:000100" *) 
  FDRE #(
    .INIT(1'b0)) 
    \FSM_onehot_phase_state_reg[0] 
       (.C(clock),
        .CE(1'b1),
        .D(\FSM_onehot_phase_state[0]_i_1_n_0 ),
        .Q(\FSM_onehot_phase_state_reg_n_0_[0] ),
        .R(1'b0));
  (* FSM_ENCODED_STATES = "pos_state:100000,neg_state:010000,int_low:000010,int_high:000001,off_state:001000,iSTATE:000100" *) 
  FDRE #(
    .INIT(1'b0)) 
    \FSM_onehot_phase_state_reg[1] 
       (.C(clock),
        .CE(1'b1),
        .D(\FSM_onehot_phase_state[1]_i_1_n_0 ),
        .Q(p_2_in),
        .R(1'b0));
  (* FSM_ENCODED_STATES = "pos_state:100000,neg_state:010000,int_low:000010,int_high:000001,off_state:001000,iSTATE:000100" *) 
  FDRE #(
    .INIT(1'b0)) 
    \FSM_onehot_phase_state_reg[2] 
       (.C(clock),
        .CE(1'b1),
        .D(\FSM_onehot_phase_state[2]_i_1_n_0 ),
        .Q(p_1_in),
        .R(1'b0));
  (* FSM_ENCODED_STATES = "pos_state:100000,neg_state:010000,int_low:000010,int_high:000001,off_state:001000,iSTATE:000100" *) 
  FDRE #(
    .INIT(1'b1)) 
    \FSM_onehot_phase_state_reg[3] 
       (.C(clock),
        .CE(1'b1),
        .D(\FSM_onehot_phase_state[3]_i_1_n_0 ),
        .Q(Q[0]),
        .R(1'b0));
  (* FSM_ENCODED_STATES = "pos_state:100000,neg_state:010000,int_low:000010,int_high:000001,off_state:001000,iSTATE:000100" *) 
  FDRE #(
    .INIT(1'b0)) 
    \FSM_onehot_phase_state_reg[4] 
       (.C(clock),
        .CE(1'b1),
        .D(\FSM_onehot_phase_state[4]_i_1_n_0 ),
        .Q(Q[1]),
        .R(1'b0));
  (* FSM_ENCODED_STATES = "pos_state:100000,neg_state:010000,int_low:000010,int_high:000001,off_state:001000,iSTATE:000100" *) 
  FDRE #(
    .INIT(1'b0)) 
    \FSM_onehot_phase_state_reg[5] 
       (.C(clock),
        .CE(1'b1),
        .D(\FSM_onehot_phase_state[5]_i_1_n_0 ),
        .Q(Q[2]),
        .R(1'b0));
  LUT6 #(
    .INIT(64'hAAA8FFFFAAAAAAAA)) 
    \counter[0]_i_1 
       (.I0(deadtime[0]),
        .I1(Q[0]),
        .I2(Q[2]),
        .I3(Q[1]),
        .I4(counter[0]),
        .I5(\counter[9]_i_4_n_0 ),
        .O(\counter[0]_i_1_n_0 ));
  LUT6 #(
    .INIT(64'hF8F8F8888F8F8F88)) 
    \counter[1]_i_1 
       (.I0(\counter[9]_i_6_n_0 ),
        .I1(deadtime[1]),
        .I2(counter[1]),
        .I3(p_2_in),
        .I4(\FSM_onehot_phase_state_reg_n_0_[0] ),
        .I5(counter[0]),
        .O(\counter[1]_i_1_n_0 ));
  LUT6 #(
    .INIT(64'hFF888888F8888F88)) 
    \counter[2]_i_1 
       (.I0(\counter[9]_i_6_n_0 ),
        .I1(deadtime[2]),
        .I2(counter[0]),
        .I3(\counter[9]_i_4_n_0 ),
        .I4(counter[2]),
        .I5(counter[1]),
        .O(\counter[2]_i_1_n_0 ));
  LUT6 #(
    .INIT(64'hFFF88888888F8888)) 
    \counter[3]_i_1 
       (.I0(\counter[9]_i_6_n_0 ),
        .I1(deadtime[3]),
        .I2(counter[0]),
        .I3(\counter[3]_i_2_n_0 ),
        .I4(\counter[9]_i_4_n_0 ),
        .I5(counter[3]),
        .O(\counter[3]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair6" *) 
  LUT2 #(
    .INIT(4'hE)) 
    \counter[3]_i_2 
       (.I0(counter[1]),
        .I1(counter[2]),
        .O(\counter[3]_i_2_n_0 ));
  LUT6 #(
    .INIT(64'hFFF88888888F8888)) 
    \counter[4]_i_1 
       (.I0(\counter[9]_i_6_n_0 ),
        .I1(deadtime[4]),
        .I2(counter[0]),
        .I3(\counter[4]_i_2_n_0 ),
        .I4(\counter[9]_i_4_n_0 ),
        .I5(counter[4]),
        .O(\counter[4]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair6" *) 
  LUT3 #(
    .INIT(8'hFE)) 
    \counter[4]_i_2 
       (.I0(counter[2]),
        .I1(counter[1]),
        .I2(counter[3]),
        .O(\counter[4]_i_2_n_0 ));
  LUT6 #(
    .INIT(64'hFFC0C0C0FF848484)) 
    \counter[5]_i_1 
       (.I0(counter[0]),
        .I1(\counter[9]_i_4_n_0 ),
        .I2(counter[5]),
        .I3(deadtime[5]),
        .I4(\counter[9]_i_6_n_0 ),
        .I5(\counter[5]_i_2_n_0 ),
        .O(\counter[5]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair3" *) 
  LUT4 #(
    .INIT(16'hFFFE)) 
    \counter[5]_i_2 
       (.I0(counter[3]),
        .I1(counter[1]),
        .I2(counter[2]),
        .I3(counter[4]),
        .O(\counter[5]_i_2_n_0 ));
  LUT6 #(
    .INIT(64'hFFC0C0C0FF848484)) 
    \counter[6]_i_1 
       (.I0(counter[0]),
        .I1(\counter[9]_i_4_n_0 ),
        .I2(counter[6]),
        .I3(deadtime[6]),
        .I4(\counter[9]_i_6_n_0 ),
        .I5(\counter[6]_i_2_n_0 ),
        .O(\counter[6]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair3" *) 
  LUT5 #(
    .INIT(32'hFFFFFFFE)) 
    \counter[6]_i_2 
       (.I0(counter[4]),
        .I1(counter[2]),
        .I2(counter[1]),
        .I3(counter[3]),
        .I4(counter[5]),
        .O(\counter[6]_i_2_n_0 ));
  LUT6 #(
    .INIT(64'hFFC0C0C0FF848484)) 
    \counter[7]_i_1 
       (.I0(counter[0]),
        .I1(\counter[9]_i_4_n_0 ),
        .I2(counter[7]),
        .I3(deadtime[7]),
        .I4(\counter[9]_i_6_n_0 ),
        .I5(\counter[7]_i_2_n_0 ),
        .O(\counter[7]_i_1_n_0 ));
  LUT6 #(
    .INIT(64'hFFFFFFFFFFFFFFFE)) 
    \counter[7]_i_2 
       (.I0(counter[5]),
        .I1(counter[3]),
        .I2(counter[1]),
        .I3(counter[2]),
        .I4(counter[4]),
        .I5(counter[6]),
        .O(\counter[7]_i_2_n_0 ));
  LUT6 #(
    .INIT(64'hFFC0C0C0FF848484)) 
    \counter[8]_i_1 
       (.I0(counter[0]),
        .I1(\counter[9]_i_4_n_0 ),
        .I2(counter[8]),
        .I3(deadtime[8]),
        .I4(\counter[9]_i_6_n_0 ),
        .I5(\counter[8]_i_2_n_0 ),
        .O(\counter[8]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair5" *) 
  LUT2 #(
    .INIT(4'hE)) 
    \counter[8]_i_2 
       (.I0(\counter[7]_i_2_n_0 ),
        .I1(counter[7]),
        .O(\counter[8]_i_2_n_0 ));
  LUT6 #(
    .INIT(64'hFFFFFFFFFFFFF808)) 
    \counter[9]_i_1 
       (.I0(Q[0]),
        .I1(enable),
        .I2(\counter[9]_i_3_n_0 ),
        .I3(Q[1]),
        .I4(\counter[9]_i_4_n_0 ),
        .I5(\counter[9]_i_5_n_0 ),
        .O(counter_0));
  LUT6 #(
    .INIT(64'hFFC0C0C0FF848484)) 
    \counter[9]_i_2 
       (.I0(counter[0]),
        .I1(\counter[9]_i_4_n_0 ),
        .I2(counter[9]),
        .I3(deadtime[9]),
        .I4(\counter[9]_i_6_n_0 ),
        .I5(\counter[9]_i_7_n_0 ),
        .O(\counter[9]_i_2_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair4" *) 
  LUT2 #(
    .INIT(4'hE)) 
    \counter[9]_i_3 
       (.I0(switching_signals[0]),
        .I1(switching_signals[1]),
        .O(\counter[9]_i_3_n_0 ));
  LUT2 #(
    .INIT(4'hE)) 
    \counter[9]_i_4 
       (.I0(\FSM_onehot_phase_state_reg_n_0_[0] ),
        .I1(p_2_in),
        .O(\counter[9]_i_4_n_0 ));
  LUT6 #(
    .INIT(64'hEAFF6AFFEBAA6BAA)) 
    \counter[9]_i_5 
       (.I0(Q[2]),
        .I1(switching_signals[1]),
        .I2(switching_signals[0]),
        .I3(enable),
        .I4(Q[0]),
        .I5(Q[1]),
        .O(\counter[9]_i_5_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair1" *) 
  LUT5 #(
    .INIT(32'hFFFFFFF1)) 
    \counter[9]_i_6 
       (.I0(\FSM_onehot_phase_state_reg_n_0_[0] ),
        .I1(p_2_in),
        .I2(Q[0]),
        .I3(Q[2]),
        .I4(Q[1]),
        .O(\counter[9]_i_6_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair5" *) 
  LUT3 #(
    .INIT(8'hFE)) 
    \counter[9]_i_7 
       (.I0(counter[7]),
        .I1(\counter[7]_i_2_n_0 ),
        .I2(counter[8]),
        .O(\counter[9]_i_7_n_0 ));
  FDRE #(
    .INIT(1'b0)) 
    \counter_reg[0] 
       (.C(clock),
        .CE(counter_0),
        .D(\counter[0]_i_1_n_0 ),
        .Q(counter[0]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \counter_reg[1] 
       (.C(clock),
        .CE(counter_0),
        .D(\counter[1]_i_1_n_0 ),
        .Q(counter[1]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \counter_reg[2] 
       (.C(clock),
        .CE(counter_0),
        .D(\counter[2]_i_1_n_0 ),
        .Q(counter[2]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b1)) 
    \counter_reg[3] 
       (.C(clock),
        .CE(counter_0),
        .D(\counter[3]_i_1_n_0 ),
        .Q(counter[3]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \counter_reg[4] 
       (.C(clock),
        .CE(counter_0),
        .D(\counter[4]_i_1_n_0 ),
        .Q(counter[4]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \counter_reg[5] 
       (.C(clock),
        .CE(counter_0),
        .D(\counter[5]_i_1_n_0 ),
        .Q(counter[5]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b1)) 
    \counter_reg[6] 
       (.C(clock),
        .CE(counter_0),
        .D(\counter[6]_i_1_n_0 ),
        .Q(counter[6]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b1)) 
    \counter_reg[7] 
       (.C(clock),
        .CE(counter_0),
        .D(\counter[7]_i_1_n_0 ),
        .Q(counter[7]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \counter_reg[8] 
       (.C(clock),
        .CE(counter_0),
        .D(\counter[8]_i_1_n_0 ),
        .Q(counter[8]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \counter_reg[9] 
       (.C(clock),
        .CE(counter_0),
        .D(\counter[9]_i_2_n_0 ),
        .Q(counter[9]),
        .R(1'b0));
endmodule

(* ORIG_REF_NAME = "npc_phase_state_machine" *) 
module zusys_top_npc_state_machine_0_0_npc_phase_state_machine_0
   (Q,
    B_S2,
    B_S3,
    switching_signals,
    enable,
    deadtime,
    clock);
  output [2:0]Q;
  output B_S2;
  output B_S3;
  input [1:0]switching_signals;
  input enable;
  input [9:0]deadtime;
  input clock;

  wire B_S2;
  wire B_S3;
  wire \FSM_onehot_phase_state[0]_i_1__0_n_0 ;
  wire \FSM_onehot_phase_state[0]_i_2__0_n_0 ;
  wire \FSM_onehot_phase_state[1]_i_1__0_n_0 ;
  wire \FSM_onehot_phase_state[1]_i_2__0_n_0 ;
  wire \FSM_onehot_phase_state[2]_i_1__0_n_0 ;
  wire \FSM_onehot_phase_state[2]_i_2__0_n_0 ;
  wire \FSM_onehot_phase_state[3]_i_1__0_n_0 ;
  wire \FSM_onehot_phase_state[3]_i_2__0_n_0 ;
  wire \FSM_onehot_phase_state[3]_i_3__0_n_0 ;
  wire \FSM_onehot_phase_state[4]_i_1__0_n_0 ;
  wire \FSM_onehot_phase_state[5]_i_1__0_n_0 ;
  wire \FSM_onehot_phase_state[5]_i_2__0_n_0 ;
  wire \FSM_onehot_phase_state_reg_n_0_[0] ;
  wire [2:0]Q;
  wire clock;
  wire counter;
  wire \counter[0]_i_1__0_n_0 ;
  wire \counter[1]_i_1__0_n_0 ;
  wire \counter[2]_i_1__0_n_0 ;
  wire \counter[3]_i_1__0_n_0 ;
  wire \counter[3]_i_2__0_n_0 ;
  wire \counter[4]_i_1__0_n_0 ;
  wire \counter[4]_i_2__0_n_0 ;
  wire \counter[5]_i_1__0_n_0 ;
  wire \counter[5]_i_2__0_n_0 ;
  wire \counter[6]_i_1__0_n_0 ;
  wire \counter[6]_i_2__0_n_0 ;
  wire \counter[7]_i_1__0_n_0 ;
  wire \counter[7]_i_2__0_n_0 ;
  wire \counter[8]_i_1__0_n_0 ;
  wire \counter[8]_i_2__0_n_0 ;
  wire \counter[9]_i_2__0_n_0 ;
  wire \counter[9]_i_3__0_n_0 ;
  wire \counter[9]_i_4__0_n_0 ;
  wire \counter[9]_i_5__0_n_0 ;
  wire \counter[9]_i_6__0_n_0 ;
  wire \counter[9]_i_7__0_n_0 ;
  wire \counter_reg_n_0_[0] ;
  wire \counter_reg_n_0_[1] ;
  wire \counter_reg_n_0_[2] ;
  wire \counter_reg_n_0_[3] ;
  wire \counter_reg_n_0_[4] ;
  wire \counter_reg_n_0_[5] ;
  wire \counter_reg_n_0_[6] ;
  wire \counter_reg_n_0_[7] ;
  wire \counter_reg_n_0_[8] ;
  wire \counter_reg_n_0_[9] ;
  wire [9:0]deadtime;
  wire enable;
  wire p_1_in;
  wire p_2_in;
  wire [1:0]switching_signals;

  (* SOFT_HLUTNM = "soft_lutpair15" *) 
  LUT3 #(
    .INIT(8'hFE)) 
    B_S2_INST_0
       (.I0(Q[2]),
        .I1(p_1_in),
        .I2(\FSM_onehot_phase_state_reg_n_0_[0] ),
        .O(B_S2));
  (* SOFT_HLUTNM = "soft_lutpair15" *) 
  LUT3 #(
    .INIT(8'hFE)) 
    B_S3_INST_0
       (.I0(Q[1]),
        .I1(p_1_in),
        .I2(p_2_in),
        .O(B_S3));
  LUT5 #(
    .INIT(32'hFFD8D8D8)) 
    \FSM_onehot_phase_state[0]_i_1__0 
       (.I0(\FSM_onehot_phase_state[0]_i_2__0_n_0 ),
        .I1(Q[2]),
        .I2(\FSM_onehot_phase_state[3]_i_3__0_n_0 ),
        .I3(\FSM_onehot_phase_state_reg_n_0_[0] ),
        .I4(\FSM_onehot_phase_state[5]_i_2__0_n_0 ),
        .O(\FSM_onehot_phase_state[0]_i_1__0_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair8" *) 
  LUT3 #(
    .INIT(8'h7F)) 
    \FSM_onehot_phase_state[0]_i_2__0 
       (.I0(switching_signals[1]),
        .I1(switching_signals[0]),
        .I2(enable),
        .O(\FSM_onehot_phase_state[0]_i_2__0_n_0 ));
  LUT5 #(
    .INIT(32'hFFD8D8D8)) 
    \FSM_onehot_phase_state[1]_i_1__0 
       (.I0(\FSM_onehot_phase_state[1]_i_2__0_n_0 ),
        .I1(Q[1]),
        .I2(\FSM_onehot_phase_state[3]_i_3__0_n_0 ),
        .I3(p_2_in),
        .I4(\FSM_onehot_phase_state[5]_i_2__0_n_0 ),
        .O(\FSM_onehot_phase_state[1]_i_1__0_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair12" *) 
  LUT3 #(
    .INIT(8'hEF)) 
    \FSM_onehot_phase_state[1]_i_2__0 
       (.I0(switching_signals[1]),
        .I1(switching_signals[0]),
        .I2(enable),
        .O(\FSM_onehot_phase_state[1]_i_2__0_n_0 ));
  LUT6 #(
    .INIT(64'h44F4F44444444444)) 
    \FSM_onehot_phase_state[2]_i_1__0 
       (.I0(\FSM_onehot_phase_state[5]_i_2__0_n_0 ),
        .I1(\FSM_onehot_phase_state[2]_i_2__0_n_0 ),
        .I2(\FSM_onehot_phase_state[3]_i_3__0_n_0 ),
        .I3(switching_signals[1]),
        .I4(switching_signals[0]),
        .I5(enable),
        .O(\FSM_onehot_phase_state[2]_i_1__0_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair8" *) 
  LUT5 #(
    .INIT(32'hF7E00000)) 
    \FSM_onehot_phase_state[2]_i_2__0 
       (.I0(switching_signals[1]),
        .I1(switching_signals[0]),
        .I2(p_2_in),
        .I3(\FSM_onehot_phase_state_reg_n_0_[0] ),
        .I4(enable),
        .O(\FSM_onehot_phase_state[2]_i_2__0_n_0 ));
  LUT6 #(
    .INIT(64'h0000FFFF00004440)) 
    \FSM_onehot_phase_state[3]_i_1__0 
       (.I0(\FSM_onehot_phase_state[3]_i_2__0_n_0 ),
        .I1(\counter_reg_n_0_[0] ),
        .I2(\FSM_onehot_phase_state_reg_n_0_[0] ),
        .I3(p_2_in),
        .I4(enable),
        .I5(\FSM_onehot_phase_state[3]_i_3__0_n_0 ),
        .O(\FSM_onehot_phase_state[3]_i_1__0_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair10" *) 
  LUT4 #(
    .INIT(16'hFFFE)) 
    \FSM_onehot_phase_state[3]_i_2__0 
       (.I0(\counter_reg_n_0_[8] ),
        .I1(\counter[7]_i_2__0_n_0 ),
        .I2(\counter_reg_n_0_[7] ),
        .I3(\counter_reg_n_0_[9] ),
        .O(\FSM_onehot_phase_state[3]_i_2__0_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair9" *) 
  LUT5 #(
    .INIT(32'hFFFF0001)) 
    \FSM_onehot_phase_state[3]_i_3__0 
       (.I0(\FSM_onehot_phase_state_reg_n_0_[0] ),
        .I1(p_2_in),
        .I2(Q[1]),
        .I3(Q[2]),
        .I4(Q[0]),
        .O(\FSM_onehot_phase_state[3]_i_3__0_n_0 ));
  LUT6 #(
    .INIT(64'h000F000000040000)) 
    \FSM_onehot_phase_state[4]_i_1__0 
       (.I0(\FSM_onehot_phase_state[5]_i_2__0_n_0 ),
        .I1(p_2_in),
        .I2(switching_signals[1]),
        .I3(switching_signals[0]),
        .I4(enable),
        .I5(Q[1]),
        .O(\FSM_onehot_phase_state[4]_i_1__0_n_0 ));
  LUT6 #(
    .INIT(64'hF000000040000000)) 
    \FSM_onehot_phase_state[5]_i_1__0 
       (.I0(\FSM_onehot_phase_state[5]_i_2__0_n_0 ),
        .I1(\FSM_onehot_phase_state_reg_n_0_[0] ),
        .I2(switching_signals[1]),
        .I3(switching_signals[0]),
        .I4(enable),
        .I5(Q[2]),
        .O(\FSM_onehot_phase_state[5]_i_1__0_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair10" *) 
  LUT5 #(
    .INIT(32'hFFFEFFFF)) 
    \FSM_onehot_phase_state[5]_i_2__0 
       (.I0(\counter_reg_n_0_[9] ),
        .I1(\counter_reg_n_0_[7] ),
        .I2(\counter[7]_i_2__0_n_0 ),
        .I3(\counter_reg_n_0_[8] ),
        .I4(\counter_reg_n_0_[0] ),
        .O(\FSM_onehot_phase_state[5]_i_2__0_n_0 ));
  (* FSM_ENCODED_STATES = "pos_state:100000,neg_state:010000,int_low:000010,int_high:000001,off_state:001000,iSTATE:000100" *) 
  FDRE #(
    .INIT(1'b0)) 
    \FSM_onehot_phase_state_reg[0] 
       (.C(clock),
        .CE(1'b1),
        .D(\FSM_onehot_phase_state[0]_i_1__0_n_0 ),
        .Q(\FSM_onehot_phase_state_reg_n_0_[0] ),
        .R(1'b0));
  (* FSM_ENCODED_STATES = "pos_state:100000,neg_state:010000,int_low:000010,int_high:000001,off_state:001000,iSTATE:000100" *) 
  FDRE #(
    .INIT(1'b0)) 
    \FSM_onehot_phase_state_reg[1] 
       (.C(clock),
        .CE(1'b1),
        .D(\FSM_onehot_phase_state[1]_i_1__0_n_0 ),
        .Q(p_2_in),
        .R(1'b0));
  (* FSM_ENCODED_STATES = "pos_state:100000,neg_state:010000,int_low:000010,int_high:000001,off_state:001000,iSTATE:000100" *) 
  FDRE #(
    .INIT(1'b0)) 
    \FSM_onehot_phase_state_reg[2] 
       (.C(clock),
        .CE(1'b1),
        .D(\FSM_onehot_phase_state[2]_i_1__0_n_0 ),
        .Q(p_1_in),
        .R(1'b0));
  (* FSM_ENCODED_STATES = "pos_state:100000,neg_state:010000,int_low:000010,int_high:000001,off_state:001000,iSTATE:000100" *) 
  FDRE #(
    .INIT(1'b1)) 
    \FSM_onehot_phase_state_reg[3] 
       (.C(clock),
        .CE(1'b1),
        .D(\FSM_onehot_phase_state[3]_i_1__0_n_0 ),
        .Q(Q[0]),
        .R(1'b0));
  (* FSM_ENCODED_STATES = "pos_state:100000,neg_state:010000,int_low:000010,int_high:000001,off_state:001000,iSTATE:000100" *) 
  FDRE #(
    .INIT(1'b0)) 
    \FSM_onehot_phase_state_reg[4] 
       (.C(clock),
        .CE(1'b1),
        .D(\FSM_onehot_phase_state[4]_i_1__0_n_0 ),
        .Q(Q[1]),
        .R(1'b0));
  (* FSM_ENCODED_STATES = "pos_state:100000,neg_state:010000,int_low:000010,int_high:000001,off_state:001000,iSTATE:000100" *) 
  FDRE #(
    .INIT(1'b0)) 
    \FSM_onehot_phase_state_reg[5] 
       (.C(clock),
        .CE(1'b1),
        .D(\FSM_onehot_phase_state[5]_i_1__0_n_0 ),
        .Q(Q[2]),
        .R(1'b0));
  LUT6 #(
    .INIT(64'hAAA8FFFFAAAAAAAA)) 
    \counter[0]_i_1__0 
       (.I0(deadtime[0]),
        .I1(Q[0]),
        .I2(Q[2]),
        .I3(Q[1]),
        .I4(\counter_reg_n_0_[0] ),
        .I5(\counter[9]_i_4__0_n_0 ),
        .O(\counter[0]_i_1__0_n_0 ));
  LUT6 #(
    .INIT(64'hF8F8F8888F8F8F88)) 
    \counter[1]_i_1__0 
       (.I0(\counter[9]_i_6__0_n_0 ),
        .I1(deadtime[1]),
        .I2(\counter_reg_n_0_[1] ),
        .I3(p_2_in),
        .I4(\FSM_onehot_phase_state_reg_n_0_[0] ),
        .I5(\counter_reg_n_0_[0] ),
        .O(\counter[1]_i_1__0_n_0 ));
  LUT6 #(
    .INIT(64'hFF888888F8888F88)) 
    \counter[2]_i_1__0 
       (.I0(\counter[9]_i_6__0_n_0 ),
        .I1(deadtime[2]),
        .I2(\counter_reg_n_0_[0] ),
        .I3(\counter[9]_i_4__0_n_0 ),
        .I4(\counter_reg_n_0_[2] ),
        .I5(\counter_reg_n_0_[1] ),
        .O(\counter[2]_i_1__0_n_0 ));
  LUT6 #(
    .INIT(64'hFFF88888888F8888)) 
    \counter[3]_i_1__0 
       (.I0(\counter[9]_i_6__0_n_0 ),
        .I1(deadtime[3]),
        .I2(\counter_reg_n_0_[0] ),
        .I3(\counter[3]_i_2__0_n_0 ),
        .I4(\counter[9]_i_4__0_n_0 ),
        .I5(\counter_reg_n_0_[3] ),
        .O(\counter[3]_i_1__0_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair14" *) 
  LUT2 #(
    .INIT(4'hE)) 
    \counter[3]_i_2__0 
       (.I0(\counter_reg_n_0_[1] ),
        .I1(\counter_reg_n_0_[2] ),
        .O(\counter[3]_i_2__0_n_0 ));
  LUT6 #(
    .INIT(64'hFFF88888888F8888)) 
    \counter[4]_i_1__0 
       (.I0(\counter[9]_i_6__0_n_0 ),
        .I1(deadtime[4]),
        .I2(\counter_reg_n_0_[0] ),
        .I3(\counter[4]_i_2__0_n_0 ),
        .I4(\counter[9]_i_4__0_n_0 ),
        .I5(\counter_reg_n_0_[4] ),
        .O(\counter[4]_i_1__0_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair14" *) 
  LUT3 #(
    .INIT(8'hFE)) 
    \counter[4]_i_2__0 
       (.I0(\counter_reg_n_0_[2] ),
        .I1(\counter_reg_n_0_[1] ),
        .I2(\counter_reg_n_0_[3] ),
        .O(\counter[4]_i_2__0_n_0 ));
  LUT6 #(
    .INIT(64'hFFC0C0C0FF848484)) 
    \counter[5]_i_1__0 
       (.I0(\counter_reg_n_0_[0] ),
        .I1(\counter[9]_i_4__0_n_0 ),
        .I2(\counter_reg_n_0_[5] ),
        .I3(deadtime[5]),
        .I4(\counter[9]_i_6__0_n_0 ),
        .I5(\counter[5]_i_2__0_n_0 ),
        .O(\counter[5]_i_1__0_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair11" *) 
  LUT4 #(
    .INIT(16'hFFFE)) 
    \counter[5]_i_2__0 
       (.I0(\counter_reg_n_0_[3] ),
        .I1(\counter_reg_n_0_[1] ),
        .I2(\counter_reg_n_0_[2] ),
        .I3(\counter_reg_n_0_[4] ),
        .O(\counter[5]_i_2__0_n_0 ));
  LUT6 #(
    .INIT(64'hFFC0C0C0FF848484)) 
    \counter[6]_i_1__0 
       (.I0(\counter_reg_n_0_[0] ),
        .I1(\counter[9]_i_4__0_n_0 ),
        .I2(\counter_reg_n_0_[6] ),
        .I3(deadtime[6]),
        .I4(\counter[9]_i_6__0_n_0 ),
        .I5(\counter[6]_i_2__0_n_0 ),
        .O(\counter[6]_i_1__0_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair11" *) 
  LUT5 #(
    .INIT(32'hFFFFFFFE)) 
    \counter[6]_i_2__0 
       (.I0(\counter_reg_n_0_[4] ),
        .I1(\counter_reg_n_0_[2] ),
        .I2(\counter_reg_n_0_[1] ),
        .I3(\counter_reg_n_0_[3] ),
        .I4(\counter_reg_n_0_[5] ),
        .O(\counter[6]_i_2__0_n_0 ));
  LUT6 #(
    .INIT(64'hFFC0C0C0FF848484)) 
    \counter[7]_i_1__0 
       (.I0(\counter_reg_n_0_[0] ),
        .I1(\counter[9]_i_4__0_n_0 ),
        .I2(\counter_reg_n_0_[7] ),
        .I3(deadtime[7]),
        .I4(\counter[9]_i_6__0_n_0 ),
        .I5(\counter[7]_i_2__0_n_0 ),
        .O(\counter[7]_i_1__0_n_0 ));
  LUT6 #(
    .INIT(64'hFFFFFFFFFFFFFFFE)) 
    \counter[7]_i_2__0 
       (.I0(\counter_reg_n_0_[5] ),
        .I1(\counter_reg_n_0_[3] ),
        .I2(\counter_reg_n_0_[1] ),
        .I3(\counter_reg_n_0_[2] ),
        .I4(\counter_reg_n_0_[4] ),
        .I5(\counter_reg_n_0_[6] ),
        .O(\counter[7]_i_2__0_n_0 ));
  LUT6 #(
    .INIT(64'hFFC0C0C0FF848484)) 
    \counter[8]_i_1__0 
       (.I0(\counter_reg_n_0_[0] ),
        .I1(\counter[9]_i_4__0_n_0 ),
        .I2(\counter_reg_n_0_[8] ),
        .I3(deadtime[8]),
        .I4(\counter[9]_i_6__0_n_0 ),
        .I5(\counter[8]_i_2__0_n_0 ),
        .O(\counter[8]_i_1__0_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair13" *) 
  LUT2 #(
    .INIT(4'hE)) 
    \counter[8]_i_2__0 
       (.I0(\counter[7]_i_2__0_n_0 ),
        .I1(\counter_reg_n_0_[7] ),
        .O(\counter[8]_i_2__0_n_0 ));
  LUT6 #(
    .INIT(64'hFFFFFFFFFFFFF808)) 
    \counter[9]_i_1__0 
       (.I0(Q[0]),
        .I1(enable),
        .I2(\counter[9]_i_3__0_n_0 ),
        .I3(Q[1]),
        .I4(\counter[9]_i_4__0_n_0 ),
        .I5(\counter[9]_i_5__0_n_0 ),
        .O(counter));
  LUT6 #(
    .INIT(64'hFFC0C0C0FF848484)) 
    \counter[9]_i_2__0 
       (.I0(\counter_reg_n_0_[0] ),
        .I1(\counter[9]_i_4__0_n_0 ),
        .I2(\counter_reg_n_0_[9] ),
        .I3(deadtime[9]),
        .I4(\counter[9]_i_6__0_n_0 ),
        .I5(\counter[9]_i_7__0_n_0 ),
        .O(\counter[9]_i_2__0_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair12" *) 
  LUT2 #(
    .INIT(4'hE)) 
    \counter[9]_i_3__0 
       (.I0(switching_signals[0]),
        .I1(switching_signals[1]),
        .O(\counter[9]_i_3__0_n_0 ));
  LUT2 #(
    .INIT(4'hE)) 
    \counter[9]_i_4__0 
       (.I0(\FSM_onehot_phase_state_reg_n_0_[0] ),
        .I1(p_2_in),
        .O(\counter[9]_i_4__0_n_0 ));
  LUT6 #(
    .INIT(64'hEAFF6AFFEBAA6BAA)) 
    \counter[9]_i_5__0 
       (.I0(Q[2]),
        .I1(switching_signals[1]),
        .I2(switching_signals[0]),
        .I3(enable),
        .I4(Q[0]),
        .I5(Q[1]),
        .O(\counter[9]_i_5__0_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair9" *) 
  LUT5 #(
    .INIT(32'hFFFFFFF1)) 
    \counter[9]_i_6__0 
       (.I0(\FSM_onehot_phase_state_reg_n_0_[0] ),
        .I1(p_2_in),
        .I2(Q[0]),
        .I3(Q[2]),
        .I4(Q[1]),
        .O(\counter[9]_i_6__0_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair13" *) 
  LUT3 #(
    .INIT(8'hFE)) 
    \counter[9]_i_7__0 
       (.I0(\counter_reg_n_0_[7] ),
        .I1(\counter[7]_i_2__0_n_0 ),
        .I2(\counter_reg_n_0_[8] ),
        .O(\counter[9]_i_7__0_n_0 ));
  FDRE #(
    .INIT(1'b0)) 
    \counter_reg[0] 
       (.C(clock),
        .CE(counter),
        .D(\counter[0]_i_1__0_n_0 ),
        .Q(\counter_reg_n_0_[0] ),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \counter_reg[1] 
       (.C(clock),
        .CE(counter),
        .D(\counter[1]_i_1__0_n_0 ),
        .Q(\counter_reg_n_0_[1] ),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \counter_reg[2] 
       (.C(clock),
        .CE(counter),
        .D(\counter[2]_i_1__0_n_0 ),
        .Q(\counter_reg_n_0_[2] ),
        .R(1'b0));
  FDRE #(
    .INIT(1'b1)) 
    \counter_reg[3] 
       (.C(clock),
        .CE(counter),
        .D(\counter[3]_i_1__0_n_0 ),
        .Q(\counter_reg_n_0_[3] ),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \counter_reg[4] 
       (.C(clock),
        .CE(counter),
        .D(\counter[4]_i_1__0_n_0 ),
        .Q(\counter_reg_n_0_[4] ),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \counter_reg[5] 
       (.C(clock),
        .CE(counter),
        .D(\counter[5]_i_1__0_n_0 ),
        .Q(\counter_reg_n_0_[5] ),
        .R(1'b0));
  FDRE #(
    .INIT(1'b1)) 
    \counter_reg[6] 
       (.C(clock),
        .CE(counter),
        .D(\counter[6]_i_1__0_n_0 ),
        .Q(\counter_reg_n_0_[6] ),
        .R(1'b0));
  FDRE #(
    .INIT(1'b1)) 
    \counter_reg[7] 
       (.C(clock),
        .CE(counter),
        .D(\counter[7]_i_1__0_n_0 ),
        .Q(\counter_reg_n_0_[7] ),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \counter_reg[8] 
       (.C(clock),
        .CE(counter),
        .D(\counter[8]_i_1__0_n_0 ),
        .Q(\counter_reg_n_0_[8] ),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \counter_reg[9] 
       (.C(clock),
        .CE(counter),
        .D(\counter[9]_i_2__0_n_0 ),
        .Q(\counter_reg_n_0_[9] ),
        .R(1'b0));
endmodule

(* ORIG_REF_NAME = "npc_phase_state_machine" *) 
module zusys_top_npc_state_machine_0_0_npc_phase_state_machine_1
   (Q,
    C_S2,
    C_S3,
    switching_signals,
    enable,
    deadtime,
    clock);
  output [2:0]Q;
  output C_S2;
  output C_S3;
  input [1:0]switching_signals;
  input enable;
  input [9:0]deadtime;
  input clock;

  wire C_S2;
  wire C_S3;
  wire \FSM_onehot_phase_state[0]_i_1__1_n_0 ;
  wire \FSM_onehot_phase_state[0]_i_2__1_n_0 ;
  wire \FSM_onehot_phase_state[1]_i_1__1_n_0 ;
  wire \FSM_onehot_phase_state[1]_i_2__1_n_0 ;
  wire \FSM_onehot_phase_state[2]_i_1__1_n_0 ;
  wire \FSM_onehot_phase_state[2]_i_2__1_n_0 ;
  wire \FSM_onehot_phase_state[3]_i_1__1_n_0 ;
  wire \FSM_onehot_phase_state[3]_i_2__1_n_0 ;
  wire \FSM_onehot_phase_state[3]_i_3__1_n_0 ;
  wire \FSM_onehot_phase_state[4]_i_1__1_n_0 ;
  wire \FSM_onehot_phase_state[5]_i_1__1_n_0 ;
  wire \FSM_onehot_phase_state[5]_i_2__1_n_0 ;
  wire \FSM_onehot_phase_state_reg_n_0_[0] ;
  wire [2:0]Q;
  wire clock;
  wire counter;
  wire \counter[0]_i_1__1_n_0 ;
  wire \counter[1]_i_1__1_n_0 ;
  wire \counter[2]_i_1__1_n_0 ;
  wire \counter[3]_i_1__1_n_0 ;
  wire \counter[3]_i_2__1_n_0 ;
  wire \counter[4]_i_1__1_n_0 ;
  wire \counter[4]_i_2__1_n_0 ;
  wire \counter[5]_i_1__1_n_0 ;
  wire \counter[5]_i_2__1_n_0 ;
  wire \counter[6]_i_1__1_n_0 ;
  wire \counter[6]_i_2__1_n_0 ;
  wire \counter[7]_i_1__1_n_0 ;
  wire \counter[7]_i_2__1_n_0 ;
  wire \counter[8]_i_1__1_n_0 ;
  wire \counter[8]_i_2__1_n_0 ;
  wire \counter[9]_i_2__1_n_0 ;
  wire \counter[9]_i_3__1_n_0 ;
  wire \counter[9]_i_4__1_n_0 ;
  wire \counter[9]_i_5__1_n_0 ;
  wire \counter[9]_i_6__1_n_0 ;
  wire \counter[9]_i_7__1_n_0 ;
  wire \counter_reg_n_0_[0] ;
  wire \counter_reg_n_0_[1] ;
  wire \counter_reg_n_0_[2] ;
  wire \counter_reg_n_0_[3] ;
  wire \counter_reg_n_0_[4] ;
  wire \counter_reg_n_0_[5] ;
  wire \counter_reg_n_0_[6] ;
  wire \counter_reg_n_0_[7] ;
  wire \counter_reg_n_0_[8] ;
  wire \counter_reg_n_0_[9] ;
  wire [9:0]deadtime;
  wire enable;
  wire p_1_in;
  wire p_2_in;
  wire [1:0]switching_signals;

  (* SOFT_HLUTNM = "soft_lutpair23" *) 
  LUT3 #(
    .INIT(8'hFE)) 
    C_S2_INST_0
       (.I0(Q[2]),
        .I1(p_1_in),
        .I2(\FSM_onehot_phase_state_reg_n_0_[0] ),
        .O(C_S2));
  (* SOFT_HLUTNM = "soft_lutpair23" *) 
  LUT3 #(
    .INIT(8'hFE)) 
    C_S3_INST_0
       (.I0(Q[1]),
        .I1(p_1_in),
        .I2(p_2_in),
        .O(C_S3));
  LUT5 #(
    .INIT(32'hFFD8D8D8)) 
    \FSM_onehot_phase_state[0]_i_1__1 
       (.I0(\FSM_onehot_phase_state[0]_i_2__1_n_0 ),
        .I1(Q[2]),
        .I2(\FSM_onehot_phase_state[3]_i_3__1_n_0 ),
        .I3(\FSM_onehot_phase_state_reg_n_0_[0] ),
        .I4(\FSM_onehot_phase_state[5]_i_2__1_n_0 ),
        .O(\FSM_onehot_phase_state[0]_i_1__1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair16" *) 
  LUT3 #(
    .INIT(8'h7F)) 
    \FSM_onehot_phase_state[0]_i_2__1 
       (.I0(switching_signals[1]),
        .I1(switching_signals[0]),
        .I2(enable),
        .O(\FSM_onehot_phase_state[0]_i_2__1_n_0 ));
  LUT5 #(
    .INIT(32'hFFD8D8D8)) 
    \FSM_onehot_phase_state[1]_i_1__1 
       (.I0(\FSM_onehot_phase_state[1]_i_2__1_n_0 ),
        .I1(Q[1]),
        .I2(\FSM_onehot_phase_state[3]_i_3__1_n_0 ),
        .I3(p_2_in),
        .I4(\FSM_onehot_phase_state[5]_i_2__1_n_0 ),
        .O(\FSM_onehot_phase_state[1]_i_1__1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair20" *) 
  LUT3 #(
    .INIT(8'hEF)) 
    \FSM_onehot_phase_state[1]_i_2__1 
       (.I0(switching_signals[1]),
        .I1(switching_signals[0]),
        .I2(enable),
        .O(\FSM_onehot_phase_state[1]_i_2__1_n_0 ));
  LUT6 #(
    .INIT(64'h44F4F44444444444)) 
    \FSM_onehot_phase_state[2]_i_1__1 
       (.I0(\FSM_onehot_phase_state[5]_i_2__1_n_0 ),
        .I1(\FSM_onehot_phase_state[2]_i_2__1_n_0 ),
        .I2(\FSM_onehot_phase_state[3]_i_3__1_n_0 ),
        .I3(switching_signals[1]),
        .I4(switching_signals[0]),
        .I5(enable),
        .O(\FSM_onehot_phase_state[2]_i_1__1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair16" *) 
  LUT5 #(
    .INIT(32'hF7E00000)) 
    \FSM_onehot_phase_state[2]_i_2__1 
       (.I0(switching_signals[1]),
        .I1(switching_signals[0]),
        .I2(p_2_in),
        .I3(\FSM_onehot_phase_state_reg_n_0_[0] ),
        .I4(enable),
        .O(\FSM_onehot_phase_state[2]_i_2__1_n_0 ));
  LUT6 #(
    .INIT(64'h0000FFFF00004440)) 
    \FSM_onehot_phase_state[3]_i_1__1 
       (.I0(\FSM_onehot_phase_state[3]_i_2__1_n_0 ),
        .I1(\counter_reg_n_0_[0] ),
        .I2(\FSM_onehot_phase_state_reg_n_0_[0] ),
        .I3(p_2_in),
        .I4(enable),
        .I5(\FSM_onehot_phase_state[3]_i_3__1_n_0 ),
        .O(\FSM_onehot_phase_state[3]_i_1__1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair18" *) 
  LUT4 #(
    .INIT(16'hFFFE)) 
    \FSM_onehot_phase_state[3]_i_2__1 
       (.I0(\counter_reg_n_0_[8] ),
        .I1(\counter[7]_i_2__1_n_0 ),
        .I2(\counter_reg_n_0_[7] ),
        .I3(\counter_reg_n_0_[9] ),
        .O(\FSM_onehot_phase_state[3]_i_2__1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair17" *) 
  LUT5 #(
    .INIT(32'hFFFF0001)) 
    \FSM_onehot_phase_state[3]_i_3__1 
       (.I0(\FSM_onehot_phase_state_reg_n_0_[0] ),
        .I1(p_2_in),
        .I2(Q[1]),
        .I3(Q[2]),
        .I4(Q[0]),
        .O(\FSM_onehot_phase_state[3]_i_3__1_n_0 ));
  LUT6 #(
    .INIT(64'h000F000000040000)) 
    \FSM_onehot_phase_state[4]_i_1__1 
       (.I0(\FSM_onehot_phase_state[5]_i_2__1_n_0 ),
        .I1(p_2_in),
        .I2(switching_signals[1]),
        .I3(switching_signals[0]),
        .I4(enable),
        .I5(Q[1]),
        .O(\FSM_onehot_phase_state[4]_i_1__1_n_0 ));
  LUT6 #(
    .INIT(64'hF000000040000000)) 
    \FSM_onehot_phase_state[5]_i_1__1 
       (.I0(\FSM_onehot_phase_state[5]_i_2__1_n_0 ),
        .I1(\FSM_onehot_phase_state_reg_n_0_[0] ),
        .I2(switching_signals[1]),
        .I3(switching_signals[0]),
        .I4(enable),
        .I5(Q[2]),
        .O(\FSM_onehot_phase_state[5]_i_1__1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair18" *) 
  LUT5 #(
    .INIT(32'hFFFEFFFF)) 
    \FSM_onehot_phase_state[5]_i_2__1 
       (.I0(\counter_reg_n_0_[9] ),
        .I1(\counter_reg_n_0_[7] ),
        .I2(\counter[7]_i_2__1_n_0 ),
        .I3(\counter_reg_n_0_[8] ),
        .I4(\counter_reg_n_0_[0] ),
        .O(\FSM_onehot_phase_state[5]_i_2__1_n_0 ));
  (* FSM_ENCODED_STATES = "pos_state:100000,neg_state:010000,int_low:000010,int_high:000001,off_state:001000,iSTATE:000100" *) 
  FDRE #(
    .INIT(1'b0)) 
    \FSM_onehot_phase_state_reg[0] 
       (.C(clock),
        .CE(1'b1),
        .D(\FSM_onehot_phase_state[0]_i_1__1_n_0 ),
        .Q(\FSM_onehot_phase_state_reg_n_0_[0] ),
        .R(1'b0));
  (* FSM_ENCODED_STATES = "pos_state:100000,neg_state:010000,int_low:000010,int_high:000001,off_state:001000,iSTATE:000100" *) 
  FDRE #(
    .INIT(1'b0)) 
    \FSM_onehot_phase_state_reg[1] 
       (.C(clock),
        .CE(1'b1),
        .D(\FSM_onehot_phase_state[1]_i_1__1_n_0 ),
        .Q(p_2_in),
        .R(1'b0));
  (* FSM_ENCODED_STATES = "pos_state:100000,neg_state:010000,int_low:000010,int_high:000001,off_state:001000,iSTATE:000100" *) 
  FDRE #(
    .INIT(1'b0)) 
    \FSM_onehot_phase_state_reg[2] 
       (.C(clock),
        .CE(1'b1),
        .D(\FSM_onehot_phase_state[2]_i_1__1_n_0 ),
        .Q(p_1_in),
        .R(1'b0));
  (* FSM_ENCODED_STATES = "pos_state:100000,neg_state:010000,int_low:000010,int_high:000001,off_state:001000,iSTATE:000100" *) 
  FDRE #(
    .INIT(1'b1)) 
    \FSM_onehot_phase_state_reg[3] 
       (.C(clock),
        .CE(1'b1),
        .D(\FSM_onehot_phase_state[3]_i_1__1_n_0 ),
        .Q(Q[0]),
        .R(1'b0));
  (* FSM_ENCODED_STATES = "pos_state:100000,neg_state:010000,int_low:000010,int_high:000001,off_state:001000,iSTATE:000100" *) 
  FDRE #(
    .INIT(1'b0)) 
    \FSM_onehot_phase_state_reg[4] 
       (.C(clock),
        .CE(1'b1),
        .D(\FSM_onehot_phase_state[4]_i_1__1_n_0 ),
        .Q(Q[1]),
        .R(1'b0));
  (* FSM_ENCODED_STATES = "pos_state:100000,neg_state:010000,int_low:000010,int_high:000001,off_state:001000,iSTATE:000100" *) 
  FDRE #(
    .INIT(1'b0)) 
    \FSM_onehot_phase_state_reg[5] 
       (.C(clock),
        .CE(1'b1),
        .D(\FSM_onehot_phase_state[5]_i_1__1_n_0 ),
        .Q(Q[2]),
        .R(1'b0));
  LUT6 #(
    .INIT(64'hAAA8FFFFAAAAAAAA)) 
    \counter[0]_i_1__1 
       (.I0(deadtime[0]),
        .I1(Q[0]),
        .I2(Q[2]),
        .I3(Q[1]),
        .I4(\counter_reg_n_0_[0] ),
        .I5(\counter[9]_i_4__1_n_0 ),
        .O(\counter[0]_i_1__1_n_0 ));
  LUT6 #(
    .INIT(64'hF8F8F8888F8F8F88)) 
    \counter[1]_i_1__1 
       (.I0(\counter[9]_i_6__1_n_0 ),
        .I1(deadtime[1]),
        .I2(\counter_reg_n_0_[1] ),
        .I3(p_2_in),
        .I4(\FSM_onehot_phase_state_reg_n_0_[0] ),
        .I5(\counter_reg_n_0_[0] ),
        .O(\counter[1]_i_1__1_n_0 ));
  LUT6 #(
    .INIT(64'hFF888888F8888F88)) 
    \counter[2]_i_1__1 
       (.I0(\counter[9]_i_6__1_n_0 ),
        .I1(deadtime[2]),
        .I2(\counter_reg_n_0_[0] ),
        .I3(\counter[9]_i_4__1_n_0 ),
        .I4(\counter_reg_n_0_[2] ),
        .I5(\counter_reg_n_0_[1] ),
        .O(\counter[2]_i_1__1_n_0 ));
  LUT6 #(
    .INIT(64'hFFF88888888F8888)) 
    \counter[3]_i_1__1 
       (.I0(\counter[9]_i_6__1_n_0 ),
        .I1(deadtime[3]),
        .I2(\counter_reg_n_0_[0] ),
        .I3(\counter[3]_i_2__1_n_0 ),
        .I4(\counter[9]_i_4__1_n_0 ),
        .I5(\counter_reg_n_0_[3] ),
        .O(\counter[3]_i_1__1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair22" *) 
  LUT2 #(
    .INIT(4'hE)) 
    \counter[3]_i_2__1 
       (.I0(\counter_reg_n_0_[1] ),
        .I1(\counter_reg_n_0_[2] ),
        .O(\counter[3]_i_2__1_n_0 ));
  LUT6 #(
    .INIT(64'hFFF88888888F8888)) 
    \counter[4]_i_1__1 
       (.I0(\counter[9]_i_6__1_n_0 ),
        .I1(deadtime[4]),
        .I2(\counter_reg_n_0_[0] ),
        .I3(\counter[4]_i_2__1_n_0 ),
        .I4(\counter[9]_i_4__1_n_0 ),
        .I5(\counter_reg_n_0_[4] ),
        .O(\counter[4]_i_1__1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair22" *) 
  LUT3 #(
    .INIT(8'hFE)) 
    \counter[4]_i_2__1 
       (.I0(\counter_reg_n_0_[2] ),
        .I1(\counter_reg_n_0_[1] ),
        .I2(\counter_reg_n_0_[3] ),
        .O(\counter[4]_i_2__1_n_0 ));
  LUT6 #(
    .INIT(64'hFFC0C0C0FF848484)) 
    \counter[5]_i_1__1 
       (.I0(\counter_reg_n_0_[0] ),
        .I1(\counter[9]_i_4__1_n_0 ),
        .I2(\counter_reg_n_0_[5] ),
        .I3(deadtime[5]),
        .I4(\counter[9]_i_6__1_n_0 ),
        .I5(\counter[5]_i_2__1_n_0 ),
        .O(\counter[5]_i_1__1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair19" *) 
  LUT4 #(
    .INIT(16'hFFFE)) 
    \counter[5]_i_2__1 
       (.I0(\counter_reg_n_0_[3] ),
        .I1(\counter_reg_n_0_[1] ),
        .I2(\counter_reg_n_0_[2] ),
        .I3(\counter_reg_n_0_[4] ),
        .O(\counter[5]_i_2__1_n_0 ));
  LUT6 #(
    .INIT(64'hFFC0C0C0FF848484)) 
    \counter[6]_i_1__1 
       (.I0(\counter_reg_n_0_[0] ),
        .I1(\counter[9]_i_4__1_n_0 ),
        .I2(\counter_reg_n_0_[6] ),
        .I3(deadtime[6]),
        .I4(\counter[9]_i_6__1_n_0 ),
        .I5(\counter[6]_i_2__1_n_0 ),
        .O(\counter[6]_i_1__1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair19" *) 
  LUT5 #(
    .INIT(32'hFFFFFFFE)) 
    \counter[6]_i_2__1 
       (.I0(\counter_reg_n_0_[4] ),
        .I1(\counter_reg_n_0_[2] ),
        .I2(\counter_reg_n_0_[1] ),
        .I3(\counter_reg_n_0_[3] ),
        .I4(\counter_reg_n_0_[5] ),
        .O(\counter[6]_i_2__1_n_0 ));
  LUT6 #(
    .INIT(64'hFFC0C0C0FF848484)) 
    \counter[7]_i_1__1 
       (.I0(\counter_reg_n_0_[0] ),
        .I1(\counter[9]_i_4__1_n_0 ),
        .I2(\counter_reg_n_0_[7] ),
        .I3(deadtime[7]),
        .I4(\counter[9]_i_6__1_n_0 ),
        .I5(\counter[7]_i_2__1_n_0 ),
        .O(\counter[7]_i_1__1_n_0 ));
  LUT6 #(
    .INIT(64'hFFFFFFFFFFFFFFFE)) 
    \counter[7]_i_2__1 
       (.I0(\counter_reg_n_0_[5] ),
        .I1(\counter_reg_n_0_[3] ),
        .I2(\counter_reg_n_0_[1] ),
        .I3(\counter_reg_n_0_[2] ),
        .I4(\counter_reg_n_0_[4] ),
        .I5(\counter_reg_n_0_[6] ),
        .O(\counter[7]_i_2__1_n_0 ));
  LUT6 #(
    .INIT(64'hFFC0C0C0FF848484)) 
    \counter[8]_i_1__1 
       (.I0(\counter_reg_n_0_[0] ),
        .I1(\counter[9]_i_4__1_n_0 ),
        .I2(\counter_reg_n_0_[8] ),
        .I3(deadtime[8]),
        .I4(\counter[9]_i_6__1_n_0 ),
        .I5(\counter[8]_i_2__1_n_0 ),
        .O(\counter[8]_i_1__1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair21" *) 
  LUT2 #(
    .INIT(4'hE)) 
    \counter[8]_i_2__1 
       (.I0(\counter[7]_i_2__1_n_0 ),
        .I1(\counter_reg_n_0_[7] ),
        .O(\counter[8]_i_2__1_n_0 ));
  LUT6 #(
    .INIT(64'hFFFFFFFFFFFFF808)) 
    \counter[9]_i_1__1 
       (.I0(Q[0]),
        .I1(enable),
        .I2(\counter[9]_i_3__1_n_0 ),
        .I3(Q[1]),
        .I4(\counter[9]_i_4__1_n_0 ),
        .I5(\counter[9]_i_5__1_n_0 ),
        .O(counter));
  LUT6 #(
    .INIT(64'hFFC0C0C0FF848484)) 
    \counter[9]_i_2__1 
       (.I0(\counter_reg_n_0_[0] ),
        .I1(\counter[9]_i_4__1_n_0 ),
        .I2(\counter_reg_n_0_[9] ),
        .I3(deadtime[9]),
        .I4(\counter[9]_i_6__1_n_0 ),
        .I5(\counter[9]_i_7__1_n_0 ),
        .O(\counter[9]_i_2__1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair20" *) 
  LUT2 #(
    .INIT(4'hE)) 
    \counter[9]_i_3__1 
       (.I0(switching_signals[0]),
        .I1(switching_signals[1]),
        .O(\counter[9]_i_3__1_n_0 ));
  LUT2 #(
    .INIT(4'hE)) 
    \counter[9]_i_4__1 
       (.I0(\FSM_onehot_phase_state_reg_n_0_[0] ),
        .I1(p_2_in),
        .O(\counter[9]_i_4__1_n_0 ));
  LUT6 #(
    .INIT(64'hEAFF6AFFEBAA6BAA)) 
    \counter[9]_i_5__1 
       (.I0(Q[2]),
        .I1(switching_signals[1]),
        .I2(switching_signals[0]),
        .I3(enable),
        .I4(Q[0]),
        .I5(Q[1]),
        .O(\counter[9]_i_5__1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair17" *) 
  LUT5 #(
    .INIT(32'hFFFFFFF1)) 
    \counter[9]_i_6__1 
       (.I0(\FSM_onehot_phase_state_reg_n_0_[0] ),
        .I1(p_2_in),
        .I2(Q[0]),
        .I3(Q[2]),
        .I4(Q[1]),
        .O(\counter[9]_i_6__1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair21" *) 
  LUT3 #(
    .INIT(8'hFE)) 
    \counter[9]_i_7__1 
       (.I0(\counter_reg_n_0_[7] ),
        .I1(\counter[7]_i_2__1_n_0 ),
        .I2(\counter_reg_n_0_[8] ),
        .O(\counter[9]_i_7__1_n_0 ));
  FDRE #(
    .INIT(1'b0)) 
    \counter_reg[0] 
       (.C(clock),
        .CE(counter),
        .D(\counter[0]_i_1__1_n_0 ),
        .Q(\counter_reg_n_0_[0] ),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \counter_reg[1] 
       (.C(clock),
        .CE(counter),
        .D(\counter[1]_i_1__1_n_0 ),
        .Q(\counter_reg_n_0_[1] ),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \counter_reg[2] 
       (.C(clock),
        .CE(counter),
        .D(\counter[2]_i_1__1_n_0 ),
        .Q(\counter_reg_n_0_[2] ),
        .R(1'b0));
  FDRE #(
    .INIT(1'b1)) 
    \counter_reg[3] 
       (.C(clock),
        .CE(counter),
        .D(\counter[3]_i_1__1_n_0 ),
        .Q(\counter_reg_n_0_[3] ),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \counter_reg[4] 
       (.C(clock),
        .CE(counter),
        .D(\counter[4]_i_1__1_n_0 ),
        .Q(\counter_reg_n_0_[4] ),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \counter_reg[5] 
       (.C(clock),
        .CE(counter),
        .D(\counter[5]_i_1__1_n_0 ),
        .Q(\counter_reg_n_0_[5] ),
        .R(1'b0));
  FDRE #(
    .INIT(1'b1)) 
    \counter_reg[6] 
       (.C(clock),
        .CE(counter),
        .D(\counter[6]_i_1__1_n_0 ),
        .Q(\counter_reg_n_0_[6] ),
        .R(1'b0));
  FDRE #(
    .INIT(1'b1)) 
    \counter_reg[7] 
       (.C(clock),
        .CE(counter),
        .D(\counter[7]_i_1__1_n_0 ),
        .Q(\counter_reg_n_0_[7] ),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \counter_reg[8] 
       (.C(clock),
        .CE(counter),
        .D(\counter[8]_i_1__1_n_0 ),
        .Q(\counter_reg_n_0_[8] ),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \counter_reg[9] 
       (.C(clock),
        .CE(counter),
        .D(\counter[9]_i_2__1_n_0 ),
        .Q(\counter_reg_n_0_[9] ),
        .R(1'b0));
endmodule

(* ORIG_REF_NAME = "top_npc_state_machine" *) 
module zusys_top_npc_state_machine_0_0_top_npc_state_machine
   (A_S1,
    A_S4,
    A_phase_off,
    B_S1,
    B_S4,
    B_phase_off,
    C_S1,
    C_S4,
    C_phase_off,
    A_S2,
    A_S3,
    B_S2,
    B_S3,
    C_S2,
    C_S3,
    clock,
    switching_signals,
    enable,
    deadtime);
  output A_S1;
  output A_S4;
  output A_phase_off;
  output B_S1;
  output B_S4;
  output B_phase_off;
  output C_S1;
  output C_S4;
  output C_phase_off;
  output A_S2;
  output A_S3;
  output B_S2;
  output B_S3;
  output C_S2;
  output C_S3;
  input clock;
  input [5:0]switching_signals;
  input enable;
  input [9:0]deadtime;

  wire A_S1;
  wire A_S2;
  wire A_S3;
  wire A_S4;
  wire A_phase_off;
  wire B_S1;
  wire B_S2;
  wire B_S3;
  wire B_S4;
  wire B_phase_off;
  wire C_S1;
  wire C_S2;
  wire C_S3;
  wire C_S4;
  wire C_phase_off;
  wire clock;
  wire [9:0]deadtime;
  wire enable;
  wire [5:0]switching_signals;

  zusys_top_npc_state_machine_0_0_npc_phase_state_machine npc_FCM_phase_A
       (.A_S2(A_S2),
        .A_S3(A_S3),
        .Q({A_S1,A_S4,A_phase_off}),
        .clock(clock),
        .deadtime(deadtime),
        .enable(enable),
        .switching_signals(switching_signals[1:0]));
  zusys_top_npc_state_machine_0_0_npc_phase_state_machine_0 npc_FCM_phase_B
       (.B_S2(B_S2),
        .B_S3(B_S3),
        .Q({B_S1,B_S4,B_phase_off}),
        .clock(clock),
        .deadtime(deadtime),
        .enable(enable),
        .switching_signals(switching_signals[3:2]));
  zusys_top_npc_state_machine_0_0_npc_phase_state_machine_1 npc_FCM_phase_C
       (.C_S2(C_S2),
        .C_S3(C_S3),
        .Q({C_S1,C_S4,C_phase_off}),
        .clock(clock),
        .deadtime(deadtime),
        .enable(enable),
        .switching_signals(switching_signals[5:4]));
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
