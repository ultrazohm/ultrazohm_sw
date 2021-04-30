//Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
//--------------------------------------------------------------------------------
//Tool Version: Vivado v.2020.1.1 (win64) Build 2960000 Wed Aug  5 22:57:20 MDT 2020
//Date        : Thu Apr 29 10:25:27 2021
//Host        : ELN176252 running 64-bit major release  (build 9200)
//Command     : generate_target slicer.bd
//Design      : slicer
//Purpose     : IP block netlist
//--------------------------------------------------------------------------------
`timescale 1 ps / 1 ps

(* CORE_GENERATION_INFO = "slicer,IP_Integrator,{x_ipVendor=xilinx.com,x_ipLibrary=BlockDiagram,x_ipName=slicer,x_ipVersion=1.00.a,x_ipLanguage=VERILOG,numBlks=22,numReposBlks=22,numNonXlnxBlks=0,numHierBlks=0,maxHierDepth=0,numSysgenBlks=0,numHlsBlks=0,numHdlrefBlks=0,numPkgbdBlks=0,bdsource=USER,synth_mode=OOC_per_IP}" *) (* HW_HANDOFF = "slicer.hwdef" *) 
module slicer
   (GaN_FAULT,
    GaN_H1_FAULT,
    GaN_H1_OC,
    GaN_H1_Temp,
    GaN_H2_FAULT,
    GaN_H2_OC,
    GaN_H2_Temp,
    GaN_H3_FAULT,
    GaN_H3_OC,
    GaN_H3_Temp,
    GaN_L1_FAULT,
    GaN_L1_OC,
    GaN_L1_Temp,
    GaN_L2_FAULT,
    GaN_L2_OC,
    GaN_L2_Temp,
    GaN_L3_FAULT,
    GaN_L3_OC,
    GaN_L3_Temp,
    GaN_OC,
    GaN_Temp,
    I1_DIAG,
    I2_DIAG,
    I3_DIAG,
    I_DIAG,
    I_SENSE_DIAG);
  input [5:0]GaN_FAULT;
  output [0:0]GaN_H1_FAULT;
  output [0:0]GaN_H1_OC;
  output [0:0]GaN_H1_Temp;
  output [0:0]GaN_H2_FAULT;
  output [0:0]GaN_H2_OC;
  output [0:0]GaN_H2_Temp;
  output [0:0]GaN_H3_FAULT;
  output [0:0]GaN_H3_OC;
  output [0:0]GaN_H3_Temp;
  output [0:0]GaN_L1_FAULT;
  output [0:0]GaN_L1_OC;
  output [0:0]GaN_L1_Temp;
  output [0:0]GaN_L2_FAULT;
  output [0:0]GaN_L2_OC;
  output [0:0]GaN_L2_Temp;
  output [0:0]GaN_L3_FAULT;
  output [0:0]GaN_L3_OC;
  output [0:0]GaN_L3_Temp;
  input [5:0]GaN_OC;
  input [5:0]GaN_Temp;
  output [0:0]I1_DIAG;
  output [0:0]I2_DIAG;
  output [0:0]I3_DIAG;
  output [0:0]I_DIAG;
  input [3:0]I_SENSE_DIAG;

  wire [5:0]GaN_FAULT_1;
  wire [5:0]GaN_OC_1;
  wire [5:0]GaN_Temp_1;
  wire [3:0]I_DIAG_1;
  wire [0:0]xlslice_0_Dout;
  wire [0:0]xlslice_10_Dout;
  wire [0:0]xlslice_11_Dout;
  wire [0:0]xlslice_12_Dout;
  wire [0:0]xlslice_13_Dout;
  wire [0:0]xlslice_14_Dout;
  wire [0:0]xlslice_15_Dout;
  wire [0:0]xlslice_16_Dout;
  wire [0:0]xlslice_17_Dout;
  wire [0:0]xlslice_18_Dout;
  wire [0:0]xlslice_19_Dout;
  wire [0:0]xlslice_1_Dout;
  wire [0:0]xlslice_20_Dout;
  wire [0:0]xlslice_21_Dout;
  wire [0:0]xlslice_2_Dout;
  wire [0:0]xlslice_3_Dout;
  wire [0:0]xlslice_4_Dout;
  wire [0:0]xlslice_5_Dout;
  wire [0:0]xlslice_6_Dout;
  wire [0:0]xlslice_7_Dout;
  wire [0:0]xlslice_8_Dout;
  wire [0:0]xlslice_9_Dout;

  assign GaN_FAULT_1 = GaN_FAULT[5:0];
  assign GaN_H1_FAULT[0] = xlslice_15_Dout;
  assign GaN_H1_OC[0] = xlslice_7_Dout;
  assign GaN_H1_Temp[0] = xlslice_0_Dout;
  assign GaN_H2_FAULT[0] = xlslice_17_Dout;
  assign GaN_H2_OC[0] = xlslice_9_Dout;
  assign GaN_H2_Temp[0] = xlslice_2_Dout;
  assign GaN_H3_FAULT[0] = xlslice_13_Dout;
  assign GaN_H3_OC[0] = xlslice_10_Dout;
  assign GaN_H3_Temp[0] = xlslice_4_Dout;
  assign GaN_L1_FAULT[0] = xlslice_16_Dout;
  assign GaN_L1_OC[0] = xlslice_8_Dout;
  assign GaN_L1_Temp[0] = xlslice_1_Dout;
  assign GaN_L2_FAULT[0] = xlslice_14_Dout;
  assign GaN_L2_OC[0] = xlslice_11_Dout;
  assign GaN_L2_Temp[0] = xlslice_3_Dout;
  assign GaN_L3_FAULT[0] = xlslice_12_Dout;
  assign GaN_L3_OC[0] = xlslice_6_Dout;
  assign GaN_L3_Temp[0] = xlslice_5_Dout;
  assign GaN_OC_1 = GaN_OC[5:0];
  assign GaN_Temp_1 = GaN_Temp[5:0];
  assign I1_DIAG[0] = xlslice_19_Dout;
  assign I2_DIAG[0] = xlslice_20_Dout;
  assign I3_DIAG[0] = xlslice_21_Dout;
  assign I_DIAG[0] = xlslice_18_Dout;
  assign I_DIAG_1 = I_SENSE_DIAG[3:0];
  slicer_xlslice_0_0 xlslice_0
       (.Din(GaN_Temp_1),
        .Dout(xlslice_0_Dout));
  slicer_xlslice_0_1 xlslice_1
       (.Din(GaN_Temp_1),
        .Dout(xlslice_1_Dout));
  slicer_xlslice_4_1 xlslice_10
       (.Din(GaN_OC_1),
        .Dout(xlslice_10_Dout));
  slicer_xlslice_5_0 xlslice_11
       (.Din(GaN_OC_1),
        .Dout(xlslice_11_Dout));
  slicer_xlslice_10_1 xlslice_12
       (.Din(GaN_FAULT_1),
        .Dout(xlslice_12_Dout));
  slicer_xlslice_11_1 xlslice_13
       (.Din(GaN_FAULT_1),
        .Dout(xlslice_13_Dout));
  slicer_xlslice_6_1 xlslice_14
       (.Din(GaN_FAULT_1),
        .Dout(xlslice_14_Dout));
  slicer_xlslice_7_0 xlslice_15
       (.Din(GaN_FAULT_1),
        .Dout(xlslice_15_Dout));
  slicer_xlslice_8_1 xlslice_16
       (.Din(GaN_FAULT_1),
        .Dout(xlslice_16_Dout));
  slicer_xlslice_9_1 xlslice_17
       (.Din(GaN_FAULT_1),
        .Dout(xlslice_17_Dout));
  slicer_xlslice_18_0 xlslice_18
       (.Din(I_DIAG_1),
        .Dout(xlslice_18_Dout));
  slicer_xlslice_18_1 xlslice_19
       (.Din(I_DIAG_1),
        .Dout(xlslice_19_Dout));
  slicer_xlslice_1_0 xlslice_2
       (.Din(GaN_Temp_1),
        .Dout(xlslice_2_Dout));
  slicer_xlslice_19_0 xlslice_20
       (.Din(I_DIAG_1),
        .Dout(xlslice_20_Dout));
  slicer_xlslice_20_0 xlslice_21
       (.Din(I_DIAG_1),
        .Dout(xlslice_21_Dout));
  slicer_xlslice_2_0 xlslice_3
       (.Din(GaN_Temp_1),
        .Dout(xlslice_3_Dout));
  slicer_xlslice_2_1 xlslice_4
       (.Din(GaN_Temp_1),
        .Dout(xlslice_4_Dout));
  slicer_xlslice_4_0 xlslice_5
       (.Din(GaN_Temp_1),
        .Dout(xlslice_5_Dout));
  slicer_xlslice_0_2 xlslice_6
       (.Din(GaN_OC_1),
        .Dout(xlslice_6_Dout));
  slicer_xlslice_1_1 xlslice_7
       (.Din(GaN_OC_1),
        .Dout(xlslice_7_Dout));
  slicer_xlslice_2_2 xlslice_8
       (.Din(GaN_OC_1),
        .Dout(xlslice_8_Dout));
  slicer_xlslice_3_0 xlslice_9
       (.Din(GaN_OC_1),
        .Dout(xlslice_9_Dout));
endmodule
