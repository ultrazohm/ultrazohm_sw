//Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
//--------------------------------------------------------------------------------
//Tool Version: Vivado v.2020.1.1 (win64) Build 2960000 Wed Aug  5 22:57:20 MDT 2020
//Date        : Thu Apr  8 15:57:57 2021
//Host        : ELN176252 running 64-bit major release  (build 9200)
//Command     : generate_target UZ_D_GaN_Inverter_Mapping.bd
//Design      : UZ_D_GaN_Inverter_Mapping
//Purpose     : IP block netlist
//--------------------------------------------------------------------------------
`timescale 1 ps / 1 ps

/* DIG_IO_01
DIG_IO_15
DIG_IO_02
DIG_IO_03
DIG_IO_04
DIG_IO_05
DIG_IO_06 */
(* CORE_GENERATION_INFO = "UZ_D_GaN_Inverter_Mapping,IP_Integrator,{x_ipVendor=xilinx.com,x_ipLibrary=BlockDiagram,x_ipName=UZ_D_GaN_Inverter_Mapping,x_ipVersion=1.00.a,x_ipLanguage=VERILOG,numBlks=10,numReposBlks=10,numNonXlnxBlks=0,numHierBlks=0,maxHierDepth=0,numSysgenBlks=0,numHlsBlks=0,numHdlrefBlks=0,numPkgbdBlks=0,bdsource=USER,synth_mode=OOC_per_IP}" *) (* HW_HANDOFF = "UZ_D_GaN_Inverter_Mapping.hwdef" *) 
module UZ_D_GaN_Inverter_Mapping
   (DIG_IO_17,
    GaN_FAULT,
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
    Gates,
    I0_DIAG,
    I1_DIAG,
    I2_DIAG,
    I3_DIAG,
    I_DIAG,
    PWM_EN,
    PWM_ENABLE,
    PWM_H1,
    PWM_H2,
    PWM_H3,
    PWM_L1,
    PWM_L2,
    PWM_L3);
  input DIG_IO_17;
  output [5:0]GaN_FAULT;
  input GaN_H1_FAULT;
  input GaN_H1_OC;
  input GaN_H1_Temp;
  input GaN_H2_FAULT;
  input GaN_H2_OC;
  input GaN_H2_Temp;
  input GaN_H3_FAULT;
  input GaN_H3_OC;
  input GaN_H3_Temp;
  input GaN_L1_FAULT;
  input GaN_L1_OC;
  input GaN_L1_Temp;
  input GaN_L2_FAULT;
  input GaN_L2_OC;
  input GaN_L2_Temp;
  input GaN_L3_FAULT;
  input GaN_L3_OC;
  input GaN_L3_Temp;
  output [5:0]GaN_OC;
  output [5:0]GaN_Temp;
  input [5:0]Gates;
  input I0_DIAG;
  input I1_DIAG;
  input I2_DIAG;
  input I3_DIAG;
  output [3:0]I_DIAG;
  output PWM_EN;
  input PWM_ENABLE;
  output [0:0]PWM_H1;
  output [0:0]PWM_H2;
  output [0:0]PWM_H3;
  output [0:0]PWM_L1;
  output [0:0]PWM_L2;
  output [0:0]PWM_L3;

  wire GaN_H1_FAULT_1;
  wire GaN_H1_OC_1;
  wire GaN_H1_Temp_1;
  wire GaN_H2_FAULT_1;
  wire GaN_H2_OC_1;
  wire GaN_H2_Temp_1;
  wire GaN_H3_FAULT_1;
  wire GaN_H3_OC_1;
  wire GaN_H3_Temp_1;
  wire GaN_L1_FAULT_1;
  wire GaN_L1_OC_1;
  wire GaN_L1_Temp_1;
  wire GaN_L2_FAULT_1;
  wire GaN_L2_OC_1;
  wire GaN_L2_Temp_1;
  wire GaN_L3_FAULT_1;
  wire GaN_L3_OC_1;
  wire GaN_L3_Temp_1;
  wire [5:0]Gates_1;
  wire I0_DIAG_1;
  wire I1_DIAG_1;
  wire I2_DIAG_1;
  wire I3_DIAG_1;
  wire PWM_ENABLE_1;
  wire [3:0]xlconcat_0_dout;
  wire [5:0]xlconcat_1_dout;
  wire [5:0]xlconcat_2_dout;
  wire [5:0]xlconcat_3_dout;
  wire [0:0]xlslice_0_Dout;
  wire [0:0]xlslice_1_Dout;
  wire [0:0]xlslice_2_Dout;
  wire [0:0]xlslice_3_Dout;
  wire [0:0]xlslice_4_Dout;
  wire [0:0]xlslice_5_Dout;

  assign GaN_FAULT[5:0] = xlconcat_3_dout;
  assign GaN_H1_FAULT_1 = GaN_H1_FAULT;
  assign GaN_H1_OC_1 = GaN_H1_OC;
  assign GaN_H1_Temp_1 = GaN_H1_Temp;
  assign GaN_H2_FAULT_1 = GaN_H2_FAULT;
  assign GaN_H2_OC_1 = GaN_H2_OC;
  assign GaN_H2_Temp_1 = GaN_H2_Temp;
  assign GaN_H3_FAULT_1 = GaN_H3_FAULT;
  assign GaN_H3_OC_1 = GaN_H3_OC;
  assign GaN_H3_Temp_1 = GaN_H3_Temp;
  assign GaN_L1_FAULT_1 = GaN_L1_FAULT;
  assign GaN_L1_OC_1 = GaN_L1_OC;
  assign GaN_L1_Temp_1 = GaN_L1_Temp;
  assign GaN_L2_FAULT_1 = GaN_L2_FAULT;
  assign GaN_L2_OC_1 = GaN_L2_OC;
  assign GaN_L2_Temp_1 = GaN_L2_Temp;
  assign GaN_L3_FAULT_1 = GaN_L3_FAULT;
  assign GaN_L3_OC_1 = GaN_L3_OC;
  assign GaN_L3_Temp_1 = GaN_L3_Temp;
  assign GaN_OC[5:0] = xlconcat_2_dout;
  assign GaN_Temp[5:0] = xlconcat_1_dout;
  assign Gates_1 = Gates[5:0];
  assign I0_DIAG_1 = I0_DIAG;
  assign I1_DIAG_1 = I1_DIAG;
  assign I2_DIAG_1 = I2_DIAG;
  assign I3_DIAG_1 = I3_DIAG;
  assign I_DIAG[3:0] = xlconcat_0_dout;
  assign PWM_EN = PWM_ENABLE_1;
  assign PWM_ENABLE_1 = PWM_ENABLE;
  assign PWM_H1[0] = xlslice_0_Dout;
  assign PWM_H2[0] = xlslice_2_Dout;
  assign PWM_H3[0] = xlslice_4_Dout;
  assign PWM_L1[0] = xlslice_1_Dout;
  assign PWM_L2[0] = xlslice_3_Dout;
  assign PWM_L3[0] = xlslice_5_Dout;
  UZ_D_GaN_Inverter_Mapping_xlconcat_0_0 xlconcat_0
       (.In0(I0_DIAG_1),
        .In1(I1_DIAG_1),
        .In2(I2_DIAG_1),
        .In3(I3_DIAG_1),
        .dout(xlconcat_0_dout));
  UZ_D_GaN_Inverter_Mapping_xlconcat_0_1 xlconcat_1
       (.In0(GaN_H1_Temp_1),
        .In1(GaN_L1_Temp_1),
        .In2(GaN_H2_Temp_1),
        .In3(GaN_L2_Temp_1),
        .In4(GaN_H3_Temp_1),
        .In5(GaN_L3_Temp_1),
        .dout(xlconcat_1_dout));
  UZ_D_GaN_Inverter_Mapping_xlconcat_1_0 xlconcat_2
       (.In0(GaN_H1_OC_1),
        .In1(GaN_L1_OC_1),
        .In2(GaN_H2_OC_1),
        .In3(GaN_L2_OC_1),
        .In4(GaN_H3_OC_1),
        .In5(GaN_L3_OC_1),
        .dout(xlconcat_2_dout));
  UZ_D_GaN_Inverter_Mapping_xlconcat_2_0 xlconcat_3
       (.In0(GaN_H1_FAULT_1),
        .In1(GaN_L1_FAULT_1),
        .In2(GaN_H2_FAULT_1),
        .In3(GaN_L2_FAULT_1),
        .In4(GaN_L3_FAULT_1),
        .In5(GaN_H3_FAULT_1),
        .dout(xlconcat_3_dout));
  UZ_D_GaN_Inverter_Mapping_xlslice_0_0 xlslice_0
       (.Din(Gates_1),
        .Dout(xlslice_0_Dout));
  UZ_D_GaN_Inverter_Mapping_xlslice_0_1 xlslice_1
       (.Din(Gates_1),
        .Dout(xlslice_1_Dout));
  UZ_D_GaN_Inverter_Mapping_xlslice_1_0 xlslice_2
       (.Din(Gates_1),
        .Dout(xlslice_2_Dout));
  UZ_D_GaN_Inverter_Mapping_xlslice_1_1 xlslice_3
       (.Din(Gates_1),
        .Dout(xlslice_3_Dout));
  UZ_D_GaN_Inverter_Mapping_xlslice_1_2 xlslice_4
       (.Din(Gates_1),
        .Dout(xlslice_4_Dout));
  UZ_D_GaN_Inverter_Mapping_xlslice_1_3 xlslice_5
       (.Din(Gates_1),
        .Dout(xlslice_5_Dout));
endmodule
