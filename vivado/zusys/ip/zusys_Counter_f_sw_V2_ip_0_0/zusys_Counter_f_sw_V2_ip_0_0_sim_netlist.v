// Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// --------------------------------------------------------------------------------
// Tool Version: Vivado v.2020.1.1 (win64) Build 2960000 Wed Aug  5 22:57:20 MDT 2020
// Date        : Fri Jan 28 14:43:12 2022
// Host        : enc177112 running 64-bit major release  (build 9200)
// Command     : write_verilog -force -mode funcsim
//               c:/GIT/UltraZohm/software/ultrazohm_sw_develop/vivado/zusys/ip/zusys_Counter_f_sw_V2_ip_0_0/zusys_Counter_f_sw_V2_ip_0_0_sim_netlist.v
// Design      : zusys_Counter_f_sw_V2_ip_0_0
// Purpose     : This verilog netlist is a functional simulation representation of the design and should not be modified
//               or synthesized. This netlist cannot be used for SDF annotated simulation.
// Device      : xczu9eg-ffvc900-1-e
// --------------------------------------------------------------------------------
`timescale 1 ps / 1 ps

(* CHECK_LICENSE_TYPE = "zusys_Counter_f_sw_V2_ip_0_0,Counter_f_sw_V2_ip,{}" *) (* downgradeipidentifiedwarnings = "yes" *) (* ip_definition_source = "package_project" *) 
(* x_core_info = "Counter_f_sw_V2_ip,Vivado 2020.1.1" *) 
(* NotValidForBitStream *)
module zusys_Counter_f_sw_V2_ip_0_0
   (IPCORE_CLK,
    IPCORE_RESETN,
    ss_in_0,
    ss_in_1,
    ss_in_2,
    ss_in_3,
    ss_in_4,
    ss_in_5,
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
    switchNumb,
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
  input ss_in_0;
  input ss_in_1;
  input ss_in_2;
  input ss_in_3;
  input ss_in_4;
  input ss_in_5;
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
  output [24:0]switchNumb;
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
  wire [29:0]\^AXI4_Lite_RDATA ;
  wire AXI4_Lite_RREADY;
  wire AXI4_Lite_RVALID;
  wire [31:0]AXI4_Lite_WDATA;
  wire AXI4_Lite_WREADY;
  wire [3:0]AXI4_Lite_WSTRB;
  wire AXI4_Lite_WVALID;
  wire IPCORE_CLK;
  wire IPCORE_RESETN;
  wire ss_in_0;
  wire ss_in_1;
  wire ss_in_2;
  wire ss_in_3;
  wire ss_in_4;
  wire ss_in_5;
  wire [24:0]switchNumb;

  assign AXI4_Lite_BRESP[1] = \<const0> ;
  assign AXI4_Lite_BRESP[0] = \<const0> ;
  assign AXI4_Lite_RDATA[31] = \<const0> ;
  assign AXI4_Lite_RDATA[30] = \^AXI4_Lite_RDATA [29];
  assign AXI4_Lite_RDATA[29] = \^AXI4_Lite_RDATA [29];
  assign AXI4_Lite_RDATA[28] = \^AXI4_Lite_RDATA [29];
  assign AXI4_Lite_RDATA[27] = \<const0> ;
  assign AXI4_Lite_RDATA[26] = \^AXI4_Lite_RDATA [29];
  assign AXI4_Lite_RDATA[25] = \^AXI4_Lite_RDATA [29];
  assign AXI4_Lite_RDATA[24:0] = \^AXI4_Lite_RDATA [24:0];
  assign AXI4_Lite_RRESP[1] = \<const0> ;
  assign AXI4_Lite_RRESP[0] = \<const0> ;
  GND GND
       (.G(\<const0> ));
  zusys_Counter_f_sw_V2_ip_0_0_Counter_f_sw_V2_ip U0
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
        .AXI4_Lite_RDATA({\^AXI4_Lite_RDATA [29],\^AXI4_Lite_RDATA [24:0]}),
        .AXI4_Lite_RREADY(AXI4_Lite_RREADY),
        .AXI4_Lite_RVALID(AXI4_Lite_RVALID),
        .AXI4_Lite_WDATA(AXI4_Lite_WDATA[0]),
        .AXI4_Lite_WREADY(AXI4_Lite_WREADY),
        .AXI4_Lite_WSTRB(AXI4_Lite_WSTRB),
        .AXI4_Lite_WVALID(AXI4_Lite_WVALID),
        .IPCORE_CLK(IPCORE_CLK),
        .IPCORE_RESETN(IPCORE_RESETN),
        .ss_in_0(ss_in_0),
        .ss_in_1(ss_in_1),
        .ss_in_2(ss_in_2),
        .ss_in_3(ss_in_3),
        .ss_in_4(ss_in_4),
        .ss_in_5(ss_in_5),
        .switchNumb(switchNumb));
endmodule

(* ORIG_REF_NAME = "Counter_f_sw_V2_ip" *) 
module zusys_Counter_f_sw_V2_ip_0_0_Counter_f_sw_V2_ip
   (AXI4_Lite_RVALID,
    AXI4_Lite_BVALID,
    AXI4_Lite_WREADY,
    switchNumb,
    AXI4_Lite_RDATA,
    AXI4_Lite_ARREADY,
    AXI4_Lite_AWREADY,
    AXI4_Lite_ACLK,
    ss_in_5,
    IPCORE_CLK,
    ss_in_4,
    ss_in_3,
    ss_in_2,
    ss_in_1,
    ss_in_0,
    AXI4_Lite_AWADDR,
    AXI4_Lite_ARADDR,
    AXI4_Lite_ARVALID,
    AXI4_Lite_ARESETN,
    AXI4_Lite_RREADY,
    AXI4_Lite_AWVALID,
    AXI4_Lite_WVALID,
    IPCORE_RESETN,
    AXI4_Lite_BREADY,
    AXI4_Lite_WSTRB,
    AXI4_Lite_WDATA);
  output AXI4_Lite_RVALID;
  output AXI4_Lite_BVALID;
  output AXI4_Lite_WREADY;
  output [24:0]switchNumb;
  output [25:0]AXI4_Lite_RDATA;
  output AXI4_Lite_ARREADY;
  output AXI4_Lite_AWREADY;
  input AXI4_Lite_ACLK;
  input ss_in_5;
  input IPCORE_CLK;
  input ss_in_4;
  input ss_in_3;
  input ss_in_2;
  input ss_in_1;
  input ss_in_0;
  input [13:0]AXI4_Lite_AWADDR;
  input [13:0]AXI4_Lite_ARADDR;
  input AXI4_Lite_ARVALID;
  input AXI4_Lite_ARESETN;
  input AXI4_Lite_RREADY;
  input AXI4_Lite_AWVALID;
  input AXI4_Lite_WVALID;
  input IPCORE_RESETN;
  input AXI4_Lite_BREADY;
  input [3:0]AXI4_Lite_WSTRB;
  input [0:0]AXI4_Lite_WDATA;

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
  wire [25:0]AXI4_Lite_RDATA;
  wire AXI4_Lite_RREADY;
  wire AXI4_Lite_RVALID;
  wire [0:0]AXI4_Lite_WDATA;
  wire AXI4_Lite_WREADY;
  wire [3:0]AXI4_Lite_WSTRB;
  wire AXI4_Lite_WVALID;
  wire IPCORE_CLK;
  wire IPCORE_RESETN;
  wire bResetAXI;
  wire reset;
  wire ss_in_0;
  wire ss_in_1;
  wire ss_in_2;
  wire ss_in_3;
  wire ss_in_4;
  wire ss_in_5;
  wire [24:0]switchNumb;
  wire \u_Counter_f_sw_V2_ip_axi_lite_module_inst/soft_reset ;
  wire write_axi_enable;

  zusys_Counter_f_sw_V2_ip_0_0_Counter_f_sw_V2_ip_axi_lite u_Counter_f_sw_V2_ip_axi_lite_inst
       (.AXI4_Lite_ACLK(AXI4_Lite_ACLK),
        .AXI4_Lite_ARADDR(AXI4_Lite_ARADDR),
        .AXI4_Lite_ARESETN(AXI4_Lite_ARESETN),
        .AXI4_Lite_ARREADY(AXI4_Lite_ARREADY),
        .AXI4_Lite_ARVALID(AXI4_Lite_ARVALID),
        .AXI4_Lite_AWADDR(AXI4_Lite_AWADDR),
        .AXI4_Lite_AWREADY(AXI4_Lite_AWREADY),
        .AXI4_Lite_AWVALID(AXI4_Lite_AWVALID),
        .AXI4_Lite_BREADY(AXI4_Lite_BREADY),
        .AXI4_Lite_RDATA(AXI4_Lite_RDATA),
        .AXI4_Lite_RREADY(AXI4_Lite_RREADY),
        .AXI4_Lite_RVALID(AXI4_Lite_RVALID),
        .AXI4_Lite_WDATA(AXI4_Lite_WDATA),
        .AXI4_Lite_WSTRB(AXI4_Lite_WSTRB),
        .AXI4_Lite_WVALID(AXI4_Lite_WVALID),
        .IPCORE_RESETN(IPCORE_RESETN),
        .Q({AXI4_Lite_BVALID,AXI4_Lite_WREADY}),
        .SR(reset),
        .bResetAXI(bResetAXI),
        .soft_reset(\u_Counter_f_sw_V2_ip_axi_lite_module_inst/soft_reset ),
        .switchNumb(switchNumb),
        .write_axi_enable(write_axi_enable));
  zusys_Counter_f_sw_V2_ip_0_0_Counter_f_sw_V2_ip_dut u_Counter_f_sw_V2_ip_dut_inst
       (.AXI4_Lite_ARESETN(AXI4_Lite_ARESETN),
        .E(write_axi_enable),
        .IPCORE_CLK(IPCORE_CLK),
        .IPCORE_RESETN(IPCORE_RESETN),
        .SR(reset),
        .bResetAXI(bResetAXI),
        .soft_reset(\u_Counter_f_sw_V2_ip_axi_lite_module_inst/soft_reset ),
        .ss_in_0(ss_in_0),
        .ss_in_1(ss_in_1),
        .ss_in_2(ss_in_2),
        .ss_in_3(ss_in_3),
        .ss_in_4(ss_in_4),
        .ss_in_5(ss_in_5),
        .switchNumb(switchNumb));
endmodule

(* ORIG_REF_NAME = "Counter_f_sw_V2_ip_addr_decoder" *) 
module zusys_Counter_f_sw_V2_ip_0_0_Counter_f_sw_V2_ip_addr_decoder
   (read_reg_ip_timestamp,
    write_axi_enable,
    bResetAXI,
    Q,
    SR,
    AXI4_Lite_ACLK,
    write_reg_axi_enable_reg_0,
    write_reg_bResetAXI_reg_0,
    switchNumb);
  output [0:0]read_reg_ip_timestamp;
  output write_axi_enable;
  output bResetAXI;
  output [24:0]Q;
  input [0:0]SR;
  input AXI4_Lite_ACLK;
  input write_reg_axi_enable_reg_0;
  input write_reg_bResetAXI_reg_0;
  input [24:0]switchNumb;

  wire AXI4_Lite_ACLK;
  wire [24:0]Q;
  wire [0:0]SR;
  wire bResetAXI;
  wire [0:0]read_reg_ip_timestamp;
  wire [24:0]switchNumb;
  wire write_axi_enable;
  wire write_reg_axi_enable_reg_0;
  wire write_reg_bResetAXI_reg_0;

  FDRE \read_reg_ip_timestamp_reg[30] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(1'b1),
        .Q(read_reg_ip_timestamp),
        .R(SR));
  FDRE \read_reg_switchNumb_AXI_reg[0] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(switchNumb[0]),
        .Q(Q[0]),
        .R(SR));
  FDRE \read_reg_switchNumb_AXI_reg[10] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(switchNumb[10]),
        .Q(Q[10]),
        .R(SR));
  FDRE \read_reg_switchNumb_AXI_reg[11] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(switchNumb[11]),
        .Q(Q[11]),
        .R(SR));
  FDRE \read_reg_switchNumb_AXI_reg[12] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(switchNumb[12]),
        .Q(Q[12]),
        .R(SR));
  FDRE \read_reg_switchNumb_AXI_reg[13] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(switchNumb[13]),
        .Q(Q[13]),
        .R(SR));
  FDRE \read_reg_switchNumb_AXI_reg[14] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(switchNumb[14]),
        .Q(Q[14]),
        .R(SR));
  FDRE \read_reg_switchNumb_AXI_reg[15] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(switchNumb[15]),
        .Q(Q[15]),
        .R(SR));
  FDRE \read_reg_switchNumb_AXI_reg[16] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(switchNumb[16]),
        .Q(Q[16]),
        .R(SR));
  FDRE \read_reg_switchNumb_AXI_reg[17] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(switchNumb[17]),
        .Q(Q[17]),
        .R(SR));
  FDRE \read_reg_switchNumb_AXI_reg[18] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(switchNumb[18]),
        .Q(Q[18]),
        .R(SR));
  FDRE \read_reg_switchNumb_AXI_reg[19] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(switchNumb[19]),
        .Q(Q[19]),
        .R(SR));
  FDRE \read_reg_switchNumb_AXI_reg[1] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(switchNumb[1]),
        .Q(Q[1]),
        .R(SR));
  FDRE \read_reg_switchNumb_AXI_reg[20] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(switchNumb[20]),
        .Q(Q[20]),
        .R(SR));
  FDRE \read_reg_switchNumb_AXI_reg[21] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(switchNumb[21]),
        .Q(Q[21]),
        .R(SR));
  FDRE \read_reg_switchNumb_AXI_reg[22] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(switchNumb[22]),
        .Q(Q[22]),
        .R(SR));
  FDRE \read_reg_switchNumb_AXI_reg[23] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(switchNumb[23]),
        .Q(Q[23]),
        .R(SR));
  FDRE \read_reg_switchNumb_AXI_reg[24] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(switchNumb[24]),
        .Q(Q[24]),
        .R(SR));
  FDRE \read_reg_switchNumb_AXI_reg[2] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(switchNumb[2]),
        .Q(Q[2]),
        .R(SR));
  FDRE \read_reg_switchNumb_AXI_reg[3] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(switchNumb[3]),
        .Q(Q[3]),
        .R(SR));
  FDRE \read_reg_switchNumb_AXI_reg[4] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(switchNumb[4]),
        .Q(Q[4]),
        .R(SR));
  FDRE \read_reg_switchNumb_AXI_reg[5] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(switchNumb[5]),
        .Q(Q[5]),
        .R(SR));
  FDRE \read_reg_switchNumb_AXI_reg[6] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(switchNumb[6]),
        .Q(Q[6]),
        .R(SR));
  FDRE \read_reg_switchNumb_AXI_reg[7] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(switchNumb[7]),
        .Q(Q[7]),
        .R(SR));
  FDRE \read_reg_switchNumb_AXI_reg[8] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(switchNumb[8]),
        .Q(Q[8]),
        .R(SR));
  FDRE \read_reg_switchNumb_AXI_reg[9] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(switchNumb[9]),
        .Q(Q[9]),
        .R(SR));
  FDSE write_reg_axi_enable_reg
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(write_reg_axi_enable_reg_0),
        .Q(write_axi_enable),
        .S(SR));
  FDRE write_reg_bResetAXI_reg
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(write_reg_bResetAXI_reg_0),
        .Q(bResetAXI),
        .R(SR));
endmodule

(* ORIG_REF_NAME = "Counter_f_sw_V2_ip_axi_lite" *) 
module zusys_Counter_f_sw_V2_ip_0_0_Counter_f_sw_V2_ip_axi_lite
   (AXI4_Lite_RVALID,
    SR,
    write_axi_enable,
    soft_reset,
    bResetAXI,
    Q,
    AXI4_Lite_RDATA,
    AXI4_Lite_ARREADY,
    AXI4_Lite_AWREADY,
    AXI4_Lite_ACLK,
    AXI4_Lite_WDATA,
    AXI4_Lite_WVALID,
    AXI4_Lite_AWADDR,
    switchNumb,
    AXI4_Lite_ARADDR,
    AXI4_Lite_ARVALID,
    AXI4_Lite_ARESETN,
    AXI4_Lite_RREADY,
    AXI4_Lite_AWVALID,
    IPCORE_RESETN,
    AXI4_Lite_BREADY,
    AXI4_Lite_WSTRB);
  output AXI4_Lite_RVALID;
  output [0:0]SR;
  output write_axi_enable;
  output soft_reset;
  output bResetAXI;
  output [1:0]Q;
  output [25:0]AXI4_Lite_RDATA;
  output AXI4_Lite_ARREADY;
  output AXI4_Lite_AWREADY;
  input AXI4_Lite_ACLK;
  input [0:0]AXI4_Lite_WDATA;
  input AXI4_Lite_WVALID;
  input [13:0]AXI4_Lite_AWADDR;
  input [24:0]switchNumb;
  input [13:0]AXI4_Lite_ARADDR;
  input AXI4_Lite_ARVALID;
  input AXI4_Lite_ARESETN;
  input AXI4_Lite_RREADY;
  input AXI4_Lite_AWVALID;
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
  wire [25:0]AXI4_Lite_RDATA;
  wire AXI4_Lite_RREADY;
  wire AXI4_Lite_RVALID;
  wire [0:0]AXI4_Lite_WDATA;
  wire [3:0]AXI4_Lite_WSTRB;
  wire AXI4_Lite_WVALID;
  wire IPCORE_RESETN;
  wire [1:0]Q;
  wire [0:0]SR;
  wire bResetAXI;
  wire [30:30]read_reg_ip_timestamp;
  wire [24:0]read_reg_switchNumb_AXI;
  wire soft_reset;
  wire [24:0]switchNumb;
  wire u_Counter_f_sw_V2_ip_axi_lite_module_inst_n_4;
  wire u_Counter_f_sw_V2_ip_axi_lite_module_inst_n_5;
  wire write_axi_enable;

  zusys_Counter_f_sw_V2_ip_0_0_Counter_f_sw_V2_ip_addr_decoder u_Counter_f_sw_V2_ip_addr_decoder_inst
       (.AXI4_Lite_ACLK(AXI4_Lite_ACLK),
        .Q(read_reg_switchNumb_AXI),
        .SR(SR),
        .bResetAXI(bResetAXI),
        .read_reg_ip_timestamp(read_reg_ip_timestamp),
        .switchNumb(switchNumb),
        .write_axi_enable(write_axi_enable),
        .write_reg_axi_enable_reg_0(u_Counter_f_sw_V2_ip_axi_lite_module_inst_n_4),
        .write_reg_bResetAXI_reg_0(u_Counter_f_sw_V2_ip_axi_lite_module_inst_n_5));
  zusys_Counter_f_sw_V2_ip_0_0_Counter_f_sw_V2_ip_axi_lite_module u_Counter_f_sw_V2_ip_axi_lite_module_inst
       (.AXI4_Lite_ACLK(AXI4_Lite_ACLK),
        .AXI4_Lite_ARADDR(AXI4_Lite_ARADDR),
        .AXI4_Lite_ARESETN(AXI4_Lite_ARESETN),
        .AXI4_Lite_ARREADY(AXI4_Lite_ARREADY),
        .AXI4_Lite_ARVALID(AXI4_Lite_ARVALID),
        .AXI4_Lite_AWADDR(AXI4_Lite_AWADDR),
        .AXI4_Lite_AWREADY(AXI4_Lite_AWREADY),
        .AXI4_Lite_AWVALID(AXI4_Lite_AWVALID),
        .AXI4_Lite_BREADY(AXI4_Lite_BREADY),
        .AXI4_Lite_RDATA(AXI4_Lite_RDATA),
        .\AXI4_Lite_RDATA_tmp_reg[24]_0 (read_reg_switchNumb_AXI),
        .AXI4_Lite_RREADY(AXI4_Lite_RREADY),
        .AXI4_Lite_WDATA(AXI4_Lite_WDATA),
        .AXI4_Lite_WSTRB(AXI4_Lite_WSTRB),
        .AXI4_Lite_WVALID(AXI4_Lite_WVALID),
        .FSM_sequential_axi_lite_rstate_reg_0(AXI4_Lite_RVALID),
        .IPCORE_RESETN(IPCORE_RESETN),
        .Q(Q),
        .SR(SR),
        .bResetAXI(bResetAXI),
        .read_reg_ip_timestamp(read_reg_ip_timestamp),
        .soft_reset(soft_reset),
        .\wdata_reg[0]_0 (u_Counter_f_sw_V2_ip_axi_lite_module_inst_n_4),
        .\wdata_reg[0]_1 (u_Counter_f_sw_V2_ip_axi_lite_module_inst_n_5),
        .write_axi_enable(write_axi_enable));
endmodule

(* ORIG_REF_NAME = "Counter_f_sw_V2_ip_axi_lite_module" *) 
module zusys_Counter_f_sw_V2_ip_0_0_Counter_f_sw_V2_ip_axi_lite_module
   (FSM_sequential_axi_lite_rstate_reg_0,
    soft_reset,
    Q,
    \wdata_reg[0]_0 ,
    \wdata_reg[0]_1 ,
    AXI4_Lite_RDATA,
    AXI4_Lite_ARREADY,
    AXI4_Lite_AWREADY,
    SR,
    AXI4_Lite_ACLK,
    AXI4_Lite_WDATA,
    AXI4_Lite_WVALID,
    write_axi_enable,
    bResetAXI,
    AXI4_Lite_AWADDR,
    \AXI4_Lite_RDATA_tmp_reg[24]_0 ,
    read_reg_ip_timestamp,
    AXI4_Lite_ARADDR,
    AXI4_Lite_ARVALID,
    AXI4_Lite_ARESETN,
    AXI4_Lite_RREADY,
    AXI4_Lite_AWVALID,
    IPCORE_RESETN,
    AXI4_Lite_BREADY,
    AXI4_Lite_WSTRB);
  output FSM_sequential_axi_lite_rstate_reg_0;
  output soft_reset;
  output [1:0]Q;
  output \wdata_reg[0]_0 ;
  output \wdata_reg[0]_1 ;
  output [25:0]AXI4_Lite_RDATA;
  output AXI4_Lite_ARREADY;
  output AXI4_Lite_AWREADY;
  output [0:0]SR;
  input AXI4_Lite_ACLK;
  input [0:0]AXI4_Lite_WDATA;
  input AXI4_Lite_WVALID;
  input write_axi_enable;
  input bResetAXI;
  input [13:0]AXI4_Lite_AWADDR;
  input [24:0]\AXI4_Lite_RDATA_tmp_reg[24]_0 ;
  input [0:0]read_reg_ip_timestamp;
  input [13:0]AXI4_Lite_ARADDR;
  input AXI4_Lite_ARVALID;
  input AXI4_Lite_ARESETN;
  input AXI4_Lite_RREADY;
  input AXI4_Lite_AWVALID;
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
  wire [25:0]AXI4_Lite_RDATA;
  wire \AXI4_Lite_RDATA_tmp[30]_i_10_n_0 ;
  wire \AXI4_Lite_RDATA_tmp[30]_i_11_n_0 ;
  wire \AXI4_Lite_RDATA_tmp[30]_i_12_n_0 ;
  wire \AXI4_Lite_RDATA_tmp[30]_i_3_n_0 ;
  wire \AXI4_Lite_RDATA_tmp[30]_i_4_n_0 ;
  wire \AXI4_Lite_RDATA_tmp[30]_i_5_n_0 ;
  wire \AXI4_Lite_RDATA_tmp[30]_i_6_n_0 ;
  wire \AXI4_Lite_RDATA_tmp[30]_i_7_n_0 ;
  wire \AXI4_Lite_RDATA_tmp[30]_i_8_n_0 ;
  wire \AXI4_Lite_RDATA_tmp[30]_i_9_n_0 ;
  wire [24:0]\AXI4_Lite_RDATA_tmp_reg[24]_0 ;
  wire AXI4_Lite_RREADY;
  wire [0:0]AXI4_Lite_WDATA;
  wire [3:0]AXI4_Lite_WSTRB;
  wire AXI4_Lite_WVALID;
  wire \FSM_onehot_axi_lite_wstate_reg_n_0_[0] ;
  wire FSM_sequential_axi_lite_rstate_reg_0;
  wire IPCORE_RESETN;
  wire [1:0]Q;
  wire [0:0]SR;
  wire aw_transfer;
  wire axi_lite_rstate_next;
  wire [2:0]axi_lite_wstate_next;
  wire bResetAXI;
  wire [30:0]data_read;
  wire [0:0]read_reg_ip_timestamp;
  wire reset;
  wire [13:0]sel0;
  wire soft_reset;
  wire soft_reset_i_1_n_0;
  wire soft_reset_i_2_n_0;
  wire soft_reset_i_3_n_0;
  wire soft_reset_i_4_n_0;
  wire soft_reset_i_5_n_0;
  wire top_rd_enb;
  wire top_wr_enb;
  wire w_transfer_and_wstrb;
  wire \wdata[0]_i_1_n_0 ;
  wire \wdata_reg[0]_0 ;
  wire \wdata_reg[0]_1 ;
  wire \wdata_reg_n_0_[0] ;
  wire write_axi_enable;
  wire write_reg_axi_enable_i_2_n_0;
  wire write_reg_bResetAXI_i_2_n_0;

  (* SOFT_HLUTNM = "soft_lutpair1" *) 
  LUT3 #(
    .INIT(8'h04)) 
    AXI4_Lite_ARREADY_INST_0
       (.I0(FSM_sequential_axi_lite_rstate_reg_0),
        .I1(\FSM_onehot_axi_lite_wstate_reg_n_0_[0] ),
        .I2(AXI4_Lite_AWVALID),
        .O(AXI4_Lite_ARREADY));
  (* SOFT_HLUTNM = "soft_lutpair2" *) 
  LUT2 #(
    .INIT(4'h2)) 
    AXI4_Lite_AWREADY_INST_0
       (.I0(\FSM_onehot_axi_lite_wstate_reg_n_0_[0] ),
        .I1(FSM_sequential_axi_lite_rstate_reg_0),
        .O(AXI4_Lite_AWREADY));
  LUT6 #(
    .INIT(64'h200C000020000000)) 
    \AXI4_Lite_RDATA_tmp[0]_i_1 
       (.I0(\AXI4_Lite_RDATA_tmp_reg[24]_0 [0]),
        .I1(\AXI4_Lite_RDATA_tmp[30]_i_6_n_0 ),
        .I2(\AXI4_Lite_RDATA_tmp[30]_i_5_n_0 ),
        .I3(\AXI4_Lite_RDATA_tmp[30]_i_4_n_0 ),
        .I4(\AXI4_Lite_RDATA_tmp[30]_i_3_n_0 ),
        .I5(read_reg_ip_timestamp),
        .O(data_read[0]));
  LUT5 #(
    .INIT(32'h00800000)) 
    \AXI4_Lite_RDATA_tmp[10]_i_1 
       (.I0(\AXI4_Lite_RDATA_tmp[30]_i_3_n_0 ),
        .I1(\AXI4_Lite_RDATA_tmp[30]_i_4_n_0 ),
        .I2(\AXI4_Lite_RDATA_tmp[30]_i_5_n_0 ),
        .I3(\AXI4_Lite_RDATA_tmp[30]_i_6_n_0 ),
        .I4(\AXI4_Lite_RDATA_tmp_reg[24]_0 [10]),
        .O(data_read[10]));
  LUT5 #(
    .INIT(32'h00800000)) 
    \AXI4_Lite_RDATA_tmp[11]_i_1 
       (.I0(\AXI4_Lite_RDATA_tmp[30]_i_3_n_0 ),
        .I1(\AXI4_Lite_RDATA_tmp[30]_i_4_n_0 ),
        .I2(\AXI4_Lite_RDATA_tmp[30]_i_5_n_0 ),
        .I3(\AXI4_Lite_RDATA_tmp[30]_i_6_n_0 ),
        .I4(\AXI4_Lite_RDATA_tmp_reg[24]_0 [11]),
        .O(data_read[11]));
  LUT5 #(
    .INIT(32'h00800000)) 
    \AXI4_Lite_RDATA_tmp[12]_i_1 
       (.I0(\AXI4_Lite_RDATA_tmp[30]_i_3_n_0 ),
        .I1(\AXI4_Lite_RDATA_tmp[30]_i_4_n_0 ),
        .I2(\AXI4_Lite_RDATA_tmp[30]_i_5_n_0 ),
        .I3(\AXI4_Lite_RDATA_tmp[30]_i_6_n_0 ),
        .I4(\AXI4_Lite_RDATA_tmp_reg[24]_0 [12]),
        .O(data_read[12]));
  LUT5 #(
    .INIT(32'h00800000)) 
    \AXI4_Lite_RDATA_tmp[13]_i_1 
       (.I0(\AXI4_Lite_RDATA_tmp[30]_i_3_n_0 ),
        .I1(\AXI4_Lite_RDATA_tmp[30]_i_4_n_0 ),
        .I2(\AXI4_Lite_RDATA_tmp[30]_i_5_n_0 ),
        .I3(\AXI4_Lite_RDATA_tmp[30]_i_6_n_0 ),
        .I4(\AXI4_Lite_RDATA_tmp_reg[24]_0 [13]),
        .O(data_read[13]));
  LUT6 #(
    .INIT(64'h200C000020000000)) 
    \AXI4_Lite_RDATA_tmp[14]_i_1 
       (.I0(\AXI4_Lite_RDATA_tmp_reg[24]_0 [14]),
        .I1(\AXI4_Lite_RDATA_tmp[30]_i_6_n_0 ),
        .I2(\AXI4_Lite_RDATA_tmp[30]_i_5_n_0 ),
        .I3(\AXI4_Lite_RDATA_tmp[30]_i_4_n_0 ),
        .I4(\AXI4_Lite_RDATA_tmp[30]_i_3_n_0 ),
        .I5(read_reg_ip_timestamp),
        .O(data_read[14]));
  LUT6 #(
    .INIT(64'h200C000020000000)) 
    \AXI4_Lite_RDATA_tmp[15]_i_1 
       (.I0(\AXI4_Lite_RDATA_tmp_reg[24]_0 [15]),
        .I1(\AXI4_Lite_RDATA_tmp[30]_i_6_n_0 ),
        .I2(\AXI4_Lite_RDATA_tmp[30]_i_5_n_0 ),
        .I3(\AXI4_Lite_RDATA_tmp[30]_i_4_n_0 ),
        .I4(\AXI4_Lite_RDATA_tmp[30]_i_3_n_0 ),
        .I5(read_reg_ip_timestamp),
        .O(data_read[15]));
  LUT5 #(
    .INIT(32'h00800000)) 
    \AXI4_Lite_RDATA_tmp[16]_i_1 
       (.I0(\AXI4_Lite_RDATA_tmp[30]_i_3_n_0 ),
        .I1(\AXI4_Lite_RDATA_tmp[30]_i_4_n_0 ),
        .I2(\AXI4_Lite_RDATA_tmp[30]_i_5_n_0 ),
        .I3(\AXI4_Lite_RDATA_tmp[30]_i_6_n_0 ),
        .I4(\AXI4_Lite_RDATA_tmp_reg[24]_0 [16]),
        .O(data_read[16]));
  LUT6 #(
    .INIT(64'h200C000020000000)) 
    \AXI4_Lite_RDATA_tmp[17]_i_1 
       (.I0(\AXI4_Lite_RDATA_tmp_reg[24]_0 [17]),
        .I1(\AXI4_Lite_RDATA_tmp[30]_i_6_n_0 ),
        .I2(\AXI4_Lite_RDATA_tmp[30]_i_5_n_0 ),
        .I3(\AXI4_Lite_RDATA_tmp[30]_i_4_n_0 ),
        .I4(\AXI4_Lite_RDATA_tmp[30]_i_3_n_0 ),
        .I5(read_reg_ip_timestamp),
        .O(data_read[17]));
  LUT6 #(
    .INIT(64'h200C000020000000)) 
    \AXI4_Lite_RDATA_tmp[18]_i_1 
       (.I0(\AXI4_Lite_RDATA_tmp_reg[24]_0 [18]),
        .I1(\AXI4_Lite_RDATA_tmp[30]_i_6_n_0 ),
        .I2(\AXI4_Lite_RDATA_tmp[30]_i_5_n_0 ),
        .I3(\AXI4_Lite_RDATA_tmp[30]_i_4_n_0 ),
        .I4(\AXI4_Lite_RDATA_tmp[30]_i_3_n_0 ),
        .I5(read_reg_ip_timestamp),
        .O(data_read[18]));
  LUT5 #(
    .INIT(32'h00800000)) 
    \AXI4_Lite_RDATA_tmp[19]_i_1 
       (.I0(\AXI4_Lite_RDATA_tmp[30]_i_3_n_0 ),
        .I1(\AXI4_Lite_RDATA_tmp[30]_i_4_n_0 ),
        .I2(\AXI4_Lite_RDATA_tmp[30]_i_5_n_0 ),
        .I3(\AXI4_Lite_RDATA_tmp[30]_i_6_n_0 ),
        .I4(\AXI4_Lite_RDATA_tmp_reg[24]_0 [19]),
        .O(data_read[19]));
  LUT6 #(
    .INIT(64'h200C000020000000)) 
    \AXI4_Lite_RDATA_tmp[1]_i_1 
       (.I0(\AXI4_Lite_RDATA_tmp_reg[24]_0 [1]),
        .I1(\AXI4_Lite_RDATA_tmp[30]_i_6_n_0 ),
        .I2(\AXI4_Lite_RDATA_tmp[30]_i_5_n_0 ),
        .I3(\AXI4_Lite_RDATA_tmp[30]_i_4_n_0 ),
        .I4(\AXI4_Lite_RDATA_tmp[30]_i_3_n_0 ),
        .I5(read_reg_ip_timestamp),
        .O(data_read[1]));
  LUT6 #(
    .INIT(64'h200C000020000000)) 
    \AXI4_Lite_RDATA_tmp[20]_i_1 
       (.I0(\AXI4_Lite_RDATA_tmp_reg[24]_0 [20]),
        .I1(\AXI4_Lite_RDATA_tmp[30]_i_6_n_0 ),
        .I2(\AXI4_Lite_RDATA_tmp[30]_i_5_n_0 ),
        .I3(\AXI4_Lite_RDATA_tmp[30]_i_4_n_0 ),
        .I4(\AXI4_Lite_RDATA_tmp[30]_i_3_n_0 ),
        .I5(read_reg_ip_timestamp),
        .O(data_read[20]));
  LUT6 #(
    .INIT(64'h200C000020000000)) 
    \AXI4_Lite_RDATA_tmp[21]_i_1 
       (.I0(\AXI4_Lite_RDATA_tmp_reg[24]_0 [21]),
        .I1(\AXI4_Lite_RDATA_tmp[30]_i_6_n_0 ),
        .I2(\AXI4_Lite_RDATA_tmp[30]_i_5_n_0 ),
        .I3(\AXI4_Lite_RDATA_tmp[30]_i_4_n_0 ),
        .I4(\AXI4_Lite_RDATA_tmp[30]_i_3_n_0 ),
        .I5(read_reg_ip_timestamp),
        .O(data_read[21]));
  LUT6 #(
    .INIT(64'h200C000020000000)) 
    \AXI4_Lite_RDATA_tmp[22]_i_1 
       (.I0(\AXI4_Lite_RDATA_tmp_reg[24]_0 [22]),
        .I1(\AXI4_Lite_RDATA_tmp[30]_i_6_n_0 ),
        .I2(\AXI4_Lite_RDATA_tmp[30]_i_5_n_0 ),
        .I3(\AXI4_Lite_RDATA_tmp[30]_i_4_n_0 ),
        .I4(\AXI4_Lite_RDATA_tmp[30]_i_3_n_0 ),
        .I5(read_reg_ip_timestamp),
        .O(data_read[22]));
  LUT5 #(
    .INIT(32'h00800000)) 
    \AXI4_Lite_RDATA_tmp[23]_i_1 
       (.I0(\AXI4_Lite_RDATA_tmp[30]_i_3_n_0 ),
        .I1(\AXI4_Lite_RDATA_tmp[30]_i_4_n_0 ),
        .I2(\AXI4_Lite_RDATA_tmp[30]_i_5_n_0 ),
        .I3(\AXI4_Lite_RDATA_tmp[30]_i_6_n_0 ),
        .I4(\AXI4_Lite_RDATA_tmp_reg[24]_0 [23]),
        .O(data_read[23]));
  LUT6 #(
    .INIT(64'h200C000020000000)) 
    \AXI4_Lite_RDATA_tmp[24]_i_1 
       (.I0(\AXI4_Lite_RDATA_tmp_reg[24]_0 [24]),
        .I1(\AXI4_Lite_RDATA_tmp[30]_i_6_n_0 ),
        .I2(\AXI4_Lite_RDATA_tmp[30]_i_5_n_0 ),
        .I3(\AXI4_Lite_RDATA_tmp[30]_i_4_n_0 ),
        .I4(\AXI4_Lite_RDATA_tmp[30]_i_3_n_0 ),
        .I5(read_reg_ip_timestamp),
        .O(data_read[24]));
  LUT5 #(
    .INIT(32'h00800000)) 
    \AXI4_Lite_RDATA_tmp[2]_i_1 
       (.I0(\AXI4_Lite_RDATA_tmp[30]_i_3_n_0 ),
        .I1(\AXI4_Lite_RDATA_tmp[30]_i_4_n_0 ),
        .I2(\AXI4_Lite_RDATA_tmp[30]_i_5_n_0 ),
        .I3(\AXI4_Lite_RDATA_tmp[30]_i_6_n_0 ),
        .I4(\AXI4_Lite_RDATA_tmp_reg[24]_0 [2]),
        .O(data_read[2]));
  LUT4 #(
    .INIT(16'h0400)) 
    \AXI4_Lite_RDATA_tmp[30]_i_1 
       (.I0(AXI4_Lite_AWVALID),
        .I1(AXI4_Lite_ARVALID),
        .I2(FSM_sequential_axi_lite_rstate_reg_0),
        .I3(\FSM_onehot_axi_lite_wstate_reg_n_0_[0] ),
        .O(top_rd_enb));
  (* SOFT_HLUTNM = "soft_lutpair3" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \AXI4_Lite_RDATA_tmp[30]_i_10 
       (.I0(AXI4_Lite_ARADDR[13]),
        .I1(AXI4_Lite_ARVALID),
        .I2(sel0[13]),
        .O(\AXI4_Lite_RDATA_tmp[30]_i_10_n_0 ));
  LUT5 #(
    .INIT(32'hEEFFEEF0)) 
    \AXI4_Lite_RDATA_tmp[30]_i_11 
       (.I0(AXI4_Lite_ARADDR[9]),
        .I1(AXI4_Lite_ARADDR[8]),
        .I2(sel0[9]),
        .I3(AXI4_Lite_ARVALID),
        .I4(sel0[8]),
        .O(\AXI4_Lite_RDATA_tmp[30]_i_11_n_0 ));
  LUT5 #(
    .INIT(32'h00053305)) 
    \AXI4_Lite_RDATA_tmp[30]_i_12 
       (.I0(sel0[11]),
        .I1(AXI4_Lite_ARADDR[11]),
        .I2(sel0[10]),
        .I3(AXI4_Lite_ARVALID),
        .I4(AXI4_Lite_ARADDR[10]),
        .O(\AXI4_Lite_RDATA_tmp[30]_i_12_n_0 ));
  LUT5 #(
    .INIT(32'h00080000)) 
    \AXI4_Lite_RDATA_tmp[30]_i_2 
       (.I0(read_reg_ip_timestamp),
        .I1(\AXI4_Lite_RDATA_tmp[30]_i_3_n_0 ),
        .I2(\AXI4_Lite_RDATA_tmp[30]_i_4_n_0 ),
        .I3(\AXI4_Lite_RDATA_tmp[30]_i_5_n_0 ),
        .I4(\AXI4_Lite_RDATA_tmp[30]_i_6_n_0 ),
        .O(data_read[30]));
  LUT6 #(
    .INIT(64'h0000001000000000)) 
    \AXI4_Lite_RDATA_tmp[30]_i_3 
       (.I0(\AXI4_Lite_RDATA_tmp[30]_i_7_n_0 ),
        .I1(\AXI4_Lite_RDATA_tmp[30]_i_8_n_0 ),
        .I2(\AXI4_Lite_RDATA_tmp[30]_i_9_n_0 ),
        .I3(\AXI4_Lite_RDATA_tmp[30]_i_10_n_0 ),
        .I4(\AXI4_Lite_RDATA_tmp[30]_i_11_n_0 ),
        .I5(\AXI4_Lite_RDATA_tmp[30]_i_12_n_0 ),
        .O(\AXI4_Lite_RDATA_tmp[30]_i_3_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair3" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \AXI4_Lite_RDATA_tmp[30]_i_4 
       (.I0(AXI4_Lite_ARADDR[6]),
        .I1(AXI4_Lite_ARVALID),
        .I2(sel0[6]),
        .O(\AXI4_Lite_RDATA_tmp[30]_i_4_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair4" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \AXI4_Lite_RDATA_tmp[30]_i_5 
       (.I0(AXI4_Lite_ARADDR[0]),
        .I1(AXI4_Lite_ARVALID),
        .I2(sel0[0]),
        .O(\AXI4_Lite_RDATA_tmp[30]_i_5_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair4" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \AXI4_Lite_RDATA_tmp[30]_i_6 
       (.I0(AXI4_Lite_ARADDR[1]),
        .I1(AXI4_Lite_ARVALID),
        .I2(sel0[1]),
        .O(\AXI4_Lite_RDATA_tmp[30]_i_6_n_0 ));
  LUT5 #(
    .INIT(32'hEEFFEEF0)) 
    \AXI4_Lite_RDATA_tmp[30]_i_7 
       (.I0(AXI4_Lite_ARADDR[3]),
        .I1(AXI4_Lite_ARADDR[2]),
        .I2(sel0[3]),
        .I3(AXI4_Lite_ARVALID),
        .I4(sel0[2]),
        .O(\AXI4_Lite_RDATA_tmp[30]_i_7_n_0 ));
  LUT5 #(
    .INIT(32'hFFEEF0EE)) 
    \AXI4_Lite_RDATA_tmp[30]_i_8 
       (.I0(sel0[5]),
        .I1(sel0[4]),
        .I2(AXI4_Lite_ARADDR[5]),
        .I3(AXI4_Lite_ARVALID),
        .I4(AXI4_Lite_ARADDR[4]),
        .O(\AXI4_Lite_RDATA_tmp[30]_i_8_n_0 ));
  LUT5 #(
    .INIT(32'h00053305)) 
    \AXI4_Lite_RDATA_tmp[30]_i_9 
       (.I0(sel0[7]),
        .I1(AXI4_Lite_ARADDR[7]),
        .I2(sel0[12]),
        .I3(AXI4_Lite_ARVALID),
        .I4(AXI4_Lite_ARADDR[12]),
        .O(\AXI4_Lite_RDATA_tmp[30]_i_9_n_0 ));
  LUT6 #(
    .INIT(64'h200C000020000000)) 
    \AXI4_Lite_RDATA_tmp[3]_i_1 
       (.I0(\AXI4_Lite_RDATA_tmp_reg[24]_0 [3]),
        .I1(\AXI4_Lite_RDATA_tmp[30]_i_6_n_0 ),
        .I2(\AXI4_Lite_RDATA_tmp[30]_i_5_n_0 ),
        .I3(\AXI4_Lite_RDATA_tmp[30]_i_4_n_0 ),
        .I4(\AXI4_Lite_RDATA_tmp[30]_i_3_n_0 ),
        .I5(read_reg_ip_timestamp),
        .O(data_read[3]));
  LUT5 #(
    .INIT(32'h00800000)) 
    \AXI4_Lite_RDATA_tmp[4]_i_1 
       (.I0(\AXI4_Lite_RDATA_tmp[30]_i_3_n_0 ),
        .I1(\AXI4_Lite_RDATA_tmp[30]_i_4_n_0 ),
        .I2(\AXI4_Lite_RDATA_tmp[30]_i_5_n_0 ),
        .I3(\AXI4_Lite_RDATA_tmp[30]_i_6_n_0 ),
        .I4(\AXI4_Lite_RDATA_tmp_reg[24]_0 [4]),
        .O(data_read[4]));
  LUT6 #(
    .INIT(64'h200C000020000000)) 
    \AXI4_Lite_RDATA_tmp[5]_i_1 
       (.I0(\AXI4_Lite_RDATA_tmp_reg[24]_0 [5]),
        .I1(\AXI4_Lite_RDATA_tmp[30]_i_6_n_0 ),
        .I2(\AXI4_Lite_RDATA_tmp[30]_i_5_n_0 ),
        .I3(\AXI4_Lite_RDATA_tmp[30]_i_4_n_0 ),
        .I4(\AXI4_Lite_RDATA_tmp[30]_i_3_n_0 ),
        .I5(read_reg_ip_timestamp),
        .O(data_read[5]));
  LUT5 #(
    .INIT(32'h00800000)) 
    \AXI4_Lite_RDATA_tmp[6]_i_1 
       (.I0(\AXI4_Lite_RDATA_tmp[30]_i_3_n_0 ),
        .I1(\AXI4_Lite_RDATA_tmp[30]_i_4_n_0 ),
        .I2(\AXI4_Lite_RDATA_tmp[30]_i_5_n_0 ),
        .I3(\AXI4_Lite_RDATA_tmp[30]_i_6_n_0 ),
        .I4(\AXI4_Lite_RDATA_tmp_reg[24]_0 [6]),
        .O(data_read[6]));
  LUT5 #(
    .INIT(32'h00800000)) 
    \AXI4_Lite_RDATA_tmp[7]_i_1 
       (.I0(\AXI4_Lite_RDATA_tmp[30]_i_3_n_0 ),
        .I1(\AXI4_Lite_RDATA_tmp[30]_i_4_n_0 ),
        .I2(\AXI4_Lite_RDATA_tmp[30]_i_5_n_0 ),
        .I3(\AXI4_Lite_RDATA_tmp[30]_i_6_n_0 ),
        .I4(\AXI4_Lite_RDATA_tmp_reg[24]_0 [7]),
        .O(data_read[7]));
  LUT6 #(
    .INIT(64'h200C000020000000)) 
    \AXI4_Lite_RDATA_tmp[8]_i_1 
       (.I0(\AXI4_Lite_RDATA_tmp_reg[24]_0 [8]),
        .I1(\AXI4_Lite_RDATA_tmp[30]_i_6_n_0 ),
        .I2(\AXI4_Lite_RDATA_tmp[30]_i_5_n_0 ),
        .I3(\AXI4_Lite_RDATA_tmp[30]_i_4_n_0 ),
        .I4(\AXI4_Lite_RDATA_tmp[30]_i_3_n_0 ),
        .I5(read_reg_ip_timestamp),
        .O(data_read[8]));
  LUT6 #(
    .INIT(64'h200C000020000000)) 
    \AXI4_Lite_RDATA_tmp[9]_i_1 
       (.I0(\AXI4_Lite_RDATA_tmp_reg[24]_0 [9]),
        .I1(\AXI4_Lite_RDATA_tmp[30]_i_6_n_0 ),
        .I2(\AXI4_Lite_RDATA_tmp[30]_i_5_n_0 ),
        .I3(\AXI4_Lite_RDATA_tmp[30]_i_4_n_0 ),
        .I4(\AXI4_Lite_RDATA_tmp[30]_i_3_n_0 ),
        .I5(read_reg_ip_timestamp),
        .O(data_read[9]));
  FDRE \AXI4_Lite_RDATA_tmp_reg[0] 
       (.C(AXI4_Lite_ACLK),
        .CE(top_rd_enb),
        .D(data_read[0]),
        .Q(AXI4_Lite_RDATA[0]),
        .R(reset));
  FDRE \AXI4_Lite_RDATA_tmp_reg[10] 
       (.C(AXI4_Lite_ACLK),
        .CE(top_rd_enb),
        .D(data_read[10]),
        .Q(AXI4_Lite_RDATA[10]),
        .R(reset));
  FDRE \AXI4_Lite_RDATA_tmp_reg[11] 
       (.C(AXI4_Lite_ACLK),
        .CE(top_rd_enb),
        .D(data_read[11]),
        .Q(AXI4_Lite_RDATA[11]),
        .R(reset));
  FDRE \AXI4_Lite_RDATA_tmp_reg[12] 
       (.C(AXI4_Lite_ACLK),
        .CE(top_rd_enb),
        .D(data_read[12]),
        .Q(AXI4_Lite_RDATA[12]),
        .R(reset));
  FDRE \AXI4_Lite_RDATA_tmp_reg[13] 
       (.C(AXI4_Lite_ACLK),
        .CE(top_rd_enb),
        .D(data_read[13]),
        .Q(AXI4_Lite_RDATA[13]),
        .R(reset));
  FDRE \AXI4_Lite_RDATA_tmp_reg[14] 
       (.C(AXI4_Lite_ACLK),
        .CE(top_rd_enb),
        .D(data_read[14]),
        .Q(AXI4_Lite_RDATA[14]),
        .R(reset));
  FDRE \AXI4_Lite_RDATA_tmp_reg[15] 
       (.C(AXI4_Lite_ACLK),
        .CE(top_rd_enb),
        .D(data_read[15]),
        .Q(AXI4_Lite_RDATA[15]),
        .R(reset));
  FDRE \AXI4_Lite_RDATA_tmp_reg[16] 
       (.C(AXI4_Lite_ACLK),
        .CE(top_rd_enb),
        .D(data_read[16]),
        .Q(AXI4_Lite_RDATA[16]),
        .R(reset));
  FDRE \AXI4_Lite_RDATA_tmp_reg[17] 
       (.C(AXI4_Lite_ACLK),
        .CE(top_rd_enb),
        .D(data_read[17]),
        .Q(AXI4_Lite_RDATA[17]),
        .R(reset));
  FDRE \AXI4_Lite_RDATA_tmp_reg[18] 
       (.C(AXI4_Lite_ACLK),
        .CE(top_rd_enb),
        .D(data_read[18]),
        .Q(AXI4_Lite_RDATA[18]),
        .R(reset));
  FDRE \AXI4_Lite_RDATA_tmp_reg[19] 
       (.C(AXI4_Lite_ACLK),
        .CE(top_rd_enb),
        .D(data_read[19]),
        .Q(AXI4_Lite_RDATA[19]),
        .R(reset));
  FDRE \AXI4_Lite_RDATA_tmp_reg[1] 
       (.C(AXI4_Lite_ACLK),
        .CE(top_rd_enb),
        .D(data_read[1]),
        .Q(AXI4_Lite_RDATA[1]),
        .R(reset));
  FDRE \AXI4_Lite_RDATA_tmp_reg[20] 
       (.C(AXI4_Lite_ACLK),
        .CE(top_rd_enb),
        .D(data_read[20]),
        .Q(AXI4_Lite_RDATA[20]),
        .R(reset));
  FDRE \AXI4_Lite_RDATA_tmp_reg[21] 
       (.C(AXI4_Lite_ACLK),
        .CE(top_rd_enb),
        .D(data_read[21]),
        .Q(AXI4_Lite_RDATA[21]),
        .R(reset));
  FDRE \AXI4_Lite_RDATA_tmp_reg[22] 
       (.C(AXI4_Lite_ACLK),
        .CE(top_rd_enb),
        .D(data_read[22]),
        .Q(AXI4_Lite_RDATA[22]),
        .R(reset));
  FDRE \AXI4_Lite_RDATA_tmp_reg[23] 
       (.C(AXI4_Lite_ACLK),
        .CE(top_rd_enb),
        .D(data_read[23]),
        .Q(AXI4_Lite_RDATA[23]),
        .R(reset));
  FDRE \AXI4_Lite_RDATA_tmp_reg[24] 
       (.C(AXI4_Lite_ACLK),
        .CE(top_rd_enb),
        .D(data_read[24]),
        .Q(AXI4_Lite_RDATA[24]),
        .R(reset));
  FDRE \AXI4_Lite_RDATA_tmp_reg[2] 
       (.C(AXI4_Lite_ACLK),
        .CE(top_rd_enb),
        .D(data_read[2]),
        .Q(AXI4_Lite_RDATA[2]),
        .R(reset));
  FDRE \AXI4_Lite_RDATA_tmp_reg[30] 
       (.C(AXI4_Lite_ACLK),
        .CE(top_rd_enb),
        .D(data_read[30]),
        .Q(AXI4_Lite_RDATA[25]),
        .R(reset));
  FDRE \AXI4_Lite_RDATA_tmp_reg[3] 
       (.C(AXI4_Lite_ACLK),
        .CE(top_rd_enb),
        .D(data_read[3]),
        .Q(AXI4_Lite_RDATA[3]),
        .R(reset));
  FDRE \AXI4_Lite_RDATA_tmp_reg[4] 
       (.C(AXI4_Lite_ACLK),
        .CE(top_rd_enb),
        .D(data_read[4]),
        .Q(AXI4_Lite_RDATA[4]),
        .R(reset));
  FDRE \AXI4_Lite_RDATA_tmp_reg[5] 
       (.C(AXI4_Lite_ACLK),
        .CE(top_rd_enb),
        .D(data_read[5]),
        .Q(AXI4_Lite_RDATA[5]),
        .R(reset));
  FDRE \AXI4_Lite_RDATA_tmp_reg[6] 
       (.C(AXI4_Lite_ACLK),
        .CE(top_rd_enb),
        .D(data_read[6]),
        .Q(AXI4_Lite_RDATA[6]),
        .R(reset));
  FDRE \AXI4_Lite_RDATA_tmp_reg[7] 
       (.C(AXI4_Lite_ACLK),
        .CE(top_rd_enb),
        .D(data_read[7]),
        .Q(AXI4_Lite_RDATA[7]),
        .R(reset));
  FDRE \AXI4_Lite_RDATA_tmp_reg[8] 
       (.C(AXI4_Lite_ACLK),
        .CE(top_rd_enb),
        .D(data_read[8]),
        .Q(AXI4_Lite_RDATA[8]),
        .R(reset));
  FDRE \AXI4_Lite_RDATA_tmp_reg[9] 
       (.C(AXI4_Lite_ACLK),
        .CE(top_rd_enb),
        .D(data_read[9]),
        .Q(AXI4_Lite_RDATA[9]),
        .R(reset));
  LUT5 #(
    .INIT(32'hFF8A8A8A)) 
    \FSM_onehot_axi_lite_wstate[0]_i_1 
       (.I0(\FSM_onehot_axi_lite_wstate_reg_n_0_[0] ),
        .I1(FSM_sequential_axi_lite_rstate_reg_0),
        .I2(AXI4_Lite_AWVALID),
        .I3(AXI4_Lite_BREADY),
        .I4(Q[1]),
        .O(axi_lite_wstate_next[0]));
  LUT1 #(
    .INIT(2'h1)) 
    \FSM_onehot_axi_lite_wstate[1]_i_1 
       (.I0(AXI4_Lite_ARESETN),
        .O(reset));
  (* SOFT_HLUTNM = "soft_lutpair2" *) 
  LUT5 #(
    .INIT(32'h08FF0808)) 
    \FSM_onehot_axi_lite_wstate[1]_i_2 
       (.I0(AXI4_Lite_AWVALID),
        .I1(\FSM_onehot_axi_lite_wstate_reg_n_0_[0] ),
        .I2(FSM_sequential_axi_lite_rstate_reg_0),
        .I3(AXI4_Lite_WVALID),
        .I4(Q[0]),
        .O(axi_lite_wstate_next[1]));
  LUT4 #(
    .INIT(16'hF444)) 
    \FSM_onehot_axi_lite_wstate[2]_i_1 
       (.I0(AXI4_Lite_BREADY),
        .I1(Q[1]),
        .I2(AXI4_Lite_WVALID),
        .I3(Q[0]),
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
  (* SOFT_HLUTNM = "soft_lutpair1" *) 
  LUT5 #(
    .INIT(32'h50505C50)) 
    FSM_sequential_axi_lite_rstate_i_1
       (.I0(AXI4_Lite_RREADY),
        .I1(\FSM_onehot_axi_lite_wstate_reg_n_0_[0] ),
        .I2(FSM_sequential_axi_lite_rstate_reg_0),
        .I3(AXI4_Lite_ARVALID),
        .I4(AXI4_Lite_AWVALID),
        .O(axi_lite_rstate_next));
  (* FSM_ENCODED_STATES = "iSTATE:0,iSTATE0:1" *) 
  FDRE FSM_sequential_axi_lite_rstate_reg
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(axi_lite_rstate_next),
        .Q(FSM_sequential_axi_lite_rstate_reg_0),
        .R(reset));
  LUT5 #(
    .INIT(32'h0A020000)) 
    soft_reset_i_1
       (.I0(soft_reset_i_2_n_0),
        .I1(sel0[9]),
        .I2(sel0[11]),
        .I3(sel0[10]),
        .I4(soft_reset_i_3_n_0),
        .O(soft_reset_i_1_n_0));
  LUT6 #(
    .INIT(64'h0000000000000008)) 
    soft_reset_i_2
       (.I0(soft_reset_i_4_n_0),
        .I1(soft_reset_i_5_n_0),
        .I2(sel0[1]),
        .I3(sel0[0]),
        .I4(sel0[7]),
        .I5(sel0[2]),
        .O(soft_reset_i_2_n_0));
  LUT6 #(
    .INIT(64'h0000230000002323)) 
    soft_reset_i_3
       (.I0(sel0[7]),
        .I1(sel0[8]),
        .I2(sel0[6]),
        .I3(sel0[4]),
        .I4(sel0[5]),
        .I5(sel0[3]),
        .O(soft_reset_i_3_n_0));
  LUT6 #(
    .INIT(64'h0000000000002000)) 
    soft_reset_i_4
       (.I0(\wdata_reg_n_0_[0] ),
        .I1(sel0[13]),
        .I2(AXI4_Lite_ARESETN),
        .I3(top_wr_enb),
        .I4(sel0[5]),
        .I5(sel0[4]),
        .O(soft_reset_i_4_n_0));
  LUT4 #(
    .INIT(16'h0001)) 
    soft_reset_i_5
       (.I0(sel0[12]),
        .I1(sel0[11]),
        .I2(sel0[10]),
        .I3(sel0[8]),
        .O(soft_reset_i_5_n_0));
  FDRE soft_reset_reg
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(soft_reset_i_1_n_0),
        .Q(soft_reset),
        .R(1'b0));
  LUT3 #(
    .INIT(8'hDF)) 
    ss_in_5_1_i_1
       (.I0(AXI4_Lite_ARESETN),
        .I1(soft_reset),
        .I2(IPCORE_RESETN),
        .O(SR));
  LUT3 #(
    .INIT(8'h40)) 
    \waddr[15]_i_1 
       (.I0(FSM_sequential_axi_lite_rstate_reg_0),
        .I1(\FSM_onehot_axi_lite_wstate_reg_n_0_[0] ),
        .I2(AXI4_Lite_AWVALID),
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
  LUT4 #(
    .INIT(16'hBF80)) 
    \wdata[0]_i_1 
       (.I0(AXI4_Lite_WDATA),
        .I1(Q[0]),
        .I2(AXI4_Lite_WVALID),
        .I3(\wdata_reg_n_0_[0] ),
        .O(\wdata[0]_i_1_n_0 ));
  FDRE \wdata_reg[0] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(\wdata[0]_i_1_n_0 ),
        .Q(\wdata_reg_n_0_[0] ),
        .R(reset));
  LUT6 #(
    .INIT(64'h8000000000000000)) 
    wr_enb_1_i_1
       (.I0(AXI4_Lite_WSTRB[2]),
        .I1(AXI4_Lite_WSTRB[3]),
        .I2(AXI4_Lite_WSTRB[0]),
        .I3(AXI4_Lite_WSTRB[1]),
        .I4(Q[0]),
        .I5(AXI4_Lite_WVALID),
        .O(w_transfer_and_wstrb));
  FDRE wr_enb_1_reg
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(w_transfer_and_wstrb),
        .Q(top_wr_enb),
        .R(reset));
  LUT6 #(
    .INIT(64'hFBFFFFFF08000000)) 
    write_reg_axi_enable_i_1
       (.I0(\wdata_reg_n_0_[0] ),
        .I1(top_wr_enb),
        .I2(\AXI4_Lite_RDATA_tmp[30]_i_4_n_0 ),
        .I3(write_reg_axi_enable_i_2_n_0),
        .I4(\AXI4_Lite_RDATA_tmp[30]_i_3_n_0 ),
        .I5(write_axi_enable),
        .O(\wdata_reg[0]_0 ));
  (* SOFT_HLUTNM = "soft_lutpair0" *) 
  LUT5 #(
    .INIT(32'h000ACC0A)) 
    write_reg_axi_enable_i_2
       (.I0(sel0[0]),
        .I1(AXI4_Lite_ARADDR[0]),
        .I2(sel0[1]),
        .I3(AXI4_Lite_ARVALID),
        .I4(AXI4_Lite_ARADDR[1]),
        .O(write_reg_axi_enable_i_2_n_0));
  LUT6 #(
    .INIT(64'hBFFFFFFF80000000)) 
    write_reg_bResetAXI_i_1
       (.I0(\wdata_reg_n_0_[0] ),
        .I1(\AXI4_Lite_RDATA_tmp[30]_i_4_n_0 ),
        .I2(top_wr_enb),
        .I3(write_reg_bResetAXI_i_2_n_0),
        .I4(\AXI4_Lite_RDATA_tmp[30]_i_3_n_0 ),
        .I5(bResetAXI),
        .O(\wdata_reg[0]_1 ));
  (* SOFT_HLUTNM = "soft_lutpair0" *) 
  LUT5 #(
    .INIT(32'h00053305)) 
    write_reg_bResetAXI_i_2
       (.I0(sel0[1]),
        .I1(AXI4_Lite_ARADDR[1]),
        .I2(sel0[0]),
        .I3(AXI4_Lite_ARVALID),
        .I4(AXI4_Lite_ARADDR[0]),
        .O(write_reg_bResetAXI_i_2_n_0));
endmodule

(* ORIG_REF_NAME = "Counter_f_sw_V2_ip_dut" *) 
module zusys_Counter_f_sw_V2_ip_0_0_Counter_f_sw_V2_ip_dut
   (switchNumb,
    SR,
    E,
    ss_in_5,
    IPCORE_CLK,
    ss_in_4,
    ss_in_3,
    ss_in_2,
    ss_in_1,
    ss_in_0,
    bResetAXI,
    IPCORE_RESETN,
    soft_reset,
    AXI4_Lite_ARESETN);
  output [24:0]switchNumb;
  input [0:0]SR;
  input [0:0]E;
  input ss_in_5;
  input IPCORE_CLK;
  input ss_in_4;
  input ss_in_3;
  input ss_in_2;
  input ss_in_1;
  input ss_in_0;
  input bResetAXI;
  input IPCORE_RESETN;
  input soft_reset;
  input AXI4_Lite_ARESETN;

  wire AXI4_Lite_ARESETN;
  wire [0:0]E;
  wire IPCORE_CLK;
  wire IPCORE_RESETN;
  wire [0:0]SR;
  wire bResetAXI;
  wire soft_reset;
  wire ss_in_0;
  wire ss_in_1;
  wire ss_in_2;
  wire ss_in_3;
  wire ss_in_4;
  wire ss_in_5;
  wire [24:0]switchNumb;

  zusys_Counter_f_sw_V2_ip_0_0_Counter_f_sw_V2_ip_src_Counter_f_sw_V2 u_Counter_f_sw_V2_ip_src_Counter_f_sw_V2
       (.AXI4_Lite_ARESETN(AXI4_Lite_ARESETN),
        .E(E),
        .IPCORE_CLK(IPCORE_CLK),
        .IPCORE_RESETN(IPCORE_RESETN),
        .SR(SR),
        .bResetAXI(bResetAXI),
        .soft_reset(soft_reset),
        .ss_in_0(ss_in_0),
        .ss_in_1(ss_in_1),
        .ss_in_2(ss_in_2),
        .ss_in_3(ss_in_3),
        .ss_in_4(ss_in_4),
        .ss_in_5(ss_in_5),
        .switchNumb(switchNumb));
endmodule

(* ORIG_REF_NAME = "Counter_f_sw_V2_ip_src_Count_f_sw" *) 
module zusys_Counter_f_sw_V2_ip_0_0_Counter_f_sw_V2_ip_src_Count_f_sw
   (switchNumb,
    S,
    reset_old2_out1,
    bResetAXI_1,
    Q,
    D,
    switchNumb10__0_carry__1_0);
  output [24:0]switchNumb;
  input [0:0]S;
  input reset_old2_out1;
  input bResetAXI_1;
  input [5:0]Q;
  input [5:0]D;
  input [23:0]switchNumb10__0_carry__1_0;

  wire [5:0]D;
  wire [5:0]Q;
  wire [0:0]S;
  wire bResetAXI_1;
  wire reset_old2_out1;
  wire [24:0]switchNumb;
  wire [23:2]switchNumb1;
  wire switchNumb10__0_carry__0_n_0;
  wire switchNumb10__0_carry__0_n_1;
  wire switchNumb10__0_carry__0_n_10;
  wire switchNumb10__0_carry__0_n_11;
  wire switchNumb10__0_carry__0_n_12;
  wire switchNumb10__0_carry__0_n_13;
  wire switchNumb10__0_carry__0_n_14;
  wire switchNumb10__0_carry__0_n_15;
  wire switchNumb10__0_carry__0_n_2;
  wire switchNumb10__0_carry__0_n_3;
  wire switchNumb10__0_carry__0_n_4;
  wire switchNumb10__0_carry__0_n_5;
  wire switchNumb10__0_carry__0_n_6;
  wire switchNumb10__0_carry__0_n_7;
  wire switchNumb10__0_carry__0_n_8;
  wire switchNumb10__0_carry__0_n_9;
  wire [23:0]switchNumb10__0_carry__1_0;
  wire switchNumb10__0_carry__1_n_0;
  wire switchNumb10__0_carry__1_n_1;
  wire switchNumb10__0_carry__1_n_10;
  wire switchNumb10__0_carry__1_n_11;
  wire switchNumb10__0_carry__1_n_12;
  wire switchNumb10__0_carry__1_n_13;
  wire switchNumb10__0_carry__1_n_14;
  wire switchNumb10__0_carry__1_n_15;
  wire switchNumb10__0_carry__1_n_2;
  wire switchNumb10__0_carry__1_n_3;
  wire switchNumb10__0_carry__1_n_4;
  wire switchNumb10__0_carry__1_n_5;
  wire switchNumb10__0_carry__1_n_6;
  wire switchNumb10__0_carry__1_n_7;
  wire switchNumb10__0_carry__1_n_8;
  wire switchNumb10__0_carry__1_n_9;
  wire switchNumb10__0_carry__2_n_15;
  wire switchNumb10__0_carry_i_10_n_0;
  wire switchNumb10__0_carry_i_1_n_0;
  wire switchNumb10__0_carry_i_8_n_0;
  wire switchNumb10__0_carry_i_9_n_0;
  wire switchNumb10__0_carry_n_0;
  wire switchNumb10__0_carry_n_1;
  wire switchNumb10__0_carry_n_10;
  wire switchNumb10__0_carry_n_11;
  wire switchNumb10__0_carry_n_12;
  wire switchNumb10__0_carry_n_13;
  wire switchNumb10__0_carry_n_14;
  wire switchNumb10__0_carry_n_15;
  wire switchNumb10__0_carry_n_2;
  wire switchNumb10__0_carry_n_3;
  wire switchNumb10__0_carry_n_4;
  wire switchNumb10__0_carry_n_5;
  wire switchNumb10__0_carry_n_6;
  wire switchNumb10__0_carry_n_7;
  wire switchNumb10__0_carry_n_8;
  wire switchNumb10__0_carry_n_9;
  wire switchNumb10__51_carry__0_n_0;
  wire switchNumb10__51_carry__0_n_1;
  wire switchNumb10__51_carry__0_n_2;
  wire switchNumb10__51_carry__0_n_3;
  wire switchNumb10__51_carry__0_n_4;
  wire switchNumb10__51_carry__0_n_5;
  wire switchNumb10__51_carry__0_n_6;
  wire switchNumb10__51_carry__0_n_7;
  wire switchNumb10__51_carry__1_n_0;
  wire switchNumb10__51_carry__1_n_1;
  wire switchNumb10__51_carry__1_n_2;
  wire switchNumb10__51_carry__1_n_3;
  wire switchNumb10__51_carry__1_n_4;
  wire switchNumb10__51_carry__1_n_5;
  wire switchNumb10__51_carry__1_n_6;
  wire switchNumb10__51_carry__1_n_7;
  wire switchNumb10__51_carry_i_1_n_0;
  wire switchNumb10__51_carry_i_2_n_0;
  wire switchNumb10__51_carry_i_3_n_0;
  wire switchNumb10__51_carry_n_0;
  wire switchNumb10__51_carry_n_1;
  wire switchNumb10__51_carry_n_2;
  wire switchNumb10__51_carry_n_3;
  wire switchNumb10__51_carry_n_4;
  wire switchNumb10__51_carry_n_5;
  wire switchNumb10__51_carry_n_6;
  wire switchNumb10__51_carry_n_7;
  wire switchNumb111_out;
  wire switchNumb114_out;
  wire [7:0]NLW_switchNumb10__0_carry__2_CO_UNCONNECTED;
  wire [7:1]NLW_switchNumb10__0_carry__2_O_UNCONNECTED;
  wire [7:0]NLW_switchNumb10__51_carry__2_CO_UNCONNECTED;
  wire [7:1]NLW_switchNumb10__51_carry__2_O_UNCONNECTED;

  (* ADDER_THRESHOLD = "35" *) 
  CARRY8 switchNumb10__0_carry
       (.CI(1'b0),
        .CI_TOP(1'b0),
        .CO({switchNumb10__0_carry_n_0,switchNumb10__0_carry_n_1,switchNumb10__0_carry_n_2,switchNumb10__0_carry_n_3,switchNumb10__0_carry_n_4,switchNumb10__0_carry_n_5,switchNumb10__0_carry_n_6,switchNumb10__0_carry_n_7}),
        .DI({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,switchNumb10__0_carry_i_1_n_0,1'b0}),
        .O({switchNumb10__0_carry_n_8,switchNumb10__0_carry_n_9,switchNumb10__0_carry_n_10,switchNumb10__0_carry_n_11,switchNumb10__0_carry_n_12,switchNumb10__0_carry_n_13,switchNumb10__0_carry_n_14,switchNumb10__0_carry_n_15}),
        .S({switchNumb1[7:2],switchNumb10__0_carry_i_8_n_0,switchNumb10__0_carry_i_9_n_0}));
  (* ADDER_THRESHOLD = "35" *) 
  CARRY8 switchNumb10__0_carry__0
       (.CI(switchNumb10__0_carry_n_0),
        .CI_TOP(1'b0),
        .CO({switchNumb10__0_carry__0_n_0,switchNumb10__0_carry__0_n_1,switchNumb10__0_carry__0_n_2,switchNumb10__0_carry__0_n_3,switchNumb10__0_carry__0_n_4,switchNumb10__0_carry__0_n_5,switchNumb10__0_carry__0_n_6,switchNumb10__0_carry__0_n_7}),
        .DI({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .O({switchNumb10__0_carry__0_n_8,switchNumb10__0_carry__0_n_9,switchNumb10__0_carry__0_n_10,switchNumb10__0_carry__0_n_11,switchNumb10__0_carry__0_n_12,switchNumb10__0_carry__0_n_13,switchNumb10__0_carry__0_n_14,switchNumb10__0_carry__0_n_15}),
        .S(switchNumb1[15:8]));
  LUT3 #(
    .INIT(8'hA2)) 
    switchNumb10__0_carry__0_i_1
       (.I0(switchNumb10__0_carry__1_0[15]),
        .I1(bResetAXI_1),
        .I2(reset_old2_out1),
        .O(switchNumb1[15]));
  LUT3 #(
    .INIT(8'hA2)) 
    switchNumb10__0_carry__0_i_2
       (.I0(switchNumb10__0_carry__1_0[14]),
        .I1(bResetAXI_1),
        .I2(reset_old2_out1),
        .O(switchNumb1[14]));
  LUT3 #(
    .INIT(8'hA2)) 
    switchNumb10__0_carry__0_i_3
       (.I0(switchNumb10__0_carry__1_0[13]),
        .I1(bResetAXI_1),
        .I2(reset_old2_out1),
        .O(switchNumb1[13]));
  LUT3 #(
    .INIT(8'hA2)) 
    switchNumb10__0_carry__0_i_4
       (.I0(switchNumb10__0_carry__1_0[12]),
        .I1(bResetAXI_1),
        .I2(reset_old2_out1),
        .O(switchNumb1[12]));
  LUT3 #(
    .INIT(8'hA2)) 
    switchNumb10__0_carry__0_i_5
       (.I0(switchNumb10__0_carry__1_0[11]),
        .I1(bResetAXI_1),
        .I2(reset_old2_out1),
        .O(switchNumb1[11]));
  LUT3 #(
    .INIT(8'hA2)) 
    switchNumb10__0_carry__0_i_6
       (.I0(switchNumb10__0_carry__1_0[10]),
        .I1(bResetAXI_1),
        .I2(reset_old2_out1),
        .O(switchNumb1[10]));
  LUT3 #(
    .INIT(8'hA2)) 
    switchNumb10__0_carry__0_i_7
       (.I0(switchNumb10__0_carry__1_0[9]),
        .I1(bResetAXI_1),
        .I2(reset_old2_out1),
        .O(switchNumb1[9]));
  LUT3 #(
    .INIT(8'hA2)) 
    switchNumb10__0_carry__0_i_8
       (.I0(switchNumb10__0_carry__1_0[8]),
        .I1(bResetAXI_1),
        .I2(reset_old2_out1),
        .O(switchNumb1[8]));
  (* ADDER_THRESHOLD = "35" *) 
  CARRY8 switchNumb10__0_carry__1
       (.CI(switchNumb10__0_carry__0_n_0),
        .CI_TOP(1'b0),
        .CO({switchNumb10__0_carry__1_n_0,switchNumb10__0_carry__1_n_1,switchNumb10__0_carry__1_n_2,switchNumb10__0_carry__1_n_3,switchNumb10__0_carry__1_n_4,switchNumb10__0_carry__1_n_5,switchNumb10__0_carry__1_n_6,switchNumb10__0_carry__1_n_7}),
        .DI({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .O({switchNumb10__0_carry__1_n_8,switchNumb10__0_carry__1_n_9,switchNumb10__0_carry__1_n_10,switchNumb10__0_carry__1_n_11,switchNumb10__0_carry__1_n_12,switchNumb10__0_carry__1_n_13,switchNumb10__0_carry__1_n_14,switchNumb10__0_carry__1_n_15}),
        .S(switchNumb1[23:16]));
  LUT3 #(
    .INIT(8'hA2)) 
    switchNumb10__0_carry__1_i_1
       (.I0(switchNumb10__0_carry__1_0[23]),
        .I1(bResetAXI_1),
        .I2(reset_old2_out1),
        .O(switchNumb1[23]));
  LUT3 #(
    .INIT(8'hA2)) 
    switchNumb10__0_carry__1_i_2
       (.I0(switchNumb10__0_carry__1_0[22]),
        .I1(bResetAXI_1),
        .I2(reset_old2_out1),
        .O(switchNumb1[22]));
  LUT3 #(
    .INIT(8'hA2)) 
    switchNumb10__0_carry__1_i_3
       (.I0(switchNumb10__0_carry__1_0[21]),
        .I1(bResetAXI_1),
        .I2(reset_old2_out1),
        .O(switchNumb1[21]));
  LUT3 #(
    .INIT(8'hA2)) 
    switchNumb10__0_carry__1_i_4
       (.I0(switchNumb10__0_carry__1_0[20]),
        .I1(bResetAXI_1),
        .I2(reset_old2_out1),
        .O(switchNumb1[20]));
  LUT3 #(
    .INIT(8'hA2)) 
    switchNumb10__0_carry__1_i_5
       (.I0(switchNumb10__0_carry__1_0[19]),
        .I1(bResetAXI_1),
        .I2(reset_old2_out1),
        .O(switchNumb1[19]));
  LUT3 #(
    .INIT(8'hA2)) 
    switchNumb10__0_carry__1_i_6
       (.I0(switchNumb10__0_carry__1_0[18]),
        .I1(bResetAXI_1),
        .I2(reset_old2_out1),
        .O(switchNumb1[18]));
  LUT3 #(
    .INIT(8'hA2)) 
    switchNumb10__0_carry__1_i_7
       (.I0(switchNumb10__0_carry__1_0[17]),
        .I1(bResetAXI_1),
        .I2(reset_old2_out1),
        .O(switchNumb1[17]));
  LUT3 #(
    .INIT(8'hA2)) 
    switchNumb10__0_carry__1_i_8
       (.I0(switchNumb10__0_carry__1_0[16]),
        .I1(bResetAXI_1),
        .I2(reset_old2_out1),
        .O(switchNumb1[16]));
  (* ADDER_THRESHOLD = "35" *) 
  CARRY8 switchNumb10__0_carry__2
       (.CI(switchNumb10__0_carry__1_n_0),
        .CI_TOP(1'b0),
        .CO(NLW_switchNumb10__0_carry__2_CO_UNCONNECTED[7:0]),
        .DI({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .O({NLW_switchNumb10__0_carry__2_O_UNCONNECTED[7:1],switchNumb10__0_carry__2_n_15}),
        .S({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,S}));
  LUT6 #(
    .INIT(64'h06606FF606600660)) 
    switchNumb10__0_carry_i_1
       (.I0(D[1]),
        .I1(Q[1]),
        .I2(D[0]),
        .I3(Q[0]),
        .I4(switchNumb10__0_carry_i_10_n_0),
        .I5(switchNumb10__0_carry__1_0[0]),
        .O(switchNumb10__0_carry_i_1_n_0));
  LUT2 #(
    .INIT(4'h4)) 
    switchNumb10__0_carry_i_10
       (.I0(reset_old2_out1),
        .I1(bResetAXI_1),
        .O(switchNumb10__0_carry_i_10_n_0));
  LUT2 #(
    .INIT(4'h6)) 
    switchNumb10__0_carry_i_11
       (.I0(Q[0]),
        .I1(D[0]),
        .O(switchNumb114_out));
  LUT3 #(
    .INIT(8'hA2)) 
    switchNumb10__0_carry_i_2
       (.I0(switchNumb10__0_carry__1_0[7]),
        .I1(bResetAXI_1),
        .I2(reset_old2_out1),
        .O(switchNumb1[7]));
  LUT3 #(
    .INIT(8'hA2)) 
    switchNumb10__0_carry_i_3
       (.I0(switchNumb10__0_carry__1_0[6]),
        .I1(bResetAXI_1),
        .I2(reset_old2_out1),
        .O(switchNumb1[6]));
  LUT3 #(
    .INIT(8'hA2)) 
    switchNumb10__0_carry_i_4
       (.I0(switchNumb10__0_carry__1_0[5]),
        .I1(bResetAXI_1),
        .I2(reset_old2_out1),
        .O(switchNumb1[5]));
  LUT3 #(
    .INIT(8'hA2)) 
    switchNumb10__0_carry_i_5
       (.I0(switchNumb10__0_carry__1_0[4]),
        .I1(bResetAXI_1),
        .I2(reset_old2_out1),
        .O(switchNumb1[4]));
  LUT3 #(
    .INIT(8'hA2)) 
    switchNumb10__0_carry_i_6
       (.I0(switchNumb10__0_carry__1_0[3]),
        .I1(bResetAXI_1),
        .I2(reset_old2_out1),
        .O(switchNumb1[3]));
  LUT3 #(
    .INIT(8'hA2)) 
    switchNumb10__0_carry_i_7
       (.I0(switchNumb10__0_carry__1_0[2]),
        .I1(bResetAXI_1),
        .I2(reset_old2_out1),
        .O(switchNumb1[2]));
  LUT6 #(
    .INIT(64'h0CC071170CC08EE8)) 
    switchNumb10__0_carry_i_8
       (.I0(switchNumb10__0_carry__1_0[0]),
        .I1(switchNumb114_out),
        .I2(Q[1]),
        .I3(D[1]),
        .I4(switchNumb10__0_carry_i_10_n_0),
        .I5(switchNumb10__0_carry__1_0[1]),
        .O(switchNumb10__0_carry_i_8_n_0));
  LUT6 #(
    .INIT(64'h4BB4B44BB44B4BB4)) 
    switchNumb10__0_carry_i_9
       (.I0(switchNumb10__0_carry_i_10_n_0),
        .I1(switchNumb10__0_carry__1_0[0]),
        .I2(Q[1]),
        .I3(D[1]),
        .I4(Q[0]),
        .I5(D[0]),
        .O(switchNumb10__0_carry_i_9_n_0));
  (* ADDER_THRESHOLD = "35" *) 
  CARRY8 switchNumb10__51_carry
       (.CI(switchNumb10__51_carry_i_1_n_0),
        .CI_TOP(1'b0),
        .CO({switchNumb10__51_carry_n_0,switchNumb10__51_carry_n_1,switchNumb10__51_carry_n_2,switchNumb10__51_carry_n_3,switchNumb10__51_carry_n_4,switchNumb10__51_carry_n_5,switchNumb10__51_carry_n_6,switchNumb10__51_carry_n_7}),
        .DI({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,switchNumb10__0_carry_n_14,switchNumb10__0_carry_n_15}),
        .O(switchNumb[7:0]),
        .S({switchNumb10__0_carry_n_8,switchNumb10__0_carry_n_9,switchNumb10__0_carry_n_10,switchNumb10__0_carry_n_11,switchNumb10__0_carry_n_12,switchNumb10__0_carry_n_13,switchNumb10__51_carry_i_2_n_0,switchNumb10__51_carry_i_3_n_0}));
  (* ADDER_THRESHOLD = "35" *) 
  CARRY8 switchNumb10__51_carry__0
       (.CI(switchNumb10__51_carry_n_0),
        .CI_TOP(1'b0),
        .CO({switchNumb10__51_carry__0_n_0,switchNumb10__51_carry__0_n_1,switchNumb10__51_carry__0_n_2,switchNumb10__51_carry__0_n_3,switchNumb10__51_carry__0_n_4,switchNumb10__51_carry__0_n_5,switchNumb10__51_carry__0_n_6,switchNumb10__51_carry__0_n_7}),
        .DI({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .O(switchNumb[15:8]),
        .S({switchNumb10__0_carry__0_n_8,switchNumb10__0_carry__0_n_9,switchNumb10__0_carry__0_n_10,switchNumb10__0_carry__0_n_11,switchNumb10__0_carry__0_n_12,switchNumb10__0_carry__0_n_13,switchNumb10__0_carry__0_n_14,switchNumb10__0_carry__0_n_15}));
  (* ADDER_THRESHOLD = "35" *) 
  CARRY8 switchNumb10__51_carry__1
       (.CI(switchNumb10__51_carry__0_n_0),
        .CI_TOP(1'b0),
        .CO({switchNumb10__51_carry__1_n_0,switchNumb10__51_carry__1_n_1,switchNumb10__51_carry__1_n_2,switchNumb10__51_carry__1_n_3,switchNumb10__51_carry__1_n_4,switchNumb10__51_carry__1_n_5,switchNumb10__51_carry__1_n_6,switchNumb10__51_carry__1_n_7}),
        .DI({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .O(switchNumb[23:16]),
        .S({switchNumb10__0_carry__1_n_8,switchNumb10__0_carry__1_n_9,switchNumb10__0_carry__1_n_10,switchNumb10__0_carry__1_n_11,switchNumb10__0_carry__1_n_12,switchNumb10__0_carry__1_n_13,switchNumb10__0_carry__1_n_14,switchNumb10__0_carry__1_n_15}));
  (* ADDER_THRESHOLD = "35" *) 
  CARRY8 switchNumb10__51_carry__2
       (.CI(switchNumb10__51_carry__1_n_0),
        .CI_TOP(1'b0),
        .CO(NLW_switchNumb10__51_carry__2_CO_UNCONNECTED[7:0]),
        .DI({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .O({NLW_switchNumb10__51_carry__2_O_UNCONNECTED[7:1],switchNumb[24]}),
        .S({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,switchNumb10__0_carry__2_n_15}));
  LUT6 #(
    .INIT(64'h6996966996696996)) 
    switchNumb10__51_carry_i_1
       (.I0(D[2]),
        .I1(Q[2]),
        .I2(Q[4]),
        .I3(D[4]),
        .I4(Q[3]),
        .I5(D[3]),
        .O(switchNumb10__51_carry_i_1_n_0));
  LUT6 #(
    .INIT(64'h96AA5596559696AA)) 
    switchNumb10__51_carry_i_2
       (.I0(switchNumb10__0_carry_n_14),
        .I1(Q[2]),
        .I2(D[2]),
        .I3(switchNumb111_out),
        .I4(Q[4]),
        .I5(D[4]),
        .O(switchNumb10__51_carry_i_2_n_0));
  LUT3 #(
    .INIT(8'h96)) 
    switchNumb10__51_carry_i_3
       (.I0(D[5]),
        .I1(Q[5]),
        .I2(switchNumb10__0_carry_n_15),
        .O(switchNumb10__51_carry_i_3_n_0));
  LUT2 #(
    .INIT(4'h6)) 
    switchNumb10__51_carry_i_4
       (.I0(Q[3]),
        .I1(D[3]),
        .O(switchNumb111_out));
endmodule

(* ORIG_REF_NAME = "Counter_f_sw_V2_ip_src_Counter_f_sw_V2" *) 
module zusys_Counter_f_sw_V2_ip_0_0_Counter_f_sw_V2_ip_src_Counter_f_sw_V2
   (switchNumb,
    SR,
    E,
    ss_in_5,
    IPCORE_CLK,
    ss_in_4,
    ss_in_3,
    ss_in_2,
    ss_in_1,
    ss_in_0,
    bResetAXI,
    IPCORE_RESETN,
    soft_reset,
    AXI4_Lite_ARESETN);
  output [24:0]switchNumb;
  input [0:0]SR;
  input [0:0]E;
  input ss_in_5;
  input IPCORE_CLK;
  input ss_in_4;
  input ss_in_3;
  input ss_in_2;
  input ss_in_1;
  input ss_in_0;
  input bResetAXI;
  input IPCORE_RESETN;
  input soft_reset;
  input AXI4_Lite_ARESETN;

  wire AXI4_Lite_ARESETN;
  wire [0:0]E;
  wire IPCORE_CLK;
  wire IPCORE_RESETN;
  wire [0:5]Mux_out1;
  wire [0:0]SR;
  wire \SS_Old_out1_reg_n_0_[5] ;
  wire bResetAXI;
  wire bResetAXI_1;
  wire [24:0]delay_out1;
  wire reset_old2_out1;
  wire reset_old2_out1_i_1_n_0;
  wire soft_reset;
  wire ss_in_0;
  wire ss_in_1;
  wire ss_in_2;
  wire ss_in_3;
  wire ss_in_4;
  wire ss_in_5;
  wire ss_v_old_0;
  wire ss_v_old_1;
  wire ss_v_old_2;
  wire ss_v_old_3;
  wire ss_v_old_4;
  wire [24:0]switchNumb;
  wire [24:24]switchNumb1;

  FDRE \SS_Old_out1_reg[0] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(Mux_out1[0]),
        .Q(ss_v_old_0),
        .R(SR));
  FDRE \SS_Old_out1_reg[1] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(Mux_out1[1]),
        .Q(ss_v_old_1),
        .R(SR));
  FDRE \SS_Old_out1_reg[2] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(Mux_out1[2]),
        .Q(ss_v_old_2),
        .R(SR));
  FDRE \SS_Old_out1_reg[3] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(Mux_out1[3]),
        .Q(ss_v_old_3),
        .R(SR));
  FDRE \SS_Old_out1_reg[4] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(Mux_out1[4]),
        .Q(ss_v_old_4),
        .R(SR));
  FDRE \SS_Old_out1_reg[5] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(Mux_out1[5]),
        .Q(\SS_Old_out1_reg_n_0_[5] ),
        .R(SR));
  FDRE bResetAXI_1_reg
       (.C(IPCORE_CLK),
        .CE(E),
        .D(bResetAXI),
        .Q(bResetAXI_1),
        .R(SR));
  FDRE \delay_out1_reg[0] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(switchNumb[0]),
        .Q(delay_out1[0]),
        .R(SR));
  FDRE \delay_out1_reg[10] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(switchNumb[10]),
        .Q(delay_out1[10]),
        .R(SR));
  FDRE \delay_out1_reg[11] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(switchNumb[11]),
        .Q(delay_out1[11]),
        .R(SR));
  FDRE \delay_out1_reg[12] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(switchNumb[12]),
        .Q(delay_out1[12]),
        .R(SR));
  FDRE \delay_out1_reg[13] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(switchNumb[13]),
        .Q(delay_out1[13]),
        .R(SR));
  FDRE \delay_out1_reg[14] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(switchNumb[14]),
        .Q(delay_out1[14]),
        .R(SR));
  FDRE \delay_out1_reg[15] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(switchNumb[15]),
        .Q(delay_out1[15]),
        .R(SR));
  FDRE \delay_out1_reg[16] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(switchNumb[16]),
        .Q(delay_out1[16]),
        .R(SR));
  FDRE \delay_out1_reg[17] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(switchNumb[17]),
        .Q(delay_out1[17]),
        .R(SR));
  FDRE \delay_out1_reg[18] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(switchNumb[18]),
        .Q(delay_out1[18]),
        .R(SR));
  FDRE \delay_out1_reg[19] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(switchNumb[19]),
        .Q(delay_out1[19]),
        .R(SR));
  FDRE \delay_out1_reg[1] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(switchNumb[1]),
        .Q(delay_out1[1]),
        .R(SR));
  FDRE \delay_out1_reg[20] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(switchNumb[20]),
        .Q(delay_out1[20]),
        .R(SR));
  FDRE \delay_out1_reg[21] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(switchNumb[21]),
        .Q(delay_out1[21]),
        .R(SR));
  FDRE \delay_out1_reg[22] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(switchNumb[22]),
        .Q(delay_out1[22]),
        .R(SR));
  FDRE \delay_out1_reg[23] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(switchNumb[23]),
        .Q(delay_out1[23]),
        .R(SR));
  FDRE \delay_out1_reg[24] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(switchNumb[24]),
        .Q(delay_out1[24]),
        .R(SR));
  FDRE \delay_out1_reg[2] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(switchNumb[2]),
        .Q(delay_out1[2]),
        .R(SR));
  FDRE \delay_out1_reg[3] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(switchNumb[3]),
        .Q(delay_out1[3]),
        .R(SR));
  FDRE \delay_out1_reg[4] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(switchNumb[4]),
        .Q(delay_out1[4]),
        .R(SR));
  FDRE \delay_out1_reg[5] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(switchNumb[5]),
        .Q(delay_out1[5]),
        .R(SR));
  FDRE \delay_out1_reg[6] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(switchNumb[6]),
        .Q(delay_out1[6]),
        .R(SR));
  FDRE \delay_out1_reg[7] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(switchNumb[7]),
        .Q(delay_out1[7]),
        .R(SR));
  FDRE \delay_out1_reg[8] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(switchNumb[8]),
        .Q(delay_out1[8]),
        .R(SR));
  FDRE \delay_out1_reg[9] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(switchNumb[9]),
        .Q(delay_out1[9]),
        .R(SR));
  LUT6 #(
    .INIT(64'h0000CA0000000000)) 
    reset_old2_out1_i_1
       (.I0(reset_old2_out1),
        .I1(bResetAXI_1),
        .I2(E),
        .I3(IPCORE_RESETN),
        .I4(soft_reset),
        .I5(AXI4_Lite_ARESETN),
        .O(reset_old2_out1_i_1_n_0));
  FDRE reset_old2_out1_reg
       (.C(IPCORE_CLK),
        .CE(1'b1),
        .D(reset_old2_out1_i_1_n_0),
        .Q(reset_old2_out1),
        .R(1'b0));
  FDRE ss_in_0_1_reg
       (.C(IPCORE_CLK),
        .CE(E),
        .D(ss_in_0),
        .Q(Mux_out1[0]),
        .R(SR));
  FDRE ss_in_1_1_reg
       (.C(IPCORE_CLK),
        .CE(E),
        .D(ss_in_1),
        .Q(Mux_out1[1]),
        .R(SR));
  FDRE ss_in_2_1_reg
       (.C(IPCORE_CLK),
        .CE(E),
        .D(ss_in_2),
        .Q(Mux_out1[2]),
        .R(SR));
  FDRE ss_in_3_1_reg
       (.C(IPCORE_CLK),
        .CE(E),
        .D(ss_in_3),
        .Q(Mux_out1[3]),
        .R(SR));
  FDRE ss_in_4_1_reg
       (.C(IPCORE_CLK),
        .CE(E),
        .D(ss_in_4),
        .Q(Mux_out1[4]),
        .R(SR));
  FDRE ss_in_5_1_reg
       (.C(IPCORE_CLK),
        .CE(E),
        .D(ss_in_5),
        .Q(Mux_out1[5]),
        .R(SR));
  LUT3 #(
    .INIT(8'hA2)) 
    switchNumb10__0_carry__2_i_1
       (.I0(delay_out1[24]),
        .I1(bResetAXI_1),
        .I2(reset_old2_out1),
        .O(switchNumb1));
  zusys_Counter_f_sw_V2_ip_0_0_Counter_f_sw_V2_ip_src_Count_f_sw u_Count_f_sw
       (.D({Mux_out1[0],Mux_out1[1],Mux_out1[2],Mux_out1[3],Mux_out1[4],Mux_out1[5]}),
        .Q({ss_v_old_0,ss_v_old_1,ss_v_old_2,ss_v_old_3,ss_v_old_4,\SS_Old_out1_reg_n_0_[5] }),
        .S(switchNumb1),
        .bResetAXI_1(bResetAXI_1),
        .reset_old2_out1(reset_old2_out1),
        .switchNumb(switchNumb),
        .switchNumb10__0_carry__1_0(delay_out1[23:0]));
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
