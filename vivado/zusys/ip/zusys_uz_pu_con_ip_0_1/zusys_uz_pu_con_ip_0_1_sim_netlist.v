// Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// --------------------------------------------------------------------------------
// Tool Version: Vivado v.2020.1.1 (win64) Build 2960000 Wed Aug  5 22:57:20 MDT 2020
// Date        : Mon Feb 28 14:42:09 2022
// Host        : enc177112 running 64-bit major release  (build 9200)
// Command     : write_verilog -force -mode funcsim
//               c:/GIT/UltraZohm/software/ultrazohm_sw_develop/vivado/zusys/ip/zusys_uz_pu_con_ip_0_1/zusys_uz_pu_con_ip_0_1_sim_netlist.v
// Design      : zusys_uz_pu_con_ip_0_1
// Purpose     : This verilog netlist is a functional simulation representation of the design and should not be modified
//               or synthesized. This netlist cannot be used for SDF annotated simulation.
// Device      : xczu9eg-ffvc900-1-e
// --------------------------------------------------------------------------------
`timescale 1 ps / 1 ps

(* CHECK_LICENSE_TYPE = "zusys_uz_pu_con_ip_0_1,uz_pu_con_ip,{}" *) (* downgradeipidentifiedwarnings = "yes" *) (* ip_definition_source = "package_project" *) 
(* x_core_info = "uz_pu_con_ip,Vivado 2020.1.1" *) 
(* NotValidForBitStream *)
module zusys_uz_pu_con_ip_0_1
   (IPCORE_CLK,
    IPCORE_RESETN,
    in0,
    in1,
    in2,
    in3,
    in4,
    in5,
    in6,
    in7,
    in8,
    in9,
    in10,
    in11,
    in12,
    in13,
    in14,
    in15,
    in16,
    in17,
    in18,
    in19,
    in20,
    in21,
    in22,
    in23,
    in24,
    in25,
    in26,
    in27,
    in28,
    in29,
    in30,
    in31,
    adc_trigger,
    AXI4_Lite_ACLK,
    AXI4_Lite_ARESETN,
    AXI4_Lite_AWADDR,
    AXI4_Lite_AWVALID,
    AXI4_Lite_WDATA,
    AXI4_Lite_WSTRB,
    AXI4_Lite_WVALID,
    AXI4_Lite_BREADY,
    AXI4_Lite_ARADDR,
    AXI4_Lite_ARVALID,
    AXI4_Lite_RREADY,
    out0,
    out1,
    out2,
    out3,
    out4,
    out5,
    out6,
    out7,
    out8,
    out9,
    out10,
    out11,
    out12,
    out13,
    out14,
    out15,
    out16,
    out17,
    out18,
    out19,
    out20,
    out21,
    out22,
    out23,
    out24,
    out25,
    out26,
    out27,
    out28,
    out29,
    out30,
    out31,
    out_valid,
    AXI4_Lite_AWREADY,
    AXI4_Lite_WREADY,
    AXI4_Lite_BRESP,
    AXI4_Lite_BVALID,
    AXI4_Lite_ARREADY,
    AXI4_Lite_RDATA,
    AXI4_Lite_RRESP,
    AXI4_Lite_RVALID);
  (* x_interface_info = "xilinx.com:signal:clock:1.0 IPCORE_CLK CLK" *) (* x_interface_parameter = "XIL_INTERFACENAME IPCORE_CLK, ASSOCIATED_RESET IPCORE_RESETN, FREQ_HZ 100000000, FREQ_TOLERANCE_HZ 0, PHASE 0.000, CLK_DOMAIN zusys_zynq_ultra_ps_e_0_0_pl_clk0, INSERT_VIP 0" *) input IPCORE_CLK;
  (* x_interface_info = "xilinx.com:signal:reset:1.0 IPCORE_RESETN RST" *) (* x_interface_parameter = "XIL_INTERFACENAME IPCORE_RESETN, POLARITY ACTIVE_LOW, INSERT_VIP 0" *) input IPCORE_RESETN;
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
  (* x_interface_info = "xilinx.com:signal:clock:1.0 AXI4_Lite_signal_clock CLK" *) (* x_interface_parameter = "XIL_INTERFACENAME AXI4_Lite_signal_clock, ASSOCIATED_BUSIF AXI4_Lite, ASSOCIATED_RESET AXI4_Lite_ARESETN, FREQ_HZ 100000000, FREQ_TOLERANCE_HZ 0, PHASE 0.000, CLK_DOMAIN zusys_zynq_ultra_ps_e_0_0_pl_clk0, INSERT_VIP 0" *) input AXI4_Lite_ACLK;
  (* x_interface_info = "xilinx.com:signal:reset:1.0 AXI4_Lite_signal_reset RST" *) (* x_interface_parameter = "XIL_INTERFACENAME AXI4_Lite_signal_reset, POLARITY ACTIVE_LOW, INSERT_VIP 0" *) input AXI4_Lite_ARESETN;
  (* x_interface_info = "xilinx.com:interface:aximm:1.0 AXI4_Lite AWADDR" *) (* x_interface_parameter = "XIL_INTERFACENAME AXI4_Lite, DATA_WIDTH 32, PROTOCOL AXI4LITE, FREQ_HZ 100000000, ID_WIDTH 0, ADDR_WIDTH 16, AWUSER_WIDTH 0, ARUSER_WIDTH 0, WUSER_WIDTH 0, RUSER_WIDTH 0, BUSER_WIDTH 0, READ_WRITE_MODE READ_WRITE, HAS_BURST 0, HAS_LOCK 0, HAS_PROT 0, HAS_CACHE 0, HAS_QOS 0, HAS_REGION 0, HAS_WSTRB 1, HAS_BRESP 1, HAS_RRESP 1, SUPPORTS_NARROW_BURST 0, NUM_READ_OUTSTANDING 1, NUM_WRITE_OUTSTANDING 1, MAX_BURST_LENGTH 1, PHASE 0.000, CLK_DOMAIN zusys_zynq_ultra_ps_e_0_0_pl_clk0, NUM_READ_THREADS 1, NUM_WRITE_THREADS 1, RUSER_BITS_PER_BYTE 0, WUSER_BITS_PER_BYTE 0, INSERT_VIP 0" *) input [15:0]AXI4_Lite_AWADDR;
  (* x_interface_info = "xilinx.com:interface:aximm:1.0 AXI4_Lite AWVALID" *) input AXI4_Lite_AWVALID;
  (* x_interface_info = "xilinx.com:interface:aximm:1.0 AXI4_Lite WDATA" *) input [31:0]AXI4_Lite_WDATA;
  (* x_interface_info = "xilinx.com:interface:aximm:1.0 AXI4_Lite WSTRB" *) input [3:0]AXI4_Lite_WSTRB;
  (* x_interface_info = "xilinx.com:interface:aximm:1.0 AXI4_Lite WVALID" *) input AXI4_Lite_WVALID;
  (* x_interface_info = "xilinx.com:interface:aximm:1.0 AXI4_Lite BREADY" *) input AXI4_Lite_BREADY;
  (* x_interface_info = "xilinx.com:interface:aximm:1.0 AXI4_Lite ARADDR" *) input [15:0]AXI4_Lite_ARADDR;
  (* x_interface_info = "xilinx.com:interface:aximm:1.0 AXI4_Lite ARVALID" *) input AXI4_Lite_ARVALID;
  (* x_interface_info = "xilinx.com:interface:aximm:1.0 AXI4_Lite RREADY" *) input AXI4_Lite_RREADY;
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
  (* x_interface_info = "xilinx.com:interface:aximm:1.0 AXI4_Lite AWREADY" *) output AXI4_Lite_AWREADY;
  (* x_interface_info = "xilinx.com:interface:aximm:1.0 AXI4_Lite WREADY" *) output AXI4_Lite_WREADY;
  (* x_interface_info = "xilinx.com:interface:aximm:1.0 AXI4_Lite BRESP" *) output [1:0]AXI4_Lite_BRESP;
  (* x_interface_info = "xilinx.com:interface:aximm:1.0 AXI4_Lite BVALID" *) output AXI4_Lite_BVALID;
  (* x_interface_info = "xilinx.com:interface:aximm:1.0 AXI4_Lite ARREADY" *) output AXI4_Lite_ARREADY;
  (* x_interface_info = "xilinx.com:interface:aximm:1.0 AXI4_Lite RDATA" *) output [31:0]AXI4_Lite_RDATA;
  (* x_interface_info = "xilinx.com:interface:aximm:1.0 AXI4_Lite RRESP" *) output [1:0]AXI4_Lite_RRESP;
  (* x_interface_info = "xilinx.com:interface:aximm:1.0 AXI4_Lite RVALID" *) output AXI4_Lite_RVALID;

  wire \<const0> ;
  wire AXI4_Lite_ACLK;
  wire [15:0]AXI4_Lite_ARADDR;
  wire AXI4_Lite_ARESETN;
  wire AXI4_Lite_ARREADY;
  wire AXI4_Lite_ARVALID;
  wire [15:0]AXI4_Lite_AWADDR;
  wire AXI4_Lite_AWREADY;
  wire AXI4_Lite_AWVALID;
  wire AXI4_Lite_BREADY;
  wire AXI4_Lite_BVALID;
  wire [25:25]\^AXI4_Lite_RDATA ;
  wire AXI4_Lite_RREADY;
  wire AXI4_Lite_RVALID;
  wire [31:0]AXI4_Lite_WDATA;
  wire AXI4_Lite_WREADY;
  wire [3:0]AXI4_Lite_WSTRB;
  wire AXI4_Lite_WVALID;
  wire IPCORE_CLK;
  wire IPCORE_RESETN;
  wire adc_trigger;
  wire [26:0]in0;
  wire [26:0]in1;
  wire [26:0]in10;
  wire [26:0]in11;
  wire [26:0]in12;
  wire [26:0]in13;
  wire [26:0]in14;
  wire [26:0]in15;
  wire [26:0]in16;
  wire [26:0]in17;
  wire [26:0]in18;
  wire [26:0]in19;
  wire [26:0]in2;
  wire [26:0]in20;
  wire [26:0]in21;
  wire [26:0]in22;
  wire [26:0]in23;
  wire [26:0]in24;
  wire [26:0]in25;
  wire [26:0]in26;
  wire [26:0]in27;
  wire [26:0]in28;
  wire [26:0]in29;
  wire [26:0]in3;
  wire [26:0]in30;
  wire [26:0]in31;
  wire [26:0]in4;
  wire [26:0]in5;
  wire [26:0]in6;
  wire [26:0]in7;
  wire [26:0]in8;
  wire [26:0]in9;
  wire [17:0]out0;
  wire [17:0]out1;
  wire [17:0]out10;
  wire [17:0]out11;
  wire [17:0]out12;
  wire [17:0]out13;
  wire [17:0]out14;
  wire [17:0]out15;
  wire [17:0]out16;
  wire [17:0]out17;
  wire [17:0]out18;
  wire [17:0]out19;
  wire [17:0]out2;
  wire [17:0]out20;
  wire [17:0]out21;
  wire [17:0]out22;
  wire [17:0]out23;
  wire [17:0]out24;
  wire [17:0]out25;
  wire [17:0]out26;
  wire [17:0]out27;
  wire [17:0]out28;
  wire [17:0]out29;
  wire [17:0]out3;
  wire [17:0]out30;
  wire [17:0]out31;
  wire [17:0]out4;
  wire [17:0]out5;
  wire [17:0]out6;
  wire [17:0]out7;
  wire [17:0]out8;
  wire [17:0]out9;

  assign AXI4_Lite_BRESP[1] = \<const0> ;
  assign AXI4_Lite_BRESP[0] = \<const0> ;
  assign AXI4_Lite_RDATA[31] = \^AXI4_Lite_RDATA [25];
  assign AXI4_Lite_RDATA[30] = \<const0> ;
  assign AXI4_Lite_RDATA[29] = \<const0> ;
  assign AXI4_Lite_RDATA[28] = \<const0> ;
  assign AXI4_Lite_RDATA[27] = \<const0> ;
  assign AXI4_Lite_RDATA[26] = \<const0> ;
  assign AXI4_Lite_RDATA[25] = \^AXI4_Lite_RDATA [25];
  assign AXI4_Lite_RDATA[24] = \^AXI4_Lite_RDATA [25];
  assign AXI4_Lite_RDATA[23] = \<const0> ;
  assign AXI4_Lite_RDATA[22] = \^AXI4_Lite_RDATA [25];
  assign AXI4_Lite_RDATA[21] = \<const0> ;
  assign AXI4_Lite_RDATA[20] = \<const0> ;
  assign AXI4_Lite_RDATA[19] = \<const0> ;
  assign AXI4_Lite_RDATA[18] = \^AXI4_Lite_RDATA [25];
  assign AXI4_Lite_RDATA[17] = \<const0> ;
  assign AXI4_Lite_RDATA[16] = \<const0> ;
  assign AXI4_Lite_RDATA[15] = \<const0> ;
  assign AXI4_Lite_RDATA[14] = \<const0> ;
  assign AXI4_Lite_RDATA[13] = \^AXI4_Lite_RDATA [25];
  assign AXI4_Lite_RDATA[12] = \<const0> ;
  assign AXI4_Lite_RDATA[11] = \<const0> ;
  assign AXI4_Lite_RDATA[10] = \^AXI4_Lite_RDATA [25];
  assign AXI4_Lite_RDATA[9] = \<const0> ;
  assign AXI4_Lite_RDATA[8] = \^AXI4_Lite_RDATA [25];
  assign AXI4_Lite_RDATA[7] = \^AXI4_Lite_RDATA [25];
  assign AXI4_Lite_RDATA[6] = \^AXI4_Lite_RDATA [25];
  assign AXI4_Lite_RDATA[5] = \<const0> ;
  assign AXI4_Lite_RDATA[4] = \^AXI4_Lite_RDATA [25];
  assign AXI4_Lite_RDATA[3] = \<const0> ;
  assign AXI4_Lite_RDATA[2] = \<const0> ;
  assign AXI4_Lite_RDATA[1] = \^AXI4_Lite_RDATA [25];
  assign AXI4_Lite_RDATA[0] = \^AXI4_Lite_RDATA [25];
  assign AXI4_Lite_RRESP[1] = \<const0> ;
  assign AXI4_Lite_RRESP[0] = \<const0> ;
  assign out_valid = adc_trigger;
  GND GND
       (.G(\<const0> ));
  zusys_uz_pu_con_ip_0_1_uz_pu_con_ip U0
       (.AXI4_Lite_ACLK(AXI4_Lite_ACLK),
        .AXI4_Lite_ARADDR(AXI4_Lite_ARADDR[15:2]),
        .AXI4_Lite_ARESETN(AXI4_Lite_ARESETN),
        .AXI4_Lite_ARREADY(AXI4_Lite_ARREADY),
        .AXI4_Lite_ARVALID(AXI4_Lite_ARVALID),
        .AXI4_Lite_AWADDR(AXI4_Lite_AWADDR[15:2]),
        .AXI4_Lite_AWREADY(AXI4_Lite_AWREADY),
        .AXI4_Lite_AWVALID(AXI4_Lite_AWVALID),
        .AXI4_Lite_BREADY(AXI4_Lite_BREADY),
        .AXI4_Lite_BVALID(AXI4_Lite_BVALID),
        .AXI4_Lite_RDATA(\^AXI4_Lite_RDATA ),
        .AXI4_Lite_RREADY(AXI4_Lite_RREADY),
        .AXI4_Lite_RVALID(AXI4_Lite_RVALID),
        .AXI4_Lite_WDATA(AXI4_Lite_WDATA[17:0]),
        .AXI4_Lite_WREADY(AXI4_Lite_WREADY),
        .AXI4_Lite_WSTRB(AXI4_Lite_WSTRB),
        .AXI4_Lite_WVALID(AXI4_Lite_WVALID),
        .IPCORE_CLK(IPCORE_CLK),
        .IPCORE_RESETN(IPCORE_RESETN),
        .adc_trigger(adc_trigger),
        .in0(in0),
        .in1(in1),
        .in10(in10),
        .in11(in11),
        .in12(in12),
        .in13(in13),
        .in14(in14),
        .in15(in15),
        .in16(in16),
        .in17(in17),
        .in18(in18),
        .in19(in19),
        .in2(in2),
        .in20(in20),
        .in21(in21),
        .in22(in22),
        .in23(in23),
        .in24(in24),
        .in25(in25),
        .in26(in26),
        .in27(in27),
        .in28(in28),
        .in29(in29),
        .in3(in3),
        .in30(in30),
        .in31(in31),
        .in4(in4),
        .in5(in5),
        .in6(in6),
        .in7(in7),
        .in8(in8),
        .in9(in9),
        .out0(out0),
        .out1(out1),
        .out10(out10),
        .out11(out11),
        .out12(out12),
        .out13(out13),
        .out14(out14),
        .out15(out15),
        .out16(out16),
        .out17(out17),
        .out18(out18),
        .out19(out19),
        .out2(out2),
        .out20(out20),
        .out21(out21),
        .out22(out22),
        .out23(out23),
        .out24(out24),
        .out25(out25),
        .out26(out26),
        .out27(out27),
        .out28(out28),
        .out29(out29),
        .out3(out3),
        .out30(out30),
        .out31(out31),
        .out4(out4),
        .out5(out5),
        .out6(out6),
        .out7(out7),
        .out8(out8),
        .out9(out9));
endmodule

(* ORIG_REF_NAME = "uz_pu_con_ip" *) 
module zusys_uz_pu_con_ip_0_1_uz_pu_con_ip
   (AXI4_Lite_RVALID,
    AXI4_Lite_BVALID,
    AXI4_Lite_WREADY,
    out0,
    out1,
    out2,
    out3,
    out4,
    out5,
    out6,
    out7,
    out8,
    out9,
    out10,
    out11,
    out12,
    out13,
    out14,
    out15,
    out16,
    out17,
    out18,
    out19,
    out20,
    out21,
    out22,
    out23,
    out24,
    out25,
    out26,
    out27,
    out28,
    out29,
    out30,
    out31,
    AXI4_Lite_AWREADY,
    AXI4_Lite_ARREADY,
    AXI4_Lite_RDATA,
    AXI4_Lite_ARADDR,
    AXI4_Lite_ARVALID,
    AXI4_Lite_ACLK,
    adc_trigger,
    in0,
    IPCORE_CLK,
    in1,
    in2,
    in3,
    in4,
    in5,
    in6,
    in7,
    in8,
    in9,
    in10,
    in11,
    in12,
    in13,
    in14,
    in15,
    in16,
    in17,
    in18,
    in19,
    in20,
    in21,
    in22,
    in23,
    in24,
    in25,
    in26,
    in27,
    in28,
    in29,
    in30,
    in31,
    AXI4_Lite_AWADDR,
    AXI4_Lite_WDATA,
    AXI4_Lite_AWVALID,
    AXI4_Lite_WVALID,
    AXI4_Lite_RREADY,
    AXI4_Lite_ARESETN,
    IPCORE_RESETN,
    AXI4_Lite_BREADY,
    AXI4_Lite_WSTRB);
  output AXI4_Lite_RVALID;
  output AXI4_Lite_BVALID;
  output AXI4_Lite_WREADY;
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
  output AXI4_Lite_AWREADY;
  output AXI4_Lite_ARREADY;
  output [0:0]AXI4_Lite_RDATA;
  input [13:0]AXI4_Lite_ARADDR;
  input AXI4_Lite_ARVALID;
  input AXI4_Lite_ACLK;
  input adc_trigger;
  input [26:0]in0;
  input IPCORE_CLK;
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
  input [13:0]AXI4_Lite_AWADDR;
  input [17:0]AXI4_Lite_WDATA;
  input AXI4_Lite_AWVALID;
  input AXI4_Lite_WVALID;
  input AXI4_Lite_RREADY;
  input AXI4_Lite_ARESETN;
  input IPCORE_RESETN;
  input AXI4_Lite_BREADY;
  input [3:0]AXI4_Lite_WSTRB;

  wire AXI4_Lite_ACLK;
  wire [13:0]AXI4_Lite_ARADDR;
  wire AXI4_Lite_ARESETN;
  wire AXI4_Lite_ARREADY;
  wire AXI4_Lite_ARVALID;
  wire [13:0]AXI4_Lite_AWADDR;
  wire AXI4_Lite_AWREADY;
  wire AXI4_Lite_AWVALID;
  wire AXI4_Lite_BREADY;
  wire AXI4_Lite_BVALID;
  wire [0:0]AXI4_Lite_RDATA;
  wire AXI4_Lite_RREADY;
  wire AXI4_Lite_RVALID;
  wire [17:0]AXI4_Lite_WDATA;
  wire AXI4_Lite_WREADY;
  wire [3:0]AXI4_Lite_WSTRB;
  wire AXI4_Lite_WVALID;
  wire IPCORE_CLK;
  wire IPCORE_RESETN;
  wire adc_trigger;
  wire [26:0]in0;
  wire [26:0]in1;
  wire [26:0]in10;
  wire [26:0]in11;
  wire [26:0]in12;
  wire [26:0]in13;
  wire [26:0]in14;
  wire [26:0]in15;
  wire [26:0]in16;
  wire [26:0]in17;
  wire [26:0]in18;
  wire [26:0]in19;
  wire [26:0]in2;
  wire [26:0]in20;
  wire [26:0]in21;
  wire [26:0]in22;
  wire [26:0]in23;
  wire [26:0]in24;
  wire [26:0]in25;
  wire [26:0]in26;
  wire [26:0]in27;
  wire [26:0]in28;
  wire [26:0]in29;
  wire [26:0]in3;
  wire [26:0]in30;
  wire [26:0]in31;
  wire [26:0]in4;
  wire [26:0]in5;
  wire [26:0]in6;
  wire [26:0]in7;
  wire [26:0]in8;
  wire [26:0]in9;
  wire [17:0]out0;
  wire [17:0]out1;
  wire [17:0]out10;
  wire [17:0]out11;
  wire [17:0]out12;
  wire [17:0]out13;
  wire [17:0]out14;
  wire [17:0]out15;
  wire [17:0]out16;
  wire [17:0]out17;
  wire [17:0]out18;
  wire [17:0]out19;
  wire [17:0]out2;
  wire [17:0]out20;
  wire [17:0]out21;
  wire [17:0]out22;
  wire [17:0]out23;
  wire [17:0]out24;
  wire [17:0]out25;
  wire [17:0]out26;
  wire [17:0]out27;
  wire [17:0]out28;
  wire [17:0]out29;
  wire [17:0]out3;
  wire [17:0]out30;
  wire [17:0]out31;
  wire [17:0]out4;
  wire [17:0]out5;
  wire [17:0]out6;
  wire [17:0]out7;
  wire [17:0]out8;
  wire [17:0]out9;
  wire reset;
  wire reset_in;
  wire \u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in0_1_1 ;
  wire \u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in10_1_1 ;
  wire \u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in11_1_1 ;
  wire \u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in12_1_1 ;
  wire \u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in13_1_1 ;
  wire \u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in14_1_1 ;
  wire \u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in15_1_1 ;
  wire \u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in16_1_1 ;
  wire \u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in17_1_1 ;
  wire \u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in18_1_1 ;
  wire \u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in19_1_1 ;
  wire \u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in1_1_1 ;
  wire \u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in20_1_1 ;
  wire \u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in21_1_1 ;
  wire \u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in22_1_1 ;
  wire \u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in23_1_1 ;
  wire \u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in24_1_1 ;
  wire \u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in25_1_1 ;
  wire \u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in26_1_1 ;
  wire \u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in27_1_1 ;
  wire \u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in28_1_1 ;
  wire \u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in29_1_1 ;
  wire \u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in2_1_1 ;
  wire \u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in30_1_1 ;
  wire \u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in31_1_1 ;
  wire \u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in3_1_1 ;
  wire \u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in4_1_1 ;
  wire \u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in5_1_1 ;
  wire \u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in6_1_1 ;
  wire \u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in7_1_1 ;
  wire \u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in8_1_1 ;
  wire \u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in9_1_1 ;
  wire u_uz_pu_con_ip_axi_lite_inst_n_72;
  wire u_uz_pu_con_ip_axi_lite_inst_n_73;
  wire u_uz_pu_con_ip_axi_lite_inst_n_74;
  wire u_uz_pu_con_ip_axi_lite_inst_n_75;
  wire u_uz_pu_con_ip_axi_lite_inst_n_76;
  wire u_uz_pu_con_ip_axi_lite_inst_n_77;
  wire u_uz_pu_con_ip_axi_lite_inst_n_78;
  wire u_uz_pu_con_ip_axi_lite_inst_n_79;
  wire u_uz_pu_con_ip_axi_lite_inst_n_80;
  wire u_uz_pu_con_ip_axi_lite_inst_n_81;
  wire u_uz_pu_con_ip_axi_lite_inst_n_82;
  wire u_uz_pu_con_ip_axi_lite_inst_n_83;
  wire u_uz_pu_con_ip_axi_lite_inst_n_84;
  wire u_uz_pu_con_ip_axi_lite_inst_n_85;
  wire u_uz_pu_con_ip_axi_lite_inst_n_86;
  wire u_uz_pu_con_ip_axi_lite_inst_n_87;
  wire u_uz_pu_con_ip_axi_lite_inst_n_88;
  wire \u_uz_pu_con_ip_axi_lite_module_inst/soft_reset ;
  wire u_uz_pu_con_ip_reset_sync_inst_n_1;
  wire [0:0]write_AXI_pu_conv_in0;
  wire [0:0]write_AXI_pu_conv_in1;
  wire [0:0]write_AXI_pu_conv_in10;
  wire [0:0]write_AXI_pu_conv_in11;
  wire [0:0]write_AXI_pu_conv_in12;
  wire [0:0]write_AXI_pu_conv_in13;
  wire [0:0]write_AXI_pu_conv_in14;
  wire [0:0]write_AXI_pu_conv_in15;
  wire [0:0]write_AXI_pu_conv_in16;
  wire [0:0]write_AXI_pu_conv_in17;
  wire [0:0]write_AXI_pu_conv_in18;
  wire [0:0]write_AXI_pu_conv_in19;
  wire [0:0]write_AXI_pu_conv_in2;
  wire [0:0]write_AXI_pu_conv_in20;
  wire [0:0]write_AXI_pu_conv_in21;
  wire [0:0]write_AXI_pu_conv_in22;
  wire [0:0]write_AXI_pu_conv_in23;
  wire [0:0]write_AXI_pu_conv_in24;
  wire [0:0]write_AXI_pu_conv_in25;
  wire [0:0]write_AXI_pu_conv_in26;
  wire [0:0]write_AXI_pu_conv_in27;
  wire [0:0]write_AXI_pu_conv_in28;
  wire [0:0]write_AXI_pu_conv_in29;
  wire [0:0]write_AXI_pu_conv_in3;
  wire [0:0]write_AXI_pu_conv_in30;
  wire [0:0]write_AXI_pu_conv_in31;
  wire [0:0]write_AXI_pu_conv_in4;
  wire [0:0]write_AXI_pu_conv_in5;
  wire [0:0]write_AXI_pu_conv_in6;
  wire [0:0]write_AXI_pu_conv_in7;
  wire [0:0]write_AXI_pu_conv_in8;
  wire [0:0]write_AXI_pu_conv_in9;

  zusys_uz_pu_con_ip_0_1_uz_pu_con_ip_axi_lite u_uz_pu_con_ip_axi_lite_inst
       (.AXI4_Lite_ACLK(AXI4_Lite_ACLK),
        .AXI4_Lite_ARADDR(AXI4_Lite_ARADDR),
        .\AXI4_Lite_ARADDR[3]_0 (\u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in12_1_1 ),
        .\AXI4_Lite_ARADDR[4]_0 (\u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in14_1_1 ),
        .\AXI4_Lite_ARADDR[4]_1 (\u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in11_1_1 ),
        .\AXI4_Lite_ARADDR[4]_2 (\u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in10_1_1 ),
        .\AXI4_Lite_ARADDR[7]_0 (\u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in30_1_1 ),
        .\AXI4_Lite_ARADDR[7]_1 (\u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in29_1_1 ),
        .\AXI4_Lite_ARADDR[7]_2 (\u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in28_1_1 ),
        .\AXI4_Lite_ARADDR[7]_3 (\u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in27_1_1 ),
        .\AXI4_Lite_ARADDR[7]_4 (\u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in26_1_1 ),
        .\AXI4_Lite_ARADDR[7]_5 (\u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in25_1_1 ),
        .\AXI4_Lite_ARADDR[8]_0 (\u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in23_1_1 ),
        .\AXI4_Lite_ARADDR[8]_1 (\u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in7_1_1 ),
        .\AXI4_Lite_ARADDR[8]_10 (\u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in18_1_1 ),
        .\AXI4_Lite_ARADDR[8]_11 (\u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in2_1_1 ),
        .\AXI4_Lite_ARADDR[8]_12 (\u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in17_1_1 ),
        .\AXI4_Lite_ARADDR[8]_13 (\u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in1_1_1 ),
        .\AXI4_Lite_ARADDR[8]_2 (\u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in22_1_1 ),
        .\AXI4_Lite_ARADDR[8]_3 (\u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in6_1_1 ),
        .\AXI4_Lite_ARADDR[8]_4 (\u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in21_1_1 ),
        .\AXI4_Lite_ARADDR[8]_5 (\u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in5_1_1 ),
        .\AXI4_Lite_ARADDR[8]_6 (\u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in20_1_1 ),
        .\AXI4_Lite_ARADDR[8]_7 (\u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in4_1_1 ),
        .\AXI4_Lite_ARADDR[8]_8 (\u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in19_1_1 ),
        .\AXI4_Lite_ARADDR[8]_9 (\u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in3_1_1 ),
        .AXI4_Lite_ARADDR_11_sp_1(\u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in8_1_1 ),
        .AXI4_Lite_ARADDR_3_sp_1(\u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in13_1_1 ),
        .AXI4_Lite_ARADDR_4_sp_1(\u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in15_1_1 ),
        .AXI4_Lite_ARADDR_6_sp_1(\u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in9_1_1 ),
        .AXI4_Lite_ARADDR_7_sp_1(\u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in31_1_1 ),
        .AXI4_Lite_ARADDR_8_sp_1(\u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in16_1_1 ),
        .AXI4_Lite_ARESETN(AXI4_Lite_ARESETN),
        .AXI4_Lite_ARREADY(AXI4_Lite_ARREADY),
        .AXI4_Lite_ARVALID(AXI4_Lite_ARVALID),
        .AXI4_Lite_AWADDR(AXI4_Lite_AWADDR),
        .AXI4_Lite_AWREADY(AXI4_Lite_AWREADY),
        .AXI4_Lite_AWVALID(AXI4_Lite_AWVALID),
        .AXI4_Lite_BREADY(AXI4_Lite_BREADY),
        .AXI4_Lite_RDATA(AXI4_Lite_RDATA),
        .AXI4_Lite_RREADY(AXI4_Lite_RREADY),
        .AXI4_Lite_WDATA(AXI4_Lite_WDATA),
        .AXI4_Lite_WSTRB(AXI4_Lite_WSTRB),
        .AXI4_Lite_WVALID(AXI4_Lite_WVALID),
        .CEB2(\u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in24_1_1 ),
        .FSM_sequential_axi_lite_rstate_reg(AXI4_Lite_RVALID),
        .IPCORE_RESETN(IPCORE_RESETN),
        .OPMODE(write_AXI_pu_conv_in0),
        .Q({AXI4_Lite_BVALID,AXI4_Lite_WREADY}),
        .\data_reg_AXI_pu_conv_in10_1_1_reg[0] (write_AXI_pu_conv_in10),
        .\data_reg_AXI_pu_conv_in11_1_1_reg[0] (write_AXI_pu_conv_in11),
        .\data_reg_AXI_pu_conv_in12_1_1_reg[0] (write_AXI_pu_conv_in12),
        .\data_reg_AXI_pu_conv_in13_1_1_reg[0] (write_AXI_pu_conv_in13),
        .\data_reg_AXI_pu_conv_in14_1_1_reg[0] (write_AXI_pu_conv_in14),
        .\data_reg_AXI_pu_conv_in15_1_1_reg[0] (write_AXI_pu_conv_in15),
        .\data_reg_AXI_pu_conv_in16_1_1_reg[0] (write_AXI_pu_conv_in16),
        .\data_reg_AXI_pu_conv_in17_1_1_reg[0] (write_AXI_pu_conv_in17),
        .\data_reg_AXI_pu_conv_in18_1_1_reg[0] (write_AXI_pu_conv_in18),
        .\data_reg_AXI_pu_conv_in19_1_1_reg[0] (write_AXI_pu_conv_in19),
        .\data_reg_AXI_pu_conv_in1_1_1_reg[0] (write_AXI_pu_conv_in1),
        .\data_reg_AXI_pu_conv_in20_1_1_reg[0] (write_AXI_pu_conv_in20),
        .\data_reg_AXI_pu_conv_in21_1_1_reg[0] (write_AXI_pu_conv_in21),
        .\data_reg_AXI_pu_conv_in22_1_1_reg[0] (write_AXI_pu_conv_in22),
        .\data_reg_AXI_pu_conv_in23_1_1_reg[0] (write_AXI_pu_conv_in23),
        .\data_reg_AXI_pu_conv_in24_1_1_reg[0] (write_AXI_pu_conv_in24),
        .\data_reg_AXI_pu_conv_in25_1_1_reg[0] (write_AXI_pu_conv_in25),
        .\data_reg_AXI_pu_conv_in26_1_1_reg[0] (write_AXI_pu_conv_in26),
        .\data_reg_AXI_pu_conv_in27_1_1_reg[0] (write_AXI_pu_conv_in27),
        .\data_reg_AXI_pu_conv_in28_1_1_reg[0] (write_AXI_pu_conv_in28),
        .\data_reg_AXI_pu_conv_in29_1_1_reg[0] (write_AXI_pu_conv_in29),
        .\data_reg_AXI_pu_conv_in2_1_1_reg[0] (write_AXI_pu_conv_in2),
        .\data_reg_AXI_pu_conv_in30_1_1_reg[0] (write_AXI_pu_conv_in30),
        .\data_reg_AXI_pu_conv_in31_1_1_reg[0] (write_AXI_pu_conv_in31),
        .\data_reg_AXI_pu_conv_in3_1_1_reg[0] (write_AXI_pu_conv_in3),
        .\data_reg_AXI_pu_conv_in4_1_1_reg[0] (write_AXI_pu_conv_in4),
        .\data_reg_AXI_pu_conv_in5_1_1_reg[0] (write_AXI_pu_conv_in5),
        .\data_reg_AXI_pu_conv_in6_1_1_reg[0] (write_AXI_pu_conv_in6),
        .\data_reg_AXI_pu_conv_in7_1_1_reg[0] (write_AXI_pu_conv_in7),
        .\data_reg_AXI_pu_conv_in8_1_1_reg[0] (write_AXI_pu_conv_in8),
        .\data_reg_AXI_pu_conv_in9_1_1_reg[0] (write_AXI_pu_conv_in9),
        .\read_reg_ip_timestamp_reg[31] (u_uz_pu_con_ip_reset_sync_inst_n_1),
        .reset(reset),
        .reset_in(reset_in),
        .soft_reset(\u_uz_pu_con_ip_axi_lite_module_inst/soft_reset ),
        .\wdata_reg[17] ({u_uz_pu_con_ip_axi_lite_inst_n_72,u_uz_pu_con_ip_axi_lite_inst_n_73,u_uz_pu_con_ip_axi_lite_inst_n_74,u_uz_pu_con_ip_axi_lite_inst_n_75,u_uz_pu_con_ip_axi_lite_inst_n_76,u_uz_pu_con_ip_axi_lite_inst_n_77,u_uz_pu_con_ip_axi_lite_inst_n_78,u_uz_pu_con_ip_axi_lite_inst_n_79,u_uz_pu_con_ip_axi_lite_inst_n_80,u_uz_pu_con_ip_axi_lite_inst_n_81,u_uz_pu_con_ip_axi_lite_inst_n_82,u_uz_pu_con_ip_axi_lite_inst_n_83,u_uz_pu_con_ip_axi_lite_inst_n_84,u_uz_pu_con_ip_axi_lite_inst_n_85,u_uz_pu_con_ip_axi_lite_inst_n_86,u_uz_pu_con_ip_axi_lite_inst_n_87,u_uz_pu_con_ip_axi_lite_inst_n_88}),
        .wr_enb_1_reg(\u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in0_1_1 ));
  zusys_uz_pu_con_ip_0_1_uz_pu_con_ip_dut u_uz_pu_con_ip_dut_inst
       (.AXI4_Lite_ACLK(AXI4_Lite_ACLK),
        .AXI_pu_conv_in31({u_uz_pu_con_ip_axi_lite_inst_n_72,u_uz_pu_con_ip_axi_lite_inst_n_73,u_uz_pu_con_ip_axi_lite_inst_n_74,u_uz_pu_con_ip_axi_lite_inst_n_75,u_uz_pu_con_ip_axi_lite_inst_n_76,u_uz_pu_con_ip_axi_lite_inst_n_77,u_uz_pu_con_ip_axi_lite_inst_n_78,u_uz_pu_con_ip_axi_lite_inst_n_79,u_uz_pu_con_ip_axi_lite_inst_n_80,u_uz_pu_con_ip_axi_lite_inst_n_81,u_uz_pu_con_ip_axi_lite_inst_n_82,u_uz_pu_con_ip_axi_lite_inst_n_83,u_uz_pu_con_ip_axi_lite_inst_n_84,u_uz_pu_con_ip_axi_lite_inst_n_85,u_uz_pu_con_ip_axi_lite_inst_n_86,u_uz_pu_con_ip_axi_lite_inst_n_87,u_uz_pu_con_ip_axi_lite_inst_n_88}),
        .CEB2(\u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in24_1_1 ),
        .DSP_ALU_INST(\u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in0_1_1 ),
        .DSP_ALU_INST_0(\u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in1_1_1 ),
        .DSP_ALU_INST_1(\u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in2_1_1 ),
        .DSP_ALU_INST_10(\u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in11_1_1 ),
        .DSP_ALU_INST_11(\u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in12_1_1 ),
        .DSP_ALU_INST_12(\u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in13_1_1 ),
        .DSP_ALU_INST_13(\u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in14_1_1 ),
        .DSP_ALU_INST_14(\u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in15_1_1 ),
        .DSP_ALU_INST_15(\u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in16_1_1 ),
        .DSP_ALU_INST_16(\u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in17_1_1 ),
        .DSP_ALU_INST_17(\u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in18_1_1 ),
        .DSP_ALU_INST_18(\u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in19_1_1 ),
        .DSP_ALU_INST_19(\u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in20_1_1 ),
        .DSP_ALU_INST_2(\u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in3_1_1 ),
        .DSP_ALU_INST_20(\u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in21_1_1 ),
        .DSP_ALU_INST_21(\u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in22_1_1 ),
        .DSP_ALU_INST_22(\u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in23_1_1 ),
        .DSP_ALU_INST_23(\u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in25_1_1 ),
        .DSP_ALU_INST_24(\u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in26_1_1 ),
        .DSP_ALU_INST_25(\u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in27_1_1 ),
        .DSP_ALU_INST_26(\u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in28_1_1 ),
        .DSP_ALU_INST_27(\u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in29_1_1 ),
        .DSP_ALU_INST_28(\u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in30_1_1 ),
        .DSP_ALU_INST_29(\u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in31_1_1 ),
        .DSP_ALU_INST_3(\u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in4_1_1 ),
        .DSP_ALU_INST_4(\u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in5_1_1 ),
        .DSP_ALU_INST_5(\u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in6_1_1 ),
        .DSP_ALU_INST_6(\u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in7_1_1 ),
        .DSP_ALU_INST_7(\u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in8_1_1 ),
        .DSP_ALU_INST_8(\u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in9_1_1 ),
        .DSP_ALU_INST_9(\u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in10_1_1 ),
        .IPCORE_CLK(IPCORE_CLK),
        .OPMODE(write_AXI_pu_conv_in0),
        .adc_trigger(adc_trigger),
        .in0(in0),
        .in1(in1),
        .in10(in10),
        .in11(in11),
        .in12(in12),
        .in13(in13),
        .in14(in14),
        .in15(in15),
        .in16(in16),
        .in17(in17),
        .in18(in18),
        .in19(in19),
        .in2(in2),
        .in20(in20),
        .in21(in21),
        .in22(in22),
        .in23(in23),
        .in24(in24),
        .in25(in25),
        .in26(in26),
        .in27(in27),
        .in28(in28),
        .in29(in29),
        .in3(in3),
        .in30(in30),
        .in31(in31),
        .in4(in4),
        .in5(in5),
        .in6(in6),
        .in7(in7),
        .in8(in8),
        .in9(in9),
        .out0(out0),
        .out1(out1),
        .out10(out10),
        .\out10[17] (write_AXI_pu_conv_in10),
        .out11(out11),
        .\out11[17] (write_AXI_pu_conv_in11),
        .out12(out12),
        .\out12[17] (write_AXI_pu_conv_in12),
        .out13(out13),
        .\out13[17] (write_AXI_pu_conv_in13),
        .out14(out14),
        .\out14[17] (write_AXI_pu_conv_in14),
        .out15(out15),
        .\out15[17] (write_AXI_pu_conv_in15),
        .out16(out16),
        .\out16[17] (write_AXI_pu_conv_in16),
        .out17(out17),
        .\out17[17] (write_AXI_pu_conv_in17),
        .out18(out18),
        .\out18[17] (write_AXI_pu_conv_in18),
        .out19(out19),
        .\out19[17] (write_AXI_pu_conv_in19),
        .\out1[17] (write_AXI_pu_conv_in1),
        .out2(out2),
        .out20(out20),
        .\out20[17] (write_AXI_pu_conv_in20),
        .out21(out21),
        .\out21[17] (write_AXI_pu_conv_in21),
        .out22(out22),
        .\out22[17] (write_AXI_pu_conv_in22),
        .out23(out23),
        .\out23[17] (write_AXI_pu_conv_in23),
        .out24(out24),
        .\out24[17] (write_AXI_pu_conv_in24),
        .out25(out25),
        .\out25[17] (write_AXI_pu_conv_in25),
        .out26(out26),
        .\out26[17] (write_AXI_pu_conv_in26),
        .out27(out27),
        .\out27[17] (write_AXI_pu_conv_in27),
        .out28(out28),
        .\out28[17] (write_AXI_pu_conv_in28),
        .out29(out29),
        .\out29[17] (write_AXI_pu_conv_in29),
        .\out2[17] (write_AXI_pu_conv_in2),
        .out3(out3),
        .out30(out30),
        .\out30[17] (write_AXI_pu_conv_in30),
        .out31(out31),
        .\out31[17] (write_AXI_pu_conv_in31),
        .\out3[17] (write_AXI_pu_conv_in3),
        .out4(out4),
        .\out4[17] (write_AXI_pu_conv_in4),
        .out5(out5),
        .\out5[17] (write_AXI_pu_conv_in5),
        .out6(out6),
        .\out6[17] (write_AXI_pu_conv_in6),
        .out7(out7),
        .\out7[17] (write_AXI_pu_conv_in7),
        .out8(out8),
        .\out8[17] (write_AXI_pu_conv_in8),
        .out9(out9),
        .\out9[17] (write_AXI_pu_conv_in9),
        .reset(reset));
  zusys_uz_pu_con_ip_0_1_uz_pu_con_ip_reset_sync u_uz_pu_con_ip_reset_sync_inst
       (.AXI4_Lite_ARESETN(AXI4_Lite_ARESETN),
        .IPCORE_CLK(IPCORE_CLK),
        .IPCORE_RESETN(IPCORE_RESETN),
        .reset(reset),
        .reset_in(reset_in),
        .reset_out_reg_0(u_uz_pu_con_ip_reset_sync_inst_n_1),
        .soft_reset(\u_uz_pu_con_ip_axi_lite_module_inst/soft_reset ));
endmodule

(* ORIG_REF_NAME = "uz_pu_con_ip_addr_decoder" *) 
module zusys_uz_pu_con_ip_0_1_uz_pu_con_ip_addr_decoder
   (OPMODE,
    \data_reg_AXI_pu_conv_in1_1_1_reg[0]_0 ,
    \data_reg_AXI_pu_conv_in2_1_1_reg[0]_0 ,
    \data_reg_AXI_pu_conv_in3_1_1_reg[0]_0 ,
    \data_reg_AXI_pu_conv_in4_1_1_reg[0]_0 ,
    \data_reg_AXI_pu_conv_in5_1_1_reg[0]_0 ,
    \data_reg_AXI_pu_conv_in6_1_1_reg[0]_0 ,
    \data_reg_AXI_pu_conv_in7_1_1_reg[0]_0 ,
    \data_reg_AXI_pu_conv_in8_1_1_reg[0]_0 ,
    \data_reg_AXI_pu_conv_in9_1_1_reg[0]_0 ,
    \data_reg_AXI_pu_conv_in10_1_1_reg[0]_0 ,
    \data_reg_AXI_pu_conv_in11_1_1_reg[0]_0 ,
    \data_reg_AXI_pu_conv_in12_1_1_reg[0]_0 ,
    \data_reg_AXI_pu_conv_in13_1_1_reg[0]_0 ,
    \data_reg_AXI_pu_conv_in14_1_1_reg[0]_0 ,
    \data_reg_AXI_pu_conv_in15_1_1_reg[0]_0 ,
    \data_reg_AXI_pu_conv_in16_1_1_reg[0]_0 ,
    \data_reg_AXI_pu_conv_in17_1_1_reg[0]_0 ,
    \data_reg_AXI_pu_conv_in18_1_1_reg[0]_0 ,
    \data_reg_AXI_pu_conv_in19_1_1_reg[0]_0 ,
    \data_reg_AXI_pu_conv_in20_1_1_reg[0]_0 ,
    \data_reg_AXI_pu_conv_in21_1_1_reg[0]_0 ,
    \data_reg_AXI_pu_conv_in22_1_1_reg[0]_0 ,
    \data_reg_AXI_pu_conv_in23_1_1_reg[0]_0 ,
    \data_reg_AXI_pu_conv_in24_1_1_reg[0]_0 ,
    \data_reg_AXI_pu_conv_in25_1_1_reg[0]_0 ,
    \data_reg_AXI_pu_conv_in26_1_1_reg[0]_0 ,
    \data_reg_AXI_pu_conv_in27_1_1_reg[0]_0 ,
    \data_reg_AXI_pu_conv_in28_1_1_reg[0]_0 ,
    \data_reg_AXI_pu_conv_in29_1_1_reg[0]_0 ,
    \data_reg_AXI_pu_conv_in30_1_1_reg[0]_0 ,
    \data_reg_AXI_pu_conv_in31_1_1_reg[0]_0 ,
    read_reg_ip_timestamp,
    reset,
    \data_reg_AXI_pu_conv_in0_1_1_reg[0]_0 ,
    AXI4_Lite_ACLK,
    \data_reg_AXI_pu_conv_in1_1_1_reg[0]_1 ,
    \data_reg_AXI_pu_conv_in2_1_1_reg[0]_1 ,
    \data_reg_AXI_pu_conv_in3_1_1_reg[0]_1 ,
    \data_reg_AXI_pu_conv_in4_1_1_reg[0]_1 ,
    \data_reg_AXI_pu_conv_in5_1_1_reg[0]_1 ,
    \data_reg_AXI_pu_conv_in6_1_1_reg[0]_1 ,
    \data_reg_AXI_pu_conv_in7_1_1_reg[0]_1 ,
    \data_reg_AXI_pu_conv_in8_1_1_reg[0]_1 ,
    \data_reg_AXI_pu_conv_in9_1_1_reg[0]_1 ,
    \data_reg_AXI_pu_conv_in10_1_1_reg[0]_1 ,
    \data_reg_AXI_pu_conv_in11_1_1_reg[0]_1 ,
    \data_reg_AXI_pu_conv_in12_1_1_reg[0]_1 ,
    \data_reg_AXI_pu_conv_in13_1_1_reg[0]_1 ,
    \data_reg_AXI_pu_conv_in14_1_1_reg[0]_1 ,
    \data_reg_AXI_pu_conv_in15_1_1_reg[0]_1 ,
    \data_reg_AXI_pu_conv_in16_1_1_reg[0]_1 ,
    \data_reg_AXI_pu_conv_in17_1_1_reg[0]_1 ,
    \data_reg_AXI_pu_conv_in18_1_1_reg[0]_1 ,
    \data_reg_AXI_pu_conv_in19_1_1_reg[0]_1 ,
    \data_reg_AXI_pu_conv_in20_1_1_reg[0]_1 ,
    \data_reg_AXI_pu_conv_in21_1_1_reg[0]_1 ,
    \data_reg_AXI_pu_conv_in22_1_1_reg[0]_1 ,
    \data_reg_AXI_pu_conv_in23_1_1_reg[0]_1 ,
    \data_reg_AXI_pu_conv_in24_1_1_reg[0]_1 ,
    \data_reg_AXI_pu_conv_in25_1_1_reg[0]_1 ,
    \data_reg_AXI_pu_conv_in26_1_1_reg[0]_1 ,
    \data_reg_AXI_pu_conv_in27_1_1_reg[0]_1 ,
    \data_reg_AXI_pu_conv_in28_1_1_reg[0]_1 ,
    \data_reg_AXI_pu_conv_in29_1_1_reg[0]_1 ,
    \data_reg_AXI_pu_conv_in30_1_1_reg[0]_1 ,
    \data_reg_AXI_pu_conv_in31_1_1_reg[0]_1 ,
    \read_reg_ip_timestamp_reg[31]_0 );
  output [0:0]OPMODE;
  output [0:0]\data_reg_AXI_pu_conv_in1_1_1_reg[0]_0 ;
  output [0:0]\data_reg_AXI_pu_conv_in2_1_1_reg[0]_0 ;
  output [0:0]\data_reg_AXI_pu_conv_in3_1_1_reg[0]_0 ;
  output [0:0]\data_reg_AXI_pu_conv_in4_1_1_reg[0]_0 ;
  output [0:0]\data_reg_AXI_pu_conv_in5_1_1_reg[0]_0 ;
  output [0:0]\data_reg_AXI_pu_conv_in6_1_1_reg[0]_0 ;
  output [0:0]\data_reg_AXI_pu_conv_in7_1_1_reg[0]_0 ;
  output [0:0]\data_reg_AXI_pu_conv_in8_1_1_reg[0]_0 ;
  output [0:0]\data_reg_AXI_pu_conv_in9_1_1_reg[0]_0 ;
  output [0:0]\data_reg_AXI_pu_conv_in10_1_1_reg[0]_0 ;
  output [0:0]\data_reg_AXI_pu_conv_in11_1_1_reg[0]_0 ;
  output [0:0]\data_reg_AXI_pu_conv_in12_1_1_reg[0]_0 ;
  output [0:0]\data_reg_AXI_pu_conv_in13_1_1_reg[0]_0 ;
  output [0:0]\data_reg_AXI_pu_conv_in14_1_1_reg[0]_0 ;
  output [0:0]\data_reg_AXI_pu_conv_in15_1_1_reg[0]_0 ;
  output [0:0]\data_reg_AXI_pu_conv_in16_1_1_reg[0]_0 ;
  output [0:0]\data_reg_AXI_pu_conv_in17_1_1_reg[0]_0 ;
  output [0:0]\data_reg_AXI_pu_conv_in18_1_1_reg[0]_0 ;
  output [0:0]\data_reg_AXI_pu_conv_in19_1_1_reg[0]_0 ;
  output [0:0]\data_reg_AXI_pu_conv_in20_1_1_reg[0]_0 ;
  output [0:0]\data_reg_AXI_pu_conv_in21_1_1_reg[0]_0 ;
  output [0:0]\data_reg_AXI_pu_conv_in22_1_1_reg[0]_0 ;
  output [0:0]\data_reg_AXI_pu_conv_in23_1_1_reg[0]_0 ;
  output [0:0]\data_reg_AXI_pu_conv_in24_1_1_reg[0]_0 ;
  output [0:0]\data_reg_AXI_pu_conv_in25_1_1_reg[0]_0 ;
  output [0:0]\data_reg_AXI_pu_conv_in26_1_1_reg[0]_0 ;
  output [0:0]\data_reg_AXI_pu_conv_in27_1_1_reg[0]_0 ;
  output [0:0]\data_reg_AXI_pu_conv_in28_1_1_reg[0]_0 ;
  output [0:0]\data_reg_AXI_pu_conv_in29_1_1_reg[0]_0 ;
  output [0:0]\data_reg_AXI_pu_conv_in30_1_1_reg[0]_0 ;
  output [0:0]\data_reg_AXI_pu_conv_in31_1_1_reg[0]_0 ;
  output [0:0]read_reg_ip_timestamp;
  input reset;
  input \data_reg_AXI_pu_conv_in0_1_1_reg[0]_0 ;
  input AXI4_Lite_ACLK;
  input \data_reg_AXI_pu_conv_in1_1_1_reg[0]_1 ;
  input \data_reg_AXI_pu_conv_in2_1_1_reg[0]_1 ;
  input \data_reg_AXI_pu_conv_in3_1_1_reg[0]_1 ;
  input \data_reg_AXI_pu_conv_in4_1_1_reg[0]_1 ;
  input \data_reg_AXI_pu_conv_in5_1_1_reg[0]_1 ;
  input \data_reg_AXI_pu_conv_in6_1_1_reg[0]_1 ;
  input \data_reg_AXI_pu_conv_in7_1_1_reg[0]_1 ;
  input \data_reg_AXI_pu_conv_in8_1_1_reg[0]_1 ;
  input \data_reg_AXI_pu_conv_in9_1_1_reg[0]_1 ;
  input \data_reg_AXI_pu_conv_in10_1_1_reg[0]_1 ;
  input \data_reg_AXI_pu_conv_in11_1_1_reg[0]_1 ;
  input \data_reg_AXI_pu_conv_in12_1_1_reg[0]_1 ;
  input \data_reg_AXI_pu_conv_in13_1_1_reg[0]_1 ;
  input \data_reg_AXI_pu_conv_in14_1_1_reg[0]_1 ;
  input \data_reg_AXI_pu_conv_in15_1_1_reg[0]_1 ;
  input \data_reg_AXI_pu_conv_in16_1_1_reg[0]_1 ;
  input \data_reg_AXI_pu_conv_in17_1_1_reg[0]_1 ;
  input \data_reg_AXI_pu_conv_in18_1_1_reg[0]_1 ;
  input \data_reg_AXI_pu_conv_in19_1_1_reg[0]_1 ;
  input \data_reg_AXI_pu_conv_in20_1_1_reg[0]_1 ;
  input \data_reg_AXI_pu_conv_in21_1_1_reg[0]_1 ;
  input \data_reg_AXI_pu_conv_in22_1_1_reg[0]_1 ;
  input \data_reg_AXI_pu_conv_in23_1_1_reg[0]_1 ;
  input \data_reg_AXI_pu_conv_in24_1_1_reg[0]_1 ;
  input \data_reg_AXI_pu_conv_in25_1_1_reg[0]_1 ;
  input \data_reg_AXI_pu_conv_in26_1_1_reg[0]_1 ;
  input \data_reg_AXI_pu_conv_in27_1_1_reg[0]_1 ;
  input \data_reg_AXI_pu_conv_in28_1_1_reg[0]_1 ;
  input \data_reg_AXI_pu_conv_in29_1_1_reg[0]_1 ;
  input \data_reg_AXI_pu_conv_in30_1_1_reg[0]_1 ;
  input \data_reg_AXI_pu_conv_in31_1_1_reg[0]_1 ;
  input \read_reg_ip_timestamp_reg[31]_0 ;

  wire AXI4_Lite_ACLK;
  wire [0:0]OPMODE;
  wire \data_reg_AXI_pu_conv_in0_1_1_reg[0]_0 ;
  wire [0:0]\data_reg_AXI_pu_conv_in10_1_1_reg[0]_0 ;
  wire \data_reg_AXI_pu_conv_in10_1_1_reg[0]_1 ;
  wire [0:0]\data_reg_AXI_pu_conv_in11_1_1_reg[0]_0 ;
  wire \data_reg_AXI_pu_conv_in11_1_1_reg[0]_1 ;
  wire [0:0]\data_reg_AXI_pu_conv_in12_1_1_reg[0]_0 ;
  wire \data_reg_AXI_pu_conv_in12_1_1_reg[0]_1 ;
  wire [0:0]\data_reg_AXI_pu_conv_in13_1_1_reg[0]_0 ;
  wire \data_reg_AXI_pu_conv_in13_1_1_reg[0]_1 ;
  wire [0:0]\data_reg_AXI_pu_conv_in14_1_1_reg[0]_0 ;
  wire \data_reg_AXI_pu_conv_in14_1_1_reg[0]_1 ;
  wire [0:0]\data_reg_AXI_pu_conv_in15_1_1_reg[0]_0 ;
  wire \data_reg_AXI_pu_conv_in15_1_1_reg[0]_1 ;
  wire [0:0]\data_reg_AXI_pu_conv_in16_1_1_reg[0]_0 ;
  wire \data_reg_AXI_pu_conv_in16_1_1_reg[0]_1 ;
  wire [0:0]\data_reg_AXI_pu_conv_in17_1_1_reg[0]_0 ;
  wire \data_reg_AXI_pu_conv_in17_1_1_reg[0]_1 ;
  wire [0:0]\data_reg_AXI_pu_conv_in18_1_1_reg[0]_0 ;
  wire \data_reg_AXI_pu_conv_in18_1_1_reg[0]_1 ;
  wire [0:0]\data_reg_AXI_pu_conv_in19_1_1_reg[0]_0 ;
  wire \data_reg_AXI_pu_conv_in19_1_1_reg[0]_1 ;
  wire [0:0]\data_reg_AXI_pu_conv_in1_1_1_reg[0]_0 ;
  wire \data_reg_AXI_pu_conv_in1_1_1_reg[0]_1 ;
  wire [0:0]\data_reg_AXI_pu_conv_in20_1_1_reg[0]_0 ;
  wire \data_reg_AXI_pu_conv_in20_1_1_reg[0]_1 ;
  wire [0:0]\data_reg_AXI_pu_conv_in21_1_1_reg[0]_0 ;
  wire \data_reg_AXI_pu_conv_in21_1_1_reg[0]_1 ;
  wire [0:0]\data_reg_AXI_pu_conv_in22_1_1_reg[0]_0 ;
  wire \data_reg_AXI_pu_conv_in22_1_1_reg[0]_1 ;
  wire [0:0]\data_reg_AXI_pu_conv_in23_1_1_reg[0]_0 ;
  wire \data_reg_AXI_pu_conv_in23_1_1_reg[0]_1 ;
  wire [0:0]\data_reg_AXI_pu_conv_in24_1_1_reg[0]_0 ;
  wire \data_reg_AXI_pu_conv_in24_1_1_reg[0]_1 ;
  wire [0:0]\data_reg_AXI_pu_conv_in25_1_1_reg[0]_0 ;
  wire \data_reg_AXI_pu_conv_in25_1_1_reg[0]_1 ;
  wire [0:0]\data_reg_AXI_pu_conv_in26_1_1_reg[0]_0 ;
  wire \data_reg_AXI_pu_conv_in26_1_1_reg[0]_1 ;
  wire [0:0]\data_reg_AXI_pu_conv_in27_1_1_reg[0]_0 ;
  wire \data_reg_AXI_pu_conv_in27_1_1_reg[0]_1 ;
  wire [0:0]\data_reg_AXI_pu_conv_in28_1_1_reg[0]_0 ;
  wire \data_reg_AXI_pu_conv_in28_1_1_reg[0]_1 ;
  wire [0:0]\data_reg_AXI_pu_conv_in29_1_1_reg[0]_0 ;
  wire \data_reg_AXI_pu_conv_in29_1_1_reg[0]_1 ;
  wire [0:0]\data_reg_AXI_pu_conv_in2_1_1_reg[0]_0 ;
  wire \data_reg_AXI_pu_conv_in2_1_1_reg[0]_1 ;
  wire [0:0]\data_reg_AXI_pu_conv_in30_1_1_reg[0]_0 ;
  wire \data_reg_AXI_pu_conv_in30_1_1_reg[0]_1 ;
  wire [0:0]\data_reg_AXI_pu_conv_in31_1_1_reg[0]_0 ;
  wire \data_reg_AXI_pu_conv_in31_1_1_reg[0]_1 ;
  wire [0:0]\data_reg_AXI_pu_conv_in3_1_1_reg[0]_0 ;
  wire \data_reg_AXI_pu_conv_in3_1_1_reg[0]_1 ;
  wire [0:0]\data_reg_AXI_pu_conv_in4_1_1_reg[0]_0 ;
  wire \data_reg_AXI_pu_conv_in4_1_1_reg[0]_1 ;
  wire [0:0]\data_reg_AXI_pu_conv_in5_1_1_reg[0]_0 ;
  wire \data_reg_AXI_pu_conv_in5_1_1_reg[0]_1 ;
  wire [0:0]\data_reg_AXI_pu_conv_in6_1_1_reg[0]_0 ;
  wire \data_reg_AXI_pu_conv_in6_1_1_reg[0]_1 ;
  wire [0:0]\data_reg_AXI_pu_conv_in7_1_1_reg[0]_0 ;
  wire \data_reg_AXI_pu_conv_in7_1_1_reg[0]_1 ;
  wire [0:0]\data_reg_AXI_pu_conv_in8_1_1_reg[0]_0 ;
  wire \data_reg_AXI_pu_conv_in8_1_1_reg[0]_1 ;
  wire [0:0]\data_reg_AXI_pu_conv_in9_1_1_reg[0]_0 ;
  wire \data_reg_AXI_pu_conv_in9_1_1_reg[0]_1 ;
  wire [0:0]read_reg_ip_timestamp;
  wire \read_reg_ip_timestamp_reg[31]_0 ;
  wire reset;

  FDRE \data_reg_AXI_pu_conv_in0_1_1_reg[0] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(\data_reg_AXI_pu_conv_in0_1_1_reg[0]_0 ),
        .Q(OPMODE),
        .R(reset));
  FDRE \data_reg_AXI_pu_conv_in10_1_1_reg[0] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(\data_reg_AXI_pu_conv_in10_1_1_reg[0]_1 ),
        .Q(\data_reg_AXI_pu_conv_in10_1_1_reg[0]_0 ),
        .R(reset));
  FDRE \data_reg_AXI_pu_conv_in11_1_1_reg[0] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(\data_reg_AXI_pu_conv_in11_1_1_reg[0]_1 ),
        .Q(\data_reg_AXI_pu_conv_in11_1_1_reg[0]_0 ),
        .R(reset));
  FDRE \data_reg_AXI_pu_conv_in12_1_1_reg[0] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(\data_reg_AXI_pu_conv_in12_1_1_reg[0]_1 ),
        .Q(\data_reg_AXI_pu_conv_in12_1_1_reg[0]_0 ),
        .R(reset));
  FDRE \data_reg_AXI_pu_conv_in13_1_1_reg[0] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(\data_reg_AXI_pu_conv_in13_1_1_reg[0]_1 ),
        .Q(\data_reg_AXI_pu_conv_in13_1_1_reg[0]_0 ),
        .R(reset));
  FDRE \data_reg_AXI_pu_conv_in14_1_1_reg[0] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(\data_reg_AXI_pu_conv_in14_1_1_reg[0]_1 ),
        .Q(\data_reg_AXI_pu_conv_in14_1_1_reg[0]_0 ),
        .R(reset));
  FDRE \data_reg_AXI_pu_conv_in15_1_1_reg[0] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(\data_reg_AXI_pu_conv_in15_1_1_reg[0]_1 ),
        .Q(\data_reg_AXI_pu_conv_in15_1_1_reg[0]_0 ),
        .R(reset));
  FDRE \data_reg_AXI_pu_conv_in16_1_1_reg[0] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(\data_reg_AXI_pu_conv_in16_1_1_reg[0]_1 ),
        .Q(\data_reg_AXI_pu_conv_in16_1_1_reg[0]_0 ),
        .R(reset));
  FDRE \data_reg_AXI_pu_conv_in17_1_1_reg[0] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(\data_reg_AXI_pu_conv_in17_1_1_reg[0]_1 ),
        .Q(\data_reg_AXI_pu_conv_in17_1_1_reg[0]_0 ),
        .R(reset));
  FDRE \data_reg_AXI_pu_conv_in18_1_1_reg[0] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(\data_reg_AXI_pu_conv_in18_1_1_reg[0]_1 ),
        .Q(\data_reg_AXI_pu_conv_in18_1_1_reg[0]_0 ),
        .R(reset));
  FDRE \data_reg_AXI_pu_conv_in19_1_1_reg[0] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(\data_reg_AXI_pu_conv_in19_1_1_reg[0]_1 ),
        .Q(\data_reg_AXI_pu_conv_in19_1_1_reg[0]_0 ),
        .R(reset));
  FDRE \data_reg_AXI_pu_conv_in1_1_1_reg[0] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(\data_reg_AXI_pu_conv_in1_1_1_reg[0]_1 ),
        .Q(\data_reg_AXI_pu_conv_in1_1_1_reg[0]_0 ),
        .R(reset));
  FDRE \data_reg_AXI_pu_conv_in20_1_1_reg[0] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(\data_reg_AXI_pu_conv_in20_1_1_reg[0]_1 ),
        .Q(\data_reg_AXI_pu_conv_in20_1_1_reg[0]_0 ),
        .R(reset));
  FDRE \data_reg_AXI_pu_conv_in21_1_1_reg[0] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(\data_reg_AXI_pu_conv_in21_1_1_reg[0]_1 ),
        .Q(\data_reg_AXI_pu_conv_in21_1_1_reg[0]_0 ),
        .R(reset));
  FDRE \data_reg_AXI_pu_conv_in22_1_1_reg[0] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(\data_reg_AXI_pu_conv_in22_1_1_reg[0]_1 ),
        .Q(\data_reg_AXI_pu_conv_in22_1_1_reg[0]_0 ),
        .R(reset));
  FDRE \data_reg_AXI_pu_conv_in23_1_1_reg[0] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(\data_reg_AXI_pu_conv_in23_1_1_reg[0]_1 ),
        .Q(\data_reg_AXI_pu_conv_in23_1_1_reg[0]_0 ),
        .R(reset));
  FDRE \data_reg_AXI_pu_conv_in24_1_1_reg[0] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(\data_reg_AXI_pu_conv_in24_1_1_reg[0]_1 ),
        .Q(\data_reg_AXI_pu_conv_in24_1_1_reg[0]_0 ),
        .R(reset));
  FDRE \data_reg_AXI_pu_conv_in25_1_1_reg[0] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(\data_reg_AXI_pu_conv_in25_1_1_reg[0]_1 ),
        .Q(\data_reg_AXI_pu_conv_in25_1_1_reg[0]_0 ),
        .R(reset));
  FDRE \data_reg_AXI_pu_conv_in26_1_1_reg[0] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(\data_reg_AXI_pu_conv_in26_1_1_reg[0]_1 ),
        .Q(\data_reg_AXI_pu_conv_in26_1_1_reg[0]_0 ),
        .R(reset));
  FDRE \data_reg_AXI_pu_conv_in27_1_1_reg[0] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(\data_reg_AXI_pu_conv_in27_1_1_reg[0]_1 ),
        .Q(\data_reg_AXI_pu_conv_in27_1_1_reg[0]_0 ),
        .R(reset));
  FDRE \data_reg_AXI_pu_conv_in28_1_1_reg[0] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(\data_reg_AXI_pu_conv_in28_1_1_reg[0]_1 ),
        .Q(\data_reg_AXI_pu_conv_in28_1_1_reg[0]_0 ),
        .R(reset));
  FDRE \data_reg_AXI_pu_conv_in29_1_1_reg[0] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(\data_reg_AXI_pu_conv_in29_1_1_reg[0]_1 ),
        .Q(\data_reg_AXI_pu_conv_in29_1_1_reg[0]_0 ),
        .R(reset));
  FDRE \data_reg_AXI_pu_conv_in2_1_1_reg[0] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(\data_reg_AXI_pu_conv_in2_1_1_reg[0]_1 ),
        .Q(\data_reg_AXI_pu_conv_in2_1_1_reg[0]_0 ),
        .R(reset));
  FDRE \data_reg_AXI_pu_conv_in30_1_1_reg[0] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(\data_reg_AXI_pu_conv_in30_1_1_reg[0]_1 ),
        .Q(\data_reg_AXI_pu_conv_in30_1_1_reg[0]_0 ),
        .R(reset));
  FDRE \data_reg_AXI_pu_conv_in31_1_1_reg[0] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(\data_reg_AXI_pu_conv_in31_1_1_reg[0]_1 ),
        .Q(\data_reg_AXI_pu_conv_in31_1_1_reg[0]_0 ),
        .R(reset));
  FDRE \data_reg_AXI_pu_conv_in3_1_1_reg[0] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(\data_reg_AXI_pu_conv_in3_1_1_reg[0]_1 ),
        .Q(\data_reg_AXI_pu_conv_in3_1_1_reg[0]_0 ),
        .R(reset));
  FDRE \data_reg_AXI_pu_conv_in4_1_1_reg[0] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(\data_reg_AXI_pu_conv_in4_1_1_reg[0]_1 ),
        .Q(\data_reg_AXI_pu_conv_in4_1_1_reg[0]_0 ),
        .R(reset));
  FDRE \data_reg_AXI_pu_conv_in5_1_1_reg[0] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(\data_reg_AXI_pu_conv_in5_1_1_reg[0]_1 ),
        .Q(\data_reg_AXI_pu_conv_in5_1_1_reg[0]_0 ),
        .R(reset));
  FDRE \data_reg_AXI_pu_conv_in6_1_1_reg[0] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(\data_reg_AXI_pu_conv_in6_1_1_reg[0]_1 ),
        .Q(\data_reg_AXI_pu_conv_in6_1_1_reg[0]_0 ),
        .R(reset));
  FDRE \data_reg_AXI_pu_conv_in7_1_1_reg[0] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(\data_reg_AXI_pu_conv_in7_1_1_reg[0]_1 ),
        .Q(\data_reg_AXI_pu_conv_in7_1_1_reg[0]_0 ),
        .R(reset));
  FDRE \data_reg_AXI_pu_conv_in8_1_1_reg[0] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(\data_reg_AXI_pu_conv_in8_1_1_reg[0]_1 ),
        .Q(\data_reg_AXI_pu_conv_in8_1_1_reg[0]_0 ),
        .R(reset));
  FDRE \data_reg_AXI_pu_conv_in9_1_1_reg[0] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(\data_reg_AXI_pu_conv_in9_1_1_reg[0]_1 ),
        .Q(\data_reg_AXI_pu_conv_in9_1_1_reg[0]_0 ),
        .R(reset));
  FDRE \read_reg_ip_timestamp_reg[31] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(\read_reg_ip_timestamp_reg[31]_0 ),
        .Q(read_reg_ip_timestamp),
        .R(1'b0));
endmodule

(* ORIG_REF_NAME = "uz_pu_con_ip_axi_lite" *) 
module zusys_uz_pu_con_ip_0_1_uz_pu_con_ip_axi_lite
   (FSM_sequential_axi_lite_rstate_reg,
    OPMODE,
    \data_reg_AXI_pu_conv_in1_1_1_reg[0] ,
    \data_reg_AXI_pu_conv_in2_1_1_reg[0] ,
    \data_reg_AXI_pu_conv_in3_1_1_reg[0] ,
    \data_reg_AXI_pu_conv_in4_1_1_reg[0] ,
    \data_reg_AXI_pu_conv_in5_1_1_reg[0] ,
    \data_reg_AXI_pu_conv_in6_1_1_reg[0] ,
    \data_reg_AXI_pu_conv_in7_1_1_reg[0] ,
    \data_reg_AXI_pu_conv_in8_1_1_reg[0] ,
    \data_reg_AXI_pu_conv_in9_1_1_reg[0] ,
    \data_reg_AXI_pu_conv_in10_1_1_reg[0] ,
    \data_reg_AXI_pu_conv_in11_1_1_reg[0] ,
    \data_reg_AXI_pu_conv_in12_1_1_reg[0] ,
    \data_reg_AXI_pu_conv_in13_1_1_reg[0] ,
    \data_reg_AXI_pu_conv_in14_1_1_reg[0] ,
    \data_reg_AXI_pu_conv_in15_1_1_reg[0] ,
    \data_reg_AXI_pu_conv_in16_1_1_reg[0] ,
    \data_reg_AXI_pu_conv_in17_1_1_reg[0] ,
    \data_reg_AXI_pu_conv_in18_1_1_reg[0] ,
    \data_reg_AXI_pu_conv_in19_1_1_reg[0] ,
    \data_reg_AXI_pu_conv_in20_1_1_reg[0] ,
    \data_reg_AXI_pu_conv_in21_1_1_reg[0] ,
    \data_reg_AXI_pu_conv_in22_1_1_reg[0] ,
    \data_reg_AXI_pu_conv_in23_1_1_reg[0] ,
    \data_reg_AXI_pu_conv_in24_1_1_reg[0] ,
    \data_reg_AXI_pu_conv_in25_1_1_reg[0] ,
    \data_reg_AXI_pu_conv_in26_1_1_reg[0] ,
    \data_reg_AXI_pu_conv_in27_1_1_reg[0] ,
    \data_reg_AXI_pu_conv_in28_1_1_reg[0] ,
    \data_reg_AXI_pu_conv_in29_1_1_reg[0] ,
    \data_reg_AXI_pu_conv_in30_1_1_reg[0] ,
    \data_reg_AXI_pu_conv_in31_1_1_reg[0] ,
    AXI4_Lite_RDATA,
    soft_reset,
    CEB2,
    AXI4_Lite_ARADDR_8_sp_1,
    AXI4_Lite_ARADDR_11_sp_1,
    AXI4_Lite_ARADDR_7_sp_1,
    \AXI4_Lite_ARADDR[8]_0 ,
    AXI4_Lite_ARADDR_4_sp_1,
    \AXI4_Lite_ARADDR[8]_1 ,
    \AXI4_Lite_ARADDR[7]_0 ,
    \AXI4_Lite_ARADDR[8]_2 ,
    \AXI4_Lite_ARADDR[4]_0 ,
    \AXI4_Lite_ARADDR[8]_3 ,
    \AXI4_Lite_ARADDR[7]_1 ,
    \AXI4_Lite_ARADDR[8]_4 ,
    AXI4_Lite_ARADDR_3_sp_1,
    \AXI4_Lite_ARADDR[8]_5 ,
    \AXI4_Lite_ARADDR[7]_2 ,
    \AXI4_Lite_ARADDR[8]_6 ,
    \AXI4_Lite_ARADDR[3]_0 ,
    \AXI4_Lite_ARADDR[8]_7 ,
    \AXI4_Lite_ARADDR[7]_3 ,
    \AXI4_Lite_ARADDR[8]_8 ,
    \AXI4_Lite_ARADDR[4]_1 ,
    \AXI4_Lite_ARADDR[8]_9 ,
    \AXI4_Lite_ARADDR[7]_4 ,
    \AXI4_Lite_ARADDR[8]_10 ,
    \AXI4_Lite_ARADDR[4]_2 ,
    \AXI4_Lite_ARADDR[8]_11 ,
    \AXI4_Lite_ARADDR[7]_5 ,
    \AXI4_Lite_ARADDR[8]_12 ,
    AXI4_Lite_ARADDR_6_sp_1,
    \AXI4_Lite_ARADDR[8]_13 ,
    wr_enb_1_reg,
    Q,
    AXI4_Lite_AWREADY,
    AXI4_Lite_ARREADY,
    reset_in,
    \wdata_reg[17] ,
    AXI4_Lite_ACLK,
    reset,
    \read_reg_ip_timestamp_reg[31] ,
    AXI4_Lite_ARADDR,
    AXI4_Lite_ARVALID,
    AXI4_Lite_AWVALID,
    AXI4_Lite_WVALID,
    AXI4_Lite_RREADY,
    AXI4_Lite_ARESETN,
    IPCORE_RESETN,
    AXI4_Lite_BREADY,
    AXI4_Lite_WSTRB,
    AXI4_Lite_AWADDR,
    AXI4_Lite_WDATA);
  output FSM_sequential_axi_lite_rstate_reg;
  output [0:0]OPMODE;
  output [0:0]\data_reg_AXI_pu_conv_in1_1_1_reg[0] ;
  output [0:0]\data_reg_AXI_pu_conv_in2_1_1_reg[0] ;
  output [0:0]\data_reg_AXI_pu_conv_in3_1_1_reg[0] ;
  output [0:0]\data_reg_AXI_pu_conv_in4_1_1_reg[0] ;
  output [0:0]\data_reg_AXI_pu_conv_in5_1_1_reg[0] ;
  output [0:0]\data_reg_AXI_pu_conv_in6_1_1_reg[0] ;
  output [0:0]\data_reg_AXI_pu_conv_in7_1_1_reg[0] ;
  output [0:0]\data_reg_AXI_pu_conv_in8_1_1_reg[0] ;
  output [0:0]\data_reg_AXI_pu_conv_in9_1_1_reg[0] ;
  output [0:0]\data_reg_AXI_pu_conv_in10_1_1_reg[0] ;
  output [0:0]\data_reg_AXI_pu_conv_in11_1_1_reg[0] ;
  output [0:0]\data_reg_AXI_pu_conv_in12_1_1_reg[0] ;
  output [0:0]\data_reg_AXI_pu_conv_in13_1_1_reg[0] ;
  output [0:0]\data_reg_AXI_pu_conv_in14_1_1_reg[0] ;
  output [0:0]\data_reg_AXI_pu_conv_in15_1_1_reg[0] ;
  output [0:0]\data_reg_AXI_pu_conv_in16_1_1_reg[0] ;
  output [0:0]\data_reg_AXI_pu_conv_in17_1_1_reg[0] ;
  output [0:0]\data_reg_AXI_pu_conv_in18_1_1_reg[0] ;
  output [0:0]\data_reg_AXI_pu_conv_in19_1_1_reg[0] ;
  output [0:0]\data_reg_AXI_pu_conv_in20_1_1_reg[0] ;
  output [0:0]\data_reg_AXI_pu_conv_in21_1_1_reg[0] ;
  output [0:0]\data_reg_AXI_pu_conv_in22_1_1_reg[0] ;
  output [0:0]\data_reg_AXI_pu_conv_in23_1_1_reg[0] ;
  output [0:0]\data_reg_AXI_pu_conv_in24_1_1_reg[0] ;
  output [0:0]\data_reg_AXI_pu_conv_in25_1_1_reg[0] ;
  output [0:0]\data_reg_AXI_pu_conv_in26_1_1_reg[0] ;
  output [0:0]\data_reg_AXI_pu_conv_in27_1_1_reg[0] ;
  output [0:0]\data_reg_AXI_pu_conv_in28_1_1_reg[0] ;
  output [0:0]\data_reg_AXI_pu_conv_in29_1_1_reg[0] ;
  output [0:0]\data_reg_AXI_pu_conv_in30_1_1_reg[0] ;
  output [0:0]\data_reg_AXI_pu_conv_in31_1_1_reg[0] ;
  output [0:0]AXI4_Lite_RDATA;
  output soft_reset;
  output CEB2;
  output AXI4_Lite_ARADDR_8_sp_1;
  output AXI4_Lite_ARADDR_11_sp_1;
  output AXI4_Lite_ARADDR_7_sp_1;
  output \AXI4_Lite_ARADDR[8]_0 ;
  output AXI4_Lite_ARADDR_4_sp_1;
  output \AXI4_Lite_ARADDR[8]_1 ;
  output \AXI4_Lite_ARADDR[7]_0 ;
  output \AXI4_Lite_ARADDR[8]_2 ;
  output \AXI4_Lite_ARADDR[4]_0 ;
  output \AXI4_Lite_ARADDR[8]_3 ;
  output \AXI4_Lite_ARADDR[7]_1 ;
  output \AXI4_Lite_ARADDR[8]_4 ;
  output AXI4_Lite_ARADDR_3_sp_1;
  output \AXI4_Lite_ARADDR[8]_5 ;
  output \AXI4_Lite_ARADDR[7]_2 ;
  output \AXI4_Lite_ARADDR[8]_6 ;
  output \AXI4_Lite_ARADDR[3]_0 ;
  output \AXI4_Lite_ARADDR[8]_7 ;
  output \AXI4_Lite_ARADDR[7]_3 ;
  output \AXI4_Lite_ARADDR[8]_8 ;
  output \AXI4_Lite_ARADDR[4]_1 ;
  output \AXI4_Lite_ARADDR[8]_9 ;
  output \AXI4_Lite_ARADDR[7]_4 ;
  output \AXI4_Lite_ARADDR[8]_10 ;
  output \AXI4_Lite_ARADDR[4]_2 ;
  output \AXI4_Lite_ARADDR[8]_11 ;
  output \AXI4_Lite_ARADDR[7]_5 ;
  output \AXI4_Lite_ARADDR[8]_12 ;
  output AXI4_Lite_ARADDR_6_sp_1;
  output \AXI4_Lite_ARADDR[8]_13 ;
  output wr_enb_1_reg;
  output [1:0]Q;
  output AXI4_Lite_AWREADY;
  output AXI4_Lite_ARREADY;
  output reset_in;
  output [16:0]\wdata_reg[17] ;
  input AXI4_Lite_ACLK;
  input reset;
  input \read_reg_ip_timestamp_reg[31] ;
  input [13:0]AXI4_Lite_ARADDR;
  input AXI4_Lite_ARVALID;
  input AXI4_Lite_AWVALID;
  input AXI4_Lite_WVALID;
  input AXI4_Lite_RREADY;
  input AXI4_Lite_ARESETN;
  input IPCORE_RESETN;
  input AXI4_Lite_BREADY;
  input [3:0]AXI4_Lite_WSTRB;
  input [13:0]AXI4_Lite_AWADDR;
  input [17:0]AXI4_Lite_WDATA;

  wire AXI4_Lite_ACLK;
  wire [13:0]AXI4_Lite_ARADDR;
  wire \AXI4_Lite_ARADDR[3]_0 ;
  wire \AXI4_Lite_ARADDR[4]_0 ;
  wire \AXI4_Lite_ARADDR[4]_1 ;
  wire \AXI4_Lite_ARADDR[4]_2 ;
  wire \AXI4_Lite_ARADDR[7]_0 ;
  wire \AXI4_Lite_ARADDR[7]_1 ;
  wire \AXI4_Lite_ARADDR[7]_2 ;
  wire \AXI4_Lite_ARADDR[7]_3 ;
  wire \AXI4_Lite_ARADDR[7]_4 ;
  wire \AXI4_Lite_ARADDR[7]_5 ;
  wire \AXI4_Lite_ARADDR[8]_0 ;
  wire \AXI4_Lite_ARADDR[8]_1 ;
  wire \AXI4_Lite_ARADDR[8]_10 ;
  wire \AXI4_Lite_ARADDR[8]_11 ;
  wire \AXI4_Lite_ARADDR[8]_12 ;
  wire \AXI4_Lite_ARADDR[8]_13 ;
  wire \AXI4_Lite_ARADDR[8]_2 ;
  wire \AXI4_Lite_ARADDR[8]_3 ;
  wire \AXI4_Lite_ARADDR[8]_4 ;
  wire \AXI4_Lite_ARADDR[8]_5 ;
  wire \AXI4_Lite_ARADDR[8]_6 ;
  wire \AXI4_Lite_ARADDR[8]_7 ;
  wire \AXI4_Lite_ARADDR[8]_8 ;
  wire \AXI4_Lite_ARADDR[8]_9 ;
  wire AXI4_Lite_ARADDR_11_sn_1;
  wire AXI4_Lite_ARADDR_3_sn_1;
  wire AXI4_Lite_ARADDR_4_sn_1;
  wire AXI4_Lite_ARADDR_6_sn_1;
  wire AXI4_Lite_ARADDR_7_sn_1;
  wire AXI4_Lite_ARADDR_8_sn_1;
  wire AXI4_Lite_ARESETN;
  wire AXI4_Lite_ARREADY;
  wire AXI4_Lite_ARVALID;
  wire [13:0]AXI4_Lite_AWADDR;
  wire AXI4_Lite_AWREADY;
  wire AXI4_Lite_AWVALID;
  wire AXI4_Lite_BREADY;
  wire [0:0]AXI4_Lite_RDATA;
  wire AXI4_Lite_RREADY;
  wire [17:0]AXI4_Lite_WDATA;
  wire [3:0]AXI4_Lite_WSTRB;
  wire AXI4_Lite_WVALID;
  wire CEB2;
  wire FSM_sequential_axi_lite_rstate_reg;
  wire IPCORE_RESETN;
  wire [0:0]OPMODE;
  wire [1:0]Q;
  wire [0:0]\data_reg_AXI_pu_conv_in10_1_1_reg[0] ;
  wire [0:0]\data_reg_AXI_pu_conv_in11_1_1_reg[0] ;
  wire [0:0]\data_reg_AXI_pu_conv_in12_1_1_reg[0] ;
  wire [0:0]\data_reg_AXI_pu_conv_in13_1_1_reg[0] ;
  wire [0:0]\data_reg_AXI_pu_conv_in14_1_1_reg[0] ;
  wire [0:0]\data_reg_AXI_pu_conv_in15_1_1_reg[0] ;
  wire [0:0]\data_reg_AXI_pu_conv_in16_1_1_reg[0] ;
  wire [0:0]\data_reg_AXI_pu_conv_in17_1_1_reg[0] ;
  wire [0:0]\data_reg_AXI_pu_conv_in18_1_1_reg[0] ;
  wire [0:0]\data_reg_AXI_pu_conv_in19_1_1_reg[0] ;
  wire [0:0]\data_reg_AXI_pu_conv_in1_1_1_reg[0] ;
  wire [0:0]\data_reg_AXI_pu_conv_in20_1_1_reg[0] ;
  wire [0:0]\data_reg_AXI_pu_conv_in21_1_1_reg[0] ;
  wire [0:0]\data_reg_AXI_pu_conv_in22_1_1_reg[0] ;
  wire [0:0]\data_reg_AXI_pu_conv_in23_1_1_reg[0] ;
  wire [0:0]\data_reg_AXI_pu_conv_in24_1_1_reg[0] ;
  wire [0:0]\data_reg_AXI_pu_conv_in25_1_1_reg[0] ;
  wire [0:0]\data_reg_AXI_pu_conv_in26_1_1_reg[0] ;
  wire [0:0]\data_reg_AXI_pu_conv_in27_1_1_reg[0] ;
  wire [0:0]\data_reg_AXI_pu_conv_in28_1_1_reg[0] ;
  wire [0:0]\data_reg_AXI_pu_conv_in29_1_1_reg[0] ;
  wire [0:0]\data_reg_AXI_pu_conv_in2_1_1_reg[0] ;
  wire [0:0]\data_reg_AXI_pu_conv_in30_1_1_reg[0] ;
  wire [0:0]\data_reg_AXI_pu_conv_in31_1_1_reg[0] ;
  wire [0:0]\data_reg_AXI_pu_conv_in3_1_1_reg[0] ;
  wire [0:0]\data_reg_AXI_pu_conv_in4_1_1_reg[0] ;
  wire [0:0]\data_reg_AXI_pu_conv_in5_1_1_reg[0] ;
  wire [0:0]\data_reg_AXI_pu_conv_in6_1_1_reg[0] ;
  wire [0:0]\data_reg_AXI_pu_conv_in7_1_1_reg[0] ;
  wire [0:0]\data_reg_AXI_pu_conv_in8_1_1_reg[0] ;
  wire [0:0]\data_reg_AXI_pu_conv_in9_1_1_reg[0] ;
  wire [31:31]read_reg_ip_timestamp;
  wire \read_reg_ip_timestamp_reg[31] ;
  wire reset;
  wire reset_in;
  wire soft_reset;
  wire u_uz_pu_con_ip_axi_lite_module_inst_n_40;
  wire u_uz_pu_con_ip_axi_lite_module_inst_n_41;
  wire u_uz_pu_con_ip_axi_lite_module_inst_n_42;
  wire u_uz_pu_con_ip_axi_lite_module_inst_n_43;
  wire u_uz_pu_con_ip_axi_lite_module_inst_n_44;
  wire u_uz_pu_con_ip_axi_lite_module_inst_n_45;
  wire u_uz_pu_con_ip_axi_lite_module_inst_n_46;
  wire u_uz_pu_con_ip_axi_lite_module_inst_n_47;
  wire u_uz_pu_con_ip_axi_lite_module_inst_n_48;
  wire u_uz_pu_con_ip_axi_lite_module_inst_n_49;
  wire u_uz_pu_con_ip_axi_lite_module_inst_n_50;
  wire u_uz_pu_con_ip_axi_lite_module_inst_n_51;
  wire u_uz_pu_con_ip_axi_lite_module_inst_n_52;
  wire u_uz_pu_con_ip_axi_lite_module_inst_n_53;
  wire u_uz_pu_con_ip_axi_lite_module_inst_n_54;
  wire u_uz_pu_con_ip_axi_lite_module_inst_n_55;
  wire u_uz_pu_con_ip_axi_lite_module_inst_n_56;
  wire u_uz_pu_con_ip_axi_lite_module_inst_n_57;
  wire u_uz_pu_con_ip_axi_lite_module_inst_n_58;
  wire u_uz_pu_con_ip_axi_lite_module_inst_n_59;
  wire u_uz_pu_con_ip_axi_lite_module_inst_n_60;
  wire u_uz_pu_con_ip_axi_lite_module_inst_n_61;
  wire u_uz_pu_con_ip_axi_lite_module_inst_n_62;
  wire u_uz_pu_con_ip_axi_lite_module_inst_n_63;
  wire u_uz_pu_con_ip_axi_lite_module_inst_n_64;
  wire u_uz_pu_con_ip_axi_lite_module_inst_n_65;
  wire u_uz_pu_con_ip_axi_lite_module_inst_n_66;
  wire u_uz_pu_con_ip_axi_lite_module_inst_n_67;
  wire u_uz_pu_con_ip_axi_lite_module_inst_n_68;
  wire u_uz_pu_con_ip_axi_lite_module_inst_n_69;
  wire u_uz_pu_con_ip_axi_lite_module_inst_n_70;
  wire u_uz_pu_con_ip_axi_lite_module_inst_n_71;
  wire [16:0]\wdata_reg[17] ;
  wire wr_enb_1_reg;

  assign AXI4_Lite_ARADDR_11_sp_1 = AXI4_Lite_ARADDR_11_sn_1;
  assign AXI4_Lite_ARADDR_3_sp_1 = AXI4_Lite_ARADDR_3_sn_1;
  assign AXI4_Lite_ARADDR_4_sp_1 = AXI4_Lite_ARADDR_4_sn_1;
  assign AXI4_Lite_ARADDR_6_sp_1 = AXI4_Lite_ARADDR_6_sn_1;
  assign AXI4_Lite_ARADDR_7_sp_1 = AXI4_Lite_ARADDR_7_sn_1;
  assign AXI4_Lite_ARADDR_8_sp_1 = AXI4_Lite_ARADDR_8_sn_1;
  zusys_uz_pu_con_ip_0_1_uz_pu_con_ip_addr_decoder u_uz_pu_con_ip_addr_decoder_inst
       (.AXI4_Lite_ACLK(AXI4_Lite_ACLK),
        .OPMODE(OPMODE),
        .\data_reg_AXI_pu_conv_in0_1_1_reg[0]_0 (u_uz_pu_con_ip_axi_lite_module_inst_n_71),
        .\data_reg_AXI_pu_conv_in10_1_1_reg[0]_0 (\data_reg_AXI_pu_conv_in10_1_1_reg[0] ),
        .\data_reg_AXI_pu_conv_in10_1_1_reg[0]_1 (u_uz_pu_con_ip_axi_lite_module_inst_n_65),
        .\data_reg_AXI_pu_conv_in11_1_1_reg[0]_0 (\data_reg_AXI_pu_conv_in11_1_1_reg[0] ),
        .\data_reg_AXI_pu_conv_in11_1_1_reg[0]_1 (u_uz_pu_con_ip_axi_lite_module_inst_n_61),
        .\data_reg_AXI_pu_conv_in12_1_1_reg[0]_0 (\data_reg_AXI_pu_conv_in12_1_1_reg[0] ),
        .\data_reg_AXI_pu_conv_in12_1_1_reg[0]_1 (u_uz_pu_con_ip_axi_lite_module_inst_n_57),
        .\data_reg_AXI_pu_conv_in13_1_1_reg[0]_0 (\data_reg_AXI_pu_conv_in13_1_1_reg[0] ),
        .\data_reg_AXI_pu_conv_in13_1_1_reg[0]_1 (u_uz_pu_con_ip_axi_lite_module_inst_n_53),
        .\data_reg_AXI_pu_conv_in14_1_1_reg[0]_0 (\data_reg_AXI_pu_conv_in14_1_1_reg[0] ),
        .\data_reg_AXI_pu_conv_in14_1_1_reg[0]_1 (u_uz_pu_con_ip_axi_lite_module_inst_n_49),
        .\data_reg_AXI_pu_conv_in15_1_1_reg[0]_0 (\data_reg_AXI_pu_conv_in15_1_1_reg[0] ),
        .\data_reg_AXI_pu_conv_in15_1_1_reg[0]_1 (u_uz_pu_con_ip_axi_lite_module_inst_n_45),
        .\data_reg_AXI_pu_conv_in16_1_1_reg[0]_0 (\data_reg_AXI_pu_conv_in16_1_1_reg[0] ),
        .\data_reg_AXI_pu_conv_in16_1_1_reg[0]_1 (u_uz_pu_con_ip_axi_lite_module_inst_n_41),
        .\data_reg_AXI_pu_conv_in17_1_1_reg[0]_0 (\data_reg_AXI_pu_conv_in17_1_1_reg[0] ),
        .\data_reg_AXI_pu_conv_in17_1_1_reg[0]_1 (u_uz_pu_con_ip_axi_lite_module_inst_n_68),
        .\data_reg_AXI_pu_conv_in18_1_1_reg[0]_0 (\data_reg_AXI_pu_conv_in18_1_1_reg[0] ),
        .\data_reg_AXI_pu_conv_in18_1_1_reg[0]_1 (u_uz_pu_con_ip_axi_lite_module_inst_n_64),
        .\data_reg_AXI_pu_conv_in19_1_1_reg[0]_0 (\data_reg_AXI_pu_conv_in19_1_1_reg[0] ),
        .\data_reg_AXI_pu_conv_in19_1_1_reg[0]_1 (u_uz_pu_con_ip_axi_lite_module_inst_n_60),
        .\data_reg_AXI_pu_conv_in1_1_1_reg[0]_0 (\data_reg_AXI_pu_conv_in1_1_1_reg[0] ),
        .\data_reg_AXI_pu_conv_in1_1_1_reg[0]_1 (u_uz_pu_con_ip_axi_lite_module_inst_n_70),
        .\data_reg_AXI_pu_conv_in20_1_1_reg[0]_0 (\data_reg_AXI_pu_conv_in20_1_1_reg[0] ),
        .\data_reg_AXI_pu_conv_in20_1_1_reg[0]_1 (u_uz_pu_con_ip_axi_lite_module_inst_n_56),
        .\data_reg_AXI_pu_conv_in21_1_1_reg[0]_0 (\data_reg_AXI_pu_conv_in21_1_1_reg[0] ),
        .\data_reg_AXI_pu_conv_in21_1_1_reg[0]_1 (u_uz_pu_con_ip_axi_lite_module_inst_n_52),
        .\data_reg_AXI_pu_conv_in22_1_1_reg[0]_0 (\data_reg_AXI_pu_conv_in22_1_1_reg[0] ),
        .\data_reg_AXI_pu_conv_in22_1_1_reg[0]_1 (u_uz_pu_con_ip_axi_lite_module_inst_n_48),
        .\data_reg_AXI_pu_conv_in23_1_1_reg[0]_0 (\data_reg_AXI_pu_conv_in23_1_1_reg[0] ),
        .\data_reg_AXI_pu_conv_in23_1_1_reg[0]_1 (u_uz_pu_con_ip_axi_lite_module_inst_n_44),
        .\data_reg_AXI_pu_conv_in24_1_1_reg[0]_0 (\data_reg_AXI_pu_conv_in24_1_1_reg[0] ),
        .\data_reg_AXI_pu_conv_in24_1_1_reg[0]_1 (u_uz_pu_con_ip_axi_lite_module_inst_n_40),
        .\data_reg_AXI_pu_conv_in25_1_1_reg[0]_0 (\data_reg_AXI_pu_conv_in25_1_1_reg[0] ),
        .\data_reg_AXI_pu_conv_in25_1_1_reg[0]_1 (u_uz_pu_con_ip_axi_lite_module_inst_n_67),
        .\data_reg_AXI_pu_conv_in26_1_1_reg[0]_0 (\data_reg_AXI_pu_conv_in26_1_1_reg[0] ),
        .\data_reg_AXI_pu_conv_in26_1_1_reg[0]_1 (u_uz_pu_con_ip_axi_lite_module_inst_n_63),
        .\data_reg_AXI_pu_conv_in27_1_1_reg[0]_0 (\data_reg_AXI_pu_conv_in27_1_1_reg[0] ),
        .\data_reg_AXI_pu_conv_in27_1_1_reg[0]_1 (u_uz_pu_con_ip_axi_lite_module_inst_n_59),
        .\data_reg_AXI_pu_conv_in28_1_1_reg[0]_0 (\data_reg_AXI_pu_conv_in28_1_1_reg[0] ),
        .\data_reg_AXI_pu_conv_in28_1_1_reg[0]_1 (u_uz_pu_con_ip_axi_lite_module_inst_n_55),
        .\data_reg_AXI_pu_conv_in29_1_1_reg[0]_0 (\data_reg_AXI_pu_conv_in29_1_1_reg[0] ),
        .\data_reg_AXI_pu_conv_in29_1_1_reg[0]_1 (u_uz_pu_con_ip_axi_lite_module_inst_n_51),
        .\data_reg_AXI_pu_conv_in2_1_1_reg[0]_0 (\data_reg_AXI_pu_conv_in2_1_1_reg[0] ),
        .\data_reg_AXI_pu_conv_in2_1_1_reg[0]_1 (u_uz_pu_con_ip_axi_lite_module_inst_n_66),
        .\data_reg_AXI_pu_conv_in30_1_1_reg[0]_0 (\data_reg_AXI_pu_conv_in30_1_1_reg[0] ),
        .\data_reg_AXI_pu_conv_in30_1_1_reg[0]_1 (u_uz_pu_con_ip_axi_lite_module_inst_n_47),
        .\data_reg_AXI_pu_conv_in31_1_1_reg[0]_0 (\data_reg_AXI_pu_conv_in31_1_1_reg[0] ),
        .\data_reg_AXI_pu_conv_in31_1_1_reg[0]_1 (u_uz_pu_con_ip_axi_lite_module_inst_n_43),
        .\data_reg_AXI_pu_conv_in3_1_1_reg[0]_0 (\data_reg_AXI_pu_conv_in3_1_1_reg[0] ),
        .\data_reg_AXI_pu_conv_in3_1_1_reg[0]_1 (u_uz_pu_con_ip_axi_lite_module_inst_n_62),
        .\data_reg_AXI_pu_conv_in4_1_1_reg[0]_0 (\data_reg_AXI_pu_conv_in4_1_1_reg[0] ),
        .\data_reg_AXI_pu_conv_in4_1_1_reg[0]_1 (u_uz_pu_con_ip_axi_lite_module_inst_n_58),
        .\data_reg_AXI_pu_conv_in5_1_1_reg[0]_0 (\data_reg_AXI_pu_conv_in5_1_1_reg[0] ),
        .\data_reg_AXI_pu_conv_in5_1_1_reg[0]_1 (u_uz_pu_con_ip_axi_lite_module_inst_n_54),
        .\data_reg_AXI_pu_conv_in6_1_1_reg[0]_0 (\data_reg_AXI_pu_conv_in6_1_1_reg[0] ),
        .\data_reg_AXI_pu_conv_in6_1_1_reg[0]_1 (u_uz_pu_con_ip_axi_lite_module_inst_n_50),
        .\data_reg_AXI_pu_conv_in7_1_1_reg[0]_0 (\data_reg_AXI_pu_conv_in7_1_1_reg[0] ),
        .\data_reg_AXI_pu_conv_in7_1_1_reg[0]_1 (u_uz_pu_con_ip_axi_lite_module_inst_n_46),
        .\data_reg_AXI_pu_conv_in8_1_1_reg[0]_0 (\data_reg_AXI_pu_conv_in8_1_1_reg[0] ),
        .\data_reg_AXI_pu_conv_in8_1_1_reg[0]_1 (u_uz_pu_con_ip_axi_lite_module_inst_n_42),
        .\data_reg_AXI_pu_conv_in9_1_1_reg[0]_0 (\data_reg_AXI_pu_conv_in9_1_1_reg[0] ),
        .\data_reg_AXI_pu_conv_in9_1_1_reg[0]_1 (u_uz_pu_con_ip_axi_lite_module_inst_n_69),
        .read_reg_ip_timestamp(read_reg_ip_timestamp),
        .\read_reg_ip_timestamp_reg[31]_0 (\read_reg_ip_timestamp_reg[31] ),
        .reset(reset));
  zusys_uz_pu_con_ip_0_1_uz_pu_con_ip_axi_lite_module u_uz_pu_con_ip_axi_lite_module_inst
       (.AXI4_Lite_ACLK(AXI4_Lite_ACLK),
        .AXI4_Lite_ARADDR(AXI4_Lite_ARADDR),
        .\AXI4_Lite_ARADDR[3]_0 (\AXI4_Lite_ARADDR[3]_0 ),
        .\AXI4_Lite_ARADDR[4]_0 (\AXI4_Lite_ARADDR[4]_0 ),
        .\AXI4_Lite_ARADDR[4]_1 (\AXI4_Lite_ARADDR[4]_1 ),
        .\AXI4_Lite_ARADDR[4]_2 (\AXI4_Lite_ARADDR[4]_2 ),
        .\AXI4_Lite_ARADDR[7]_0 (\AXI4_Lite_ARADDR[7]_0 ),
        .\AXI4_Lite_ARADDR[7]_1 (\AXI4_Lite_ARADDR[7]_1 ),
        .\AXI4_Lite_ARADDR[7]_2 (\AXI4_Lite_ARADDR[7]_2 ),
        .\AXI4_Lite_ARADDR[7]_3 (\AXI4_Lite_ARADDR[7]_3 ),
        .\AXI4_Lite_ARADDR[7]_4 (\AXI4_Lite_ARADDR[7]_4 ),
        .\AXI4_Lite_ARADDR[7]_5 (\AXI4_Lite_ARADDR[7]_5 ),
        .\AXI4_Lite_ARADDR[8]_0 (\AXI4_Lite_ARADDR[8]_0 ),
        .\AXI4_Lite_ARADDR[8]_1 (\AXI4_Lite_ARADDR[8]_1 ),
        .\AXI4_Lite_ARADDR[8]_10 (\AXI4_Lite_ARADDR[8]_10 ),
        .\AXI4_Lite_ARADDR[8]_11 (\AXI4_Lite_ARADDR[8]_11 ),
        .\AXI4_Lite_ARADDR[8]_12 (\AXI4_Lite_ARADDR[8]_12 ),
        .\AXI4_Lite_ARADDR[8]_13 (\AXI4_Lite_ARADDR[8]_13 ),
        .\AXI4_Lite_ARADDR[8]_2 (\AXI4_Lite_ARADDR[8]_2 ),
        .\AXI4_Lite_ARADDR[8]_3 (\AXI4_Lite_ARADDR[8]_3 ),
        .\AXI4_Lite_ARADDR[8]_4 (\AXI4_Lite_ARADDR[8]_4 ),
        .\AXI4_Lite_ARADDR[8]_5 (\AXI4_Lite_ARADDR[8]_5 ),
        .\AXI4_Lite_ARADDR[8]_6 (\AXI4_Lite_ARADDR[8]_6 ),
        .\AXI4_Lite_ARADDR[8]_7 (\AXI4_Lite_ARADDR[8]_7 ),
        .\AXI4_Lite_ARADDR[8]_8 (\AXI4_Lite_ARADDR[8]_8 ),
        .\AXI4_Lite_ARADDR[8]_9 (\AXI4_Lite_ARADDR[8]_9 ),
        .AXI4_Lite_ARADDR_11_sp_1(AXI4_Lite_ARADDR_11_sn_1),
        .AXI4_Lite_ARADDR_3_sp_1(AXI4_Lite_ARADDR_3_sn_1),
        .AXI4_Lite_ARADDR_4_sp_1(AXI4_Lite_ARADDR_4_sn_1),
        .AXI4_Lite_ARADDR_6_sp_1(AXI4_Lite_ARADDR_6_sn_1),
        .AXI4_Lite_ARADDR_7_sp_1(AXI4_Lite_ARADDR_7_sn_1),
        .AXI4_Lite_ARADDR_8_sp_1(AXI4_Lite_ARADDR_8_sn_1),
        .AXI4_Lite_ARESETN(AXI4_Lite_ARESETN),
        .AXI4_Lite_ARREADY(AXI4_Lite_ARREADY),
        .AXI4_Lite_ARVALID(AXI4_Lite_ARVALID),
        .AXI4_Lite_AWADDR(AXI4_Lite_AWADDR),
        .AXI4_Lite_AWREADY(AXI4_Lite_AWREADY),
        .AXI4_Lite_AWVALID(AXI4_Lite_AWVALID),
        .AXI4_Lite_BREADY(AXI4_Lite_BREADY),
        .AXI4_Lite_RDATA(AXI4_Lite_RDATA),
        .AXI4_Lite_RREADY(AXI4_Lite_RREADY),
        .AXI4_Lite_WDATA(AXI4_Lite_WDATA),
        .AXI4_Lite_WSTRB(AXI4_Lite_WSTRB),
        .AXI4_Lite_WVALID(AXI4_Lite_WVALID),
        .CEB2(CEB2),
        .FSM_sequential_axi_lite_rstate_reg_0(FSM_sequential_axi_lite_rstate_reg),
        .IPCORE_RESETN(IPCORE_RESETN),
        .OPMODE(OPMODE),
        .Q(Q),
        .\data_reg_AXI_pu_conv_in10_1_1_reg[0] (\data_reg_AXI_pu_conv_in10_1_1_reg[0] ),
        .\data_reg_AXI_pu_conv_in11_1_1_reg[0] (\data_reg_AXI_pu_conv_in11_1_1_reg[0] ),
        .\data_reg_AXI_pu_conv_in12_1_1_reg[0] (\data_reg_AXI_pu_conv_in12_1_1_reg[0] ),
        .\data_reg_AXI_pu_conv_in13_1_1_reg[0] (\data_reg_AXI_pu_conv_in13_1_1_reg[0] ),
        .\data_reg_AXI_pu_conv_in14_1_1_reg[0] (\data_reg_AXI_pu_conv_in14_1_1_reg[0] ),
        .\data_reg_AXI_pu_conv_in15_1_1_reg[0] (\data_reg_AXI_pu_conv_in15_1_1_reg[0] ),
        .\data_reg_AXI_pu_conv_in16_1_1_reg[0] (\data_reg_AXI_pu_conv_in16_1_1_reg[0] ),
        .\data_reg_AXI_pu_conv_in17_1_1_reg[0] (\data_reg_AXI_pu_conv_in17_1_1_reg[0] ),
        .\data_reg_AXI_pu_conv_in18_1_1_reg[0] (\data_reg_AXI_pu_conv_in18_1_1_reg[0] ),
        .\data_reg_AXI_pu_conv_in19_1_1_reg[0] (\data_reg_AXI_pu_conv_in19_1_1_reg[0] ),
        .\data_reg_AXI_pu_conv_in1_1_1_reg[0] (\data_reg_AXI_pu_conv_in1_1_1_reg[0] ),
        .\data_reg_AXI_pu_conv_in20_1_1_reg[0] (\data_reg_AXI_pu_conv_in20_1_1_reg[0] ),
        .\data_reg_AXI_pu_conv_in21_1_1_reg[0] (\data_reg_AXI_pu_conv_in21_1_1_reg[0] ),
        .\data_reg_AXI_pu_conv_in22_1_1_reg[0] (\data_reg_AXI_pu_conv_in22_1_1_reg[0] ),
        .\data_reg_AXI_pu_conv_in23_1_1_reg[0] (\data_reg_AXI_pu_conv_in23_1_1_reg[0] ),
        .\data_reg_AXI_pu_conv_in24_1_1_reg[0] (\data_reg_AXI_pu_conv_in24_1_1_reg[0] ),
        .\data_reg_AXI_pu_conv_in25_1_1_reg[0] (\data_reg_AXI_pu_conv_in25_1_1_reg[0] ),
        .\data_reg_AXI_pu_conv_in26_1_1_reg[0] (\data_reg_AXI_pu_conv_in26_1_1_reg[0] ),
        .\data_reg_AXI_pu_conv_in27_1_1_reg[0] (\data_reg_AXI_pu_conv_in27_1_1_reg[0] ),
        .\data_reg_AXI_pu_conv_in28_1_1_reg[0] (\data_reg_AXI_pu_conv_in28_1_1_reg[0] ),
        .\data_reg_AXI_pu_conv_in29_1_1_reg[0] (\data_reg_AXI_pu_conv_in29_1_1_reg[0] ),
        .\data_reg_AXI_pu_conv_in2_1_1_reg[0] (\data_reg_AXI_pu_conv_in2_1_1_reg[0] ),
        .\data_reg_AXI_pu_conv_in30_1_1_reg[0] (\data_reg_AXI_pu_conv_in30_1_1_reg[0] ),
        .\data_reg_AXI_pu_conv_in31_1_1_reg[0] (\data_reg_AXI_pu_conv_in31_1_1_reg[0] ),
        .\data_reg_AXI_pu_conv_in3_1_1_reg[0] (\data_reg_AXI_pu_conv_in3_1_1_reg[0] ),
        .\data_reg_AXI_pu_conv_in4_1_1_reg[0] (\data_reg_AXI_pu_conv_in4_1_1_reg[0] ),
        .\data_reg_AXI_pu_conv_in5_1_1_reg[0] (\data_reg_AXI_pu_conv_in5_1_1_reg[0] ),
        .\data_reg_AXI_pu_conv_in6_1_1_reg[0] (\data_reg_AXI_pu_conv_in6_1_1_reg[0] ),
        .\data_reg_AXI_pu_conv_in7_1_1_reg[0] (\data_reg_AXI_pu_conv_in7_1_1_reg[0] ),
        .\data_reg_AXI_pu_conv_in8_1_1_reg[0] (\data_reg_AXI_pu_conv_in8_1_1_reg[0] ),
        .\data_reg_AXI_pu_conv_in9_1_1_reg[0] (\data_reg_AXI_pu_conv_in9_1_1_reg[0] ),
        .read_reg_ip_timestamp(read_reg_ip_timestamp),
        .reset_in(reset_in),
        .soft_reset(soft_reset),
        .\wdata_reg[0]_0 (u_uz_pu_con_ip_axi_lite_module_inst_n_40),
        .\wdata_reg[0]_1 (u_uz_pu_con_ip_axi_lite_module_inst_n_41),
        .\wdata_reg[0]_10 (u_uz_pu_con_ip_axi_lite_module_inst_n_50),
        .\wdata_reg[0]_11 (u_uz_pu_con_ip_axi_lite_module_inst_n_51),
        .\wdata_reg[0]_12 (u_uz_pu_con_ip_axi_lite_module_inst_n_52),
        .\wdata_reg[0]_13 (u_uz_pu_con_ip_axi_lite_module_inst_n_53),
        .\wdata_reg[0]_14 (u_uz_pu_con_ip_axi_lite_module_inst_n_54),
        .\wdata_reg[0]_15 (u_uz_pu_con_ip_axi_lite_module_inst_n_55),
        .\wdata_reg[0]_16 (u_uz_pu_con_ip_axi_lite_module_inst_n_56),
        .\wdata_reg[0]_17 (u_uz_pu_con_ip_axi_lite_module_inst_n_57),
        .\wdata_reg[0]_18 (u_uz_pu_con_ip_axi_lite_module_inst_n_58),
        .\wdata_reg[0]_19 (u_uz_pu_con_ip_axi_lite_module_inst_n_59),
        .\wdata_reg[0]_2 (u_uz_pu_con_ip_axi_lite_module_inst_n_42),
        .\wdata_reg[0]_20 (u_uz_pu_con_ip_axi_lite_module_inst_n_60),
        .\wdata_reg[0]_21 (u_uz_pu_con_ip_axi_lite_module_inst_n_61),
        .\wdata_reg[0]_22 (u_uz_pu_con_ip_axi_lite_module_inst_n_62),
        .\wdata_reg[0]_23 (u_uz_pu_con_ip_axi_lite_module_inst_n_63),
        .\wdata_reg[0]_24 (u_uz_pu_con_ip_axi_lite_module_inst_n_64),
        .\wdata_reg[0]_25 (u_uz_pu_con_ip_axi_lite_module_inst_n_65),
        .\wdata_reg[0]_26 (u_uz_pu_con_ip_axi_lite_module_inst_n_66),
        .\wdata_reg[0]_27 (u_uz_pu_con_ip_axi_lite_module_inst_n_67),
        .\wdata_reg[0]_28 (u_uz_pu_con_ip_axi_lite_module_inst_n_68),
        .\wdata_reg[0]_29 (u_uz_pu_con_ip_axi_lite_module_inst_n_69),
        .\wdata_reg[0]_3 (u_uz_pu_con_ip_axi_lite_module_inst_n_43),
        .\wdata_reg[0]_30 (u_uz_pu_con_ip_axi_lite_module_inst_n_70),
        .\wdata_reg[0]_31 (u_uz_pu_con_ip_axi_lite_module_inst_n_71),
        .\wdata_reg[0]_4 (u_uz_pu_con_ip_axi_lite_module_inst_n_44),
        .\wdata_reg[0]_5 (u_uz_pu_con_ip_axi_lite_module_inst_n_45),
        .\wdata_reg[0]_6 (u_uz_pu_con_ip_axi_lite_module_inst_n_46),
        .\wdata_reg[0]_7 (u_uz_pu_con_ip_axi_lite_module_inst_n_47),
        .\wdata_reg[0]_8 (u_uz_pu_con_ip_axi_lite_module_inst_n_48),
        .\wdata_reg[0]_9 (u_uz_pu_con_ip_axi_lite_module_inst_n_49),
        .\wdata_reg[17]_0 (\wdata_reg[17] ),
        .wr_enb_1_reg_0(wr_enb_1_reg));
endmodule

(* ORIG_REF_NAME = "uz_pu_con_ip_axi_lite_module" *) 
module zusys_uz_pu_con_ip_0_1_uz_pu_con_ip_axi_lite_module
   (FSM_sequential_axi_lite_rstate_reg_0,
    AXI4_Lite_RDATA,
    soft_reset,
    CEB2,
    AXI4_Lite_ARADDR_8_sp_1,
    AXI4_Lite_ARADDR_11_sp_1,
    AXI4_Lite_ARADDR_7_sp_1,
    \AXI4_Lite_ARADDR[8]_0 ,
    AXI4_Lite_ARADDR_4_sp_1,
    \AXI4_Lite_ARADDR[8]_1 ,
    \AXI4_Lite_ARADDR[7]_0 ,
    \AXI4_Lite_ARADDR[8]_2 ,
    \AXI4_Lite_ARADDR[4]_0 ,
    \AXI4_Lite_ARADDR[8]_3 ,
    \AXI4_Lite_ARADDR[7]_1 ,
    \AXI4_Lite_ARADDR[8]_4 ,
    AXI4_Lite_ARADDR_3_sp_1,
    \AXI4_Lite_ARADDR[8]_5 ,
    \AXI4_Lite_ARADDR[7]_2 ,
    \AXI4_Lite_ARADDR[8]_6 ,
    \AXI4_Lite_ARADDR[3]_0 ,
    \AXI4_Lite_ARADDR[8]_7 ,
    \AXI4_Lite_ARADDR[7]_3 ,
    \AXI4_Lite_ARADDR[8]_8 ,
    \AXI4_Lite_ARADDR[4]_1 ,
    \AXI4_Lite_ARADDR[8]_9 ,
    \AXI4_Lite_ARADDR[7]_4 ,
    \AXI4_Lite_ARADDR[8]_10 ,
    \AXI4_Lite_ARADDR[4]_2 ,
    \AXI4_Lite_ARADDR[8]_11 ,
    \AXI4_Lite_ARADDR[7]_5 ,
    \AXI4_Lite_ARADDR[8]_12 ,
    AXI4_Lite_ARADDR_6_sp_1,
    \AXI4_Lite_ARADDR[8]_13 ,
    wr_enb_1_reg_0,
    Q,
    AXI4_Lite_AWREADY,
    AXI4_Lite_ARREADY,
    reset_in,
    \wdata_reg[0]_0 ,
    \wdata_reg[0]_1 ,
    \wdata_reg[0]_2 ,
    \wdata_reg[0]_3 ,
    \wdata_reg[0]_4 ,
    \wdata_reg[0]_5 ,
    \wdata_reg[0]_6 ,
    \wdata_reg[0]_7 ,
    \wdata_reg[0]_8 ,
    \wdata_reg[0]_9 ,
    \wdata_reg[0]_10 ,
    \wdata_reg[0]_11 ,
    \wdata_reg[0]_12 ,
    \wdata_reg[0]_13 ,
    \wdata_reg[0]_14 ,
    \wdata_reg[0]_15 ,
    \wdata_reg[0]_16 ,
    \wdata_reg[0]_17 ,
    \wdata_reg[0]_18 ,
    \wdata_reg[0]_19 ,
    \wdata_reg[0]_20 ,
    \wdata_reg[0]_21 ,
    \wdata_reg[0]_22 ,
    \wdata_reg[0]_23 ,
    \wdata_reg[0]_24 ,
    \wdata_reg[0]_25 ,
    \wdata_reg[0]_26 ,
    \wdata_reg[0]_27 ,
    \wdata_reg[0]_28 ,
    \wdata_reg[0]_29 ,
    \wdata_reg[0]_30 ,
    \wdata_reg[0]_31 ,
    \wdata_reg[17]_0 ,
    AXI4_Lite_ACLK,
    AXI4_Lite_ARADDR,
    AXI4_Lite_ARVALID,
    read_reg_ip_timestamp,
    AXI4_Lite_AWVALID,
    AXI4_Lite_WVALID,
    AXI4_Lite_RREADY,
    AXI4_Lite_ARESETN,
    IPCORE_RESETN,
    AXI4_Lite_BREADY,
    AXI4_Lite_WSTRB,
    \data_reg_AXI_pu_conv_in24_1_1_reg[0] ,
    \data_reg_AXI_pu_conv_in16_1_1_reg[0] ,
    \data_reg_AXI_pu_conv_in8_1_1_reg[0] ,
    \data_reg_AXI_pu_conv_in31_1_1_reg[0] ,
    \data_reg_AXI_pu_conv_in23_1_1_reg[0] ,
    \data_reg_AXI_pu_conv_in15_1_1_reg[0] ,
    \data_reg_AXI_pu_conv_in7_1_1_reg[0] ,
    \data_reg_AXI_pu_conv_in30_1_1_reg[0] ,
    \data_reg_AXI_pu_conv_in22_1_1_reg[0] ,
    \data_reg_AXI_pu_conv_in14_1_1_reg[0] ,
    \data_reg_AXI_pu_conv_in6_1_1_reg[0] ,
    \data_reg_AXI_pu_conv_in29_1_1_reg[0] ,
    \data_reg_AXI_pu_conv_in21_1_1_reg[0] ,
    \data_reg_AXI_pu_conv_in13_1_1_reg[0] ,
    \data_reg_AXI_pu_conv_in5_1_1_reg[0] ,
    \data_reg_AXI_pu_conv_in28_1_1_reg[0] ,
    \data_reg_AXI_pu_conv_in20_1_1_reg[0] ,
    \data_reg_AXI_pu_conv_in12_1_1_reg[0] ,
    \data_reg_AXI_pu_conv_in4_1_1_reg[0] ,
    \data_reg_AXI_pu_conv_in27_1_1_reg[0] ,
    \data_reg_AXI_pu_conv_in19_1_1_reg[0] ,
    \data_reg_AXI_pu_conv_in11_1_1_reg[0] ,
    \data_reg_AXI_pu_conv_in3_1_1_reg[0] ,
    \data_reg_AXI_pu_conv_in26_1_1_reg[0] ,
    \data_reg_AXI_pu_conv_in18_1_1_reg[0] ,
    \data_reg_AXI_pu_conv_in10_1_1_reg[0] ,
    \data_reg_AXI_pu_conv_in2_1_1_reg[0] ,
    \data_reg_AXI_pu_conv_in25_1_1_reg[0] ,
    \data_reg_AXI_pu_conv_in17_1_1_reg[0] ,
    \data_reg_AXI_pu_conv_in9_1_1_reg[0] ,
    \data_reg_AXI_pu_conv_in1_1_1_reg[0] ,
    OPMODE,
    AXI4_Lite_AWADDR,
    AXI4_Lite_WDATA);
  output FSM_sequential_axi_lite_rstate_reg_0;
  output [0:0]AXI4_Lite_RDATA;
  output soft_reset;
  output CEB2;
  output AXI4_Lite_ARADDR_8_sp_1;
  output AXI4_Lite_ARADDR_11_sp_1;
  output AXI4_Lite_ARADDR_7_sp_1;
  output \AXI4_Lite_ARADDR[8]_0 ;
  output AXI4_Lite_ARADDR_4_sp_1;
  output \AXI4_Lite_ARADDR[8]_1 ;
  output \AXI4_Lite_ARADDR[7]_0 ;
  output \AXI4_Lite_ARADDR[8]_2 ;
  output \AXI4_Lite_ARADDR[4]_0 ;
  output \AXI4_Lite_ARADDR[8]_3 ;
  output \AXI4_Lite_ARADDR[7]_1 ;
  output \AXI4_Lite_ARADDR[8]_4 ;
  output AXI4_Lite_ARADDR_3_sp_1;
  output \AXI4_Lite_ARADDR[8]_5 ;
  output \AXI4_Lite_ARADDR[7]_2 ;
  output \AXI4_Lite_ARADDR[8]_6 ;
  output \AXI4_Lite_ARADDR[3]_0 ;
  output \AXI4_Lite_ARADDR[8]_7 ;
  output \AXI4_Lite_ARADDR[7]_3 ;
  output \AXI4_Lite_ARADDR[8]_8 ;
  output \AXI4_Lite_ARADDR[4]_1 ;
  output \AXI4_Lite_ARADDR[8]_9 ;
  output \AXI4_Lite_ARADDR[7]_4 ;
  output \AXI4_Lite_ARADDR[8]_10 ;
  output \AXI4_Lite_ARADDR[4]_2 ;
  output \AXI4_Lite_ARADDR[8]_11 ;
  output \AXI4_Lite_ARADDR[7]_5 ;
  output \AXI4_Lite_ARADDR[8]_12 ;
  output AXI4_Lite_ARADDR_6_sp_1;
  output \AXI4_Lite_ARADDR[8]_13 ;
  output wr_enb_1_reg_0;
  output [1:0]Q;
  output AXI4_Lite_AWREADY;
  output AXI4_Lite_ARREADY;
  output reset_in;
  output \wdata_reg[0]_0 ;
  output \wdata_reg[0]_1 ;
  output \wdata_reg[0]_2 ;
  output \wdata_reg[0]_3 ;
  output \wdata_reg[0]_4 ;
  output \wdata_reg[0]_5 ;
  output \wdata_reg[0]_6 ;
  output \wdata_reg[0]_7 ;
  output \wdata_reg[0]_8 ;
  output \wdata_reg[0]_9 ;
  output \wdata_reg[0]_10 ;
  output \wdata_reg[0]_11 ;
  output \wdata_reg[0]_12 ;
  output \wdata_reg[0]_13 ;
  output \wdata_reg[0]_14 ;
  output \wdata_reg[0]_15 ;
  output \wdata_reg[0]_16 ;
  output \wdata_reg[0]_17 ;
  output \wdata_reg[0]_18 ;
  output \wdata_reg[0]_19 ;
  output \wdata_reg[0]_20 ;
  output \wdata_reg[0]_21 ;
  output \wdata_reg[0]_22 ;
  output \wdata_reg[0]_23 ;
  output \wdata_reg[0]_24 ;
  output \wdata_reg[0]_25 ;
  output \wdata_reg[0]_26 ;
  output \wdata_reg[0]_27 ;
  output \wdata_reg[0]_28 ;
  output \wdata_reg[0]_29 ;
  output \wdata_reg[0]_30 ;
  output \wdata_reg[0]_31 ;
  output [16:0]\wdata_reg[17]_0 ;
  input AXI4_Lite_ACLK;
  input [13:0]AXI4_Lite_ARADDR;
  input AXI4_Lite_ARVALID;
  input [0:0]read_reg_ip_timestamp;
  input AXI4_Lite_AWVALID;
  input AXI4_Lite_WVALID;
  input AXI4_Lite_RREADY;
  input AXI4_Lite_ARESETN;
  input IPCORE_RESETN;
  input AXI4_Lite_BREADY;
  input [3:0]AXI4_Lite_WSTRB;
  input [0:0]\data_reg_AXI_pu_conv_in24_1_1_reg[0] ;
  input [0:0]\data_reg_AXI_pu_conv_in16_1_1_reg[0] ;
  input [0:0]\data_reg_AXI_pu_conv_in8_1_1_reg[0] ;
  input [0:0]\data_reg_AXI_pu_conv_in31_1_1_reg[0] ;
  input [0:0]\data_reg_AXI_pu_conv_in23_1_1_reg[0] ;
  input [0:0]\data_reg_AXI_pu_conv_in15_1_1_reg[0] ;
  input [0:0]\data_reg_AXI_pu_conv_in7_1_1_reg[0] ;
  input [0:0]\data_reg_AXI_pu_conv_in30_1_1_reg[0] ;
  input [0:0]\data_reg_AXI_pu_conv_in22_1_1_reg[0] ;
  input [0:0]\data_reg_AXI_pu_conv_in14_1_1_reg[0] ;
  input [0:0]\data_reg_AXI_pu_conv_in6_1_1_reg[0] ;
  input [0:0]\data_reg_AXI_pu_conv_in29_1_1_reg[0] ;
  input [0:0]\data_reg_AXI_pu_conv_in21_1_1_reg[0] ;
  input [0:0]\data_reg_AXI_pu_conv_in13_1_1_reg[0] ;
  input [0:0]\data_reg_AXI_pu_conv_in5_1_1_reg[0] ;
  input [0:0]\data_reg_AXI_pu_conv_in28_1_1_reg[0] ;
  input [0:0]\data_reg_AXI_pu_conv_in20_1_1_reg[0] ;
  input [0:0]\data_reg_AXI_pu_conv_in12_1_1_reg[0] ;
  input [0:0]\data_reg_AXI_pu_conv_in4_1_1_reg[0] ;
  input [0:0]\data_reg_AXI_pu_conv_in27_1_1_reg[0] ;
  input [0:0]\data_reg_AXI_pu_conv_in19_1_1_reg[0] ;
  input [0:0]\data_reg_AXI_pu_conv_in11_1_1_reg[0] ;
  input [0:0]\data_reg_AXI_pu_conv_in3_1_1_reg[0] ;
  input [0:0]\data_reg_AXI_pu_conv_in26_1_1_reg[0] ;
  input [0:0]\data_reg_AXI_pu_conv_in18_1_1_reg[0] ;
  input [0:0]\data_reg_AXI_pu_conv_in10_1_1_reg[0] ;
  input [0:0]\data_reg_AXI_pu_conv_in2_1_1_reg[0] ;
  input [0:0]\data_reg_AXI_pu_conv_in25_1_1_reg[0] ;
  input [0:0]\data_reg_AXI_pu_conv_in17_1_1_reg[0] ;
  input [0:0]\data_reg_AXI_pu_conv_in9_1_1_reg[0] ;
  input [0:0]\data_reg_AXI_pu_conv_in1_1_1_reg[0] ;
  input [0:0]OPMODE;
  input [13:0]AXI4_Lite_AWADDR;
  input [17:0]AXI4_Lite_WDATA;

  wire AXI4_Lite_ACLK;
  wire [13:0]AXI4_Lite_ARADDR;
  wire \AXI4_Lite_ARADDR[3]_0 ;
  wire \AXI4_Lite_ARADDR[4]_0 ;
  wire \AXI4_Lite_ARADDR[4]_1 ;
  wire \AXI4_Lite_ARADDR[4]_2 ;
  wire \AXI4_Lite_ARADDR[7]_0 ;
  wire \AXI4_Lite_ARADDR[7]_1 ;
  wire \AXI4_Lite_ARADDR[7]_2 ;
  wire \AXI4_Lite_ARADDR[7]_3 ;
  wire \AXI4_Lite_ARADDR[7]_4 ;
  wire \AXI4_Lite_ARADDR[7]_5 ;
  wire \AXI4_Lite_ARADDR[8]_0 ;
  wire \AXI4_Lite_ARADDR[8]_1 ;
  wire \AXI4_Lite_ARADDR[8]_10 ;
  wire \AXI4_Lite_ARADDR[8]_11 ;
  wire \AXI4_Lite_ARADDR[8]_12 ;
  wire \AXI4_Lite_ARADDR[8]_13 ;
  wire \AXI4_Lite_ARADDR[8]_2 ;
  wire \AXI4_Lite_ARADDR[8]_3 ;
  wire \AXI4_Lite_ARADDR[8]_4 ;
  wire \AXI4_Lite_ARADDR[8]_5 ;
  wire \AXI4_Lite_ARADDR[8]_6 ;
  wire \AXI4_Lite_ARADDR[8]_7 ;
  wire \AXI4_Lite_ARADDR[8]_8 ;
  wire \AXI4_Lite_ARADDR[8]_9 ;
  wire AXI4_Lite_ARADDR_11_sn_1;
  wire AXI4_Lite_ARADDR_3_sn_1;
  wire AXI4_Lite_ARADDR_4_sn_1;
  wire AXI4_Lite_ARADDR_6_sn_1;
  wire AXI4_Lite_ARADDR_7_sn_1;
  wire AXI4_Lite_ARADDR_8_sn_1;
  wire AXI4_Lite_ARESETN;
  wire AXI4_Lite_ARREADY;
  wire AXI4_Lite_ARVALID;
  wire [13:0]AXI4_Lite_AWADDR;
  wire AXI4_Lite_AWREADY;
  wire AXI4_Lite_AWVALID;
  wire AXI4_Lite_BREADY;
  wire [0:0]AXI4_Lite_RDATA;
  wire \AXI4_Lite_RDATA_tmp[31]_i_1_n_0 ;
  wire \AXI4_Lite_RDATA_tmp[31]_i_2_n_0 ;
  wire \AXI4_Lite_RDATA_tmp[31]_i_3_n_0 ;
  wire \AXI4_Lite_RDATA_tmp[31]_i_4_n_0 ;
  wire \AXI4_Lite_RDATA_tmp[31]_i_5_n_0 ;
  wire \AXI4_Lite_RDATA_tmp[31]_i_6_n_0 ;
  wire AXI4_Lite_RREADY;
  wire [17:0]AXI4_Lite_WDATA;
  wire [3:0]AXI4_Lite_WSTRB;
  wire AXI4_Lite_WVALID;
  wire CEB2;
  wire \FSM_onehot_axi_lite_wstate_reg_n_0_[0] ;
  wire FSM_sequential_axi_lite_rstate_reg_0;
  wire IPCORE_RESETN;
  wire [0:0]OPMODE;
  wire [1:0]Q;
  wire aw_transfer;
  wire axi_lite_rstate_next;
  wire [2:0]axi_lite_wstate_next;
  wire \data_reg_AXI_pu_conv_in0_1_1[0]_i_2_n_0 ;
  wire [0:0]\data_reg_AXI_pu_conv_in10_1_1_reg[0] ;
  wire [0:0]\data_reg_AXI_pu_conv_in11_1_1_reg[0] ;
  wire [0:0]\data_reg_AXI_pu_conv_in12_1_1_reg[0] ;
  wire [0:0]\data_reg_AXI_pu_conv_in13_1_1_reg[0] ;
  wire [0:0]\data_reg_AXI_pu_conv_in14_1_1_reg[0] ;
  wire [0:0]\data_reg_AXI_pu_conv_in15_1_1_reg[0] ;
  wire \data_reg_AXI_pu_conv_in16_1_1[0]_i_2_n_0 ;
  wire [0:0]\data_reg_AXI_pu_conv_in16_1_1_reg[0] ;
  wire \data_reg_AXI_pu_conv_in17_1_1[0]_i_2_n_0 ;
  wire [0:0]\data_reg_AXI_pu_conv_in17_1_1_reg[0] ;
  wire \data_reg_AXI_pu_conv_in18_1_1[0]_i_2_n_0 ;
  wire [0:0]\data_reg_AXI_pu_conv_in18_1_1_reg[0] ;
  wire \data_reg_AXI_pu_conv_in19_1_1[0]_i_2_n_0 ;
  wire [0:0]\data_reg_AXI_pu_conv_in19_1_1_reg[0] ;
  wire \data_reg_AXI_pu_conv_in1_1_1[0]_i_2_n_0 ;
  wire \data_reg_AXI_pu_conv_in1_1_1[0]_i_3_n_0 ;
  wire [0:0]\data_reg_AXI_pu_conv_in1_1_1_reg[0] ;
  wire \data_reg_AXI_pu_conv_in20_1_1[0]_i_2_n_0 ;
  wire [0:0]\data_reg_AXI_pu_conv_in20_1_1_reg[0] ;
  wire \data_reg_AXI_pu_conv_in21_1_1[0]_i_2_n_0 ;
  wire [0:0]\data_reg_AXI_pu_conv_in21_1_1_reg[0] ;
  wire \data_reg_AXI_pu_conv_in22_1_1[0]_i_2_n_0 ;
  wire [0:0]\data_reg_AXI_pu_conv_in22_1_1_reg[0] ;
  wire \data_reg_AXI_pu_conv_in23_1_1[0]_i_2_n_0 ;
  wire [0:0]\data_reg_AXI_pu_conv_in23_1_1_reg[0] ;
  wire [0:0]\data_reg_AXI_pu_conv_in24_1_1_reg[0] ;
  wire [0:0]\data_reg_AXI_pu_conv_in25_1_1_reg[0] ;
  wire [0:0]\data_reg_AXI_pu_conv_in26_1_1_reg[0] ;
  wire [0:0]\data_reg_AXI_pu_conv_in27_1_1_reg[0] ;
  wire [0:0]\data_reg_AXI_pu_conv_in28_1_1_reg[0] ;
  wire [0:0]\data_reg_AXI_pu_conv_in29_1_1_reg[0] ;
  wire \data_reg_AXI_pu_conv_in2_1_1[0]_i_2_n_0 ;
  wire \data_reg_AXI_pu_conv_in2_1_1[0]_i_3_n_0 ;
  wire [0:0]\data_reg_AXI_pu_conv_in2_1_1_reg[0] ;
  wire [0:0]\data_reg_AXI_pu_conv_in30_1_1_reg[0] ;
  wire [0:0]\data_reg_AXI_pu_conv_in31_1_1_reg[0] ;
  wire \data_reg_AXI_pu_conv_in3_1_1[0]_i_2_n_0 ;
  wire [0:0]\data_reg_AXI_pu_conv_in3_1_1_reg[0] ;
  wire \data_reg_AXI_pu_conv_in4_1_1[0]_i_2_n_0 ;
  wire \data_reg_AXI_pu_conv_in4_1_1[0]_i_3_n_0 ;
  wire [0:0]\data_reg_AXI_pu_conv_in4_1_1_reg[0] ;
  wire \data_reg_AXI_pu_conv_in5_1_1[0]_i_2_n_0 ;
  wire [0:0]\data_reg_AXI_pu_conv_in5_1_1_reg[0] ;
  wire \data_reg_AXI_pu_conv_in6_1_1[0]_i_2_n_0 ;
  wire \data_reg_AXI_pu_conv_in6_1_1[0]_i_3_n_0 ;
  wire [0:0]\data_reg_AXI_pu_conv_in6_1_1_reg[0] ;
  wire \data_reg_AXI_pu_conv_in7_1_1[0]_i_2_n_0 ;
  wire [0:0]\data_reg_AXI_pu_conv_in7_1_1_reg[0] ;
  wire \data_reg_AXI_pu_conv_in8_1_1[0]_i_2_n_0 ;
  wire \data_reg_AXI_pu_conv_in8_1_1[0]_i_3_n_0 ;
  wire \data_reg_AXI_pu_conv_in8_1_1[0]_i_4_n_0 ;
  wire [0:0]\data_reg_AXI_pu_conv_in8_1_1_reg[0] ;
  wire [0:0]\data_reg_AXI_pu_conv_in9_1_1_reg[0] ;
  wire p_1_out__0_i_29_n_0;
  wire p_1_out__0_i_30_n_0;
  wire p_1_out__0_i_31_n_0;
  wire p_1_out__0_i_32_n_0;
  wire p_1_out__0_i_33_n_0;
  wire p_1_out__0_i_34_n_0;
  wire p_1_out__0_i_35_n_0;
  wire p_1_out__0_i_36_n_0;
  wire p_1_out__15_i_29_n_0;
  wire p_1_out__15_i_30_n_0;
  wire p_1_out__1_i_29_n_0;
  wire p_1_out__2_i_29_n_0;
  wire p_1_out__3_i_29_n_0;
  wire p_1_out__4_i_29_n_0;
  wire p_1_out__5_i_29_n_0;
  wire p_1_out__6_i_29_n_0;
  wire p_1_out_i_29_n_0;
  wire p_1_out_i_30_n_0;
  wire p_1_out_i_31_n_0;
  wire p_1_out_i_32_n_0;
  wire p_1_out_i_33_n_0;
  wire p_1_out_i_34_n_0;
  wire p_1_out_i_35_n_0;
  wire p_1_out_i_36_n_0;
  wire [0:0]read_reg_ip_timestamp;
  wire reset;
  wire reset_in;
  wire [13:0]sel0;
  wire soft_reset;
  wire soft_reset_i_1_n_0;
  wire soft_reset_i_2_n_0;
  wire soft_reset_i_3_n_0;
  wire soft_reset_i_4_n_0;
  wire top_wr_enb;
  wire w_transfer;
  wire w_transfer_and_wstrb;
  wire \wdata_reg[0]_0 ;
  wire \wdata_reg[0]_1 ;
  wire \wdata_reg[0]_10 ;
  wire \wdata_reg[0]_11 ;
  wire \wdata_reg[0]_12 ;
  wire \wdata_reg[0]_13 ;
  wire \wdata_reg[0]_14 ;
  wire \wdata_reg[0]_15 ;
  wire \wdata_reg[0]_16 ;
  wire \wdata_reg[0]_17 ;
  wire \wdata_reg[0]_18 ;
  wire \wdata_reg[0]_19 ;
  wire \wdata_reg[0]_2 ;
  wire \wdata_reg[0]_20 ;
  wire \wdata_reg[0]_21 ;
  wire \wdata_reg[0]_22 ;
  wire \wdata_reg[0]_23 ;
  wire \wdata_reg[0]_24 ;
  wire \wdata_reg[0]_25 ;
  wire \wdata_reg[0]_26 ;
  wire \wdata_reg[0]_27 ;
  wire \wdata_reg[0]_28 ;
  wire \wdata_reg[0]_29 ;
  wire \wdata_reg[0]_3 ;
  wire \wdata_reg[0]_30 ;
  wire \wdata_reg[0]_31 ;
  wire \wdata_reg[0]_4 ;
  wire \wdata_reg[0]_5 ;
  wire \wdata_reg[0]_6 ;
  wire \wdata_reg[0]_7 ;
  wire \wdata_reg[0]_8 ;
  wire \wdata_reg[0]_9 ;
  wire [16:0]\wdata_reg[17]_0 ;
  wire \wdata_reg_n_0_[0] ;
  wire wr_enb_1_reg_0;

  assign AXI4_Lite_ARADDR_11_sp_1 = AXI4_Lite_ARADDR_11_sn_1;
  assign AXI4_Lite_ARADDR_3_sp_1 = AXI4_Lite_ARADDR_3_sn_1;
  assign AXI4_Lite_ARADDR_4_sp_1 = AXI4_Lite_ARADDR_4_sn_1;
  assign AXI4_Lite_ARADDR_6_sp_1 = AXI4_Lite_ARADDR_6_sn_1;
  assign AXI4_Lite_ARADDR_7_sp_1 = AXI4_Lite_ARADDR_7_sn_1;
  assign AXI4_Lite_ARADDR_8_sp_1 = AXI4_Lite_ARADDR_8_sn_1;
  (* SOFT_HLUTNM = "soft_lutpair19" *) 
  LUT3 #(
    .INIT(8'h04)) 
    AXI4_Lite_ARREADY_INST_0
       (.I0(FSM_sequential_axi_lite_rstate_reg_0),
        .I1(\FSM_onehot_axi_lite_wstate_reg_n_0_[0] ),
        .I2(AXI4_Lite_AWVALID),
        .O(AXI4_Lite_ARREADY));
  (* SOFT_HLUTNM = "soft_lutpair20" *) 
  LUT2 #(
    .INIT(4'h2)) 
    AXI4_Lite_AWREADY_INST_0
       (.I0(\FSM_onehot_axi_lite_wstate_reg_n_0_[0] ),
        .I1(FSM_sequential_axi_lite_rstate_reg_0),
        .O(AXI4_Lite_AWREADY));
  LUT6 #(
    .INIT(64'hFFFFFF2F00000020)) 
    \AXI4_Lite_RDATA_tmp[31]_i_1 
       (.I0(p_1_out_i_29_n_0),
        .I1(\AXI4_Lite_RDATA_tmp[31]_i_2_n_0 ),
        .I2(AXI4_Lite_ARVALID),
        .I3(\AXI4_Lite_RDATA_tmp[31]_i_3_n_0 ),
        .I4(AXI4_Lite_AWVALID),
        .I5(AXI4_Lite_RDATA),
        .O(\AXI4_Lite_RDATA_tmp[31]_i_1_n_0 ));
  LUT6 #(
    .INIT(64'hFFFFFFFFFFFBFFFF)) 
    \AXI4_Lite_RDATA_tmp[31]_i_2 
       (.I0(p_1_out_i_33_n_0),
        .I1(\AXI4_Lite_RDATA_tmp[31]_i_4_n_0 ),
        .I2(\AXI4_Lite_RDATA_tmp[31]_i_5_n_0 ),
        .I3(\AXI4_Lite_RDATA_tmp[31]_i_6_n_0 ),
        .I4(read_reg_ip_timestamp),
        .I5(p_1_out_i_31_n_0),
        .O(\AXI4_Lite_RDATA_tmp[31]_i_2_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair21" *) 
  LUT2 #(
    .INIT(4'hB)) 
    \AXI4_Lite_RDATA_tmp[31]_i_3 
       (.I0(FSM_sequential_axi_lite_rstate_reg_0),
        .I1(\FSM_onehot_axi_lite_wstate_reg_n_0_[0] ),
        .O(\AXI4_Lite_RDATA_tmp[31]_i_3_n_0 ));
  LUT3 #(
    .INIT(8'hB8)) 
    \AXI4_Lite_RDATA_tmp[31]_i_4 
       (.I0(AXI4_Lite_ARADDR[1]),
        .I1(AXI4_Lite_ARVALID),
        .I2(sel0[1]),
        .O(\AXI4_Lite_RDATA_tmp[31]_i_4_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair13" *) 
  LUT5 #(
    .INIT(32'hFFFACCFA)) 
    \AXI4_Lite_RDATA_tmp[31]_i_5 
       (.I0(sel0[6]),
        .I1(AXI4_Lite_ARADDR[6]),
        .I2(sel0[7]),
        .I3(AXI4_Lite_ARVALID),
        .I4(AXI4_Lite_ARADDR[7]),
        .O(\AXI4_Lite_RDATA_tmp[31]_i_5_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair22" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \AXI4_Lite_RDATA_tmp[31]_i_6 
       (.I0(AXI4_Lite_ARADDR[2]),
        .I1(AXI4_Lite_ARVALID),
        .I2(sel0[2]),
        .O(\AXI4_Lite_RDATA_tmp[31]_i_6_n_0 ));
  FDRE \AXI4_Lite_RDATA_tmp_reg[31] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(\AXI4_Lite_RDATA_tmp[31]_i_1_n_0 ),
        .Q(AXI4_Lite_RDATA),
        .R(reset));
  (* SOFT_HLUTNM = "soft_lutpair21" *) 
  LUT5 #(
    .INIT(32'hFF8F8888)) 
    \FSM_onehot_axi_lite_wstate[0]_i_1 
       (.I0(Q[1]),
        .I1(AXI4_Lite_BREADY),
        .I2(AXI4_Lite_AWVALID),
        .I3(FSM_sequential_axi_lite_rstate_reg_0),
        .I4(\FSM_onehot_axi_lite_wstate_reg_n_0_[0] ),
        .O(axi_lite_wstate_next[0]));
  LUT1 #(
    .INIT(2'h1)) 
    \FSM_onehot_axi_lite_wstate[1]_i_1 
       (.I0(AXI4_Lite_ARESETN),
        .O(reset));
  (* SOFT_HLUTNM = "soft_lutpair19" *) 
  LUT5 #(
    .INIT(32'h40FF4040)) 
    \FSM_onehot_axi_lite_wstate[1]_i_2 
       (.I0(FSM_sequential_axi_lite_rstate_reg_0),
        .I1(\FSM_onehot_axi_lite_wstate_reg_n_0_[0] ),
        .I2(AXI4_Lite_AWVALID),
        .I3(AXI4_Lite_WVALID),
        .I4(Q[0]),
        .O(axi_lite_wstate_next[1]));
  LUT4 #(
    .INIT(16'h8F88)) 
    \FSM_onehot_axi_lite_wstate[2]_i_1 
       (.I0(Q[0]),
        .I1(AXI4_Lite_WVALID),
        .I2(AXI4_Lite_BREADY),
        .I3(Q[1]),
        .O(axi_lite_wstate_next[2]));
  (* FSM_ENCODED_STATES = "iSTATE:010,iSTATE0:100,iSTATE1:001" *) 
  FDSE #(
    .INIT(1'b1)) 
    \FSM_onehot_axi_lite_wstate_reg[0] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(axi_lite_wstate_next[0]),
        .Q(\FSM_onehot_axi_lite_wstate_reg_n_0_[0] ),
        .S(reset));
  (* FSM_ENCODED_STATES = "iSTATE:010,iSTATE0:100,iSTATE1:001" *) 
  FDRE #(
    .INIT(1'b0)) 
    \FSM_onehot_axi_lite_wstate_reg[1] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(axi_lite_wstate_next[1]),
        .Q(Q[0]),
        .R(reset));
  (* FSM_ENCODED_STATES = "iSTATE:010,iSTATE0:100,iSTATE1:001" *) 
  FDRE #(
    .INIT(1'b0)) 
    \FSM_onehot_axi_lite_wstate_reg[2] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(axi_lite_wstate_next[2]),
        .Q(Q[1]),
        .R(reset));
  (* SOFT_HLUTNM = "soft_lutpair20" *) 
  LUT5 #(
    .INIT(32'h55305500)) 
    FSM_sequential_axi_lite_rstate_i_1
       (.I0(AXI4_Lite_RREADY),
        .I1(AXI4_Lite_AWVALID),
        .I2(\FSM_onehot_axi_lite_wstate_reg_n_0_[0] ),
        .I3(FSM_sequential_axi_lite_rstate_reg_0),
        .I4(AXI4_Lite_ARVALID),
        .O(axi_lite_rstate_next));
  (* FSM_ENCODED_STATES = "iSTATE:0,iSTATE0:1" *) 
  FDRE FSM_sequential_axi_lite_rstate_reg
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(axi_lite_rstate_next),
        .Q(FSM_sequential_axi_lite_rstate_reg_0),
        .R(reset));
  LUT6 #(
    .INIT(64'hFFFFFFFB00000008)) 
    \data_reg_AXI_pu_conv_in0_1_1[0]_i_1 
       (.I0(\wdata_reg_n_0_[0] ),
        .I1(p_1_out_i_29_n_0),
        .I2(p_1_out_i_30_n_0),
        .I3(p_1_out_i_31_n_0),
        .I4(\data_reg_AXI_pu_conv_in0_1_1[0]_i_2_n_0 ),
        .I5(OPMODE),
        .O(\wdata_reg[0]_31 ));
  (* SOFT_HLUTNM = "soft_lutpair14" *) 
  LUT5 #(
    .INIT(32'hFBFFFBBB)) 
    \data_reg_AXI_pu_conv_in0_1_1[0]_i_2 
       (.I0(p_1_out_i_32_n_0),
        .I1(top_wr_enb),
        .I2(AXI4_Lite_ARADDR[12]),
        .I3(AXI4_Lite_ARVALID),
        .I4(sel0[12]),
        .O(\data_reg_AXI_pu_conv_in0_1_1[0]_i_2_n_0 ));
  LUT6 #(
    .INIT(64'hFFFFFFBF00000080)) 
    \data_reg_AXI_pu_conv_in10_1_1[0]_i_1 
       (.I0(\wdata_reg_n_0_[0] ),
        .I1(\data_reg_AXI_pu_conv_in2_1_1[0]_i_2_n_0 ),
        .I2(p_1_out__0_i_31_n_0),
        .I3(p_1_out__0_i_29_n_0),
        .I4(p_1_out__0_i_30_n_0),
        .I5(\data_reg_AXI_pu_conv_in10_1_1_reg[0] ),
        .O(\wdata_reg[0]_25 ));
  LUT6 #(
    .INIT(64'hFFFFFFBF00000080)) 
    \data_reg_AXI_pu_conv_in11_1_1[0]_i_1 
       (.I0(\wdata_reg_n_0_[0] ),
        .I1(\data_reg_AXI_pu_conv_in3_1_1[0]_i_2_n_0 ),
        .I2(p_1_out__0_i_31_n_0),
        .I3(p_1_out__0_i_29_n_0),
        .I4(p_1_out__0_i_30_n_0),
        .I5(\data_reg_AXI_pu_conv_in11_1_1_reg[0] ),
        .O(\wdata_reg[0]_21 ));
  LUT6 #(
    .INIT(64'hFFFFFFBF00000080)) 
    \data_reg_AXI_pu_conv_in12_1_1[0]_i_1 
       (.I0(\wdata_reg_n_0_[0] ),
        .I1(\data_reg_AXI_pu_conv_in4_1_1[0]_i_2_n_0 ),
        .I2(p_1_out__0_i_31_n_0),
        .I3(p_1_out__0_i_29_n_0),
        .I4(p_1_out__0_i_30_n_0),
        .I5(\data_reg_AXI_pu_conv_in12_1_1_reg[0] ),
        .O(\wdata_reg[0]_17 ));
  LUT6 #(
    .INIT(64'hFFFFFFBF00000080)) 
    \data_reg_AXI_pu_conv_in13_1_1[0]_i_1 
       (.I0(\wdata_reg_n_0_[0] ),
        .I1(\data_reg_AXI_pu_conv_in5_1_1[0]_i_2_n_0 ),
        .I2(p_1_out__0_i_31_n_0),
        .I3(p_1_out__0_i_29_n_0),
        .I4(p_1_out__0_i_30_n_0),
        .I5(\data_reg_AXI_pu_conv_in13_1_1_reg[0] ),
        .O(\wdata_reg[0]_13 ));
  LUT6 #(
    .INIT(64'hFFFFFFBF00000080)) 
    \data_reg_AXI_pu_conv_in14_1_1[0]_i_1 
       (.I0(\wdata_reg_n_0_[0] ),
        .I1(\data_reg_AXI_pu_conv_in6_1_1[0]_i_2_n_0 ),
        .I2(p_1_out__0_i_31_n_0),
        .I3(p_1_out__0_i_29_n_0),
        .I4(p_1_out__0_i_30_n_0),
        .I5(\data_reg_AXI_pu_conv_in14_1_1_reg[0] ),
        .O(\wdata_reg[0]_9 ));
  LUT6 #(
    .INIT(64'hFFFFFFBF00000080)) 
    \data_reg_AXI_pu_conv_in15_1_1[0]_i_1 
       (.I0(\wdata_reg_n_0_[0] ),
        .I1(\data_reg_AXI_pu_conv_in7_1_1[0]_i_2_n_0 ),
        .I2(p_1_out__0_i_31_n_0),
        .I3(p_1_out__0_i_29_n_0),
        .I4(p_1_out__0_i_30_n_0),
        .I5(\data_reg_AXI_pu_conv_in15_1_1_reg[0] ),
        .O(\wdata_reg[0]_5 ));
  LUT6 #(
    .INIT(64'hEFFFFFFF20000000)) 
    \data_reg_AXI_pu_conv_in16_1_1[0]_i_1 
       (.I0(\wdata_reg_n_0_[0] ),
        .I1(p_1_out__0_i_29_n_0),
        .I2(p_1_out__15_i_29_n_0),
        .I3(p_1_out__0_i_31_n_0),
        .I4(\data_reg_AXI_pu_conv_in16_1_1[0]_i_2_n_0 ),
        .I5(\data_reg_AXI_pu_conv_in16_1_1_reg[0] ),
        .O(\wdata_reg[0]_1 ));
  LUT6 #(
    .INIT(64'h0000000000470000)) 
    \data_reg_AXI_pu_conv_in16_1_1[0]_i_2 
       (.I0(AXI4_Lite_ARADDR[0]),
        .I1(AXI4_Lite_ARVALID),
        .I2(sel0[0]),
        .I3(p_1_out_i_32_n_0),
        .I4(\data_reg_AXI_pu_conv_in8_1_1[0]_i_4_n_0 ),
        .I5(p_1_out__0_i_36_n_0),
        .O(\data_reg_AXI_pu_conv_in16_1_1[0]_i_2_n_0 ));
  LUT6 #(
    .INIT(64'hEFFFFFFF20000000)) 
    \data_reg_AXI_pu_conv_in17_1_1[0]_i_1 
       (.I0(\wdata_reg_n_0_[0] ),
        .I1(p_1_out__0_i_29_n_0),
        .I2(p_1_out__15_i_29_n_0),
        .I3(p_1_out__0_i_31_n_0),
        .I4(\data_reg_AXI_pu_conv_in17_1_1[0]_i_2_n_0 ),
        .I5(\data_reg_AXI_pu_conv_in17_1_1_reg[0] ),
        .O(\wdata_reg[0]_28 ));
  LUT6 #(
    .INIT(64'h0000000045400000)) 
    \data_reg_AXI_pu_conv_in17_1_1[0]_i_2 
       (.I0(p_1_out_i_32_n_0),
        .I1(AXI4_Lite_ARADDR[0]),
        .I2(AXI4_Lite_ARVALID),
        .I3(sel0[0]),
        .I4(\data_reg_AXI_pu_conv_in8_1_1[0]_i_4_n_0 ),
        .I5(p_1_out__0_i_36_n_0),
        .O(\data_reg_AXI_pu_conv_in17_1_1[0]_i_2_n_0 ));
  LUT6 #(
    .INIT(64'hEFFFFFFF20000000)) 
    \data_reg_AXI_pu_conv_in18_1_1[0]_i_1 
       (.I0(\wdata_reg_n_0_[0] ),
        .I1(p_1_out__0_i_29_n_0),
        .I2(p_1_out__15_i_29_n_0),
        .I3(p_1_out__0_i_31_n_0),
        .I4(\data_reg_AXI_pu_conv_in18_1_1[0]_i_2_n_0 ),
        .I5(\data_reg_AXI_pu_conv_in18_1_1_reg[0] ),
        .O(\wdata_reg[0]_24 ));
  LUT6 #(
    .INIT(64'h00000000202A0000)) 
    \data_reg_AXI_pu_conv_in18_1_1[0]_i_2 
       (.I0(\data_reg_AXI_pu_conv_in2_1_1[0]_i_3_n_0 ),
        .I1(AXI4_Lite_ARADDR[0]),
        .I2(AXI4_Lite_ARVALID),
        .I3(sel0[0]),
        .I4(\data_reg_AXI_pu_conv_in8_1_1[0]_i_4_n_0 ),
        .I5(p_1_out__0_i_36_n_0),
        .O(\data_reg_AXI_pu_conv_in18_1_1[0]_i_2_n_0 ));
  LUT6 #(
    .INIT(64'hEFFFFFFF20000000)) 
    \data_reg_AXI_pu_conv_in19_1_1[0]_i_1 
       (.I0(\wdata_reg_n_0_[0] ),
        .I1(p_1_out__0_i_29_n_0),
        .I2(p_1_out__15_i_29_n_0),
        .I3(p_1_out__0_i_31_n_0),
        .I4(\data_reg_AXI_pu_conv_in19_1_1[0]_i_2_n_0 ),
        .I5(\data_reg_AXI_pu_conv_in19_1_1_reg[0] ),
        .O(\wdata_reg[0]_20 ));
  LUT6 #(
    .INIT(64'h000000008A800000)) 
    \data_reg_AXI_pu_conv_in19_1_1[0]_i_2 
       (.I0(\data_reg_AXI_pu_conv_in2_1_1[0]_i_3_n_0 ),
        .I1(AXI4_Lite_ARADDR[0]),
        .I2(AXI4_Lite_ARVALID),
        .I3(sel0[0]),
        .I4(\data_reg_AXI_pu_conv_in8_1_1[0]_i_4_n_0 ),
        .I5(p_1_out__0_i_36_n_0),
        .O(\data_reg_AXI_pu_conv_in19_1_1[0]_i_2_n_0 ));
  LUT6 #(
    .INIT(64'hEFFFFFFF20000000)) 
    \data_reg_AXI_pu_conv_in1_1_1[0]_i_1 
       (.I0(\wdata_reg_n_0_[0] ),
        .I1(p_1_out__0_i_29_n_0),
        .I2(p_1_out__0_i_30_n_0),
        .I3(p_1_out__0_i_31_n_0),
        .I4(\data_reg_AXI_pu_conv_in1_1_1[0]_i_2_n_0 ),
        .I5(\data_reg_AXI_pu_conv_in1_1_1_reg[0] ),
        .O(\wdata_reg[0]_30 ));
  LUT6 #(
    .INIT(64'h0000000045400000)) 
    \data_reg_AXI_pu_conv_in1_1_1[0]_i_2 
       (.I0(p_1_out_i_32_n_0),
        .I1(AXI4_Lite_ARADDR[0]),
        .I2(AXI4_Lite_ARVALID),
        .I3(sel0[0]),
        .I4(\data_reg_AXI_pu_conv_in1_1_1[0]_i_3_n_0 ),
        .I5(p_1_out__0_i_36_n_0),
        .O(\data_reg_AXI_pu_conv_in1_1_1[0]_i_2_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair17" *) 
  LUT5 #(
    .INIT(32'h00053305)) 
    \data_reg_AXI_pu_conv_in1_1_1[0]_i_3 
       (.I0(sel0[5]),
        .I1(AXI4_Lite_ARADDR[5]),
        .I2(sel0[4]),
        .I3(AXI4_Lite_ARVALID),
        .I4(AXI4_Lite_ARADDR[4]),
        .O(\data_reg_AXI_pu_conv_in1_1_1[0]_i_3_n_0 ));
  LUT6 #(
    .INIT(64'hEFFFFFFF20000000)) 
    \data_reg_AXI_pu_conv_in20_1_1[0]_i_1 
       (.I0(\wdata_reg_n_0_[0] ),
        .I1(p_1_out__0_i_29_n_0),
        .I2(p_1_out__15_i_29_n_0),
        .I3(p_1_out__0_i_31_n_0),
        .I4(\data_reg_AXI_pu_conv_in20_1_1[0]_i_2_n_0 ),
        .I5(\data_reg_AXI_pu_conv_in20_1_1_reg[0] ),
        .O(\wdata_reg[0]_16 ));
  LUT6 #(
    .INIT(64'h00000000202A0000)) 
    \data_reg_AXI_pu_conv_in20_1_1[0]_i_2 
       (.I0(\data_reg_AXI_pu_conv_in4_1_1[0]_i_3_n_0 ),
        .I1(AXI4_Lite_ARADDR[0]),
        .I2(AXI4_Lite_ARVALID),
        .I3(sel0[0]),
        .I4(\data_reg_AXI_pu_conv_in8_1_1[0]_i_4_n_0 ),
        .I5(p_1_out__0_i_36_n_0),
        .O(\data_reg_AXI_pu_conv_in20_1_1[0]_i_2_n_0 ));
  LUT6 #(
    .INIT(64'hEFFFFFFF20000000)) 
    \data_reg_AXI_pu_conv_in21_1_1[0]_i_1 
       (.I0(\wdata_reg_n_0_[0] ),
        .I1(p_1_out__0_i_29_n_0),
        .I2(p_1_out__15_i_29_n_0),
        .I3(p_1_out__0_i_31_n_0),
        .I4(\data_reg_AXI_pu_conv_in21_1_1[0]_i_2_n_0 ),
        .I5(\data_reg_AXI_pu_conv_in21_1_1_reg[0] ),
        .O(\wdata_reg[0]_12 ));
  LUT6 #(
    .INIT(64'h000000008A800000)) 
    \data_reg_AXI_pu_conv_in21_1_1[0]_i_2 
       (.I0(\data_reg_AXI_pu_conv_in4_1_1[0]_i_3_n_0 ),
        .I1(AXI4_Lite_ARADDR[0]),
        .I2(AXI4_Lite_ARVALID),
        .I3(sel0[0]),
        .I4(\data_reg_AXI_pu_conv_in8_1_1[0]_i_4_n_0 ),
        .I5(p_1_out__0_i_36_n_0),
        .O(\data_reg_AXI_pu_conv_in21_1_1[0]_i_2_n_0 ));
  LUT6 #(
    .INIT(64'hEFFFFFFF20000000)) 
    \data_reg_AXI_pu_conv_in22_1_1[0]_i_1 
       (.I0(\wdata_reg_n_0_[0] ),
        .I1(p_1_out__0_i_29_n_0),
        .I2(p_1_out__15_i_29_n_0),
        .I3(p_1_out__0_i_31_n_0),
        .I4(\data_reg_AXI_pu_conv_in22_1_1[0]_i_2_n_0 ),
        .I5(\data_reg_AXI_pu_conv_in22_1_1_reg[0] ),
        .O(\wdata_reg[0]_8 ));
  LUT6 #(
    .INIT(64'h00000000202A0000)) 
    \data_reg_AXI_pu_conv_in22_1_1[0]_i_2 
       (.I0(\data_reg_AXI_pu_conv_in6_1_1[0]_i_3_n_0 ),
        .I1(AXI4_Lite_ARADDR[0]),
        .I2(AXI4_Lite_ARVALID),
        .I3(sel0[0]),
        .I4(\data_reg_AXI_pu_conv_in8_1_1[0]_i_4_n_0 ),
        .I5(p_1_out__0_i_36_n_0),
        .O(\data_reg_AXI_pu_conv_in22_1_1[0]_i_2_n_0 ));
  LUT6 #(
    .INIT(64'hEFFFFFFF20000000)) 
    \data_reg_AXI_pu_conv_in23_1_1[0]_i_1 
       (.I0(\wdata_reg_n_0_[0] ),
        .I1(p_1_out__0_i_29_n_0),
        .I2(p_1_out__15_i_29_n_0),
        .I3(p_1_out__0_i_31_n_0),
        .I4(\data_reg_AXI_pu_conv_in23_1_1[0]_i_2_n_0 ),
        .I5(\data_reg_AXI_pu_conv_in23_1_1_reg[0] ),
        .O(\wdata_reg[0]_4 ));
  LUT6 #(
    .INIT(64'h000000008A800000)) 
    \data_reg_AXI_pu_conv_in23_1_1[0]_i_2 
       (.I0(\data_reg_AXI_pu_conv_in6_1_1[0]_i_3_n_0 ),
        .I1(AXI4_Lite_ARADDR[0]),
        .I2(AXI4_Lite_ARVALID),
        .I3(sel0[0]),
        .I4(\data_reg_AXI_pu_conv_in8_1_1[0]_i_4_n_0 ),
        .I5(p_1_out__0_i_36_n_0),
        .O(\data_reg_AXI_pu_conv_in23_1_1[0]_i_2_n_0 ));
  LUT6 #(
    .INIT(64'hFFFFFFBF00000080)) 
    \data_reg_AXI_pu_conv_in24_1_1[0]_i_1 
       (.I0(\wdata_reg_n_0_[0] ),
        .I1(\data_reg_AXI_pu_conv_in16_1_1[0]_i_2_n_0 ),
        .I2(p_1_out__0_i_31_n_0),
        .I3(p_1_out__0_i_29_n_0),
        .I4(p_1_out__15_i_29_n_0),
        .I5(\data_reg_AXI_pu_conv_in24_1_1_reg[0] ),
        .O(\wdata_reg[0]_0 ));
  LUT6 #(
    .INIT(64'hFFFFFFBF00000080)) 
    \data_reg_AXI_pu_conv_in25_1_1[0]_i_1 
       (.I0(\wdata_reg_n_0_[0] ),
        .I1(\data_reg_AXI_pu_conv_in17_1_1[0]_i_2_n_0 ),
        .I2(p_1_out__0_i_31_n_0),
        .I3(p_1_out__0_i_29_n_0),
        .I4(p_1_out__15_i_29_n_0),
        .I5(\data_reg_AXI_pu_conv_in25_1_1_reg[0] ),
        .O(\wdata_reg[0]_27 ));
  LUT6 #(
    .INIT(64'hFFFFFFBF00000080)) 
    \data_reg_AXI_pu_conv_in26_1_1[0]_i_1 
       (.I0(\wdata_reg_n_0_[0] ),
        .I1(\data_reg_AXI_pu_conv_in18_1_1[0]_i_2_n_0 ),
        .I2(p_1_out__0_i_31_n_0),
        .I3(p_1_out__0_i_29_n_0),
        .I4(p_1_out__15_i_29_n_0),
        .I5(\data_reg_AXI_pu_conv_in26_1_1_reg[0] ),
        .O(\wdata_reg[0]_23 ));
  LUT6 #(
    .INIT(64'hFFFFFFBF00000080)) 
    \data_reg_AXI_pu_conv_in27_1_1[0]_i_1 
       (.I0(\wdata_reg_n_0_[0] ),
        .I1(\data_reg_AXI_pu_conv_in19_1_1[0]_i_2_n_0 ),
        .I2(p_1_out__0_i_31_n_0),
        .I3(p_1_out__0_i_29_n_0),
        .I4(p_1_out__15_i_29_n_0),
        .I5(\data_reg_AXI_pu_conv_in27_1_1_reg[0] ),
        .O(\wdata_reg[0]_19 ));
  LUT6 #(
    .INIT(64'hFFFFFFBF00000080)) 
    \data_reg_AXI_pu_conv_in28_1_1[0]_i_1 
       (.I0(\wdata_reg_n_0_[0] ),
        .I1(\data_reg_AXI_pu_conv_in20_1_1[0]_i_2_n_0 ),
        .I2(p_1_out__0_i_31_n_0),
        .I3(p_1_out__0_i_29_n_0),
        .I4(p_1_out__15_i_29_n_0),
        .I5(\data_reg_AXI_pu_conv_in28_1_1_reg[0] ),
        .O(\wdata_reg[0]_15 ));
  LUT6 #(
    .INIT(64'hFFFFFFBF00000080)) 
    \data_reg_AXI_pu_conv_in29_1_1[0]_i_1 
       (.I0(\wdata_reg_n_0_[0] ),
        .I1(\data_reg_AXI_pu_conv_in21_1_1[0]_i_2_n_0 ),
        .I2(p_1_out__0_i_31_n_0),
        .I3(p_1_out__0_i_29_n_0),
        .I4(p_1_out__15_i_29_n_0),
        .I5(\data_reg_AXI_pu_conv_in29_1_1_reg[0] ),
        .O(\wdata_reg[0]_11 ));
  LUT6 #(
    .INIT(64'hEFFFFFFF20000000)) 
    \data_reg_AXI_pu_conv_in2_1_1[0]_i_1 
       (.I0(\wdata_reg_n_0_[0] ),
        .I1(p_1_out__0_i_29_n_0),
        .I2(p_1_out__0_i_30_n_0),
        .I3(p_1_out__0_i_31_n_0),
        .I4(\data_reg_AXI_pu_conv_in2_1_1[0]_i_2_n_0 ),
        .I5(\data_reg_AXI_pu_conv_in2_1_1_reg[0] ),
        .O(\wdata_reg[0]_26 ));
  LUT6 #(
    .INIT(64'h0020000000202020)) 
    \data_reg_AXI_pu_conv_in2_1_1[0]_i_2 
       (.I0(\data_reg_AXI_pu_conv_in1_1_1[0]_i_3_n_0 ),
        .I1(p_1_out__0_i_36_n_0),
        .I2(\data_reg_AXI_pu_conv_in2_1_1[0]_i_3_n_0 ),
        .I3(AXI4_Lite_ARADDR[0]),
        .I4(AXI4_Lite_ARVALID),
        .I5(sel0[0]),
        .O(\data_reg_AXI_pu_conv_in2_1_1[0]_i_2_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair16" *) 
  LUT5 #(
    .INIT(32'h000ACC0A)) 
    \data_reg_AXI_pu_conv_in2_1_1[0]_i_3 
       (.I0(sel0[1]),
        .I1(AXI4_Lite_ARADDR[1]),
        .I2(sel0[2]),
        .I3(AXI4_Lite_ARVALID),
        .I4(AXI4_Lite_ARADDR[2]),
        .O(\data_reg_AXI_pu_conv_in2_1_1[0]_i_3_n_0 ));
  LUT6 #(
    .INIT(64'hFFFFFFBF00000080)) 
    \data_reg_AXI_pu_conv_in30_1_1[0]_i_1 
       (.I0(\wdata_reg_n_0_[0] ),
        .I1(\data_reg_AXI_pu_conv_in22_1_1[0]_i_2_n_0 ),
        .I2(p_1_out__0_i_31_n_0),
        .I3(p_1_out__0_i_29_n_0),
        .I4(p_1_out__15_i_29_n_0),
        .I5(\data_reg_AXI_pu_conv_in30_1_1_reg[0] ),
        .O(\wdata_reg[0]_7 ));
  LUT6 #(
    .INIT(64'hFFFFFFBF00000080)) 
    \data_reg_AXI_pu_conv_in31_1_1[0]_i_1 
       (.I0(\wdata_reg_n_0_[0] ),
        .I1(\data_reg_AXI_pu_conv_in23_1_1[0]_i_2_n_0 ),
        .I2(p_1_out__0_i_31_n_0),
        .I3(p_1_out__0_i_29_n_0),
        .I4(p_1_out__15_i_29_n_0),
        .I5(\data_reg_AXI_pu_conv_in31_1_1_reg[0] ),
        .O(\wdata_reg[0]_3 ));
  LUT6 #(
    .INIT(64'hEFFFFFFF20000000)) 
    \data_reg_AXI_pu_conv_in3_1_1[0]_i_1 
       (.I0(\wdata_reg_n_0_[0] ),
        .I1(p_1_out__0_i_29_n_0),
        .I2(p_1_out__0_i_30_n_0),
        .I3(p_1_out__0_i_31_n_0),
        .I4(\data_reg_AXI_pu_conv_in3_1_1[0]_i_2_n_0 ),
        .I5(\data_reg_AXI_pu_conv_in3_1_1_reg[0] ),
        .O(\wdata_reg[0]_22 ));
  LUT6 #(
    .INIT(64'h2000202020000000)) 
    \data_reg_AXI_pu_conv_in3_1_1[0]_i_2 
       (.I0(\data_reg_AXI_pu_conv_in1_1_1[0]_i_3_n_0 ),
        .I1(p_1_out__0_i_36_n_0),
        .I2(\data_reg_AXI_pu_conv_in2_1_1[0]_i_3_n_0 ),
        .I3(AXI4_Lite_ARADDR[0]),
        .I4(AXI4_Lite_ARVALID),
        .I5(sel0[0]),
        .O(\data_reg_AXI_pu_conv_in3_1_1[0]_i_2_n_0 ));
  LUT6 #(
    .INIT(64'hEFFFFFFF20000000)) 
    \data_reg_AXI_pu_conv_in4_1_1[0]_i_1 
       (.I0(\wdata_reg_n_0_[0] ),
        .I1(p_1_out__0_i_29_n_0),
        .I2(p_1_out__0_i_30_n_0),
        .I3(p_1_out__0_i_31_n_0),
        .I4(\data_reg_AXI_pu_conv_in4_1_1[0]_i_2_n_0 ),
        .I5(\data_reg_AXI_pu_conv_in4_1_1_reg[0] ),
        .O(\wdata_reg[0]_18 ));
  LUT6 #(
    .INIT(64'h0020000000202020)) 
    \data_reg_AXI_pu_conv_in4_1_1[0]_i_2 
       (.I0(\data_reg_AXI_pu_conv_in1_1_1[0]_i_3_n_0 ),
        .I1(p_1_out__0_i_36_n_0),
        .I2(\data_reg_AXI_pu_conv_in4_1_1[0]_i_3_n_0 ),
        .I3(AXI4_Lite_ARADDR[0]),
        .I4(AXI4_Lite_ARVALID),
        .I5(sel0[0]),
        .O(\data_reg_AXI_pu_conv_in4_1_1[0]_i_2_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair15" *) 
  LUT5 #(
    .INIT(32'h000ACC0A)) 
    \data_reg_AXI_pu_conv_in4_1_1[0]_i_3 
       (.I0(sel0[2]),
        .I1(AXI4_Lite_ARADDR[2]),
        .I2(sel0[1]),
        .I3(AXI4_Lite_ARVALID),
        .I4(AXI4_Lite_ARADDR[1]),
        .O(\data_reg_AXI_pu_conv_in4_1_1[0]_i_3_n_0 ));
  LUT6 #(
    .INIT(64'hEFFFFFFF20000000)) 
    \data_reg_AXI_pu_conv_in5_1_1[0]_i_1 
       (.I0(\wdata_reg_n_0_[0] ),
        .I1(p_1_out__0_i_29_n_0),
        .I2(p_1_out__0_i_30_n_0),
        .I3(p_1_out__0_i_31_n_0),
        .I4(\data_reg_AXI_pu_conv_in5_1_1[0]_i_2_n_0 ),
        .I5(\data_reg_AXI_pu_conv_in5_1_1_reg[0] ),
        .O(\wdata_reg[0]_14 ));
  LUT6 #(
    .INIT(64'h2000202020000000)) 
    \data_reg_AXI_pu_conv_in5_1_1[0]_i_2 
       (.I0(\data_reg_AXI_pu_conv_in1_1_1[0]_i_3_n_0 ),
        .I1(p_1_out__0_i_36_n_0),
        .I2(\data_reg_AXI_pu_conv_in4_1_1[0]_i_3_n_0 ),
        .I3(AXI4_Lite_ARADDR[0]),
        .I4(AXI4_Lite_ARVALID),
        .I5(sel0[0]),
        .O(\data_reg_AXI_pu_conv_in5_1_1[0]_i_2_n_0 ));
  LUT6 #(
    .INIT(64'hEFFFFFFF20000000)) 
    \data_reg_AXI_pu_conv_in6_1_1[0]_i_1 
       (.I0(\wdata_reg_n_0_[0] ),
        .I1(p_1_out__0_i_29_n_0),
        .I2(p_1_out__0_i_30_n_0),
        .I3(p_1_out__0_i_31_n_0),
        .I4(\data_reg_AXI_pu_conv_in6_1_1[0]_i_2_n_0 ),
        .I5(\data_reg_AXI_pu_conv_in6_1_1_reg[0] ),
        .O(\wdata_reg[0]_10 ));
  LUT6 #(
    .INIT(64'h0020000000202020)) 
    \data_reg_AXI_pu_conv_in6_1_1[0]_i_2 
       (.I0(\data_reg_AXI_pu_conv_in1_1_1[0]_i_3_n_0 ),
        .I1(p_1_out__0_i_36_n_0),
        .I2(\data_reg_AXI_pu_conv_in6_1_1[0]_i_3_n_0 ),
        .I3(AXI4_Lite_ARADDR[0]),
        .I4(AXI4_Lite_ARVALID),
        .I5(sel0[0]),
        .O(\data_reg_AXI_pu_conv_in6_1_1[0]_i_2_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair15" *) 
  LUT5 #(
    .INIT(32'hCCA000A0)) 
    \data_reg_AXI_pu_conv_in6_1_1[0]_i_3 
       (.I0(sel0[1]),
        .I1(AXI4_Lite_ARADDR[1]),
        .I2(sel0[2]),
        .I3(AXI4_Lite_ARVALID),
        .I4(AXI4_Lite_ARADDR[2]),
        .O(\data_reg_AXI_pu_conv_in6_1_1[0]_i_3_n_0 ));
  LUT6 #(
    .INIT(64'hEFFFFFFF20000000)) 
    \data_reg_AXI_pu_conv_in7_1_1[0]_i_1 
       (.I0(\wdata_reg_n_0_[0] ),
        .I1(p_1_out__0_i_29_n_0),
        .I2(p_1_out__0_i_30_n_0),
        .I3(p_1_out__0_i_31_n_0),
        .I4(\data_reg_AXI_pu_conv_in7_1_1[0]_i_2_n_0 ),
        .I5(\data_reg_AXI_pu_conv_in7_1_1_reg[0] ),
        .O(\wdata_reg[0]_6 ));
  LUT6 #(
    .INIT(64'h2000202020000000)) 
    \data_reg_AXI_pu_conv_in7_1_1[0]_i_2 
       (.I0(\data_reg_AXI_pu_conv_in1_1_1[0]_i_3_n_0 ),
        .I1(p_1_out__0_i_36_n_0),
        .I2(\data_reg_AXI_pu_conv_in6_1_1[0]_i_3_n_0 ),
        .I3(AXI4_Lite_ARADDR[0]),
        .I4(AXI4_Lite_ARVALID),
        .I5(sel0[0]),
        .O(\data_reg_AXI_pu_conv_in7_1_1[0]_i_2_n_0 ));
  LUT6 #(
    .INIT(64'hFFFFFFFB00000008)) 
    \data_reg_AXI_pu_conv_in8_1_1[0]_i_1 
       (.I0(\wdata_reg_n_0_[0] ),
        .I1(p_1_out__0_i_31_n_0),
        .I2(\data_reg_AXI_pu_conv_in8_1_1[0]_i_2_n_0 ),
        .I3(\data_reg_AXI_pu_conv_in8_1_1[0]_i_3_n_0 ),
        .I4(p_1_out__0_i_32_n_0),
        .I5(\data_reg_AXI_pu_conv_in8_1_1_reg[0] ),
        .O(\wdata_reg[0]_2 ));
  LUT6 #(
    .INIT(64'hFFFFFFFF4700FFFF)) 
    \data_reg_AXI_pu_conv_in8_1_1[0]_i_2 
       (.I0(AXI4_Lite_ARADDR[8]),
        .I1(AXI4_Lite_ARVALID),
        .I2(sel0[8]),
        .I3(p_1_out_i_30_n_0),
        .I4(p_1_out_i_36_n_0),
        .I5(\data_reg_AXI_pu_conv_in8_1_1[0]_i_4_n_0 ),
        .O(\data_reg_AXI_pu_conv_in8_1_1[0]_i_2_n_0 ));
  LUT6 #(
    .INIT(64'hFFFFFFFFFFBBFCB8)) 
    \data_reg_AXI_pu_conv_in8_1_1[0]_i_3 
       (.I0(AXI4_Lite_ARADDR[2]),
        .I1(AXI4_Lite_ARVALID),
        .I2(sel0[2]),
        .I3(AXI4_Lite_ARADDR[1]),
        .I4(sel0[1]),
        .I5(p_1_out__0_i_33_n_0),
        .O(\data_reg_AXI_pu_conv_in8_1_1[0]_i_3_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair17" *) 
  LUT5 #(
    .INIT(32'h000ACC0A)) 
    \data_reg_AXI_pu_conv_in8_1_1[0]_i_4 
       (.I0(sel0[4]),
        .I1(AXI4_Lite_ARADDR[4]),
        .I2(sel0[5]),
        .I3(AXI4_Lite_ARVALID),
        .I4(AXI4_Lite_ARADDR[5]),
        .O(\data_reg_AXI_pu_conv_in8_1_1[0]_i_4_n_0 ));
  LUT6 #(
    .INIT(64'hFFFFFFBF00000080)) 
    \data_reg_AXI_pu_conv_in9_1_1[0]_i_1 
       (.I0(\wdata_reg_n_0_[0] ),
        .I1(\data_reg_AXI_pu_conv_in1_1_1[0]_i_2_n_0 ),
        .I2(p_1_out__0_i_31_n_0),
        .I3(p_1_out__0_i_29_n_0),
        .I4(p_1_out__0_i_30_n_0),
        .I5(\data_reg_AXI_pu_conv_in9_1_1_reg[0] ),
        .O(\wdata_reg[0]_29 ));
  LUT6 #(
    .INIT(64'h0000000000400000)) 
    p_1_out__0_i_1
       (.I0(p_1_out__0_i_29_n_0),
        .I1(p_1_out__0_i_30_n_0),
        .I2(p_1_out__0_i_31_n_0),
        .I3(p_1_out__0_i_32_n_0),
        .I4(p_1_out__0_i_33_n_0),
        .I5(p_1_out_i_32_n_0),
        .O(\AXI4_Lite_ARADDR[8]_13 ));
  LUT6 #(
    .INIT(64'h00000000FF77CF47)) 
    p_1_out__0_i_29
       (.I0(AXI4_Lite_ARADDR[6]),
        .I1(AXI4_Lite_ARVALID),
        .I2(sel0[6]),
        .I3(AXI4_Lite_ARADDR[7]),
        .I4(sel0[7]),
        .I5(p_1_out__0_i_34_n_0),
        .O(p_1_out__0_i_29_n_0));
  LUT6 #(
    .INIT(64'h47034400FFFFFFFF)) 
    p_1_out__0_i_30
       (.I0(AXI4_Lite_ARADDR[5]),
        .I1(AXI4_Lite_ARVALID),
        .I2(sel0[5]),
        .I3(AXI4_Lite_ARADDR[4]),
        .I4(sel0[4]),
        .I5(p_1_out_i_36_n_0),
        .O(p_1_out__0_i_30_n_0));
  LUT6 #(
    .INIT(64'h0000000000004700)) 
    p_1_out__0_i_31
       (.I0(AXI4_Lite_ARADDR[9]),
        .I1(AXI4_Lite_ARVALID),
        .I2(sel0[9]),
        .I3(p_1_out_i_34_n_0),
        .I4(p_1_out__0_i_35_n_0),
        .I5(p_1_out_i_33_n_0),
        .O(p_1_out__0_i_31_n_0));
  LUT6 #(
    .INIT(64'hFFFFEFEFFFFAEFEA)) 
    p_1_out__0_i_32
       (.I0(p_1_out__0_i_36_n_0),
        .I1(AXI4_Lite_ARADDR[4]),
        .I2(AXI4_Lite_ARVALID),
        .I3(sel0[4]),
        .I4(AXI4_Lite_ARADDR[5]),
        .I5(sel0[5]),
        .O(p_1_out__0_i_32_n_0));
  (* SOFT_HLUTNM = "soft_lutpair22" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    p_1_out__0_i_33
       (.I0(AXI4_Lite_ARADDR[0]),
        .I1(AXI4_Lite_ARVALID),
        .I2(sel0[0]),
        .O(p_1_out__0_i_33_n_0));
  (* SOFT_HLUTNM = "soft_lutpair18" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    p_1_out__0_i_34
       (.I0(AXI4_Lite_ARADDR[8]),
        .I1(AXI4_Lite_ARVALID),
        .I2(sel0[8]),
        .O(p_1_out__0_i_34_n_0));
  (* SOFT_HLUTNM = "soft_lutpair12" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    p_1_out__0_i_35
       (.I0(AXI4_Lite_ARADDR[13]),
        .I1(AXI4_Lite_ARVALID),
        .I2(sel0[13]),
        .O(p_1_out__0_i_35_n_0));
  LUT6 #(
    .INIT(64'hFFBBFCB8FFFFFFFF)) 
    p_1_out__0_i_36
       (.I0(AXI4_Lite_ARADDR[7]),
        .I1(AXI4_Lite_ARVALID),
        .I2(sel0[7]),
        .I3(AXI4_Lite_ARADDR[8]),
        .I4(sel0[8]),
        .I5(top_wr_enb),
        .O(p_1_out__0_i_36_n_0));
  (* SOFT_HLUTNM = "soft_lutpair9" *) 
  LUT5 #(
    .INIT(32'h00000010)) 
    p_1_out__10_i_1
       (.I0(p_1_out__2_i_29_n_0),
        .I1(p_1_out__0_i_32_n_0),
        .I2(p_1_out__0_i_31_n_0),
        .I3(p_1_out__0_i_29_n_0),
        .I4(p_1_out__0_i_30_n_0),
        .O(\AXI4_Lite_ARADDR[4]_1 ));
  (* SOFT_HLUTNM = "soft_lutpair7" *) 
  LUT5 #(
    .INIT(32'h00000010)) 
    p_1_out__11_i_1
       (.I0(p_1_out__3_i_29_n_0),
        .I1(p_1_out__0_i_32_n_0),
        .I2(p_1_out__0_i_31_n_0),
        .I3(p_1_out__0_i_29_n_0),
        .I4(p_1_out__0_i_30_n_0),
        .O(\AXI4_Lite_ARADDR[3]_0 ));
  (* SOFT_HLUTNM = "soft_lutpair5" *) 
  LUT5 #(
    .INIT(32'h00000010)) 
    p_1_out__12_i_1
       (.I0(p_1_out__4_i_29_n_0),
        .I1(p_1_out__0_i_32_n_0),
        .I2(p_1_out__0_i_31_n_0),
        .I3(p_1_out__0_i_29_n_0),
        .I4(p_1_out__0_i_30_n_0),
        .O(AXI4_Lite_ARADDR_3_sn_1));
  (* SOFT_HLUTNM = "soft_lutpair3" *) 
  LUT5 #(
    .INIT(32'h00000010)) 
    p_1_out__13_i_1
       (.I0(p_1_out__5_i_29_n_0),
        .I1(p_1_out__0_i_32_n_0),
        .I2(p_1_out__0_i_31_n_0),
        .I3(p_1_out__0_i_29_n_0),
        .I4(p_1_out__0_i_30_n_0),
        .O(\AXI4_Lite_ARADDR[4]_0 ));
  (* SOFT_HLUTNM = "soft_lutpair1" *) 
  LUT5 #(
    .INIT(32'h00000010)) 
    p_1_out__14_i_1
       (.I0(p_1_out__6_i_29_n_0),
        .I1(p_1_out__0_i_32_n_0),
        .I2(p_1_out__0_i_31_n_0),
        .I3(p_1_out__0_i_29_n_0),
        .I4(p_1_out__0_i_30_n_0),
        .O(AXI4_Lite_ARADDR_4_sn_1));
  LUT6 #(
    .INIT(64'h0000000000000040)) 
    p_1_out__15_i_1
       (.I0(p_1_out__0_i_29_n_0),
        .I1(p_1_out__15_i_29_n_0),
        .I2(p_1_out__0_i_31_n_0),
        .I3(p_1_out__15_i_30_n_0),
        .I4(p_1_out_i_32_n_0),
        .I5(p_1_out__0_i_33_n_0),
        .O(AXI4_Lite_ARADDR_8_sn_1));
  LUT6 #(
    .INIT(64'h00440347FFFFFFFF)) 
    p_1_out__15_i_29
       (.I0(AXI4_Lite_ARADDR[4]),
        .I1(AXI4_Lite_ARVALID),
        .I2(sel0[4]),
        .I3(AXI4_Lite_ARADDR[5]),
        .I4(sel0[5]),
        .I5(p_1_out_i_36_n_0),
        .O(p_1_out__15_i_29_n_0));
  LUT6 #(
    .INIT(64'hEFEAFFFAEFEFFFFF)) 
    p_1_out__15_i_30
       (.I0(p_1_out__0_i_36_n_0),
        .I1(AXI4_Lite_ARADDR[5]),
        .I2(AXI4_Lite_ARVALID),
        .I3(sel0[5]),
        .I4(AXI4_Lite_ARADDR[4]),
        .I5(sel0[4]),
        .O(p_1_out__15_i_30_n_0));
  LUT6 #(
    .INIT(64'h0000000000400000)) 
    p_1_out__16_i_1
       (.I0(p_1_out__0_i_29_n_0),
        .I1(p_1_out__15_i_29_n_0),
        .I2(p_1_out__0_i_31_n_0),
        .I3(p_1_out__15_i_30_n_0),
        .I4(p_1_out__0_i_33_n_0),
        .I5(p_1_out_i_32_n_0),
        .O(\AXI4_Lite_ARADDR[8]_12 ));
  (* SOFT_HLUTNM = "soft_lutpair10" *) 
  LUT5 #(
    .INIT(32'h00000040)) 
    p_1_out__17_i_1
       (.I0(p_1_out__0_i_29_n_0),
        .I1(p_1_out__15_i_29_n_0),
        .I2(p_1_out__0_i_31_n_0),
        .I3(p_1_out__15_i_30_n_0),
        .I4(p_1_out__1_i_29_n_0),
        .O(\AXI4_Lite_ARADDR[8]_10 ));
  (* SOFT_HLUTNM = "soft_lutpair8" *) 
  LUT5 #(
    .INIT(32'h00000040)) 
    p_1_out__18_i_1
       (.I0(p_1_out__0_i_29_n_0),
        .I1(p_1_out__15_i_29_n_0),
        .I2(p_1_out__0_i_31_n_0),
        .I3(p_1_out__15_i_30_n_0),
        .I4(p_1_out__2_i_29_n_0),
        .O(\AXI4_Lite_ARADDR[8]_8 ));
  (* SOFT_HLUTNM = "soft_lutpair6" *) 
  LUT5 #(
    .INIT(32'h00000040)) 
    p_1_out__19_i_1
       (.I0(p_1_out__0_i_29_n_0),
        .I1(p_1_out__15_i_29_n_0),
        .I2(p_1_out__0_i_31_n_0),
        .I3(p_1_out__15_i_30_n_0),
        .I4(p_1_out__3_i_29_n_0),
        .O(\AXI4_Lite_ARADDR[8]_6 ));
  (* SOFT_HLUTNM = "soft_lutpair11" *) 
  LUT5 #(
    .INIT(32'h00000040)) 
    p_1_out__1_i_1
       (.I0(p_1_out__0_i_29_n_0),
        .I1(p_1_out__0_i_30_n_0),
        .I2(p_1_out__0_i_31_n_0),
        .I3(p_1_out__1_i_29_n_0),
        .I4(p_1_out__0_i_32_n_0),
        .O(\AXI4_Lite_ARADDR[8]_11 ));
  LUT6 #(
    .INIT(64'hEFEAFFFAEFEFFFFF)) 
    p_1_out__1_i_29
       (.I0(p_1_out__0_i_33_n_0),
        .I1(AXI4_Lite_ARADDR[2]),
        .I2(AXI4_Lite_ARVALID),
        .I3(sel0[2]),
        .I4(AXI4_Lite_ARADDR[1]),
        .I5(sel0[1]),
        .O(p_1_out__1_i_29_n_0));
  (* SOFT_HLUTNM = "soft_lutpair4" *) 
  LUT5 #(
    .INIT(32'h00000040)) 
    p_1_out__20_i_1
       (.I0(p_1_out__0_i_29_n_0),
        .I1(p_1_out__15_i_29_n_0),
        .I2(p_1_out__0_i_31_n_0),
        .I3(p_1_out__15_i_30_n_0),
        .I4(p_1_out__4_i_29_n_0),
        .O(\AXI4_Lite_ARADDR[8]_4 ));
  (* SOFT_HLUTNM = "soft_lutpair2" *) 
  LUT5 #(
    .INIT(32'h00000040)) 
    p_1_out__21_i_1
       (.I0(p_1_out__0_i_29_n_0),
        .I1(p_1_out__15_i_29_n_0),
        .I2(p_1_out__0_i_31_n_0),
        .I3(p_1_out__15_i_30_n_0),
        .I4(p_1_out__5_i_29_n_0),
        .O(\AXI4_Lite_ARADDR[8]_2 ));
  (* SOFT_HLUTNM = "soft_lutpair0" *) 
  LUT5 #(
    .INIT(32'h00000040)) 
    p_1_out__22_i_1
       (.I0(p_1_out__0_i_29_n_0),
        .I1(p_1_out__15_i_29_n_0),
        .I2(p_1_out__0_i_31_n_0),
        .I3(p_1_out__15_i_30_n_0),
        .I4(p_1_out__6_i_29_n_0),
        .O(\AXI4_Lite_ARADDR[8]_0 ));
  LUT6 #(
    .INIT(64'h0000000000000100)) 
    p_1_out__23_i_1
       (.I0(p_1_out__15_i_30_n_0),
        .I1(p_1_out_i_32_n_0),
        .I2(p_1_out__0_i_33_n_0),
        .I3(p_1_out__0_i_31_n_0),
        .I4(p_1_out__0_i_29_n_0),
        .I5(p_1_out__15_i_29_n_0),
        .O(CEB2));
  LUT6 #(
    .INIT(64'h0000000000000400)) 
    p_1_out__24_i_1
       (.I0(p_1_out__15_i_30_n_0),
        .I1(p_1_out__0_i_33_n_0),
        .I2(p_1_out_i_32_n_0),
        .I3(p_1_out__0_i_31_n_0),
        .I4(p_1_out__0_i_29_n_0),
        .I5(p_1_out__15_i_29_n_0),
        .O(\AXI4_Lite_ARADDR[7]_5 ));
  (* SOFT_HLUTNM = "soft_lutpair10" *) 
  LUT5 #(
    .INIT(32'h00000010)) 
    p_1_out__25_i_1
       (.I0(p_1_out__15_i_30_n_0),
        .I1(p_1_out__1_i_29_n_0),
        .I2(p_1_out__0_i_31_n_0),
        .I3(p_1_out__0_i_29_n_0),
        .I4(p_1_out__15_i_29_n_0),
        .O(\AXI4_Lite_ARADDR[7]_4 ));
  (* SOFT_HLUTNM = "soft_lutpair8" *) 
  LUT5 #(
    .INIT(32'h00000010)) 
    p_1_out__26_i_1
       (.I0(p_1_out__15_i_30_n_0),
        .I1(p_1_out__2_i_29_n_0),
        .I2(p_1_out__0_i_31_n_0),
        .I3(p_1_out__0_i_29_n_0),
        .I4(p_1_out__15_i_29_n_0),
        .O(\AXI4_Lite_ARADDR[7]_3 ));
  (* SOFT_HLUTNM = "soft_lutpair6" *) 
  LUT5 #(
    .INIT(32'h00000010)) 
    p_1_out__27_i_1
       (.I0(p_1_out__15_i_30_n_0),
        .I1(p_1_out__3_i_29_n_0),
        .I2(p_1_out__0_i_31_n_0),
        .I3(p_1_out__0_i_29_n_0),
        .I4(p_1_out__15_i_29_n_0),
        .O(\AXI4_Lite_ARADDR[7]_2 ));
  (* SOFT_HLUTNM = "soft_lutpair4" *) 
  LUT5 #(
    .INIT(32'h00000010)) 
    p_1_out__28_i_1
       (.I0(p_1_out__15_i_30_n_0),
        .I1(p_1_out__4_i_29_n_0),
        .I2(p_1_out__0_i_31_n_0),
        .I3(p_1_out__0_i_29_n_0),
        .I4(p_1_out__15_i_29_n_0),
        .O(\AXI4_Lite_ARADDR[7]_1 ));
  (* SOFT_HLUTNM = "soft_lutpair2" *) 
  LUT5 #(
    .INIT(32'h00000010)) 
    p_1_out__29_i_1
       (.I0(p_1_out__15_i_30_n_0),
        .I1(p_1_out__5_i_29_n_0),
        .I2(p_1_out__0_i_31_n_0),
        .I3(p_1_out__0_i_29_n_0),
        .I4(p_1_out__15_i_29_n_0),
        .O(\AXI4_Lite_ARADDR[7]_0 ));
  (* SOFT_HLUTNM = "soft_lutpair9" *) 
  LUT5 #(
    .INIT(32'h00000040)) 
    p_1_out__2_i_1
       (.I0(p_1_out__0_i_29_n_0),
        .I1(p_1_out__0_i_30_n_0),
        .I2(p_1_out__0_i_31_n_0),
        .I3(p_1_out__2_i_29_n_0),
        .I4(p_1_out__0_i_32_n_0),
        .O(\AXI4_Lite_ARADDR[8]_9 ));
  LUT6 #(
    .INIT(64'hDFD5FFF5DFDFFFFF)) 
    p_1_out__2_i_29
       (.I0(p_1_out__0_i_33_n_0),
        .I1(AXI4_Lite_ARADDR[2]),
        .I2(AXI4_Lite_ARVALID),
        .I3(sel0[2]),
        .I4(AXI4_Lite_ARADDR[1]),
        .I5(sel0[1]),
        .O(p_1_out__2_i_29_n_0));
  (* SOFT_HLUTNM = "soft_lutpair0" *) 
  LUT5 #(
    .INIT(32'h00000010)) 
    p_1_out__30_i_1
       (.I0(p_1_out__15_i_30_n_0),
        .I1(p_1_out__6_i_29_n_0),
        .I2(p_1_out__0_i_31_n_0),
        .I3(p_1_out__0_i_29_n_0),
        .I4(p_1_out__15_i_29_n_0),
        .O(AXI4_Lite_ARADDR_7_sn_1));
  (* SOFT_HLUTNM = "soft_lutpair7" *) 
  LUT5 #(
    .INIT(32'h00000040)) 
    p_1_out__3_i_1
       (.I0(p_1_out__0_i_29_n_0),
        .I1(p_1_out__0_i_30_n_0),
        .I2(p_1_out__0_i_31_n_0),
        .I3(p_1_out__3_i_29_n_0),
        .I4(p_1_out__0_i_32_n_0),
        .O(\AXI4_Lite_ARADDR[8]_7 ));
  LUT6 #(
    .INIT(64'hEFEAFFFAEFEFFFFF)) 
    p_1_out__3_i_29
       (.I0(p_1_out__0_i_33_n_0),
        .I1(AXI4_Lite_ARADDR[1]),
        .I2(AXI4_Lite_ARVALID),
        .I3(sel0[1]),
        .I4(AXI4_Lite_ARADDR[2]),
        .I5(sel0[2]),
        .O(p_1_out__3_i_29_n_0));
  (* SOFT_HLUTNM = "soft_lutpair5" *) 
  LUT5 #(
    .INIT(32'h00000040)) 
    p_1_out__4_i_1
       (.I0(p_1_out__0_i_29_n_0),
        .I1(p_1_out__0_i_30_n_0),
        .I2(p_1_out__0_i_31_n_0),
        .I3(p_1_out__4_i_29_n_0),
        .I4(p_1_out__0_i_32_n_0),
        .O(\AXI4_Lite_ARADDR[8]_5 ));
  LUT6 #(
    .INIT(64'hDFD5FFF5DFDFFFFF)) 
    p_1_out__4_i_29
       (.I0(p_1_out__0_i_33_n_0),
        .I1(AXI4_Lite_ARADDR[1]),
        .I2(AXI4_Lite_ARVALID),
        .I3(sel0[1]),
        .I4(AXI4_Lite_ARADDR[2]),
        .I5(sel0[2]),
        .O(p_1_out__4_i_29_n_0));
  (* SOFT_HLUTNM = "soft_lutpair3" *) 
  LUT5 #(
    .INIT(32'h00000040)) 
    p_1_out__5_i_1
       (.I0(p_1_out__0_i_29_n_0),
        .I1(p_1_out__0_i_30_n_0),
        .I2(p_1_out__0_i_31_n_0),
        .I3(p_1_out__5_i_29_n_0),
        .I4(p_1_out__0_i_32_n_0),
        .O(\AXI4_Lite_ARADDR[8]_3 ));
  LUT6 #(
    .INIT(64'hBABFFAFFBFBFFFFF)) 
    p_1_out__5_i_29
       (.I0(p_1_out__0_i_33_n_0),
        .I1(AXI4_Lite_ARADDR[2]),
        .I2(AXI4_Lite_ARVALID),
        .I3(sel0[2]),
        .I4(AXI4_Lite_ARADDR[1]),
        .I5(sel0[1]),
        .O(p_1_out__5_i_29_n_0));
  (* SOFT_HLUTNM = "soft_lutpair1" *) 
  LUT5 #(
    .INIT(32'h00000040)) 
    p_1_out__6_i_1
       (.I0(p_1_out__0_i_29_n_0),
        .I1(p_1_out__0_i_30_n_0),
        .I2(p_1_out__0_i_31_n_0),
        .I3(p_1_out__6_i_29_n_0),
        .I4(p_1_out__0_i_32_n_0),
        .O(\AXI4_Lite_ARADDR[8]_1 ));
  LUT6 #(
    .INIT(64'h757FF5FF7F7FFFFF)) 
    p_1_out__6_i_29
       (.I0(p_1_out__0_i_33_n_0),
        .I1(AXI4_Lite_ARADDR[2]),
        .I2(AXI4_Lite_ARVALID),
        .I3(sel0[2]),
        .I4(AXI4_Lite_ARADDR[1]),
        .I5(sel0[1]),
        .O(p_1_out__6_i_29_n_0));
  LUT6 #(
    .INIT(64'h0000000000000002)) 
    p_1_out__7_i_1
       (.I0(p_1_out__0_i_31_n_0),
        .I1(p_1_out__0_i_29_n_0),
        .I2(p_1_out__0_i_30_n_0),
        .I3(p_1_out_i_32_n_0),
        .I4(p_1_out__0_i_33_n_0),
        .I5(p_1_out__0_i_32_n_0),
        .O(AXI4_Lite_ARADDR_11_sn_1));
  LUT6 #(
    .INIT(64'h0000000000000400)) 
    p_1_out__8_i_1
       (.I0(p_1_out__0_i_32_n_0),
        .I1(p_1_out__0_i_33_n_0),
        .I2(p_1_out_i_32_n_0),
        .I3(p_1_out__0_i_31_n_0),
        .I4(p_1_out__0_i_29_n_0),
        .I5(p_1_out__0_i_30_n_0),
        .O(AXI4_Lite_ARADDR_6_sn_1));
  (* SOFT_HLUTNM = "soft_lutpair11" *) 
  LUT5 #(
    .INIT(32'h00000010)) 
    p_1_out__9_i_1
       (.I0(p_1_out__1_i_29_n_0),
        .I1(p_1_out__0_i_32_n_0),
        .I2(p_1_out__0_i_31_n_0),
        .I3(p_1_out__0_i_29_n_0),
        .I4(p_1_out__0_i_30_n_0),
        .O(\AXI4_Lite_ARADDR[4]_2 ));
  LUT6 #(
    .INIT(64'h0000000000020000)) 
    p_1_out_i_1
       (.I0(p_1_out_i_29_n_0),
        .I1(p_1_out_i_30_n_0),
        .I2(p_1_out_i_31_n_0),
        .I3(p_1_out_i_32_n_0),
        .I4(top_wr_enb),
        .I5(p_1_out_i_33_n_0),
        .O(wr_enb_1_reg_0));
  LUT6 #(
    .INIT(64'h0000000000004700)) 
    p_1_out_i_29
       (.I0(AXI4_Lite_ARADDR[9]),
        .I1(AXI4_Lite_ARVALID),
        .I2(sel0[9]),
        .I3(p_1_out_i_34_n_0),
        .I4(p_1_out_i_35_n_0),
        .I5(p_1_out_i_36_n_0),
        .O(p_1_out_i_29_n_0));
  (* SOFT_HLUTNM = "soft_lutpair13" *) 
  LUT5 #(
    .INIT(32'hCCAFFFAF)) 
    p_1_out_i_30
       (.I0(sel0[7]),
        .I1(AXI4_Lite_ARADDR[7]),
        .I2(sel0[6]),
        .I3(AXI4_Lite_ARVALID),
        .I4(AXI4_Lite_ARADDR[6]),
        .O(p_1_out_i_30_n_0));
  (* SOFT_HLUTNM = "soft_lutpair12" *) 
  LUT5 #(
    .INIT(32'hFFFACCFA)) 
    p_1_out_i_31
       (.I0(sel0[13]),
        .I1(AXI4_Lite_ARADDR[13]),
        .I2(sel0[0]),
        .I3(AXI4_Lite_ARVALID),
        .I4(AXI4_Lite_ARADDR[0]),
        .O(p_1_out_i_31_n_0));
  (* SOFT_HLUTNM = "soft_lutpair16" *) 
  LUT5 #(
    .INIT(32'hFFFACCFA)) 
    p_1_out_i_32
       (.I0(sel0[1]),
        .I1(AXI4_Lite_ARADDR[1]),
        .I2(sel0[2]),
        .I3(AXI4_Lite_ARVALID),
        .I4(AXI4_Lite_ARADDR[2]),
        .O(p_1_out_i_32_n_0));
  (* SOFT_HLUTNM = "soft_lutpair14" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    p_1_out_i_33
       (.I0(AXI4_Lite_ARADDR[12]),
        .I1(AXI4_Lite_ARVALID),
        .I2(sel0[12]),
        .O(p_1_out_i_33_n_0));
  LUT5 #(
    .INIT(32'h00053305)) 
    p_1_out_i_34
       (.I0(sel0[10]),
        .I1(AXI4_Lite_ARADDR[10]),
        .I2(sel0[11]),
        .I3(AXI4_Lite_ARVALID),
        .I4(AXI4_Lite_ARADDR[11]),
        .O(p_1_out_i_34_n_0));
  (* SOFT_HLUTNM = "soft_lutpair18" *) 
  LUT5 #(
    .INIT(32'hFFFACCFA)) 
    p_1_out_i_35
       (.I0(sel0[8]),
        .I1(AXI4_Lite_ARADDR[8]),
        .I2(sel0[4]),
        .I3(AXI4_Lite_ARVALID),
        .I4(AXI4_Lite_ARADDR[4]),
        .O(p_1_out_i_35_n_0));
  LUT5 #(
    .INIT(32'hFFFACCFA)) 
    p_1_out_i_36
       (.I0(sel0[5]),
        .I1(AXI4_Lite_ARADDR[5]),
        .I2(sel0[3]),
        .I3(AXI4_Lite_ARVALID),
        .I4(AXI4_Lite_ARADDR[3]),
        .O(p_1_out_i_36_n_0));
  LUT3 #(
    .INIT(8'hBF)) 
    reset_pipe_i_1
       (.I0(soft_reset),
        .I1(AXI4_Lite_ARESETN),
        .I2(IPCORE_RESETN),
        .O(reset_in));
  LUT6 #(
    .INIT(64'h0000000000000002)) 
    soft_reset_i_1
       (.I0(soft_reset_i_2_n_0),
        .I1(soft_reset_i_3_n_0),
        .I2(soft_reset_i_4_n_0),
        .I3(sel0[10]),
        .I4(sel0[11]),
        .I5(sel0[9]),
        .O(soft_reset_i_1_n_0));
  LUT6 #(
    .INIT(64'h0000000400000000)) 
    soft_reset_i_2
       (.I0(sel0[2]),
        .I1(top_wr_enb),
        .I2(sel0[1]),
        .I3(sel0[13]),
        .I4(sel0[4]),
        .I5(AXI4_Lite_ARESETN),
        .O(soft_reset_i_2_n_0));
  LUT4 #(
    .INIT(16'hFFFD)) 
    soft_reset_i_3
       (.I0(\wdata_reg_n_0_[0] ),
        .I1(sel0[3]),
        .I2(sel0[12]),
        .I3(sel0[7]),
        .O(soft_reset_i_3_n_0));
  LUT4 #(
    .INIT(16'hFFFE)) 
    soft_reset_i_4
       (.I0(sel0[6]),
        .I1(sel0[0]),
        .I2(sel0[8]),
        .I3(sel0[5]),
        .O(soft_reset_i_4_n_0));
  FDRE soft_reset_reg
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(soft_reset_i_1_n_0),
        .Q(soft_reset),
        .R(1'b0));
  LUT3 #(
    .INIT(8'h08)) 
    \waddr[15]_i_1 
       (.I0(AXI4_Lite_AWVALID),
        .I1(\FSM_onehot_axi_lite_wstate_reg_n_0_[0] ),
        .I2(FSM_sequential_axi_lite_rstate_reg_0),
        .O(aw_transfer));
  FDRE \waddr_reg[10] 
       (.C(AXI4_Lite_ACLK),
        .CE(aw_transfer),
        .D(AXI4_Lite_AWADDR[8]),
        .Q(sel0[8]),
        .R(reset));
  FDRE \waddr_reg[11] 
       (.C(AXI4_Lite_ACLK),
        .CE(aw_transfer),
        .D(AXI4_Lite_AWADDR[9]),
        .Q(sel0[9]),
        .R(reset));
  FDRE \waddr_reg[12] 
       (.C(AXI4_Lite_ACLK),
        .CE(aw_transfer),
        .D(AXI4_Lite_AWADDR[10]),
        .Q(sel0[10]),
        .R(reset));
  FDRE \waddr_reg[13] 
       (.C(AXI4_Lite_ACLK),
        .CE(aw_transfer),
        .D(AXI4_Lite_AWADDR[11]),
        .Q(sel0[11]),
        .R(reset));
  FDRE \waddr_reg[14] 
       (.C(AXI4_Lite_ACLK),
        .CE(aw_transfer),
        .D(AXI4_Lite_AWADDR[12]),
        .Q(sel0[12]),
        .R(reset));
  FDRE \waddr_reg[15] 
       (.C(AXI4_Lite_ACLK),
        .CE(aw_transfer),
        .D(AXI4_Lite_AWADDR[13]),
        .Q(sel0[13]),
        .R(reset));
  FDRE \waddr_reg[2] 
       (.C(AXI4_Lite_ACLK),
        .CE(aw_transfer),
        .D(AXI4_Lite_AWADDR[0]),
        .Q(sel0[0]),
        .R(reset));
  FDRE \waddr_reg[3] 
       (.C(AXI4_Lite_ACLK),
        .CE(aw_transfer),
        .D(AXI4_Lite_AWADDR[1]),
        .Q(sel0[1]),
        .R(reset));
  FDRE \waddr_reg[4] 
       (.C(AXI4_Lite_ACLK),
        .CE(aw_transfer),
        .D(AXI4_Lite_AWADDR[2]),
        .Q(sel0[2]),
        .R(reset));
  FDRE \waddr_reg[5] 
       (.C(AXI4_Lite_ACLK),
        .CE(aw_transfer),
        .D(AXI4_Lite_AWADDR[3]),
        .Q(sel0[3]),
        .R(reset));
  FDRE \waddr_reg[6] 
       (.C(AXI4_Lite_ACLK),
        .CE(aw_transfer),
        .D(AXI4_Lite_AWADDR[4]),
        .Q(sel0[4]),
        .R(reset));
  FDRE \waddr_reg[7] 
       (.C(AXI4_Lite_ACLK),
        .CE(aw_transfer),
        .D(AXI4_Lite_AWADDR[5]),
        .Q(sel0[5]),
        .R(reset));
  FDRE \waddr_reg[8] 
       (.C(AXI4_Lite_ACLK),
        .CE(aw_transfer),
        .D(AXI4_Lite_AWADDR[6]),
        .Q(sel0[6]),
        .R(reset));
  FDRE \waddr_reg[9] 
       (.C(AXI4_Lite_ACLK),
        .CE(aw_transfer),
        .D(AXI4_Lite_AWADDR[7]),
        .Q(sel0[7]),
        .R(reset));
  LUT2 #(
    .INIT(4'h8)) 
    \wdata[17]_i_1 
       (.I0(AXI4_Lite_WVALID),
        .I1(Q[0]),
        .O(w_transfer));
  FDRE \wdata_reg[0] 
       (.C(AXI4_Lite_ACLK),
        .CE(w_transfer),
        .D(AXI4_Lite_WDATA[0]),
        .Q(\wdata_reg_n_0_[0] ),
        .R(reset));
  FDRE \wdata_reg[10] 
       (.C(AXI4_Lite_ACLK),
        .CE(w_transfer),
        .D(AXI4_Lite_WDATA[10]),
        .Q(\wdata_reg[17]_0 [9]),
        .R(reset));
  FDRE \wdata_reg[11] 
       (.C(AXI4_Lite_ACLK),
        .CE(w_transfer),
        .D(AXI4_Lite_WDATA[11]),
        .Q(\wdata_reg[17]_0 [10]),
        .R(reset));
  FDRE \wdata_reg[12] 
       (.C(AXI4_Lite_ACLK),
        .CE(w_transfer),
        .D(AXI4_Lite_WDATA[12]),
        .Q(\wdata_reg[17]_0 [11]),
        .R(reset));
  FDRE \wdata_reg[13] 
       (.C(AXI4_Lite_ACLK),
        .CE(w_transfer),
        .D(AXI4_Lite_WDATA[13]),
        .Q(\wdata_reg[17]_0 [12]),
        .R(reset));
  FDRE \wdata_reg[14] 
       (.C(AXI4_Lite_ACLK),
        .CE(w_transfer),
        .D(AXI4_Lite_WDATA[14]),
        .Q(\wdata_reg[17]_0 [13]),
        .R(reset));
  FDRE \wdata_reg[15] 
       (.C(AXI4_Lite_ACLK),
        .CE(w_transfer),
        .D(AXI4_Lite_WDATA[15]),
        .Q(\wdata_reg[17]_0 [14]),
        .R(reset));
  FDRE \wdata_reg[16] 
       (.C(AXI4_Lite_ACLK),
        .CE(w_transfer),
        .D(AXI4_Lite_WDATA[16]),
        .Q(\wdata_reg[17]_0 [15]),
        .R(reset));
  FDRE \wdata_reg[17] 
       (.C(AXI4_Lite_ACLK),
        .CE(w_transfer),
        .D(AXI4_Lite_WDATA[17]),
        .Q(\wdata_reg[17]_0 [16]),
        .R(reset));
  FDRE \wdata_reg[1] 
       (.C(AXI4_Lite_ACLK),
        .CE(w_transfer),
        .D(AXI4_Lite_WDATA[1]),
        .Q(\wdata_reg[17]_0 [0]),
        .R(reset));
  FDRE \wdata_reg[2] 
       (.C(AXI4_Lite_ACLK),
        .CE(w_transfer),
        .D(AXI4_Lite_WDATA[2]),
        .Q(\wdata_reg[17]_0 [1]),
        .R(reset));
  FDRE \wdata_reg[3] 
       (.C(AXI4_Lite_ACLK),
        .CE(w_transfer),
        .D(AXI4_Lite_WDATA[3]),
        .Q(\wdata_reg[17]_0 [2]),
        .R(reset));
  FDRE \wdata_reg[4] 
       (.C(AXI4_Lite_ACLK),
        .CE(w_transfer),
        .D(AXI4_Lite_WDATA[4]),
        .Q(\wdata_reg[17]_0 [3]),
        .R(reset));
  FDRE \wdata_reg[5] 
       (.C(AXI4_Lite_ACLK),
        .CE(w_transfer),
        .D(AXI4_Lite_WDATA[5]),
        .Q(\wdata_reg[17]_0 [4]),
        .R(reset));
  FDRE \wdata_reg[6] 
       (.C(AXI4_Lite_ACLK),
        .CE(w_transfer),
        .D(AXI4_Lite_WDATA[6]),
        .Q(\wdata_reg[17]_0 [5]),
        .R(reset));
  FDRE \wdata_reg[7] 
       (.C(AXI4_Lite_ACLK),
        .CE(w_transfer),
        .D(AXI4_Lite_WDATA[7]),
        .Q(\wdata_reg[17]_0 [6]),
        .R(reset));
  FDRE \wdata_reg[8] 
       (.C(AXI4_Lite_ACLK),
        .CE(w_transfer),
        .D(AXI4_Lite_WDATA[8]),
        .Q(\wdata_reg[17]_0 [7]),
        .R(reset));
  FDRE \wdata_reg[9] 
       (.C(AXI4_Lite_ACLK),
        .CE(w_transfer),
        .D(AXI4_Lite_WDATA[9]),
        .Q(\wdata_reg[17]_0 [8]),
        .R(reset));
  LUT6 #(
    .INIT(64'h8000000000000000)) 
    wr_enb_1_i_1
       (.I0(Q[0]),
        .I1(AXI4_Lite_WVALID),
        .I2(AXI4_Lite_WSTRB[2]),
        .I3(AXI4_Lite_WSTRB[1]),
        .I4(AXI4_Lite_WSTRB[0]),
        .I5(AXI4_Lite_WSTRB[3]),
        .O(w_transfer_and_wstrb));
  FDRE wr_enb_1_reg
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(w_transfer_and_wstrb),
        .Q(top_wr_enb),
        .R(reset));
endmodule

(* ORIG_REF_NAME = "uz_pu_con_ip_dut" *) 
module zusys_uz_pu_con_ip_0_1_uz_pu_con_ip_dut
   (out0,
    out1,
    out2,
    out3,
    out4,
    out5,
    out6,
    out7,
    out8,
    out9,
    out10,
    out11,
    out12,
    out13,
    out14,
    out15,
    out16,
    out17,
    out18,
    out19,
    out20,
    out21,
    out22,
    out23,
    out24,
    out25,
    out26,
    out27,
    out28,
    out29,
    out30,
    out31,
    reset,
    adc_trigger,
    in0,
    IPCORE_CLK,
    DSP_ALU_INST,
    AXI4_Lite_ACLK,
    AXI_pu_conv_in31,
    OPMODE,
    in1,
    DSP_ALU_INST_0,
    \out1[17] ,
    in2,
    DSP_ALU_INST_1,
    \out2[17] ,
    in3,
    DSP_ALU_INST_2,
    \out3[17] ,
    in4,
    DSP_ALU_INST_3,
    \out4[17] ,
    in5,
    DSP_ALU_INST_4,
    \out5[17] ,
    in6,
    DSP_ALU_INST_5,
    \out6[17] ,
    in7,
    DSP_ALU_INST_6,
    \out7[17] ,
    in8,
    DSP_ALU_INST_7,
    \out8[17] ,
    in9,
    DSP_ALU_INST_8,
    \out9[17] ,
    in10,
    DSP_ALU_INST_9,
    \out10[17] ,
    in11,
    DSP_ALU_INST_10,
    \out11[17] ,
    in12,
    DSP_ALU_INST_11,
    \out12[17] ,
    in13,
    DSP_ALU_INST_12,
    \out13[17] ,
    in14,
    DSP_ALU_INST_13,
    \out14[17] ,
    in15,
    DSP_ALU_INST_14,
    \out15[17] ,
    in16,
    DSP_ALU_INST_15,
    \out16[17] ,
    in17,
    DSP_ALU_INST_16,
    \out17[17] ,
    in18,
    DSP_ALU_INST_17,
    \out18[17] ,
    in19,
    DSP_ALU_INST_18,
    \out19[17] ,
    in20,
    DSP_ALU_INST_19,
    \out20[17] ,
    in21,
    DSP_ALU_INST_20,
    \out21[17] ,
    in22,
    DSP_ALU_INST_21,
    \out22[17] ,
    in23,
    DSP_ALU_INST_22,
    \out23[17] ,
    in24,
    CEB2,
    \out24[17] ,
    in25,
    DSP_ALU_INST_23,
    \out25[17] ,
    in26,
    DSP_ALU_INST_24,
    \out26[17] ,
    in27,
    DSP_ALU_INST_25,
    \out27[17] ,
    in28,
    DSP_ALU_INST_26,
    \out28[17] ,
    in29,
    DSP_ALU_INST_27,
    \out29[17] ,
    in30,
    DSP_ALU_INST_28,
    \out30[17] ,
    in31,
    DSP_ALU_INST_29,
    \out31[17] );
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
  input reset;
  input adc_trigger;
  input [26:0]in0;
  input IPCORE_CLK;
  input DSP_ALU_INST;
  input AXI4_Lite_ACLK;
  input [16:0]AXI_pu_conv_in31;
  input [0:0]OPMODE;
  input [26:0]in1;
  input DSP_ALU_INST_0;
  input [0:0]\out1[17] ;
  input [26:0]in2;
  input DSP_ALU_INST_1;
  input [0:0]\out2[17] ;
  input [26:0]in3;
  input DSP_ALU_INST_2;
  input [0:0]\out3[17] ;
  input [26:0]in4;
  input DSP_ALU_INST_3;
  input [0:0]\out4[17] ;
  input [26:0]in5;
  input DSP_ALU_INST_4;
  input [0:0]\out5[17] ;
  input [26:0]in6;
  input DSP_ALU_INST_5;
  input [0:0]\out6[17] ;
  input [26:0]in7;
  input DSP_ALU_INST_6;
  input [0:0]\out7[17] ;
  input [26:0]in8;
  input DSP_ALU_INST_7;
  input [0:0]\out8[17] ;
  input [26:0]in9;
  input DSP_ALU_INST_8;
  input [0:0]\out9[17] ;
  input [26:0]in10;
  input DSP_ALU_INST_9;
  input [0:0]\out10[17] ;
  input [26:0]in11;
  input DSP_ALU_INST_10;
  input [0:0]\out11[17] ;
  input [26:0]in12;
  input DSP_ALU_INST_11;
  input [0:0]\out12[17] ;
  input [26:0]in13;
  input DSP_ALU_INST_12;
  input [0:0]\out13[17] ;
  input [26:0]in14;
  input DSP_ALU_INST_13;
  input [0:0]\out14[17] ;
  input [26:0]in15;
  input DSP_ALU_INST_14;
  input [0:0]\out15[17] ;
  input [26:0]in16;
  input DSP_ALU_INST_15;
  input [0:0]\out16[17] ;
  input [26:0]in17;
  input DSP_ALU_INST_16;
  input [0:0]\out17[17] ;
  input [26:0]in18;
  input DSP_ALU_INST_17;
  input [0:0]\out18[17] ;
  input [26:0]in19;
  input DSP_ALU_INST_18;
  input [0:0]\out19[17] ;
  input [26:0]in20;
  input DSP_ALU_INST_19;
  input [0:0]\out20[17] ;
  input [26:0]in21;
  input DSP_ALU_INST_20;
  input [0:0]\out21[17] ;
  input [26:0]in22;
  input DSP_ALU_INST_21;
  input [0:0]\out22[17] ;
  input [26:0]in23;
  input DSP_ALU_INST_22;
  input [0:0]\out23[17] ;
  input [26:0]in24;
  input CEB2;
  input [0:0]\out24[17] ;
  input [26:0]in25;
  input DSP_ALU_INST_23;
  input [0:0]\out25[17] ;
  input [26:0]in26;
  input DSP_ALU_INST_24;
  input [0:0]\out26[17] ;
  input [26:0]in27;
  input DSP_ALU_INST_25;
  input [0:0]\out27[17] ;
  input [26:0]in28;
  input DSP_ALU_INST_26;
  input [0:0]\out28[17] ;
  input [26:0]in29;
  input DSP_ALU_INST_27;
  input [0:0]\out29[17] ;
  input [26:0]in30;
  input DSP_ALU_INST_28;
  input [0:0]\out30[17] ;
  input [26:0]in31;
  input DSP_ALU_INST_29;
  input [0:0]\out31[17] ;

  wire AXI4_Lite_ACLK;
  wire [16:0]AXI_pu_conv_in31;
  wire CEB2;
  wire DSP_ALU_INST;
  wire DSP_ALU_INST_0;
  wire DSP_ALU_INST_1;
  wire DSP_ALU_INST_10;
  wire DSP_ALU_INST_11;
  wire DSP_ALU_INST_12;
  wire DSP_ALU_INST_13;
  wire DSP_ALU_INST_14;
  wire DSP_ALU_INST_15;
  wire DSP_ALU_INST_16;
  wire DSP_ALU_INST_17;
  wire DSP_ALU_INST_18;
  wire DSP_ALU_INST_19;
  wire DSP_ALU_INST_2;
  wire DSP_ALU_INST_20;
  wire DSP_ALU_INST_21;
  wire DSP_ALU_INST_22;
  wire DSP_ALU_INST_23;
  wire DSP_ALU_INST_24;
  wire DSP_ALU_INST_25;
  wire DSP_ALU_INST_26;
  wire DSP_ALU_INST_27;
  wire DSP_ALU_INST_28;
  wire DSP_ALU_INST_29;
  wire DSP_ALU_INST_3;
  wire DSP_ALU_INST_4;
  wire DSP_ALU_INST_5;
  wire DSP_ALU_INST_6;
  wire DSP_ALU_INST_7;
  wire DSP_ALU_INST_8;
  wire DSP_ALU_INST_9;
  wire IPCORE_CLK;
  wire [0:0]OPMODE;
  wire adc_trigger;
  wire [26:0]in0;
  wire [26:0]in1;
  wire [26:0]in10;
  wire [26:0]in11;
  wire [26:0]in12;
  wire [26:0]in13;
  wire [26:0]in14;
  wire [26:0]in15;
  wire [26:0]in16;
  wire [26:0]in17;
  wire [26:0]in18;
  wire [26:0]in19;
  wire [26:0]in2;
  wire [26:0]in20;
  wire [26:0]in21;
  wire [26:0]in22;
  wire [26:0]in23;
  wire [26:0]in24;
  wire [26:0]in25;
  wire [26:0]in26;
  wire [26:0]in27;
  wire [26:0]in28;
  wire [26:0]in29;
  wire [26:0]in3;
  wire [26:0]in30;
  wire [26:0]in31;
  wire [26:0]in4;
  wire [26:0]in5;
  wire [26:0]in6;
  wire [26:0]in7;
  wire [26:0]in8;
  wire [26:0]in9;
  wire [17:0]out0;
  wire [17:0]out1;
  wire [17:0]out10;
  wire [0:0]\out10[17] ;
  wire [17:0]out11;
  wire [0:0]\out11[17] ;
  wire [17:0]out12;
  wire [0:0]\out12[17] ;
  wire [17:0]out13;
  wire [0:0]\out13[17] ;
  wire [17:0]out14;
  wire [0:0]\out14[17] ;
  wire [17:0]out15;
  wire [0:0]\out15[17] ;
  wire [17:0]out16;
  wire [0:0]\out16[17] ;
  wire [17:0]out17;
  wire [0:0]\out17[17] ;
  wire [17:0]out18;
  wire [0:0]\out18[17] ;
  wire [17:0]out19;
  wire [0:0]\out19[17] ;
  wire [0:0]\out1[17] ;
  wire [17:0]out2;
  wire [17:0]out20;
  wire [0:0]\out20[17] ;
  wire [17:0]out21;
  wire [0:0]\out21[17] ;
  wire [17:0]out22;
  wire [0:0]\out22[17] ;
  wire [17:0]out23;
  wire [0:0]\out23[17] ;
  wire [17:0]out24;
  wire [0:0]\out24[17] ;
  wire [17:0]out25;
  wire [0:0]\out25[17] ;
  wire [17:0]out26;
  wire [0:0]\out26[17] ;
  wire [17:0]out27;
  wire [0:0]\out27[17] ;
  wire [17:0]out28;
  wire [0:0]\out28[17] ;
  wire [17:0]out29;
  wire [0:0]\out29[17] ;
  wire [0:0]\out2[17] ;
  wire [17:0]out3;
  wire [17:0]out30;
  wire [0:0]\out30[17] ;
  wire [17:0]out31;
  wire [0:0]\out31[17] ;
  wire [0:0]\out3[17] ;
  wire [17:0]out4;
  wire [0:0]\out4[17] ;
  wire [17:0]out5;
  wire [0:0]\out5[17] ;
  wire [17:0]out6;
  wire [0:0]\out6[17] ;
  wire [17:0]out7;
  wire [0:0]\out7[17] ;
  wire [17:0]out8;
  wire [0:0]\out8[17] ;
  wire [17:0]out9;
  wire [0:0]\out9[17] ;
  wire reset;

  zusys_uz_pu_con_ip_0_1_uz_pu_con_ip_src_uz_pu_conversion u_uz_pu_con_ip_src_uz_pu_conversion
       (.AXI4_Lite_ACLK(AXI4_Lite_ACLK),
        .AXI_pu_conv_in31(AXI_pu_conv_in31),
        .CEB2(CEB2),
        .DSP_ALU_INST(DSP_ALU_INST),
        .DSP_ALU_INST_0(DSP_ALU_INST_0),
        .DSP_ALU_INST_1(DSP_ALU_INST_1),
        .DSP_ALU_INST_10(DSP_ALU_INST_10),
        .DSP_ALU_INST_11(DSP_ALU_INST_11),
        .DSP_ALU_INST_12(DSP_ALU_INST_12),
        .DSP_ALU_INST_13(DSP_ALU_INST_13),
        .DSP_ALU_INST_14(DSP_ALU_INST_14),
        .DSP_ALU_INST_15(DSP_ALU_INST_15),
        .DSP_ALU_INST_16(DSP_ALU_INST_16),
        .DSP_ALU_INST_17(DSP_ALU_INST_17),
        .DSP_ALU_INST_18(DSP_ALU_INST_18),
        .DSP_ALU_INST_19(DSP_ALU_INST_19),
        .DSP_ALU_INST_2(DSP_ALU_INST_2),
        .DSP_ALU_INST_20(DSP_ALU_INST_20),
        .DSP_ALU_INST_21(DSP_ALU_INST_21),
        .DSP_ALU_INST_22(DSP_ALU_INST_22),
        .DSP_ALU_INST_23(DSP_ALU_INST_23),
        .DSP_ALU_INST_24(DSP_ALU_INST_24),
        .DSP_ALU_INST_25(DSP_ALU_INST_25),
        .DSP_ALU_INST_26(DSP_ALU_INST_26),
        .DSP_ALU_INST_27(DSP_ALU_INST_27),
        .DSP_ALU_INST_28(DSP_ALU_INST_28),
        .DSP_ALU_INST_29(DSP_ALU_INST_29),
        .DSP_ALU_INST_3(DSP_ALU_INST_3),
        .DSP_ALU_INST_4(DSP_ALU_INST_4),
        .DSP_ALU_INST_5(DSP_ALU_INST_5),
        .DSP_ALU_INST_6(DSP_ALU_INST_6),
        .DSP_ALU_INST_7(DSP_ALU_INST_7),
        .DSP_ALU_INST_8(DSP_ALU_INST_8),
        .DSP_ALU_INST_9(DSP_ALU_INST_9),
        .IPCORE_CLK(IPCORE_CLK),
        .OPMODE(OPMODE),
        .adc_trigger(adc_trigger),
        .in0(in0),
        .in1(in1),
        .in10(in10),
        .in11(in11),
        .in12(in12),
        .in13(in13),
        .in14(in14),
        .in15(in15),
        .in16(in16),
        .in17(in17),
        .in18(in18),
        .in19(in19),
        .in2(in2),
        .in20(in20),
        .in21(in21),
        .in22(in22),
        .in23(in23),
        .in24(in24),
        .in25(in25),
        .in26(in26),
        .in27(in27),
        .in28(in28),
        .in29(in29),
        .in3(in3),
        .in30(in30),
        .in31(in31),
        .in4(in4),
        .in5(in5),
        .in6(in6),
        .in7(in7),
        .in8(in8),
        .in9(in9),
        .out0(out0),
        .out1(out1),
        .out10(out10),
        .\out10[17] (\out10[17] ),
        .out11(out11),
        .\out11[17] (\out11[17] ),
        .out12(out12),
        .\out12[17] (\out12[17] ),
        .out13(out13),
        .\out13[17] (\out13[17] ),
        .out14(out14),
        .\out14[17] (\out14[17] ),
        .out15(out15),
        .\out15[17] (\out15[17] ),
        .out16(out16),
        .\out16[17] (\out16[17] ),
        .out17(out17),
        .\out17[17] (\out17[17] ),
        .out18(out18),
        .\out18[17] (\out18[17] ),
        .out19(out19),
        .\out19[17] (\out19[17] ),
        .\out1[17] (\out1[17] ),
        .out2(out2),
        .out20(out20),
        .\out20[17] (\out20[17] ),
        .out21(out21),
        .\out21[17] (\out21[17] ),
        .out22(out22),
        .\out22[17] (\out22[17] ),
        .out23(out23),
        .\out23[17] (\out23[17] ),
        .out24(out24),
        .\out24[17] (\out24[17] ),
        .out25(out25),
        .\out25[17] (\out25[17] ),
        .out26(out26),
        .\out26[17] (\out26[17] ),
        .out27(out27),
        .\out27[17] (\out27[17] ),
        .out28(out28),
        .\out28[17] (\out28[17] ),
        .out29(out29),
        .\out29[17] (\out29[17] ),
        .\out2[17] (\out2[17] ),
        .out3(out3),
        .out30(out30),
        .\out30[17] (\out30[17] ),
        .out31(out31),
        .\out31[17] (\out31[17] ),
        .\out3[17] (\out3[17] ),
        .out4(out4),
        .\out4[17] (\out4[17] ),
        .out5(out5),
        .\out5[17] (\out5[17] ),
        .out6(out6),
        .\out6[17] (\out6[17] ),
        .out7(out7),
        .\out7[17] (\out7[17] ),
        .out8(out8),
        .\out8[17] (\out8[17] ),
        .out9(out9),
        .\out9[17] (\out9[17] ),
        .reset(reset));
endmodule

(* ORIG_REF_NAME = "uz_pu_con_ip_reset_sync" *) 
module zusys_uz_pu_con_ip_0_1_uz_pu_con_ip_reset_sync
   (reset,
    reset_out_reg_0,
    reset_in,
    IPCORE_CLK,
    IPCORE_RESETN,
    AXI4_Lite_ARESETN,
    soft_reset);
  output reset;
  output reset_out_reg_0;
  input reset_in;
  input IPCORE_CLK;
  input IPCORE_RESETN;
  input AXI4_Lite_ARESETN;
  input soft_reset;

  wire AXI4_Lite_ARESETN;
  wire IPCORE_CLK;
  wire IPCORE_RESETN;
  wire reset;
  wire reset_in;
  wire reset_out_i_1_n_0;
  wire reset_out_reg_0;
  wire reset_pipe;
  wire soft_reset;

  LUT1 #(
    .INIT(2'h1)) 
    \read_reg_ip_timestamp[31]_i_1 
       (.I0(reset),
        .O(reset_out_reg_0));
  LUT4 #(
    .INIT(16'hFFBF)) 
    reset_out_i_1
       (.I0(reset_pipe),
        .I1(IPCORE_RESETN),
        .I2(AXI4_Lite_ARESETN),
        .I3(soft_reset),
        .O(reset_out_i_1_n_0));
  FDRE reset_out_reg
       (.C(IPCORE_CLK),
        .CE(1'b1),
        .D(reset_out_i_1_n_0),
        .Q(reset),
        .R(1'b0));
  FDRE reset_pipe_reg
       (.C(IPCORE_CLK),
        .CE(1'b1),
        .D(reset_in),
        .Q(reset_pipe),
        .R(1'b0));
endmodule

(* ORIG_REF_NAME = "uz_pu_con_ip_src_uz_pu_conversion" *) 
module zusys_uz_pu_con_ip_0_1_uz_pu_con_ip_src_uz_pu_conversion
   (out0,
    out1,
    out2,
    out3,
    out4,
    out5,
    out6,
    out7,
    out8,
    out9,
    out10,
    out11,
    out12,
    out13,
    out14,
    out15,
    out16,
    out17,
    out18,
    out19,
    out20,
    out21,
    out22,
    out23,
    out24,
    out25,
    out26,
    out27,
    out28,
    out29,
    out30,
    out31,
    reset,
    adc_trigger,
    in0,
    IPCORE_CLK,
    DSP_ALU_INST,
    AXI4_Lite_ACLK,
    AXI_pu_conv_in31,
    OPMODE,
    in1,
    DSP_ALU_INST_0,
    \out1[17] ,
    in2,
    DSP_ALU_INST_1,
    \out2[17] ,
    in3,
    DSP_ALU_INST_2,
    \out3[17] ,
    in4,
    DSP_ALU_INST_3,
    \out4[17] ,
    in5,
    DSP_ALU_INST_4,
    \out5[17] ,
    in6,
    DSP_ALU_INST_5,
    \out6[17] ,
    in7,
    DSP_ALU_INST_6,
    \out7[17] ,
    in8,
    DSP_ALU_INST_7,
    \out8[17] ,
    in9,
    DSP_ALU_INST_8,
    \out9[17] ,
    in10,
    DSP_ALU_INST_9,
    \out10[17] ,
    in11,
    DSP_ALU_INST_10,
    \out11[17] ,
    in12,
    DSP_ALU_INST_11,
    \out12[17] ,
    in13,
    DSP_ALU_INST_12,
    \out13[17] ,
    in14,
    DSP_ALU_INST_13,
    \out14[17] ,
    in15,
    DSP_ALU_INST_14,
    \out15[17] ,
    in16,
    DSP_ALU_INST_15,
    \out16[17] ,
    in17,
    DSP_ALU_INST_16,
    \out17[17] ,
    in18,
    DSP_ALU_INST_17,
    \out18[17] ,
    in19,
    DSP_ALU_INST_18,
    \out19[17] ,
    in20,
    DSP_ALU_INST_19,
    \out20[17] ,
    in21,
    DSP_ALU_INST_20,
    \out21[17] ,
    in22,
    DSP_ALU_INST_21,
    \out22[17] ,
    in23,
    DSP_ALU_INST_22,
    \out23[17] ,
    in24,
    CEB2,
    \out24[17] ,
    in25,
    DSP_ALU_INST_23,
    \out25[17] ,
    in26,
    DSP_ALU_INST_24,
    \out26[17] ,
    in27,
    DSP_ALU_INST_25,
    \out27[17] ,
    in28,
    DSP_ALU_INST_26,
    \out28[17] ,
    in29,
    DSP_ALU_INST_27,
    \out29[17] ,
    in30,
    DSP_ALU_INST_28,
    \out30[17] ,
    in31,
    DSP_ALU_INST_29,
    \out31[17] );
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
  input reset;
  input adc_trigger;
  input [26:0]in0;
  input IPCORE_CLK;
  input DSP_ALU_INST;
  input AXI4_Lite_ACLK;
  input [16:0]AXI_pu_conv_in31;
  input [0:0]OPMODE;
  input [26:0]in1;
  input DSP_ALU_INST_0;
  input [0:0]\out1[17] ;
  input [26:0]in2;
  input DSP_ALU_INST_1;
  input [0:0]\out2[17] ;
  input [26:0]in3;
  input DSP_ALU_INST_2;
  input [0:0]\out3[17] ;
  input [26:0]in4;
  input DSP_ALU_INST_3;
  input [0:0]\out4[17] ;
  input [26:0]in5;
  input DSP_ALU_INST_4;
  input [0:0]\out5[17] ;
  input [26:0]in6;
  input DSP_ALU_INST_5;
  input [0:0]\out6[17] ;
  input [26:0]in7;
  input DSP_ALU_INST_6;
  input [0:0]\out7[17] ;
  input [26:0]in8;
  input DSP_ALU_INST_7;
  input [0:0]\out8[17] ;
  input [26:0]in9;
  input DSP_ALU_INST_8;
  input [0:0]\out9[17] ;
  input [26:0]in10;
  input DSP_ALU_INST_9;
  input [0:0]\out10[17] ;
  input [26:0]in11;
  input DSP_ALU_INST_10;
  input [0:0]\out11[17] ;
  input [26:0]in12;
  input DSP_ALU_INST_11;
  input [0:0]\out12[17] ;
  input [26:0]in13;
  input DSP_ALU_INST_12;
  input [0:0]\out13[17] ;
  input [26:0]in14;
  input DSP_ALU_INST_13;
  input [0:0]\out14[17] ;
  input [26:0]in15;
  input DSP_ALU_INST_14;
  input [0:0]\out15[17] ;
  input [26:0]in16;
  input DSP_ALU_INST_15;
  input [0:0]\out16[17] ;
  input [26:0]in17;
  input DSP_ALU_INST_16;
  input [0:0]\out17[17] ;
  input [26:0]in18;
  input DSP_ALU_INST_17;
  input [0:0]\out18[17] ;
  input [26:0]in19;
  input DSP_ALU_INST_18;
  input [0:0]\out19[17] ;
  input [26:0]in20;
  input DSP_ALU_INST_19;
  input [0:0]\out20[17] ;
  input [26:0]in21;
  input DSP_ALU_INST_20;
  input [0:0]\out21[17] ;
  input [26:0]in22;
  input DSP_ALU_INST_21;
  input [0:0]\out22[17] ;
  input [26:0]in23;
  input DSP_ALU_INST_22;
  input [0:0]\out23[17] ;
  input [26:0]in24;
  input CEB2;
  input [0:0]\out24[17] ;
  input [26:0]in25;
  input DSP_ALU_INST_23;
  input [0:0]\out25[17] ;
  input [26:0]in26;
  input DSP_ALU_INST_24;
  input [0:0]\out26[17] ;
  input [26:0]in27;
  input DSP_ALU_INST_25;
  input [0:0]\out27[17] ;
  input [26:0]in28;
  input DSP_ALU_INST_26;
  input [0:0]\out28[17] ;
  input [26:0]in29;
  input DSP_ALU_INST_27;
  input [0:0]\out29[17] ;
  input [26:0]in30;
  input DSP_ALU_INST_28;
  input [0:0]\out30[17] ;
  input [26:0]in31;
  input DSP_ALU_INST_29;
  input [0:0]\out31[17] ;

  wire [26:1]A;
  wire AXI4_Lite_ACLK;
  wire [16:0]AXI_pu_conv_in31;
  wire [26:1]A__0;
  wire [26:1]A__1;
  wire [26:1]A__10;
  wire [26:1]A__11;
  wire [26:1]A__12;
  wire [26:1]A__13;
  wire [26:1]A__14;
  wire [26:1]A__15;
  wire [26:1]A__16;
  wire [26:1]A__17;
  wire [26:1]A__18;
  wire [26:1]A__19;
  wire [26:1]A__2;
  wire [26:1]A__20;
  wire [26:1]A__21;
  wire [26:1]A__22;
  wire [26:1]A__23;
  wire [26:1]A__24;
  wire [26:1]A__25;
  wire [26:1]A__26;
  wire [26:1]A__27;
  wire [26:1]A__28;
  wire [26:1]A__29;
  wire [26:1]A__3;
  wire [26:1]A__30;
  wire [26:1]A__4;
  wire [26:1]A__5;
  wire [26:1]A__6;
  wire [26:1]A__7;
  wire [26:1]A__8;
  wire [26:1]A__9;
  wire CEB2;
  wire DSP_ALU_INST;
  wire DSP_ALU_INST_0;
  wire DSP_ALU_INST_1;
  wire DSP_ALU_INST_10;
  wire DSP_ALU_INST_11;
  wire DSP_ALU_INST_12;
  wire DSP_ALU_INST_13;
  wire DSP_ALU_INST_14;
  wire DSP_ALU_INST_15;
  wire DSP_ALU_INST_16;
  wire DSP_ALU_INST_17;
  wire DSP_ALU_INST_18;
  wire DSP_ALU_INST_19;
  wire DSP_ALU_INST_2;
  wire DSP_ALU_INST_20;
  wire DSP_ALU_INST_21;
  wire DSP_ALU_INST_22;
  wire DSP_ALU_INST_23;
  wire DSP_ALU_INST_24;
  wire DSP_ALU_INST_25;
  wire DSP_ALU_INST_26;
  wire DSP_ALU_INST_27;
  wire DSP_ALU_INST_28;
  wire DSP_ALU_INST_29;
  wire DSP_ALU_INST_3;
  wire DSP_ALU_INST_4;
  wire DSP_ALU_INST_5;
  wire DSP_ALU_INST_6;
  wire DSP_ALU_INST_7;
  wire DSP_ALU_INST_8;
  wire DSP_ALU_INST_9;
  wire [26:0]Delay10_out1;
  wire [26:0]Delay11_out1;
  wire [26:0]Delay12_out1;
  wire [26:0]Delay13_out1;
  wire [26:0]Delay14_out1;
  wire [26:0]Delay15_out1;
  wire [26:0]Delay16_out1;
  wire [26:0]Delay17_out1;
  wire [26:0]Delay18_out1;
  wire [26:0]Delay19_out1;
  wire [26:0]Delay1_out1;
  wire [26:0]Delay20_out1;
  wire [26:0]Delay21_out1;
  wire [26:0]Delay22_out1;
  wire [26:0]Delay23_out1;
  wire [26:0]Delay24_out1;
  wire [26:0]Delay25_out1;
  wire [26:0]Delay26_out1;
  wire [26:0]Delay27_out1;
  wire [26:0]Delay28_out1;
  wire [26:0]Delay29_out1;
  wire [26:0]Delay2_out1;
  wire [26:0]Delay30_out1;
  wire [26:0]Delay31_out1;
  wire [26:0]Delay3_out1;
  wire [26:0]Delay4_out1;
  wire [26:0]Delay5_out1;
  wire [26:0]Delay6_out1;
  wire [26:0]Delay7_out1;
  wire [26:0]Delay8_out1;
  wire [26:0]Delay9_out1;
  wire [26:0]Delay_out1;
  wire IPCORE_CLK;
  wire [0:0]OPMODE;
  wire adc_trigger;
  wire [26:0]in0;
  wire [26:0]in1;
  wire [26:0]in10;
  wire [26:0]in11;
  wire [26:0]in12;
  wire [26:0]in13;
  wire [26:0]in14;
  wire [26:0]in15;
  wire [26:0]in16;
  wire [26:0]in17;
  wire [26:0]in18;
  wire [26:0]in19;
  wire [26:0]in2;
  wire [26:0]in20;
  wire [26:0]in21;
  wire [26:0]in22;
  wire [26:0]in23;
  wire [26:0]in24;
  wire [26:0]in25;
  wire [26:0]in26;
  wire [26:0]in27;
  wire [26:0]in28;
  wire [26:0]in29;
  wire [26:0]in3;
  wire [26:0]in30;
  wire [26:0]in31;
  wire [26:0]in4;
  wire [26:0]in5;
  wire [26:0]in6;
  wire [26:0]in7;
  wire [26:0]in8;
  wire [26:0]in9;
  wire [17:0]out0;
  wire [17:0]out1;
  wire [17:0]out10;
  wire [0:0]\out10[17] ;
  wire [17:0]out11;
  wire [0:0]\out11[17] ;
  wire [17:0]out12;
  wire [0:0]\out12[17] ;
  wire [17:0]out13;
  wire [0:0]\out13[17] ;
  wire [17:0]out14;
  wire [0:0]\out14[17] ;
  wire [17:0]out15;
  wire [0:0]\out15[17] ;
  wire [17:0]out16;
  wire [0:0]\out16[17] ;
  wire [17:0]out17;
  wire [0:0]\out17[17] ;
  wire [17:0]out18;
  wire [0:0]\out18[17] ;
  wire [17:0]out19;
  wire [0:0]\out19[17] ;
  wire [0:0]\out1[17] ;
  wire [17:0]out2;
  wire [17:0]out20;
  wire [0:0]\out20[17] ;
  wire [17:0]out21;
  wire [0:0]\out21[17] ;
  wire [17:0]out22;
  wire [0:0]\out22[17] ;
  wire [17:0]out23;
  wire [0:0]\out23[17] ;
  wire [17:0]out24;
  wire [0:0]\out24[17] ;
  wire [17:0]out25;
  wire [0:0]\out25[17] ;
  wire [17:0]out26;
  wire [0:0]\out26[17] ;
  wire [17:0]out27;
  wire [0:0]\out27[17] ;
  wire [17:0]out28;
  wire [0:0]\out28[17] ;
  wire [17:0]out29;
  wire [0:0]\out29[17] ;
  wire [0:0]\out2[17] ;
  wire [17:0]out3;
  wire [17:0]out30;
  wire [0:0]\out30[17] ;
  wire [17:0]out31;
  wire [0:0]\out31[17] ;
  wire [0:0]\out3[17] ;
  wire [17:0]out4;
  wire [0:0]\out4[17] ;
  wire [17:0]out5;
  wire [0:0]\out5[17] ;
  wire [17:0]out6;
  wire [0:0]\out6[17] ;
  wire [17:0]out7;
  wire [0:0]\out7[17] ;
  wire [17:0]out8;
  wire [0:0]\out8[17] ;
  wire [17:0]out9;
  wire [0:0]\out9[17] ;
  wire p_1_out__0_i_28_n_0;
  wire p_1_out__0_n_100;
  wire p_1_out__0_n_101;
  wire p_1_out__0_n_102;
  wire p_1_out__0_n_103;
  wire p_1_out__0_n_104;
  wire p_1_out__0_n_105;
  wire p_1_out__0_n_61;
  wire p_1_out__0_n_62;
  wire p_1_out__0_n_63;
  wire p_1_out__0_n_64;
  wire p_1_out__0_n_65;
  wire p_1_out__0_n_66;
  wire p_1_out__0_n_67;
  wire p_1_out__0_n_68;
  wire p_1_out__0_n_69;
  wire p_1_out__0_n_70;
  wire p_1_out__0_n_89;
  wire p_1_out__0_n_90;
  wire p_1_out__0_n_91;
  wire p_1_out__0_n_92;
  wire p_1_out__0_n_93;
  wire p_1_out__0_n_94;
  wire p_1_out__0_n_95;
  wire p_1_out__0_n_96;
  wire p_1_out__0_n_97;
  wire p_1_out__0_n_98;
  wire p_1_out__0_n_99;
  wire p_1_out__10_i_28_n_0;
  wire p_1_out__10_n_100;
  wire p_1_out__10_n_101;
  wire p_1_out__10_n_102;
  wire p_1_out__10_n_103;
  wire p_1_out__10_n_104;
  wire p_1_out__10_n_105;
  wire p_1_out__10_n_61;
  wire p_1_out__10_n_62;
  wire p_1_out__10_n_63;
  wire p_1_out__10_n_64;
  wire p_1_out__10_n_65;
  wire p_1_out__10_n_66;
  wire p_1_out__10_n_67;
  wire p_1_out__10_n_68;
  wire p_1_out__10_n_69;
  wire p_1_out__10_n_70;
  wire p_1_out__10_n_89;
  wire p_1_out__10_n_90;
  wire p_1_out__10_n_91;
  wire p_1_out__10_n_92;
  wire p_1_out__10_n_93;
  wire p_1_out__10_n_94;
  wire p_1_out__10_n_95;
  wire p_1_out__10_n_96;
  wire p_1_out__10_n_97;
  wire p_1_out__10_n_98;
  wire p_1_out__10_n_99;
  wire p_1_out__11_i_28_n_0;
  wire p_1_out__11_n_100;
  wire p_1_out__11_n_101;
  wire p_1_out__11_n_102;
  wire p_1_out__11_n_103;
  wire p_1_out__11_n_104;
  wire p_1_out__11_n_105;
  wire p_1_out__11_n_61;
  wire p_1_out__11_n_62;
  wire p_1_out__11_n_63;
  wire p_1_out__11_n_64;
  wire p_1_out__11_n_65;
  wire p_1_out__11_n_66;
  wire p_1_out__11_n_67;
  wire p_1_out__11_n_68;
  wire p_1_out__11_n_69;
  wire p_1_out__11_n_70;
  wire p_1_out__11_n_89;
  wire p_1_out__11_n_90;
  wire p_1_out__11_n_91;
  wire p_1_out__11_n_92;
  wire p_1_out__11_n_93;
  wire p_1_out__11_n_94;
  wire p_1_out__11_n_95;
  wire p_1_out__11_n_96;
  wire p_1_out__11_n_97;
  wire p_1_out__11_n_98;
  wire p_1_out__11_n_99;
  wire p_1_out__12_i_28_n_0;
  wire p_1_out__12_n_100;
  wire p_1_out__12_n_101;
  wire p_1_out__12_n_102;
  wire p_1_out__12_n_103;
  wire p_1_out__12_n_104;
  wire p_1_out__12_n_105;
  wire p_1_out__12_n_61;
  wire p_1_out__12_n_62;
  wire p_1_out__12_n_63;
  wire p_1_out__12_n_64;
  wire p_1_out__12_n_65;
  wire p_1_out__12_n_66;
  wire p_1_out__12_n_67;
  wire p_1_out__12_n_68;
  wire p_1_out__12_n_69;
  wire p_1_out__12_n_70;
  wire p_1_out__12_n_89;
  wire p_1_out__12_n_90;
  wire p_1_out__12_n_91;
  wire p_1_out__12_n_92;
  wire p_1_out__12_n_93;
  wire p_1_out__12_n_94;
  wire p_1_out__12_n_95;
  wire p_1_out__12_n_96;
  wire p_1_out__12_n_97;
  wire p_1_out__12_n_98;
  wire p_1_out__12_n_99;
  wire p_1_out__13_i_28_n_0;
  wire p_1_out__13_n_100;
  wire p_1_out__13_n_101;
  wire p_1_out__13_n_102;
  wire p_1_out__13_n_103;
  wire p_1_out__13_n_104;
  wire p_1_out__13_n_105;
  wire p_1_out__13_n_61;
  wire p_1_out__13_n_62;
  wire p_1_out__13_n_63;
  wire p_1_out__13_n_64;
  wire p_1_out__13_n_65;
  wire p_1_out__13_n_66;
  wire p_1_out__13_n_67;
  wire p_1_out__13_n_68;
  wire p_1_out__13_n_69;
  wire p_1_out__13_n_70;
  wire p_1_out__13_n_89;
  wire p_1_out__13_n_90;
  wire p_1_out__13_n_91;
  wire p_1_out__13_n_92;
  wire p_1_out__13_n_93;
  wire p_1_out__13_n_94;
  wire p_1_out__13_n_95;
  wire p_1_out__13_n_96;
  wire p_1_out__13_n_97;
  wire p_1_out__13_n_98;
  wire p_1_out__13_n_99;
  wire p_1_out__14_i_28_n_0;
  wire p_1_out__14_n_100;
  wire p_1_out__14_n_101;
  wire p_1_out__14_n_102;
  wire p_1_out__14_n_103;
  wire p_1_out__14_n_104;
  wire p_1_out__14_n_105;
  wire p_1_out__14_n_61;
  wire p_1_out__14_n_62;
  wire p_1_out__14_n_63;
  wire p_1_out__14_n_64;
  wire p_1_out__14_n_65;
  wire p_1_out__14_n_66;
  wire p_1_out__14_n_67;
  wire p_1_out__14_n_68;
  wire p_1_out__14_n_69;
  wire p_1_out__14_n_70;
  wire p_1_out__14_n_89;
  wire p_1_out__14_n_90;
  wire p_1_out__14_n_91;
  wire p_1_out__14_n_92;
  wire p_1_out__14_n_93;
  wire p_1_out__14_n_94;
  wire p_1_out__14_n_95;
  wire p_1_out__14_n_96;
  wire p_1_out__14_n_97;
  wire p_1_out__14_n_98;
  wire p_1_out__14_n_99;
  wire p_1_out__15_i_28_n_0;
  wire p_1_out__15_n_100;
  wire p_1_out__15_n_101;
  wire p_1_out__15_n_102;
  wire p_1_out__15_n_103;
  wire p_1_out__15_n_104;
  wire p_1_out__15_n_105;
  wire p_1_out__15_n_61;
  wire p_1_out__15_n_62;
  wire p_1_out__15_n_63;
  wire p_1_out__15_n_64;
  wire p_1_out__15_n_65;
  wire p_1_out__15_n_66;
  wire p_1_out__15_n_67;
  wire p_1_out__15_n_68;
  wire p_1_out__15_n_69;
  wire p_1_out__15_n_70;
  wire p_1_out__15_n_89;
  wire p_1_out__15_n_90;
  wire p_1_out__15_n_91;
  wire p_1_out__15_n_92;
  wire p_1_out__15_n_93;
  wire p_1_out__15_n_94;
  wire p_1_out__15_n_95;
  wire p_1_out__15_n_96;
  wire p_1_out__15_n_97;
  wire p_1_out__15_n_98;
  wire p_1_out__15_n_99;
  wire p_1_out__16_i_28_n_0;
  wire p_1_out__16_n_100;
  wire p_1_out__16_n_101;
  wire p_1_out__16_n_102;
  wire p_1_out__16_n_103;
  wire p_1_out__16_n_104;
  wire p_1_out__16_n_105;
  wire p_1_out__16_n_61;
  wire p_1_out__16_n_62;
  wire p_1_out__16_n_63;
  wire p_1_out__16_n_64;
  wire p_1_out__16_n_65;
  wire p_1_out__16_n_66;
  wire p_1_out__16_n_67;
  wire p_1_out__16_n_68;
  wire p_1_out__16_n_69;
  wire p_1_out__16_n_70;
  wire p_1_out__16_n_89;
  wire p_1_out__16_n_90;
  wire p_1_out__16_n_91;
  wire p_1_out__16_n_92;
  wire p_1_out__16_n_93;
  wire p_1_out__16_n_94;
  wire p_1_out__16_n_95;
  wire p_1_out__16_n_96;
  wire p_1_out__16_n_97;
  wire p_1_out__16_n_98;
  wire p_1_out__16_n_99;
  wire p_1_out__17_i_28_n_0;
  wire p_1_out__17_n_100;
  wire p_1_out__17_n_101;
  wire p_1_out__17_n_102;
  wire p_1_out__17_n_103;
  wire p_1_out__17_n_104;
  wire p_1_out__17_n_105;
  wire p_1_out__17_n_61;
  wire p_1_out__17_n_62;
  wire p_1_out__17_n_63;
  wire p_1_out__17_n_64;
  wire p_1_out__17_n_65;
  wire p_1_out__17_n_66;
  wire p_1_out__17_n_67;
  wire p_1_out__17_n_68;
  wire p_1_out__17_n_69;
  wire p_1_out__17_n_70;
  wire p_1_out__17_n_89;
  wire p_1_out__17_n_90;
  wire p_1_out__17_n_91;
  wire p_1_out__17_n_92;
  wire p_1_out__17_n_93;
  wire p_1_out__17_n_94;
  wire p_1_out__17_n_95;
  wire p_1_out__17_n_96;
  wire p_1_out__17_n_97;
  wire p_1_out__17_n_98;
  wire p_1_out__17_n_99;
  wire p_1_out__18_i_28_n_0;
  wire p_1_out__18_n_100;
  wire p_1_out__18_n_101;
  wire p_1_out__18_n_102;
  wire p_1_out__18_n_103;
  wire p_1_out__18_n_104;
  wire p_1_out__18_n_105;
  wire p_1_out__18_n_61;
  wire p_1_out__18_n_62;
  wire p_1_out__18_n_63;
  wire p_1_out__18_n_64;
  wire p_1_out__18_n_65;
  wire p_1_out__18_n_66;
  wire p_1_out__18_n_67;
  wire p_1_out__18_n_68;
  wire p_1_out__18_n_69;
  wire p_1_out__18_n_70;
  wire p_1_out__18_n_89;
  wire p_1_out__18_n_90;
  wire p_1_out__18_n_91;
  wire p_1_out__18_n_92;
  wire p_1_out__18_n_93;
  wire p_1_out__18_n_94;
  wire p_1_out__18_n_95;
  wire p_1_out__18_n_96;
  wire p_1_out__18_n_97;
  wire p_1_out__18_n_98;
  wire p_1_out__18_n_99;
  wire p_1_out__19_i_28_n_0;
  wire p_1_out__19_n_100;
  wire p_1_out__19_n_101;
  wire p_1_out__19_n_102;
  wire p_1_out__19_n_103;
  wire p_1_out__19_n_104;
  wire p_1_out__19_n_105;
  wire p_1_out__19_n_61;
  wire p_1_out__19_n_62;
  wire p_1_out__19_n_63;
  wire p_1_out__19_n_64;
  wire p_1_out__19_n_65;
  wire p_1_out__19_n_66;
  wire p_1_out__19_n_67;
  wire p_1_out__19_n_68;
  wire p_1_out__19_n_69;
  wire p_1_out__19_n_70;
  wire p_1_out__19_n_89;
  wire p_1_out__19_n_90;
  wire p_1_out__19_n_91;
  wire p_1_out__19_n_92;
  wire p_1_out__19_n_93;
  wire p_1_out__19_n_94;
  wire p_1_out__19_n_95;
  wire p_1_out__19_n_96;
  wire p_1_out__19_n_97;
  wire p_1_out__19_n_98;
  wire p_1_out__19_n_99;
  wire p_1_out__1_i_28_n_0;
  wire p_1_out__1_n_100;
  wire p_1_out__1_n_101;
  wire p_1_out__1_n_102;
  wire p_1_out__1_n_103;
  wire p_1_out__1_n_104;
  wire p_1_out__1_n_105;
  wire p_1_out__1_n_61;
  wire p_1_out__1_n_62;
  wire p_1_out__1_n_63;
  wire p_1_out__1_n_64;
  wire p_1_out__1_n_65;
  wire p_1_out__1_n_66;
  wire p_1_out__1_n_67;
  wire p_1_out__1_n_68;
  wire p_1_out__1_n_69;
  wire p_1_out__1_n_70;
  wire p_1_out__1_n_89;
  wire p_1_out__1_n_90;
  wire p_1_out__1_n_91;
  wire p_1_out__1_n_92;
  wire p_1_out__1_n_93;
  wire p_1_out__1_n_94;
  wire p_1_out__1_n_95;
  wire p_1_out__1_n_96;
  wire p_1_out__1_n_97;
  wire p_1_out__1_n_98;
  wire p_1_out__1_n_99;
  wire p_1_out__20_i_28_n_0;
  wire p_1_out__20_n_100;
  wire p_1_out__20_n_101;
  wire p_1_out__20_n_102;
  wire p_1_out__20_n_103;
  wire p_1_out__20_n_104;
  wire p_1_out__20_n_105;
  wire p_1_out__20_n_61;
  wire p_1_out__20_n_62;
  wire p_1_out__20_n_63;
  wire p_1_out__20_n_64;
  wire p_1_out__20_n_65;
  wire p_1_out__20_n_66;
  wire p_1_out__20_n_67;
  wire p_1_out__20_n_68;
  wire p_1_out__20_n_69;
  wire p_1_out__20_n_70;
  wire p_1_out__20_n_89;
  wire p_1_out__20_n_90;
  wire p_1_out__20_n_91;
  wire p_1_out__20_n_92;
  wire p_1_out__20_n_93;
  wire p_1_out__20_n_94;
  wire p_1_out__20_n_95;
  wire p_1_out__20_n_96;
  wire p_1_out__20_n_97;
  wire p_1_out__20_n_98;
  wire p_1_out__20_n_99;
  wire p_1_out__21_i_28_n_0;
  wire p_1_out__21_n_100;
  wire p_1_out__21_n_101;
  wire p_1_out__21_n_102;
  wire p_1_out__21_n_103;
  wire p_1_out__21_n_104;
  wire p_1_out__21_n_105;
  wire p_1_out__21_n_61;
  wire p_1_out__21_n_62;
  wire p_1_out__21_n_63;
  wire p_1_out__21_n_64;
  wire p_1_out__21_n_65;
  wire p_1_out__21_n_66;
  wire p_1_out__21_n_67;
  wire p_1_out__21_n_68;
  wire p_1_out__21_n_69;
  wire p_1_out__21_n_70;
  wire p_1_out__21_n_89;
  wire p_1_out__21_n_90;
  wire p_1_out__21_n_91;
  wire p_1_out__21_n_92;
  wire p_1_out__21_n_93;
  wire p_1_out__21_n_94;
  wire p_1_out__21_n_95;
  wire p_1_out__21_n_96;
  wire p_1_out__21_n_97;
  wire p_1_out__21_n_98;
  wire p_1_out__21_n_99;
  wire p_1_out__22_i_28_n_0;
  wire p_1_out__22_n_100;
  wire p_1_out__22_n_101;
  wire p_1_out__22_n_102;
  wire p_1_out__22_n_103;
  wire p_1_out__22_n_104;
  wire p_1_out__22_n_105;
  wire p_1_out__22_n_61;
  wire p_1_out__22_n_62;
  wire p_1_out__22_n_63;
  wire p_1_out__22_n_64;
  wire p_1_out__22_n_65;
  wire p_1_out__22_n_66;
  wire p_1_out__22_n_67;
  wire p_1_out__22_n_68;
  wire p_1_out__22_n_69;
  wire p_1_out__22_n_70;
  wire p_1_out__22_n_89;
  wire p_1_out__22_n_90;
  wire p_1_out__22_n_91;
  wire p_1_out__22_n_92;
  wire p_1_out__22_n_93;
  wire p_1_out__22_n_94;
  wire p_1_out__22_n_95;
  wire p_1_out__22_n_96;
  wire p_1_out__22_n_97;
  wire p_1_out__22_n_98;
  wire p_1_out__22_n_99;
  wire p_1_out__23_i_28_n_0;
  wire p_1_out__23_n_100;
  wire p_1_out__23_n_101;
  wire p_1_out__23_n_102;
  wire p_1_out__23_n_103;
  wire p_1_out__23_n_104;
  wire p_1_out__23_n_105;
  wire p_1_out__23_n_61;
  wire p_1_out__23_n_62;
  wire p_1_out__23_n_63;
  wire p_1_out__23_n_64;
  wire p_1_out__23_n_65;
  wire p_1_out__23_n_66;
  wire p_1_out__23_n_67;
  wire p_1_out__23_n_68;
  wire p_1_out__23_n_69;
  wire p_1_out__23_n_70;
  wire p_1_out__23_n_89;
  wire p_1_out__23_n_90;
  wire p_1_out__23_n_91;
  wire p_1_out__23_n_92;
  wire p_1_out__23_n_93;
  wire p_1_out__23_n_94;
  wire p_1_out__23_n_95;
  wire p_1_out__23_n_96;
  wire p_1_out__23_n_97;
  wire p_1_out__23_n_98;
  wire p_1_out__23_n_99;
  wire p_1_out__24_i_28_n_0;
  wire p_1_out__24_n_100;
  wire p_1_out__24_n_101;
  wire p_1_out__24_n_102;
  wire p_1_out__24_n_103;
  wire p_1_out__24_n_104;
  wire p_1_out__24_n_105;
  wire p_1_out__24_n_61;
  wire p_1_out__24_n_62;
  wire p_1_out__24_n_63;
  wire p_1_out__24_n_64;
  wire p_1_out__24_n_65;
  wire p_1_out__24_n_66;
  wire p_1_out__24_n_67;
  wire p_1_out__24_n_68;
  wire p_1_out__24_n_69;
  wire p_1_out__24_n_70;
  wire p_1_out__24_n_89;
  wire p_1_out__24_n_90;
  wire p_1_out__24_n_91;
  wire p_1_out__24_n_92;
  wire p_1_out__24_n_93;
  wire p_1_out__24_n_94;
  wire p_1_out__24_n_95;
  wire p_1_out__24_n_96;
  wire p_1_out__24_n_97;
  wire p_1_out__24_n_98;
  wire p_1_out__24_n_99;
  wire p_1_out__25_i_28_n_0;
  wire p_1_out__25_n_100;
  wire p_1_out__25_n_101;
  wire p_1_out__25_n_102;
  wire p_1_out__25_n_103;
  wire p_1_out__25_n_104;
  wire p_1_out__25_n_105;
  wire p_1_out__25_n_61;
  wire p_1_out__25_n_62;
  wire p_1_out__25_n_63;
  wire p_1_out__25_n_64;
  wire p_1_out__25_n_65;
  wire p_1_out__25_n_66;
  wire p_1_out__25_n_67;
  wire p_1_out__25_n_68;
  wire p_1_out__25_n_69;
  wire p_1_out__25_n_70;
  wire p_1_out__25_n_89;
  wire p_1_out__25_n_90;
  wire p_1_out__25_n_91;
  wire p_1_out__25_n_92;
  wire p_1_out__25_n_93;
  wire p_1_out__25_n_94;
  wire p_1_out__25_n_95;
  wire p_1_out__25_n_96;
  wire p_1_out__25_n_97;
  wire p_1_out__25_n_98;
  wire p_1_out__25_n_99;
  wire p_1_out__26_i_28_n_0;
  wire p_1_out__26_n_100;
  wire p_1_out__26_n_101;
  wire p_1_out__26_n_102;
  wire p_1_out__26_n_103;
  wire p_1_out__26_n_104;
  wire p_1_out__26_n_105;
  wire p_1_out__26_n_61;
  wire p_1_out__26_n_62;
  wire p_1_out__26_n_63;
  wire p_1_out__26_n_64;
  wire p_1_out__26_n_65;
  wire p_1_out__26_n_66;
  wire p_1_out__26_n_67;
  wire p_1_out__26_n_68;
  wire p_1_out__26_n_69;
  wire p_1_out__26_n_70;
  wire p_1_out__26_n_89;
  wire p_1_out__26_n_90;
  wire p_1_out__26_n_91;
  wire p_1_out__26_n_92;
  wire p_1_out__26_n_93;
  wire p_1_out__26_n_94;
  wire p_1_out__26_n_95;
  wire p_1_out__26_n_96;
  wire p_1_out__26_n_97;
  wire p_1_out__26_n_98;
  wire p_1_out__26_n_99;
  wire p_1_out__27_i_28_n_0;
  wire p_1_out__27_n_100;
  wire p_1_out__27_n_101;
  wire p_1_out__27_n_102;
  wire p_1_out__27_n_103;
  wire p_1_out__27_n_104;
  wire p_1_out__27_n_105;
  wire p_1_out__27_n_61;
  wire p_1_out__27_n_62;
  wire p_1_out__27_n_63;
  wire p_1_out__27_n_64;
  wire p_1_out__27_n_65;
  wire p_1_out__27_n_66;
  wire p_1_out__27_n_67;
  wire p_1_out__27_n_68;
  wire p_1_out__27_n_69;
  wire p_1_out__27_n_70;
  wire p_1_out__27_n_89;
  wire p_1_out__27_n_90;
  wire p_1_out__27_n_91;
  wire p_1_out__27_n_92;
  wire p_1_out__27_n_93;
  wire p_1_out__27_n_94;
  wire p_1_out__27_n_95;
  wire p_1_out__27_n_96;
  wire p_1_out__27_n_97;
  wire p_1_out__27_n_98;
  wire p_1_out__27_n_99;
  wire p_1_out__28_i_28_n_0;
  wire p_1_out__28_n_100;
  wire p_1_out__28_n_101;
  wire p_1_out__28_n_102;
  wire p_1_out__28_n_103;
  wire p_1_out__28_n_104;
  wire p_1_out__28_n_105;
  wire p_1_out__28_n_61;
  wire p_1_out__28_n_62;
  wire p_1_out__28_n_63;
  wire p_1_out__28_n_64;
  wire p_1_out__28_n_65;
  wire p_1_out__28_n_66;
  wire p_1_out__28_n_67;
  wire p_1_out__28_n_68;
  wire p_1_out__28_n_69;
  wire p_1_out__28_n_70;
  wire p_1_out__28_n_89;
  wire p_1_out__28_n_90;
  wire p_1_out__28_n_91;
  wire p_1_out__28_n_92;
  wire p_1_out__28_n_93;
  wire p_1_out__28_n_94;
  wire p_1_out__28_n_95;
  wire p_1_out__28_n_96;
  wire p_1_out__28_n_97;
  wire p_1_out__28_n_98;
  wire p_1_out__28_n_99;
  wire p_1_out__29_i_28_n_0;
  wire p_1_out__29_n_100;
  wire p_1_out__29_n_101;
  wire p_1_out__29_n_102;
  wire p_1_out__29_n_103;
  wire p_1_out__29_n_104;
  wire p_1_out__29_n_105;
  wire p_1_out__29_n_61;
  wire p_1_out__29_n_62;
  wire p_1_out__29_n_63;
  wire p_1_out__29_n_64;
  wire p_1_out__29_n_65;
  wire p_1_out__29_n_66;
  wire p_1_out__29_n_67;
  wire p_1_out__29_n_68;
  wire p_1_out__29_n_69;
  wire p_1_out__29_n_70;
  wire p_1_out__29_n_89;
  wire p_1_out__29_n_90;
  wire p_1_out__29_n_91;
  wire p_1_out__29_n_92;
  wire p_1_out__29_n_93;
  wire p_1_out__29_n_94;
  wire p_1_out__29_n_95;
  wire p_1_out__29_n_96;
  wire p_1_out__29_n_97;
  wire p_1_out__29_n_98;
  wire p_1_out__29_n_99;
  wire p_1_out__2_i_28_n_0;
  wire p_1_out__2_n_100;
  wire p_1_out__2_n_101;
  wire p_1_out__2_n_102;
  wire p_1_out__2_n_103;
  wire p_1_out__2_n_104;
  wire p_1_out__2_n_105;
  wire p_1_out__2_n_61;
  wire p_1_out__2_n_62;
  wire p_1_out__2_n_63;
  wire p_1_out__2_n_64;
  wire p_1_out__2_n_65;
  wire p_1_out__2_n_66;
  wire p_1_out__2_n_67;
  wire p_1_out__2_n_68;
  wire p_1_out__2_n_69;
  wire p_1_out__2_n_70;
  wire p_1_out__2_n_89;
  wire p_1_out__2_n_90;
  wire p_1_out__2_n_91;
  wire p_1_out__2_n_92;
  wire p_1_out__2_n_93;
  wire p_1_out__2_n_94;
  wire p_1_out__2_n_95;
  wire p_1_out__2_n_96;
  wire p_1_out__2_n_97;
  wire p_1_out__2_n_98;
  wire p_1_out__2_n_99;
  wire p_1_out__30_i_28_n_0;
  wire p_1_out__30_n_100;
  wire p_1_out__30_n_101;
  wire p_1_out__30_n_102;
  wire p_1_out__30_n_103;
  wire p_1_out__30_n_104;
  wire p_1_out__30_n_105;
  wire p_1_out__30_n_61;
  wire p_1_out__30_n_62;
  wire p_1_out__30_n_63;
  wire p_1_out__30_n_64;
  wire p_1_out__30_n_65;
  wire p_1_out__30_n_66;
  wire p_1_out__30_n_67;
  wire p_1_out__30_n_68;
  wire p_1_out__30_n_69;
  wire p_1_out__30_n_70;
  wire p_1_out__30_n_89;
  wire p_1_out__30_n_90;
  wire p_1_out__30_n_91;
  wire p_1_out__30_n_92;
  wire p_1_out__30_n_93;
  wire p_1_out__30_n_94;
  wire p_1_out__30_n_95;
  wire p_1_out__30_n_96;
  wire p_1_out__30_n_97;
  wire p_1_out__30_n_98;
  wire p_1_out__30_n_99;
  wire p_1_out__3_i_28_n_0;
  wire p_1_out__3_n_100;
  wire p_1_out__3_n_101;
  wire p_1_out__3_n_102;
  wire p_1_out__3_n_103;
  wire p_1_out__3_n_104;
  wire p_1_out__3_n_105;
  wire p_1_out__3_n_61;
  wire p_1_out__3_n_62;
  wire p_1_out__3_n_63;
  wire p_1_out__3_n_64;
  wire p_1_out__3_n_65;
  wire p_1_out__3_n_66;
  wire p_1_out__3_n_67;
  wire p_1_out__3_n_68;
  wire p_1_out__3_n_69;
  wire p_1_out__3_n_70;
  wire p_1_out__3_n_89;
  wire p_1_out__3_n_90;
  wire p_1_out__3_n_91;
  wire p_1_out__3_n_92;
  wire p_1_out__3_n_93;
  wire p_1_out__3_n_94;
  wire p_1_out__3_n_95;
  wire p_1_out__3_n_96;
  wire p_1_out__3_n_97;
  wire p_1_out__3_n_98;
  wire p_1_out__3_n_99;
  wire p_1_out__4_i_28_n_0;
  wire p_1_out__4_n_100;
  wire p_1_out__4_n_101;
  wire p_1_out__4_n_102;
  wire p_1_out__4_n_103;
  wire p_1_out__4_n_104;
  wire p_1_out__4_n_105;
  wire p_1_out__4_n_61;
  wire p_1_out__4_n_62;
  wire p_1_out__4_n_63;
  wire p_1_out__4_n_64;
  wire p_1_out__4_n_65;
  wire p_1_out__4_n_66;
  wire p_1_out__4_n_67;
  wire p_1_out__4_n_68;
  wire p_1_out__4_n_69;
  wire p_1_out__4_n_70;
  wire p_1_out__4_n_89;
  wire p_1_out__4_n_90;
  wire p_1_out__4_n_91;
  wire p_1_out__4_n_92;
  wire p_1_out__4_n_93;
  wire p_1_out__4_n_94;
  wire p_1_out__4_n_95;
  wire p_1_out__4_n_96;
  wire p_1_out__4_n_97;
  wire p_1_out__4_n_98;
  wire p_1_out__4_n_99;
  wire p_1_out__5_i_28_n_0;
  wire p_1_out__5_n_100;
  wire p_1_out__5_n_101;
  wire p_1_out__5_n_102;
  wire p_1_out__5_n_103;
  wire p_1_out__5_n_104;
  wire p_1_out__5_n_105;
  wire p_1_out__5_n_61;
  wire p_1_out__5_n_62;
  wire p_1_out__5_n_63;
  wire p_1_out__5_n_64;
  wire p_1_out__5_n_65;
  wire p_1_out__5_n_66;
  wire p_1_out__5_n_67;
  wire p_1_out__5_n_68;
  wire p_1_out__5_n_69;
  wire p_1_out__5_n_70;
  wire p_1_out__5_n_89;
  wire p_1_out__5_n_90;
  wire p_1_out__5_n_91;
  wire p_1_out__5_n_92;
  wire p_1_out__5_n_93;
  wire p_1_out__5_n_94;
  wire p_1_out__5_n_95;
  wire p_1_out__5_n_96;
  wire p_1_out__5_n_97;
  wire p_1_out__5_n_98;
  wire p_1_out__5_n_99;
  wire p_1_out__6_i_28_n_0;
  wire p_1_out__6_n_100;
  wire p_1_out__6_n_101;
  wire p_1_out__6_n_102;
  wire p_1_out__6_n_103;
  wire p_1_out__6_n_104;
  wire p_1_out__6_n_105;
  wire p_1_out__6_n_61;
  wire p_1_out__6_n_62;
  wire p_1_out__6_n_63;
  wire p_1_out__6_n_64;
  wire p_1_out__6_n_65;
  wire p_1_out__6_n_66;
  wire p_1_out__6_n_67;
  wire p_1_out__6_n_68;
  wire p_1_out__6_n_69;
  wire p_1_out__6_n_70;
  wire p_1_out__6_n_89;
  wire p_1_out__6_n_90;
  wire p_1_out__6_n_91;
  wire p_1_out__6_n_92;
  wire p_1_out__6_n_93;
  wire p_1_out__6_n_94;
  wire p_1_out__6_n_95;
  wire p_1_out__6_n_96;
  wire p_1_out__6_n_97;
  wire p_1_out__6_n_98;
  wire p_1_out__6_n_99;
  wire p_1_out__7_i_28_n_0;
  wire p_1_out__7_n_100;
  wire p_1_out__7_n_101;
  wire p_1_out__7_n_102;
  wire p_1_out__7_n_103;
  wire p_1_out__7_n_104;
  wire p_1_out__7_n_105;
  wire p_1_out__7_n_61;
  wire p_1_out__7_n_62;
  wire p_1_out__7_n_63;
  wire p_1_out__7_n_64;
  wire p_1_out__7_n_65;
  wire p_1_out__7_n_66;
  wire p_1_out__7_n_67;
  wire p_1_out__7_n_68;
  wire p_1_out__7_n_69;
  wire p_1_out__7_n_70;
  wire p_1_out__7_n_89;
  wire p_1_out__7_n_90;
  wire p_1_out__7_n_91;
  wire p_1_out__7_n_92;
  wire p_1_out__7_n_93;
  wire p_1_out__7_n_94;
  wire p_1_out__7_n_95;
  wire p_1_out__7_n_96;
  wire p_1_out__7_n_97;
  wire p_1_out__7_n_98;
  wire p_1_out__7_n_99;
  wire p_1_out__8_i_28_n_0;
  wire p_1_out__8_n_100;
  wire p_1_out__8_n_101;
  wire p_1_out__8_n_102;
  wire p_1_out__8_n_103;
  wire p_1_out__8_n_104;
  wire p_1_out__8_n_105;
  wire p_1_out__8_n_61;
  wire p_1_out__8_n_62;
  wire p_1_out__8_n_63;
  wire p_1_out__8_n_64;
  wire p_1_out__8_n_65;
  wire p_1_out__8_n_66;
  wire p_1_out__8_n_67;
  wire p_1_out__8_n_68;
  wire p_1_out__8_n_69;
  wire p_1_out__8_n_70;
  wire p_1_out__8_n_89;
  wire p_1_out__8_n_90;
  wire p_1_out__8_n_91;
  wire p_1_out__8_n_92;
  wire p_1_out__8_n_93;
  wire p_1_out__8_n_94;
  wire p_1_out__8_n_95;
  wire p_1_out__8_n_96;
  wire p_1_out__8_n_97;
  wire p_1_out__8_n_98;
  wire p_1_out__8_n_99;
  wire p_1_out__9_i_28_n_0;
  wire p_1_out__9_n_100;
  wire p_1_out__9_n_101;
  wire p_1_out__9_n_102;
  wire p_1_out__9_n_103;
  wire p_1_out__9_n_104;
  wire p_1_out__9_n_105;
  wire p_1_out__9_n_61;
  wire p_1_out__9_n_62;
  wire p_1_out__9_n_63;
  wire p_1_out__9_n_64;
  wire p_1_out__9_n_65;
  wire p_1_out__9_n_66;
  wire p_1_out__9_n_67;
  wire p_1_out__9_n_68;
  wire p_1_out__9_n_69;
  wire p_1_out__9_n_70;
  wire p_1_out__9_n_89;
  wire p_1_out__9_n_90;
  wire p_1_out__9_n_91;
  wire p_1_out__9_n_92;
  wire p_1_out__9_n_93;
  wire p_1_out__9_n_94;
  wire p_1_out__9_n_95;
  wire p_1_out__9_n_96;
  wire p_1_out__9_n_97;
  wire p_1_out__9_n_98;
  wire p_1_out__9_n_99;
  wire p_1_out_i_28_n_0;
  wire p_1_out_n_100;
  wire p_1_out_n_101;
  wire p_1_out_n_102;
  wire p_1_out_n_103;
  wire p_1_out_n_104;
  wire p_1_out_n_105;
  wire p_1_out_n_61;
  wire p_1_out_n_62;
  wire p_1_out_n_63;
  wire p_1_out_n_64;
  wire p_1_out_n_65;
  wire p_1_out_n_66;
  wire p_1_out_n_67;
  wire p_1_out_n_68;
  wire p_1_out_n_69;
  wire p_1_out_n_70;
  wire p_1_out_n_89;
  wire p_1_out_n_90;
  wire p_1_out_n_91;
  wire p_1_out_n_92;
  wire p_1_out_n_93;
  wire p_1_out_n_94;
  wire p_1_out_n_95;
  wire p_1_out_n_96;
  wire p_1_out_n_97;
  wire p_1_out_n_98;
  wire p_1_out_n_99;
  wire reset;
  wire NLW_p_1_out_CARRYCASCOUT_UNCONNECTED;
  wire NLW_p_1_out_MULTSIGNOUT_UNCONNECTED;
  wire NLW_p_1_out_OVERFLOW_UNCONNECTED;
  wire NLW_p_1_out_PATTERNBDETECT_UNCONNECTED;
  wire NLW_p_1_out_PATTERNDETECT_UNCONNECTED;
  wire NLW_p_1_out_UNDERFLOW_UNCONNECTED;
  wire [29:0]NLW_p_1_out_ACOUT_UNCONNECTED;
  wire [17:0]NLW_p_1_out_BCOUT_UNCONNECTED;
  wire [3:0]NLW_p_1_out_CARRYOUT_UNCONNECTED;
  wire [47:45]NLW_p_1_out_P_UNCONNECTED;
  wire [47:0]NLW_p_1_out_PCOUT_UNCONNECTED;
  wire [7:0]NLW_p_1_out_XOROUT_UNCONNECTED;
  wire NLW_p_1_out__0_CARRYCASCOUT_UNCONNECTED;
  wire NLW_p_1_out__0_MULTSIGNOUT_UNCONNECTED;
  wire NLW_p_1_out__0_OVERFLOW_UNCONNECTED;
  wire NLW_p_1_out__0_PATTERNBDETECT_UNCONNECTED;
  wire NLW_p_1_out__0_PATTERNDETECT_UNCONNECTED;
  wire NLW_p_1_out__0_UNDERFLOW_UNCONNECTED;
  wire [29:0]NLW_p_1_out__0_ACOUT_UNCONNECTED;
  wire [17:0]NLW_p_1_out__0_BCOUT_UNCONNECTED;
  wire [3:0]NLW_p_1_out__0_CARRYOUT_UNCONNECTED;
  wire [47:45]NLW_p_1_out__0_P_UNCONNECTED;
  wire [47:0]NLW_p_1_out__0_PCOUT_UNCONNECTED;
  wire [7:0]NLW_p_1_out__0_XOROUT_UNCONNECTED;
  wire NLW_p_1_out__1_CARRYCASCOUT_UNCONNECTED;
  wire NLW_p_1_out__1_MULTSIGNOUT_UNCONNECTED;
  wire NLW_p_1_out__1_OVERFLOW_UNCONNECTED;
  wire NLW_p_1_out__1_PATTERNBDETECT_UNCONNECTED;
  wire NLW_p_1_out__1_PATTERNDETECT_UNCONNECTED;
  wire NLW_p_1_out__1_UNDERFLOW_UNCONNECTED;
  wire [29:0]NLW_p_1_out__1_ACOUT_UNCONNECTED;
  wire [17:0]NLW_p_1_out__1_BCOUT_UNCONNECTED;
  wire [3:0]NLW_p_1_out__1_CARRYOUT_UNCONNECTED;
  wire [47:45]NLW_p_1_out__1_P_UNCONNECTED;
  wire [47:0]NLW_p_1_out__1_PCOUT_UNCONNECTED;
  wire [7:0]NLW_p_1_out__1_XOROUT_UNCONNECTED;
  wire NLW_p_1_out__10_CARRYCASCOUT_UNCONNECTED;
  wire NLW_p_1_out__10_MULTSIGNOUT_UNCONNECTED;
  wire NLW_p_1_out__10_OVERFLOW_UNCONNECTED;
  wire NLW_p_1_out__10_PATTERNBDETECT_UNCONNECTED;
  wire NLW_p_1_out__10_PATTERNDETECT_UNCONNECTED;
  wire NLW_p_1_out__10_UNDERFLOW_UNCONNECTED;
  wire [29:0]NLW_p_1_out__10_ACOUT_UNCONNECTED;
  wire [17:0]NLW_p_1_out__10_BCOUT_UNCONNECTED;
  wire [3:0]NLW_p_1_out__10_CARRYOUT_UNCONNECTED;
  wire [47:45]NLW_p_1_out__10_P_UNCONNECTED;
  wire [47:0]NLW_p_1_out__10_PCOUT_UNCONNECTED;
  wire [7:0]NLW_p_1_out__10_XOROUT_UNCONNECTED;
  wire NLW_p_1_out__11_CARRYCASCOUT_UNCONNECTED;
  wire NLW_p_1_out__11_MULTSIGNOUT_UNCONNECTED;
  wire NLW_p_1_out__11_OVERFLOW_UNCONNECTED;
  wire NLW_p_1_out__11_PATTERNBDETECT_UNCONNECTED;
  wire NLW_p_1_out__11_PATTERNDETECT_UNCONNECTED;
  wire NLW_p_1_out__11_UNDERFLOW_UNCONNECTED;
  wire [29:0]NLW_p_1_out__11_ACOUT_UNCONNECTED;
  wire [17:0]NLW_p_1_out__11_BCOUT_UNCONNECTED;
  wire [3:0]NLW_p_1_out__11_CARRYOUT_UNCONNECTED;
  wire [47:45]NLW_p_1_out__11_P_UNCONNECTED;
  wire [47:0]NLW_p_1_out__11_PCOUT_UNCONNECTED;
  wire [7:0]NLW_p_1_out__11_XOROUT_UNCONNECTED;
  wire NLW_p_1_out__12_CARRYCASCOUT_UNCONNECTED;
  wire NLW_p_1_out__12_MULTSIGNOUT_UNCONNECTED;
  wire NLW_p_1_out__12_OVERFLOW_UNCONNECTED;
  wire NLW_p_1_out__12_PATTERNBDETECT_UNCONNECTED;
  wire NLW_p_1_out__12_PATTERNDETECT_UNCONNECTED;
  wire NLW_p_1_out__12_UNDERFLOW_UNCONNECTED;
  wire [29:0]NLW_p_1_out__12_ACOUT_UNCONNECTED;
  wire [17:0]NLW_p_1_out__12_BCOUT_UNCONNECTED;
  wire [3:0]NLW_p_1_out__12_CARRYOUT_UNCONNECTED;
  wire [47:45]NLW_p_1_out__12_P_UNCONNECTED;
  wire [47:0]NLW_p_1_out__12_PCOUT_UNCONNECTED;
  wire [7:0]NLW_p_1_out__12_XOROUT_UNCONNECTED;
  wire NLW_p_1_out__13_CARRYCASCOUT_UNCONNECTED;
  wire NLW_p_1_out__13_MULTSIGNOUT_UNCONNECTED;
  wire NLW_p_1_out__13_OVERFLOW_UNCONNECTED;
  wire NLW_p_1_out__13_PATTERNBDETECT_UNCONNECTED;
  wire NLW_p_1_out__13_PATTERNDETECT_UNCONNECTED;
  wire NLW_p_1_out__13_UNDERFLOW_UNCONNECTED;
  wire [29:0]NLW_p_1_out__13_ACOUT_UNCONNECTED;
  wire [17:0]NLW_p_1_out__13_BCOUT_UNCONNECTED;
  wire [3:0]NLW_p_1_out__13_CARRYOUT_UNCONNECTED;
  wire [47:45]NLW_p_1_out__13_P_UNCONNECTED;
  wire [47:0]NLW_p_1_out__13_PCOUT_UNCONNECTED;
  wire [7:0]NLW_p_1_out__13_XOROUT_UNCONNECTED;
  wire NLW_p_1_out__14_CARRYCASCOUT_UNCONNECTED;
  wire NLW_p_1_out__14_MULTSIGNOUT_UNCONNECTED;
  wire NLW_p_1_out__14_OVERFLOW_UNCONNECTED;
  wire NLW_p_1_out__14_PATTERNBDETECT_UNCONNECTED;
  wire NLW_p_1_out__14_PATTERNDETECT_UNCONNECTED;
  wire NLW_p_1_out__14_UNDERFLOW_UNCONNECTED;
  wire [29:0]NLW_p_1_out__14_ACOUT_UNCONNECTED;
  wire [17:0]NLW_p_1_out__14_BCOUT_UNCONNECTED;
  wire [3:0]NLW_p_1_out__14_CARRYOUT_UNCONNECTED;
  wire [47:45]NLW_p_1_out__14_P_UNCONNECTED;
  wire [47:0]NLW_p_1_out__14_PCOUT_UNCONNECTED;
  wire [7:0]NLW_p_1_out__14_XOROUT_UNCONNECTED;
  wire NLW_p_1_out__15_CARRYCASCOUT_UNCONNECTED;
  wire NLW_p_1_out__15_MULTSIGNOUT_UNCONNECTED;
  wire NLW_p_1_out__15_OVERFLOW_UNCONNECTED;
  wire NLW_p_1_out__15_PATTERNBDETECT_UNCONNECTED;
  wire NLW_p_1_out__15_PATTERNDETECT_UNCONNECTED;
  wire NLW_p_1_out__15_UNDERFLOW_UNCONNECTED;
  wire [29:0]NLW_p_1_out__15_ACOUT_UNCONNECTED;
  wire [17:0]NLW_p_1_out__15_BCOUT_UNCONNECTED;
  wire [3:0]NLW_p_1_out__15_CARRYOUT_UNCONNECTED;
  wire [47:45]NLW_p_1_out__15_P_UNCONNECTED;
  wire [47:0]NLW_p_1_out__15_PCOUT_UNCONNECTED;
  wire [7:0]NLW_p_1_out__15_XOROUT_UNCONNECTED;
  wire NLW_p_1_out__16_CARRYCASCOUT_UNCONNECTED;
  wire NLW_p_1_out__16_MULTSIGNOUT_UNCONNECTED;
  wire NLW_p_1_out__16_OVERFLOW_UNCONNECTED;
  wire NLW_p_1_out__16_PATTERNBDETECT_UNCONNECTED;
  wire NLW_p_1_out__16_PATTERNDETECT_UNCONNECTED;
  wire NLW_p_1_out__16_UNDERFLOW_UNCONNECTED;
  wire [29:0]NLW_p_1_out__16_ACOUT_UNCONNECTED;
  wire [17:0]NLW_p_1_out__16_BCOUT_UNCONNECTED;
  wire [3:0]NLW_p_1_out__16_CARRYOUT_UNCONNECTED;
  wire [47:45]NLW_p_1_out__16_P_UNCONNECTED;
  wire [47:0]NLW_p_1_out__16_PCOUT_UNCONNECTED;
  wire [7:0]NLW_p_1_out__16_XOROUT_UNCONNECTED;
  wire NLW_p_1_out__17_CARRYCASCOUT_UNCONNECTED;
  wire NLW_p_1_out__17_MULTSIGNOUT_UNCONNECTED;
  wire NLW_p_1_out__17_OVERFLOW_UNCONNECTED;
  wire NLW_p_1_out__17_PATTERNBDETECT_UNCONNECTED;
  wire NLW_p_1_out__17_PATTERNDETECT_UNCONNECTED;
  wire NLW_p_1_out__17_UNDERFLOW_UNCONNECTED;
  wire [29:0]NLW_p_1_out__17_ACOUT_UNCONNECTED;
  wire [17:0]NLW_p_1_out__17_BCOUT_UNCONNECTED;
  wire [3:0]NLW_p_1_out__17_CARRYOUT_UNCONNECTED;
  wire [47:45]NLW_p_1_out__17_P_UNCONNECTED;
  wire [47:0]NLW_p_1_out__17_PCOUT_UNCONNECTED;
  wire [7:0]NLW_p_1_out__17_XOROUT_UNCONNECTED;
  wire NLW_p_1_out__18_CARRYCASCOUT_UNCONNECTED;
  wire NLW_p_1_out__18_MULTSIGNOUT_UNCONNECTED;
  wire NLW_p_1_out__18_OVERFLOW_UNCONNECTED;
  wire NLW_p_1_out__18_PATTERNBDETECT_UNCONNECTED;
  wire NLW_p_1_out__18_PATTERNDETECT_UNCONNECTED;
  wire NLW_p_1_out__18_UNDERFLOW_UNCONNECTED;
  wire [29:0]NLW_p_1_out__18_ACOUT_UNCONNECTED;
  wire [17:0]NLW_p_1_out__18_BCOUT_UNCONNECTED;
  wire [3:0]NLW_p_1_out__18_CARRYOUT_UNCONNECTED;
  wire [47:45]NLW_p_1_out__18_P_UNCONNECTED;
  wire [47:0]NLW_p_1_out__18_PCOUT_UNCONNECTED;
  wire [7:0]NLW_p_1_out__18_XOROUT_UNCONNECTED;
  wire NLW_p_1_out__19_CARRYCASCOUT_UNCONNECTED;
  wire NLW_p_1_out__19_MULTSIGNOUT_UNCONNECTED;
  wire NLW_p_1_out__19_OVERFLOW_UNCONNECTED;
  wire NLW_p_1_out__19_PATTERNBDETECT_UNCONNECTED;
  wire NLW_p_1_out__19_PATTERNDETECT_UNCONNECTED;
  wire NLW_p_1_out__19_UNDERFLOW_UNCONNECTED;
  wire [29:0]NLW_p_1_out__19_ACOUT_UNCONNECTED;
  wire [17:0]NLW_p_1_out__19_BCOUT_UNCONNECTED;
  wire [3:0]NLW_p_1_out__19_CARRYOUT_UNCONNECTED;
  wire [47:45]NLW_p_1_out__19_P_UNCONNECTED;
  wire [47:0]NLW_p_1_out__19_PCOUT_UNCONNECTED;
  wire [7:0]NLW_p_1_out__19_XOROUT_UNCONNECTED;
  wire NLW_p_1_out__2_CARRYCASCOUT_UNCONNECTED;
  wire NLW_p_1_out__2_MULTSIGNOUT_UNCONNECTED;
  wire NLW_p_1_out__2_OVERFLOW_UNCONNECTED;
  wire NLW_p_1_out__2_PATTERNBDETECT_UNCONNECTED;
  wire NLW_p_1_out__2_PATTERNDETECT_UNCONNECTED;
  wire NLW_p_1_out__2_UNDERFLOW_UNCONNECTED;
  wire [29:0]NLW_p_1_out__2_ACOUT_UNCONNECTED;
  wire [17:0]NLW_p_1_out__2_BCOUT_UNCONNECTED;
  wire [3:0]NLW_p_1_out__2_CARRYOUT_UNCONNECTED;
  wire [47:45]NLW_p_1_out__2_P_UNCONNECTED;
  wire [47:0]NLW_p_1_out__2_PCOUT_UNCONNECTED;
  wire [7:0]NLW_p_1_out__2_XOROUT_UNCONNECTED;
  wire NLW_p_1_out__20_CARRYCASCOUT_UNCONNECTED;
  wire NLW_p_1_out__20_MULTSIGNOUT_UNCONNECTED;
  wire NLW_p_1_out__20_OVERFLOW_UNCONNECTED;
  wire NLW_p_1_out__20_PATTERNBDETECT_UNCONNECTED;
  wire NLW_p_1_out__20_PATTERNDETECT_UNCONNECTED;
  wire NLW_p_1_out__20_UNDERFLOW_UNCONNECTED;
  wire [29:0]NLW_p_1_out__20_ACOUT_UNCONNECTED;
  wire [17:0]NLW_p_1_out__20_BCOUT_UNCONNECTED;
  wire [3:0]NLW_p_1_out__20_CARRYOUT_UNCONNECTED;
  wire [47:45]NLW_p_1_out__20_P_UNCONNECTED;
  wire [47:0]NLW_p_1_out__20_PCOUT_UNCONNECTED;
  wire [7:0]NLW_p_1_out__20_XOROUT_UNCONNECTED;
  wire NLW_p_1_out__21_CARRYCASCOUT_UNCONNECTED;
  wire NLW_p_1_out__21_MULTSIGNOUT_UNCONNECTED;
  wire NLW_p_1_out__21_OVERFLOW_UNCONNECTED;
  wire NLW_p_1_out__21_PATTERNBDETECT_UNCONNECTED;
  wire NLW_p_1_out__21_PATTERNDETECT_UNCONNECTED;
  wire NLW_p_1_out__21_UNDERFLOW_UNCONNECTED;
  wire [29:0]NLW_p_1_out__21_ACOUT_UNCONNECTED;
  wire [17:0]NLW_p_1_out__21_BCOUT_UNCONNECTED;
  wire [3:0]NLW_p_1_out__21_CARRYOUT_UNCONNECTED;
  wire [47:45]NLW_p_1_out__21_P_UNCONNECTED;
  wire [47:0]NLW_p_1_out__21_PCOUT_UNCONNECTED;
  wire [7:0]NLW_p_1_out__21_XOROUT_UNCONNECTED;
  wire NLW_p_1_out__22_CARRYCASCOUT_UNCONNECTED;
  wire NLW_p_1_out__22_MULTSIGNOUT_UNCONNECTED;
  wire NLW_p_1_out__22_OVERFLOW_UNCONNECTED;
  wire NLW_p_1_out__22_PATTERNBDETECT_UNCONNECTED;
  wire NLW_p_1_out__22_PATTERNDETECT_UNCONNECTED;
  wire NLW_p_1_out__22_UNDERFLOW_UNCONNECTED;
  wire [29:0]NLW_p_1_out__22_ACOUT_UNCONNECTED;
  wire [17:0]NLW_p_1_out__22_BCOUT_UNCONNECTED;
  wire [3:0]NLW_p_1_out__22_CARRYOUT_UNCONNECTED;
  wire [47:45]NLW_p_1_out__22_P_UNCONNECTED;
  wire [47:0]NLW_p_1_out__22_PCOUT_UNCONNECTED;
  wire [7:0]NLW_p_1_out__22_XOROUT_UNCONNECTED;
  wire NLW_p_1_out__23_CARRYCASCOUT_UNCONNECTED;
  wire NLW_p_1_out__23_MULTSIGNOUT_UNCONNECTED;
  wire NLW_p_1_out__23_OVERFLOW_UNCONNECTED;
  wire NLW_p_1_out__23_PATTERNBDETECT_UNCONNECTED;
  wire NLW_p_1_out__23_PATTERNDETECT_UNCONNECTED;
  wire NLW_p_1_out__23_UNDERFLOW_UNCONNECTED;
  wire [29:0]NLW_p_1_out__23_ACOUT_UNCONNECTED;
  wire [17:0]NLW_p_1_out__23_BCOUT_UNCONNECTED;
  wire [3:0]NLW_p_1_out__23_CARRYOUT_UNCONNECTED;
  wire [47:45]NLW_p_1_out__23_P_UNCONNECTED;
  wire [47:0]NLW_p_1_out__23_PCOUT_UNCONNECTED;
  wire [7:0]NLW_p_1_out__23_XOROUT_UNCONNECTED;
  wire NLW_p_1_out__24_CARRYCASCOUT_UNCONNECTED;
  wire NLW_p_1_out__24_MULTSIGNOUT_UNCONNECTED;
  wire NLW_p_1_out__24_OVERFLOW_UNCONNECTED;
  wire NLW_p_1_out__24_PATTERNBDETECT_UNCONNECTED;
  wire NLW_p_1_out__24_PATTERNDETECT_UNCONNECTED;
  wire NLW_p_1_out__24_UNDERFLOW_UNCONNECTED;
  wire [29:0]NLW_p_1_out__24_ACOUT_UNCONNECTED;
  wire [17:0]NLW_p_1_out__24_BCOUT_UNCONNECTED;
  wire [3:0]NLW_p_1_out__24_CARRYOUT_UNCONNECTED;
  wire [47:45]NLW_p_1_out__24_P_UNCONNECTED;
  wire [47:0]NLW_p_1_out__24_PCOUT_UNCONNECTED;
  wire [7:0]NLW_p_1_out__24_XOROUT_UNCONNECTED;
  wire NLW_p_1_out__25_CARRYCASCOUT_UNCONNECTED;
  wire NLW_p_1_out__25_MULTSIGNOUT_UNCONNECTED;
  wire NLW_p_1_out__25_OVERFLOW_UNCONNECTED;
  wire NLW_p_1_out__25_PATTERNBDETECT_UNCONNECTED;
  wire NLW_p_1_out__25_PATTERNDETECT_UNCONNECTED;
  wire NLW_p_1_out__25_UNDERFLOW_UNCONNECTED;
  wire [29:0]NLW_p_1_out__25_ACOUT_UNCONNECTED;
  wire [17:0]NLW_p_1_out__25_BCOUT_UNCONNECTED;
  wire [3:0]NLW_p_1_out__25_CARRYOUT_UNCONNECTED;
  wire [47:45]NLW_p_1_out__25_P_UNCONNECTED;
  wire [47:0]NLW_p_1_out__25_PCOUT_UNCONNECTED;
  wire [7:0]NLW_p_1_out__25_XOROUT_UNCONNECTED;
  wire NLW_p_1_out__26_CARRYCASCOUT_UNCONNECTED;
  wire NLW_p_1_out__26_MULTSIGNOUT_UNCONNECTED;
  wire NLW_p_1_out__26_OVERFLOW_UNCONNECTED;
  wire NLW_p_1_out__26_PATTERNBDETECT_UNCONNECTED;
  wire NLW_p_1_out__26_PATTERNDETECT_UNCONNECTED;
  wire NLW_p_1_out__26_UNDERFLOW_UNCONNECTED;
  wire [29:0]NLW_p_1_out__26_ACOUT_UNCONNECTED;
  wire [17:0]NLW_p_1_out__26_BCOUT_UNCONNECTED;
  wire [3:0]NLW_p_1_out__26_CARRYOUT_UNCONNECTED;
  wire [47:45]NLW_p_1_out__26_P_UNCONNECTED;
  wire [47:0]NLW_p_1_out__26_PCOUT_UNCONNECTED;
  wire [7:0]NLW_p_1_out__26_XOROUT_UNCONNECTED;
  wire NLW_p_1_out__27_CARRYCASCOUT_UNCONNECTED;
  wire NLW_p_1_out__27_MULTSIGNOUT_UNCONNECTED;
  wire NLW_p_1_out__27_OVERFLOW_UNCONNECTED;
  wire NLW_p_1_out__27_PATTERNBDETECT_UNCONNECTED;
  wire NLW_p_1_out__27_PATTERNDETECT_UNCONNECTED;
  wire NLW_p_1_out__27_UNDERFLOW_UNCONNECTED;
  wire [29:0]NLW_p_1_out__27_ACOUT_UNCONNECTED;
  wire [17:0]NLW_p_1_out__27_BCOUT_UNCONNECTED;
  wire [3:0]NLW_p_1_out__27_CARRYOUT_UNCONNECTED;
  wire [47:45]NLW_p_1_out__27_P_UNCONNECTED;
  wire [47:0]NLW_p_1_out__27_PCOUT_UNCONNECTED;
  wire [7:0]NLW_p_1_out__27_XOROUT_UNCONNECTED;
  wire NLW_p_1_out__28_CARRYCASCOUT_UNCONNECTED;
  wire NLW_p_1_out__28_MULTSIGNOUT_UNCONNECTED;
  wire NLW_p_1_out__28_OVERFLOW_UNCONNECTED;
  wire NLW_p_1_out__28_PATTERNBDETECT_UNCONNECTED;
  wire NLW_p_1_out__28_PATTERNDETECT_UNCONNECTED;
  wire NLW_p_1_out__28_UNDERFLOW_UNCONNECTED;
  wire [29:0]NLW_p_1_out__28_ACOUT_UNCONNECTED;
  wire [17:0]NLW_p_1_out__28_BCOUT_UNCONNECTED;
  wire [3:0]NLW_p_1_out__28_CARRYOUT_UNCONNECTED;
  wire [47:45]NLW_p_1_out__28_P_UNCONNECTED;
  wire [47:0]NLW_p_1_out__28_PCOUT_UNCONNECTED;
  wire [7:0]NLW_p_1_out__28_XOROUT_UNCONNECTED;
  wire NLW_p_1_out__29_CARRYCASCOUT_UNCONNECTED;
  wire NLW_p_1_out__29_MULTSIGNOUT_UNCONNECTED;
  wire NLW_p_1_out__29_OVERFLOW_UNCONNECTED;
  wire NLW_p_1_out__29_PATTERNBDETECT_UNCONNECTED;
  wire NLW_p_1_out__29_PATTERNDETECT_UNCONNECTED;
  wire NLW_p_1_out__29_UNDERFLOW_UNCONNECTED;
  wire [29:0]NLW_p_1_out__29_ACOUT_UNCONNECTED;
  wire [17:0]NLW_p_1_out__29_BCOUT_UNCONNECTED;
  wire [3:0]NLW_p_1_out__29_CARRYOUT_UNCONNECTED;
  wire [47:45]NLW_p_1_out__29_P_UNCONNECTED;
  wire [47:0]NLW_p_1_out__29_PCOUT_UNCONNECTED;
  wire [7:0]NLW_p_1_out__29_XOROUT_UNCONNECTED;
  wire NLW_p_1_out__3_CARRYCASCOUT_UNCONNECTED;
  wire NLW_p_1_out__3_MULTSIGNOUT_UNCONNECTED;
  wire NLW_p_1_out__3_OVERFLOW_UNCONNECTED;
  wire NLW_p_1_out__3_PATTERNBDETECT_UNCONNECTED;
  wire NLW_p_1_out__3_PATTERNDETECT_UNCONNECTED;
  wire NLW_p_1_out__3_UNDERFLOW_UNCONNECTED;
  wire [29:0]NLW_p_1_out__3_ACOUT_UNCONNECTED;
  wire [17:0]NLW_p_1_out__3_BCOUT_UNCONNECTED;
  wire [3:0]NLW_p_1_out__3_CARRYOUT_UNCONNECTED;
  wire [47:45]NLW_p_1_out__3_P_UNCONNECTED;
  wire [47:0]NLW_p_1_out__3_PCOUT_UNCONNECTED;
  wire [7:0]NLW_p_1_out__3_XOROUT_UNCONNECTED;
  wire NLW_p_1_out__30_CARRYCASCOUT_UNCONNECTED;
  wire NLW_p_1_out__30_MULTSIGNOUT_UNCONNECTED;
  wire NLW_p_1_out__30_OVERFLOW_UNCONNECTED;
  wire NLW_p_1_out__30_PATTERNBDETECT_UNCONNECTED;
  wire NLW_p_1_out__30_PATTERNDETECT_UNCONNECTED;
  wire NLW_p_1_out__30_UNDERFLOW_UNCONNECTED;
  wire [29:0]NLW_p_1_out__30_ACOUT_UNCONNECTED;
  wire [17:0]NLW_p_1_out__30_BCOUT_UNCONNECTED;
  wire [3:0]NLW_p_1_out__30_CARRYOUT_UNCONNECTED;
  wire [47:45]NLW_p_1_out__30_P_UNCONNECTED;
  wire [47:0]NLW_p_1_out__30_PCOUT_UNCONNECTED;
  wire [7:0]NLW_p_1_out__30_XOROUT_UNCONNECTED;
  wire NLW_p_1_out__4_CARRYCASCOUT_UNCONNECTED;
  wire NLW_p_1_out__4_MULTSIGNOUT_UNCONNECTED;
  wire NLW_p_1_out__4_OVERFLOW_UNCONNECTED;
  wire NLW_p_1_out__4_PATTERNBDETECT_UNCONNECTED;
  wire NLW_p_1_out__4_PATTERNDETECT_UNCONNECTED;
  wire NLW_p_1_out__4_UNDERFLOW_UNCONNECTED;
  wire [29:0]NLW_p_1_out__4_ACOUT_UNCONNECTED;
  wire [17:0]NLW_p_1_out__4_BCOUT_UNCONNECTED;
  wire [3:0]NLW_p_1_out__4_CARRYOUT_UNCONNECTED;
  wire [47:45]NLW_p_1_out__4_P_UNCONNECTED;
  wire [47:0]NLW_p_1_out__4_PCOUT_UNCONNECTED;
  wire [7:0]NLW_p_1_out__4_XOROUT_UNCONNECTED;
  wire NLW_p_1_out__5_CARRYCASCOUT_UNCONNECTED;
  wire NLW_p_1_out__5_MULTSIGNOUT_UNCONNECTED;
  wire NLW_p_1_out__5_OVERFLOW_UNCONNECTED;
  wire NLW_p_1_out__5_PATTERNBDETECT_UNCONNECTED;
  wire NLW_p_1_out__5_PATTERNDETECT_UNCONNECTED;
  wire NLW_p_1_out__5_UNDERFLOW_UNCONNECTED;
  wire [29:0]NLW_p_1_out__5_ACOUT_UNCONNECTED;
  wire [17:0]NLW_p_1_out__5_BCOUT_UNCONNECTED;
  wire [3:0]NLW_p_1_out__5_CARRYOUT_UNCONNECTED;
  wire [47:45]NLW_p_1_out__5_P_UNCONNECTED;
  wire [47:0]NLW_p_1_out__5_PCOUT_UNCONNECTED;
  wire [7:0]NLW_p_1_out__5_XOROUT_UNCONNECTED;
  wire NLW_p_1_out__6_CARRYCASCOUT_UNCONNECTED;
  wire NLW_p_1_out__6_MULTSIGNOUT_UNCONNECTED;
  wire NLW_p_1_out__6_OVERFLOW_UNCONNECTED;
  wire NLW_p_1_out__6_PATTERNBDETECT_UNCONNECTED;
  wire NLW_p_1_out__6_PATTERNDETECT_UNCONNECTED;
  wire NLW_p_1_out__6_UNDERFLOW_UNCONNECTED;
  wire [29:0]NLW_p_1_out__6_ACOUT_UNCONNECTED;
  wire [17:0]NLW_p_1_out__6_BCOUT_UNCONNECTED;
  wire [3:0]NLW_p_1_out__6_CARRYOUT_UNCONNECTED;
  wire [47:45]NLW_p_1_out__6_P_UNCONNECTED;
  wire [47:0]NLW_p_1_out__6_PCOUT_UNCONNECTED;
  wire [7:0]NLW_p_1_out__6_XOROUT_UNCONNECTED;
  wire NLW_p_1_out__7_CARRYCASCOUT_UNCONNECTED;
  wire NLW_p_1_out__7_MULTSIGNOUT_UNCONNECTED;
  wire NLW_p_1_out__7_OVERFLOW_UNCONNECTED;
  wire NLW_p_1_out__7_PATTERNBDETECT_UNCONNECTED;
  wire NLW_p_1_out__7_PATTERNDETECT_UNCONNECTED;
  wire NLW_p_1_out__7_UNDERFLOW_UNCONNECTED;
  wire [29:0]NLW_p_1_out__7_ACOUT_UNCONNECTED;
  wire [17:0]NLW_p_1_out__7_BCOUT_UNCONNECTED;
  wire [3:0]NLW_p_1_out__7_CARRYOUT_UNCONNECTED;
  wire [47:45]NLW_p_1_out__7_P_UNCONNECTED;
  wire [47:0]NLW_p_1_out__7_PCOUT_UNCONNECTED;
  wire [7:0]NLW_p_1_out__7_XOROUT_UNCONNECTED;
  wire NLW_p_1_out__8_CARRYCASCOUT_UNCONNECTED;
  wire NLW_p_1_out__8_MULTSIGNOUT_UNCONNECTED;
  wire NLW_p_1_out__8_OVERFLOW_UNCONNECTED;
  wire NLW_p_1_out__8_PATTERNBDETECT_UNCONNECTED;
  wire NLW_p_1_out__8_PATTERNDETECT_UNCONNECTED;
  wire NLW_p_1_out__8_UNDERFLOW_UNCONNECTED;
  wire [29:0]NLW_p_1_out__8_ACOUT_UNCONNECTED;
  wire [17:0]NLW_p_1_out__8_BCOUT_UNCONNECTED;
  wire [3:0]NLW_p_1_out__8_CARRYOUT_UNCONNECTED;
  wire [47:45]NLW_p_1_out__8_P_UNCONNECTED;
  wire [47:0]NLW_p_1_out__8_PCOUT_UNCONNECTED;
  wire [7:0]NLW_p_1_out__8_XOROUT_UNCONNECTED;
  wire NLW_p_1_out__9_CARRYCASCOUT_UNCONNECTED;
  wire NLW_p_1_out__9_MULTSIGNOUT_UNCONNECTED;
  wire NLW_p_1_out__9_OVERFLOW_UNCONNECTED;
  wire NLW_p_1_out__9_PATTERNBDETECT_UNCONNECTED;
  wire NLW_p_1_out__9_PATTERNDETECT_UNCONNECTED;
  wire NLW_p_1_out__9_UNDERFLOW_UNCONNECTED;
  wire [29:0]NLW_p_1_out__9_ACOUT_UNCONNECTED;
  wire [17:0]NLW_p_1_out__9_BCOUT_UNCONNECTED;
  wire [3:0]NLW_p_1_out__9_CARRYOUT_UNCONNECTED;
  wire [47:45]NLW_p_1_out__9_P_UNCONNECTED;
  wire [47:0]NLW_p_1_out__9_PCOUT_UNCONNECTED;
  wire [7:0]NLW_p_1_out__9_XOROUT_UNCONNECTED;

  FDRE \Delay10_out1_reg[0] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in10[0]),
        .Q(Delay10_out1[0]),
        .R(reset));
  FDRE \Delay10_out1_reg[10] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in10[10]),
        .Q(Delay10_out1[10]),
        .R(reset));
  FDRE \Delay10_out1_reg[11] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in10[11]),
        .Q(Delay10_out1[11]),
        .R(reset));
  FDRE \Delay10_out1_reg[12] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in10[12]),
        .Q(Delay10_out1[12]),
        .R(reset));
  FDRE \Delay10_out1_reg[13] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in10[13]),
        .Q(Delay10_out1[13]),
        .R(reset));
  FDRE \Delay10_out1_reg[14] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in10[14]),
        .Q(Delay10_out1[14]),
        .R(reset));
  FDRE \Delay10_out1_reg[15] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in10[15]),
        .Q(Delay10_out1[15]),
        .R(reset));
  FDRE \Delay10_out1_reg[16] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in10[16]),
        .Q(Delay10_out1[16]),
        .R(reset));
  FDRE \Delay10_out1_reg[17] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in10[17]),
        .Q(Delay10_out1[17]),
        .R(reset));
  FDRE \Delay10_out1_reg[18] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in10[18]),
        .Q(Delay10_out1[18]),
        .R(reset));
  FDRE \Delay10_out1_reg[19] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in10[19]),
        .Q(Delay10_out1[19]),
        .R(reset));
  FDRE \Delay10_out1_reg[1] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in10[1]),
        .Q(Delay10_out1[1]),
        .R(reset));
  FDRE \Delay10_out1_reg[20] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in10[20]),
        .Q(Delay10_out1[20]),
        .R(reset));
  FDRE \Delay10_out1_reg[21] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in10[21]),
        .Q(Delay10_out1[21]),
        .R(reset));
  FDRE \Delay10_out1_reg[22] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in10[22]),
        .Q(Delay10_out1[22]),
        .R(reset));
  FDRE \Delay10_out1_reg[23] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in10[23]),
        .Q(Delay10_out1[23]),
        .R(reset));
  FDRE \Delay10_out1_reg[24] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in10[24]),
        .Q(Delay10_out1[24]),
        .R(reset));
  FDRE \Delay10_out1_reg[25] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in10[25]),
        .Q(Delay10_out1[25]),
        .R(reset));
  FDRE \Delay10_out1_reg[26] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in10[26]),
        .Q(Delay10_out1[26]),
        .R(reset));
  FDRE \Delay10_out1_reg[2] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in10[2]),
        .Q(Delay10_out1[2]),
        .R(reset));
  FDRE \Delay10_out1_reg[3] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in10[3]),
        .Q(Delay10_out1[3]),
        .R(reset));
  FDRE \Delay10_out1_reg[4] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in10[4]),
        .Q(Delay10_out1[4]),
        .R(reset));
  FDRE \Delay10_out1_reg[5] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in10[5]),
        .Q(Delay10_out1[5]),
        .R(reset));
  FDRE \Delay10_out1_reg[6] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in10[6]),
        .Q(Delay10_out1[6]),
        .R(reset));
  FDRE \Delay10_out1_reg[7] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in10[7]),
        .Q(Delay10_out1[7]),
        .R(reset));
  FDRE \Delay10_out1_reg[8] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in10[8]),
        .Q(Delay10_out1[8]),
        .R(reset));
  FDRE \Delay10_out1_reg[9] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in10[9]),
        .Q(Delay10_out1[9]),
        .R(reset));
  FDRE \Delay11_out1_reg[0] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in11[0]),
        .Q(Delay11_out1[0]),
        .R(reset));
  FDRE \Delay11_out1_reg[10] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in11[10]),
        .Q(Delay11_out1[10]),
        .R(reset));
  FDRE \Delay11_out1_reg[11] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in11[11]),
        .Q(Delay11_out1[11]),
        .R(reset));
  FDRE \Delay11_out1_reg[12] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in11[12]),
        .Q(Delay11_out1[12]),
        .R(reset));
  FDRE \Delay11_out1_reg[13] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in11[13]),
        .Q(Delay11_out1[13]),
        .R(reset));
  FDRE \Delay11_out1_reg[14] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in11[14]),
        .Q(Delay11_out1[14]),
        .R(reset));
  FDRE \Delay11_out1_reg[15] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in11[15]),
        .Q(Delay11_out1[15]),
        .R(reset));
  FDRE \Delay11_out1_reg[16] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in11[16]),
        .Q(Delay11_out1[16]),
        .R(reset));
  FDRE \Delay11_out1_reg[17] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in11[17]),
        .Q(Delay11_out1[17]),
        .R(reset));
  FDRE \Delay11_out1_reg[18] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in11[18]),
        .Q(Delay11_out1[18]),
        .R(reset));
  FDRE \Delay11_out1_reg[19] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in11[19]),
        .Q(Delay11_out1[19]),
        .R(reset));
  FDRE \Delay11_out1_reg[1] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in11[1]),
        .Q(Delay11_out1[1]),
        .R(reset));
  FDRE \Delay11_out1_reg[20] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in11[20]),
        .Q(Delay11_out1[20]),
        .R(reset));
  FDRE \Delay11_out1_reg[21] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in11[21]),
        .Q(Delay11_out1[21]),
        .R(reset));
  FDRE \Delay11_out1_reg[22] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in11[22]),
        .Q(Delay11_out1[22]),
        .R(reset));
  FDRE \Delay11_out1_reg[23] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in11[23]),
        .Q(Delay11_out1[23]),
        .R(reset));
  FDRE \Delay11_out1_reg[24] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in11[24]),
        .Q(Delay11_out1[24]),
        .R(reset));
  FDRE \Delay11_out1_reg[25] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in11[25]),
        .Q(Delay11_out1[25]),
        .R(reset));
  FDRE \Delay11_out1_reg[26] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in11[26]),
        .Q(Delay11_out1[26]),
        .R(reset));
  FDRE \Delay11_out1_reg[2] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in11[2]),
        .Q(Delay11_out1[2]),
        .R(reset));
  FDRE \Delay11_out1_reg[3] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in11[3]),
        .Q(Delay11_out1[3]),
        .R(reset));
  FDRE \Delay11_out1_reg[4] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in11[4]),
        .Q(Delay11_out1[4]),
        .R(reset));
  FDRE \Delay11_out1_reg[5] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in11[5]),
        .Q(Delay11_out1[5]),
        .R(reset));
  FDRE \Delay11_out1_reg[6] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in11[6]),
        .Q(Delay11_out1[6]),
        .R(reset));
  FDRE \Delay11_out1_reg[7] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in11[7]),
        .Q(Delay11_out1[7]),
        .R(reset));
  FDRE \Delay11_out1_reg[8] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in11[8]),
        .Q(Delay11_out1[8]),
        .R(reset));
  FDRE \Delay11_out1_reg[9] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in11[9]),
        .Q(Delay11_out1[9]),
        .R(reset));
  FDRE \Delay12_out1_reg[0] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in12[0]),
        .Q(Delay12_out1[0]),
        .R(reset));
  FDRE \Delay12_out1_reg[10] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in12[10]),
        .Q(Delay12_out1[10]),
        .R(reset));
  FDRE \Delay12_out1_reg[11] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in12[11]),
        .Q(Delay12_out1[11]),
        .R(reset));
  FDRE \Delay12_out1_reg[12] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in12[12]),
        .Q(Delay12_out1[12]),
        .R(reset));
  FDRE \Delay12_out1_reg[13] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in12[13]),
        .Q(Delay12_out1[13]),
        .R(reset));
  FDRE \Delay12_out1_reg[14] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in12[14]),
        .Q(Delay12_out1[14]),
        .R(reset));
  FDRE \Delay12_out1_reg[15] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in12[15]),
        .Q(Delay12_out1[15]),
        .R(reset));
  FDRE \Delay12_out1_reg[16] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in12[16]),
        .Q(Delay12_out1[16]),
        .R(reset));
  FDRE \Delay12_out1_reg[17] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in12[17]),
        .Q(Delay12_out1[17]),
        .R(reset));
  FDRE \Delay12_out1_reg[18] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in12[18]),
        .Q(Delay12_out1[18]),
        .R(reset));
  FDRE \Delay12_out1_reg[19] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in12[19]),
        .Q(Delay12_out1[19]),
        .R(reset));
  FDRE \Delay12_out1_reg[1] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in12[1]),
        .Q(Delay12_out1[1]),
        .R(reset));
  FDRE \Delay12_out1_reg[20] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in12[20]),
        .Q(Delay12_out1[20]),
        .R(reset));
  FDRE \Delay12_out1_reg[21] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in12[21]),
        .Q(Delay12_out1[21]),
        .R(reset));
  FDRE \Delay12_out1_reg[22] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in12[22]),
        .Q(Delay12_out1[22]),
        .R(reset));
  FDRE \Delay12_out1_reg[23] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in12[23]),
        .Q(Delay12_out1[23]),
        .R(reset));
  FDRE \Delay12_out1_reg[24] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in12[24]),
        .Q(Delay12_out1[24]),
        .R(reset));
  FDRE \Delay12_out1_reg[25] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in12[25]),
        .Q(Delay12_out1[25]),
        .R(reset));
  FDRE \Delay12_out1_reg[26] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in12[26]),
        .Q(Delay12_out1[26]),
        .R(reset));
  FDRE \Delay12_out1_reg[2] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in12[2]),
        .Q(Delay12_out1[2]),
        .R(reset));
  FDRE \Delay12_out1_reg[3] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in12[3]),
        .Q(Delay12_out1[3]),
        .R(reset));
  FDRE \Delay12_out1_reg[4] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in12[4]),
        .Q(Delay12_out1[4]),
        .R(reset));
  FDRE \Delay12_out1_reg[5] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in12[5]),
        .Q(Delay12_out1[5]),
        .R(reset));
  FDRE \Delay12_out1_reg[6] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in12[6]),
        .Q(Delay12_out1[6]),
        .R(reset));
  FDRE \Delay12_out1_reg[7] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in12[7]),
        .Q(Delay12_out1[7]),
        .R(reset));
  FDRE \Delay12_out1_reg[8] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in12[8]),
        .Q(Delay12_out1[8]),
        .R(reset));
  FDRE \Delay12_out1_reg[9] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in12[9]),
        .Q(Delay12_out1[9]),
        .R(reset));
  FDRE \Delay13_out1_reg[0] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in13[0]),
        .Q(Delay13_out1[0]),
        .R(reset));
  FDRE \Delay13_out1_reg[10] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in13[10]),
        .Q(Delay13_out1[10]),
        .R(reset));
  FDRE \Delay13_out1_reg[11] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in13[11]),
        .Q(Delay13_out1[11]),
        .R(reset));
  FDRE \Delay13_out1_reg[12] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in13[12]),
        .Q(Delay13_out1[12]),
        .R(reset));
  FDRE \Delay13_out1_reg[13] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in13[13]),
        .Q(Delay13_out1[13]),
        .R(reset));
  FDRE \Delay13_out1_reg[14] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in13[14]),
        .Q(Delay13_out1[14]),
        .R(reset));
  FDRE \Delay13_out1_reg[15] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in13[15]),
        .Q(Delay13_out1[15]),
        .R(reset));
  FDRE \Delay13_out1_reg[16] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in13[16]),
        .Q(Delay13_out1[16]),
        .R(reset));
  FDRE \Delay13_out1_reg[17] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in13[17]),
        .Q(Delay13_out1[17]),
        .R(reset));
  FDRE \Delay13_out1_reg[18] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in13[18]),
        .Q(Delay13_out1[18]),
        .R(reset));
  FDRE \Delay13_out1_reg[19] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in13[19]),
        .Q(Delay13_out1[19]),
        .R(reset));
  FDRE \Delay13_out1_reg[1] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in13[1]),
        .Q(Delay13_out1[1]),
        .R(reset));
  FDRE \Delay13_out1_reg[20] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in13[20]),
        .Q(Delay13_out1[20]),
        .R(reset));
  FDRE \Delay13_out1_reg[21] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in13[21]),
        .Q(Delay13_out1[21]),
        .R(reset));
  FDRE \Delay13_out1_reg[22] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in13[22]),
        .Q(Delay13_out1[22]),
        .R(reset));
  FDRE \Delay13_out1_reg[23] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in13[23]),
        .Q(Delay13_out1[23]),
        .R(reset));
  FDRE \Delay13_out1_reg[24] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in13[24]),
        .Q(Delay13_out1[24]),
        .R(reset));
  FDRE \Delay13_out1_reg[25] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in13[25]),
        .Q(Delay13_out1[25]),
        .R(reset));
  FDRE \Delay13_out1_reg[26] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in13[26]),
        .Q(Delay13_out1[26]),
        .R(reset));
  FDRE \Delay13_out1_reg[2] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in13[2]),
        .Q(Delay13_out1[2]),
        .R(reset));
  FDRE \Delay13_out1_reg[3] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in13[3]),
        .Q(Delay13_out1[3]),
        .R(reset));
  FDRE \Delay13_out1_reg[4] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in13[4]),
        .Q(Delay13_out1[4]),
        .R(reset));
  FDRE \Delay13_out1_reg[5] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in13[5]),
        .Q(Delay13_out1[5]),
        .R(reset));
  FDRE \Delay13_out1_reg[6] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in13[6]),
        .Q(Delay13_out1[6]),
        .R(reset));
  FDRE \Delay13_out1_reg[7] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in13[7]),
        .Q(Delay13_out1[7]),
        .R(reset));
  FDRE \Delay13_out1_reg[8] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in13[8]),
        .Q(Delay13_out1[8]),
        .R(reset));
  FDRE \Delay13_out1_reg[9] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in13[9]),
        .Q(Delay13_out1[9]),
        .R(reset));
  FDRE \Delay14_out1_reg[0] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in14[0]),
        .Q(Delay14_out1[0]),
        .R(reset));
  FDRE \Delay14_out1_reg[10] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in14[10]),
        .Q(Delay14_out1[10]),
        .R(reset));
  FDRE \Delay14_out1_reg[11] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in14[11]),
        .Q(Delay14_out1[11]),
        .R(reset));
  FDRE \Delay14_out1_reg[12] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in14[12]),
        .Q(Delay14_out1[12]),
        .R(reset));
  FDRE \Delay14_out1_reg[13] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in14[13]),
        .Q(Delay14_out1[13]),
        .R(reset));
  FDRE \Delay14_out1_reg[14] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in14[14]),
        .Q(Delay14_out1[14]),
        .R(reset));
  FDRE \Delay14_out1_reg[15] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in14[15]),
        .Q(Delay14_out1[15]),
        .R(reset));
  FDRE \Delay14_out1_reg[16] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in14[16]),
        .Q(Delay14_out1[16]),
        .R(reset));
  FDRE \Delay14_out1_reg[17] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in14[17]),
        .Q(Delay14_out1[17]),
        .R(reset));
  FDRE \Delay14_out1_reg[18] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in14[18]),
        .Q(Delay14_out1[18]),
        .R(reset));
  FDRE \Delay14_out1_reg[19] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in14[19]),
        .Q(Delay14_out1[19]),
        .R(reset));
  FDRE \Delay14_out1_reg[1] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in14[1]),
        .Q(Delay14_out1[1]),
        .R(reset));
  FDRE \Delay14_out1_reg[20] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in14[20]),
        .Q(Delay14_out1[20]),
        .R(reset));
  FDRE \Delay14_out1_reg[21] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in14[21]),
        .Q(Delay14_out1[21]),
        .R(reset));
  FDRE \Delay14_out1_reg[22] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in14[22]),
        .Q(Delay14_out1[22]),
        .R(reset));
  FDRE \Delay14_out1_reg[23] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in14[23]),
        .Q(Delay14_out1[23]),
        .R(reset));
  FDRE \Delay14_out1_reg[24] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in14[24]),
        .Q(Delay14_out1[24]),
        .R(reset));
  FDRE \Delay14_out1_reg[25] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in14[25]),
        .Q(Delay14_out1[25]),
        .R(reset));
  FDRE \Delay14_out1_reg[26] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in14[26]),
        .Q(Delay14_out1[26]),
        .R(reset));
  FDRE \Delay14_out1_reg[2] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in14[2]),
        .Q(Delay14_out1[2]),
        .R(reset));
  FDRE \Delay14_out1_reg[3] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in14[3]),
        .Q(Delay14_out1[3]),
        .R(reset));
  FDRE \Delay14_out1_reg[4] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in14[4]),
        .Q(Delay14_out1[4]),
        .R(reset));
  FDRE \Delay14_out1_reg[5] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in14[5]),
        .Q(Delay14_out1[5]),
        .R(reset));
  FDRE \Delay14_out1_reg[6] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in14[6]),
        .Q(Delay14_out1[6]),
        .R(reset));
  FDRE \Delay14_out1_reg[7] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in14[7]),
        .Q(Delay14_out1[7]),
        .R(reset));
  FDRE \Delay14_out1_reg[8] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in14[8]),
        .Q(Delay14_out1[8]),
        .R(reset));
  FDRE \Delay14_out1_reg[9] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in14[9]),
        .Q(Delay14_out1[9]),
        .R(reset));
  FDRE \Delay15_out1_reg[0] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in15[0]),
        .Q(Delay15_out1[0]),
        .R(reset));
  FDRE \Delay15_out1_reg[10] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in15[10]),
        .Q(Delay15_out1[10]),
        .R(reset));
  FDRE \Delay15_out1_reg[11] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in15[11]),
        .Q(Delay15_out1[11]),
        .R(reset));
  FDRE \Delay15_out1_reg[12] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in15[12]),
        .Q(Delay15_out1[12]),
        .R(reset));
  FDRE \Delay15_out1_reg[13] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in15[13]),
        .Q(Delay15_out1[13]),
        .R(reset));
  FDRE \Delay15_out1_reg[14] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in15[14]),
        .Q(Delay15_out1[14]),
        .R(reset));
  FDRE \Delay15_out1_reg[15] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in15[15]),
        .Q(Delay15_out1[15]),
        .R(reset));
  FDRE \Delay15_out1_reg[16] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in15[16]),
        .Q(Delay15_out1[16]),
        .R(reset));
  FDRE \Delay15_out1_reg[17] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in15[17]),
        .Q(Delay15_out1[17]),
        .R(reset));
  FDRE \Delay15_out1_reg[18] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in15[18]),
        .Q(Delay15_out1[18]),
        .R(reset));
  FDRE \Delay15_out1_reg[19] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in15[19]),
        .Q(Delay15_out1[19]),
        .R(reset));
  FDRE \Delay15_out1_reg[1] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in15[1]),
        .Q(Delay15_out1[1]),
        .R(reset));
  FDRE \Delay15_out1_reg[20] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in15[20]),
        .Q(Delay15_out1[20]),
        .R(reset));
  FDRE \Delay15_out1_reg[21] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in15[21]),
        .Q(Delay15_out1[21]),
        .R(reset));
  FDRE \Delay15_out1_reg[22] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in15[22]),
        .Q(Delay15_out1[22]),
        .R(reset));
  FDRE \Delay15_out1_reg[23] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in15[23]),
        .Q(Delay15_out1[23]),
        .R(reset));
  FDRE \Delay15_out1_reg[24] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in15[24]),
        .Q(Delay15_out1[24]),
        .R(reset));
  FDRE \Delay15_out1_reg[25] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in15[25]),
        .Q(Delay15_out1[25]),
        .R(reset));
  FDRE \Delay15_out1_reg[26] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in15[26]),
        .Q(Delay15_out1[26]),
        .R(reset));
  FDRE \Delay15_out1_reg[2] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in15[2]),
        .Q(Delay15_out1[2]),
        .R(reset));
  FDRE \Delay15_out1_reg[3] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in15[3]),
        .Q(Delay15_out1[3]),
        .R(reset));
  FDRE \Delay15_out1_reg[4] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in15[4]),
        .Q(Delay15_out1[4]),
        .R(reset));
  FDRE \Delay15_out1_reg[5] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in15[5]),
        .Q(Delay15_out1[5]),
        .R(reset));
  FDRE \Delay15_out1_reg[6] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in15[6]),
        .Q(Delay15_out1[6]),
        .R(reset));
  FDRE \Delay15_out1_reg[7] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in15[7]),
        .Q(Delay15_out1[7]),
        .R(reset));
  FDRE \Delay15_out1_reg[8] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in15[8]),
        .Q(Delay15_out1[8]),
        .R(reset));
  FDRE \Delay15_out1_reg[9] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in15[9]),
        .Q(Delay15_out1[9]),
        .R(reset));
  FDRE \Delay16_out1_reg[0] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in16[0]),
        .Q(Delay16_out1[0]),
        .R(reset));
  FDRE \Delay16_out1_reg[10] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in16[10]),
        .Q(Delay16_out1[10]),
        .R(reset));
  FDRE \Delay16_out1_reg[11] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in16[11]),
        .Q(Delay16_out1[11]),
        .R(reset));
  FDRE \Delay16_out1_reg[12] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in16[12]),
        .Q(Delay16_out1[12]),
        .R(reset));
  FDRE \Delay16_out1_reg[13] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in16[13]),
        .Q(Delay16_out1[13]),
        .R(reset));
  FDRE \Delay16_out1_reg[14] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in16[14]),
        .Q(Delay16_out1[14]),
        .R(reset));
  FDRE \Delay16_out1_reg[15] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in16[15]),
        .Q(Delay16_out1[15]),
        .R(reset));
  FDRE \Delay16_out1_reg[16] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in16[16]),
        .Q(Delay16_out1[16]),
        .R(reset));
  FDRE \Delay16_out1_reg[17] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in16[17]),
        .Q(Delay16_out1[17]),
        .R(reset));
  FDRE \Delay16_out1_reg[18] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in16[18]),
        .Q(Delay16_out1[18]),
        .R(reset));
  FDRE \Delay16_out1_reg[19] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in16[19]),
        .Q(Delay16_out1[19]),
        .R(reset));
  FDRE \Delay16_out1_reg[1] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in16[1]),
        .Q(Delay16_out1[1]),
        .R(reset));
  FDRE \Delay16_out1_reg[20] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in16[20]),
        .Q(Delay16_out1[20]),
        .R(reset));
  FDRE \Delay16_out1_reg[21] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in16[21]),
        .Q(Delay16_out1[21]),
        .R(reset));
  FDRE \Delay16_out1_reg[22] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in16[22]),
        .Q(Delay16_out1[22]),
        .R(reset));
  FDRE \Delay16_out1_reg[23] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in16[23]),
        .Q(Delay16_out1[23]),
        .R(reset));
  FDRE \Delay16_out1_reg[24] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in16[24]),
        .Q(Delay16_out1[24]),
        .R(reset));
  FDRE \Delay16_out1_reg[25] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in16[25]),
        .Q(Delay16_out1[25]),
        .R(reset));
  FDRE \Delay16_out1_reg[26] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in16[26]),
        .Q(Delay16_out1[26]),
        .R(reset));
  FDRE \Delay16_out1_reg[2] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in16[2]),
        .Q(Delay16_out1[2]),
        .R(reset));
  FDRE \Delay16_out1_reg[3] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in16[3]),
        .Q(Delay16_out1[3]),
        .R(reset));
  FDRE \Delay16_out1_reg[4] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in16[4]),
        .Q(Delay16_out1[4]),
        .R(reset));
  FDRE \Delay16_out1_reg[5] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in16[5]),
        .Q(Delay16_out1[5]),
        .R(reset));
  FDRE \Delay16_out1_reg[6] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in16[6]),
        .Q(Delay16_out1[6]),
        .R(reset));
  FDRE \Delay16_out1_reg[7] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in16[7]),
        .Q(Delay16_out1[7]),
        .R(reset));
  FDRE \Delay16_out1_reg[8] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in16[8]),
        .Q(Delay16_out1[8]),
        .R(reset));
  FDRE \Delay16_out1_reg[9] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in16[9]),
        .Q(Delay16_out1[9]),
        .R(reset));
  FDRE \Delay17_out1_reg[0] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in17[0]),
        .Q(Delay17_out1[0]),
        .R(reset));
  FDRE \Delay17_out1_reg[10] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in17[10]),
        .Q(Delay17_out1[10]),
        .R(reset));
  FDRE \Delay17_out1_reg[11] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in17[11]),
        .Q(Delay17_out1[11]),
        .R(reset));
  FDRE \Delay17_out1_reg[12] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in17[12]),
        .Q(Delay17_out1[12]),
        .R(reset));
  FDRE \Delay17_out1_reg[13] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in17[13]),
        .Q(Delay17_out1[13]),
        .R(reset));
  FDRE \Delay17_out1_reg[14] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in17[14]),
        .Q(Delay17_out1[14]),
        .R(reset));
  FDRE \Delay17_out1_reg[15] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in17[15]),
        .Q(Delay17_out1[15]),
        .R(reset));
  FDRE \Delay17_out1_reg[16] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in17[16]),
        .Q(Delay17_out1[16]),
        .R(reset));
  FDRE \Delay17_out1_reg[17] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in17[17]),
        .Q(Delay17_out1[17]),
        .R(reset));
  FDRE \Delay17_out1_reg[18] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in17[18]),
        .Q(Delay17_out1[18]),
        .R(reset));
  FDRE \Delay17_out1_reg[19] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in17[19]),
        .Q(Delay17_out1[19]),
        .R(reset));
  FDRE \Delay17_out1_reg[1] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in17[1]),
        .Q(Delay17_out1[1]),
        .R(reset));
  FDRE \Delay17_out1_reg[20] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in17[20]),
        .Q(Delay17_out1[20]),
        .R(reset));
  FDRE \Delay17_out1_reg[21] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in17[21]),
        .Q(Delay17_out1[21]),
        .R(reset));
  FDRE \Delay17_out1_reg[22] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in17[22]),
        .Q(Delay17_out1[22]),
        .R(reset));
  FDRE \Delay17_out1_reg[23] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in17[23]),
        .Q(Delay17_out1[23]),
        .R(reset));
  FDRE \Delay17_out1_reg[24] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in17[24]),
        .Q(Delay17_out1[24]),
        .R(reset));
  FDRE \Delay17_out1_reg[25] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in17[25]),
        .Q(Delay17_out1[25]),
        .R(reset));
  FDRE \Delay17_out1_reg[26] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in17[26]),
        .Q(Delay17_out1[26]),
        .R(reset));
  FDRE \Delay17_out1_reg[2] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in17[2]),
        .Q(Delay17_out1[2]),
        .R(reset));
  FDRE \Delay17_out1_reg[3] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in17[3]),
        .Q(Delay17_out1[3]),
        .R(reset));
  FDRE \Delay17_out1_reg[4] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in17[4]),
        .Q(Delay17_out1[4]),
        .R(reset));
  FDRE \Delay17_out1_reg[5] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in17[5]),
        .Q(Delay17_out1[5]),
        .R(reset));
  FDRE \Delay17_out1_reg[6] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in17[6]),
        .Q(Delay17_out1[6]),
        .R(reset));
  FDRE \Delay17_out1_reg[7] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in17[7]),
        .Q(Delay17_out1[7]),
        .R(reset));
  FDRE \Delay17_out1_reg[8] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in17[8]),
        .Q(Delay17_out1[8]),
        .R(reset));
  FDRE \Delay17_out1_reg[9] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in17[9]),
        .Q(Delay17_out1[9]),
        .R(reset));
  FDRE \Delay18_out1_reg[0] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in18[0]),
        .Q(Delay18_out1[0]),
        .R(reset));
  FDRE \Delay18_out1_reg[10] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in18[10]),
        .Q(Delay18_out1[10]),
        .R(reset));
  FDRE \Delay18_out1_reg[11] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in18[11]),
        .Q(Delay18_out1[11]),
        .R(reset));
  FDRE \Delay18_out1_reg[12] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in18[12]),
        .Q(Delay18_out1[12]),
        .R(reset));
  FDRE \Delay18_out1_reg[13] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in18[13]),
        .Q(Delay18_out1[13]),
        .R(reset));
  FDRE \Delay18_out1_reg[14] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in18[14]),
        .Q(Delay18_out1[14]),
        .R(reset));
  FDRE \Delay18_out1_reg[15] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in18[15]),
        .Q(Delay18_out1[15]),
        .R(reset));
  FDRE \Delay18_out1_reg[16] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in18[16]),
        .Q(Delay18_out1[16]),
        .R(reset));
  FDRE \Delay18_out1_reg[17] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in18[17]),
        .Q(Delay18_out1[17]),
        .R(reset));
  FDRE \Delay18_out1_reg[18] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in18[18]),
        .Q(Delay18_out1[18]),
        .R(reset));
  FDRE \Delay18_out1_reg[19] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in18[19]),
        .Q(Delay18_out1[19]),
        .R(reset));
  FDRE \Delay18_out1_reg[1] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in18[1]),
        .Q(Delay18_out1[1]),
        .R(reset));
  FDRE \Delay18_out1_reg[20] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in18[20]),
        .Q(Delay18_out1[20]),
        .R(reset));
  FDRE \Delay18_out1_reg[21] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in18[21]),
        .Q(Delay18_out1[21]),
        .R(reset));
  FDRE \Delay18_out1_reg[22] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in18[22]),
        .Q(Delay18_out1[22]),
        .R(reset));
  FDRE \Delay18_out1_reg[23] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in18[23]),
        .Q(Delay18_out1[23]),
        .R(reset));
  FDRE \Delay18_out1_reg[24] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in18[24]),
        .Q(Delay18_out1[24]),
        .R(reset));
  FDRE \Delay18_out1_reg[25] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in18[25]),
        .Q(Delay18_out1[25]),
        .R(reset));
  FDRE \Delay18_out1_reg[26] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in18[26]),
        .Q(Delay18_out1[26]),
        .R(reset));
  FDRE \Delay18_out1_reg[2] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in18[2]),
        .Q(Delay18_out1[2]),
        .R(reset));
  FDRE \Delay18_out1_reg[3] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in18[3]),
        .Q(Delay18_out1[3]),
        .R(reset));
  FDRE \Delay18_out1_reg[4] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in18[4]),
        .Q(Delay18_out1[4]),
        .R(reset));
  FDRE \Delay18_out1_reg[5] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in18[5]),
        .Q(Delay18_out1[5]),
        .R(reset));
  FDRE \Delay18_out1_reg[6] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in18[6]),
        .Q(Delay18_out1[6]),
        .R(reset));
  FDRE \Delay18_out1_reg[7] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in18[7]),
        .Q(Delay18_out1[7]),
        .R(reset));
  FDRE \Delay18_out1_reg[8] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in18[8]),
        .Q(Delay18_out1[8]),
        .R(reset));
  FDRE \Delay18_out1_reg[9] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in18[9]),
        .Q(Delay18_out1[9]),
        .R(reset));
  FDRE \Delay19_out1_reg[0] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in19[0]),
        .Q(Delay19_out1[0]),
        .R(reset));
  FDRE \Delay19_out1_reg[10] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in19[10]),
        .Q(Delay19_out1[10]),
        .R(reset));
  FDRE \Delay19_out1_reg[11] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in19[11]),
        .Q(Delay19_out1[11]),
        .R(reset));
  FDRE \Delay19_out1_reg[12] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in19[12]),
        .Q(Delay19_out1[12]),
        .R(reset));
  FDRE \Delay19_out1_reg[13] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in19[13]),
        .Q(Delay19_out1[13]),
        .R(reset));
  FDRE \Delay19_out1_reg[14] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in19[14]),
        .Q(Delay19_out1[14]),
        .R(reset));
  FDRE \Delay19_out1_reg[15] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in19[15]),
        .Q(Delay19_out1[15]),
        .R(reset));
  FDRE \Delay19_out1_reg[16] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in19[16]),
        .Q(Delay19_out1[16]),
        .R(reset));
  FDRE \Delay19_out1_reg[17] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in19[17]),
        .Q(Delay19_out1[17]),
        .R(reset));
  FDRE \Delay19_out1_reg[18] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in19[18]),
        .Q(Delay19_out1[18]),
        .R(reset));
  FDRE \Delay19_out1_reg[19] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in19[19]),
        .Q(Delay19_out1[19]),
        .R(reset));
  FDRE \Delay19_out1_reg[1] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in19[1]),
        .Q(Delay19_out1[1]),
        .R(reset));
  FDRE \Delay19_out1_reg[20] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in19[20]),
        .Q(Delay19_out1[20]),
        .R(reset));
  FDRE \Delay19_out1_reg[21] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in19[21]),
        .Q(Delay19_out1[21]),
        .R(reset));
  FDRE \Delay19_out1_reg[22] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in19[22]),
        .Q(Delay19_out1[22]),
        .R(reset));
  FDRE \Delay19_out1_reg[23] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in19[23]),
        .Q(Delay19_out1[23]),
        .R(reset));
  FDRE \Delay19_out1_reg[24] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in19[24]),
        .Q(Delay19_out1[24]),
        .R(reset));
  FDRE \Delay19_out1_reg[25] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in19[25]),
        .Q(Delay19_out1[25]),
        .R(reset));
  FDRE \Delay19_out1_reg[26] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in19[26]),
        .Q(Delay19_out1[26]),
        .R(reset));
  FDRE \Delay19_out1_reg[2] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in19[2]),
        .Q(Delay19_out1[2]),
        .R(reset));
  FDRE \Delay19_out1_reg[3] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in19[3]),
        .Q(Delay19_out1[3]),
        .R(reset));
  FDRE \Delay19_out1_reg[4] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in19[4]),
        .Q(Delay19_out1[4]),
        .R(reset));
  FDRE \Delay19_out1_reg[5] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in19[5]),
        .Q(Delay19_out1[5]),
        .R(reset));
  FDRE \Delay19_out1_reg[6] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in19[6]),
        .Q(Delay19_out1[6]),
        .R(reset));
  FDRE \Delay19_out1_reg[7] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in19[7]),
        .Q(Delay19_out1[7]),
        .R(reset));
  FDRE \Delay19_out1_reg[8] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in19[8]),
        .Q(Delay19_out1[8]),
        .R(reset));
  FDRE \Delay19_out1_reg[9] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in19[9]),
        .Q(Delay19_out1[9]),
        .R(reset));
  FDRE \Delay1_out1_reg[0] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in1[0]),
        .Q(Delay1_out1[0]),
        .R(reset));
  FDRE \Delay1_out1_reg[10] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in1[10]),
        .Q(Delay1_out1[10]),
        .R(reset));
  FDRE \Delay1_out1_reg[11] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in1[11]),
        .Q(Delay1_out1[11]),
        .R(reset));
  FDRE \Delay1_out1_reg[12] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in1[12]),
        .Q(Delay1_out1[12]),
        .R(reset));
  FDRE \Delay1_out1_reg[13] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in1[13]),
        .Q(Delay1_out1[13]),
        .R(reset));
  FDRE \Delay1_out1_reg[14] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in1[14]),
        .Q(Delay1_out1[14]),
        .R(reset));
  FDRE \Delay1_out1_reg[15] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in1[15]),
        .Q(Delay1_out1[15]),
        .R(reset));
  FDRE \Delay1_out1_reg[16] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in1[16]),
        .Q(Delay1_out1[16]),
        .R(reset));
  FDRE \Delay1_out1_reg[17] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in1[17]),
        .Q(Delay1_out1[17]),
        .R(reset));
  FDRE \Delay1_out1_reg[18] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in1[18]),
        .Q(Delay1_out1[18]),
        .R(reset));
  FDRE \Delay1_out1_reg[19] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in1[19]),
        .Q(Delay1_out1[19]),
        .R(reset));
  FDRE \Delay1_out1_reg[1] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in1[1]),
        .Q(Delay1_out1[1]),
        .R(reset));
  FDRE \Delay1_out1_reg[20] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in1[20]),
        .Q(Delay1_out1[20]),
        .R(reset));
  FDRE \Delay1_out1_reg[21] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in1[21]),
        .Q(Delay1_out1[21]),
        .R(reset));
  FDRE \Delay1_out1_reg[22] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in1[22]),
        .Q(Delay1_out1[22]),
        .R(reset));
  FDRE \Delay1_out1_reg[23] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in1[23]),
        .Q(Delay1_out1[23]),
        .R(reset));
  FDRE \Delay1_out1_reg[24] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in1[24]),
        .Q(Delay1_out1[24]),
        .R(reset));
  FDRE \Delay1_out1_reg[25] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in1[25]),
        .Q(Delay1_out1[25]),
        .R(reset));
  FDRE \Delay1_out1_reg[26] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in1[26]),
        .Q(Delay1_out1[26]),
        .R(reset));
  FDRE \Delay1_out1_reg[2] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in1[2]),
        .Q(Delay1_out1[2]),
        .R(reset));
  FDRE \Delay1_out1_reg[3] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in1[3]),
        .Q(Delay1_out1[3]),
        .R(reset));
  FDRE \Delay1_out1_reg[4] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in1[4]),
        .Q(Delay1_out1[4]),
        .R(reset));
  FDRE \Delay1_out1_reg[5] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in1[5]),
        .Q(Delay1_out1[5]),
        .R(reset));
  FDRE \Delay1_out1_reg[6] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in1[6]),
        .Q(Delay1_out1[6]),
        .R(reset));
  FDRE \Delay1_out1_reg[7] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in1[7]),
        .Q(Delay1_out1[7]),
        .R(reset));
  FDRE \Delay1_out1_reg[8] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in1[8]),
        .Q(Delay1_out1[8]),
        .R(reset));
  FDRE \Delay1_out1_reg[9] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in1[9]),
        .Q(Delay1_out1[9]),
        .R(reset));
  FDRE \Delay20_out1_reg[0] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in20[0]),
        .Q(Delay20_out1[0]),
        .R(reset));
  FDRE \Delay20_out1_reg[10] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in20[10]),
        .Q(Delay20_out1[10]),
        .R(reset));
  FDRE \Delay20_out1_reg[11] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in20[11]),
        .Q(Delay20_out1[11]),
        .R(reset));
  FDRE \Delay20_out1_reg[12] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in20[12]),
        .Q(Delay20_out1[12]),
        .R(reset));
  FDRE \Delay20_out1_reg[13] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in20[13]),
        .Q(Delay20_out1[13]),
        .R(reset));
  FDRE \Delay20_out1_reg[14] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in20[14]),
        .Q(Delay20_out1[14]),
        .R(reset));
  FDRE \Delay20_out1_reg[15] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in20[15]),
        .Q(Delay20_out1[15]),
        .R(reset));
  FDRE \Delay20_out1_reg[16] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in20[16]),
        .Q(Delay20_out1[16]),
        .R(reset));
  FDRE \Delay20_out1_reg[17] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in20[17]),
        .Q(Delay20_out1[17]),
        .R(reset));
  FDRE \Delay20_out1_reg[18] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in20[18]),
        .Q(Delay20_out1[18]),
        .R(reset));
  FDRE \Delay20_out1_reg[19] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in20[19]),
        .Q(Delay20_out1[19]),
        .R(reset));
  FDRE \Delay20_out1_reg[1] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in20[1]),
        .Q(Delay20_out1[1]),
        .R(reset));
  FDRE \Delay20_out1_reg[20] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in20[20]),
        .Q(Delay20_out1[20]),
        .R(reset));
  FDRE \Delay20_out1_reg[21] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in20[21]),
        .Q(Delay20_out1[21]),
        .R(reset));
  FDRE \Delay20_out1_reg[22] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in20[22]),
        .Q(Delay20_out1[22]),
        .R(reset));
  FDRE \Delay20_out1_reg[23] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in20[23]),
        .Q(Delay20_out1[23]),
        .R(reset));
  FDRE \Delay20_out1_reg[24] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in20[24]),
        .Q(Delay20_out1[24]),
        .R(reset));
  FDRE \Delay20_out1_reg[25] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in20[25]),
        .Q(Delay20_out1[25]),
        .R(reset));
  FDRE \Delay20_out1_reg[26] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in20[26]),
        .Q(Delay20_out1[26]),
        .R(reset));
  FDRE \Delay20_out1_reg[2] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in20[2]),
        .Q(Delay20_out1[2]),
        .R(reset));
  FDRE \Delay20_out1_reg[3] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in20[3]),
        .Q(Delay20_out1[3]),
        .R(reset));
  FDRE \Delay20_out1_reg[4] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in20[4]),
        .Q(Delay20_out1[4]),
        .R(reset));
  FDRE \Delay20_out1_reg[5] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in20[5]),
        .Q(Delay20_out1[5]),
        .R(reset));
  FDRE \Delay20_out1_reg[6] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in20[6]),
        .Q(Delay20_out1[6]),
        .R(reset));
  FDRE \Delay20_out1_reg[7] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in20[7]),
        .Q(Delay20_out1[7]),
        .R(reset));
  FDRE \Delay20_out1_reg[8] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in20[8]),
        .Q(Delay20_out1[8]),
        .R(reset));
  FDRE \Delay20_out1_reg[9] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in20[9]),
        .Q(Delay20_out1[9]),
        .R(reset));
  FDRE \Delay21_out1_reg[0] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in21[0]),
        .Q(Delay21_out1[0]),
        .R(reset));
  FDRE \Delay21_out1_reg[10] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in21[10]),
        .Q(Delay21_out1[10]),
        .R(reset));
  FDRE \Delay21_out1_reg[11] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in21[11]),
        .Q(Delay21_out1[11]),
        .R(reset));
  FDRE \Delay21_out1_reg[12] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in21[12]),
        .Q(Delay21_out1[12]),
        .R(reset));
  FDRE \Delay21_out1_reg[13] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in21[13]),
        .Q(Delay21_out1[13]),
        .R(reset));
  FDRE \Delay21_out1_reg[14] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in21[14]),
        .Q(Delay21_out1[14]),
        .R(reset));
  FDRE \Delay21_out1_reg[15] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in21[15]),
        .Q(Delay21_out1[15]),
        .R(reset));
  FDRE \Delay21_out1_reg[16] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in21[16]),
        .Q(Delay21_out1[16]),
        .R(reset));
  FDRE \Delay21_out1_reg[17] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in21[17]),
        .Q(Delay21_out1[17]),
        .R(reset));
  FDRE \Delay21_out1_reg[18] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in21[18]),
        .Q(Delay21_out1[18]),
        .R(reset));
  FDRE \Delay21_out1_reg[19] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in21[19]),
        .Q(Delay21_out1[19]),
        .R(reset));
  FDRE \Delay21_out1_reg[1] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in21[1]),
        .Q(Delay21_out1[1]),
        .R(reset));
  FDRE \Delay21_out1_reg[20] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in21[20]),
        .Q(Delay21_out1[20]),
        .R(reset));
  FDRE \Delay21_out1_reg[21] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in21[21]),
        .Q(Delay21_out1[21]),
        .R(reset));
  FDRE \Delay21_out1_reg[22] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in21[22]),
        .Q(Delay21_out1[22]),
        .R(reset));
  FDRE \Delay21_out1_reg[23] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in21[23]),
        .Q(Delay21_out1[23]),
        .R(reset));
  FDRE \Delay21_out1_reg[24] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in21[24]),
        .Q(Delay21_out1[24]),
        .R(reset));
  FDRE \Delay21_out1_reg[25] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in21[25]),
        .Q(Delay21_out1[25]),
        .R(reset));
  FDRE \Delay21_out1_reg[26] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in21[26]),
        .Q(Delay21_out1[26]),
        .R(reset));
  FDRE \Delay21_out1_reg[2] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in21[2]),
        .Q(Delay21_out1[2]),
        .R(reset));
  FDRE \Delay21_out1_reg[3] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in21[3]),
        .Q(Delay21_out1[3]),
        .R(reset));
  FDRE \Delay21_out1_reg[4] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in21[4]),
        .Q(Delay21_out1[4]),
        .R(reset));
  FDRE \Delay21_out1_reg[5] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in21[5]),
        .Q(Delay21_out1[5]),
        .R(reset));
  FDRE \Delay21_out1_reg[6] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in21[6]),
        .Q(Delay21_out1[6]),
        .R(reset));
  FDRE \Delay21_out1_reg[7] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in21[7]),
        .Q(Delay21_out1[7]),
        .R(reset));
  FDRE \Delay21_out1_reg[8] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in21[8]),
        .Q(Delay21_out1[8]),
        .R(reset));
  FDRE \Delay21_out1_reg[9] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in21[9]),
        .Q(Delay21_out1[9]),
        .R(reset));
  FDRE \Delay22_out1_reg[0] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in22[0]),
        .Q(Delay22_out1[0]),
        .R(reset));
  FDRE \Delay22_out1_reg[10] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in22[10]),
        .Q(Delay22_out1[10]),
        .R(reset));
  FDRE \Delay22_out1_reg[11] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in22[11]),
        .Q(Delay22_out1[11]),
        .R(reset));
  FDRE \Delay22_out1_reg[12] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in22[12]),
        .Q(Delay22_out1[12]),
        .R(reset));
  FDRE \Delay22_out1_reg[13] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in22[13]),
        .Q(Delay22_out1[13]),
        .R(reset));
  FDRE \Delay22_out1_reg[14] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in22[14]),
        .Q(Delay22_out1[14]),
        .R(reset));
  FDRE \Delay22_out1_reg[15] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in22[15]),
        .Q(Delay22_out1[15]),
        .R(reset));
  FDRE \Delay22_out1_reg[16] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in22[16]),
        .Q(Delay22_out1[16]),
        .R(reset));
  FDRE \Delay22_out1_reg[17] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in22[17]),
        .Q(Delay22_out1[17]),
        .R(reset));
  FDRE \Delay22_out1_reg[18] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in22[18]),
        .Q(Delay22_out1[18]),
        .R(reset));
  FDRE \Delay22_out1_reg[19] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in22[19]),
        .Q(Delay22_out1[19]),
        .R(reset));
  FDRE \Delay22_out1_reg[1] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in22[1]),
        .Q(Delay22_out1[1]),
        .R(reset));
  FDRE \Delay22_out1_reg[20] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in22[20]),
        .Q(Delay22_out1[20]),
        .R(reset));
  FDRE \Delay22_out1_reg[21] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in22[21]),
        .Q(Delay22_out1[21]),
        .R(reset));
  FDRE \Delay22_out1_reg[22] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in22[22]),
        .Q(Delay22_out1[22]),
        .R(reset));
  FDRE \Delay22_out1_reg[23] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in22[23]),
        .Q(Delay22_out1[23]),
        .R(reset));
  FDRE \Delay22_out1_reg[24] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in22[24]),
        .Q(Delay22_out1[24]),
        .R(reset));
  FDRE \Delay22_out1_reg[25] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in22[25]),
        .Q(Delay22_out1[25]),
        .R(reset));
  FDRE \Delay22_out1_reg[26] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in22[26]),
        .Q(Delay22_out1[26]),
        .R(reset));
  FDRE \Delay22_out1_reg[2] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in22[2]),
        .Q(Delay22_out1[2]),
        .R(reset));
  FDRE \Delay22_out1_reg[3] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in22[3]),
        .Q(Delay22_out1[3]),
        .R(reset));
  FDRE \Delay22_out1_reg[4] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in22[4]),
        .Q(Delay22_out1[4]),
        .R(reset));
  FDRE \Delay22_out1_reg[5] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in22[5]),
        .Q(Delay22_out1[5]),
        .R(reset));
  FDRE \Delay22_out1_reg[6] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in22[6]),
        .Q(Delay22_out1[6]),
        .R(reset));
  FDRE \Delay22_out1_reg[7] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in22[7]),
        .Q(Delay22_out1[7]),
        .R(reset));
  FDRE \Delay22_out1_reg[8] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in22[8]),
        .Q(Delay22_out1[8]),
        .R(reset));
  FDRE \Delay22_out1_reg[9] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in22[9]),
        .Q(Delay22_out1[9]),
        .R(reset));
  FDRE \Delay23_out1_reg[0] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in23[0]),
        .Q(Delay23_out1[0]),
        .R(reset));
  FDRE \Delay23_out1_reg[10] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in23[10]),
        .Q(Delay23_out1[10]),
        .R(reset));
  FDRE \Delay23_out1_reg[11] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in23[11]),
        .Q(Delay23_out1[11]),
        .R(reset));
  FDRE \Delay23_out1_reg[12] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in23[12]),
        .Q(Delay23_out1[12]),
        .R(reset));
  FDRE \Delay23_out1_reg[13] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in23[13]),
        .Q(Delay23_out1[13]),
        .R(reset));
  FDRE \Delay23_out1_reg[14] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in23[14]),
        .Q(Delay23_out1[14]),
        .R(reset));
  FDRE \Delay23_out1_reg[15] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in23[15]),
        .Q(Delay23_out1[15]),
        .R(reset));
  FDRE \Delay23_out1_reg[16] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in23[16]),
        .Q(Delay23_out1[16]),
        .R(reset));
  FDRE \Delay23_out1_reg[17] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in23[17]),
        .Q(Delay23_out1[17]),
        .R(reset));
  FDRE \Delay23_out1_reg[18] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in23[18]),
        .Q(Delay23_out1[18]),
        .R(reset));
  FDRE \Delay23_out1_reg[19] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in23[19]),
        .Q(Delay23_out1[19]),
        .R(reset));
  FDRE \Delay23_out1_reg[1] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in23[1]),
        .Q(Delay23_out1[1]),
        .R(reset));
  FDRE \Delay23_out1_reg[20] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in23[20]),
        .Q(Delay23_out1[20]),
        .R(reset));
  FDRE \Delay23_out1_reg[21] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in23[21]),
        .Q(Delay23_out1[21]),
        .R(reset));
  FDRE \Delay23_out1_reg[22] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in23[22]),
        .Q(Delay23_out1[22]),
        .R(reset));
  FDRE \Delay23_out1_reg[23] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in23[23]),
        .Q(Delay23_out1[23]),
        .R(reset));
  FDRE \Delay23_out1_reg[24] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in23[24]),
        .Q(Delay23_out1[24]),
        .R(reset));
  FDRE \Delay23_out1_reg[25] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in23[25]),
        .Q(Delay23_out1[25]),
        .R(reset));
  FDRE \Delay23_out1_reg[26] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in23[26]),
        .Q(Delay23_out1[26]),
        .R(reset));
  FDRE \Delay23_out1_reg[2] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in23[2]),
        .Q(Delay23_out1[2]),
        .R(reset));
  FDRE \Delay23_out1_reg[3] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in23[3]),
        .Q(Delay23_out1[3]),
        .R(reset));
  FDRE \Delay23_out1_reg[4] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in23[4]),
        .Q(Delay23_out1[4]),
        .R(reset));
  FDRE \Delay23_out1_reg[5] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in23[5]),
        .Q(Delay23_out1[5]),
        .R(reset));
  FDRE \Delay23_out1_reg[6] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in23[6]),
        .Q(Delay23_out1[6]),
        .R(reset));
  FDRE \Delay23_out1_reg[7] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in23[7]),
        .Q(Delay23_out1[7]),
        .R(reset));
  FDRE \Delay23_out1_reg[8] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in23[8]),
        .Q(Delay23_out1[8]),
        .R(reset));
  FDRE \Delay23_out1_reg[9] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in23[9]),
        .Q(Delay23_out1[9]),
        .R(reset));
  FDRE \Delay24_out1_reg[0] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in24[0]),
        .Q(Delay24_out1[0]),
        .R(reset));
  FDRE \Delay24_out1_reg[10] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in24[10]),
        .Q(Delay24_out1[10]),
        .R(reset));
  FDRE \Delay24_out1_reg[11] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in24[11]),
        .Q(Delay24_out1[11]),
        .R(reset));
  FDRE \Delay24_out1_reg[12] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in24[12]),
        .Q(Delay24_out1[12]),
        .R(reset));
  FDRE \Delay24_out1_reg[13] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in24[13]),
        .Q(Delay24_out1[13]),
        .R(reset));
  FDRE \Delay24_out1_reg[14] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in24[14]),
        .Q(Delay24_out1[14]),
        .R(reset));
  FDRE \Delay24_out1_reg[15] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in24[15]),
        .Q(Delay24_out1[15]),
        .R(reset));
  FDRE \Delay24_out1_reg[16] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in24[16]),
        .Q(Delay24_out1[16]),
        .R(reset));
  FDRE \Delay24_out1_reg[17] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in24[17]),
        .Q(Delay24_out1[17]),
        .R(reset));
  FDRE \Delay24_out1_reg[18] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in24[18]),
        .Q(Delay24_out1[18]),
        .R(reset));
  FDRE \Delay24_out1_reg[19] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in24[19]),
        .Q(Delay24_out1[19]),
        .R(reset));
  FDRE \Delay24_out1_reg[1] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in24[1]),
        .Q(Delay24_out1[1]),
        .R(reset));
  FDRE \Delay24_out1_reg[20] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in24[20]),
        .Q(Delay24_out1[20]),
        .R(reset));
  FDRE \Delay24_out1_reg[21] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in24[21]),
        .Q(Delay24_out1[21]),
        .R(reset));
  FDRE \Delay24_out1_reg[22] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in24[22]),
        .Q(Delay24_out1[22]),
        .R(reset));
  FDRE \Delay24_out1_reg[23] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in24[23]),
        .Q(Delay24_out1[23]),
        .R(reset));
  FDRE \Delay24_out1_reg[24] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in24[24]),
        .Q(Delay24_out1[24]),
        .R(reset));
  FDRE \Delay24_out1_reg[25] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in24[25]),
        .Q(Delay24_out1[25]),
        .R(reset));
  FDRE \Delay24_out1_reg[26] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in24[26]),
        .Q(Delay24_out1[26]),
        .R(reset));
  FDRE \Delay24_out1_reg[2] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in24[2]),
        .Q(Delay24_out1[2]),
        .R(reset));
  FDRE \Delay24_out1_reg[3] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in24[3]),
        .Q(Delay24_out1[3]),
        .R(reset));
  FDRE \Delay24_out1_reg[4] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in24[4]),
        .Q(Delay24_out1[4]),
        .R(reset));
  FDRE \Delay24_out1_reg[5] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in24[5]),
        .Q(Delay24_out1[5]),
        .R(reset));
  FDRE \Delay24_out1_reg[6] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in24[6]),
        .Q(Delay24_out1[6]),
        .R(reset));
  FDRE \Delay24_out1_reg[7] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in24[7]),
        .Q(Delay24_out1[7]),
        .R(reset));
  FDRE \Delay24_out1_reg[8] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in24[8]),
        .Q(Delay24_out1[8]),
        .R(reset));
  FDRE \Delay24_out1_reg[9] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in24[9]),
        .Q(Delay24_out1[9]),
        .R(reset));
  FDRE \Delay25_out1_reg[0] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in25[0]),
        .Q(Delay25_out1[0]),
        .R(reset));
  FDRE \Delay25_out1_reg[10] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in25[10]),
        .Q(Delay25_out1[10]),
        .R(reset));
  FDRE \Delay25_out1_reg[11] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in25[11]),
        .Q(Delay25_out1[11]),
        .R(reset));
  FDRE \Delay25_out1_reg[12] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in25[12]),
        .Q(Delay25_out1[12]),
        .R(reset));
  FDRE \Delay25_out1_reg[13] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in25[13]),
        .Q(Delay25_out1[13]),
        .R(reset));
  FDRE \Delay25_out1_reg[14] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in25[14]),
        .Q(Delay25_out1[14]),
        .R(reset));
  FDRE \Delay25_out1_reg[15] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in25[15]),
        .Q(Delay25_out1[15]),
        .R(reset));
  FDRE \Delay25_out1_reg[16] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in25[16]),
        .Q(Delay25_out1[16]),
        .R(reset));
  FDRE \Delay25_out1_reg[17] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in25[17]),
        .Q(Delay25_out1[17]),
        .R(reset));
  FDRE \Delay25_out1_reg[18] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in25[18]),
        .Q(Delay25_out1[18]),
        .R(reset));
  FDRE \Delay25_out1_reg[19] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in25[19]),
        .Q(Delay25_out1[19]),
        .R(reset));
  FDRE \Delay25_out1_reg[1] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in25[1]),
        .Q(Delay25_out1[1]),
        .R(reset));
  FDRE \Delay25_out1_reg[20] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in25[20]),
        .Q(Delay25_out1[20]),
        .R(reset));
  FDRE \Delay25_out1_reg[21] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in25[21]),
        .Q(Delay25_out1[21]),
        .R(reset));
  FDRE \Delay25_out1_reg[22] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in25[22]),
        .Q(Delay25_out1[22]),
        .R(reset));
  FDRE \Delay25_out1_reg[23] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in25[23]),
        .Q(Delay25_out1[23]),
        .R(reset));
  FDRE \Delay25_out1_reg[24] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in25[24]),
        .Q(Delay25_out1[24]),
        .R(reset));
  FDRE \Delay25_out1_reg[25] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in25[25]),
        .Q(Delay25_out1[25]),
        .R(reset));
  FDRE \Delay25_out1_reg[26] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in25[26]),
        .Q(Delay25_out1[26]),
        .R(reset));
  FDRE \Delay25_out1_reg[2] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in25[2]),
        .Q(Delay25_out1[2]),
        .R(reset));
  FDRE \Delay25_out1_reg[3] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in25[3]),
        .Q(Delay25_out1[3]),
        .R(reset));
  FDRE \Delay25_out1_reg[4] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in25[4]),
        .Q(Delay25_out1[4]),
        .R(reset));
  FDRE \Delay25_out1_reg[5] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in25[5]),
        .Q(Delay25_out1[5]),
        .R(reset));
  FDRE \Delay25_out1_reg[6] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in25[6]),
        .Q(Delay25_out1[6]),
        .R(reset));
  FDRE \Delay25_out1_reg[7] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in25[7]),
        .Q(Delay25_out1[7]),
        .R(reset));
  FDRE \Delay25_out1_reg[8] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in25[8]),
        .Q(Delay25_out1[8]),
        .R(reset));
  FDRE \Delay25_out1_reg[9] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in25[9]),
        .Q(Delay25_out1[9]),
        .R(reset));
  FDRE \Delay26_out1_reg[0] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in26[0]),
        .Q(Delay26_out1[0]),
        .R(reset));
  FDRE \Delay26_out1_reg[10] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in26[10]),
        .Q(Delay26_out1[10]),
        .R(reset));
  FDRE \Delay26_out1_reg[11] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in26[11]),
        .Q(Delay26_out1[11]),
        .R(reset));
  FDRE \Delay26_out1_reg[12] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in26[12]),
        .Q(Delay26_out1[12]),
        .R(reset));
  FDRE \Delay26_out1_reg[13] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in26[13]),
        .Q(Delay26_out1[13]),
        .R(reset));
  FDRE \Delay26_out1_reg[14] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in26[14]),
        .Q(Delay26_out1[14]),
        .R(reset));
  FDRE \Delay26_out1_reg[15] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in26[15]),
        .Q(Delay26_out1[15]),
        .R(reset));
  FDRE \Delay26_out1_reg[16] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in26[16]),
        .Q(Delay26_out1[16]),
        .R(reset));
  FDRE \Delay26_out1_reg[17] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in26[17]),
        .Q(Delay26_out1[17]),
        .R(reset));
  FDRE \Delay26_out1_reg[18] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in26[18]),
        .Q(Delay26_out1[18]),
        .R(reset));
  FDRE \Delay26_out1_reg[19] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in26[19]),
        .Q(Delay26_out1[19]),
        .R(reset));
  FDRE \Delay26_out1_reg[1] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in26[1]),
        .Q(Delay26_out1[1]),
        .R(reset));
  FDRE \Delay26_out1_reg[20] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in26[20]),
        .Q(Delay26_out1[20]),
        .R(reset));
  FDRE \Delay26_out1_reg[21] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in26[21]),
        .Q(Delay26_out1[21]),
        .R(reset));
  FDRE \Delay26_out1_reg[22] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in26[22]),
        .Q(Delay26_out1[22]),
        .R(reset));
  FDRE \Delay26_out1_reg[23] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in26[23]),
        .Q(Delay26_out1[23]),
        .R(reset));
  FDRE \Delay26_out1_reg[24] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in26[24]),
        .Q(Delay26_out1[24]),
        .R(reset));
  FDRE \Delay26_out1_reg[25] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in26[25]),
        .Q(Delay26_out1[25]),
        .R(reset));
  FDRE \Delay26_out1_reg[26] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in26[26]),
        .Q(Delay26_out1[26]),
        .R(reset));
  FDRE \Delay26_out1_reg[2] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in26[2]),
        .Q(Delay26_out1[2]),
        .R(reset));
  FDRE \Delay26_out1_reg[3] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in26[3]),
        .Q(Delay26_out1[3]),
        .R(reset));
  FDRE \Delay26_out1_reg[4] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in26[4]),
        .Q(Delay26_out1[4]),
        .R(reset));
  FDRE \Delay26_out1_reg[5] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in26[5]),
        .Q(Delay26_out1[5]),
        .R(reset));
  FDRE \Delay26_out1_reg[6] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in26[6]),
        .Q(Delay26_out1[6]),
        .R(reset));
  FDRE \Delay26_out1_reg[7] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in26[7]),
        .Q(Delay26_out1[7]),
        .R(reset));
  FDRE \Delay26_out1_reg[8] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in26[8]),
        .Q(Delay26_out1[8]),
        .R(reset));
  FDRE \Delay26_out1_reg[9] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in26[9]),
        .Q(Delay26_out1[9]),
        .R(reset));
  FDRE \Delay27_out1_reg[0] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in27[0]),
        .Q(Delay27_out1[0]),
        .R(reset));
  FDRE \Delay27_out1_reg[10] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in27[10]),
        .Q(Delay27_out1[10]),
        .R(reset));
  FDRE \Delay27_out1_reg[11] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in27[11]),
        .Q(Delay27_out1[11]),
        .R(reset));
  FDRE \Delay27_out1_reg[12] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in27[12]),
        .Q(Delay27_out1[12]),
        .R(reset));
  FDRE \Delay27_out1_reg[13] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in27[13]),
        .Q(Delay27_out1[13]),
        .R(reset));
  FDRE \Delay27_out1_reg[14] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in27[14]),
        .Q(Delay27_out1[14]),
        .R(reset));
  FDRE \Delay27_out1_reg[15] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in27[15]),
        .Q(Delay27_out1[15]),
        .R(reset));
  FDRE \Delay27_out1_reg[16] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in27[16]),
        .Q(Delay27_out1[16]),
        .R(reset));
  FDRE \Delay27_out1_reg[17] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in27[17]),
        .Q(Delay27_out1[17]),
        .R(reset));
  FDRE \Delay27_out1_reg[18] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in27[18]),
        .Q(Delay27_out1[18]),
        .R(reset));
  FDRE \Delay27_out1_reg[19] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in27[19]),
        .Q(Delay27_out1[19]),
        .R(reset));
  FDRE \Delay27_out1_reg[1] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in27[1]),
        .Q(Delay27_out1[1]),
        .R(reset));
  FDRE \Delay27_out1_reg[20] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in27[20]),
        .Q(Delay27_out1[20]),
        .R(reset));
  FDRE \Delay27_out1_reg[21] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in27[21]),
        .Q(Delay27_out1[21]),
        .R(reset));
  FDRE \Delay27_out1_reg[22] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in27[22]),
        .Q(Delay27_out1[22]),
        .R(reset));
  FDRE \Delay27_out1_reg[23] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in27[23]),
        .Q(Delay27_out1[23]),
        .R(reset));
  FDRE \Delay27_out1_reg[24] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in27[24]),
        .Q(Delay27_out1[24]),
        .R(reset));
  FDRE \Delay27_out1_reg[25] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in27[25]),
        .Q(Delay27_out1[25]),
        .R(reset));
  FDRE \Delay27_out1_reg[26] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in27[26]),
        .Q(Delay27_out1[26]),
        .R(reset));
  FDRE \Delay27_out1_reg[2] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in27[2]),
        .Q(Delay27_out1[2]),
        .R(reset));
  FDRE \Delay27_out1_reg[3] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in27[3]),
        .Q(Delay27_out1[3]),
        .R(reset));
  FDRE \Delay27_out1_reg[4] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in27[4]),
        .Q(Delay27_out1[4]),
        .R(reset));
  FDRE \Delay27_out1_reg[5] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in27[5]),
        .Q(Delay27_out1[5]),
        .R(reset));
  FDRE \Delay27_out1_reg[6] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in27[6]),
        .Q(Delay27_out1[6]),
        .R(reset));
  FDRE \Delay27_out1_reg[7] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in27[7]),
        .Q(Delay27_out1[7]),
        .R(reset));
  FDRE \Delay27_out1_reg[8] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in27[8]),
        .Q(Delay27_out1[8]),
        .R(reset));
  FDRE \Delay27_out1_reg[9] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in27[9]),
        .Q(Delay27_out1[9]),
        .R(reset));
  FDRE \Delay28_out1_reg[0] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in28[0]),
        .Q(Delay28_out1[0]),
        .R(reset));
  FDRE \Delay28_out1_reg[10] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in28[10]),
        .Q(Delay28_out1[10]),
        .R(reset));
  FDRE \Delay28_out1_reg[11] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in28[11]),
        .Q(Delay28_out1[11]),
        .R(reset));
  FDRE \Delay28_out1_reg[12] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in28[12]),
        .Q(Delay28_out1[12]),
        .R(reset));
  FDRE \Delay28_out1_reg[13] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in28[13]),
        .Q(Delay28_out1[13]),
        .R(reset));
  FDRE \Delay28_out1_reg[14] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in28[14]),
        .Q(Delay28_out1[14]),
        .R(reset));
  FDRE \Delay28_out1_reg[15] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in28[15]),
        .Q(Delay28_out1[15]),
        .R(reset));
  FDRE \Delay28_out1_reg[16] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in28[16]),
        .Q(Delay28_out1[16]),
        .R(reset));
  FDRE \Delay28_out1_reg[17] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in28[17]),
        .Q(Delay28_out1[17]),
        .R(reset));
  FDRE \Delay28_out1_reg[18] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in28[18]),
        .Q(Delay28_out1[18]),
        .R(reset));
  FDRE \Delay28_out1_reg[19] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in28[19]),
        .Q(Delay28_out1[19]),
        .R(reset));
  FDRE \Delay28_out1_reg[1] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in28[1]),
        .Q(Delay28_out1[1]),
        .R(reset));
  FDRE \Delay28_out1_reg[20] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in28[20]),
        .Q(Delay28_out1[20]),
        .R(reset));
  FDRE \Delay28_out1_reg[21] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in28[21]),
        .Q(Delay28_out1[21]),
        .R(reset));
  FDRE \Delay28_out1_reg[22] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in28[22]),
        .Q(Delay28_out1[22]),
        .R(reset));
  FDRE \Delay28_out1_reg[23] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in28[23]),
        .Q(Delay28_out1[23]),
        .R(reset));
  FDRE \Delay28_out1_reg[24] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in28[24]),
        .Q(Delay28_out1[24]),
        .R(reset));
  FDRE \Delay28_out1_reg[25] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in28[25]),
        .Q(Delay28_out1[25]),
        .R(reset));
  FDRE \Delay28_out1_reg[26] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in28[26]),
        .Q(Delay28_out1[26]),
        .R(reset));
  FDRE \Delay28_out1_reg[2] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in28[2]),
        .Q(Delay28_out1[2]),
        .R(reset));
  FDRE \Delay28_out1_reg[3] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in28[3]),
        .Q(Delay28_out1[3]),
        .R(reset));
  FDRE \Delay28_out1_reg[4] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in28[4]),
        .Q(Delay28_out1[4]),
        .R(reset));
  FDRE \Delay28_out1_reg[5] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in28[5]),
        .Q(Delay28_out1[5]),
        .R(reset));
  FDRE \Delay28_out1_reg[6] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in28[6]),
        .Q(Delay28_out1[6]),
        .R(reset));
  FDRE \Delay28_out1_reg[7] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in28[7]),
        .Q(Delay28_out1[7]),
        .R(reset));
  FDRE \Delay28_out1_reg[8] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in28[8]),
        .Q(Delay28_out1[8]),
        .R(reset));
  FDRE \Delay28_out1_reg[9] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in28[9]),
        .Q(Delay28_out1[9]),
        .R(reset));
  FDRE \Delay29_out1_reg[0] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in29[0]),
        .Q(Delay29_out1[0]),
        .R(reset));
  FDRE \Delay29_out1_reg[10] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in29[10]),
        .Q(Delay29_out1[10]),
        .R(reset));
  FDRE \Delay29_out1_reg[11] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in29[11]),
        .Q(Delay29_out1[11]),
        .R(reset));
  FDRE \Delay29_out1_reg[12] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in29[12]),
        .Q(Delay29_out1[12]),
        .R(reset));
  FDRE \Delay29_out1_reg[13] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in29[13]),
        .Q(Delay29_out1[13]),
        .R(reset));
  FDRE \Delay29_out1_reg[14] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in29[14]),
        .Q(Delay29_out1[14]),
        .R(reset));
  FDRE \Delay29_out1_reg[15] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in29[15]),
        .Q(Delay29_out1[15]),
        .R(reset));
  FDRE \Delay29_out1_reg[16] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in29[16]),
        .Q(Delay29_out1[16]),
        .R(reset));
  FDRE \Delay29_out1_reg[17] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in29[17]),
        .Q(Delay29_out1[17]),
        .R(reset));
  FDRE \Delay29_out1_reg[18] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in29[18]),
        .Q(Delay29_out1[18]),
        .R(reset));
  FDRE \Delay29_out1_reg[19] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in29[19]),
        .Q(Delay29_out1[19]),
        .R(reset));
  FDRE \Delay29_out1_reg[1] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in29[1]),
        .Q(Delay29_out1[1]),
        .R(reset));
  FDRE \Delay29_out1_reg[20] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in29[20]),
        .Q(Delay29_out1[20]),
        .R(reset));
  FDRE \Delay29_out1_reg[21] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in29[21]),
        .Q(Delay29_out1[21]),
        .R(reset));
  FDRE \Delay29_out1_reg[22] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in29[22]),
        .Q(Delay29_out1[22]),
        .R(reset));
  FDRE \Delay29_out1_reg[23] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in29[23]),
        .Q(Delay29_out1[23]),
        .R(reset));
  FDRE \Delay29_out1_reg[24] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in29[24]),
        .Q(Delay29_out1[24]),
        .R(reset));
  FDRE \Delay29_out1_reg[25] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in29[25]),
        .Q(Delay29_out1[25]),
        .R(reset));
  FDRE \Delay29_out1_reg[26] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in29[26]),
        .Q(Delay29_out1[26]),
        .R(reset));
  FDRE \Delay29_out1_reg[2] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in29[2]),
        .Q(Delay29_out1[2]),
        .R(reset));
  FDRE \Delay29_out1_reg[3] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in29[3]),
        .Q(Delay29_out1[3]),
        .R(reset));
  FDRE \Delay29_out1_reg[4] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in29[4]),
        .Q(Delay29_out1[4]),
        .R(reset));
  FDRE \Delay29_out1_reg[5] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in29[5]),
        .Q(Delay29_out1[5]),
        .R(reset));
  FDRE \Delay29_out1_reg[6] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in29[6]),
        .Q(Delay29_out1[6]),
        .R(reset));
  FDRE \Delay29_out1_reg[7] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in29[7]),
        .Q(Delay29_out1[7]),
        .R(reset));
  FDRE \Delay29_out1_reg[8] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in29[8]),
        .Q(Delay29_out1[8]),
        .R(reset));
  FDRE \Delay29_out1_reg[9] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in29[9]),
        .Q(Delay29_out1[9]),
        .R(reset));
  FDRE \Delay2_out1_reg[0] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in2[0]),
        .Q(Delay2_out1[0]),
        .R(reset));
  FDRE \Delay2_out1_reg[10] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in2[10]),
        .Q(Delay2_out1[10]),
        .R(reset));
  FDRE \Delay2_out1_reg[11] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in2[11]),
        .Q(Delay2_out1[11]),
        .R(reset));
  FDRE \Delay2_out1_reg[12] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in2[12]),
        .Q(Delay2_out1[12]),
        .R(reset));
  FDRE \Delay2_out1_reg[13] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in2[13]),
        .Q(Delay2_out1[13]),
        .R(reset));
  FDRE \Delay2_out1_reg[14] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in2[14]),
        .Q(Delay2_out1[14]),
        .R(reset));
  FDRE \Delay2_out1_reg[15] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in2[15]),
        .Q(Delay2_out1[15]),
        .R(reset));
  FDRE \Delay2_out1_reg[16] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in2[16]),
        .Q(Delay2_out1[16]),
        .R(reset));
  FDRE \Delay2_out1_reg[17] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in2[17]),
        .Q(Delay2_out1[17]),
        .R(reset));
  FDRE \Delay2_out1_reg[18] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in2[18]),
        .Q(Delay2_out1[18]),
        .R(reset));
  FDRE \Delay2_out1_reg[19] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in2[19]),
        .Q(Delay2_out1[19]),
        .R(reset));
  FDRE \Delay2_out1_reg[1] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in2[1]),
        .Q(Delay2_out1[1]),
        .R(reset));
  FDRE \Delay2_out1_reg[20] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in2[20]),
        .Q(Delay2_out1[20]),
        .R(reset));
  FDRE \Delay2_out1_reg[21] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in2[21]),
        .Q(Delay2_out1[21]),
        .R(reset));
  FDRE \Delay2_out1_reg[22] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in2[22]),
        .Q(Delay2_out1[22]),
        .R(reset));
  FDRE \Delay2_out1_reg[23] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in2[23]),
        .Q(Delay2_out1[23]),
        .R(reset));
  FDRE \Delay2_out1_reg[24] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in2[24]),
        .Q(Delay2_out1[24]),
        .R(reset));
  FDRE \Delay2_out1_reg[25] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in2[25]),
        .Q(Delay2_out1[25]),
        .R(reset));
  FDRE \Delay2_out1_reg[26] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in2[26]),
        .Q(Delay2_out1[26]),
        .R(reset));
  FDRE \Delay2_out1_reg[2] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in2[2]),
        .Q(Delay2_out1[2]),
        .R(reset));
  FDRE \Delay2_out1_reg[3] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in2[3]),
        .Q(Delay2_out1[3]),
        .R(reset));
  FDRE \Delay2_out1_reg[4] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in2[4]),
        .Q(Delay2_out1[4]),
        .R(reset));
  FDRE \Delay2_out1_reg[5] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in2[5]),
        .Q(Delay2_out1[5]),
        .R(reset));
  FDRE \Delay2_out1_reg[6] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in2[6]),
        .Q(Delay2_out1[6]),
        .R(reset));
  FDRE \Delay2_out1_reg[7] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in2[7]),
        .Q(Delay2_out1[7]),
        .R(reset));
  FDRE \Delay2_out1_reg[8] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in2[8]),
        .Q(Delay2_out1[8]),
        .R(reset));
  FDRE \Delay2_out1_reg[9] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in2[9]),
        .Q(Delay2_out1[9]),
        .R(reset));
  FDRE \Delay30_out1_reg[0] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in30[0]),
        .Q(Delay30_out1[0]),
        .R(reset));
  FDRE \Delay30_out1_reg[10] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in30[10]),
        .Q(Delay30_out1[10]),
        .R(reset));
  FDRE \Delay30_out1_reg[11] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in30[11]),
        .Q(Delay30_out1[11]),
        .R(reset));
  FDRE \Delay30_out1_reg[12] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in30[12]),
        .Q(Delay30_out1[12]),
        .R(reset));
  FDRE \Delay30_out1_reg[13] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in30[13]),
        .Q(Delay30_out1[13]),
        .R(reset));
  FDRE \Delay30_out1_reg[14] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in30[14]),
        .Q(Delay30_out1[14]),
        .R(reset));
  FDRE \Delay30_out1_reg[15] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in30[15]),
        .Q(Delay30_out1[15]),
        .R(reset));
  FDRE \Delay30_out1_reg[16] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in30[16]),
        .Q(Delay30_out1[16]),
        .R(reset));
  FDRE \Delay30_out1_reg[17] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in30[17]),
        .Q(Delay30_out1[17]),
        .R(reset));
  FDRE \Delay30_out1_reg[18] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in30[18]),
        .Q(Delay30_out1[18]),
        .R(reset));
  FDRE \Delay30_out1_reg[19] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in30[19]),
        .Q(Delay30_out1[19]),
        .R(reset));
  FDRE \Delay30_out1_reg[1] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in30[1]),
        .Q(Delay30_out1[1]),
        .R(reset));
  FDRE \Delay30_out1_reg[20] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in30[20]),
        .Q(Delay30_out1[20]),
        .R(reset));
  FDRE \Delay30_out1_reg[21] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in30[21]),
        .Q(Delay30_out1[21]),
        .R(reset));
  FDRE \Delay30_out1_reg[22] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in30[22]),
        .Q(Delay30_out1[22]),
        .R(reset));
  FDRE \Delay30_out1_reg[23] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in30[23]),
        .Q(Delay30_out1[23]),
        .R(reset));
  FDRE \Delay30_out1_reg[24] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in30[24]),
        .Q(Delay30_out1[24]),
        .R(reset));
  FDRE \Delay30_out1_reg[25] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in30[25]),
        .Q(Delay30_out1[25]),
        .R(reset));
  FDRE \Delay30_out1_reg[26] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in30[26]),
        .Q(Delay30_out1[26]),
        .R(reset));
  FDRE \Delay30_out1_reg[2] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in30[2]),
        .Q(Delay30_out1[2]),
        .R(reset));
  FDRE \Delay30_out1_reg[3] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in30[3]),
        .Q(Delay30_out1[3]),
        .R(reset));
  FDRE \Delay30_out1_reg[4] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in30[4]),
        .Q(Delay30_out1[4]),
        .R(reset));
  FDRE \Delay30_out1_reg[5] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in30[5]),
        .Q(Delay30_out1[5]),
        .R(reset));
  FDRE \Delay30_out1_reg[6] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in30[6]),
        .Q(Delay30_out1[6]),
        .R(reset));
  FDRE \Delay30_out1_reg[7] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in30[7]),
        .Q(Delay30_out1[7]),
        .R(reset));
  FDRE \Delay30_out1_reg[8] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in30[8]),
        .Q(Delay30_out1[8]),
        .R(reset));
  FDRE \Delay30_out1_reg[9] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in30[9]),
        .Q(Delay30_out1[9]),
        .R(reset));
  FDRE \Delay31_out1_reg[0] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in31[0]),
        .Q(Delay31_out1[0]),
        .R(reset));
  FDRE \Delay31_out1_reg[10] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in31[10]),
        .Q(Delay31_out1[10]),
        .R(reset));
  FDRE \Delay31_out1_reg[11] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in31[11]),
        .Q(Delay31_out1[11]),
        .R(reset));
  FDRE \Delay31_out1_reg[12] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in31[12]),
        .Q(Delay31_out1[12]),
        .R(reset));
  FDRE \Delay31_out1_reg[13] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in31[13]),
        .Q(Delay31_out1[13]),
        .R(reset));
  FDRE \Delay31_out1_reg[14] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in31[14]),
        .Q(Delay31_out1[14]),
        .R(reset));
  FDRE \Delay31_out1_reg[15] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in31[15]),
        .Q(Delay31_out1[15]),
        .R(reset));
  FDRE \Delay31_out1_reg[16] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in31[16]),
        .Q(Delay31_out1[16]),
        .R(reset));
  FDRE \Delay31_out1_reg[17] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in31[17]),
        .Q(Delay31_out1[17]),
        .R(reset));
  FDRE \Delay31_out1_reg[18] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in31[18]),
        .Q(Delay31_out1[18]),
        .R(reset));
  FDRE \Delay31_out1_reg[19] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in31[19]),
        .Q(Delay31_out1[19]),
        .R(reset));
  FDRE \Delay31_out1_reg[1] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in31[1]),
        .Q(Delay31_out1[1]),
        .R(reset));
  FDRE \Delay31_out1_reg[20] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in31[20]),
        .Q(Delay31_out1[20]),
        .R(reset));
  FDRE \Delay31_out1_reg[21] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in31[21]),
        .Q(Delay31_out1[21]),
        .R(reset));
  FDRE \Delay31_out1_reg[22] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in31[22]),
        .Q(Delay31_out1[22]),
        .R(reset));
  FDRE \Delay31_out1_reg[23] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in31[23]),
        .Q(Delay31_out1[23]),
        .R(reset));
  FDRE \Delay31_out1_reg[24] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in31[24]),
        .Q(Delay31_out1[24]),
        .R(reset));
  FDRE \Delay31_out1_reg[25] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in31[25]),
        .Q(Delay31_out1[25]),
        .R(reset));
  FDRE \Delay31_out1_reg[26] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in31[26]),
        .Q(Delay31_out1[26]),
        .R(reset));
  FDRE \Delay31_out1_reg[2] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in31[2]),
        .Q(Delay31_out1[2]),
        .R(reset));
  FDRE \Delay31_out1_reg[3] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in31[3]),
        .Q(Delay31_out1[3]),
        .R(reset));
  FDRE \Delay31_out1_reg[4] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in31[4]),
        .Q(Delay31_out1[4]),
        .R(reset));
  FDRE \Delay31_out1_reg[5] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in31[5]),
        .Q(Delay31_out1[5]),
        .R(reset));
  FDRE \Delay31_out1_reg[6] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in31[6]),
        .Q(Delay31_out1[6]),
        .R(reset));
  FDRE \Delay31_out1_reg[7] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in31[7]),
        .Q(Delay31_out1[7]),
        .R(reset));
  FDRE \Delay31_out1_reg[8] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in31[8]),
        .Q(Delay31_out1[8]),
        .R(reset));
  FDRE \Delay31_out1_reg[9] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in31[9]),
        .Q(Delay31_out1[9]),
        .R(reset));
  FDRE \Delay3_out1_reg[0] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in3[0]),
        .Q(Delay3_out1[0]),
        .R(reset));
  FDRE \Delay3_out1_reg[10] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in3[10]),
        .Q(Delay3_out1[10]),
        .R(reset));
  FDRE \Delay3_out1_reg[11] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in3[11]),
        .Q(Delay3_out1[11]),
        .R(reset));
  FDRE \Delay3_out1_reg[12] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in3[12]),
        .Q(Delay3_out1[12]),
        .R(reset));
  FDRE \Delay3_out1_reg[13] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in3[13]),
        .Q(Delay3_out1[13]),
        .R(reset));
  FDRE \Delay3_out1_reg[14] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in3[14]),
        .Q(Delay3_out1[14]),
        .R(reset));
  FDRE \Delay3_out1_reg[15] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in3[15]),
        .Q(Delay3_out1[15]),
        .R(reset));
  FDRE \Delay3_out1_reg[16] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in3[16]),
        .Q(Delay3_out1[16]),
        .R(reset));
  FDRE \Delay3_out1_reg[17] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in3[17]),
        .Q(Delay3_out1[17]),
        .R(reset));
  FDRE \Delay3_out1_reg[18] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in3[18]),
        .Q(Delay3_out1[18]),
        .R(reset));
  FDRE \Delay3_out1_reg[19] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in3[19]),
        .Q(Delay3_out1[19]),
        .R(reset));
  FDRE \Delay3_out1_reg[1] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in3[1]),
        .Q(Delay3_out1[1]),
        .R(reset));
  FDRE \Delay3_out1_reg[20] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in3[20]),
        .Q(Delay3_out1[20]),
        .R(reset));
  FDRE \Delay3_out1_reg[21] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in3[21]),
        .Q(Delay3_out1[21]),
        .R(reset));
  FDRE \Delay3_out1_reg[22] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in3[22]),
        .Q(Delay3_out1[22]),
        .R(reset));
  FDRE \Delay3_out1_reg[23] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in3[23]),
        .Q(Delay3_out1[23]),
        .R(reset));
  FDRE \Delay3_out1_reg[24] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in3[24]),
        .Q(Delay3_out1[24]),
        .R(reset));
  FDRE \Delay3_out1_reg[25] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in3[25]),
        .Q(Delay3_out1[25]),
        .R(reset));
  FDRE \Delay3_out1_reg[26] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in3[26]),
        .Q(Delay3_out1[26]),
        .R(reset));
  FDRE \Delay3_out1_reg[2] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in3[2]),
        .Q(Delay3_out1[2]),
        .R(reset));
  FDRE \Delay3_out1_reg[3] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in3[3]),
        .Q(Delay3_out1[3]),
        .R(reset));
  FDRE \Delay3_out1_reg[4] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in3[4]),
        .Q(Delay3_out1[4]),
        .R(reset));
  FDRE \Delay3_out1_reg[5] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in3[5]),
        .Q(Delay3_out1[5]),
        .R(reset));
  FDRE \Delay3_out1_reg[6] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in3[6]),
        .Q(Delay3_out1[6]),
        .R(reset));
  FDRE \Delay3_out1_reg[7] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in3[7]),
        .Q(Delay3_out1[7]),
        .R(reset));
  FDRE \Delay3_out1_reg[8] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in3[8]),
        .Q(Delay3_out1[8]),
        .R(reset));
  FDRE \Delay3_out1_reg[9] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in3[9]),
        .Q(Delay3_out1[9]),
        .R(reset));
  FDRE \Delay4_out1_reg[0] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in4[0]),
        .Q(Delay4_out1[0]),
        .R(reset));
  FDRE \Delay4_out1_reg[10] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in4[10]),
        .Q(Delay4_out1[10]),
        .R(reset));
  FDRE \Delay4_out1_reg[11] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in4[11]),
        .Q(Delay4_out1[11]),
        .R(reset));
  FDRE \Delay4_out1_reg[12] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in4[12]),
        .Q(Delay4_out1[12]),
        .R(reset));
  FDRE \Delay4_out1_reg[13] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in4[13]),
        .Q(Delay4_out1[13]),
        .R(reset));
  FDRE \Delay4_out1_reg[14] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in4[14]),
        .Q(Delay4_out1[14]),
        .R(reset));
  FDRE \Delay4_out1_reg[15] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in4[15]),
        .Q(Delay4_out1[15]),
        .R(reset));
  FDRE \Delay4_out1_reg[16] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in4[16]),
        .Q(Delay4_out1[16]),
        .R(reset));
  FDRE \Delay4_out1_reg[17] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in4[17]),
        .Q(Delay4_out1[17]),
        .R(reset));
  FDRE \Delay4_out1_reg[18] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in4[18]),
        .Q(Delay4_out1[18]),
        .R(reset));
  FDRE \Delay4_out1_reg[19] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in4[19]),
        .Q(Delay4_out1[19]),
        .R(reset));
  FDRE \Delay4_out1_reg[1] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in4[1]),
        .Q(Delay4_out1[1]),
        .R(reset));
  FDRE \Delay4_out1_reg[20] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in4[20]),
        .Q(Delay4_out1[20]),
        .R(reset));
  FDRE \Delay4_out1_reg[21] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in4[21]),
        .Q(Delay4_out1[21]),
        .R(reset));
  FDRE \Delay4_out1_reg[22] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in4[22]),
        .Q(Delay4_out1[22]),
        .R(reset));
  FDRE \Delay4_out1_reg[23] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in4[23]),
        .Q(Delay4_out1[23]),
        .R(reset));
  FDRE \Delay4_out1_reg[24] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in4[24]),
        .Q(Delay4_out1[24]),
        .R(reset));
  FDRE \Delay4_out1_reg[25] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in4[25]),
        .Q(Delay4_out1[25]),
        .R(reset));
  FDRE \Delay4_out1_reg[26] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in4[26]),
        .Q(Delay4_out1[26]),
        .R(reset));
  FDRE \Delay4_out1_reg[2] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in4[2]),
        .Q(Delay4_out1[2]),
        .R(reset));
  FDRE \Delay4_out1_reg[3] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in4[3]),
        .Q(Delay4_out1[3]),
        .R(reset));
  FDRE \Delay4_out1_reg[4] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in4[4]),
        .Q(Delay4_out1[4]),
        .R(reset));
  FDRE \Delay4_out1_reg[5] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in4[5]),
        .Q(Delay4_out1[5]),
        .R(reset));
  FDRE \Delay4_out1_reg[6] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in4[6]),
        .Q(Delay4_out1[6]),
        .R(reset));
  FDRE \Delay4_out1_reg[7] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in4[7]),
        .Q(Delay4_out1[7]),
        .R(reset));
  FDRE \Delay4_out1_reg[8] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in4[8]),
        .Q(Delay4_out1[8]),
        .R(reset));
  FDRE \Delay4_out1_reg[9] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in4[9]),
        .Q(Delay4_out1[9]),
        .R(reset));
  FDRE \Delay5_out1_reg[0] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in5[0]),
        .Q(Delay5_out1[0]),
        .R(reset));
  FDRE \Delay5_out1_reg[10] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in5[10]),
        .Q(Delay5_out1[10]),
        .R(reset));
  FDRE \Delay5_out1_reg[11] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in5[11]),
        .Q(Delay5_out1[11]),
        .R(reset));
  FDRE \Delay5_out1_reg[12] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in5[12]),
        .Q(Delay5_out1[12]),
        .R(reset));
  FDRE \Delay5_out1_reg[13] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in5[13]),
        .Q(Delay5_out1[13]),
        .R(reset));
  FDRE \Delay5_out1_reg[14] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in5[14]),
        .Q(Delay5_out1[14]),
        .R(reset));
  FDRE \Delay5_out1_reg[15] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in5[15]),
        .Q(Delay5_out1[15]),
        .R(reset));
  FDRE \Delay5_out1_reg[16] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in5[16]),
        .Q(Delay5_out1[16]),
        .R(reset));
  FDRE \Delay5_out1_reg[17] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in5[17]),
        .Q(Delay5_out1[17]),
        .R(reset));
  FDRE \Delay5_out1_reg[18] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in5[18]),
        .Q(Delay5_out1[18]),
        .R(reset));
  FDRE \Delay5_out1_reg[19] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in5[19]),
        .Q(Delay5_out1[19]),
        .R(reset));
  FDRE \Delay5_out1_reg[1] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in5[1]),
        .Q(Delay5_out1[1]),
        .R(reset));
  FDRE \Delay5_out1_reg[20] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in5[20]),
        .Q(Delay5_out1[20]),
        .R(reset));
  FDRE \Delay5_out1_reg[21] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in5[21]),
        .Q(Delay5_out1[21]),
        .R(reset));
  FDRE \Delay5_out1_reg[22] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in5[22]),
        .Q(Delay5_out1[22]),
        .R(reset));
  FDRE \Delay5_out1_reg[23] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in5[23]),
        .Q(Delay5_out1[23]),
        .R(reset));
  FDRE \Delay5_out1_reg[24] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in5[24]),
        .Q(Delay5_out1[24]),
        .R(reset));
  FDRE \Delay5_out1_reg[25] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in5[25]),
        .Q(Delay5_out1[25]),
        .R(reset));
  FDRE \Delay5_out1_reg[26] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in5[26]),
        .Q(Delay5_out1[26]),
        .R(reset));
  FDRE \Delay5_out1_reg[2] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in5[2]),
        .Q(Delay5_out1[2]),
        .R(reset));
  FDRE \Delay5_out1_reg[3] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in5[3]),
        .Q(Delay5_out1[3]),
        .R(reset));
  FDRE \Delay5_out1_reg[4] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in5[4]),
        .Q(Delay5_out1[4]),
        .R(reset));
  FDRE \Delay5_out1_reg[5] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in5[5]),
        .Q(Delay5_out1[5]),
        .R(reset));
  FDRE \Delay5_out1_reg[6] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in5[6]),
        .Q(Delay5_out1[6]),
        .R(reset));
  FDRE \Delay5_out1_reg[7] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in5[7]),
        .Q(Delay5_out1[7]),
        .R(reset));
  FDRE \Delay5_out1_reg[8] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in5[8]),
        .Q(Delay5_out1[8]),
        .R(reset));
  FDRE \Delay5_out1_reg[9] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in5[9]),
        .Q(Delay5_out1[9]),
        .R(reset));
  FDRE \Delay6_out1_reg[0] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in6[0]),
        .Q(Delay6_out1[0]),
        .R(reset));
  FDRE \Delay6_out1_reg[10] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in6[10]),
        .Q(Delay6_out1[10]),
        .R(reset));
  FDRE \Delay6_out1_reg[11] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in6[11]),
        .Q(Delay6_out1[11]),
        .R(reset));
  FDRE \Delay6_out1_reg[12] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in6[12]),
        .Q(Delay6_out1[12]),
        .R(reset));
  FDRE \Delay6_out1_reg[13] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in6[13]),
        .Q(Delay6_out1[13]),
        .R(reset));
  FDRE \Delay6_out1_reg[14] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in6[14]),
        .Q(Delay6_out1[14]),
        .R(reset));
  FDRE \Delay6_out1_reg[15] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in6[15]),
        .Q(Delay6_out1[15]),
        .R(reset));
  FDRE \Delay6_out1_reg[16] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in6[16]),
        .Q(Delay6_out1[16]),
        .R(reset));
  FDRE \Delay6_out1_reg[17] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in6[17]),
        .Q(Delay6_out1[17]),
        .R(reset));
  FDRE \Delay6_out1_reg[18] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in6[18]),
        .Q(Delay6_out1[18]),
        .R(reset));
  FDRE \Delay6_out1_reg[19] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in6[19]),
        .Q(Delay6_out1[19]),
        .R(reset));
  FDRE \Delay6_out1_reg[1] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in6[1]),
        .Q(Delay6_out1[1]),
        .R(reset));
  FDRE \Delay6_out1_reg[20] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in6[20]),
        .Q(Delay6_out1[20]),
        .R(reset));
  FDRE \Delay6_out1_reg[21] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in6[21]),
        .Q(Delay6_out1[21]),
        .R(reset));
  FDRE \Delay6_out1_reg[22] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in6[22]),
        .Q(Delay6_out1[22]),
        .R(reset));
  FDRE \Delay6_out1_reg[23] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in6[23]),
        .Q(Delay6_out1[23]),
        .R(reset));
  FDRE \Delay6_out1_reg[24] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in6[24]),
        .Q(Delay6_out1[24]),
        .R(reset));
  FDRE \Delay6_out1_reg[25] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in6[25]),
        .Q(Delay6_out1[25]),
        .R(reset));
  FDRE \Delay6_out1_reg[26] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in6[26]),
        .Q(Delay6_out1[26]),
        .R(reset));
  FDRE \Delay6_out1_reg[2] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in6[2]),
        .Q(Delay6_out1[2]),
        .R(reset));
  FDRE \Delay6_out1_reg[3] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in6[3]),
        .Q(Delay6_out1[3]),
        .R(reset));
  FDRE \Delay6_out1_reg[4] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in6[4]),
        .Q(Delay6_out1[4]),
        .R(reset));
  FDRE \Delay6_out1_reg[5] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in6[5]),
        .Q(Delay6_out1[5]),
        .R(reset));
  FDRE \Delay6_out1_reg[6] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in6[6]),
        .Q(Delay6_out1[6]),
        .R(reset));
  FDRE \Delay6_out1_reg[7] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in6[7]),
        .Q(Delay6_out1[7]),
        .R(reset));
  FDRE \Delay6_out1_reg[8] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in6[8]),
        .Q(Delay6_out1[8]),
        .R(reset));
  FDRE \Delay6_out1_reg[9] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in6[9]),
        .Q(Delay6_out1[9]),
        .R(reset));
  FDRE \Delay7_out1_reg[0] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in7[0]),
        .Q(Delay7_out1[0]),
        .R(reset));
  FDRE \Delay7_out1_reg[10] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in7[10]),
        .Q(Delay7_out1[10]),
        .R(reset));
  FDRE \Delay7_out1_reg[11] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in7[11]),
        .Q(Delay7_out1[11]),
        .R(reset));
  FDRE \Delay7_out1_reg[12] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in7[12]),
        .Q(Delay7_out1[12]),
        .R(reset));
  FDRE \Delay7_out1_reg[13] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in7[13]),
        .Q(Delay7_out1[13]),
        .R(reset));
  FDRE \Delay7_out1_reg[14] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in7[14]),
        .Q(Delay7_out1[14]),
        .R(reset));
  FDRE \Delay7_out1_reg[15] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in7[15]),
        .Q(Delay7_out1[15]),
        .R(reset));
  FDRE \Delay7_out1_reg[16] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in7[16]),
        .Q(Delay7_out1[16]),
        .R(reset));
  FDRE \Delay7_out1_reg[17] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in7[17]),
        .Q(Delay7_out1[17]),
        .R(reset));
  FDRE \Delay7_out1_reg[18] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in7[18]),
        .Q(Delay7_out1[18]),
        .R(reset));
  FDRE \Delay7_out1_reg[19] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in7[19]),
        .Q(Delay7_out1[19]),
        .R(reset));
  FDRE \Delay7_out1_reg[1] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in7[1]),
        .Q(Delay7_out1[1]),
        .R(reset));
  FDRE \Delay7_out1_reg[20] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in7[20]),
        .Q(Delay7_out1[20]),
        .R(reset));
  FDRE \Delay7_out1_reg[21] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in7[21]),
        .Q(Delay7_out1[21]),
        .R(reset));
  FDRE \Delay7_out1_reg[22] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in7[22]),
        .Q(Delay7_out1[22]),
        .R(reset));
  FDRE \Delay7_out1_reg[23] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in7[23]),
        .Q(Delay7_out1[23]),
        .R(reset));
  FDRE \Delay7_out1_reg[24] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in7[24]),
        .Q(Delay7_out1[24]),
        .R(reset));
  FDRE \Delay7_out1_reg[25] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in7[25]),
        .Q(Delay7_out1[25]),
        .R(reset));
  FDRE \Delay7_out1_reg[26] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in7[26]),
        .Q(Delay7_out1[26]),
        .R(reset));
  FDRE \Delay7_out1_reg[2] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in7[2]),
        .Q(Delay7_out1[2]),
        .R(reset));
  FDRE \Delay7_out1_reg[3] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in7[3]),
        .Q(Delay7_out1[3]),
        .R(reset));
  FDRE \Delay7_out1_reg[4] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in7[4]),
        .Q(Delay7_out1[4]),
        .R(reset));
  FDRE \Delay7_out1_reg[5] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in7[5]),
        .Q(Delay7_out1[5]),
        .R(reset));
  FDRE \Delay7_out1_reg[6] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in7[6]),
        .Q(Delay7_out1[6]),
        .R(reset));
  FDRE \Delay7_out1_reg[7] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in7[7]),
        .Q(Delay7_out1[7]),
        .R(reset));
  FDRE \Delay7_out1_reg[8] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in7[8]),
        .Q(Delay7_out1[8]),
        .R(reset));
  FDRE \Delay7_out1_reg[9] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in7[9]),
        .Q(Delay7_out1[9]),
        .R(reset));
  FDRE \Delay8_out1_reg[0] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in8[0]),
        .Q(Delay8_out1[0]),
        .R(reset));
  FDRE \Delay8_out1_reg[10] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in8[10]),
        .Q(Delay8_out1[10]),
        .R(reset));
  FDRE \Delay8_out1_reg[11] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in8[11]),
        .Q(Delay8_out1[11]),
        .R(reset));
  FDRE \Delay8_out1_reg[12] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in8[12]),
        .Q(Delay8_out1[12]),
        .R(reset));
  FDRE \Delay8_out1_reg[13] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in8[13]),
        .Q(Delay8_out1[13]),
        .R(reset));
  FDRE \Delay8_out1_reg[14] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in8[14]),
        .Q(Delay8_out1[14]),
        .R(reset));
  FDRE \Delay8_out1_reg[15] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in8[15]),
        .Q(Delay8_out1[15]),
        .R(reset));
  FDRE \Delay8_out1_reg[16] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in8[16]),
        .Q(Delay8_out1[16]),
        .R(reset));
  FDRE \Delay8_out1_reg[17] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in8[17]),
        .Q(Delay8_out1[17]),
        .R(reset));
  FDRE \Delay8_out1_reg[18] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in8[18]),
        .Q(Delay8_out1[18]),
        .R(reset));
  FDRE \Delay8_out1_reg[19] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in8[19]),
        .Q(Delay8_out1[19]),
        .R(reset));
  FDRE \Delay8_out1_reg[1] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in8[1]),
        .Q(Delay8_out1[1]),
        .R(reset));
  FDRE \Delay8_out1_reg[20] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in8[20]),
        .Q(Delay8_out1[20]),
        .R(reset));
  FDRE \Delay8_out1_reg[21] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in8[21]),
        .Q(Delay8_out1[21]),
        .R(reset));
  FDRE \Delay8_out1_reg[22] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in8[22]),
        .Q(Delay8_out1[22]),
        .R(reset));
  FDRE \Delay8_out1_reg[23] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in8[23]),
        .Q(Delay8_out1[23]),
        .R(reset));
  FDRE \Delay8_out1_reg[24] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in8[24]),
        .Q(Delay8_out1[24]),
        .R(reset));
  FDRE \Delay8_out1_reg[25] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in8[25]),
        .Q(Delay8_out1[25]),
        .R(reset));
  FDRE \Delay8_out1_reg[26] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in8[26]),
        .Q(Delay8_out1[26]),
        .R(reset));
  FDRE \Delay8_out1_reg[2] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in8[2]),
        .Q(Delay8_out1[2]),
        .R(reset));
  FDRE \Delay8_out1_reg[3] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in8[3]),
        .Q(Delay8_out1[3]),
        .R(reset));
  FDRE \Delay8_out1_reg[4] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in8[4]),
        .Q(Delay8_out1[4]),
        .R(reset));
  FDRE \Delay8_out1_reg[5] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in8[5]),
        .Q(Delay8_out1[5]),
        .R(reset));
  FDRE \Delay8_out1_reg[6] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in8[6]),
        .Q(Delay8_out1[6]),
        .R(reset));
  FDRE \Delay8_out1_reg[7] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in8[7]),
        .Q(Delay8_out1[7]),
        .R(reset));
  FDRE \Delay8_out1_reg[8] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in8[8]),
        .Q(Delay8_out1[8]),
        .R(reset));
  FDRE \Delay8_out1_reg[9] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in8[9]),
        .Q(Delay8_out1[9]),
        .R(reset));
  FDRE \Delay9_out1_reg[0] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in9[0]),
        .Q(Delay9_out1[0]),
        .R(reset));
  FDRE \Delay9_out1_reg[10] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in9[10]),
        .Q(Delay9_out1[10]),
        .R(reset));
  FDRE \Delay9_out1_reg[11] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in9[11]),
        .Q(Delay9_out1[11]),
        .R(reset));
  FDRE \Delay9_out1_reg[12] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in9[12]),
        .Q(Delay9_out1[12]),
        .R(reset));
  FDRE \Delay9_out1_reg[13] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in9[13]),
        .Q(Delay9_out1[13]),
        .R(reset));
  FDRE \Delay9_out1_reg[14] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in9[14]),
        .Q(Delay9_out1[14]),
        .R(reset));
  FDRE \Delay9_out1_reg[15] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in9[15]),
        .Q(Delay9_out1[15]),
        .R(reset));
  FDRE \Delay9_out1_reg[16] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in9[16]),
        .Q(Delay9_out1[16]),
        .R(reset));
  FDRE \Delay9_out1_reg[17] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in9[17]),
        .Q(Delay9_out1[17]),
        .R(reset));
  FDRE \Delay9_out1_reg[18] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in9[18]),
        .Q(Delay9_out1[18]),
        .R(reset));
  FDRE \Delay9_out1_reg[19] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in9[19]),
        .Q(Delay9_out1[19]),
        .R(reset));
  FDRE \Delay9_out1_reg[1] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in9[1]),
        .Q(Delay9_out1[1]),
        .R(reset));
  FDRE \Delay9_out1_reg[20] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in9[20]),
        .Q(Delay9_out1[20]),
        .R(reset));
  FDRE \Delay9_out1_reg[21] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in9[21]),
        .Q(Delay9_out1[21]),
        .R(reset));
  FDRE \Delay9_out1_reg[22] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in9[22]),
        .Q(Delay9_out1[22]),
        .R(reset));
  FDRE \Delay9_out1_reg[23] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in9[23]),
        .Q(Delay9_out1[23]),
        .R(reset));
  FDRE \Delay9_out1_reg[24] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in9[24]),
        .Q(Delay9_out1[24]),
        .R(reset));
  FDRE \Delay9_out1_reg[25] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in9[25]),
        .Q(Delay9_out1[25]),
        .R(reset));
  FDRE \Delay9_out1_reg[26] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in9[26]),
        .Q(Delay9_out1[26]),
        .R(reset));
  FDRE \Delay9_out1_reg[2] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in9[2]),
        .Q(Delay9_out1[2]),
        .R(reset));
  FDRE \Delay9_out1_reg[3] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in9[3]),
        .Q(Delay9_out1[3]),
        .R(reset));
  FDRE \Delay9_out1_reg[4] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in9[4]),
        .Q(Delay9_out1[4]),
        .R(reset));
  FDRE \Delay9_out1_reg[5] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in9[5]),
        .Q(Delay9_out1[5]),
        .R(reset));
  FDRE \Delay9_out1_reg[6] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in9[6]),
        .Q(Delay9_out1[6]),
        .R(reset));
  FDRE \Delay9_out1_reg[7] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in9[7]),
        .Q(Delay9_out1[7]),
        .R(reset));
  FDRE \Delay9_out1_reg[8] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in9[8]),
        .Q(Delay9_out1[8]),
        .R(reset));
  FDRE \Delay9_out1_reg[9] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in9[9]),
        .Q(Delay9_out1[9]),
        .R(reset));
  FDRE \Delay_out1_reg[0] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in0[0]),
        .Q(Delay_out1[0]),
        .R(reset));
  FDRE \Delay_out1_reg[10] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in0[10]),
        .Q(Delay_out1[10]),
        .R(reset));
  FDRE \Delay_out1_reg[11] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in0[11]),
        .Q(Delay_out1[11]),
        .R(reset));
  FDRE \Delay_out1_reg[12] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in0[12]),
        .Q(Delay_out1[12]),
        .R(reset));
  FDRE \Delay_out1_reg[13] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in0[13]),
        .Q(Delay_out1[13]),
        .R(reset));
  FDRE \Delay_out1_reg[14] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in0[14]),
        .Q(Delay_out1[14]),
        .R(reset));
  FDRE \Delay_out1_reg[15] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in0[15]),
        .Q(Delay_out1[15]),
        .R(reset));
  FDRE \Delay_out1_reg[16] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in0[16]),
        .Q(Delay_out1[16]),
        .R(reset));
  FDRE \Delay_out1_reg[17] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in0[17]),
        .Q(Delay_out1[17]),
        .R(reset));
  FDRE \Delay_out1_reg[18] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in0[18]),
        .Q(Delay_out1[18]),
        .R(reset));
  FDRE \Delay_out1_reg[19] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in0[19]),
        .Q(Delay_out1[19]),
        .R(reset));
  FDRE \Delay_out1_reg[1] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in0[1]),
        .Q(Delay_out1[1]),
        .R(reset));
  FDRE \Delay_out1_reg[20] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in0[20]),
        .Q(Delay_out1[20]),
        .R(reset));
  FDRE \Delay_out1_reg[21] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in0[21]),
        .Q(Delay_out1[21]),
        .R(reset));
  FDRE \Delay_out1_reg[22] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in0[22]),
        .Q(Delay_out1[22]),
        .R(reset));
  FDRE \Delay_out1_reg[23] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in0[23]),
        .Q(Delay_out1[23]),
        .R(reset));
  FDRE \Delay_out1_reg[24] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in0[24]),
        .Q(Delay_out1[24]),
        .R(reset));
  FDRE \Delay_out1_reg[25] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in0[25]),
        .Q(Delay_out1[25]),
        .R(reset));
  FDRE \Delay_out1_reg[26] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in0[26]),
        .Q(Delay_out1[26]),
        .R(reset));
  FDRE \Delay_out1_reg[2] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in0[2]),
        .Q(Delay_out1[2]),
        .R(reset));
  FDRE \Delay_out1_reg[3] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in0[3]),
        .Q(Delay_out1[3]),
        .R(reset));
  FDRE \Delay_out1_reg[4] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in0[4]),
        .Q(Delay_out1[4]),
        .R(reset));
  FDRE \Delay_out1_reg[5] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in0[5]),
        .Q(Delay_out1[5]),
        .R(reset));
  FDRE \Delay_out1_reg[6] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in0[6]),
        .Q(Delay_out1[6]),
        .R(reset));
  FDRE \Delay_out1_reg[7] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in0[7]),
        .Q(Delay_out1[7]),
        .R(reset));
  FDRE \Delay_out1_reg[8] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in0[8]),
        .Q(Delay_out1[8]),
        .R(reset));
  FDRE \Delay_out1_reg[9] 
       (.C(IPCORE_CLK),
        .CE(adc_trigger),
        .D(in0[9]),
        .Q(Delay_out1[9]),
        .R(reset));
  (* KEEP_HIERARCHY = "yes" *) 
  (* METHODOLOGY_DRC_VIOS = "{SYNTH-11 {cell *THIS*}}" *) 
  DSP48E2 #(
    .ACASCREG(0),
    .ADREG(1),
    .ALUMODEREG(0),
    .AMULTSEL("A"),
    .AREG(0),
    .AUTORESET_PATDET("NO_RESET"),
    .AUTORESET_PRIORITY("RESET"),
    .A_INPUT("DIRECT"),
    .BCASCREG(1),
    .BMULTSEL("B"),
    .BREG(1),
    .B_INPUT("DIRECT"),
    .CARRYINREG(0),
    .CARRYINSELREG(0),
    .CREG(0),
    .DREG(1),
    .INMODEREG(0),
    .MASK(48'h3FFFFFFFFFFF),
    .MREG(0),
    .OPMODEREG(0),
    .PATTERN(48'h000000000000),
    .PREADDINSEL("A"),
    .PREG(0),
    .RND(48'h000000000000),
    .SEL_MASK("MASK"),
    .SEL_PATTERN("PATTERN"),
    .USE_MULT("MULTIPLY"),
    .USE_PATTERN_DETECT("NO_PATDET"),
    .USE_SIMD("ONE48"),
    .USE_WIDEXOR("FALSE"),
    .XORSIMD("XOR24_48_96")) 
    p_1_out
       (.A({A[26],A[26],A[26],A,p_1_out_i_28_n_0}),
        .ACIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .ACOUT(NLW_p_1_out_ACOUT_UNCONNECTED[29:0]),
        .ALUMODE({1'b0,1'b0,1'b0,1'b0}),
        .B({1'b0,AXI_pu_conv_in31}),
        .BCIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .BCOUT(NLW_p_1_out_BCOUT_UNCONNECTED[17:0]),
        .C({A[26],A[26],A[26],A[26],A[26],A[26],A[26],A[26],A[26],A[26],A[26],A[26],A[26],A[26],A[26],A[26],A[26],A[26],A[26],A[26],A[26],A[26],A}),
        .CARRYCASCIN(1'b0),
        .CARRYCASCOUT(NLW_p_1_out_CARRYCASCOUT_UNCONNECTED),
        .CARRYIN(1'b0),
        .CARRYINSEL({1'b0,1'b0,1'b0}),
        .CARRYOUT(NLW_p_1_out_CARRYOUT_UNCONNECTED[3:0]),
        .CEA1(1'b0),
        .CEA2(1'b0),
        .CEAD(1'b0),
        .CEALUMODE(1'b0),
        .CEB1(1'b0),
        .CEB2(DSP_ALU_INST),
        .CEC(1'b0),
        .CECARRYIN(1'b0),
        .CECTRL(1'b0),
        .CED(1'b0),
        .CEINMODE(1'b0),
        .CEM(1'b0),
        .CEP(1'b0),
        .CLK(AXI4_Lite_ACLK),
        .D({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .INMODE({1'b0,1'b0,1'b0,1'b0,1'b0}),
        .MULTSIGNIN(1'b0),
        .MULTSIGNOUT(NLW_p_1_out_MULTSIGNOUT_UNCONNECTED),
        .OPMODE({1'b0,1'b0,1'b0,OPMODE,OPMODE,1'b0,1'b1,1'b0,1'b1}),
        .OVERFLOW(NLW_p_1_out_OVERFLOW_UNCONNECTED),
        .P({NLW_p_1_out_P_UNCONNECTED[47:45],p_1_out_n_61,p_1_out_n_62,p_1_out_n_63,p_1_out_n_64,p_1_out_n_65,p_1_out_n_66,p_1_out_n_67,p_1_out_n_68,p_1_out_n_69,p_1_out_n_70,out0,p_1_out_n_89,p_1_out_n_90,p_1_out_n_91,p_1_out_n_92,p_1_out_n_93,p_1_out_n_94,p_1_out_n_95,p_1_out_n_96,p_1_out_n_97,p_1_out_n_98,p_1_out_n_99,p_1_out_n_100,p_1_out_n_101,p_1_out_n_102,p_1_out_n_103,p_1_out_n_104,p_1_out_n_105}),
        .PATTERNBDETECT(NLW_p_1_out_PATTERNBDETECT_UNCONNECTED),
        .PATTERNDETECT(NLW_p_1_out_PATTERNDETECT_UNCONNECTED),
        .PCIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .PCOUT(NLW_p_1_out_PCOUT_UNCONNECTED[47:0]),
        .RSTA(1'b0),
        .RSTALLCARRYIN(1'b0),
        .RSTALUMODE(1'b0),
        .RSTB(reset),
        .RSTC(1'b0),
        .RSTCTRL(1'b0),
        .RSTD(1'b0),
        .RSTINMODE(1'b0),
        .RSTM(1'b0),
        .RSTP(1'b0),
        .UNDERFLOW(NLW_p_1_out_UNDERFLOW_UNCONNECTED),
        .XOROUT(NLW_p_1_out_XOROUT_UNCONNECTED[7:0]));
  (* KEEP_HIERARCHY = "yes" *) 
  (* METHODOLOGY_DRC_VIOS = "{SYNTH-11 {cell *THIS*}}" *) 
  DSP48E2 #(
    .ACASCREG(0),
    .ADREG(1),
    .ALUMODEREG(0),
    .AMULTSEL("A"),
    .AREG(0),
    .AUTORESET_PATDET("NO_RESET"),
    .AUTORESET_PRIORITY("RESET"),
    .A_INPUT("DIRECT"),
    .BCASCREG(1),
    .BMULTSEL("B"),
    .BREG(1),
    .B_INPUT("DIRECT"),
    .CARRYINREG(0),
    .CARRYINSELREG(0),
    .CREG(0),
    .DREG(1),
    .INMODEREG(0),
    .MASK(48'h3FFFFFFFFFFF),
    .MREG(0),
    .OPMODEREG(0),
    .PATTERN(48'h000000000000),
    .PREADDINSEL("A"),
    .PREG(0),
    .RND(48'h000000000000),
    .SEL_MASK("MASK"),
    .SEL_PATTERN("PATTERN"),
    .USE_MULT("MULTIPLY"),
    .USE_PATTERN_DETECT("NO_PATDET"),
    .USE_SIMD("ONE48"),
    .USE_WIDEXOR("FALSE"),
    .XORSIMD("XOR24_48_96")) 
    p_1_out__0
       (.A({A__0[26],A__0[26],A__0[26],A__0,p_1_out__0_i_28_n_0}),
        .ACIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .ACOUT(NLW_p_1_out__0_ACOUT_UNCONNECTED[29:0]),
        .ALUMODE({1'b0,1'b0,1'b0,1'b0}),
        .B({1'b0,AXI_pu_conv_in31}),
        .BCIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .BCOUT(NLW_p_1_out__0_BCOUT_UNCONNECTED[17:0]),
        .C({A__0[26],A__0[26],A__0[26],A__0[26],A__0[26],A__0[26],A__0[26],A__0[26],A__0[26],A__0[26],A__0[26],A__0[26],A__0[26],A__0[26],A__0[26],A__0[26],A__0[26],A__0[26],A__0[26],A__0[26],A__0[26],A__0[26],A__0}),
        .CARRYCASCIN(1'b0),
        .CARRYCASCOUT(NLW_p_1_out__0_CARRYCASCOUT_UNCONNECTED),
        .CARRYIN(1'b0),
        .CARRYINSEL({1'b0,1'b0,1'b0}),
        .CARRYOUT(NLW_p_1_out__0_CARRYOUT_UNCONNECTED[3:0]),
        .CEA1(1'b0),
        .CEA2(1'b0),
        .CEAD(1'b0),
        .CEALUMODE(1'b0),
        .CEB1(1'b0),
        .CEB2(DSP_ALU_INST_0),
        .CEC(1'b0),
        .CECARRYIN(1'b0),
        .CECTRL(1'b0),
        .CED(1'b0),
        .CEINMODE(1'b0),
        .CEM(1'b0),
        .CEP(1'b0),
        .CLK(AXI4_Lite_ACLK),
        .D({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .INMODE({1'b0,1'b0,1'b0,1'b0,1'b0}),
        .MULTSIGNIN(1'b0),
        .MULTSIGNOUT(NLW_p_1_out__0_MULTSIGNOUT_UNCONNECTED),
        .OPMODE({1'b0,1'b0,1'b0,\out1[17] ,\out1[17] ,1'b0,1'b1,1'b0,1'b1}),
        .OVERFLOW(NLW_p_1_out__0_OVERFLOW_UNCONNECTED),
        .P({NLW_p_1_out__0_P_UNCONNECTED[47:45],p_1_out__0_n_61,p_1_out__0_n_62,p_1_out__0_n_63,p_1_out__0_n_64,p_1_out__0_n_65,p_1_out__0_n_66,p_1_out__0_n_67,p_1_out__0_n_68,p_1_out__0_n_69,p_1_out__0_n_70,out1,p_1_out__0_n_89,p_1_out__0_n_90,p_1_out__0_n_91,p_1_out__0_n_92,p_1_out__0_n_93,p_1_out__0_n_94,p_1_out__0_n_95,p_1_out__0_n_96,p_1_out__0_n_97,p_1_out__0_n_98,p_1_out__0_n_99,p_1_out__0_n_100,p_1_out__0_n_101,p_1_out__0_n_102,p_1_out__0_n_103,p_1_out__0_n_104,p_1_out__0_n_105}),
        .PATTERNBDETECT(NLW_p_1_out__0_PATTERNBDETECT_UNCONNECTED),
        .PATTERNDETECT(NLW_p_1_out__0_PATTERNDETECT_UNCONNECTED),
        .PCIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .PCOUT(NLW_p_1_out__0_PCOUT_UNCONNECTED[47:0]),
        .RSTA(1'b0),
        .RSTALLCARRYIN(1'b0),
        .RSTALUMODE(1'b0),
        .RSTB(reset),
        .RSTC(1'b0),
        .RSTCTRL(1'b0),
        .RSTD(1'b0),
        .RSTINMODE(1'b0),
        .RSTM(1'b0),
        .RSTP(1'b0),
        .UNDERFLOW(NLW_p_1_out__0_UNDERFLOW_UNCONNECTED),
        .XOROUT(NLW_p_1_out__0_XOROUT_UNCONNECTED[7:0]));
  (* SOFT_HLUTNM = "soft_lutpair45" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__0_i_10
       (.I0(in1[18]),
        .I1(Delay1_out1[18]),
        .I2(adc_trigger),
        .O(A__0[18]));
  (* SOFT_HLUTNM = "soft_lutpair45" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__0_i_11
       (.I0(in1[17]),
        .I1(Delay1_out1[17]),
        .I2(adc_trigger),
        .O(A__0[17]));
  (* SOFT_HLUTNM = "soft_lutpair44" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__0_i_12
       (.I0(in1[16]),
        .I1(Delay1_out1[16]),
        .I2(adc_trigger),
        .O(A__0[16]));
  (* SOFT_HLUTNM = "soft_lutpair44" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__0_i_13
       (.I0(in1[15]),
        .I1(Delay1_out1[15]),
        .I2(adc_trigger),
        .O(A__0[15]));
  (* SOFT_HLUTNM = "soft_lutpair43" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__0_i_14
       (.I0(in1[14]),
        .I1(Delay1_out1[14]),
        .I2(adc_trigger),
        .O(A__0[14]));
  (* SOFT_HLUTNM = "soft_lutpair43" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__0_i_15
       (.I0(in1[13]),
        .I1(Delay1_out1[13]),
        .I2(adc_trigger),
        .O(A__0[13]));
  (* SOFT_HLUTNM = "soft_lutpair42" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__0_i_16
       (.I0(in1[12]),
        .I1(Delay1_out1[12]),
        .I2(adc_trigger),
        .O(A__0[12]));
  (* SOFT_HLUTNM = "soft_lutpair42" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__0_i_17
       (.I0(in1[11]),
        .I1(Delay1_out1[11]),
        .I2(adc_trigger),
        .O(A__0[11]));
  (* SOFT_HLUTNM = "soft_lutpair41" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__0_i_18
       (.I0(in1[10]),
        .I1(Delay1_out1[10]),
        .I2(adc_trigger),
        .O(A__0[10]));
  (* SOFT_HLUTNM = "soft_lutpair41" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__0_i_19
       (.I0(in1[9]),
        .I1(Delay1_out1[9]),
        .I2(adc_trigger),
        .O(A__0[9]));
  (* SOFT_HLUTNM = "soft_lutpair49" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__0_i_2
       (.I0(in1[26]),
        .I1(Delay1_out1[26]),
        .I2(adc_trigger),
        .O(A__0[26]));
  (* SOFT_HLUTNM = "soft_lutpair40" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__0_i_20
       (.I0(in1[8]),
        .I1(Delay1_out1[8]),
        .I2(adc_trigger),
        .O(A__0[8]));
  (* SOFT_HLUTNM = "soft_lutpair40" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__0_i_21
       (.I0(in1[7]),
        .I1(Delay1_out1[7]),
        .I2(adc_trigger),
        .O(A__0[7]));
  (* SOFT_HLUTNM = "soft_lutpair39" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__0_i_22
       (.I0(in1[6]),
        .I1(Delay1_out1[6]),
        .I2(adc_trigger),
        .O(A__0[6]));
  (* SOFT_HLUTNM = "soft_lutpair39" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__0_i_23
       (.I0(in1[5]),
        .I1(Delay1_out1[5]),
        .I2(adc_trigger),
        .O(A__0[5]));
  (* SOFT_HLUTNM = "soft_lutpair38" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__0_i_24
       (.I0(in1[4]),
        .I1(Delay1_out1[4]),
        .I2(adc_trigger),
        .O(A__0[4]));
  (* SOFT_HLUTNM = "soft_lutpair38" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__0_i_25
       (.I0(in1[3]),
        .I1(Delay1_out1[3]),
        .I2(adc_trigger),
        .O(A__0[3]));
  (* SOFT_HLUTNM = "soft_lutpair37" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__0_i_26
       (.I0(in1[2]),
        .I1(Delay1_out1[2]),
        .I2(adc_trigger),
        .O(A__0[2]));
  (* SOFT_HLUTNM = "soft_lutpair37" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__0_i_27
       (.I0(in1[1]),
        .I1(Delay1_out1[1]),
        .I2(adc_trigger),
        .O(A__0[1]));
  (* SOFT_HLUTNM = "soft_lutpair36" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__0_i_28
       (.I0(in1[0]),
        .I1(Delay1_out1[0]),
        .I2(adc_trigger),
        .O(p_1_out__0_i_28_n_0));
  (* SOFT_HLUTNM = "soft_lutpair49" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__0_i_3
       (.I0(in1[25]),
        .I1(Delay1_out1[25]),
        .I2(adc_trigger),
        .O(A__0[25]));
  (* SOFT_HLUTNM = "soft_lutpair48" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__0_i_4
       (.I0(in1[24]),
        .I1(Delay1_out1[24]),
        .I2(adc_trigger),
        .O(A__0[24]));
  (* SOFT_HLUTNM = "soft_lutpair48" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__0_i_5
       (.I0(in1[23]),
        .I1(Delay1_out1[23]),
        .I2(adc_trigger),
        .O(A__0[23]));
  (* SOFT_HLUTNM = "soft_lutpair47" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__0_i_6
       (.I0(in1[22]),
        .I1(Delay1_out1[22]),
        .I2(adc_trigger),
        .O(A__0[22]));
  (* SOFT_HLUTNM = "soft_lutpair47" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__0_i_7
       (.I0(in1[21]),
        .I1(Delay1_out1[21]),
        .I2(adc_trigger),
        .O(A__0[21]));
  (* SOFT_HLUTNM = "soft_lutpair46" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__0_i_8
       (.I0(in1[20]),
        .I1(Delay1_out1[20]),
        .I2(adc_trigger),
        .O(A__0[20]));
  (* SOFT_HLUTNM = "soft_lutpair46" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__0_i_9
       (.I0(in1[19]),
        .I1(Delay1_out1[19]),
        .I2(adc_trigger),
        .O(A__0[19]));
  (* KEEP_HIERARCHY = "yes" *) 
  (* METHODOLOGY_DRC_VIOS = "{SYNTH-11 {cell *THIS*}}" *) 
  DSP48E2 #(
    .ACASCREG(0),
    .ADREG(1),
    .ALUMODEREG(0),
    .AMULTSEL("A"),
    .AREG(0),
    .AUTORESET_PATDET("NO_RESET"),
    .AUTORESET_PRIORITY("RESET"),
    .A_INPUT("DIRECT"),
    .BCASCREG(1),
    .BMULTSEL("B"),
    .BREG(1),
    .B_INPUT("DIRECT"),
    .CARRYINREG(0),
    .CARRYINSELREG(0),
    .CREG(0),
    .DREG(1),
    .INMODEREG(0),
    .MASK(48'h3FFFFFFFFFFF),
    .MREG(0),
    .OPMODEREG(0),
    .PATTERN(48'h000000000000),
    .PREADDINSEL("A"),
    .PREG(0),
    .RND(48'h000000000000),
    .SEL_MASK("MASK"),
    .SEL_PATTERN("PATTERN"),
    .USE_MULT("MULTIPLY"),
    .USE_PATTERN_DETECT("NO_PATDET"),
    .USE_SIMD("ONE48"),
    .USE_WIDEXOR("FALSE"),
    .XORSIMD("XOR24_48_96")) 
    p_1_out__1
       (.A({A__1[26],A__1[26],A__1[26],A__1,p_1_out__1_i_28_n_0}),
        .ACIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .ACOUT(NLW_p_1_out__1_ACOUT_UNCONNECTED[29:0]),
        .ALUMODE({1'b0,1'b0,1'b0,1'b0}),
        .B({1'b0,AXI_pu_conv_in31}),
        .BCIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .BCOUT(NLW_p_1_out__1_BCOUT_UNCONNECTED[17:0]),
        .C({A__1[26],A__1[26],A__1[26],A__1[26],A__1[26],A__1[26],A__1[26],A__1[26],A__1[26],A__1[26],A__1[26],A__1[26],A__1[26],A__1[26],A__1[26],A__1[26],A__1[26],A__1[26],A__1[26],A__1[26],A__1[26],A__1[26],A__1}),
        .CARRYCASCIN(1'b0),
        .CARRYCASCOUT(NLW_p_1_out__1_CARRYCASCOUT_UNCONNECTED),
        .CARRYIN(1'b0),
        .CARRYINSEL({1'b0,1'b0,1'b0}),
        .CARRYOUT(NLW_p_1_out__1_CARRYOUT_UNCONNECTED[3:0]),
        .CEA1(1'b0),
        .CEA2(1'b0),
        .CEAD(1'b0),
        .CEALUMODE(1'b0),
        .CEB1(1'b0),
        .CEB2(DSP_ALU_INST_1),
        .CEC(1'b0),
        .CECARRYIN(1'b0),
        .CECTRL(1'b0),
        .CED(1'b0),
        .CEINMODE(1'b0),
        .CEM(1'b0),
        .CEP(1'b0),
        .CLK(AXI4_Lite_ACLK),
        .D({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .INMODE({1'b0,1'b0,1'b0,1'b0,1'b0}),
        .MULTSIGNIN(1'b0),
        .MULTSIGNOUT(NLW_p_1_out__1_MULTSIGNOUT_UNCONNECTED),
        .OPMODE({1'b0,1'b0,1'b0,\out2[17] ,\out2[17] ,1'b0,1'b1,1'b0,1'b1}),
        .OVERFLOW(NLW_p_1_out__1_OVERFLOW_UNCONNECTED),
        .P({NLW_p_1_out__1_P_UNCONNECTED[47:45],p_1_out__1_n_61,p_1_out__1_n_62,p_1_out__1_n_63,p_1_out__1_n_64,p_1_out__1_n_65,p_1_out__1_n_66,p_1_out__1_n_67,p_1_out__1_n_68,p_1_out__1_n_69,p_1_out__1_n_70,out2,p_1_out__1_n_89,p_1_out__1_n_90,p_1_out__1_n_91,p_1_out__1_n_92,p_1_out__1_n_93,p_1_out__1_n_94,p_1_out__1_n_95,p_1_out__1_n_96,p_1_out__1_n_97,p_1_out__1_n_98,p_1_out__1_n_99,p_1_out__1_n_100,p_1_out__1_n_101,p_1_out__1_n_102,p_1_out__1_n_103,p_1_out__1_n_104,p_1_out__1_n_105}),
        .PATTERNBDETECT(NLW_p_1_out__1_PATTERNBDETECT_UNCONNECTED),
        .PATTERNDETECT(NLW_p_1_out__1_PATTERNDETECT_UNCONNECTED),
        .PCIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .PCOUT(NLW_p_1_out__1_PCOUT_UNCONNECTED[47:0]),
        .RSTA(1'b0),
        .RSTALLCARRYIN(1'b0),
        .RSTALUMODE(1'b0),
        .RSTB(reset),
        .RSTC(1'b0),
        .RSTCTRL(1'b0),
        .RSTD(1'b0),
        .RSTINMODE(1'b0),
        .RSTM(1'b0),
        .RSTP(1'b0),
        .UNDERFLOW(NLW_p_1_out__1_UNDERFLOW_UNCONNECTED),
        .XOROUT(NLW_p_1_out__1_XOROUT_UNCONNECTED[7:0]));
  (* KEEP_HIERARCHY = "yes" *) 
  (* METHODOLOGY_DRC_VIOS = "{SYNTH-11 {cell *THIS*}}" *) 
  DSP48E2 #(
    .ACASCREG(0),
    .ADREG(1),
    .ALUMODEREG(0),
    .AMULTSEL("A"),
    .AREG(0),
    .AUTORESET_PATDET("NO_RESET"),
    .AUTORESET_PRIORITY("RESET"),
    .A_INPUT("DIRECT"),
    .BCASCREG(1),
    .BMULTSEL("B"),
    .BREG(1),
    .B_INPUT("DIRECT"),
    .CARRYINREG(0),
    .CARRYINSELREG(0),
    .CREG(0),
    .DREG(1),
    .INMODEREG(0),
    .MASK(48'h3FFFFFFFFFFF),
    .MREG(0),
    .OPMODEREG(0),
    .PATTERN(48'h000000000000),
    .PREADDINSEL("A"),
    .PREG(0),
    .RND(48'h000000000000),
    .SEL_MASK("MASK"),
    .SEL_PATTERN("PATTERN"),
    .USE_MULT("MULTIPLY"),
    .USE_PATTERN_DETECT("NO_PATDET"),
    .USE_SIMD("ONE48"),
    .USE_WIDEXOR("FALSE"),
    .XORSIMD("XOR24_48_96")) 
    p_1_out__10
       (.A({A__10[26],A__10[26],A__10[26],A__10,p_1_out__10_i_28_n_0}),
        .ACIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .ACOUT(NLW_p_1_out__10_ACOUT_UNCONNECTED[29:0]),
        .ALUMODE({1'b0,1'b0,1'b0,1'b0}),
        .B({1'b0,AXI_pu_conv_in31}),
        .BCIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .BCOUT(NLW_p_1_out__10_BCOUT_UNCONNECTED[17:0]),
        .C({A__10[26],A__10[26],A__10[26],A__10[26],A__10[26],A__10[26],A__10[26],A__10[26],A__10[26],A__10[26],A__10[26],A__10[26],A__10[26],A__10[26],A__10[26],A__10[26],A__10[26],A__10[26],A__10[26],A__10[26],A__10[26],A__10[26],A__10}),
        .CARRYCASCIN(1'b0),
        .CARRYCASCOUT(NLW_p_1_out__10_CARRYCASCOUT_UNCONNECTED),
        .CARRYIN(1'b0),
        .CARRYINSEL({1'b0,1'b0,1'b0}),
        .CARRYOUT(NLW_p_1_out__10_CARRYOUT_UNCONNECTED[3:0]),
        .CEA1(1'b0),
        .CEA2(1'b0),
        .CEAD(1'b0),
        .CEALUMODE(1'b0),
        .CEB1(1'b0),
        .CEB2(DSP_ALU_INST_10),
        .CEC(1'b0),
        .CECARRYIN(1'b0),
        .CECTRL(1'b0),
        .CED(1'b0),
        .CEINMODE(1'b0),
        .CEM(1'b0),
        .CEP(1'b0),
        .CLK(AXI4_Lite_ACLK),
        .D({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .INMODE({1'b0,1'b0,1'b0,1'b0,1'b0}),
        .MULTSIGNIN(1'b0),
        .MULTSIGNOUT(NLW_p_1_out__10_MULTSIGNOUT_UNCONNECTED),
        .OPMODE({1'b0,1'b0,1'b0,\out11[17] ,\out11[17] ,1'b0,1'b1,1'b0,1'b1}),
        .OVERFLOW(NLW_p_1_out__10_OVERFLOW_UNCONNECTED),
        .P({NLW_p_1_out__10_P_UNCONNECTED[47:45],p_1_out__10_n_61,p_1_out__10_n_62,p_1_out__10_n_63,p_1_out__10_n_64,p_1_out__10_n_65,p_1_out__10_n_66,p_1_out__10_n_67,p_1_out__10_n_68,p_1_out__10_n_69,p_1_out__10_n_70,out11,p_1_out__10_n_89,p_1_out__10_n_90,p_1_out__10_n_91,p_1_out__10_n_92,p_1_out__10_n_93,p_1_out__10_n_94,p_1_out__10_n_95,p_1_out__10_n_96,p_1_out__10_n_97,p_1_out__10_n_98,p_1_out__10_n_99,p_1_out__10_n_100,p_1_out__10_n_101,p_1_out__10_n_102,p_1_out__10_n_103,p_1_out__10_n_104,p_1_out__10_n_105}),
        .PATTERNBDETECT(NLW_p_1_out__10_PATTERNBDETECT_UNCONNECTED),
        .PATTERNDETECT(NLW_p_1_out__10_PATTERNDETECT_UNCONNECTED),
        .PCIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .PCOUT(NLW_p_1_out__10_PCOUT_UNCONNECTED[47:0]),
        .RSTA(1'b0),
        .RSTALLCARRYIN(1'b0),
        .RSTALUMODE(1'b0),
        .RSTB(reset),
        .RSTC(1'b0),
        .RSTCTRL(1'b0),
        .RSTD(1'b0),
        .RSTINMODE(1'b0),
        .RSTM(1'b0),
        .RSTP(1'b0),
        .UNDERFLOW(NLW_p_1_out__10_UNDERFLOW_UNCONNECTED),
        .XOROUT(NLW_p_1_out__10_XOROUT_UNCONNECTED[7:0]));
  (* SOFT_HLUTNM = "soft_lutpair180" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__10_i_10
       (.I0(in11[18]),
        .I1(Delay11_out1[18]),
        .I2(adc_trigger),
        .O(A__10[18]));
  (* SOFT_HLUTNM = "soft_lutpair180" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__10_i_11
       (.I0(in11[17]),
        .I1(Delay11_out1[17]),
        .I2(adc_trigger),
        .O(A__10[17]));
  (* SOFT_HLUTNM = "soft_lutpair179" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__10_i_12
       (.I0(in11[16]),
        .I1(Delay11_out1[16]),
        .I2(adc_trigger),
        .O(A__10[16]));
  (* SOFT_HLUTNM = "soft_lutpair179" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__10_i_13
       (.I0(in11[15]),
        .I1(Delay11_out1[15]),
        .I2(adc_trigger),
        .O(A__10[15]));
  (* SOFT_HLUTNM = "soft_lutpair178" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__10_i_14
       (.I0(in11[14]),
        .I1(Delay11_out1[14]),
        .I2(adc_trigger),
        .O(A__10[14]));
  (* SOFT_HLUTNM = "soft_lutpair178" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__10_i_15
       (.I0(in11[13]),
        .I1(Delay11_out1[13]),
        .I2(adc_trigger),
        .O(A__10[13]));
  (* SOFT_HLUTNM = "soft_lutpair177" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__10_i_16
       (.I0(in11[12]),
        .I1(Delay11_out1[12]),
        .I2(adc_trigger),
        .O(A__10[12]));
  (* SOFT_HLUTNM = "soft_lutpair177" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__10_i_17
       (.I0(in11[11]),
        .I1(Delay11_out1[11]),
        .I2(adc_trigger),
        .O(A__10[11]));
  (* SOFT_HLUTNM = "soft_lutpair176" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__10_i_18
       (.I0(in11[10]),
        .I1(Delay11_out1[10]),
        .I2(adc_trigger),
        .O(A__10[10]));
  (* SOFT_HLUTNM = "soft_lutpair176" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__10_i_19
       (.I0(in11[9]),
        .I1(Delay11_out1[9]),
        .I2(adc_trigger),
        .O(A__10[9]));
  (* SOFT_HLUTNM = "soft_lutpair184" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__10_i_2
       (.I0(in11[26]),
        .I1(Delay11_out1[26]),
        .I2(adc_trigger),
        .O(A__10[26]));
  (* SOFT_HLUTNM = "soft_lutpair175" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__10_i_20
       (.I0(in11[8]),
        .I1(Delay11_out1[8]),
        .I2(adc_trigger),
        .O(A__10[8]));
  (* SOFT_HLUTNM = "soft_lutpair175" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__10_i_21
       (.I0(in11[7]),
        .I1(Delay11_out1[7]),
        .I2(adc_trigger),
        .O(A__10[7]));
  (* SOFT_HLUTNM = "soft_lutpair174" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__10_i_22
       (.I0(in11[6]),
        .I1(Delay11_out1[6]),
        .I2(adc_trigger),
        .O(A__10[6]));
  (* SOFT_HLUTNM = "soft_lutpair174" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__10_i_23
       (.I0(in11[5]),
        .I1(Delay11_out1[5]),
        .I2(adc_trigger),
        .O(A__10[5]));
  (* SOFT_HLUTNM = "soft_lutpair173" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__10_i_24
       (.I0(in11[4]),
        .I1(Delay11_out1[4]),
        .I2(adc_trigger),
        .O(A__10[4]));
  (* SOFT_HLUTNM = "soft_lutpair173" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__10_i_25
       (.I0(in11[3]),
        .I1(Delay11_out1[3]),
        .I2(adc_trigger),
        .O(A__10[3]));
  (* SOFT_HLUTNM = "soft_lutpair172" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__10_i_26
       (.I0(in11[2]),
        .I1(Delay11_out1[2]),
        .I2(adc_trigger),
        .O(A__10[2]));
  (* SOFT_HLUTNM = "soft_lutpair172" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__10_i_27
       (.I0(in11[1]),
        .I1(Delay11_out1[1]),
        .I2(adc_trigger),
        .O(A__10[1]));
  (* SOFT_HLUTNM = "soft_lutpair171" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__10_i_28
       (.I0(in11[0]),
        .I1(Delay11_out1[0]),
        .I2(adc_trigger),
        .O(p_1_out__10_i_28_n_0));
  (* SOFT_HLUTNM = "soft_lutpair184" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__10_i_3
       (.I0(in11[25]),
        .I1(Delay11_out1[25]),
        .I2(adc_trigger),
        .O(A__10[25]));
  (* SOFT_HLUTNM = "soft_lutpair183" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__10_i_4
       (.I0(in11[24]),
        .I1(Delay11_out1[24]),
        .I2(adc_trigger),
        .O(A__10[24]));
  (* SOFT_HLUTNM = "soft_lutpair183" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__10_i_5
       (.I0(in11[23]),
        .I1(Delay11_out1[23]),
        .I2(adc_trigger),
        .O(A__10[23]));
  (* SOFT_HLUTNM = "soft_lutpair182" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__10_i_6
       (.I0(in11[22]),
        .I1(Delay11_out1[22]),
        .I2(adc_trigger),
        .O(A__10[22]));
  (* SOFT_HLUTNM = "soft_lutpair182" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__10_i_7
       (.I0(in11[21]),
        .I1(Delay11_out1[21]),
        .I2(adc_trigger),
        .O(A__10[21]));
  (* SOFT_HLUTNM = "soft_lutpair181" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__10_i_8
       (.I0(in11[20]),
        .I1(Delay11_out1[20]),
        .I2(adc_trigger),
        .O(A__10[20]));
  (* SOFT_HLUTNM = "soft_lutpair181" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__10_i_9
       (.I0(in11[19]),
        .I1(Delay11_out1[19]),
        .I2(adc_trigger),
        .O(A__10[19]));
  (* KEEP_HIERARCHY = "yes" *) 
  (* METHODOLOGY_DRC_VIOS = "{SYNTH-11 {cell *THIS*}}" *) 
  DSP48E2 #(
    .ACASCREG(0),
    .ADREG(1),
    .ALUMODEREG(0),
    .AMULTSEL("A"),
    .AREG(0),
    .AUTORESET_PATDET("NO_RESET"),
    .AUTORESET_PRIORITY("RESET"),
    .A_INPUT("DIRECT"),
    .BCASCREG(1),
    .BMULTSEL("B"),
    .BREG(1),
    .B_INPUT("DIRECT"),
    .CARRYINREG(0),
    .CARRYINSELREG(0),
    .CREG(0),
    .DREG(1),
    .INMODEREG(0),
    .MASK(48'h3FFFFFFFFFFF),
    .MREG(0),
    .OPMODEREG(0),
    .PATTERN(48'h000000000000),
    .PREADDINSEL("A"),
    .PREG(0),
    .RND(48'h000000000000),
    .SEL_MASK("MASK"),
    .SEL_PATTERN("PATTERN"),
    .USE_MULT("MULTIPLY"),
    .USE_PATTERN_DETECT("NO_PATDET"),
    .USE_SIMD("ONE48"),
    .USE_WIDEXOR("FALSE"),
    .XORSIMD("XOR24_48_96")) 
    p_1_out__11
       (.A({A__11[26],A__11[26],A__11[26],A__11,p_1_out__11_i_28_n_0}),
        .ACIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .ACOUT(NLW_p_1_out__11_ACOUT_UNCONNECTED[29:0]),
        .ALUMODE({1'b0,1'b0,1'b0,1'b0}),
        .B({1'b0,AXI_pu_conv_in31}),
        .BCIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .BCOUT(NLW_p_1_out__11_BCOUT_UNCONNECTED[17:0]),
        .C({A__11[26],A__11[26],A__11[26],A__11[26],A__11[26],A__11[26],A__11[26],A__11[26],A__11[26],A__11[26],A__11[26],A__11[26],A__11[26],A__11[26],A__11[26],A__11[26],A__11[26],A__11[26],A__11[26],A__11[26],A__11[26],A__11[26],A__11}),
        .CARRYCASCIN(1'b0),
        .CARRYCASCOUT(NLW_p_1_out__11_CARRYCASCOUT_UNCONNECTED),
        .CARRYIN(1'b0),
        .CARRYINSEL({1'b0,1'b0,1'b0}),
        .CARRYOUT(NLW_p_1_out__11_CARRYOUT_UNCONNECTED[3:0]),
        .CEA1(1'b0),
        .CEA2(1'b0),
        .CEAD(1'b0),
        .CEALUMODE(1'b0),
        .CEB1(1'b0),
        .CEB2(DSP_ALU_INST_11),
        .CEC(1'b0),
        .CECARRYIN(1'b0),
        .CECTRL(1'b0),
        .CED(1'b0),
        .CEINMODE(1'b0),
        .CEM(1'b0),
        .CEP(1'b0),
        .CLK(AXI4_Lite_ACLK),
        .D({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .INMODE({1'b0,1'b0,1'b0,1'b0,1'b0}),
        .MULTSIGNIN(1'b0),
        .MULTSIGNOUT(NLW_p_1_out__11_MULTSIGNOUT_UNCONNECTED),
        .OPMODE({1'b0,1'b0,1'b0,\out12[17] ,\out12[17] ,1'b0,1'b1,1'b0,1'b1}),
        .OVERFLOW(NLW_p_1_out__11_OVERFLOW_UNCONNECTED),
        .P({NLW_p_1_out__11_P_UNCONNECTED[47:45],p_1_out__11_n_61,p_1_out__11_n_62,p_1_out__11_n_63,p_1_out__11_n_64,p_1_out__11_n_65,p_1_out__11_n_66,p_1_out__11_n_67,p_1_out__11_n_68,p_1_out__11_n_69,p_1_out__11_n_70,out12,p_1_out__11_n_89,p_1_out__11_n_90,p_1_out__11_n_91,p_1_out__11_n_92,p_1_out__11_n_93,p_1_out__11_n_94,p_1_out__11_n_95,p_1_out__11_n_96,p_1_out__11_n_97,p_1_out__11_n_98,p_1_out__11_n_99,p_1_out__11_n_100,p_1_out__11_n_101,p_1_out__11_n_102,p_1_out__11_n_103,p_1_out__11_n_104,p_1_out__11_n_105}),
        .PATTERNBDETECT(NLW_p_1_out__11_PATTERNBDETECT_UNCONNECTED),
        .PATTERNDETECT(NLW_p_1_out__11_PATTERNDETECT_UNCONNECTED),
        .PCIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .PCOUT(NLW_p_1_out__11_PCOUT_UNCONNECTED[47:0]),
        .RSTA(1'b0),
        .RSTALLCARRYIN(1'b0),
        .RSTALUMODE(1'b0),
        .RSTB(reset),
        .RSTC(1'b0),
        .RSTCTRL(1'b0),
        .RSTD(1'b0),
        .RSTINMODE(1'b0),
        .RSTM(1'b0),
        .RSTP(1'b0),
        .UNDERFLOW(NLW_p_1_out__11_UNDERFLOW_UNCONNECTED),
        .XOROUT(NLW_p_1_out__11_XOROUT_UNCONNECTED[7:0]));
  (* SOFT_HLUTNM = "soft_lutpair194" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__11_i_10
       (.I0(in12[18]),
        .I1(Delay12_out1[18]),
        .I2(adc_trigger),
        .O(A__11[18]));
  (* SOFT_HLUTNM = "soft_lutpair193" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__11_i_11
       (.I0(in12[17]),
        .I1(Delay12_out1[17]),
        .I2(adc_trigger),
        .O(A__11[17]));
  (* SOFT_HLUTNM = "soft_lutpair193" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__11_i_12
       (.I0(in12[16]),
        .I1(Delay12_out1[16]),
        .I2(adc_trigger),
        .O(A__11[16]));
  (* SOFT_HLUTNM = "soft_lutpair192" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__11_i_13
       (.I0(in12[15]),
        .I1(Delay12_out1[15]),
        .I2(adc_trigger),
        .O(A__11[15]));
  (* SOFT_HLUTNM = "soft_lutpair192" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__11_i_14
       (.I0(in12[14]),
        .I1(Delay12_out1[14]),
        .I2(adc_trigger),
        .O(A__11[14]));
  (* SOFT_HLUTNM = "soft_lutpair191" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__11_i_15
       (.I0(in12[13]),
        .I1(Delay12_out1[13]),
        .I2(adc_trigger),
        .O(A__11[13]));
  (* SOFT_HLUTNM = "soft_lutpair191" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__11_i_16
       (.I0(in12[12]),
        .I1(Delay12_out1[12]),
        .I2(adc_trigger),
        .O(A__11[12]));
  (* SOFT_HLUTNM = "soft_lutpair190" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__11_i_17
       (.I0(in12[11]),
        .I1(Delay12_out1[11]),
        .I2(adc_trigger),
        .O(A__11[11]));
  (* SOFT_HLUTNM = "soft_lutpair190" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__11_i_18
       (.I0(in12[10]),
        .I1(Delay12_out1[10]),
        .I2(adc_trigger),
        .O(A__11[10]));
  (* SOFT_HLUTNM = "soft_lutpair189" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__11_i_19
       (.I0(in12[9]),
        .I1(Delay12_out1[9]),
        .I2(adc_trigger),
        .O(A__11[9]));
  (* SOFT_HLUTNM = "soft_lutpair198" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__11_i_2
       (.I0(in12[26]),
        .I1(Delay12_out1[26]),
        .I2(adc_trigger),
        .O(A__11[26]));
  (* SOFT_HLUTNM = "soft_lutpair189" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__11_i_20
       (.I0(in12[8]),
        .I1(Delay12_out1[8]),
        .I2(adc_trigger),
        .O(A__11[8]));
  (* SOFT_HLUTNM = "soft_lutpair188" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__11_i_21
       (.I0(in12[7]),
        .I1(Delay12_out1[7]),
        .I2(adc_trigger),
        .O(A__11[7]));
  (* SOFT_HLUTNM = "soft_lutpair188" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__11_i_22
       (.I0(in12[6]),
        .I1(Delay12_out1[6]),
        .I2(adc_trigger),
        .O(A__11[6]));
  (* SOFT_HLUTNM = "soft_lutpair187" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__11_i_23
       (.I0(in12[5]),
        .I1(Delay12_out1[5]),
        .I2(adc_trigger),
        .O(A__11[5]));
  (* SOFT_HLUTNM = "soft_lutpair187" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__11_i_24
       (.I0(in12[4]),
        .I1(Delay12_out1[4]),
        .I2(adc_trigger),
        .O(A__11[4]));
  (* SOFT_HLUTNM = "soft_lutpair186" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__11_i_25
       (.I0(in12[3]),
        .I1(Delay12_out1[3]),
        .I2(adc_trigger),
        .O(A__11[3]));
  (* SOFT_HLUTNM = "soft_lutpair186" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__11_i_26
       (.I0(in12[2]),
        .I1(Delay12_out1[2]),
        .I2(adc_trigger),
        .O(A__11[2]));
  (* SOFT_HLUTNM = "soft_lutpair185" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__11_i_27
       (.I0(in12[1]),
        .I1(Delay12_out1[1]),
        .I2(adc_trigger),
        .O(A__11[1]));
  (* SOFT_HLUTNM = "soft_lutpair185" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__11_i_28
       (.I0(in12[0]),
        .I1(Delay12_out1[0]),
        .I2(adc_trigger),
        .O(p_1_out__11_i_28_n_0));
  (* SOFT_HLUTNM = "soft_lutpair197" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__11_i_3
       (.I0(in12[25]),
        .I1(Delay12_out1[25]),
        .I2(adc_trigger),
        .O(A__11[25]));
  (* SOFT_HLUTNM = "soft_lutpair197" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__11_i_4
       (.I0(in12[24]),
        .I1(Delay12_out1[24]),
        .I2(adc_trigger),
        .O(A__11[24]));
  (* SOFT_HLUTNM = "soft_lutpair196" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__11_i_5
       (.I0(in12[23]),
        .I1(Delay12_out1[23]),
        .I2(adc_trigger),
        .O(A__11[23]));
  (* SOFT_HLUTNM = "soft_lutpair196" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__11_i_6
       (.I0(in12[22]),
        .I1(Delay12_out1[22]),
        .I2(adc_trigger),
        .O(A__11[22]));
  (* SOFT_HLUTNM = "soft_lutpair195" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__11_i_7
       (.I0(in12[21]),
        .I1(Delay12_out1[21]),
        .I2(adc_trigger),
        .O(A__11[21]));
  (* SOFT_HLUTNM = "soft_lutpair195" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__11_i_8
       (.I0(in12[20]),
        .I1(Delay12_out1[20]),
        .I2(adc_trigger),
        .O(A__11[20]));
  (* SOFT_HLUTNM = "soft_lutpair194" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__11_i_9
       (.I0(in12[19]),
        .I1(Delay12_out1[19]),
        .I2(adc_trigger),
        .O(A__11[19]));
  (* KEEP_HIERARCHY = "yes" *) 
  (* METHODOLOGY_DRC_VIOS = "{SYNTH-11 {cell *THIS*}}" *) 
  DSP48E2 #(
    .ACASCREG(0),
    .ADREG(1),
    .ALUMODEREG(0),
    .AMULTSEL("A"),
    .AREG(0),
    .AUTORESET_PATDET("NO_RESET"),
    .AUTORESET_PRIORITY("RESET"),
    .A_INPUT("DIRECT"),
    .BCASCREG(1),
    .BMULTSEL("B"),
    .BREG(1),
    .B_INPUT("DIRECT"),
    .CARRYINREG(0),
    .CARRYINSELREG(0),
    .CREG(0),
    .DREG(1),
    .INMODEREG(0),
    .MASK(48'h3FFFFFFFFFFF),
    .MREG(0),
    .OPMODEREG(0),
    .PATTERN(48'h000000000000),
    .PREADDINSEL("A"),
    .PREG(0),
    .RND(48'h000000000000),
    .SEL_MASK("MASK"),
    .SEL_PATTERN("PATTERN"),
    .USE_MULT("MULTIPLY"),
    .USE_PATTERN_DETECT("NO_PATDET"),
    .USE_SIMD("ONE48"),
    .USE_WIDEXOR("FALSE"),
    .XORSIMD("XOR24_48_96")) 
    p_1_out__12
       (.A({A__12[26],A__12[26],A__12[26],A__12,p_1_out__12_i_28_n_0}),
        .ACIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .ACOUT(NLW_p_1_out__12_ACOUT_UNCONNECTED[29:0]),
        .ALUMODE({1'b0,1'b0,1'b0,1'b0}),
        .B({1'b0,AXI_pu_conv_in31}),
        .BCIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .BCOUT(NLW_p_1_out__12_BCOUT_UNCONNECTED[17:0]),
        .C({A__12[26],A__12[26],A__12[26],A__12[26],A__12[26],A__12[26],A__12[26],A__12[26],A__12[26],A__12[26],A__12[26],A__12[26],A__12[26],A__12[26],A__12[26],A__12[26],A__12[26],A__12[26],A__12[26],A__12[26],A__12[26],A__12[26],A__12}),
        .CARRYCASCIN(1'b0),
        .CARRYCASCOUT(NLW_p_1_out__12_CARRYCASCOUT_UNCONNECTED),
        .CARRYIN(1'b0),
        .CARRYINSEL({1'b0,1'b0,1'b0}),
        .CARRYOUT(NLW_p_1_out__12_CARRYOUT_UNCONNECTED[3:0]),
        .CEA1(1'b0),
        .CEA2(1'b0),
        .CEAD(1'b0),
        .CEALUMODE(1'b0),
        .CEB1(1'b0),
        .CEB2(DSP_ALU_INST_12),
        .CEC(1'b0),
        .CECARRYIN(1'b0),
        .CECTRL(1'b0),
        .CED(1'b0),
        .CEINMODE(1'b0),
        .CEM(1'b0),
        .CEP(1'b0),
        .CLK(AXI4_Lite_ACLK),
        .D({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .INMODE({1'b0,1'b0,1'b0,1'b0,1'b0}),
        .MULTSIGNIN(1'b0),
        .MULTSIGNOUT(NLW_p_1_out__12_MULTSIGNOUT_UNCONNECTED),
        .OPMODE({1'b0,1'b0,1'b0,\out13[17] ,\out13[17] ,1'b0,1'b1,1'b0,1'b1}),
        .OVERFLOW(NLW_p_1_out__12_OVERFLOW_UNCONNECTED),
        .P({NLW_p_1_out__12_P_UNCONNECTED[47:45],p_1_out__12_n_61,p_1_out__12_n_62,p_1_out__12_n_63,p_1_out__12_n_64,p_1_out__12_n_65,p_1_out__12_n_66,p_1_out__12_n_67,p_1_out__12_n_68,p_1_out__12_n_69,p_1_out__12_n_70,out13,p_1_out__12_n_89,p_1_out__12_n_90,p_1_out__12_n_91,p_1_out__12_n_92,p_1_out__12_n_93,p_1_out__12_n_94,p_1_out__12_n_95,p_1_out__12_n_96,p_1_out__12_n_97,p_1_out__12_n_98,p_1_out__12_n_99,p_1_out__12_n_100,p_1_out__12_n_101,p_1_out__12_n_102,p_1_out__12_n_103,p_1_out__12_n_104,p_1_out__12_n_105}),
        .PATTERNBDETECT(NLW_p_1_out__12_PATTERNBDETECT_UNCONNECTED),
        .PATTERNDETECT(NLW_p_1_out__12_PATTERNDETECT_UNCONNECTED),
        .PCIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .PCOUT(NLW_p_1_out__12_PCOUT_UNCONNECTED[47:0]),
        .RSTA(1'b0),
        .RSTALLCARRYIN(1'b0),
        .RSTALUMODE(1'b0),
        .RSTB(reset),
        .RSTC(1'b0),
        .RSTCTRL(1'b0),
        .RSTD(1'b0),
        .RSTINMODE(1'b0),
        .RSTM(1'b0),
        .RSTP(1'b0),
        .UNDERFLOW(NLW_p_1_out__12_UNDERFLOW_UNCONNECTED),
        .XOROUT(NLW_p_1_out__12_XOROUT_UNCONNECTED[7:0]));
  (* SOFT_HLUTNM = "soft_lutpair207" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__12_i_10
       (.I0(in13[18]),
        .I1(Delay13_out1[18]),
        .I2(adc_trigger),
        .O(A__12[18]));
  (* SOFT_HLUTNM = "soft_lutpair207" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__12_i_11
       (.I0(in13[17]),
        .I1(Delay13_out1[17]),
        .I2(adc_trigger),
        .O(A__12[17]));
  (* SOFT_HLUTNM = "soft_lutpair206" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__12_i_12
       (.I0(in13[16]),
        .I1(Delay13_out1[16]),
        .I2(adc_trigger),
        .O(A__12[16]));
  (* SOFT_HLUTNM = "soft_lutpair206" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__12_i_13
       (.I0(in13[15]),
        .I1(Delay13_out1[15]),
        .I2(adc_trigger),
        .O(A__12[15]));
  (* SOFT_HLUTNM = "soft_lutpair205" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__12_i_14
       (.I0(in13[14]),
        .I1(Delay13_out1[14]),
        .I2(adc_trigger),
        .O(A__12[14]));
  (* SOFT_HLUTNM = "soft_lutpair205" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__12_i_15
       (.I0(in13[13]),
        .I1(Delay13_out1[13]),
        .I2(adc_trigger),
        .O(A__12[13]));
  (* SOFT_HLUTNM = "soft_lutpair204" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__12_i_16
       (.I0(in13[12]),
        .I1(Delay13_out1[12]),
        .I2(adc_trigger),
        .O(A__12[12]));
  (* SOFT_HLUTNM = "soft_lutpair204" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__12_i_17
       (.I0(in13[11]),
        .I1(Delay13_out1[11]),
        .I2(adc_trigger),
        .O(A__12[11]));
  (* SOFT_HLUTNM = "soft_lutpair203" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__12_i_18
       (.I0(in13[10]),
        .I1(Delay13_out1[10]),
        .I2(adc_trigger),
        .O(A__12[10]));
  (* SOFT_HLUTNM = "soft_lutpair203" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__12_i_19
       (.I0(in13[9]),
        .I1(Delay13_out1[9]),
        .I2(adc_trigger),
        .O(A__12[9]));
  (* SOFT_HLUTNM = "soft_lutpair211" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__12_i_2
       (.I0(in13[26]),
        .I1(Delay13_out1[26]),
        .I2(adc_trigger),
        .O(A__12[26]));
  (* SOFT_HLUTNM = "soft_lutpair202" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__12_i_20
       (.I0(in13[8]),
        .I1(Delay13_out1[8]),
        .I2(adc_trigger),
        .O(A__12[8]));
  (* SOFT_HLUTNM = "soft_lutpair202" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__12_i_21
       (.I0(in13[7]),
        .I1(Delay13_out1[7]),
        .I2(adc_trigger),
        .O(A__12[7]));
  (* SOFT_HLUTNM = "soft_lutpair201" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__12_i_22
       (.I0(in13[6]),
        .I1(Delay13_out1[6]),
        .I2(adc_trigger),
        .O(A__12[6]));
  (* SOFT_HLUTNM = "soft_lutpair201" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__12_i_23
       (.I0(in13[5]),
        .I1(Delay13_out1[5]),
        .I2(adc_trigger),
        .O(A__12[5]));
  (* SOFT_HLUTNM = "soft_lutpair200" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__12_i_24
       (.I0(in13[4]),
        .I1(Delay13_out1[4]),
        .I2(adc_trigger),
        .O(A__12[4]));
  (* SOFT_HLUTNM = "soft_lutpair200" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__12_i_25
       (.I0(in13[3]),
        .I1(Delay13_out1[3]),
        .I2(adc_trigger),
        .O(A__12[3]));
  (* SOFT_HLUTNM = "soft_lutpair199" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__12_i_26
       (.I0(in13[2]),
        .I1(Delay13_out1[2]),
        .I2(adc_trigger),
        .O(A__12[2]));
  (* SOFT_HLUTNM = "soft_lutpair199" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__12_i_27
       (.I0(in13[1]),
        .I1(Delay13_out1[1]),
        .I2(adc_trigger),
        .O(A__12[1]));
  (* SOFT_HLUTNM = "soft_lutpair198" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__12_i_28
       (.I0(in13[0]),
        .I1(Delay13_out1[0]),
        .I2(adc_trigger),
        .O(p_1_out__12_i_28_n_0));
  (* SOFT_HLUTNM = "soft_lutpair211" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__12_i_3
       (.I0(in13[25]),
        .I1(Delay13_out1[25]),
        .I2(adc_trigger),
        .O(A__12[25]));
  (* SOFT_HLUTNM = "soft_lutpair210" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__12_i_4
       (.I0(in13[24]),
        .I1(Delay13_out1[24]),
        .I2(adc_trigger),
        .O(A__12[24]));
  (* SOFT_HLUTNM = "soft_lutpair210" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__12_i_5
       (.I0(in13[23]),
        .I1(Delay13_out1[23]),
        .I2(adc_trigger),
        .O(A__12[23]));
  (* SOFT_HLUTNM = "soft_lutpair209" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__12_i_6
       (.I0(in13[22]),
        .I1(Delay13_out1[22]),
        .I2(adc_trigger),
        .O(A__12[22]));
  (* SOFT_HLUTNM = "soft_lutpair209" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__12_i_7
       (.I0(in13[21]),
        .I1(Delay13_out1[21]),
        .I2(adc_trigger),
        .O(A__12[21]));
  (* SOFT_HLUTNM = "soft_lutpair208" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__12_i_8
       (.I0(in13[20]),
        .I1(Delay13_out1[20]),
        .I2(adc_trigger),
        .O(A__12[20]));
  (* SOFT_HLUTNM = "soft_lutpair208" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__12_i_9
       (.I0(in13[19]),
        .I1(Delay13_out1[19]),
        .I2(adc_trigger),
        .O(A__12[19]));
  (* KEEP_HIERARCHY = "yes" *) 
  (* METHODOLOGY_DRC_VIOS = "{SYNTH-11 {cell *THIS*}}" *) 
  DSP48E2 #(
    .ACASCREG(0),
    .ADREG(1),
    .ALUMODEREG(0),
    .AMULTSEL("A"),
    .AREG(0),
    .AUTORESET_PATDET("NO_RESET"),
    .AUTORESET_PRIORITY("RESET"),
    .A_INPUT("DIRECT"),
    .BCASCREG(1),
    .BMULTSEL("B"),
    .BREG(1),
    .B_INPUT("DIRECT"),
    .CARRYINREG(0),
    .CARRYINSELREG(0),
    .CREG(0),
    .DREG(1),
    .INMODEREG(0),
    .MASK(48'h3FFFFFFFFFFF),
    .MREG(0),
    .OPMODEREG(0),
    .PATTERN(48'h000000000000),
    .PREADDINSEL("A"),
    .PREG(0),
    .RND(48'h000000000000),
    .SEL_MASK("MASK"),
    .SEL_PATTERN("PATTERN"),
    .USE_MULT("MULTIPLY"),
    .USE_PATTERN_DETECT("NO_PATDET"),
    .USE_SIMD("ONE48"),
    .USE_WIDEXOR("FALSE"),
    .XORSIMD("XOR24_48_96")) 
    p_1_out__13
       (.A({A__13[26],A__13[26],A__13[26],A__13,p_1_out__13_i_28_n_0}),
        .ACIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .ACOUT(NLW_p_1_out__13_ACOUT_UNCONNECTED[29:0]),
        .ALUMODE({1'b0,1'b0,1'b0,1'b0}),
        .B({1'b0,AXI_pu_conv_in31}),
        .BCIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .BCOUT(NLW_p_1_out__13_BCOUT_UNCONNECTED[17:0]),
        .C({A__13[26],A__13[26],A__13[26],A__13[26],A__13[26],A__13[26],A__13[26],A__13[26],A__13[26],A__13[26],A__13[26],A__13[26],A__13[26],A__13[26],A__13[26],A__13[26],A__13[26],A__13[26],A__13[26],A__13[26],A__13[26],A__13[26],A__13}),
        .CARRYCASCIN(1'b0),
        .CARRYCASCOUT(NLW_p_1_out__13_CARRYCASCOUT_UNCONNECTED),
        .CARRYIN(1'b0),
        .CARRYINSEL({1'b0,1'b0,1'b0}),
        .CARRYOUT(NLW_p_1_out__13_CARRYOUT_UNCONNECTED[3:0]),
        .CEA1(1'b0),
        .CEA2(1'b0),
        .CEAD(1'b0),
        .CEALUMODE(1'b0),
        .CEB1(1'b0),
        .CEB2(DSP_ALU_INST_13),
        .CEC(1'b0),
        .CECARRYIN(1'b0),
        .CECTRL(1'b0),
        .CED(1'b0),
        .CEINMODE(1'b0),
        .CEM(1'b0),
        .CEP(1'b0),
        .CLK(AXI4_Lite_ACLK),
        .D({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .INMODE({1'b0,1'b0,1'b0,1'b0,1'b0}),
        .MULTSIGNIN(1'b0),
        .MULTSIGNOUT(NLW_p_1_out__13_MULTSIGNOUT_UNCONNECTED),
        .OPMODE({1'b0,1'b0,1'b0,\out14[17] ,\out14[17] ,1'b0,1'b1,1'b0,1'b1}),
        .OVERFLOW(NLW_p_1_out__13_OVERFLOW_UNCONNECTED),
        .P({NLW_p_1_out__13_P_UNCONNECTED[47:45],p_1_out__13_n_61,p_1_out__13_n_62,p_1_out__13_n_63,p_1_out__13_n_64,p_1_out__13_n_65,p_1_out__13_n_66,p_1_out__13_n_67,p_1_out__13_n_68,p_1_out__13_n_69,p_1_out__13_n_70,out14,p_1_out__13_n_89,p_1_out__13_n_90,p_1_out__13_n_91,p_1_out__13_n_92,p_1_out__13_n_93,p_1_out__13_n_94,p_1_out__13_n_95,p_1_out__13_n_96,p_1_out__13_n_97,p_1_out__13_n_98,p_1_out__13_n_99,p_1_out__13_n_100,p_1_out__13_n_101,p_1_out__13_n_102,p_1_out__13_n_103,p_1_out__13_n_104,p_1_out__13_n_105}),
        .PATTERNBDETECT(NLW_p_1_out__13_PATTERNBDETECT_UNCONNECTED),
        .PATTERNDETECT(NLW_p_1_out__13_PATTERNDETECT_UNCONNECTED),
        .PCIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .PCOUT(NLW_p_1_out__13_PCOUT_UNCONNECTED[47:0]),
        .RSTA(1'b0),
        .RSTALLCARRYIN(1'b0),
        .RSTALUMODE(1'b0),
        .RSTB(reset),
        .RSTC(1'b0),
        .RSTCTRL(1'b0),
        .RSTD(1'b0),
        .RSTINMODE(1'b0),
        .RSTM(1'b0),
        .RSTP(1'b0),
        .UNDERFLOW(NLW_p_1_out__13_UNDERFLOW_UNCONNECTED),
        .XOROUT(NLW_p_1_out__13_XOROUT_UNCONNECTED[7:0]));
  (* SOFT_HLUTNM = "soft_lutpair221" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__13_i_10
       (.I0(in14[18]),
        .I1(Delay14_out1[18]),
        .I2(adc_trigger),
        .O(A__13[18]));
  (* SOFT_HLUTNM = "soft_lutpair220" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__13_i_11
       (.I0(in14[17]),
        .I1(Delay14_out1[17]),
        .I2(adc_trigger),
        .O(A__13[17]));
  (* SOFT_HLUTNM = "soft_lutpair220" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__13_i_12
       (.I0(in14[16]),
        .I1(Delay14_out1[16]),
        .I2(adc_trigger),
        .O(A__13[16]));
  (* SOFT_HLUTNM = "soft_lutpair219" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__13_i_13
       (.I0(in14[15]),
        .I1(Delay14_out1[15]),
        .I2(adc_trigger),
        .O(A__13[15]));
  (* SOFT_HLUTNM = "soft_lutpair219" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__13_i_14
       (.I0(in14[14]),
        .I1(Delay14_out1[14]),
        .I2(adc_trigger),
        .O(A__13[14]));
  (* SOFT_HLUTNM = "soft_lutpair218" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__13_i_15
       (.I0(in14[13]),
        .I1(Delay14_out1[13]),
        .I2(adc_trigger),
        .O(A__13[13]));
  (* SOFT_HLUTNM = "soft_lutpair218" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__13_i_16
       (.I0(in14[12]),
        .I1(Delay14_out1[12]),
        .I2(adc_trigger),
        .O(A__13[12]));
  (* SOFT_HLUTNM = "soft_lutpair217" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__13_i_17
       (.I0(in14[11]),
        .I1(Delay14_out1[11]),
        .I2(adc_trigger),
        .O(A__13[11]));
  (* SOFT_HLUTNM = "soft_lutpair217" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__13_i_18
       (.I0(in14[10]),
        .I1(Delay14_out1[10]),
        .I2(adc_trigger),
        .O(A__13[10]));
  (* SOFT_HLUTNM = "soft_lutpair216" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__13_i_19
       (.I0(in14[9]),
        .I1(Delay14_out1[9]),
        .I2(adc_trigger),
        .O(A__13[9]));
  (* SOFT_HLUTNM = "soft_lutpair225" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__13_i_2
       (.I0(in14[26]),
        .I1(Delay14_out1[26]),
        .I2(adc_trigger),
        .O(A__13[26]));
  (* SOFT_HLUTNM = "soft_lutpair216" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__13_i_20
       (.I0(in14[8]),
        .I1(Delay14_out1[8]),
        .I2(adc_trigger),
        .O(A__13[8]));
  (* SOFT_HLUTNM = "soft_lutpair215" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__13_i_21
       (.I0(in14[7]),
        .I1(Delay14_out1[7]),
        .I2(adc_trigger),
        .O(A__13[7]));
  (* SOFT_HLUTNM = "soft_lutpair215" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__13_i_22
       (.I0(in14[6]),
        .I1(Delay14_out1[6]),
        .I2(adc_trigger),
        .O(A__13[6]));
  (* SOFT_HLUTNM = "soft_lutpair214" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__13_i_23
       (.I0(in14[5]),
        .I1(Delay14_out1[5]),
        .I2(adc_trigger),
        .O(A__13[5]));
  (* SOFT_HLUTNM = "soft_lutpair214" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__13_i_24
       (.I0(in14[4]),
        .I1(Delay14_out1[4]),
        .I2(adc_trigger),
        .O(A__13[4]));
  (* SOFT_HLUTNM = "soft_lutpair213" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__13_i_25
       (.I0(in14[3]),
        .I1(Delay14_out1[3]),
        .I2(adc_trigger),
        .O(A__13[3]));
  (* SOFT_HLUTNM = "soft_lutpair213" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__13_i_26
       (.I0(in14[2]),
        .I1(Delay14_out1[2]),
        .I2(adc_trigger),
        .O(A__13[2]));
  (* SOFT_HLUTNM = "soft_lutpair212" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__13_i_27
       (.I0(in14[1]),
        .I1(Delay14_out1[1]),
        .I2(adc_trigger),
        .O(A__13[1]));
  (* SOFT_HLUTNM = "soft_lutpair212" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__13_i_28
       (.I0(in14[0]),
        .I1(Delay14_out1[0]),
        .I2(adc_trigger),
        .O(p_1_out__13_i_28_n_0));
  (* SOFT_HLUTNM = "soft_lutpair224" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__13_i_3
       (.I0(in14[25]),
        .I1(Delay14_out1[25]),
        .I2(adc_trigger),
        .O(A__13[25]));
  (* SOFT_HLUTNM = "soft_lutpair224" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__13_i_4
       (.I0(in14[24]),
        .I1(Delay14_out1[24]),
        .I2(adc_trigger),
        .O(A__13[24]));
  (* SOFT_HLUTNM = "soft_lutpair223" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__13_i_5
       (.I0(in14[23]),
        .I1(Delay14_out1[23]),
        .I2(adc_trigger),
        .O(A__13[23]));
  (* SOFT_HLUTNM = "soft_lutpair223" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__13_i_6
       (.I0(in14[22]),
        .I1(Delay14_out1[22]),
        .I2(adc_trigger),
        .O(A__13[22]));
  (* SOFT_HLUTNM = "soft_lutpair222" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__13_i_7
       (.I0(in14[21]),
        .I1(Delay14_out1[21]),
        .I2(adc_trigger),
        .O(A__13[21]));
  (* SOFT_HLUTNM = "soft_lutpair222" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__13_i_8
       (.I0(in14[20]),
        .I1(Delay14_out1[20]),
        .I2(adc_trigger),
        .O(A__13[20]));
  (* SOFT_HLUTNM = "soft_lutpair221" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__13_i_9
       (.I0(in14[19]),
        .I1(Delay14_out1[19]),
        .I2(adc_trigger),
        .O(A__13[19]));
  (* KEEP_HIERARCHY = "yes" *) 
  (* METHODOLOGY_DRC_VIOS = "{SYNTH-11 {cell *THIS*}}" *) 
  DSP48E2 #(
    .ACASCREG(0),
    .ADREG(1),
    .ALUMODEREG(0),
    .AMULTSEL("A"),
    .AREG(0),
    .AUTORESET_PATDET("NO_RESET"),
    .AUTORESET_PRIORITY("RESET"),
    .A_INPUT("DIRECT"),
    .BCASCREG(1),
    .BMULTSEL("B"),
    .BREG(1),
    .B_INPUT("DIRECT"),
    .CARRYINREG(0),
    .CARRYINSELREG(0),
    .CREG(0),
    .DREG(1),
    .INMODEREG(0),
    .MASK(48'h3FFFFFFFFFFF),
    .MREG(0),
    .OPMODEREG(0),
    .PATTERN(48'h000000000000),
    .PREADDINSEL("A"),
    .PREG(0),
    .RND(48'h000000000000),
    .SEL_MASK("MASK"),
    .SEL_PATTERN("PATTERN"),
    .USE_MULT("MULTIPLY"),
    .USE_PATTERN_DETECT("NO_PATDET"),
    .USE_SIMD("ONE48"),
    .USE_WIDEXOR("FALSE"),
    .XORSIMD("XOR24_48_96")) 
    p_1_out__14
       (.A({A__14[26],A__14[26],A__14[26],A__14,p_1_out__14_i_28_n_0}),
        .ACIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .ACOUT(NLW_p_1_out__14_ACOUT_UNCONNECTED[29:0]),
        .ALUMODE({1'b0,1'b0,1'b0,1'b0}),
        .B({1'b0,AXI_pu_conv_in31}),
        .BCIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .BCOUT(NLW_p_1_out__14_BCOUT_UNCONNECTED[17:0]),
        .C({A__14[26],A__14[26],A__14[26],A__14[26],A__14[26],A__14[26],A__14[26],A__14[26],A__14[26],A__14[26],A__14[26],A__14[26],A__14[26],A__14[26],A__14[26],A__14[26],A__14[26],A__14[26],A__14[26],A__14[26],A__14[26],A__14[26],A__14}),
        .CARRYCASCIN(1'b0),
        .CARRYCASCOUT(NLW_p_1_out__14_CARRYCASCOUT_UNCONNECTED),
        .CARRYIN(1'b0),
        .CARRYINSEL({1'b0,1'b0,1'b0}),
        .CARRYOUT(NLW_p_1_out__14_CARRYOUT_UNCONNECTED[3:0]),
        .CEA1(1'b0),
        .CEA2(1'b0),
        .CEAD(1'b0),
        .CEALUMODE(1'b0),
        .CEB1(1'b0),
        .CEB2(DSP_ALU_INST_14),
        .CEC(1'b0),
        .CECARRYIN(1'b0),
        .CECTRL(1'b0),
        .CED(1'b0),
        .CEINMODE(1'b0),
        .CEM(1'b0),
        .CEP(1'b0),
        .CLK(AXI4_Lite_ACLK),
        .D({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .INMODE({1'b0,1'b0,1'b0,1'b0,1'b0}),
        .MULTSIGNIN(1'b0),
        .MULTSIGNOUT(NLW_p_1_out__14_MULTSIGNOUT_UNCONNECTED),
        .OPMODE({1'b0,1'b0,1'b0,\out15[17] ,\out15[17] ,1'b0,1'b1,1'b0,1'b1}),
        .OVERFLOW(NLW_p_1_out__14_OVERFLOW_UNCONNECTED),
        .P({NLW_p_1_out__14_P_UNCONNECTED[47:45],p_1_out__14_n_61,p_1_out__14_n_62,p_1_out__14_n_63,p_1_out__14_n_64,p_1_out__14_n_65,p_1_out__14_n_66,p_1_out__14_n_67,p_1_out__14_n_68,p_1_out__14_n_69,p_1_out__14_n_70,out15,p_1_out__14_n_89,p_1_out__14_n_90,p_1_out__14_n_91,p_1_out__14_n_92,p_1_out__14_n_93,p_1_out__14_n_94,p_1_out__14_n_95,p_1_out__14_n_96,p_1_out__14_n_97,p_1_out__14_n_98,p_1_out__14_n_99,p_1_out__14_n_100,p_1_out__14_n_101,p_1_out__14_n_102,p_1_out__14_n_103,p_1_out__14_n_104,p_1_out__14_n_105}),
        .PATTERNBDETECT(NLW_p_1_out__14_PATTERNBDETECT_UNCONNECTED),
        .PATTERNDETECT(NLW_p_1_out__14_PATTERNDETECT_UNCONNECTED),
        .PCIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .PCOUT(NLW_p_1_out__14_PCOUT_UNCONNECTED[47:0]),
        .RSTA(1'b0),
        .RSTALLCARRYIN(1'b0),
        .RSTALUMODE(1'b0),
        .RSTB(reset),
        .RSTC(1'b0),
        .RSTCTRL(1'b0),
        .RSTD(1'b0),
        .RSTINMODE(1'b0),
        .RSTM(1'b0),
        .RSTP(1'b0),
        .UNDERFLOW(NLW_p_1_out__14_UNDERFLOW_UNCONNECTED),
        .XOROUT(NLW_p_1_out__14_XOROUT_UNCONNECTED[7:0]));
  (* SOFT_HLUTNM = "soft_lutpair234" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__14_i_10
       (.I0(in15[18]),
        .I1(Delay15_out1[18]),
        .I2(adc_trigger),
        .O(A__14[18]));
  (* SOFT_HLUTNM = "soft_lutpair234" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__14_i_11
       (.I0(in15[17]),
        .I1(Delay15_out1[17]),
        .I2(adc_trigger),
        .O(A__14[17]));
  (* SOFT_HLUTNM = "soft_lutpair233" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__14_i_12
       (.I0(in15[16]),
        .I1(Delay15_out1[16]),
        .I2(adc_trigger),
        .O(A__14[16]));
  (* SOFT_HLUTNM = "soft_lutpair233" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__14_i_13
       (.I0(in15[15]),
        .I1(Delay15_out1[15]),
        .I2(adc_trigger),
        .O(A__14[15]));
  (* SOFT_HLUTNM = "soft_lutpair232" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__14_i_14
       (.I0(in15[14]),
        .I1(Delay15_out1[14]),
        .I2(adc_trigger),
        .O(A__14[14]));
  (* SOFT_HLUTNM = "soft_lutpair232" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__14_i_15
       (.I0(in15[13]),
        .I1(Delay15_out1[13]),
        .I2(adc_trigger),
        .O(A__14[13]));
  (* SOFT_HLUTNM = "soft_lutpair231" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__14_i_16
       (.I0(in15[12]),
        .I1(Delay15_out1[12]),
        .I2(adc_trigger),
        .O(A__14[12]));
  (* SOFT_HLUTNM = "soft_lutpair231" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__14_i_17
       (.I0(in15[11]),
        .I1(Delay15_out1[11]),
        .I2(adc_trigger),
        .O(A__14[11]));
  (* SOFT_HLUTNM = "soft_lutpair230" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__14_i_18
       (.I0(in15[10]),
        .I1(Delay15_out1[10]),
        .I2(adc_trigger),
        .O(A__14[10]));
  (* SOFT_HLUTNM = "soft_lutpair230" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__14_i_19
       (.I0(in15[9]),
        .I1(Delay15_out1[9]),
        .I2(adc_trigger),
        .O(A__14[9]));
  (* SOFT_HLUTNM = "soft_lutpair238" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__14_i_2
       (.I0(in15[26]),
        .I1(Delay15_out1[26]),
        .I2(adc_trigger),
        .O(A__14[26]));
  (* SOFT_HLUTNM = "soft_lutpair229" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__14_i_20
       (.I0(in15[8]),
        .I1(Delay15_out1[8]),
        .I2(adc_trigger),
        .O(A__14[8]));
  (* SOFT_HLUTNM = "soft_lutpair229" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__14_i_21
       (.I0(in15[7]),
        .I1(Delay15_out1[7]),
        .I2(adc_trigger),
        .O(A__14[7]));
  (* SOFT_HLUTNM = "soft_lutpair228" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__14_i_22
       (.I0(in15[6]),
        .I1(Delay15_out1[6]),
        .I2(adc_trigger),
        .O(A__14[6]));
  (* SOFT_HLUTNM = "soft_lutpair228" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__14_i_23
       (.I0(in15[5]),
        .I1(Delay15_out1[5]),
        .I2(adc_trigger),
        .O(A__14[5]));
  (* SOFT_HLUTNM = "soft_lutpair227" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__14_i_24
       (.I0(in15[4]),
        .I1(Delay15_out1[4]),
        .I2(adc_trigger),
        .O(A__14[4]));
  (* SOFT_HLUTNM = "soft_lutpair227" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__14_i_25
       (.I0(in15[3]),
        .I1(Delay15_out1[3]),
        .I2(adc_trigger),
        .O(A__14[3]));
  (* SOFT_HLUTNM = "soft_lutpair226" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__14_i_26
       (.I0(in15[2]),
        .I1(Delay15_out1[2]),
        .I2(adc_trigger),
        .O(A__14[2]));
  (* SOFT_HLUTNM = "soft_lutpair226" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__14_i_27
       (.I0(in15[1]),
        .I1(Delay15_out1[1]),
        .I2(adc_trigger),
        .O(A__14[1]));
  (* SOFT_HLUTNM = "soft_lutpair225" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__14_i_28
       (.I0(in15[0]),
        .I1(Delay15_out1[0]),
        .I2(adc_trigger),
        .O(p_1_out__14_i_28_n_0));
  (* SOFT_HLUTNM = "soft_lutpair238" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__14_i_3
       (.I0(in15[25]),
        .I1(Delay15_out1[25]),
        .I2(adc_trigger),
        .O(A__14[25]));
  (* SOFT_HLUTNM = "soft_lutpair237" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__14_i_4
       (.I0(in15[24]),
        .I1(Delay15_out1[24]),
        .I2(adc_trigger),
        .O(A__14[24]));
  (* SOFT_HLUTNM = "soft_lutpair237" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__14_i_5
       (.I0(in15[23]),
        .I1(Delay15_out1[23]),
        .I2(adc_trigger),
        .O(A__14[23]));
  (* SOFT_HLUTNM = "soft_lutpair236" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__14_i_6
       (.I0(in15[22]),
        .I1(Delay15_out1[22]),
        .I2(adc_trigger),
        .O(A__14[22]));
  (* SOFT_HLUTNM = "soft_lutpair236" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__14_i_7
       (.I0(in15[21]),
        .I1(Delay15_out1[21]),
        .I2(adc_trigger),
        .O(A__14[21]));
  (* SOFT_HLUTNM = "soft_lutpair235" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__14_i_8
       (.I0(in15[20]),
        .I1(Delay15_out1[20]),
        .I2(adc_trigger),
        .O(A__14[20]));
  (* SOFT_HLUTNM = "soft_lutpair235" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__14_i_9
       (.I0(in15[19]),
        .I1(Delay15_out1[19]),
        .I2(adc_trigger),
        .O(A__14[19]));
  (* KEEP_HIERARCHY = "yes" *) 
  (* METHODOLOGY_DRC_VIOS = "{SYNTH-11 {cell *THIS*}}" *) 
  DSP48E2 #(
    .ACASCREG(0),
    .ADREG(1),
    .ALUMODEREG(0),
    .AMULTSEL("A"),
    .AREG(0),
    .AUTORESET_PATDET("NO_RESET"),
    .AUTORESET_PRIORITY("RESET"),
    .A_INPUT("DIRECT"),
    .BCASCREG(1),
    .BMULTSEL("B"),
    .BREG(1),
    .B_INPUT("DIRECT"),
    .CARRYINREG(0),
    .CARRYINSELREG(0),
    .CREG(0),
    .DREG(1),
    .INMODEREG(0),
    .MASK(48'h3FFFFFFFFFFF),
    .MREG(0),
    .OPMODEREG(0),
    .PATTERN(48'h000000000000),
    .PREADDINSEL("A"),
    .PREG(0),
    .RND(48'h000000000000),
    .SEL_MASK("MASK"),
    .SEL_PATTERN("PATTERN"),
    .USE_MULT("MULTIPLY"),
    .USE_PATTERN_DETECT("NO_PATDET"),
    .USE_SIMD("ONE48"),
    .USE_WIDEXOR("FALSE"),
    .XORSIMD("XOR24_48_96")) 
    p_1_out__15
       (.A({A__15[26],A__15[26],A__15[26],A__15,p_1_out__15_i_28_n_0}),
        .ACIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .ACOUT(NLW_p_1_out__15_ACOUT_UNCONNECTED[29:0]),
        .ALUMODE({1'b0,1'b0,1'b0,1'b0}),
        .B({1'b0,AXI_pu_conv_in31}),
        .BCIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .BCOUT(NLW_p_1_out__15_BCOUT_UNCONNECTED[17:0]),
        .C({A__15[26],A__15[26],A__15[26],A__15[26],A__15[26],A__15[26],A__15[26],A__15[26],A__15[26],A__15[26],A__15[26],A__15[26],A__15[26],A__15[26],A__15[26],A__15[26],A__15[26],A__15[26],A__15[26],A__15[26],A__15[26],A__15[26],A__15}),
        .CARRYCASCIN(1'b0),
        .CARRYCASCOUT(NLW_p_1_out__15_CARRYCASCOUT_UNCONNECTED),
        .CARRYIN(1'b0),
        .CARRYINSEL({1'b0,1'b0,1'b0}),
        .CARRYOUT(NLW_p_1_out__15_CARRYOUT_UNCONNECTED[3:0]),
        .CEA1(1'b0),
        .CEA2(1'b0),
        .CEAD(1'b0),
        .CEALUMODE(1'b0),
        .CEB1(1'b0),
        .CEB2(DSP_ALU_INST_15),
        .CEC(1'b0),
        .CECARRYIN(1'b0),
        .CECTRL(1'b0),
        .CED(1'b0),
        .CEINMODE(1'b0),
        .CEM(1'b0),
        .CEP(1'b0),
        .CLK(AXI4_Lite_ACLK),
        .D({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .INMODE({1'b0,1'b0,1'b0,1'b0,1'b0}),
        .MULTSIGNIN(1'b0),
        .MULTSIGNOUT(NLW_p_1_out__15_MULTSIGNOUT_UNCONNECTED),
        .OPMODE({1'b0,1'b0,1'b0,\out16[17] ,\out16[17] ,1'b0,1'b1,1'b0,1'b1}),
        .OVERFLOW(NLW_p_1_out__15_OVERFLOW_UNCONNECTED),
        .P({NLW_p_1_out__15_P_UNCONNECTED[47:45],p_1_out__15_n_61,p_1_out__15_n_62,p_1_out__15_n_63,p_1_out__15_n_64,p_1_out__15_n_65,p_1_out__15_n_66,p_1_out__15_n_67,p_1_out__15_n_68,p_1_out__15_n_69,p_1_out__15_n_70,out16,p_1_out__15_n_89,p_1_out__15_n_90,p_1_out__15_n_91,p_1_out__15_n_92,p_1_out__15_n_93,p_1_out__15_n_94,p_1_out__15_n_95,p_1_out__15_n_96,p_1_out__15_n_97,p_1_out__15_n_98,p_1_out__15_n_99,p_1_out__15_n_100,p_1_out__15_n_101,p_1_out__15_n_102,p_1_out__15_n_103,p_1_out__15_n_104,p_1_out__15_n_105}),
        .PATTERNBDETECT(NLW_p_1_out__15_PATTERNBDETECT_UNCONNECTED),
        .PATTERNDETECT(NLW_p_1_out__15_PATTERNDETECT_UNCONNECTED),
        .PCIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .PCOUT(NLW_p_1_out__15_PCOUT_UNCONNECTED[47:0]),
        .RSTA(1'b0),
        .RSTALLCARRYIN(1'b0),
        .RSTALUMODE(1'b0),
        .RSTB(reset),
        .RSTC(1'b0),
        .RSTCTRL(1'b0),
        .RSTD(1'b0),
        .RSTINMODE(1'b0),
        .RSTM(1'b0),
        .RSTP(1'b0),
        .UNDERFLOW(NLW_p_1_out__15_UNDERFLOW_UNCONNECTED),
        .XOROUT(NLW_p_1_out__15_XOROUT_UNCONNECTED[7:0]));
  (* SOFT_HLUTNM = "soft_lutpair248" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__15_i_10
       (.I0(in16[18]),
        .I1(Delay16_out1[18]),
        .I2(adc_trigger),
        .O(A__15[18]));
  (* SOFT_HLUTNM = "soft_lutpair247" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__15_i_11
       (.I0(in16[17]),
        .I1(Delay16_out1[17]),
        .I2(adc_trigger),
        .O(A__15[17]));
  (* SOFT_HLUTNM = "soft_lutpair247" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__15_i_12
       (.I0(in16[16]),
        .I1(Delay16_out1[16]),
        .I2(adc_trigger),
        .O(A__15[16]));
  (* SOFT_HLUTNM = "soft_lutpair246" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__15_i_13
       (.I0(in16[15]),
        .I1(Delay16_out1[15]),
        .I2(adc_trigger),
        .O(A__15[15]));
  (* SOFT_HLUTNM = "soft_lutpair246" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__15_i_14
       (.I0(in16[14]),
        .I1(Delay16_out1[14]),
        .I2(adc_trigger),
        .O(A__15[14]));
  (* SOFT_HLUTNM = "soft_lutpair245" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__15_i_15
       (.I0(in16[13]),
        .I1(Delay16_out1[13]),
        .I2(adc_trigger),
        .O(A__15[13]));
  (* SOFT_HLUTNM = "soft_lutpair245" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__15_i_16
       (.I0(in16[12]),
        .I1(Delay16_out1[12]),
        .I2(adc_trigger),
        .O(A__15[12]));
  (* SOFT_HLUTNM = "soft_lutpair244" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__15_i_17
       (.I0(in16[11]),
        .I1(Delay16_out1[11]),
        .I2(adc_trigger),
        .O(A__15[11]));
  (* SOFT_HLUTNM = "soft_lutpair244" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__15_i_18
       (.I0(in16[10]),
        .I1(Delay16_out1[10]),
        .I2(adc_trigger),
        .O(A__15[10]));
  (* SOFT_HLUTNM = "soft_lutpair243" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__15_i_19
       (.I0(in16[9]),
        .I1(Delay16_out1[9]),
        .I2(adc_trigger),
        .O(A__15[9]));
  (* SOFT_HLUTNM = "soft_lutpair252" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__15_i_2
       (.I0(in16[26]),
        .I1(Delay16_out1[26]),
        .I2(adc_trigger),
        .O(A__15[26]));
  (* SOFT_HLUTNM = "soft_lutpair243" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__15_i_20
       (.I0(in16[8]),
        .I1(Delay16_out1[8]),
        .I2(adc_trigger),
        .O(A__15[8]));
  (* SOFT_HLUTNM = "soft_lutpair242" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__15_i_21
       (.I0(in16[7]),
        .I1(Delay16_out1[7]),
        .I2(adc_trigger),
        .O(A__15[7]));
  (* SOFT_HLUTNM = "soft_lutpair242" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__15_i_22
       (.I0(in16[6]),
        .I1(Delay16_out1[6]),
        .I2(adc_trigger),
        .O(A__15[6]));
  (* SOFT_HLUTNM = "soft_lutpair241" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__15_i_23
       (.I0(in16[5]),
        .I1(Delay16_out1[5]),
        .I2(adc_trigger),
        .O(A__15[5]));
  (* SOFT_HLUTNM = "soft_lutpair241" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__15_i_24
       (.I0(in16[4]),
        .I1(Delay16_out1[4]),
        .I2(adc_trigger),
        .O(A__15[4]));
  (* SOFT_HLUTNM = "soft_lutpair240" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__15_i_25
       (.I0(in16[3]),
        .I1(Delay16_out1[3]),
        .I2(adc_trigger),
        .O(A__15[3]));
  (* SOFT_HLUTNM = "soft_lutpair240" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__15_i_26
       (.I0(in16[2]),
        .I1(Delay16_out1[2]),
        .I2(adc_trigger),
        .O(A__15[2]));
  (* SOFT_HLUTNM = "soft_lutpair239" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__15_i_27
       (.I0(in16[1]),
        .I1(Delay16_out1[1]),
        .I2(adc_trigger),
        .O(A__15[1]));
  (* SOFT_HLUTNM = "soft_lutpair239" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__15_i_28
       (.I0(in16[0]),
        .I1(Delay16_out1[0]),
        .I2(adc_trigger),
        .O(p_1_out__15_i_28_n_0));
  (* SOFT_HLUTNM = "soft_lutpair251" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__15_i_3
       (.I0(in16[25]),
        .I1(Delay16_out1[25]),
        .I2(adc_trigger),
        .O(A__15[25]));
  (* SOFT_HLUTNM = "soft_lutpair251" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__15_i_4
       (.I0(in16[24]),
        .I1(Delay16_out1[24]),
        .I2(adc_trigger),
        .O(A__15[24]));
  (* SOFT_HLUTNM = "soft_lutpair250" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__15_i_5
       (.I0(in16[23]),
        .I1(Delay16_out1[23]),
        .I2(adc_trigger),
        .O(A__15[23]));
  (* SOFT_HLUTNM = "soft_lutpair250" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__15_i_6
       (.I0(in16[22]),
        .I1(Delay16_out1[22]),
        .I2(adc_trigger),
        .O(A__15[22]));
  (* SOFT_HLUTNM = "soft_lutpair249" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__15_i_7
       (.I0(in16[21]),
        .I1(Delay16_out1[21]),
        .I2(adc_trigger),
        .O(A__15[21]));
  (* SOFT_HLUTNM = "soft_lutpair249" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__15_i_8
       (.I0(in16[20]),
        .I1(Delay16_out1[20]),
        .I2(adc_trigger),
        .O(A__15[20]));
  (* SOFT_HLUTNM = "soft_lutpair248" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__15_i_9
       (.I0(in16[19]),
        .I1(Delay16_out1[19]),
        .I2(adc_trigger),
        .O(A__15[19]));
  (* KEEP_HIERARCHY = "yes" *) 
  (* METHODOLOGY_DRC_VIOS = "{SYNTH-11 {cell *THIS*}}" *) 
  DSP48E2 #(
    .ACASCREG(0),
    .ADREG(1),
    .ALUMODEREG(0),
    .AMULTSEL("A"),
    .AREG(0),
    .AUTORESET_PATDET("NO_RESET"),
    .AUTORESET_PRIORITY("RESET"),
    .A_INPUT("DIRECT"),
    .BCASCREG(1),
    .BMULTSEL("B"),
    .BREG(1),
    .B_INPUT("DIRECT"),
    .CARRYINREG(0),
    .CARRYINSELREG(0),
    .CREG(0),
    .DREG(1),
    .INMODEREG(0),
    .MASK(48'h3FFFFFFFFFFF),
    .MREG(0),
    .OPMODEREG(0),
    .PATTERN(48'h000000000000),
    .PREADDINSEL("A"),
    .PREG(0),
    .RND(48'h000000000000),
    .SEL_MASK("MASK"),
    .SEL_PATTERN("PATTERN"),
    .USE_MULT("MULTIPLY"),
    .USE_PATTERN_DETECT("NO_PATDET"),
    .USE_SIMD("ONE48"),
    .USE_WIDEXOR("FALSE"),
    .XORSIMD("XOR24_48_96")) 
    p_1_out__16
       (.A({A__16[26],A__16[26],A__16[26],A__16,p_1_out__16_i_28_n_0}),
        .ACIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .ACOUT(NLW_p_1_out__16_ACOUT_UNCONNECTED[29:0]),
        .ALUMODE({1'b0,1'b0,1'b0,1'b0}),
        .B({1'b0,AXI_pu_conv_in31}),
        .BCIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .BCOUT(NLW_p_1_out__16_BCOUT_UNCONNECTED[17:0]),
        .C({A__16[26],A__16[26],A__16[26],A__16[26],A__16[26],A__16[26],A__16[26],A__16[26],A__16[26],A__16[26],A__16[26],A__16[26],A__16[26],A__16[26],A__16[26],A__16[26],A__16[26],A__16[26],A__16[26],A__16[26],A__16[26],A__16[26],A__16}),
        .CARRYCASCIN(1'b0),
        .CARRYCASCOUT(NLW_p_1_out__16_CARRYCASCOUT_UNCONNECTED),
        .CARRYIN(1'b0),
        .CARRYINSEL({1'b0,1'b0,1'b0}),
        .CARRYOUT(NLW_p_1_out__16_CARRYOUT_UNCONNECTED[3:0]),
        .CEA1(1'b0),
        .CEA2(1'b0),
        .CEAD(1'b0),
        .CEALUMODE(1'b0),
        .CEB1(1'b0),
        .CEB2(DSP_ALU_INST_16),
        .CEC(1'b0),
        .CECARRYIN(1'b0),
        .CECTRL(1'b0),
        .CED(1'b0),
        .CEINMODE(1'b0),
        .CEM(1'b0),
        .CEP(1'b0),
        .CLK(AXI4_Lite_ACLK),
        .D({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .INMODE({1'b0,1'b0,1'b0,1'b0,1'b0}),
        .MULTSIGNIN(1'b0),
        .MULTSIGNOUT(NLW_p_1_out__16_MULTSIGNOUT_UNCONNECTED),
        .OPMODE({1'b0,1'b0,1'b0,\out17[17] ,\out17[17] ,1'b0,1'b1,1'b0,1'b1}),
        .OVERFLOW(NLW_p_1_out__16_OVERFLOW_UNCONNECTED),
        .P({NLW_p_1_out__16_P_UNCONNECTED[47:45],p_1_out__16_n_61,p_1_out__16_n_62,p_1_out__16_n_63,p_1_out__16_n_64,p_1_out__16_n_65,p_1_out__16_n_66,p_1_out__16_n_67,p_1_out__16_n_68,p_1_out__16_n_69,p_1_out__16_n_70,out17,p_1_out__16_n_89,p_1_out__16_n_90,p_1_out__16_n_91,p_1_out__16_n_92,p_1_out__16_n_93,p_1_out__16_n_94,p_1_out__16_n_95,p_1_out__16_n_96,p_1_out__16_n_97,p_1_out__16_n_98,p_1_out__16_n_99,p_1_out__16_n_100,p_1_out__16_n_101,p_1_out__16_n_102,p_1_out__16_n_103,p_1_out__16_n_104,p_1_out__16_n_105}),
        .PATTERNBDETECT(NLW_p_1_out__16_PATTERNBDETECT_UNCONNECTED),
        .PATTERNDETECT(NLW_p_1_out__16_PATTERNDETECT_UNCONNECTED),
        .PCIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .PCOUT(NLW_p_1_out__16_PCOUT_UNCONNECTED[47:0]),
        .RSTA(1'b0),
        .RSTALLCARRYIN(1'b0),
        .RSTALUMODE(1'b0),
        .RSTB(reset),
        .RSTC(1'b0),
        .RSTCTRL(1'b0),
        .RSTD(1'b0),
        .RSTINMODE(1'b0),
        .RSTM(1'b0),
        .RSTP(1'b0),
        .UNDERFLOW(NLW_p_1_out__16_UNDERFLOW_UNCONNECTED),
        .XOROUT(NLW_p_1_out__16_XOROUT_UNCONNECTED[7:0]));
  (* SOFT_HLUTNM = "soft_lutpair261" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__16_i_10
       (.I0(in17[18]),
        .I1(Delay17_out1[18]),
        .I2(adc_trigger),
        .O(A__16[18]));
  (* SOFT_HLUTNM = "soft_lutpair261" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__16_i_11
       (.I0(in17[17]),
        .I1(Delay17_out1[17]),
        .I2(adc_trigger),
        .O(A__16[17]));
  (* SOFT_HLUTNM = "soft_lutpair260" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__16_i_12
       (.I0(in17[16]),
        .I1(Delay17_out1[16]),
        .I2(adc_trigger),
        .O(A__16[16]));
  (* SOFT_HLUTNM = "soft_lutpair260" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__16_i_13
       (.I0(in17[15]),
        .I1(Delay17_out1[15]),
        .I2(adc_trigger),
        .O(A__16[15]));
  (* SOFT_HLUTNM = "soft_lutpair259" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__16_i_14
       (.I0(in17[14]),
        .I1(Delay17_out1[14]),
        .I2(adc_trigger),
        .O(A__16[14]));
  (* SOFT_HLUTNM = "soft_lutpair259" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__16_i_15
       (.I0(in17[13]),
        .I1(Delay17_out1[13]),
        .I2(adc_trigger),
        .O(A__16[13]));
  (* SOFT_HLUTNM = "soft_lutpair258" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__16_i_16
       (.I0(in17[12]),
        .I1(Delay17_out1[12]),
        .I2(adc_trigger),
        .O(A__16[12]));
  (* SOFT_HLUTNM = "soft_lutpair258" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__16_i_17
       (.I0(in17[11]),
        .I1(Delay17_out1[11]),
        .I2(adc_trigger),
        .O(A__16[11]));
  (* SOFT_HLUTNM = "soft_lutpair257" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__16_i_18
       (.I0(in17[10]),
        .I1(Delay17_out1[10]),
        .I2(adc_trigger),
        .O(A__16[10]));
  (* SOFT_HLUTNM = "soft_lutpair257" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__16_i_19
       (.I0(in17[9]),
        .I1(Delay17_out1[9]),
        .I2(adc_trigger),
        .O(A__16[9]));
  (* SOFT_HLUTNM = "soft_lutpair265" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__16_i_2
       (.I0(in17[26]),
        .I1(Delay17_out1[26]),
        .I2(adc_trigger),
        .O(A__16[26]));
  (* SOFT_HLUTNM = "soft_lutpair256" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__16_i_20
       (.I0(in17[8]),
        .I1(Delay17_out1[8]),
        .I2(adc_trigger),
        .O(A__16[8]));
  (* SOFT_HLUTNM = "soft_lutpair256" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__16_i_21
       (.I0(in17[7]),
        .I1(Delay17_out1[7]),
        .I2(adc_trigger),
        .O(A__16[7]));
  (* SOFT_HLUTNM = "soft_lutpair255" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__16_i_22
       (.I0(in17[6]),
        .I1(Delay17_out1[6]),
        .I2(adc_trigger),
        .O(A__16[6]));
  (* SOFT_HLUTNM = "soft_lutpair255" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__16_i_23
       (.I0(in17[5]),
        .I1(Delay17_out1[5]),
        .I2(adc_trigger),
        .O(A__16[5]));
  (* SOFT_HLUTNM = "soft_lutpair254" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__16_i_24
       (.I0(in17[4]),
        .I1(Delay17_out1[4]),
        .I2(adc_trigger),
        .O(A__16[4]));
  (* SOFT_HLUTNM = "soft_lutpair254" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__16_i_25
       (.I0(in17[3]),
        .I1(Delay17_out1[3]),
        .I2(adc_trigger),
        .O(A__16[3]));
  (* SOFT_HLUTNM = "soft_lutpair253" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__16_i_26
       (.I0(in17[2]),
        .I1(Delay17_out1[2]),
        .I2(adc_trigger),
        .O(A__16[2]));
  (* SOFT_HLUTNM = "soft_lutpair253" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__16_i_27
       (.I0(in17[1]),
        .I1(Delay17_out1[1]),
        .I2(adc_trigger),
        .O(A__16[1]));
  (* SOFT_HLUTNM = "soft_lutpair252" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__16_i_28
       (.I0(in17[0]),
        .I1(Delay17_out1[0]),
        .I2(adc_trigger),
        .O(p_1_out__16_i_28_n_0));
  (* SOFT_HLUTNM = "soft_lutpair265" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__16_i_3
       (.I0(in17[25]),
        .I1(Delay17_out1[25]),
        .I2(adc_trigger),
        .O(A__16[25]));
  (* SOFT_HLUTNM = "soft_lutpair264" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__16_i_4
       (.I0(in17[24]),
        .I1(Delay17_out1[24]),
        .I2(adc_trigger),
        .O(A__16[24]));
  (* SOFT_HLUTNM = "soft_lutpair264" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__16_i_5
       (.I0(in17[23]),
        .I1(Delay17_out1[23]),
        .I2(adc_trigger),
        .O(A__16[23]));
  (* SOFT_HLUTNM = "soft_lutpair263" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__16_i_6
       (.I0(in17[22]),
        .I1(Delay17_out1[22]),
        .I2(adc_trigger),
        .O(A__16[22]));
  (* SOFT_HLUTNM = "soft_lutpair263" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__16_i_7
       (.I0(in17[21]),
        .I1(Delay17_out1[21]),
        .I2(adc_trigger),
        .O(A__16[21]));
  (* SOFT_HLUTNM = "soft_lutpair262" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__16_i_8
       (.I0(in17[20]),
        .I1(Delay17_out1[20]),
        .I2(adc_trigger),
        .O(A__16[20]));
  (* SOFT_HLUTNM = "soft_lutpair262" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__16_i_9
       (.I0(in17[19]),
        .I1(Delay17_out1[19]),
        .I2(adc_trigger),
        .O(A__16[19]));
  (* KEEP_HIERARCHY = "yes" *) 
  (* METHODOLOGY_DRC_VIOS = "{SYNTH-11 {cell *THIS*}}" *) 
  DSP48E2 #(
    .ACASCREG(0),
    .ADREG(1),
    .ALUMODEREG(0),
    .AMULTSEL("A"),
    .AREG(0),
    .AUTORESET_PATDET("NO_RESET"),
    .AUTORESET_PRIORITY("RESET"),
    .A_INPUT("DIRECT"),
    .BCASCREG(1),
    .BMULTSEL("B"),
    .BREG(1),
    .B_INPUT("DIRECT"),
    .CARRYINREG(0),
    .CARRYINSELREG(0),
    .CREG(0),
    .DREG(1),
    .INMODEREG(0),
    .MASK(48'h3FFFFFFFFFFF),
    .MREG(0),
    .OPMODEREG(0),
    .PATTERN(48'h000000000000),
    .PREADDINSEL("A"),
    .PREG(0),
    .RND(48'h000000000000),
    .SEL_MASK("MASK"),
    .SEL_PATTERN("PATTERN"),
    .USE_MULT("MULTIPLY"),
    .USE_PATTERN_DETECT("NO_PATDET"),
    .USE_SIMD("ONE48"),
    .USE_WIDEXOR("FALSE"),
    .XORSIMD("XOR24_48_96")) 
    p_1_out__17
       (.A({A__17[26],A__17[26],A__17[26],A__17,p_1_out__17_i_28_n_0}),
        .ACIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .ACOUT(NLW_p_1_out__17_ACOUT_UNCONNECTED[29:0]),
        .ALUMODE({1'b0,1'b0,1'b0,1'b0}),
        .B({1'b0,AXI_pu_conv_in31}),
        .BCIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .BCOUT(NLW_p_1_out__17_BCOUT_UNCONNECTED[17:0]),
        .C({A__17[26],A__17[26],A__17[26],A__17[26],A__17[26],A__17[26],A__17[26],A__17[26],A__17[26],A__17[26],A__17[26],A__17[26],A__17[26],A__17[26],A__17[26],A__17[26],A__17[26],A__17[26],A__17[26],A__17[26],A__17[26],A__17[26],A__17}),
        .CARRYCASCIN(1'b0),
        .CARRYCASCOUT(NLW_p_1_out__17_CARRYCASCOUT_UNCONNECTED),
        .CARRYIN(1'b0),
        .CARRYINSEL({1'b0,1'b0,1'b0}),
        .CARRYOUT(NLW_p_1_out__17_CARRYOUT_UNCONNECTED[3:0]),
        .CEA1(1'b0),
        .CEA2(1'b0),
        .CEAD(1'b0),
        .CEALUMODE(1'b0),
        .CEB1(1'b0),
        .CEB2(DSP_ALU_INST_17),
        .CEC(1'b0),
        .CECARRYIN(1'b0),
        .CECTRL(1'b0),
        .CED(1'b0),
        .CEINMODE(1'b0),
        .CEM(1'b0),
        .CEP(1'b0),
        .CLK(AXI4_Lite_ACLK),
        .D({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .INMODE({1'b0,1'b0,1'b0,1'b0,1'b0}),
        .MULTSIGNIN(1'b0),
        .MULTSIGNOUT(NLW_p_1_out__17_MULTSIGNOUT_UNCONNECTED),
        .OPMODE({1'b0,1'b0,1'b0,\out18[17] ,\out18[17] ,1'b0,1'b1,1'b0,1'b1}),
        .OVERFLOW(NLW_p_1_out__17_OVERFLOW_UNCONNECTED),
        .P({NLW_p_1_out__17_P_UNCONNECTED[47:45],p_1_out__17_n_61,p_1_out__17_n_62,p_1_out__17_n_63,p_1_out__17_n_64,p_1_out__17_n_65,p_1_out__17_n_66,p_1_out__17_n_67,p_1_out__17_n_68,p_1_out__17_n_69,p_1_out__17_n_70,out18,p_1_out__17_n_89,p_1_out__17_n_90,p_1_out__17_n_91,p_1_out__17_n_92,p_1_out__17_n_93,p_1_out__17_n_94,p_1_out__17_n_95,p_1_out__17_n_96,p_1_out__17_n_97,p_1_out__17_n_98,p_1_out__17_n_99,p_1_out__17_n_100,p_1_out__17_n_101,p_1_out__17_n_102,p_1_out__17_n_103,p_1_out__17_n_104,p_1_out__17_n_105}),
        .PATTERNBDETECT(NLW_p_1_out__17_PATTERNBDETECT_UNCONNECTED),
        .PATTERNDETECT(NLW_p_1_out__17_PATTERNDETECT_UNCONNECTED),
        .PCIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .PCOUT(NLW_p_1_out__17_PCOUT_UNCONNECTED[47:0]),
        .RSTA(1'b0),
        .RSTALLCARRYIN(1'b0),
        .RSTALUMODE(1'b0),
        .RSTB(reset),
        .RSTC(1'b0),
        .RSTCTRL(1'b0),
        .RSTD(1'b0),
        .RSTINMODE(1'b0),
        .RSTM(1'b0),
        .RSTP(1'b0),
        .UNDERFLOW(NLW_p_1_out__17_UNDERFLOW_UNCONNECTED),
        .XOROUT(NLW_p_1_out__17_XOROUT_UNCONNECTED[7:0]));
  (* SOFT_HLUTNM = "soft_lutpair275" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__17_i_10
       (.I0(in18[18]),
        .I1(Delay18_out1[18]),
        .I2(adc_trigger),
        .O(A__17[18]));
  (* SOFT_HLUTNM = "soft_lutpair274" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__17_i_11
       (.I0(in18[17]),
        .I1(Delay18_out1[17]),
        .I2(adc_trigger),
        .O(A__17[17]));
  (* SOFT_HLUTNM = "soft_lutpair274" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__17_i_12
       (.I0(in18[16]),
        .I1(Delay18_out1[16]),
        .I2(adc_trigger),
        .O(A__17[16]));
  (* SOFT_HLUTNM = "soft_lutpair273" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__17_i_13
       (.I0(in18[15]),
        .I1(Delay18_out1[15]),
        .I2(adc_trigger),
        .O(A__17[15]));
  (* SOFT_HLUTNM = "soft_lutpair273" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__17_i_14
       (.I0(in18[14]),
        .I1(Delay18_out1[14]),
        .I2(adc_trigger),
        .O(A__17[14]));
  (* SOFT_HLUTNM = "soft_lutpair272" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__17_i_15
       (.I0(in18[13]),
        .I1(Delay18_out1[13]),
        .I2(adc_trigger),
        .O(A__17[13]));
  (* SOFT_HLUTNM = "soft_lutpair272" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__17_i_16
       (.I0(in18[12]),
        .I1(Delay18_out1[12]),
        .I2(adc_trigger),
        .O(A__17[12]));
  (* SOFT_HLUTNM = "soft_lutpair271" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__17_i_17
       (.I0(in18[11]),
        .I1(Delay18_out1[11]),
        .I2(adc_trigger),
        .O(A__17[11]));
  (* SOFT_HLUTNM = "soft_lutpair271" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__17_i_18
       (.I0(in18[10]),
        .I1(Delay18_out1[10]),
        .I2(adc_trigger),
        .O(A__17[10]));
  (* SOFT_HLUTNM = "soft_lutpair270" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__17_i_19
       (.I0(in18[9]),
        .I1(Delay18_out1[9]),
        .I2(adc_trigger),
        .O(A__17[9]));
  (* SOFT_HLUTNM = "soft_lutpair279" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__17_i_2
       (.I0(in18[26]),
        .I1(Delay18_out1[26]),
        .I2(adc_trigger),
        .O(A__17[26]));
  (* SOFT_HLUTNM = "soft_lutpair270" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__17_i_20
       (.I0(in18[8]),
        .I1(Delay18_out1[8]),
        .I2(adc_trigger),
        .O(A__17[8]));
  (* SOFT_HLUTNM = "soft_lutpair269" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__17_i_21
       (.I0(in18[7]),
        .I1(Delay18_out1[7]),
        .I2(adc_trigger),
        .O(A__17[7]));
  (* SOFT_HLUTNM = "soft_lutpair269" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__17_i_22
       (.I0(in18[6]),
        .I1(Delay18_out1[6]),
        .I2(adc_trigger),
        .O(A__17[6]));
  (* SOFT_HLUTNM = "soft_lutpair268" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__17_i_23
       (.I0(in18[5]),
        .I1(Delay18_out1[5]),
        .I2(adc_trigger),
        .O(A__17[5]));
  (* SOFT_HLUTNM = "soft_lutpair268" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__17_i_24
       (.I0(in18[4]),
        .I1(Delay18_out1[4]),
        .I2(adc_trigger),
        .O(A__17[4]));
  (* SOFT_HLUTNM = "soft_lutpair267" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__17_i_25
       (.I0(in18[3]),
        .I1(Delay18_out1[3]),
        .I2(adc_trigger),
        .O(A__17[3]));
  (* SOFT_HLUTNM = "soft_lutpair267" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__17_i_26
       (.I0(in18[2]),
        .I1(Delay18_out1[2]),
        .I2(adc_trigger),
        .O(A__17[2]));
  (* SOFT_HLUTNM = "soft_lutpair266" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__17_i_27
       (.I0(in18[1]),
        .I1(Delay18_out1[1]),
        .I2(adc_trigger),
        .O(A__17[1]));
  (* SOFT_HLUTNM = "soft_lutpair266" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__17_i_28
       (.I0(in18[0]),
        .I1(Delay18_out1[0]),
        .I2(adc_trigger),
        .O(p_1_out__17_i_28_n_0));
  (* SOFT_HLUTNM = "soft_lutpair278" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__17_i_3
       (.I0(in18[25]),
        .I1(Delay18_out1[25]),
        .I2(adc_trigger),
        .O(A__17[25]));
  (* SOFT_HLUTNM = "soft_lutpair278" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__17_i_4
       (.I0(in18[24]),
        .I1(Delay18_out1[24]),
        .I2(adc_trigger),
        .O(A__17[24]));
  (* SOFT_HLUTNM = "soft_lutpair277" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__17_i_5
       (.I0(in18[23]),
        .I1(Delay18_out1[23]),
        .I2(adc_trigger),
        .O(A__17[23]));
  (* SOFT_HLUTNM = "soft_lutpair277" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__17_i_6
       (.I0(in18[22]),
        .I1(Delay18_out1[22]),
        .I2(adc_trigger),
        .O(A__17[22]));
  (* SOFT_HLUTNM = "soft_lutpair276" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__17_i_7
       (.I0(in18[21]),
        .I1(Delay18_out1[21]),
        .I2(adc_trigger),
        .O(A__17[21]));
  (* SOFT_HLUTNM = "soft_lutpair276" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__17_i_8
       (.I0(in18[20]),
        .I1(Delay18_out1[20]),
        .I2(adc_trigger),
        .O(A__17[20]));
  (* SOFT_HLUTNM = "soft_lutpair275" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__17_i_9
       (.I0(in18[19]),
        .I1(Delay18_out1[19]),
        .I2(adc_trigger),
        .O(A__17[19]));
  (* KEEP_HIERARCHY = "yes" *) 
  (* METHODOLOGY_DRC_VIOS = "{SYNTH-11 {cell *THIS*}}" *) 
  DSP48E2 #(
    .ACASCREG(0),
    .ADREG(1),
    .ALUMODEREG(0),
    .AMULTSEL("A"),
    .AREG(0),
    .AUTORESET_PATDET("NO_RESET"),
    .AUTORESET_PRIORITY("RESET"),
    .A_INPUT("DIRECT"),
    .BCASCREG(1),
    .BMULTSEL("B"),
    .BREG(1),
    .B_INPUT("DIRECT"),
    .CARRYINREG(0),
    .CARRYINSELREG(0),
    .CREG(0),
    .DREG(1),
    .INMODEREG(0),
    .MASK(48'h3FFFFFFFFFFF),
    .MREG(0),
    .OPMODEREG(0),
    .PATTERN(48'h000000000000),
    .PREADDINSEL("A"),
    .PREG(0),
    .RND(48'h000000000000),
    .SEL_MASK("MASK"),
    .SEL_PATTERN("PATTERN"),
    .USE_MULT("MULTIPLY"),
    .USE_PATTERN_DETECT("NO_PATDET"),
    .USE_SIMD("ONE48"),
    .USE_WIDEXOR("FALSE"),
    .XORSIMD("XOR24_48_96")) 
    p_1_out__18
       (.A({A__18[26],A__18[26],A__18[26],A__18,p_1_out__18_i_28_n_0}),
        .ACIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .ACOUT(NLW_p_1_out__18_ACOUT_UNCONNECTED[29:0]),
        .ALUMODE({1'b0,1'b0,1'b0,1'b0}),
        .B({1'b0,AXI_pu_conv_in31}),
        .BCIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .BCOUT(NLW_p_1_out__18_BCOUT_UNCONNECTED[17:0]),
        .C({A__18[26],A__18[26],A__18[26],A__18[26],A__18[26],A__18[26],A__18[26],A__18[26],A__18[26],A__18[26],A__18[26],A__18[26],A__18[26],A__18[26],A__18[26],A__18[26],A__18[26],A__18[26],A__18[26],A__18[26],A__18[26],A__18[26],A__18}),
        .CARRYCASCIN(1'b0),
        .CARRYCASCOUT(NLW_p_1_out__18_CARRYCASCOUT_UNCONNECTED),
        .CARRYIN(1'b0),
        .CARRYINSEL({1'b0,1'b0,1'b0}),
        .CARRYOUT(NLW_p_1_out__18_CARRYOUT_UNCONNECTED[3:0]),
        .CEA1(1'b0),
        .CEA2(1'b0),
        .CEAD(1'b0),
        .CEALUMODE(1'b0),
        .CEB1(1'b0),
        .CEB2(DSP_ALU_INST_18),
        .CEC(1'b0),
        .CECARRYIN(1'b0),
        .CECTRL(1'b0),
        .CED(1'b0),
        .CEINMODE(1'b0),
        .CEM(1'b0),
        .CEP(1'b0),
        .CLK(AXI4_Lite_ACLK),
        .D({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .INMODE({1'b0,1'b0,1'b0,1'b0,1'b0}),
        .MULTSIGNIN(1'b0),
        .MULTSIGNOUT(NLW_p_1_out__18_MULTSIGNOUT_UNCONNECTED),
        .OPMODE({1'b0,1'b0,1'b0,\out19[17] ,\out19[17] ,1'b0,1'b1,1'b0,1'b1}),
        .OVERFLOW(NLW_p_1_out__18_OVERFLOW_UNCONNECTED),
        .P({NLW_p_1_out__18_P_UNCONNECTED[47:45],p_1_out__18_n_61,p_1_out__18_n_62,p_1_out__18_n_63,p_1_out__18_n_64,p_1_out__18_n_65,p_1_out__18_n_66,p_1_out__18_n_67,p_1_out__18_n_68,p_1_out__18_n_69,p_1_out__18_n_70,out19,p_1_out__18_n_89,p_1_out__18_n_90,p_1_out__18_n_91,p_1_out__18_n_92,p_1_out__18_n_93,p_1_out__18_n_94,p_1_out__18_n_95,p_1_out__18_n_96,p_1_out__18_n_97,p_1_out__18_n_98,p_1_out__18_n_99,p_1_out__18_n_100,p_1_out__18_n_101,p_1_out__18_n_102,p_1_out__18_n_103,p_1_out__18_n_104,p_1_out__18_n_105}),
        .PATTERNBDETECT(NLW_p_1_out__18_PATTERNBDETECT_UNCONNECTED),
        .PATTERNDETECT(NLW_p_1_out__18_PATTERNDETECT_UNCONNECTED),
        .PCIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .PCOUT(NLW_p_1_out__18_PCOUT_UNCONNECTED[47:0]),
        .RSTA(1'b0),
        .RSTALLCARRYIN(1'b0),
        .RSTALUMODE(1'b0),
        .RSTB(reset),
        .RSTC(1'b0),
        .RSTCTRL(1'b0),
        .RSTD(1'b0),
        .RSTINMODE(1'b0),
        .RSTM(1'b0),
        .RSTP(1'b0),
        .UNDERFLOW(NLW_p_1_out__18_UNDERFLOW_UNCONNECTED),
        .XOROUT(NLW_p_1_out__18_XOROUT_UNCONNECTED[7:0]));
  (* SOFT_HLUTNM = "soft_lutpair288" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__18_i_10
       (.I0(in19[18]),
        .I1(Delay19_out1[18]),
        .I2(adc_trigger),
        .O(A__18[18]));
  (* SOFT_HLUTNM = "soft_lutpair288" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__18_i_11
       (.I0(in19[17]),
        .I1(Delay19_out1[17]),
        .I2(adc_trigger),
        .O(A__18[17]));
  (* SOFT_HLUTNM = "soft_lutpair287" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__18_i_12
       (.I0(in19[16]),
        .I1(Delay19_out1[16]),
        .I2(adc_trigger),
        .O(A__18[16]));
  (* SOFT_HLUTNM = "soft_lutpair287" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__18_i_13
       (.I0(in19[15]),
        .I1(Delay19_out1[15]),
        .I2(adc_trigger),
        .O(A__18[15]));
  (* SOFT_HLUTNM = "soft_lutpair286" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__18_i_14
       (.I0(in19[14]),
        .I1(Delay19_out1[14]),
        .I2(adc_trigger),
        .O(A__18[14]));
  (* SOFT_HLUTNM = "soft_lutpair286" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__18_i_15
       (.I0(in19[13]),
        .I1(Delay19_out1[13]),
        .I2(adc_trigger),
        .O(A__18[13]));
  (* SOFT_HLUTNM = "soft_lutpair285" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__18_i_16
       (.I0(in19[12]),
        .I1(Delay19_out1[12]),
        .I2(adc_trigger),
        .O(A__18[12]));
  (* SOFT_HLUTNM = "soft_lutpair285" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__18_i_17
       (.I0(in19[11]),
        .I1(Delay19_out1[11]),
        .I2(adc_trigger),
        .O(A__18[11]));
  (* SOFT_HLUTNM = "soft_lutpair284" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__18_i_18
       (.I0(in19[10]),
        .I1(Delay19_out1[10]),
        .I2(adc_trigger),
        .O(A__18[10]));
  (* SOFT_HLUTNM = "soft_lutpair284" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__18_i_19
       (.I0(in19[9]),
        .I1(Delay19_out1[9]),
        .I2(adc_trigger),
        .O(A__18[9]));
  (* SOFT_HLUTNM = "soft_lutpair292" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__18_i_2
       (.I0(in19[26]),
        .I1(Delay19_out1[26]),
        .I2(adc_trigger),
        .O(A__18[26]));
  (* SOFT_HLUTNM = "soft_lutpair283" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__18_i_20
       (.I0(in19[8]),
        .I1(Delay19_out1[8]),
        .I2(adc_trigger),
        .O(A__18[8]));
  (* SOFT_HLUTNM = "soft_lutpair283" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__18_i_21
       (.I0(in19[7]),
        .I1(Delay19_out1[7]),
        .I2(adc_trigger),
        .O(A__18[7]));
  (* SOFT_HLUTNM = "soft_lutpair282" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__18_i_22
       (.I0(in19[6]),
        .I1(Delay19_out1[6]),
        .I2(adc_trigger),
        .O(A__18[6]));
  (* SOFT_HLUTNM = "soft_lutpair282" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__18_i_23
       (.I0(in19[5]),
        .I1(Delay19_out1[5]),
        .I2(adc_trigger),
        .O(A__18[5]));
  (* SOFT_HLUTNM = "soft_lutpair281" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__18_i_24
       (.I0(in19[4]),
        .I1(Delay19_out1[4]),
        .I2(adc_trigger),
        .O(A__18[4]));
  (* SOFT_HLUTNM = "soft_lutpair281" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__18_i_25
       (.I0(in19[3]),
        .I1(Delay19_out1[3]),
        .I2(adc_trigger),
        .O(A__18[3]));
  (* SOFT_HLUTNM = "soft_lutpair280" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__18_i_26
       (.I0(in19[2]),
        .I1(Delay19_out1[2]),
        .I2(adc_trigger),
        .O(A__18[2]));
  (* SOFT_HLUTNM = "soft_lutpair280" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__18_i_27
       (.I0(in19[1]),
        .I1(Delay19_out1[1]),
        .I2(adc_trigger),
        .O(A__18[1]));
  (* SOFT_HLUTNM = "soft_lutpair279" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__18_i_28
       (.I0(in19[0]),
        .I1(Delay19_out1[0]),
        .I2(adc_trigger),
        .O(p_1_out__18_i_28_n_0));
  (* SOFT_HLUTNM = "soft_lutpair292" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__18_i_3
       (.I0(in19[25]),
        .I1(Delay19_out1[25]),
        .I2(adc_trigger),
        .O(A__18[25]));
  (* SOFT_HLUTNM = "soft_lutpair291" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__18_i_4
       (.I0(in19[24]),
        .I1(Delay19_out1[24]),
        .I2(adc_trigger),
        .O(A__18[24]));
  (* SOFT_HLUTNM = "soft_lutpair291" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__18_i_5
       (.I0(in19[23]),
        .I1(Delay19_out1[23]),
        .I2(adc_trigger),
        .O(A__18[23]));
  (* SOFT_HLUTNM = "soft_lutpair290" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__18_i_6
       (.I0(in19[22]),
        .I1(Delay19_out1[22]),
        .I2(adc_trigger),
        .O(A__18[22]));
  (* SOFT_HLUTNM = "soft_lutpair290" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__18_i_7
       (.I0(in19[21]),
        .I1(Delay19_out1[21]),
        .I2(adc_trigger),
        .O(A__18[21]));
  (* SOFT_HLUTNM = "soft_lutpair289" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__18_i_8
       (.I0(in19[20]),
        .I1(Delay19_out1[20]),
        .I2(adc_trigger),
        .O(A__18[20]));
  (* SOFT_HLUTNM = "soft_lutpair289" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__18_i_9
       (.I0(in19[19]),
        .I1(Delay19_out1[19]),
        .I2(adc_trigger),
        .O(A__18[19]));
  (* KEEP_HIERARCHY = "yes" *) 
  (* METHODOLOGY_DRC_VIOS = "{SYNTH-11 {cell *THIS*}}" *) 
  DSP48E2 #(
    .ACASCREG(0),
    .ADREG(1),
    .ALUMODEREG(0),
    .AMULTSEL("A"),
    .AREG(0),
    .AUTORESET_PATDET("NO_RESET"),
    .AUTORESET_PRIORITY("RESET"),
    .A_INPUT("DIRECT"),
    .BCASCREG(1),
    .BMULTSEL("B"),
    .BREG(1),
    .B_INPUT("DIRECT"),
    .CARRYINREG(0),
    .CARRYINSELREG(0),
    .CREG(0),
    .DREG(1),
    .INMODEREG(0),
    .MASK(48'h3FFFFFFFFFFF),
    .MREG(0),
    .OPMODEREG(0),
    .PATTERN(48'h000000000000),
    .PREADDINSEL("A"),
    .PREG(0),
    .RND(48'h000000000000),
    .SEL_MASK("MASK"),
    .SEL_PATTERN("PATTERN"),
    .USE_MULT("MULTIPLY"),
    .USE_PATTERN_DETECT("NO_PATDET"),
    .USE_SIMD("ONE48"),
    .USE_WIDEXOR("FALSE"),
    .XORSIMD("XOR24_48_96")) 
    p_1_out__19
       (.A({A__19[26],A__19[26],A__19[26],A__19,p_1_out__19_i_28_n_0}),
        .ACIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .ACOUT(NLW_p_1_out__19_ACOUT_UNCONNECTED[29:0]),
        .ALUMODE({1'b0,1'b0,1'b0,1'b0}),
        .B({1'b0,AXI_pu_conv_in31}),
        .BCIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .BCOUT(NLW_p_1_out__19_BCOUT_UNCONNECTED[17:0]),
        .C({A__19[26],A__19[26],A__19[26],A__19[26],A__19[26],A__19[26],A__19[26],A__19[26],A__19[26],A__19[26],A__19[26],A__19[26],A__19[26],A__19[26],A__19[26],A__19[26],A__19[26],A__19[26],A__19[26],A__19[26],A__19[26],A__19[26],A__19}),
        .CARRYCASCIN(1'b0),
        .CARRYCASCOUT(NLW_p_1_out__19_CARRYCASCOUT_UNCONNECTED),
        .CARRYIN(1'b0),
        .CARRYINSEL({1'b0,1'b0,1'b0}),
        .CARRYOUT(NLW_p_1_out__19_CARRYOUT_UNCONNECTED[3:0]),
        .CEA1(1'b0),
        .CEA2(1'b0),
        .CEAD(1'b0),
        .CEALUMODE(1'b0),
        .CEB1(1'b0),
        .CEB2(DSP_ALU_INST_19),
        .CEC(1'b0),
        .CECARRYIN(1'b0),
        .CECTRL(1'b0),
        .CED(1'b0),
        .CEINMODE(1'b0),
        .CEM(1'b0),
        .CEP(1'b0),
        .CLK(AXI4_Lite_ACLK),
        .D({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .INMODE({1'b0,1'b0,1'b0,1'b0,1'b0}),
        .MULTSIGNIN(1'b0),
        .MULTSIGNOUT(NLW_p_1_out__19_MULTSIGNOUT_UNCONNECTED),
        .OPMODE({1'b0,1'b0,1'b0,\out20[17] ,\out20[17] ,1'b0,1'b1,1'b0,1'b1}),
        .OVERFLOW(NLW_p_1_out__19_OVERFLOW_UNCONNECTED),
        .P({NLW_p_1_out__19_P_UNCONNECTED[47:45],p_1_out__19_n_61,p_1_out__19_n_62,p_1_out__19_n_63,p_1_out__19_n_64,p_1_out__19_n_65,p_1_out__19_n_66,p_1_out__19_n_67,p_1_out__19_n_68,p_1_out__19_n_69,p_1_out__19_n_70,out20,p_1_out__19_n_89,p_1_out__19_n_90,p_1_out__19_n_91,p_1_out__19_n_92,p_1_out__19_n_93,p_1_out__19_n_94,p_1_out__19_n_95,p_1_out__19_n_96,p_1_out__19_n_97,p_1_out__19_n_98,p_1_out__19_n_99,p_1_out__19_n_100,p_1_out__19_n_101,p_1_out__19_n_102,p_1_out__19_n_103,p_1_out__19_n_104,p_1_out__19_n_105}),
        .PATTERNBDETECT(NLW_p_1_out__19_PATTERNBDETECT_UNCONNECTED),
        .PATTERNDETECT(NLW_p_1_out__19_PATTERNDETECT_UNCONNECTED),
        .PCIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .PCOUT(NLW_p_1_out__19_PCOUT_UNCONNECTED[47:0]),
        .RSTA(1'b0),
        .RSTALLCARRYIN(1'b0),
        .RSTALUMODE(1'b0),
        .RSTB(reset),
        .RSTC(1'b0),
        .RSTCTRL(1'b0),
        .RSTD(1'b0),
        .RSTINMODE(1'b0),
        .RSTM(1'b0),
        .RSTP(1'b0),
        .UNDERFLOW(NLW_p_1_out__19_UNDERFLOW_UNCONNECTED),
        .XOROUT(NLW_p_1_out__19_XOROUT_UNCONNECTED[7:0]));
  (* SOFT_HLUTNM = "soft_lutpair302" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__19_i_10
       (.I0(in20[18]),
        .I1(Delay20_out1[18]),
        .I2(adc_trigger),
        .O(A__19[18]));
  (* SOFT_HLUTNM = "soft_lutpair301" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__19_i_11
       (.I0(in20[17]),
        .I1(Delay20_out1[17]),
        .I2(adc_trigger),
        .O(A__19[17]));
  (* SOFT_HLUTNM = "soft_lutpair301" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__19_i_12
       (.I0(in20[16]),
        .I1(Delay20_out1[16]),
        .I2(adc_trigger),
        .O(A__19[16]));
  (* SOFT_HLUTNM = "soft_lutpair300" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__19_i_13
       (.I0(in20[15]),
        .I1(Delay20_out1[15]),
        .I2(adc_trigger),
        .O(A__19[15]));
  (* SOFT_HLUTNM = "soft_lutpair300" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__19_i_14
       (.I0(in20[14]),
        .I1(Delay20_out1[14]),
        .I2(adc_trigger),
        .O(A__19[14]));
  (* SOFT_HLUTNM = "soft_lutpair299" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__19_i_15
       (.I0(in20[13]),
        .I1(Delay20_out1[13]),
        .I2(adc_trigger),
        .O(A__19[13]));
  (* SOFT_HLUTNM = "soft_lutpair299" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__19_i_16
       (.I0(in20[12]),
        .I1(Delay20_out1[12]),
        .I2(adc_trigger),
        .O(A__19[12]));
  (* SOFT_HLUTNM = "soft_lutpair298" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__19_i_17
       (.I0(in20[11]),
        .I1(Delay20_out1[11]),
        .I2(adc_trigger),
        .O(A__19[11]));
  (* SOFT_HLUTNM = "soft_lutpair298" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__19_i_18
       (.I0(in20[10]),
        .I1(Delay20_out1[10]),
        .I2(adc_trigger),
        .O(A__19[10]));
  (* SOFT_HLUTNM = "soft_lutpair297" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__19_i_19
       (.I0(in20[9]),
        .I1(Delay20_out1[9]),
        .I2(adc_trigger),
        .O(A__19[9]));
  (* SOFT_HLUTNM = "soft_lutpair306" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__19_i_2
       (.I0(in20[26]),
        .I1(Delay20_out1[26]),
        .I2(adc_trigger),
        .O(A__19[26]));
  (* SOFT_HLUTNM = "soft_lutpair297" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__19_i_20
       (.I0(in20[8]),
        .I1(Delay20_out1[8]),
        .I2(adc_trigger),
        .O(A__19[8]));
  (* SOFT_HLUTNM = "soft_lutpair296" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__19_i_21
       (.I0(in20[7]),
        .I1(Delay20_out1[7]),
        .I2(adc_trigger),
        .O(A__19[7]));
  (* SOFT_HLUTNM = "soft_lutpair296" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__19_i_22
       (.I0(in20[6]),
        .I1(Delay20_out1[6]),
        .I2(adc_trigger),
        .O(A__19[6]));
  (* SOFT_HLUTNM = "soft_lutpair295" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__19_i_23
       (.I0(in20[5]),
        .I1(Delay20_out1[5]),
        .I2(adc_trigger),
        .O(A__19[5]));
  (* SOFT_HLUTNM = "soft_lutpair295" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__19_i_24
       (.I0(in20[4]),
        .I1(Delay20_out1[4]),
        .I2(adc_trigger),
        .O(A__19[4]));
  (* SOFT_HLUTNM = "soft_lutpair294" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__19_i_25
       (.I0(in20[3]),
        .I1(Delay20_out1[3]),
        .I2(adc_trigger),
        .O(A__19[3]));
  (* SOFT_HLUTNM = "soft_lutpair294" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__19_i_26
       (.I0(in20[2]),
        .I1(Delay20_out1[2]),
        .I2(adc_trigger),
        .O(A__19[2]));
  (* SOFT_HLUTNM = "soft_lutpair293" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__19_i_27
       (.I0(in20[1]),
        .I1(Delay20_out1[1]),
        .I2(adc_trigger),
        .O(A__19[1]));
  (* SOFT_HLUTNM = "soft_lutpair293" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__19_i_28
       (.I0(in20[0]),
        .I1(Delay20_out1[0]),
        .I2(adc_trigger),
        .O(p_1_out__19_i_28_n_0));
  (* SOFT_HLUTNM = "soft_lutpair305" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__19_i_3
       (.I0(in20[25]),
        .I1(Delay20_out1[25]),
        .I2(adc_trigger),
        .O(A__19[25]));
  (* SOFT_HLUTNM = "soft_lutpair305" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__19_i_4
       (.I0(in20[24]),
        .I1(Delay20_out1[24]),
        .I2(adc_trigger),
        .O(A__19[24]));
  (* SOFT_HLUTNM = "soft_lutpair304" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__19_i_5
       (.I0(in20[23]),
        .I1(Delay20_out1[23]),
        .I2(adc_trigger),
        .O(A__19[23]));
  (* SOFT_HLUTNM = "soft_lutpair304" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__19_i_6
       (.I0(in20[22]),
        .I1(Delay20_out1[22]),
        .I2(adc_trigger),
        .O(A__19[22]));
  (* SOFT_HLUTNM = "soft_lutpair303" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__19_i_7
       (.I0(in20[21]),
        .I1(Delay20_out1[21]),
        .I2(adc_trigger),
        .O(A__19[21]));
  (* SOFT_HLUTNM = "soft_lutpair303" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__19_i_8
       (.I0(in20[20]),
        .I1(Delay20_out1[20]),
        .I2(adc_trigger),
        .O(A__19[20]));
  (* SOFT_HLUTNM = "soft_lutpair302" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__19_i_9
       (.I0(in20[19]),
        .I1(Delay20_out1[19]),
        .I2(adc_trigger),
        .O(A__19[19]));
  (* SOFT_HLUTNM = "soft_lutpair59" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__1_i_10
       (.I0(in2[18]),
        .I1(Delay2_out1[18]),
        .I2(adc_trigger),
        .O(A__1[18]));
  (* SOFT_HLUTNM = "soft_lutpair58" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__1_i_11
       (.I0(in2[17]),
        .I1(Delay2_out1[17]),
        .I2(adc_trigger),
        .O(A__1[17]));
  (* SOFT_HLUTNM = "soft_lutpair58" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__1_i_12
       (.I0(in2[16]),
        .I1(Delay2_out1[16]),
        .I2(adc_trigger),
        .O(A__1[16]));
  (* SOFT_HLUTNM = "soft_lutpair57" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__1_i_13
       (.I0(in2[15]),
        .I1(Delay2_out1[15]),
        .I2(adc_trigger),
        .O(A__1[15]));
  (* SOFT_HLUTNM = "soft_lutpair57" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__1_i_14
       (.I0(in2[14]),
        .I1(Delay2_out1[14]),
        .I2(adc_trigger),
        .O(A__1[14]));
  (* SOFT_HLUTNM = "soft_lutpair56" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__1_i_15
       (.I0(in2[13]),
        .I1(Delay2_out1[13]),
        .I2(adc_trigger),
        .O(A__1[13]));
  (* SOFT_HLUTNM = "soft_lutpair56" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__1_i_16
       (.I0(in2[12]),
        .I1(Delay2_out1[12]),
        .I2(adc_trigger),
        .O(A__1[12]));
  (* SOFT_HLUTNM = "soft_lutpair55" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__1_i_17
       (.I0(in2[11]),
        .I1(Delay2_out1[11]),
        .I2(adc_trigger),
        .O(A__1[11]));
  (* SOFT_HLUTNM = "soft_lutpair55" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__1_i_18
       (.I0(in2[10]),
        .I1(Delay2_out1[10]),
        .I2(adc_trigger),
        .O(A__1[10]));
  (* SOFT_HLUTNM = "soft_lutpair54" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__1_i_19
       (.I0(in2[9]),
        .I1(Delay2_out1[9]),
        .I2(adc_trigger),
        .O(A__1[9]));
  (* SOFT_HLUTNM = "soft_lutpair63" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__1_i_2
       (.I0(in2[26]),
        .I1(Delay2_out1[26]),
        .I2(adc_trigger),
        .O(A__1[26]));
  (* SOFT_HLUTNM = "soft_lutpair54" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__1_i_20
       (.I0(in2[8]),
        .I1(Delay2_out1[8]),
        .I2(adc_trigger),
        .O(A__1[8]));
  (* SOFT_HLUTNM = "soft_lutpair53" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__1_i_21
       (.I0(in2[7]),
        .I1(Delay2_out1[7]),
        .I2(adc_trigger),
        .O(A__1[7]));
  (* SOFT_HLUTNM = "soft_lutpair53" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__1_i_22
       (.I0(in2[6]),
        .I1(Delay2_out1[6]),
        .I2(adc_trigger),
        .O(A__1[6]));
  (* SOFT_HLUTNM = "soft_lutpair52" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__1_i_23
       (.I0(in2[5]),
        .I1(Delay2_out1[5]),
        .I2(adc_trigger),
        .O(A__1[5]));
  (* SOFT_HLUTNM = "soft_lutpair52" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__1_i_24
       (.I0(in2[4]),
        .I1(Delay2_out1[4]),
        .I2(adc_trigger),
        .O(A__1[4]));
  (* SOFT_HLUTNM = "soft_lutpair51" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__1_i_25
       (.I0(in2[3]),
        .I1(Delay2_out1[3]),
        .I2(adc_trigger),
        .O(A__1[3]));
  (* SOFT_HLUTNM = "soft_lutpair51" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__1_i_26
       (.I0(in2[2]),
        .I1(Delay2_out1[2]),
        .I2(adc_trigger),
        .O(A__1[2]));
  (* SOFT_HLUTNM = "soft_lutpair50" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__1_i_27
       (.I0(in2[1]),
        .I1(Delay2_out1[1]),
        .I2(adc_trigger),
        .O(A__1[1]));
  (* SOFT_HLUTNM = "soft_lutpair50" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__1_i_28
       (.I0(in2[0]),
        .I1(Delay2_out1[0]),
        .I2(adc_trigger),
        .O(p_1_out__1_i_28_n_0));
  (* SOFT_HLUTNM = "soft_lutpair62" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__1_i_3
       (.I0(in2[25]),
        .I1(Delay2_out1[25]),
        .I2(adc_trigger),
        .O(A__1[25]));
  (* SOFT_HLUTNM = "soft_lutpair62" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__1_i_4
       (.I0(in2[24]),
        .I1(Delay2_out1[24]),
        .I2(adc_trigger),
        .O(A__1[24]));
  (* SOFT_HLUTNM = "soft_lutpair61" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__1_i_5
       (.I0(in2[23]),
        .I1(Delay2_out1[23]),
        .I2(adc_trigger),
        .O(A__1[23]));
  (* SOFT_HLUTNM = "soft_lutpair61" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__1_i_6
       (.I0(in2[22]),
        .I1(Delay2_out1[22]),
        .I2(adc_trigger),
        .O(A__1[22]));
  (* SOFT_HLUTNM = "soft_lutpair60" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__1_i_7
       (.I0(in2[21]),
        .I1(Delay2_out1[21]),
        .I2(adc_trigger),
        .O(A__1[21]));
  (* SOFT_HLUTNM = "soft_lutpair60" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__1_i_8
       (.I0(in2[20]),
        .I1(Delay2_out1[20]),
        .I2(adc_trigger),
        .O(A__1[20]));
  (* SOFT_HLUTNM = "soft_lutpair59" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__1_i_9
       (.I0(in2[19]),
        .I1(Delay2_out1[19]),
        .I2(adc_trigger),
        .O(A__1[19]));
  (* KEEP_HIERARCHY = "yes" *) 
  (* METHODOLOGY_DRC_VIOS = "{SYNTH-11 {cell *THIS*}}" *) 
  DSP48E2 #(
    .ACASCREG(0),
    .ADREG(1),
    .ALUMODEREG(0),
    .AMULTSEL("A"),
    .AREG(0),
    .AUTORESET_PATDET("NO_RESET"),
    .AUTORESET_PRIORITY("RESET"),
    .A_INPUT("DIRECT"),
    .BCASCREG(1),
    .BMULTSEL("B"),
    .BREG(1),
    .B_INPUT("DIRECT"),
    .CARRYINREG(0),
    .CARRYINSELREG(0),
    .CREG(0),
    .DREG(1),
    .INMODEREG(0),
    .MASK(48'h3FFFFFFFFFFF),
    .MREG(0),
    .OPMODEREG(0),
    .PATTERN(48'h000000000000),
    .PREADDINSEL("A"),
    .PREG(0),
    .RND(48'h000000000000),
    .SEL_MASK("MASK"),
    .SEL_PATTERN("PATTERN"),
    .USE_MULT("MULTIPLY"),
    .USE_PATTERN_DETECT("NO_PATDET"),
    .USE_SIMD("ONE48"),
    .USE_WIDEXOR("FALSE"),
    .XORSIMD("XOR24_48_96")) 
    p_1_out__2
       (.A({A__2[26],A__2[26],A__2[26],A__2,p_1_out__2_i_28_n_0}),
        .ACIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .ACOUT(NLW_p_1_out__2_ACOUT_UNCONNECTED[29:0]),
        .ALUMODE({1'b0,1'b0,1'b0,1'b0}),
        .B({1'b0,AXI_pu_conv_in31}),
        .BCIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .BCOUT(NLW_p_1_out__2_BCOUT_UNCONNECTED[17:0]),
        .C({A__2[26],A__2[26],A__2[26],A__2[26],A__2[26],A__2[26],A__2[26],A__2[26],A__2[26],A__2[26],A__2[26],A__2[26],A__2[26],A__2[26],A__2[26],A__2[26],A__2[26],A__2[26],A__2[26],A__2[26],A__2[26],A__2[26],A__2}),
        .CARRYCASCIN(1'b0),
        .CARRYCASCOUT(NLW_p_1_out__2_CARRYCASCOUT_UNCONNECTED),
        .CARRYIN(1'b0),
        .CARRYINSEL({1'b0,1'b0,1'b0}),
        .CARRYOUT(NLW_p_1_out__2_CARRYOUT_UNCONNECTED[3:0]),
        .CEA1(1'b0),
        .CEA2(1'b0),
        .CEAD(1'b0),
        .CEALUMODE(1'b0),
        .CEB1(1'b0),
        .CEB2(DSP_ALU_INST_2),
        .CEC(1'b0),
        .CECARRYIN(1'b0),
        .CECTRL(1'b0),
        .CED(1'b0),
        .CEINMODE(1'b0),
        .CEM(1'b0),
        .CEP(1'b0),
        .CLK(AXI4_Lite_ACLK),
        .D({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .INMODE({1'b0,1'b0,1'b0,1'b0,1'b0}),
        .MULTSIGNIN(1'b0),
        .MULTSIGNOUT(NLW_p_1_out__2_MULTSIGNOUT_UNCONNECTED),
        .OPMODE({1'b0,1'b0,1'b0,\out3[17] ,\out3[17] ,1'b0,1'b1,1'b0,1'b1}),
        .OVERFLOW(NLW_p_1_out__2_OVERFLOW_UNCONNECTED),
        .P({NLW_p_1_out__2_P_UNCONNECTED[47:45],p_1_out__2_n_61,p_1_out__2_n_62,p_1_out__2_n_63,p_1_out__2_n_64,p_1_out__2_n_65,p_1_out__2_n_66,p_1_out__2_n_67,p_1_out__2_n_68,p_1_out__2_n_69,p_1_out__2_n_70,out3,p_1_out__2_n_89,p_1_out__2_n_90,p_1_out__2_n_91,p_1_out__2_n_92,p_1_out__2_n_93,p_1_out__2_n_94,p_1_out__2_n_95,p_1_out__2_n_96,p_1_out__2_n_97,p_1_out__2_n_98,p_1_out__2_n_99,p_1_out__2_n_100,p_1_out__2_n_101,p_1_out__2_n_102,p_1_out__2_n_103,p_1_out__2_n_104,p_1_out__2_n_105}),
        .PATTERNBDETECT(NLW_p_1_out__2_PATTERNBDETECT_UNCONNECTED),
        .PATTERNDETECT(NLW_p_1_out__2_PATTERNDETECT_UNCONNECTED),
        .PCIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .PCOUT(NLW_p_1_out__2_PCOUT_UNCONNECTED[47:0]),
        .RSTA(1'b0),
        .RSTALLCARRYIN(1'b0),
        .RSTALUMODE(1'b0),
        .RSTB(reset),
        .RSTC(1'b0),
        .RSTCTRL(1'b0),
        .RSTD(1'b0),
        .RSTINMODE(1'b0),
        .RSTM(1'b0),
        .RSTP(1'b0),
        .UNDERFLOW(NLW_p_1_out__2_UNDERFLOW_UNCONNECTED),
        .XOROUT(NLW_p_1_out__2_XOROUT_UNCONNECTED[7:0]));
  (* KEEP_HIERARCHY = "yes" *) 
  (* METHODOLOGY_DRC_VIOS = "{SYNTH-11 {cell *THIS*}}" *) 
  DSP48E2 #(
    .ACASCREG(0),
    .ADREG(1),
    .ALUMODEREG(0),
    .AMULTSEL("A"),
    .AREG(0),
    .AUTORESET_PATDET("NO_RESET"),
    .AUTORESET_PRIORITY("RESET"),
    .A_INPUT("DIRECT"),
    .BCASCREG(1),
    .BMULTSEL("B"),
    .BREG(1),
    .B_INPUT("DIRECT"),
    .CARRYINREG(0),
    .CARRYINSELREG(0),
    .CREG(0),
    .DREG(1),
    .INMODEREG(0),
    .MASK(48'h3FFFFFFFFFFF),
    .MREG(0),
    .OPMODEREG(0),
    .PATTERN(48'h000000000000),
    .PREADDINSEL("A"),
    .PREG(0),
    .RND(48'h000000000000),
    .SEL_MASK("MASK"),
    .SEL_PATTERN("PATTERN"),
    .USE_MULT("MULTIPLY"),
    .USE_PATTERN_DETECT("NO_PATDET"),
    .USE_SIMD("ONE48"),
    .USE_WIDEXOR("FALSE"),
    .XORSIMD("XOR24_48_96")) 
    p_1_out__20
       (.A({A__20[26],A__20[26],A__20[26],A__20,p_1_out__20_i_28_n_0}),
        .ACIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .ACOUT(NLW_p_1_out__20_ACOUT_UNCONNECTED[29:0]),
        .ALUMODE({1'b0,1'b0,1'b0,1'b0}),
        .B({1'b0,AXI_pu_conv_in31}),
        .BCIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .BCOUT(NLW_p_1_out__20_BCOUT_UNCONNECTED[17:0]),
        .C({A__20[26],A__20[26],A__20[26],A__20[26],A__20[26],A__20[26],A__20[26],A__20[26],A__20[26],A__20[26],A__20[26],A__20[26],A__20[26],A__20[26],A__20[26],A__20[26],A__20[26],A__20[26],A__20[26],A__20[26],A__20[26],A__20[26],A__20}),
        .CARRYCASCIN(1'b0),
        .CARRYCASCOUT(NLW_p_1_out__20_CARRYCASCOUT_UNCONNECTED),
        .CARRYIN(1'b0),
        .CARRYINSEL({1'b0,1'b0,1'b0}),
        .CARRYOUT(NLW_p_1_out__20_CARRYOUT_UNCONNECTED[3:0]),
        .CEA1(1'b0),
        .CEA2(1'b0),
        .CEAD(1'b0),
        .CEALUMODE(1'b0),
        .CEB1(1'b0),
        .CEB2(DSP_ALU_INST_20),
        .CEC(1'b0),
        .CECARRYIN(1'b0),
        .CECTRL(1'b0),
        .CED(1'b0),
        .CEINMODE(1'b0),
        .CEM(1'b0),
        .CEP(1'b0),
        .CLK(AXI4_Lite_ACLK),
        .D({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .INMODE({1'b0,1'b0,1'b0,1'b0,1'b0}),
        .MULTSIGNIN(1'b0),
        .MULTSIGNOUT(NLW_p_1_out__20_MULTSIGNOUT_UNCONNECTED),
        .OPMODE({1'b0,1'b0,1'b0,\out21[17] ,\out21[17] ,1'b0,1'b1,1'b0,1'b1}),
        .OVERFLOW(NLW_p_1_out__20_OVERFLOW_UNCONNECTED),
        .P({NLW_p_1_out__20_P_UNCONNECTED[47:45],p_1_out__20_n_61,p_1_out__20_n_62,p_1_out__20_n_63,p_1_out__20_n_64,p_1_out__20_n_65,p_1_out__20_n_66,p_1_out__20_n_67,p_1_out__20_n_68,p_1_out__20_n_69,p_1_out__20_n_70,out21,p_1_out__20_n_89,p_1_out__20_n_90,p_1_out__20_n_91,p_1_out__20_n_92,p_1_out__20_n_93,p_1_out__20_n_94,p_1_out__20_n_95,p_1_out__20_n_96,p_1_out__20_n_97,p_1_out__20_n_98,p_1_out__20_n_99,p_1_out__20_n_100,p_1_out__20_n_101,p_1_out__20_n_102,p_1_out__20_n_103,p_1_out__20_n_104,p_1_out__20_n_105}),
        .PATTERNBDETECT(NLW_p_1_out__20_PATTERNBDETECT_UNCONNECTED),
        .PATTERNDETECT(NLW_p_1_out__20_PATTERNDETECT_UNCONNECTED),
        .PCIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .PCOUT(NLW_p_1_out__20_PCOUT_UNCONNECTED[47:0]),
        .RSTA(1'b0),
        .RSTALLCARRYIN(1'b0),
        .RSTALUMODE(1'b0),
        .RSTB(reset),
        .RSTC(1'b0),
        .RSTCTRL(1'b0),
        .RSTD(1'b0),
        .RSTINMODE(1'b0),
        .RSTM(1'b0),
        .RSTP(1'b0),
        .UNDERFLOW(NLW_p_1_out__20_UNDERFLOW_UNCONNECTED),
        .XOROUT(NLW_p_1_out__20_XOROUT_UNCONNECTED[7:0]));
  (* SOFT_HLUTNM = "soft_lutpair315" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__20_i_10
       (.I0(in21[18]),
        .I1(Delay21_out1[18]),
        .I2(adc_trigger),
        .O(A__20[18]));
  (* SOFT_HLUTNM = "soft_lutpair315" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__20_i_11
       (.I0(in21[17]),
        .I1(Delay21_out1[17]),
        .I2(adc_trigger),
        .O(A__20[17]));
  (* SOFT_HLUTNM = "soft_lutpair314" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__20_i_12
       (.I0(in21[16]),
        .I1(Delay21_out1[16]),
        .I2(adc_trigger),
        .O(A__20[16]));
  (* SOFT_HLUTNM = "soft_lutpair314" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__20_i_13
       (.I0(in21[15]),
        .I1(Delay21_out1[15]),
        .I2(adc_trigger),
        .O(A__20[15]));
  (* SOFT_HLUTNM = "soft_lutpair313" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__20_i_14
       (.I0(in21[14]),
        .I1(Delay21_out1[14]),
        .I2(adc_trigger),
        .O(A__20[14]));
  (* SOFT_HLUTNM = "soft_lutpair313" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__20_i_15
       (.I0(in21[13]),
        .I1(Delay21_out1[13]),
        .I2(adc_trigger),
        .O(A__20[13]));
  (* SOFT_HLUTNM = "soft_lutpair312" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__20_i_16
       (.I0(in21[12]),
        .I1(Delay21_out1[12]),
        .I2(adc_trigger),
        .O(A__20[12]));
  (* SOFT_HLUTNM = "soft_lutpair312" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__20_i_17
       (.I0(in21[11]),
        .I1(Delay21_out1[11]),
        .I2(adc_trigger),
        .O(A__20[11]));
  (* SOFT_HLUTNM = "soft_lutpair311" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__20_i_18
       (.I0(in21[10]),
        .I1(Delay21_out1[10]),
        .I2(adc_trigger),
        .O(A__20[10]));
  (* SOFT_HLUTNM = "soft_lutpair311" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__20_i_19
       (.I0(in21[9]),
        .I1(Delay21_out1[9]),
        .I2(adc_trigger),
        .O(A__20[9]));
  (* SOFT_HLUTNM = "soft_lutpair319" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__20_i_2
       (.I0(in21[26]),
        .I1(Delay21_out1[26]),
        .I2(adc_trigger),
        .O(A__20[26]));
  (* SOFT_HLUTNM = "soft_lutpair310" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__20_i_20
       (.I0(in21[8]),
        .I1(Delay21_out1[8]),
        .I2(adc_trigger),
        .O(A__20[8]));
  (* SOFT_HLUTNM = "soft_lutpair310" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__20_i_21
       (.I0(in21[7]),
        .I1(Delay21_out1[7]),
        .I2(adc_trigger),
        .O(A__20[7]));
  (* SOFT_HLUTNM = "soft_lutpair309" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__20_i_22
       (.I0(in21[6]),
        .I1(Delay21_out1[6]),
        .I2(adc_trigger),
        .O(A__20[6]));
  (* SOFT_HLUTNM = "soft_lutpair309" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__20_i_23
       (.I0(in21[5]),
        .I1(Delay21_out1[5]),
        .I2(adc_trigger),
        .O(A__20[5]));
  (* SOFT_HLUTNM = "soft_lutpair308" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__20_i_24
       (.I0(in21[4]),
        .I1(Delay21_out1[4]),
        .I2(adc_trigger),
        .O(A__20[4]));
  (* SOFT_HLUTNM = "soft_lutpair308" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__20_i_25
       (.I0(in21[3]),
        .I1(Delay21_out1[3]),
        .I2(adc_trigger),
        .O(A__20[3]));
  (* SOFT_HLUTNM = "soft_lutpair307" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__20_i_26
       (.I0(in21[2]),
        .I1(Delay21_out1[2]),
        .I2(adc_trigger),
        .O(A__20[2]));
  (* SOFT_HLUTNM = "soft_lutpair307" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__20_i_27
       (.I0(in21[1]),
        .I1(Delay21_out1[1]),
        .I2(adc_trigger),
        .O(A__20[1]));
  (* SOFT_HLUTNM = "soft_lutpair306" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__20_i_28
       (.I0(in21[0]),
        .I1(Delay21_out1[0]),
        .I2(adc_trigger),
        .O(p_1_out__20_i_28_n_0));
  (* SOFT_HLUTNM = "soft_lutpair319" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__20_i_3
       (.I0(in21[25]),
        .I1(Delay21_out1[25]),
        .I2(adc_trigger),
        .O(A__20[25]));
  (* SOFT_HLUTNM = "soft_lutpair318" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__20_i_4
       (.I0(in21[24]),
        .I1(Delay21_out1[24]),
        .I2(adc_trigger),
        .O(A__20[24]));
  (* SOFT_HLUTNM = "soft_lutpair318" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__20_i_5
       (.I0(in21[23]),
        .I1(Delay21_out1[23]),
        .I2(adc_trigger),
        .O(A__20[23]));
  (* SOFT_HLUTNM = "soft_lutpair317" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__20_i_6
       (.I0(in21[22]),
        .I1(Delay21_out1[22]),
        .I2(adc_trigger),
        .O(A__20[22]));
  (* SOFT_HLUTNM = "soft_lutpair317" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__20_i_7
       (.I0(in21[21]),
        .I1(Delay21_out1[21]),
        .I2(adc_trigger),
        .O(A__20[21]));
  (* SOFT_HLUTNM = "soft_lutpair316" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__20_i_8
       (.I0(in21[20]),
        .I1(Delay21_out1[20]),
        .I2(adc_trigger),
        .O(A__20[20]));
  (* SOFT_HLUTNM = "soft_lutpair316" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__20_i_9
       (.I0(in21[19]),
        .I1(Delay21_out1[19]),
        .I2(adc_trigger),
        .O(A__20[19]));
  (* KEEP_HIERARCHY = "yes" *) 
  (* METHODOLOGY_DRC_VIOS = "{SYNTH-11 {cell *THIS*}}" *) 
  DSP48E2 #(
    .ACASCREG(0),
    .ADREG(1),
    .ALUMODEREG(0),
    .AMULTSEL("A"),
    .AREG(0),
    .AUTORESET_PATDET("NO_RESET"),
    .AUTORESET_PRIORITY("RESET"),
    .A_INPUT("DIRECT"),
    .BCASCREG(1),
    .BMULTSEL("B"),
    .BREG(1),
    .B_INPUT("DIRECT"),
    .CARRYINREG(0),
    .CARRYINSELREG(0),
    .CREG(0),
    .DREG(1),
    .INMODEREG(0),
    .MASK(48'h3FFFFFFFFFFF),
    .MREG(0),
    .OPMODEREG(0),
    .PATTERN(48'h000000000000),
    .PREADDINSEL("A"),
    .PREG(0),
    .RND(48'h000000000000),
    .SEL_MASK("MASK"),
    .SEL_PATTERN("PATTERN"),
    .USE_MULT("MULTIPLY"),
    .USE_PATTERN_DETECT("NO_PATDET"),
    .USE_SIMD("ONE48"),
    .USE_WIDEXOR("FALSE"),
    .XORSIMD("XOR24_48_96")) 
    p_1_out__21
       (.A({A__21[26],A__21[26],A__21[26],A__21,p_1_out__21_i_28_n_0}),
        .ACIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .ACOUT(NLW_p_1_out__21_ACOUT_UNCONNECTED[29:0]),
        .ALUMODE({1'b0,1'b0,1'b0,1'b0}),
        .B({1'b0,AXI_pu_conv_in31}),
        .BCIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .BCOUT(NLW_p_1_out__21_BCOUT_UNCONNECTED[17:0]),
        .C({A__21[26],A__21[26],A__21[26],A__21[26],A__21[26],A__21[26],A__21[26],A__21[26],A__21[26],A__21[26],A__21[26],A__21[26],A__21[26],A__21[26],A__21[26],A__21[26],A__21[26],A__21[26],A__21[26],A__21[26],A__21[26],A__21[26],A__21}),
        .CARRYCASCIN(1'b0),
        .CARRYCASCOUT(NLW_p_1_out__21_CARRYCASCOUT_UNCONNECTED),
        .CARRYIN(1'b0),
        .CARRYINSEL({1'b0,1'b0,1'b0}),
        .CARRYOUT(NLW_p_1_out__21_CARRYOUT_UNCONNECTED[3:0]),
        .CEA1(1'b0),
        .CEA2(1'b0),
        .CEAD(1'b0),
        .CEALUMODE(1'b0),
        .CEB1(1'b0),
        .CEB2(DSP_ALU_INST_21),
        .CEC(1'b0),
        .CECARRYIN(1'b0),
        .CECTRL(1'b0),
        .CED(1'b0),
        .CEINMODE(1'b0),
        .CEM(1'b0),
        .CEP(1'b0),
        .CLK(AXI4_Lite_ACLK),
        .D({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .INMODE({1'b0,1'b0,1'b0,1'b0,1'b0}),
        .MULTSIGNIN(1'b0),
        .MULTSIGNOUT(NLW_p_1_out__21_MULTSIGNOUT_UNCONNECTED),
        .OPMODE({1'b0,1'b0,1'b0,\out22[17] ,\out22[17] ,1'b0,1'b1,1'b0,1'b1}),
        .OVERFLOW(NLW_p_1_out__21_OVERFLOW_UNCONNECTED),
        .P({NLW_p_1_out__21_P_UNCONNECTED[47:45],p_1_out__21_n_61,p_1_out__21_n_62,p_1_out__21_n_63,p_1_out__21_n_64,p_1_out__21_n_65,p_1_out__21_n_66,p_1_out__21_n_67,p_1_out__21_n_68,p_1_out__21_n_69,p_1_out__21_n_70,out22,p_1_out__21_n_89,p_1_out__21_n_90,p_1_out__21_n_91,p_1_out__21_n_92,p_1_out__21_n_93,p_1_out__21_n_94,p_1_out__21_n_95,p_1_out__21_n_96,p_1_out__21_n_97,p_1_out__21_n_98,p_1_out__21_n_99,p_1_out__21_n_100,p_1_out__21_n_101,p_1_out__21_n_102,p_1_out__21_n_103,p_1_out__21_n_104,p_1_out__21_n_105}),
        .PATTERNBDETECT(NLW_p_1_out__21_PATTERNBDETECT_UNCONNECTED),
        .PATTERNDETECT(NLW_p_1_out__21_PATTERNDETECT_UNCONNECTED),
        .PCIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .PCOUT(NLW_p_1_out__21_PCOUT_UNCONNECTED[47:0]),
        .RSTA(1'b0),
        .RSTALLCARRYIN(1'b0),
        .RSTALUMODE(1'b0),
        .RSTB(reset),
        .RSTC(1'b0),
        .RSTCTRL(1'b0),
        .RSTD(1'b0),
        .RSTINMODE(1'b0),
        .RSTM(1'b0),
        .RSTP(1'b0),
        .UNDERFLOW(NLW_p_1_out__21_UNDERFLOW_UNCONNECTED),
        .XOROUT(NLW_p_1_out__21_XOROUT_UNCONNECTED[7:0]));
  (* SOFT_HLUTNM = "soft_lutpair329" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__21_i_10
       (.I0(in22[18]),
        .I1(Delay22_out1[18]),
        .I2(adc_trigger),
        .O(A__21[18]));
  (* SOFT_HLUTNM = "soft_lutpair328" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__21_i_11
       (.I0(in22[17]),
        .I1(Delay22_out1[17]),
        .I2(adc_trigger),
        .O(A__21[17]));
  (* SOFT_HLUTNM = "soft_lutpair328" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__21_i_12
       (.I0(in22[16]),
        .I1(Delay22_out1[16]),
        .I2(adc_trigger),
        .O(A__21[16]));
  (* SOFT_HLUTNM = "soft_lutpair327" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__21_i_13
       (.I0(in22[15]),
        .I1(Delay22_out1[15]),
        .I2(adc_trigger),
        .O(A__21[15]));
  (* SOFT_HLUTNM = "soft_lutpair327" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__21_i_14
       (.I0(in22[14]),
        .I1(Delay22_out1[14]),
        .I2(adc_trigger),
        .O(A__21[14]));
  (* SOFT_HLUTNM = "soft_lutpair326" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__21_i_15
       (.I0(in22[13]),
        .I1(Delay22_out1[13]),
        .I2(adc_trigger),
        .O(A__21[13]));
  (* SOFT_HLUTNM = "soft_lutpair326" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__21_i_16
       (.I0(in22[12]),
        .I1(Delay22_out1[12]),
        .I2(adc_trigger),
        .O(A__21[12]));
  (* SOFT_HLUTNM = "soft_lutpair325" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__21_i_17
       (.I0(in22[11]),
        .I1(Delay22_out1[11]),
        .I2(adc_trigger),
        .O(A__21[11]));
  (* SOFT_HLUTNM = "soft_lutpair325" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__21_i_18
       (.I0(in22[10]),
        .I1(Delay22_out1[10]),
        .I2(adc_trigger),
        .O(A__21[10]));
  (* SOFT_HLUTNM = "soft_lutpair324" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__21_i_19
       (.I0(in22[9]),
        .I1(Delay22_out1[9]),
        .I2(adc_trigger),
        .O(A__21[9]));
  (* SOFT_HLUTNM = "soft_lutpair333" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__21_i_2
       (.I0(in22[26]),
        .I1(Delay22_out1[26]),
        .I2(adc_trigger),
        .O(A__21[26]));
  (* SOFT_HLUTNM = "soft_lutpair324" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__21_i_20
       (.I0(in22[8]),
        .I1(Delay22_out1[8]),
        .I2(adc_trigger),
        .O(A__21[8]));
  (* SOFT_HLUTNM = "soft_lutpair323" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__21_i_21
       (.I0(in22[7]),
        .I1(Delay22_out1[7]),
        .I2(adc_trigger),
        .O(A__21[7]));
  (* SOFT_HLUTNM = "soft_lutpair323" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__21_i_22
       (.I0(in22[6]),
        .I1(Delay22_out1[6]),
        .I2(adc_trigger),
        .O(A__21[6]));
  (* SOFT_HLUTNM = "soft_lutpair322" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__21_i_23
       (.I0(in22[5]),
        .I1(Delay22_out1[5]),
        .I2(adc_trigger),
        .O(A__21[5]));
  (* SOFT_HLUTNM = "soft_lutpair322" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__21_i_24
       (.I0(in22[4]),
        .I1(Delay22_out1[4]),
        .I2(adc_trigger),
        .O(A__21[4]));
  (* SOFT_HLUTNM = "soft_lutpair321" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__21_i_25
       (.I0(in22[3]),
        .I1(Delay22_out1[3]),
        .I2(adc_trigger),
        .O(A__21[3]));
  (* SOFT_HLUTNM = "soft_lutpair321" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__21_i_26
       (.I0(in22[2]),
        .I1(Delay22_out1[2]),
        .I2(adc_trigger),
        .O(A__21[2]));
  (* SOFT_HLUTNM = "soft_lutpair320" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__21_i_27
       (.I0(in22[1]),
        .I1(Delay22_out1[1]),
        .I2(adc_trigger),
        .O(A__21[1]));
  (* SOFT_HLUTNM = "soft_lutpair320" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__21_i_28
       (.I0(in22[0]),
        .I1(Delay22_out1[0]),
        .I2(adc_trigger),
        .O(p_1_out__21_i_28_n_0));
  (* SOFT_HLUTNM = "soft_lutpair332" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__21_i_3
       (.I0(in22[25]),
        .I1(Delay22_out1[25]),
        .I2(adc_trigger),
        .O(A__21[25]));
  (* SOFT_HLUTNM = "soft_lutpair332" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__21_i_4
       (.I0(in22[24]),
        .I1(Delay22_out1[24]),
        .I2(adc_trigger),
        .O(A__21[24]));
  (* SOFT_HLUTNM = "soft_lutpair331" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__21_i_5
       (.I0(in22[23]),
        .I1(Delay22_out1[23]),
        .I2(adc_trigger),
        .O(A__21[23]));
  (* SOFT_HLUTNM = "soft_lutpair331" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__21_i_6
       (.I0(in22[22]),
        .I1(Delay22_out1[22]),
        .I2(adc_trigger),
        .O(A__21[22]));
  (* SOFT_HLUTNM = "soft_lutpair330" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__21_i_7
       (.I0(in22[21]),
        .I1(Delay22_out1[21]),
        .I2(adc_trigger),
        .O(A__21[21]));
  (* SOFT_HLUTNM = "soft_lutpair330" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__21_i_8
       (.I0(in22[20]),
        .I1(Delay22_out1[20]),
        .I2(adc_trigger),
        .O(A__21[20]));
  (* SOFT_HLUTNM = "soft_lutpair329" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__21_i_9
       (.I0(in22[19]),
        .I1(Delay22_out1[19]),
        .I2(adc_trigger),
        .O(A__21[19]));
  (* KEEP_HIERARCHY = "yes" *) 
  (* METHODOLOGY_DRC_VIOS = "{SYNTH-11 {cell *THIS*}}" *) 
  DSP48E2 #(
    .ACASCREG(0),
    .ADREG(1),
    .ALUMODEREG(0),
    .AMULTSEL("A"),
    .AREG(0),
    .AUTORESET_PATDET("NO_RESET"),
    .AUTORESET_PRIORITY("RESET"),
    .A_INPUT("DIRECT"),
    .BCASCREG(1),
    .BMULTSEL("B"),
    .BREG(1),
    .B_INPUT("DIRECT"),
    .CARRYINREG(0),
    .CARRYINSELREG(0),
    .CREG(0),
    .DREG(1),
    .INMODEREG(0),
    .MASK(48'h3FFFFFFFFFFF),
    .MREG(0),
    .OPMODEREG(0),
    .PATTERN(48'h000000000000),
    .PREADDINSEL("A"),
    .PREG(0),
    .RND(48'h000000000000),
    .SEL_MASK("MASK"),
    .SEL_PATTERN("PATTERN"),
    .USE_MULT("MULTIPLY"),
    .USE_PATTERN_DETECT("NO_PATDET"),
    .USE_SIMD("ONE48"),
    .USE_WIDEXOR("FALSE"),
    .XORSIMD("XOR24_48_96")) 
    p_1_out__22
       (.A({A__22[26],A__22[26],A__22[26],A__22,p_1_out__22_i_28_n_0}),
        .ACIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .ACOUT(NLW_p_1_out__22_ACOUT_UNCONNECTED[29:0]),
        .ALUMODE({1'b0,1'b0,1'b0,1'b0}),
        .B({1'b0,AXI_pu_conv_in31}),
        .BCIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .BCOUT(NLW_p_1_out__22_BCOUT_UNCONNECTED[17:0]),
        .C({A__22[26],A__22[26],A__22[26],A__22[26],A__22[26],A__22[26],A__22[26],A__22[26],A__22[26],A__22[26],A__22[26],A__22[26],A__22[26],A__22[26],A__22[26],A__22[26],A__22[26],A__22[26],A__22[26],A__22[26],A__22[26],A__22[26],A__22}),
        .CARRYCASCIN(1'b0),
        .CARRYCASCOUT(NLW_p_1_out__22_CARRYCASCOUT_UNCONNECTED),
        .CARRYIN(1'b0),
        .CARRYINSEL({1'b0,1'b0,1'b0}),
        .CARRYOUT(NLW_p_1_out__22_CARRYOUT_UNCONNECTED[3:0]),
        .CEA1(1'b0),
        .CEA2(1'b0),
        .CEAD(1'b0),
        .CEALUMODE(1'b0),
        .CEB1(1'b0),
        .CEB2(DSP_ALU_INST_22),
        .CEC(1'b0),
        .CECARRYIN(1'b0),
        .CECTRL(1'b0),
        .CED(1'b0),
        .CEINMODE(1'b0),
        .CEM(1'b0),
        .CEP(1'b0),
        .CLK(AXI4_Lite_ACLK),
        .D({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .INMODE({1'b0,1'b0,1'b0,1'b0,1'b0}),
        .MULTSIGNIN(1'b0),
        .MULTSIGNOUT(NLW_p_1_out__22_MULTSIGNOUT_UNCONNECTED),
        .OPMODE({1'b0,1'b0,1'b0,\out23[17] ,\out23[17] ,1'b0,1'b1,1'b0,1'b1}),
        .OVERFLOW(NLW_p_1_out__22_OVERFLOW_UNCONNECTED),
        .P({NLW_p_1_out__22_P_UNCONNECTED[47:45],p_1_out__22_n_61,p_1_out__22_n_62,p_1_out__22_n_63,p_1_out__22_n_64,p_1_out__22_n_65,p_1_out__22_n_66,p_1_out__22_n_67,p_1_out__22_n_68,p_1_out__22_n_69,p_1_out__22_n_70,out23,p_1_out__22_n_89,p_1_out__22_n_90,p_1_out__22_n_91,p_1_out__22_n_92,p_1_out__22_n_93,p_1_out__22_n_94,p_1_out__22_n_95,p_1_out__22_n_96,p_1_out__22_n_97,p_1_out__22_n_98,p_1_out__22_n_99,p_1_out__22_n_100,p_1_out__22_n_101,p_1_out__22_n_102,p_1_out__22_n_103,p_1_out__22_n_104,p_1_out__22_n_105}),
        .PATTERNBDETECT(NLW_p_1_out__22_PATTERNBDETECT_UNCONNECTED),
        .PATTERNDETECT(NLW_p_1_out__22_PATTERNDETECT_UNCONNECTED),
        .PCIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .PCOUT(NLW_p_1_out__22_PCOUT_UNCONNECTED[47:0]),
        .RSTA(1'b0),
        .RSTALLCARRYIN(1'b0),
        .RSTALUMODE(1'b0),
        .RSTB(reset),
        .RSTC(1'b0),
        .RSTCTRL(1'b0),
        .RSTD(1'b0),
        .RSTINMODE(1'b0),
        .RSTM(1'b0),
        .RSTP(1'b0),
        .UNDERFLOW(NLW_p_1_out__22_UNDERFLOW_UNCONNECTED),
        .XOROUT(NLW_p_1_out__22_XOROUT_UNCONNECTED[7:0]));
  (* SOFT_HLUTNM = "soft_lutpair342" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__22_i_10
       (.I0(in23[18]),
        .I1(Delay23_out1[18]),
        .I2(adc_trigger),
        .O(A__22[18]));
  (* SOFT_HLUTNM = "soft_lutpair342" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__22_i_11
       (.I0(in23[17]),
        .I1(Delay23_out1[17]),
        .I2(adc_trigger),
        .O(A__22[17]));
  (* SOFT_HLUTNM = "soft_lutpair341" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__22_i_12
       (.I0(in23[16]),
        .I1(Delay23_out1[16]),
        .I2(adc_trigger),
        .O(A__22[16]));
  (* SOFT_HLUTNM = "soft_lutpair341" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__22_i_13
       (.I0(in23[15]),
        .I1(Delay23_out1[15]),
        .I2(adc_trigger),
        .O(A__22[15]));
  (* SOFT_HLUTNM = "soft_lutpair340" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__22_i_14
       (.I0(in23[14]),
        .I1(Delay23_out1[14]),
        .I2(adc_trigger),
        .O(A__22[14]));
  (* SOFT_HLUTNM = "soft_lutpair340" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__22_i_15
       (.I0(in23[13]),
        .I1(Delay23_out1[13]),
        .I2(adc_trigger),
        .O(A__22[13]));
  (* SOFT_HLUTNM = "soft_lutpair339" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__22_i_16
       (.I0(in23[12]),
        .I1(Delay23_out1[12]),
        .I2(adc_trigger),
        .O(A__22[12]));
  (* SOFT_HLUTNM = "soft_lutpair339" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__22_i_17
       (.I0(in23[11]),
        .I1(Delay23_out1[11]),
        .I2(adc_trigger),
        .O(A__22[11]));
  (* SOFT_HLUTNM = "soft_lutpair338" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__22_i_18
       (.I0(in23[10]),
        .I1(Delay23_out1[10]),
        .I2(adc_trigger),
        .O(A__22[10]));
  (* SOFT_HLUTNM = "soft_lutpair338" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__22_i_19
       (.I0(in23[9]),
        .I1(Delay23_out1[9]),
        .I2(adc_trigger),
        .O(A__22[9]));
  (* SOFT_HLUTNM = "soft_lutpair346" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__22_i_2
       (.I0(in23[26]),
        .I1(Delay23_out1[26]),
        .I2(adc_trigger),
        .O(A__22[26]));
  (* SOFT_HLUTNM = "soft_lutpair337" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__22_i_20
       (.I0(in23[8]),
        .I1(Delay23_out1[8]),
        .I2(adc_trigger),
        .O(A__22[8]));
  (* SOFT_HLUTNM = "soft_lutpair337" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__22_i_21
       (.I0(in23[7]),
        .I1(Delay23_out1[7]),
        .I2(adc_trigger),
        .O(A__22[7]));
  (* SOFT_HLUTNM = "soft_lutpair336" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__22_i_22
       (.I0(in23[6]),
        .I1(Delay23_out1[6]),
        .I2(adc_trigger),
        .O(A__22[6]));
  (* SOFT_HLUTNM = "soft_lutpair336" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__22_i_23
       (.I0(in23[5]),
        .I1(Delay23_out1[5]),
        .I2(adc_trigger),
        .O(A__22[5]));
  (* SOFT_HLUTNM = "soft_lutpair335" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__22_i_24
       (.I0(in23[4]),
        .I1(Delay23_out1[4]),
        .I2(adc_trigger),
        .O(A__22[4]));
  (* SOFT_HLUTNM = "soft_lutpair335" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__22_i_25
       (.I0(in23[3]),
        .I1(Delay23_out1[3]),
        .I2(adc_trigger),
        .O(A__22[3]));
  (* SOFT_HLUTNM = "soft_lutpair334" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__22_i_26
       (.I0(in23[2]),
        .I1(Delay23_out1[2]),
        .I2(adc_trigger),
        .O(A__22[2]));
  (* SOFT_HLUTNM = "soft_lutpair334" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__22_i_27
       (.I0(in23[1]),
        .I1(Delay23_out1[1]),
        .I2(adc_trigger),
        .O(A__22[1]));
  (* SOFT_HLUTNM = "soft_lutpair333" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__22_i_28
       (.I0(in23[0]),
        .I1(Delay23_out1[0]),
        .I2(adc_trigger),
        .O(p_1_out__22_i_28_n_0));
  (* SOFT_HLUTNM = "soft_lutpair346" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__22_i_3
       (.I0(in23[25]),
        .I1(Delay23_out1[25]),
        .I2(adc_trigger),
        .O(A__22[25]));
  (* SOFT_HLUTNM = "soft_lutpair345" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__22_i_4
       (.I0(in23[24]),
        .I1(Delay23_out1[24]),
        .I2(adc_trigger),
        .O(A__22[24]));
  (* SOFT_HLUTNM = "soft_lutpair345" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__22_i_5
       (.I0(in23[23]),
        .I1(Delay23_out1[23]),
        .I2(adc_trigger),
        .O(A__22[23]));
  (* SOFT_HLUTNM = "soft_lutpair344" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__22_i_6
       (.I0(in23[22]),
        .I1(Delay23_out1[22]),
        .I2(adc_trigger),
        .O(A__22[22]));
  (* SOFT_HLUTNM = "soft_lutpair344" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__22_i_7
       (.I0(in23[21]),
        .I1(Delay23_out1[21]),
        .I2(adc_trigger),
        .O(A__22[21]));
  (* SOFT_HLUTNM = "soft_lutpair343" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__22_i_8
       (.I0(in23[20]),
        .I1(Delay23_out1[20]),
        .I2(adc_trigger),
        .O(A__22[20]));
  (* SOFT_HLUTNM = "soft_lutpair343" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__22_i_9
       (.I0(in23[19]),
        .I1(Delay23_out1[19]),
        .I2(adc_trigger),
        .O(A__22[19]));
  (* KEEP_HIERARCHY = "yes" *) 
  (* METHODOLOGY_DRC_VIOS = "{SYNTH-11 {cell *THIS*}}" *) 
  DSP48E2 #(
    .ACASCREG(0),
    .ADREG(1),
    .ALUMODEREG(0),
    .AMULTSEL("A"),
    .AREG(0),
    .AUTORESET_PATDET("NO_RESET"),
    .AUTORESET_PRIORITY("RESET"),
    .A_INPUT("DIRECT"),
    .BCASCREG(1),
    .BMULTSEL("B"),
    .BREG(1),
    .B_INPUT("DIRECT"),
    .CARRYINREG(0),
    .CARRYINSELREG(0),
    .CREG(0),
    .DREG(1),
    .INMODEREG(0),
    .MASK(48'h3FFFFFFFFFFF),
    .MREG(0),
    .OPMODEREG(0),
    .PATTERN(48'h000000000000),
    .PREADDINSEL("A"),
    .PREG(0),
    .RND(48'h000000000000),
    .SEL_MASK("MASK"),
    .SEL_PATTERN("PATTERN"),
    .USE_MULT("MULTIPLY"),
    .USE_PATTERN_DETECT("NO_PATDET"),
    .USE_SIMD("ONE48"),
    .USE_WIDEXOR("FALSE"),
    .XORSIMD("XOR24_48_96")) 
    p_1_out__23
       (.A({A__23[26],A__23[26],A__23[26],A__23,p_1_out__23_i_28_n_0}),
        .ACIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .ACOUT(NLW_p_1_out__23_ACOUT_UNCONNECTED[29:0]),
        .ALUMODE({1'b0,1'b0,1'b0,1'b0}),
        .B({1'b0,AXI_pu_conv_in31}),
        .BCIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .BCOUT(NLW_p_1_out__23_BCOUT_UNCONNECTED[17:0]),
        .C({A__23[26],A__23[26],A__23[26],A__23[26],A__23[26],A__23[26],A__23[26],A__23[26],A__23[26],A__23[26],A__23[26],A__23[26],A__23[26],A__23[26],A__23[26],A__23[26],A__23[26],A__23[26],A__23[26],A__23[26],A__23[26],A__23[26],A__23}),
        .CARRYCASCIN(1'b0),
        .CARRYCASCOUT(NLW_p_1_out__23_CARRYCASCOUT_UNCONNECTED),
        .CARRYIN(1'b0),
        .CARRYINSEL({1'b0,1'b0,1'b0}),
        .CARRYOUT(NLW_p_1_out__23_CARRYOUT_UNCONNECTED[3:0]),
        .CEA1(1'b0),
        .CEA2(1'b0),
        .CEAD(1'b0),
        .CEALUMODE(1'b0),
        .CEB1(1'b0),
        .CEB2(CEB2),
        .CEC(1'b0),
        .CECARRYIN(1'b0),
        .CECTRL(1'b0),
        .CED(1'b0),
        .CEINMODE(1'b0),
        .CEM(1'b0),
        .CEP(1'b0),
        .CLK(AXI4_Lite_ACLK),
        .D({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .INMODE({1'b0,1'b0,1'b0,1'b0,1'b0}),
        .MULTSIGNIN(1'b0),
        .MULTSIGNOUT(NLW_p_1_out__23_MULTSIGNOUT_UNCONNECTED),
        .OPMODE({1'b0,1'b0,1'b0,\out24[17] ,\out24[17] ,1'b0,1'b1,1'b0,1'b1}),
        .OVERFLOW(NLW_p_1_out__23_OVERFLOW_UNCONNECTED),
        .P({NLW_p_1_out__23_P_UNCONNECTED[47:45],p_1_out__23_n_61,p_1_out__23_n_62,p_1_out__23_n_63,p_1_out__23_n_64,p_1_out__23_n_65,p_1_out__23_n_66,p_1_out__23_n_67,p_1_out__23_n_68,p_1_out__23_n_69,p_1_out__23_n_70,out24,p_1_out__23_n_89,p_1_out__23_n_90,p_1_out__23_n_91,p_1_out__23_n_92,p_1_out__23_n_93,p_1_out__23_n_94,p_1_out__23_n_95,p_1_out__23_n_96,p_1_out__23_n_97,p_1_out__23_n_98,p_1_out__23_n_99,p_1_out__23_n_100,p_1_out__23_n_101,p_1_out__23_n_102,p_1_out__23_n_103,p_1_out__23_n_104,p_1_out__23_n_105}),
        .PATTERNBDETECT(NLW_p_1_out__23_PATTERNBDETECT_UNCONNECTED),
        .PATTERNDETECT(NLW_p_1_out__23_PATTERNDETECT_UNCONNECTED),
        .PCIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .PCOUT(NLW_p_1_out__23_PCOUT_UNCONNECTED[47:0]),
        .RSTA(1'b0),
        .RSTALLCARRYIN(1'b0),
        .RSTALUMODE(1'b0),
        .RSTB(reset),
        .RSTC(1'b0),
        .RSTCTRL(1'b0),
        .RSTD(1'b0),
        .RSTINMODE(1'b0),
        .RSTM(1'b0),
        .RSTP(1'b0),
        .UNDERFLOW(NLW_p_1_out__23_UNDERFLOW_UNCONNECTED),
        .XOROUT(NLW_p_1_out__23_XOROUT_UNCONNECTED[7:0]));
  (* SOFT_HLUTNM = "soft_lutpair356" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__23_i_10
       (.I0(in24[18]),
        .I1(Delay24_out1[18]),
        .I2(adc_trigger),
        .O(A__23[18]));
  (* SOFT_HLUTNM = "soft_lutpair355" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__23_i_11
       (.I0(in24[17]),
        .I1(Delay24_out1[17]),
        .I2(adc_trigger),
        .O(A__23[17]));
  (* SOFT_HLUTNM = "soft_lutpair355" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__23_i_12
       (.I0(in24[16]),
        .I1(Delay24_out1[16]),
        .I2(adc_trigger),
        .O(A__23[16]));
  (* SOFT_HLUTNM = "soft_lutpair354" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__23_i_13
       (.I0(in24[15]),
        .I1(Delay24_out1[15]),
        .I2(adc_trigger),
        .O(A__23[15]));
  (* SOFT_HLUTNM = "soft_lutpair354" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__23_i_14
       (.I0(in24[14]),
        .I1(Delay24_out1[14]),
        .I2(adc_trigger),
        .O(A__23[14]));
  (* SOFT_HLUTNM = "soft_lutpair353" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__23_i_15
       (.I0(in24[13]),
        .I1(Delay24_out1[13]),
        .I2(adc_trigger),
        .O(A__23[13]));
  (* SOFT_HLUTNM = "soft_lutpair353" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__23_i_16
       (.I0(in24[12]),
        .I1(Delay24_out1[12]),
        .I2(adc_trigger),
        .O(A__23[12]));
  (* SOFT_HLUTNM = "soft_lutpair352" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__23_i_17
       (.I0(in24[11]),
        .I1(Delay24_out1[11]),
        .I2(adc_trigger),
        .O(A__23[11]));
  (* SOFT_HLUTNM = "soft_lutpair352" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__23_i_18
       (.I0(in24[10]),
        .I1(Delay24_out1[10]),
        .I2(adc_trigger),
        .O(A__23[10]));
  (* SOFT_HLUTNM = "soft_lutpair351" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__23_i_19
       (.I0(in24[9]),
        .I1(Delay24_out1[9]),
        .I2(adc_trigger),
        .O(A__23[9]));
  (* SOFT_HLUTNM = "soft_lutpair360" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__23_i_2
       (.I0(in24[26]),
        .I1(Delay24_out1[26]),
        .I2(adc_trigger),
        .O(A__23[26]));
  (* SOFT_HLUTNM = "soft_lutpair351" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__23_i_20
       (.I0(in24[8]),
        .I1(Delay24_out1[8]),
        .I2(adc_trigger),
        .O(A__23[8]));
  (* SOFT_HLUTNM = "soft_lutpair350" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__23_i_21
       (.I0(in24[7]),
        .I1(Delay24_out1[7]),
        .I2(adc_trigger),
        .O(A__23[7]));
  (* SOFT_HLUTNM = "soft_lutpair350" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__23_i_22
       (.I0(in24[6]),
        .I1(Delay24_out1[6]),
        .I2(adc_trigger),
        .O(A__23[6]));
  (* SOFT_HLUTNM = "soft_lutpair349" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__23_i_23
       (.I0(in24[5]),
        .I1(Delay24_out1[5]),
        .I2(adc_trigger),
        .O(A__23[5]));
  (* SOFT_HLUTNM = "soft_lutpair349" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__23_i_24
       (.I0(in24[4]),
        .I1(Delay24_out1[4]),
        .I2(adc_trigger),
        .O(A__23[4]));
  (* SOFT_HLUTNM = "soft_lutpair348" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__23_i_25
       (.I0(in24[3]),
        .I1(Delay24_out1[3]),
        .I2(adc_trigger),
        .O(A__23[3]));
  (* SOFT_HLUTNM = "soft_lutpair348" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__23_i_26
       (.I0(in24[2]),
        .I1(Delay24_out1[2]),
        .I2(adc_trigger),
        .O(A__23[2]));
  (* SOFT_HLUTNM = "soft_lutpair347" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__23_i_27
       (.I0(in24[1]),
        .I1(Delay24_out1[1]),
        .I2(adc_trigger),
        .O(A__23[1]));
  (* SOFT_HLUTNM = "soft_lutpair347" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__23_i_28
       (.I0(in24[0]),
        .I1(Delay24_out1[0]),
        .I2(adc_trigger),
        .O(p_1_out__23_i_28_n_0));
  (* SOFT_HLUTNM = "soft_lutpair359" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__23_i_3
       (.I0(in24[25]),
        .I1(Delay24_out1[25]),
        .I2(adc_trigger),
        .O(A__23[25]));
  (* SOFT_HLUTNM = "soft_lutpair359" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__23_i_4
       (.I0(in24[24]),
        .I1(Delay24_out1[24]),
        .I2(adc_trigger),
        .O(A__23[24]));
  (* SOFT_HLUTNM = "soft_lutpair358" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__23_i_5
       (.I0(in24[23]),
        .I1(Delay24_out1[23]),
        .I2(adc_trigger),
        .O(A__23[23]));
  (* SOFT_HLUTNM = "soft_lutpair358" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__23_i_6
       (.I0(in24[22]),
        .I1(Delay24_out1[22]),
        .I2(adc_trigger),
        .O(A__23[22]));
  (* SOFT_HLUTNM = "soft_lutpair357" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__23_i_7
       (.I0(in24[21]),
        .I1(Delay24_out1[21]),
        .I2(adc_trigger),
        .O(A__23[21]));
  (* SOFT_HLUTNM = "soft_lutpair357" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__23_i_8
       (.I0(in24[20]),
        .I1(Delay24_out1[20]),
        .I2(adc_trigger),
        .O(A__23[20]));
  (* SOFT_HLUTNM = "soft_lutpair356" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__23_i_9
       (.I0(in24[19]),
        .I1(Delay24_out1[19]),
        .I2(adc_trigger),
        .O(A__23[19]));
  (* KEEP_HIERARCHY = "yes" *) 
  (* METHODOLOGY_DRC_VIOS = "{SYNTH-11 {cell *THIS*}}" *) 
  DSP48E2 #(
    .ACASCREG(0),
    .ADREG(1),
    .ALUMODEREG(0),
    .AMULTSEL("A"),
    .AREG(0),
    .AUTORESET_PATDET("NO_RESET"),
    .AUTORESET_PRIORITY("RESET"),
    .A_INPUT("DIRECT"),
    .BCASCREG(1),
    .BMULTSEL("B"),
    .BREG(1),
    .B_INPUT("DIRECT"),
    .CARRYINREG(0),
    .CARRYINSELREG(0),
    .CREG(0),
    .DREG(1),
    .INMODEREG(0),
    .MASK(48'h3FFFFFFFFFFF),
    .MREG(0),
    .OPMODEREG(0),
    .PATTERN(48'h000000000000),
    .PREADDINSEL("A"),
    .PREG(0),
    .RND(48'h000000000000),
    .SEL_MASK("MASK"),
    .SEL_PATTERN("PATTERN"),
    .USE_MULT("MULTIPLY"),
    .USE_PATTERN_DETECT("NO_PATDET"),
    .USE_SIMD("ONE48"),
    .USE_WIDEXOR("FALSE"),
    .XORSIMD("XOR24_48_96")) 
    p_1_out__24
       (.A({A__24[26],A__24[26],A__24[26],A__24,p_1_out__24_i_28_n_0}),
        .ACIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .ACOUT(NLW_p_1_out__24_ACOUT_UNCONNECTED[29:0]),
        .ALUMODE({1'b0,1'b0,1'b0,1'b0}),
        .B({1'b0,AXI_pu_conv_in31}),
        .BCIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .BCOUT(NLW_p_1_out__24_BCOUT_UNCONNECTED[17:0]),
        .C({A__24[26],A__24[26],A__24[26],A__24[26],A__24[26],A__24[26],A__24[26],A__24[26],A__24[26],A__24[26],A__24[26],A__24[26],A__24[26],A__24[26],A__24[26],A__24[26],A__24[26],A__24[26],A__24[26],A__24[26],A__24[26],A__24[26],A__24}),
        .CARRYCASCIN(1'b0),
        .CARRYCASCOUT(NLW_p_1_out__24_CARRYCASCOUT_UNCONNECTED),
        .CARRYIN(1'b0),
        .CARRYINSEL({1'b0,1'b0,1'b0}),
        .CARRYOUT(NLW_p_1_out__24_CARRYOUT_UNCONNECTED[3:0]),
        .CEA1(1'b0),
        .CEA2(1'b0),
        .CEAD(1'b0),
        .CEALUMODE(1'b0),
        .CEB1(1'b0),
        .CEB2(DSP_ALU_INST_23),
        .CEC(1'b0),
        .CECARRYIN(1'b0),
        .CECTRL(1'b0),
        .CED(1'b0),
        .CEINMODE(1'b0),
        .CEM(1'b0),
        .CEP(1'b0),
        .CLK(AXI4_Lite_ACLK),
        .D({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .INMODE({1'b0,1'b0,1'b0,1'b0,1'b0}),
        .MULTSIGNIN(1'b0),
        .MULTSIGNOUT(NLW_p_1_out__24_MULTSIGNOUT_UNCONNECTED),
        .OPMODE({1'b0,1'b0,1'b0,\out25[17] ,\out25[17] ,1'b0,1'b1,1'b0,1'b1}),
        .OVERFLOW(NLW_p_1_out__24_OVERFLOW_UNCONNECTED),
        .P({NLW_p_1_out__24_P_UNCONNECTED[47:45],p_1_out__24_n_61,p_1_out__24_n_62,p_1_out__24_n_63,p_1_out__24_n_64,p_1_out__24_n_65,p_1_out__24_n_66,p_1_out__24_n_67,p_1_out__24_n_68,p_1_out__24_n_69,p_1_out__24_n_70,out25,p_1_out__24_n_89,p_1_out__24_n_90,p_1_out__24_n_91,p_1_out__24_n_92,p_1_out__24_n_93,p_1_out__24_n_94,p_1_out__24_n_95,p_1_out__24_n_96,p_1_out__24_n_97,p_1_out__24_n_98,p_1_out__24_n_99,p_1_out__24_n_100,p_1_out__24_n_101,p_1_out__24_n_102,p_1_out__24_n_103,p_1_out__24_n_104,p_1_out__24_n_105}),
        .PATTERNBDETECT(NLW_p_1_out__24_PATTERNBDETECT_UNCONNECTED),
        .PATTERNDETECT(NLW_p_1_out__24_PATTERNDETECT_UNCONNECTED),
        .PCIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .PCOUT(NLW_p_1_out__24_PCOUT_UNCONNECTED[47:0]),
        .RSTA(1'b0),
        .RSTALLCARRYIN(1'b0),
        .RSTALUMODE(1'b0),
        .RSTB(reset),
        .RSTC(1'b0),
        .RSTCTRL(1'b0),
        .RSTD(1'b0),
        .RSTINMODE(1'b0),
        .RSTM(1'b0),
        .RSTP(1'b0),
        .UNDERFLOW(NLW_p_1_out__24_UNDERFLOW_UNCONNECTED),
        .XOROUT(NLW_p_1_out__24_XOROUT_UNCONNECTED[7:0]));
  (* SOFT_HLUTNM = "soft_lutpair369" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__24_i_10
       (.I0(in25[18]),
        .I1(Delay25_out1[18]),
        .I2(adc_trigger),
        .O(A__24[18]));
  (* SOFT_HLUTNM = "soft_lutpair369" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__24_i_11
       (.I0(in25[17]),
        .I1(Delay25_out1[17]),
        .I2(adc_trigger),
        .O(A__24[17]));
  (* SOFT_HLUTNM = "soft_lutpair368" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__24_i_12
       (.I0(in25[16]),
        .I1(Delay25_out1[16]),
        .I2(adc_trigger),
        .O(A__24[16]));
  (* SOFT_HLUTNM = "soft_lutpair368" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__24_i_13
       (.I0(in25[15]),
        .I1(Delay25_out1[15]),
        .I2(adc_trigger),
        .O(A__24[15]));
  (* SOFT_HLUTNM = "soft_lutpair367" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__24_i_14
       (.I0(in25[14]),
        .I1(Delay25_out1[14]),
        .I2(adc_trigger),
        .O(A__24[14]));
  (* SOFT_HLUTNM = "soft_lutpair367" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__24_i_15
       (.I0(in25[13]),
        .I1(Delay25_out1[13]),
        .I2(adc_trigger),
        .O(A__24[13]));
  (* SOFT_HLUTNM = "soft_lutpair366" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__24_i_16
       (.I0(in25[12]),
        .I1(Delay25_out1[12]),
        .I2(adc_trigger),
        .O(A__24[12]));
  (* SOFT_HLUTNM = "soft_lutpair366" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__24_i_17
       (.I0(in25[11]),
        .I1(Delay25_out1[11]),
        .I2(adc_trigger),
        .O(A__24[11]));
  (* SOFT_HLUTNM = "soft_lutpair365" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__24_i_18
       (.I0(in25[10]),
        .I1(Delay25_out1[10]),
        .I2(adc_trigger),
        .O(A__24[10]));
  (* SOFT_HLUTNM = "soft_lutpair365" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__24_i_19
       (.I0(in25[9]),
        .I1(Delay25_out1[9]),
        .I2(adc_trigger),
        .O(A__24[9]));
  (* SOFT_HLUTNM = "soft_lutpair373" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__24_i_2
       (.I0(in25[26]),
        .I1(Delay25_out1[26]),
        .I2(adc_trigger),
        .O(A__24[26]));
  (* SOFT_HLUTNM = "soft_lutpair364" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__24_i_20
       (.I0(in25[8]),
        .I1(Delay25_out1[8]),
        .I2(adc_trigger),
        .O(A__24[8]));
  (* SOFT_HLUTNM = "soft_lutpair364" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__24_i_21
       (.I0(in25[7]),
        .I1(Delay25_out1[7]),
        .I2(adc_trigger),
        .O(A__24[7]));
  (* SOFT_HLUTNM = "soft_lutpair363" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__24_i_22
       (.I0(in25[6]),
        .I1(Delay25_out1[6]),
        .I2(adc_trigger),
        .O(A__24[6]));
  (* SOFT_HLUTNM = "soft_lutpair363" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__24_i_23
       (.I0(in25[5]),
        .I1(Delay25_out1[5]),
        .I2(adc_trigger),
        .O(A__24[5]));
  (* SOFT_HLUTNM = "soft_lutpair362" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__24_i_24
       (.I0(in25[4]),
        .I1(Delay25_out1[4]),
        .I2(adc_trigger),
        .O(A__24[4]));
  (* SOFT_HLUTNM = "soft_lutpair362" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__24_i_25
       (.I0(in25[3]),
        .I1(Delay25_out1[3]),
        .I2(adc_trigger),
        .O(A__24[3]));
  (* SOFT_HLUTNM = "soft_lutpair361" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__24_i_26
       (.I0(in25[2]),
        .I1(Delay25_out1[2]),
        .I2(adc_trigger),
        .O(A__24[2]));
  (* SOFT_HLUTNM = "soft_lutpair361" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__24_i_27
       (.I0(in25[1]),
        .I1(Delay25_out1[1]),
        .I2(adc_trigger),
        .O(A__24[1]));
  (* SOFT_HLUTNM = "soft_lutpair360" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__24_i_28
       (.I0(in25[0]),
        .I1(Delay25_out1[0]),
        .I2(adc_trigger),
        .O(p_1_out__24_i_28_n_0));
  (* SOFT_HLUTNM = "soft_lutpair373" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__24_i_3
       (.I0(in25[25]),
        .I1(Delay25_out1[25]),
        .I2(adc_trigger),
        .O(A__24[25]));
  (* SOFT_HLUTNM = "soft_lutpair372" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__24_i_4
       (.I0(in25[24]),
        .I1(Delay25_out1[24]),
        .I2(adc_trigger),
        .O(A__24[24]));
  (* SOFT_HLUTNM = "soft_lutpair372" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__24_i_5
       (.I0(in25[23]),
        .I1(Delay25_out1[23]),
        .I2(adc_trigger),
        .O(A__24[23]));
  (* SOFT_HLUTNM = "soft_lutpair371" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__24_i_6
       (.I0(in25[22]),
        .I1(Delay25_out1[22]),
        .I2(adc_trigger),
        .O(A__24[22]));
  (* SOFT_HLUTNM = "soft_lutpair371" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__24_i_7
       (.I0(in25[21]),
        .I1(Delay25_out1[21]),
        .I2(adc_trigger),
        .O(A__24[21]));
  (* SOFT_HLUTNM = "soft_lutpair370" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__24_i_8
       (.I0(in25[20]),
        .I1(Delay25_out1[20]),
        .I2(adc_trigger),
        .O(A__24[20]));
  (* SOFT_HLUTNM = "soft_lutpair370" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__24_i_9
       (.I0(in25[19]),
        .I1(Delay25_out1[19]),
        .I2(adc_trigger),
        .O(A__24[19]));
  (* KEEP_HIERARCHY = "yes" *) 
  (* METHODOLOGY_DRC_VIOS = "{SYNTH-11 {cell *THIS*}}" *) 
  DSP48E2 #(
    .ACASCREG(0),
    .ADREG(1),
    .ALUMODEREG(0),
    .AMULTSEL("A"),
    .AREG(0),
    .AUTORESET_PATDET("NO_RESET"),
    .AUTORESET_PRIORITY("RESET"),
    .A_INPUT("DIRECT"),
    .BCASCREG(1),
    .BMULTSEL("B"),
    .BREG(1),
    .B_INPUT("DIRECT"),
    .CARRYINREG(0),
    .CARRYINSELREG(0),
    .CREG(0),
    .DREG(1),
    .INMODEREG(0),
    .MASK(48'h3FFFFFFFFFFF),
    .MREG(0),
    .OPMODEREG(0),
    .PATTERN(48'h000000000000),
    .PREADDINSEL("A"),
    .PREG(0),
    .RND(48'h000000000000),
    .SEL_MASK("MASK"),
    .SEL_PATTERN("PATTERN"),
    .USE_MULT("MULTIPLY"),
    .USE_PATTERN_DETECT("NO_PATDET"),
    .USE_SIMD("ONE48"),
    .USE_WIDEXOR("FALSE"),
    .XORSIMD("XOR24_48_96")) 
    p_1_out__25
       (.A({A__25[26],A__25[26],A__25[26],A__25,p_1_out__25_i_28_n_0}),
        .ACIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .ACOUT(NLW_p_1_out__25_ACOUT_UNCONNECTED[29:0]),
        .ALUMODE({1'b0,1'b0,1'b0,1'b0}),
        .B({1'b0,AXI_pu_conv_in31}),
        .BCIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .BCOUT(NLW_p_1_out__25_BCOUT_UNCONNECTED[17:0]),
        .C({A__25[26],A__25[26],A__25[26],A__25[26],A__25[26],A__25[26],A__25[26],A__25[26],A__25[26],A__25[26],A__25[26],A__25[26],A__25[26],A__25[26],A__25[26],A__25[26],A__25[26],A__25[26],A__25[26],A__25[26],A__25[26],A__25[26],A__25}),
        .CARRYCASCIN(1'b0),
        .CARRYCASCOUT(NLW_p_1_out__25_CARRYCASCOUT_UNCONNECTED),
        .CARRYIN(1'b0),
        .CARRYINSEL({1'b0,1'b0,1'b0}),
        .CARRYOUT(NLW_p_1_out__25_CARRYOUT_UNCONNECTED[3:0]),
        .CEA1(1'b0),
        .CEA2(1'b0),
        .CEAD(1'b0),
        .CEALUMODE(1'b0),
        .CEB1(1'b0),
        .CEB2(DSP_ALU_INST_24),
        .CEC(1'b0),
        .CECARRYIN(1'b0),
        .CECTRL(1'b0),
        .CED(1'b0),
        .CEINMODE(1'b0),
        .CEM(1'b0),
        .CEP(1'b0),
        .CLK(AXI4_Lite_ACLK),
        .D({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .INMODE({1'b0,1'b0,1'b0,1'b0,1'b0}),
        .MULTSIGNIN(1'b0),
        .MULTSIGNOUT(NLW_p_1_out__25_MULTSIGNOUT_UNCONNECTED),
        .OPMODE({1'b0,1'b0,1'b0,\out26[17] ,\out26[17] ,1'b0,1'b1,1'b0,1'b1}),
        .OVERFLOW(NLW_p_1_out__25_OVERFLOW_UNCONNECTED),
        .P({NLW_p_1_out__25_P_UNCONNECTED[47:45],p_1_out__25_n_61,p_1_out__25_n_62,p_1_out__25_n_63,p_1_out__25_n_64,p_1_out__25_n_65,p_1_out__25_n_66,p_1_out__25_n_67,p_1_out__25_n_68,p_1_out__25_n_69,p_1_out__25_n_70,out26,p_1_out__25_n_89,p_1_out__25_n_90,p_1_out__25_n_91,p_1_out__25_n_92,p_1_out__25_n_93,p_1_out__25_n_94,p_1_out__25_n_95,p_1_out__25_n_96,p_1_out__25_n_97,p_1_out__25_n_98,p_1_out__25_n_99,p_1_out__25_n_100,p_1_out__25_n_101,p_1_out__25_n_102,p_1_out__25_n_103,p_1_out__25_n_104,p_1_out__25_n_105}),
        .PATTERNBDETECT(NLW_p_1_out__25_PATTERNBDETECT_UNCONNECTED),
        .PATTERNDETECT(NLW_p_1_out__25_PATTERNDETECT_UNCONNECTED),
        .PCIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .PCOUT(NLW_p_1_out__25_PCOUT_UNCONNECTED[47:0]),
        .RSTA(1'b0),
        .RSTALLCARRYIN(1'b0),
        .RSTALUMODE(1'b0),
        .RSTB(reset),
        .RSTC(1'b0),
        .RSTCTRL(1'b0),
        .RSTD(1'b0),
        .RSTINMODE(1'b0),
        .RSTM(1'b0),
        .RSTP(1'b0),
        .UNDERFLOW(NLW_p_1_out__25_UNDERFLOW_UNCONNECTED),
        .XOROUT(NLW_p_1_out__25_XOROUT_UNCONNECTED[7:0]));
  (* SOFT_HLUTNM = "soft_lutpair383" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__25_i_10
       (.I0(in26[18]),
        .I1(Delay26_out1[18]),
        .I2(adc_trigger),
        .O(A__25[18]));
  (* SOFT_HLUTNM = "soft_lutpair382" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__25_i_11
       (.I0(in26[17]),
        .I1(Delay26_out1[17]),
        .I2(adc_trigger),
        .O(A__25[17]));
  (* SOFT_HLUTNM = "soft_lutpair382" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__25_i_12
       (.I0(in26[16]),
        .I1(Delay26_out1[16]),
        .I2(adc_trigger),
        .O(A__25[16]));
  (* SOFT_HLUTNM = "soft_lutpair381" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__25_i_13
       (.I0(in26[15]),
        .I1(Delay26_out1[15]),
        .I2(adc_trigger),
        .O(A__25[15]));
  (* SOFT_HLUTNM = "soft_lutpair381" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__25_i_14
       (.I0(in26[14]),
        .I1(Delay26_out1[14]),
        .I2(adc_trigger),
        .O(A__25[14]));
  (* SOFT_HLUTNM = "soft_lutpair380" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__25_i_15
       (.I0(in26[13]),
        .I1(Delay26_out1[13]),
        .I2(adc_trigger),
        .O(A__25[13]));
  (* SOFT_HLUTNM = "soft_lutpair380" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__25_i_16
       (.I0(in26[12]),
        .I1(Delay26_out1[12]),
        .I2(adc_trigger),
        .O(A__25[12]));
  (* SOFT_HLUTNM = "soft_lutpair379" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__25_i_17
       (.I0(in26[11]),
        .I1(Delay26_out1[11]),
        .I2(adc_trigger),
        .O(A__25[11]));
  (* SOFT_HLUTNM = "soft_lutpair379" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__25_i_18
       (.I0(in26[10]),
        .I1(Delay26_out1[10]),
        .I2(adc_trigger),
        .O(A__25[10]));
  (* SOFT_HLUTNM = "soft_lutpair378" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__25_i_19
       (.I0(in26[9]),
        .I1(Delay26_out1[9]),
        .I2(adc_trigger),
        .O(A__25[9]));
  (* SOFT_HLUTNM = "soft_lutpair387" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__25_i_2
       (.I0(in26[26]),
        .I1(Delay26_out1[26]),
        .I2(adc_trigger),
        .O(A__25[26]));
  (* SOFT_HLUTNM = "soft_lutpair378" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__25_i_20
       (.I0(in26[8]),
        .I1(Delay26_out1[8]),
        .I2(adc_trigger),
        .O(A__25[8]));
  (* SOFT_HLUTNM = "soft_lutpair377" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__25_i_21
       (.I0(in26[7]),
        .I1(Delay26_out1[7]),
        .I2(adc_trigger),
        .O(A__25[7]));
  (* SOFT_HLUTNM = "soft_lutpair377" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__25_i_22
       (.I0(in26[6]),
        .I1(Delay26_out1[6]),
        .I2(adc_trigger),
        .O(A__25[6]));
  (* SOFT_HLUTNM = "soft_lutpair376" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__25_i_23
       (.I0(in26[5]),
        .I1(Delay26_out1[5]),
        .I2(adc_trigger),
        .O(A__25[5]));
  (* SOFT_HLUTNM = "soft_lutpair376" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__25_i_24
       (.I0(in26[4]),
        .I1(Delay26_out1[4]),
        .I2(adc_trigger),
        .O(A__25[4]));
  (* SOFT_HLUTNM = "soft_lutpair375" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__25_i_25
       (.I0(in26[3]),
        .I1(Delay26_out1[3]),
        .I2(adc_trigger),
        .O(A__25[3]));
  (* SOFT_HLUTNM = "soft_lutpair375" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__25_i_26
       (.I0(in26[2]),
        .I1(Delay26_out1[2]),
        .I2(adc_trigger),
        .O(A__25[2]));
  (* SOFT_HLUTNM = "soft_lutpair374" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__25_i_27
       (.I0(in26[1]),
        .I1(Delay26_out1[1]),
        .I2(adc_trigger),
        .O(A__25[1]));
  (* SOFT_HLUTNM = "soft_lutpair374" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__25_i_28
       (.I0(in26[0]),
        .I1(Delay26_out1[0]),
        .I2(adc_trigger),
        .O(p_1_out__25_i_28_n_0));
  (* SOFT_HLUTNM = "soft_lutpair386" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__25_i_3
       (.I0(in26[25]),
        .I1(Delay26_out1[25]),
        .I2(adc_trigger),
        .O(A__25[25]));
  (* SOFT_HLUTNM = "soft_lutpair386" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__25_i_4
       (.I0(in26[24]),
        .I1(Delay26_out1[24]),
        .I2(adc_trigger),
        .O(A__25[24]));
  (* SOFT_HLUTNM = "soft_lutpair385" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__25_i_5
       (.I0(in26[23]),
        .I1(Delay26_out1[23]),
        .I2(adc_trigger),
        .O(A__25[23]));
  (* SOFT_HLUTNM = "soft_lutpair385" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__25_i_6
       (.I0(in26[22]),
        .I1(Delay26_out1[22]),
        .I2(adc_trigger),
        .O(A__25[22]));
  (* SOFT_HLUTNM = "soft_lutpair384" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__25_i_7
       (.I0(in26[21]),
        .I1(Delay26_out1[21]),
        .I2(adc_trigger),
        .O(A__25[21]));
  (* SOFT_HLUTNM = "soft_lutpair384" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__25_i_8
       (.I0(in26[20]),
        .I1(Delay26_out1[20]),
        .I2(adc_trigger),
        .O(A__25[20]));
  (* SOFT_HLUTNM = "soft_lutpair383" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__25_i_9
       (.I0(in26[19]),
        .I1(Delay26_out1[19]),
        .I2(adc_trigger),
        .O(A__25[19]));
  (* KEEP_HIERARCHY = "yes" *) 
  (* METHODOLOGY_DRC_VIOS = "{SYNTH-11 {cell *THIS*}}" *) 
  DSP48E2 #(
    .ACASCREG(0),
    .ADREG(1),
    .ALUMODEREG(0),
    .AMULTSEL("A"),
    .AREG(0),
    .AUTORESET_PATDET("NO_RESET"),
    .AUTORESET_PRIORITY("RESET"),
    .A_INPUT("DIRECT"),
    .BCASCREG(1),
    .BMULTSEL("B"),
    .BREG(1),
    .B_INPUT("DIRECT"),
    .CARRYINREG(0),
    .CARRYINSELREG(0),
    .CREG(0),
    .DREG(1),
    .INMODEREG(0),
    .MASK(48'h3FFFFFFFFFFF),
    .MREG(0),
    .OPMODEREG(0),
    .PATTERN(48'h000000000000),
    .PREADDINSEL("A"),
    .PREG(0),
    .RND(48'h000000000000),
    .SEL_MASK("MASK"),
    .SEL_PATTERN("PATTERN"),
    .USE_MULT("MULTIPLY"),
    .USE_PATTERN_DETECT("NO_PATDET"),
    .USE_SIMD("ONE48"),
    .USE_WIDEXOR("FALSE"),
    .XORSIMD("XOR24_48_96")) 
    p_1_out__26
       (.A({A__26[26],A__26[26],A__26[26],A__26,p_1_out__26_i_28_n_0}),
        .ACIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .ACOUT(NLW_p_1_out__26_ACOUT_UNCONNECTED[29:0]),
        .ALUMODE({1'b0,1'b0,1'b0,1'b0}),
        .B({1'b0,AXI_pu_conv_in31}),
        .BCIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .BCOUT(NLW_p_1_out__26_BCOUT_UNCONNECTED[17:0]),
        .C({A__26[26],A__26[26],A__26[26],A__26[26],A__26[26],A__26[26],A__26[26],A__26[26],A__26[26],A__26[26],A__26[26],A__26[26],A__26[26],A__26[26],A__26[26],A__26[26],A__26[26],A__26[26],A__26[26],A__26[26],A__26[26],A__26[26],A__26}),
        .CARRYCASCIN(1'b0),
        .CARRYCASCOUT(NLW_p_1_out__26_CARRYCASCOUT_UNCONNECTED),
        .CARRYIN(1'b0),
        .CARRYINSEL({1'b0,1'b0,1'b0}),
        .CARRYOUT(NLW_p_1_out__26_CARRYOUT_UNCONNECTED[3:0]),
        .CEA1(1'b0),
        .CEA2(1'b0),
        .CEAD(1'b0),
        .CEALUMODE(1'b0),
        .CEB1(1'b0),
        .CEB2(DSP_ALU_INST_25),
        .CEC(1'b0),
        .CECARRYIN(1'b0),
        .CECTRL(1'b0),
        .CED(1'b0),
        .CEINMODE(1'b0),
        .CEM(1'b0),
        .CEP(1'b0),
        .CLK(AXI4_Lite_ACLK),
        .D({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .INMODE({1'b0,1'b0,1'b0,1'b0,1'b0}),
        .MULTSIGNIN(1'b0),
        .MULTSIGNOUT(NLW_p_1_out__26_MULTSIGNOUT_UNCONNECTED),
        .OPMODE({1'b0,1'b0,1'b0,\out27[17] ,\out27[17] ,1'b0,1'b1,1'b0,1'b1}),
        .OVERFLOW(NLW_p_1_out__26_OVERFLOW_UNCONNECTED),
        .P({NLW_p_1_out__26_P_UNCONNECTED[47:45],p_1_out__26_n_61,p_1_out__26_n_62,p_1_out__26_n_63,p_1_out__26_n_64,p_1_out__26_n_65,p_1_out__26_n_66,p_1_out__26_n_67,p_1_out__26_n_68,p_1_out__26_n_69,p_1_out__26_n_70,out27,p_1_out__26_n_89,p_1_out__26_n_90,p_1_out__26_n_91,p_1_out__26_n_92,p_1_out__26_n_93,p_1_out__26_n_94,p_1_out__26_n_95,p_1_out__26_n_96,p_1_out__26_n_97,p_1_out__26_n_98,p_1_out__26_n_99,p_1_out__26_n_100,p_1_out__26_n_101,p_1_out__26_n_102,p_1_out__26_n_103,p_1_out__26_n_104,p_1_out__26_n_105}),
        .PATTERNBDETECT(NLW_p_1_out__26_PATTERNBDETECT_UNCONNECTED),
        .PATTERNDETECT(NLW_p_1_out__26_PATTERNDETECT_UNCONNECTED),
        .PCIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .PCOUT(NLW_p_1_out__26_PCOUT_UNCONNECTED[47:0]),
        .RSTA(1'b0),
        .RSTALLCARRYIN(1'b0),
        .RSTALUMODE(1'b0),
        .RSTB(reset),
        .RSTC(1'b0),
        .RSTCTRL(1'b0),
        .RSTD(1'b0),
        .RSTINMODE(1'b0),
        .RSTM(1'b0),
        .RSTP(1'b0),
        .UNDERFLOW(NLW_p_1_out__26_UNDERFLOW_UNCONNECTED),
        .XOROUT(NLW_p_1_out__26_XOROUT_UNCONNECTED[7:0]));
  (* SOFT_HLUTNM = "soft_lutpair396" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__26_i_10
       (.I0(in27[18]),
        .I1(Delay27_out1[18]),
        .I2(adc_trigger),
        .O(A__26[18]));
  (* SOFT_HLUTNM = "soft_lutpair396" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__26_i_11
       (.I0(in27[17]),
        .I1(Delay27_out1[17]),
        .I2(adc_trigger),
        .O(A__26[17]));
  (* SOFT_HLUTNM = "soft_lutpair395" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__26_i_12
       (.I0(in27[16]),
        .I1(Delay27_out1[16]),
        .I2(adc_trigger),
        .O(A__26[16]));
  (* SOFT_HLUTNM = "soft_lutpair395" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__26_i_13
       (.I0(in27[15]),
        .I1(Delay27_out1[15]),
        .I2(adc_trigger),
        .O(A__26[15]));
  (* SOFT_HLUTNM = "soft_lutpair394" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__26_i_14
       (.I0(in27[14]),
        .I1(Delay27_out1[14]),
        .I2(adc_trigger),
        .O(A__26[14]));
  (* SOFT_HLUTNM = "soft_lutpair394" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__26_i_15
       (.I0(in27[13]),
        .I1(Delay27_out1[13]),
        .I2(adc_trigger),
        .O(A__26[13]));
  (* SOFT_HLUTNM = "soft_lutpair393" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__26_i_16
       (.I0(in27[12]),
        .I1(Delay27_out1[12]),
        .I2(adc_trigger),
        .O(A__26[12]));
  (* SOFT_HLUTNM = "soft_lutpair393" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__26_i_17
       (.I0(in27[11]),
        .I1(Delay27_out1[11]),
        .I2(adc_trigger),
        .O(A__26[11]));
  (* SOFT_HLUTNM = "soft_lutpair392" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__26_i_18
       (.I0(in27[10]),
        .I1(Delay27_out1[10]),
        .I2(adc_trigger),
        .O(A__26[10]));
  (* SOFT_HLUTNM = "soft_lutpair392" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__26_i_19
       (.I0(in27[9]),
        .I1(Delay27_out1[9]),
        .I2(adc_trigger),
        .O(A__26[9]));
  (* SOFT_HLUTNM = "soft_lutpair400" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__26_i_2
       (.I0(in27[26]),
        .I1(Delay27_out1[26]),
        .I2(adc_trigger),
        .O(A__26[26]));
  (* SOFT_HLUTNM = "soft_lutpair391" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__26_i_20
       (.I0(in27[8]),
        .I1(Delay27_out1[8]),
        .I2(adc_trigger),
        .O(A__26[8]));
  (* SOFT_HLUTNM = "soft_lutpair391" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__26_i_21
       (.I0(in27[7]),
        .I1(Delay27_out1[7]),
        .I2(adc_trigger),
        .O(A__26[7]));
  (* SOFT_HLUTNM = "soft_lutpair390" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__26_i_22
       (.I0(in27[6]),
        .I1(Delay27_out1[6]),
        .I2(adc_trigger),
        .O(A__26[6]));
  (* SOFT_HLUTNM = "soft_lutpair390" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__26_i_23
       (.I0(in27[5]),
        .I1(Delay27_out1[5]),
        .I2(adc_trigger),
        .O(A__26[5]));
  (* SOFT_HLUTNM = "soft_lutpair389" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__26_i_24
       (.I0(in27[4]),
        .I1(Delay27_out1[4]),
        .I2(adc_trigger),
        .O(A__26[4]));
  (* SOFT_HLUTNM = "soft_lutpair389" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__26_i_25
       (.I0(in27[3]),
        .I1(Delay27_out1[3]),
        .I2(adc_trigger),
        .O(A__26[3]));
  (* SOFT_HLUTNM = "soft_lutpair388" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__26_i_26
       (.I0(in27[2]),
        .I1(Delay27_out1[2]),
        .I2(adc_trigger),
        .O(A__26[2]));
  (* SOFT_HLUTNM = "soft_lutpair388" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__26_i_27
       (.I0(in27[1]),
        .I1(Delay27_out1[1]),
        .I2(adc_trigger),
        .O(A__26[1]));
  (* SOFT_HLUTNM = "soft_lutpair387" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__26_i_28
       (.I0(in27[0]),
        .I1(Delay27_out1[0]),
        .I2(adc_trigger),
        .O(p_1_out__26_i_28_n_0));
  (* SOFT_HLUTNM = "soft_lutpair400" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__26_i_3
       (.I0(in27[25]),
        .I1(Delay27_out1[25]),
        .I2(adc_trigger),
        .O(A__26[25]));
  (* SOFT_HLUTNM = "soft_lutpair399" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__26_i_4
       (.I0(in27[24]),
        .I1(Delay27_out1[24]),
        .I2(adc_trigger),
        .O(A__26[24]));
  (* SOFT_HLUTNM = "soft_lutpair399" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__26_i_5
       (.I0(in27[23]),
        .I1(Delay27_out1[23]),
        .I2(adc_trigger),
        .O(A__26[23]));
  (* SOFT_HLUTNM = "soft_lutpair398" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__26_i_6
       (.I0(in27[22]),
        .I1(Delay27_out1[22]),
        .I2(adc_trigger),
        .O(A__26[22]));
  (* SOFT_HLUTNM = "soft_lutpair398" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__26_i_7
       (.I0(in27[21]),
        .I1(Delay27_out1[21]),
        .I2(adc_trigger),
        .O(A__26[21]));
  (* SOFT_HLUTNM = "soft_lutpair397" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__26_i_8
       (.I0(in27[20]),
        .I1(Delay27_out1[20]),
        .I2(adc_trigger),
        .O(A__26[20]));
  (* SOFT_HLUTNM = "soft_lutpair397" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__26_i_9
       (.I0(in27[19]),
        .I1(Delay27_out1[19]),
        .I2(adc_trigger),
        .O(A__26[19]));
  (* KEEP_HIERARCHY = "yes" *) 
  (* METHODOLOGY_DRC_VIOS = "{SYNTH-11 {cell *THIS*}}" *) 
  DSP48E2 #(
    .ACASCREG(0),
    .ADREG(1),
    .ALUMODEREG(0),
    .AMULTSEL("A"),
    .AREG(0),
    .AUTORESET_PATDET("NO_RESET"),
    .AUTORESET_PRIORITY("RESET"),
    .A_INPUT("DIRECT"),
    .BCASCREG(1),
    .BMULTSEL("B"),
    .BREG(1),
    .B_INPUT("DIRECT"),
    .CARRYINREG(0),
    .CARRYINSELREG(0),
    .CREG(0),
    .DREG(1),
    .INMODEREG(0),
    .MASK(48'h3FFFFFFFFFFF),
    .MREG(0),
    .OPMODEREG(0),
    .PATTERN(48'h000000000000),
    .PREADDINSEL("A"),
    .PREG(0),
    .RND(48'h000000000000),
    .SEL_MASK("MASK"),
    .SEL_PATTERN("PATTERN"),
    .USE_MULT("MULTIPLY"),
    .USE_PATTERN_DETECT("NO_PATDET"),
    .USE_SIMD("ONE48"),
    .USE_WIDEXOR("FALSE"),
    .XORSIMD("XOR24_48_96")) 
    p_1_out__27
       (.A({A__27[26],A__27[26],A__27[26],A__27,p_1_out__27_i_28_n_0}),
        .ACIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .ACOUT(NLW_p_1_out__27_ACOUT_UNCONNECTED[29:0]),
        .ALUMODE({1'b0,1'b0,1'b0,1'b0}),
        .B({1'b0,AXI_pu_conv_in31}),
        .BCIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .BCOUT(NLW_p_1_out__27_BCOUT_UNCONNECTED[17:0]),
        .C({A__27[26],A__27[26],A__27[26],A__27[26],A__27[26],A__27[26],A__27[26],A__27[26],A__27[26],A__27[26],A__27[26],A__27[26],A__27[26],A__27[26],A__27[26],A__27[26],A__27[26],A__27[26],A__27[26],A__27[26],A__27[26],A__27[26],A__27}),
        .CARRYCASCIN(1'b0),
        .CARRYCASCOUT(NLW_p_1_out__27_CARRYCASCOUT_UNCONNECTED),
        .CARRYIN(1'b0),
        .CARRYINSEL({1'b0,1'b0,1'b0}),
        .CARRYOUT(NLW_p_1_out__27_CARRYOUT_UNCONNECTED[3:0]),
        .CEA1(1'b0),
        .CEA2(1'b0),
        .CEAD(1'b0),
        .CEALUMODE(1'b0),
        .CEB1(1'b0),
        .CEB2(DSP_ALU_INST_26),
        .CEC(1'b0),
        .CECARRYIN(1'b0),
        .CECTRL(1'b0),
        .CED(1'b0),
        .CEINMODE(1'b0),
        .CEM(1'b0),
        .CEP(1'b0),
        .CLK(AXI4_Lite_ACLK),
        .D({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .INMODE({1'b0,1'b0,1'b0,1'b0,1'b0}),
        .MULTSIGNIN(1'b0),
        .MULTSIGNOUT(NLW_p_1_out__27_MULTSIGNOUT_UNCONNECTED),
        .OPMODE({1'b0,1'b0,1'b0,\out28[17] ,\out28[17] ,1'b0,1'b1,1'b0,1'b1}),
        .OVERFLOW(NLW_p_1_out__27_OVERFLOW_UNCONNECTED),
        .P({NLW_p_1_out__27_P_UNCONNECTED[47:45],p_1_out__27_n_61,p_1_out__27_n_62,p_1_out__27_n_63,p_1_out__27_n_64,p_1_out__27_n_65,p_1_out__27_n_66,p_1_out__27_n_67,p_1_out__27_n_68,p_1_out__27_n_69,p_1_out__27_n_70,out28,p_1_out__27_n_89,p_1_out__27_n_90,p_1_out__27_n_91,p_1_out__27_n_92,p_1_out__27_n_93,p_1_out__27_n_94,p_1_out__27_n_95,p_1_out__27_n_96,p_1_out__27_n_97,p_1_out__27_n_98,p_1_out__27_n_99,p_1_out__27_n_100,p_1_out__27_n_101,p_1_out__27_n_102,p_1_out__27_n_103,p_1_out__27_n_104,p_1_out__27_n_105}),
        .PATTERNBDETECT(NLW_p_1_out__27_PATTERNBDETECT_UNCONNECTED),
        .PATTERNDETECT(NLW_p_1_out__27_PATTERNDETECT_UNCONNECTED),
        .PCIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .PCOUT(NLW_p_1_out__27_PCOUT_UNCONNECTED[47:0]),
        .RSTA(1'b0),
        .RSTALLCARRYIN(1'b0),
        .RSTALUMODE(1'b0),
        .RSTB(reset),
        .RSTC(1'b0),
        .RSTCTRL(1'b0),
        .RSTD(1'b0),
        .RSTINMODE(1'b0),
        .RSTM(1'b0),
        .RSTP(1'b0),
        .UNDERFLOW(NLW_p_1_out__27_UNDERFLOW_UNCONNECTED),
        .XOROUT(NLW_p_1_out__27_XOROUT_UNCONNECTED[7:0]));
  (* SOFT_HLUTNM = "soft_lutpair410" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__27_i_10
       (.I0(in28[18]),
        .I1(Delay28_out1[18]),
        .I2(adc_trigger),
        .O(A__27[18]));
  (* SOFT_HLUTNM = "soft_lutpair409" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__27_i_11
       (.I0(in28[17]),
        .I1(Delay28_out1[17]),
        .I2(adc_trigger),
        .O(A__27[17]));
  (* SOFT_HLUTNM = "soft_lutpair409" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__27_i_12
       (.I0(in28[16]),
        .I1(Delay28_out1[16]),
        .I2(adc_trigger),
        .O(A__27[16]));
  (* SOFT_HLUTNM = "soft_lutpair408" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__27_i_13
       (.I0(in28[15]),
        .I1(Delay28_out1[15]),
        .I2(adc_trigger),
        .O(A__27[15]));
  (* SOFT_HLUTNM = "soft_lutpair408" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__27_i_14
       (.I0(in28[14]),
        .I1(Delay28_out1[14]),
        .I2(adc_trigger),
        .O(A__27[14]));
  (* SOFT_HLUTNM = "soft_lutpair407" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__27_i_15
       (.I0(in28[13]),
        .I1(Delay28_out1[13]),
        .I2(adc_trigger),
        .O(A__27[13]));
  (* SOFT_HLUTNM = "soft_lutpair407" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__27_i_16
       (.I0(in28[12]),
        .I1(Delay28_out1[12]),
        .I2(adc_trigger),
        .O(A__27[12]));
  (* SOFT_HLUTNM = "soft_lutpair406" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__27_i_17
       (.I0(in28[11]),
        .I1(Delay28_out1[11]),
        .I2(adc_trigger),
        .O(A__27[11]));
  (* SOFT_HLUTNM = "soft_lutpair406" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__27_i_18
       (.I0(in28[10]),
        .I1(Delay28_out1[10]),
        .I2(adc_trigger),
        .O(A__27[10]));
  (* SOFT_HLUTNM = "soft_lutpair405" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__27_i_19
       (.I0(in28[9]),
        .I1(Delay28_out1[9]),
        .I2(adc_trigger),
        .O(A__27[9]));
  (* SOFT_HLUTNM = "soft_lutpair414" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__27_i_2
       (.I0(in28[26]),
        .I1(Delay28_out1[26]),
        .I2(adc_trigger),
        .O(A__27[26]));
  (* SOFT_HLUTNM = "soft_lutpair405" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__27_i_20
       (.I0(in28[8]),
        .I1(Delay28_out1[8]),
        .I2(adc_trigger),
        .O(A__27[8]));
  (* SOFT_HLUTNM = "soft_lutpair404" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__27_i_21
       (.I0(in28[7]),
        .I1(Delay28_out1[7]),
        .I2(adc_trigger),
        .O(A__27[7]));
  (* SOFT_HLUTNM = "soft_lutpair404" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__27_i_22
       (.I0(in28[6]),
        .I1(Delay28_out1[6]),
        .I2(adc_trigger),
        .O(A__27[6]));
  (* SOFT_HLUTNM = "soft_lutpair403" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__27_i_23
       (.I0(in28[5]),
        .I1(Delay28_out1[5]),
        .I2(adc_trigger),
        .O(A__27[5]));
  (* SOFT_HLUTNM = "soft_lutpair403" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__27_i_24
       (.I0(in28[4]),
        .I1(Delay28_out1[4]),
        .I2(adc_trigger),
        .O(A__27[4]));
  (* SOFT_HLUTNM = "soft_lutpair402" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__27_i_25
       (.I0(in28[3]),
        .I1(Delay28_out1[3]),
        .I2(adc_trigger),
        .O(A__27[3]));
  (* SOFT_HLUTNM = "soft_lutpair402" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__27_i_26
       (.I0(in28[2]),
        .I1(Delay28_out1[2]),
        .I2(adc_trigger),
        .O(A__27[2]));
  (* SOFT_HLUTNM = "soft_lutpair401" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__27_i_27
       (.I0(in28[1]),
        .I1(Delay28_out1[1]),
        .I2(adc_trigger),
        .O(A__27[1]));
  (* SOFT_HLUTNM = "soft_lutpair401" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__27_i_28
       (.I0(in28[0]),
        .I1(Delay28_out1[0]),
        .I2(adc_trigger),
        .O(p_1_out__27_i_28_n_0));
  (* SOFT_HLUTNM = "soft_lutpair413" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__27_i_3
       (.I0(in28[25]),
        .I1(Delay28_out1[25]),
        .I2(adc_trigger),
        .O(A__27[25]));
  (* SOFT_HLUTNM = "soft_lutpair413" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__27_i_4
       (.I0(in28[24]),
        .I1(Delay28_out1[24]),
        .I2(adc_trigger),
        .O(A__27[24]));
  (* SOFT_HLUTNM = "soft_lutpair412" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__27_i_5
       (.I0(in28[23]),
        .I1(Delay28_out1[23]),
        .I2(adc_trigger),
        .O(A__27[23]));
  (* SOFT_HLUTNM = "soft_lutpair412" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__27_i_6
       (.I0(in28[22]),
        .I1(Delay28_out1[22]),
        .I2(adc_trigger),
        .O(A__27[22]));
  (* SOFT_HLUTNM = "soft_lutpair411" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__27_i_7
       (.I0(in28[21]),
        .I1(Delay28_out1[21]),
        .I2(adc_trigger),
        .O(A__27[21]));
  (* SOFT_HLUTNM = "soft_lutpair411" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__27_i_8
       (.I0(in28[20]),
        .I1(Delay28_out1[20]),
        .I2(adc_trigger),
        .O(A__27[20]));
  (* SOFT_HLUTNM = "soft_lutpair410" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__27_i_9
       (.I0(in28[19]),
        .I1(Delay28_out1[19]),
        .I2(adc_trigger),
        .O(A__27[19]));
  (* KEEP_HIERARCHY = "yes" *) 
  (* METHODOLOGY_DRC_VIOS = "{SYNTH-11 {cell *THIS*}}" *) 
  DSP48E2 #(
    .ACASCREG(0),
    .ADREG(1),
    .ALUMODEREG(0),
    .AMULTSEL("A"),
    .AREG(0),
    .AUTORESET_PATDET("NO_RESET"),
    .AUTORESET_PRIORITY("RESET"),
    .A_INPUT("DIRECT"),
    .BCASCREG(1),
    .BMULTSEL("B"),
    .BREG(1),
    .B_INPUT("DIRECT"),
    .CARRYINREG(0),
    .CARRYINSELREG(0),
    .CREG(0),
    .DREG(1),
    .INMODEREG(0),
    .MASK(48'h3FFFFFFFFFFF),
    .MREG(0),
    .OPMODEREG(0),
    .PATTERN(48'h000000000000),
    .PREADDINSEL("A"),
    .PREG(0),
    .RND(48'h000000000000),
    .SEL_MASK("MASK"),
    .SEL_PATTERN("PATTERN"),
    .USE_MULT("MULTIPLY"),
    .USE_PATTERN_DETECT("NO_PATDET"),
    .USE_SIMD("ONE48"),
    .USE_WIDEXOR("FALSE"),
    .XORSIMD("XOR24_48_96")) 
    p_1_out__28
       (.A({A__28[26],A__28[26],A__28[26],A__28,p_1_out__28_i_28_n_0}),
        .ACIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .ACOUT(NLW_p_1_out__28_ACOUT_UNCONNECTED[29:0]),
        .ALUMODE({1'b0,1'b0,1'b0,1'b0}),
        .B({1'b0,AXI_pu_conv_in31}),
        .BCIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .BCOUT(NLW_p_1_out__28_BCOUT_UNCONNECTED[17:0]),
        .C({A__28[26],A__28[26],A__28[26],A__28[26],A__28[26],A__28[26],A__28[26],A__28[26],A__28[26],A__28[26],A__28[26],A__28[26],A__28[26],A__28[26],A__28[26],A__28[26],A__28[26],A__28[26],A__28[26],A__28[26],A__28[26],A__28[26],A__28}),
        .CARRYCASCIN(1'b0),
        .CARRYCASCOUT(NLW_p_1_out__28_CARRYCASCOUT_UNCONNECTED),
        .CARRYIN(1'b0),
        .CARRYINSEL({1'b0,1'b0,1'b0}),
        .CARRYOUT(NLW_p_1_out__28_CARRYOUT_UNCONNECTED[3:0]),
        .CEA1(1'b0),
        .CEA2(1'b0),
        .CEAD(1'b0),
        .CEALUMODE(1'b0),
        .CEB1(1'b0),
        .CEB2(DSP_ALU_INST_27),
        .CEC(1'b0),
        .CECARRYIN(1'b0),
        .CECTRL(1'b0),
        .CED(1'b0),
        .CEINMODE(1'b0),
        .CEM(1'b0),
        .CEP(1'b0),
        .CLK(AXI4_Lite_ACLK),
        .D({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .INMODE({1'b0,1'b0,1'b0,1'b0,1'b0}),
        .MULTSIGNIN(1'b0),
        .MULTSIGNOUT(NLW_p_1_out__28_MULTSIGNOUT_UNCONNECTED),
        .OPMODE({1'b0,1'b0,1'b0,\out29[17] ,\out29[17] ,1'b0,1'b1,1'b0,1'b1}),
        .OVERFLOW(NLW_p_1_out__28_OVERFLOW_UNCONNECTED),
        .P({NLW_p_1_out__28_P_UNCONNECTED[47:45],p_1_out__28_n_61,p_1_out__28_n_62,p_1_out__28_n_63,p_1_out__28_n_64,p_1_out__28_n_65,p_1_out__28_n_66,p_1_out__28_n_67,p_1_out__28_n_68,p_1_out__28_n_69,p_1_out__28_n_70,out29,p_1_out__28_n_89,p_1_out__28_n_90,p_1_out__28_n_91,p_1_out__28_n_92,p_1_out__28_n_93,p_1_out__28_n_94,p_1_out__28_n_95,p_1_out__28_n_96,p_1_out__28_n_97,p_1_out__28_n_98,p_1_out__28_n_99,p_1_out__28_n_100,p_1_out__28_n_101,p_1_out__28_n_102,p_1_out__28_n_103,p_1_out__28_n_104,p_1_out__28_n_105}),
        .PATTERNBDETECT(NLW_p_1_out__28_PATTERNBDETECT_UNCONNECTED),
        .PATTERNDETECT(NLW_p_1_out__28_PATTERNDETECT_UNCONNECTED),
        .PCIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .PCOUT(NLW_p_1_out__28_PCOUT_UNCONNECTED[47:0]),
        .RSTA(1'b0),
        .RSTALLCARRYIN(1'b0),
        .RSTALUMODE(1'b0),
        .RSTB(reset),
        .RSTC(1'b0),
        .RSTCTRL(1'b0),
        .RSTD(1'b0),
        .RSTINMODE(1'b0),
        .RSTM(1'b0),
        .RSTP(1'b0),
        .UNDERFLOW(NLW_p_1_out__28_UNDERFLOW_UNCONNECTED),
        .XOROUT(NLW_p_1_out__28_XOROUT_UNCONNECTED[7:0]));
  (* SOFT_HLUTNM = "soft_lutpair423" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__28_i_10
       (.I0(in29[18]),
        .I1(Delay29_out1[18]),
        .I2(adc_trigger),
        .O(A__28[18]));
  (* SOFT_HLUTNM = "soft_lutpair423" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__28_i_11
       (.I0(in29[17]),
        .I1(Delay29_out1[17]),
        .I2(adc_trigger),
        .O(A__28[17]));
  (* SOFT_HLUTNM = "soft_lutpair422" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__28_i_12
       (.I0(in29[16]),
        .I1(Delay29_out1[16]),
        .I2(adc_trigger),
        .O(A__28[16]));
  (* SOFT_HLUTNM = "soft_lutpair422" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__28_i_13
       (.I0(in29[15]),
        .I1(Delay29_out1[15]),
        .I2(adc_trigger),
        .O(A__28[15]));
  (* SOFT_HLUTNM = "soft_lutpair421" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__28_i_14
       (.I0(in29[14]),
        .I1(Delay29_out1[14]),
        .I2(adc_trigger),
        .O(A__28[14]));
  (* SOFT_HLUTNM = "soft_lutpair421" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__28_i_15
       (.I0(in29[13]),
        .I1(Delay29_out1[13]),
        .I2(adc_trigger),
        .O(A__28[13]));
  (* SOFT_HLUTNM = "soft_lutpair420" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__28_i_16
       (.I0(in29[12]),
        .I1(Delay29_out1[12]),
        .I2(adc_trigger),
        .O(A__28[12]));
  (* SOFT_HLUTNM = "soft_lutpair420" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__28_i_17
       (.I0(in29[11]),
        .I1(Delay29_out1[11]),
        .I2(adc_trigger),
        .O(A__28[11]));
  (* SOFT_HLUTNM = "soft_lutpair419" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__28_i_18
       (.I0(in29[10]),
        .I1(Delay29_out1[10]),
        .I2(adc_trigger),
        .O(A__28[10]));
  (* SOFT_HLUTNM = "soft_lutpair419" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__28_i_19
       (.I0(in29[9]),
        .I1(Delay29_out1[9]),
        .I2(adc_trigger),
        .O(A__28[9]));
  (* SOFT_HLUTNM = "soft_lutpair427" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__28_i_2
       (.I0(in29[26]),
        .I1(Delay29_out1[26]),
        .I2(adc_trigger),
        .O(A__28[26]));
  (* SOFT_HLUTNM = "soft_lutpair418" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__28_i_20
       (.I0(in29[8]),
        .I1(Delay29_out1[8]),
        .I2(adc_trigger),
        .O(A__28[8]));
  (* SOFT_HLUTNM = "soft_lutpair418" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__28_i_21
       (.I0(in29[7]),
        .I1(Delay29_out1[7]),
        .I2(adc_trigger),
        .O(A__28[7]));
  (* SOFT_HLUTNM = "soft_lutpair417" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__28_i_22
       (.I0(in29[6]),
        .I1(Delay29_out1[6]),
        .I2(adc_trigger),
        .O(A__28[6]));
  (* SOFT_HLUTNM = "soft_lutpair417" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__28_i_23
       (.I0(in29[5]),
        .I1(Delay29_out1[5]),
        .I2(adc_trigger),
        .O(A__28[5]));
  (* SOFT_HLUTNM = "soft_lutpair416" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__28_i_24
       (.I0(in29[4]),
        .I1(Delay29_out1[4]),
        .I2(adc_trigger),
        .O(A__28[4]));
  (* SOFT_HLUTNM = "soft_lutpair416" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__28_i_25
       (.I0(in29[3]),
        .I1(Delay29_out1[3]),
        .I2(adc_trigger),
        .O(A__28[3]));
  (* SOFT_HLUTNM = "soft_lutpair415" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__28_i_26
       (.I0(in29[2]),
        .I1(Delay29_out1[2]),
        .I2(adc_trigger),
        .O(A__28[2]));
  (* SOFT_HLUTNM = "soft_lutpair415" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__28_i_27
       (.I0(in29[1]),
        .I1(Delay29_out1[1]),
        .I2(adc_trigger),
        .O(A__28[1]));
  (* SOFT_HLUTNM = "soft_lutpair414" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__28_i_28
       (.I0(in29[0]),
        .I1(Delay29_out1[0]),
        .I2(adc_trigger),
        .O(p_1_out__28_i_28_n_0));
  (* SOFT_HLUTNM = "soft_lutpair427" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__28_i_3
       (.I0(in29[25]),
        .I1(Delay29_out1[25]),
        .I2(adc_trigger),
        .O(A__28[25]));
  (* SOFT_HLUTNM = "soft_lutpair426" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__28_i_4
       (.I0(in29[24]),
        .I1(Delay29_out1[24]),
        .I2(adc_trigger),
        .O(A__28[24]));
  (* SOFT_HLUTNM = "soft_lutpair426" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__28_i_5
       (.I0(in29[23]),
        .I1(Delay29_out1[23]),
        .I2(adc_trigger),
        .O(A__28[23]));
  (* SOFT_HLUTNM = "soft_lutpair425" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__28_i_6
       (.I0(in29[22]),
        .I1(Delay29_out1[22]),
        .I2(adc_trigger),
        .O(A__28[22]));
  (* SOFT_HLUTNM = "soft_lutpair425" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__28_i_7
       (.I0(in29[21]),
        .I1(Delay29_out1[21]),
        .I2(adc_trigger),
        .O(A__28[21]));
  (* SOFT_HLUTNM = "soft_lutpair424" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__28_i_8
       (.I0(in29[20]),
        .I1(Delay29_out1[20]),
        .I2(adc_trigger),
        .O(A__28[20]));
  (* SOFT_HLUTNM = "soft_lutpair424" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__28_i_9
       (.I0(in29[19]),
        .I1(Delay29_out1[19]),
        .I2(adc_trigger),
        .O(A__28[19]));
  (* KEEP_HIERARCHY = "yes" *) 
  (* METHODOLOGY_DRC_VIOS = "{SYNTH-11 {cell *THIS*}}" *) 
  DSP48E2 #(
    .ACASCREG(0),
    .ADREG(1),
    .ALUMODEREG(0),
    .AMULTSEL("A"),
    .AREG(0),
    .AUTORESET_PATDET("NO_RESET"),
    .AUTORESET_PRIORITY("RESET"),
    .A_INPUT("DIRECT"),
    .BCASCREG(1),
    .BMULTSEL("B"),
    .BREG(1),
    .B_INPUT("DIRECT"),
    .CARRYINREG(0),
    .CARRYINSELREG(0),
    .CREG(0),
    .DREG(1),
    .INMODEREG(0),
    .MASK(48'h3FFFFFFFFFFF),
    .MREG(0),
    .OPMODEREG(0),
    .PATTERN(48'h000000000000),
    .PREADDINSEL("A"),
    .PREG(0),
    .RND(48'h000000000000),
    .SEL_MASK("MASK"),
    .SEL_PATTERN("PATTERN"),
    .USE_MULT("MULTIPLY"),
    .USE_PATTERN_DETECT("NO_PATDET"),
    .USE_SIMD("ONE48"),
    .USE_WIDEXOR("FALSE"),
    .XORSIMD("XOR24_48_96")) 
    p_1_out__29
       (.A({A__29[26],A__29[26],A__29[26],A__29,p_1_out__29_i_28_n_0}),
        .ACIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .ACOUT(NLW_p_1_out__29_ACOUT_UNCONNECTED[29:0]),
        .ALUMODE({1'b0,1'b0,1'b0,1'b0}),
        .B({1'b0,AXI_pu_conv_in31}),
        .BCIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .BCOUT(NLW_p_1_out__29_BCOUT_UNCONNECTED[17:0]),
        .C({A__29[26],A__29[26],A__29[26],A__29[26],A__29[26],A__29[26],A__29[26],A__29[26],A__29[26],A__29[26],A__29[26],A__29[26],A__29[26],A__29[26],A__29[26],A__29[26],A__29[26],A__29[26],A__29[26],A__29[26],A__29[26],A__29[26],A__29}),
        .CARRYCASCIN(1'b0),
        .CARRYCASCOUT(NLW_p_1_out__29_CARRYCASCOUT_UNCONNECTED),
        .CARRYIN(1'b0),
        .CARRYINSEL({1'b0,1'b0,1'b0}),
        .CARRYOUT(NLW_p_1_out__29_CARRYOUT_UNCONNECTED[3:0]),
        .CEA1(1'b0),
        .CEA2(1'b0),
        .CEAD(1'b0),
        .CEALUMODE(1'b0),
        .CEB1(1'b0),
        .CEB2(DSP_ALU_INST_28),
        .CEC(1'b0),
        .CECARRYIN(1'b0),
        .CECTRL(1'b0),
        .CED(1'b0),
        .CEINMODE(1'b0),
        .CEM(1'b0),
        .CEP(1'b0),
        .CLK(AXI4_Lite_ACLK),
        .D({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .INMODE({1'b0,1'b0,1'b0,1'b0,1'b0}),
        .MULTSIGNIN(1'b0),
        .MULTSIGNOUT(NLW_p_1_out__29_MULTSIGNOUT_UNCONNECTED),
        .OPMODE({1'b0,1'b0,1'b0,\out30[17] ,\out30[17] ,1'b0,1'b1,1'b0,1'b1}),
        .OVERFLOW(NLW_p_1_out__29_OVERFLOW_UNCONNECTED),
        .P({NLW_p_1_out__29_P_UNCONNECTED[47:45],p_1_out__29_n_61,p_1_out__29_n_62,p_1_out__29_n_63,p_1_out__29_n_64,p_1_out__29_n_65,p_1_out__29_n_66,p_1_out__29_n_67,p_1_out__29_n_68,p_1_out__29_n_69,p_1_out__29_n_70,out30,p_1_out__29_n_89,p_1_out__29_n_90,p_1_out__29_n_91,p_1_out__29_n_92,p_1_out__29_n_93,p_1_out__29_n_94,p_1_out__29_n_95,p_1_out__29_n_96,p_1_out__29_n_97,p_1_out__29_n_98,p_1_out__29_n_99,p_1_out__29_n_100,p_1_out__29_n_101,p_1_out__29_n_102,p_1_out__29_n_103,p_1_out__29_n_104,p_1_out__29_n_105}),
        .PATTERNBDETECT(NLW_p_1_out__29_PATTERNBDETECT_UNCONNECTED),
        .PATTERNDETECT(NLW_p_1_out__29_PATTERNDETECT_UNCONNECTED),
        .PCIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .PCOUT(NLW_p_1_out__29_PCOUT_UNCONNECTED[47:0]),
        .RSTA(1'b0),
        .RSTALLCARRYIN(1'b0),
        .RSTALUMODE(1'b0),
        .RSTB(reset),
        .RSTC(1'b0),
        .RSTCTRL(1'b0),
        .RSTD(1'b0),
        .RSTINMODE(1'b0),
        .RSTM(1'b0),
        .RSTP(1'b0),
        .UNDERFLOW(NLW_p_1_out__29_UNDERFLOW_UNCONNECTED),
        .XOROUT(NLW_p_1_out__29_XOROUT_UNCONNECTED[7:0]));
  (* SOFT_HLUTNM = "soft_lutpair437" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__29_i_10
       (.I0(in30[18]),
        .I1(Delay30_out1[18]),
        .I2(adc_trigger),
        .O(A__29[18]));
  (* SOFT_HLUTNM = "soft_lutpair436" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__29_i_11
       (.I0(in30[17]),
        .I1(Delay30_out1[17]),
        .I2(adc_trigger),
        .O(A__29[17]));
  (* SOFT_HLUTNM = "soft_lutpair436" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__29_i_12
       (.I0(in30[16]),
        .I1(Delay30_out1[16]),
        .I2(adc_trigger),
        .O(A__29[16]));
  (* SOFT_HLUTNM = "soft_lutpair435" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__29_i_13
       (.I0(in30[15]),
        .I1(Delay30_out1[15]),
        .I2(adc_trigger),
        .O(A__29[15]));
  (* SOFT_HLUTNM = "soft_lutpair435" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__29_i_14
       (.I0(in30[14]),
        .I1(Delay30_out1[14]),
        .I2(adc_trigger),
        .O(A__29[14]));
  (* SOFT_HLUTNM = "soft_lutpair434" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__29_i_15
       (.I0(in30[13]),
        .I1(Delay30_out1[13]),
        .I2(adc_trigger),
        .O(A__29[13]));
  (* SOFT_HLUTNM = "soft_lutpair434" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__29_i_16
       (.I0(in30[12]),
        .I1(Delay30_out1[12]),
        .I2(adc_trigger),
        .O(A__29[12]));
  (* SOFT_HLUTNM = "soft_lutpair433" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__29_i_17
       (.I0(in30[11]),
        .I1(Delay30_out1[11]),
        .I2(adc_trigger),
        .O(A__29[11]));
  (* SOFT_HLUTNM = "soft_lutpair433" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__29_i_18
       (.I0(in30[10]),
        .I1(Delay30_out1[10]),
        .I2(adc_trigger),
        .O(A__29[10]));
  (* SOFT_HLUTNM = "soft_lutpair432" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__29_i_19
       (.I0(in30[9]),
        .I1(Delay30_out1[9]),
        .I2(adc_trigger),
        .O(A__29[9]));
  (* SOFT_HLUTNM = "soft_lutpair441" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__29_i_2
       (.I0(in30[26]),
        .I1(Delay30_out1[26]),
        .I2(adc_trigger),
        .O(A__29[26]));
  (* SOFT_HLUTNM = "soft_lutpair432" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__29_i_20
       (.I0(in30[8]),
        .I1(Delay30_out1[8]),
        .I2(adc_trigger),
        .O(A__29[8]));
  (* SOFT_HLUTNM = "soft_lutpair431" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__29_i_21
       (.I0(in30[7]),
        .I1(Delay30_out1[7]),
        .I2(adc_trigger),
        .O(A__29[7]));
  (* SOFT_HLUTNM = "soft_lutpair431" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__29_i_22
       (.I0(in30[6]),
        .I1(Delay30_out1[6]),
        .I2(adc_trigger),
        .O(A__29[6]));
  (* SOFT_HLUTNM = "soft_lutpair430" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__29_i_23
       (.I0(in30[5]),
        .I1(Delay30_out1[5]),
        .I2(adc_trigger),
        .O(A__29[5]));
  (* SOFT_HLUTNM = "soft_lutpair430" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__29_i_24
       (.I0(in30[4]),
        .I1(Delay30_out1[4]),
        .I2(adc_trigger),
        .O(A__29[4]));
  (* SOFT_HLUTNM = "soft_lutpair429" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__29_i_25
       (.I0(in30[3]),
        .I1(Delay30_out1[3]),
        .I2(adc_trigger),
        .O(A__29[3]));
  (* SOFT_HLUTNM = "soft_lutpair429" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__29_i_26
       (.I0(in30[2]),
        .I1(Delay30_out1[2]),
        .I2(adc_trigger),
        .O(A__29[2]));
  (* SOFT_HLUTNM = "soft_lutpair428" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__29_i_27
       (.I0(in30[1]),
        .I1(Delay30_out1[1]),
        .I2(adc_trigger),
        .O(A__29[1]));
  (* SOFT_HLUTNM = "soft_lutpair428" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__29_i_28
       (.I0(in30[0]),
        .I1(Delay30_out1[0]),
        .I2(adc_trigger),
        .O(p_1_out__29_i_28_n_0));
  (* SOFT_HLUTNM = "soft_lutpair440" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__29_i_3
       (.I0(in30[25]),
        .I1(Delay30_out1[25]),
        .I2(adc_trigger),
        .O(A__29[25]));
  (* SOFT_HLUTNM = "soft_lutpair440" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__29_i_4
       (.I0(in30[24]),
        .I1(Delay30_out1[24]),
        .I2(adc_trigger),
        .O(A__29[24]));
  (* SOFT_HLUTNM = "soft_lutpair439" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__29_i_5
       (.I0(in30[23]),
        .I1(Delay30_out1[23]),
        .I2(adc_trigger),
        .O(A__29[23]));
  (* SOFT_HLUTNM = "soft_lutpair439" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__29_i_6
       (.I0(in30[22]),
        .I1(Delay30_out1[22]),
        .I2(adc_trigger),
        .O(A__29[22]));
  (* SOFT_HLUTNM = "soft_lutpair438" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__29_i_7
       (.I0(in30[21]),
        .I1(Delay30_out1[21]),
        .I2(adc_trigger),
        .O(A__29[21]));
  (* SOFT_HLUTNM = "soft_lutpair438" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__29_i_8
       (.I0(in30[20]),
        .I1(Delay30_out1[20]),
        .I2(adc_trigger),
        .O(A__29[20]));
  (* SOFT_HLUTNM = "soft_lutpair437" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__29_i_9
       (.I0(in30[19]),
        .I1(Delay30_out1[19]),
        .I2(adc_trigger),
        .O(A__29[19]));
  (* SOFT_HLUTNM = "soft_lutpair72" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__2_i_10
       (.I0(in3[18]),
        .I1(Delay3_out1[18]),
        .I2(adc_trigger),
        .O(A__2[18]));
  (* SOFT_HLUTNM = "soft_lutpair72" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__2_i_11
       (.I0(in3[17]),
        .I1(Delay3_out1[17]),
        .I2(adc_trigger),
        .O(A__2[17]));
  (* SOFT_HLUTNM = "soft_lutpair71" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__2_i_12
       (.I0(in3[16]),
        .I1(Delay3_out1[16]),
        .I2(adc_trigger),
        .O(A__2[16]));
  (* SOFT_HLUTNM = "soft_lutpair71" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__2_i_13
       (.I0(in3[15]),
        .I1(Delay3_out1[15]),
        .I2(adc_trigger),
        .O(A__2[15]));
  (* SOFT_HLUTNM = "soft_lutpair70" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__2_i_14
       (.I0(in3[14]),
        .I1(Delay3_out1[14]),
        .I2(adc_trigger),
        .O(A__2[14]));
  (* SOFT_HLUTNM = "soft_lutpair70" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__2_i_15
       (.I0(in3[13]),
        .I1(Delay3_out1[13]),
        .I2(adc_trigger),
        .O(A__2[13]));
  (* SOFT_HLUTNM = "soft_lutpair69" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__2_i_16
       (.I0(in3[12]),
        .I1(Delay3_out1[12]),
        .I2(adc_trigger),
        .O(A__2[12]));
  (* SOFT_HLUTNM = "soft_lutpair69" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__2_i_17
       (.I0(in3[11]),
        .I1(Delay3_out1[11]),
        .I2(adc_trigger),
        .O(A__2[11]));
  (* SOFT_HLUTNM = "soft_lutpair68" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__2_i_18
       (.I0(in3[10]),
        .I1(Delay3_out1[10]),
        .I2(adc_trigger),
        .O(A__2[10]));
  (* SOFT_HLUTNM = "soft_lutpair68" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__2_i_19
       (.I0(in3[9]),
        .I1(Delay3_out1[9]),
        .I2(adc_trigger),
        .O(A__2[9]));
  (* SOFT_HLUTNM = "soft_lutpair76" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__2_i_2
       (.I0(in3[26]),
        .I1(Delay3_out1[26]),
        .I2(adc_trigger),
        .O(A__2[26]));
  (* SOFT_HLUTNM = "soft_lutpair67" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__2_i_20
       (.I0(in3[8]),
        .I1(Delay3_out1[8]),
        .I2(adc_trigger),
        .O(A__2[8]));
  (* SOFT_HLUTNM = "soft_lutpair67" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__2_i_21
       (.I0(in3[7]),
        .I1(Delay3_out1[7]),
        .I2(adc_trigger),
        .O(A__2[7]));
  (* SOFT_HLUTNM = "soft_lutpair66" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__2_i_22
       (.I0(in3[6]),
        .I1(Delay3_out1[6]),
        .I2(adc_trigger),
        .O(A__2[6]));
  (* SOFT_HLUTNM = "soft_lutpair66" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__2_i_23
       (.I0(in3[5]),
        .I1(Delay3_out1[5]),
        .I2(adc_trigger),
        .O(A__2[5]));
  (* SOFT_HLUTNM = "soft_lutpair65" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__2_i_24
       (.I0(in3[4]),
        .I1(Delay3_out1[4]),
        .I2(adc_trigger),
        .O(A__2[4]));
  (* SOFT_HLUTNM = "soft_lutpair65" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__2_i_25
       (.I0(in3[3]),
        .I1(Delay3_out1[3]),
        .I2(adc_trigger),
        .O(A__2[3]));
  (* SOFT_HLUTNM = "soft_lutpair64" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__2_i_26
       (.I0(in3[2]),
        .I1(Delay3_out1[2]),
        .I2(adc_trigger),
        .O(A__2[2]));
  (* SOFT_HLUTNM = "soft_lutpair64" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__2_i_27
       (.I0(in3[1]),
        .I1(Delay3_out1[1]),
        .I2(adc_trigger),
        .O(A__2[1]));
  (* SOFT_HLUTNM = "soft_lutpair63" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__2_i_28
       (.I0(in3[0]),
        .I1(Delay3_out1[0]),
        .I2(adc_trigger),
        .O(p_1_out__2_i_28_n_0));
  (* SOFT_HLUTNM = "soft_lutpair76" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__2_i_3
       (.I0(in3[25]),
        .I1(Delay3_out1[25]),
        .I2(adc_trigger),
        .O(A__2[25]));
  (* SOFT_HLUTNM = "soft_lutpair75" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__2_i_4
       (.I0(in3[24]),
        .I1(Delay3_out1[24]),
        .I2(adc_trigger),
        .O(A__2[24]));
  (* SOFT_HLUTNM = "soft_lutpair75" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__2_i_5
       (.I0(in3[23]),
        .I1(Delay3_out1[23]),
        .I2(adc_trigger),
        .O(A__2[23]));
  (* SOFT_HLUTNM = "soft_lutpair74" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__2_i_6
       (.I0(in3[22]),
        .I1(Delay3_out1[22]),
        .I2(adc_trigger),
        .O(A__2[22]));
  (* SOFT_HLUTNM = "soft_lutpair74" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__2_i_7
       (.I0(in3[21]),
        .I1(Delay3_out1[21]),
        .I2(adc_trigger),
        .O(A__2[21]));
  (* SOFT_HLUTNM = "soft_lutpair73" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__2_i_8
       (.I0(in3[20]),
        .I1(Delay3_out1[20]),
        .I2(adc_trigger),
        .O(A__2[20]));
  (* SOFT_HLUTNM = "soft_lutpair73" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__2_i_9
       (.I0(in3[19]),
        .I1(Delay3_out1[19]),
        .I2(adc_trigger),
        .O(A__2[19]));
  (* KEEP_HIERARCHY = "yes" *) 
  (* METHODOLOGY_DRC_VIOS = "{SYNTH-11 {cell *THIS*}}" *) 
  DSP48E2 #(
    .ACASCREG(0),
    .ADREG(1),
    .ALUMODEREG(0),
    .AMULTSEL("A"),
    .AREG(0),
    .AUTORESET_PATDET("NO_RESET"),
    .AUTORESET_PRIORITY("RESET"),
    .A_INPUT("DIRECT"),
    .BCASCREG(1),
    .BMULTSEL("B"),
    .BREG(1),
    .B_INPUT("DIRECT"),
    .CARRYINREG(0),
    .CARRYINSELREG(0),
    .CREG(0),
    .DREG(1),
    .INMODEREG(0),
    .MASK(48'h3FFFFFFFFFFF),
    .MREG(0),
    .OPMODEREG(0),
    .PATTERN(48'h000000000000),
    .PREADDINSEL("A"),
    .PREG(0),
    .RND(48'h000000000000),
    .SEL_MASK("MASK"),
    .SEL_PATTERN("PATTERN"),
    .USE_MULT("MULTIPLY"),
    .USE_PATTERN_DETECT("NO_PATDET"),
    .USE_SIMD("ONE48"),
    .USE_WIDEXOR("FALSE"),
    .XORSIMD("XOR24_48_96")) 
    p_1_out__3
       (.A({A__3[26],A__3[26],A__3[26],A__3,p_1_out__3_i_28_n_0}),
        .ACIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .ACOUT(NLW_p_1_out__3_ACOUT_UNCONNECTED[29:0]),
        .ALUMODE({1'b0,1'b0,1'b0,1'b0}),
        .B({1'b0,AXI_pu_conv_in31}),
        .BCIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .BCOUT(NLW_p_1_out__3_BCOUT_UNCONNECTED[17:0]),
        .C({A__3[26],A__3[26],A__3[26],A__3[26],A__3[26],A__3[26],A__3[26],A__3[26],A__3[26],A__3[26],A__3[26],A__3[26],A__3[26],A__3[26],A__3[26],A__3[26],A__3[26],A__3[26],A__3[26],A__3[26],A__3[26],A__3[26],A__3}),
        .CARRYCASCIN(1'b0),
        .CARRYCASCOUT(NLW_p_1_out__3_CARRYCASCOUT_UNCONNECTED),
        .CARRYIN(1'b0),
        .CARRYINSEL({1'b0,1'b0,1'b0}),
        .CARRYOUT(NLW_p_1_out__3_CARRYOUT_UNCONNECTED[3:0]),
        .CEA1(1'b0),
        .CEA2(1'b0),
        .CEAD(1'b0),
        .CEALUMODE(1'b0),
        .CEB1(1'b0),
        .CEB2(DSP_ALU_INST_3),
        .CEC(1'b0),
        .CECARRYIN(1'b0),
        .CECTRL(1'b0),
        .CED(1'b0),
        .CEINMODE(1'b0),
        .CEM(1'b0),
        .CEP(1'b0),
        .CLK(AXI4_Lite_ACLK),
        .D({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .INMODE({1'b0,1'b0,1'b0,1'b0,1'b0}),
        .MULTSIGNIN(1'b0),
        .MULTSIGNOUT(NLW_p_1_out__3_MULTSIGNOUT_UNCONNECTED),
        .OPMODE({1'b0,1'b0,1'b0,\out4[17] ,\out4[17] ,1'b0,1'b1,1'b0,1'b1}),
        .OVERFLOW(NLW_p_1_out__3_OVERFLOW_UNCONNECTED),
        .P({NLW_p_1_out__3_P_UNCONNECTED[47:45],p_1_out__3_n_61,p_1_out__3_n_62,p_1_out__3_n_63,p_1_out__3_n_64,p_1_out__3_n_65,p_1_out__3_n_66,p_1_out__3_n_67,p_1_out__3_n_68,p_1_out__3_n_69,p_1_out__3_n_70,out4,p_1_out__3_n_89,p_1_out__3_n_90,p_1_out__3_n_91,p_1_out__3_n_92,p_1_out__3_n_93,p_1_out__3_n_94,p_1_out__3_n_95,p_1_out__3_n_96,p_1_out__3_n_97,p_1_out__3_n_98,p_1_out__3_n_99,p_1_out__3_n_100,p_1_out__3_n_101,p_1_out__3_n_102,p_1_out__3_n_103,p_1_out__3_n_104,p_1_out__3_n_105}),
        .PATTERNBDETECT(NLW_p_1_out__3_PATTERNBDETECT_UNCONNECTED),
        .PATTERNDETECT(NLW_p_1_out__3_PATTERNDETECT_UNCONNECTED),
        .PCIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .PCOUT(NLW_p_1_out__3_PCOUT_UNCONNECTED[47:0]),
        .RSTA(1'b0),
        .RSTALLCARRYIN(1'b0),
        .RSTALUMODE(1'b0),
        .RSTB(reset),
        .RSTC(1'b0),
        .RSTCTRL(1'b0),
        .RSTD(1'b0),
        .RSTINMODE(1'b0),
        .RSTM(1'b0),
        .RSTP(1'b0),
        .UNDERFLOW(NLW_p_1_out__3_UNDERFLOW_UNCONNECTED),
        .XOROUT(NLW_p_1_out__3_XOROUT_UNCONNECTED[7:0]));
  (* KEEP_HIERARCHY = "yes" *) 
  (* METHODOLOGY_DRC_VIOS = "{SYNTH-11 {cell *THIS*}}" *) 
  DSP48E2 #(
    .ACASCREG(0),
    .ADREG(1),
    .ALUMODEREG(0),
    .AMULTSEL("A"),
    .AREG(0),
    .AUTORESET_PATDET("NO_RESET"),
    .AUTORESET_PRIORITY("RESET"),
    .A_INPUT("DIRECT"),
    .BCASCREG(1),
    .BMULTSEL("B"),
    .BREG(1),
    .B_INPUT("DIRECT"),
    .CARRYINREG(0),
    .CARRYINSELREG(0),
    .CREG(0),
    .DREG(1),
    .INMODEREG(0),
    .MASK(48'h3FFFFFFFFFFF),
    .MREG(0),
    .OPMODEREG(0),
    .PATTERN(48'h000000000000),
    .PREADDINSEL("A"),
    .PREG(0),
    .RND(48'h000000000000),
    .SEL_MASK("MASK"),
    .SEL_PATTERN("PATTERN"),
    .USE_MULT("MULTIPLY"),
    .USE_PATTERN_DETECT("NO_PATDET"),
    .USE_SIMD("ONE48"),
    .USE_WIDEXOR("FALSE"),
    .XORSIMD("XOR24_48_96")) 
    p_1_out__30
       (.A({A__30[26],A__30[26],A__30[26],A__30,p_1_out__30_i_28_n_0}),
        .ACIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .ACOUT(NLW_p_1_out__30_ACOUT_UNCONNECTED[29:0]),
        .ALUMODE({1'b0,1'b0,1'b0,1'b0}),
        .B({1'b0,AXI_pu_conv_in31}),
        .BCIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .BCOUT(NLW_p_1_out__30_BCOUT_UNCONNECTED[17:0]),
        .C({A__30[26],A__30[26],A__30[26],A__30[26],A__30[26],A__30[26],A__30[26],A__30[26],A__30[26],A__30[26],A__30[26],A__30[26],A__30[26],A__30[26],A__30[26],A__30[26],A__30[26],A__30[26],A__30[26],A__30[26],A__30[26],A__30[26],A__30}),
        .CARRYCASCIN(1'b0),
        .CARRYCASCOUT(NLW_p_1_out__30_CARRYCASCOUT_UNCONNECTED),
        .CARRYIN(1'b0),
        .CARRYINSEL({1'b0,1'b0,1'b0}),
        .CARRYOUT(NLW_p_1_out__30_CARRYOUT_UNCONNECTED[3:0]),
        .CEA1(1'b0),
        .CEA2(1'b0),
        .CEAD(1'b0),
        .CEALUMODE(1'b0),
        .CEB1(1'b0),
        .CEB2(DSP_ALU_INST_29),
        .CEC(1'b0),
        .CECARRYIN(1'b0),
        .CECTRL(1'b0),
        .CED(1'b0),
        .CEINMODE(1'b0),
        .CEM(1'b0),
        .CEP(1'b0),
        .CLK(AXI4_Lite_ACLK),
        .D({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .INMODE({1'b0,1'b0,1'b0,1'b0,1'b0}),
        .MULTSIGNIN(1'b0),
        .MULTSIGNOUT(NLW_p_1_out__30_MULTSIGNOUT_UNCONNECTED),
        .OPMODE({1'b0,1'b0,1'b0,\out31[17] ,\out31[17] ,1'b0,1'b1,1'b0,1'b1}),
        .OVERFLOW(NLW_p_1_out__30_OVERFLOW_UNCONNECTED),
        .P({NLW_p_1_out__30_P_UNCONNECTED[47:45],p_1_out__30_n_61,p_1_out__30_n_62,p_1_out__30_n_63,p_1_out__30_n_64,p_1_out__30_n_65,p_1_out__30_n_66,p_1_out__30_n_67,p_1_out__30_n_68,p_1_out__30_n_69,p_1_out__30_n_70,out31,p_1_out__30_n_89,p_1_out__30_n_90,p_1_out__30_n_91,p_1_out__30_n_92,p_1_out__30_n_93,p_1_out__30_n_94,p_1_out__30_n_95,p_1_out__30_n_96,p_1_out__30_n_97,p_1_out__30_n_98,p_1_out__30_n_99,p_1_out__30_n_100,p_1_out__30_n_101,p_1_out__30_n_102,p_1_out__30_n_103,p_1_out__30_n_104,p_1_out__30_n_105}),
        .PATTERNBDETECT(NLW_p_1_out__30_PATTERNBDETECT_UNCONNECTED),
        .PATTERNDETECT(NLW_p_1_out__30_PATTERNDETECT_UNCONNECTED),
        .PCIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .PCOUT(NLW_p_1_out__30_PCOUT_UNCONNECTED[47:0]),
        .RSTA(1'b0),
        .RSTALLCARRYIN(1'b0),
        .RSTALUMODE(1'b0),
        .RSTB(reset),
        .RSTC(1'b0),
        .RSTCTRL(1'b0),
        .RSTD(1'b0),
        .RSTINMODE(1'b0),
        .RSTM(1'b0),
        .RSTP(1'b0),
        .UNDERFLOW(NLW_p_1_out__30_UNDERFLOW_UNCONNECTED),
        .XOROUT(NLW_p_1_out__30_XOROUT_UNCONNECTED[7:0]));
  (* SOFT_HLUTNM = "soft_lutpair450" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__30_i_10
       (.I0(in31[18]),
        .I1(Delay31_out1[18]),
        .I2(adc_trigger),
        .O(A__30[18]));
  (* SOFT_HLUTNM = "soft_lutpair450" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__30_i_11
       (.I0(in31[17]),
        .I1(Delay31_out1[17]),
        .I2(adc_trigger),
        .O(A__30[17]));
  (* SOFT_HLUTNM = "soft_lutpair449" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__30_i_12
       (.I0(in31[16]),
        .I1(Delay31_out1[16]),
        .I2(adc_trigger),
        .O(A__30[16]));
  (* SOFT_HLUTNM = "soft_lutpair449" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__30_i_13
       (.I0(in31[15]),
        .I1(Delay31_out1[15]),
        .I2(adc_trigger),
        .O(A__30[15]));
  (* SOFT_HLUTNM = "soft_lutpair448" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__30_i_14
       (.I0(in31[14]),
        .I1(Delay31_out1[14]),
        .I2(adc_trigger),
        .O(A__30[14]));
  (* SOFT_HLUTNM = "soft_lutpair448" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__30_i_15
       (.I0(in31[13]),
        .I1(Delay31_out1[13]),
        .I2(adc_trigger),
        .O(A__30[13]));
  (* SOFT_HLUTNM = "soft_lutpair447" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__30_i_16
       (.I0(in31[12]),
        .I1(Delay31_out1[12]),
        .I2(adc_trigger),
        .O(A__30[12]));
  (* SOFT_HLUTNM = "soft_lutpair447" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__30_i_17
       (.I0(in31[11]),
        .I1(Delay31_out1[11]),
        .I2(adc_trigger),
        .O(A__30[11]));
  (* SOFT_HLUTNM = "soft_lutpair446" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__30_i_18
       (.I0(in31[10]),
        .I1(Delay31_out1[10]),
        .I2(adc_trigger),
        .O(A__30[10]));
  (* SOFT_HLUTNM = "soft_lutpair446" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__30_i_19
       (.I0(in31[9]),
        .I1(Delay31_out1[9]),
        .I2(adc_trigger),
        .O(A__30[9]));
  (* SOFT_HLUTNM = "soft_lutpair454" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__30_i_2
       (.I0(in31[26]),
        .I1(Delay31_out1[26]),
        .I2(adc_trigger),
        .O(A__30[26]));
  (* SOFT_HLUTNM = "soft_lutpair445" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__30_i_20
       (.I0(in31[8]),
        .I1(Delay31_out1[8]),
        .I2(adc_trigger),
        .O(A__30[8]));
  (* SOFT_HLUTNM = "soft_lutpair445" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__30_i_21
       (.I0(in31[7]),
        .I1(Delay31_out1[7]),
        .I2(adc_trigger),
        .O(A__30[7]));
  (* SOFT_HLUTNM = "soft_lutpair444" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__30_i_22
       (.I0(in31[6]),
        .I1(Delay31_out1[6]),
        .I2(adc_trigger),
        .O(A__30[6]));
  (* SOFT_HLUTNM = "soft_lutpair444" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__30_i_23
       (.I0(in31[5]),
        .I1(Delay31_out1[5]),
        .I2(adc_trigger),
        .O(A__30[5]));
  (* SOFT_HLUTNM = "soft_lutpair443" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__30_i_24
       (.I0(in31[4]),
        .I1(Delay31_out1[4]),
        .I2(adc_trigger),
        .O(A__30[4]));
  (* SOFT_HLUTNM = "soft_lutpair443" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__30_i_25
       (.I0(in31[3]),
        .I1(Delay31_out1[3]),
        .I2(adc_trigger),
        .O(A__30[3]));
  (* SOFT_HLUTNM = "soft_lutpair442" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__30_i_26
       (.I0(in31[2]),
        .I1(Delay31_out1[2]),
        .I2(adc_trigger),
        .O(A__30[2]));
  (* SOFT_HLUTNM = "soft_lutpair442" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__30_i_27
       (.I0(in31[1]),
        .I1(Delay31_out1[1]),
        .I2(adc_trigger),
        .O(A__30[1]));
  (* SOFT_HLUTNM = "soft_lutpair441" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__30_i_28
       (.I0(in31[0]),
        .I1(Delay31_out1[0]),
        .I2(adc_trigger),
        .O(p_1_out__30_i_28_n_0));
  (* SOFT_HLUTNM = "soft_lutpair454" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__30_i_3
       (.I0(in31[25]),
        .I1(Delay31_out1[25]),
        .I2(adc_trigger),
        .O(A__30[25]));
  (* SOFT_HLUTNM = "soft_lutpair453" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__30_i_4
       (.I0(in31[24]),
        .I1(Delay31_out1[24]),
        .I2(adc_trigger),
        .O(A__30[24]));
  (* SOFT_HLUTNM = "soft_lutpair453" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__30_i_5
       (.I0(in31[23]),
        .I1(Delay31_out1[23]),
        .I2(adc_trigger),
        .O(A__30[23]));
  (* SOFT_HLUTNM = "soft_lutpair452" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__30_i_6
       (.I0(in31[22]),
        .I1(Delay31_out1[22]),
        .I2(adc_trigger),
        .O(A__30[22]));
  (* SOFT_HLUTNM = "soft_lutpair452" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__30_i_7
       (.I0(in31[21]),
        .I1(Delay31_out1[21]),
        .I2(adc_trigger),
        .O(A__30[21]));
  (* SOFT_HLUTNM = "soft_lutpair451" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__30_i_8
       (.I0(in31[20]),
        .I1(Delay31_out1[20]),
        .I2(adc_trigger),
        .O(A__30[20]));
  (* SOFT_HLUTNM = "soft_lutpair451" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__30_i_9
       (.I0(in31[19]),
        .I1(Delay31_out1[19]),
        .I2(adc_trigger),
        .O(A__30[19]));
  (* SOFT_HLUTNM = "soft_lutpair86" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__3_i_10
       (.I0(in4[18]),
        .I1(Delay4_out1[18]),
        .I2(adc_trigger),
        .O(A__3[18]));
  (* SOFT_HLUTNM = "soft_lutpair85" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__3_i_11
       (.I0(in4[17]),
        .I1(Delay4_out1[17]),
        .I2(adc_trigger),
        .O(A__3[17]));
  (* SOFT_HLUTNM = "soft_lutpair85" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__3_i_12
       (.I0(in4[16]),
        .I1(Delay4_out1[16]),
        .I2(adc_trigger),
        .O(A__3[16]));
  (* SOFT_HLUTNM = "soft_lutpair84" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__3_i_13
       (.I0(in4[15]),
        .I1(Delay4_out1[15]),
        .I2(adc_trigger),
        .O(A__3[15]));
  (* SOFT_HLUTNM = "soft_lutpair84" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__3_i_14
       (.I0(in4[14]),
        .I1(Delay4_out1[14]),
        .I2(adc_trigger),
        .O(A__3[14]));
  (* SOFT_HLUTNM = "soft_lutpair83" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__3_i_15
       (.I0(in4[13]),
        .I1(Delay4_out1[13]),
        .I2(adc_trigger),
        .O(A__3[13]));
  (* SOFT_HLUTNM = "soft_lutpair83" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__3_i_16
       (.I0(in4[12]),
        .I1(Delay4_out1[12]),
        .I2(adc_trigger),
        .O(A__3[12]));
  (* SOFT_HLUTNM = "soft_lutpair82" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__3_i_17
       (.I0(in4[11]),
        .I1(Delay4_out1[11]),
        .I2(adc_trigger),
        .O(A__3[11]));
  (* SOFT_HLUTNM = "soft_lutpair82" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__3_i_18
       (.I0(in4[10]),
        .I1(Delay4_out1[10]),
        .I2(adc_trigger),
        .O(A__3[10]));
  (* SOFT_HLUTNM = "soft_lutpair81" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__3_i_19
       (.I0(in4[9]),
        .I1(Delay4_out1[9]),
        .I2(adc_trigger),
        .O(A__3[9]));
  (* SOFT_HLUTNM = "soft_lutpair90" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__3_i_2
       (.I0(in4[26]),
        .I1(Delay4_out1[26]),
        .I2(adc_trigger),
        .O(A__3[26]));
  (* SOFT_HLUTNM = "soft_lutpair81" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__3_i_20
       (.I0(in4[8]),
        .I1(Delay4_out1[8]),
        .I2(adc_trigger),
        .O(A__3[8]));
  (* SOFT_HLUTNM = "soft_lutpair80" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__3_i_21
       (.I0(in4[7]),
        .I1(Delay4_out1[7]),
        .I2(adc_trigger),
        .O(A__3[7]));
  (* SOFT_HLUTNM = "soft_lutpair80" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__3_i_22
       (.I0(in4[6]),
        .I1(Delay4_out1[6]),
        .I2(adc_trigger),
        .O(A__3[6]));
  (* SOFT_HLUTNM = "soft_lutpair79" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__3_i_23
       (.I0(in4[5]),
        .I1(Delay4_out1[5]),
        .I2(adc_trigger),
        .O(A__3[5]));
  (* SOFT_HLUTNM = "soft_lutpair79" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__3_i_24
       (.I0(in4[4]),
        .I1(Delay4_out1[4]),
        .I2(adc_trigger),
        .O(A__3[4]));
  (* SOFT_HLUTNM = "soft_lutpair78" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__3_i_25
       (.I0(in4[3]),
        .I1(Delay4_out1[3]),
        .I2(adc_trigger),
        .O(A__3[3]));
  (* SOFT_HLUTNM = "soft_lutpair78" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__3_i_26
       (.I0(in4[2]),
        .I1(Delay4_out1[2]),
        .I2(adc_trigger),
        .O(A__3[2]));
  (* SOFT_HLUTNM = "soft_lutpair77" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__3_i_27
       (.I0(in4[1]),
        .I1(Delay4_out1[1]),
        .I2(adc_trigger),
        .O(A__3[1]));
  (* SOFT_HLUTNM = "soft_lutpair77" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__3_i_28
       (.I0(in4[0]),
        .I1(Delay4_out1[0]),
        .I2(adc_trigger),
        .O(p_1_out__3_i_28_n_0));
  (* SOFT_HLUTNM = "soft_lutpair89" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__3_i_3
       (.I0(in4[25]),
        .I1(Delay4_out1[25]),
        .I2(adc_trigger),
        .O(A__3[25]));
  (* SOFT_HLUTNM = "soft_lutpair89" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__3_i_4
       (.I0(in4[24]),
        .I1(Delay4_out1[24]),
        .I2(adc_trigger),
        .O(A__3[24]));
  (* SOFT_HLUTNM = "soft_lutpair88" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__3_i_5
       (.I0(in4[23]),
        .I1(Delay4_out1[23]),
        .I2(adc_trigger),
        .O(A__3[23]));
  (* SOFT_HLUTNM = "soft_lutpair88" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__3_i_6
       (.I0(in4[22]),
        .I1(Delay4_out1[22]),
        .I2(adc_trigger),
        .O(A__3[22]));
  (* SOFT_HLUTNM = "soft_lutpair87" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__3_i_7
       (.I0(in4[21]),
        .I1(Delay4_out1[21]),
        .I2(adc_trigger),
        .O(A__3[21]));
  (* SOFT_HLUTNM = "soft_lutpair87" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__3_i_8
       (.I0(in4[20]),
        .I1(Delay4_out1[20]),
        .I2(adc_trigger),
        .O(A__3[20]));
  (* SOFT_HLUTNM = "soft_lutpair86" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__3_i_9
       (.I0(in4[19]),
        .I1(Delay4_out1[19]),
        .I2(adc_trigger),
        .O(A__3[19]));
  (* KEEP_HIERARCHY = "yes" *) 
  (* METHODOLOGY_DRC_VIOS = "{SYNTH-11 {cell *THIS*}}" *) 
  DSP48E2 #(
    .ACASCREG(0),
    .ADREG(1),
    .ALUMODEREG(0),
    .AMULTSEL("A"),
    .AREG(0),
    .AUTORESET_PATDET("NO_RESET"),
    .AUTORESET_PRIORITY("RESET"),
    .A_INPUT("DIRECT"),
    .BCASCREG(1),
    .BMULTSEL("B"),
    .BREG(1),
    .B_INPUT("DIRECT"),
    .CARRYINREG(0),
    .CARRYINSELREG(0),
    .CREG(0),
    .DREG(1),
    .INMODEREG(0),
    .MASK(48'h3FFFFFFFFFFF),
    .MREG(0),
    .OPMODEREG(0),
    .PATTERN(48'h000000000000),
    .PREADDINSEL("A"),
    .PREG(0),
    .RND(48'h000000000000),
    .SEL_MASK("MASK"),
    .SEL_PATTERN("PATTERN"),
    .USE_MULT("MULTIPLY"),
    .USE_PATTERN_DETECT("NO_PATDET"),
    .USE_SIMD("ONE48"),
    .USE_WIDEXOR("FALSE"),
    .XORSIMD("XOR24_48_96")) 
    p_1_out__4
       (.A({A__4[26],A__4[26],A__4[26],A__4,p_1_out__4_i_28_n_0}),
        .ACIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .ACOUT(NLW_p_1_out__4_ACOUT_UNCONNECTED[29:0]),
        .ALUMODE({1'b0,1'b0,1'b0,1'b0}),
        .B({1'b0,AXI_pu_conv_in31}),
        .BCIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .BCOUT(NLW_p_1_out__4_BCOUT_UNCONNECTED[17:0]),
        .C({A__4[26],A__4[26],A__4[26],A__4[26],A__4[26],A__4[26],A__4[26],A__4[26],A__4[26],A__4[26],A__4[26],A__4[26],A__4[26],A__4[26],A__4[26],A__4[26],A__4[26],A__4[26],A__4[26],A__4[26],A__4[26],A__4[26],A__4}),
        .CARRYCASCIN(1'b0),
        .CARRYCASCOUT(NLW_p_1_out__4_CARRYCASCOUT_UNCONNECTED),
        .CARRYIN(1'b0),
        .CARRYINSEL({1'b0,1'b0,1'b0}),
        .CARRYOUT(NLW_p_1_out__4_CARRYOUT_UNCONNECTED[3:0]),
        .CEA1(1'b0),
        .CEA2(1'b0),
        .CEAD(1'b0),
        .CEALUMODE(1'b0),
        .CEB1(1'b0),
        .CEB2(DSP_ALU_INST_4),
        .CEC(1'b0),
        .CECARRYIN(1'b0),
        .CECTRL(1'b0),
        .CED(1'b0),
        .CEINMODE(1'b0),
        .CEM(1'b0),
        .CEP(1'b0),
        .CLK(AXI4_Lite_ACLK),
        .D({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .INMODE({1'b0,1'b0,1'b0,1'b0,1'b0}),
        .MULTSIGNIN(1'b0),
        .MULTSIGNOUT(NLW_p_1_out__4_MULTSIGNOUT_UNCONNECTED),
        .OPMODE({1'b0,1'b0,1'b0,\out5[17] ,\out5[17] ,1'b0,1'b1,1'b0,1'b1}),
        .OVERFLOW(NLW_p_1_out__4_OVERFLOW_UNCONNECTED),
        .P({NLW_p_1_out__4_P_UNCONNECTED[47:45],p_1_out__4_n_61,p_1_out__4_n_62,p_1_out__4_n_63,p_1_out__4_n_64,p_1_out__4_n_65,p_1_out__4_n_66,p_1_out__4_n_67,p_1_out__4_n_68,p_1_out__4_n_69,p_1_out__4_n_70,out5,p_1_out__4_n_89,p_1_out__4_n_90,p_1_out__4_n_91,p_1_out__4_n_92,p_1_out__4_n_93,p_1_out__4_n_94,p_1_out__4_n_95,p_1_out__4_n_96,p_1_out__4_n_97,p_1_out__4_n_98,p_1_out__4_n_99,p_1_out__4_n_100,p_1_out__4_n_101,p_1_out__4_n_102,p_1_out__4_n_103,p_1_out__4_n_104,p_1_out__4_n_105}),
        .PATTERNBDETECT(NLW_p_1_out__4_PATTERNBDETECT_UNCONNECTED),
        .PATTERNDETECT(NLW_p_1_out__4_PATTERNDETECT_UNCONNECTED),
        .PCIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .PCOUT(NLW_p_1_out__4_PCOUT_UNCONNECTED[47:0]),
        .RSTA(1'b0),
        .RSTALLCARRYIN(1'b0),
        .RSTALUMODE(1'b0),
        .RSTB(reset),
        .RSTC(1'b0),
        .RSTCTRL(1'b0),
        .RSTD(1'b0),
        .RSTINMODE(1'b0),
        .RSTM(1'b0),
        .RSTP(1'b0),
        .UNDERFLOW(NLW_p_1_out__4_UNDERFLOW_UNCONNECTED),
        .XOROUT(NLW_p_1_out__4_XOROUT_UNCONNECTED[7:0]));
  (* SOFT_HLUTNM = "soft_lutpair99" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__4_i_10
       (.I0(in5[18]),
        .I1(Delay5_out1[18]),
        .I2(adc_trigger),
        .O(A__4[18]));
  (* SOFT_HLUTNM = "soft_lutpair99" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__4_i_11
       (.I0(in5[17]),
        .I1(Delay5_out1[17]),
        .I2(adc_trigger),
        .O(A__4[17]));
  (* SOFT_HLUTNM = "soft_lutpair98" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__4_i_12
       (.I0(in5[16]),
        .I1(Delay5_out1[16]),
        .I2(adc_trigger),
        .O(A__4[16]));
  (* SOFT_HLUTNM = "soft_lutpair98" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__4_i_13
       (.I0(in5[15]),
        .I1(Delay5_out1[15]),
        .I2(adc_trigger),
        .O(A__4[15]));
  (* SOFT_HLUTNM = "soft_lutpair97" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__4_i_14
       (.I0(in5[14]),
        .I1(Delay5_out1[14]),
        .I2(adc_trigger),
        .O(A__4[14]));
  (* SOFT_HLUTNM = "soft_lutpair97" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__4_i_15
       (.I0(in5[13]),
        .I1(Delay5_out1[13]),
        .I2(adc_trigger),
        .O(A__4[13]));
  (* SOFT_HLUTNM = "soft_lutpair96" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__4_i_16
       (.I0(in5[12]),
        .I1(Delay5_out1[12]),
        .I2(adc_trigger),
        .O(A__4[12]));
  (* SOFT_HLUTNM = "soft_lutpair96" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__4_i_17
       (.I0(in5[11]),
        .I1(Delay5_out1[11]),
        .I2(adc_trigger),
        .O(A__4[11]));
  (* SOFT_HLUTNM = "soft_lutpair95" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__4_i_18
       (.I0(in5[10]),
        .I1(Delay5_out1[10]),
        .I2(adc_trigger),
        .O(A__4[10]));
  (* SOFT_HLUTNM = "soft_lutpair95" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__4_i_19
       (.I0(in5[9]),
        .I1(Delay5_out1[9]),
        .I2(adc_trigger),
        .O(A__4[9]));
  (* SOFT_HLUTNM = "soft_lutpair103" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__4_i_2
       (.I0(in5[26]),
        .I1(Delay5_out1[26]),
        .I2(adc_trigger),
        .O(A__4[26]));
  (* SOFT_HLUTNM = "soft_lutpair94" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__4_i_20
       (.I0(in5[8]),
        .I1(Delay5_out1[8]),
        .I2(adc_trigger),
        .O(A__4[8]));
  (* SOFT_HLUTNM = "soft_lutpair94" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__4_i_21
       (.I0(in5[7]),
        .I1(Delay5_out1[7]),
        .I2(adc_trigger),
        .O(A__4[7]));
  (* SOFT_HLUTNM = "soft_lutpair93" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__4_i_22
       (.I0(in5[6]),
        .I1(Delay5_out1[6]),
        .I2(adc_trigger),
        .O(A__4[6]));
  (* SOFT_HLUTNM = "soft_lutpair93" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__4_i_23
       (.I0(in5[5]),
        .I1(Delay5_out1[5]),
        .I2(adc_trigger),
        .O(A__4[5]));
  (* SOFT_HLUTNM = "soft_lutpair92" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__4_i_24
       (.I0(in5[4]),
        .I1(Delay5_out1[4]),
        .I2(adc_trigger),
        .O(A__4[4]));
  (* SOFT_HLUTNM = "soft_lutpair92" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__4_i_25
       (.I0(in5[3]),
        .I1(Delay5_out1[3]),
        .I2(adc_trigger),
        .O(A__4[3]));
  (* SOFT_HLUTNM = "soft_lutpair91" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__4_i_26
       (.I0(in5[2]),
        .I1(Delay5_out1[2]),
        .I2(adc_trigger),
        .O(A__4[2]));
  (* SOFT_HLUTNM = "soft_lutpair91" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__4_i_27
       (.I0(in5[1]),
        .I1(Delay5_out1[1]),
        .I2(adc_trigger),
        .O(A__4[1]));
  (* SOFT_HLUTNM = "soft_lutpair90" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__4_i_28
       (.I0(in5[0]),
        .I1(Delay5_out1[0]),
        .I2(adc_trigger),
        .O(p_1_out__4_i_28_n_0));
  (* SOFT_HLUTNM = "soft_lutpair103" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__4_i_3
       (.I0(in5[25]),
        .I1(Delay5_out1[25]),
        .I2(adc_trigger),
        .O(A__4[25]));
  (* SOFT_HLUTNM = "soft_lutpair102" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__4_i_4
       (.I0(in5[24]),
        .I1(Delay5_out1[24]),
        .I2(adc_trigger),
        .O(A__4[24]));
  (* SOFT_HLUTNM = "soft_lutpair102" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__4_i_5
       (.I0(in5[23]),
        .I1(Delay5_out1[23]),
        .I2(adc_trigger),
        .O(A__4[23]));
  (* SOFT_HLUTNM = "soft_lutpair101" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__4_i_6
       (.I0(in5[22]),
        .I1(Delay5_out1[22]),
        .I2(adc_trigger),
        .O(A__4[22]));
  (* SOFT_HLUTNM = "soft_lutpair101" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__4_i_7
       (.I0(in5[21]),
        .I1(Delay5_out1[21]),
        .I2(adc_trigger),
        .O(A__4[21]));
  (* SOFT_HLUTNM = "soft_lutpair100" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__4_i_8
       (.I0(in5[20]),
        .I1(Delay5_out1[20]),
        .I2(adc_trigger),
        .O(A__4[20]));
  (* SOFT_HLUTNM = "soft_lutpair100" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__4_i_9
       (.I0(in5[19]),
        .I1(Delay5_out1[19]),
        .I2(adc_trigger),
        .O(A__4[19]));
  (* KEEP_HIERARCHY = "yes" *) 
  (* METHODOLOGY_DRC_VIOS = "{SYNTH-11 {cell *THIS*}}" *) 
  DSP48E2 #(
    .ACASCREG(0),
    .ADREG(1),
    .ALUMODEREG(0),
    .AMULTSEL("A"),
    .AREG(0),
    .AUTORESET_PATDET("NO_RESET"),
    .AUTORESET_PRIORITY("RESET"),
    .A_INPUT("DIRECT"),
    .BCASCREG(1),
    .BMULTSEL("B"),
    .BREG(1),
    .B_INPUT("DIRECT"),
    .CARRYINREG(0),
    .CARRYINSELREG(0),
    .CREG(0),
    .DREG(1),
    .INMODEREG(0),
    .MASK(48'h3FFFFFFFFFFF),
    .MREG(0),
    .OPMODEREG(0),
    .PATTERN(48'h000000000000),
    .PREADDINSEL("A"),
    .PREG(0),
    .RND(48'h000000000000),
    .SEL_MASK("MASK"),
    .SEL_PATTERN("PATTERN"),
    .USE_MULT("MULTIPLY"),
    .USE_PATTERN_DETECT("NO_PATDET"),
    .USE_SIMD("ONE48"),
    .USE_WIDEXOR("FALSE"),
    .XORSIMD("XOR24_48_96")) 
    p_1_out__5
       (.A({A__5[26],A__5[26],A__5[26],A__5,p_1_out__5_i_28_n_0}),
        .ACIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .ACOUT(NLW_p_1_out__5_ACOUT_UNCONNECTED[29:0]),
        .ALUMODE({1'b0,1'b0,1'b0,1'b0}),
        .B({1'b0,AXI_pu_conv_in31}),
        .BCIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .BCOUT(NLW_p_1_out__5_BCOUT_UNCONNECTED[17:0]),
        .C({A__5[26],A__5[26],A__5[26],A__5[26],A__5[26],A__5[26],A__5[26],A__5[26],A__5[26],A__5[26],A__5[26],A__5[26],A__5[26],A__5[26],A__5[26],A__5[26],A__5[26],A__5[26],A__5[26],A__5[26],A__5[26],A__5[26],A__5}),
        .CARRYCASCIN(1'b0),
        .CARRYCASCOUT(NLW_p_1_out__5_CARRYCASCOUT_UNCONNECTED),
        .CARRYIN(1'b0),
        .CARRYINSEL({1'b0,1'b0,1'b0}),
        .CARRYOUT(NLW_p_1_out__5_CARRYOUT_UNCONNECTED[3:0]),
        .CEA1(1'b0),
        .CEA2(1'b0),
        .CEAD(1'b0),
        .CEALUMODE(1'b0),
        .CEB1(1'b0),
        .CEB2(DSP_ALU_INST_5),
        .CEC(1'b0),
        .CECARRYIN(1'b0),
        .CECTRL(1'b0),
        .CED(1'b0),
        .CEINMODE(1'b0),
        .CEM(1'b0),
        .CEP(1'b0),
        .CLK(AXI4_Lite_ACLK),
        .D({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .INMODE({1'b0,1'b0,1'b0,1'b0,1'b0}),
        .MULTSIGNIN(1'b0),
        .MULTSIGNOUT(NLW_p_1_out__5_MULTSIGNOUT_UNCONNECTED),
        .OPMODE({1'b0,1'b0,1'b0,\out6[17] ,\out6[17] ,1'b0,1'b1,1'b0,1'b1}),
        .OVERFLOW(NLW_p_1_out__5_OVERFLOW_UNCONNECTED),
        .P({NLW_p_1_out__5_P_UNCONNECTED[47:45],p_1_out__5_n_61,p_1_out__5_n_62,p_1_out__5_n_63,p_1_out__5_n_64,p_1_out__5_n_65,p_1_out__5_n_66,p_1_out__5_n_67,p_1_out__5_n_68,p_1_out__5_n_69,p_1_out__5_n_70,out6,p_1_out__5_n_89,p_1_out__5_n_90,p_1_out__5_n_91,p_1_out__5_n_92,p_1_out__5_n_93,p_1_out__5_n_94,p_1_out__5_n_95,p_1_out__5_n_96,p_1_out__5_n_97,p_1_out__5_n_98,p_1_out__5_n_99,p_1_out__5_n_100,p_1_out__5_n_101,p_1_out__5_n_102,p_1_out__5_n_103,p_1_out__5_n_104,p_1_out__5_n_105}),
        .PATTERNBDETECT(NLW_p_1_out__5_PATTERNBDETECT_UNCONNECTED),
        .PATTERNDETECT(NLW_p_1_out__5_PATTERNDETECT_UNCONNECTED),
        .PCIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .PCOUT(NLW_p_1_out__5_PCOUT_UNCONNECTED[47:0]),
        .RSTA(1'b0),
        .RSTALLCARRYIN(1'b0),
        .RSTALUMODE(1'b0),
        .RSTB(reset),
        .RSTC(1'b0),
        .RSTCTRL(1'b0),
        .RSTD(1'b0),
        .RSTINMODE(1'b0),
        .RSTM(1'b0),
        .RSTP(1'b0),
        .UNDERFLOW(NLW_p_1_out__5_UNDERFLOW_UNCONNECTED),
        .XOROUT(NLW_p_1_out__5_XOROUT_UNCONNECTED[7:0]));
  (* SOFT_HLUTNM = "soft_lutpair113" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__5_i_10
       (.I0(in6[18]),
        .I1(Delay6_out1[18]),
        .I2(adc_trigger),
        .O(A__5[18]));
  (* SOFT_HLUTNM = "soft_lutpair112" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__5_i_11
       (.I0(in6[17]),
        .I1(Delay6_out1[17]),
        .I2(adc_trigger),
        .O(A__5[17]));
  (* SOFT_HLUTNM = "soft_lutpair112" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__5_i_12
       (.I0(in6[16]),
        .I1(Delay6_out1[16]),
        .I2(adc_trigger),
        .O(A__5[16]));
  (* SOFT_HLUTNM = "soft_lutpair111" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__5_i_13
       (.I0(in6[15]),
        .I1(Delay6_out1[15]),
        .I2(adc_trigger),
        .O(A__5[15]));
  (* SOFT_HLUTNM = "soft_lutpair111" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__5_i_14
       (.I0(in6[14]),
        .I1(Delay6_out1[14]),
        .I2(adc_trigger),
        .O(A__5[14]));
  (* SOFT_HLUTNM = "soft_lutpair110" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__5_i_15
       (.I0(in6[13]),
        .I1(Delay6_out1[13]),
        .I2(adc_trigger),
        .O(A__5[13]));
  (* SOFT_HLUTNM = "soft_lutpair110" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__5_i_16
       (.I0(in6[12]),
        .I1(Delay6_out1[12]),
        .I2(adc_trigger),
        .O(A__5[12]));
  (* SOFT_HLUTNM = "soft_lutpair109" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__5_i_17
       (.I0(in6[11]),
        .I1(Delay6_out1[11]),
        .I2(adc_trigger),
        .O(A__5[11]));
  (* SOFT_HLUTNM = "soft_lutpair109" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__5_i_18
       (.I0(in6[10]),
        .I1(Delay6_out1[10]),
        .I2(adc_trigger),
        .O(A__5[10]));
  (* SOFT_HLUTNM = "soft_lutpair108" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__5_i_19
       (.I0(in6[9]),
        .I1(Delay6_out1[9]),
        .I2(adc_trigger),
        .O(A__5[9]));
  (* SOFT_HLUTNM = "soft_lutpair117" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__5_i_2
       (.I0(in6[26]),
        .I1(Delay6_out1[26]),
        .I2(adc_trigger),
        .O(A__5[26]));
  (* SOFT_HLUTNM = "soft_lutpair108" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__5_i_20
       (.I0(in6[8]),
        .I1(Delay6_out1[8]),
        .I2(adc_trigger),
        .O(A__5[8]));
  (* SOFT_HLUTNM = "soft_lutpair107" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__5_i_21
       (.I0(in6[7]),
        .I1(Delay6_out1[7]),
        .I2(adc_trigger),
        .O(A__5[7]));
  (* SOFT_HLUTNM = "soft_lutpair107" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__5_i_22
       (.I0(in6[6]),
        .I1(Delay6_out1[6]),
        .I2(adc_trigger),
        .O(A__5[6]));
  (* SOFT_HLUTNM = "soft_lutpair106" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__5_i_23
       (.I0(in6[5]),
        .I1(Delay6_out1[5]),
        .I2(adc_trigger),
        .O(A__5[5]));
  (* SOFT_HLUTNM = "soft_lutpair106" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__5_i_24
       (.I0(in6[4]),
        .I1(Delay6_out1[4]),
        .I2(adc_trigger),
        .O(A__5[4]));
  (* SOFT_HLUTNM = "soft_lutpair105" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__5_i_25
       (.I0(in6[3]),
        .I1(Delay6_out1[3]),
        .I2(adc_trigger),
        .O(A__5[3]));
  (* SOFT_HLUTNM = "soft_lutpair105" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__5_i_26
       (.I0(in6[2]),
        .I1(Delay6_out1[2]),
        .I2(adc_trigger),
        .O(A__5[2]));
  (* SOFT_HLUTNM = "soft_lutpair104" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__5_i_27
       (.I0(in6[1]),
        .I1(Delay6_out1[1]),
        .I2(adc_trigger),
        .O(A__5[1]));
  (* SOFT_HLUTNM = "soft_lutpair104" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__5_i_28
       (.I0(in6[0]),
        .I1(Delay6_out1[0]),
        .I2(adc_trigger),
        .O(p_1_out__5_i_28_n_0));
  (* SOFT_HLUTNM = "soft_lutpair116" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__5_i_3
       (.I0(in6[25]),
        .I1(Delay6_out1[25]),
        .I2(adc_trigger),
        .O(A__5[25]));
  (* SOFT_HLUTNM = "soft_lutpair116" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__5_i_4
       (.I0(in6[24]),
        .I1(Delay6_out1[24]),
        .I2(adc_trigger),
        .O(A__5[24]));
  (* SOFT_HLUTNM = "soft_lutpair115" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__5_i_5
       (.I0(in6[23]),
        .I1(Delay6_out1[23]),
        .I2(adc_trigger),
        .O(A__5[23]));
  (* SOFT_HLUTNM = "soft_lutpair115" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__5_i_6
       (.I0(in6[22]),
        .I1(Delay6_out1[22]),
        .I2(adc_trigger),
        .O(A__5[22]));
  (* SOFT_HLUTNM = "soft_lutpair114" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__5_i_7
       (.I0(in6[21]),
        .I1(Delay6_out1[21]),
        .I2(adc_trigger),
        .O(A__5[21]));
  (* SOFT_HLUTNM = "soft_lutpair114" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__5_i_8
       (.I0(in6[20]),
        .I1(Delay6_out1[20]),
        .I2(adc_trigger),
        .O(A__5[20]));
  (* SOFT_HLUTNM = "soft_lutpair113" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__5_i_9
       (.I0(in6[19]),
        .I1(Delay6_out1[19]),
        .I2(adc_trigger),
        .O(A__5[19]));
  (* KEEP_HIERARCHY = "yes" *) 
  (* METHODOLOGY_DRC_VIOS = "{SYNTH-11 {cell *THIS*}}" *) 
  DSP48E2 #(
    .ACASCREG(0),
    .ADREG(1),
    .ALUMODEREG(0),
    .AMULTSEL("A"),
    .AREG(0),
    .AUTORESET_PATDET("NO_RESET"),
    .AUTORESET_PRIORITY("RESET"),
    .A_INPUT("DIRECT"),
    .BCASCREG(1),
    .BMULTSEL("B"),
    .BREG(1),
    .B_INPUT("DIRECT"),
    .CARRYINREG(0),
    .CARRYINSELREG(0),
    .CREG(0),
    .DREG(1),
    .INMODEREG(0),
    .MASK(48'h3FFFFFFFFFFF),
    .MREG(0),
    .OPMODEREG(0),
    .PATTERN(48'h000000000000),
    .PREADDINSEL("A"),
    .PREG(0),
    .RND(48'h000000000000),
    .SEL_MASK("MASK"),
    .SEL_PATTERN("PATTERN"),
    .USE_MULT("MULTIPLY"),
    .USE_PATTERN_DETECT("NO_PATDET"),
    .USE_SIMD("ONE48"),
    .USE_WIDEXOR("FALSE"),
    .XORSIMD("XOR24_48_96")) 
    p_1_out__6
       (.A({A__6[26],A__6[26],A__6[26],A__6,p_1_out__6_i_28_n_0}),
        .ACIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .ACOUT(NLW_p_1_out__6_ACOUT_UNCONNECTED[29:0]),
        .ALUMODE({1'b0,1'b0,1'b0,1'b0}),
        .B({1'b0,AXI_pu_conv_in31}),
        .BCIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .BCOUT(NLW_p_1_out__6_BCOUT_UNCONNECTED[17:0]),
        .C({A__6[26],A__6[26],A__6[26],A__6[26],A__6[26],A__6[26],A__6[26],A__6[26],A__6[26],A__6[26],A__6[26],A__6[26],A__6[26],A__6[26],A__6[26],A__6[26],A__6[26],A__6[26],A__6[26],A__6[26],A__6[26],A__6[26],A__6}),
        .CARRYCASCIN(1'b0),
        .CARRYCASCOUT(NLW_p_1_out__6_CARRYCASCOUT_UNCONNECTED),
        .CARRYIN(1'b0),
        .CARRYINSEL({1'b0,1'b0,1'b0}),
        .CARRYOUT(NLW_p_1_out__6_CARRYOUT_UNCONNECTED[3:0]),
        .CEA1(1'b0),
        .CEA2(1'b0),
        .CEAD(1'b0),
        .CEALUMODE(1'b0),
        .CEB1(1'b0),
        .CEB2(DSP_ALU_INST_6),
        .CEC(1'b0),
        .CECARRYIN(1'b0),
        .CECTRL(1'b0),
        .CED(1'b0),
        .CEINMODE(1'b0),
        .CEM(1'b0),
        .CEP(1'b0),
        .CLK(AXI4_Lite_ACLK),
        .D({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .INMODE({1'b0,1'b0,1'b0,1'b0,1'b0}),
        .MULTSIGNIN(1'b0),
        .MULTSIGNOUT(NLW_p_1_out__6_MULTSIGNOUT_UNCONNECTED),
        .OPMODE({1'b0,1'b0,1'b0,\out7[17] ,\out7[17] ,1'b0,1'b1,1'b0,1'b1}),
        .OVERFLOW(NLW_p_1_out__6_OVERFLOW_UNCONNECTED),
        .P({NLW_p_1_out__6_P_UNCONNECTED[47:45],p_1_out__6_n_61,p_1_out__6_n_62,p_1_out__6_n_63,p_1_out__6_n_64,p_1_out__6_n_65,p_1_out__6_n_66,p_1_out__6_n_67,p_1_out__6_n_68,p_1_out__6_n_69,p_1_out__6_n_70,out7,p_1_out__6_n_89,p_1_out__6_n_90,p_1_out__6_n_91,p_1_out__6_n_92,p_1_out__6_n_93,p_1_out__6_n_94,p_1_out__6_n_95,p_1_out__6_n_96,p_1_out__6_n_97,p_1_out__6_n_98,p_1_out__6_n_99,p_1_out__6_n_100,p_1_out__6_n_101,p_1_out__6_n_102,p_1_out__6_n_103,p_1_out__6_n_104,p_1_out__6_n_105}),
        .PATTERNBDETECT(NLW_p_1_out__6_PATTERNBDETECT_UNCONNECTED),
        .PATTERNDETECT(NLW_p_1_out__6_PATTERNDETECT_UNCONNECTED),
        .PCIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .PCOUT(NLW_p_1_out__6_PCOUT_UNCONNECTED[47:0]),
        .RSTA(1'b0),
        .RSTALLCARRYIN(1'b0),
        .RSTALUMODE(1'b0),
        .RSTB(reset),
        .RSTC(1'b0),
        .RSTCTRL(1'b0),
        .RSTD(1'b0),
        .RSTINMODE(1'b0),
        .RSTM(1'b0),
        .RSTP(1'b0),
        .UNDERFLOW(NLW_p_1_out__6_UNDERFLOW_UNCONNECTED),
        .XOROUT(NLW_p_1_out__6_XOROUT_UNCONNECTED[7:0]));
  (* SOFT_HLUTNM = "soft_lutpair126" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__6_i_10
       (.I0(in7[18]),
        .I1(Delay7_out1[18]),
        .I2(adc_trigger),
        .O(A__6[18]));
  (* SOFT_HLUTNM = "soft_lutpair126" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__6_i_11
       (.I0(in7[17]),
        .I1(Delay7_out1[17]),
        .I2(adc_trigger),
        .O(A__6[17]));
  (* SOFT_HLUTNM = "soft_lutpair125" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__6_i_12
       (.I0(in7[16]),
        .I1(Delay7_out1[16]),
        .I2(adc_trigger),
        .O(A__6[16]));
  (* SOFT_HLUTNM = "soft_lutpair125" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__6_i_13
       (.I0(in7[15]),
        .I1(Delay7_out1[15]),
        .I2(adc_trigger),
        .O(A__6[15]));
  (* SOFT_HLUTNM = "soft_lutpair124" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__6_i_14
       (.I0(in7[14]),
        .I1(Delay7_out1[14]),
        .I2(adc_trigger),
        .O(A__6[14]));
  (* SOFT_HLUTNM = "soft_lutpair124" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__6_i_15
       (.I0(in7[13]),
        .I1(Delay7_out1[13]),
        .I2(adc_trigger),
        .O(A__6[13]));
  (* SOFT_HLUTNM = "soft_lutpair123" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__6_i_16
       (.I0(in7[12]),
        .I1(Delay7_out1[12]),
        .I2(adc_trigger),
        .O(A__6[12]));
  (* SOFT_HLUTNM = "soft_lutpair123" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__6_i_17
       (.I0(in7[11]),
        .I1(Delay7_out1[11]),
        .I2(adc_trigger),
        .O(A__6[11]));
  (* SOFT_HLUTNM = "soft_lutpair122" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__6_i_18
       (.I0(in7[10]),
        .I1(Delay7_out1[10]),
        .I2(adc_trigger),
        .O(A__6[10]));
  (* SOFT_HLUTNM = "soft_lutpair122" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__6_i_19
       (.I0(in7[9]),
        .I1(Delay7_out1[9]),
        .I2(adc_trigger),
        .O(A__6[9]));
  (* SOFT_HLUTNM = "soft_lutpair130" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__6_i_2
       (.I0(in7[26]),
        .I1(Delay7_out1[26]),
        .I2(adc_trigger),
        .O(A__6[26]));
  (* SOFT_HLUTNM = "soft_lutpair121" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__6_i_20
       (.I0(in7[8]),
        .I1(Delay7_out1[8]),
        .I2(adc_trigger),
        .O(A__6[8]));
  (* SOFT_HLUTNM = "soft_lutpair121" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__6_i_21
       (.I0(in7[7]),
        .I1(Delay7_out1[7]),
        .I2(adc_trigger),
        .O(A__6[7]));
  (* SOFT_HLUTNM = "soft_lutpair120" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__6_i_22
       (.I0(in7[6]),
        .I1(Delay7_out1[6]),
        .I2(adc_trigger),
        .O(A__6[6]));
  (* SOFT_HLUTNM = "soft_lutpair120" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__6_i_23
       (.I0(in7[5]),
        .I1(Delay7_out1[5]),
        .I2(adc_trigger),
        .O(A__6[5]));
  (* SOFT_HLUTNM = "soft_lutpair119" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__6_i_24
       (.I0(in7[4]),
        .I1(Delay7_out1[4]),
        .I2(adc_trigger),
        .O(A__6[4]));
  (* SOFT_HLUTNM = "soft_lutpair119" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__6_i_25
       (.I0(in7[3]),
        .I1(Delay7_out1[3]),
        .I2(adc_trigger),
        .O(A__6[3]));
  (* SOFT_HLUTNM = "soft_lutpair118" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__6_i_26
       (.I0(in7[2]),
        .I1(Delay7_out1[2]),
        .I2(adc_trigger),
        .O(A__6[2]));
  (* SOFT_HLUTNM = "soft_lutpair118" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__6_i_27
       (.I0(in7[1]),
        .I1(Delay7_out1[1]),
        .I2(adc_trigger),
        .O(A__6[1]));
  (* SOFT_HLUTNM = "soft_lutpair117" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__6_i_28
       (.I0(in7[0]),
        .I1(Delay7_out1[0]),
        .I2(adc_trigger),
        .O(p_1_out__6_i_28_n_0));
  (* SOFT_HLUTNM = "soft_lutpair130" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__6_i_3
       (.I0(in7[25]),
        .I1(Delay7_out1[25]),
        .I2(adc_trigger),
        .O(A__6[25]));
  (* SOFT_HLUTNM = "soft_lutpair129" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__6_i_4
       (.I0(in7[24]),
        .I1(Delay7_out1[24]),
        .I2(adc_trigger),
        .O(A__6[24]));
  (* SOFT_HLUTNM = "soft_lutpair129" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__6_i_5
       (.I0(in7[23]),
        .I1(Delay7_out1[23]),
        .I2(adc_trigger),
        .O(A__6[23]));
  (* SOFT_HLUTNM = "soft_lutpair128" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__6_i_6
       (.I0(in7[22]),
        .I1(Delay7_out1[22]),
        .I2(adc_trigger),
        .O(A__6[22]));
  (* SOFT_HLUTNM = "soft_lutpair128" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__6_i_7
       (.I0(in7[21]),
        .I1(Delay7_out1[21]),
        .I2(adc_trigger),
        .O(A__6[21]));
  (* SOFT_HLUTNM = "soft_lutpair127" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__6_i_8
       (.I0(in7[20]),
        .I1(Delay7_out1[20]),
        .I2(adc_trigger),
        .O(A__6[20]));
  (* SOFT_HLUTNM = "soft_lutpair127" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__6_i_9
       (.I0(in7[19]),
        .I1(Delay7_out1[19]),
        .I2(adc_trigger),
        .O(A__6[19]));
  (* KEEP_HIERARCHY = "yes" *) 
  (* METHODOLOGY_DRC_VIOS = "{SYNTH-11 {cell *THIS*}}" *) 
  DSP48E2 #(
    .ACASCREG(0),
    .ADREG(1),
    .ALUMODEREG(0),
    .AMULTSEL("A"),
    .AREG(0),
    .AUTORESET_PATDET("NO_RESET"),
    .AUTORESET_PRIORITY("RESET"),
    .A_INPUT("DIRECT"),
    .BCASCREG(1),
    .BMULTSEL("B"),
    .BREG(1),
    .B_INPUT("DIRECT"),
    .CARRYINREG(0),
    .CARRYINSELREG(0),
    .CREG(0),
    .DREG(1),
    .INMODEREG(0),
    .MASK(48'h3FFFFFFFFFFF),
    .MREG(0),
    .OPMODEREG(0),
    .PATTERN(48'h000000000000),
    .PREADDINSEL("A"),
    .PREG(0),
    .RND(48'h000000000000),
    .SEL_MASK("MASK"),
    .SEL_PATTERN("PATTERN"),
    .USE_MULT("MULTIPLY"),
    .USE_PATTERN_DETECT("NO_PATDET"),
    .USE_SIMD("ONE48"),
    .USE_WIDEXOR("FALSE"),
    .XORSIMD("XOR24_48_96")) 
    p_1_out__7
       (.A({A__7[26],A__7[26],A__7[26],A__7,p_1_out__7_i_28_n_0}),
        .ACIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .ACOUT(NLW_p_1_out__7_ACOUT_UNCONNECTED[29:0]),
        .ALUMODE({1'b0,1'b0,1'b0,1'b0}),
        .B({1'b0,AXI_pu_conv_in31}),
        .BCIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .BCOUT(NLW_p_1_out__7_BCOUT_UNCONNECTED[17:0]),
        .C({A__7[26],A__7[26],A__7[26],A__7[26],A__7[26],A__7[26],A__7[26],A__7[26],A__7[26],A__7[26],A__7[26],A__7[26],A__7[26],A__7[26],A__7[26],A__7[26],A__7[26],A__7[26],A__7[26],A__7[26],A__7[26],A__7[26],A__7}),
        .CARRYCASCIN(1'b0),
        .CARRYCASCOUT(NLW_p_1_out__7_CARRYCASCOUT_UNCONNECTED),
        .CARRYIN(1'b0),
        .CARRYINSEL({1'b0,1'b0,1'b0}),
        .CARRYOUT(NLW_p_1_out__7_CARRYOUT_UNCONNECTED[3:0]),
        .CEA1(1'b0),
        .CEA2(1'b0),
        .CEAD(1'b0),
        .CEALUMODE(1'b0),
        .CEB1(1'b0),
        .CEB2(DSP_ALU_INST_7),
        .CEC(1'b0),
        .CECARRYIN(1'b0),
        .CECTRL(1'b0),
        .CED(1'b0),
        .CEINMODE(1'b0),
        .CEM(1'b0),
        .CEP(1'b0),
        .CLK(AXI4_Lite_ACLK),
        .D({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .INMODE({1'b0,1'b0,1'b0,1'b0,1'b0}),
        .MULTSIGNIN(1'b0),
        .MULTSIGNOUT(NLW_p_1_out__7_MULTSIGNOUT_UNCONNECTED),
        .OPMODE({1'b0,1'b0,1'b0,\out8[17] ,\out8[17] ,1'b0,1'b1,1'b0,1'b1}),
        .OVERFLOW(NLW_p_1_out__7_OVERFLOW_UNCONNECTED),
        .P({NLW_p_1_out__7_P_UNCONNECTED[47:45],p_1_out__7_n_61,p_1_out__7_n_62,p_1_out__7_n_63,p_1_out__7_n_64,p_1_out__7_n_65,p_1_out__7_n_66,p_1_out__7_n_67,p_1_out__7_n_68,p_1_out__7_n_69,p_1_out__7_n_70,out8,p_1_out__7_n_89,p_1_out__7_n_90,p_1_out__7_n_91,p_1_out__7_n_92,p_1_out__7_n_93,p_1_out__7_n_94,p_1_out__7_n_95,p_1_out__7_n_96,p_1_out__7_n_97,p_1_out__7_n_98,p_1_out__7_n_99,p_1_out__7_n_100,p_1_out__7_n_101,p_1_out__7_n_102,p_1_out__7_n_103,p_1_out__7_n_104,p_1_out__7_n_105}),
        .PATTERNBDETECT(NLW_p_1_out__7_PATTERNBDETECT_UNCONNECTED),
        .PATTERNDETECT(NLW_p_1_out__7_PATTERNDETECT_UNCONNECTED),
        .PCIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .PCOUT(NLW_p_1_out__7_PCOUT_UNCONNECTED[47:0]),
        .RSTA(1'b0),
        .RSTALLCARRYIN(1'b0),
        .RSTALUMODE(1'b0),
        .RSTB(reset),
        .RSTC(1'b0),
        .RSTCTRL(1'b0),
        .RSTD(1'b0),
        .RSTINMODE(1'b0),
        .RSTM(1'b0),
        .RSTP(1'b0),
        .UNDERFLOW(NLW_p_1_out__7_UNDERFLOW_UNCONNECTED),
        .XOROUT(NLW_p_1_out__7_XOROUT_UNCONNECTED[7:0]));
  (* SOFT_HLUTNM = "soft_lutpair140" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__7_i_10
       (.I0(in8[18]),
        .I1(Delay8_out1[18]),
        .I2(adc_trigger),
        .O(A__7[18]));
  (* SOFT_HLUTNM = "soft_lutpair139" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__7_i_11
       (.I0(in8[17]),
        .I1(Delay8_out1[17]),
        .I2(adc_trigger),
        .O(A__7[17]));
  (* SOFT_HLUTNM = "soft_lutpair139" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__7_i_12
       (.I0(in8[16]),
        .I1(Delay8_out1[16]),
        .I2(adc_trigger),
        .O(A__7[16]));
  (* SOFT_HLUTNM = "soft_lutpair138" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__7_i_13
       (.I0(in8[15]),
        .I1(Delay8_out1[15]),
        .I2(adc_trigger),
        .O(A__7[15]));
  (* SOFT_HLUTNM = "soft_lutpair138" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__7_i_14
       (.I0(in8[14]),
        .I1(Delay8_out1[14]),
        .I2(adc_trigger),
        .O(A__7[14]));
  (* SOFT_HLUTNM = "soft_lutpair137" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__7_i_15
       (.I0(in8[13]),
        .I1(Delay8_out1[13]),
        .I2(adc_trigger),
        .O(A__7[13]));
  (* SOFT_HLUTNM = "soft_lutpair137" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__7_i_16
       (.I0(in8[12]),
        .I1(Delay8_out1[12]),
        .I2(adc_trigger),
        .O(A__7[12]));
  (* SOFT_HLUTNM = "soft_lutpair136" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__7_i_17
       (.I0(in8[11]),
        .I1(Delay8_out1[11]),
        .I2(adc_trigger),
        .O(A__7[11]));
  (* SOFT_HLUTNM = "soft_lutpair136" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__7_i_18
       (.I0(in8[10]),
        .I1(Delay8_out1[10]),
        .I2(adc_trigger),
        .O(A__7[10]));
  (* SOFT_HLUTNM = "soft_lutpair135" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__7_i_19
       (.I0(in8[9]),
        .I1(Delay8_out1[9]),
        .I2(adc_trigger),
        .O(A__7[9]));
  (* SOFT_HLUTNM = "soft_lutpair144" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__7_i_2
       (.I0(in8[26]),
        .I1(Delay8_out1[26]),
        .I2(adc_trigger),
        .O(A__7[26]));
  (* SOFT_HLUTNM = "soft_lutpair135" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__7_i_20
       (.I0(in8[8]),
        .I1(Delay8_out1[8]),
        .I2(adc_trigger),
        .O(A__7[8]));
  (* SOFT_HLUTNM = "soft_lutpair134" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__7_i_21
       (.I0(in8[7]),
        .I1(Delay8_out1[7]),
        .I2(adc_trigger),
        .O(A__7[7]));
  (* SOFT_HLUTNM = "soft_lutpair134" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__7_i_22
       (.I0(in8[6]),
        .I1(Delay8_out1[6]),
        .I2(adc_trigger),
        .O(A__7[6]));
  (* SOFT_HLUTNM = "soft_lutpair133" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__7_i_23
       (.I0(in8[5]),
        .I1(Delay8_out1[5]),
        .I2(adc_trigger),
        .O(A__7[5]));
  (* SOFT_HLUTNM = "soft_lutpair133" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__7_i_24
       (.I0(in8[4]),
        .I1(Delay8_out1[4]),
        .I2(adc_trigger),
        .O(A__7[4]));
  (* SOFT_HLUTNM = "soft_lutpair132" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__7_i_25
       (.I0(in8[3]),
        .I1(Delay8_out1[3]),
        .I2(adc_trigger),
        .O(A__7[3]));
  (* SOFT_HLUTNM = "soft_lutpair132" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__7_i_26
       (.I0(in8[2]),
        .I1(Delay8_out1[2]),
        .I2(adc_trigger),
        .O(A__7[2]));
  (* SOFT_HLUTNM = "soft_lutpair131" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__7_i_27
       (.I0(in8[1]),
        .I1(Delay8_out1[1]),
        .I2(adc_trigger),
        .O(A__7[1]));
  (* SOFT_HLUTNM = "soft_lutpair131" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__7_i_28
       (.I0(in8[0]),
        .I1(Delay8_out1[0]),
        .I2(adc_trigger),
        .O(p_1_out__7_i_28_n_0));
  (* SOFT_HLUTNM = "soft_lutpair143" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__7_i_3
       (.I0(in8[25]),
        .I1(Delay8_out1[25]),
        .I2(adc_trigger),
        .O(A__7[25]));
  (* SOFT_HLUTNM = "soft_lutpair143" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__7_i_4
       (.I0(in8[24]),
        .I1(Delay8_out1[24]),
        .I2(adc_trigger),
        .O(A__7[24]));
  (* SOFT_HLUTNM = "soft_lutpair142" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__7_i_5
       (.I0(in8[23]),
        .I1(Delay8_out1[23]),
        .I2(adc_trigger),
        .O(A__7[23]));
  (* SOFT_HLUTNM = "soft_lutpair142" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__7_i_6
       (.I0(in8[22]),
        .I1(Delay8_out1[22]),
        .I2(adc_trigger),
        .O(A__7[22]));
  (* SOFT_HLUTNM = "soft_lutpair141" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__7_i_7
       (.I0(in8[21]),
        .I1(Delay8_out1[21]),
        .I2(adc_trigger),
        .O(A__7[21]));
  (* SOFT_HLUTNM = "soft_lutpair141" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__7_i_8
       (.I0(in8[20]),
        .I1(Delay8_out1[20]),
        .I2(adc_trigger),
        .O(A__7[20]));
  (* SOFT_HLUTNM = "soft_lutpair140" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__7_i_9
       (.I0(in8[19]),
        .I1(Delay8_out1[19]),
        .I2(adc_trigger),
        .O(A__7[19]));
  (* KEEP_HIERARCHY = "yes" *) 
  (* METHODOLOGY_DRC_VIOS = "{SYNTH-11 {cell *THIS*}}" *) 
  DSP48E2 #(
    .ACASCREG(0),
    .ADREG(1),
    .ALUMODEREG(0),
    .AMULTSEL("A"),
    .AREG(0),
    .AUTORESET_PATDET("NO_RESET"),
    .AUTORESET_PRIORITY("RESET"),
    .A_INPUT("DIRECT"),
    .BCASCREG(1),
    .BMULTSEL("B"),
    .BREG(1),
    .B_INPUT("DIRECT"),
    .CARRYINREG(0),
    .CARRYINSELREG(0),
    .CREG(0),
    .DREG(1),
    .INMODEREG(0),
    .MASK(48'h3FFFFFFFFFFF),
    .MREG(0),
    .OPMODEREG(0),
    .PATTERN(48'h000000000000),
    .PREADDINSEL("A"),
    .PREG(0),
    .RND(48'h000000000000),
    .SEL_MASK("MASK"),
    .SEL_PATTERN("PATTERN"),
    .USE_MULT("MULTIPLY"),
    .USE_PATTERN_DETECT("NO_PATDET"),
    .USE_SIMD("ONE48"),
    .USE_WIDEXOR("FALSE"),
    .XORSIMD("XOR24_48_96")) 
    p_1_out__8
       (.A({A__8[26],A__8[26],A__8[26],A__8,p_1_out__8_i_28_n_0}),
        .ACIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .ACOUT(NLW_p_1_out__8_ACOUT_UNCONNECTED[29:0]),
        .ALUMODE({1'b0,1'b0,1'b0,1'b0}),
        .B({1'b0,AXI_pu_conv_in31}),
        .BCIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .BCOUT(NLW_p_1_out__8_BCOUT_UNCONNECTED[17:0]),
        .C({A__8[26],A__8[26],A__8[26],A__8[26],A__8[26],A__8[26],A__8[26],A__8[26],A__8[26],A__8[26],A__8[26],A__8[26],A__8[26],A__8[26],A__8[26],A__8[26],A__8[26],A__8[26],A__8[26],A__8[26],A__8[26],A__8[26],A__8}),
        .CARRYCASCIN(1'b0),
        .CARRYCASCOUT(NLW_p_1_out__8_CARRYCASCOUT_UNCONNECTED),
        .CARRYIN(1'b0),
        .CARRYINSEL({1'b0,1'b0,1'b0}),
        .CARRYOUT(NLW_p_1_out__8_CARRYOUT_UNCONNECTED[3:0]),
        .CEA1(1'b0),
        .CEA2(1'b0),
        .CEAD(1'b0),
        .CEALUMODE(1'b0),
        .CEB1(1'b0),
        .CEB2(DSP_ALU_INST_8),
        .CEC(1'b0),
        .CECARRYIN(1'b0),
        .CECTRL(1'b0),
        .CED(1'b0),
        .CEINMODE(1'b0),
        .CEM(1'b0),
        .CEP(1'b0),
        .CLK(AXI4_Lite_ACLK),
        .D({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .INMODE({1'b0,1'b0,1'b0,1'b0,1'b0}),
        .MULTSIGNIN(1'b0),
        .MULTSIGNOUT(NLW_p_1_out__8_MULTSIGNOUT_UNCONNECTED),
        .OPMODE({1'b0,1'b0,1'b0,\out9[17] ,\out9[17] ,1'b0,1'b1,1'b0,1'b1}),
        .OVERFLOW(NLW_p_1_out__8_OVERFLOW_UNCONNECTED),
        .P({NLW_p_1_out__8_P_UNCONNECTED[47:45],p_1_out__8_n_61,p_1_out__8_n_62,p_1_out__8_n_63,p_1_out__8_n_64,p_1_out__8_n_65,p_1_out__8_n_66,p_1_out__8_n_67,p_1_out__8_n_68,p_1_out__8_n_69,p_1_out__8_n_70,out9,p_1_out__8_n_89,p_1_out__8_n_90,p_1_out__8_n_91,p_1_out__8_n_92,p_1_out__8_n_93,p_1_out__8_n_94,p_1_out__8_n_95,p_1_out__8_n_96,p_1_out__8_n_97,p_1_out__8_n_98,p_1_out__8_n_99,p_1_out__8_n_100,p_1_out__8_n_101,p_1_out__8_n_102,p_1_out__8_n_103,p_1_out__8_n_104,p_1_out__8_n_105}),
        .PATTERNBDETECT(NLW_p_1_out__8_PATTERNBDETECT_UNCONNECTED),
        .PATTERNDETECT(NLW_p_1_out__8_PATTERNDETECT_UNCONNECTED),
        .PCIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .PCOUT(NLW_p_1_out__8_PCOUT_UNCONNECTED[47:0]),
        .RSTA(1'b0),
        .RSTALLCARRYIN(1'b0),
        .RSTALUMODE(1'b0),
        .RSTB(reset),
        .RSTC(1'b0),
        .RSTCTRL(1'b0),
        .RSTD(1'b0),
        .RSTINMODE(1'b0),
        .RSTM(1'b0),
        .RSTP(1'b0),
        .UNDERFLOW(NLW_p_1_out__8_UNDERFLOW_UNCONNECTED),
        .XOROUT(NLW_p_1_out__8_XOROUT_UNCONNECTED[7:0]));
  (* SOFT_HLUTNM = "soft_lutpair153" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__8_i_10
       (.I0(in9[18]),
        .I1(Delay9_out1[18]),
        .I2(adc_trigger),
        .O(A__8[18]));
  (* SOFT_HLUTNM = "soft_lutpair153" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__8_i_11
       (.I0(in9[17]),
        .I1(Delay9_out1[17]),
        .I2(adc_trigger),
        .O(A__8[17]));
  (* SOFT_HLUTNM = "soft_lutpair152" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__8_i_12
       (.I0(in9[16]),
        .I1(Delay9_out1[16]),
        .I2(adc_trigger),
        .O(A__8[16]));
  (* SOFT_HLUTNM = "soft_lutpair152" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__8_i_13
       (.I0(in9[15]),
        .I1(Delay9_out1[15]),
        .I2(adc_trigger),
        .O(A__8[15]));
  (* SOFT_HLUTNM = "soft_lutpair151" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__8_i_14
       (.I0(in9[14]),
        .I1(Delay9_out1[14]),
        .I2(adc_trigger),
        .O(A__8[14]));
  (* SOFT_HLUTNM = "soft_lutpair151" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__8_i_15
       (.I0(in9[13]),
        .I1(Delay9_out1[13]),
        .I2(adc_trigger),
        .O(A__8[13]));
  (* SOFT_HLUTNM = "soft_lutpair150" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__8_i_16
       (.I0(in9[12]),
        .I1(Delay9_out1[12]),
        .I2(adc_trigger),
        .O(A__8[12]));
  (* SOFT_HLUTNM = "soft_lutpair150" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__8_i_17
       (.I0(in9[11]),
        .I1(Delay9_out1[11]),
        .I2(adc_trigger),
        .O(A__8[11]));
  (* SOFT_HLUTNM = "soft_lutpair149" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__8_i_18
       (.I0(in9[10]),
        .I1(Delay9_out1[10]),
        .I2(adc_trigger),
        .O(A__8[10]));
  (* SOFT_HLUTNM = "soft_lutpair149" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__8_i_19
       (.I0(in9[9]),
        .I1(Delay9_out1[9]),
        .I2(adc_trigger),
        .O(A__8[9]));
  (* SOFT_HLUTNM = "soft_lutpair157" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__8_i_2
       (.I0(in9[26]),
        .I1(Delay9_out1[26]),
        .I2(adc_trigger),
        .O(A__8[26]));
  (* SOFT_HLUTNM = "soft_lutpair148" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__8_i_20
       (.I0(in9[8]),
        .I1(Delay9_out1[8]),
        .I2(adc_trigger),
        .O(A__8[8]));
  (* SOFT_HLUTNM = "soft_lutpair148" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__8_i_21
       (.I0(in9[7]),
        .I1(Delay9_out1[7]),
        .I2(adc_trigger),
        .O(A__8[7]));
  (* SOFT_HLUTNM = "soft_lutpair147" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__8_i_22
       (.I0(in9[6]),
        .I1(Delay9_out1[6]),
        .I2(adc_trigger),
        .O(A__8[6]));
  (* SOFT_HLUTNM = "soft_lutpair147" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__8_i_23
       (.I0(in9[5]),
        .I1(Delay9_out1[5]),
        .I2(adc_trigger),
        .O(A__8[5]));
  (* SOFT_HLUTNM = "soft_lutpair146" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__8_i_24
       (.I0(in9[4]),
        .I1(Delay9_out1[4]),
        .I2(adc_trigger),
        .O(A__8[4]));
  (* SOFT_HLUTNM = "soft_lutpair146" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__8_i_25
       (.I0(in9[3]),
        .I1(Delay9_out1[3]),
        .I2(adc_trigger),
        .O(A__8[3]));
  (* SOFT_HLUTNM = "soft_lutpair145" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__8_i_26
       (.I0(in9[2]),
        .I1(Delay9_out1[2]),
        .I2(adc_trigger),
        .O(A__8[2]));
  (* SOFT_HLUTNM = "soft_lutpair145" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__8_i_27
       (.I0(in9[1]),
        .I1(Delay9_out1[1]),
        .I2(adc_trigger),
        .O(A__8[1]));
  (* SOFT_HLUTNM = "soft_lutpair144" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__8_i_28
       (.I0(in9[0]),
        .I1(Delay9_out1[0]),
        .I2(adc_trigger),
        .O(p_1_out__8_i_28_n_0));
  (* SOFT_HLUTNM = "soft_lutpair157" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__8_i_3
       (.I0(in9[25]),
        .I1(Delay9_out1[25]),
        .I2(adc_trigger),
        .O(A__8[25]));
  (* SOFT_HLUTNM = "soft_lutpair156" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__8_i_4
       (.I0(in9[24]),
        .I1(Delay9_out1[24]),
        .I2(adc_trigger),
        .O(A__8[24]));
  (* SOFT_HLUTNM = "soft_lutpair156" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__8_i_5
       (.I0(in9[23]),
        .I1(Delay9_out1[23]),
        .I2(adc_trigger),
        .O(A__8[23]));
  (* SOFT_HLUTNM = "soft_lutpair155" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__8_i_6
       (.I0(in9[22]),
        .I1(Delay9_out1[22]),
        .I2(adc_trigger),
        .O(A__8[22]));
  (* SOFT_HLUTNM = "soft_lutpair155" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__8_i_7
       (.I0(in9[21]),
        .I1(Delay9_out1[21]),
        .I2(adc_trigger),
        .O(A__8[21]));
  (* SOFT_HLUTNM = "soft_lutpair154" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__8_i_8
       (.I0(in9[20]),
        .I1(Delay9_out1[20]),
        .I2(adc_trigger),
        .O(A__8[20]));
  (* SOFT_HLUTNM = "soft_lutpair154" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__8_i_9
       (.I0(in9[19]),
        .I1(Delay9_out1[19]),
        .I2(adc_trigger),
        .O(A__8[19]));
  (* KEEP_HIERARCHY = "yes" *) 
  (* METHODOLOGY_DRC_VIOS = "{SYNTH-11 {cell *THIS*}}" *) 
  DSP48E2 #(
    .ACASCREG(0),
    .ADREG(1),
    .ALUMODEREG(0),
    .AMULTSEL("A"),
    .AREG(0),
    .AUTORESET_PATDET("NO_RESET"),
    .AUTORESET_PRIORITY("RESET"),
    .A_INPUT("DIRECT"),
    .BCASCREG(1),
    .BMULTSEL("B"),
    .BREG(1),
    .B_INPUT("DIRECT"),
    .CARRYINREG(0),
    .CARRYINSELREG(0),
    .CREG(0),
    .DREG(1),
    .INMODEREG(0),
    .MASK(48'h3FFFFFFFFFFF),
    .MREG(0),
    .OPMODEREG(0),
    .PATTERN(48'h000000000000),
    .PREADDINSEL("A"),
    .PREG(0),
    .RND(48'h000000000000),
    .SEL_MASK("MASK"),
    .SEL_PATTERN("PATTERN"),
    .USE_MULT("MULTIPLY"),
    .USE_PATTERN_DETECT("NO_PATDET"),
    .USE_SIMD("ONE48"),
    .USE_WIDEXOR("FALSE"),
    .XORSIMD("XOR24_48_96")) 
    p_1_out__9
       (.A({A__9[26],A__9[26],A__9[26],A__9,p_1_out__9_i_28_n_0}),
        .ACIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .ACOUT(NLW_p_1_out__9_ACOUT_UNCONNECTED[29:0]),
        .ALUMODE({1'b0,1'b0,1'b0,1'b0}),
        .B({1'b0,AXI_pu_conv_in31}),
        .BCIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .BCOUT(NLW_p_1_out__9_BCOUT_UNCONNECTED[17:0]),
        .C({A__9[26],A__9[26],A__9[26],A__9[26],A__9[26],A__9[26],A__9[26],A__9[26],A__9[26],A__9[26],A__9[26],A__9[26],A__9[26],A__9[26],A__9[26],A__9[26],A__9[26],A__9[26],A__9[26],A__9[26],A__9[26],A__9[26],A__9}),
        .CARRYCASCIN(1'b0),
        .CARRYCASCOUT(NLW_p_1_out__9_CARRYCASCOUT_UNCONNECTED),
        .CARRYIN(1'b0),
        .CARRYINSEL({1'b0,1'b0,1'b0}),
        .CARRYOUT(NLW_p_1_out__9_CARRYOUT_UNCONNECTED[3:0]),
        .CEA1(1'b0),
        .CEA2(1'b0),
        .CEAD(1'b0),
        .CEALUMODE(1'b0),
        .CEB1(1'b0),
        .CEB2(DSP_ALU_INST_9),
        .CEC(1'b0),
        .CECARRYIN(1'b0),
        .CECTRL(1'b0),
        .CED(1'b0),
        .CEINMODE(1'b0),
        .CEM(1'b0),
        .CEP(1'b0),
        .CLK(AXI4_Lite_ACLK),
        .D({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .INMODE({1'b0,1'b0,1'b0,1'b0,1'b0}),
        .MULTSIGNIN(1'b0),
        .MULTSIGNOUT(NLW_p_1_out__9_MULTSIGNOUT_UNCONNECTED),
        .OPMODE({1'b0,1'b0,1'b0,\out10[17] ,\out10[17] ,1'b0,1'b1,1'b0,1'b1}),
        .OVERFLOW(NLW_p_1_out__9_OVERFLOW_UNCONNECTED),
        .P({NLW_p_1_out__9_P_UNCONNECTED[47:45],p_1_out__9_n_61,p_1_out__9_n_62,p_1_out__9_n_63,p_1_out__9_n_64,p_1_out__9_n_65,p_1_out__9_n_66,p_1_out__9_n_67,p_1_out__9_n_68,p_1_out__9_n_69,p_1_out__9_n_70,out10,p_1_out__9_n_89,p_1_out__9_n_90,p_1_out__9_n_91,p_1_out__9_n_92,p_1_out__9_n_93,p_1_out__9_n_94,p_1_out__9_n_95,p_1_out__9_n_96,p_1_out__9_n_97,p_1_out__9_n_98,p_1_out__9_n_99,p_1_out__9_n_100,p_1_out__9_n_101,p_1_out__9_n_102,p_1_out__9_n_103,p_1_out__9_n_104,p_1_out__9_n_105}),
        .PATTERNBDETECT(NLW_p_1_out__9_PATTERNBDETECT_UNCONNECTED),
        .PATTERNDETECT(NLW_p_1_out__9_PATTERNDETECT_UNCONNECTED),
        .PCIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .PCOUT(NLW_p_1_out__9_PCOUT_UNCONNECTED[47:0]),
        .RSTA(1'b0),
        .RSTALLCARRYIN(1'b0),
        .RSTALUMODE(1'b0),
        .RSTB(reset),
        .RSTC(1'b0),
        .RSTCTRL(1'b0),
        .RSTD(1'b0),
        .RSTINMODE(1'b0),
        .RSTM(1'b0),
        .RSTP(1'b0),
        .UNDERFLOW(NLW_p_1_out__9_UNDERFLOW_UNCONNECTED),
        .XOROUT(NLW_p_1_out__9_XOROUT_UNCONNECTED[7:0]));
  (* SOFT_HLUTNM = "soft_lutpair167" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__9_i_10
       (.I0(in10[18]),
        .I1(Delay10_out1[18]),
        .I2(adc_trigger),
        .O(A__9[18]));
  (* SOFT_HLUTNM = "soft_lutpair166" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__9_i_11
       (.I0(in10[17]),
        .I1(Delay10_out1[17]),
        .I2(adc_trigger),
        .O(A__9[17]));
  (* SOFT_HLUTNM = "soft_lutpair166" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__9_i_12
       (.I0(in10[16]),
        .I1(Delay10_out1[16]),
        .I2(adc_trigger),
        .O(A__9[16]));
  (* SOFT_HLUTNM = "soft_lutpair165" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__9_i_13
       (.I0(in10[15]),
        .I1(Delay10_out1[15]),
        .I2(adc_trigger),
        .O(A__9[15]));
  (* SOFT_HLUTNM = "soft_lutpair165" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__9_i_14
       (.I0(in10[14]),
        .I1(Delay10_out1[14]),
        .I2(adc_trigger),
        .O(A__9[14]));
  (* SOFT_HLUTNM = "soft_lutpair164" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__9_i_15
       (.I0(in10[13]),
        .I1(Delay10_out1[13]),
        .I2(adc_trigger),
        .O(A__9[13]));
  (* SOFT_HLUTNM = "soft_lutpair164" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__9_i_16
       (.I0(in10[12]),
        .I1(Delay10_out1[12]),
        .I2(adc_trigger),
        .O(A__9[12]));
  (* SOFT_HLUTNM = "soft_lutpair163" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__9_i_17
       (.I0(in10[11]),
        .I1(Delay10_out1[11]),
        .I2(adc_trigger),
        .O(A__9[11]));
  (* SOFT_HLUTNM = "soft_lutpair163" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__9_i_18
       (.I0(in10[10]),
        .I1(Delay10_out1[10]),
        .I2(adc_trigger),
        .O(A__9[10]));
  (* SOFT_HLUTNM = "soft_lutpair162" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__9_i_19
       (.I0(in10[9]),
        .I1(Delay10_out1[9]),
        .I2(adc_trigger),
        .O(A__9[9]));
  (* SOFT_HLUTNM = "soft_lutpair171" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__9_i_2
       (.I0(in10[26]),
        .I1(Delay10_out1[26]),
        .I2(adc_trigger),
        .O(A__9[26]));
  (* SOFT_HLUTNM = "soft_lutpair162" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__9_i_20
       (.I0(in10[8]),
        .I1(Delay10_out1[8]),
        .I2(adc_trigger),
        .O(A__9[8]));
  (* SOFT_HLUTNM = "soft_lutpair161" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__9_i_21
       (.I0(in10[7]),
        .I1(Delay10_out1[7]),
        .I2(adc_trigger),
        .O(A__9[7]));
  (* SOFT_HLUTNM = "soft_lutpair161" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__9_i_22
       (.I0(in10[6]),
        .I1(Delay10_out1[6]),
        .I2(adc_trigger),
        .O(A__9[6]));
  (* SOFT_HLUTNM = "soft_lutpair160" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__9_i_23
       (.I0(in10[5]),
        .I1(Delay10_out1[5]),
        .I2(adc_trigger),
        .O(A__9[5]));
  (* SOFT_HLUTNM = "soft_lutpair160" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__9_i_24
       (.I0(in10[4]),
        .I1(Delay10_out1[4]),
        .I2(adc_trigger),
        .O(A__9[4]));
  (* SOFT_HLUTNM = "soft_lutpair159" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__9_i_25
       (.I0(in10[3]),
        .I1(Delay10_out1[3]),
        .I2(adc_trigger),
        .O(A__9[3]));
  (* SOFT_HLUTNM = "soft_lutpair159" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__9_i_26
       (.I0(in10[2]),
        .I1(Delay10_out1[2]),
        .I2(adc_trigger),
        .O(A__9[2]));
  (* SOFT_HLUTNM = "soft_lutpair158" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__9_i_27
       (.I0(in10[1]),
        .I1(Delay10_out1[1]),
        .I2(adc_trigger),
        .O(A__9[1]));
  (* SOFT_HLUTNM = "soft_lutpair158" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__9_i_28
       (.I0(in10[0]),
        .I1(Delay10_out1[0]),
        .I2(adc_trigger),
        .O(p_1_out__9_i_28_n_0));
  (* SOFT_HLUTNM = "soft_lutpair170" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__9_i_3
       (.I0(in10[25]),
        .I1(Delay10_out1[25]),
        .I2(adc_trigger),
        .O(A__9[25]));
  (* SOFT_HLUTNM = "soft_lutpair170" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__9_i_4
       (.I0(in10[24]),
        .I1(Delay10_out1[24]),
        .I2(adc_trigger),
        .O(A__9[24]));
  (* SOFT_HLUTNM = "soft_lutpair169" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__9_i_5
       (.I0(in10[23]),
        .I1(Delay10_out1[23]),
        .I2(adc_trigger),
        .O(A__9[23]));
  (* SOFT_HLUTNM = "soft_lutpair169" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__9_i_6
       (.I0(in10[22]),
        .I1(Delay10_out1[22]),
        .I2(adc_trigger),
        .O(A__9[22]));
  (* SOFT_HLUTNM = "soft_lutpair168" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__9_i_7
       (.I0(in10[21]),
        .I1(Delay10_out1[21]),
        .I2(adc_trigger),
        .O(A__9[21]));
  (* SOFT_HLUTNM = "soft_lutpair168" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__9_i_8
       (.I0(in10[20]),
        .I1(Delay10_out1[20]),
        .I2(adc_trigger),
        .O(A__9[20]));
  (* SOFT_HLUTNM = "soft_lutpair167" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out__9_i_9
       (.I0(in10[19]),
        .I1(Delay10_out1[19]),
        .I2(adc_trigger),
        .O(A__9[19]));
  (* SOFT_HLUTNM = "soft_lutpair32" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out_i_10
       (.I0(in0[18]),
        .I1(Delay_out1[18]),
        .I2(adc_trigger),
        .O(A[18]));
  (* SOFT_HLUTNM = "soft_lutpair31" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out_i_11
       (.I0(in0[17]),
        .I1(Delay_out1[17]),
        .I2(adc_trigger),
        .O(A[17]));
  (* SOFT_HLUTNM = "soft_lutpair31" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out_i_12
       (.I0(in0[16]),
        .I1(Delay_out1[16]),
        .I2(adc_trigger),
        .O(A[16]));
  (* SOFT_HLUTNM = "soft_lutpair30" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out_i_13
       (.I0(in0[15]),
        .I1(Delay_out1[15]),
        .I2(adc_trigger),
        .O(A[15]));
  (* SOFT_HLUTNM = "soft_lutpair30" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out_i_14
       (.I0(in0[14]),
        .I1(Delay_out1[14]),
        .I2(adc_trigger),
        .O(A[14]));
  (* SOFT_HLUTNM = "soft_lutpair29" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out_i_15
       (.I0(in0[13]),
        .I1(Delay_out1[13]),
        .I2(adc_trigger),
        .O(A[13]));
  (* SOFT_HLUTNM = "soft_lutpair29" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out_i_16
       (.I0(in0[12]),
        .I1(Delay_out1[12]),
        .I2(adc_trigger),
        .O(A[12]));
  (* SOFT_HLUTNM = "soft_lutpair28" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out_i_17
       (.I0(in0[11]),
        .I1(Delay_out1[11]),
        .I2(adc_trigger),
        .O(A[11]));
  (* SOFT_HLUTNM = "soft_lutpair28" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out_i_18
       (.I0(in0[10]),
        .I1(Delay_out1[10]),
        .I2(adc_trigger),
        .O(A[10]));
  (* SOFT_HLUTNM = "soft_lutpair27" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out_i_19
       (.I0(in0[9]),
        .I1(Delay_out1[9]),
        .I2(adc_trigger),
        .O(A[9]));
  (* SOFT_HLUTNM = "soft_lutpair36" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out_i_2
       (.I0(in0[26]),
        .I1(Delay_out1[26]),
        .I2(adc_trigger),
        .O(A[26]));
  (* SOFT_HLUTNM = "soft_lutpair27" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out_i_20
       (.I0(in0[8]),
        .I1(Delay_out1[8]),
        .I2(adc_trigger),
        .O(A[8]));
  (* SOFT_HLUTNM = "soft_lutpair26" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out_i_21
       (.I0(in0[7]),
        .I1(Delay_out1[7]),
        .I2(adc_trigger),
        .O(A[7]));
  (* SOFT_HLUTNM = "soft_lutpair26" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out_i_22
       (.I0(in0[6]),
        .I1(Delay_out1[6]),
        .I2(adc_trigger),
        .O(A[6]));
  (* SOFT_HLUTNM = "soft_lutpair25" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out_i_23
       (.I0(in0[5]),
        .I1(Delay_out1[5]),
        .I2(adc_trigger),
        .O(A[5]));
  (* SOFT_HLUTNM = "soft_lutpair25" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out_i_24
       (.I0(in0[4]),
        .I1(Delay_out1[4]),
        .I2(adc_trigger),
        .O(A[4]));
  (* SOFT_HLUTNM = "soft_lutpair24" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out_i_25
       (.I0(in0[3]),
        .I1(Delay_out1[3]),
        .I2(adc_trigger),
        .O(A[3]));
  (* SOFT_HLUTNM = "soft_lutpair24" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out_i_26
       (.I0(in0[2]),
        .I1(Delay_out1[2]),
        .I2(adc_trigger),
        .O(A[2]));
  (* SOFT_HLUTNM = "soft_lutpair23" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out_i_27
       (.I0(in0[1]),
        .I1(Delay_out1[1]),
        .I2(adc_trigger),
        .O(A[1]));
  (* SOFT_HLUTNM = "soft_lutpair23" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out_i_28
       (.I0(in0[0]),
        .I1(Delay_out1[0]),
        .I2(adc_trigger),
        .O(p_1_out_i_28_n_0));
  (* SOFT_HLUTNM = "soft_lutpair35" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out_i_3
       (.I0(in0[25]),
        .I1(Delay_out1[25]),
        .I2(adc_trigger),
        .O(A[25]));
  (* SOFT_HLUTNM = "soft_lutpair35" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out_i_4
       (.I0(in0[24]),
        .I1(Delay_out1[24]),
        .I2(adc_trigger),
        .O(A[24]));
  (* SOFT_HLUTNM = "soft_lutpair34" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out_i_5
       (.I0(in0[23]),
        .I1(Delay_out1[23]),
        .I2(adc_trigger),
        .O(A[23]));
  (* SOFT_HLUTNM = "soft_lutpair34" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out_i_6
       (.I0(in0[22]),
        .I1(Delay_out1[22]),
        .I2(adc_trigger),
        .O(A[22]));
  (* SOFT_HLUTNM = "soft_lutpair33" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out_i_7
       (.I0(in0[21]),
        .I1(Delay_out1[21]),
        .I2(adc_trigger),
        .O(A[21]));
  (* SOFT_HLUTNM = "soft_lutpair33" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out_i_8
       (.I0(in0[20]),
        .I1(Delay_out1[20]),
        .I2(adc_trigger),
        .O(A[20]));
  (* SOFT_HLUTNM = "soft_lutpair32" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    p_1_out_i_9
       (.I0(in0[19]),
        .I1(Delay_out1[19]),
        .I2(adc_trigger),
        .O(A[19]));
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
