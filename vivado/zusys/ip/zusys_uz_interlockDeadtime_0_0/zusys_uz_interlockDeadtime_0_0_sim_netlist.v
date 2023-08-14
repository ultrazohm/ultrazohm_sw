// Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// --------------------------------------------------------------------------------
// Tool Version: Vivado v.2020.1.1 (win64) Build 2960000 Wed Aug  5 22:57:20 MDT 2020
// Date        : Fri Jan 28 14:44:28 2022
// Host        : enc177112 running 64-bit major release  (build 9200)
// Command     : write_verilog -force -mode funcsim
//               c:/GIT/UltraZohm/software/ultrazohm_sw_develop/vivado/zusys/ip/zusys_uz_interlockDeadtime_0_0/zusys_uz_interlockDeadtime_0_0_sim_netlist.v
// Design      : zusys_uz_interlockDeadtime_0_0
// Purpose     : This verilog netlist is a functional simulation representation of the design and should not be modified
//               or synthesized. This netlist cannot be used for SDF annotated simulation.
// Device      : xczu9eg-ffvc900-1-e
// --------------------------------------------------------------------------------
`timescale 1 ps / 1 ps

(* CHECK_LICENSE_TYPE = "zusys_uz_interlockDeadtime_0_0,uz_interlockDeadtime2L,{}" *) (* downgradeipidentifiedwarnings = "yes" *) (* ip_definition_source = "package_project" *) 
(* x_core_info = "uz_interlockDeadtime2L,Vivado 2020.1.1" *) 
(* NotValidForBitStream *)
module zusys_uz_interlockDeadtime_0_0
   (IPCORE_CLK,
    IPCORE_RESETN,
    S0,
    S1,
    S2,
    S3,
    S4,
    S5,
    AXI4_ACLK,
    AXI4_ARESETN,
    AXI4_AWID,
    AXI4_AWADDR,
    AXI4_AWLEN,
    AXI4_AWSIZE,
    AXI4_AWBURST,
    AXI4_AWLOCK,
    AXI4_AWCACHE,
    AXI4_AWPROT,
    AXI4_AWVALID,
    AXI4_WDATA,
    AXI4_WSTRB,
    AXI4_WLAST,
    AXI4_WVALID,
    AXI4_BREADY,
    AXI4_ARID,
    AXI4_ARADDR,
    AXI4_ARLEN,
    AXI4_ARSIZE,
    AXI4_ARBURST,
    AXI4_ARLOCK,
    AXI4_ARCACHE,
    AXI4_ARPROT,
    AXI4_ARVALID,
    AXI4_RREADY,
    s0_out,
    s1_out,
    s2_out,
    s3_out,
    s4_out,
    s5_out,
    enableFB,
    AXI4_AWREADY,
    AXI4_WREADY,
    AXI4_BID,
    AXI4_BRESP,
    AXI4_BVALID,
    AXI4_ARREADY,
    AXI4_RID,
    AXI4_RDATA,
    AXI4_RRESP,
    AXI4_RLAST,
    AXI4_RVALID);
  (* x_interface_info = "xilinx.com:signal:clock:1.0 IPCORE_CLK CLK" *) (* x_interface_parameter = "XIL_INTERFACENAME IPCORE_CLK, ASSOCIATED_RESET IPCORE_RESETN, FREQ_HZ 100000000, FREQ_TOLERANCE_HZ 0, PHASE 0.000, CLK_DOMAIN zusys_zynq_ultra_ps_e_0_0_pl_clk0, INSERT_VIP 0" *) input IPCORE_CLK;
  (* x_interface_info = "xilinx.com:signal:reset:1.0 IPCORE_RESETN RST" *) (* x_interface_parameter = "XIL_INTERFACENAME IPCORE_RESETN, POLARITY ACTIVE_LOW, INSERT_VIP 0" *) input IPCORE_RESETN;
  input S0;
  input S1;
  input S2;
  input S3;
  input S4;
  input S5;
  (* x_interface_info = "xilinx.com:signal:clock:1.0 AXI4_signal_clock CLK" *) (* x_interface_parameter = "XIL_INTERFACENAME AXI4_signal_clock, ASSOCIATED_BUSIF AXI4, ASSOCIATED_RESET AXI4_ARESETN, FREQ_HZ 100000000, FREQ_TOLERANCE_HZ 0, PHASE 0.000, CLK_DOMAIN zusys_zynq_ultra_ps_e_0_0_pl_clk0, INSERT_VIP 0" *) input AXI4_ACLK;
  (* x_interface_info = "xilinx.com:signal:reset:1.0 AXI4_signal_reset RST" *) (* x_interface_parameter = "XIL_INTERFACENAME AXI4_signal_reset, POLARITY ACTIVE_LOW, INSERT_VIP 0" *) input AXI4_ARESETN;
  (* x_interface_info = "xilinx.com:interface:aximm:1.0 AXI4 AWID" *) (* x_interface_parameter = "XIL_INTERFACENAME AXI4, DATA_WIDTH 32, PROTOCOL AXI4, FREQ_HZ 100000000, ID_WIDTH 12, ADDR_WIDTH 16, AWUSER_WIDTH 0, ARUSER_WIDTH 0, WUSER_WIDTH 0, RUSER_WIDTH 0, BUSER_WIDTH 0, READ_WRITE_MODE READ_WRITE, HAS_BURST 1, HAS_LOCK 1, HAS_PROT 1, HAS_CACHE 1, HAS_QOS 0, HAS_REGION 0, HAS_WSTRB 1, HAS_BRESP 1, HAS_RRESP 1, SUPPORTS_NARROW_BURST 1, NUM_READ_OUTSTANDING 2, NUM_WRITE_OUTSTANDING 2, MAX_BURST_LENGTH 256, PHASE 0.000, CLK_DOMAIN zusys_zynq_ultra_ps_e_0_0_pl_clk0, NUM_READ_THREADS 1, NUM_WRITE_THREADS 1, RUSER_BITS_PER_BYTE 0, WUSER_BITS_PER_BYTE 0, INSERT_VIP 0" *) input [11:0]AXI4_AWID;
  (* x_interface_info = "xilinx.com:interface:aximm:1.0 AXI4 AWADDR" *) input [15:0]AXI4_AWADDR;
  (* x_interface_info = "xilinx.com:interface:aximm:1.0 AXI4 AWLEN" *) input [7:0]AXI4_AWLEN;
  (* x_interface_info = "xilinx.com:interface:aximm:1.0 AXI4 AWSIZE" *) input [2:0]AXI4_AWSIZE;
  (* x_interface_info = "xilinx.com:interface:aximm:1.0 AXI4 AWBURST" *) input [1:0]AXI4_AWBURST;
  (* x_interface_info = "xilinx.com:interface:aximm:1.0 AXI4 AWLOCK" *) input AXI4_AWLOCK;
  (* x_interface_info = "xilinx.com:interface:aximm:1.0 AXI4 AWCACHE" *) input [3:0]AXI4_AWCACHE;
  (* x_interface_info = "xilinx.com:interface:aximm:1.0 AXI4 AWPROT" *) input [2:0]AXI4_AWPROT;
  (* x_interface_info = "xilinx.com:interface:aximm:1.0 AXI4 AWVALID" *) input AXI4_AWVALID;
  (* x_interface_info = "xilinx.com:interface:aximm:1.0 AXI4 WDATA" *) input [31:0]AXI4_WDATA;
  (* x_interface_info = "xilinx.com:interface:aximm:1.0 AXI4 WSTRB" *) input [3:0]AXI4_WSTRB;
  (* x_interface_info = "xilinx.com:interface:aximm:1.0 AXI4 WLAST" *) input AXI4_WLAST;
  (* x_interface_info = "xilinx.com:interface:aximm:1.0 AXI4 WVALID" *) input AXI4_WVALID;
  (* x_interface_info = "xilinx.com:interface:aximm:1.0 AXI4 BREADY" *) input AXI4_BREADY;
  (* x_interface_info = "xilinx.com:interface:aximm:1.0 AXI4 ARID" *) input [11:0]AXI4_ARID;
  (* x_interface_info = "xilinx.com:interface:aximm:1.0 AXI4 ARADDR" *) input [15:0]AXI4_ARADDR;
  (* x_interface_info = "xilinx.com:interface:aximm:1.0 AXI4 ARLEN" *) input [7:0]AXI4_ARLEN;
  (* x_interface_info = "xilinx.com:interface:aximm:1.0 AXI4 ARSIZE" *) input [2:0]AXI4_ARSIZE;
  (* x_interface_info = "xilinx.com:interface:aximm:1.0 AXI4 ARBURST" *) input [1:0]AXI4_ARBURST;
  (* x_interface_info = "xilinx.com:interface:aximm:1.0 AXI4 ARLOCK" *) input AXI4_ARLOCK;
  (* x_interface_info = "xilinx.com:interface:aximm:1.0 AXI4 ARCACHE" *) input [3:0]AXI4_ARCACHE;
  (* x_interface_info = "xilinx.com:interface:aximm:1.0 AXI4 ARPROT" *) input [2:0]AXI4_ARPROT;
  (* x_interface_info = "xilinx.com:interface:aximm:1.0 AXI4 ARVALID" *) input AXI4_ARVALID;
  (* x_interface_info = "xilinx.com:interface:aximm:1.0 AXI4 RREADY" *) input AXI4_RREADY;
  output s0_out;
  output s1_out;
  output s2_out;
  output s3_out;
  output s4_out;
  output s5_out;
  output enableFB;
  (* x_interface_info = "xilinx.com:interface:aximm:1.0 AXI4 AWREADY" *) output AXI4_AWREADY;
  (* x_interface_info = "xilinx.com:interface:aximm:1.0 AXI4 WREADY" *) output AXI4_WREADY;
  (* x_interface_info = "xilinx.com:interface:aximm:1.0 AXI4 BID" *) output [11:0]AXI4_BID;
  (* x_interface_info = "xilinx.com:interface:aximm:1.0 AXI4 BRESP" *) output [1:0]AXI4_BRESP;
  (* x_interface_info = "xilinx.com:interface:aximm:1.0 AXI4 BVALID" *) output AXI4_BVALID;
  (* x_interface_info = "xilinx.com:interface:aximm:1.0 AXI4 ARREADY" *) output AXI4_ARREADY;
  (* x_interface_info = "xilinx.com:interface:aximm:1.0 AXI4 RID" *) output [11:0]AXI4_RID;
  (* x_interface_info = "xilinx.com:interface:aximm:1.0 AXI4 RDATA" *) output [31:0]AXI4_RDATA;
  (* x_interface_info = "xilinx.com:interface:aximm:1.0 AXI4 RRESP" *) output [1:0]AXI4_RRESP;
  (* x_interface_info = "xilinx.com:interface:aximm:1.0 AXI4 RLAST" *) output AXI4_RLAST;
  (* x_interface_info = "xilinx.com:interface:aximm:1.0 AXI4 RVALID" *) output AXI4_RVALID;

  wire \<const0> ;
  wire AXI4_ACLK;
  wire [15:0]AXI4_ARADDR;
  wire [1:0]AXI4_ARBURST;
  wire AXI4_ARESETN;
  wire [11:0]AXI4_ARID;
  wire [7:0]AXI4_ARLEN;
  wire AXI4_ARREADY;
  wire AXI4_ARVALID;
  wire [15:0]AXI4_AWADDR;
  wire [1:0]AXI4_AWBURST;
  wire [11:0]AXI4_AWID;
  wire AXI4_AWREADY;
  wire AXI4_AWVALID;
  wire [11:0]AXI4_BID;
  wire AXI4_BREADY;
  wire AXI4_BVALID;
  wire [31:0]AXI4_RDATA;
  wire [11:0]AXI4_RID;
  wire AXI4_RLAST;
  wire AXI4_RREADY;
  wire AXI4_RVALID;
  wire [31:0]AXI4_WDATA;
  wire AXI4_WLAST;
  wire AXI4_WREADY;
  wire [3:0]AXI4_WSTRB;
  wire AXI4_WVALID;
  wire IPCORE_CLK;
  wire IPCORE_RESETN;
  wire S0;
  wire S1;
  wire S2;
  wire S3;
  wire S4;
  wire S5;
  wire enableFB;
  wire s0_out;
  wire s1_out;
  wire s2_out;
  wire s3_out;
  wire s4_out;
  wire s5_out;

  assign AXI4_BRESP[1] = \<const0> ;
  assign AXI4_BRESP[0] = \<const0> ;
  assign AXI4_RRESP[1] = \<const0> ;
  assign AXI4_RRESP[0] = \<const0> ;
  GND GND
       (.G(\<const0> ));
  zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L U0
       (.AXI4_ACLK(AXI4_ACLK),
        .AXI4_ARADDR(AXI4_ARADDR[15:2]),
        .AXI4_ARBURST(AXI4_ARBURST),
        .AXI4_ARESETN(AXI4_ARESETN),
        .AXI4_ARID(AXI4_ARID),
        .AXI4_ARLEN(AXI4_ARLEN),
        .AXI4_ARREADY(AXI4_ARREADY),
        .AXI4_ARVALID(AXI4_ARVALID),
        .AXI4_AWADDR(AXI4_AWADDR[15:2]),
        .AXI4_AWBURST(AXI4_AWBURST),
        .AXI4_AWID(AXI4_AWID),
        .AXI4_AWREADY(AXI4_AWREADY),
        .AXI4_AWVALID(AXI4_AWVALID),
        .AXI4_BID(AXI4_BID),
        .AXI4_BREADY(AXI4_BREADY),
        .AXI4_BVALID(AXI4_BVALID),
        .AXI4_RDATA(AXI4_RDATA),
        .AXI4_RID(AXI4_RID),
        .AXI4_RLAST(AXI4_RLAST),
        .AXI4_RREADY(AXI4_RREADY),
        .AXI4_WDATA(AXI4_WDATA[9:0]),
        .AXI4_WLAST(AXI4_WLAST),
        .AXI4_WREADY(AXI4_WREADY),
        .AXI4_WSTRB(AXI4_WSTRB),
        .AXI4_WVALID(AXI4_WVALID),
        .IPCORE_CLK(IPCORE_CLK),
        .IPCORE_RESETN(IPCORE_RESETN),
        .S0(S0),
        .S1(S1),
        .S2(S2),
        .S3(S3),
        .S4(S4),
        .S5(S5),
        .enableFB(enableFB),
        .out_valid_reg(AXI4_RVALID),
        .s0_out(s0_out),
        .s1_out(s1_out),
        .s2_out(s2_out),
        .s3_out(s3_out),
        .s4_out(s4_out),
        .s5_out(s5_out));
endmodule

(* ORIG_REF_NAME = "uz_interlockDeadtime2L" *) 
module zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L
   (AXI4_BVALID,
    AXI4_WREADY,
    enableFB,
    out_valid_reg,
    AXI4_RDATA,
    AXI4_RID,
    AXI4_BID,
    AXI4_ARREADY,
    AXI4_AWREADY,
    s1_out,
    s0_out,
    s3_out,
    s2_out,
    s5_out,
    s4_out,
    AXI4_RLAST,
    AXI4_ACLK,
    AXI4_WSTRB,
    IPCORE_CLK,
    AXI4_WDATA,
    AXI4_ARID,
    AXI4_AWID,
    AXI4_ARADDR,
    AXI4_AWADDR,
    AXI4_RREADY,
    AXI4_ARESETN,
    AXI4_AWVALID,
    AXI4_BREADY,
    AXI4_ARVALID,
    AXI4_WVALID,
    AXI4_WLAST,
    IPCORE_RESETN,
    AXI4_ARLEN,
    S0,
    S1,
    S2,
    S3,
    S4,
    S5,
    AXI4_ARBURST,
    AXI4_AWBURST);
  output AXI4_BVALID;
  output AXI4_WREADY;
  output enableFB;
  output out_valid_reg;
  output [31:0]AXI4_RDATA;
  output [11:0]AXI4_RID;
  output [11:0]AXI4_BID;
  output AXI4_ARREADY;
  output AXI4_AWREADY;
  output s1_out;
  output s0_out;
  output s3_out;
  output s2_out;
  output s5_out;
  output s4_out;
  output AXI4_RLAST;
  input AXI4_ACLK;
  input [3:0]AXI4_WSTRB;
  input IPCORE_CLK;
  input [9:0]AXI4_WDATA;
  input [11:0]AXI4_ARID;
  input [11:0]AXI4_AWID;
  input [13:0]AXI4_ARADDR;
  input [13:0]AXI4_AWADDR;
  input AXI4_RREADY;
  input AXI4_ARESETN;
  input AXI4_AWVALID;
  input AXI4_BREADY;
  input AXI4_ARVALID;
  input AXI4_WVALID;
  input AXI4_WLAST;
  input IPCORE_RESETN;
  input [7:0]AXI4_ARLEN;
  input S0;
  input S1;
  input S2;
  input S3;
  input S4;
  input S5;
  input [1:0]AXI4_ARBURST;
  input [1:0]AXI4_AWBURST;

  wire AXI4_ACLK;
  wire [13:0]AXI4_ARADDR;
  wire [1:0]AXI4_ARBURST;
  wire AXI4_ARESETN;
  wire [11:0]AXI4_ARID;
  wire [7:0]AXI4_ARLEN;
  wire AXI4_ARREADY;
  wire AXI4_ARVALID;
  wire [13:0]AXI4_AWADDR;
  wire [1:0]AXI4_AWBURST;
  wire [11:0]AXI4_AWID;
  wire AXI4_AWREADY;
  wire AXI4_AWVALID;
  wire [11:0]AXI4_BID;
  wire AXI4_BREADY;
  wire AXI4_BVALID;
  wire [31:0]AXI4_RDATA;
  wire [11:0]AXI4_RID;
  wire AXI4_RLAST;
  wire AXI4_RREADY;
  wire [9:0]AXI4_WDATA;
  wire AXI4_WLAST;
  wire AXI4_WREADY;
  wire [3:0]AXI4_WSTRB;
  wire AXI4_WVALID;
  wire [9:0]Delay2_out1;
  wire Delay3_out1;
  wire IPCORE_CLK;
  wire IPCORE_RESETN;
  wire S0;
  wire S1;
  wire S2;
  wire S3;
  wire S4;
  wire S5;
  wire [9:0]axi_DelayCycles;
  wire axi_EnableOutput;
  wire axi_InverseBotSwitch;
  wire enableFB;
  wire out_valid_reg;
  wire reset_in;
  wire reset_x;
  wire s0_out;
  wire s1_out;
  wire s2_out;
  wire s3_out;
  wire s4_out;
  wire s5_out;
  wire u_uz_interlockDeadtime2L_axi4_inst_n_12;
  wire u_uz_interlockDeadtime2L_axi4_inst_n_13;
  wire u_uz_interlockDeadtime2L_axi4_inst_n_14;
  wire u_uz_interlockDeadtime2L_axi4_inst_n_15;
  wire u_uz_interlockDeadtime2L_axi4_inst_n_16;
  wire u_uz_interlockDeadtime2L_axi4_inst_n_17;
  wire u_uz_interlockDeadtime2L_axi4_inst_n_18;
  wire \u_uz_interlockDeadtime2L_axi4_module_inst/soft_reset ;
  wire \u_uz_interlockDeadtime2L_src_uz_interlockDeadtime2L/GEN_LABEL3[0].u_DeadtimeModule/HDL_Counter_out1 ;
  wire \u_uz_interlockDeadtime2L_src_uz_interlockDeadtime2L/GEN_LABEL3[0].u_DeadtimeModule/PipelineDelay1_out1 ;
  wire \u_uz_interlockDeadtime2L_src_uz_interlockDeadtime2L/GEN_LABEL3[1].u_DeadtimeModule/HDL_Counter_out1 ;
  wire \u_uz_interlockDeadtime2L_src_uz_interlockDeadtime2L/GEN_LABEL3[1].u_DeadtimeModule/PipelineDelay1_out1 ;
  wire \u_uz_interlockDeadtime2L_src_uz_interlockDeadtime2L/GEN_LABEL3[2].u_DeadtimeModule/HDL_Counter_out1 ;
  wire \u_uz_interlockDeadtime2L_src_uz_interlockDeadtime2L/GEN_LABEL3[2].u_DeadtimeModule/PipelineDelay1_out1 ;
  wire \u_uz_interlockDeadtime2L_src_uz_interlockDeadtime2L/GEN_LABEL3[3].u_DeadtimeModule/HDL_Counter_out1 ;
  wire \u_uz_interlockDeadtime2L_src_uz_interlockDeadtime2L/GEN_LABEL3[3].u_DeadtimeModule/PipelineDelay1_out1 ;
  wire \u_uz_interlockDeadtime2L_src_uz_interlockDeadtime2L/GEN_LABEL3[4].u_DeadtimeModule/HDL_Counter_out1 ;
  wire \u_uz_interlockDeadtime2L_src_uz_interlockDeadtime2L/GEN_LABEL3[4].u_DeadtimeModule/PipelineDelay1_out1 ;
  wire \u_uz_interlockDeadtime2L_src_uz_interlockDeadtime2L/GEN_LABEL3[5].u_DeadtimeModule/HDL_Counter_out1 ;
  wire \u_uz_interlockDeadtime2L_src_uz_interlockDeadtime2L/GEN_LABEL3[5].u_DeadtimeModule/PipelineDelay1_out1 ;
  wire write_axi_enable;

  zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_axi4 u_uz_interlockDeadtime2L_axi4_inst
       (.AXI4_ACLK(AXI4_ACLK),
        .AXI4_ARADDR(AXI4_ARADDR),
        .AXI4_ARBURST(AXI4_ARBURST),
        .AXI4_ARESETN(AXI4_ARESETN),
        .AXI4_ARID(AXI4_ARID),
        .AXI4_ARLEN(AXI4_ARLEN),
        .AXI4_ARREADY(AXI4_ARREADY),
        .AXI4_ARVALID(AXI4_ARVALID),
        .AXI4_AWADDR(AXI4_AWADDR),
        .AXI4_AWBURST(AXI4_AWBURST),
        .AXI4_AWID(AXI4_AWID),
        .AXI4_AWREADY(AXI4_AWREADY),
        .AXI4_AWVALID(AXI4_AWVALID),
        .AXI4_BID(AXI4_BID),
        .AXI4_BREADY(AXI4_BREADY),
        .AXI4_RDATA(AXI4_RDATA),
        .AXI4_RID(AXI4_RID),
        .AXI4_RLAST(AXI4_RLAST),
        .AXI4_RREADY(AXI4_RREADY),
        .AXI4_WDATA(AXI4_WDATA),
        .AXI4_WLAST(AXI4_WLAST),
        .AXI4_WSTRB(AXI4_WSTRB),
        .AXI4_WVALID(AXI4_WVALID),
        .Delay3_out1(Delay3_out1),
        .E(\u_uz_interlockDeadtime2L_src_uz_interlockDeadtime2L/GEN_LABEL3[0].u_DeadtimeModule/HDL_Counter_out1 ),
        .IPCORE_RESETN(IPCORE_RESETN),
        .PipelineDelay1_out1(\u_uz_interlockDeadtime2L_src_uz_interlockDeadtime2L/GEN_LABEL3[0].u_DeadtimeModule/PipelineDelay1_out1 ),
        .PipelineDelay1_out1_0(\u_uz_interlockDeadtime2L_src_uz_interlockDeadtime2L/GEN_LABEL3[1].u_DeadtimeModule/PipelineDelay1_out1 ),
        .PipelineDelay1_out1_1(\u_uz_interlockDeadtime2L_src_uz_interlockDeadtime2L/GEN_LABEL3[2].u_DeadtimeModule/PipelineDelay1_out1 ),
        .PipelineDelay1_out1_2(\u_uz_interlockDeadtime2L_src_uz_interlockDeadtime2L/GEN_LABEL3[3].u_DeadtimeModule/PipelineDelay1_out1 ),
        .PipelineDelay1_out1_3(\u_uz_interlockDeadtime2L_src_uz_interlockDeadtime2L/GEN_LABEL3[4].u_DeadtimeModule/PipelineDelay1_out1 ),
        .PipelineDelay1_out1_4(\u_uz_interlockDeadtime2L_src_uz_interlockDeadtime2L/GEN_LABEL3[5].u_DeadtimeModule/PipelineDelay1_out1 ),
        .Q({AXI4_BVALID,AXI4_WREADY}),
        .S0(S0),
        .S1(S1),
        .S2(S2),
        .S3(S3),
        .S4(S4),
        .S5(S5),
        .SR(u_uz_interlockDeadtime2L_axi4_inst_n_12),
        .axi_EnableOutput(axi_EnableOutput),
        .axi_InverseBotSwitch(axi_InverseBotSwitch),
        .\data_reg_axi_DelayCycles_1_1_reg[9] (axi_DelayCycles),
        .data_reg_axi_enable_1_1_reg(u_uz_interlockDeadtime2L_axi4_inst_n_13),
        .data_reg_axi_enable_1_1_reg_0(u_uz_interlockDeadtime2L_axi4_inst_n_14),
        .data_reg_axi_enable_1_1_reg_1(u_uz_interlockDeadtime2L_axi4_inst_n_15),
        .data_reg_axi_enable_1_1_reg_2(u_uz_interlockDeadtime2L_axi4_inst_n_16),
        .data_reg_axi_enable_1_1_reg_3(u_uz_interlockDeadtime2L_axi4_inst_n_17),
        .data_reg_axi_enable_1_1_reg_4(u_uz_interlockDeadtime2L_axi4_inst_n_18),
        .data_reg_axi_enable_1_1_reg_5(\u_uz_interlockDeadtime2L_src_uz_interlockDeadtime2L/GEN_LABEL3[1].u_DeadtimeModule/HDL_Counter_out1 ),
        .data_reg_axi_enable_1_1_reg_6(\u_uz_interlockDeadtime2L_src_uz_interlockDeadtime2L/GEN_LABEL3[2].u_DeadtimeModule/HDL_Counter_out1 ),
        .data_reg_axi_enable_1_1_reg_7(\u_uz_interlockDeadtime2L_src_uz_interlockDeadtime2L/GEN_LABEL3[3].u_DeadtimeModule/HDL_Counter_out1 ),
        .data_reg_axi_enable_1_1_reg_8(\u_uz_interlockDeadtime2L_src_uz_interlockDeadtime2L/GEN_LABEL3[4].u_DeadtimeModule/HDL_Counter_out1 ),
        .data_reg_axi_enable_1_1_reg_9(\u_uz_interlockDeadtime2L_src_uz_interlockDeadtime2L/GEN_LABEL3[5].u_DeadtimeModule/HDL_Counter_out1 ),
        .out_valid_reg(out_valid_reg),
        .\read_reg_axi_fb_DelayCycles_reg[9] (Delay2_out1),
        .read_reg_axi_fb_enable_reg(enableFB),
        .reset_in(reset_in),
        .reset_x(reset_x),
        .soft_reset(\u_uz_interlockDeadtime2L_axi4_module_inst/soft_reset ),
        .write_axi_enable(write_axi_enable));
  zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_dut u_uz_interlockDeadtime2L_dut_inst
       (.D(axi_DelayCycles),
        .Delay2_delOut_reg(u_uz_interlockDeadtime2L_axi4_inst_n_18),
        .Delay3_out1(Delay3_out1),
        .Delay_out1_reg(enableFB),
        .E(\u_uz_interlockDeadtime2L_src_uz_interlockDeadtime2L/GEN_LABEL3[0].u_DeadtimeModule/HDL_Counter_out1 ),
        .\HDL_Counter_out1_reg[9] (u_uz_interlockDeadtime2L_axi4_inst_n_13),
        .\HDL_Counter_out1_reg[9]_0 (\u_uz_interlockDeadtime2L_src_uz_interlockDeadtime2L/GEN_LABEL3[1].u_DeadtimeModule/HDL_Counter_out1 ),
        .\HDL_Counter_out1_reg[9]_1 (u_uz_interlockDeadtime2L_axi4_inst_n_14),
        .\HDL_Counter_out1_reg[9]_2 (\u_uz_interlockDeadtime2L_src_uz_interlockDeadtime2L/GEN_LABEL3[2].u_DeadtimeModule/HDL_Counter_out1 ),
        .\HDL_Counter_out1_reg[9]_3 (u_uz_interlockDeadtime2L_axi4_inst_n_15),
        .\HDL_Counter_out1_reg[9]_4 (\u_uz_interlockDeadtime2L_src_uz_interlockDeadtime2L/GEN_LABEL3[3].u_DeadtimeModule/HDL_Counter_out1 ),
        .\HDL_Counter_out1_reg[9]_5 (u_uz_interlockDeadtime2L_axi4_inst_n_16),
        .\HDL_Counter_out1_reg[9]_6 (\u_uz_interlockDeadtime2L_src_uz_interlockDeadtime2L/GEN_LABEL3[4].u_DeadtimeModule/HDL_Counter_out1 ),
        .\HDL_Counter_out1_reg[9]_7 (u_uz_interlockDeadtime2L_axi4_inst_n_17),
        .\HDL_Counter_out1_reg[9]_8 (\u_uz_interlockDeadtime2L_src_uz_interlockDeadtime2L/GEN_LABEL3[5].u_DeadtimeModule/HDL_Counter_out1 ),
        .IPCORE_CLK(IPCORE_CLK),
        .PipelineDelay1_out1(\u_uz_interlockDeadtime2L_src_uz_interlockDeadtime2L/GEN_LABEL3[0].u_DeadtimeModule/PipelineDelay1_out1 ),
        .PipelineDelay1_out1_0(\u_uz_interlockDeadtime2L_src_uz_interlockDeadtime2L/GEN_LABEL3[1].u_DeadtimeModule/PipelineDelay1_out1 ),
        .PipelineDelay1_out1_1(\u_uz_interlockDeadtime2L_src_uz_interlockDeadtime2L/GEN_LABEL3[2].u_DeadtimeModule/PipelineDelay1_out1 ),
        .PipelineDelay1_out1_2(\u_uz_interlockDeadtime2L_src_uz_interlockDeadtime2L/GEN_LABEL3[3].u_DeadtimeModule/PipelineDelay1_out1 ),
        .PipelineDelay1_out1_3(\u_uz_interlockDeadtime2L_src_uz_interlockDeadtime2L/GEN_LABEL3[4].u_DeadtimeModule/PipelineDelay1_out1 ),
        .PipelineDelay1_out1_4(\u_uz_interlockDeadtime2L_src_uz_interlockDeadtime2L/GEN_LABEL3[5].u_DeadtimeModule/PipelineDelay1_out1 ),
        .Q(Delay2_out1),
        .S0(S0),
        .S1(S1),
        .S2(S2),
        .S3(S3),
        .S4(S4),
        .S5(S5),
        .SR(u_uz_interlockDeadtime2L_axi4_inst_n_12),
        .axi_EnableOutput(axi_EnableOutput),
        .axi_InverseBotSwitch(axi_InverseBotSwitch),
        .reset_x(reset_x),
        .s0_out(s0_out),
        .s1_out(s1_out),
        .s2_out(s2_out),
        .s3_out(s3_out),
        .s4_out(s4_out),
        .s5_out(s5_out),
        .write_axi_enable(write_axi_enable));
  zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_reset_sync u_uz_interlockDeadtime2L_reset_sync_inst
       (.AXI4_ARESETN(AXI4_ARESETN),
        .IPCORE_CLK(IPCORE_CLK),
        .IPCORE_RESETN(IPCORE_RESETN),
        .reset_in(reset_in),
        .reset_x(reset_x),
        .soft_reset(\u_uz_interlockDeadtime2L_axi4_module_inst/soft_reset ));
endmodule

(* ORIG_REF_NAME = "uz_interlockDeadtime2L_SimpleDualPortRAM_generic" *) 
module zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_SimpleDualPortRAM_generic
   (axi4_rd_active_reg,
    axi4_rd_active_reg_0,
    \axi4_raddr_reg[8] ,
    \waddr_reg[15] ,
    \waddr_reg[11] ,
    E,
    D,
    data_int,
    w_d1_reg,
    \data_int_reg[1]_0 ,
    Q,
    read_reg_axi_fb_enable,
    read_reg_axi_fb_InverseBotSwitch,
    read_reg_ip_timestamp,
    \data_reg_axi_DelayCycles_1_1_reg[9] ,
    rd_active,
    data_reg_axi_enable_1_1_i_2,
    data_reg_axi_enable_1_1_i_2_0,
    \fifo_back_indx_reg[3] ,
    top_rd_enb,
    \cache_data_reg[31] ,
    \cache_data_reg[31]_0 ,
    cache_valid,
    \Out_tmp_reg[31] ,
    AXI4_ACLK,
    \data_int_reg[29]_0 ,
    \data_int_reg[29]_1 );
  output axi4_rd_active_reg;
  output axi4_rd_active_reg_0;
  output \axi4_raddr_reg[8] ;
  output \waddr_reg[15] ;
  output \waddr_reg[11] ;
  output [0:0]E;
  output [31:0]D;
  output [31:0]data_int;
  output [31:0]w_d1_reg;
  input [9:0]\data_int_reg[1]_0 ;
  input [13:0]Q;
  input read_reg_axi_fb_enable;
  input read_reg_axi_fb_InverseBotSwitch;
  input [0:0]read_reg_ip_timestamp;
  input [5:0]\data_reg_axi_DelayCycles_1_1_reg[9] ;
  input rd_active;
  input data_reg_axi_enable_1_1_i_2;
  input data_reg_axi_enable_1_1_i_2_0;
  input [4:0]\fifo_back_indx_reg[3] ;
  input top_rd_enb;
  input \cache_data_reg[31] ;
  input [31:0]\cache_data_reg[31]_0 ;
  input cache_valid;
  input [31:0]\Out_tmp_reg[31] ;
  input AXI4_ACLK;
  input [3:0]\data_int_reg[29]_0 ;
  input [3:0]\data_int_reg[29]_1 ;

  wire AXI4_ACLK;
  wire [31:0]D;
  wire [0:0]E;
  wire [31:0]\Out_tmp_reg[31] ;
  wire [13:0]Q;
  wire \axi4_raddr_reg[8] ;
  wire axi4_rd_active_reg;
  wire axi4_rd_active_reg_0;
  wire \cache_data_reg[31] ;
  wire [31:0]\cache_data_reg[31]_0 ;
  wire cache_valid;
  wire [31:0]data_int;
  wire [9:0]\data_int_reg[1]_0 ;
  wire [3:0]\data_int_reg[29]_0 ;
  wire [3:0]\data_int_reg[29]_1 ;
  wire [5:0]\data_reg_axi_DelayCycles_1_1_reg[9] ;
  wire data_reg_axi_enable_1_1_i_2;
  wire data_reg_axi_enable_1_1_i_2_0;
  wire [4:0]\fifo_back_indx_reg[3] ;
  wire [31:0]p_1_out;
  wire ram_reg_0_15_0_13_i_13_n_0;
  wire ram_reg_0_15_0_13_i_14_n_0;
  wire ram_reg_0_15_0_13_i_15_n_0;
  wire ram_reg_0_15_0_13_i_16_n_0;
  wire ram_reg_0_15_0_13_i_18_n_0;
  wire ram_reg_0_15_0_13_i_20_n_0;
  wire rd_active;
  wire read_reg_axi_fb_InverseBotSwitch;
  wire read_reg_axi_fb_enable;
  wire [0:0]read_reg_ip_timestamp;
  wire top_rd_enb;
  wire [31:0]w_d1_reg;
  wire \waddr_reg[11] ;
  wire \waddr_reg[15] ;
  wire [29:0]wr_din;
  wire [1:0]NLW_ram_reg_0_15_0_13_DOH_UNCONNECTED;
  wire [1:0]NLW_ram_reg_0_15_14_27_DOH_UNCONNECTED;
  wire [1:0]NLW_ram_reg_0_15_28_31_DOC_UNCONNECTED;
  wire [1:0]NLW_ram_reg_0_15_28_31_DOD_UNCONNECTED;
  wire [1:0]NLW_ram_reg_0_15_28_31_DOE_UNCONNECTED;
  wire [1:0]NLW_ram_reg_0_15_28_31_DOF_UNCONNECTED;
  wire [1:0]NLW_ram_reg_0_15_28_31_DOG_UNCONNECTED;
  wire [1:0]NLW_ram_reg_0_15_28_31_DOH_UNCONNECTED;

  (* SOFT_HLUTNM = "soft_lutpair7" *) 
  LUT5 #(
    .INIT(32'hFFE400E4)) 
    \Out_tmp[0]_i_1 
       (.I0(\cache_data_reg[31] ),
        .I1(\cache_data_reg[31]_0 [0]),
        .I2(data_int[0]),
        .I3(cache_valid),
        .I4(\Out_tmp_reg[31] [0]),
        .O(w_d1_reg[0]));
  (* SOFT_HLUTNM = "soft_lutpair17" *) 
  LUT5 #(
    .INIT(32'hFFE400E4)) 
    \Out_tmp[10]_i_1 
       (.I0(\cache_data_reg[31] ),
        .I1(\cache_data_reg[31]_0 [10]),
        .I2(data_int[10]),
        .I3(cache_valid),
        .I4(\Out_tmp_reg[31] [10]),
        .O(w_d1_reg[10]));
  (* SOFT_HLUTNM = "soft_lutpair18" *) 
  LUT5 #(
    .INIT(32'hFFE400E4)) 
    \Out_tmp[11]_i_1__0 
       (.I0(\cache_data_reg[31] ),
        .I1(\cache_data_reg[31]_0 [11]),
        .I2(data_int[11]),
        .I3(cache_valid),
        .I4(\Out_tmp_reg[31] [11]),
        .O(w_d1_reg[11]));
  (* SOFT_HLUTNM = "soft_lutpair19" *) 
  LUT5 #(
    .INIT(32'hFFE400E4)) 
    \Out_tmp[12]_i_1 
       (.I0(\cache_data_reg[31] ),
        .I1(\cache_data_reg[31]_0 [12]),
        .I2(data_int[12]),
        .I3(cache_valid),
        .I4(\Out_tmp_reg[31] [12]),
        .O(w_d1_reg[12]));
  (* SOFT_HLUTNM = "soft_lutpair20" *) 
  LUT5 #(
    .INIT(32'hFFE400E4)) 
    \Out_tmp[13]_i_1 
       (.I0(\cache_data_reg[31] ),
        .I1(\cache_data_reg[31]_0 [13]),
        .I2(data_int[13]),
        .I3(cache_valid),
        .I4(\Out_tmp_reg[31] [13]),
        .O(w_d1_reg[13]));
  (* SOFT_HLUTNM = "soft_lutpair21" *) 
  LUT5 #(
    .INIT(32'hFFE400E4)) 
    \Out_tmp[14]_i_1 
       (.I0(\cache_data_reg[31] ),
        .I1(\cache_data_reg[31]_0 [14]),
        .I2(data_int[14]),
        .I3(cache_valid),
        .I4(\Out_tmp_reg[31] [14]),
        .O(w_d1_reg[14]));
  (* SOFT_HLUTNM = "soft_lutpair22" *) 
  LUT5 #(
    .INIT(32'hFFE400E4)) 
    \Out_tmp[15]_i_1 
       (.I0(\cache_data_reg[31] ),
        .I1(\cache_data_reg[31]_0 [15]),
        .I2(data_int[15]),
        .I3(cache_valid),
        .I4(\Out_tmp_reg[31] [15]),
        .O(w_d1_reg[15]));
  (* SOFT_HLUTNM = "soft_lutpair23" *) 
  LUT5 #(
    .INIT(32'hFFE400E4)) 
    \Out_tmp[16]_i_1 
       (.I0(\cache_data_reg[31] ),
        .I1(\cache_data_reg[31]_0 [16]),
        .I2(data_int[16]),
        .I3(cache_valid),
        .I4(\Out_tmp_reg[31] [16]),
        .O(w_d1_reg[16]));
  (* SOFT_HLUTNM = "soft_lutpair24" *) 
  LUT5 #(
    .INIT(32'hFFE400E4)) 
    \Out_tmp[17]_i_1 
       (.I0(\cache_data_reg[31] ),
        .I1(\cache_data_reg[31]_0 [17]),
        .I2(data_int[17]),
        .I3(cache_valid),
        .I4(\Out_tmp_reg[31] [17]),
        .O(w_d1_reg[17]));
  (* SOFT_HLUTNM = "soft_lutpair25" *) 
  LUT5 #(
    .INIT(32'hFFE400E4)) 
    \Out_tmp[18]_i_1 
       (.I0(\cache_data_reg[31] ),
        .I1(\cache_data_reg[31]_0 [18]),
        .I2(data_int[18]),
        .I3(cache_valid),
        .I4(\Out_tmp_reg[31] [18]),
        .O(w_d1_reg[18]));
  (* SOFT_HLUTNM = "soft_lutpair26" *) 
  LUT5 #(
    .INIT(32'hFFE400E4)) 
    \Out_tmp[19]_i_1 
       (.I0(\cache_data_reg[31] ),
        .I1(\cache_data_reg[31]_0 [19]),
        .I2(data_int[19]),
        .I3(cache_valid),
        .I4(\Out_tmp_reg[31] [19]),
        .O(w_d1_reg[19]));
  (* SOFT_HLUTNM = "soft_lutpair8" *) 
  LUT5 #(
    .INIT(32'hFFE400E4)) 
    \Out_tmp[1]_i_1 
       (.I0(\cache_data_reg[31] ),
        .I1(\cache_data_reg[31]_0 [1]),
        .I2(data_int[1]),
        .I3(cache_valid),
        .I4(\Out_tmp_reg[31] [1]),
        .O(w_d1_reg[1]));
  (* SOFT_HLUTNM = "soft_lutpair27" *) 
  LUT5 #(
    .INIT(32'hFFE400E4)) 
    \Out_tmp[20]_i_1 
       (.I0(\cache_data_reg[31] ),
        .I1(\cache_data_reg[31]_0 [20]),
        .I2(data_int[20]),
        .I3(cache_valid),
        .I4(\Out_tmp_reg[31] [20]),
        .O(w_d1_reg[20]));
  (* SOFT_HLUTNM = "soft_lutpair28" *) 
  LUT5 #(
    .INIT(32'hFFE400E4)) 
    \Out_tmp[21]_i_1 
       (.I0(\cache_data_reg[31] ),
        .I1(\cache_data_reg[31]_0 [21]),
        .I2(data_int[21]),
        .I3(cache_valid),
        .I4(\Out_tmp_reg[31] [21]),
        .O(w_d1_reg[21]));
  (* SOFT_HLUTNM = "soft_lutpair29" *) 
  LUT5 #(
    .INIT(32'hFFE400E4)) 
    \Out_tmp[22]_i_1 
       (.I0(\cache_data_reg[31] ),
        .I1(\cache_data_reg[31]_0 [22]),
        .I2(data_int[22]),
        .I3(cache_valid),
        .I4(\Out_tmp_reg[31] [22]),
        .O(w_d1_reg[22]));
  (* SOFT_HLUTNM = "soft_lutpair30" *) 
  LUT5 #(
    .INIT(32'hFFE400E4)) 
    \Out_tmp[23]_i_1 
       (.I0(\cache_data_reg[31] ),
        .I1(\cache_data_reg[31]_0 [23]),
        .I2(data_int[23]),
        .I3(cache_valid),
        .I4(\Out_tmp_reg[31] [23]),
        .O(w_d1_reg[23]));
  (* SOFT_HLUTNM = "soft_lutpair31" *) 
  LUT5 #(
    .INIT(32'hFFE400E4)) 
    \Out_tmp[24]_i_1 
       (.I0(\cache_data_reg[31] ),
        .I1(\cache_data_reg[31]_0 [24]),
        .I2(data_int[24]),
        .I3(cache_valid),
        .I4(\Out_tmp_reg[31] [24]),
        .O(w_d1_reg[24]));
  (* SOFT_HLUTNM = "soft_lutpair32" *) 
  LUT5 #(
    .INIT(32'hFFE400E4)) 
    \Out_tmp[25]_i_1 
       (.I0(\cache_data_reg[31] ),
        .I1(\cache_data_reg[31]_0 [25]),
        .I2(data_int[25]),
        .I3(cache_valid),
        .I4(\Out_tmp_reg[31] [25]),
        .O(w_d1_reg[25]));
  (* SOFT_HLUTNM = "soft_lutpair33" *) 
  LUT5 #(
    .INIT(32'hFFE400E4)) 
    \Out_tmp[26]_i_1 
       (.I0(\cache_data_reg[31] ),
        .I1(\cache_data_reg[31]_0 [26]),
        .I2(data_int[26]),
        .I3(cache_valid),
        .I4(\Out_tmp_reg[31] [26]),
        .O(w_d1_reg[26]));
  (* SOFT_HLUTNM = "soft_lutpair34" *) 
  LUT5 #(
    .INIT(32'hFFE400E4)) 
    \Out_tmp[27]_i_1 
       (.I0(\cache_data_reg[31] ),
        .I1(\cache_data_reg[31]_0 [27]),
        .I2(data_int[27]),
        .I3(cache_valid),
        .I4(\Out_tmp_reg[31] [27]),
        .O(w_d1_reg[27]));
  (* SOFT_HLUTNM = "soft_lutpair35" *) 
  LUT5 #(
    .INIT(32'hFFE400E4)) 
    \Out_tmp[28]_i_1 
       (.I0(\cache_data_reg[31] ),
        .I1(\cache_data_reg[31]_0 [28]),
        .I2(data_int[28]),
        .I3(cache_valid),
        .I4(\Out_tmp_reg[31] [28]),
        .O(w_d1_reg[28]));
  (* SOFT_HLUTNM = "soft_lutpair36" *) 
  LUT5 #(
    .INIT(32'hFFE400E4)) 
    \Out_tmp[29]_i_1 
       (.I0(\cache_data_reg[31] ),
        .I1(\cache_data_reg[31]_0 [29]),
        .I2(data_int[29]),
        .I3(cache_valid),
        .I4(\Out_tmp_reg[31] [29]),
        .O(w_d1_reg[29]));
  (* SOFT_HLUTNM = "soft_lutpair9" *) 
  LUT5 #(
    .INIT(32'hFFE400E4)) 
    \Out_tmp[2]_i_1 
       (.I0(\cache_data_reg[31] ),
        .I1(\cache_data_reg[31]_0 [2]),
        .I2(data_int[2]),
        .I3(cache_valid),
        .I4(\Out_tmp_reg[31] [2]),
        .O(w_d1_reg[2]));
  (* SOFT_HLUTNM = "soft_lutpair37" *) 
  LUT5 #(
    .INIT(32'hFFE400E4)) 
    \Out_tmp[30]_i_1 
       (.I0(\cache_data_reg[31] ),
        .I1(\cache_data_reg[31]_0 [30]),
        .I2(data_int[30]),
        .I3(cache_valid),
        .I4(\Out_tmp_reg[31] [30]),
        .O(w_d1_reg[30]));
  (* SOFT_HLUTNM = "soft_lutpair6" *) 
  LUT5 #(
    .INIT(32'hFFE400E4)) 
    \Out_tmp[31]_i_2 
       (.I0(\cache_data_reg[31] ),
        .I1(\cache_data_reg[31]_0 [31]),
        .I2(data_int[31]),
        .I3(cache_valid),
        .I4(\Out_tmp_reg[31] [31]),
        .O(w_d1_reg[31]));
  (* SOFT_HLUTNM = "soft_lutpair10" *) 
  LUT5 #(
    .INIT(32'hFFE400E4)) 
    \Out_tmp[3]_i_1 
       (.I0(\cache_data_reg[31] ),
        .I1(\cache_data_reg[31]_0 [3]),
        .I2(data_int[3]),
        .I3(cache_valid),
        .I4(\Out_tmp_reg[31] [3]),
        .O(w_d1_reg[3]));
  (* SOFT_HLUTNM = "soft_lutpair11" *) 
  LUT5 #(
    .INIT(32'hFFE400E4)) 
    \Out_tmp[4]_i_1 
       (.I0(\cache_data_reg[31] ),
        .I1(\cache_data_reg[31]_0 [4]),
        .I2(data_int[4]),
        .I3(cache_valid),
        .I4(\Out_tmp_reg[31] [4]),
        .O(w_d1_reg[4]));
  (* SOFT_HLUTNM = "soft_lutpair12" *) 
  LUT5 #(
    .INIT(32'hFFE400E4)) 
    \Out_tmp[5]_i_1 
       (.I0(\cache_data_reg[31] ),
        .I1(\cache_data_reg[31]_0 [5]),
        .I2(data_int[5]),
        .I3(cache_valid),
        .I4(\Out_tmp_reg[31] [5]),
        .O(w_d1_reg[5]));
  (* SOFT_HLUTNM = "soft_lutpair13" *) 
  LUT5 #(
    .INIT(32'hFFE400E4)) 
    \Out_tmp[6]_i_1 
       (.I0(\cache_data_reg[31] ),
        .I1(\cache_data_reg[31]_0 [6]),
        .I2(data_int[6]),
        .I3(cache_valid),
        .I4(\Out_tmp_reg[31] [6]),
        .O(w_d1_reg[6]));
  (* SOFT_HLUTNM = "soft_lutpair14" *) 
  LUT5 #(
    .INIT(32'hFFE400E4)) 
    \Out_tmp[7]_i_1 
       (.I0(\cache_data_reg[31] ),
        .I1(\cache_data_reg[31]_0 [7]),
        .I2(data_int[7]),
        .I3(cache_valid),
        .I4(\Out_tmp_reg[31] [7]),
        .O(w_d1_reg[7]));
  (* SOFT_HLUTNM = "soft_lutpair15" *) 
  LUT5 #(
    .INIT(32'hFFE400E4)) 
    \Out_tmp[8]_i_1 
       (.I0(\cache_data_reg[31] ),
        .I1(\cache_data_reg[31]_0 [8]),
        .I2(data_int[8]),
        .I3(cache_valid),
        .I4(\Out_tmp_reg[31] [8]),
        .O(w_d1_reg[8]));
  (* SOFT_HLUTNM = "soft_lutpair16" *) 
  LUT5 #(
    .INIT(32'hFFE400E4)) 
    \Out_tmp[9]_i_1 
       (.I0(\cache_data_reg[31] ),
        .I1(\cache_data_reg[31]_0 [9]),
        .I2(data_int[9]),
        .I3(cache_valid),
        .I4(\Out_tmp_reg[31] [9]),
        .O(w_d1_reg[9]));
  (* SOFT_HLUTNM = "soft_lutpair7" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \cache_data[0]_i_1 
       (.I0(data_int[0]),
        .I1(\cache_data_reg[31] ),
        .I2(\cache_data_reg[31]_0 [0]),
        .O(D[0]));
  (* SOFT_HLUTNM = "soft_lutpair17" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \cache_data[10]_i_1 
       (.I0(data_int[10]),
        .I1(\cache_data_reg[31] ),
        .I2(\cache_data_reg[31]_0 [10]),
        .O(D[10]));
  (* SOFT_HLUTNM = "soft_lutpair18" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \cache_data[11]_i_1__0 
       (.I0(data_int[11]),
        .I1(\cache_data_reg[31] ),
        .I2(\cache_data_reg[31]_0 [11]),
        .O(D[11]));
  (* SOFT_HLUTNM = "soft_lutpair19" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \cache_data[12]_i_1 
       (.I0(data_int[12]),
        .I1(\cache_data_reg[31] ),
        .I2(\cache_data_reg[31]_0 [12]),
        .O(D[12]));
  (* SOFT_HLUTNM = "soft_lutpair20" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \cache_data[13]_i_1 
       (.I0(data_int[13]),
        .I1(\cache_data_reg[31] ),
        .I2(\cache_data_reg[31]_0 [13]),
        .O(D[13]));
  (* SOFT_HLUTNM = "soft_lutpair21" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \cache_data[14]_i_1 
       (.I0(data_int[14]),
        .I1(\cache_data_reg[31] ),
        .I2(\cache_data_reg[31]_0 [14]),
        .O(D[14]));
  (* SOFT_HLUTNM = "soft_lutpair22" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \cache_data[15]_i_1 
       (.I0(data_int[15]),
        .I1(\cache_data_reg[31] ),
        .I2(\cache_data_reg[31]_0 [15]),
        .O(D[15]));
  (* SOFT_HLUTNM = "soft_lutpair23" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \cache_data[16]_i_1 
       (.I0(data_int[16]),
        .I1(\cache_data_reg[31] ),
        .I2(\cache_data_reg[31]_0 [16]),
        .O(D[16]));
  (* SOFT_HLUTNM = "soft_lutpair24" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \cache_data[17]_i_1 
       (.I0(data_int[17]),
        .I1(\cache_data_reg[31] ),
        .I2(\cache_data_reg[31]_0 [17]),
        .O(D[17]));
  (* SOFT_HLUTNM = "soft_lutpair25" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \cache_data[18]_i_1 
       (.I0(data_int[18]),
        .I1(\cache_data_reg[31] ),
        .I2(\cache_data_reg[31]_0 [18]),
        .O(D[18]));
  (* SOFT_HLUTNM = "soft_lutpair26" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \cache_data[19]_i_1 
       (.I0(data_int[19]),
        .I1(\cache_data_reg[31] ),
        .I2(\cache_data_reg[31]_0 [19]),
        .O(D[19]));
  (* SOFT_HLUTNM = "soft_lutpair8" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \cache_data[1]_i_1 
       (.I0(data_int[1]),
        .I1(\cache_data_reg[31] ),
        .I2(\cache_data_reg[31]_0 [1]),
        .O(D[1]));
  (* SOFT_HLUTNM = "soft_lutpair27" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \cache_data[20]_i_1 
       (.I0(data_int[20]),
        .I1(\cache_data_reg[31] ),
        .I2(\cache_data_reg[31]_0 [20]),
        .O(D[20]));
  (* SOFT_HLUTNM = "soft_lutpair28" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \cache_data[21]_i_1 
       (.I0(data_int[21]),
        .I1(\cache_data_reg[31] ),
        .I2(\cache_data_reg[31]_0 [21]),
        .O(D[21]));
  (* SOFT_HLUTNM = "soft_lutpair29" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \cache_data[22]_i_1 
       (.I0(data_int[22]),
        .I1(\cache_data_reg[31] ),
        .I2(\cache_data_reg[31]_0 [22]),
        .O(D[22]));
  (* SOFT_HLUTNM = "soft_lutpair30" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \cache_data[23]_i_1 
       (.I0(data_int[23]),
        .I1(\cache_data_reg[31] ),
        .I2(\cache_data_reg[31]_0 [23]),
        .O(D[23]));
  (* SOFT_HLUTNM = "soft_lutpair31" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \cache_data[24]_i_1 
       (.I0(data_int[24]),
        .I1(\cache_data_reg[31] ),
        .I2(\cache_data_reg[31]_0 [24]),
        .O(D[24]));
  (* SOFT_HLUTNM = "soft_lutpair32" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \cache_data[25]_i_1 
       (.I0(data_int[25]),
        .I1(\cache_data_reg[31] ),
        .I2(\cache_data_reg[31]_0 [25]),
        .O(D[25]));
  (* SOFT_HLUTNM = "soft_lutpair33" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \cache_data[26]_i_1 
       (.I0(data_int[26]),
        .I1(\cache_data_reg[31] ),
        .I2(\cache_data_reg[31]_0 [26]),
        .O(D[26]));
  (* SOFT_HLUTNM = "soft_lutpair34" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \cache_data[27]_i_1 
       (.I0(data_int[27]),
        .I1(\cache_data_reg[31] ),
        .I2(\cache_data_reg[31]_0 [27]),
        .O(D[27]));
  (* SOFT_HLUTNM = "soft_lutpair35" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \cache_data[28]_i_1 
       (.I0(data_int[28]),
        .I1(\cache_data_reg[31] ),
        .I2(\cache_data_reg[31]_0 [28]),
        .O(D[28]));
  (* SOFT_HLUTNM = "soft_lutpair36" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \cache_data[29]_i_1 
       (.I0(data_int[29]),
        .I1(\cache_data_reg[31] ),
        .I2(\cache_data_reg[31]_0 [29]),
        .O(D[29]));
  (* SOFT_HLUTNM = "soft_lutpair9" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \cache_data[2]_i_1 
       (.I0(data_int[2]),
        .I1(\cache_data_reg[31] ),
        .I2(\cache_data_reg[31]_0 [2]),
        .O(D[2]));
  (* SOFT_HLUTNM = "soft_lutpair37" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \cache_data[30]_i_1 
       (.I0(data_int[30]),
        .I1(\cache_data_reg[31] ),
        .I2(\cache_data_reg[31]_0 [30]),
        .O(D[30]));
  (* SOFT_HLUTNM = "soft_lutpair6" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \cache_data[31]_i_2 
       (.I0(data_int[31]),
        .I1(\cache_data_reg[31] ),
        .I2(\cache_data_reg[31]_0 [31]),
        .O(D[31]));
  (* SOFT_HLUTNM = "soft_lutpair10" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \cache_data[3]_i_1 
       (.I0(data_int[3]),
        .I1(\cache_data_reg[31] ),
        .I2(\cache_data_reg[31]_0 [3]),
        .O(D[3]));
  (* SOFT_HLUTNM = "soft_lutpair11" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \cache_data[4]_i_1 
       (.I0(data_int[4]),
        .I1(\cache_data_reg[31] ),
        .I2(\cache_data_reg[31]_0 [4]),
        .O(D[4]));
  (* SOFT_HLUTNM = "soft_lutpair12" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \cache_data[5]_i_1 
       (.I0(data_int[5]),
        .I1(\cache_data_reg[31] ),
        .I2(\cache_data_reg[31]_0 [5]),
        .O(D[5]));
  (* SOFT_HLUTNM = "soft_lutpair13" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \cache_data[6]_i_1 
       (.I0(data_int[6]),
        .I1(\cache_data_reg[31] ),
        .I2(\cache_data_reg[31]_0 [6]),
        .O(D[6]));
  (* SOFT_HLUTNM = "soft_lutpair14" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \cache_data[7]_i_1 
       (.I0(data_int[7]),
        .I1(\cache_data_reg[31] ),
        .I2(\cache_data_reg[31]_0 [7]),
        .O(D[7]));
  (* SOFT_HLUTNM = "soft_lutpair15" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \cache_data[8]_i_1 
       (.I0(data_int[8]),
        .I1(\cache_data_reg[31] ),
        .I2(\cache_data_reg[31]_0 [8]),
        .O(D[8]));
  (* SOFT_HLUTNM = "soft_lutpair16" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \cache_data[9]_i_1 
       (.I0(data_int[9]),
        .I1(\cache_data_reg[31] ),
        .I2(\cache_data_reg[31]_0 [9]),
        .O(D[9]));
  FDRE #(
    .INIT(1'b0)) 
    \data_int_reg[0] 
       (.C(AXI4_ACLK),
        .CE(1'b1),
        .D(p_1_out[0]),
        .Q(data_int[0]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \data_int_reg[10] 
       (.C(AXI4_ACLK),
        .CE(1'b1),
        .D(p_1_out[10]),
        .Q(data_int[10]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \data_int_reg[11] 
       (.C(AXI4_ACLK),
        .CE(1'b1),
        .D(p_1_out[11]),
        .Q(data_int[11]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \data_int_reg[12] 
       (.C(AXI4_ACLK),
        .CE(1'b1),
        .D(p_1_out[12]),
        .Q(data_int[12]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \data_int_reg[13] 
       (.C(AXI4_ACLK),
        .CE(1'b1),
        .D(p_1_out[13]),
        .Q(data_int[13]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \data_int_reg[14] 
       (.C(AXI4_ACLK),
        .CE(1'b1),
        .D(p_1_out[14]),
        .Q(data_int[14]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \data_int_reg[15] 
       (.C(AXI4_ACLK),
        .CE(1'b1),
        .D(p_1_out[15]),
        .Q(data_int[15]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \data_int_reg[16] 
       (.C(AXI4_ACLK),
        .CE(1'b1),
        .D(p_1_out[16]),
        .Q(data_int[16]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \data_int_reg[17] 
       (.C(AXI4_ACLK),
        .CE(1'b1),
        .D(p_1_out[17]),
        .Q(data_int[17]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \data_int_reg[18] 
       (.C(AXI4_ACLK),
        .CE(1'b1),
        .D(p_1_out[18]),
        .Q(data_int[18]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \data_int_reg[19] 
       (.C(AXI4_ACLK),
        .CE(1'b1),
        .D(p_1_out[19]),
        .Q(data_int[19]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \data_int_reg[1] 
       (.C(AXI4_ACLK),
        .CE(1'b1),
        .D(p_1_out[1]),
        .Q(data_int[1]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \data_int_reg[20] 
       (.C(AXI4_ACLK),
        .CE(1'b1),
        .D(p_1_out[20]),
        .Q(data_int[20]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \data_int_reg[21] 
       (.C(AXI4_ACLK),
        .CE(1'b1),
        .D(p_1_out[21]),
        .Q(data_int[21]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \data_int_reg[22] 
       (.C(AXI4_ACLK),
        .CE(1'b1),
        .D(p_1_out[22]),
        .Q(data_int[22]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \data_int_reg[23] 
       (.C(AXI4_ACLK),
        .CE(1'b1),
        .D(p_1_out[23]),
        .Q(data_int[23]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \data_int_reg[24] 
       (.C(AXI4_ACLK),
        .CE(1'b1),
        .D(p_1_out[24]),
        .Q(data_int[24]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \data_int_reg[25] 
       (.C(AXI4_ACLK),
        .CE(1'b1),
        .D(p_1_out[25]),
        .Q(data_int[25]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \data_int_reg[26] 
       (.C(AXI4_ACLK),
        .CE(1'b1),
        .D(p_1_out[26]),
        .Q(data_int[26]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \data_int_reg[27] 
       (.C(AXI4_ACLK),
        .CE(1'b1),
        .D(p_1_out[27]),
        .Q(data_int[27]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \data_int_reg[28] 
       (.C(AXI4_ACLK),
        .CE(1'b1),
        .D(p_1_out[28]),
        .Q(data_int[28]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \data_int_reg[29] 
       (.C(AXI4_ACLK),
        .CE(1'b1),
        .D(p_1_out[29]),
        .Q(data_int[29]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \data_int_reg[2] 
       (.C(AXI4_ACLK),
        .CE(1'b1),
        .D(p_1_out[2]),
        .Q(data_int[2]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \data_int_reg[30] 
       (.C(AXI4_ACLK),
        .CE(1'b1),
        .D(p_1_out[30]),
        .Q(data_int[30]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \data_int_reg[31] 
       (.C(AXI4_ACLK),
        .CE(1'b1),
        .D(p_1_out[31]),
        .Q(data_int[31]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \data_int_reg[3] 
       (.C(AXI4_ACLK),
        .CE(1'b1),
        .D(p_1_out[3]),
        .Q(data_int[3]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \data_int_reg[4] 
       (.C(AXI4_ACLK),
        .CE(1'b1),
        .D(p_1_out[4]),
        .Q(data_int[4]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \data_int_reg[5] 
       (.C(AXI4_ACLK),
        .CE(1'b1),
        .D(p_1_out[5]),
        .Q(data_int[5]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \data_int_reg[6] 
       (.C(AXI4_ACLK),
        .CE(1'b1),
        .D(p_1_out[6]),
        .Q(data_int[6]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \data_int_reg[7] 
       (.C(AXI4_ACLK),
        .CE(1'b1),
        .D(p_1_out[7]),
        .Q(data_int[7]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \data_int_reg[8] 
       (.C(AXI4_ACLK),
        .CE(1'b1),
        .D(p_1_out[8]),
        .Q(data_int[8]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \data_int_reg[9] 
       (.C(AXI4_ACLK),
        .CE(1'b1),
        .D(p_1_out[9]),
        .Q(data_int[9]),
        .R(1'b0));
  (* SOFT_HLUTNM = "soft_lutpair43" *) 
  LUT2 #(
    .INIT(4'h2)) 
    \data_reg_axi_DelayCycles_1_1[9]_i_3 
       (.I0(\data_reg_axi_DelayCycles_1_1_reg[9] [5]),
        .I1(\data_reg_axi_DelayCycles_1_1_reg[9] [1]),
        .O(\axi4_raddr_reg[8] ));
  (* METHODOLOGY_DRC_VIOS = "" *) 
  (* RTL_RAM_BITS = "512" *) 
  (* RTL_RAM_NAME = "U0/u_uz_interlockDeadtime2L_axi4_inst/u_uz_interlockDeadtime2L_axi4_module_inst/u_uz_interlockDeadtime2L_rdfifo_data_inst/u_uz_interlockDeadtime2L_rdfifo_data_classic_ram_generic/ram" *) 
  (* RTL_RAM_TYPE = "RAM_SDP" *) 
  (* ram_addr_begin = "0" *) 
  (* ram_addr_end = "15" *) 
  (* ram_offset = "0" *) 
  (* ram_slice_begin = "0" *) 
  (* ram_slice_end = "13" *) 
  RAM32M16 #(
    .INIT_A(64'h0000000000000000),
    .INIT_B(64'h0000000000000000),
    .INIT_C(64'h0000000000000000),
    .INIT_D(64'h0000000000000000),
    .INIT_E(64'h0000000000000000),
    .INIT_F(64'h0000000000000000),
    .INIT_G(64'h0000000000000000),
    .INIT_H(64'h0000000000000000)) 
    ram_reg_0_15_0_13
       (.ADDRA({1'b0,\data_int_reg[29]_0 }),
        .ADDRB({1'b0,\data_int_reg[29]_0 }),
        .ADDRC({1'b0,\data_int_reg[29]_0 }),
        .ADDRD({1'b0,\data_int_reg[29]_0 }),
        .ADDRE({1'b0,\data_int_reg[29]_0 }),
        .ADDRF({1'b0,\data_int_reg[29]_0 }),
        .ADDRG({1'b0,\data_int_reg[29]_0 }),
        .ADDRH({1'b0,\data_int_reg[29]_1 }),
        .DIA(wr_din[1:0]),
        .DIB(wr_din[3:2]),
        .DIC(wr_din[5:4]),
        .DID(wr_din[7:6]),
        .DIE(wr_din[9:8]),
        .DIF({wr_din[29],wr_din[29]}),
        .DIG({1'b0,wr_din[29]}),
        .DIH({1'b0,1'b0}),
        .DOA(p_1_out[1:0]),
        .DOB(p_1_out[3:2]),
        .DOC(p_1_out[5:4]),
        .DOD(p_1_out[7:6]),
        .DOE(p_1_out[9:8]),
        .DOF(p_1_out[11:10]),
        .DOG(p_1_out[13:12]),
        .DOH(NLW_ram_reg_0_15_0_13_DOH_UNCONNECTED[1:0]),
        .WCLK(AXI4_ACLK),
        .WE(E));
  LUT6 #(
    .INIT(64'hFFFFFFFD00000000)) 
    ram_reg_0_15_0_13_i_1
       (.I0(\fifo_back_indx_reg[3] [4]),
        .I1(\fifo_back_indx_reg[3] [2]),
        .I2(\fifo_back_indx_reg[3] [0]),
        .I3(\fifo_back_indx_reg[3] [1]),
        .I4(\fifo_back_indx_reg[3] [3]),
        .I5(top_rd_enb),
        .O(E));
  (* SOFT_HLUTNM = "soft_lutpair38" *) 
  LUT3 #(
    .INIT(8'hF8)) 
    ram_reg_0_15_0_13_i_10
       (.I0(\data_int_reg[1]_0 [9]),
        .I1(ram_reg_0_15_0_13_i_13_n_0),
        .I2(wr_din[29]),
        .O(wr_din[9]));
  LUT2 #(
    .INIT(4'h8)) 
    ram_reg_0_15_0_13_i_11
       (.I0(ram_reg_0_15_0_13_i_13_n_0),
        .I1(\data_int_reg[1]_0 [8]),
        .O(wr_din[8]));
  LUT5 #(
    .INIT(32'hF8880000)) 
    ram_reg_0_15_0_13_i_12
       (.I0(ram_reg_0_15_0_13_i_16_n_0),
        .I1(axi4_rd_active_reg),
        .I2(ram_reg_0_15_0_13_i_18_n_0),
        .I3(axi4_rd_active_reg_0),
        .I4(read_reg_ip_timestamp),
        .O(wr_din[29]));
  LUT6 #(
    .INIT(64'hFF80808080808080)) 
    ram_reg_0_15_0_13_i_13
       (.I0(ram_reg_0_15_0_13_i_20_n_0),
        .I1(axi4_rd_active_reg),
        .I2(Q[0]),
        .I3(\axi4_raddr_reg[8] ),
        .I4(axi4_rd_active_reg_0),
        .I5(\data_reg_axi_DelayCycles_1_1_reg[9] [0]),
        .O(ram_reg_0_15_0_13_i_13_n_0));
  LUT6 #(
    .INIT(64'h4400500000000000)) 
    ram_reg_0_15_0_13_i_14
       (.I0(\data_reg_axi_DelayCycles_1_1_reg[9] [0]),
        .I1(read_reg_axi_fb_enable),
        .I2(read_reg_axi_fb_InverseBotSwitch),
        .I3(\data_reg_axi_DelayCycles_1_1_reg[9] [5]),
        .I4(\data_reg_axi_DelayCycles_1_1_reg[9] [1]),
        .I5(axi4_rd_active_reg_0),
        .O(ram_reg_0_15_0_13_i_14_n_0));
  LUT6 #(
    .INIT(64'h4400500000000000)) 
    ram_reg_0_15_0_13_i_15
       (.I0(Q[0]),
        .I1(read_reg_axi_fb_enable),
        .I2(read_reg_axi_fb_InverseBotSwitch),
        .I3(Q[6]),
        .I4(Q[1]),
        .I5(axi4_rd_active_reg),
        .O(ram_reg_0_15_0_13_i_15_n_0));
  (* SOFT_HLUTNM = "soft_lutpair42" *) 
  LUT3 #(
    .INIT(8'h04)) 
    ram_reg_0_15_0_13_i_16
       (.I0(Q[6]),
        .I1(Q[1]),
        .I2(Q[0]),
        .O(ram_reg_0_15_0_13_i_16_n_0));
  LUT6 #(
    .INIT(64'h0000000000000040)) 
    ram_reg_0_15_0_13_i_17
       (.I0(rd_active),
        .I1(\waddr_reg[15] ),
        .I2(\waddr_reg[11] ),
        .I3(Q[4]),
        .I4(Q[3]),
        .I5(Q[2]),
        .O(axi4_rd_active_reg));
  (* SOFT_HLUTNM = "soft_lutpair43" *) 
  LUT3 #(
    .INIT(8'h04)) 
    ram_reg_0_15_0_13_i_18
       (.I0(\data_reg_axi_DelayCycles_1_1_reg[9] [5]),
        .I1(\data_reg_axi_DelayCycles_1_1_reg[9] [1]),
        .I2(\data_reg_axi_DelayCycles_1_1_reg[9] [0]),
        .O(ram_reg_0_15_0_13_i_18_n_0));
  LUT6 #(
    .INIT(64'h0000000000080000)) 
    ram_reg_0_15_0_13_i_19
       (.I0(data_reg_axi_enable_1_1_i_2),
        .I1(rd_active),
        .I2(\data_reg_axi_DelayCycles_1_1_reg[9] [3]),
        .I3(\data_reg_axi_DelayCycles_1_1_reg[9] [4]),
        .I4(data_reg_axi_enable_1_1_i_2_0),
        .I5(\data_reg_axi_DelayCycles_1_1_reg[9] [2]),
        .O(axi4_rd_active_reg_0));
  (* SOFT_HLUTNM = "soft_lutpair41" *) 
  LUT3 #(
    .INIT(8'hF8)) 
    ram_reg_0_15_0_13_i_2
       (.I0(\data_int_reg[1]_0 [1]),
        .I1(ram_reg_0_15_0_13_i_13_n_0),
        .I2(wr_din[29]),
        .O(wr_din[1]));
  (* SOFT_HLUTNM = "soft_lutpair42" *) 
  LUT2 #(
    .INIT(4'h2)) 
    ram_reg_0_15_0_13_i_20
       (.I0(Q[6]),
        .I1(Q[1]),
        .O(ram_reg_0_15_0_13_i_20_n_0));
  LUT5 #(
    .INIT(32'hFFFEFEFE)) 
    ram_reg_0_15_0_13_i_3
       (.I0(wr_din[29]),
        .I1(ram_reg_0_15_0_13_i_14_n_0),
        .I2(ram_reg_0_15_0_13_i_15_n_0),
        .I3(\data_int_reg[1]_0 [0]),
        .I4(ram_reg_0_15_0_13_i_13_n_0),
        .O(wr_din[0]));
  (* SOFT_HLUTNM = "soft_lutpair40" *) 
  LUT3 #(
    .INIT(8'hF8)) 
    ram_reg_0_15_0_13_i_4
       (.I0(\data_int_reg[1]_0 [3]),
        .I1(ram_reg_0_15_0_13_i_13_n_0),
        .I2(wr_din[29]),
        .O(wr_din[3]));
  (* SOFT_HLUTNM = "soft_lutpair41" *) 
  LUT2 #(
    .INIT(4'h8)) 
    ram_reg_0_15_0_13_i_5
       (.I0(ram_reg_0_15_0_13_i_13_n_0),
        .I1(\data_int_reg[1]_0 [2]),
        .O(wr_din[2]));
  (* SOFT_HLUTNM = "soft_lutpair39" *) 
  LUT3 #(
    .INIT(8'hF8)) 
    ram_reg_0_15_0_13_i_6
       (.I0(\data_int_reg[1]_0 [5]),
        .I1(ram_reg_0_15_0_13_i_13_n_0),
        .I2(wr_din[29]),
        .O(wr_din[5]));
  (* SOFT_HLUTNM = "soft_lutpair40" *) 
  LUT3 #(
    .INIT(8'hF8)) 
    ram_reg_0_15_0_13_i_7
       (.I0(\data_int_reg[1]_0 [4]),
        .I1(ram_reg_0_15_0_13_i_13_n_0),
        .I2(wr_din[29]),
        .O(wr_din[4]));
  (* SOFT_HLUTNM = "soft_lutpair38" *) 
  LUT3 #(
    .INIT(8'hF8)) 
    ram_reg_0_15_0_13_i_8
       (.I0(\data_int_reg[1]_0 [7]),
        .I1(ram_reg_0_15_0_13_i_13_n_0),
        .I2(wr_din[29]),
        .O(wr_din[7]));
  (* SOFT_HLUTNM = "soft_lutpair39" *) 
  LUT3 #(
    .INIT(8'hF8)) 
    ram_reg_0_15_0_13_i_9
       (.I0(\data_int_reg[1]_0 [6]),
        .I1(ram_reg_0_15_0_13_i_13_n_0),
        .I2(wr_din[29]),
        .O(wr_din[6]));
  (* METHODOLOGY_DRC_VIOS = "" *) 
  (* RTL_RAM_BITS = "512" *) 
  (* RTL_RAM_NAME = "U0/u_uz_interlockDeadtime2L_axi4_inst/u_uz_interlockDeadtime2L_axi4_module_inst/u_uz_interlockDeadtime2L_rdfifo_data_inst/u_uz_interlockDeadtime2L_rdfifo_data_classic_ram_generic/ram" *) 
  (* RTL_RAM_TYPE = "RAM_SDP" *) 
  (* ram_addr_begin = "0" *) 
  (* ram_addr_end = "15" *) 
  (* ram_offset = "0" *) 
  (* ram_slice_begin = "14" *) 
  (* ram_slice_end = "27" *) 
  RAM32M16 #(
    .INIT_A(64'h0000000000000000),
    .INIT_B(64'h0000000000000000),
    .INIT_C(64'h0000000000000000),
    .INIT_D(64'h0000000000000000),
    .INIT_E(64'h0000000000000000),
    .INIT_F(64'h0000000000000000),
    .INIT_G(64'h0000000000000000),
    .INIT_H(64'h0000000000000000)) 
    ram_reg_0_15_14_27
       (.ADDRA({1'b0,\data_int_reg[29]_0 }),
        .ADDRB({1'b0,\data_int_reg[29]_0 }),
        .ADDRC({1'b0,\data_int_reg[29]_0 }),
        .ADDRD({1'b0,\data_int_reg[29]_0 }),
        .ADDRE({1'b0,\data_int_reg[29]_0 }),
        .ADDRF({1'b0,\data_int_reg[29]_0 }),
        .ADDRG({1'b0,\data_int_reg[29]_0 }),
        .ADDRH({1'b0,\data_int_reg[29]_1 }),
        .DIA({wr_din[29],wr_din[29]}),
        .DIB({wr_din[29],wr_din[29]}),
        .DIC({wr_din[29],1'b0}),
        .DID({wr_din[29],1'b0}),
        .DIE({1'b0,wr_din[29]}),
        .DIF({1'b0,wr_din[29]}),
        .DIG({wr_din[29],wr_din[29]}),
        .DIH({1'b0,1'b0}),
        .DOA(p_1_out[15:14]),
        .DOB(p_1_out[17:16]),
        .DOC(p_1_out[19:18]),
        .DOD(p_1_out[21:20]),
        .DOE(p_1_out[23:22]),
        .DOF(p_1_out[25:24]),
        .DOG(p_1_out[27:26]),
        .DOH(NLW_ram_reg_0_15_14_27_DOH_UNCONNECTED[1:0]),
        .WCLK(AXI4_ACLK),
        .WE(E));
  (* METHODOLOGY_DRC_VIOS = "" *) 
  (* RTL_RAM_BITS = "512" *) 
  (* RTL_RAM_NAME = "U0/u_uz_interlockDeadtime2L_axi4_inst/u_uz_interlockDeadtime2L_axi4_module_inst/u_uz_interlockDeadtime2L_rdfifo_data_inst/u_uz_interlockDeadtime2L_rdfifo_data_classic_ram_generic/ram" *) 
  (* RTL_RAM_TYPE = "RAM_SDP" *) 
  (* ram_addr_begin = "0" *) 
  (* ram_addr_end = "15" *) 
  (* ram_offset = "0" *) 
  (* ram_slice_begin = "28" *) 
  (* ram_slice_end = "31" *) 
  RAM32M16 #(
    .INIT_A(64'h0000000000000000),
    .INIT_B(64'h0000000000000000),
    .INIT_C(64'h0000000000000000),
    .INIT_D(64'h0000000000000000),
    .INIT_E(64'h0000000000000000),
    .INIT_F(64'h0000000000000000),
    .INIT_G(64'h0000000000000000),
    .INIT_H(64'h0000000000000000)) 
    ram_reg_0_15_28_31
       (.ADDRA({1'b0,\data_int_reg[29]_0 }),
        .ADDRB({1'b0,\data_int_reg[29]_0 }),
        .ADDRC({1'b0,\data_int_reg[29]_0 }),
        .ADDRD({1'b0,\data_int_reg[29]_0 }),
        .ADDRE({1'b0,\data_int_reg[29]_0 }),
        .ADDRF({1'b0,\data_int_reg[29]_0 }),
        .ADDRG({1'b0,\data_int_reg[29]_0 }),
        .ADDRH({1'b0,\data_int_reg[29]_1 }),
        .DIA({wr_din[29],wr_din[29]}),
        .DIB({1'b0,wr_din[29]}),
        .DIC({1'b0,1'b0}),
        .DID({1'b0,1'b0}),
        .DIE({1'b0,1'b0}),
        .DIF({1'b0,1'b0}),
        .DIG({1'b0,1'b0}),
        .DIH({1'b0,1'b0}),
        .DOA(p_1_out[29:28]),
        .DOB(p_1_out[31:30]),
        .DOC(NLW_ram_reg_0_15_28_31_DOC_UNCONNECTED[1:0]),
        .DOD(NLW_ram_reg_0_15_28_31_DOD_UNCONNECTED[1:0]),
        .DOE(NLW_ram_reg_0_15_28_31_DOE_UNCONNECTED[1:0]),
        .DOF(NLW_ram_reg_0_15_28_31_DOF_UNCONNECTED[1:0]),
        .DOG(NLW_ram_reg_0_15_28_31_DOG_UNCONNECTED[1:0]),
        .DOH(NLW_ram_reg_0_15_28_31_DOH_UNCONNECTED[1:0]),
        .WCLK(AXI4_ACLK),
        .WE(E));
  LUT4 #(
    .INIT(16'h0001)) 
    soft_reset_i_2
       (.I0(Q[13]),
        .I1(Q[12]),
        .I2(Q[11]),
        .I3(Q[10]),
        .O(\waddr_reg[15] ));
  LUT4 #(
    .INIT(16'h0001)) 
    soft_reset_i_3
       (.I0(Q[9]),
        .I1(Q[8]),
        .I2(Q[7]),
        .I3(Q[5]),
        .O(\waddr_reg[11] ));
endmodule

(* ORIG_REF_NAME = "uz_interlockDeadtime2L_SimpleDualPortRAM_generic" *) 
module zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_SimpleDualPortRAM_generic__parameterized1
   (E,
    D,
    data_int,
    w_d1_reg,
    Q,
    top_rd_enb,
    \cache_data_reg[11] ,
    \cache_data_reg[11]_0 ,
    cache_valid,
    \Out_tmp_reg[11] ,
    AXI4_ACLK,
    \data_int_reg[1]_0 ,
    \data_int_reg[1]_1 ,
    \data_int_reg[1]_2 );
  output [0:0]E;
  output [11:0]D;
  output [11:0]data_int;
  output [11:0]w_d1_reg;
  input [4:0]Q;
  input top_rd_enb;
  input \cache_data_reg[11] ;
  input [11:0]\cache_data_reg[11]_0 ;
  input cache_valid;
  input [11:0]\Out_tmp_reg[11] ;
  input AXI4_ACLK;
  input [11:0]\data_int_reg[1]_0 ;
  input [3:0]\data_int_reg[1]_1 ;
  input [3:0]\data_int_reg[1]_2 ;

  wire AXI4_ACLK;
  wire [11:0]D;
  wire [0:0]E;
  wire [11:0]\Out_tmp_reg[11] ;
  wire [4:0]Q;
  wire \cache_data_reg[11] ;
  wire [11:0]\cache_data_reg[11]_0 ;
  wire cache_valid;
  wire [11:0]data_int;
  wire [11:0]\data_int_reg[1]_0 ;
  wire [3:0]\data_int_reg[1]_1 ;
  wire [3:0]\data_int_reg[1]_2 ;
  wire [11:0]p_1_out__0;
  wire top_rd_enb;
  wire [11:0]w_d1_reg;
  wire [1:0]NLW_ram_reg_0_15_0_11_DOG_UNCONNECTED;
  wire [1:0]NLW_ram_reg_0_15_0_11_DOH_UNCONNECTED;

  (* SOFT_HLUTNM = "soft_lutpair61" *) 
  LUT5 #(
    .INIT(32'hFFE400E4)) 
    \Out_tmp[0]_i_1__0 
       (.I0(\cache_data_reg[11] ),
        .I1(\cache_data_reg[11]_0 [0]),
        .I2(data_int[0]),
        .I3(cache_valid),
        .I4(\Out_tmp_reg[11] [0]),
        .O(w_d1_reg[0]));
  (* SOFT_HLUTNM = "soft_lutpair71" *) 
  LUT5 #(
    .INIT(32'hFFE400E4)) 
    \Out_tmp[10]_i_1__0 
       (.I0(\cache_data_reg[11] ),
        .I1(\cache_data_reg[11]_0 [10]),
        .I2(data_int[10]),
        .I3(cache_valid),
        .I4(\Out_tmp_reg[11] [10]),
        .O(w_d1_reg[10]));
  (* SOFT_HLUTNM = "soft_lutpair60" *) 
  LUT5 #(
    .INIT(32'hFFE400E4)) 
    \Out_tmp[11]_i_2 
       (.I0(\cache_data_reg[11] ),
        .I1(\cache_data_reg[11]_0 [11]),
        .I2(data_int[11]),
        .I3(cache_valid),
        .I4(\Out_tmp_reg[11] [11]),
        .O(w_d1_reg[11]));
  (* SOFT_HLUTNM = "soft_lutpair62" *) 
  LUT5 #(
    .INIT(32'hFFE400E4)) 
    \Out_tmp[1]_i_1__0 
       (.I0(\cache_data_reg[11] ),
        .I1(\cache_data_reg[11]_0 [1]),
        .I2(data_int[1]),
        .I3(cache_valid),
        .I4(\Out_tmp_reg[11] [1]),
        .O(w_d1_reg[1]));
  (* SOFT_HLUTNM = "soft_lutpair63" *) 
  LUT5 #(
    .INIT(32'hFFE400E4)) 
    \Out_tmp[2]_i_1__0 
       (.I0(\cache_data_reg[11] ),
        .I1(\cache_data_reg[11]_0 [2]),
        .I2(data_int[2]),
        .I3(cache_valid),
        .I4(\Out_tmp_reg[11] [2]),
        .O(w_d1_reg[2]));
  (* SOFT_HLUTNM = "soft_lutpair64" *) 
  LUT5 #(
    .INIT(32'hFFE400E4)) 
    \Out_tmp[3]_i_1__0 
       (.I0(\cache_data_reg[11] ),
        .I1(\cache_data_reg[11]_0 [3]),
        .I2(data_int[3]),
        .I3(cache_valid),
        .I4(\Out_tmp_reg[11] [3]),
        .O(w_d1_reg[3]));
  (* SOFT_HLUTNM = "soft_lutpair65" *) 
  LUT5 #(
    .INIT(32'hFFE400E4)) 
    \Out_tmp[4]_i_1__0 
       (.I0(\cache_data_reg[11] ),
        .I1(\cache_data_reg[11]_0 [4]),
        .I2(data_int[4]),
        .I3(cache_valid),
        .I4(\Out_tmp_reg[11] [4]),
        .O(w_d1_reg[4]));
  (* SOFT_HLUTNM = "soft_lutpair66" *) 
  LUT5 #(
    .INIT(32'hFFE400E4)) 
    \Out_tmp[5]_i_1__0 
       (.I0(\cache_data_reg[11] ),
        .I1(\cache_data_reg[11]_0 [5]),
        .I2(data_int[5]),
        .I3(cache_valid),
        .I4(\Out_tmp_reg[11] [5]),
        .O(w_d1_reg[5]));
  (* SOFT_HLUTNM = "soft_lutpair67" *) 
  LUT5 #(
    .INIT(32'hFFE400E4)) 
    \Out_tmp[6]_i_1__0 
       (.I0(\cache_data_reg[11] ),
        .I1(\cache_data_reg[11]_0 [6]),
        .I2(data_int[6]),
        .I3(cache_valid),
        .I4(\Out_tmp_reg[11] [6]),
        .O(w_d1_reg[6]));
  (* SOFT_HLUTNM = "soft_lutpair68" *) 
  LUT5 #(
    .INIT(32'hFFE400E4)) 
    \Out_tmp[7]_i_1__0 
       (.I0(\cache_data_reg[11] ),
        .I1(\cache_data_reg[11]_0 [7]),
        .I2(data_int[7]),
        .I3(cache_valid),
        .I4(\Out_tmp_reg[11] [7]),
        .O(w_d1_reg[7]));
  (* SOFT_HLUTNM = "soft_lutpair69" *) 
  LUT5 #(
    .INIT(32'hFFE400E4)) 
    \Out_tmp[8]_i_1__0 
       (.I0(\cache_data_reg[11] ),
        .I1(\cache_data_reg[11]_0 [8]),
        .I2(data_int[8]),
        .I3(cache_valid),
        .I4(\Out_tmp_reg[11] [8]),
        .O(w_d1_reg[8]));
  (* SOFT_HLUTNM = "soft_lutpair70" *) 
  LUT5 #(
    .INIT(32'hFFE400E4)) 
    \Out_tmp[9]_i_1__0 
       (.I0(\cache_data_reg[11] ),
        .I1(\cache_data_reg[11]_0 [9]),
        .I2(data_int[9]),
        .I3(cache_valid),
        .I4(\Out_tmp_reg[11] [9]),
        .O(w_d1_reg[9]));
  (* SOFT_HLUTNM = "soft_lutpair61" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \cache_data[0]_i_1__0 
       (.I0(data_int[0]),
        .I1(\cache_data_reg[11] ),
        .I2(\cache_data_reg[11]_0 [0]),
        .O(D[0]));
  (* SOFT_HLUTNM = "soft_lutpair71" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \cache_data[10]_i_1__0 
       (.I0(data_int[10]),
        .I1(\cache_data_reg[11] ),
        .I2(\cache_data_reg[11]_0 [10]),
        .O(D[10]));
  (* SOFT_HLUTNM = "soft_lutpair60" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \cache_data[11]_i_2 
       (.I0(data_int[11]),
        .I1(\cache_data_reg[11] ),
        .I2(\cache_data_reg[11]_0 [11]),
        .O(D[11]));
  (* SOFT_HLUTNM = "soft_lutpair62" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \cache_data[1]_i_1__0 
       (.I0(data_int[1]),
        .I1(\cache_data_reg[11] ),
        .I2(\cache_data_reg[11]_0 [1]),
        .O(D[1]));
  (* SOFT_HLUTNM = "soft_lutpair63" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \cache_data[2]_i_1__0 
       (.I0(data_int[2]),
        .I1(\cache_data_reg[11] ),
        .I2(\cache_data_reg[11]_0 [2]),
        .O(D[2]));
  (* SOFT_HLUTNM = "soft_lutpair64" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \cache_data[3]_i_1__0 
       (.I0(data_int[3]),
        .I1(\cache_data_reg[11] ),
        .I2(\cache_data_reg[11]_0 [3]),
        .O(D[3]));
  (* SOFT_HLUTNM = "soft_lutpair65" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \cache_data[4]_i_1__0 
       (.I0(data_int[4]),
        .I1(\cache_data_reg[11] ),
        .I2(\cache_data_reg[11]_0 [4]),
        .O(D[4]));
  (* SOFT_HLUTNM = "soft_lutpair66" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \cache_data[5]_i_1__0 
       (.I0(data_int[5]),
        .I1(\cache_data_reg[11] ),
        .I2(\cache_data_reg[11]_0 [5]),
        .O(D[5]));
  (* SOFT_HLUTNM = "soft_lutpair67" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \cache_data[6]_i_1__0 
       (.I0(data_int[6]),
        .I1(\cache_data_reg[11] ),
        .I2(\cache_data_reg[11]_0 [6]),
        .O(D[6]));
  (* SOFT_HLUTNM = "soft_lutpair68" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \cache_data[7]_i_1__0 
       (.I0(data_int[7]),
        .I1(\cache_data_reg[11] ),
        .I2(\cache_data_reg[11]_0 [7]),
        .O(D[7]));
  (* SOFT_HLUTNM = "soft_lutpair69" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \cache_data[8]_i_1__0 
       (.I0(data_int[8]),
        .I1(\cache_data_reg[11] ),
        .I2(\cache_data_reg[11]_0 [8]),
        .O(D[8]));
  (* SOFT_HLUTNM = "soft_lutpair70" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \cache_data[9]_i_1__0 
       (.I0(data_int[9]),
        .I1(\cache_data_reg[11] ),
        .I2(\cache_data_reg[11]_0 [9]),
        .O(D[9]));
  FDRE #(
    .INIT(1'b0)) 
    \data_int_reg[0] 
       (.C(AXI4_ACLK),
        .CE(1'b1),
        .D(p_1_out__0[0]),
        .Q(data_int[0]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \data_int_reg[10] 
       (.C(AXI4_ACLK),
        .CE(1'b1),
        .D(p_1_out__0[10]),
        .Q(data_int[10]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \data_int_reg[11] 
       (.C(AXI4_ACLK),
        .CE(1'b1),
        .D(p_1_out__0[11]),
        .Q(data_int[11]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \data_int_reg[1] 
       (.C(AXI4_ACLK),
        .CE(1'b1),
        .D(p_1_out__0[1]),
        .Q(data_int[1]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \data_int_reg[2] 
       (.C(AXI4_ACLK),
        .CE(1'b1),
        .D(p_1_out__0[2]),
        .Q(data_int[2]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \data_int_reg[3] 
       (.C(AXI4_ACLK),
        .CE(1'b1),
        .D(p_1_out__0[3]),
        .Q(data_int[3]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \data_int_reg[4] 
       (.C(AXI4_ACLK),
        .CE(1'b1),
        .D(p_1_out__0[4]),
        .Q(data_int[4]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \data_int_reg[5] 
       (.C(AXI4_ACLK),
        .CE(1'b1),
        .D(p_1_out__0[5]),
        .Q(data_int[5]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \data_int_reg[6] 
       (.C(AXI4_ACLK),
        .CE(1'b1),
        .D(p_1_out__0[6]),
        .Q(data_int[6]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \data_int_reg[7] 
       (.C(AXI4_ACLK),
        .CE(1'b1),
        .D(p_1_out__0[7]),
        .Q(data_int[7]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \data_int_reg[8] 
       (.C(AXI4_ACLK),
        .CE(1'b1),
        .D(p_1_out__0[8]),
        .Q(data_int[8]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \data_int_reg[9] 
       (.C(AXI4_ACLK),
        .CE(1'b1),
        .D(p_1_out__0[9]),
        .Q(data_int[9]),
        .R(1'b0));
  (* METHODOLOGY_DRC_VIOS = "" *) 
  (* RTL_RAM_BITS = "192" *) 
  (* RTL_RAM_NAME = "U0/u_uz_interlockDeadtime2L_axi4_inst/u_uz_interlockDeadtime2L_axi4_module_inst/u_uz_interlockDeadtime2L_rdfifo_rid_inst/u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram/ram" *) 
  (* RTL_RAM_TYPE = "RAM_SDP" *) 
  (* ram_addr_begin = "0" *) 
  (* ram_addr_end = "15" *) 
  (* ram_offset = "0" *) 
  (* ram_slice_begin = "0" *) 
  (* ram_slice_end = "11" *) 
  RAM32M16 #(
    .INIT_A(64'h0000000000000000),
    .INIT_B(64'h0000000000000000),
    .INIT_C(64'h0000000000000000),
    .INIT_D(64'h0000000000000000),
    .INIT_E(64'h0000000000000000),
    .INIT_F(64'h0000000000000000),
    .INIT_G(64'h0000000000000000),
    .INIT_H(64'h0000000000000000)) 
    ram_reg_0_15_0_11
       (.ADDRA({1'b0,\data_int_reg[1]_1 }),
        .ADDRB({1'b0,\data_int_reg[1]_1 }),
        .ADDRC({1'b0,\data_int_reg[1]_1 }),
        .ADDRD({1'b0,\data_int_reg[1]_1 }),
        .ADDRE({1'b0,\data_int_reg[1]_1 }),
        .ADDRF({1'b0,\data_int_reg[1]_1 }),
        .ADDRG({1'b0,\data_int_reg[1]_1 }),
        .ADDRH({1'b0,\data_int_reg[1]_2 }),
        .DIA(\data_int_reg[1]_0 [1:0]),
        .DIB(\data_int_reg[1]_0 [3:2]),
        .DIC(\data_int_reg[1]_0 [5:4]),
        .DID(\data_int_reg[1]_0 [7:6]),
        .DIE(\data_int_reg[1]_0 [9:8]),
        .DIF(\data_int_reg[1]_0 [11:10]),
        .DIG({1'b0,1'b0}),
        .DIH({1'b0,1'b0}),
        .DOA(p_1_out__0[1:0]),
        .DOB(p_1_out__0[3:2]),
        .DOC(p_1_out__0[5:4]),
        .DOD(p_1_out__0[7:6]),
        .DOE(p_1_out__0[9:8]),
        .DOF(p_1_out__0[11:10]),
        .DOG(NLW_ram_reg_0_15_0_11_DOG_UNCONNECTED[1:0]),
        .DOH(NLW_ram_reg_0_15_0_11_DOH_UNCONNECTED[1:0]),
        .WCLK(AXI4_ACLK),
        .WE(E));
  LUT6 #(
    .INIT(64'hFFFFFFFD00000000)) 
    ram_reg_0_15_0_11_i_1
       (.I0(Q[4]),
        .I1(Q[2]),
        .I2(Q[0]),
        .I3(Q[1]),
        .I4(Q[3]),
        .I5(top_rd_enb),
        .O(E));
endmodule

(* ORIG_REF_NAME = "uz_interlockDeadtime2L_SimpleDualPortRAM_singlebit" *) 
module zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_SimpleDualPortRAM_singlebit
   (E,
    AXI4_RREADY_0,
    w_out,
    cache_data_reg,
    Q,
    top_rd_enb,
    AXI4_RREADY,
    out_valid,
    fifo_valid,
    cache_valid,
    cache_data_reg_0,
    Out_rsvd_reg,
    AXI4_RLAST,
    w_d2_reg,
    w_d2,
    AXI4_ACLK,
    axi4_rlast_1,
    data_int_reg_0,
    data_int_reg_1);
  output [0:0]E;
  output AXI4_RREADY_0;
  output w_out;
  output cache_data_reg;
  input [4:0]Q;
  input top_rd_enb;
  input AXI4_RREADY;
  input out_valid;
  input fifo_valid;
  input cache_valid;
  input cache_data_reg_0;
  input Out_rsvd_reg;
  input AXI4_RLAST;
  input w_d2_reg;
  input w_d2;
  input AXI4_ACLK;
  input axi4_rlast_1;
  input [3:0]data_int_reg_0;
  input [3:0]data_int_reg_1;

  wire AXI4_ACLK;
  wire AXI4_RLAST;
  wire AXI4_RREADY;
  wire AXI4_RREADY_0;
  wire [0:0]E;
  wire Out_rsvd_reg;
  wire [4:0]Q;
  wire axi4_rlast_1;
  wire cache_data_reg;
  wire cache_data_reg_0;
  wire cache_valid;
  wire [3:0]data_int_reg_0;
  wire [3:0]data_int_reg_1;
  wire fifo_valid;
  wire out_valid;
  wire p_1_out__1;
  wire top_rd_enb;
  wire w_d2;
  wire w_d2_reg;
  wire w_out;
  wire w_waddr_1;
  wire NLW_ram_reg_0_15_0_0_SPO_UNCONNECTED;

  LUT6 #(
    .INIT(64'hAACFFFFFAAC00000)) 
    Out_rsvd_i_1
       (.I0(cache_data_reg_0),
        .I1(w_out),
        .I2(fifo_valid),
        .I3(cache_valid),
        .I4(Out_rsvd_reg),
        .I5(AXI4_RLAST),
        .O(cache_data_reg));
  LUT6 #(
    .INIT(64'hBAFFEFFF8A002000)) 
    cache_data_i_1
       (.I0(w_out),
        .I1(AXI4_RREADY),
        .I2(out_valid),
        .I3(fifo_valid),
        .I4(cache_valid),
        .I5(cache_data_reg_0),
        .O(AXI4_RREADY_0));
  FDRE #(
    .INIT(1'b0)) 
    data_int_reg
       (.C(AXI4_ACLK),
        .CE(1'b1),
        .D(p_1_out__1),
        .Q(w_waddr_1),
        .R(1'b0));
  (* RTL_RAM_BITS = "16" *) 
  (* RTL_RAM_NAME = "U0/u_uz_interlockDeadtime2L_axi4_inst/u_uz_interlockDeadtime2L_axi4_module_inst/u_uz_interlockDeadtime2L_rdfifo_last_inst/u_uz_interlockDeadtime2L_rdfifo_last_classic_ram_singlebit/ram" *) 
  (* RTL_RAM_TYPE = "RAM_TDP" *) 
  (* XILINX_LEGACY_PRIM = "RAM16X1D" *) 
  (* ram_addr_begin = "0" *) 
  (* ram_addr_end = "15" *) 
  (* ram_offset = "0" *) 
  (* ram_slice_begin = "0" *) 
  (* ram_slice_end = "0" *) 
  RAM32X1D #(
    .INIT(32'h00000000)) 
    ram_reg_0_15_0_0
       (.A0(data_int_reg_0[0]),
        .A1(data_int_reg_0[1]),
        .A2(data_int_reg_0[2]),
        .A3(data_int_reg_0[3]),
        .A4(1'b0),
        .D(axi4_rlast_1),
        .DPO(p_1_out__1),
        .DPRA0(data_int_reg_1[0]),
        .DPRA1(data_int_reg_1[1]),
        .DPRA2(data_int_reg_1[2]),
        .DPRA3(data_int_reg_1[3]),
        .DPRA4(1'b0),
        .SPO(NLW_ram_reg_0_15_0_0_SPO_UNCONNECTED),
        .WCLK(AXI4_ACLK),
        .WE(E));
  LUT6 #(
    .INIT(64'hFFFFFFFD00000000)) 
    ram_reg_0_15_0_0_i_1
       (.I0(Q[4]),
        .I1(Q[2]),
        .I2(Q[0]),
        .I3(Q[1]),
        .I4(Q[3]),
        .I5(top_rd_enb),
        .O(E));
  LUT3 #(
    .INIT(8'hB8)) 
    w_d2_i_1
       (.I0(w_waddr_1),
        .I1(w_d2_reg),
        .I2(w_d2),
        .O(w_out));
endmodule

(* ORIG_REF_NAME = "uz_interlockDeadtime2L_addr_decoder" *) 
module zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_addr_decoder
   (read_reg_ip_timestamp,
    read_reg_axi_fb_InverseBotSwitch,
    read_reg_axi_fb_enable,
    data_reg_axi_enable_1_1_reg_0,
    axi_EnableOutput,
    axi_InverseBotSwitch,
    E,
    SR,
    data_reg_axi_enable_1_1_reg_1,
    data_reg_axi_enable_1_1_reg_2,
    data_reg_axi_enable_1_1_reg_3,
    data_reg_axi_enable_1_1_reg_4,
    data_reg_axi_enable_1_1_reg_5,
    data_reg_axi_enable_1_1_reg_6,
    data_reg_axi_enable_1_1_reg_7,
    data_reg_axi_enable_1_1_reg_8,
    data_reg_axi_enable_1_1_reg_9,
    data_reg_axi_enable_1_1_reg_10,
    data_reg_axi_enable_1_1_reg_11,
    \data_reg_axi_DelayCycles_1_1_reg[9]_0 ,
    \read_reg_axi_fb_DelayCycles_reg[9]_0 ,
    reset_x,
    AXI4_ACLK,
    Delay3_out1,
    read_reg_axi_fb_enable_reg_0,
    data_reg_axi_enable_1_1_reg_12,
    data_reg_axi_EnableOutput_1_1_reg_0,
    data_reg_axi_InverseBotSwitch_1_1_reg_0,
    S0,
    PipelineDelay1_out1,
    PipelineDelay1_out1_0,
    PipelineDelay1_out1_1,
    PipelineDelay1_out1_2,
    PipelineDelay1_out1_3,
    PipelineDelay1_out1_4,
    S1,
    S2,
    S3,
    S4,
    S5,
    \data_reg_axi_DelayCycles_1_1_reg[9]_1 ,
    Q,
    \read_reg_axi_fb_DelayCycles_reg[9]_1 );
  output [0:0]read_reg_ip_timestamp;
  output read_reg_axi_fb_InverseBotSwitch;
  output read_reg_axi_fb_enable;
  output data_reg_axi_enable_1_1_reg_0;
  output axi_EnableOutput;
  output axi_InverseBotSwitch;
  output [0:0]E;
  output [0:0]SR;
  output [0:0]data_reg_axi_enable_1_1_reg_1;
  output [0:0]data_reg_axi_enable_1_1_reg_2;
  output [0:0]data_reg_axi_enable_1_1_reg_3;
  output [0:0]data_reg_axi_enable_1_1_reg_4;
  output [0:0]data_reg_axi_enable_1_1_reg_5;
  output data_reg_axi_enable_1_1_reg_6;
  output [0:0]data_reg_axi_enable_1_1_reg_7;
  output [0:0]data_reg_axi_enable_1_1_reg_8;
  output [0:0]data_reg_axi_enable_1_1_reg_9;
  output [0:0]data_reg_axi_enable_1_1_reg_10;
  output [0:0]data_reg_axi_enable_1_1_reg_11;
  output [9:0]\data_reg_axi_DelayCycles_1_1_reg[9]_0 ;
  output [9:0]\read_reg_axi_fb_DelayCycles_reg[9]_0 ;
  input reset_x;
  input AXI4_ACLK;
  input Delay3_out1;
  input read_reg_axi_fb_enable_reg_0;
  input data_reg_axi_enable_1_1_reg_12;
  input data_reg_axi_EnableOutput_1_1_reg_0;
  input data_reg_axi_InverseBotSwitch_1_1_reg_0;
  input S0;
  input PipelineDelay1_out1;
  input PipelineDelay1_out1_0;
  input PipelineDelay1_out1_1;
  input PipelineDelay1_out1_2;
  input PipelineDelay1_out1_3;
  input PipelineDelay1_out1_4;
  input S1;
  input S2;
  input S3;
  input S4;
  input S5;
  input [0:0]\data_reg_axi_DelayCycles_1_1_reg[9]_1 ;
  input [9:0]Q;
  input [9:0]\read_reg_axi_fb_DelayCycles_reg[9]_1 ;

  wire AXI4_ACLK;
  wire Delay3_out1;
  wire [0:0]E;
  wire PipelineDelay1_out1;
  wire PipelineDelay1_out1_0;
  wire PipelineDelay1_out1_1;
  wire PipelineDelay1_out1_2;
  wire PipelineDelay1_out1_3;
  wire PipelineDelay1_out1_4;
  wire [9:0]Q;
  wire S0;
  wire S1;
  wire S2;
  wire S3;
  wire S4;
  wire S5;
  wire [0:0]SR;
  wire axi_EnableOutput;
  wire axi_InverseBotSwitch;
  wire [9:0]\data_reg_axi_DelayCycles_1_1_reg[9]_0 ;
  wire [0:0]\data_reg_axi_DelayCycles_1_1_reg[9]_1 ;
  wire data_reg_axi_EnableOutput_1_1_reg_0;
  wire data_reg_axi_InverseBotSwitch_1_1_reg_0;
  wire data_reg_axi_enable_1_1_reg_0;
  wire [0:0]data_reg_axi_enable_1_1_reg_1;
  wire [0:0]data_reg_axi_enable_1_1_reg_10;
  wire [0:0]data_reg_axi_enable_1_1_reg_11;
  wire data_reg_axi_enable_1_1_reg_12;
  wire [0:0]data_reg_axi_enable_1_1_reg_2;
  wire [0:0]data_reg_axi_enable_1_1_reg_3;
  wire [0:0]data_reg_axi_enable_1_1_reg_4;
  wire [0:0]data_reg_axi_enable_1_1_reg_5;
  wire data_reg_axi_enable_1_1_reg_6;
  wire [0:0]data_reg_axi_enable_1_1_reg_7;
  wire [0:0]data_reg_axi_enable_1_1_reg_8;
  wire [0:0]data_reg_axi_enable_1_1_reg_9;
  wire [9:0]\read_reg_axi_fb_DelayCycles_reg[9]_0 ;
  wire [9:0]\read_reg_axi_fb_DelayCycles_reg[9]_1 ;
  wire read_reg_axi_fb_InverseBotSwitch;
  wire read_reg_axi_fb_enable;
  wire read_reg_axi_fb_enable_reg_0;
  wire [0:0]read_reg_ip_timestamp;
  wire reset_x;

  (* SOFT_HLUTNM = "soft_lutpair3" *) 
  LUT2 #(
    .INIT(4'hE)) 
    Delay2_delOut_i_1
       (.I0(data_reg_axi_enable_1_1_reg_0),
        .I1(reset_x),
        .O(data_reg_axi_enable_1_1_reg_6));
  (* SOFT_HLUTNM = "soft_lutpair0" *) 
  LUT3 #(
    .INIT(8'hEC)) 
    \HDL_Counter_out1[9]_i_1 
       (.I0(data_reg_axi_enable_1_1_reg_0),
        .I1(reset_x),
        .I2(PipelineDelay1_out1),
        .O(SR));
  (* SOFT_HLUTNM = "soft_lutpair0" *) 
  LUT3 #(
    .INIT(8'hF8)) 
    \HDL_Counter_out1[9]_i_1__0 
       (.I0(data_reg_axi_enable_1_1_reg_0),
        .I1(PipelineDelay1_out1_0),
        .I2(reset_x),
        .O(data_reg_axi_enable_1_1_reg_1));
  (* SOFT_HLUTNM = "soft_lutpair1" *) 
  LUT3 #(
    .INIT(8'hF8)) 
    \HDL_Counter_out1[9]_i_1__1 
       (.I0(data_reg_axi_enable_1_1_reg_0),
        .I1(PipelineDelay1_out1_1),
        .I2(reset_x),
        .O(data_reg_axi_enable_1_1_reg_2));
  (* SOFT_HLUTNM = "soft_lutpair1" *) 
  LUT3 #(
    .INIT(8'hF8)) 
    \HDL_Counter_out1[9]_i_1__2 
       (.I0(data_reg_axi_enable_1_1_reg_0),
        .I1(PipelineDelay1_out1_2),
        .I2(reset_x),
        .O(data_reg_axi_enable_1_1_reg_3));
  (* SOFT_HLUTNM = "soft_lutpair2" *) 
  LUT3 #(
    .INIT(8'hF8)) 
    \HDL_Counter_out1[9]_i_1__3 
       (.I0(data_reg_axi_enable_1_1_reg_0),
        .I1(PipelineDelay1_out1_3),
        .I2(reset_x),
        .O(data_reg_axi_enable_1_1_reg_4));
  (* SOFT_HLUTNM = "soft_lutpair2" *) 
  LUT3 #(
    .INIT(8'hF8)) 
    \HDL_Counter_out1[9]_i_1__4 
       (.I0(data_reg_axi_enable_1_1_reg_0),
        .I1(PipelineDelay1_out1_4),
        .I2(reset_x),
        .O(data_reg_axi_enable_1_1_reg_5));
  (* SOFT_HLUTNM = "soft_lutpair3" *) 
  LUT2 #(
    .INIT(4'h8)) 
    \HDL_Counter_out1[9]_i_2 
       (.I0(S0),
        .I1(data_reg_axi_enable_1_1_reg_0),
        .O(E));
  (* SOFT_HLUTNM = "soft_lutpair4" *) 
  LUT2 #(
    .INIT(4'h8)) 
    \HDL_Counter_out1[9]_i_2__0 
       (.I0(data_reg_axi_enable_1_1_reg_0),
        .I1(S1),
        .O(data_reg_axi_enable_1_1_reg_7));
  (* SOFT_HLUTNM = "soft_lutpair4" *) 
  LUT2 #(
    .INIT(4'h8)) 
    \HDL_Counter_out1[9]_i_2__1 
       (.I0(data_reg_axi_enable_1_1_reg_0),
        .I1(S2),
        .O(data_reg_axi_enable_1_1_reg_8));
  (* SOFT_HLUTNM = "soft_lutpair5" *) 
  LUT2 #(
    .INIT(4'h8)) 
    \HDL_Counter_out1[9]_i_2__2 
       (.I0(data_reg_axi_enable_1_1_reg_0),
        .I1(S3),
        .O(data_reg_axi_enable_1_1_reg_9));
  (* SOFT_HLUTNM = "soft_lutpair5" *) 
  LUT2 #(
    .INIT(4'h8)) 
    \HDL_Counter_out1[9]_i_2__3 
       (.I0(data_reg_axi_enable_1_1_reg_0),
        .I1(S4),
        .O(data_reg_axi_enable_1_1_reg_10));
  LUT2 #(
    .INIT(4'h8)) 
    \HDL_Counter_out1[9]_i_2__4 
       (.I0(data_reg_axi_enable_1_1_reg_0),
        .I1(S5),
        .O(data_reg_axi_enable_1_1_reg_11));
  FDRE \data_reg_axi_DelayCycles_1_1_reg[0] 
       (.C(AXI4_ACLK),
        .CE(\data_reg_axi_DelayCycles_1_1_reg[9]_1 ),
        .D(Q[0]),
        .Q(\data_reg_axi_DelayCycles_1_1_reg[9]_0 [0]),
        .R(reset_x));
  FDRE \data_reg_axi_DelayCycles_1_1_reg[1] 
       (.C(AXI4_ACLK),
        .CE(\data_reg_axi_DelayCycles_1_1_reg[9]_1 ),
        .D(Q[1]),
        .Q(\data_reg_axi_DelayCycles_1_1_reg[9]_0 [1]),
        .R(reset_x));
  FDRE \data_reg_axi_DelayCycles_1_1_reg[2] 
       (.C(AXI4_ACLK),
        .CE(\data_reg_axi_DelayCycles_1_1_reg[9]_1 ),
        .D(Q[2]),
        .Q(\data_reg_axi_DelayCycles_1_1_reg[9]_0 [2]),
        .R(reset_x));
  FDRE \data_reg_axi_DelayCycles_1_1_reg[3] 
       (.C(AXI4_ACLK),
        .CE(\data_reg_axi_DelayCycles_1_1_reg[9]_1 ),
        .D(Q[3]),
        .Q(\data_reg_axi_DelayCycles_1_1_reg[9]_0 [3]),
        .R(reset_x));
  FDRE \data_reg_axi_DelayCycles_1_1_reg[4] 
       (.C(AXI4_ACLK),
        .CE(\data_reg_axi_DelayCycles_1_1_reg[9]_1 ),
        .D(Q[4]),
        .Q(\data_reg_axi_DelayCycles_1_1_reg[9]_0 [4]),
        .R(reset_x));
  FDRE \data_reg_axi_DelayCycles_1_1_reg[5] 
       (.C(AXI4_ACLK),
        .CE(\data_reg_axi_DelayCycles_1_1_reg[9]_1 ),
        .D(Q[5]),
        .Q(\data_reg_axi_DelayCycles_1_1_reg[9]_0 [5]),
        .R(reset_x));
  FDRE \data_reg_axi_DelayCycles_1_1_reg[6] 
       (.C(AXI4_ACLK),
        .CE(\data_reg_axi_DelayCycles_1_1_reg[9]_1 ),
        .D(Q[6]),
        .Q(\data_reg_axi_DelayCycles_1_1_reg[9]_0 [6]),
        .R(reset_x));
  FDRE \data_reg_axi_DelayCycles_1_1_reg[7] 
       (.C(AXI4_ACLK),
        .CE(\data_reg_axi_DelayCycles_1_1_reg[9]_1 ),
        .D(Q[7]),
        .Q(\data_reg_axi_DelayCycles_1_1_reg[9]_0 [7]),
        .R(reset_x));
  FDRE \data_reg_axi_DelayCycles_1_1_reg[8] 
       (.C(AXI4_ACLK),
        .CE(\data_reg_axi_DelayCycles_1_1_reg[9]_1 ),
        .D(Q[8]),
        .Q(\data_reg_axi_DelayCycles_1_1_reg[9]_0 [8]),
        .R(reset_x));
  FDRE \data_reg_axi_DelayCycles_1_1_reg[9] 
       (.C(AXI4_ACLK),
        .CE(\data_reg_axi_DelayCycles_1_1_reg[9]_1 ),
        .D(Q[9]),
        .Q(\data_reg_axi_DelayCycles_1_1_reg[9]_0 [9]),
        .R(reset_x));
  FDRE data_reg_axi_EnableOutput_1_1_reg
       (.C(AXI4_ACLK),
        .CE(1'b1),
        .D(data_reg_axi_EnableOutput_1_1_reg_0),
        .Q(axi_EnableOutput),
        .R(reset_x));
  FDRE data_reg_axi_InverseBotSwitch_1_1_reg
       (.C(AXI4_ACLK),
        .CE(1'b1),
        .D(data_reg_axi_InverseBotSwitch_1_1_reg_0),
        .Q(axi_InverseBotSwitch),
        .R(reset_x));
  FDSE data_reg_axi_enable_1_1_reg
       (.C(AXI4_ACLK),
        .CE(1'b1),
        .D(data_reg_axi_enable_1_1_reg_12),
        .Q(data_reg_axi_enable_1_1_reg_0),
        .S(reset_x));
  FDRE \read_reg_axi_fb_DelayCycles_reg[0] 
       (.C(AXI4_ACLK),
        .CE(1'b1),
        .D(\read_reg_axi_fb_DelayCycles_reg[9]_1 [0]),
        .Q(\read_reg_axi_fb_DelayCycles_reg[9]_0 [0]),
        .R(reset_x));
  FDRE \read_reg_axi_fb_DelayCycles_reg[1] 
       (.C(AXI4_ACLK),
        .CE(1'b1),
        .D(\read_reg_axi_fb_DelayCycles_reg[9]_1 [1]),
        .Q(\read_reg_axi_fb_DelayCycles_reg[9]_0 [1]),
        .R(reset_x));
  FDRE \read_reg_axi_fb_DelayCycles_reg[2] 
       (.C(AXI4_ACLK),
        .CE(1'b1),
        .D(\read_reg_axi_fb_DelayCycles_reg[9]_1 [2]),
        .Q(\read_reg_axi_fb_DelayCycles_reg[9]_0 [2]),
        .R(reset_x));
  FDRE \read_reg_axi_fb_DelayCycles_reg[3] 
       (.C(AXI4_ACLK),
        .CE(1'b1),
        .D(\read_reg_axi_fb_DelayCycles_reg[9]_1 [3]),
        .Q(\read_reg_axi_fb_DelayCycles_reg[9]_0 [3]),
        .R(reset_x));
  FDRE \read_reg_axi_fb_DelayCycles_reg[4] 
       (.C(AXI4_ACLK),
        .CE(1'b1),
        .D(\read_reg_axi_fb_DelayCycles_reg[9]_1 [4]),
        .Q(\read_reg_axi_fb_DelayCycles_reg[9]_0 [4]),
        .R(reset_x));
  FDRE \read_reg_axi_fb_DelayCycles_reg[5] 
       (.C(AXI4_ACLK),
        .CE(1'b1),
        .D(\read_reg_axi_fb_DelayCycles_reg[9]_1 [5]),
        .Q(\read_reg_axi_fb_DelayCycles_reg[9]_0 [5]),
        .R(reset_x));
  FDRE \read_reg_axi_fb_DelayCycles_reg[6] 
       (.C(AXI4_ACLK),
        .CE(1'b1),
        .D(\read_reg_axi_fb_DelayCycles_reg[9]_1 [6]),
        .Q(\read_reg_axi_fb_DelayCycles_reg[9]_0 [6]),
        .R(reset_x));
  FDRE \read_reg_axi_fb_DelayCycles_reg[7] 
       (.C(AXI4_ACLK),
        .CE(1'b1),
        .D(\read_reg_axi_fb_DelayCycles_reg[9]_1 [7]),
        .Q(\read_reg_axi_fb_DelayCycles_reg[9]_0 [7]),
        .R(reset_x));
  FDRE \read_reg_axi_fb_DelayCycles_reg[8] 
       (.C(AXI4_ACLK),
        .CE(1'b1),
        .D(\read_reg_axi_fb_DelayCycles_reg[9]_1 [8]),
        .Q(\read_reg_axi_fb_DelayCycles_reg[9]_0 [8]),
        .R(reset_x));
  FDRE \read_reg_axi_fb_DelayCycles_reg[9] 
       (.C(AXI4_ACLK),
        .CE(1'b1),
        .D(\read_reg_axi_fb_DelayCycles_reg[9]_1 [9]),
        .Q(\read_reg_axi_fb_DelayCycles_reg[9]_0 [9]),
        .R(reset_x));
  FDRE read_reg_axi_fb_InverseBotSwitch_reg
       (.C(AXI4_ACLK),
        .CE(1'b1),
        .D(Delay3_out1),
        .Q(read_reg_axi_fb_InverseBotSwitch),
        .R(reset_x));
  FDRE read_reg_axi_fb_enable_reg
       (.C(AXI4_ACLK),
        .CE(1'b1),
        .D(read_reg_axi_fb_enable_reg_0),
        .Q(read_reg_axi_fb_enable),
        .R(reset_x));
  FDRE \read_reg_ip_timestamp_reg[29] 
       (.C(AXI4_ACLK),
        .CE(1'b1),
        .D(1'b1),
        .Q(read_reg_ip_timestamp),
        .R(reset_x));
endmodule

(* ORIG_REF_NAME = "uz_interlockDeadtime2L_axi4" *) 
module zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_axi4
   (out_valid_reg,
    write_axi_enable,
    axi_EnableOutput,
    axi_InverseBotSwitch,
    AXI4_RLAST,
    soft_reset,
    Q,
    AXI4_ARREADY,
    AXI4_AWREADY,
    reset_in,
    E,
    SR,
    data_reg_axi_enable_1_1_reg,
    data_reg_axi_enable_1_1_reg_0,
    data_reg_axi_enable_1_1_reg_1,
    data_reg_axi_enable_1_1_reg_2,
    data_reg_axi_enable_1_1_reg_3,
    data_reg_axi_enable_1_1_reg_4,
    data_reg_axi_enable_1_1_reg_5,
    data_reg_axi_enable_1_1_reg_6,
    data_reg_axi_enable_1_1_reg_7,
    data_reg_axi_enable_1_1_reg_8,
    data_reg_axi_enable_1_1_reg_9,
    \data_reg_axi_DelayCycles_1_1_reg[9] ,
    AXI4_RDATA,
    AXI4_RID,
    AXI4_BID,
    AXI4_WSTRB,
    AXI4_ACLK,
    reset_x,
    Delay3_out1,
    read_reg_axi_fb_enable_reg,
    AXI4_ARADDR,
    AXI4_AWADDR,
    AXI4_RREADY,
    AXI4_ARESETN,
    AXI4_AWVALID,
    AXI4_BREADY,
    AXI4_ARVALID,
    AXI4_WVALID,
    AXI4_WLAST,
    IPCORE_RESETN,
    AXI4_ARLEN,
    S0,
    PipelineDelay1_out1,
    PipelineDelay1_out1_0,
    PipelineDelay1_out1_1,
    PipelineDelay1_out1_2,
    PipelineDelay1_out1_3,
    PipelineDelay1_out1_4,
    S1,
    S2,
    S3,
    S4,
    S5,
    AXI4_ARBURST,
    AXI4_AWBURST,
    AXI4_WDATA,
    \read_reg_axi_fb_DelayCycles_reg[9] ,
    AXI4_ARID,
    AXI4_AWID);
  output out_valid_reg;
  output write_axi_enable;
  output axi_EnableOutput;
  output axi_InverseBotSwitch;
  output AXI4_RLAST;
  output soft_reset;
  output [1:0]Q;
  output AXI4_ARREADY;
  output AXI4_AWREADY;
  output reset_in;
  output [0:0]E;
  output [0:0]SR;
  output [0:0]data_reg_axi_enable_1_1_reg;
  output [0:0]data_reg_axi_enable_1_1_reg_0;
  output [0:0]data_reg_axi_enable_1_1_reg_1;
  output [0:0]data_reg_axi_enable_1_1_reg_2;
  output [0:0]data_reg_axi_enable_1_1_reg_3;
  output data_reg_axi_enable_1_1_reg_4;
  output [0:0]data_reg_axi_enable_1_1_reg_5;
  output [0:0]data_reg_axi_enable_1_1_reg_6;
  output [0:0]data_reg_axi_enable_1_1_reg_7;
  output [0:0]data_reg_axi_enable_1_1_reg_8;
  output [0:0]data_reg_axi_enable_1_1_reg_9;
  output [9:0]\data_reg_axi_DelayCycles_1_1_reg[9] ;
  output [31:0]AXI4_RDATA;
  output [11:0]AXI4_RID;
  output [11:0]AXI4_BID;
  input [3:0]AXI4_WSTRB;
  input AXI4_ACLK;
  input reset_x;
  input Delay3_out1;
  input read_reg_axi_fb_enable_reg;
  input [13:0]AXI4_ARADDR;
  input [13:0]AXI4_AWADDR;
  input AXI4_RREADY;
  input AXI4_ARESETN;
  input AXI4_AWVALID;
  input AXI4_BREADY;
  input AXI4_ARVALID;
  input AXI4_WVALID;
  input AXI4_WLAST;
  input IPCORE_RESETN;
  input [7:0]AXI4_ARLEN;
  input S0;
  input PipelineDelay1_out1;
  input PipelineDelay1_out1_0;
  input PipelineDelay1_out1_1;
  input PipelineDelay1_out1_2;
  input PipelineDelay1_out1_3;
  input PipelineDelay1_out1_4;
  input S1;
  input S2;
  input S3;
  input S4;
  input S5;
  input [1:0]AXI4_ARBURST;
  input [1:0]AXI4_AWBURST;
  input [9:0]AXI4_WDATA;
  input [9:0]\read_reg_axi_fb_DelayCycles_reg[9] ;
  input [11:0]AXI4_ARID;
  input [11:0]AXI4_AWID;

  wire AXI4_ACLK;
  wire [13:0]AXI4_ARADDR;
  wire [1:0]AXI4_ARBURST;
  wire AXI4_ARESETN;
  wire [11:0]AXI4_ARID;
  wire [7:0]AXI4_ARLEN;
  wire AXI4_ARREADY;
  wire AXI4_ARVALID;
  wire [13:0]AXI4_AWADDR;
  wire [1:0]AXI4_AWBURST;
  wire [11:0]AXI4_AWID;
  wire AXI4_AWREADY;
  wire AXI4_AWVALID;
  wire [11:0]AXI4_BID;
  wire AXI4_BREADY;
  wire [31:0]AXI4_RDATA;
  wire [11:0]AXI4_RID;
  wire AXI4_RLAST;
  wire AXI4_RREADY;
  wire [9:0]AXI4_WDATA;
  wire AXI4_WLAST;
  wire [3:0]AXI4_WSTRB;
  wire AXI4_WVALID;
  wire Delay3_out1;
  wire [0:0]E;
  wire IPCORE_RESETN;
  wire PipelineDelay1_out1;
  wire PipelineDelay1_out1_0;
  wire PipelineDelay1_out1_1;
  wire PipelineDelay1_out1_2;
  wire PipelineDelay1_out1_3;
  wire PipelineDelay1_out1_4;
  wire [1:0]Q;
  wire S0;
  wire S1;
  wire S2;
  wire S3;
  wire S4;
  wire S5;
  wire [0:0]SR;
  wire axi_EnableOutput;
  wire axi_InverseBotSwitch;
  wire [9:0]\data_reg_axi_DelayCycles_1_1_reg[9] ;
  wire [0:0]data_reg_axi_enable_1_1_reg;
  wire [0:0]data_reg_axi_enable_1_1_reg_0;
  wire [0:0]data_reg_axi_enable_1_1_reg_1;
  wire [0:0]data_reg_axi_enable_1_1_reg_2;
  wire [0:0]data_reg_axi_enable_1_1_reg_3;
  wire data_reg_axi_enable_1_1_reg_4;
  wire [0:0]data_reg_axi_enable_1_1_reg_5;
  wire [0:0]data_reg_axi_enable_1_1_reg_6;
  wire [0:0]data_reg_axi_enable_1_1_reg_7;
  wire [0:0]data_reg_axi_enable_1_1_reg_8;
  wire [0:0]data_reg_axi_enable_1_1_reg_9;
  wire out_valid_reg;
  wire [9:0]read_reg_axi_fb_DelayCycles;
  wire [9:0]\read_reg_axi_fb_DelayCycles_reg[9] ;
  wire read_reg_axi_fb_InverseBotSwitch;
  wire read_reg_axi_fb_enable;
  wire read_reg_axi_fb_enable_reg;
  wire [29:29]read_reg_ip_timestamp;
  wire reg_enb_axi_DelayCycles_1_1;
  wire reset_in;
  wire reset_x;
  wire soft_reset;
  wire u_uz_interlockDeadtime2L_axi4_module_inst_n_10;
  wire u_uz_interlockDeadtime2L_axi4_module_inst_n_11;
  wire u_uz_interlockDeadtime2L_axi4_module_inst_n_12;
  wire u_uz_interlockDeadtime2L_axi4_module_inst_n_13;
  wire u_uz_interlockDeadtime2L_axi4_module_inst_n_14;
  wire u_uz_interlockDeadtime2L_axi4_module_inst_n_15;
  wire u_uz_interlockDeadtime2L_axi4_module_inst_n_16;
  wire u_uz_interlockDeadtime2L_axi4_module_inst_n_17;
  wire u_uz_interlockDeadtime2L_axi4_module_inst_n_18;
  wire u_uz_interlockDeadtime2L_axi4_module_inst_n_19;
  wire u_uz_interlockDeadtime2L_axi4_module_inst_n_20;
  wire u_uz_interlockDeadtime2L_axi4_module_inst_n_21;
  wire u_uz_interlockDeadtime2L_axi4_module_inst_n_9;
  wire write_axi_enable;

  zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_addr_decoder u_uz_interlockDeadtime2L_addr_decoder_inst
       (.AXI4_ACLK(AXI4_ACLK),
        .Delay3_out1(Delay3_out1),
        .E(E),
        .PipelineDelay1_out1(PipelineDelay1_out1),
        .PipelineDelay1_out1_0(PipelineDelay1_out1_0),
        .PipelineDelay1_out1_1(PipelineDelay1_out1_1),
        .PipelineDelay1_out1_2(PipelineDelay1_out1_2),
        .PipelineDelay1_out1_3(PipelineDelay1_out1_3),
        .PipelineDelay1_out1_4(PipelineDelay1_out1_4),
        .Q({u_uz_interlockDeadtime2L_axi4_module_inst_n_9,u_uz_interlockDeadtime2L_axi4_module_inst_n_10,u_uz_interlockDeadtime2L_axi4_module_inst_n_11,u_uz_interlockDeadtime2L_axi4_module_inst_n_12,u_uz_interlockDeadtime2L_axi4_module_inst_n_13,u_uz_interlockDeadtime2L_axi4_module_inst_n_14,u_uz_interlockDeadtime2L_axi4_module_inst_n_15,u_uz_interlockDeadtime2L_axi4_module_inst_n_16,u_uz_interlockDeadtime2L_axi4_module_inst_n_17,u_uz_interlockDeadtime2L_axi4_module_inst_n_18}),
        .S0(S0),
        .S1(S1),
        .S2(S2),
        .S3(S3),
        .S4(S4),
        .S5(S5),
        .SR(SR),
        .axi_EnableOutput(axi_EnableOutput),
        .axi_InverseBotSwitch(axi_InverseBotSwitch),
        .\data_reg_axi_DelayCycles_1_1_reg[9]_0 (\data_reg_axi_DelayCycles_1_1_reg[9] ),
        .\data_reg_axi_DelayCycles_1_1_reg[9]_1 (reg_enb_axi_DelayCycles_1_1),
        .data_reg_axi_EnableOutput_1_1_reg_0(u_uz_interlockDeadtime2L_axi4_module_inst_n_20),
        .data_reg_axi_InverseBotSwitch_1_1_reg_0(u_uz_interlockDeadtime2L_axi4_module_inst_n_21),
        .data_reg_axi_enable_1_1_reg_0(write_axi_enable),
        .data_reg_axi_enable_1_1_reg_1(data_reg_axi_enable_1_1_reg),
        .data_reg_axi_enable_1_1_reg_10(data_reg_axi_enable_1_1_reg_8),
        .data_reg_axi_enable_1_1_reg_11(data_reg_axi_enable_1_1_reg_9),
        .data_reg_axi_enable_1_1_reg_12(u_uz_interlockDeadtime2L_axi4_module_inst_n_19),
        .data_reg_axi_enable_1_1_reg_2(data_reg_axi_enable_1_1_reg_0),
        .data_reg_axi_enable_1_1_reg_3(data_reg_axi_enable_1_1_reg_1),
        .data_reg_axi_enable_1_1_reg_4(data_reg_axi_enable_1_1_reg_2),
        .data_reg_axi_enable_1_1_reg_5(data_reg_axi_enable_1_1_reg_3),
        .data_reg_axi_enable_1_1_reg_6(data_reg_axi_enable_1_1_reg_4),
        .data_reg_axi_enable_1_1_reg_7(data_reg_axi_enable_1_1_reg_5),
        .data_reg_axi_enable_1_1_reg_8(data_reg_axi_enable_1_1_reg_6),
        .data_reg_axi_enable_1_1_reg_9(data_reg_axi_enable_1_1_reg_7),
        .\read_reg_axi_fb_DelayCycles_reg[9]_0 (read_reg_axi_fb_DelayCycles),
        .\read_reg_axi_fb_DelayCycles_reg[9]_1 (\read_reg_axi_fb_DelayCycles_reg[9] ),
        .read_reg_axi_fb_InverseBotSwitch(read_reg_axi_fb_InverseBotSwitch),
        .read_reg_axi_fb_enable(read_reg_axi_fb_enable),
        .read_reg_axi_fb_enable_reg_0(read_reg_axi_fb_enable_reg),
        .read_reg_ip_timestamp(read_reg_ip_timestamp),
        .reset_x(reset_x));
  zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_axi4_module u_uz_interlockDeadtime2L_axi4_module_inst
       (.AXI4_ACLK(AXI4_ACLK),
        .AXI4_ARADDR(AXI4_ARADDR),
        .AXI4_ARBURST(AXI4_ARBURST),
        .AXI4_ARESETN(AXI4_ARESETN),
        .AXI4_ARID(AXI4_ARID),
        .AXI4_ARLEN(AXI4_ARLEN),
        .AXI4_ARREADY(AXI4_ARREADY),
        .AXI4_ARVALID(AXI4_ARVALID),
        .AXI4_AWADDR(AXI4_AWADDR),
        .AXI4_AWBURST(AXI4_AWBURST),
        .AXI4_AWID(AXI4_AWID),
        .AXI4_AWREADY(AXI4_AWREADY),
        .AXI4_AWVALID(AXI4_AWVALID),
        .AXI4_BID(AXI4_BID),
        .AXI4_BREADY(AXI4_BREADY),
        .AXI4_RDATA(AXI4_RDATA),
        .AXI4_RID(AXI4_RID),
        .AXI4_RLAST(AXI4_RLAST),
        .AXI4_RREADY(AXI4_RREADY),
        .AXI4_WDATA(AXI4_WDATA),
        .AXI4_WLAST(AXI4_WLAST),
        .AXI4_WSTRB(AXI4_WSTRB),
        .AXI4_WVALID(AXI4_WVALID),
        .IPCORE_RESETN(IPCORE_RESETN),
        .Q(Q),
        .\axi4_raddr_reg[2]_0 (reg_enb_axi_DelayCycles_1_1),
        .axi_EnableOutput(axi_EnableOutput),
        .axi_InverseBotSwitch(axi_InverseBotSwitch),
        .\data_int_reg[1] (read_reg_axi_fb_DelayCycles),
        .out_valid_reg(out_valid_reg),
        .read_reg_axi_fb_InverseBotSwitch(read_reg_axi_fb_InverseBotSwitch),
        .read_reg_axi_fb_enable(read_reg_axi_fb_enable),
        .read_reg_ip_timestamp(read_reg_ip_timestamp),
        .reset_in(reset_in),
        .soft_reset(soft_reset),
        .\wdata_reg[0]_0 (u_uz_interlockDeadtime2L_axi4_module_inst_n_19),
        .\wdata_reg[0]_1 (u_uz_interlockDeadtime2L_axi4_module_inst_n_20),
        .\wdata_reg[0]_2 (u_uz_interlockDeadtime2L_axi4_module_inst_n_21),
        .\wdata_reg[9]_0 ({u_uz_interlockDeadtime2L_axi4_module_inst_n_9,u_uz_interlockDeadtime2L_axi4_module_inst_n_10,u_uz_interlockDeadtime2L_axi4_module_inst_n_11,u_uz_interlockDeadtime2L_axi4_module_inst_n_12,u_uz_interlockDeadtime2L_axi4_module_inst_n_13,u_uz_interlockDeadtime2L_axi4_module_inst_n_14,u_uz_interlockDeadtime2L_axi4_module_inst_n_15,u_uz_interlockDeadtime2L_axi4_module_inst_n_16,u_uz_interlockDeadtime2L_axi4_module_inst_n_17,u_uz_interlockDeadtime2L_axi4_module_inst_n_18}),
        .write_axi_enable(write_axi_enable));
endmodule

(* ORIG_REF_NAME = "uz_interlockDeadtime2L_axi4_module" *) 
module zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_axi4_module
   (out_valid_reg,
    AXI4_RLAST,
    soft_reset,
    Q,
    \axi4_raddr_reg[2]_0 ,
    AXI4_ARREADY,
    AXI4_AWREADY,
    reset_in,
    \wdata_reg[9]_0 ,
    \wdata_reg[0]_0 ,
    \wdata_reg[0]_1 ,
    \wdata_reg[0]_2 ,
    AXI4_RDATA,
    AXI4_RID,
    AXI4_BID,
    AXI4_WSTRB,
    AXI4_ACLK,
    AXI4_ARADDR,
    AXI4_AWADDR,
    \data_int_reg[1] ,
    read_reg_axi_fb_enable,
    read_reg_axi_fb_InverseBotSwitch,
    read_reg_ip_timestamp,
    AXI4_RREADY,
    AXI4_ARESETN,
    AXI4_AWVALID,
    AXI4_BREADY,
    AXI4_ARVALID,
    AXI4_WVALID,
    AXI4_WLAST,
    IPCORE_RESETN,
    AXI4_ARLEN,
    AXI4_ARBURST,
    AXI4_AWBURST,
    write_axi_enable,
    axi_EnableOutput,
    axi_InverseBotSwitch,
    AXI4_WDATA,
    AXI4_ARID,
    AXI4_AWID);
  output out_valid_reg;
  output AXI4_RLAST;
  output soft_reset;
  output [1:0]Q;
  output [0:0]\axi4_raddr_reg[2]_0 ;
  output AXI4_ARREADY;
  output AXI4_AWREADY;
  output reset_in;
  output [9:0]\wdata_reg[9]_0 ;
  output \wdata_reg[0]_0 ;
  output \wdata_reg[0]_1 ;
  output \wdata_reg[0]_2 ;
  output [31:0]AXI4_RDATA;
  output [11:0]AXI4_RID;
  output [11:0]AXI4_BID;
  input [3:0]AXI4_WSTRB;
  input AXI4_ACLK;
  input [13:0]AXI4_ARADDR;
  input [13:0]AXI4_AWADDR;
  input [9:0]\data_int_reg[1] ;
  input read_reg_axi_fb_enable;
  input read_reg_axi_fb_InverseBotSwitch;
  input [0:0]read_reg_ip_timestamp;
  input AXI4_RREADY;
  input AXI4_ARESETN;
  input AXI4_AWVALID;
  input AXI4_BREADY;
  input AXI4_ARVALID;
  input AXI4_WVALID;
  input AXI4_WLAST;
  input IPCORE_RESETN;
  input [7:0]AXI4_ARLEN;
  input [1:0]AXI4_ARBURST;
  input [1:0]AXI4_AWBURST;
  input write_axi_enable;
  input axi_EnableOutput;
  input axi_InverseBotSwitch;
  input [9:0]AXI4_WDATA;
  input [11:0]AXI4_ARID;
  input [11:0]AXI4_AWID;

  wire AXI4_ACLK;
  wire [13:0]AXI4_ARADDR;
  wire [1:0]AXI4_ARBURST;
  wire AXI4_ARESETN;
  wire [11:0]AXI4_ARID;
  wire [7:0]AXI4_ARLEN;
  wire AXI4_ARREADY;
  wire AXI4_ARVALID;
  wire [13:0]AXI4_AWADDR;
  wire [1:0]AXI4_AWBURST;
  wire [11:0]AXI4_AWID;
  wire AXI4_AWREADY;
  wire AXI4_AWVALID;
  wire [11:0]AXI4_BID;
  wire AXI4_BREADY;
  wire [31:0]AXI4_RDATA;
  wire [11:0]AXI4_RID;
  wire AXI4_RLAST;
  wire AXI4_RREADY;
  wire [9:0]AXI4_WDATA;
  wire AXI4_WLAST;
  wire [3:0]AXI4_WSTRB;
  wire AXI4_WVALID;
  wire IPCORE_RESETN;
  wire [1:0]Q;
  wire axi4_awtransfer;
  wire axi4_awtransfer_next;
  wire \axi4_raddr[10]_i_1_n_0 ;
  wire \axi4_raddr[11]_i_1_n_0 ;
  wire \axi4_raddr[12]_i_1_n_0 ;
  wire \axi4_raddr[13]_i_1_n_0 ;
  wire \axi4_raddr[14]_i_1_n_0 ;
  wire \axi4_raddr[15]_i_1_n_0 ;
  wire \axi4_raddr[15]_i_2_n_0 ;
  wire \axi4_raddr[2]_i_1_n_0 ;
  wire \axi4_raddr[3]_i_1_n_0 ;
  wire \axi4_raddr[4]_i_1_n_0 ;
  wire \axi4_raddr[5]_i_1_n_0 ;
  wire \axi4_raddr[6]_i_1_n_0 ;
  wire \axi4_raddr[7]_i_1_n_0 ;
  wire \axi4_raddr[8]_i_1_n_0 ;
  wire \axi4_raddr[9]_i_1_n_0 ;
  wire [2:2]axi4_raddr_inc;
  wire \axi4_raddr_inc[2]_i_1_n_0 ;
  wire axi4_raddr_inc_next;
  wire \axi4_raddr_reg[15]_i_3_n_3 ;
  wire \axi4_raddr_reg[15]_i_3_n_4 ;
  wire \axi4_raddr_reg[15]_i_3_n_5 ;
  wire \axi4_raddr_reg[15]_i_3_n_6 ;
  wire \axi4_raddr_reg[15]_i_3_n_7 ;
  wire [0:0]\axi4_raddr_reg[2]_0 ;
  wire \axi4_raddr_reg[9]_i_2_n_0 ;
  wire \axi4_raddr_reg[9]_i_2_n_1 ;
  wire \axi4_raddr_reg[9]_i_2_n_2 ;
  wire \axi4_raddr_reg[9]_i_2_n_3 ;
  wire \axi4_raddr_reg[9]_i_2_n_4 ;
  wire \axi4_raddr_reg[9]_i_2_n_5 ;
  wire \axi4_raddr_reg[9]_i_2_n_6 ;
  wire \axi4_raddr_reg[9]_i_2_n_7 ;
  wire axi4_rd_active_i_1_n_0;
  wire axi4_rd_active_next;
  wire [11:0]axi4_rid_1;
  wire axi4_rlast_1;
  wire axi4_rlast_1_i_2_n_0;
  wire [7:0]axi4_rlen;
  wire \axi4_rlen[0]_i_1_n_0 ;
  wire \axi4_rlen[1]_i_1_n_0 ;
  wire \axi4_rlen[2]_i_1_n_0 ;
  wire \axi4_rlen[3]_i_1_n_0 ;
  wire \axi4_rlen[3]_i_2_n_0 ;
  wire \axi4_rlen[4]_i_1_n_0 ;
  wire \axi4_rlen[4]_i_2_n_0 ;
  wire \axi4_rlen[5]_i_1_n_0 ;
  wire \axi4_rlen[5]_i_2_n_0 ;
  wire \axi4_rlen[6]_i_1_n_0 ;
  wire \axi4_rlen[7]_i_2_n_0 ;
  wire \axi4_rlen[7]_i_3_n_0 ;
  wire [2:1]axi4_rstate;
  wire [2:0]axi4_rstate_next;
  wire [15:2]axi4_waddr;
  wire \axi4_waddr[10]_i_1_n_0 ;
  wire \axi4_waddr[11]_i_1_n_0 ;
  wire \axi4_waddr[12]_i_1_n_0 ;
  wire \axi4_waddr[13]_i_1_n_0 ;
  wire \axi4_waddr[14]_i_1_n_0 ;
  wire \axi4_waddr[15]_i_1_n_0 ;
  wire \axi4_waddr[15]_i_2_n_0 ;
  wire \axi4_waddr[2]_i_1_n_0 ;
  wire \axi4_waddr[3]_i_1_n_0 ;
  wire \axi4_waddr[4]_i_1_n_0 ;
  wire \axi4_waddr[5]_i_1_n_0 ;
  wire \axi4_waddr[6]_i_1_n_0 ;
  wire \axi4_waddr[7]_i_1_n_0 ;
  wire \axi4_waddr[8]_i_1_n_0 ;
  wire \axi4_waddr[9]_i_1_n_0 ;
  wire [2:2]axi4_waddr_inc;
  wire \axi4_waddr_inc[2]_i_1_n_0 ;
  wire \axi4_waddr_reg[15]_i_3_n_3 ;
  wire \axi4_waddr_reg[15]_i_3_n_4 ;
  wire \axi4_waddr_reg[15]_i_3_n_5 ;
  wire \axi4_waddr_reg[15]_i_3_n_6 ;
  wire \axi4_waddr_reg[15]_i_3_n_7 ;
  wire \axi4_waddr_reg[9]_i_2_n_0 ;
  wire \axi4_waddr_reg[9]_i_2_n_1 ;
  wire \axi4_waddr_reg[9]_i_2_n_2 ;
  wire \axi4_waddr_reg[9]_i_2_n_3 ;
  wire \axi4_waddr_reg[9]_i_2_n_4 ;
  wire \axi4_waddr_reg[9]_i_2_n_5 ;
  wire \axi4_waddr_reg[9]_i_2_n_6 ;
  wire \axi4_waddr_reg[9]_i_2_n_7 ;
  wire axi4_wid_next;
  wire [2:0]axi4_wstate_next;
  wire axi4_wtransfer;
  wire axi4_wtransfer_i_1_n_0;
  wire axi4_wtransfer_next;
  wire axi_EnableOutput;
  wire axi_InverseBotSwitch;
  wire [9:0]\data_int_reg[1] ;
  wire \data_reg_axi_DelayCycles_1_1[9]_i_2_n_0 ;
  wire \data_reg_axi_DelayCycles_1_1[9]_i_4_n_0 ;
  wire \data_reg_axi_DelayCycles_1_1[9]_i_5_n_0 ;
  wire \data_reg_axi_DelayCycles_1_1[9]_i_6_n_0 ;
  wire data_reg_axi_EnableOutput_1_1_i_2_n_0;
  wire data_reg_axi_EnableOutput_1_1_i_3_n_0;
  wire data_reg_axi_EnableOutput_1_1_i_4_n_0;
  wire data_reg_axi_InverseBotSwitch_1_1_i_2_n_0;
  wire data_reg_axi_InverseBotSwitch_1_1_i_3_n_0;
  wire data_reg_axi_enable_1_1_i_2_n_0;
  wire data_reg_axi_enable_1_1_i_3_n_0;
  wire data_reg_axi_enable_1_1_i_4_n_0;
  wire data_reg_axi_enable_1_1_i_5_n_0;
  wire [15:2]in7;
  wire [15:2]in8;
  wire out_valid_reg;
  wire [15:2]raddr_r;
  wire rd_active;
  wire read_reg_axi_fb_InverseBotSwitch;
  wire read_reg_axi_fb_enable;
  wire [0:0]read_reg_ip_timestamp;
  wire reset_in;
  wire reset_x;
  wire [13:0]sel0;
  wire soft_reset;
  wire soft_reset_i_1_n_0;
  wire soft_reset_i_4_n_0;
  wire top_rd_enb;
  wire top_wr_enb;
  wire u_uz_interlockDeadtime2L_rdfifo_data_inst_n_10;
  wire u_uz_interlockDeadtime2L_rdfifo_data_inst_n_11;
  wire u_uz_interlockDeadtime2L_rdfifo_data_inst_n_2;
  wire u_uz_interlockDeadtime2L_rdfifo_data_inst_n_3;
  wire u_uz_interlockDeadtime2L_rdfifo_data_inst_n_4;
  wire u_uz_interlockDeadtime2L_rdfifo_data_inst_n_5;
  wire u_uz_interlockDeadtime2L_rdfifo_data_inst_n_6;
  wire u_uz_interlockDeadtime2L_rdfifo_data_inst_n_9;
  wire w_transfer_and_wstrb;
  wire [15:2]waddr_r;
  wire [9:0]wdata_int;
  wire \wdata_reg[0]_0 ;
  wire \wdata_reg[0]_1 ;
  wire \wdata_reg[0]_2 ;
  wire [9:0]\wdata_reg[9]_0 ;
  wire write_axi_enable;
  wire wstrb_reduce__0;
  wire wstrb_reduce_reg;
  wire [7:5]\NLW_axi4_raddr_reg[15]_i_3_CO_UNCONNECTED ;
  wire [7:6]\NLW_axi4_raddr_reg[15]_i_3_O_UNCONNECTED ;
  wire [0:0]\NLW_axi4_raddr_reg[9]_i_2_O_UNCONNECTED ;
  wire [7:5]\NLW_axi4_waddr_reg[15]_i_3_CO_UNCONNECTED ;
  wire [7:6]\NLW_axi4_waddr_reg[15]_i_3_O_UNCONNECTED ;
  wire [0:0]\NLW_axi4_waddr_reg[9]_i_2_O_UNCONNECTED ;

  (* SOFT_HLUTNM = "soft_lutpair81" *) 
  LUT3 #(
    .INIT(8'h08)) 
    AXI4_ARREADY_INST_0
       (.I0(axi4_raddr_inc_next),
        .I1(axi4_wid_next),
        .I2(AXI4_AWVALID),
        .O(AXI4_ARREADY));
  (* SOFT_HLUTNM = "soft_lutpair82" *) 
  LUT2 #(
    .INIT(4'h8)) 
    AXI4_AWREADY_INST_0
       (.I0(axi4_wid_next),
        .I1(axi4_raddr_inc_next),
        .O(AXI4_AWREADY));
  LUT6 #(
    .INIT(64'h44F4444444444444)) 
    \FSM_onehot_axi4_rstate[1]_i_1 
       (.I0(axi4_rlast_1),
        .I1(axi4_rstate[1]),
        .I2(axi4_wid_next),
        .I3(AXI4_AWVALID),
        .I4(AXI4_ARVALID),
        .I5(axi4_raddr_inc_next),
        .O(axi4_rstate_next[1]));
  (* FSM_ENCODED_STATES = "iSTATE:010,iSTATE0:100,iSTATE1:001" *) 
  FDSE #(
    .INIT(1'b1)) 
    \FSM_onehot_axi4_rstate_reg[0] 
       (.C(AXI4_ACLK),
        .CE(1'b1),
        .D(axi4_rstate_next[0]),
        .Q(axi4_raddr_inc_next),
        .S(reset_x));
  (* FSM_ENCODED_STATES = "iSTATE:010,iSTATE0:100,iSTATE1:001" *) 
  FDRE #(
    .INIT(1'b0)) 
    \FSM_onehot_axi4_rstate_reg[1] 
       (.C(AXI4_ACLK),
        .CE(1'b1),
        .D(axi4_rstate_next[1]),
        .Q(axi4_rstate[1]),
        .R(reset_x));
  (* FSM_ENCODED_STATES = "iSTATE:010,iSTATE0:100,iSTATE1:001" *) 
  FDRE #(
    .INIT(1'b0)) 
    \FSM_onehot_axi4_rstate_reg[2] 
       (.C(AXI4_ACLK),
        .CE(1'b1),
        .D(axi4_rstate_next[2]),
        .Q(axi4_rstate[2]),
        .R(reset_x));
  (* SOFT_HLUTNM = "soft_lutpair81" *) 
  LUT5 #(
    .INIT(32'hD5FFC0C0)) 
    \FSM_onehot_axi4_wstate[0]_i_1 
       (.I0(AXI4_AWVALID),
        .I1(AXI4_BREADY),
        .I2(Q[1]),
        .I3(axi4_raddr_inc_next),
        .I4(axi4_wid_next),
        .O(axi4_wstate_next[0]));
  LUT6 #(
    .INIT(64'h80FFFFFF80808080)) 
    \FSM_onehot_axi4_wstate[1]_i_2 
       (.I0(AXI4_AWVALID),
        .I1(axi4_wid_next),
        .I2(axi4_raddr_inc_next),
        .I3(AXI4_WVALID),
        .I4(AXI4_WLAST),
        .I5(Q[0]),
        .O(axi4_wstate_next[1]));
  LUT5 #(
    .INIT(32'h80FF8080)) 
    \FSM_onehot_axi4_wstate[2]_i_1 
       (.I0(AXI4_WLAST),
        .I1(AXI4_WVALID),
        .I2(Q[0]),
        .I3(AXI4_BREADY),
        .I4(Q[1]),
        .O(axi4_wstate_next[2]));
  (* FSM_ENCODED_STATES = "iSTATE:010,iSTATE0:100,iSTATE1:001" *) 
  FDSE #(
    .INIT(1'b1)) 
    \FSM_onehot_axi4_wstate_reg[0] 
       (.C(AXI4_ACLK),
        .CE(1'b1),
        .D(axi4_wstate_next[0]),
        .Q(axi4_wid_next),
        .S(reset_x));
  (* FSM_ENCODED_STATES = "iSTATE:010,iSTATE0:100,iSTATE1:001" *) 
  FDRE #(
    .INIT(1'b0)) 
    \FSM_onehot_axi4_wstate_reg[1] 
       (.C(AXI4_ACLK),
        .CE(1'b1),
        .D(axi4_wstate_next[1]),
        .Q(Q[0]),
        .R(reset_x));
  (* FSM_ENCODED_STATES = "iSTATE:010,iSTATE0:100,iSTATE1:001" *) 
  FDRE #(
    .INIT(1'b0)) 
    \FSM_onehot_axi4_wstate_reg[2] 
       (.C(AXI4_ACLK),
        .CE(1'b1),
        .D(axi4_wstate_next[2]),
        .Q(Q[1]),
        .R(reset_x));
  FDRE axi4_ar_transfer_reg
       (.C(AXI4_ACLK),
        .CE(1'b1),
        .D(u_uz_interlockDeadtime2L_rdfifo_data_inst_n_11),
        .Q(top_rd_enb),
        .R(reset_x));
  (* SOFT_HLUTNM = "soft_lutpair82" *) 
  LUT5 #(
    .INIT(32'hFF808080)) 
    axi4_awtransfer_i_1
       (.I0(axi4_raddr_inc_next),
        .I1(axi4_wid_next),
        .I2(AXI4_AWVALID),
        .I3(Q[0]),
        .I4(AXI4_WVALID),
        .O(axi4_awtransfer_next));
  FDRE axi4_awtransfer_reg
       (.C(AXI4_ACLK),
        .CE(axi4_wtransfer_i_1_n_0),
        .D(axi4_awtransfer_next),
        .Q(axi4_awtransfer),
        .R(reset_x));
  LUT4 #(
    .INIT(16'hF888)) 
    \axi4_raddr[10]_i_1 
       (.I0(axi4_raddr_inc_next),
        .I1(AXI4_ARADDR[8]),
        .I2(axi4_rstate[1]),
        .I3(in8[10]),
        .O(\axi4_raddr[10]_i_1_n_0 ));
  LUT4 #(
    .INIT(16'hF888)) 
    \axi4_raddr[11]_i_1 
       (.I0(axi4_raddr_inc_next),
        .I1(AXI4_ARADDR[9]),
        .I2(axi4_rstate[1]),
        .I3(in8[11]),
        .O(\axi4_raddr[11]_i_1_n_0 ));
  LUT4 #(
    .INIT(16'hF888)) 
    \axi4_raddr[12]_i_1 
       (.I0(axi4_raddr_inc_next),
        .I1(AXI4_ARADDR[10]),
        .I2(axi4_rstate[1]),
        .I3(in8[12]),
        .O(\axi4_raddr[12]_i_1_n_0 ));
  LUT4 #(
    .INIT(16'hF888)) 
    \axi4_raddr[13]_i_1 
       (.I0(axi4_raddr_inc_next),
        .I1(AXI4_ARADDR[11]),
        .I2(axi4_rstate[1]),
        .I3(in8[13]),
        .O(\axi4_raddr[13]_i_1_n_0 ));
  LUT4 #(
    .INIT(16'hF888)) 
    \axi4_raddr[14]_i_1 
       (.I0(axi4_raddr_inc_next),
        .I1(AXI4_ARADDR[12]),
        .I2(axi4_rstate[1]),
        .I3(in8[14]),
        .O(\axi4_raddr[14]_i_1_n_0 ));
  LUT3 #(
    .INIT(8'hF8)) 
    \axi4_raddr[15]_i_1 
       (.I0(axi4_rstate[1]),
        .I1(top_rd_enb),
        .I2(axi4_raddr_inc_next),
        .O(\axi4_raddr[15]_i_1_n_0 ));
  LUT4 #(
    .INIT(16'hF888)) 
    \axi4_raddr[15]_i_2 
       (.I0(axi4_raddr_inc_next),
        .I1(AXI4_ARADDR[13]),
        .I2(axi4_rstate[1]),
        .I3(in8[15]),
        .O(\axi4_raddr[15]_i_2_n_0 ));
  LUT5 #(
    .INIT(32'h88F8F888)) 
    \axi4_raddr[2]_i_1 
       (.I0(axi4_raddr_inc_next),
        .I1(AXI4_ARADDR[0]),
        .I2(axi4_rstate[1]),
        .I3(raddr_r[2]),
        .I4(axi4_raddr_inc),
        .O(\axi4_raddr[2]_i_1_n_0 ));
  LUT4 #(
    .INIT(16'hF888)) 
    \axi4_raddr[3]_i_1 
       (.I0(axi4_raddr_inc_next),
        .I1(AXI4_ARADDR[1]),
        .I2(axi4_rstate[1]),
        .I3(in8[3]),
        .O(\axi4_raddr[3]_i_1_n_0 ));
  LUT4 #(
    .INIT(16'hF888)) 
    \axi4_raddr[4]_i_1 
       (.I0(axi4_raddr_inc_next),
        .I1(AXI4_ARADDR[2]),
        .I2(axi4_rstate[1]),
        .I3(in8[4]),
        .O(\axi4_raddr[4]_i_1_n_0 ));
  LUT4 #(
    .INIT(16'hF888)) 
    \axi4_raddr[5]_i_1 
       (.I0(axi4_raddr_inc_next),
        .I1(AXI4_ARADDR[3]),
        .I2(axi4_rstate[1]),
        .I3(in8[5]),
        .O(\axi4_raddr[5]_i_1_n_0 ));
  LUT4 #(
    .INIT(16'hF888)) 
    \axi4_raddr[6]_i_1 
       (.I0(axi4_raddr_inc_next),
        .I1(AXI4_ARADDR[4]),
        .I2(axi4_rstate[1]),
        .I3(in8[6]),
        .O(\axi4_raddr[6]_i_1_n_0 ));
  LUT4 #(
    .INIT(16'hF888)) 
    \axi4_raddr[7]_i_1 
       (.I0(axi4_raddr_inc_next),
        .I1(AXI4_ARADDR[5]),
        .I2(axi4_rstate[1]),
        .I3(in8[7]),
        .O(\axi4_raddr[7]_i_1_n_0 ));
  LUT4 #(
    .INIT(16'hF888)) 
    \axi4_raddr[8]_i_1 
       (.I0(axi4_raddr_inc_next),
        .I1(AXI4_ARADDR[6]),
        .I2(axi4_rstate[1]),
        .I3(in8[8]),
        .O(\axi4_raddr[8]_i_1_n_0 ));
  LUT4 #(
    .INIT(16'hF888)) 
    \axi4_raddr[9]_i_1 
       (.I0(axi4_raddr_inc_next),
        .I1(AXI4_ARADDR[7]),
        .I2(axi4_rstate[1]),
        .I3(in8[9]),
        .O(\axi4_raddr[9]_i_1_n_0 ));
  LUT2 #(
    .INIT(4'h6)) 
    \axi4_raddr[9]_i_3 
       (.I0(raddr_r[2]),
        .I1(axi4_raddr_inc),
        .O(in8[2]));
  LUT4 #(
    .INIT(16'hEFE0)) 
    \axi4_raddr_inc[2]_i_1 
       (.I0(AXI4_ARBURST[0]),
        .I1(AXI4_ARBURST[1]),
        .I2(axi4_raddr_inc_next),
        .I3(axi4_raddr_inc),
        .O(\axi4_raddr_inc[2]_i_1_n_0 ));
  FDRE \axi4_raddr_inc_reg[2] 
       (.C(AXI4_ACLK),
        .CE(1'b1),
        .D(\axi4_raddr_inc[2]_i_1_n_0 ),
        .Q(axi4_raddr_inc),
        .R(reset_x));
  FDRE \axi4_raddr_reg[10] 
       (.C(AXI4_ACLK),
        .CE(\axi4_raddr[15]_i_1_n_0 ),
        .D(\axi4_raddr[10]_i_1_n_0 ),
        .Q(raddr_r[10]),
        .R(reset_x));
  FDRE \axi4_raddr_reg[11] 
       (.C(AXI4_ACLK),
        .CE(\axi4_raddr[15]_i_1_n_0 ),
        .D(\axi4_raddr[11]_i_1_n_0 ),
        .Q(raddr_r[11]),
        .R(reset_x));
  FDRE \axi4_raddr_reg[12] 
       (.C(AXI4_ACLK),
        .CE(\axi4_raddr[15]_i_1_n_0 ),
        .D(\axi4_raddr[12]_i_1_n_0 ),
        .Q(raddr_r[12]),
        .R(reset_x));
  FDRE \axi4_raddr_reg[13] 
       (.C(AXI4_ACLK),
        .CE(\axi4_raddr[15]_i_1_n_0 ),
        .D(\axi4_raddr[13]_i_1_n_0 ),
        .Q(raddr_r[13]),
        .R(reset_x));
  FDRE \axi4_raddr_reg[14] 
       (.C(AXI4_ACLK),
        .CE(\axi4_raddr[15]_i_1_n_0 ),
        .D(\axi4_raddr[14]_i_1_n_0 ),
        .Q(raddr_r[14]),
        .R(reset_x));
  FDRE \axi4_raddr_reg[15] 
       (.C(AXI4_ACLK),
        .CE(\axi4_raddr[15]_i_1_n_0 ),
        .D(\axi4_raddr[15]_i_2_n_0 ),
        .Q(raddr_r[15]),
        .R(reset_x));
  (* ADDER_THRESHOLD = "35" *) 
  CARRY8 \axi4_raddr_reg[15]_i_3 
       (.CI(\axi4_raddr_reg[9]_i_2_n_0 ),
        .CI_TOP(1'b0),
        .CO({\NLW_axi4_raddr_reg[15]_i_3_CO_UNCONNECTED [7:5],\axi4_raddr_reg[15]_i_3_n_3 ,\axi4_raddr_reg[15]_i_3_n_4 ,\axi4_raddr_reg[15]_i_3_n_5 ,\axi4_raddr_reg[15]_i_3_n_6 ,\axi4_raddr_reg[15]_i_3_n_7 }),
        .DI({1'b0,1'b0,1'b0,raddr_r[14:10]}),
        .O({\NLW_axi4_raddr_reg[15]_i_3_O_UNCONNECTED [7:6],in8[15:10]}),
        .S({1'b0,1'b0,raddr_r[15:10]}));
  FDRE \axi4_raddr_reg[2] 
       (.C(AXI4_ACLK),
        .CE(\axi4_raddr[15]_i_1_n_0 ),
        .D(\axi4_raddr[2]_i_1_n_0 ),
        .Q(raddr_r[2]),
        .R(reset_x));
  FDRE \axi4_raddr_reg[3] 
       (.C(AXI4_ACLK),
        .CE(\axi4_raddr[15]_i_1_n_0 ),
        .D(\axi4_raddr[3]_i_1_n_0 ),
        .Q(raddr_r[3]),
        .R(reset_x));
  FDRE \axi4_raddr_reg[4] 
       (.C(AXI4_ACLK),
        .CE(\axi4_raddr[15]_i_1_n_0 ),
        .D(\axi4_raddr[4]_i_1_n_0 ),
        .Q(raddr_r[4]),
        .R(reset_x));
  FDRE \axi4_raddr_reg[5] 
       (.C(AXI4_ACLK),
        .CE(\axi4_raddr[15]_i_1_n_0 ),
        .D(\axi4_raddr[5]_i_1_n_0 ),
        .Q(raddr_r[5]),
        .R(reset_x));
  FDRE \axi4_raddr_reg[6] 
       (.C(AXI4_ACLK),
        .CE(\axi4_raddr[15]_i_1_n_0 ),
        .D(\axi4_raddr[6]_i_1_n_0 ),
        .Q(raddr_r[6]),
        .R(reset_x));
  FDRE \axi4_raddr_reg[7] 
       (.C(AXI4_ACLK),
        .CE(\axi4_raddr[15]_i_1_n_0 ),
        .D(\axi4_raddr[7]_i_1_n_0 ),
        .Q(raddr_r[7]),
        .R(reset_x));
  FDRE \axi4_raddr_reg[8] 
       (.C(AXI4_ACLK),
        .CE(\axi4_raddr[15]_i_1_n_0 ),
        .D(\axi4_raddr[8]_i_1_n_0 ),
        .Q(raddr_r[8]),
        .R(reset_x));
  FDRE \axi4_raddr_reg[9] 
       (.C(AXI4_ACLK),
        .CE(\axi4_raddr[15]_i_1_n_0 ),
        .D(\axi4_raddr[9]_i_1_n_0 ),
        .Q(raddr_r[9]),
        .R(reset_x));
  (* ADDER_THRESHOLD = "35" *) 
  CARRY8 \axi4_raddr_reg[9]_i_2 
       (.CI(1'b0),
        .CI_TOP(1'b0),
        .CO({\axi4_raddr_reg[9]_i_2_n_0 ,\axi4_raddr_reg[9]_i_2_n_1 ,\axi4_raddr_reg[9]_i_2_n_2 ,\axi4_raddr_reg[9]_i_2_n_3 ,\axi4_raddr_reg[9]_i_2_n_4 ,\axi4_raddr_reg[9]_i_2_n_5 ,\axi4_raddr_reg[9]_i_2_n_6 ,\axi4_raddr_reg[9]_i_2_n_7 }),
        .DI(raddr_r[9:2]),
        .O({in8[9:3],\NLW_axi4_raddr_reg[9]_i_2_O_UNCONNECTED [0]}),
        .S({raddr_r[9:3],in8[2]}));
  LUT6 #(
    .INIT(64'h202000FF20200000)) 
    axi4_rd_active_i_1
       (.I0(AXI4_ARVALID),
        .I1(AXI4_AWVALID),
        .I2(axi4_wid_next),
        .I3(axi4_rstate[2]),
        .I4(axi4_raddr_inc_next),
        .I5(rd_active),
        .O(axi4_rd_active_i_1_n_0));
  FDRE axi4_rd_active_reg
       (.C(AXI4_ACLK),
        .CE(1'b1),
        .D(axi4_rd_active_i_1_n_0),
        .Q(rd_active),
        .R(reset_x));
  LUT4 #(
    .INIT(16'h0800)) 
    \axi4_rid_1[11]_i_1 
       (.I0(axi4_raddr_inc_next),
        .I1(AXI4_ARVALID),
        .I2(AXI4_AWVALID),
        .I3(axi4_wid_next),
        .O(axi4_rd_active_next));
  FDRE \axi4_rid_1_reg[0] 
       (.C(AXI4_ACLK),
        .CE(axi4_rd_active_next),
        .D(AXI4_ARID[0]),
        .Q(axi4_rid_1[0]),
        .R(reset_x));
  FDRE \axi4_rid_1_reg[10] 
       (.C(AXI4_ACLK),
        .CE(axi4_rd_active_next),
        .D(AXI4_ARID[10]),
        .Q(axi4_rid_1[10]),
        .R(reset_x));
  FDRE \axi4_rid_1_reg[11] 
       (.C(AXI4_ACLK),
        .CE(axi4_rd_active_next),
        .D(AXI4_ARID[11]),
        .Q(axi4_rid_1[11]),
        .R(reset_x));
  FDRE \axi4_rid_1_reg[1] 
       (.C(AXI4_ACLK),
        .CE(axi4_rd_active_next),
        .D(AXI4_ARID[1]),
        .Q(axi4_rid_1[1]),
        .R(reset_x));
  FDRE \axi4_rid_1_reg[2] 
       (.C(AXI4_ACLK),
        .CE(axi4_rd_active_next),
        .D(AXI4_ARID[2]),
        .Q(axi4_rid_1[2]),
        .R(reset_x));
  FDRE \axi4_rid_1_reg[3] 
       (.C(AXI4_ACLK),
        .CE(axi4_rd_active_next),
        .D(AXI4_ARID[3]),
        .Q(axi4_rid_1[3]),
        .R(reset_x));
  FDRE \axi4_rid_1_reg[4] 
       (.C(AXI4_ACLK),
        .CE(axi4_rd_active_next),
        .D(AXI4_ARID[4]),
        .Q(axi4_rid_1[4]),
        .R(reset_x));
  FDRE \axi4_rid_1_reg[5] 
       (.C(AXI4_ACLK),
        .CE(axi4_rd_active_next),
        .D(AXI4_ARID[5]),
        .Q(axi4_rid_1[5]),
        .R(reset_x));
  FDRE \axi4_rid_1_reg[6] 
       (.C(AXI4_ACLK),
        .CE(axi4_rd_active_next),
        .D(AXI4_ARID[6]),
        .Q(axi4_rid_1[6]),
        .R(reset_x));
  FDRE \axi4_rid_1_reg[7] 
       (.C(AXI4_ACLK),
        .CE(axi4_rd_active_next),
        .D(AXI4_ARID[7]),
        .Q(axi4_rid_1[7]),
        .R(reset_x));
  FDRE \axi4_rid_1_reg[8] 
       (.C(AXI4_ACLK),
        .CE(axi4_rd_active_next),
        .D(AXI4_ARID[8]),
        .Q(axi4_rid_1[8]),
        .R(reset_x));
  FDRE \axi4_rid_1_reg[9] 
       (.C(AXI4_ACLK),
        .CE(axi4_rd_active_next),
        .D(AXI4_ARID[9]),
        .Q(axi4_rid_1[9]),
        .R(reset_x));
  LUT4 #(
    .INIT(16'h0100)) 
    axi4_rlast_1_i_2
       (.I0(axi4_rlen[7]),
        .I1(axi4_rlen[6]),
        .I2(axi4_rlast_1),
        .I3(axi4_rstate[1]),
        .O(axi4_rlast_1_i_2_n_0));
  FDRE axi4_rlast_1_reg
       (.C(AXI4_ACLK),
        .CE(1'b1),
        .D(u_uz_interlockDeadtime2L_rdfifo_data_inst_n_10),
        .Q(axi4_rlast_1),
        .R(reset_x));
  LUT4 #(
    .INIT(16'h8F88)) 
    \axi4_rlen[0]_i_1 
       (.I0(axi4_raddr_inc_next),
        .I1(AXI4_ARLEN[0]),
        .I2(axi4_rlen[0]),
        .I3(axi4_rstate[1]),
        .O(\axi4_rlen[0]_i_1_n_0 ));
  LUT5 #(
    .INIT(32'hF88F8888)) 
    \axi4_rlen[1]_i_1 
       (.I0(axi4_raddr_inc_next),
        .I1(AXI4_ARLEN[1]),
        .I2(axi4_rlen[0]),
        .I3(axi4_rlen[1]),
        .I4(axi4_rstate[1]),
        .O(\axi4_rlen[1]_i_1_n_0 ));
  LUT6 #(
    .INIT(64'hFFF8888F88888888)) 
    \axi4_rlen[2]_i_1 
       (.I0(axi4_raddr_inc_next),
        .I1(AXI4_ARLEN[2]),
        .I2(axi4_rlen[1]),
        .I3(axi4_rlen[0]),
        .I4(axi4_rlen[2]),
        .I5(axi4_rstate[1]),
        .O(\axi4_rlen[2]_i_1_n_0 ));
  LUT5 #(
    .INIT(32'hF88F8888)) 
    \axi4_rlen[3]_i_1 
       (.I0(axi4_raddr_inc_next),
        .I1(AXI4_ARLEN[3]),
        .I2(\axi4_rlen[3]_i_2_n_0 ),
        .I3(axi4_rlen[3]),
        .I4(axi4_rstate[1]),
        .O(\axi4_rlen[3]_i_1_n_0 ));
  LUT3 #(
    .INIT(8'hFE)) 
    \axi4_rlen[3]_i_2 
       (.I0(axi4_rlen[1]),
        .I1(axi4_rlen[0]),
        .I2(axi4_rlen[2]),
        .O(\axi4_rlen[3]_i_2_n_0 ));
  LUT5 #(
    .INIT(32'hF88F8888)) 
    \axi4_rlen[4]_i_1 
       (.I0(axi4_raddr_inc_next),
        .I1(AXI4_ARLEN[4]),
        .I2(\axi4_rlen[4]_i_2_n_0 ),
        .I3(axi4_rlen[4]),
        .I4(axi4_rstate[1]),
        .O(\axi4_rlen[4]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair83" *) 
  LUT4 #(
    .INIT(16'hFFFE)) 
    \axi4_rlen[4]_i_2 
       (.I0(axi4_rlen[2]),
        .I1(axi4_rlen[0]),
        .I2(axi4_rlen[1]),
        .I3(axi4_rlen[3]),
        .O(\axi4_rlen[4]_i_2_n_0 ));
  LUT5 #(
    .INIT(32'hF88F8888)) 
    \axi4_rlen[5]_i_1 
       (.I0(axi4_raddr_inc_next),
        .I1(AXI4_ARLEN[5]),
        .I2(\axi4_rlen[5]_i_2_n_0 ),
        .I3(axi4_rlen[5]),
        .I4(axi4_rstate[1]),
        .O(\axi4_rlen[5]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair83" *) 
  LUT5 #(
    .INIT(32'hFFFFFFFE)) 
    \axi4_rlen[5]_i_2 
       (.I0(axi4_rlen[3]),
        .I1(axi4_rlen[1]),
        .I2(axi4_rlen[0]),
        .I3(axi4_rlen[2]),
        .I4(axi4_rlen[4]),
        .O(\axi4_rlen[5]_i_2_n_0 ));
  LUT5 #(
    .INIT(32'hF88F8888)) 
    \axi4_rlen[6]_i_1 
       (.I0(axi4_raddr_inc_next),
        .I1(AXI4_ARLEN[6]),
        .I2(\axi4_rlen[7]_i_3_n_0 ),
        .I3(axi4_rlen[6]),
        .I4(axi4_rstate[1]),
        .O(\axi4_rlen[6]_i_1_n_0 ));
  LUT6 #(
    .INIT(64'hFFF8888F88888888)) 
    \axi4_rlen[7]_i_2 
       (.I0(axi4_raddr_inc_next),
        .I1(AXI4_ARLEN[7]),
        .I2(axi4_rlen[6]),
        .I3(\axi4_rlen[7]_i_3_n_0 ),
        .I4(axi4_rlen[7]),
        .I5(axi4_rstate[1]),
        .O(\axi4_rlen[7]_i_2_n_0 ));
  LUT6 #(
    .INIT(64'hFFFFFFFFFFFFFFFE)) 
    \axi4_rlen[7]_i_3 
       (.I0(axi4_rlen[4]),
        .I1(axi4_rlen[2]),
        .I2(axi4_rlen[0]),
        .I3(axi4_rlen[1]),
        .I4(axi4_rlen[3]),
        .I5(axi4_rlen[5]),
        .O(\axi4_rlen[7]_i_3_n_0 ));
  FDRE \axi4_rlen_reg[0] 
       (.C(AXI4_ACLK),
        .CE(u_uz_interlockDeadtime2L_rdfifo_data_inst_n_9),
        .D(\axi4_rlen[0]_i_1_n_0 ),
        .Q(axi4_rlen[0]),
        .R(reset_x));
  FDRE \axi4_rlen_reg[1] 
       (.C(AXI4_ACLK),
        .CE(u_uz_interlockDeadtime2L_rdfifo_data_inst_n_9),
        .D(\axi4_rlen[1]_i_1_n_0 ),
        .Q(axi4_rlen[1]),
        .R(reset_x));
  FDRE \axi4_rlen_reg[2] 
       (.C(AXI4_ACLK),
        .CE(u_uz_interlockDeadtime2L_rdfifo_data_inst_n_9),
        .D(\axi4_rlen[2]_i_1_n_0 ),
        .Q(axi4_rlen[2]),
        .R(reset_x));
  FDRE \axi4_rlen_reg[3] 
       (.C(AXI4_ACLK),
        .CE(u_uz_interlockDeadtime2L_rdfifo_data_inst_n_9),
        .D(\axi4_rlen[3]_i_1_n_0 ),
        .Q(axi4_rlen[3]),
        .R(reset_x));
  FDRE \axi4_rlen_reg[4] 
       (.C(AXI4_ACLK),
        .CE(u_uz_interlockDeadtime2L_rdfifo_data_inst_n_9),
        .D(\axi4_rlen[4]_i_1_n_0 ),
        .Q(axi4_rlen[4]),
        .R(reset_x));
  FDRE \axi4_rlen_reg[5] 
       (.C(AXI4_ACLK),
        .CE(u_uz_interlockDeadtime2L_rdfifo_data_inst_n_9),
        .D(\axi4_rlen[5]_i_1_n_0 ),
        .Q(axi4_rlen[5]),
        .R(reset_x));
  FDRE \axi4_rlen_reg[6] 
       (.C(AXI4_ACLK),
        .CE(u_uz_interlockDeadtime2L_rdfifo_data_inst_n_9),
        .D(\axi4_rlen[6]_i_1_n_0 ),
        .Q(axi4_rlen[6]),
        .R(reset_x));
  FDRE \axi4_rlen_reg[7] 
       (.C(AXI4_ACLK),
        .CE(u_uz_interlockDeadtime2L_rdfifo_data_inst_n_9),
        .D(\axi4_rlen[7]_i_2_n_0 ),
        .Q(axi4_rlen[7]),
        .R(reset_x));
  LUT4 #(
    .INIT(16'hF888)) 
    \axi4_waddr[10]_i_1 
       (.I0(axi4_wid_next),
        .I1(AXI4_AWADDR[8]),
        .I2(Q[0]),
        .I3(in7[10]),
        .O(\axi4_waddr[10]_i_1_n_0 ));
  LUT4 #(
    .INIT(16'hF888)) 
    \axi4_waddr[11]_i_1 
       (.I0(axi4_wid_next),
        .I1(AXI4_AWADDR[9]),
        .I2(Q[0]),
        .I3(in7[11]),
        .O(\axi4_waddr[11]_i_1_n_0 ));
  LUT4 #(
    .INIT(16'hF888)) 
    \axi4_waddr[12]_i_1 
       (.I0(axi4_wid_next),
        .I1(AXI4_AWADDR[10]),
        .I2(Q[0]),
        .I3(in7[12]),
        .O(\axi4_waddr[12]_i_1_n_0 ));
  LUT4 #(
    .INIT(16'hF888)) 
    \axi4_waddr[13]_i_1 
       (.I0(axi4_wid_next),
        .I1(AXI4_AWADDR[11]),
        .I2(Q[0]),
        .I3(in7[13]),
        .O(\axi4_waddr[13]_i_1_n_0 ));
  LUT4 #(
    .INIT(16'hF888)) 
    \axi4_waddr[14]_i_1 
       (.I0(axi4_wid_next),
        .I1(AXI4_AWADDR[12]),
        .I2(Q[0]),
        .I3(in7[14]),
        .O(\axi4_waddr[14]_i_1_n_0 ));
  LUT3 #(
    .INIT(8'hF8)) 
    \axi4_waddr[15]_i_1 
       (.I0(Q[0]),
        .I1(AXI4_WVALID),
        .I2(axi4_wid_next),
        .O(\axi4_waddr[15]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair84" *) 
  LUT4 #(
    .INIT(16'hF888)) 
    \axi4_waddr[15]_i_2 
       (.I0(axi4_wid_next),
        .I1(AXI4_AWADDR[13]),
        .I2(Q[0]),
        .I3(in7[15]),
        .O(\axi4_waddr[15]_i_2_n_0 ));
  LUT5 #(
    .INIT(32'h88F8F888)) 
    \axi4_waddr[2]_i_1 
       (.I0(axi4_wid_next),
        .I1(AXI4_AWADDR[0]),
        .I2(Q[0]),
        .I3(axi4_waddr[2]),
        .I4(axi4_waddr_inc),
        .O(\axi4_waddr[2]_i_1_n_0 ));
  LUT4 #(
    .INIT(16'hF888)) 
    \axi4_waddr[3]_i_1 
       (.I0(axi4_wid_next),
        .I1(AXI4_AWADDR[1]),
        .I2(Q[0]),
        .I3(in7[3]),
        .O(\axi4_waddr[3]_i_1_n_0 ));
  LUT4 #(
    .INIT(16'hF888)) 
    \axi4_waddr[4]_i_1 
       (.I0(axi4_wid_next),
        .I1(AXI4_AWADDR[2]),
        .I2(Q[0]),
        .I3(in7[4]),
        .O(\axi4_waddr[4]_i_1_n_0 ));
  LUT4 #(
    .INIT(16'hF888)) 
    \axi4_waddr[5]_i_1 
       (.I0(axi4_wid_next),
        .I1(AXI4_AWADDR[3]),
        .I2(Q[0]),
        .I3(in7[5]),
        .O(\axi4_waddr[5]_i_1_n_0 ));
  LUT4 #(
    .INIT(16'hF888)) 
    \axi4_waddr[6]_i_1 
       (.I0(axi4_wid_next),
        .I1(AXI4_AWADDR[4]),
        .I2(Q[0]),
        .I3(in7[6]),
        .O(\axi4_waddr[6]_i_1_n_0 ));
  LUT4 #(
    .INIT(16'hF888)) 
    \axi4_waddr[7]_i_1 
       (.I0(axi4_wid_next),
        .I1(AXI4_AWADDR[5]),
        .I2(Q[0]),
        .I3(in7[7]),
        .O(\axi4_waddr[7]_i_1_n_0 ));
  LUT4 #(
    .INIT(16'hF888)) 
    \axi4_waddr[8]_i_1 
       (.I0(axi4_wid_next),
        .I1(AXI4_AWADDR[6]),
        .I2(Q[0]),
        .I3(in7[8]),
        .O(\axi4_waddr[8]_i_1_n_0 ));
  LUT4 #(
    .INIT(16'hF888)) 
    \axi4_waddr[9]_i_1 
       (.I0(axi4_wid_next),
        .I1(AXI4_AWADDR[7]),
        .I2(Q[0]),
        .I3(in7[9]),
        .O(\axi4_waddr[9]_i_1_n_0 ));
  LUT2 #(
    .INIT(4'h6)) 
    \axi4_waddr[9]_i_3 
       (.I0(axi4_waddr[2]),
        .I1(axi4_waddr_inc),
        .O(in7[2]));
  LUT2 #(
    .INIT(4'hE)) 
    \axi4_waddr_inc[2]_i_1 
       (.I0(AXI4_AWBURST[0]),
        .I1(AXI4_AWBURST[1]),
        .O(\axi4_waddr_inc[2]_i_1_n_0 ));
  FDRE \axi4_waddr_inc_reg[2] 
       (.C(AXI4_ACLK),
        .CE(axi4_wid_next),
        .D(\axi4_waddr_inc[2]_i_1_n_0 ),
        .Q(axi4_waddr_inc),
        .R(reset_x));
  FDRE \axi4_waddr_reg[10] 
       (.C(AXI4_ACLK),
        .CE(\axi4_waddr[15]_i_1_n_0 ),
        .D(\axi4_waddr[10]_i_1_n_0 ),
        .Q(axi4_waddr[10]),
        .R(reset_x));
  FDRE \axi4_waddr_reg[11] 
       (.C(AXI4_ACLK),
        .CE(\axi4_waddr[15]_i_1_n_0 ),
        .D(\axi4_waddr[11]_i_1_n_0 ),
        .Q(axi4_waddr[11]),
        .R(reset_x));
  FDRE \axi4_waddr_reg[12] 
       (.C(AXI4_ACLK),
        .CE(\axi4_waddr[15]_i_1_n_0 ),
        .D(\axi4_waddr[12]_i_1_n_0 ),
        .Q(axi4_waddr[12]),
        .R(reset_x));
  FDRE \axi4_waddr_reg[13] 
       (.C(AXI4_ACLK),
        .CE(\axi4_waddr[15]_i_1_n_0 ),
        .D(\axi4_waddr[13]_i_1_n_0 ),
        .Q(axi4_waddr[13]),
        .R(reset_x));
  FDRE \axi4_waddr_reg[14] 
       (.C(AXI4_ACLK),
        .CE(\axi4_waddr[15]_i_1_n_0 ),
        .D(\axi4_waddr[14]_i_1_n_0 ),
        .Q(axi4_waddr[14]),
        .R(reset_x));
  FDRE \axi4_waddr_reg[15] 
       (.C(AXI4_ACLK),
        .CE(\axi4_waddr[15]_i_1_n_0 ),
        .D(\axi4_waddr[15]_i_2_n_0 ),
        .Q(axi4_waddr[15]),
        .R(reset_x));
  (* ADDER_THRESHOLD = "35" *) 
  CARRY8 \axi4_waddr_reg[15]_i_3 
       (.CI(\axi4_waddr_reg[9]_i_2_n_0 ),
        .CI_TOP(1'b0),
        .CO({\NLW_axi4_waddr_reg[15]_i_3_CO_UNCONNECTED [7:5],\axi4_waddr_reg[15]_i_3_n_3 ,\axi4_waddr_reg[15]_i_3_n_4 ,\axi4_waddr_reg[15]_i_3_n_5 ,\axi4_waddr_reg[15]_i_3_n_6 ,\axi4_waddr_reg[15]_i_3_n_7 }),
        .DI({1'b0,1'b0,1'b0,axi4_waddr[14:10]}),
        .O({\NLW_axi4_waddr_reg[15]_i_3_O_UNCONNECTED [7:6],in7[15:10]}),
        .S({1'b0,1'b0,axi4_waddr[15:10]}));
  FDRE \axi4_waddr_reg[2] 
       (.C(AXI4_ACLK),
        .CE(\axi4_waddr[15]_i_1_n_0 ),
        .D(\axi4_waddr[2]_i_1_n_0 ),
        .Q(axi4_waddr[2]),
        .R(reset_x));
  FDRE \axi4_waddr_reg[3] 
       (.C(AXI4_ACLK),
        .CE(\axi4_waddr[15]_i_1_n_0 ),
        .D(\axi4_waddr[3]_i_1_n_0 ),
        .Q(axi4_waddr[3]),
        .R(reset_x));
  FDRE \axi4_waddr_reg[4] 
       (.C(AXI4_ACLK),
        .CE(\axi4_waddr[15]_i_1_n_0 ),
        .D(\axi4_waddr[4]_i_1_n_0 ),
        .Q(axi4_waddr[4]),
        .R(reset_x));
  FDRE \axi4_waddr_reg[5] 
       (.C(AXI4_ACLK),
        .CE(\axi4_waddr[15]_i_1_n_0 ),
        .D(\axi4_waddr[5]_i_1_n_0 ),
        .Q(axi4_waddr[5]),
        .R(reset_x));
  FDRE \axi4_waddr_reg[6] 
       (.C(AXI4_ACLK),
        .CE(\axi4_waddr[15]_i_1_n_0 ),
        .D(\axi4_waddr[6]_i_1_n_0 ),
        .Q(axi4_waddr[6]),
        .R(reset_x));
  FDRE \axi4_waddr_reg[7] 
       (.C(AXI4_ACLK),
        .CE(\axi4_waddr[15]_i_1_n_0 ),
        .D(\axi4_waddr[7]_i_1_n_0 ),
        .Q(axi4_waddr[7]),
        .R(reset_x));
  FDRE \axi4_waddr_reg[8] 
       (.C(AXI4_ACLK),
        .CE(\axi4_waddr[15]_i_1_n_0 ),
        .D(\axi4_waddr[8]_i_1_n_0 ),
        .Q(axi4_waddr[8]),
        .R(reset_x));
  FDRE \axi4_waddr_reg[9] 
       (.C(AXI4_ACLK),
        .CE(\axi4_waddr[15]_i_1_n_0 ),
        .D(\axi4_waddr[9]_i_1_n_0 ),
        .Q(axi4_waddr[9]),
        .R(reset_x));
  (* ADDER_THRESHOLD = "35" *) 
  CARRY8 \axi4_waddr_reg[9]_i_2 
       (.CI(1'b0),
        .CI_TOP(1'b0),
        .CO({\axi4_waddr_reg[9]_i_2_n_0 ,\axi4_waddr_reg[9]_i_2_n_1 ,\axi4_waddr_reg[9]_i_2_n_2 ,\axi4_waddr_reg[9]_i_2_n_3 ,\axi4_waddr_reg[9]_i_2_n_4 ,\axi4_waddr_reg[9]_i_2_n_5 ,\axi4_waddr_reg[9]_i_2_n_6 ,\axi4_waddr_reg[9]_i_2_n_7 }),
        .DI(axi4_waddr[9:2]),
        .O({in7[9:3],\NLW_axi4_waddr_reg[9]_i_2_O_UNCONNECTED [0]}),
        .S({axi4_waddr[9:3],in7[2]}));
  FDRE \axi4_wid_reg[0] 
       (.C(AXI4_ACLK),
        .CE(axi4_wid_next),
        .D(AXI4_AWID[0]),
        .Q(AXI4_BID[0]),
        .R(reset_x));
  FDRE \axi4_wid_reg[10] 
       (.C(AXI4_ACLK),
        .CE(axi4_wid_next),
        .D(AXI4_AWID[10]),
        .Q(AXI4_BID[10]),
        .R(reset_x));
  FDRE \axi4_wid_reg[11] 
       (.C(AXI4_ACLK),
        .CE(axi4_wid_next),
        .D(AXI4_AWID[11]),
        .Q(AXI4_BID[11]),
        .R(reset_x));
  FDRE \axi4_wid_reg[1] 
       (.C(AXI4_ACLK),
        .CE(axi4_wid_next),
        .D(AXI4_AWID[1]),
        .Q(AXI4_BID[1]),
        .R(reset_x));
  FDRE \axi4_wid_reg[2] 
       (.C(AXI4_ACLK),
        .CE(axi4_wid_next),
        .D(AXI4_AWID[2]),
        .Q(AXI4_BID[2]),
        .R(reset_x));
  FDRE \axi4_wid_reg[3] 
       (.C(AXI4_ACLK),
        .CE(axi4_wid_next),
        .D(AXI4_AWID[3]),
        .Q(AXI4_BID[3]),
        .R(reset_x));
  FDRE \axi4_wid_reg[4] 
       (.C(AXI4_ACLK),
        .CE(axi4_wid_next),
        .D(AXI4_AWID[4]),
        .Q(AXI4_BID[4]),
        .R(reset_x));
  FDRE \axi4_wid_reg[5] 
       (.C(AXI4_ACLK),
        .CE(axi4_wid_next),
        .D(AXI4_AWID[5]),
        .Q(AXI4_BID[5]),
        .R(reset_x));
  FDRE \axi4_wid_reg[6] 
       (.C(AXI4_ACLK),
        .CE(axi4_wid_next),
        .D(AXI4_AWID[6]),
        .Q(AXI4_BID[6]),
        .R(reset_x));
  FDRE \axi4_wid_reg[7] 
       (.C(AXI4_ACLK),
        .CE(axi4_wid_next),
        .D(AXI4_AWID[7]),
        .Q(AXI4_BID[7]),
        .R(reset_x));
  FDRE \axi4_wid_reg[8] 
       (.C(AXI4_ACLK),
        .CE(axi4_wid_next),
        .D(AXI4_AWID[8]),
        .Q(AXI4_BID[8]),
        .R(reset_x));
  FDRE \axi4_wid_reg[9] 
       (.C(AXI4_ACLK),
        .CE(axi4_wid_next),
        .D(AXI4_AWID[9]),
        .Q(AXI4_BID[9]),
        .R(reset_x));
  LUT3 #(
    .INIT(8'hFE)) 
    axi4_wtransfer_i_1
       (.I0(Q[1]),
        .I1(Q[0]),
        .I2(axi4_wid_next),
        .O(axi4_wtransfer_i_1_n_0));
  (* SOFT_HLUTNM = "soft_lutpair84" *) 
  LUT2 #(
    .INIT(4'h8)) 
    axi4_wtransfer_i_2
       (.I0(AXI4_WVALID),
        .I1(Q[0]),
        .O(axi4_wtransfer_next));
  FDRE axi4_wtransfer_reg
       (.C(AXI4_ACLK),
        .CE(axi4_wtransfer_i_1_n_0),
        .D(axi4_wtransfer_next),
        .Q(axi4_wtransfer),
        .R(reset_x));
  LUT6 #(
    .INIT(64'hFFFFFFFF80000000)) 
    \data_reg_axi_DelayCycles_1_1[9]_i_1 
       (.I0(\data_reg_axi_DelayCycles_1_1[9]_i_2_n_0 ),
        .I1(raddr_r[2]),
        .I2(raddr_r[4]),
        .I3(top_wr_enb),
        .I4(u_uz_interlockDeadtime2L_rdfifo_data_inst_n_4),
        .I5(\data_reg_axi_DelayCycles_1_1[9]_i_4_n_0 ),
        .O(\axi4_raddr_reg[2]_0 ));
  LUT5 #(
    .INIT(32'h02000000)) 
    \data_reg_axi_DelayCycles_1_1[9]_i_2 
       (.I0(\data_reg_axi_DelayCycles_1_1[9]_i_5_n_0 ),
        .I1(raddr_r[6]),
        .I2(raddr_r[5]),
        .I3(rd_active),
        .I4(\data_reg_axi_DelayCycles_1_1[9]_i_6_n_0 ),
        .O(\data_reg_axi_DelayCycles_1_1[9]_i_2_n_0 ));
  LUT6 #(
    .INIT(64'h2000000000000000)) 
    \data_reg_axi_DelayCycles_1_1[9]_i_4 
       (.I0(sel0[6]),
        .I1(sel0[1]),
        .I2(top_wr_enb),
        .I3(sel0[2]),
        .I4(sel0[0]),
        .I5(data_reg_axi_EnableOutput_1_1_i_3_n_0),
        .O(\data_reg_axi_DelayCycles_1_1[9]_i_4_n_0 ));
  LUT4 #(
    .INIT(16'h0001)) 
    \data_reg_axi_DelayCycles_1_1[9]_i_5 
       (.I0(raddr_r[11]),
        .I1(raddr_r[10]),
        .I2(raddr_r[9]),
        .I3(raddr_r[7]),
        .O(\data_reg_axi_DelayCycles_1_1[9]_i_5_n_0 ));
  LUT4 #(
    .INIT(16'h0001)) 
    \data_reg_axi_DelayCycles_1_1[9]_i_6 
       (.I0(raddr_r[15]),
        .I1(raddr_r[14]),
        .I2(raddr_r[13]),
        .I3(raddr_r[12]),
        .O(\data_reg_axi_DelayCycles_1_1[9]_i_6_n_0 ));
  LUT6 #(
    .INIT(64'hAABFBFBFAA808080)) 
    data_reg_axi_EnableOutput_1_1_i_1
       (.I0(\wdata_reg[9]_0 [0]),
        .I1(\data_reg_axi_DelayCycles_1_1[9]_i_2_n_0 ),
        .I2(data_reg_axi_EnableOutput_1_1_i_2_n_0),
        .I3(data_reg_axi_EnableOutput_1_1_i_3_n_0),
        .I4(data_reg_axi_EnableOutput_1_1_i_4_n_0),
        .I5(axi_EnableOutput),
        .O(\wdata_reg[0]_1 ));
  (* SOFT_HLUTNM = "soft_lutpair80" *) 
  LUT5 #(
    .INIT(32'h00400000)) 
    data_reg_axi_EnableOutput_1_1_i_2
       (.I0(raddr_r[2]),
        .I1(raddr_r[4]),
        .I2(top_wr_enb),
        .I3(raddr_r[3]),
        .I4(raddr_r[8]),
        .O(data_reg_axi_EnableOutput_1_1_i_2_n_0));
  LUT5 #(
    .INIT(32'h00001000)) 
    data_reg_axi_EnableOutput_1_1_i_3
       (.I0(sel0[3]),
        .I1(sel0[4]),
        .I2(u_uz_interlockDeadtime2L_rdfifo_data_inst_n_6),
        .I3(u_uz_interlockDeadtime2L_rdfifo_data_inst_n_5),
        .I4(rd_active),
        .O(data_reg_axi_EnableOutput_1_1_i_3_n_0));
  (* SOFT_HLUTNM = "soft_lutpair79" *) 
  LUT5 #(
    .INIT(32'h00400000)) 
    data_reg_axi_EnableOutput_1_1_i_4
       (.I0(sel0[0]),
        .I1(sel0[2]),
        .I2(top_wr_enb),
        .I3(sel0[1]),
        .I4(sel0[6]),
        .O(data_reg_axi_EnableOutput_1_1_i_4_n_0));
  LUT6 #(
    .INIT(64'hAABFBFBFAA808080)) 
    data_reg_axi_InverseBotSwitch_1_1_i_1
       (.I0(\wdata_reg[9]_0 [0]),
        .I1(data_reg_axi_enable_1_1_i_2_n_0),
        .I2(data_reg_axi_InverseBotSwitch_1_1_i_2_n_0),
        .I3(data_reg_axi_enable_1_1_i_4_n_0),
        .I4(data_reg_axi_InverseBotSwitch_1_1_i_3_n_0),
        .I5(axi_InverseBotSwitch),
        .O(\wdata_reg[0]_2 ));
  (* SOFT_HLUTNM = "soft_lutpair85" *) 
  LUT3 #(
    .INIT(8'h80)) 
    data_reg_axi_InverseBotSwitch_1_1_i_2
       (.I0(top_wr_enb),
        .I1(raddr_r[8]),
        .I2(raddr_r[3]),
        .O(data_reg_axi_InverseBotSwitch_1_1_i_2_n_0));
  (* SOFT_HLUTNM = "soft_lutpair85" *) 
  LUT3 #(
    .INIT(8'h80)) 
    data_reg_axi_InverseBotSwitch_1_1_i_3
       (.I0(top_wr_enb),
        .I1(sel0[6]),
        .I2(sel0[1]),
        .O(data_reg_axi_InverseBotSwitch_1_1_i_3_n_0));
  LUT6 #(
    .INIT(64'hAABFBFBFAA808080)) 
    data_reg_axi_enable_1_1_i_1
       (.I0(\wdata_reg[9]_0 [0]),
        .I1(data_reg_axi_enable_1_1_i_2_n_0),
        .I2(data_reg_axi_enable_1_1_i_3_n_0),
        .I3(data_reg_axi_enable_1_1_i_4_n_0),
        .I4(data_reg_axi_enable_1_1_i_5_n_0),
        .I5(write_axi_enable),
        .O(\wdata_reg[0]_0 ));
  LUT2 #(
    .INIT(4'h8)) 
    data_reg_axi_enable_1_1_i_2
       (.I0(u_uz_interlockDeadtime2L_rdfifo_data_inst_n_3),
        .I1(raddr_r[2]),
        .O(data_reg_axi_enable_1_1_i_2_n_0));
  (* SOFT_HLUTNM = "soft_lutpair80" *) 
  LUT3 #(
    .INIT(8'h04)) 
    data_reg_axi_enable_1_1_i_3
       (.I0(raddr_r[8]),
        .I1(top_wr_enb),
        .I2(raddr_r[3]),
        .O(data_reg_axi_enable_1_1_i_3_n_0));
  LUT2 #(
    .INIT(4'h8)) 
    data_reg_axi_enable_1_1_i_4
       (.I0(u_uz_interlockDeadtime2L_rdfifo_data_inst_n_2),
        .I1(sel0[0]),
        .O(data_reg_axi_enable_1_1_i_4_n_0));
  (* SOFT_HLUTNM = "soft_lutpair79" *) 
  LUT3 #(
    .INIT(8'h04)) 
    data_reg_axi_enable_1_1_i_5
       (.I0(sel0[6]),
        .I1(top_wr_enb),
        .I2(sel0[1]),
        .O(data_reg_axi_enable_1_1_i_5_n_0));
  LUT3 #(
    .INIT(8'hDF)) 
    reset_pipe_i_1
       (.I0(IPCORE_RESETN),
        .I1(soft_reset),
        .I2(AXI4_ARESETN),
        .O(reset_in));
  LUT6 #(
    .INIT(64'h0000000800000000)) 
    soft_reset_i_1
       (.I0(u_uz_interlockDeadtime2L_rdfifo_data_inst_n_5),
        .I1(u_uz_interlockDeadtime2L_rdfifo_data_inst_n_6),
        .I2(sel0[4]),
        .I3(sel0[3]),
        .I4(sel0[0]),
        .I5(soft_reset_i_4_n_0),
        .O(soft_reset_i_1_n_0));
  LUT6 #(
    .INIT(64'h0002000000000000)) 
    soft_reset_i_4
       (.I0(\wdata_reg[9]_0 [0]),
        .I1(sel0[6]),
        .I2(sel0[1]),
        .I3(sel0[2]),
        .I4(top_wr_enb),
        .I5(AXI4_ARESETN),
        .O(soft_reset_i_4_n_0));
  FDRE soft_reset_reg
       (.C(AXI4_ACLK),
        .CE(1'b1),
        .D(soft_reset_i_1_n_0),
        .Q(soft_reset),
        .R(1'b0));
  zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_rdfifo_data u_uz_interlockDeadtime2L_rdfifo_data_inst
       (.AXI4_ACLK(AXI4_ACLK),
        .AXI4_ARESETN(AXI4_ARESETN),
        .AXI4_ARVALID(AXI4_ARVALID),
        .AXI4_AWVALID(AXI4_AWVALID),
        .AXI4_RDATA(AXI4_RDATA),
        .AXI4_RREADY(AXI4_RREADY),
        .D({axi4_rstate_next[2],axi4_rstate_next[0]}),
        .E(u_uz_interlockDeadtime2L_rdfifo_data_inst_n_9),
        .\FSM_onehot_axi4_rstate_reg[0] ({axi4_rstate,axi4_raddr_inc_next}),
        .\FSM_onehot_axi4_rstate_reg[0]_0 (axi4_wid_next),
        .\FSM_onehot_axi4_rstate_reg[1] (u_uz_interlockDeadtime2L_rdfifo_data_inst_n_10),
        .Q(sel0),
        .SR(reset_x),
        .\axi4_raddr_reg[8] (u_uz_interlockDeadtime2L_rdfifo_data_inst_n_4),
        .axi4_rd_active_reg(u_uz_interlockDeadtime2L_rdfifo_data_inst_n_2),
        .axi4_rd_active_reg_0(u_uz_interlockDeadtime2L_rdfifo_data_inst_n_3),
        .axi4_rlast_1(axi4_rlast_1),
        .axi4_rlast_1_reg(u_uz_interlockDeadtime2L_rdfifo_data_inst_n_11),
        .axi4_rlast_1_reg_0(\axi4_rlen[7]_i_3_n_0 ),
        .axi4_rlast_1_reg_1(axi4_rlast_1_i_2_n_0),
        .\data_int_reg[1] (\data_int_reg[1] ),
        .\data_reg_axi_DelayCycles_1_1_reg[9] ({raddr_r[8],raddr_r[6:2]}),
        .data_reg_axi_enable_1_1_i_2(\data_reg_axi_DelayCycles_1_1[9]_i_6_n_0 ),
        .data_reg_axi_enable_1_1_i_2_0(\data_reg_axi_DelayCycles_1_1[9]_i_5_n_0 ),
        .out_valid_reg_0(out_valid_reg),
        .rd_active(rd_active),
        .read_reg_axi_fb_InverseBotSwitch(read_reg_axi_fb_InverseBotSwitch),
        .read_reg_axi_fb_enable(read_reg_axi_fb_enable),
        .read_reg_ip_timestamp(read_reg_ip_timestamp),
        .top_rd_enb(top_rd_enb),
        .\waddr_reg[11] (u_uz_interlockDeadtime2L_rdfifo_data_inst_n_6),
        .\waddr_reg[15] (u_uz_interlockDeadtime2L_rdfifo_data_inst_n_5));
  zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_rdfifo_last u_uz_interlockDeadtime2L_rdfifo_last_inst
       (.AXI4_ACLK(AXI4_ACLK),
        .AXI4_ARESETN(AXI4_ARESETN),
        .AXI4_RLAST(AXI4_RLAST),
        .AXI4_RREADY(AXI4_RREADY),
        .SR(reset_x),
        .axi4_rlast_1(axi4_rlast_1),
        .top_rd_enb(top_rd_enb));
  zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_rdfifo_rid u_uz_interlockDeadtime2L_rdfifo_rid_inst
       (.AXI4_ACLK(AXI4_ACLK),
        .AXI4_ARESETN(AXI4_ARESETN),
        .AXI4_RID(AXI4_RID),
        .AXI4_RREADY(AXI4_RREADY),
        .Q(axi4_rid_1),
        .SR(reset_x),
        .top_rd_enb(top_rd_enb));
  FDRE \waddr_r_reg[10] 
       (.C(AXI4_ACLK),
        .CE(axi4_awtransfer),
        .D(axi4_waddr[10]),
        .Q(waddr_r[10]),
        .R(reset_x));
  FDRE \waddr_r_reg[11] 
       (.C(AXI4_ACLK),
        .CE(axi4_awtransfer),
        .D(axi4_waddr[11]),
        .Q(waddr_r[11]),
        .R(reset_x));
  FDRE \waddr_r_reg[12] 
       (.C(AXI4_ACLK),
        .CE(axi4_awtransfer),
        .D(axi4_waddr[12]),
        .Q(waddr_r[12]),
        .R(reset_x));
  FDRE \waddr_r_reg[13] 
       (.C(AXI4_ACLK),
        .CE(axi4_awtransfer),
        .D(axi4_waddr[13]),
        .Q(waddr_r[13]),
        .R(reset_x));
  FDRE \waddr_r_reg[14] 
       (.C(AXI4_ACLK),
        .CE(axi4_awtransfer),
        .D(axi4_waddr[14]),
        .Q(waddr_r[14]),
        .R(reset_x));
  FDRE \waddr_r_reg[15] 
       (.C(AXI4_ACLK),
        .CE(axi4_awtransfer),
        .D(axi4_waddr[15]),
        .Q(waddr_r[15]),
        .R(reset_x));
  FDRE \waddr_r_reg[2] 
       (.C(AXI4_ACLK),
        .CE(axi4_awtransfer),
        .D(axi4_waddr[2]),
        .Q(waddr_r[2]),
        .R(reset_x));
  FDRE \waddr_r_reg[3] 
       (.C(AXI4_ACLK),
        .CE(axi4_awtransfer),
        .D(axi4_waddr[3]),
        .Q(waddr_r[3]),
        .R(reset_x));
  FDRE \waddr_r_reg[4] 
       (.C(AXI4_ACLK),
        .CE(axi4_awtransfer),
        .D(axi4_waddr[4]),
        .Q(waddr_r[4]),
        .R(reset_x));
  FDRE \waddr_r_reg[5] 
       (.C(AXI4_ACLK),
        .CE(axi4_awtransfer),
        .D(axi4_waddr[5]),
        .Q(waddr_r[5]),
        .R(reset_x));
  FDRE \waddr_r_reg[6] 
       (.C(AXI4_ACLK),
        .CE(axi4_awtransfer),
        .D(axi4_waddr[6]),
        .Q(waddr_r[6]),
        .R(reset_x));
  FDRE \waddr_r_reg[7] 
       (.C(AXI4_ACLK),
        .CE(axi4_awtransfer),
        .D(axi4_waddr[7]),
        .Q(waddr_r[7]),
        .R(reset_x));
  FDRE \waddr_r_reg[8] 
       (.C(AXI4_ACLK),
        .CE(axi4_awtransfer),
        .D(axi4_waddr[8]),
        .Q(waddr_r[8]),
        .R(reset_x));
  FDRE \waddr_r_reg[9] 
       (.C(AXI4_ACLK),
        .CE(axi4_awtransfer),
        .D(axi4_waddr[9]),
        .Q(waddr_r[9]),
        .R(reset_x));
  FDRE \waddr_reg[10] 
       (.C(AXI4_ACLK),
        .CE(1'b1),
        .D(waddr_r[10]),
        .Q(sel0[8]),
        .R(reset_x));
  FDRE \waddr_reg[11] 
       (.C(AXI4_ACLK),
        .CE(1'b1),
        .D(waddr_r[11]),
        .Q(sel0[9]),
        .R(reset_x));
  FDRE \waddr_reg[12] 
       (.C(AXI4_ACLK),
        .CE(1'b1),
        .D(waddr_r[12]),
        .Q(sel0[10]),
        .R(reset_x));
  FDRE \waddr_reg[13] 
       (.C(AXI4_ACLK),
        .CE(1'b1),
        .D(waddr_r[13]),
        .Q(sel0[11]),
        .R(reset_x));
  FDRE \waddr_reg[14] 
       (.C(AXI4_ACLK),
        .CE(1'b1),
        .D(waddr_r[14]),
        .Q(sel0[12]),
        .R(reset_x));
  FDRE \waddr_reg[15] 
       (.C(AXI4_ACLK),
        .CE(1'b1),
        .D(waddr_r[15]),
        .Q(sel0[13]),
        .R(reset_x));
  FDRE \waddr_reg[2] 
       (.C(AXI4_ACLK),
        .CE(1'b1),
        .D(waddr_r[2]),
        .Q(sel0[0]),
        .R(reset_x));
  FDRE \waddr_reg[3] 
       (.C(AXI4_ACLK),
        .CE(1'b1),
        .D(waddr_r[3]),
        .Q(sel0[1]),
        .R(reset_x));
  FDRE \waddr_reg[4] 
       (.C(AXI4_ACLK),
        .CE(1'b1),
        .D(waddr_r[4]),
        .Q(sel0[2]),
        .R(reset_x));
  FDRE \waddr_reg[5] 
       (.C(AXI4_ACLK),
        .CE(1'b1),
        .D(waddr_r[5]),
        .Q(sel0[3]),
        .R(reset_x));
  FDRE \waddr_reg[6] 
       (.C(AXI4_ACLK),
        .CE(1'b1),
        .D(waddr_r[6]),
        .Q(sel0[4]),
        .R(reset_x));
  FDRE \waddr_reg[7] 
       (.C(AXI4_ACLK),
        .CE(1'b1),
        .D(waddr_r[7]),
        .Q(sel0[5]),
        .R(reset_x));
  FDRE \waddr_reg[8] 
       (.C(AXI4_ACLK),
        .CE(1'b1),
        .D(waddr_r[8]),
        .Q(sel0[6]),
        .R(reset_x));
  FDRE \waddr_reg[9] 
       (.C(AXI4_ACLK),
        .CE(1'b1),
        .D(waddr_r[9]),
        .Q(sel0[7]),
        .R(reset_x));
  FDRE \wdata_int_reg[0] 
       (.C(AXI4_ACLK),
        .CE(1'b1),
        .D(AXI4_WDATA[0]),
        .Q(wdata_int[0]),
        .R(reset_x));
  FDRE \wdata_int_reg[1] 
       (.C(AXI4_ACLK),
        .CE(1'b1),
        .D(AXI4_WDATA[1]),
        .Q(wdata_int[1]),
        .R(reset_x));
  FDRE \wdata_int_reg[2] 
       (.C(AXI4_ACLK),
        .CE(1'b1),
        .D(AXI4_WDATA[2]),
        .Q(wdata_int[2]),
        .R(reset_x));
  FDRE \wdata_int_reg[3] 
       (.C(AXI4_ACLK),
        .CE(1'b1),
        .D(AXI4_WDATA[3]),
        .Q(wdata_int[3]),
        .R(reset_x));
  FDRE \wdata_int_reg[4] 
       (.C(AXI4_ACLK),
        .CE(1'b1),
        .D(AXI4_WDATA[4]),
        .Q(wdata_int[4]),
        .R(reset_x));
  FDRE \wdata_int_reg[5] 
       (.C(AXI4_ACLK),
        .CE(1'b1),
        .D(AXI4_WDATA[5]),
        .Q(wdata_int[5]),
        .R(reset_x));
  FDRE \wdata_int_reg[6] 
       (.C(AXI4_ACLK),
        .CE(1'b1),
        .D(AXI4_WDATA[6]),
        .Q(wdata_int[6]),
        .R(reset_x));
  FDRE \wdata_int_reg[7] 
       (.C(AXI4_ACLK),
        .CE(1'b1),
        .D(AXI4_WDATA[7]),
        .Q(wdata_int[7]),
        .R(reset_x));
  FDRE \wdata_int_reg[8] 
       (.C(AXI4_ACLK),
        .CE(1'b1),
        .D(AXI4_WDATA[8]),
        .Q(wdata_int[8]),
        .R(reset_x));
  FDRE \wdata_int_reg[9] 
       (.C(AXI4_ACLK),
        .CE(1'b1),
        .D(AXI4_WDATA[9]),
        .Q(wdata_int[9]),
        .R(reset_x));
  FDRE \wdata_reg[0] 
       (.C(AXI4_ACLK),
        .CE(axi4_wtransfer),
        .D(wdata_int[0]),
        .Q(\wdata_reg[9]_0 [0]),
        .R(reset_x));
  FDRE \wdata_reg[1] 
       (.C(AXI4_ACLK),
        .CE(axi4_wtransfer),
        .D(wdata_int[1]),
        .Q(\wdata_reg[9]_0 [1]),
        .R(reset_x));
  FDRE \wdata_reg[2] 
       (.C(AXI4_ACLK),
        .CE(axi4_wtransfer),
        .D(wdata_int[2]),
        .Q(\wdata_reg[9]_0 [2]),
        .R(reset_x));
  FDRE \wdata_reg[3] 
       (.C(AXI4_ACLK),
        .CE(axi4_wtransfer),
        .D(wdata_int[3]),
        .Q(\wdata_reg[9]_0 [3]),
        .R(reset_x));
  FDRE \wdata_reg[4] 
       (.C(AXI4_ACLK),
        .CE(axi4_wtransfer),
        .D(wdata_int[4]),
        .Q(\wdata_reg[9]_0 [4]),
        .R(reset_x));
  FDRE \wdata_reg[5] 
       (.C(AXI4_ACLK),
        .CE(axi4_wtransfer),
        .D(wdata_int[5]),
        .Q(\wdata_reg[9]_0 [5]),
        .R(reset_x));
  FDRE \wdata_reg[6] 
       (.C(AXI4_ACLK),
        .CE(axi4_wtransfer),
        .D(wdata_int[6]),
        .Q(\wdata_reg[9]_0 [6]),
        .R(reset_x));
  FDRE \wdata_reg[7] 
       (.C(AXI4_ACLK),
        .CE(axi4_wtransfer),
        .D(wdata_int[7]),
        .Q(\wdata_reg[9]_0 [7]),
        .R(reset_x));
  FDRE \wdata_reg[8] 
       (.C(AXI4_ACLK),
        .CE(axi4_wtransfer),
        .D(wdata_int[8]),
        .Q(\wdata_reg[9]_0 [8]),
        .R(reset_x));
  FDRE \wdata_reg[9] 
       (.C(AXI4_ACLK),
        .CE(axi4_wtransfer),
        .D(wdata_int[9]),
        .Q(\wdata_reg[9]_0 [9]),
        .R(reset_x));
  LUT2 #(
    .INIT(4'h8)) 
    wr_enb_1_i_1
       (.I0(wstrb_reduce_reg),
        .I1(axi4_wtransfer),
        .O(w_transfer_and_wstrb));
  FDRE wr_enb_1_reg
       (.C(AXI4_ACLK),
        .CE(1'b1),
        .D(w_transfer_and_wstrb),
        .Q(top_wr_enb),
        .R(reset_x));
  LUT4 #(
    .INIT(16'h8000)) 
    wstrb_reduce
       (.I0(AXI4_WSTRB[1]),
        .I1(AXI4_WSTRB[0]),
        .I2(AXI4_WSTRB[3]),
        .I3(AXI4_WSTRB[2]),
        .O(wstrb_reduce__0));
  FDRE wstrb_reduce_reg_reg
       (.C(AXI4_ACLK),
        .CE(1'b1),
        .D(wstrb_reduce__0),
        .Q(wstrb_reduce_reg),
        .R(reset_x));
endmodule

(* ORIG_REF_NAME = "uz_interlockDeadtime2L_dut" *) 
module zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_dut
   (Delay_out1_reg,
    Delay3_out1,
    PipelineDelay1_out1,
    PipelineDelay1_out1_0,
    PipelineDelay1_out1_1,
    PipelineDelay1_out1_2,
    PipelineDelay1_out1_3,
    PipelineDelay1_out1_4,
    s1_out,
    s0_out,
    Q,
    s3_out,
    s2_out,
    s5_out,
    s4_out,
    reset_x,
    write_axi_enable,
    axi_EnableOutput,
    IPCORE_CLK,
    axi_InverseBotSwitch,
    Delay2_delOut_reg,
    S0,
    S1,
    S2,
    S3,
    S4,
    S5,
    D,
    SR,
    E,
    \HDL_Counter_out1_reg[9] ,
    \HDL_Counter_out1_reg[9]_0 ,
    \HDL_Counter_out1_reg[9]_1 ,
    \HDL_Counter_out1_reg[9]_2 ,
    \HDL_Counter_out1_reg[9]_3 ,
    \HDL_Counter_out1_reg[9]_4 ,
    \HDL_Counter_out1_reg[9]_5 ,
    \HDL_Counter_out1_reg[9]_6 ,
    \HDL_Counter_out1_reg[9]_7 ,
    \HDL_Counter_out1_reg[9]_8 );
  output Delay_out1_reg;
  output Delay3_out1;
  output PipelineDelay1_out1;
  output PipelineDelay1_out1_0;
  output PipelineDelay1_out1_1;
  output PipelineDelay1_out1_2;
  output PipelineDelay1_out1_3;
  output PipelineDelay1_out1_4;
  output s1_out;
  output s0_out;
  output [9:0]Q;
  output s3_out;
  output s2_out;
  output s5_out;
  output s4_out;
  input reset_x;
  input write_axi_enable;
  input axi_EnableOutput;
  input IPCORE_CLK;
  input axi_InverseBotSwitch;
  input Delay2_delOut_reg;
  input S0;
  input S1;
  input S2;
  input S3;
  input S4;
  input S5;
  input [9:0]D;
  input [0:0]SR;
  input [0:0]E;
  input [0:0]\HDL_Counter_out1_reg[9] ;
  input [0:0]\HDL_Counter_out1_reg[9]_0 ;
  input [0:0]\HDL_Counter_out1_reg[9]_1 ;
  input [0:0]\HDL_Counter_out1_reg[9]_2 ;
  input [0:0]\HDL_Counter_out1_reg[9]_3 ;
  input [0:0]\HDL_Counter_out1_reg[9]_4 ;
  input [0:0]\HDL_Counter_out1_reg[9]_5 ;
  input [0:0]\HDL_Counter_out1_reg[9]_6 ;
  input [0:0]\HDL_Counter_out1_reg[9]_7 ;
  input [0:0]\HDL_Counter_out1_reg[9]_8 ;

  wire [9:0]D;
  wire Delay2_delOut_reg;
  wire Delay3_out1;
  wire Delay_out1_reg;
  wire [0:0]E;
  wire [0:0]\HDL_Counter_out1_reg[9] ;
  wire [0:0]\HDL_Counter_out1_reg[9]_0 ;
  wire [0:0]\HDL_Counter_out1_reg[9]_1 ;
  wire [0:0]\HDL_Counter_out1_reg[9]_2 ;
  wire [0:0]\HDL_Counter_out1_reg[9]_3 ;
  wire [0:0]\HDL_Counter_out1_reg[9]_4 ;
  wire [0:0]\HDL_Counter_out1_reg[9]_5 ;
  wire [0:0]\HDL_Counter_out1_reg[9]_6 ;
  wire [0:0]\HDL_Counter_out1_reg[9]_7 ;
  wire [0:0]\HDL_Counter_out1_reg[9]_8 ;
  wire IPCORE_CLK;
  wire PipelineDelay1_out1;
  wire PipelineDelay1_out1_0;
  wire PipelineDelay1_out1_1;
  wire PipelineDelay1_out1_2;
  wire PipelineDelay1_out1_3;
  wire PipelineDelay1_out1_4;
  wire [9:0]Q;
  wire S0;
  wire S1;
  wire S2;
  wire S3;
  wire S4;
  wire S5;
  wire [0:0]SR;
  wire axi_EnableOutput;
  wire axi_InverseBotSwitch;
  wire reset_x;
  wire s0_out;
  wire s1_out;
  wire s2_out;
  wire s3_out;
  wire s4_out;
  wire s5_out;
  wire write_axi_enable;

  zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_src_uz_interlockDeadtime2L u_uz_interlockDeadtime2L_src_uz_interlockDeadtime2L
       (.D(D),
        .Delay2_delOut_reg(Delay2_delOut_reg),
        .Delay3_out1(Delay3_out1),
        .Delay_out1_reg_0(Delay_out1_reg),
        .E(E),
        .\HDL_Counter_out1_reg[9] (\HDL_Counter_out1_reg[9] ),
        .\HDL_Counter_out1_reg[9]_0 (\HDL_Counter_out1_reg[9]_0 ),
        .\HDL_Counter_out1_reg[9]_1 (\HDL_Counter_out1_reg[9]_1 ),
        .\HDL_Counter_out1_reg[9]_2 (\HDL_Counter_out1_reg[9]_2 ),
        .\HDL_Counter_out1_reg[9]_3 (\HDL_Counter_out1_reg[9]_3 ),
        .\HDL_Counter_out1_reg[9]_4 (\HDL_Counter_out1_reg[9]_4 ),
        .\HDL_Counter_out1_reg[9]_5 (\HDL_Counter_out1_reg[9]_5 ),
        .\HDL_Counter_out1_reg[9]_6 (\HDL_Counter_out1_reg[9]_6 ),
        .\HDL_Counter_out1_reg[9]_7 (\HDL_Counter_out1_reg[9]_7 ),
        .\HDL_Counter_out1_reg[9]_8 (\HDL_Counter_out1_reg[9]_8 ),
        .IPCORE_CLK(IPCORE_CLK),
        .PipelineDelay1_out1(PipelineDelay1_out1),
        .PipelineDelay1_out1_0(PipelineDelay1_out1_0),
        .PipelineDelay1_out1_1(PipelineDelay1_out1_1),
        .PipelineDelay1_out1_2(PipelineDelay1_out1_2),
        .PipelineDelay1_out1_3(PipelineDelay1_out1_3),
        .PipelineDelay1_out1_4(PipelineDelay1_out1_4),
        .Q(Q),
        .S0(S0),
        .S1(S1),
        .S2(S2),
        .S3(S3),
        .S4(S4),
        .S5(S5),
        .SR(SR),
        .axi_EnableOutput(axi_EnableOutput),
        .axi_InverseBotSwitch(axi_InverseBotSwitch),
        .reset_x(reset_x),
        .s0_out(s0_out),
        .s1_out(s1_out),
        .s2_out(s2_out),
        .s3_out(s3_out),
        .s4_out(s4_out),
        .s5_out(s5_out),
        .write_axi_enable(write_axi_enable));
endmodule

(* ORIG_REF_NAME = "uz_interlockDeadtime2L_rdfifo_data" *) 
module zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_rdfifo_data
   (out_valid_reg_0,
    SR,
    axi4_rd_active_reg,
    axi4_rd_active_reg_0,
    \axi4_raddr_reg[8] ,
    \waddr_reg[15] ,
    \waddr_reg[11] ,
    D,
    E,
    \FSM_onehot_axi4_rstate_reg[1] ,
    axi4_rlast_1_reg,
    AXI4_RDATA,
    AXI4_ACLK,
    \data_int_reg[1] ,
    Q,
    read_reg_axi_fb_enable,
    read_reg_axi_fb_InverseBotSwitch,
    read_reg_ip_timestamp,
    \data_reg_axi_DelayCycles_1_1_reg[9] ,
    rd_active,
    data_reg_axi_enable_1_1_i_2,
    data_reg_axi_enable_1_1_i_2_0,
    AXI4_RREADY,
    AXI4_ARESETN,
    top_rd_enb,
    \FSM_onehot_axi4_rstate_reg[0] ,
    \FSM_onehot_axi4_rstate_reg[0]_0 ,
    AXI4_AWVALID,
    AXI4_ARVALID,
    axi4_rlast_1,
    axi4_rlast_1_reg_0,
    axi4_rlast_1_reg_1);
  output out_valid_reg_0;
  output [0:0]SR;
  output axi4_rd_active_reg;
  output axi4_rd_active_reg_0;
  output \axi4_raddr_reg[8] ;
  output \waddr_reg[15] ;
  output \waddr_reg[11] ;
  output [1:0]D;
  output [0:0]E;
  output \FSM_onehot_axi4_rstate_reg[1] ;
  output axi4_rlast_1_reg;
  output [31:0]AXI4_RDATA;
  input AXI4_ACLK;
  input [9:0]\data_int_reg[1] ;
  input [13:0]Q;
  input read_reg_axi_fb_enable;
  input read_reg_axi_fb_InverseBotSwitch;
  input [0:0]read_reg_ip_timestamp;
  input [5:0]\data_reg_axi_DelayCycles_1_1_reg[9] ;
  input rd_active;
  input data_reg_axi_enable_1_1_i_2;
  input data_reg_axi_enable_1_1_i_2_0;
  input AXI4_RREADY;
  input AXI4_ARESETN;
  input top_rd_enb;
  input [2:0]\FSM_onehot_axi4_rstate_reg[0] ;
  input [0:0]\FSM_onehot_axi4_rstate_reg[0]_0 ;
  input AXI4_AWVALID;
  input AXI4_ARVALID;
  input axi4_rlast_1;
  input axi4_rlast_1_reg_0;
  input axi4_rlast_1_reg_1;

  wire AXI4_ACLK;
  wire AXI4_ARESETN;
  wire AXI4_ARVALID;
  wire AXI4_AWVALID;
  wire [31:0]AXI4_RDATA;
  wire AXI4_RREADY;
  wire [1:0]D;
  wire [0:0]E;
  wire \FSM_onehot_axi4_rstate[2]_i_2_n_0 ;
  wire [2:0]\FSM_onehot_axi4_rstate_reg[0] ;
  wire [0:0]\FSM_onehot_axi4_rstate_reg[0]_0 ;
  wire \FSM_onehot_axi4_rstate_reg[1] ;
  wire [13:0]Q;
  wire Q_next;
  wire Q_next_1;
  wire Q_next_2;
  wire [0:0]SR;
  wire \axi4_raddr_reg[8] ;
  wire axi4_rd_active_reg;
  wire axi4_rd_active_reg_0;
  wire axi4_rlast_1;
  wire axi4_rlast_1_reg;
  wire axi4_rlast_1_reg_0;
  wire axi4_rlast_1_reg_1;
  wire [31:0]cache_data;
  wire cache_valid;
  wire cache_wr_en;
  wire [31:0]data_int;
  wire [9:0]\data_int_reg[1] ;
  wire [31:0]data_out_next;
  wire [5:0]\data_reg_axi_DelayCycles_1_1_reg[9] ;
  wire data_reg_axi_enable_1_1_i_2;
  wire data_reg_axi_enable_1_1_i_2_0;
  wire [3:0]fifo_back_indx0;
  wire [3:0]fifo_front_indx0;
  wire \fifo_front_indx[3]_i_3_n_0 ;
  wire fifo_read_enable;
  wire \fifo_sample_count[0]_i_1_n_0 ;
  wire \fifo_sample_count[1]_i_1_n_0 ;
  wire \fifo_sample_count[4]_i_1_n_0 ;
  wire \fifo_sample_count[4]_i_3_n_0 ;
  wire \fifo_sample_count[4]_i_4_n_0 ;
  wire [4:2]fifo_sample_count_next;
  wire \fifo_sample_count_reg_n_0_[0] ;
  wire \fifo_sample_count_reg_n_0_[1] ;
  wire \fifo_sample_count_reg_n_0_[2] ;
  wire \fifo_sample_count_reg_n_0_[3] ;
  wire \fifo_sample_count_reg_n_0_[4] ;
  wire fifo_valid;
  wire out_valid_reg_0;
  wire out_wr_en;
  wire rd_active;
  wire [3:0]rd_addr;
  wire read_reg_axi_fb_InverseBotSwitch;
  wire read_reg_axi_fb_enable;
  wire [0:0]read_reg_ip_timestamp;
  wire top_rd_enb;
  wire w_d1_i_1_n_0;
  wire w_d1_reg_n_0;
  wire [31:0]w_d2;
  wire [31:0]w_out;
  wire \waddr_reg[11] ;
  wire \waddr_reg[15] ;
  wire [3:0]wr_addr;
  wire wr_en;

  LUT6 #(
    .INIT(64'hF4F444F4F4F4F4F4)) 
    \FSM_onehot_axi4_rstate[0]_i_1 
       (.I0(\FSM_onehot_axi4_rstate[2]_i_2_n_0 ),
        .I1(\FSM_onehot_axi4_rstate_reg[0] [2]),
        .I2(\FSM_onehot_axi4_rstate_reg[0] [0]),
        .I3(\FSM_onehot_axi4_rstate_reg[0]_0 ),
        .I4(AXI4_AWVALID),
        .I5(AXI4_ARVALID),
        .O(D[0]));
  LUT4 #(
    .INIT(16'hF888)) 
    \FSM_onehot_axi4_rstate[2]_i_1 
       (.I0(\FSM_onehot_axi4_rstate_reg[0] [2]),
        .I1(\FSM_onehot_axi4_rstate[2]_i_2_n_0 ),
        .I2(axi4_rlast_1),
        .I3(\FSM_onehot_axi4_rstate_reg[0] [1]),
        .O(D[1]));
  (* SOFT_HLUTNM = "soft_lutpair46" *) 
  LUT4 #(
    .INIT(16'hEAAA)) 
    \FSM_onehot_axi4_rstate[2]_i_2 
       (.I0(\fifo_sample_count_reg_n_0_[4] ),
        .I1(\fifo_sample_count_reg_n_0_[3] ),
        .I2(\fifo_sample_count_reg_n_0_[1] ),
        .I3(\fifo_sample_count_reg_n_0_[2] ),
        .O(\FSM_onehot_axi4_rstate[2]_i_2_n_0 ));
  LUT1 #(
    .INIT(2'h1)) 
    \FSM_onehot_axi4_wstate[1]_i_1 
       (.I0(AXI4_ARESETN),
        .O(SR));
  LUT4 #(
    .INIT(16'hEE0E)) 
    \Out_tmp[31]_i_1 
       (.I0(fifo_valid),
        .I1(cache_valid),
        .I2(out_valid_reg_0),
        .I3(AXI4_RREADY),
        .O(out_wr_en));
  FDRE \Out_tmp_reg[0] 
       (.C(AXI4_ACLK),
        .CE(out_wr_en),
        .D(data_out_next[0]),
        .Q(AXI4_RDATA[0]),
        .R(SR));
  FDRE \Out_tmp_reg[10] 
       (.C(AXI4_ACLK),
        .CE(out_wr_en),
        .D(data_out_next[10]),
        .Q(AXI4_RDATA[10]),
        .R(SR));
  FDRE \Out_tmp_reg[11] 
       (.C(AXI4_ACLK),
        .CE(out_wr_en),
        .D(data_out_next[11]),
        .Q(AXI4_RDATA[11]),
        .R(SR));
  FDRE \Out_tmp_reg[12] 
       (.C(AXI4_ACLK),
        .CE(out_wr_en),
        .D(data_out_next[12]),
        .Q(AXI4_RDATA[12]),
        .R(SR));
  FDRE \Out_tmp_reg[13] 
       (.C(AXI4_ACLK),
        .CE(out_wr_en),
        .D(data_out_next[13]),
        .Q(AXI4_RDATA[13]),
        .R(SR));
  FDRE \Out_tmp_reg[14] 
       (.C(AXI4_ACLK),
        .CE(out_wr_en),
        .D(data_out_next[14]),
        .Q(AXI4_RDATA[14]),
        .R(SR));
  FDRE \Out_tmp_reg[15] 
       (.C(AXI4_ACLK),
        .CE(out_wr_en),
        .D(data_out_next[15]),
        .Q(AXI4_RDATA[15]),
        .R(SR));
  FDRE \Out_tmp_reg[16] 
       (.C(AXI4_ACLK),
        .CE(out_wr_en),
        .D(data_out_next[16]),
        .Q(AXI4_RDATA[16]),
        .R(SR));
  FDRE \Out_tmp_reg[17] 
       (.C(AXI4_ACLK),
        .CE(out_wr_en),
        .D(data_out_next[17]),
        .Q(AXI4_RDATA[17]),
        .R(SR));
  FDRE \Out_tmp_reg[18] 
       (.C(AXI4_ACLK),
        .CE(out_wr_en),
        .D(data_out_next[18]),
        .Q(AXI4_RDATA[18]),
        .R(SR));
  FDRE \Out_tmp_reg[19] 
       (.C(AXI4_ACLK),
        .CE(out_wr_en),
        .D(data_out_next[19]),
        .Q(AXI4_RDATA[19]),
        .R(SR));
  FDRE \Out_tmp_reg[1] 
       (.C(AXI4_ACLK),
        .CE(out_wr_en),
        .D(data_out_next[1]),
        .Q(AXI4_RDATA[1]),
        .R(SR));
  FDRE \Out_tmp_reg[20] 
       (.C(AXI4_ACLK),
        .CE(out_wr_en),
        .D(data_out_next[20]),
        .Q(AXI4_RDATA[20]),
        .R(SR));
  FDRE \Out_tmp_reg[21] 
       (.C(AXI4_ACLK),
        .CE(out_wr_en),
        .D(data_out_next[21]),
        .Q(AXI4_RDATA[21]),
        .R(SR));
  FDRE \Out_tmp_reg[22] 
       (.C(AXI4_ACLK),
        .CE(out_wr_en),
        .D(data_out_next[22]),
        .Q(AXI4_RDATA[22]),
        .R(SR));
  FDRE \Out_tmp_reg[23] 
       (.C(AXI4_ACLK),
        .CE(out_wr_en),
        .D(data_out_next[23]),
        .Q(AXI4_RDATA[23]),
        .R(SR));
  FDRE \Out_tmp_reg[24] 
       (.C(AXI4_ACLK),
        .CE(out_wr_en),
        .D(data_out_next[24]),
        .Q(AXI4_RDATA[24]),
        .R(SR));
  FDRE \Out_tmp_reg[25] 
       (.C(AXI4_ACLK),
        .CE(out_wr_en),
        .D(data_out_next[25]),
        .Q(AXI4_RDATA[25]),
        .R(SR));
  FDRE \Out_tmp_reg[26] 
       (.C(AXI4_ACLK),
        .CE(out_wr_en),
        .D(data_out_next[26]),
        .Q(AXI4_RDATA[26]),
        .R(SR));
  FDRE \Out_tmp_reg[27] 
       (.C(AXI4_ACLK),
        .CE(out_wr_en),
        .D(data_out_next[27]),
        .Q(AXI4_RDATA[27]),
        .R(SR));
  FDRE \Out_tmp_reg[28] 
       (.C(AXI4_ACLK),
        .CE(out_wr_en),
        .D(data_out_next[28]),
        .Q(AXI4_RDATA[28]),
        .R(SR));
  FDRE \Out_tmp_reg[29] 
       (.C(AXI4_ACLK),
        .CE(out_wr_en),
        .D(data_out_next[29]),
        .Q(AXI4_RDATA[29]),
        .R(SR));
  FDRE \Out_tmp_reg[2] 
       (.C(AXI4_ACLK),
        .CE(out_wr_en),
        .D(data_out_next[2]),
        .Q(AXI4_RDATA[2]),
        .R(SR));
  FDRE \Out_tmp_reg[30] 
       (.C(AXI4_ACLK),
        .CE(out_wr_en),
        .D(data_out_next[30]),
        .Q(AXI4_RDATA[30]),
        .R(SR));
  FDRE \Out_tmp_reg[31] 
       (.C(AXI4_ACLK),
        .CE(out_wr_en),
        .D(data_out_next[31]),
        .Q(AXI4_RDATA[31]),
        .R(SR));
  FDRE \Out_tmp_reg[3] 
       (.C(AXI4_ACLK),
        .CE(out_wr_en),
        .D(data_out_next[3]),
        .Q(AXI4_RDATA[3]),
        .R(SR));
  FDRE \Out_tmp_reg[4] 
       (.C(AXI4_ACLK),
        .CE(out_wr_en),
        .D(data_out_next[4]),
        .Q(AXI4_RDATA[4]),
        .R(SR));
  FDRE \Out_tmp_reg[5] 
       (.C(AXI4_ACLK),
        .CE(out_wr_en),
        .D(data_out_next[5]),
        .Q(AXI4_RDATA[5]),
        .R(SR));
  FDRE \Out_tmp_reg[6] 
       (.C(AXI4_ACLK),
        .CE(out_wr_en),
        .D(data_out_next[6]),
        .Q(AXI4_RDATA[6]),
        .R(SR));
  FDRE \Out_tmp_reg[7] 
       (.C(AXI4_ACLK),
        .CE(out_wr_en),
        .D(data_out_next[7]),
        .Q(AXI4_RDATA[7]),
        .R(SR));
  FDRE \Out_tmp_reg[8] 
       (.C(AXI4_ACLK),
        .CE(out_wr_en),
        .D(data_out_next[8]),
        .Q(AXI4_RDATA[8]),
        .R(SR));
  FDRE \Out_tmp_reg[9] 
       (.C(AXI4_ACLK),
        .CE(out_wr_en),
        .D(data_out_next[9]),
        .Q(AXI4_RDATA[9]),
        .R(SR));
  LUT5 #(
    .INIT(32'h101F1010)) 
    axi4_ar_transfer_i_1
       (.I0(axi4_rlast_1),
        .I1(\FSM_onehot_axi4_rstate[2]_i_2_n_0 ),
        .I2(\FSM_onehot_axi4_rstate_reg[0] [1]),
        .I3(\FSM_onehot_axi4_rstate_reg[0] [0]),
        .I4(top_rd_enb),
        .O(axi4_rlast_1_reg));
  LUT6 #(
    .INIT(64'h0000FFCF00AA0020)) 
    axi4_rlast_1_i_1
       (.I0(\FSM_onehot_axi4_rstate_reg[0] [1]),
        .I1(axi4_rlast_1_reg_0),
        .I2(axi4_rlast_1_reg_1),
        .I3(\FSM_onehot_axi4_rstate[2]_i_2_n_0 ),
        .I4(\FSM_onehot_axi4_rstate_reg[0] [0]),
        .I5(axi4_rlast_1),
        .O(\FSM_onehot_axi4_rstate_reg[1] ));
  LUT6 #(
    .INIT(64'hFFFFFFFF15550000)) 
    \axi4_rlen[7]_i_1 
       (.I0(\fifo_sample_count_reg_n_0_[4] ),
        .I1(\fifo_sample_count_reg_n_0_[3] ),
        .I2(\fifo_sample_count_reg_n_0_[1] ),
        .I3(\fifo_sample_count_reg_n_0_[2] ),
        .I4(\FSM_onehot_axi4_rstate_reg[0] [1]),
        .I5(\FSM_onehot_axi4_rstate_reg[0] [0]),
        .O(E));
  LUT4 #(
    .INIT(16'hB040)) 
    \cache_data[31]_i_1 
       (.I0(AXI4_RREADY),
        .I1(out_valid_reg_0),
        .I2(fifo_valid),
        .I3(cache_valid),
        .O(cache_wr_en));
  FDRE \cache_data_reg[0] 
       (.C(AXI4_ACLK),
        .CE(cache_wr_en),
        .D(w_out[0]),
        .Q(cache_data[0]),
        .R(SR));
  FDRE \cache_data_reg[10] 
       (.C(AXI4_ACLK),
        .CE(cache_wr_en),
        .D(w_out[10]),
        .Q(cache_data[10]),
        .R(SR));
  FDRE \cache_data_reg[11] 
       (.C(AXI4_ACLK),
        .CE(cache_wr_en),
        .D(w_out[11]),
        .Q(cache_data[11]),
        .R(SR));
  FDRE \cache_data_reg[12] 
       (.C(AXI4_ACLK),
        .CE(cache_wr_en),
        .D(w_out[12]),
        .Q(cache_data[12]),
        .R(SR));
  FDRE \cache_data_reg[13] 
       (.C(AXI4_ACLK),
        .CE(cache_wr_en),
        .D(w_out[13]),
        .Q(cache_data[13]),
        .R(SR));
  FDRE \cache_data_reg[14] 
       (.C(AXI4_ACLK),
        .CE(cache_wr_en),
        .D(w_out[14]),
        .Q(cache_data[14]),
        .R(SR));
  FDRE \cache_data_reg[15] 
       (.C(AXI4_ACLK),
        .CE(cache_wr_en),
        .D(w_out[15]),
        .Q(cache_data[15]),
        .R(SR));
  FDRE \cache_data_reg[16] 
       (.C(AXI4_ACLK),
        .CE(cache_wr_en),
        .D(w_out[16]),
        .Q(cache_data[16]),
        .R(SR));
  FDRE \cache_data_reg[17] 
       (.C(AXI4_ACLK),
        .CE(cache_wr_en),
        .D(w_out[17]),
        .Q(cache_data[17]),
        .R(SR));
  FDRE \cache_data_reg[18] 
       (.C(AXI4_ACLK),
        .CE(cache_wr_en),
        .D(w_out[18]),
        .Q(cache_data[18]),
        .R(SR));
  FDRE \cache_data_reg[19] 
       (.C(AXI4_ACLK),
        .CE(cache_wr_en),
        .D(w_out[19]),
        .Q(cache_data[19]),
        .R(SR));
  FDRE \cache_data_reg[1] 
       (.C(AXI4_ACLK),
        .CE(cache_wr_en),
        .D(w_out[1]),
        .Q(cache_data[1]),
        .R(SR));
  FDRE \cache_data_reg[20] 
       (.C(AXI4_ACLK),
        .CE(cache_wr_en),
        .D(w_out[20]),
        .Q(cache_data[20]),
        .R(SR));
  FDRE \cache_data_reg[21] 
       (.C(AXI4_ACLK),
        .CE(cache_wr_en),
        .D(w_out[21]),
        .Q(cache_data[21]),
        .R(SR));
  FDRE \cache_data_reg[22] 
       (.C(AXI4_ACLK),
        .CE(cache_wr_en),
        .D(w_out[22]),
        .Q(cache_data[22]),
        .R(SR));
  FDRE \cache_data_reg[23] 
       (.C(AXI4_ACLK),
        .CE(cache_wr_en),
        .D(w_out[23]),
        .Q(cache_data[23]),
        .R(SR));
  FDRE \cache_data_reg[24] 
       (.C(AXI4_ACLK),
        .CE(cache_wr_en),
        .D(w_out[24]),
        .Q(cache_data[24]),
        .R(SR));
  FDRE \cache_data_reg[25] 
       (.C(AXI4_ACLK),
        .CE(cache_wr_en),
        .D(w_out[25]),
        .Q(cache_data[25]),
        .R(SR));
  FDRE \cache_data_reg[26] 
       (.C(AXI4_ACLK),
        .CE(cache_wr_en),
        .D(w_out[26]),
        .Q(cache_data[26]),
        .R(SR));
  FDRE \cache_data_reg[27] 
       (.C(AXI4_ACLK),
        .CE(cache_wr_en),
        .D(w_out[27]),
        .Q(cache_data[27]),
        .R(SR));
  FDRE \cache_data_reg[28] 
       (.C(AXI4_ACLK),
        .CE(cache_wr_en),
        .D(w_out[28]),
        .Q(cache_data[28]),
        .R(SR));
  FDRE \cache_data_reg[29] 
       (.C(AXI4_ACLK),
        .CE(cache_wr_en),
        .D(w_out[29]),
        .Q(cache_data[29]),
        .R(SR));
  FDRE \cache_data_reg[2] 
       (.C(AXI4_ACLK),
        .CE(cache_wr_en),
        .D(w_out[2]),
        .Q(cache_data[2]),
        .R(SR));
  FDRE \cache_data_reg[30] 
       (.C(AXI4_ACLK),
        .CE(cache_wr_en),
        .D(w_out[30]),
        .Q(cache_data[30]),
        .R(SR));
  FDRE \cache_data_reg[31] 
       (.C(AXI4_ACLK),
        .CE(cache_wr_en),
        .D(w_out[31]),
        .Q(cache_data[31]),
        .R(SR));
  FDRE \cache_data_reg[3] 
       (.C(AXI4_ACLK),
        .CE(cache_wr_en),
        .D(w_out[3]),
        .Q(cache_data[3]),
        .R(SR));
  FDRE \cache_data_reg[4] 
       (.C(AXI4_ACLK),
        .CE(cache_wr_en),
        .D(w_out[4]),
        .Q(cache_data[4]),
        .R(SR));
  FDRE \cache_data_reg[5] 
       (.C(AXI4_ACLK),
        .CE(cache_wr_en),
        .D(w_out[5]),
        .Q(cache_data[5]),
        .R(SR));
  FDRE \cache_data_reg[6] 
       (.C(AXI4_ACLK),
        .CE(cache_wr_en),
        .D(w_out[6]),
        .Q(cache_data[6]),
        .R(SR));
  FDRE \cache_data_reg[7] 
       (.C(AXI4_ACLK),
        .CE(cache_wr_en),
        .D(w_out[7]),
        .Q(cache_data[7]),
        .R(SR));
  FDRE \cache_data_reg[8] 
       (.C(AXI4_ACLK),
        .CE(cache_wr_en),
        .D(w_out[8]),
        .Q(cache_data[8]),
        .R(SR));
  FDRE \cache_data_reg[9] 
       (.C(AXI4_ACLK),
        .CE(cache_wr_en),
        .D(w_out[9]),
        .Q(cache_data[9]),
        .R(SR));
  (* SOFT_HLUTNM = "soft_lutpair45" *) 
  LUT4 #(
    .INIT(16'hF440)) 
    cache_valid_i_1
       (.I0(AXI4_RREADY),
        .I1(out_valid_reg_0),
        .I2(fifo_valid),
        .I3(cache_valid),
        .O(Q_next));
  FDRE cache_valid_reg
       (.C(AXI4_ACLK),
        .CE(1'b1),
        .D(Q_next),
        .Q(cache_valid),
        .R(SR));
  (* SOFT_HLUTNM = "soft_lutpair50" *) 
  LUT1 #(
    .INIT(2'h1)) 
    \fifo_back_indx[0]_i_1 
       (.I0(wr_addr[0]),
        .O(fifo_back_indx0[0]));
  (* SOFT_HLUTNM = "soft_lutpair50" *) 
  LUT2 #(
    .INIT(4'h6)) 
    \fifo_back_indx[1]_i_1 
       (.I0(wr_addr[0]),
        .I1(wr_addr[1]),
        .O(fifo_back_indx0[1]));
  (* SOFT_HLUTNM = "soft_lutpair47" *) 
  LUT3 #(
    .INIT(8'h78)) 
    \fifo_back_indx[2]_i_1 
       (.I0(wr_addr[1]),
        .I1(wr_addr[0]),
        .I2(wr_addr[2]),
        .O(fifo_back_indx0[2]));
  (* SOFT_HLUTNM = "soft_lutpair47" *) 
  LUT4 #(
    .INIT(16'h7F80)) 
    \fifo_back_indx[3]_i_1 
       (.I0(wr_addr[0]),
        .I1(wr_addr[1]),
        .I2(wr_addr[2]),
        .I3(wr_addr[3]),
        .O(fifo_back_indx0[3]));
  FDRE \fifo_back_indx_reg[0] 
       (.C(AXI4_ACLK),
        .CE(wr_en),
        .D(fifo_back_indx0[0]),
        .Q(wr_addr[0]),
        .R(SR));
  FDRE \fifo_back_indx_reg[1] 
       (.C(AXI4_ACLK),
        .CE(wr_en),
        .D(fifo_back_indx0[1]),
        .Q(wr_addr[1]),
        .R(SR));
  FDRE \fifo_back_indx_reg[2] 
       (.C(AXI4_ACLK),
        .CE(wr_en),
        .D(fifo_back_indx0[2]),
        .Q(wr_addr[2]),
        .R(SR));
  FDRE \fifo_back_indx_reg[3] 
       (.C(AXI4_ACLK),
        .CE(wr_en),
        .D(fifo_back_indx0[3]),
        .Q(wr_addr[3]),
        .R(SR));
  (* SOFT_HLUTNM = "soft_lutpair51" *) 
  LUT1 #(
    .INIT(2'h1)) 
    \fifo_front_indx[0]_i_1 
       (.I0(rd_addr[0]),
        .O(fifo_front_indx0[0]));
  (* SOFT_HLUTNM = "soft_lutpair51" *) 
  LUT2 #(
    .INIT(4'h6)) 
    \fifo_front_indx[1]_i_1 
       (.I0(rd_addr[0]),
        .I1(rd_addr[1]),
        .O(fifo_front_indx0[1]));
  (* SOFT_HLUTNM = "soft_lutpair48" *) 
  LUT3 #(
    .INIT(8'h78)) 
    \fifo_front_indx[2]_i_1 
       (.I0(rd_addr[1]),
        .I1(rd_addr[0]),
        .I2(rd_addr[2]),
        .O(fifo_front_indx0[2]));
  LUT6 #(
    .INIT(64'hFFFFFFFE00000000)) 
    \fifo_front_indx[3]_i_1 
       (.I0(\fifo_sample_count_reg_n_0_[4] ),
        .I1(\fifo_sample_count_reg_n_0_[2] ),
        .I2(\fifo_sample_count_reg_n_0_[0] ),
        .I3(\fifo_sample_count_reg_n_0_[1] ),
        .I4(\fifo_sample_count_reg_n_0_[3] ),
        .I5(\fifo_front_indx[3]_i_3_n_0 ),
        .O(fifo_read_enable));
  (* SOFT_HLUTNM = "soft_lutpair48" *) 
  LUT4 #(
    .INIT(16'h7F80)) 
    \fifo_front_indx[3]_i_2 
       (.I0(rd_addr[0]),
        .I1(rd_addr[1]),
        .I2(rd_addr[2]),
        .I3(rd_addr[3]),
        .O(fifo_front_indx0[3]));
  LUT3 #(
    .INIT(8'h7F)) 
    \fifo_front_indx[3]_i_3 
       (.I0(fifo_valid),
        .I1(cache_valid),
        .I2(out_valid_reg_0),
        .O(\fifo_front_indx[3]_i_3_n_0 ));
  FDRE \fifo_front_indx_reg[0] 
       (.C(AXI4_ACLK),
        .CE(fifo_read_enable),
        .D(fifo_front_indx0[0]),
        .Q(rd_addr[0]),
        .R(SR));
  FDRE \fifo_front_indx_reg[1] 
       (.C(AXI4_ACLK),
        .CE(fifo_read_enable),
        .D(fifo_front_indx0[1]),
        .Q(rd_addr[1]),
        .R(SR));
  FDRE \fifo_front_indx_reg[2] 
       (.C(AXI4_ACLK),
        .CE(fifo_read_enable),
        .D(fifo_front_indx0[2]),
        .Q(rd_addr[2]),
        .R(SR));
  FDRE \fifo_front_indx_reg[3] 
       (.C(AXI4_ACLK),
        .CE(fifo_read_enable),
        .D(fifo_front_indx0[3]),
        .Q(rd_addr[3]),
        .R(SR));
  (* SOFT_HLUTNM = "soft_lutpair49" *) 
  LUT1 #(
    .INIT(2'h1)) 
    \fifo_sample_count[0]_i_1 
       (.I0(\fifo_sample_count_reg_n_0_[0] ),
        .O(\fifo_sample_count[0]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair49" *) 
  LUT3 #(
    .INIT(8'h96)) 
    \fifo_sample_count[1]_i_1 
       (.I0(\fifo_sample_count[4]_i_4_n_0 ),
        .I1(\fifo_sample_count_reg_n_0_[1] ),
        .I2(\fifo_sample_count_reg_n_0_[0] ),
        .O(\fifo_sample_count[1]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair44" *) 
  LUT4 #(
    .INIT(16'hBD42)) 
    \fifo_sample_count[2]_i_1 
       (.I0(\fifo_sample_count[4]_i_4_n_0 ),
        .I1(\fifo_sample_count_reg_n_0_[1] ),
        .I2(\fifo_sample_count_reg_n_0_[0] ),
        .I3(\fifo_sample_count_reg_n_0_[2] ),
        .O(fifo_sample_count_next[2]));
  (* SOFT_HLUTNM = "soft_lutpair44" *) 
  LUT5 #(
    .INIT(32'hBFFD4002)) 
    \fifo_sample_count[3]_i_1 
       (.I0(\fifo_sample_count[4]_i_4_n_0 ),
        .I1(\fifo_sample_count_reg_n_0_[1] ),
        .I2(\fifo_sample_count_reg_n_0_[2] ),
        .I3(\fifo_sample_count_reg_n_0_[0] ),
        .I4(\fifo_sample_count_reg_n_0_[3] ),
        .O(fifo_sample_count_next[3]));
  LUT6 #(
    .INIT(64'h8A76767676767676)) 
    \fifo_sample_count[4]_i_1 
       (.I0(top_rd_enb),
        .I1(\fifo_sample_count[4]_i_3_n_0 ),
        .I2(\fifo_sample_count_reg_n_0_[4] ),
        .I3(fifo_valid),
        .I4(cache_valid),
        .I5(out_valid_reg_0),
        .O(\fifo_sample_count[4]_i_1_n_0 ));
  LUT6 #(
    .INIT(64'hBFFFFFFD40000002)) 
    \fifo_sample_count[4]_i_2 
       (.I0(\fifo_sample_count[4]_i_4_n_0 ),
        .I1(\fifo_sample_count_reg_n_0_[2] ),
        .I2(\fifo_sample_count_reg_n_0_[1] ),
        .I3(\fifo_sample_count_reg_n_0_[3] ),
        .I4(\fifo_sample_count_reg_n_0_[0] ),
        .I5(\fifo_sample_count_reg_n_0_[4] ),
        .O(fifo_sample_count_next[4]));
  (* SOFT_HLUTNM = "soft_lutpair46" *) 
  LUT4 #(
    .INIT(16'hFFFE)) 
    \fifo_sample_count[4]_i_3 
       (.I0(\fifo_sample_count_reg_n_0_[2] ),
        .I1(\fifo_sample_count_reg_n_0_[0] ),
        .I2(\fifo_sample_count_reg_n_0_[1] ),
        .I3(\fifo_sample_count_reg_n_0_[3] ),
        .O(\fifo_sample_count[4]_i_3_n_0 ));
  LUT6 #(
    .INIT(64'h2EEEEEEEFFFFFFFF)) 
    \fifo_sample_count[4]_i_4 
       (.I0(\fifo_sample_count_reg_n_0_[4] ),
        .I1(\fifo_sample_count[4]_i_3_n_0 ),
        .I2(fifo_valid),
        .I3(cache_valid),
        .I4(out_valid_reg_0),
        .I5(top_rd_enb),
        .O(\fifo_sample_count[4]_i_4_n_0 ));
  FDRE \fifo_sample_count_reg[0] 
       (.C(AXI4_ACLK),
        .CE(\fifo_sample_count[4]_i_1_n_0 ),
        .D(\fifo_sample_count[0]_i_1_n_0 ),
        .Q(\fifo_sample_count_reg_n_0_[0] ),
        .R(SR));
  FDRE \fifo_sample_count_reg[1] 
       (.C(AXI4_ACLK),
        .CE(\fifo_sample_count[4]_i_1_n_0 ),
        .D(\fifo_sample_count[1]_i_1_n_0 ),
        .Q(\fifo_sample_count_reg_n_0_[1] ),
        .R(SR));
  FDRE \fifo_sample_count_reg[2] 
       (.C(AXI4_ACLK),
        .CE(\fifo_sample_count[4]_i_1_n_0 ),
        .D(fifo_sample_count_next[2]),
        .Q(\fifo_sample_count_reg_n_0_[2] ),
        .R(SR));
  FDRE \fifo_sample_count_reg[3] 
       (.C(AXI4_ACLK),
        .CE(\fifo_sample_count[4]_i_1_n_0 ),
        .D(fifo_sample_count_next[3]),
        .Q(\fifo_sample_count_reg_n_0_[3] ),
        .R(SR));
  FDRE \fifo_sample_count_reg[4] 
       (.C(AXI4_ACLK),
        .CE(\fifo_sample_count[4]_i_1_n_0 ),
        .D(fifo_sample_count_next[4]),
        .Q(\fifo_sample_count_reg_n_0_[4] ),
        .R(SR));
  LUT6 #(
    .INIT(64'h0EEEEEEEFEEEEEEE)) 
    fifo_valid_i_1
       (.I0(\fifo_sample_count[4]_i_3_n_0 ),
        .I1(\fifo_sample_count_reg_n_0_[4] ),
        .I2(fifo_valid),
        .I3(cache_valid),
        .I4(out_valid_reg_0),
        .I5(AXI4_RREADY),
        .O(Q_next_1));
  FDRE fifo_valid_reg
       (.C(AXI4_ACLK),
        .CE(1'b1),
        .D(Q_next_1),
        .Q(fifo_valid),
        .R(SR));
  (* SOFT_HLUTNM = "soft_lutpair45" *) 
  LUT4 #(
    .INIT(16'hEEFE)) 
    out_valid_i_1
       (.I0(fifo_valid),
        .I1(cache_valid),
        .I2(out_valid_reg_0),
        .I3(AXI4_RREADY),
        .O(Q_next_2));
  FDRE out_valid_reg
       (.C(AXI4_ACLK),
        .CE(1'b1),
        .D(Q_next_2),
        .Q(out_valid_reg_0),
        .R(SR));
  zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_SimpleDualPortRAM_generic u_uz_interlockDeadtime2L_rdfifo_data_classic_ram_generic
       (.AXI4_ACLK(AXI4_ACLK),
        .D(w_out),
        .E(wr_en),
        .\Out_tmp_reg[31] (cache_data),
        .Q(Q),
        .\axi4_raddr_reg[8] (\axi4_raddr_reg[8] ),
        .axi4_rd_active_reg(axi4_rd_active_reg),
        .axi4_rd_active_reg_0(axi4_rd_active_reg_0),
        .\cache_data_reg[31] (w_d1_reg_n_0),
        .\cache_data_reg[31]_0 (w_d2),
        .cache_valid(cache_valid),
        .data_int(data_int),
        .\data_int_reg[1]_0 (\data_int_reg[1] ),
        .\data_int_reg[29]_0 (rd_addr),
        .\data_int_reg[29]_1 (wr_addr),
        .\data_reg_axi_DelayCycles_1_1_reg[9] (\data_reg_axi_DelayCycles_1_1_reg[9] ),
        .data_reg_axi_enable_1_1_i_2(data_reg_axi_enable_1_1_i_2),
        .data_reg_axi_enable_1_1_i_2_0(data_reg_axi_enable_1_1_i_2_0),
        .\fifo_back_indx_reg[3] ({\fifo_sample_count_reg_n_0_[4] ,\fifo_sample_count_reg_n_0_[3] ,\fifo_sample_count_reg_n_0_[2] ,\fifo_sample_count_reg_n_0_[1] ,\fifo_sample_count_reg_n_0_[0] }),
        .rd_active(rd_active),
        .read_reg_axi_fb_InverseBotSwitch(read_reg_axi_fb_InverseBotSwitch),
        .read_reg_axi_fb_enable(read_reg_axi_fb_enable),
        .read_reg_ip_timestamp(read_reg_ip_timestamp),
        .top_rd_enb(top_rd_enb),
        .w_d1_reg(data_out_next),
        .\waddr_reg[11] (\waddr_reg[11] ),
        .\waddr_reg[15] (\waddr_reg[15] ));
  LUT6 #(
    .INIT(64'h2AAA2AAA2AAA0000)) 
    w_d1_i_1
       (.I0(AXI4_ARESETN),
        .I1(fifo_valid),
        .I2(cache_valid),
        .I3(out_valid_reg_0),
        .I4(\fifo_sample_count_reg_n_0_[4] ),
        .I5(\fifo_sample_count[4]_i_3_n_0 ),
        .O(w_d1_i_1_n_0));
  FDRE w_d1_reg
       (.C(AXI4_ACLK),
        .CE(1'b1),
        .D(w_d1_i_1_n_0),
        .Q(w_d1_reg_n_0),
        .R(1'b0));
  FDRE \w_d2_reg[0] 
       (.C(AXI4_ACLK),
        .CE(w_d1_reg_n_0),
        .D(data_int[0]),
        .Q(w_d2[0]),
        .R(SR));
  FDRE \w_d2_reg[10] 
       (.C(AXI4_ACLK),
        .CE(w_d1_reg_n_0),
        .D(data_int[10]),
        .Q(w_d2[10]),
        .R(SR));
  FDRE \w_d2_reg[11] 
       (.C(AXI4_ACLK),
        .CE(w_d1_reg_n_0),
        .D(data_int[11]),
        .Q(w_d2[11]),
        .R(SR));
  FDRE \w_d2_reg[12] 
       (.C(AXI4_ACLK),
        .CE(w_d1_reg_n_0),
        .D(data_int[12]),
        .Q(w_d2[12]),
        .R(SR));
  FDRE \w_d2_reg[13] 
       (.C(AXI4_ACLK),
        .CE(w_d1_reg_n_0),
        .D(data_int[13]),
        .Q(w_d2[13]),
        .R(SR));
  FDRE \w_d2_reg[14] 
       (.C(AXI4_ACLK),
        .CE(w_d1_reg_n_0),
        .D(data_int[14]),
        .Q(w_d2[14]),
        .R(SR));
  FDRE \w_d2_reg[15] 
       (.C(AXI4_ACLK),
        .CE(w_d1_reg_n_0),
        .D(data_int[15]),
        .Q(w_d2[15]),
        .R(SR));
  FDRE \w_d2_reg[16] 
       (.C(AXI4_ACLK),
        .CE(w_d1_reg_n_0),
        .D(data_int[16]),
        .Q(w_d2[16]),
        .R(SR));
  FDRE \w_d2_reg[17] 
       (.C(AXI4_ACLK),
        .CE(w_d1_reg_n_0),
        .D(data_int[17]),
        .Q(w_d2[17]),
        .R(SR));
  FDRE \w_d2_reg[18] 
       (.C(AXI4_ACLK),
        .CE(w_d1_reg_n_0),
        .D(data_int[18]),
        .Q(w_d2[18]),
        .R(SR));
  FDRE \w_d2_reg[19] 
       (.C(AXI4_ACLK),
        .CE(w_d1_reg_n_0),
        .D(data_int[19]),
        .Q(w_d2[19]),
        .R(SR));
  FDRE \w_d2_reg[1] 
       (.C(AXI4_ACLK),
        .CE(w_d1_reg_n_0),
        .D(data_int[1]),
        .Q(w_d2[1]),
        .R(SR));
  FDRE \w_d2_reg[20] 
       (.C(AXI4_ACLK),
        .CE(w_d1_reg_n_0),
        .D(data_int[20]),
        .Q(w_d2[20]),
        .R(SR));
  FDRE \w_d2_reg[21] 
       (.C(AXI4_ACLK),
        .CE(w_d1_reg_n_0),
        .D(data_int[21]),
        .Q(w_d2[21]),
        .R(SR));
  FDRE \w_d2_reg[22] 
       (.C(AXI4_ACLK),
        .CE(w_d1_reg_n_0),
        .D(data_int[22]),
        .Q(w_d2[22]),
        .R(SR));
  FDRE \w_d2_reg[23] 
       (.C(AXI4_ACLK),
        .CE(w_d1_reg_n_0),
        .D(data_int[23]),
        .Q(w_d2[23]),
        .R(SR));
  FDRE \w_d2_reg[24] 
       (.C(AXI4_ACLK),
        .CE(w_d1_reg_n_0),
        .D(data_int[24]),
        .Q(w_d2[24]),
        .R(SR));
  FDRE \w_d2_reg[25] 
       (.C(AXI4_ACLK),
        .CE(w_d1_reg_n_0),
        .D(data_int[25]),
        .Q(w_d2[25]),
        .R(SR));
  FDRE \w_d2_reg[26] 
       (.C(AXI4_ACLK),
        .CE(w_d1_reg_n_0),
        .D(data_int[26]),
        .Q(w_d2[26]),
        .R(SR));
  FDRE \w_d2_reg[27] 
       (.C(AXI4_ACLK),
        .CE(w_d1_reg_n_0),
        .D(data_int[27]),
        .Q(w_d2[27]),
        .R(SR));
  FDRE \w_d2_reg[28] 
       (.C(AXI4_ACLK),
        .CE(w_d1_reg_n_0),
        .D(data_int[28]),
        .Q(w_d2[28]),
        .R(SR));
  FDRE \w_d2_reg[29] 
       (.C(AXI4_ACLK),
        .CE(w_d1_reg_n_0),
        .D(data_int[29]),
        .Q(w_d2[29]),
        .R(SR));
  FDRE \w_d2_reg[2] 
       (.C(AXI4_ACLK),
        .CE(w_d1_reg_n_0),
        .D(data_int[2]),
        .Q(w_d2[2]),
        .R(SR));
  FDRE \w_d2_reg[30] 
       (.C(AXI4_ACLK),
        .CE(w_d1_reg_n_0),
        .D(data_int[30]),
        .Q(w_d2[30]),
        .R(SR));
  FDRE \w_d2_reg[31] 
       (.C(AXI4_ACLK),
        .CE(w_d1_reg_n_0),
        .D(data_int[31]),
        .Q(w_d2[31]),
        .R(SR));
  FDRE \w_d2_reg[3] 
       (.C(AXI4_ACLK),
        .CE(w_d1_reg_n_0),
        .D(data_int[3]),
        .Q(w_d2[3]),
        .R(SR));
  FDRE \w_d2_reg[4] 
       (.C(AXI4_ACLK),
        .CE(w_d1_reg_n_0),
        .D(data_int[4]),
        .Q(w_d2[4]),
        .R(SR));
  FDRE \w_d2_reg[5] 
       (.C(AXI4_ACLK),
        .CE(w_d1_reg_n_0),
        .D(data_int[5]),
        .Q(w_d2[5]),
        .R(SR));
  FDRE \w_d2_reg[6] 
       (.C(AXI4_ACLK),
        .CE(w_d1_reg_n_0),
        .D(data_int[6]),
        .Q(w_d2[6]),
        .R(SR));
  FDRE \w_d2_reg[7] 
       (.C(AXI4_ACLK),
        .CE(w_d1_reg_n_0),
        .D(data_int[7]),
        .Q(w_d2[7]),
        .R(SR));
  FDRE \w_d2_reg[8] 
       (.C(AXI4_ACLK),
        .CE(w_d1_reg_n_0),
        .D(data_int[8]),
        .Q(w_d2[8]),
        .R(SR));
  FDRE \w_d2_reg[9] 
       (.C(AXI4_ACLK),
        .CE(w_d1_reg_n_0),
        .D(data_int[9]),
        .Q(w_d2[9]),
        .R(SR));
endmodule

(* ORIG_REF_NAME = "uz_interlockDeadtime2L_rdfifo_last" *) 
module zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_rdfifo_last
   (AXI4_RLAST,
    SR,
    AXI4_ACLK,
    AXI4_RREADY,
    AXI4_ARESETN,
    top_rd_enb,
    axi4_rlast_1);
  output AXI4_RLAST;
  input [0:0]SR;
  input AXI4_ACLK;
  input AXI4_RREADY;
  input AXI4_ARESETN;
  input top_rd_enb;
  input axi4_rlast_1;

  wire AXI4_ACLK;
  wire AXI4_ARESETN;
  wire AXI4_RLAST;
  wire AXI4_RREADY;
  wire Out_rsvd_i_2_n_0;
  wire Q_next;
  wire Q_next_1;
  wire Q_next_2;
  wire [0:0]SR;
  wire axi4_rlast_1;
  wire cache_data_reg_n_0;
  wire cache_valid;
  wire [3:0]fifo_back_indx0__1;
  wire \fifo_back_indx_reg_n_0_[0] ;
  wire \fifo_back_indx_reg_n_0_[1] ;
  wire \fifo_back_indx_reg_n_0_[2] ;
  wire \fifo_back_indx_reg_n_0_[3] ;
  wire [3:0]fifo_front_indx0__1;
  wire \fifo_front_indx[3]_i_3__0_n_0 ;
  wire \fifo_front_indx_reg_n_0_[0] ;
  wire \fifo_front_indx_reg_n_0_[1] ;
  wire \fifo_front_indx_reg_n_0_[2] ;
  wire \fifo_front_indx_reg_n_0_[3] ;
  wire fifo_read_enable;
  wire \fifo_sample_count[0]_i_1__1_n_0 ;
  wire \fifo_sample_count[1]_i_1__1_n_0 ;
  wire \fifo_sample_count[4]_i_1__1_n_0 ;
  wire \fifo_sample_count[4]_i_3__1_n_0 ;
  wire \fifo_sample_count[4]_i_4__1_n_0 ;
  wire [4:2]fifo_sample_count_next;
  wire \fifo_sample_count_reg_n_0_[0] ;
  wire \fifo_sample_count_reg_n_0_[1] ;
  wire \fifo_sample_count_reg_n_0_[2] ;
  wire \fifo_sample_count_reg_n_0_[3] ;
  wire \fifo_sample_count_reg_n_0_[4] ;
  wire fifo_valid;
  wire out_valid;
  wire top_rd_enb;
  wire u_uz_interlockDeadtime2L_rdfifo_last_classic_ram_singlebit_n_1;
  wire u_uz_interlockDeadtime2L_rdfifo_last_classic_ram_singlebit_n_3;
  wire w_d1_i_1__1_n_0;
  wire w_d1_reg_n_0;
  wire w_d2;
  wire w_out;
  wire wr_en;

  (* SOFT_HLUTNM = "soft_lutpair57" *) 
  LUT2 #(
    .INIT(4'hB)) 
    Out_rsvd_i_2
       (.I0(AXI4_RREADY),
        .I1(out_valid),
        .O(Out_rsvd_i_2_n_0));
  FDRE Out_rsvd_reg
       (.C(AXI4_ACLK),
        .CE(1'b1),
        .D(u_uz_interlockDeadtime2L_rdfifo_last_classic_ram_singlebit_n_3),
        .Q(AXI4_RLAST),
        .R(SR));
  FDRE cache_data_reg
       (.C(AXI4_ACLK),
        .CE(1'b1),
        .D(u_uz_interlockDeadtime2L_rdfifo_last_classic_ram_singlebit_n_1),
        .Q(cache_data_reg_n_0),
        .R(SR));
  (* SOFT_HLUTNM = "soft_lutpair53" *) 
  LUT4 #(
    .INIT(16'hF440)) 
    cache_valid_i_1__1
       (.I0(AXI4_RREADY),
        .I1(out_valid),
        .I2(fifo_valid),
        .I3(cache_valid),
        .O(Q_next));
  FDRE cache_valid_reg
       (.C(AXI4_ACLK),
        .CE(1'b1),
        .D(Q_next),
        .Q(cache_valid),
        .R(SR));
  (* SOFT_HLUTNM = "soft_lutpair58" *) 
  LUT1 #(
    .INIT(2'h1)) 
    \fifo_back_indx[0]_i_1__1 
       (.I0(\fifo_back_indx_reg_n_0_[0] ),
        .O(fifo_back_indx0__1[0]));
  (* SOFT_HLUTNM = "soft_lutpair58" *) 
  LUT2 #(
    .INIT(4'h6)) 
    \fifo_back_indx[1]_i_1__1 
       (.I0(\fifo_back_indx_reg_n_0_[0] ),
        .I1(\fifo_back_indx_reg_n_0_[1] ),
        .O(fifo_back_indx0__1[1]));
  (* SOFT_HLUTNM = "soft_lutpair55" *) 
  LUT3 #(
    .INIT(8'h78)) 
    \fifo_back_indx[2]_i_1__1 
       (.I0(\fifo_back_indx_reg_n_0_[1] ),
        .I1(\fifo_back_indx_reg_n_0_[0] ),
        .I2(\fifo_back_indx_reg_n_0_[2] ),
        .O(fifo_back_indx0__1[2]));
  (* SOFT_HLUTNM = "soft_lutpair55" *) 
  LUT4 #(
    .INIT(16'h7F80)) 
    \fifo_back_indx[3]_i_1__1 
       (.I0(\fifo_back_indx_reg_n_0_[0] ),
        .I1(\fifo_back_indx_reg_n_0_[1] ),
        .I2(\fifo_back_indx_reg_n_0_[2] ),
        .I3(\fifo_back_indx_reg_n_0_[3] ),
        .O(fifo_back_indx0__1[3]));
  FDRE \fifo_back_indx_reg[0] 
       (.C(AXI4_ACLK),
        .CE(wr_en),
        .D(fifo_back_indx0__1[0]),
        .Q(\fifo_back_indx_reg_n_0_[0] ),
        .R(SR));
  FDRE \fifo_back_indx_reg[1] 
       (.C(AXI4_ACLK),
        .CE(wr_en),
        .D(fifo_back_indx0__1[1]),
        .Q(\fifo_back_indx_reg_n_0_[1] ),
        .R(SR));
  FDRE \fifo_back_indx_reg[2] 
       (.C(AXI4_ACLK),
        .CE(wr_en),
        .D(fifo_back_indx0__1[2]),
        .Q(\fifo_back_indx_reg_n_0_[2] ),
        .R(SR));
  FDRE \fifo_back_indx_reg[3] 
       (.C(AXI4_ACLK),
        .CE(wr_en),
        .D(fifo_back_indx0__1[3]),
        .Q(\fifo_back_indx_reg_n_0_[3] ),
        .R(SR));
  (* SOFT_HLUTNM = "soft_lutpair59" *) 
  LUT1 #(
    .INIT(2'h1)) 
    \fifo_front_indx[0]_i_1__1 
       (.I0(\fifo_front_indx_reg_n_0_[0] ),
        .O(fifo_front_indx0__1[0]));
  (* SOFT_HLUTNM = "soft_lutpair59" *) 
  LUT2 #(
    .INIT(4'h6)) 
    \fifo_front_indx[1]_i_1__1 
       (.I0(\fifo_front_indx_reg_n_0_[0] ),
        .I1(\fifo_front_indx_reg_n_0_[1] ),
        .O(fifo_front_indx0__1[1]));
  (* SOFT_HLUTNM = "soft_lutpair56" *) 
  LUT3 #(
    .INIT(8'h78)) 
    \fifo_front_indx[2]_i_1__1 
       (.I0(\fifo_front_indx_reg_n_0_[1] ),
        .I1(\fifo_front_indx_reg_n_0_[0] ),
        .I2(\fifo_front_indx_reg_n_0_[2] ),
        .O(fifo_front_indx0__1[2]));
  LUT6 #(
    .INIT(64'hFFFFFFFE00000000)) 
    \fifo_front_indx[3]_i_1__1 
       (.I0(\fifo_sample_count_reg_n_0_[4] ),
        .I1(\fifo_sample_count_reg_n_0_[2] ),
        .I2(\fifo_sample_count_reg_n_0_[0] ),
        .I3(\fifo_sample_count_reg_n_0_[1] ),
        .I4(\fifo_sample_count_reg_n_0_[3] ),
        .I5(\fifo_front_indx[3]_i_3__0_n_0 ),
        .O(fifo_read_enable));
  (* SOFT_HLUTNM = "soft_lutpair56" *) 
  LUT4 #(
    .INIT(16'h7F80)) 
    \fifo_front_indx[3]_i_2__1 
       (.I0(\fifo_front_indx_reg_n_0_[0] ),
        .I1(\fifo_front_indx_reg_n_0_[1] ),
        .I2(\fifo_front_indx_reg_n_0_[2] ),
        .I3(\fifo_front_indx_reg_n_0_[3] ),
        .O(fifo_front_indx0__1[3]));
  (* SOFT_HLUTNM = "soft_lutpair57" *) 
  LUT3 #(
    .INIT(8'h7F)) 
    \fifo_front_indx[3]_i_3__0 
       (.I0(fifo_valid),
        .I1(cache_valid),
        .I2(out_valid),
        .O(\fifo_front_indx[3]_i_3__0_n_0 ));
  FDRE \fifo_front_indx_reg[0] 
       (.C(AXI4_ACLK),
        .CE(fifo_read_enable),
        .D(fifo_front_indx0__1[0]),
        .Q(\fifo_front_indx_reg_n_0_[0] ),
        .R(SR));
  FDRE \fifo_front_indx_reg[1] 
       (.C(AXI4_ACLK),
        .CE(fifo_read_enable),
        .D(fifo_front_indx0__1[1]),
        .Q(\fifo_front_indx_reg_n_0_[1] ),
        .R(SR));
  FDRE \fifo_front_indx_reg[2] 
       (.C(AXI4_ACLK),
        .CE(fifo_read_enable),
        .D(fifo_front_indx0__1[2]),
        .Q(\fifo_front_indx_reg_n_0_[2] ),
        .R(SR));
  FDRE \fifo_front_indx_reg[3] 
       (.C(AXI4_ACLK),
        .CE(fifo_read_enable),
        .D(fifo_front_indx0__1[3]),
        .Q(\fifo_front_indx_reg_n_0_[3] ),
        .R(SR));
  LUT1 #(
    .INIT(2'h1)) 
    \fifo_sample_count[0]_i_1__1 
       (.I0(\fifo_sample_count_reg_n_0_[0] ),
        .O(\fifo_sample_count[0]_i_1__1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair54" *) 
  LUT3 #(
    .INIT(8'h96)) 
    \fifo_sample_count[1]_i_1__1 
       (.I0(\fifo_sample_count[4]_i_4__1_n_0 ),
        .I1(\fifo_sample_count_reg_n_0_[1] ),
        .I2(\fifo_sample_count_reg_n_0_[0] ),
        .O(\fifo_sample_count[1]_i_1__1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair52" *) 
  LUT4 #(
    .INIT(16'hBD42)) 
    \fifo_sample_count[2]_i_1__1 
       (.I0(\fifo_sample_count[4]_i_4__1_n_0 ),
        .I1(\fifo_sample_count_reg_n_0_[1] ),
        .I2(\fifo_sample_count_reg_n_0_[0] ),
        .I3(\fifo_sample_count_reg_n_0_[2] ),
        .O(fifo_sample_count_next[2]));
  (* SOFT_HLUTNM = "soft_lutpair52" *) 
  LUT5 #(
    .INIT(32'hBFFD4002)) 
    \fifo_sample_count[3]_i_1__1 
       (.I0(\fifo_sample_count[4]_i_4__1_n_0 ),
        .I1(\fifo_sample_count_reg_n_0_[0] ),
        .I2(\fifo_sample_count_reg_n_0_[1] ),
        .I3(\fifo_sample_count_reg_n_0_[2] ),
        .I4(\fifo_sample_count_reg_n_0_[3] ),
        .O(fifo_sample_count_next[3]));
  LUT6 #(
    .INIT(64'h8A76767676767676)) 
    \fifo_sample_count[4]_i_1__1 
       (.I0(top_rd_enb),
        .I1(\fifo_sample_count[4]_i_3__1_n_0 ),
        .I2(\fifo_sample_count_reg_n_0_[4] ),
        .I3(fifo_valid),
        .I4(cache_valid),
        .I5(out_valid),
        .O(\fifo_sample_count[4]_i_1__1_n_0 ));
  LUT6 #(
    .INIT(64'hBFFFFFFD40000002)) 
    \fifo_sample_count[4]_i_2__1 
       (.I0(\fifo_sample_count[4]_i_4__1_n_0 ),
        .I1(\fifo_sample_count_reg_n_0_[2] ),
        .I2(\fifo_sample_count_reg_n_0_[3] ),
        .I3(\fifo_sample_count_reg_n_0_[0] ),
        .I4(\fifo_sample_count_reg_n_0_[1] ),
        .I5(\fifo_sample_count_reg_n_0_[4] ),
        .O(fifo_sample_count_next[4]));
  (* SOFT_HLUTNM = "soft_lutpair54" *) 
  LUT4 #(
    .INIT(16'hFFFE)) 
    \fifo_sample_count[4]_i_3__1 
       (.I0(\fifo_sample_count_reg_n_0_[2] ),
        .I1(\fifo_sample_count_reg_n_0_[0] ),
        .I2(\fifo_sample_count_reg_n_0_[1] ),
        .I3(\fifo_sample_count_reg_n_0_[3] ),
        .O(\fifo_sample_count[4]_i_3__1_n_0 ));
  LUT6 #(
    .INIT(64'h2EEEEEEEFFFFFFFF)) 
    \fifo_sample_count[4]_i_4__1 
       (.I0(\fifo_sample_count_reg_n_0_[4] ),
        .I1(\fifo_sample_count[4]_i_3__1_n_0 ),
        .I2(fifo_valid),
        .I3(cache_valid),
        .I4(out_valid),
        .I5(top_rd_enb),
        .O(\fifo_sample_count[4]_i_4__1_n_0 ));
  FDRE \fifo_sample_count_reg[0] 
       (.C(AXI4_ACLK),
        .CE(\fifo_sample_count[4]_i_1__1_n_0 ),
        .D(\fifo_sample_count[0]_i_1__1_n_0 ),
        .Q(\fifo_sample_count_reg_n_0_[0] ),
        .R(SR));
  FDRE \fifo_sample_count_reg[1] 
       (.C(AXI4_ACLK),
        .CE(\fifo_sample_count[4]_i_1__1_n_0 ),
        .D(\fifo_sample_count[1]_i_1__1_n_0 ),
        .Q(\fifo_sample_count_reg_n_0_[1] ),
        .R(SR));
  FDRE \fifo_sample_count_reg[2] 
       (.C(AXI4_ACLK),
        .CE(\fifo_sample_count[4]_i_1__1_n_0 ),
        .D(fifo_sample_count_next[2]),
        .Q(\fifo_sample_count_reg_n_0_[2] ),
        .R(SR));
  FDRE \fifo_sample_count_reg[3] 
       (.C(AXI4_ACLK),
        .CE(\fifo_sample_count[4]_i_1__1_n_0 ),
        .D(fifo_sample_count_next[3]),
        .Q(\fifo_sample_count_reg_n_0_[3] ),
        .R(SR));
  FDRE \fifo_sample_count_reg[4] 
       (.C(AXI4_ACLK),
        .CE(\fifo_sample_count[4]_i_1__1_n_0 ),
        .D(fifo_sample_count_next[4]),
        .Q(\fifo_sample_count_reg_n_0_[4] ),
        .R(SR));
  LUT6 #(
    .INIT(64'h0EEEEEEEFEEEEEEE)) 
    fifo_valid_i_1__1
       (.I0(\fifo_sample_count[4]_i_3__1_n_0 ),
        .I1(\fifo_sample_count_reg_n_0_[4] ),
        .I2(fifo_valid),
        .I3(cache_valid),
        .I4(out_valid),
        .I5(AXI4_RREADY),
        .O(Q_next_1));
  FDRE fifo_valid_reg
       (.C(AXI4_ACLK),
        .CE(1'b1),
        .D(Q_next_1),
        .Q(fifo_valid),
        .R(SR));
  (* SOFT_HLUTNM = "soft_lutpair53" *) 
  LUT4 #(
    .INIT(16'hEEFE)) 
    out_valid_i_1__1
       (.I0(fifo_valid),
        .I1(cache_valid),
        .I2(out_valid),
        .I3(AXI4_RREADY),
        .O(Q_next_2));
  FDRE out_valid_reg
       (.C(AXI4_ACLK),
        .CE(1'b1),
        .D(Q_next_2),
        .Q(out_valid),
        .R(SR));
  zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_SimpleDualPortRAM_singlebit u_uz_interlockDeadtime2L_rdfifo_last_classic_ram_singlebit
       (.AXI4_ACLK(AXI4_ACLK),
        .AXI4_RLAST(AXI4_RLAST),
        .AXI4_RREADY(AXI4_RREADY),
        .AXI4_RREADY_0(u_uz_interlockDeadtime2L_rdfifo_last_classic_ram_singlebit_n_1),
        .E(wr_en),
        .Out_rsvd_reg(Out_rsvd_i_2_n_0),
        .Q({\fifo_sample_count_reg_n_0_[4] ,\fifo_sample_count_reg_n_0_[3] ,\fifo_sample_count_reg_n_0_[2] ,\fifo_sample_count_reg_n_0_[1] ,\fifo_sample_count_reg_n_0_[0] }),
        .axi4_rlast_1(axi4_rlast_1),
        .cache_data_reg(u_uz_interlockDeadtime2L_rdfifo_last_classic_ram_singlebit_n_3),
        .cache_data_reg_0(cache_data_reg_n_0),
        .cache_valid(cache_valid),
        .data_int_reg_0({\fifo_back_indx_reg_n_0_[3] ,\fifo_back_indx_reg_n_0_[2] ,\fifo_back_indx_reg_n_0_[1] ,\fifo_back_indx_reg_n_0_[0] }),
        .data_int_reg_1({\fifo_front_indx_reg_n_0_[3] ,\fifo_front_indx_reg_n_0_[2] ,\fifo_front_indx_reg_n_0_[1] ,\fifo_front_indx_reg_n_0_[0] }),
        .fifo_valid(fifo_valid),
        .out_valid(out_valid),
        .top_rd_enb(top_rd_enb),
        .w_d2(w_d2),
        .w_d2_reg(w_d1_reg_n_0),
        .w_out(w_out));
  LUT6 #(
    .INIT(64'h2AAA2AAA2AAA0000)) 
    w_d1_i_1__1
       (.I0(AXI4_ARESETN),
        .I1(fifo_valid),
        .I2(cache_valid),
        .I3(out_valid),
        .I4(\fifo_sample_count_reg_n_0_[4] ),
        .I5(\fifo_sample_count[4]_i_3__1_n_0 ),
        .O(w_d1_i_1__1_n_0));
  FDRE w_d1_reg
       (.C(AXI4_ACLK),
        .CE(1'b1),
        .D(w_d1_i_1__1_n_0),
        .Q(w_d1_reg_n_0),
        .R(1'b0));
  FDRE w_d2_reg
       (.C(AXI4_ACLK),
        .CE(1'b1),
        .D(w_out),
        .Q(w_d2),
        .R(SR));
endmodule

(* ORIG_REF_NAME = "uz_interlockDeadtime2L_rdfifo_rid" *) 
module zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_rdfifo_rid
   (AXI4_RID,
    SR,
    AXI4_ACLK,
    top_rd_enb,
    AXI4_RREADY,
    AXI4_ARESETN,
    Q);
  output [11:0]AXI4_RID;
  input [0:0]SR;
  input AXI4_ACLK;
  input top_rd_enb;
  input AXI4_RREADY;
  input AXI4_ARESETN;
  input [11:0]Q;

  wire AXI4_ACLK;
  wire AXI4_ARESETN;
  wire [11:0]AXI4_RID;
  wire AXI4_RREADY;
  wire [11:0]Q;
  wire Q_next;
  wire Q_next_1;
  wire Q_next_2;
  wire [0:0]SR;
  wire \cache_data_reg_n_0_[0] ;
  wire \cache_data_reg_n_0_[10] ;
  wire \cache_data_reg_n_0_[11] ;
  wire \cache_data_reg_n_0_[1] ;
  wire \cache_data_reg_n_0_[2] ;
  wire \cache_data_reg_n_0_[3] ;
  wire \cache_data_reg_n_0_[4] ;
  wire \cache_data_reg_n_0_[5] ;
  wire \cache_data_reg_n_0_[6] ;
  wire \cache_data_reg_n_0_[7] ;
  wire \cache_data_reg_n_0_[8] ;
  wire \cache_data_reg_n_0_[9] ;
  wire cache_valid;
  wire cache_wr_en;
  wire [3:0]fifo_back_indx0__0;
  wire \fifo_back_indx_reg_n_0_[0] ;
  wire \fifo_back_indx_reg_n_0_[1] ;
  wire \fifo_back_indx_reg_n_0_[2] ;
  wire \fifo_back_indx_reg_n_0_[3] ;
  wire [3:0]fifo_front_indx0__0;
  wire \fifo_front_indx_reg_n_0_[0] ;
  wire \fifo_front_indx_reg_n_0_[1] ;
  wire \fifo_front_indx_reg_n_0_[2] ;
  wire \fifo_front_indx_reg_n_0_[3] ;
  wire fifo_read_enable;
  wire \fifo_sample_count[0]_i_1__0_n_0 ;
  wire \fifo_sample_count[1]_i_1__0_n_0 ;
  wire \fifo_sample_count[1]_i_2_n_0 ;
  wire \fifo_sample_count[4]_i_1__0_n_0 ;
  wire \fifo_sample_count[4]_i_3__0_n_0 ;
  wire \fifo_sample_count[4]_i_4__0_n_0 ;
  wire [4:2]fifo_sample_count_next;
  wire \fifo_sample_count_reg_n_0_[0] ;
  wire \fifo_sample_count_reg_n_0_[1] ;
  wire \fifo_sample_count_reg_n_0_[2] ;
  wire \fifo_sample_count_reg_n_0_[3] ;
  wire \fifo_sample_count_reg_n_0_[4] ;
  wire fifo_valid;
  wire out_valid;
  wire out_wr_en;
  wire top_rd_enb;
  wire u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_1;
  wire u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_10;
  wire u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_11;
  wire u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_12;
  wire u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_13;
  wire u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_14;
  wire u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_15;
  wire u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_16;
  wire u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_17;
  wire u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_18;
  wire u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_19;
  wire u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_2;
  wire u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_20;
  wire u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_21;
  wire u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_22;
  wire u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_23;
  wire u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_24;
  wire u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_25;
  wire u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_26;
  wire u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_27;
  wire u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_28;
  wire u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_29;
  wire u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_3;
  wire u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_30;
  wire u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_31;
  wire u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_32;
  wire u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_33;
  wire u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_34;
  wire u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_35;
  wire u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_36;
  wire u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_4;
  wire u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_5;
  wire u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_6;
  wire u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_7;
  wire u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_8;
  wire u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_9;
  wire w_d1_i_1__0_n_0;
  wire w_d1_reg_n_0;
  wire \w_d2_reg_n_0_[0] ;
  wire \w_d2_reg_n_0_[10] ;
  wire \w_d2_reg_n_0_[11] ;
  wire \w_d2_reg_n_0_[1] ;
  wire \w_d2_reg_n_0_[2] ;
  wire \w_d2_reg_n_0_[3] ;
  wire \w_d2_reg_n_0_[4] ;
  wire \w_d2_reg_n_0_[5] ;
  wire \w_d2_reg_n_0_[6] ;
  wire \w_d2_reg_n_0_[7] ;
  wire \w_d2_reg_n_0_[8] ;
  wire \w_d2_reg_n_0_[9] ;
  wire wr_en;

  LUT4 #(
    .INIT(16'hEE0E)) 
    \Out_tmp[11]_i_1 
       (.I0(fifo_valid),
        .I1(cache_valid),
        .I2(out_valid),
        .I3(AXI4_RREADY),
        .O(out_wr_en));
  FDRE \Out_tmp_reg[0] 
       (.C(AXI4_ACLK),
        .CE(out_wr_en),
        .D(u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_36),
        .Q(AXI4_RID[0]),
        .R(SR));
  FDRE \Out_tmp_reg[10] 
       (.C(AXI4_ACLK),
        .CE(out_wr_en),
        .D(u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_26),
        .Q(AXI4_RID[10]),
        .R(SR));
  FDRE \Out_tmp_reg[11] 
       (.C(AXI4_ACLK),
        .CE(out_wr_en),
        .D(u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_25),
        .Q(AXI4_RID[11]),
        .R(SR));
  FDRE \Out_tmp_reg[1] 
       (.C(AXI4_ACLK),
        .CE(out_wr_en),
        .D(u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_35),
        .Q(AXI4_RID[1]),
        .R(SR));
  FDRE \Out_tmp_reg[2] 
       (.C(AXI4_ACLK),
        .CE(out_wr_en),
        .D(u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_34),
        .Q(AXI4_RID[2]),
        .R(SR));
  FDRE \Out_tmp_reg[3] 
       (.C(AXI4_ACLK),
        .CE(out_wr_en),
        .D(u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_33),
        .Q(AXI4_RID[3]),
        .R(SR));
  FDRE \Out_tmp_reg[4] 
       (.C(AXI4_ACLK),
        .CE(out_wr_en),
        .D(u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_32),
        .Q(AXI4_RID[4]),
        .R(SR));
  FDRE \Out_tmp_reg[5] 
       (.C(AXI4_ACLK),
        .CE(out_wr_en),
        .D(u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_31),
        .Q(AXI4_RID[5]),
        .R(SR));
  FDRE \Out_tmp_reg[6] 
       (.C(AXI4_ACLK),
        .CE(out_wr_en),
        .D(u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_30),
        .Q(AXI4_RID[6]),
        .R(SR));
  FDRE \Out_tmp_reg[7] 
       (.C(AXI4_ACLK),
        .CE(out_wr_en),
        .D(u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_29),
        .Q(AXI4_RID[7]),
        .R(SR));
  FDRE \Out_tmp_reg[8] 
       (.C(AXI4_ACLK),
        .CE(out_wr_en),
        .D(u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_28),
        .Q(AXI4_RID[8]),
        .R(SR));
  FDRE \Out_tmp_reg[9] 
       (.C(AXI4_ACLK),
        .CE(out_wr_en),
        .D(u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_27),
        .Q(AXI4_RID[9]),
        .R(SR));
  LUT4 #(
    .INIT(16'hB040)) 
    \cache_data[11]_i_1 
       (.I0(AXI4_RREADY),
        .I1(out_valid),
        .I2(fifo_valid),
        .I3(cache_valid),
        .O(cache_wr_en));
  FDRE \cache_data_reg[0] 
       (.C(AXI4_ACLK),
        .CE(cache_wr_en),
        .D(u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_12),
        .Q(\cache_data_reg_n_0_[0] ),
        .R(SR));
  FDRE \cache_data_reg[10] 
       (.C(AXI4_ACLK),
        .CE(cache_wr_en),
        .D(u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_2),
        .Q(\cache_data_reg_n_0_[10] ),
        .R(SR));
  FDRE \cache_data_reg[11] 
       (.C(AXI4_ACLK),
        .CE(cache_wr_en),
        .D(u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_1),
        .Q(\cache_data_reg_n_0_[11] ),
        .R(SR));
  FDRE \cache_data_reg[1] 
       (.C(AXI4_ACLK),
        .CE(cache_wr_en),
        .D(u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_11),
        .Q(\cache_data_reg_n_0_[1] ),
        .R(SR));
  FDRE \cache_data_reg[2] 
       (.C(AXI4_ACLK),
        .CE(cache_wr_en),
        .D(u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_10),
        .Q(\cache_data_reg_n_0_[2] ),
        .R(SR));
  FDRE \cache_data_reg[3] 
       (.C(AXI4_ACLK),
        .CE(cache_wr_en),
        .D(u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_9),
        .Q(\cache_data_reg_n_0_[3] ),
        .R(SR));
  FDRE \cache_data_reg[4] 
       (.C(AXI4_ACLK),
        .CE(cache_wr_en),
        .D(u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_8),
        .Q(\cache_data_reg_n_0_[4] ),
        .R(SR));
  FDRE \cache_data_reg[5] 
       (.C(AXI4_ACLK),
        .CE(cache_wr_en),
        .D(u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_7),
        .Q(\cache_data_reg_n_0_[5] ),
        .R(SR));
  FDRE \cache_data_reg[6] 
       (.C(AXI4_ACLK),
        .CE(cache_wr_en),
        .D(u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_6),
        .Q(\cache_data_reg_n_0_[6] ),
        .R(SR));
  FDRE \cache_data_reg[7] 
       (.C(AXI4_ACLK),
        .CE(cache_wr_en),
        .D(u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_5),
        .Q(\cache_data_reg_n_0_[7] ),
        .R(SR));
  FDRE \cache_data_reg[8] 
       (.C(AXI4_ACLK),
        .CE(cache_wr_en),
        .D(u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_4),
        .Q(\cache_data_reg_n_0_[8] ),
        .R(SR));
  FDRE \cache_data_reg[9] 
       (.C(AXI4_ACLK),
        .CE(cache_wr_en),
        .D(u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_3),
        .Q(\cache_data_reg_n_0_[9] ),
        .R(SR));
  (* SOFT_HLUTNM = "soft_lutpair73" *) 
  LUT4 #(
    .INIT(16'hF440)) 
    cache_valid_i_1__0
       (.I0(AXI4_RREADY),
        .I1(out_valid),
        .I2(fifo_valid),
        .I3(cache_valid),
        .O(Q_next));
  FDRE cache_valid_reg
       (.C(AXI4_ACLK),
        .CE(1'b1),
        .D(Q_next),
        .Q(cache_valid),
        .R(SR));
  (* SOFT_HLUTNM = "soft_lutpair77" *) 
  LUT1 #(
    .INIT(2'h1)) 
    \fifo_back_indx[0]_i_1__0 
       (.I0(\fifo_back_indx_reg_n_0_[0] ),
        .O(fifo_back_indx0__0[0]));
  (* SOFT_HLUTNM = "soft_lutpair77" *) 
  LUT2 #(
    .INIT(4'h6)) 
    \fifo_back_indx[1]_i_1__0 
       (.I0(\fifo_back_indx_reg_n_0_[0] ),
        .I1(\fifo_back_indx_reg_n_0_[1] ),
        .O(fifo_back_indx0__0[1]));
  (* SOFT_HLUTNM = "soft_lutpair75" *) 
  LUT3 #(
    .INIT(8'h78)) 
    \fifo_back_indx[2]_i_1__0 
       (.I0(\fifo_back_indx_reg_n_0_[1] ),
        .I1(\fifo_back_indx_reg_n_0_[0] ),
        .I2(\fifo_back_indx_reg_n_0_[2] ),
        .O(fifo_back_indx0__0[2]));
  (* SOFT_HLUTNM = "soft_lutpair75" *) 
  LUT4 #(
    .INIT(16'h7F80)) 
    \fifo_back_indx[3]_i_1__0 
       (.I0(\fifo_back_indx_reg_n_0_[0] ),
        .I1(\fifo_back_indx_reg_n_0_[1] ),
        .I2(\fifo_back_indx_reg_n_0_[2] ),
        .I3(\fifo_back_indx_reg_n_0_[3] ),
        .O(fifo_back_indx0__0[3]));
  FDRE \fifo_back_indx_reg[0] 
       (.C(AXI4_ACLK),
        .CE(wr_en),
        .D(fifo_back_indx0__0[0]),
        .Q(\fifo_back_indx_reg_n_0_[0] ),
        .R(SR));
  FDRE \fifo_back_indx_reg[1] 
       (.C(AXI4_ACLK),
        .CE(wr_en),
        .D(fifo_back_indx0__0[1]),
        .Q(\fifo_back_indx_reg_n_0_[1] ),
        .R(SR));
  FDRE \fifo_back_indx_reg[2] 
       (.C(AXI4_ACLK),
        .CE(wr_en),
        .D(fifo_back_indx0__0[2]),
        .Q(\fifo_back_indx_reg_n_0_[2] ),
        .R(SR));
  FDRE \fifo_back_indx_reg[3] 
       (.C(AXI4_ACLK),
        .CE(wr_en),
        .D(fifo_back_indx0__0[3]),
        .Q(\fifo_back_indx_reg_n_0_[3] ),
        .R(SR));
  (* SOFT_HLUTNM = "soft_lutpair78" *) 
  LUT1 #(
    .INIT(2'h1)) 
    \fifo_front_indx[0]_i_1__0 
       (.I0(\fifo_front_indx_reg_n_0_[0] ),
        .O(fifo_front_indx0__0[0]));
  (* SOFT_HLUTNM = "soft_lutpair78" *) 
  LUT2 #(
    .INIT(4'h6)) 
    \fifo_front_indx[1]_i_1__0 
       (.I0(\fifo_front_indx_reg_n_0_[0] ),
        .I1(\fifo_front_indx_reg_n_0_[1] ),
        .O(fifo_front_indx0__0[1]));
  (* SOFT_HLUTNM = "soft_lutpair76" *) 
  LUT3 #(
    .INIT(8'h78)) 
    \fifo_front_indx[2]_i_1__0 
       (.I0(\fifo_front_indx_reg_n_0_[1] ),
        .I1(\fifo_front_indx_reg_n_0_[0] ),
        .I2(\fifo_front_indx_reg_n_0_[2] ),
        .O(fifo_front_indx0__0[2]));
  LUT6 #(
    .INIT(64'hFFFFFFFE00000000)) 
    \fifo_front_indx[3]_i_1__0 
       (.I0(\fifo_sample_count_reg_n_0_[4] ),
        .I1(\fifo_sample_count_reg_n_0_[2] ),
        .I2(\fifo_sample_count_reg_n_0_[0] ),
        .I3(\fifo_sample_count_reg_n_0_[1] ),
        .I4(\fifo_sample_count_reg_n_0_[3] ),
        .I5(\fifo_sample_count[1]_i_2_n_0 ),
        .O(fifo_read_enable));
  (* SOFT_HLUTNM = "soft_lutpair76" *) 
  LUT4 #(
    .INIT(16'h7F80)) 
    \fifo_front_indx[3]_i_2__0 
       (.I0(\fifo_front_indx_reg_n_0_[0] ),
        .I1(\fifo_front_indx_reg_n_0_[1] ),
        .I2(\fifo_front_indx_reg_n_0_[2] ),
        .I3(\fifo_front_indx_reg_n_0_[3] ),
        .O(fifo_front_indx0__0[3]));
  FDRE \fifo_front_indx_reg[0] 
       (.C(AXI4_ACLK),
        .CE(fifo_read_enable),
        .D(fifo_front_indx0__0[0]),
        .Q(\fifo_front_indx_reg_n_0_[0] ),
        .R(SR));
  FDRE \fifo_front_indx_reg[1] 
       (.C(AXI4_ACLK),
        .CE(fifo_read_enable),
        .D(fifo_front_indx0__0[1]),
        .Q(\fifo_front_indx_reg_n_0_[1] ),
        .R(SR));
  FDRE \fifo_front_indx_reg[2] 
       (.C(AXI4_ACLK),
        .CE(fifo_read_enable),
        .D(fifo_front_indx0__0[2]),
        .Q(\fifo_front_indx_reg_n_0_[2] ),
        .R(SR));
  FDRE \fifo_front_indx_reg[3] 
       (.C(AXI4_ACLK),
        .CE(fifo_read_enable),
        .D(fifo_front_indx0__0[3]),
        .Q(\fifo_front_indx_reg_n_0_[3] ),
        .R(SR));
  (* SOFT_HLUTNM = "soft_lutpair74" *) 
  LUT1 #(
    .INIT(2'h1)) 
    \fifo_sample_count[0]_i_1__0 
       (.I0(\fifo_sample_count_reg_n_0_[0] ),
        .O(\fifo_sample_count[0]_i_1__0_n_0 ));
  LUT6 #(
    .INIT(64'hDFD5202A202ADFD5)) 
    \fifo_sample_count[1]_i_1__0 
       (.I0(top_rd_enb),
        .I1(\fifo_sample_count[1]_i_2_n_0 ),
        .I2(\fifo_sample_count[4]_i_3__0_n_0 ),
        .I3(\fifo_sample_count_reg_n_0_[4] ),
        .I4(\fifo_sample_count_reg_n_0_[1] ),
        .I5(\fifo_sample_count_reg_n_0_[0] ),
        .O(\fifo_sample_count[1]_i_1__0_n_0 ));
  LUT3 #(
    .INIT(8'h7F)) 
    \fifo_sample_count[1]_i_2 
       (.I0(fifo_valid),
        .I1(cache_valid),
        .I2(out_valid),
        .O(\fifo_sample_count[1]_i_2_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair72" *) 
  LUT4 #(
    .INIT(16'hBD42)) 
    \fifo_sample_count[2]_i_1__0 
       (.I0(\fifo_sample_count[4]_i_4__0_n_0 ),
        .I1(\fifo_sample_count_reg_n_0_[1] ),
        .I2(\fifo_sample_count_reg_n_0_[0] ),
        .I3(\fifo_sample_count_reg_n_0_[2] ),
        .O(fifo_sample_count_next[2]));
  (* SOFT_HLUTNM = "soft_lutpair72" *) 
  LUT5 #(
    .INIT(32'hBFFD4002)) 
    \fifo_sample_count[3]_i_1__0 
       (.I0(\fifo_sample_count[4]_i_4__0_n_0 ),
        .I1(\fifo_sample_count_reg_n_0_[0] ),
        .I2(\fifo_sample_count_reg_n_0_[1] ),
        .I3(\fifo_sample_count_reg_n_0_[2] ),
        .I4(\fifo_sample_count_reg_n_0_[3] ),
        .O(fifo_sample_count_next[3]));
  LUT6 #(
    .INIT(64'h807F807F7F7FFF00)) 
    \fifo_sample_count[4]_i_1__0 
       (.I0(fifo_valid),
        .I1(cache_valid),
        .I2(out_valid),
        .I3(top_rd_enb),
        .I4(\fifo_sample_count_reg_n_0_[4] ),
        .I5(\fifo_sample_count[4]_i_3__0_n_0 ),
        .O(\fifo_sample_count[4]_i_1__0_n_0 ));
  LUT6 #(
    .INIT(64'hBFFFFFFD40000002)) 
    \fifo_sample_count[4]_i_2__0 
       (.I0(\fifo_sample_count[4]_i_4__0_n_0 ),
        .I1(\fifo_sample_count_reg_n_0_[2] ),
        .I2(\fifo_sample_count_reg_n_0_[3] ),
        .I3(\fifo_sample_count_reg_n_0_[0] ),
        .I4(\fifo_sample_count_reg_n_0_[1] ),
        .I5(\fifo_sample_count_reg_n_0_[4] ),
        .O(fifo_sample_count_next[4]));
  (* SOFT_HLUTNM = "soft_lutpair74" *) 
  LUT4 #(
    .INIT(16'hFFFE)) 
    \fifo_sample_count[4]_i_3__0 
       (.I0(\fifo_sample_count_reg_n_0_[2] ),
        .I1(\fifo_sample_count_reg_n_0_[0] ),
        .I2(\fifo_sample_count_reg_n_0_[1] ),
        .I3(\fifo_sample_count_reg_n_0_[3] ),
        .O(\fifo_sample_count[4]_i_3__0_n_0 ));
  LUT6 #(
    .INIT(64'h2EEEEEEEFFFFFFFF)) 
    \fifo_sample_count[4]_i_4__0 
       (.I0(\fifo_sample_count_reg_n_0_[4] ),
        .I1(\fifo_sample_count[4]_i_3__0_n_0 ),
        .I2(fifo_valid),
        .I3(cache_valid),
        .I4(out_valid),
        .I5(top_rd_enb),
        .O(\fifo_sample_count[4]_i_4__0_n_0 ));
  FDRE \fifo_sample_count_reg[0] 
       (.C(AXI4_ACLK),
        .CE(\fifo_sample_count[4]_i_1__0_n_0 ),
        .D(\fifo_sample_count[0]_i_1__0_n_0 ),
        .Q(\fifo_sample_count_reg_n_0_[0] ),
        .R(SR));
  FDRE \fifo_sample_count_reg[1] 
       (.C(AXI4_ACLK),
        .CE(\fifo_sample_count[4]_i_1__0_n_0 ),
        .D(\fifo_sample_count[1]_i_1__0_n_0 ),
        .Q(\fifo_sample_count_reg_n_0_[1] ),
        .R(SR));
  FDRE \fifo_sample_count_reg[2] 
       (.C(AXI4_ACLK),
        .CE(\fifo_sample_count[4]_i_1__0_n_0 ),
        .D(fifo_sample_count_next[2]),
        .Q(\fifo_sample_count_reg_n_0_[2] ),
        .R(SR));
  FDRE \fifo_sample_count_reg[3] 
       (.C(AXI4_ACLK),
        .CE(\fifo_sample_count[4]_i_1__0_n_0 ),
        .D(fifo_sample_count_next[3]),
        .Q(\fifo_sample_count_reg_n_0_[3] ),
        .R(SR));
  FDRE \fifo_sample_count_reg[4] 
       (.C(AXI4_ACLK),
        .CE(\fifo_sample_count[4]_i_1__0_n_0 ),
        .D(fifo_sample_count_next[4]),
        .Q(\fifo_sample_count_reg_n_0_[4] ),
        .R(SR));
  LUT6 #(
    .INIT(64'h0EEEEEEEFEEEEEEE)) 
    fifo_valid_i_1__0
       (.I0(\fifo_sample_count[4]_i_3__0_n_0 ),
        .I1(\fifo_sample_count_reg_n_0_[4] ),
        .I2(fifo_valid),
        .I3(cache_valid),
        .I4(out_valid),
        .I5(AXI4_RREADY),
        .O(Q_next_1));
  FDRE fifo_valid_reg
       (.C(AXI4_ACLK),
        .CE(1'b1),
        .D(Q_next_1),
        .Q(fifo_valid),
        .R(SR));
  (* SOFT_HLUTNM = "soft_lutpair73" *) 
  LUT4 #(
    .INIT(16'hEEFE)) 
    out_valid_i_1__0
       (.I0(fifo_valid),
        .I1(cache_valid),
        .I2(out_valid),
        .I3(AXI4_RREADY),
        .O(Q_next_2));
  FDRE out_valid_reg
       (.C(AXI4_ACLK),
        .CE(1'b1),
        .D(Q_next_2),
        .Q(out_valid),
        .R(SR));
  zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_SimpleDualPortRAM_generic__parameterized1 u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram
       (.AXI4_ACLK(AXI4_ACLK),
        .D({u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_1,u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_2,u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_3,u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_4,u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_5,u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_6,u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_7,u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_8,u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_9,u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_10,u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_11,u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_12}),
        .E(wr_en),
        .\Out_tmp_reg[11] ({\cache_data_reg_n_0_[11] ,\cache_data_reg_n_0_[10] ,\cache_data_reg_n_0_[9] ,\cache_data_reg_n_0_[8] ,\cache_data_reg_n_0_[7] ,\cache_data_reg_n_0_[6] ,\cache_data_reg_n_0_[5] ,\cache_data_reg_n_0_[4] ,\cache_data_reg_n_0_[3] ,\cache_data_reg_n_0_[2] ,\cache_data_reg_n_0_[1] ,\cache_data_reg_n_0_[0] }),
        .Q({\fifo_sample_count_reg_n_0_[4] ,\fifo_sample_count_reg_n_0_[3] ,\fifo_sample_count_reg_n_0_[2] ,\fifo_sample_count_reg_n_0_[1] ,\fifo_sample_count_reg_n_0_[0] }),
        .\cache_data_reg[11] (w_d1_reg_n_0),
        .\cache_data_reg[11]_0 ({\w_d2_reg_n_0_[11] ,\w_d2_reg_n_0_[10] ,\w_d2_reg_n_0_[9] ,\w_d2_reg_n_0_[8] ,\w_d2_reg_n_0_[7] ,\w_d2_reg_n_0_[6] ,\w_d2_reg_n_0_[5] ,\w_d2_reg_n_0_[4] ,\w_d2_reg_n_0_[3] ,\w_d2_reg_n_0_[2] ,\w_d2_reg_n_0_[1] ,\w_d2_reg_n_0_[0] }),
        .cache_valid(cache_valid),
        .data_int({u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_13,u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_14,u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_15,u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_16,u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_17,u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_18,u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_19,u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_20,u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_21,u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_22,u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_23,u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_24}),
        .\data_int_reg[1]_0 (Q),
        .\data_int_reg[1]_1 ({\fifo_front_indx_reg_n_0_[3] ,\fifo_front_indx_reg_n_0_[2] ,\fifo_front_indx_reg_n_0_[1] ,\fifo_front_indx_reg_n_0_[0] }),
        .\data_int_reg[1]_2 ({\fifo_back_indx_reg_n_0_[3] ,\fifo_back_indx_reg_n_0_[2] ,\fifo_back_indx_reg_n_0_[1] ,\fifo_back_indx_reg_n_0_[0] }),
        .top_rd_enb(top_rd_enb),
        .w_d1_reg({u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_25,u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_26,u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_27,u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_28,u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_29,u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_30,u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_31,u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_32,u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_33,u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_34,u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_35,u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_36}));
  LUT6 #(
    .INIT(64'h2AAA2AAA2AAA0000)) 
    w_d1_i_1__0
       (.I0(AXI4_ARESETN),
        .I1(fifo_valid),
        .I2(cache_valid),
        .I3(out_valid),
        .I4(\fifo_sample_count_reg_n_0_[4] ),
        .I5(\fifo_sample_count[4]_i_3__0_n_0 ),
        .O(w_d1_i_1__0_n_0));
  FDRE w_d1_reg
       (.C(AXI4_ACLK),
        .CE(1'b1),
        .D(w_d1_i_1__0_n_0),
        .Q(w_d1_reg_n_0),
        .R(1'b0));
  FDRE \w_d2_reg[0] 
       (.C(AXI4_ACLK),
        .CE(w_d1_reg_n_0),
        .D(u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_24),
        .Q(\w_d2_reg_n_0_[0] ),
        .R(SR));
  FDRE \w_d2_reg[10] 
       (.C(AXI4_ACLK),
        .CE(w_d1_reg_n_0),
        .D(u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_14),
        .Q(\w_d2_reg_n_0_[10] ),
        .R(SR));
  FDRE \w_d2_reg[11] 
       (.C(AXI4_ACLK),
        .CE(w_d1_reg_n_0),
        .D(u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_13),
        .Q(\w_d2_reg_n_0_[11] ),
        .R(SR));
  FDRE \w_d2_reg[1] 
       (.C(AXI4_ACLK),
        .CE(w_d1_reg_n_0),
        .D(u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_23),
        .Q(\w_d2_reg_n_0_[1] ),
        .R(SR));
  FDRE \w_d2_reg[2] 
       (.C(AXI4_ACLK),
        .CE(w_d1_reg_n_0),
        .D(u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_22),
        .Q(\w_d2_reg_n_0_[2] ),
        .R(SR));
  FDRE \w_d2_reg[3] 
       (.C(AXI4_ACLK),
        .CE(w_d1_reg_n_0),
        .D(u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_21),
        .Q(\w_d2_reg_n_0_[3] ),
        .R(SR));
  FDRE \w_d2_reg[4] 
       (.C(AXI4_ACLK),
        .CE(w_d1_reg_n_0),
        .D(u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_20),
        .Q(\w_d2_reg_n_0_[4] ),
        .R(SR));
  FDRE \w_d2_reg[5] 
       (.C(AXI4_ACLK),
        .CE(w_d1_reg_n_0),
        .D(u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_19),
        .Q(\w_d2_reg_n_0_[5] ),
        .R(SR));
  FDRE \w_d2_reg[6] 
       (.C(AXI4_ACLK),
        .CE(w_d1_reg_n_0),
        .D(u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_18),
        .Q(\w_d2_reg_n_0_[6] ),
        .R(SR));
  FDRE \w_d2_reg[7] 
       (.C(AXI4_ACLK),
        .CE(w_d1_reg_n_0),
        .D(u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_17),
        .Q(\w_d2_reg_n_0_[7] ),
        .R(SR));
  FDRE \w_d2_reg[8] 
       (.C(AXI4_ACLK),
        .CE(w_d1_reg_n_0),
        .D(u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_16),
        .Q(\w_d2_reg_n_0_[8] ),
        .R(SR));
  FDRE \w_d2_reg[9] 
       (.C(AXI4_ACLK),
        .CE(w_d1_reg_n_0),
        .D(u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_15),
        .Q(\w_d2_reg_n_0_[9] ),
        .R(SR));
endmodule

(* ORIG_REF_NAME = "uz_interlockDeadtime2L_reset_sync" *) 
module zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_reset_sync
   (reset_x,
    reset_in,
    IPCORE_CLK,
    AXI4_ARESETN,
    IPCORE_RESETN,
    soft_reset);
  output reset_x;
  input reset_in;
  input IPCORE_CLK;
  input AXI4_ARESETN;
  input IPCORE_RESETN;
  input soft_reset;

  wire AXI4_ARESETN;
  wire IPCORE_CLK;
  wire IPCORE_RESETN;
  wire reset_in;
  wire reset_out_i_1_n_0;
  wire reset_pipe;
  wire reset_x;
  wire soft_reset;

  LUT4 #(
    .INIT(16'hFFDF)) 
    reset_out_i_1
       (.I0(AXI4_ARESETN),
        .I1(reset_pipe),
        .I2(IPCORE_RESETN),
        .I3(soft_reset),
        .O(reset_out_i_1_n_0));
  FDRE reset_out_reg
       (.C(IPCORE_CLK),
        .CE(1'b1),
        .D(reset_out_i_1_n_0),
        .Q(reset_x),
        .R(1'b0));
  FDRE reset_pipe_reg
       (.C(IPCORE_CLK),
        .CE(1'b1),
        .D(reset_in),
        .Q(reset_pipe),
        .R(1'b0));
endmodule

(* ORIG_REF_NAME = "uz_interlockDeadtime2L_src_DeadtimeModule" *) 
module zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_src_DeadtimeModule
   (PipelineDelay1_out1,
    s0_out,
    PipelineDelay1_out1_reg_0,
    reset_x,
    write_axi_enable,
    IPCORE_CLK,
    Delay2_delOut_reg_0,
    S0,
    s0_out_0,
    s0_out_1,
    S1,
    Q,
    SR,
    E);
  output PipelineDelay1_out1;
  output s0_out;
  output PipelineDelay1_out1_reg_0;
  input reset_x;
  input write_axi_enable;
  input IPCORE_CLK;
  input Delay2_delOut_reg_0;
  input S0;
  input s0_out_0;
  input s0_out_1;
  input S1;
  input [9:0]Q;
  input [0:0]SR;
  input [0:0]E;

  wire Delay2_delOut;
  wire Delay2_delOut2_out;
  wire Delay2_delOut_reg_0;
  wire Detect_Fall_Nonpositive2_out1;
  wire [0:0]E;
  wire \HDL_Counter_out1[6]_i_1__2_n_0 ;
  wire \HDL_Counter_out1[9]_i_4_n_0 ;
  wire [9:0]HDL_Counter_out1_reg;
  wire IPCORE_CLK;
  wire PipelineDelay1_out1;
  wire PipelineDelay1_out1_reg_0;
  wire [9:0]Q;
  wire S0;
  wire S1;
  wire [0:0]SR;
  wire [9:0]p_0_in;
  wire reset_x;
  wire s0_out;
  wire s0_out_0;
  wire s0_out_1;
  wire s0_out_INST_0_i_3_n_0;
  wire s0_out_INST_0_i_5_n_0;
  wire s0_out_INST_0_i_6_n_0;
  wire s0_out_INST_0_i_7_n_0;
  wire write_axi_enable;

  (* SOFT_HLUTNM = "soft_lutpair87" *) 
  LUT5 #(
    .INIT(32'h00220030)) 
    Delay2_delOut_i_2
       (.I0(S0),
        .I1(reset_x),
        .I2(Delay2_delOut),
        .I3(PipelineDelay1_out1),
        .I4(s0_out_INST_0_i_3_n_0),
        .O(Delay2_delOut2_out));
  FDRE Delay2_delOut_reg
       (.C(IPCORE_CLK),
        .CE(Delay2_delOut_reg_0),
        .D(Delay2_delOut2_out),
        .Q(Delay2_delOut),
        .R(1'b0));
  LUT1 #(
    .INIT(2'h1)) 
    \HDL_Counter_out1[0]_i_1 
       (.I0(HDL_Counter_out1_reg[0]),
        .O(p_0_in[0]));
  (* SOFT_HLUTNM = "soft_lutpair90" *) 
  LUT2 #(
    .INIT(4'h6)) 
    \HDL_Counter_out1[1]_i_1 
       (.I0(HDL_Counter_out1_reg[0]),
        .I1(HDL_Counter_out1_reg[1]),
        .O(p_0_in[1]));
  (* SOFT_HLUTNM = "soft_lutpair90" *) 
  LUT3 #(
    .INIT(8'h6A)) 
    \HDL_Counter_out1[2]_i_1 
       (.I0(HDL_Counter_out1_reg[2]),
        .I1(HDL_Counter_out1_reg[0]),
        .I2(HDL_Counter_out1_reg[1]),
        .O(p_0_in[2]));
  (* SOFT_HLUTNM = "soft_lutpair88" *) 
  LUT4 #(
    .INIT(16'h6AAA)) 
    \HDL_Counter_out1[3]_i_1 
       (.I0(HDL_Counter_out1_reg[3]),
        .I1(HDL_Counter_out1_reg[1]),
        .I2(HDL_Counter_out1_reg[0]),
        .I3(HDL_Counter_out1_reg[2]),
        .O(p_0_in[3]));
  (* SOFT_HLUTNM = "soft_lutpair88" *) 
  LUT5 #(
    .INIT(32'h6AAAAAAA)) 
    \HDL_Counter_out1[4]_i_1 
       (.I0(HDL_Counter_out1_reg[4]),
        .I1(HDL_Counter_out1_reg[2]),
        .I2(HDL_Counter_out1_reg[0]),
        .I3(HDL_Counter_out1_reg[1]),
        .I4(HDL_Counter_out1_reg[3]),
        .O(p_0_in[4]));
  LUT6 #(
    .INIT(64'h6AAAAAAAAAAAAAAA)) 
    \HDL_Counter_out1[5]_i_1 
       (.I0(HDL_Counter_out1_reg[5]),
        .I1(HDL_Counter_out1_reg[3]),
        .I2(HDL_Counter_out1_reg[1]),
        .I3(HDL_Counter_out1_reg[0]),
        .I4(HDL_Counter_out1_reg[2]),
        .I5(HDL_Counter_out1_reg[4]),
        .O(p_0_in[5]));
  (* SOFT_HLUTNM = "soft_lutpair91" *) 
  LUT2 #(
    .INIT(4'h9)) 
    \HDL_Counter_out1[6]_i_1__2 
       (.I0(HDL_Counter_out1_reg[6]),
        .I1(\HDL_Counter_out1[9]_i_4_n_0 ),
        .O(\HDL_Counter_out1[6]_i_1__2_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair91" *) 
  LUT3 #(
    .INIT(8'h9A)) 
    \HDL_Counter_out1[7]_i_1 
       (.I0(HDL_Counter_out1_reg[7]),
        .I1(\HDL_Counter_out1[9]_i_4_n_0 ),
        .I2(HDL_Counter_out1_reg[6]),
        .O(p_0_in[7]));
  (* SOFT_HLUTNM = "soft_lutpair89" *) 
  LUT4 #(
    .INIT(16'hA6AA)) 
    \HDL_Counter_out1[8]_i_1 
       (.I0(HDL_Counter_out1_reg[8]),
        .I1(HDL_Counter_out1_reg[6]),
        .I2(\HDL_Counter_out1[9]_i_4_n_0 ),
        .I3(HDL_Counter_out1_reg[7]),
        .O(p_0_in[8]));
  (* SOFT_HLUTNM = "soft_lutpair89" *) 
  LUT5 #(
    .INIT(32'hA6AAAAAA)) 
    \HDL_Counter_out1[9]_i_3 
       (.I0(HDL_Counter_out1_reg[9]),
        .I1(HDL_Counter_out1_reg[7]),
        .I2(\HDL_Counter_out1[9]_i_4_n_0 ),
        .I3(HDL_Counter_out1_reg[6]),
        .I4(HDL_Counter_out1_reg[8]),
        .O(p_0_in[9]));
  LUT6 #(
    .INIT(64'h7FFFFFFFFFFFFFFF)) 
    \HDL_Counter_out1[9]_i_4 
       (.I0(HDL_Counter_out1_reg[4]),
        .I1(HDL_Counter_out1_reg[2]),
        .I2(HDL_Counter_out1_reg[0]),
        .I3(HDL_Counter_out1_reg[1]),
        .I4(HDL_Counter_out1_reg[3]),
        .I5(HDL_Counter_out1_reg[5]),
        .O(\HDL_Counter_out1[9]_i_4_n_0 ));
  FDRE \HDL_Counter_out1_reg[0] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(p_0_in[0]),
        .Q(HDL_Counter_out1_reg[0]),
        .R(SR));
  FDRE \HDL_Counter_out1_reg[1] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(p_0_in[1]),
        .Q(HDL_Counter_out1_reg[1]),
        .R(SR));
  FDRE \HDL_Counter_out1_reg[2] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(p_0_in[2]),
        .Q(HDL_Counter_out1_reg[2]),
        .R(SR));
  FDRE \HDL_Counter_out1_reg[3] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(p_0_in[3]),
        .Q(HDL_Counter_out1_reg[3]),
        .R(SR));
  FDRE \HDL_Counter_out1_reg[4] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(p_0_in[4]),
        .Q(HDL_Counter_out1_reg[4]),
        .R(SR));
  FDRE \HDL_Counter_out1_reg[5] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(p_0_in[5]),
        .Q(HDL_Counter_out1_reg[5]),
        .R(SR));
  FDRE \HDL_Counter_out1_reg[6] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(\HDL_Counter_out1[6]_i_1__2_n_0 ),
        .Q(HDL_Counter_out1_reg[6]),
        .R(SR));
  FDRE \HDL_Counter_out1_reg[7] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(p_0_in[7]),
        .Q(HDL_Counter_out1_reg[7]),
        .R(SR));
  FDRE \HDL_Counter_out1_reg[8] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(p_0_in[8]),
        .Q(HDL_Counter_out1_reg[8]),
        .R(SR));
  FDRE \HDL_Counter_out1_reg[9] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(p_0_in[9]),
        .Q(HDL_Counter_out1_reg[9]),
        .R(SR));
  FDRE PipelineDelay1_out1_reg
       (.C(IPCORE_CLK),
        .CE(write_axi_enable),
        .D(Detect_Fall_Nonpositive2_out1),
        .Q(PipelineDelay1_out1),
        .R(reset_x));
  LUT5 #(
    .INIT(32'h08000808)) 
    s0_out_INST_0
       (.I0(s0_out_0),
        .I1(S0),
        .I2(PipelineDelay1_out1_reg_0),
        .I3(s0_out_1),
        .I4(S1),
        .O(s0_out));
  (* SOFT_HLUTNM = "soft_lutpair87" *) 
  LUT3 #(
    .INIT(8'h45)) 
    s0_out_INST_0_i_1
       (.I0(s0_out_INST_0_i_3_n_0),
        .I1(PipelineDelay1_out1),
        .I2(Delay2_delOut),
        .O(PipelineDelay1_out1_reg_0));
  LUT5 #(
    .INIT(32'h04000004)) 
    s0_out_INST_0_i_3
       (.I0(s0_out_INST_0_i_5_n_0),
        .I1(s0_out_INST_0_i_6_n_0),
        .I2(s0_out_INST_0_i_7_n_0),
        .I3(HDL_Counter_out1_reg[9]),
        .I4(Q[9]),
        .O(s0_out_INST_0_i_3_n_0));
  LUT6 #(
    .INIT(64'h6FF6FFFFFFFF6FF6)) 
    s0_out_INST_0_i_5
       (.I0(Q[3]),
        .I1(HDL_Counter_out1_reg[3]),
        .I2(HDL_Counter_out1_reg[5]),
        .I3(Q[5]),
        .I4(HDL_Counter_out1_reg[4]),
        .I5(Q[4]),
        .O(s0_out_INST_0_i_5_n_0));
  LUT6 #(
    .INIT(64'h9009000000009009)) 
    s0_out_INST_0_i_6
       (.I0(Q[6]),
        .I1(HDL_Counter_out1_reg[6]),
        .I2(HDL_Counter_out1_reg[8]),
        .I3(Q[8]),
        .I4(HDL_Counter_out1_reg[7]),
        .I5(Q[7]),
        .O(s0_out_INST_0_i_6_n_0));
  LUT6 #(
    .INIT(64'h6FF6FFFFFFFF6FF6)) 
    s0_out_INST_0_i_7
       (.I0(Q[0]),
        .I1(HDL_Counter_out1_reg[0]),
        .I2(HDL_Counter_out1_reg[1]),
        .I3(Q[1]),
        .I4(HDL_Counter_out1_reg[2]),
        .I5(Q[2]),
        .O(s0_out_INST_0_i_7_n_0));
  zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_src_Detect_Fall_Nonpositive2_9 u_Detect_Fall_Nonpositive2
       (.Detect_Fall_Nonpositive2_out1(Detect_Fall_Nonpositive2_out1),
        .IPCORE_CLK(IPCORE_CLK),
        .S0(S0),
        .reset_x(reset_x),
        .write_axi_enable(write_axi_enable));
endmodule

(* ORIG_REF_NAME = "uz_interlockDeadtime2L_src_DeadtimeModule" *) 
module zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_src_DeadtimeModule_0
   (PipelineDelay1_out1_0,
    s1_out,
    PipelineDelay1_out1_reg_0,
    reset_x,
    write_axi_enable,
    IPCORE_CLK,
    Delay2_delOut_reg_0,
    S1,
    s1_out_0,
    s1_out_1,
    S0,
    PipeDelay_out1,
    Q,
    \HDL_Counter_out1_reg[9]_0 ,
    \HDL_Counter_out1_reg[9]_1 );
  output PipelineDelay1_out1_0;
  output s1_out;
  output PipelineDelay1_out1_reg_0;
  input reset_x;
  input write_axi_enable;
  input IPCORE_CLK;
  input Delay2_delOut_reg_0;
  input S1;
  input s1_out_0;
  input s1_out_1;
  input S0;
  input PipeDelay_out1;
  input [9:0]Q;
  input [0:0]\HDL_Counter_out1_reg[9]_0 ;
  input [0:0]\HDL_Counter_out1_reg[9]_1 ;

  wire Delay2_delOut;
  wire Delay2_delOut2_out;
  wire Delay2_delOut_reg_0;
  wire Detect_Fall_Nonpositive2_out1;
  wire \HDL_Counter_out1[6]_i_1__3_n_0 ;
  wire \HDL_Counter_out1[9]_i_4__0_n_0 ;
  wire [9:0]HDL_Counter_out1_reg;
  wire [0:0]\HDL_Counter_out1_reg[9]_0 ;
  wire [0:0]\HDL_Counter_out1_reg[9]_1 ;
  wire IPCORE_CLK;
  wire PipeDelay_out1;
  wire PipelineDelay1_out1_0;
  wire PipelineDelay1_out1_reg_0;
  wire [9:0]Q;
  wire S0;
  wire S1;
  wire [9:0]p_0_in__0;
  wire reset_x;
  wire s0_out_INST_0_i_10_n_0;
  wire s0_out_INST_0_i_4_n_0;
  wire s0_out_INST_0_i_8_n_0;
  wire s0_out_INST_0_i_9_n_0;
  wire s1_out;
  wire s1_out_0;
  wire s1_out_1;
  wire write_axi_enable;

  (* SOFT_HLUTNM = "soft_lutpair93" *) 
  LUT5 #(
    .INIT(32'h00220030)) 
    Delay2_delOut_i_1__0
       (.I0(S1),
        .I1(reset_x),
        .I2(Delay2_delOut),
        .I3(PipelineDelay1_out1_0),
        .I4(s0_out_INST_0_i_4_n_0),
        .O(Delay2_delOut2_out));
  FDRE Delay2_delOut_reg
       (.C(IPCORE_CLK),
        .CE(Delay2_delOut_reg_0),
        .D(Delay2_delOut2_out),
        .Q(Delay2_delOut),
        .R(1'b0));
  LUT1 #(
    .INIT(2'h1)) 
    \HDL_Counter_out1[0]_i_1__0 
       (.I0(HDL_Counter_out1_reg[0]),
        .O(p_0_in__0[0]));
  (* SOFT_HLUTNM = "soft_lutpair96" *) 
  LUT2 #(
    .INIT(4'h6)) 
    \HDL_Counter_out1[1]_i_1__0 
       (.I0(HDL_Counter_out1_reg[0]),
        .I1(HDL_Counter_out1_reg[1]),
        .O(p_0_in__0[1]));
  (* SOFT_HLUTNM = "soft_lutpair96" *) 
  LUT3 #(
    .INIT(8'h6A)) 
    \HDL_Counter_out1[2]_i_1__0 
       (.I0(HDL_Counter_out1_reg[2]),
        .I1(HDL_Counter_out1_reg[0]),
        .I2(HDL_Counter_out1_reg[1]),
        .O(p_0_in__0[2]));
  (* SOFT_HLUTNM = "soft_lutpair94" *) 
  LUT4 #(
    .INIT(16'h6AAA)) 
    \HDL_Counter_out1[3]_i_1__0 
       (.I0(HDL_Counter_out1_reg[3]),
        .I1(HDL_Counter_out1_reg[1]),
        .I2(HDL_Counter_out1_reg[0]),
        .I3(HDL_Counter_out1_reg[2]),
        .O(p_0_in__0[3]));
  (* SOFT_HLUTNM = "soft_lutpair94" *) 
  LUT5 #(
    .INIT(32'h6AAAAAAA)) 
    \HDL_Counter_out1[4]_i_1__0 
       (.I0(HDL_Counter_out1_reg[4]),
        .I1(HDL_Counter_out1_reg[2]),
        .I2(HDL_Counter_out1_reg[0]),
        .I3(HDL_Counter_out1_reg[1]),
        .I4(HDL_Counter_out1_reg[3]),
        .O(p_0_in__0[4]));
  LUT6 #(
    .INIT(64'h6AAAAAAAAAAAAAAA)) 
    \HDL_Counter_out1[5]_i_1__0 
       (.I0(HDL_Counter_out1_reg[5]),
        .I1(HDL_Counter_out1_reg[3]),
        .I2(HDL_Counter_out1_reg[1]),
        .I3(HDL_Counter_out1_reg[0]),
        .I4(HDL_Counter_out1_reg[2]),
        .I5(HDL_Counter_out1_reg[4]),
        .O(p_0_in__0[5]));
  (* SOFT_HLUTNM = "soft_lutpair97" *) 
  LUT2 #(
    .INIT(4'h9)) 
    \HDL_Counter_out1[6]_i_1__3 
       (.I0(HDL_Counter_out1_reg[6]),
        .I1(\HDL_Counter_out1[9]_i_4__0_n_0 ),
        .O(\HDL_Counter_out1[6]_i_1__3_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair97" *) 
  LUT3 #(
    .INIT(8'h9A)) 
    \HDL_Counter_out1[7]_i_1__0 
       (.I0(HDL_Counter_out1_reg[7]),
        .I1(\HDL_Counter_out1[9]_i_4__0_n_0 ),
        .I2(HDL_Counter_out1_reg[6]),
        .O(p_0_in__0[7]));
  (* SOFT_HLUTNM = "soft_lutpair95" *) 
  LUT4 #(
    .INIT(16'hA6AA)) 
    \HDL_Counter_out1[8]_i_1__0 
       (.I0(HDL_Counter_out1_reg[8]),
        .I1(HDL_Counter_out1_reg[6]),
        .I2(\HDL_Counter_out1[9]_i_4__0_n_0 ),
        .I3(HDL_Counter_out1_reg[7]),
        .O(p_0_in__0[8]));
  (* SOFT_HLUTNM = "soft_lutpair95" *) 
  LUT5 #(
    .INIT(32'hA6AAAAAA)) 
    \HDL_Counter_out1[9]_i_3__0 
       (.I0(HDL_Counter_out1_reg[9]),
        .I1(HDL_Counter_out1_reg[7]),
        .I2(\HDL_Counter_out1[9]_i_4__0_n_0 ),
        .I3(HDL_Counter_out1_reg[6]),
        .I4(HDL_Counter_out1_reg[8]),
        .O(p_0_in__0[9]));
  LUT6 #(
    .INIT(64'h7FFFFFFFFFFFFFFF)) 
    \HDL_Counter_out1[9]_i_4__0 
       (.I0(HDL_Counter_out1_reg[4]),
        .I1(HDL_Counter_out1_reg[2]),
        .I2(HDL_Counter_out1_reg[0]),
        .I3(HDL_Counter_out1_reg[1]),
        .I4(HDL_Counter_out1_reg[3]),
        .I5(HDL_Counter_out1_reg[5]),
        .O(\HDL_Counter_out1[9]_i_4__0_n_0 ));
  FDRE \HDL_Counter_out1_reg[0] 
       (.C(IPCORE_CLK),
        .CE(\HDL_Counter_out1_reg[9]_1 ),
        .D(p_0_in__0[0]),
        .Q(HDL_Counter_out1_reg[0]),
        .R(\HDL_Counter_out1_reg[9]_0 ));
  FDRE \HDL_Counter_out1_reg[1] 
       (.C(IPCORE_CLK),
        .CE(\HDL_Counter_out1_reg[9]_1 ),
        .D(p_0_in__0[1]),
        .Q(HDL_Counter_out1_reg[1]),
        .R(\HDL_Counter_out1_reg[9]_0 ));
  FDRE \HDL_Counter_out1_reg[2] 
       (.C(IPCORE_CLK),
        .CE(\HDL_Counter_out1_reg[9]_1 ),
        .D(p_0_in__0[2]),
        .Q(HDL_Counter_out1_reg[2]),
        .R(\HDL_Counter_out1_reg[9]_0 ));
  FDRE \HDL_Counter_out1_reg[3] 
       (.C(IPCORE_CLK),
        .CE(\HDL_Counter_out1_reg[9]_1 ),
        .D(p_0_in__0[3]),
        .Q(HDL_Counter_out1_reg[3]),
        .R(\HDL_Counter_out1_reg[9]_0 ));
  FDRE \HDL_Counter_out1_reg[4] 
       (.C(IPCORE_CLK),
        .CE(\HDL_Counter_out1_reg[9]_1 ),
        .D(p_0_in__0[4]),
        .Q(HDL_Counter_out1_reg[4]),
        .R(\HDL_Counter_out1_reg[9]_0 ));
  FDRE \HDL_Counter_out1_reg[5] 
       (.C(IPCORE_CLK),
        .CE(\HDL_Counter_out1_reg[9]_1 ),
        .D(p_0_in__0[5]),
        .Q(HDL_Counter_out1_reg[5]),
        .R(\HDL_Counter_out1_reg[9]_0 ));
  FDRE \HDL_Counter_out1_reg[6] 
       (.C(IPCORE_CLK),
        .CE(\HDL_Counter_out1_reg[9]_1 ),
        .D(\HDL_Counter_out1[6]_i_1__3_n_0 ),
        .Q(HDL_Counter_out1_reg[6]),
        .R(\HDL_Counter_out1_reg[9]_0 ));
  FDRE \HDL_Counter_out1_reg[7] 
       (.C(IPCORE_CLK),
        .CE(\HDL_Counter_out1_reg[9]_1 ),
        .D(p_0_in__0[7]),
        .Q(HDL_Counter_out1_reg[7]),
        .R(\HDL_Counter_out1_reg[9]_0 ));
  FDRE \HDL_Counter_out1_reg[8] 
       (.C(IPCORE_CLK),
        .CE(\HDL_Counter_out1_reg[9]_1 ),
        .D(p_0_in__0[8]),
        .Q(HDL_Counter_out1_reg[8]),
        .R(\HDL_Counter_out1_reg[9]_0 ));
  FDRE \HDL_Counter_out1_reg[9] 
       (.C(IPCORE_CLK),
        .CE(\HDL_Counter_out1_reg[9]_1 ),
        .D(p_0_in__0[9]),
        .Q(HDL_Counter_out1_reg[9]),
        .R(\HDL_Counter_out1_reg[9]_0 ));
  FDRE PipelineDelay1_out1_reg
       (.C(IPCORE_CLK),
        .CE(write_axi_enable),
        .D(Detect_Fall_Nonpositive2_out1),
        .Q(PipelineDelay1_out1_0),
        .R(reset_x));
  LUT6 #(
    .INIT(64'h6FF6FFFFFFFF6FF6)) 
    s0_out_INST_0_i_10
       (.I0(Q[0]),
        .I1(HDL_Counter_out1_reg[0]),
        .I2(HDL_Counter_out1_reg[1]),
        .I3(Q[1]),
        .I4(HDL_Counter_out1_reg[2]),
        .I5(Q[2]),
        .O(s0_out_INST_0_i_10_n_0));
  (* SOFT_HLUTNM = "soft_lutpair93" *) 
  LUT3 #(
    .INIT(8'h45)) 
    s0_out_INST_0_i_2
       (.I0(s0_out_INST_0_i_4_n_0),
        .I1(PipelineDelay1_out1_0),
        .I2(Delay2_delOut),
        .O(PipelineDelay1_out1_reg_0));
  LUT5 #(
    .INIT(32'h04000004)) 
    s0_out_INST_0_i_4
       (.I0(s0_out_INST_0_i_8_n_0),
        .I1(s0_out_INST_0_i_9_n_0),
        .I2(s0_out_INST_0_i_10_n_0),
        .I3(HDL_Counter_out1_reg[9]),
        .I4(Q[9]),
        .O(s0_out_INST_0_i_4_n_0));
  LUT6 #(
    .INIT(64'h6FF6FFFFFFFF6FF6)) 
    s0_out_INST_0_i_8
       (.I0(Q[3]),
        .I1(HDL_Counter_out1_reg[3]),
        .I2(HDL_Counter_out1_reg[4]),
        .I3(Q[4]),
        .I4(HDL_Counter_out1_reg[5]),
        .I5(Q[5]),
        .O(s0_out_INST_0_i_8_n_0));
  LUT6 #(
    .INIT(64'h9009000000009009)) 
    s0_out_INST_0_i_9
       (.I0(Q[6]),
        .I1(HDL_Counter_out1_reg[6]),
        .I2(HDL_Counter_out1_reg[8]),
        .I3(Q[8]),
        .I4(HDL_Counter_out1_reg[7]),
        .I5(Q[7]),
        .O(s0_out_INST_0_i_9_n_0));
  LUT6 #(
    .INIT(64'h8AAA8A8A20002020)) 
    s1_out_INST_0
       (.I0(s1_out_0),
        .I1(PipelineDelay1_out1_reg_0),
        .I2(S1),
        .I3(s1_out_1),
        .I4(S0),
        .I5(PipeDelay_out1),
        .O(s1_out));
  zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_src_Detect_Fall_Nonpositive2_8 u_Detect_Fall_Nonpositive2
       (.Detect_Fall_Nonpositive2_out1(Detect_Fall_Nonpositive2_out1),
        .IPCORE_CLK(IPCORE_CLK),
        .S1(S1),
        .reset_x(reset_x),
        .write_axi_enable(write_axi_enable));
endmodule

(* ORIG_REF_NAME = "uz_interlockDeadtime2L_src_DeadtimeModule" *) 
module zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_src_DeadtimeModule_1
   (PipelineDelay1_out1_1,
    s2_out,
    PipelineDelay1_out1_reg_0,
    reset_x,
    write_axi_enable,
    IPCORE_CLK,
    Delay2_delOut_reg_0,
    S2,
    s2_out_0,
    s2_out_1,
    S3,
    Q,
    \HDL_Counter_out1_reg[9]_0 ,
    \HDL_Counter_out1_reg[9]_1 );
  output PipelineDelay1_out1_1;
  output s2_out;
  output PipelineDelay1_out1_reg_0;
  input reset_x;
  input write_axi_enable;
  input IPCORE_CLK;
  input Delay2_delOut_reg_0;
  input S2;
  input s2_out_0;
  input s2_out_1;
  input S3;
  input [9:0]Q;
  input [0:0]\HDL_Counter_out1_reg[9]_0 ;
  input [0:0]\HDL_Counter_out1_reg[9]_1 ;

  wire Delay2_delOut;
  wire Delay2_delOut2_out;
  wire Delay2_delOut_reg_0;
  wire Detect_Fall_Nonpositive2_out1;
  wire \HDL_Counter_out1[9]_i_4__1_n_0 ;
  wire [9:0]HDL_Counter_out1_reg;
  wire [0:0]\HDL_Counter_out1_reg[9]_0 ;
  wire [0:0]\HDL_Counter_out1_reg[9]_1 ;
  wire IPCORE_CLK;
  wire PipelineDelay1_out1_1;
  wire PipelineDelay1_out1_reg_0;
  wire [9:0]Q;
  wire S2;
  wire S3;
  wire [9:0]p_0_in__1;
  wire reset_x;
  wire s2_out;
  wire s2_out_0;
  wire s2_out_1;
  wire s2_out_INST_0_i_3_n_0;
  wire s2_out_INST_0_i_5_n_0;
  wire s2_out_INST_0_i_6_n_0;
  wire s2_out_INST_0_i_7_n_0;
  wire write_axi_enable;

  (* SOFT_HLUTNM = "soft_lutpair99" *) 
  LUT5 #(
    .INIT(32'h00220030)) 
    Delay2_delOut_i_1__1
       (.I0(S2),
        .I1(reset_x),
        .I2(Delay2_delOut),
        .I3(PipelineDelay1_out1_1),
        .I4(s2_out_INST_0_i_3_n_0),
        .O(Delay2_delOut2_out));
  FDRE Delay2_delOut_reg
       (.C(IPCORE_CLK),
        .CE(Delay2_delOut_reg_0),
        .D(Delay2_delOut2_out),
        .Q(Delay2_delOut),
        .R(1'b0));
  LUT1 #(
    .INIT(2'h1)) 
    \HDL_Counter_out1[0]_i_1__1 
       (.I0(HDL_Counter_out1_reg[0]),
        .O(p_0_in__1[0]));
  (* SOFT_HLUTNM = "soft_lutpair102" *) 
  LUT2 #(
    .INIT(4'h6)) 
    \HDL_Counter_out1[1]_i_1__1 
       (.I0(HDL_Counter_out1_reg[0]),
        .I1(HDL_Counter_out1_reg[1]),
        .O(p_0_in__1[1]));
  (* SOFT_HLUTNM = "soft_lutpair102" *) 
  LUT3 #(
    .INIT(8'h6A)) 
    \HDL_Counter_out1[2]_i_1__1 
       (.I0(HDL_Counter_out1_reg[2]),
        .I1(HDL_Counter_out1_reg[0]),
        .I2(HDL_Counter_out1_reg[1]),
        .O(p_0_in__1[2]));
  (* SOFT_HLUTNM = "soft_lutpair100" *) 
  LUT4 #(
    .INIT(16'h6AAA)) 
    \HDL_Counter_out1[3]_i_1__1 
       (.I0(HDL_Counter_out1_reg[3]),
        .I1(HDL_Counter_out1_reg[1]),
        .I2(HDL_Counter_out1_reg[0]),
        .I3(HDL_Counter_out1_reg[2]),
        .O(p_0_in__1[3]));
  (* SOFT_HLUTNM = "soft_lutpair100" *) 
  LUT5 #(
    .INIT(32'h6AAAAAAA)) 
    \HDL_Counter_out1[4]_i_1__1 
       (.I0(HDL_Counter_out1_reg[4]),
        .I1(HDL_Counter_out1_reg[2]),
        .I2(HDL_Counter_out1_reg[0]),
        .I3(HDL_Counter_out1_reg[1]),
        .I4(HDL_Counter_out1_reg[3]),
        .O(p_0_in__1[4]));
  LUT6 #(
    .INIT(64'h7FFFFFFF80000000)) 
    \HDL_Counter_out1[5]_i_1__1 
       (.I0(HDL_Counter_out1_reg[3]),
        .I1(HDL_Counter_out1_reg[1]),
        .I2(HDL_Counter_out1_reg[0]),
        .I3(HDL_Counter_out1_reg[2]),
        .I4(HDL_Counter_out1_reg[4]),
        .I5(HDL_Counter_out1_reg[5]),
        .O(p_0_in__1[5]));
  (* SOFT_HLUTNM = "soft_lutpair103" *) 
  LUT2 #(
    .INIT(4'h6)) 
    \HDL_Counter_out1[6]_i_1 
       (.I0(HDL_Counter_out1_reg[6]),
        .I1(\HDL_Counter_out1[9]_i_4__1_n_0 ),
        .O(p_0_in__1[6]));
  (* SOFT_HLUTNM = "soft_lutpair103" *) 
  LUT3 #(
    .INIT(8'h6A)) 
    \HDL_Counter_out1[7]_i_1__1 
       (.I0(HDL_Counter_out1_reg[7]),
        .I1(\HDL_Counter_out1[9]_i_4__1_n_0 ),
        .I2(HDL_Counter_out1_reg[6]),
        .O(p_0_in__1[7]));
  (* SOFT_HLUTNM = "soft_lutpair101" *) 
  LUT4 #(
    .INIT(16'h6AAA)) 
    \HDL_Counter_out1[8]_i_1__1 
       (.I0(HDL_Counter_out1_reg[8]),
        .I1(HDL_Counter_out1_reg[6]),
        .I2(\HDL_Counter_out1[9]_i_4__1_n_0 ),
        .I3(HDL_Counter_out1_reg[7]),
        .O(p_0_in__1[8]));
  (* SOFT_HLUTNM = "soft_lutpair101" *) 
  LUT5 #(
    .INIT(32'h6AAAAAAA)) 
    \HDL_Counter_out1[9]_i_3__1 
       (.I0(HDL_Counter_out1_reg[9]),
        .I1(HDL_Counter_out1_reg[7]),
        .I2(\HDL_Counter_out1[9]_i_4__1_n_0 ),
        .I3(HDL_Counter_out1_reg[6]),
        .I4(HDL_Counter_out1_reg[8]),
        .O(p_0_in__1[9]));
  LUT6 #(
    .INIT(64'h8000000000000000)) 
    \HDL_Counter_out1[9]_i_4__1 
       (.I0(HDL_Counter_out1_reg[5]),
        .I1(HDL_Counter_out1_reg[4]),
        .I2(HDL_Counter_out1_reg[2]),
        .I3(HDL_Counter_out1_reg[0]),
        .I4(HDL_Counter_out1_reg[1]),
        .I5(HDL_Counter_out1_reg[3]),
        .O(\HDL_Counter_out1[9]_i_4__1_n_0 ));
  FDRE \HDL_Counter_out1_reg[0] 
       (.C(IPCORE_CLK),
        .CE(\HDL_Counter_out1_reg[9]_1 ),
        .D(p_0_in__1[0]),
        .Q(HDL_Counter_out1_reg[0]),
        .R(\HDL_Counter_out1_reg[9]_0 ));
  FDRE \HDL_Counter_out1_reg[1] 
       (.C(IPCORE_CLK),
        .CE(\HDL_Counter_out1_reg[9]_1 ),
        .D(p_0_in__1[1]),
        .Q(HDL_Counter_out1_reg[1]),
        .R(\HDL_Counter_out1_reg[9]_0 ));
  FDRE \HDL_Counter_out1_reg[2] 
       (.C(IPCORE_CLK),
        .CE(\HDL_Counter_out1_reg[9]_1 ),
        .D(p_0_in__1[2]),
        .Q(HDL_Counter_out1_reg[2]),
        .R(\HDL_Counter_out1_reg[9]_0 ));
  FDRE \HDL_Counter_out1_reg[3] 
       (.C(IPCORE_CLK),
        .CE(\HDL_Counter_out1_reg[9]_1 ),
        .D(p_0_in__1[3]),
        .Q(HDL_Counter_out1_reg[3]),
        .R(\HDL_Counter_out1_reg[9]_0 ));
  FDRE \HDL_Counter_out1_reg[4] 
       (.C(IPCORE_CLK),
        .CE(\HDL_Counter_out1_reg[9]_1 ),
        .D(p_0_in__1[4]),
        .Q(HDL_Counter_out1_reg[4]),
        .R(\HDL_Counter_out1_reg[9]_0 ));
  FDRE \HDL_Counter_out1_reg[5] 
       (.C(IPCORE_CLK),
        .CE(\HDL_Counter_out1_reg[9]_1 ),
        .D(p_0_in__1[5]),
        .Q(HDL_Counter_out1_reg[5]),
        .R(\HDL_Counter_out1_reg[9]_0 ));
  FDRE \HDL_Counter_out1_reg[6] 
       (.C(IPCORE_CLK),
        .CE(\HDL_Counter_out1_reg[9]_1 ),
        .D(p_0_in__1[6]),
        .Q(HDL_Counter_out1_reg[6]),
        .R(\HDL_Counter_out1_reg[9]_0 ));
  FDRE \HDL_Counter_out1_reg[7] 
       (.C(IPCORE_CLK),
        .CE(\HDL_Counter_out1_reg[9]_1 ),
        .D(p_0_in__1[7]),
        .Q(HDL_Counter_out1_reg[7]),
        .R(\HDL_Counter_out1_reg[9]_0 ));
  FDRE \HDL_Counter_out1_reg[8] 
       (.C(IPCORE_CLK),
        .CE(\HDL_Counter_out1_reg[9]_1 ),
        .D(p_0_in__1[8]),
        .Q(HDL_Counter_out1_reg[8]),
        .R(\HDL_Counter_out1_reg[9]_0 ));
  FDRE \HDL_Counter_out1_reg[9] 
       (.C(IPCORE_CLK),
        .CE(\HDL_Counter_out1_reg[9]_1 ),
        .D(p_0_in__1[9]),
        .Q(HDL_Counter_out1_reg[9]),
        .R(\HDL_Counter_out1_reg[9]_0 ));
  FDRE PipelineDelay1_out1_reg
       (.C(IPCORE_CLK),
        .CE(write_axi_enable),
        .D(Detect_Fall_Nonpositive2_out1),
        .Q(PipelineDelay1_out1_1),
        .R(reset_x));
  LUT5 #(
    .INIT(32'h08000808)) 
    s2_out_INST_0
       (.I0(s2_out_0),
        .I1(S2),
        .I2(PipelineDelay1_out1_reg_0),
        .I3(s2_out_1),
        .I4(S3),
        .O(s2_out));
  (* SOFT_HLUTNM = "soft_lutpair99" *) 
  LUT3 #(
    .INIT(8'h45)) 
    s2_out_INST_0_i_1
       (.I0(s2_out_INST_0_i_3_n_0),
        .I1(PipelineDelay1_out1_1),
        .I2(Delay2_delOut),
        .O(PipelineDelay1_out1_reg_0));
  LUT5 #(
    .INIT(32'h04000004)) 
    s2_out_INST_0_i_3
       (.I0(s2_out_INST_0_i_5_n_0),
        .I1(s2_out_INST_0_i_6_n_0),
        .I2(s2_out_INST_0_i_7_n_0),
        .I3(HDL_Counter_out1_reg[9]),
        .I4(Q[9]),
        .O(s2_out_INST_0_i_3_n_0));
  LUT6 #(
    .INIT(64'h6FF6FFFFFFFF6FF6)) 
    s2_out_INST_0_i_5
       (.I0(Q[3]),
        .I1(HDL_Counter_out1_reg[3]),
        .I2(HDL_Counter_out1_reg[4]),
        .I3(Q[4]),
        .I4(HDL_Counter_out1_reg[5]),
        .I5(Q[5]),
        .O(s2_out_INST_0_i_5_n_0));
  LUT6 #(
    .INIT(64'h9009000000009009)) 
    s2_out_INST_0_i_6
       (.I0(HDL_Counter_out1_reg[7]),
        .I1(Q[7]),
        .I2(HDL_Counter_out1_reg[8]),
        .I3(Q[8]),
        .I4(Q[6]),
        .I5(HDL_Counter_out1_reg[6]),
        .O(s2_out_INST_0_i_6_n_0));
  LUT6 #(
    .INIT(64'h6FF6FFFFFFFF6FF6)) 
    s2_out_INST_0_i_7
       (.I0(Q[0]),
        .I1(HDL_Counter_out1_reg[0]),
        .I2(HDL_Counter_out1_reg[1]),
        .I3(Q[1]),
        .I4(HDL_Counter_out1_reg[2]),
        .I5(Q[2]),
        .O(s2_out_INST_0_i_7_n_0));
  zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_src_Detect_Fall_Nonpositive2_7 u_Detect_Fall_Nonpositive2
       (.Detect_Fall_Nonpositive2_out1(Detect_Fall_Nonpositive2_out1),
        .IPCORE_CLK(IPCORE_CLK),
        .S2(S2),
        .reset_x(reset_x),
        .write_axi_enable(write_axi_enable));
endmodule

(* ORIG_REF_NAME = "uz_interlockDeadtime2L_src_DeadtimeModule" *) 
module zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_src_DeadtimeModule_2
   (PipelineDelay1_out1_2,
    s3_out,
    PipelineDelay1_out1_reg_0,
    reset_x,
    write_axi_enable,
    IPCORE_CLK,
    Delay2_delOut_reg_0,
    S3,
    s3_out_0,
    s3_out_1,
    S2,
    PipeDelay_out1,
    Q,
    \HDL_Counter_out1_reg[9]_0 ,
    \HDL_Counter_out1_reg[9]_1 );
  output PipelineDelay1_out1_2;
  output s3_out;
  output PipelineDelay1_out1_reg_0;
  input reset_x;
  input write_axi_enable;
  input IPCORE_CLK;
  input Delay2_delOut_reg_0;
  input S3;
  input s3_out_0;
  input s3_out_1;
  input S2;
  input PipeDelay_out1;
  input [9:0]Q;
  input [0:0]\HDL_Counter_out1_reg[9]_0 ;
  input [0:0]\HDL_Counter_out1_reg[9]_1 ;

  wire Delay2_delOut;
  wire Delay2_delOut2_out;
  wire Delay2_delOut_reg_0;
  wire Detect_Fall_Nonpositive2_out1;
  wire \HDL_Counter_out1[9]_i_4__2_n_0 ;
  wire [9:0]HDL_Counter_out1_reg;
  wire [0:0]\HDL_Counter_out1_reg[9]_0 ;
  wire [0:0]\HDL_Counter_out1_reg[9]_1 ;
  wire IPCORE_CLK;
  wire PipeDelay_out1;
  wire PipelineDelay1_out1_2;
  wire PipelineDelay1_out1_reg_0;
  wire [9:0]Q;
  wire S2;
  wire S3;
  wire [9:0]p_0_in__2;
  wire reset_x;
  wire s2_out_INST_0_i_10_n_0;
  wire s2_out_INST_0_i_4_n_0;
  wire s2_out_INST_0_i_8_n_0;
  wire s2_out_INST_0_i_9_n_0;
  wire s3_out;
  wire s3_out_0;
  wire s3_out_1;
  wire write_axi_enable;

  (* SOFT_HLUTNM = "soft_lutpair105" *) 
  LUT5 #(
    .INIT(32'h00220030)) 
    Delay2_delOut_i_1__2
       (.I0(S3),
        .I1(reset_x),
        .I2(Delay2_delOut),
        .I3(PipelineDelay1_out1_2),
        .I4(s2_out_INST_0_i_4_n_0),
        .O(Delay2_delOut2_out));
  FDRE Delay2_delOut_reg
       (.C(IPCORE_CLK),
        .CE(Delay2_delOut_reg_0),
        .D(Delay2_delOut2_out),
        .Q(Delay2_delOut),
        .R(1'b0));
  LUT1 #(
    .INIT(2'h1)) 
    \HDL_Counter_out1[0]_i_1__2 
       (.I0(HDL_Counter_out1_reg[0]),
        .O(p_0_in__2[0]));
  (* SOFT_HLUTNM = "soft_lutpair108" *) 
  LUT2 #(
    .INIT(4'h6)) 
    \HDL_Counter_out1[1]_i_1__2 
       (.I0(HDL_Counter_out1_reg[0]),
        .I1(HDL_Counter_out1_reg[1]),
        .O(p_0_in__2[1]));
  (* SOFT_HLUTNM = "soft_lutpair108" *) 
  LUT3 #(
    .INIT(8'h6A)) 
    \HDL_Counter_out1[2]_i_1__2 
       (.I0(HDL_Counter_out1_reg[2]),
        .I1(HDL_Counter_out1_reg[0]),
        .I2(HDL_Counter_out1_reg[1]),
        .O(p_0_in__2[2]));
  (* SOFT_HLUTNM = "soft_lutpair106" *) 
  LUT4 #(
    .INIT(16'h6AAA)) 
    \HDL_Counter_out1[3]_i_1__2 
       (.I0(HDL_Counter_out1_reg[3]),
        .I1(HDL_Counter_out1_reg[1]),
        .I2(HDL_Counter_out1_reg[0]),
        .I3(HDL_Counter_out1_reg[2]),
        .O(p_0_in__2[3]));
  (* SOFT_HLUTNM = "soft_lutpair106" *) 
  LUT5 #(
    .INIT(32'h6AAAAAAA)) 
    \HDL_Counter_out1[4]_i_1__2 
       (.I0(HDL_Counter_out1_reg[4]),
        .I1(HDL_Counter_out1_reg[2]),
        .I2(HDL_Counter_out1_reg[0]),
        .I3(HDL_Counter_out1_reg[1]),
        .I4(HDL_Counter_out1_reg[3]),
        .O(p_0_in__2[4]));
  LUT6 #(
    .INIT(64'h7FFFFFFF80000000)) 
    \HDL_Counter_out1[5]_i_1__2 
       (.I0(HDL_Counter_out1_reg[3]),
        .I1(HDL_Counter_out1_reg[1]),
        .I2(HDL_Counter_out1_reg[0]),
        .I3(HDL_Counter_out1_reg[2]),
        .I4(HDL_Counter_out1_reg[4]),
        .I5(HDL_Counter_out1_reg[5]),
        .O(p_0_in__2[5]));
  (* SOFT_HLUTNM = "soft_lutpair109" *) 
  LUT2 #(
    .INIT(4'h6)) 
    \HDL_Counter_out1[6]_i_1__0 
       (.I0(HDL_Counter_out1_reg[6]),
        .I1(\HDL_Counter_out1[9]_i_4__2_n_0 ),
        .O(p_0_in__2[6]));
  (* SOFT_HLUTNM = "soft_lutpair109" *) 
  LUT3 #(
    .INIT(8'h6A)) 
    \HDL_Counter_out1[7]_i_1__2 
       (.I0(HDL_Counter_out1_reg[7]),
        .I1(\HDL_Counter_out1[9]_i_4__2_n_0 ),
        .I2(HDL_Counter_out1_reg[6]),
        .O(p_0_in__2[7]));
  (* SOFT_HLUTNM = "soft_lutpair107" *) 
  LUT4 #(
    .INIT(16'h6AAA)) 
    \HDL_Counter_out1[8]_i_1__2 
       (.I0(HDL_Counter_out1_reg[8]),
        .I1(HDL_Counter_out1_reg[6]),
        .I2(\HDL_Counter_out1[9]_i_4__2_n_0 ),
        .I3(HDL_Counter_out1_reg[7]),
        .O(p_0_in__2[8]));
  (* SOFT_HLUTNM = "soft_lutpair107" *) 
  LUT5 #(
    .INIT(32'h6AAAAAAA)) 
    \HDL_Counter_out1[9]_i_3__2 
       (.I0(HDL_Counter_out1_reg[9]),
        .I1(HDL_Counter_out1_reg[7]),
        .I2(\HDL_Counter_out1[9]_i_4__2_n_0 ),
        .I3(HDL_Counter_out1_reg[6]),
        .I4(HDL_Counter_out1_reg[8]),
        .O(p_0_in__2[9]));
  LUT6 #(
    .INIT(64'h8000000000000000)) 
    \HDL_Counter_out1[9]_i_4__2 
       (.I0(HDL_Counter_out1_reg[5]),
        .I1(HDL_Counter_out1_reg[4]),
        .I2(HDL_Counter_out1_reg[2]),
        .I3(HDL_Counter_out1_reg[0]),
        .I4(HDL_Counter_out1_reg[1]),
        .I5(HDL_Counter_out1_reg[3]),
        .O(\HDL_Counter_out1[9]_i_4__2_n_0 ));
  FDRE \HDL_Counter_out1_reg[0] 
       (.C(IPCORE_CLK),
        .CE(\HDL_Counter_out1_reg[9]_1 ),
        .D(p_0_in__2[0]),
        .Q(HDL_Counter_out1_reg[0]),
        .R(\HDL_Counter_out1_reg[9]_0 ));
  FDRE \HDL_Counter_out1_reg[1] 
       (.C(IPCORE_CLK),
        .CE(\HDL_Counter_out1_reg[9]_1 ),
        .D(p_0_in__2[1]),
        .Q(HDL_Counter_out1_reg[1]),
        .R(\HDL_Counter_out1_reg[9]_0 ));
  FDRE \HDL_Counter_out1_reg[2] 
       (.C(IPCORE_CLK),
        .CE(\HDL_Counter_out1_reg[9]_1 ),
        .D(p_0_in__2[2]),
        .Q(HDL_Counter_out1_reg[2]),
        .R(\HDL_Counter_out1_reg[9]_0 ));
  FDRE \HDL_Counter_out1_reg[3] 
       (.C(IPCORE_CLK),
        .CE(\HDL_Counter_out1_reg[9]_1 ),
        .D(p_0_in__2[3]),
        .Q(HDL_Counter_out1_reg[3]),
        .R(\HDL_Counter_out1_reg[9]_0 ));
  FDRE \HDL_Counter_out1_reg[4] 
       (.C(IPCORE_CLK),
        .CE(\HDL_Counter_out1_reg[9]_1 ),
        .D(p_0_in__2[4]),
        .Q(HDL_Counter_out1_reg[4]),
        .R(\HDL_Counter_out1_reg[9]_0 ));
  FDRE \HDL_Counter_out1_reg[5] 
       (.C(IPCORE_CLK),
        .CE(\HDL_Counter_out1_reg[9]_1 ),
        .D(p_0_in__2[5]),
        .Q(HDL_Counter_out1_reg[5]),
        .R(\HDL_Counter_out1_reg[9]_0 ));
  FDRE \HDL_Counter_out1_reg[6] 
       (.C(IPCORE_CLK),
        .CE(\HDL_Counter_out1_reg[9]_1 ),
        .D(p_0_in__2[6]),
        .Q(HDL_Counter_out1_reg[6]),
        .R(\HDL_Counter_out1_reg[9]_0 ));
  FDRE \HDL_Counter_out1_reg[7] 
       (.C(IPCORE_CLK),
        .CE(\HDL_Counter_out1_reg[9]_1 ),
        .D(p_0_in__2[7]),
        .Q(HDL_Counter_out1_reg[7]),
        .R(\HDL_Counter_out1_reg[9]_0 ));
  FDRE \HDL_Counter_out1_reg[8] 
       (.C(IPCORE_CLK),
        .CE(\HDL_Counter_out1_reg[9]_1 ),
        .D(p_0_in__2[8]),
        .Q(HDL_Counter_out1_reg[8]),
        .R(\HDL_Counter_out1_reg[9]_0 ));
  FDRE \HDL_Counter_out1_reg[9] 
       (.C(IPCORE_CLK),
        .CE(\HDL_Counter_out1_reg[9]_1 ),
        .D(p_0_in__2[9]),
        .Q(HDL_Counter_out1_reg[9]),
        .R(\HDL_Counter_out1_reg[9]_0 ));
  FDRE PipelineDelay1_out1_reg
       (.C(IPCORE_CLK),
        .CE(write_axi_enable),
        .D(Detect_Fall_Nonpositive2_out1),
        .Q(PipelineDelay1_out1_2),
        .R(reset_x));
  LUT6 #(
    .INIT(64'h6FF6FFFFFFFF6FF6)) 
    s2_out_INST_0_i_10
       (.I0(Q[0]),
        .I1(HDL_Counter_out1_reg[0]),
        .I2(HDL_Counter_out1_reg[1]),
        .I3(Q[1]),
        .I4(HDL_Counter_out1_reg[2]),
        .I5(Q[2]),
        .O(s2_out_INST_0_i_10_n_0));
  (* SOFT_HLUTNM = "soft_lutpair105" *) 
  LUT3 #(
    .INIT(8'h45)) 
    s2_out_INST_0_i_2
       (.I0(s2_out_INST_0_i_4_n_0),
        .I1(PipelineDelay1_out1_2),
        .I2(Delay2_delOut),
        .O(PipelineDelay1_out1_reg_0));
  LUT5 #(
    .INIT(32'h04000004)) 
    s2_out_INST_0_i_4
       (.I0(s2_out_INST_0_i_8_n_0),
        .I1(s2_out_INST_0_i_9_n_0),
        .I2(s2_out_INST_0_i_10_n_0),
        .I3(HDL_Counter_out1_reg[9]),
        .I4(Q[9]),
        .O(s2_out_INST_0_i_4_n_0));
  LUT6 #(
    .INIT(64'h6FF6FFFFFFFF6FF6)) 
    s2_out_INST_0_i_8
       (.I0(Q[3]),
        .I1(HDL_Counter_out1_reg[3]),
        .I2(HDL_Counter_out1_reg[4]),
        .I3(Q[4]),
        .I4(HDL_Counter_out1_reg[5]),
        .I5(Q[5]),
        .O(s2_out_INST_0_i_8_n_0));
  LUT6 #(
    .INIT(64'h9009000000009009)) 
    s2_out_INST_0_i_9
       (.I0(HDL_Counter_out1_reg[7]),
        .I1(Q[7]),
        .I2(HDL_Counter_out1_reg[8]),
        .I3(Q[8]),
        .I4(Q[6]),
        .I5(HDL_Counter_out1_reg[6]),
        .O(s2_out_INST_0_i_9_n_0));
  LUT6 #(
    .INIT(64'h8AAA8A8A20002020)) 
    s3_out_INST_0
       (.I0(s3_out_0),
        .I1(PipelineDelay1_out1_reg_0),
        .I2(S3),
        .I3(s3_out_1),
        .I4(S2),
        .I5(PipeDelay_out1),
        .O(s3_out));
  zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_src_Detect_Fall_Nonpositive2_6 u_Detect_Fall_Nonpositive2
       (.Detect_Fall_Nonpositive2_out1(Detect_Fall_Nonpositive2_out1),
        .IPCORE_CLK(IPCORE_CLK),
        .S3(S3),
        .reset_x(reset_x),
        .write_axi_enable(write_axi_enable));
endmodule

(* ORIG_REF_NAME = "uz_interlockDeadtime2L_src_DeadtimeModule" *) 
module zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_src_DeadtimeModule_3
   (PipelineDelay1_out1_3,
    s4_out,
    PipelineDelay1_out1_reg_0,
    reset_x,
    write_axi_enable,
    IPCORE_CLK,
    Delay2_delOut_reg_0,
    S4,
    s4_out_0,
    s4_out_1,
    S5,
    Q,
    \HDL_Counter_out1_reg[9]_0 ,
    \HDL_Counter_out1_reg[9]_1 );
  output PipelineDelay1_out1_3;
  output s4_out;
  output PipelineDelay1_out1_reg_0;
  input reset_x;
  input write_axi_enable;
  input IPCORE_CLK;
  input Delay2_delOut_reg_0;
  input S4;
  input s4_out_0;
  input s4_out_1;
  input S5;
  input [9:0]Q;
  input [0:0]\HDL_Counter_out1_reg[9]_0 ;
  input [0:0]\HDL_Counter_out1_reg[9]_1 ;

  wire Delay2_delOut;
  wire Delay2_delOut2_out;
  wire Delay2_delOut_reg_0;
  wire Detect_Fall_Nonpositive2_out1;
  wire \HDL_Counter_out1[6]_i_1__4_n_0 ;
  wire \HDL_Counter_out1[9]_i_4__3_n_0 ;
  wire [9:0]HDL_Counter_out1_reg;
  wire [0:0]\HDL_Counter_out1_reg[9]_0 ;
  wire [0:0]\HDL_Counter_out1_reg[9]_1 ;
  wire IPCORE_CLK;
  wire PipelineDelay1_out1_3;
  wire PipelineDelay1_out1_reg_0;
  wire [9:0]Q;
  wire S4;
  wire S5;
  wire [9:0]p_0_in__3;
  wire reset_x;
  wire s4_out;
  wire s4_out_0;
  wire s4_out_1;
  wire s4_out_INST_0_i_3_n_0;
  wire s4_out_INST_0_i_5_n_0;
  wire s4_out_INST_0_i_6_n_0;
  wire s4_out_INST_0_i_7_n_0;
  wire write_axi_enable;

  (* SOFT_HLUTNM = "soft_lutpair111" *) 
  LUT5 #(
    .INIT(32'h00220030)) 
    Delay2_delOut_i_1__3
       (.I0(S4),
        .I1(reset_x),
        .I2(Delay2_delOut),
        .I3(PipelineDelay1_out1_3),
        .I4(s4_out_INST_0_i_3_n_0),
        .O(Delay2_delOut2_out));
  FDRE Delay2_delOut_reg
       (.C(IPCORE_CLK),
        .CE(Delay2_delOut_reg_0),
        .D(Delay2_delOut2_out),
        .Q(Delay2_delOut),
        .R(1'b0));
  LUT1 #(
    .INIT(2'h1)) 
    \HDL_Counter_out1[0]_i_1__3 
       (.I0(HDL_Counter_out1_reg[0]),
        .O(p_0_in__3[0]));
  (* SOFT_HLUTNM = "soft_lutpair114" *) 
  LUT2 #(
    .INIT(4'h6)) 
    \HDL_Counter_out1[1]_i_1__3 
       (.I0(HDL_Counter_out1_reg[0]),
        .I1(HDL_Counter_out1_reg[1]),
        .O(p_0_in__3[1]));
  (* SOFT_HLUTNM = "soft_lutpair114" *) 
  LUT3 #(
    .INIT(8'h6A)) 
    \HDL_Counter_out1[2]_i_1__3 
       (.I0(HDL_Counter_out1_reg[2]),
        .I1(HDL_Counter_out1_reg[0]),
        .I2(HDL_Counter_out1_reg[1]),
        .O(p_0_in__3[2]));
  (* SOFT_HLUTNM = "soft_lutpair112" *) 
  LUT4 #(
    .INIT(16'h6AAA)) 
    \HDL_Counter_out1[3]_i_1__3 
       (.I0(HDL_Counter_out1_reg[3]),
        .I1(HDL_Counter_out1_reg[1]),
        .I2(HDL_Counter_out1_reg[0]),
        .I3(HDL_Counter_out1_reg[2]),
        .O(p_0_in__3[3]));
  (* SOFT_HLUTNM = "soft_lutpair112" *) 
  LUT5 #(
    .INIT(32'h6AAAAAAA)) 
    \HDL_Counter_out1[4]_i_1__3 
       (.I0(HDL_Counter_out1_reg[4]),
        .I1(HDL_Counter_out1_reg[2]),
        .I2(HDL_Counter_out1_reg[0]),
        .I3(HDL_Counter_out1_reg[1]),
        .I4(HDL_Counter_out1_reg[3]),
        .O(p_0_in__3[4]));
  LUT6 #(
    .INIT(64'h6AAAAAAAAAAAAAAA)) 
    \HDL_Counter_out1[5]_i_1__3 
       (.I0(HDL_Counter_out1_reg[5]),
        .I1(HDL_Counter_out1_reg[3]),
        .I2(HDL_Counter_out1_reg[1]),
        .I3(HDL_Counter_out1_reg[0]),
        .I4(HDL_Counter_out1_reg[2]),
        .I5(HDL_Counter_out1_reg[4]),
        .O(p_0_in__3[5]));
  (* SOFT_HLUTNM = "soft_lutpair115" *) 
  LUT2 #(
    .INIT(4'h9)) 
    \HDL_Counter_out1[6]_i_1__4 
       (.I0(HDL_Counter_out1_reg[6]),
        .I1(\HDL_Counter_out1[9]_i_4__3_n_0 ),
        .O(\HDL_Counter_out1[6]_i_1__4_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair115" *) 
  LUT3 #(
    .INIT(8'h9A)) 
    \HDL_Counter_out1[7]_i_1__3 
       (.I0(HDL_Counter_out1_reg[7]),
        .I1(\HDL_Counter_out1[9]_i_4__3_n_0 ),
        .I2(HDL_Counter_out1_reg[6]),
        .O(p_0_in__3[7]));
  (* SOFT_HLUTNM = "soft_lutpair113" *) 
  LUT4 #(
    .INIT(16'hA6AA)) 
    \HDL_Counter_out1[8]_i_1__3 
       (.I0(HDL_Counter_out1_reg[8]),
        .I1(HDL_Counter_out1_reg[6]),
        .I2(\HDL_Counter_out1[9]_i_4__3_n_0 ),
        .I3(HDL_Counter_out1_reg[7]),
        .O(p_0_in__3[8]));
  (* SOFT_HLUTNM = "soft_lutpair113" *) 
  LUT5 #(
    .INIT(32'hA6AAAAAA)) 
    \HDL_Counter_out1[9]_i_3__3 
       (.I0(HDL_Counter_out1_reg[9]),
        .I1(HDL_Counter_out1_reg[7]),
        .I2(\HDL_Counter_out1[9]_i_4__3_n_0 ),
        .I3(HDL_Counter_out1_reg[6]),
        .I4(HDL_Counter_out1_reg[8]),
        .O(p_0_in__3[9]));
  LUT6 #(
    .INIT(64'h7FFFFFFFFFFFFFFF)) 
    \HDL_Counter_out1[9]_i_4__3 
       (.I0(HDL_Counter_out1_reg[4]),
        .I1(HDL_Counter_out1_reg[2]),
        .I2(HDL_Counter_out1_reg[0]),
        .I3(HDL_Counter_out1_reg[1]),
        .I4(HDL_Counter_out1_reg[3]),
        .I5(HDL_Counter_out1_reg[5]),
        .O(\HDL_Counter_out1[9]_i_4__3_n_0 ));
  FDRE \HDL_Counter_out1_reg[0] 
       (.C(IPCORE_CLK),
        .CE(\HDL_Counter_out1_reg[9]_1 ),
        .D(p_0_in__3[0]),
        .Q(HDL_Counter_out1_reg[0]),
        .R(\HDL_Counter_out1_reg[9]_0 ));
  FDRE \HDL_Counter_out1_reg[1] 
       (.C(IPCORE_CLK),
        .CE(\HDL_Counter_out1_reg[9]_1 ),
        .D(p_0_in__3[1]),
        .Q(HDL_Counter_out1_reg[1]),
        .R(\HDL_Counter_out1_reg[9]_0 ));
  FDRE \HDL_Counter_out1_reg[2] 
       (.C(IPCORE_CLK),
        .CE(\HDL_Counter_out1_reg[9]_1 ),
        .D(p_0_in__3[2]),
        .Q(HDL_Counter_out1_reg[2]),
        .R(\HDL_Counter_out1_reg[9]_0 ));
  FDRE \HDL_Counter_out1_reg[3] 
       (.C(IPCORE_CLK),
        .CE(\HDL_Counter_out1_reg[9]_1 ),
        .D(p_0_in__3[3]),
        .Q(HDL_Counter_out1_reg[3]),
        .R(\HDL_Counter_out1_reg[9]_0 ));
  FDRE \HDL_Counter_out1_reg[4] 
       (.C(IPCORE_CLK),
        .CE(\HDL_Counter_out1_reg[9]_1 ),
        .D(p_0_in__3[4]),
        .Q(HDL_Counter_out1_reg[4]),
        .R(\HDL_Counter_out1_reg[9]_0 ));
  FDRE \HDL_Counter_out1_reg[5] 
       (.C(IPCORE_CLK),
        .CE(\HDL_Counter_out1_reg[9]_1 ),
        .D(p_0_in__3[5]),
        .Q(HDL_Counter_out1_reg[5]),
        .R(\HDL_Counter_out1_reg[9]_0 ));
  FDRE \HDL_Counter_out1_reg[6] 
       (.C(IPCORE_CLK),
        .CE(\HDL_Counter_out1_reg[9]_1 ),
        .D(\HDL_Counter_out1[6]_i_1__4_n_0 ),
        .Q(HDL_Counter_out1_reg[6]),
        .R(\HDL_Counter_out1_reg[9]_0 ));
  FDRE \HDL_Counter_out1_reg[7] 
       (.C(IPCORE_CLK),
        .CE(\HDL_Counter_out1_reg[9]_1 ),
        .D(p_0_in__3[7]),
        .Q(HDL_Counter_out1_reg[7]),
        .R(\HDL_Counter_out1_reg[9]_0 ));
  FDRE \HDL_Counter_out1_reg[8] 
       (.C(IPCORE_CLK),
        .CE(\HDL_Counter_out1_reg[9]_1 ),
        .D(p_0_in__3[8]),
        .Q(HDL_Counter_out1_reg[8]),
        .R(\HDL_Counter_out1_reg[9]_0 ));
  FDRE \HDL_Counter_out1_reg[9] 
       (.C(IPCORE_CLK),
        .CE(\HDL_Counter_out1_reg[9]_1 ),
        .D(p_0_in__3[9]),
        .Q(HDL_Counter_out1_reg[9]),
        .R(\HDL_Counter_out1_reg[9]_0 ));
  FDRE PipelineDelay1_out1_reg
       (.C(IPCORE_CLK),
        .CE(write_axi_enable),
        .D(Detect_Fall_Nonpositive2_out1),
        .Q(PipelineDelay1_out1_3),
        .R(reset_x));
  LUT5 #(
    .INIT(32'h08000808)) 
    s4_out_INST_0
       (.I0(s4_out_0),
        .I1(S4),
        .I2(PipelineDelay1_out1_reg_0),
        .I3(s4_out_1),
        .I4(S5),
        .O(s4_out));
  (* SOFT_HLUTNM = "soft_lutpair111" *) 
  LUT3 #(
    .INIT(8'h45)) 
    s4_out_INST_0_i_1
       (.I0(s4_out_INST_0_i_3_n_0),
        .I1(PipelineDelay1_out1_3),
        .I2(Delay2_delOut),
        .O(PipelineDelay1_out1_reg_0));
  LUT5 #(
    .INIT(32'h04000004)) 
    s4_out_INST_0_i_3
       (.I0(s4_out_INST_0_i_5_n_0),
        .I1(s4_out_INST_0_i_6_n_0),
        .I2(s4_out_INST_0_i_7_n_0),
        .I3(HDL_Counter_out1_reg[9]),
        .I4(Q[9]),
        .O(s4_out_INST_0_i_3_n_0));
  LUT6 #(
    .INIT(64'h6FF6FFFFFFFF6FF6)) 
    s4_out_INST_0_i_5
       (.I0(Q[3]),
        .I1(HDL_Counter_out1_reg[3]),
        .I2(HDL_Counter_out1_reg[5]),
        .I3(Q[5]),
        .I4(HDL_Counter_out1_reg[4]),
        .I5(Q[4]),
        .O(s4_out_INST_0_i_5_n_0));
  LUT6 #(
    .INIT(64'h9009000000009009)) 
    s4_out_INST_0_i_6
       (.I0(Q[6]),
        .I1(HDL_Counter_out1_reg[6]),
        .I2(HDL_Counter_out1_reg[7]),
        .I3(Q[7]),
        .I4(HDL_Counter_out1_reg[8]),
        .I5(Q[8]),
        .O(s4_out_INST_0_i_6_n_0));
  LUT6 #(
    .INIT(64'h6FF6FFFFFFFF6FF6)) 
    s4_out_INST_0_i_7
       (.I0(Q[0]),
        .I1(HDL_Counter_out1_reg[0]),
        .I2(HDL_Counter_out1_reg[1]),
        .I3(Q[1]),
        .I4(HDL_Counter_out1_reg[2]),
        .I5(Q[2]),
        .O(s4_out_INST_0_i_7_n_0));
  zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_src_Detect_Fall_Nonpositive2_5 u_Detect_Fall_Nonpositive2
       (.Detect_Fall_Nonpositive2_out1(Detect_Fall_Nonpositive2_out1),
        .IPCORE_CLK(IPCORE_CLK),
        .S4(S4),
        .reset_x(reset_x),
        .write_axi_enable(write_axi_enable));
endmodule

(* ORIG_REF_NAME = "uz_interlockDeadtime2L_src_DeadtimeModule" *) 
module zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_src_DeadtimeModule_4
   (PipelineDelay1_out1_4,
    s5_out,
    PipelineDelay1_out1_reg_0,
    reset_x,
    write_axi_enable,
    IPCORE_CLK,
    Delay2_delOut_reg_0,
    S5,
    s5_out_0,
    s5_out_1,
    S4,
    PipeDelay_out1,
    Q,
    \HDL_Counter_out1_reg[9]_0 ,
    \HDL_Counter_out1_reg[9]_1 );
  output PipelineDelay1_out1_4;
  output s5_out;
  output PipelineDelay1_out1_reg_0;
  input reset_x;
  input write_axi_enable;
  input IPCORE_CLK;
  input Delay2_delOut_reg_0;
  input S5;
  input s5_out_0;
  input s5_out_1;
  input S4;
  input PipeDelay_out1;
  input [9:0]Q;
  input [0:0]\HDL_Counter_out1_reg[9]_0 ;
  input [0:0]\HDL_Counter_out1_reg[9]_1 ;

  wire Delay2_delOut;
  wire Delay2_delOut2_out;
  wire Delay2_delOut_reg_0;
  wire Detect_Fall_Nonpositive2_out1;
  wire \HDL_Counter_out1[9]_i_4__4_n_0 ;
  wire [9:0]HDL_Counter_out1_reg;
  wire [0:0]\HDL_Counter_out1_reg[9]_0 ;
  wire [0:0]\HDL_Counter_out1_reg[9]_1 ;
  wire IPCORE_CLK;
  wire PipeDelay_out1;
  wire PipelineDelay1_out1_4;
  wire PipelineDelay1_out1_reg_0;
  wire [9:0]Q;
  wire S4;
  wire S5;
  wire [9:0]p_0_in__4;
  wire reset_x;
  wire s4_out_INST_0_i_10_n_0;
  wire s4_out_INST_0_i_4_n_0;
  wire s4_out_INST_0_i_8_n_0;
  wire s4_out_INST_0_i_9_n_0;
  wire s5_out;
  wire s5_out_0;
  wire s5_out_1;
  wire write_axi_enable;

  (* SOFT_HLUTNM = "soft_lutpair117" *) 
  LUT5 #(
    .INIT(32'h00220030)) 
    Delay2_delOut_i_1__4
       (.I0(S5),
        .I1(reset_x),
        .I2(Delay2_delOut),
        .I3(PipelineDelay1_out1_4),
        .I4(s4_out_INST_0_i_4_n_0),
        .O(Delay2_delOut2_out));
  FDRE Delay2_delOut_reg
       (.C(IPCORE_CLK),
        .CE(Delay2_delOut_reg_0),
        .D(Delay2_delOut2_out),
        .Q(Delay2_delOut),
        .R(1'b0));
  LUT1 #(
    .INIT(2'h1)) 
    \HDL_Counter_out1[0]_i_1__4 
       (.I0(HDL_Counter_out1_reg[0]),
        .O(p_0_in__4[0]));
  (* SOFT_HLUTNM = "soft_lutpair120" *) 
  LUT2 #(
    .INIT(4'h6)) 
    \HDL_Counter_out1[1]_i_1__4 
       (.I0(HDL_Counter_out1_reg[0]),
        .I1(HDL_Counter_out1_reg[1]),
        .O(p_0_in__4[1]));
  (* SOFT_HLUTNM = "soft_lutpair120" *) 
  LUT3 #(
    .INIT(8'h6A)) 
    \HDL_Counter_out1[2]_i_1__4 
       (.I0(HDL_Counter_out1_reg[2]),
        .I1(HDL_Counter_out1_reg[0]),
        .I2(HDL_Counter_out1_reg[1]),
        .O(p_0_in__4[2]));
  (* SOFT_HLUTNM = "soft_lutpair118" *) 
  LUT4 #(
    .INIT(16'h6AAA)) 
    \HDL_Counter_out1[3]_i_1__4 
       (.I0(HDL_Counter_out1_reg[3]),
        .I1(HDL_Counter_out1_reg[1]),
        .I2(HDL_Counter_out1_reg[0]),
        .I3(HDL_Counter_out1_reg[2]),
        .O(p_0_in__4[3]));
  (* SOFT_HLUTNM = "soft_lutpair118" *) 
  LUT5 #(
    .INIT(32'h6AAAAAAA)) 
    \HDL_Counter_out1[4]_i_1__4 
       (.I0(HDL_Counter_out1_reg[4]),
        .I1(HDL_Counter_out1_reg[2]),
        .I2(HDL_Counter_out1_reg[0]),
        .I3(HDL_Counter_out1_reg[1]),
        .I4(HDL_Counter_out1_reg[3]),
        .O(p_0_in__4[4]));
  LUT6 #(
    .INIT(64'h7FFFFFFF80000000)) 
    \HDL_Counter_out1[5]_i_1__4 
       (.I0(HDL_Counter_out1_reg[3]),
        .I1(HDL_Counter_out1_reg[1]),
        .I2(HDL_Counter_out1_reg[0]),
        .I3(HDL_Counter_out1_reg[2]),
        .I4(HDL_Counter_out1_reg[4]),
        .I5(HDL_Counter_out1_reg[5]),
        .O(p_0_in__4[5]));
  (* SOFT_HLUTNM = "soft_lutpair121" *) 
  LUT2 #(
    .INIT(4'h6)) 
    \HDL_Counter_out1[6]_i_1__1 
       (.I0(HDL_Counter_out1_reg[6]),
        .I1(\HDL_Counter_out1[9]_i_4__4_n_0 ),
        .O(p_0_in__4[6]));
  (* SOFT_HLUTNM = "soft_lutpair121" *) 
  LUT3 #(
    .INIT(8'h6A)) 
    \HDL_Counter_out1[7]_i_1__4 
       (.I0(HDL_Counter_out1_reg[7]),
        .I1(\HDL_Counter_out1[9]_i_4__4_n_0 ),
        .I2(HDL_Counter_out1_reg[6]),
        .O(p_0_in__4[7]));
  (* SOFT_HLUTNM = "soft_lutpair119" *) 
  LUT4 #(
    .INIT(16'h6AAA)) 
    \HDL_Counter_out1[8]_i_1__4 
       (.I0(HDL_Counter_out1_reg[8]),
        .I1(HDL_Counter_out1_reg[6]),
        .I2(\HDL_Counter_out1[9]_i_4__4_n_0 ),
        .I3(HDL_Counter_out1_reg[7]),
        .O(p_0_in__4[8]));
  (* SOFT_HLUTNM = "soft_lutpair119" *) 
  LUT5 #(
    .INIT(32'h6AAAAAAA)) 
    \HDL_Counter_out1[9]_i_3__4 
       (.I0(HDL_Counter_out1_reg[9]),
        .I1(HDL_Counter_out1_reg[7]),
        .I2(\HDL_Counter_out1[9]_i_4__4_n_0 ),
        .I3(HDL_Counter_out1_reg[6]),
        .I4(HDL_Counter_out1_reg[8]),
        .O(p_0_in__4[9]));
  LUT6 #(
    .INIT(64'h8000000000000000)) 
    \HDL_Counter_out1[9]_i_4__4 
       (.I0(HDL_Counter_out1_reg[5]),
        .I1(HDL_Counter_out1_reg[4]),
        .I2(HDL_Counter_out1_reg[2]),
        .I3(HDL_Counter_out1_reg[0]),
        .I4(HDL_Counter_out1_reg[1]),
        .I5(HDL_Counter_out1_reg[3]),
        .O(\HDL_Counter_out1[9]_i_4__4_n_0 ));
  FDRE \HDL_Counter_out1_reg[0] 
       (.C(IPCORE_CLK),
        .CE(\HDL_Counter_out1_reg[9]_1 ),
        .D(p_0_in__4[0]),
        .Q(HDL_Counter_out1_reg[0]),
        .R(\HDL_Counter_out1_reg[9]_0 ));
  FDRE \HDL_Counter_out1_reg[1] 
       (.C(IPCORE_CLK),
        .CE(\HDL_Counter_out1_reg[9]_1 ),
        .D(p_0_in__4[1]),
        .Q(HDL_Counter_out1_reg[1]),
        .R(\HDL_Counter_out1_reg[9]_0 ));
  FDRE \HDL_Counter_out1_reg[2] 
       (.C(IPCORE_CLK),
        .CE(\HDL_Counter_out1_reg[9]_1 ),
        .D(p_0_in__4[2]),
        .Q(HDL_Counter_out1_reg[2]),
        .R(\HDL_Counter_out1_reg[9]_0 ));
  FDRE \HDL_Counter_out1_reg[3] 
       (.C(IPCORE_CLK),
        .CE(\HDL_Counter_out1_reg[9]_1 ),
        .D(p_0_in__4[3]),
        .Q(HDL_Counter_out1_reg[3]),
        .R(\HDL_Counter_out1_reg[9]_0 ));
  FDRE \HDL_Counter_out1_reg[4] 
       (.C(IPCORE_CLK),
        .CE(\HDL_Counter_out1_reg[9]_1 ),
        .D(p_0_in__4[4]),
        .Q(HDL_Counter_out1_reg[4]),
        .R(\HDL_Counter_out1_reg[9]_0 ));
  FDRE \HDL_Counter_out1_reg[5] 
       (.C(IPCORE_CLK),
        .CE(\HDL_Counter_out1_reg[9]_1 ),
        .D(p_0_in__4[5]),
        .Q(HDL_Counter_out1_reg[5]),
        .R(\HDL_Counter_out1_reg[9]_0 ));
  FDRE \HDL_Counter_out1_reg[6] 
       (.C(IPCORE_CLK),
        .CE(\HDL_Counter_out1_reg[9]_1 ),
        .D(p_0_in__4[6]),
        .Q(HDL_Counter_out1_reg[6]),
        .R(\HDL_Counter_out1_reg[9]_0 ));
  FDRE \HDL_Counter_out1_reg[7] 
       (.C(IPCORE_CLK),
        .CE(\HDL_Counter_out1_reg[9]_1 ),
        .D(p_0_in__4[7]),
        .Q(HDL_Counter_out1_reg[7]),
        .R(\HDL_Counter_out1_reg[9]_0 ));
  FDRE \HDL_Counter_out1_reg[8] 
       (.C(IPCORE_CLK),
        .CE(\HDL_Counter_out1_reg[9]_1 ),
        .D(p_0_in__4[8]),
        .Q(HDL_Counter_out1_reg[8]),
        .R(\HDL_Counter_out1_reg[9]_0 ));
  FDRE \HDL_Counter_out1_reg[9] 
       (.C(IPCORE_CLK),
        .CE(\HDL_Counter_out1_reg[9]_1 ),
        .D(p_0_in__4[9]),
        .Q(HDL_Counter_out1_reg[9]),
        .R(\HDL_Counter_out1_reg[9]_0 ));
  FDRE PipelineDelay1_out1_reg
       (.C(IPCORE_CLK),
        .CE(write_axi_enable),
        .D(Detect_Fall_Nonpositive2_out1),
        .Q(PipelineDelay1_out1_4),
        .R(reset_x));
  LUT6 #(
    .INIT(64'h6FF6FFFFFFFF6FF6)) 
    s4_out_INST_0_i_10
       (.I0(Q[0]),
        .I1(HDL_Counter_out1_reg[0]),
        .I2(HDL_Counter_out1_reg[1]),
        .I3(Q[1]),
        .I4(HDL_Counter_out1_reg[2]),
        .I5(Q[2]),
        .O(s4_out_INST_0_i_10_n_0));
  (* SOFT_HLUTNM = "soft_lutpair117" *) 
  LUT3 #(
    .INIT(8'h45)) 
    s4_out_INST_0_i_2
       (.I0(s4_out_INST_0_i_4_n_0),
        .I1(PipelineDelay1_out1_4),
        .I2(Delay2_delOut),
        .O(PipelineDelay1_out1_reg_0));
  LUT5 #(
    .INIT(32'h04000004)) 
    s4_out_INST_0_i_4
       (.I0(s4_out_INST_0_i_8_n_0),
        .I1(s4_out_INST_0_i_9_n_0),
        .I2(s4_out_INST_0_i_10_n_0),
        .I3(HDL_Counter_out1_reg[9]),
        .I4(Q[9]),
        .O(s4_out_INST_0_i_4_n_0));
  LUT6 #(
    .INIT(64'h6FF6FFFFFFFF6FF6)) 
    s4_out_INST_0_i_8
       (.I0(Q[3]),
        .I1(HDL_Counter_out1_reg[3]),
        .I2(HDL_Counter_out1_reg[4]),
        .I3(Q[4]),
        .I4(HDL_Counter_out1_reg[5]),
        .I5(Q[5]),
        .O(s4_out_INST_0_i_8_n_0));
  LUT6 #(
    .INIT(64'h9009000000009009)) 
    s4_out_INST_0_i_9
       (.I0(HDL_Counter_out1_reg[7]),
        .I1(Q[7]),
        .I2(HDL_Counter_out1_reg[8]),
        .I3(Q[8]),
        .I4(Q[6]),
        .I5(HDL_Counter_out1_reg[6]),
        .O(s4_out_INST_0_i_9_n_0));
  LUT6 #(
    .INIT(64'h8AAA8A8A20002020)) 
    s5_out_INST_0
       (.I0(s5_out_0),
        .I1(PipelineDelay1_out1_reg_0),
        .I2(S5),
        .I3(s5_out_1),
        .I4(S4),
        .I5(PipeDelay_out1),
        .O(s5_out));
  zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_src_Detect_Fall_Nonpositive2 u_Detect_Fall_Nonpositive2
       (.Detect_Fall_Nonpositive2_out1(Detect_Fall_Nonpositive2_out1),
        .IPCORE_CLK(IPCORE_CLK),
        .S5(S5),
        .reset_x(reset_x),
        .write_axi_enable(write_axi_enable));
endmodule

(* ORIG_REF_NAME = "uz_interlockDeadtime2L_src_Detect_Fall_Nonpositive2" *) 
module zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_src_Detect_Fall_Nonpositive2
   (Detect_Fall_Nonpositive2_out1,
    reset_x,
    write_axi_enable,
    IPCORE_CLK,
    S5);
  output Detect_Fall_Nonpositive2_out1;
  input reset_x;
  input write_axi_enable;
  input IPCORE_CLK;
  input S5;

  wire Detect_Fall_Nonpositive2_out1;
  wire IPCORE_CLK;
  wire S5;
  wire U_k_1;
  wire U_k_1_i_1__4_n_0;
  wire reset_x;
  wire write_axi_enable;

  (* SOFT_HLUTNM = "soft_lutpair116" *) 
  LUT2 #(
    .INIT(4'h1)) 
    PipelineDelay1_out1_i_1__4
       (.I0(U_k_1),
        .I1(S5),
        .O(Detect_Fall_Nonpositive2_out1));
  (* SOFT_HLUTNM = "soft_lutpair116" *) 
  LUT1 #(
    .INIT(2'h1)) 
    U_k_1_i_1__4
       (.I0(S5),
        .O(U_k_1_i_1__4_n_0));
  FDRE U_k_1_reg
       (.C(IPCORE_CLK),
        .CE(write_axi_enable),
        .D(U_k_1_i_1__4_n_0),
        .Q(U_k_1),
        .R(reset_x));
endmodule

(* ORIG_REF_NAME = "uz_interlockDeadtime2L_src_Detect_Fall_Nonpositive2" *) 
module zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_src_Detect_Fall_Nonpositive2_5
   (Detect_Fall_Nonpositive2_out1,
    reset_x,
    write_axi_enable,
    IPCORE_CLK,
    S4);
  output Detect_Fall_Nonpositive2_out1;
  input reset_x;
  input write_axi_enable;
  input IPCORE_CLK;
  input S4;

  wire Detect_Fall_Nonpositive2_out1;
  wire IPCORE_CLK;
  wire S4;
  wire U_k_1;
  wire U_k_1_i_1__3_n_0;
  wire reset_x;
  wire write_axi_enable;

  (* SOFT_HLUTNM = "soft_lutpair110" *) 
  LUT2 #(
    .INIT(4'h1)) 
    PipelineDelay1_out1_i_1__3
       (.I0(U_k_1),
        .I1(S4),
        .O(Detect_Fall_Nonpositive2_out1));
  (* SOFT_HLUTNM = "soft_lutpair110" *) 
  LUT1 #(
    .INIT(2'h1)) 
    U_k_1_i_1__3
       (.I0(S4),
        .O(U_k_1_i_1__3_n_0));
  FDRE U_k_1_reg
       (.C(IPCORE_CLK),
        .CE(write_axi_enable),
        .D(U_k_1_i_1__3_n_0),
        .Q(U_k_1),
        .R(reset_x));
endmodule

(* ORIG_REF_NAME = "uz_interlockDeadtime2L_src_Detect_Fall_Nonpositive2" *) 
module zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_src_Detect_Fall_Nonpositive2_6
   (Detect_Fall_Nonpositive2_out1,
    reset_x,
    write_axi_enable,
    IPCORE_CLK,
    S3);
  output Detect_Fall_Nonpositive2_out1;
  input reset_x;
  input write_axi_enable;
  input IPCORE_CLK;
  input S3;

  wire Detect_Fall_Nonpositive2_out1;
  wire IPCORE_CLK;
  wire S3;
  wire U_k_1;
  wire U_k_1_i_1__2_n_0;
  wire reset_x;
  wire write_axi_enable;

  (* SOFT_HLUTNM = "soft_lutpair104" *) 
  LUT2 #(
    .INIT(4'h1)) 
    PipelineDelay1_out1_i_1__2
       (.I0(U_k_1),
        .I1(S3),
        .O(Detect_Fall_Nonpositive2_out1));
  (* SOFT_HLUTNM = "soft_lutpair104" *) 
  LUT1 #(
    .INIT(2'h1)) 
    U_k_1_i_1__2
       (.I0(S3),
        .O(U_k_1_i_1__2_n_0));
  FDRE U_k_1_reg
       (.C(IPCORE_CLK),
        .CE(write_axi_enable),
        .D(U_k_1_i_1__2_n_0),
        .Q(U_k_1),
        .R(reset_x));
endmodule

(* ORIG_REF_NAME = "uz_interlockDeadtime2L_src_Detect_Fall_Nonpositive2" *) 
module zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_src_Detect_Fall_Nonpositive2_7
   (Detect_Fall_Nonpositive2_out1,
    reset_x,
    write_axi_enable,
    IPCORE_CLK,
    S2);
  output Detect_Fall_Nonpositive2_out1;
  input reset_x;
  input write_axi_enable;
  input IPCORE_CLK;
  input S2;

  wire Detect_Fall_Nonpositive2_out1;
  wire IPCORE_CLK;
  wire S2;
  wire U_k_1;
  wire U_k_1_i_1__1_n_0;
  wire reset_x;
  wire write_axi_enable;

  (* SOFT_HLUTNM = "soft_lutpair98" *) 
  LUT2 #(
    .INIT(4'h1)) 
    PipelineDelay1_out1_i_1__1
       (.I0(U_k_1),
        .I1(S2),
        .O(Detect_Fall_Nonpositive2_out1));
  (* SOFT_HLUTNM = "soft_lutpair98" *) 
  LUT1 #(
    .INIT(2'h1)) 
    U_k_1_i_1__1
       (.I0(S2),
        .O(U_k_1_i_1__1_n_0));
  FDRE U_k_1_reg
       (.C(IPCORE_CLK),
        .CE(write_axi_enable),
        .D(U_k_1_i_1__1_n_0),
        .Q(U_k_1),
        .R(reset_x));
endmodule

(* ORIG_REF_NAME = "uz_interlockDeadtime2L_src_Detect_Fall_Nonpositive2" *) 
module zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_src_Detect_Fall_Nonpositive2_8
   (Detect_Fall_Nonpositive2_out1,
    reset_x,
    write_axi_enable,
    IPCORE_CLK,
    S1);
  output Detect_Fall_Nonpositive2_out1;
  input reset_x;
  input write_axi_enable;
  input IPCORE_CLK;
  input S1;

  wire Detect_Fall_Nonpositive2_out1;
  wire IPCORE_CLK;
  wire S1;
  wire U_k_1;
  wire U_k_1_i_1__0_n_0;
  wire reset_x;
  wire write_axi_enable;

  (* SOFT_HLUTNM = "soft_lutpair92" *) 
  LUT2 #(
    .INIT(4'h1)) 
    PipelineDelay1_out1_i_1__0
       (.I0(U_k_1),
        .I1(S1),
        .O(Detect_Fall_Nonpositive2_out1));
  (* SOFT_HLUTNM = "soft_lutpair92" *) 
  LUT1 #(
    .INIT(2'h1)) 
    U_k_1_i_1__0
       (.I0(S1),
        .O(U_k_1_i_1__0_n_0));
  FDRE U_k_1_reg
       (.C(IPCORE_CLK),
        .CE(write_axi_enable),
        .D(U_k_1_i_1__0_n_0),
        .Q(U_k_1),
        .R(reset_x));
endmodule

(* ORIG_REF_NAME = "uz_interlockDeadtime2L_src_Detect_Fall_Nonpositive2" *) 
module zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_src_Detect_Fall_Nonpositive2_9
   (Detect_Fall_Nonpositive2_out1,
    reset_x,
    write_axi_enable,
    IPCORE_CLK,
    S0);
  output Detect_Fall_Nonpositive2_out1;
  input reset_x;
  input write_axi_enable;
  input IPCORE_CLK;
  input S0;

  wire Detect_Fall_Nonpositive2_out1;
  wire IPCORE_CLK;
  wire S0;
  wire U_k_1;
  wire U_k_1_i_1_n_0;
  wire reset_x;
  wire write_axi_enable;

  (* SOFT_HLUTNM = "soft_lutpair86" *) 
  LUT2 #(
    .INIT(4'h1)) 
    PipelineDelay1_out1_i_1
       (.I0(U_k_1),
        .I1(S0),
        .O(Detect_Fall_Nonpositive2_out1));
  (* SOFT_HLUTNM = "soft_lutpair86" *) 
  LUT1 #(
    .INIT(2'h1)) 
    U_k_1_i_1
       (.I0(S0),
        .O(U_k_1_i_1_n_0));
  FDRE U_k_1_reg
       (.C(IPCORE_CLK),
        .CE(write_axi_enable),
        .D(U_k_1_i_1_n_0),
        .Q(U_k_1),
        .R(reset_x));
endmodule

(* ORIG_REF_NAME = "uz_interlockDeadtime2L_src_InverseBotSwitchModule" *) 
module zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_src_InverseBotSwitchModule
   (PipeDelay_out1,
    reset_x,
    write_axi_enable,
    Delay3_out1,
    IPCORE_CLK);
  output PipeDelay_out1;
  input reset_x;
  input write_axi_enable;
  input Delay3_out1;
  input IPCORE_CLK;

  wire Delay3_out1;
  wire IPCORE_CLK;
  wire PipeDelay_out1;
  wire reset_x;
  wire write_axi_enable;

  FDRE PipeDelay_out1_reg
       (.C(IPCORE_CLK),
        .CE(write_axi_enable),
        .D(Delay3_out1),
        .Q(PipeDelay_out1),
        .R(reset_x));
endmodule

(* ORIG_REF_NAME = "uz_interlockDeadtime2L_src_uz_interlockDeadtime2L" *) 
module zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_src_uz_interlockDeadtime2L
   (Delay_out1_reg_0,
    Delay3_out1,
    PipelineDelay1_out1,
    PipelineDelay1_out1_0,
    PipelineDelay1_out1_1,
    PipelineDelay1_out1_2,
    PipelineDelay1_out1_3,
    PipelineDelay1_out1_4,
    s1_out,
    s0_out,
    Q,
    s3_out,
    s2_out,
    s5_out,
    s4_out,
    reset_x,
    write_axi_enable,
    axi_EnableOutput,
    IPCORE_CLK,
    axi_InverseBotSwitch,
    Delay2_delOut_reg,
    S0,
    S1,
    S2,
    S3,
    S4,
    S5,
    D,
    SR,
    E,
    \HDL_Counter_out1_reg[9] ,
    \HDL_Counter_out1_reg[9]_0 ,
    \HDL_Counter_out1_reg[9]_1 ,
    \HDL_Counter_out1_reg[9]_2 ,
    \HDL_Counter_out1_reg[9]_3 ,
    \HDL_Counter_out1_reg[9]_4 ,
    \HDL_Counter_out1_reg[9]_5 ,
    \HDL_Counter_out1_reg[9]_6 ,
    \HDL_Counter_out1_reg[9]_7 ,
    \HDL_Counter_out1_reg[9]_8 );
  output Delay_out1_reg_0;
  output Delay3_out1;
  output PipelineDelay1_out1;
  output PipelineDelay1_out1_0;
  output PipelineDelay1_out1_1;
  output PipelineDelay1_out1_2;
  output PipelineDelay1_out1_3;
  output PipelineDelay1_out1_4;
  output s1_out;
  output s0_out;
  output [9:0]Q;
  output s3_out;
  output s2_out;
  output s5_out;
  output s4_out;
  input reset_x;
  input write_axi_enable;
  input axi_EnableOutput;
  input IPCORE_CLK;
  input axi_InverseBotSwitch;
  input Delay2_delOut_reg;
  input S0;
  input S1;
  input S2;
  input S3;
  input S4;
  input S5;
  input [9:0]D;
  input [0:0]SR;
  input [0:0]E;
  input [0:0]\HDL_Counter_out1_reg[9] ;
  input [0:0]\HDL_Counter_out1_reg[9]_0 ;
  input [0:0]\HDL_Counter_out1_reg[9]_1 ;
  input [0:0]\HDL_Counter_out1_reg[9]_2 ;
  input [0:0]\HDL_Counter_out1_reg[9]_3 ;
  input [0:0]\HDL_Counter_out1_reg[9]_4 ;
  input [0:0]\HDL_Counter_out1_reg[9]_5 ;
  input [0:0]\HDL_Counter_out1_reg[9]_6 ;
  input [0:0]\HDL_Counter_out1_reg[9]_7 ;
  input [0:0]\HDL_Counter_out1_reg[9]_8 ;

  wire [9:0]D;
  wire Delay2_delOut_reg;
  wire Delay3_out1;
  wire Delay_out1_reg_0;
  wire [0:0]E;
  wire \GEN_LABEL1[2].u_InverseBotSwitchModule/PipeDelay_out1 ;
  wire \GEN_LABEL3[0].u_DeadtimeModule_n_2 ;
  wire \GEN_LABEL3[1].u_DeadtimeModule_n_2 ;
  wire \GEN_LABEL3[2].u_DeadtimeModule_n_2 ;
  wire \GEN_LABEL3[3].u_DeadtimeModule_n_2 ;
  wire \GEN_LABEL3[4].u_DeadtimeModule_n_2 ;
  wire \GEN_LABEL3[5].u_DeadtimeModule_n_2 ;
  wire [0:0]\HDL_Counter_out1_reg[9] ;
  wire [0:0]\HDL_Counter_out1_reg[9]_0 ;
  wire [0:0]\HDL_Counter_out1_reg[9]_1 ;
  wire [0:0]\HDL_Counter_out1_reg[9]_2 ;
  wire [0:0]\HDL_Counter_out1_reg[9]_3 ;
  wire [0:0]\HDL_Counter_out1_reg[9]_4 ;
  wire [0:0]\HDL_Counter_out1_reg[9]_5 ;
  wire [0:0]\HDL_Counter_out1_reg[9]_6 ;
  wire [0:0]\HDL_Counter_out1_reg[9]_7 ;
  wire [0:0]\HDL_Counter_out1_reg[9]_8 ;
  wire IPCORE_CLK;
  wire PipelineDelay1_out1;
  wire PipelineDelay1_out1_0;
  wire PipelineDelay1_out1_1;
  wire PipelineDelay1_out1_2;
  wire PipelineDelay1_out1_3;
  wire PipelineDelay1_out1_4;
  wire [9:0]Q;
  wire S0;
  wire S1;
  wire S2;
  wire S3;
  wire S4;
  wire S5;
  wire [0:0]SR;
  wire axi_EnableOutput;
  wire axi_InverseBotSwitch;
  wire reset_x;
  wire s0_out;
  wire s1_out;
  wire s2_out;
  wire s3_out;
  wire s4_out;
  wire s5_out;
  wire write_axi_enable;

  FDRE \Delay2_out1_reg[0] 
       (.C(IPCORE_CLK),
        .CE(write_axi_enable),
        .D(D[0]),
        .Q(Q[0]),
        .R(reset_x));
  FDRE \Delay2_out1_reg[1] 
       (.C(IPCORE_CLK),
        .CE(write_axi_enable),
        .D(D[1]),
        .Q(Q[1]),
        .R(reset_x));
  FDRE \Delay2_out1_reg[2] 
       (.C(IPCORE_CLK),
        .CE(write_axi_enable),
        .D(D[2]),
        .Q(Q[2]),
        .R(reset_x));
  FDRE \Delay2_out1_reg[3] 
       (.C(IPCORE_CLK),
        .CE(write_axi_enable),
        .D(D[3]),
        .Q(Q[3]),
        .R(reset_x));
  FDRE \Delay2_out1_reg[4] 
       (.C(IPCORE_CLK),
        .CE(write_axi_enable),
        .D(D[4]),
        .Q(Q[4]),
        .R(reset_x));
  FDRE \Delay2_out1_reg[5] 
       (.C(IPCORE_CLK),
        .CE(write_axi_enable),
        .D(D[5]),
        .Q(Q[5]),
        .R(reset_x));
  FDRE \Delay2_out1_reg[6] 
       (.C(IPCORE_CLK),
        .CE(write_axi_enable),
        .D(D[6]),
        .Q(Q[6]),
        .R(reset_x));
  FDRE \Delay2_out1_reg[7] 
       (.C(IPCORE_CLK),
        .CE(write_axi_enable),
        .D(D[7]),
        .Q(Q[7]),
        .R(reset_x));
  FDRE \Delay2_out1_reg[8] 
       (.C(IPCORE_CLK),
        .CE(write_axi_enable),
        .D(D[8]),
        .Q(Q[8]),
        .R(reset_x));
  FDRE \Delay2_out1_reg[9] 
       (.C(IPCORE_CLK),
        .CE(write_axi_enable),
        .D(D[9]),
        .Q(Q[9]),
        .R(reset_x));
  FDRE Delay3_out1_reg
       (.C(IPCORE_CLK),
        .CE(write_axi_enable),
        .D(axi_InverseBotSwitch),
        .Q(Delay3_out1),
        .R(reset_x));
  FDRE Delay_out1_reg
       (.C(IPCORE_CLK),
        .CE(write_axi_enable),
        .D(axi_EnableOutput),
        .Q(Delay_out1_reg_0),
        .R(reset_x));
  zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_src_InverseBotSwitchModule \GEN_LABEL1[0].u_InverseBotSwitchModule 
       (.Delay3_out1(Delay3_out1),
        .IPCORE_CLK(IPCORE_CLK),
        .PipeDelay_out1(\GEN_LABEL1[2].u_InverseBotSwitchModule/PipeDelay_out1 ),
        .reset_x(reset_x),
        .write_axi_enable(write_axi_enable));
  zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_src_DeadtimeModule \GEN_LABEL3[0].u_DeadtimeModule 
       (.Delay2_delOut_reg_0(Delay2_delOut_reg),
        .E(E),
        .IPCORE_CLK(IPCORE_CLK),
        .PipelineDelay1_out1(PipelineDelay1_out1),
        .PipelineDelay1_out1_reg_0(\GEN_LABEL3[0].u_DeadtimeModule_n_2 ),
        .Q(Q),
        .S0(S0),
        .S1(S1),
        .SR(SR),
        .reset_x(reset_x),
        .s0_out(s0_out),
        .s0_out_0(Delay_out1_reg_0),
        .s0_out_1(\GEN_LABEL3[1].u_DeadtimeModule_n_2 ),
        .write_axi_enable(write_axi_enable));
  zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_src_DeadtimeModule_0 \GEN_LABEL3[1].u_DeadtimeModule 
       (.Delay2_delOut_reg_0(Delay2_delOut_reg),
        .\HDL_Counter_out1_reg[9]_0 (\HDL_Counter_out1_reg[9] ),
        .\HDL_Counter_out1_reg[9]_1 (\HDL_Counter_out1_reg[9]_0 ),
        .IPCORE_CLK(IPCORE_CLK),
        .PipeDelay_out1(\GEN_LABEL1[2].u_InverseBotSwitchModule/PipeDelay_out1 ),
        .PipelineDelay1_out1_0(PipelineDelay1_out1_0),
        .PipelineDelay1_out1_reg_0(\GEN_LABEL3[1].u_DeadtimeModule_n_2 ),
        .Q(Q),
        .S0(S0),
        .S1(S1),
        .reset_x(reset_x),
        .s1_out(s1_out),
        .s1_out_0(Delay_out1_reg_0),
        .s1_out_1(\GEN_LABEL3[0].u_DeadtimeModule_n_2 ),
        .write_axi_enable(write_axi_enable));
  zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_src_DeadtimeModule_1 \GEN_LABEL3[2].u_DeadtimeModule 
       (.Delay2_delOut_reg_0(Delay2_delOut_reg),
        .\HDL_Counter_out1_reg[9]_0 (\HDL_Counter_out1_reg[9]_1 ),
        .\HDL_Counter_out1_reg[9]_1 (\HDL_Counter_out1_reg[9]_2 ),
        .IPCORE_CLK(IPCORE_CLK),
        .PipelineDelay1_out1_1(PipelineDelay1_out1_1),
        .PipelineDelay1_out1_reg_0(\GEN_LABEL3[2].u_DeadtimeModule_n_2 ),
        .Q(Q),
        .S2(S2),
        .S3(S3),
        .reset_x(reset_x),
        .s2_out(s2_out),
        .s2_out_0(Delay_out1_reg_0),
        .s2_out_1(\GEN_LABEL3[3].u_DeadtimeModule_n_2 ),
        .write_axi_enable(write_axi_enable));
  zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_src_DeadtimeModule_2 \GEN_LABEL3[3].u_DeadtimeModule 
       (.Delay2_delOut_reg_0(Delay2_delOut_reg),
        .\HDL_Counter_out1_reg[9]_0 (\HDL_Counter_out1_reg[9]_3 ),
        .\HDL_Counter_out1_reg[9]_1 (\HDL_Counter_out1_reg[9]_4 ),
        .IPCORE_CLK(IPCORE_CLK),
        .PipeDelay_out1(\GEN_LABEL1[2].u_InverseBotSwitchModule/PipeDelay_out1 ),
        .PipelineDelay1_out1_2(PipelineDelay1_out1_2),
        .PipelineDelay1_out1_reg_0(\GEN_LABEL3[3].u_DeadtimeModule_n_2 ),
        .Q(Q),
        .S2(S2),
        .S3(S3),
        .reset_x(reset_x),
        .s3_out(s3_out),
        .s3_out_0(Delay_out1_reg_0),
        .s3_out_1(\GEN_LABEL3[2].u_DeadtimeModule_n_2 ),
        .write_axi_enable(write_axi_enable));
  zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_src_DeadtimeModule_3 \GEN_LABEL3[4].u_DeadtimeModule 
       (.Delay2_delOut_reg_0(Delay2_delOut_reg),
        .\HDL_Counter_out1_reg[9]_0 (\HDL_Counter_out1_reg[9]_5 ),
        .\HDL_Counter_out1_reg[9]_1 (\HDL_Counter_out1_reg[9]_6 ),
        .IPCORE_CLK(IPCORE_CLK),
        .PipelineDelay1_out1_3(PipelineDelay1_out1_3),
        .PipelineDelay1_out1_reg_0(\GEN_LABEL3[4].u_DeadtimeModule_n_2 ),
        .Q(Q),
        .S4(S4),
        .S5(S5),
        .reset_x(reset_x),
        .s4_out(s4_out),
        .s4_out_0(Delay_out1_reg_0),
        .s4_out_1(\GEN_LABEL3[5].u_DeadtimeModule_n_2 ),
        .write_axi_enable(write_axi_enable));
  zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_src_DeadtimeModule_4 \GEN_LABEL3[5].u_DeadtimeModule 
       (.Delay2_delOut_reg_0(Delay2_delOut_reg),
        .\HDL_Counter_out1_reg[9]_0 (\HDL_Counter_out1_reg[9]_7 ),
        .\HDL_Counter_out1_reg[9]_1 (\HDL_Counter_out1_reg[9]_8 ),
        .IPCORE_CLK(IPCORE_CLK),
        .PipeDelay_out1(\GEN_LABEL1[2].u_InverseBotSwitchModule/PipeDelay_out1 ),
        .PipelineDelay1_out1_4(PipelineDelay1_out1_4),
        .PipelineDelay1_out1_reg_0(\GEN_LABEL3[5].u_DeadtimeModule_n_2 ),
        .Q(Q),
        .S4(S4),
        .S5(S5),
        .reset_x(reset_x),
        .s5_out(s5_out),
        .s5_out_0(Delay_out1_reg_0),
        .s5_out_1(\GEN_LABEL3[4].u_DeadtimeModule_n_2 ),
        .write_axi_enable(write_axi_enable));
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
