// Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// --------------------------------------------------------------------------------
// Tool Version: Vivado v.2020.1.1 (win64) Build 2960000 Wed Aug  5 22:57:20 MDT 2020
// Date        : Fri Jan 28 14:50:25 2022
// Host        : enc177112 running 64-bit major release  (build 9200)
// Command     : write_verilog -force -mode funcsim
//               c:/GIT/UltraZohm/software/ultrazohm_sw_develop/vivado/zusys/ip/zusys_IncreEncoder_V24_ip_0_0/zusys_IncreEncoder_V24_ip_0_0_sim_netlist.v
// Design      : zusys_IncreEncoder_V24_ip_0_0
// Purpose     : This verilog netlist is a functional simulation representation of the design and should not be modified
//               or synthesized. This netlist cannot be used for SDF annotated simulation.
// Device      : xczu9eg-ffvc900-1-e
// --------------------------------------------------------------------------------
`timescale 1 ps / 1 ps

(* CHECK_LICENSE_TYPE = "zusys_IncreEncoder_V24_ip_0_0,IncreEncoder_V24_ip,{}" *) (* downgradeipidentifiedwarnings = "yes" *) (* ip_definition_source = "package_project" *) 
(* x_core_info = "IncreEncoder_V24_ip,Vivado 2020.1.1" *) 
(* NotValidForBitStream *)
module zusys_IncreEncoder_V24_ip_0_0
   (IPCORE_CLK,
    IPCORE_RESETN,
    A,
    B,
    I,
    PeriodEnd,
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
    omega,
    theta_el,
    position,
    edge_rsvd,
    count,
    OverSamplFactor,
    AXI4_Lite_AWREADY,
    AXI4_Lite_WREADY,
    AXI4_Lite_BRESP,
    AXI4_Lite_BVALID,
    AXI4_Lite_ARREADY,
    AXI4_Lite_RDATA,
    AXI4_Lite_RRESP,
    AXI4_Lite_RVALID);
  (* x_interface_info = "xilinx.com:signal:clock:1.0 IPCORE_CLK CLK" *) (* x_interface_parameter = "XIL_INTERFACENAME IPCORE_CLK, ASSOCIATED_RESET IPCORE_RESETN, FREQ_HZ 50000000, FREQ_TOLERANCE_HZ 0, PHASE 0.0, CLK_DOMAIN zusys_clk_wiz_0_0_clk_50MHz, INSERT_VIP 0" *) input IPCORE_CLK;
  (* x_interface_info = "xilinx.com:signal:reset:1.0 IPCORE_RESETN RST" *) (* x_interface_parameter = "XIL_INTERFACENAME IPCORE_RESETN, POLARITY ACTIVE_LOW, INSERT_VIP 0" *) input IPCORE_RESETN;
  input A;
  input B;
  input I;
  input PeriodEnd;
  (* x_interface_info = "xilinx.com:signal:clock:1.0 AXI4_Lite_signal_clock CLK" *) (* x_interface_parameter = "XIL_INTERFACENAME AXI4_Lite_signal_clock, ASSOCIATED_BUSIF AXI4_Lite, ASSOCIATED_RESET AXI4_Lite_ARESETN, FREQ_HZ 50000000, FREQ_TOLERANCE_HZ 0, PHASE 0.0, CLK_DOMAIN zusys_clk_wiz_0_0_clk_50MHz, INSERT_VIP 0" *) input AXI4_Lite_ACLK;
  (* x_interface_info = "xilinx.com:signal:reset:1.0 AXI4_Lite_signal_reset RST" *) (* x_interface_parameter = "XIL_INTERFACENAME AXI4_Lite_signal_reset, POLARITY ACTIVE_LOW, INSERT_VIP 0" *) input AXI4_Lite_ARESETN;
  (* x_interface_info = "xilinx.com:interface:aximm:1.0 AXI4_Lite AWADDR" *) (* x_interface_parameter = "XIL_INTERFACENAME AXI4_Lite, DATA_WIDTH 32, PROTOCOL AXI4LITE, FREQ_HZ 50000000, ID_WIDTH 0, ADDR_WIDTH 16, AWUSER_WIDTH 0, ARUSER_WIDTH 0, WUSER_WIDTH 0, RUSER_WIDTH 0, BUSER_WIDTH 0, READ_WRITE_MODE READ_WRITE, HAS_BURST 0, HAS_LOCK 0, HAS_PROT 0, HAS_CACHE 0, HAS_QOS 0, HAS_REGION 0, HAS_WSTRB 1, HAS_BRESP 1, HAS_RRESP 1, SUPPORTS_NARROW_BURST 0, NUM_READ_OUTSTANDING 1, NUM_WRITE_OUTSTANDING 1, MAX_BURST_LENGTH 1, PHASE 0.0, CLK_DOMAIN zusys_clk_wiz_0_0_clk_50MHz, NUM_READ_THREADS 1, NUM_WRITE_THREADS 1, RUSER_BITS_PER_BYTE 0, WUSER_BITS_PER_BYTE 0, INSERT_VIP 0" *) input [15:0]AXI4_Lite_AWADDR;
  (* x_interface_info = "xilinx.com:interface:aximm:1.0 AXI4_Lite AWVALID" *) input AXI4_Lite_AWVALID;
  (* x_interface_info = "xilinx.com:interface:aximm:1.0 AXI4_Lite WDATA" *) input [31:0]AXI4_Lite_WDATA;
  (* x_interface_info = "xilinx.com:interface:aximm:1.0 AXI4_Lite WSTRB" *) input [3:0]AXI4_Lite_WSTRB;
  (* x_interface_info = "xilinx.com:interface:aximm:1.0 AXI4_Lite WVALID" *) input AXI4_Lite_WVALID;
  (* x_interface_info = "xilinx.com:interface:aximm:1.0 AXI4_Lite BREADY" *) input AXI4_Lite_BREADY;
  (* x_interface_info = "xilinx.com:interface:aximm:1.0 AXI4_Lite ARADDR" *) input [15:0]AXI4_Lite_ARADDR;
  (* x_interface_info = "xilinx.com:interface:aximm:1.0 AXI4_Lite ARVALID" *) input AXI4_Lite_ARVALID;
  (* x_interface_info = "xilinx.com:interface:aximm:1.0 AXI4_Lite RREADY" *) input AXI4_Lite_RREADY;
  output [23:0]omega;
  output [23:0]theta_el;
  output [15:0]position;
  output edge_rsvd;
  output count;
  output [15:0]OverSamplFactor;
  (* x_interface_info = "xilinx.com:interface:aximm:1.0 AXI4_Lite AWREADY" *) output AXI4_Lite_AWREADY;
  (* x_interface_info = "xilinx.com:interface:aximm:1.0 AXI4_Lite WREADY" *) output AXI4_Lite_WREADY;
  (* x_interface_info = "xilinx.com:interface:aximm:1.0 AXI4_Lite BRESP" *) output [1:0]AXI4_Lite_BRESP;
  (* x_interface_info = "xilinx.com:interface:aximm:1.0 AXI4_Lite BVALID" *) output AXI4_Lite_BVALID;
  (* x_interface_info = "xilinx.com:interface:aximm:1.0 AXI4_Lite ARREADY" *) output AXI4_Lite_ARREADY;
  (* x_interface_info = "xilinx.com:interface:aximm:1.0 AXI4_Lite RDATA" *) output [31:0]AXI4_Lite_RDATA;
  (* x_interface_info = "xilinx.com:interface:aximm:1.0 AXI4_Lite RRESP" *) output [1:0]AXI4_Lite_RRESP;
  (* x_interface_info = "xilinx.com:interface:aximm:1.0 AXI4_Lite RVALID" *) output AXI4_Lite_RVALID;

  wire \<const0> ;
  wire A;
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
  wire B;
  wire I;
  wire IPCORE_CLK;
  wire IPCORE_RESETN;
  wire [15:0]OverSamplFactor;
  wire PeriodEnd;
  wire count;
  wire edge_rsvd;
  wire [23:0]omega;
  wire [15:0]position;
  wire [23:0]theta_el;

  assign AXI4_Lite_BRESP[1] = \<const0> ;
  assign AXI4_Lite_BRESP[0] = \<const0> ;
  assign AXI4_Lite_RDATA[31] = \^AXI4_Lite_RDATA [27];
  assign AXI4_Lite_RDATA[30] = \^AXI4_Lite_RDATA [29];
  assign AXI4_Lite_RDATA[29] = \^AXI4_Lite_RDATA [29];
  assign AXI4_Lite_RDATA[28] = \^AXI4_Lite_RDATA [29];
  assign AXI4_Lite_RDATA[27] = \^AXI4_Lite_RDATA [27];
  assign AXI4_Lite_RDATA[26] = \^AXI4_Lite_RDATA [29];
  assign AXI4_Lite_RDATA[25] = \^AXI4_Lite_RDATA [29];
  assign AXI4_Lite_RDATA[24] = \^AXI4_Lite_RDATA [29];
  assign AXI4_Lite_RDATA[23] = \^AXI4_Lite_RDATA [29];
  assign AXI4_Lite_RDATA[22:0] = \^AXI4_Lite_RDATA [22:0];
  assign AXI4_Lite_RRESP[1] = \<const0> ;
  assign AXI4_Lite_RRESP[0] = \<const0> ;
  GND GND
       (.G(\<const0> ));
  zusys_IncreEncoder_V24_ip_0_0_IncreEncoder_V24_ip U0
       (.A(A),
        .AXI4_Lite_ACLK(AXI4_Lite_ACLK),
        .AXI4_Lite_ARADDR(AXI4_Lite_ARADDR[15:2]),
        .AXI4_Lite_ARESETN(AXI4_Lite_ARESETN),
        .AXI4_Lite_ARREADY(AXI4_Lite_ARREADY),
        .AXI4_Lite_ARVALID(AXI4_Lite_ARVALID),
        .AXI4_Lite_AWADDR(AXI4_Lite_AWADDR[15:2]),
        .AXI4_Lite_AWREADY(AXI4_Lite_AWREADY),
        .AXI4_Lite_AWVALID(AXI4_Lite_AWVALID),
        .AXI4_Lite_BREADY(AXI4_Lite_BREADY),
        .AXI4_Lite_BVALID(AXI4_Lite_BVALID),
        .AXI4_Lite_RDATA({\^AXI4_Lite_RDATA [27],\^AXI4_Lite_RDATA [29],\^AXI4_Lite_RDATA [22:0]}),
        .AXI4_Lite_RREADY(AXI4_Lite_RREADY),
        .AXI4_Lite_RVALID(AXI4_Lite_RVALID),
        .AXI4_Lite_WDATA(AXI4_Lite_WDATA),
        .AXI4_Lite_WREADY(AXI4_Lite_WREADY),
        .AXI4_Lite_WSTRB(AXI4_Lite_WSTRB),
        .AXI4_Lite_WVALID(AXI4_Lite_WVALID),
        .B(B),
        .I(I),
        .IPCORE_CLK(IPCORE_CLK),
        .IPCORE_RESETN(IPCORE_RESETN),
        .OverSamplFactor(OverSamplFactor),
        .PeriodEnd(PeriodEnd),
        .Q(omega[23]),
        .count(count),
        .edge_rsvd(edge_rsvd),
        .omega(omega[22:0]),
        .position(position),
        .theta_el(theta_el));
endmodule

(* ORIG_REF_NAME = "IncreEncoder_V24_ip" *) 
module zusys_IncreEncoder_V24_ip_0_0_IncreEncoder_V24_ip
   (Q,
    AXI4_Lite_RVALID,
    AXI4_Lite_BVALID,
    AXI4_Lite_WREADY,
    omega,
    theta_el,
    position,
    AXI4_Lite_RDATA,
    edge_rsvd,
    count,
    OverSamplFactor,
    AXI4_Lite_ARREADY,
    AXI4_Lite_AWREADY,
    IPCORE_CLK,
    PeriodEnd,
    I,
    A,
    B,
    AXI4_Lite_ACLK,
    AXI4_Lite_AWADDR,
    AXI4_Lite_WDATA,
    AXI4_Lite_ARESETN,
    AXI4_Lite_ARADDR,
    AXI4_Lite_ARVALID,
    AXI4_Lite_RREADY,
    AXI4_Lite_AWVALID,
    AXI4_Lite_WVALID,
    IPCORE_RESETN,
    AXI4_Lite_BREADY,
    AXI4_Lite_WSTRB);
  output [0:0]Q;
  output AXI4_Lite_RVALID;
  output AXI4_Lite_BVALID;
  output AXI4_Lite_WREADY;
  output [22:0]omega;
  output [23:0]theta_el;
  output [15:0]position;
  output [24:0]AXI4_Lite_RDATA;
  output edge_rsvd;
  output count;
  output [15:0]OverSamplFactor;
  output AXI4_Lite_ARREADY;
  output AXI4_Lite_AWREADY;
  input IPCORE_CLK;
  input PeriodEnd;
  input I;
  input A;
  input B;
  input AXI4_Lite_ACLK;
  input [13:0]AXI4_Lite_AWADDR;
  input [31:0]AXI4_Lite_WDATA;
  input AXI4_Lite_ARESETN;
  input [13:0]AXI4_Lite_ARADDR;
  input AXI4_Lite_ARVALID;
  input AXI4_Lite_RREADY;
  input AXI4_Lite_AWVALID;
  input AXI4_Lite_WVALID;
  input IPCORE_RESETN;
  input AXI4_Lite_BREADY;
  input [3:0]AXI4_Lite_WSTRB;

  wire A;
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
  wire [24:0]AXI4_Lite_RDATA;
  wire AXI4_Lite_RREADY;
  wire AXI4_Lite_RVALID;
  wire [31:0]AXI4_Lite_WDATA;
  wire AXI4_Lite_WREADY;
  wire [3:0]AXI4_Lite_WSTRB;
  wire AXI4_Lite_WVALID;
  wire B;
  wire I;
  wire IPCORE_CLK;
  wire IPCORE_RESETN;
  wire [15:0]OverSamplFactor;
  wire PeriodEnd;
  wire [0:0]Q;
  wire count;
  wire [15:0]countPerPeriod_AXI4_sig;
  wire edge_rsvd;
  wire [22:0]omega;
  wire [15:0]position;
  wire reset;
  wire [23:0]theta_el;
  wire u_IncreEncoder_V24_ip_axi_lite_inst_n_3;
  wire [0:0]\u_IncreEncoder_V24_ip_src_IncreEncoder_V24/u_Counter_theta_ele/p_1_in ;
  wire [3:0]\u_IncreEncoder_V24_ip_src_IncreEncoder_V24/u_Counter_theta_ele/reset_old5_out1 ;
  wire \u_IncreEncoder_V24_ip_src_IncreEncoder_V24/u_IncreEncoder_V24_tc/phase_0 ;
  wire [15:0]write_IncPerTurn_elek_AXI4;
  wire [15:0]write_IncPerTurn_mech_AXI4;
  wire [23:0]write_OmegaPerOverSampl_AXI4;
  wire [23:0]write_PI2_Inc_AXI4;
  wire [31:0]write_Timer_FPGA_ms_AXI4;
  wire write_axi_enable;

  zusys_IncreEncoder_V24_ip_0_0_IncreEncoder_V24_ip_axi_lite u_IncreEncoder_V24_ip_axi_lite_inst
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
        .AXI4_Lite_WDATA(AXI4_Lite_WDATA),
        .AXI4_Lite_WSTRB(AXI4_Lite_WSTRB),
        .AXI4_Lite_WVALID(AXI4_Lite_WVALID),
        .D({Q,omega}),
        .FSM_sequential_axi_lite_rstate_reg(AXI4_Lite_RVALID),
        .IPCORE_RESETN(IPCORE_RESETN),
        .Q({AXI4_Lite_BVALID,AXI4_Lite_WREADY}),
        .RSTP(reset),
        .p_1_in(\u_IncreEncoder_V24_ip_src_IncreEncoder_V24/u_Counter_theta_ele/p_1_in ),
        .phase_0(\u_IncreEncoder_V24_ip_src_IncreEncoder_V24/u_IncreEncoder_V24_tc/phase_0 ),
        .phase_0_reg(u_IncreEncoder_V24_ip_axi_lite_inst_n_3),
        .position(position),
        .\read_reg_countPerPeriod_AXI4_reg[15] (countPerPeriod_AXI4_sig),
        .reset_old5_out1({\u_IncreEncoder_V24_ip_src_IncreEncoder_V24/u_Counter_theta_ele/reset_old5_out1 [3],\u_IncreEncoder_V24_ip_src_IncreEncoder_V24/u_Counter_theta_ele/reset_old5_out1 [0]}),
        .theta_el(theta_el),
        .write_axi_enable(write_axi_enable),
        .\write_reg_IncPerTurn_elek_AXI4_reg[15] (write_IncPerTurn_elek_AXI4),
        .\write_reg_IncPerTurn_mech_AXI4_reg[15] (write_IncPerTurn_mech_AXI4),
        .\write_reg_OmegaPerOverSampl_AXI4_reg[23] (write_OmegaPerOverSampl_AXI4),
        .\write_reg_PI2_Inc_AXI4_reg[23] (write_PI2_Inc_AXI4),
        .\write_reg_Timer_FPGA_ms_AXI4_reg[31] (write_Timer_FPGA_ms_AXI4));
  zusys_IncreEncoder_V24_ip_0_0_IncreEncoder_V24_ip_dut u_IncreEncoder_V24_ip_dut_inst
       (.A(A),
        .B(B),
        .D({Q,omega}),
        .DSP_ALU_INST(write_PI2_Inc_AXI4),
        .I(I),
        .IPCORE_CLK(IPCORE_CLK),
        .OverSamplFactor(OverSamplFactor),
        .PeriodEnd(PeriodEnd),
        .\Pipeline2_out1_reg[15] (write_IncPerTurn_elek_AXI4),
        .\Pipeline3_out1_reg[15] (write_IncPerTurn_mech_AXI4),
        .\Pipeline4_out1_reg[23] (write_OmegaPerOverSampl_AXI4),
        .\Pipeline6_out1_reg[31] (write_Timer_FPGA_ms_AXI4),
        .RSTP(reset),
        .count(count),
        .\countPerPEriod_1_reg[15] (countPerPeriod_AXI4_sig),
        .edge_rsvd(edge_rsvd),
        .phase_0(\u_IncreEncoder_V24_ip_src_IncreEncoder_V24/u_IncreEncoder_V24_tc/phase_0 ),
        .position(position),
        .\reset_old4_out1_reg[0] (u_IncreEncoder_V24_ip_axi_lite_inst_n_3),
        .\reset_old4_out1_reg[0]_0 (\u_IncreEncoder_V24_ip_src_IncreEncoder_V24/u_Counter_theta_ele/p_1_in ),
        .reset_old5_out1({\u_IncreEncoder_V24_ip_src_IncreEncoder_V24/u_Counter_theta_ele/reset_old5_out1 [3],\u_IncreEncoder_V24_ip_src_IncreEncoder_V24/u_Counter_theta_ele/reset_old5_out1 [0]}),
        .theta_el(theta_el),
        .write_axi_enable(write_axi_enable));
endmodule

(* ORIG_REF_NAME = "IncreEncoder_V24_ip_addr_decoder" *) 
module zusys_IncreEncoder_V24_ip_0_0_IncreEncoder_V24_ip_addr_decoder
   (read_reg_ip_timestamp,
    write_axi_enable,
    phase_0_reg,
    AXI4_Lite_ARADDR_2_sp_1,
    \AXI4_Lite_ARADDR[4] ,
    Q,
    \write_reg_Timer_FPGA_ms_AXI4_reg[31]_0 ,
    \write_reg_PI2_Inc_AXI4_reg[23]_0 ,
    \write_reg_IncPerTurn_mech_AXI4_reg[15]_0 ,
    \write_reg_IncPerTurn_elek_AXI4_reg[15]_0 ,
    \write_reg_OmegaPerOverSampl_AXI4_reg[23]_0 ,
    \read_reg_omega_AXI4_reg[23]_0 ,
    \read_reg_theta_el_AXI4_reg[23]_0 ,
    \read_reg_position_AXI4_reg[15]_0 ,
    \read_reg_countPerPeriod_AXI4_reg[15]_0 ,
    SR,
    AXI4_Lite_ACLK,
    write_reg_axi_enable_reg_0,
    phase_0,
    AXI4_Lite_ARADDR,
    \AXI4_Lite_RDATA_tmp[13]_i_2 ,
    E,
    \write_reg_Timer_FPGA_ms_AXI4_reg[31]_1 ,
    \write_reg_PI2_Inc_AXI4_reg[23]_1 ,
    \write_reg_IncPerTurn_mech_AXI4_reg[15]_1 ,
    \write_reg_IncPerTurn_elek_AXI4_reg[15]_1 ,
    \write_reg_OmegaPerOverSampl_AXI4_reg[23]_1 ,
    D,
    reset_old5_out1,
    theta_el,
    position,
    \read_reg_countPerPeriod_AXI4_reg[15]_1 );
  output [0:0]read_reg_ip_timestamp;
  output write_axi_enable;
  output phase_0_reg;
  output AXI4_Lite_ARADDR_2_sp_1;
  output \AXI4_Lite_ARADDR[4] ;
  output [1:0]Q;
  output [31:0]\write_reg_Timer_FPGA_ms_AXI4_reg[31]_0 ;
  output [23:0]\write_reg_PI2_Inc_AXI4_reg[23]_0 ;
  output [15:0]\write_reg_IncPerTurn_mech_AXI4_reg[15]_0 ;
  output [15:0]\write_reg_IncPerTurn_elek_AXI4_reg[15]_0 ;
  output [23:0]\write_reg_OmegaPerOverSampl_AXI4_reg[23]_0 ;
  output [23:0]\read_reg_omega_AXI4_reg[23]_0 ;
  output [23:0]\read_reg_theta_el_AXI4_reg[23]_0 ;
  output [15:0]\read_reg_position_AXI4_reg[15]_0 ;
  output [15:0]\read_reg_countPerPeriod_AXI4_reg[15]_0 ;
  input [0:0]SR;
  input AXI4_Lite_ACLK;
  input write_reg_axi_enable_reg_0;
  input phase_0;
  input [3:0]AXI4_Lite_ARADDR;
  input \AXI4_Lite_RDATA_tmp[13]_i_2 ;
  input [0:0]E;
  input [31:0]\write_reg_Timer_FPGA_ms_AXI4_reg[31]_1 ;
  input [0:0]\write_reg_PI2_Inc_AXI4_reg[23]_1 ;
  input [0:0]\write_reg_IncPerTurn_mech_AXI4_reg[15]_1 ;
  input [0:0]\write_reg_IncPerTurn_elek_AXI4_reg[15]_1 ;
  input [0:0]\write_reg_OmegaPerOverSampl_AXI4_reg[23]_1 ;
  input [23:0]D;
  input [1:0]reset_old5_out1;
  input [23:0]theta_el;
  input [15:0]position;
  input [15:0]\read_reg_countPerPeriod_AXI4_reg[15]_1 ;

  wire AXI4_Lite_ACLK;
  wire [3:0]AXI4_Lite_ARADDR;
  wire \AXI4_Lite_ARADDR[4] ;
  wire AXI4_Lite_ARADDR_2_sn_1;
  wire \AXI4_Lite_RDATA_tmp[13]_i_2 ;
  wire [23:0]D;
  wire [0:0]E;
  wire [1:0]Q;
  wire [0:0]SR;
  wire phase_0;
  wire phase_0_reg;
  wire [15:0]position;
  wire [15:0]\read_reg_countPerPeriod_AXI4_reg[15]_0 ;
  wire [15:0]\read_reg_countPerPeriod_AXI4_reg[15]_1 ;
  wire [0:0]read_reg_ip_timestamp;
  wire [23:0]\read_reg_omega_AXI4_reg[23]_0 ;
  wire [15:0]\read_reg_position_AXI4_reg[15]_0 ;
  wire [23:0]\read_reg_theta_el_AXI4_reg[23]_0 ;
  wire [1:0]reset_old5_out1;
  wire [23:0]theta_el;
  wire write_axi_enable;
  wire [15:0]\write_reg_IncPerTurn_elek_AXI4_reg[15]_0 ;
  wire [0:0]\write_reg_IncPerTurn_elek_AXI4_reg[15]_1 ;
  wire [15:0]\write_reg_IncPerTurn_mech_AXI4_reg[15]_0 ;
  wire [0:0]\write_reg_IncPerTurn_mech_AXI4_reg[15]_1 ;
  wire [23:0]\write_reg_OmegaPerOverSampl_AXI4_reg[23]_0 ;
  wire [0:0]\write_reg_OmegaPerOverSampl_AXI4_reg[23]_1 ;
  wire [23:0]\write_reg_PI2_Inc_AXI4_reg[23]_0 ;
  wire [0:0]\write_reg_PI2_Inc_AXI4_reg[23]_1 ;
  wire [31:0]\write_reg_Timer_FPGA_ms_AXI4_reg[31]_0 ;
  wire [31:0]\write_reg_Timer_FPGA_ms_AXI4_reg[31]_1 ;
  wire write_reg_axi_enable_reg_0;

  assign AXI4_Lite_ARADDR_2_sp_1 = AXI4_Lite_ARADDR_2_sn_1;
  LUT6 #(
    .INIT(64'h8002800000020000)) 
    \AXI4_Lite_RDATA_tmp[13]_i_4 
       (.I0(\AXI4_Lite_RDATA_tmp[13]_i_2 ),
        .I1(AXI4_Lite_ARADDR[1]),
        .I2(AXI4_Lite_ARADDR[0]),
        .I3(AXI4_Lite_ARADDR[3]),
        .I4(read_reg_ip_timestamp),
        .I5(Q[1]),
        .O(\AXI4_Lite_ARADDR[4] ));
  LUT3 #(
    .INIT(8'hF8)) 
    \omega_oversampled[23]_i_1 
       (.I0(phase_0),
        .I1(write_axi_enable),
        .I2(SR),
        .O(phase_0_reg));
  FDRE \read_reg_countPerPeriod_AXI4_reg[0] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(\read_reg_countPerPeriod_AXI4_reg[15]_1 [0]),
        .Q(\read_reg_countPerPeriod_AXI4_reg[15]_0 [0]),
        .R(SR));
  FDRE \read_reg_countPerPeriod_AXI4_reg[10] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(\read_reg_countPerPeriod_AXI4_reg[15]_1 [10]),
        .Q(\read_reg_countPerPeriod_AXI4_reg[15]_0 [10]),
        .R(SR));
  FDRE \read_reg_countPerPeriod_AXI4_reg[11] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(\read_reg_countPerPeriod_AXI4_reg[15]_1 [11]),
        .Q(\read_reg_countPerPeriod_AXI4_reg[15]_0 [11]),
        .R(SR));
  FDRE \read_reg_countPerPeriod_AXI4_reg[12] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(\read_reg_countPerPeriod_AXI4_reg[15]_1 [12]),
        .Q(\read_reg_countPerPeriod_AXI4_reg[15]_0 [12]),
        .R(SR));
  FDRE \read_reg_countPerPeriod_AXI4_reg[13] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(\read_reg_countPerPeriod_AXI4_reg[15]_1 [13]),
        .Q(\read_reg_countPerPeriod_AXI4_reg[15]_0 [13]),
        .R(SR));
  FDRE \read_reg_countPerPeriod_AXI4_reg[14] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(\read_reg_countPerPeriod_AXI4_reg[15]_1 [14]),
        .Q(\read_reg_countPerPeriod_AXI4_reg[15]_0 [14]),
        .R(SR));
  FDRE \read_reg_countPerPeriod_AXI4_reg[15] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(\read_reg_countPerPeriod_AXI4_reg[15]_1 [15]),
        .Q(\read_reg_countPerPeriod_AXI4_reg[15]_0 [15]),
        .R(SR));
  FDRE \read_reg_countPerPeriod_AXI4_reg[1] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(\read_reg_countPerPeriod_AXI4_reg[15]_1 [1]),
        .Q(\read_reg_countPerPeriod_AXI4_reg[15]_0 [1]),
        .R(SR));
  FDRE \read_reg_countPerPeriod_AXI4_reg[2] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(\read_reg_countPerPeriod_AXI4_reg[15]_1 [2]),
        .Q(\read_reg_countPerPeriod_AXI4_reg[15]_0 [2]),
        .R(SR));
  FDRE \read_reg_countPerPeriod_AXI4_reg[3] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(\read_reg_countPerPeriod_AXI4_reg[15]_1 [3]),
        .Q(\read_reg_countPerPeriod_AXI4_reg[15]_0 [3]),
        .R(SR));
  FDRE \read_reg_countPerPeriod_AXI4_reg[4] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(\read_reg_countPerPeriod_AXI4_reg[15]_1 [4]),
        .Q(\read_reg_countPerPeriod_AXI4_reg[15]_0 [4]),
        .R(SR));
  FDRE \read_reg_countPerPeriod_AXI4_reg[5] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(\read_reg_countPerPeriod_AXI4_reg[15]_1 [5]),
        .Q(\read_reg_countPerPeriod_AXI4_reg[15]_0 [5]),
        .R(SR));
  FDRE \read_reg_countPerPeriod_AXI4_reg[6] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(\read_reg_countPerPeriod_AXI4_reg[15]_1 [6]),
        .Q(\read_reg_countPerPeriod_AXI4_reg[15]_0 [6]),
        .R(SR));
  FDRE \read_reg_countPerPeriod_AXI4_reg[7] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(\read_reg_countPerPeriod_AXI4_reg[15]_1 [7]),
        .Q(\read_reg_countPerPeriod_AXI4_reg[15]_0 [7]),
        .R(SR));
  FDRE \read_reg_countPerPeriod_AXI4_reg[8] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(\read_reg_countPerPeriod_AXI4_reg[15]_1 [8]),
        .Q(\read_reg_countPerPeriod_AXI4_reg[15]_0 [8]),
        .R(SR));
  FDRE \read_reg_countPerPeriod_AXI4_reg[9] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(\read_reg_countPerPeriod_AXI4_reg[15]_1 [9]),
        .Q(\read_reg_countPerPeriod_AXI4_reg[15]_0 [9]),
        .R(SR));
  FDRE \read_reg_direction_AXI4_reg[0] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(reset_old5_out1[0]),
        .Q(Q[0]),
        .R(SR));
  FDRE \read_reg_direction_AXI4_reg[3] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(reset_old5_out1[1]),
        .Q(Q[1]),
        .R(SR));
  FDRE \read_reg_ip_timestamp_reg[30] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(1'b1),
        .Q(read_reg_ip_timestamp),
        .R(SR));
  FDRE \read_reg_omega_AXI4_reg[0] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(D[0]),
        .Q(\read_reg_omega_AXI4_reg[23]_0 [0]),
        .R(SR));
  FDRE \read_reg_omega_AXI4_reg[10] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(D[10]),
        .Q(\read_reg_omega_AXI4_reg[23]_0 [10]),
        .R(SR));
  FDRE \read_reg_omega_AXI4_reg[11] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(D[11]),
        .Q(\read_reg_omega_AXI4_reg[23]_0 [11]),
        .R(SR));
  FDRE \read_reg_omega_AXI4_reg[12] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(D[12]),
        .Q(\read_reg_omega_AXI4_reg[23]_0 [12]),
        .R(SR));
  FDRE \read_reg_omega_AXI4_reg[13] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(D[13]),
        .Q(\read_reg_omega_AXI4_reg[23]_0 [13]),
        .R(SR));
  FDRE \read_reg_omega_AXI4_reg[14] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(D[14]),
        .Q(\read_reg_omega_AXI4_reg[23]_0 [14]),
        .R(SR));
  FDRE \read_reg_omega_AXI4_reg[15] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(D[15]),
        .Q(\read_reg_omega_AXI4_reg[23]_0 [15]),
        .R(SR));
  FDRE \read_reg_omega_AXI4_reg[16] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(D[16]),
        .Q(\read_reg_omega_AXI4_reg[23]_0 [16]),
        .R(SR));
  FDRE \read_reg_omega_AXI4_reg[17] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(D[17]),
        .Q(\read_reg_omega_AXI4_reg[23]_0 [17]),
        .R(SR));
  FDRE \read_reg_omega_AXI4_reg[18] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(D[18]),
        .Q(\read_reg_omega_AXI4_reg[23]_0 [18]),
        .R(SR));
  FDRE \read_reg_omega_AXI4_reg[19] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(D[19]),
        .Q(\read_reg_omega_AXI4_reg[23]_0 [19]),
        .R(SR));
  FDRE \read_reg_omega_AXI4_reg[1] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(D[1]),
        .Q(\read_reg_omega_AXI4_reg[23]_0 [1]),
        .R(SR));
  FDRE \read_reg_omega_AXI4_reg[20] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(D[20]),
        .Q(\read_reg_omega_AXI4_reg[23]_0 [20]),
        .R(SR));
  FDRE \read_reg_omega_AXI4_reg[21] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(D[21]),
        .Q(\read_reg_omega_AXI4_reg[23]_0 [21]),
        .R(SR));
  FDRE \read_reg_omega_AXI4_reg[22] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(D[22]),
        .Q(\read_reg_omega_AXI4_reg[23]_0 [22]),
        .R(SR));
  FDRE \read_reg_omega_AXI4_reg[23] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(D[23]),
        .Q(\read_reg_omega_AXI4_reg[23]_0 [23]),
        .R(SR));
  FDRE \read_reg_omega_AXI4_reg[2] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(D[2]),
        .Q(\read_reg_omega_AXI4_reg[23]_0 [2]),
        .R(SR));
  FDRE \read_reg_omega_AXI4_reg[3] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(D[3]),
        .Q(\read_reg_omega_AXI4_reg[23]_0 [3]),
        .R(SR));
  FDRE \read_reg_omega_AXI4_reg[4] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(D[4]),
        .Q(\read_reg_omega_AXI4_reg[23]_0 [4]),
        .R(SR));
  FDRE \read_reg_omega_AXI4_reg[5] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(D[5]),
        .Q(\read_reg_omega_AXI4_reg[23]_0 [5]),
        .R(SR));
  FDRE \read_reg_omega_AXI4_reg[6] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(D[6]),
        .Q(\read_reg_omega_AXI4_reg[23]_0 [6]),
        .R(SR));
  FDRE \read_reg_omega_AXI4_reg[7] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(D[7]),
        .Q(\read_reg_omega_AXI4_reg[23]_0 [7]),
        .R(SR));
  FDRE \read_reg_omega_AXI4_reg[8] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(D[8]),
        .Q(\read_reg_omega_AXI4_reg[23]_0 [8]),
        .R(SR));
  FDRE \read_reg_omega_AXI4_reg[9] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(D[9]),
        .Q(\read_reg_omega_AXI4_reg[23]_0 [9]),
        .R(SR));
  FDRE \read_reg_position_AXI4_reg[0] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(position[0]),
        .Q(\read_reg_position_AXI4_reg[15]_0 [0]),
        .R(SR));
  FDRE \read_reg_position_AXI4_reg[10] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(position[10]),
        .Q(\read_reg_position_AXI4_reg[15]_0 [10]),
        .R(SR));
  FDRE \read_reg_position_AXI4_reg[11] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(position[11]),
        .Q(\read_reg_position_AXI4_reg[15]_0 [11]),
        .R(SR));
  FDRE \read_reg_position_AXI4_reg[12] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(position[12]),
        .Q(\read_reg_position_AXI4_reg[15]_0 [12]),
        .R(SR));
  FDRE \read_reg_position_AXI4_reg[13] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(position[13]),
        .Q(\read_reg_position_AXI4_reg[15]_0 [13]),
        .R(SR));
  FDRE \read_reg_position_AXI4_reg[14] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(position[14]),
        .Q(\read_reg_position_AXI4_reg[15]_0 [14]),
        .R(SR));
  FDRE \read_reg_position_AXI4_reg[15] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(position[15]),
        .Q(\read_reg_position_AXI4_reg[15]_0 [15]),
        .R(SR));
  FDRE \read_reg_position_AXI4_reg[1] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(position[1]),
        .Q(\read_reg_position_AXI4_reg[15]_0 [1]),
        .R(SR));
  FDRE \read_reg_position_AXI4_reg[2] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(position[2]),
        .Q(\read_reg_position_AXI4_reg[15]_0 [2]),
        .R(SR));
  FDRE \read_reg_position_AXI4_reg[3] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(position[3]),
        .Q(\read_reg_position_AXI4_reg[15]_0 [3]),
        .R(SR));
  FDRE \read_reg_position_AXI4_reg[4] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(position[4]),
        .Q(\read_reg_position_AXI4_reg[15]_0 [4]),
        .R(SR));
  FDRE \read_reg_position_AXI4_reg[5] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(position[5]),
        .Q(\read_reg_position_AXI4_reg[15]_0 [5]),
        .R(SR));
  FDRE \read_reg_position_AXI4_reg[6] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(position[6]),
        .Q(\read_reg_position_AXI4_reg[15]_0 [6]),
        .R(SR));
  FDRE \read_reg_position_AXI4_reg[7] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(position[7]),
        .Q(\read_reg_position_AXI4_reg[15]_0 [7]),
        .R(SR));
  FDRE \read_reg_position_AXI4_reg[8] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(position[8]),
        .Q(\read_reg_position_AXI4_reg[15]_0 [8]),
        .R(SR));
  FDRE \read_reg_position_AXI4_reg[9] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(position[9]),
        .Q(\read_reg_position_AXI4_reg[15]_0 [9]),
        .R(SR));
  FDRE \read_reg_theta_el_AXI4_reg[0] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(theta_el[0]),
        .Q(\read_reg_theta_el_AXI4_reg[23]_0 [0]),
        .R(SR));
  FDRE \read_reg_theta_el_AXI4_reg[10] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(theta_el[10]),
        .Q(\read_reg_theta_el_AXI4_reg[23]_0 [10]),
        .R(SR));
  FDRE \read_reg_theta_el_AXI4_reg[11] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(theta_el[11]),
        .Q(\read_reg_theta_el_AXI4_reg[23]_0 [11]),
        .R(SR));
  FDRE \read_reg_theta_el_AXI4_reg[12] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(theta_el[12]),
        .Q(\read_reg_theta_el_AXI4_reg[23]_0 [12]),
        .R(SR));
  FDRE \read_reg_theta_el_AXI4_reg[13] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(theta_el[13]),
        .Q(\read_reg_theta_el_AXI4_reg[23]_0 [13]),
        .R(SR));
  FDRE \read_reg_theta_el_AXI4_reg[14] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(theta_el[14]),
        .Q(\read_reg_theta_el_AXI4_reg[23]_0 [14]),
        .R(SR));
  FDRE \read_reg_theta_el_AXI4_reg[15] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(theta_el[15]),
        .Q(\read_reg_theta_el_AXI4_reg[23]_0 [15]),
        .R(SR));
  FDRE \read_reg_theta_el_AXI4_reg[16] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(theta_el[16]),
        .Q(\read_reg_theta_el_AXI4_reg[23]_0 [16]),
        .R(SR));
  FDRE \read_reg_theta_el_AXI4_reg[17] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(theta_el[17]),
        .Q(\read_reg_theta_el_AXI4_reg[23]_0 [17]),
        .R(SR));
  FDRE \read_reg_theta_el_AXI4_reg[18] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(theta_el[18]),
        .Q(\read_reg_theta_el_AXI4_reg[23]_0 [18]),
        .R(SR));
  FDRE \read_reg_theta_el_AXI4_reg[19] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(theta_el[19]),
        .Q(\read_reg_theta_el_AXI4_reg[23]_0 [19]),
        .R(SR));
  FDRE \read_reg_theta_el_AXI4_reg[1] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(theta_el[1]),
        .Q(\read_reg_theta_el_AXI4_reg[23]_0 [1]),
        .R(SR));
  FDRE \read_reg_theta_el_AXI4_reg[20] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(theta_el[20]),
        .Q(\read_reg_theta_el_AXI4_reg[23]_0 [20]),
        .R(SR));
  FDRE \read_reg_theta_el_AXI4_reg[21] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(theta_el[21]),
        .Q(\read_reg_theta_el_AXI4_reg[23]_0 [21]),
        .R(SR));
  FDRE \read_reg_theta_el_AXI4_reg[22] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(theta_el[22]),
        .Q(\read_reg_theta_el_AXI4_reg[23]_0 [22]),
        .R(SR));
  FDRE \read_reg_theta_el_AXI4_reg[23] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(theta_el[23]),
        .Q(\read_reg_theta_el_AXI4_reg[23]_0 [23]),
        .R(SR));
  FDRE \read_reg_theta_el_AXI4_reg[2] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(theta_el[2]),
        .Q(\read_reg_theta_el_AXI4_reg[23]_0 [2]),
        .R(SR));
  FDRE \read_reg_theta_el_AXI4_reg[3] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(theta_el[3]),
        .Q(\read_reg_theta_el_AXI4_reg[23]_0 [3]),
        .R(SR));
  FDRE \read_reg_theta_el_AXI4_reg[4] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(theta_el[4]),
        .Q(\read_reg_theta_el_AXI4_reg[23]_0 [4]),
        .R(SR));
  FDRE \read_reg_theta_el_AXI4_reg[5] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(theta_el[5]),
        .Q(\read_reg_theta_el_AXI4_reg[23]_0 [5]),
        .R(SR));
  FDRE \read_reg_theta_el_AXI4_reg[6] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(theta_el[6]),
        .Q(\read_reg_theta_el_AXI4_reg[23]_0 [6]),
        .R(SR));
  FDRE \read_reg_theta_el_AXI4_reg[7] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(theta_el[7]),
        .Q(\read_reg_theta_el_AXI4_reg[23]_0 [7]),
        .R(SR));
  FDRE \read_reg_theta_el_AXI4_reg[8] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(theta_el[8]),
        .Q(\read_reg_theta_el_AXI4_reg[23]_0 [8]),
        .R(SR));
  FDRE \read_reg_theta_el_AXI4_reg[9] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(theta_el[9]),
        .Q(\read_reg_theta_el_AXI4_reg[23]_0 [9]),
        .R(SR));
  FDRE \write_reg_IncPerTurn_elek_AXI4_reg[0] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_IncPerTurn_elek_AXI4_reg[15]_1 ),
        .D(\write_reg_Timer_FPGA_ms_AXI4_reg[31]_1 [0]),
        .Q(\write_reg_IncPerTurn_elek_AXI4_reg[15]_0 [0]),
        .R(SR));
  FDRE \write_reg_IncPerTurn_elek_AXI4_reg[10] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_IncPerTurn_elek_AXI4_reg[15]_1 ),
        .D(\write_reg_Timer_FPGA_ms_AXI4_reg[31]_1 [10]),
        .Q(\write_reg_IncPerTurn_elek_AXI4_reg[15]_0 [10]),
        .R(SR));
  FDRE \write_reg_IncPerTurn_elek_AXI4_reg[11] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_IncPerTurn_elek_AXI4_reg[15]_1 ),
        .D(\write_reg_Timer_FPGA_ms_AXI4_reg[31]_1 [11]),
        .Q(\write_reg_IncPerTurn_elek_AXI4_reg[15]_0 [11]),
        .R(SR));
  FDRE \write_reg_IncPerTurn_elek_AXI4_reg[12] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_IncPerTurn_elek_AXI4_reg[15]_1 ),
        .D(\write_reg_Timer_FPGA_ms_AXI4_reg[31]_1 [12]),
        .Q(\write_reg_IncPerTurn_elek_AXI4_reg[15]_0 [12]),
        .R(SR));
  FDRE \write_reg_IncPerTurn_elek_AXI4_reg[13] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_IncPerTurn_elek_AXI4_reg[15]_1 ),
        .D(\write_reg_Timer_FPGA_ms_AXI4_reg[31]_1 [13]),
        .Q(\write_reg_IncPerTurn_elek_AXI4_reg[15]_0 [13]),
        .R(SR));
  FDRE \write_reg_IncPerTurn_elek_AXI4_reg[14] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_IncPerTurn_elek_AXI4_reg[15]_1 ),
        .D(\write_reg_Timer_FPGA_ms_AXI4_reg[31]_1 [14]),
        .Q(\write_reg_IncPerTurn_elek_AXI4_reg[15]_0 [14]),
        .R(SR));
  FDRE \write_reg_IncPerTurn_elek_AXI4_reg[15] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_IncPerTurn_elek_AXI4_reg[15]_1 ),
        .D(\write_reg_Timer_FPGA_ms_AXI4_reg[31]_1 [15]),
        .Q(\write_reg_IncPerTurn_elek_AXI4_reg[15]_0 [15]),
        .R(SR));
  FDRE \write_reg_IncPerTurn_elek_AXI4_reg[1] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_IncPerTurn_elek_AXI4_reg[15]_1 ),
        .D(\write_reg_Timer_FPGA_ms_AXI4_reg[31]_1 [1]),
        .Q(\write_reg_IncPerTurn_elek_AXI4_reg[15]_0 [1]),
        .R(SR));
  FDRE \write_reg_IncPerTurn_elek_AXI4_reg[2] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_IncPerTurn_elek_AXI4_reg[15]_1 ),
        .D(\write_reg_Timer_FPGA_ms_AXI4_reg[31]_1 [2]),
        .Q(\write_reg_IncPerTurn_elek_AXI4_reg[15]_0 [2]),
        .R(SR));
  FDRE \write_reg_IncPerTurn_elek_AXI4_reg[3] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_IncPerTurn_elek_AXI4_reg[15]_1 ),
        .D(\write_reg_Timer_FPGA_ms_AXI4_reg[31]_1 [3]),
        .Q(\write_reg_IncPerTurn_elek_AXI4_reg[15]_0 [3]),
        .R(SR));
  FDRE \write_reg_IncPerTurn_elek_AXI4_reg[4] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_IncPerTurn_elek_AXI4_reg[15]_1 ),
        .D(\write_reg_Timer_FPGA_ms_AXI4_reg[31]_1 [4]),
        .Q(\write_reg_IncPerTurn_elek_AXI4_reg[15]_0 [4]),
        .R(SR));
  FDRE \write_reg_IncPerTurn_elek_AXI4_reg[5] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_IncPerTurn_elek_AXI4_reg[15]_1 ),
        .D(\write_reg_Timer_FPGA_ms_AXI4_reg[31]_1 [5]),
        .Q(\write_reg_IncPerTurn_elek_AXI4_reg[15]_0 [5]),
        .R(SR));
  FDRE \write_reg_IncPerTurn_elek_AXI4_reg[6] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_IncPerTurn_elek_AXI4_reg[15]_1 ),
        .D(\write_reg_Timer_FPGA_ms_AXI4_reg[31]_1 [6]),
        .Q(\write_reg_IncPerTurn_elek_AXI4_reg[15]_0 [6]),
        .R(SR));
  FDRE \write_reg_IncPerTurn_elek_AXI4_reg[7] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_IncPerTurn_elek_AXI4_reg[15]_1 ),
        .D(\write_reg_Timer_FPGA_ms_AXI4_reg[31]_1 [7]),
        .Q(\write_reg_IncPerTurn_elek_AXI4_reg[15]_0 [7]),
        .R(SR));
  FDRE \write_reg_IncPerTurn_elek_AXI4_reg[8] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_IncPerTurn_elek_AXI4_reg[15]_1 ),
        .D(\write_reg_Timer_FPGA_ms_AXI4_reg[31]_1 [8]),
        .Q(\write_reg_IncPerTurn_elek_AXI4_reg[15]_0 [8]),
        .R(SR));
  FDRE \write_reg_IncPerTurn_elek_AXI4_reg[9] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_IncPerTurn_elek_AXI4_reg[15]_1 ),
        .D(\write_reg_Timer_FPGA_ms_AXI4_reg[31]_1 [9]),
        .Q(\write_reg_IncPerTurn_elek_AXI4_reg[15]_0 [9]),
        .R(SR));
  FDRE \write_reg_IncPerTurn_mech_AXI4_reg[0] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_IncPerTurn_mech_AXI4_reg[15]_1 ),
        .D(\write_reg_Timer_FPGA_ms_AXI4_reg[31]_1 [0]),
        .Q(\write_reg_IncPerTurn_mech_AXI4_reg[15]_0 [0]),
        .R(SR));
  FDRE \write_reg_IncPerTurn_mech_AXI4_reg[10] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_IncPerTurn_mech_AXI4_reg[15]_1 ),
        .D(\write_reg_Timer_FPGA_ms_AXI4_reg[31]_1 [10]),
        .Q(\write_reg_IncPerTurn_mech_AXI4_reg[15]_0 [10]),
        .R(SR));
  FDRE \write_reg_IncPerTurn_mech_AXI4_reg[11] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_IncPerTurn_mech_AXI4_reg[15]_1 ),
        .D(\write_reg_Timer_FPGA_ms_AXI4_reg[31]_1 [11]),
        .Q(\write_reg_IncPerTurn_mech_AXI4_reg[15]_0 [11]),
        .R(SR));
  FDRE \write_reg_IncPerTurn_mech_AXI4_reg[12] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_IncPerTurn_mech_AXI4_reg[15]_1 ),
        .D(\write_reg_Timer_FPGA_ms_AXI4_reg[31]_1 [12]),
        .Q(\write_reg_IncPerTurn_mech_AXI4_reg[15]_0 [12]),
        .R(SR));
  FDRE \write_reg_IncPerTurn_mech_AXI4_reg[13] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_IncPerTurn_mech_AXI4_reg[15]_1 ),
        .D(\write_reg_Timer_FPGA_ms_AXI4_reg[31]_1 [13]),
        .Q(\write_reg_IncPerTurn_mech_AXI4_reg[15]_0 [13]),
        .R(SR));
  FDRE \write_reg_IncPerTurn_mech_AXI4_reg[14] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_IncPerTurn_mech_AXI4_reg[15]_1 ),
        .D(\write_reg_Timer_FPGA_ms_AXI4_reg[31]_1 [14]),
        .Q(\write_reg_IncPerTurn_mech_AXI4_reg[15]_0 [14]),
        .R(SR));
  FDRE \write_reg_IncPerTurn_mech_AXI4_reg[15] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_IncPerTurn_mech_AXI4_reg[15]_1 ),
        .D(\write_reg_Timer_FPGA_ms_AXI4_reg[31]_1 [15]),
        .Q(\write_reg_IncPerTurn_mech_AXI4_reg[15]_0 [15]),
        .R(SR));
  FDRE \write_reg_IncPerTurn_mech_AXI4_reg[1] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_IncPerTurn_mech_AXI4_reg[15]_1 ),
        .D(\write_reg_Timer_FPGA_ms_AXI4_reg[31]_1 [1]),
        .Q(\write_reg_IncPerTurn_mech_AXI4_reg[15]_0 [1]),
        .R(SR));
  FDRE \write_reg_IncPerTurn_mech_AXI4_reg[2] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_IncPerTurn_mech_AXI4_reg[15]_1 ),
        .D(\write_reg_Timer_FPGA_ms_AXI4_reg[31]_1 [2]),
        .Q(\write_reg_IncPerTurn_mech_AXI4_reg[15]_0 [2]),
        .R(SR));
  FDRE \write_reg_IncPerTurn_mech_AXI4_reg[3] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_IncPerTurn_mech_AXI4_reg[15]_1 ),
        .D(\write_reg_Timer_FPGA_ms_AXI4_reg[31]_1 [3]),
        .Q(\write_reg_IncPerTurn_mech_AXI4_reg[15]_0 [3]),
        .R(SR));
  FDRE \write_reg_IncPerTurn_mech_AXI4_reg[4] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_IncPerTurn_mech_AXI4_reg[15]_1 ),
        .D(\write_reg_Timer_FPGA_ms_AXI4_reg[31]_1 [4]),
        .Q(\write_reg_IncPerTurn_mech_AXI4_reg[15]_0 [4]),
        .R(SR));
  FDRE \write_reg_IncPerTurn_mech_AXI4_reg[5] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_IncPerTurn_mech_AXI4_reg[15]_1 ),
        .D(\write_reg_Timer_FPGA_ms_AXI4_reg[31]_1 [5]),
        .Q(\write_reg_IncPerTurn_mech_AXI4_reg[15]_0 [5]),
        .R(SR));
  FDRE \write_reg_IncPerTurn_mech_AXI4_reg[6] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_IncPerTurn_mech_AXI4_reg[15]_1 ),
        .D(\write_reg_Timer_FPGA_ms_AXI4_reg[31]_1 [6]),
        .Q(\write_reg_IncPerTurn_mech_AXI4_reg[15]_0 [6]),
        .R(SR));
  FDRE \write_reg_IncPerTurn_mech_AXI4_reg[7] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_IncPerTurn_mech_AXI4_reg[15]_1 ),
        .D(\write_reg_Timer_FPGA_ms_AXI4_reg[31]_1 [7]),
        .Q(\write_reg_IncPerTurn_mech_AXI4_reg[15]_0 [7]),
        .R(SR));
  FDRE \write_reg_IncPerTurn_mech_AXI4_reg[8] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_IncPerTurn_mech_AXI4_reg[15]_1 ),
        .D(\write_reg_Timer_FPGA_ms_AXI4_reg[31]_1 [8]),
        .Q(\write_reg_IncPerTurn_mech_AXI4_reg[15]_0 [8]),
        .R(SR));
  FDRE \write_reg_IncPerTurn_mech_AXI4_reg[9] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_IncPerTurn_mech_AXI4_reg[15]_1 ),
        .D(\write_reg_Timer_FPGA_ms_AXI4_reg[31]_1 [9]),
        .Q(\write_reg_IncPerTurn_mech_AXI4_reg[15]_0 [9]),
        .R(SR));
  FDRE \write_reg_OmegaPerOverSampl_AXI4_reg[0] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_OmegaPerOverSampl_AXI4_reg[23]_1 ),
        .D(\write_reg_Timer_FPGA_ms_AXI4_reg[31]_1 [0]),
        .Q(\write_reg_OmegaPerOverSampl_AXI4_reg[23]_0 [0]),
        .R(SR));
  FDRE \write_reg_OmegaPerOverSampl_AXI4_reg[10] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_OmegaPerOverSampl_AXI4_reg[23]_1 ),
        .D(\write_reg_Timer_FPGA_ms_AXI4_reg[31]_1 [10]),
        .Q(\write_reg_OmegaPerOverSampl_AXI4_reg[23]_0 [10]),
        .R(SR));
  FDRE \write_reg_OmegaPerOverSampl_AXI4_reg[11] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_OmegaPerOverSampl_AXI4_reg[23]_1 ),
        .D(\write_reg_Timer_FPGA_ms_AXI4_reg[31]_1 [11]),
        .Q(\write_reg_OmegaPerOverSampl_AXI4_reg[23]_0 [11]),
        .R(SR));
  FDRE \write_reg_OmegaPerOverSampl_AXI4_reg[12] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_OmegaPerOverSampl_AXI4_reg[23]_1 ),
        .D(\write_reg_Timer_FPGA_ms_AXI4_reg[31]_1 [12]),
        .Q(\write_reg_OmegaPerOverSampl_AXI4_reg[23]_0 [12]),
        .R(SR));
  FDRE \write_reg_OmegaPerOverSampl_AXI4_reg[13] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_OmegaPerOverSampl_AXI4_reg[23]_1 ),
        .D(\write_reg_Timer_FPGA_ms_AXI4_reg[31]_1 [13]),
        .Q(\write_reg_OmegaPerOverSampl_AXI4_reg[23]_0 [13]),
        .R(SR));
  FDRE \write_reg_OmegaPerOverSampl_AXI4_reg[14] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_OmegaPerOverSampl_AXI4_reg[23]_1 ),
        .D(\write_reg_Timer_FPGA_ms_AXI4_reg[31]_1 [14]),
        .Q(\write_reg_OmegaPerOverSampl_AXI4_reg[23]_0 [14]),
        .R(SR));
  FDRE \write_reg_OmegaPerOverSampl_AXI4_reg[15] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_OmegaPerOverSampl_AXI4_reg[23]_1 ),
        .D(\write_reg_Timer_FPGA_ms_AXI4_reg[31]_1 [15]),
        .Q(\write_reg_OmegaPerOverSampl_AXI4_reg[23]_0 [15]),
        .R(SR));
  FDRE \write_reg_OmegaPerOverSampl_AXI4_reg[16] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_OmegaPerOverSampl_AXI4_reg[23]_1 ),
        .D(\write_reg_Timer_FPGA_ms_AXI4_reg[31]_1 [16]),
        .Q(\write_reg_OmegaPerOverSampl_AXI4_reg[23]_0 [16]),
        .R(SR));
  FDRE \write_reg_OmegaPerOverSampl_AXI4_reg[17] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_OmegaPerOverSampl_AXI4_reg[23]_1 ),
        .D(\write_reg_Timer_FPGA_ms_AXI4_reg[31]_1 [17]),
        .Q(\write_reg_OmegaPerOverSampl_AXI4_reg[23]_0 [17]),
        .R(SR));
  FDRE \write_reg_OmegaPerOverSampl_AXI4_reg[18] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_OmegaPerOverSampl_AXI4_reg[23]_1 ),
        .D(\write_reg_Timer_FPGA_ms_AXI4_reg[31]_1 [18]),
        .Q(\write_reg_OmegaPerOverSampl_AXI4_reg[23]_0 [18]),
        .R(SR));
  FDRE \write_reg_OmegaPerOverSampl_AXI4_reg[19] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_OmegaPerOverSampl_AXI4_reg[23]_1 ),
        .D(\write_reg_Timer_FPGA_ms_AXI4_reg[31]_1 [19]),
        .Q(\write_reg_OmegaPerOverSampl_AXI4_reg[23]_0 [19]),
        .R(SR));
  FDRE \write_reg_OmegaPerOverSampl_AXI4_reg[1] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_OmegaPerOverSampl_AXI4_reg[23]_1 ),
        .D(\write_reg_Timer_FPGA_ms_AXI4_reg[31]_1 [1]),
        .Q(\write_reg_OmegaPerOverSampl_AXI4_reg[23]_0 [1]),
        .R(SR));
  FDRE \write_reg_OmegaPerOverSampl_AXI4_reg[20] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_OmegaPerOverSampl_AXI4_reg[23]_1 ),
        .D(\write_reg_Timer_FPGA_ms_AXI4_reg[31]_1 [20]),
        .Q(\write_reg_OmegaPerOverSampl_AXI4_reg[23]_0 [20]),
        .R(SR));
  FDRE \write_reg_OmegaPerOverSampl_AXI4_reg[21] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_OmegaPerOverSampl_AXI4_reg[23]_1 ),
        .D(\write_reg_Timer_FPGA_ms_AXI4_reg[31]_1 [21]),
        .Q(\write_reg_OmegaPerOverSampl_AXI4_reg[23]_0 [21]),
        .R(SR));
  FDRE \write_reg_OmegaPerOverSampl_AXI4_reg[22] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_OmegaPerOverSampl_AXI4_reg[23]_1 ),
        .D(\write_reg_Timer_FPGA_ms_AXI4_reg[31]_1 [22]),
        .Q(\write_reg_OmegaPerOverSampl_AXI4_reg[23]_0 [22]),
        .R(SR));
  FDRE \write_reg_OmegaPerOverSampl_AXI4_reg[23] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_OmegaPerOverSampl_AXI4_reg[23]_1 ),
        .D(\write_reg_Timer_FPGA_ms_AXI4_reg[31]_1 [23]),
        .Q(\write_reg_OmegaPerOverSampl_AXI4_reg[23]_0 [23]),
        .R(SR));
  FDRE \write_reg_OmegaPerOverSampl_AXI4_reg[2] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_OmegaPerOverSampl_AXI4_reg[23]_1 ),
        .D(\write_reg_Timer_FPGA_ms_AXI4_reg[31]_1 [2]),
        .Q(\write_reg_OmegaPerOverSampl_AXI4_reg[23]_0 [2]),
        .R(SR));
  FDRE \write_reg_OmegaPerOverSampl_AXI4_reg[3] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_OmegaPerOverSampl_AXI4_reg[23]_1 ),
        .D(\write_reg_Timer_FPGA_ms_AXI4_reg[31]_1 [3]),
        .Q(\write_reg_OmegaPerOverSampl_AXI4_reg[23]_0 [3]),
        .R(SR));
  FDRE \write_reg_OmegaPerOverSampl_AXI4_reg[4] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_OmegaPerOverSampl_AXI4_reg[23]_1 ),
        .D(\write_reg_Timer_FPGA_ms_AXI4_reg[31]_1 [4]),
        .Q(\write_reg_OmegaPerOverSampl_AXI4_reg[23]_0 [4]),
        .R(SR));
  FDRE \write_reg_OmegaPerOverSampl_AXI4_reg[5] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_OmegaPerOverSampl_AXI4_reg[23]_1 ),
        .D(\write_reg_Timer_FPGA_ms_AXI4_reg[31]_1 [5]),
        .Q(\write_reg_OmegaPerOverSampl_AXI4_reg[23]_0 [5]),
        .R(SR));
  FDRE \write_reg_OmegaPerOverSampl_AXI4_reg[6] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_OmegaPerOverSampl_AXI4_reg[23]_1 ),
        .D(\write_reg_Timer_FPGA_ms_AXI4_reg[31]_1 [6]),
        .Q(\write_reg_OmegaPerOverSampl_AXI4_reg[23]_0 [6]),
        .R(SR));
  FDRE \write_reg_OmegaPerOverSampl_AXI4_reg[7] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_OmegaPerOverSampl_AXI4_reg[23]_1 ),
        .D(\write_reg_Timer_FPGA_ms_AXI4_reg[31]_1 [7]),
        .Q(\write_reg_OmegaPerOverSampl_AXI4_reg[23]_0 [7]),
        .R(SR));
  FDRE \write_reg_OmegaPerOverSampl_AXI4_reg[8] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_OmegaPerOverSampl_AXI4_reg[23]_1 ),
        .D(\write_reg_Timer_FPGA_ms_AXI4_reg[31]_1 [8]),
        .Q(\write_reg_OmegaPerOverSampl_AXI4_reg[23]_0 [8]),
        .R(SR));
  FDRE \write_reg_OmegaPerOverSampl_AXI4_reg[9] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_OmegaPerOverSampl_AXI4_reg[23]_1 ),
        .D(\write_reg_Timer_FPGA_ms_AXI4_reg[31]_1 [9]),
        .Q(\write_reg_OmegaPerOverSampl_AXI4_reg[23]_0 [9]),
        .R(SR));
  FDRE \write_reg_PI2_Inc_AXI4_reg[0] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_PI2_Inc_AXI4_reg[23]_1 ),
        .D(\write_reg_Timer_FPGA_ms_AXI4_reg[31]_1 [0]),
        .Q(\write_reg_PI2_Inc_AXI4_reg[23]_0 [0]),
        .R(SR));
  FDRE \write_reg_PI2_Inc_AXI4_reg[10] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_PI2_Inc_AXI4_reg[23]_1 ),
        .D(\write_reg_Timer_FPGA_ms_AXI4_reg[31]_1 [10]),
        .Q(\write_reg_PI2_Inc_AXI4_reg[23]_0 [10]),
        .R(SR));
  FDRE \write_reg_PI2_Inc_AXI4_reg[11] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_PI2_Inc_AXI4_reg[23]_1 ),
        .D(\write_reg_Timer_FPGA_ms_AXI4_reg[31]_1 [11]),
        .Q(\write_reg_PI2_Inc_AXI4_reg[23]_0 [11]),
        .R(SR));
  FDRE \write_reg_PI2_Inc_AXI4_reg[12] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_PI2_Inc_AXI4_reg[23]_1 ),
        .D(\write_reg_Timer_FPGA_ms_AXI4_reg[31]_1 [12]),
        .Q(\write_reg_PI2_Inc_AXI4_reg[23]_0 [12]),
        .R(SR));
  FDRE \write_reg_PI2_Inc_AXI4_reg[13] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_PI2_Inc_AXI4_reg[23]_1 ),
        .D(\write_reg_Timer_FPGA_ms_AXI4_reg[31]_1 [13]),
        .Q(\write_reg_PI2_Inc_AXI4_reg[23]_0 [13]),
        .R(SR));
  FDRE \write_reg_PI2_Inc_AXI4_reg[14] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_PI2_Inc_AXI4_reg[23]_1 ),
        .D(\write_reg_Timer_FPGA_ms_AXI4_reg[31]_1 [14]),
        .Q(\write_reg_PI2_Inc_AXI4_reg[23]_0 [14]),
        .R(SR));
  FDRE \write_reg_PI2_Inc_AXI4_reg[15] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_PI2_Inc_AXI4_reg[23]_1 ),
        .D(\write_reg_Timer_FPGA_ms_AXI4_reg[31]_1 [15]),
        .Q(\write_reg_PI2_Inc_AXI4_reg[23]_0 [15]),
        .R(SR));
  FDRE \write_reg_PI2_Inc_AXI4_reg[16] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_PI2_Inc_AXI4_reg[23]_1 ),
        .D(\write_reg_Timer_FPGA_ms_AXI4_reg[31]_1 [16]),
        .Q(\write_reg_PI2_Inc_AXI4_reg[23]_0 [16]),
        .R(SR));
  FDRE \write_reg_PI2_Inc_AXI4_reg[17] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_PI2_Inc_AXI4_reg[23]_1 ),
        .D(\write_reg_Timer_FPGA_ms_AXI4_reg[31]_1 [17]),
        .Q(\write_reg_PI2_Inc_AXI4_reg[23]_0 [17]),
        .R(SR));
  FDRE \write_reg_PI2_Inc_AXI4_reg[18] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_PI2_Inc_AXI4_reg[23]_1 ),
        .D(\write_reg_Timer_FPGA_ms_AXI4_reg[31]_1 [18]),
        .Q(\write_reg_PI2_Inc_AXI4_reg[23]_0 [18]),
        .R(SR));
  FDRE \write_reg_PI2_Inc_AXI4_reg[19] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_PI2_Inc_AXI4_reg[23]_1 ),
        .D(\write_reg_Timer_FPGA_ms_AXI4_reg[31]_1 [19]),
        .Q(\write_reg_PI2_Inc_AXI4_reg[23]_0 [19]),
        .R(SR));
  FDRE \write_reg_PI2_Inc_AXI4_reg[1] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_PI2_Inc_AXI4_reg[23]_1 ),
        .D(\write_reg_Timer_FPGA_ms_AXI4_reg[31]_1 [1]),
        .Q(\write_reg_PI2_Inc_AXI4_reg[23]_0 [1]),
        .R(SR));
  FDRE \write_reg_PI2_Inc_AXI4_reg[20] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_PI2_Inc_AXI4_reg[23]_1 ),
        .D(\write_reg_Timer_FPGA_ms_AXI4_reg[31]_1 [20]),
        .Q(\write_reg_PI2_Inc_AXI4_reg[23]_0 [20]),
        .R(SR));
  FDRE \write_reg_PI2_Inc_AXI4_reg[21] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_PI2_Inc_AXI4_reg[23]_1 ),
        .D(\write_reg_Timer_FPGA_ms_AXI4_reg[31]_1 [21]),
        .Q(\write_reg_PI2_Inc_AXI4_reg[23]_0 [21]),
        .R(SR));
  FDRE \write_reg_PI2_Inc_AXI4_reg[22] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_PI2_Inc_AXI4_reg[23]_1 ),
        .D(\write_reg_Timer_FPGA_ms_AXI4_reg[31]_1 [22]),
        .Q(\write_reg_PI2_Inc_AXI4_reg[23]_0 [22]),
        .R(SR));
  FDRE \write_reg_PI2_Inc_AXI4_reg[23] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_PI2_Inc_AXI4_reg[23]_1 ),
        .D(\write_reg_Timer_FPGA_ms_AXI4_reg[31]_1 [23]),
        .Q(\write_reg_PI2_Inc_AXI4_reg[23]_0 [23]),
        .R(SR));
  FDRE \write_reg_PI2_Inc_AXI4_reg[2] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_PI2_Inc_AXI4_reg[23]_1 ),
        .D(\write_reg_Timer_FPGA_ms_AXI4_reg[31]_1 [2]),
        .Q(\write_reg_PI2_Inc_AXI4_reg[23]_0 [2]),
        .R(SR));
  FDRE \write_reg_PI2_Inc_AXI4_reg[3] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_PI2_Inc_AXI4_reg[23]_1 ),
        .D(\write_reg_Timer_FPGA_ms_AXI4_reg[31]_1 [3]),
        .Q(\write_reg_PI2_Inc_AXI4_reg[23]_0 [3]),
        .R(SR));
  FDRE \write_reg_PI2_Inc_AXI4_reg[4] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_PI2_Inc_AXI4_reg[23]_1 ),
        .D(\write_reg_Timer_FPGA_ms_AXI4_reg[31]_1 [4]),
        .Q(\write_reg_PI2_Inc_AXI4_reg[23]_0 [4]),
        .R(SR));
  FDRE \write_reg_PI2_Inc_AXI4_reg[5] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_PI2_Inc_AXI4_reg[23]_1 ),
        .D(\write_reg_Timer_FPGA_ms_AXI4_reg[31]_1 [5]),
        .Q(\write_reg_PI2_Inc_AXI4_reg[23]_0 [5]),
        .R(SR));
  FDRE \write_reg_PI2_Inc_AXI4_reg[6] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_PI2_Inc_AXI4_reg[23]_1 ),
        .D(\write_reg_Timer_FPGA_ms_AXI4_reg[31]_1 [6]),
        .Q(\write_reg_PI2_Inc_AXI4_reg[23]_0 [6]),
        .R(SR));
  FDRE \write_reg_PI2_Inc_AXI4_reg[7] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_PI2_Inc_AXI4_reg[23]_1 ),
        .D(\write_reg_Timer_FPGA_ms_AXI4_reg[31]_1 [7]),
        .Q(\write_reg_PI2_Inc_AXI4_reg[23]_0 [7]),
        .R(SR));
  FDRE \write_reg_PI2_Inc_AXI4_reg[8] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_PI2_Inc_AXI4_reg[23]_1 ),
        .D(\write_reg_Timer_FPGA_ms_AXI4_reg[31]_1 [8]),
        .Q(\write_reg_PI2_Inc_AXI4_reg[23]_0 [8]),
        .R(SR));
  FDRE \write_reg_PI2_Inc_AXI4_reg[9] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_PI2_Inc_AXI4_reg[23]_1 ),
        .D(\write_reg_Timer_FPGA_ms_AXI4_reg[31]_1 [9]),
        .Q(\write_reg_PI2_Inc_AXI4_reg[23]_0 [9]),
        .R(SR));
  LUT2 #(
    .INIT(4'h2)) 
    \write_reg_Timer_FPGA_ms_AXI4[31]_i_3 
       (.I0(AXI4_Lite_ARADDR[0]),
        .I1(AXI4_Lite_ARADDR[2]),
        .O(AXI4_Lite_ARADDR_2_sn_1));
  FDRE \write_reg_Timer_FPGA_ms_AXI4_reg[0] 
       (.C(AXI4_Lite_ACLK),
        .CE(E),
        .D(\write_reg_Timer_FPGA_ms_AXI4_reg[31]_1 [0]),
        .Q(\write_reg_Timer_FPGA_ms_AXI4_reg[31]_0 [0]),
        .R(SR));
  FDRE \write_reg_Timer_FPGA_ms_AXI4_reg[10] 
       (.C(AXI4_Lite_ACLK),
        .CE(E),
        .D(\write_reg_Timer_FPGA_ms_AXI4_reg[31]_1 [10]),
        .Q(\write_reg_Timer_FPGA_ms_AXI4_reg[31]_0 [10]),
        .R(SR));
  FDRE \write_reg_Timer_FPGA_ms_AXI4_reg[11] 
       (.C(AXI4_Lite_ACLK),
        .CE(E),
        .D(\write_reg_Timer_FPGA_ms_AXI4_reg[31]_1 [11]),
        .Q(\write_reg_Timer_FPGA_ms_AXI4_reg[31]_0 [11]),
        .R(SR));
  FDRE \write_reg_Timer_FPGA_ms_AXI4_reg[12] 
       (.C(AXI4_Lite_ACLK),
        .CE(E),
        .D(\write_reg_Timer_FPGA_ms_AXI4_reg[31]_1 [12]),
        .Q(\write_reg_Timer_FPGA_ms_AXI4_reg[31]_0 [12]),
        .R(SR));
  FDRE \write_reg_Timer_FPGA_ms_AXI4_reg[13] 
       (.C(AXI4_Lite_ACLK),
        .CE(E),
        .D(\write_reg_Timer_FPGA_ms_AXI4_reg[31]_1 [13]),
        .Q(\write_reg_Timer_FPGA_ms_AXI4_reg[31]_0 [13]),
        .R(SR));
  FDRE \write_reg_Timer_FPGA_ms_AXI4_reg[14] 
       (.C(AXI4_Lite_ACLK),
        .CE(E),
        .D(\write_reg_Timer_FPGA_ms_AXI4_reg[31]_1 [14]),
        .Q(\write_reg_Timer_FPGA_ms_AXI4_reg[31]_0 [14]),
        .R(SR));
  FDRE \write_reg_Timer_FPGA_ms_AXI4_reg[15] 
       (.C(AXI4_Lite_ACLK),
        .CE(E),
        .D(\write_reg_Timer_FPGA_ms_AXI4_reg[31]_1 [15]),
        .Q(\write_reg_Timer_FPGA_ms_AXI4_reg[31]_0 [15]),
        .R(SR));
  FDRE \write_reg_Timer_FPGA_ms_AXI4_reg[16] 
       (.C(AXI4_Lite_ACLK),
        .CE(E),
        .D(\write_reg_Timer_FPGA_ms_AXI4_reg[31]_1 [16]),
        .Q(\write_reg_Timer_FPGA_ms_AXI4_reg[31]_0 [16]),
        .R(SR));
  FDRE \write_reg_Timer_FPGA_ms_AXI4_reg[17] 
       (.C(AXI4_Lite_ACLK),
        .CE(E),
        .D(\write_reg_Timer_FPGA_ms_AXI4_reg[31]_1 [17]),
        .Q(\write_reg_Timer_FPGA_ms_AXI4_reg[31]_0 [17]),
        .R(SR));
  FDRE \write_reg_Timer_FPGA_ms_AXI4_reg[18] 
       (.C(AXI4_Lite_ACLK),
        .CE(E),
        .D(\write_reg_Timer_FPGA_ms_AXI4_reg[31]_1 [18]),
        .Q(\write_reg_Timer_FPGA_ms_AXI4_reg[31]_0 [18]),
        .R(SR));
  FDRE \write_reg_Timer_FPGA_ms_AXI4_reg[19] 
       (.C(AXI4_Lite_ACLK),
        .CE(E),
        .D(\write_reg_Timer_FPGA_ms_AXI4_reg[31]_1 [19]),
        .Q(\write_reg_Timer_FPGA_ms_AXI4_reg[31]_0 [19]),
        .R(SR));
  FDRE \write_reg_Timer_FPGA_ms_AXI4_reg[1] 
       (.C(AXI4_Lite_ACLK),
        .CE(E),
        .D(\write_reg_Timer_FPGA_ms_AXI4_reg[31]_1 [1]),
        .Q(\write_reg_Timer_FPGA_ms_AXI4_reg[31]_0 [1]),
        .R(SR));
  FDRE \write_reg_Timer_FPGA_ms_AXI4_reg[20] 
       (.C(AXI4_Lite_ACLK),
        .CE(E),
        .D(\write_reg_Timer_FPGA_ms_AXI4_reg[31]_1 [20]),
        .Q(\write_reg_Timer_FPGA_ms_AXI4_reg[31]_0 [20]),
        .R(SR));
  FDRE \write_reg_Timer_FPGA_ms_AXI4_reg[21] 
       (.C(AXI4_Lite_ACLK),
        .CE(E),
        .D(\write_reg_Timer_FPGA_ms_AXI4_reg[31]_1 [21]),
        .Q(\write_reg_Timer_FPGA_ms_AXI4_reg[31]_0 [21]),
        .R(SR));
  FDRE \write_reg_Timer_FPGA_ms_AXI4_reg[22] 
       (.C(AXI4_Lite_ACLK),
        .CE(E),
        .D(\write_reg_Timer_FPGA_ms_AXI4_reg[31]_1 [22]),
        .Q(\write_reg_Timer_FPGA_ms_AXI4_reg[31]_0 [22]),
        .R(SR));
  FDRE \write_reg_Timer_FPGA_ms_AXI4_reg[23] 
       (.C(AXI4_Lite_ACLK),
        .CE(E),
        .D(\write_reg_Timer_FPGA_ms_AXI4_reg[31]_1 [23]),
        .Q(\write_reg_Timer_FPGA_ms_AXI4_reg[31]_0 [23]),
        .R(SR));
  FDRE \write_reg_Timer_FPGA_ms_AXI4_reg[24] 
       (.C(AXI4_Lite_ACLK),
        .CE(E),
        .D(\write_reg_Timer_FPGA_ms_AXI4_reg[31]_1 [24]),
        .Q(\write_reg_Timer_FPGA_ms_AXI4_reg[31]_0 [24]),
        .R(SR));
  FDRE \write_reg_Timer_FPGA_ms_AXI4_reg[25] 
       (.C(AXI4_Lite_ACLK),
        .CE(E),
        .D(\write_reg_Timer_FPGA_ms_AXI4_reg[31]_1 [25]),
        .Q(\write_reg_Timer_FPGA_ms_AXI4_reg[31]_0 [25]),
        .R(SR));
  FDRE \write_reg_Timer_FPGA_ms_AXI4_reg[26] 
       (.C(AXI4_Lite_ACLK),
        .CE(E),
        .D(\write_reg_Timer_FPGA_ms_AXI4_reg[31]_1 [26]),
        .Q(\write_reg_Timer_FPGA_ms_AXI4_reg[31]_0 [26]),
        .R(SR));
  FDRE \write_reg_Timer_FPGA_ms_AXI4_reg[27] 
       (.C(AXI4_Lite_ACLK),
        .CE(E),
        .D(\write_reg_Timer_FPGA_ms_AXI4_reg[31]_1 [27]),
        .Q(\write_reg_Timer_FPGA_ms_AXI4_reg[31]_0 [27]),
        .R(SR));
  FDRE \write_reg_Timer_FPGA_ms_AXI4_reg[28] 
       (.C(AXI4_Lite_ACLK),
        .CE(E),
        .D(\write_reg_Timer_FPGA_ms_AXI4_reg[31]_1 [28]),
        .Q(\write_reg_Timer_FPGA_ms_AXI4_reg[31]_0 [28]),
        .R(SR));
  FDRE \write_reg_Timer_FPGA_ms_AXI4_reg[29] 
       (.C(AXI4_Lite_ACLK),
        .CE(E),
        .D(\write_reg_Timer_FPGA_ms_AXI4_reg[31]_1 [29]),
        .Q(\write_reg_Timer_FPGA_ms_AXI4_reg[31]_0 [29]),
        .R(SR));
  FDRE \write_reg_Timer_FPGA_ms_AXI4_reg[2] 
       (.C(AXI4_Lite_ACLK),
        .CE(E),
        .D(\write_reg_Timer_FPGA_ms_AXI4_reg[31]_1 [2]),
        .Q(\write_reg_Timer_FPGA_ms_AXI4_reg[31]_0 [2]),
        .R(SR));
  FDRE \write_reg_Timer_FPGA_ms_AXI4_reg[30] 
       (.C(AXI4_Lite_ACLK),
        .CE(E),
        .D(\write_reg_Timer_FPGA_ms_AXI4_reg[31]_1 [30]),
        .Q(\write_reg_Timer_FPGA_ms_AXI4_reg[31]_0 [30]),
        .R(SR));
  FDRE \write_reg_Timer_FPGA_ms_AXI4_reg[31] 
       (.C(AXI4_Lite_ACLK),
        .CE(E),
        .D(\write_reg_Timer_FPGA_ms_AXI4_reg[31]_1 [31]),
        .Q(\write_reg_Timer_FPGA_ms_AXI4_reg[31]_0 [31]),
        .R(SR));
  FDRE \write_reg_Timer_FPGA_ms_AXI4_reg[3] 
       (.C(AXI4_Lite_ACLK),
        .CE(E),
        .D(\write_reg_Timer_FPGA_ms_AXI4_reg[31]_1 [3]),
        .Q(\write_reg_Timer_FPGA_ms_AXI4_reg[31]_0 [3]),
        .R(SR));
  FDRE \write_reg_Timer_FPGA_ms_AXI4_reg[4] 
       (.C(AXI4_Lite_ACLK),
        .CE(E),
        .D(\write_reg_Timer_FPGA_ms_AXI4_reg[31]_1 [4]),
        .Q(\write_reg_Timer_FPGA_ms_AXI4_reg[31]_0 [4]),
        .R(SR));
  FDRE \write_reg_Timer_FPGA_ms_AXI4_reg[5] 
       (.C(AXI4_Lite_ACLK),
        .CE(E),
        .D(\write_reg_Timer_FPGA_ms_AXI4_reg[31]_1 [5]),
        .Q(\write_reg_Timer_FPGA_ms_AXI4_reg[31]_0 [5]),
        .R(SR));
  FDRE \write_reg_Timer_FPGA_ms_AXI4_reg[6] 
       (.C(AXI4_Lite_ACLK),
        .CE(E),
        .D(\write_reg_Timer_FPGA_ms_AXI4_reg[31]_1 [6]),
        .Q(\write_reg_Timer_FPGA_ms_AXI4_reg[31]_0 [6]),
        .R(SR));
  FDRE \write_reg_Timer_FPGA_ms_AXI4_reg[7] 
       (.C(AXI4_Lite_ACLK),
        .CE(E),
        .D(\write_reg_Timer_FPGA_ms_AXI4_reg[31]_1 [7]),
        .Q(\write_reg_Timer_FPGA_ms_AXI4_reg[31]_0 [7]),
        .R(SR));
  FDRE \write_reg_Timer_FPGA_ms_AXI4_reg[8] 
       (.C(AXI4_Lite_ACLK),
        .CE(E),
        .D(\write_reg_Timer_FPGA_ms_AXI4_reg[31]_1 [8]),
        .Q(\write_reg_Timer_FPGA_ms_AXI4_reg[31]_0 [8]),
        .R(SR));
  FDRE \write_reg_Timer_FPGA_ms_AXI4_reg[9] 
       (.C(AXI4_Lite_ACLK),
        .CE(E),
        .D(\write_reg_Timer_FPGA_ms_AXI4_reg[31]_1 [9]),
        .Q(\write_reg_Timer_FPGA_ms_AXI4_reg[31]_0 [9]),
        .R(SR));
  FDSE write_reg_axi_enable_reg
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(write_reg_axi_enable_reg_0),
        .Q(write_axi_enable),
        .S(SR));
endmodule

(* ORIG_REF_NAME = "IncreEncoder_V24_ip_axi_lite" *) 
module zusys_IncreEncoder_V24_ip_0_0_IncreEncoder_V24_ip_axi_lite
   (FSM_sequential_axi_lite_rstate_reg,
    RSTP,
    write_axi_enable,
    phase_0_reg,
    AXI4_Lite_ARREADY,
    Q,
    AXI4_Lite_AWREADY,
    p_1_in,
    \write_reg_Timer_FPGA_ms_AXI4_reg[31] ,
    \write_reg_PI2_Inc_AXI4_reg[23] ,
    \write_reg_IncPerTurn_mech_AXI4_reg[15] ,
    \write_reg_IncPerTurn_elek_AXI4_reg[15] ,
    \write_reg_OmegaPerOverSampl_AXI4_reg[23] ,
    AXI4_Lite_RDATA,
    AXI4_Lite_ACLK,
    phase_0,
    AXI4_Lite_ARESETN,
    AXI4_Lite_ARADDR,
    AXI4_Lite_ARVALID,
    AXI4_Lite_RREADY,
    AXI4_Lite_AWVALID,
    AXI4_Lite_WVALID,
    IPCORE_RESETN,
    AXI4_Lite_BREADY,
    AXI4_Lite_WSTRB,
    AXI4_Lite_AWADDR,
    AXI4_Lite_WDATA,
    D,
    reset_old5_out1,
    theta_el,
    position,
    \read_reg_countPerPeriod_AXI4_reg[15] );
  output FSM_sequential_axi_lite_rstate_reg;
  output RSTP;
  output write_axi_enable;
  output phase_0_reg;
  output AXI4_Lite_ARREADY;
  output [1:0]Q;
  output AXI4_Lite_AWREADY;
  output [0:0]p_1_in;
  output [31:0]\write_reg_Timer_FPGA_ms_AXI4_reg[31] ;
  output [23:0]\write_reg_PI2_Inc_AXI4_reg[23] ;
  output [15:0]\write_reg_IncPerTurn_mech_AXI4_reg[15] ;
  output [15:0]\write_reg_IncPerTurn_elek_AXI4_reg[15] ;
  output [23:0]\write_reg_OmegaPerOverSampl_AXI4_reg[23] ;
  output [24:0]AXI4_Lite_RDATA;
  input AXI4_Lite_ACLK;
  input phase_0;
  input AXI4_Lite_ARESETN;
  input [13:0]AXI4_Lite_ARADDR;
  input AXI4_Lite_ARVALID;
  input AXI4_Lite_RREADY;
  input AXI4_Lite_AWVALID;
  input AXI4_Lite_WVALID;
  input IPCORE_RESETN;
  input AXI4_Lite_BREADY;
  input [3:0]AXI4_Lite_WSTRB;
  input [13:0]AXI4_Lite_AWADDR;
  input [31:0]AXI4_Lite_WDATA;
  input [23:0]D;
  input [1:0]reset_old5_out1;
  input [23:0]theta_el;
  input [15:0]position;
  input [15:0]\read_reg_countPerPeriod_AXI4_reg[15] ;

  wire AXI4_Lite_ACLK;
  wire [13:0]AXI4_Lite_ARADDR;
  wire AXI4_Lite_ARESETN;
  wire AXI4_Lite_ARREADY;
  wire AXI4_Lite_ARVALID;
  wire [13:0]AXI4_Lite_AWADDR;
  wire AXI4_Lite_AWREADY;
  wire AXI4_Lite_AWVALID;
  wire AXI4_Lite_BREADY;
  wire [24:0]AXI4_Lite_RDATA;
  wire AXI4_Lite_RREADY;
  wire [31:0]AXI4_Lite_WDATA;
  wire [3:0]AXI4_Lite_WSTRB;
  wire AXI4_Lite_WVALID;
  wire [23:0]D;
  wire FSM_sequential_axi_lite_rstate_reg;
  wire IPCORE_RESETN;
  wire [1:0]Q;
  wire RSTP;
  wire [0:0]p_1_in;
  wire phase_0;
  wire phase_0_reg;
  wire [15:0]position;
  wire [15:0]read_reg_countPerPeriod_AXI4;
  wire [15:0]\read_reg_countPerPeriod_AXI4_reg[15] ;
  wire [3:0]read_reg_direction_AXI4;
  wire [30:30]read_reg_ip_timestamp;
  wire [23:0]read_reg_omega_AXI4;
  wire [15:0]read_reg_position_AXI4;
  wire [23:0]read_reg_theta_el_AXI4;
  wire reg_enb_IncPerTurn_elek_AXI4;
  wire reg_enb_IncPerTurn_mech_AXI4;
  wire reg_enb_OmegaPerOverSampl_AXI4;
  wire reg_enb_PI2_Inc_AXI4;
  wire reg_enb_Timer_FPGA_ms_AXI4;
  wire [1:0]reset_old5_out1;
  wire [23:0]theta_el;
  wire u_IncreEncoder_V24_ip_addr_decoder_inst_n_3;
  wire u_IncreEncoder_V24_ip_addr_decoder_inst_n_4;
  wire u_IncreEncoder_V24_ip_axi_lite_module_inst_n_1;
  wire u_IncreEncoder_V24_ip_axi_lite_module_inst_n_10;
  wire u_IncreEncoder_V24_ip_axi_lite_module_inst_n_11;
  wire u_IncreEncoder_V24_ip_axi_lite_module_inst_n_12;
  wire u_IncreEncoder_V24_ip_axi_lite_module_inst_n_13;
  wire u_IncreEncoder_V24_ip_axi_lite_module_inst_n_14;
  wire u_IncreEncoder_V24_ip_axi_lite_module_inst_n_15;
  wire u_IncreEncoder_V24_ip_axi_lite_module_inst_n_16;
  wire u_IncreEncoder_V24_ip_axi_lite_module_inst_n_17;
  wire u_IncreEncoder_V24_ip_axi_lite_module_inst_n_18;
  wire u_IncreEncoder_V24_ip_axi_lite_module_inst_n_19;
  wire u_IncreEncoder_V24_ip_axi_lite_module_inst_n_2;
  wire u_IncreEncoder_V24_ip_axi_lite_module_inst_n_20;
  wire u_IncreEncoder_V24_ip_axi_lite_module_inst_n_21;
  wire u_IncreEncoder_V24_ip_axi_lite_module_inst_n_22;
  wire u_IncreEncoder_V24_ip_axi_lite_module_inst_n_23;
  wire u_IncreEncoder_V24_ip_axi_lite_module_inst_n_24;
  wire u_IncreEncoder_V24_ip_axi_lite_module_inst_n_25;
  wire u_IncreEncoder_V24_ip_axi_lite_module_inst_n_26;
  wire u_IncreEncoder_V24_ip_axi_lite_module_inst_n_27;
  wire u_IncreEncoder_V24_ip_axi_lite_module_inst_n_28;
  wire u_IncreEncoder_V24_ip_axi_lite_module_inst_n_29;
  wire u_IncreEncoder_V24_ip_axi_lite_module_inst_n_3;
  wire u_IncreEncoder_V24_ip_axi_lite_module_inst_n_30;
  wire u_IncreEncoder_V24_ip_axi_lite_module_inst_n_31;
  wire u_IncreEncoder_V24_ip_axi_lite_module_inst_n_32;
  wire u_IncreEncoder_V24_ip_axi_lite_module_inst_n_4;
  wire u_IncreEncoder_V24_ip_axi_lite_module_inst_n_44;
  wire u_IncreEncoder_V24_ip_axi_lite_module_inst_n_45;
  wire u_IncreEncoder_V24_ip_axi_lite_module_inst_n_5;
  wire u_IncreEncoder_V24_ip_axi_lite_module_inst_n_6;
  wire u_IncreEncoder_V24_ip_axi_lite_module_inst_n_7;
  wire u_IncreEncoder_V24_ip_axi_lite_module_inst_n_8;
  wire u_IncreEncoder_V24_ip_axi_lite_module_inst_n_9;
  wire write_axi_enable;
  wire [15:0]\write_reg_IncPerTurn_elek_AXI4_reg[15] ;
  wire [15:0]\write_reg_IncPerTurn_mech_AXI4_reg[15] ;
  wire [23:0]\write_reg_OmegaPerOverSampl_AXI4_reg[23] ;
  wire [23:0]\write_reg_PI2_Inc_AXI4_reg[23] ;
  wire [31:0]\write_reg_Timer_FPGA_ms_AXI4_reg[31] ;

  zusys_IncreEncoder_V24_ip_0_0_IncreEncoder_V24_ip_addr_decoder u_IncreEncoder_V24_ip_addr_decoder_inst
       (.AXI4_Lite_ACLK(AXI4_Lite_ACLK),
        .AXI4_Lite_ARADDR({AXI4_Lite_ARADDR[6],AXI4_Lite_ARADDR[3:2],AXI4_Lite_ARADDR[0]}),
        .\AXI4_Lite_ARADDR[4] (u_IncreEncoder_V24_ip_addr_decoder_inst_n_4),
        .AXI4_Lite_ARADDR_2_sp_1(u_IncreEncoder_V24_ip_addr_decoder_inst_n_3),
        .\AXI4_Lite_RDATA_tmp[13]_i_2 (u_IncreEncoder_V24_ip_axi_lite_module_inst_n_44),
        .D(D),
        .E(reg_enb_Timer_FPGA_ms_AXI4),
        .Q({read_reg_direction_AXI4[3],read_reg_direction_AXI4[0]}),
        .SR(RSTP),
        .phase_0(phase_0),
        .phase_0_reg(phase_0_reg),
        .position(position),
        .\read_reg_countPerPeriod_AXI4_reg[15]_0 (read_reg_countPerPeriod_AXI4),
        .\read_reg_countPerPeriod_AXI4_reg[15]_1 (\read_reg_countPerPeriod_AXI4_reg[15] ),
        .read_reg_ip_timestamp(read_reg_ip_timestamp),
        .\read_reg_omega_AXI4_reg[23]_0 (read_reg_omega_AXI4),
        .\read_reg_position_AXI4_reg[15]_0 (read_reg_position_AXI4),
        .\read_reg_theta_el_AXI4_reg[23]_0 (read_reg_theta_el_AXI4),
        .reset_old5_out1(reset_old5_out1),
        .theta_el(theta_el),
        .write_axi_enable(write_axi_enable),
        .\write_reg_IncPerTurn_elek_AXI4_reg[15]_0 (\write_reg_IncPerTurn_elek_AXI4_reg[15] ),
        .\write_reg_IncPerTurn_elek_AXI4_reg[15]_1 (reg_enb_IncPerTurn_elek_AXI4),
        .\write_reg_IncPerTurn_mech_AXI4_reg[15]_0 (\write_reg_IncPerTurn_mech_AXI4_reg[15] ),
        .\write_reg_IncPerTurn_mech_AXI4_reg[15]_1 (reg_enb_IncPerTurn_mech_AXI4),
        .\write_reg_OmegaPerOverSampl_AXI4_reg[23]_0 (\write_reg_OmegaPerOverSampl_AXI4_reg[23] ),
        .\write_reg_OmegaPerOverSampl_AXI4_reg[23]_1 (reg_enb_OmegaPerOverSampl_AXI4),
        .\write_reg_PI2_Inc_AXI4_reg[23]_0 (\write_reg_PI2_Inc_AXI4_reg[23] ),
        .\write_reg_PI2_Inc_AXI4_reg[23]_1 (reg_enb_PI2_Inc_AXI4),
        .\write_reg_Timer_FPGA_ms_AXI4_reg[31]_0 (\write_reg_Timer_FPGA_ms_AXI4_reg[31] ),
        .\write_reg_Timer_FPGA_ms_AXI4_reg[31]_1 ({u_IncreEncoder_V24_ip_axi_lite_module_inst_n_1,u_IncreEncoder_V24_ip_axi_lite_module_inst_n_2,u_IncreEncoder_V24_ip_axi_lite_module_inst_n_3,u_IncreEncoder_V24_ip_axi_lite_module_inst_n_4,u_IncreEncoder_V24_ip_axi_lite_module_inst_n_5,u_IncreEncoder_V24_ip_axi_lite_module_inst_n_6,u_IncreEncoder_V24_ip_axi_lite_module_inst_n_7,u_IncreEncoder_V24_ip_axi_lite_module_inst_n_8,u_IncreEncoder_V24_ip_axi_lite_module_inst_n_9,u_IncreEncoder_V24_ip_axi_lite_module_inst_n_10,u_IncreEncoder_V24_ip_axi_lite_module_inst_n_11,u_IncreEncoder_V24_ip_axi_lite_module_inst_n_12,u_IncreEncoder_V24_ip_axi_lite_module_inst_n_13,u_IncreEncoder_V24_ip_axi_lite_module_inst_n_14,u_IncreEncoder_V24_ip_axi_lite_module_inst_n_15,u_IncreEncoder_V24_ip_axi_lite_module_inst_n_16,u_IncreEncoder_V24_ip_axi_lite_module_inst_n_17,u_IncreEncoder_V24_ip_axi_lite_module_inst_n_18,u_IncreEncoder_V24_ip_axi_lite_module_inst_n_19,u_IncreEncoder_V24_ip_axi_lite_module_inst_n_20,u_IncreEncoder_V24_ip_axi_lite_module_inst_n_21,u_IncreEncoder_V24_ip_axi_lite_module_inst_n_22,u_IncreEncoder_V24_ip_axi_lite_module_inst_n_23,u_IncreEncoder_V24_ip_axi_lite_module_inst_n_24,u_IncreEncoder_V24_ip_axi_lite_module_inst_n_25,u_IncreEncoder_V24_ip_axi_lite_module_inst_n_26,u_IncreEncoder_V24_ip_axi_lite_module_inst_n_27,u_IncreEncoder_V24_ip_axi_lite_module_inst_n_28,u_IncreEncoder_V24_ip_axi_lite_module_inst_n_29,u_IncreEncoder_V24_ip_axi_lite_module_inst_n_30,u_IncreEncoder_V24_ip_axi_lite_module_inst_n_31,u_IncreEncoder_V24_ip_axi_lite_module_inst_n_32}),
        .write_reg_axi_enable_reg_0(u_IncreEncoder_V24_ip_axi_lite_module_inst_n_45));
  zusys_IncreEncoder_V24_ip_0_0_IncreEncoder_V24_ip_axi_lite_module u_IncreEncoder_V24_ip_axi_lite_module_inst
       (.AXI4_Lite_ACLK(AXI4_Lite_ACLK),
        .AXI4_Lite_ARADDR(AXI4_Lite_ARADDR),
        .\AXI4_Lite_ARADDR[3] (reg_enb_IncPerTurn_elek_AXI4),
        .\AXI4_Lite_ARADDR[3]_0 (reg_enb_IncPerTurn_mech_AXI4),
        .\AXI4_Lite_ARADDR[3]_1 (u_IncreEncoder_V24_ip_axi_lite_module_inst_n_44),
        .\AXI4_Lite_ARADDR[5] (reg_enb_OmegaPerOverSampl_AXI4),
        .\AXI4_Lite_ARADDR[5]_0 (reg_enb_PI2_Inc_AXI4),
        .AXI4_Lite_ARESETN(AXI4_Lite_ARESETN),
        .AXI4_Lite_ARREADY(AXI4_Lite_ARREADY),
        .AXI4_Lite_ARVALID(AXI4_Lite_ARVALID),
        .AXI4_Lite_AWADDR(AXI4_Lite_AWADDR),
        .AXI4_Lite_AWREADY(AXI4_Lite_AWREADY),
        .AXI4_Lite_AWVALID(AXI4_Lite_AWVALID),
        .AXI4_Lite_BREADY(AXI4_Lite_BREADY),
        .AXI4_Lite_RDATA(AXI4_Lite_RDATA),
        .\AXI4_Lite_RDATA_tmp_reg[13]_0 (u_IncreEncoder_V24_ip_addr_decoder_inst_n_4),
        .\AXI4_Lite_RDATA_tmp_reg[15]_0 (read_reg_position_AXI4),
        .\AXI4_Lite_RDATA_tmp_reg[30]_0 (read_reg_countPerPeriod_AXI4),
        .\AXI4_Lite_RDATA_tmp_reg[30]_1 (read_reg_omega_AXI4),
        .\AXI4_Lite_RDATA_tmp_reg[30]_2 (read_reg_theta_el_AXI4),
        .AXI4_Lite_RREADY(AXI4_Lite_RREADY),
        .AXI4_Lite_WDATA(AXI4_Lite_WDATA),
        .AXI4_Lite_WSTRB(AXI4_Lite_WSTRB),
        .AXI4_Lite_WVALID(AXI4_Lite_WVALID),
        .E(reg_enb_Timer_FPGA_ms_AXI4),
        .\FSM_onehot_axi_lite_wstate_reg[2]_0 (Q),
        .FSM_sequential_axi_lite_rstate_reg_0(FSM_sequential_axi_lite_rstate_reg),
        .IPCORE_RESETN(IPCORE_RESETN),
        .Q({read_reg_direction_AXI4[3],read_reg_direction_AXI4[0]}),
        .RSTP(RSTP),
        .p_1_in(p_1_in),
        .read_reg_ip_timestamp(read_reg_ip_timestamp),
        .\wdata_reg[0]_0 (u_IncreEncoder_V24_ip_axi_lite_module_inst_n_45),
        .\wdata_reg[31]_0 ({u_IncreEncoder_V24_ip_axi_lite_module_inst_n_1,u_IncreEncoder_V24_ip_axi_lite_module_inst_n_2,u_IncreEncoder_V24_ip_axi_lite_module_inst_n_3,u_IncreEncoder_V24_ip_axi_lite_module_inst_n_4,u_IncreEncoder_V24_ip_axi_lite_module_inst_n_5,u_IncreEncoder_V24_ip_axi_lite_module_inst_n_6,u_IncreEncoder_V24_ip_axi_lite_module_inst_n_7,u_IncreEncoder_V24_ip_axi_lite_module_inst_n_8,u_IncreEncoder_V24_ip_axi_lite_module_inst_n_9,u_IncreEncoder_V24_ip_axi_lite_module_inst_n_10,u_IncreEncoder_V24_ip_axi_lite_module_inst_n_11,u_IncreEncoder_V24_ip_axi_lite_module_inst_n_12,u_IncreEncoder_V24_ip_axi_lite_module_inst_n_13,u_IncreEncoder_V24_ip_axi_lite_module_inst_n_14,u_IncreEncoder_V24_ip_axi_lite_module_inst_n_15,u_IncreEncoder_V24_ip_axi_lite_module_inst_n_16,u_IncreEncoder_V24_ip_axi_lite_module_inst_n_17,u_IncreEncoder_V24_ip_axi_lite_module_inst_n_18,u_IncreEncoder_V24_ip_axi_lite_module_inst_n_19,u_IncreEncoder_V24_ip_axi_lite_module_inst_n_20,u_IncreEncoder_V24_ip_axi_lite_module_inst_n_21,u_IncreEncoder_V24_ip_axi_lite_module_inst_n_22,u_IncreEncoder_V24_ip_axi_lite_module_inst_n_23,u_IncreEncoder_V24_ip_axi_lite_module_inst_n_24,u_IncreEncoder_V24_ip_axi_lite_module_inst_n_25,u_IncreEncoder_V24_ip_axi_lite_module_inst_n_26,u_IncreEncoder_V24_ip_axi_lite_module_inst_n_27,u_IncreEncoder_V24_ip_axi_lite_module_inst_n_28,u_IncreEncoder_V24_ip_axi_lite_module_inst_n_29,u_IncreEncoder_V24_ip_axi_lite_module_inst_n_30,u_IncreEncoder_V24_ip_axi_lite_module_inst_n_31,u_IncreEncoder_V24_ip_axi_lite_module_inst_n_32}),
        .write_axi_enable(write_axi_enable),
        .\write_reg_IncPerTurn_elek_AXI4_reg[15] (u_IncreEncoder_V24_ip_addr_decoder_inst_n_3));
endmodule

(* ORIG_REF_NAME = "IncreEncoder_V24_ip_axi_lite_module" *) 
module zusys_IncreEncoder_V24_ip_0_0_IncreEncoder_V24_ip_axi_lite_module
   (FSM_sequential_axi_lite_rstate_reg_0,
    \wdata_reg[31]_0 ,
    \AXI4_Lite_ARADDR[5] ,
    \AXI4_Lite_ARADDR[3] ,
    \AXI4_Lite_ARADDR[3]_0 ,
    \AXI4_Lite_ARADDR[5]_0 ,
    E,
    AXI4_Lite_ARREADY,
    \FSM_onehot_axi_lite_wstate_reg[2]_0 ,
    AXI4_Lite_AWREADY,
    p_1_in,
    RSTP,
    \AXI4_Lite_ARADDR[3]_1 ,
    \wdata_reg[0]_0 ,
    AXI4_Lite_RDATA,
    AXI4_Lite_ACLK,
    Q,
    \AXI4_Lite_RDATA_tmp_reg[30]_0 ,
    AXI4_Lite_ARESETN,
    \AXI4_Lite_RDATA_tmp_reg[30]_1 ,
    \AXI4_Lite_RDATA_tmp_reg[30]_2 ,
    \AXI4_Lite_RDATA_tmp_reg[13]_0 ,
    \AXI4_Lite_RDATA_tmp_reg[15]_0 ,
    AXI4_Lite_ARADDR,
    \write_reg_IncPerTurn_elek_AXI4_reg[15] ,
    AXI4_Lite_ARVALID,
    AXI4_Lite_RREADY,
    AXI4_Lite_AWVALID,
    AXI4_Lite_WVALID,
    IPCORE_RESETN,
    AXI4_Lite_BREADY,
    AXI4_Lite_WSTRB,
    read_reg_ip_timestamp,
    write_axi_enable,
    AXI4_Lite_AWADDR,
    AXI4_Lite_WDATA);
  output FSM_sequential_axi_lite_rstate_reg_0;
  output [31:0]\wdata_reg[31]_0 ;
  output [0:0]\AXI4_Lite_ARADDR[5] ;
  output [0:0]\AXI4_Lite_ARADDR[3] ;
  output [0:0]\AXI4_Lite_ARADDR[3]_0 ;
  output [0:0]\AXI4_Lite_ARADDR[5]_0 ;
  output [0:0]E;
  output AXI4_Lite_ARREADY;
  output [1:0]\FSM_onehot_axi_lite_wstate_reg[2]_0 ;
  output AXI4_Lite_AWREADY;
  output [0:0]p_1_in;
  output RSTP;
  output \AXI4_Lite_ARADDR[3]_1 ;
  output \wdata_reg[0]_0 ;
  output [24:0]AXI4_Lite_RDATA;
  input AXI4_Lite_ACLK;
  input [1:0]Q;
  input [15:0]\AXI4_Lite_RDATA_tmp_reg[30]_0 ;
  input AXI4_Lite_ARESETN;
  input [23:0]\AXI4_Lite_RDATA_tmp_reg[30]_1 ;
  input [23:0]\AXI4_Lite_RDATA_tmp_reg[30]_2 ;
  input \AXI4_Lite_RDATA_tmp_reg[13]_0 ;
  input [15:0]\AXI4_Lite_RDATA_tmp_reg[15]_0 ;
  input [13:0]AXI4_Lite_ARADDR;
  input \write_reg_IncPerTurn_elek_AXI4_reg[15] ;
  input AXI4_Lite_ARVALID;
  input AXI4_Lite_RREADY;
  input AXI4_Lite_AWVALID;
  input AXI4_Lite_WVALID;
  input IPCORE_RESETN;
  input AXI4_Lite_BREADY;
  input [3:0]AXI4_Lite_WSTRB;
  input [0:0]read_reg_ip_timestamp;
  input write_axi_enable;
  input [13:0]AXI4_Lite_AWADDR;
  input [31:0]AXI4_Lite_WDATA;

  wire AXI4_Lite_ACLK;
  wire [13:0]AXI4_Lite_ARADDR;
  wire [0:0]\AXI4_Lite_ARADDR[3] ;
  wire [0:0]\AXI4_Lite_ARADDR[3]_0 ;
  wire \AXI4_Lite_ARADDR[3]_1 ;
  wire [0:0]\AXI4_Lite_ARADDR[5] ;
  wire [0:0]\AXI4_Lite_ARADDR[5]_0 ;
  wire AXI4_Lite_ARESETN;
  wire AXI4_Lite_ARREADY;
  wire AXI4_Lite_ARVALID;
  wire [13:0]AXI4_Lite_AWADDR;
  wire AXI4_Lite_AWREADY;
  wire AXI4_Lite_AWVALID;
  wire AXI4_Lite_BREADY;
  wire [24:0]AXI4_Lite_RDATA;
  wire \AXI4_Lite_RDATA_tmp[0]_i_2_n_0 ;
  wire \AXI4_Lite_RDATA_tmp[0]_i_3_n_0 ;
  wire \AXI4_Lite_RDATA_tmp[0]_i_4_n_0 ;
  wire \AXI4_Lite_RDATA_tmp[10]_i_2_n_0 ;
  wire \AXI4_Lite_RDATA_tmp[11]_i_2_n_0 ;
  wire \AXI4_Lite_RDATA_tmp[12]_i_2_n_0 ;
  wire \AXI4_Lite_RDATA_tmp[13]_i_2_n_0 ;
  wire \AXI4_Lite_RDATA_tmp[13]_i_3_n_0 ;
  wire \AXI4_Lite_RDATA_tmp[13]_i_5_n_0 ;
  wire \AXI4_Lite_RDATA_tmp[14]_i_2_n_0 ;
  wire \AXI4_Lite_RDATA_tmp[14]_i_3_n_0 ;
  wire \AXI4_Lite_RDATA_tmp[14]_i_4_n_0 ;
  wire \AXI4_Lite_RDATA_tmp[14]_i_5_n_0 ;
  wire \AXI4_Lite_RDATA_tmp[14]_i_6_n_0 ;
  wire \AXI4_Lite_RDATA_tmp[15]_i_2_n_0 ;
  wire \AXI4_Lite_RDATA_tmp[1]_i_2_n_0 ;
  wire \AXI4_Lite_RDATA_tmp[2]_i_2_n_0 ;
  wire \AXI4_Lite_RDATA_tmp[30]_i_2_n_0 ;
  wire \AXI4_Lite_RDATA_tmp[31]_i_3_n_0 ;
  wire \AXI4_Lite_RDATA_tmp[31]_i_4_n_0 ;
  wire \AXI4_Lite_RDATA_tmp[31]_i_5_n_0 ;
  wire \AXI4_Lite_RDATA_tmp[31]_i_6_n_0 ;
  wire \AXI4_Lite_RDATA_tmp[31]_i_7_n_0 ;
  wire \AXI4_Lite_RDATA_tmp[3]_i_2_n_0 ;
  wire \AXI4_Lite_RDATA_tmp[4]_i_2_n_0 ;
  wire \AXI4_Lite_RDATA_tmp[5]_i_2_n_0 ;
  wire \AXI4_Lite_RDATA_tmp[6]_i_2_n_0 ;
  wire \AXI4_Lite_RDATA_tmp[7]_i_2_n_0 ;
  wire \AXI4_Lite_RDATA_tmp[8]_i_2_n_0 ;
  wire \AXI4_Lite_RDATA_tmp[9]_i_2_n_0 ;
  wire \AXI4_Lite_RDATA_tmp_reg[13]_0 ;
  wire [15:0]\AXI4_Lite_RDATA_tmp_reg[15]_0 ;
  wire [15:0]\AXI4_Lite_RDATA_tmp_reg[30]_0 ;
  wire [23:0]\AXI4_Lite_RDATA_tmp_reg[30]_1 ;
  wire [23:0]\AXI4_Lite_RDATA_tmp_reg[30]_2 ;
  wire AXI4_Lite_RREADY;
  wire [31:0]AXI4_Lite_WDATA;
  wire [3:0]AXI4_Lite_WSTRB;
  wire AXI4_Lite_WVALID;
  wire [0:0]E;
  wire [1:0]\FSM_onehot_axi_lite_wstate_reg[2]_0 ;
  wire \FSM_onehot_axi_lite_wstate_reg_n_0_[0] ;
  wire FSM_sequential_axi_lite_rstate_reg_0;
  wire IPCORE_RESETN;
  wire [1:0]Q;
  wire RSTP;
  wire aw_transfer;
  wire axi_lite_rstate_next;
  wire [2:0]axi_lite_wstate_next;
  wire [31:0]data_read;
  wire [0:0]p_1_in;
  wire [0:0]read_reg_ip_timestamp;
  wire reset;
  wire [13:0]sel0;
  wire soft_reset;
  wire soft_reset_i_1_n_0;
  wire soft_reset_i_2_n_0;
  wire soft_reset_i_3_n_0;
  wire soft_reset_i_4_n_0;
  wire top_rd_enb;
  wire top_wr_enb;
  wire w_transfer;
  wire w_transfer_and_wstrb;
  wire \wdata_reg[0]_0 ;
  wire [31:0]\wdata_reg[31]_0 ;
  wire write_axi_enable;
  wire \write_reg_IncPerTurn_elek_AXI4[15]_i_2_n_0 ;
  wire \write_reg_IncPerTurn_elek_AXI4[15]_i_3_n_0 ;
  wire \write_reg_IncPerTurn_elek_AXI4_reg[15] ;
  wire \write_reg_IncPerTurn_mech_AXI4[15]_i_2_n_0 ;
  wire \write_reg_OmegaPerOverSampl_AXI4[23]_i_2_n_0 ;
  wire \write_reg_PI2_Inc_AXI4[23]_i_2_n_0 ;
  wire \write_reg_Timer_FPGA_ms_AXI4[31]_i_2_n_0 ;
  wire \write_reg_Timer_FPGA_ms_AXI4[31]_i_4_n_0 ;
  wire \write_reg_Timer_FPGA_ms_AXI4[31]_i_5_n_0 ;
  wire \write_reg_Timer_FPGA_ms_AXI4[31]_i_6_n_0 ;
  wire write_reg_axi_enable_i_2_n_0;
  wire write_reg_axi_enable_i_3_n_0;
  wire write_reg_axi_enable_i_4_n_0;
  wire write_reg_axi_enable_i_5_n_0;
  wire write_reg_axi_enable_i_6_n_0;
  wire write_reg_axi_enable_i_7_n_0;

  (* SOFT_HLUTNM = "soft_lutpair4" *) 
  LUT3 #(
    .INIT(8'h04)) 
    AXI4_Lite_ARREADY_INST_0
       (.I0(FSM_sequential_axi_lite_rstate_reg_0),
        .I1(\FSM_onehot_axi_lite_wstate_reg_n_0_[0] ),
        .I2(AXI4_Lite_AWVALID),
        .O(AXI4_Lite_ARREADY));
  (* SOFT_HLUTNM = "soft_lutpair5" *) 
  LUT2 #(
    .INIT(4'h2)) 
    AXI4_Lite_AWREADY_INST_0
       (.I0(\FSM_onehot_axi_lite_wstate_reg_n_0_[0] ),
        .I1(FSM_sequential_axi_lite_rstate_reg_0),
        .O(AXI4_Lite_AWREADY));
  LUT5 #(
    .INIT(32'hFFEAEAEA)) 
    \AXI4_Lite_RDATA_tmp[0]_i_1 
       (.I0(\AXI4_Lite_RDATA_tmp[0]_i_2_n_0 ),
        .I1(\AXI4_Lite_RDATA_tmp[0]_i_3_n_0 ),
        .I2(\AXI4_Lite_RDATA_tmp_reg[15]_0 [0]),
        .I3(\AXI4_Lite_RDATA_tmp_reg[30]_0 [0]),
        .I4(\AXI4_Lite_RDATA_tmp[14]_i_3_n_0 ),
        .O(data_read[0]));
  LUT6 #(
    .INIT(64'hFFFFF888F888F888)) 
    \AXI4_Lite_RDATA_tmp[0]_i_2 
       (.I0(\AXI4_Lite_RDATA_tmp[31]_i_3_n_0 ),
        .I1(\AXI4_Lite_RDATA_tmp_reg[30]_1 [0]),
        .I2(\AXI4_Lite_RDATA_tmp[14]_i_2_n_0 ),
        .I3(Q[0]),
        .I4(\AXI4_Lite_RDATA_tmp_reg[30]_2 [0]),
        .I5(\AXI4_Lite_RDATA_tmp[31]_i_4_n_0 ),
        .O(\AXI4_Lite_RDATA_tmp[0]_i_2_n_0 ));
  LUT6 #(
    .INIT(64'hAAAAAEAAAAAAAAAA)) 
    \AXI4_Lite_RDATA_tmp[0]_i_3 
       (.I0(\AXI4_Lite_RDATA_tmp[0]_i_4_n_0 ),
        .I1(\write_reg_Timer_FPGA_ms_AXI4[31]_i_4_n_0 ),
        .I2(sel0[1]),
        .I3(sel0[0]),
        .I4(sel0[2]),
        .I5(sel0[3]),
        .O(\AXI4_Lite_RDATA_tmp[0]_i_3_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair1" *) 
  LUT5 #(
    .INIT(32'h00200000)) 
    \AXI4_Lite_RDATA_tmp[0]_i_4 
       (.I0(AXI4_Lite_ARADDR[3]),
        .I1(AXI4_Lite_ARADDR[2]),
        .I2(AXI4_Lite_ARADDR[0]),
        .I3(AXI4_Lite_ARADDR[1]),
        .I4(\write_reg_IncPerTurn_elek_AXI4[15]_i_2_n_0 ),
        .O(\AXI4_Lite_RDATA_tmp[0]_i_4_n_0 ));
  LUT5 #(
    .INIT(32'hFFFFF888)) 
    \AXI4_Lite_RDATA_tmp[10]_i_1 
       (.I0(\AXI4_Lite_RDATA_tmp[14]_i_2_n_0 ),
        .I1(Q[1]),
        .I2(\AXI4_Lite_RDATA_tmp[14]_i_3_n_0 ),
        .I3(\AXI4_Lite_RDATA_tmp_reg[30]_0 [10]),
        .I4(\AXI4_Lite_RDATA_tmp[10]_i_2_n_0 ),
        .O(data_read[10]));
  LUT6 #(
    .INIT(64'hFFFFF888F888F888)) 
    \AXI4_Lite_RDATA_tmp[10]_i_2 
       (.I0(\AXI4_Lite_RDATA_tmp[31]_i_3_n_0 ),
        .I1(\AXI4_Lite_RDATA_tmp_reg[30]_1 [10]),
        .I2(\AXI4_Lite_RDATA_tmp[31]_i_4_n_0 ),
        .I3(\AXI4_Lite_RDATA_tmp_reg[30]_2 [10]),
        .I4(\AXI4_Lite_RDATA_tmp_reg[15]_0 [10]),
        .I5(\AXI4_Lite_RDATA_tmp[0]_i_3_n_0 ),
        .O(\AXI4_Lite_RDATA_tmp[10]_i_2_n_0 ));
  LUT5 #(
    .INIT(32'hFFFFF888)) 
    \AXI4_Lite_RDATA_tmp[11]_i_1 
       (.I0(\AXI4_Lite_RDATA_tmp[14]_i_2_n_0 ),
        .I1(Q[1]),
        .I2(\AXI4_Lite_RDATA_tmp[14]_i_3_n_0 ),
        .I3(\AXI4_Lite_RDATA_tmp_reg[30]_0 [11]),
        .I4(\AXI4_Lite_RDATA_tmp[11]_i_2_n_0 ),
        .O(data_read[11]));
  LUT6 #(
    .INIT(64'hFFFFF888F888F888)) 
    \AXI4_Lite_RDATA_tmp[11]_i_2 
       (.I0(\AXI4_Lite_RDATA_tmp[31]_i_3_n_0 ),
        .I1(\AXI4_Lite_RDATA_tmp_reg[30]_1 [11]),
        .I2(\AXI4_Lite_RDATA_tmp[31]_i_4_n_0 ),
        .I3(\AXI4_Lite_RDATA_tmp_reg[30]_2 [11]),
        .I4(\AXI4_Lite_RDATA_tmp_reg[15]_0 [11]),
        .I5(\AXI4_Lite_RDATA_tmp[0]_i_3_n_0 ),
        .O(\AXI4_Lite_RDATA_tmp[11]_i_2_n_0 ));
  LUT5 #(
    .INIT(32'hFFFFF888)) 
    \AXI4_Lite_RDATA_tmp[12]_i_1 
       (.I0(\AXI4_Lite_RDATA_tmp[14]_i_2_n_0 ),
        .I1(Q[1]),
        .I2(\AXI4_Lite_RDATA_tmp[14]_i_3_n_0 ),
        .I3(\AXI4_Lite_RDATA_tmp_reg[30]_0 [12]),
        .I4(\AXI4_Lite_RDATA_tmp[12]_i_2_n_0 ),
        .O(data_read[12]));
  LUT6 #(
    .INIT(64'hFFFFF888F888F888)) 
    \AXI4_Lite_RDATA_tmp[12]_i_2 
       (.I0(\AXI4_Lite_RDATA_tmp[31]_i_3_n_0 ),
        .I1(\AXI4_Lite_RDATA_tmp_reg[30]_1 [12]),
        .I2(\AXI4_Lite_RDATA_tmp[31]_i_4_n_0 ),
        .I3(\AXI4_Lite_RDATA_tmp_reg[30]_2 [12]),
        .I4(\AXI4_Lite_RDATA_tmp_reg[15]_0 [12]),
        .I5(\AXI4_Lite_RDATA_tmp[0]_i_3_n_0 ),
        .O(\AXI4_Lite_RDATA_tmp[12]_i_2_n_0 ));
  LUT4 #(
    .INIT(16'hFFEA)) 
    \AXI4_Lite_RDATA_tmp[13]_i_1 
       (.I0(\AXI4_Lite_RDATA_tmp[13]_i_2_n_0 ),
        .I1(\AXI4_Lite_RDATA_tmp[14]_i_3_n_0 ),
        .I2(\AXI4_Lite_RDATA_tmp_reg[30]_0 [13]),
        .I3(\AXI4_Lite_RDATA_tmp[13]_i_3_n_0 ),
        .O(data_read[13]));
  LUT6 #(
    .INIT(64'h88F8888888888888)) 
    \AXI4_Lite_RDATA_tmp[13]_i_2 
       (.I0(write_reg_axi_enable_i_2_n_0),
        .I1(\AXI4_Lite_RDATA_tmp_reg[13]_0 ),
        .I2(write_reg_axi_enable_i_4_n_0),
        .I3(sel0[3]),
        .I4(sel0[1]),
        .I5(\AXI4_Lite_RDATA_tmp[13]_i_5_n_0 ),
        .O(\AXI4_Lite_RDATA_tmp[13]_i_2_n_0 ));
  LUT6 #(
    .INIT(64'hFFFFF888F888F888)) 
    \AXI4_Lite_RDATA_tmp[13]_i_3 
       (.I0(\AXI4_Lite_RDATA_tmp[31]_i_3_n_0 ),
        .I1(\AXI4_Lite_RDATA_tmp_reg[30]_1 [13]),
        .I2(\AXI4_Lite_RDATA_tmp[31]_i_4_n_0 ),
        .I3(\AXI4_Lite_RDATA_tmp_reg[30]_2 [13]),
        .I4(\AXI4_Lite_RDATA_tmp_reg[15]_0 [13]),
        .I5(\AXI4_Lite_RDATA_tmp[0]_i_3_n_0 ),
        .O(\AXI4_Lite_RDATA_tmp[13]_i_3_n_0 ));
  LUT5 #(
    .INIT(32'hA000000C)) 
    \AXI4_Lite_RDATA_tmp[13]_i_5 
       (.I0(Q[1]),
        .I1(read_reg_ip_timestamp),
        .I2(sel0[6]),
        .I3(sel0[0]),
        .I4(sel0[2]),
        .O(\AXI4_Lite_RDATA_tmp[13]_i_5_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair3" *) 
  LUT2 #(
    .INIT(4'h2)) 
    \AXI4_Lite_RDATA_tmp[13]_i_6 
       (.I0(AXI4_Lite_ARADDR[1]),
        .I1(AXI4_Lite_ARADDR[3]),
        .O(\AXI4_Lite_ARADDR[3]_1 ));
  LUT5 #(
    .INIT(32'hFFFFF888)) 
    \AXI4_Lite_RDATA_tmp[14]_i_1 
       (.I0(\AXI4_Lite_RDATA_tmp[14]_i_2_n_0 ),
        .I1(Q[1]),
        .I2(\AXI4_Lite_RDATA_tmp[14]_i_3_n_0 ),
        .I3(\AXI4_Lite_RDATA_tmp_reg[30]_0 [14]),
        .I4(\AXI4_Lite_RDATA_tmp[14]_i_4_n_0 ),
        .O(data_read[14]));
  LUT6 #(
    .INIT(64'hAAAAEAAAAAAAAAAA)) 
    \AXI4_Lite_RDATA_tmp[14]_i_2 
       (.I0(\AXI4_Lite_RDATA_tmp[14]_i_5_n_0 ),
        .I1(\write_reg_Timer_FPGA_ms_AXI4[31]_i_4_n_0 ),
        .I2(sel0[1]),
        .I3(sel0[0]),
        .I4(sel0[3]),
        .I5(sel0[2]),
        .O(\AXI4_Lite_RDATA_tmp[14]_i_2_n_0 ));
  LUT6 #(
    .INIT(64'hAAAAEAAAAAAAAAAA)) 
    \AXI4_Lite_RDATA_tmp[14]_i_3 
       (.I0(\AXI4_Lite_RDATA_tmp[14]_i_6_n_0 ),
        .I1(\write_reg_Timer_FPGA_ms_AXI4[31]_i_4_n_0 ),
        .I2(sel0[1]),
        .I3(sel0[0]),
        .I4(sel0[2]),
        .I5(sel0[3]),
        .O(\AXI4_Lite_RDATA_tmp[14]_i_3_n_0 ));
  LUT6 #(
    .INIT(64'hFFFFF888F888F888)) 
    \AXI4_Lite_RDATA_tmp[14]_i_4 
       (.I0(\AXI4_Lite_RDATA_tmp[31]_i_3_n_0 ),
        .I1(\AXI4_Lite_RDATA_tmp_reg[30]_1 [14]),
        .I2(\AXI4_Lite_RDATA_tmp[31]_i_4_n_0 ),
        .I3(\AXI4_Lite_RDATA_tmp_reg[30]_2 [14]),
        .I4(\AXI4_Lite_RDATA_tmp_reg[15]_0 [14]),
        .I5(\AXI4_Lite_RDATA_tmp[0]_i_3_n_0 ),
        .O(\AXI4_Lite_RDATA_tmp[14]_i_4_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair3" *) 
  LUT5 #(
    .INIT(32'h20000000)) 
    \AXI4_Lite_RDATA_tmp[14]_i_5 
       (.I0(AXI4_Lite_ARADDR[2]),
        .I1(AXI4_Lite_ARADDR[3]),
        .I2(AXI4_Lite_ARADDR[0]),
        .I3(AXI4_Lite_ARADDR[1]),
        .I4(\write_reg_IncPerTurn_elek_AXI4[15]_i_2_n_0 ),
        .O(\AXI4_Lite_RDATA_tmp[14]_i_5_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair2" *) 
  LUT5 #(
    .INIT(32'h20000000)) 
    \AXI4_Lite_RDATA_tmp[14]_i_6 
       (.I0(AXI4_Lite_ARADDR[3]),
        .I1(AXI4_Lite_ARADDR[2]),
        .I2(AXI4_Lite_ARADDR[0]),
        .I3(AXI4_Lite_ARADDR[1]),
        .I4(\write_reg_IncPerTurn_elek_AXI4[15]_i_2_n_0 ),
        .O(\AXI4_Lite_RDATA_tmp[14]_i_6_n_0 ));
  LUT2 #(
    .INIT(4'hE)) 
    \AXI4_Lite_RDATA_tmp[15]_i_1 
       (.I0(\AXI4_Lite_RDATA_tmp[15]_i_2_n_0 ),
        .I1(\AXI4_Lite_RDATA_tmp[31]_i_5_n_0 ),
        .O(data_read[15]));
  LUT6 #(
    .INIT(64'hFFFFF888F888F888)) 
    \AXI4_Lite_RDATA_tmp[15]_i_2 
       (.I0(\AXI4_Lite_RDATA_tmp[31]_i_3_n_0 ),
        .I1(\AXI4_Lite_RDATA_tmp_reg[30]_1 [15]),
        .I2(\AXI4_Lite_RDATA_tmp[31]_i_4_n_0 ),
        .I3(\AXI4_Lite_RDATA_tmp_reg[30]_2 [15]),
        .I4(\AXI4_Lite_RDATA_tmp_reg[15]_0 [15]),
        .I5(\AXI4_Lite_RDATA_tmp[0]_i_3_n_0 ),
        .O(\AXI4_Lite_RDATA_tmp[15]_i_2_n_0 ));
  LUT5 #(
    .INIT(32'hFFEAEAEA)) 
    \AXI4_Lite_RDATA_tmp[16]_i_1 
       (.I0(\AXI4_Lite_RDATA_tmp[30]_i_2_n_0 ),
        .I1(\AXI4_Lite_RDATA_tmp[31]_i_3_n_0 ),
        .I2(\AXI4_Lite_RDATA_tmp_reg[30]_1 [16]),
        .I3(\AXI4_Lite_RDATA_tmp_reg[30]_2 [16]),
        .I4(\AXI4_Lite_RDATA_tmp[31]_i_4_n_0 ),
        .O(data_read[16]));
  LUT5 #(
    .INIT(32'hFFEAEAEA)) 
    \AXI4_Lite_RDATA_tmp[17]_i_1 
       (.I0(\AXI4_Lite_RDATA_tmp[30]_i_2_n_0 ),
        .I1(\AXI4_Lite_RDATA_tmp[31]_i_3_n_0 ),
        .I2(\AXI4_Lite_RDATA_tmp_reg[30]_1 [17]),
        .I3(\AXI4_Lite_RDATA_tmp_reg[30]_2 [17]),
        .I4(\AXI4_Lite_RDATA_tmp[31]_i_4_n_0 ),
        .O(data_read[17]));
  LUT5 #(
    .INIT(32'hFFEAEAEA)) 
    \AXI4_Lite_RDATA_tmp[18]_i_1 
       (.I0(\AXI4_Lite_RDATA_tmp[31]_i_5_n_0 ),
        .I1(\AXI4_Lite_RDATA_tmp[31]_i_3_n_0 ),
        .I2(\AXI4_Lite_RDATA_tmp_reg[30]_1 [18]),
        .I3(\AXI4_Lite_RDATA_tmp_reg[30]_2 [18]),
        .I4(\AXI4_Lite_RDATA_tmp[31]_i_4_n_0 ),
        .O(data_read[18]));
  LUT5 #(
    .INIT(32'hFFEAEAEA)) 
    \AXI4_Lite_RDATA_tmp[19]_i_1 
       (.I0(\AXI4_Lite_RDATA_tmp[31]_i_5_n_0 ),
        .I1(\AXI4_Lite_RDATA_tmp[31]_i_3_n_0 ),
        .I2(\AXI4_Lite_RDATA_tmp_reg[30]_1 [19]),
        .I3(\AXI4_Lite_RDATA_tmp_reg[30]_2 [19]),
        .I4(\AXI4_Lite_RDATA_tmp[31]_i_4_n_0 ),
        .O(data_read[19]));
  LUT5 #(
    .INIT(32'hFFFFF888)) 
    \AXI4_Lite_RDATA_tmp[1]_i_1 
       (.I0(\AXI4_Lite_RDATA_tmp[14]_i_2_n_0 ),
        .I1(Q[1]),
        .I2(\AXI4_Lite_RDATA_tmp[14]_i_3_n_0 ),
        .I3(\AXI4_Lite_RDATA_tmp_reg[30]_0 [1]),
        .I4(\AXI4_Lite_RDATA_tmp[1]_i_2_n_0 ),
        .O(data_read[1]));
  LUT6 #(
    .INIT(64'hFFFFF888F888F888)) 
    \AXI4_Lite_RDATA_tmp[1]_i_2 
       (.I0(\AXI4_Lite_RDATA_tmp[31]_i_3_n_0 ),
        .I1(\AXI4_Lite_RDATA_tmp_reg[30]_1 [1]),
        .I2(\AXI4_Lite_RDATA_tmp[31]_i_4_n_0 ),
        .I3(\AXI4_Lite_RDATA_tmp_reg[30]_2 [1]),
        .I4(\AXI4_Lite_RDATA_tmp_reg[15]_0 [1]),
        .I5(\AXI4_Lite_RDATA_tmp[0]_i_3_n_0 ),
        .O(\AXI4_Lite_RDATA_tmp[1]_i_2_n_0 ));
  LUT5 #(
    .INIT(32'hFFEAEAEA)) 
    \AXI4_Lite_RDATA_tmp[20]_i_1 
       (.I0(\AXI4_Lite_RDATA_tmp[30]_i_2_n_0 ),
        .I1(\AXI4_Lite_RDATA_tmp[31]_i_3_n_0 ),
        .I2(\AXI4_Lite_RDATA_tmp_reg[30]_1 [20]),
        .I3(\AXI4_Lite_RDATA_tmp_reg[30]_2 [20]),
        .I4(\AXI4_Lite_RDATA_tmp[31]_i_4_n_0 ),
        .O(data_read[20]));
  LUT5 #(
    .INIT(32'hFFEAEAEA)) 
    \AXI4_Lite_RDATA_tmp[21]_i_1 
       (.I0(\AXI4_Lite_RDATA_tmp[31]_i_5_n_0 ),
        .I1(\AXI4_Lite_RDATA_tmp[31]_i_3_n_0 ),
        .I2(\AXI4_Lite_RDATA_tmp_reg[30]_1 [21]),
        .I3(\AXI4_Lite_RDATA_tmp_reg[30]_2 [21]),
        .I4(\AXI4_Lite_RDATA_tmp[31]_i_4_n_0 ),
        .O(data_read[21]));
  LUT5 #(
    .INIT(32'hFFEAEAEA)) 
    \AXI4_Lite_RDATA_tmp[22]_i_1 
       (.I0(\AXI4_Lite_RDATA_tmp[31]_i_5_n_0 ),
        .I1(\AXI4_Lite_RDATA_tmp[31]_i_3_n_0 ),
        .I2(\AXI4_Lite_RDATA_tmp_reg[30]_1 [22]),
        .I3(\AXI4_Lite_RDATA_tmp_reg[30]_2 [22]),
        .I4(\AXI4_Lite_RDATA_tmp[31]_i_4_n_0 ),
        .O(data_read[22]));
  LUT4 #(
    .INIT(16'hFFEA)) 
    \AXI4_Lite_RDATA_tmp[2]_i_1 
       (.I0(\AXI4_Lite_RDATA_tmp[13]_i_2_n_0 ),
        .I1(\AXI4_Lite_RDATA_tmp[14]_i_3_n_0 ),
        .I2(\AXI4_Lite_RDATA_tmp_reg[30]_0 [2]),
        .I3(\AXI4_Lite_RDATA_tmp[2]_i_2_n_0 ),
        .O(data_read[2]));
  LUT6 #(
    .INIT(64'hFFFFF888F888F888)) 
    \AXI4_Lite_RDATA_tmp[2]_i_2 
       (.I0(\AXI4_Lite_RDATA_tmp[31]_i_3_n_0 ),
        .I1(\AXI4_Lite_RDATA_tmp_reg[30]_1 [2]),
        .I2(\AXI4_Lite_RDATA_tmp[31]_i_4_n_0 ),
        .I3(\AXI4_Lite_RDATA_tmp_reg[30]_2 [2]),
        .I4(\AXI4_Lite_RDATA_tmp_reg[15]_0 [2]),
        .I5(\AXI4_Lite_RDATA_tmp[0]_i_3_n_0 ),
        .O(\AXI4_Lite_RDATA_tmp[2]_i_2_n_0 ));
  LUT5 #(
    .INIT(32'hFFFFF888)) 
    \AXI4_Lite_RDATA_tmp[30]_i_1 
       (.I0(\AXI4_Lite_RDATA_tmp[31]_i_3_n_0 ),
        .I1(\AXI4_Lite_RDATA_tmp_reg[30]_1 [23]),
        .I2(\AXI4_Lite_RDATA_tmp[31]_i_4_n_0 ),
        .I3(\AXI4_Lite_RDATA_tmp_reg[30]_2 [23]),
        .I4(\AXI4_Lite_RDATA_tmp[30]_i_2_n_0 ),
        .O(data_read[30]));
  (* SOFT_HLUTNM = "soft_lutpair6" *) 
  LUT3 #(
    .INIT(8'hF8)) 
    \AXI4_Lite_RDATA_tmp[30]_i_2 
       (.I0(\AXI4_Lite_RDATA_tmp_reg[30]_0 [15]),
        .I1(\AXI4_Lite_RDATA_tmp[14]_i_3_n_0 ),
        .I2(\AXI4_Lite_RDATA_tmp[13]_i_2_n_0 ),
        .O(\AXI4_Lite_RDATA_tmp[30]_i_2_n_0 ));
  LUT4 #(
    .INIT(16'h0400)) 
    \AXI4_Lite_RDATA_tmp[31]_i_1 
       (.I0(AXI4_Lite_AWVALID),
        .I1(AXI4_Lite_ARVALID),
        .I2(FSM_sequential_axi_lite_rstate_reg_0),
        .I3(\FSM_onehot_axi_lite_wstate_reg_n_0_[0] ),
        .O(top_rd_enb));
  LUT5 #(
    .INIT(32'hFFFFF888)) 
    \AXI4_Lite_RDATA_tmp[31]_i_2 
       (.I0(\AXI4_Lite_RDATA_tmp[31]_i_3_n_0 ),
        .I1(\AXI4_Lite_RDATA_tmp_reg[30]_1 [23]),
        .I2(\AXI4_Lite_RDATA_tmp[31]_i_4_n_0 ),
        .I3(\AXI4_Lite_RDATA_tmp_reg[30]_2 [23]),
        .I4(\AXI4_Lite_RDATA_tmp[31]_i_5_n_0 ),
        .O(data_read[31]));
  LUT6 #(
    .INIT(64'hAAAAAEAAAAAAAAAA)) 
    \AXI4_Lite_RDATA_tmp[31]_i_3 
       (.I0(\AXI4_Lite_RDATA_tmp[31]_i_6_n_0 ),
        .I1(\write_reg_Timer_FPGA_ms_AXI4[31]_i_4_n_0 ),
        .I2(sel0[0]),
        .I3(sel0[1]),
        .I4(sel0[3]),
        .I5(sel0[2]),
        .O(\AXI4_Lite_RDATA_tmp[31]_i_3_n_0 ));
  LUT6 #(
    .INIT(64'hAAAAAAAEAAAAAAAA)) 
    \AXI4_Lite_RDATA_tmp[31]_i_4 
       (.I0(\AXI4_Lite_RDATA_tmp[31]_i_7_n_0 ),
        .I1(\write_reg_Timer_FPGA_ms_AXI4[31]_i_4_n_0 ),
        .I2(sel0[1]),
        .I3(sel0[0]),
        .I4(sel0[2]),
        .I5(sel0[3]),
        .O(\AXI4_Lite_RDATA_tmp[31]_i_4_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair6" *) 
  LUT4 #(
    .INIT(16'hF888)) 
    \AXI4_Lite_RDATA_tmp[31]_i_5 
       (.I0(\AXI4_Lite_RDATA_tmp[14]_i_2_n_0 ),
        .I1(Q[1]),
        .I2(\AXI4_Lite_RDATA_tmp_reg[30]_0 [15]),
        .I3(\AXI4_Lite_RDATA_tmp[14]_i_3_n_0 ),
        .O(\AXI4_Lite_RDATA_tmp[31]_i_5_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair2" *) 
  LUT5 #(
    .INIT(32'h00200000)) 
    \AXI4_Lite_RDATA_tmp[31]_i_6 
       (.I0(AXI4_Lite_ARADDR[2]),
        .I1(AXI4_Lite_ARADDR[3]),
        .I2(AXI4_Lite_ARADDR[1]),
        .I3(AXI4_Lite_ARADDR[0]),
        .I4(\write_reg_IncPerTurn_elek_AXI4[15]_i_2_n_0 ),
        .O(\AXI4_Lite_RDATA_tmp[31]_i_6_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair1" *) 
  LUT5 #(
    .INIT(32'h00020000)) 
    \AXI4_Lite_RDATA_tmp[31]_i_7 
       (.I0(AXI4_Lite_ARADDR[3]),
        .I1(AXI4_Lite_ARADDR[2]),
        .I2(AXI4_Lite_ARADDR[0]),
        .I3(AXI4_Lite_ARADDR[1]),
        .I4(\write_reg_IncPerTurn_elek_AXI4[15]_i_2_n_0 ),
        .O(\AXI4_Lite_RDATA_tmp[31]_i_7_n_0 ));
  LUT4 #(
    .INIT(16'hFFEA)) 
    \AXI4_Lite_RDATA_tmp[3]_i_1 
       (.I0(\AXI4_Lite_RDATA_tmp[13]_i_2_n_0 ),
        .I1(\AXI4_Lite_RDATA_tmp[14]_i_3_n_0 ),
        .I2(\AXI4_Lite_RDATA_tmp_reg[30]_0 [3]),
        .I3(\AXI4_Lite_RDATA_tmp[3]_i_2_n_0 ),
        .O(data_read[3]));
  LUT6 #(
    .INIT(64'hFFFFF888F888F888)) 
    \AXI4_Lite_RDATA_tmp[3]_i_2 
       (.I0(\AXI4_Lite_RDATA_tmp[31]_i_3_n_0 ),
        .I1(\AXI4_Lite_RDATA_tmp_reg[30]_1 [3]),
        .I2(\AXI4_Lite_RDATA_tmp[31]_i_4_n_0 ),
        .I3(\AXI4_Lite_RDATA_tmp_reg[30]_2 [3]),
        .I4(\AXI4_Lite_RDATA_tmp_reg[15]_0 [3]),
        .I5(\AXI4_Lite_RDATA_tmp[0]_i_3_n_0 ),
        .O(\AXI4_Lite_RDATA_tmp[3]_i_2_n_0 ));
  LUT5 #(
    .INIT(32'hFFFFF888)) 
    \AXI4_Lite_RDATA_tmp[4]_i_1 
       (.I0(\AXI4_Lite_RDATA_tmp[14]_i_2_n_0 ),
        .I1(Q[1]),
        .I2(\AXI4_Lite_RDATA_tmp[14]_i_3_n_0 ),
        .I3(\AXI4_Lite_RDATA_tmp_reg[30]_0 [4]),
        .I4(\AXI4_Lite_RDATA_tmp[4]_i_2_n_0 ),
        .O(data_read[4]));
  LUT6 #(
    .INIT(64'hFFFFF888F888F888)) 
    \AXI4_Lite_RDATA_tmp[4]_i_2 
       (.I0(\AXI4_Lite_RDATA_tmp[31]_i_3_n_0 ),
        .I1(\AXI4_Lite_RDATA_tmp_reg[30]_1 [4]),
        .I2(\AXI4_Lite_RDATA_tmp[31]_i_4_n_0 ),
        .I3(\AXI4_Lite_RDATA_tmp_reg[30]_2 [4]),
        .I4(\AXI4_Lite_RDATA_tmp_reg[15]_0 [4]),
        .I5(\AXI4_Lite_RDATA_tmp[0]_i_3_n_0 ),
        .O(\AXI4_Lite_RDATA_tmp[4]_i_2_n_0 ));
  LUT4 #(
    .INIT(16'hFFEA)) 
    \AXI4_Lite_RDATA_tmp[5]_i_1 
       (.I0(\AXI4_Lite_RDATA_tmp[13]_i_2_n_0 ),
        .I1(\AXI4_Lite_RDATA_tmp[14]_i_3_n_0 ),
        .I2(\AXI4_Lite_RDATA_tmp_reg[30]_0 [5]),
        .I3(\AXI4_Lite_RDATA_tmp[5]_i_2_n_0 ),
        .O(data_read[5]));
  LUT6 #(
    .INIT(64'hFFFFF888F888F888)) 
    \AXI4_Lite_RDATA_tmp[5]_i_2 
       (.I0(\AXI4_Lite_RDATA_tmp[31]_i_3_n_0 ),
        .I1(\AXI4_Lite_RDATA_tmp_reg[30]_1 [5]),
        .I2(\AXI4_Lite_RDATA_tmp[31]_i_4_n_0 ),
        .I3(\AXI4_Lite_RDATA_tmp_reg[30]_2 [5]),
        .I4(\AXI4_Lite_RDATA_tmp_reg[15]_0 [5]),
        .I5(\AXI4_Lite_RDATA_tmp[0]_i_3_n_0 ),
        .O(\AXI4_Lite_RDATA_tmp[5]_i_2_n_0 ));
  LUT5 #(
    .INIT(32'hFFFFF888)) 
    \AXI4_Lite_RDATA_tmp[6]_i_1 
       (.I0(\AXI4_Lite_RDATA_tmp[14]_i_2_n_0 ),
        .I1(Q[1]),
        .I2(\AXI4_Lite_RDATA_tmp[14]_i_3_n_0 ),
        .I3(\AXI4_Lite_RDATA_tmp_reg[30]_0 [6]),
        .I4(\AXI4_Lite_RDATA_tmp[6]_i_2_n_0 ),
        .O(data_read[6]));
  LUT6 #(
    .INIT(64'hFFFFF888F888F888)) 
    \AXI4_Lite_RDATA_tmp[6]_i_2 
       (.I0(\AXI4_Lite_RDATA_tmp[31]_i_3_n_0 ),
        .I1(\AXI4_Lite_RDATA_tmp_reg[30]_1 [6]),
        .I2(\AXI4_Lite_RDATA_tmp[31]_i_4_n_0 ),
        .I3(\AXI4_Lite_RDATA_tmp_reg[30]_2 [6]),
        .I4(\AXI4_Lite_RDATA_tmp_reg[15]_0 [6]),
        .I5(\AXI4_Lite_RDATA_tmp[0]_i_3_n_0 ),
        .O(\AXI4_Lite_RDATA_tmp[6]_i_2_n_0 ));
  LUT4 #(
    .INIT(16'hFFEA)) 
    \AXI4_Lite_RDATA_tmp[7]_i_1 
       (.I0(\AXI4_Lite_RDATA_tmp[13]_i_2_n_0 ),
        .I1(\AXI4_Lite_RDATA_tmp[14]_i_3_n_0 ),
        .I2(\AXI4_Lite_RDATA_tmp_reg[30]_0 [7]),
        .I3(\AXI4_Lite_RDATA_tmp[7]_i_2_n_0 ),
        .O(data_read[7]));
  LUT6 #(
    .INIT(64'hFFFFF888F888F888)) 
    \AXI4_Lite_RDATA_tmp[7]_i_2 
       (.I0(\AXI4_Lite_RDATA_tmp[31]_i_3_n_0 ),
        .I1(\AXI4_Lite_RDATA_tmp_reg[30]_1 [7]),
        .I2(\AXI4_Lite_RDATA_tmp[31]_i_4_n_0 ),
        .I3(\AXI4_Lite_RDATA_tmp_reg[30]_2 [7]),
        .I4(\AXI4_Lite_RDATA_tmp_reg[15]_0 [7]),
        .I5(\AXI4_Lite_RDATA_tmp[0]_i_3_n_0 ),
        .O(\AXI4_Lite_RDATA_tmp[7]_i_2_n_0 ));
  LUT4 #(
    .INIT(16'hFFEA)) 
    \AXI4_Lite_RDATA_tmp[8]_i_1 
       (.I0(\AXI4_Lite_RDATA_tmp[13]_i_2_n_0 ),
        .I1(\AXI4_Lite_RDATA_tmp[14]_i_3_n_0 ),
        .I2(\AXI4_Lite_RDATA_tmp_reg[30]_0 [8]),
        .I3(\AXI4_Lite_RDATA_tmp[8]_i_2_n_0 ),
        .O(data_read[8]));
  LUT6 #(
    .INIT(64'hFFFFF888F888F888)) 
    \AXI4_Lite_RDATA_tmp[8]_i_2 
       (.I0(\AXI4_Lite_RDATA_tmp[31]_i_3_n_0 ),
        .I1(\AXI4_Lite_RDATA_tmp_reg[30]_1 [8]),
        .I2(\AXI4_Lite_RDATA_tmp[31]_i_4_n_0 ),
        .I3(\AXI4_Lite_RDATA_tmp_reg[30]_2 [8]),
        .I4(\AXI4_Lite_RDATA_tmp_reg[15]_0 [8]),
        .I5(\AXI4_Lite_RDATA_tmp[0]_i_3_n_0 ),
        .O(\AXI4_Lite_RDATA_tmp[8]_i_2_n_0 ));
  LUT5 #(
    .INIT(32'hFFFFF888)) 
    \AXI4_Lite_RDATA_tmp[9]_i_1 
       (.I0(\AXI4_Lite_RDATA_tmp[14]_i_2_n_0 ),
        .I1(Q[1]),
        .I2(\AXI4_Lite_RDATA_tmp[14]_i_3_n_0 ),
        .I3(\AXI4_Lite_RDATA_tmp_reg[30]_0 [9]),
        .I4(\AXI4_Lite_RDATA_tmp[9]_i_2_n_0 ),
        .O(data_read[9]));
  LUT6 #(
    .INIT(64'hFFFFF888F888F888)) 
    \AXI4_Lite_RDATA_tmp[9]_i_2 
       (.I0(\AXI4_Lite_RDATA_tmp[31]_i_3_n_0 ),
        .I1(\AXI4_Lite_RDATA_tmp_reg[30]_1 [9]),
        .I2(\AXI4_Lite_RDATA_tmp[31]_i_4_n_0 ),
        .I3(\AXI4_Lite_RDATA_tmp_reg[30]_2 [9]),
        .I4(\AXI4_Lite_RDATA_tmp_reg[15]_0 [9]),
        .I5(\AXI4_Lite_RDATA_tmp[0]_i_3_n_0 ),
        .O(\AXI4_Lite_RDATA_tmp[9]_i_2_n_0 ));
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
        .Q(AXI4_Lite_RDATA[23]),
        .R(reset));
  FDRE \AXI4_Lite_RDATA_tmp_reg[31] 
       (.C(AXI4_Lite_ACLK),
        .CE(top_rd_enb),
        .D(data_read[31]),
        .Q(AXI4_Lite_RDATA[24]),
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
    .INIT(32'hFFC0D5C0)) 
    \FSM_onehot_axi_lite_wstate[0]_i_1 
       (.I0(AXI4_Lite_AWVALID),
        .I1(AXI4_Lite_BREADY),
        .I2(\FSM_onehot_axi_lite_wstate_reg[2]_0 [1]),
        .I3(\FSM_onehot_axi_lite_wstate_reg_n_0_[0] ),
        .I4(FSM_sequential_axi_lite_rstate_reg_0),
        .O(axi_lite_wstate_next[0]));
  LUT1 #(
    .INIT(2'h1)) 
    \FSM_onehot_axi_lite_wstate[1]_i_1 
       (.I0(AXI4_Lite_ARESETN),
        .O(reset));
  (* SOFT_HLUTNM = "soft_lutpair5" *) 
  LUT5 #(
    .INIT(32'h4444F444)) 
    \FSM_onehot_axi_lite_wstate[1]_i_2 
       (.I0(AXI4_Lite_WVALID),
        .I1(\FSM_onehot_axi_lite_wstate_reg[2]_0 [0]),
        .I2(AXI4_Lite_AWVALID),
        .I3(\FSM_onehot_axi_lite_wstate_reg_n_0_[0] ),
        .I4(FSM_sequential_axi_lite_rstate_reg_0),
        .O(axi_lite_wstate_next[1]));
  LUT4 #(
    .INIT(16'h8F88)) 
    \FSM_onehot_axi_lite_wstate[2]_i_1 
       (.I0(\FSM_onehot_axi_lite_wstate_reg[2]_0 [0]),
        .I1(AXI4_Lite_WVALID),
        .I2(AXI4_Lite_BREADY),
        .I3(\FSM_onehot_axi_lite_wstate_reg[2]_0 [1]),
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
        .Q(\FSM_onehot_axi_lite_wstate_reg[2]_0 [0]),
        .R(reset));
  (* FSM_ENCODED_STATES = "iSTATE:010,iSTATE0:100,iSTATE1:001" *) 
  FDRE #(
    .INIT(1'b0)) 
    \FSM_onehot_axi_lite_wstate_reg[2] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(axi_lite_wstate_next[2]),
        .Q(\FSM_onehot_axi_lite_wstate_reg[2]_0 [1]),
        .R(reset));
  (* SOFT_HLUTNM = "soft_lutpair4" *) 
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
  (* SOFT_HLUTNM = "soft_lutpair9" *) 
  LUT3 #(
    .INIT(8'h20)) 
    \reset_old4_out1[0]_i_1 
       (.I0(IPCORE_RESETN),
        .I1(soft_reset),
        .I2(AXI4_Lite_ARESETN),
        .O(p_1_in));
  LUT6 #(
    .INIT(64'h2000000000000000)) 
    soft_reset_i_1
       (.I0(soft_reset_i_2_n_0),
        .I1(sel0[0]),
        .I2(soft_reset_i_3_n_0),
        .I3(AXI4_Lite_ARESETN),
        .I4(\wdata_reg[31]_0 [0]),
        .I5(\write_reg_Timer_FPGA_ms_AXI4[31]_i_6_n_0 ),
        .O(soft_reset_i_1_n_0));
  LUT6 #(
    .INIT(64'h0000000000000002)) 
    soft_reset_i_2
       (.I0(soft_reset_i_4_n_0),
        .I1(sel0[8]),
        .I2(sel0[7]),
        .I3(sel0[5]),
        .I4(sel0[4]),
        .I5(sel0[13]),
        .O(soft_reset_i_2_n_0));
  (* SOFT_HLUTNM = "soft_lutpair10" *) 
  LUT2 #(
    .INIT(4'h1)) 
    soft_reset_i_3
       (.I0(sel0[1]),
        .I1(sel0[6]),
        .O(soft_reset_i_3_n_0));
  LUT4 #(
    .INIT(16'h0001)) 
    soft_reset_i_4
       (.I0(sel0[12]),
        .I1(sel0[11]),
        .I2(sel0[10]),
        .I3(sel0[9]),
        .O(soft_reset_i_4_n_0));
  FDRE soft_reset_reg
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(soft_reset_i_1_n_0),
        .Q(soft_reset),
        .R(1'b0));
  (* SOFT_HLUTNM = "soft_lutpair9" *) 
  LUT3 #(
    .INIT(8'hDF)) 
    theta_el_tmp_reg_i_2
       (.I0(AXI4_Lite_ARESETN),
        .I1(soft_reset),
        .I2(IPCORE_RESETN),
        .O(RSTP));
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
  LUT2 #(
    .INIT(4'h8)) 
    \wdata[31]_i_1 
       (.I0(AXI4_Lite_WVALID),
        .I1(\FSM_onehot_axi_lite_wstate_reg[2]_0 [0]),
        .O(w_transfer));
  FDRE \wdata_reg[0] 
       (.C(AXI4_Lite_ACLK),
        .CE(w_transfer),
        .D(AXI4_Lite_WDATA[0]),
        .Q(\wdata_reg[31]_0 [0]),
        .R(reset));
  FDRE \wdata_reg[10] 
       (.C(AXI4_Lite_ACLK),
        .CE(w_transfer),
        .D(AXI4_Lite_WDATA[10]),
        .Q(\wdata_reg[31]_0 [10]),
        .R(reset));
  FDRE \wdata_reg[11] 
       (.C(AXI4_Lite_ACLK),
        .CE(w_transfer),
        .D(AXI4_Lite_WDATA[11]),
        .Q(\wdata_reg[31]_0 [11]),
        .R(reset));
  FDRE \wdata_reg[12] 
       (.C(AXI4_Lite_ACLK),
        .CE(w_transfer),
        .D(AXI4_Lite_WDATA[12]),
        .Q(\wdata_reg[31]_0 [12]),
        .R(reset));
  FDRE \wdata_reg[13] 
       (.C(AXI4_Lite_ACLK),
        .CE(w_transfer),
        .D(AXI4_Lite_WDATA[13]),
        .Q(\wdata_reg[31]_0 [13]),
        .R(reset));
  FDRE \wdata_reg[14] 
       (.C(AXI4_Lite_ACLK),
        .CE(w_transfer),
        .D(AXI4_Lite_WDATA[14]),
        .Q(\wdata_reg[31]_0 [14]),
        .R(reset));
  FDRE \wdata_reg[15] 
       (.C(AXI4_Lite_ACLK),
        .CE(w_transfer),
        .D(AXI4_Lite_WDATA[15]),
        .Q(\wdata_reg[31]_0 [15]),
        .R(reset));
  FDRE \wdata_reg[16] 
       (.C(AXI4_Lite_ACLK),
        .CE(w_transfer),
        .D(AXI4_Lite_WDATA[16]),
        .Q(\wdata_reg[31]_0 [16]),
        .R(reset));
  FDRE \wdata_reg[17] 
       (.C(AXI4_Lite_ACLK),
        .CE(w_transfer),
        .D(AXI4_Lite_WDATA[17]),
        .Q(\wdata_reg[31]_0 [17]),
        .R(reset));
  FDRE \wdata_reg[18] 
       (.C(AXI4_Lite_ACLK),
        .CE(w_transfer),
        .D(AXI4_Lite_WDATA[18]),
        .Q(\wdata_reg[31]_0 [18]),
        .R(reset));
  FDRE \wdata_reg[19] 
       (.C(AXI4_Lite_ACLK),
        .CE(w_transfer),
        .D(AXI4_Lite_WDATA[19]),
        .Q(\wdata_reg[31]_0 [19]),
        .R(reset));
  FDRE \wdata_reg[1] 
       (.C(AXI4_Lite_ACLK),
        .CE(w_transfer),
        .D(AXI4_Lite_WDATA[1]),
        .Q(\wdata_reg[31]_0 [1]),
        .R(reset));
  FDRE \wdata_reg[20] 
       (.C(AXI4_Lite_ACLK),
        .CE(w_transfer),
        .D(AXI4_Lite_WDATA[20]),
        .Q(\wdata_reg[31]_0 [20]),
        .R(reset));
  FDRE \wdata_reg[21] 
       (.C(AXI4_Lite_ACLK),
        .CE(w_transfer),
        .D(AXI4_Lite_WDATA[21]),
        .Q(\wdata_reg[31]_0 [21]),
        .R(reset));
  FDRE \wdata_reg[22] 
       (.C(AXI4_Lite_ACLK),
        .CE(w_transfer),
        .D(AXI4_Lite_WDATA[22]),
        .Q(\wdata_reg[31]_0 [22]),
        .R(reset));
  FDRE \wdata_reg[23] 
       (.C(AXI4_Lite_ACLK),
        .CE(w_transfer),
        .D(AXI4_Lite_WDATA[23]),
        .Q(\wdata_reg[31]_0 [23]),
        .R(reset));
  FDRE \wdata_reg[24] 
       (.C(AXI4_Lite_ACLK),
        .CE(w_transfer),
        .D(AXI4_Lite_WDATA[24]),
        .Q(\wdata_reg[31]_0 [24]),
        .R(reset));
  FDRE \wdata_reg[25] 
       (.C(AXI4_Lite_ACLK),
        .CE(w_transfer),
        .D(AXI4_Lite_WDATA[25]),
        .Q(\wdata_reg[31]_0 [25]),
        .R(reset));
  FDRE \wdata_reg[26] 
       (.C(AXI4_Lite_ACLK),
        .CE(w_transfer),
        .D(AXI4_Lite_WDATA[26]),
        .Q(\wdata_reg[31]_0 [26]),
        .R(reset));
  FDRE \wdata_reg[27] 
       (.C(AXI4_Lite_ACLK),
        .CE(w_transfer),
        .D(AXI4_Lite_WDATA[27]),
        .Q(\wdata_reg[31]_0 [27]),
        .R(reset));
  FDRE \wdata_reg[28] 
       (.C(AXI4_Lite_ACLK),
        .CE(w_transfer),
        .D(AXI4_Lite_WDATA[28]),
        .Q(\wdata_reg[31]_0 [28]),
        .R(reset));
  FDRE \wdata_reg[29] 
       (.C(AXI4_Lite_ACLK),
        .CE(w_transfer),
        .D(AXI4_Lite_WDATA[29]),
        .Q(\wdata_reg[31]_0 [29]),
        .R(reset));
  FDRE \wdata_reg[2] 
       (.C(AXI4_Lite_ACLK),
        .CE(w_transfer),
        .D(AXI4_Lite_WDATA[2]),
        .Q(\wdata_reg[31]_0 [2]),
        .R(reset));
  FDRE \wdata_reg[30] 
       (.C(AXI4_Lite_ACLK),
        .CE(w_transfer),
        .D(AXI4_Lite_WDATA[30]),
        .Q(\wdata_reg[31]_0 [30]),
        .R(reset));
  FDRE \wdata_reg[31] 
       (.C(AXI4_Lite_ACLK),
        .CE(w_transfer),
        .D(AXI4_Lite_WDATA[31]),
        .Q(\wdata_reg[31]_0 [31]),
        .R(reset));
  FDRE \wdata_reg[3] 
       (.C(AXI4_Lite_ACLK),
        .CE(w_transfer),
        .D(AXI4_Lite_WDATA[3]),
        .Q(\wdata_reg[31]_0 [3]),
        .R(reset));
  FDRE \wdata_reg[4] 
       (.C(AXI4_Lite_ACLK),
        .CE(w_transfer),
        .D(AXI4_Lite_WDATA[4]),
        .Q(\wdata_reg[31]_0 [4]),
        .R(reset));
  FDRE \wdata_reg[5] 
       (.C(AXI4_Lite_ACLK),
        .CE(w_transfer),
        .D(AXI4_Lite_WDATA[5]),
        .Q(\wdata_reg[31]_0 [5]),
        .R(reset));
  FDRE \wdata_reg[6] 
       (.C(AXI4_Lite_ACLK),
        .CE(w_transfer),
        .D(AXI4_Lite_WDATA[6]),
        .Q(\wdata_reg[31]_0 [6]),
        .R(reset));
  FDRE \wdata_reg[7] 
       (.C(AXI4_Lite_ACLK),
        .CE(w_transfer),
        .D(AXI4_Lite_WDATA[7]),
        .Q(\wdata_reg[31]_0 [7]),
        .R(reset));
  FDRE \wdata_reg[8] 
       (.C(AXI4_Lite_ACLK),
        .CE(w_transfer),
        .D(AXI4_Lite_WDATA[8]),
        .Q(\wdata_reg[31]_0 [8]),
        .R(reset));
  FDRE \wdata_reg[9] 
       (.C(AXI4_Lite_ACLK),
        .CE(w_transfer),
        .D(AXI4_Lite_WDATA[9]),
        .Q(\wdata_reg[31]_0 [9]),
        .R(reset));
  LUT6 #(
    .INIT(64'h8000000000000000)) 
    wr_enb_1_i_1
       (.I0(AXI4_Lite_WSTRB[2]),
        .I1(AXI4_Lite_WSTRB[3]),
        .I2(AXI4_Lite_WSTRB[0]),
        .I3(AXI4_Lite_WSTRB[1]),
        .I4(\FSM_onehot_axi_lite_wstate_reg[2]_0 [0]),
        .I5(AXI4_Lite_WVALID),
        .O(w_transfer_and_wstrb));
  FDRE wr_enb_1_reg
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(w_transfer_and_wstrb),
        .Q(top_wr_enb),
        .R(reset));
  LUT6 #(
    .INIT(64'hFFFFFFFF20000000)) 
    \write_reg_IncPerTurn_elek_AXI4[15]_i_1 
       (.I0(\write_reg_IncPerTurn_elek_AXI4[15]_i_2_n_0 ),
        .I1(AXI4_Lite_ARADDR[1]),
        .I2(AXI4_Lite_ARADDR[2]),
        .I3(top_wr_enb),
        .I4(\write_reg_IncPerTurn_elek_AXI4_reg[15] ),
        .I5(\write_reg_IncPerTurn_elek_AXI4[15]_i_3_n_0 ),
        .O(\AXI4_Lite_ARADDR[3] ));
  LUT2 #(
    .INIT(4'h8)) 
    \write_reg_IncPerTurn_elek_AXI4[15]_i_2 
       (.I0(write_reg_axi_enable_i_2_n_0),
        .I1(AXI4_Lite_ARADDR[6]),
        .O(\write_reg_IncPerTurn_elek_AXI4[15]_i_2_n_0 ));
  LUT6 #(
    .INIT(64'h0200000000000000)) 
    \write_reg_IncPerTurn_elek_AXI4[15]_i_3 
       (.I0(top_wr_enb),
        .I1(sel0[3]),
        .I2(sel0[1]),
        .I3(sel0[2]),
        .I4(sel0[0]),
        .I5(\write_reg_Timer_FPGA_ms_AXI4[31]_i_4_n_0 ),
        .O(\write_reg_IncPerTurn_elek_AXI4[15]_i_3_n_0 ));
  LUT6 #(
    .INIT(64'hFF80808080808080)) 
    \write_reg_IncPerTurn_mech_AXI4[15]_i_1 
       (.I0(\write_reg_Timer_FPGA_ms_AXI4[31]_i_2_n_0 ),
        .I1(\write_reg_IncPerTurn_elek_AXI4_reg[15] ),
        .I2(AXI4_Lite_ARADDR[1]),
        .I3(\write_reg_Timer_FPGA_ms_AXI4[31]_i_4_n_0 ),
        .I4(\write_reg_IncPerTurn_mech_AXI4[15]_i_2_n_0 ),
        .I5(\write_reg_Timer_FPGA_ms_AXI4[31]_i_6_n_0 ),
        .O(\AXI4_Lite_ARADDR[3]_0 ));
  (* SOFT_HLUTNM = "soft_lutpair11" *) 
  LUT2 #(
    .INIT(4'h8)) 
    \write_reg_IncPerTurn_mech_AXI4[15]_i_2 
       (.I0(sel0[0]),
        .I1(sel0[1]),
        .O(\write_reg_IncPerTurn_mech_AXI4[15]_i_2_n_0 ));
  LUT6 #(
    .INIT(64'hFFFF008000800080)) 
    \write_reg_OmegaPerOverSampl_AXI4[23]_i_1 
       (.I0(\write_reg_Timer_FPGA_ms_AXI4[31]_i_2_n_0 ),
        .I1(AXI4_Lite_ARADDR[3]),
        .I2(AXI4_Lite_ARADDR[1]),
        .I3(AXI4_Lite_ARADDR[0]),
        .I4(\write_reg_Timer_FPGA_ms_AXI4[31]_i_4_n_0 ),
        .I5(\write_reg_OmegaPerOverSampl_AXI4[23]_i_2_n_0 ),
        .O(\AXI4_Lite_ARADDR[5] ));
  (* SOFT_HLUTNM = "soft_lutpair0" *) 
  LUT5 #(
    .INIT(32'h00400000)) 
    \write_reg_OmegaPerOverSampl_AXI4[23]_i_2 
       (.I0(sel0[0]),
        .I1(sel0[1]),
        .I2(sel0[3]),
        .I3(sel0[2]),
        .I4(top_wr_enb),
        .O(\write_reg_OmegaPerOverSampl_AXI4[23]_i_2_n_0 ));
  LUT6 #(
    .INIT(64'hFFFF002000200020)) 
    \write_reg_PI2_Inc_AXI4[23]_i_1 
       (.I0(\write_reg_Timer_FPGA_ms_AXI4[31]_i_2_n_0 ),
        .I1(AXI4_Lite_ARADDR[3]),
        .I2(AXI4_Lite_ARADDR[1]),
        .I3(AXI4_Lite_ARADDR[0]),
        .I4(\write_reg_Timer_FPGA_ms_AXI4[31]_i_4_n_0 ),
        .I5(\write_reg_PI2_Inc_AXI4[23]_i_2_n_0 ),
        .O(\AXI4_Lite_ARADDR[5]_0 ));
  (* SOFT_HLUTNM = "soft_lutpair0" *) 
  LUT5 #(
    .INIT(32'h00000400)) 
    \write_reg_PI2_Inc_AXI4[23]_i_2 
       (.I0(sel0[0]),
        .I1(sel0[1]),
        .I2(sel0[3]),
        .I3(top_wr_enb),
        .I4(sel0[2]),
        .O(\write_reg_PI2_Inc_AXI4[23]_i_2_n_0 ));
  LUT6 #(
    .INIT(64'hFF08080808080808)) 
    \write_reg_Timer_FPGA_ms_AXI4[31]_i_1 
       (.I0(\write_reg_Timer_FPGA_ms_AXI4[31]_i_2_n_0 ),
        .I1(\write_reg_IncPerTurn_elek_AXI4_reg[15] ),
        .I2(AXI4_Lite_ARADDR[1]),
        .I3(\write_reg_Timer_FPGA_ms_AXI4[31]_i_4_n_0 ),
        .I4(\write_reg_Timer_FPGA_ms_AXI4[31]_i_5_n_0 ),
        .I5(\write_reg_Timer_FPGA_ms_AXI4[31]_i_6_n_0 ),
        .O(E));
  (* SOFT_HLUTNM = "soft_lutpair8" *) 
  LUT3 #(
    .INIT(8'h40)) 
    \write_reg_Timer_FPGA_ms_AXI4[31]_i_2 
       (.I0(AXI4_Lite_ARADDR[2]),
        .I1(top_wr_enb),
        .I2(\write_reg_IncPerTurn_elek_AXI4[15]_i_2_n_0 ),
        .O(\write_reg_Timer_FPGA_ms_AXI4[31]_i_2_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair10" *) 
  LUT2 #(
    .INIT(4'h8)) 
    \write_reg_Timer_FPGA_ms_AXI4[31]_i_4 
       (.I0(write_reg_axi_enable_i_4_n_0),
        .I1(sel0[6]),
        .O(\write_reg_Timer_FPGA_ms_AXI4[31]_i_4_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair11" *) 
  LUT2 #(
    .INIT(4'h2)) 
    \write_reg_Timer_FPGA_ms_AXI4[31]_i_5 
       (.I0(sel0[0]),
        .I1(sel0[1]),
        .O(\write_reg_Timer_FPGA_ms_AXI4[31]_i_5_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair8" *) 
  LUT3 #(
    .INIT(8'h04)) 
    \write_reg_Timer_FPGA_ms_AXI4[31]_i_6 
       (.I0(sel0[2]),
        .I1(top_wr_enb),
        .I2(sel0[3]),
        .O(\write_reg_Timer_FPGA_ms_AXI4[31]_i_6_n_0 ));
  LUT6 #(
    .INIT(64'hAABFBFBFAA808080)) 
    write_reg_axi_enable_i_1
       (.I0(\wdata_reg[31]_0 [0]),
        .I1(write_reg_axi_enable_i_2_n_0),
        .I2(write_reg_axi_enable_i_3_n_0),
        .I3(write_reg_axi_enable_i_4_n_0),
        .I4(write_reg_axi_enable_i_5_n_0),
        .I5(write_axi_enable),
        .O(\wdata_reg[0]_0 ));
  LUT4 #(
    .INIT(16'h0008)) 
    write_reg_axi_enable_i_2
       (.I0(write_reg_axi_enable_i_6_n_0),
        .I1(write_reg_axi_enable_i_7_n_0),
        .I2(AXI4_Lite_ARADDR[5]),
        .I3(AXI4_Lite_ARADDR[4]),
        .O(write_reg_axi_enable_i_2_n_0));
  LUT6 #(
    .INIT(64'h0000000200000000)) 
    write_reg_axi_enable_i_3
       (.I0(top_wr_enb),
        .I1(AXI4_Lite_ARADDR[2]),
        .I2(AXI4_Lite_ARADDR[1]),
        .I3(AXI4_Lite_ARADDR[6]),
        .I4(AXI4_Lite_ARADDR[3]),
        .I5(AXI4_Lite_ARADDR[0]),
        .O(write_reg_axi_enable_i_3_n_0));
  (* SOFT_HLUTNM = "soft_lutpair7" *) 
  LUT2 #(
    .INIT(4'h2)) 
    write_reg_axi_enable_i_4
       (.I0(soft_reset_i_2_n_0),
        .I1(AXI4_Lite_ARVALID),
        .O(write_reg_axi_enable_i_4_n_0));
  LUT6 #(
    .INIT(64'h0000000000020000)) 
    write_reg_axi_enable_i_5
       (.I0(sel0[0]),
        .I1(sel0[1]),
        .I2(sel0[6]),
        .I3(sel0[3]),
        .I4(top_wr_enb),
        .I5(sel0[2]),
        .O(write_reg_axi_enable_i_5_n_0));
  (* SOFT_HLUTNM = "soft_lutpair7" *) 
  LUT4 #(
    .INIT(16'h0004)) 
    write_reg_axi_enable_i_6
       (.I0(AXI4_Lite_ARADDR[13]),
        .I1(AXI4_Lite_ARVALID),
        .I2(AXI4_Lite_ARADDR[12]),
        .I3(AXI4_Lite_ARADDR[11]),
        .O(write_reg_axi_enable_i_6_n_0));
  LUT4 #(
    .INIT(16'h0001)) 
    write_reg_axi_enable_i_7
       (.I0(AXI4_Lite_ARADDR[10]),
        .I1(AXI4_Lite_ARADDR[9]),
        .I2(AXI4_Lite_ARADDR[8]),
        .I3(AXI4_Lite_ARADDR[7]),
        .O(write_reg_axi_enable_i_7_n_0));
endmodule

(* ORIG_REF_NAME = "IncreEncoder_V24_ip_dut" *) 
module zusys_IncreEncoder_V24_ip_0_0_IncreEncoder_V24_ip_dut
   (phase_0,
    theta_el,
    edge_rsvd,
    count,
    \countPerPEriod_1_reg[15] ,
    position,
    reset_old5_out1,
    D,
    OverSamplFactor,
    RSTP,
    IPCORE_CLK,
    write_axi_enable,
    DSP_ALU_INST,
    \reset_old4_out1_reg[0] ,
    \reset_old4_out1_reg[0]_0 ,
    PeriodEnd,
    I,
    A,
    B,
    \Pipeline6_out1_reg[31] ,
    \Pipeline4_out1_reg[23] ,
    \Pipeline2_out1_reg[15] ,
    \Pipeline3_out1_reg[15] );
  output phase_0;
  output [23:0]theta_el;
  output edge_rsvd;
  output count;
  output [15:0]\countPerPEriod_1_reg[15] ;
  output [15:0]position;
  output [1:0]reset_old5_out1;
  output [23:0]D;
  output [15:0]OverSamplFactor;
  input RSTP;
  input IPCORE_CLK;
  input write_axi_enable;
  input [23:0]DSP_ALU_INST;
  input \reset_old4_out1_reg[0] ;
  input [0:0]\reset_old4_out1_reg[0]_0 ;
  input PeriodEnd;
  input I;
  input A;
  input B;
  input [31:0]\Pipeline6_out1_reg[31] ;
  input [23:0]\Pipeline4_out1_reg[23] ;
  input [15:0]\Pipeline2_out1_reg[15] ;
  input [15:0]\Pipeline3_out1_reg[15] ;

  wire A;
  wire B;
  wire [23:0]D;
  wire [23:0]DSP_ALU_INST;
  wire I;
  wire IPCORE_CLK;
  wire [15:0]OverSamplFactor;
  wire PeriodEnd;
  wire [15:0]\Pipeline2_out1_reg[15] ;
  wire [15:0]\Pipeline3_out1_reg[15] ;
  wire [23:0]\Pipeline4_out1_reg[23] ;
  wire [31:0]\Pipeline6_out1_reg[31] ;
  wire RSTP;
  wire count;
  wire [15:0]\countPerPEriod_1_reg[15] ;
  wire edge_rsvd;
  wire phase_0;
  wire [15:0]position;
  wire \reset_old4_out1_reg[0] ;
  wire [0:0]\reset_old4_out1_reg[0]_0 ;
  wire [1:0]reset_old5_out1;
  wire [23:0]theta_el;
  wire write_axi_enable;

  zusys_IncreEncoder_V24_ip_0_0_IncreEncoder_V24_ip_src_IncreEncoder_V24 u_IncreEncoder_V24_ip_src_IncreEncoder_V24
       (.A(A),
        .B(B),
        .D(D[22:0]),
        .DSP_ALU_INST(DSP_ALU_INST),
        .I(I),
        .IPCORE_CLK(IPCORE_CLK),
        .OverSamplFactor(OverSamplFactor),
        .PeriodEnd(PeriodEnd),
        .\Pipeline2_out1_reg[15]_0 (\Pipeline2_out1_reg[15] ),
        .\Pipeline3_out1_reg[15]_0 (\Pipeline3_out1_reg[15] ),
        .\Pipeline4_out1_reg[23]_0 (\Pipeline4_out1_reg[23] ),
        .\Pipeline6_out1_reg[31]_0 (\Pipeline6_out1_reg[31] ),
        .Q(D[23]),
        .RSTP(RSTP),
        .count(count),
        .\countPerPEriod_1_reg[15]_0 (\countPerPEriod_1_reg[15] ),
        .edge_rsvd(edge_rsvd),
        .phase_0_reg(phase_0),
        .position(position),
        .\reset_old4_out1_reg[0] (\reset_old4_out1_reg[0] ),
        .\reset_old4_out1_reg[0]_0 (\reset_old4_out1_reg[0]_0 ),
        .\reset_old5_out1_reg[0] (reset_old5_out1[0]),
        .\reset_old5_out1_reg[3] (reset_old5_out1[1]),
        .theta_el(theta_el),
        .write_axi_enable(write_axi_enable));
endmodule

(* ORIG_REF_NAME = "IncreEncoder_V24_ip_src_Check_Direction" *) 
module zusys_IncreEncoder_V24_ip_0_0_IncreEncoder_V24_ip_src_Check_Direction
   (count_old1_out1_reg_0,
    count_old_out1_reg_0,
    Q,
    RSTP,
    count_old1_out1_reg_1,
    IPCORE_CLK,
    count_old_out1_reg_1,
    \Dir_tmp_reg[0]_0 ,
    write_axi_enable,
    A,
    B,
    CEP);
  output count_old1_out1_reg_0;
  output count_old_out1_reg_0;
  output [1:0]Q;
  input RSTP;
  input count_old1_out1_reg_1;
  input IPCORE_CLK;
  input count_old_out1_reg_1;
  input \Dir_tmp_reg[0]_0 ;
  input write_axi_enable;
  input A;
  input B;
  input CEP;

  wire A;
  wire B;
  wire CEP;
  wire [1:0]Change_out1;
  wire Dir_tmp;
  wire \Dir_tmp_reg[0]_0 ;
  wire IPCORE_CLK;
  wire [1:0]Q;
  wire RSTP;
  wire count_old1_out1_reg_0;
  wire count_old1_out1_reg_1;
  wire count_old_out1_reg_0;
  wire count_old_out1_reg_1;
  wire [1:0]new_value_out1;
  wire write_axi_enable;

  (* SOFT_HLUTNM = "soft_lutpair12" *) 
  LUT4 #(
    .INIT(16'h0350)) 
    \Change_1[0]_i_1 
       (.I0(count_old_out1_reg_0),
        .I1(count_old1_out1_reg_0),
        .I2(A),
        .I3(B),
        .O(Change_out1[0]));
  (* SOFT_HLUTNM = "soft_lutpair12" *) 
  LUT3 #(
    .INIT(8'h02)) 
    \Change_1[1]_i_1 
       (.I0(B),
        .I1(A),
        .I2(count_old1_out1_reg_0),
        .O(Change_out1[1]));
  FDRE \Change_1_reg[0] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Change_out1[0]),
        .Q(new_value_out1[0]),
        .R(RSTP));
  FDRE \Change_1_reg[1] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Change_out1[1]),
        .Q(new_value_out1[1]),
        .R(RSTP));
  LUT4 #(
    .INIT(16'h8880)) 
    \Dir_tmp[3]_i_1 
       (.I0(\Dir_tmp_reg[0]_0 ),
        .I1(write_axi_enable),
        .I2(new_value_out1[0]),
        .I3(new_value_out1[1]),
        .O(Dir_tmp));
  FDRE \Dir_tmp_reg[0] 
       (.C(IPCORE_CLK),
        .CE(Dir_tmp),
        .D(new_value_out1[0]),
        .Q(Q[0]),
        .R(RSTP));
  FDRE \Dir_tmp_reg[3] 
       (.C(IPCORE_CLK),
        .CE(Dir_tmp),
        .D(new_value_out1[1]),
        .Q(Q[1]),
        .R(RSTP));
  FDRE count_old1_out1_reg
       (.C(IPCORE_CLK),
        .CE(1'b1),
        .D(count_old1_out1_reg_1),
        .Q(count_old1_out1_reg_0),
        .R(RSTP));
  FDRE count_old_out1_reg
       (.C(IPCORE_CLK),
        .CE(1'b1),
        .D(count_old_out1_reg_1),
        .Q(count_old_out1_reg_0),
        .R(RSTP));
endmodule

(* ORIG_REF_NAME = "IncreEncoder_V24_ip_src_Count" *) 
module zusys_IncreEncoder_V24_ip_0_0_IncreEncoder_V24_ip_src_Count
   (D,
    O,
    Delay3_out1_reg,
    Delay3_out1_reg_0,
    Delay6_out1_reg,
    S,
    Q,
    \Delay6_out1_reg[23] ,
    DI,
    \Delay7_out_reg[15] ,
    Delay3_out1,
    \Delay7_out_reg[7] ,
    \Delay7_out_reg[7]_0 );
  output [15:0]D;
  output [7:0]O;
  output [7:0]Delay3_out1_reg;
  output [7:0]Delay3_out1_reg_0;
  input [23:0]Delay6_out1_reg;
  input [7:0]S;
  input [23:0]Q;
  input [23:0]\Delay6_out1_reg[23] ;
  input [6:0]DI;
  input [7:0]\Delay7_out_reg[15] ;
  input Delay3_out1;
  input \Delay7_out_reg[7] ;
  input [7:0]\Delay7_out_reg[7]_0 ;

  wire [15:0]D;
  wire [6:0]DI;
  wire Delay3_out1;
  wire [7:0]Delay3_out1_reg;
  wire [7:0]Delay3_out1_reg_0;
  wire \Delay6_out1[0]_i_10_n_0 ;
  wire \Delay6_out1[0]_i_11_n_0 ;
  wire \Delay6_out1[0]_i_12_n_0 ;
  wire \Delay6_out1[0]_i_13_n_0 ;
  wire \Delay6_out1[0]_i_14_n_0 ;
  wire \Delay6_out1[0]_i_15_n_0 ;
  wire \Delay6_out1[0]_i_16_n_0 ;
  wire \Delay6_out1[0]_i_17_n_0 ;
  wire \Delay6_out1[0]_i_2_n_0 ;
  wire \Delay6_out1[0]_i_3_n_0 ;
  wire \Delay6_out1[0]_i_4_n_0 ;
  wire \Delay6_out1[0]_i_5_n_0 ;
  wire \Delay6_out1[0]_i_6_n_0 ;
  wire \Delay6_out1[0]_i_7_n_0 ;
  wire \Delay6_out1[0]_i_8_n_0 ;
  wire \Delay6_out1[0]_i_9_n_0 ;
  wire \Delay6_out1[16]_i_10_n_0 ;
  wire \Delay6_out1[16]_i_11_n_0 ;
  wire \Delay6_out1[16]_i_12_n_0 ;
  wire \Delay6_out1[16]_i_13_n_0 ;
  wire \Delay6_out1[16]_i_14_n_0 ;
  wire \Delay6_out1[16]_i_15_n_0 ;
  wire \Delay6_out1[16]_i_16_n_0 ;
  wire \Delay6_out1[16]_i_2_n_0 ;
  wire \Delay6_out1[16]_i_3_n_0 ;
  wire \Delay6_out1[16]_i_4_n_0 ;
  wire \Delay6_out1[16]_i_5_n_0 ;
  wire \Delay6_out1[16]_i_6_n_0 ;
  wire \Delay6_out1[16]_i_7_n_0 ;
  wire \Delay6_out1[16]_i_8_n_0 ;
  wire \Delay6_out1[16]_i_9_n_0 ;
  wire \Delay6_out1[8]_i_10_n_0 ;
  wire \Delay6_out1[8]_i_11_n_0 ;
  wire \Delay6_out1[8]_i_12_n_0 ;
  wire \Delay6_out1[8]_i_13_n_0 ;
  wire \Delay6_out1[8]_i_14_n_0 ;
  wire \Delay6_out1[8]_i_15_n_0 ;
  wire \Delay6_out1[8]_i_16_n_0 ;
  wire \Delay6_out1[8]_i_17_n_0 ;
  wire \Delay6_out1[8]_i_2_n_0 ;
  wire \Delay6_out1[8]_i_3_n_0 ;
  wire \Delay6_out1[8]_i_4_n_0 ;
  wire \Delay6_out1[8]_i_5_n_0 ;
  wire \Delay6_out1[8]_i_6_n_0 ;
  wire \Delay6_out1[8]_i_7_n_0 ;
  wire \Delay6_out1[8]_i_8_n_0 ;
  wire \Delay6_out1[8]_i_9_n_0 ;
  wire [23:0]Delay6_out1_reg;
  wire \Delay6_out1_reg[0]_i_1_n_0 ;
  wire \Delay6_out1_reg[0]_i_1_n_1 ;
  wire \Delay6_out1_reg[0]_i_1_n_2 ;
  wire \Delay6_out1_reg[0]_i_1_n_3 ;
  wire \Delay6_out1_reg[0]_i_1_n_4 ;
  wire \Delay6_out1_reg[0]_i_1_n_5 ;
  wire \Delay6_out1_reg[0]_i_1_n_6 ;
  wire \Delay6_out1_reg[0]_i_1_n_7 ;
  wire \Delay6_out1_reg[16]_i_1_n_1 ;
  wire \Delay6_out1_reg[16]_i_1_n_2 ;
  wire \Delay6_out1_reg[16]_i_1_n_3 ;
  wire \Delay6_out1_reg[16]_i_1_n_4 ;
  wire \Delay6_out1_reg[16]_i_1_n_5 ;
  wire \Delay6_out1_reg[16]_i_1_n_6 ;
  wire \Delay6_out1_reg[16]_i_1_n_7 ;
  wire [23:0]\Delay6_out1_reg[23] ;
  wire \Delay6_out1_reg[8]_i_1_n_0 ;
  wire \Delay6_out1_reg[8]_i_1_n_1 ;
  wire \Delay6_out1_reg[8]_i_1_n_2 ;
  wire \Delay6_out1_reg[8]_i_1_n_3 ;
  wire \Delay6_out1_reg[8]_i_1_n_4 ;
  wire \Delay6_out1_reg[8]_i_1_n_5 ;
  wire \Delay6_out1_reg[8]_i_1_n_6 ;
  wire \Delay6_out1_reg[8]_i_1_n_7 ;
  wire [7:0]\Delay7_out_reg[15] ;
  wire \Delay7_out_reg[7] ;
  wire [7:0]\Delay7_out_reg[7]_0 ;
  wire [23:1]InternalOmega_Out_tmp0;
  wire InternalOmega_Out_tmp0_carry__0_i_1_n_0;
  wire InternalOmega_Out_tmp0_carry__0_i_2_n_0;
  wire InternalOmega_Out_tmp0_carry__0_i_3_n_0;
  wire InternalOmega_Out_tmp0_carry__0_i_4_n_0;
  wire InternalOmega_Out_tmp0_carry__0_i_5_n_0;
  wire InternalOmega_Out_tmp0_carry__0_i_6_n_0;
  wire InternalOmega_Out_tmp0_carry__0_i_7_n_0;
  wire InternalOmega_Out_tmp0_carry__0_i_8_n_0;
  wire InternalOmega_Out_tmp0_carry__0_n_0;
  wire InternalOmega_Out_tmp0_carry__0_n_1;
  wire InternalOmega_Out_tmp0_carry__0_n_2;
  wire InternalOmega_Out_tmp0_carry__0_n_3;
  wire InternalOmega_Out_tmp0_carry__0_n_4;
  wire InternalOmega_Out_tmp0_carry__0_n_5;
  wire InternalOmega_Out_tmp0_carry__0_n_6;
  wire InternalOmega_Out_tmp0_carry__0_n_7;
  wire InternalOmega_Out_tmp0_carry__1_n_1;
  wire InternalOmega_Out_tmp0_carry__1_n_2;
  wire InternalOmega_Out_tmp0_carry__1_n_3;
  wire InternalOmega_Out_tmp0_carry__1_n_4;
  wire InternalOmega_Out_tmp0_carry__1_n_5;
  wire InternalOmega_Out_tmp0_carry__1_n_6;
  wire InternalOmega_Out_tmp0_carry__1_n_7;
  wire InternalOmega_Out_tmp0_carry_i_1_n_0;
  wire InternalOmega_Out_tmp0_carry_i_2_n_0;
  wire InternalOmega_Out_tmp0_carry_i_3_n_0;
  wire InternalOmega_Out_tmp0_carry_i_4_n_0;
  wire InternalOmega_Out_tmp0_carry_i_5_n_0;
  wire InternalOmega_Out_tmp0_carry_i_6_n_0;
  wire InternalOmega_Out_tmp0_carry_i_7_n_0;
  wire InternalOmega_Out_tmp0_carry_i_8_n_0;
  wire InternalOmega_Out_tmp0_carry_n_0;
  wire InternalOmega_Out_tmp0_carry_n_1;
  wire InternalOmega_Out_tmp0_carry_n_2;
  wire InternalOmega_Out_tmp0_carry_n_3;
  wire InternalOmega_Out_tmp0_carry_n_4;
  wire InternalOmega_Out_tmp0_carry_n_5;
  wire InternalOmega_Out_tmp0_carry_n_6;
  wire InternalOmega_Out_tmp0_carry_n_7;
  wire [7:0]O;
  wire [23:0]Q;
  wire [7:0]S;
  wire \_inferred__1/i___71_carry__0_n_0 ;
  wire \_inferred__1/i___71_carry__0_n_1 ;
  wire \_inferred__1/i___71_carry__0_n_2 ;
  wire \_inferred__1/i___71_carry__0_n_3 ;
  wire \_inferred__1/i___71_carry__0_n_4 ;
  wire \_inferred__1/i___71_carry__0_n_5 ;
  wire \_inferred__1/i___71_carry__0_n_6 ;
  wire \_inferred__1/i___71_carry__0_n_7 ;
  wire \_inferred__1/i___71_carry__1_n_0 ;
  wire \_inferred__1/i___71_carry__1_n_1 ;
  wire \_inferred__1/i___71_carry__1_n_2 ;
  wire \_inferred__1/i___71_carry__1_n_3 ;
  wire \_inferred__1/i___71_carry__1_n_4 ;
  wire \_inferred__1/i___71_carry__1_n_5 ;
  wire \_inferred__1/i___71_carry__1_n_6 ;
  wire \_inferred__1/i___71_carry__1_n_7 ;
  wire \_inferred__1/i___71_carry__2_n_7 ;
  wire \_inferred__1/i___71_carry_n_0 ;
  wire \_inferred__1/i___71_carry_n_1 ;
  wire \_inferred__1/i___71_carry_n_2 ;
  wire \_inferred__1/i___71_carry_n_3 ;
  wire \_inferred__1/i___71_carry_n_4 ;
  wire \_inferred__1/i___71_carry_n_5 ;
  wire \_inferred__1/i___71_carry_n_6 ;
  wire \_inferred__1/i___71_carry_n_7 ;
  wire \_inferred__1/i__carry__0_n_0 ;
  wire \_inferred__1/i__carry__0_n_1 ;
  wire \_inferred__1/i__carry__0_n_2 ;
  wire \_inferred__1/i__carry__0_n_3 ;
  wire \_inferred__1/i__carry__0_n_4 ;
  wire \_inferred__1/i__carry__0_n_5 ;
  wire \_inferred__1/i__carry__0_n_6 ;
  wire \_inferred__1/i__carry__0_n_7 ;
  wire \_inferred__1/i__carry__1_n_0 ;
  wire \_inferred__1/i__carry__1_n_1 ;
  wire \_inferred__1/i__carry__1_n_2 ;
  wire \_inferred__1/i__carry__1_n_3 ;
  wire \_inferred__1/i__carry__1_n_4 ;
  wire \_inferred__1/i__carry__1_n_5 ;
  wire \_inferred__1/i__carry__1_n_6 ;
  wire \_inferred__1/i__carry__1_n_7 ;
  wire \_inferred__1/i__carry_n_0 ;
  wire \_inferred__1/i__carry_n_1 ;
  wire \_inferred__1/i__carry_n_2 ;
  wire \_inferred__1/i__carry_n_3 ;
  wire \_inferred__1/i__carry_n_4 ;
  wire \_inferred__1/i__carry_n_5 ;
  wire \_inferred__1/i__carry_n_6 ;
  wire \_inferred__1/i__carry_n_7 ;
  wire [23:0]arg0;
  wire [23:0]arg0_0;
  wire arg0_carry__0_i_1_n_0;
  wire arg0_carry__0_i_2_n_0;
  wire arg0_carry__0_i_3_n_0;
  wire arg0_carry__0_i_4_n_0;
  wire arg0_carry__0_i_5_n_0;
  wire arg0_carry__0_i_6_n_0;
  wire arg0_carry__0_i_7_n_0;
  wire arg0_carry__0_i_8_n_0;
  wire arg0_carry__0_n_0;
  wire arg0_carry__0_n_1;
  wire arg0_carry__0_n_2;
  wire arg0_carry__0_n_3;
  wire arg0_carry__0_n_4;
  wire arg0_carry__0_n_5;
  wire arg0_carry__0_n_6;
  wire arg0_carry__0_n_7;
  wire arg0_carry__1_i_1_n_0;
  wire arg0_carry__1_i_2_n_0;
  wire arg0_carry__1_i_3_n_0;
  wire arg0_carry__1_i_4_n_0;
  wire arg0_carry__1_i_5_n_0;
  wire arg0_carry__1_i_6_n_0;
  wire arg0_carry__1_i_7_n_0;
  wire arg0_carry__1_i_8_n_0;
  wire arg0_carry__1_n_0;
  wire arg0_carry__1_n_1;
  wire arg0_carry__1_n_2;
  wire arg0_carry__1_n_3;
  wire arg0_carry__1_n_4;
  wire arg0_carry__1_n_5;
  wire arg0_carry__1_n_6;
  wire arg0_carry__1_n_7;
  wire arg0_carry_i_1_n_0;
  wire arg0_carry_i_2_n_0;
  wire arg0_carry_i_3_n_0;
  wire arg0_carry_i_4_n_0;
  wire arg0_carry_i_5_n_0;
  wire arg0_carry_i_6_n_0;
  wire arg0_carry_i_7_n_0;
  wire arg0_carry_i_8_n_0;
  wire arg0_carry_n_0;
  wire arg0_carry_n_1;
  wire arg0_carry_n_2;
  wire arg0_carry_n_3;
  wire arg0_carry_n_4;
  wire arg0_carry_n_5;
  wire arg0_carry_n_6;
  wire arg0_carry_n_7;
  wire arg_carry__0_i_10_n_0;
  wire arg_carry__0_i_11_n_7;
  wire arg_carry__0_i_1_n_0;
  wire arg_carry__0_i_2_n_0;
  wire arg_carry__0_i_3_n_0;
  wire arg_carry__0_i_4_n_0;
  wire arg_carry__0_i_5_n_0;
  wire arg_carry__0_i_6_n_0;
  wire arg_carry__0_i_7_n_0;
  wire arg_carry__0_i_8_n_0;
  wire arg_carry__0_i_9_n_0;
  wire arg_carry__0_n_4;
  wire arg_carry__0_n_5;
  wire arg_carry__0_n_6;
  wire arg_carry__0_n_7;
  wire arg_carry_i_10_n_0;
  wire arg_carry_i_11_n_0;
  wire arg_carry_i_12_n_0;
  wire arg_carry_i_13_n_0;
  wire arg_carry_i_14_n_0;
  wire arg_carry_i_15_n_0;
  wire arg_carry_i_16_n_0;
  wire arg_carry_i_1_n_0;
  wire arg_carry_i_2_n_0;
  wire arg_carry_i_3_n_0;
  wire arg_carry_i_4_n_0;
  wire arg_carry_i_5_n_0;
  wire arg_carry_i_6_n_0;
  wire arg_carry_i_7_n_0;
  wire arg_carry_i_8_n_0;
  wire arg_carry_i_9_n_0;
  wire arg_carry_n_0;
  wire arg_carry_n_1;
  wire arg_carry_n_2;
  wire arg_carry_n_3;
  wire arg_carry_n_4;
  wire arg_carry_n_5;
  wire arg_carry_n_6;
  wire arg_carry_n_7;
  wire hdlcoder_to_stdlogic;
  wire i___71_carry__0_i_1_n_0;
  wire i___71_carry__0_i_2_n_0;
  wire i___71_carry__0_i_3_n_0;
  wire i___71_carry__0_i_4_n_0;
  wire i___71_carry__0_i_5_n_0;
  wire i___71_carry__0_i_6_n_0;
  wire i___71_carry__0_i_7_n_0;
  wire i___71_carry__0_i_8_n_0;
  wire i___71_carry__1_i_1_n_0;
  wire i___71_carry__1_i_2_n_0;
  wire i___71_carry__1_i_3_n_0;
  wire i___71_carry__1_i_4_n_0;
  wire i___71_carry__1_i_5_n_0;
  wire i___71_carry__1_i_6_n_0;
  wire i___71_carry__1_i_7_n_0;
  wire i___71_carry__1_i_8_n_0;
  wire i___71_carry__2_i_1_n_0;
  wire i___71_carry__2_i_2_n_7;
  wire i___71_carry_i_1_n_0;
  wire i___71_carry_i_2_n_0;
  wire i___71_carry_i_3_n_0;
  wire i___71_carry_i_4_n_0;
  wire i___71_carry_i_5_n_0;
  wire i___71_carry_i_6_n_0;
  wire i___71_carry_i_7_n_0;
  wire i___71_carry_i_8_n_0;
  wire i__carry__0_i_1_n_0;
  wire i__carry__0_i_2_n_0;
  wire i__carry__0_i_3_n_0;
  wire i__carry__0_i_4_n_0;
  wire i__carry__0_i_5_n_0;
  wire i__carry__0_i_6_n_0;
  wire i__carry__0_i_7_n_0;
  wire i__carry__0_i_8_n_0;
  wire i__carry__1_i_1_n_0;
  wire i__carry__1_i_2_n_0;
  wire i__carry__1_i_3_n_0;
  wire i__carry__1_i_4_n_0;
  wire i__carry__1_i_5_n_0;
  wire i__carry__1_i_6_n_0;
  wire i__carry__1_i_7_n_0;
  wire i__carry__1_i_8_n_0;
  wire i__carry__1_i_9_n_0;
  wire i__carry_i_1_n_0;
  wire i__carry_i_2_n_0;
  wire i__carry_i_3_n_0;
  wire i__carry_i_4_n_0;
  wire i__carry_i_5_n_0;
  wire i__carry_i_6_n_0;
  wire i__carry_i_7_n_0;
  wire i__carry_i_8_n_0;
  wire state_Out_tmp0_carry__0_n_1;
  wire state_Out_tmp0_carry__0_n_2;
  wire state_Out_tmp0_carry__0_n_3;
  wire state_Out_tmp0_carry__0_n_4;
  wire state_Out_tmp0_carry__0_n_5;
  wire state_Out_tmp0_carry__0_n_6;
  wire state_Out_tmp0_carry__0_n_7;
  wire state_Out_tmp0_carry_i_10_n_0;
  wire state_Out_tmp0_carry_i_11_n_0;
  wire state_Out_tmp0_carry_i_12_n_0;
  wire state_Out_tmp0_carry_i_13_n_0;
  wire state_Out_tmp0_carry_i_14_n_0;
  wire state_Out_tmp0_carry_i_15_n_0;
  wire state_Out_tmp0_carry_i_16_n_0;
  wire state_Out_tmp0_carry_i_1_n_0;
  wire state_Out_tmp0_carry_i_2_n_0;
  wire state_Out_tmp0_carry_i_3_n_0;
  wire state_Out_tmp0_carry_i_4_n_0;
  wire state_Out_tmp0_carry_i_5_n_0;
  wire state_Out_tmp0_carry_i_6_n_0;
  wire state_Out_tmp0_carry_i_7_n_0;
  wire state_Out_tmp0_carry_i_8_n_0;
  wire state_Out_tmp0_carry_i_9_n_0;
  wire state_Out_tmp0_carry_n_0;
  wire state_Out_tmp0_carry_n_1;
  wire state_Out_tmp0_carry_n_2;
  wire state_Out_tmp0_carry_n_3;
  wire state_Out_tmp0_carry_n_4;
  wire state_Out_tmp0_carry_n_5;
  wire state_Out_tmp0_carry_n_6;
  wire state_Out_tmp0_carry_n_7;
  wire [7:7]\NLW_Delay6_out1_reg[16]_i_1_CO_UNCONNECTED ;
  wire [7:7]NLW_InternalOmega_Out_tmp0_carry__1_CO_UNCONNECTED;
  wire [7:0]\NLW__inferred__1/i___71_carry_O_UNCONNECTED ;
  wire [7:0]\NLW__inferred__1/i___71_carry__0_O_UNCONNECTED ;
  wire [7:0]\NLW__inferred__1/i___71_carry__1_O_UNCONNECTED ;
  wire [7:1]\NLW__inferred__1/i___71_carry__2_CO_UNCONNECTED ;
  wire [7:0]\NLW__inferred__1/i___71_carry__2_O_UNCONNECTED ;
  wire [0:0]NLW_arg0_carry_O_UNCONNECTED;
  wire [7:0]NLW_arg_carry_O_UNCONNECTED;
  wire [7:5]NLW_arg_carry__0_CO_UNCONNECTED;
  wire [7:0]NLW_arg_carry__0_O_UNCONNECTED;
  wire [7:1]NLW_arg_carry__0_i_11_CO_UNCONNECTED;
  wire [7:0]NLW_arg_carry__0_i_11_O_UNCONNECTED;
  wire [7:1]NLW_i___71_carry__2_i_2_CO_UNCONNECTED;
  wire [7:0]NLW_i___71_carry__2_i_2_O_UNCONNECTED;
  wire [7:7]NLW_state_Out_tmp0_carry__0_CO_UNCONNECTED;

  LUT6 #(
    .INIT(64'hC5F5FFFFCA0A0000)) 
    \Delay6_out1[0]_i_10 
       (.I0(\Delay6_out1_reg[23] [7]),
        .I1(InternalOmega_Out_tmp0[7]),
        .I2(\_inferred__1/i___71_carry__2_n_7 ),
        .I3(hdlcoder_to_stdlogic),
        .I4(Delay3_out1),
        .I5(Delay6_out1_reg[7]),
        .O(\Delay6_out1[0]_i_10_n_0 ));
  LUT6 #(
    .INIT(64'hC5F5FFFFCA0A0000)) 
    \Delay6_out1[0]_i_11 
       (.I0(\Delay6_out1_reg[23] [6]),
        .I1(InternalOmega_Out_tmp0[6]),
        .I2(\_inferred__1/i___71_carry__2_n_7 ),
        .I3(hdlcoder_to_stdlogic),
        .I4(Delay3_out1),
        .I5(Delay6_out1_reg[6]),
        .O(\Delay6_out1[0]_i_11_n_0 ));
  LUT6 #(
    .INIT(64'hC5F5FFFFCA0A0000)) 
    \Delay6_out1[0]_i_12 
       (.I0(\Delay6_out1_reg[23] [5]),
        .I1(InternalOmega_Out_tmp0[5]),
        .I2(\_inferred__1/i___71_carry__2_n_7 ),
        .I3(hdlcoder_to_stdlogic),
        .I4(Delay3_out1),
        .I5(Delay6_out1_reg[5]),
        .O(\Delay6_out1[0]_i_12_n_0 ));
  LUT6 #(
    .INIT(64'hC5F5FFFFCA0A0000)) 
    \Delay6_out1[0]_i_13 
       (.I0(\Delay6_out1_reg[23] [4]),
        .I1(InternalOmega_Out_tmp0[4]),
        .I2(\_inferred__1/i___71_carry__2_n_7 ),
        .I3(hdlcoder_to_stdlogic),
        .I4(Delay3_out1),
        .I5(Delay6_out1_reg[4]),
        .O(\Delay6_out1[0]_i_13_n_0 ));
  LUT6 #(
    .INIT(64'hC5F5FFFFCA0A0000)) 
    \Delay6_out1[0]_i_14 
       (.I0(\Delay6_out1_reg[23] [3]),
        .I1(InternalOmega_Out_tmp0[3]),
        .I2(\_inferred__1/i___71_carry__2_n_7 ),
        .I3(hdlcoder_to_stdlogic),
        .I4(Delay3_out1),
        .I5(Delay6_out1_reg[3]),
        .O(\Delay6_out1[0]_i_14_n_0 ));
  LUT6 #(
    .INIT(64'hC5F5FFFFCA0A0000)) 
    \Delay6_out1[0]_i_15 
       (.I0(\Delay6_out1_reg[23] [2]),
        .I1(InternalOmega_Out_tmp0[2]),
        .I2(\_inferred__1/i___71_carry__2_n_7 ),
        .I3(hdlcoder_to_stdlogic),
        .I4(Delay3_out1),
        .I5(Delay6_out1_reg[2]),
        .O(\Delay6_out1[0]_i_15_n_0 ));
  LUT6 #(
    .INIT(64'hC5F5FFFFCA0A0000)) 
    \Delay6_out1[0]_i_16 
       (.I0(\Delay6_out1_reg[23] [1]),
        .I1(InternalOmega_Out_tmp0[1]),
        .I2(\_inferred__1/i___71_carry__2_n_7 ),
        .I3(hdlcoder_to_stdlogic),
        .I4(Delay3_out1),
        .I5(Delay6_out1_reg[1]),
        .O(\Delay6_out1[0]_i_16_n_0 ));
  LUT5 #(
    .INIT(32'h66A6AAAA)) 
    \Delay6_out1[0]_i_17 
       (.I0(Delay6_out1_reg[0]),
        .I1(\Delay6_out1_reg[23] [0]),
        .I2(\_inferred__1/i___71_carry__2_n_7 ),
        .I3(hdlcoder_to_stdlogic),
        .I4(Delay3_out1),
        .O(\Delay6_out1[0]_i_17_n_0 ));
  LUT3 #(
    .INIT(8'h40)) 
    \Delay6_out1[0]_i_2 
       (.I0(\_inferred__1/i___71_carry__2_n_7 ),
        .I1(Delay3_out1),
        .I2(\Delay6_out1_reg[23] [7]),
        .O(\Delay6_out1[0]_i_2_n_0 ));
  LUT3 #(
    .INIT(8'h40)) 
    \Delay6_out1[0]_i_3 
       (.I0(\_inferred__1/i___71_carry__2_n_7 ),
        .I1(Delay3_out1),
        .I2(\Delay6_out1_reg[23] [6]),
        .O(\Delay6_out1[0]_i_3_n_0 ));
  LUT3 #(
    .INIT(8'h40)) 
    \Delay6_out1[0]_i_4 
       (.I0(\_inferred__1/i___71_carry__2_n_7 ),
        .I1(Delay3_out1),
        .I2(\Delay6_out1_reg[23] [5]),
        .O(\Delay6_out1[0]_i_4_n_0 ));
  LUT3 #(
    .INIT(8'h40)) 
    \Delay6_out1[0]_i_5 
       (.I0(\_inferred__1/i___71_carry__2_n_7 ),
        .I1(Delay3_out1),
        .I2(\Delay6_out1_reg[23] [4]),
        .O(\Delay6_out1[0]_i_5_n_0 ));
  LUT3 #(
    .INIT(8'h40)) 
    \Delay6_out1[0]_i_6 
       (.I0(\_inferred__1/i___71_carry__2_n_7 ),
        .I1(Delay3_out1),
        .I2(\Delay6_out1_reg[23] [3]),
        .O(\Delay6_out1[0]_i_6_n_0 ));
  LUT3 #(
    .INIT(8'h40)) 
    \Delay6_out1[0]_i_7 
       (.I0(\_inferred__1/i___71_carry__2_n_7 ),
        .I1(Delay3_out1),
        .I2(\Delay6_out1_reg[23] [2]),
        .O(\Delay6_out1[0]_i_7_n_0 ));
  LUT3 #(
    .INIT(8'h40)) 
    \Delay6_out1[0]_i_8 
       (.I0(\_inferred__1/i___71_carry__2_n_7 ),
        .I1(Delay3_out1),
        .I2(\Delay6_out1_reg[23] [1]),
        .O(\Delay6_out1[0]_i_8_n_0 ));
  LUT3 #(
    .INIT(8'h40)) 
    \Delay6_out1[0]_i_9 
       (.I0(\_inferred__1/i___71_carry__2_n_7 ),
        .I1(Delay3_out1),
        .I2(\Delay6_out1_reg[23] [0]),
        .O(\Delay6_out1[0]_i_9_n_0 ));
  LUT6 #(
    .INIT(64'hC5F5FFFFCA0A0000)) 
    \Delay6_out1[16]_i_10 
       (.I0(\Delay6_out1_reg[23] [22]),
        .I1(InternalOmega_Out_tmp0[22]),
        .I2(\_inferred__1/i___71_carry__2_n_7 ),
        .I3(hdlcoder_to_stdlogic),
        .I4(Delay3_out1),
        .I5(Delay6_out1_reg[22]),
        .O(\Delay6_out1[16]_i_10_n_0 ));
  LUT6 #(
    .INIT(64'hC5F5FFFFCA0A0000)) 
    \Delay6_out1[16]_i_11 
       (.I0(\Delay6_out1_reg[23] [21]),
        .I1(InternalOmega_Out_tmp0[21]),
        .I2(\_inferred__1/i___71_carry__2_n_7 ),
        .I3(hdlcoder_to_stdlogic),
        .I4(Delay3_out1),
        .I5(Delay6_out1_reg[21]),
        .O(\Delay6_out1[16]_i_11_n_0 ));
  LUT6 #(
    .INIT(64'hC5F5FFFFCA0A0000)) 
    \Delay6_out1[16]_i_12 
       (.I0(\Delay6_out1_reg[23] [20]),
        .I1(InternalOmega_Out_tmp0[20]),
        .I2(\_inferred__1/i___71_carry__2_n_7 ),
        .I3(hdlcoder_to_stdlogic),
        .I4(Delay3_out1),
        .I5(Delay6_out1_reg[20]),
        .O(\Delay6_out1[16]_i_12_n_0 ));
  LUT6 #(
    .INIT(64'hC5F5FFFFCA0A0000)) 
    \Delay6_out1[16]_i_13 
       (.I0(\Delay6_out1_reg[23] [19]),
        .I1(InternalOmega_Out_tmp0[19]),
        .I2(\_inferred__1/i___71_carry__2_n_7 ),
        .I3(hdlcoder_to_stdlogic),
        .I4(Delay3_out1),
        .I5(Delay6_out1_reg[19]),
        .O(\Delay6_out1[16]_i_13_n_0 ));
  LUT6 #(
    .INIT(64'hC5F5FFFFCA0A0000)) 
    \Delay6_out1[16]_i_14 
       (.I0(\Delay6_out1_reg[23] [18]),
        .I1(InternalOmega_Out_tmp0[18]),
        .I2(\_inferred__1/i___71_carry__2_n_7 ),
        .I3(hdlcoder_to_stdlogic),
        .I4(Delay3_out1),
        .I5(Delay6_out1_reg[18]),
        .O(\Delay6_out1[16]_i_14_n_0 ));
  LUT6 #(
    .INIT(64'hC5F5FFFFCA0A0000)) 
    \Delay6_out1[16]_i_15 
       (.I0(\Delay6_out1_reg[23] [17]),
        .I1(InternalOmega_Out_tmp0[17]),
        .I2(\_inferred__1/i___71_carry__2_n_7 ),
        .I3(hdlcoder_to_stdlogic),
        .I4(Delay3_out1),
        .I5(Delay6_out1_reg[17]),
        .O(\Delay6_out1[16]_i_15_n_0 ));
  LUT6 #(
    .INIT(64'hC5F5FFFFCA0A0000)) 
    \Delay6_out1[16]_i_16 
       (.I0(\Delay6_out1_reg[23] [16]),
        .I1(InternalOmega_Out_tmp0[16]),
        .I2(\_inferred__1/i___71_carry__2_n_7 ),
        .I3(hdlcoder_to_stdlogic),
        .I4(Delay3_out1),
        .I5(Delay6_out1_reg[16]),
        .O(\Delay6_out1[16]_i_16_n_0 ));
  LUT3 #(
    .INIT(8'h40)) 
    \Delay6_out1[16]_i_2 
       (.I0(\_inferred__1/i___71_carry__2_n_7 ),
        .I1(Delay3_out1),
        .I2(\Delay6_out1_reg[23] [22]),
        .O(\Delay6_out1[16]_i_2_n_0 ));
  LUT3 #(
    .INIT(8'h40)) 
    \Delay6_out1[16]_i_3 
       (.I0(\_inferred__1/i___71_carry__2_n_7 ),
        .I1(Delay3_out1),
        .I2(\Delay6_out1_reg[23] [21]),
        .O(\Delay6_out1[16]_i_3_n_0 ));
  LUT3 #(
    .INIT(8'h40)) 
    \Delay6_out1[16]_i_4 
       (.I0(\_inferred__1/i___71_carry__2_n_7 ),
        .I1(Delay3_out1),
        .I2(\Delay6_out1_reg[23] [20]),
        .O(\Delay6_out1[16]_i_4_n_0 ));
  LUT3 #(
    .INIT(8'h40)) 
    \Delay6_out1[16]_i_5 
       (.I0(\_inferred__1/i___71_carry__2_n_7 ),
        .I1(Delay3_out1),
        .I2(\Delay6_out1_reg[23] [19]),
        .O(\Delay6_out1[16]_i_5_n_0 ));
  LUT3 #(
    .INIT(8'h40)) 
    \Delay6_out1[16]_i_6 
       (.I0(\_inferred__1/i___71_carry__2_n_7 ),
        .I1(Delay3_out1),
        .I2(\Delay6_out1_reg[23] [18]),
        .O(\Delay6_out1[16]_i_6_n_0 ));
  LUT3 #(
    .INIT(8'h40)) 
    \Delay6_out1[16]_i_7 
       (.I0(\_inferred__1/i___71_carry__2_n_7 ),
        .I1(Delay3_out1),
        .I2(\Delay6_out1_reg[23] [17]),
        .O(\Delay6_out1[16]_i_7_n_0 ));
  LUT3 #(
    .INIT(8'h40)) 
    \Delay6_out1[16]_i_8 
       (.I0(\_inferred__1/i___71_carry__2_n_7 ),
        .I1(Delay3_out1),
        .I2(\Delay6_out1_reg[23] [16]),
        .O(\Delay6_out1[16]_i_8_n_0 ));
  LUT6 #(
    .INIT(64'hC5F5FFFFCA0A0000)) 
    \Delay6_out1[16]_i_9 
       (.I0(\Delay6_out1_reg[23] [23]),
        .I1(InternalOmega_Out_tmp0[23]),
        .I2(\_inferred__1/i___71_carry__2_n_7 ),
        .I3(hdlcoder_to_stdlogic),
        .I4(Delay3_out1),
        .I5(Delay6_out1_reg[23]),
        .O(\Delay6_out1[16]_i_9_n_0 ));
  LUT6 #(
    .INIT(64'hC5F5FFFFCA0A0000)) 
    \Delay6_out1[8]_i_10 
       (.I0(\Delay6_out1_reg[23] [15]),
        .I1(InternalOmega_Out_tmp0[15]),
        .I2(\_inferred__1/i___71_carry__2_n_7 ),
        .I3(hdlcoder_to_stdlogic),
        .I4(Delay3_out1),
        .I5(Delay6_out1_reg[15]),
        .O(\Delay6_out1[8]_i_10_n_0 ));
  LUT6 #(
    .INIT(64'hC5F5FFFFCA0A0000)) 
    \Delay6_out1[8]_i_11 
       (.I0(\Delay6_out1_reg[23] [14]),
        .I1(InternalOmega_Out_tmp0[14]),
        .I2(\_inferred__1/i___71_carry__2_n_7 ),
        .I3(hdlcoder_to_stdlogic),
        .I4(Delay3_out1),
        .I5(Delay6_out1_reg[14]),
        .O(\Delay6_out1[8]_i_11_n_0 ));
  LUT6 #(
    .INIT(64'hC5F5FFFFCA0A0000)) 
    \Delay6_out1[8]_i_12 
       (.I0(\Delay6_out1_reg[23] [13]),
        .I1(InternalOmega_Out_tmp0[13]),
        .I2(\_inferred__1/i___71_carry__2_n_7 ),
        .I3(hdlcoder_to_stdlogic),
        .I4(Delay3_out1),
        .I5(Delay6_out1_reg[13]),
        .O(\Delay6_out1[8]_i_12_n_0 ));
  LUT6 #(
    .INIT(64'hC5F5FFFFCA0A0000)) 
    \Delay6_out1[8]_i_13 
       (.I0(\Delay6_out1_reg[23] [12]),
        .I1(InternalOmega_Out_tmp0[12]),
        .I2(\_inferred__1/i___71_carry__2_n_7 ),
        .I3(hdlcoder_to_stdlogic),
        .I4(Delay3_out1),
        .I5(Delay6_out1_reg[12]),
        .O(\Delay6_out1[8]_i_13_n_0 ));
  LUT6 #(
    .INIT(64'hC5F5FFFFCA0A0000)) 
    \Delay6_out1[8]_i_14 
       (.I0(\Delay6_out1_reg[23] [11]),
        .I1(InternalOmega_Out_tmp0[11]),
        .I2(\_inferred__1/i___71_carry__2_n_7 ),
        .I3(hdlcoder_to_stdlogic),
        .I4(Delay3_out1),
        .I5(Delay6_out1_reg[11]),
        .O(\Delay6_out1[8]_i_14_n_0 ));
  LUT6 #(
    .INIT(64'hC5F5FFFFCA0A0000)) 
    \Delay6_out1[8]_i_15 
       (.I0(\Delay6_out1_reg[23] [10]),
        .I1(InternalOmega_Out_tmp0[10]),
        .I2(\_inferred__1/i___71_carry__2_n_7 ),
        .I3(hdlcoder_to_stdlogic),
        .I4(Delay3_out1),
        .I5(Delay6_out1_reg[10]),
        .O(\Delay6_out1[8]_i_15_n_0 ));
  LUT6 #(
    .INIT(64'hC5F5FFFFCA0A0000)) 
    \Delay6_out1[8]_i_16 
       (.I0(\Delay6_out1_reg[23] [9]),
        .I1(InternalOmega_Out_tmp0[9]),
        .I2(\_inferred__1/i___71_carry__2_n_7 ),
        .I3(hdlcoder_to_stdlogic),
        .I4(Delay3_out1),
        .I5(Delay6_out1_reg[9]),
        .O(\Delay6_out1[8]_i_16_n_0 ));
  LUT6 #(
    .INIT(64'hC5F5FFFFCA0A0000)) 
    \Delay6_out1[8]_i_17 
       (.I0(\Delay6_out1_reg[23] [8]),
        .I1(InternalOmega_Out_tmp0[8]),
        .I2(\_inferred__1/i___71_carry__2_n_7 ),
        .I3(hdlcoder_to_stdlogic),
        .I4(Delay3_out1),
        .I5(Delay6_out1_reg[8]),
        .O(\Delay6_out1[8]_i_17_n_0 ));
  LUT3 #(
    .INIT(8'h40)) 
    \Delay6_out1[8]_i_2 
       (.I0(\_inferred__1/i___71_carry__2_n_7 ),
        .I1(Delay3_out1),
        .I2(\Delay6_out1_reg[23] [15]),
        .O(\Delay6_out1[8]_i_2_n_0 ));
  LUT3 #(
    .INIT(8'h40)) 
    \Delay6_out1[8]_i_3 
       (.I0(\_inferred__1/i___71_carry__2_n_7 ),
        .I1(Delay3_out1),
        .I2(\Delay6_out1_reg[23] [14]),
        .O(\Delay6_out1[8]_i_3_n_0 ));
  LUT3 #(
    .INIT(8'h40)) 
    \Delay6_out1[8]_i_4 
       (.I0(\_inferred__1/i___71_carry__2_n_7 ),
        .I1(Delay3_out1),
        .I2(\Delay6_out1_reg[23] [13]),
        .O(\Delay6_out1[8]_i_4_n_0 ));
  LUT3 #(
    .INIT(8'h40)) 
    \Delay6_out1[8]_i_5 
       (.I0(\_inferred__1/i___71_carry__2_n_7 ),
        .I1(Delay3_out1),
        .I2(\Delay6_out1_reg[23] [12]),
        .O(\Delay6_out1[8]_i_5_n_0 ));
  LUT3 #(
    .INIT(8'h40)) 
    \Delay6_out1[8]_i_6 
       (.I0(\_inferred__1/i___71_carry__2_n_7 ),
        .I1(Delay3_out1),
        .I2(\Delay6_out1_reg[23] [11]),
        .O(\Delay6_out1[8]_i_6_n_0 ));
  LUT3 #(
    .INIT(8'h40)) 
    \Delay6_out1[8]_i_7 
       (.I0(\_inferred__1/i___71_carry__2_n_7 ),
        .I1(Delay3_out1),
        .I2(\Delay6_out1_reg[23] [10]),
        .O(\Delay6_out1[8]_i_7_n_0 ));
  LUT3 #(
    .INIT(8'h40)) 
    \Delay6_out1[8]_i_8 
       (.I0(\_inferred__1/i___71_carry__2_n_7 ),
        .I1(Delay3_out1),
        .I2(\Delay6_out1_reg[23] [9]),
        .O(\Delay6_out1[8]_i_8_n_0 ));
  LUT3 #(
    .INIT(8'h40)) 
    \Delay6_out1[8]_i_9 
       (.I0(\_inferred__1/i___71_carry__2_n_7 ),
        .I1(Delay3_out1),
        .I2(\Delay6_out1_reg[23] [8]),
        .O(\Delay6_out1[8]_i_9_n_0 ));
  (* ADDER_THRESHOLD = "16" *) 
  CARRY8 \Delay6_out1_reg[0]_i_1 
       (.CI(1'b0),
        .CI_TOP(1'b0),
        .CO({\Delay6_out1_reg[0]_i_1_n_0 ,\Delay6_out1_reg[0]_i_1_n_1 ,\Delay6_out1_reg[0]_i_1_n_2 ,\Delay6_out1_reg[0]_i_1_n_3 ,\Delay6_out1_reg[0]_i_1_n_4 ,\Delay6_out1_reg[0]_i_1_n_5 ,\Delay6_out1_reg[0]_i_1_n_6 ,\Delay6_out1_reg[0]_i_1_n_7 }),
        .DI({\Delay6_out1[0]_i_2_n_0 ,\Delay6_out1[0]_i_3_n_0 ,\Delay6_out1[0]_i_4_n_0 ,\Delay6_out1[0]_i_5_n_0 ,\Delay6_out1[0]_i_6_n_0 ,\Delay6_out1[0]_i_7_n_0 ,\Delay6_out1[0]_i_8_n_0 ,\Delay6_out1[0]_i_9_n_0 }),
        .O(O),
        .S({\Delay6_out1[0]_i_10_n_0 ,\Delay6_out1[0]_i_11_n_0 ,\Delay6_out1[0]_i_12_n_0 ,\Delay6_out1[0]_i_13_n_0 ,\Delay6_out1[0]_i_14_n_0 ,\Delay6_out1[0]_i_15_n_0 ,\Delay6_out1[0]_i_16_n_0 ,\Delay6_out1[0]_i_17_n_0 }));
  (* ADDER_THRESHOLD = "16" *) 
  CARRY8 \Delay6_out1_reg[16]_i_1 
       (.CI(\Delay6_out1_reg[8]_i_1_n_0 ),
        .CI_TOP(1'b0),
        .CO({\NLW_Delay6_out1_reg[16]_i_1_CO_UNCONNECTED [7],\Delay6_out1_reg[16]_i_1_n_1 ,\Delay6_out1_reg[16]_i_1_n_2 ,\Delay6_out1_reg[16]_i_1_n_3 ,\Delay6_out1_reg[16]_i_1_n_4 ,\Delay6_out1_reg[16]_i_1_n_5 ,\Delay6_out1_reg[16]_i_1_n_6 ,\Delay6_out1_reg[16]_i_1_n_7 }),
        .DI({1'b0,\Delay6_out1[16]_i_2_n_0 ,\Delay6_out1[16]_i_3_n_0 ,\Delay6_out1[16]_i_4_n_0 ,\Delay6_out1[16]_i_5_n_0 ,\Delay6_out1[16]_i_6_n_0 ,\Delay6_out1[16]_i_7_n_0 ,\Delay6_out1[16]_i_8_n_0 }),
        .O(Delay3_out1_reg_0),
        .S({\Delay6_out1[16]_i_9_n_0 ,\Delay6_out1[16]_i_10_n_0 ,\Delay6_out1[16]_i_11_n_0 ,\Delay6_out1[16]_i_12_n_0 ,\Delay6_out1[16]_i_13_n_0 ,\Delay6_out1[16]_i_14_n_0 ,\Delay6_out1[16]_i_15_n_0 ,\Delay6_out1[16]_i_16_n_0 }));
  (* ADDER_THRESHOLD = "16" *) 
  CARRY8 \Delay6_out1_reg[8]_i_1 
       (.CI(\Delay6_out1_reg[0]_i_1_n_0 ),
        .CI_TOP(1'b0),
        .CO({\Delay6_out1_reg[8]_i_1_n_0 ,\Delay6_out1_reg[8]_i_1_n_1 ,\Delay6_out1_reg[8]_i_1_n_2 ,\Delay6_out1_reg[8]_i_1_n_3 ,\Delay6_out1_reg[8]_i_1_n_4 ,\Delay6_out1_reg[8]_i_1_n_5 ,\Delay6_out1_reg[8]_i_1_n_6 ,\Delay6_out1_reg[8]_i_1_n_7 }),
        .DI({\Delay6_out1[8]_i_2_n_0 ,\Delay6_out1[8]_i_3_n_0 ,\Delay6_out1[8]_i_4_n_0 ,\Delay6_out1[8]_i_5_n_0 ,\Delay6_out1[8]_i_6_n_0 ,\Delay6_out1[8]_i_7_n_0 ,\Delay6_out1[8]_i_8_n_0 ,\Delay6_out1[8]_i_9_n_0 }),
        .O(Delay3_out1_reg),
        .S({\Delay6_out1[8]_i_10_n_0 ,\Delay6_out1[8]_i_11_n_0 ,\Delay6_out1[8]_i_12_n_0 ,\Delay6_out1[8]_i_13_n_0 ,\Delay6_out1[8]_i_14_n_0 ,\Delay6_out1[8]_i_15_n_0 ,\Delay6_out1[8]_i_16_n_0 ,\Delay6_out1[8]_i_17_n_0 }));
  (* ADDER_THRESHOLD = "35" *) 
  CARRY8 InternalOmega_Out_tmp0_carry
       (.CI(1'b1),
        .CI_TOP(1'b0),
        .CO({InternalOmega_Out_tmp0_carry_n_0,InternalOmega_Out_tmp0_carry_n_1,InternalOmega_Out_tmp0_carry_n_2,InternalOmega_Out_tmp0_carry_n_3,InternalOmega_Out_tmp0_carry_n_4,InternalOmega_Out_tmp0_carry_n_5,InternalOmega_Out_tmp0_carry_n_6,InternalOmega_Out_tmp0_carry_n_7}),
        .DI(Delay6_out1_reg[7:0]),
        .O({InternalOmega_Out_tmp0[7:1],arg0_0[0]}),
        .S({InternalOmega_Out_tmp0_carry_i_1_n_0,InternalOmega_Out_tmp0_carry_i_2_n_0,InternalOmega_Out_tmp0_carry_i_3_n_0,InternalOmega_Out_tmp0_carry_i_4_n_0,InternalOmega_Out_tmp0_carry_i_5_n_0,InternalOmega_Out_tmp0_carry_i_6_n_0,InternalOmega_Out_tmp0_carry_i_7_n_0,InternalOmega_Out_tmp0_carry_i_8_n_0}));
  (* ADDER_THRESHOLD = "35" *) 
  CARRY8 InternalOmega_Out_tmp0_carry__0
       (.CI(InternalOmega_Out_tmp0_carry_n_0),
        .CI_TOP(1'b0),
        .CO({InternalOmega_Out_tmp0_carry__0_n_0,InternalOmega_Out_tmp0_carry__0_n_1,InternalOmega_Out_tmp0_carry__0_n_2,InternalOmega_Out_tmp0_carry__0_n_3,InternalOmega_Out_tmp0_carry__0_n_4,InternalOmega_Out_tmp0_carry__0_n_5,InternalOmega_Out_tmp0_carry__0_n_6,InternalOmega_Out_tmp0_carry__0_n_7}),
        .DI(Delay6_out1_reg[15:8]),
        .O(InternalOmega_Out_tmp0[15:8]),
        .S({InternalOmega_Out_tmp0_carry__0_i_1_n_0,InternalOmega_Out_tmp0_carry__0_i_2_n_0,InternalOmega_Out_tmp0_carry__0_i_3_n_0,InternalOmega_Out_tmp0_carry__0_i_4_n_0,InternalOmega_Out_tmp0_carry__0_i_5_n_0,InternalOmega_Out_tmp0_carry__0_i_6_n_0,InternalOmega_Out_tmp0_carry__0_i_7_n_0,InternalOmega_Out_tmp0_carry__0_i_8_n_0}));
  LUT2 #(
    .INIT(4'h9)) 
    InternalOmega_Out_tmp0_carry__0_i_1
       (.I0(Delay6_out1_reg[15]),
        .I1(\Delay6_out1_reg[23] [15]),
        .O(InternalOmega_Out_tmp0_carry__0_i_1_n_0));
  LUT2 #(
    .INIT(4'h9)) 
    InternalOmega_Out_tmp0_carry__0_i_2
       (.I0(Delay6_out1_reg[14]),
        .I1(\Delay6_out1_reg[23] [14]),
        .O(InternalOmega_Out_tmp0_carry__0_i_2_n_0));
  LUT2 #(
    .INIT(4'h9)) 
    InternalOmega_Out_tmp0_carry__0_i_3
       (.I0(Delay6_out1_reg[13]),
        .I1(\Delay6_out1_reg[23] [13]),
        .O(InternalOmega_Out_tmp0_carry__0_i_3_n_0));
  LUT2 #(
    .INIT(4'h9)) 
    InternalOmega_Out_tmp0_carry__0_i_4
       (.I0(Delay6_out1_reg[12]),
        .I1(\Delay6_out1_reg[23] [12]),
        .O(InternalOmega_Out_tmp0_carry__0_i_4_n_0));
  LUT2 #(
    .INIT(4'h9)) 
    InternalOmega_Out_tmp0_carry__0_i_5
       (.I0(Delay6_out1_reg[11]),
        .I1(\Delay6_out1_reg[23] [11]),
        .O(InternalOmega_Out_tmp0_carry__0_i_5_n_0));
  LUT2 #(
    .INIT(4'h9)) 
    InternalOmega_Out_tmp0_carry__0_i_6
       (.I0(Delay6_out1_reg[10]),
        .I1(\Delay6_out1_reg[23] [10]),
        .O(InternalOmega_Out_tmp0_carry__0_i_6_n_0));
  LUT2 #(
    .INIT(4'h9)) 
    InternalOmega_Out_tmp0_carry__0_i_7
       (.I0(Delay6_out1_reg[9]),
        .I1(\Delay6_out1_reg[23] [9]),
        .O(InternalOmega_Out_tmp0_carry__0_i_7_n_0));
  LUT2 #(
    .INIT(4'h9)) 
    InternalOmega_Out_tmp0_carry__0_i_8
       (.I0(Delay6_out1_reg[8]),
        .I1(\Delay6_out1_reg[23] [8]),
        .O(InternalOmega_Out_tmp0_carry__0_i_8_n_0));
  (* ADDER_THRESHOLD = "35" *) 
  CARRY8 InternalOmega_Out_tmp0_carry__1
       (.CI(InternalOmega_Out_tmp0_carry__0_n_0),
        .CI_TOP(1'b0),
        .CO({NLW_InternalOmega_Out_tmp0_carry__1_CO_UNCONNECTED[7],InternalOmega_Out_tmp0_carry__1_n_1,InternalOmega_Out_tmp0_carry__1_n_2,InternalOmega_Out_tmp0_carry__1_n_3,InternalOmega_Out_tmp0_carry__1_n_4,InternalOmega_Out_tmp0_carry__1_n_5,InternalOmega_Out_tmp0_carry__1_n_6,InternalOmega_Out_tmp0_carry__1_n_7}),
        .DI({1'b0,Delay6_out1_reg[22:16]}),
        .O(InternalOmega_Out_tmp0[23:16]),
        .S(S));
  LUT2 #(
    .INIT(4'h9)) 
    InternalOmega_Out_tmp0_carry_i_1
       (.I0(Delay6_out1_reg[7]),
        .I1(\Delay6_out1_reg[23] [7]),
        .O(InternalOmega_Out_tmp0_carry_i_1_n_0));
  LUT2 #(
    .INIT(4'h9)) 
    InternalOmega_Out_tmp0_carry_i_2
       (.I0(Delay6_out1_reg[6]),
        .I1(\Delay6_out1_reg[23] [6]),
        .O(InternalOmega_Out_tmp0_carry_i_2_n_0));
  LUT2 #(
    .INIT(4'h9)) 
    InternalOmega_Out_tmp0_carry_i_3
       (.I0(Delay6_out1_reg[5]),
        .I1(\Delay6_out1_reg[23] [5]),
        .O(InternalOmega_Out_tmp0_carry_i_3_n_0));
  LUT2 #(
    .INIT(4'h9)) 
    InternalOmega_Out_tmp0_carry_i_4
       (.I0(Delay6_out1_reg[4]),
        .I1(\Delay6_out1_reg[23] [4]),
        .O(InternalOmega_Out_tmp0_carry_i_4_n_0));
  LUT2 #(
    .INIT(4'h9)) 
    InternalOmega_Out_tmp0_carry_i_5
       (.I0(Delay6_out1_reg[3]),
        .I1(\Delay6_out1_reg[23] [3]),
        .O(InternalOmega_Out_tmp0_carry_i_5_n_0));
  LUT2 #(
    .INIT(4'h9)) 
    InternalOmega_Out_tmp0_carry_i_6
       (.I0(Delay6_out1_reg[2]),
        .I1(\Delay6_out1_reg[23] [2]),
        .O(InternalOmega_Out_tmp0_carry_i_6_n_0));
  LUT2 #(
    .INIT(4'h9)) 
    InternalOmega_Out_tmp0_carry_i_7
       (.I0(Delay6_out1_reg[1]),
        .I1(\Delay6_out1_reg[23] [1]),
        .O(InternalOmega_Out_tmp0_carry_i_7_n_0));
  LUT2 #(
    .INIT(4'h9)) 
    InternalOmega_Out_tmp0_carry_i_8
       (.I0(Delay6_out1_reg[0]),
        .I1(\Delay6_out1_reg[23] [0]),
        .O(InternalOmega_Out_tmp0_carry_i_8_n_0));
  CARRY8 \_inferred__1/i___71_carry 
       (.CI(1'b1),
        .CI_TOP(1'b0),
        .CO({\_inferred__1/i___71_carry_n_0 ,\_inferred__1/i___71_carry_n_1 ,\_inferred__1/i___71_carry_n_2 ,\_inferred__1/i___71_carry_n_3 ,\_inferred__1/i___71_carry_n_4 ,\_inferred__1/i___71_carry_n_5 ,\_inferred__1/i___71_carry_n_6 ,\_inferred__1/i___71_carry_n_7 }),
        .DI(arg0[7:0]),
        .O(\NLW__inferred__1/i___71_carry_O_UNCONNECTED [7:0]),
        .S({i___71_carry_i_1_n_0,i___71_carry_i_2_n_0,i___71_carry_i_3_n_0,i___71_carry_i_4_n_0,i___71_carry_i_5_n_0,i___71_carry_i_6_n_0,i___71_carry_i_7_n_0,i___71_carry_i_8_n_0}));
  CARRY8 \_inferred__1/i___71_carry__0 
       (.CI(\_inferred__1/i___71_carry_n_0 ),
        .CI_TOP(1'b0),
        .CO({\_inferred__1/i___71_carry__0_n_0 ,\_inferred__1/i___71_carry__0_n_1 ,\_inferred__1/i___71_carry__0_n_2 ,\_inferred__1/i___71_carry__0_n_3 ,\_inferred__1/i___71_carry__0_n_4 ,\_inferred__1/i___71_carry__0_n_5 ,\_inferred__1/i___71_carry__0_n_6 ,\_inferred__1/i___71_carry__0_n_7 }),
        .DI(arg0[15:8]),
        .O(\NLW__inferred__1/i___71_carry__0_O_UNCONNECTED [7:0]),
        .S({i___71_carry__0_i_1_n_0,i___71_carry__0_i_2_n_0,i___71_carry__0_i_3_n_0,i___71_carry__0_i_4_n_0,i___71_carry__0_i_5_n_0,i___71_carry__0_i_6_n_0,i___71_carry__0_i_7_n_0,i___71_carry__0_i_8_n_0}));
  CARRY8 \_inferred__1/i___71_carry__1 
       (.CI(\_inferred__1/i___71_carry__0_n_0 ),
        .CI_TOP(1'b0),
        .CO({\_inferred__1/i___71_carry__1_n_0 ,\_inferred__1/i___71_carry__1_n_1 ,\_inferred__1/i___71_carry__1_n_2 ,\_inferred__1/i___71_carry__1_n_3 ,\_inferred__1/i___71_carry__1_n_4 ,\_inferred__1/i___71_carry__1_n_5 ,\_inferred__1/i___71_carry__1_n_6 ,\_inferred__1/i___71_carry__1_n_7 }),
        .DI(arg0[23:16]),
        .O(\NLW__inferred__1/i___71_carry__1_O_UNCONNECTED [7:0]),
        .S({i___71_carry__1_i_1_n_0,i___71_carry__1_i_2_n_0,i___71_carry__1_i_3_n_0,i___71_carry__1_i_4_n_0,i___71_carry__1_i_5_n_0,i___71_carry__1_i_6_n_0,i___71_carry__1_i_7_n_0,i___71_carry__1_i_8_n_0}));
  CARRY8 \_inferred__1/i___71_carry__2 
       (.CI(\_inferred__1/i___71_carry__1_n_0 ),
        .CI_TOP(1'b0),
        .CO({\NLW__inferred__1/i___71_carry__2_CO_UNCONNECTED [7:1],\_inferred__1/i___71_carry__2_n_7 }),
        .DI({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,Q[23]}),
        .O(\NLW__inferred__1/i___71_carry__2_O_UNCONNECTED [7:0]),
        .S({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,i___71_carry__2_i_1_n_0}));
  CARRY8 \_inferred__1/i__carry 
       (.CI(1'b0),
        .CI_TOP(1'b0),
        .CO({\_inferred__1/i__carry_n_0 ,\_inferred__1/i__carry_n_1 ,\_inferred__1/i__carry_n_2 ,\_inferred__1/i__carry_n_3 ,\_inferred__1/i__carry_n_4 ,\_inferred__1/i__carry_n_5 ,\_inferred__1/i__carry_n_6 ,\_inferred__1/i__carry_n_7 }),
        .DI(Delay6_out1_reg[7:0]),
        .O(arg0[7:0]),
        .S({i__carry_i_1_n_0,i__carry_i_2_n_0,i__carry_i_3_n_0,i__carry_i_4_n_0,i__carry_i_5_n_0,i__carry_i_6_n_0,i__carry_i_7_n_0,i__carry_i_8_n_0}));
  CARRY8 \_inferred__1/i__carry__0 
       (.CI(\_inferred__1/i__carry_n_0 ),
        .CI_TOP(1'b0),
        .CO({\_inferred__1/i__carry__0_n_0 ,\_inferred__1/i__carry__0_n_1 ,\_inferred__1/i__carry__0_n_2 ,\_inferred__1/i__carry__0_n_3 ,\_inferred__1/i__carry__0_n_4 ,\_inferred__1/i__carry__0_n_5 ,\_inferred__1/i__carry__0_n_6 ,\_inferred__1/i__carry__0_n_7 }),
        .DI(Delay6_out1_reg[15:8]),
        .O(arg0[15:8]),
        .S({i__carry__0_i_1_n_0,i__carry__0_i_2_n_0,i__carry__0_i_3_n_0,i__carry__0_i_4_n_0,i__carry__0_i_5_n_0,i__carry__0_i_6_n_0,i__carry__0_i_7_n_0,i__carry__0_i_8_n_0}));
  CARRY8 \_inferred__1/i__carry__1 
       (.CI(\_inferred__1/i__carry__0_n_0 ),
        .CI_TOP(1'b0),
        .CO({\_inferred__1/i__carry__1_n_0 ,\_inferred__1/i__carry__1_n_1 ,\_inferred__1/i__carry__1_n_2 ,\_inferred__1/i__carry__1_n_3 ,\_inferred__1/i__carry__1_n_4 ,\_inferred__1/i__carry__1_n_5 ,\_inferred__1/i__carry__1_n_6 ,\_inferred__1/i__carry__1_n_7 }),
        .DI({i__carry__1_i_1_n_0,Delay6_out1_reg[22:16]}),
        .O(arg0[23:16]),
        .S({i__carry__1_i_2_n_0,i__carry__1_i_3_n_0,i__carry__1_i_4_n_0,i__carry__1_i_5_n_0,i__carry__1_i_6_n_0,i__carry__1_i_7_n_0,i__carry__1_i_8_n_0,i__carry__1_i_9_n_0}));
  CARRY8 arg0_carry
       (.CI(1'b1),
        .CI_TOP(1'b0),
        .CO({arg0_carry_n_0,arg0_carry_n_1,arg0_carry_n_2,arg0_carry_n_3,arg0_carry_n_4,arg0_carry_n_5,arg0_carry_n_6,arg0_carry_n_7}),
        .DI(Delay6_out1_reg[7:0]),
        .O({arg0_0[7:1],NLW_arg0_carry_O_UNCONNECTED[0]}),
        .S({arg0_carry_i_1_n_0,arg0_carry_i_2_n_0,arg0_carry_i_3_n_0,arg0_carry_i_4_n_0,arg0_carry_i_5_n_0,arg0_carry_i_6_n_0,arg0_carry_i_7_n_0,arg0_carry_i_8_n_0}));
  CARRY8 arg0_carry__0
       (.CI(arg0_carry_n_0),
        .CI_TOP(1'b0),
        .CO({arg0_carry__0_n_0,arg0_carry__0_n_1,arg0_carry__0_n_2,arg0_carry__0_n_3,arg0_carry__0_n_4,arg0_carry__0_n_5,arg0_carry__0_n_6,arg0_carry__0_n_7}),
        .DI(Delay6_out1_reg[15:8]),
        .O(arg0_0[15:8]),
        .S({arg0_carry__0_i_1_n_0,arg0_carry__0_i_2_n_0,arg0_carry__0_i_3_n_0,arg0_carry__0_i_4_n_0,arg0_carry__0_i_5_n_0,arg0_carry__0_i_6_n_0,arg0_carry__0_i_7_n_0,arg0_carry__0_i_8_n_0}));
  LUT2 #(
    .INIT(4'h9)) 
    arg0_carry__0_i_1
       (.I0(Delay6_out1_reg[15]),
        .I1(\Delay6_out1_reg[23] [15]),
        .O(arg0_carry__0_i_1_n_0));
  LUT2 #(
    .INIT(4'h9)) 
    arg0_carry__0_i_2
       (.I0(Delay6_out1_reg[14]),
        .I1(\Delay6_out1_reg[23] [14]),
        .O(arg0_carry__0_i_2_n_0));
  LUT2 #(
    .INIT(4'h9)) 
    arg0_carry__0_i_3
       (.I0(Delay6_out1_reg[13]),
        .I1(\Delay6_out1_reg[23] [13]),
        .O(arg0_carry__0_i_3_n_0));
  LUT2 #(
    .INIT(4'h9)) 
    arg0_carry__0_i_4
       (.I0(Delay6_out1_reg[12]),
        .I1(\Delay6_out1_reg[23] [12]),
        .O(arg0_carry__0_i_4_n_0));
  LUT2 #(
    .INIT(4'h9)) 
    arg0_carry__0_i_5
       (.I0(Delay6_out1_reg[11]),
        .I1(\Delay6_out1_reg[23] [11]),
        .O(arg0_carry__0_i_5_n_0));
  LUT2 #(
    .INIT(4'h9)) 
    arg0_carry__0_i_6
       (.I0(Delay6_out1_reg[10]),
        .I1(\Delay6_out1_reg[23] [10]),
        .O(arg0_carry__0_i_6_n_0));
  LUT2 #(
    .INIT(4'h9)) 
    arg0_carry__0_i_7
       (.I0(Delay6_out1_reg[9]),
        .I1(\Delay6_out1_reg[23] [9]),
        .O(arg0_carry__0_i_7_n_0));
  LUT2 #(
    .INIT(4'h9)) 
    arg0_carry__0_i_8
       (.I0(Delay6_out1_reg[8]),
        .I1(\Delay6_out1_reg[23] [8]),
        .O(arg0_carry__0_i_8_n_0));
  CARRY8 arg0_carry__1
       (.CI(arg0_carry__0_n_0),
        .CI_TOP(1'b0),
        .CO({arg0_carry__1_n_0,arg0_carry__1_n_1,arg0_carry__1_n_2,arg0_carry__1_n_3,arg0_carry__1_n_4,arg0_carry__1_n_5,arg0_carry__1_n_6,arg0_carry__1_n_7}),
        .DI({\Delay6_out1_reg[23] [23],Delay6_out1_reg[22:16]}),
        .O(arg0_0[23:16]),
        .S({arg0_carry__1_i_1_n_0,arg0_carry__1_i_2_n_0,arg0_carry__1_i_3_n_0,arg0_carry__1_i_4_n_0,arg0_carry__1_i_5_n_0,arg0_carry__1_i_6_n_0,arg0_carry__1_i_7_n_0,arg0_carry__1_i_8_n_0}));
  LUT2 #(
    .INIT(4'h9)) 
    arg0_carry__1_i_1
       (.I0(Delay6_out1_reg[23]),
        .I1(\Delay6_out1_reg[23] [23]),
        .O(arg0_carry__1_i_1_n_0));
  LUT2 #(
    .INIT(4'h9)) 
    arg0_carry__1_i_2
       (.I0(Delay6_out1_reg[22]),
        .I1(\Delay6_out1_reg[23] [22]),
        .O(arg0_carry__1_i_2_n_0));
  LUT2 #(
    .INIT(4'h9)) 
    arg0_carry__1_i_3
       (.I0(Delay6_out1_reg[21]),
        .I1(\Delay6_out1_reg[23] [21]),
        .O(arg0_carry__1_i_3_n_0));
  LUT2 #(
    .INIT(4'h9)) 
    arg0_carry__1_i_4
       (.I0(Delay6_out1_reg[20]),
        .I1(\Delay6_out1_reg[23] [20]),
        .O(arg0_carry__1_i_4_n_0));
  LUT2 #(
    .INIT(4'h9)) 
    arg0_carry__1_i_5
       (.I0(Delay6_out1_reg[19]),
        .I1(\Delay6_out1_reg[23] [19]),
        .O(arg0_carry__1_i_5_n_0));
  LUT2 #(
    .INIT(4'h9)) 
    arg0_carry__1_i_6
       (.I0(Delay6_out1_reg[18]),
        .I1(\Delay6_out1_reg[23] [18]),
        .O(arg0_carry__1_i_6_n_0));
  LUT2 #(
    .INIT(4'h9)) 
    arg0_carry__1_i_7
       (.I0(Delay6_out1_reg[17]),
        .I1(\Delay6_out1_reg[23] [17]),
        .O(arg0_carry__1_i_7_n_0));
  LUT2 #(
    .INIT(4'h9)) 
    arg0_carry__1_i_8
       (.I0(Delay6_out1_reg[16]),
        .I1(\Delay6_out1_reg[23] [16]),
        .O(arg0_carry__1_i_8_n_0));
  LUT2 #(
    .INIT(4'h9)) 
    arg0_carry_i_1
       (.I0(Delay6_out1_reg[7]),
        .I1(\Delay6_out1_reg[23] [7]),
        .O(arg0_carry_i_1_n_0));
  LUT2 #(
    .INIT(4'h9)) 
    arg0_carry_i_2
       (.I0(Delay6_out1_reg[6]),
        .I1(\Delay6_out1_reg[23] [6]),
        .O(arg0_carry_i_2_n_0));
  LUT2 #(
    .INIT(4'h9)) 
    arg0_carry_i_3
       (.I0(Delay6_out1_reg[5]),
        .I1(\Delay6_out1_reg[23] [5]),
        .O(arg0_carry_i_3_n_0));
  LUT2 #(
    .INIT(4'h9)) 
    arg0_carry_i_4
       (.I0(Delay6_out1_reg[4]),
        .I1(\Delay6_out1_reg[23] [4]),
        .O(arg0_carry_i_4_n_0));
  LUT2 #(
    .INIT(4'h9)) 
    arg0_carry_i_5
       (.I0(Delay6_out1_reg[3]),
        .I1(\Delay6_out1_reg[23] [3]),
        .O(arg0_carry_i_5_n_0));
  LUT2 #(
    .INIT(4'h9)) 
    arg0_carry_i_6
       (.I0(Delay6_out1_reg[2]),
        .I1(\Delay6_out1_reg[23] [2]),
        .O(arg0_carry_i_6_n_0));
  LUT2 #(
    .INIT(4'h9)) 
    arg0_carry_i_7
       (.I0(Delay6_out1_reg[1]),
        .I1(\Delay6_out1_reg[23] [1]),
        .O(arg0_carry_i_7_n_0));
  LUT2 #(
    .INIT(4'h9)) 
    arg0_carry_i_8
       (.I0(Delay6_out1_reg[0]),
        .I1(\Delay6_out1_reg[23] [0]),
        .O(arg0_carry_i_8_n_0));
  (* COMPARATOR_THRESHOLD = "11" *) 
  CARRY8 arg_carry
       (.CI(1'b0),
        .CI_TOP(1'b0),
        .CO({arg_carry_n_0,arg_carry_n_1,arg_carry_n_2,arg_carry_n_3,arg_carry_n_4,arg_carry_n_5,arg_carry_n_6,arg_carry_n_7}),
        .DI({arg_carry_i_1_n_0,arg_carry_i_2_n_0,arg_carry_i_3_n_0,arg_carry_i_4_n_0,arg_carry_i_5_n_0,arg_carry_i_6_n_0,arg_carry_i_7_n_0,arg_carry_i_8_n_0}),
        .O(NLW_arg_carry_O_UNCONNECTED[7:0]),
        .S({arg_carry_i_9_n_0,arg_carry_i_10_n_0,arg_carry_i_11_n_0,arg_carry_i_12_n_0,arg_carry_i_13_n_0,arg_carry_i_14_n_0,arg_carry_i_15_n_0,arg_carry_i_16_n_0}));
  (* COMPARATOR_THRESHOLD = "11" *) 
  CARRY8 arg_carry__0
       (.CI(arg_carry_n_0),
        .CI_TOP(1'b0),
        .CO({NLW_arg_carry__0_CO_UNCONNECTED[7:5],hdlcoder_to_stdlogic,arg_carry__0_n_4,arg_carry__0_n_5,arg_carry__0_n_6,arg_carry__0_n_7}),
        .DI({1'b0,1'b0,1'b0,arg_carry__0_i_1_n_0,arg_carry__0_i_2_n_0,arg_carry__0_i_3_n_0,arg_carry__0_i_4_n_0,arg_carry__0_i_5_n_0}),
        .O(NLW_arg_carry__0_O_UNCONNECTED[7:0]),
        .S({1'b0,1'b0,1'b0,arg_carry__0_i_6_n_0,arg_carry__0_i_7_n_0,arg_carry__0_i_8_n_0,arg_carry__0_i_9_n_0,arg_carry__0_i_10_n_0}));
  LUT2 #(
    .INIT(4'h8)) 
    arg_carry__0_i_1
       (.I0(arg_carry__0_i_11_n_7),
        .I1(Q[23]),
        .O(arg_carry__0_i_1_n_0));
  LUT4 #(
    .INIT(16'h9009)) 
    arg_carry__0_i_10
       (.I0(Q[17]),
        .I1(arg0_0[17]),
        .I2(Q[16]),
        .I3(arg0_0[16]),
        .O(arg_carry__0_i_10_n_0));
  CARRY8 arg_carry__0_i_11
       (.CI(arg0_carry__1_n_0),
        .CI_TOP(1'b0),
        .CO({NLW_arg_carry__0_i_11_CO_UNCONNECTED[7:1],arg_carry__0_i_11_n_7}),
        .DI({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .O(NLW_arg_carry__0_i_11_O_UNCONNECTED[7:0]),
        .S({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b1}));
  LUT4 #(
    .INIT(16'h22B2)) 
    arg_carry__0_i_2
       (.I0(arg0_0[23]),
        .I1(Q[23]),
        .I2(arg0_0[22]),
        .I3(Q[22]),
        .O(arg_carry__0_i_2_n_0));
  LUT4 #(
    .INIT(16'h22B2)) 
    arg_carry__0_i_3
       (.I0(arg0_0[21]),
        .I1(Q[21]),
        .I2(arg0_0[20]),
        .I3(Q[20]),
        .O(arg_carry__0_i_3_n_0));
  LUT4 #(
    .INIT(16'h22B2)) 
    arg_carry__0_i_4
       (.I0(arg0_0[19]),
        .I1(Q[19]),
        .I2(arg0_0[18]),
        .I3(Q[18]),
        .O(arg_carry__0_i_4_n_0));
  LUT4 #(
    .INIT(16'h22B2)) 
    arg_carry__0_i_5
       (.I0(arg0_0[17]),
        .I1(Q[17]),
        .I2(arg0_0[16]),
        .I3(Q[16]),
        .O(arg_carry__0_i_5_n_0));
  LUT2 #(
    .INIT(4'h6)) 
    arg_carry__0_i_6
       (.I0(arg_carry__0_i_11_n_7),
        .I1(Q[23]),
        .O(arg_carry__0_i_6_n_0));
  LUT4 #(
    .INIT(16'h9009)) 
    arg_carry__0_i_7
       (.I0(Q[23]),
        .I1(arg0_0[23]),
        .I2(Q[22]),
        .I3(arg0_0[22]),
        .O(arg_carry__0_i_7_n_0));
  LUT4 #(
    .INIT(16'h9009)) 
    arg_carry__0_i_8
       (.I0(Q[21]),
        .I1(arg0_0[21]),
        .I2(Q[20]),
        .I3(arg0_0[20]),
        .O(arg_carry__0_i_8_n_0));
  LUT4 #(
    .INIT(16'h9009)) 
    arg_carry__0_i_9
       (.I0(Q[19]),
        .I1(arg0_0[19]),
        .I2(Q[18]),
        .I3(arg0_0[18]),
        .O(arg_carry__0_i_9_n_0));
  LUT4 #(
    .INIT(16'h22B2)) 
    arg_carry_i_1
       (.I0(arg0_0[15]),
        .I1(Q[15]),
        .I2(arg0_0[14]),
        .I3(Q[14]),
        .O(arg_carry_i_1_n_0));
  LUT4 #(
    .INIT(16'h9009)) 
    arg_carry_i_10
       (.I0(Q[13]),
        .I1(arg0_0[13]),
        .I2(Q[12]),
        .I3(arg0_0[12]),
        .O(arg_carry_i_10_n_0));
  LUT4 #(
    .INIT(16'h9009)) 
    arg_carry_i_11
       (.I0(Q[11]),
        .I1(arg0_0[11]),
        .I2(Q[10]),
        .I3(arg0_0[10]),
        .O(arg_carry_i_11_n_0));
  LUT4 #(
    .INIT(16'h9009)) 
    arg_carry_i_12
       (.I0(Q[9]),
        .I1(arg0_0[9]),
        .I2(Q[8]),
        .I3(arg0_0[8]),
        .O(arg_carry_i_12_n_0));
  LUT4 #(
    .INIT(16'h9009)) 
    arg_carry_i_13
       (.I0(Q[7]),
        .I1(arg0_0[7]),
        .I2(Q[6]),
        .I3(arg0_0[6]),
        .O(arg_carry_i_13_n_0));
  LUT4 #(
    .INIT(16'h9009)) 
    arg_carry_i_14
       (.I0(Q[5]),
        .I1(arg0_0[5]),
        .I2(Q[4]),
        .I3(arg0_0[4]),
        .O(arg_carry_i_14_n_0));
  LUT4 #(
    .INIT(16'h9009)) 
    arg_carry_i_15
       (.I0(Q[3]),
        .I1(arg0_0[3]),
        .I2(Q[2]),
        .I3(arg0_0[2]),
        .O(arg_carry_i_15_n_0));
  LUT4 #(
    .INIT(16'h9009)) 
    arg_carry_i_16
       (.I0(Q[1]),
        .I1(arg0_0[1]),
        .I2(Q[0]),
        .I3(arg0_0[0]),
        .O(arg_carry_i_16_n_0));
  LUT4 #(
    .INIT(16'h22B2)) 
    arg_carry_i_2
       (.I0(arg0_0[13]),
        .I1(Q[13]),
        .I2(arg0_0[12]),
        .I3(Q[12]),
        .O(arg_carry_i_2_n_0));
  LUT4 #(
    .INIT(16'h22B2)) 
    arg_carry_i_3
       (.I0(arg0_0[11]),
        .I1(Q[11]),
        .I2(arg0_0[10]),
        .I3(Q[10]),
        .O(arg_carry_i_3_n_0));
  LUT4 #(
    .INIT(16'h22B2)) 
    arg_carry_i_4
       (.I0(arg0_0[9]),
        .I1(Q[9]),
        .I2(arg0_0[8]),
        .I3(Q[8]),
        .O(arg_carry_i_4_n_0));
  LUT4 #(
    .INIT(16'h22B2)) 
    arg_carry_i_5
       (.I0(arg0_0[7]),
        .I1(Q[7]),
        .I2(arg0_0[6]),
        .I3(Q[6]),
        .O(arg_carry_i_5_n_0));
  LUT4 #(
    .INIT(16'h22B2)) 
    arg_carry_i_6
       (.I0(arg0_0[5]),
        .I1(Q[5]),
        .I2(arg0_0[4]),
        .I3(Q[4]),
        .O(arg_carry_i_6_n_0));
  LUT4 #(
    .INIT(16'h22B2)) 
    arg_carry_i_7
       (.I0(arg0_0[3]),
        .I1(Q[3]),
        .I2(arg0_0[2]),
        .I3(Q[2]),
        .O(arg_carry_i_7_n_0));
  LUT4 #(
    .INIT(16'h22B2)) 
    arg_carry_i_8
       (.I0(arg0_0[1]),
        .I1(Q[1]),
        .I2(arg0_0[0]),
        .I3(Q[0]),
        .O(arg_carry_i_8_n_0));
  LUT4 #(
    .INIT(16'h9009)) 
    arg_carry_i_9
       (.I0(Q[15]),
        .I1(arg0_0[15]),
        .I2(Q[14]),
        .I3(arg0_0[14]),
        .O(arg_carry_i_9_n_0));
  LUT2 #(
    .INIT(4'h9)) 
    i___71_carry__0_i_1
       (.I0(arg0[15]),
        .I1(Q[15]),
        .O(i___71_carry__0_i_1_n_0));
  LUT2 #(
    .INIT(4'h9)) 
    i___71_carry__0_i_2
       (.I0(arg0[14]),
        .I1(Q[14]),
        .O(i___71_carry__0_i_2_n_0));
  LUT2 #(
    .INIT(4'h9)) 
    i___71_carry__0_i_3
       (.I0(arg0[13]),
        .I1(Q[13]),
        .O(i___71_carry__0_i_3_n_0));
  LUT2 #(
    .INIT(4'h9)) 
    i___71_carry__0_i_4
       (.I0(arg0[12]),
        .I1(Q[12]),
        .O(i___71_carry__0_i_4_n_0));
  LUT2 #(
    .INIT(4'h9)) 
    i___71_carry__0_i_5
       (.I0(arg0[11]),
        .I1(Q[11]),
        .O(i___71_carry__0_i_5_n_0));
  LUT2 #(
    .INIT(4'h9)) 
    i___71_carry__0_i_6
       (.I0(arg0[10]),
        .I1(Q[10]),
        .O(i___71_carry__0_i_6_n_0));
  LUT2 #(
    .INIT(4'h9)) 
    i___71_carry__0_i_7
       (.I0(arg0[9]),
        .I1(Q[9]),
        .O(i___71_carry__0_i_7_n_0));
  LUT2 #(
    .INIT(4'h9)) 
    i___71_carry__0_i_8
       (.I0(arg0[8]),
        .I1(Q[8]),
        .O(i___71_carry__0_i_8_n_0));
  LUT2 #(
    .INIT(4'h9)) 
    i___71_carry__1_i_1
       (.I0(Q[23]),
        .I1(arg0[23]),
        .O(i___71_carry__1_i_1_n_0));
  LUT2 #(
    .INIT(4'h9)) 
    i___71_carry__1_i_2
       (.I0(arg0[22]),
        .I1(Q[22]),
        .O(i___71_carry__1_i_2_n_0));
  LUT2 #(
    .INIT(4'h9)) 
    i___71_carry__1_i_3
       (.I0(arg0[21]),
        .I1(Q[21]),
        .O(i___71_carry__1_i_3_n_0));
  LUT2 #(
    .INIT(4'h9)) 
    i___71_carry__1_i_4
       (.I0(arg0[20]),
        .I1(Q[20]),
        .O(i___71_carry__1_i_4_n_0));
  LUT2 #(
    .INIT(4'h9)) 
    i___71_carry__1_i_5
       (.I0(arg0[19]),
        .I1(Q[19]),
        .O(i___71_carry__1_i_5_n_0));
  LUT2 #(
    .INIT(4'h9)) 
    i___71_carry__1_i_6
       (.I0(arg0[18]),
        .I1(Q[18]),
        .O(i___71_carry__1_i_6_n_0));
  LUT2 #(
    .INIT(4'h9)) 
    i___71_carry__1_i_7
       (.I0(arg0[17]),
        .I1(Q[17]),
        .O(i___71_carry__1_i_7_n_0));
  LUT2 #(
    .INIT(4'h9)) 
    i___71_carry__1_i_8
       (.I0(arg0[16]),
        .I1(Q[16]),
        .O(i___71_carry__1_i_8_n_0));
  LUT2 #(
    .INIT(4'h6)) 
    i___71_carry__2_i_1
       (.I0(Q[23]),
        .I1(i___71_carry__2_i_2_n_7),
        .O(i___71_carry__2_i_1_n_0));
  CARRY8 i___71_carry__2_i_2
       (.CI(\_inferred__1/i__carry__1_n_0 ),
        .CI_TOP(1'b0),
        .CO({NLW_i___71_carry__2_i_2_CO_UNCONNECTED[7:1],i___71_carry__2_i_2_n_7}),
        .DI({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .O(NLW_i___71_carry__2_i_2_O_UNCONNECTED[7:0]),
        .S({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b1}));
  LUT2 #(
    .INIT(4'h9)) 
    i___71_carry_i_1
       (.I0(arg0[7]),
        .I1(Q[7]),
        .O(i___71_carry_i_1_n_0));
  LUT2 #(
    .INIT(4'h9)) 
    i___71_carry_i_2
       (.I0(arg0[6]),
        .I1(Q[6]),
        .O(i___71_carry_i_2_n_0));
  LUT2 #(
    .INIT(4'h9)) 
    i___71_carry_i_3
       (.I0(arg0[5]),
        .I1(Q[5]),
        .O(i___71_carry_i_3_n_0));
  LUT2 #(
    .INIT(4'h9)) 
    i___71_carry_i_4
       (.I0(arg0[4]),
        .I1(Q[4]),
        .O(i___71_carry_i_4_n_0));
  LUT2 #(
    .INIT(4'h9)) 
    i___71_carry_i_5
       (.I0(arg0[3]),
        .I1(Q[3]),
        .O(i___71_carry_i_5_n_0));
  LUT2 #(
    .INIT(4'h9)) 
    i___71_carry_i_6
       (.I0(arg0[2]),
        .I1(Q[2]),
        .O(i___71_carry_i_6_n_0));
  LUT2 #(
    .INIT(4'h9)) 
    i___71_carry_i_7
       (.I0(arg0[1]),
        .I1(Q[1]),
        .O(i___71_carry_i_7_n_0));
  LUT2 #(
    .INIT(4'h9)) 
    i___71_carry_i_8
       (.I0(arg0[0]),
        .I1(Q[0]),
        .O(i___71_carry_i_8_n_0));
  LUT2 #(
    .INIT(4'h6)) 
    i__carry__0_i_1
       (.I0(\Delay6_out1_reg[23] [15]),
        .I1(Delay6_out1_reg[15]),
        .O(i__carry__0_i_1_n_0));
  LUT2 #(
    .INIT(4'h6)) 
    i__carry__0_i_2
       (.I0(\Delay6_out1_reg[23] [14]),
        .I1(Delay6_out1_reg[14]),
        .O(i__carry__0_i_2_n_0));
  LUT2 #(
    .INIT(4'h6)) 
    i__carry__0_i_3
       (.I0(\Delay6_out1_reg[23] [13]),
        .I1(Delay6_out1_reg[13]),
        .O(i__carry__0_i_3_n_0));
  LUT2 #(
    .INIT(4'h6)) 
    i__carry__0_i_4
       (.I0(\Delay6_out1_reg[23] [12]),
        .I1(Delay6_out1_reg[12]),
        .O(i__carry__0_i_4_n_0));
  LUT2 #(
    .INIT(4'h6)) 
    i__carry__0_i_5
       (.I0(\Delay6_out1_reg[23] [11]),
        .I1(Delay6_out1_reg[11]),
        .O(i__carry__0_i_5_n_0));
  LUT2 #(
    .INIT(4'h6)) 
    i__carry__0_i_6
       (.I0(\Delay6_out1_reg[23] [10]),
        .I1(Delay6_out1_reg[10]),
        .O(i__carry__0_i_6_n_0));
  LUT2 #(
    .INIT(4'h6)) 
    i__carry__0_i_7
       (.I0(\Delay6_out1_reg[23] [9]),
        .I1(Delay6_out1_reg[9]),
        .O(i__carry__0_i_7_n_0));
  LUT2 #(
    .INIT(4'h6)) 
    i__carry__0_i_8
       (.I0(\Delay6_out1_reg[23] [8]),
        .I1(Delay6_out1_reg[8]),
        .O(i__carry__0_i_8_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    i__carry__1_i_1
       (.I0(\Delay6_out1_reg[23] [23]),
        .O(i__carry__1_i_1_n_0));
  LUT2 #(
    .INIT(4'h6)) 
    i__carry__1_i_2
       (.I0(\Delay6_out1_reg[23] [23]),
        .I1(Delay6_out1_reg[23]),
        .O(i__carry__1_i_2_n_0));
  LUT2 #(
    .INIT(4'h6)) 
    i__carry__1_i_3
       (.I0(\Delay6_out1_reg[23] [22]),
        .I1(Delay6_out1_reg[22]),
        .O(i__carry__1_i_3_n_0));
  LUT2 #(
    .INIT(4'h6)) 
    i__carry__1_i_4
       (.I0(\Delay6_out1_reg[23] [21]),
        .I1(Delay6_out1_reg[21]),
        .O(i__carry__1_i_4_n_0));
  LUT2 #(
    .INIT(4'h6)) 
    i__carry__1_i_5
       (.I0(\Delay6_out1_reg[23] [20]),
        .I1(Delay6_out1_reg[20]),
        .O(i__carry__1_i_5_n_0));
  LUT2 #(
    .INIT(4'h6)) 
    i__carry__1_i_6
       (.I0(\Delay6_out1_reg[23] [19]),
        .I1(Delay6_out1_reg[19]),
        .O(i__carry__1_i_6_n_0));
  LUT2 #(
    .INIT(4'h6)) 
    i__carry__1_i_7
       (.I0(\Delay6_out1_reg[23] [18]),
        .I1(Delay6_out1_reg[18]),
        .O(i__carry__1_i_7_n_0));
  LUT2 #(
    .INIT(4'h6)) 
    i__carry__1_i_8
       (.I0(\Delay6_out1_reg[23] [17]),
        .I1(Delay6_out1_reg[17]),
        .O(i__carry__1_i_8_n_0));
  LUT2 #(
    .INIT(4'h6)) 
    i__carry__1_i_9
       (.I0(\Delay6_out1_reg[23] [16]),
        .I1(Delay6_out1_reg[16]),
        .O(i__carry__1_i_9_n_0));
  LUT2 #(
    .INIT(4'h6)) 
    i__carry_i_1
       (.I0(\Delay6_out1_reg[23] [7]),
        .I1(Delay6_out1_reg[7]),
        .O(i__carry_i_1_n_0));
  LUT2 #(
    .INIT(4'h6)) 
    i__carry_i_2
       (.I0(\Delay6_out1_reg[23] [6]),
        .I1(Delay6_out1_reg[6]),
        .O(i__carry_i_2_n_0));
  LUT2 #(
    .INIT(4'h6)) 
    i__carry_i_3
       (.I0(\Delay6_out1_reg[23] [5]),
        .I1(Delay6_out1_reg[5]),
        .O(i__carry_i_3_n_0));
  LUT2 #(
    .INIT(4'h6)) 
    i__carry_i_4
       (.I0(\Delay6_out1_reg[23] [4]),
        .I1(Delay6_out1_reg[4]),
        .O(i__carry_i_4_n_0));
  LUT2 #(
    .INIT(4'h6)) 
    i__carry_i_5
       (.I0(\Delay6_out1_reg[23] [3]),
        .I1(Delay6_out1_reg[3]),
        .O(i__carry_i_5_n_0));
  LUT2 #(
    .INIT(4'h6)) 
    i__carry_i_6
       (.I0(\Delay6_out1_reg[23] [2]),
        .I1(Delay6_out1_reg[2]),
        .O(i__carry_i_6_n_0));
  LUT2 #(
    .INIT(4'h6)) 
    i__carry_i_7
       (.I0(\Delay6_out1_reg[23] [1]),
        .I1(Delay6_out1_reg[1]),
        .O(i__carry_i_7_n_0));
  LUT2 #(
    .INIT(4'h6)) 
    i__carry_i_8
       (.I0(\Delay6_out1_reg[23] [0]),
        .I1(Delay6_out1_reg[0]),
        .O(i__carry_i_8_n_0));
  (* ADDER_THRESHOLD = "35" *) 
  CARRY8 state_Out_tmp0_carry
       (.CI(1'b0),
        .CI_TOP(1'b0),
        .CO({state_Out_tmp0_carry_n_0,state_Out_tmp0_carry_n_1,state_Out_tmp0_carry_n_2,state_Out_tmp0_carry_n_3,state_Out_tmp0_carry_n_4,state_Out_tmp0_carry_n_5,state_Out_tmp0_carry_n_6,state_Out_tmp0_carry_n_7}),
        .DI({state_Out_tmp0_carry_i_1_n_0,state_Out_tmp0_carry_i_2_n_0,state_Out_tmp0_carry_i_3_n_0,state_Out_tmp0_carry_i_4_n_0,state_Out_tmp0_carry_i_5_n_0,state_Out_tmp0_carry_i_6_n_0,state_Out_tmp0_carry_i_7_n_0,state_Out_tmp0_carry_i_8_n_0}),
        .O(D[7:0]),
        .S({state_Out_tmp0_carry_i_9_n_0,state_Out_tmp0_carry_i_10_n_0,state_Out_tmp0_carry_i_11_n_0,state_Out_tmp0_carry_i_12_n_0,state_Out_tmp0_carry_i_13_n_0,state_Out_tmp0_carry_i_14_n_0,state_Out_tmp0_carry_i_15_n_0,state_Out_tmp0_carry_i_16_n_0}));
  (* ADDER_THRESHOLD = "35" *) 
  CARRY8 state_Out_tmp0_carry__0
       (.CI(state_Out_tmp0_carry_n_0),
        .CI_TOP(1'b0),
        .CO({NLW_state_Out_tmp0_carry__0_CO_UNCONNECTED[7],state_Out_tmp0_carry__0_n_1,state_Out_tmp0_carry__0_n_2,state_Out_tmp0_carry__0_n_3,state_Out_tmp0_carry__0_n_4,state_Out_tmp0_carry__0_n_5,state_Out_tmp0_carry__0_n_6,state_Out_tmp0_carry__0_n_7}),
        .DI({1'b0,DI}),
        .O(D[15:8]),
        .S(\Delay7_out_reg[15] ));
  LUT2 #(
    .INIT(4'h7)) 
    state_Out_tmp0_carry_i_1
       (.I0(\Delay7_out_reg[7]_0 [7]),
        .I1(\Delay7_out_reg[7] ),
        .O(state_Out_tmp0_carry_i_1_n_0));
  LUT3 #(
    .INIT(8'hB7)) 
    state_Out_tmp0_carry_i_10
       (.I0(\Delay7_out_reg[7]_0 [5]),
        .I1(\Delay7_out_reg[7] ),
        .I2(\Delay7_out_reg[7]_0 [6]),
        .O(state_Out_tmp0_carry_i_10_n_0));
  LUT3 #(
    .INIT(8'hB7)) 
    state_Out_tmp0_carry_i_11
       (.I0(\Delay7_out_reg[7]_0 [4]),
        .I1(\Delay7_out_reg[7] ),
        .I2(\Delay7_out_reg[7]_0 [5]),
        .O(state_Out_tmp0_carry_i_11_n_0));
  LUT3 #(
    .INIT(8'hB7)) 
    state_Out_tmp0_carry_i_12
       (.I0(\Delay7_out_reg[7]_0 [3]),
        .I1(\Delay7_out_reg[7] ),
        .I2(\Delay7_out_reg[7]_0 [4]),
        .O(state_Out_tmp0_carry_i_12_n_0));
  LUT3 #(
    .INIT(8'hB7)) 
    state_Out_tmp0_carry_i_13
       (.I0(\Delay7_out_reg[7]_0 [2]),
        .I1(\Delay7_out_reg[7] ),
        .I2(\Delay7_out_reg[7]_0 [3]),
        .O(state_Out_tmp0_carry_i_13_n_0));
  LUT5 #(
    .INIT(32'h7F808080)) 
    state_Out_tmp0_carry_i_14
       (.I0(\_inferred__1/i___71_carry__2_n_7 ),
        .I1(hdlcoder_to_stdlogic),
        .I2(Delay3_out1),
        .I3(\Delay7_out_reg[7] ),
        .I4(\Delay7_out_reg[7]_0 [2]),
        .O(state_Out_tmp0_carry_i_14_n_0));
  LUT5 #(
    .INIT(32'h7F808080)) 
    state_Out_tmp0_carry_i_15
       (.I0(\_inferred__1/i___71_carry__2_n_7 ),
        .I1(hdlcoder_to_stdlogic),
        .I2(Delay3_out1),
        .I3(\Delay7_out_reg[7] ),
        .I4(\Delay7_out_reg[7]_0 [1]),
        .O(state_Out_tmp0_carry_i_15_n_0));
  LUT5 #(
    .INIT(32'h2DDD22DD)) 
    state_Out_tmp0_carry_i_16
       (.I0(\Delay7_out_reg[7] ),
        .I1(\Delay7_out_reg[7]_0 [0]),
        .I2(hdlcoder_to_stdlogic),
        .I3(Delay3_out1),
        .I4(\_inferred__1/i___71_carry__2_n_7 ),
        .O(state_Out_tmp0_carry_i_16_n_0));
  LUT2 #(
    .INIT(4'h7)) 
    state_Out_tmp0_carry_i_2
       (.I0(\Delay7_out_reg[7]_0 [6]),
        .I1(\Delay7_out_reg[7] ),
        .O(state_Out_tmp0_carry_i_2_n_0));
  LUT2 #(
    .INIT(4'h7)) 
    state_Out_tmp0_carry_i_3
       (.I0(\Delay7_out_reg[7]_0 [5]),
        .I1(\Delay7_out_reg[7] ),
        .O(state_Out_tmp0_carry_i_3_n_0));
  LUT2 #(
    .INIT(4'h7)) 
    state_Out_tmp0_carry_i_4
       (.I0(\Delay7_out_reg[7]_0 [4]),
        .I1(\Delay7_out_reg[7] ),
        .O(state_Out_tmp0_carry_i_4_n_0));
  LUT2 #(
    .INIT(4'h7)) 
    state_Out_tmp0_carry_i_5
       (.I0(\Delay7_out_reg[7]_0 [3]),
        .I1(\Delay7_out_reg[7] ),
        .O(state_Out_tmp0_carry_i_5_n_0));
  LUT3 #(
    .INIT(8'h7F)) 
    state_Out_tmp0_carry_i_6
       (.I0(Delay3_out1),
        .I1(hdlcoder_to_stdlogic),
        .I2(\_inferred__1/i___71_carry__2_n_7 ),
        .O(state_Out_tmp0_carry_i_6_n_0));
  LUT3 #(
    .INIT(8'h80)) 
    state_Out_tmp0_carry_i_7
       (.I0(\_inferred__1/i___71_carry__2_n_7 ),
        .I1(hdlcoder_to_stdlogic),
        .I2(Delay3_out1),
        .O(state_Out_tmp0_carry_i_7_n_0));
  LUT2 #(
    .INIT(4'hB)) 
    state_Out_tmp0_carry_i_8
       (.I0(\Delay7_out_reg[7]_0 [0]),
        .I1(\Delay7_out_reg[7] ),
        .O(state_Out_tmp0_carry_i_8_n_0));
  LUT3 #(
    .INIT(8'hB7)) 
    state_Out_tmp0_carry_i_9
       (.I0(\Delay7_out_reg[7]_0 [6]),
        .I1(\Delay7_out_reg[7] ),
        .I2(\Delay7_out_reg[7]_0 [7]),
        .O(state_Out_tmp0_carry_i_9_n_0));
endmodule

(* ORIG_REF_NAME = "IncreEncoder_V24_ip_src_Counter" *) 
module zusys_IncreEncoder_V24_ip_0_0_IncreEncoder_V24_ip_src_Counter
   (reset_old1_out1,
    reset_old_out1,
    count_2_reg,
    DI,
    I_0,
    I_1,
    count_2_reg_0,
    count_2_reg_1,
    count_2_reg_2,
    RSTP,
    reset_old1_out1_reg_0,
    IPCORE_CLK,
    reset_old_out1_reg_0,
    count_2,
    reset_old4_out1,
    I,
    reset_old3_out1,
    reset_old3_out1_0);
  output reset_old1_out1;
  output reset_old_out1;
  output count_2_reg;
  output [6:0]DI;
  output I_0;
  output I_1;
  output [6:0]count_2_reg_0;
  output [6:0]count_2_reg_1;
  output [6:0]count_2_reg_2;
  input RSTP;
  input reset_old1_out1_reg_0;
  input IPCORE_CLK;
  input reset_old_out1_reg_0;
  input count_2;
  input [0:0]reset_old4_out1;
  input I;
  input reset_old3_out1;
  input reset_old3_out1_0;

  wire [6:0]DI;
  wire I;
  wire IPCORE_CLK;
  wire I_0;
  wire I_1;
  wire RSTP;
  wire count_2;
  wire count_2_reg;
  wire [6:0]count_2_reg_0;
  wire [6:0]count_2_reg_1;
  wire [6:0]count_2_reg_2;
  wire reset_old1_out1;
  wire reset_old1_out1_reg_0;
  wire reset_old3_out1;
  wire reset_old3_out1_0;
  wire [0:0]reset_old4_out1;
  wire reset_old_out1;
  wire reset_old_out1_reg_0;

  LUT3 #(
    .INIT(8'h60)) 
    Add1_out1_carry__0_i_1
       (.I0(count_2),
        .I1(reset_old1_out1),
        .I2(reset_old4_out1),
        .O(DI[6]));
  LUT3 #(
    .INIT(8'h60)) 
    Add1_out1_carry__0_i_1__0
       (.I0(count_2),
        .I1(reset_old1_out1),
        .I2(reset_old4_out1),
        .O(count_2_reg_1[6]));
  LUT3 #(
    .INIT(8'h60)) 
    Add1_out1_carry__0_i_2
       (.I0(count_2),
        .I1(reset_old1_out1),
        .I2(reset_old4_out1),
        .O(count_2_reg_1[5]));
  LUT3 #(
    .INIT(8'h60)) 
    Add1_out1_carry__0_i_2__0
       (.I0(count_2),
        .I1(reset_old1_out1),
        .I2(reset_old4_out1),
        .O(DI[5]));
  LUT3 #(
    .INIT(8'h60)) 
    Add1_out1_carry__0_i_3
       (.I0(count_2),
        .I1(reset_old1_out1),
        .I2(reset_old4_out1),
        .O(count_2_reg_1[4]));
  LUT3 #(
    .INIT(8'h60)) 
    Add1_out1_carry__0_i_3__0
       (.I0(count_2),
        .I1(reset_old1_out1),
        .I2(reset_old4_out1),
        .O(DI[4]));
  LUT3 #(
    .INIT(8'h60)) 
    Add1_out1_carry__0_i_4
       (.I0(count_2),
        .I1(reset_old1_out1),
        .I2(reset_old4_out1),
        .O(count_2_reg_1[3]));
  LUT3 #(
    .INIT(8'h60)) 
    Add1_out1_carry__0_i_4__0
       (.I0(count_2),
        .I1(reset_old1_out1),
        .I2(reset_old4_out1),
        .O(DI[3]));
  LUT3 #(
    .INIT(8'h60)) 
    Add1_out1_carry__0_i_5
       (.I0(count_2),
        .I1(reset_old1_out1),
        .I2(reset_old4_out1),
        .O(count_2_reg_1[2]));
  LUT3 #(
    .INIT(8'h60)) 
    Add1_out1_carry__0_i_5__0
       (.I0(count_2),
        .I1(reset_old1_out1),
        .I2(reset_old4_out1),
        .O(DI[2]));
  LUT3 #(
    .INIT(8'h60)) 
    Add1_out1_carry__0_i_6
       (.I0(count_2),
        .I1(reset_old1_out1),
        .I2(reset_old4_out1),
        .O(count_2_reg_1[1]));
  LUT3 #(
    .INIT(8'h60)) 
    Add1_out1_carry__0_i_6__0
       (.I0(count_2),
        .I1(reset_old1_out1),
        .I2(reset_old4_out1),
        .O(DI[1]));
  LUT3 #(
    .INIT(8'h60)) 
    Add1_out1_carry__0_i_7
       (.I0(count_2),
        .I1(reset_old1_out1),
        .I2(reset_old4_out1),
        .O(count_2_reg_1[0]));
  LUT3 #(
    .INIT(8'h60)) 
    Add1_out1_carry__0_i_7__0
       (.I0(count_2),
        .I1(reset_old1_out1),
        .I2(reset_old4_out1),
        .O(DI[0]));
  LUT3 #(
    .INIT(8'h60)) 
    Add1_out1_carry_i_1
       (.I0(count_2),
        .I1(reset_old1_out1),
        .I2(reset_old4_out1),
        .O(count_2_reg_0[6]));
  LUT3 #(
    .INIT(8'h60)) 
    Add1_out1_carry_i_1__0
       (.I0(count_2),
        .I1(reset_old1_out1),
        .I2(reset_old4_out1),
        .O(count_2_reg_2[6]));
  LUT3 #(
    .INIT(8'h60)) 
    Add1_out1_carry_i_2
       (.I0(count_2),
        .I1(reset_old1_out1),
        .I2(reset_old4_out1),
        .O(count_2_reg_0[5]));
  LUT3 #(
    .INIT(8'h60)) 
    Add1_out1_carry_i_2__0
       (.I0(count_2),
        .I1(reset_old1_out1),
        .I2(reset_old4_out1),
        .O(count_2_reg_2[5]));
  LUT3 #(
    .INIT(8'h60)) 
    Add1_out1_carry_i_3
       (.I0(count_2),
        .I1(reset_old1_out1),
        .I2(reset_old4_out1),
        .O(count_2_reg_0[4]));
  LUT3 #(
    .INIT(8'h60)) 
    Add1_out1_carry_i_3__0
       (.I0(count_2),
        .I1(reset_old1_out1),
        .I2(reset_old4_out1),
        .O(count_2_reg_2[4]));
  LUT3 #(
    .INIT(8'h60)) 
    Add1_out1_carry_i_4
       (.I0(count_2),
        .I1(reset_old1_out1),
        .I2(reset_old4_out1),
        .O(count_2_reg_0[3]));
  LUT3 #(
    .INIT(8'h60)) 
    Add1_out1_carry_i_4__0
       (.I0(count_2),
        .I1(reset_old1_out1),
        .I2(reset_old4_out1),
        .O(count_2_reg_2[3]));
  LUT3 #(
    .INIT(8'h60)) 
    Add1_out1_carry_i_5
       (.I0(count_2),
        .I1(reset_old1_out1),
        .I2(reset_old4_out1),
        .O(count_2_reg_0[2]));
  LUT3 #(
    .INIT(8'h60)) 
    Add1_out1_carry_i_5__0
       (.I0(count_2),
        .I1(reset_old1_out1),
        .I2(reset_old4_out1),
        .O(count_2_reg_2[2]));
  LUT3 #(
    .INIT(8'h60)) 
    Add1_out1_carry_i_6
       (.I0(count_2),
        .I1(reset_old1_out1),
        .I2(reset_old4_out1),
        .O(count_2_reg_0[1]));
  LUT3 #(
    .INIT(8'h60)) 
    Add1_out1_carry_i_6__0
       (.I0(count_2),
        .I1(reset_old1_out1),
        .I2(reset_old4_out1),
        .O(count_2_reg_2[1]));
  LUT3 #(
    .INIT(8'h60)) 
    Add1_out1_carry_i_7
       (.I0(count_2),
        .I1(reset_old1_out1),
        .I2(reset_old4_out1),
        .O(count_2_reg_0[0]));
  LUT3 #(
    .INIT(8'h60)) 
    Add1_out1_carry_i_7__0
       (.I0(count_2),
        .I1(reset_old1_out1),
        .I2(reset_old4_out1),
        .O(count_2_reg_2[0]));
  LUT2 #(
    .INIT(4'h6)) 
    edge_rsvd_i_1
       (.I0(count_2),
        .I1(reset_old1_out1),
        .O(count_2_reg));
  FDRE reset_old1_out1_reg
       (.C(IPCORE_CLK),
        .CE(1'b1),
        .D(reset_old1_out1_reg_0),
        .Q(reset_old1_out1),
        .R(RSTP));
  (* SOFT_HLUTNM = "soft_lutpair13" *) 
  LUT3 #(
    .INIT(8'hF6)) 
    reset_old3_out10_carry_i_19
       (.I0(I),
        .I1(reset_old_out1),
        .I2(reset_old3_out1),
        .O(I_0));
  (* SOFT_HLUTNM = "soft_lutpair13" *) 
  LUT3 #(
    .INIT(8'hF6)) 
    reset_old3_out10_carry_i_19__0
       (.I0(I),
        .I1(reset_old_out1),
        .I2(reset_old3_out1_0),
        .O(I_1));
  FDRE reset_old_out1_reg
       (.C(IPCORE_CLK),
        .CE(1'b1),
        .D(reset_old_out1_reg_0),
        .Q(reset_old_out1),
        .R(RSTP));
endmodule

(* ORIG_REF_NAME = "IncreEncoder_V24_ip_src_Counter_position" *) 
module zusys_IncreEncoder_V24_ip_0_0_IncreEncoder_V24_ip_src_Counter_position
   (reset_old3_out1,
    reset_old2_out1,
    count_mech,
    RSTP,
    CEP,
    IPCORE_CLK,
    DI,
    S,
    \position_tmp_reg[15] ,
    \position_tmp_reg[15]_0 ,
    I,
    reset_old_out1,
    \position_tmp_reg[0] ,
    reset_old2_out1_reg_0,
    reset_old3_out1_reg_0,
    reset_old3_out10_carry_i_9_0,
    reset_old3_out10_carry_i_9_1,
    Q);
  output reset_old3_out1;
  output reset_old2_out1;
  output [15:0]count_mech;
  input RSTP;
  input CEP;
  input IPCORE_CLK;
  input [7:0]DI;
  input [7:0]S;
  input [6:0]\position_tmp_reg[15] ;
  input [7:0]\position_tmp_reg[15]_0 ;
  input I;
  input reset_old_out1;
  input \position_tmp_reg[0] ;
  input reset_old2_out1_reg_0;
  input reset_old3_out1_reg_0;
  input reset_old3_out10_carry_i_9_0;
  input reset_old3_out10_carry_i_9_1;
  input [15:0]Q;

  wire Add1_out1_carry__0_n_1;
  wire Add1_out1_carry__0_n_2;
  wire Add1_out1_carry__0_n_3;
  wire Add1_out1_carry__0_n_4;
  wire Add1_out1_carry__0_n_5;
  wire Add1_out1_carry__0_n_6;
  wire Add1_out1_carry__0_n_7;
  wire Add1_out1_carry_n_0;
  wire Add1_out1_carry_n_1;
  wire Add1_out1_carry_n_2;
  wire Add1_out1_carry_n_3;
  wire Add1_out1_carry_n_4;
  wire Add1_out1_carry_n_5;
  wire Add1_out1_carry_n_6;
  wire Add1_out1_carry_n_7;
  wire CEP;
  wire [7:0]DI;
  wire I;
  wire IPCORE_CLK;
  wire [15:0]Q;
  wire RSTP;
  wire Relational_Operator1_relop1;
  wire Relational_Operator_relop1;
  wire [15:15]Resett_switch3_out1;
  wire [7:0]S;
  wire [15:0]count_mech;
  wire [15:0]data0;
  wire \position_tmp_reg[0] ;
  wire [6:0]\position_tmp_reg[15] ;
  wire [7:0]\position_tmp_reg[15]_0 ;
  wire reset_old2_out1;
  wire reset_old2_out10_carry_i_2_n_0;
  wire reset_old2_out10_carry_i_3_n_0;
  wire reset_old2_out10_carry_i_4_n_0;
  wire reset_old2_out10_carry_i_5_n_0;
  wire reset_old2_out10_carry_i_6_n_0;
  wire reset_old2_out10_carry_i_7_n_0;
  wire reset_old2_out10_carry_i_8_n_0;
  wire reset_old2_out10_carry_i_9_n_0;
  wire reset_old2_out10_carry_n_1;
  wire reset_old2_out10_carry_n_2;
  wire reset_old2_out10_carry_n_3;
  wire reset_old2_out10_carry_n_4;
  wire reset_old2_out10_carry_n_5;
  wire reset_old2_out10_carry_n_6;
  wire reset_old2_out10_carry_n_7;
  wire reset_old2_out1_reg_0;
  wire reset_old3_out1;
  wire reset_old3_out10_carry_i_10_n_0;
  wire reset_old3_out10_carry_i_11_n_0;
  wire reset_old3_out10_carry_i_12_n_0;
  wire reset_old3_out10_carry_i_13_n_0;
  wire reset_old3_out10_carry_i_14_n_0;
  wire reset_old3_out10_carry_i_15_n_0;
  wire reset_old3_out10_carry_i_16_n_0;
  wire reset_old3_out10_carry_i_17_n_0;
  wire reset_old3_out10_carry_i_18_n_0;
  wire reset_old3_out10_carry_i_1_n_0;
  wire reset_old3_out10_carry_i_2_n_0;
  wire reset_old3_out10_carry_i_3_n_0;
  wire reset_old3_out10_carry_i_4_n_0;
  wire reset_old3_out10_carry_i_5_n_0;
  wire reset_old3_out10_carry_i_6_n_0;
  wire reset_old3_out10_carry_i_7_n_0;
  wire reset_old3_out10_carry_i_8_n_0;
  wire reset_old3_out10_carry_i_9_0;
  wire reset_old3_out10_carry_i_9_1;
  wire reset_old3_out10_carry_i_9_n_0;
  wire reset_old3_out10_carry_n_1;
  wire reset_old3_out10_carry_n_2;
  wire reset_old3_out10_carry_n_3;
  wire reset_old3_out10_carry_n_4;
  wire reset_old3_out10_carry_n_5;
  wire reset_old3_out10_carry_n_6;
  wire reset_old3_out10_carry_n_7;
  wire reset_old3_out1_reg_0;
  wire [15:0]reset_old5_out1;
  wire reset_old_out1;
  wire [7:7]NLW_Add1_out1_carry__0_CO_UNCONNECTED;
  wire [7:0]NLW_reset_old2_out10_carry_O_UNCONNECTED;
  wire [7:0]NLW_reset_old3_out10_carry_O_UNCONNECTED;

  (* ADDER_THRESHOLD = "35" *) 
  (* METHODOLOGY_DRC_VIOS = "{SYNTH-8 {cell *THIS*}}" *) 
  CARRY8 Add1_out1_carry
       (.CI(1'b0),
        .CI_TOP(1'b0),
        .CO({Add1_out1_carry_n_0,Add1_out1_carry_n_1,Add1_out1_carry_n_2,Add1_out1_carry_n_3,Add1_out1_carry_n_4,Add1_out1_carry_n_5,Add1_out1_carry_n_6,Add1_out1_carry_n_7}),
        .DI(DI),
        .O(data0[7:0]),
        .S(S));
  (* ADDER_THRESHOLD = "35" *) 
  (* METHODOLOGY_DRC_VIOS = "{SYNTH-8 {cell *THIS*}}" *) 
  CARRY8 Add1_out1_carry__0
       (.CI(Add1_out1_carry_n_0),
        .CI_TOP(1'b0),
        .CO({NLW_Add1_out1_carry__0_CO_UNCONNECTED[7],Add1_out1_carry__0_n_1,Add1_out1_carry__0_n_2,Add1_out1_carry__0_n_3,Add1_out1_carry__0_n_4,Add1_out1_carry__0_n_5,Add1_out1_carry__0_n_6,Add1_out1_carry__0_n_7}),
        .DI({1'b0,\position_tmp_reg[15] }),
        .O(data0[15:8]),
        .S(\position_tmp_reg[15]_0 ));
  LUT6 #(
    .INIT(64'h000000008282FF00)) 
    \position_tmp[0]_i_1 
       (.I0(data0[0]),
        .I1(reset_old_out1),
        .I2(I),
        .I3(reset_old5_out1[0]),
        .I4(\position_tmp_reg[0] ),
        .I5(reset_old3_out1),
        .O(count_mech[0]));
  LUT6 #(
    .INIT(64'h000000008282FF00)) 
    \position_tmp[10]_i_1 
       (.I0(data0[10]),
        .I1(reset_old_out1),
        .I2(I),
        .I3(reset_old5_out1[10]),
        .I4(\position_tmp_reg[0] ),
        .I5(reset_old3_out1),
        .O(count_mech[10]));
  LUT6 #(
    .INIT(64'h000000008282FF00)) 
    \position_tmp[11]_i_1 
       (.I0(data0[11]),
        .I1(reset_old_out1),
        .I2(I),
        .I3(reset_old5_out1[11]),
        .I4(\position_tmp_reg[0] ),
        .I5(reset_old3_out1),
        .O(count_mech[11]));
  LUT6 #(
    .INIT(64'h000000008282FF00)) 
    \position_tmp[12]_i_1 
       (.I0(data0[12]),
        .I1(reset_old_out1),
        .I2(I),
        .I3(reset_old5_out1[12]),
        .I4(\position_tmp_reg[0] ),
        .I5(reset_old3_out1),
        .O(count_mech[12]));
  LUT6 #(
    .INIT(64'h000000008282FF00)) 
    \position_tmp[13]_i_1 
       (.I0(data0[13]),
        .I1(reset_old_out1),
        .I2(I),
        .I3(reset_old5_out1[13]),
        .I4(\position_tmp_reg[0] ),
        .I5(reset_old3_out1),
        .O(count_mech[13]));
  LUT6 #(
    .INIT(64'h000000008282FF00)) 
    \position_tmp[14]_i_1 
       (.I0(data0[14]),
        .I1(reset_old_out1),
        .I2(I),
        .I3(reset_old5_out1[14]),
        .I4(\position_tmp_reg[0] ),
        .I5(reset_old3_out1),
        .O(count_mech[14]));
  LUT6 #(
    .INIT(64'h000000008282FF00)) 
    \position_tmp[15]_i_1 
       (.I0(data0[15]),
        .I1(reset_old_out1),
        .I2(I),
        .I3(reset_old5_out1[15]),
        .I4(\position_tmp_reg[0] ),
        .I5(reset_old3_out1),
        .O(count_mech[15]));
  LUT6 #(
    .INIT(64'h000000008282FF00)) 
    \position_tmp[1]_i_1 
       (.I0(data0[1]),
        .I1(reset_old_out1),
        .I2(I),
        .I3(reset_old5_out1[1]),
        .I4(\position_tmp_reg[0] ),
        .I5(reset_old3_out1),
        .O(count_mech[1]));
  LUT6 #(
    .INIT(64'h000000008282FF00)) 
    \position_tmp[2]_i_1 
       (.I0(data0[2]),
        .I1(reset_old_out1),
        .I2(I),
        .I3(reset_old5_out1[2]),
        .I4(\position_tmp_reg[0] ),
        .I5(reset_old3_out1),
        .O(count_mech[2]));
  LUT6 #(
    .INIT(64'h000000008282FF00)) 
    \position_tmp[3]_i_1 
       (.I0(data0[3]),
        .I1(reset_old_out1),
        .I2(I),
        .I3(reset_old5_out1[3]),
        .I4(\position_tmp_reg[0] ),
        .I5(reset_old3_out1),
        .O(count_mech[3]));
  LUT6 #(
    .INIT(64'h000000008282FF00)) 
    \position_tmp[4]_i_1 
       (.I0(data0[4]),
        .I1(reset_old_out1),
        .I2(I),
        .I3(reset_old5_out1[4]),
        .I4(\position_tmp_reg[0] ),
        .I5(reset_old3_out1),
        .O(count_mech[4]));
  LUT6 #(
    .INIT(64'h000000008282FF00)) 
    \position_tmp[5]_i_1 
       (.I0(data0[5]),
        .I1(reset_old_out1),
        .I2(I),
        .I3(reset_old5_out1[5]),
        .I4(\position_tmp_reg[0] ),
        .I5(reset_old3_out1),
        .O(count_mech[5]));
  LUT6 #(
    .INIT(64'h000000008282FF00)) 
    \position_tmp[6]_i_1 
       (.I0(data0[6]),
        .I1(reset_old_out1),
        .I2(I),
        .I3(reset_old5_out1[6]),
        .I4(\position_tmp_reg[0] ),
        .I5(reset_old3_out1),
        .O(count_mech[6]));
  LUT6 #(
    .INIT(64'h000000008282FF00)) 
    \position_tmp[7]_i_1 
       (.I0(data0[7]),
        .I1(reset_old_out1),
        .I2(I),
        .I3(reset_old5_out1[7]),
        .I4(\position_tmp_reg[0] ),
        .I5(reset_old3_out1),
        .O(count_mech[7]));
  LUT6 #(
    .INIT(64'h000000008282FF00)) 
    \position_tmp[8]_i_1 
       (.I0(data0[8]),
        .I1(reset_old_out1),
        .I2(I),
        .I3(reset_old5_out1[8]),
        .I4(\position_tmp_reg[0] ),
        .I5(reset_old3_out1),
        .O(count_mech[8]));
  LUT6 #(
    .INIT(64'h000000008282FF00)) 
    \position_tmp[9]_i_1 
       (.I0(data0[9]),
        .I1(reset_old_out1),
        .I2(I),
        .I3(reset_old5_out1[9]),
        .I4(\position_tmp_reg[0] ),
        .I5(reset_old3_out1),
        .O(count_mech[9]));
  (* COMPARATOR_THRESHOLD = "14" *) 
  (* METHODOLOGY_DRC_VIOS = "{SYNTH-8 {cell *THIS*}}" *) 
  CARRY8 reset_old2_out10_carry
       (.CI(1'b1),
        .CI_TOP(1'b0),
        .CO({Relational_Operator1_relop1,reset_old2_out10_carry_n_1,reset_old2_out10_carry_n_2,reset_old2_out10_carry_n_3,reset_old2_out10_carry_n_4,reset_old2_out10_carry_n_5,reset_old2_out10_carry_n_6,reset_old2_out10_carry_n_7}),
        .DI({Resett_switch3_out1,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .O(NLW_reset_old2_out10_carry_O_UNCONNECTED[7:0]),
        .S({reset_old2_out10_carry_i_2_n_0,reset_old2_out10_carry_i_3_n_0,reset_old2_out10_carry_i_4_n_0,reset_old2_out10_carry_i_5_n_0,reset_old2_out10_carry_i_6_n_0,reset_old2_out10_carry_i_7_n_0,reset_old2_out10_carry_i_8_n_0,reset_old2_out10_carry_i_9_n_0}));
  LUT5 #(
    .INIT(32'h82FF8200)) 
    reset_old2_out10_carry_i_1
       (.I0(data0[15]),
        .I1(I),
        .I2(reset_old_out1),
        .I3(\position_tmp_reg[0] ),
        .I4(reset_old5_out1[15]),
        .O(Resett_switch3_out1));
  LUT6 #(
    .INIT(64'hAAABAAABAAABFFAB)) 
    reset_old2_out10_carry_i_2
       (.I0(reset_old2_out1_reg_0),
        .I1(reset_old5_out1[15]),
        .I2(reset_old5_out1[14]),
        .I3(\position_tmp_reg[0] ),
        .I4(data0[14]),
        .I5(data0[15]),
        .O(reset_old2_out10_carry_i_2_n_0));
  LUT6 #(
    .INIT(64'hAAABAAABAAABFFAB)) 
    reset_old2_out10_carry_i_3
       (.I0(reset_old2_out1_reg_0),
        .I1(reset_old5_out1[13]),
        .I2(reset_old5_out1[12]),
        .I3(\position_tmp_reg[0] ),
        .I4(data0[12]),
        .I5(data0[13]),
        .O(reset_old2_out10_carry_i_3_n_0));
  LUT6 #(
    .INIT(64'hAAABAAABAAABFFAB)) 
    reset_old2_out10_carry_i_4
       (.I0(reset_old2_out1_reg_0),
        .I1(reset_old5_out1[11]),
        .I2(reset_old5_out1[10]),
        .I3(\position_tmp_reg[0] ),
        .I4(data0[10]),
        .I5(data0[11]),
        .O(reset_old2_out10_carry_i_4_n_0));
  LUT6 #(
    .INIT(64'hAAABAAABAAABFFAB)) 
    reset_old2_out10_carry_i_5
       (.I0(reset_old2_out1_reg_0),
        .I1(reset_old5_out1[9]),
        .I2(reset_old5_out1[8]),
        .I3(\position_tmp_reg[0] ),
        .I4(data0[8]),
        .I5(data0[9]),
        .O(reset_old2_out10_carry_i_5_n_0));
  LUT6 #(
    .INIT(64'hAAABAAABAAABFFAB)) 
    reset_old2_out10_carry_i_6
       (.I0(reset_old2_out1_reg_0),
        .I1(reset_old5_out1[7]),
        .I2(reset_old5_out1[6]),
        .I3(\position_tmp_reg[0] ),
        .I4(data0[6]),
        .I5(data0[7]),
        .O(reset_old2_out10_carry_i_6_n_0));
  LUT6 #(
    .INIT(64'hAAABAAABAAABFFAB)) 
    reset_old2_out10_carry_i_7
       (.I0(reset_old2_out1_reg_0),
        .I1(reset_old5_out1[5]),
        .I2(reset_old5_out1[4]),
        .I3(\position_tmp_reg[0] ),
        .I4(data0[4]),
        .I5(data0[5]),
        .O(reset_old2_out10_carry_i_7_n_0));
  LUT6 #(
    .INIT(64'hAAABAAABAAABFFAB)) 
    reset_old2_out10_carry_i_8
       (.I0(reset_old2_out1_reg_0),
        .I1(reset_old5_out1[3]),
        .I2(reset_old5_out1[2]),
        .I3(\position_tmp_reg[0] ),
        .I4(data0[2]),
        .I5(data0[3]),
        .O(reset_old2_out10_carry_i_8_n_0));
  LUT6 #(
    .INIT(64'hAAABAAABAAABFFAB)) 
    reset_old2_out10_carry_i_9
       (.I0(reset_old2_out1_reg_0),
        .I1(reset_old5_out1[1]),
        .I2(reset_old5_out1[0]),
        .I3(\position_tmp_reg[0] ),
        .I4(data0[0]),
        .I5(data0[1]),
        .O(reset_old2_out10_carry_i_9_n_0));
  FDRE reset_old2_out1_reg
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Relational_Operator1_relop1),
        .Q(reset_old2_out1),
        .R(RSTP));
  (* COMPARATOR_THRESHOLD = "14" *) 
  (* METHODOLOGY_DRC_VIOS = "{SYNTH-8 {cell *THIS*}}" *) 
  CARRY8 reset_old3_out10_carry
       (.CI(1'b0),
        .CI_TOP(1'b0),
        .CO({Relational_Operator_relop1,reset_old3_out10_carry_n_1,reset_old3_out10_carry_n_2,reset_old3_out10_carry_n_3,reset_old3_out10_carry_n_4,reset_old3_out10_carry_n_5,reset_old3_out10_carry_n_6,reset_old3_out10_carry_n_7}),
        .DI({reset_old3_out10_carry_i_1_n_0,reset_old3_out10_carry_i_2_n_0,reset_old3_out10_carry_i_3_n_0,reset_old3_out10_carry_i_4_n_0,reset_old3_out10_carry_i_5_n_0,reset_old3_out10_carry_i_6_n_0,reset_old3_out10_carry_i_7_n_0,reset_old3_out10_carry_i_8_n_0}),
        .O(NLW_reset_old3_out10_carry_O_UNCONNECTED[7:0]),
        .S({reset_old3_out10_carry_i_9_n_0,reset_old3_out10_carry_i_10_n_0,reset_old3_out10_carry_i_11_n_0,reset_old3_out10_carry_i_12_n_0,reset_old3_out10_carry_i_13_n_0,reset_old3_out10_carry_i_14_n_0,reset_old3_out10_carry_i_15_n_0,reset_old3_out10_carry_i_16_n_0}));
  LUT5 #(
    .INIT(32'h4000F040)) 
    reset_old3_out10_carry_i_1
       (.I0(reset_old5_out1[14]),
        .I1(data0[14]),
        .I2(reset_old3_out10_carry_i_17_n_0),
        .I3(data0[15]),
        .I4(reset_old5_out1[15]),
        .O(reset_old3_out10_carry_i_1_n_0));
  LUT6 #(
    .INIT(64'hAAEAAAAEAABAFFAB)) 
    reset_old3_out10_carry_i_10
       (.I0(reset_old3_out10_carry_i_18_n_0),
        .I1(data0[13]),
        .I2(data0[12]),
        .I3(reset_old3_out1_reg_0),
        .I4(reset_old5_out1[12]),
        .I5(reset_old5_out1[13]),
        .O(reset_old3_out10_carry_i_10_n_0));
  LUT6 #(
    .INIT(64'hAAEAAAAEAABAFFAB)) 
    reset_old3_out10_carry_i_11
       (.I0(reset_old3_out10_carry_i_18_n_0),
        .I1(data0[11]),
        .I2(data0[10]),
        .I3(reset_old3_out1_reg_0),
        .I4(reset_old5_out1[10]),
        .I5(reset_old5_out1[11]),
        .O(reset_old3_out10_carry_i_11_n_0));
  LUT6 #(
    .INIT(64'hAAEAAAAEAABAFFAB)) 
    reset_old3_out10_carry_i_12
       (.I0(reset_old3_out10_carry_i_18_n_0),
        .I1(data0[9]),
        .I2(data0[8]),
        .I3(reset_old3_out1_reg_0),
        .I4(reset_old5_out1[8]),
        .I5(reset_old5_out1[9]),
        .O(reset_old3_out10_carry_i_12_n_0));
  LUT6 #(
    .INIT(64'hAAEAAAAEAABAFFAB)) 
    reset_old3_out10_carry_i_13
       (.I0(reset_old3_out10_carry_i_18_n_0),
        .I1(data0[7]),
        .I2(data0[6]),
        .I3(reset_old3_out1_reg_0),
        .I4(reset_old5_out1[6]),
        .I5(reset_old5_out1[7]),
        .O(reset_old3_out10_carry_i_13_n_0));
  LUT6 #(
    .INIT(64'hAAEAAAAEAABAFFAB)) 
    reset_old3_out10_carry_i_14
       (.I0(reset_old3_out10_carry_i_18_n_0),
        .I1(data0[5]),
        .I2(data0[4]),
        .I3(reset_old3_out1_reg_0),
        .I4(reset_old5_out1[4]),
        .I5(reset_old5_out1[5]),
        .O(reset_old3_out10_carry_i_14_n_0));
  LUT6 #(
    .INIT(64'hAAEAAAAEAABAFFAB)) 
    reset_old3_out10_carry_i_15
       (.I0(reset_old3_out10_carry_i_18_n_0),
        .I1(data0[3]),
        .I2(data0[2]),
        .I3(reset_old3_out1_reg_0),
        .I4(reset_old5_out1[2]),
        .I5(reset_old5_out1[3]),
        .O(reset_old3_out10_carry_i_15_n_0));
  LUT6 #(
    .INIT(64'hAAEAAAAEAABAFFAB)) 
    reset_old3_out10_carry_i_16
       (.I0(reset_old3_out10_carry_i_18_n_0),
        .I1(data0[1]),
        .I2(data0[0]),
        .I3(reset_old3_out1_reg_0),
        .I4(reset_old5_out1[0]),
        .I5(reset_old5_out1[1]),
        .O(reset_old3_out10_carry_i_16_n_0));
  LUT6 #(
    .INIT(64'h0075000000000075)) 
    reset_old3_out10_carry_i_17
       (.I0(reset_old2_out1),
        .I1(reset_old3_out10_carry_i_9_0),
        .I2(reset_old3_out10_carry_i_9_1),
        .I3(reset_old3_out1),
        .I4(reset_old_out1),
        .I5(I),
        .O(reset_old3_out10_carry_i_17_n_0));
  LUT4 #(
    .INIT(16'h008A)) 
    reset_old3_out10_carry_i_18
       (.I0(reset_old2_out1),
        .I1(reset_old3_out10_carry_i_9_0),
        .I2(reset_old3_out10_carry_i_9_1),
        .I3(reset_old3_out1),
        .O(reset_old3_out10_carry_i_18_n_0));
  LUT5 #(
    .INIT(32'h4000F040)) 
    reset_old3_out10_carry_i_2
       (.I0(reset_old5_out1[12]),
        .I1(data0[12]),
        .I2(reset_old3_out10_carry_i_17_n_0),
        .I3(data0[13]),
        .I4(reset_old5_out1[13]),
        .O(reset_old3_out10_carry_i_2_n_0));
  LUT5 #(
    .INIT(32'h4000F040)) 
    reset_old3_out10_carry_i_3
       (.I0(reset_old5_out1[10]),
        .I1(data0[10]),
        .I2(reset_old3_out10_carry_i_17_n_0),
        .I3(data0[11]),
        .I4(reset_old5_out1[11]),
        .O(reset_old3_out10_carry_i_3_n_0));
  LUT5 #(
    .INIT(32'h4000F040)) 
    reset_old3_out10_carry_i_4
       (.I0(reset_old5_out1[8]),
        .I1(data0[8]),
        .I2(reset_old3_out10_carry_i_17_n_0),
        .I3(data0[9]),
        .I4(reset_old5_out1[9]),
        .O(reset_old3_out10_carry_i_4_n_0));
  LUT5 #(
    .INIT(32'h4000F040)) 
    reset_old3_out10_carry_i_5
       (.I0(reset_old5_out1[6]),
        .I1(data0[6]),
        .I2(reset_old3_out10_carry_i_17_n_0),
        .I3(data0[7]),
        .I4(reset_old5_out1[7]),
        .O(reset_old3_out10_carry_i_5_n_0));
  LUT5 #(
    .INIT(32'h4000F040)) 
    reset_old3_out10_carry_i_6
       (.I0(reset_old5_out1[4]),
        .I1(data0[4]),
        .I2(reset_old3_out10_carry_i_17_n_0),
        .I3(data0[5]),
        .I4(reset_old5_out1[5]),
        .O(reset_old3_out10_carry_i_6_n_0));
  LUT5 #(
    .INIT(32'h4000F040)) 
    reset_old3_out10_carry_i_7
       (.I0(reset_old5_out1[2]),
        .I1(data0[2]),
        .I2(reset_old3_out10_carry_i_17_n_0),
        .I3(data0[3]),
        .I4(reset_old5_out1[3]),
        .O(reset_old3_out10_carry_i_7_n_0));
  LUT5 #(
    .INIT(32'h4000F040)) 
    reset_old3_out10_carry_i_8
       (.I0(reset_old5_out1[0]),
        .I1(data0[0]),
        .I2(reset_old3_out10_carry_i_17_n_0),
        .I3(data0[1]),
        .I4(reset_old5_out1[1]),
        .O(reset_old3_out10_carry_i_8_n_0));
  LUT6 #(
    .INIT(64'hAAEAAAAEAABAFFAB)) 
    reset_old3_out10_carry_i_9
       (.I0(reset_old3_out10_carry_i_18_n_0),
        .I1(data0[15]),
        .I2(data0[14]),
        .I3(reset_old3_out1_reg_0),
        .I4(reset_old5_out1[14]),
        .I5(reset_old5_out1[15]),
        .O(reset_old3_out10_carry_i_9_n_0));
  FDRE reset_old3_out1_reg
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Relational_Operator_relop1),
        .Q(reset_old3_out1),
        .R(RSTP));
  FDRE \reset_old5_out1_reg[0] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Q[0]),
        .Q(reset_old5_out1[0]),
        .R(RSTP));
  FDRE \reset_old5_out1_reg[10] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Q[10]),
        .Q(reset_old5_out1[10]),
        .R(RSTP));
  FDRE \reset_old5_out1_reg[11] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Q[11]),
        .Q(reset_old5_out1[11]),
        .R(RSTP));
  FDRE \reset_old5_out1_reg[12] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Q[12]),
        .Q(reset_old5_out1[12]),
        .R(RSTP));
  FDRE \reset_old5_out1_reg[13] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Q[13]),
        .Q(reset_old5_out1[13]),
        .R(RSTP));
  FDRE \reset_old5_out1_reg[14] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Q[14]),
        .Q(reset_old5_out1[14]),
        .R(RSTP));
  FDRE \reset_old5_out1_reg[15] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Q[15]),
        .Q(reset_old5_out1[15]),
        .R(RSTP));
  FDRE \reset_old5_out1_reg[1] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Q[1]),
        .Q(reset_old5_out1[1]),
        .R(RSTP));
  FDRE \reset_old5_out1_reg[2] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Q[2]),
        .Q(reset_old5_out1[2]),
        .R(RSTP));
  FDRE \reset_old5_out1_reg[3] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Q[3]),
        .Q(reset_old5_out1[3]),
        .R(RSTP));
  FDRE \reset_old5_out1_reg[4] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Q[4]),
        .Q(reset_old5_out1[4]),
        .R(RSTP));
  FDRE \reset_old5_out1_reg[5] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Q[5]),
        .Q(reset_old5_out1[5]),
        .R(RSTP));
  FDRE \reset_old5_out1_reg[6] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Q[6]),
        .Q(reset_old5_out1[6]),
        .R(RSTP));
  FDRE \reset_old5_out1_reg[7] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Q[7]),
        .Q(reset_old5_out1[7]),
        .R(RSTP));
  FDRE \reset_old5_out1_reg[8] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Q[8]),
        .Q(reset_old5_out1[8]),
        .R(RSTP));
  FDRE \reset_old5_out1_reg[9] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Q[9]),
        .Q(reset_old5_out1[9]),
        .R(RSTP));
endmodule

(* ORIG_REF_NAME = "IncreEncoder_V24_ip_src_Counter_theta_ele" *) 
module zusys_IncreEncoder_V24_ip_0_0_IncreEncoder_V24_ip_src_Counter_theta_ele
   (reset_old3_out1,
    \reset_old5_out1_reg[0]_0 ,
    \reset_old5_out1_reg[3]_0 ,
    \reset_old4_out1_reg[15]_0 ,
    \reset_old4_out1_reg[15]_1 ,
    I_0,
    D,
    \reset_old5_out1_reg[0]_1 ,
    S,
    RSTP,
    CEP,
    IPCORE_CLK,
    Q,
    \reset_old6_out1_reg[7]_0 ,
    \reset_old6_out1_reg[15]_0 ,
    \reset_old4_out1_reg[0]_0 ,
    \reset_old4_out1_reg[0]_1 ,
    reset_old1_out1,
    count_2,
    position,
    I,
    reset_old_out1,
    reset_old2_out1,
    reset_old3_out10_carry_0,
    \reset_old1_out1_reg[15]_0 );
  output reset_old3_out1;
  output \reset_old5_out1_reg[0]_0 ;
  output \reset_old5_out1_reg[3]_0 ;
  output [0:0]\reset_old4_out1_reg[15]_0 ;
  output [7:0]\reset_old4_out1_reg[15]_1 ;
  output I_0;
  output [15:0]D;
  output \reset_old5_out1_reg[0]_1 ;
  output [7:0]S;
  input RSTP;
  input CEP;
  input IPCORE_CLK;
  input [1:0]Q;
  input [6:0]\reset_old6_out1_reg[7]_0 ;
  input [6:0]\reset_old6_out1_reg[15]_0 ;
  input \reset_old4_out1_reg[0]_0 ;
  input [0:0]\reset_old4_out1_reg[0]_1 ;
  input reset_old1_out1;
  input count_2;
  input [15:0]position;
  input I;
  input reset_old_out1;
  input reset_old2_out1;
  input reset_old3_out10_carry_0;
  input [15:0]\reset_old1_out1_reg[15]_0 ;

  wire Add1_out1_carry__0_i_10_n_0;
  wire Add1_out1_carry__0_i_11_n_0;
  wire Add1_out1_carry__0_i_12_n_0;
  wire Add1_out1_carry__0_i_13_n_0;
  wire Add1_out1_carry__0_i_14_n_0;
  wire Add1_out1_carry__0_i_15_n_0;
  wire Add1_out1_carry__0_i_8_n_0;
  wire Add1_out1_carry__0_i_9_n_0;
  wire Add1_out1_carry__0_n_1;
  wire Add1_out1_carry__0_n_2;
  wire Add1_out1_carry__0_n_3;
  wire Add1_out1_carry__0_n_4;
  wire Add1_out1_carry__0_n_5;
  wire Add1_out1_carry__0_n_6;
  wire Add1_out1_carry__0_n_7;
  wire Add1_out1_carry_i_10_n_0;
  wire Add1_out1_carry_i_11_n_0;
  wire Add1_out1_carry_i_12_n_0;
  wire Add1_out1_carry_i_13_n_0;
  wire Add1_out1_carry_i_14_n_0;
  wire Add1_out1_carry_i_15_n_0;
  wire Add1_out1_carry_i_8_n_0;
  wire Add1_out1_carry_i_9_n_0;
  wire Add1_out1_carry_n_0;
  wire Add1_out1_carry_n_1;
  wire Add1_out1_carry_n_2;
  wire Add1_out1_carry_n_3;
  wire Add1_out1_carry_n_4;
  wire Add1_out1_carry_n_5;
  wire Add1_out1_carry_n_6;
  wire Add1_out1_carry_n_7;
  wire CEP;
  wire [15:0]D;
  wire I;
  wire IPCORE_CLK;
  wire I_0;
  wire [1:0]Q;
  wire RSTP;
  wire Relational_Operator1_relop1;
  wire Relational_Operator_relop1;
  wire [15:15]Reset_switch3_out1;
  wire [7:0]S;
  wire count_2;
  wire [15:0]data0;
  wire [15:15]p_1_in;
  wire [15:0]position;
  wire reset_old1_out1;
  wire [15:0]reset_old1_out1_1;
  wire [15:0]\reset_old1_out1_reg[15]_0 ;
  wire reset_old2_out1;
  wire reset_old2_out10_carry_i_10__0_n_0;
  wire reset_old2_out10_carry_i_2__0_n_0;
  wire reset_old2_out10_carry_i_3__0_n_0;
  wire reset_old2_out10_carry_i_4__0_n_0;
  wire reset_old2_out10_carry_i_5__0_n_0;
  wire reset_old2_out10_carry_i_6__0_n_0;
  wire reset_old2_out10_carry_i_7__0_n_0;
  wire reset_old2_out10_carry_i_8__0_n_0;
  wire reset_old2_out10_carry_i_9__0_n_0;
  wire reset_old2_out10_carry_n_1;
  wire reset_old2_out10_carry_n_2;
  wire reset_old2_out10_carry_n_3;
  wire reset_old2_out10_carry_n_4;
  wire reset_old2_out10_carry_n_5;
  wire reset_old2_out10_carry_n_6;
  wire reset_old2_out10_carry_n_7;
  wire reset_old2_out1_0;
  wire reset_old3_out1;
  wire reset_old3_out10_carry_0;
  wire reset_old3_out10_carry__0_i_1_n_0;
  wire reset_old3_out10_carry_i_10__0_n_0;
  wire reset_old3_out10_carry_i_11__0_n_0;
  wire reset_old3_out10_carry_i_12__0_n_0;
  wire reset_old3_out10_carry_i_13__0_n_0;
  wire reset_old3_out10_carry_i_14__0_n_0;
  wire reset_old3_out10_carry_i_15__0_n_0;
  wire reset_old3_out10_carry_i_16__0_n_0;
  wire reset_old3_out10_carry_i_17__0_n_0;
  wire reset_old3_out10_carry_i_18__0_n_0;
  wire reset_old3_out10_carry_i_1__0_n_0;
  wire reset_old3_out10_carry_i_2__0_n_0;
  wire reset_old3_out10_carry_i_3__0_n_0;
  wire reset_old3_out10_carry_i_4__0_n_0;
  wire reset_old3_out10_carry_i_5__0_n_0;
  wire reset_old3_out10_carry_i_6__0_n_0;
  wire reset_old3_out10_carry_i_7__0_n_0;
  wire reset_old3_out10_carry_i_8__0_n_0;
  wire reset_old3_out10_carry_i_9__0_n_0;
  wire reset_old3_out10_carry_n_0;
  wire reset_old3_out10_carry_n_1;
  wire reset_old3_out10_carry_n_2;
  wire reset_old3_out10_carry_n_3;
  wire reset_old3_out10_carry_n_4;
  wire reset_old3_out10_carry_n_5;
  wire reset_old3_out10_carry_n_6;
  wire reset_old3_out10_carry_n_7;
  wire [0:0]reset_old4_out1;
  wire \reset_old4_out1_reg[0]_0 ;
  wire [0:0]\reset_old4_out1_reg[0]_1 ;
  wire [0:0]\reset_old4_out1_reg[15]_0 ;
  wire [7:0]\reset_old4_out1_reg[15]_1 ;
  wire \reset_old5_out1_reg[0]_0 ;
  wire \reset_old5_out1_reg[0]_1 ;
  wire \reset_old5_out1_reg[3]_0 ;
  wire [15:0]reset_old6_out1;
  wire [6:0]\reset_old6_out1_reg[15]_0 ;
  wire [6:0]\reset_old6_out1_reg[7]_0 ;
  wire reset_old_out1;
  wire theta_el_tmp_reg_i_19_n_0;
  wire [7:7]NLW_Add1_out1_carry__0_CO_UNCONNECTED;
  wire [7:0]NLW_reset_old2_out10_carry_O_UNCONNECTED;
  wire [7:0]NLW_reset_old3_out10_carry_O_UNCONNECTED;
  wire [7:1]NLW_reset_old3_out10_carry__0_CO_UNCONNECTED;
  wire [7:0]NLW_reset_old3_out10_carry__0_O_UNCONNECTED;

  (* ADDER_THRESHOLD = "35" *) 
  (* METHODOLOGY_DRC_VIOS = "{SYNTH-8 {cell *THIS*}}" *) 
  CARRY8 Add1_out1_carry
       (.CI(1'b0),
        .CI_TOP(1'b0),
        .CO({Add1_out1_carry_n_0,Add1_out1_carry_n_1,Add1_out1_carry_n_2,Add1_out1_carry_n_3,Add1_out1_carry_n_4,Add1_out1_carry_n_5,Add1_out1_carry_n_6,Add1_out1_carry_n_7}),
        .DI({\reset_old6_out1_reg[7]_0 ,reset_old6_out1[0]}),
        .O(data0[7:0]),
        .S({Add1_out1_carry_i_8_n_0,Add1_out1_carry_i_9_n_0,Add1_out1_carry_i_10_n_0,Add1_out1_carry_i_11_n_0,Add1_out1_carry_i_12_n_0,Add1_out1_carry_i_13_n_0,Add1_out1_carry_i_14_n_0,Add1_out1_carry_i_15_n_0}));
  (* ADDER_THRESHOLD = "35" *) 
  (* METHODOLOGY_DRC_VIOS = "{SYNTH-8 {cell *THIS*}}" *) 
  CARRY8 Add1_out1_carry__0
       (.CI(Add1_out1_carry_n_0),
        .CI_TOP(1'b0),
        .CO({NLW_Add1_out1_carry__0_CO_UNCONNECTED[7],Add1_out1_carry__0_n_1,Add1_out1_carry__0_n_2,Add1_out1_carry__0_n_3,Add1_out1_carry__0_n_4,Add1_out1_carry__0_n_5,Add1_out1_carry__0_n_6,Add1_out1_carry__0_n_7}),
        .DI({1'b0,\reset_old6_out1_reg[15]_0 }),
        .O(data0[15:8]),
        .S({Add1_out1_carry__0_i_8_n_0,Add1_out1_carry__0_i_9_n_0,Add1_out1_carry__0_i_10_n_0,Add1_out1_carry__0_i_11_n_0,Add1_out1_carry__0_i_12_n_0,Add1_out1_carry__0_i_13_n_0,Add1_out1_carry__0_i_14_n_0,Add1_out1_carry__0_i_15_n_0}));
  LUT4 #(
    .INIT(16'hD728)) 
    Add1_out1_carry__0_i_10
       (.I0(\reset_old4_out1_reg[15]_0 ),
        .I1(reset_old1_out1),
        .I2(count_2),
        .I3(reset_old6_out1[13]),
        .O(Add1_out1_carry__0_i_10_n_0));
  LUT4 #(
    .INIT(16'hD728)) 
    Add1_out1_carry__0_i_10__0
       (.I0(\reset_old4_out1_reg[15]_0 ),
        .I1(reset_old1_out1),
        .I2(count_2),
        .I3(position[13]),
        .O(\reset_old4_out1_reg[15]_1 [5]));
  LUT4 #(
    .INIT(16'hD728)) 
    Add1_out1_carry__0_i_11
       (.I0(\reset_old4_out1_reg[15]_0 ),
        .I1(reset_old1_out1),
        .I2(count_2),
        .I3(reset_old6_out1[12]),
        .O(Add1_out1_carry__0_i_11_n_0));
  LUT4 #(
    .INIT(16'hD728)) 
    Add1_out1_carry__0_i_11__0
       (.I0(\reset_old4_out1_reg[15]_0 ),
        .I1(reset_old1_out1),
        .I2(count_2),
        .I3(position[12]),
        .O(\reset_old4_out1_reg[15]_1 [4]));
  LUT4 #(
    .INIT(16'hD728)) 
    Add1_out1_carry__0_i_12
       (.I0(\reset_old4_out1_reg[15]_0 ),
        .I1(reset_old1_out1),
        .I2(count_2),
        .I3(reset_old6_out1[11]),
        .O(Add1_out1_carry__0_i_12_n_0));
  LUT4 #(
    .INIT(16'hD728)) 
    Add1_out1_carry__0_i_12__0
       (.I0(\reset_old4_out1_reg[15]_0 ),
        .I1(reset_old1_out1),
        .I2(count_2),
        .I3(position[11]),
        .O(\reset_old4_out1_reg[15]_1 [3]));
  LUT4 #(
    .INIT(16'hD728)) 
    Add1_out1_carry__0_i_13
       (.I0(\reset_old4_out1_reg[15]_0 ),
        .I1(reset_old1_out1),
        .I2(count_2),
        .I3(reset_old6_out1[10]),
        .O(Add1_out1_carry__0_i_13_n_0));
  LUT4 #(
    .INIT(16'hD728)) 
    Add1_out1_carry__0_i_13__0
       (.I0(\reset_old4_out1_reg[15]_0 ),
        .I1(reset_old1_out1),
        .I2(count_2),
        .I3(position[10]),
        .O(\reset_old4_out1_reg[15]_1 [2]));
  LUT4 #(
    .INIT(16'hD728)) 
    Add1_out1_carry__0_i_14
       (.I0(\reset_old4_out1_reg[15]_0 ),
        .I1(reset_old1_out1),
        .I2(count_2),
        .I3(reset_old6_out1[9]),
        .O(Add1_out1_carry__0_i_14_n_0));
  LUT4 #(
    .INIT(16'hD728)) 
    Add1_out1_carry__0_i_14__0
       (.I0(\reset_old4_out1_reg[15]_0 ),
        .I1(reset_old1_out1),
        .I2(count_2),
        .I3(position[9]),
        .O(\reset_old4_out1_reg[15]_1 [1]));
  LUT4 #(
    .INIT(16'hD728)) 
    Add1_out1_carry__0_i_15
       (.I0(\reset_old4_out1_reg[15]_0 ),
        .I1(reset_old1_out1),
        .I2(count_2),
        .I3(reset_old6_out1[8]),
        .O(Add1_out1_carry__0_i_15_n_0));
  LUT4 #(
    .INIT(16'hD728)) 
    Add1_out1_carry__0_i_15__0
       (.I0(\reset_old4_out1_reg[15]_0 ),
        .I1(reset_old1_out1),
        .I2(count_2),
        .I3(position[8]),
        .O(\reset_old4_out1_reg[15]_1 [0]));
  LUT4 #(
    .INIT(16'hD728)) 
    Add1_out1_carry__0_i_8
       (.I0(\reset_old4_out1_reg[15]_0 ),
        .I1(reset_old1_out1),
        .I2(count_2),
        .I3(reset_old6_out1[15]),
        .O(Add1_out1_carry__0_i_8_n_0));
  LUT4 #(
    .INIT(16'hD728)) 
    Add1_out1_carry__0_i_8__0
       (.I0(\reset_old4_out1_reg[15]_0 ),
        .I1(reset_old1_out1),
        .I2(count_2),
        .I3(position[15]),
        .O(\reset_old4_out1_reg[15]_1 [7]));
  LUT4 #(
    .INIT(16'hD728)) 
    Add1_out1_carry__0_i_9
       (.I0(\reset_old4_out1_reg[15]_0 ),
        .I1(reset_old1_out1),
        .I2(count_2),
        .I3(reset_old6_out1[14]),
        .O(Add1_out1_carry__0_i_9_n_0));
  LUT4 #(
    .INIT(16'hD728)) 
    Add1_out1_carry__0_i_9__0
       (.I0(\reset_old4_out1_reg[15]_0 ),
        .I1(reset_old1_out1),
        .I2(count_2),
        .I3(position[14]),
        .O(\reset_old4_out1_reg[15]_1 [6]));
  LUT4 #(
    .INIT(16'hD728)) 
    Add1_out1_carry_i_10
       (.I0(\reset_old4_out1_reg[15]_0 ),
        .I1(reset_old1_out1),
        .I2(count_2),
        .I3(reset_old6_out1[5]),
        .O(Add1_out1_carry_i_10_n_0));
  LUT4 #(
    .INIT(16'hD728)) 
    Add1_out1_carry_i_10__0
       (.I0(\reset_old4_out1_reg[15]_0 ),
        .I1(reset_old1_out1),
        .I2(count_2),
        .I3(position[5]),
        .O(S[5]));
  LUT4 #(
    .INIT(16'hD728)) 
    Add1_out1_carry_i_11
       (.I0(\reset_old4_out1_reg[15]_0 ),
        .I1(reset_old1_out1),
        .I2(count_2),
        .I3(reset_old6_out1[4]),
        .O(Add1_out1_carry_i_11_n_0));
  LUT4 #(
    .INIT(16'hD728)) 
    Add1_out1_carry_i_11__0
       (.I0(\reset_old4_out1_reg[15]_0 ),
        .I1(reset_old1_out1),
        .I2(count_2),
        .I3(position[4]),
        .O(S[4]));
  LUT4 #(
    .INIT(16'hD728)) 
    Add1_out1_carry_i_12
       (.I0(\reset_old4_out1_reg[15]_0 ),
        .I1(reset_old1_out1),
        .I2(count_2),
        .I3(reset_old6_out1[3]),
        .O(Add1_out1_carry_i_12_n_0));
  LUT4 #(
    .INIT(16'hD728)) 
    Add1_out1_carry_i_12__0
       (.I0(\reset_old4_out1_reg[15]_0 ),
        .I1(reset_old1_out1),
        .I2(count_2),
        .I3(position[3]),
        .O(S[3]));
  LUT4 #(
    .INIT(16'hD728)) 
    Add1_out1_carry_i_13
       (.I0(\reset_old4_out1_reg[15]_0 ),
        .I1(reset_old1_out1),
        .I2(count_2),
        .I3(reset_old6_out1[2]),
        .O(Add1_out1_carry_i_13_n_0));
  LUT4 #(
    .INIT(16'hD728)) 
    Add1_out1_carry_i_13__0
       (.I0(\reset_old4_out1_reg[15]_0 ),
        .I1(reset_old1_out1),
        .I2(count_2),
        .I3(position[2]),
        .O(S[2]));
  LUT4 #(
    .INIT(16'hD728)) 
    Add1_out1_carry_i_14
       (.I0(\reset_old4_out1_reg[15]_0 ),
        .I1(reset_old1_out1),
        .I2(count_2),
        .I3(reset_old6_out1[1]),
        .O(Add1_out1_carry_i_14_n_0));
  LUT4 #(
    .INIT(16'hD728)) 
    Add1_out1_carry_i_14__0
       (.I0(\reset_old4_out1_reg[15]_0 ),
        .I1(reset_old1_out1),
        .I2(count_2),
        .I3(position[1]),
        .O(S[1]));
  LUT4 #(
    .INIT(16'hD728)) 
    Add1_out1_carry_i_15
       (.I0(reset_old4_out1),
        .I1(reset_old1_out1),
        .I2(count_2),
        .I3(reset_old6_out1[0]),
        .O(Add1_out1_carry_i_15_n_0));
  LUT4 #(
    .INIT(16'hD728)) 
    Add1_out1_carry_i_15__0
       (.I0(reset_old4_out1),
        .I1(reset_old1_out1),
        .I2(count_2),
        .I3(position[0]),
        .O(S[0]));
  LUT4 #(
    .INIT(16'hD728)) 
    Add1_out1_carry_i_8
       (.I0(\reset_old4_out1_reg[15]_0 ),
        .I1(reset_old1_out1),
        .I2(count_2),
        .I3(reset_old6_out1[7]),
        .O(Add1_out1_carry_i_8_n_0));
  LUT4 #(
    .INIT(16'hD728)) 
    Add1_out1_carry_i_8__0
       (.I0(\reset_old4_out1_reg[15]_0 ),
        .I1(reset_old1_out1),
        .I2(count_2),
        .I3(position[7]),
        .O(S[7]));
  LUT4 #(
    .INIT(16'hD728)) 
    Add1_out1_carry_i_9
       (.I0(\reset_old4_out1_reg[15]_0 ),
        .I1(reset_old1_out1),
        .I2(count_2),
        .I3(reset_old6_out1[6]),
        .O(Add1_out1_carry_i_9_n_0));
  LUT4 #(
    .INIT(16'hD728)) 
    Add1_out1_carry_i_9__0
       (.I0(\reset_old4_out1_reg[15]_0 ),
        .I1(reset_old1_out1),
        .I2(count_2),
        .I3(position[6]),
        .O(S[6]));
  (* SOFT_HLUTNM = "soft_lutpair14" *) 
  LUT3 #(
    .INIT(8'h2F)) 
    \position_tmp[15]_i_2 
       (.I0(\reset_old5_out1_reg[0]_0 ),
        .I1(\reset_old5_out1_reg[3]_0 ),
        .I2(reset_old2_out1),
        .O(\reset_old5_out1_reg[0]_1 ));
  FDRE \reset_old1_out1_reg[0] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\reset_old1_out1_reg[15]_0 [0]),
        .Q(reset_old1_out1_1[0]),
        .R(RSTP));
  FDRE \reset_old1_out1_reg[10] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\reset_old1_out1_reg[15]_0 [10]),
        .Q(reset_old1_out1_1[10]),
        .R(RSTP));
  FDRE \reset_old1_out1_reg[11] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\reset_old1_out1_reg[15]_0 [11]),
        .Q(reset_old1_out1_1[11]),
        .R(RSTP));
  FDRE \reset_old1_out1_reg[12] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\reset_old1_out1_reg[15]_0 [12]),
        .Q(reset_old1_out1_1[12]),
        .R(RSTP));
  FDRE \reset_old1_out1_reg[13] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\reset_old1_out1_reg[15]_0 [13]),
        .Q(reset_old1_out1_1[13]),
        .R(RSTP));
  FDRE \reset_old1_out1_reg[14] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\reset_old1_out1_reg[15]_0 [14]),
        .Q(reset_old1_out1_1[14]),
        .R(RSTP));
  FDRE \reset_old1_out1_reg[15] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\reset_old1_out1_reg[15]_0 [15]),
        .Q(reset_old1_out1_1[15]),
        .R(RSTP));
  FDRE \reset_old1_out1_reg[1] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\reset_old1_out1_reg[15]_0 [1]),
        .Q(reset_old1_out1_1[1]),
        .R(RSTP));
  FDRE \reset_old1_out1_reg[2] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\reset_old1_out1_reg[15]_0 [2]),
        .Q(reset_old1_out1_1[2]),
        .R(RSTP));
  FDRE \reset_old1_out1_reg[3] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\reset_old1_out1_reg[15]_0 [3]),
        .Q(reset_old1_out1_1[3]),
        .R(RSTP));
  FDRE \reset_old1_out1_reg[4] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\reset_old1_out1_reg[15]_0 [4]),
        .Q(reset_old1_out1_1[4]),
        .R(RSTP));
  FDRE \reset_old1_out1_reg[5] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\reset_old1_out1_reg[15]_0 [5]),
        .Q(reset_old1_out1_1[5]),
        .R(RSTP));
  FDRE \reset_old1_out1_reg[6] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\reset_old1_out1_reg[15]_0 [6]),
        .Q(reset_old1_out1_1[6]),
        .R(RSTP));
  FDRE \reset_old1_out1_reg[7] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\reset_old1_out1_reg[15]_0 [7]),
        .Q(reset_old1_out1_1[7]),
        .R(RSTP));
  FDRE \reset_old1_out1_reg[8] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\reset_old1_out1_reg[15]_0 [8]),
        .Q(reset_old1_out1_1[8]),
        .R(RSTP));
  FDRE \reset_old1_out1_reg[9] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\reset_old1_out1_reg[15]_0 [9]),
        .Q(reset_old1_out1_1[9]),
        .R(RSTP));
  (* COMPARATOR_THRESHOLD = "14" *) 
  (* METHODOLOGY_DRC_VIOS = "{SYNTH-8 {cell *THIS*}}" *) 
  CARRY8 reset_old2_out10_carry
       (.CI(1'b1),
        .CI_TOP(1'b0),
        .CO({Relational_Operator1_relop1,reset_old2_out10_carry_n_1,reset_old2_out10_carry_n_2,reset_old2_out10_carry_n_3,reset_old2_out10_carry_n_4,reset_old2_out10_carry_n_5,reset_old2_out10_carry_n_6,reset_old2_out10_carry_n_7}),
        .DI({Reset_switch3_out1,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .O(NLW_reset_old2_out10_carry_O_UNCONNECTED[7:0]),
        .S({reset_old2_out10_carry_i_2__0_n_0,reset_old2_out10_carry_i_3__0_n_0,reset_old2_out10_carry_i_4__0_n_0,reset_old2_out10_carry_i_5__0_n_0,reset_old2_out10_carry_i_6__0_n_0,reset_old2_out10_carry_i_7__0_n_0,reset_old2_out10_carry_i_8__0_n_0,reset_old2_out10_carry_i_9__0_n_0}));
  (* SOFT_HLUTNM = "soft_lutpair14" *) 
  LUT5 #(
    .INIT(32'h06660606)) 
    reset_old2_out10_carry_i_10
       (.I0(I),
        .I1(reset_old_out1),
        .I2(reset_old2_out1),
        .I3(\reset_old5_out1_reg[3]_0 ),
        .I4(\reset_old5_out1_reg[0]_0 ),
        .O(I_0));
  (* SOFT_HLUTNM = "soft_lutpair15" *) 
  LUT5 #(
    .INIT(32'h06660606)) 
    reset_old2_out10_carry_i_10__0
       (.I0(I),
        .I1(reset_old_out1),
        .I2(reset_old2_out1_0),
        .I3(\reset_old5_out1_reg[3]_0 ),
        .I4(\reset_old5_out1_reg[0]_0 ),
        .O(reset_old2_out10_carry_i_10__0_n_0));
  LUT5 #(
    .INIT(32'h82FF8200)) 
    reset_old2_out10_carry_i_1__0
       (.I0(data0[15]),
        .I1(I),
        .I2(reset_old_out1),
        .I3(theta_el_tmp_reg_i_19_n_0),
        .I4(reset_old1_out1_1[15]),
        .O(Reset_switch3_out1));
  LUT6 #(
    .INIT(64'hAAABAAABAAABFFAB)) 
    reset_old2_out10_carry_i_2__0
       (.I0(reset_old2_out10_carry_i_10__0_n_0),
        .I1(reset_old1_out1_1[15]),
        .I2(reset_old1_out1_1[14]),
        .I3(theta_el_tmp_reg_i_19_n_0),
        .I4(data0[14]),
        .I5(data0[15]),
        .O(reset_old2_out10_carry_i_2__0_n_0));
  LUT6 #(
    .INIT(64'hAAABAAABAAABFFAB)) 
    reset_old2_out10_carry_i_3__0
       (.I0(reset_old2_out10_carry_i_10__0_n_0),
        .I1(reset_old1_out1_1[13]),
        .I2(reset_old1_out1_1[12]),
        .I3(theta_el_tmp_reg_i_19_n_0),
        .I4(data0[12]),
        .I5(data0[13]),
        .O(reset_old2_out10_carry_i_3__0_n_0));
  LUT6 #(
    .INIT(64'hAAABAAABAAABFFAB)) 
    reset_old2_out10_carry_i_4__0
       (.I0(reset_old2_out10_carry_i_10__0_n_0),
        .I1(reset_old1_out1_1[11]),
        .I2(reset_old1_out1_1[10]),
        .I3(theta_el_tmp_reg_i_19_n_0),
        .I4(data0[10]),
        .I5(data0[11]),
        .O(reset_old2_out10_carry_i_4__0_n_0));
  LUT6 #(
    .INIT(64'hAAABAAABAAABFFAB)) 
    reset_old2_out10_carry_i_5__0
       (.I0(reset_old2_out10_carry_i_10__0_n_0),
        .I1(reset_old1_out1_1[9]),
        .I2(reset_old1_out1_1[8]),
        .I3(theta_el_tmp_reg_i_19_n_0),
        .I4(data0[8]),
        .I5(data0[9]),
        .O(reset_old2_out10_carry_i_5__0_n_0));
  LUT6 #(
    .INIT(64'hAAABAAABAAABFFAB)) 
    reset_old2_out10_carry_i_6__0
       (.I0(reset_old2_out10_carry_i_10__0_n_0),
        .I1(reset_old1_out1_1[7]),
        .I2(reset_old1_out1_1[6]),
        .I3(theta_el_tmp_reg_i_19_n_0),
        .I4(data0[6]),
        .I5(data0[7]),
        .O(reset_old2_out10_carry_i_6__0_n_0));
  LUT6 #(
    .INIT(64'hAAABAAABAAABFFAB)) 
    reset_old2_out10_carry_i_7__0
       (.I0(reset_old2_out10_carry_i_10__0_n_0),
        .I1(reset_old1_out1_1[5]),
        .I2(reset_old1_out1_1[4]),
        .I3(theta_el_tmp_reg_i_19_n_0),
        .I4(data0[4]),
        .I5(data0[5]),
        .O(reset_old2_out10_carry_i_7__0_n_0));
  LUT6 #(
    .INIT(64'hAAABAAABAAABFFAB)) 
    reset_old2_out10_carry_i_8__0
       (.I0(reset_old2_out10_carry_i_10__0_n_0),
        .I1(reset_old1_out1_1[3]),
        .I2(reset_old1_out1_1[2]),
        .I3(theta_el_tmp_reg_i_19_n_0),
        .I4(data0[2]),
        .I5(data0[3]),
        .O(reset_old2_out10_carry_i_8__0_n_0));
  LUT6 #(
    .INIT(64'hAAABAAABAAABFFAB)) 
    reset_old2_out10_carry_i_9__0
       (.I0(reset_old2_out10_carry_i_10__0_n_0),
        .I1(reset_old1_out1_1[1]),
        .I2(reset_old1_out1_1[0]),
        .I3(theta_el_tmp_reg_i_19_n_0),
        .I4(data0[0]),
        .I5(data0[1]),
        .O(reset_old2_out10_carry_i_9__0_n_0));
  FDRE reset_old2_out1_reg
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Relational_Operator1_relop1),
        .Q(reset_old2_out1_0),
        .R(RSTP));
  (* COMPARATOR_THRESHOLD = "14" *) 
  (* METHODOLOGY_DRC_VIOS = "{SYNTH-8 {cell *THIS*}}" *) 
  CARRY8 reset_old3_out10_carry
       (.CI(1'b0),
        .CI_TOP(1'b0),
        .CO({reset_old3_out10_carry_n_0,reset_old3_out10_carry_n_1,reset_old3_out10_carry_n_2,reset_old3_out10_carry_n_3,reset_old3_out10_carry_n_4,reset_old3_out10_carry_n_5,reset_old3_out10_carry_n_6,reset_old3_out10_carry_n_7}),
        .DI({reset_old3_out10_carry_i_1__0_n_0,reset_old3_out10_carry_i_2__0_n_0,reset_old3_out10_carry_i_3__0_n_0,reset_old3_out10_carry_i_4__0_n_0,reset_old3_out10_carry_i_5__0_n_0,reset_old3_out10_carry_i_6__0_n_0,reset_old3_out10_carry_i_7__0_n_0,reset_old3_out10_carry_i_8__0_n_0}),
        .O(NLW_reset_old3_out10_carry_O_UNCONNECTED[7:0]),
        .S({reset_old3_out10_carry_i_9__0_n_0,reset_old3_out10_carry_i_10__0_n_0,reset_old3_out10_carry_i_11__0_n_0,reset_old3_out10_carry_i_12__0_n_0,reset_old3_out10_carry_i_13__0_n_0,reset_old3_out10_carry_i_14__0_n_0,reset_old3_out10_carry_i_15__0_n_0,reset_old3_out10_carry_i_16__0_n_0}));
  (* COMPARATOR_THRESHOLD = "14" *) 
  (* METHODOLOGY_DRC_VIOS = "{SYNTH-8 {cell *THIS*}}" *) 
  CARRY8 reset_old3_out10_carry__0
       (.CI(reset_old3_out10_carry_n_0),
        .CI_TOP(1'b0),
        .CO({NLW_reset_old3_out10_carry__0_CO_UNCONNECTED[7:1],Relational_Operator_relop1}),
        .DI({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .O(NLW_reset_old3_out10_carry__0_O_UNCONNECTED[7:0]),
        .S({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,reset_old3_out10_carry__0_i_1_n_0}));
  LUT6 #(
    .INIT(64'hFFFFFFFF3FF35555)) 
    reset_old3_out10_carry__0_i_1
       (.I0(reset_old1_out1_1[15]),
        .I1(data0[15]),
        .I2(I),
        .I3(reset_old_out1),
        .I4(theta_el_tmp_reg_i_19_n_0),
        .I5(reset_old3_out1),
        .O(reset_old3_out10_carry__0_i_1_n_0));
  LUT6 #(
    .INIT(64'hAAEAAAAEAABAFFAB)) 
    reset_old3_out10_carry_i_10__0
       (.I0(reset_old3_out10_carry_i_18__0_n_0),
        .I1(data0[13]),
        .I2(data0[12]),
        .I3(reset_old3_out10_carry_0),
        .I4(reset_old1_out1_1[12]),
        .I5(reset_old1_out1_1[13]),
        .O(reset_old3_out10_carry_i_10__0_n_0));
  LUT6 #(
    .INIT(64'hAAEAAAAEAABAFFAB)) 
    reset_old3_out10_carry_i_11__0
       (.I0(reset_old3_out10_carry_i_18__0_n_0),
        .I1(data0[11]),
        .I2(data0[10]),
        .I3(reset_old3_out10_carry_0),
        .I4(reset_old1_out1_1[10]),
        .I5(reset_old1_out1_1[11]),
        .O(reset_old3_out10_carry_i_11__0_n_0));
  LUT6 #(
    .INIT(64'hAAEAAAAEAABAFFAB)) 
    reset_old3_out10_carry_i_12__0
       (.I0(reset_old3_out10_carry_i_18__0_n_0),
        .I1(data0[9]),
        .I2(data0[8]),
        .I3(reset_old3_out10_carry_0),
        .I4(reset_old1_out1_1[8]),
        .I5(reset_old1_out1_1[9]),
        .O(reset_old3_out10_carry_i_12__0_n_0));
  LUT6 #(
    .INIT(64'hAAEAAAAEAABAFFAB)) 
    reset_old3_out10_carry_i_13__0
       (.I0(reset_old3_out10_carry_i_18__0_n_0),
        .I1(data0[7]),
        .I2(data0[6]),
        .I3(reset_old3_out10_carry_0),
        .I4(reset_old1_out1_1[6]),
        .I5(reset_old1_out1_1[7]),
        .O(reset_old3_out10_carry_i_13__0_n_0));
  LUT6 #(
    .INIT(64'hAAEAAAAEAABAFFAB)) 
    reset_old3_out10_carry_i_14__0
       (.I0(reset_old3_out10_carry_i_18__0_n_0),
        .I1(data0[5]),
        .I2(data0[4]),
        .I3(reset_old3_out10_carry_0),
        .I4(reset_old1_out1_1[4]),
        .I5(reset_old1_out1_1[5]),
        .O(reset_old3_out10_carry_i_14__0_n_0));
  LUT6 #(
    .INIT(64'hAAEAAAAEAABAFFAB)) 
    reset_old3_out10_carry_i_15__0
       (.I0(reset_old3_out10_carry_i_18__0_n_0),
        .I1(data0[3]),
        .I2(data0[2]),
        .I3(reset_old3_out10_carry_0),
        .I4(reset_old1_out1_1[2]),
        .I5(reset_old1_out1_1[3]),
        .O(reset_old3_out10_carry_i_15__0_n_0));
  LUT6 #(
    .INIT(64'hAAEAAAAEAABAFFAB)) 
    reset_old3_out10_carry_i_16__0
       (.I0(reset_old3_out10_carry_i_18__0_n_0),
        .I1(data0[1]),
        .I2(data0[0]),
        .I3(reset_old3_out10_carry_0),
        .I4(reset_old1_out1_1[0]),
        .I5(reset_old1_out1_1[1]),
        .O(reset_old3_out10_carry_i_16__0_n_0));
  LUT6 #(
    .INIT(64'h0075000000000075)) 
    reset_old3_out10_carry_i_17__0
       (.I0(reset_old2_out1_0),
        .I1(\reset_old5_out1_reg[3]_0 ),
        .I2(\reset_old5_out1_reg[0]_0 ),
        .I3(reset_old3_out1),
        .I4(reset_old_out1),
        .I5(I),
        .O(reset_old3_out10_carry_i_17__0_n_0));
  (* SOFT_HLUTNM = "soft_lutpair16" *) 
  LUT4 #(
    .INIT(16'h008A)) 
    reset_old3_out10_carry_i_18__0
       (.I0(reset_old2_out1_0),
        .I1(\reset_old5_out1_reg[3]_0 ),
        .I2(\reset_old5_out1_reg[0]_0 ),
        .I3(reset_old3_out1),
        .O(reset_old3_out10_carry_i_18__0_n_0));
  LUT5 #(
    .INIT(32'h4000F040)) 
    reset_old3_out10_carry_i_1__0
       (.I0(reset_old1_out1_1[14]),
        .I1(data0[14]),
        .I2(reset_old3_out10_carry_i_17__0_n_0),
        .I3(data0[15]),
        .I4(reset_old1_out1_1[15]),
        .O(reset_old3_out10_carry_i_1__0_n_0));
  LUT5 #(
    .INIT(32'h4000F040)) 
    reset_old3_out10_carry_i_2__0
       (.I0(reset_old1_out1_1[12]),
        .I1(data0[12]),
        .I2(reset_old3_out10_carry_i_17__0_n_0),
        .I3(data0[13]),
        .I4(reset_old1_out1_1[13]),
        .O(reset_old3_out10_carry_i_2__0_n_0));
  LUT5 #(
    .INIT(32'h4000F040)) 
    reset_old3_out10_carry_i_3__0
       (.I0(reset_old1_out1_1[10]),
        .I1(data0[10]),
        .I2(reset_old3_out10_carry_i_17__0_n_0),
        .I3(data0[11]),
        .I4(reset_old1_out1_1[11]),
        .O(reset_old3_out10_carry_i_3__0_n_0));
  LUT5 #(
    .INIT(32'h4000F040)) 
    reset_old3_out10_carry_i_4__0
       (.I0(reset_old1_out1_1[8]),
        .I1(data0[8]),
        .I2(reset_old3_out10_carry_i_17__0_n_0),
        .I3(data0[9]),
        .I4(reset_old1_out1_1[9]),
        .O(reset_old3_out10_carry_i_4__0_n_0));
  LUT5 #(
    .INIT(32'h4000F040)) 
    reset_old3_out10_carry_i_5__0
       (.I0(reset_old1_out1_1[6]),
        .I1(data0[6]),
        .I2(reset_old3_out10_carry_i_17__0_n_0),
        .I3(data0[7]),
        .I4(reset_old1_out1_1[7]),
        .O(reset_old3_out10_carry_i_5__0_n_0));
  LUT5 #(
    .INIT(32'h4000F040)) 
    reset_old3_out10_carry_i_6__0
       (.I0(reset_old1_out1_1[4]),
        .I1(data0[4]),
        .I2(reset_old3_out10_carry_i_17__0_n_0),
        .I3(data0[5]),
        .I4(reset_old1_out1_1[5]),
        .O(reset_old3_out10_carry_i_6__0_n_0));
  LUT5 #(
    .INIT(32'h4000F040)) 
    reset_old3_out10_carry_i_7__0
       (.I0(reset_old1_out1_1[2]),
        .I1(data0[2]),
        .I2(reset_old3_out10_carry_i_17__0_n_0),
        .I3(data0[3]),
        .I4(reset_old1_out1_1[3]),
        .O(reset_old3_out10_carry_i_7__0_n_0));
  LUT5 #(
    .INIT(32'h4000F040)) 
    reset_old3_out10_carry_i_8__0
       (.I0(reset_old1_out1_1[0]),
        .I1(data0[0]),
        .I2(reset_old3_out10_carry_i_17__0_n_0),
        .I3(data0[1]),
        .I4(reset_old1_out1_1[1]),
        .O(reset_old3_out10_carry_i_8__0_n_0));
  LUT6 #(
    .INIT(64'hAAEAAAAEAABAFFAB)) 
    reset_old3_out10_carry_i_9__0
       (.I0(reset_old3_out10_carry_i_18__0_n_0),
        .I1(data0[15]),
        .I2(data0[14]),
        .I3(reset_old3_out10_carry_0),
        .I4(reset_old1_out1_1[14]),
        .I5(reset_old1_out1_1[15]),
        .O(reset_old3_out10_carry_i_9__0_n_0));
  FDRE reset_old3_out1_reg
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Relational_Operator_relop1),
        .Q(reset_old3_out1),
        .R(RSTP));
  (* SOFT_HLUTNM = "soft_lutpair16" *) 
  LUT3 #(
    .INIT(8'h0D)) 
    \reset_old4_out1[15]_i_1 
       (.I0(\reset_old5_out1_reg[0]_0 ),
        .I1(\reset_old5_out1_reg[3]_0 ),
        .I2(RSTP),
        .O(p_1_in));
  FDRE \reset_old4_out1_reg[0] 
       (.C(IPCORE_CLK),
        .CE(\reset_old4_out1_reg[0]_0 ),
        .D(\reset_old4_out1_reg[0]_1 ),
        .Q(reset_old4_out1),
        .R(1'b0));
  FDRE \reset_old4_out1_reg[15] 
       (.C(IPCORE_CLK),
        .CE(\reset_old4_out1_reg[0]_0 ),
        .D(p_1_in),
        .Q(\reset_old4_out1_reg[15]_0 ),
        .R(1'b0));
  FDRE \reset_old5_out1_reg[0] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Q[0]),
        .Q(\reset_old5_out1_reg[0]_0 ),
        .R(RSTP));
  FDRE \reset_old5_out1_reg[3] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Q[1]),
        .Q(\reset_old5_out1_reg[3]_0 ),
        .R(RSTP));
  FDRE \reset_old6_out1_reg[0] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(D[0]),
        .Q(reset_old6_out1[0]),
        .R(RSTP));
  FDRE \reset_old6_out1_reg[10] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(D[10]),
        .Q(reset_old6_out1[10]),
        .R(RSTP));
  FDRE \reset_old6_out1_reg[11] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(D[11]),
        .Q(reset_old6_out1[11]),
        .R(RSTP));
  FDRE \reset_old6_out1_reg[12] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(D[12]),
        .Q(reset_old6_out1[12]),
        .R(RSTP));
  FDRE \reset_old6_out1_reg[13] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(D[13]),
        .Q(reset_old6_out1[13]),
        .R(RSTP));
  FDRE \reset_old6_out1_reg[14] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(D[14]),
        .Q(reset_old6_out1[14]),
        .R(RSTP));
  FDRE \reset_old6_out1_reg[15] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(D[15]),
        .Q(reset_old6_out1[15]),
        .R(RSTP));
  FDRE \reset_old6_out1_reg[1] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(D[1]),
        .Q(reset_old6_out1[1]),
        .R(RSTP));
  FDRE \reset_old6_out1_reg[2] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(D[2]),
        .Q(reset_old6_out1[2]),
        .R(RSTP));
  FDRE \reset_old6_out1_reg[3] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(D[3]),
        .Q(reset_old6_out1[3]),
        .R(RSTP));
  FDRE \reset_old6_out1_reg[4] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(D[4]),
        .Q(reset_old6_out1[4]),
        .R(RSTP));
  FDRE \reset_old6_out1_reg[5] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(D[5]),
        .Q(reset_old6_out1[5]),
        .R(RSTP));
  FDRE \reset_old6_out1_reg[6] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(D[6]),
        .Q(reset_old6_out1[6]),
        .R(RSTP));
  FDRE \reset_old6_out1_reg[7] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(D[7]),
        .Q(reset_old6_out1[7]),
        .R(RSTP));
  FDRE \reset_old6_out1_reg[8] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(D[8]),
        .Q(reset_old6_out1[8]),
        .R(RSTP));
  FDRE \reset_old6_out1_reg[9] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(D[9]),
        .Q(reset_old6_out1[9]),
        .R(RSTP));
  LUT6 #(
    .INIT(64'h000000008282FF00)) 
    theta_el_tmp_reg_i_10
       (.I0(data0[8]),
        .I1(reset_old_out1),
        .I2(I),
        .I3(reset_old1_out1_1[8]),
        .I4(theta_el_tmp_reg_i_19_n_0),
        .I5(reset_old3_out1),
        .O(D[8]));
  LUT6 #(
    .INIT(64'h000000008282FF00)) 
    theta_el_tmp_reg_i_11
       (.I0(data0[7]),
        .I1(reset_old_out1),
        .I2(I),
        .I3(reset_old1_out1_1[7]),
        .I4(theta_el_tmp_reg_i_19_n_0),
        .I5(reset_old3_out1),
        .O(D[7]));
  LUT6 #(
    .INIT(64'h000000008282FF00)) 
    theta_el_tmp_reg_i_12
       (.I0(data0[6]),
        .I1(reset_old_out1),
        .I2(I),
        .I3(reset_old1_out1_1[6]),
        .I4(theta_el_tmp_reg_i_19_n_0),
        .I5(reset_old3_out1),
        .O(D[6]));
  LUT6 #(
    .INIT(64'h000000008282FF00)) 
    theta_el_tmp_reg_i_13
       (.I0(data0[5]),
        .I1(reset_old_out1),
        .I2(I),
        .I3(reset_old1_out1_1[5]),
        .I4(theta_el_tmp_reg_i_19_n_0),
        .I5(reset_old3_out1),
        .O(D[5]));
  LUT6 #(
    .INIT(64'h000000008282FF00)) 
    theta_el_tmp_reg_i_14
       (.I0(data0[4]),
        .I1(reset_old_out1),
        .I2(I),
        .I3(reset_old1_out1_1[4]),
        .I4(theta_el_tmp_reg_i_19_n_0),
        .I5(reset_old3_out1),
        .O(D[4]));
  LUT6 #(
    .INIT(64'h000000008282FF00)) 
    theta_el_tmp_reg_i_15
       (.I0(data0[3]),
        .I1(reset_old_out1),
        .I2(I),
        .I3(reset_old1_out1_1[3]),
        .I4(theta_el_tmp_reg_i_19_n_0),
        .I5(reset_old3_out1),
        .O(D[3]));
  LUT6 #(
    .INIT(64'h000000008282FF00)) 
    theta_el_tmp_reg_i_16
       (.I0(data0[2]),
        .I1(reset_old_out1),
        .I2(I),
        .I3(reset_old1_out1_1[2]),
        .I4(theta_el_tmp_reg_i_19_n_0),
        .I5(reset_old3_out1),
        .O(D[2]));
  LUT6 #(
    .INIT(64'h000000008282FF00)) 
    theta_el_tmp_reg_i_17
       (.I0(data0[1]),
        .I1(reset_old_out1),
        .I2(I),
        .I3(reset_old1_out1_1[1]),
        .I4(theta_el_tmp_reg_i_19_n_0),
        .I5(reset_old3_out1),
        .O(D[1]));
  LUT6 #(
    .INIT(64'h000000008282FF00)) 
    theta_el_tmp_reg_i_18
       (.I0(data0[0]),
        .I1(reset_old_out1),
        .I2(I),
        .I3(reset_old1_out1_1[0]),
        .I4(theta_el_tmp_reg_i_19_n_0),
        .I5(reset_old3_out1),
        .O(D[0]));
  (* SOFT_HLUTNM = "soft_lutpair15" *) 
  LUT3 #(
    .INIT(8'h2F)) 
    theta_el_tmp_reg_i_19
       (.I0(\reset_old5_out1_reg[0]_0 ),
        .I1(\reset_old5_out1_reg[3]_0 ),
        .I2(reset_old2_out1_0),
        .O(theta_el_tmp_reg_i_19_n_0));
  LUT6 #(
    .INIT(64'h000000008282FF00)) 
    theta_el_tmp_reg_i_3
       (.I0(data0[15]),
        .I1(reset_old_out1),
        .I2(I),
        .I3(reset_old1_out1_1[15]),
        .I4(theta_el_tmp_reg_i_19_n_0),
        .I5(reset_old3_out1),
        .O(D[15]));
  LUT6 #(
    .INIT(64'h000000008282FF00)) 
    theta_el_tmp_reg_i_4
       (.I0(data0[14]),
        .I1(reset_old_out1),
        .I2(I),
        .I3(reset_old1_out1_1[14]),
        .I4(theta_el_tmp_reg_i_19_n_0),
        .I5(reset_old3_out1),
        .O(D[14]));
  LUT6 #(
    .INIT(64'h000000008282FF00)) 
    theta_el_tmp_reg_i_5
       (.I0(data0[13]),
        .I1(reset_old_out1),
        .I2(I),
        .I3(reset_old1_out1_1[13]),
        .I4(theta_el_tmp_reg_i_19_n_0),
        .I5(reset_old3_out1),
        .O(D[13]));
  LUT6 #(
    .INIT(64'h000000008282FF00)) 
    theta_el_tmp_reg_i_6
       (.I0(data0[12]),
        .I1(reset_old_out1),
        .I2(I),
        .I3(reset_old1_out1_1[12]),
        .I4(theta_el_tmp_reg_i_19_n_0),
        .I5(reset_old3_out1),
        .O(D[12]));
  LUT6 #(
    .INIT(64'h000000008282FF00)) 
    theta_el_tmp_reg_i_7
       (.I0(data0[11]),
        .I1(reset_old_out1),
        .I2(I),
        .I3(reset_old1_out1_1[11]),
        .I4(theta_el_tmp_reg_i_19_n_0),
        .I5(reset_old3_out1),
        .O(D[11]));
  LUT6 #(
    .INIT(64'h000000008282FF00)) 
    theta_el_tmp_reg_i_8
       (.I0(data0[10]),
        .I1(reset_old_out1),
        .I2(I),
        .I3(reset_old1_out1_1[10]),
        .I4(theta_el_tmp_reg_i_19_n_0),
        .I5(reset_old3_out1),
        .O(D[10]));
  LUT6 #(
    .INIT(64'h000000008282FF00)) 
    theta_el_tmp_reg_i_9
       (.I0(data0[9]),
        .I1(reset_old_out1),
        .I2(I),
        .I3(reset_old1_out1_1[9]),
        .I4(theta_el_tmp_reg_i_19_n_0),
        .I5(reset_old3_out1),
        .O(D[9]));
endmodule

(* ORIG_REF_NAME = "IncreEncoder_V24_ip_src_HDL_Reciprocal" *) 
module zusys_IncreEncoder_V24_ip_0_0_IncreEncoder_V24_ip_src_HDL_Reciprocal
   (A,
    RSTP,
    CEP,
    IPCORE_CLK,
    Q,
    write_axi_enable);
  output [23:0]A;
  input RSTP;
  input CEP;
  input IPCORE_CLK;
  input [23:0]Q;
  input write_axi_enable;

  wire [23:0]A;
  wire CEP;
  wire IPCORE_CLK;
  wire [23:0]Q;
  wire RSTP;
  wire [31:2]anorm;
  wire [30:2]anorm_p;
  wire \anorm_p[10]_i_2_n_0 ;
  wire \anorm_p[10]_i_4_n_0 ;
  wire \anorm_p[11]_i_2_n_0 ;
  wire \anorm_p[11]_i_3_n_0 ;
  wire \anorm_p[11]_i_4_n_0 ;
  wire \anorm_p[11]_i_5_n_0 ;
  wire \anorm_p[11]_i_6_n_0 ;
  wire \anorm_p[11]_i_7_n_0 ;
  wire \anorm_p[11]_i_8_n_0 ;
  wire \anorm_p[12]_i_2_n_0 ;
  wire \anorm_p[12]_i_3_n_0 ;
  wire \anorm_p[12]_i_4_n_0 ;
  wire \anorm_p[12]_i_5_n_0 ;
  wire \anorm_p[12]_i_6_n_0 ;
  wire \anorm_p[12]_i_7_n_0 ;
  wire \anorm_p[12]_i_8_n_0 ;
  wire \anorm_p[12]_i_9_n_0 ;
  wire \anorm_p[13]_i_2_n_0 ;
  wire \anorm_p[14]_i_2_n_0 ;
  wire \anorm_p[15]_i_2_n_0 ;
  wire \anorm_p[15]_i_3_n_0 ;
  wire \anorm_p[16]_i_2_n_0 ;
  wire \anorm_p[16]_i_3_n_0 ;
  wire \anorm_p[17]_i_2_n_0 ;
  wire \anorm_p[17]_i_3_n_0 ;
  wire \anorm_p[18]_i_2_n_0 ;
  wire \anorm_p[18]_i_3_n_0 ;
  wire \anorm_p[19]_i_2_n_0 ;
  wire \anorm_p[19]_i_3_n_0 ;
  wire \anorm_p[20]_i_2_n_0 ;
  wire \anorm_p[20]_i_3_n_0 ;
  wire \anorm_p[21]_i_2_n_0 ;
  wire \anorm_p[21]_i_3_n_0 ;
  wire \anorm_p[22]_i_2_n_0 ;
  wire \anorm_p[22]_i_3_n_0 ;
  wire \anorm_p[23]_i_2_n_0 ;
  wire \anorm_p[23]_i_3_n_0 ;
  wire \anorm_p[23]_i_4_n_0 ;
  wire \anorm_p[24]_i_2_n_0 ;
  wire \anorm_p[24]_i_3_n_0 ;
  wire \anorm_p[24]_i_4_n_0 ;
  wire \anorm_p[25]_i_2_n_0 ;
  wire \anorm_p[25]_i_3_n_0 ;
  wire \anorm_p[25]_i_4_n_0 ;
  wire \anorm_p[26]_i_2_n_0 ;
  wire \anorm_p[26]_i_3_n_0 ;
  wire \anorm_p[26]_i_4_n_0 ;
  wire \anorm_p[27]_i_2_n_0 ;
  wire \anorm_p[27]_i_3_n_0 ;
  wire \anorm_p[27]_i_4_n_0 ;
  wire \anorm_p[28]_i_2_n_0 ;
  wire \anorm_p[28]_i_3_n_0 ;
  wire \anorm_p[28]_i_4_n_0 ;
  wire \anorm_p[29]_i_2_n_0 ;
  wire \anorm_p[29]_i_3_n_0 ;
  wire \anorm_p[29]_i_4_n_0 ;
  wire \anorm_p[30]_i_2_n_0 ;
  wire \anorm_p[30]_i_3_n_0 ;
  wire \anorm_p[31]_i_10_n_0 ;
  wire \anorm_p[31]_i_11_n_0 ;
  wire \anorm_p[31]_i_12_n_0 ;
  wire \anorm_p[31]_i_13_n_0 ;
  wire \anorm_p[31]_i_14_n_0 ;
  wire \anorm_p[31]_i_15_n_0 ;
  wire \anorm_p[31]_i_16_n_0 ;
  wire \anorm_p[31]_i_17_n_0 ;
  wire \anorm_p[31]_i_18_n_0 ;
  wire \anorm_p[31]_i_19_n_0 ;
  wire \anorm_p[31]_i_20_n_0 ;
  wire \anorm_p[31]_i_21_n_0 ;
  wire \anorm_p[31]_i_22_n_0 ;
  wire \anorm_p[31]_i_23_n_0 ;
  wire \anorm_p[31]_i_3_n_0 ;
  wire \anorm_p[31]_i_4_n_0 ;
  wire \anorm_p[31]_i_5_n_0 ;
  wire \anorm_p[31]_i_6_n_0 ;
  wire \anorm_p[31]_i_7_n_0 ;
  wire \anorm_p[31]_i_8_n_0 ;
  wire \anorm_p[31]_i_9_n_0 ;
  wire \anorm_p[3]_i_2_n_0 ;
  wire \anorm_p[4]_i_2_n_0 ;
  wire \anorm_p[4]_i_3_n_0 ;
  wire \anorm_p[5]_i_2_n_0 ;
  wire \anorm_p[6]_i_2_n_0 ;
  wire \anorm_p[7]_i_2_n_0 ;
  wire \anorm_p[8]_i_2_n_0 ;
  wire \anorm_p[9]_i_2_n_0 ;
  wire \anorm_p_reg[10]_i_3_n_0 ;
  wire \anorm_p_reg[10]_i_3_n_1 ;
  wire \anorm_p_reg[10]_i_3_n_2 ;
  wire \anorm_p_reg[10]_i_3_n_3 ;
  wire \anorm_p_reg[10]_i_3_n_4 ;
  wire \anorm_p_reg[10]_i_3_n_5 ;
  wire \anorm_p_reg[10]_i_3_n_6 ;
  wire \anorm_p_reg[10]_i_3_n_7 ;
  wire [31:2]aout_tmp;
  wire \changesign_reg_reg_reg[1]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_n_0 ;
  wire \changesign_reg_reg_reg[2]_U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_1_n_0 ;
  wire changesign_reg_reg_reg_gate_n_0;
  wire \changesign_reg_reg_reg_n_0_[3] ;
  wire [31:0]delayout;
  wire \ds_reg_reg_reg[1][0]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_2_n_0 ;
  wire \ds_reg_reg_reg[1][0]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_3_n_0 ;
  wire \ds_reg_reg_reg[1][0]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_4_n_0 ;
  wire \ds_reg_reg_reg[1][0]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_5_n_0 ;
  wire \ds_reg_reg_reg[1][0]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_6_n_0 ;
  wire \ds_reg_reg_reg[1][0]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_7_n_0 ;
  wire \ds_reg_reg_reg[1][0]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_8_n_0 ;
  wire \ds_reg_reg_reg[1][0]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_9_n_0 ;
  wire \ds_reg_reg_reg[1][0]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_n_0 ;
  wire \ds_reg_reg_reg[1][1]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_10_n_0 ;
  wire \ds_reg_reg_reg[1][1]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_2_n_0 ;
  wire \ds_reg_reg_reg[1][1]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_3_n_0 ;
  wire \ds_reg_reg_reg[1][1]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_4_n_0 ;
  wire \ds_reg_reg_reg[1][1]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_5_n_0 ;
  wire \ds_reg_reg_reg[1][1]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_6_n_0 ;
  wire \ds_reg_reg_reg[1][1]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_7_n_0 ;
  wire \ds_reg_reg_reg[1][1]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_8_n_0 ;
  wire \ds_reg_reg_reg[1][1]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_9_n_0 ;
  wire \ds_reg_reg_reg[1][1]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_n_0 ;
  wire \ds_reg_reg_reg[1][2]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_3_n_0 ;
  wire \ds_reg_reg_reg[1][2]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_4_n_0 ;
  wire \ds_reg_reg_reg[1][2]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_5_n_0 ;
  wire \ds_reg_reg_reg[1][2]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_6_n_0 ;
  wire \ds_reg_reg_reg[1][2]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_7_n_0 ;
  wire \ds_reg_reg_reg[1][2]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_n_0 ;
  wire \ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_10_n_0 ;
  wire \ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_11_n_0 ;
  wire \ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_12_n_0 ;
  wire \ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_13_n_0 ;
  wire \ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_14_n_0 ;
  wire \ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_15_n_0 ;
  wire \ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_15_n_1 ;
  wire \ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_15_n_2 ;
  wire \ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_15_n_3 ;
  wire \ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_15_n_4 ;
  wire \ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_15_n_5 ;
  wire \ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_15_n_6 ;
  wire \ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_15_n_7 ;
  wire \ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_16_n_0 ;
  wire \ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_17_n_0 ;
  wire \ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_18_n_0 ;
  wire \ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_1_n_0 ;
  wire \ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_2_n_0 ;
  wire \ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_3_n_0 ;
  wire \ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_4_n_2 ;
  wire \ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_4_n_3 ;
  wire \ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_4_n_4 ;
  wire \ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_4_n_5 ;
  wire \ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_4_n_6 ;
  wire \ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_4_n_7 ;
  wire \ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_5_n_0 ;
  wire \ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_6_n_0 ;
  wire \ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_6_n_1 ;
  wire \ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_6_n_2 ;
  wire \ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_6_n_3 ;
  wire \ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_6_n_4 ;
  wire \ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_6_n_5 ;
  wire \ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_6_n_6 ;
  wire \ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_6_n_7 ;
  wire \ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_7_n_0 ;
  wire \ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_9_n_0 ;
  wire \ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_n_0 ;
  wire \ds_reg_reg_reg[2][0]_U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_1_n_0 ;
  wire \ds_reg_reg_reg[2][1]_U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_1_n_0 ;
  wire \ds_reg_reg_reg[2][2]_U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_1_n_0 ;
  wire \ds_reg_reg_reg[2][3]_U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_1_n_0 ;
  wire [3:0]\ds_reg_reg_reg[3]_0 ;
  wire ds_reg_reg_reg_gate__0_n_0;
  wire ds_reg_reg_reg_gate__1_n_0;
  wire ds_reg_reg_reg_gate__2_n_0;
  wire ds_reg_reg_reg_gate_n_0;
  wire [0:1]inzero_reg_reg;
  wire \inzero_reg_reg_reg_n_0_[2] ;
  wire mstwobit;
  wire [31:0]muxout;
  wire \onemoreshift_reg_reg_reg[1]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_n_0 ;
  wire \onemoreshift_reg_reg_reg[2]_U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_1_n_0 ;
  wire onemoreshift_reg_reg_reg_gate_n_0;
  wire \onemoreshift_reg_reg_reg_n_0_[3] ;
  wire onemoreshift_reg_reg_reg_r_0_n_0;
  wire onemoreshift_reg_reg_reg_r_1_n_0;
  wire onemoreshift_reg_reg_reg_r_n_0;
  wire [2:0]out1;
  wire out1142_out;
  wire p_0_in;
  wire [30:0]p_0_in__0;
  wire [2:2]p_1_out;
  wire [3:3]p_2_out;
  wire sel;
  wire sel_i_1_n_0;
  wire subtractor_sub_temp_carry__0_i_1__0_n_0;
  wire subtractor_sub_temp_carry__0_i_1__1_n_0;
  wire subtractor_sub_temp_carry__0_i_1_n_0;
  wire subtractor_sub_temp_carry__0_i_2__0_n_0;
  wire subtractor_sub_temp_carry__0_i_2__1_n_0;
  wire subtractor_sub_temp_carry__0_i_2_n_0;
  wire subtractor_sub_temp_carry__0_i_3__0_n_0;
  wire subtractor_sub_temp_carry__0_i_3__1_n_0;
  wire subtractor_sub_temp_carry__0_i_3_n_0;
  wire subtractor_sub_temp_carry__0_i_4__0_n_0;
  wire subtractor_sub_temp_carry__0_i_4__1_n_0;
  wire subtractor_sub_temp_carry__0_i_4_n_0;
  wire subtractor_sub_temp_carry__0_i_5__0_n_0;
  wire subtractor_sub_temp_carry__0_i_5__1_n_0;
  wire subtractor_sub_temp_carry__0_i_5_n_0;
  wire subtractor_sub_temp_carry__0_i_6__0_n_0;
  wire subtractor_sub_temp_carry__0_i_6__1_n_0;
  wire subtractor_sub_temp_carry__0_i_6_n_0;
  wire subtractor_sub_temp_carry__0_i_7__0_n_0;
  wire subtractor_sub_temp_carry__0_i_7__1_n_0;
  wire subtractor_sub_temp_carry__0_i_7_n_0;
  wire subtractor_sub_temp_carry__0_i_8__0_n_0;
  wire subtractor_sub_temp_carry__0_i_8__1_n_0;
  wire subtractor_sub_temp_carry__0_i_8_n_0;
  wire subtractor_sub_temp_carry__1_i_1__0_n_0;
  wire subtractor_sub_temp_carry__1_i_1__1_n_0;
  wire subtractor_sub_temp_carry__1_i_1_n_0;
  wire subtractor_sub_temp_carry__1_i_2__0_n_0;
  wire subtractor_sub_temp_carry__1_i_2__1_n_0;
  wire subtractor_sub_temp_carry__1_i_2_n_0;
  wire subtractor_sub_temp_carry__1_i_3__0_n_0;
  wire subtractor_sub_temp_carry__1_i_3__1_n_0;
  wire subtractor_sub_temp_carry__1_i_3_n_0;
  wire subtractor_sub_temp_carry__1_i_4__0_n_0;
  wire subtractor_sub_temp_carry__1_i_4__1_n_0;
  wire subtractor_sub_temp_carry__1_i_4_n_0;
  wire subtractor_sub_temp_carry__1_i_5__0_n_0;
  wire subtractor_sub_temp_carry__1_i_5__1_n_0;
  wire subtractor_sub_temp_carry__1_i_5_n_0;
  wire subtractor_sub_temp_carry__1_i_6__0_n_0;
  wire subtractor_sub_temp_carry__1_i_6__1_n_0;
  wire subtractor_sub_temp_carry__1_i_6_n_0;
  wire subtractor_sub_temp_carry__1_i_7__0_n_0;
  wire subtractor_sub_temp_carry__1_i_7__1_n_0;
  wire subtractor_sub_temp_carry__1_i_7_n_0;
  wire subtractor_sub_temp_carry__1_i_8__0_n_0;
  wire subtractor_sub_temp_carry__1_i_8__1_n_0;
  wire subtractor_sub_temp_carry__1_i_8_n_0;
  wire subtractor_sub_temp_carry__2_i_1__0_n_0;
  wire subtractor_sub_temp_carry__2_i_1__1_n_0;
  wire subtractor_sub_temp_carry__2_i_1_n_0;
  wire subtractor_sub_temp_carry__2_i_2__0_n_0;
  wire subtractor_sub_temp_carry__2_i_2__1_n_0;
  wire subtractor_sub_temp_carry__2_i_2_n_0;
  wire subtractor_sub_temp_carry__2_i_3__0_n_0;
  wire subtractor_sub_temp_carry__2_i_3__1_n_0;
  wire subtractor_sub_temp_carry__2_i_3_n_0;
  wire subtractor_sub_temp_carry__2_i_4__0_n_0;
  wire subtractor_sub_temp_carry__2_i_4__1_n_0;
  wire subtractor_sub_temp_carry__2_i_4_n_0;
  wire subtractor_sub_temp_carry__2_i_5__0_n_0;
  wire subtractor_sub_temp_carry__2_i_5__1_n_0;
  wire subtractor_sub_temp_carry__2_i_5_n_0;
  wire subtractor_sub_temp_carry__2_i_6__0_n_0;
  wire subtractor_sub_temp_carry__2_i_6__1_n_0;
  wire subtractor_sub_temp_carry__2_i_6_n_0;
  wire subtractor_sub_temp_carry__2_i_7__0_n_0;
  wire subtractor_sub_temp_carry__2_i_7__1_n_0;
  wire subtractor_sub_temp_carry__2_i_7_n_0;
  wire subtractor_sub_temp_carry_i_1__0_n_0;
  wire subtractor_sub_temp_carry_i_1__1_n_0;
  wire subtractor_sub_temp_carry_i_1_n_0;
  wire subtractor_sub_temp_carry_i_2__0_n_0;
  wire subtractor_sub_temp_carry_i_2__1_n_0;
  wire subtractor_sub_temp_carry_i_2_n_0;
  wire subtractor_sub_temp_carry_i_3__0_n_0;
  wire subtractor_sub_temp_carry_i_3__1_n_0;
  wire subtractor_sub_temp_carry_i_3_n_0;
  wire subtractor_sub_temp_carry_i_4__0_n_0;
  wire subtractor_sub_temp_carry_i_4__1_n_0;
  wire subtractor_sub_temp_carry_i_4_n_0;
  wire subtractor_sub_temp_carry_i_5__0_n_0;
  wire subtractor_sub_temp_carry_i_5__1_n_0;
  wire subtractor_sub_temp_carry_i_5_n_0;
  wire subtractor_sub_temp_carry_i_6__0_n_0;
  wire subtractor_sub_temp_carry_i_6__1_n_0;
  wire subtractor_sub_temp_carry_i_6_n_0;
  wire subtractor_sub_temp_carry_i_7__0_n_0;
  wire subtractor_sub_temp_carry_i_7__1_n_0;
  wire subtractor_sub_temp_carry_i_7_n_0;
  wire subtractor_sub_temp_carry_i_8__0_n_0;
  wire subtractor_sub_temp_carry_i_8__1_n_0;
  wire subtractor_sub_temp_carry_i_8_n_0;
  wire subtractor_sub_temp_carry_i_9__0_n_0;
  wire subtractor_sub_temp_carry_i_9__1_n_0;
  wire subtractor_sub_temp_carry_i_9_n_0;
  wire u_core_stage2_inst_n_0;
  wire u_core_stage2_inst_n_1;
  wire u_core_stage2_inst_n_10;
  wire u_core_stage2_inst_n_11;
  wire u_core_stage2_inst_n_12;
  wire u_core_stage2_inst_n_13;
  wire u_core_stage2_inst_n_14;
  wire u_core_stage2_inst_n_15;
  wire u_core_stage2_inst_n_16;
  wire u_core_stage2_inst_n_17;
  wire u_core_stage2_inst_n_18;
  wire u_core_stage2_inst_n_19;
  wire u_core_stage2_inst_n_2;
  wire u_core_stage2_inst_n_20;
  wire u_core_stage2_inst_n_21;
  wire u_core_stage2_inst_n_22;
  wire u_core_stage2_inst_n_23;
  wire u_core_stage2_inst_n_24;
  wire u_core_stage2_inst_n_25;
  wire u_core_stage2_inst_n_26;
  wire u_core_stage2_inst_n_27;
  wire u_core_stage2_inst_n_28;
  wire u_core_stage2_inst_n_29;
  wire u_core_stage2_inst_n_3;
  wire u_core_stage2_inst_n_30;
  wire u_core_stage2_inst_n_31;
  wire u_core_stage2_inst_n_32;
  wire u_core_stage2_inst_n_33;
  wire u_core_stage2_inst_n_34;
  wire u_core_stage2_inst_n_35;
  wire u_core_stage2_inst_n_36;
  wire u_core_stage2_inst_n_37;
  wire u_core_stage2_inst_n_38;
  wire u_core_stage2_inst_n_39;
  wire u_core_stage2_inst_n_4;
  wire u_core_stage2_inst_n_40;
  wire u_core_stage2_inst_n_41;
  wire u_core_stage2_inst_n_42;
  wire u_core_stage2_inst_n_43;
  wire u_core_stage2_inst_n_44;
  wire u_core_stage2_inst_n_45;
  wire u_core_stage2_inst_n_46;
  wire u_core_stage2_inst_n_47;
  wire u_core_stage2_inst_n_48;
  wire u_core_stage2_inst_n_49;
  wire u_core_stage2_inst_n_5;
  wire u_core_stage2_inst_n_50;
  wire u_core_stage2_inst_n_51;
  wire u_core_stage2_inst_n_52;
  wire u_core_stage2_inst_n_53;
  wire u_core_stage2_inst_n_54;
  wire u_core_stage2_inst_n_55;
  wire u_core_stage2_inst_n_56;
  wire u_core_stage2_inst_n_57;
  wire u_core_stage2_inst_n_58;
  wire u_core_stage2_inst_n_59;
  wire u_core_stage2_inst_n_6;
  wire u_core_stage2_inst_n_60;
  wire u_core_stage2_inst_n_61;
  wire u_core_stage2_inst_n_62;
  wire u_core_stage2_inst_n_63;
  wire u_core_stage2_inst_n_64;
  wire u_core_stage2_inst_n_65;
  wire u_core_stage2_inst_n_66;
  wire u_core_stage2_inst_n_67;
  wire u_core_stage2_inst_n_68;
  wire u_core_stage2_inst_n_69;
  wire u_core_stage2_inst_n_7;
  wire u_core_stage2_inst_n_70;
  wire u_core_stage2_inst_n_71;
  wire u_core_stage2_inst_n_72;
  wire u_core_stage2_inst_n_73;
  wire u_core_stage2_inst_n_74;
  wire u_core_stage2_inst_n_75;
  wire u_core_stage2_inst_n_76;
  wire u_core_stage2_inst_n_77;
  wire u_core_stage2_inst_n_78;
  wire u_core_stage2_inst_n_79;
  wire u_core_stage2_inst_n_8;
  wire u_core_stage2_inst_n_80;
  wire u_core_stage2_inst_n_81;
  wire u_core_stage2_inst_n_82;
  wire u_core_stage2_inst_n_83;
  wire u_core_stage2_inst_n_84;
  wire u_core_stage2_inst_n_85;
  wire u_core_stage2_inst_n_86;
  wire u_core_stage2_inst_n_87;
  wire u_core_stage2_inst_n_88;
  wire u_core_stage2_inst_n_89;
  wire u_core_stage2_inst_n_9;
  wire u_core_stage2_inst_n_90;
  wire u_core_stage2_inst_n_91;
  wire u_core_stage2_inst_n_92;
  wire u_core_stage2_inst_n_93;
  wire u_core_stage3_inst_n_0;
  wire u_core_stage3_inst_n_1;
  wire u_core_stage3_inst_n_10;
  wire u_core_stage3_inst_n_11;
  wire u_core_stage3_inst_n_12;
  wire u_core_stage3_inst_n_13;
  wire u_core_stage3_inst_n_14;
  wire u_core_stage3_inst_n_15;
  wire u_core_stage3_inst_n_16;
  wire u_core_stage3_inst_n_17;
  wire u_core_stage3_inst_n_18;
  wire u_core_stage3_inst_n_19;
  wire u_core_stage3_inst_n_2;
  wire u_core_stage3_inst_n_20;
  wire u_core_stage3_inst_n_21;
  wire u_core_stage3_inst_n_22;
  wire u_core_stage3_inst_n_23;
  wire u_core_stage3_inst_n_24;
  wire u_core_stage3_inst_n_25;
  wire u_core_stage3_inst_n_26;
  wire u_core_stage3_inst_n_27;
  wire u_core_stage3_inst_n_28;
  wire u_core_stage3_inst_n_29;
  wire u_core_stage3_inst_n_3;
  wire u_core_stage3_inst_n_30;
  wire u_core_stage3_inst_n_31;
  wire u_core_stage3_inst_n_4;
  wire u_core_stage3_inst_n_5;
  wire u_core_stage3_inst_n_6;
  wire u_core_stage3_inst_n_7;
  wire u_core_stage3_inst_n_8;
  wire u_core_stage3_inst_n_9;
  wire [31:1]uain0;
  wire write_axi_enable;
  wire [7:6]\NLW_ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_4_CO_UNCONNECTED ;
  wire [7:7]\NLW_ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_4_O_UNCONNECTED ;

  LUT6 #(
    .INIT(64'hFF33CC00B8B8B8B8)) 
    \anorm_p[10]_i_1 
       (.I0(\anorm_p[10]_i_2_n_0 ),
        .I1(out1[0]),
        .I2(\anorm_p[12]_i_2_n_0 ),
        .I3(\anorm_p[11]_i_2_n_0 ),
        .I4(\anorm_p[11]_i_3_n_0 ),
        .I5(p_0_in),
        .O(anorm[10]));
  LUT1 #(
    .INIT(2'h1)) 
    \anorm_p[10]_i_10 
       (.I0(Q[4]),
        .O(p_0_in__0[4]));
  LUT1 #(
    .INIT(2'h1)) 
    \anorm_p[10]_i_11 
       (.I0(Q[3]),
        .O(p_0_in__0[3]));
  LUT1 #(
    .INIT(2'h1)) 
    \anorm_p[10]_i_12 
       (.I0(Q[2]),
        .O(p_0_in__0[2]));
  LUT1 #(
    .INIT(2'h1)) 
    \anorm_p[10]_i_13 
       (.I0(Q[1]),
        .O(p_0_in__0[1]));
  LUT6 #(
    .INIT(64'hE2FF0000E2000000)) 
    \anorm_p[10]_i_2 
       (.I0(Q[3]),
        .I1(Q[23]),
        .I2(uain0[3]),
        .I3(out1[1]),
        .I4(\anorm_p[10]_i_4_n_0 ),
        .I5(\anorm_p[12]_i_7_n_0 ),
        .O(\anorm_p[10]_i_2_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair70" *) 
  LUT2 #(
    .INIT(4'hB)) 
    \anorm_p[10]_i_4 
       (.I0(out1142_out),
        .I1(\ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_2_n_0 ),
        .O(\anorm_p[10]_i_4_n_0 ));
  LUT1 #(
    .INIT(2'h1)) 
    \anorm_p[10]_i_5 
       (.I0(Q[0]),
        .O(p_0_in__0[0]));
  LUT1 #(
    .INIT(2'h1)) 
    \anorm_p[10]_i_6 
       (.I0(Q[8]),
        .O(p_0_in__0[8]));
  LUT1 #(
    .INIT(2'h1)) 
    \anorm_p[10]_i_7 
       (.I0(Q[7]),
        .O(p_0_in__0[7]));
  LUT1 #(
    .INIT(2'h1)) 
    \anorm_p[10]_i_8 
       (.I0(Q[6]),
        .O(p_0_in__0[6]));
  LUT1 #(
    .INIT(2'h1)) 
    \anorm_p[10]_i_9 
       (.I0(Q[5]),
        .O(p_0_in__0[5]));
  LUT6 #(
    .INIT(64'hB8B8B8B8FF33CC00)) 
    \anorm_p[11]_i_1 
       (.I0(\anorm_p[12]_i_2_n_0 ),
        .I1(out1[0]),
        .I2(\anorm_p[12]_i_3_n_0 ),
        .I3(\anorm_p[11]_i_2_n_0 ),
        .I4(\anorm_p[11]_i_3_n_0 ),
        .I5(p_0_in),
        .O(anorm[11]));
  LUT6 #(
    .INIT(64'h000000003030BB88)) 
    \anorm_p[11]_i_2 
       (.I0(\anorm_p[11]_i_4_n_0 ),
        .I1(out1[1]),
        .I2(Q[0]),
        .I3(\anorm_p[11]_i_5_n_0 ),
        .I4(out1[2]),
        .I5(\ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_1_n_0 ),
        .O(\anorm_p[11]_i_2_n_0 ));
  LUT6 #(
    .INIT(64'h000000003030BB88)) 
    \anorm_p[11]_i_3 
       (.I0(\anorm_p[11]_i_6_n_0 ),
        .I1(out1[1]),
        .I2(\anorm_p[11]_i_7_n_0 ),
        .I3(\anorm_p[11]_i_8_n_0 ),
        .I4(out1[2]),
        .I5(\ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_1_n_0 ),
        .O(\anorm_p[11]_i_3_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair99" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \anorm_p[11]_i_4 
       (.I0(uain0[4]),
        .I1(Q[23]),
        .I2(Q[4]),
        .O(\anorm_p[11]_i_4_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair98" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \anorm_p[11]_i_5 
       (.I0(uain0[8]),
        .I1(Q[23]),
        .I2(Q[8]),
        .O(\anorm_p[11]_i_5_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair97" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \anorm_p[11]_i_6 
       (.I0(uain0[6]),
        .I1(Q[23]),
        .I2(Q[6]),
        .O(\anorm_p[11]_i_6_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair98" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \anorm_p[11]_i_7 
       (.I0(uain0[2]),
        .I1(Q[23]),
        .I2(Q[2]),
        .O(\anorm_p[11]_i_7_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair96" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \anorm_p[11]_i_8 
       (.I0(uain0[10]),
        .I1(Q[23]),
        .I2(Q[10]),
        .O(\anorm_p[11]_i_8_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair69" *) 
  LUT5 #(
    .INIT(32'hFF00B8B8)) 
    \anorm_p[12]_i_1 
       (.I0(\anorm_p[12]_i_2_n_0 ),
        .I1(out1[0]),
        .I2(\anorm_p[12]_i_3_n_0 ),
        .I3(\anorm_p[13]_i_2_n_0 ),
        .I4(p_0_in),
        .O(anorm[12]));
  LUT6 #(
    .INIT(64'h000000003030BB88)) 
    \anorm_p[12]_i_2 
       (.I0(\anorm_p[12]_i_4_n_0 ),
        .I1(out1[1]),
        .I2(\anorm_p[12]_i_5_n_0 ),
        .I3(\anorm_p[12]_i_6_n_0 ),
        .I4(out1[2]),
        .I5(\ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_1_n_0 ),
        .O(\anorm_p[12]_i_2_n_0 ));
  LUT6 #(
    .INIT(64'h000000003030BB88)) 
    \anorm_p[12]_i_3 
       (.I0(\anorm_p[12]_i_7_n_0 ),
        .I1(out1[1]),
        .I2(\anorm_p[12]_i_8_n_0 ),
        .I3(\anorm_p[12]_i_9_n_0 ),
        .I4(out1[2]),
        .I5(\ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_1_n_0 ),
        .O(\anorm_p[12]_i_3_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair80" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \anorm_p[12]_i_4 
       (.I0(uain0[5]),
        .I1(Q[23]),
        .I2(Q[5]),
        .O(\anorm_p[12]_i_4_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair82" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \anorm_p[12]_i_5 
       (.I0(uain0[1]),
        .I1(Q[23]),
        .I2(Q[1]),
        .O(\anorm_p[12]_i_5_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair79" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \anorm_p[12]_i_6 
       (.I0(uain0[9]),
        .I1(Q[23]),
        .I2(Q[9]),
        .O(\anorm_p[12]_i_6_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair78" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \anorm_p[12]_i_7 
       (.I0(uain0[7]),
        .I1(Q[23]),
        .I2(Q[7]),
        .O(\anorm_p[12]_i_7_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair83" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \anorm_p[12]_i_8 
       (.I0(uain0[3]),
        .I1(Q[23]),
        .I2(Q[3]),
        .O(\anorm_p[12]_i_8_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair76" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \anorm_p[12]_i_9 
       (.I0(uain0[11]),
        .I1(Q[23]),
        .I2(Q[11]),
        .O(\anorm_p[12]_i_9_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair84" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \anorm_p[13]_i_1 
       (.I0(\anorm_p[14]_i_2_n_0 ),
        .I1(p_0_in),
        .I2(\anorm_p[13]_i_2_n_0 ),
        .O(anorm[13]));
  LUT5 #(
    .INIT(32'hB8BBB888)) 
    \anorm_p[13]_i_2 
       (.I0(\anorm_p[11]_i_3_n_0 ),
        .I1(out1[0]),
        .I2(\anorm_p[15]_i_3_n_0 ),
        .I3(out1[1]),
        .I4(\anorm_p[19]_i_3_n_0 ),
        .O(\anorm_p[13]_i_2_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair84" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \anorm_p[14]_i_1 
       (.I0(\anorm_p[15]_i_2_n_0 ),
        .I1(p_0_in),
        .I2(\anorm_p[14]_i_2_n_0 ),
        .O(anorm[14]));
  LUT5 #(
    .INIT(32'hB8BBB888)) 
    \anorm_p[14]_i_2 
       (.I0(\anorm_p[12]_i_3_n_0 ),
        .I1(out1[0]),
        .I2(\anorm_p[16]_i_3_n_0 ),
        .I3(out1[1]),
        .I4(\anorm_p[20]_i_3_n_0 ),
        .O(\anorm_p[14]_i_2_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair85" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \anorm_p[15]_i_1 
       (.I0(\anorm_p[16]_i_2_n_0 ),
        .I1(p_0_in),
        .I2(\anorm_p[15]_i_2_n_0 ),
        .O(anorm[15]));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \anorm_p[15]_i_2 
       (.I0(\anorm_p[15]_i_3_n_0 ),
        .I1(\anorm_p[19]_i_3_n_0 ),
        .I2(out1[0]),
        .I3(\anorm_p[17]_i_3_n_0 ),
        .I4(out1[1]),
        .I5(\anorm_p[21]_i_3_n_0 ),
        .O(\anorm_p[15]_i_2_n_0 ));
  LUT6 #(
    .INIT(64'h00000000AAAACFC0)) 
    \anorm_p[15]_i_3 
       (.I0(Q[0]),
        .I1(uain0[8]),
        .I2(Q[23]),
        .I3(Q[8]),
        .I4(out1[2]),
        .I5(\ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_1_n_0 ),
        .O(\anorm_p[15]_i_3_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair85" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \anorm_p[16]_i_1 
       (.I0(\anorm_p[17]_i_2_n_0 ),
        .I1(p_0_in),
        .I2(\anorm_p[16]_i_2_n_0 ),
        .O(anorm[16]));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \anorm_p[16]_i_2 
       (.I0(\anorm_p[16]_i_3_n_0 ),
        .I1(\anorm_p[20]_i_3_n_0 ),
        .I2(out1[0]),
        .I3(\anorm_p[18]_i_3_n_0 ),
        .I4(out1[1]),
        .I5(\anorm_p[22]_i_3_n_0 ),
        .O(\anorm_p[16]_i_2_n_0 ));
  LUT6 #(
    .INIT(64'h00000000B8B8FF00)) 
    \anorm_p[16]_i_3 
       (.I0(uain0[1]),
        .I1(Q[23]),
        .I2(Q[1]),
        .I3(\anorm_p[12]_i_6_n_0 ),
        .I4(out1[2]),
        .I5(\ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_1_n_0 ),
        .O(\anorm_p[16]_i_3_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair86" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \anorm_p[17]_i_1 
       (.I0(\anorm_p[18]_i_2_n_0 ),
        .I1(p_0_in),
        .I2(\anorm_p[17]_i_2_n_0 ),
        .O(anorm[17]));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \anorm_p[17]_i_2 
       (.I0(\anorm_p[17]_i_3_n_0 ),
        .I1(\anorm_p[21]_i_3_n_0 ),
        .I2(out1[0]),
        .I3(\anorm_p[19]_i_3_n_0 ),
        .I4(out1[1]),
        .I5(\anorm_p[23]_i_3_n_0 ),
        .O(\anorm_p[17]_i_2_n_0 ));
  LUT6 #(
    .INIT(64'h00000000B8B8FF00)) 
    \anorm_p[17]_i_3 
       (.I0(uain0[2]),
        .I1(Q[23]),
        .I2(Q[2]),
        .I3(\anorm_p[11]_i_8_n_0 ),
        .I4(out1[2]),
        .I5(\ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_1_n_0 ),
        .O(\anorm_p[17]_i_3_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair86" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \anorm_p[18]_i_1 
       (.I0(\anorm_p[19]_i_2_n_0 ),
        .I1(p_0_in),
        .I2(\anorm_p[18]_i_2_n_0 ),
        .O(anorm[18]));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \anorm_p[18]_i_2 
       (.I0(\anorm_p[18]_i_3_n_0 ),
        .I1(\anorm_p[22]_i_3_n_0 ),
        .I2(out1[0]),
        .I3(\anorm_p[20]_i_3_n_0 ),
        .I4(out1[1]),
        .I5(\anorm_p[24]_i_3_n_0 ),
        .O(\anorm_p[18]_i_2_n_0 ));
  LUT6 #(
    .INIT(64'h00000000B8B8FF00)) 
    \anorm_p[18]_i_3 
       (.I0(uain0[3]),
        .I1(Q[23]),
        .I2(Q[3]),
        .I3(\anorm_p[12]_i_9_n_0 ),
        .I4(out1[2]),
        .I5(\ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_1_n_0 ),
        .O(\anorm_p[18]_i_3_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair87" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \anorm_p[19]_i_1 
       (.I0(\anorm_p[20]_i_2_n_0 ),
        .I1(p_0_in),
        .I2(\anorm_p[19]_i_2_n_0 ),
        .O(anorm[19]));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \anorm_p[19]_i_2 
       (.I0(\anorm_p[19]_i_3_n_0 ),
        .I1(\anorm_p[23]_i_3_n_0 ),
        .I2(out1[0]),
        .I3(\anorm_p[21]_i_3_n_0 ),
        .I4(out1[1]),
        .I5(\anorm_p[25]_i_3_n_0 ),
        .O(\anorm_p[19]_i_2_n_0 ));
  LUT6 #(
    .INIT(64'h00000000B8B8FF00)) 
    \anorm_p[19]_i_3 
       (.I0(uain0[4]),
        .I1(Q[23]),
        .I2(Q[4]),
        .I3(\ds_reg_reg_reg[1][1]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_7_n_0 ),
        .I4(out1[2]),
        .I5(\ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_1_n_0 ),
        .O(\anorm_p[19]_i_3_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair87" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \anorm_p[20]_i_1 
       (.I0(\anorm_p[21]_i_2_n_0 ),
        .I1(p_0_in),
        .I2(\anorm_p[20]_i_2_n_0 ),
        .O(anorm[20]));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \anorm_p[20]_i_2 
       (.I0(\anorm_p[20]_i_3_n_0 ),
        .I1(\anorm_p[24]_i_3_n_0 ),
        .I2(out1[0]),
        .I3(\anorm_p[22]_i_3_n_0 ),
        .I4(out1[1]),
        .I5(\anorm_p[26]_i_3_n_0 ),
        .O(\anorm_p[20]_i_2_n_0 ));
  LUT6 #(
    .INIT(64'h00000000B8B8FF00)) 
    \anorm_p[20]_i_3 
       (.I0(uain0[5]),
        .I1(Q[23]),
        .I2(Q[5]),
        .I3(\anorm_p[31]_i_16_n_0 ),
        .I4(out1[2]),
        .I5(\ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_1_n_0 ),
        .O(\anorm_p[20]_i_3_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair88" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \anorm_p[21]_i_1 
       (.I0(\anorm_p[22]_i_2_n_0 ),
        .I1(p_0_in),
        .I2(\anorm_p[21]_i_2_n_0 ),
        .O(anorm[21]));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \anorm_p[21]_i_2 
       (.I0(\anorm_p[21]_i_3_n_0 ),
        .I1(\anorm_p[25]_i_3_n_0 ),
        .I2(out1[0]),
        .I3(\anorm_p[23]_i_3_n_0 ),
        .I4(out1[1]),
        .I5(\anorm_p[27]_i_3_n_0 ),
        .O(\anorm_p[21]_i_2_n_0 ));
  LUT6 #(
    .INIT(64'h00000000B8B8FF00)) 
    \anorm_p[21]_i_3 
       (.I0(uain0[6]),
        .I1(Q[23]),
        .I2(Q[6]),
        .I3(\anorm_p[31]_i_18_n_0 ),
        .I4(out1[2]),
        .I5(\ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_1_n_0 ),
        .O(\anorm_p[21]_i_3_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair88" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \anorm_p[22]_i_1 
       (.I0(\anorm_p[23]_i_2_n_0 ),
        .I1(p_0_in),
        .I2(\anorm_p[22]_i_2_n_0 ),
        .O(anorm[22]));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \anorm_p[22]_i_2 
       (.I0(\anorm_p[22]_i_3_n_0 ),
        .I1(\anorm_p[26]_i_3_n_0 ),
        .I2(out1[0]),
        .I3(\anorm_p[24]_i_3_n_0 ),
        .I4(out1[1]),
        .I5(\anorm_p[28]_i_3_n_0 ),
        .O(\anorm_p[22]_i_2_n_0 ));
  LUT6 #(
    .INIT(64'h00000000B8B8FF00)) 
    \anorm_p[22]_i_3 
       (.I0(uain0[7]),
        .I1(Q[23]),
        .I2(Q[7]),
        .I3(\anorm_p[31]_i_12_n_0 ),
        .I4(out1[2]),
        .I5(\ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_1_n_0 ),
        .O(\anorm_p[22]_i_3_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair89" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \anorm_p[23]_i_1 
       (.I0(\anorm_p[24]_i_2_n_0 ),
        .I1(p_0_in),
        .I2(\anorm_p[23]_i_2_n_0 ),
        .O(anorm[23]));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \anorm_p[23]_i_2 
       (.I0(\anorm_p[23]_i_3_n_0 ),
        .I1(\anorm_p[27]_i_3_n_0 ),
        .I2(out1[0]),
        .I3(\anorm_p[25]_i_3_n_0 ),
        .I4(out1[1]),
        .I5(\anorm_p[29]_i_3_n_0 ),
        .O(\anorm_p[23]_i_2_n_0 ));
  LUT5 #(
    .INIT(32'h30BB3088)) 
    \anorm_p[23]_i_3 
       (.I0(\anorm_p[11]_i_5_n_0 ),
        .I1(out1[2]),
        .I2(Q[0]),
        .I3(\ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_1_n_0 ),
        .I4(\anorm_p[23]_i_4_n_0 ),
        .O(\anorm_p[23]_i_3_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair96" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \anorm_p[23]_i_4 
       (.I0(uain0[16]),
        .I1(Q[23]),
        .I2(Q[16]),
        .O(\anorm_p[23]_i_4_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair89" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \anorm_p[24]_i_1 
       (.I0(\anorm_p[25]_i_2_n_0 ),
        .I1(p_0_in),
        .I2(\anorm_p[24]_i_2_n_0 ),
        .O(anorm[24]));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \anorm_p[24]_i_2 
       (.I0(\anorm_p[24]_i_3_n_0 ),
        .I1(\anorm_p[28]_i_3_n_0 ),
        .I2(out1[0]),
        .I3(\anorm_p[26]_i_3_n_0 ),
        .I4(out1[1]),
        .I5(\anorm_p[30]_i_3_n_0 ),
        .O(\anorm_p[24]_i_2_n_0 ));
  LUT5 #(
    .INIT(32'h30BB3088)) 
    \anorm_p[24]_i_3 
       (.I0(\anorm_p[12]_i_6_n_0 ),
        .I1(out1[2]),
        .I2(\anorm_p[12]_i_5_n_0 ),
        .I3(\ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_1_n_0 ),
        .I4(\anorm_p[24]_i_4_n_0 ),
        .O(\anorm_p[24]_i_3_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair75" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \anorm_p[24]_i_4 
       (.I0(uain0[17]),
        .I1(Q[23]),
        .I2(Q[17]),
        .O(\anorm_p[24]_i_4_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair90" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \anorm_p[25]_i_1 
       (.I0(\anorm_p[26]_i_2_n_0 ),
        .I1(p_0_in),
        .I2(\anorm_p[25]_i_2_n_0 ),
        .O(anorm[25]));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \anorm_p[25]_i_2 
       (.I0(\anorm_p[25]_i_3_n_0 ),
        .I1(\anorm_p[29]_i_3_n_0 ),
        .I2(out1[0]),
        .I3(\anorm_p[27]_i_3_n_0 ),
        .I4(out1[1]),
        .I5(\anorm_p[31]_i_10_n_0 ),
        .O(\anorm_p[25]_i_2_n_0 ));
  LUT5 #(
    .INIT(32'h30BB3088)) 
    \anorm_p[25]_i_3 
       (.I0(\anorm_p[11]_i_8_n_0 ),
        .I1(out1[2]),
        .I2(\anorm_p[11]_i_7_n_0 ),
        .I3(\ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_1_n_0 ),
        .I4(\anorm_p[25]_i_4_n_0 ),
        .O(\anorm_p[25]_i_3_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair97" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \anorm_p[25]_i_4 
       (.I0(uain0[18]),
        .I1(Q[23]),
        .I2(Q[18]),
        .O(\anorm_p[25]_i_4_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair90" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \anorm_p[26]_i_1 
       (.I0(\anorm_p[27]_i_2_n_0 ),
        .I1(p_0_in),
        .I2(\anorm_p[26]_i_2_n_0 ),
        .O(anorm[26]));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \anorm_p[26]_i_2 
       (.I0(\anorm_p[26]_i_3_n_0 ),
        .I1(\anorm_p[30]_i_3_n_0 ),
        .I2(out1[0]),
        .I3(\anorm_p[28]_i_3_n_0 ),
        .I4(out1[1]),
        .I5(\anorm_p[31]_i_6_n_0 ),
        .O(\anorm_p[26]_i_2_n_0 ));
  LUT5 #(
    .INIT(32'h30BB3088)) 
    \anorm_p[26]_i_3 
       (.I0(\anorm_p[12]_i_9_n_0 ),
        .I1(out1[2]),
        .I2(\anorm_p[12]_i_8_n_0 ),
        .I3(\ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_1_n_0 ),
        .I4(\anorm_p[26]_i_4_n_0 ),
        .O(\anorm_p[26]_i_3_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair77" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \anorm_p[26]_i_4 
       (.I0(uain0[19]),
        .I1(Q[23]),
        .I2(Q[19]),
        .O(\anorm_p[26]_i_4_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair91" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \anorm_p[27]_i_1 
       (.I0(\anorm_p[28]_i_2_n_0 ),
        .I1(p_0_in),
        .I2(\anorm_p[27]_i_2_n_0 ),
        .O(anorm[27]));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \anorm_p[27]_i_2 
       (.I0(\anorm_p[27]_i_3_n_0 ),
        .I1(\anorm_p[31]_i_10_n_0 ),
        .I2(out1[0]),
        .I3(\anorm_p[29]_i_3_n_0 ),
        .I4(out1[1]),
        .I5(\anorm_p[31]_i_9_n_0 ),
        .O(\anorm_p[27]_i_2_n_0 ));
  LUT5 #(
    .INIT(32'h30BB3088)) 
    \anorm_p[27]_i_3 
       (.I0(\ds_reg_reg_reg[1][1]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_7_n_0 ),
        .I1(out1[2]),
        .I2(\anorm_p[11]_i_4_n_0 ),
        .I3(\ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_1_n_0 ),
        .I4(\anorm_p[27]_i_4_n_0 ),
        .O(\anorm_p[27]_i_3_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair95" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \anorm_p[27]_i_4 
       (.I0(uain0[20]),
        .I1(Q[23]),
        .I2(Q[20]),
        .O(\anorm_p[27]_i_4_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair91" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \anorm_p[28]_i_1 
       (.I0(\anorm_p[29]_i_2_n_0 ),
        .I1(p_0_in),
        .I2(\anorm_p[28]_i_2_n_0 ),
        .O(anorm[28]));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \anorm_p[28]_i_2 
       (.I0(\anorm_p[28]_i_3_n_0 ),
        .I1(\anorm_p[31]_i_6_n_0 ),
        .I2(out1[0]),
        .I3(\anorm_p[30]_i_3_n_0 ),
        .I4(out1[1]),
        .I5(\anorm_p[31]_i_5_n_0 ),
        .O(\anorm_p[28]_i_2_n_0 ));
  LUT5 #(
    .INIT(32'h30BB3088)) 
    \anorm_p[28]_i_3 
       (.I0(\anorm_p[31]_i_16_n_0 ),
        .I1(out1[2]),
        .I2(\anorm_p[12]_i_4_n_0 ),
        .I3(\ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_1_n_0 ),
        .I4(\anorm_p[28]_i_4_n_0 ),
        .O(\anorm_p[28]_i_3_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair74" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \anorm_p[28]_i_4 
       (.I0(uain0[21]),
        .I1(Q[23]),
        .I2(Q[21]),
        .O(\anorm_p[28]_i_4_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair92" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \anorm_p[29]_i_1 
       (.I0(\anorm_p[30]_i_2_n_0 ),
        .I1(p_0_in),
        .I2(\anorm_p[29]_i_2_n_0 ),
        .O(anorm[29]));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \anorm_p[29]_i_2 
       (.I0(\anorm_p[29]_i_3_n_0 ),
        .I1(\anorm_p[31]_i_9_n_0 ),
        .I2(out1[0]),
        .I3(\anorm_p[31]_i_10_n_0 ),
        .I4(out1[1]),
        .I5(\anorm_p[31]_i_11_n_0 ),
        .O(\anorm_p[29]_i_2_n_0 ));
  LUT5 #(
    .INIT(32'h30BB3088)) 
    \anorm_p[29]_i_3 
       (.I0(\anorm_p[31]_i_18_n_0 ),
        .I1(out1[2]),
        .I2(\anorm_p[11]_i_6_n_0 ),
        .I3(\ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_1_n_0 ),
        .I4(\anorm_p[29]_i_4_n_0 ),
        .O(\anorm_p[29]_i_3_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair94" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \anorm_p[29]_i_4 
       (.I0(uain0[22]),
        .I1(Q[23]),
        .I2(Q[22]),
        .O(\anorm_p[29]_i_4_n_0 ));
  LUT5 #(
    .INIT(32'hF011F000)) 
    \anorm_p[2]_i_1 
       (.I0(out1[0]),
        .I1(out1[1]),
        .I2(\anorm_p[3]_i_2_n_0 ),
        .I3(p_0_in),
        .I4(\anorm_p[4]_i_2_n_0 ),
        .O(anorm[2]));
  (* SOFT_HLUTNM = "soft_lutpair92" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \anorm_p[30]_i_1 
       (.I0(\anorm_p[31]_i_3_n_0 ),
        .I1(p_0_in),
        .I2(\anorm_p[30]_i_2_n_0 ),
        .O(anorm[30]));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \anorm_p[30]_i_2 
       (.I0(\anorm_p[30]_i_3_n_0 ),
        .I1(\anorm_p[31]_i_5_n_0 ),
        .I2(out1[0]),
        .I3(\anorm_p[31]_i_6_n_0 ),
        .I4(out1[1]),
        .I5(\anorm_p[31]_i_7_n_0 ),
        .O(\anorm_p[30]_i_2_n_0 ));
  LUT6 #(
    .INIT(64'h30BB308830883088)) 
    \anorm_p[30]_i_3 
       (.I0(\anorm_p[31]_i_12_n_0 ),
        .I1(out1[2]),
        .I2(\anorm_p[12]_i_7_n_0 ),
        .I3(\ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_1_n_0 ),
        .I4(uain0[23]),
        .I5(Q[23]),
        .O(\anorm_p[30]_i_3_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair93" *) 
  LUT2 #(
    .INIT(4'hE)) 
    \anorm_p[31]_i_1 
       (.I0(p_0_in),
        .I1(\anorm_p[31]_i_3_n_0 ),
        .O(anorm[31]));
  LUT6 #(
    .INIT(64'hFFFFEC200000EC20)) 
    \anorm_p[31]_i_10 
       (.I0(Q[23]),
        .I1(\ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_1_n_0 ),
        .I2(uain0[24]),
        .I3(\anorm_p[11]_i_5_n_0 ),
        .I4(out1[2]),
        .I5(\anorm_p[31]_i_21_n_0 ),
        .O(\anorm_p[31]_i_10_n_0 ));
  LUT6 #(
    .INIT(64'hFFFFEC200000EC20)) 
    \anorm_p[31]_i_11 
       (.I0(Q[23]),
        .I1(\ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_1_n_0 ),
        .I2(uain0[28]),
        .I3(\ds_reg_reg_reg[1][1]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_7_n_0 ),
        .I4(out1[2]),
        .I5(\anorm_p[31]_i_22_n_0 ),
        .O(\anorm_p[31]_i_11_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair81" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \anorm_p[31]_i_12 
       (.I0(uain0[15]),
        .I1(Q[23]),
        .I2(Q[15]),
        .O(\anorm_p[31]_i_12_n_0 ));
  LUT6 #(
    .INIT(64'hFFBF008000800080)) 
    \anorm_p[31]_i_13 
       (.I0(\anorm_p[12]_i_7_n_0 ),
        .I1(\ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_2_n_0 ),
        .I2(\anorm_p[31]_i_23_n_0 ),
        .I3(\ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_5_n_0 ),
        .I4(uain0[23]),
        .I5(Q[23]),
        .O(\anorm_p[31]_i_13_n_0 ));
  LUT6 #(
    .INIT(64'hFFFFFFFB00000008)) 
    \anorm_p[31]_i_14 
       (.I0(\anorm_p[12]_i_8_n_0 ),
        .I1(\ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_2_n_0 ),
        .I2(\ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_3_n_0 ),
        .I3(out1142_out),
        .I4(\ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_5_n_0 ),
        .I5(\anorm_p[26]_i_4_n_0 ),
        .O(\anorm_p[31]_i_14_n_0 ));
  LUT6 #(
    .INIT(64'hFFFFFFFB00000008)) 
    \anorm_p[31]_i_15 
       (.I0(\anorm_p[12]_i_5_n_0 ),
        .I1(\ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_2_n_0 ),
        .I2(\ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_3_n_0 ),
        .I3(out1142_out),
        .I4(\ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_5_n_0 ),
        .I5(\anorm_p[24]_i_4_n_0 ),
        .O(\anorm_p[31]_i_15_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair73" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \anorm_p[31]_i_16 
       (.I0(uain0[13]),
        .I1(Q[23]),
        .I2(Q[13]),
        .O(\anorm_p[31]_i_16_n_0 ));
  LUT6 #(
    .INIT(64'hFFFFFFFB00000008)) 
    \anorm_p[31]_i_17 
       (.I0(\anorm_p[12]_i_4_n_0 ),
        .I1(\ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_2_n_0 ),
        .I2(\ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_3_n_0 ),
        .I3(out1142_out),
        .I4(\ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_5_n_0 ),
        .I5(\anorm_p[28]_i_4_n_0 ),
        .O(\anorm_p[31]_i_17_n_0 ));
  LUT3 #(
    .INIT(8'hB8)) 
    \anorm_p[31]_i_18 
       (.I0(uain0[14]),
        .I1(Q[23]),
        .I2(Q[14]),
        .O(\anorm_p[31]_i_18_n_0 ));
  LUT6 #(
    .INIT(64'hFFFFFFFB00000008)) 
    \anorm_p[31]_i_19 
       (.I0(\anorm_p[11]_i_6_n_0 ),
        .I1(\ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_2_n_0 ),
        .I2(\ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_3_n_0 ),
        .I3(out1142_out),
        .I4(\ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_5_n_0 ),
        .I5(\anorm_p[29]_i_4_n_0 ),
        .O(\anorm_p[31]_i_19_n_0 ));
  LUT6 #(
    .INIT(64'hFC0CFAFAFC0C0A0A)) 
    \anorm_p[31]_i_2 
       (.I0(\anorm_p[31]_i_4_n_0 ),
        .I1(\anorm_p[31]_i_5_n_0 ),
        .I2(out1[0]),
        .I3(\anorm_p[31]_i_6_n_0 ),
        .I4(out1[1]),
        .I5(\anorm_p[31]_i_7_n_0 ),
        .O(p_0_in));
  LUT6 #(
    .INIT(64'hFFFFFFFB00000008)) 
    \anorm_p[31]_i_20 
       (.I0(\anorm_p[11]_i_7_n_0 ),
        .I1(\ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_2_n_0 ),
        .I2(\ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_3_n_0 ),
        .I3(out1142_out),
        .I4(\ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_5_n_0 ),
        .I5(\anorm_p[25]_i_4_n_0 ),
        .O(\anorm_p[31]_i_20_n_0 ));
  LUT6 #(
    .INIT(64'hFFFFFFFB00000008)) 
    \anorm_p[31]_i_21 
       (.I0(Q[0]),
        .I1(\ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_2_n_0 ),
        .I2(\ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_3_n_0 ),
        .I3(out1142_out),
        .I4(\ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_5_n_0 ),
        .I5(\anorm_p[23]_i_4_n_0 ),
        .O(\anorm_p[31]_i_21_n_0 ));
  LUT6 #(
    .INIT(64'hFFFFFFFB00000008)) 
    \anorm_p[31]_i_22 
       (.I0(\anorm_p[11]_i_4_n_0 ),
        .I1(\ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_2_n_0 ),
        .I2(\ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_3_n_0 ),
        .I3(out1142_out),
        .I4(\ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_5_n_0 ),
        .I5(\anorm_p[27]_i_4_n_0 ),
        .O(\anorm_p[31]_i_22_n_0 ));
  LUT6 #(
    .INIT(64'h0000000000000353)) 
    \anorm_p[31]_i_23 
       (.I0(uain0[23]),
        .I1(Q[22]),
        .I2(Q[23]),
        .I3(uain0[22]),
        .I4(\ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_7_n_0 ),
        .I5(out1142_out),
        .O(\anorm_p[31]_i_23_n_0 ));
  LUT6 #(
    .INIT(64'hFC0CFAFAFC0C0A0A)) 
    \anorm_p[31]_i_3 
       (.I0(\anorm_p[31]_i_8_n_0 ),
        .I1(\anorm_p[31]_i_9_n_0 ),
        .I2(out1[0]),
        .I3(\anorm_p[31]_i_10_n_0 ),
        .I4(out1[1]),
        .I5(\anorm_p[31]_i_11_n_0 ),
        .O(\anorm_p[31]_i_3_n_0 ));
  LUT6 #(
    .INIT(64'hFFFFEC200000EC20)) 
    \anorm_p[31]_i_4 
       (.I0(Q[23]),
        .I1(\ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_1_n_0 ),
        .I2(uain0[31]),
        .I3(\anorm_p[31]_i_12_n_0 ),
        .I4(out1[2]),
        .I5(\anorm_p[31]_i_13_n_0 ),
        .O(\anorm_p[31]_i_4_n_0 ));
  LUT6 #(
    .INIT(64'hFFFFEC200000EC20)) 
    \anorm_p[31]_i_5 
       (.I0(Q[23]),
        .I1(\ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_1_n_0 ),
        .I2(uain0[27]),
        .I3(\anorm_p[12]_i_9_n_0 ),
        .I4(out1[2]),
        .I5(\anorm_p[31]_i_14_n_0 ),
        .O(\anorm_p[31]_i_5_n_0 ));
  LUT6 #(
    .INIT(64'hFFFFEC200000EC20)) 
    \anorm_p[31]_i_6 
       (.I0(Q[23]),
        .I1(\ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_1_n_0 ),
        .I2(uain0[25]),
        .I3(\anorm_p[12]_i_6_n_0 ),
        .I4(out1[2]),
        .I5(\anorm_p[31]_i_15_n_0 ),
        .O(\anorm_p[31]_i_6_n_0 ));
  LUT6 #(
    .INIT(64'hFFFFEC200000EC20)) 
    \anorm_p[31]_i_7 
       (.I0(Q[23]),
        .I1(\ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_1_n_0 ),
        .I2(uain0[29]),
        .I3(\anorm_p[31]_i_16_n_0 ),
        .I4(out1[2]),
        .I5(\anorm_p[31]_i_17_n_0 ),
        .O(\anorm_p[31]_i_7_n_0 ));
  LUT6 #(
    .INIT(64'hFFFFEC200000EC20)) 
    \anorm_p[31]_i_8 
       (.I0(Q[23]),
        .I1(\ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_1_n_0 ),
        .I2(uain0[30]),
        .I3(\anorm_p[31]_i_18_n_0 ),
        .I4(out1[2]),
        .I5(\anorm_p[31]_i_19_n_0 ),
        .O(\anorm_p[31]_i_8_n_0 ));
  LUT6 #(
    .INIT(64'hFFFFEC200000EC20)) 
    \anorm_p[31]_i_9 
       (.I0(Q[23]),
        .I1(\ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_1_n_0 ),
        .I2(uain0[26]),
        .I3(\anorm_p[11]_i_8_n_0 ),
        .I4(out1[2]),
        .I5(\anorm_p[31]_i_20_n_0 ),
        .O(\anorm_p[31]_i_9_n_0 ));
  LUT6 #(
    .INIT(64'h00ACFFFF00AC0000)) 
    \anorm_p[3]_i_1 
       (.I0(\anorm_p[4]_i_2_n_0 ),
        .I1(\anorm_p[4]_i_3_n_0 ),
        .I2(out1[0]),
        .I3(out1[1]),
        .I4(p_0_in),
        .I5(\anorm_p[3]_i_2_n_0 ),
        .O(anorm[3]));
  LUT5 #(
    .INIT(32'h000088C0)) 
    \anorm_p[3]_i_2 
       (.I0(Q[0]),
        .I1(\anorm_p[10]_i_4_n_0 ),
        .I2(\anorm_p[11]_i_7_n_0 ),
        .I3(out1[0]),
        .I4(out1[1]),
        .O(\anorm_p[3]_i_2_n_0 ));
  LUT6 #(
    .INIT(64'hFFFF000000AC00AC)) 
    \anorm_p[4]_i_1 
       (.I0(\anorm_p[4]_i_2_n_0 ),
        .I1(\anorm_p[4]_i_3_n_0 ),
        .I2(out1[0]),
        .I3(out1[1]),
        .I4(\anorm_p[5]_i_2_n_0 ),
        .I5(p_0_in),
        .O(anorm[4]));
  (* SOFT_HLUTNM = "soft_lutpair82" *) 
  LUT4 #(
    .INIT(16'hA808)) 
    \anorm_p[4]_i_2 
       (.I0(\anorm_p[10]_i_4_n_0 ),
        .I1(Q[1]),
        .I2(Q[23]),
        .I3(uain0[1]),
        .O(\anorm_p[4]_i_2_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair83" *) 
  LUT4 #(
    .INIT(16'hA808)) 
    \anorm_p[4]_i_3 
       (.I0(\anorm_p[10]_i_4_n_0 ),
        .I1(Q[3]),
        .I2(Q[23]),
        .I3(uain0[3]),
        .O(\anorm_p[4]_i_3_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair93" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \anorm_p[5]_i_1 
       (.I0(\anorm_p[6]_i_2_n_0 ),
        .I1(p_0_in),
        .I2(\anorm_p[5]_i_2_n_0 ),
        .O(anorm[5]));
  LUT6 #(
    .INIT(64'h30BB000030880000)) 
    \anorm_p[5]_i_2 
       (.I0(\anorm_p[11]_i_7_n_0 ),
        .I1(out1[0]),
        .I2(Q[0]),
        .I3(out1[1]),
        .I4(\anorm_p[10]_i_4_n_0 ),
        .I5(\anorm_p[11]_i_4_n_0 ),
        .O(\anorm_p[5]_i_2_n_0 ));
  LUT5 #(
    .INIT(32'hB8FFB800)) 
    \anorm_p[6]_i_1 
       (.I0(\anorm_p[7]_i_2_n_0 ),
        .I1(out1[0]),
        .I2(\anorm_p[9]_i_2_n_0 ),
        .I3(p_0_in),
        .I4(\anorm_p[6]_i_2_n_0 ),
        .O(anorm[6]));
  LUT6 #(
    .INIT(64'h30BB000030880000)) 
    \anorm_p[6]_i_2 
       (.I0(\anorm_p[12]_i_8_n_0 ),
        .I1(out1[0]),
        .I2(\anorm_p[12]_i_5_n_0 ),
        .I3(out1[1]),
        .I4(\anorm_p[10]_i_4_n_0 ),
        .I5(\anorm_p[12]_i_4_n_0 ),
        .O(\anorm_p[6]_i_2_n_0 ));
  LUT6 #(
    .INIT(64'hB8B8B8B8FF33CC00)) 
    \anorm_p[7]_i_1 
       (.I0(\anorm_p[8]_i_2_n_0 ),
        .I1(out1[0]),
        .I2(\anorm_p[10]_i_2_n_0 ),
        .I3(\anorm_p[7]_i_2_n_0 ),
        .I4(\anorm_p[9]_i_2_n_0 ),
        .I5(p_0_in),
        .O(anorm[7]));
  LUT6 #(
    .INIT(64'hB0B0B0808080B080)) 
    \anorm_p[7]_i_2 
       (.I0(Q[0]),
        .I1(out1[1]),
        .I2(\anorm_p[10]_i_4_n_0 ),
        .I3(Q[4]),
        .I4(Q[23]),
        .I5(uain0[4]),
        .O(\anorm_p[7]_i_2_n_0 ));
  LUT6 #(
    .INIT(64'hFF33CC00B8B8B8B8)) 
    \anorm_p[8]_i_1 
       (.I0(\anorm_p[8]_i_2_n_0 ),
        .I1(out1[0]),
        .I2(\anorm_p[10]_i_2_n_0 ),
        .I3(\anorm_p[9]_i_2_n_0 ),
        .I4(\anorm_p[11]_i_2_n_0 ),
        .I5(p_0_in),
        .O(anorm[8]));
  LUT6 #(
    .INIT(64'hE2FF0000E2000000)) 
    \anorm_p[8]_i_2 
       (.I0(Q[1]),
        .I1(Q[23]),
        .I2(uain0[1]),
        .I3(out1[1]),
        .I4(\anorm_p[10]_i_4_n_0 ),
        .I5(\anorm_p[12]_i_4_n_0 ),
        .O(\anorm_p[8]_i_2_n_0 ));
  LUT6 #(
    .INIT(64'hB8B8B8B8FF33CC00)) 
    \anorm_p[9]_i_1 
       (.I0(\anorm_p[10]_i_2_n_0 ),
        .I1(out1[0]),
        .I2(\anorm_p[12]_i_2_n_0 ),
        .I3(\anorm_p[9]_i_2_n_0 ),
        .I4(\anorm_p[11]_i_2_n_0 ),
        .I5(p_0_in),
        .O(anorm[9]));
  LUT6 #(
    .INIT(64'hE2FF0000E2000000)) 
    \anorm_p[9]_i_2 
       (.I0(Q[2]),
        .I1(Q[23]),
        .I2(uain0[2]),
        .I3(out1[1]),
        .I4(\anorm_p[10]_i_4_n_0 ),
        .I5(\anorm_p[11]_i_6_n_0 ),
        .O(\anorm_p[9]_i_2_n_0 ));
  FDRE \anorm_p_reg[10] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(anorm[10]),
        .Q(anorm_p[10]),
        .R(RSTP));
  (* ADDER_THRESHOLD = "35" *) 
  CARRY8 \anorm_p_reg[10]_i_3 
       (.CI(p_0_in__0[0]),
        .CI_TOP(1'b0),
        .CO({\anorm_p_reg[10]_i_3_n_0 ,\anorm_p_reg[10]_i_3_n_1 ,\anorm_p_reg[10]_i_3_n_2 ,\anorm_p_reg[10]_i_3_n_3 ,\anorm_p_reg[10]_i_3_n_4 ,\anorm_p_reg[10]_i_3_n_5 ,\anorm_p_reg[10]_i_3_n_6 ,\anorm_p_reg[10]_i_3_n_7 }),
        .DI({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .O(uain0[8:1]),
        .S(p_0_in__0[8:1]));
  FDRE \anorm_p_reg[11] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(anorm[11]),
        .Q(anorm_p[11]),
        .R(RSTP));
  FDRE \anorm_p_reg[12] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(anorm[12]),
        .Q(anorm_p[12]),
        .R(RSTP));
  FDRE \anorm_p_reg[13] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(anorm[13]),
        .Q(anorm_p[13]),
        .R(RSTP));
  FDRE \anorm_p_reg[14] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(anorm[14]),
        .Q(anorm_p[14]),
        .R(RSTP));
  FDRE \anorm_p_reg[15] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(anorm[15]),
        .Q(anorm_p[15]),
        .R(RSTP));
  FDRE \anorm_p_reg[16] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(anorm[16]),
        .Q(anorm_p[16]),
        .R(RSTP));
  FDRE \anorm_p_reg[17] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(anorm[17]),
        .Q(anorm_p[17]),
        .R(RSTP));
  FDRE \anorm_p_reg[18] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(anorm[18]),
        .Q(anorm_p[18]),
        .R(RSTP));
  FDRE \anorm_p_reg[19] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(anorm[19]),
        .Q(anorm_p[19]),
        .R(RSTP));
  FDRE \anorm_p_reg[20] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(anorm[20]),
        .Q(anorm_p[20]),
        .R(RSTP));
  FDRE \anorm_p_reg[21] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(anorm[21]),
        .Q(anorm_p[21]),
        .R(RSTP));
  FDRE \anorm_p_reg[22] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(anorm[22]),
        .Q(anorm_p[22]),
        .R(RSTP));
  FDRE \anorm_p_reg[23] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(anorm[23]),
        .Q(anorm_p[23]),
        .R(RSTP));
  FDRE \anorm_p_reg[24] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(anorm[24]),
        .Q(anorm_p[24]),
        .R(RSTP));
  FDRE \anorm_p_reg[25] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(anorm[25]),
        .Q(anorm_p[25]),
        .R(RSTP));
  FDRE \anorm_p_reg[26] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(anorm[26]),
        .Q(anorm_p[26]),
        .R(RSTP));
  FDRE \anorm_p_reg[27] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(anorm[27]),
        .Q(anorm_p[27]),
        .R(RSTP));
  FDRE \anorm_p_reg[28] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(anorm[28]),
        .Q(anorm_p[28]),
        .R(RSTP));
  FDRE \anorm_p_reg[29] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(anorm[29]),
        .Q(anorm_p[29]),
        .R(RSTP));
  FDRE \anorm_p_reg[2] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(anorm[2]),
        .Q(anorm_p[2]),
        .R(RSTP));
  FDRE \anorm_p_reg[30] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(anorm[30]),
        .Q(anorm_p[30]),
        .R(RSTP));
  FDRE \anorm_p_reg[31] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(anorm[31]),
        .Q(mstwobit),
        .R(RSTP));
  FDRE \anorm_p_reg[3] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(anorm[3]),
        .Q(anorm_p[3]),
        .R(RSTP));
  FDRE \anorm_p_reg[4] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(anorm[4]),
        .Q(anorm_p[4]),
        .R(RSTP));
  FDRE \anorm_p_reg[5] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(anorm[5]),
        .Q(anorm_p[5]),
        .R(RSTP));
  FDRE \anorm_p_reg[6] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(anorm[6]),
        .Q(anorm_p[6]),
        .R(RSTP));
  FDRE \anorm_p_reg[7] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(anorm[7]),
        .Q(anorm_p[7]),
        .R(RSTP));
  FDRE \anorm_p_reg[8] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(anorm[8]),
        .Q(anorm_p[8]),
        .R(RSTP));
  FDRE \anorm_p_reg[9] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(anorm[9]),
        .Q(anorm_p[9]),
        .R(RSTP));
  (* srl_bus_name = "\U0/u_IncreEncoder_V24_ip_dut_inst/u_IncreEncoder_V24_ip_src_IncreEncoder_V24/u_HDL_Reciprocal/changesign_reg_reg_reg " *) 
  (* srl_name = "\U0/u_IncreEncoder_V24_ip_dut_inst/u_IncreEncoder_V24_ip_src_IncreEncoder_V24/u_HDL_Reciprocal/changesign_reg_reg_reg[1]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0 " *) 
  SRL16E \changesign_reg_reg_reg[1]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0 
       (.A0(1'b1),
        .A1(1'b0),
        .A2(1'b0),
        .A3(1'b0),
        .CE(CEP),
        .CLK(IPCORE_CLK),
        .D(Q[23]),
        .Q(\changesign_reg_reg_reg[1]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_n_0 ));
  FDRE \changesign_reg_reg_reg[2]_U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_1 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\changesign_reg_reg_reg[1]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_n_0 ),
        .Q(\changesign_reg_reg_reg[2]_U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_1_n_0 ),
        .R(1'b0));
  FDRE \changesign_reg_reg_reg[3] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(changesign_reg_reg_reg_gate_n_0),
        .Q(\changesign_reg_reg_reg_n_0_[3] ),
        .R(RSTP));
  (* SOFT_HLUTNM = "soft_lutpair100" *) 
  LUT2 #(
    .INIT(4'h8)) 
    changesign_reg_reg_reg_gate
       (.I0(\changesign_reg_reg_reg[2]_U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_1_n_0 ),
        .I1(onemoreshift_reg_reg_reg_r_1_n_0),
        .O(changesign_reg_reg_reg_gate_n_0));
  (* srl_bus_name = "\U0/u_IncreEncoder_V24_ip_dut_inst/u_IncreEncoder_V24_ip_src_IncreEncoder_V24/u_HDL_Reciprocal/ds_reg_reg_reg[1] " *) 
  (* srl_name = "\U0/u_IncreEncoder_V24_ip_dut_inst/u_IncreEncoder_V24_ip_src_IncreEncoder_V24/u_HDL_Reciprocal/ds_reg_reg_reg[1][0]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0 " *) 
  SRL16E \ds_reg_reg_reg[1][0]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0 
       (.A0(1'b1),
        .A1(1'b0),
        .A2(1'b0),
        .A3(1'b0),
        .CE(CEP),
        .CLK(IPCORE_CLK),
        .D(out1[0]),
        .Q(\ds_reg_reg_reg[1][0]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_n_0 ));
  LUT5 #(
    .INIT(32'h0000E0A0)) 
    \ds_reg_reg_reg[1][0]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_1 
       (.I0(\ds_reg_reg_reg[1][0]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_2_n_0 ),
        .I1(\ds_reg_reg_reg[1][0]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_3_n_0 ),
        .I2(\ds_reg_reg_reg[1][0]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_4_n_0 ),
        .I3(\ds_reg_reg_reg[1][0]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_5_n_0 ),
        .I4(\ds_reg_reg_reg[1][0]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_6_n_0 ),
        .O(out1[0]));
  LUT4 #(
    .INIT(16'hFFFE)) 
    \ds_reg_reg_reg[1][0]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_2 
       (.I0(\ds_reg_reg_reg[1][2]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_4_n_0 ),
        .I1(\ds_reg_reg_reg[1][2]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_6_n_0 ),
        .I2(\ds_reg_reg_reg[1][1]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_8_n_0 ),
        .I3(\ds_reg_reg_reg[1][0]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_7_n_0 ),
        .O(\ds_reg_reg_reg[1][0]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_2_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair78" *) 
  LUT5 #(
    .INIT(32'h00053305)) 
    \ds_reg_reg_reg[1][0]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_3 
       (.I0(Q[7]),
        .I1(uain0[7]),
        .I2(Q[6]),
        .I3(Q[23]),
        .I4(uain0[6]),
        .O(\ds_reg_reg_reg[1][0]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_3_n_0 ));
  LUT6 #(
    .INIT(64'h00FD00FD00FDFDFD)) 
    \ds_reg_reg_reg[1][0]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_4 
       (.I0(\ds_reg_reg_reg[1][2]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_5_n_0 ),
        .I1(\ds_reg_reg_reg[1][1]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_8_n_0 ),
        .I2(\ds_reg_reg_reg[1][0]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_7_n_0 ),
        .I3(Q[23]),
        .I4(uain0[31]),
        .I5(uain0[30]),
        .O(\ds_reg_reg_reg[1][0]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_4_n_0 ));
  LUT6 #(
    .INIT(64'hAAAABABAAAAFBABF)) 
    \ds_reg_reg_reg[1][0]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_5 
       (.I0(\ds_reg_reg_reg[1][1]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_9_n_0 ),
        .I1(uain0[2]),
        .I2(Q[23]),
        .I3(Q[2]),
        .I4(uain0[3]),
        .I5(Q[3]),
        .O(\ds_reg_reg_reg[1][0]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_5_n_0 ));
  LUT6 #(
    .INIT(64'hFFFFFFFF00FF0002)) 
    \ds_reg_reg_reg[1][0]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_6 
       (.I0(\ds_reg_reg_reg[1][2]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_7_n_0 ),
        .I1(\ds_reg_reg_reg[1][2]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_6_n_0 ),
        .I2(\ds_reg_reg_reg[1][1]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_8_n_0 ),
        .I3(\ds_reg_reg_reg[1][0]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_7_n_0 ),
        .I4(\ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_16_n_0 ),
        .I5(\ds_reg_reg_reg[1][0]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_8_n_0 ),
        .O(\ds_reg_reg_reg[1][0]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_6_n_0 ));
  LUT6 #(
    .INIT(64'hFFFFFFFFF0F0F0E0)) 
    \ds_reg_reg_reg[1][0]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_7 
       (.I0(uain0[28]),
        .I1(uain0[29]),
        .I2(Q[23]),
        .I3(uain0[24]),
        .I4(uain0[25]),
        .I5(\ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_7_n_0 ),
        .O(\ds_reg_reg_reg[1][0]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_7_n_0 ));
  LUT6 #(
    .INIT(64'h0F0F0F0202020202)) 
    \ds_reg_reg_reg[1][0]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_8 
       (.I0(\ds_reg_reg_reg[1][1]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_10_n_0 ),
        .I1(\ds_reg_reg_reg[1][0]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_9_n_0 ),
        .I2(\ds_reg_reg_reg[1][1]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_3_n_0 ),
        .I3(uain0[26]),
        .I4(uain0[27]),
        .I5(Q[23]),
        .O(\ds_reg_reg_reg[1][0]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_8_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair71" *) 
  LUT3 #(
    .INIT(8'hE0)) 
    \ds_reg_reg_reg[1][0]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_9 
       (.I0(uain0[24]),
        .I1(uain0[25]),
        .I2(Q[23]),
        .O(\ds_reg_reg_reg[1][0]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_9_n_0 ));
  (* srl_bus_name = "\U0/u_IncreEncoder_V24_ip_dut_inst/u_IncreEncoder_V24_ip_src_IncreEncoder_V24/u_HDL_Reciprocal/ds_reg_reg_reg[1] " *) 
  (* srl_name = "\U0/u_IncreEncoder_V24_ip_dut_inst/u_IncreEncoder_V24_ip_src_IncreEncoder_V24/u_HDL_Reciprocal/ds_reg_reg_reg[1][1]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0 " *) 
  SRL16E \ds_reg_reg_reg[1][1]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0 
       (.A0(1'b1),
        .A1(1'b0),
        .A2(1'b0),
        .A3(1'b0),
        .CE(CEP),
        .CLK(IPCORE_CLK),
        .D(out1[1]),
        .Q(\ds_reg_reg_reg[1][1]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_n_0 ));
  LUT6 #(
    .INIT(64'h0000000022222322)) 
    \ds_reg_reg_reg[1][1]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_1 
       (.I0(\ds_reg_reg_reg[1][1]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_2_n_0 ),
        .I1(\ds_reg_reg_reg[1][1]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_3_n_0 ),
        .I2(\ds_reg_reg_reg[1][1]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_4_n_0 ),
        .I3(\ds_reg_reg_reg[1][1]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_5_n_0 ),
        .I4(\ds_reg_reg_reg[1][1]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_6_n_0 ),
        .I5(out1142_out),
        .O(out1[1]));
  (* SOFT_HLUTNM = "soft_lutpair72" *) 
  LUT4 #(
    .INIT(16'hFCAC)) 
    \ds_reg_reg_reg[1][1]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_10 
       (.I0(uain0[23]),
        .I1(Q[22]),
        .I2(Q[23]),
        .I3(uain0[22]),
        .O(\ds_reg_reg_reg[1][1]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_10_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair71" *) 
  LUT5 #(
    .INIT(32'hF0F0F0E0)) 
    \ds_reg_reg_reg[1][1]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_2 
       (.I0(uain0[25]),
        .I1(uain0[24]),
        .I2(Q[23]),
        .I3(uain0[27]),
        .I4(uain0[26]),
        .O(\ds_reg_reg_reg[1][1]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_2_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair94" *) 
  LUT3 #(
    .INIT(8'hE0)) 
    \ds_reg_reg_reg[1][1]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_3 
       (.I0(uain0[28]),
        .I1(uain0[29]),
        .I2(Q[23]),
        .O(\ds_reg_reg_reg[1][1]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_3_n_0 ));
  LUT6 #(
    .INIT(64'h000000000000EFEA)) 
    \ds_reg_reg_reg[1][1]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_4 
       (.I0(\ds_reg_reg_reg[1][1]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_7_n_0 ),
        .I1(uain0[13]),
        .I2(Q[23]),
        .I3(Q[13]),
        .I4(\ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_16_n_0 ),
        .I5(\ds_reg_reg_reg[1][1]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_8_n_0 ),
        .O(\ds_reg_reg_reg[1][1]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_4_n_0 ));
  LUT6 #(
    .INIT(64'hFFFFFFFFFFFFEEFE)) 
    \ds_reg_reg_reg[1][1]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_5 
       (.I0(\ds_reg_reg_reg[1][1]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_8_n_0 ),
        .I1(\ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_16_n_0 ),
        .I2(\ds_reg_reg_reg[1][0]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_3_n_0 ),
        .I3(\ds_reg_reg_reg[1][1]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_9_n_0 ),
        .I4(\ds_reg_reg_reg[1][2]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_7_n_0 ),
        .I5(\ds_reg_reg_reg[1][2]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_4_n_0 ),
        .O(\ds_reg_reg_reg[1][1]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_5_n_0 ));
  LUT5 #(
    .INIT(32'hFFFFFF10)) 
    \ds_reg_reg_reg[1][1]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_6 
       (.I0(\ds_reg_reg_reg[1][1]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_8_n_0 ),
        .I1(\ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_16_n_0 ),
        .I2(\ds_reg_reg_reg[1][2]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_5_n_0 ),
        .I3(\ds_reg_reg_reg[1][1]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_10_n_0 ),
        .I4(\ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_7_n_0 ),
        .O(\ds_reg_reg_reg[1][1]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_6_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair95" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \ds_reg_reg_reg[1][1]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_7 
       (.I0(uain0[12]),
        .I1(Q[23]),
        .I2(Q[12]),
        .O(\ds_reg_reg_reg[1][1]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_7_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair75" *) 
  LUT5 #(
    .INIT(32'hFFFACCFA)) 
    \ds_reg_reg_reg[1][1]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_8 
       (.I0(Q[17]),
        .I1(uain0[17]),
        .I2(Q[16]),
        .I3(Q[23]),
        .I4(uain0[16]),
        .O(\ds_reg_reg_reg[1][1]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_8_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair80" *) 
  LUT5 #(
    .INIT(32'hFFFACCFA)) 
    \ds_reg_reg_reg[1][1]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_9 
       (.I0(Q[5]),
        .I1(uain0[5]),
        .I2(Q[4]),
        .I3(Q[23]),
        .I4(uain0[4]),
        .O(\ds_reg_reg_reg[1][1]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_9_n_0 ));
  (* srl_bus_name = "\U0/u_IncreEncoder_V24_ip_dut_inst/u_IncreEncoder_V24_ip_src_IncreEncoder_V24/u_HDL_Reciprocal/ds_reg_reg_reg[1] " *) 
  (* srl_name = "\U0/u_IncreEncoder_V24_ip_dut_inst/u_IncreEncoder_V24_ip_src_IncreEncoder_V24/u_HDL_Reciprocal/ds_reg_reg_reg[1][2]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0 " *) 
  SRL16E \ds_reg_reg_reg[1][2]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0 
       (.A0(1'b1),
        .A1(1'b0),
        .A2(1'b0),
        .A3(1'b0),
        .CE(CEP),
        .CLK(IPCORE_CLK),
        .D(out1[2]),
        .Q(\ds_reg_reg_reg[1][2]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair70" *) 
  LUT5 #(
    .INIT(32'h44444440)) 
    \ds_reg_reg_reg[1][2]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_1 
       (.I0(out1142_out),
        .I1(\ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_2_n_0 ),
        .I2(\ds_reg_reg_reg[1][2]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_3_n_0 ),
        .I3(\ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_3_n_0 ),
        .I4(\ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_5_n_0 ),
        .O(out1[2]));
  (* SOFT_HLUTNM = "soft_lutpair99" *) 
  LUT3 #(
    .INIT(8'hE0)) 
    \ds_reg_reg_reg[1][2]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_2 
       (.I0(uain0[30]),
        .I1(uain0[31]),
        .I2(Q[23]),
        .O(out1142_out));
  LUT4 #(
    .INIT(16'h0001)) 
    \ds_reg_reg_reg[1][2]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_3 
       (.I0(\ds_reg_reg_reg[1][2]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_4_n_0 ),
        .I1(\ds_reg_reg_reg[1][2]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_5_n_0 ),
        .I2(\ds_reg_reg_reg[1][2]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_6_n_0 ),
        .I3(\ds_reg_reg_reg[1][2]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_7_n_0 ),
        .O(\ds_reg_reg_reg[1][2]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_3_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair79" *) 
  LUT5 #(
    .INIT(32'hFFFACCFA)) 
    \ds_reg_reg_reg[1][2]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_4 
       (.I0(Q[9]),
        .I1(uain0[9]),
        .I2(Q[8]),
        .I3(Q[23]),
        .I4(uain0[8]),
        .O(\ds_reg_reg_reg[1][2]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_4_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair81" *) 
  LUT5 #(
    .INIT(32'hFFFACCFA)) 
    \ds_reg_reg_reg[1][2]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_5 
       (.I0(Q[15]),
        .I1(uain0[15]),
        .I2(Q[14]),
        .I3(Q[23]),
        .I4(uain0[14]),
        .O(\ds_reg_reg_reg[1][2]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_5_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair73" *) 
  LUT5 #(
    .INIT(32'hFFFACCFA)) 
    \ds_reg_reg_reg[1][2]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_6 
       (.I0(Q[13]),
        .I1(uain0[13]),
        .I2(Q[12]),
        .I3(Q[23]),
        .I4(uain0[12]),
        .O(\ds_reg_reg_reg[1][2]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_6_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair76" *) 
  LUT5 #(
    .INIT(32'hFFFACCFA)) 
    \ds_reg_reg_reg[1][2]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_7 
       (.I0(Q[11]),
        .I1(uain0[11]),
        .I2(Q[10]),
        .I3(Q[23]),
        .I4(uain0[10]),
        .O(\ds_reg_reg_reg[1][2]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_7_n_0 ));
  (* srl_bus_name = "\U0/u_IncreEncoder_V24_ip_dut_inst/u_IncreEncoder_V24_ip_src_IncreEncoder_V24/u_HDL_Reciprocal/ds_reg_reg_reg[1] " *) 
  (* srl_name = "\U0/u_IncreEncoder_V24_ip_dut_inst/u_IncreEncoder_V24_ip_src_IncreEncoder_V24/u_HDL_Reciprocal/ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0 " *) 
  SRL16E \ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0 
       (.A0(1'b1),
        .A1(1'b0),
        .A2(1'b0),
        .A3(1'b0),
        .CE(CEP),
        .CLK(IPCORE_CLK),
        .D(\ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_1_n_0 ),
        .Q(\ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_n_0 ));
  LUT6 #(
    .INIT(64'h0000000002020222)) 
    \ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_1 
       (.I0(\ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_2_n_0 ),
        .I1(\ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_3_n_0 ),
        .I2(Q[23]),
        .I3(uain0[31]),
        .I4(uain0[30]),
        .I5(\ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_5_n_0 ),
        .O(\ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_1_n_0 ));
  LUT1 #(
    .INIT(2'h1)) 
    \ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_10 
       (.I0(Q[23]),
        .O(\ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_10_n_0 ));
  LUT1 #(
    .INIT(2'h1)) 
    \ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_11 
       (.I0(Q[23]),
        .O(\ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_11_n_0 ));
  LUT1 #(
    .INIT(2'h1)) 
    \ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_12 
       (.I0(Q[23]),
        .O(\ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_12_n_0 ));
  LUT1 #(
    .INIT(2'h1)) 
    \ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_13 
       (.I0(Q[23]),
        .O(\ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_13_n_0 ));
  LUT1 #(
    .INIT(2'h1)) 
    \ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_14 
       (.I0(Q[23]),
        .O(\ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_14_n_0 ));
  (* ADDER_THRESHOLD = "35" *) 
  CARRY8 \ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_15 
       (.CI(\anorm_p_reg[10]_i_3_n_0 ),
        .CI_TOP(1'b0),
        .CO({\ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_15_n_0 ,\ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_15_n_1 ,\ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_15_n_2 ,\ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_15_n_3 ,\ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_15_n_4 ,\ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_15_n_5 ,\ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_15_n_6 ,\ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_15_n_7 }),
        .DI({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .O(uain0[16:9]),
        .S(p_0_in__0[16:9]));
  (* SOFT_HLUTNM = "soft_lutpair77" *) 
  LUT5 #(
    .INIT(32'hFFFACCFA)) 
    \ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_16 
       (.I0(Q[19]),
        .I1(uain0[19]),
        .I2(Q[18]),
        .I3(Q[23]),
        .I4(uain0[18]),
        .O(\ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_16_n_0 ));
  LUT1 #(
    .INIT(2'h1)) 
    \ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_17 
       (.I0(Q[23]),
        .O(\ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_17_n_0 ));
  LUT1 #(
    .INIT(2'h1)) 
    \ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_18 
       (.I0(Q[23]),
        .O(\ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_18_n_0 ));
  LUT1 #(
    .INIT(2'h1)) 
    \ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_19 
       (.I0(Q[22]),
        .O(p_0_in__0[22]));
  LUT6 #(
    .INIT(64'h000000000F0F0F1F)) 
    \ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_2 
       (.I0(uain0[26]),
        .I1(uain0[27]),
        .I2(Q[23]),
        .I3(uain0[24]),
        .I4(uain0[25]),
        .I5(\ds_reg_reg_reg[1][1]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_3_n_0 ),
        .O(\ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_2_n_0 ));
  LUT1 #(
    .INIT(2'h1)) 
    \ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_20 
       (.I0(Q[21]),
        .O(p_0_in__0[21]));
  LUT1 #(
    .INIT(2'h1)) 
    \ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_21 
       (.I0(Q[20]),
        .O(p_0_in__0[20]));
  LUT1 #(
    .INIT(2'h1)) 
    \ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_22 
       (.I0(Q[19]),
        .O(p_0_in__0[19]));
  LUT1 #(
    .INIT(2'h1)) 
    \ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_23 
       (.I0(Q[18]),
        .O(p_0_in__0[18]));
  LUT1 #(
    .INIT(2'h1)) 
    \ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_24 
       (.I0(Q[17]),
        .O(p_0_in__0[17]));
  LUT1 #(
    .INIT(2'h1)) 
    \ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_25 
       (.I0(Q[16]),
        .O(p_0_in__0[16]));
  LUT1 #(
    .INIT(2'h1)) 
    \ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_26 
       (.I0(Q[15]),
        .O(p_0_in__0[15]));
  LUT1 #(
    .INIT(2'h1)) 
    \ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_27 
       (.I0(Q[14]),
        .O(p_0_in__0[14]));
  LUT1 #(
    .INIT(2'h1)) 
    \ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_28 
       (.I0(Q[13]),
        .O(p_0_in__0[13]));
  LUT1 #(
    .INIT(2'h1)) 
    \ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_29 
       (.I0(Q[12]),
        .O(p_0_in__0[12]));
  (* SOFT_HLUTNM = "soft_lutpair72" *) 
  LUT5 #(
    .INIT(32'hFFFAEFEA)) 
    \ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_3 
       (.I0(\ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_7_n_0 ),
        .I1(uain0[22]),
        .I2(Q[23]),
        .I3(Q[22]),
        .I4(uain0[23]),
        .O(\ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_3_n_0 ));
  LUT1 #(
    .INIT(2'h1)) 
    \ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_30 
       (.I0(Q[11]),
        .O(p_0_in__0[11]));
  LUT1 #(
    .INIT(2'h1)) 
    \ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_31 
       (.I0(Q[10]),
        .O(p_0_in__0[10]));
  LUT1 #(
    .INIT(2'h1)) 
    \ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_32 
       (.I0(Q[9]),
        .O(p_0_in__0[9]));
  (* ADDER_THRESHOLD = "35" *) 
  CARRY8 \ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_4 
       (.CI(\ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_6_n_0 ),
        .CI_TOP(1'b0),
        .CO({\NLW_ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_4_CO_UNCONNECTED [7:6],\ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_4_n_2 ,\ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_4_n_3 ,\ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_4_n_4 ,\ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_4_n_5 ,\ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_4_n_6 ,\ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_4_n_7 }),
        .DI({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .O({\NLW_ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_4_O_UNCONNECTED [7],uain0[31:25]}),
        .S({1'b0,p_0_in__0[30],\ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_9_n_0 ,\ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_10_n_0 ,\ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_11_n_0 ,\ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_12_n_0 ,\ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_13_n_0 ,\ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_14_n_0 }));
  LUT6 #(
    .INIT(64'hFFFFFFFFFFBBFCB8)) 
    \ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_5 
       (.I0(uain0[16]),
        .I1(Q[23]),
        .I2(Q[16]),
        .I3(uain0[17]),
        .I4(Q[17]),
        .I5(\ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_16_n_0 ),
        .O(\ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_5_n_0 ));
  (* ADDER_THRESHOLD = "35" *) 
  CARRY8 \ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_6 
       (.CI(\ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_15_n_0 ),
        .CI_TOP(1'b0),
        .CO({\ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_6_n_0 ,\ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_6_n_1 ,\ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_6_n_2 ,\ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_6_n_3 ,\ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_6_n_4 ,\ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_6_n_5 ,\ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_6_n_6 ,\ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_6_n_7 }),
        .DI({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .O(uain0[24:17]),
        .S({\ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_17_n_0 ,\ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_18_n_0 ,p_0_in__0[22:17]}));
  (* SOFT_HLUTNM = "soft_lutpair74" *) 
  LUT5 #(
    .INIT(32'hFFFACCFA)) 
    \ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_7 
       (.I0(Q[21]),
        .I1(uain0[21]),
        .I2(Q[20]),
        .I3(Q[23]),
        .I4(uain0[20]),
        .O(\ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_7_n_0 ));
  LUT1 #(
    .INIT(2'h1)) 
    \ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_8 
       (.I0(Q[23]),
        .O(p_0_in__0[30]));
  LUT1 #(
    .INIT(2'h1)) 
    \ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_9 
       (.I0(Q[23]),
        .O(\ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_9_n_0 ));
  FDRE \ds_reg_reg_reg[2][0]_U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_1 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\ds_reg_reg_reg[1][0]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_n_0 ),
        .Q(\ds_reg_reg_reg[2][0]_U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_1_n_0 ),
        .R(1'b0));
  FDRE \ds_reg_reg_reg[2][1]_U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_1 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\ds_reg_reg_reg[1][1]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_n_0 ),
        .Q(\ds_reg_reg_reg[2][1]_U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_1_n_0 ),
        .R(1'b0));
  FDRE \ds_reg_reg_reg[2][2]_U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_1 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\ds_reg_reg_reg[1][2]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_n_0 ),
        .Q(\ds_reg_reg_reg[2][2]_U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_1_n_0 ),
        .R(1'b0));
  FDRE \ds_reg_reg_reg[2][3]_U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_1 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\ds_reg_reg_reg[1][3]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_n_0 ),
        .Q(\ds_reg_reg_reg[2][3]_U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_1_n_0 ),
        .R(1'b0));
  FDRE \ds_reg_reg_reg[3][0] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(ds_reg_reg_reg_gate__2_n_0),
        .Q(\ds_reg_reg_reg[3]_0 [0]),
        .R(RSTP));
  FDRE \ds_reg_reg_reg[3][1] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(ds_reg_reg_reg_gate__1_n_0),
        .Q(\ds_reg_reg_reg[3]_0 [1]),
        .R(RSTP));
  FDRE \ds_reg_reg_reg[3][2] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(ds_reg_reg_reg_gate__0_n_0),
        .Q(\ds_reg_reg_reg[3]_0 [2]),
        .R(RSTP));
  FDRE \ds_reg_reg_reg[3][3] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(ds_reg_reg_reg_gate_n_0),
        .Q(\ds_reg_reg_reg[3]_0 [3]),
        .R(RSTP));
  (* SOFT_HLUTNM = "soft_lutpair101" *) 
  LUT2 #(
    .INIT(4'h8)) 
    ds_reg_reg_reg_gate
       (.I0(\ds_reg_reg_reg[2][3]_U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_1_n_0 ),
        .I1(onemoreshift_reg_reg_reg_r_1_n_0),
        .O(ds_reg_reg_reg_gate_n_0));
  (* SOFT_HLUTNM = "soft_lutpair101" *) 
  LUT2 #(
    .INIT(4'h8)) 
    ds_reg_reg_reg_gate__0
       (.I0(\ds_reg_reg_reg[2][2]_U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_1_n_0 ),
        .I1(onemoreshift_reg_reg_reg_r_1_n_0),
        .O(ds_reg_reg_reg_gate__0_n_0));
  (* SOFT_HLUTNM = "soft_lutpair102" *) 
  LUT2 #(
    .INIT(4'h8)) 
    ds_reg_reg_reg_gate__1
       (.I0(\ds_reg_reg_reg[2][1]_U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_1_n_0 ),
        .I1(onemoreshift_reg_reg_reg_r_1_n_0),
        .O(ds_reg_reg_reg_gate__1_n_0));
  (* SOFT_HLUTNM = "soft_lutpair102" *) 
  LUT2 #(
    .INIT(4'h8)) 
    ds_reg_reg_reg_gate__2
       (.I0(\ds_reg_reg_reg[2][0]_U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_1_n_0 ),
        .I1(onemoreshift_reg_reg_reg_r_1_n_0),
        .O(ds_reg_reg_reg_gate__2_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    \inzero_reg_reg[0]_i_1 
       (.I0(mstwobit),
        .O(p_1_out));
  FDRE \inzero_reg_reg_reg[0] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(p_1_out),
        .Q(inzero_reg_reg[0]),
        .R(RSTP));
  FDRE \inzero_reg_reg_reg[1] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(inzero_reg_reg[0]),
        .Q(inzero_reg_reg[1]),
        .R(RSTP));
  FDRE \inzero_reg_reg_reg[2] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(inzero_reg_reg[1]),
        .Q(\inzero_reg_reg_reg_n_0_[2] ),
        .R(RSTP));
  (* srl_bus_name = "\U0/u_IncreEncoder_V24_ip_dut_inst/u_IncreEncoder_V24_ip_src_IncreEncoder_V24/u_HDL_Reciprocal/onemoreshift_reg_reg_reg " *) 
  (* srl_name = "\U0/u_IncreEncoder_V24_ip_dut_inst/u_IncreEncoder_V24_ip_src_IncreEncoder_V24/u_HDL_Reciprocal/onemoreshift_reg_reg_reg[1]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0 " *) 
  SRL16E \onemoreshift_reg_reg_reg[1]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0 
       (.A0(1'b1),
        .A1(1'b0),
        .A2(1'b0),
        .A3(1'b0),
        .CE(CEP),
        .CLK(IPCORE_CLK),
        .D(p_2_out),
        .Q(\onemoreshift_reg_reg_reg[1]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair69" *) 
  LUT1 #(
    .INIT(2'h1)) 
    \onemoreshift_reg_reg_reg[1]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_i_1 
       (.I0(p_0_in),
        .O(p_2_out));
  FDRE \onemoreshift_reg_reg_reg[2]_U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_1 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\onemoreshift_reg_reg_reg[1]_srl2___U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_0_n_0 ),
        .Q(\onemoreshift_reg_reg_reg[2]_U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_1_n_0 ),
        .R(1'b0));
  FDRE \onemoreshift_reg_reg_reg[3] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(onemoreshift_reg_reg_reg_gate_n_0),
        .Q(\onemoreshift_reg_reg_reg_n_0_[3] ),
        .R(RSTP));
  (* SOFT_HLUTNM = "soft_lutpair100" *) 
  LUT2 #(
    .INIT(4'h8)) 
    onemoreshift_reg_reg_reg_gate
       (.I0(\onemoreshift_reg_reg_reg[2]_U0_u_IncreEncoder_V24_ip_dut_inst_u_IncreEncoder_V24_ip_src_IncreEncoder_V24_u_HDL_Reciprocal_onemoreshift_reg_reg_reg_r_1_n_0 ),
        .I1(onemoreshift_reg_reg_reg_r_1_n_0),
        .O(onemoreshift_reg_reg_reg_gate_n_0));
  FDRE onemoreshift_reg_reg_reg_r
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(1'b1),
        .Q(onemoreshift_reg_reg_reg_r_n_0),
        .R(RSTP));
  FDRE onemoreshift_reg_reg_reg_r_0
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(onemoreshift_reg_reg_reg_r_n_0),
        .Q(onemoreshift_reg_reg_reg_r_0_n_0),
        .R(RSTP));
  FDRE onemoreshift_reg_reg_reg_r_1
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(onemoreshift_reg_reg_reg_r_0_n_0),
        .Q(onemoreshift_reg_reg_reg_r_1_n_0),
        .R(RSTP));
  LUT1 #(
    .INIT(2'h1)) 
    sel_i_1
       (.I0(sel),
        .O(sel_i_1_n_0));
  FDRE sel_reg
       (.C(IPCORE_CLK),
        .CE(write_axi_enable),
        .D(sel_i_1_n_0),
        .Q(sel),
        .R(RSTP));
  LUT1 #(
    .INIT(2'h1)) 
    subtractor_sub_temp_carry__0_i_1
       (.I0(u_core_stage3_inst_n_15),
        .O(subtractor_sub_temp_carry__0_i_1_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    subtractor_sub_temp_carry__0_i_1__0
       (.I0(u_core_stage2_inst_n_15),
        .O(subtractor_sub_temp_carry__0_i_1__0_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    subtractor_sub_temp_carry__0_i_1__1
       (.I0(delayout[16]),
        .O(subtractor_sub_temp_carry__0_i_1__1_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    subtractor_sub_temp_carry__0_i_2
       (.I0(u_core_stage3_inst_n_16),
        .O(subtractor_sub_temp_carry__0_i_2_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    subtractor_sub_temp_carry__0_i_2__0
       (.I0(u_core_stage2_inst_n_16),
        .O(subtractor_sub_temp_carry__0_i_2__0_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    subtractor_sub_temp_carry__0_i_2__1
       (.I0(delayout[15]),
        .O(subtractor_sub_temp_carry__0_i_2__1_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    subtractor_sub_temp_carry__0_i_3
       (.I0(u_core_stage3_inst_n_17),
        .O(subtractor_sub_temp_carry__0_i_3_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    subtractor_sub_temp_carry__0_i_3__0
       (.I0(u_core_stage2_inst_n_17),
        .O(subtractor_sub_temp_carry__0_i_3__0_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    subtractor_sub_temp_carry__0_i_3__1
       (.I0(delayout[14]),
        .O(subtractor_sub_temp_carry__0_i_3__1_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    subtractor_sub_temp_carry__0_i_4
       (.I0(u_core_stage3_inst_n_18),
        .O(subtractor_sub_temp_carry__0_i_4_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    subtractor_sub_temp_carry__0_i_4__0
       (.I0(u_core_stage2_inst_n_18),
        .O(subtractor_sub_temp_carry__0_i_4__0_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    subtractor_sub_temp_carry__0_i_4__1
       (.I0(delayout[13]),
        .O(subtractor_sub_temp_carry__0_i_4__1_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    subtractor_sub_temp_carry__0_i_5
       (.I0(u_core_stage3_inst_n_19),
        .O(subtractor_sub_temp_carry__0_i_5_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    subtractor_sub_temp_carry__0_i_5__0
       (.I0(u_core_stage2_inst_n_19),
        .O(subtractor_sub_temp_carry__0_i_5__0_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    subtractor_sub_temp_carry__0_i_5__1
       (.I0(delayout[12]),
        .O(subtractor_sub_temp_carry__0_i_5__1_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    subtractor_sub_temp_carry__0_i_6
       (.I0(u_core_stage3_inst_n_20),
        .O(subtractor_sub_temp_carry__0_i_6_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    subtractor_sub_temp_carry__0_i_6__0
       (.I0(u_core_stage2_inst_n_20),
        .O(subtractor_sub_temp_carry__0_i_6__0_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    subtractor_sub_temp_carry__0_i_6__1
       (.I0(delayout[11]),
        .O(subtractor_sub_temp_carry__0_i_6__1_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    subtractor_sub_temp_carry__0_i_7
       (.I0(u_core_stage3_inst_n_21),
        .O(subtractor_sub_temp_carry__0_i_7_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    subtractor_sub_temp_carry__0_i_7__0
       (.I0(u_core_stage2_inst_n_21),
        .O(subtractor_sub_temp_carry__0_i_7__0_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    subtractor_sub_temp_carry__0_i_7__1
       (.I0(delayout[10]),
        .O(subtractor_sub_temp_carry__0_i_7__1_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    subtractor_sub_temp_carry__0_i_8
       (.I0(u_core_stage3_inst_n_22),
        .O(subtractor_sub_temp_carry__0_i_8_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    subtractor_sub_temp_carry__0_i_8__0
       (.I0(u_core_stage2_inst_n_22),
        .O(subtractor_sub_temp_carry__0_i_8__0_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    subtractor_sub_temp_carry__0_i_8__1
       (.I0(delayout[9]),
        .O(subtractor_sub_temp_carry__0_i_8__1_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    subtractor_sub_temp_carry__1_i_1
       (.I0(u_core_stage3_inst_n_7),
        .O(subtractor_sub_temp_carry__1_i_1_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    subtractor_sub_temp_carry__1_i_1__0
       (.I0(u_core_stage2_inst_n_7),
        .O(subtractor_sub_temp_carry__1_i_1__0_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    subtractor_sub_temp_carry__1_i_1__1
       (.I0(delayout[24]),
        .O(subtractor_sub_temp_carry__1_i_1__1_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    subtractor_sub_temp_carry__1_i_2
       (.I0(u_core_stage3_inst_n_8),
        .O(subtractor_sub_temp_carry__1_i_2_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    subtractor_sub_temp_carry__1_i_2__0
       (.I0(u_core_stage2_inst_n_8),
        .O(subtractor_sub_temp_carry__1_i_2__0_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    subtractor_sub_temp_carry__1_i_2__1
       (.I0(delayout[23]),
        .O(subtractor_sub_temp_carry__1_i_2__1_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    subtractor_sub_temp_carry__1_i_3
       (.I0(u_core_stage3_inst_n_9),
        .O(subtractor_sub_temp_carry__1_i_3_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    subtractor_sub_temp_carry__1_i_3__0
       (.I0(u_core_stage2_inst_n_9),
        .O(subtractor_sub_temp_carry__1_i_3__0_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    subtractor_sub_temp_carry__1_i_3__1
       (.I0(delayout[22]),
        .O(subtractor_sub_temp_carry__1_i_3__1_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    subtractor_sub_temp_carry__1_i_4
       (.I0(u_core_stage3_inst_n_10),
        .O(subtractor_sub_temp_carry__1_i_4_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    subtractor_sub_temp_carry__1_i_4__0
       (.I0(u_core_stage2_inst_n_10),
        .O(subtractor_sub_temp_carry__1_i_4__0_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    subtractor_sub_temp_carry__1_i_4__1
       (.I0(delayout[21]),
        .O(subtractor_sub_temp_carry__1_i_4__1_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    subtractor_sub_temp_carry__1_i_5
       (.I0(u_core_stage3_inst_n_11),
        .O(subtractor_sub_temp_carry__1_i_5_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    subtractor_sub_temp_carry__1_i_5__0
       (.I0(u_core_stage2_inst_n_11),
        .O(subtractor_sub_temp_carry__1_i_5__0_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    subtractor_sub_temp_carry__1_i_5__1
       (.I0(delayout[20]),
        .O(subtractor_sub_temp_carry__1_i_5__1_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    subtractor_sub_temp_carry__1_i_6
       (.I0(u_core_stage3_inst_n_12),
        .O(subtractor_sub_temp_carry__1_i_6_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    subtractor_sub_temp_carry__1_i_6__0
       (.I0(u_core_stage2_inst_n_12),
        .O(subtractor_sub_temp_carry__1_i_6__0_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    subtractor_sub_temp_carry__1_i_6__1
       (.I0(delayout[19]),
        .O(subtractor_sub_temp_carry__1_i_6__1_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    subtractor_sub_temp_carry__1_i_7
       (.I0(u_core_stage3_inst_n_13),
        .O(subtractor_sub_temp_carry__1_i_7_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    subtractor_sub_temp_carry__1_i_7__0
       (.I0(u_core_stage2_inst_n_13),
        .O(subtractor_sub_temp_carry__1_i_7__0_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    subtractor_sub_temp_carry__1_i_7__1
       (.I0(delayout[18]),
        .O(subtractor_sub_temp_carry__1_i_7__1_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    subtractor_sub_temp_carry__1_i_8
       (.I0(u_core_stage3_inst_n_14),
        .O(subtractor_sub_temp_carry__1_i_8_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    subtractor_sub_temp_carry__1_i_8__0
       (.I0(u_core_stage2_inst_n_14),
        .O(subtractor_sub_temp_carry__1_i_8__0_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    subtractor_sub_temp_carry__1_i_8__1
       (.I0(delayout[17]),
        .O(subtractor_sub_temp_carry__1_i_8__1_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    subtractor_sub_temp_carry__2_i_1
       (.I0(u_core_stage3_inst_n_0),
        .O(subtractor_sub_temp_carry__2_i_1_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    subtractor_sub_temp_carry__2_i_1__0
       (.I0(u_core_stage2_inst_n_0),
        .O(subtractor_sub_temp_carry__2_i_1__0_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    subtractor_sub_temp_carry__2_i_1__1
       (.I0(delayout[31]),
        .O(subtractor_sub_temp_carry__2_i_1__1_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    subtractor_sub_temp_carry__2_i_2
       (.I0(u_core_stage3_inst_n_1),
        .O(subtractor_sub_temp_carry__2_i_2_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    subtractor_sub_temp_carry__2_i_2__0
       (.I0(u_core_stage2_inst_n_1),
        .O(subtractor_sub_temp_carry__2_i_2__0_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    subtractor_sub_temp_carry__2_i_2__1
       (.I0(delayout[30]),
        .O(subtractor_sub_temp_carry__2_i_2__1_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    subtractor_sub_temp_carry__2_i_3
       (.I0(u_core_stage3_inst_n_2),
        .O(subtractor_sub_temp_carry__2_i_3_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    subtractor_sub_temp_carry__2_i_3__0
       (.I0(u_core_stage2_inst_n_2),
        .O(subtractor_sub_temp_carry__2_i_3__0_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    subtractor_sub_temp_carry__2_i_3__1
       (.I0(delayout[29]),
        .O(subtractor_sub_temp_carry__2_i_3__1_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    subtractor_sub_temp_carry__2_i_4
       (.I0(u_core_stage3_inst_n_3),
        .O(subtractor_sub_temp_carry__2_i_4_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    subtractor_sub_temp_carry__2_i_4__0
       (.I0(u_core_stage2_inst_n_3),
        .O(subtractor_sub_temp_carry__2_i_4__0_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    subtractor_sub_temp_carry__2_i_4__1
       (.I0(delayout[28]),
        .O(subtractor_sub_temp_carry__2_i_4__1_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    subtractor_sub_temp_carry__2_i_5
       (.I0(u_core_stage3_inst_n_4),
        .O(subtractor_sub_temp_carry__2_i_5_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    subtractor_sub_temp_carry__2_i_5__0
       (.I0(u_core_stage2_inst_n_4),
        .O(subtractor_sub_temp_carry__2_i_5__0_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    subtractor_sub_temp_carry__2_i_5__1
       (.I0(delayout[27]),
        .O(subtractor_sub_temp_carry__2_i_5__1_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    subtractor_sub_temp_carry__2_i_6
       (.I0(u_core_stage3_inst_n_5),
        .O(subtractor_sub_temp_carry__2_i_6_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    subtractor_sub_temp_carry__2_i_6__0
       (.I0(u_core_stage2_inst_n_5),
        .O(subtractor_sub_temp_carry__2_i_6__0_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    subtractor_sub_temp_carry__2_i_6__1
       (.I0(delayout[26]),
        .O(subtractor_sub_temp_carry__2_i_6__1_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    subtractor_sub_temp_carry__2_i_7
       (.I0(u_core_stage3_inst_n_6),
        .O(subtractor_sub_temp_carry__2_i_7_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    subtractor_sub_temp_carry__2_i_7__0
       (.I0(u_core_stage2_inst_n_6),
        .O(subtractor_sub_temp_carry__2_i_7__0_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    subtractor_sub_temp_carry__2_i_7__1
       (.I0(delayout[25]),
        .O(subtractor_sub_temp_carry__2_i_7__1_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    subtractor_sub_temp_carry_i_1
       (.I0(u_core_stage3_inst_n_31),
        .O(subtractor_sub_temp_carry_i_1_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    subtractor_sub_temp_carry_i_1__0
       (.I0(u_core_stage2_inst_n_31),
        .O(subtractor_sub_temp_carry_i_1__0_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    subtractor_sub_temp_carry_i_1__1
       (.I0(delayout[0]),
        .O(subtractor_sub_temp_carry_i_1__1_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    subtractor_sub_temp_carry_i_2
       (.I0(u_core_stage3_inst_n_23),
        .O(subtractor_sub_temp_carry_i_2_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    subtractor_sub_temp_carry_i_2__0
       (.I0(u_core_stage2_inst_n_23),
        .O(subtractor_sub_temp_carry_i_2__0_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    subtractor_sub_temp_carry_i_2__1
       (.I0(delayout[8]),
        .O(subtractor_sub_temp_carry_i_2__1_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    subtractor_sub_temp_carry_i_3
       (.I0(u_core_stage3_inst_n_24),
        .O(subtractor_sub_temp_carry_i_3_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    subtractor_sub_temp_carry_i_3__0
       (.I0(u_core_stage2_inst_n_24),
        .O(subtractor_sub_temp_carry_i_3__0_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    subtractor_sub_temp_carry_i_3__1
       (.I0(delayout[7]),
        .O(subtractor_sub_temp_carry_i_3__1_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    subtractor_sub_temp_carry_i_4
       (.I0(u_core_stage3_inst_n_25),
        .O(subtractor_sub_temp_carry_i_4_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    subtractor_sub_temp_carry_i_4__0
       (.I0(u_core_stage2_inst_n_25),
        .O(subtractor_sub_temp_carry_i_4__0_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    subtractor_sub_temp_carry_i_4__1
       (.I0(delayout[6]),
        .O(subtractor_sub_temp_carry_i_4__1_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    subtractor_sub_temp_carry_i_5
       (.I0(u_core_stage3_inst_n_26),
        .O(subtractor_sub_temp_carry_i_5_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    subtractor_sub_temp_carry_i_5__0
       (.I0(u_core_stage2_inst_n_26),
        .O(subtractor_sub_temp_carry_i_5__0_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    subtractor_sub_temp_carry_i_5__1
       (.I0(delayout[5]),
        .O(subtractor_sub_temp_carry_i_5__1_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    subtractor_sub_temp_carry_i_6
       (.I0(u_core_stage3_inst_n_27),
        .O(subtractor_sub_temp_carry_i_6_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    subtractor_sub_temp_carry_i_6__0
       (.I0(u_core_stage2_inst_n_27),
        .O(subtractor_sub_temp_carry_i_6__0_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    subtractor_sub_temp_carry_i_6__1
       (.I0(delayout[4]),
        .O(subtractor_sub_temp_carry_i_6__1_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    subtractor_sub_temp_carry_i_7
       (.I0(u_core_stage3_inst_n_28),
        .O(subtractor_sub_temp_carry_i_7_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    subtractor_sub_temp_carry_i_7__0
       (.I0(u_core_stage2_inst_n_28),
        .O(subtractor_sub_temp_carry_i_7__0_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    subtractor_sub_temp_carry_i_7__1
       (.I0(delayout[3]),
        .O(subtractor_sub_temp_carry_i_7__1_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    subtractor_sub_temp_carry_i_8
       (.I0(u_core_stage3_inst_n_29),
        .O(subtractor_sub_temp_carry_i_8_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    subtractor_sub_temp_carry_i_8__0
       (.I0(u_core_stage2_inst_n_29),
        .O(subtractor_sub_temp_carry_i_8__0_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    subtractor_sub_temp_carry_i_8__1
       (.I0(delayout[2]),
        .O(subtractor_sub_temp_carry_i_8__1_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    subtractor_sub_temp_carry_i_9
       (.I0(u_core_stage3_inst_n_30),
        .O(subtractor_sub_temp_carry_i_9_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    subtractor_sub_temp_carry_i_9__0
       (.I0(u_core_stage2_inst_n_30),
        .O(subtractor_sub_temp_carry_i_9__0_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    subtractor_sub_temp_carry_i_9__1
       (.I0(delayout[1]),
        .O(subtractor_sub_temp_carry_i_9__1_n_0));
  zusys_IncreEncoder_V24_ip_0_0_IncreEncoder_V24_ip_src_HDL_Reciprocal_core u_core_stage1_inst
       (.CEP(CEP),
        .D(muxout),
        .DI(subtractor_sub_temp_carry__2_i_1__1_n_0),
        .IPCORE_CLK(IPCORE_CLK),
        .Q(delayout),
        .RSTP(RSTP),
        .S({subtractor_sub_temp_carry_i_2__1_n_0,subtractor_sub_temp_carry_i_3__1_n_0,subtractor_sub_temp_carry_i_4__1_n_0,subtractor_sub_temp_carry_i_5__1_n_0,subtractor_sub_temp_carry_i_6__1_n_0,subtractor_sub_temp_carry_i_7__1_n_0,subtractor_sub_temp_carry_i_8__1_n_0,subtractor_sub_temp_carry_i_9__1_n_0}),
        .\aout_tmp_reg[31]_0 (aout_tmp),
        .\aout_tmp_reg[31]_1 ({mstwobit,anorm_p}),
        .\delayout_reg[16]_0 ({subtractor_sub_temp_carry__0_i_1__1_n_0,subtractor_sub_temp_carry__0_i_2__1_n_0,subtractor_sub_temp_carry__0_i_3__1_n_0,subtractor_sub_temp_carry__0_i_4__1_n_0,subtractor_sub_temp_carry__0_i_5__1_n_0,subtractor_sub_temp_carry__0_i_6__1_n_0,subtractor_sub_temp_carry__0_i_7__1_n_0,subtractor_sub_temp_carry__0_i_8__1_n_0}),
        .\delayout_reg[24]_0 ({subtractor_sub_temp_carry__1_i_1__1_n_0,subtractor_sub_temp_carry__1_i_2__1_n_0,subtractor_sub_temp_carry__1_i_3__1_n_0,subtractor_sub_temp_carry__1_i_4__1_n_0,subtractor_sub_temp_carry__1_i_5__1_n_0,subtractor_sub_temp_carry__1_i_6__1_n_0,subtractor_sub_temp_carry__1_i_7__1_n_0,subtractor_sub_temp_carry__1_i_8__1_n_0}),
        .\delayout_reg[31]_0 ({subtractor_sub_temp_carry__2_i_2__1_n_0,subtractor_sub_temp_carry__2_i_3__1_n_0,subtractor_sub_temp_carry__2_i_4__1_n_0,subtractor_sub_temp_carry__2_i_5__1_n_0,subtractor_sub_temp_carry__2_i_6__1_n_0,subtractor_sub_temp_carry__2_i_7__1_n_0}),
        .\delayout_reg[8]_0 (subtractor_sub_temp_carry_i_1__1_n_0),
        .sel(sel),
        .write_axi_enable(write_axi_enable));
  zusys_IncreEncoder_V24_ip_0_0_IncreEncoder_V24_ip_src_HDL_Reciprocal_core_0 u_core_stage2_inst
       (.CEP(CEP),
        .D(muxout),
        .DI(subtractor_sub_temp_carry__2_i_1__0_n_0),
        .IPCORE_CLK(IPCORE_CLK),
        .Q({u_core_stage2_inst_n_0,u_core_stage2_inst_n_1,u_core_stage2_inst_n_2,u_core_stage2_inst_n_3,u_core_stage2_inst_n_4,u_core_stage2_inst_n_5,u_core_stage2_inst_n_6,u_core_stage2_inst_n_7,u_core_stage2_inst_n_8,u_core_stage2_inst_n_9,u_core_stage2_inst_n_10,u_core_stage2_inst_n_11,u_core_stage2_inst_n_12,u_core_stage2_inst_n_13,u_core_stage2_inst_n_14,u_core_stage2_inst_n_15,u_core_stage2_inst_n_16,u_core_stage2_inst_n_17,u_core_stage2_inst_n_18,u_core_stage2_inst_n_19,u_core_stage2_inst_n_20,u_core_stage2_inst_n_21,u_core_stage2_inst_n_22,u_core_stage2_inst_n_23,u_core_stage2_inst_n_24,u_core_stage2_inst_n_25,u_core_stage2_inst_n_26,u_core_stage2_inst_n_27,u_core_stage2_inst_n_28,u_core_stage2_inst_n_29,u_core_stage2_inst_n_30,u_core_stage2_inst_n_31}),
        .RSTP(RSTP),
        .S({subtractor_sub_temp_carry_i_2__0_n_0,subtractor_sub_temp_carry_i_3__0_n_0,subtractor_sub_temp_carry_i_4__0_n_0,subtractor_sub_temp_carry_i_5__0_n_0,subtractor_sub_temp_carry_i_6__0_n_0,subtractor_sub_temp_carry_i_7__0_n_0,subtractor_sub_temp_carry_i_8__0_n_0,subtractor_sub_temp_carry_i_9__0_n_0}),
        .\aout_tmp_reg[31]_0 ({u_core_stage2_inst_n_32,u_core_stage2_inst_n_33,u_core_stage2_inst_n_34,u_core_stage2_inst_n_35,u_core_stage2_inst_n_36,u_core_stage2_inst_n_37,u_core_stage2_inst_n_38,u_core_stage2_inst_n_39,u_core_stage2_inst_n_40,u_core_stage2_inst_n_41,u_core_stage2_inst_n_42,u_core_stage2_inst_n_43,u_core_stage2_inst_n_44,u_core_stage2_inst_n_45,u_core_stage2_inst_n_46,u_core_stage2_inst_n_47,u_core_stage2_inst_n_48,u_core_stage2_inst_n_49,u_core_stage2_inst_n_50,u_core_stage2_inst_n_51,u_core_stage2_inst_n_52,u_core_stage2_inst_n_53,u_core_stage2_inst_n_54,u_core_stage2_inst_n_55,u_core_stage2_inst_n_56,u_core_stage2_inst_n_57,u_core_stage2_inst_n_58,u_core_stage2_inst_n_59,u_core_stage2_inst_n_60,u_core_stage2_inst_n_61}),
        .\aout_tmp_reg[31]_1 (aout_tmp),
        .mul1_mul_temp__0_i_15_0({subtractor_sub_temp_carry__1_i_1__0_n_0,subtractor_sub_temp_carry__1_i_2__0_n_0,subtractor_sub_temp_carry__1_i_3__0_n_0,subtractor_sub_temp_carry__1_i_4__0_n_0,subtractor_sub_temp_carry__1_i_5__0_n_0,subtractor_sub_temp_carry__1_i_6__0_n_0,subtractor_sub_temp_carry__1_i_7__0_n_0,subtractor_sub_temp_carry__1_i_8__0_n_0}),
        .mul1_mul_temp__0_i_7_0({subtractor_sub_temp_carry__2_i_2__0_n_0,subtractor_sub_temp_carry__2_i_3__0_n_0,subtractor_sub_temp_carry__2_i_4__0_n_0,subtractor_sub_temp_carry__2_i_5__0_n_0,subtractor_sub_temp_carry__2_i_6__0_n_0,subtractor_sub_temp_carry__2_i_7__0_n_0}),
        .mul1_mul_temp_carry__4_0({u_core_stage2_inst_n_62,u_core_stage2_inst_n_63,u_core_stage2_inst_n_64,u_core_stage2_inst_n_65,u_core_stage2_inst_n_66,u_core_stage2_inst_n_67,u_core_stage2_inst_n_68,u_core_stage2_inst_n_69,u_core_stage2_inst_n_70,u_core_stage2_inst_n_71,u_core_stage2_inst_n_72,u_core_stage2_inst_n_73,u_core_stage2_inst_n_74,u_core_stage2_inst_n_75,u_core_stage2_inst_n_76,u_core_stage2_inst_n_77,u_core_stage2_inst_n_78,u_core_stage2_inst_n_79,u_core_stage2_inst_n_80,u_core_stage2_inst_n_81,u_core_stage2_inst_n_82,u_core_stage2_inst_n_83,u_core_stage2_inst_n_84,u_core_stage2_inst_n_85,u_core_stage2_inst_n_86,u_core_stage2_inst_n_87,u_core_stage2_inst_n_88,u_core_stage2_inst_n_89,u_core_stage2_inst_n_90,u_core_stage2_inst_n_91,u_core_stage2_inst_n_92,u_core_stage2_inst_n_93}),
        .mul1_mul_temp_i_16_0(subtractor_sub_temp_carry_i_1__0_n_0),
        .mul1_mul_temp_i_8_0({subtractor_sub_temp_carry__0_i_1__0_n_0,subtractor_sub_temp_carry__0_i_2__0_n_0,subtractor_sub_temp_carry__0_i_3__0_n_0,subtractor_sub_temp_carry__0_i_4__0_n_0,subtractor_sub_temp_carry__0_i_5__0_n_0,subtractor_sub_temp_carry__0_i_6__0_n_0,subtractor_sub_temp_carry__0_i_7__0_n_0,subtractor_sub_temp_carry__0_i_8__0_n_0}),
        .sel(sel),
        .write_axi_enable(write_axi_enable));
  zusys_IncreEncoder_V24_ip_0_0_IncreEncoder_V24_ip_src_HDL_Reciprocal_core_1 u_core_stage3_inst
       (.A(A),
        .CEP(CEP),
        .DI(subtractor_sub_temp_carry__2_i_1_n_0),
        .DSP_ALU_INST({u_core_stage2_inst_n_62,u_core_stage2_inst_n_63,u_core_stage2_inst_n_64,u_core_stage2_inst_n_65,u_core_stage2_inst_n_66,u_core_stage2_inst_n_67,u_core_stage2_inst_n_68,u_core_stage2_inst_n_69,u_core_stage2_inst_n_70,u_core_stage2_inst_n_71,u_core_stage2_inst_n_72,u_core_stage2_inst_n_73,u_core_stage2_inst_n_74,u_core_stage2_inst_n_75,u_core_stage2_inst_n_76,u_core_stage2_inst_n_77,u_core_stage2_inst_n_78,u_core_stage2_inst_n_79,u_core_stage2_inst_n_80,u_core_stage2_inst_n_81,u_core_stage2_inst_n_82,u_core_stage2_inst_n_83,u_core_stage2_inst_n_84,u_core_stage2_inst_n_85,u_core_stage2_inst_n_86,u_core_stage2_inst_n_87,u_core_stage2_inst_n_88,u_core_stage2_inst_n_89,u_core_stage2_inst_n_90,u_core_stage2_inst_n_91,u_core_stage2_inst_n_92,u_core_stage2_inst_n_93}),
        .DSP_A_B_DATA_INST({u_core_stage2_inst_n_32,u_core_stage2_inst_n_33,u_core_stage2_inst_n_34,u_core_stage2_inst_n_35,u_core_stage2_inst_n_36,u_core_stage2_inst_n_37,u_core_stage2_inst_n_38,u_core_stage2_inst_n_39,u_core_stage2_inst_n_40,u_core_stage2_inst_n_41,u_core_stage2_inst_n_42,u_core_stage2_inst_n_43,u_core_stage2_inst_n_44,u_core_stage2_inst_n_45,u_core_stage2_inst_n_46,u_core_stage2_inst_n_47,u_core_stage2_inst_n_48,u_core_stage2_inst_n_49,u_core_stage2_inst_n_50,u_core_stage2_inst_n_51,u_core_stage2_inst_n_52,u_core_stage2_inst_n_53,u_core_stage2_inst_n_54,u_core_stage2_inst_n_55,u_core_stage2_inst_n_56,u_core_stage2_inst_n_57,u_core_stage2_inst_n_58,u_core_stage2_inst_n_59,u_core_stage2_inst_n_60,u_core_stage2_inst_n_61}),
        .DSP_A_B_DATA_INST_0(\inzero_reg_reg_reg_n_0_[2] ),
        .DSP_A_B_DATA_INST_1(\changesign_reg_reg_reg_n_0_[3] ),
        .Div_i1_mul_temp_i_50_0(\onemoreshift_reg_reg_reg_n_0_[3] ),
        .IPCORE_CLK(IPCORE_CLK),
        .Q({u_core_stage3_inst_n_0,u_core_stage3_inst_n_1,u_core_stage3_inst_n_2,u_core_stage3_inst_n_3,u_core_stage3_inst_n_4,u_core_stage3_inst_n_5,u_core_stage3_inst_n_6,u_core_stage3_inst_n_7,u_core_stage3_inst_n_8,u_core_stage3_inst_n_9,u_core_stage3_inst_n_10,u_core_stage3_inst_n_11,u_core_stage3_inst_n_12,u_core_stage3_inst_n_13,u_core_stage3_inst_n_14,u_core_stage3_inst_n_15,u_core_stage3_inst_n_16,u_core_stage3_inst_n_17,u_core_stage3_inst_n_18,u_core_stage3_inst_n_19,u_core_stage3_inst_n_20,u_core_stage3_inst_n_21,u_core_stage3_inst_n_22,u_core_stage3_inst_n_23,u_core_stage3_inst_n_24,u_core_stage3_inst_n_25,u_core_stage3_inst_n_26,u_core_stage3_inst_n_27,u_core_stage3_inst_n_28,u_core_stage3_inst_n_29,u_core_stage3_inst_n_30,u_core_stage3_inst_n_31}),
        .RSTP(RSTP),
        .S({subtractor_sub_temp_carry_i_2_n_0,subtractor_sub_temp_carry_i_3_n_0,subtractor_sub_temp_carry_i_4_n_0,subtractor_sub_temp_carry_i_5_n_0,subtractor_sub_temp_carry_i_6_n_0,subtractor_sub_temp_carry_i_7_n_0,subtractor_sub_temp_carry_i_8_n_0,subtractor_sub_temp_carry_i_9_n_0}),
        .\ds_reg_reg_reg[3]_0 (\ds_reg_reg_reg[3]_0 ),
        .mul1_mul_temp__0_i_15_0({subtractor_sub_temp_carry__1_i_1_n_0,subtractor_sub_temp_carry__1_i_2_n_0,subtractor_sub_temp_carry__1_i_3_n_0,subtractor_sub_temp_carry__1_i_4_n_0,subtractor_sub_temp_carry__1_i_5_n_0,subtractor_sub_temp_carry__1_i_6_n_0,subtractor_sub_temp_carry__1_i_7_n_0,subtractor_sub_temp_carry__1_i_8_n_0}),
        .mul1_mul_temp__0_i_7_0({subtractor_sub_temp_carry__2_i_2_n_0,subtractor_sub_temp_carry__2_i_3_n_0,subtractor_sub_temp_carry__2_i_4_n_0,subtractor_sub_temp_carry__2_i_5_n_0,subtractor_sub_temp_carry__2_i_6_n_0,subtractor_sub_temp_carry__2_i_7_n_0}),
        .mul1_mul_temp_i_16_0(subtractor_sub_temp_carry_i_1_n_0),
        .mul1_mul_temp_i_8_0({subtractor_sub_temp_carry__0_i_1_n_0,subtractor_sub_temp_carry__0_i_2_n_0,subtractor_sub_temp_carry__0_i_3_n_0,subtractor_sub_temp_carry__0_i_4_n_0,subtractor_sub_temp_carry__0_i_5_n_0,subtractor_sub_temp_carry__0_i_6_n_0,subtractor_sub_temp_carry__0_i_7_n_0,subtractor_sub_temp_carry__0_i_8_n_0}),
        .sel(sel),
        .write_axi_enable(write_axi_enable));
endmodule

(* ORIG_REF_NAME = "IncreEncoder_V24_ip_src_HDL_Reciprocal_core" *) 
module zusys_IncreEncoder_V24_ip_0_0_IncreEncoder_V24_ip_src_HDL_Reciprocal_core
   (Q,
    \aout_tmp_reg[31]_0 ,
    D,
    \delayout_reg[8]_0 ,
    S,
    \delayout_reg[16]_0 ,
    \delayout_reg[24]_0 ,
    DI,
    \delayout_reg[31]_0 ,
    RSTP,
    CEP,
    \aout_tmp_reg[31]_1 ,
    IPCORE_CLK,
    write_axi_enable,
    sel);
  output [31:0]Q;
  output [29:0]\aout_tmp_reg[31]_0 ;
  output [31:0]D;
  input \delayout_reg[8]_0 ;
  input [7:0]S;
  input [7:0]\delayout_reg[16]_0 ;
  input [7:0]\delayout_reg[24]_0 ;
  input [0:0]DI;
  input [5:0]\delayout_reg[31]_0 ;
  input RSTP;
  input CEP;
  input [29:0]\aout_tmp_reg[31]_1 ;
  input IPCORE_CLK;
  input write_axi_enable;
  input sel;

  wire CEP;
  wire [31:0]D;
  wire [0:0]DI;
  wire IPCORE_CLK;
  wire [31:0]Q;
  wire RSTP;
  wire [7:0]S;
  wire [29:0]\aout_tmp_reg[31]_0 ;
  wire [29:0]\aout_tmp_reg[31]_1 ;
  wire [7:0]\delayout_reg[16]_0 ;
  wire [7:0]\delayout_reg[24]_0 ;
  wire [5:0]\delayout_reg[31]_0 ;
  wire \delayout_reg[8]_0 ;
  wire sel;
  wire subtractor_sub_temp_carry__0_n_0;
  wire subtractor_sub_temp_carry__0_n_1;
  wire subtractor_sub_temp_carry__0_n_10;
  wire subtractor_sub_temp_carry__0_n_11;
  wire subtractor_sub_temp_carry__0_n_12;
  wire subtractor_sub_temp_carry__0_n_13;
  wire subtractor_sub_temp_carry__0_n_14;
  wire subtractor_sub_temp_carry__0_n_15;
  wire subtractor_sub_temp_carry__0_n_2;
  wire subtractor_sub_temp_carry__0_n_3;
  wire subtractor_sub_temp_carry__0_n_4;
  wire subtractor_sub_temp_carry__0_n_5;
  wire subtractor_sub_temp_carry__0_n_6;
  wire subtractor_sub_temp_carry__0_n_7;
  wire subtractor_sub_temp_carry__0_n_8;
  wire subtractor_sub_temp_carry__0_n_9;
  wire subtractor_sub_temp_carry__1_n_0;
  wire subtractor_sub_temp_carry__1_n_1;
  wire subtractor_sub_temp_carry__1_n_10;
  wire subtractor_sub_temp_carry__1_n_11;
  wire subtractor_sub_temp_carry__1_n_12;
  wire subtractor_sub_temp_carry__1_n_13;
  wire subtractor_sub_temp_carry__1_n_14;
  wire subtractor_sub_temp_carry__1_n_15;
  wire subtractor_sub_temp_carry__1_n_2;
  wire subtractor_sub_temp_carry__1_n_3;
  wire subtractor_sub_temp_carry__1_n_4;
  wire subtractor_sub_temp_carry__1_n_5;
  wire subtractor_sub_temp_carry__1_n_6;
  wire subtractor_sub_temp_carry__1_n_7;
  wire subtractor_sub_temp_carry__1_n_8;
  wire subtractor_sub_temp_carry__1_n_9;
  wire subtractor_sub_temp_carry__2_n_0;
  wire subtractor_sub_temp_carry__2_n_10;
  wire subtractor_sub_temp_carry__2_n_11;
  wire subtractor_sub_temp_carry__2_n_12;
  wire subtractor_sub_temp_carry__2_n_13;
  wire subtractor_sub_temp_carry__2_n_14;
  wire subtractor_sub_temp_carry__2_n_15;
  wire subtractor_sub_temp_carry__2_n_2;
  wire subtractor_sub_temp_carry__2_n_3;
  wire subtractor_sub_temp_carry__2_n_4;
  wire subtractor_sub_temp_carry__2_n_5;
  wire subtractor_sub_temp_carry__2_n_6;
  wire subtractor_sub_temp_carry__2_n_7;
  wire subtractor_sub_temp_carry__2_n_9;
  wire subtractor_sub_temp_carry_n_0;
  wire subtractor_sub_temp_carry_n_1;
  wire subtractor_sub_temp_carry_n_10;
  wire subtractor_sub_temp_carry_n_11;
  wire subtractor_sub_temp_carry_n_12;
  wire subtractor_sub_temp_carry_n_13;
  wire subtractor_sub_temp_carry_n_14;
  wire subtractor_sub_temp_carry_n_15;
  wire subtractor_sub_temp_carry_n_2;
  wire subtractor_sub_temp_carry_n_3;
  wire subtractor_sub_temp_carry_n_4;
  wire subtractor_sub_temp_carry_n_5;
  wire subtractor_sub_temp_carry_n_6;
  wire subtractor_sub_temp_carry_n_7;
  wire subtractor_sub_temp_carry_n_8;
  wire subtractor_sub_temp_carry_n_9;
  wire write_axi_enable;
  wire [6:6]NLW_subtractor_sub_temp_carry__2_CO_UNCONNECTED;
  wire [7:7]NLW_subtractor_sub_temp_carry__2_O_UNCONNECTED;

  FDRE \aout_tmp_reg[10] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\aout_tmp_reg[31]_1 [8]),
        .Q(\aout_tmp_reg[31]_0 [8]),
        .R(RSTP));
  FDRE \aout_tmp_reg[11] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\aout_tmp_reg[31]_1 [9]),
        .Q(\aout_tmp_reg[31]_0 [9]),
        .R(RSTP));
  FDRE \aout_tmp_reg[12] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\aout_tmp_reg[31]_1 [10]),
        .Q(\aout_tmp_reg[31]_0 [10]),
        .R(RSTP));
  FDRE \aout_tmp_reg[13] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\aout_tmp_reg[31]_1 [11]),
        .Q(\aout_tmp_reg[31]_0 [11]),
        .R(RSTP));
  FDRE \aout_tmp_reg[14] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\aout_tmp_reg[31]_1 [12]),
        .Q(\aout_tmp_reg[31]_0 [12]),
        .R(RSTP));
  FDRE \aout_tmp_reg[15] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\aout_tmp_reg[31]_1 [13]),
        .Q(\aout_tmp_reg[31]_0 [13]),
        .R(RSTP));
  FDRE \aout_tmp_reg[16] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\aout_tmp_reg[31]_1 [14]),
        .Q(\aout_tmp_reg[31]_0 [14]),
        .R(RSTP));
  FDRE \aout_tmp_reg[17] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\aout_tmp_reg[31]_1 [15]),
        .Q(\aout_tmp_reg[31]_0 [15]),
        .R(RSTP));
  FDRE \aout_tmp_reg[18] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\aout_tmp_reg[31]_1 [16]),
        .Q(\aout_tmp_reg[31]_0 [16]),
        .R(RSTP));
  FDRE \aout_tmp_reg[19] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\aout_tmp_reg[31]_1 [17]),
        .Q(\aout_tmp_reg[31]_0 [17]),
        .R(RSTP));
  FDRE \aout_tmp_reg[20] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\aout_tmp_reg[31]_1 [18]),
        .Q(\aout_tmp_reg[31]_0 [18]),
        .R(RSTP));
  FDRE \aout_tmp_reg[21] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\aout_tmp_reg[31]_1 [19]),
        .Q(\aout_tmp_reg[31]_0 [19]),
        .R(RSTP));
  FDRE \aout_tmp_reg[22] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\aout_tmp_reg[31]_1 [20]),
        .Q(\aout_tmp_reg[31]_0 [20]),
        .R(RSTP));
  FDRE \aout_tmp_reg[23] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\aout_tmp_reg[31]_1 [21]),
        .Q(\aout_tmp_reg[31]_0 [21]),
        .R(RSTP));
  FDRE \aout_tmp_reg[24] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\aout_tmp_reg[31]_1 [22]),
        .Q(\aout_tmp_reg[31]_0 [22]),
        .R(RSTP));
  FDRE \aout_tmp_reg[25] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\aout_tmp_reg[31]_1 [23]),
        .Q(\aout_tmp_reg[31]_0 [23]),
        .R(RSTP));
  FDRE \aout_tmp_reg[26] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\aout_tmp_reg[31]_1 [24]),
        .Q(\aout_tmp_reg[31]_0 [24]),
        .R(RSTP));
  FDRE \aout_tmp_reg[27] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\aout_tmp_reg[31]_1 [25]),
        .Q(\aout_tmp_reg[31]_0 [25]),
        .R(RSTP));
  FDRE \aout_tmp_reg[28] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\aout_tmp_reg[31]_1 [26]),
        .Q(\aout_tmp_reg[31]_0 [26]),
        .R(RSTP));
  FDRE \aout_tmp_reg[29] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\aout_tmp_reg[31]_1 [27]),
        .Q(\aout_tmp_reg[31]_0 [27]),
        .R(RSTP));
  FDRE \aout_tmp_reg[2] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\aout_tmp_reg[31]_1 [0]),
        .Q(\aout_tmp_reg[31]_0 [0]),
        .R(RSTP));
  FDRE \aout_tmp_reg[30] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\aout_tmp_reg[31]_1 [28]),
        .Q(\aout_tmp_reg[31]_0 [28]),
        .R(RSTP));
  FDRE \aout_tmp_reg[31] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\aout_tmp_reg[31]_1 [29]),
        .Q(\aout_tmp_reg[31]_0 [29]),
        .R(RSTP));
  FDRE \aout_tmp_reg[3] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\aout_tmp_reg[31]_1 [1]),
        .Q(\aout_tmp_reg[31]_0 [1]),
        .R(RSTP));
  FDRE \aout_tmp_reg[4] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\aout_tmp_reg[31]_1 [2]),
        .Q(\aout_tmp_reg[31]_0 [2]),
        .R(RSTP));
  FDRE \aout_tmp_reg[5] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\aout_tmp_reg[31]_1 [3]),
        .Q(\aout_tmp_reg[31]_0 [3]),
        .R(RSTP));
  FDRE \aout_tmp_reg[6] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\aout_tmp_reg[31]_1 [4]),
        .Q(\aout_tmp_reg[31]_0 [4]),
        .R(RSTP));
  FDRE \aout_tmp_reg[7] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\aout_tmp_reg[31]_1 [5]),
        .Q(\aout_tmp_reg[31]_0 [5]),
        .R(RSTP));
  FDRE \aout_tmp_reg[8] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\aout_tmp_reg[31]_1 [6]),
        .Q(\aout_tmp_reg[31]_0 [6]),
        .R(RSTP));
  FDRE \aout_tmp_reg[9] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\aout_tmp_reg[31]_1 [7]),
        .Q(\aout_tmp_reg[31]_0 [7]),
        .R(RSTP));
  (* SOFT_HLUTNM = "soft_lutpair17" *) 
  LUT4 #(
    .INIT(16'hBFB0)) 
    \delayout[0]_i_1 
       (.I0(Q[0]),
        .I1(subtractor_sub_temp_carry__2_n_0),
        .I2(sel),
        .I3(\aout_tmp_reg[31]_1 [0]),
        .O(D[0]));
  LUT4 #(
    .INIT(16'hBFB0)) 
    \delayout[10]_i_1 
       (.I0(subtractor_sub_temp_carry__0_n_14),
        .I1(subtractor_sub_temp_carry__2_n_0),
        .I2(sel),
        .I3(\aout_tmp_reg[31]_1 [10]),
        .O(D[10]));
  LUT4 #(
    .INIT(16'hBFB0)) 
    \delayout[11]_i_1 
       (.I0(subtractor_sub_temp_carry__0_n_13),
        .I1(subtractor_sub_temp_carry__2_n_0),
        .I2(sel),
        .I3(\aout_tmp_reg[31]_1 [11]),
        .O(D[11]));
  LUT4 #(
    .INIT(16'hBFB0)) 
    \delayout[12]_i_1 
       (.I0(subtractor_sub_temp_carry__0_n_12),
        .I1(subtractor_sub_temp_carry__2_n_0),
        .I2(sel),
        .I3(\aout_tmp_reg[31]_1 [12]),
        .O(D[12]));
  LUT4 #(
    .INIT(16'hBFB0)) 
    \delayout[13]_i_1 
       (.I0(subtractor_sub_temp_carry__0_n_11),
        .I1(subtractor_sub_temp_carry__2_n_0),
        .I2(sel),
        .I3(\aout_tmp_reg[31]_1 [13]),
        .O(D[13]));
  LUT4 #(
    .INIT(16'hBFB0)) 
    \delayout[14]_i_1 
       (.I0(subtractor_sub_temp_carry__0_n_10),
        .I1(subtractor_sub_temp_carry__2_n_0),
        .I2(sel),
        .I3(\aout_tmp_reg[31]_1 [14]),
        .O(D[14]));
  LUT4 #(
    .INIT(16'hBFB0)) 
    \delayout[15]_i_1 
       (.I0(subtractor_sub_temp_carry__0_n_9),
        .I1(subtractor_sub_temp_carry__2_n_0),
        .I2(sel),
        .I3(\aout_tmp_reg[31]_1 [15]),
        .O(D[15]));
  LUT4 #(
    .INIT(16'hBFB0)) 
    \delayout[16]_i_1 
       (.I0(subtractor_sub_temp_carry__0_n_8),
        .I1(subtractor_sub_temp_carry__2_n_0),
        .I2(sel),
        .I3(\aout_tmp_reg[31]_1 [16]),
        .O(D[16]));
  LUT4 #(
    .INIT(16'hBFB0)) 
    \delayout[17]_i_1 
       (.I0(subtractor_sub_temp_carry__1_n_15),
        .I1(subtractor_sub_temp_carry__2_n_0),
        .I2(sel),
        .I3(\aout_tmp_reg[31]_1 [17]),
        .O(D[17]));
  LUT4 #(
    .INIT(16'hBFB0)) 
    \delayout[18]_i_1 
       (.I0(subtractor_sub_temp_carry__1_n_14),
        .I1(subtractor_sub_temp_carry__2_n_0),
        .I2(sel),
        .I3(\aout_tmp_reg[31]_1 [18]),
        .O(D[18]));
  LUT4 #(
    .INIT(16'hBFB0)) 
    \delayout[19]_i_1 
       (.I0(subtractor_sub_temp_carry__1_n_13),
        .I1(subtractor_sub_temp_carry__2_n_0),
        .I2(sel),
        .I3(\aout_tmp_reg[31]_1 [19]),
        .O(D[19]));
  (* SOFT_HLUTNM = "soft_lutpair18" *) 
  LUT4 #(
    .INIT(16'hBFB0)) 
    \delayout[1]_i_1 
       (.I0(subtractor_sub_temp_carry_n_15),
        .I1(subtractor_sub_temp_carry__2_n_0),
        .I2(sel),
        .I3(\aout_tmp_reg[31]_1 [1]),
        .O(D[1]));
  LUT4 #(
    .INIT(16'hBFB0)) 
    \delayout[20]_i_1 
       (.I0(subtractor_sub_temp_carry__1_n_12),
        .I1(subtractor_sub_temp_carry__2_n_0),
        .I2(sel),
        .I3(\aout_tmp_reg[31]_1 [20]),
        .O(D[20]));
  LUT4 #(
    .INIT(16'hBFB0)) 
    \delayout[21]_i_1 
       (.I0(subtractor_sub_temp_carry__1_n_11),
        .I1(subtractor_sub_temp_carry__2_n_0),
        .I2(sel),
        .I3(\aout_tmp_reg[31]_1 [21]),
        .O(D[21]));
  LUT4 #(
    .INIT(16'hBFB0)) 
    \delayout[22]_i_1 
       (.I0(subtractor_sub_temp_carry__1_n_10),
        .I1(subtractor_sub_temp_carry__2_n_0),
        .I2(sel),
        .I3(\aout_tmp_reg[31]_1 [22]),
        .O(D[22]));
  LUT4 #(
    .INIT(16'hBFB0)) 
    \delayout[23]_i_1 
       (.I0(subtractor_sub_temp_carry__1_n_9),
        .I1(subtractor_sub_temp_carry__2_n_0),
        .I2(sel),
        .I3(\aout_tmp_reg[31]_1 [23]),
        .O(D[23]));
  LUT4 #(
    .INIT(16'hBFB0)) 
    \delayout[24]_i_1 
       (.I0(subtractor_sub_temp_carry__1_n_8),
        .I1(subtractor_sub_temp_carry__2_n_0),
        .I2(sel),
        .I3(\aout_tmp_reg[31]_1 [24]),
        .O(D[24]));
  LUT4 #(
    .INIT(16'hBFB0)) 
    \delayout[25]_i_1 
       (.I0(subtractor_sub_temp_carry__2_n_15),
        .I1(subtractor_sub_temp_carry__2_n_0),
        .I2(sel),
        .I3(\aout_tmp_reg[31]_1 [25]),
        .O(D[25]));
  LUT4 #(
    .INIT(16'hBFB0)) 
    \delayout[26]_i_1 
       (.I0(subtractor_sub_temp_carry__2_n_14),
        .I1(subtractor_sub_temp_carry__2_n_0),
        .I2(sel),
        .I3(\aout_tmp_reg[31]_1 [26]),
        .O(D[26]));
  LUT4 #(
    .INIT(16'hBFB0)) 
    \delayout[27]_i_1 
       (.I0(subtractor_sub_temp_carry__2_n_13),
        .I1(subtractor_sub_temp_carry__2_n_0),
        .I2(sel),
        .I3(\aout_tmp_reg[31]_1 [27]),
        .O(D[27]));
  LUT4 #(
    .INIT(16'hBFB0)) 
    \delayout[28]_i_1 
       (.I0(subtractor_sub_temp_carry__2_n_12),
        .I1(subtractor_sub_temp_carry__2_n_0),
        .I2(sel),
        .I3(\aout_tmp_reg[31]_1 [28]),
        .O(D[28]));
  LUT4 #(
    .INIT(16'hBFB0)) 
    \delayout[29]_i_1 
       (.I0(subtractor_sub_temp_carry__2_n_11),
        .I1(subtractor_sub_temp_carry__2_n_0),
        .I2(sel),
        .I3(\aout_tmp_reg[31]_1 [29]),
        .O(D[29]));
  LUT4 #(
    .INIT(16'hBFB0)) 
    \delayout[2]_i_1 
       (.I0(subtractor_sub_temp_carry_n_14),
        .I1(subtractor_sub_temp_carry__2_n_0),
        .I2(sel),
        .I3(\aout_tmp_reg[31]_1 [2]),
        .O(D[2]));
  (* SOFT_HLUTNM = "soft_lutpair17" *) 
  LUT3 #(
    .INIT(8'hA2)) 
    \delayout[30]_i_1 
       (.I0(sel),
        .I1(subtractor_sub_temp_carry__2_n_0),
        .I2(subtractor_sub_temp_carry__2_n_10),
        .O(D[30]));
  (* SOFT_HLUTNM = "soft_lutpair18" *) 
  LUT3 #(
    .INIT(8'hA2)) 
    \delayout[31]_i_1 
       (.I0(sel),
        .I1(subtractor_sub_temp_carry__2_n_0),
        .I2(subtractor_sub_temp_carry__2_n_9),
        .O(D[31]));
  LUT4 #(
    .INIT(16'hBFB0)) 
    \delayout[3]_i_1 
       (.I0(subtractor_sub_temp_carry_n_13),
        .I1(subtractor_sub_temp_carry__2_n_0),
        .I2(sel),
        .I3(\aout_tmp_reg[31]_1 [3]),
        .O(D[3]));
  LUT4 #(
    .INIT(16'hBFB0)) 
    \delayout[4]_i_1 
       (.I0(subtractor_sub_temp_carry_n_12),
        .I1(subtractor_sub_temp_carry__2_n_0),
        .I2(sel),
        .I3(\aout_tmp_reg[31]_1 [4]),
        .O(D[4]));
  LUT4 #(
    .INIT(16'hBFB0)) 
    \delayout[5]_i_1 
       (.I0(subtractor_sub_temp_carry_n_11),
        .I1(subtractor_sub_temp_carry__2_n_0),
        .I2(sel),
        .I3(\aout_tmp_reg[31]_1 [5]),
        .O(D[5]));
  LUT4 #(
    .INIT(16'hBFB0)) 
    \delayout[6]_i_1 
       (.I0(subtractor_sub_temp_carry_n_10),
        .I1(subtractor_sub_temp_carry__2_n_0),
        .I2(sel),
        .I3(\aout_tmp_reg[31]_1 [6]),
        .O(D[6]));
  LUT4 #(
    .INIT(16'hBFB0)) 
    \delayout[7]_i_1 
       (.I0(subtractor_sub_temp_carry_n_9),
        .I1(subtractor_sub_temp_carry__2_n_0),
        .I2(sel),
        .I3(\aout_tmp_reg[31]_1 [7]),
        .O(D[7]));
  LUT4 #(
    .INIT(16'hBFB0)) 
    \delayout[8]_i_1 
       (.I0(subtractor_sub_temp_carry_n_8),
        .I1(subtractor_sub_temp_carry__2_n_0),
        .I2(sel),
        .I3(\aout_tmp_reg[31]_1 [8]),
        .O(D[8]));
  LUT4 #(
    .INIT(16'hBFB0)) 
    \delayout[9]_i_1 
       (.I0(subtractor_sub_temp_carry__0_n_15),
        .I1(subtractor_sub_temp_carry__2_n_0),
        .I2(sel),
        .I3(\aout_tmp_reg[31]_1 [9]),
        .O(D[9]));
  FDRE \delayout_reg[0] 
       (.C(IPCORE_CLK),
        .CE(write_axi_enable),
        .D(D[0]),
        .Q(Q[0]),
        .R(RSTP));
  FDRE \delayout_reg[10] 
       (.C(IPCORE_CLK),
        .CE(write_axi_enable),
        .D(D[10]),
        .Q(Q[10]),
        .R(RSTP));
  FDRE \delayout_reg[11] 
       (.C(IPCORE_CLK),
        .CE(write_axi_enable),
        .D(D[11]),
        .Q(Q[11]),
        .R(RSTP));
  FDRE \delayout_reg[12] 
       (.C(IPCORE_CLK),
        .CE(write_axi_enable),
        .D(D[12]),
        .Q(Q[12]),
        .R(RSTP));
  FDRE \delayout_reg[13] 
       (.C(IPCORE_CLK),
        .CE(write_axi_enable),
        .D(D[13]),
        .Q(Q[13]),
        .R(RSTP));
  FDRE \delayout_reg[14] 
       (.C(IPCORE_CLK),
        .CE(write_axi_enable),
        .D(D[14]),
        .Q(Q[14]),
        .R(RSTP));
  FDRE \delayout_reg[15] 
       (.C(IPCORE_CLK),
        .CE(write_axi_enable),
        .D(D[15]),
        .Q(Q[15]),
        .R(RSTP));
  FDRE \delayout_reg[16] 
       (.C(IPCORE_CLK),
        .CE(write_axi_enable),
        .D(D[16]),
        .Q(Q[16]),
        .R(RSTP));
  FDRE \delayout_reg[17] 
       (.C(IPCORE_CLK),
        .CE(write_axi_enable),
        .D(D[17]),
        .Q(Q[17]),
        .R(RSTP));
  FDRE \delayout_reg[18] 
       (.C(IPCORE_CLK),
        .CE(write_axi_enable),
        .D(D[18]),
        .Q(Q[18]),
        .R(RSTP));
  FDRE \delayout_reg[19] 
       (.C(IPCORE_CLK),
        .CE(write_axi_enable),
        .D(D[19]),
        .Q(Q[19]),
        .R(RSTP));
  FDRE \delayout_reg[1] 
       (.C(IPCORE_CLK),
        .CE(write_axi_enable),
        .D(D[1]),
        .Q(Q[1]),
        .R(RSTP));
  FDRE \delayout_reg[20] 
       (.C(IPCORE_CLK),
        .CE(write_axi_enable),
        .D(D[20]),
        .Q(Q[20]),
        .R(RSTP));
  FDRE \delayout_reg[21] 
       (.C(IPCORE_CLK),
        .CE(write_axi_enable),
        .D(D[21]),
        .Q(Q[21]),
        .R(RSTP));
  FDRE \delayout_reg[22] 
       (.C(IPCORE_CLK),
        .CE(write_axi_enable),
        .D(D[22]),
        .Q(Q[22]),
        .R(RSTP));
  FDRE \delayout_reg[23] 
       (.C(IPCORE_CLK),
        .CE(write_axi_enable),
        .D(D[23]),
        .Q(Q[23]),
        .R(RSTP));
  FDRE \delayout_reg[24] 
       (.C(IPCORE_CLK),
        .CE(write_axi_enable),
        .D(D[24]),
        .Q(Q[24]),
        .R(RSTP));
  FDRE \delayout_reg[25] 
       (.C(IPCORE_CLK),
        .CE(write_axi_enable),
        .D(D[25]),
        .Q(Q[25]),
        .R(RSTP));
  FDRE \delayout_reg[26] 
       (.C(IPCORE_CLK),
        .CE(write_axi_enable),
        .D(D[26]),
        .Q(Q[26]),
        .R(RSTP));
  FDRE \delayout_reg[27] 
       (.C(IPCORE_CLK),
        .CE(write_axi_enable),
        .D(D[27]),
        .Q(Q[27]),
        .R(RSTP));
  FDRE \delayout_reg[28] 
       (.C(IPCORE_CLK),
        .CE(write_axi_enable),
        .D(D[28]),
        .Q(Q[28]),
        .R(RSTP));
  FDRE \delayout_reg[29] 
       (.C(IPCORE_CLK),
        .CE(write_axi_enable),
        .D(D[29]),
        .Q(Q[29]),
        .R(RSTP));
  FDRE \delayout_reg[2] 
       (.C(IPCORE_CLK),
        .CE(write_axi_enable),
        .D(D[2]),
        .Q(Q[2]),
        .R(RSTP));
  FDRE \delayout_reg[30] 
       (.C(IPCORE_CLK),
        .CE(write_axi_enable),
        .D(D[30]),
        .Q(Q[30]),
        .R(RSTP));
  FDRE \delayout_reg[31] 
       (.C(IPCORE_CLK),
        .CE(write_axi_enable),
        .D(D[31]),
        .Q(Q[31]),
        .R(RSTP));
  FDRE \delayout_reg[3] 
       (.C(IPCORE_CLK),
        .CE(write_axi_enable),
        .D(D[3]),
        .Q(Q[3]),
        .R(RSTP));
  FDRE \delayout_reg[4] 
       (.C(IPCORE_CLK),
        .CE(write_axi_enable),
        .D(D[4]),
        .Q(Q[4]),
        .R(RSTP));
  FDRE \delayout_reg[5] 
       (.C(IPCORE_CLK),
        .CE(write_axi_enable),
        .D(D[5]),
        .Q(Q[5]),
        .R(RSTP));
  FDRE \delayout_reg[6] 
       (.C(IPCORE_CLK),
        .CE(write_axi_enable),
        .D(D[6]),
        .Q(Q[6]),
        .R(RSTP));
  FDRE \delayout_reg[7] 
       (.C(IPCORE_CLK),
        .CE(write_axi_enable),
        .D(D[7]),
        .Q(Q[7]),
        .R(RSTP));
  FDRE \delayout_reg[8] 
       (.C(IPCORE_CLK),
        .CE(write_axi_enable),
        .D(D[8]),
        .Q(Q[8]),
        .R(RSTP));
  FDRE \delayout_reg[9] 
       (.C(IPCORE_CLK),
        .CE(write_axi_enable),
        .D(D[9]),
        .Q(Q[9]),
        .R(RSTP));
  CARRY8 subtractor_sub_temp_carry
       (.CI(\delayout_reg[8]_0 ),
        .CI_TOP(1'b0),
        .CO({subtractor_sub_temp_carry_n_0,subtractor_sub_temp_carry_n_1,subtractor_sub_temp_carry_n_2,subtractor_sub_temp_carry_n_3,subtractor_sub_temp_carry_n_4,subtractor_sub_temp_carry_n_5,subtractor_sub_temp_carry_n_6,subtractor_sub_temp_carry_n_7}),
        .DI({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .O({subtractor_sub_temp_carry_n_8,subtractor_sub_temp_carry_n_9,subtractor_sub_temp_carry_n_10,subtractor_sub_temp_carry_n_11,subtractor_sub_temp_carry_n_12,subtractor_sub_temp_carry_n_13,subtractor_sub_temp_carry_n_14,subtractor_sub_temp_carry_n_15}),
        .S(S));
  CARRY8 subtractor_sub_temp_carry__0
       (.CI(subtractor_sub_temp_carry_n_0),
        .CI_TOP(1'b0),
        .CO({subtractor_sub_temp_carry__0_n_0,subtractor_sub_temp_carry__0_n_1,subtractor_sub_temp_carry__0_n_2,subtractor_sub_temp_carry__0_n_3,subtractor_sub_temp_carry__0_n_4,subtractor_sub_temp_carry__0_n_5,subtractor_sub_temp_carry__0_n_6,subtractor_sub_temp_carry__0_n_7}),
        .DI({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .O({subtractor_sub_temp_carry__0_n_8,subtractor_sub_temp_carry__0_n_9,subtractor_sub_temp_carry__0_n_10,subtractor_sub_temp_carry__0_n_11,subtractor_sub_temp_carry__0_n_12,subtractor_sub_temp_carry__0_n_13,subtractor_sub_temp_carry__0_n_14,subtractor_sub_temp_carry__0_n_15}),
        .S(\delayout_reg[16]_0 ));
  CARRY8 subtractor_sub_temp_carry__1
       (.CI(subtractor_sub_temp_carry__0_n_0),
        .CI_TOP(1'b0),
        .CO({subtractor_sub_temp_carry__1_n_0,subtractor_sub_temp_carry__1_n_1,subtractor_sub_temp_carry__1_n_2,subtractor_sub_temp_carry__1_n_3,subtractor_sub_temp_carry__1_n_4,subtractor_sub_temp_carry__1_n_5,subtractor_sub_temp_carry__1_n_6,subtractor_sub_temp_carry__1_n_7}),
        .DI({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .O({subtractor_sub_temp_carry__1_n_8,subtractor_sub_temp_carry__1_n_9,subtractor_sub_temp_carry__1_n_10,subtractor_sub_temp_carry__1_n_11,subtractor_sub_temp_carry__1_n_12,subtractor_sub_temp_carry__1_n_13,subtractor_sub_temp_carry__1_n_14,subtractor_sub_temp_carry__1_n_15}),
        .S(\delayout_reg[24]_0 ));
  CARRY8 subtractor_sub_temp_carry__2
       (.CI(subtractor_sub_temp_carry__1_n_0),
        .CI_TOP(1'b0),
        .CO({subtractor_sub_temp_carry__2_n_0,NLW_subtractor_sub_temp_carry__2_CO_UNCONNECTED[6],subtractor_sub_temp_carry__2_n_2,subtractor_sub_temp_carry__2_n_3,subtractor_sub_temp_carry__2_n_4,subtractor_sub_temp_carry__2_n_5,subtractor_sub_temp_carry__2_n_6,subtractor_sub_temp_carry__2_n_7}),
        .DI({1'b0,DI,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .O({NLW_subtractor_sub_temp_carry__2_O_UNCONNECTED[7],subtractor_sub_temp_carry__2_n_9,subtractor_sub_temp_carry__2_n_10,subtractor_sub_temp_carry__2_n_11,subtractor_sub_temp_carry__2_n_12,subtractor_sub_temp_carry__2_n_13,subtractor_sub_temp_carry__2_n_14,subtractor_sub_temp_carry__2_n_15}),
        .S({1'b1,Q[31],\delayout_reg[31]_0 }));
endmodule

(* ORIG_REF_NAME = "IncreEncoder_V24_ip_src_HDL_Reciprocal_core" *) 
module zusys_IncreEncoder_V24_ip_0_0_IncreEncoder_V24_ip_src_HDL_Reciprocal_core_0
   (Q,
    \aout_tmp_reg[31]_0 ,
    mul1_mul_temp_carry__4_0,
    CEP,
    IPCORE_CLK,
    RSTP,
    D,
    mul1_mul_temp_i_16_0,
    S,
    mul1_mul_temp_i_8_0,
    mul1_mul_temp__0_i_15_0,
    DI,
    mul1_mul_temp__0_i_7_0,
    \aout_tmp_reg[31]_1 ,
    write_axi_enable,
    sel);
  output [31:0]Q;
  output [29:0]\aout_tmp_reg[31]_0 ;
  output [31:0]mul1_mul_temp_carry__4_0;
  input CEP;
  input IPCORE_CLK;
  input RSTP;
  input [31:0]D;
  input mul1_mul_temp_i_16_0;
  input [7:0]S;
  input [7:0]mul1_mul_temp_i_8_0;
  input [7:0]mul1_mul_temp__0_i_15_0;
  input [0:0]DI;
  input [5:0]mul1_mul_temp__0_i_7_0;
  input [29:0]\aout_tmp_reg[31]_1 ;
  input write_axi_enable;
  input sel;

  wire CEP;
  wire [31:0]D;
  wire [0:0]DI;
  wire IPCORE_CLK;
  wire [31:0]Q;
  wire RSTP;
  wire [7:0]S;
  wire [29:0]\aout_tmp_reg[31]_0 ;
  wire [29:0]\aout_tmp_reg[31]_1 ;
  wire mul1_mul_temp__0_i_10_n_0;
  wire mul1_mul_temp__0_i_11_n_0;
  wire mul1_mul_temp__0_i_12_n_0;
  wire mul1_mul_temp__0_i_13_n_0;
  wire mul1_mul_temp__0_i_14_n_0;
  wire [7:0]mul1_mul_temp__0_i_15_0;
  wire mul1_mul_temp__0_i_15_n_0;
  wire mul1_mul_temp__0_i_1_n_0;
  wire mul1_mul_temp__0_i_2_n_0;
  wire mul1_mul_temp__0_i_3_n_0;
  wire mul1_mul_temp__0_i_4_n_0;
  wire mul1_mul_temp__0_i_5_n_0;
  wire mul1_mul_temp__0_i_6_n_0;
  wire [5:0]mul1_mul_temp__0_i_7_0;
  wire mul1_mul_temp__0_i_7_n_0;
  wire mul1_mul_temp__0_i_8_n_0;
  wire mul1_mul_temp__0_i_9_n_0;
  wire mul1_mul_temp__0_n_100;
  wire mul1_mul_temp__0_n_101;
  wire mul1_mul_temp__0_n_102;
  wire mul1_mul_temp__0_n_103;
  wire mul1_mul_temp__0_n_104;
  wire mul1_mul_temp__0_n_105;
  wire mul1_mul_temp__0_n_76;
  wire mul1_mul_temp__0_n_77;
  wire mul1_mul_temp__0_n_78;
  wire mul1_mul_temp__0_n_79;
  wire mul1_mul_temp__0_n_80;
  wire mul1_mul_temp__0_n_81;
  wire mul1_mul_temp__0_n_82;
  wire mul1_mul_temp__0_n_83;
  wire mul1_mul_temp__0_n_84;
  wire mul1_mul_temp__0_n_85;
  wire mul1_mul_temp__0_n_86;
  wire mul1_mul_temp__0_n_87;
  wire mul1_mul_temp__0_n_88;
  wire mul1_mul_temp__0_n_89;
  wire mul1_mul_temp__0_n_90;
  wire mul1_mul_temp__0_n_91;
  wire mul1_mul_temp__0_n_92;
  wire mul1_mul_temp__0_n_93;
  wire mul1_mul_temp__0_n_94;
  wire mul1_mul_temp__0_n_95;
  wire mul1_mul_temp__0_n_96;
  wire mul1_mul_temp__0_n_97;
  wire mul1_mul_temp__0_n_98;
  wire mul1_mul_temp__0_n_99;
  wire mul1_mul_temp__1_n_100;
  wire mul1_mul_temp__1_n_101;
  wire mul1_mul_temp__1_n_102;
  wire mul1_mul_temp__1_n_103;
  wire mul1_mul_temp__1_n_104;
  wire mul1_mul_temp__1_n_105;
  wire mul1_mul_temp__1_n_106;
  wire mul1_mul_temp__1_n_107;
  wire mul1_mul_temp__1_n_108;
  wire mul1_mul_temp__1_n_109;
  wire mul1_mul_temp__1_n_110;
  wire mul1_mul_temp__1_n_111;
  wire mul1_mul_temp__1_n_112;
  wire mul1_mul_temp__1_n_113;
  wire mul1_mul_temp__1_n_114;
  wire mul1_mul_temp__1_n_115;
  wire mul1_mul_temp__1_n_116;
  wire mul1_mul_temp__1_n_117;
  wire mul1_mul_temp__1_n_118;
  wire mul1_mul_temp__1_n_119;
  wire mul1_mul_temp__1_n_120;
  wire mul1_mul_temp__1_n_121;
  wire mul1_mul_temp__1_n_122;
  wire mul1_mul_temp__1_n_123;
  wire mul1_mul_temp__1_n_124;
  wire mul1_mul_temp__1_n_125;
  wire mul1_mul_temp__1_n_126;
  wire mul1_mul_temp__1_n_127;
  wire mul1_mul_temp__1_n_128;
  wire mul1_mul_temp__1_n_129;
  wire mul1_mul_temp__1_n_130;
  wire mul1_mul_temp__1_n_131;
  wire mul1_mul_temp__1_n_132;
  wire mul1_mul_temp__1_n_133;
  wire mul1_mul_temp__1_n_134;
  wire mul1_mul_temp__1_n_135;
  wire mul1_mul_temp__1_n_136;
  wire mul1_mul_temp__1_n_137;
  wire mul1_mul_temp__1_n_138;
  wire mul1_mul_temp__1_n_139;
  wire mul1_mul_temp__1_n_140;
  wire mul1_mul_temp__1_n_141;
  wire mul1_mul_temp__1_n_142;
  wire mul1_mul_temp__1_n_143;
  wire mul1_mul_temp__1_n_144;
  wire mul1_mul_temp__1_n_145;
  wire mul1_mul_temp__1_n_146;
  wire mul1_mul_temp__1_n_147;
  wire mul1_mul_temp__1_n_148;
  wire mul1_mul_temp__1_n_149;
  wire mul1_mul_temp__1_n_150;
  wire mul1_mul_temp__1_n_151;
  wire mul1_mul_temp__1_n_152;
  wire mul1_mul_temp__1_n_153;
  wire mul1_mul_temp__1_n_58;
  wire mul1_mul_temp__1_n_59;
  wire mul1_mul_temp__1_n_60;
  wire mul1_mul_temp__1_n_61;
  wire mul1_mul_temp__1_n_62;
  wire mul1_mul_temp__1_n_63;
  wire mul1_mul_temp__1_n_64;
  wire mul1_mul_temp__1_n_65;
  wire mul1_mul_temp__1_n_66;
  wire mul1_mul_temp__1_n_67;
  wire mul1_mul_temp__1_n_68;
  wire mul1_mul_temp__1_n_69;
  wire mul1_mul_temp__1_n_70;
  wire mul1_mul_temp__1_n_71;
  wire mul1_mul_temp__1_n_72;
  wire mul1_mul_temp__1_n_73;
  wire mul1_mul_temp__1_n_74;
  wire mul1_mul_temp__1_n_75;
  wire mul1_mul_temp__1_n_76;
  wire mul1_mul_temp__1_n_77;
  wire mul1_mul_temp__1_n_78;
  wire mul1_mul_temp__1_n_79;
  wire mul1_mul_temp__1_n_80;
  wire mul1_mul_temp__1_n_81;
  wire mul1_mul_temp__1_n_82;
  wire mul1_mul_temp__1_n_83;
  wire mul1_mul_temp__1_n_84;
  wire mul1_mul_temp__1_n_85;
  wire mul1_mul_temp__1_n_86;
  wire mul1_mul_temp__1_n_87;
  wire mul1_mul_temp__1_n_88;
  wire mul1_mul_temp__1_n_89;
  wire mul1_mul_temp__1_n_90;
  wire mul1_mul_temp__1_n_91;
  wire mul1_mul_temp__1_n_92;
  wire mul1_mul_temp__1_n_93;
  wire mul1_mul_temp__1_n_94;
  wire mul1_mul_temp__1_n_95;
  wire mul1_mul_temp__1_n_96;
  wire mul1_mul_temp__1_n_97;
  wire mul1_mul_temp__1_n_98;
  wire mul1_mul_temp__1_n_99;
  wire mul1_mul_temp__2_n_100;
  wire mul1_mul_temp__2_n_101;
  wire mul1_mul_temp__2_n_102;
  wire mul1_mul_temp__2_n_103;
  wire mul1_mul_temp__2_n_104;
  wire mul1_mul_temp__2_n_105;
  wire mul1_mul_temp__2_n_59;
  wire mul1_mul_temp__2_n_60;
  wire mul1_mul_temp__2_n_61;
  wire mul1_mul_temp__2_n_62;
  wire mul1_mul_temp__2_n_63;
  wire mul1_mul_temp__2_n_64;
  wire mul1_mul_temp__2_n_65;
  wire mul1_mul_temp__2_n_66;
  wire mul1_mul_temp__2_n_67;
  wire mul1_mul_temp__2_n_68;
  wire mul1_mul_temp__2_n_69;
  wire mul1_mul_temp__2_n_70;
  wire mul1_mul_temp__2_n_71;
  wire mul1_mul_temp__2_n_72;
  wire mul1_mul_temp__2_n_73;
  wire mul1_mul_temp__2_n_74;
  wire mul1_mul_temp__2_n_75;
  wire mul1_mul_temp__2_n_76;
  wire mul1_mul_temp__2_n_77;
  wire mul1_mul_temp__2_n_78;
  wire mul1_mul_temp__2_n_79;
  wire mul1_mul_temp__2_n_80;
  wire mul1_mul_temp__2_n_81;
  wire mul1_mul_temp__2_n_82;
  wire mul1_mul_temp__2_n_83;
  wire mul1_mul_temp__2_n_84;
  wire mul1_mul_temp__2_n_85;
  wire mul1_mul_temp__2_n_86;
  wire mul1_mul_temp__2_n_87;
  wire mul1_mul_temp__2_n_88;
  wire mul1_mul_temp__2_n_89;
  wire mul1_mul_temp__2_n_90;
  wire mul1_mul_temp__2_n_91;
  wire mul1_mul_temp__2_n_92;
  wire mul1_mul_temp__2_n_93;
  wire mul1_mul_temp__2_n_94;
  wire mul1_mul_temp__2_n_95;
  wire mul1_mul_temp__2_n_96;
  wire mul1_mul_temp__2_n_97;
  wire mul1_mul_temp__2_n_98;
  wire mul1_mul_temp__2_n_99;
  wire mul1_mul_temp_carry__0_i_1_n_0;
  wire mul1_mul_temp_carry__0_i_2_n_0;
  wire mul1_mul_temp_carry__0_i_3_n_0;
  wire mul1_mul_temp_carry__0_i_4_n_0;
  wire mul1_mul_temp_carry__0_i_5_n_0;
  wire mul1_mul_temp_carry__0_i_6_n_0;
  wire mul1_mul_temp_carry__0_i_7_n_0;
  wire mul1_mul_temp_carry__0_i_8_n_0;
  wire mul1_mul_temp_carry__0_n_0;
  wire mul1_mul_temp_carry__0_n_1;
  wire mul1_mul_temp_carry__0_n_2;
  wire mul1_mul_temp_carry__0_n_3;
  wire mul1_mul_temp_carry__0_n_4;
  wire mul1_mul_temp_carry__0_n_5;
  wire mul1_mul_temp_carry__0_n_6;
  wire mul1_mul_temp_carry__0_n_7;
  wire mul1_mul_temp_carry__0_n_8;
  wire mul1_mul_temp_carry__0_n_9;
  wire mul1_mul_temp_carry__1_i_1_n_0;
  wire mul1_mul_temp_carry__1_i_2_n_0;
  wire mul1_mul_temp_carry__1_i_3_n_0;
  wire mul1_mul_temp_carry__1_i_4_n_0;
  wire mul1_mul_temp_carry__1_i_5_n_0;
  wire mul1_mul_temp_carry__1_i_6_n_0;
  wire mul1_mul_temp_carry__1_i_7_n_0;
  wire mul1_mul_temp_carry__1_i_8_n_0;
  wire mul1_mul_temp_carry__1_n_0;
  wire mul1_mul_temp_carry__1_n_1;
  wire mul1_mul_temp_carry__1_n_10;
  wire mul1_mul_temp_carry__1_n_11;
  wire mul1_mul_temp_carry__1_n_12;
  wire mul1_mul_temp_carry__1_n_13;
  wire mul1_mul_temp_carry__1_n_14;
  wire mul1_mul_temp_carry__1_n_15;
  wire mul1_mul_temp_carry__1_n_2;
  wire mul1_mul_temp_carry__1_n_3;
  wire mul1_mul_temp_carry__1_n_4;
  wire mul1_mul_temp_carry__1_n_5;
  wire mul1_mul_temp_carry__1_n_6;
  wire mul1_mul_temp_carry__1_n_7;
  wire mul1_mul_temp_carry__1_n_8;
  wire mul1_mul_temp_carry__1_n_9;
  wire mul1_mul_temp_carry__2_i_1_n_0;
  wire mul1_mul_temp_carry__2_i_2_n_0;
  wire mul1_mul_temp_carry__2_i_3_n_0;
  wire mul1_mul_temp_carry__2_i_4_n_0;
  wire mul1_mul_temp_carry__2_i_5_n_0;
  wire mul1_mul_temp_carry__2_i_6_n_0;
  wire mul1_mul_temp_carry__2_i_7_n_0;
  wire mul1_mul_temp_carry__2_i_8_n_0;
  wire mul1_mul_temp_carry__2_n_0;
  wire mul1_mul_temp_carry__2_n_1;
  wire mul1_mul_temp_carry__2_n_10;
  wire mul1_mul_temp_carry__2_n_11;
  wire mul1_mul_temp_carry__2_n_12;
  wire mul1_mul_temp_carry__2_n_13;
  wire mul1_mul_temp_carry__2_n_14;
  wire mul1_mul_temp_carry__2_n_15;
  wire mul1_mul_temp_carry__2_n_2;
  wire mul1_mul_temp_carry__2_n_3;
  wire mul1_mul_temp_carry__2_n_4;
  wire mul1_mul_temp_carry__2_n_5;
  wire mul1_mul_temp_carry__2_n_6;
  wire mul1_mul_temp_carry__2_n_7;
  wire mul1_mul_temp_carry__2_n_8;
  wire mul1_mul_temp_carry__2_n_9;
  wire mul1_mul_temp_carry__3_i_1_n_0;
  wire mul1_mul_temp_carry__3_i_2_n_0;
  wire mul1_mul_temp_carry__3_i_3_n_0;
  wire mul1_mul_temp_carry__3_i_4_n_0;
  wire mul1_mul_temp_carry__3_i_5_n_0;
  wire mul1_mul_temp_carry__3_i_6_n_0;
  wire mul1_mul_temp_carry__3_i_7_n_0;
  wire mul1_mul_temp_carry__3_i_8_n_0;
  wire mul1_mul_temp_carry__3_n_0;
  wire mul1_mul_temp_carry__3_n_1;
  wire mul1_mul_temp_carry__3_n_10;
  wire mul1_mul_temp_carry__3_n_11;
  wire mul1_mul_temp_carry__3_n_12;
  wire mul1_mul_temp_carry__3_n_13;
  wire mul1_mul_temp_carry__3_n_14;
  wire mul1_mul_temp_carry__3_n_15;
  wire mul1_mul_temp_carry__3_n_2;
  wire mul1_mul_temp_carry__3_n_3;
  wire mul1_mul_temp_carry__3_n_4;
  wire mul1_mul_temp_carry__3_n_5;
  wire mul1_mul_temp_carry__3_n_6;
  wire mul1_mul_temp_carry__3_n_7;
  wire mul1_mul_temp_carry__3_n_8;
  wire mul1_mul_temp_carry__3_n_9;
  wire [31:0]mul1_mul_temp_carry__4_0;
  wire mul1_mul_temp_carry__4_i_1_n_0;
  wire mul1_mul_temp_carry__4_i_2_n_0;
  wire mul1_mul_temp_carry__4_i_3_n_0;
  wire mul1_mul_temp_carry__4_i_4_n_0;
  wire mul1_mul_temp_carry__4_i_5_n_0;
  wire mul1_mul_temp_carry__4_i_6_n_0;
  wire mul1_mul_temp_carry__4_i_7_n_0;
  wire mul1_mul_temp_carry__4_i_8_n_0;
  wire mul1_mul_temp_carry__4_n_1;
  wire mul1_mul_temp_carry__4_n_10;
  wire mul1_mul_temp_carry__4_n_11;
  wire mul1_mul_temp_carry__4_n_12;
  wire mul1_mul_temp_carry__4_n_13;
  wire mul1_mul_temp_carry__4_n_14;
  wire mul1_mul_temp_carry__4_n_15;
  wire mul1_mul_temp_carry__4_n_2;
  wire mul1_mul_temp_carry__4_n_3;
  wire mul1_mul_temp_carry__4_n_4;
  wire mul1_mul_temp_carry__4_n_5;
  wire mul1_mul_temp_carry__4_n_6;
  wire mul1_mul_temp_carry__4_n_7;
  wire mul1_mul_temp_carry__4_n_8;
  wire mul1_mul_temp_carry__4_n_9;
  wire mul1_mul_temp_carry_i_1_n_0;
  wire mul1_mul_temp_carry_i_2_n_0;
  wire mul1_mul_temp_carry_i_3_n_0;
  wire mul1_mul_temp_carry_i_4_n_0;
  wire mul1_mul_temp_carry_i_5_n_0;
  wire mul1_mul_temp_carry_i_6_n_0;
  wire mul1_mul_temp_carry_i_7_n_0;
  wire mul1_mul_temp_carry_n_0;
  wire mul1_mul_temp_carry_n_1;
  wire mul1_mul_temp_carry_n_2;
  wire mul1_mul_temp_carry_n_3;
  wire mul1_mul_temp_carry_n_4;
  wire mul1_mul_temp_carry_n_5;
  wire mul1_mul_temp_carry_n_6;
  wire mul1_mul_temp_carry_n_7;
  wire mul1_mul_temp_i_10_n_0;
  wire mul1_mul_temp_i_11_n_0;
  wire mul1_mul_temp_i_12_n_0;
  wire mul1_mul_temp_i_13_n_0;
  wire mul1_mul_temp_i_14_n_0;
  wire mul1_mul_temp_i_15_n_0;
  wire mul1_mul_temp_i_16_0;
  wire mul1_mul_temp_i_16_n_0;
  wire mul1_mul_temp_i_17_n_0;
  wire mul1_mul_temp_i_1_n_0;
  wire mul1_mul_temp_i_2_n_0;
  wire mul1_mul_temp_i_3_n_0;
  wire mul1_mul_temp_i_4_n_0;
  wire mul1_mul_temp_i_5_n_0;
  wire mul1_mul_temp_i_6_n_0;
  wire mul1_mul_temp_i_7_n_0;
  wire [7:0]mul1_mul_temp_i_8_0;
  wire mul1_mul_temp_i_8_n_0;
  wire mul1_mul_temp_i_9_n_0;
  wire mul1_mul_temp_n_100;
  wire mul1_mul_temp_n_101;
  wire mul1_mul_temp_n_102;
  wire mul1_mul_temp_n_103;
  wire mul1_mul_temp_n_104;
  wire mul1_mul_temp_n_105;
  wire mul1_mul_temp_n_106;
  wire mul1_mul_temp_n_107;
  wire mul1_mul_temp_n_108;
  wire mul1_mul_temp_n_109;
  wire mul1_mul_temp_n_110;
  wire mul1_mul_temp_n_111;
  wire mul1_mul_temp_n_112;
  wire mul1_mul_temp_n_113;
  wire mul1_mul_temp_n_114;
  wire mul1_mul_temp_n_115;
  wire mul1_mul_temp_n_116;
  wire mul1_mul_temp_n_117;
  wire mul1_mul_temp_n_118;
  wire mul1_mul_temp_n_119;
  wire mul1_mul_temp_n_120;
  wire mul1_mul_temp_n_121;
  wire mul1_mul_temp_n_122;
  wire mul1_mul_temp_n_123;
  wire mul1_mul_temp_n_124;
  wire mul1_mul_temp_n_125;
  wire mul1_mul_temp_n_126;
  wire mul1_mul_temp_n_127;
  wire mul1_mul_temp_n_128;
  wire mul1_mul_temp_n_129;
  wire mul1_mul_temp_n_130;
  wire mul1_mul_temp_n_131;
  wire mul1_mul_temp_n_132;
  wire mul1_mul_temp_n_133;
  wire mul1_mul_temp_n_134;
  wire mul1_mul_temp_n_135;
  wire mul1_mul_temp_n_136;
  wire mul1_mul_temp_n_137;
  wire mul1_mul_temp_n_138;
  wire mul1_mul_temp_n_139;
  wire mul1_mul_temp_n_140;
  wire mul1_mul_temp_n_141;
  wire mul1_mul_temp_n_142;
  wire mul1_mul_temp_n_143;
  wire mul1_mul_temp_n_144;
  wire mul1_mul_temp_n_145;
  wire mul1_mul_temp_n_146;
  wire mul1_mul_temp_n_147;
  wire mul1_mul_temp_n_148;
  wire mul1_mul_temp_n_149;
  wire mul1_mul_temp_n_150;
  wire mul1_mul_temp_n_151;
  wire mul1_mul_temp_n_152;
  wire mul1_mul_temp_n_153;
  wire mul1_mul_temp_n_58;
  wire mul1_mul_temp_n_59;
  wire mul1_mul_temp_n_60;
  wire mul1_mul_temp_n_61;
  wire mul1_mul_temp_n_62;
  wire mul1_mul_temp_n_63;
  wire mul1_mul_temp_n_64;
  wire mul1_mul_temp_n_65;
  wire mul1_mul_temp_n_66;
  wire mul1_mul_temp_n_67;
  wire mul1_mul_temp_n_68;
  wire mul1_mul_temp_n_69;
  wire mul1_mul_temp_n_70;
  wire mul1_mul_temp_n_71;
  wire mul1_mul_temp_n_72;
  wire mul1_mul_temp_n_73;
  wire mul1_mul_temp_n_74;
  wire mul1_mul_temp_n_75;
  wire mul1_mul_temp_n_76;
  wire mul1_mul_temp_n_77;
  wire mul1_mul_temp_n_78;
  wire mul1_mul_temp_n_79;
  wire mul1_mul_temp_n_80;
  wire mul1_mul_temp_n_81;
  wire mul1_mul_temp_n_82;
  wire mul1_mul_temp_n_83;
  wire mul1_mul_temp_n_84;
  wire mul1_mul_temp_n_85;
  wire mul1_mul_temp_n_86;
  wire mul1_mul_temp_n_87;
  wire mul1_mul_temp_n_88;
  wire mul1_mul_temp_n_89;
  wire mul1_mul_temp_n_90;
  wire mul1_mul_temp_n_91;
  wire mul1_mul_temp_n_92;
  wire mul1_mul_temp_n_93;
  wire mul1_mul_temp_n_94;
  wire mul1_mul_temp_n_95;
  wire mul1_mul_temp_n_96;
  wire mul1_mul_temp_n_97;
  wire mul1_mul_temp_n_98;
  wire mul1_mul_temp_n_99;
  wire sel;
  wire subtractor_sub_temp_carry__0_n_0;
  wire subtractor_sub_temp_carry__0_n_1;
  wire subtractor_sub_temp_carry__0_n_10;
  wire subtractor_sub_temp_carry__0_n_11;
  wire subtractor_sub_temp_carry__0_n_12;
  wire subtractor_sub_temp_carry__0_n_13;
  wire subtractor_sub_temp_carry__0_n_14;
  wire subtractor_sub_temp_carry__0_n_15;
  wire subtractor_sub_temp_carry__0_n_2;
  wire subtractor_sub_temp_carry__0_n_3;
  wire subtractor_sub_temp_carry__0_n_4;
  wire subtractor_sub_temp_carry__0_n_5;
  wire subtractor_sub_temp_carry__0_n_6;
  wire subtractor_sub_temp_carry__0_n_7;
  wire subtractor_sub_temp_carry__0_n_8;
  wire subtractor_sub_temp_carry__0_n_9;
  wire subtractor_sub_temp_carry__1_n_0;
  wire subtractor_sub_temp_carry__1_n_1;
  wire subtractor_sub_temp_carry__1_n_10;
  wire subtractor_sub_temp_carry__1_n_11;
  wire subtractor_sub_temp_carry__1_n_12;
  wire subtractor_sub_temp_carry__1_n_13;
  wire subtractor_sub_temp_carry__1_n_14;
  wire subtractor_sub_temp_carry__1_n_15;
  wire subtractor_sub_temp_carry__1_n_2;
  wire subtractor_sub_temp_carry__1_n_3;
  wire subtractor_sub_temp_carry__1_n_4;
  wire subtractor_sub_temp_carry__1_n_5;
  wire subtractor_sub_temp_carry__1_n_6;
  wire subtractor_sub_temp_carry__1_n_7;
  wire subtractor_sub_temp_carry__1_n_8;
  wire subtractor_sub_temp_carry__1_n_9;
  wire subtractor_sub_temp_carry__2_n_0;
  wire subtractor_sub_temp_carry__2_n_10;
  wire subtractor_sub_temp_carry__2_n_11;
  wire subtractor_sub_temp_carry__2_n_12;
  wire subtractor_sub_temp_carry__2_n_13;
  wire subtractor_sub_temp_carry__2_n_14;
  wire subtractor_sub_temp_carry__2_n_15;
  wire subtractor_sub_temp_carry__2_n_2;
  wire subtractor_sub_temp_carry__2_n_3;
  wire subtractor_sub_temp_carry__2_n_4;
  wire subtractor_sub_temp_carry__2_n_5;
  wire subtractor_sub_temp_carry__2_n_6;
  wire subtractor_sub_temp_carry__2_n_7;
  wire subtractor_sub_temp_carry__2_n_9;
  wire subtractor_sub_temp_carry_n_0;
  wire subtractor_sub_temp_carry_n_1;
  wire subtractor_sub_temp_carry_n_10;
  wire subtractor_sub_temp_carry_n_11;
  wire subtractor_sub_temp_carry_n_12;
  wire subtractor_sub_temp_carry_n_13;
  wire subtractor_sub_temp_carry_n_14;
  wire subtractor_sub_temp_carry_n_15;
  wire subtractor_sub_temp_carry_n_2;
  wire subtractor_sub_temp_carry_n_3;
  wire subtractor_sub_temp_carry_n_4;
  wire subtractor_sub_temp_carry_n_5;
  wire subtractor_sub_temp_carry_n_6;
  wire subtractor_sub_temp_carry_n_7;
  wire subtractor_sub_temp_carry_n_8;
  wire subtractor_sub_temp_carry_n_9;
  wire write_axi_enable;
  wire NLW_mul1_mul_temp_CARRYCASCOUT_UNCONNECTED;
  wire NLW_mul1_mul_temp_MULTSIGNOUT_UNCONNECTED;
  wire NLW_mul1_mul_temp_OVERFLOW_UNCONNECTED;
  wire NLW_mul1_mul_temp_PATTERNBDETECT_UNCONNECTED;
  wire NLW_mul1_mul_temp_PATTERNDETECT_UNCONNECTED;
  wire NLW_mul1_mul_temp_UNDERFLOW_UNCONNECTED;
  wire [29:0]NLW_mul1_mul_temp_ACOUT_UNCONNECTED;
  wire [17:0]NLW_mul1_mul_temp_BCOUT_UNCONNECTED;
  wire [3:0]NLW_mul1_mul_temp_CARRYOUT_UNCONNECTED;
  wire [7:0]NLW_mul1_mul_temp_XOROUT_UNCONNECTED;
  wire NLW_mul1_mul_temp__0_CARRYCASCOUT_UNCONNECTED;
  wire NLW_mul1_mul_temp__0_MULTSIGNOUT_UNCONNECTED;
  wire NLW_mul1_mul_temp__0_OVERFLOW_UNCONNECTED;
  wire NLW_mul1_mul_temp__0_PATTERNBDETECT_UNCONNECTED;
  wire NLW_mul1_mul_temp__0_PATTERNDETECT_UNCONNECTED;
  wire NLW_mul1_mul_temp__0_UNDERFLOW_UNCONNECTED;
  wire [29:0]NLW_mul1_mul_temp__0_ACOUT_UNCONNECTED;
  wire [17:0]NLW_mul1_mul_temp__0_BCOUT_UNCONNECTED;
  wire [3:0]NLW_mul1_mul_temp__0_CARRYOUT_UNCONNECTED;
  wire [47:30]NLW_mul1_mul_temp__0_P_UNCONNECTED;
  wire [47:0]NLW_mul1_mul_temp__0_PCOUT_UNCONNECTED;
  wire [7:0]NLW_mul1_mul_temp__0_XOROUT_UNCONNECTED;
  wire NLW_mul1_mul_temp__1_CARRYCASCOUT_UNCONNECTED;
  wire NLW_mul1_mul_temp__1_MULTSIGNOUT_UNCONNECTED;
  wire NLW_mul1_mul_temp__1_OVERFLOW_UNCONNECTED;
  wire NLW_mul1_mul_temp__1_PATTERNBDETECT_UNCONNECTED;
  wire NLW_mul1_mul_temp__1_PATTERNDETECT_UNCONNECTED;
  wire NLW_mul1_mul_temp__1_UNDERFLOW_UNCONNECTED;
  wire [29:0]NLW_mul1_mul_temp__1_ACOUT_UNCONNECTED;
  wire [17:0]NLW_mul1_mul_temp__1_BCOUT_UNCONNECTED;
  wire [3:0]NLW_mul1_mul_temp__1_CARRYOUT_UNCONNECTED;
  wire [7:0]NLW_mul1_mul_temp__1_XOROUT_UNCONNECTED;
  wire NLW_mul1_mul_temp__2_CARRYCASCOUT_UNCONNECTED;
  wire NLW_mul1_mul_temp__2_MULTSIGNOUT_UNCONNECTED;
  wire NLW_mul1_mul_temp__2_OVERFLOW_UNCONNECTED;
  wire NLW_mul1_mul_temp__2_PATTERNBDETECT_UNCONNECTED;
  wire NLW_mul1_mul_temp__2_PATTERNDETECT_UNCONNECTED;
  wire NLW_mul1_mul_temp__2_UNDERFLOW_UNCONNECTED;
  wire [29:0]NLW_mul1_mul_temp__2_ACOUT_UNCONNECTED;
  wire [17:0]NLW_mul1_mul_temp__2_BCOUT_UNCONNECTED;
  wire [3:0]NLW_mul1_mul_temp__2_CARRYOUT_UNCONNECTED;
  wire [47:47]NLW_mul1_mul_temp__2_P_UNCONNECTED;
  wire [47:0]NLW_mul1_mul_temp__2_PCOUT_UNCONNECTED;
  wire [7:0]NLW_mul1_mul_temp__2_XOROUT_UNCONNECTED;
  wire [7:0]NLW_mul1_mul_temp_carry_O_UNCONNECTED;
  wire [5:0]NLW_mul1_mul_temp_carry__0_O_UNCONNECTED;
  wire [7:7]NLW_mul1_mul_temp_carry__4_CO_UNCONNECTED;
  wire [6:6]NLW_subtractor_sub_temp_carry__2_CO_UNCONNECTED;
  wire [7:7]NLW_subtractor_sub_temp_carry__2_O_UNCONNECTED;

  FDRE \aout_tmp_reg[10] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\aout_tmp_reg[31]_1 [8]),
        .Q(\aout_tmp_reg[31]_0 [8]),
        .R(RSTP));
  FDRE \aout_tmp_reg[11] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\aout_tmp_reg[31]_1 [9]),
        .Q(\aout_tmp_reg[31]_0 [9]),
        .R(RSTP));
  FDRE \aout_tmp_reg[12] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\aout_tmp_reg[31]_1 [10]),
        .Q(\aout_tmp_reg[31]_0 [10]),
        .R(RSTP));
  FDRE \aout_tmp_reg[13] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\aout_tmp_reg[31]_1 [11]),
        .Q(\aout_tmp_reg[31]_0 [11]),
        .R(RSTP));
  FDRE \aout_tmp_reg[14] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\aout_tmp_reg[31]_1 [12]),
        .Q(\aout_tmp_reg[31]_0 [12]),
        .R(RSTP));
  FDRE \aout_tmp_reg[15] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\aout_tmp_reg[31]_1 [13]),
        .Q(\aout_tmp_reg[31]_0 [13]),
        .R(RSTP));
  FDRE \aout_tmp_reg[16] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\aout_tmp_reg[31]_1 [14]),
        .Q(\aout_tmp_reg[31]_0 [14]),
        .R(RSTP));
  FDRE \aout_tmp_reg[17] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\aout_tmp_reg[31]_1 [15]),
        .Q(\aout_tmp_reg[31]_0 [15]),
        .R(RSTP));
  FDRE \aout_tmp_reg[18] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\aout_tmp_reg[31]_1 [16]),
        .Q(\aout_tmp_reg[31]_0 [16]),
        .R(RSTP));
  FDRE \aout_tmp_reg[19] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\aout_tmp_reg[31]_1 [17]),
        .Q(\aout_tmp_reg[31]_0 [17]),
        .R(RSTP));
  FDRE \aout_tmp_reg[20] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\aout_tmp_reg[31]_1 [18]),
        .Q(\aout_tmp_reg[31]_0 [18]),
        .R(RSTP));
  FDRE \aout_tmp_reg[21] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\aout_tmp_reg[31]_1 [19]),
        .Q(\aout_tmp_reg[31]_0 [19]),
        .R(RSTP));
  FDRE \aout_tmp_reg[22] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\aout_tmp_reg[31]_1 [20]),
        .Q(\aout_tmp_reg[31]_0 [20]),
        .R(RSTP));
  FDRE \aout_tmp_reg[23] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\aout_tmp_reg[31]_1 [21]),
        .Q(\aout_tmp_reg[31]_0 [21]),
        .R(RSTP));
  FDRE \aout_tmp_reg[24] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\aout_tmp_reg[31]_1 [22]),
        .Q(\aout_tmp_reg[31]_0 [22]),
        .R(RSTP));
  FDRE \aout_tmp_reg[25] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\aout_tmp_reg[31]_1 [23]),
        .Q(\aout_tmp_reg[31]_0 [23]),
        .R(RSTP));
  FDRE \aout_tmp_reg[26] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\aout_tmp_reg[31]_1 [24]),
        .Q(\aout_tmp_reg[31]_0 [24]),
        .R(RSTP));
  FDRE \aout_tmp_reg[27] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\aout_tmp_reg[31]_1 [25]),
        .Q(\aout_tmp_reg[31]_0 [25]),
        .R(RSTP));
  FDRE \aout_tmp_reg[28] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\aout_tmp_reg[31]_1 [26]),
        .Q(\aout_tmp_reg[31]_0 [26]),
        .R(RSTP));
  FDRE \aout_tmp_reg[29] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\aout_tmp_reg[31]_1 [27]),
        .Q(\aout_tmp_reg[31]_0 [27]),
        .R(RSTP));
  FDRE \aout_tmp_reg[2] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\aout_tmp_reg[31]_1 [0]),
        .Q(\aout_tmp_reg[31]_0 [0]),
        .R(RSTP));
  FDRE \aout_tmp_reg[30] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\aout_tmp_reg[31]_1 [28]),
        .Q(\aout_tmp_reg[31]_0 [28]),
        .R(RSTP));
  FDRE \aout_tmp_reg[31] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\aout_tmp_reg[31]_1 [29]),
        .Q(\aout_tmp_reg[31]_0 [29]),
        .R(RSTP));
  FDRE \aout_tmp_reg[3] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\aout_tmp_reg[31]_1 [1]),
        .Q(\aout_tmp_reg[31]_0 [1]),
        .R(RSTP));
  FDRE \aout_tmp_reg[4] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\aout_tmp_reg[31]_1 [2]),
        .Q(\aout_tmp_reg[31]_0 [2]),
        .R(RSTP));
  FDRE \aout_tmp_reg[5] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\aout_tmp_reg[31]_1 [3]),
        .Q(\aout_tmp_reg[31]_0 [3]),
        .R(RSTP));
  FDRE \aout_tmp_reg[6] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\aout_tmp_reg[31]_1 [4]),
        .Q(\aout_tmp_reg[31]_0 [4]),
        .R(RSTP));
  FDRE \aout_tmp_reg[7] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\aout_tmp_reg[31]_1 [5]),
        .Q(\aout_tmp_reg[31]_0 [5]),
        .R(RSTP));
  FDRE \aout_tmp_reg[8] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\aout_tmp_reg[31]_1 [6]),
        .Q(\aout_tmp_reg[31]_0 [6]),
        .R(RSTP));
  FDRE \aout_tmp_reg[9] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\aout_tmp_reg[31]_1 [7]),
        .Q(\aout_tmp_reg[31]_0 [7]),
        .R(RSTP));
  (* SOFT_HLUTNM = "soft_lutpair36" *) 
  LUT3 #(
    .INIT(8'hFE)) 
    \delayout[0]_i_1 
       (.I0(mul1_mul_temp_carry__4_n_9),
        .I1(mul1_mul_temp_carry__4_n_8),
        .I2(mul1_mul_temp_carry__0_n_9),
        .O(mul1_mul_temp_carry__4_0[0]));
  (* SOFT_HLUTNM = "soft_lutpair31" *) 
  LUT3 #(
    .INIT(8'hFE)) 
    \delayout[10]_i_1 
       (.I0(mul1_mul_temp_carry__4_n_9),
        .I1(mul1_mul_temp_carry__4_n_8),
        .I2(mul1_mul_temp_carry__2_n_15),
        .O(mul1_mul_temp_carry__4_0[10]));
  (* SOFT_HLUTNM = "soft_lutpair31" *) 
  LUT3 #(
    .INIT(8'hFE)) 
    \delayout[11]_i_1 
       (.I0(mul1_mul_temp_carry__4_n_9),
        .I1(mul1_mul_temp_carry__4_n_8),
        .I2(mul1_mul_temp_carry__2_n_14),
        .O(mul1_mul_temp_carry__4_0[11]));
  (* SOFT_HLUTNM = "soft_lutpair30" *) 
  LUT3 #(
    .INIT(8'hFE)) 
    \delayout[12]_i_1 
       (.I0(mul1_mul_temp_carry__4_n_9),
        .I1(mul1_mul_temp_carry__4_n_8),
        .I2(mul1_mul_temp_carry__2_n_13),
        .O(mul1_mul_temp_carry__4_0[12]));
  (* SOFT_HLUTNM = "soft_lutpair30" *) 
  LUT3 #(
    .INIT(8'hFE)) 
    \delayout[13]_i_1 
       (.I0(mul1_mul_temp_carry__4_n_9),
        .I1(mul1_mul_temp_carry__4_n_8),
        .I2(mul1_mul_temp_carry__2_n_12),
        .O(mul1_mul_temp_carry__4_0[13]));
  (* SOFT_HLUTNM = "soft_lutpair29" *) 
  LUT3 #(
    .INIT(8'hFE)) 
    \delayout[14]_i_1 
       (.I0(mul1_mul_temp_carry__4_n_9),
        .I1(mul1_mul_temp_carry__4_n_8),
        .I2(mul1_mul_temp_carry__2_n_11),
        .O(mul1_mul_temp_carry__4_0[14]));
  (* SOFT_HLUTNM = "soft_lutpair29" *) 
  LUT3 #(
    .INIT(8'hFE)) 
    \delayout[15]_i_1 
       (.I0(mul1_mul_temp_carry__4_n_9),
        .I1(mul1_mul_temp_carry__4_n_8),
        .I2(mul1_mul_temp_carry__2_n_10),
        .O(mul1_mul_temp_carry__4_0[15]));
  (* SOFT_HLUTNM = "soft_lutpair28" *) 
  LUT3 #(
    .INIT(8'hFE)) 
    \delayout[16]_i_1 
       (.I0(mul1_mul_temp_carry__4_n_9),
        .I1(mul1_mul_temp_carry__4_n_8),
        .I2(mul1_mul_temp_carry__2_n_9),
        .O(mul1_mul_temp_carry__4_0[16]));
  (* SOFT_HLUTNM = "soft_lutpair28" *) 
  LUT3 #(
    .INIT(8'hFE)) 
    \delayout[17]_i_1 
       (.I0(mul1_mul_temp_carry__4_n_9),
        .I1(mul1_mul_temp_carry__4_n_8),
        .I2(mul1_mul_temp_carry__2_n_8),
        .O(mul1_mul_temp_carry__4_0[17]));
  (* SOFT_HLUTNM = "soft_lutpair27" *) 
  LUT3 #(
    .INIT(8'hFE)) 
    \delayout[18]_i_1 
       (.I0(mul1_mul_temp_carry__4_n_9),
        .I1(mul1_mul_temp_carry__4_n_8),
        .I2(mul1_mul_temp_carry__3_n_15),
        .O(mul1_mul_temp_carry__4_0[18]));
  (* SOFT_HLUTNM = "soft_lutpair27" *) 
  LUT3 #(
    .INIT(8'hFE)) 
    \delayout[19]_i_1 
       (.I0(mul1_mul_temp_carry__4_n_9),
        .I1(mul1_mul_temp_carry__4_n_8),
        .I2(mul1_mul_temp_carry__3_n_14),
        .O(mul1_mul_temp_carry__4_0[19]));
  (* SOFT_HLUTNM = "soft_lutpair36" *) 
  LUT3 #(
    .INIT(8'hFE)) 
    \delayout[1]_i_1 
       (.I0(mul1_mul_temp_carry__4_n_9),
        .I1(mul1_mul_temp_carry__4_n_8),
        .I2(mul1_mul_temp_carry__0_n_8),
        .O(mul1_mul_temp_carry__4_0[1]));
  (* SOFT_HLUTNM = "soft_lutpair26" *) 
  LUT3 #(
    .INIT(8'hFE)) 
    \delayout[20]_i_1 
       (.I0(mul1_mul_temp_carry__4_n_9),
        .I1(mul1_mul_temp_carry__4_n_8),
        .I2(mul1_mul_temp_carry__3_n_13),
        .O(mul1_mul_temp_carry__4_0[20]));
  (* SOFT_HLUTNM = "soft_lutpair26" *) 
  LUT3 #(
    .INIT(8'hFE)) 
    \delayout[21]_i_1 
       (.I0(mul1_mul_temp_carry__4_n_9),
        .I1(mul1_mul_temp_carry__4_n_8),
        .I2(mul1_mul_temp_carry__3_n_12),
        .O(mul1_mul_temp_carry__4_0[21]));
  (* SOFT_HLUTNM = "soft_lutpair25" *) 
  LUT3 #(
    .INIT(8'hFE)) 
    \delayout[22]_i_1 
       (.I0(mul1_mul_temp_carry__4_n_9),
        .I1(mul1_mul_temp_carry__4_n_8),
        .I2(mul1_mul_temp_carry__3_n_11),
        .O(mul1_mul_temp_carry__4_0[22]));
  (* SOFT_HLUTNM = "soft_lutpair25" *) 
  LUT3 #(
    .INIT(8'hFE)) 
    \delayout[23]_i_1 
       (.I0(mul1_mul_temp_carry__4_n_9),
        .I1(mul1_mul_temp_carry__4_n_8),
        .I2(mul1_mul_temp_carry__3_n_10),
        .O(mul1_mul_temp_carry__4_0[23]));
  (* SOFT_HLUTNM = "soft_lutpair24" *) 
  LUT3 #(
    .INIT(8'hFE)) 
    \delayout[24]_i_1 
       (.I0(mul1_mul_temp_carry__4_n_9),
        .I1(mul1_mul_temp_carry__4_n_8),
        .I2(mul1_mul_temp_carry__3_n_9),
        .O(mul1_mul_temp_carry__4_0[24]));
  (* SOFT_HLUTNM = "soft_lutpair24" *) 
  LUT3 #(
    .INIT(8'hFE)) 
    \delayout[25]_i_1 
       (.I0(mul1_mul_temp_carry__4_n_9),
        .I1(mul1_mul_temp_carry__4_n_8),
        .I2(mul1_mul_temp_carry__3_n_8),
        .O(mul1_mul_temp_carry__4_0[25]));
  (* SOFT_HLUTNM = "soft_lutpair23" *) 
  LUT3 #(
    .INIT(8'hFE)) 
    \delayout[26]_i_1 
       (.I0(mul1_mul_temp_carry__4_n_9),
        .I1(mul1_mul_temp_carry__4_n_8),
        .I2(mul1_mul_temp_carry__4_n_15),
        .O(mul1_mul_temp_carry__4_0[26]));
  (* SOFT_HLUTNM = "soft_lutpair23" *) 
  LUT3 #(
    .INIT(8'hFE)) 
    \delayout[27]_i_1 
       (.I0(mul1_mul_temp_carry__4_n_9),
        .I1(mul1_mul_temp_carry__4_n_8),
        .I2(mul1_mul_temp_carry__4_n_14),
        .O(mul1_mul_temp_carry__4_0[27]));
  (* SOFT_HLUTNM = "soft_lutpair22" *) 
  LUT3 #(
    .INIT(8'hFE)) 
    \delayout[28]_i_1 
       (.I0(mul1_mul_temp_carry__4_n_9),
        .I1(mul1_mul_temp_carry__4_n_8),
        .I2(mul1_mul_temp_carry__4_n_13),
        .O(mul1_mul_temp_carry__4_0[28]));
  (* SOFT_HLUTNM = "soft_lutpair22" *) 
  LUT3 #(
    .INIT(8'hFE)) 
    \delayout[29]_i_1 
       (.I0(mul1_mul_temp_carry__4_n_9),
        .I1(mul1_mul_temp_carry__4_n_8),
        .I2(mul1_mul_temp_carry__4_n_12),
        .O(mul1_mul_temp_carry__4_0[29]));
  (* SOFT_HLUTNM = "soft_lutpair35" *) 
  LUT3 #(
    .INIT(8'hFE)) 
    \delayout[2]_i_1 
       (.I0(mul1_mul_temp_carry__4_n_9),
        .I1(mul1_mul_temp_carry__4_n_8),
        .I2(mul1_mul_temp_carry__1_n_15),
        .O(mul1_mul_temp_carry__4_0[2]));
  (* SOFT_HLUTNM = "soft_lutpair21" *) 
  LUT3 #(
    .INIT(8'hFE)) 
    \delayout[30]_i_1 
       (.I0(mul1_mul_temp_carry__4_n_9),
        .I1(mul1_mul_temp_carry__4_n_8),
        .I2(mul1_mul_temp_carry__4_n_11),
        .O(mul1_mul_temp_carry__4_0[30]));
  (* SOFT_HLUTNM = "soft_lutpair21" *) 
  LUT3 #(
    .INIT(8'hFE)) 
    \delayout[31]_i_1 
       (.I0(mul1_mul_temp_carry__4_n_9),
        .I1(mul1_mul_temp_carry__4_n_8),
        .I2(mul1_mul_temp_carry__4_n_10),
        .O(mul1_mul_temp_carry__4_0[31]));
  (* SOFT_HLUTNM = "soft_lutpair35" *) 
  LUT3 #(
    .INIT(8'hFE)) 
    \delayout[3]_i_1 
       (.I0(mul1_mul_temp_carry__4_n_9),
        .I1(mul1_mul_temp_carry__4_n_8),
        .I2(mul1_mul_temp_carry__1_n_14),
        .O(mul1_mul_temp_carry__4_0[3]));
  (* SOFT_HLUTNM = "soft_lutpair34" *) 
  LUT3 #(
    .INIT(8'hFE)) 
    \delayout[4]_i_1 
       (.I0(mul1_mul_temp_carry__4_n_9),
        .I1(mul1_mul_temp_carry__4_n_8),
        .I2(mul1_mul_temp_carry__1_n_13),
        .O(mul1_mul_temp_carry__4_0[4]));
  (* SOFT_HLUTNM = "soft_lutpair34" *) 
  LUT3 #(
    .INIT(8'hFE)) 
    \delayout[5]_i_1 
       (.I0(mul1_mul_temp_carry__4_n_9),
        .I1(mul1_mul_temp_carry__4_n_8),
        .I2(mul1_mul_temp_carry__1_n_12),
        .O(mul1_mul_temp_carry__4_0[5]));
  (* SOFT_HLUTNM = "soft_lutpair33" *) 
  LUT3 #(
    .INIT(8'hFE)) 
    \delayout[6]_i_1 
       (.I0(mul1_mul_temp_carry__4_n_9),
        .I1(mul1_mul_temp_carry__4_n_8),
        .I2(mul1_mul_temp_carry__1_n_11),
        .O(mul1_mul_temp_carry__4_0[6]));
  (* SOFT_HLUTNM = "soft_lutpair33" *) 
  LUT3 #(
    .INIT(8'hFE)) 
    \delayout[7]_i_1 
       (.I0(mul1_mul_temp_carry__4_n_9),
        .I1(mul1_mul_temp_carry__4_n_8),
        .I2(mul1_mul_temp_carry__1_n_10),
        .O(mul1_mul_temp_carry__4_0[7]));
  (* SOFT_HLUTNM = "soft_lutpair32" *) 
  LUT3 #(
    .INIT(8'hFE)) 
    \delayout[8]_i_1 
       (.I0(mul1_mul_temp_carry__4_n_9),
        .I1(mul1_mul_temp_carry__4_n_8),
        .I2(mul1_mul_temp_carry__1_n_9),
        .O(mul1_mul_temp_carry__4_0[8]));
  (* SOFT_HLUTNM = "soft_lutpair32" *) 
  LUT3 #(
    .INIT(8'hFE)) 
    \delayout[9]_i_1 
       (.I0(mul1_mul_temp_carry__4_n_9),
        .I1(mul1_mul_temp_carry__4_n_8),
        .I2(mul1_mul_temp_carry__1_n_8),
        .O(mul1_mul_temp_carry__4_0[9]));
  FDRE \delayout_reg[0] 
       (.C(IPCORE_CLK),
        .CE(write_axi_enable),
        .D(mul1_mul_temp_carry__4_0[0]),
        .Q(Q[0]),
        .R(RSTP));
  FDRE \delayout_reg[10] 
       (.C(IPCORE_CLK),
        .CE(write_axi_enable),
        .D(mul1_mul_temp_carry__4_0[10]),
        .Q(Q[10]),
        .R(RSTP));
  FDRE \delayout_reg[11] 
       (.C(IPCORE_CLK),
        .CE(write_axi_enable),
        .D(mul1_mul_temp_carry__4_0[11]),
        .Q(Q[11]),
        .R(RSTP));
  FDRE \delayout_reg[12] 
       (.C(IPCORE_CLK),
        .CE(write_axi_enable),
        .D(mul1_mul_temp_carry__4_0[12]),
        .Q(Q[12]),
        .R(RSTP));
  FDRE \delayout_reg[13] 
       (.C(IPCORE_CLK),
        .CE(write_axi_enable),
        .D(mul1_mul_temp_carry__4_0[13]),
        .Q(Q[13]),
        .R(RSTP));
  FDRE \delayout_reg[14] 
       (.C(IPCORE_CLK),
        .CE(write_axi_enable),
        .D(mul1_mul_temp_carry__4_0[14]),
        .Q(Q[14]),
        .R(RSTP));
  FDRE \delayout_reg[15] 
       (.C(IPCORE_CLK),
        .CE(write_axi_enable),
        .D(mul1_mul_temp_carry__4_0[15]),
        .Q(Q[15]),
        .R(RSTP));
  FDRE \delayout_reg[16] 
       (.C(IPCORE_CLK),
        .CE(write_axi_enable),
        .D(mul1_mul_temp_carry__4_0[16]),
        .Q(Q[16]),
        .R(RSTP));
  FDRE \delayout_reg[17] 
       (.C(IPCORE_CLK),
        .CE(write_axi_enable),
        .D(mul1_mul_temp_carry__4_0[17]),
        .Q(Q[17]),
        .R(RSTP));
  FDRE \delayout_reg[18] 
       (.C(IPCORE_CLK),
        .CE(write_axi_enable),
        .D(mul1_mul_temp_carry__4_0[18]),
        .Q(Q[18]),
        .R(RSTP));
  FDRE \delayout_reg[19] 
       (.C(IPCORE_CLK),
        .CE(write_axi_enable),
        .D(mul1_mul_temp_carry__4_0[19]),
        .Q(Q[19]),
        .R(RSTP));
  FDRE \delayout_reg[1] 
       (.C(IPCORE_CLK),
        .CE(write_axi_enable),
        .D(mul1_mul_temp_carry__4_0[1]),
        .Q(Q[1]),
        .R(RSTP));
  FDRE \delayout_reg[20] 
       (.C(IPCORE_CLK),
        .CE(write_axi_enable),
        .D(mul1_mul_temp_carry__4_0[20]),
        .Q(Q[20]),
        .R(RSTP));
  FDRE \delayout_reg[21] 
       (.C(IPCORE_CLK),
        .CE(write_axi_enable),
        .D(mul1_mul_temp_carry__4_0[21]),
        .Q(Q[21]),
        .R(RSTP));
  FDRE \delayout_reg[22] 
       (.C(IPCORE_CLK),
        .CE(write_axi_enable),
        .D(mul1_mul_temp_carry__4_0[22]),
        .Q(Q[22]),
        .R(RSTP));
  FDRE \delayout_reg[23] 
       (.C(IPCORE_CLK),
        .CE(write_axi_enable),
        .D(mul1_mul_temp_carry__4_0[23]),
        .Q(Q[23]),
        .R(RSTP));
  FDRE \delayout_reg[24] 
       (.C(IPCORE_CLK),
        .CE(write_axi_enable),
        .D(mul1_mul_temp_carry__4_0[24]),
        .Q(Q[24]),
        .R(RSTP));
  FDRE \delayout_reg[25] 
       (.C(IPCORE_CLK),
        .CE(write_axi_enable),
        .D(mul1_mul_temp_carry__4_0[25]),
        .Q(Q[25]),
        .R(RSTP));
  FDRE \delayout_reg[26] 
       (.C(IPCORE_CLK),
        .CE(write_axi_enable),
        .D(mul1_mul_temp_carry__4_0[26]),
        .Q(Q[26]),
        .R(RSTP));
  FDRE \delayout_reg[27] 
       (.C(IPCORE_CLK),
        .CE(write_axi_enable),
        .D(mul1_mul_temp_carry__4_0[27]),
        .Q(Q[27]),
        .R(RSTP));
  FDRE \delayout_reg[28] 
       (.C(IPCORE_CLK),
        .CE(write_axi_enable),
        .D(mul1_mul_temp_carry__4_0[28]),
        .Q(Q[28]),
        .R(RSTP));
  FDRE \delayout_reg[29] 
       (.C(IPCORE_CLK),
        .CE(write_axi_enable),
        .D(mul1_mul_temp_carry__4_0[29]),
        .Q(Q[29]),
        .R(RSTP));
  FDRE \delayout_reg[2] 
       (.C(IPCORE_CLK),
        .CE(write_axi_enable),
        .D(mul1_mul_temp_carry__4_0[2]),
        .Q(Q[2]),
        .R(RSTP));
  FDRE \delayout_reg[30] 
       (.C(IPCORE_CLK),
        .CE(write_axi_enable),
        .D(mul1_mul_temp_carry__4_0[30]),
        .Q(Q[30]),
        .R(RSTP));
  FDRE \delayout_reg[31] 
       (.C(IPCORE_CLK),
        .CE(write_axi_enable),
        .D(mul1_mul_temp_carry__4_0[31]),
        .Q(Q[31]),
        .R(RSTP));
  FDRE \delayout_reg[3] 
       (.C(IPCORE_CLK),
        .CE(write_axi_enable),
        .D(mul1_mul_temp_carry__4_0[3]),
        .Q(Q[3]),
        .R(RSTP));
  FDRE \delayout_reg[4] 
       (.C(IPCORE_CLK),
        .CE(write_axi_enable),
        .D(mul1_mul_temp_carry__4_0[4]),
        .Q(Q[4]),
        .R(RSTP));
  FDRE \delayout_reg[5] 
       (.C(IPCORE_CLK),
        .CE(write_axi_enable),
        .D(mul1_mul_temp_carry__4_0[5]),
        .Q(Q[5]),
        .R(RSTP));
  FDRE \delayout_reg[6] 
       (.C(IPCORE_CLK),
        .CE(write_axi_enable),
        .D(mul1_mul_temp_carry__4_0[6]),
        .Q(Q[6]),
        .R(RSTP));
  FDRE \delayout_reg[7] 
       (.C(IPCORE_CLK),
        .CE(write_axi_enable),
        .D(mul1_mul_temp_carry__4_0[7]),
        .Q(Q[7]),
        .R(RSTP));
  FDRE \delayout_reg[8] 
       (.C(IPCORE_CLK),
        .CE(write_axi_enable),
        .D(mul1_mul_temp_carry__4_0[8]),
        .Q(Q[8]),
        .R(RSTP));
  FDRE \delayout_reg[9] 
       (.C(IPCORE_CLK),
        .CE(write_axi_enable),
        .D(mul1_mul_temp_carry__4_0[9]),
        .Q(Q[9]),
        .R(RSTP));
  (* KEEP_HIERARCHY = "yes" *) 
  (* METHODOLOGY_DRC_VIOS = "{SYNTH-10 {cell *THIS*} {string 16x18 4}}" *) 
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
    .CREG(1),
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
    mul1_mul_temp
       (.A({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,mul1_mul_temp_i_1_n_0,mul1_mul_temp_i_2_n_0,mul1_mul_temp_i_3_n_0,mul1_mul_temp_i_4_n_0,mul1_mul_temp_i_5_n_0,mul1_mul_temp_i_6_n_0,mul1_mul_temp_i_7_n_0,mul1_mul_temp_i_8_n_0,mul1_mul_temp_i_9_n_0,mul1_mul_temp_i_10_n_0,mul1_mul_temp_i_11_n_0,mul1_mul_temp_i_12_n_0,mul1_mul_temp_i_13_n_0,mul1_mul_temp_i_14_n_0,mul1_mul_temp_i_15_n_0,mul1_mul_temp_i_16_n_0,mul1_mul_temp_i_17_n_0}),
        .ACIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .ACOUT(NLW_mul1_mul_temp_ACOUT_UNCONNECTED[29:0]),
        .ALUMODE({1'b0,1'b0,1'b0,1'b0}),
        .B({1'b0,1'b0,1'b0,D[31:17]}),
        .BCIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .BCOUT(NLW_mul1_mul_temp_BCOUT_UNCONNECTED[17:0]),
        .C({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .CARRYCASCIN(1'b0),
        .CARRYCASCOUT(NLW_mul1_mul_temp_CARRYCASCOUT_UNCONNECTED),
        .CARRYIN(1'b0),
        .CARRYINSEL({1'b0,1'b0,1'b0}),
        .CARRYOUT(NLW_mul1_mul_temp_CARRYOUT_UNCONNECTED[3:0]),
        .CEA1(1'b0),
        .CEA2(1'b0),
        .CEAD(1'b0),
        .CEALUMODE(1'b0),
        .CEB1(1'b0),
        .CEB2(CEP),
        .CEC(1'b0),
        .CECARRYIN(1'b0),
        .CECTRL(1'b0),
        .CED(1'b0),
        .CEINMODE(1'b0),
        .CEM(1'b0),
        .CEP(1'b0),
        .CLK(IPCORE_CLK),
        .D({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .INMODE({1'b0,1'b0,1'b0,1'b0,1'b0}),
        .MULTSIGNIN(1'b0),
        .MULTSIGNOUT(NLW_mul1_mul_temp_MULTSIGNOUT_UNCONNECTED),
        .OPMODE({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b1,1'b0,1'b1}),
        .OVERFLOW(NLW_mul1_mul_temp_OVERFLOW_UNCONNECTED),
        .P({mul1_mul_temp_n_58,mul1_mul_temp_n_59,mul1_mul_temp_n_60,mul1_mul_temp_n_61,mul1_mul_temp_n_62,mul1_mul_temp_n_63,mul1_mul_temp_n_64,mul1_mul_temp_n_65,mul1_mul_temp_n_66,mul1_mul_temp_n_67,mul1_mul_temp_n_68,mul1_mul_temp_n_69,mul1_mul_temp_n_70,mul1_mul_temp_n_71,mul1_mul_temp_n_72,mul1_mul_temp_n_73,mul1_mul_temp_n_74,mul1_mul_temp_n_75,mul1_mul_temp_n_76,mul1_mul_temp_n_77,mul1_mul_temp_n_78,mul1_mul_temp_n_79,mul1_mul_temp_n_80,mul1_mul_temp_n_81,mul1_mul_temp_n_82,mul1_mul_temp_n_83,mul1_mul_temp_n_84,mul1_mul_temp_n_85,mul1_mul_temp_n_86,mul1_mul_temp_n_87,mul1_mul_temp_n_88,mul1_mul_temp_n_89,mul1_mul_temp_n_90,mul1_mul_temp_n_91,mul1_mul_temp_n_92,mul1_mul_temp_n_93,mul1_mul_temp_n_94,mul1_mul_temp_n_95,mul1_mul_temp_n_96,mul1_mul_temp_n_97,mul1_mul_temp_n_98,mul1_mul_temp_n_99,mul1_mul_temp_n_100,mul1_mul_temp_n_101,mul1_mul_temp_n_102,mul1_mul_temp_n_103,mul1_mul_temp_n_104,mul1_mul_temp_n_105}),
        .PATTERNBDETECT(NLW_mul1_mul_temp_PATTERNBDETECT_UNCONNECTED),
        .PATTERNDETECT(NLW_mul1_mul_temp_PATTERNDETECT_UNCONNECTED),
        .PCIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .PCOUT({mul1_mul_temp_n_106,mul1_mul_temp_n_107,mul1_mul_temp_n_108,mul1_mul_temp_n_109,mul1_mul_temp_n_110,mul1_mul_temp_n_111,mul1_mul_temp_n_112,mul1_mul_temp_n_113,mul1_mul_temp_n_114,mul1_mul_temp_n_115,mul1_mul_temp_n_116,mul1_mul_temp_n_117,mul1_mul_temp_n_118,mul1_mul_temp_n_119,mul1_mul_temp_n_120,mul1_mul_temp_n_121,mul1_mul_temp_n_122,mul1_mul_temp_n_123,mul1_mul_temp_n_124,mul1_mul_temp_n_125,mul1_mul_temp_n_126,mul1_mul_temp_n_127,mul1_mul_temp_n_128,mul1_mul_temp_n_129,mul1_mul_temp_n_130,mul1_mul_temp_n_131,mul1_mul_temp_n_132,mul1_mul_temp_n_133,mul1_mul_temp_n_134,mul1_mul_temp_n_135,mul1_mul_temp_n_136,mul1_mul_temp_n_137,mul1_mul_temp_n_138,mul1_mul_temp_n_139,mul1_mul_temp_n_140,mul1_mul_temp_n_141,mul1_mul_temp_n_142,mul1_mul_temp_n_143,mul1_mul_temp_n_144,mul1_mul_temp_n_145,mul1_mul_temp_n_146,mul1_mul_temp_n_147,mul1_mul_temp_n_148,mul1_mul_temp_n_149,mul1_mul_temp_n_150,mul1_mul_temp_n_151,mul1_mul_temp_n_152,mul1_mul_temp_n_153}),
        .RSTA(1'b0),
        .RSTALLCARRYIN(1'b0),
        .RSTALUMODE(1'b0),
        .RSTB(RSTP),
        .RSTC(1'b0),
        .RSTCTRL(1'b0),
        .RSTD(1'b0),
        .RSTINMODE(1'b0),
        .RSTM(1'b0),
        .RSTP(1'b0),
        .UNDERFLOW(NLW_mul1_mul_temp_UNDERFLOW_UNCONNECTED),
        .XOROUT(NLW_mul1_mul_temp_XOROUT_UNCONNECTED[7:0]));
  (* KEEP_HIERARCHY = "yes" *) 
  (* METHODOLOGY_DRC_VIOS = "{SYNTH-10 {cell *THIS*} {string 16x16 4}}" *) 
  DSP48E2 #(
    .ACASCREG(1),
    .ADREG(1),
    .ALUMODEREG(0),
    .AMULTSEL("A"),
    .AREG(1),
    .AUTORESET_PATDET("NO_RESET"),
    .AUTORESET_PRIORITY("RESET"),
    .A_INPUT("DIRECT"),
    .BCASCREG(0),
    .BMULTSEL("B"),
    .BREG(0),
    .B_INPUT("DIRECT"),
    .CARRYINREG(0),
    .CARRYINSELREG(0),
    .CREG(1),
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
    mul1_mul_temp__0
       (.A({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,D[31:17]}),
        .ACIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .ACOUT(NLW_mul1_mul_temp__0_ACOUT_UNCONNECTED[29:0]),
        .ALUMODE({1'b0,1'b0,1'b0,1'b0}),
        .B({1'b0,1'b0,1'b0,mul1_mul_temp__0_i_1_n_0,mul1_mul_temp__0_i_2_n_0,mul1_mul_temp__0_i_3_n_0,mul1_mul_temp__0_i_4_n_0,mul1_mul_temp__0_i_5_n_0,mul1_mul_temp__0_i_6_n_0,mul1_mul_temp__0_i_7_n_0,mul1_mul_temp__0_i_8_n_0,mul1_mul_temp__0_i_9_n_0,mul1_mul_temp__0_i_10_n_0,mul1_mul_temp__0_i_11_n_0,mul1_mul_temp__0_i_12_n_0,mul1_mul_temp__0_i_13_n_0,mul1_mul_temp__0_i_14_n_0,mul1_mul_temp__0_i_15_n_0}),
        .BCIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .BCOUT(NLW_mul1_mul_temp__0_BCOUT_UNCONNECTED[17:0]),
        .C({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .CARRYCASCIN(1'b0),
        .CARRYCASCOUT(NLW_mul1_mul_temp__0_CARRYCASCOUT_UNCONNECTED),
        .CARRYIN(1'b0),
        .CARRYINSEL({1'b0,1'b0,1'b0}),
        .CARRYOUT(NLW_mul1_mul_temp__0_CARRYOUT_UNCONNECTED[3:0]),
        .CEA1(1'b0),
        .CEA2(CEP),
        .CEAD(1'b0),
        .CEALUMODE(1'b0),
        .CEB1(1'b0),
        .CEB2(1'b0),
        .CEC(1'b0),
        .CECARRYIN(1'b0),
        .CECTRL(1'b0),
        .CED(1'b0),
        .CEINMODE(1'b0),
        .CEM(1'b0),
        .CEP(1'b0),
        .CLK(IPCORE_CLK),
        .D({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .INMODE({1'b0,1'b0,1'b0,1'b0,1'b0}),
        .MULTSIGNIN(1'b0),
        .MULTSIGNOUT(NLW_mul1_mul_temp__0_MULTSIGNOUT_UNCONNECTED),
        .OPMODE({1'b0,1'b0,1'b1,1'b0,1'b1,1'b0,1'b1,1'b0,1'b1}),
        .OVERFLOW(NLW_mul1_mul_temp__0_OVERFLOW_UNCONNECTED),
        .P({NLW_mul1_mul_temp__0_P_UNCONNECTED[47:30],mul1_mul_temp__0_n_76,mul1_mul_temp__0_n_77,mul1_mul_temp__0_n_78,mul1_mul_temp__0_n_79,mul1_mul_temp__0_n_80,mul1_mul_temp__0_n_81,mul1_mul_temp__0_n_82,mul1_mul_temp__0_n_83,mul1_mul_temp__0_n_84,mul1_mul_temp__0_n_85,mul1_mul_temp__0_n_86,mul1_mul_temp__0_n_87,mul1_mul_temp__0_n_88,mul1_mul_temp__0_n_89,mul1_mul_temp__0_n_90,mul1_mul_temp__0_n_91,mul1_mul_temp__0_n_92,mul1_mul_temp__0_n_93,mul1_mul_temp__0_n_94,mul1_mul_temp__0_n_95,mul1_mul_temp__0_n_96,mul1_mul_temp__0_n_97,mul1_mul_temp__0_n_98,mul1_mul_temp__0_n_99,mul1_mul_temp__0_n_100,mul1_mul_temp__0_n_101,mul1_mul_temp__0_n_102,mul1_mul_temp__0_n_103,mul1_mul_temp__0_n_104,mul1_mul_temp__0_n_105}),
        .PATTERNBDETECT(NLW_mul1_mul_temp__0_PATTERNBDETECT_UNCONNECTED),
        .PATTERNDETECT(NLW_mul1_mul_temp__0_PATTERNDETECT_UNCONNECTED),
        .PCIN({mul1_mul_temp_n_106,mul1_mul_temp_n_107,mul1_mul_temp_n_108,mul1_mul_temp_n_109,mul1_mul_temp_n_110,mul1_mul_temp_n_111,mul1_mul_temp_n_112,mul1_mul_temp_n_113,mul1_mul_temp_n_114,mul1_mul_temp_n_115,mul1_mul_temp_n_116,mul1_mul_temp_n_117,mul1_mul_temp_n_118,mul1_mul_temp_n_119,mul1_mul_temp_n_120,mul1_mul_temp_n_121,mul1_mul_temp_n_122,mul1_mul_temp_n_123,mul1_mul_temp_n_124,mul1_mul_temp_n_125,mul1_mul_temp_n_126,mul1_mul_temp_n_127,mul1_mul_temp_n_128,mul1_mul_temp_n_129,mul1_mul_temp_n_130,mul1_mul_temp_n_131,mul1_mul_temp_n_132,mul1_mul_temp_n_133,mul1_mul_temp_n_134,mul1_mul_temp_n_135,mul1_mul_temp_n_136,mul1_mul_temp_n_137,mul1_mul_temp_n_138,mul1_mul_temp_n_139,mul1_mul_temp_n_140,mul1_mul_temp_n_141,mul1_mul_temp_n_142,mul1_mul_temp_n_143,mul1_mul_temp_n_144,mul1_mul_temp_n_145,mul1_mul_temp_n_146,mul1_mul_temp_n_147,mul1_mul_temp_n_148,mul1_mul_temp_n_149,mul1_mul_temp_n_150,mul1_mul_temp_n_151,mul1_mul_temp_n_152,mul1_mul_temp_n_153}),
        .PCOUT(NLW_mul1_mul_temp__0_PCOUT_UNCONNECTED[47:0]),
        .RSTA(RSTP),
        .RSTALLCARRYIN(1'b0),
        .RSTALUMODE(1'b0),
        .RSTB(1'b0),
        .RSTC(1'b0),
        .RSTCTRL(1'b0),
        .RSTD(1'b0),
        .RSTINMODE(1'b0),
        .RSTM(1'b0),
        .RSTP(1'b0),
        .UNDERFLOW(NLW_mul1_mul_temp__0_UNDERFLOW_UNCONNECTED),
        .XOROUT(NLW_mul1_mul_temp__0_XOROUT_UNCONNECTED[7:0]));
  (* SOFT_HLUTNM = "soft_lutpair20" *) 
  LUT3 #(
    .INIT(8'hA2)) 
    mul1_mul_temp__0_i_1
       (.I0(sel),
        .I1(subtractor_sub_temp_carry__2_n_0),
        .I2(subtractor_sub_temp_carry__2_n_9),
        .O(mul1_mul_temp__0_i_1_n_0));
  LUT4 #(
    .INIT(16'hBFB0)) 
    mul1_mul_temp__0_i_10
       (.I0(subtractor_sub_temp_carry__1_n_10),
        .I1(subtractor_sub_temp_carry__2_n_0),
        .I2(sel),
        .I3(\aout_tmp_reg[31]_1 [22]),
        .O(mul1_mul_temp__0_i_10_n_0));
  LUT4 #(
    .INIT(16'hBFB0)) 
    mul1_mul_temp__0_i_11
       (.I0(subtractor_sub_temp_carry__1_n_11),
        .I1(subtractor_sub_temp_carry__2_n_0),
        .I2(sel),
        .I3(\aout_tmp_reg[31]_1 [21]),
        .O(mul1_mul_temp__0_i_11_n_0));
  LUT4 #(
    .INIT(16'hBFB0)) 
    mul1_mul_temp__0_i_12
       (.I0(subtractor_sub_temp_carry__1_n_12),
        .I1(subtractor_sub_temp_carry__2_n_0),
        .I2(sel),
        .I3(\aout_tmp_reg[31]_1 [20]),
        .O(mul1_mul_temp__0_i_12_n_0));
  LUT4 #(
    .INIT(16'hBFB0)) 
    mul1_mul_temp__0_i_13
       (.I0(subtractor_sub_temp_carry__1_n_13),
        .I1(subtractor_sub_temp_carry__2_n_0),
        .I2(sel),
        .I3(\aout_tmp_reg[31]_1 [19]),
        .O(mul1_mul_temp__0_i_13_n_0));
  LUT4 #(
    .INIT(16'hBFB0)) 
    mul1_mul_temp__0_i_14
       (.I0(subtractor_sub_temp_carry__1_n_14),
        .I1(subtractor_sub_temp_carry__2_n_0),
        .I2(sel),
        .I3(\aout_tmp_reg[31]_1 [18]),
        .O(mul1_mul_temp__0_i_14_n_0));
  LUT4 #(
    .INIT(16'hBFB0)) 
    mul1_mul_temp__0_i_15
       (.I0(subtractor_sub_temp_carry__1_n_15),
        .I1(subtractor_sub_temp_carry__2_n_0),
        .I2(sel),
        .I3(\aout_tmp_reg[31]_1 [17]),
        .O(mul1_mul_temp__0_i_15_n_0));
  (* SOFT_HLUTNM = "soft_lutpair19" *) 
  LUT3 #(
    .INIT(8'hA2)) 
    mul1_mul_temp__0_i_2
       (.I0(sel),
        .I1(subtractor_sub_temp_carry__2_n_0),
        .I2(subtractor_sub_temp_carry__2_n_10),
        .O(mul1_mul_temp__0_i_2_n_0));
  LUT4 #(
    .INIT(16'hBFB0)) 
    mul1_mul_temp__0_i_3
       (.I0(subtractor_sub_temp_carry__2_n_11),
        .I1(subtractor_sub_temp_carry__2_n_0),
        .I2(sel),
        .I3(\aout_tmp_reg[31]_1 [29]),
        .O(mul1_mul_temp__0_i_3_n_0));
  LUT4 #(
    .INIT(16'hBFB0)) 
    mul1_mul_temp__0_i_4
       (.I0(subtractor_sub_temp_carry__2_n_12),
        .I1(subtractor_sub_temp_carry__2_n_0),
        .I2(sel),
        .I3(\aout_tmp_reg[31]_1 [28]),
        .O(mul1_mul_temp__0_i_4_n_0));
  LUT4 #(
    .INIT(16'hBFB0)) 
    mul1_mul_temp__0_i_5
       (.I0(subtractor_sub_temp_carry__2_n_13),
        .I1(subtractor_sub_temp_carry__2_n_0),
        .I2(sel),
        .I3(\aout_tmp_reg[31]_1 [27]),
        .O(mul1_mul_temp__0_i_5_n_0));
  LUT4 #(
    .INIT(16'hBFB0)) 
    mul1_mul_temp__0_i_6
       (.I0(subtractor_sub_temp_carry__2_n_14),
        .I1(subtractor_sub_temp_carry__2_n_0),
        .I2(sel),
        .I3(\aout_tmp_reg[31]_1 [26]),
        .O(mul1_mul_temp__0_i_6_n_0));
  LUT4 #(
    .INIT(16'hBFB0)) 
    mul1_mul_temp__0_i_7
       (.I0(subtractor_sub_temp_carry__2_n_15),
        .I1(subtractor_sub_temp_carry__2_n_0),
        .I2(sel),
        .I3(\aout_tmp_reg[31]_1 [25]),
        .O(mul1_mul_temp__0_i_7_n_0));
  LUT4 #(
    .INIT(16'hBFB0)) 
    mul1_mul_temp__0_i_8
       (.I0(subtractor_sub_temp_carry__1_n_8),
        .I1(subtractor_sub_temp_carry__2_n_0),
        .I2(sel),
        .I3(\aout_tmp_reg[31]_1 [24]),
        .O(mul1_mul_temp__0_i_8_n_0));
  LUT4 #(
    .INIT(16'hBFB0)) 
    mul1_mul_temp__0_i_9
       (.I0(subtractor_sub_temp_carry__1_n_9),
        .I1(subtractor_sub_temp_carry__2_n_0),
        .I2(sel),
        .I3(\aout_tmp_reg[31]_1 [23]),
        .O(mul1_mul_temp__0_i_9_n_0));
  (* KEEP_HIERARCHY = "yes" *) 
  (* METHODOLOGY_DRC_VIOS = "{SYNTH-10 {cell *THIS*} {string 18x18 4}}" *) 
  DSP48E2 #(
    .ACASCREG(1),
    .ADREG(1),
    .ALUMODEREG(0),
    .AMULTSEL("A"),
    .AREG(1),
    .AUTORESET_PATDET("NO_RESET"),
    .AUTORESET_PRIORITY("RESET"),
    .A_INPUT("DIRECT"),
    .BCASCREG(0),
    .BMULTSEL("B"),
    .BREG(0),
    .B_INPUT("DIRECT"),
    .CARRYINREG(0),
    .CARRYINSELREG(0),
    .CREG(1),
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
    mul1_mul_temp__1
       (.A({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,D[16:0]}),
        .ACIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .ACOUT(NLW_mul1_mul_temp__1_ACOUT_UNCONNECTED[29:0]),
        .ALUMODE({1'b0,1'b0,1'b0,1'b0}),
        .B({1'b0,mul1_mul_temp_i_1_n_0,mul1_mul_temp_i_2_n_0,mul1_mul_temp_i_3_n_0,mul1_mul_temp_i_4_n_0,mul1_mul_temp_i_5_n_0,mul1_mul_temp_i_6_n_0,mul1_mul_temp_i_7_n_0,mul1_mul_temp_i_8_n_0,mul1_mul_temp_i_9_n_0,mul1_mul_temp_i_10_n_0,mul1_mul_temp_i_11_n_0,mul1_mul_temp_i_12_n_0,mul1_mul_temp_i_13_n_0,mul1_mul_temp_i_14_n_0,mul1_mul_temp_i_15_n_0,mul1_mul_temp_i_16_n_0,mul1_mul_temp_i_17_n_0}),
        .BCIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .BCOUT(NLW_mul1_mul_temp__1_BCOUT_UNCONNECTED[17:0]),
        .C({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .CARRYCASCIN(1'b0),
        .CARRYCASCOUT(NLW_mul1_mul_temp__1_CARRYCASCOUT_UNCONNECTED),
        .CARRYIN(1'b0),
        .CARRYINSEL({1'b0,1'b0,1'b0}),
        .CARRYOUT(NLW_mul1_mul_temp__1_CARRYOUT_UNCONNECTED[3:0]),
        .CEA1(1'b0),
        .CEA2(CEP),
        .CEAD(1'b0),
        .CEALUMODE(1'b0),
        .CEB1(1'b0),
        .CEB2(1'b0),
        .CEC(1'b0),
        .CECARRYIN(1'b0),
        .CECTRL(1'b0),
        .CED(1'b0),
        .CEINMODE(1'b0),
        .CEM(1'b0),
        .CEP(1'b0),
        .CLK(IPCORE_CLK),
        .D({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .INMODE({1'b0,1'b0,1'b0,1'b0,1'b0}),
        .MULTSIGNIN(1'b0),
        .MULTSIGNOUT(NLW_mul1_mul_temp__1_MULTSIGNOUT_UNCONNECTED),
        .OPMODE({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b1,1'b0,1'b1}),
        .OVERFLOW(NLW_mul1_mul_temp__1_OVERFLOW_UNCONNECTED),
        .P({mul1_mul_temp__1_n_58,mul1_mul_temp__1_n_59,mul1_mul_temp__1_n_60,mul1_mul_temp__1_n_61,mul1_mul_temp__1_n_62,mul1_mul_temp__1_n_63,mul1_mul_temp__1_n_64,mul1_mul_temp__1_n_65,mul1_mul_temp__1_n_66,mul1_mul_temp__1_n_67,mul1_mul_temp__1_n_68,mul1_mul_temp__1_n_69,mul1_mul_temp__1_n_70,mul1_mul_temp__1_n_71,mul1_mul_temp__1_n_72,mul1_mul_temp__1_n_73,mul1_mul_temp__1_n_74,mul1_mul_temp__1_n_75,mul1_mul_temp__1_n_76,mul1_mul_temp__1_n_77,mul1_mul_temp__1_n_78,mul1_mul_temp__1_n_79,mul1_mul_temp__1_n_80,mul1_mul_temp__1_n_81,mul1_mul_temp__1_n_82,mul1_mul_temp__1_n_83,mul1_mul_temp__1_n_84,mul1_mul_temp__1_n_85,mul1_mul_temp__1_n_86,mul1_mul_temp__1_n_87,mul1_mul_temp__1_n_88,mul1_mul_temp__1_n_89,mul1_mul_temp__1_n_90,mul1_mul_temp__1_n_91,mul1_mul_temp__1_n_92,mul1_mul_temp__1_n_93,mul1_mul_temp__1_n_94,mul1_mul_temp__1_n_95,mul1_mul_temp__1_n_96,mul1_mul_temp__1_n_97,mul1_mul_temp__1_n_98,mul1_mul_temp__1_n_99,mul1_mul_temp__1_n_100,mul1_mul_temp__1_n_101,mul1_mul_temp__1_n_102,mul1_mul_temp__1_n_103,mul1_mul_temp__1_n_104,mul1_mul_temp__1_n_105}),
        .PATTERNBDETECT(NLW_mul1_mul_temp__1_PATTERNBDETECT_UNCONNECTED),
        .PATTERNDETECT(NLW_mul1_mul_temp__1_PATTERNDETECT_UNCONNECTED),
        .PCIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .PCOUT({mul1_mul_temp__1_n_106,mul1_mul_temp__1_n_107,mul1_mul_temp__1_n_108,mul1_mul_temp__1_n_109,mul1_mul_temp__1_n_110,mul1_mul_temp__1_n_111,mul1_mul_temp__1_n_112,mul1_mul_temp__1_n_113,mul1_mul_temp__1_n_114,mul1_mul_temp__1_n_115,mul1_mul_temp__1_n_116,mul1_mul_temp__1_n_117,mul1_mul_temp__1_n_118,mul1_mul_temp__1_n_119,mul1_mul_temp__1_n_120,mul1_mul_temp__1_n_121,mul1_mul_temp__1_n_122,mul1_mul_temp__1_n_123,mul1_mul_temp__1_n_124,mul1_mul_temp__1_n_125,mul1_mul_temp__1_n_126,mul1_mul_temp__1_n_127,mul1_mul_temp__1_n_128,mul1_mul_temp__1_n_129,mul1_mul_temp__1_n_130,mul1_mul_temp__1_n_131,mul1_mul_temp__1_n_132,mul1_mul_temp__1_n_133,mul1_mul_temp__1_n_134,mul1_mul_temp__1_n_135,mul1_mul_temp__1_n_136,mul1_mul_temp__1_n_137,mul1_mul_temp__1_n_138,mul1_mul_temp__1_n_139,mul1_mul_temp__1_n_140,mul1_mul_temp__1_n_141,mul1_mul_temp__1_n_142,mul1_mul_temp__1_n_143,mul1_mul_temp__1_n_144,mul1_mul_temp__1_n_145,mul1_mul_temp__1_n_146,mul1_mul_temp__1_n_147,mul1_mul_temp__1_n_148,mul1_mul_temp__1_n_149,mul1_mul_temp__1_n_150,mul1_mul_temp__1_n_151,mul1_mul_temp__1_n_152,mul1_mul_temp__1_n_153}),
        .RSTA(RSTP),
        .RSTALLCARRYIN(1'b0),
        .RSTALUMODE(1'b0),
        .RSTB(1'b0),
        .RSTC(1'b0),
        .RSTCTRL(1'b0),
        .RSTD(1'b0),
        .RSTINMODE(1'b0),
        .RSTM(1'b0),
        .RSTP(1'b0),
        .UNDERFLOW(NLW_mul1_mul_temp__1_UNDERFLOW_UNCONNECTED),
        .XOROUT(NLW_mul1_mul_temp__1_XOROUT_UNCONNECTED[7:0]));
  (* KEEP_HIERARCHY = "yes" *) 
  (* METHODOLOGY_DRC_VIOS = "{SYNTH-10 {cell *THIS*} {string 18x16 4}}" *) 
  DSP48E2 #(
    .ACASCREG(1),
    .ADREG(1),
    .ALUMODEREG(0),
    .AMULTSEL("A"),
    .AREG(1),
    .AUTORESET_PATDET("NO_RESET"),
    .AUTORESET_PRIORITY("RESET"),
    .A_INPUT("DIRECT"),
    .BCASCREG(0),
    .BMULTSEL("B"),
    .BREG(0),
    .B_INPUT("DIRECT"),
    .CARRYINREG(0),
    .CARRYINSELREG(0),
    .CREG(1),
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
    mul1_mul_temp__2
       (.A({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,D[16:0]}),
        .ACIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .ACOUT(NLW_mul1_mul_temp__2_ACOUT_UNCONNECTED[29:0]),
        .ALUMODE({1'b0,1'b0,1'b0,1'b0}),
        .B({1'b0,1'b0,1'b0,mul1_mul_temp__0_i_1_n_0,mul1_mul_temp__0_i_2_n_0,mul1_mul_temp__0_i_3_n_0,mul1_mul_temp__0_i_4_n_0,mul1_mul_temp__0_i_5_n_0,mul1_mul_temp__0_i_6_n_0,mul1_mul_temp__0_i_7_n_0,mul1_mul_temp__0_i_8_n_0,mul1_mul_temp__0_i_9_n_0,mul1_mul_temp__0_i_10_n_0,mul1_mul_temp__0_i_11_n_0,mul1_mul_temp__0_i_12_n_0,mul1_mul_temp__0_i_13_n_0,mul1_mul_temp__0_i_14_n_0,mul1_mul_temp__0_i_15_n_0}),
        .BCIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .BCOUT(NLW_mul1_mul_temp__2_BCOUT_UNCONNECTED[17:0]),
        .C({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .CARRYCASCIN(1'b0),
        .CARRYCASCOUT(NLW_mul1_mul_temp__2_CARRYCASCOUT_UNCONNECTED),
        .CARRYIN(1'b0),
        .CARRYINSEL({1'b0,1'b0,1'b0}),
        .CARRYOUT(NLW_mul1_mul_temp__2_CARRYOUT_UNCONNECTED[3:0]),
        .CEA1(1'b0),
        .CEA2(CEP),
        .CEAD(1'b0),
        .CEALUMODE(1'b0),
        .CEB1(1'b0),
        .CEB2(1'b0),
        .CEC(1'b0),
        .CECARRYIN(1'b0),
        .CECTRL(1'b0),
        .CED(1'b0),
        .CEINMODE(1'b0),
        .CEM(1'b0),
        .CEP(1'b0),
        .CLK(IPCORE_CLK),
        .D({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .INMODE({1'b0,1'b0,1'b0,1'b0,1'b0}),
        .MULTSIGNIN(1'b0),
        .MULTSIGNOUT(NLW_mul1_mul_temp__2_MULTSIGNOUT_UNCONNECTED),
        .OPMODE({1'b0,1'b0,1'b1,1'b0,1'b1,1'b0,1'b1,1'b0,1'b1}),
        .OVERFLOW(NLW_mul1_mul_temp__2_OVERFLOW_UNCONNECTED),
        .P({NLW_mul1_mul_temp__2_P_UNCONNECTED[47],mul1_mul_temp__2_n_59,mul1_mul_temp__2_n_60,mul1_mul_temp__2_n_61,mul1_mul_temp__2_n_62,mul1_mul_temp__2_n_63,mul1_mul_temp__2_n_64,mul1_mul_temp__2_n_65,mul1_mul_temp__2_n_66,mul1_mul_temp__2_n_67,mul1_mul_temp__2_n_68,mul1_mul_temp__2_n_69,mul1_mul_temp__2_n_70,mul1_mul_temp__2_n_71,mul1_mul_temp__2_n_72,mul1_mul_temp__2_n_73,mul1_mul_temp__2_n_74,mul1_mul_temp__2_n_75,mul1_mul_temp__2_n_76,mul1_mul_temp__2_n_77,mul1_mul_temp__2_n_78,mul1_mul_temp__2_n_79,mul1_mul_temp__2_n_80,mul1_mul_temp__2_n_81,mul1_mul_temp__2_n_82,mul1_mul_temp__2_n_83,mul1_mul_temp__2_n_84,mul1_mul_temp__2_n_85,mul1_mul_temp__2_n_86,mul1_mul_temp__2_n_87,mul1_mul_temp__2_n_88,mul1_mul_temp__2_n_89,mul1_mul_temp__2_n_90,mul1_mul_temp__2_n_91,mul1_mul_temp__2_n_92,mul1_mul_temp__2_n_93,mul1_mul_temp__2_n_94,mul1_mul_temp__2_n_95,mul1_mul_temp__2_n_96,mul1_mul_temp__2_n_97,mul1_mul_temp__2_n_98,mul1_mul_temp__2_n_99,mul1_mul_temp__2_n_100,mul1_mul_temp__2_n_101,mul1_mul_temp__2_n_102,mul1_mul_temp__2_n_103,mul1_mul_temp__2_n_104,mul1_mul_temp__2_n_105}),
        .PATTERNBDETECT(NLW_mul1_mul_temp__2_PATTERNBDETECT_UNCONNECTED),
        .PATTERNDETECT(NLW_mul1_mul_temp__2_PATTERNDETECT_UNCONNECTED),
        .PCIN({mul1_mul_temp__1_n_106,mul1_mul_temp__1_n_107,mul1_mul_temp__1_n_108,mul1_mul_temp__1_n_109,mul1_mul_temp__1_n_110,mul1_mul_temp__1_n_111,mul1_mul_temp__1_n_112,mul1_mul_temp__1_n_113,mul1_mul_temp__1_n_114,mul1_mul_temp__1_n_115,mul1_mul_temp__1_n_116,mul1_mul_temp__1_n_117,mul1_mul_temp__1_n_118,mul1_mul_temp__1_n_119,mul1_mul_temp__1_n_120,mul1_mul_temp__1_n_121,mul1_mul_temp__1_n_122,mul1_mul_temp__1_n_123,mul1_mul_temp__1_n_124,mul1_mul_temp__1_n_125,mul1_mul_temp__1_n_126,mul1_mul_temp__1_n_127,mul1_mul_temp__1_n_128,mul1_mul_temp__1_n_129,mul1_mul_temp__1_n_130,mul1_mul_temp__1_n_131,mul1_mul_temp__1_n_132,mul1_mul_temp__1_n_133,mul1_mul_temp__1_n_134,mul1_mul_temp__1_n_135,mul1_mul_temp__1_n_136,mul1_mul_temp__1_n_137,mul1_mul_temp__1_n_138,mul1_mul_temp__1_n_139,mul1_mul_temp__1_n_140,mul1_mul_temp__1_n_141,mul1_mul_temp__1_n_142,mul1_mul_temp__1_n_143,mul1_mul_temp__1_n_144,mul1_mul_temp__1_n_145,mul1_mul_temp__1_n_146,mul1_mul_temp__1_n_147,mul1_mul_temp__1_n_148,mul1_mul_temp__1_n_149,mul1_mul_temp__1_n_150,mul1_mul_temp__1_n_151,mul1_mul_temp__1_n_152,mul1_mul_temp__1_n_153}),
        .PCOUT(NLW_mul1_mul_temp__2_PCOUT_UNCONNECTED[47:0]),
        .RSTA(RSTP),
        .RSTALLCARRYIN(1'b0),
        .RSTALUMODE(1'b0),
        .RSTB(1'b0),
        .RSTC(1'b0),
        .RSTCTRL(1'b0),
        .RSTD(1'b0),
        .RSTINMODE(1'b0),
        .RSTM(1'b0),
        .RSTP(1'b0),
        .UNDERFLOW(NLW_mul1_mul_temp__2_UNDERFLOW_UNCONNECTED),
        .XOROUT(NLW_mul1_mul_temp__2_XOROUT_UNCONNECTED[7:0]));
  (* ADDER_THRESHOLD = "35" *) 
  CARRY8 mul1_mul_temp_carry
       (.CI(1'b0),
        .CI_TOP(1'b0),
        .CO({mul1_mul_temp_carry_n_0,mul1_mul_temp_carry_n_1,mul1_mul_temp_carry_n_2,mul1_mul_temp_carry_n_3,mul1_mul_temp_carry_n_4,mul1_mul_temp_carry_n_5,mul1_mul_temp_carry_n_6,mul1_mul_temp_carry_n_7}),
        .DI({mul1_mul_temp__2_n_99,mul1_mul_temp__2_n_100,mul1_mul_temp__2_n_101,mul1_mul_temp__2_n_102,mul1_mul_temp__2_n_103,mul1_mul_temp__2_n_104,mul1_mul_temp__2_n_105,1'b0}),
        .O(NLW_mul1_mul_temp_carry_O_UNCONNECTED[7:0]),
        .S({mul1_mul_temp_carry_i_1_n_0,mul1_mul_temp_carry_i_2_n_0,mul1_mul_temp_carry_i_3_n_0,mul1_mul_temp_carry_i_4_n_0,mul1_mul_temp_carry_i_5_n_0,mul1_mul_temp_carry_i_6_n_0,mul1_mul_temp_carry_i_7_n_0,mul1_mul_temp__1_n_89}));
  (* ADDER_THRESHOLD = "35" *) 
  CARRY8 mul1_mul_temp_carry__0
       (.CI(mul1_mul_temp_carry_n_0),
        .CI_TOP(1'b0),
        .CO({mul1_mul_temp_carry__0_n_0,mul1_mul_temp_carry__0_n_1,mul1_mul_temp_carry__0_n_2,mul1_mul_temp_carry__0_n_3,mul1_mul_temp_carry__0_n_4,mul1_mul_temp_carry__0_n_5,mul1_mul_temp_carry__0_n_6,mul1_mul_temp_carry__0_n_7}),
        .DI({mul1_mul_temp__2_n_91,mul1_mul_temp__2_n_92,mul1_mul_temp__2_n_93,mul1_mul_temp__2_n_94,mul1_mul_temp__2_n_95,mul1_mul_temp__2_n_96,mul1_mul_temp__2_n_97,mul1_mul_temp__2_n_98}),
        .O({mul1_mul_temp_carry__0_n_8,mul1_mul_temp_carry__0_n_9,NLW_mul1_mul_temp_carry__0_O_UNCONNECTED[5:0]}),
        .S({mul1_mul_temp_carry__0_i_1_n_0,mul1_mul_temp_carry__0_i_2_n_0,mul1_mul_temp_carry__0_i_3_n_0,mul1_mul_temp_carry__0_i_4_n_0,mul1_mul_temp_carry__0_i_5_n_0,mul1_mul_temp_carry__0_i_6_n_0,mul1_mul_temp_carry__0_i_7_n_0,mul1_mul_temp_carry__0_i_8_n_0}));
  LUT2 #(
    .INIT(4'h6)) 
    mul1_mul_temp_carry__0_i_1
       (.I0(mul1_mul_temp__2_n_91),
        .I1(mul1_mul_temp_n_91),
        .O(mul1_mul_temp_carry__0_i_1_n_0));
  LUT2 #(
    .INIT(4'h6)) 
    mul1_mul_temp_carry__0_i_2
       (.I0(mul1_mul_temp__2_n_92),
        .I1(mul1_mul_temp_n_92),
        .O(mul1_mul_temp_carry__0_i_2_n_0));
  LUT2 #(
    .INIT(4'h6)) 
    mul1_mul_temp_carry__0_i_3
       (.I0(mul1_mul_temp__2_n_93),
        .I1(mul1_mul_temp_n_93),
        .O(mul1_mul_temp_carry__0_i_3_n_0));
  LUT2 #(
    .INIT(4'h6)) 
    mul1_mul_temp_carry__0_i_4
       (.I0(mul1_mul_temp__2_n_94),
        .I1(mul1_mul_temp_n_94),
        .O(mul1_mul_temp_carry__0_i_4_n_0));
  LUT2 #(
    .INIT(4'h6)) 
    mul1_mul_temp_carry__0_i_5
       (.I0(mul1_mul_temp__2_n_95),
        .I1(mul1_mul_temp_n_95),
        .O(mul1_mul_temp_carry__0_i_5_n_0));
  LUT2 #(
    .INIT(4'h6)) 
    mul1_mul_temp_carry__0_i_6
       (.I0(mul1_mul_temp__2_n_96),
        .I1(mul1_mul_temp_n_96),
        .O(mul1_mul_temp_carry__0_i_6_n_0));
  LUT2 #(
    .INIT(4'h6)) 
    mul1_mul_temp_carry__0_i_7
       (.I0(mul1_mul_temp__2_n_97),
        .I1(mul1_mul_temp_n_97),
        .O(mul1_mul_temp_carry__0_i_7_n_0));
  LUT2 #(
    .INIT(4'h6)) 
    mul1_mul_temp_carry__0_i_8
       (.I0(mul1_mul_temp__2_n_98),
        .I1(mul1_mul_temp_n_98),
        .O(mul1_mul_temp_carry__0_i_8_n_0));
  (* ADDER_THRESHOLD = "35" *) 
  CARRY8 mul1_mul_temp_carry__1
       (.CI(mul1_mul_temp_carry__0_n_0),
        .CI_TOP(1'b0),
        .CO({mul1_mul_temp_carry__1_n_0,mul1_mul_temp_carry__1_n_1,mul1_mul_temp_carry__1_n_2,mul1_mul_temp_carry__1_n_3,mul1_mul_temp_carry__1_n_4,mul1_mul_temp_carry__1_n_5,mul1_mul_temp_carry__1_n_6,mul1_mul_temp_carry__1_n_7}),
        .DI({mul1_mul_temp__2_n_83,mul1_mul_temp__2_n_84,mul1_mul_temp__2_n_85,mul1_mul_temp__2_n_86,mul1_mul_temp__2_n_87,mul1_mul_temp__2_n_88,mul1_mul_temp__2_n_89,mul1_mul_temp__2_n_90}),
        .O({mul1_mul_temp_carry__1_n_8,mul1_mul_temp_carry__1_n_9,mul1_mul_temp_carry__1_n_10,mul1_mul_temp_carry__1_n_11,mul1_mul_temp_carry__1_n_12,mul1_mul_temp_carry__1_n_13,mul1_mul_temp_carry__1_n_14,mul1_mul_temp_carry__1_n_15}),
        .S({mul1_mul_temp_carry__1_i_1_n_0,mul1_mul_temp_carry__1_i_2_n_0,mul1_mul_temp_carry__1_i_3_n_0,mul1_mul_temp_carry__1_i_4_n_0,mul1_mul_temp_carry__1_i_5_n_0,mul1_mul_temp_carry__1_i_6_n_0,mul1_mul_temp_carry__1_i_7_n_0,mul1_mul_temp_carry__1_i_8_n_0}));
  LUT2 #(
    .INIT(4'h6)) 
    mul1_mul_temp_carry__1_i_1
       (.I0(mul1_mul_temp__2_n_83),
        .I1(mul1_mul_temp__0_n_100),
        .O(mul1_mul_temp_carry__1_i_1_n_0));
  LUT2 #(
    .INIT(4'h6)) 
    mul1_mul_temp_carry__1_i_2
       (.I0(mul1_mul_temp__2_n_84),
        .I1(mul1_mul_temp__0_n_101),
        .O(mul1_mul_temp_carry__1_i_2_n_0));
  LUT2 #(
    .INIT(4'h6)) 
    mul1_mul_temp_carry__1_i_3
       (.I0(mul1_mul_temp__2_n_85),
        .I1(mul1_mul_temp__0_n_102),
        .O(mul1_mul_temp_carry__1_i_3_n_0));
  LUT2 #(
    .INIT(4'h6)) 
    mul1_mul_temp_carry__1_i_4
       (.I0(mul1_mul_temp__2_n_86),
        .I1(mul1_mul_temp__0_n_103),
        .O(mul1_mul_temp_carry__1_i_4_n_0));
  LUT2 #(
    .INIT(4'h6)) 
    mul1_mul_temp_carry__1_i_5
       (.I0(mul1_mul_temp__2_n_87),
        .I1(mul1_mul_temp__0_n_104),
        .O(mul1_mul_temp_carry__1_i_5_n_0));
  LUT2 #(
    .INIT(4'h6)) 
    mul1_mul_temp_carry__1_i_6
       (.I0(mul1_mul_temp__2_n_88),
        .I1(mul1_mul_temp__0_n_105),
        .O(mul1_mul_temp_carry__1_i_6_n_0));
  LUT2 #(
    .INIT(4'h6)) 
    mul1_mul_temp_carry__1_i_7
       (.I0(mul1_mul_temp__2_n_89),
        .I1(mul1_mul_temp_n_89),
        .O(mul1_mul_temp_carry__1_i_7_n_0));
  LUT2 #(
    .INIT(4'h6)) 
    mul1_mul_temp_carry__1_i_8
       (.I0(mul1_mul_temp__2_n_90),
        .I1(mul1_mul_temp_n_90),
        .O(mul1_mul_temp_carry__1_i_8_n_0));
  (* ADDER_THRESHOLD = "35" *) 
  CARRY8 mul1_mul_temp_carry__2
       (.CI(mul1_mul_temp_carry__1_n_0),
        .CI_TOP(1'b0),
        .CO({mul1_mul_temp_carry__2_n_0,mul1_mul_temp_carry__2_n_1,mul1_mul_temp_carry__2_n_2,mul1_mul_temp_carry__2_n_3,mul1_mul_temp_carry__2_n_4,mul1_mul_temp_carry__2_n_5,mul1_mul_temp_carry__2_n_6,mul1_mul_temp_carry__2_n_7}),
        .DI({mul1_mul_temp__2_n_75,mul1_mul_temp__2_n_76,mul1_mul_temp__2_n_77,mul1_mul_temp__2_n_78,mul1_mul_temp__2_n_79,mul1_mul_temp__2_n_80,mul1_mul_temp__2_n_81,mul1_mul_temp__2_n_82}),
        .O({mul1_mul_temp_carry__2_n_8,mul1_mul_temp_carry__2_n_9,mul1_mul_temp_carry__2_n_10,mul1_mul_temp_carry__2_n_11,mul1_mul_temp_carry__2_n_12,mul1_mul_temp_carry__2_n_13,mul1_mul_temp_carry__2_n_14,mul1_mul_temp_carry__2_n_15}),
        .S({mul1_mul_temp_carry__2_i_1_n_0,mul1_mul_temp_carry__2_i_2_n_0,mul1_mul_temp_carry__2_i_3_n_0,mul1_mul_temp_carry__2_i_4_n_0,mul1_mul_temp_carry__2_i_5_n_0,mul1_mul_temp_carry__2_i_6_n_0,mul1_mul_temp_carry__2_i_7_n_0,mul1_mul_temp_carry__2_i_8_n_0}));
  LUT2 #(
    .INIT(4'h6)) 
    mul1_mul_temp_carry__2_i_1
       (.I0(mul1_mul_temp__2_n_75),
        .I1(mul1_mul_temp__0_n_92),
        .O(mul1_mul_temp_carry__2_i_1_n_0));
  LUT2 #(
    .INIT(4'h6)) 
    mul1_mul_temp_carry__2_i_2
       (.I0(mul1_mul_temp__2_n_76),
        .I1(mul1_mul_temp__0_n_93),
        .O(mul1_mul_temp_carry__2_i_2_n_0));
  LUT2 #(
    .INIT(4'h6)) 
    mul1_mul_temp_carry__2_i_3
       (.I0(mul1_mul_temp__2_n_77),
        .I1(mul1_mul_temp__0_n_94),
        .O(mul1_mul_temp_carry__2_i_3_n_0));
  LUT2 #(
    .INIT(4'h6)) 
    mul1_mul_temp_carry__2_i_4
       (.I0(mul1_mul_temp__2_n_78),
        .I1(mul1_mul_temp__0_n_95),
        .O(mul1_mul_temp_carry__2_i_4_n_0));
  LUT2 #(
    .INIT(4'h6)) 
    mul1_mul_temp_carry__2_i_5
       (.I0(mul1_mul_temp__2_n_79),
        .I1(mul1_mul_temp__0_n_96),
        .O(mul1_mul_temp_carry__2_i_5_n_0));
  LUT2 #(
    .INIT(4'h6)) 
    mul1_mul_temp_carry__2_i_6
       (.I0(mul1_mul_temp__2_n_80),
        .I1(mul1_mul_temp__0_n_97),
        .O(mul1_mul_temp_carry__2_i_6_n_0));
  LUT2 #(
    .INIT(4'h6)) 
    mul1_mul_temp_carry__2_i_7
       (.I0(mul1_mul_temp__2_n_81),
        .I1(mul1_mul_temp__0_n_98),
        .O(mul1_mul_temp_carry__2_i_7_n_0));
  LUT2 #(
    .INIT(4'h6)) 
    mul1_mul_temp_carry__2_i_8
       (.I0(mul1_mul_temp__2_n_82),
        .I1(mul1_mul_temp__0_n_99),
        .O(mul1_mul_temp_carry__2_i_8_n_0));
  (* ADDER_THRESHOLD = "35" *) 
  CARRY8 mul1_mul_temp_carry__3
       (.CI(mul1_mul_temp_carry__2_n_0),
        .CI_TOP(1'b0),
        .CO({mul1_mul_temp_carry__3_n_0,mul1_mul_temp_carry__3_n_1,mul1_mul_temp_carry__3_n_2,mul1_mul_temp_carry__3_n_3,mul1_mul_temp_carry__3_n_4,mul1_mul_temp_carry__3_n_5,mul1_mul_temp_carry__3_n_6,mul1_mul_temp_carry__3_n_7}),
        .DI({mul1_mul_temp__2_n_67,mul1_mul_temp__2_n_68,mul1_mul_temp__2_n_69,mul1_mul_temp__2_n_70,mul1_mul_temp__2_n_71,mul1_mul_temp__2_n_72,mul1_mul_temp__2_n_73,mul1_mul_temp__2_n_74}),
        .O({mul1_mul_temp_carry__3_n_8,mul1_mul_temp_carry__3_n_9,mul1_mul_temp_carry__3_n_10,mul1_mul_temp_carry__3_n_11,mul1_mul_temp_carry__3_n_12,mul1_mul_temp_carry__3_n_13,mul1_mul_temp_carry__3_n_14,mul1_mul_temp_carry__3_n_15}),
        .S({mul1_mul_temp_carry__3_i_1_n_0,mul1_mul_temp_carry__3_i_2_n_0,mul1_mul_temp_carry__3_i_3_n_0,mul1_mul_temp_carry__3_i_4_n_0,mul1_mul_temp_carry__3_i_5_n_0,mul1_mul_temp_carry__3_i_6_n_0,mul1_mul_temp_carry__3_i_7_n_0,mul1_mul_temp_carry__3_i_8_n_0}));
  LUT2 #(
    .INIT(4'h6)) 
    mul1_mul_temp_carry__3_i_1
       (.I0(mul1_mul_temp__2_n_67),
        .I1(mul1_mul_temp__0_n_84),
        .O(mul1_mul_temp_carry__3_i_1_n_0));
  LUT2 #(
    .INIT(4'h6)) 
    mul1_mul_temp_carry__3_i_2
       (.I0(mul1_mul_temp__2_n_68),
        .I1(mul1_mul_temp__0_n_85),
        .O(mul1_mul_temp_carry__3_i_2_n_0));
  LUT2 #(
    .INIT(4'h6)) 
    mul1_mul_temp_carry__3_i_3
       (.I0(mul1_mul_temp__2_n_69),
        .I1(mul1_mul_temp__0_n_86),
        .O(mul1_mul_temp_carry__3_i_3_n_0));
  LUT2 #(
    .INIT(4'h6)) 
    mul1_mul_temp_carry__3_i_4
       (.I0(mul1_mul_temp__2_n_70),
        .I1(mul1_mul_temp__0_n_87),
        .O(mul1_mul_temp_carry__3_i_4_n_0));
  LUT2 #(
    .INIT(4'h6)) 
    mul1_mul_temp_carry__3_i_5
       (.I0(mul1_mul_temp__2_n_71),
        .I1(mul1_mul_temp__0_n_88),
        .O(mul1_mul_temp_carry__3_i_5_n_0));
  LUT2 #(
    .INIT(4'h6)) 
    mul1_mul_temp_carry__3_i_6
       (.I0(mul1_mul_temp__2_n_72),
        .I1(mul1_mul_temp__0_n_89),
        .O(mul1_mul_temp_carry__3_i_6_n_0));
  LUT2 #(
    .INIT(4'h6)) 
    mul1_mul_temp_carry__3_i_7
       (.I0(mul1_mul_temp__2_n_73),
        .I1(mul1_mul_temp__0_n_90),
        .O(mul1_mul_temp_carry__3_i_7_n_0));
  LUT2 #(
    .INIT(4'h6)) 
    mul1_mul_temp_carry__3_i_8
       (.I0(mul1_mul_temp__2_n_74),
        .I1(mul1_mul_temp__0_n_91),
        .O(mul1_mul_temp_carry__3_i_8_n_0));
  (* ADDER_THRESHOLD = "35" *) 
  CARRY8 mul1_mul_temp_carry__4
       (.CI(mul1_mul_temp_carry__3_n_0),
        .CI_TOP(1'b0),
        .CO({NLW_mul1_mul_temp_carry__4_CO_UNCONNECTED[7],mul1_mul_temp_carry__4_n_1,mul1_mul_temp_carry__4_n_2,mul1_mul_temp_carry__4_n_3,mul1_mul_temp_carry__4_n_4,mul1_mul_temp_carry__4_n_5,mul1_mul_temp_carry__4_n_6,mul1_mul_temp_carry__4_n_7}),
        .DI({1'b0,mul1_mul_temp__2_n_60,mul1_mul_temp__2_n_61,mul1_mul_temp__2_n_62,mul1_mul_temp__2_n_63,mul1_mul_temp__2_n_64,mul1_mul_temp__2_n_65,mul1_mul_temp__2_n_66}),
        .O({mul1_mul_temp_carry__4_n_8,mul1_mul_temp_carry__4_n_9,mul1_mul_temp_carry__4_n_10,mul1_mul_temp_carry__4_n_11,mul1_mul_temp_carry__4_n_12,mul1_mul_temp_carry__4_n_13,mul1_mul_temp_carry__4_n_14,mul1_mul_temp_carry__4_n_15}),
        .S({mul1_mul_temp_carry__4_i_1_n_0,mul1_mul_temp_carry__4_i_2_n_0,mul1_mul_temp_carry__4_i_3_n_0,mul1_mul_temp_carry__4_i_4_n_0,mul1_mul_temp_carry__4_i_5_n_0,mul1_mul_temp_carry__4_i_6_n_0,mul1_mul_temp_carry__4_i_7_n_0,mul1_mul_temp_carry__4_i_8_n_0}));
  LUT2 #(
    .INIT(4'h6)) 
    mul1_mul_temp_carry__4_i_1
       (.I0(mul1_mul_temp__2_n_59),
        .I1(mul1_mul_temp__0_n_76),
        .O(mul1_mul_temp_carry__4_i_1_n_0));
  LUT2 #(
    .INIT(4'h6)) 
    mul1_mul_temp_carry__4_i_2
       (.I0(mul1_mul_temp__2_n_60),
        .I1(mul1_mul_temp__0_n_77),
        .O(mul1_mul_temp_carry__4_i_2_n_0));
  LUT2 #(
    .INIT(4'h6)) 
    mul1_mul_temp_carry__4_i_3
       (.I0(mul1_mul_temp__2_n_61),
        .I1(mul1_mul_temp__0_n_78),
        .O(mul1_mul_temp_carry__4_i_3_n_0));
  LUT2 #(
    .INIT(4'h6)) 
    mul1_mul_temp_carry__4_i_4
       (.I0(mul1_mul_temp__2_n_62),
        .I1(mul1_mul_temp__0_n_79),
        .O(mul1_mul_temp_carry__4_i_4_n_0));
  LUT2 #(
    .INIT(4'h6)) 
    mul1_mul_temp_carry__4_i_5
       (.I0(mul1_mul_temp__2_n_63),
        .I1(mul1_mul_temp__0_n_80),
        .O(mul1_mul_temp_carry__4_i_5_n_0));
  LUT2 #(
    .INIT(4'h6)) 
    mul1_mul_temp_carry__4_i_6
       (.I0(mul1_mul_temp__2_n_64),
        .I1(mul1_mul_temp__0_n_81),
        .O(mul1_mul_temp_carry__4_i_6_n_0));
  LUT2 #(
    .INIT(4'h6)) 
    mul1_mul_temp_carry__4_i_7
       (.I0(mul1_mul_temp__2_n_65),
        .I1(mul1_mul_temp__0_n_82),
        .O(mul1_mul_temp_carry__4_i_7_n_0));
  LUT2 #(
    .INIT(4'h6)) 
    mul1_mul_temp_carry__4_i_8
       (.I0(mul1_mul_temp__2_n_66),
        .I1(mul1_mul_temp__0_n_83),
        .O(mul1_mul_temp_carry__4_i_8_n_0));
  LUT2 #(
    .INIT(4'h6)) 
    mul1_mul_temp_carry_i_1
       (.I0(mul1_mul_temp__2_n_99),
        .I1(mul1_mul_temp_n_99),
        .O(mul1_mul_temp_carry_i_1_n_0));
  LUT2 #(
    .INIT(4'h6)) 
    mul1_mul_temp_carry_i_2
       (.I0(mul1_mul_temp__2_n_100),
        .I1(mul1_mul_temp_n_100),
        .O(mul1_mul_temp_carry_i_2_n_0));
  LUT2 #(
    .INIT(4'h6)) 
    mul1_mul_temp_carry_i_3
       (.I0(mul1_mul_temp__2_n_101),
        .I1(mul1_mul_temp_n_101),
        .O(mul1_mul_temp_carry_i_3_n_0));
  LUT2 #(
    .INIT(4'h6)) 
    mul1_mul_temp_carry_i_4
       (.I0(mul1_mul_temp__2_n_102),
        .I1(mul1_mul_temp_n_102),
        .O(mul1_mul_temp_carry_i_4_n_0));
  LUT2 #(
    .INIT(4'h6)) 
    mul1_mul_temp_carry_i_5
       (.I0(mul1_mul_temp__2_n_103),
        .I1(mul1_mul_temp_n_103),
        .O(mul1_mul_temp_carry_i_5_n_0));
  LUT2 #(
    .INIT(4'h6)) 
    mul1_mul_temp_carry_i_6
       (.I0(mul1_mul_temp__2_n_104),
        .I1(mul1_mul_temp_n_104),
        .O(mul1_mul_temp_carry_i_6_n_0));
  LUT2 #(
    .INIT(4'h6)) 
    mul1_mul_temp_carry_i_7
       (.I0(mul1_mul_temp__2_n_105),
        .I1(mul1_mul_temp_n_105),
        .O(mul1_mul_temp_carry_i_7_n_0));
  LUT4 #(
    .INIT(16'hBFB0)) 
    mul1_mul_temp_i_1
       (.I0(subtractor_sub_temp_carry__0_n_8),
        .I1(subtractor_sub_temp_carry__2_n_0),
        .I2(sel),
        .I3(\aout_tmp_reg[31]_1 [16]),
        .O(mul1_mul_temp_i_1_n_0));
  LUT4 #(
    .INIT(16'hBFB0)) 
    mul1_mul_temp_i_10
       (.I0(subtractor_sub_temp_carry_n_9),
        .I1(subtractor_sub_temp_carry__2_n_0),
        .I2(sel),
        .I3(\aout_tmp_reg[31]_1 [7]),
        .O(mul1_mul_temp_i_10_n_0));
  LUT4 #(
    .INIT(16'hBFB0)) 
    mul1_mul_temp_i_11
       (.I0(subtractor_sub_temp_carry_n_10),
        .I1(subtractor_sub_temp_carry__2_n_0),
        .I2(sel),
        .I3(\aout_tmp_reg[31]_1 [6]),
        .O(mul1_mul_temp_i_11_n_0));
  LUT4 #(
    .INIT(16'hBFB0)) 
    mul1_mul_temp_i_12
       (.I0(subtractor_sub_temp_carry_n_11),
        .I1(subtractor_sub_temp_carry__2_n_0),
        .I2(sel),
        .I3(\aout_tmp_reg[31]_1 [5]),
        .O(mul1_mul_temp_i_12_n_0));
  LUT4 #(
    .INIT(16'hBFB0)) 
    mul1_mul_temp_i_13
       (.I0(subtractor_sub_temp_carry_n_12),
        .I1(subtractor_sub_temp_carry__2_n_0),
        .I2(sel),
        .I3(\aout_tmp_reg[31]_1 [4]),
        .O(mul1_mul_temp_i_13_n_0));
  LUT4 #(
    .INIT(16'hBFB0)) 
    mul1_mul_temp_i_14
       (.I0(subtractor_sub_temp_carry_n_13),
        .I1(subtractor_sub_temp_carry__2_n_0),
        .I2(sel),
        .I3(\aout_tmp_reg[31]_1 [3]),
        .O(mul1_mul_temp_i_14_n_0));
  LUT4 #(
    .INIT(16'hBFB0)) 
    mul1_mul_temp_i_15
       (.I0(subtractor_sub_temp_carry_n_14),
        .I1(subtractor_sub_temp_carry__2_n_0),
        .I2(sel),
        .I3(\aout_tmp_reg[31]_1 [2]),
        .O(mul1_mul_temp_i_15_n_0));
  (* SOFT_HLUTNM = "soft_lutpair20" *) 
  LUT4 #(
    .INIT(16'hBFB0)) 
    mul1_mul_temp_i_16
       (.I0(subtractor_sub_temp_carry_n_15),
        .I1(subtractor_sub_temp_carry__2_n_0),
        .I2(sel),
        .I3(\aout_tmp_reg[31]_1 [1]),
        .O(mul1_mul_temp_i_16_n_0));
  (* SOFT_HLUTNM = "soft_lutpair19" *) 
  LUT4 #(
    .INIT(16'hBFB0)) 
    mul1_mul_temp_i_17
       (.I0(Q[0]),
        .I1(subtractor_sub_temp_carry__2_n_0),
        .I2(sel),
        .I3(\aout_tmp_reg[31]_1 [0]),
        .O(mul1_mul_temp_i_17_n_0));
  LUT4 #(
    .INIT(16'hBFB0)) 
    mul1_mul_temp_i_2
       (.I0(subtractor_sub_temp_carry__0_n_9),
        .I1(subtractor_sub_temp_carry__2_n_0),
        .I2(sel),
        .I3(\aout_tmp_reg[31]_1 [15]),
        .O(mul1_mul_temp_i_2_n_0));
  LUT4 #(
    .INIT(16'hBFB0)) 
    mul1_mul_temp_i_3
       (.I0(subtractor_sub_temp_carry__0_n_10),
        .I1(subtractor_sub_temp_carry__2_n_0),
        .I2(sel),
        .I3(\aout_tmp_reg[31]_1 [14]),
        .O(mul1_mul_temp_i_3_n_0));
  LUT4 #(
    .INIT(16'hBFB0)) 
    mul1_mul_temp_i_4
       (.I0(subtractor_sub_temp_carry__0_n_11),
        .I1(subtractor_sub_temp_carry__2_n_0),
        .I2(sel),
        .I3(\aout_tmp_reg[31]_1 [13]),
        .O(mul1_mul_temp_i_4_n_0));
  LUT4 #(
    .INIT(16'hBFB0)) 
    mul1_mul_temp_i_5
       (.I0(subtractor_sub_temp_carry__0_n_12),
        .I1(subtractor_sub_temp_carry__2_n_0),
        .I2(sel),
        .I3(\aout_tmp_reg[31]_1 [12]),
        .O(mul1_mul_temp_i_5_n_0));
  LUT4 #(
    .INIT(16'hBFB0)) 
    mul1_mul_temp_i_6
       (.I0(subtractor_sub_temp_carry__0_n_13),
        .I1(subtractor_sub_temp_carry__2_n_0),
        .I2(sel),
        .I3(\aout_tmp_reg[31]_1 [11]),
        .O(mul1_mul_temp_i_6_n_0));
  LUT4 #(
    .INIT(16'hBFB0)) 
    mul1_mul_temp_i_7
       (.I0(subtractor_sub_temp_carry__0_n_14),
        .I1(subtractor_sub_temp_carry__2_n_0),
        .I2(sel),
        .I3(\aout_tmp_reg[31]_1 [10]),
        .O(mul1_mul_temp_i_7_n_0));
  LUT4 #(
    .INIT(16'hBFB0)) 
    mul1_mul_temp_i_8
       (.I0(subtractor_sub_temp_carry__0_n_15),
        .I1(subtractor_sub_temp_carry__2_n_0),
        .I2(sel),
        .I3(\aout_tmp_reg[31]_1 [9]),
        .O(mul1_mul_temp_i_8_n_0));
  LUT4 #(
    .INIT(16'hBFB0)) 
    mul1_mul_temp_i_9
       (.I0(subtractor_sub_temp_carry_n_8),
        .I1(subtractor_sub_temp_carry__2_n_0),
        .I2(sel),
        .I3(\aout_tmp_reg[31]_1 [8]),
        .O(mul1_mul_temp_i_9_n_0));
  CARRY8 subtractor_sub_temp_carry
       (.CI(mul1_mul_temp_i_16_0),
        .CI_TOP(1'b0),
        .CO({subtractor_sub_temp_carry_n_0,subtractor_sub_temp_carry_n_1,subtractor_sub_temp_carry_n_2,subtractor_sub_temp_carry_n_3,subtractor_sub_temp_carry_n_4,subtractor_sub_temp_carry_n_5,subtractor_sub_temp_carry_n_6,subtractor_sub_temp_carry_n_7}),
        .DI({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .O({subtractor_sub_temp_carry_n_8,subtractor_sub_temp_carry_n_9,subtractor_sub_temp_carry_n_10,subtractor_sub_temp_carry_n_11,subtractor_sub_temp_carry_n_12,subtractor_sub_temp_carry_n_13,subtractor_sub_temp_carry_n_14,subtractor_sub_temp_carry_n_15}),
        .S(S));
  CARRY8 subtractor_sub_temp_carry__0
       (.CI(subtractor_sub_temp_carry_n_0),
        .CI_TOP(1'b0),
        .CO({subtractor_sub_temp_carry__0_n_0,subtractor_sub_temp_carry__0_n_1,subtractor_sub_temp_carry__0_n_2,subtractor_sub_temp_carry__0_n_3,subtractor_sub_temp_carry__0_n_4,subtractor_sub_temp_carry__0_n_5,subtractor_sub_temp_carry__0_n_6,subtractor_sub_temp_carry__0_n_7}),
        .DI({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .O({subtractor_sub_temp_carry__0_n_8,subtractor_sub_temp_carry__0_n_9,subtractor_sub_temp_carry__0_n_10,subtractor_sub_temp_carry__0_n_11,subtractor_sub_temp_carry__0_n_12,subtractor_sub_temp_carry__0_n_13,subtractor_sub_temp_carry__0_n_14,subtractor_sub_temp_carry__0_n_15}),
        .S(mul1_mul_temp_i_8_0));
  CARRY8 subtractor_sub_temp_carry__1
       (.CI(subtractor_sub_temp_carry__0_n_0),
        .CI_TOP(1'b0),
        .CO({subtractor_sub_temp_carry__1_n_0,subtractor_sub_temp_carry__1_n_1,subtractor_sub_temp_carry__1_n_2,subtractor_sub_temp_carry__1_n_3,subtractor_sub_temp_carry__1_n_4,subtractor_sub_temp_carry__1_n_5,subtractor_sub_temp_carry__1_n_6,subtractor_sub_temp_carry__1_n_7}),
        .DI({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .O({subtractor_sub_temp_carry__1_n_8,subtractor_sub_temp_carry__1_n_9,subtractor_sub_temp_carry__1_n_10,subtractor_sub_temp_carry__1_n_11,subtractor_sub_temp_carry__1_n_12,subtractor_sub_temp_carry__1_n_13,subtractor_sub_temp_carry__1_n_14,subtractor_sub_temp_carry__1_n_15}),
        .S(mul1_mul_temp__0_i_15_0));
  CARRY8 subtractor_sub_temp_carry__2
       (.CI(subtractor_sub_temp_carry__1_n_0),
        .CI_TOP(1'b0),
        .CO({subtractor_sub_temp_carry__2_n_0,NLW_subtractor_sub_temp_carry__2_CO_UNCONNECTED[6],subtractor_sub_temp_carry__2_n_2,subtractor_sub_temp_carry__2_n_3,subtractor_sub_temp_carry__2_n_4,subtractor_sub_temp_carry__2_n_5,subtractor_sub_temp_carry__2_n_6,subtractor_sub_temp_carry__2_n_7}),
        .DI({1'b0,DI,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .O({NLW_subtractor_sub_temp_carry__2_O_UNCONNECTED[7],subtractor_sub_temp_carry__2_n_9,subtractor_sub_temp_carry__2_n_10,subtractor_sub_temp_carry__2_n_11,subtractor_sub_temp_carry__2_n_12,subtractor_sub_temp_carry__2_n_13,subtractor_sub_temp_carry__2_n_14,subtractor_sub_temp_carry__2_n_15}),
        .S({1'b1,Q[31],mul1_mul_temp__0_i_7_0}));
endmodule

(* ORIG_REF_NAME = "IncreEncoder_V24_ip_src_HDL_Reciprocal_core" *) 
module zusys_IncreEncoder_V24_ip_0_0_IncreEncoder_V24_ip_src_HDL_Reciprocal_core_1
   (Q,
    A,
    CEP,
    IPCORE_CLK,
    RSTP,
    DSP_ALU_INST,
    mul1_mul_temp_i_16_0,
    S,
    mul1_mul_temp_i_8_0,
    mul1_mul_temp__0_i_15_0,
    DI,
    mul1_mul_temp__0_i_7_0,
    \ds_reg_reg_reg[3]_0 ,
    Div_i1_mul_temp_i_50_0,
    write_axi_enable,
    sel,
    DSP_A_B_DATA_INST,
    DSP_A_B_DATA_INST_0,
    DSP_A_B_DATA_INST_1);
  output [31:0]Q;
  output [23:0]A;
  input CEP;
  input IPCORE_CLK;
  input RSTP;
  input [31:0]DSP_ALU_INST;
  input mul1_mul_temp_i_16_0;
  input [7:0]S;
  input [7:0]mul1_mul_temp_i_8_0;
  input [7:0]mul1_mul_temp__0_i_15_0;
  input [0:0]DI;
  input [5:0]mul1_mul_temp__0_i_7_0;
  input [3:0]\ds_reg_reg_reg[3]_0 ;
  input Div_i1_mul_temp_i_50_0;
  input write_axi_enable;
  input sel;
  input [29:0]DSP_A_B_DATA_INST;
  input [0:0]DSP_A_B_DATA_INST_0;
  input DSP_A_B_DATA_INST_1;

  wire [23:0]A;
  wire CEP;
  wire [0:0]DI;
  wire [31:0]DSP_ALU_INST;
  wire [29:0]DSP_A_B_DATA_INST;
  wire [0:0]DSP_A_B_DATA_INST_0;
  wire DSP_A_B_DATA_INST_1;
  wire Div_i1_mul_temp_i_100_n_0;
  wire Div_i1_mul_temp_i_101_n_0;
  wire Div_i1_mul_temp_i_102_n_0;
  wire Div_i1_mul_temp_i_103_n_0;
  wire Div_i1_mul_temp_i_104_n_0;
  wire Div_i1_mul_temp_i_105_n_0;
  wire Div_i1_mul_temp_i_106_n_0;
  wire Div_i1_mul_temp_i_107_n_0;
  wire Div_i1_mul_temp_i_108_n_0;
  wire Div_i1_mul_temp_i_109_n_0;
  wire Div_i1_mul_temp_i_110_n_0;
  wire Div_i1_mul_temp_i_111_n_0;
  wire Div_i1_mul_temp_i_112_n_0;
  wire Div_i1_mul_temp_i_113_n_0;
  wire Div_i1_mul_temp_i_114_n_0;
  wire Div_i1_mul_temp_i_115_n_0;
  wire Div_i1_mul_temp_i_116_n_0;
  wire Div_i1_mul_temp_i_117_n_0;
  wire Div_i1_mul_temp_i_118_n_0;
  wire Div_i1_mul_temp_i_119_n_0;
  wire Div_i1_mul_temp_i_120_n_0;
  wire Div_i1_mul_temp_i_121_n_0;
  wire Div_i1_mul_temp_i_122_n_0;
  wire Div_i1_mul_temp_i_123_n_0;
  wire Div_i1_mul_temp_i_124_n_0;
  wire Div_i1_mul_temp_i_125_n_0;
  wire Div_i1_mul_temp_i_126_n_0;
  wire Div_i1_mul_temp_i_127_n_0;
  wire Div_i1_mul_temp_i_128_n_0;
  wire Div_i1_mul_temp_i_129_n_0;
  wire Div_i1_mul_temp_i_130_n_0;
  wire Div_i1_mul_temp_i_131_n_0;
  wire Div_i1_mul_temp_i_132_n_0;
  wire Div_i1_mul_temp_i_133_n_0;
  wire Div_i1_mul_temp_i_134_n_0;
  wire Div_i1_mul_temp_i_135_n_0;
  wire Div_i1_mul_temp_i_136_n_0;
  wire Div_i1_mul_temp_i_137_n_0;
  wire Div_i1_mul_temp_i_138_n_0;
  wire Div_i1_mul_temp_i_139_n_0;
  wire Div_i1_mul_temp_i_140_n_0;
  wire Div_i1_mul_temp_i_141_n_0;
  wire Div_i1_mul_temp_i_142_n_0;
  wire Div_i1_mul_temp_i_143_n_0;
  wire Div_i1_mul_temp_i_144_n_0;
  wire Div_i1_mul_temp_i_145_n_0;
  wire Div_i1_mul_temp_i_146_n_0;
  wire Div_i1_mul_temp_i_147_n_0;
  wire Div_i1_mul_temp_i_148_n_0;
  wire Div_i1_mul_temp_i_149_n_0;
  wire Div_i1_mul_temp_i_150_n_0;
  wire Div_i1_mul_temp_i_151_n_0;
  wire Div_i1_mul_temp_i_152_n_0;
  wire Div_i1_mul_temp_i_153_n_0;
  wire Div_i1_mul_temp_i_154_n_0;
  wire Div_i1_mul_temp_i_155_n_0;
  wire Div_i1_mul_temp_i_156_n_0;
  wire Div_i1_mul_temp_i_157_n_0;
  wire Div_i1_mul_temp_i_158_n_0;
  wire Div_i1_mul_temp_i_159_n_0;
  wire Div_i1_mul_temp_i_160_n_0;
  wire Div_i1_mul_temp_i_161_n_0;
  wire Div_i1_mul_temp_i_162_n_0;
  wire Div_i1_mul_temp_i_163_n_0;
  wire Div_i1_mul_temp_i_164_n_0;
  wire Div_i1_mul_temp_i_165_n_0;
  wire Div_i1_mul_temp_i_166_n_0;
  wire Div_i1_mul_temp_i_167_n_0;
  wire Div_i1_mul_temp_i_168_n_0;
  wire Div_i1_mul_temp_i_169_n_0;
  wire Div_i1_mul_temp_i_170_n_0;
  wire Div_i1_mul_temp_i_171_n_0;
  wire Div_i1_mul_temp_i_172_n_0;
  wire Div_i1_mul_temp_i_173_n_0;
  wire Div_i1_mul_temp_i_174_n_0;
  wire Div_i1_mul_temp_i_175_n_0;
  wire Div_i1_mul_temp_i_176_n_0;
  wire Div_i1_mul_temp_i_177_n_0;
  wire Div_i1_mul_temp_i_178_n_0;
  wire Div_i1_mul_temp_i_179_n_0;
  wire Div_i1_mul_temp_i_41_n_2;
  wire Div_i1_mul_temp_i_41_n_3;
  wire Div_i1_mul_temp_i_41_n_4;
  wire Div_i1_mul_temp_i_41_n_5;
  wire Div_i1_mul_temp_i_41_n_6;
  wire Div_i1_mul_temp_i_41_n_7;
  wire Div_i1_mul_temp_i_42_n_0;
  wire Div_i1_mul_temp_i_43_n_0;
  wire Div_i1_mul_temp_i_44_n_0;
  wire Div_i1_mul_temp_i_45_n_0;
  wire Div_i1_mul_temp_i_46_n_0;
  wire Div_i1_mul_temp_i_47_n_0;
  wire Div_i1_mul_temp_i_48_n_0;
  wire Div_i1_mul_temp_i_49_n_0;
  wire Div_i1_mul_temp_i_50_0;
  wire Div_i1_mul_temp_i_50_n_0;
  wire Div_i1_mul_temp_i_50_n_1;
  wire Div_i1_mul_temp_i_50_n_2;
  wire Div_i1_mul_temp_i_50_n_3;
  wire Div_i1_mul_temp_i_50_n_4;
  wire Div_i1_mul_temp_i_50_n_5;
  wire Div_i1_mul_temp_i_50_n_6;
  wire Div_i1_mul_temp_i_50_n_7;
  wire Div_i1_mul_temp_i_51_n_0;
  wire Div_i1_mul_temp_i_52_n_0;
  wire Div_i1_mul_temp_i_53_n_0;
  wire Div_i1_mul_temp_i_54_n_0;
  wire Div_i1_mul_temp_i_55_n_0;
  wire Div_i1_mul_temp_i_56_n_0;
  wire Div_i1_mul_temp_i_57_n_0;
  wire Div_i1_mul_temp_i_58_n_0;
  wire Div_i1_mul_temp_i_59_n_0;
  wire Div_i1_mul_temp_i_59_n_1;
  wire Div_i1_mul_temp_i_59_n_2;
  wire Div_i1_mul_temp_i_59_n_3;
  wire Div_i1_mul_temp_i_59_n_4;
  wire Div_i1_mul_temp_i_59_n_5;
  wire Div_i1_mul_temp_i_59_n_6;
  wire Div_i1_mul_temp_i_59_n_7;
  wire Div_i1_mul_temp_i_60_n_0;
  wire Div_i1_mul_temp_i_61_n_0;
  wire Div_i1_mul_temp_i_62_n_0;
  wire Div_i1_mul_temp_i_63_n_0;
  wire Div_i1_mul_temp_i_64_n_0;
  wire Div_i1_mul_temp_i_65_n_0;
  wire Div_i1_mul_temp_i_66_n_0;
  wire Div_i1_mul_temp_i_67_n_0;
  wire Div_i1_mul_temp_i_68_n_0;
  wire Div_i1_mul_temp_i_69_n_0;
  wire Div_i1_mul_temp_i_70_n_0;
  wire Div_i1_mul_temp_i_71_n_0;
  wire Div_i1_mul_temp_i_72_n_0;
  wire Div_i1_mul_temp_i_73_n_0;
  wire Div_i1_mul_temp_i_74_n_0;
  wire Div_i1_mul_temp_i_75_n_0;
  wire Div_i1_mul_temp_i_76_n_0;
  wire Div_i1_mul_temp_i_77_n_0;
  wire Div_i1_mul_temp_i_78_n_0;
  wire Div_i1_mul_temp_i_79_n_0;
  wire Div_i1_mul_temp_i_80_n_0;
  wire Div_i1_mul_temp_i_81_n_0;
  wire Div_i1_mul_temp_i_82_n_0;
  wire Div_i1_mul_temp_i_83_n_0;
  wire Div_i1_mul_temp_i_84_n_0;
  wire Div_i1_mul_temp_i_85_n_0;
  wire Div_i1_mul_temp_i_86_n_0;
  wire Div_i1_mul_temp_i_87_n_0;
  wire Div_i1_mul_temp_i_88_n_0;
  wire Div_i1_mul_temp_i_89_n_0;
  wire Div_i1_mul_temp_i_90_n_0;
  wire Div_i1_mul_temp_i_91_n_0;
  wire Div_i1_mul_temp_i_92_n_0;
  wire Div_i1_mul_temp_i_93_n_0;
  wire Div_i1_mul_temp_i_94_n_0;
  wire Div_i1_mul_temp_i_95_n_0;
  wire Div_i1_mul_temp_i_96_n_0;
  wire Div_i1_mul_temp_i_97_n_0;
  wire Div_i1_mul_temp_i_98_n_0;
  wire Div_i1_mul_temp_i_99_n_0;
  wire IPCORE_CLK;
  wire [31:0]Q;
  wire RSTP;
  wire [7:0]S;
  wire \delayout[0]_i_1_n_0 ;
  wire \delayout[10]_i_1_n_0 ;
  wire \delayout[11]_i_1_n_0 ;
  wire \delayout[12]_i_1_n_0 ;
  wire \delayout[13]_i_1_n_0 ;
  wire \delayout[14]_i_1_n_0 ;
  wire \delayout[15]_i_1_n_0 ;
  wire \delayout[16]_i_1_n_0 ;
  wire \delayout[17]_i_1_n_0 ;
  wire \delayout[18]_i_1_n_0 ;
  wire \delayout[19]_i_1_n_0 ;
  wire \delayout[1]_i_1_n_0 ;
  wire \delayout[20]_i_1_n_0 ;
  wire \delayout[21]_i_1_n_0 ;
  wire \delayout[22]_i_1_n_0 ;
  wire \delayout[23]_i_1_n_0 ;
  wire \delayout[24]_i_1_n_0 ;
  wire \delayout[25]_i_1_n_0 ;
  wire \delayout[26]_i_1_n_0 ;
  wire \delayout[27]_i_1_n_0 ;
  wire \delayout[28]_i_1_n_0 ;
  wire \delayout[29]_i_1_n_0 ;
  wire \delayout[2]_i_1_n_0 ;
  wire \delayout[30]_i_1_n_0 ;
  wire \delayout[31]_i_1_n_0 ;
  wire \delayout[3]_i_1_n_0 ;
  wire \delayout[4]_i_1_n_0 ;
  wire \delayout[5]_i_1_n_0 ;
  wire \delayout[6]_i_1_n_0 ;
  wire \delayout[7]_i_1_n_0 ;
  wire \delayout[8]_i_1_n_0 ;
  wire \delayout[9]_i_1_n_0 ;
  wire [3:0]\ds_reg_reg_reg[3]_0 ;
  wire mul1_mul_temp__0_i_10_n_0;
  wire mul1_mul_temp__0_i_11_n_0;
  wire mul1_mul_temp__0_i_12_n_0;
  wire mul1_mul_temp__0_i_13_n_0;
  wire mul1_mul_temp__0_i_14_n_0;
  wire [7:0]mul1_mul_temp__0_i_15_0;
  wire mul1_mul_temp__0_i_15_n_0;
  wire mul1_mul_temp__0_i_1_n_0;
  wire mul1_mul_temp__0_i_2_n_0;
  wire mul1_mul_temp__0_i_3_n_0;
  wire mul1_mul_temp__0_i_4_n_0;
  wire mul1_mul_temp__0_i_5_n_0;
  wire mul1_mul_temp__0_i_6_n_0;
  wire [5:0]mul1_mul_temp__0_i_7_0;
  wire mul1_mul_temp__0_i_7_n_0;
  wire mul1_mul_temp__0_i_8_n_0;
  wire mul1_mul_temp__0_i_9_n_0;
  wire mul1_mul_temp__0_n_100;
  wire mul1_mul_temp__0_n_101;
  wire mul1_mul_temp__0_n_102;
  wire mul1_mul_temp__0_n_103;
  wire mul1_mul_temp__0_n_104;
  wire mul1_mul_temp__0_n_105;
  wire mul1_mul_temp__0_n_76;
  wire mul1_mul_temp__0_n_77;
  wire mul1_mul_temp__0_n_78;
  wire mul1_mul_temp__0_n_79;
  wire mul1_mul_temp__0_n_80;
  wire mul1_mul_temp__0_n_81;
  wire mul1_mul_temp__0_n_82;
  wire mul1_mul_temp__0_n_83;
  wire mul1_mul_temp__0_n_84;
  wire mul1_mul_temp__0_n_85;
  wire mul1_mul_temp__0_n_86;
  wire mul1_mul_temp__0_n_87;
  wire mul1_mul_temp__0_n_88;
  wire mul1_mul_temp__0_n_89;
  wire mul1_mul_temp__0_n_90;
  wire mul1_mul_temp__0_n_91;
  wire mul1_mul_temp__0_n_92;
  wire mul1_mul_temp__0_n_93;
  wire mul1_mul_temp__0_n_94;
  wire mul1_mul_temp__0_n_95;
  wire mul1_mul_temp__0_n_96;
  wire mul1_mul_temp__0_n_97;
  wire mul1_mul_temp__0_n_98;
  wire mul1_mul_temp__0_n_99;
  wire mul1_mul_temp__1_n_100;
  wire mul1_mul_temp__1_n_101;
  wire mul1_mul_temp__1_n_102;
  wire mul1_mul_temp__1_n_103;
  wire mul1_mul_temp__1_n_104;
  wire mul1_mul_temp__1_n_105;
  wire mul1_mul_temp__1_n_106;
  wire mul1_mul_temp__1_n_107;
  wire mul1_mul_temp__1_n_108;
  wire mul1_mul_temp__1_n_109;
  wire mul1_mul_temp__1_n_110;
  wire mul1_mul_temp__1_n_111;
  wire mul1_mul_temp__1_n_112;
  wire mul1_mul_temp__1_n_113;
  wire mul1_mul_temp__1_n_114;
  wire mul1_mul_temp__1_n_115;
  wire mul1_mul_temp__1_n_116;
  wire mul1_mul_temp__1_n_117;
  wire mul1_mul_temp__1_n_118;
  wire mul1_mul_temp__1_n_119;
  wire mul1_mul_temp__1_n_120;
  wire mul1_mul_temp__1_n_121;
  wire mul1_mul_temp__1_n_122;
  wire mul1_mul_temp__1_n_123;
  wire mul1_mul_temp__1_n_124;
  wire mul1_mul_temp__1_n_125;
  wire mul1_mul_temp__1_n_126;
  wire mul1_mul_temp__1_n_127;
  wire mul1_mul_temp__1_n_128;
  wire mul1_mul_temp__1_n_129;
  wire mul1_mul_temp__1_n_130;
  wire mul1_mul_temp__1_n_131;
  wire mul1_mul_temp__1_n_132;
  wire mul1_mul_temp__1_n_133;
  wire mul1_mul_temp__1_n_134;
  wire mul1_mul_temp__1_n_135;
  wire mul1_mul_temp__1_n_136;
  wire mul1_mul_temp__1_n_137;
  wire mul1_mul_temp__1_n_138;
  wire mul1_mul_temp__1_n_139;
  wire mul1_mul_temp__1_n_140;
  wire mul1_mul_temp__1_n_141;
  wire mul1_mul_temp__1_n_142;
  wire mul1_mul_temp__1_n_143;
  wire mul1_mul_temp__1_n_144;
  wire mul1_mul_temp__1_n_145;
  wire mul1_mul_temp__1_n_146;
  wire mul1_mul_temp__1_n_147;
  wire mul1_mul_temp__1_n_148;
  wire mul1_mul_temp__1_n_149;
  wire mul1_mul_temp__1_n_150;
  wire mul1_mul_temp__1_n_151;
  wire mul1_mul_temp__1_n_152;
  wire mul1_mul_temp__1_n_153;
  wire mul1_mul_temp__1_n_58;
  wire mul1_mul_temp__1_n_59;
  wire mul1_mul_temp__1_n_60;
  wire mul1_mul_temp__1_n_61;
  wire mul1_mul_temp__1_n_62;
  wire mul1_mul_temp__1_n_63;
  wire mul1_mul_temp__1_n_64;
  wire mul1_mul_temp__1_n_65;
  wire mul1_mul_temp__1_n_66;
  wire mul1_mul_temp__1_n_67;
  wire mul1_mul_temp__1_n_68;
  wire mul1_mul_temp__1_n_69;
  wire mul1_mul_temp__1_n_70;
  wire mul1_mul_temp__1_n_71;
  wire mul1_mul_temp__1_n_72;
  wire mul1_mul_temp__1_n_73;
  wire mul1_mul_temp__1_n_74;
  wire mul1_mul_temp__1_n_75;
  wire mul1_mul_temp__1_n_76;
  wire mul1_mul_temp__1_n_77;
  wire mul1_mul_temp__1_n_78;
  wire mul1_mul_temp__1_n_79;
  wire mul1_mul_temp__1_n_80;
  wire mul1_mul_temp__1_n_81;
  wire mul1_mul_temp__1_n_82;
  wire mul1_mul_temp__1_n_83;
  wire mul1_mul_temp__1_n_84;
  wire mul1_mul_temp__1_n_85;
  wire mul1_mul_temp__1_n_86;
  wire mul1_mul_temp__1_n_87;
  wire mul1_mul_temp__1_n_88;
  wire mul1_mul_temp__1_n_89;
  wire mul1_mul_temp__1_n_90;
  wire mul1_mul_temp__1_n_91;
  wire mul1_mul_temp__1_n_92;
  wire mul1_mul_temp__1_n_93;
  wire mul1_mul_temp__1_n_94;
  wire mul1_mul_temp__1_n_95;
  wire mul1_mul_temp__1_n_96;
  wire mul1_mul_temp__1_n_97;
  wire mul1_mul_temp__1_n_98;
  wire mul1_mul_temp__1_n_99;
  wire mul1_mul_temp__2_n_100;
  wire mul1_mul_temp__2_n_101;
  wire mul1_mul_temp__2_n_102;
  wire mul1_mul_temp__2_n_103;
  wire mul1_mul_temp__2_n_104;
  wire mul1_mul_temp__2_n_105;
  wire mul1_mul_temp__2_n_59;
  wire mul1_mul_temp__2_n_60;
  wire mul1_mul_temp__2_n_61;
  wire mul1_mul_temp__2_n_62;
  wire mul1_mul_temp__2_n_63;
  wire mul1_mul_temp__2_n_64;
  wire mul1_mul_temp__2_n_65;
  wire mul1_mul_temp__2_n_66;
  wire mul1_mul_temp__2_n_67;
  wire mul1_mul_temp__2_n_68;
  wire mul1_mul_temp__2_n_69;
  wire mul1_mul_temp__2_n_70;
  wire mul1_mul_temp__2_n_71;
  wire mul1_mul_temp__2_n_72;
  wire mul1_mul_temp__2_n_73;
  wire mul1_mul_temp__2_n_74;
  wire mul1_mul_temp__2_n_75;
  wire mul1_mul_temp__2_n_76;
  wire mul1_mul_temp__2_n_77;
  wire mul1_mul_temp__2_n_78;
  wire mul1_mul_temp__2_n_79;
  wire mul1_mul_temp__2_n_80;
  wire mul1_mul_temp__2_n_81;
  wire mul1_mul_temp__2_n_82;
  wire mul1_mul_temp__2_n_83;
  wire mul1_mul_temp__2_n_84;
  wire mul1_mul_temp__2_n_85;
  wire mul1_mul_temp__2_n_86;
  wire mul1_mul_temp__2_n_87;
  wire mul1_mul_temp__2_n_88;
  wire mul1_mul_temp__2_n_89;
  wire mul1_mul_temp__2_n_90;
  wire mul1_mul_temp__2_n_91;
  wire mul1_mul_temp__2_n_92;
  wire mul1_mul_temp__2_n_93;
  wire mul1_mul_temp__2_n_94;
  wire mul1_mul_temp__2_n_95;
  wire mul1_mul_temp__2_n_96;
  wire mul1_mul_temp__2_n_97;
  wire mul1_mul_temp__2_n_98;
  wire mul1_mul_temp__2_n_99;
  wire mul1_mul_temp_carry__0_i_1__0_n_0;
  wire mul1_mul_temp_carry__0_i_2__0_n_0;
  wire mul1_mul_temp_carry__0_i_3__0_n_0;
  wire mul1_mul_temp_carry__0_i_4__0_n_0;
  wire mul1_mul_temp_carry__0_i_5__0_n_0;
  wire mul1_mul_temp_carry__0_i_6__0_n_0;
  wire mul1_mul_temp_carry__0_i_7__0_n_0;
  wire mul1_mul_temp_carry__0_i_8__0_n_0;
  wire mul1_mul_temp_carry__0_n_0;
  wire mul1_mul_temp_carry__0_n_1;
  wire mul1_mul_temp_carry__0_n_2;
  wire mul1_mul_temp_carry__0_n_3;
  wire mul1_mul_temp_carry__0_n_4;
  wire mul1_mul_temp_carry__0_n_5;
  wire mul1_mul_temp_carry__0_n_6;
  wire mul1_mul_temp_carry__0_n_7;
  wire mul1_mul_temp_carry__0_n_8;
  wire mul1_mul_temp_carry__0_n_9;
  wire mul1_mul_temp_carry__1_i_1__0_n_0;
  wire mul1_mul_temp_carry__1_i_2__0_n_0;
  wire mul1_mul_temp_carry__1_i_3__0_n_0;
  wire mul1_mul_temp_carry__1_i_4__0_n_0;
  wire mul1_mul_temp_carry__1_i_5__0_n_0;
  wire mul1_mul_temp_carry__1_i_6__0_n_0;
  wire mul1_mul_temp_carry__1_i_7__0_n_0;
  wire mul1_mul_temp_carry__1_i_8__0_n_0;
  wire mul1_mul_temp_carry__1_n_0;
  wire mul1_mul_temp_carry__1_n_1;
  wire mul1_mul_temp_carry__1_n_10;
  wire mul1_mul_temp_carry__1_n_11;
  wire mul1_mul_temp_carry__1_n_12;
  wire mul1_mul_temp_carry__1_n_13;
  wire mul1_mul_temp_carry__1_n_14;
  wire mul1_mul_temp_carry__1_n_15;
  wire mul1_mul_temp_carry__1_n_2;
  wire mul1_mul_temp_carry__1_n_3;
  wire mul1_mul_temp_carry__1_n_4;
  wire mul1_mul_temp_carry__1_n_5;
  wire mul1_mul_temp_carry__1_n_6;
  wire mul1_mul_temp_carry__1_n_7;
  wire mul1_mul_temp_carry__1_n_8;
  wire mul1_mul_temp_carry__1_n_9;
  wire mul1_mul_temp_carry__2_i_1__0_n_0;
  wire mul1_mul_temp_carry__2_i_2__0_n_0;
  wire mul1_mul_temp_carry__2_i_3__0_n_0;
  wire mul1_mul_temp_carry__2_i_4__0_n_0;
  wire mul1_mul_temp_carry__2_i_5__0_n_0;
  wire mul1_mul_temp_carry__2_i_6__0_n_0;
  wire mul1_mul_temp_carry__2_i_7__0_n_0;
  wire mul1_mul_temp_carry__2_i_8__0_n_0;
  wire mul1_mul_temp_carry__2_n_0;
  wire mul1_mul_temp_carry__2_n_1;
  wire mul1_mul_temp_carry__2_n_10;
  wire mul1_mul_temp_carry__2_n_11;
  wire mul1_mul_temp_carry__2_n_12;
  wire mul1_mul_temp_carry__2_n_13;
  wire mul1_mul_temp_carry__2_n_14;
  wire mul1_mul_temp_carry__2_n_15;
  wire mul1_mul_temp_carry__2_n_2;
  wire mul1_mul_temp_carry__2_n_3;
  wire mul1_mul_temp_carry__2_n_4;
  wire mul1_mul_temp_carry__2_n_5;
  wire mul1_mul_temp_carry__2_n_6;
  wire mul1_mul_temp_carry__2_n_7;
  wire mul1_mul_temp_carry__2_n_8;
  wire mul1_mul_temp_carry__2_n_9;
  wire mul1_mul_temp_carry__3_i_1__0_n_0;
  wire mul1_mul_temp_carry__3_i_2__0_n_0;
  wire mul1_mul_temp_carry__3_i_3__0_n_0;
  wire mul1_mul_temp_carry__3_i_4__0_n_0;
  wire mul1_mul_temp_carry__3_i_5__0_n_0;
  wire mul1_mul_temp_carry__3_i_6__0_n_0;
  wire mul1_mul_temp_carry__3_i_7__0_n_0;
  wire mul1_mul_temp_carry__3_i_8__0_n_0;
  wire mul1_mul_temp_carry__3_n_0;
  wire mul1_mul_temp_carry__3_n_1;
  wire mul1_mul_temp_carry__3_n_10;
  wire mul1_mul_temp_carry__3_n_11;
  wire mul1_mul_temp_carry__3_n_12;
  wire mul1_mul_temp_carry__3_n_13;
  wire mul1_mul_temp_carry__3_n_14;
  wire mul1_mul_temp_carry__3_n_15;
  wire mul1_mul_temp_carry__3_n_2;
  wire mul1_mul_temp_carry__3_n_3;
  wire mul1_mul_temp_carry__3_n_4;
  wire mul1_mul_temp_carry__3_n_5;
  wire mul1_mul_temp_carry__3_n_6;
  wire mul1_mul_temp_carry__3_n_7;
  wire mul1_mul_temp_carry__3_n_8;
  wire mul1_mul_temp_carry__3_n_9;
  wire mul1_mul_temp_carry__4_i_1__0_n_0;
  wire mul1_mul_temp_carry__4_i_2__0_n_0;
  wire mul1_mul_temp_carry__4_i_3__0_n_0;
  wire mul1_mul_temp_carry__4_i_4__0_n_0;
  wire mul1_mul_temp_carry__4_i_5__0_n_0;
  wire mul1_mul_temp_carry__4_i_6__0_n_0;
  wire mul1_mul_temp_carry__4_i_7__0_n_0;
  wire mul1_mul_temp_carry__4_i_8__0_n_0;
  wire mul1_mul_temp_carry__4_n_1;
  wire mul1_mul_temp_carry__4_n_10;
  wire mul1_mul_temp_carry__4_n_11;
  wire mul1_mul_temp_carry__4_n_12;
  wire mul1_mul_temp_carry__4_n_13;
  wire mul1_mul_temp_carry__4_n_14;
  wire mul1_mul_temp_carry__4_n_15;
  wire mul1_mul_temp_carry__4_n_2;
  wire mul1_mul_temp_carry__4_n_3;
  wire mul1_mul_temp_carry__4_n_4;
  wire mul1_mul_temp_carry__4_n_5;
  wire mul1_mul_temp_carry__4_n_6;
  wire mul1_mul_temp_carry__4_n_7;
  wire mul1_mul_temp_carry__4_n_8;
  wire mul1_mul_temp_carry__4_n_9;
  wire mul1_mul_temp_carry_i_1__0_n_0;
  wire mul1_mul_temp_carry_i_2__0_n_0;
  wire mul1_mul_temp_carry_i_3__0_n_0;
  wire mul1_mul_temp_carry_i_4__0_n_0;
  wire mul1_mul_temp_carry_i_5__0_n_0;
  wire mul1_mul_temp_carry_i_6__0_n_0;
  wire mul1_mul_temp_carry_i_7__0_n_0;
  wire mul1_mul_temp_carry_n_0;
  wire mul1_mul_temp_carry_n_1;
  wire mul1_mul_temp_carry_n_2;
  wire mul1_mul_temp_carry_n_3;
  wire mul1_mul_temp_carry_n_4;
  wire mul1_mul_temp_carry_n_5;
  wire mul1_mul_temp_carry_n_6;
  wire mul1_mul_temp_carry_n_7;
  wire mul1_mul_temp_i_10_n_0;
  wire mul1_mul_temp_i_11_n_0;
  wire mul1_mul_temp_i_12_n_0;
  wire mul1_mul_temp_i_13_n_0;
  wire mul1_mul_temp_i_14_n_0;
  wire mul1_mul_temp_i_15_n_0;
  wire mul1_mul_temp_i_16_0;
  wire mul1_mul_temp_i_16_n_0;
  wire mul1_mul_temp_i_17_n_0;
  wire mul1_mul_temp_i_1_n_0;
  wire mul1_mul_temp_i_2_n_0;
  wire mul1_mul_temp_i_3_n_0;
  wire mul1_mul_temp_i_4_n_0;
  wire mul1_mul_temp_i_5_n_0;
  wire mul1_mul_temp_i_6_n_0;
  wire mul1_mul_temp_i_7_n_0;
  wire [7:0]mul1_mul_temp_i_8_0;
  wire mul1_mul_temp_i_8_n_0;
  wire mul1_mul_temp_i_9_n_0;
  wire mul1_mul_temp_n_100;
  wire mul1_mul_temp_n_101;
  wire mul1_mul_temp_n_102;
  wire mul1_mul_temp_n_103;
  wire mul1_mul_temp_n_104;
  wire mul1_mul_temp_n_105;
  wire mul1_mul_temp_n_106;
  wire mul1_mul_temp_n_107;
  wire mul1_mul_temp_n_108;
  wire mul1_mul_temp_n_109;
  wire mul1_mul_temp_n_110;
  wire mul1_mul_temp_n_111;
  wire mul1_mul_temp_n_112;
  wire mul1_mul_temp_n_113;
  wire mul1_mul_temp_n_114;
  wire mul1_mul_temp_n_115;
  wire mul1_mul_temp_n_116;
  wire mul1_mul_temp_n_117;
  wire mul1_mul_temp_n_118;
  wire mul1_mul_temp_n_119;
  wire mul1_mul_temp_n_120;
  wire mul1_mul_temp_n_121;
  wire mul1_mul_temp_n_122;
  wire mul1_mul_temp_n_123;
  wire mul1_mul_temp_n_124;
  wire mul1_mul_temp_n_125;
  wire mul1_mul_temp_n_126;
  wire mul1_mul_temp_n_127;
  wire mul1_mul_temp_n_128;
  wire mul1_mul_temp_n_129;
  wire mul1_mul_temp_n_130;
  wire mul1_mul_temp_n_131;
  wire mul1_mul_temp_n_132;
  wire mul1_mul_temp_n_133;
  wire mul1_mul_temp_n_134;
  wire mul1_mul_temp_n_135;
  wire mul1_mul_temp_n_136;
  wire mul1_mul_temp_n_137;
  wire mul1_mul_temp_n_138;
  wire mul1_mul_temp_n_139;
  wire mul1_mul_temp_n_140;
  wire mul1_mul_temp_n_141;
  wire mul1_mul_temp_n_142;
  wire mul1_mul_temp_n_143;
  wire mul1_mul_temp_n_144;
  wire mul1_mul_temp_n_145;
  wire mul1_mul_temp_n_146;
  wire mul1_mul_temp_n_147;
  wire mul1_mul_temp_n_148;
  wire mul1_mul_temp_n_149;
  wire mul1_mul_temp_n_150;
  wire mul1_mul_temp_n_151;
  wire mul1_mul_temp_n_152;
  wire mul1_mul_temp_n_153;
  wire mul1_mul_temp_n_58;
  wire mul1_mul_temp_n_59;
  wire mul1_mul_temp_n_60;
  wire mul1_mul_temp_n_61;
  wire mul1_mul_temp_n_62;
  wire mul1_mul_temp_n_63;
  wire mul1_mul_temp_n_64;
  wire mul1_mul_temp_n_65;
  wire mul1_mul_temp_n_66;
  wire mul1_mul_temp_n_67;
  wire mul1_mul_temp_n_68;
  wire mul1_mul_temp_n_69;
  wire mul1_mul_temp_n_70;
  wire mul1_mul_temp_n_71;
  wire mul1_mul_temp_n_72;
  wire mul1_mul_temp_n_73;
  wire mul1_mul_temp_n_74;
  wire mul1_mul_temp_n_75;
  wire mul1_mul_temp_n_76;
  wire mul1_mul_temp_n_77;
  wire mul1_mul_temp_n_78;
  wire mul1_mul_temp_n_79;
  wire mul1_mul_temp_n_80;
  wire mul1_mul_temp_n_81;
  wire mul1_mul_temp_n_82;
  wire mul1_mul_temp_n_83;
  wire mul1_mul_temp_n_84;
  wire mul1_mul_temp_n_85;
  wire mul1_mul_temp_n_86;
  wire mul1_mul_temp_n_87;
  wire mul1_mul_temp_n_88;
  wire mul1_mul_temp_n_89;
  wire mul1_mul_temp_n_90;
  wire mul1_mul_temp_n_91;
  wire mul1_mul_temp_n_92;
  wire mul1_mul_temp_n_93;
  wire mul1_mul_temp_n_94;
  wire mul1_mul_temp_n_95;
  wire mul1_mul_temp_n_96;
  wire mul1_mul_temp_n_97;
  wire mul1_mul_temp_n_98;
  wire mul1_mul_temp_n_99;
  wire sel;
  wire \shiftarr[0]0 ;
  wire subtractor_sub_temp_carry__0_n_0;
  wire subtractor_sub_temp_carry__0_n_1;
  wire subtractor_sub_temp_carry__0_n_10;
  wire subtractor_sub_temp_carry__0_n_11;
  wire subtractor_sub_temp_carry__0_n_12;
  wire subtractor_sub_temp_carry__0_n_13;
  wire subtractor_sub_temp_carry__0_n_14;
  wire subtractor_sub_temp_carry__0_n_15;
  wire subtractor_sub_temp_carry__0_n_2;
  wire subtractor_sub_temp_carry__0_n_3;
  wire subtractor_sub_temp_carry__0_n_4;
  wire subtractor_sub_temp_carry__0_n_5;
  wire subtractor_sub_temp_carry__0_n_6;
  wire subtractor_sub_temp_carry__0_n_7;
  wire subtractor_sub_temp_carry__0_n_8;
  wire subtractor_sub_temp_carry__0_n_9;
  wire subtractor_sub_temp_carry__1_n_0;
  wire subtractor_sub_temp_carry__1_n_1;
  wire subtractor_sub_temp_carry__1_n_10;
  wire subtractor_sub_temp_carry__1_n_11;
  wire subtractor_sub_temp_carry__1_n_12;
  wire subtractor_sub_temp_carry__1_n_13;
  wire subtractor_sub_temp_carry__1_n_14;
  wire subtractor_sub_temp_carry__1_n_15;
  wire subtractor_sub_temp_carry__1_n_2;
  wire subtractor_sub_temp_carry__1_n_3;
  wire subtractor_sub_temp_carry__1_n_4;
  wire subtractor_sub_temp_carry__1_n_5;
  wire subtractor_sub_temp_carry__1_n_6;
  wire subtractor_sub_temp_carry__1_n_7;
  wire subtractor_sub_temp_carry__1_n_8;
  wire subtractor_sub_temp_carry__1_n_9;
  wire subtractor_sub_temp_carry__2_n_0;
  wire subtractor_sub_temp_carry__2_n_10;
  wire subtractor_sub_temp_carry__2_n_11;
  wire subtractor_sub_temp_carry__2_n_12;
  wire subtractor_sub_temp_carry__2_n_13;
  wire subtractor_sub_temp_carry__2_n_14;
  wire subtractor_sub_temp_carry__2_n_15;
  wire subtractor_sub_temp_carry__2_n_2;
  wire subtractor_sub_temp_carry__2_n_3;
  wire subtractor_sub_temp_carry__2_n_4;
  wire subtractor_sub_temp_carry__2_n_5;
  wire subtractor_sub_temp_carry__2_n_6;
  wire subtractor_sub_temp_carry__2_n_7;
  wire subtractor_sub_temp_carry__2_n_9;
  wire subtractor_sub_temp_carry_n_0;
  wire subtractor_sub_temp_carry_n_1;
  wire subtractor_sub_temp_carry_n_10;
  wire subtractor_sub_temp_carry_n_11;
  wire subtractor_sub_temp_carry_n_12;
  wire subtractor_sub_temp_carry_n_13;
  wire subtractor_sub_temp_carry_n_14;
  wire subtractor_sub_temp_carry_n_15;
  wire subtractor_sub_temp_carry_n_2;
  wire subtractor_sub_temp_carry_n_3;
  wire subtractor_sub_temp_carry_n_4;
  wire subtractor_sub_temp_carry_n_5;
  wire subtractor_sub_temp_carry_n_6;
  wire subtractor_sub_temp_carry_n_7;
  wire subtractor_sub_temp_carry_n_8;
  wire subtractor_sub_temp_carry_n_9;
  wire [23:1]uminus_cast_1;
  wire write_axi_enable;
  wire \xout_tmp_reg_n_0_[10] ;
  wire \xout_tmp_reg_n_0_[11] ;
  wire \xout_tmp_reg_n_0_[12] ;
  wire \xout_tmp_reg_n_0_[13] ;
  wire \xout_tmp_reg_n_0_[14] ;
  wire \xout_tmp_reg_n_0_[15] ;
  wire \xout_tmp_reg_n_0_[16] ;
  wire \xout_tmp_reg_n_0_[17] ;
  wire \xout_tmp_reg_n_0_[18] ;
  wire \xout_tmp_reg_n_0_[19] ;
  wire \xout_tmp_reg_n_0_[1] ;
  wire \xout_tmp_reg_n_0_[20] ;
  wire \xout_tmp_reg_n_0_[21] ;
  wire \xout_tmp_reg_n_0_[22] ;
  wire \xout_tmp_reg_n_0_[23] ;
  wire \xout_tmp_reg_n_0_[24] ;
  wire \xout_tmp_reg_n_0_[25] ;
  wire \xout_tmp_reg_n_0_[26] ;
  wire \xout_tmp_reg_n_0_[27] ;
  wire \xout_tmp_reg_n_0_[28] ;
  wire \xout_tmp_reg_n_0_[29] ;
  wire \xout_tmp_reg_n_0_[2] ;
  wire \xout_tmp_reg_n_0_[30] ;
  wire \xout_tmp_reg_n_0_[3] ;
  wire \xout_tmp_reg_n_0_[4] ;
  wire \xout_tmp_reg_n_0_[5] ;
  wire \xout_tmp_reg_n_0_[6] ;
  wire \xout_tmp_reg_n_0_[7] ;
  wire \xout_tmp_reg_n_0_[8] ;
  wire \xout_tmp_reg_n_0_[9] ;
  wire [7:6]NLW_Div_i1_mul_temp_i_41_CO_UNCONNECTED;
  wire [7:7]NLW_Div_i1_mul_temp_i_41_O_UNCONNECTED;
  wire NLW_mul1_mul_temp_CARRYCASCOUT_UNCONNECTED;
  wire NLW_mul1_mul_temp_MULTSIGNOUT_UNCONNECTED;
  wire NLW_mul1_mul_temp_OVERFLOW_UNCONNECTED;
  wire NLW_mul1_mul_temp_PATTERNBDETECT_UNCONNECTED;
  wire NLW_mul1_mul_temp_PATTERNDETECT_UNCONNECTED;
  wire NLW_mul1_mul_temp_UNDERFLOW_UNCONNECTED;
  wire [29:0]NLW_mul1_mul_temp_ACOUT_UNCONNECTED;
  wire [17:0]NLW_mul1_mul_temp_BCOUT_UNCONNECTED;
  wire [3:0]NLW_mul1_mul_temp_CARRYOUT_UNCONNECTED;
  wire [7:0]NLW_mul1_mul_temp_XOROUT_UNCONNECTED;
  wire NLW_mul1_mul_temp__0_CARRYCASCOUT_UNCONNECTED;
  wire NLW_mul1_mul_temp__0_MULTSIGNOUT_UNCONNECTED;
  wire NLW_mul1_mul_temp__0_OVERFLOW_UNCONNECTED;
  wire NLW_mul1_mul_temp__0_PATTERNBDETECT_UNCONNECTED;
  wire NLW_mul1_mul_temp__0_PATTERNDETECT_UNCONNECTED;
  wire NLW_mul1_mul_temp__0_UNDERFLOW_UNCONNECTED;
  wire [29:0]NLW_mul1_mul_temp__0_ACOUT_UNCONNECTED;
  wire [17:0]NLW_mul1_mul_temp__0_BCOUT_UNCONNECTED;
  wire [3:0]NLW_mul1_mul_temp__0_CARRYOUT_UNCONNECTED;
  wire [47:30]NLW_mul1_mul_temp__0_P_UNCONNECTED;
  wire [47:0]NLW_mul1_mul_temp__0_PCOUT_UNCONNECTED;
  wire [7:0]NLW_mul1_mul_temp__0_XOROUT_UNCONNECTED;
  wire NLW_mul1_mul_temp__1_CARRYCASCOUT_UNCONNECTED;
  wire NLW_mul1_mul_temp__1_MULTSIGNOUT_UNCONNECTED;
  wire NLW_mul1_mul_temp__1_OVERFLOW_UNCONNECTED;
  wire NLW_mul1_mul_temp__1_PATTERNBDETECT_UNCONNECTED;
  wire NLW_mul1_mul_temp__1_PATTERNDETECT_UNCONNECTED;
  wire NLW_mul1_mul_temp__1_UNDERFLOW_UNCONNECTED;
  wire [29:0]NLW_mul1_mul_temp__1_ACOUT_UNCONNECTED;
  wire [17:0]NLW_mul1_mul_temp__1_BCOUT_UNCONNECTED;
  wire [3:0]NLW_mul1_mul_temp__1_CARRYOUT_UNCONNECTED;
  wire [7:0]NLW_mul1_mul_temp__1_XOROUT_UNCONNECTED;
  wire NLW_mul1_mul_temp__2_CARRYCASCOUT_UNCONNECTED;
  wire NLW_mul1_mul_temp__2_MULTSIGNOUT_UNCONNECTED;
  wire NLW_mul1_mul_temp__2_OVERFLOW_UNCONNECTED;
  wire NLW_mul1_mul_temp__2_PATTERNBDETECT_UNCONNECTED;
  wire NLW_mul1_mul_temp__2_PATTERNDETECT_UNCONNECTED;
  wire NLW_mul1_mul_temp__2_UNDERFLOW_UNCONNECTED;
  wire [29:0]NLW_mul1_mul_temp__2_ACOUT_UNCONNECTED;
  wire [17:0]NLW_mul1_mul_temp__2_BCOUT_UNCONNECTED;
  wire [3:0]NLW_mul1_mul_temp__2_CARRYOUT_UNCONNECTED;
  wire [47:47]NLW_mul1_mul_temp__2_P_UNCONNECTED;
  wire [47:0]NLW_mul1_mul_temp__2_PCOUT_UNCONNECTED;
  wire [7:0]NLW_mul1_mul_temp__2_XOROUT_UNCONNECTED;
  wire [7:0]NLW_mul1_mul_temp_carry_O_UNCONNECTED;
  wire [5:0]NLW_mul1_mul_temp_carry__0_O_UNCONNECTED;
  wire [7:7]NLW_mul1_mul_temp_carry__4_CO_UNCONNECTED;
  wire [6:6]NLW_subtractor_sub_temp_carry__2_CO_UNCONNECTED;
  wire [7:7]NLW_subtractor_sub_temp_carry__2_O_UNCONNECTED;

  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    Div_i1_mul_temp_i_100
       (.I0(\xout_tmp_reg_n_0_[13] ),
        .I1(\xout_tmp_reg_n_0_[15] ),
        .I2(\ds_reg_reg_reg[3]_0 [1]),
        .I3(\xout_tmp_reg_n_0_[17] ),
        .I4(\ds_reg_reg_reg[3]_0 [0]),
        .I5(\xout_tmp_reg_n_0_[19] ),
        .O(Div_i1_mul_temp_i_100_n_0));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    Div_i1_mul_temp_i_101
       (.I0(\xout_tmp_reg_n_0_[21] ),
        .I1(\xout_tmp_reg_n_0_[23] ),
        .I2(\ds_reg_reg_reg[3]_0 [1]),
        .I3(\xout_tmp_reg_n_0_[25] ),
        .I4(\ds_reg_reg_reg[3]_0 [0]),
        .I5(\xout_tmp_reg_n_0_[27] ),
        .O(Div_i1_mul_temp_i_101_n_0));
  (* SOFT_HLUTNM = "soft_lutpair52" *) 
  LUT4 #(
    .INIT(16'hE200)) 
    Div_i1_mul_temp_i_102
       (.I0(\shiftarr[0]0 ),
        .I1(\ds_reg_reg_reg[3]_0 [0]),
        .I2(\xout_tmp_reg_n_0_[29] ),
        .I3(\ds_reg_reg_reg[3]_0 [1]),
        .O(Div_i1_mul_temp_i_102_n_0));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    Div_i1_mul_temp_i_103
       (.I0(\xout_tmp_reg_n_0_[12] ),
        .I1(\xout_tmp_reg_n_0_[14] ),
        .I2(\ds_reg_reg_reg[3]_0 [1]),
        .I3(\xout_tmp_reg_n_0_[16] ),
        .I4(\ds_reg_reg_reg[3]_0 [0]),
        .I5(\xout_tmp_reg_n_0_[18] ),
        .O(Div_i1_mul_temp_i_103_n_0));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    Div_i1_mul_temp_i_104
       (.I0(\xout_tmp_reg_n_0_[20] ),
        .I1(\xout_tmp_reg_n_0_[22] ),
        .I2(\ds_reg_reg_reg[3]_0 [1]),
        .I3(\xout_tmp_reg_n_0_[24] ),
        .I4(\ds_reg_reg_reg[3]_0 [0]),
        .I5(\xout_tmp_reg_n_0_[26] ),
        .O(Div_i1_mul_temp_i_104_n_0));
  (* SOFT_HLUTNM = "soft_lutpair51" *) 
  LUT4 #(
    .INIT(16'hE200)) 
    Div_i1_mul_temp_i_105
       (.I0(\xout_tmp_reg_n_0_[30] ),
        .I1(\ds_reg_reg_reg[3]_0 [0]),
        .I2(\xout_tmp_reg_n_0_[28] ),
        .I3(\ds_reg_reg_reg[3]_0 [1]),
        .O(Div_i1_mul_temp_i_105_n_0));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    Div_i1_mul_temp_i_106
       (.I0(\xout_tmp_reg_n_0_[11] ),
        .I1(\xout_tmp_reg_n_0_[13] ),
        .I2(\ds_reg_reg_reg[3]_0 [1]),
        .I3(\xout_tmp_reg_n_0_[15] ),
        .I4(\ds_reg_reg_reg[3]_0 [0]),
        .I5(\xout_tmp_reg_n_0_[17] ),
        .O(Div_i1_mul_temp_i_106_n_0));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    Div_i1_mul_temp_i_107
       (.I0(\xout_tmp_reg_n_0_[10] ),
        .I1(\xout_tmp_reg_n_0_[12] ),
        .I2(\ds_reg_reg_reg[3]_0 [1]),
        .I3(\xout_tmp_reg_n_0_[14] ),
        .I4(\ds_reg_reg_reg[3]_0 [0]),
        .I5(\xout_tmp_reg_n_0_[16] ),
        .O(Div_i1_mul_temp_i_107_n_0));
  LUT3 #(
    .INIT(8'hB8)) 
    Div_i1_mul_temp_i_108
       (.I0(Div_i1_mul_temp_i_145_n_0),
        .I1(Div_i1_mul_temp_i_50_0),
        .I2(Div_i1_mul_temp_i_146_n_0),
        .O(Div_i1_mul_temp_i_108_n_0));
  LUT3 #(
    .INIT(8'hB8)) 
    Div_i1_mul_temp_i_109
       (.I0(Div_i1_mul_temp_i_147_n_0),
        .I1(Div_i1_mul_temp_i_50_0),
        .I2(Div_i1_mul_temp_i_144_n_0),
        .O(Div_i1_mul_temp_i_109_n_0));
  LUT3 #(
    .INIT(8'hB8)) 
    Div_i1_mul_temp_i_110
       (.I0(Div_i1_mul_temp_i_148_n_0),
        .I1(Div_i1_mul_temp_i_50_0),
        .I2(Div_i1_mul_temp_i_147_n_0),
        .O(Div_i1_mul_temp_i_110_n_0));
  LUT3 #(
    .INIT(8'hB8)) 
    Div_i1_mul_temp_i_111
       (.I0(Div_i1_mul_temp_i_149_n_0),
        .I1(Div_i1_mul_temp_i_50_0),
        .I2(Div_i1_mul_temp_i_148_n_0),
        .O(Div_i1_mul_temp_i_111_n_0));
  LUT3 #(
    .INIT(8'hB8)) 
    Div_i1_mul_temp_i_112
       (.I0(Div_i1_mul_temp_i_150_n_0),
        .I1(Div_i1_mul_temp_i_50_0),
        .I2(Div_i1_mul_temp_i_149_n_0),
        .O(Div_i1_mul_temp_i_112_n_0));
  LUT3 #(
    .INIT(8'hB8)) 
    Div_i1_mul_temp_i_113
       (.I0(Div_i1_mul_temp_i_151_n_0),
        .I1(Div_i1_mul_temp_i_50_0),
        .I2(Div_i1_mul_temp_i_150_n_0),
        .O(Div_i1_mul_temp_i_113_n_0));
  LUT3 #(
    .INIT(8'hB8)) 
    Div_i1_mul_temp_i_114
       (.I0(Div_i1_mul_temp_i_152_n_0),
        .I1(Div_i1_mul_temp_i_50_0),
        .I2(Div_i1_mul_temp_i_151_n_0),
        .O(Div_i1_mul_temp_i_114_n_0));
  LUT3 #(
    .INIT(8'hB8)) 
    Div_i1_mul_temp_i_115
       (.I0(Div_i1_mul_temp_i_153_n_0),
        .I1(Div_i1_mul_temp_i_50_0),
        .I2(Div_i1_mul_temp_i_152_n_0),
        .O(Div_i1_mul_temp_i_115_n_0));
  LUT3 #(
    .INIT(8'hB8)) 
    Div_i1_mul_temp_i_116
       (.I0(Div_i1_mul_temp_i_146_n_0),
        .I1(Div_i1_mul_temp_i_50_0),
        .I2(Div_i1_mul_temp_i_153_n_0),
        .O(Div_i1_mul_temp_i_116_n_0));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    Div_i1_mul_temp_i_117
       (.I0(\xout_tmp_reg_n_0_[9] ),
        .I1(\xout_tmp_reg_n_0_[11] ),
        .I2(\ds_reg_reg_reg[3]_0 [1]),
        .I3(\xout_tmp_reg_n_0_[13] ),
        .I4(\ds_reg_reg_reg[3]_0 [0]),
        .I5(\xout_tmp_reg_n_0_[15] ),
        .O(Div_i1_mul_temp_i_117_n_0));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    Div_i1_mul_temp_i_118
       (.I0(\xout_tmp_reg_n_0_[8] ),
        .I1(\xout_tmp_reg_n_0_[10] ),
        .I2(\ds_reg_reg_reg[3]_0 [1]),
        .I3(\xout_tmp_reg_n_0_[12] ),
        .I4(\ds_reg_reg_reg[3]_0 [0]),
        .I5(\xout_tmp_reg_n_0_[14] ),
        .O(Div_i1_mul_temp_i_118_n_0));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    Div_i1_mul_temp_i_119
       (.I0(\xout_tmp_reg_n_0_[7] ),
        .I1(\xout_tmp_reg_n_0_[9] ),
        .I2(\ds_reg_reg_reg[3]_0 [1]),
        .I3(\xout_tmp_reg_n_0_[11] ),
        .I4(\ds_reg_reg_reg[3]_0 [0]),
        .I5(\xout_tmp_reg_n_0_[13] ),
        .O(Div_i1_mul_temp_i_119_n_0));
  LUT5 #(
    .INIT(32'hB8888888)) 
    Div_i1_mul_temp_i_120
       (.I0(Div_i1_mul_temp_i_78_n_0),
        .I1(\ds_reg_reg_reg[3]_0 [2]),
        .I2(\ds_reg_reg_reg[3]_0 [0]),
        .I3(\shiftarr[0]0 ),
        .I4(\ds_reg_reg_reg[3]_0 [1]),
        .O(Div_i1_mul_temp_i_120_n_0));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    Div_i1_mul_temp_i_121
       (.I0(\xout_tmp_reg_n_0_[6] ),
        .I1(\xout_tmp_reg_n_0_[8] ),
        .I2(\ds_reg_reg_reg[3]_0 [1]),
        .I3(\xout_tmp_reg_n_0_[10] ),
        .I4(\ds_reg_reg_reg[3]_0 [0]),
        .I5(\xout_tmp_reg_n_0_[12] ),
        .O(Div_i1_mul_temp_i_121_n_0));
  LUT5 #(
    .INIT(32'hB8888888)) 
    Div_i1_mul_temp_i_122
       (.I0(Div_i1_mul_temp_i_79_n_0),
        .I1(\ds_reg_reg_reg[3]_0 [2]),
        .I2(\ds_reg_reg_reg[3]_0 [0]),
        .I3(\xout_tmp_reg_n_0_[30] ),
        .I4(\ds_reg_reg_reg[3]_0 [1]),
        .O(Div_i1_mul_temp_i_122_n_0));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    Div_i1_mul_temp_i_123
       (.I0(\xout_tmp_reg_n_0_[5] ),
        .I1(\xout_tmp_reg_n_0_[7] ),
        .I2(\ds_reg_reg_reg[3]_0 [1]),
        .I3(\xout_tmp_reg_n_0_[9] ),
        .I4(\ds_reg_reg_reg[3]_0 [0]),
        .I5(\xout_tmp_reg_n_0_[11] ),
        .O(Div_i1_mul_temp_i_123_n_0));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    Div_i1_mul_temp_i_124
       (.I0(\xout_tmp_reg_n_0_[4] ),
        .I1(\xout_tmp_reg_n_0_[6] ),
        .I2(\ds_reg_reg_reg[3]_0 [1]),
        .I3(\xout_tmp_reg_n_0_[8] ),
        .I4(\ds_reg_reg_reg[3]_0 [0]),
        .I5(\xout_tmp_reg_n_0_[10] ),
        .O(Div_i1_mul_temp_i_124_n_0));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    Div_i1_mul_temp_i_125
       (.I0(\xout_tmp_reg_n_0_[3] ),
        .I1(\xout_tmp_reg_n_0_[5] ),
        .I2(\ds_reg_reg_reg[3]_0 [1]),
        .I3(\xout_tmp_reg_n_0_[7] ),
        .I4(\ds_reg_reg_reg[3]_0 [0]),
        .I5(\xout_tmp_reg_n_0_[9] ),
        .O(Div_i1_mul_temp_i_125_n_0));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    Div_i1_mul_temp_i_126
       (.I0(\xout_tmp_reg_n_0_[2] ),
        .I1(\xout_tmp_reg_n_0_[4] ),
        .I2(\ds_reg_reg_reg[3]_0 [1]),
        .I3(\xout_tmp_reg_n_0_[6] ),
        .I4(\ds_reg_reg_reg[3]_0 [0]),
        .I5(\xout_tmp_reg_n_0_[8] ),
        .O(Div_i1_mul_temp_i_126_n_0));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    Div_i1_mul_temp_i_127
       (.I0(\xout_tmp_reg_n_0_[1] ),
        .I1(\xout_tmp_reg_n_0_[3] ),
        .I2(\ds_reg_reg_reg[3]_0 [1]),
        .I3(\xout_tmp_reg_n_0_[5] ),
        .I4(\ds_reg_reg_reg[3]_0 [0]),
        .I5(\xout_tmp_reg_n_0_[7] ),
        .O(Div_i1_mul_temp_i_127_n_0));
  LUT6 #(
    .INIT(64'h505F3030505F3F3F)) 
    Div_i1_mul_temp_i_128
       (.I0(\xout_tmp_reg_n_0_[24] ),
        .I1(\xout_tmp_reg_n_0_[26] ),
        .I2(\ds_reg_reg_reg[3]_0 [1]),
        .I3(\xout_tmp_reg_n_0_[28] ),
        .I4(\ds_reg_reg_reg[3]_0 [0]),
        .I5(\xout_tmp_reg_n_0_[30] ),
        .O(Div_i1_mul_temp_i_128_n_0));
  LUT6 #(
    .INIT(64'h505F3030505F3F3F)) 
    Div_i1_mul_temp_i_129
       (.I0(\xout_tmp_reg_n_0_[25] ),
        .I1(\xout_tmp_reg_n_0_[27] ),
        .I2(\ds_reg_reg_reg[3]_0 [1]),
        .I3(\xout_tmp_reg_n_0_[29] ),
        .I4(\ds_reg_reg_reg[3]_0 [0]),
        .I5(\shiftarr[0]0 ),
        .O(Div_i1_mul_temp_i_129_n_0));
  LUT6 #(
    .INIT(64'hFF7F007FFFFFFFFF)) 
    Div_i1_mul_temp_i_130
       (.I0(\ds_reg_reg_reg[3]_0 [1]),
        .I1(\ds_reg_reg_reg[3]_0 [0]),
        .I2(\shiftarr[0]0 ),
        .I3(\ds_reg_reg_reg[3]_0 [2]),
        .I4(Div_i1_mul_temp_i_154_n_0),
        .I5(\ds_reg_reg_reg[3]_0 [3]),
        .O(Div_i1_mul_temp_i_130_n_0));
  LUT6 #(
    .INIT(64'hFF7F007FFFFFFFFF)) 
    Div_i1_mul_temp_i_131
       (.I0(\ds_reg_reg_reg[3]_0 [1]),
        .I1(\ds_reg_reg_reg[3]_0 [0]),
        .I2(\xout_tmp_reg_n_0_[30] ),
        .I3(\ds_reg_reg_reg[3]_0 [2]),
        .I4(Div_i1_mul_temp_i_155_n_0),
        .I5(\ds_reg_reg_reg[3]_0 [3]),
        .O(Div_i1_mul_temp_i_131_n_0));
  LUT6 #(
    .INIT(64'h888BBB8BBBBBBBBB)) 
    Div_i1_mul_temp_i_132
       (.I0(Div_i1_mul_temp_i_156_n_0),
        .I1(\ds_reg_reg_reg[3]_0 [2]),
        .I2(\shiftarr[0]0 ),
        .I3(\ds_reg_reg_reg[3]_0 [0]),
        .I4(\xout_tmp_reg_n_0_[29] ),
        .I5(\ds_reg_reg_reg[3]_0 [1]),
        .O(Div_i1_mul_temp_i_132_n_0));
  LUT6 #(
    .INIT(64'h888BBB8BBBBBBBBB)) 
    Div_i1_mul_temp_i_133
       (.I0(Div_i1_mul_temp_i_157_n_0),
        .I1(\ds_reg_reg_reg[3]_0 [2]),
        .I2(\xout_tmp_reg_n_0_[30] ),
        .I3(\ds_reg_reg_reg[3]_0 [0]),
        .I4(\xout_tmp_reg_n_0_[28] ),
        .I5(\ds_reg_reg_reg[3]_0 [1]),
        .O(Div_i1_mul_temp_i_133_n_0));
  (* SOFT_HLUTNM = "soft_lutpair39" *) 
  LUT4 #(
    .INIT(16'hE2FF)) 
    Div_i1_mul_temp_i_134
       (.I0(Div_i1_mul_temp_i_158_n_0),
        .I1(\ds_reg_reg_reg[3]_0 [2]),
        .I2(Div_i1_mul_temp_i_159_n_0),
        .I3(\ds_reg_reg_reg[3]_0 [3]),
        .O(Div_i1_mul_temp_i_134_n_0));
  (* SOFT_HLUTNM = "soft_lutpair38" *) 
  LUT5 #(
    .INIT(32'h503F5F3F)) 
    Div_i1_mul_temp_i_135
       (.I0(\xout_tmp_reg_n_0_[26] ),
        .I1(\xout_tmp_reg_n_0_[28] ),
        .I2(\ds_reg_reg_reg[3]_0 [1]),
        .I3(\ds_reg_reg_reg[3]_0 [0]),
        .I4(\xout_tmp_reg_n_0_[30] ),
        .O(Div_i1_mul_temp_i_135_n_0));
  LUT6 #(
    .INIT(64'h505F3030505F3F3F)) 
    Div_i1_mul_temp_i_136
       (.I0(\xout_tmp_reg_n_0_[18] ),
        .I1(\xout_tmp_reg_n_0_[20] ),
        .I2(\ds_reg_reg_reg[3]_0 [1]),
        .I3(\xout_tmp_reg_n_0_[22] ),
        .I4(\ds_reg_reg_reg[3]_0 [0]),
        .I5(\xout_tmp_reg_n_0_[24] ),
        .O(Div_i1_mul_temp_i_136_n_0));
  (* SOFT_HLUTNM = "soft_lutpair41" *) 
  LUT4 #(
    .INIT(16'hE2FF)) 
    Div_i1_mul_temp_i_137
       (.I0(Div_i1_mul_temp_i_129_n_0),
        .I1(\ds_reg_reg_reg[3]_0 [2]),
        .I2(Div_i1_mul_temp_i_160_n_0),
        .I3(\ds_reg_reg_reg[3]_0 [3]),
        .O(Div_i1_mul_temp_i_137_n_0));
  LUT6 #(
    .INIT(64'h505F3030505F3F3F)) 
    Div_i1_mul_temp_i_138
       (.I0(\xout_tmp_reg_n_0_[16] ),
        .I1(\xout_tmp_reg_n_0_[18] ),
        .I2(\ds_reg_reg_reg[3]_0 [1]),
        .I3(\xout_tmp_reg_n_0_[20] ),
        .I4(\ds_reg_reg_reg[3]_0 [0]),
        .I5(\xout_tmp_reg_n_0_[22] ),
        .O(Div_i1_mul_temp_i_138_n_0));
  LUT6 #(
    .INIT(64'hA0AFAFAFCFCFCFCF)) 
    Div_i1_mul_temp_i_139
       (.I0(Div_i1_mul_temp_i_161_n_0),
        .I1(Div_i1_mul_temp_i_154_n_0),
        .I2(\ds_reg_reg_reg[3]_0 [3]),
        .I3(\ds_reg_reg_reg[3]_0 [1]),
        .I4(Div_i1_mul_temp_i_97_n_0),
        .I5(\ds_reg_reg_reg[3]_0 [2]),
        .O(Div_i1_mul_temp_i_139_n_0));
  LUT6 #(
    .INIT(64'hA0AFAFAFCFCFCFCF)) 
    Div_i1_mul_temp_i_140
       (.I0(Div_i1_mul_temp_i_162_n_0),
        .I1(Div_i1_mul_temp_i_155_n_0),
        .I2(\ds_reg_reg_reg[3]_0 [3]),
        .I3(\ds_reg_reg_reg[3]_0 [1]),
        .I4(Div_i1_mul_temp_i_99_n_0),
        .I5(\ds_reg_reg_reg[3]_0 [2]),
        .O(Div_i1_mul_temp_i_140_n_0));
  LUT5 #(
    .INIT(32'hAFA0CFCF)) 
    Div_i1_mul_temp_i_141
       (.I0(Div_i1_mul_temp_i_163_n_0),
        .I1(Div_i1_mul_temp_i_156_n_0),
        .I2(\ds_reg_reg_reg[3]_0 [3]),
        .I3(Div_i1_mul_temp_i_164_n_0),
        .I4(\ds_reg_reg_reg[3]_0 [2]),
        .O(Div_i1_mul_temp_i_141_n_0));
  LUT5 #(
    .INIT(32'hAFA0CFCF)) 
    Div_i1_mul_temp_i_142
       (.I0(Div_i1_mul_temp_i_165_n_0),
        .I1(Div_i1_mul_temp_i_157_n_0),
        .I2(\ds_reg_reg_reg[3]_0 [3]),
        .I3(Div_i1_mul_temp_i_166_n_0),
        .I4(\ds_reg_reg_reg[3]_0 [2]),
        .O(Div_i1_mul_temp_i_142_n_0));
  (* SOFT_HLUTNM = "soft_lutpair39" *) 
  LUT5 #(
    .INIT(32'hAFA0CFCF)) 
    Div_i1_mul_temp_i_143
       (.I0(Div_i1_mul_temp_i_167_n_0),
        .I1(Div_i1_mul_temp_i_159_n_0),
        .I2(\ds_reg_reg_reg[3]_0 [3]),
        .I3(Div_i1_mul_temp_i_158_n_0),
        .I4(\ds_reg_reg_reg[3]_0 [2]),
        .O(Div_i1_mul_temp_i_143_n_0));
  LUT5 #(
    .INIT(32'hAFA0CFCF)) 
    Div_i1_mul_temp_i_144
       (.I0(Div_i1_mul_temp_i_168_n_0),
        .I1(Div_i1_mul_temp_i_136_n_0),
        .I2(\ds_reg_reg_reg[3]_0 [3]),
        .I3(Div_i1_mul_temp_i_135_n_0),
        .I4(\ds_reg_reg_reg[3]_0 [2]),
        .O(Div_i1_mul_temp_i_144_n_0));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    Div_i1_mul_temp_i_145
       (.I0(Div_i1_mul_temp_i_169_n_0),
        .I1(Div_i1_mul_temp_i_170_n_0),
        .I2(\ds_reg_reg_reg[3]_0 [3]),
        .I3(Div_i1_mul_temp_i_160_n_0),
        .I4(\ds_reg_reg_reg[3]_0 [2]),
        .I5(Div_i1_mul_temp_i_129_n_0),
        .O(Div_i1_mul_temp_i_145_n_0));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    Div_i1_mul_temp_i_146
       (.I0(Div_i1_mul_temp_i_171_n_0),
        .I1(Div_i1_mul_temp_i_168_n_0),
        .I2(\ds_reg_reg_reg[3]_0 [3]),
        .I3(Div_i1_mul_temp_i_136_n_0),
        .I4(\ds_reg_reg_reg[3]_0 [2]),
        .I5(Div_i1_mul_temp_i_135_n_0),
        .O(Div_i1_mul_temp_i_146_n_0));
  (* SOFT_HLUTNM = "soft_lutpair41" *) 
  LUT5 #(
    .INIT(32'hAFA0CFCF)) 
    Div_i1_mul_temp_i_147
       (.I0(Div_i1_mul_temp_i_170_n_0),
        .I1(Div_i1_mul_temp_i_160_n_0),
        .I2(\ds_reg_reg_reg[3]_0 [3]),
        .I3(Div_i1_mul_temp_i_129_n_0),
        .I4(\ds_reg_reg_reg[3]_0 [2]),
        .O(Div_i1_mul_temp_i_147_n_0));
  LUT5 #(
    .INIT(32'hAFA0CFCF)) 
    Div_i1_mul_temp_i_148
       (.I0(Div_i1_mul_temp_i_172_n_0),
        .I1(Div_i1_mul_temp_i_138_n_0),
        .I2(\ds_reg_reg_reg[3]_0 [3]),
        .I3(Div_i1_mul_temp_i_128_n_0),
        .I4(\ds_reg_reg_reg[3]_0 [2]),
        .O(Div_i1_mul_temp_i_148_n_0));
  LUT5 #(
    .INIT(32'hB8FFB800)) 
    Div_i1_mul_temp_i_149
       (.I0(Div_i1_mul_temp_i_173_n_0),
        .I1(\ds_reg_reg_reg[3]_0 [2]),
        .I2(Div_i1_mul_temp_i_161_n_0),
        .I3(\ds_reg_reg_reg[3]_0 [3]),
        .I4(Div_i1_mul_temp_i_174_n_0),
        .O(Div_i1_mul_temp_i_149_n_0));
  LUT5 #(
    .INIT(32'hB8FFB800)) 
    Div_i1_mul_temp_i_150
       (.I0(Div_i1_mul_temp_i_175_n_0),
        .I1(\ds_reg_reg_reg[3]_0 [2]),
        .I2(Div_i1_mul_temp_i_162_n_0),
        .I3(\ds_reg_reg_reg[3]_0 [3]),
        .I4(Div_i1_mul_temp_i_176_n_0),
        .O(Div_i1_mul_temp_i_150_n_0));
  LUT5 #(
    .INIT(32'hB8FFB800)) 
    Div_i1_mul_temp_i_151
       (.I0(Div_i1_mul_temp_i_177_n_0),
        .I1(\ds_reg_reg_reg[3]_0 [2]),
        .I2(Div_i1_mul_temp_i_163_n_0),
        .I3(\ds_reg_reg_reg[3]_0 [3]),
        .I4(Div_i1_mul_temp_i_132_n_0),
        .O(Div_i1_mul_temp_i_151_n_0));
  LUT5 #(
    .INIT(32'hB8FFB800)) 
    Div_i1_mul_temp_i_152
       (.I0(Div_i1_mul_temp_i_178_n_0),
        .I1(\ds_reg_reg_reg[3]_0 [2]),
        .I2(Div_i1_mul_temp_i_165_n_0),
        .I3(\ds_reg_reg_reg[3]_0 [3]),
        .I4(Div_i1_mul_temp_i_133_n_0),
        .O(Div_i1_mul_temp_i_152_n_0));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    Div_i1_mul_temp_i_153
       (.I0(Div_i1_mul_temp_i_179_n_0),
        .I1(Div_i1_mul_temp_i_167_n_0),
        .I2(\ds_reg_reg_reg[3]_0 [3]),
        .I3(Div_i1_mul_temp_i_159_n_0),
        .I4(\ds_reg_reg_reg[3]_0 [2]),
        .I5(Div_i1_mul_temp_i_158_n_0),
        .O(Div_i1_mul_temp_i_153_n_0));
  LUT6 #(
    .INIT(64'h505F3030505F3F3F)) 
    Div_i1_mul_temp_i_154
       (.I0(\xout_tmp_reg_n_0_[23] ),
        .I1(\xout_tmp_reg_n_0_[25] ),
        .I2(\ds_reg_reg_reg[3]_0 [1]),
        .I3(\xout_tmp_reg_n_0_[27] ),
        .I4(\ds_reg_reg_reg[3]_0 [0]),
        .I5(\xout_tmp_reg_n_0_[29] ),
        .O(Div_i1_mul_temp_i_154_n_0));
  LUT6 #(
    .INIT(64'h505F3030505F3F3F)) 
    Div_i1_mul_temp_i_155
       (.I0(\xout_tmp_reg_n_0_[22] ),
        .I1(\xout_tmp_reg_n_0_[24] ),
        .I2(\ds_reg_reg_reg[3]_0 [1]),
        .I3(\xout_tmp_reg_n_0_[26] ),
        .I4(\ds_reg_reg_reg[3]_0 [0]),
        .I5(\xout_tmp_reg_n_0_[28] ),
        .O(Div_i1_mul_temp_i_155_n_0));
  LUT6 #(
    .INIT(64'h505F3030505F3F3F)) 
    Div_i1_mul_temp_i_156
       (.I0(\xout_tmp_reg_n_0_[21] ),
        .I1(\xout_tmp_reg_n_0_[23] ),
        .I2(\ds_reg_reg_reg[3]_0 [1]),
        .I3(\xout_tmp_reg_n_0_[25] ),
        .I4(\ds_reg_reg_reg[3]_0 [0]),
        .I5(\xout_tmp_reg_n_0_[27] ),
        .O(Div_i1_mul_temp_i_156_n_0));
  LUT6 #(
    .INIT(64'h505F3030505F3F3F)) 
    Div_i1_mul_temp_i_157
       (.I0(\xout_tmp_reg_n_0_[20] ),
        .I1(\xout_tmp_reg_n_0_[22] ),
        .I2(\ds_reg_reg_reg[3]_0 [1]),
        .I3(\xout_tmp_reg_n_0_[24] ),
        .I4(\ds_reg_reg_reg[3]_0 [0]),
        .I5(\xout_tmp_reg_n_0_[26] ),
        .O(Div_i1_mul_temp_i_157_n_0));
  (* SOFT_HLUTNM = "soft_lutpair42" *) 
  LUT5 #(
    .INIT(32'h503F5F3F)) 
    Div_i1_mul_temp_i_158
       (.I0(\xout_tmp_reg_n_0_[27] ),
        .I1(\xout_tmp_reg_n_0_[29] ),
        .I2(\ds_reg_reg_reg[3]_0 [1]),
        .I3(\ds_reg_reg_reg[3]_0 [0]),
        .I4(\shiftarr[0]0 ),
        .O(Div_i1_mul_temp_i_158_n_0));
  LUT6 #(
    .INIT(64'h505F3030505F3F3F)) 
    Div_i1_mul_temp_i_159
       (.I0(\xout_tmp_reg_n_0_[19] ),
        .I1(\xout_tmp_reg_n_0_[21] ),
        .I2(\ds_reg_reg_reg[3]_0 [1]),
        .I3(\xout_tmp_reg_n_0_[23] ),
        .I4(\ds_reg_reg_reg[3]_0 [0]),
        .I5(\xout_tmp_reg_n_0_[25] ),
        .O(Div_i1_mul_temp_i_159_n_0));
  LUT6 #(
    .INIT(64'h505F3030505F3F3F)) 
    Div_i1_mul_temp_i_160
       (.I0(\xout_tmp_reg_n_0_[17] ),
        .I1(\xout_tmp_reg_n_0_[19] ),
        .I2(\ds_reg_reg_reg[3]_0 [1]),
        .I3(\xout_tmp_reg_n_0_[21] ),
        .I4(\ds_reg_reg_reg[3]_0 [0]),
        .I5(\xout_tmp_reg_n_0_[23] ),
        .O(Div_i1_mul_temp_i_160_n_0));
  LUT6 #(
    .INIT(64'h505F3030505F3F3F)) 
    Div_i1_mul_temp_i_161
       (.I0(\xout_tmp_reg_n_0_[15] ),
        .I1(\xout_tmp_reg_n_0_[17] ),
        .I2(\ds_reg_reg_reg[3]_0 [1]),
        .I3(\xout_tmp_reg_n_0_[19] ),
        .I4(\ds_reg_reg_reg[3]_0 [0]),
        .I5(\xout_tmp_reg_n_0_[21] ),
        .O(Div_i1_mul_temp_i_161_n_0));
  LUT6 #(
    .INIT(64'h505F3030505F3F3F)) 
    Div_i1_mul_temp_i_162
       (.I0(\xout_tmp_reg_n_0_[14] ),
        .I1(\xout_tmp_reg_n_0_[16] ),
        .I2(\ds_reg_reg_reg[3]_0 [1]),
        .I3(\xout_tmp_reg_n_0_[18] ),
        .I4(\ds_reg_reg_reg[3]_0 [0]),
        .I5(\xout_tmp_reg_n_0_[20] ),
        .O(Div_i1_mul_temp_i_162_n_0));
  LUT6 #(
    .INIT(64'h505F3030505F3F3F)) 
    Div_i1_mul_temp_i_163
       (.I0(\xout_tmp_reg_n_0_[13] ),
        .I1(\xout_tmp_reg_n_0_[15] ),
        .I2(\ds_reg_reg_reg[3]_0 [1]),
        .I3(\xout_tmp_reg_n_0_[17] ),
        .I4(\ds_reg_reg_reg[3]_0 [0]),
        .I5(\xout_tmp_reg_n_0_[19] ),
        .O(Div_i1_mul_temp_i_163_n_0));
  (* SOFT_HLUTNM = "soft_lutpair52" *) 
  LUT4 #(
    .INIT(16'h1DFF)) 
    Div_i1_mul_temp_i_164
       (.I0(\shiftarr[0]0 ),
        .I1(\ds_reg_reg_reg[3]_0 [0]),
        .I2(\xout_tmp_reg_n_0_[29] ),
        .I3(\ds_reg_reg_reg[3]_0 [1]),
        .O(Div_i1_mul_temp_i_164_n_0));
  LUT6 #(
    .INIT(64'h505F3030505F3F3F)) 
    Div_i1_mul_temp_i_165
       (.I0(\xout_tmp_reg_n_0_[12] ),
        .I1(\xout_tmp_reg_n_0_[14] ),
        .I2(\ds_reg_reg_reg[3]_0 [1]),
        .I3(\xout_tmp_reg_n_0_[16] ),
        .I4(\ds_reg_reg_reg[3]_0 [0]),
        .I5(\xout_tmp_reg_n_0_[18] ),
        .O(Div_i1_mul_temp_i_165_n_0));
  (* SOFT_HLUTNM = "soft_lutpair51" *) 
  LUT4 #(
    .INIT(16'h1DFF)) 
    Div_i1_mul_temp_i_166
       (.I0(\xout_tmp_reg_n_0_[30] ),
        .I1(\ds_reg_reg_reg[3]_0 [0]),
        .I2(\xout_tmp_reg_n_0_[28] ),
        .I3(\ds_reg_reg_reg[3]_0 [1]),
        .O(Div_i1_mul_temp_i_166_n_0));
  LUT6 #(
    .INIT(64'h505F3030505F3F3F)) 
    Div_i1_mul_temp_i_167
       (.I0(\xout_tmp_reg_n_0_[11] ),
        .I1(\xout_tmp_reg_n_0_[13] ),
        .I2(\ds_reg_reg_reg[3]_0 [1]),
        .I3(\xout_tmp_reg_n_0_[15] ),
        .I4(\ds_reg_reg_reg[3]_0 [0]),
        .I5(\xout_tmp_reg_n_0_[17] ),
        .O(Div_i1_mul_temp_i_167_n_0));
  LUT6 #(
    .INIT(64'h505F3030505F3F3F)) 
    Div_i1_mul_temp_i_168
       (.I0(\xout_tmp_reg_n_0_[10] ),
        .I1(\xout_tmp_reg_n_0_[12] ),
        .I2(\ds_reg_reg_reg[3]_0 [1]),
        .I3(\xout_tmp_reg_n_0_[14] ),
        .I4(\ds_reg_reg_reg[3]_0 [0]),
        .I5(\xout_tmp_reg_n_0_[16] ),
        .O(Div_i1_mul_temp_i_168_n_0));
  LUT6 #(
    .INIT(64'h505F3030505F3F3F)) 
    Div_i1_mul_temp_i_169
       (.I0(\xout_tmp_reg_n_0_[1] ),
        .I1(\xout_tmp_reg_n_0_[3] ),
        .I2(\ds_reg_reg_reg[3]_0 [1]),
        .I3(\xout_tmp_reg_n_0_[5] ),
        .I4(\ds_reg_reg_reg[3]_0 [0]),
        .I5(\xout_tmp_reg_n_0_[7] ),
        .O(Div_i1_mul_temp_i_169_n_0));
  LUT4 #(
    .INIT(16'hEFE0)) 
    Div_i1_mul_temp_i_17
       (.I0(uminus_cast_1[23]),
        .I1(DSP_A_B_DATA_INST_0),
        .I2(DSP_A_B_DATA_INST_1),
        .I3(Div_i1_mul_temp_i_42_n_0),
        .O(A[23]));
  LUT6 #(
    .INIT(64'h505F3030505F3F3F)) 
    Div_i1_mul_temp_i_170
       (.I0(\xout_tmp_reg_n_0_[9] ),
        .I1(\xout_tmp_reg_n_0_[11] ),
        .I2(\ds_reg_reg_reg[3]_0 [1]),
        .I3(\xout_tmp_reg_n_0_[13] ),
        .I4(\ds_reg_reg_reg[3]_0 [0]),
        .I5(\xout_tmp_reg_n_0_[15] ),
        .O(Div_i1_mul_temp_i_170_n_0));
  LUT6 #(
    .INIT(64'h505F3030505F3F3F)) 
    Div_i1_mul_temp_i_171
       (.I0(\xout_tmp_reg_n_0_[2] ),
        .I1(\xout_tmp_reg_n_0_[4] ),
        .I2(\ds_reg_reg_reg[3]_0 [1]),
        .I3(\xout_tmp_reg_n_0_[6] ),
        .I4(\ds_reg_reg_reg[3]_0 [0]),
        .I5(\xout_tmp_reg_n_0_[8] ),
        .O(Div_i1_mul_temp_i_171_n_0));
  LUT6 #(
    .INIT(64'h505F3030505F3F3F)) 
    Div_i1_mul_temp_i_172
       (.I0(\xout_tmp_reg_n_0_[8] ),
        .I1(\xout_tmp_reg_n_0_[10] ),
        .I2(\ds_reg_reg_reg[3]_0 [1]),
        .I3(\xout_tmp_reg_n_0_[12] ),
        .I4(\ds_reg_reg_reg[3]_0 [0]),
        .I5(\xout_tmp_reg_n_0_[14] ),
        .O(Div_i1_mul_temp_i_172_n_0));
  LUT6 #(
    .INIT(64'h505F3030505F3F3F)) 
    Div_i1_mul_temp_i_173
       (.I0(\xout_tmp_reg_n_0_[7] ),
        .I1(\xout_tmp_reg_n_0_[9] ),
        .I2(\ds_reg_reg_reg[3]_0 [1]),
        .I3(\xout_tmp_reg_n_0_[11] ),
        .I4(\ds_reg_reg_reg[3]_0 [0]),
        .I5(\xout_tmp_reg_n_0_[13] ),
        .O(Div_i1_mul_temp_i_173_n_0));
  (* SOFT_HLUTNM = "soft_lutpair40" *) 
  LUT5 #(
    .INIT(32'h8BBBBBBB)) 
    Div_i1_mul_temp_i_174
       (.I0(Div_i1_mul_temp_i_154_n_0),
        .I1(\ds_reg_reg_reg[3]_0 [2]),
        .I2(\shiftarr[0]0 ),
        .I3(\ds_reg_reg_reg[3]_0 [0]),
        .I4(\ds_reg_reg_reg[3]_0 [1]),
        .O(Div_i1_mul_temp_i_174_n_0));
  LUT6 #(
    .INIT(64'h505F3030505F3F3F)) 
    Div_i1_mul_temp_i_175
       (.I0(\xout_tmp_reg_n_0_[6] ),
        .I1(\xout_tmp_reg_n_0_[8] ),
        .I2(\ds_reg_reg_reg[3]_0 [1]),
        .I3(\xout_tmp_reg_n_0_[10] ),
        .I4(\ds_reg_reg_reg[3]_0 [0]),
        .I5(\xout_tmp_reg_n_0_[12] ),
        .O(Div_i1_mul_temp_i_175_n_0));
  (* SOFT_HLUTNM = "soft_lutpair37" *) 
  LUT5 #(
    .INIT(32'h8BBBBBBB)) 
    Div_i1_mul_temp_i_176
       (.I0(Div_i1_mul_temp_i_155_n_0),
        .I1(\ds_reg_reg_reg[3]_0 [2]),
        .I2(\xout_tmp_reg_n_0_[30] ),
        .I3(\ds_reg_reg_reg[3]_0 [0]),
        .I4(\ds_reg_reg_reg[3]_0 [1]),
        .O(Div_i1_mul_temp_i_176_n_0));
  LUT6 #(
    .INIT(64'h505F3030505F3F3F)) 
    Div_i1_mul_temp_i_177
       (.I0(\xout_tmp_reg_n_0_[5] ),
        .I1(\xout_tmp_reg_n_0_[7] ),
        .I2(\ds_reg_reg_reg[3]_0 [1]),
        .I3(\xout_tmp_reg_n_0_[9] ),
        .I4(\ds_reg_reg_reg[3]_0 [0]),
        .I5(\xout_tmp_reg_n_0_[11] ),
        .O(Div_i1_mul_temp_i_177_n_0));
  LUT6 #(
    .INIT(64'h505F3030505F3F3F)) 
    Div_i1_mul_temp_i_178
       (.I0(\xout_tmp_reg_n_0_[4] ),
        .I1(\xout_tmp_reg_n_0_[6] ),
        .I2(\ds_reg_reg_reg[3]_0 [1]),
        .I3(\xout_tmp_reg_n_0_[8] ),
        .I4(\ds_reg_reg_reg[3]_0 [0]),
        .I5(\xout_tmp_reg_n_0_[10] ),
        .O(Div_i1_mul_temp_i_178_n_0));
  LUT6 #(
    .INIT(64'h505F3030505F3F3F)) 
    Div_i1_mul_temp_i_179
       (.I0(\xout_tmp_reg_n_0_[3] ),
        .I1(\xout_tmp_reg_n_0_[5] ),
        .I2(\ds_reg_reg_reg[3]_0 [1]),
        .I3(\xout_tmp_reg_n_0_[7] ),
        .I4(\ds_reg_reg_reg[3]_0 [0]),
        .I5(\xout_tmp_reg_n_0_[9] ),
        .O(Div_i1_mul_temp_i_179_n_0));
  LUT6 #(
    .INIT(64'hFFFFFFFFBBB888B8)) 
    Div_i1_mul_temp_i_18
       (.I0(uminus_cast_1[22]),
        .I1(DSP_A_B_DATA_INST_1),
        .I2(Div_i1_mul_temp_i_43_n_0),
        .I3(Div_i1_mul_temp_i_50_0),
        .I4(Div_i1_mul_temp_i_44_n_0),
        .I5(DSP_A_B_DATA_INST_0),
        .O(A[22]));
  LUT6 #(
    .INIT(64'hFFFFFFFFBBB888B8)) 
    Div_i1_mul_temp_i_19
       (.I0(uminus_cast_1[21]),
        .I1(DSP_A_B_DATA_INST_1),
        .I2(Div_i1_mul_temp_i_44_n_0),
        .I3(Div_i1_mul_temp_i_50_0),
        .I4(Div_i1_mul_temp_i_45_n_0),
        .I5(DSP_A_B_DATA_INST_0),
        .O(A[21]));
  LUT6 #(
    .INIT(64'hFFFFFFFFBBB888B8)) 
    Div_i1_mul_temp_i_20
       (.I0(uminus_cast_1[20]),
        .I1(DSP_A_B_DATA_INST_1),
        .I2(Div_i1_mul_temp_i_45_n_0),
        .I3(Div_i1_mul_temp_i_50_0),
        .I4(Div_i1_mul_temp_i_46_n_0),
        .I5(DSP_A_B_DATA_INST_0),
        .O(A[20]));
  LUT6 #(
    .INIT(64'hFFFFFFFFBBB888B8)) 
    Div_i1_mul_temp_i_21
       (.I0(uminus_cast_1[19]),
        .I1(DSP_A_B_DATA_INST_1),
        .I2(Div_i1_mul_temp_i_46_n_0),
        .I3(Div_i1_mul_temp_i_50_0),
        .I4(Div_i1_mul_temp_i_47_n_0),
        .I5(DSP_A_B_DATA_INST_0),
        .O(A[19]));
  LUT6 #(
    .INIT(64'hFFFFFFFFBBB888B8)) 
    Div_i1_mul_temp_i_22
       (.I0(uminus_cast_1[18]),
        .I1(DSP_A_B_DATA_INST_1),
        .I2(Div_i1_mul_temp_i_47_n_0),
        .I3(Div_i1_mul_temp_i_50_0),
        .I4(Div_i1_mul_temp_i_48_n_0),
        .I5(DSP_A_B_DATA_INST_0),
        .O(A[18]));
  LUT6 #(
    .INIT(64'hFFFFFFFFBBB888B8)) 
    Div_i1_mul_temp_i_23
       (.I0(uminus_cast_1[17]),
        .I1(DSP_A_B_DATA_INST_1),
        .I2(Div_i1_mul_temp_i_48_n_0),
        .I3(Div_i1_mul_temp_i_50_0),
        .I4(Div_i1_mul_temp_i_49_n_0),
        .I5(DSP_A_B_DATA_INST_0),
        .O(A[17]));
  LUT6 #(
    .INIT(64'hFFFFFFFFBBB888B8)) 
    Div_i1_mul_temp_i_24
       (.I0(uminus_cast_1[16]),
        .I1(DSP_A_B_DATA_INST_1),
        .I2(Div_i1_mul_temp_i_49_n_0),
        .I3(Div_i1_mul_temp_i_50_0),
        .I4(Div_i1_mul_temp_i_51_n_0),
        .I5(DSP_A_B_DATA_INST_0),
        .O(A[16]));
  LUT6 #(
    .INIT(64'hFFFFFFFFBBB888B8)) 
    Div_i1_mul_temp_i_25
       (.I0(uminus_cast_1[15]),
        .I1(DSP_A_B_DATA_INST_1),
        .I2(Div_i1_mul_temp_i_51_n_0),
        .I3(Div_i1_mul_temp_i_50_0),
        .I4(Div_i1_mul_temp_i_52_n_0),
        .I5(DSP_A_B_DATA_INST_0),
        .O(A[15]));
  LUT6 #(
    .INIT(64'hFFFFFFFFBBB888B8)) 
    Div_i1_mul_temp_i_26
       (.I0(uminus_cast_1[14]),
        .I1(DSP_A_B_DATA_INST_1),
        .I2(Div_i1_mul_temp_i_52_n_0),
        .I3(Div_i1_mul_temp_i_50_0),
        .I4(Div_i1_mul_temp_i_53_n_0),
        .I5(DSP_A_B_DATA_INST_0),
        .O(A[14]));
  LUT6 #(
    .INIT(64'hFFFFFFFFBBB888B8)) 
    Div_i1_mul_temp_i_27
       (.I0(uminus_cast_1[13]),
        .I1(DSP_A_B_DATA_INST_1),
        .I2(Div_i1_mul_temp_i_53_n_0),
        .I3(Div_i1_mul_temp_i_50_0),
        .I4(Div_i1_mul_temp_i_54_n_0),
        .I5(DSP_A_B_DATA_INST_0),
        .O(A[13]));
  LUT6 #(
    .INIT(64'hFFFFFFFFBBB888B8)) 
    Div_i1_mul_temp_i_28
       (.I0(uminus_cast_1[12]),
        .I1(DSP_A_B_DATA_INST_1),
        .I2(Div_i1_mul_temp_i_54_n_0),
        .I3(Div_i1_mul_temp_i_50_0),
        .I4(Div_i1_mul_temp_i_55_n_0),
        .I5(DSP_A_B_DATA_INST_0),
        .O(A[12]));
  LUT6 #(
    .INIT(64'hFFFFFFFFBBB888B8)) 
    Div_i1_mul_temp_i_29
       (.I0(uminus_cast_1[11]),
        .I1(DSP_A_B_DATA_INST_1),
        .I2(Div_i1_mul_temp_i_55_n_0),
        .I3(Div_i1_mul_temp_i_50_0),
        .I4(Div_i1_mul_temp_i_56_n_0),
        .I5(DSP_A_B_DATA_INST_0),
        .O(A[11]));
  LUT6 #(
    .INIT(64'hFFFFFFFFBBB888B8)) 
    Div_i1_mul_temp_i_30
       (.I0(uminus_cast_1[10]),
        .I1(DSP_A_B_DATA_INST_1),
        .I2(Div_i1_mul_temp_i_56_n_0),
        .I3(Div_i1_mul_temp_i_50_0),
        .I4(Div_i1_mul_temp_i_57_n_0),
        .I5(DSP_A_B_DATA_INST_0),
        .O(A[10]));
  LUT6 #(
    .INIT(64'hFFFFFFFFBBB888B8)) 
    Div_i1_mul_temp_i_31
       (.I0(uminus_cast_1[9]),
        .I1(DSP_A_B_DATA_INST_1),
        .I2(Div_i1_mul_temp_i_57_n_0),
        .I3(Div_i1_mul_temp_i_50_0),
        .I4(Div_i1_mul_temp_i_58_n_0),
        .I5(DSP_A_B_DATA_INST_0),
        .O(A[9]));
  LUT6 #(
    .INIT(64'hFFFFFFFFBBB888B8)) 
    Div_i1_mul_temp_i_32
       (.I0(uminus_cast_1[8]),
        .I1(DSP_A_B_DATA_INST_1),
        .I2(Div_i1_mul_temp_i_58_n_0),
        .I3(Div_i1_mul_temp_i_50_0),
        .I4(Div_i1_mul_temp_i_60_n_0),
        .I5(DSP_A_B_DATA_INST_0),
        .O(A[8]));
  LUT6 #(
    .INIT(64'hFFFFFFFFBBB888B8)) 
    Div_i1_mul_temp_i_33
       (.I0(uminus_cast_1[7]),
        .I1(DSP_A_B_DATA_INST_1),
        .I2(Div_i1_mul_temp_i_60_n_0),
        .I3(Div_i1_mul_temp_i_50_0),
        .I4(Div_i1_mul_temp_i_61_n_0),
        .I5(DSP_A_B_DATA_INST_0),
        .O(A[7]));
  LUT6 #(
    .INIT(64'hFFFFFFFFBBB888B8)) 
    Div_i1_mul_temp_i_34
       (.I0(uminus_cast_1[6]),
        .I1(DSP_A_B_DATA_INST_1),
        .I2(Div_i1_mul_temp_i_61_n_0),
        .I3(Div_i1_mul_temp_i_50_0),
        .I4(Div_i1_mul_temp_i_62_n_0),
        .I5(DSP_A_B_DATA_INST_0),
        .O(A[6]));
  LUT6 #(
    .INIT(64'hFFFFFFFFBBB888B8)) 
    Div_i1_mul_temp_i_35
       (.I0(uminus_cast_1[5]),
        .I1(DSP_A_B_DATA_INST_1),
        .I2(Div_i1_mul_temp_i_62_n_0),
        .I3(Div_i1_mul_temp_i_50_0),
        .I4(Div_i1_mul_temp_i_63_n_0),
        .I5(DSP_A_B_DATA_INST_0),
        .O(A[5]));
  LUT6 #(
    .INIT(64'hFFFFFFFFBBB888B8)) 
    Div_i1_mul_temp_i_36
       (.I0(uminus_cast_1[4]),
        .I1(DSP_A_B_DATA_INST_1),
        .I2(Div_i1_mul_temp_i_63_n_0),
        .I3(Div_i1_mul_temp_i_50_0),
        .I4(Div_i1_mul_temp_i_64_n_0),
        .I5(DSP_A_B_DATA_INST_0),
        .O(A[4]));
  LUT6 #(
    .INIT(64'hFFFFFFFFBBB888B8)) 
    Div_i1_mul_temp_i_37
       (.I0(uminus_cast_1[3]),
        .I1(DSP_A_B_DATA_INST_1),
        .I2(Div_i1_mul_temp_i_64_n_0),
        .I3(Div_i1_mul_temp_i_50_0),
        .I4(Div_i1_mul_temp_i_65_n_0),
        .I5(DSP_A_B_DATA_INST_0),
        .O(A[3]));
  LUT6 #(
    .INIT(64'hFFFFFFFFBBB888B8)) 
    Div_i1_mul_temp_i_38
       (.I0(uminus_cast_1[2]),
        .I1(DSP_A_B_DATA_INST_1),
        .I2(Div_i1_mul_temp_i_65_n_0),
        .I3(Div_i1_mul_temp_i_50_0),
        .I4(Div_i1_mul_temp_i_66_n_0),
        .I5(DSP_A_B_DATA_INST_0),
        .O(A[2]));
  LUT6 #(
    .INIT(64'hFFFFFFFFBBB888B8)) 
    Div_i1_mul_temp_i_39
       (.I0(uminus_cast_1[1]),
        .I1(DSP_A_B_DATA_INST_1),
        .I2(Div_i1_mul_temp_i_66_n_0),
        .I3(Div_i1_mul_temp_i_50_0),
        .I4(Div_i1_mul_temp_i_67_n_0),
        .I5(DSP_A_B_DATA_INST_0),
        .O(A[1]));
  LUT4 #(
    .INIT(16'hFFE2)) 
    Div_i1_mul_temp_i_40
       (.I0(Div_i1_mul_temp_i_67_n_0),
        .I1(Div_i1_mul_temp_i_50_0),
        .I2(Div_i1_mul_temp_i_68_n_0),
        .I3(DSP_A_B_DATA_INST_0),
        .O(A[0]));
  CARRY8 Div_i1_mul_temp_i_41
       (.CI(Div_i1_mul_temp_i_50_n_0),
        .CI_TOP(1'b0),
        .CO({NLW_Div_i1_mul_temp_i_41_CO_UNCONNECTED[7:6],Div_i1_mul_temp_i_41_n_2,Div_i1_mul_temp_i_41_n_3,Div_i1_mul_temp_i_41_n_4,Div_i1_mul_temp_i_41_n_5,Div_i1_mul_temp_i_41_n_6,Div_i1_mul_temp_i_41_n_7}),
        .DI({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .O({NLW_Div_i1_mul_temp_i_41_O_UNCONNECTED[7],uminus_cast_1[23:17]}),
        .S({1'b0,Div_i1_mul_temp_i_69_n_0,Div_i1_mul_temp_i_70_n_0,Div_i1_mul_temp_i_71_n_0,Div_i1_mul_temp_i_72_n_0,Div_i1_mul_temp_i_73_n_0,Div_i1_mul_temp_i_74_n_0,Div_i1_mul_temp_i_75_n_0}));
  LUT6 #(
    .INIT(64'hFFFFFFFFA0800080)) 
    Div_i1_mul_temp_i_42
       (.I0(\ds_reg_reg_reg[3]_0 [3]),
        .I1(Div_i1_mul_temp_i_76_n_0),
        .I2(\ds_reg_reg_reg[3]_0 [2]),
        .I3(Div_i1_mul_temp_i_50_0),
        .I4(Div_i1_mul_temp_i_77_n_0),
        .I5(DSP_A_B_DATA_INST_0),
        .O(Div_i1_mul_temp_i_42_n_0));
  LUT3 #(
    .INIT(8'h80)) 
    Div_i1_mul_temp_i_43
       (.I0(\ds_reg_reg_reg[3]_0 [2]),
        .I1(Div_i1_mul_temp_i_77_n_0),
        .I2(\ds_reg_reg_reg[3]_0 [3]),
        .O(Div_i1_mul_temp_i_43_n_0));
  LUT6 #(
    .INIT(64'hFF80008000000000)) 
    Div_i1_mul_temp_i_44
       (.I0(\ds_reg_reg_reg[3]_0 [1]),
        .I1(\shiftarr[0]0 ),
        .I2(\ds_reg_reg_reg[3]_0 [0]),
        .I3(\ds_reg_reg_reg[3]_0 [2]),
        .I4(Div_i1_mul_temp_i_78_n_0),
        .I5(\ds_reg_reg_reg[3]_0 [3]),
        .O(Div_i1_mul_temp_i_44_n_0));
  LUT6 #(
    .INIT(64'hFF80008000000000)) 
    Div_i1_mul_temp_i_45
       (.I0(\ds_reg_reg_reg[3]_0 [1]),
        .I1(\xout_tmp_reg_n_0_[30] ),
        .I2(\ds_reg_reg_reg[3]_0 [0]),
        .I3(\ds_reg_reg_reg[3]_0 [2]),
        .I4(Div_i1_mul_temp_i_79_n_0),
        .I5(\ds_reg_reg_reg[3]_0 [3]),
        .O(Div_i1_mul_temp_i_45_n_0));
  (* SOFT_HLUTNM = "soft_lutpair45" *) 
  LUT2 #(
    .INIT(4'h8)) 
    Div_i1_mul_temp_i_46
       (.I0(Div_i1_mul_temp_i_80_n_0),
        .I1(\ds_reg_reg_reg[3]_0 [3]),
        .O(Div_i1_mul_temp_i_46_n_0));
  (* SOFT_HLUTNM = "soft_lutpair43" *) 
  LUT2 #(
    .INIT(4'h8)) 
    Div_i1_mul_temp_i_47
       (.I0(Div_i1_mul_temp_i_81_n_0),
        .I1(\ds_reg_reg_reg[3]_0 [3]),
        .O(Div_i1_mul_temp_i_47_n_0));
  (* SOFT_HLUTNM = "soft_lutpair47" *) 
  LUT4 #(
    .INIT(16'hE200)) 
    Div_i1_mul_temp_i_48
       (.I0(Div_i1_mul_temp_i_82_n_0),
        .I1(\ds_reg_reg_reg[3]_0 [2]),
        .I2(Div_i1_mul_temp_i_83_n_0),
        .I3(\ds_reg_reg_reg[3]_0 [3]),
        .O(Div_i1_mul_temp_i_48_n_0));
  (* SOFT_HLUTNM = "soft_lutpair48" *) 
  LUT4 #(
    .INIT(16'hE200)) 
    Div_i1_mul_temp_i_49
       (.I0(Div_i1_mul_temp_i_84_n_0),
        .I1(\ds_reg_reg_reg[3]_0 [2]),
        .I2(Div_i1_mul_temp_i_85_n_0),
        .I3(\ds_reg_reg_reg[3]_0 [3]),
        .O(Div_i1_mul_temp_i_49_n_0));
  CARRY8 Div_i1_mul_temp_i_50
       (.CI(Div_i1_mul_temp_i_59_n_0),
        .CI_TOP(1'b0),
        .CO({Div_i1_mul_temp_i_50_n_0,Div_i1_mul_temp_i_50_n_1,Div_i1_mul_temp_i_50_n_2,Div_i1_mul_temp_i_50_n_3,Div_i1_mul_temp_i_50_n_4,Div_i1_mul_temp_i_50_n_5,Div_i1_mul_temp_i_50_n_6,Div_i1_mul_temp_i_50_n_7}),
        .DI({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .O(uminus_cast_1[16:9]),
        .S({Div_i1_mul_temp_i_86_n_0,Div_i1_mul_temp_i_87_n_0,Div_i1_mul_temp_i_88_n_0,Div_i1_mul_temp_i_89_n_0,Div_i1_mul_temp_i_90_n_0,Div_i1_mul_temp_i_91_n_0,Div_i1_mul_temp_i_92_n_0,Div_i1_mul_temp_i_93_n_0}));
  (* SOFT_HLUTNM = "soft_lutpair46" *) 
  LUT4 #(
    .INIT(16'hE200)) 
    Div_i1_mul_temp_i_51
       (.I0(Div_i1_mul_temp_i_76_n_0),
        .I1(\ds_reg_reg_reg[3]_0 [2]),
        .I2(Div_i1_mul_temp_i_94_n_0),
        .I3(\ds_reg_reg_reg[3]_0 [3]),
        .O(Div_i1_mul_temp_i_51_n_0));
  (* SOFT_HLUTNM = "soft_lutpair44" *) 
  LUT4 #(
    .INIT(16'hE200)) 
    Div_i1_mul_temp_i_52
       (.I0(Div_i1_mul_temp_i_77_n_0),
        .I1(\ds_reg_reg_reg[3]_0 [2]),
        .I2(Div_i1_mul_temp_i_95_n_0),
        .I3(\ds_reg_reg_reg[3]_0 [3]),
        .O(Div_i1_mul_temp_i_52_n_0));
  LUT6 #(
    .INIT(64'hAFA0A0A0C0C0C0C0)) 
    Div_i1_mul_temp_i_53
       (.I0(Div_i1_mul_temp_i_96_n_0),
        .I1(Div_i1_mul_temp_i_78_n_0),
        .I2(\ds_reg_reg_reg[3]_0 [3]),
        .I3(\ds_reg_reg_reg[3]_0 [1]),
        .I4(Div_i1_mul_temp_i_97_n_0),
        .I5(\ds_reg_reg_reg[3]_0 [2]),
        .O(Div_i1_mul_temp_i_53_n_0));
  LUT6 #(
    .INIT(64'hAFA0A0A0C0C0C0C0)) 
    Div_i1_mul_temp_i_54
       (.I0(Div_i1_mul_temp_i_98_n_0),
        .I1(Div_i1_mul_temp_i_79_n_0),
        .I2(\ds_reg_reg_reg[3]_0 [3]),
        .I3(\ds_reg_reg_reg[3]_0 [1]),
        .I4(Div_i1_mul_temp_i_99_n_0),
        .I5(\ds_reg_reg_reg[3]_0 [2]),
        .O(Div_i1_mul_temp_i_54_n_0));
  LUT5 #(
    .INIT(32'hAFA0C0C0)) 
    Div_i1_mul_temp_i_55
       (.I0(Div_i1_mul_temp_i_100_n_0),
        .I1(Div_i1_mul_temp_i_101_n_0),
        .I2(\ds_reg_reg_reg[3]_0 [3]),
        .I3(Div_i1_mul_temp_i_102_n_0),
        .I4(\ds_reg_reg_reg[3]_0 [2]),
        .O(Div_i1_mul_temp_i_55_n_0));
  LUT5 #(
    .INIT(32'hAFA0C0C0)) 
    Div_i1_mul_temp_i_56
       (.I0(Div_i1_mul_temp_i_103_n_0),
        .I1(Div_i1_mul_temp_i_104_n_0),
        .I2(\ds_reg_reg_reg[3]_0 [3]),
        .I3(Div_i1_mul_temp_i_105_n_0),
        .I4(\ds_reg_reg_reg[3]_0 [2]),
        .O(Div_i1_mul_temp_i_56_n_0));
  (* SOFT_HLUTNM = "soft_lutpair47" *) 
  LUT5 #(
    .INIT(32'hAFA0C0C0)) 
    Div_i1_mul_temp_i_57
       (.I0(Div_i1_mul_temp_i_106_n_0),
        .I1(Div_i1_mul_temp_i_83_n_0),
        .I2(\ds_reg_reg_reg[3]_0 [3]),
        .I3(Div_i1_mul_temp_i_82_n_0),
        .I4(\ds_reg_reg_reg[3]_0 [2]),
        .O(Div_i1_mul_temp_i_57_n_0));
  (* SOFT_HLUTNM = "soft_lutpair48" *) 
  LUT5 #(
    .INIT(32'hAFA0C0C0)) 
    Div_i1_mul_temp_i_58
       (.I0(Div_i1_mul_temp_i_107_n_0),
        .I1(Div_i1_mul_temp_i_85_n_0),
        .I2(\ds_reg_reg_reg[3]_0 [3]),
        .I3(Div_i1_mul_temp_i_84_n_0),
        .I4(\ds_reg_reg_reg[3]_0 [2]),
        .O(Div_i1_mul_temp_i_58_n_0));
  CARRY8 Div_i1_mul_temp_i_59
       (.CI(Div_i1_mul_temp_i_108_n_0),
        .CI_TOP(1'b0),
        .CO({Div_i1_mul_temp_i_59_n_0,Div_i1_mul_temp_i_59_n_1,Div_i1_mul_temp_i_59_n_2,Div_i1_mul_temp_i_59_n_3,Div_i1_mul_temp_i_59_n_4,Div_i1_mul_temp_i_59_n_5,Div_i1_mul_temp_i_59_n_6,Div_i1_mul_temp_i_59_n_7}),
        .DI({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .O(uminus_cast_1[8:1]),
        .S({Div_i1_mul_temp_i_109_n_0,Div_i1_mul_temp_i_110_n_0,Div_i1_mul_temp_i_111_n_0,Div_i1_mul_temp_i_112_n_0,Div_i1_mul_temp_i_113_n_0,Div_i1_mul_temp_i_114_n_0,Div_i1_mul_temp_i_115_n_0,Div_i1_mul_temp_i_116_n_0}));
  (* SOFT_HLUTNM = "soft_lutpair46" *) 
  LUT5 #(
    .INIT(32'hAFA0C0C0)) 
    Div_i1_mul_temp_i_60
       (.I0(Div_i1_mul_temp_i_117_n_0),
        .I1(Div_i1_mul_temp_i_94_n_0),
        .I2(\ds_reg_reg_reg[3]_0 [3]),
        .I3(Div_i1_mul_temp_i_76_n_0),
        .I4(\ds_reg_reg_reg[3]_0 [2]),
        .O(Div_i1_mul_temp_i_60_n_0));
  (* SOFT_HLUTNM = "soft_lutpair44" *) 
  LUT5 #(
    .INIT(32'hAFA0C0C0)) 
    Div_i1_mul_temp_i_61
       (.I0(Div_i1_mul_temp_i_118_n_0),
        .I1(Div_i1_mul_temp_i_95_n_0),
        .I2(\ds_reg_reg_reg[3]_0 [3]),
        .I3(Div_i1_mul_temp_i_77_n_0),
        .I4(\ds_reg_reg_reg[3]_0 [2]),
        .O(Div_i1_mul_temp_i_61_n_0));
  LUT5 #(
    .INIT(32'hB8FFB800)) 
    Div_i1_mul_temp_i_62
       (.I0(Div_i1_mul_temp_i_119_n_0),
        .I1(\ds_reg_reg_reg[3]_0 [2]),
        .I2(Div_i1_mul_temp_i_96_n_0),
        .I3(\ds_reg_reg_reg[3]_0 [3]),
        .I4(Div_i1_mul_temp_i_120_n_0),
        .O(Div_i1_mul_temp_i_62_n_0));
  LUT5 #(
    .INIT(32'hB8FFB800)) 
    Div_i1_mul_temp_i_63
       (.I0(Div_i1_mul_temp_i_121_n_0),
        .I1(\ds_reg_reg_reg[3]_0 [2]),
        .I2(Div_i1_mul_temp_i_98_n_0),
        .I3(\ds_reg_reg_reg[3]_0 [3]),
        .I4(Div_i1_mul_temp_i_122_n_0),
        .O(Div_i1_mul_temp_i_63_n_0));
  (* SOFT_HLUTNM = "soft_lutpair45" *) 
  LUT5 #(
    .INIT(32'hB8FFB800)) 
    Div_i1_mul_temp_i_64
       (.I0(Div_i1_mul_temp_i_123_n_0),
        .I1(\ds_reg_reg_reg[3]_0 [2]),
        .I2(Div_i1_mul_temp_i_100_n_0),
        .I3(\ds_reg_reg_reg[3]_0 [3]),
        .I4(Div_i1_mul_temp_i_80_n_0),
        .O(Div_i1_mul_temp_i_64_n_0));
  (* SOFT_HLUTNM = "soft_lutpair43" *) 
  LUT5 #(
    .INIT(32'hB8FFB800)) 
    Div_i1_mul_temp_i_65
       (.I0(Div_i1_mul_temp_i_124_n_0),
        .I1(\ds_reg_reg_reg[3]_0 [2]),
        .I2(Div_i1_mul_temp_i_103_n_0),
        .I3(\ds_reg_reg_reg[3]_0 [3]),
        .I4(Div_i1_mul_temp_i_81_n_0),
        .O(Div_i1_mul_temp_i_65_n_0));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    Div_i1_mul_temp_i_66
       (.I0(Div_i1_mul_temp_i_125_n_0),
        .I1(Div_i1_mul_temp_i_106_n_0),
        .I2(\ds_reg_reg_reg[3]_0 [3]),
        .I3(Div_i1_mul_temp_i_83_n_0),
        .I4(\ds_reg_reg_reg[3]_0 [2]),
        .I5(Div_i1_mul_temp_i_82_n_0),
        .O(Div_i1_mul_temp_i_66_n_0));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    Div_i1_mul_temp_i_67
       (.I0(Div_i1_mul_temp_i_126_n_0),
        .I1(Div_i1_mul_temp_i_107_n_0),
        .I2(\ds_reg_reg_reg[3]_0 [3]),
        .I3(Div_i1_mul_temp_i_85_n_0),
        .I4(\ds_reg_reg_reg[3]_0 [2]),
        .I5(Div_i1_mul_temp_i_84_n_0),
        .O(Div_i1_mul_temp_i_67_n_0));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    Div_i1_mul_temp_i_68
       (.I0(Div_i1_mul_temp_i_127_n_0),
        .I1(Div_i1_mul_temp_i_117_n_0),
        .I2(\ds_reg_reg_reg[3]_0 [3]),
        .I3(Div_i1_mul_temp_i_94_n_0),
        .I4(\ds_reg_reg_reg[3]_0 [2]),
        .I5(Div_i1_mul_temp_i_76_n_0),
        .O(Div_i1_mul_temp_i_68_n_0));
  LUT5 #(
    .INIT(32'hBF8FFFFF)) 
    Div_i1_mul_temp_i_69
       (.I0(Div_i1_mul_temp_i_128_n_0),
        .I1(Div_i1_mul_temp_i_50_0),
        .I2(\ds_reg_reg_reg[3]_0 [2]),
        .I3(Div_i1_mul_temp_i_129_n_0),
        .I4(\ds_reg_reg_reg[3]_0 [3]),
        .O(Div_i1_mul_temp_i_69_n_0));
  LUT5 #(
    .INIT(32'hBB8BBBBB)) 
    Div_i1_mul_temp_i_70
       (.I0(Div_i1_mul_temp_i_130_n_0),
        .I1(Div_i1_mul_temp_i_50_0),
        .I2(\ds_reg_reg_reg[3]_0 [2]),
        .I3(Div_i1_mul_temp_i_128_n_0),
        .I4(\ds_reg_reg_reg[3]_0 [3]),
        .O(Div_i1_mul_temp_i_70_n_0));
  LUT3 #(
    .INIT(8'hB8)) 
    Div_i1_mul_temp_i_71
       (.I0(Div_i1_mul_temp_i_131_n_0),
        .I1(Div_i1_mul_temp_i_50_0),
        .I2(Div_i1_mul_temp_i_130_n_0),
        .O(Div_i1_mul_temp_i_71_n_0));
  LUT4 #(
    .INIT(16'hBFB0)) 
    Div_i1_mul_temp_i_72
       (.I0(Div_i1_mul_temp_i_132_n_0),
        .I1(\ds_reg_reg_reg[3]_0 [3]),
        .I2(Div_i1_mul_temp_i_50_0),
        .I3(Div_i1_mul_temp_i_131_n_0),
        .O(Div_i1_mul_temp_i_72_n_0));
  LUT4 #(
    .INIT(16'hB8FF)) 
    Div_i1_mul_temp_i_73
       (.I0(Div_i1_mul_temp_i_133_n_0),
        .I1(Div_i1_mul_temp_i_50_0),
        .I2(Div_i1_mul_temp_i_132_n_0),
        .I3(\ds_reg_reg_reg[3]_0 [3]),
        .O(Div_i1_mul_temp_i_73_n_0));
  LUT4 #(
    .INIT(16'hB8BB)) 
    Div_i1_mul_temp_i_74
       (.I0(Div_i1_mul_temp_i_134_n_0),
        .I1(Div_i1_mul_temp_i_50_0),
        .I2(Div_i1_mul_temp_i_133_n_0),
        .I3(\ds_reg_reg_reg[3]_0 [3]),
        .O(Div_i1_mul_temp_i_74_n_0));
  LUT6 #(
    .INIT(64'hE2FFFFFFE2FF0000)) 
    Div_i1_mul_temp_i_75
       (.I0(Div_i1_mul_temp_i_135_n_0),
        .I1(\ds_reg_reg_reg[3]_0 [2]),
        .I2(Div_i1_mul_temp_i_136_n_0),
        .I3(\ds_reg_reg_reg[3]_0 [3]),
        .I4(Div_i1_mul_temp_i_50_0),
        .I5(Div_i1_mul_temp_i_134_n_0),
        .O(Div_i1_mul_temp_i_75_n_0));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    Div_i1_mul_temp_i_76
       (.I0(\xout_tmp_reg_n_0_[25] ),
        .I1(\xout_tmp_reg_n_0_[27] ),
        .I2(\ds_reg_reg_reg[3]_0 [1]),
        .I3(\xout_tmp_reg_n_0_[29] ),
        .I4(\ds_reg_reg_reg[3]_0 [0]),
        .I5(\shiftarr[0]0 ),
        .O(Div_i1_mul_temp_i_76_n_0));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    Div_i1_mul_temp_i_77
       (.I0(\xout_tmp_reg_n_0_[24] ),
        .I1(\xout_tmp_reg_n_0_[26] ),
        .I2(\ds_reg_reg_reg[3]_0 [1]),
        .I3(\xout_tmp_reg_n_0_[28] ),
        .I4(\ds_reg_reg_reg[3]_0 [0]),
        .I5(\xout_tmp_reg_n_0_[30] ),
        .O(Div_i1_mul_temp_i_77_n_0));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    Div_i1_mul_temp_i_78
       (.I0(\xout_tmp_reg_n_0_[23] ),
        .I1(\xout_tmp_reg_n_0_[25] ),
        .I2(\ds_reg_reg_reg[3]_0 [1]),
        .I3(\xout_tmp_reg_n_0_[27] ),
        .I4(\ds_reg_reg_reg[3]_0 [0]),
        .I5(\xout_tmp_reg_n_0_[29] ),
        .O(Div_i1_mul_temp_i_78_n_0));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    Div_i1_mul_temp_i_79
       (.I0(\xout_tmp_reg_n_0_[22] ),
        .I1(\xout_tmp_reg_n_0_[24] ),
        .I2(\ds_reg_reg_reg[3]_0 [1]),
        .I3(\xout_tmp_reg_n_0_[26] ),
        .I4(\ds_reg_reg_reg[3]_0 [0]),
        .I5(\xout_tmp_reg_n_0_[28] ),
        .O(Div_i1_mul_temp_i_79_n_0));
  LUT6 #(
    .INIT(64'hBBB888B888888888)) 
    Div_i1_mul_temp_i_80
       (.I0(Div_i1_mul_temp_i_101_n_0),
        .I1(\ds_reg_reg_reg[3]_0 [2]),
        .I2(\shiftarr[0]0 ),
        .I3(\ds_reg_reg_reg[3]_0 [0]),
        .I4(\xout_tmp_reg_n_0_[29] ),
        .I5(\ds_reg_reg_reg[3]_0 [1]),
        .O(Div_i1_mul_temp_i_80_n_0));
  LUT6 #(
    .INIT(64'hBBB888B888888888)) 
    Div_i1_mul_temp_i_81
       (.I0(Div_i1_mul_temp_i_104_n_0),
        .I1(\ds_reg_reg_reg[3]_0 [2]),
        .I2(\xout_tmp_reg_n_0_[30] ),
        .I3(\ds_reg_reg_reg[3]_0 [0]),
        .I4(\xout_tmp_reg_n_0_[28] ),
        .I5(\ds_reg_reg_reg[3]_0 [1]),
        .O(Div_i1_mul_temp_i_81_n_0));
  (* SOFT_HLUTNM = "soft_lutpair42" *) 
  LUT5 #(
    .INIT(32'hAFA0C0C0)) 
    Div_i1_mul_temp_i_82
       (.I0(\xout_tmp_reg_n_0_[27] ),
        .I1(\xout_tmp_reg_n_0_[29] ),
        .I2(\ds_reg_reg_reg[3]_0 [1]),
        .I3(\shiftarr[0]0 ),
        .I4(\ds_reg_reg_reg[3]_0 [0]),
        .O(Div_i1_mul_temp_i_82_n_0));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    Div_i1_mul_temp_i_83
       (.I0(\xout_tmp_reg_n_0_[19] ),
        .I1(\xout_tmp_reg_n_0_[21] ),
        .I2(\ds_reg_reg_reg[3]_0 [1]),
        .I3(\xout_tmp_reg_n_0_[23] ),
        .I4(\ds_reg_reg_reg[3]_0 [0]),
        .I5(\xout_tmp_reg_n_0_[25] ),
        .O(Div_i1_mul_temp_i_83_n_0));
  (* SOFT_HLUTNM = "soft_lutpair38" *) 
  LUT5 #(
    .INIT(32'hAFA0C0C0)) 
    Div_i1_mul_temp_i_84
       (.I0(\xout_tmp_reg_n_0_[26] ),
        .I1(\xout_tmp_reg_n_0_[28] ),
        .I2(\ds_reg_reg_reg[3]_0 [1]),
        .I3(\xout_tmp_reg_n_0_[30] ),
        .I4(\ds_reg_reg_reg[3]_0 [0]),
        .O(Div_i1_mul_temp_i_84_n_0));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    Div_i1_mul_temp_i_85
       (.I0(\xout_tmp_reg_n_0_[18] ),
        .I1(\xout_tmp_reg_n_0_[20] ),
        .I2(\ds_reg_reg_reg[3]_0 [1]),
        .I3(\xout_tmp_reg_n_0_[22] ),
        .I4(\ds_reg_reg_reg[3]_0 [0]),
        .I5(\xout_tmp_reg_n_0_[24] ),
        .O(Div_i1_mul_temp_i_85_n_0));
  LUT6 #(
    .INIT(64'hFFFF0000E2FFE2FF)) 
    Div_i1_mul_temp_i_86
       (.I0(Div_i1_mul_temp_i_135_n_0),
        .I1(\ds_reg_reg_reg[3]_0 [2]),
        .I2(Div_i1_mul_temp_i_136_n_0),
        .I3(\ds_reg_reg_reg[3]_0 [3]),
        .I4(Div_i1_mul_temp_i_137_n_0),
        .I5(Div_i1_mul_temp_i_50_0),
        .O(Div_i1_mul_temp_i_86_n_0));
  LUT6 #(
    .INIT(64'hE2FFFFFFE2FF0000)) 
    Div_i1_mul_temp_i_87
       (.I0(Div_i1_mul_temp_i_128_n_0),
        .I1(\ds_reg_reg_reg[3]_0 [2]),
        .I2(Div_i1_mul_temp_i_138_n_0),
        .I3(\ds_reg_reg_reg[3]_0 [3]),
        .I4(Div_i1_mul_temp_i_50_0),
        .I5(Div_i1_mul_temp_i_137_n_0),
        .O(Div_i1_mul_temp_i_87_n_0));
  LUT6 #(
    .INIT(64'hFFFF0000E2FFE2FF)) 
    Div_i1_mul_temp_i_88
       (.I0(Div_i1_mul_temp_i_128_n_0),
        .I1(\ds_reg_reg_reg[3]_0 [2]),
        .I2(Div_i1_mul_temp_i_138_n_0),
        .I3(\ds_reg_reg_reg[3]_0 [3]),
        .I4(Div_i1_mul_temp_i_139_n_0),
        .I5(Div_i1_mul_temp_i_50_0),
        .O(Div_i1_mul_temp_i_88_n_0));
  LUT3 #(
    .INIT(8'hB8)) 
    Div_i1_mul_temp_i_89
       (.I0(Div_i1_mul_temp_i_140_n_0),
        .I1(Div_i1_mul_temp_i_50_0),
        .I2(Div_i1_mul_temp_i_139_n_0),
        .O(Div_i1_mul_temp_i_89_n_0));
  LUT3 #(
    .INIT(8'hB8)) 
    Div_i1_mul_temp_i_90
       (.I0(Div_i1_mul_temp_i_141_n_0),
        .I1(Div_i1_mul_temp_i_50_0),
        .I2(Div_i1_mul_temp_i_140_n_0),
        .O(Div_i1_mul_temp_i_90_n_0));
  LUT3 #(
    .INIT(8'hB8)) 
    Div_i1_mul_temp_i_91
       (.I0(Div_i1_mul_temp_i_142_n_0),
        .I1(Div_i1_mul_temp_i_50_0),
        .I2(Div_i1_mul_temp_i_141_n_0),
        .O(Div_i1_mul_temp_i_91_n_0));
  LUT3 #(
    .INIT(8'hB8)) 
    Div_i1_mul_temp_i_92
       (.I0(Div_i1_mul_temp_i_143_n_0),
        .I1(Div_i1_mul_temp_i_50_0),
        .I2(Div_i1_mul_temp_i_142_n_0),
        .O(Div_i1_mul_temp_i_92_n_0));
  LUT3 #(
    .INIT(8'hB8)) 
    Div_i1_mul_temp_i_93
       (.I0(Div_i1_mul_temp_i_144_n_0),
        .I1(Div_i1_mul_temp_i_50_0),
        .I2(Div_i1_mul_temp_i_143_n_0),
        .O(Div_i1_mul_temp_i_93_n_0));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    Div_i1_mul_temp_i_94
       (.I0(\xout_tmp_reg_n_0_[17] ),
        .I1(\xout_tmp_reg_n_0_[19] ),
        .I2(\ds_reg_reg_reg[3]_0 [1]),
        .I3(\xout_tmp_reg_n_0_[21] ),
        .I4(\ds_reg_reg_reg[3]_0 [0]),
        .I5(\xout_tmp_reg_n_0_[23] ),
        .O(Div_i1_mul_temp_i_94_n_0));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    Div_i1_mul_temp_i_95
       (.I0(\xout_tmp_reg_n_0_[16] ),
        .I1(\xout_tmp_reg_n_0_[18] ),
        .I2(\ds_reg_reg_reg[3]_0 [1]),
        .I3(\xout_tmp_reg_n_0_[20] ),
        .I4(\ds_reg_reg_reg[3]_0 [0]),
        .I5(\xout_tmp_reg_n_0_[22] ),
        .O(Div_i1_mul_temp_i_95_n_0));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    Div_i1_mul_temp_i_96
       (.I0(\xout_tmp_reg_n_0_[15] ),
        .I1(\xout_tmp_reg_n_0_[17] ),
        .I2(\ds_reg_reg_reg[3]_0 [1]),
        .I3(\xout_tmp_reg_n_0_[19] ),
        .I4(\ds_reg_reg_reg[3]_0 [0]),
        .I5(\xout_tmp_reg_n_0_[21] ),
        .O(Div_i1_mul_temp_i_96_n_0));
  (* SOFT_HLUTNM = "soft_lutpair40" *) 
  LUT2 #(
    .INIT(4'h8)) 
    Div_i1_mul_temp_i_97
       (.I0(\shiftarr[0]0 ),
        .I1(\ds_reg_reg_reg[3]_0 [0]),
        .O(Div_i1_mul_temp_i_97_n_0));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    Div_i1_mul_temp_i_98
       (.I0(\xout_tmp_reg_n_0_[14] ),
        .I1(\xout_tmp_reg_n_0_[16] ),
        .I2(\ds_reg_reg_reg[3]_0 [1]),
        .I3(\xout_tmp_reg_n_0_[18] ),
        .I4(\ds_reg_reg_reg[3]_0 [0]),
        .I5(\xout_tmp_reg_n_0_[20] ),
        .O(Div_i1_mul_temp_i_98_n_0));
  (* SOFT_HLUTNM = "soft_lutpair37" *) 
  LUT2 #(
    .INIT(4'h8)) 
    Div_i1_mul_temp_i_99
       (.I0(\xout_tmp_reg_n_0_[30] ),
        .I1(\ds_reg_reg_reg[3]_0 [0]),
        .O(Div_i1_mul_temp_i_99_n_0));
  (* SOFT_HLUTNM = "soft_lutpair68" *) 
  LUT3 #(
    .INIT(8'hFE)) 
    \delayout[0]_i_1 
       (.I0(mul1_mul_temp_carry__4_n_9),
        .I1(mul1_mul_temp_carry__4_n_8),
        .I2(mul1_mul_temp_carry__0_n_9),
        .O(\delayout[0]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair63" *) 
  LUT3 #(
    .INIT(8'hFE)) 
    \delayout[10]_i_1 
       (.I0(mul1_mul_temp_carry__4_n_9),
        .I1(mul1_mul_temp_carry__4_n_8),
        .I2(mul1_mul_temp_carry__2_n_15),
        .O(\delayout[10]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair63" *) 
  LUT3 #(
    .INIT(8'hFE)) 
    \delayout[11]_i_1 
       (.I0(mul1_mul_temp_carry__4_n_9),
        .I1(mul1_mul_temp_carry__4_n_8),
        .I2(mul1_mul_temp_carry__2_n_14),
        .O(\delayout[11]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair62" *) 
  LUT3 #(
    .INIT(8'hFE)) 
    \delayout[12]_i_1 
       (.I0(mul1_mul_temp_carry__4_n_9),
        .I1(mul1_mul_temp_carry__4_n_8),
        .I2(mul1_mul_temp_carry__2_n_13),
        .O(\delayout[12]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair62" *) 
  LUT3 #(
    .INIT(8'hFE)) 
    \delayout[13]_i_1 
       (.I0(mul1_mul_temp_carry__4_n_9),
        .I1(mul1_mul_temp_carry__4_n_8),
        .I2(mul1_mul_temp_carry__2_n_12),
        .O(\delayout[13]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair61" *) 
  LUT3 #(
    .INIT(8'hFE)) 
    \delayout[14]_i_1 
       (.I0(mul1_mul_temp_carry__4_n_9),
        .I1(mul1_mul_temp_carry__4_n_8),
        .I2(mul1_mul_temp_carry__2_n_11),
        .O(\delayout[14]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair61" *) 
  LUT3 #(
    .INIT(8'hFE)) 
    \delayout[15]_i_1 
       (.I0(mul1_mul_temp_carry__4_n_9),
        .I1(mul1_mul_temp_carry__4_n_8),
        .I2(mul1_mul_temp_carry__2_n_10),
        .O(\delayout[15]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair60" *) 
  LUT3 #(
    .INIT(8'hFE)) 
    \delayout[16]_i_1 
       (.I0(mul1_mul_temp_carry__4_n_9),
        .I1(mul1_mul_temp_carry__4_n_8),
        .I2(mul1_mul_temp_carry__2_n_9),
        .O(\delayout[16]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair60" *) 
  LUT3 #(
    .INIT(8'hFE)) 
    \delayout[17]_i_1 
       (.I0(mul1_mul_temp_carry__4_n_9),
        .I1(mul1_mul_temp_carry__4_n_8),
        .I2(mul1_mul_temp_carry__2_n_8),
        .O(\delayout[17]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair59" *) 
  LUT3 #(
    .INIT(8'hFE)) 
    \delayout[18]_i_1 
       (.I0(mul1_mul_temp_carry__4_n_9),
        .I1(mul1_mul_temp_carry__4_n_8),
        .I2(mul1_mul_temp_carry__3_n_15),
        .O(\delayout[18]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair59" *) 
  LUT3 #(
    .INIT(8'hFE)) 
    \delayout[19]_i_1 
       (.I0(mul1_mul_temp_carry__4_n_9),
        .I1(mul1_mul_temp_carry__4_n_8),
        .I2(mul1_mul_temp_carry__3_n_14),
        .O(\delayout[19]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair68" *) 
  LUT3 #(
    .INIT(8'hFE)) 
    \delayout[1]_i_1 
       (.I0(mul1_mul_temp_carry__4_n_9),
        .I1(mul1_mul_temp_carry__4_n_8),
        .I2(mul1_mul_temp_carry__0_n_8),
        .O(\delayout[1]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair58" *) 
  LUT3 #(
    .INIT(8'hFE)) 
    \delayout[20]_i_1 
       (.I0(mul1_mul_temp_carry__4_n_9),
        .I1(mul1_mul_temp_carry__4_n_8),
        .I2(mul1_mul_temp_carry__3_n_13),
        .O(\delayout[20]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair58" *) 
  LUT3 #(
    .INIT(8'hFE)) 
    \delayout[21]_i_1 
       (.I0(mul1_mul_temp_carry__4_n_9),
        .I1(mul1_mul_temp_carry__4_n_8),
        .I2(mul1_mul_temp_carry__3_n_12),
        .O(\delayout[21]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair57" *) 
  LUT3 #(
    .INIT(8'hFE)) 
    \delayout[22]_i_1 
       (.I0(mul1_mul_temp_carry__4_n_9),
        .I1(mul1_mul_temp_carry__4_n_8),
        .I2(mul1_mul_temp_carry__3_n_11),
        .O(\delayout[22]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair57" *) 
  LUT3 #(
    .INIT(8'hFE)) 
    \delayout[23]_i_1 
       (.I0(mul1_mul_temp_carry__4_n_9),
        .I1(mul1_mul_temp_carry__4_n_8),
        .I2(mul1_mul_temp_carry__3_n_10),
        .O(\delayout[23]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair56" *) 
  LUT3 #(
    .INIT(8'hFE)) 
    \delayout[24]_i_1 
       (.I0(mul1_mul_temp_carry__4_n_9),
        .I1(mul1_mul_temp_carry__4_n_8),
        .I2(mul1_mul_temp_carry__3_n_9),
        .O(\delayout[24]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair56" *) 
  LUT3 #(
    .INIT(8'hFE)) 
    \delayout[25]_i_1 
       (.I0(mul1_mul_temp_carry__4_n_9),
        .I1(mul1_mul_temp_carry__4_n_8),
        .I2(mul1_mul_temp_carry__3_n_8),
        .O(\delayout[25]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair55" *) 
  LUT3 #(
    .INIT(8'hFE)) 
    \delayout[26]_i_1 
       (.I0(mul1_mul_temp_carry__4_n_9),
        .I1(mul1_mul_temp_carry__4_n_8),
        .I2(mul1_mul_temp_carry__4_n_15),
        .O(\delayout[26]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair55" *) 
  LUT3 #(
    .INIT(8'hFE)) 
    \delayout[27]_i_1 
       (.I0(mul1_mul_temp_carry__4_n_9),
        .I1(mul1_mul_temp_carry__4_n_8),
        .I2(mul1_mul_temp_carry__4_n_14),
        .O(\delayout[27]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair54" *) 
  LUT3 #(
    .INIT(8'hFE)) 
    \delayout[28]_i_1 
       (.I0(mul1_mul_temp_carry__4_n_9),
        .I1(mul1_mul_temp_carry__4_n_8),
        .I2(mul1_mul_temp_carry__4_n_13),
        .O(\delayout[28]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair54" *) 
  LUT3 #(
    .INIT(8'hFE)) 
    \delayout[29]_i_1 
       (.I0(mul1_mul_temp_carry__4_n_9),
        .I1(mul1_mul_temp_carry__4_n_8),
        .I2(mul1_mul_temp_carry__4_n_12),
        .O(\delayout[29]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair67" *) 
  LUT3 #(
    .INIT(8'hFE)) 
    \delayout[2]_i_1 
       (.I0(mul1_mul_temp_carry__4_n_9),
        .I1(mul1_mul_temp_carry__4_n_8),
        .I2(mul1_mul_temp_carry__1_n_15),
        .O(\delayout[2]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair53" *) 
  LUT3 #(
    .INIT(8'hFE)) 
    \delayout[30]_i_1 
       (.I0(mul1_mul_temp_carry__4_n_9),
        .I1(mul1_mul_temp_carry__4_n_8),
        .I2(mul1_mul_temp_carry__4_n_11),
        .O(\delayout[30]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair53" *) 
  LUT3 #(
    .INIT(8'hFE)) 
    \delayout[31]_i_1 
       (.I0(mul1_mul_temp_carry__4_n_9),
        .I1(mul1_mul_temp_carry__4_n_8),
        .I2(mul1_mul_temp_carry__4_n_10),
        .O(\delayout[31]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair67" *) 
  LUT3 #(
    .INIT(8'hFE)) 
    \delayout[3]_i_1 
       (.I0(mul1_mul_temp_carry__4_n_9),
        .I1(mul1_mul_temp_carry__4_n_8),
        .I2(mul1_mul_temp_carry__1_n_14),
        .O(\delayout[3]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair66" *) 
  LUT3 #(
    .INIT(8'hFE)) 
    \delayout[4]_i_1 
       (.I0(mul1_mul_temp_carry__4_n_9),
        .I1(mul1_mul_temp_carry__4_n_8),
        .I2(mul1_mul_temp_carry__1_n_13),
        .O(\delayout[4]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair66" *) 
  LUT3 #(
    .INIT(8'hFE)) 
    \delayout[5]_i_1 
       (.I0(mul1_mul_temp_carry__4_n_9),
        .I1(mul1_mul_temp_carry__4_n_8),
        .I2(mul1_mul_temp_carry__1_n_12),
        .O(\delayout[5]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair65" *) 
  LUT3 #(
    .INIT(8'hFE)) 
    \delayout[6]_i_1 
       (.I0(mul1_mul_temp_carry__4_n_9),
        .I1(mul1_mul_temp_carry__4_n_8),
        .I2(mul1_mul_temp_carry__1_n_11),
        .O(\delayout[6]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair65" *) 
  LUT3 #(
    .INIT(8'hFE)) 
    \delayout[7]_i_1 
       (.I0(mul1_mul_temp_carry__4_n_9),
        .I1(mul1_mul_temp_carry__4_n_8),
        .I2(mul1_mul_temp_carry__1_n_10),
        .O(\delayout[7]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair64" *) 
  LUT3 #(
    .INIT(8'hFE)) 
    \delayout[8]_i_1 
       (.I0(mul1_mul_temp_carry__4_n_9),
        .I1(mul1_mul_temp_carry__4_n_8),
        .I2(mul1_mul_temp_carry__1_n_9),
        .O(\delayout[8]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair64" *) 
  LUT3 #(
    .INIT(8'hFE)) 
    \delayout[9]_i_1 
       (.I0(mul1_mul_temp_carry__4_n_9),
        .I1(mul1_mul_temp_carry__4_n_8),
        .I2(mul1_mul_temp_carry__1_n_8),
        .O(\delayout[9]_i_1_n_0 ));
  FDRE \delayout_reg[0] 
       (.C(IPCORE_CLK),
        .CE(write_axi_enable),
        .D(\delayout[0]_i_1_n_0 ),
        .Q(Q[0]),
        .R(RSTP));
  FDRE \delayout_reg[10] 
       (.C(IPCORE_CLK),
        .CE(write_axi_enable),
        .D(\delayout[10]_i_1_n_0 ),
        .Q(Q[10]),
        .R(RSTP));
  FDRE \delayout_reg[11] 
       (.C(IPCORE_CLK),
        .CE(write_axi_enable),
        .D(\delayout[11]_i_1_n_0 ),
        .Q(Q[11]),
        .R(RSTP));
  FDRE \delayout_reg[12] 
       (.C(IPCORE_CLK),
        .CE(write_axi_enable),
        .D(\delayout[12]_i_1_n_0 ),
        .Q(Q[12]),
        .R(RSTP));
  FDRE \delayout_reg[13] 
       (.C(IPCORE_CLK),
        .CE(write_axi_enable),
        .D(\delayout[13]_i_1_n_0 ),
        .Q(Q[13]),
        .R(RSTP));
  FDRE \delayout_reg[14] 
       (.C(IPCORE_CLK),
        .CE(write_axi_enable),
        .D(\delayout[14]_i_1_n_0 ),
        .Q(Q[14]),
        .R(RSTP));
  FDRE \delayout_reg[15] 
       (.C(IPCORE_CLK),
        .CE(write_axi_enable),
        .D(\delayout[15]_i_1_n_0 ),
        .Q(Q[15]),
        .R(RSTP));
  FDRE \delayout_reg[16] 
       (.C(IPCORE_CLK),
        .CE(write_axi_enable),
        .D(\delayout[16]_i_1_n_0 ),
        .Q(Q[16]),
        .R(RSTP));
  FDRE \delayout_reg[17] 
       (.C(IPCORE_CLK),
        .CE(write_axi_enable),
        .D(\delayout[17]_i_1_n_0 ),
        .Q(Q[17]),
        .R(RSTP));
  FDRE \delayout_reg[18] 
       (.C(IPCORE_CLK),
        .CE(write_axi_enable),
        .D(\delayout[18]_i_1_n_0 ),
        .Q(Q[18]),
        .R(RSTP));
  FDRE \delayout_reg[19] 
       (.C(IPCORE_CLK),
        .CE(write_axi_enable),
        .D(\delayout[19]_i_1_n_0 ),
        .Q(Q[19]),
        .R(RSTP));
  FDRE \delayout_reg[1] 
       (.C(IPCORE_CLK),
        .CE(write_axi_enable),
        .D(\delayout[1]_i_1_n_0 ),
        .Q(Q[1]),
        .R(RSTP));
  FDRE \delayout_reg[20] 
       (.C(IPCORE_CLK),
        .CE(write_axi_enable),
        .D(\delayout[20]_i_1_n_0 ),
        .Q(Q[20]),
        .R(RSTP));
  FDRE \delayout_reg[21] 
       (.C(IPCORE_CLK),
        .CE(write_axi_enable),
        .D(\delayout[21]_i_1_n_0 ),
        .Q(Q[21]),
        .R(RSTP));
  FDRE \delayout_reg[22] 
       (.C(IPCORE_CLK),
        .CE(write_axi_enable),
        .D(\delayout[22]_i_1_n_0 ),
        .Q(Q[22]),
        .R(RSTP));
  FDRE \delayout_reg[23] 
       (.C(IPCORE_CLK),
        .CE(write_axi_enable),
        .D(\delayout[23]_i_1_n_0 ),
        .Q(Q[23]),
        .R(RSTP));
  FDRE \delayout_reg[24] 
       (.C(IPCORE_CLK),
        .CE(write_axi_enable),
        .D(\delayout[24]_i_1_n_0 ),
        .Q(Q[24]),
        .R(RSTP));
  FDRE \delayout_reg[25] 
       (.C(IPCORE_CLK),
        .CE(write_axi_enable),
        .D(\delayout[25]_i_1_n_0 ),
        .Q(Q[25]),
        .R(RSTP));
  FDRE \delayout_reg[26] 
       (.C(IPCORE_CLK),
        .CE(write_axi_enable),
        .D(\delayout[26]_i_1_n_0 ),
        .Q(Q[26]),
        .R(RSTP));
  FDRE \delayout_reg[27] 
       (.C(IPCORE_CLK),
        .CE(write_axi_enable),
        .D(\delayout[27]_i_1_n_0 ),
        .Q(Q[27]),
        .R(RSTP));
  FDRE \delayout_reg[28] 
       (.C(IPCORE_CLK),
        .CE(write_axi_enable),
        .D(\delayout[28]_i_1_n_0 ),
        .Q(Q[28]),
        .R(RSTP));
  FDRE \delayout_reg[29] 
       (.C(IPCORE_CLK),
        .CE(write_axi_enable),
        .D(\delayout[29]_i_1_n_0 ),
        .Q(Q[29]),
        .R(RSTP));
  FDRE \delayout_reg[2] 
       (.C(IPCORE_CLK),
        .CE(write_axi_enable),
        .D(\delayout[2]_i_1_n_0 ),
        .Q(Q[2]),
        .R(RSTP));
  FDRE \delayout_reg[30] 
       (.C(IPCORE_CLK),
        .CE(write_axi_enable),
        .D(\delayout[30]_i_1_n_0 ),
        .Q(Q[30]),
        .R(RSTP));
  FDRE \delayout_reg[31] 
       (.C(IPCORE_CLK),
        .CE(write_axi_enable),
        .D(\delayout[31]_i_1_n_0 ),
        .Q(Q[31]),
        .R(RSTP));
  FDRE \delayout_reg[3] 
       (.C(IPCORE_CLK),
        .CE(write_axi_enable),
        .D(\delayout[3]_i_1_n_0 ),
        .Q(Q[3]),
        .R(RSTP));
  FDRE \delayout_reg[4] 
       (.C(IPCORE_CLK),
        .CE(write_axi_enable),
        .D(\delayout[4]_i_1_n_0 ),
        .Q(Q[4]),
        .R(RSTP));
  FDRE \delayout_reg[5] 
       (.C(IPCORE_CLK),
        .CE(write_axi_enable),
        .D(\delayout[5]_i_1_n_0 ),
        .Q(Q[5]),
        .R(RSTP));
  FDRE \delayout_reg[6] 
       (.C(IPCORE_CLK),
        .CE(write_axi_enable),
        .D(\delayout[6]_i_1_n_0 ),
        .Q(Q[6]),
        .R(RSTP));
  FDRE \delayout_reg[7] 
       (.C(IPCORE_CLK),
        .CE(write_axi_enable),
        .D(\delayout[7]_i_1_n_0 ),
        .Q(Q[7]),
        .R(RSTP));
  FDRE \delayout_reg[8] 
       (.C(IPCORE_CLK),
        .CE(write_axi_enable),
        .D(\delayout[8]_i_1_n_0 ),
        .Q(Q[8]),
        .R(RSTP));
  FDRE \delayout_reg[9] 
       (.C(IPCORE_CLK),
        .CE(write_axi_enable),
        .D(\delayout[9]_i_1_n_0 ),
        .Q(Q[9]),
        .R(RSTP));
  (* KEEP_HIERARCHY = "yes" *) 
  (* METHODOLOGY_DRC_VIOS = "{SYNTH-10 {cell *THIS*} {string 16x18 4}}" *) 
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
    .CREG(1),
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
    mul1_mul_temp
       (.A({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,mul1_mul_temp_i_1_n_0,mul1_mul_temp_i_2_n_0,mul1_mul_temp_i_3_n_0,mul1_mul_temp_i_4_n_0,mul1_mul_temp_i_5_n_0,mul1_mul_temp_i_6_n_0,mul1_mul_temp_i_7_n_0,mul1_mul_temp_i_8_n_0,mul1_mul_temp_i_9_n_0,mul1_mul_temp_i_10_n_0,mul1_mul_temp_i_11_n_0,mul1_mul_temp_i_12_n_0,mul1_mul_temp_i_13_n_0,mul1_mul_temp_i_14_n_0,mul1_mul_temp_i_15_n_0,mul1_mul_temp_i_16_n_0,mul1_mul_temp_i_17_n_0}),
        .ACIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .ACOUT(NLW_mul1_mul_temp_ACOUT_UNCONNECTED[29:0]),
        .ALUMODE({1'b0,1'b0,1'b0,1'b0}),
        .B({1'b0,1'b0,1'b0,DSP_ALU_INST[31:17]}),
        .BCIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .BCOUT(NLW_mul1_mul_temp_BCOUT_UNCONNECTED[17:0]),
        .C({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .CARRYCASCIN(1'b0),
        .CARRYCASCOUT(NLW_mul1_mul_temp_CARRYCASCOUT_UNCONNECTED),
        .CARRYIN(1'b0),
        .CARRYINSEL({1'b0,1'b0,1'b0}),
        .CARRYOUT(NLW_mul1_mul_temp_CARRYOUT_UNCONNECTED[3:0]),
        .CEA1(1'b0),
        .CEA2(1'b0),
        .CEAD(1'b0),
        .CEALUMODE(1'b0),
        .CEB1(1'b0),
        .CEB2(CEP),
        .CEC(1'b0),
        .CECARRYIN(1'b0),
        .CECTRL(1'b0),
        .CED(1'b0),
        .CEINMODE(1'b0),
        .CEM(1'b0),
        .CEP(1'b0),
        .CLK(IPCORE_CLK),
        .D({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .INMODE({1'b0,1'b0,1'b0,1'b0,1'b0}),
        .MULTSIGNIN(1'b0),
        .MULTSIGNOUT(NLW_mul1_mul_temp_MULTSIGNOUT_UNCONNECTED),
        .OPMODE({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b1,1'b0,1'b1}),
        .OVERFLOW(NLW_mul1_mul_temp_OVERFLOW_UNCONNECTED),
        .P({mul1_mul_temp_n_58,mul1_mul_temp_n_59,mul1_mul_temp_n_60,mul1_mul_temp_n_61,mul1_mul_temp_n_62,mul1_mul_temp_n_63,mul1_mul_temp_n_64,mul1_mul_temp_n_65,mul1_mul_temp_n_66,mul1_mul_temp_n_67,mul1_mul_temp_n_68,mul1_mul_temp_n_69,mul1_mul_temp_n_70,mul1_mul_temp_n_71,mul1_mul_temp_n_72,mul1_mul_temp_n_73,mul1_mul_temp_n_74,mul1_mul_temp_n_75,mul1_mul_temp_n_76,mul1_mul_temp_n_77,mul1_mul_temp_n_78,mul1_mul_temp_n_79,mul1_mul_temp_n_80,mul1_mul_temp_n_81,mul1_mul_temp_n_82,mul1_mul_temp_n_83,mul1_mul_temp_n_84,mul1_mul_temp_n_85,mul1_mul_temp_n_86,mul1_mul_temp_n_87,mul1_mul_temp_n_88,mul1_mul_temp_n_89,mul1_mul_temp_n_90,mul1_mul_temp_n_91,mul1_mul_temp_n_92,mul1_mul_temp_n_93,mul1_mul_temp_n_94,mul1_mul_temp_n_95,mul1_mul_temp_n_96,mul1_mul_temp_n_97,mul1_mul_temp_n_98,mul1_mul_temp_n_99,mul1_mul_temp_n_100,mul1_mul_temp_n_101,mul1_mul_temp_n_102,mul1_mul_temp_n_103,mul1_mul_temp_n_104,mul1_mul_temp_n_105}),
        .PATTERNBDETECT(NLW_mul1_mul_temp_PATTERNBDETECT_UNCONNECTED),
        .PATTERNDETECT(NLW_mul1_mul_temp_PATTERNDETECT_UNCONNECTED),
        .PCIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .PCOUT({mul1_mul_temp_n_106,mul1_mul_temp_n_107,mul1_mul_temp_n_108,mul1_mul_temp_n_109,mul1_mul_temp_n_110,mul1_mul_temp_n_111,mul1_mul_temp_n_112,mul1_mul_temp_n_113,mul1_mul_temp_n_114,mul1_mul_temp_n_115,mul1_mul_temp_n_116,mul1_mul_temp_n_117,mul1_mul_temp_n_118,mul1_mul_temp_n_119,mul1_mul_temp_n_120,mul1_mul_temp_n_121,mul1_mul_temp_n_122,mul1_mul_temp_n_123,mul1_mul_temp_n_124,mul1_mul_temp_n_125,mul1_mul_temp_n_126,mul1_mul_temp_n_127,mul1_mul_temp_n_128,mul1_mul_temp_n_129,mul1_mul_temp_n_130,mul1_mul_temp_n_131,mul1_mul_temp_n_132,mul1_mul_temp_n_133,mul1_mul_temp_n_134,mul1_mul_temp_n_135,mul1_mul_temp_n_136,mul1_mul_temp_n_137,mul1_mul_temp_n_138,mul1_mul_temp_n_139,mul1_mul_temp_n_140,mul1_mul_temp_n_141,mul1_mul_temp_n_142,mul1_mul_temp_n_143,mul1_mul_temp_n_144,mul1_mul_temp_n_145,mul1_mul_temp_n_146,mul1_mul_temp_n_147,mul1_mul_temp_n_148,mul1_mul_temp_n_149,mul1_mul_temp_n_150,mul1_mul_temp_n_151,mul1_mul_temp_n_152,mul1_mul_temp_n_153}),
        .RSTA(1'b0),
        .RSTALLCARRYIN(1'b0),
        .RSTALUMODE(1'b0),
        .RSTB(RSTP),
        .RSTC(1'b0),
        .RSTCTRL(1'b0),
        .RSTD(1'b0),
        .RSTINMODE(1'b0),
        .RSTM(1'b0),
        .RSTP(1'b0),
        .UNDERFLOW(NLW_mul1_mul_temp_UNDERFLOW_UNCONNECTED),
        .XOROUT(NLW_mul1_mul_temp_XOROUT_UNCONNECTED[7:0]));
  (* KEEP_HIERARCHY = "yes" *) 
  (* METHODOLOGY_DRC_VIOS = "{SYNTH-10 {cell *THIS*} {string 16x16 4}}" *) 
  DSP48E2 #(
    .ACASCREG(1),
    .ADREG(1),
    .ALUMODEREG(0),
    .AMULTSEL("A"),
    .AREG(1),
    .AUTORESET_PATDET("NO_RESET"),
    .AUTORESET_PRIORITY("RESET"),
    .A_INPUT("DIRECT"),
    .BCASCREG(0),
    .BMULTSEL("B"),
    .BREG(0),
    .B_INPUT("DIRECT"),
    .CARRYINREG(0),
    .CARRYINSELREG(0),
    .CREG(1),
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
    mul1_mul_temp__0
       (.A({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,DSP_ALU_INST[31:17]}),
        .ACIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .ACOUT(NLW_mul1_mul_temp__0_ACOUT_UNCONNECTED[29:0]),
        .ALUMODE({1'b0,1'b0,1'b0,1'b0}),
        .B({1'b0,1'b0,1'b0,mul1_mul_temp__0_i_1_n_0,mul1_mul_temp__0_i_2_n_0,mul1_mul_temp__0_i_3_n_0,mul1_mul_temp__0_i_4_n_0,mul1_mul_temp__0_i_5_n_0,mul1_mul_temp__0_i_6_n_0,mul1_mul_temp__0_i_7_n_0,mul1_mul_temp__0_i_8_n_0,mul1_mul_temp__0_i_9_n_0,mul1_mul_temp__0_i_10_n_0,mul1_mul_temp__0_i_11_n_0,mul1_mul_temp__0_i_12_n_0,mul1_mul_temp__0_i_13_n_0,mul1_mul_temp__0_i_14_n_0,mul1_mul_temp__0_i_15_n_0}),
        .BCIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .BCOUT(NLW_mul1_mul_temp__0_BCOUT_UNCONNECTED[17:0]),
        .C({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .CARRYCASCIN(1'b0),
        .CARRYCASCOUT(NLW_mul1_mul_temp__0_CARRYCASCOUT_UNCONNECTED),
        .CARRYIN(1'b0),
        .CARRYINSEL({1'b0,1'b0,1'b0}),
        .CARRYOUT(NLW_mul1_mul_temp__0_CARRYOUT_UNCONNECTED[3:0]),
        .CEA1(1'b0),
        .CEA2(CEP),
        .CEAD(1'b0),
        .CEALUMODE(1'b0),
        .CEB1(1'b0),
        .CEB2(1'b0),
        .CEC(1'b0),
        .CECARRYIN(1'b0),
        .CECTRL(1'b0),
        .CED(1'b0),
        .CEINMODE(1'b0),
        .CEM(1'b0),
        .CEP(1'b0),
        .CLK(IPCORE_CLK),
        .D({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .INMODE({1'b0,1'b0,1'b0,1'b0,1'b0}),
        .MULTSIGNIN(1'b0),
        .MULTSIGNOUT(NLW_mul1_mul_temp__0_MULTSIGNOUT_UNCONNECTED),
        .OPMODE({1'b0,1'b0,1'b1,1'b0,1'b1,1'b0,1'b1,1'b0,1'b1}),
        .OVERFLOW(NLW_mul1_mul_temp__0_OVERFLOW_UNCONNECTED),
        .P({NLW_mul1_mul_temp__0_P_UNCONNECTED[47:30],mul1_mul_temp__0_n_76,mul1_mul_temp__0_n_77,mul1_mul_temp__0_n_78,mul1_mul_temp__0_n_79,mul1_mul_temp__0_n_80,mul1_mul_temp__0_n_81,mul1_mul_temp__0_n_82,mul1_mul_temp__0_n_83,mul1_mul_temp__0_n_84,mul1_mul_temp__0_n_85,mul1_mul_temp__0_n_86,mul1_mul_temp__0_n_87,mul1_mul_temp__0_n_88,mul1_mul_temp__0_n_89,mul1_mul_temp__0_n_90,mul1_mul_temp__0_n_91,mul1_mul_temp__0_n_92,mul1_mul_temp__0_n_93,mul1_mul_temp__0_n_94,mul1_mul_temp__0_n_95,mul1_mul_temp__0_n_96,mul1_mul_temp__0_n_97,mul1_mul_temp__0_n_98,mul1_mul_temp__0_n_99,mul1_mul_temp__0_n_100,mul1_mul_temp__0_n_101,mul1_mul_temp__0_n_102,mul1_mul_temp__0_n_103,mul1_mul_temp__0_n_104,mul1_mul_temp__0_n_105}),
        .PATTERNBDETECT(NLW_mul1_mul_temp__0_PATTERNBDETECT_UNCONNECTED),
        .PATTERNDETECT(NLW_mul1_mul_temp__0_PATTERNDETECT_UNCONNECTED),
        .PCIN({mul1_mul_temp_n_106,mul1_mul_temp_n_107,mul1_mul_temp_n_108,mul1_mul_temp_n_109,mul1_mul_temp_n_110,mul1_mul_temp_n_111,mul1_mul_temp_n_112,mul1_mul_temp_n_113,mul1_mul_temp_n_114,mul1_mul_temp_n_115,mul1_mul_temp_n_116,mul1_mul_temp_n_117,mul1_mul_temp_n_118,mul1_mul_temp_n_119,mul1_mul_temp_n_120,mul1_mul_temp_n_121,mul1_mul_temp_n_122,mul1_mul_temp_n_123,mul1_mul_temp_n_124,mul1_mul_temp_n_125,mul1_mul_temp_n_126,mul1_mul_temp_n_127,mul1_mul_temp_n_128,mul1_mul_temp_n_129,mul1_mul_temp_n_130,mul1_mul_temp_n_131,mul1_mul_temp_n_132,mul1_mul_temp_n_133,mul1_mul_temp_n_134,mul1_mul_temp_n_135,mul1_mul_temp_n_136,mul1_mul_temp_n_137,mul1_mul_temp_n_138,mul1_mul_temp_n_139,mul1_mul_temp_n_140,mul1_mul_temp_n_141,mul1_mul_temp_n_142,mul1_mul_temp_n_143,mul1_mul_temp_n_144,mul1_mul_temp_n_145,mul1_mul_temp_n_146,mul1_mul_temp_n_147,mul1_mul_temp_n_148,mul1_mul_temp_n_149,mul1_mul_temp_n_150,mul1_mul_temp_n_151,mul1_mul_temp_n_152,mul1_mul_temp_n_153}),
        .PCOUT(NLW_mul1_mul_temp__0_PCOUT_UNCONNECTED[47:0]),
        .RSTA(RSTP),
        .RSTALLCARRYIN(1'b0),
        .RSTALUMODE(1'b0),
        .RSTB(1'b0),
        .RSTC(1'b0),
        .RSTCTRL(1'b0),
        .RSTD(1'b0),
        .RSTINMODE(1'b0),
        .RSTM(1'b0),
        .RSTP(1'b0),
        .UNDERFLOW(NLW_mul1_mul_temp__0_UNDERFLOW_UNCONNECTED),
        .XOROUT(NLW_mul1_mul_temp__0_XOROUT_UNCONNECTED[7:0]));
  (* SOFT_HLUTNM = "soft_lutpair50" *) 
  LUT3 #(
    .INIT(8'hA2)) 
    mul1_mul_temp__0_i_1
       (.I0(sel),
        .I1(subtractor_sub_temp_carry__2_n_0),
        .I2(subtractor_sub_temp_carry__2_n_9),
        .O(mul1_mul_temp__0_i_1_n_0));
  LUT4 #(
    .INIT(16'hBFB0)) 
    mul1_mul_temp__0_i_10
       (.I0(subtractor_sub_temp_carry__1_n_10),
        .I1(subtractor_sub_temp_carry__2_n_0),
        .I2(sel),
        .I3(DSP_A_B_DATA_INST[22]),
        .O(mul1_mul_temp__0_i_10_n_0));
  LUT4 #(
    .INIT(16'hBFB0)) 
    mul1_mul_temp__0_i_11
       (.I0(subtractor_sub_temp_carry__1_n_11),
        .I1(subtractor_sub_temp_carry__2_n_0),
        .I2(sel),
        .I3(DSP_A_B_DATA_INST[21]),
        .O(mul1_mul_temp__0_i_11_n_0));
  LUT4 #(
    .INIT(16'hBFB0)) 
    mul1_mul_temp__0_i_12
       (.I0(subtractor_sub_temp_carry__1_n_12),
        .I1(subtractor_sub_temp_carry__2_n_0),
        .I2(sel),
        .I3(DSP_A_B_DATA_INST[20]),
        .O(mul1_mul_temp__0_i_12_n_0));
  LUT4 #(
    .INIT(16'hBFB0)) 
    mul1_mul_temp__0_i_13
       (.I0(subtractor_sub_temp_carry__1_n_13),
        .I1(subtractor_sub_temp_carry__2_n_0),
        .I2(sel),
        .I3(DSP_A_B_DATA_INST[19]),
        .O(mul1_mul_temp__0_i_13_n_0));
  LUT4 #(
    .INIT(16'hBFB0)) 
    mul1_mul_temp__0_i_14
       (.I0(subtractor_sub_temp_carry__1_n_14),
        .I1(subtractor_sub_temp_carry__2_n_0),
        .I2(sel),
        .I3(DSP_A_B_DATA_INST[18]),
        .O(mul1_mul_temp__0_i_14_n_0));
  LUT4 #(
    .INIT(16'hBFB0)) 
    mul1_mul_temp__0_i_15
       (.I0(subtractor_sub_temp_carry__1_n_15),
        .I1(subtractor_sub_temp_carry__2_n_0),
        .I2(sel),
        .I3(DSP_A_B_DATA_INST[17]),
        .O(mul1_mul_temp__0_i_15_n_0));
  (* SOFT_HLUTNM = "soft_lutpair49" *) 
  LUT3 #(
    .INIT(8'hA2)) 
    mul1_mul_temp__0_i_2
       (.I0(sel),
        .I1(subtractor_sub_temp_carry__2_n_0),
        .I2(subtractor_sub_temp_carry__2_n_10),
        .O(mul1_mul_temp__0_i_2_n_0));
  LUT4 #(
    .INIT(16'hBFB0)) 
    mul1_mul_temp__0_i_3
       (.I0(subtractor_sub_temp_carry__2_n_11),
        .I1(subtractor_sub_temp_carry__2_n_0),
        .I2(sel),
        .I3(DSP_A_B_DATA_INST[29]),
        .O(mul1_mul_temp__0_i_3_n_0));
  LUT4 #(
    .INIT(16'hBFB0)) 
    mul1_mul_temp__0_i_4
       (.I0(subtractor_sub_temp_carry__2_n_12),
        .I1(subtractor_sub_temp_carry__2_n_0),
        .I2(sel),
        .I3(DSP_A_B_DATA_INST[28]),
        .O(mul1_mul_temp__0_i_4_n_0));
  LUT4 #(
    .INIT(16'hBFB0)) 
    mul1_mul_temp__0_i_5
       (.I0(subtractor_sub_temp_carry__2_n_13),
        .I1(subtractor_sub_temp_carry__2_n_0),
        .I2(sel),
        .I3(DSP_A_B_DATA_INST[27]),
        .O(mul1_mul_temp__0_i_5_n_0));
  LUT4 #(
    .INIT(16'hBFB0)) 
    mul1_mul_temp__0_i_6
       (.I0(subtractor_sub_temp_carry__2_n_14),
        .I1(subtractor_sub_temp_carry__2_n_0),
        .I2(sel),
        .I3(DSP_A_B_DATA_INST[26]),
        .O(mul1_mul_temp__0_i_6_n_0));
  LUT4 #(
    .INIT(16'hBFB0)) 
    mul1_mul_temp__0_i_7
       (.I0(subtractor_sub_temp_carry__2_n_15),
        .I1(subtractor_sub_temp_carry__2_n_0),
        .I2(sel),
        .I3(DSP_A_B_DATA_INST[25]),
        .O(mul1_mul_temp__0_i_7_n_0));
  LUT4 #(
    .INIT(16'hBFB0)) 
    mul1_mul_temp__0_i_8
       (.I0(subtractor_sub_temp_carry__1_n_8),
        .I1(subtractor_sub_temp_carry__2_n_0),
        .I2(sel),
        .I3(DSP_A_B_DATA_INST[24]),
        .O(mul1_mul_temp__0_i_8_n_0));
  LUT4 #(
    .INIT(16'hBFB0)) 
    mul1_mul_temp__0_i_9
       (.I0(subtractor_sub_temp_carry__1_n_9),
        .I1(subtractor_sub_temp_carry__2_n_0),
        .I2(sel),
        .I3(DSP_A_B_DATA_INST[23]),
        .O(mul1_mul_temp__0_i_9_n_0));
  (* KEEP_HIERARCHY = "yes" *) 
  (* METHODOLOGY_DRC_VIOS = "{SYNTH-10 {cell *THIS*} {string 18x18 4}}" *) 
  DSP48E2 #(
    .ACASCREG(1),
    .ADREG(1),
    .ALUMODEREG(0),
    .AMULTSEL("A"),
    .AREG(1),
    .AUTORESET_PATDET("NO_RESET"),
    .AUTORESET_PRIORITY("RESET"),
    .A_INPUT("DIRECT"),
    .BCASCREG(0),
    .BMULTSEL("B"),
    .BREG(0),
    .B_INPUT("DIRECT"),
    .CARRYINREG(0),
    .CARRYINSELREG(0),
    .CREG(1),
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
    mul1_mul_temp__1
       (.A({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,DSP_ALU_INST[16:0]}),
        .ACIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .ACOUT(NLW_mul1_mul_temp__1_ACOUT_UNCONNECTED[29:0]),
        .ALUMODE({1'b0,1'b0,1'b0,1'b0}),
        .B({1'b0,mul1_mul_temp_i_1_n_0,mul1_mul_temp_i_2_n_0,mul1_mul_temp_i_3_n_0,mul1_mul_temp_i_4_n_0,mul1_mul_temp_i_5_n_0,mul1_mul_temp_i_6_n_0,mul1_mul_temp_i_7_n_0,mul1_mul_temp_i_8_n_0,mul1_mul_temp_i_9_n_0,mul1_mul_temp_i_10_n_0,mul1_mul_temp_i_11_n_0,mul1_mul_temp_i_12_n_0,mul1_mul_temp_i_13_n_0,mul1_mul_temp_i_14_n_0,mul1_mul_temp_i_15_n_0,mul1_mul_temp_i_16_n_0,mul1_mul_temp_i_17_n_0}),
        .BCIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .BCOUT(NLW_mul1_mul_temp__1_BCOUT_UNCONNECTED[17:0]),
        .C({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .CARRYCASCIN(1'b0),
        .CARRYCASCOUT(NLW_mul1_mul_temp__1_CARRYCASCOUT_UNCONNECTED),
        .CARRYIN(1'b0),
        .CARRYINSEL({1'b0,1'b0,1'b0}),
        .CARRYOUT(NLW_mul1_mul_temp__1_CARRYOUT_UNCONNECTED[3:0]),
        .CEA1(1'b0),
        .CEA2(CEP),
        .CEAD(1'b0),
        .CEALUMODE(1'b0),
        .CEB1(1'b0),
        .CEB2(1'b0),
        .CEC(1'b0),
        .CECARRYIN(1'b0),
        .CECTRL(1'b0),
        .CED(1'b0),
        .CEINMODE(1'b0),
        .CEM(1'b0),
        .CEP(1'b0),
        .CLK(IPCORE_CLK),
        .D({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .INMODE({1'b0,1'b0,1'b0,1'b0,1'b0}),
        .MULTSIGNIN(1'b0),
        .MULTSIGNOUT(NLW_mul1_mul_temp__1_MULTSIGNOUT_UNCONNECTED),
        .OPMODE({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b1,1'b0,1'b1}),
        .OVERFLOW(NLW_mul1_mul_temp__1_OVERFLOW_UNCONNECTED),
        .P({mul1_mul_temp__1_n_58,mul1_mul_temp__1_n_59,mul1_mul_temp__1_n_60,mul1_mul_temp__1_n_61,mul1_mul_temp__1_n_62,mul1_mul_temp__1_n_63,mul1_mul_temp__1_n_64,mul1_mul_temp__1_n_65,mul1_mul_temp__1_n_66,mul1_mul_temp__1_n_67,mul1_mul_temp__1_n_68,mul1_mul_temp__1_n_69,mul1_mul_temp__1_n_70,mul1_mul_temp__1_n_71,mul1_mul_temp__1_n_72,mul1_mul_temp__1_n_73,mul1_mul_temp__1_n_74,mul1_mul_temp__1_n_75,mul1_mul_temp__1_n_76,mul1_mul_temp__1_n_77,mul1_mul_temp__1_n_78,mul1_mul_temp__1_n_79,mul1_mul_temp__1_n_80,mul1_mul_temp__1_n_81,mul1_mul_temp__1_n_82,mul1_mul_temp__1_n_83,mul1_mul_temp__1_n_84,mul1_mul_temp__1_n_85,mul1_mul_temp__1_n_86,mul1_mul_temp__1_n_87,mul1_mul_temp__1_n_88,mul1_mul_temp__1_n_89,mul1_mul_temp__1_n_90,mul1_mul_temp__1_n_91,mul1_mul_temp__1_n_92,mul1_mul_temp__1_n_93,mul1_mul_temp__1_n_94,mul1_mul_temp__1_n_95,mul1_mul_temp__1_n_96,mul1_mul_temp__1_n_97,mul1_mul_temp__1_n_98,mul1_mul_temp__1_n_99,mul1_mul_temp__1_n_100,mul1_mul_temp__1_n_101,mul1_mul_temp__1_n_102,mul1_mul_temp__1_n_103,mul1_mul_temp__1_n_104,mul1_mul_temp__1_n_105}),
        .PATTERNBDETECT(NLW_mul1_mul_temp__1_PATTERNBDETECT_UNCONNECTED),
        .PATTERNDETECT(NLW_mul1_mul_temp__1_PATTERNDETECT_UNCONNECTED),
        .PCIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .PCOUT({mul1_mul_temp__1_n_106,mul1_mul_temp__1_n_107,mul1_mul_temp__1_n_108,mul1_mul_temp__1_n_109,mul1_mul_temp__1_n_110,mul1_mul_temp__1_n_111,mul1_mul_temp__1_n_112,mul1_mul_temp__1_n_113,mul1_mul_temp__1_n_114,mul1_mul_temp__1_n_115,mul1_mul_temp__1_n_116,mul1_mul_temp__1_n_117,mul1_mul_temp__1_n_118,mul1_mul_temp__1_n_119,mul1_mul_temp__1_n_120,mul1_mul_temp__1_n_121,mul1_mul_temp__1_n_122,mul1_mul_temp__1_n_123,mul1_mul_temp__1_n_124,mul1_mul_temp__1_n_125,mul1_mul_temp__1_n_126,mul1_mul_temp__1_n_127,mul1_mul_temp__1_n_128,mul1_mul_temp__1_n_129,mul1_mul_temp__1_n_130,mul1_mul_temp__1_n_131,mul1_mul_temp__1_n_132,mul1_mul_temp__1_n_133,mul1_mul_temp__1_n_134,mul1_mul_temp__1_n_135,mul1_mul_temp__1_n_136,mul1_mul_temp__1_n_137,mul1_mul_temp__1_n_138,mul1_mul_temp__1_n_139,mul1_mul_temp__1_n_140,mul1_mul_temp__1_n_141,mul1_mul_temp__1_n_142,mul1_mul_temp__1_n_143,mul1_mul_temp__1_n_144,mul1_mul_temp__1_n_145,mul1_mul_temp__1_n_146,mul1_mul_temp__1_n_147,mul1_mul_temp__1_n_148,mul1_mul_temp__1_n_149,mul1_mul_temp__1_n_150,mul1_mul_temp__1_n_151,mul1_mul_temp__1_n_152,mul1_mul_temp__1_n_153}),
        .RSTA(RSTP),
        .RSTALLCARRYIN(1'b0),
        .RSTALUMODE(1'b0),
        .RSTB(1'b0),
        .RSTC(1'b0),
        .RSTCTRL(1'b0),
        .RSTD(1'b0),
        .RSTINMODE(1'b0),
        .RSTM(1'b0),
        .RSTP(1'b0),
        .UNDERFLOW(NLW_mul1_mul_temp__1_UNDERFLOW_UNCONNECTED),
        .XOROUT(NLW_mul1_mul_temp__1_XOROUT_UNCONNECTED[7:0]));
  (* KEEP_HIERARCHY = "yes" *) 
  (* METHODOLOGY_DRC_VIOS = "{SYNTH-10 {cell *THIS*} {string 18x16 4}}" *) 
  DSP48E2 #(
    .ACASCREG(1),
    .ADREG(1),
    .ALUMODEREG(0),
    .AMULTSEL("A"),
    .AREG(1),
    .AUTORESET_PATDET("NO_RESET"),
    .AUTORESET_PRIORITY("RESET"),
    .A_INPUT("DIRECT"),
    .BCASCREG(0),
    .BMULTSEL("B"),
    .BREG(0),
    .B_INPUT("DIRECT"),
    .CARRYINREG(0),
    .CARRYINSELREG(0),
    .CREG(1),
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
    mul1_mul_temp__2
       (.A({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,DSP_ALU_INST[16:0]}),
        .ACIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .ACOUT(NLW_mul1_mul_temp__2_ACOUT_UNCONNECTED[29:0]),
        .ALUMODE({1'b0,1'b0,1'b0,1'b0}),
        .B({1'b0,1'b0,1'b0,mul1_mul_temp__0_i_1_n_0,mul1_mul_temp__0_i_2_n_0,mul1_mul_temp__0_i_3_n_0,mul1_mul_temp__0_i_4_n_0,mul1_mul_temp__0_i_5_n_0,mul1_mul_temp__0_i_6_n_0,mul1_mul_temp__0_i_7_n_0,mul1_mul_temp__0_i_8_n_0,mul1_mul_temp__0_i_9_n_0,mul1_mul_temp__0_i_10_n_0,mul1_mul_temp__0_i_11_n_0,mul1_mul_temp__0_i_12_n_0,mul1_mul_temp__0_i_13_n_0,mul1_mul_temp__0_i_14_n_0,mul1_mul_temp__0_i_15_n_0}),
        .BCIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .BCOUT(NLW_mul1_mul_temp__2_BCOUT_UNCONNECTED[17:0]),
        .C({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .CARRYCASCIN(1'b0),
        .CARRYCASCOUT(NLW_mul1_mul_temp__2_CARRYCASCOUT_UNCONNECTED),
        .CARRYIN(1'b0),
        .CARRYINSEL({1'b0,1'b0,1'b0}),
        .CARRYOUT(NLW_mul1_mul_temp__2_CARRYOUT_UNCONNECTED[3:0]),
        .CEA1(1'b0),
        .CEA2(CEP),
        .CEAD(1'b0),
        .CEALUMODE(1'b0),
        .CEB1(1'b0),
        .CEB2(1'b0),
        .CEC(1'b0),
        .CECARRYIN(1'b0),
        .CECTRL(1'b0),
        .CED(1'b0),
        .CEINMODE(1'b0),
        .CEM(1'b0),
        .CEP(1'b0),
        .CLK(IPCORE_CLK),
        .D({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .INMODE({1'b0,1'b0,1'b0,1'b0,1'b0}),
        .MULTSIGNIN(1'b0),
        .MULTSIGNOUT(NLW_mul1_mul_temp__2_MULTSIGNOUT_UNCONNECTED),
        .OPMODE({1'b0,1'b0,1'b1,1'b0,1'b1,1'b0,1'b1,1'b0,1'b1}),
        .OVERFLOW(NLW_mul1_mul_temp__2_OVERFLOW_UNCONNECTED),
        .P({NLW_mul1_mul_temp__2_P_UNCONNECTED[47],mul1_mul_temp__2_n_59,mul1_mul_temp__2_n_60,mul1_mul_temp__2_n_61,mul1_mul_temp__2_n_62,mul1_mul_temp__2_n_63,mul1_mul_temp__2_n_64,mul1_mul_temp__2_n_65,mul1_mul_temp__2_n_66,mul1_mul_temp__2_n_67,mul1_mul_temp__2_n_68,mul1_mul_temp__2_n_69,mul1_mul_temp__2_n_70,mul1_mul_temp__2_n_71,mul1_mul_temp__2_n_72,mul1_mul_temp__2_n_73,mul1_mul_temp__2_n_74,mul1_mul_temp__2_n_75,mul1_mul_temp__2_n_76,mul1_mul_temp__2_n_77,mul1_mul_temp__2_n_78,mul1_mul_temp__2_n_79,mul1_mul_temp__2_n_80,mul1_mul_temp__2_n_81,mul1_mul_temp__2_n_82,mul1_mul_temp__2_n_83,mul1_mul_temp__2_n_84,mul1_mul_temp__2_n_85,mul1_mul_temp__2_n_86,mul1_mul_temp__2_n_87,mul1_mul_temp__2_n_88,mul1_mul_temp__2_n_89,mul1_mul_temp__2_n_90,mul1_mul_temp__2_n_91,mul1_mul_temp__2_n_92,mul1_mul_temp__2_n_93,mul1_mul_temp__2_n_94,mul1_mul_temp__2_n_95,mul1_mul_temp__2_n_96,mul1_mul_temp__2_n_97,mul1_mul_temp__2_n_98,mul1_mul_temp__2_n_99,mul1_mul_temp__2_n_100,mul1_mul_temp__2_n_101,mul1_mul_temp__2_n_102,mul1_mul_temp__2_n_103,mul1_mul_temp__2_n_104,mul1_mul_temp__2_n_105}),
        .PATTERNBDETECT(NLW_mul1_mul_temp__2_PATTERNBDETECT_UNCONNECTED),
        .PATTERNDETECT(NLW_mul1_mul_temp__2_PATTERNDETECT_UNCONNECTED),
        .PCIN({mul1_mul_temp__1_n_106,mul1_mul_temp__1_n_107,mul1_mul_temp__1_n_108,mul1_mul_temp__1_n_109,mul1_mul_temp__1_n_110,mul1_mul_temp__1_n_111,mul1_mul_temp__1_n_112,mul1_mul_temp__1_n_113,mul1_mul_temp__1_n_114,mul1_mul_temp__1_n_115,mul1_mul_temp__1_n_116,mul1_mul_temp__1_n_117,mul1_mul_temp__1_n_118,mul1_mul_temp__1_n_119,mul1_mul_temp__1_n_120,mul1_mul_temp__1_n_121,mul1_mul_temp__1_n_122,mul1_mul_temp__1_n_123,mul1_mul_temp__1_n_124,mul1_mul_temp__1_n_125,mul1_mul_temp__1_n_126,mul1_mul_temp__1_n_127,mul1_mul_temp__1_n_128,mul1_mul_temp__1_n_129,mul1_mul_temp__1_n_130,mul1_mul_temp__1_n_131,mul1_mul_temp__1_n_132,mul1_mul_temp__1_n_133,mul1_mul_temp__1_n_134,mul1_mul_temp__1_n_135,mul1_mul_temp__1_n_136,mul1_mul_temp__1_n_137,mul1_mul_temp__1_n_138,mul1_mul_temp__1_n_139,mul1_mul_temp__1_n_140,mul1_mul_temp__1_n_141,mul1_mul_temp__1_n_142,mul1_mul_temp__1_n_143,mul1_mul_temp__1_n_144,mul1_mul_temp__1_n_145,mul1_mul_temp__1_n_146,mul1_mul_temp__1_n_147,mul1_mul_temp__1_n_148,mul1_mul_temp__1_n_149,mul1_mul_temp__1_n_150,mul1_mul_temp__1_n_151,mul1_mul_temp__1_n_152,mul1_mul_temp__1_n_153}),
        .PCOUT(NLW_mul1_mul_temp__2_PCOUT_UNCONNECTED[47:0]),
        .RSTA(RSTP),
        .RSTALLCARRYIN(1'b0),
        .RSTALUMODE(1'b0),
        .RSTB(1'b0),
        .RSTC(1'b0),
        .RSTCTRL(1'b0),
        .RSTD(1'b0),
        .RSTINMODE(1'b0),
        .RSTM(1'b0),
        .RSTP(1'b0),
        .UNDERFLOW(NLW_mul1_mul_temp__2_UNDERFLOW_UNCONNECTED),
        .XOROUT(NLW_mul1_mul_temp__2_XOROUT_UNCONNECTED[7:0]));
  (* ADDER_THRESHOLD = "35" *) 
  CARRY8 mul1_mul_temp_carry
       (.CI(1'b0),
        .CI_TOP(1'b0),
        .CO({mul1_mul_temp_carry_n_0,mul1_mul_temp_carry_n_1,mul1_mul_temp_carry_n_2,mul1_mul_temp_carry_n_3,mul1_mul_temp_carry_n_4,mul1_mul_temp_carry_n_5,mul1_mul_temp_carry_n_6,mul1_mul_temp_carry_n_7}),
        .DI({mul1_mul_temp__2_n_99,mul1_mul_temp__2_n_100,mul1_mul_temp__2_n_101,mul1_mul_temp__2_n_102,mul1_mul_temp__2_n_103,mul1_mul_temp__2_n_104,mul1_mul_temp__2_n_105,1'b0}),
        .O(NLW_mul1_mul_temp_carry_O_UNCONNECTED[7:0]),
        .S({mul1_mul_temp_carry_i_1__0_n_0,mul1_mul_temp_carry_i_2__0_n_0,mul1_mul_temp_carry_i_3__0_n_0,mul1_mul_temp_carry_i_4__0_n_0,mul1_mul_temp_carry_i_5__0_n_0,mul1_mul_temp_carry_i_6__0_n_0,mul1_mul_temp_carry_i_7__0_n_0,mul1_mul_temp__1_n_89}));
  (* ADDER_THRESHOLD = "35" *) 
  CARRY8 mul1_mul_temp_carry__0
       (.CI(mul1_mul_temp_carry_n_0),
        .CI_TOP(1'b0),
        .CO({mul1_mul_temp_carry__0_n_0,mul1_mul_temp_carry__0_n_1,mul1_mul_temp_carry__0_n_2,mul1_mul_temp_carry__0_n_3,mul1_mul_temp_carry__0_n_4,mul1_mul_temp_carry__0_n_5,mul1_mul_temp_carry__0_n_6,mul1_mul_temp_carry__0_n_7}),
        .DI({mul1_mul_temp__2_n_91,mul1_mul_temp__2_n_92,mul1_mul_temp__2_n_93,mul1_mul_temp__2_n_94,mul1_mul_temp__2_n_95,mul1_mul_temp__2_n_96,mul1_mul_temp__2_n_97,mul1_mul_temp__2_n_98}),
        .O({mul1_mul_temp_carry__0_n_8,mul1_mul_temp_carry__0_n_9,NLW_mul1_mul_temp_carry__0_O_UNCONNECTED[5:0]}),
        .S({mul1_mul_temp_carry__0_i_1__0_n_0,mul1_mul_temp_carry__0_i_2__0_n_0,mul1_mul_temp_carry__0_i_3__0_n_0,mul1_mul_temp_carry__0_i_4__0_n_0,mul1_mul_temp_carry__0_i_5__0_n_0,mul1_mul_temp_carry__0_i_6__0_n_0,mul1_mul_temp_carry__0_i_7__0_n_0,mul1_mul_temp_carry__0_i_8__0_n_0}));
  LUT2 #(
    .INIT(4'h6)) 
    mul1_mul_temp_carry__0_i_1__0
       (.I0(mul1_mul_temp__2_n_91),
        .I1(mul1_mul_temp_n_91),
        .O(mul1_mul_temp_carry__0_i_1__0_n_0));
  LUT2 #(
    .INIT(4'h6)) 
    mul1_mul_temp_carry__0_i_2__0
       (.I0(mul1_mul_temp__2_n_92),
        .I1(mul1_mul_temp_n_92),
        .O(mul1_mul_temp_carry__0_i_2__0_n_0));
  LUT2 #(
    .INIT(4'h6)) 
    mul1_mul_temp_carry__0_i_3__0
       (.I0(mul1_mul_temp__2_n_93),
        .I1(mul1_mul_temp_n_93),
        .O(mul1_mul_temp_carry__0_i_3__0_n_0));
  LUT2 #(
    .INIT(4'h6)) 
    mul1_mul_temp_carry__0_i_4__0
       (.I0(mul1_mul_temp__2_n_94),
        .I1(mul1_mul_temp_n_94),
        .O(mul1_mul_temp_carry__0_i_4__0_n_0));
  LUT2 #(
    .INIT(4'h6)) 
    mul1_mul_temp_carry__0_i_5__0
       (.I0(mul1_mul_temp__2_n_95),
        .I1(mul1_mul_temp_n_95),
        .O(mul1_mul_temp_carry__0_i_5__0_n_0));
  LUT2 #(
    .INIT(4'h6)) 
    mul1_mul_temp_carry__0_i_6__0
       (.I0(mul1_mul_temp__2_n_96),
        .I1(mul1_mul_temp_n_96),
        .O(mul1_mul_temp_carry__0_i_6__0_n_0));
  LUT2 #(
    .INIT(4'h6)) 
    mul1_mul_temp_carry__0_i_7__0
       (.I0(mul1_mul_temp__2_n_97),
        .I1(mul1_mul_temp_n_97),
        .O(mul1_mul_temp_carry__0_i_7__0_n_0));
  LUT2 #(
    .INIT(4'h6)) 
    mul1_mul_temp_carry__0_i_8__0
       (.I0(mul1_mul_temp__2_n_98),
        .I1(mul1_mul_temp_n_98),
        .O(mul1_mul_temp_carry__0_i_8__0_n_0));
  (* ADDER_THRESHOLD = "35" *) 
  CARRY8 mul1_mul_temp_carry__1
       (.CI(mul1_mul_temp_carry__0_n_0),
        .CI_TOP(1'b0),
        .CO({mul1_mul_temp_carry__1_n_0,mul1_mul_temp_carry__1_n_1,mul1_mul_temp_carry__1_n_2,mul1_mul_temp_carry__1_n_3,mul1_mul_temp_carry__1_n_4,mul1_mul_temp_carry__1_n_5,mul1_mul_temp_carry__1_n_6,mul1_mul_temp_carry__1_n_7}),
        .DI({mul1_mul_temp__2_n_83,mul1_mul_temp__2_n_84,mul1_mul_temp__2_n_85,mul1_mul_temp__2_n_86,mul1_mul_temp__2_n_87,mul1_mul_temp__2_n_88,mul1_mul_temp__2_n_89,mul1_mul_temp__2_n_90}),
        .O({mul1_mul_temp_carry__1_n_8,mul1_mul_temp_carry__1_n_9,mul1_mul_temp_carry__1_n_10,mul1_mul_temp_carry__1_n_11,mul1_mul_temp_carry__1_n_12,mul1_mul_temp_carry__1_n_13,mul1_mul_temp_carry__1_n_14,mul1_mul_temp_carry__1_n_15}),
        .S({mul1_mul_temp_carry__1_i_1__0_n_0,mul1_mul_temp_carry__1_i_2__0_n_0,mul1_mul_temp_carry__1_i_3__0_n_0,mul1_mul_temp_carry__1_i_4__0_n_0,mul1_mul_temp_carry__1_i_5__0_n_0,mul1_mul_temp_carry__1_i_6__0_n_0,mul1_mul_temp_carry__1_i_7__0_n_0,mul1_mul_temp_carry__1_i_8__0_n_0}));
  LUT2 #(
    .INIT(4'h6)) 
    mul1_mul_temp_carry__1_i_1__0
       (.I0(mul1_mul_temp__2_n_83),
        .I1(mul1_mul_temp__0_n_100),
        .O(mul1_mul_temp_carry__1_i_1__0_n_0));
  LUT2 #(
    .INIT(4'h6)) 
    mul1_mul_temp_carry__1_i_2__0
       (.I0(mul1_mul_temp__2_n_84),
        .I1(mul1_mul_temp__0_n_101),
        .O(mul1_mul_temp_carry__1_i_2__0_n_0));
  LUT2 #(
    .INIT(4'h6)) 
    mul1_mul_temp_carry__1_i_3__0
       (.I0(mul1_mul_temp__2_n_85),
        .I1(mul1_mul_temp__0_n_102),
        .O(mul1_mul_temp_carry__1_i_3__0_n_0));
  LUT2 #(
    .INIT(4'h6)) 
    mul1_mul_temp_carry__1_i_4__0
       (.I0(mul1_mul_temp__2_n_86),
        .I1(mul1_mul_temp__0_n_103),
        .O(mul1_mul_temp_carry__1_i_4__0_n_0));
  LUT2 #(
    .INIT(4'h6)) 
    mul1_mul_temp_carry__1_i_5__0
       (.I0(mul1_mul_temp__2_n_87),
        .I1(mul1_mul_temp__0_n_104),
        .O(mul1_mul_temp_carry__1_i_5__0_n_0));
  LUT2 #(
    .INIT(4'h6)) 
    mul1_mul_temp_carry__1_i_6__0
       (.I0(mul1_mul_temp__2_n_88),
        .I1(mul1_mul_temp__0_n_105),
        .O(mul1_mul_temp_carry__1_i_6__0_n_0));
  LUT2 #(
    .INIT(4'h6)) 
    mul1_mul_temp_carry__1_i_7__0
       (.I0(mul1_mul_temp__2_n_89),
        .I1(mul1_mul_temp_n_89),
        .O(mul1_mul_temp_carry__1_i_7__0_n_0));
  LUT2 #(
    .INIT(4'h6)) 
    mul1_mul_temp_carry__1_i_8__0
       (.I0(mul1_mul_temp__2_n_90),
        .I1(mul1_mul_temp_n_90),
        .O(mul1_mul_temp_carry__1_i_8__0_n_0));
  (* ADDER_THRESHOLD = "35" *) 
  CARRY8 mul1_mul_temp_carry__2
       (.CI(mul1_mul_temp_carry__1_n_0),
        .CI_TOP(1'b0),
        .CO({mul1_mul_temp_carry__2_n_0,mul1_mul_temp_carry__2_n_1,mul1_mul_temp_carry__2_n_2,mul1_mul_temp_carry__2_n_3,mul1_mul_temp_carry__2_n_4,mul1_mul_temp_carry__2_n_5,mul1_mul_temp_carry__2_n_6,mul1_mul_temp_carry__2_n_7}),
        .DI({mul1_mul_temp__2_n_75,mul1_mul_temp__2_n_76,mul1_mul_temp__2_n_77,mul1_mul_temp__2_n_78,mul1_mul_temp__2_n_79,mul1_mul_temp__2_n_80,mul1_mul_temp__2_n_81,mul1_mul_temp__2_n_82}),
        .O({mul1_mul_temp_carry__2_n_8,mul1_mul_temp_carry__2_n_9,mul1_mul_temp_carry__2_n_10,mul1_mul_temp_carry__2_n_11,mul1_mul_temp_carry__2_n_12,mul1_mul_temp_carry__2_n_13,mul1_mul_temp_carry__2_n_14,mul1_mul_temp_carry__2_n_15}),
        .S({mul1_mul_temp_carry__2_i_1__0_n_0,mul1_mul_temp_carry__2_i_2__0_n_0,mul1_mul_temp_carry__2_i_3__0_n_0,mul1_mul_temp_carry__2_i_4__0_n_0,mul1_mul_temp_carry__2_i_5__0_n_0,mul1_mul_temp_carry__2_i_6__0_n_0,mul1_mul_temp_carry__2_i_7__0_n_0,mul1_mul_temp_carry__2_i_8__0_n_0}));
  LUT2 #(
    .INIT(4'h6)) 
    mul1_mul_temp_carry__2_i_1__0
       (.I0(mul1_mul_temp__2_n_75),
        .I1(mul1_mul_temp__0_n_92),
        .O(mul1_mul_temp_carry__2_i_1__0_n_0));
  LUT2 #(
    .INIT(4'h6)) 
    mul1_mul_temp_carry__2_i_2__0
       (.I0(mul1_mul_temp__2_n_76),
        .I1(mul1_mul_temp__0_n_93),
        .O(mul1_mul_temp_carry__2_i_2__0_n_0));
  LUT2 #(
    .INIT(4'h6)) 
    mul1_mul_temp_carry__2_i_3__0
       (.I0(mul1_mul_temp__2_n_77),
        .I1(mul1_mul_temp__0_n_94),
        .O(mul1_mul_temp_carry__2_i_3__0_n_0));
  LUT2 #(
    .INIT(4'h6)) 
    mul1_mul_temp_carry__2_i_4__0
       (.I0(mul1_mul_temp__2_n_78),
        .I1(mul1_mul_temp__0_n_95),
        .O(mul1_mul_temp_carry__2_i_4__0_n_0));
  LUT2 #(
    .INIT(4'h6)) 
    mul1_mul_temp_carry__2_i_5__0
       (.I0(mul1_mul_temp__2_n_79),
        .I1(mul1_mul_temp__0_n_96),
        .O(mul1_mul_temp_carry__2_i_5__0_n_0));
  LUT2 #(
    .INIT(4'h6)) 
    mul1_mul_temp_carry__2_i_6__0
       (.I0(mul1_mul_temp__2_n_80),
        .I1(mul1_mul_temp__0_n_97),
        .O(mul1_mul_temp_carry__2_i_6__0_n_0));
  LUT2 #(
    .INIT(4'h6)) 
    mul1_mul_temp_carry__2_i_7__0
       (.I0(mul1_mul_temp__2_n_81),
        .I1(mul1_mul_temp__0_n_98),
        .O(mul1_mul_temp_carry__2_i_7__0_n_0));
  LUT2 #(
    .INIT(4'h6)) 
    mul1_mul_temp_carry__2_i_8__0
       (.I0(mul1_mul_temp__2_n_82),
        .I1(mul1_mul_temp__0_n_99),
        .O(mul1_mul_temp_carry__2_i_8__0_n_0));
  (* ADDER_THRESHOLD = "35" *) 
  CARRY8 mul1_mul_temp_carry__3
       (.CI(mul1_mul_temp_carry__2_n_0),
        .CI_TOP(1'b0),
        .CO({mul1_mul_temp_carry__3_n_0,mul1_mul_temp_carry__3_n_1,mul1_mul_temp_carry__3_n_2,mul1_mul_temp_carry__3_n_3,mul1_mul_temp_carry__3_n_4,mul1_mul_temp_carry__3_n_5,mul1_mul_temp_carry__3_n_6,mul1_mul_temp_carry__3_n_7}),
        .DI({mul1_mul_temp__2_n_67,mul1_mul_temp__2_n_68,mul1_mul_temp__2_n_69,mul1_mul_temp__2_n_70,mul1_mul_temp__2_n_71,mul1_mul_temp__2_n_72,mul1_mul_temp__2_n_73,mul1_mul_temp__2_n_74}),
        .O({mul1_mul_temp_carry__3_n_8,mul1_mul_temp_carry__3_n_9,mul1_mul_temp_carry__3_n_10,mul1_mul_temp_carry__3_n_11,mul1_mul_temp_carry__3_n_12,mul1_mul_temp_carry__3_n_13,mul1_mul_temp_carry__3_n_14,mul1_mul_temp_carry__3_n_15}),
        .S({mul1_mul_temp_carry__3_i_1__0_n_0,mul1_mul_temp_carry__3_i_2__0_n_0,mul1_mul_temp_carry__3_i_3__0_n_0,mul1_mul_temp_carry__3_i_4__0_n_0,mul1_mul_temp_carry__3_i_5__0_n_0,mul1_mul_temp_carry__3_i_6__0_n_0,mul1_mul_temp_carry__3_i_7__0_n_0,mul1_mul_temp_carry__3_i_8__0_n_0}));
  LUT2 #(
    .INIT(4'h6)) 
    mul1_mul_temp_carry__3_i_1__0
       (.I0(mul1_mul_temp__2_n_67),
        .I1(mul1_mul_temp__0_n_84),
        .O(mul1_mul_temp_carry__3_i_1__0_n_0));
  LUT2 #(
    .INIT(4'h6)) 
    mul1_mul_temp_carry__3_i_2__0
       (.I0(mul1_mul_temp__2_n_68),
        .I1(mul1_mul_temp__0_n_85),
        .O(mul1_mul_temp_carry__3_i_2__0_n_0));
  LUT2 #(
    .INIT(4'h6)) 
    mul1_mul_temp_carry__3_i_3__0
       (.I0(mul1_mul_temp__2_n_69),
        .I1(mul1_mul_temp__0_n_86),
        .O(mul1_mul_temp_carry__3_i_3__0_n_0));
  LUT2 #(
    .INIT(4'h6)) 
    mul1_mul_temp_carry__3_i_4__0
       (.I0(mul1_mul_temp__2_n_70),
        .I1(mul1_mul_temp__0_n_87),
        .O(mul1_mul_temp_carry__3_i_4__0_n_0));
  LUT2 #(
    .INIT(4'h6)) 
    mul1_mul_temp_carry__3_i_5__0
       (.I0(mul1_mul_temp__2_n_71),
        .I1(mul1_mul_temp__0_n_88),
        .O(mul1_mul_temp_carry__3_i_5__0_n_0));
  LUT2 #(
    .INIT(4'h6)) 
    mul1_mul_temp_carry__3_i_6__0
       (.I0(mul1_mul_temp__2_n_72),
        .I1(mul1_mul_temp__0_n_89),
        .O(mul1_mul_temp_carry__3_i_6__0_n_0));
  LUT2 #(
    .INIT(4'h6)) 
    mul1_mul_temp_carry__3_i_7__0
       (.I0(mul1_mul_temp__2_n_73),
        .I1(mul1_mul_temp__0_n_90),
        .O(mul1_mul_temp_carry__3_i_7__0_n_0));
  LUT2 #(
    .INIT(4'h6)) 
    mul1_mul_temp_carry__3_i_8__0
       (.I0(mul1_mul_temp__2_n_74),
        .I1(mul1_mul_temp__0_n_91),
        .O(mul1_mul_temp_carry__3_i_8__0_n_0));
  (* ADDER_THRESHOLD = "35" *) 
  CARRY8 mul1_mul_temp_carry__4
       (.CI(mul1_mul_temp_carry__3_n_0),
        .CI_TOP(1'b0),
        .CO({NLW_mul1_mul_temp_carry__4_CO_UNCONNECTED[7],mul1_mul_temp_carry__4_n_1,mul1_mul_temp_carry__4_n_2,mul1_mul_temp_carry__4_n_3,mul1_mul_temp_carry__4_n_4,mul1_mul_temp_carry__4_n_5,mul1_mul_temp_carry__4_n_6,mul1_mul_temp_carry__4_n_7}),
        .DI({1'b0,mul1_mul_temp__2_n_60,mul1_mul_temp__2_n_61,mul1_mul_temp__2_n_62,mul1_mul_temp__2_n_63,mul1_mul_temp__2_n_64,mul1_mul_temp__2_n_65,mul1_mul_temp__2_n_66}),
        .O({mul1_mul_temp_carry__4_n_8,mul1_mul_temp_carry__4_n_9,mul1_mul_temp_carry__4_n_10,mul1_mul_temp_carry__4_n_11,mul1_mul_temp_carry__4_n_12,mul1_mul_temp_carry__4_n_13,mul1_mul_temp_carry__4_n_14,mul1_mul_temp_carry__4_n_15}),
        .S({mul1_mul_temp_carry__4_i_1__0_n_0,mul1_mul_temp_carry__4_i_2__0_n_0,mul1_mul_temp_carry__4_i_3__0_n_0,mul1_mul_temp_carry__4_i_4__0_n_0,mul1_mul_temp_carry__4_i_5__0_n_0,mul1_mul_temp_carry__4_i_6__0_n_0,mul1_mul_temp_carry__4_i_7__0_n_0,mul1_mul_temp_carry__4_i_8__0_n_0}));
  LUT2 #(
    .INIT(4'h6)) 
    mul1_mul_temp_carry__4_i_1__0
       (.I0(mul1_mul_temp__2_n_59),
        .I1(mul1_mul_temp__0_n_76),
        .O(mul1_mul_temp_carry__4_i_1__0_n_0));
  LUT2 #(
    .INIT(4'h6)) 
    mul1_mul_temp_carry__4_i_2__0
       (.I0(mul1_mul_temp__2_n_60),
        .I1(mul1_mul_temp__0_n_77),
        .O(mul1_mul_temp_carry__4_i_2__0_n_0));
  LUT2 #(
    .INIT(4'h6)) 
    mul1_mul_temp_carry__4_i_3__0
       (.I0(mul1_mul_temp__2_n_61),
        .I1(mul1_mul_temp__0_n_78),
        .O(mul1_mul_temp_carry__4_i_3__0_n_0));
  LUT2 #(
    .INIT(4'h6)) 
    mul1_mul_temp_carry__4_i_4__0
       (.I0(mul1_mul_temp__2_n_62),
        .I1(mul1_mul_temp__0_n_79),
        .O(mul1_mul_temp_carry__4_i_4__0_n_0));
  LUT2 #(
    .INIT(4'h6)) 
    mul1_mul_temp_carry__4_i_5__0
       (.I0(mul1_mul_temp__2_n_63),
        .I1(mul1_mul_temp__0_n_80),
        .O(mul1_mul_temp_carry__4_i_5__0_n_0));
  LUT2 #(
    .INIT(4'h6)) 
    mul1_mul_temp_carry__4_i_6__0
       (.I0(mul1_mul_temp__2_n_64),
        .I1(mul1_mul_temp__0_n_81),
        .O(mul1_mul_temp_carry__4_i_6__0_n_0));
  LUT2 #(
    .INIT(4'h6)) 
    mul1_mul_temp_carry__4_i_7__0
       (.I0(mul1_mul_temp__2_n_65),
        .I1(mul1_mul_temp__0_n_82),
        .O(mul1_mul_temp_carry__4_i_7__0_n_0));
  LUT2 #(
    .INIT(4'h6)) 
    mul1_mul_temp_carry__4_i_8__0
       (.I0(mul1_mul_temp__2_n_66),
        .I1(mul1_mul_temp__0_n_83),
        .O(mul1_mul_temp_carry__4_i_8__0_n_0));
  LUT2 #(
    .INIT(4'h6)) 
    mul1_mul_temp_carry_i_1__0
       (.I0(mul1_mul_temp__2_n_99),
        .I1(mul1_mul_temp_n_99),
        .O(mul1_mul_temp_carry_i_1__0_n_0));
  LUT2 #(
    .INIT(4'h6)) 
    mul1_mul_temp_carry_i_2__0
       (.I0(mul1_mul_temp__2_n_100),
        .I1(mul1_mul_temp_n_100),
        .O(mul1_mul_temp_carry_i_2__0_n_0));
  LUT2 #(
    .INIT(4'h6)) 
    mul1_mul_temp_carry_i_3__0
       (.I0(mul1_mul_temp__2_n_101),
        .I1(mul1_mul_temp_n_101),
        .O(mul1_mul_temp_carry_i_3__0_n_0));
  LUT2 #(
    .INIT(4'h6)) 
    mul1_mul_temp_carry_i_4__0
       (.I0(mul1_mul_temp__2_n_102),
        .I1(mul1_mul_temp_n_102),
        .O(mul1_mul_temp_carry_i_4__0_n_0));
  LUT2 #(
    .INIT(4'h6)) 
    mul1_mul_temp_carry_i_5__0
       (.I0(mul1_mul_temp__2_n_103),
        .I1(mul1_mul_temp_n_103),
        .O(mul1_mul_temp_carry_i_5__0_n_0));
  LUT2 #(
    .INIT(4'h6)) 
    mul1_mul_temp_carry_i_6__0
       (.I0(mul1_mul_temp__2_n_104),
        .I1(mul1_mul_temp_n_104),
        .O(mul1_mul_temp_carry_i_6__0_n_0));
  LUT2 #(
    .INIT(4'h6)) 
    mul1_mul_temp_carry_i_7__0
       (.I0(mul1_mul_temp__2_n_105),
        .I1(mul1_mul_temp_n_105),
        .O(mul1_mul_temp_carry_i_7__0_n_0));
  LUT4 #(
    .INIT(16'hBFB0)) 
    mul1_mul_temp_i_1
       (.I0(subtractor_sub_temp_carry__0_n_8),
        .I1(subtractor_sub_temp_carry__2_n_0),
        .I2(sel),
        .I3(DSP_A_B_DATA_INST[16]),
        .O(mul1_mul_temp_i_1_n_0));
  LUT4 #(
    .INIT(16'hBFB0)) 
    mul1_mul_temp_i_10
       (.I0(subtractor_sub_temp_carry_n_9),
        .I1(subtractor_sub_temp_carry__2_n_0),
        .I2(sel),
        .I3(DSP_A_B_DATA_INST[7]),
        .O(mul1_mul_temp_i_10_n_0));
  LUT4 #(
    .INIT(16'hBFB0)) 
    mul1_mul_temp_i_11
       (.I0(subtractor_sub_temp_carry_n_10),
        .I1(subtractor_sub_temp_carry__2_n_0),
        .I2(sel),
        .I3(DSP_A_B_DATA_INST[6]),
        .O(mul1_mul_temp_i_11_n_0));
  LUT4 #(
    .INIT(16'hBFB0)) 
    mul1_mul_temp_i_12
       (.I0(subtractor_sub_temp_carry_n_11),
        .I1(subtractor_sub_temp_carry__2_n_0),
        .I2(sel),
        .I3(DSP_A_B_DATA_INST[5]),
        .O(mul1_mul_temp_i_12_n_0));
  LUT4 #(
    .INIT(16'hBFB0)) 
    mul1_mul_temp_i_13
       (.I0(subtractor_sub_temp_carry_n_12),
        .I1(subtractor_sub_temp_carry__2_n_0),
        .I2(sel),
        .I3(DSP_A_B_DATA_INST[4]),
        .O(mul1_mul_temp_i_13_n_0));
  LUT4 #(
    .INIT(16'hBFB0)) 
    mul1_mul_temp_i_14
       (.I0(subtractor_sub_temp_carry_n_13),
        .I1(subtractor_sub_temp_carry__2_n_0),
        .I2(sel),
        .I3(DSP_A_B_DATA_INST[3]),
        .O(mul1_mul_temp_i_14_n_0));
  LUT4 #(
    .INIT(16'hBFB0)) 
    mul1_mul_temp_i_15
       (.I0(subtractor_sub_temp_carry_n_14),
        .I1(subtractor_sub_temp_carry__2_n_0),
        .I2(sel),
        .I3(DSP_A_B_DATA_INST[2]),
        .O(mul1_mul_temp_i_15_n_0));
  (* SOFT_HLUTNM = "soft_lutpair50" *) 
  LUT4 #(
    .INIT(16'hBFB0)) 
    mul1_mul_temp_i_16
       (.I0(subtractor_sub_temp_carry_n_15),
        .I1(subtractor_sub_temp_carry__2_n_0),
        .I2(sel),
        .I3(DSP_A_B_DATA_INST[1]),
        .O(mul1_mul_temp_i_16_n_0));
  (* SOFT_HLUTNM = "soft_lutpair49" *) 
  LUT4 #(
    .INIT(16'hBFB0)) 
    mul1_mul_temp_i_17
       (.I0(Q[0]),
        .I1(subtractor_sub_temp_carry__2_n_0),
        .I2(sel),
        .I3(DSP_A_B_DATA_INST[0]),
        .O(mul1_mul_temp_i_17_n_0));
  LUT4 #(
    .INIT(16'hBFB0)) 
    mul1_mul_temp_i_2
       (.I0(subtractor_sub_temp_carry__0_n_9),
        .I1(subtractor_sub_temp_carry__2_n_0),
        .I2(sel),
        .I3(DSP_A_B_DATA_INST[15]),
        .O(mul1_mul_temp_i_2_n_0));
  LUT4 #(
    .INIT(16'hBFB0)) 
    mul1_mul_temp_i_3
       (.I0(subtractor_sub_temp_carry__0_n_10),
        .I1(subtractor_sub_temp_carry__2_n_0),
        .I2(sel),
        .I3(DSP_A_B_DATA_INST[14]),
        .O(mul1_mul_temp_i_3_n_0));
  LUT4 #(
    .INIT(16'hBFB0)) 
    mul1_mul_temp_i_4
       (.I0(subtractor_sub_temp_carry__0_n_11),
        .I1(subtractor_sub_temp_carry__2_n_0),
        .I2(sel),
        .I3(DSP_A_B_DATA_INST[13]),
        .O(mul1_mul_temp_i_4_n_0));
  LUT4 #(
    .INIT(16'hBFB0)) 
    mul1_mul_temp_i_5
       (.I0(subtractor_sub_temp_carry__0_n_12),
        .I1(subtractor_sub_temp_carry__2_n_0),
        .I2(sel),
        .I3(DSP_A_B_DATA_INST[12]),
        .O(mul1_mul_temp_i_5_n_0));
  LUT4 #(
    .INIT(16'hBFB0)) 
    mul1_mul_temp_i_6
       (.I0(subtractor_sub_temp_carry__0_n_13),
        .I1(subtractor_sub_temp_carry__2_n_0),
        .I2(sel),
        .I3(DSP_A_B_DATA_INST[11]),
        .O(mul1_mul_temp_i_6_n_0));
  LUT4 #(
    .INIT(16'hBFB0)) 
    mul1_mul_temp_i_7
       (.I0(subtractor_sub_temp_carry__0_n_14),
        .I1(subtractor_sub_temp_carry__2_n_0),
        .I2(sel),
        .I3(DSP_A_B_DATA_INST[10]),
        .O(mul1_mul_temp_i_7_n_0));
  LUT4 #(
    .INIT(16'hBFB0)) 
    mul1_mul_temp_i_8
       (.I0(subtractor_sub_temp_carry__0_n_15),
        .I1(subtractor_sub_temp_carry__2_n_0),
        .I2(sel),
        .I3(DSP_A_B_DATA_INST[9]),
        .O(mul1_mul_temp_i_8_n_0));
  LUT4 #(
    .INIT(16'hBFB0)) 
    mul1_mul_temp_i_9
       (.I0(subtractor_sub_temp_carry_n_8),
        .I1(subtractor_sub_temp_carry__2_n_0),
        .I2(sel),
        .I3(DSP_A_B_DATA_INST[8]),
        .O(mul1_mul_temp_i_9_n_0));
  CARRY8 subtractor_sub_temp_carry
       (.CI(mul1_mul_temp_i_16_0),
        .CI_TOP(1'b0),
        .CO({subtractor_sub_temp_carry_n_0,subtractor_sub_temp_carry_n_1,subtractor_sub_temp_carry_n_2,subtractor_sub_temp_carry_n_3,subtractor_sub_temp_carry_n_4,subtractor_sub_temp_carry_n_5,subtractor_sub_temp_carry_n_6,subtractor_sub_temp_carry_n_7}),
        .DI({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .O({subtractor_sub_temp_carry_n_8,subtractor_sub_temp_carry_n_9,subtractor_sub_temp_carry_n_10,subtractor_sub_temp_carry_n_11,subtractor_sub_temp_carry_n_12,subtractor_sub_temp_carry_n_13,subtractor_sub_temp_carry_n_14,subtractor_sub_temp_carry_n_15}),
        .S(S));
  CARRY8 subtractor_sub_temp_carry__0
       (.CI(subtractor_sub_temp_carry_n_0),
        .CI_TOP(1'b0),
        .CO({subtractor_sub_temp_carry__0_n_0,subtractor_sub_temp_carry__0_n_1,subtractor_sub_temp_carry__0_n_2,subtractor_sub_temp_carry__0_n_3,subtractor_sub_temp_carry__0_n_4,subtractor_sub_temp_carry__0_n_5,subtractor_sub_temp_carry__0_n_6,subtractor_sub_temp_carry__0_n_7}),
        .DI({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .O({subtractor_sub_temp_carry__0_n_8,subtractor_sub_temp_carry__0_n_9,subtractor_sub_temp_carry__0_n_10,subtractor_sub_temp_carry__0_n_11,subtractor_sub_temp_carry__0_n_12,subtractor_sub_temp_carry__0_n_13,subtractor_sub_temp_carry__0_n_14,subtractor_sub_temp_carry__0_n_15}),
        .S(mul1_mul_temp_i_8_0));
  CARRY8 subtractor_sub_temp_carry__1
       (.CI(subtractor_sub_temp_carry__0_n_0),
        .CI_TOP(1'b0),
        .CO({subtractor_sub_temp_carry__1_n_0,subtractor_sub_temp_carry__1_n_1,subtractor_sub_temp_carry__1_n_2,subtractor_sub_temp_carry__1_n_3,subtractor_sub_temp_carry__1_n_4,subtractor_sub_temp_carry__1_n_5,subtractor_sub_temp_carry__1_n_6,subtractor_sub_temp_carry__1_n_7}),
        .DI({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .O({subtractor_sub_temp_carry__1_n_8,subtractor_sub_temp_carry__1_n_9,subtractor_sub_temp_carry__1_n_10,subtractor_sub_temp_carry__1_n_11,subtractor_sub_temp_carry__1_n_12,subtractor_sub_temp_carry__1_n_13,subtractor_sub_temp_carry__1_n_14,subtractor_sub_temp_carry__1_n_15}),
        .S(mul1_mul_temp__0_i_15_0));
  CARRY8 subtractor_sub_temp_carry__2
       (.CI(subtractor_sub_temp_carry__1_n_0),
        .CI_TOP(1'b0),
        .CO({subtractor_sub_temp_carry__2_n_0,NLW_subtractor_sub_temp_carry__2_CO_UNCONNECTED[6],subtractor_sub_temp_carry__2_n_2,subtractor_sub_temp_carry__2_n_3,subtractor_sub_temp_carry__2_n_4,subtractor_sub_temp_carry__2_n_5,subtractor_sub_temp_carry__2_n_6,subtractor_sub_temp_carry__2_n_7}),
        .DI({1'b0,DI,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .O({NLW_subtractor_sub_temp_carry__2_O_UNCONNECTED[7],subtractor_sub_temp_carry__2_n_9,subtractor_sub_temp_carry__2_n_10,subtractor_sub_temp_carry__2_n_11,subtractor_sub_temp_carry__2_n_12,subtractor_sub_temp_carry__2_n_13,subtractor_sub_temp_carry__2_n_14,subtractor_sub_temp_carry__2_n_15}),
        .S({1'b1,Q[31],mul1_mul_temp__0_i_7_0}));
  FDRE \xout_tmp_reg[10] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\delayout[10]_i_1_n_0 ),
        .Q(\xout_tmp_reg_n_0_[10] ),
        .R(RSTP));
  FDRE \xout_tmp_reg[11] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\delayout[11]_i_1_n_0 ),
        .Q(\xout_tmp_reg_n_0_[11] ),
        .R(RSTP));
  FDRE \xout_tmp_reg[12] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\delayout[12]_i_1_n_0 ),
        .Q(\xout_tmp_reg_n_0_[12] ),
        .R(RSTP));
  FDRE \xout_tmp_reg[13] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\delayout[13]_i_1_n_0 ),
        .Q(\xout_tmp_reg_n_0_[13] ),
        .R(RSTP));
  FDRE \xout_tmp_reg[14] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\delayout[14]_i_1_n_0 ),
        .Q(\xout_tmp_reg_n_0_[14] ),
        .R(RSTP));
  FDRE \xout_tmp_reg[15] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\delayout[15]_i_1_n_0 ),
        .Q(\xout_tmp_reg_n_0_[15] ),
        .R(RSTP));
  FDRE \xout_tmp_reg[16] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\delayout[16]_i_1_n_0 ),
        .Q(\xout_tmp_reg_n_0_[16] ),
        .R(RSTP));
  FDRE \xout_tmp_reg[17] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\delayout[17]_i_1_n_0 ),
        .Q(\xout_tmp_reg_n_0_[17] ),
        .R(RSTP));
  FDRE \xout_tmp_reg[18] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\delayout[18]_i_1_n_0 ),
        .Q(\xout_tmp_reg_n_0_[18] ),
        .R(RSTP));
  FDRE \xout_tmp_reg[19] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\delayout[19]_i_1_n_0 ),
        .Q(\xout_tmp_reg_n_0_[19] ),
        .R(RSTP));
  FDRE \xout_tmp_reg[1] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\delayout[1]_i_1_n_0 ),
        .Q(\xout_tmp_reg_n_0_[1] ),
        .R(RSTP));
  FDRE \xout_tmp_reg[20] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\delayout[20]_i_1_n_0 ),
        .Q(\xout_tmp_reg_n_0_[20] ),
        .R(RSTP));
  FDRE \xout_tmp_reg[21] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\delayout[21]_i_1_n_0 ),
        .Q(\xout_tmp_reg_n_0_[21] ),
        .R(RSTP));
  FDRE \xout_tmp_reg[22] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\delayout[22]_i_1_n_0 ),
        .Q(\xout_tmp_reg_n_0_[22] ),
        .R(RSTP));
  FDRE \xout_tmp_reg[23] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\delayout[23]_i_1_n_0 ),
        .Q(\xout_tmp_reg_n_0_[23] ),
        .R(RSTP));
  FDRE \xout_tmp_reg[24] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\delayout[24]_i_1_n_0 ),
        .Q(\xout_tmp_reg_n_0_[24] ),
        .R(RSTP));
  FDRE \xout_tmp_reg[25] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\delayout[25]_i_1_n_0 ),
        .Q(\xout_tmp_reg_n_0_[25] ),
        .R(RSTP));
  FDRE \xout_tmp_reg[26] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\delayout[26]_i_1_n_0 ),
        .Q(\xout_tmp_reg_n_0_[26] ),
        .R(RSTP));
  FDRE \xout_tmp_reg[27] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\delayout[27]_i_1_n_0 ),
        .Q(\xout_tmp_reg_n_0_[27] ),
        .R(RSTP));
  FDRE \xout_tmp_reg[28] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\delayout[28]_i_1_n_0 ),
        .Q(\xout_tmp_reg_n_0_[28] ),
        .R(RSTP));
  FDRE \xout_tmp_reg[29] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\delayout[29]_i_1_n_0 ),
        .Q(\xout_tmp_reg_n_0_[29] ),
        .R(RSTP));
  FDRE \xout_tmp_reg[2] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\delayout[2]_i_1_n_0 ),
        .Q(\xout_tmp_reg_n_0_[2] ),
        .R(RSTP));
  FDRE \xout_tmp_reg[30] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\delayout[30]_i_1_n_0 ),
        .Q(\xout_tmp_reg_n_0_[30] ),
        .R(RSTP));
  FDRE \xout_tmp_reg[31] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\delayout[31]_i_1_n_0 ),
        .Q(\shiftarr[0]0 ),
        .R(RSTP));
  FDRE \xout_tmp_reg[3] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\delayout[3]_i_1_n_0 ),
        .Q(\xout_tmp_reg_n_0_[3] ),
        .R(RSTP));
  FDRE \xout_tmp_reg[4] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\delayout[4]_i_1_n_0 ),
        .Q(\xout_tmp_reg_n_0_[4] ),
        .R(RSTP));
  FDRE \xout_tmp_reg[5] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\delayout[5]_i_1_n_0 ),
        .Q(\xout_tmp_reg_n_0_[5] ),
        .R(RSTP));
  FDRE \xout_tmp_reg[6] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\delayout[6]_i_1_n_0 ),
        .Q(\xout_tmp_reg_n_0_[6] ),
        .R(RSTP));
  FDRE \xout_tmp_reg[7] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\delayout[7]_i_1_n_0 ),
        .Q(\xout_tmp_reg_n_0_[7] ),
        .R(RSTP));
  FDRE \xout_tmp_reg[8] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\delayout[8]_i_1_n_0 ),
        .Q(\xout_tmp_reg_n_0_[8] ),
        .R(RSTP));
  FDRE \xout_tmp_reg[9] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\delayout[9]_i_1_n_0 ),
        .Q(\xout_tmp_reg_n_0_[9] ),
        .R(RSTP));
endmodule

(* ORIG_REF_NAME = "IncreEncoder_V24_ip_src_IncreEncoder_V24" *) 
module zusys_IncreEncoder_V24_ip_0_0_IncreEncoder_V24_ip_src_IncreEncoder_V24
   (phase_0_reg,
    theta_el,
    edge_rsvd,
    count,
    \countPerPEriod_1_reg[15]_0 ,
    position,
    \reset_old5_out1_reg[0] ,
    \reset_old5_out1_reg[3] ,
    Q,
    D,
    OverSamplFactor,
    RSTP,
    IPCORE_CLK,
    write_axi_enable,
    DSP_ALU_INST,
    \reset_old4_out1_reg[0] ,
    \reset_old4_out1_reg[0]_0 ,
    PeriodEnd,
    I,
    A,
    B,
    \Pipeline6_out1_reg[31]_0 ,
    \Pipeline4_out1_reg[23]_0 ,
    \Pipeline2_out1_reg[15]_0 ,
    \Pipeline3_out1_reg[15]_0 );
  output phase_0_reg;
  output [23:0]theta_el;
  output edge_rsvd;
  output count;
  output [15:0]\countPerPEriod_1_reg[15]_0 ;
  output [15:0]position;
  output \reset_old5_out1_reg[0] ;
  output \reset_old5_out1_reg[3] ;
  output [0:0]Q;
  output [22:0]D;
  output [15:0]OverSamplFactor;
  input RSTP;
  input IPCORE_CLK;
  input write_axi_enable;
  input [23:0]DSP_ALU_INST;
  input \reset_old4_out1_reg[0] ;
  input [0:0]\reset_old4_out1_reg[0]_0 ;
  input PeriodEnd;
  input I;
  input A;
  input B;
  input [31:0]\Pipeline6_out1_reg[31]_0 ;
  input [23:0]\Pipeline4_out1_reg[23]_0 ;
  input [15:0]\Pipeline2_out1_reg[15]_0 ;
  input [15:0]\Pipeline3_out1_reg[15]_0 ;

  wire A;
  wire B;
  wire [3:0]Check_Direction_out1;
  wire [22:0]D;
  wire [23:0]DSP_ALU_INST;
  wire Delay7_ctrl_delay_out;
  wire Div_i1_mul_temp_n_100;
  wire Div_i1_mul_temp_n_101;
  wire Div_i1_mul_temp_n_102;
  wire Div_i1_mul_temp_n_103;
  wire Div_i1_mul_temp_n_104;
  wire Div_i1_mul_temp_n_105;
  wire Div_i1_mul_temp_n_65;
  wire Div_i1_mul_temp_n_82;
  wire Div_i1_mul_temp_n_83;
  wire Div_i1_mul_temp_n_84;
  wire Div_i1_mul_temp_n_85;
  wire Div_i1_mul_temp_n_86;
  wire Div_i1_mul_temp_n_87;
  wire Div_i1_mul_temp_n_88;
  wire Div_i1_mul_temp_n_89;
  wire Div_i1_mul_temp_n_90;
  wire Div_i1_mul_temp_n_91;
  wire Div_i1_mul_temp_n_92;
  wire Div_i1_mul_temp_n_93;
  wire Div_i1_mul_temp_n_94;
  wire Div_i1_mul_temp_n_95;
  wire Div_i1_mul_temp_n_96;
  wire Div_i1_mul_temp_n_97;
  wire Div_i1_mul_temp_n_98;
  wire Div_i1_mul_temp_n_99;
  wire I;
  wire IPCORE_CLK;
  wire Logical2_out1;
  wire Logical2_out1_1;
  wire OnlyAllowInNewPeriod_out1;
  wire [15:0]OverSamplFactor;
  wire PeriodEnd;
  wire [15:0]Pipeline2_out1;
  wire [15:0]\Pipeline2_out1_reg[15]_0 ;
  wire [15:0]Pipeline3_out1;
  wire [15:0]\Pipeline3_out1_reg[15]_0 ;
  wire [23:0]Pipeline4_out1;
  wire [23:0]\Pipeline4_out1_reg[23]_0 ;
  wire [31:0]Pipeline6_out1;
  wire [31:0]\Pipeline6_out1_reg[31]_0 ;
  wire [31:0]Pipeline7_out1;
  wire [0:0]Q;
  wire RSTP;
  wire Relational_Operator_relop1;
  wire count;
  wire [15:0]countPerPEriod;
  wire [15:0]\countPerPEriod_1_reg[15]_0 ;
  wire count_1;
  wire count_2;
  wire [15:0]count_el;
  wire [15:0]count_mech;
  wire edge_rsvd;
  wire enb_1_100_0;
  wire [3:0]hold1_out1;
  wire [31:0]hold2_out1;
  wire [15:0]hold5_out1;
  wire [15:0]omega_by_measure_time_out2;
  wire [23:23]omega_oversampled;
  wire \omega_oversampled[0]_i_1_n_0 ;
  wire \omega_oversampled[10]_i_1_n_0 ;
  wire \omega_oversampled[11]_i_1_n_0 ;
  wire \omega_oversampled[12]_i_1_n_0 ;
  wire \omega_oversampled[13]_i_1_n_0 ;
  wire \omega_oversampled[14]_i_1_n_0 ;
  wire \omega_oversampled[15]_i_1_n_0 ;
  wire \omega_oversampled[16]_i_1_n_0 ;
  wire \omega_oversampled[17]_i_1_n_0 ;
  wire \omega_oversampled[18]_i_1_n_0 ;
  wire \omega_oversampled[19]_i_1_n_0 ;
  wire \omega_oversampled[1]_i_1_n_0 ;
  wire \omega_oversampled[20]_i_1_n_0 ;
  wire \omega_oversampled[21]_i_1_n_0 ;
  wire \omega_oversampled[22]_i_10_n_0 ;
  wire \omega_oversampled[22]_i_11_n_0 ;
  wire \omega_oversampled[22]_i_2_n_0 ;
  wire \omega_oversampled[22]_i_3_n_0 ;
  wire \omega_oversampled[22]_i_4_n_0 ;
  wire \omega_oversampled[22]_i_5_n_0 ;
  wire \omega_oversampled[22]_i_6_n_0 ;
  wire \omega_oversampled[22]_i_7_n_0 ;
  wire \omega_oversampled[22]_i_8_n_0 ;
  wire \omega_oversampled[22]_i_9_n_0 ;
  wire \omega_oversampled[2]_i_1_n_0 ;
  wire \omega_oversampled[3]_i_1_n_0 ;
  wire \omega_oversampled[4]_i_1_n_0 ;
  wire \omega_oversampled[5]_i_1_n_0 ;
  wire \omega_oversampled[6]_i_1_n_0 ;
  wire \omega_oversampled[7]_i_1_n_0 ;
  wire \omega_oversampled[8]_i_1_n_0 ;
  wire \omega_oversampled[9]_i_1_n_0 ;
  wire p_0_in;
  wire [14:0]p_0_in__0;
  wire phase_0_reg;
  wire [15:0]position;
  wire reset_old1_out1;
  wire reset_old2_out1;
  wire reset_old3_out1;
  wire reset_old3_out1_0;
  wire [15:15]reset_old4_out1;
  wire \reset_old4_out1_reg[0] ;
  wire [0:0]\reset_old4_out1_reg[0]_0 ;
  wire \reset_old5_out1_reg[0] ;
  wire \reset_old5_out1_reg[3] ;
  wire reset_old_out1;
  wire [37:14]rps;
  wire [15:15]speed_old_switch1_out1;
  wire [23:0]theta_el;
  wire theta_el_tmp_reg_n_102;
  wire theta_el_tmp_reg_n_103;
  wire theta_el_tmp_reg_n_104;
  wire theta_el_tmp_reg_n_105;
  wire u_Check_Direction_n_0;
  wire u_Check_Direction_n_1;
  wire u_Counter_n_10;
  wire u_Counter_n_11;
  wire u_Counter_n_12;
  wire u_Counter_n_13;
  wire u_Counter_n_14;
  wire u_Counter_n_15;
  wire u_Counter_n_16;
  wire u_Counter_n_17;
  wire u_Counter_n_18;
  wire u_Counter_n_19;
  wire u_Counter_n_2;
  wire u_Counter_n_20;
  wire u_Counter_n_21;
  wire u_Counter_n_22;
  wire u_Counter_n_23;
  wire u_Counter_n_24;
  wire u_Counter_n_25;
  wire u_Counter_n_26;
  wire u_Counter_n_27;
  wire u_Counter_n_28;
  wire u_Counter_n_29;
  wire u_Counter_n_30;
  wire u_Counter_n_31;
  wire u_Counter_n_32;
  wire u_Counter_n_4;
  wire u_Counter_n_5;
  wire u_Counter_n_6;
  wire u_Counter_n_7;
  wire u_Counter_n_8;
  wire u_Counter_n_9;
  wire u_Counter_theta_ele_n_10;
  wire u_Counter_theta_ele_n_11;
  wire u_Counter_theta_ele_n_12;
  wire u_Counter_theta_ele_n_29;
  wire u_Counter_theta_ele_n_30;
  wire u_Counter_theta_ele_n_31;
  wire u_Counter_theta_ele_n_32;
  wire u_Counter_theta_ele_n_33;
  wire u_Counter_theta_ele_n_34;
  wire u_Counter_theta_ele_n_35;
  wire u_Counter_theta_ele_n_36;
  wire u_Counter_theta_ele_n_37;
  wire u_Counter_theta_ele_n_4;
  wire u_Counter_theta_ele_n_5;
  wire u_Counter_theta_ele_n_6;
  wire u_Counter_theta_ele_n_7;
  wire u_Counter_theta_ele_n_8;
  wire u_Counter_theta_ele_n_9;
  wire u_HDL_Reciprocal_n_0;
  wire u_HDL_Reciprocal_n_1;
  wire u_HDL_Reciprocal_n_10;
  wire u_HDL_Reciprocal_n_11;
  wire u_HDL_Reciprocal_n_12;
  wire u_HDL_Reciprocal_n_13;
  wire u_HDL_Reciprocal_n_14;
  wire u_HDL_Reciprocal_n_15;
  wire u_HDL_Reciprocal_n_16;
  wire u_HDL_Reciprocal_n_17;
  wire u_HDL_Reciprocal_n_18;
  wire u_HDL_Reciprocal_n_19;
  wire u_HDL_Reciprocal_n_2;
  wire u_HDL_Reciprocal_n_20;
  wire u_HDL_Reciprocal_n_21;
  wire u_HDL_Reciprocal_n_22;
  wire u_HDL_Reciprocal_n_23;
  wire u_HDL_Reciprocal_n_3;
  wire u_HDL_Reciprocal_n_4;
  wire u_HDL_Reciprocal_n_5;
  wire u_HDL_Reciprocal_n_6;
  wire u_HDL_Reciprocal_n_7;
  wire u_HDL_Reciprocal_n_8;
  wire u_HDL_Reciprocal_n_9;
  wire u_IncreEncoder_V24_tc_n_1;
  wire u_IncreEncoder_V24_tc_n_3;
  wire u_IncreEncoder_V24_tc_n_4;
  wire u_IncreEncoder_V24_tc_n_5;
  wire u_IncreEncoder_V24_tc_n_6;
  wire u_IncreEncoder_V24_tc_n_7;
  wire u_IncreEncoder_V24_tc_n_8;
  wire u_omega_by_measure_time_n_0;
  wire u_omega_by_measure_time_n_2;
  wire write_axi_enable;
  wire NLW_Div_i1_mul_temp_CARRYCASCOUT_UNCONNECTED;
  wire NLW_Div_i1_mul_temp_MULTSIGNOUT_UNCONNECTED;
  wire NLW_Div_i1_mul_temp_OVERFLOW_UNCONNECTED;
  wire NLW_Div_i1_mul_temp_PATTERNBDETECT_UNCONNECTED;
  wire NLW_Div_i1_mul_temp_PATTERNDETECT_UNCONNECTED;
  wire NLW_Div_i1_mul_temp_UNDERFLOW_UNCONNECTED;
  wire [29:0]NLW_Div_i1_mul_temp_ACOUT_UNCONNECTED;
  wire [17:0]NLW_Div_i1_mul_temp_BCOUT_UNCONNECTED;
  wire [3:0]NLW_Div_i1_mul_temp_CARRYOUT_UNCONNECTED;
  wire [47:41]NLW_Div_i1_mul_temp_P_UNCONNECTED;
  wire [47:0]NLW_Div_i1_mul_temp_PCOUT_UNCONNECTED;
  wire [7:0]NLW_Div_i1_mul_temp_XOROUT_UNCONNECTED;
  wire NLW_theta_el_tmp_reg_CARRYCASCOUT_UNCONNECTED;
  wire NLW_theta_el_tmp_reg_MULTSIGNOUT_UNCONNECTED;
  wire NLW_theta_el_tmp_reg_OVERFLOW_UNCONNECTED;
  wire NLW_theta_el_tmp_reg_PATTERNBDETECT_UNCONNECTED;
  wire NLW_theta_el_tmp_reg_PATTERNDETECT_UNCONNECTED;
  wire NLW_theta_el_tmp_reg_UNDERFLOW_UNCONNECTED;
  wire [29:0]NLW_theta_el_tmp_reg_ACOUT_UNCONNECTED;
  wire [17:0]NLW_theta_el_tmp_reg_BCOUT_UNCONNECTED;
  wire [3:0]NLW_theta_el_tmp_reg_CARRYOUT_UNCONNECTED;
  wire [47:28]NLW_theta_el_tmp_reg_P_UNCONNECTED;
  wire [47:0]NLW_theta_el_tmp_reg_PCOUT_UNCONNECTED;
  wire [7:0]NLW_theta_el_tmp_reg_XOROUT_UNCONNECTED;

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
    .BCASCREG(2),
    .BMULTSEL("B"),
    .BREG(2),
    .B_INPUT("DIRECT"),
    .CARRYINREG(0),
    .CARRYINSELREG(0),
    .CREG(1),
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
    Div_i1_mul_temp
       (.A({u_HDL_Reciprocal_n_0,u_HDL_Reciprocal_n_0,u_HDL_Reciprocal_n_0,u_HDL_Reciprocal_n_0,u_HDL_Reciprocal_n_0,u_HDL_Reciprocal_n_0,u_HDL_Reciprocal_n_0,u_HDL_Reciprocal_n_1,u_HDL_Reciprocal_n_2,u_HDL_Reciprocal_n_3,u_HDL_Reciprocal_n_4,u_HDL_Reciprocal_n_5,u_HDL_Reciprocal_n_6,u_HDL_Reciprocal_n_7,u_HDL_Reciprocal_n_8,u_HDL_Reciprocal_n_9,u_HDL_Reciprocal_n_10,u_HDL_Reciprocal_n_11,u_HDL_Reciprocal_n_12,u_HDL_Reciprocal_n_13,u_HDL_Reciprocal_n_14,u_HDL_Reciprocal_n_15,u_HDL_Reciprocal_n_16,u_HDL_Reciprocal_n_17,u_HDL_Reciprocal_n_18,u_HDL_Reciprocal_n_19,u_HDL_Reciprocal_n_20,u_HDL_Reciprocal_n_21,u_HDL_Reciprocal_n_22,u_HDL_Reciprocal_n_23}),
        .ACIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .ACOUT(NLW_Div_i1_mul_temp_ACOUT_UNCONNECTED[29:0]),
        .ALUMODE({1'b0,1'b0,1'b0,1'b0}),
        .B({1'b0,1'b0,omega_by_measure_time_out2}),
        .BCIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .BCOUT(NLW_Div_i1_mul_temp_BCOUT_UNCONNECTED[17:0]),
        .C({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .CARRYCASCIN(1'b0),
        .CARRYCASCOUT(NLW_Div_i1_mul_temp_CARRYCASCOUT_UNCONNECTED),
        .CARRYIN(1'b0),
        .CARRYINSEL({1'b0,1'b0,1'b0}),
        .CARRYOUT(NLW_Div_i1_mul_temp_CARRYOUT_UNCONNECTED[3:0]),
        .CEA1(1'b0),
        .CEA2(1'b0),
        .CEAD(1'b0),
        .CEALUMODE(1'b0),
        .CEB1(enb_1_100_0),
        .CEB2(enb_1_100_0),
        .CEC(1'b0),
        .CECARRYIN(1'b0),
        .CECTRL(1'b0),
        .CED(1'b0),
        .CEINMODE(1'b0),
        .CEM(1'b0),
        .CEP(1'b0),
        .CLK(IPCORE_CLK),
        .D({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .INMODE({1'b0,1'b0,1'b0,1'b0,1'b0}),
        .MULTSIGNIN(1'b0),
        .MULTSIGNOUT(NLW_Div_i1_mul_temp_MULTSIGNOUT_UNCONNECTED),
        .OPMODE({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b1,1'b0,1'b1}),
        .OVERFLOW(NLW_Div_i1_mul_temp_OVERFLOW_UNCONNECTED),
        .P({NLW_Div_i1_mul_temp_P_UNCONNECTED[47:41],Div_i1_mul_temp_n_65,p_0_in,p_0_in__0,Div_i1_mul_temp_n_82,Div_i1_mul_temp_n_83,Div_i1_mul_temp_n_84,Div_i1_mul_temp_n_85,Div_i1_mul_temp_n_86,Div_i1_mul_temp_n_87,Div_i1_mul_temp_n_88,Div_i1_mul_temp_n_89,Div_i1_mul_temp_n_90,Div_i1_mul_temp_n_91,Div_i1_mul_temp_n_92,Div_i1_mul_temp_n_93,Div_i1_mul_temp_n_94,Div_i1_mul_temp_n_95,Div_i1_mul_temp_n_96,Div_i1_mul_temp_n_97,Div_i1_mul_temp_n_98,Div_i1_mul_temp_n_99,Div_i1_mul_temp_n_100,Div_i1_mul_temp_n_101,Div_i1_mul_temp_n_102,Div_i1_mul_temp_n_103,Div_i1_mul_temp_n_104,Div_i1_mul_temp_n_105}),
        .PATTERNBDETECT(NLW_Div_i1_mul_temp_PATTERNBDETECT_UNCONNECTED),
        .PATTERNDETECT(NLW_Div_i1_mul_temp_PATTERNDETECT_UNCONNECTED),
        .PCIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .PCOUT(NLW_Div_i1_mul_temp_PCOUT_UNCONNECTED[47:0]),
        .RSTA(1'b0),
        .RSTALLCARRYIN(1'b0),
        .RSTALUMODE(1'b0),
        .RSTB(RSTP),
        .RSTC(1'b0),
        .RSTCTRL(1'b0),
        .RSTD(1'b0),
        .RSTINMODE(1'b0),
        .RSTM(1'b0),
        .RSTP(1'b0),
        .UNDERFLOW(NLW_Div_i1_mul_temp_UNDERFLOW_UNCONNECTED),
        .XOROUT(NLW_Div_i1_mul_temp_XOROUT_UNCONNECTED[7:0]));
  (* SOFT_HLUTNM = "soft_lutpair185" *) 
  LUT1 #(
    .INIT(2'h1)) 
    Logical2_out1_1_i_1
       (.I0(A),
        .O(Logical2_out1));
  FDRE Logical2_out1_1_reg
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(Logical2_out1),
        .Q(Logical2_out1_1),
        .R(RSTP));
  FDRE \Pipeline2_out1_reg[0] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(\Pipeline2_out1_reg[15]_0 [0]),
        .Q(Pipeline2_out1[0]),
        .R(RSTP));
  FDRE \Pipeline2_out1_reg[10] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(\Pipeline2_out1_reg[15]_0 [10]),
        .Q(Pipeline2_out1[10]),
        .R(RSTP));
  FDRE \Pipeline2_out1_reg[11] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(\Pipeline2_out1_reg[15]_0 [11]),
        .Q(Pipeline2_out1[11]),
        .R(RSTP));
  FDRE \Pipeline2_out1_reg[12] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(\Pipeline2_out1_reg[15]_0 [12]),
        .Q(Pipeline2_out1[12]),
        .R(RSTP));
  FDRE \Pipeline2_out1_reg[13] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(\Pipeline2_out1_reg[15]_0 [13]),
        .Q(Pipeline2_out1[13]),
        .R(RSTP));
  FDRE \Pipeline2_out1_reg[14] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(\Pipeline2_out1_reg[15]_0 [14]),
        .Q(Pipeline2_out1[14]),
        .R(RSTP));
  FDRE \Pipeline2_out1_reg[15] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(\Pipeline2_out1_reg[15]_0 [15]),
        .Q(Pipeline2_out1[15]),
        .R(RSTP));
  FDRE \Pipeline2_out1_reg[1] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(\Pipeline2_out1_reg[15]_0 [1]),
        .Q(Pipeline2_out1[1]),
        .R(RSTP));
  FDRE \Pipeline2_out1_reg[2] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(\Pipeline2_out1_reg[15]_0 [2]),
        .Q(Pipeline2_out1[2]),
        .R(RSTP));
  FDRE \Pipeline2_out1_reg[3] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(\Pipeline2_out1_reg[15]_0 [3]),
        .Q(Pipeline2_out1[3]),
        .R(RSTP));
  FDRE \Pipeline2_out1_reg[4] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(\Pipeline2_out1_reg[15]_0 [4]),
        .Q(Pipeline2_out1[4]),
        .R(RSTP));
  FDRE \Pipeline2_out1_reg[5] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(\Pipeline2_out1_reg[15]_0 [5]),
        .Q(Pipeline2_out1[5]),
        .R(RSTP));
  FDRE \Pipeline2_out1_reg[6] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(\Pipeline2_out1_reg[15]_0 [6]),
        .Q(Pipeline2_out1[6]),
        .R(RSTP));
  FDRE \Pipeline2_out1_reg[7] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(\Pipeline2_out1_reg[15]_0 [7]),
        .Q(Pipeline2_out1[7]),
        .R(RSTP));
  FDRE \Pipeline2_out1_reg[8] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(\Pipeline2_out1_reg[15]_0 [8]),
        .Q(Pipeline2_out1[8]),
        .R(RSTP));
  FDRE \Pipeline2_out1_reg[9] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(\Pipeline2_out1_reg[15]_0 [9]),
        .Q(Pipeline2_out1[9]),
        .R(RSTP));
  FDRE \Pipeline3_out1_reg[0] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(\Pipeline3_out1_reg[15]_0 [0]),
        .Q(Pipeline3_out1[0]),
        .R(RSTP));
  FDRE \Pipeline3_out1_reg[10] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(\Pipeline3_out1_reg[15]_0 [10]),
        .Q(Pipeline3_out1[10]),
        .R(RSTP));
  FDRE \Pipeline3_out1_reg[11] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(\Pipeline3_out1_reg[15]_0 [11]),
        .Q(Pipeline3_out1[11]),
        .R(RSTP));
  FDRE \Pipeline3_out1_reg[12] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(\Pipeline3_out1_reg[15]_0 [12]),
        .Q(Pipeline3_out1[12]),
        .R(RSTP));
  FDRE \Pipeline3_out1_reg[13] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(\Pipeline3_out1_reg[15]_0 [13]),
        .Q(Pipeline3_out1[13]),
        .R(RSTP));
  FDRE \Pipeline3_out1_reg[14] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(\Pipeline3_out1_reg[15]_0 [14]),
        .Q(Pipeline3_out1[14]),
        .R(RSTP));
  FDRE \Pipeline3_out1_reg[15] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(\Pipeline3_out1_reg[15]_0 [15]),
        .Q(Pipeline3_out1[15]),
        .R(RSTP));
  FDRE \Pipeline3_out1_reg[1] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(\Pipeline3_out1_reg[15]_0 [1]),
        .Q(Pipeline3_out1[1]),
        .R(RSTP));
  FDRE \Pipeline3_out1_reg[2] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(\Pipeline3_out1_reg[15]_0 [2]),
        .Q(Pipeline3_out1[2]),
        .R(RSTP));
  FDRE \Pipeline3_out1_reg[3] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(\Pipeline3_out1_reg[15]_0 [3]),
        .Q(Pipeline3_out1[3]),
        .R(RSTP));
  FDRE \Pipeline3_out1_reg[4] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(\Pipeline3_out1_reg[15]_0 [4]),
        .Q(Pipeline3_out1[4]),
        .R(RSTP));
  FDRE \Pipeline3_out1_reg[5] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(\Pipeline3_out1_reg[15]_0 [5]),
        .Q(Pipeline3_out1[5]),
        .R(RSTP));
  FDRE \Pipeline3_out1_reg[6] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(\Pipeline3_out1_reg[15]_0 [6]),
        .Q(Pipeline3_out1[6]),
        .R(RSTP));
  FDRE \Pipeline3_out1_reg[7] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(\Pipeline3_out1_reg[15]_0 [7]),
        .Q(Pipeline3_out1[7]),
        .R(RSTP));
  FDRE \Pipeline3_out1_reg[8] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(\Pipeline3_out1_reg[15]_0 [8]),
        .Q(Pipeline3_out1[8]),
        .R(RSTP));
  FDRE \Pipeline3_out1_reg[9] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(\Pipeline3_out1_reg[15]_0 [9]),
        .Q(Pipeline3_out1[9]),
        .R(RSTP));
  FDRE \Pipeline4_out1_reg[0] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(\Pipeline4_out1_reg[23]_0 [0]),
        .Q(Pipeline4_out1[0]),
        .R(RSTP));
  FDRE \Pipeline4_out1_reg[10] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(\Pipeline4_out1_reg[23]_0 [10]),
        .Q(Pipeline4_out1[10]),
        .R(RSTP));
  FDRE \Pipeline4_out1_reg[11] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(\Pipeline4_out1_reg[23]_0 [11]),
        .Q(Pipeline4_out1[11]),
        .R(RSTP));
  FDRE \Pipeline4_out1_reg[12] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(\Pipeline4_out1_reg[23]_0 [12]),
        .Q(Pipeline4_out1[12]),
        .R(RSTP));
  FDRE \Pipeline4_out1_reg[13] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(\Pipeline4_out1_reg[23]_0 [13]),
        .Q(Pipeline4_out1[13]),
        .R(RSTP));
  FDRE \Pipeline4_out1_reg[14] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(\Pipeline4_out1_reg[23]_0 [14]),
        .Q(Pipeline4_out1[14]),
        .R(RSTP));
  FDRE \Pipeline4_out1_reg[15] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(\Pipeline4_out1_reg[23]_0 [15]),
        .Q(Pipeline4_out1[15]),
        .R(RSTP));
  FDRE \Pipeline4_out1_reg[16] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(\Pipeline4_out1_reg[23]_0 [16]),
        .Q(Pipeline4_out1[16]),
        .R(RSTP));
  FDRE \Pipeline4_out1_reg[17] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(\Pipeline4_out1_reg[23]_0 [17]),
        .Q(Pipeline4_out1[17]),
        .R(RSTP));
  FDRE \Pipeline4_out1_reg[18] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(\Pipeline4_out1_reg[23]_0 [18]),
        .Q(Pipeline4_out1[18]),
        .R(RSTP));
  FDRE \Pipeline4_out1_reg[19] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(\Pipeline4_out1_reg[23]_0 [19]),
        .Q(Pipeline4_out1[19]),
        .R(RSTP));
  FDRE \Pipeline4_out1_reg[1] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(\Pipeline4_out1_reg[23]_0 [1]),
        .Q(Pipeline4_out1[1]),
        .R(RSTP));
  FDRE \Pipeline4_out1_reg[20] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(\Pipeline4_out1_reg[23]_0 [20]),
        .Q(Pipeline4_out1[20]),
        .R(RSTP));
  FDRE \Pipeline4_out1_reg[21] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(\Pipeline4_out1_reg[23]_0 [21]),
        .Q(Pipeline4_out1[21]),
        .R(RSTP));
  FDRE \Pipeline4_out1_reg[22] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(\Pipeline4_out1_reg[23]_0 [22]),
        .Q(Pipeline4_out1[22]),
        .R(RSTP));
  FDRE \Pipeline4_out1_reg[23] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(\Pipeline4_out1_reg[23]_0 [23]),
        .Q(Pipeline4_out1[23]),
        .R(RSTP));
  FDRE \Pipeline4_out1_reg[2] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(\Pipeline4_out1_reg[23]_0 [2]),
        .Q(Pipeline4_out1[2]),
        .R(RSTP));
  FDRE \Pipeline4_out1_reg[3] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(\Pipeline4_out1_reg[23]_0 [3]),
        .Q(Pipeline4_out1[3]),
        .R(RSTP));
  FDRE \Pipeline4_out1_reg[4] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(\Pipeline4_out1_reg[23]_0 [4]),
        .Q(Pipeline4_out1[4]),
        .R(RSTP));
  FDRE \Pipeline4_out1_reg[5] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(\Pipeline4_out1_reg[23]_0 [5]),
        .Q(Pipeline4_out1[5]),
        .R(RSTP));
  FDRE \Pipeline4_out1_reg[6] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(\Pipeline4_out1_reg[23]_0 [6]),
        .Q(Pipeline4_out1[6]),
        .R(RSTP));
  FDRE \Pipeline4_out1_reg[7] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(\Pipeline4_out1_reg[23]_0 [7]),
        .Q(Pipeline4_out1[7]),
        .R(RSTP));
  FDRE \Pipeline4_out1_reg[8] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(\Pipeline4_out1_reg[23]_0 [8]),
        .Q(Pipeline4_out1[8]),
        .R(RSTP));
  FDRE \Pipeline4_out1_reg[9] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(\Pipeline4_out1_reg[23]_0 [9]),
        .Q(Pipeline4_out1[9]),
        .R(RSTP));
  FDRE \Pipeline6_out1_reg[0] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(\Pipeline6_out1_reg[31]_0 [0]),
        .Q(Pipeline6_out1[0]),
        .R(RSTP));
  FDRE \Pipeline6_out1_reg[10] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(\Pipeline6_out1_reg[31]_0 [10]),
        .Q(Pipeline6_out1[10]),
        .R(RSTP));
  FDRE \Pipeline6_out1_reg[11] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(\Pipeline6_out1_reg[31]_0 [11]),
        .Q(Pipeline6_out1[11]),
        .R(RSTP));
  FDRE \Pipeline6_out1_reg[12] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(\Pipeline6_out1_reg[31]_0 [12]),
        .Q(Pipeline6_out1[12]),
        .R(RSTP));
  FDRE \Pipeline6_out1_reg[13] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(\Pipeline6_out1_reg[31]_0 [13]),
        .Q(Pipeline6_out1[13]),
        .R(RSTP));
  FDRE \Pipeline6_out1_reg[14] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(\Pipeline6_out1_reg[31]_0 [14]),
        .Q(Pipeline6_out1[14]),
        .R(RSTP));
  FDRE \Pipeline6_out1_reg[15] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(\Pipeline6_out1_reg[31]_0 [15]),
        .Q(Pipeline6_out1[15]),
        .R(RSTP));
  FDRE \Pipeline6_out1_reg[16] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(\Pipeline6_out1_reg[31]_0 [16]),
        .Q(Pipeline6_out1[16]),
        .R(RSTP));
  FDRE \Pipeline6_out1_reg[17] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(\Pipeline6_out1_reg[31]_0 [17]),
        .Q(Pipeline6_out1[17]),
        .R(RSTP));
  FDRE \Pipeline6_out1_reg[18] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(\Pipeline6_out1_reg[31]_0 [18]),
        .Q(Pipeline6_out1[18]),
        .R(RSTP));
  FDRE \Pipeline6_out1_reg[19] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(\Pipeline6_out1_reg[31]_0 [19]),
        .Q(Pipeline6_out1[19]),
        .R(RSTP));
  FDRE \Pipeline6_out1_reg[1] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(\Pipeline6_out1_reg[31]_0 [1]),
        .Q(Pipeline6_out1[1]),
        .R(RSTP));
  FDRE \Pipeline6_out1_reg[20] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(\Pipeline6_out1_reg[31]_0 [20]),
        .Q(Pipeline6_out1[20]),
        .R(RSTP));
  FDRE \Pipeline6_out1_reg[21] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(\Pipeline6_out1_reg[31]_0 [21]),
        .Q(Pipeline6_out1[21]),
        .R(RSTP));
  FDRE \Pipeline6_out1_reg[22] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(\Pipeline6_out1_reg[31]_0 [22]),
        .Q(Pipeline6_out1[22]),
        .R(RSTP));
  FDRE \Pipeline6_out1_reg[23] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(\Pipeline6_out1_reg[31]_0 [23]),
        .Q(Pipeline6_out1[23]),
        .R(RSTP));
  FDRE \Pipeline6_out1_reg[24] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(\Pipeline6_out1_reg[31]_0 [24]),
        .Q(Pipeline6_out1[24]),
        .R(RSTP));
  FDRE \Pipeline6_out1_reg[25] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(\Pipeline6_out1_reg[31]_0 [25]),
        .Q(Pipeline6_out1[25]),
        .R(RSTP));
  FDRE \Pipeline6_out1_reg[26] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(\Pipeline6_out1_reg[31]_0 [26]),
        .Q(Pipeline6_out1[26]),
        .R(RSTP));
  FDRE \Pipeline6_out1_reg[27] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(\Pipeline6_out1_reg[31]_0 [27]),
        .Q(Pipeline6_out1[27]),
        .R(RSTP));
  FDRE \Pipeline6_out1_reg[28] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(\Pipeline6_out1_reg[31]_0 [28]),
        .Q(Pipeline6_out1[28]),
        .R(RSTP));
  FDRE \Pipeline6_out1_reg[29] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(\Pipeline6_out1_reg[31]_0 [29]),
        .Q(Pipeline6_out1[29]),
        .R(RSTP));
  FDRE \Pipeline6_out1_reg[2] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(\Pipeline6_out1_reg[31]_0 [2]),
        .Q(Pipeline6_out1[2]),
        .R(RSTP));
  FDRE \Pipeline6_out1_reg[30] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(\Pipeline6_out1_reg[31]_0 [30]),
        .Q(Pipeline6_out1[30]),
        .R(RSTP));
  FDRE \Pipeline6_out1_reg[31] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(\Pipeline6_out1_reg[31]_0 [31]),
        .Q(Pipeline6_out1[31]),
        .R(RSTP));
  FDRE \Pipeline6_out1_reg[3] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(\Pipeline6_out1_reg[31]_0 [3]),
        .Q(Pipeline6_out1[3]),
        .R(RSTP));
  FDRE \Pipeline6_out1_reg[4] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(\Pipeline6_out1_reg[31]_0 [4]),
        .Q(Pipeline6_out1[4]),
        .R(RSTP));
  FDRE \Pipeline6_out1_reg[5] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(\Pipeline6_out1_reg[31]_0 [5]),
        .Q(Pipeline6_out1[5]),
        .R(RSTP));
  FDRE \Pipeline6_out1_reg[6] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(\Pipeline6_out1_reg[31]_0 [6]),
        .Q(Pipeline6_out1[6]),
        .R(RSTP));
  FDRE \Pipeline6_out1_reg[7] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(\Pipeline6_out1_reg[31]_0 [7]),
        .Q(Pipeline6_out1[7]),
        .R(RSTP));
  FDRE \Pipeline6_out1_reg[8] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(\Pipeline6_out1_reg[31]_0 [8]),
        .Q(Pipeline6_out1[8]),
        .R(RSTP));
  FDRE \Pipeline6_out1_reg[9] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(\Pipeline6_out1_reg[31]_0 [9]),
        .Q(Pipeline6_out1[9]),
        .R(RSTP));
  FDRE \Pipeline7_out1_reg[0] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(Pipeline6_out1[0]),
        .Q(Pipeline7_out1[0]),
        .R(RSTP));
  FDRE \Pipeline7_out1_reg[10] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(Pipeline6_out1[10]),
        .Q(Pipeline7_out1[10]),
        .R(RSTP));
  FDRE \Pipeline7_out1_reg[11] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(Pipeline6_out1[11]),
        .Q(Pipeline7_out1[11]),
        .R(RSTP));
  FDRE \Pipeline7_out1_reg[12] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(Pipeline6_out1[12]),
        .Q(Pipeline7_out1[12]),
        .R(RSTP));
  FDRE \Pipeline7_out1_reg[13] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(Pipeline6_out1[13]),
        .Q(Pipeline7_out1[13]),
        .R(RSTP));
  FDRE \Pipeline7_out1_reg[14] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(Pipeline6_out1[14]),
        .Q(Pipeline7_out1[14]),
        .R(RSTP));
  FDRE \Pipeline7_out1_reg[15] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(Pipeline6_out1[15]),
        .Q(Pipeline7_out1[15]),
        .R(RSTP));
  FDRE \Pipeline7_out1_reg[16] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(Pipeline6_out1[16]),
        .Q(Pipeline7_out1[16]),
        .R(RSTP));
  FDRE \Pipeline7_out1_reg[17] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(Pipeline6_out1[17]),
        .Q(Pipeline7_out1[17]),
        .R(RSTP));
  FDRE \Pipeline7_out1_reg[18] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(Pipeline6_out1[18]),
        .Q(Pipeline7_out1[18]),
        .R(RSTP));
  FDRE \Pipeline7_out1_reg[19] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(Pipeline6_out1[19]),
        .Q(Pipeline7_out1[19]),
        .R(RSTP));
  FDRE \Pipeline7_out1_reg[1] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(Pipeline6_out1[1]),
        .Q(Pipeline7_out1[1]),
        .R(RSTP));
  FDRE \Pipeline7_out1_reg[20] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(Pipeline6_out1[20]),
        .Q(Pipeline7_out1[20]),
        .R(RSTP));
  FDRE \Pipeline7_out1_reg[21] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(Pipeline6_out1[21]),
        .Q(Pipeline7_out1[21]),
        .R(RSTP));
  FDRE \Pipeline7_out1_reg[22] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(Pipeline6_out1[22]),
        .Q(Pipeline7_out1[22]),
        .R(RSTP));
  FDRE \Pipeline7_out1_reg[23] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(Pipeline6_out1[23]),
        .Q(Pipeline7_out1[23]),
        .R(RSTP));
  FDRE \Pipeline7_out1_reg[24] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(Pipeline6_out1[24]),
        .Q(Pipeline7_out1[24]),
        .R(RSTP));
  FDRE \Pipeline7_out1_reg[25] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(Pipeline6_out1[25]),
        .Q(Pipeline7_out1[25]),
        .R(RSTP));
  FDRE \Pipeline7_out1_reg[26] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(Pipeline6_out1[26]),
        .Q(Pipeline7_out1[26]),
        .R(RSTP));
  FDRE \Pipeline7_out1_reg[27] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(Pipeline6_out1[27]),
        .Q(Pipeline7_out1[27]),
        .R(RSTP));
  FDRE \Pipeline7_out1_reg[28] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(Pipeline6_out1[28]),
        .Q(Pipeline7_out1[28]),
        .R(RSTP));
  FDRE \Pipeline7_out1_reg[29] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(Pipeline6_out1[29]),
        .Q(Pipeline7_out1[29]),
        .R(RSTP));
  FDRE \Pipeline7_out1_reg[2] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(Pipeline6_out1[2]),
        .Q(Pipeline7_out1[2]),
        .R(RSTP));
  FDRE \Pipeline7_out1_reg[30] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(Pipeline6_out1[30]),
        .Q(Pipeline7_out1[30]),
        .R(RSTP));
  FDRE \Pipeline7_out1_reg[31] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(Pipeline6_out1[31]),
        .Q(Pipeline7_out1[31]),
        .R(RSTP));
  FDRE \Pipeline7_out1_reg[3] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(Pipeline6_out1[3]),
        .Q(Pipeline7_out1[3]),
        .R(RSTP));
  FDRE \Pipeline7_out1_reg[4] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(Pipeline6_out1[4]),
        .Q(Pipeline7_out1[4]),
        .R(RSTP));
  FDRE \Pipeline7_out1_reg[5] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(Pipeline6_out1[5]),
        .Q(Pipeline7_out1[5]),
        .R(RSTP));
  FDRE \Pipeline7_out1_reg[6] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(Pipeline6_out1[6]),
        .Q(Pipeline7_out1[6]),
        .R(RSTP));
  FDRE \Pipeline7_out1_reg[7] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(Pipeline6_out1[7]),
        .Q(Pipeline7_out1[7]),
        .R(RSTP));
  FDRE \Pipeline7_out1_reg[8] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(Pipeline6_out1[8]),
        .Q(Pipeline7_out1[8]),
        .R(RSTP));
  FDRE \Pipeline7_out1_reg[9] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(Pipeline6_out1[9]),
        .Q(Pipeline7_out1[9]),
        .R(RSTP));
  FDRE \countPerPEriod_1_reg[0] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(countPerPEriod[0]),
        .Q(\countPerPEriod_1_reg[15]_0 [0]),
        .R(RSTP));
  FDRE \countPerPEriod_1_reg[10] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(countPerPEriod[10]),
        .Q(\countPerPEriod_1_reg[15]_0 [10]),
        .R(RSTP));
  FDRE \countPerPEriod_1_reg[11] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(countPerPEriod[11]),
        .Q(\countPerPEriod_1_reg[15]_0 [11]),
        .R(RSTP));
  FDRE \countPerPEriod_1_reg[12] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(countPerPEriod[12]),
        .Q(\countPerPEriod_1_reg[15]_0 [12]),
        .R(RSTP));
  FDRE \countPerPEriod_1_reg[13] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(countPerPEriod[13]),
        .Q(\countPerPEriod_1_reg[15]_0 [13]),
        .R(RSTP));
  FDRE \countPerPEriod_1_reg[14] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(countPerPEriod[14]),
        .Q(\countPerPEriod_1_reg[15]_0 [14]),
        .R(RSTP));
  FDRE \countPerPEriod_1_reg[15] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(countPerPEriod[15]),
        .Q(\countPerPEriod_1_reg[15]_0 [15]),
        .R(RSTP));
  FDRE \countPerPEriod_1_reg[1] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(countPerPEriod[1]),
        .Q(\countPerPEriod_1_reg[15]_0 [1]),
        .R(RSTP));
  FDRE \countPerPEriod_1_reg[2] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(countPerPEriod[2]),
        .Q(\countPerPEriod_1_reg[15]_0 [2]),
        .R(RSTP));
  FDRE \countPerPEriod_1_reg[3] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(countPerPEriod[3]),
        .Q(\countPerPEriod_1_reg[15]_0 [3]),
        .R(RSTP));
  FDRE \countPerPEriod_1_reg[4] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(countPerPEriod[4]),
        .Q(\countPerPEriod_1_reg[15]_0 [4]),
        .R(RSTP));
  FDRE \countPerPEriod_1_reg[5] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(countPerPEriod[5]),
        .Q(\countPerPEriod_1_reg[15]_0 [5]),
        .R(RSTP));
  FDRE \countPerPEriod_1_reg[6] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(countPerPEriod[6]),
        .Q(\countPerPEriod_1_reg[15]_0 [6]),
        .R(RSTP));
  FDRE \countPerPEriod_1_reg[7] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(countPerPEriod[7]),
        .Q(\countPerPEriod_1_reg[15]_0 [7]),
        .R(RSTP));
  FDRE \countPerPEriod_1_reg[8] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(countPerPEriod[8]),
        .Q(\countPerPEriod_1_reg[15]_0 [8]),
        .R(RSTP));
  FDRE \countPerPEriod_1_reg[9] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(countPerPEriod[9]),
        .Q(\countPerPEriod_1_reg[15]_0 [9]),
        .R(RSTP));
  (* SOFT_HLUTNM = "soft_lutpair185" *) 
  LUT2 #(
    .INIT(4'h6)) 
    count_2_i_1
       (.I0(B),
        .I1(A),
        .O(count_1));
  FDRE count_2_reg
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(count_1),
        .Q(count_2),
        .R(RSTP));
  FDRE count_reg
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(count_2),
        .Q(count),
        .R(RSTP));
  FDRE edge_rsvd_reg
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(u_Counter_n_2),
        .Q(edge_rsvd),
        .R(RSTP));
  FDRE \hold1_out1_reg[0] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(Check_Direction_out1[0]),
        .Q(hold1_out1[0]),
        .R(RSTP));
  FDRE \hold1_out1_reg[3] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(Check_Direction_out1[3]),
        .Q(hold1_out1[3]),
        .R(RSTP));
  FDRE \hold2_out1_reg[0] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(rps[14]),
        .Q(hold2_out1[0]),
        .R(RSTP));
  FDRE \hold2_out1_reg[10] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(rps[24]),
        .Q(hold2_out1[10]),
        .R(RSTP));
  FDRE \hold2_out1_reg[11] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(rps[25]),
        .Q(hold2_out1[11]),
        .R(RSTP));
  FDRE \hold2_out1_reg[12] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(rps[26]),
        .Q(hold2_out1[12]),
        .R(RSTP));
  FDRE \hold2_out1_reg[13] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(rps[27]),
        .Q(hold2_out1[13]),
        .R(RSTP));
  FDRE \hold2_out1_reg[14] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(rps[28]),
        .Q(hold2_out1[14]),
        .R(RSTP));
  FDRE \hold2_out1_reg[15] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(rps[29]),
        .Q(hold2_out1[15]),
        .R(RSTP));
  FDRE \hold2_out1_reg[16] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(rps[30]),
        .Q(hold2_out1[16]),
        .R(RSTP));
  FDRE \hold2_out1_reg[17] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(rps[31]),
        .Q(hold2_out1[17]),
        .R(RSTP));
  FDRE \hold2_out1_reg[18] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(rps[32]),
        .Q(hold2_out1[18]),
        .R(RSTP));
  FDRE \hold2_out1_reg[19] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(rps[33]),
        .Q(hold2_out1[19]),
        .R(RSTP));
  FDRE \hold2_out1_reg[1] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(rps[15]),
        .Q(hold2_out1[1]),
        .R(RSTP));
  FDRE \hold2_out1_reg[20] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(rps[34]),
        .Q(hold2_out1[20]),
        .R(RSTP));
  FDRE \hold2_out1_reg[21] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(rps[35]),
        .Q(hold2_out1[21]),
        .R(RSTP));
  FDRE \hold2_out1_reg[22] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(rps[36]),
        .Q(hold2_out1[22]),
        .R(RSTP));
  FDRE \hold2_out1_reg[2] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(rps[16]),
        .Q(hold2_out1[2]),
        .R(RSTP));
  FDRE \hold2_out1_reg[31] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(rps[37]),
        .Q(hold2_out1[31]),
        .R(RSTP));
  FDRE \hold2_out1_reg[3] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(rps[17]),
        .Q(hold2_out1[3]),
        .R(RSTP));
  FDRE \hold2_out1_reg[4] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(rps[18]),
        .Q(hold2_out1[4]),
        .R(RSTP));
  FDRE \hold2_out1_reg[5] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(rps[19]),
        .Q(hold2_out1[5]),
        .R(RSTP));
  FDRE \hold2_out1_reg[6] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(rps[20]),
        .Q(hold2_out1[6]),
        .R(RSTP));
  FDRE \hold2_out1_reg[7] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(rps[21]),
        .Q(hold2_out1[7]),
        .R(RSTP));
  FDRE \hold2_out1_reg[8] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(rps[22]),
        .Q(hold2_out1[8]),
        .R(RSTP));
  FDRE \hold2_out1_reg[9] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(rps[23]),
        .Q(hold2_out1[9]),
        .R(RSTP));
  FDRE \hold5_out1_1_reg[0] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(hold5_out1[0]),
        .Q(OverSamplFactor[0]),
        .R(RSTP));
  FDRE \hold5_out1_1_reg[10] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(hold5_out1[10]),
        .Q(OverSamplFactor[10]),
        .R(RSTP));
  FDRE \hold5_out1_1_reg[11] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(hold5_out1[11]),
        .Q(OverSamplFactor[11]),
        .R(RSTP));
  FDRE \hold5_out1_1_reg[12] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(hold5_out1[12]),
        .Q(OverSamplFactor[12]),
        .R(RSTP));
  FDRE \hold5_out1_1_reg[13] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(hold5_out1[13]),
        .Q(OverSamplFactor[13]),
        .R(RSTP));
  FDRE \hold5_out1_1_reg[14] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(hold5_out1[14]),
        .Q(OverSamplFactor[14]),
        .R(RSTP));
  FDRE \hold5_out1_1_reg[15] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(hold5_out1[15]),
        .Q(OverSamplFactor[15]),
        .R(RSTP));
  FDRE \hold5_out1_1_reg[1] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(hold5_out1[1]),
        .Q(OverSamplFactor[1]),
        .R(RSTP));
  FDRE \hold5_out1_1_reg[2] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(hold5_out1[2]),
        .Q(OverSamplFactor[2]),
        .R(RSTP));
  FDRE \hold5_out1_1_reg[3] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(hold5_out1[3]),
        .Q(OverSamplFactor[3]),
        .R(RSTP));
  FDRE \hold5_out1_1_reg[4] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(hold5_out1[4]),
        .Q(OverSamplFactor[4]),
        .R(RSTP));
  FDRE \hold5_out1_1_reg[5] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(hold5_out1[5]),
        .Q(OverSamplFactor[5]),
        .R(RSTP));
  FDRE \hold5_out1_1_reg[6] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(hold5_out1[6]),
        .Q(OverSamplFactor[6]),
        .R(RSTP));
  FDRE \hold5_out1_1_reg[7] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(hold5_out1[7]),
        .Q(OverSamplFactor[7]),
        .R(RSTP));
  FDRE \hold5_out1_1_reg[8] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(hold5_out1[8]),
        .Q(OverSamplFactor[8]),
        .R(RSTP));
  FDRE \hold5_out1_1_reg[9] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(hold5_out1[9]),
        .Q(OverSamplFactor[9]),
        .R(RSTP));
  FDRE \hold5_out1_reg[0] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(omega_by_measure_time_out2[0]),
        .Q(hold5_out1[0]),
        .R(RSTP));
  FDRE \hold5_out1_reg[10] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(omega_by_measure_time_out2[10]),
        .Q(hold5_out1[10]),
        .R(RSTP));
  FDRE \hold5_out1_reg[11] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(omega_by_measure_time_out2[11]),
        .Q(hold5_out1[11]),
        .R(RSTP));
  FDRE \hold5_out1_reg[12] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(omega_by_measure_time_out2[12]),
        .Q(hold5_out1[12]),
        .R(RSTP));
  FDRE \hold5_out1_reg[13] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(omega_by_measure_time_out2[13]),
        .Q(hold5_out1[13]),
        .R(RSTP));
  FDRE \hold5_out1_reg[14] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(omega_by_measure_time_out2[14]),
        .Q(hold5_out1[14]),
        .R(RSTP));
  FDRE \hold5_out1_reg[15] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(omega_by_measure_time_out2[15]),
        .Q(hold5_out1[15]),
        .R(RSTP));
  FDRE \hold5_out1_reg[1] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(omega_by_measure_time_out2[1]),
        .Q(hold5_out1[1]),
        .R(RSTP));
  FDRE \hold5_out1_reg[2] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(omega_by_measure_time_out2[2]),
        .Q(hold5_out1[2]),
        .R(RSTP));
  FDRE \hold5_out1_reg[3] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(omega_by_measure_time_out2[3]),
        .Q(hold5_out1[3]),
        .R(RSTP));
  FDRE \hold5_out1_reg[4] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(omega_by_measure_time_out2[4]),
        .Q(hold5_out1[4]),
        .R(RSTP));
  FDRE \hold5_out1_reg[5] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(omega_by_measure_time_out2[5]),
        .Q(hold5_out1[5]),
        .R(RSTP));
  FDRE \hold5_out1_reg[6] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(omega_by_measure_time_out2[6]),
        .Q(hold5_out1[6]),
        .R(RSTP));
  FDRE \hold5_out1_reg[7] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(omega_by_measure_time_out2[7]),
        .Q(hold5_out1[7]),
        .R(RSTP));
  FDRE \hold5_out1_reg[8] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(omega_by_measure_time_out2[8]),
        .Q(hold5_out1[8]),
        .R(RSTP));
  FDRE \hold5_out1_reg[9] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(omega_by_measure_time_out2[9]),
        .Q(hold5_out1[9]),
        .R(RSTP));
  (* SOFT_HLUTNM = "soft_lutpair174" *) 
  LUT2 #(
    .INIT(4'h8)) 
    \omega_oversampled[0]_i_1 
       (.I0(\omega_oversampled[22]_i_4_n_0 ),
        .I1(Div_i1_mul_temp_n_104),
        .O(\omega_oversampled[0]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair179" *) 
  LUT2 #(
    .INIT(4'h8)) 
    \omega_oversampled[10]_i_1 
       (.I0(\omega_oversampled[22]_i_4_n_0 ),
        .I1(Div_i1_mul_temp_n_94),
        .O(\omega_oversampled[10]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair179" *) 
  LUT2 #(
    .INIT(4'h8)) 
    \omega_oversampled[11]_i_1 
       (.I0(\omega_oversampled[22]_i_4_n_0 ),
        .I1(Div_i1_mul_temp_n_93),
        .O(\omega_oversampled[11]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair180" *) 
  LUT2 #(
    .INIT(4'h8)) 
    \omega_oversampled[12]_i_1 
       (.I0(\omega_oversampled[22]_i_4_n_0 ),
        .I1(Div_i1_mul_temp_n_92),
        .O(\omega_oversampled[12]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair180" *) 
  LUT2 #(
    .INIT(4'h8)) 
    \omega_oversampled[13]_i_1 
       (.I0(\omega_oversampled[22]_i_4_n_0 ),
        .I1(Div_i1_mul_temp_n_91),
        .O(\omega_oversampled[13]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair181" *) 
  LUT2 #(
    .INIT(4'h8)) 
    \omega_oversampled[14]_i_1 
       (.I0(\omega_oversampled[22]_i_4_n_0 ),
        .I1(Div_i1_mul_temp_n_90),
        .O(\omega_oversampled[14]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair181" *) 
  LUT2 #(
    .INIT(4'h8)) 
    \omega_oversampled[15]_i_1 
       (.I0(\omega_oversampled[22]_i_4_n_0 ),
        .I1(Div_i1_mul_temp_n_89),
        .O(\omega_oversampled[15]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair182" *) 
  LUT2 #(
    .INIT(4'h8)) 
    \omega_oversampled[16]_i_1 
       (.I0(\omega_oversampled[22]_i_4_n_0 ),
        .I1(Div_i1_mul_temp_n_88),
        .O(\omega_oversampled[16]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair182" *) 
  LUT2 #(
    .INIT(4'h8)) 
    \omega_oversampled[17]_i_1 
       (.I0(\omega_oversampled[22]_i_4_n_0 ),
        .I1(Div_i1_mul_temp_n_87),
        .O(\omega_oversampled[17]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair183" *) 
  LUT2 #(
    .INIT(4'h8)) 
    \omega_oversampled[18]_i_1 
       (.I0(\omega_oversampled[22]_i_4_n_0 ),
        .I1(Div_i1_mul_temp_n_86),
        .O(\omega_oversampled[18]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair183" *) 
  LUT2 #(
    .INIT(4'h8)) 
    \omega_oversampled[19]_i_1 
       (.I0(\omega_oversampled[22]_i_4_n_0 ),
        .I1(Div_i1_mul_temp_n_85),
        .O(\omega_oversampled[19]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair174" *) 
  LUT2 #(
    .INIT(4'h8)) 
    \omega_oversampled[1]_i_1 
       (.I0(\omega_oversampled[22]_i_4_n_0 ),
        .I1(Div_i1_mul_temp_n_103),
        .O(\omega_oversampled[1]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair184" *) 
  LUT2 #(
    .INIT(4'h8)) 
    \omega_oversampled[20]_i_1 
       (.I0(\omega_oversampled[22]_i_4_n_0 ),
        .I1(Div_i1_mul_temp_n_84),
        .O(\omega_oversampled[20]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair184" *) 
  LUT2 #(
    .INIT(4'h8)) 
    \omega_oversampled[21]_i_1 
       (.I0(\omega_oversampled[22]_i_4_n_0 ),
        .I1(Div_i1_mul_temp_n_83),
        .O(\omega_oversampled[21]_i_1_n_0 ));
  LUT4 #(
    .INIT(16'h8000)) 
    \omega_oversampled[22]_i_10 
       (.I0(p_0_in__0[10]),
        .I1(p_0_in__0[9]),
        .I2(p_0_in__0[8]),
        .I3(p_0_in__0[7]),
        .O(\omega_oversampled[22]_i_10_n_0 ));
  LUT4 #(
    .INIT(16'h8000)) 
    \omega_oversampled[22]_i_11 
       (.I0(p_0_in__0[14]),
        .I1(p_0_in__0[13]),
        .I2(p_0_in__0[12]),
        .I3(p_0_in__0[11]),
        .O(\omega_oversampled[22]_i_11_n_0 ));
  LUT2 #(
    .INIT(4'h8)) 
    \omega_oversampled[22]_i_2 
       (.I0(\omega_oversampled[22]_i_4_n_0 ),
        .I1(Div_i1_mul_temp_n_82),
        .O(\omega_oversampled[22]_i_2_n_0 ));
  LUT6 #(
    .INIT(64'hFFFFFFFFFFFFFFFE)) 
    \omega_oversampled[22]_i_3 
       (.I0(\omega_oversampled[22]_i_5_n_0 ),
        .I1(\omega_oversampled[22]_i_6_n_0 ),
        .I2(p_0_in__0[14]),
        .I3(p_0_in__0[13]),
        .I4(p_0_in__0[0]),
        .I5(\omega_oversampled[22]_i_7_n_0 ),
        .O(\omega_oversampled[22]_i_3_n_0 ));
  LUT6 #(
    .INIT(64'h00000000D5555555)) 
    \omega_oversampled[22]_i_4 
       (.I0(p_0_in),
        .I1(\omega_oversampled[22]_i_8_n_0 ),
        .I2(\omega_oversampled[22]_i_9_n_0 ),
        .I3(\omega_oversampled[22]_i_10_n_0 ),
        .I4(\omega_oversampled[22]_i_11_n_0 ),
        .I5(RSTP),
        .O(\omega_oversampled[22]_i_4_n_0 ));
  LUT4 #(
    .INIT(16'hFFFE)) 
    \omega_oversampled[22]_i_5 
       (.I0(p_0_in__0[6]),
        .I1(p_0_in__0[5]),
        .I2(p_0_in__0[8]),
        .I3(p_0_in__0[7]),
        .O(\omega_oversampled[22]_i_5_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair173" *) 
  LUT4 #(
    .INIT(16'hFFFE)) 
    \omega_oversampled[22]_i_6 
       (.I0(p_0_in__0[2]),
        .I1(p_0_in__0[1]),
        .I2(p_0_in__0[4]),
        .I3(p_0_in__0[3]),
        .O(\omega_oversampled[22]_i_6_n_0 ));
  LUT4 #(
    .INIT(16'hFFFE)) 
    \omega_oversampled[22]_i_7 
       (.I0(p_0_in__0[10]),
        .I1(p_0_in__0[9]),
        .I2(p_0_in__0[12]),
        .I3(p_0_in__0[11]),
        .O(\omega_oversampled[22]_i_7_n_0 ));
  LUT4 #(
    .INIT(16'h8000)) 
    \omega_oversampled[22]_i_8 
       (.I0(p_0_in__0[6]),
        .I1(p_0_in__0[5]),
        .I2(p_0_in__0[4]),
        .I3(p_0_in__0[3]),
        .O(\omega_oversampled[22]_i_8_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair173" *) 
  LUT3 #(
    .INIT(8'h80)) 
    \omega_oversampled[22]_i_9 
       (.I0(p_0_in__0[2]),
        .I1(p_0_in__0[1]),
        .I2(p_0_in__0[0]),
        .O(\omega_oversampled[22]_i_9_n_0 ));
  LUT2 #(
    .INIT(4'h2)) 
    \omega_oversampled[23]_i_2 
       (.I0(p_0_in),
        .I1(RSTP),
        .O(omega_oversampled));
  (* SOFT_HLUTNM = "soft_lutpair175" *) 
  LUT2 #(
    .INIT(4'h8)) 
    \omega_oversampled[2]_i_1 
       (.I0(\omega_oversampled[22]_i_4_n_0 ),
        .I1(Div_i1_mul_temp_n_102),
        .O(\omega_oversampled[2]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair175" *) 
  LUT2 #(
    .INIT(4'h8)) 
    \omega_oversampled[3]_i_1 
       (.I0(\omega_oversampled[22]_i_4_n_0 ),
        .I1(Div_i1_mul_temp_n_101),
        .O(\omega_oversampled[3]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair176" *) 
  LUT2 #(
    .INIT(4'h8)) 
    \omega_oversampled[4]_i_1 
       (.I0(\omega_oversampled[22]_i_4_n_0 ),
        .I1(Div_i1_mul_temp_n_100),
        .O(\omega_oversampled[4]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair176" *) 
  LUT2 #(
    .INIT(4'h8)) 
    \omega_oversampled[5]_i_1 
       (.I0(\omega_oversampled[22]_i_4_n_0 ),
        .I1(Div_i1_mul_temp_n_99),
        .O(\omega_oversampled[5]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair177" *) 
  LUT2 #(
    .INIT(4'h8)) 
    \omega_oversampled[6]_i_1 
       (.I0(\omega_oversampled[22]_i_4_n_0 ),
        .I1(Div_i1_mul_temp_n_98),
        .O(\omega_oversampled[6]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair177" *) 
  LUT2 #(
    .INIT(4'h8)) 
    \omega_oversampled[7]_i_1 
       (.I0(\omega_oversampled[22]_i_4_n_0 ),
        .I1(Div_i1_mul_temp_n_97),
        .O(\omega_oversampled[7]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair178" *) 
  LUT2 #(
    .INIT(4'h8)) 
    \omega_oversampled[8]_i_1 
       (.I0(\omega_oversampled[22]_i_4_n_0 ),
        .I1(Div_i1_mul_temp_n_96),
        .O(\omega_oversampled[8]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair178" *) 
  LUT2 #(
    .INIT(4'h8)) 
    \omega_oversampled[9]_i_1 
       (.I0(\omega_oversampled[22]_i_4_n_0 ),
        .I1(Div_i1_mul_temp_n_95),
        .O(\omega_oversampled[9]_i_1_n_0 ));
  FDSE \omega_oversampled_reg[0] 
       (.C(IPCORE_CLK),
        .CE(\reset_old4_out1_reg[0] ),
        .D(\omega_oversampled[0]_i_1_n_0 ),
        .Q(D[0]),
        .S(u_IncreEncoder_V24_tc_n_5));
  FDSE \omega_oversampled_reg[10] 
       (.C(IPCORE_CLK),
        .CE(\reset_old4_out1_reg[0] ),
        .D(\omega_oversampled[10]_i_1_n_0 ),
        .Q(D[10]),
        .S(u_IncreEncoder_V24_tc_n_5));
  FDSE \omega_oversampled_reg[11] 
       (.C(IPCORE_CLK),
        .CE(\reset_old4_out1_reg[0] ),
        .D(\omega_oversampled[11]_i_1_n_0 ),
        .Q(D[11]),
        .S(u_IncreEncoder_V24_tc_n_5));
  FDSE \omega_oversampled_reg[12] 
       (.C(IPCORE_CLK),
        .CE(\reset_old4_out1_reg[0] ),
        .D(\omega_oversampled[12]_i_1_n_0 ),
        .Q(D[12]),
        .S(u_IncreEncoder_V24_tc_n_5));
  FDSE \omega_oversampled_reg[13] 
       (.C(IPCORE_CLK),
        .CE(\reset_old4_out1_reg[0] ),
        .D(\omega_oversampled[13]_i_1_n_0 ),
        .Q(D[13]),
        .S(u_IncreEncoder_V24_tc_n_5));
  FDSE \omega_oversampled_reg[14] 
       (.C(IPCORE_CLK),
        .CE(\reset_old4_out1_reg[0] ),
        .D(\omega_oversampled[14]_i_1_n_0 ),
        .Q(D[14]),
        .S(u_IncreEncoder_V24_tc_n_5));
  FDSE \omega_oversampled_reg[15] 
       (.C(IPCORE_CLK),
        .CE(\reset_old4_out1_reg[0] ),
        .D(\omega_oversampled[15]_i_1_n_0 ),
        .Q(D[15]),
        .S(u_IncreEncoder_V24_tc_n_5));
  FDSE \omega_oversampled_reg[16] 
       (.C(IPCORE_CLK),
        .CE(\reset_old4_out1_reg[0] ),
        .D(\omega_oversampled[16]_i_1_n_0 ),
        .Q(D[16]),
        .S(u_IncreEncoder_V24_tc_n_5));
  FDSE \omega_oversampled_reg[17] 
       (.C(IPCORE_CLK),
        .CE(\reset_old4_out1_reg[0] ),
        .D(\omega_oversampled[17]_i_1_n_0 ),
        .Q(D[17]),
        .S(u_IncreEncoder_V24_tc_n_5));
  FDSE \omega_oversampled_reg[18] 
       (.C(IPCORE_CLK),
        .CE(\reset_old4_out1_reg[0] ),
        .D(\omega_oversampled[18]_i_1_n_0 ),
        .Q(D[18]),
        .S(u_IncreEncoder_V24_tc_n_5));
  FDSE \omega_oversampled_reg[19] 
       (.C(IPCORE_CLK),
        .CE(\reset_old4_out1_reg[0] ),
        .D(\omega_oversampled[19]_i_1_n_0 ),
        .Q(D[19]),
        .S(u_IncreEncoder_V24_tc_n_5));
  FDSE \omega_oversampled_reg[1] 
       (.C(IPCORE_CLK),
        .CE(\reset_old4_out1_reg[0] ),
        .D(\omega_oversampled[1]_i_1_n_0 ),
        .Q(D[1]),
        .S(u_IncreEncoder_V24_tc_n_5));
  FDSE \omega_oversampled_reg[20] 
       (.C(IPCORE_CLK),
        .CE(\reset_old4_out1_reg[0] ),
        .D(\omega_oversampled[20]_i_1_n_0 ),
        .Q(D[20]),
        .S(u_IncreEncoder_V24_tc_n_5));
  FDSE \omega_oversampled_reg[21] 
       (.C(IPCORE_CLK),
        .CE(\reset_old4_out1_reg[0] ),
        .D(\omega_oversampled[21]_i_1_n_0 ),
        .Q(D[21]),
        .S(u_IncreEncoder_V24_tc_n_5));
  FDSE \omega_oversampled_reg[22] 
       (.C(IPCORE_CLK),
        .CE(\reset_old4_out1_reg[0] ),
        .D(\omega_oversampled[22]_i_2_n_0 ),
        .Q(D[22]),
        .S(u_IncreEncoder_V24_tc_n_5));
  FDRE \omega_oversampled_reg[23] 
       (.C(IPCORE_CLK),
        .CE(\reset_old4_out1_reg[0] ),
        .D(omega_oversampled),
        .Q(Q),
        .R(1'b0));
  FDSE \omega_oversampled_reg[2] 
       (.C(IPCORE_CLK),
        .CE(\reset_old4_out1_reg[0] ),
        .D(\omega_oversampled[2]_i_1_n_0 ),
        .Q(D[2]),
        .S(u_IncreEncoder_V24_tc_n_5));
  FDSE \omega_oversampled_reg[3] 
       (.C(IPCORE_CLK),
        .CE(\reset_old4_out1_reg[0] ),
        .D(\omega_oversampled[3]_i_1_n_0 ),
        .Q(D[3]),
        .S(u_IncreEncoder_V24_tc_n_5));
  FDSE \omega_oversampled_reg[4] 
       (.C(IPCORE_CLK),
        .CE(\reset_old4_out1_reg[0] ),
        .D(\omega_oversampled[4]_i_1_n_0 ),
        .Q(D[4]),
        .S(u_IncreEncoder_V24_tc_n_5));
  FDSE \omega_oversampled_reg[5] 
       (.C(IPCORE_CLK),
        .CE(\reset_old4_out1_reg[0] ),
        .D(\omega_oversampled[5]_i_1_n_0 ),
        .Q(D[5]),
        .S(u_IncreEncoder_V24_tc_n_5));
  FDSE \omega_oversampled_reg[6] 
       (.C(IPCORE_CLK),
        .CE(\reset_old4_out1_reg[0] ),
        .D(\omega_oversampled[6]_i_1_n_0 ),
        .Q(D[6]),
        .S(u_IncreEncoder_V24_tc_n_5));
  FDSE \omega_oversampled_reg[7] 
       (.C(IPCORE_CLK),
        .CE(\reset_old4_out1_reg[0] ),
        .D(\omega_oversampled[7]_i_1_n_0 ),
        .Q(D[7]),
        .S(u_IncreEncoder_V24_tc_n_5));
  FDSE \omega_oversampled_reg[8] 
       (.C(IPCORE_CLK),
        .CE(\reset_old4_out1_reg[0] ),
        .D(\omega_oversampled[8]_i_1_n_0 ),
        .Q(D[8]),
        .S(u_IncreEncoder_V24_tc_n_5));
  FDSE \omega_oversampled_reg[9] 
       (.C(IPCORE_CLK),
        .CE(\reset_old4_out1_reg[0] ),
        .D(\omega_oversampled[9]_i_1_n_0 ),
        .Q(D[9]),
        .S(u_IncreEncoder_V24_tc_n_5));
  FDRE \position_tmp_reg[0] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(count_mech[0]),
        .Q(position[0]),
        .R(RSTP));
  FDRE \position_tmp_reg[10] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(count_mech[10]),
        .Q(position[10]),
        .R(RSTP));
  FDRE \position_tmp_reg[11] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(count_mech[11]),
        .Q(position[11]),
        .R(RSTP));
  FDRE \position_tmp_reg[12] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(count_mech[12]),
        .Q(position[12]),
        .R(RSTP));
  FDRE \position_tmp_reg[13] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(count_mech[13]),
        .Q(position[13]),
        .R(RSTP));
  FDRE \position_tmp_reg[14] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(count_mech[14]),
        .Q(position[14]),
        .R(RSTP));
  FDRE \position_tmp_reg[15] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(count_mech[15]),
        .Q(position[15]),
        .R(RSTP));
  FDRE \position_tmp_reg[1] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(count_mech[1]),
        .Q(position[1]),
        .R(RSTP));
  FDRE \position_tmp_reg[2] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(count_mech[2]),
        .Q(position[2]),
        .R(RSTP));
  FDRE \position_tmp_reg[3] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(count_mech[3]),
        .Q(position[3]),
        .R(RSTP));
  FDRE \position_tmp_reg[4] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(count_mech[4]),
        .Q(position[4]),
        .R(RSTP));
  FDRE \position_tmp_reg[5] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(count_mech[5]),
        .Q(position[5]),
        .R(RSTP));
  FDRE \position_tmp_reg[6] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(count_mech[6]),
        .Q(position[6]),
        .R(RSTP));
  FDRE \position_tmp_reg[7] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(count_mech[7]),
        .Q(position[7]),
        .R(RSTP));
  FDRE \position_tmp_reg[8] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(count_mech[8]),
        .Q(position[8]),
        .R(RSTP));
  FDRE \position_tmp_reg[9] 
       (.C(IPCORE_CLK),
        .CE(enb_1_100_0),
        .D(count_mech[9]),
        .Q(position[9]),
        .R(RSTP));
  (* KEEP_HIERARCHY = "yes" *) 
  DSP48E2 #(
    .ACASCREG(1),
    .ADREG(1),
    .ALUMODEREG(0),
    .AMULTSEL("A"),
    .AREG(1),
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
    .PREG(1),
    .RND(48'h000000000000),
    .SEL_MASK("MASK"),
    .SEL_PATTERN("PATTERN"),
    .USE_MULT("MULTIPLY"),
    .USE_PATTERN_DETECT("NO_PATDET"),
    .USE_SIMD("ONE48"),
    .USE_WIDEXOR("FALSE"),
    .XORSIMD("XOR24_48_96")) 
    theta_el_tmp_reg
       (.A({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,DSP_ALU_INST}),
        .ACIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .ACOUT(NLW_theta_el_tmp_reg_ACOUT_UNCONNECTED[29:0]),
        .ALUMODE({1'b0,1'b0,1'b0,1'b0}),
        .B({count_el[15],count_el[15],count_el}),
        .BCIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .BCOUT(NLW_theta_el_tmp_reg_BCOUT_UNCONNECTED[17:0]),
        .C({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .CARRYCASCIN(1'b0),
        .CARRYCASCOUT(NLW_theta_el_tmp_reg_CARRYCASCOUT_UNCONNECTED),
        .CARRYIN(1'b0),
        .CARRYINSEL({1'b0,1'b0,1'b0}),
        .CARRYOUT(NLW_theta_el_tmp_reg_CARRYOUT_UNCONNECTED[3:0]),
        .CEA1(1'b0),
        .CEA2(enb_1_100_0),
        .CEAD(1'b0),
        .CEALUMODE(1'b0),
        .CEB1(1'b0),
        .CEB2(enb_1_100_0),
        .CEC(1'b0),
        .CECARRYIN(1'b0),
        .CECTRL(1'b0),
        .CED(1'b0),
        .CEINMODE(1'b0),
        .CEM(1'b0),
        .CEP(enb_1_100_0),
        .CLK(IPCORE_CLK),
        .D({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .INMODE({1'b0,1'b0,1'b0,1'b0,1'b0}),
        .MULTSIGNIN(1'b0),
        .MULTSIGNOUT(NLW_theta_el_tmp_reg_MULTSIGNOUT_UNCONNECTED),
        .OPMODE({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b1,1'b0,1'b1}),
        .OVERFLOW(NLW_theta_el_tmp_reg_OVERFLOW_UNCONNECTED),
        .P({NLW_theta_el_tmp_reg_P_UNCONNECTED[47:28],theta_el,theta_el_tmp_reg_n_102,theta_el_tmp_reg_n_103,theta_el_tmp_reg_n_104,theta_el_tmp_reg_n_105}),
        .PATTERNBDETECT(NLW_theta_el_tmp_reg_PATTERNBDETECT_UNCONNECTED),
        .PATTERNDETECT(NLW_theta_el_tmp_reg_PATTERNDETECT_UNCONNECTED),
        .PCIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .PCOUT(NLW_theta_el_tmp_reg_PCOUT_UNCONNECTED[47:0]),
        .RSTA(RSTP),
        .RSTALLCARRYIN(1'b0),
        .RSTALUMODE(1'b0),
        .RSTB(RSTP),
        .RSTC(1'b0),
        .RSTCTRL(1'b0),
        .RSTD(1'b0),
        .RSTINMODE(1'b0),
        .RSTM(1'b0),
        .RSTP(RSTP),
        .UNDERFLOW(NLW_theta_el_tmp_reg_UNDERFLOW_UNCONNECTED),
        .XOROUT(NLW_theta_el_tmp_reg_XOROUT_UNCONNECTED[7:0]));
  zusys_IncreEncoder_V24_ip_0_0_IncreEncoder_V24_ip_src_Check_Direction u_Check_Direction
       (.A(A),
        .B(B),
        .CEP(enb_1_100_0),
        .\Dir_tmp_reg[0]_0 (phase_0_reg),
        .IPCORE_CLK(IPCORE_CLK),
        .Q({Check_Direction_out1[3],Check_Direction_out1[0]}),
        .RSTP(RSTP),
        .count_old1_out1_reg_0(u_Check_Direction_n_0),
        .count_old1_out1_reg_1(u_IncreEncoder_V24_tc_n_8),
        .count_old_out1_reg_0(u_Check_Direction_n_1),
        .count_old_out1_reg_1(u_IncreEncoder_V24_tc_n_7),
        .write_axi_enable(write_axi_enable));
  zusys_IncreEncoder_V24_ip_0_0_IncreEncoder_V24_ip_src_Counter u_Counter
       (.DI({speed_old_switch1_out1,u_Counter_n_4,u_Counter_n_5,u_Counter_n_6,u_Counter_n_7,u_Counter_n_8,u_Counter_n_9}),
        .I(I),
        .IPCORE_CLK(IPCORE_CLK),
        .I_0(u_Counter_n_10),
        .I_1(u_Counter_n_11),
        .RSTP(RSTP),
        .count_2(count_2),
        .count_2_reg(u_Counter_n_2),
        .count_2_reg_0({u_Counter_n_12,u_Counter_n_13,u_Counter_n_14,u_Counter_n_15,u_Counter_n_16,u_Counter_n_17,u_Counter_n_18}),
        .count_2_reg_1({u_Counter_n_19,u_Counter_n_20,u_Counter_n_21,u_Counter_n_22,u_Counter_n_23,u_Counter_n_24,u_Counter_n_25}),
        .count_2_reg_2({u_Counter_n_26,u_Counter_n_27,u_Counter_n_28,u_Counter_n_29,u_Counter_n_30,u_Counter_n_31,u_Counter_n_32}),
        .reset_old1_out1(reset_old1_out1),
        .reset_old1_out1_reg_0(u_IncreEncoder_V24_tc_n_4),
        .reset_old3_out1(reset_old3_out1),
        .reset_old3_out1_0(reset_old3_out1_0),
        .reset_old4_out1(reset_old4_out1),
        .reset_old_out1(reset_old_out1),
        .reset_old_out1_reg_0(u_IncreEncoder_V24_tc_n_3));
  zusys_IncreEncoder_V24_ip_0_0_IncreEncoder_V24_ip_src_Counter_position u_Counter_position
       (.CEP(enb_1_100_0),
        .DI({u_Counter_n_26,u_Counter_n_27,u_Counter_n_28,u_Counter_n_29,u_Counter_n_30,u_Counter_n_31,u_Counter_n_32,position[0]}),
        .I(I),
        .IPCORE_CLK(IPCORE_CLK),
        .Q(Pipeline3_out1),
        .RSTP(RSTP),
        .S({u_Counter_theta_ele_n_30,u_Counter_theta_ele_n_31,u_Counter_theta_ele_n_32,u_Counter_theta_ele_n_33,u_Counter_theta_ele_n_34,u_Counter_theta_ele_n_35,u_Counter_theta_ele_n_36,u_Counter_theta_ele_n_37}),
        .count_mech(count_mech),
        .\position_tmp_reg[0] (u_Counter_theta_ele_n_29),
        .\position_tmp_reg[15] ({speed_old_switch1_out1,u_Counter_n_4,u_Counter_n_5,u_Counter_n_6,u_Counter_n_7,u_Counter_n_8,u_Counter_n_9}),
        .\position_tmp_reg[15]_0 ({u_Counter_theta_ele_n_4,u_Counter_theta_ele_n_5,u_Counter_theta_ele_n_6,u_Counter_theta_ele_n_7,u_Counter_theta_ele_n_8,u_Counter_theta_ele_n_9,u_Counter_theta_ele_n_10,u_Counter_theta_ele_n_11}),
        .reset_old2_out1(reset_old2_out1),
        .reset_old2_out1_reg_0(u_Counter_theta_ele_n_12),
        .reset_old3_out1(reset_old3_out1),
        .reset_old3_out10_carry_i_9_0(\reset_old5_out1_reg[3] ),
        .reset_old3_out10_carry_i_9_1(\reset_old5_out1_reg[0] ),
        .reset_old3_out1_reg_0(u_Counter_n_10),
        .reset_old_out1(reset_old_out1));
  zusys_IncreEncoder_V24_ip_0_0_IncreEncoder_V24_ip_src_Counter_theta_ele u_Counter_theta_ele
       (.CEP(enb_1_100_0),
        .D(count_el),
        .I(I),
        .IPCORE_CLK(IPCORE_CLK),
        .I_0(u_Counter_theta_ele_n_12),
        .Q({hold1_out1[3],hold1_out1[0]}),
        .RSTP(RSTP),
        .S({u_Counter_theta_ele_n_30,u_Counter_theta_ele_n_31,u_Counter_theta_ele_n_32,u_Counter_theta_ele_n_33,u_Counter_theta_ele_n_34,u_Counter_theta_ele_n_35,u_Counter_theta_ele_n_36,u_Counter_theta_ele_n_37}),
        .count_2(count_2),
        .position(position),
        .reset_old1_out1(reset_old1_out1),
        .\reset_old1_out1_reg[15]_0 (Pipeline2_out1),
        .reset_old2_out1(reset_old2_out1),
        .reset_old3_out1(reset_old3_out1_0),
        .reset_old3_out10_carry_0(u_Counter_n_11),
        .\reset_old4_out1_reg[0]_0 (\reset_old4_out1_reg[0] ),
        .\reset_old4_out1_reg[0]_1 (\reset_old4_out1_reg[0]_0 ),
        .\reset_old4_out1_reg[15]_0 (reset_old4_out1),
        .\reset_old4_out1_reg[15]_1 ({u_Counter_theta_ele_n_4,u_Counter_theta_ele_n_5,u_Counter_theta_ele_n_6,u_Counter_theta_ele_n_7,u_Counter_theta_ele_n_8,u_Counter_theta_ele_n_9,u_Counter_theta_ele_n_10,u_Counter_theta_ele_n_11}),
        .\reset_old5_out1_reg[0]_0 (\reset_old5_out1_reg[0] ),
        .\reset_old5_out1_reg[0]_1 (u_Counter_theta_ele_n_29),
        .\reset_old5_out1_reg[3]_0 (\reset_old5_out1_reg[3] ),
        .\reset_old6_out1_reg[15]_0 ({u_Counter_n_19,u_Counter_n_20,u_Counter_n_21,u_Counter_n_22,u_Counter_n_23,u_Counter_n_24,u_Counter_n_25}),
        .\reset_old6_out1_reg[7]_0 ({u_Counter_n_12,u_Counter_n_13,u_Counter_n_14,u_Counter_n_15,u_Counter_n_16,u_Counter_n_17,u_Counter_n_18}),
        .reset_old_out1(reset_old_out1));
  zusys_IncreEncoder_V24_ip_0_0_IncreEncoder_V24_ip_src_HDL_Reciprocal u_HDL_Reciprocal
       (.A({u_HDL_Reciprocal_n_0,u_HDL_Reciprocal_n_1,u_HDL_Reciprocal_n_2,u_HDL_Reciprocal_n_3,u_HDL_Reciprocal_n_4,u_HDL_Reciprocal_n_5,u_HDL_Reciprocal_n_6,u_HDL_Reciprocal_n_7,u_HDL_Reciprocal_n_8,u_HDL_Reciprocal_n_9,u_HDL_Reciprocal_n_10,u_HDL_Reciprocal_n_11,u_HDL_Reciprocal_n_12,u_HDL_Reciprocal_n_13,u_HDL_Reciprocal_n_14,u_HDL_Reciprocal_n_15,u_HDL_Reciprocal_n_16,u_HDL_Reciprocal_n_17,u_HDL_Reciprocal_n_18,u_HDL_Reciprocal_n_19,u_HDL_Reciprocal_n_20,u_HDL_Reciprocal_n_21,u_HDL_Reciprocal_n_22,u_HDL_Reciprocal_n_23}),
        .CEP(enb_1_100_0),
        .IPCORE_CLK(IPCORE_CLK),
        .Q({hold2_out1[31],hold2_out1[22:0]}),
        .RSTP(RSTP),
        .write_axi_enable(write_axi_enable));
  zusys_IncreEncoder_V24_ip_0_0_IncreEncoder_V24_ip_src_IncreEncoder_V24_tc u_IncreEncoder_V24_tc
       (.A(A),
        .B(B),
        .CEP(enb_1_100_0),
        .CO(Relational_Operator_relop1),
        .E(OnlyAllowInNewPeriod_out1),
        .I(I),
        .IPCORE_CLK(IPCORE_CLK),
        .Logical2_out1_1(Logical2_out1_1),
        .\OnlyAllowInNewPeriod_out1_reg[15] (u_omega_by_measure_time_n_0),
        .P(p_0_in),
        .PeriodEnd(PeriodEnd),
        .RSTP(RSTP),
        .SR(u_IncreEncoder_V24_tc_n_1),
        .count_2(count_2),
        .count_old1_out1_reg(u_Check_Direction_n_0),
        .count_old_out1_reg(u_Check_Direction_n_1),
        .\omega_oversampled_reg[0] (\omega_oversampled[22]_i_3_n_0 ),
        .phase_0_reg_0(phase_0_reg),
        .phase_0_reg_1(u_IncreEncoder_V24_tc_n_3),
        .phase_0_reg_2(u_IncreEncoder_V24_tc_n_4),
        .phase_0_reg_3(u_IncreEncoder_V24_tc_n_5),
        .phase_0_reg_4(u_IncreEncoder_V24_tc_n_6),
        .phase_0_reg_5(u_IncreEncoder_V24_tc_n_7),
        .phase_0_reg_6(u_IncreEncoder_V24_tc_n_8),
        .reset_old1_out1(reset_old1_out1),
        .reset_old1_out1_reg(u_omega_by_measure_time_n_2),
        .reset_old_out1(reset_old_out1),
        .write_axi_enable(write_axi_enable));
  zusys_IncreEncoder_V24_ip_0_0_IncreEncoder_V24_ip_src_omega_by_count_lines u_omega_by_count_lines
       (.CEP(enb_1_100_0),
        .CO(Relational_Operator_relop1),
        .Delay7_ctrl_delay_out(Delay7_ctrl_delay_out),
        .IPCORE_CLK(IPCORE_CLK),
        .PeriodEnd(PeriodEnd),
        .Q(Pipeline3_out1),
        .RSTP(RSTP),
        .SR(u_IncreEncoder_V24_tc_n_1),
        .countPerPEriod(countPerPEriod),
        .\countPerPEriod_1_reg[15] (\countPerPEriod_1_reg[15]_0 ),
        .count_2(count_2),
        .reset_old1_out1(reset_old1_out1));
  zusys_IncreEncoder_V24_ip_0_0_IncreEncoder_V24_ip_src_omega_by_measure_time u_omega_by_measure_time
       (.B(omega_by_measure_time_out2),
        .CEP(enb_1_100_0),
        .D(rps),
        .\Delay1_out1_reg[15]_0 (u_omega_by_measure_time_n_0),
        .\Delay5_out1_reg[23]_0 (D),
        .\Delay5_out1_reg[7]_0 (Q),
        .Delay7_ctrl_delay_out(Delay7_ctrl_delay_out),
        .E(OnlyAllowInNewPeriod_out1),
        .IPCORE_CLK(IPCORE_CLK),
        .Logical2_out1_1(Logical2_out1_1),
        .Q(Pipeline4_out1),
        .RSTP(RSTP),
        .\T_count_out1_reg[31]_0 (Pipeline7_out1),
        .\T_count_out1_reg[37]_0 (phase_0_reg),
        .\T_count_out1_reg[7]_0 ({hold1_out1[3],hold1_out1[0]}),
        .\hold5_out1_reg[15] (hold5_out1),
        .reset_old1_out1_reg_0(u_omega_by_measure_time_n_2),
        .reset_old1_out1_reg_1(u_IncreEncoder_V24_tc_n_6),
        .write_axi_enable(write_axi_enable));
endmodule

(* ORIG_REF_NAME = "IncreEncoder_V24_ip_src_IncreEncoder_V24_tc" *) 
module zusys_IncreEncoder_V24_ip_0_0_IncreEncoder_V24_ip_src_IncreEncoder_V24_tc
   (phase_0_reg_0,
    SR,
    E,
    phase_0_reg_1,
    phase_0_reg_2,
    phase_0_reg_3,
    phase_0_reg_4,
    phase_0_reg_5,
    phase_0_reg_6,
    CEP,
    RSTP,
    write_axi_enable,
    IPCORE_CLK,
    PeriodEnd,
    CO,
    \OnlyAllowInNewPeriod_out1_reg[15] ,
    I,
    reset_old_out1,
    count_2,
    reset_old1_out1,
    P,
    \omega_oversampled_reg[0] ,
    reset_old1_out1_reg,
    Logical2_out1_1,
    count_old_out1_reg,
    A,
    count_old1_out1_reg,
    B);
  output phase_0_reg_0;
  output [0:0]SR;
  output [0:0]E;
  output phase_0_reg_1;
  output phase_0_reg_2;
  output phase_0_reg_3;
  output phase_0_reg_4;
  output phase_0_reg_5;
  output phase_0_reg_6;
  output CEP;
  input RSTP;
  input write_axi_enable;
  input IPCORE_CLK;
  input PeriodEnd;
  input [0:0]CO;
  input [0:0]\OnlyAllowInNewPeriod_out1_reg[15] ;
  input I;
  input reset_old_out1;
  input count_2;
  input reset_old1_out1;
  input [0:0]P;
  input \omega_oversampled_reg[0] ;
  input reset_old1_out1_reg;
  input Logical2_out1_1;
  input count_old_out1_reg;
  input A;
  input count_old1_out1_reg;
  input B;

  wire A;
  wire B;
  wire CEP;
  wire [0:0]CO;
  wire [0:0]E;
  wire I;
  wire IPCORE_CLK;
  wire Logical2_out1_1;
  wire [0:0]\OnlyAllowInNewPeriod_out1_reg[15] ;
  wire [0:0]P;
  wire PeriodEnd;
  wire RSTP;
  wire [0:0]SR;
  wire count2;
  wire count2_i_1_n_0;
  wire count_2;
  wire count_old1_out1_reg;
  wire count_old_out1_reg;
  wire \omega_oversampled_reg[0] ;
  wire phase_0_reg_0;
  wire phase_0_reg_1;
  wire phase_0_reg_2;
  wire phase_0_reg_3;
  wire phase_0_reg_4;
  wire phase_0_reg_5;
  wire phase_0_reg_6;
  wire reset_old1_out1;
  wire reset_old1_out1_reg;
  wire reset_old_out1;
  wire write_axi_enable;

  (* SOFT_HLUTNM = "soft_lutpair104" *) 
  LUT3 #(
    .INIT(8'h80)) 
    \OnlyAllowInNewPeriod_out1[15]_i_1 
       (.I0(phase_0_reg_0),
        .I1(write_axi_enable),
        .I2(\OnlyAllowInNewPeriod_out1_reg[15] ),
        .O(E));
  LUT1 #(
    .INIT(2'h1)) 
    count2_i_1
       (.I0(count2),
        .O(count2_i_1_n_0));
  FDSE count2_reg
       (.C(IPCORE_CLK),
        .CE(write_axi_enable),
        .D(count2_i_1_n_0),
        .Q(count2),
        .S(RSTP));
  LUT4 #(
    .INIT(16'hF870)) 
    count_old1_out1_i_1
       (.I0(phase_0_reg_0),
        .I1(write_axi_enable),
        .I2(count_old1_out1_reg),
        .I3(B),
        .O(phase_0_reg_6));
  LUT4 #(
    .INIT(16'hF870)) 
    count_old_out1_i_1
       (.I0(phase_0_reg_0),
        .I1(write_axi_enable),
        .I2(count_old_out1_reg),
        .I3(A),
        .O(phase_0_reg_5));
  LUT5 #(
    .INIT(32'h00000800)) 
    \omega_oversampled[22]_i_1 
       (.I0(phase_0_reg_0),
        .I1(write_axi_enable),
        .I2(P),
        .I3(\omega_oversampled_reg[0] ),
        .I4(RSTP),
        .O(phase_0_reg_3));
  FDRE phase_0_reg
       (.C(IPCORE_CLK),
        .CE(write_axi_enable),
        .D(count2),
        .Q(phase_0_reg_0),
        .R(RSTP));
  LUT4 #(
    .INIT(16'hF780)) 
    reset_old1_out1_i_1
       (.I0(phase_0_reg_0),
        .I1(write_axi_enable),
        .I2(count_2),
        .I3(reset_old1_out1),
        .O(phase_0_reg_2));
  LUT4 #(
    .INIT(16'hF870)) 
    reset_old1_out1_i_1__0
       (.I0(phase_0_reg_0),
        .I1(write_axi_enable),
        .I2(reset_old1_out1_reg),
        .I3(Logical2_out1_1),
        .O(phase_0_reg_4));
  (* SOFT_HLUTNM = "soft_lutpair103" *) 
  LUT5 #(
    .INIT(32'hF8F8F8F0)) 
    \reset_old3_out1[15]_i_1 
       (.I0(phase_0_reg_0),
        .I1(write_axi_enable),
        .I2(RSTP),
        .I3(PeriodEnd),
        .I4(CO),
        .O(SR));
  (* SOFT_HLUTNM = "soft_lutpair104" *) 
  LUT4 #(
    .INIT(16'hF780)) 
    reset_old_out1_i_1
       (.I0(phase_0_reg_0),
        .I1(write_axi_enable),
        .I2(I),
        .I3(reset_old_out1),
        .O(phase_0_reg_1));
  (* SOFT_HLUTNM = "soft_lutpair103" *) 
  LUT2 #(
    .INIT(4'h8)) 
    theta_el_tmp_reg_i_1
       (.I0(phase_0_reg_0),
        .I1(write_axi_enable),
        .O(CEP));
endmodule

(* ORIG_REF_NAME = "IncreEncoder_V24_ip_src_omega_by_count_lines" *) 
module zusys_IncreEncoder_V24_ip_0_0_IncreEncoder_V24_ip_src_omega_by_count_lines
   (CO,
    countPerPEriod,
    PeriodEnd,
    \countPerPEriod_1_reg[15] ,
    Q,
    RSTP,
    CEP,
    IPCORE_CLK,
    SR,
    Delay7_ctrl_delay_out,
    reset_old1_out1,
    count_2);
  output [0:0]CO;
  output [15:0]countPerPEriod;
  input PeriodEnd;
  input [15:0]\countPerPEriod_1_reg[15] ;
  input [15:0]Q;
  input RSTP;
  input CEP;
  input IPCORE_CLK;
  input [0:0]SR;
  input Delay7_ctrl_delay_out;
  input reset_old1_out1;
  input count_2;

  wire [15:0]Add1_out1;
  wire Add1_out1_carry__0_n_1;
  wire Add1_out1_carry__0_n_2;
  wire Add1_out1_carry__0_n_3;
  wire Add1_out1_carry__0_n_4;
  wire Add1_out1_carry__0_n_5;
  wire Add1_out1_carry__0_n_6;
  wire Add1_out1_carry__0_n_7;
  wire Add1_out1_carry_i_1_n_0;
  wire Add1_out1_carry_n_0;
  wire Add1_out1_carry_n_1;
  wire Add1_out1_carry_n_2;
  wire Add1_out1_carry_n_3;
  wire Add1_out1_carry_n_4;
  wire Add1_out1_carry_n_5;
  wire Add1_out1_carry_n_6;
  wire Add1_out1_carry_n_7;
  wire CEP;
  wire [0:0]CO;
  wire Delay7_ctrl_delay_out;
  wire IPCORE_CLK;
  wire PeriodEnd;
  wire [15:0]Q;
  wire RSTP;
  wire [15:0]Reset_when_overflow_out1;
  wire Resett_switch1_out11_carry_i_10_n_0;
  wire Resett_switch1_out11_carry_i_11_n_0;
  wire Resett_switch1_out11_carry_i_12_n_0;
  wire Resett_switch1_out11_carry_i_13_n_0;
  wire Resett_switch1_out11_carry_i_14_n_0;
  wire Resett_switch1_out11_carry_i_15_n_0;
  wire Resett_switch1_out11_carry_i_16_n_0;
  wire Resett_switch1_out11_carry_i_1_n_0;
  wire Resett_switch1_out11_carry_i_2_n_0;
  wire Resett_switch1_out11_carry_i_3_n_0;
  wire Resett_switch1_out11_carry_i_4_n_0;
  wire Resett_switch1_out11_carry_i_5_n_0;
  wire Resett_switch1_out11_carry_i_6_n_0;
  wire Resett_switch1_out11_carry_i_7_n_0;
  wire Resett_switch1_out11_carry_i_8_n_0;
  wire Resett_switch1_out11_carry_i_9_n_0;
  wire Resett_switch1_out11_carry_n_1;
  wire Resett_switch1_out11_carry_n_2;
  wire Resett_switch1_out11_carry_n_3;
  wire Resett_switch1_out11_carry_n_4;
  wire Resett_switch1_out11_carry_n_5;
  wire Resett_switch1_out11_carry_n_6;
  wire Resett_switch1_out11_carry_n_7;
  wire [0:0]SR;
  wire [15:0]countPerPEriod;
  wire [15:0]\countPerPEriod_1_reg[15] ;
  wire count_2;
  wire reset_old1_out1;
  wire [15:0]reset_old3_out1_reg;
  wire [15:0]reset_old5_out1;
  wire \reset_old5_out1[7]_i_2_n_0 ;
  wire \reset_old5_out1[7]_i_3_n_0 ;
  wire \reset_old5_out1_reg[15]_i_1_n_1 ;
  wire \reset_old5_out1_reg[15]_i_1_n_2 ;
  wire \reset_old5_out1_reg[15]_i_1_n_3 ;
  wire \reset_old5_out1_reg[15]_i_1_n_4 ;
  wire \reset_old5_out1_reg[15]_i_1_n_5 ;
  wire \reset_old5_out1_reg[15]_i_1_n_6 ;
  wire \reset_old5_out1_reg[15]_i_1_n_7 ;
  wire \reset_old5_out1_reg[7]_i_1_n_0 ;
  wire \reset_old5_out1_reg[7]_i_1_n_1 ;
  wire \reset_old5_out1_reg[7]_i_1_n_2 ;
  wire \reset_old5_out1_reg[7]_i_1_n_3 ;
  wire \reset_old5_out1_reg[7]_i_1_n_4 ;
  wire \reset_old5_out1_reg[7]_i_1_n_5 ;
  wire \reset_old5_out1_reg[7]_i_1_n_6 ;
  wire \reset_old5_out1_reg[7]_i_1_n_7 ;
  wire [7:7]NLW_Add1_out1_carry__0_CO_UNCONNECTED;
  wire [7:0]NLW_Resett_switch1_out11_carry_O_UNCONNECTED;
  wire [7:7]\NLW_reset_old5_out1_reg[15]_i_1_CO_UNCONNECTED ;

  (* ADDER_THRESHOLD = "35" *) 
  (* METHODOLOGY_DRC_VIOS = "{SYNTH-8 {cell *THIS*}}" *) 
  CARRY8 Add1_out1_carry
       (.CI(1'b0),
        .CI_TOP(1'b0),
        .CO({Add1_out1_carry_n_0,Add1_out1_carry_n_1,Add1_out1_carry_n_2,Add1_out1_carry_n_3,Add1_out1_carry_n_4,Add1_out1_carry_n_5,Add1_out1_carry_n_6,Add1_out1_carry_n_7}),
        .DI({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,reset_old3_out1_reg[0]}),
        .O(Add1_out1[7:0]),
        .S({reset_old3_out1_reg[7:1],Add1_out1_carry_i_1_n_0}));
  (* ADDER_THRESHOLD = "35" *) 
  (* METHODOLOGY_DRC_VIOS = "{SYNTH-8 {cell *THIS*}}" *) 
  CARRY8 Add1_out1_carry__0
       (.CI(Add1_out1_carry_n_0),
        .CI_TOP(1'b0),
        .CO({NLW_Add1_out1_carry__0_CO_UNCONNECTED[7],Add1_out1_carry__0_n_1,Add1_out1_carry__0_n_2,Add1_out1_carry__0_n_3,Add1_out1_carry__0_n_4,Add1_out1_carry__0_n_5,Add1_out1_carry__0_n_6,Add1_out1_carry__0_n_7}),
        .DI({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .O(Add1_out1[15:8]),
        .S(reset_old3_out1_reg[15:8]));
  LUT4 #(
    .INIT(16'hD728)) 
    Add1_out1_carry_i_1
       (.I0(Delay7_ctrl_delay_out),
        .I1(reset_old1_out1),
        .I2(count_2),
        .I3(reset_old3_out1_reg[0]),
        .O(Add1_out1_carry_i_1_n_0));
  (* COMPARATOR_THRESHOLD = "11" *) 
  (* METHODOLOGY_DRC_VIOS = "{SYNTH-8 {cell *THIS*}}" *) 
  CARRY8 Resett_switch1_out11_carry
       (.CI(1'b0),
        .CI_TOP(1'b0),
        .CO({CO,Resett_switch1_out11_carry_n_1,Resett_switch1_out11_carry_n_2,Resett_switch1_out11_carry_n_3,Resett_switch1_out11_carry_n_4,Resett_switch1_out11_carry_n_5,Resett_switch1_out11_carry_n_6,Resett_switch1_out11_carry_n_7}),
        .DI({Resett_switch1_out11_carry_i_1_n_0,Resett_switch1_out11_carry_i_2_n_0,Resett_switch1_out11_carry_i_3_n_0,Resett_switch1_out11_carry_i_4_n_0,Resett_switch1_out11_carry_i_5_n_0,Resett_switch1_out11_carry_i_6_n_0,Resett_switch1_out11_carry_i_7_n_0,Resett_switch1_out11_carry_i_8_n_0}),
        .O(NLW_Resett_switch1_out11_carry_O_UNCONNECTED[7:0]),
        .S({Resett_switch1_out11_carry_i_9_n_0,Resett_switch1_out11_carry_i_10_n_0,Resett_switch1_out11_carry_i_11_n_0,Resett_switch1_out11_carry_i_12_n_0,Resett_switch1_out11_carry_i_13_n_0,Resett_switch1_out11_carry_i_14_n_0,Resett_switch1_out11_carry_i_15_n_0,Resett_switch1_out11_carry_i_16_n_0}));
  LUT4 #(
    .INIT(16'h22B2)) 
    Resett_switch1_out11_carry_i_1
       (.I0(reset_old5_out1[15]),
        .I1(reset_old3_out1_reg[15]),
        .I2(reset_old3_out1_reg[14]),
        .I3(reset_old5_out1[14]),
        .O(Resett_switch1_out11_carry_i_1_n_0));
  LUT4 #(
    .INIT(16'h9009)) 
    Resett_switch1_out11_carry_i_10
       (.I0(reset_old5_out1[13]),
        .I1(reset_old3_out1_reg[13]),
        .I2(reset_old5_out1[12]),
        .I3(reset_old3_out1_reg[12]),
        .O(Resett_switch1_out11_carry_i_10_n_0));
  LUT4 #(
    .INIT(16'h9009)) 
    Resett_switch1_out11_carry_i_11
       (.I0(reset_old5_out1[11]),
        .I1(reset_old3_out1_reg[11]),
        .I2(reset_old5_out1[10]),
        .I3(reset_old3_out1_reg[10]),
        .O(Resett_switch1_out11_carry_i_11_n_0));
  LUT4 #(
    .INIT(16'h9009)) 
    Resett_switch1_out11_carry_i_12
       (.I0(reset_old5_out1[9]),
        .I1(reset_old3_out1_reg[9]),
        .I2(reset_old5_out1[8]),
        .I3(reset_old3_out1_reg[8]),
        .O(Resett_switch1_out11_carry_i_12_n_0));
  LUT4 #(
    .INIT(16'h9009)) 
    Resett_switch1_out11_carry_i_13
       (.I0(reset_old5_out1[7]),
        .I1(reset_old3_out1_reg[7]),
        .I2(reset_old5_out1[6]),
        .I3(reset_old3_out1_reg[6]),
        .O(Resett_switch1_out11_carry_i_13_n_0));
  LUT4 #(
    .INIT(16'h9009)) 
    Resett_switch1_out11_carry_i_14
       (.I0(reset_old5_out1[5]),
        .I1(reset_old3_out1_reg[5]),
        .I2(reset_old5_out1[4]),
        .I3(reset_old3_out1_reg[4]),
        .O(Resett_switch1_out11_carry_i_14_n_0));
  LUT4 #(
    .INIT(16'h9009)) 
    Resett_switch1_out11_carry_i_15
       (.I0(reset_old5_out1[3]),
        .I1(reset_old3_out1_reg[3]),
        .I2(reset_old5_out1[2]),
        .I3(reset_old3_out1_reg[2]),
        .O(Resett_switch1_out11_carry_i_15_n_0));
  LUT4 #(
    .INIT(16'h9009)) 
    Resett_switch1_out11_carry_i_16
       (.I0(reset_old5_out1[1]),
        .I1(reset_old3_out1_reg[1]),
        .I2(reset_old5_out1[0]),
        .I3(reset_old3_out1_reg[0]),
        .O(Resett_switch1_out11_carry_i_16_n_0));
  LUT4 #(
    .INIT(16'h22B2)) 
    Resett_switch1_out11_carry_i_2
       (.I0(reset_old3_out1_reg[13]),
        .I1(reset_old5_out1[13]),
        .I2(reset_old3_out1_reg[12]),
        .I3(reset_old5_out1[12]),
        .O(Resett_switch1_out11_carry_i_2_n_0));
  LUT4 #(
    .INIT(16'h22B2)) 
    Resett_switch1_out11_carry_i_3
       (.I0(reset_old3_out1_reg[11]),
        .I1(reset_old5_out1[11]),
        .I2(reset_old3_out1_reg[10]),
        .I3(reset_old5_out1[10]),
        .O(Resett_switch1_out11_carry_i_3_n_0));
  LUT4 #(
    .INIT(16'h22B2)) 
    Resett_switch1_out11_carry_i_4
       (.I0(reset_old3_out1_reg[9]),
        .I1(reset_old5_out1[9]),
        .I2(reset_old3_out1_reg[8]),
        .I3(reset_old5_out1[8]),
        .O(Resett_switch1_out11_carry_i_4_n_0));
  LUT4 #(
    .INIT(16'h22B2)) 
    Resett_switch1_out11_carry_i_5
       (.I0(reset_old3_out1_reg[7]),
        .I1(reset_old5_out1[7]),
        .I2(reset_old3_out1_reg[6]),
        .I3(reset_old5_out1[6]),
        .O(Resett_switch1_out11_carry_i_5_n_0));
  LUT4 #(
    .INIT(16'h22B2)) 
    Resett_switch1_out11_carry_i_6
       (.I0(reset_old3_out1_reg[5]),
        .I1(reset_old5_out1[5]),
        .I2(reset_old3_out1_reg[4]),
        .I3(reset_old5_out1[4]),
        .O(Resett_switch1_out11_carry_i_6_n_0));
  LUT4 #(
    .INIT(16'h22B2)) 
    Resett_switch1_out11_carry_i_7
       (.I0(reset_old3_out1_reg[3]),
        .I1(reset_old5_out1[3]),
        .I2(reset_old3_out1_reg[2]),
        .I3(reset_old5_out1[2]),
        .O(Resett_switch1_out11_carry_i_7_n_0));
  LUT4 #(
    .INIT(16'h22B2)) 
    Resett_switch1_out11_carry_i_8
       (.I0(reset_old3_out1_reg[1]),
        .I1(reset_old5_out1[1]),
        .I2(reset_old3_out1_reg[0]),
        .I3(reset_old5_out1[0]),
        .O(Resett_switch1_out11_carry_i_8_n_0));
  LUT4 #(
    .INIT(16'h9009)) 
    Resett_switch1_out11_carry_i_9
       (.I0(reset_old5_out1[15]),
        .I1(reset_old3_out1_reg[15]),
        .I2(reset_old5_out1[14]),
        .I3(reset_old3_out1_reg[14]),
        .O(Resett_switch1_out11_carry_i_9_n_0));
  (* SOFT_HLUTNM = "soft_lutpair112" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \countPerPEriod_1[0]_i_1 
       (.I0(reset_old3_out1_reg[0]),
        .I1(PeriodEnd),
        .I2(\countPerPEriod_1_reg[15] [0]),
        .O(countPerPEriod[0]));
  (* SOFT_HLUTNM = "soft_lutpair107" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \countPerPEriod_1[10]_i_1 
       (.I0(reset_old3_out1_reg[10]),
        .I1(PeriodEnd),
        .I2(\countPerPEriod_1_reg[15] [10]),
        .O(countPerPEriod[10]));
  (* SOFT_HLUTNM = "soft_lutpair107" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \countPerPEriod_1[11]_i_1 
       (.I0(reset_old3_out1_reg[11]),
        .I1(PeriodEnd),
        .I2(\countPerPEriod_1_reg[15] [11]),
        .O(countPerPEriod[11]));
  (* SOFT_HLUTNM = "soft_lutpair106" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \countPerPEriod_1[12]_i_1 
       (.I0(reset_old3_out1_reg[12]),
        .I1(PeriodEnd),
        .I2(\countPerPEriod_1_reg[15] [12]),
        .O(countPerPEriod[12]));
  (* SOFT_HLUTNM = "soft_lutpair106" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \countPerPEriod_1[13]_i_1 
       (.I0(reset_old3_out1_reg[13]),
        .I1(PeriodEnd),
        .I2(\countPerPEriod_1_reg[15] [13]),
        .O(countPerPEriod[13]));
  (* SOFT_HLUTNM = "soft_lutpair105" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \countPerPEriod_1[14]_i_1 
       (.I0(reset_old3_out1_reg[14]),
        .I1(PeriodEnd),
        .I2(\countPerPEriod_1_reg[15] [14]),
        .O(countPerPEriod[14]));
  (* SOFT_HLUTNM = "soft_lutpair105" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \countPerPEriod_1[15]_i_1 
       (.I0(reset_old3_out1_reg[15]),
        .I1(PeriodEnd),
        .I2(\countPerPEriod_1_reg[15] [15]),
        .O(countPerPEriod[15]));
  (* SOFT_HLUTNM = "soft_lutpair112" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \countPerPEriod_1[1]_i_1 
       (.I0(reset_old3_out1_reg[1]),
        .I1(PeriodEnd),
        .I2(\countPerPEriod_1_reg[15] [1]),
        .O(countPerPEriod[1]));
  (* SOFT_HLUTNM = "soft_lutpair111" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \countPerPEriod_1[2]_i_1 
       (.I0(reset_old3_out1_reg[2]),
        .I1(PeriodEnd),
        .I2(\countPerPEriod_1_reg[15] [2]),
        .O(countPerPEriod[2]));
  (* SOFT_HLUTNM = "soft_lutpair111" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \countPerPEriod_1[3]_i_1 
       (.I0(reset_old3_out1_reg[3]),
        .I1(PeriodEnd),
        .I2(\countPerPEriod_1_reg[15] [3]),
        .O(countPerPEriod[3]));
  (* SOFT_HLUTNM = "soft_lutpair110" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \countPerPEriod_1[4]_i_1 
       (.I0(reset_old3_out1_reg[4]),
        .I1(PeriodEnd),
        .I2(\countPerPEriod_1_reg[15] [4]),
        .O(countPerPEriod[4]));
  (* SOFT_HLUTNM = "soft_lutpair110" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \countPerPEriod_1[5]_i_1 
       (.I0(reset_old3_out1_reg[5]),
        .I1(PeriodEnd),
        .I2(\countPerPEriod_1_reg[15] [5]),
        .O(countPerPEriod[5]));
  (* SOFT_HLUTNM = "soft_lutpair109" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \countPerPEriod_1[6]_i_1 
       (.I0(reset_old3_out1_reg[6]),
        .I1(PeriodEnd),
        .I2(\countPerPEriod_1_reg[15] [6]),
        .O(countPerPEriod[6]));
  (* SOFT_HLUTNM = "soft_lutpair109" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \countPerPEriod_1[7]_i_1 
       (.I0(reset_old3_out1_reg[7]),
        .I1(PeriodEnd),
        .I2(\countPerPEriod_1_reg[15] [7]),
        .O(countPerPEriod[7]));
  (* SOFT_HLUTNM = "soft_lutpair108" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \countPerPEriod_1[8]_i_1 
       (.I0(reset_old3_out1_reg[8]),
        .I1(PeriodEnd),
        .I2(\countPerPEriod_1_reg[15] [8]),
        .O(countPerPEriod[8]));
  (* SOFT_HLUTNM = "soft_lutpair108" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \countPerPEriod_1[9]_i_1 
       (.I0(reset_old3_out1_reg[9]),
        .I1(PeriodEnd),
        .I2(\countPerPEriod_1_reg[15] [9]),
        .O(countPerPEriod[9]));
  FDRE \reset_old3_out1_reg[0] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Add1_out1[0]),
        .Q(reset_old3_out1_reg[0]),
        .R(SR));
  FDRE \reset_old3_out1_reg[10] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Add1_out1[10]),
        .Q(reset_old3_out1_reg[10]),
        .R(SR));
  FDRE \reset_old3_out1_reg[11] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Add1_out1[11]),
        .Q(reset_old3_out1_reg[11]),
        .R(SR));
  FDRE \reset_old3_out1_reg[12] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Add1_out1[12]),
        .Q(reset_old3_out1_reg[12]),
        .R(SR));
  FDRE \reset_old3_out1_reg[13] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Add1_out1[13]),
        .Q(reset_old3_out1_reg[13]),
        .R(SR));
  FDRE \reset_old3_out1_reg[14] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Add1_out1[14]),
        .Q(reset_old3_out1_reg[14]),
        .R(SR));
  FDRE \reset_old3_out1_reg[15] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Add1_out1[15]),
        .Q(reset_old3_out1_reg[15]),
        .R(SR));
  FDRE \reset_old3_out1_reg[1] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Add1_out1[1]),
        .Q(reset_old3_out1_reg[1]),
        .R(SR));
  FDRE \reset_old3_out1_reg[2] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Add1_out1[2]),
        .Q(reset_old3_out1_reg[2]),
        .R(SR));
  FDRE \reset_old3_out1_reg[3] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Add1_out1[3]),
        .Q(reset_old3_out1_reg[3]),
        .R(SR));
  FDRE \reset_old3_out1_reg[4] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Add1_out1[4]),
        .Q(reset_old3_out1_reg[4]),
        .R(SR));
  FDRE \reset_old3_out1_reg[5] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Add1_out1[5]),
        .Q(reset_old3_out1_reg[5]),
        .R(SR));
  FDRE \reset_old3_out1_reg[6] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Add1_out1[6]),
        .Q(reset_old3_out1_reg[6]),
        .R(SR));
  FDRE \reset_old3_out1_reg[7] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Add1_out1[7]),
        .Q(reset_old3_out1_reg[7]),
        .R(SR));
  FDRE \reset_old3_out1_reg[8] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Add1_out1[8]),
        .Q(reset_old3_out1_reg[8]),
        .R(SR));
  FDRE \reset_old3_out1_reg[9] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Add1_out1[9]),
        .Q(reset_old3_out1_reg[9]),
        .R(SR));
  LUT1 #(
    .INIT(2'h1)) 
    \reset_old5_out1[7]_i_2 
       (.I0(Q[3]),
        .O(\reset_old5_out1[7]_i_2_n_0 ));
  LUT1 #(
    .INIT(2'h1)) 
    \reset_old5_out1[7]_i_3 
       (.I0(Q[1]),
        .O(\reset_old5_out1[7]_i_3_n_0 ));
  FDRE \reset_old5_out1_reg[0] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Reset_when_overflow_out1[0]),
        .Q(reset_old5_out1[0]),
        .R(RSTP));
  FDRE \reset_old5_out1_reg[10] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Reset_when_overflow_out1[10]),
        .Q(reset_old5_out1[10]),
        .R(RSTP));
  FDRE \reset_old5_out1_reg[11] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Reset_when_overflow_out1[11]),
        .Q(reset_old5_out1[11]),
        .R(RSTP));
  FDRE \reset_old5_out1_reg[12] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Reset_when_overflow_out1[12]),
        .Q(reset_old5_out1[12]),
        .R(RSTP));
  FDRE \reset_old5_out1_reg[13] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Reset_when_overflow_out1[13]),
        .Q(reset_old5_out1[13]),
        .R(RSTP));
  FDRE \reset_old5_out1_reg[14] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Reset_when_overflow_out1[14]),
        .Q(reset_old5_out1[14]),
        .R(RSTP));
  FDRE \reset_old5_out1_reg[15] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Reset_when_overflow_out1[15]),
        .Q(reset_old5_out1[15]),
        .R(RSTP));
  (* ADDER_THRESHOLD = "35" *) 
  CARRY8 \reset_old5_out1_reg[15]_i_1 
       (.CI(\reset_old5_out1_reg[7]_i_1_n_0 ),
        .CI_TOP(1'b0),
        .CO({\NLW_reset_old5_out1_reg[15]_i_1_CO_UNCONNECTED [7],\reset_old5_out1_reg[15]_i_1_n_1 ,\reset_old5_out1_reg[15]_i_1_n_2 ,\reset_old5_out1_reg[15]_i_1_n_3 ,\reset_old5_out1_reg[15]_i_1_n_4 ,\reset_old5_out1_reg[15]_i_1_n_5 ,\reset_old5_out1_reg[15]_i_1_n_6 ,\reset_old5_out1_reg[15]_i_1_n_7 }),
        .DI({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .O(Reset_when_overflow_out1[15:8]),
        .S(Q[15:8]));
  FDRE \reset_old5_out1_reg[1] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Reset_when_overflow_out1[1]),
        .Q(reset_old5_out1[1]),
        .R(RSTP));
  FDRE \reset_old5_out1_reg[2] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Reset_when_overflow_out1[2]),
        .Q(reset_old5_out1[2]),
        .R(RSTP));
  FDRE \reset_old5_out1_reg[3] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Reset_when_overflow_out1[3]),
        .Q(reset_old5_out1[3]),
        .R(RSTP));
  FDRE \reset_old5_out1_reg[4] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Reset_when_overflow_out1[4]),
        .Q(reset_old5_out1[4]),
        .R(RSTP));
  FDRE \reset_old5_out1_reg[5] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Reset_when_overflow_out1[5]),
        .Q(reset_old5_out1[5]),
        .R(RSTP));
  FDRE \reset_old5_out1_reg[6] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Reset_when_overflow_out1[6]),
        .Q(reset_old5_out1[6]),
        .R(RSTP));
  FDRE \reset_old5_out1_reg[7] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Reset_when_overflow_out1[7]),
        .Q(reset_old5_out1[7]),
        .R(RSTP));
  (* ADDER_THRESHOLD = "35" *) 
  CARRY8 \reset_old5_out1_reg[7]_i_1 
       (.CI(1'b0),
        .CI_TOP(1'b0),
        .CO({\reset_old5_out1_reg[7]_i_1_n_0 ,\reset_old5_out1_reg[7]_i_1_n_1 ,\reset_old5_out1_reg[7]_i_1_n_2 ,\reset_old5_out1_reg[7]_i_1_n_3 ,\reset_old5_out1_reg[7]_i_1_n_4 ,\reset_old5_out1_reg[7]_i_1_n_5 ,\reset_old5_out1_reg[7]_i_1_n_6 ,\reset_old5_out1_reg[7]_i_1_n_7 }),
        .DI({1'b0,1'b0,1'b0,1'b0,Q[3],1'b0,Q[1],1'b0}),
        .O(Reset_when_overflow_out1[7:0]),
        .S({Q[7:4],\reset_old5_out1[7]_i_2_n_0 ,Q[2],\reset_old5_out1[7]_i_3_n_0 ,Q[0]}));
  FDRE \reset_old5_out1_reg[8] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Reset_when_overflow_out1[8]),
        .Q(reset_old5_out1[8]),
        .R(RSTP));
  FDRE \reset_old5_out1_reg[9] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Reset_when_overflow_out1[9]),
        .Q(reset_old5_out1[9]),
        .R(RSTP));
endmodule

(* ORIG_REF_NAME = "IncreEncoder_V24_ip_src_omega_by_measure_time" *) 
module zusys_IncreEncoder_V24_ip_0_0_IncreEncoder_V24_ip_src_omega_by_measure_time
   (\Delay1_out1_reg[15]_0 ,
    Delay7_ctrl_delay_out,
    reset_old1_out1_reg_0,
    D,
    B,
    RSTP,
    CEP,
    IPCORE_CLK,
    Q,
    reset_old1_out1_reg_1,
    \T_count_out1_reg[7]_0 ,
    \Delay5_out1_reg[7]_0 ,
    \T_count_out1_reg[37]_0 ,
    write_axi_enable,
    Logical2_out1_1,
    \hold5_out1_reg[15] ,
    \T_count_out1_reg[31]_0 ,
    E,
    \Delay5_out1_reg[23]_0 );
  output [0:0]\Delay1_out1_reg[15]_0 ;
  output Delay7_ctrl_delay_out;
  output reset_old1_out1_reg_0;
  output [23:0]D;
  output [15:0]B;
  input RSTP;
  input CEP;
  input IPCORE_CLK;
  input [23:0]Q;
  input reset_old1_out1_reg_1;
  input [1:0]\T_count_out1_reg[7]_0 ;
  input [0:0]\Delay5_out1_reg[7]_0 ;
  input \T_count_out1_reg[37]_0 ;
  input write_axi_enable;
  input Logical2_out1_1;
  input [15:0]\hold5_out1_reg[15] ;
  input [31:0]\T_count_out1_reg[31]_0 ;
  input [0:0]E;
  input [22:0]\Delay5_out1_reg[23]_0 ;

  wire [15:0]B;
  wire CEP;
  wire [23:0]D;
  wire [15:0]Delay1_out1;
  wire [0:0]\Delay1_out1_reg[15]_0 ;
  wire Delay3_out1;
  wire Delay3_out10_carry__0_i_1_n_0;
  wire Delay3_out10_carry_i_10_n_0;
  wire Delay3_out10_carry_i_11_n_0;
  wire Delay3_out10_carry_i_12_n_0;
  wire Delay3_out10_carry_i_13_n_0;
  wire Delay3_out10_carry_i_14_n_0;
  wire Delay3_out10_carry_i_15_n_0;
  wire Delay3_out10_carry_i_16_n_0;
  wire Delay3_out10_carry_i_1_n_0;
  wire Delay3_out10_carry_i_2_n_0;
  wire Delay3_out10_carry_i_3_n_0;
  wire Delay3_out10_carry_i_4_n_0;
  wire Delay3_out10_carry_i_5_n_0;
  wire Delay3_out10_carry_i_6_n_0;
  wire Delay3_out10_carry_i_7_n_0;
  wire Delay3_out10_carry_i_8_n_0;
  wire Delay3_out10_carry_i_9_n_0;
  wire Delay3_out10_carry_n_0;
  wire Delay3_out10_carry_n_1;
  wire Delay3_out10_carry_n_2;
  wire Delay3_out10_carry_n_3;
  wire Delay3_out10_carry_n_4;
  wire Delay3_out10_carry_n_5;
  wire Delay3_out10_carry_n_6;
  wire Delay3_out10_carry_n_7;
  wire [23:0]Delay5_out1;
  wire \Delay5_out1[15]_i_2_n_0 ;
  wire \Delay5_out1[15]_i_3_n_0 ;
  wire \Delay5_out1[15]_i_4_n_0 ;
  wire \Delay5_out1[15]_i_5_n_0 ;
  wire \Delay5_out1[15]_i_6_n_0 ;
  wire \Delay5_out1[15]_i_7_n_0 ;
  wire \Delay5_out1[15]_i_8_n_0 ;
  wire \Delay5_out1[15]_i_9_n_0 ;
  wire \Delay5_out1[23]_i_2_n_0 ;
  wire \Delay5_out1[23]_i_3_n_0 ;
  wire \Delay5_out1[23]_i_4_n_0 ;
  wire \Delay5_out1[23]_i_5_n_0 ;
  wire \Delay5_out1[23]_i_6_n_0 ;
  wire \Delay5_out1[23]_i_7_n_0 ;
  wire \Delay5_out1[23]_i_8_n_0 ;
  wire \Delay5_out1[7]_i_10_n_0 ;
  wire \Delay5_out1[7]_i_2_n_0 ;
  wire \Delay5_out1[7]_i_3_n_0 ;
  wire \Delay5_out1[7]_i_4_n_0 ;
  wire \Delay5_out1[7]_i_5_n_0 ;
  wire \Delay5_out1[7]_i_6_n_0 ;
  wire \Delay5_out1[7]_i_7_n_0 ;
  wire \Delay5_out1[7]_i_8_n_0 ;
  wire \Delay5_out1[7]_i_9_n_0 ;
  wire \Delay5_out1_reg[15]_i_1_n_0 ;
  wire \Delay5_out1_reg[15]_i_1_n_1 ;
  wire \Delay5_out1_reg[15]_i_1_n_10 ;
  wire \Delay5_out1_reg[15]_i_1_n_11 ;
  wire \Delay5_out1_reg[15]_i_1_n_12 ;
  wire \Delay5_out1_reg[15]_i_1_n_13 ;
  wire \Delay5_out1_reg[15]_i_1_n_14 ;
  wire \Delay5_out1_reg[15]_i_1_n_15 ;
  wire \Delay5_out1_reg[15]_i_1_n_2 ;
  wire \Delay5_out1_reg[15]_i_1_n_3 ;
  wire \Delay5_out1_reg[15]_i_1_n_4 ;
  wire \Delay5_out1_reg[15]_i_1_n_5 ;
  wire \Delay5_out1_reg[15]_i_1_n_6 ;
  wire \Delay5_out1_reg[15]_i_1_n_7 ;
  wire \Delay5_out1_reg[15]_i_1_n_8 ;
  wire \Delay5_out1_reg[15]_i_1_n_9 ;
  wire [22:0]\Delay5_out1_reg[23]_0 ;
  wire \Delay5_out1_reg[23]_i_1_n_1 ;
  wire \Delay5_out1_reg[23]_i_1_n_10 ;
  wire \Delay5_out1_reg[23]_i_1_n_11 ;
  wire \Delay5_out1_reg[23]_i_1_n_12 ;
  wire \Delay5_out1_reg[23]_i_1_n_13 ;
  wire \Delay5_out1_reg[23]_i_1_n_14 ;
  wire \Delay5_out1_reg[23]_i_1_n_15 ;
  wire \Delay5_out1_reg[23]_i_1_n_2 ;
  wire \Delay5_out1_reg[23]_i_1_n_3 ;
  wire \Delay5_out1_reg[23]_i_1_n_4 ;
  wire \Delay5_out1_reg[23]_i_1_n_5 ;
  wire \Delay5_out1_reg[23]_i_1_n_6 ;
  wire \Delay5_out1_reg[23]_i_1_n_7 ;
  wire \Delay5_out1_reg[23]_i_1_n_8 ;
  wire \Delay5_out1_reg[23]_i_1_n_9 ;
  wire [0:0]\Delay5_out1_reg[7]_0 ;
  wire \Delay5_out1_reg[7]_i_1_n_0 ;
  wire \Delay5_out1_reg[7]_i_1_n_1 ;
  wire \Delay5_out1_reg[7]_i_1_n_10 ;
  wire \Delay5_out1_reg[7]_i_1_n_11 ;
  wire \Delay5_out1_reg[7]_i_1_n_12 ;
  wire \Delay5_out1_reg[7]_i_1_n_13 ;
  wire \Delay5_out1_reg[7]_i_1_n_14 ;
  wire \Delay5_out1_reg[7]_i_1_n_15 ;
  wire \Delay5_out1_reg[7]_i_1_n_2 ;
  wire \Delay5_out1_reg[7]_i_1_n_3 ;
  wire \Delay5_out1_reg[7]_i_1_n_4 ;
  wire \Delay5_out1_reg[7]_i_1_n_5 ;
  wire \Delay5_out1_reg[7]_i_1_n_6 ;
  wire \Delay5_out1_reg[7]_i_1_n_7 ;
  wire \Delay5_out1_reg[7]_i_1_n_8 ;
  wire \Delay5_out1_reg[7]_i_1_n_9 ;
  wire [23:0]Delay6_out1_reg;
  wire Delay7_ctrl_delay_out;
  wire [15:0]Delay7_out_reg;
  wire [0:0]E;
  wire IPCORE_CLK;
  wire InternalOmega_Out_tmp0_carry__1_i_1_n_0;
  wire InternalOmega_Out_tmp0_carry__1_i_2_n_0;
  wire InternalOmega_Out_tmp0_carry__1_i_3_n_0;
  wire InternalOmega_Out_tmp0_carry__1_i_4_n_0;
  wire InternalOmega_Out_tmp0_carry__1_i_5_n_0;
  wire InternalOmega_Out_tmp0_carry__1_i_6_n_0;
  wire InternalOmega_Out_tmp0_carry__1_i_7_n_0;
  wire InternalOmega_Out_tmp0_carry__1_i_8_n_0;
  wire Logical2_out1_1;
  wire [15:0]OnlyAllowInNewPeriod_out1__0;
  wire [37:0]Pipeline1_out1;
  wire \Pipeline1_out1[15]_i_2_n_0 ;
  wire \Pipeline1_out1[15]_i_3_n_0 ;
  wire \Pipeline1_out1[15]_i_4_n_0 ;
  wire \Pipeline1_out1[15]_i_5_n_0 ;
  wire \Pipeline1_out1[15]_i_6_n_0 ;
  wire \Pipeline1_out1[15]_i_7_n_0 ;
  wire \Pipeline1_out1[15]_i_8_n_0 ;
  wire \Pipeline1_out1[15]_i_9_n_0 ;
  wire \Pipeline1_out1[23]_i_2_n_0 ;
  wire \Pipeline1_out1[23]_i_3_n_0 ;
  wire \Pipeline1_out1[23]_i_4_n_0 ;
  wire \Pipeline1_out1[23]_i_5_n_0 ;
  wire \Pipeline1_out1[23]_i_6_n_0 ;
  wire \Pipeline1_out1[23]_i_7_n_0 ;
  wire \Pipeline1_out1[23]_i_8_n_0 ;
  wire \Pipeline1_out1[23]_i_9_n_0 ;
  wire \Pipeline1_out1[31]_i_2_n_0 ;
  wire \Pipeline1_out1[31]_i_3_n_0 ;
  wire \Pipeline1_out1[31]_i_4_n_0 ;
  wire \Pipeline1_out1[31]_i_5_n_0 ;
  wire \Pipeline1_out1[31]_i_6_n_0 ;
  wire \Pipeline1_out1[31]_i_7_n_0 ;
  wire \Pipeline1_out1[31]_i_8_n_0 ;
  wire \Pipeline1_out1[31]_i_9_n_0 ;
  wire \Pipeline1_out1[37]_i_2_n_0 ;
  wire \Pipeline1_out1[37]_i_3_n_0 ;
  wire \Pipeline1_out1[37]_i_4_n_0 ;
  wire \Pipeline1_out1[37]_i_5_n_0 ;
  wire \Pipeline1_out1[37]_i_6_n_0 ;
  wire \Pipeline1_out1[7]_i_10_n_0 ;
  wire \Pipeline1_out1[7]_i_2_n_0 ;
  wire \Pipeline1_out1[7]_i_3_n_0 ;
  wire \Pipeline1_out1[7]_i_4_n_0 ;
  wire \Pipeline1_out1[7]_i_5_n_0 ;
  wire \Pipeline1_out1[7]_i_6_n_0 ;
  wire \Pipeline1_out1[7]_i_7_n_0 ;
  wire \Pipeline1_out1[7]_i_8_n_0 ;
  wire \Pipeline1_out1[7]_i_9_n_0 ;
  wire \Pipeline1_out1_reg[15]_i_1_n_0 ;
  wire \Pipeline1_out1_reg[15]_i_1_n_1 ;
  wire \Pipeline1_out1_reg[15]_i_1_n_10 ;
  wire \Pipeline1_out1_reg[15]_i_1_n_11 ;
  wire \Pipeline1_out1_reg[15]_i_1_n_12 ;
  wire \Pipeline1_out1_reg[15]_i_1_n_13 ;
  wire \Pipeline1_out1_reg[15]_i_1_n_14 ;
  wire \Pipeline1_out1_reg[15]_i_1_n_15 ;
  wire \Pipeline1_out1_reg[15]_i_1_n_2 ;
  wire \Pipeline1_out1_reg[15]_i_1_n_3 ;
  wire \Pipeline1_out1_reg[15]_i_1_n_4 ;
  wire \Pipeline1_out1_reg[15]_i_1_n_5 ;
  wire \Pipeline1_out1_reg[15]_i_1_n_6 ;
  wire \Pipeline1_out1_reg[15]_i_1_n_7 ;
  wire \Pipeline1_out1_reg[15]_i_1_n_8 ;
  wire \Pipeline1_out1_reg[15]_i_1_n_9 ;
  wire \Pipeline1_out1_reg[23]_i_1_n_0 ;
  wire \Pipeline1_out1_reg[23]_i_1_n_1 ;
  wire \Pipeline1_out1_reg[23]_i_1_n_10 ;
  wire \Pipeline1_out1_reg[23]_i_1_n_11 ;
  wire \Pipeline1_out1_reg[23]_i_1_n_12 ;
  wire \Pipeline1_out1_reg[23]_i_1_n_13 ;
  wire \Pipeline1_out1_reg[23]_i_1_n_14 ;
  wire \Pipeline1_out1_reg[23]_i_1_n_15 ;
  wire \Pipeline1_out1_reg[23]_i_1_n_2 ;
  wire \Pipeline1_out1_reg[23]_i_1_n_3 ;
  wire \Pipeline1_out1_reg[23]_i_1_n_4 ;
  wire \Pipeline1_out1_reg[23]_i_1_n_5 ;
  wire \Pipeline1_out1_reg[23]_i_1_n_6 ;
  wire \Pipeline1_out1_reg[23]_i_1_n_7 ;
  wire \Pipeline1_out1_reg[23]_i_1_n_8 ;
  wire \Pipeline1_out1_reg[23]_i_1_n_9 ;
  wire \Pipeline1_out1_reg[31]_i_1_n_0 ;
  wire \Pipeline1_out1_reg[31]_i_1_n_1 ;
  wire \Pipeline1_out1_reg[31]_i_1_n_10 ;
  wire \Pipeline1_out1_reg[31]_i_1_n_11 ;
  wire \Pipeline1_out1_reg[31]_i_1_n_12 ;
  wire \Pipeline1_out1_reg[31]_i_1_n_13 ;
  wire \Pipeline1_out1_reg[31]_i_1_n_14 ;
  wire \Pipeline1_out1_reg[31]_i_1_n_15 ;
  wire \Pipeline1_out1_reg[31]_i_1_n_2 ;
  wire \Pipeline1_out1_reg[31]_i_1_n_3 ;
  wire \Pipeline1_out1_reg[31]_i_1_n_4 ;
  wire \Pipeline1_out1_reg[31]_i_1_n_5 ;
  wire \Pipeline1_out1_reg[31]_i_1_n_6 ;
  wire \Pipeline1_out1_reg[31]_i_1_n_7 ;
  wire \Pipeline1_out1_reg[31]_i_1_n_8 ;
  wire \Pipeline1_out1_reg[31]_i_1_n_9 ;
  wire \Pipeline1_out1_reg[37]_i_1_n_10 ;
  wire \Pipeline1_out1_reg[37]_i_1_n_11 ;
  wire \Pipeline1_out1_reg[37]_i_1_n_12 ;
  wire \Pipeline1_out1_reg[37]_i_1_n_13 ;
  wire \Pipeline1_out1_reg[37]_i_1_n_14 ;
  wire \Pipeline1_out1_reg[37]_i_1_n_15 ;
  wire \Pipeline1_out1_reg[37]_i_1_n_3 ;
  wire \Pipeline1_out1_reg[37]_i_1_n_4 ;
  wire \Pipeline1_out1_reg[37]_i_1_n_5 ;
  wire \Pipeline1_out1_reg[37]_i_1_n_6 ;
  wire \Pipeline1_out1_reg[37]_i_1_n_7 ;
  wire \Pipeline1_out1_reg[7]_i_1_n_0 ;
  wire \Pipeline1_out1_reg[7]_i_1_n_1 ;
  wire \Pipeline1_out1_reg[7]_i_1_n_10 ;
  wire \Pipeline1_out1_reg[7]_i_1_n_11 ;
  wire \Pipeline1_out1_reg[7]_i_1_n_12 ;
  wire \Pipeline1_out1_reg[7]_i_1_n_13 ;
  wire \Pipeline1_out1_reg[7]_i_1_n_14 ;
  wire \Pipeline1_out1_reg[7]_i_1_n_15 ;
  wire \Pipeline1_out1_reg[7]_i_1_n_2 ;
  wire \Pipeline1_out1_reg[7]_i_1_n_3 ;
  wire \Pipeline1_out1_reg[7]_i_1_n_4 ;
  wire \Pipeline1_out1_reg[7]_i_1_n_5 ;
  wire \Pipeline1_out1_reg[7]_i_1_n_6 ;
  wire \Pipeline1_out1_reg[7]_i_1_n_7 ;
  wire \Pipeline1_out1_reg[7]_i_1_n_8 ;
  wire \Pipeline1_out1_reg[7]_i_1_n_9 ;
  wire [37:0]Pipeline_out1;
  wire \Pipeline_out1[0]_i_1_n_0 ;
  wire \Pipeline_out1[10]_i_1_n_0 ;
  wire \Pipeline_out1[11]_i_1_n_0 ;
  wire \Pipeline_out1[12]_i_1_n_0 ;
  wire \Pipeline_out1[13]_i_1_n_0 ;
  wire \Pipeline_out1[1]_i_1_n_0 ;
  wire \Pipeline_out1[2]_i_1_n_0 ;
  wire \Pipeline_out1[3]_i_1_n_0 ;
  wire \Pipeline_out1[4]_i_1_n_0 ;
  wire \Pipeline_out1[5]_i_1_n_0 ;
  wire \Pipeline_out1[6]_i_1_n_0 ;
  wire \Pipeline_out1[7]_i_1_n_0 ;
  wire \Pipeline_out1[8]_i_1_n_0 ;
  wire \Pipeline_out1[9]_i_1_n_0 ;
  wire ProtectOverflow_T_count_out11_carry__0_i_10_n_0;
  wire ProtectOverflow_T_count_out11_carry__0_i_11_n_0;
  wire ProtectOverflow_T_count_out11_carry__0_i_12_n_0;
  wire ProtectOverflow_T_count_out11_carry__0_i_13_n_0;
  wire ProtectOverflow_T_count_out11_carry__0_i_14_n_0;
  wire ProtectOverflow_T_count_out11_carry__0_i_15_n_0;
  wire ProtectOverflow_T_count_out11_carry__0_i_16_n_0;
  wire ProtectOverflow_T_count_out11_carry__0_i_1_n_0;
  wire ProtectOverflow_T_count_out11_carry__0_i_2_n_0;
  wire ProtectOverflow_T_count_out11_carry__0_i_3_n_0;
  wire ProtectOverflow_T_count_out11_carry__0_i_4_n_0;
  wire ProtectOverflow_T_count_out11_carry__0_i_5_n_0;
  wire ProtectOverflow_T_count_out11_carry__0_i_6_n_0;
  wire ProtectOverflow_T_count_out11_carry__0_i_7_n_0;
  wire ProtectOverflow_T_count_out11_carry__0_i_8_n_0;
  wire ProtectOverflow_T_count_out11_carry__0_i_9_n_0;
  wire ProtectOverflow_T_count_out11_carry__0_n_0;
  wire ProtectOverflow_T_count_out11_carry__0_n_1;
  wire ProtectOverflow_T_count_out11_carry__0_n_2;
  wire ProtectOverflow_T_count_out11_carry__0_n_3;
  wire ProtectOverflow_T_count_out11_carry__0_n_4;
  wire ProtectOverflow_T_count_out11_carry__0_n_5;
  wire ProtectOverflow_T_count_out11_carry__0_n_6;
  wire ProtectOverflow_T_count_out11_carry__0_n_7;
  wire ProtectOverflow_T_count_out11_carry__1_i_1_n_0;
  wire ProtectOverflow_T_count_out11_carry__1_i_2_n_0;
  wire ProtectOverflow_T_count_out11_carry__1_i_3_n_0;
  wire ProtectOverflow_T_count_out11_carry__1_i_4_n_0;
  wire ProtectOverflow_T_count_out11_carry__1_n_6;
  wire ProtectOverflow_T_count_out11_carry__1_n_7;
  wire ProtectOverflow_T_count_out11_carry_i_10_n_0;
  wire ProtectOverflow_T_count_out11_carry_i_11_n_0;
  wire ProtectOverflow_T_count_out11_carry_i_12_n_0;
  wire ProtectOverflow_T_count_out11_carry_i_13_n_0;
  wire ProtectOverflow_T_count_out11_carry_i_14_n_0;
  wire ProtectOverflow_T_count_out11_carry_i_15_n_0;
  wire ProtectOverflow_T_count_out11_carry_i_16_n_0;
  wire ProtectOverflow_T_count_out11_carry_i_1_n_0;
  wire ProtectOverflow_T_count_out11_carry_i_2_n_0;
  wire ProtectOverflow_T_count_out11_carry_i_3_n_0;
  wire ProtectOverflow_T_count_out11_carry_i_4_n_0;
  wire ProtectOverflow_T_count_out11_carry_i_5_n_0;
  wire ProtectOverflow_T_count_out11_carry_i_6_n_0;
  wire ProtectOverflow_T_count_out11_carry_i_7_n_0;
  wire ProtectOverflow_T_count_out11_carry_i_8_n_0;
  wire ProtectOverflow_T_count_out11_carry_i_9_n_0;
  wire ProtectOverflow_T_count_out11_carry_n_0;
  wire ProtectOverflow_T_count_out11_carry_n_1;
  wire ProtectOverflow_T_count_out11_carry_n_2;
  wire ProtectOverflow_T_count_out11_carry_n_3;
  wire ProtectOverflow_T_count_out11_carry_n_4;
  wire ProtectOverflow_T_count_out11_carry_n_5;
  wire ProtectOverflow_T_count_out11_carry_n_6;
  wire ProtectOverflow_T_count_out11_carry_n_7;
  wire [23:0]Q;
  wire [10:2]RESIZE;
  wire RSTP;
  wire [37:0]T_count_out1;
  wire \T_count_out1[37]_i_1_n_0 ;
  wire [31:0]\T_count_out1_reg[31]_0 ;
  wire \T_count_out1_reg[37]_0 ;
  wire [1:0]\T_count_out1_reg[7]_0 ;
  wire [37:14]T_count_switch_out1;
  wire [1:0]count_old1_out1;
  wire \count_old1_out1[0]_i_1_n_0 ;
  wire \count_old1_out1[1]_i_1_n_0 ;
  wire [15:0]\hold5_out1_reg[15] ;
  wire reset_old1_out1_reg_0;
  wire reset_old1_out1_reg_1;
  wire [37:14]speed_old_out1;
  wire [37:14]speed_old_switch_out1;
  wire speed_old_switch_out10_carry__0_i_1_n_0;
  wire speed_old_switch_out10_carry__0_i_2_n_0;
  wire speed_old_switch_out10_carry__0_i_3_n_0;
  wire speed_old_switch_out10_carry__0_i_4_n_0;
  wire speed_old_switch_out10_carry__0_i_5_n_0;
  wire speed_old_switch_out10_carry__0_i_6_n_0;
  wire speed_old_switch_out10_carry__0_i_7_n_0;
  wire speed_old_switch_out10_carry__0_i_8_n_0;
  wire speed_old_switch_out10_carry__0_n_0;
  wire speed_old_switch_out10_carry__0_n_1;
  wire speed_old_switch_out10_carry__0_n_10;
  wire speed_old_switch_out10_carry__0_n_11;
  wire speed_old_switch_out10_carry__0_n_12;
  wire speed_old_switch_out10_carry__0_n_13;
  wire speed_old_switch_out10_carry__0_n_14;
  wire speed_old_switch_out10_carry__0_n_15;
  wire speed_old_switch_out10_carry__0_n_2;
  wire speed_old_switch_out10_carry__0_n_3;
  wire speed_old_switch_out10_carry__0_n_4;
  wire speed_old_switch_out10_carry__0_n_5;
  wire speed_old_switch_out10_carry__0_n_6;
  wire speed_old_switch_out10_carry__0_n_7;
  wire speed_old_switch_out10_carry__0_n_8;
  wire speed_old_switch_out10_carry__0_n_9;
  wire speed_old_switch_out10_carry__1_i_1_n_0;
  wire speed_old_switch_out10_carry__1_i_2_n_0;
  wire speed_old_switch_out10_carry__1_i_3_n_0;
  wire speed_old_switch_out10_carry__1_i_4_n_0;
  wire speed_old_switch_out10_carry__1_i_5_n_0;
  wire speed_old_switch_out10_carry__1_i_6_n_0;
  wire speed_old_switch_out10_carry__1_i_7_n_0;
  wire speed_old_switch_out10_carry__1_i_8_n_0;
  wire speed_old_switch_out10_carry__1_n_0;
  wire speed_old_switch_out10_carry__1_n_1;
  wire speed_old_switch_out10_carry__1_n_10;
  wire speed_old_switch_out10_carry__1_n_11;
  wire speed_old_switch_out10_carry__1_n_12;
  wire speed_old_switch_out10_carry__1_n_13;
  wire speed_old_switch_out10_carry__1_n_14;
  wire speed_old_switch_out10_carry__1_n_15;
  wire speed_old_switch_out10_carry__1_n_2;
  wire speed_old_switch_out10_carry__1_n_3;
  wire speed_old_switch_out10_carry__1_n_4;
  wire speed_old_switch_out10_carry__1_n_5;
  wire speed_old_switch_out10_carry__1_n_6;
  wire speed_old_switch_out10_carry__1_n_7;
  wire speed_old_switch_out10_carry__1_n_8;
  wire speed_old_switch_out10_carry__1_n_9;
  wire speed_old_switch_out10_carry__2_i_1_n_0;
  wire speed_old_switch_out10_carry__2_i_2_n_0;
  wire speed_old_switch_out10_carry__2_i_3_n_0;
  wire speed_old_switch_out10_carry__2_i_4_n_0;
  wire speed_old_switch_out10_carry__2_i_5_n_0;
  wire speed_old_switch_out10_carry__2_i_6_n_0;
  wire speed_old_switch_out10_carry__2_i_7_n_0;
  wire speed_old_switch_out10_carry__2_i_8_n_0;
  wire speed_old_switch_out10_carry__2_n_0;
  wire speed_old_switch_out10_carry__2_n_1;
  wire speed_old_switch_out10_carry__2_n_10;
  wire speed_old_switch_out10_carry__2_n_11;
  wire speed_old_switch_out10_carry__2_n_12;
  wire speed_old_switch_out10_carry__2_n_13;
  wire speed_old_switch_out10_carry__2_n_14;
  wire speed_old_switch_out10_carry__2_n_15;
  wire speed_old_switch_out10_carry__2_n_2;
  wire speed_old_switch_out10_carry__2_n_3;
  wire speed_old_switch_out10_carry__2_n_4;
  wire speed_old_switch_out10_carry__2_n_5;
  wire speed_old_switch_out10_carry__2_n_6;
  wire speed_old_switch_out10_carry__2_n_7;
  wire speed_old_switch_out10_carry__2_n_8;
  wire speed_old_switch_out10_carry__2_n_9;
  wire speed_old_switch_out10_carry__3_i_1_n_0;
  wire speed_old_switch_out10_carry__3_i_2_n_0;
  wire speed_old_switch_out10_carry__3_i_3_n_0;
  wire speed_old_switch_out10_carry__3_i_4_n_0;
  wire speed_old_switch_out10_carry__3_i_5_n_0;
  wire speed_old_switch_out10_carry__3_i_6_n_0;
  wire speed_old_switch_out10_carry__3_n_10;
  wire speed_old_switch_out10_carry__3_n_11;
  wire speed_old_switch_out10_carry__3_n_12;
  wire speed_old_switch_out10_carry__3_n_13;
  wire speed_old_switch_out10_carry__3_n_14;
  wire speed_old_switch_out10_carry__3_n_15;
  wire speed_old_switch_out10_carry__3_n_3;
  wire speed_old_switch_out10_carry__3_n_4;
  wire speed_old_switch_out10_carry__3_n_5;
  wire speed_old_switch_out10_carry__3_n_6;
  wire speed_old_switch_out10_carry__3_n_7;
  wire speed_old_switch_out10_carry_i_1_n_0;
  wire speed_old_switch_out10_carry_i_2_n_0;
  wire speed_old_switch_out10_carry_i_3_n_0;
  wire speed_old_switch_out10_carry_i_4_n_0;
  wire speed_old_switch_out10_carry_i_5_n_0;
  wire speed_old_switch_out10_carry_i_6_n_0;
  wire speed_old_switch_out10_carry_i_7_n_0;
  wire speed_old_switch_out10_carry_i_8_n_0;
  wire speed_old_switch_out10_carry_i_9_n_0;
  wire speed_old_switch_out10_carry_n_0;
  wire speed_old_switch_out10_carry_n_1;
  wire speed_old_switch_out10_carry_n_10;
  wire speed_old_switch_out10_carry_n_11;
  wire speed_old_switch_out10_carry_n_12;
  wire speed_old_switch_out10_carry_n_13;
  wire speed_old_switch_out10_carry_n_14;
  wire speed_old_switch_out10_carry_n_15;
  wire speed_old_switch_out10_carry_n_2;
  wire speed_old_switch_out10_carry_n_3;
  wire speed_old_switch_out10_carry_n_4;
  wire speed_old_switch_out10_carry_n_5;
  wire speed_old_switch_out10_carry_n_6;
  wire speed_old_switch_out10_carry_n_7;
  wire speed_old_switch_out10_carry_n_8;
  wire speed_old_switch_out10_carry_n_9;
  wire [15:0]state;
  wire state_Out_tmp0_carry__0_i_10_n_0;
  wire state_Out_tmp0_carry__0_i_11_n_0;
  wire state_Out_tmp0_carry__0_i_12_n_0;
  wire state_Out_tmp0_carry__0_i_13_n_0;
  wire state_Out_tmp0_carry__0_i_14_n_0;
  wire state_Out_tmp0_carry__0_i_15_n_0;
  wire state_Out_tmp0_carry__0_i_1_n_0;
  wire state_Out_tmp0_carry__0_i_2_n_0;
  wire state_Out_tmp0_carry__0_i_3_n_0;
  wire state_Out_tmp0_carry__0_i_4_n_0;
  wire state_Out_tmp0_carry__0_i_5_n_0;
  wire state_Out_tmp0_carry__0_i_6_n_0;
  wire state_Out_tmp0_carry__0_i_7_n_0;
  wire state_Out_tmp0_carry__0_i_8_n_0;
  wire state_Out_tmp0_carry__0_i_9_n_0;
  wire [15:0]state_Out_unsigned;
  wire [15:0]state_prev;
  wire state_prev_carry__0_i_1_n_0;
  wire state_prev_carry__0_i_2_n_0;
  wire state_prev_carry__0_i_4_n_0;
  wire state_prev_carry__0_n_3;
  wire state_prev_carry__0_n_4;
  wire state_prev_carry__0_n_5;
  wire state_prev_carry__0_n_6;
  wire state_prev_carry__0_n_7;
  wire state_prev_carry_i_1_n_0;
  wire state_prev_carry_i_2_n_0;
  wire state_prev_carry_i_4_n_0;
  wire state_prev_carry_i_6_n_0;
  wire state_prev_carry_i_8_n_0;
  wire state_prev_carry_i_9_n_0;
  wire state_prev_carry_n_0;
  wire state_prev_carry_n_1;
  wire state_prev_carry_n_2;
  wire state_prev_carry_n_3;
  wire state_prev_carry_n_4;
  wire state_prev_carry_n_5;
  wire state_prev_carry_n_6;
  wire state_prev_carry_n_7;
  wire switch_compare_1_2;
  wire u_Count_n_16;
  wire u_Count_n_17;
  wire u_Count_n_18;
  wire u_Count_n_19;
  wire u_Count_n_20;
  wire u_Count_n_21;
  wire u_Count_n_22;
  wire u_Count_n_23;
  wire u_Count_n_24;
  wire u_Count_n_25;
  wire u_Count_n_26;
  wire u_Count_n_27;
  wire u_Count_n_28;
  wire u_Count_n_29;
  wire u_Count_n_30;
  wire u_Count_n_31;
  wire u_Count_n_32;
  wire u_Count_n_33;
  wire u_Count_n_34;
  wire u_Count_n_35;
  wire u_Count_n_36;
  wire u_Count_n_37;
  wire u_Count_n_38;
  wire u_Count_n_39;
  wire write_axi_enable;
  wire [7:0]NLW_Delay3_out10_carry_O_UNCONNECTED;
  wire [7:1]NLW_Delay3_out10_carry__0_CO_UNCONNECTED;
  wire [7:0]NLW_Delay3_out10_carry__0_O_UNCONNECTED;
  wire [7:7]\NLW_Delay5_out1_reg[23]_i_1_CO_UNCONNECTED ;
  wire [7:5]\NLW_Pipeline1_out1_reg[37]_i_1_CO_UNCONNECTED ;
  wire [7:6]\NLW_Pipeline1_out1_reg[37]_i_1_O_UNCONNECTED ;
  wire [7:0]NLW_ProtectOverflow_T_count_out11_carry_O_UNCONNECTED;
  wire [7:0]NLW_ProtectOverflow_T_count_out11_carry__0_O_UNCONNECTED;
  wire [7:3]NLW_ProtectOverflow_T_count_out11_carry__1_CO_UNCONNECTED;
  wire [7:0]NLW_ProtectOverflow_T_count_out11_carry__1_O_UNCONNECTED;
  wire [7:5]NLW_speed_old_switch_out10_carry__3_CO_UNCONNECTED;
  wire [7:6]NLW_speed_old_switch_out10_carry__3_O_UNCONNECTED;
  wire [7:5]NLW_state_prev_carry__0_CO_UNCONNECTED;
  wire [7:6]NLW_state_prev_carry__0_O_UNCONNECTED;

  FDRE \Delay1_out1_reg[0] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(state_prev[0]),
        .Q(Delay1_out1[0]),
        .R(RSTP));
  FDRE \Delay1_out1_reg[10] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(state_prev[10]),
        .Q(Delay1_out1[10]),
        .R(RSTP));
  FDRE \Delay1_out1_reg[11] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(state_prev[11]),
        .Q(Delay1_out1[11]),
        .R(RSTP));
  FDRE \Delay1_out1_reg[12] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(state_prev[12]),
        .Q(Delay1_out1[12]),
        .R(RSTP));
  FDRE \Delay1_out1_reg[15] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(state_prev[15]),
        .Q(Delay1_out1[15]),
        .R(RSTP));
  FDRE \Delay1_out1_reg[1] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(state_prev[1]),
        .Q(Delay1_out1[1]),
        .R(RSTP));
  FDRE \Delay1_out1_reg[2] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(state_prev[2]),
        .Q(Delay1_out1[2]),
        .R(RSTP));
  FDRE \Delay1_out1_reg[3] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(state_prev[3]),
        .Q(Delay1_out1[3]),
        .R(RSTP));
  FDRE \Delay1_out1_reg[4] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(state_prev[4]),
        .Q(Delay1_out1[4]),
        .R(RSTP));
  FDRE \Delay1_out1_reg[5] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(state_prev[5]),
        .Q(Delay1_out1[5]),
        .R(RSTP));
  FDRE \Delay1_out1_reg[6] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(state_prev[6]),
        .Q(Delay1_out1[6]),
        .R(RSTP));
  FDRE \Delay1_out1_reg[7] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(state_prev[7]),
        .Q(Delay1_out1[7]),
        .R(RSTP));
  FDRE \Delay1_out1_reg[8] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(state_prev[8]),
        .Q(Delay1_out1[8]),
        .R(RSTP));
  FDRE \Delay1_out1_reg[9] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(state_prev[9]),
        .Q(Delay1_out1[9]),
        .R(RSTP));
  (* COMPARATOR_THRESHOLD = "11" *) 
  CARRY8 Delay3_out10_carry
       (.CI(1'b0),
        .CI_TOP(1'b0),
        .CO({Delay3_out10_carry_n_0,Delay3_out10_carry_n_1,Delay3_out10_carry_n_2,Delay3_out10_carry_n_3,Delay3_out10_carry_n_4,Delay3_out10_carry_n_5,Delay3_out10_carry_n_6,Delay3_out10_carry_n_7}),
        .DI({Delay3_out10_carry_i_1_n_0,Delay3_out10_carry_i_2_n_0,Delay3_out10_carry_i_3_n_0,Delay3_out10_carry_i_4_n_0,Delay3_out10_carry_i_5_n_0,Delay3_out10_carry_i_6_n_0,Delay3_out10_carry_i_7_n_0,Delay3_out10_carry_i_8_n_0}),
        .O(NLW_Delay3_out10_carry_O_UNCONNECTED[7:0]),
        .S({Delay3_out10_carry_i_9_n_0,Delay3_out10_carry_i_10_n_0,Delay3_out10_carry_i_11_n_0,Delay3_out10_carry_i_12_n_0,Delay3_out10_carry_i_13_n_0,Delay3_out10_carry_i_14_n_0,Delay3_out10_carry_i_15_n_0,Delay3_out10_carry_i_16_n_0}));
  (* COMPARATOR_THRESHOLD = "11" *) 
  CARRY8 Delay3_out10_carry__0
       (.CI(Delay3_out10_carry_n_0),
        .CI_TOP(1'b0),
        .CO({NLW_Delay3_out10_carry__0_CO_UNCONNECTED[7:1],\Delay1_out1_reg[15]_0 }),
        .DI({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .O(NLW_Delay3_out10_carry__0_O_UNCONNECTED[7:0]),
        .S({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,Delay3_out10_carry__0_i_1_n_0}));
  LUT1 #(
    .INIT(2'h1)) 
    Delay3_out10_carry__0_i_1
       (.I0(Delay1_out1[15]),
        .O(Delay3_out10_carry__0_i_1_n_0));
  LUT3 #(
    .INIT(8'h70)) 
    Delay3_out10_carry_i_1
       (.I0(OnlyAllowInNewPeriod_out1__0[15]),
        .I1(OnlyAllowInNewPeriod_out1__0[14]),
        .I2(Delay1_out1[15]),
        .O(Delay3_out10_carry_i_1_n_0));
  LUT4 #(
    .INIT(16'h9009)) 
    Delay3_out10_carry_i_10
       (.I0(OnlyAllowInNewPeriod_out1__0[13]),
        .I1(Delay1_out1[15]),
        .I2(OnlyAllowInNewPeriod_out1__0[12]),
        .I3(Delay1_out1[12]),
        .O(Delay3_out10_carry_i_10_n_0));
  LUT4 #(
    .INIT(16'h9009)) 
    Delay3_out10_carry_i_11
       (.I0(OnlyAllowInNewPeriod_out1__0[11]),
        .I1(Delay1_out1[11]),
        .I2(OnlyAllowInNewPeriod_out1__0[10]),
        .I3(Delay1_out1[10]),
        .O(Delay3_out10_carry_i_11_n_0));
  LUT4 #(
    .INIT(16'h9009)) 
    Delay3_out10_carry_i_12
       (.I0(OnlyAllowInNewPeriod_out1__0[9]),
        .I1(Delay1_out1[9]),
        .I2(OnlyAllowInNewPeriod_out1__0[8]),
        .I3(Delay1_out1[8]),
        .O(Delay3_out10_carry_i_12_n_0));
  LUT4 #(
    .INIT(16'h9009)) 
    Delay3_out10_carry_i_13
       (.I0(OnlyAllowInNewPeriod_out1__0[7]),
        .I1(Delay1_out1[7]),
        .I2(OnlyAllowInNewPeriod_out1__0[6]),
        .I3(Delay1_out1[6]),
        .O(Delay3_out10_carry_i_13_n_0));
  LUT4 #(
    .INIT(16'h9009)) 
    Delay3_out10_carry_i_14
       (.I0(OnlyAllowInNewPeriod_out1__0[5]),
        .I1(Delay1_out1[5]),
        .I2(OnlyAllowInNewPeriod_out1__0[4]),
        .I3(Delay1_out1[4]),
        .O(Delay3_out10_carry_i_14_n_0));
  LUT4 #(
    .INIT(16'h9009)) 
    Delay3_out10_carry_i_15
       (.I0(OnlyAllowInNewPeriod_out1__0[3]),
        .I1(Delay1_out1[3]),
        .I2(OnlyAllowInNewPeriod_out1__0[2]),
        .I3(Delay1_out1[2]),
        .O(Delay3_out10_carry_i_15_n_0));
  LUT4 #(
    .INIT(16'h9009)) 
    Delay3_out10_carry_i_16
       (.I0(OnlyAllowInNewPeriod_out1__0[1]),
        .I1(Delay1_out1[1]),
        .I2(OnlyAllowInNewPeriod_out1__0[0]),
        .I3(Delay1_out1[0]),
        .O(Delay3_out10_carry_i_16_n_0));
  LUT4 #(
    .INIT(16'h22B2)) 
    Delay3_out10_carry_i_2
       (.I0(Delay1_out1[15]),
        .I1(OnlyAllowInNewPeriod_out1__0[13]),
        .I2(Delay1_out1[12]),
        .I3(OnlyAllowInNewPeriod_out1__0[12]),
        .O(Delay3_out10_carry_i_2_n_0));
  LUT4 #(
    .INIT(16'h22B2)) 
    Delay3_out10_carry_i_3
       (.I0(Delay1_out1[11]),
        .I1(OnlyAllowInNewPeriod_out1__0[11]),
        .I2(Delay1_out1[10]),
        .I3(OnlyAllowInNewPeriod_out1__0[10]),
        .O(Delay3_out10_carry_i_3_n_0));
  LUT4 #(
    .INIT(16'h22B2)) 
    Delay3_out10_carry_i_4
       (.I0(Delay1_out1[9]),
        .I1(OnlyAllowInNewPeriod_out1__0[9]),
        .I2(Delay1_out1[8]),
        .I3(OnlyAllowInNewPeriod_out1__0[8]),
        .O(Delay3_out10_carry_i_4_n_0));
  LUT4 #(
    .INIT(16'h22B2)) 
    Delay3_out10_carry_i_5
       (.I0(Delay1_out1[7]),
        .I1(OnlyAllowInNewPeriod_out1__0[7]),
        .I2(Delay1_out1[6]),
        .I3(OnlyAllowInNewPeriod_out1__0[6]),
        .O(Delay3_out10_carry_i_5_n_0));
  LUT4 #(
    .INIT(16'h22B2)) 
    Delay3_out10_carry_i_6
       (.I0(Delay1_out1[5]),
        .I1(OnlyAllowInNewPeriod_out1__0[5]),
        .I2(Delay1_out1[4]),
        .I3(OnlyAllowInNewPeriod_out1__0[4]),
        .O(Delay3_out10_carry_i_6_n_0));
  LUT4 #(
    .INIT(16'h22B2)) 
    Delay3_out10_carry_i_7
       (.I0(Delay1_out1[3]),
        .I1(OnlyAllowInNewPeriod_out1__0[3]),
        .I2(Delay1_out1[2]),
        .I3(OnlyAllowInNewPeriod_out1__0[2]),
        .O(Delay3_out10_carry_i_7_n_0));
  LUT4 #(
    .INIT(16'h22B2)) 
    Delay3_out10_carry_i_8
       (.I0(Delay1_out1[1]),
        .I1(OnlyAllowInNewPeriod_out1__0[1]),
        .I2(Delay1_out1[0]),
        .I3(OnlyAllowInNewPeriod_out1__0[0]),
        .O(Delay3_out10_carry_i_8_n_0));
  LUT3 #(
    .INIT(8'h81)) 
    Delay3_out10_carry_i_9
       (.I0(Delay1_out1[15]),
        .I1(OnlyAllowInNewPeriod_out1__0[14]),
        .I2(OnlyAllowInNewPeriod_out1__0[15]),
        .O(Delay3_out10_carry_i_9_n_0));
  FDRE Delay3_out1_reg
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\Delay1_out1_reg[15]_0 ),
        .Q(Delay3_out1),
        .R(RSTP));
  LUT2 #(
    .INIT(4'h6)) 
    \Delay5_out1[15]_i_2 
       (.I0(\Delay5_out1_reg[7]_0 ),
        .I1(\Delay5_out1_reg[23]_0 [15]),
        .O(\Delay5_out1[15]_i_2_n_0 ));
  LUT2 #(
    .INIT(4'h6)) 
    \Delay5_out1[15]_i_3 
       (.I0(\Delay5_out1_reg[7]_0 ),
        .I1(\Delay5_out1_reg[23]_0 [14]),
        .O(\Delay5_out1[15]_i_3_n_0 ));
  LUT2 #(
    .INIT(4'h6)) 
    \Delay5_out1[15]_i_4 
       (.I0(\Delay5_out1_reg[7]_0 ),
        .I1(\Delay5_out1_reg[23]_0 [13]),
        .O(\Delay5_out1[15]_i_4_n_0 ));
  LUT2 #(
    .INIT(4'h6)) 
    \Delay5_out1[15]_i_5 
       (.I0(\Delay5_out1_reg[7]_0 ),
        .I1(\Delay5_out1_reg[23]_0 [12]),
        .O(\Delay5_out1[15]_i_5_n_0 ));
  LUT2 #(
    .INIT(4'h6)) 
    \Delay5_out1[15]_i_6 
       (.I0(\Delay5_out1_reg[7]_0 ),
        .I1(\Delay5_out1_reg[23]_0 [11]),
        .O(\Delay5_out1[15]_i_6_n_0 ));
  LUT2 #(
    .INIT(4'h6)) 
    \Delay5_out1[15]_i_7 
       (.I0(\Delay5_out1_reg[7]_0 ),
        .I1(\Delay5_out1_reg[23]_0 [10]),
        .O(\Delay5_out1[15]_i_7_n_0 ));
  LUT2 #(
    .INIT(4'h6)) 
    \Delay5_out1[15]_i_8 
       (.I0(\Delay5_out1_reg[7]_0 ),
        .I1(\Delay5_out1_reg[23]_0 [9]),
        .O(\Delay5_out1[15]_i_8_n_0 ));
  LUT2 #(
    .INIT(4'h6)) 
    \Delay5_out1[15]_i_9 
       (.I0(\Delay5_out1_reg[7]_0 ),
        .I1(\Delay5_out1_reg[23]_0 [8]),
        .O(\Delay5_out1[15]_i_9_n_0 ));
  LUT2 #(
    .INIT(4'h6)) 
    \Delay5_out1[23]_i_2 
       (.I0(\Delay5_out1_reg[7]_0 ),
        .I1(\Delay5_out1_reg[23]_0 [22]),
        .O(\Delay5_out1[23]_i_2_n_0 ));
  LUT2 #(
    .INIT(4'h6)) 
    \Delay5_out1[23]_i_3 
       (.I0(\Delay5_out1_reg[7]_0 ),
        .I1(\Delay5_out1_reg[23]_0 [21]),
        .O(\Delay5_out1[23]_i_3_n_0 ));
  LUT2 #(
    .INIT(4'h6)) 
    \Delay5_out1[23]_i_4 
       (.I0(\Delay5_out1_reg[7]_0 ),
        .I1(\Delay5_out1_reg[23]_0 [20]),
        .O(\Delay5_out1[23]_i_4_n_0 ));
  LUT2 #(
    .INIT(4'h6)) 
    \Delay5_out1[23]_i_5 
       (.I0(\Delay5_out1_reg[7]_0 ),
        .I1(\Delay5_out1_reg[23]_0 [19]),
        .O(\Delay5_out1[23]_i_5_n_0 ));
  LUT2 #(
    .INIT(4'h6)) 
    \Delay5_out1[23]_i_6 
       (.I0(\Delay5_out1_reg[7]_0 ),
        .I1(\Delay5_out1_reg[23]_0 [18]),
        .O(\Delay5_out1[23]_i_6_n_0 ));
  LUT2 #(
    .INIT(4'h6)) 
    \Delay5_out1[23]_i_7 
       (.I0(\Delay5_out1_reg[7]_0 ),
        .I1(\Delay5_out1_reg[23]_0 [17]),
        .O(\Delay5_out1[23]_i_7_n_0 ));
  LUT2 #(
    .INIT(4'h6)) 
    \Delay5_out1[23]_i_8 
       (.I0(\Delay5_out1_reg[7]_0 ),
        .I1(\Delay5_out1_reg[23]_0 [16]),
        .O(\Delay5_out1[23]_i_8_n_0 ));
  LUT1 #(
    .INIT(2'h2)) 
    \Delay5_out1[7]_i_10 
       (.I0(\Delay5_out1_reg[23]_0 [0]),
        .O(\Delay5_out1[7]_i_10_n_0 ));
  LUT1 #(
    .INIT(2'h2)) 
    \Delay5_out1[7]_i_2 
       (.I0(\Delay5_out1_reg[7]_0 ),
        .O(\Delay5_out1[7]_i_2_n_0 ));
  LUT2 #(
    .INIT(4'h6)) 
    \Delay5_out1[7]_i_3 
       (.I0(\Delay5_out1_reg[7]_0 ),
        .I1(\Delay5_out1_reg[23]_0 [7]),
        .O(\Delay5_out1[7]_i_3_n_0 ));
  LUT2 #(
    .INIT(4'h6)) 
    \Delay5_out1[7]_i_4 
       (.I0(\Delay5_out1_reg[7]_0 ),
        .I1(\Delay5_out1_reg[23]_0 [6]),
        .O(\Delay5_out1[7]_i_4_n_0 ));
  LUT2 #(
    .INIT(4'h6)) 
    \Delay5_out1[7]_i_5 
       (.I0(\Delay5_out1_reg[7]_0 ),
        .I1(\Delay5_out1_reg[23]_0 [5]),
        .O(\Delay5_out1[7]_i_5_n_0 ));
  LUT2 #(
    .INIT(4'h6)) 
    \Delay5_out1[7]_i_6 
       (.I0(\Delay5_out1_reg[7]_0 ),
        .I1(\Delay5_out1_reg[23]_0 [4]),
        .O(\Delay5_out1[7]_i_6_n_0 ));
  LUT2 #(
    .INIT(4'h6)) 
    \Delay5_out1[7]_i_7 
       (.I0(\Delay5_out1_reg[7]_0 ),
        .I1(\Delay5_out1_reg[23]_0 [3]),
        .O(\Delay5_out1[7]_i_7_n_0 ));
  LUT2 #(
    .INIT(4'h6)) 
    \Delay5_out1[7]_i_8 
       (.I0(\Delay5_out1_reg[7]_0 ),
        .I1(\Delay5_out1_reg[23]_0 [2]),
        .O(\Delay5_out1[7]_i_8_n_0 ));
  LUT2 #(
    .INIT(4'h6)) 
    \Delay5_out1[7]_i_9 
       (.I0(\Delay5_out1_reg[7]_0 ),
        .I1(\Delay5_out1_reg[23]_0 [1]),
        .O(\Delay5_out1[7]_i_9_n_0 ));
  FDRE \Delay5_out1_reg[0] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\Delay5_out1_reg[7]_i_1_n_15 ),
        .Q(Delay5_out1[0]),
        .R(RSTP));
  FDRE \Delay5_out1_reg[10] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\Delay5_out1_reg[15]_i_1_n_13 ),
        .Q(Delay5_out1[10]),
        .R(RSTP));
  FDRE \Delay5_out1_reg[11] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\Delay5_out1_reg[15]_i_1_n_12 ),
        .Q(Delay5_out1[11]),
        .R(RSTP));
  FDRE \Delay5_out1_reg[12] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\Delay5_out1_reg[15]_i_1_n_11 ),
        .Q(Delay5_out1[12]),
        .R(RSTP));
  FDRE \Delay5_out1_reg[13] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\Delay5_out1_reg[15]_i_1_n_10 ),
        .Q(Delay5_out1[13]),
        .R(RSTP));
  FDRE \Delay5_out1_reg[14] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\Delay5_out1_reg[15]_i_1_n_9 ),
        .Q(Delay5_out1[14]),
        .R(RSTP));
  FDRE \Delay5_out1_reg[15] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\Delay5_out1_reg[15]_i_1_n_8 ),
        .Q(Delay5_out1[15]),
        .R(RSTP));
  (* ADDER_THRESHOLD = "35" *) 
  CARRY8 \Delay5_out1_reg[15]_i_1 
       (.CI(\Delay5_out1_reg[7]_i_1_n_0 ),
        .CI_TOP(1'b0),
        .CO({\Delay5_out1_reg[15]_i_1_n_0 ,\Delay5_out1_reg[15]_i_1_n_1 ,\Delay5_out1_reg[15]_i_1_n_2 ,\Delay5_out1_reg[15]_i_1_n_3 ,\Delay5_out1_reg[15]_i_1_n_4 ,\Delay5_out1_reg[15]_i_1_n_5 ,\Delay5_out1_reg[15]_i_1_n_6 ,\Delay5_out1_reg[15]_i_1_n_7 }),
        .DI({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .O({\Delay5_out1_reg[15]_i_1_n_8 ,\Delay5_out1_reg[15]_i_1_n_9 ,\Delay5_out1_reg[15]_i_1_n_10 ,\Delay5_out1_reg[15]_i_1_n_11 ,\Delay5_out1_reg[15]_i_1_n_12 ,\Delay5_out1_reg[15]_i_1_n_13 ,\Delay5_out1_reg[15]_i_1_n_14 ,\Delay5_out1_reg[15]_i_1_n_15 }),
        .S({\Delay5_out1[15]_i_2_n_0 ,\Delay5_out1[15]_i_3_n_0 ,\Delay5_out1[15]_i_4_n_0 ,\Delay5_out1[15]_i_5_n_0 ,\Delay5_out1[15]_i_6_n_0 ,\Delay5_out1[15]_i_7_n_0 ,\Delay5_out1[15]_i_8_n_0 ,\Delay5_out1[15]_i_9_n_0 }));
  FDRE \Delay5_out1_reg[16] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\Delay5_out1_reg[23]_i_1_n_15 ),
        .Q(Delay5_out1[16]),
        .R(RSTP));
  FDRE \Delay5_out1_reg[17] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\Delay5_out1_reg[23]_i_1_n_14 ),
        .Q(Delay5_out1[17]),
        .R(RSTP));
  FDRE \Delay5_out1_reg[18] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\Delay5_out1_reg[23]_i_1_n_13 ),
        .Q(Delay5_out1[18]),
        .R(RSTP));
  FDRE \Delay5_out1_reg[19] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\Delay5_out1_reg[23]_i_1_n_12 ),
        .Q(Delay5_out1[19]),
        .R(RSTP));
  FDRE \Delay5_out1_reg[1] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\Delay5_out1_reg[7]_i_1_n_14 ),
        .Q(Delay5_out1[1]),
        .R(RSTP));
  FDRE \Delay5_out1_reg[20] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\Delay5_out1_reg[23]_i_1_n_11 ),
        .Q(Delay5_out1[20]),
        .R(RSTP));
  FDRE \Delay5_out1_reg[21] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\Delay5_out1_reg[23]_i_1_n_10 ),
        .Q(Delay5_out1[21]),
        .R(RSTP));
  FDRE \Delay5_out1_reg[22] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\Delay5_out1_reg[23]_i_1_n_9 ),
        .Q(Delay5_out1[22]),
        .R(RSTP));
  FDRE \Delay5_out1_reg[23] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\Delay5_out1_reg[23]_i_1_n_8 ),
        .Q(Delay5_out1[23]),
        .R(RSTP));
  (* ADDER_THRESHOLD = "35" *) 
  CARRY8 \Delay5_out1_reg[23]_i_1 
       (.CI(\Delay5_out1_reg[15]_i_1_n_0 ),
        .CI_TOP(1'b0),
        .CO({\NLW_Delay5_out1_reg[23]_i_1_CO_UNCONNECTED [7],\Delay5_out1_reg[23]_i_1_n_1 ,\Delay5_out1_reg[23]_i_1_n_2 ,\Delay5_out1_reg[23]_i_1_n_3 ,\Delay5_out1_reg[23]_i_1_n_4 ,\Delay5_out1_reg[23]_i_1_n_5 ,\Delay5_out1_reg[23]_i_1_n_6 ,\Delay5_out1_reg[23]_i_1_n_7 }),
        .DI({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .O({\Delay5_out1_reg[23]_i_1_n_8 ,\Delay5_out1_reg[23]_i_1_n_9 ,\Delay5_out1_reg[23]_i_1_n_10 ,\Delay5_out1_reg[23]_i_1_n_11 ,\Delay5_out1_reg[23]_i_1_n_12 ,\Delay5_out1_reg[23]_i_1_n_13 ,\Delay5_out1_reg[23]_i_1_n_14 ,\Delay5_out1_reg[23]_i_1_n_15 }),
        .S({1'b0,\Delay5_out1[23]_i_2_n_0 ,\Delay5_out1[23]_i_3_n_0 ,\Delay5_out1[23]_i_4_n_0 ,\Delay5_out1[23]_i_5_n_0 ,\Delay5_out1[23]_i_6_n_0 ,\Delay5_out1[23]_i_7_n_0 ,\Delay5_out1[23]_i_8_n_0 }));
  FDRE \Delay5_out1_reg[2] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\Delay5_out1_reg[7]_i_1_n_13 ),
        .Q(Delay5_out1[2]),
        .R(RSTP));
  FDRE \Delay5_out1_reg[3] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\Delay5_out1_reg[7]_i_1_n_12 ),
        .Q(Delay5_out1[3]),
        .R(RSTP));
  FDRE \Delay5_out1_reg[4] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\Delay5_out1_reg[7]_i_1_n_11 ),
        .Q(Delay5_out1[4]),
        .R(RSTP));
  FDRE \Delay5_out1_reg[5] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\Delay5_out1_reg[7]_i_1_n_10 ),
        .Q(Delay5_out1[5]),
        .R(RSTP));
  FDRE \Delay5_out1_reg[6] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\Delay5_out1_reg[7]_i_1_n_9 ),
        .Q(Delay5_out1[6]),
        .R(RSTP));
  FDRE \Delay5_out1_reg[7] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\Delay5_out1_reg[7]_i_1_n_8 ),
        .Q(Delay5_out1[7]),
        .R(RSTP));
  (* ADDER_THRESHOLD = "35" *) 
  CARRY8 \Delay5_out1_reg[7]_i_1 
       (.CI(1'b0),
        .CI_TOP(1'b0),
        .CO({\Delay5_out1_reg[7]_i_1_n_0 ,\Delay5_out1_reg[7]_i_1_n_1 ,\Delay5_out1_reg[7]_i_1_n_2 ,\Delay5_out1_reg[7]_i_1_n_3 ,\Delay5_out1_reg[7]_i_1_n_4 ,\Delay5_out1_reg[7]_i_1_n_5 ,\Delay5_out1_reg[7]_i_1_n_6 ,\Delay5_out1_reg[7]_i_1_n_7 }),
        .DI({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,\Delay5_out1[7]_i_2_n_0 }),
        .O({\Delay5_out1_reg[7]_i_1_n_8 ,\Delay5_out1_reg[7]_i_1_n_9 ,\Delay5_out1_reg[7]_i_1_n_10 ,\Delay5_out1_reg[7]_i_1_n_11 ,\Delay5_out1_reg[7]_i_1_n_12 ,\Delay5_out1_reg[7]_i_1_n_13 ,\Delay5_out1_reg[7]_i_1_n_14 ,\Delay5_out1_reg[7]_i_1_n_15 }),
        .S({\Delay5_out1[7]_i_3_n_0 ,\Delay5_out1[7]_i_4_n_0 ,\Delay5_out1[7]_i_5_n_0 ,\Delay5_out1[7]_i_6_n_0 ,\Delay5_out1[7]_i_7_n_0 ,\Delay5_out1[7]_i_8_n_0 ,\Delay5_out1[7]_i_9_n_0 ,\Delay5_out1[7]_i_10_n_0 }));
  FDRE \Delay5_out1_reg[8] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\Delay5_out1_reg[15]_i_1_n_15 ),
        .Q(Delay5_out1[8]),
        .R(RSTP));
  FDRE \Delay5_out1_reg[9] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\Delay5_out1_reg[15]_i_1_n_14 ),
        .Q(Delay5_out1[9]),
        .R(RSTP));
  FDRE \Delay6_out1_reg[0] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(u_Count_n_23),
        .Q(Delay6_out1_reg[0]),
        .R(RSTP));
  FDRE \Delay6_out1_reg[10] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(u_Count_n_29),
        .Q(Delay6_out1_reg[10]),
        .R(RSTP));
  FDRE \Delay6_out1_reg[11] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(u_Count_n_28),
        .Q(Delay6_out1_reg[11]),
        .R(RSTP));
  FDRE \Delay6_out1_reg[12] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(u_Count_n_27),
        .Q(Delay6_out1_reg[12]),
        .R(RSTP));
  FDRE \Delay6_out1_reg[13] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(u_Count_n_26),
        .Q(Delay6_out1_reg[13]),
        .R(RSTP));
  FDRE \Delay6_out1_reg[14] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(u_Count_n_25),
        .Q(Delay6_out1_reg[14]),
        .R(RSTP));
  FDRE \Delay6_out1_reg[15] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(u_Count_n_24),
        .Q(Delay6_out1_reg[15]),
        .R(RSTP));
  FDRE \Delay6_out1_reg[16] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(u_Count_n_39),
        .Q(Delay6_out1_reg[16]),
        .R(RSTP));
  FDRE \Delay6_out1_reg[17] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(u_Count_n_38),
        .Q(Delay6_out1_reg[17]),
        .R(RSTP));
  FDRE \Delay6_out1_reg[18] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(u_Count_n_37),
        .Q(Delay6_out1_reg[18]),
        .R(RSTP));
  FDRE \Delay6_out1_reg[19] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(u_Count_n_36),
        .Q(Delay6_out1_reg[19]),
        .R(RSTP));
  FDRE \Delay6_out1_reg[1] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(u_Count_n_22),
        .Q(Delay6_out1_reg[1]),
        .R(RSTP));
  FDRE \Delay6_out1_reg[20] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(u_Count_n_35),
        .Q(Delay6_out1_reg[20]),
        .R(RSTP));
  FDRE \Delay6_out1_reg[21] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(u_Count_n_34),
        .Q(Delay6_out1_reg[21]),
        .R(RSTP));
  FDRE \Delay6_out1_reg[22] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(u_Count_n_33),
        .Q(Delay6_out1_reg[22]),
        .R(RSTP));
  FDRE \Delay6_out1_reg[23] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(u_Count_n_32),
        .Q(Delay6_out1_reg[23]),
        .R(RSTP));
  FDRE \Delay6_out1_reg[2] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(u_Count_n_21),
        .Q(Delay6_out1_reg[2]),
        .R(RSTP));
  FDRE \Delay6_out1_reg[3] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(u_Count_n_20),
        .Q(Delay6_out1_reg[3]),
        .R(RSTP));
  FDRE \Delay6_out1_reg[4] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(u_Count_n_19),
        .Q(Delay6_out1_reg[4]),
        .R(RSTP));
  FDRE \Delay6_out1_reg[5] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(u_Count_n_18),
        .Q(Delay6_out1_reg[5]),
        .R(RSTP));
  FDRE \Delay6_out1_reg[6] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(u_Count_n_17),
        .Q(Delay6_out1_reg[6]),
        .R(RSTP));
  FDRE \Delay6_out1_reg[7] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(u_Count_n_16),
        .Q(Delay6_out1_reg[7]),
        .R(RSTP));
  FDRE \Delay6_out1_reg[8] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(u_Count_n_31),
        .Q(Delay6_out1_reg[8]),
        .R(RSTP));
  FDRE \Delay6_out1_reg[9] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(u_Count_n_30),
        .Q(Delay6_out1_reg[9]),
        .R(RSTP));
  FDRE Delay7_ctrl_delay_out_reg
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(1'b1),
        .Q(Delay7_ctrl_delay_out),
        .R(RSTP));
  FDRE \Delay7_out_reg[0] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(state_Out_unsigned[0]),
        .Q(Delay7_out_reg[0]),
        .R(RSTP));
  FDRE \Delay7_out_reg[10] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(state_Out_unsigned[10]),
        .Q(Delay7_out_reg[10]),
        .R(RSTP));
  FDRE \Delay7_out_reg[11] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(state_Out_unsigned[11]),
        .Q(Delay7_out_reg[11]),
        .R(RSTP));
  FDRE \Delay7_out_reg[12] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(state_Out_unsigned[12]),
        .Q(Delay7_out_reg[12]),
        .R(RSTP));
  FDRE \Delay7_out_reg[13] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(state_Out_unsigned[13]),
        .Q(Delay7_out_reg[13]),
        .R(RSTP));
  FDRE \Delay7_out_reg[14] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(state_Out_unsigned[14]),
        .Q(Delay7_out_reg[14]),
        .R(RSTP));
  FDRE \Delay7_out_reg[15] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(state_Out_unsigned[15]),
        .Q(Delay7_out_reg[15]),
        .R(RSTP));
  FDRE \Delay7_out_reg[1] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(state_Out_unsigned[1]),
        .Q(Delay7_out_reg[1]),
        .R(RSTP));
  FDRE \Delay7_out_reg[2] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(state_Out_unsigned[2]),
        .Q(Delay7_out_reg[2]),
        .R(RSTP));
  FDRE \Delay7_out_reg[3] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(state_Out_unsigned[3]),
        .Q(Delay7_out_reg[3]),
        .R(RSTP));
  FDRE \Delay7_out_reg[4] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(state_Out_unsigned[4]),
        .Q(Delay7_out_reg[4]),
        .R(RSTP));
  FDRE \Delay7_out_reg[5] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(state_Out_unsigned[5]),
        .Q(Delay7_out_reg[5]),
        .R(RSTP));
  FDRE \Delay7_out_reg[6] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(state_Out_unsigned[6]),
        .Q(Delay7_out_reg[6]),
        .R(RSTP));
  FDRE \Delay7_out_reg[7] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(state_Out_unsigned[7]),
        .Q(Delay7_out_reg[7]),
        .R(RSTP));
  FDRE \Delay7_out_reg[8] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(state_Out_unsigned[8]),
        .Q(Delay7_out_reg[8]),
        .R(RSTP));
  FDRE \Delay7_out_reg[9] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(state_Out_unsigned[9]),
        .Q(Delay7_out_reg[9]),
        .R(RSTP));
  (* SOFT_HLUTNM = "soft_lutpair137" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    Div_i1_mul_temp_i_1
       (.I0(OnlyAllowInNewPeriod_out1__0[15]),
        .I1(\Delay1_out1_reg[15]_0 ),
        .I2(\hold5_out1_reg[15] [15]),
        .O(B[15]));
  (* SOFT_HLUTNM = "soft_lutpair146" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    Div_i1_mul_temp_i_10
       (.I0(OnlyAllowInNewPeriod_out1__0[6]),
        .I1(\Delay1_out1_reg[15]_0 ),
        .I2(\hold5_out1_reg[15] [6]),
        .O(B[6]));
  (* SOFT_HLUTNM = "soft_lutpair147" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    Div_i1_mul_temp_i_11
       (.I0(OnlyAllowInNewPeriod_out1__0[5]),
        .I1(\Delay1_out1_reg[15]_0 ),
        .I2(\hold5_out1_reg[15] [5]),
        .O(B[5]));
  (* SOFT_HLUTNM = "soft_lutpair148" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    Div_i1_mul_temp_i_12
       (.I0(OnlyAllowInNewPeriod_out1__0[4]),
        .I1(\Delay1_out1_reg[15]_0 ),
        .I2(\hold5_out1_reg[15] [4]),
        .O(B[4]));
  (* SOFT_HLUTNM = "soft_lutpair149" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    Div_i1_mul_temp_i_13
       (.I0(OnlyAllowInNewPeriod_out1__0[3]),
        .I1(\Delay1_out1_reg[15]_0 ),
        .I2(\hold5_out1_reg[15] [3]),
        .O(B[3]));
  (* SOFT_HLUTNM = "soft_lutpair150" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    Div_i1_mul_temp_i_14
       (.I0(OnlyAllowInNewPeriod_out1__0[2]),
        .I1(\Delay1_out1_reg[15]_0 ),
        .I2(\hold5_out1_reg[15] [2]),
        .O(B[2]));
  (* SOFT_HLUTNM = "soft_lutpair151" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    Div_i1_mul_temp_i_15
       (.I0(OnlyAllowInNewPeriod_out1__0[1]),
        .I1(\Delay1_out1_reg[15]_0 ),
        .I2(\hold5_out1_reg[15] [1]),
        .O(B[1]));
  (* SOFT_HLUTNM = "soft_lutpair152" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    Div_i1_mul_temp_i_16
       (.I0(OnlyAllowInNewPeriod_out1__0[0]),
        .I1(\Delay1_out1_reg[15]_0 ),
        .I2(\hold5_out1_reg[15] [0]),
        .O(B[0]));
  (* SOFT_HLUTNM = "soft_lutpair138" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    Div_i1_mul_temp_i_2
       (.I0(OnlyAllowInNewPeriod_out1__0[14]),
        .I1(\Delay1_out1_reg[15]_0 ),
        .I2(\hold5_out1_reg[15] [14]),
        .O(B[14]));
  (* SOFT_HLUTNM = "soft_lutpair139" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    Div_i1_mul_temp_i_3
       (.I0(OnlyAllowInNewPeriod_out1__0[13]),
        .I1(\Delay1_out1_reg[15]_0 ),
        .I2(\hold5_out1_reg[15] [13]),
        .O(B[13]));
  (* SOFT_HLUTNM = "soft_lutpair140" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    Div_i1_mul_temp_i_4
       (.I0(OnlyAllowInNewPeriod_out1__0[12]),
        .I1(\Delay1_out1_reg[15]_0 ),
        .I2(\hold5_out1_reg[15] [12]),
        .O(B[12]));
  (* SOFT_HLUTNM = "soft_lutpair141" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    Div_i1_mul_temp_i_5
       (.I0(OnlyAllowInNewPeriod_out1__0[11]),
        .I1(\Delay1_out1_reg[15]_0 ),
        .I2(\hold5_out1_reg[15] [11]),
        .O(B[11]));
  (* SOFT_HLUTNM = "soft_lutpair142" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    Div_i1_mul_temp_i_6
       (.I0(OnlyAllowInNewPeriod_out1__0[10]),
        .I1(\Delay1_out1_reg[15]_0 ),
        .I2(\hold5_out1_reg[15] [10]),
        .O(B[10]));
  (* SOFT_HLUTNM = "soft_lutpair143" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    Div_i1_mul_temp_i_7
       (.I0(OnlyAllowInNewPeriod_out1__0[9]),
        .I1(\Delay1_out1_reg[15]_0 ),
        .I2(\hold5_out1_reg[15] [9]),
        .O(B[9]));
  (* SOFT_HLUTNM = "soft_lutpair144" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    Div_i1_mul_temp_i_8
       (.I0(OnlyAllowInNewPeriod_out1__0[8]),
        .I1(\Delay1_out1_reg[15]_0 ),
        .I2(\hold5_out1_reg[15] [8]),
        .O(B[8]));
  (* SOFT_HLUTNM = "soft_lutpair145" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    Div_i1_mul_temp_i_9
       (.I0(OnlyAllowInNewPeriod_out1__0[7]),
        .I1(\Delay1_out1_reg[15]_0 ),
        .I2(\hold5_out1_reg[15] [7]),
        .O(B[7]));
  LUT2 #(
    .INIT(4'h9)) 
    InternalOmega_Out_tmp0_carry__1_i_1
       (.I0(Delay6_out1_reg[23]),
        .I1(Q[23]),
        .O(InternalOmega_Out_tmp0_carry__1_i_1_n_0));
  LUT2 #(
    .INIT(4'h9)) 
    InternalOmega_Out_tmp0_carry__1_i_2
       (.I0(Delay6_out1_reg[22]),
        .I1(Q[22]),
        .O(InternalOmega_Out_tmp0_carry__1_i_2_n_0));
  LUT2 #(
    .INIT(4'h9)) 
    InternalOmega_Out_tmp0_carry__1_i_3
       (.I0(Delay6_out1_reg[21]),
        .I1(Q[21]),
        .O(InternalOmega_Out_tmp0_carry__1_i_3_n_0));
  LUT2 #(
    .INIT(4'h9)) 
    InternalOmega_Out_tmp0_carry__1_i_4
       (.I0(Delay6_out1_reg[20]),
        .I1(Q[20]),
        .O(InternalOmega_Out_tmp0_carry__1_i_4_n_0));
  LUT2 #(
    .INIT(4'h9)) 
    InternalOmega_Out_tmp0_carry__1_i_5
       (.I0(Delay6_out1_reg[19]),
        .I1(Q[19]),
        .O(InternalOmega_Out_tmp0_carry__1_i_5_n_0));
  LUT2 #(
    .INIT(4'h9)) 
    InternalOmega_Out_tmp0_carry__1_i_6
       (.I0(Delay6_out1_reg[18]),
        .I1(Q[18]),
        .O(InternalOmega_Out_tmp0_carry__1_i_6_n_0));
  LUT2 #(
    .INIT(4'h9)) 
    InternalOmega_Out_tmp0_carry__1_i_7
       (.I0(Delay6_out1_reg[17]),
        .I1(Q[17]),
        .O(InternalOmega_Out_tmp0_carry__1_i_7_n_0));
  LUT2 #(
    .INIT(4'h9)) 
    InternalOmega_Out_tmp0_carry__1_i_8
       (.I0(Delay6_out1_reg[16]),
        .I1(Q[16]),
        .O(InternalOmega_Out_tmp0_carry__1_i_8_n_0));
  (* SOFT_HLUTNM = "soft_lutpair172" *) 
  LUT2 #(
    .INIT(4'hB)) 
    \OnlyAllowInNewPeriod_out1[0]_i_1 
       (.I0(Delay7_out_reg[0]),
        .I1(Delay7_ctrl_delay_out),
        .O(state[0]));
  (* SOFT_HLUTNM = "soft_lutpair154" *) 
  LUT2 #(
    .INIT(4'h8)) 
    \OnlyAllowInNewPeriod_out1[10]_i_1 
       (.I0(Delay7_ctrl_delay_out),
        .I1(Delay7_out_reg[10]),
        .O(state[10]));
  (* SOFT_HLUTNM = "soft_lutpair154" *) 
  LUT2 #(
    .INIT(4'h8)) 
    \OnlyAllowInNewPeriod_out1[11]_i_1 
       (.I0(Delay7_ctrl_delay_out),
        .I1(Delay7_out_reg[11]),
        .O(state[11]));
  (* SOFT_HLUTNM = "soft_lutpair153" *) 
  LUT2 #(
    .INIT(4'h8)) 
    \OnlyAllowInNewPeriod_out1[12]_i_1 
       (.I0(Delay7_ctrl_delay_out),
        .I1(Delay7_out_reg[12]),
        .O(state[12]));
  (* SOFT_HLUTNM = "soft_lutpair153" *) 
  LUT2 #(
    .INIT(4'h8)) 
    \OnlyAllowInNewPeriod_out1[13]_i_1 
       (.I0(Delay7_ctrl_delay_out),
        .I1(Delay7_out_reg[13]),
        .O(state[13]));
  (* SOFT_HLUTNM = "soft_lutpair159" *) 
  LUT2 #(
    .INIT(4'h8)) 
    \OnlyAllowInNewPeriod_out1[14]_i_1 
       (.I0(Delay7_ctrl_delay_out),
        .I1(Delay7_out_reg[14]),
        .O(state[14]));
  (* SOFT_HLUTNM = "soft_lutpair159" *) 
  LUT2 #(
    .INIT(4'h8)) 
    \OnlyAllowInNewPeriod_out1[15]_i_2 
       (.I0(Delay7_out_reg[15]),
        .I1(Delay7_ctrl_delay_out),
        .O(state[15]));
  (* SOFT_HLUTNM = "soft_lutpair172" *) 
  LUT2 #(
    .INIT(4'h8)) 
    \OnlyAllowInNewPeriod_out1[1]_i_1 
       (.I0(Delay7_out_reg[1]),
        .I1(Delay7_ctrl_delay_out),
        .O(state[1]));
  (* SOFT_HLUTNM = "soft_lutpair158" *) 
  LUT2 #(
    .INIT(4'h8)) 
    \OnlyAllowInNewPeriod_out1[2]_i_1 
       (.I0(Delay7_ctrl_delay_out),
        .I1(Delay7_out_reg[2]),
        .O(state[2]));
  (* SOFT_HLUTNM = "soft_lutpair158" *) 
  LUT2 #(
    .INIT(4'h8)) 
    \OnlyAllowInNewPeriod_out1[3]_i_1 
       (.I0(Delay7_ctrl_delay_out),
        .I1(Delay7_out_reg[3]),
        .O(state[3]));
  (* SOFT_HLUTNM = "soft_lutpair157" *) 
  LUT2 #(
    .INIT(4'h8)) 
    \OnlyAllowInNewPeriod_out1[4]_i_1 
       (.I0(Delay7_ctrl_delay_out),
        .I1(Delay7_out_reg[4]),
        .O(state[4]));
  (* SOFT_HLUTNM = "soft_lutpair157" *) 
  LUT2 #(
    .INIT(4'h8)) 
    \OnlyAllowInNewPeriod_out1[5]_i_1 
       (.I0(Delay7_ctrl_delay_out),
        .I1(Delay7_out_reg[5]),
        .O(state[5]));
  (* SOFT_HLUTNM = "soft_lutpair156" *) 
  LUT2 #(
    .INIT(4'h8)) 
    \OnlyAllowInNewPeriod_out1[6]_i_1 
       (.I0(Delay7_ctrl_delay_out),
        .I1(Delay7_out_reg[6]),
        .O(state[6]));
  (* SOFT_HLUTNM = "soft_lutpair156" *) 
  LUT2 #(
    .INIT(4'h8)) 
    \OnlyAllowInNewPeriod_out1[7]_i_1 
       (.I0(Delay7_ctrl_delay_out),
        .I1(Delay7_out_reg[7]),
        .O(state[7]));
  (* SOFT_HLUTNM = "soft_lutpair155" *) 
  LUT2 #(
    .INIT(4'h8)) 
    \OnlyAllowInNewPeriod_out1[8]_i_1 
       (.I0(Delay7_ctrl_delay_out),
        .I1(Delay7_out_reg[8]),
        .O(state[8]));
  (* SOFT_HLUTNM = "soft_lutpair155" *) 
  LUT2 #(
    .INIT(4'h8)) 
    \OnlyAllowInNewPeriod_out1[9]_i_1 
       (.I0(Delay7_ctrl_delay_out),
        .I1(Delay7_out_reg[9]),
        .O(state[9]));
  FDRE \OnlyAllowInNewPeriod_out1_reg[0] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(state[0]),
        .Q(OnlyAllowInNewPeriod_out1__0[0]),
        .R(RSTP));
  FDRE \OnlyAllowInNewPeriod_out1_reg[10] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(state[10]),
        .Q(OnlyAllowInNewPeriod_out1__0[10]),
        .R(RSTP));
  FDRE \OnlyAllowInNewPeriod_out1_reg[11] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(state[11]),
        .Q(OnlyAllowInNewPeriod_out1__0[11]),
        .R(RSTP));
  FDRE \OnlyAllowInNewPeriod_out1_reg[12] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(state[12]),
        .Q(OnlyAllowInNewPeriod_out1__0[12]),
        .R(RSTP));
  FDRE \OnlyAllowInNewPeriod_out1_reg[13] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(state[13]),
        .Q(OnlyAllowInNewPeriod_out1__0[13]),
        .R(RSTP));
  FDRE \OnlyAllowInNewPeriod_out1_reg[14] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(state[14]),
        .Q(OnlyAllowInNewPeriod_out1__0[14]),
        .R(RSTP));
  FDRE \OnlyAllowInNewPeriod_out1_reg[15] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(state[15]),
        .Q(OnlyAllowInNewPeriod_out1__0[15]),
        .R(RSTP));
  FDRE \OnlyAllowInNewPeriod_out1_reg[1] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(state[1]),
        .Q(OnlyAllowInNewPeriod_out1__0[1]),
        .R(RSTP));
  FDRE \OnlyAllowInNewPeriod_out1_reg[2] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(state[2]),
        .Q(OnlyAllowInNewPeriod_out1__0[2]),
        .R(RSTP));
  FDRE \OnlyAllowInNewPeriod_out1_reg[3] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(state[3]),
        .Q(OnlyAllowInNewPeriod_out1__0[3]),
        .R(RSTP));
  FDRE \OnlyAllowInNewPeriod_out1_reg[4] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(state[4]),
        .Q(OnlyAllowInNewPeriod_out1__0[4]),
        .R(RSTP));
  FDRE \OnlyAllowInNewPeriod_out1_reg[5] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(state[5]),
        .Q(OnlyAllowInNewPeriod_out1__0[5]),
        .R(RSTP));
  FDRE \OnlyAllowInNewPeriod_out1_reg[6] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(state[6]),
        .Q(OnlyAllowInNewPeriod_out1__0[6]),
        .R(RSTP));
  FDRE \OnlyAllowInNewPeriod_out1_reg[7] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(state[7]),
        .Q(OnlyAllowInNewPeriod_out1__0[7]),
        .R(RSTP));
  FDRE \OnlyAllowInNewPeriod_out1_reg[8] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(state[8]),
        .Q(OnlyAllowInNewPeriod_out1__0[8]),
        .R(RSTP));
  FDRE \OnlyAllowInNewPeriod_out1_reg[9] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(state[9]),
        .Q(OnlyAllowInNewPeriod_out1__0[9]),
        .R(RSTP));
  LUT2 #(
    .INIT(4'h6)) 
    \Pipeline1_out1[15]_i_2 
       (.I0(Pipeline_out1[37]),
        .I1(Pipeline_out1[15]),
        .O(\Pipeline1_out1[15]_i_2_n_0 ));
  LUT2 #(
    .INIT(4'h6)) 
    \Pipeline1_out1[15]_i_3 
       (.I0(Pipeline_out1[37]),
        .I1(Pipeline_out1[14]),
        .O(\Pipeline1_out1[15]_i_3_n_0 ));
  LUT2 #(
    .INIT(4'h6)) 
    \Pipeline1_out1[15]_i_4 
       (.I0(Pipeline_out1[37]),
        .I1(Pipeline_out1[13]),
        .O(\Pipeline1_out1[15]_i_4_n_0 ));
  LUT2 #(
    .INIT(4'h6)) 
    \Pipeline1_out1[15]_i_5 
       (.I0(Pipeline_out1[37]),
        .I1(Pipeline_out1[12]),
        .O(\Pipeline1_out1[15]_i_5_n_0 ));
  LUT2 #(
    .INIT(4'h6)) 
    \Pipeline1_out1[15]_i_6 
       (.I0(Pipeline_out1[37]),
        .I1(Pipeline_out1[11]),
        .O(\Pipeline1_out1[15]_i_6_n_0 ));
  LUT2 #(
    .INIT(4'h6)) 
    \Pipeline1_out1[15]_i_7 
       (.I0(Pipeline_out1[37]),
        .I1(Pipeline_out1[10]),
        .O(\Pipeline1_out1[15]_i_7_n_0 ));
  LUT2 #(
    .INIT(4'h6)) 
    \Pipeline1_out1[15]_i_8 
       (.I0(Pipeline_out1[37]),
        .I1(Pipeline_out1[9]),
        .O(\Pipeline1_out1[15]_i_8_n_0 ));
  LUT2 #(
    .INIT(4'h6)) 
    \Pipeline1_out1[15]_i_9 
       (.I0(Pipeline_out1[37]),
        .I1(Pipeline_out1[8]),
        .O(\Pipeline1_out1[15]_i_9_n_0 ));
  LUT2 #(
    .INIT(4'h6)) 
    \Pipeline1_out1[23]_i_2 
       (.I0(Pipeline_out1[37]),
        .I1(Pipeline_out1[23]),
        .O(\Pipeline1_out1[23]_i_2_n_0 ));
  LUT2 #(
    .INIT(4'h6)) 
    \Pipeline1_out1[23]_i_3 
       (.I0(Pipeline_out1[37]),
        .I1(Pipeline_out1[22]),
        .O(\Pipeline1_out1[23]_i_3_n_0 ));
  LUT2 #(
    .INIT(4'h6)) 
    \Pipeline1_out1[23]_i_4 
       (.I0(Pipeline_out1[37]),
        .I1(Pipeline_out1[21]),
        .O(\Pipeline1_out1[23]_i_4_n_0 ));
  LUT2 #(
    .INIT(4'h6)) 
    \Pipeline1_out1[23]_i_5 
       (.I0(Pipeline_out1[37]),
        .I1(Pipeline_out1[20]),
        .O(\Pipeline1_out1[23]_i_5_n_0 ));
  LUT2 #(
    .INIT(4'h6)) 
    \Pipeline1_out1[23]_i_6 
       (.I0(Pipeline_out1[37]),
        .I1(Pipeline_out1[19]),
        .O(\Pipeline1_out1[23]_i_6_n_0 ));
  LUT2 #(
    .INIT(4'h6)) 
    \Pipeline1_out1[23]_i_7 
       (.I0(Pipeline_out1[37]),
        .I1(Pipeline_out1[18]),
        .O(\Pipeline1_out1[23]_i_7_n_0 ));
  LUT2 #(
    .INIT(4'h6)) 
    \Pipeline1_out1[23]_i_8 
       (.I0(Pipeline_out1[37]),
        .I1(Pipeline_out1[17]),
        .O(\Pipeline1_out1[23]_i_8_n_0 ));
  LUT2 #(
    .INIT(4'h6)) 
    \Pipeline1_out1[23]_i_9 
       (.I0(Pipeline_out1[37]),
        .I1(Pipeline_out1[16]),
        .O(\Pipeline1_out1[23]_i_9_n_0 ));
  LUT2 #(
    .INIT(4'h6)) 
    \Pipeline1_out1[31]_i_2 
       (.I0(Pipeline_out1[37]),
        .I1(Pipeline_out1[31]),
        .O(\Pipeline1_out1[31]_i_2_n_0 ));
  LUT2 #(
    .INIT(4'h6)) 
    \Pipeline1_out1[31]_i_3 
       (.I0(Pipeline_out1[37]),
        .I1(Pipeline_out1[30]),
        .O(\Pipeline1_out1[31]_i_3_n_0 ));
  LUT2 #(
    .INIT(4'h6)) 
    \Pipeline1_out1[31]_i_4 
       (.I0(Pipeline_out1[37]),
        .I1(Pipeline_out1[29]),
        .O(\Pipeline1_out1[31]_i_4_n_0 ));
  LUT2 #(
    .INIT(4'h6)) 
    \Pipeline1_out1[31]_i_5 
       (.I0(Pipeline_out1[37]),
        .I1(Pipeline_out1[28]),
        .O(\Pipeline1_out1[31]_i_5_n_0 ));
  LUT2 #(
    .INIT(4'h6)) 
    \Pipeline1_out1[31]_i_6 
       (.I0(Pipeline_out1[37]),
        .I1(Pipeline_out1[27]),
        .O(\Pipeline1_out1[31]_i_6_n_0 ));
  LUT2 #(
    .INIT(4'h6)) 
    \Pipeline1_out1[31]_i_7 
       (.I0(Pipeline_out1[37]),
        .I1(Pipeline_out1[26]),
        .O(\Pipeline1_out1[31]_i_7_n_0 ));
  LUT2 #(
    .INIT(4'h6)) 
    \Pipeline1_out1[31]_i_8 
       (.I0(Pipeline_out1[37]),
        .I1(Pipeline_out1[25]),
        .O(\Pipeline1_out1[31]_i_8_n_0 ));
  LUT2 #(
    .INIT(4'h6)) 
    \Pipeline1_out1[31]_i_9 
       (.I0(Pipeline_out1[37]),
        .I1(Pipeline_out1[24]),
        .O(\Pipeline1_out1[31]_i_9_n_0 ));
  LUT2 #(
    .INIT(4'h6)) 
    \Pipeline1_out1[37]_i_2 
       (.I0(Pipeline_out1[37]),
        .I1(Pipeline_out1[36]),
        .O(\Pipeline1_out1[37]_i_2_n_0 ));
  LUT2 #(
    .INIT(4'h6)) 
    \Pipeline1_out1[37]_i_3 
       (.I0(Pipeline_out1[37]),
        .I1(Pipeline_out1[35]),
        .O(\Pipeline1_out1[37]_i_3_n_0 ));
  LUT2 #(
    .INIT(4'h6)) 
    \Pipeline1_out1[37]_i_4 
       (.I0(Pipeline_out1[37]),
        .I1(Pipeline_out1[34]),
        .O(\Pipeline1_out1[37]_i_4_n_0 ));
  LUT2 #(
    .INIT(4'h6)) 
    \Pipeline1_out1[37]_i_5 
       (.I0(Pipeline_out1[37]),
        .I1(Pipeline_out1[33]),
        .O(\Pipeline1_out1[37]_i_5_n_0 ));
  LUT2 #(
    .INIT(4'h6)) 
    \Pipeline1_out1[37]_i_6 
       (.I0(Pipeline_out1[37]),
        .I1(Pipeline_out1[32]),
        .O(\Pipeline1_out1[37]_i_6_n_0 ));
  LUT1 #(
    .INIT(2'h2)) 
    \Pipeline1_out1[7]_i_10 
       (.I0(Pipeline_out1[0]),
        .O(\Pipeline1_out1[7]_i_10_n_0 ));
  LUT1 #(
    .INIT(2'h2)) 
    \Pipeline1_out1[7]_i_2 
       (.I0(Pipeline_out1[37]),
        .O(\Pipeline1_out1[7]_i_2_n_0 ));
  LUT2 #(
    .INIT(4'h6)) 
    \Pipeline1_out1[7]_i_3 
       (.I0(Pipeline_out1[37]),
        .I1(Pipeline_out1[7]),
        .O(\Pipeline1_out1[7]_i_3_n_0 ));
  LUT2 #(
    .INIT(4'h6)) 
    \Pipeline1_out1[7]_i_4 
       (.I0(Pipeline_out1[37]),
        .I1(Pipeline_out1[6]),
        .O(\Pipeline1_out1[7]_i_4_n_0 ));
  LUT2 #(
    .INIT(4'h6)) 
    \Pipeline1_out1[7]_i_5 
       (.I0(Pipeline_out1[37]),
        .I1(Pipeline_out1[5]),
        .O(\Pipeline1_out1[7]_i_5_n_0 ));
  LUT2 #(
    .INIT(4'h6)) 
    \Pipeline1_out1[7]_i_6 
       (.I0(Pipeline_out1[37]),
        .I1(Pipeline_out1[4]),
        .O(\Pipeline1_out1[7]_i_6_n_0 ));
  LUT2 #(
    .INIT(4'h6)) 
    \Pipeline1_out1[7]_i_7 
       (.I0(Pipeline_out1[37]),
        .I1(Pipeline_out1[3]),
        .O(\Pipeline1_out1[7]_i_7_n_0 ));
  LUT2 #(
    .INIT(4'h6)) 
    \Pipeline1_out1[7]_i_8 
       (.I0(Pipeline_out1[37]),
        .I1(Pipeline_out1[2]),
        .O(\Pipeline1_out1[7]_i_8_n_0 ));
  LUT2 #(
    .INIT(4'h6)) 
    \Pipeline1_out1[7]_i_9 
       (.I0(Pipeline_out1[37]),
        .I1(Pipeline_out1[1]),
        .O(\Pipeline1_out1[7]_i_9_n_0 ));
  FDRE \Pipeline1_out1_reg[0] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\Pipeline1_out1_reg[7]_i_1_n_15 ),
        .Q(Pipeline1_out1[0]),
        .R(RSTP));
  FDRE \Pipeline1_out1_reg[10] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\Pipeline1_out1_reg[15]_i_1_n_13 ),
        .Q(Pipeline1_out1[10]),
        .R(RSTP));
  FDRE \Pipeline1_out1_reg[11] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\Pipeline1_out1_reg[15]_i_1_n_12 ),
        .Q(Pipeline1_out1[11]),
        .R(RSTP));
  FDRE \Pipeline1_out1_reg[12] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\Pipeline1_out1_reg[15]_i_1_n_11 ),
        .Q(Pipeline1_out1[12]),
        .R(RSTP));
  FDRE \Pipeline1_out1_reg[13] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\Pipeline1_out1_reg[15]_i_1_n_10 ),
        .Q(Pipeline1_out1[13]),
        .R(RSTP));
  FDRE \Pipeline1_out1_reg[14] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\Pipeline1_out1_reg[15]_i_1_n_9 ),
        .Q(Pipeline1_out1[14]),
        .R(RSTP));
  FDRE \Pipeline1_out1_reg[15] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\Pipeline1_out1_reg[15]_i_1_n_8 ),
        .Q(Pipeline1_out1[15]),
        .R(RSTP));
  (* ADDER_THRESHOLD = "35" *) 
  CARRY8 \Pipeline1_out1_reg[15]_i_1 
       (.CI(\Pipeline1_out1_reg[7]_i_1_n_0 ),
        .CI_TOP(1'b0),
        .CO({\Pipeline1_out1_reg[15]_i_1_n_0 ,\Pipeline1_out1_reg[15]_i_1_n_1 ,\Pipeline1_out1_reg[15]_i_1_n_2 ,\Pipeline1_out1_reg[15]_i_1_n_3 ,\Pipeline1_out1_reg[15]_i_1_n_4 ,\Pipeline1_out1_reg[15]_i_1_n_5 ,\Pipeline1_out1_reg[15]_i_1_n_6 ,\Pipeline1_out1_reg[15]_i_1_n_7 }),
        .DI({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .O({\Pipeline1_out1_reg[15]_i_1_n_8 ,\Pipeline1_out1_reg[15]_i_1_n_9 ,\Pipeline1_out1_reg[15]_i_1_n_10 ,\Pipeline1_out1_reg[15]_i_1_n_11 ,\Pipeline1_out1_reg[15]_i_1_n_12 ,\Pipeline1_out1_reg[15]_i_1_n_13 ,\Pipeline1_out1_reg[15]_i_1_n_14 ,\Pipeline1_out1_reg[15]_i_1_n_15 }),
        .S({\Pipeline1_out1[15]_i_2_n_0 ,\Pipeline1_out1[15]_i_3_n_0 ,\Pipeline1_out1[15]_i_4_n_0 ,\Pipeline1_out1[15]_i_5_n_0 ,\Pipeline1_out1[15]_i_6_n_0 ,\Pipeline1_out1[15]_i_7_n_0 ,\Pipeline1_out1[15]_i_8_n_0 ,\Pipeline1_out1[15]_i_9_n_0 }));
  FDRE \Pipeline1_out1_reg[16] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\Pipeline1_out1_reg[23]_i_1_n_15 ),
        .Q(Pipeline1_out1[16]),
        .R(RSTP));
  FDRE \Pipeline1_out1_reg[17] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\Pipeline1_out1_reg[23]_i_1_n_14 ),
        .Q(Pipeline1_out1[17]),
        .R(RSTP));
  FDRE \Pipeline1_out1_reg[18] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\Pipeline1_out1_reg[23]_i_1_n_13 ),
        .Q(Pipeline1_out1[18]),
        .R(RSTP));
  FDRE \Pipeline1_out1_reg[19] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\Pipeline1_out1_reg[23]_i_1_n_12 ),
        .Q(Pipeline1_out1[19]),
        .R(RSTP));
  FDRE \Pipeline1_out1_reg[1] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\Pipeline1_out1_reg[7]_i_1_n_14 ),
        .Q(Pipeline1_out1[1]),
        .R(RSTP));
  FDRE \Pipeline1_out1_reg[20] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\Pipeline1_out1_reg[23]_i_1_n_11 ),
        .Q(Pipeline1_out1[20]),
        .R(RSTP));
  FDRE \Pipeline1_out1_reg[21] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\Pipeline1_out1_reg[23]_i_1_n_10 ),
        .Q(Pipeline1_out1[21]),
        .R(RSTP));
  FDRE \Pipeline1_out1_reg[22] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\Pipeline1_out1_reg[23]_i_1_n_9 ),
        .Q(Pipeline1_out1[22]),
        .R(RSTP));
  FDRE \Pipeline1_out1_reg[23] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\Pipeline1_out1_reg[23]_i_1_n_8 ),
        .Q(Pipeline1_out1[23]),
        .R(RSTP));
  (* ADDER_THRESHOLD = "35" *) 
  CARRY8 \Pipeline1_out1_reg[23]_i_1 
       (.CI(\Pipeline1_out1_reg[15]_i_1_n_0 ),
        .CI_TOP(1'b0),
        .CO({\Pipeline1_out1_reg[23]_i_1_n_0 ,\Pipeline1_out1_reg[23]_i_1_n_1 ,\Pipeline1_out1_reg[23]_i_1_n_2 ,\Pipeline1_out1_reg[23]_i_1_n_3 ,\Pipeline1_out1_reg[23]_i_1_n_4 ,\Pipeline1_out1_reg[23]_i_1_n_5 ,\Pipeline1_out1_reg[23]_i_1_n_6 ,\Pipeline1_out1_reg[23]_i_1_n_7 }),
        .DI({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .O({\Pipeline1_out1_reg[23]_i_1_n_8 ,\Pipeline1_out1_reg[23]_i_1_n_9 ,\Pipeline1_out1_reg[23]_i_1_n_10 ,\Pipeline1_out1_reg[23]_i_1_n_11 ,\Pipeline1_out1_reg[23]_i_1_n_12 ,\Pipeline1_out1_reg[23]_i_1_n_13 ,\Pipeline1_out1_reg[23]_i_1_n_14 ,\Pipeline1_out1_reg[23]_i_1_n_15 }),
        .S({\Pipeline1_out1[23]_i_2_n_0 ,\Pipeline1_out1[23]_i_3_n_0 ,\Pipeline1_out1[23]_i_4_n_0 ,\Pipeline1_out1[23]_i_5_n_0 ,\Pipeline1_out1[23]_i_6_n_0 ,\Pipeline1_out1[23]_i_7_n_0 ,\Pipeline1_out1[23]_i_8_n_0 ,\Pipeline1_out1[23]_i_9_n_0 }));
  FDRE \Pipeline1_out1_reg[24] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\Pipeline1_out1_reg[31]_i_1_n_15 ),
        .Q(Pipeline1_out1[24]),
        .R(RSTP));
  FDRE \Pipeline1_out1_reg[25] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\Pipeline1_out1_reg[31]_i_1_n_14 ),
        .Q(Pipeline1_out1[25]),
        .R(RSTP));
  FDRE \Pipeline1_out1_reg[26] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\Pipeline1_out1_reg[31]_i_1_n_13 ),
        .Q(Pipeline1_out1[26]),
        .R(RSTP));
  FDRE \Pipeline1_out1_reg[27] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\Pipeline1_out1_reg[31]_i_1_n_12 ),
        .Q(Pipeline1_out1[27]),
        .R(RSTP));
  FDRE \Pipeline1_out1_reg[28] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\Pipeline1_out1_reg[31]_i_1_n_11 ),
        .Q(Pipeline1_out1[28]),
        .R(RSTP));
  FDRE \Pipeline1_out1_reg[29] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\Pipeline1_out1_reg[31]_i_1_n_10 ),
        .Q(Pipeline1_out1[29]),
        .R(RSTP));
  FDRE \Pipeline1_out1_reg[2] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\Pipeline1_out1_reg[7]_i_1_n_13 ),
        .Q(Pipeline1_out1[2]),
        .R(RSTP));
  FDRE \Pipeline1_out1_reg[30] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\Pipeline1_out1_reg[31]_i_1_n_9 ),
        .Q(Pipeline1_out1[30]),
        .R(RSTP));
  FDRE \Pipeline1_out1_reg[31] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\Pipeline1_out1_reg[31]_i_1_n_8 ),
        .Q(Pipeline1_out1[31]),
        .R(RSTP));
  (* ADDER_THRESHOLD = "35" *) 
  CARRY8 \Pipeline1_out1_reg[31]_i_1 
       (.CI(\Pipeline1_out1_reg[23]_i_1_n_0 ),
        .CI_TOP(1'b0),
        .CO({\Pipeline1_out1_reg[31]_i_1_n_0 ,\Pipeline1_out1_reg[31]_i_1_n_1 ,\Pipeline1_out1_reg[31]_i_1_n_2 ,\Pipeline1_out1_reg[31]_i_1_n_3 ,\Pipeline1_out1_reg[31]_i_1_n_4 ,\Pipeline1_out1_reg[31]_i_1_n_5 ,\Pipeline1_out1_reg[31]_i_1_n_6 ,\Pipeline1_out1_reg[31]_i_1_n_7 }),
        .DI({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .O({\Pipeline1_out1_reg[31]_i_1_n_8 ,\Pipeline1_out1_reg[31]_i_1_n_9 ,\Pipeline1_out1_reg[31]_i_1_n_10 ,\Pipeline1_out1_reg[31]_i_1_n_11 ,\Pipeline1_out1_reg[31]_i_1_n_12 ,\Pipeline1_out1_reg[31]_i_1_n_13 ,\Pipeline1_out1_reg[31]_i_1_n_14 ,\Pipeline1_out1_reg[31]_i_1_n_15 }),
        .S({\Pipeline1_out1[31]_i_2_n_0 ,\Pipeline1_out1[31]_i_3_n_0 ,\Pipeline1_out1[31]_i_4_n_0 ,\Pipeline1_out1[31]_i_5_n_0 ,\Pipeline1_out1[31]_i_6_n_0 ,\Pipeline1_out1[31]_i_7_n_0 ,\Pipeline1_out1[31]_i_8_n_0 ,\Pipeline1_out1[31]_i_9_n_0 }));
  FDRE \Pipeline1_out1_reg[32] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\Pipeline1_out1_reg[37]_i_1_n_15 ),
        .Q(Pipeline1_out1[32]),
        .R(RSTP));
  FDRE \Pipeline1_out1_reg[33] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\Pipeline1_out1_reg[37]_i_1_n_14 ),
        .Q(Pipeline1_out1[33]),
        .R(RSTP));
  FDRE \Pipeline1_out1_reg[34] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\Pipeline1_out1_reg[37]_i_1_n_13 ),
        .Q(Pipeline1_out1[34]),
        .R(RSTP));
  FDRE \Pipeline1_out1_reg[35] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\Pipeline1_out1_reg[37]_i_1_n_12 ),
        .Q(Pipeline1_out1[35]),
        .R(RSTP));
  FDRE \Pipeline1_out1_reg[36] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\Pipeline1_out1_reg[37]_i_1_n_11 ),
        .Q(Pipeline1_out1[36]),
        .R(RSTP));
  FDRE \Pipeline1_out1_reg[37] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\Pipeline1_out1_reg[37]_i_1_n_10 ),
        .Q(Pipeline1_out1[37]),
        .R(RSTP));
  (* ADDER_THRESHOLD = "35" *) 
  CARRY8 \Pipeline1_out1_reg[37]_i_1 
       (.CI(\Pipeline1_out1_reg[31]_i_1_n_0 ),
        .CI_TOP(1'b0),
        .CO({\NLW_Pipeline1_out1_reg[37]_i_1_CO_UNCONNECTED [7:5],\Pipeline1_out1_reg[37]_i_1_n_3 ,\Pipeline1_out1_reg[37]_i_1_n_4 ,\Pipeline1_out1_reg[37]_i_1_n_5 ,\Pipeline1_out1_reg[37]_i_1_n_6 ,\Pipeline1_out1_reg[37]_i_1_n_7 }),
        .DI({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .O({\NLW_Pipeline1_out1_reg[37]_i_1_O_UNCONNECTED [7:6],\Pipeline1_out1_reg[37]_i_1_n_10 ,\Pipeline1_out1_reg[37]_i_1_n_11 ,\Pipeline1_out1_reg[37]_i_1_n_12 ,\Pipeline1_out1_reg[37]_i_1_n_13 ,\Pipeline1_out1_reg[37]_i_1_n_14 ,\Pipeline1_out1_reg[37]_i_1_n_15 }),
        .S({1'b0,1'b0,1'b0,\Pipeline1_out1[37]_i_2_n_0 ,\Pipeline1_out1[37]_i_3_n_0 ,\Pipeline1_out1[37]_i_4_n_0 ,\Pipeline1_out1[37]_i_5_n_0 ,\Pipeline1_out1[37]_i_6_n_0 }));
  FDRE \Pipeline1_out1_reg[3] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\Pipeline1_out1_reg[7]_i_1_n_12 ),
        .Q(Pipeline1_out1[3]),
        .R(RSTP));
  FDRE \Pipeline1_out1_reg[4] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\Pipeline1_out1_reg[7]_i_1_n_11 ),
        .Q(Pipeline1_out1[4]),
        .R(RSTP));
  FDRE \Pipeline1_out1_reg[5] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\Pipeline1_out1_reg[7]_i_1_n_10 ),
        .Q(Pipeline1_out1[5]),
        .R(RSTP));
  FDRE \Pipeline1_out1_reg[6] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\Pipeline1_out1_reg[7]_i_1_n_9 ),
        .Q(Pipeline1_out1[6]),
        .R(RSTP));
  FDRE \Pipeline1_out1_reg[7] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\Pipeline1_out1_reg[7]_i_1_n_8 ),
        .Q(Pipeline1_out1[7]),
        .R(RSTP));
  (* ADDER_THRESHOLD = "35" *) 
  CARRY8 \Pipeline1_out1_reg[7]_i_1 
       (.CI(1'b0),
        .CI_TOP(1'b0),
        .CO({\Pipeline1_out1_reg[7]_i_1_n_0 ,\Pipeline1_out1_reg[7]_i_1_n_1 ,\Pipeline1_out1_reg[7]_i_1_n_2 ,\Pipeline1_out1_reg[7]_i_1_n_3 ,\Pipeline1_out1_reg[7]_i_1_n_4 ,\Pipeline1_out1_reg[7]_i_1_n_5 ,\Pipeline1_out1_reg[7]_i_1_n_6 ,\Pipeline1_out1_reg[7]_i_1_n_7 }),
        .DI({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,\Pipeline1_out1[7]_i_2_n_0 }),
        .O({\Pipeline1_out1_reg[7]_i_1_n_8 ,\Pipeline1_out1_reg[7]_i_1_n_9 ,\Pipeline1_out1_reg[7]_i_1_n_10 ,\Pipeline1_out1_reg[7]_i_1_n_11 ,\Pipeline1_out1_reg[7]_i_1_n_12 ,\Pipeline1_out1_reg[7]_i_1_n_13 ,\Pipeline1_out1_reg[7]_i_1_n_14 ,\Pipeline1_out1_reg[7]_i_1_n_15 }),
        .S({\Pipeline1_out1[7]_i_3_n_0 ,\Pipeline1_out1[7]_i_4_n_0 ,\Pipeline1_out1[7]_i_5_n_0 ,\Pipeline1_out1[7]_i_6_n_0 ,\Pipeline1_out1[7]_i_7_n_0 ,\Pipeline1_out1[7]_i_8_n_0 ,\Pipeline1_out1[7]_i_9_n_0 ,\Pipeline1_out1[7]_i_10_n_0 }));
  FDRE \Pipeline1_out1_reg[8] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\Pipeline1_out1_reg[15]_i_1_n_15 ),
        .Q(Pipeline1_out1[8]),
        .R(RSTP));
  FDRE \Pipeline1_out1_reg[9] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\Pipeline1_out1_reg[15]_i_1_n_14 ),
        .Q(Pipeline1_out1[9]),
        .R(RSTP));
  (* SOFT_HLUTNM = "soft_lutpair137" *) 
  LUT2 #(
    .INIT(4'h2)) 
    \Pipeline_out1[0]_i_1 
       (.I0(speed_old_switch_out10_carry_n_15),
        .I1(\Delay1_out1_reg[15]_0 ),
        .O(\Pipeline_out1[0]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair147" *) 
  LUT2 #(
    .INIT(4'h2)) 
    \Pipeline_out1[10]_i_1 
       (.I0(speed_old_switch_out10_carry__0_n_13),
        .I1(\Delay1_out1_reg[15]_0 ),
        .O(\Pipeline_out1[10]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair148" *) 
  LUT2 #(
    .INIT(4'h2)) 
    \Pipeline_out1[11]_i_1 
       (.I0(speed_old_switch_out10_carry__0_n_12),
        .I1(\Delay1_out1_reg[15]_0 ),
        .O(\Pipeline_out1[11]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair149" *) 
  LUT2 #(
    .INIT(4'h2)) 
    \Pipeline_out1[12]_i_1 
       (.I0(speed_old_switch_out10_carry__0_n_11),
        .I1(\Delay1_out1_reg[15]_0 ),
        .O(\Pipeline_out1[12]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair150" *) 
  LUT2 #(
    .INIT(4'h2)) 
    \Pipeline_out1[13]_i_1 
       (.I0(speed_old_switch_out10_carry__0_n_10),
        .I1(\Delay1_out1_reg[15]_0 ),
        .O(\Pipeline_out1[13]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair171" *) 
  LUT2 #(
    .INIT(4'h2)) 
    \Pipeline_out1[14]_i_1 
       (.I0(speed_old_switch_out10_carry__0_n_9),
        .I1(\Delay1_out1_reg[15]_0 ),
        .O(T_count_switch_out1[14]));
  (* SOFT_HLUTNM = "soft_lutpair171" *) 
  LUT2 #(
    .INIT(4'h2)) 
    \Pipeline_out1[15]_i_1 
       (.I0(speed_old_switch_out10_carry__0_n_8),
        .I1(\Delay1_out1_reg[15]_0 ),
        .O(T_count_switch_out1[15]));
  (* SOFT_HLUTNM = "soft_lutpair170" *) 
  LUT2 #(
    .INIT(4'h2)) 
    \Pipeline_out1[16]_i_1 
       (.I0(speed_old_switch_out10_carry__1_n_15),
        .I1(\Delay1_out1_reg[15]_0 ),
        .O(T_count_switch_out1[16]));
  (* SOFT_HLUTNM = "soft_lutpair170" *) 
  LUT2 #(
    .INIT(4'h2)) 
    \Pipeline_out1[17]_i_1 
       (.I0(speed_old_switch_out10_carry__1_n_14),
        .I1(\Delay1_out1_reg[15]_0 ),
        .O(T_count_switch_out1[17]));
  (* SOFT_HLUTNM = "soft_lutpair169" *) 
  LUT2 #(
    .INIT(4'h2)) 
    \Pipeline_out1[18]_i_1 
       (.I0(speed_old_switch_out10_carry__1_n_13),
        .I1(\Delay1_out1_reg[15]_0 ),
        .O(T_count_switch_out1[18]));
  (* SOFT_HLUTNM = "soft_lutpair169" *) 
  LUT2 #(
    .INIT(4'h2)) 
    \Pipeline_out1[19]_i_1 
       (.I0(speed_old_switch_out10_carry__1_n_12),
        .I1(\Delay1_out1_reg[15]_0 ),
        .O(T_count_switch_out1[19]));
  (* SOFT_HLUTNM = "soft_lutpair138" *) 
  LUT2 #(
    .INIT(4'h2)) 
    \Pipeline_out1[1]_i_1 
       (.I0(speed_old_switch_out10_carry_n_14),
        .I1(\Delay1_out1_reg[15]_0 ),
        .O(\Pipeline_out1[1]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair168" *) 
  LUT2 #(
    .INIT(4'h2)) 
    \Pipeline_out1[20]_i_1 
       (.I0(speed_old_switch_out10_carry__1_n_11),
        .I1(\Delay1_out1_reg[15]_0 ),
        .O(T_count_switch_out1[20]));
  (* SOFT_HLUTNM = "soft_lutpair168" *) 
  LUT2 #(
    .INIT(4'h2)) 
    \Pipeline_out1[21]_i_1 
       (.I0(speed_old_switch_out10_carry__1_n_10),
        .I1(\Delay1_out1_reg[15]_0 ),
        .O(T_count_switch_out1[21]));
  (* SOFT_HLUTNM = "soft_lutpair167" *) 
  LUT2 #(
    .INIT(4'h2)) 
    \Pipeline_out1[22]_i_1 
       (.I0(speed_old_switch_out10_carry__1_n_9),
        .I1(\Delay1_out1_reg[15]_0 ),
        .O(T_count_switch_out1[22]));
  (* SOFT_HLUTNM = "soft_lutpair167" *) 
  LUT2 #(
    .INIT(4'h2)) 
    \Pipeline_out1[23]_i_1 
       (.I0(speed_old_switch_out10_carry__1_n_8),
        .I1(\Delay1_out1_reg[15]_0 ),
        .O(T_count_switch_out1[23]));
  (* SOFT_HLUTNM = "soft_lutpair166" *) 
  LUT2 #(
    .INIT(4'h2)) 
    \Pipeline_out1[24]_i_1 
       (.I0(speed_old_switch_out10_carry__2_n_15),
        .I1(\Delay1_out1_reg[15]_0 ),
        .O(T_count_switch_out1[24]));
  (* SOFT_HLUTNM = "soft_lutpair166" *) 
  LUT2 #(
    .INIT(4'h2)) 
    \Pipeline_out1[25]_i_1 
       (.I0(speed_old_switch_out10_carry__2_n_14),
        .I1(\Delay1_out1_reg[15]_0 ),
        .O(T_count_switch_out1[25]));
  (* SOFT_HLUTNM = "soft_lutpair165" *) 
  LUT2 #(
    .INIT(4'h2)) 
    \Pipeline_out1[26]_i_1 
       (.I0(speed_old_switch_out10_carry__2_n_13),
        .I1(\Delay1_out1_reg[15]_0 ),
        .O(T_count_switch_out1[26]));
  (* SOFT_HLUTNM = "soft_lutpair165" *) 
  LUT2 #(
    .INIT(4'h2)) 
    \Pipeline_out1[27]_i_1 
       (.I0(speed_old_switch_out10_carry__2_n_12),
        .I1(\Delay1_out1_reg[15]_0 ),
        .O(T_count_switch_out1[27]));
  (* SOFT_HLUTNM = "soft_lutpair164" *) 
  LUT2 #(
    .INIT(4'h2)) 
    \Pipeline_out1[28]_i_1 
       (.I0(speed_old_switch_out10_carry__2_n_11),
        .I1(\Delay1_out1_reg[15]_0 ),
        .O(T_count_switch_out1[28]));
  (* SOFT_HLUTNM = "soft_lutpair164" *) 
  LUT2 #(
    .INIT(4'h2)) 
    \Pipeline_out1[29]_i_1 
       (.I0(speed_old_switch_out10_carry__2_n_10),
        .I1(\Delay1_out1_reg[15]_0 ),
        .O(T_count_switch_out1[29]));
  (* SOFT_HLUTNM = "soft_lutpair139" *) 
  LUT2 #(
    .INIT(4'h2)) 
    \Pipeline_out1[2]_i_1 
       (.I0(speed_old_switch_out10_carry_n_13),
        .I1(\Delay1_out1_reg[15]_0 ),
        .O(\Pipeline_out1[2]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair163" *) 
  LUT2 #(
    .INIT(4'h2)) 
    \Pipeline_out1[30]_i_1 
       (.I0(speed_old_switch_out10_carry__2_n_9),
        .I1(\Delay1_out1_reg[15]_0 ),
        .O(T_count_switch_out1[30]));
  (* SOFT_HLUTNM = "soft_lutpair163" *) 
  LUT2 #(
    .INIT(4'h2)) 
    \Pipeline_out1[31]_i_1 
       (.I0(speed_old_switch_out10_carry__2_n_8),
        .I1(\Delay1_out1_reg[15]_0 ),
        .O(T_count_switch_out1[31]));
  (* SOFT_HLUTNM = "soft_lutpair162" *) 
  LUT2 #(
    .INIT(4'h2)) 
    \Pipeline_out1[32]_i_1 
       (.I0(speed_old_switch_out10_carry__3_n_15),
        .I1(\Delay1_out1_reg[15]_0 ),
        .O(T_count_switch_out1[32]));
  (* SOFT_HLUTNM = "soft_lutpair162" *) 
  LUT2 #(
    .INIT(4'h2)) 
    \Pipeline_out1[33]_i_1 
       (.I0(speed_old_switch_out10_carry__3_n_14),
        .I1(\Delay1_out1_reg[15]_0 ),
        .O(T_count_switch_out1[33]));
  (* SOFT_HLUTNM = "soft_lutpair161" *) 
  LUT2 #(
    .INIT(4'h2)) 
    \Pipeline_out1[34]_i_1 
       (.I0(speed_old_switch_out10_carry__3_n_13),
        .I1(\Delay1_out1_reg[15]_0 ),
        .O(T_count_switch_out1[34]));
  (* SOFT_HLUTNM = "soft_lutpair161" *) 
  LUT2 #(
    .INIT(4'h2)) 
    \Pipeline_out1[35]_i_1 
       (.I0(speed_old_switch_out10_carry__3_n_12),
        .I1(\Delay1_out1_reg[15]_0 ),
        .O(T_count_switch_out1[35]));
  (* SOFT_HLUTNM = "soft_lutpair152" *) 
  LUT2 #(
    .INIT(4'h2)) 
    \Pipeline_out1[36]_i_1 
       (.I0(speed_old_switch_out10_carry__3_n_11),
        .I1(\Delay1_out1_reg[15]_0 ),
        .O(T_count_switch_out1[36]));
  (* SOFT_HLUTNM = "soft_lutpair151" *) 
  LUT2 #(
    .INIT(4'h2)) 
    \Pipeline_out1[37]_i_1 
       (.I0(speed_old_switch_out10_carry__3_n_10),
        .I1(\Delay1_out1_reg[15]_0 ),
        .O(T_count_switch_out1[37]));
  (* SOFT_HLUTNM = "soft_lutpair140" *) 
  LUT2 #(
    .INIT(4'h2)) 
    \Pipeline_out1[3]_i_1 
       (.I0(speed_old_switch_out10_carry_n_12),
        .I1(\Delay1_out1_reg[15]_0 ),
        .O(\Pipeline_out1[3]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair141" *) 
  LUT2 #(
    .INIT(4'h2)) 
    \Pipeline_out1[4]_i_1 
       (.I0(speed_old_switch_out10_carry_n_11),
        .I1(\Delay1_out1_reg[15]_0 ),
        .O(\Pipeline_out1[4]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair142" *) 
  LUT2 #(
    .INIT(4'h2)) 
    \Pipeline_out1[5]_i_1 
       (.I0(speed_old_switch_out10_carry_n_10),
        .I1(\Delay1_out1_reg[15]_0 ),
        .O(\Pipeline_out1[5]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair143" *) 
  LUT2 #(
    .INIT(4'h2)) 
    \Pipeline_out1[6]_i_1 
       (.I0(speed_old_switch_out10_carry_n_9),
        .I1(\Delay1_out1_reg[15]_0 ),
        .O(\Pipeline_out1[6]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair144" *) 
  LUT2 #(
    .INIT(4'h2)) 
    \Pipeline_out1[7]_i_1 
       (.I0(speed_old_switch_out10_carry_n_8),
        .I1(\Delay1_out1_reg[15]_0 ),
        .O(\Pipeline_out1[7]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair145" *) 
  LUT2 #(
    .INIT(4'h2)) 
    \Pipeline_out1[8]_i_1 
       (.I0(speed_old_switch_out10_carry__0_n_15),
        .I1(\Delay1_out1_reg[15]_0 ),
        .O(\Pipeline_out1[8]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair146" *) 
  LUT2 #(
    .INIT(4'h2)) 
    \Pipeline_out1[9]_i_1 
       (.I0(speed_old_switch_out10_carry__0_n_14),
        .I1(\Delay1_out1_reg[15]_0 ),
        .O(\Pipeline_out1[9]_i_1_n_0 ));
  FDRE \Pipeline_out1_reg[0] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\Pipeline_out1[0]_i_1_n_0 ),
        .Q(Pipeline_out1[0]),
        .R(RSTP));
  FDRE \Pipeline_out1_reg[10] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\Pipeline_out1[10]_i_1_n_0 ),
        .Q(Pipeline_out1[10]),
        .R(RSTP));
  FDRE \Pipeline_out1_reg[11] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\Pipeline_out1[11]_i_1_n_0 ),
        .Q(Pipeline_out1[11]),
        .R(RSTP));
  FDRE \Pipeline_out1_reg[12] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\Pipeline_out1[12]_i_1_n_0 ),
        .Q(Pipeline_out1[12]),
        .R(RSTP));
  FDRE \Pipeline_out1_reg[13] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\Pipeline_out1[13]_i_1_n_0 ),
        .Q(Pipeline_out1[13]),
        .R(RSTP));
  FDRE \Pipeline_out1_reg[14] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(T_count_switch_out1[14]),
        .Q(Pipeline_out1[14]),
        .R(RSTP));
  FDRE \Pipeline_out1_reg[15] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(T_count_switch_out1[15]),
        .Q(Pipeline_out1[15]),
        .R(RSTP));
  FDRE \Pipeline_out1_reg[16] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(T_count_switch_out1[16]),
        .Q(Pipeline_out1[16]),
        .R(RSTP));
  FDRE \Pipeline_out1_reg[17] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(T_count_switch_out1[17]),
        .Q(Pipeline_out1[17]),
        .R(RSTP));
  FDRE \Pipeline_out1_reg[18] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(T_count_switch_out1[18]),
        .Q(Pipeline_out1[18]),
        .R(RSTP));
  FDRE \Pipeline_out1_reg[19] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(T_count_switch_out1[19]),
        .Q(Pipeline_out1[19]),
        .R(RSTP));
  FDRE \Pipeline_out1_reg[1] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\Pipeline_out1[1]_i_1_n_0 ),
        .Q(Pipeline_out1[1]),
        .R(RSTP));
  FDRE \Pipeline_out1_reg[20] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(T_count_switch_out1[20]),
        .Q(Pipeline_out1[20]),
        .R(RSTP));
  FDRE \Pipeline_out1_reg[21] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(T_count_switch_out1[21]),
        .Q(Pipeline_out1[21]),
        .R(RSTP));
  FDRE \Pipeline_out1_reg[22] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(T_count_switch_out1[22]),
        .Q(Pipeline_out1[22]),
        .R(RSTP));
  FDRE \Pipeline_out1_reg[23] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(T_count_switch_out1[23]),
        .Q(Pipeline_out1[23]),
        .R(RSTP));
  FDRE \Pipeline_out1_reg[24] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(T_count_switch_out1[24]),
        .Q(Pipeline_out1[24]),
        .R(RSTP));
  FDRE \Pipeline_out1_reg[25] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(T_count_switch_out1[25]),
        .Q(Pipeline_out1[25]),
        .R(RSTP));
  FDRE \Pipeline_out1_reg[26] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(T_count_switch_out1[26]),
        .Q(Pipeline_out1[26]),
        .R(RSTP));
  FDRE \Pipeline_out1_reg[27] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(T_count_switch_out1[27]),
        .Q(Pipeline_out1[27]),
        .R(RSTP));
  FDRE \Pipeline_out1_reg[28] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(T_count_switch_out1[28]),
        .Q(Pipeline_out1[28]),
        .R(RSTP));
  FDRE \Pipeline_out1_reg[29] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(T_count_switch_out1[29]),
        .Q(Pipeline_out1[29]),
        .R(RSTP));
  FDRE \Pipeline_out1_reg[2] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\Pipeline_out1[2]_i_1_n_0 ),
        .Q(Pipeline_out1[2]),
        .R(RSTP));
  FDRE \Pipeline_out1_reg[30] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(T_count_switch_out1[30]),
        .Q(Pipeline_out1[30]),
        .R(RSTP));
  FDRE \Pipeline_out1_reg[31] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(T_count_switch_out1[31]),
        .Q(Pipeline_out1[31]),
        .R(RSTP));
  FDRE \Pipeline_out1_reg[32] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(T_count_switch_out1[32]),
        .Q(Pipeline_out1[32]),
        .R(RSTP));
  FDRE \Pipeline_out1_reg[33] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(T_count_switch_out1[33]),
        .Q(Pipeline_out1[33]),
        .R(RSTP));
  FDRE \Pipeline_out1_reg[34] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(T_count_switch_out1[34]),
        .Q(Pipeline_out1[34]),
        .R(RSTP));
  FDRE \Pipeline_out1_reg[35] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(T_count_switch_out1[35]),
        .Q(Pipeline_out1[35]),
        .R(RSTP));
  FDRE \Pipeline_out1_reg[36] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(T_count_switch_out1[36]),
        .Q(Pipeline_out1[36]),
        .R(RSTP));
  FDRE \Pipeline_out1_reg[37] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(T_count_switch_out1[37]),
        .Q(Pipeline_out1[37]),
        .R(RSTP));
  FDRE \Pipeline_out1_reg[3] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\Pipeline_out1[3]_i_1_n_0 ),
        .Q(Pipeline_out1[3]),
        .R(RSTP));
  FDRE \Pipeline_out1_reg[4] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\Pipeline_out1[4]_i_1_n_0 ),
        .Q(Pipeline_out1[4]),
        .R(RSTP));
  FDRE \Pipeline_out1_reg[5] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\Pipeline_out1[5]_i_1_n_0 ),
        .Q(Pipeline_out1[5]),
        .R(RSTP));
  FDRE \Pipeline_out1_reg[6] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\Pipeline_out1[6]_i_1_n_0 ),
        .Q(Pipeline_out1[6]),
        .R(RSTP));
  FDRE \Pipeline_out1_reg[7] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\Pipeline_out1[7]_i_1_n_0 ),
        .Q(Pipeline_out1[7]),
        .R(RSTP));
  FDRE \Pipeline_out1_reg[8] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\Pipeline_out1[8]_i_1_n_0 ),
        .Q(Pipeline_out1[8]),
        .R(RSTP));
  FDRE \Pipeline_out1_reg[9] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\Pipeline_out1[9]_i_1_n_0 ),
        .Q(Pipeline_out1[9]),
        .R(RSTP));
  (* COMPARATOR_THRESHOLD = "11" *) 
  CARRY8 ProtectOverflow_T_count_out11_carry
       (.CI(1'b1),
        .CI_TOP(1'b0),
        .CO({ProtectOverflow_T_count_out11_carry_n_0,ProtectOverflow_T_count_out11_carry_n_1,ProtectOverflow_T_count_out11_carry_n_2,ProtectOverflow_T_count_out11_carry_n_3,ProtectOverflow_T_count_out11_carry_n_4,ProtectOverflow_T_count_out11_carry_n_5,ProtectOverflow_T_count_out11_carry_n_6,ProtectOverflow_T_count_out11_carry_n_7}),
        .DI({ProtectOverflow_T_count_out11_carry_i_1_n_0,ProtectOverflow_T_count_out11_carry_i_2_n_0,ProtectOverflow_T_count_out11_carry_i_3_n_0,ProtectOverflow_T_count_out11_carry_i_4_n_0,ProtectOverflow_T_count_out11_carry_i_5_n_0,ProtectOverflow_T_count_out11_carry_i_6_n_0,ProtectOverflow_T_count_out11_carry_i_7_n_0,ProtectOverflow_T_count_out11_carry_i_8_n_0}),
        .O(NLW_ProtectOverflow_T_count_out11_carry_O_UNCONNECTED[7:0]),
        .S({ProtectOverflow_T_count_out11_carry_i_9_n_0,ProtectOverflow_T_count_out11_carry_i_10_n_0,ProtectOverflow_T_count_out11_carry_i_11_n_0,ProtectOverflow_T_count_out11_carry_i_12_n_0,ProtectOverflow_T_count_out11_carry_i_13_n_0,ProtectOverflow_T_count_out11_carry_i_14_n_0,ProtectOverflow_T_count_out11_carry_i_15_n_0,ProtectOverflow_T_count_out11_carry_i_16_n_0}));
  (* COMPARATOR_THRESHOLD = "11" *) 
  CARRY8 ProtectOverflow_T_count_out11_carry__0
       (.CI(ProtectOverflow_T_count_out11_carry_n_0),
        .CI_TOP(1'b0),
        .CO({ProtectOverflow_T_count_out11_carry__0_n_0,ProtectOverflow_T_count_out11_carry__0_n_1,ProtectOverflow_T_count_out11_carry__0_n_2,ProtectOverflow_T_count_out11_carry__0_n_3,ProtectOverflow_T_count_out11_carry__0_n_4,ProtectOverflow_T_count_out11_carry__0_n_5,ProtectOverflow_T_count_out11_carry__0_n_6,ProtectOverflow_T_count_out11_carry__0_n_7}),
        .DI({ProtectOverflow_T_count_out11_carry__0_i_1_n_0,ProtectOverflow_T_count_out11_carry__0_i_2_n_0,ProtectOverflow_T_count_out11_carry__0_i_3_n_0,ProtectOverflow_T_count_out11_carry__0_i_4_n_0,ProtectOverflow_T_count_out11_carry__0_i_5_n_0,ProtectOverflow_T_count_out11_carry__0_i_6_n_0,ProtectOverflow_T_count_out11_carry__0_i_7_n_0,ProtectOverflow_T_count_out11_carry__0_i_8_n_0}),
        .O(NLW_ProtectOverflow_T_count_out11_carry__0_O_UNCONNECTED[7:0]),
        .S({ProtectOverflow_T_count_out11_carry__0_i_9_n_0,ProtectOverflow_T_count_out11_carry__0_i_10_n_0,ProtectOverflow_T_count_out11_carry__0_i_11_n_0,ProtectOverflow_T_count_out11_carry__0_i_12_n_0,ProtectOverflow_T_count_out11_carry__0_i_13_n_0,ProtectOverflow_T_count_out11_carry__0_i_14_n_0,ProtectOverflow_T_count_out11_carry__0_i_15_n_0,ProtectOverflow_T_count_out11_carry__0_i_16_n_0}));
  LUT2 #(
    .INIT(4'hE)) 
    ProtectOverflow_T_count_out11_carry__0_i_1
       (.I0(Pipeline1_out1[30]),
        .I1(Pipeline1_out1[31]),
        .O(ProtectOverflow_T_count_out11_carry__0_i_1_n_0));
  LUT2 #(
    .INIT(4'h1)) 
    ProtectOverflow_T_count_out11_carry__0_i_10
       (.I0(Pipeline1_out1[29]),
        .I1(Pipeline1_out1[28]),
        .O(ProtectOverflow_T_count_out11_carry__0_i_10_n_0));
  LUT2 #(
    .INIT(4'h1)) 
    ProtectOverflow_T_count_out11_carry__0_i_11
       (.I0(Pipeline1_out1[27]),
        .I1(Pipeline1_out1[26]),
        .O(ProtectOverflow_T_count_out11_carry__0_i_11_n_0));
  LUT2 #(
    .INIT(4'h1)) 
    ProtectOverflow_T_count_out11_carry__0_i_12
       (.I0(Pipeline1_out1[25]),
        .I1(Pipeline1_out1[24]),
        .O(ProtectOverflow_T_count_out11_carry__0_i_12_n_0));
  LUT2 #(
    .INIT(4'h1)) 
    ProtectOverflow_T_count_out11_carry__0_i_13
       (.I0(Pipeline1_out1[23]),
        .I1(Pipeline1_out1[22]),
        .O(ProtectOverflow_T_count_out11_carry__0_i_13_n_0));
  LUT2 #(
    .INIT(4'h1)) 
    ProtectOverflow_T_count_out11_carry__0_i_14
       (.I0(Pipeline1_out1[21]),
        .I1(Pipeline1_out1[20]),
        .O(ProtectOverflow_T_count_out11_carry__0_i_14_n_0));
  LUT2 #(
    .INIT(4'h1)) 
    ProtectOverflow_T_count_out11_carry__0_i_15
       (.I0(Pipeline1_out1[18]),
        .I1(Pipeline1_out1[19]),
        .O(ProtectOverflow_T_count_out11_carry__0_i_15_n_0));
  LUT2 #(
    .INIT(4'h1)) 
    ProtectOverflow_T_count_out11_carry__0_i_16
       (.I0(Pipeline1_out1[16]),
        .I1(Pipeline1_out1[17]),
        .O(ProtectOverflow_T_count_out11_carry__0_i_16_n_0));
  LUT2 #(
    .INIT(4'hE)) 
    ProtectOverflow_T_count_out11_carry__0_i_2
       (.I0(Pipeline1_out1[28]),
        .I1(Pipeline1_out1[29]),
        .O(ProtectOverflow_T_count_out11_carry__0_i_2_n_0));
  LUT2 #(
    .INIT(4'hE)) 
    ProtectOverflow_T_count_out11_carry__0_i_3
       (.I0(Pipeline1_out1[26]),
        .I1(Pipeline1_out1[27]),
        .O(ProtectOverflow_T_count_out11_carry__0_i_3_n_0));
  LUT2 #(
    .INIT(4'hE)) 
    ProtectOverflow_T_count_out11_carry__0_i_4
       (.I0(Pipeline1_out1[24]),
        .I1(Pipeline1_out1[25]),
        .O(ProtectOverflow_T_count_out11_carry__0_i_4_n_0));
  LUT2 #(
    .INIT(4'hE)) 
    ProtectOverflow_T_count_out11_carry__0_i_5
       (.I0(Pipeline1_out1[22]),
        .I1(Pipeline1_out1[23]),
        .O(ProtectOverflow_T_count_out11_carry__0_i_5_n_0));
  LUT2 #(
    .INIT(4'hE)) 
    ProtectOverflow_T_count_out11_carry__0_i_6
       (.I0(Pipeline1_out1[20]),
        .I1(Pipeline1_out1[21]),
        .O(ProtectOverflow_T_count_out11_carry__0_i_6_n_0));
  LUT2 #(
    .INIT(4'hE)) 
    ProtectOverflow_T_count_out11_carry__0_i_7
       (.I0(Pipeline1_out1[19]),
        .I1(Pipeline1_out1[18]),
        .O(ProtectOverflow_T_count_out11_carry__0_i_7_n_0));
  LUT2 #(
    .INIT(4'hE)) 
    ProtectOverflow_T_count_out11_carry__0_i_8
       (.I0(Pipeline1_out1[17]),
        .I1(Pipeline1_out1[16]),
        .O(ProtectOverflow_T_count_out11_carry__0_i_8_n_0));
  LUT2 #(
    .INIT(4'h1)) 
    ProtectOverflow_T_count_out11_carry__0_i_9
       (.I0(Pipeline1_out1[31]),
        .I1(Pipeline1_out1[30]),
        .O(ProtectOverflow_T_count_out11_carry__0_i_9_n_0));
  (* COMPARATOR_THRESHOLD = "11" *) 
  CARRY8 ProtectOverflow_T_count_out11_carry__1
       (.CI(ProtectOverflow_T_count_out11_carry__0_n_0),
        .CI_TOP(1'b0),
        .CO({NLW_ProtectOverflow_T_count_out11_carry__1_CO_UNCONNECTED[7:3],switch_compare_1_2,ProtectOverflow_T_count_out11_carry__1_n_6,ProtectOverflow_T_count_out11_carry__1_n_7}),
        .DI({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,ProtectOverflow_T_count_out11_carry__1_i_1_n_0}),
        .O(NLW_ProtectOverflow_T_count_out11_carry__1_O_UNCONNECTED[7:0]),
        .S({1'b0,1'b0,1'b0,1'b0,1'b0,ProtectOverflow_T_count_out11_carry__1_i_2_n_0,ProtectOverflow_T_count_out11_carry__1_i_3_n_0,ProtectOverflow_T_count_out11_carry__1_i_4_n_0}));
  LUT2 #(
    .INIT(4'h8)) 
    ProtectOverflow_T_count_out11_carry__1_i_1
       (.I0(Pipeline1_out1[32]),
        .I1(Pipeline1_out1[33]),
        .O(ProtectOverflow_T_count_out11_carry__1_i_1_n_0));
  LUT2 #(
    .INIT(4'h2)) 
    ProtectOverflow_T_count_out11_carry__1_i_2
       (.I0(Pipeline1_out1[36]),
        .I1(Pipeline1_out1[37]),
        .O(ProtectOverflow_T_count_out11_carry__1_i_2_n_0));
  LUT2 #(
    .INIT(4'h8)) 
    ProtectOverflow_T_count_out11_carry__1_i_3
       (.I0(Pipeline1_out1[34]),
        .I1(Pipeline1_out1[35]),
        .O(ProtectOverflow_T_count_out11_carry__1_i_3_n_0));
  LUT2 #(
    .INIT(4'h2)) 
    ProtectOverflow_T_count_out11_carry__1_i_4
       (.I0(Pipeline1_out1[33]),
        .I1(Pipeline1_out1[32]),
        .O(ProtectOverflow_T_count_out11_carry__1_i_4_n_0));
  LUT2 #(
    .INIT(4'hE)) 
    ProtectOverflow_T_count_out11_carry_i_1
       (.I0(Pipeline1_out1[15]),
        .I1(Pipeline1_out1[14]),
        .O(ProtectOverflow_T_count_out11_carry_i_1_n_0));
  LUT2 #(
    .INIT(4'h1)) 
    ProtectOverflow_T_count_out11_carry_i_10
       (.I0(Pipeline1_out1[12]),
        .I1(Pipeline1_out1[13]),
        .O(ProtectOverflow_T_count_out11_carry_i_10_n_0));
  LUT2 #(
    .INIT(4'h1)) 
    ProtectOverflow_T_count_out11_carry_i_11
       (.I0(Pipeline1_out1[10]),
        .I1(Pipeline1_out1[11]),
        .O(ProtectOverflow_T_count_out11_carry_i_11_n_0));
  LUT2 #(
    .INIT(4'h1)) 
    ProtectOverflow_T_count_out11_carry_i_12
       (.I0(Pipeline1_out1[8]),
        .I1(Pipeline1_out1[9]),
        .O(ProtectOverflow_T_count_out11_carry_i_12_n_0));
  LUT2 #(
    .INIT(4'h1)) 
    ProtectOverflow_T_count_out11_carry_i_13
       (.I0(Pipeline1_out1[6]),
        .I1(Pipeline1_out1[7]),
        .O(ProtectOverflow_T_count_out11_carry_i_13_n_0));
  LUT2 #(
    .INIT(4'h1)) 
    ProtectOverflow_T_count_out11_carry_i_14
       (.I0(Pipeline1_out1[4]),
        .I1(Pipeline1_out1[5]),
        .O(ProtectOverflow_T_count_out11_carry_i_14_n_0));
  LUT2 #(
    .INIT(4'h1)) 
    ProtectOverflow_T_count_out11_carry_i_15
       (.I0(Pipeline1_out1[2]),
        .I1(Pipeline1_out1[3]),
        .O(ProtectOverflow_T_count_out11_carry_i_15_n_0));
  LUT2 #(
    .INIT(4'h1)) 
    ProtectOverflow_T_count_out11_carry_i_16
       (.I0(Pipeline1_out1[0]),
        .I1(Pipeline1_out1[1]),
        .O(ProtectOverflow_T_count_out11_carry_i_16_n_0));
  LUT2 #(
    .INIT(4'hE)) 
    ProtectOverflow_T_count_out11_carry_i_2
       (.I0(Pipeline1_out1[13]),
        .I1(Pipeline1_out1[12]),
        .O(ProtectOverflow_T_count_out11_carry_i_2_n_0));
  LUT2 #(
    .INIT(4'hE)) 
    ProtectOverflow_T_count_out11_carry_i_3
       (.I0(Pipeline1_out1[11]),
        .I1(Pipeline1_out1[10]),
        .O(ProtectOverflow_T_count_out11_carry_i_3_n_0));
  LUT2 #(
    .INIT(4'hE)) 
    ProtectOverflow_T_count_out11_carry_i_4
       (.I0(Pipeline1_out1[9]),
        .I1(Pipeline1_out1[8]),
        .O(ProtectOverflow_T_count_out11_carry_i_4_n_0));
  LUT2 #(
    .INIT(4'hE)) 
    ProtectOverflow_T_count_out11_carry_i_5
       (.I0(Pipeline1_out1[7]),
        .I1(Pipeline1_out1[6]),
        .O(ProtectOverflow_T_count_out11_carry_i_5_n_0));
  LUT2 #(
    .INIT(4'hE)) 
    ProtectOverflow_T_count_out11_carry_i_6
       (.I0(Pipeline1_out1[5]),
        .I1(Pipeline1_out1[4]),
        .O(ProtectOverflow_T_count_out11_carry_i_6_n_0));
  LUT2 #(
    .INIT(4'hE)) 
    ProtectOverflow_T_count_out11_carry_i_7
       (.I0(Pipeline1_out1[3]),
        .I1(Pipeline1_out1[2]),
        .O(ProtectOverflow_T_count_out11_carry_i_7_n_0));
  LUT2 #(
    .INIT(4'hE)) 
    ProtectOverflow_T_count_out11_carry_i_8
       (.I0(Pipeline1_out1[1]),
        .I1(Pipeline1_out1[0]),
        .O(ProtectOverflow_T_count_out11_carry_i_8_n_0));
  LUT2 #(
    .INIT(4'h1)) 
    ProtectOverflow_T_count_out11_carry_i_9
       (.I0(Pipeline1_out1[14]),
        .I1(Pipeline1_out1[15]),
        .O(ProtectOverflow_T_count_out11_carry_i_9_n_0));
  LUT5 #(
    .INIT(32'hF8F8F8F0)) 
    \T_count_out1[37]_i_1 
       (.I0(\T_count_out1_reg[37]_0 ),
        .I1(write_axi_enable),
        .I2(RSTP),
        .I3(switch_compare_1_2),
        .I4(\Delay1_out1_reg[15]_0 ),
        .O(\T_count_out1[37]_i_1_n_0 ));
  FDRE \T_count_out1_reg[0] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(speed_old_switch_out10_carry_n_15),
        .Q(T_count_out1[0]),
        .R(\T_count_out1[37]_i_1_n_0 ));
  FDRE \T_count_out1_reg[10] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(speed_old_switch_out10_carry__0_n_13),
        .Q(T_count_out1[10]),
        .R(\T_count_out1[37]_i_1_n_0 ));
  FDRE \T_count_out1_reg[11] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(speed_old_switch_out10_carry__0_n_12),
        .Q(T_count_out1[11]),
        .R(\T_count_out1[37]_i_1_n_0 ));
  FDRE \T_count_out1_reg[12] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(speed_old_switch_out10_carry__0_n_11),
        .Q(T_count_out1[12]),
        .R(\T_count_out1[37]_i_1_n_0 ));
  FDRE \T_count_out1_reg[13] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(speed_old_switch_out10_carry__0_n_10),
        .Q(T_count_out1[13]),
        .R(\T_count_out1[37]_i_1_n_0 ));
  FDRE \T_count_out1_reg[14] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(speed_old_switch_out10_carry__0_n_9),
        .Q(T_count_out1[14]),
        .R(\T_count_out1[37]_i_1_n_0 ));
  FDRE \T_count_out1_reg[15] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(speed_old_switch_out10_carry__0_n_8),
        .Q(T_count_out1[15]),
        .R(\T_count_out1[37]_i_1_n_0 ));
  FDRE \T_count_out1_reg[16] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(speed_old_switch_out10_carry__1_n_15),
        .Q(T_count_out1[16]),
        .R(\T_count_out1[37]_i_1_n_0 ));
  FDRE \T_count_out1_reg[17] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(speed_old_switch_out10_carry__1_n_14),
        .Q(T_count_out1[17]),
        .R(\T_count_out1[37]_i_1_n_0 ));
  FDRE \T_count_out1_reg[18] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(speed_old_switch_out10_carry__1_n_13),
        .Q(T_count_out1[18]),
        .R(\T_count_out1[37]_i_1_n_0 ));
  FDRE \T_count_out1_reg[19] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(speed_old_switch_out10_carry__1_n_12),
        .Q(T_count_out1[19]),
        .R(\T_count_out1[37]_i_1_n_0 ));
  FDRE \T_count_out1_reg[1] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(speed_old_switch_out10_carry_n_14),
        .Q(T_count_out1[1]),
        .R(\T_count_out1[37]_i_1_n_0 ));
  FDRE \T_count_out1_reg[20] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(speed_old_switch_out10_carry__1_n_11),
        .Q(T_count_out1[20]),
        .R(\T_count_out1[37]_i_1_n_0 ));
  FDRE \T_count_out1_reg[21] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(speed_old_switch_out10_carry__1_n_10),
        .Q(T_count_out1[21]),
        .R(\T_count_out1[37]_i_1_n_0 ));
  FDRE \T_count_out1_reg[22] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(speed_old_switch_out10_carry__1_n_9),
        .Q(T_count_out1[22]),
        .R(\T_count_out1[37]_i_1_n_0 ));
  FDRE \T_count_out1_reg[23] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(speed_old_switch_out10_carry__1_n_8),
        .Q(T_count_out1[23]),
        .R(\T_count_out1[37]_i_1_n_0 ));
  FDRE \T_count_out1_reg[24] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(speed_old_switch_out10_carry__2_n_15),
        .Q(T_count_out1[24]),
        .R(\T_count_out1[37]_i_1_n_0 ));
  FDRE \T_count_out1_reg[25] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(speed_old_switch_out10_carry__2_n_14),
        .Q(T_count_out1[25]),
        .R(\T_count_out1[37]_i_1_n_0 ));
  FDRE \T_count_out1_reg[26] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(speed_old_switch_out10_carry__2_n_13),
        .Q(T_count_out1[26]),
        .R(\T_count_out1[37]_i_1_n_0 ));
  FDRE \T_count_out1_reg[27] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(speed_old_switch_out10_carry__2_n_12),
        .Q(T_count_out1[27]),
        .R(\T_count_out1[37]_i_1_n_0 ));
  FDRE \T_count_out1_reg[28] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(speed_old_switch_out10_carry__2_n_11),
        .Q(T_count_out1[28]),
        .R(\T_count_out1[37]_i_1_n_0 ));
  FDRE \T_count_out1_reg[29] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(speed_old_switch_out10_carry__2_n_10),
        .Q(T_count_out1[29]),
        .R(\T_count_out1[37]_i_1_n_0 ));
  FDRE \T_count_out1_reg[2] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(speed_old_switch_out10_carry_n_13),
        .Q(T_count_out1[2]),
        .R(\T_count_out1[37]_i_1_n_0 ));
  FDRE \T_count_out1_reg[30] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(speed_old_switch_out10_carry__2_n_9),
        .Q(T_count_out1[30]),
        .R(\T_count_out1[37]_i_1_n_0 ));
  FDRE \T_count_out1_reg[31] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(speed_old_switch_out10_carry__2_n_8),
        .Q(T_count_out1[31]),
        .R(\T_count_out1[37]_i_1_n_0 ));
  FDRE \T_count_out1_reg[32] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(speed_old_switch_out10_carry__3_n_15),
        .Q(T_count_out1[32]),
        .R(\T_count_out1[37]_i_1_n_0 ));
  FDRE \T_count_out1_reg[33] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(speed_old_switch_out10_carry__3_n_14),
        .Q(T_count_out1[33]),
        .R(\T_count_out1[37]_i_1_n_0 ));
  FDRE \T_count_out1_reg[34] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(speed_old_switch_out10_carry__3_n_13),
        .Q(T_count_out1[34]),
        .R(\T_count_out1[37]_i_1_n_0 ));
  FDRE \T_count_out1_reg[35] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(speed_old_switch_out10_carry__3_n_12),
        .Q(T_count_out1[35]),
        .R(\T_count_out1[37]_i_1_n_0 ));
  FDRE \T_count_out1_reg[36] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(speed_old_switch_out10_carry__3_n_11),
        .Q(T_count_out1[36]),
        .R(\T_count_out1[37]_i_1_n_0 ));
  FDRE \T_count_out1_reg[37] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(speed_old_switch_out10_carry__3_n_10),
        .Q(T_count_out1[37]),
        .R(\T_count_out1[37]_i_1_n_0 ));
  FDRE \T_count_out1_reg[3] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(speed_old_switch_out10_carry_n_12),
        .Q(T_count_out1[3]),
        .R(\T_count_out1[37]_i_1_n_0 ));
  FDRE \T_count_out1_reg[4] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(speed_old_switch_out10_carry_n_11),
        .Q(T_count_out1[4]),
        .R(\T_count_out1[37]_i_1_n_0 ));
  FDRE \T_count_out1_reg[5] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(speed_old_switch_out10_carry_n_10),
        .Q(T_count_out1[5]),
        .R(\T_count_out1[37]_i_1_n_0 ));
  FDRE \T_count_out1_reg[6] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(speed_old_switch_out10_carry_n_9),
        .Q(T_count_out1[6]),
        .R(\T_count_out1[37]_i_1_n_0 ));
  FDRE \T_count_out1_reg[7] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(speed_old_switch_out10_carry_n_8),
        .Q(T_count_out1[7]),
        .R(\T_count_out1[37]_i_1_n_0 ));
  FDRE \T_count_out1_reg[8] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(speed_old_switch_out10_carry__0_n_15),
        .Q(T_count_out1[8]),
        .R(\T_count_out1[37]_i_1_n_0 ));
  FDRE \T_count_out1_reg[9] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(speed_old_switch_out10_carry__0_n_14),
        .Q(T_count_out1[9]),
        .R(\T_count_out1[37]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair160" *) 
  LUT2 #(
    .INIT(4'h6)) 
    \count_old1_out1[0]_i_1 
       (.I0(reset_old1_out1_reg_0),
        .I1(Logical2_out1_1),
        .O(\count_old1_out1[0]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair160" *) 
  LUT2 #(
    .INIT(4'h2)) 
    \count_old1_out1[1]_i_1 
       (.I0(reset_old1_out1_reg_0),
        .I1(Logical2_out1_1),
        .O(\count_old1_out1[1]_i_1_n_0 ));
  FDRE \count_old1_out1_reg[0] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\count_old1_out1[0]_i_1_n_0 ),
        .Q(count_old1_out1[0]),
        .R(RSTP));
  FDRE \count_old1_out1_reg[1] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\count_old1_out1[1]_i_1_n_0 ),
        .Q(count_old1_out1[1]),
        .R(RSTP));
  (* SOFT_HLUTNM = "soft_lutpair113" *) 
  LUT4 #(
    .INIT(16'h0A0C)) 
    \hold2_out1[0]_i_1 
       (.I0(speed_old_switch_out10_carry__0_n_9),
        .I1(speed_old_out1[14]),
        .I2(switch_compare_1_2),
        .I3(\Delay1_out1_reg[15]_0 ),
        .O(D[0]));
  (* SOFT_HLUTNM = "soft_lutpair123" *) 
  LUT4 #(
    .INIT(16'h0A0C)) 
    \hold2_out1[10]_i_1 
       (.I0(speed_old_switch_out10_carry__2_n_15),
        .I1(speed_old_out1[24]),
        .I2(switch_compare_1_2),
        .I3(\Delay1_out1_reg[15]_0 ),
        .O(D[10]));
  (* SOFT_HLUTNM = "soft_lutpair124" *) 
  LUT4 #(
    .INIT(16'h0A0C)) 
    \hold2_out1[11]_i_1 
       (.I0(speed_old_switch_out10_carry__2_n_14),
        .I1(speed_old_out1[25]),
        .I2(switch_compare_1_2),
        .I3(\Delay1_out1_reg[15]_0 ),
        .O(D[11]));
  (* SOFT_HLUTNM = "soft_lutpair125" *) 
  LUT4 #(
    .INIT(16'h0A0C)) 
    \hold2_out1[12]_i_1 
       (.I0(speed_old_switch_out10_carry__2_n_13),
        .I1(speed_old_out1[26]),
        .I2(switch_compare_1_2),
        .I3(\Delay1_out1_reg[15]_0 ),
        .O(D[12]));
  (* SOFT_HLUTNM = "soft_lutpair126" *) 
  LUT4 #(
    .INIT(16'h0A0C)) 
    \hold2_out1[13]_i_1 
       (.I0(speed_old_switch_out10_carry__2_n_12),
        .I1(speed_old_out1[27]),
        .I2(switch_compare_1_2),
        .I3(\Delay1_out1_reg[15]_0 ),
        .O(D[13]));
  (* SOFT_HLUTNM = "soft_lutpair127" *) 
  LUT4 #(
    .INIT(16'h0A0C)) 
    \hold2_out1[14]_i_1 
       (.I0(speed_old_switch_out10_carry__2_n_11),
        .I1(speed_old_out1[28]),
        .I2(switch_compare_1_2),
        .I3(\Delay1_out1_reg[15]_0 ),
        .O(D[14]));
  (* SOFT_HLUTNM = "soft_lutpair128" *) 
  LUT4 #(
    .INIT(16'h0A0C)) 
    \hold2_out1[15]_i_1 
       (.I0(speed_old_switch_out10_carry__2_n_10),
        .I1(speed_old_out1[29]),
        .I2(switch_compare_1_2),
        .I3(\Delay1_out1_reg[15]_0 ),
        .O(D[15]));
  (* SOFT_HLUTNM = "soft_lutpair129" *) 
  LUT4 #(
    .INIT(16'h0A0C)) 
    \hold2_out1[16]_i_1 
       (.I0(speed_old_switch_out10_carry__2_n_9),
        .I1(speed_old_out1[30]),
        .I2(switch_compare_1_2),
        .I3(\Delay1_out1_reg[15]_0 ),
        .O(D[16]));
  (* SOFT_HLUTNM = "soft_lutpair130" *) 
  LUT4 #(
    .INIT(16'h0A0C)) 
    \hold2_out1[17]_i_1 
       (.I0(speed_old_switch_out10_carry__2_n_8),
        .I1(speed_old_out1[31]),
        .I2(switch_compare_1_2),
        .I3(\Delay1_out1_reg[15]_0 ),
        .O(D[17]));
  (* SOFT_HLUTNM = "soft_lutpair131" *) 
  LUT4 #(
    .INIT(16'h0A0C)) 
    \hold2_out1[18]_i_1 
       (.I0(speed_old_switch_out10_carry__3_n_15),
        .I1(speed_old_out1[32]),
        .I2(switch_compare_1_2),
        .I3(\Delay1_out1_reg[15]_0 ),
        .O(D[18]));
  (* SOFT_HLUTNM = "soft_lutpair132" *) 
  LUT4 #(
    .INIT(16'h0A0C)) 
    \hold2_out1[19]_i_1 
       (.I0(speed_old_switch_out10_carry__3_n_14),
        .I1(speed_old_out1[33]),
        .I2(switch_compare_1_2),
        .I3(\Delay1_out1_reg[15]_0 ),
        .O(D[19]));
  (* SOFT_HLUTNM = "soft_lutpair114" *) 
  LUT4 #(
    .INIT(16'h0A0C)) 
    \hold2_out1[1]_i_1 
       (.I0(speed_old_switch_out10_carry__0_n_8),
        .I1(speed_old_out1[15]),
        .I2(switch_compare_1_2),
        .I3(\Delay1_out1_reg[15]_0 ),
        .O(D[1]));
  (* SOFT_HLUTNM = "soft_lutpair133" *) 
  LUT4 #(
    .INIT(16'h0A0C)) 
    \hold2_out1[20]_i_1 
       (.I0(speed_old_switch_out10_carry__3_n_13),
        .I1(speed_old_out1[34]),
        .I2(switch_compare_1_2),
        .I3(\Delay1_out1_reg[15]_0 ),
        .O(D[20]));
  (* SOFT_HLUTNM = "soft_lutpair134" *) 
  LUT4 #(
    .INIT(16'h0A0C)) 
    \hold2_out1[21]_i_1 
       (.I0(speed_old_switch_out10_carry__3_n_12),
        .I1(speed_old_out1[35]),
        .I2(switch_compare_1_2),
        .I3(\Delay1_out1_reg[15]_0 ),
        .O(D[21]));
  (* SOFT_HLUTNM = "soft_lutpair135" *) 
  LUT4 #(
    .INIT(16'h0A0C)) 
    \hold2_out1[22]_i_1 
       (.I0(speed_old_switch_out10_carry__3_n_11),
        .I1(speed_old_out1[36]),
        .I2(switch_compare_1_2),
        .I3(\Delay1_out1_reg[15]_0 ),
        .O(D[22]));
  (* SOFT_HLUTNM = "soft_lutpair115" *) 
  LUT4 #(
    .INIT(16'h0A0C)) 
    \hold2_out1[2]_i_1 
       (.I0(speed_old_switch_out10_carry__1_n_15),
        .I1(speed_old_out1[16]),
        .I2(switch_compare_1_2),
        .I3(\Delay1_out1_reg[15]_0 ),
        .O(D[2]));
  (* SOFT_HLUTNM = "soft_lutpair136" *) 
  LUT4 #(
    .INIT(16'h0A0C)) 
    \hold2_out1[31]_i_1 
       (.I0(speed_old_switch_out10_carry__3_n_10),
        .I1(speed_old_out1[37]),
        .I2(switch_compare_1_2),
        .I3(\Delay1_out1_reg[15]_0 ),
        .O(D[23]));
  (* SOFT_HLUTNM = "soft_lutpair116" *) 
  LUT4 #(
    .INIT(16'h0A0C)) 
    \hold2_out1[3]_i_1 
       (.I0(speed_old_switch_out10_carry__1_n_14),
        .I1(speed_old_out1[17]),
        .I2(switch_compare_1_2),
        .I3(\Delay1_out1_reg[15]_0 ),
        .O(D[3]));
  (* SOFT_HLUTNM = "soft_lutpair117" *) 
  LUT4 #(
    .INIT(16'h0A0C)) 
    \hold2_out1[4]_i_1 
       (.I0(speed_old_switch_out10_carry__1_n_13),
        .I1(speed_old_out1[18]),
        .I2(switch_compare_1_2),
        .I3(\Delay1_out1_reg[15]_0 ),
        .O(D[4]));
  (* SOFT_HLUTNM = "soft_lutpair118" *) 
  LUT4 #(
    .INIT(16'h0A0C)) 
    \hold2_out1[5]_i_1 
       (.I0(speed_old_switch_out10_carry__1_n_12),
        .I1(speed_old_out1[19]),
        .I2(switch_compare_1_2),
        .I3(\Delay1_out1_reg[15]_0 ),
        .O(D[5]));
  (* SOFT_HLUTNM = "soft_lutpair119" *) 
  LUT4 #(
    .INIT(16'h0A0C)) 
    \hold2_out1[6]_i_1 
       (.I0(speed_old_switch_out10_carry__1_n_11),
        .I1(speed_old_out1[20]),
        .I2(switch_compare_1_2),
        .I3(\Delay1_out1_reg[15]_0 ),
        .O(D[6]));
  (* SOFT_HLUTNM = "soft_lutpair120" *) 
  LUT4 #(
    .INIT(16'h0A0C)) 
    \hold2_out1[7]_i_1 
       (.I0(speed_old_switch_out10_carry__1_n_10),
        .I1(speed_old_out1[21]),
        .I2(switch_compare_1_2),
        .I3(\Delay1_out1_reg[15]_0 ),
        .O(D[7]));
  (* SOFT_HLUTNM = "soft_lutpair121" *) 
  LUT4 #(
    .INIT(16'h0A0C)) 
    \hold2_out1[8]_i_1 
       (.I0(speed_old_switch_out10_carry__1_n_9),
        .I1(speed_old_out1[22]),
        .I2(switch_compare_1_2),
        .I3(\Delay1_out1_reg[15]_0 ),
        .O(D[8]));
  (* SOFT_HLUTNM = "soft_lutpair122" *) 
  LUT4 #(
    .INIT(16'h0A0C)) 
    \hold2_out1[9]_i_1 
       (.I0(speed_old_switch_out10_carry__1_n_8),
        .I1(speed_old_out1[23]),
        .I2(switch_compare_1_2),
        .I3(\Delay1_out1_reg[15]_0 ),
        .O(D[9]));
  FDRE reset_old1_out1_reg
       (.C(IPCORE_CLK),
        .CE(1'b1),
        .D(reset_old1_out1_reg_1),
        .Q(reset_old1_out1_reg_0),
        .R(RSTP));
  (* SOFT_HLUTNM = "soft_lutpair113" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \speed_old_out1[14]_i_1 
       (.I0(speed_old_switch_out10_carry__0_n_9),
        .I1(\Delay1_out1_reg[15]_0 ),
        .I2(speed_old_out1[14]),
        .O(speed_old_switch_out1[14]));
  (* SOFT_HLUTNM = "soft_lutpair114" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \speed_old_out1[15]_i_1 
       (.I0(speed_old_switch_out10_carry__0_n_8),
        .I1(\Delay1_out1_reg[15]_0 ),
        .I2(speed_old_out1[15]),
        .O(speed_old_switch_out1[15]));
  (* SOFT_HLUTNM = "soft_lutpair115" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \speed_old_out1[16]_i_1 
       (.I0(speed_old_switch_out10_carry__1_n_15),
        .I1(\Delay1_out1_reg[15]_0 ),
        .I2(speed_old_out1[16]),
        .O(speed_old_switch_out1[16]));
  (* SOFT_HLUTNM = "soft_lutpair116" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \speed_old_out1[17]_i_1 
       (.I0(speed_old_switch_out10_carry__1_n_14),
        .I1(\Delay1_out1_reg[15]_0 ),
        .I2(speed_old_out1[17]),
        .O(speed_old_switch_out1[17]));
  (* SOFT_HLUTNM = "soft_lutpair117" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \speed_old_out1[18]_i_1 
       (.I0(speed_old_switch_out10_carry__1_n_13),
        .I1(\Delay1_out1_reg[15]_0 ),
        .I2(speed_old_out1[18]),
        .O(speed_old_switch_out1[18]));
  (* SOFT_HLUTNM = "soft_lutpair118" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \speed_old_out1[19]_i_1 
       (.I0(speed_old_switch_out10_carry__1_n_12),
        .I1(\Delay1_out1_reg[15]_0 ),
        .I2(speed_old_out1[19]),
        .O(speed_old_switch_out1[19]));
  (* SOFT_HLUTNM = "soft_lutpair119" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \speed_old_out1[20]_i_1 
       (.I0(speed_old_switch_out10_carry__1_n_11),
        .I1(\Delay1_out1_reg[15]_0 ),
        .I2(speed_old_out1[20]),
        .O(speed_old_switch_out1[20]));
  (* SOFT_HLUTNM = "soft_lutpair120" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \speed_old_out1[21]_i_1 
       (.I0(speed_old_switch_out10_carry__1_n_10),
        .I1(\Delay1_out1_reg[15]_0 ),
        .I2(speed_old_out1[21]),
        .O(speed_old_switch_out1[21]));
  (* SOFT_HLUTNM = "soft_lutpair121" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \speed_old_out1[22]_i_1 
       (.I0(speed_old_switch_out10_carry__1_n_9),
        .I1(\Delay1_out1_reg[15]_0 ),
        .I2(speed_old_out1[22]),
        .O(speed_old_switch_out1[22]));
  (* SOFT_HLUTNM = "soft_lutpair122" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \speed_old_out1[23]_i_1 
       (.I0(speed_old_switch_out10_carry__1_n_8),
        .I1(\Delay1_out1_reg[15]_0 ),
        .I2(speed_old_out1[23]),
        .O(speed_old_switch_out1[23]));
  (* SOFT_HLUTNM = "soft_lutpair123" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \speed_old_out1[24]_i_1 
       (.I0(speed_old_switch_out10_carry__2_n_15),
        .I1(\Delay1_out1_reg[15]_0 ),
        .I2(speed_old_out1[24]),
        .O(speed_old_switch_out1[24]));
  (* SOFT_HLUTNM = "soft_lutpair124" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \speed_old_out1[25]_i_1 
       (.I0(speed_old_switch_out10_carry__2_n_14),
        .I1(\Delay1_out1_reg[15]_0 ),
        .I2(speed_old_out1[25]),
        .O(speed_old_switch_out1[25]));
  (* SOFT_HLUTNM = "soft_lutpair125" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \speed_old_out1[26]_i_1 
       (.I0(speed_old_switch_out10_carry__2_n_13),
        .I1(\Delay1_out1_reg[15]_0 ),
        .I2(speed_old_out1[26]),
        .O(speed_old_switch_out1[26]));
  (* SOFT_HLUTNM = "soft_lutpair126" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \speed_old_out1[27]_i_1 
       (.I0(speed_old_switch_out10_carry__2_n_12),
        .I1(\Delay1_out1_reg[15]_0 ),
        .I2(speed_old_out1[27]),
        .O(speed_old_switch_out1[27]));
  (* SOFT_HLUTNM = "soft_lutpair127" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \speed_old_out1[28]_i_1 
       (.I0(speed_old_switch_out10_carry__2_n_11),
        .I1(\Delay1_out1_reg[15]_0 ),
        .I2(speed_old_out1[28]),
        .O(speed_old_switch_out1[28]));
  (* SOFT_HLUTNM = "soft_lutpair128" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \speed_old_out1[29]_i_1 
       (.I0(speed_old_switch_out10_carry__2_n_10),
        .I1(\Delay1_out1_reg[15]_0 ),
        .I2(speed_old_out1[29]),
        .O(speed_old_switch_out1[29]));
  (* SOFT_HLUTNM = "soft_lutpair129" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \speed_old_out1[30]_i_1 
       (.I0(speed_old_switch_out10_carry__2_n_9),
        .I1(\Delay1_out1_reg[15]_0 ),
        .I2(speed_old_out1[30]),
        .O(speed_old_switch_out1[30]));
  (* SOFT_HLUTNM = "soft_lutpair130" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \speed_old_out1[31]_i_1 
       (.I0(speed_old_switch_out10_carry__2_n_8),
        .I1(\Delay1_out1_reg[15]_0 ),
        .I2(speed_old_out1[31]),
        .O(speed_old_switch_out1[31]));
  (* SOFT_HLUTNM = "soft_lutpair131" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \speed_old_out1[32]_i_1 
       (.I0(speed_old_switch_out10_carry__3_n_15),
        .I1(\Delay1_out1_reg[15]_0 ),
        .I2(speed_old_out1[32]),
        .O(speed_old_switch_out1[32]));
  (* SOFT_HLUTNM = "soft_lutpair132" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \speed_old_out1[33]_i_1 
       (.I0(speed_old_switch_out10_carry__3_n_14),
        .I1(\Delay1_out1_reg[15]_0 ),
        .I2(speed_old_out1[33]),
        .O(speed_old_switch_out1[33]));
  (* SOFT_HLUTNM = "soft_lutpair133" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \speed_old_out1[34]_i_1 
       (.I0(speed_old_switch_out10_carry__3_n_13),
        .I1(\Delay1_out1_reg[15]_0 ),
        .I2(speed_old_out1[34]),
        .O(speed_old_switch_out1[34]));
  (* SOFT_HLUTNM = "soft_lutpair134" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \speed_old_out1[35]_i_1 
       (.I0(speed_old_switch_out10_carry__3_n_12),
        .I1(\Delay1_out1_reg[15]_0 ),
        .I2(speed_old_out1[35]),
        .O(speed_old_switch_out1[35]));
  (* SOFT_HLUTNM = "soft_lutpair135" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \speed_old_out1[36]_i_1 
       (.I0(speed_old_switch_out10_carry__3_n_11),
        .I1(\Delay1_out1_reg[15]_0 ),
        .I2(speed_old_out1[36]),
        .O(speed_old_switch_out1[36]));
  (* SOFT_HLUTNM = "soft_lutpair136" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \speed_old_out1[37]_i_1 
       (.I0(speed_old_switch_out10_carry__3_n_10),
        .I1(\Delay1_out1_reg[15]_0 ),
        .I2(speed_old_out1[37]),
        .O(speed_old_switch_out1[37]));
  FDRE \speed_old_out1_reg[14] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(speed_old_switch_out1[14]),
        .Q(speed_old_out1[14]),
        .R(RSTP));
  FDRE \speed_old_out1_reg[15] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(speed_old_switch_out1[15]),
        .Q(speed_old_out1[15]),
        .R(RSTP));
  FDRE \speed_old_out1_reg[16] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(speed_old_switch_out1[16]),
        .Q(speed_old_out1[16]),
        .R(RSTP));
  FDRE \speed_old_out1_reg[17] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(speed_old_switch_out1[17]),
        .Q(speed_old_out1[17]),
        .R(RSTP));
  FDRE \speed_old_out1_reg[18] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(speed_old_switch_out1[18]),
        .Q(speed_old_out1[18]),
        .R(RSTP));
  FDRE \speed_old_out1_reg[19] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(speed_old_switch_out1[19]),
        .Q(speed_old_out1[19]),
        .R(RSTP));
  FDRE \speed_old_out1_reg[20] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(speed_old_switch_out1[20]),
        .Q(speed_old_out1[20]),
        .R(RSTP));
  FDRE \speed_old_out1_reg[21] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(speed_old_switch_out1[21]),
        .Q(speed_old_out1[21]),
        .R(RSTP));
  FDRE \speed_old_out1_reg[22] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(speed_old_switch_out1[22]),
        .Q(speed_old_out1[22]),
        .R(RSTP));
  FDRE \speed_old_out1_reg[23] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(speed_old_switch_out1[23]),
        .Q(speed_old_out1[23]),
        .R(RSTP));
  FDRE \speed_old_out1_reg[24] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(speed_old_switch_out1[24]),
        .Q(speed_old_out1[24]),
        .R(RSTP));
  FDRE \speed_old_out1_reg[25] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(speed_old_switch_out1[25]),
        .Q(speed_old_out1[25]),
        .R(RSTP));
  FDRE \speed_old_out1_reg[26] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(speed_old_switch_out1[26]),
        .Q(speed_old_out1[26]),
        .R(RSTP));
  FDRE \speed_old_out1_reg[27] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(speed_old_switch_out1[27]),
        .Q(speed_old_out1[27]),
        .R(RSTP));
  FDRE \speed_old_out1_reg[28] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(speed_old_switch_out1[28]),
        .Q(speed_old_out1[28]),
        .R(RSTP));
  FDRE \speed_old_out1_reg[29] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(speed_old_switch_out1[29]),
        .Q(speed_old_out1[29]),
        .R(RSTP));
  FDRE \speed_old_out1_reg[30] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(speed_old_switch_out1[30]),
        .Q(speed_old_out1[30]),
        .R(RSTP));
  FDRE \speed_old_out1_reg[31] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(speed_old_switch_out1[31]),
        .Q(speed_old_out1[31]),
        .R(RSTP));
  FDRE \speed_old_out1_reg[32] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(speed_old_switch_out1[32]),
        .Q(speed_old_out1[32]),
        .R(RSTP));
  FDRE \speed_old_out1_reg[33] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(speed_old_switch_out1[33]),
        .Q(speed_old_out1[33]),
        .R(RSTP));
  FDRE \speed_old_out1_reg[34] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(speed_old_switch_out1[34]),
        .Q(speed_old_out1[34]),
        .R(RSTP));
  FDRE \speed_old_out1_reg[35] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(speed_old_switch_out1[35]),
        .Q(speed_old_out1[35]),
        .R(RSTP));
  FDRE \speed_old_out1_reg[36] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(speed_old_switch_out1[36]),
        .Q(speed_old_out1[36]),
        .R(RSTP));
  FDRE \speed_old_out1_reg[37] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(speed_old_switch_out1[37]),
        .Q(speed_old_out1[37]),
        .R(RSTP));
  (* ADDER_THRESHOLD = "35" *) 
  (* METHODOLOGY_DRC_VIOS = "{SYNTH-8 {cell *THIS*}}" *) 
  CARRY8 speed_old_switch_out10_carry
       (.CI(speed_old_switch_out10_carry_i_1_n_0),
        .CI_TOP(1'b0),
        .CO({speed_old_switch_out10_carry_n_0,speed_old_switch_out10_carry_n_1,speed_old_switch_out10_carry_n_2,speed_old_switch_out10_carry_n_3,speed_old_switch_out10_carry_n_4,speed_old_switch_out10_carry_n_5,speed_old_switch_out10_carry_n_6,speed_old_switch_out10_carry_n_7}),
        .DI(T_count_out1[7:0]),
        .O({speed_old_switch_out10_carry_n_8,speed_old_switch_out10_carry_n_9,speed_old_switch_out10_carry_n_10,speed_old_switch_out10_carry_n_11,speed_old_switch_out10_carry_n_12,speed_old_switch_out10_carry_n_13,speed_old_switch_out10_carry_n_14,speed_old_switch_out10_carry_n_15}),
        .S({speed_old_switch_out10_carry_i_2_n_0,speed_old_switch_out10_carry_i_3_n_0,speed_old_switch_out10_carry_i_4_n_0,speed_old_switch_out10_carry_i_5_n_0,speed_old_switch_out10_carry_i_6_n_0,speed_old_switch_out10_carry_i_7_n_0,speed_old_switch_out10_carry_i_8_n_0,speed_old_switch_out10_carry_i_9_n_0}));
  (* ADDER_THRESHOLD = "35" *) 
  (* METHODOLOGY_DRC_VIOS = "{SYNTH-8 {cell *THIS*}}" *) 
  CARRY8 speed_old_switch_out10_carry__0
       (.CI(speed_old_switch_out10_carry_n_0),
        .CI_TOP(1'b0),
        .CO({speed_old_switch_out10_carry__0_n_0,speed_old_switch_out10_carry__0_n_1,speed_old_switch_out10_carry__0_n_2,speed_old_switch_out10_carry__0_n_3,speed_old_switch_out10_carry__0_n_4,speed_old_switch_out10_carry__0_n_5,speed_old_switch_out10_carry__0_n_6,speed_old_switch_out10_carry__0_n_7}),
        .DI(T_count_out1[15:8]),
        .O({speed_old_switch_out10_carry__0_n_8,speed_old_switch_out10_carry__0_n_9,speed_old_switch_out10_carry__0_n_10,speed_old_switch_out10_carry__0_n_11,speed_old_switch_out10_carry__0_n_12,speed_old_switch_out10_carry__0_n_13,speed_old_switch_out10_carry__0_n_14,speed_old_switch_out10_carry__0_n_15}),
        .S({speed_old_switch_out10_carry__0_i_1_n_0,speed_old_switch_out10_carry__0_i_2_n_0,speed_old_switch_out10_carry__0_i_3_n_0,speed_old_switch_out10_carry__0_i_4_n_0,speed_old_switch_out10_carry__0_i_5_n_0,speed_old_switch_out10_carry__0_i_6_n_0,speed_old_switch_out10_carry__0_i_7_n_0,speed_old_switch_out10_carry__0_i_8_n_0}));
  LUT4 #(
    .INIT(16'h9969)) 
    speed_old_switch_out10_carry__0_i_1
       (.I0(T_count_out1[15]),
        .I1(\T_count_out1_reg[31]_0 [15]),
        .I2(\T_count_out1_reg[7]_0 [0]),
        .I3(\T_count_out1_reg[7]_0 [1]),
        .O(speed_old_switch_out10_carry__0_i_1_n_0));
  LUT4 #(
    .INIT(16'h9969)) 
    speed_old_switch_out10_carry__0_i_2
       (.I0(T_count_out1[14]),
        .I1(\T_count_out1_reg[31]_0 [14]),
        .I2(\T_count_out1_reg[7]_0 [0]),
        .I3(\T_count_out1_reg[7]_0 [1]),
        .O(speed_old_switch_out10_carry__0_i_2_n_0));
  LUT4 #(
    .INIT(16'h9969)) 
    speed_old_switch_out10_carry__0_i_3
       (.I0(T_count_out1[13]),
        .I1(\T_count_out1_reg[31]_0 [13]),
        .I2(\T_count_out1_reg[7]_0 [0]),
        .I3(\T_count_out1_reg[7]_0 [1]),
        .O(speed_old_switch_out10_carry__0_i_3_n_0));
  LUT4 #(
    .INIT(16'h9969)) 
    speed_old_switch_out10_carry__0_i_4
       (.I0(T_count_out1[12]),
        .I1(\T_count_out1_reg[31]_0 [12]),
        .I2(\T_count_out1_reg[7]_0 [0]),
        .I3(\T_count_out1_reg[7]_0 [1]),
        .O(speed_old_switch_out10_carry__0_i_4_n_0));
  LUT4 #(
    .INIT(16'h9969)) 
    speed_old_switch_out10_carry__0_i_5
       (.I0(T_count_out1[11]),
        .I1(\T_count_out1_reg[31]_0 [11]),
        .I2(\T_count_out1_reg[7]_0 [0]),
        .I3(\T_count_out1_reg[7]_0 [1]),
        .O(speed_old_switch_out10_carry__0_i_5_n_0));
  LUT4 #(
    .INIT(16'h9969)) 
    speed_old_switch_out10_carry__0_i_6
       (.I0(T_count_out1[10]),
        .I1(\T_count_out1_reg[31]_0 [10]),
        .I2(\T_count_out1_reg[7]_0 [0]),
        .I3(\T_count_out1_reg[7]_0 [1]),
        .O(speed_old_switch_out10_carry__0_i_6_n_0));
  LUT4 #(
    .INIT(16'h9969)) 
    speed_old_switch_out10_carry__0_i_7
       (.I0(T_count_out1[9]),
        .I1(\T_count_out1_reg[31]_0 [9]),
        .I2(\T_count_out1_reg[7]_0 [0]),
        .I3(\T_count_out1_reg[7]_0 [1]),
        .O(speed_old_switch_out10_carry__0_i_7_n_0));
  LUT4 #(
    .INIT(16'h9969)) 
    speed_old_switch_out10_carry__0_i_8
       (.I0(T_count_out1[8]),
        .I1(\T_count_out1_reg[31]_0 [8]),
        .I2(\T_count_out1_reg[7]_0 [0]),
        .I3(\T_count_out1_reg[7]_0 [1]),
        .O(speed_old_switch_out10_carry__0_i_8_n_0));
  (* ADDER_THRESHOLD = "35" *) 
  (* METHODOLOGY_DRC_VIOS = "{SYNTH-8 {cell *THIS*}}" *) 
  CARRY8 speed_old_switch_out10_carry__1
       (.CI(speed_old_switch_out10_carry__0_n_0),
        .CI_TOP(1'b0),
        .CO({speed_old_switch_out10_carry__1_n_0,speed_old_switch_out10_carry__1_n_1,speed_old_switch_out10_carry__1_n_2,speed_old_switch_out10_carry__1_n_3,speed_old_switch_out10_carry__1_n_4,speed_old_switch_out10_carry__1_n_5,speed_old_switch_out10_carry__1_n_6,speed_old_switch_out10_carry__1_n_7}),
        .DI(T_count_out1[23:16]),
        .O({speed_old_switch_out10_carry__1_n_8,speed_old_switch_out10_carry__1_n_9,speed_old_switch_out10_carry__1_n_10,speed_old_switch_out10_carry__1_n_11,speed_old_switch_out10_carry__1_n_12,speed_old_switch_out10_carry__1_n_13,speed_old_switch_out10_carry__1_n_14,speed_old_switch_out10_carry__1_n_15}),
        .S({speed_old_switch_out10_carry__1_i_1_n_0,speed_old_switch_out10_carry__1_i_2_n_0,speed_old_switch_out10_carry__1_i_3_n_0,speed_old_switch_out10_carry__1_i_4_n_0,speed_old_switch_out10_carry__1_i_5_n_0,speed_old_switch_out10_carry__1_i_6_n_0,speed_old_switch_out10_carry__1_i_7_n_0,speed_old_switch_out10_carry__1_i_8_n_0}));
  LUT4 #(
    .INIT(16'h9969)) 
    speed_old_switch_out10_carry__1_i_1
       (.I0(T_count_out1[23]),
        .I1(\T_count_out1_reg[31]_0 [23]),
        .I2(\T_count_out1_reg[7]_0 [0]),
        .I3(\T_count_out1_reg[7]_0 [1]),
        .O(speed_old_switch_out10_carry__1_i_1_n_0));
  LUT4 #(
    .INIT(16'h9969)) 
    speed_old_switch_out10_carry__1_i_2
       (.I0(T_count_out1[22]),
        .I1(\T_count_out1_reg[31]_0 [22]),
        .I2(\T_count_out1_reg[7]_0 [0]),
        .I3(\T_count_out1_reg[7]_0 [1]),
        .O(speed_old_switch_out10_carry__1_i_2_n_0));
  LUT4 #(
    .INIT(16'h9969)) 
    speed_old_switch_out10_carry__1_i_3
       (.I0(T_count_out1[21]),
        .I1(\T_count_out1_reg[31]_0 [21]),
        .I2(\T_count_out1_reg[7]_0 [0]),
        .I3(\T_count_out1_reg[7]_0 [1]),
        .O(speed_old_switch_out10_carry__1_i_3_n_0));
  LUT4 #(
    .INIT(16'h9969)) 
    speed_old_switch_out10_carry__1_i_4
       (.I0(T_count_out1[20]),
        .I1(\T_count_out1_reg[31]_0 [20]),
        .I2(\T_count_out1_reg[7]_0 [0]),
        .I3(\T_count_out1_reg[7]_0 [1]),
        .O(speed_old_switch_out10_carry__1_i_4_n_0));
  LUT4 #(
    .INIT(16'h9969)) 
    speed_old_switch_out10_carry__1_i_5
       (.I0(T_count_out1[19]),
        .I1(\T_count_out1_reg[31]_0 [19]),
        .I2(\T_count_out1_reg[7]_0 [0]),
        .I3(\T_count_out1_reg[7]_0 [1]),
        .O(speed_old_switch_out10_carry__1_i_5_n_0));
  LUT4 #(
    .INIT(16'h9969)) 
    speed_old_switch_out10_carry__1_i_6
       (.I0(T_count_out1[18]),
        .I1(\T_count_out1_reg[31]_0 [18]),
        .I2(\T_count_out1_reg[7]_0 [0]),
        .I3(\T_count_out1_reg[7]_0 [1]),
        .O(speed_old_switch_out10_carry__1_i_6_n_0));
  LUT4 #(
    .INIT(16'h9969)) 
    speed_old_switch_out10_carry__1_i_7
       (.I0(T_count_out1[17]),
        .I1(\T_count_out1_reg[31]_0 [17]),
        .I2(\T_count_out1_reg[7]_0 [0]),
        .I3(\T_count_out1_reg[7]_0 [1]),
        .O(speed_old_switch_out10_carry__1_i_7_n_0));
  LUT4 #(
    .INIT(16'h9969)) 
    speed_old_switch_out10_carry__1_i_8
       (.I0(T_count_out1[16]),
        .I1(\T_count_out1_reg[31]_0 [16]),
        .I2(\T_count_out1_reg[7]_0 [0]),
        .I3(\T_count_out1_reg[7]_0 [1]),
        .O(speed_old_switch_out10_carry__1_i_8_n_0));
  (* ADDER_THRESHOLD = "35" *) 
  (* METHODOLOGY_DRC_VIOS = "{SYNTH-8 {cell *THIS*}}" *) 
  CARRY8 speed_old_switch_out10_carry__2
       (.CI(speed_old_switch_out10_carry__1_n_0),
        .CI_TOP(1'b0),
        .CO({speed_old_switch_out10_carry__2_n_0,speed_old_switch_out10_carry__2_n_1,speed_old_switch_out10_carry__2_n_2,speed_old_switch_out10_carry__2_n_3,speed_old_switch_out10_carry__2_n_4,speed_old_switch_out10_carry__2_n_5,speed_old_switch_out10_carry__2_n_6,speed_old_switch_out10_carry__2_n_7}),
        .DI(T_count_out1[31:24]),
        .O({speed_old_switch_out10_carry__2_n_8,speed_old_switch_out10_carry__2_n_9,speed_old_switch_out10_carry__2_n_10,speed_old_switch_out10_carry__2_n_11,speed_old_switch_out10_carry__2_n_12,speed_old_switch_out10_carry__2_n_13,speed_old_switch_out10_carry__2_n_14,speed_old_switch_out10_carry__2_n_15}),
        .S({speed_old_switch_out10_carry__2_i_1_n_0,speed_old_switch_out10_carry__2_i_2_n_0,speed_old_switch_out10_carry__2_i_3_n_0,speed_old_switch_out10_carry__2_i_4_n_0,speed_old_switch_out10_carry__2_i_5_n_0,speed_old_switch_out10_carry__2_i_6_n_0,speed_old_switch_out10_carry__2_i_7_n_0,speed_old_switch_out10_carry__2_i_8_n_0}));
  LUT4 #(
    .INIT(16'h9969)) 
    speed_old_switch_out10_carry__2_i_1
       (.I0(T_count_out1[31]),
        .I1(\T_count_out1_reg[31]_0 [31]),
        .I2(\T_count_out1_reg[7]_0 [0]),
        .I3(\T_count_out1_reg[7]_0 [1]),
        .O(speed_old_switch_out10_carry__2_i_1_n_0));
  LUT4 #(
    .INIT(16'h9969)) 
    speed_old_switch_out10_carry__2_i_2
       (.I0(T_count_out1[30]),
        .I1(\T_count_out1_reg[31]_0 [30]),
        .I2(\T_count_out1_reg[7]_0 [0]),
        .I3(\T_count_out1_reg[7]_0 [1]),
        .O(speed_old_switch_out10_carry__2_i_2_n_0));
  LUT4 #(
    .INIT(16'h9969)) 
    speed_old_switch_out10_carry__2_i_3
       (.I0(T_count_out1[29]),
        .I1(\T_count_out1_reg[31]_0 [29]),
        .I2(\T_count_out1_reg[7]_0 [0]),
        .I3(\T_count_out1_reg[7]_0 [1]),
        .O(speed_old_switch_out10_carry__2_i_3_n_0));
  LUT4 #(
    .INIT(16'h9969)) 
    speed_old_switch_out10_carry__2_i_4
       (.I0(T_count_out1[28]),
        .I1(\T_count_out1_reg[31]_0 [28]),
        .I2(\T_count_out1_reg[7]_0 [0]),
        .I3(\T_count_out1_reg[7]_0 [1]),
        .O(speed_old_switch_out10_carry__2_i_4_n_0));
  LUT4 #(
    .INIT(16'h9969)) 
    speed_old_switch_out10_carry__2_i_5
       (.I0(T_count_out1[27]),
        .I1(\T_count_out1_reg[31]_0 [27]),
        .I2(\T_count_out1_reg[7]_0 [0]),
        .I3(\T_count_out1_reg[7]_0 [1]),
        .O(speed_old_switch_out10_carry__2_i_5_n_0));
  LUT4 #(
    .INIT(16'h9969)) 
    speed_old_switch_out10_carry__2_i_6
       (.I0(T_count_out1[26]),
        .I1(\T_count_out1_reg[31]_0 [26]),
        .I2(\T_count_out1_reg[7]_0 [0]),
        .I3(\T_count_out1_reg[7]_0 [1]),
        .O(speed_old_switch_out10_carry__2_i_6_n_0));
  LUT4 #(
    .INIT(16'h9969)) 
    speed_old_switch_out10_carry__2_i_7
       (.I0(T_count_out1[25]),
        .I1(\T_count_out1_reg[31]_0 [25]),
        .I2(\T_count_out1_reg[7]_0 [0]),
        .I3(\T_count_out1_reg[7]_0 [1]),
        .O(speed_old_switch_out10_carry__2_i_7_n_0));
  LUT4 #(
    .INIT(16'h9969)) 
    speed_old_switch_out10_carry__2_i_8
       (.I0(T_count_out1[24]),
        .I1(\T_count_out1_reg[31]_0 [24]),
        .I2(\T_count_out1_reg[7]_0 [0]),
        .I3(\T_count_out1_reg[7]_0 [1]),
        .O(speed_old_switch_out10_carry__2_i_8_n_0));
  (* ADDER_THRESHOLD = "35" *) 
  (* METHODOLOGY_DRC_VIOS = "{SYNTH-8 {cell *THIS*}}" *) 
  CARRY8 speed_old_switch_out10_carry__3
       (.CI(speed_old_switch_out10_carry__2_n_0),
        .CI_TOP(1'b0),
        .CO({NLW_speed_old_switch_out10_carry__3_CO_UNCONNECTED[7:5],speed_old_switch_out10_carry__3_n_3,speed_old_switch_out10_carry__3_n_4,speed_old_switch_out10_carry__3_n_5,speed_old_switch_out10_carry__3_n_6,speed_old_switch_out10_carry__3_n_7}),
        .DI({1'b0,1'b0,1'b0,T_count_out1[36:32]}),
        .O({NLW_speed_old_switch_out10_carry__3_O_UNCONNECTED[7:6],speed_old_switch_out10_carry__3_n_10,speed_old_switch_out10_carry__3_n_11,speed_old_switch_out10_carry__3_n_12,speed_old_switch_out10_carry__3_n_13,speed_old_switch_out10_carry__3_n_14,speed_old_switch_out10_carry__3_n_15}),
        .S({1'b0,1'b0,speed_old_switch_out10_carry__3_i_1_n_0,speed_old_switch_out10_carry__3_i_2_n_0,speed_old_switch_out10_carry__3_i_3_n_0,speed_old_switch_out10_carry__3_i_4_n_0,speed_old_switch_out10_carry__3_i_5_n_0,speed_old_switch_out10_carry__3_i_6_n_0}));
  LUT3 #(
    .INIT(8'h59)) 
    speed_old_switch_out10_carry__3_i_1
       (.I0(T_count_out1[37]),
        .I1(\T_count_out1_reg[7]_0 [0]),
        .I2(\T_count_out1_reg[7]_0 [1]),
        .O(speed_old_switch_out10_carry__3_i_1_n_0));
  LUT3 #(
    .INIT(8'h59)) 
    speed_old_switch_out10_carry__3_i_2
       (.I0(T_count_out1[36]),
        .I1(\T_count_out1_reg[7]_0 [0]),
        .I2(\T_count_out1_reg[7]_0 [1]),
        .O(speed_old_switch_out10_carry__3_i_2_n_0));
  LUT3 #(
    .INIT(8'h59)) 
    speed_old_switch_out10_carry__3_i_3
       (.I0(T_count_out1[35]),
        .I1(\T_count_out1_reg[7]_0 [0]),
        .I2(\T_count_out1_reg[7]_0 [1]),
        .O(speed_old_switch_out10_carry__3_i_3_n_0));
  LUT3 #(
    .INIT(8'h59)) 
    speed_old_switch_out10_carry__3_i_4
       (.I0(T_count_out1[34]),
        .I1(\T_count_out1_reg[7]_0 [0]),
        .I2(\T_count_out1_reg[7]_0 [1]),
        .O(speed_old_switch_out10_carry__3_i_4_n_0));
  LUT3 #(
    .INIT(8'h59)) 
    speed_old_switch_out10_carry__3_i_5
       (.I0(T_count_out1[33]),
        .I1(\T_count_out1_reg[7]_0 [0]),
        .I2(\T_count_out1_reg[7]_0 [1]),
        .O(speed_old_switch_out10_carry__3_i_5_n_0));
  LUT3 #(
    .INIT(8'h59)) 
    speed_old_switch_out10_carry__3_i_6
       (.I0(T_count_out1[32]),
        .I1(\T_count_out1_reg[7]_0 [0]),
        .I2(\T_count_out1_reg[7]_0 [1]),
        .O(speed_old_switch_out10_carry__3_i_6_n_0));
  LUT2 #(
    .INIT(4'hB)) 
    speed_old_switch_out10_carry_i_1
       (.I0(\T_count_out1_reg[7]_0 [1]),
        .I1(\T_count_out1_reg[7]_0 [0]),
        .O(speed_old_switch_out10_carry_i_1_n_0));
  LUT4 #(
    .INIT(16'h9969)) 
    speed_old_switch_out10_carry_i_2
       (.I0(T_count_out1[7]),
        .I1(\T_count_out1_reg[31]_0 [7]),
        .I2(\T_count_out1_reg[7]_0 [0]),
        .I3(\T_count_out1_reg[7]_0 [1]),
        .O(speed_old_switch_out10_carry_i_2_n_0));
  LUT4 #(
    .INIT(16'h9969)) 
    speed_old_switch_out10_carry_i_3
       (.I0(T_count_out1[6]),
        .I1(\T_count_out1_reg[31]_0 [6]),
        .I2(\T_count_out1_reg[7]_0 [0]),
        .I3(\T_count_out1_reg[7]_0 [1]),
        .O(speed_old_switch_out10_carry_i_3_n_0));
  LUT4 #(
    .INIT(16'h9969)) 
    speed_old_switch_out10_carry_i_4
       (.I0(T_count_out1[5]),
        .I1(\T_count_out1_reg[31]_0 [5]),
        .I2(\T_count_out1_reg[7]_0 [0]),
        .I3(\T_count_out1_reg[7]_0 [1]),
        .O(speed_old_switch_out10_carry_i_4_n_0));
  LUT4 #(
    .INIT(16'h9969)) 
    speed_old_switch_out10_carry_i_5
       (.I0(T_count_out1[4]),
        .I1(\T_count_out1_reg[31]_0 [4]),
        .I2(\T_count_out1_reg[7]_0 [0]),
        .I3(\T_count_out1_reg[7]_0 [1]),
        .O(speed_old_switch_out10_carry_i_5_n_0));
  LUT4 #(
    .INIT(16'h9969)) 
    speed_old_switch_out10_carry_i_6
       (.I0(T_count_out1[3]),
        .I1(\T_count_out1_reg[31]_0 [3]),
        .I2(\T_count_out1_reg[7]_0 [0]),
        .I3(\T_count_out1_reg[7]_0 [1]),
        .O(speed_old_switch_out10_carry_i_6_n_0));
  LUT4 #(
    .INIT(16'h9969)) 
    speed_old_switch_out10_carry_i_7
       (.I0(T_count_out1[2]),
        .I1(\T_count_out1_reg[31]_0 [2]),
        .I2(\T_count_out1_reg[7]_0 [0]),
        .I3(\T_count_out1_reg[7]_0 [1]),
        .O(speed_old_switch_out10_carry_i_7_n_0));
  LUT4 #(
    .INIT(16'h9969)) 
    speed_old_switch_out10_carry_i_8
       (.I0(T_count_out1[1]),
        .I1(\T_count_out1_reg[31]_0 [1]),
        .I2(\T_count_out1_reg[7]_0 [0]),
        .I3(\T_count_out1_reg[7]_0 [1]),
        .O(speed_old_switch_out10_carry_i_8_n_0));
  LUT4 #(
    .INIT(16'h9969)) 
    speed_old_switch_out10_carry_i_9
       (.I0(T_count_out1[0]),
        .I1(\T_count_out1_reg[31]_0 [0]),
        .I2(\T_count_out1_reg[7]_0 [0]),
        .I3(\T_count_out1_reg[7]_0 [1]),
        .O(speed_old_switch_out10_carry_i_9_n_0));
  LUT2 #(
    .INIT(4'h7)) 
    state_Out_tmp0_carry__0_i_1
       (.I0(Delay7_out_reg[14]),
        .I1(Delay7_ctrl_delay_out),
        .O(state_Out_tmp0_carry__0_i_1_n_0));
  LUT3 #(
    .INIT(8'hB7)) 
    state_Out_tmp0_carry__0_i_10
       (.I0(Delay7_out_reg[12]),
        .I1(Delay7_ctrl_delay_out),
        .I2(Delay7_out_reg[13]),
        .O(state_Out_tmp0_carry__0_i_10_n_0));
  LUT3 #(
    .INIT(8'hB7)) 
    state_Out_tmp0_carry__0_i_11
       (.I0(Delay7_out_reg[11]),
        .I1(Delay7_ctrl_delay_out),
        .I2(Delay7_out_reg[12]),
        .O(state_Out_tmp0_carry__0_i_11_n_0));
  LUT3 #(
    .INIT(8'hB7)) 
    state_Out_tmp0_carry__0_i_12
       (.I0(Delay7_out_reg[10]),
        .I1(Delay7_ctrl_delay_out),
        .I2(Delay7_out_reg[11]),
        .O(state_Out_tmp0_carry__0_i_12_n_0));
  LUT3 #(
    .INIT(8'hB7)) 
    state_Out_tmp0_carry__0_i_13
       (.I0(Delay7_out_reg[9]),
        .I1(Delay7_ctrl_delay_out),
        .I2(Delay7_out_reg[10]),
        .O(state_Out_tmp0_carry__0_i_13_n_0));
  LUT3 #(
    .INIT(8'hB7)) 
    state_Out_tmp0_carry__0_i_14
       (.I0(Delay7_out_reg[8]),
        .I1(Delay7_ctrl_delay_out),
        .I2(Delay7_out_reg[9]),
        .O(state_Out_tmp0_carry__0_i_14_n_0));
  LUT3 #(
    .INIT(8'hB7)) 
    state_Out_tmp0_carry__0_i_15
       (.I0(Delay7_out_reg[7]),
        .I1(Delay7_ctrl_delay_out),
        .I2(Delay7_out_reg[8]),
        .O(state_Out_tmp0_carry__0_i_15_n_0));
  LUT2 #(
    .INIT(4'h7)) 
    state_Out_tmp0_carry__0_i_2
       (.I0(Delay7_out_reg[13]),
        .I1(Delay7_ctrl_delay_out),
        .O(state_Out_tmp0_carry__0_i_2_n_0));
  LUT2 #(
    .INIT(4'h7)) 
    state_Out_tmp0_carry__0_i_3
       (.I0(Delay7_out_reg[12]),
        .I1(Delay7_ctrl_delay_out),
        .O(state_Out_tmp0_carry__0_i_3_n_0));
  LUT2 #(
    .INIT(4'h7)) 
    state_Out_tmp0_carry__0_i_4
       (.I0(Delay7_out_reg[11]),
        .I1(Delay7_ctrl_delay_out),
        .O(state_Out_tmp0_carry__0_i_4_n_0));
  LUT2 #(
    .INIT(4'h7)) 
    state_Out_tmp0_carry__0_i_5
       (.I0(Delay7_out_reg[10]),
        .I1(Delay7_ctrl_delay_out),
        .O(state_Out_tmp0_carry__0_i_5_n_0));
  LUT2 #(
    .INIT(4'h7)) 
    state_Out_tmp0_carry__0_i_6
       (.I0(Delay7_out_reg[9]),
        .I1(Delay7_ctrl_delay_out),
        .O(state_Out_tmp0_carry__0_i_6_n_0));
  LUT2 #(
    .INIT(4'h7)) 
    state_Out_tmp0_carry__0_i_7
       (.I0(Delay7_out_reg[8]),
        .I1(Delay7_ctrl_delay_out),
        .O(state_Out_tmp0_carry__0_i_7_n_0));
  LUT3 #(
    .INIT(8'h9F)) 
    state_Out_tmp0_carry__0_i_8
       (.I0(Delay7_out_reg[14]),
        .I1(Delay7_out_reg[15]),
        .I2(Delay7_ctrl_delay_out),
        .O(state_Out_tmp0_carry__0_i_8_n_0));
  LUT3 #(
    .INIT(8'hB7)) 
    state_Out_tmp0_carry__0_i_9
       (.I0(Delay7_out_reg[13]),
        .I1(Delay7_ctrl_delay_out),
        .I2(Delay7_out_reg[14]),
        .O(state_Out_tmp0_carry__0_i_9_n_0));
  CARRY8 state_prev_carry
       (.CI(1'b0),
        .CI_TOP(1'b0),
        .CO({state_prev_carry_n_0,state_prev_carry_n_1,state_prev_carry_n_2,state_prev_carry_n_3,state_prev_carry_n_4,state_prev_carry_n_5,state_prev_carry_n_6,state_prev_carry_n_7}),
        .DI({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,state_prev_carry_i_1_n_0}),
        .O(state_prev[7:0]),
        .S({state_prev_carry_i_2_n_0,RESIZE[6],state_prev_carry_i_4_n_0,RESIZE[4],state_prev_carry_i_6_n_0,RESIZE[2],state_prev_carry_i_8_n_0,state_prev_carry_i_9_n_0}));
  CARRY8 state_prev_carry__0
       (.CI(state_prev_carry_n_0),
        .CI_TOP(1'b0),
        .CO({NLW_state_prev_carry__0_CO_UNCONNECTED[7:5],state_prev_carry__0_n_3,state_prev_carry__0_n_4,state_prev_carry__0_n_5,state_prev_carry__0_n_6,state_prev_carry__0_n_7}),
        .DI({1'b0,1'b0,1'b0,1'b1,1'b0,1'b0,1'b0,1'b0}),
        .O({NLW_state_prev_carry__0_O_UNCONNECTED[7:6],state_prev[15],state_prev[12:8]}),
        .S({1'b0,1'b0,1'b1,state_prev_carry__0_i_1_n_0,state_prev_carry__0_i_2_n_0,RESIZE[10],state_prev_carry__0_i_4_n_0,RESIZE[8]}));
  LUT2 #(
    .INIT(4'h2)) 
    state_prev_carry__0_i_1
       (.I0(Delay1_out1[12]),
        .I1(\Delay1_out1_reg[15]_0 ),
        .O(state_prev_carry__0_i_1_n_0));
  LUT2 #(
    .INIT(4'h2)) 
    state_prev_carry__0_i_2
       (.I0(Delay1_out1[11]),
        .I1(\Delay1_out1_reg[15]_0 ),
        .O(state_prev_carry__0_i_2_n_0));
  LUT2 #(
    .INIT(4'h2)) 
    state_prev_carry__0_i_3
       (.I0(Delay1_out1[10]),
        .I1(\Delay1_out1_reg[15]_0 ),
        .O(RESIZE[10]));
  LUT2 #(
    .INIT(4'h2)) 
    state_prev_carry__0_i_4
       (.I0(Delay1_out1[9]),
        .I1(\Delay1_out1_reg[15]_0 ),
        .O(state_prev_carry__0_i_4_n_0));
  LUT2 #(
    .INIT(4'h2)) 
    state_prev_carry__0_i_5
       (.I0(Delay1_out1[8]),
        .I1(\Delay1_out1_reg[15]_0 ),
        .O(RESIZE[8]));
  LUT2 #(
    .INIT(4'h2)) 
    state_prev_carry_i_1
       (.I0(count_old1_out1[0]),
        .I1(count_old1_out1[1]),
        .O(state_prev_carry_i_1_n_0));
  LUT2 #(
    .INIT(4'h2)) 
    state_prev_carry_i_2
       (.I0(Delay1_out1[7]),
        .I1(\Delay1_out1_reg[15]_0 ),
        .O(state_prev_carry_i_2_n_0));
  LUT2 #(
    .INIT(4'h2)) 
    state_prev_carry_i_3
       (.I0(Delay1_out1[6]),
        .I1(\Delay1_out1_reg[15]_0 ),
        .O(RESIZE[6]));
  LUT2 #(
    .INIT(4'h2)) 
    state_prev_carry_i_4
       (.I0(Delay1_out1[5]),
        .I1(\Delay1_out1_reg[15]_0 ),
        .O(state_prev_carry_i_4_n_0));
  LUT2 #(
    .INIT(4'h2)) 
    state_prev_carry_i_5
       (.I0(Delay1_out1[4]),
        .I1(\Delay1_out1_reg[15]_0 ),
        .O(RESIZE[4]));
  LUT2 #(
    .INIT(4'h2)) 
    state_prev_carry_i_6
       (.I0(Delay1_out1[3]),
        .I1(\Delay1_out1_reg[15]_0 ),
        .O(state_prev_carry_i_6_n_0));
  LUT2 #(
    .INIT(4'h2)) 
    state_prev_carry_i_7
       (.I0(Delay1_out1[2]),
        .I1(\Delay1_out1_reg[15]_0 ),
        .O(RESIZE[2]));
  LUT2 #(
    .INIT(4'h2)) 
    state_prev_carry_i_8
       (.I0(Delay1_out1[1]),
        .I1(\Delay1_out1_reg[15]_0 ),
        .O(state_prev_carry_i_8_n_0));
  LUT4 #(
    .INIT(16'hBBB4)) 
    state_prev_carry_i_9
       (.I0(count_old1_out1[1]),
        .I1(count_old1_out1[0]),
        .I2(\Delay1_out1_reg[15]_0 ),
        .I3(Delay1_out1[0]),
        .O(state_prev_carry_i_9_n_0));
  zusys_IncreEncoder_V24_ip_0_0_IncreEncoder_V24_ip_src_Count u_Count
       (.D(state_Out_unsigned),
        .DI({state_Out_tmp0_carry__0_i_1_n_0,state_Out_tmp0_carry__0_i_2_n_0,state_Out_tmp0_carry__0_i_3_n_0,state_Out_tmp0_carry__0_i_4_n_0,state_Out_tmp0_carry__0_i_5_n_0,state_Out_tmp0_carry__0_i_6_n_0,state_Out_tmp0_carry__0_i_7_n_0}),
        .Delay3_out1(Delay3_out1),
        .Delay3_out1_reg({u_Count_n_24,u_Count_n_25,u_Count_n_26,u_Count_n_27,u_Count_n_28,u_Count_n_29,u_Count_n_30,u_Count_n_31}),
        .Delay3_out1_reg_0({u_Count_n_32,u_Count_n_33,u_Count_n_34,u_Count_n_35,u_Count_n_36,u_Count_n_37,u_Count_n_38,u_Count_n_39}),
        .Delay6_out1_reg(Delay6_out1_reg),
        .\Delay6_out1_reg[23] (Q),
        .\Delay7_out_reg[15] ({state_Out_tmp0_carry__0_i_8_n_0,state_Out_tmp0_carry__0_i_9_n_0,state_Out_tmp0_carry__0_i_10_n_0,state_Out_tmp0_carry__0_i_11_n_0,state_Out_tmp0_carry__0_i_12_n_0,state_Out_tmp0_carry__0_i_13_n_0,state_Out_tmp0_carry__0_i_14_n_0,state_Out_tmp0_carry__0_i_15_n_0}),
        .\Delay7_out_reg[7] (Delay7_ctrl_delay_out),
        .\Delay7_out_reg[7]_0 (Delay7_out_reg[7:0]),
        .O({u_Count_n_16,u_Count_n_17,u_Count_n_18,u_Count_n_19,u_Count_n_20,u_Count_n_21,u_Count_n_22,u_Count_n_23}),
        .Q(Delay5_out1),
        .S({InternalOmega_Out_tmp0_carry__1_i_1_n_0,InternalOmega_Out_tmp0_carry__1_i_2_n_0,InternalOmega_Out_tmp0_carry__1_i_3_n_0,InternalOmega_Out_tmp0_carry__1_i_4_n_0,InternalOmega_Out_tmp0_carry__1_i_5_n_0,InternalOmega_Out_tmp0_carry__1_i_6_n_0,InternalOmega_Out_tmp0_carry__1_i_7_n_0,InternalOmega_Out_tmp0_carry__1_i_8_n_0}));
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
