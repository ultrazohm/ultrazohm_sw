//Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
//--------------------------------------------------------------------------------
//Tool Version: Vivado v.2020.1.1 (win64) Build 2960000 Wed Aug  5 22:57:20 MDT 2020
//Date        : Thu Apr 29 10:25:27 2021
//Host        : ELN176252 running 64-bit major release  (build 9200)
//Command     : generate_target slicer_wrapper.bd
//Design      : slicer_wrapper
//Purpose     : IP block netlist
//--------------------------------------------------------------------------------
`timescale 1 ps / 1 ps

module slicer_wrapper
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

  wire [5:0]GaN_FAULT;
  wire [0:0]GaN_H1_FAULT;
  wire [0:0]GaN_H1_OC;
  wire [0:0]GaN_H1_Temp;
  wire [0:0]GaN_H2_FAULT;
  wire [0:0]GaN_H2_OC;
  wire [0:0]GaN_H2_Temp;
  wire [0:0]GaN_H3_FAULT;
  wire [0:0]GaN_H3_OC;
  wire [0:0]GaN_H3_Temp;
  wire [0:0]GaN_L1_FAULT;
  wire [0:0]GaN_L1_OC;
  wire [0:0]GaN_L1_Temp;
  wire [0:0]GaN_L2_FAULT;
  wire [0:0]GaN_L2_OC;
  wire [0:0]GaN_L2_Temp;
  wire [0:0]GaN_L3_FAULT;
  wire [0:0]GaN_L3_OC;
  wire [0:0]GaN_L3_Temp;
  wire [5:0]GaN_OC;
  wire [5:0]GaN_Temp;
  wire [0:0]I1_DIAG;
  wire [0:0]I2_DIAG;
  wire [0:0]I3_DIAG;
  wire [0:0]I_DIAG;
  wire [3:0]I_SENSE_DIAG;

  slicer slicer_i
       (.GaN_FAULT(GaN_FAULT),
        .GaN_H1_FAULT(GaN_H1_FAULT),
        .GaN_H1_OC(GaN_H1_OC),
        .GaN_H1_Temp(GaN_H1_Temp),
        .GaN_H2_FAULT(GaN_H2_FAULT),
        .GaN_H2_OC(GaN_H2_OC),
        .GaN_H2_Temp(GaN_H2_Temp),
        .GaN_H3_FAULT(GaN_H3_FAULT),
        .GaN_H3_OC(GaN_H3_OC),
        .GaN_H3_Temp(GaN_H3_Temp),
        .GaN_L1_FAULT(GaN_L1_FAULT),
        .GaN_L1_OC(GaN_L1_OC),
        .GaN_L1_Temp(GaN_L1_Temp),
        .GaN_L2_FAULT(GaN_L2_FAULT),
        .GaN_L2_OC(GaN_L2_OC),
        .GaN_L2_Temp(GaN_L2_Temp),
        .GaN_L3_FAULT(GaN_L3_FAULT),
        .GaN_L3_OC(GaN_L3_OC),
        .GaN_L3_Temp(GaN_L3_Temp),
        .GaN_OC(GaN_OC),
        .GaN_Temp(GaN_Temp),
        .I1_DIAG(I1_DIAG),
        .I2_DIAG(I2_DIAG),
        .I3_DIAG(I3_DIAG),
        .I_DIAG(I_DIAG),
        .I_SENSE_DIAG(I_SENSE_DIAG));
endmodule
