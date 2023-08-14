// Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// --------------------------------------------------------------------------------
// Tool Version: Vivado v.2020.1.1 (win64) Build 2960000 Wed Aug  5 22:57:20 MDT 2020
// Date        : Mon Feb 28 14:42:09 2022
// Host        : enc177112 running 64-bit major release  (build 9200)
// Command     : write_verilog -force -mode synth_stub
//               c:/GIT/UltraZohm/software/ultrazohm_sw_develop/vivado/zusys/ip/zusys_uz_pu_con_ip_0_1/zusys_uz_pu_con_ip_0_1_stub.v
// Design      : zusys_uz_pu_con_ip_0_1
// Purpose     : Stub declaration of top-level module interface
// Device      : xczu9eg-ffvc900-1-e
// --------------------------------------------------------------------------------

// This empty module with port declaration file causes synthesis tools to infer a black box for IP.
// The synthesis directives are for Synopsys Synplify support to prevent IO buffer insertion.
// Please paste the declaration into a Verilog source file or add the file as an additional source.
(* x_core_info = "uz_pu_con_ip,Vivado 2020.1.1" *)
module zusys_uz_pu_con_ip_0_1(IPCORE_CLK, IPCORE_RESETN, in0, in1, in2, in3, in4, 
  in5, in6, in7, in8, in9, in10, in11, in12, in13, in14, in15, in16, in17, in18, in19, in20, in21, in22, in23, in24, in25, 
  in26, in27, in28, in29, in30, in31, adc_trigger, AXI4_Lite_ACLK, AXI4_Lite_ARESETN, 
  AXI4_Lite_AWADDR, AXI4_Lite_AWVALID, AXI4_Lite_WDATA, AXI4_Lite_WSTRB, AXI4_Lite_WVALID, 
  AXI4_Lite_BREADY, AXI4_Lite_ARADDR, AXI4_Lite_ARVALID, AXI4_Lite_RREADY, out0, out1, out2, 
  out3, out4, out5, out6, out7, out8, out9, out10, out11, out12, out13, out14, out15, out16, out17, out18, out19, 
  out20, out21, out22, out23, out24, out25, out26, out27, out28, out29, out30, out31, out_valid, 
  AXI4_Lite_AWREADY, AXI4_Lite_WREADY, AXI4_Lite_BRESP, AXI4_Lite_BVALID, 
  AXI4_Lite_ARREADY, AXI4_Lite_RDATA, AXI4_Lite_RRESP, AXI4_Lite_RVALID)
/* synthesis syn_black_box black_box_pad_pin="IPCORE_CLK,IPCORE_RESETN,in0[26:0],in1[26:0],in2[26:0],in3[26:0],in4[26:0],in5[26:0],in6[26:0],in7[26:0],in8[26:0],in9[26:0],in10[26:0],in11[26:0],in12[26:0],in13[26:0],in14[26:0],in15[26:0],in16[26:0],in17[26:0],in18[26:0],in19[26:0],in20[26:0],in21[26:0],in22[26:0],in23[26:0],in24[26:0],in25[26:0],in26[26:0],in27[26:0],in28[26:0],in29[26:0],in30[26:0],in31[26:0],adc_trigger,AXI4_Lite_ACLK,AXI4_Lite_ARESETN,AXI4_Lite_AWADDR[15:0],AXI4_Lite_AWVALID,AXI4_Lite_WDATA[31:0],AXI4_Lite_WSTRB[3:0],AXI4_Lite_WVALID,AXI4_Lite_BREADY,AXI4_Lite_ARADDR[15:0],AXI4_Lite_ARVALID,AXI4_Lite_RREADY,out0[17:0],out1[17:0],out2[17:0],out3[17:0],out4[17:0],out5[17:0],out6[17:0],out7[17:0],out8[17:0],out9[17:0],out10[17:0],out11[17:0],out12[17:0],out13[17:0],out14[17:0],out15[17:0],out16[17:0],out17[17:0],out18[17:0],out19[17:0],out20[17:0],out21[17:0],out22[17:0],out23[17:0],out24[17:0],out25[17:0],out26[17:0],out27[17:0],out28[17:0],out29[17:0],out30[17:0],out31[17:0],out_valid,AXI4_Lite_AWREADY,AXI4_Lite_WREADY,AXI4_Lite_BRESP[1:0],AXI4_Lite_BVALID,AXI4_Lite_ARREADY,AXI4_Lite_RDATA[31:0],AXI4_Lite_RRESP[1:0],AXI4_Lite_RVALID" */;
  input IPCORE_CLK;
  input IPCORE_RESETN;
  input [26:0]in0;
  input [26:0]in1;
  input [26:0]in2;
  input [26:0]in3;
  input [26:0]in4;
  input [26:0]in5;
  input [26:0]in6;
  input [26:0]in7;
  input [26:0]in8;
  input [26:0]in9;
  input [26:0]in10;
  input [26:0]in11;
  input [26:0]in12;
  input [26:0]in13;
  input [26:0]in14;
  input [26:0]in15;
  input [26:0]in16;
  input [26:0]in17;
  input [26:0]in18;
  input [26:0]in19;
  input [26:0]in20;
  input [26:0]in21;
  input [26:0]in22;
  input [26:0]in23;
  input [26:0]in24;
  input [26:0]in25;
  input [26:0]in26;
  input [26:0]in27;
  input [26:0]in28;
  input [26:0]in29;
  input [26:0]in30;
  input [26:0]in31;
  input adc_trigger;
  input AXI4_Lite_ACLK;
  input AXI4_Lite_ARESETN;
  input [15:0]AXI4_Lite_AWADDR;
  input AXI4_Lite_AWVALID;
  input [31:0]AXI4_Lite_WDATA;
  input [3:0]AXI4_Lite_WSTRB;
  input AXI4_Lite_WVALID;
  input AXI4_Lite_BREADY;
  input [15:0]AXI4_Lite_ARADDR;
  input AXI4_Lite_ARVALID;
  input AXI4_Lite_RREADY;
  output [17:0]out0;
  output [17:0]out1;
  output [17:0]out2;
  output [17:0]out3;
  output [17:0]out4;
  output [17:0]out5;
  output [17:0]out6;
  output [17:0]out7;
  output [17:0]out8;
  output [17:0]out9;
  output [17:0]out10;
  output [17:0]out11;
  output [17:0]out12;
  output [17:0]out13;
  output [17:0]out14;
  output [17:0]out15;
  output [17:0]out16;
  output [17:0]out17;
  output [17:0]out18;
  output [17:0]out19;
  output [17:0]out20;
  output [17:0]out21;
  output [17:0]out22;
  output [17:0]out23;
  output [17:0]out24;
  output [17:0]out25;
  output [17:0]out26;
  output [17:0]out27;
  output [17:0]out28;
  output [17:0]out29;
  output [17:0]out30;
  output [17:0]out31;
  output out_valid;
  output AXI4_Lite_AWREADY;
  output AXI4_Lite_WREADY;
  output [1:0]AXI4_Lite_BRESP;
  output AXI4_Lite_BVALID;
  output AXI4_Lite_ARREADY;
  output [31:0]AXI4_Lite_RDATA;
  output [1:0]AXI4_Lite_RRESP;
  output AXI4_Lite_RVALID;
endmodule
