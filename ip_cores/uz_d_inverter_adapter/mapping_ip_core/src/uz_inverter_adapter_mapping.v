//Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
//--------------------------------------------------------------------------------
//Tool Version: Vivado v.2020.1.1 (win64) Build 2960000 Wed Aug  5 22:57:20 MDT 2020
//Date        : Thu Apr  8 15:57:57 2021
//Host        : ELN176252 running 64-bit major release  (build 9200)
//Command     : generate_target uz_d_inverter_adapter_mapping.bd
//Design      : uz_d_inverter_adapter_mapping
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
(* CORE_GENERATION_INFO = "uz_inverter_adapter_mapping,IP_Integrator,{x_ipVendor=xilinx.com,x_ipLibrary=BlockDiagram,x_ipName=uz_inverter_adapter_mapping,x_ipVersion=1.00.a,x_ipLanguage=VERILOG,numBlks=10,numReposBlks=10,numNonXlnxBlks=0,numHierBlks=0,maxHierDepth=0,numSysgenBlks=0,numHlsBlks=0,numHdlrefBlks=0,numPkgbdBlks=0,bdsource=USER,synth_mode=OOC_per_IP}" *) (* HW_HANDOFF = "uz_inverter_adapter_mapping.hwdef" *) 
module uz_inverter_adapter_mapping
   (DIG_IO_17,
    FAULT,
    H1_FAULT,
    H1_OC,
    H1_Temp,
    H2_FAULT,
    H2_OC,
    H2_Temp,
    H3_FAULT,
    H3_OC,
    H3_Temp,
    L1_FAULT,
    L1_OC,
    L1_Temp,
    L2_FAULT,
    L2_OC,
    L2_Temp,
    L3_FAULT,
    L3_OC,
    L3_Temp,
    OC,
    Temp,
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
  output [5:0]FAULT;
  input H1_FAULT;
  input H1_OC;
  input H1_Temp;
  input H2_FAULT;
  input H2_OC;
  input H2_Temp;
  input H3_FAULT;
  input H3_OC;
  input H3_Temp;
  input L1_FAULT;
  input L1_OC;
  input L1_Temp;
  input L2_FAULT;
  input L2_OC;
  input L2_Temp;
  input L3_FAULT;
  input L3_OC;
  input L3_Temp;
  output [5:0]OC;
  output [5:0]Temp;
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

  wire H1_FAULT_1;
  wire H1_OC_1;
  wire H1_Temp_1;
  wire H2_FAULT_1;
  wire H2_OC_1;
  wire H2_Temp_1;
  wire H3_FAULT_1;
  wire H3_OC_1;
  wire H3_Temp_1;
  wire L1_FAULT_1;
  wire L1_OC_1;
  wire L1_Temp_1;
  wire L2_FAULT_1;
  wire L2_OC_1;
  wire L2_Temp_1;
  wire L3_FAULT_1;
  wire L3_OC_1;
  wire L3_Temp_1;
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

  assign FAULT[5:0] = xlconcat_3_dout;
  assign H1_FAULT_1 = H1_FAULT;
  assign H1_OC_1 = H1_OC;
  assign H1_Temp_1 = H1_Temp;
  assign H2_FAULT_1 = H2_FAULT;
  assign H2_OC_1 = H2_OC;
  assign H2_Temp_1 = H2_Temp;
  assign H3_FAULT_1 = H3_FAULT;
  assign H3_OC_1 = H3_OC;
  assign H3_Temp_1 = H3_Temp;
  assign L1_FAULT_1 = L1_FAULT;
  assign L1_OC_1 = L1_OC;
  assign L1_Temp_1 = L1_Temp;
  assign L2_FAULT_1 = L2_FAULT;
  assign L2_OC_1 = L2_OC;
  assign L2_Temp_1 = L2_Temp;
  assign L3_FAULT_1 = L3_FAULT;
  assign L3_OC_1 = L3_OC;
  assign L3_Temp_1 = L3_Temp;
  assign OC[5:0] = xlconcat_2_dout;
  assign Temp[5:0] = xlconcat_1_dout;
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
  uz_inverter_adapter_mapping_xlconcat_0_0 xlconcat_0
       (.In0(I0_DIAG_1),
        .In1(I1_DIAG_1),
        .In2(I2_DIAG_1),
        .In3(I3_DIAG_1),
        .dout(xlconcat_0_dout));
  uz_inverter_adapter_mapping_xlconcat_0_1 xlconcat_1
       (.In0(H1_Temp_1),
        .In1(L1_Temp_1),
        .In2(H2_Temp_1),
        .In3(L2_Temp_1),
        .In4(H3_Temp_1),
        .In5(L3_Temp_1),
        .dout(xlconcat_1_dout));
  uz_inverter_adapter_mapping_xlconcat_1_0 xlconcat_2
       (.In0(H1_OC_1),
        .In1(L1_OC_1),
        .In2(H2_OC_1),
        .In3(L2_OC_1),
        .In4(H3_OC_1),
        .In5(L3_OC_1),
        .dout(xlconcat_2_dout));
  uz_inverter_adapter_mapping_xlconcat_2_0 xlconcat_3
       (.In0(H1_FAULT_1),
        .In1(L1_FAULT_1),
        .In2(H2_FAULT_1),
        .In3(L2_FAULT_1),
        .In4(L3_FAULT_1),
        .In5(H3_FAULT_1),
        .dout(xlconcat_3_dout));
  uz_inverter_adapter_mapping_xlslice_0_0 xlslice_0
       (.Din(Gates_1),
        .Dout(xlslice_0_Dout));
  uz_inverter_adapter_mapping_xlslice_0_1 xlslice_1
       (.Din(Gates_1),
        .Dout(xlslice_1_Dout));
  uz_inverter_adapter_mapping_xlslice_1_0 xlslice_2
       (.Din(Gates_1),
        .Dout(xlslice_2_Dout));
  uz_inverter_adapter_mapping_xlslice_1_1 xlslice_3
       (.Din(Gates_1),
        .Dout(xlslice_3_Dout));
  uz_inverter_adapter_mapping_xlslice_1_2 xlslice_4
       (.Din(Gates_1),
        .Dout(xlslice_4_Dout));
  uz_inverter_adapter_mapping_xlslice_1_3 xlslice_5
       (.Din(Gates_1),
        .Dout(xlslice_5_Dout));
endmodule
