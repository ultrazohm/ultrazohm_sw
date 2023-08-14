// Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// --------------------------------------------------------------------------------
// Tool Version: Vivado v.2020.1.1 (win64) Build 2960000 Wed Aug  5 22:57:20 MDT 2020
// Date        : Fri Jan 28 14:47:54 2022
// Host        : enc177112 running 64-bit major release  (build 9200)
// Command     : write_verilog -force -mode funcsim
//               c:/GIT/UltraZohm/software/ultrazohm_sw_develop/vivado/zusys/ip/zusys_PWM_SS_3L_ip_0_0/zusys_PWM_SS_3L_ip_0_0_sim_netlist.v
// Design      : zusys_PWM_SS_3L_ip_0_0
// Purpose     : This verilog netlist is a functional simulation representation of the design and should not be modified
//               or synthesized. This netlist cannot be used for SDF annotated simulation.
// Device      : xczu9eg-ffvc900-1-e
// --------------------------------------------------------------------------------
`timescale 1 ps / 1 ps

(* CHECK_LICENSE_TYPE = "zusys_PWM_SS_3L_ip_0_0,PWM_SS_3L_ip,{}" *) (* downgradeipidentifiedwarnings = "yes" *) (* ip_definition_source = "package_project" *) 
(* x_core_info = "PWM_SS_3L_ip,Vivado 2020.1.1" *) 
(* NotValidForBitStream *)
module zusys_PWM_SS_3L_ip_0_0
   (IPCORE_CLK,
    IPCORE_RESETN,
    m_u1_norm,
    m_u2_norm,
    m_u3_norm,
    SSa1_IN_External,
    SSa2_IN_External,
    SSb1_IN_External,
    SSb2_IN_External,
    SSc1_IN_External,
    SSc2_IN_External,
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
    SSa1_OUT,
    SSa2_OUT,
    SSb1_OUT,
    SSb2_OUT,
    SSc1_OUT,
    SSc2_OUT,
    Period_Center,
    Period_Start,
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
  input [13:0]m_u1_norm;
  input [13:0]m_u2_norm;
  input [13:0]m_u3_norm;
  input SSa1_IN_External;
  input SSa2_IN_External;
  input SSb1_IN_External;
  input SSb2_IN_External;
  input SSc1_IN_External;
  input SSc2_IN_External;
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
  output SSa1_OUT;
  output SSa2_OUT;
  output SSb1_OUT;
  output SSb2_OUT;
  output SSc1_OUT;
  output SSc2_OUT;
  output Period_Center;
  output Period_Start;
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
  wire [29:29]\^AXI4_Lite_RDATA ;
  wire AXI4_Lite_RREADY;
  wire AXI4_Lite_RVALID;
  wire [31:0]AXI4_Lite_WDATA;
  wire AXI4_Lite_WREADY;
  wire [3:0]AXI4_Lite_WSTRB;
  wire AXI4_Lite_WVALID;
  wire IPCORE_CLK;
  wire IPCORE_RESETN;
  wire Period_Center;
  wire Period_Start;
  wire SSa1_IN_External;
  wire SSa1_OUT;
  wire SSa2_IN_External;
  wire SSa2_OUT;
  wire SSb1_IN_External;
  wire SSb1_OUT;
  wire SSb2_IN_External;
  wire SSb2_OUT;
  wire SSc1_IN_External;
  wire SSc1_OUT;
  wire SSc2_IN_External;
  wire SSc2_OUT;
  wire [13:0]m_u1_norm;
  wire [13:0]m_u2_norm;
  wire [13:0]m_u3_norm;

  assign AXI4_Lite_BRESP[1] = \<const0> ;
  assign AXI4_Lite_BRESP[0] = \<const0> ;
  assign AXI4_Lite_RDATA[31] = \<const0> ;
  assign AXI4_Lite_RDATA[30] = \^AXI4_Lite_RDATA [29];
  assign AXI4_Lite_RDATA[29] = \^AXI4_Lite_RDATA [29];
  assign AXI4_Lite_RDATA[28] = \^AXI4_Lite_RDATA [29];
  assign AXI4_Lite_RDATA[27] = \<const0> ;
  assign AXI4_Lite_RDATA[26] = \^AXI4_Lite_RDATA [29];
  assign AXI4_Lite_RDATA[25] = \^AXI4_Lite_RDATA [29];
  assign AXI4_Lite_RDATA[24] = \^AXI4_Lite_RDATA [29];
  assign AXI4_Lite_RDATA[23] = \<const0> ;
  assign AXI4_Lite_RDATA[22] = \^AXI4_Lite_RDATA [29];
  assign AXI4_Lite_RDATA[21] = \^AXI4_Lite_RDATA [29];
  assign AXI4_Lite_RDATA[20] = \^AXI4_Lite_RDATA [29];
  assign AXI4_Lite_RDATA[19] = \<const0> ;
  assign AXI4_Lite_RDATA[18] = \<const0> ;
  assign AXI4_Lite_RDATA[17] = \^AXI4_Lite_RDATA [29];
  assign AXI4_Lite_RDATA[16] = \^AXI4_Lite_RDATA [29];
  assign AXI4_Lite_RDATA[15] = \^AXI4_Lite_RDATA [29];
  assign AXI4_Lite_RDATA[14] = \<const0> ;
  assign AXI4_Lite_RDATA[13] = \<const0> ;
  assign AXI4_Lite_RDATA[12] = \<const0> ;
  assign AXI4_Lite_RDATA[11] = \^AXI4_Lite_RDATA [29];
  assign AXI4_Lite_RDATA[10] = \^AXI4_Lite_RDATA [29];
  assign AXI4_Lite_RDATA[9] = \^AXI4_Lite_RDATA [29];
  assign AXI4_Lite_RDATA[8] = \<const0> ;
  assign AXI4_Lite_RDATA[7] = \<const0> ;
  assign AXI4_Lite_RDATA[6] = \<const0> ;
  assign AXI4_Lite_RDATA[5] = \^AXI4_Lite_RDATA [29];
  assign AXI4_Lite_RDATA[4] = \<const0> ;
  assign AXI4_Lite_RDATA[3] = \<const0> ;
  assign AXI4_Lite_RDATA[2] = \^AXI4_Lite_RDATA [29];
  assign AXI4_Lite_RDATA[1] = \^AXI4_Lite_RDATA [29];
  assign AXI4_Lite_RDATA[0] = \^AXI4_Lite_RDATA [29];
  assign AXI4_Lite_RRESP[1] = \<const0> ;
  assign AXI4_Lite_RRESP[0] = \<const0> ;
  GND GND
       (.G(\<const0> ));
  zusys_PWM_SS_3L_ip_0_0_PWM_SS_3L_ip U0
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
        .AXI4_Lite_WDATA(AXI4_Lite_WDATA[19:0]),
        .AXI4_Lite_WREADY(AXI4_Lite_WREADY),
        .AXI4_Lite_WSTRB(AXI4_Lite_WSTRB),
        .AXI4_Lite_WVALID(AXI4_Lite_WVALID),
        .IPCORE_CLK(IPCORE_CLK),
        .IPCORE_RESETN(IPCORE_RESETN),
        .Period_Center(Period_Center),
        .Period_Start(Period_Start),
        .SSa1_IN_External(SSa1_IN_External),
        .SSa1_OUT(SSa1_OUT),
        .SSa2_IN_External(SSa2_IN_External),
        .SSa2_OUT(SSa2_OUT),
        .SSb1_IN_External(SSb1_IN_External),
        .SSb1_OUT(SSb1_OUT),
        .SSb2_IN_External(SSb2_IN_External),
        .SSb2_OUT(SSb2_OUT),
        .SSc1_IN_External(SSc1_IN_External),
        .SSc1_OUT(SSc1_OUT),
        .SSc2_IN_External(SSc2_IN_External),
        .SSc2_OUT(SSc2_OUT),
        .m_u1_norm(m_u1_norm),
        .m_u2_norm(m_u2_norm),
        .m_u3_norm(m_u3_norm));
endmodule

(* ORIG_REF_NAME = "PWM_SS_3L_ip" *) 
module zusys_PWM_SS_3L_ip_0_0_PWM_SS_3L_ip
   (AXI4_Lite_RVALID,
    AXI4_Lite_BVALID,
    AXI4_Lite_WREADY,
    Period_Center,
    Period_Start,
    AXI4_Lite_ARREADY,
    AXI4_Lite_AWREADY,
    SSa2_OUT,
    SSa1_OUT,
    SSb2_OUT,
    SSb1_OUT,
    SSc2_OUT,
    SSc1_OUT,
    AXI4_Lite_RDATA,
    IPCORE_CLK,
    AXI4_Lite_ARADDR,
    AXI4_Lite_ARVALID,
    AXI4_Lite_ACLK,
    AXI4_Lite_AWADDR,
    AXI4_Lite_WDATA,
    SSc2_IN_External,
    SSc1_IN_External,
    SSb2_IN_External,
    SSb1_IN_External,
    SSa2_IN_External,
    SSa1_IN_External,
    AXI4_Lite_RREADY,
    AXI4_Lite_AWVALID,
    AXI4_Lite_ARESETN,
    IPCORE_RESETN,
    AXI4_Lite_BREADY,
    AXI4_Lite_WVALID,
    AXI4_Lite_WSTRB,
    m_u1_norm,
    m_u2_norm,
    m_u3_norm);
  output AXI4_Lite_RVALID;
  output AXI4_Lite_BVALID;
  output AXI4_Lite_WREADY;
  output Period_Center;
  output Period_Start;
  output AXI4_Lite_ARREADY;
  output AXI4_Lite_AWREADY;
  output SSa2_OUT;
  output SSa1_OUT;
  output SSb2_OUT;
  output SSb1_OUT;
  output SSc2_OUT;
  output SSc1_OUT;
  output [0:0]AXI4_Lite_RDATA;
  input IPCORE_CLK;
  input [13:0]AXI4_Lite_ARADDR;
  input AXI4_Lite_ARVALID;
  input AXI4_Lite_ACLK;
  input [13:0]AXI4_Lite_AWADDR;
  input [19:0]AXI4_Lite_WDATA;
  input SSc2_IN_External;
  input SSc1_IN_External;
  input SSb2_IN_External;
  input SSb1_IN_External;
  input SSa2_IN_External;
  input SSa1_IN_External;
  input AXI4_Lite_RREADY;
  input AXI4_Lite_AWVALID;
  input AXI4_Lite_ARESETN;
  input IPCORE_RESETN;
  input AXI4_Lite_BREADY;
  input AXI4_Lite_WVALID;
  input [3:0]AXI4_Lite_WSTRB;
  input [13:0]m_u1_norm;
  input [13:0]m_u2_norm;
  input [13:0]m_u3_norm;

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
  wire [19:0]AXI4_Lite_WDATA;
  wire AXI4_Lite_WREADY;
  wire [3:0]AXI4_Lite_WSTRB;
  wire AXI4_Lite_WVALID;
  wire IPCORE_CLK;
  wire IPCORE_RESETN;
  wire [1:0]Mode_AXI;
  wire Period_Center;
  wire Period_Start;
  wire SSa1_IN_External;
  wire SSa1_OUT;
  wire SSa2_IN_External;
  wire SSa2_OUT;
  wire SSb1_IN_External;
  wire SSb1_OUT;
  wire SSb2_IN_External;
  wire SSb2_OUT;
  wire SSc1_IN_External;
  wire SSc1_OUT;
  wire SSc2_IN_External;
  wire SSc2_OUT;
  wire [1:0]TriState_HB1_AXI;
  wire [1:0]TriState_HB2_AXI;
  wire [1:0]TriState_HB3_AXI;
  wire [13:0]m_u1_norm;
  wire [13:0]m_u1_norm_AXI;
  wire [13:0]m_u2_norm;
  wire [13:0]m_u2_norm_AXI;
  wire [13:0]m_u3_norm;
  wire [13:0]m_u3_norm_AXI;
  wire reset;
  wire reset_in;
  wire u_PWM_SS_3L_ip_axi_lite_inst_n_5;
  wire \u_PWM_SS_3L_ip_axi_lite_module_inst/soft_reset ;
  wire u_PWM_SS_3L_ip_dut_inst_n_0;
  wire u_PWM_SS_3L_ip_reset_sync_inst_n_1;
  wire [19:0]write_PWM_counter_max_value_int_AXI;
  wire write_PWM_en_AXI;
  wire [13:0]write_PWM_min_pulse_width_0to1_AXI;
  wire write_axi_enable;

  zusys_PWM_SS_3L_ip_0_0_PWM_SS_3L_ip_axi_lite u_PWM_SS_3L_ip_axi_lite_inst
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
        .CEP(write_axi_enable),
        .FSM_sequential_axi_lite_rstate_reg(AXI4_Lite_RVALID),
        .\HDL_Counter2_count_reg[19] (u_PWM_SS_3L_ip_dut_inst_n_0),
        .IPCORE_RESETN(IPCORE_RESETN),
        .Q({AXI4_Lite_BVALID,AXI4_Lite_WREADY}),
        .RSTP(reset),
        .\data_reg_Mode_AXI_1_1_reg[1] (Mode_AXI),
        .\data_reg_PWM_counter_max_value_int_AXI_1_1_reg[19] (write_PWM_counter_max_value_int_AXI),
        .\data_reg_PWM_min_pulse_width_0to1_AXI_1_1_reg[13] (write_PWM_min_pulse_width_0to1_AXI),
        .\data_reg_TriState_HB1_AXI_1_1_reg[1] (TriState_HB1_AXI),
        .\data_reg_TriState_HB2_AXI_1_1_reg[1] (TriState_HB2_AXI),
        .\data_reg_TriState_HB3_AXI_1_1_reg[1] (TriState_HB3_AXI),
        .data_reg_axi_enable_1_1_reg(u_PWM_SS_3L_ip_axi_lite_inst_n_5),
        .\data_reg_m_u1_norm_AXI_1_1_reg[13] (m_u1_norm_AXI),
        .\data_reg_m_u2_norm_AXI_1_1_reg[13] (m_u2_norm_AXI),
        .\data_reg_m_u3_norm_AXI_1_1_reg[13] (m_u3_norm_AXI),
        .reset_in(reset_in),
        .soft_reset(\u_PWM_SS_3L_ip_axi_lite_module_inst/soft_reset ),
        .write_PWM_en_AXI(write_PWM_en_AXI));
  zusys_PWM_SS_3L_ip_0_0_PWM_SS_3L_ip_dut u_PWM_SS_3L_ip_dut_inst
       (.CEP(write_axi_enable),
        .D(write_PWM_counter_max_value_int_AXI),
        .\HDL_Counter2_count_reg[19] (u_PWM_SS_3L_ip_axi_lite_inst_n_5),
        .IPCORE_CLK(IPCORE_CLK),
        .PWM_en_AXI_2_reg(u_PWM_SS_3L_ip_dut_inst_n_0),
        .Period_Center(Period_Center),
        .Period_Start(Period_Start),
        .RSTP(reset),
        .SSa1_IN_External(SSa1_IN_External),
        .SSa1_OUT(SSa1_OUT),
        .SSa2_IN_External(SSa2_IN_External),
        .SSa2_OUT(SSa2_OUT),
        .SSb1_IN_External(SSb1_IN_External),
        .SSb1_OUT(SSb1_OUT),
        .SSb2_IN_External(SSb2_IN_External),
        .SSb2_OUT(SSb2_OUT),
        .SSc1_IN_External(SSc1_IN_External),
        .SSc1_OUT(SSc1_OUT),
        .SSc2_IN_External(SSc2_IN_External),
        .SSc2_OUT(SSc2_OUT),
        .\delayMatch1_reg_reg[0][13] (m_u1_norm_AXI),
        .\delayMatch2_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2 (TriState_HB1_AXI),
        .\delayMatch3_reg_reg[0][13] (m_u2_norm_AXI),
        .\delayMatch5_reg_reg[0][13] (m_u3_norm_AXI),
        .\delayMatch5_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2 (TriState_HB2_AXI),
        .\delayMatch8_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2 (TriState_HB3_AXI),
        .m_u1_norm(m_u1_norm),
        .m_u2_norm(m_u2_norm),
        .m_u3_norm(m_u3_norm),
        .\maximum_counter_value_1_reg[8] (u_PWM_SS_3L_ip_reset_sync_inst_n_1),
        .\min_pulse_width_AXI_1_reg[13] (write_PWM_min_pulse_width_0to1_AXI),
        .\reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2 (Mode_AXI),
        .write_PWM_en_AXI(write_PWM_en_AXI));
  zusys_PWM_SS_3L_ip_0_0_PWM_SS_3L_ip_reset_sync u_PWM_SS_3L_ip_reset_sync_inst
       (.AXI4_Lite_ARESETN(AXI4_Lite_ARESETN),
        .CEP(write_axi_enable),
        .IPCORE_CLK(IPCORE_CLK),
        .IPCORE_RESETN(IPCORE_RESETN),
        .RSTP(reset),
        .reset_in(reset_in),
        .reset_out_reg_0(u_PWM_SS_3L_ip_reset_sync_inst_n_1),
        .soft_reset(\u_PWM_SS_3L_ip_axi_lite_module_inst/soft_reset ));
endmodule

(* ORIG_REF_NAME = "PWM_SS_3L_ip_addr_decoder" *) 
module zusys_PWM_SS_3L_ip_0_0_PWM_SS_3L_ip_addr_decoder
   (read_reg_ip_timestamp,
    CEP,
    write_PWM_en_AXI,
    data_reg_axi_enable_1_1_reg_0,
    \data_reg_PWM_counter_max_value_int_AXI_1_1_reg[19]_0 ,
    \data_reg_PWM_min_pulse_width_0to1_AXI_1_1_reg[13]_0 ,
    \data_reg_Mode_AXI_1_1_reg[1]_0 ,
    \data_reg_TriState_HB1_AXI_1_1_reg[1]_0 ,
    \data_reg_TriState_HB2_AXI_1_1_reg[1]_0 ,
    \data_reg_TriState_HB3_AXI_1_1_reg[1]_0 ,
    \data_reg_m_u1_norm_AXI_1_1_reg[13]_0 ,
    \data_reg_m_u2_norm_AXI_1_1_reg[13]_0 ,
    \data_reg_m_u3_norm_AXI_1_1_reg[13]_0 ,
    RSTP,
    AXI4_Lite_ACLK,
    data_reg_axi_enable_1_1_reg_1,
    data_reg_PWM_en_AXI_1_1_reg_0,
    \HDL_Counter2_count_reg[19] ,
    E,
    Q,
    \data_reg_PWM_min_pulse_width_0to1_AXI_1_1_reg[13]_1 ,
    \data_reg_Mode_AXI_1_1_reg[1]_1 ,
    \data_reg_TriState_HB1_AXI_1_1_reg[1]_1 ,
    \data_reg_TriState_HB2_AXI_1_1_reg[1]_1 ,
    \data_reg_TriState_HB3_AXI_1_1_reg[1]_1 ,
    \data_reg_m_u1_norm_AXI_1_1_reg[13]_1 ,
    \data_reg_m_u2_norm_AXI_1_1_reg[13]_1 ,
    \data_reg_m_u3_norm_AXI_1_1_reg[13]_1 );
  output [0:0]read_reg_ip_timestamp;
  output CEP;
  output write_PWM_en_AXI;
  output data_reg_axi_enable_1_1_reg_0;
  output [19:0]\data_reg_PWM_counter_max_value_int_AXI_1_1_reg[19]_0 ;
  output [13:0]\data_reg_PWM_min_pulse_width_0to1_AXI_1_1_reg[13]_0 ;
  output [1:0]\data_reg_Mode_AXI_1_1_reg[1]_0 ;
  output [1:0]\data_reg_TriState_HB1_AXI_1_1_reg[1]_0 ;
  output [1:0]\data_reg_TriState_HB2_AXI_1_1_reg[1]_0 ;
  output [1:0]\data_reg_TriState_HB3_AXI_1_1_reg[1]_0 ;
  output [13:0]\data_reg_m_u1_norm_AXI_1_1_reg[13]_0 ;
  output [13:0]\data_reg_m_u2_norm_AXI_1_1_reg[13]_0 ;
  output [13:0]\data_reg_m_u3_norm_AXI_1_1_reg[13]_0 ;
  input RSTP;
  input AXI4_Lite_ACLK;
  input data_reg_axi_enable_1_1_reg_1;
  input data_reg_PWM_en_AXI_1_1_reg_0;
  input \HDL_Counter2_count_reg[19] ;
  input [0:0]E;
  input [19:0]Q;
  input [0:0]\data_reg_PWM_min_pulse_width_0to1_AXI_1_1_reg[13]_1 ;
  input [0:0]\data_reg_Mode_AXI_1_1_reg[1]_1 ;
  input [0:0]\data_reg_TriState_HB1_AXI_1_1_reg[1]_1 ;
  input [0:0]\data_reg_TriState_HB2_AXI_1_1_reg[1]_1 ;
  input [0:0]\data_reg_TriState_HB3_AXI_1_1_reg[1]_1 ;
  input [0:0]\data_reg_m_u1_norm_AXI_1_1_reg[13]_1 ;
  input [0:0]\data_reg_m_u2_norm_AXI_1_1_reg[13]_1 ;
  input [0:0]\data_reg_m_u3_norm_AXI_1_1_reg[13]_1 ;

  wire AXI4_Lite_ACLK;
  wire CEP;
  wire [0:0]E;
  wire \HDL_Counter2_count_reg[19] ;
  wire [19:0]Q;
  wire RSTP;
  wire [1:0]\data_reg_Mode_AXI_1_1_reg[1]_0 ;
  wire [0:0]\data_reg_Mode_AXI_1_1_reg[1]_1 ;
  wire [19:0]\data_reg_PWM_counter_max_value_int_AXI_1_1_reg[19]_0 ;
  wire data_reg_PWM_en_AXI_1_1_reg_0;
  wire [13:0]\data_reg_PWM_min_pulse_width_0to1_AXI_1_1_reg[13]_0 ;
  wire [0:0]\data_reg_PWM_min_pulse_width_0to1_AXI_1_1_reg[13]_1 ;
  wire [1:0]\data_reg_TriState_HB1_AXI_1_1_reg[1]_0 ;
  wire [0:0]\data_reg_TriState_HB1_AXI_1_1_reg[1]_1 ;
  wire [1:0]\data_reg_TriState_HB2_AXI_1_1_reg[1]_0 ;
  wire [0:0]\data_reg_TriState_HB2_AXI_1_1_reg[1]_1 ;
  wire [1:0]\data_reg_TriState_HB3_AXI_1_1_reg[1]_0 ;
  wire [0:0]\data_reg_TriState_HB3_AXI_1_1_reg[1]_1 ;
  wire data_reg_axi_enable_1_1_reg_0;
  wire data_reg_axi_enable_1_1_reg_1;
  wire [13:0]\data_reg_m_u1_norm_AXI_1_1_reg[13]_0 ;
  wire [0:0]\data_reg_m_u1_norm_AXI_1_1_reg[13]_1 ;
  wire [13:0]\data_reg_m_u2_norm_AXI_1_1_reg[13]_0 ;
  wire [0:0]\data_reg_m_u2_norm_AXI_1_1_reg[13]_1 ;
  wire [13:0]\data_reg_m_u3_norm_AXI_1_1_reg[13]_0 ;
  wire [0:0]\data_reg_m_u3_norm_AXI_1_1_reg[13]_1 ;
  wire [0:0]read_reg_ip_timestamp;
  wire write_PWM_en_AXI;

  LUT2 #(
    .INIT(4'h8)) 
    \HDL_Counter2_count[0]_i_1 
       (.I0(CEP),
        .I1(\HDL_Counter2_count_reg[19] ),
        .O(data_reg_axi_enable_1_1_reg_0));
  FDRE \data_reg_Mode_AXI_1_1_reg[0] 
       (.C(AXI4_Lite_ACLK),
        .CE(\data_reg_Mode_AXI_1_1_reg[1]_1 ),
        .D(Q[0]),
        .Q(\data_reg_Mode_AXI_1_1_reg[1]_0 [0]),
        .R(RSTP));
  FDRE \data_reg_Mode_AXI_1_1_reg[1] 
       (.C(AXI4_Lite_ACLK),
        .CE(\data_reg_Mode_AXI_1_1_reg[1]_1 ),
        .D(Q[1]),
        .Q(\data_reg_Mode_AXI_1_1_reg[1]_0 [1]),
        .R(RSTP));
  FDRE \data_reg_PWM_counter_max_value_int_AXI_1_1_reg[0] 
       (.C(AXI4_Lite_ACLK),
        .CE(E),
        .D(Q[0]),
        .Q(\data_reg_PWM_counter_max_value_int_AXI_1_1_reg[19]_0 [0]),
        .R(RSTP));
  FDRE \data_reg_PWM_counter_max_value_int_AXI_1_1_reg[10] 
       (.C(AXI4_Lite_ACLK),
        .CE(E),
        .D(Q[10]),
        .Q(\data_reg_PWM_counter_max_value_int_AXI_1_1_reg[19]_0 [10]),
        .R(RSTP));
  FDRE \data_reg_PWM_counter_max_value_int_AXI_1_1_reg[11] 
       (.C(AXI4_Lite_ACLK),
        .CE(E),
        .D(Q[11]),
        .Q(\data_reg_PWM_counter_max_value_int_AXI_1_1_reg[19]_0 [11]),
        .R(RSTP));
  FDRE \data_reg_PWM_counter_max_value_int_AXI_1_1_reg[12] 
       (.C(AXI4_Lite_ACLK),
        .CE(E),
        .D(Q[12]),
        .Q(\data_reg_PWM_counter_max_value_int_AXI_1_1_reg[19]_0 [12]),
        .R(RSTP));
  FDRE \data_reg_PWM_counter_max_value_int_AXI_1_1_reg[13] 
       (.C(AXI4_Lite_ACLK),
        .CE(E),
        .D(Q[13]),
        .Q(\data_reg_PWM_counter_max_value_int_AXI_1_1_reg[19]_0 [13]),
        .R(RSTP));
  FDRE \data_reg_PWM_counter_max_value_int_AXI_1_1_reg[14] 
       (.C(AXI4_Lite_ACLK),
        .CE(E),
        .D(Q[14]),
        .Q(\data_reg_PWM_counter_max_value_int_AXI_1_1_reg[19]_0 [14]),
        .R(RSTP));
  FDRE \data_reg_PWM_counter_max_value_int_AXI_1_1_reg[15] 
       (.C(AXI4_Lite_ACLK),
        .CE(E),
        .D(Q[15]),
        .Q(\data_reg_PWM_counter_max_value_int_AXI_1_1_reg[19]_0 [15]),
        .R(RSTP));
  FDRE \data_reg_PWM_counter_max_value_int_AXI_1_1_reg[16] 
       (.C(AXI4_Lite_ACLK),
        .CE(E),
        .D(Q[16]),
        .Q(\data_reg_PWM_counter_max_value_int_AXI_1_1_reg[19]_0 [16]),
        .R(RSTP));
  FDRE \data_reg_PWM_counter_max_value_int_AXI_1_1_reg[17] 
       (.C(AXI4_Lite_ACLK),
        .CE(E),
        .D(Q[17]),
        .Q(\data_reg_PWM_counter_max_value_int_AXI_1_1_reg[19]_0 [17]),
        .R(RSTP));
  FDRE \data_reg_PWM_counter_max_value_int_AXI_1_1_reg[18] 
       (.C(AXI4_Lite_ACLK),
        .CE(E),
        .D(Q[18]),
        .Q(\data_reg_PWM_counter_max_value_int_AXI_1_1_reg[19]_0 [18]),
        .R(RSTP));
  FDRE \data_reg_PWM_counter_max_value_int_AXI_1_1_reg[19] 
       (.C(AXI4_Lite_ACLK),
        .CE(E),
        .D(Q[19]),
        .Q(\data_reg_PWM_counter_max_value_int_AXI_1_1_reg[19]_0 [19]),
        .R(RSTP));
  FDRE \data_reg_PWM_counter_max_value_int_AXI_1_1_reg[1] 
       (.C(AXI4_Lite_ACLK),
        .CE(E),
        .D(Q[1]),
        .Q(\data_reg_PWM_counter_max_value_int_AXI_1_1_reg[19]_0 [1]),
        .R(RSTP));
  FDRE \data_reg_PWM_counter_max_value_int_AXI_1_1_reg[2] 
       (.C(AXI4_Lite_ACLK),
        .CE(E),
        .D(Q[2]),
        .Q(\data_reg_PWM_counter_max_value_int_AXI_1_1_reg[19]_0 [2]),
        .R(RSTP));
  FDRE \data_reg_PWM_counter_max_value_int_AXI_1_1_reg[3] 
       (.C(AXI4_Lite_ACLK),
        .CE(E),
        .D(Q[3]),
        .Q(\data_reg_PWM_counter_max_value_int_AXI_1_1_reg[19]_0 [3]),
        .R(RSTP));
  FDRE \data_reg_PWM_counter_max_value_int_AXI_1_1_reg[4] 
       (.C(AXI4_Lite_ACLK),
        .CE(E),
        .D(Q[4]),
        .Q(\data_reg_PWM_counter_max_value_int_AXI_1_1_reg[19]_0 [4]),
        .R(RSTP));
  FDRE \data_reg_PWM_counter_max_value_int_AXI_1_1_reg[5] 
       (.C(AXI4_Lite_ACLK),
        .CE(E),
        .D(Q[5]),
        .Q(\data_reg_PWM_counter_max_value_int_AXI_1_1_reg[19]_0 [5]),
        .R(RSTP));
  FDRE \data_reg_PWM_counter_max_value_int_AXI_1_1_reg[6] 
       (.C(AXI4_Lite_ACLK),
        .CE(E),
        .D(Q[6]),
        .Q(\data_reg_PWM_counter_max_value_int_AXI_1_1_reg[19]_0 [6]),
        .R(RSTP));
  FDRE \data_reg_PWM_counter_max_value_int_AXI_1_1_reg[7] 
       (.C(AXI4_Lite_ACLK),
        .CE(E),
        .D(Q[7]),
        .Q(\data_reg_PWM_counter_max_value_int_AXI_1_1_reg[19]_0 [7]),
        .R(RSTP));
  FDRE \data_reg_PWM_counter_max_value_int_AXI_1_1_reg[8] 
       (.C(AXI4_Lite_ACLK),
        .CE(E),
        .D(Q[8]),
        .Q(\data_reg_PWM_counter_max_value_int_AXI_1_1_reg[19]_0 [8]),
        .R(RSTP));
  FDRE \data_reg_PWM_counter_max_value_int_AXI_1_1_reg[9] 
       (.C(AXI4_Lite_ACLK),
        .CE(E),
        .D(Q[9]),
        .Q(\data_reg_PWM_counter_max_value_int_AXI_1_1_reg[19]_0 [9]),
        .R(RSTP));
  FDRE data_reg_PWM_en_AXI_1_1_reg
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(data_reg_PWM_en_AXI_1_1_reg_0),
        .Q(write_PWM_en_AXI),
        .R(RSTP));
  FDRE \data_reg_PWM_min_pulse_width_0to1_AXI_1_1_reg[0] 
       (.C(AXI4_Lite_ACLK),
        .CE(\data_reg_PWM_min_pulse_width_0to1_AXI_1_1_reg[13]_1 ),
        .D(Q[0]),
        .Q(\data_reg_PWM_min_pulse_width_0to1_AXI_1_1_reg[13]_0 [0]),
        .R(RSTP));
  FDRE \data_reg_PWM_min_pulse_width_0to1_AXI_1_1_reg[10] 
       (.C(AXI4_Lite_ACLK),
        .CE(\data_reg_PWM_min_pulse_width_0to1_AXI_1_1_reg[13]_1 ),
        .D(Q[10]),
        .Q(\data_reg_PWM_min_pulse_width_0to1_AXI_1_1_reg[13]_0 [10]),
        .R(RSTP));
  FDRE \data_reg_PWM_min_pulse_width_0to1_AXI_1_1_reg[11] 
       (.C(AXI4_Lite_ACLK),
        .CE(\data_reg_PWM_min_pulse_width_0to1_AXI_1_1_reg[13]_1 ),
        .D(Q[11]),
        .Q(\data_reg_PWM_min_pulse_width_0to1_AXI_1_1_reg[13]_0 [11]),
        .R(RSTP));
  FDRE \data_reg_PWM_min_pulse_width_0to1_AXI_1_1_reg[12] 
       (.C(AXI4_Lite_ACLK),
        .CE(\data_reg_PWM_min_pulse_width_0to1_AXI_1_1_reg[13]_1 ),
        .D(Q[12]),
        .Q(\data_reg_PWM_min_pulse_width_0to1_AXI_1_1_reg[13]_0 [12]),
        .R(RSTP));
  FDRE \data_reg_PWM_min_pulse_width_0to1_AXI_1_1_reg[13] 
       (.C(AXI4_Lite_ACLK),
        .CE(\data_reg_PWM_min_pulse_width_0to1_AXI_1_1_reg[13]_1 ),
        .D(Q[13]),
        .Q(\data_reg_PWM_min_pulse_width_0to1_AXI_1_1_reg[13]_0 [13]),
        .R(RSTP));
  FDRE \data_reg_PWM_min_pulse_width_0to1_AXI_1_1_reg[1] 
       (.C(AXI4_Lite_ACLK),
        .CE(\data_reg_PWM_min_pulse_width_0to1_AXI_1_1_reg[13]_1 ),
        .D(Q[1]),
        .Q(\data_reg_PWM_min_pulse_width_0to1_AXI_1_1_reg[13]_0 [1]),
        .R(RSTP));
  FDRE \data_reg_PWM_min_pulse_width_0to1_AXI_1_1_reg[2] 
       (.C(AXI4_Lite_ACLK),
        .CE(\data_reg_PWM_min_pulse_width_0to1_AXI_1_1_reg[13]_1 ),
        .D(Q[2]),
        .Q(\data_reg_PWM_min_pulse_width_0to1_AXI_1_1_reg[13]_0 [2]),
        .R(RSTP));
  FDRE \data_reg_PWM_min_pulse_width_0to1_AXI_1_1_reg[3] 
       (.C(AXI4_Lite_ACLK),
        .CE(\data_reg_PWM_min_pulse_width_0to1_AXI_1_1_reg[13]_1 ),
        .D(Q[3]),
        .Q(\data_reg_PWM_min_pulse_width_0to1_AXI_1_1_reg[13]_0 [3]),
        .R(RSTP));
  FDRE \data_reg_PWM_min_pulse_width_0to1_AXI_1_1_reg[4] 
       (.C(AXI4_Lite_ACLK),
        .CE(\data_reg_PWM_min_pulse_width_0to1_AXI_1_1_reg[13]_1 ),
        .D(Q[4]),
        .Q(\data_reg_PWM_min_pulse_width_0to1_AXI_1_1_reg[13]_0 [4]),
        .R(RSTP));
  FDRE \data_reg_PWM_min_pulse_width_0to1_AXI_1_1_reg[5] 
       (.C(AXI4_Lite_ACLK),
        .CE(\data_reg_PWM_min_pulse_width_0to1_AXI_1_1_reg[13]_1 ),
        .D(Q[5]),
        .Q(\data_reg_PWM_min_pulse_width_0to1_AXI_1_1_reg[13]_0 [5]),
        .R(RSTP));
  FDRE \data_reg_PWM_min_pulse_width_0to1_AXI_1_1_reg[6] 
       (.C(AXI4_Lite_ACLK),
        .CE(\data_reg_PWM_min_pulse_width_0to1_AXI_1_1_reg[13]_1 ),
        .D(Q[6]),
        .Q(\data_reg_PWM_min_pulse_width_0to1_AXI_1_1_reg[13]_0 [6]),
        .R(RSTP));
  FDRE \data_reg_PWM_min_pulse_width_0to1_AXI_1_1_reg[7] 
       (.C(AXI4_Lite_ACLK),
        .CE(\data_reg_PWM_min_pulse_width_0to1_AXI_1_1_reg[13]_1 ),
        .D(Q[7]),
        .Q(\data_reg_PWM_min_pulse_width_0to1_AXI_1_1_reg[13]_0 [7]),
        .R(RSTP));
  FDRE \data_reg_PWM_min_pulse_width_0to1_AXI_1_1_reg[8] 
       (.C(AXI4_Lite_ACLK),
        .CE(\data_reg_PWM_min_pulse_width_0to1_AXI_1_1_reg[13]_1 ),
        .D(Q[8]),
        .Q(\data_reg_PWM_min_pulse_width_0to1_AXI_1_1_reg[13]_0 [8]),
        .R(RSTP));
  FDRE \data_reg_PWM_min_pulse_width_0to1_AXI_1_1_reg[9] 
       (.C(AXI4_Lite_ACLK),
        .CE(\data_reg_PWM_min_pulse_width_0to1_AXI_1_1_reg[13]_1 ),
        .D(Q[9]),
        .Q(\data_reg_PWM_min_pulse_width_0to1_AXI_1_1_reg[13]_0 [9]),
        .R(RSTP));
  FDRE \data_reg_TriState_HB1_AXI_1_1_reg[0] 
       (.C(AXI4_Lite_ACLK),
        .CE(\data_reg_TriState_HB1_AXI_1_1_reg[1]_1 ),
        .D(Q[0]),
        .Q(\data_reg_TriState_HB1_AXI_1_1_reg[1]_0 [0]),
        .R(RSTP));
  FDRE \data_reg_TriState_HB1_AXI_1_1_reg[1] 
       (.C(AXI4_Lite_ACLK),
        .CE(\data_reg_TriState_HB1_AXI_1_1_reg[1]_1 ),
        .D(Q[1]),
        .Q(\data_reg_TriState_HB1_AXI_1_1_reg[1]_0 [1]),
        .R(RSTP));
  FDRE \data_reg_TriState_HB2_AXI_1_1_reg[0] 
       (.C(AXI4_Lite_ACLK),
        .CE(\data_reg_TriState_HB2_AXI_1_1_reg[1]_1 ),
        .D(Q[0]),
        .Q(\data_reg_TriState_HB2_AXI_1_1_reg[1]_0 [0]),
        .R(RSTP));
  FDRE \data_reg_TriState_HB2_AXI_1_1_reg[1] 
       (.C(AXI4_Lite_ACLK),
        .CE(\data_reg_TriState_HB2_AXI_1_1_reg[1]_1 ),
        .D(Q[1]),
        .Q(\data_reg_TriState_HB2_AXI_1_1_reg[1]_0 [1]),
        .R(RSTP));
  FDRE \data_reg_TriState_HB3_AXI_1_1_reg[0] 
       (.C(AXI4_Lite_ACLK),
        .CE(\data_reg_TriState_HB3_AXI_1_1_reg[1]_1 ),
        .D(Q[0]),
        .Q(\data_reg_TriState_HB3_AXI_1_1_reg[1]_0 [0]),
        .R(RSTP));
  FDRE \data_reg_TriState_HB3_AXI_1_1_reg[1] 
       (.C(AXI4_Lite_ACLK),
        .CE(\data_reg_TriState_HB3_AXI_1_1_reg[1]_1 ),
        .D(Q[1]),
        .Q(\data_reg_TriState_HB3_AXI_1_1_reg[1]_0 [1]),
        .R(RSTP));
  FDSE data_reg_axi_enable_1_1_reg
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(data_reg_axi_enable_1_1_reg_1),
        .Q(CEP),
        .S(RSTP));
  FDRE \data_reg_m_u1_norm_AXI_1_1_reg[0] 
       (.C(AXI4_Lite_ACLK),
        .CE(\data_reg_m_u1_norm_AXI_1_1_reg[13]_1 ),
        .D(Q[0]),
        .Q(\data_reg_m_u1_norm_AXI_1_1_reg[13]_0 [0]),
        .R(RSTP));
  FDRE \data_reg_m_u1_norm_AXI_1_1_reg[10] 
       (.C(AXI4_Lite_ACLK),
        .CE(\data_reg_m_u1_norm_AXI_1_1_reg[13]_1 ),
        .D(Q[10]),
        .Q(\data_reg_m_u1_norm_AXI_1_1_reg[13]_0 [10]),
        .R(RSTP));
  FDRE \data_reg_m_u1_norm_AXI_1_1_reg[11] 
       (.C(AXI4_Lite_ACLK),
        .CE(\data_reg_m_u1_norm_AXI_1_1_reg[13]_1 ),
        .D(Q[11]),
        .Q(\data_reg_m_u1_norm_AXI_1_1_reg[13]_0 [11]),
        .R(RSTP));
  FDRE \data_reg_m_u1_norm_AXI_1_1_reg[12] 
       (.C(AXI4_Lite_ACLK),
        .CE(\data_reg_m_u1_norm_AXI_1_1_reg[13]_1 ),
        .D(Q[12]),
        .Q(\data_reg_m_u1_norm_AXI_1_1_reg[13]_0 [12]),
        .R(RSTP));
  FDRE \data_reg_m_u1_norm_AXI_1_1_reg[13] 
       (.C(AXI4_Lite_ACLK),
        .CE(\data_reg_m_u1_norm_AXI_1_1_reg[13]_1 ),
        .D(Q[13]),
        .Q(\data_reg_m_u1_norm_AXI_1_1_reg[13]_0 [13]),
        .R(RSTP));
  FDRE \data_reg_m_u1_norm_AXI_1_1_reg[1] 
       (.C(AXI4_Lite_ACLK),
        .CE(\data_reg_m_u1_norm_AXI_1_1_reg[13]_1 ),
        .D(Q[1]),
        .Q(\data_reg_m_u1_norm_AXI_1_1_reg[13]_0 [1]),
        .R(RSTP));
  FDRE \data_reg_m_u1_norm_AXI_1_1_reg[2] 
       (.C(AXI4_Lite_ACLK),
        .CE(\data_reg_m_u1_norm_AXI_1_1_reg[13]_1 ),
        .D(Q[2]),
        .Q(\data_reg_m_u1_norm_AXI_1_1_reg[13]_0 [2]),
        .R(RSTP));
  FDRE \data_reg_m_u1_norm_AXI_1_1_reg[3] 
       (.C(AXI4_Lite_ACLK),
        .CE(\data_reg_m_u1_norm_AXI_1_1_reg[13]_1 ),
        .D(Q[3]),
        .Q(\data_reg_m_u1_norm_AXI_1_1_reg[13]_0 [3]),
        .R(RSTP));
  FDRE \data_reg_m_u1_norm_AXI_1_1_reg[4] 
       (.C(AXI4_Lite_ACLK),
        .CE(\data_reg_m_u1_norm_AXI_1_1_reg[13]_1 ),
        .D(Q[4]),
        .Q(\data_reg_m_u1_norm_AXI_1_1_reg[13]_0 [4]),
        .R(RSTP));
  FDRE \data_reg_m_u1_norm_AXI_1_1_reg[5] 
       (.C(AXI4_Lite_ACLK),
        .CE(\data_reg_m_u1_norm_AXI_1_1_reg[13]_1 ),
        .D(Q[5]),
        .Q(\data_reg_m_u1_norm_AXI_1_1_reg[13]_0 [5]),
        .R(RSTP));
  FDRE \data_reg_m_u1_norm_AXI_1_1_reg[6] 
       (.C(AXI4_Lite_ACLK),
        .CE(\data_reg_m_u1_norm_AXI_1_1_reg[13]_1 ),
        .D(Q[6]),
        .Q(\data_reg_m_u1_norm_AXI_1_1_reg[13]_0 [6]),
        .R(RSTP));
  FDRE \data_reg_m_u1_norm_AXI_1_1_reg[7] 
       (.C(AXI4_Lite_ACLK),
        .CE(\data_reg_m_u1_norm_AXI_1_1_reg[13]_1 ),
        .D(Q[7]),
        .Q(\data_reg_m_u1_norm_AXI_1_1_reg[13]_0 [7]),
        .R(RSTP));
  FDRE \data_reg_m_u1_norm_AXI_1_1_reg[8] 
       (.C(AXI4_Lite_ACLK),
        .CE(\data_reg_m_u1_norm_AXI_1_1_reg[13]_1 ),
        .D(Q[8]),
        .Q(\data_reg_m_u1_norm_AXI_1_1_reg[13]_0 [8]),
        .R(RSTP));
  FDRE \data_reg_m_u1_norm_AXI_1_1_reg[9] 
       (.C(AXI4_Lite_ACLK),
        .CE(\data_reg_m_u1_norm_AXI_1_1_reg[13]_1 ),
        .D(Q[9]),
        .Q(\data_reg_m_u1_norm_AXI_1_1_reg[13]_0 [9]),
        .R(RSTP));
  FDRE \data_reg_m_u2_norm_AXI_1_1_reg[0] 
       (.C(AXI4_Lite_ACLK),
        .CE(\data_reg_m_u2_norm_AXI_1_1_reg[13]_1 ),
        .D(Q[0]),
        .Q(\data_reg_m_u2_norm_AXI_1_1_reg[13]_0 [0]),
        .R(RSTP));
  FDRE \data_reg_m_u2_norm_AXI_1_1_reg[10] 
       (.C(AXI4_Lite_ACLK),
        .CE(\data_reg_m_u2_norm_AXI_1_1_reg[13]_1 ),
        .D(Q[10]),
        .Q(\data_reg_m_u2_norm_AXI_1_1_reg[13]_0 [10]),
        .R(RSTP));
  FDRE \data_reg_m_u2_norm_AXI_1_1_reg[11] 
       (.C(AXI4_Lite_ACLK),
        .CE(\data_reg_m_u2_norm_AXI_1_1_reg[13]_1 ),
        .D(Q[11]),
        .Q(\data_reg_m_u2_norm_AXI_1_1_reg[13]_0 [11]),
        .R(RSTP));
  FDRE \data_reg_m_u2_norm_AXI_1_1_reg[12] 
       (.C(AXI4_Lite_ACLK),
        .CE(\data_reg_m_u2_norm_AXI_1_1_reg[13]_1 ),
        .D(Q[12]),
        .Q(\data_reg_m_u2_norm_AXI_1_1_reg[13]_0 [12]),
        .R(RSTP));
  FDRE \data_reg_m_u2_norm_AXI_1_1_reg[13] 
       (.C(AXI4_Lite_ACLK),
        .CE(\data_reg_m_u2_norm_AXI_1_1_reg[13]_1 ),
        .D(Q[13]),
        .Q(\data_reg_m_u2_norm_AXI_1_1_reg[13]_0 [13]),
        .R(RSTP));
  FDRE \data_reg_m_u2_norm_AXI_1_1_reg[1] 
       (.C(AXI4_Lite_ACLK),
        .CE(\data_reg_m_u2_norm_AXI_1_1_reg[13]_1 ),
        .D(Q[1]),
        .Q(\data_reg_m_u2_norm_AXI_1_1_reg[13]_0 [1]),
        .R(RSTP));
  FDRE \data_reg_m_u2_norm_AXI_1_1_reg[2] 
       (.C(AXI4_Lite_ACLK),
        .CE(\data_reg_m_u2_norm_AXI_1_1_reg[13]_1 ),
        .D(Q[2]),
        .Q(\data_reg_m_u2_norm_AXI_1_1_reg[13]_0 [2]),
        .R(RSTP));
  FDRE \data_reg_m_u2_norm_AXI_1_1_reg[3] 
       (.C(AXI4_Lite_ACLK),
        .CE(\data_reg_m_u2_norm_AXI_1_1_reg[13]_1 ),
        .D(Q[3]),
        .Q(\data_reg_m_u2_norm_AXI_1_1_reg[13]_0 [3]),
        .R(RSTP));
  FDRE \data_reg_m_u2_norm_AXI_1_1_reg[4] 
       (.C(AXI4_Lite_ACLK),
        .CE(\data_reg_m_u2_norm_AXI_1_1_reg[13]_1 ),
        .D(Q[4]),
        .Q(\data_reg_m_u2_norm_AXI_1_1_reg[13]_0 [4]),
        .R(RSTP));
  FDRE \data_reg_m_u2_norm_AXI_1_1_reg[5] 
       (.C(AXI4_Lite_ACLK),
        .CE(\data_reg_m_u2_norm_AXI_1_1_reg[13]_1 ),
        .D(Q[5]),
        .Q(\data_reg_m_u2_norm_AXI_1_1_reg[13]_0 [5]),
        .R(RSTP));
  FDRE \data_reg_m_u2_norm_AXI_1_1_reg[6] 
       (.C(AXI4_Lite_ACLK),
        .CE(\data_reg_m_u2_norm_AXI_1_1_reg[13]_1 ),
        .D(Q[6]),
        .Q(\data_reg_m_u2_norm_AXI_1_1_reg[13]_0 [6]),
        .R(RSTP));
  FDRE \data_reg_m_u2_norm_AXI_1_1_reg[7] 
       (.C(AXI4_Lite_ACLK),
        .CE(\data_reg_m_u2_norm_AXI_1_1_reg[13]_1 ),
        .D(Q[7]),
        .Q(\data_reg_m_u2_norm_AXI_1_1_reg[13]_0 [7]),
        .R(RSTP));
  FDRE \data_reg_m_u2_norm_AXI_1_1_reg[8] 
       (.C(AXI4_Lite_ACLK),
        .CE(\data_reg_m_u2_norm_AXI_1_1_reg[13]_1 ),
        .D(Q[8]),
        .Q(\data_reg_m_u2_norm_AXI_1_1_reg[13]_0 [8]),
        .R(RSTP));
  FDRE \data_reg_m_u2_norm_AXI_1_1_reg[9] 
       (.C(AXI4_Lite_ACLK),
        .CE(\data_reg_m_u2_norm_AXI_1_1_reg[13]_1 ),
        .D(Q[9]),
        .Q(\data_reg_m_u2_norm_AXI_1_1_reg[13]_0 [9]),
        .R(RSTP));
  FDRE \data_reg_m_u3_norm_AXI_1_1_reg[0] 
       (.C(AXI4_Lite_ACLK),
        .CE(\data_reg_m_u3_norm_AXI_1_1_reg[13]_1 ),
        .D(Q[0]),
        .Q(\data_reg_m_u3_norm_AXI_1_1_reg[13]_0 [0]),
        .R(RSTP));
  FDRE \data_reg_m_u3_norm_AXI_1_1_reg[10] 
       (.C(AXI4_Lite_ACLK),
        .CE(\data_reg_m_u3_norm_AXI_1_1_reg[13]_1 ),
        .D(Q[10]),
        .Q(\data_reg_m_u3_norm_AXI_1_1_reg[13]_0 [10]),
        .R(RSTP));
  FDRE \data_reg_m_u3_norm_AXI_1_1_reg[11] 
       (.C(AXI4_Lite_ACLK),
        .CE(\data_reg_m_u3_norm_AXI_1_1_reg[13]_1 ),
        .D(Q[11]),
        .Q(\data_reg_m_u3_norm_AXI_1_1_reg[13]_0 [11]),
        .R(RSTP));
  FDRE \data_reg_m_u3_norm_AXI_1_1_reg[12] 
       (.C(AXI4_Lite_ACLK),
        .CE(\data_reg_m_u3_norm_AXI_1_1_reg[13]_1 ),
        .D(Q[12]),
        .Q(\data_reg_m_u3_norm_AXI_1_1_reg[13]_0 [12]),
        .R(RSTP));
  FDRE \data_reg_m_u3_norm_AXI_1_1_reg[13] 
       (.C(AXI4_Lite_ACLK),
        .CE(\data_reg_m_u3_norm_AXI_1_1_reg[13]_1 ),
        .D(Q[13]),
        .Q(\data_reg_m_u3_norm_AXI_1_1_reg[13]_0 [13]),
        .R(RSTP));
  FDRE \data_reg_m_u3_norm_AXI_1_1_reg[1] 
       (.C(AXI4_Lite_ACLK),
        .CE(\data_reg_m_u3_norm_AXI_1_1_reg[13]_1 ),
        .D(Q[1]),
        .Q(\data_reg_m_u3_norm_AXI_1_1_reg[13]_0 [1]),
        .R(RSTP));
  FDRE \data_reg_m_u3_norm_AXI_1_1_reg[2] 
       (.C(AXI4_Lite_ACLK),
        .CE(\data_reg_m_u3_norm_AXI_1_1_reg[13]_1 ),
        .D(Q[2]),
        .Q(\data_reg_m_u3_norm_AXI_1_1_reg[13]_0 [2]),
        .R(RSTP));
  FDRE \data_reg_m_u3_norm_AXI_1_1_reg[3] 
       (.C(AXI4_Lite_ACLK),
        .CE(\data_reg_m_u3_norm_AXI_1_1_reg[13]_1 ),
        .D(Q[3]),
        .Q(\data_reg_m_u3_norm_AXI_1_1_reg[13]_0 [3]),
        .R(RSTP));
  FDRE \data_reg_m_u3_norm_AXI_1_1_reg[4] 
       (.C(AXI4_Lite_ACLK),
        .CE(\data_reg_m_u3_norm_AXI_1_1_reg[13]_1 ),
        .D(Q[4]),
        .Q(\data_reg_m_u3_norm_AXI_1_1_reg[13]_0 [4]),
        .R(RSTP));
  FDRE \data_reg_m_u3_norm_AXI_1_1_reg[5] 
       (.C(AXI4_Lite_ACLK),
        .CE(\data_reg_m_u3_norm_AXI_1_1_reg[13]_1 ),
        .D(Q[5]),
        .Q(\data_reg_m_u3_norm_AXI_1_1_reg[13]_0 [5]),
        .R(RSTP));
  FDRE \data_reg_m_u3_norm_AXI_1_1_reg[6] 
       (.C(AXI4_Lite_ACLK),
        .CE(\data_reg_m_u3_norm_AXI_1_1_reg[13]_1 ),
        .D(Q[6]),
        .Q(\data_reg_m_u3_norm_AXI_1_1_reg[13]_0 [6]),
        .R(RSTP));
  FDRE \data_reg_m_u3_norm_AXI_1_1_reg[7] 
       (.C(AXI4_Lite_ACLK),
        .CE(\data_reg_m_u3_norm_AXI_1_1_reg[13]_1 ),
        .D(Q[7]),
        .Q(\data_reg_m_u3_norm_AXI_1_1_reg[13]_0 [7]),
        .R(RSTP));
  FDRE \data_reg_m_u3_norm_AXI_1_1_reg[8] 
       (.C(AXI4_Lite_ACLK),
        .CE(\data_reg_m_u3_norm_AXI_1_1_reg[13]_1 ),
        .D(Q[8]),
        .Q(\data_reg_m_u3_norm_AXI_1_1_reg[13]_0 [8]),
        .R(RSTP));
  FDRE \data_reg_m_u3_norm_AXI_1_1_reg[9] 
       (.C(AXI4_Lite_ACLK),
        .CE(\data_reg_m_u3_norm_AXI_1_1_reg[13]_1 ),
        .D(Q[9]),
        .Q(\data_reg_m_u3_norm_AXI_1_1_reg[13]_0 [9]),
        .R(RSTP));
  FDRE \read_reg_ip_timestamp_reg[30] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(1'b1),
        .Q(read_reg_ip_timestamp),
        .R(RSTP));
endmodule

(* ORIG_REF_NAME = "PWM_SS_3L_ip_axi_lite" *) 
module zusys_PWM_SS_3L_ip_0_0_PWM_SS_3L_ip_axi_lite
   (FSM_sequential_axi_lite_rstate_reg,
    CEP,
    write_PWM_en_AXI,
    AXI4_Lite_RDATA,
    soft_reset,
    data_reg_axi_enable_1_1_reg,
    AXI4_Lite_ARREADY,
    AXI4_Lite_AWREADY,
    reset_in,
    Q,
    \data_reg_PWM_counter_max_value_int_AXI_1_1_reg[19] ,
    \data_reg_PWM_min_pulse_width_0to1_AXI_1_1_reg[13] ,
    \data_reg_Mode_AXI_1_1_reg[1] ,
    \data_reg_TriState_HB1_AXI_1_1_reg[1] ,
    \data_reg_TriState_HB2_AXI_1_1_reg[1] ,
    \data_reg_TriState_HB3_AXI_1_1_reg[1] ,
    \data_reg_m_u1_norm_AXI_1_1_reg[13] ,
    \data_reg_m_u2_norm_AXI_1_1_reg[13] ,
    \data_reg_m_u3_norm_AXI_1_1_reg[13] ,
    AXI4_Lite_ACLK,
    RSTP,
    AXI4_Lite_ARADDR,
    AXI4_Lite_ARVALID,
    \HDL_Counter2_count_reg[19] ,
    AXI4_Lite_RREADY,
    AXI4_Lite_AWVALID,
    AXI4_Lite_ARESETN,
    IPCORE_RESETN,
    AXI4_Lite_BREADY,
    AXI4_Lite_WVALID,
    AXI4_Lite_WSTRB,
    AXI4_Lite_AWADDR,
    AXI4_Lite_WDATA);
  output FSM_sequential_axi_lite_rstate_reg;
  output CEP;
  output write_PWM_en_AXI;
  output [0:0]AXI4_Lite_RDATA;
  output soft_reset;
  output data_reg_axi_enable_1_1_reg;
  output AXI4_Lite_ARREADY;
  output AXI4_Lite_AWREADY;
  output reset_in;
  output [1:0]Q;
  output [19:0]\data_reg_PWM_counter_max_value_int_AXI_1_1_reg[19] ;
  output [13:0]\data_reg_PWM_min_pulse_width_0to1_AXI_1_1_reg[13] ;
  output [1:0]\data_reg_Mode_AXI_1_1_reg[1] ;
  output [1:0]\data_reg_TriState_HB1_AXI_1_1_reg[1] ;
  output [1:0]\data_reg_TriState_HB2_AXI_1_1_reg[1] ;
  output [1:0]\data_reg_TriState_HB3_AXI_1_1_reg[1] ;
  output [13:0]\data_reg_m_u1_norm_AXI_1_1_reg[13] ;
  output [13:0]\data_reg_m_u2_norm_AXI_1_1_reg[13] ;
  output [13:0]\data_reg_m_u3_norm_AXI_1_1_reg[13] ;
  input AXI4_Lite_ACLK;
  input RSTP;
  input [13:0]AXI4_Lite_ARADDR;
  input AXI4_Lite_ARVALID;
  input \HDL_Counter2_count_reg[19] ;
  input AXI4_Lite_RREADY;
  input AXI4_Lite_AWVALID;
  input AXI4_Lite_ARESETN;
  input IPCORE_RESETN;
  input AXI4_Lite_BREADY;
  input AXI4_Lite_WVALID;
  input [3:0]AXI4_Lite_WSTRB;
  input [13:0]AXI4_Lite_AWADDR;
  input [19:0]AXI4_Lite_WDATA;

  wire AXI4_Lite_ACLK;
  wire [13:0]AXI4_Lite_ARADDR;
  wire AXI4_Lite_ARESETN;
  wire AXI4_Lite_ARREADY;
  wire AXI4_Lite_ARVALID;
  wire [13:0]AXI4_Lite_AWADDR;
  wire AXI4_Lite_AWREADY;
  wire AXI4_Lite_AWVALID;
  wire AXI4_Lite_BREADY;
  wire [0:0]AXI4_Lite_RDATA;
  wire AXI4_Lite_RREADY;
  wire [19:0]AXI4_Lite_WDATA;
  wire [3:0]AXI4_Lite_WSTRB;
  wire AXI4_Lite_WVALID;
  wire CEP;
  wire FSM_sequential_axi_lite_rstate_reg;
  wire \HDL_Counter2_count_reg[19] ;
  wire IPCORE_RESETN;
  wire [1:0]Q;
  wire RSTP;
  wire [1:0]\data_reg_Mode_AXI_1_1_reg[1] ;
  wire [19:0]\data_reg_PWM_counter_max_value_int_AXI_1_1_reg[19] ;
  wire [13:0]\data_reg_PWM_min_pulse_width_0to1_AXI_1_1_reg[13] ;
  wire [1:0]\data_reg_TriState_HB1_AXI_1_1_reg[1] ;
  wire [1:0]\data_reg_TriState_HB2_AXI_1_1_reg[1] ;
  wire [1:0]\data_reg_TriState_HB3_AXI_1_1_reg[1] ;
  wire data_reg_axi_enable_1_1_reg;
  wire [13:0]\data_reg_m_u1_norm_AXI_1_1_reg[13] ;
  wire [13:0]\data_reg_m_u2_norm_AXI_1_1_reg[13] ;
  wire [13:0]\data_reg_m_u3_norm_AXI_1_1_reg[13] ;
  wire [30:30]read_reg_ip_timestamp;
  wire reg_enb_Mode_AXI_1_1;
  wire reg_enb_PWM_counter_max_value_int_AXI_1_1;
  wire reg_enb_PWM_min_pulse_width_0to1_AXI_1_1;
  wire reg_enb_TriState_HB1_AXI_1_1;
  wire reg_enb_TriState_HB2_AXI_1_1;
  wire reg_enb_TriState_HB3_AXI_1_1;
  wire reg_enb_m_u1_norm_AXI_1_1;
  wire reg_enb_m_u2_norm_AXI_1_1;
  wire reg_enb_m_u3_norm_AXI_1_1;
  wire reset_in;
  wire soft_reset;
  wire u_PWM_SS_3L_ip_axi_lite_module_inst_n_15;
  wire u_PWM_SS_3L_ip_axi_lite_module_inst_n_16;
  wire u_PWM_SS_3L_ip_axi_lite_module_inst_n_17;
  wire u_PWM_SS_3L_ip_axi_lite_module_inst_n_18;
  wire u_PWM_SS_3L_ip_axi_lite_module_inst_n_19;
  wire u_PWM_SS_3L_ip_axi_lite_module_inst_n_20;
  wire u_PWM_SS_3L_ip_axi_lite_module_inst_n_21;
  wire u_PWM_SS_3L_ip_axi_lite_module_inst_n_22;
  wire u_PWM_SS_3L_ip_axi_lite_module_inst_n_23;
  wire u_PWM_SS_3L_ip_axi_lite_module_inst_n_24;
  wire u_PWM_SS_3L_ip_axi_lite_module_inst_n_25;
  wire u_PWM_SS_3L_ip_axi_lite_module_inst_n_26;
  wire u_PWM_SS_3L_ip_axi_lite_module_inst_n_27;
  wire u_PWM_SS_3L_ip_axi_lite_module_inst_n_28;
  wire u_PWM_SS_3L_ip_axi_lite_module_inst_n_29;
  wire u_PWM_SS_3L_ip_axi_lite_module_inst_n_30;
  wire u_PWM_SS_3L_ip_axi_lite_module_inst_n_31;
  wire u_PWM_SS_3L_ip_axi_lite_module_inst_n_32;
  wire u_PWM_SS_3L_ip_axi_lite_module_inst_n_33;
  wire u_PWM_SS_3L_ip_axi_lite_module_inst_n_34;
  wire u_PWM_SS_3L_ip_axi_lite_module_inst_n_37;
  wire u_PWM_SS_3L_ip_axi_lite_module_inst_n_38;
  wire write_PWM_en_AXI;

  zusys_PWM_SS_3L_ip_0_0_PWM_SS_3L_ip_addr_decoder u_PWM_SS_3L_ip_addr_decoder_inst
       (.AXI4_Lite_ACLK(AXI4_Lite_ACLK),
        .CEP(CEP),
        .E(reg_enb_PWM_counter_max_value_int_AXI_1_1),
        .\HDL_Counter2_count_reg[19] (\HDL_Counter2_count_reg[19] ),
        .Q({u_PWM_SS_3L_ip_axi_lite_module_inst_n_15,u_PWM_SS_3L_ip_axi_lite_module_inst_n_16,u_PWM_SS_3L_ip_axi_lite_module_inst_n_17,u_PWM_SS_3L_ip_axi_lite_module_inst_n_18,u_PWM_SS_3L_ip_axi_lite_module_inst_n_19,u_PWM_SS_3L_ip_axi_lite_module_inst_n_20,u_PWM_SS_3L_ip_axi_lite_module_inst_n_21,u_PWM_SS_3L_ip_axi_lite_module_inst_n_22,u_PWM_SS_3L_ip_axi_lite_module_inst_n_23,u_PWM_SS_3L_ip_axi_lite_module_inst_n_24,u_PWM_SS_3L_ip_axi_lite_module_inst_n_25,u_PWM_SS_3L_ip_axi_lite_module_inst_n_26,u_PWM_SS_3L_ip_axi_lite_module_inst_n_27,u_PWM_SS_3L_ip_axi_lite_module_inst_n_28,u_PWM_SS_3L_ip_axi_lite_module_inst_n_29,u_PWM_SS_3L_ip_axi_lite_module_inst_n_30,u_PWM_SS_3L_ip_axi_lite_module_inst_n_31,u_PWM_SS_3L_ip_axi_lite_module_inst_n_32,u_PWM_SS_3L_ip_axi_lite_module_inst_n_33,u_PWM_SS_3L_ip_axi_lite_module_inst_n_34}),
        .RSTP(RSTP),
        .\data_reg_Mode_AXI_1_1_reg[1]_0 (\data_reg_Mode_AXI_1_1_reg[1] ),
        .\data_reg_Mode_AXI_1_1_reg[1]_1 (reg_enb_Mode_AXI_1_1),
        .\data_reg_PWM_counter_max_value_int_AXI_1_1_reg[19]_0 (\data_reg_PWM_counter_max_value_int_AXI_1_1_reg[19] ),
        .data_reg_PWM_en_AXI_1_1_reg_0(u_PWM_SS_3L_ip_axi_lite_module_inst_n_38),
        .\data_reg_PWM_min_pulse_width_0to1_AXI_1_1_reg[13]_0 (\data_reg_PWM_min_pulse_width_0to1_AXI_1_1_reg[13] ),
        .\data_reg_PWM_min_pulse_width_0to1_AXI_1_1_reg[13]_1 (reg_enb_PWM_min_pulse_width_0to1_AXI_1_1),
        .\data_reg_TriState_HB1_AXI_1_1_reg[1]_0 (\data_reg_TriState_HB1_AXI_1_1_reg[1] ),
        .\data_reg_TriState_HB1_AXI_1_1_reg[1]_1 (reg_enb_TriState_HB1_AXI_1_1),
        .\data_reg_TriState_HB2_AXI_1_1_reg[1]_0 (\data_reg_TriState_HB2_AXI_1_1_reg[1] ),
        .\data_reg_TriState_HB2_AXI_1_1_reg[1]_1 (reg_enb_TriState_HB2_AXI_1_1),
        .\data_reg_TriState_HB3_AXI_1_1_reg[1]_0 (\data_reg_TriState_HB3_AXI_1_1_reg[1] ),
        .\data_reg_TriState_HB3_AXI_1_1_reg[1]_1 (reg_enb_TriState_HB3_AXI_1_1),
        .data_reg_axi_enable_1_1_reg_0(data_reg_axi_enable_1_1_reg),
        .data_reg_axi_enable_1_1_reg_1(u_PWM_SS_3L_ip_axi_lite_module_inst_n_37),
        .\data_reg_m_u1_norm_AXI_1_1_reg[13]_0 (\data_reg_m_u1_norm_AXI_1_1_reg[13] ),
        .\data_reg_m_u1_norm_AXI_1_1_reg[13]_1 (reg_enb_m_u1_norm_AXI_1_1),
        .\data_reg_m_u2_norm_AXI_1_1_reg[13]_0 (\data_reg_m_u2_norm_AXI_1_1_reg[13] ),
        .\data_reg_m_u2_norm_AXI_1_1_reg[13]_1 (reg_enb_m_u2_norm_AXI_1_1),
        .\data_reg_m_u3_norm_AXI_1_1_reg[13]_0 (\data_reg_m_u3_norm_AXI_1_1_reg[13] ),
        .\data_reg_m_u3_norm_AXI_1_1_reg[13]_1 (reg_enb_m_u3_norm_AXI_1_1),
        .read_reg_ip_timestamp(read_reg_ip_timestamp),
        .write_PWM_en_AXI(write_PWM_en_AXI));
  zusys_PWM_SS_3L_ip_0_0_PWM_SS_3L_ip_axi_lite_module u_PWM_SS_3L_ip_axi_lite_module_inst
       (.AXI4_Lite_ACLK(AXI4_Lite_ACLK),
        .AXI4_Lite_ARADDR(AXI4_Lite_ARADDR),
        .\AXI4_Lite_ARADDR[3] (reg_enb_m_u3_norm_AXI_1_1),
        .\AXI4_Lite_ARADDR[3]_0 (reg_enb_m_u2_norm_AXI_1_1),
        .\AXI4_Lite_ARADDR[3]_1 (reg_enb_m_u1_norm_AXI_1_1),
        .\AXI4_Lite_ARADDR[3]_2 (reg_enb_PWM_min_pulse_width_0to1_AXI_1_1),
        .\AXI4_Lite_ARADDR[3]_3 (reg_enb_TriState_HB3_AXI_1_1),
        .\AXI4_Lite_ARADDR[6] (reg_enb_TriState_HB1_AXI_1_1),
        .\AXI4_Lite_ARADDR[6]_0 (reg_enb_TriState_HB2_AXI_1_1),
        .\AXI4_Lite_ARADDR[6]_1 (reg_enb_Mode_AXI_1_1),
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
        .CEP(CEP),
        .E(reg_enb_PWM_counter_max_value_int_AXI_1_1),
        .\FSM_onehot_axi_lite_wstate_reg[2]_0 (Q),
        .FSM_sequential_axi_lite_rstate_reg_0(FSM_sequential_axi_lite_rstate_reg),
        .IPCORE_RESETN(IPCORE_RESETN),
        .Q({u_PWM_SS_3L_ip_axi_lite_module_inst_n_15,u_PWM_SS_3L_ip_axi_lite_module_inst_n_16,u_PWM_SS_3L_ip_axi_lite_module_inst_n_17,u_PWM_SS_3L_ip_axi_lite_module_inst_n_18,u_PWM_SS_3L_ip_axi_lite_module_inst_n_19,u_PWM_SS_3L_ip_axi_lite_module_inst_n_20,u_PWM_SS_3L_ip_axi_lite_module_inst_n_21,u_PWM_SS_3L_ip_axi_lite_module_inst_n_22,u_PWM_SS_3L_ip_axi_lite_module_inst_n_23,u_PWM_SS_3L_ip_axi_lite_module_inst_n_24,u_PWM_SS_3L_ip_axi_lite_module_inst_n_25,u_PWM_SS_3L_ip_axi_lite_module_inst_n_26,u_PWM_SS_3L_ip_axi_lite_module_inst_n_27,u_PWM_SS_3L_ip_axi_lite_module_inst_n_28,u_PWM_SS_3L_ip_axi_lite_module_inst_n_29,u_PWM_SS_3L_ip_axi_lite_module_inst_n_30,u_PWM_SS_3L_ip_axi_lite_module_inst_n_31,u_PWM_SS_3L_ip_axi_lite_module_inst_n_32,u_PWM_SS_3L_ip_axi_lite_module_inst_n_33,u_PWM_SS_3L_ip_axi_lite_module_inst_n_34}),
        .read_reg_ip_timestamp(read_reg_ip_timestamp),
        .reset_in(reset_in),
        .soft_reset(soft_reset),
        .\wdata_reg[0]_0 (u_PWM_SS_3L_ip_axi_lite_module_inst_n_37),
        .\wdata_reg[0]_1 (u_PWM_SS_3L_ip_axi_lite_module_inst_n_38),
        .write_PWM_en_AXI(write_PWM_en_AXI));
endmodule

(* ORIG_REF_NAME = "PWM_SS_3L_ip_axi_lite_module" *) 
module zusys_PWM_SS_3L_ip_0_0_PWM_SS_3L_ip_axi_lite_module
   (FSM_sequential_axi_lite_rstate_reg_0,
    AXI4_Lite_RDATA,
    soft_reset,
    \AXI4_Lite_ARADDR[3] ,
    \AXI4_Lite_ARADDR[3]_0 ,
    \AXI4_Lite_ARADDR[3]_1 ,
    \AXI4_Lite_ARADDR[3]_2 ,
    \AXI4_Lite_ARADDR[3]_3 ,
    E,
    \AXI4_Lite_ARADDR[6] ,
    \AXI4_Lite_ARADDR[6]_0 ,
    \AXI4_Lite_ARADDR[6]_1 ,
    AXI4_Lite_ARREADY,
    AXI4_Lite_AWREADY,
    reset_in,
    Q,
    \FSM_onehot_axi_lite_wstate_reg[2]_0 ,
    \wdata_reg[0]_0 ,
    \wdata_reg[0]_1 ,
    AXI4_Lite_ACLK,
    AXI4_Lite_ARADDR,
    AXI4_Lite_ARVALID,
    read_reg_ip_timestamp,
    AXI4_Lite_RREADY,
    AXI4_Lite_AWVALID,
    AXI4_Lite_ARESETN,
    IPCORE_RESETN,
    AXI4_Lite_BREADY,
    AXI4_Lite_WVALID,
    AXI4_Lite_WSTRB,
    CEP,
    write_PWM_en_AXI,
    AXI4_Lite_AWADDR,
    AXI4_Lite_WDATA);
  output FSM_sequential_axi_lite_rstate_reg_0;
  output [0:0]AXI4_Lite_RDATA;
  output soft_reset;
  output [0:0]\AXI4_Lite_ARADDR[3] ;
  output [0:0]\AXI4_Lite_ARADDR[3]_0 ;
  output [0:0]\AXI4_Lite_ARADDR[3]_1 ;
  output [0:0]\AXI4_Lite_ARADDR[3]_2 ;
  output [0:0]\AXI4_Lite_ARADDR[3]_3 ;
  output [0:0]E;
  output [0:0]\AXI4_Lite_ARADDR[6] ;
  output [0:0]\AXI4_Lite_ARADDR[6]_0 ;
  output [0:0]\AXI4_Lite_ARADDR[6]_1 ;
  output AXI4_Lite_ARREADY;
  output AXI4_Lite_AWREADY;
  output reset_in;
  output [19:0]Q;
  output [1:0]\FSM_onehot_axi_lite_wstate_reg[2]_0 ;
  output \wdata_reg[0]_0 ;
  output \wdata_reg[0]_1 ;
  input AXI4_Lite_ACLK;
  input [13:0]AXI4_Lite_ARADDR;
  input AXI4_Lite_ARVALID;
  input [0:0]read_reg_ip_timestamp;
  input AXI4_Lite_RREADY;
  input AXI4_Lite_AWVALID;
  input AXI4_Lite_ARESETN;
  input IPCORE_RESETN;
  input AXI4_Lite_BREADY;
  input AXI4_Lite_WVALID;
  input [3:0]AXI4_Lite_WSTRB;
  input CEP;
  input write_PWM_en_AXI;
  input [13:0]AXI4_Lite_AWADDR;
  input [19:0]AXI4_Lite_WDATA;

  wire AXI4_Lite_ACLK;
  wire [13:0]AXI4_Lite_ARADDR;
  wire [0:0]\AXI4_Lite_ARADDR[3] ;
  wire [0:0]\AXI4_Lite_ARADDR[3]_0 ;
  wire [0:0]\AXI4_Lite_ARADDR[3]_1 ;
  wire [0:0]\AXI4_Lite_ARADDR[3]_2 ;
  wire [0:0]\AXI4_Lite_ARADDR[3]_3 ;
  wire [0:0]\AXI4_Lite_ARADDR[6] ;
  wire [0:0]\AXI4_Lite_ARADDR[6]_0 ;
  wire [0:0]\AXI4_Lite_ARADDR[6]_1 ;
  wire AXI4_Lite_ARESETN;
  wire AXI4_Lite_ARREADY;
  wire AXI4_Lite_ARVALID;
  wire [13:0]AXI4_Lite_AWADDR;
  wire AXI4_Lite_AWREADY;
  wire AXI4_Lite_AWVALID;
  wire AXI4_Lite_BREADY;
  wire [0:0]AXI4_Lite_RDATA;
  wire \AXI4_Lite_RDATA_tmp[30]_i_1_n_0 ;
  wire \AXI4_Lite_RDATA_tmp[30]_i_2_n_0 ;
  wire \AXI4_Lite_RDATA_tmp[30]_i_3_n_0 ;
  wire \AXI4_Lite_RDATA_tmp[30]_i_4_n_0 ;
  wire \AXI4_Lite_RDATA_tmp[30]_i_5_n_0 ;
  wire \AXI4_Lite_RDATA_tmp[30]_i_6_n_0 ;
  wire AXI4_Lite_RREADY;
  wire [19:0]AXI4_Lite_WDATA;
  wire [3:0]AXI4_Lite_WSTRB;
  wire AXI4_Lite_WVALID;
  wire CEP;
  wire [0:0]E;
  wire [1:0]\FSM_onehot_axi_lite_wstate_reg[2]_0 ;
  wire \FSM_onehot_axi_lite_wstate_reg_n_0_[0] ;
  wire FSM_sequential_axi_lite_rstate_reg_0;
  wire IPCORE_RESETN;
  wire [19:0]Q;
  wire aw_transfer;
  wire axi_lite_rstate_next;
  wire [2:0]axi_lite_wstate_next;
  wire \data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_10_n_0 ;
  wire \data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_11_n_0 ;
  wire \data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_2_n_0 ;
  wire \data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_3_n_0 ;
  wire \data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_4_n_0 ;
  wire \data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_5_n_0 ;
  wire \data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_6_n_0 ;
  wire \data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_7_n_0 ;
  wire \data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_8_n_0 ;
  wire \data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_9_n_0 ;
  wire data_reg_PWM_en_AXI_1_1_i_2_n_0;
  wire data_reg_PWM_en_AXI_1_1_i_3_n_0;
  wire data_reg_PWM_en_AXI_1_1_i_4_n_0;
  wire data_reg_axi_enable_1_1_i_2_n_0;
  wire data_reg_axi_enable_1_1_i_3_n_0;
  wire data_reg_axi_enable_1_1_i_4_n_0;
  wire [0:0]read_reg_ip_timestamp;
  wire reset;
  wire reset_in;
  wire [13:0]sel0;
  wire soft_reset;
  wire soft_reset_i_1_n_0;
  wire soft_reset_i_2_n_0;
  wire soft_reset_i_3_n_0;
  wire soft_reset_i_4_n_0;
  wire soft_reset_i_5_n_0;
  wire top_wr_enb;
  wire w_transfer;
  wire w_transfer_and_wstrb;
  wire \wdata_reg[0]_0 ;
  wire \wdata_reg[0]_1 ;
  wire write_PWM_en_AXI;

  (* SOFT_HLUTNM = "soft_lutpair7" *) 
  LUT3 #(
    .INIT(8'h04)) 
    AXI4_Lite_ARREADY_INST_0
       (.I0(FSM_sequential_axi_lite_rstate_reg_0),
        .I1(\FSM_onehot_axi_lite_wstate_reg_n_0_[0] ),
        .I2(AXI4_Lite_AWVALID),
        .O(AXI4_Lite_ARREADY));
  (* SOFT_HLUTNM = "soft_lutpair8" *) 
  LUT2 #(
    .INIT(4'h2)) 
    AXI4_Lite_AWREADY_INST_0
       (.I0(\FSM_onehot_axi_lite_wstate_reg_n_0_[0] ),
        .I1(FSM_sequential_axi_lite_rstate_reg_0),
        .O(AXI4_Lite_AWREADY));
  LUT6 #(
    .INIT(64'h10FFFFFF10000000)) 
    \AXI4_Lite_RDATA_tmp[30]_i_1 
       (.I0(\AXI4_Lite_RDATA_tmp[30]_i_2_n_0 ),
        .I1(\AXI4_Lite_RDATA_tmp[30]_i_3_n_0 ),
        .I2(\AXI4_Lite_RDATA_tmp[30]_i_4_n_0 ),
        .I3(AXI4_Lite_ARVALID),
        .I4(AXI4_Lite_ARREADY),
        .I5(AXI4_Lite_RDATA),
        .O(\AXI4_Lite_RDATA_tmp[30]_i_1_n_0 ));
  LUT6 #(
    .INIT(64'hFFFFFFFFFFBBFCB8)) 
    \AXI4_Lite_RDATA_tmp[30]_i_2 
       (.I0(AXI4_Lite_ARADDR[6]),
        .I1(AXI4_Lite_ARVALID),
        .I2(sel0[6]),
        .I3(AXI4_Lite_ARADDR[7]),
        .I4(sel0[7]),
        .I5(data_reg_PWM_en_AXI_1_1_i_3_n_0),
        .O(\AXI4_Lite_RDATA_tmp[30]_i_2_n_0 ));
  LUT6 #(
    .INIT(64'hFFFFFFFFFFBBFCB8)) 
    \AXI4_Lite_RDATA_tmp[30]_i_3 
       (.I0(AXI4_Lite_ARADDR[8]),
        .I1(AXI4_Lite_ARVALID),
        .I2(sel0[8]),
        .I3(AXI4_Lite_ARADDR[9]),
        .I4(sel0[9]),
        .I5(\AXI4_Lite_RDATA_tmp[30]_i_5_n_0 ),
        .O(\AXI4_Lite_RDATA_tmp[30]_i_3_n_0 ));
  LUT5 #(
    .INIT(32'h00001000)) 
    \AXI4_Lite_RDATA_tmp[30]_i_4 
       (.I0(data_reg_axi_enable_1_1_i_3_n_0),
        .I1(\AXI4_Lite_RDATA_tmp[30]_i_6_n_0 ),
        .I2(\data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_2_n_0 ),
        .I3(read_reg_ip_timestamp),
        .I4(\data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_3_n_0 ),
        .O(\AXI4_Lite_RDATA_tmp[30]_i_4_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair6" *) 
  LUT5 #(
    .INIT(32'hFFFACCFA)) 
    \AXI4_Lite_RDATA_tmp[30]_i_5 
       (.I0(sel0[11]),
        .I1(AXI4_Lite_ARADDR[11]),
        .I2(sel0[10]),
        .I3(AXI4_Lite_ARVALID),
        .I4(AXI4_Lite_ARADDR[10]),
        .O(\AXI4_Lite_RDATA_tmp[30]_i_5_n_0 ));
  LUT5 #(
    .INIT(32'hFFFACCFA)) 
    \AXI4_Lite_RDATA_tmp[30]_i_6 
       (.I0(sel0[12]),
        .I1(AXI4_Lite_ARADDR[12]),
        .I2(sel0[13]),
        .I3(AXI4_Lite_ARVALID),
        .I4(AXI4_Lite_ARADDR[13]),
        .O(\AXI4_Lite_RDATA_tmp[30]_i_6_n_0 ));
  FDRE \AXI4_Lite_RDATA_tmp_reg[30] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(\AXI4_Lite_RDATA_tmp[30]_i_1_n_0 ),
        .Q(AXI4_Lite_RDATA),
        .R(reset));
  (* SOFT_HLUTNM = "soft_lutpair8" *) 
  LUT5 #(
    .INIT(32'hFF8F8888)) 
    \FSM_onehot_axi_lite_wstate[0]_i_1 
       (.I0(AXI4_Lite_BREADY),
        .I1(\FSM_onehot_axi_lite_wstate_reg[2]_0 [1]),
        .I2(AXI4_Lite_AWVALID),
        .I3(FSM_sequential_axi_lite_rstate_reg_0),
        .I4(\FSM_onehot_axi_lite_wstate_reg_n_0_[0] ),
        .O(axi_lite_wstate_next[0]));
  LUT1 #(
    .INIT(2'h1)) 
    \FSM_onehot_axi_lite_wstate[1]_i_1 
       (.I0(AXI4_Lite_ARESETN),
        .O(reset));
  LUT5 #(
    .INIT(32'h44F44444)) 
    \FSM_onehot_axi_lite_wstate[1]_i_2 
       (.I0(AXI4_Lite_WVALID),
        .I1(\FSM_onehot_axi_lite_wstate_reg[2]_0 [0]),
        .I2(AXI4_Lite_AWVALID),
        .I3(FSM_sequential_axi_lite_rstate_reg_0),
        .I4(\FSM_onehot_axi_lite_wstate_reg_n_0_[0] ),
        .O(axi_lite_wstate_next[1]));
  LUT4 #(
    .INIT(16'hF444)) 
    \FSM_onehot_axi_lite_wstate[2]_i_1 
       (.I0(AXI4_Lite_BREADY),
        .I1(\FSM_onehot_axi_lite_wstate_reg[2]_0 [1]),
        .I2(AXI4_Lite_WVALID),
        .I3(\FSM_onehot_axi_lite_wstate_reg[2]_0 [0]),
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
  (* SOFT_HLUTNM = "soft_lutpair7" *) 
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
    .INIT(32'h00000400)) 
    \data_reg_Mode_AXI_1_1[1]_i_1 
       (.I0(\data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_5_n_0 ),
        .I1(\data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_6_n_0 ),
        .I2(\data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_2_n_0 ),
        .I3(\data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_3_n_0 ),
        .I4(\data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_4_n_0 ),
        .O(\AXI4_Lite_ARADDR[6]_1 ));
  (* SOFT_HLUTNM = "soft_lutpair2" *) 
  LUT5 #(
    .INIT(32'h00080000)) 
    \data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_1 
       (.I0(\data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_2_n_0 ),
        .I1(\data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_3_n_0 ),
        .I2(\data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_4_n_0 ),
        .I3(\data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_5_n_0 ),
        .I4(\data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_6_n_0 ),
        .O(E));
  (* SOFT_HLUTNM = "soft_lutpair6" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_10 
       (.I0(AXI4_Lite_ARADDR[11]),
        .I1(AXI4_Lite_ARVALID),
        .I2(sel0[11]),
        .O(\data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_10_n_0 ));
  LUT3 #(
    .INIT(8'hB8)) 
    \data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_11 
       (.I0(AXI4_Lite_ARADDR[7]),
        .I1(AXI4_Lite_ARVALID),
        .I2(sel0[7]),
        .O(\data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_11_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair9" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_2 
       (.I0(AXI4_Lite_ARADDR[1]),
        .I1(AXI4_Lite_ARVALID),
        .I2(sel0[1]),
        .O(\data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_2_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair9" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_3 
       (.I0(AXI4_Lite_ARADDR[0]),
        .I1(AXI4_Lite_ARVALID),
        .I2(sel0[0]),
        .O(\data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_3_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair4" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_4 
       (.I0(AXI4_Lite_ARADDR[2]),
        .I1(AXI4_Lite_ARVALID),
        .I2(sel0[2]),
        .O(\data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_4_n_0 ));
  LUT6 #(
    .INIT(64'hFFFFFFFF47034400)) 
    \data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_5 
       (.I0(AXI4_Lite_ARADDR[4]),
        .I1(AXI4_Lite_ARVALID),
        .I2(sel0[4]),
        .I3(AXI4_Lite_ARADDR[3]),
        .I4(sel0[3]),
        .I5(\data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_7_n_0 ),
        .O(\data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_5_n_0 ));
  LUT5 #(
    .INIT(32'h00004000)) 
    \data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_6 
       (.I0(\AXI4_Lite_RDATA_tmp[30]_i_6_n_0 ),
        .I1(\data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_8_n_0 ),
        .I2(\data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_9_n_0 ),
        .I3(top_wr_enb),
        .I4(data_reg_PWM_en_AXI_1_1_i_3_n_0),
        .O(\data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_6_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair5" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_7 
       (.I0(AXI4_Lite_ARADDR[5]),
        .I1(AXI4_Lite_ARVALID),
        .I2(sel0[5]),
        .O(\data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_7_n_0 ));
  LUT6 #(
    .INIT(64'h0000000003000355)) 
    \data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_8 
       (.I0(sel0[9]),
        .I1(AXI4_Lite_ARADDR[9]),
        .I2(AXI4_Lite_ARADDR[10]),
        .I3(AXI4_Lite_ARVALID),
        .I4(sel0[10]),
        .I5(\data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_10_n_0 ),
        .O(\data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_8_n_0 ));
  LUT6 #(
    .INIT(64'h0000000047440300)) 
    \data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_9 
       (.I0(AXI4_Lite_ARADDR[8]),
        .I1(AXI4_Lite_ARVALID),
        .I2(sel0[8]),
        .I3(sel0[6]),
        .I4(AXI4_Lite_ARADDR[6]),
        .I5(\data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_11_n_0 ),
        .O(\data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_9_n_0 ));
  LUT6 #(
    .INIT(64'hFFEFFFFF00200000)) 
    data_reg_PWM_en_AXI_1_1_i_1
       (.I0(Q[0]),
        .I1(data_reg_axi_enable_1_1_i_2_n_0),
        .I2(data_reg_PWM_en_AXI_1_1_i_2_n_0),
        .I3(data_reg_PWM_en_AXI_1_1_i_3_n_0),
        .I4(data_reg_PWM_en_AXI_1_1_i_4_n_0),
        .I5(write_PWM_en_AXI),
        .O(\wdata_reg[0]_1 ));
  LUT6 #(
    .INIT(64'h0000005044440050)) 
    data_reg_PWM_en_AXI_1_1_i_2
       (.I0(\data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_2_n_0 ),
        .I1(AXI4_Lite_ARADDR[6]),
        .I2(sel0[6]),
        .I3(sel0[7]),
        .I4(AXI4_Lite_ARVALID),
        .I5(AXI4_Lite_ARADDR[7]),
        .O(data_reg_PWM_en_AXI_1_1_i_2_n_0));
  (* SOFT_HLUTNM = "soft_lutpair5" *) 
  LUT5 #(
    .INIT(32'hFFFACCFA)) 
    data_reg_PWM_en_AXI_1_1_i_3
       (.I0(sel0[5]),
        .I1(AXI4_Lite_ARADDR[5]),
        .I2(sel0[4]),
        .I3(AXI4_Lite_ARVALID),
        .I4(AXI4_Lite_ARADDR[4]),
        .O(data_reg_PWM_en_AXI_1_1_i_3_n_0));
  LUT6 #(
    .INIT(64'h0004000000040404)) 
    data_reg_PWM_en_AXI_1_1_i_4
       (.I0(\data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_3_n_0 ),
        .I1(top_wr_enb),
        .I2(\data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_4_n_0 ),
        .I3(AXI4_Lite_ARADDR[3]),
        .I4(AXI4_Lite_ARVALID),
        .I5(sel0[3]),
        .O(data_reg_PWM_en_AXI_1_1_i_4_n_0));
  (* SOFT_HLUTNM = "soft_lutpair1" *) 
  LUT5 #(
    .INIT(32'h00001000)) 
    \data_reg_PWM_min_pulse_width_0to1_AXI_1_1[13]_i_1 
       (.I0(\data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_2_n_0 ),
        .I1(\data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_3_n_0 ),
        .I2(\data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_4_n_0 ),
        .I3(\data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_6_n_0 ),
        .I4(\data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_5_n_0 ),
        .O(\AXI4_Lite_ARADDR[3]_2 ));
  (* SOFT_HLUTNM = "soft_lutpair3" *) 
  LUT5 #(
    .INIT(32'h00020000)) 
    \data_reg_TriState_HB1_AXI_1_1[1]_i_1 
       (.I0(\data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_5_n_0 ),
        .I1(\data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_4_n_0 ),
        .I2(\data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_3_n_0 ),
        .I3(\data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_2_n_0 ),
        .I4(\data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_6_n_0 ),
        .O(\AXI4_Lite_ARADDR[6] ));
  (* SOFT_HLUTNM = "soft_lutpair3" *) 
  LUT5 #(
    .INIT(32'h00200000)) 
    \data_reg_TriState_HB2_AXI_1_1[1]_i_1 
       (.I0(\data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_5_n_0 ),
        .I1(\data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_4_n_0 ),
        .I2(\data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_3_n_0 ),
        .I3(\data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_2_n_0 ),
        .I4(\data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_6_n_0 ),
        .O(\AXI4_Lite_ARADDR[6]_0 ));
  (* SOFT_HLUTNM = "soft_lutpair2" *) 
  LUT5 #(
    .INIT(32'h02000000)) 
    \data_reg_TriState_HB3_AXI_1_1[1]_i_1 
       (.I0(\data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_2_n_0 ),
        .I1(\data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_3_n_0 ),
        .I2(\data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_4_n_0 ),
        .I3(\data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_5_n_0 ),
        .I4(\data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_6_n_0 ),
        .O(\AXI4_Lite_ARADDR[3]_3 ));
  LUT6 #(
    .INIT(64'hFFFEFFFF00020000)) 
    data_reg_axi_enable_1_1_i_1
       (.I0(Q[0]),
        .I1(\AXI4_Lite_RDATA_tmp[30]_i_2_n_0 ),
        .I2(data_reg_axi_enable_1_1_i_2_n_0),
        .I3(data_reg_axi_enable_1_1_i_3_n_0),
        .I4(data_reg_axi_enable_1_1_i_4_n_0),
        .I5(CEP),
        .O(\wdata_reg[0]_0 ));
  LUT6 #(
    .INIT(64'hFFFFFFFFFFBBFCB8)) 
    data_reg_axi_enable_1_1_i_2
       (.I0(AXI4_Lite_ARADDR[13]),
        .I1(AXI4_Lite_ARVALID),
        .I2(sel0[13]),
        .I3(AXI4_Lite_ARADDR[12]),
        .I4(sel0[12]),
        .I5(\AXI4_Lite_RDATA_tmp[30]_i_3_n_0 ),
        .O(data_reg_axi_enable_1_1_i_2_n_0));
  (* SOFT_HLUTNM = "soft_lutpair4" *) 
  LUT5 #(
    .INIT(32'hFFFACCFA)) 
    data_reg_axi_enable_1_1_i_3
       (.I0(sel0[3]),
        .I1(AXI4_Lite_ARADDR[3]),
        .I2(sel0[2]),
        .I3(AXI4_Lite_ARVALID),
        .I4(AXI4_Lite_ARADDR[2]),
        .O(data_reg_axi_enable_1_1_i_3_n_0));
  LUT6 #(
    .INIT(64'h000000A0888800A0)) 
    data_reg_axi_enable_1_1_i_4
       (.I0(top_wr_enb),
        .I1(AXI4_Lite_ARADDR[0]),
        .I2(sel0[0]),
        .I3(sel0[1]),
        .I4(AXI4_Lite_ARVALID),
        .I5(AXI4_Lite_ARADDR[1]),
        .O(data_reg_axi_enable_1_1_i_4_n_0));
  (* SOFT_HLUTNM = "soft_lutpair1" *) 
  LUT5 #(
    .INIT(32'h00004000)) 
    \data_reg_m_u1_norm_AXI_1_1[13]_i_1 
       (.I0(\data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_2_n_0 ),
        .I1(\data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_3_n_0 ),
        .I2(\data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_4_n_0 ),
        .I3(\data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_6_n_0 ),
        .I4(\data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_5_n_0 ),
        .O(\AXI4_Lite_ARADDR[3]_1 ));
  (* SOFT_HLUTNM = "soft_lutpair0" *) 
  LUT5 #(
    .INIT(32'h00002000)) 
    \data_reg_m_u2_norm_AXI_1_1[13]_i_1 
       (.I0(\data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_2_n_0 ),
        .I1(\data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_3_n_0 ),
        .I2(\data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_4_n_0 ),
        .I3(\data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_6_n_0 ),
        .I4(\data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_5_n_0 ),
        .O(\AXI4_Lite_ARADDR[3]_0 ));
  (* SOFT_HLUTNM = "soft_lutpair0" *) 
  LUT5 #(
    .INIT(32'h00008000)) 
    \data_reg_m_u3_norm_AXI_1_1[13]_i_1 
       (.I0(\data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_2_n_0 ),
        .I1(\data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_3_n_0 ),
        .I2(\data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_4_n_0 ),
        .I3(\data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_6_n_0 ),
        .I4(\data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_5_n_0 ),
        .O(\AXI4_Lite_ARADDR[3] ));
  LUT3 #(
    .INIT(8'hDF)) 
    reset_pipe_i_1
       (.I0(AXI4_Lite_ARESETN),
        .I1(soft_reset),
        .I2(IPCORE_RESETN),
        .O(reset_in));
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
        .I4(sel0[4]),
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
    .INIT(64'h0010000000000000)) 
    soft_reset_i_4
       (.I0(sel0[11]),
        .I1(sel0[12]),
        .I2(Q[0]),
        .I3(sel0[13]),
        .I4(top_wr_enb),
        .I5(AXI4_Lite_ARESETN),
        .O(soft_reset_i_4_n_0));
  LUT4 #(
    .INIT(16'h0001)) 
    soft_reset_i_5
       (.I0(sel0[10]),
        .I1(sel0[8]),
        .I2(sel0[7]),
        .I3(sel0[5]),
        .O(soft_reset_i_5_n_0));
  FDRE soft_reset_reg
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(soft_reset_i_1_n_0),
        .Q(soft_reset),
        .R(1'b0));
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
    \wdata[19]_i_1 
       (.I0(\FSM_onehot_axi_lite_wstate_reg[2]_0 [0]),
        .I1(AXI4_Lite_WVALID),
        .O(w_transfer));
  FDRE \wdata_reg[0] 
       (.C(AXI4_Lite_ACLK),
        .CE(w_transfer),
        .D(AXI4_Lite_WDATA[0]),
        .Q(Q[0]),
        .R(reset));
  FDRE \wdata_reg[10] 
       (.C(AXI4_Lite_ACLK),
        .CE(w_transfer),
        .D(AXI4_Lite_WDATA[10]),
        .Q(Q[10]),
        .R(reset));
  FDRE \wdata_reg[11] 
       (.C(AXI4_Lite_ACLK),
        .CE(w_transfer),
        .D(AXI4_Lite_WDATA[11]),
        .Q(Q[11]),
        .R(reset));
  FDRE \wdata_reg[12] 
       (.C(AXI4_Lite_ACLK),
        .CE(w_transfer),
        .D(AXI4_Lite_WDATA[12]),
        .Q(Q[12]),
        .R(reset));
  FDRE \wdata_reg[13] 
       (.C(AXI4_Lite_ACLK),
        .CE(w_transfer),
        .D(AXI4_Lite_WDATA[13]),
        .Q(Q[13]),
        .R(reset));
  FDRE \wdata_reg[14] 
       (.C(AXI4_Lite_ACLK),
        .CE(w_transfer),
        .D(AXI4_Lite_WDATA[14]),
        .Q(Q[14]),
        .R(reset));
  FDRE \wdata_reg[15] 
       (.C(AXI4_Lite_ACLK),
        .CE(w_transfer),
        .D(AXI4_Lite_WDATA[15]),
        .Q(Q[15]),
        .R(reset));
  FDRE \wdata_reg[16] 
       (.C(AXI4_Lite_ACLK),
        .CE(w_transfer),
        .D(AXI4_Lite_WDATA[16]),
        .Q(Q[16]),
        .R(reset));
  FDRE \wdata_reg[17] 
       (.C(AXI4_Lite_ACLK),
        .CE(w_transfer),
        .D(AXI4_Lite_WDATA[17]),
        .Q(Q[17]),
        .R(reset));
  FDRE \wdata_reg[18] 
       (.C(AXI4_Lite_ACLK),
        .CE(w_transfer),
        .D(AXI4_Lite_WDATA[18]),
        .Q(Q[18]),
        .R(reset));
  FDRE \wdata_reg[19] 
       (.C(AXI4_Lite_ACLK),
        .CE(w_transfer),
        .D(AXI4_Lite_WDATA[19]),
        .Q(Q[19]),
        .R(reset));
  FDRE \wdata_reg[1] 
       (.C(AXI4_Lite_ACLK),
        .CE(w_transfer),
        .D(AXI4_Lite_WDATA[1]),
        .Q(Q[1]),
        .R(reset));
  FDRE \wdata_reg[2] 
       (.C(AXI4_Lite_ACLK),
        .CE(w_transfer),
        .D(AXI4_Lite_WDATA[2]),
        .Q(Q[2]),
        .R(reset));
  FDRE \wdata_reg[3] 
       (.C(AXI4_Lite_ACLK),
        .CE(w_transfer),
        .D(AXI4_Lite_WDATA[3]),
        .Q(Q[3]),
        .R(reset));
  FDRE \wdata_reg[4] 
       (.C(AXI4_Lite_ACLK),
        .CE(w_transfer),
        .D(AXI4_Lite_WDATA[4]),
        .Q(Q[4]),
        .R(reset));
  FDRE \wdata_reg[5] 
       (.C(AXI4_Lite_ACLK),
        .CE(w_transfer),
        .D(AXI4_Lite_WDATA[5]),
        .Q(Q[5]),
        .R(reset));
  FDRE \wdata_reg[6] 
       (.C(AXI4_Lite_ACLK),
        .CE(w_transfer),
        .D(AXI4_Lite_WDATA[6]),
        .Q(Q[6]),
        .R(reset));
  FDRE \wdata_reg[7] 
       (.C(AXI4_Lite_ACLK),
        .CE(w_transfer),
        .D(AXI4_Lite_WDATA[7]),
        .Q(Q[7]),
        .R(reset));
  FDRE \wdata_reg[8] 
       (.C(AXI4_Lite_ACLK),
        .CE(w_transfer),
        .D(AXI4_Lite_WDATA[8]),
        .Q(Q[8]),
        .R(reset));
  FDRE \wdata_reg[9] 
       (.C(AXI4_Lite_ACLK),
        .CE(w_transfer),
        .D(AXI4_Lite_WDATA[9]),
        .Q(Q[9]),
        .R(reset));
  LUT6 #(
    .INIT(64'h8000000000000000)) 
    wr_enb_1_i_1
       (.I0(AXI4_Lite_WSTRB[2]),
        .I1(AXI4_Lite_WSTRB[3]),
        .I2(AXI4_Lite_WSTRB[0]),
        .I3(AXI4_Lite_WSTRB[1]),
        .I4(AXI4_Lite_WVALID),
        .I5(\FSM_onehot_axi_lite_wstate_reg[2]_0 [0]),
        .O(w_transfer_and_wstrb));
  FDRE wr_enb_1_reg
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(w_transfer_and_wstrb),
        .Q(top_wr_enb),
        .R(reset));
endmodule

(* ORIG_REF_NAME = "PWM_SS_3L_ip_dut" *) 
module zusys_PWM_SS_3L_ip_0_0_PWM_SS_3L_ip_dut
   (PWM_en_AXI_2_reg,
    Period_Center,
    Period_Start,
    SSa2_OUT,
    SSa1_OUT,
    SSb2_OUT,
    SSb1_OUT,
    SSc2_OUT,
    SSc1_OUT,
    RSTP,
    CEP,
    IPCORE_CLK,
    \reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2 ,
    \delayMatch2_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2 ,
    \delayMatch5_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2 ,
    \delayMatch8_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2 ,
    write_PWM_en_AXI,
    \HDL_Counter2_count_reg[19] ,
    D,
    \maximum_counter_value_1_reg[8] ,
    \min_pulse_width_AXI_1_reg[13] ,
    SSc2_IN_External,
    SSc1_IN_External,
    SSb2_IN_External,
    SSb1_IN_External,
    SSa2_IN_External,
    SSa1_IN_External,
    \delayMatch1_reg_reg[0][13] ,
    m_u1_norm,
    \delayMatch3_reg_reg[0][13] ,
    m_u2_norm,
    \delayMatch5_reg_reg[0][13] ,
    m_u3_norm);
  output PWM_en_AXI_2_reg;
  output Period_Center;
  output Period_Start;
  output SSa2_OUT;
  output SSa1_OUT;
  output SSb2_OUT;
  output SSb1_OUT;
  output SSc2_OUT;
  output SSc1_OUT;
  input RSTP;
  input CEP;
  input IPCORE_CLK;
  input [1:0]\reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2 ;
  input [1:0]\delayMatch2_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2 ;
  input [1:0]\delayMatch5_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2 ;
  input [1:0]\delayMatch8_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2 ;
  input write_PWM_en_AXI;
  input \HDL_Counter2_count_reg[19] ;
  input [19:0]D;
  input \maximum_counter_value_1_reg[8] ;
  input [13:0]\min_pulse_width_AXI_1_reg[13] ;
  input SSc2_IN_External;
  input SSc1_IN_External;
  input SSb2_IN_External;
  input SSb1_IN_External;
  input SSa2_IN_External;
  input SSa1_IN_External;
  input [13:0]\delayMatch1_reg_reg[0][13] ;
  input [13:0]m_u1_norm;
  input [13:0]\delayMatch3_reg_reg[0][13] ;
  input [13:0]m_u2_norm;
  input [13:0]\delayMatch5_reg_reg[0][13] ;
  input [13:0]m_u3_norm;

  wire CEP;
  wire [19:0]D;
  wire \HDL_Counter2_count_reg[19] ;
  wire IPCORE_CLK;
  wire PWM_en_AXI_2_reg;
  wire Period_Center;
  wire Period_Start;
  wire RSTP;
  wire SSa1_IN_External;
  wire SSa1_OUT;
  wire SSa2_IN_External;
  wire SSa2_OUT;
  wire SSb1_IN_External;
  wire SSb1_OUT;
  wire SSb2_IN_External;
  wire SSb2_OUT;
  wire SSc1_IN_External;
  wire SSc1_OUT;
  wire SSc2_IN_External;
  wire SSc2_OUT;
  wire [13:0]\delayMatch1_reg_reg[0][13] ;
  wire [1:0]\delayMatch2_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2 ;
  wire [13:0]\delayMatch3_reg_reg[0][13] ;
  wire [13:0]\delayMatch5_reg_reg[0][13] ;
  wire [1:0]\delayMatch5_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2 ;
  wire [1:0]\delayMatch8_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2 ;
  wire [13:0]m_u1_norm;
  wire [13:0]m_u2_norm;
  wire [13:0]m_u3_norm;
  wire \maximum_counter_value_1_reg[8] ;
  wire [13:0]\min_pulse_width_AXI_1_reg[13] ;
  wire [1:0]\reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2 ;
  wire write_PWM_en_AXI;

  zusys_PWM_SS_3L_ip_0_0_PWM_SS_3L_ip_src_PWM_SS_Ctrl u_PWM_SS_3L_ip_src_PWM_SS_Ctrl
       (.CEP(CEP),
        .D(PWM_en_AXI_2_reg),
        .\HDL_Counter2_count_reg[19] (\HDL_Counter2_count_reg[19] ),
        .IPCORE_CLK(IPCORE_CLK),
        .Period_Center(Period_Center),
        .Period_Start(Period_Start),
        .RSTP(RSTP),
        .SSa1_IN_External(SSa1_IN_External),
        .SSa1_OUT(SSa1_OUT),
        .SSa2_IN_External(SSa2_IN_External),
        .SSa2_OUT(SSa2_OUT),
        .SSb1_IN_External(SSb1_IN_External),
        .SSb1_OUT(SSb1_OUT),
        .SSb2_IN_External(SSb2_IN_External),
        .SSb2_OUT(SSb2_OUT),
        .SSc1_IN_External(SSc1_IN_External),
        .SSc1_OUT(SSc1_OUT),
        .SSc2_IN_External(SSc2_IN_External),
        .SSc2_OUT(SSc2_OUT),
        .\delayMatch1_reg_reg[0][13] (\delayMatch1_reg_reg[0][13] ),
        .\delayMatch2_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2 (\delayMatch2_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2 ),
        .\delayMatch3_reg_reg[0][13] (\delayMatch3_reg_reg[0][13] ),
        .\delayMatch5_reg_reg[0][13] (\delayMatch5_reg_reg[0][13] ),
        .\delayMatch5_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2 (\delayMatch5_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2 ),
        .\delayMatch8_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2 (\delayMatch8_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2 ),
        .m_u1_norm(m_u1_norm),
        .m_u2_norm(m_u2_norm),
        .m_u3_norm(m_u3_norm),
        .\max_counter_value_1_reg[19] (D),
        .\maximum_counter_value_1_reg[8] (\maximum_counter_value_1_reg[8] ),
        .\min_pulse_width_AXI_1_reg[13] (\min_pulse_width_AXI_1_reg[13] ),
        .\reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2 (\reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2 ),
        .write_PWM_en_AXI(write_PWM_en_AXI));
endmodule

(* ORIG_REF_NAME = "PWM_SS_3L_ip_reset_sync" *) 
module zusys_PWM_SS_3L_ip_0_0_PWM_SS_3L_ip_reset_sync
   (RSTP,
    reset_out_reg_0,
    reset_in,
    IPCORE_CLK,
    CEP,
    IPCORE_RESETN,
    soft_reset,
    AXI4_Lite_ARESETN);
  output RSTP;
  output reset_out_reg_0;
  input reset_in;
  input IPCORE_CLK;
  input CEP;
  input IPCORE_RESETN;
  input soft_reset;
  input AXI4_Lite_ARESETN;

  wire AXI4_Lite_ARESETN;
  wire CEP;
  wire IPCORE_CLK;
  wire IPCORE_RESETN;
  wire RSTP;
  wire reset_in;
  wire reset_out_i_1_n_0;
  wire reset_out_reg_0;
  wire reset_pipe;
  wire soft_reset;

  LUT2 #(
    .INIT(4'hE)) 
    \maximum_counter_value_1[8]_i_1 
       (.I0(RSTP),
        .I1(CEP),
        .O(reset_out_reg_0));
  LUT4 #(
    .INIT(16'hFBFF)) 
    reset_out_i_1
       (.I0(reset_pipe),
        .I1(IPCORE_RESETN),
        .I2(soft_reset),
        .I3(AXI4_Lite_ARESETN),
        .O(reset_out_i_1_n_0));
  FDRE reset_out_reg
       (.C(IPCORE_CLK),
        .CE(1'b1),
        .D(reset_out_i_1_n_0),
        .Q(RSTP),
        .R(1'b0));
  FDRE reset_pipe_reg
       (.C(IPCORE_CLK),
        .CE(1'b1),
        .D(reset_in),
        .Q(reset_pipe),
        .R(1'b0));
endmodule

(* ORIG_REF_NAME = "PWM_SS_3L_ip_src_Chose_SS" *) 
module zusys_PWM_SS_3L_ip_0_0_PWM_SS_3L_ip_src_Chose_SS
   (delayMatch_1_reg_1,
    delayMatch_1_reg,
    delayMatch3_1_reg_1,
    delayMatch3_1_reg,
    delayMatch6_1_reg_1,
    delayMatch6_1_reg,
    SSa2_OUT,
    SSa1_OUT,
    SSb2_OUT,
    SSb1_OUT,
    SSc2_OUT,
    SSc1_OUT,
    RSTP,
    CEP,
    IPCORE_CLK,
    \reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2_0 ,
    \delayMatch2_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2_0 ,
    \delayMatch5_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2_0 ,
    \delayMatch8_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2_0 ,
    Demux_out3,
    Demux_out2,
    Demux_out1,
    Q,
    SSb1_OUT_0,
    SSc1_OUT_0);
  output [0:0]delayMatch_1_reg_1;
  output [0:0]delayMatch_1_reg;
  output [0:0]delayMatch3_1_reg_1;
  output [0:0]delayMatch3_1_reg;
  output [0:0]delayMatch6_1_reg_1;
  output [0:0]delayMatch6_1_reg;
  output SSa2_OUT;
  output SSa1_OUT;
  output SSb2_OUT;
  output SSb1_OUT;
  output SSc2_OUT;
  output SSc1_OUT;
  input RSTP;
  input CEP;
  input IPCORE_CLK;
  input [0:0]\reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2_0 ;
  input [1:0]\delayMatch2_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2_0 ;
  input [1:0]\delayMatch5_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2_0 ;
  input [1:0]\delayMatch8_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2_0 ;
  input [0:1]Demux_out3;
  input [0:1]Demux_out2;
  input [0:1]Demux_out1;
  input [1:0]Q;
  input [1:0]SSb1_OUT_0;
  input [1:0]SSc1_OUT_0;

  wire CEP;
  wire [0:1]Demux_out1;
  wire [0:1]Demux_out2;
  wire [0:1]Demux_out3;
  wire IPCORE_CLK;
  wire [1:0]Q;
  wire RSTP;
  wire SSa1_OUT;
  wire SSa2_OUT;
  wire [0:1]SSa_IN_External_2;
  wire SSb1_OUT;
  wire [1:0]SSb1_OUT_0;
  wire SSb2_OUT;
  wire [0:1]SSb_IN_External_2;
  wire SSc1_OUT;
  wire [1:0]SSc1_OUT_0;
  wire SSc2_OUT;
  wire [0:1]SSc_IN_External_2;
  wire \delayMatch2_reg_reg[2][0]_srl3___U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_1_n_0 ;
  wire \delayMatch2_reg_reg[2][1]_srl3___U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_1_n_0 ;
  wire \delayMatch2_reg_reg[3][0]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2_n_0 ;
  wire [1:0]\delayMatch2_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2_0 ;
  wire \delayMatch2_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2_n_0 ;
  wire delayMatch2_reg_reg_gate__0_n_0;
  wire delayMatch2_reg_reg_gate_n_0;
  wire \delayMatch2_reg_reg_n_0_[4][0] ;
  wire \delayMatch2_reg_reg_n_0_[4][1] ;
  wire [0:0]delayMatch3_1_reg;
  wire [0:0]delayMatch3_1_reg_1;
  wire \delayMatch5_reg_reg[2][0]_srl3___U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_1_n_0 ;
  wire \delayMatch5_reg_reg[2][1]_srl3___U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_1_n_0 ;
  wire \delayMatch5_reg_reg[3][0]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2_n_0 ;
  wire [1:0]\delayMatch5_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2_0 ;
  wire \delayMatch5_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2_n_0 ;
  wire delayMatch5_reg_reg_gate__0_n_0;
  wire delayMatch5_reg_reg_gate_n_0;
  wire \delayMatch5_reg_reg_n_0_[4][0] ;
  wire \delayMatch5_reg_reg_n_0_[4][1] ;
  wire [0:0]delayMatch6_1_reg;
  wire [0:0]delayMatch6_1_reg_1;
  wire \delayMatch8_reg_reg[2][0]_srl3___U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_1_n_0 ;
  wire \delayMatch8_reg_reg[2][1]_srl3___U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_1_n_0 ;
  wire \delayMatch8_reg_reg[3][0]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2_n_0 ;
  wire [1:0]\delayMatch8_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2_0 ;
  wire \delayMatch8_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2_n_0 ;
  wire delayMatch8_reg_reg_gate__0_n_0;
  wire delayMatch8_reg_reg_gate_n_0;
  wire \delayMatch8_reg_reg_n_0_[4][0] ;
  wire \delayMatch8_reg_reg_n_0_[4][1] ;
  wire [0:0]delayMatch_1_reg;
  wire [0:0]delayMatch_1_reg_1;
  wire \reduced_reg_reg[2][1]_srl3___U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_1_n_0 ;
  wire [0:0]\reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2_0 ;
  wire \reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2_n_0 ;
  wire reduced_reg_reg_gate_n_0;
  wire reduced_reg_reg_r_0_n_0;
  wire reduced_reg_reg_r_1_n_0;
  wire reduced_reg_reg_r_2_n_0;
  wire reduced_reg_reg_r_n_0;
  wire switch_compare_1;

  LUT5 #(
    .INIT(32'h000000E2)) 
    SSa1_OUT_INST_0
       (.I0(Q[1]),
        .I1(switch_compare_1),
        .I2(SSa_IN_External_2[0]),
        .I3(\delayMatch2_reg_reg_n_0_[4][0] ),
        .I4(\delayMatch2_reg_reg_n_0_[4][1] ),
        .O(SSa1_OUT));
  LUT5 #(
    .INIT(32'h000000E2)) 
    SSa2_OUT_INST_0
       (.I0(Q[0]),
        .I1(switch_compare_1),
        .I2(SSa_IN_External_2[1]),
        .I3(\delayMatch2_reg_reg_n_0_[4][0] ),
        .I4(\delayMatch2_reg_reg_n_0_[4][1] ),
        .O(SSa2_OUT));
  LUT5 #(
    .INIT(32'h000000E2)) 
    SSb1_OUT_INST_0
       (.I0(SSb1_OUT_0[1]),
        .I1(switch_compare_1),
        .I2(SSb_IN_External_2[0]),
        .I3(\delayMatch5_reg_reg_n_0_[4][0] ),
        .I4(\delayMatch5_reg_reg_n_0_[4][1] ),
        .O(SSb1_OUT));
  LUT5 #(
    .INIT(32'h000000E2)) 
    SSb2_OUT_INST_0
       (.I0(SSb1_OUT_0[0]),
        .I1(switch_compare_1),
        .I2(SSb_IN_External_2[1]),
        .I3(\delayMatch5_reg_reg_n_0_[4][0] ),
        .I4(\delayMatch5_reg_reg_n_0_[4][1] ),
        .O(SSb2_OUT));
  LUT5 #(
    .INIT(32'h000000E2)) 
    SSc1_OUT_INST_0
       (.I0(SSc1_OUT_0[1]),
        .I1(switch_compare_1),
        .I2(SSc_IN_External_2[0]),
        .I3(\delayMatch8_reg_reg_n_0_[4][0] ),
        .I4(\delayMatch8_reg_reg_n_0_[4][1] ),
        .O(SSc1_OUT));
  LUT5 #(
    .INIT(32'h000000E2)) 
    SSc2_OUT_INST_0
       (.I0(SSc1_OUT_0[0]),
        .I1(switch_compare_1),
        .I2(SSc_IN_External_2[1]),
        .I3(\delayMatch8_reg_reg_n_0_[4][0] ),
        .I4(\delayMatch8_reg_reg_n_0_[4][1] ),
        .O(SSc2_OUT));
  (* srl_bus_name = "\U0/u_PWM_SS_3L_ip_dut_inst/u_PWM_SS_3L_ip_src_PWM_SS_Ctrl/u_Chose_SS/delayMatch2_reg_reg[2] " *) 
  (* srl_name = "\U0/u_PWM_SS_3L_ip_dut_inst/u_PWM_SS_3L_ip_src_PWM_SS_Ctrl/u_Chose_SS/delayMatch2_reg_reg[2][0]_srl3___U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_1 " *) 
  SRL16E \delayMatch2_reg_reg[2][0]_srl3___U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_1 
       (.A0(1'b0),
        .A1(1'b1),
        .A2(1'b0),
        .A3(1'b0),
        .CE(CEP),
        .CLK(IPCORE_CLK),
        .D(\delayMatch2_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2_0 [0]),
        .Q(\delayMatch2_reg_reg[2][0]_srl3___U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_1_n_0 ));
  (* srl_bus_name = "\U0/u_PWM_SS_3L_ip_dut_inst/u_PWM_SS_3L_ip_src_PWM_SS_Ctrl/u_Chose_SS/delayMatch2_reg_reg[2] " *) 
  (* srl_name = "\U0/u_PWM_SS_3L_ip_dut_inst/u_PWM_SS_3L_ip_src_PWM_SS_Ctrl/u_Chose_SS/delayMatch2_reg_reg[2][1]_srl3___U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_1 " *) 
  SRL16E \delayMatch2_reg_reg[2][1]_srl3___U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_1 
       (.A0(1'b0),
        .A1(1'b1),
        .A2(1'b0),
        .A3(1'b0),
        .CE(CEP),
        .CLK(IPCORE_CLK),
        .D(\delayMatch2_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2_0 [1]),
        .Q(\delayMatch2_reg_reg[2][1]_srl3___U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_1_n_0 ));
  FDRE \delayMatch2_reg_reg[3][0]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\delayMatch2_reg_reg[2][0]_srl3___U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_1_n_0 ),
        .Q(\delayMatch2_reg_reg[3][0]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2_n_0 ),
        .R(1'b0));
  FDRE \delayMatch2_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\delayMatch2_reg_reg[2][1]_srl3___U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_1_n_0 ),
        .Q(\delayMatch2_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2_n_0 ),
        .R(1'b0));
  FDRE \delayMatch2_reg_reg[4][0] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(delayMatch2_reg_reg_gate__0_n_0),
        .Q(\delayMatch2_reg_reg_n_0_[4][0] ),
        .R(RSTP));
  FDRE \delayMatch2_reg_reg[4][1] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(delayMatch2_reg_reg_gate_n_0),
        .Q(\delayMatch2_reg_reg_n_0_[4][1] ),
        .R(RSTP));
  (* SOFT_HLUTNM = "soft_lutpair10" *) 
  LUT2 #(
    .INIT(4'h8)) 
    delayMatch2_reg_reg_gate
       (.I0(\delayMatch2_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2_n_0 ),
        .I1(reduced_reg_reg_r_2_n_0),
        .O(delayMatch2_reg_reg_gate_n_0));
  (* SOFT_HLUTNM = "soft_lutpair11" *) 
  LUT2 #(
    .INIT(4'h8)) 
    delayMatch2_reg_reg_gate__0
       (.I0(\delayMatch2_reg_reg[3][0]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2_n_0 ),
        .I1(reduced_reg_reg_r_2_n_0),
        .O(delayMatch2_reg_reg_gate__0_n_0));
  FDRE \delayMatch3_1_reg_1_reg[0] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Demux_out2[1]),
        .Q(delayMatch3_1_reg_1),
        .R(RSTP));
  FDRE \delayMatch3_1_reg_1_reg[1] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(delayMatch3_1_reg_1),
        .Q(SSb_IN_External_2[1]),
        .R(RSTP));
  FDRE \delayMatch3_1_reg_reg[0] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Demux_out2[0]),
        .Q(delayMatch3_1_reg),
        .R(RSTP));
  FDRE \delayMatch3_1_reg_reg[1] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(delayMatch3_1_reg),
        .Q(SSb_IN_External_2[0]),
        .R(RSTP));
  (* srl_bus_name = "\U0/u_PWM_SS_3L_ip_dut_inst/u_PWM_SS_3L_ip_src_PWM_SS_Ctrl/u_Chose_SS/delayMatch5_reg_reg[2] " *) 
  (* srl_name = "\U0/u_PWM_SS_3L_ip_dut_inst/u_PWM_SS_3L_ip_src_PWM_SS_Ctrl/u_Chose_SS/delayMatch5_reg_reg[2][0]_srl3___U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_1 " *) 
  SRL16E \delayMatch5_reg_reg[2][0]_srl3___U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_1 
       (.A0(1'b0),
        .A1(1'b1),
        .A2(1'b0),
        .A3(1'b0),
        .CE(CEP),
        .CLK(IPCORE_CLK),
        .D(\delayMatch5_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2_0 [0]),
        .Q(\delayMatch5_reg_reg[2][0]_srl3___U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_1_n_0 ));
  (* srl_bus_name = "\U0/u_PWM_SS_3L_ip_dut_inst/u_PWM_SS_3L_ip_src_PWM_SS_Ctrl/u_Chose_SS/delayMatch5_reg_reg[2] " *) 
  (* srl_name = "\U0/u_PWM_SS_3L_ip_dut_inst/u_PWM_SS_3L_ip_src_PWM_SS_Ctrl/u_Chose_SS/delayMatch5_reg_reg[2][1]_srl3___U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_1 " *) 
  SRL16E \delayMatch5_reg_reg[2][1]_srl3___U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_1 
       (.A0(1'b0),
        .A1(1'b1),
        .A2(1'b0),
        .A3(1'b0),
        .CE(CEP),
        .CLK(IPCORE_CLK),
        .D(\delayMatch5_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2_0 [1]),
        .Q(\delayMatch5_reg_reg[2][1]_srl3___U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_1_n_0 ));
  FDRE \delayMatch5_reg_reg[3][0]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\delayMatch5_reg_reg[2][0]_srl3___U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_1_n_0 ),
        .Q(\delayMatch5_reg_reg[3][0]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2_n_0 ),
        .R(1'b0));
  FDRE \delayMatch5_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\delayMatch5_reg_reg[2][1]_srl3___U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_1_n_0 ),
        .Q(\delayMatch5_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2_n_0 ),
        .R(1'b0));
  FDRE \delayMatch5_reg_reg[4][0] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(delayMatch5_reg_reg_gate__0_n_0),
        .Q(\delayMatch5_reg_reg_n_0_[4][0] ),
        .R(RSTP));
  FDRE \delayMatch5_reg_reg[4][1] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(delayMatch5_reg_reg_gate_n_0),
        .Q(\delayMatch5_reg_reg_n_0_[4][1] ),
        .R(RSTP));
  (* SOFT_HLUTNM = "soft_lutpair11" *) 
  LUT2 #(
    .INIT(4'h8)) 
    delayMatch5_reg_reg_gate
       (.I0(\delayMatch5_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2_n_0 ),
        .I1(reduced_reg_reg_r_2_n_0),
        .O(delayMatch5_reg_reg_gate_n_0));
  (* SOFT_HLUTNM = "soft_lutpair12" *) 
  LUT2 #(
    .INIT(4'h8)) 
    delayMatch5_reg_reg_gate__0
       (.I0(\delayMatch5_reg_reg[3][0]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2_n_0 ),
        .I1(reduced_reg_reg_r_2_n_0),
        .O(delayMatch5_reg_reg_gate__0_n_0));
  FDRE \delayMatch6_1_reg_1_reg[0] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Demux_out3[1]),
        .Q(delayMatch6_1_reg_1),
        .R(RSTP));
  FDRE \delayMatch6_1_reg_1_reg[1] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(delayMatch6_1_reg_1),
        .Q(SSc_IN_External_2[1]),
        .R(RSTP));
  FDRE \delayMatch6_1_reg_reg[0] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Demux_out3[0]),
        .Q(delayMatch6_1_reg),
        .R(RSTP));
  FDRE \delayMatch6_1_reg_reg[1] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(delayMatch6_1_reg),
        .Q(SSc_IN_External_2[0]),
        .R(RSTP));
  (* srl_bus_name = "\U0/u_PWM_SS_3L_ip_dut_inst/u_PWM_SS_3L_ip_src_PWM_SS_Ctrl/u_Chose_SS/delayMatch8_reg_reg[2] " *) 
  (* srl_name = "\U0/u_PWM_SS_3L_ip_dut_inst/u_PWM_SS_3L_ip_src_PWM_SS_Ctrl/u_Chose_SS/delayMatch8_reg_reg[2][0]_srl3___U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_1 " *) 
  SRL16E \delayMatch8_reg_reg[2][0]_srl3___U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_1 
       (.A0(1'b0),
        .A1(1'b1),
        .A2(1'b0),
        .A3(1'b0),
        .CE(CEP),
        .CLK(IPCORE_CLK),
        .D(\delayMatch8_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2_0 [0]),
        .Q(\delayMatch8_reg_reg[2][0]_srl3___U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_1_n_0 ));
  (* srl_bus_name = "\U0/u_PWM_SS_3L_ip_dut_inst/u_PWM_SS_3L_ip_src_PWM_SS_Ctrl/u_Chose_SS/delayMatch8_reg_reg[2] " *) 
  (* srl_name = "\U0/u_PWM_SS_3L_ip_dut_inst/u_PWM_SS_3L_ip_src_PWM_SS_Ctrl/u_Chose_SS/delayMatch8_reg_reg[2][1]_srl3___U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_1 " *) 
  SRL16E \delayMatch8_reg_reg[2][1]_srl3___U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_1 
       (.A0(1'b0),
        .A1(1'b1),
        .A2(1'b0),
        .A3(1'b0),
        .CE(CEP),
        .CLK(IPCORE_CLK),
        .D(\delayMatch8_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2_0 [1]),
        .Q(\delayMatch8_reg_reg[2][1]_srl3___U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_1_n_0 ));
  FDRE \delayMatch8_reg_reg[3][0]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\delayMatch8_reg_reg[2][0]_srl3___U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_1_n_0 ),
        .Q(\delayMatch8_reg_reg[3][0]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2_n_0 ),
        .R(1'b0));
  FDRE \delayMatch8_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\delayMatch8_reg_reg[2][1]_srl3___U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_1_n_0 ),
        .Q(\delayMatch8_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2_n_0 ),
        .R(1'b0));
  FDRE \delayMatch8_reg_reg[4][0] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(delayMatch8_reg_reg_gate__0_n_0),
        .Q(\delayMatch8_reg_reg_n_0_[4][0] ),
        .R(RSTP));
  FDRE \delayMatch8_reg_reg[4][1] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(delayMatch8_reg_reg_gate_n_0),
        .Q(\delayMatch8_reg_reg_n_0_[4][1] ),
        .R(RSTP));
  (* SOFT_HLUTNM = "soft_lutpair12" *) 
  LUT2 #(
    .INIT(4'h8)) 
    delayMatch8_reg_reg_gate
       (.I0(\delayMatch8_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2_n_0 ),
        .I1(reduced_reg_reg_r_2_n_0),
        .O(delayMatch8_reg_reg_gate_n_0));
  LUT2 #(
    .INIT(4'h8)) 
    delayMatch8_reg_reg_gate__0
       (.I0(\delayMatch8_reg_reg[3][0]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2_n_0 ),
        .I1(reduced_reg_reg_r_2_n_0),
        .O(delayMatch8_reg_reg_gate__0_n_0));
  FDRE \delayMatch_1_reg_1_reg[0] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Demux_out1[1]),
        .Q(delayMatch_1_reg_1),
        .R(RSTP));
  FDRE \delayMatch_1_reg_1_reg[1] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(delayMatch_1_reg_1),
        .Q(SSa_IN_External_2[1]),
        .R(RSTP));
  FDRE \delayMatch_1_reg_reg[0] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Demux_out1[0]),
        .Q(delayMatch_1_reg),
        .R(RSTP));
  FDRE \delayMatch_1_reg_reg[1] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(delayMatch_1_reg),
        .Q(SSa_IN_External_2[0]),
        .R(RSTP));
  (* srl_bus_name = "\U0/u_PWM_SS_3L_ip_dut_inst/u_PWM_SS_3L_ip_src_PWM_SS_Ctrl/u_Chose_SS/reduced_reg_reg[2] " *) 
  (* srl_name = "\U0/u_PWM_SS_3L_ip_dut_inst/u_PWM_SS_3L_ip_src_PWM_SS_Ctrl/u_Chose_SS/reduced_reg_reg[2][1]_srl3___U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_1 " *) 
  SRL16E \reduced_reg_reg[2][1]_srl3___U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_1 
       (.A0(1'b0),
        .A1(1'b1),
        .A2(1'b0),
        .A3(1'b0),
        .CE(CEP),
        .CLK(IPCORE_CLK),
        .D(\reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2_0 ),
        .Q(\reduced_reg_reg[2][1]_srl3___U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_1_n_0 ));
  FDRE \reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\reduced_reg_reg[2][1]_srl3___U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_1_n_0 ),
        .Q(\reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2_n_0 ),
        .R(1'b0));
  FDRE \reduced_reg_reg[4][1] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(reduced_reg_reg_gate_n_0),
        .Q(switch_compare_1),
        .R(RSTP));
  (* SOFT_HLUTNM = "soft_lutpair10" *) 
  LUT2 #(
    .INIT(4'h8)) 
    reduced_reg_reg_gate
       (.I0(\reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2_n_0 ),
        .I1(reduced_reg_reg_r_2_n_0),
        .O(reduced_reg_reg_gate_n_0));
  FDRE reduced_reg_reg_r
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(1'b1),
        .Q(reduced_reg_reg_r_n_0),
        .R(RSTP));
  FDRE reduced_reg_reg_r_0
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(reduced_reg_reg_r_n_0),
        .Q(reduced_reg_reg_r_0_n_0),
        .R(RSTP));
  FDRE reduced_reg_reg_r_1
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(reduced_reg_reg_r_0_n_0),
        .Q(reduced_reg_reg_r_1_n_0),
        .R(RSTP));
  FDRE reduced_reg_reg_r_2
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(reduced_reg_reg_r_1_n_0),
        .Q(reduced_reg_reg_r_2_n_0),
        .R(RSTP));
endmodule

(* ORIG_REF_NAME = "PWM_SS_3L_ip_src_Counter_Ctrl" *) 
module zusys_PWM_SS_3L_ip_0_0_PWM_SS_3L_ip_src_Counter_Ctrl
   (Counter_Ctrl_out3,
    CO,
    O,
    \HDL_Counter2_count_reg[0] ,
    \HDL_Counter2_count_reg[0]_0 ,
    RSTP,
    CEP,
    IPCORE_CLK,
    HDL_Counter2_count_reg,
    S,
    Counter_Ctrl_out4_1_reg,
    maximum_counter_value_1);
  output [20:0]Counter_Ctrl_out3;
  output [0:0]CO;
  output [7:0]O;
  output [7:0]\HDL_Counter2_count_reg[0] ;
  output [3:0]\HDL_Counter2_count_reg[0]_0 ;
  input RSTP;
  input CEP;
  input IPCORE_CLK;
  input [19:0]HDL_Counter2_count_reg;
  input [3:0]S;
  input [6:0]Counter_Ctrl_out4_1_reg;
  input [19:0]maximum_counter_value_1;

  wire Add1_out1_carry__0_i_1_n_0;
  wire Add1_out1_carry__0_i_2_n_0;
  wire Add1_out1_carry__0_i_3_n_0;
  wire Add1_out1_carry__0_i_4_n_0;
  wire Add1_out1_carry__0_i_5_n_0;
  wire Add1_out1_carry__0_i_6_n_0;
  wire Add1_out1_carry__0_i_7_n_0;
  wire Add1_out1_carry__0_i_8_n_0;
  wire Add1_out1_carry__0_n_0;
  wire Add1_out1_carry__0_n_1;
  wire Add1_out1_carry__0_n_2;
  wire Add1_out1_carry__0_n_3;
  wire Add1_out1_carry__0_n_4;
  wire Add1_out1_carry__0_n_5;
  wire Add1_out1_carry__0_n_6;
  wire Add1_out1_carry__0_n_7;
  wire Add1_out1_carry__1_n_4;
  wire Add1_out1_carry__1_n_5;
  wire Add1_out1_carry__1_n_6;
  wire Add1_out1_carry__1_n_7;
  wire Add1_out1_carry_i_1_n_0;
  wire Add1_out1_carry_i_2_n_0;
  wire Add1_out1_carry_i_3_n_0;
  wire Add1_out1_carry_i_4_n_0;
  wire Add1_out1_carry_i_5_n_0;
  wire Add1_out1_carry_i_6_n_0;
  wire Add1_out1_carry_i_7_n_0;
  wire Add1_out1_carry_i_8_n_0;
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
  wire [20:0]Counter_Ctrl_out3;
  wire [6:0]Counter_Ctrl_out4_1_reg;
  wire Delay6_out1;
  wire Delay6_out1_i_2_n_0;
  wire Delay6_out1_i_3_n_0;
  wire Delay6_out1_i_4_n_0;
  wire Delay6_out1_i_5_n_0;
  wire Delay6_out1_i_6_n_0;
  wire \HDL_Counter2_count[0]_i_10_n_0 ;
  wire \HDL_Counter2_count[0]_i_11_n_0 ;
  wire \HDL_Counter2_count[0]_i_3_n_0 ;
  wire \HDL_Counter2_count[0]_i_4_n_0 ;
  wire \HDL_Counter2_count[0]_i_5_n_0 ;
  wire \HDL_Counter2_count[0]_i_6_n_0 ;
  wire \HDL_Counter2_count[0]_i_7_n_0 ;
  wire \HDL_Counter2_count[0]_i_8_n_0 ;
  wire \HDL_Counter2_count[0]_i_9_n_0 ;
  wire \HDL_Counter2_count[16]_i_2_n_0 ;
  wire \HDL_Counter2_count[16]_i_3_n_0 ;
  wire \HDL_Counter2_count[16]_i_4_n_0 ;
  wire \HDL_Counter2_count[16]_i_5_n_0 ;
  wire \HDL_Counter2_count[8]_i_2_n_0 ;
  wire \HDL_Counter2_count[8]_i_3_n_0 ;
  wire \HDL_Counter2_count[8]_i_4_n_0 ;
  wire \HDL_Counter2_count[8]_i_5_n_0 ;
  wire \HDL_Counter2_count[8]_i_6_n_0 ;
  wire \HDL_Counter2_count[8]_i_7_n_0 ;
  wire \HDL_Counter2_count[8]_i_8_n_0 ;
  wire \HDL_Counter2_count[8]_i_9_n_0 ;
  wire [19:0]HDL_Counter2_count_reg;
  wire [7:0]\HDL_Counter2_count_reg[0] ;
  wire [3:0]\HDL_Counter2_count_reg[0]_0 ;
  wire \HDL_Counter2_count_reg[0]_i_2_n_0 ;
  wire \HDL_Counter2_count_reg[0]_i_2_n_1 ;
  wire \HDL_Counter2_count_reg[0]_i_2_n_2 ;
  wire \HDL_Counter2_count_reg[0]_i_2_n_3 ;
  wire \HDL_Counter2_count_reg[0]_i_2_n_4 ;
  wire \HDL_Counter2_count_reg[0]_i_2_n_5 ;
  wire \HDL_Counter2_count_reg[0]_i_2_n_6 ;
  wire \HDL_Counter2_count_reg[0]_i_2_n_7 ;
  wire \HDL_Counter2_count_reg[16]_i_1_n_5 ;
  wire \HDL_Counter2_count_reg[16]_i_1_n_6 ;
  wire \HDL_Counter2_count_reg[16]_i_1_n_7 ;
  wire \HDL_Counter2_count_reg[8]_i_1_n_0 ;
  wire \HDL_Counter2_count_reg[8]_i_1_n_1 ;
  wire \HDL_Counter2_count_reg[8]_i_1_n_2 ;
  wire \HDL_Counter2_count_reg[8]_i_1_n_3 ;
  wire \HDL_Counter2_count_reg[8]_i_1_n_4 ;
  wire \HDL_Counter2_count_reg[8]_i_1_n_5 ;
  wire \HDL_Counter2_count_reg[8]_i_1_n_6 ;
  wire \HDL_Counter2_count_reg[8]_i_1_n_7 ;
  wire IPCORE_CLK;
  wire Logical_Operator_out10_carry__0_i_1_n_0;
  wire Logical_Operator_out10_carry__0_i_2_n_0;
  wire Logical_Operator_out10_carry__0_i_3_n_0;
  wire Logical_Operator_out10_carry__0_i_4_n_0;
  wire Logical_Operator_out10_carry__0_n_7;
  wire Logical_Operator_out10_carry_i_10__2_n_0;
  wire Logical_Operator_out10_carry_i_11__2_n_0;
  wire Logical_Operator_out10_carry_i_12__2_n_0;
  wire Logical_Operator_out10_carry_i_13__2_n_0;
  wire Logical_Operator_out10_carry_i_14__2_n_0;
  wire Logical_Operator_out10_carry_i_15_n_0;
  wire Logical_Operator_out10_carry_i_16_n_0;
  wire Logical_Operator_out10_carry_i_1__2_n_0;
  wire Logical_Operator_out10_carry_i_2__2_n_0;
  wire Logical_Operator_out10_carry_i_3__2_n_0;
  wire Logical_Operator_out10_carry_i_4__2_n_0;
  wire Logical_Operator_out10_carry_i_5__2_n_0;
  wire Logical_Operator_out10_carry_i_6__2_n_0;
  wire Logical_Operator_out10_carry_i_7__2_n_0;
  wire Logical_Operator_out10_carry_i_8__2_n_0;
  wire Logical_Operator_out10_carry_i_9__2_n_0;
  wire Logical_Operator_out10_carry_n_0;
  wire Logical_Operator_out10_carry_n_1;
  wire Logical_Operator_out10_carry_n_2;
  wire Logical_Operator_out10_carry_n_3;
  wire Logical_Operator_out10_carry_n_4;
  wire Logical_Operator_out10_carry_n_5;
  wire Logical_Operator_out10_carry_n_6;
  wire Logical_Operator_out10_carry_n_7;
  wire [7:0]O;
  wire Period_Center0_carry_n_2;
  wire Period_Center0_carry_n_3;
  wire Period_Center0_carry_n_4;
  wire Period_Center0_carry_n_5;
  wire Period_Center0_carry_n_6;
  wire Period_Center0_carry_n_7;
  wire RSTP;
  wire Relational_Operator4_relop1;
  wire [3:0]S;
  wire direction_ctrl;
  wire [19:0]maximum_counter_value_1;
  wire [7:4]NLW_Add1_out1_carry__1_CO_UNCONNECTED;
  wire [7:5]NLW_Add1_out1_carry__1_O_UNCONNECTED;
  wire [7:3]\NLW_HDL_Counter2_count_reg[16]_i_1_CO_UNCONNECTED ;
  wire [7:4]\NLW_HDL_Counter2_count_reg[16]_i_1_O_UNCONNECTED ;
  wire [7:0]NLW_Logical_Operator_out10_carry_O_UNCONNECTED;
  wire [7:2]NLW_Logical_Operator_out10_carry__0_CO_UNCONNECTED;
  wire [7:0]NLW_Logical_Operator_out10_carry__0_O_UNCONNECTED;
  wire [7:7]NLW_Period_Center0_carry_CO_UNCONNECTED;
  wire [7:0]NLW_Period_Center0_carry_O_UNCONNECTED;

  CARRY8 Add1_out1_carry
       (.CI(1'b1),
        .CI_TOP(1'b0),
        .CO({Add1_out1_carry_n_0,Add1_out1_carry_n_1,Add1_out1_carry_n_2,Add1_out1_carry_n_3,Add1_out1_carry_n_4,Add1_out1_carry_n_5,Add1_out1_carry_n_6,Add1_out1_carry_n_7}),
        .DI(HDL_Counter2_count_reg[7:0]),
        .O(Counter_Ctrl_out3[7:0]),
        .S({Add1_out1_carry_i_1_n_0,Add1_out1_carry_i_2_n_0,Add1_out1_carry_i_3_n_0,Add1_out1_carry_i_4_n_0,Add1_out1_carry_i_5_n_0,Add1_out1_carry_i_6_n_0,Add1_out1_carry_i_7_n_0,Add1_out1_carry_i_8_n_0}));
  CARRY8 Add1_out1_carry__0
       (.CI(Add1_out1_carry_n_0),
        .CI_TOP(1'b0),
        .CO({Add1_out1_carry__0_n_0,Add1_out1_carry__0_n_1,Add1_out1_carry__0_n_2,Add1_out1_carry__0_n_3,Add1_out1_carry__0_n_4,Add1_out1_carry__0_n_5,Add1_out1_carry__0_n_6,Add1_out1_carry__0_n_7}),
        .DI(HDL_Counter2_count_reg[15:8]),
        .O(Counter_Ctrl_out3[15:8]),
        .S({Add1_out1_carry__0_i_1_n_0,Add1_out1_carry__0_i_2_n_0,Add1_out1_carry__0_i_3_n_0,Add1_out1_carry__0_i_4_n_0,Add1_out1_carry__0_i_5_n_0,Add1_out1_carry__0_i_6_n_0,Add1_out1_carry__0_i_7_n_0,Add1_out1_carry__0_i_8_n_0}));
  LUT2 #(
    .INIT(4'h9)) 
    Add1_out1_carry__0_i_1
       (.I0(HDL_Counter2_count_reg[15]),
        .I1(maximum_counter_value_1[15]),
        .O(Add1_out1_carry__0_i_1_n_0));
  LUT2 #(
    .INIT(4'h9)) 
    Add1_out1_carry__0_i_2
       (.I0(HDL_Counter2_count_reg[14]),
        .I1(maximum_counter_value_1[14]),
        .O(Add1_out1_carry__0_i_2_n_0));
  LUT2 #(
    .INIT(4'h9)) 
    Add1_out1_carry__0_i_3
       (.I0(HDL_Counter2_count_reg[13]),
        .I1(maximum_counter_value_1[13]),
        .O(Add1_out1_carry__0_i_3_n_0));
  LUT2 #(
    .INIT(4'h9)) 
    Add1_out1_carry__0_i_4
       (.I0(HDL_Counter2_count_reg[12]),
        .I1(maximum_counter_value_1[12]),
        .O(Add1_out1_carry__0_i_4_n_0));
  LUT2 #(
    .INIT(4'h9)) 
    Add1_out1_carry__0_i_5
       (.I0(HDL_Counter2_count_reg[11]),
        .I1(maximum_counter_value_1[11]),
        .O(Add1_out1_carry__0_i_5_n_0));
  LUT2 #(
    .INIT(4'h9)) 
    Add1_out1_carry__0_i_6
       (.I0(HDL_Counter2_count_reg[10]),
        .I1(maximum_counter_value_1[10]),
        .O(Add1_out1_carry__0_i_6_n_0));
  LUT2 #(
    .INIT(4'h9)) 
    Add1_out1_carry__0_i_7
       (.I0(HDL_Counter2_count_reg[9]),
        .I1(maximum_counter_value_1[9]),
        .O(Add1_out1_carry__0_i_7_n_0));
  LUT2 #(
    .INIT(4'h9)) 
    Add1_out1_carry__0_i_8
       (.I0(HDL_Counter2_count_reg[8]),
        .I1(maximum_counter_value_1[8]),
        .O(Add1_out1_carry__0_i_8_n_0));
  CARRY8 Add1_out1_carry__1
       (.CI(Add1_out1_carry__0_n_0),
        .CI_TOP(1'b0),
        .CO({NLW_Add1_out1_carry__1_CO_UNCONNECTED[7:4],Add1_out1_carry__1_n_4,Add1_out1_carry__1_n_5,Add1_out1_carry__1_n_6,Add1_out1_carry__1_n_7}),
        .DI({1'b0,1'b0,1'b0,1'b0,HDL_Counter2_count_reg[19:16]}),
        .O({NLW_Add1_out1_carry__1_O_UNCONNECTED[7:5],Counter_Ctrl_out3[20:16]}),
        .S({1'b0,1'b0,1'b0,1'b1,S}));
  LUT2 #(
    .INIT(4'h9)) 
    Add1_out1_carry_i_1
       (.I0(HDL_Counter2_count_reg[7]),
        .I1(maximum_counter_value_1[7]),
        .O(Add1_out1_carry_i_1_n_0));
  LUT2 #(
    .INIT(4'h9)) 
    Add1_out1_carry_i_2
       (.I0(HDL_Counter2_count_reg[6]),
        .I1(maximum_counter_value_1[6]),
        .O(Add1_out1_carry_i_2_n_0));
  LUT2 #(
    .INIT(4'h9)) 
    Add1_out1_carry_i_3
       (.I0(HDL_Counter2_count_reg[5]),
        .I1(maximum_counter_value_1[5]),
        .O(Add1_out1_carry_i_3_n_0));
  LUT2 #(
    .INIT(4'h9)) 
    Add1_out1_carry_i_4
       (.I0(HDL_Counter2_count_reg[4]),
        .I1(maximum_counter_value_1[4]),
        .O(Add1_out1_carry_i_4_n_0));
  LUT2 #(
    .INIT(4'h9)) 
    Add1_out1_carry_i_5
       (.I0(HDL_Counter2_count_reg[3]),
        .I1(maximum_counter_value_1[3]),
        .O(Add1_out1_carry_i_5_n_0));
  LUT2 #(
    .INIT(4'h9)) 
    Add1_out1_carry_i_6
       (.I0(HDL_Counter2_count_reg[2]),
        .I1(maximum_counter_value_1[2]),
        .O(Add1_out1_carry_i_6_n_0));
  LUT2 #(
    .INIT(4'h9)) 
    Add1_out1_carry_i_7
       (.I0(HDL_Counter2_count_reg[1]),
        .I1(maximum_counter_value_1[1]),
        .O(Add1_out1_carry_i_7_n_0));
  LUT2 #(
    .INIT(4'h9)) 
    Add1_out1_carry_i_8
       (.I0(HDL_Counter2_count_reg[0]),
        .I1(maximum_counter_value_1[0]),
        .O(Add1_out1_carry_i_8_n_0));
  LUT5 #(
    .INIT(32'h55550001)) 
    Delay6_out1_i_1
       (.I0(Relational_Operator4_relop1),
        .I1(Delay6_out1_i_2_n_0),
        .I2(Delay6_out1_i_3_n_0),
        .I3(HDL_Counter2_count_reg[0]),
        .I4(Delay6_out1),
        .O(direction_ctrl));
  LUT5 #(
    .INIT(32'hFFFFFFFE)) 
    Delay6_out1_i_2
       (.I0(HDL_Counter2_count_reg[13]),
        .I1(HDL_Counter2_count_reg[10]),
        .I2(HDL_Counter2_count_reg[15]),
        .I3(HDL_Counter2_count_reg[12]),
        .I4(Delay6_out1_i_4_n_0),
        .O(Delay6_out1_i_2_n_0));
  LUT5 #(
    .INIT(32'hFFFFFFFE)) 
    Delay6_out1_i_3
       (.I0(HDL_Counter2_count_reg[3]),
        .I1(HDL_Counter2_count_reg[2]),
        .I2(HDL_Counter2_count_reg[18]),
        .I3(Delay6_out1_i_5_n_0),
        .I4(Delay6_out1_i_6_n_0),
        .O(Delay6_out1_i_3_n_0));
  LUT4 #(
    .INIT(16'hFFFE)) 
    Delay6_out1_i_4
       (.I0(HDL_Counter2_count_reg[8]),
        .I1(HDL_Counter2_count_reg[11]),
        .I2(HDL_Counter2_count_reg[6]),
        .I3(HDL_Counter2_count_reg[9]),
        .O(Delay6_out1_i_4_n_0));
  LUT4 #(
    .INIT(16'hFFFE)) 
    Delay6_out1_i_5
       (.I0(HDL_Counter2_count_reg[4]),
        .I1(HDL_Counter2_count_reg[7]),
        .I2(HDL_Counter2_count_reg[1]),
        .I3(HDL_Counter2_count_reg[5]),
        .O(Delay6_out1_i_5_n_0));
  LUT4 #(
    .INIT(16'hFFFE)) 
    Delay6_out1_i_6
       (.I0(HDL_Counter2_count_reg[16]),
        .I1(HDL_Counter2_count_reg[19]),
        .I2(HDL_Counter2_count_reg[14]),
        .I3(HDL_Counter2_count_reg[17]),
        .O(Delay6_out1_i_6_n_0));
  FDRE Delay6_out1_reg
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(direction_ctrl),
        .Q(Delay6_out1),
        .R(RSTP));
  LUT6 #(
    .INIT(64'h55550001AAAAFFFE)) 
    \HDL_Counter2_count[0]_i_10 
       (.I0(Relational_Operator4_relop1),
        .I1(Delay6_out1_i_2_n_0),
        .I2(Delay6_out1_i_3_n_0),
        .I3(HDL_Counter2_count_reg[0]),
        .I4(Delay6_out1),
        .I5(HDL_Counter2_count_reg[1]),
        .O(\HDL_Counter2_count[0]_i_10_n_0 ));
  LUT5 #(
    .INIT(32'hAA55FF01)) 
    \HDL_Counter2_count[0]_i_11 
       (.I0(Relational_Operator4_relop1),
        .I1(Delay6_out1_i_2_n_0),
        .I2(Delay6_out1_i_3_n_0),
        .I3(HDL_Counter2_count_reg[0]),
        .I4(Delay6_out1),
        .O(\HDL_Counter2_count[0]_i_11_n_0 ));
  LUT5 #(
    .INIT(32'hAAAAFFFE)) 
    \HDL_Counter2_count[0]_i_3 
       (.I0(Relational_Operator4_relop1),
        .I1(Delay6_out1_i_2_n_0),
        .I2(Delay6_out1_i_3_n_0),
        .I3(HDL_Counter2_count_reg[0]),
        .I4(Delay6_out1),
        .O(\HDL_Counter2_count[0]_i_3_n_0 ));
  LUT6 #(
    .INIT(64'h55550001AAAAFFFE)) 
    \HDL_Counter2_count[0]_i_4 
       (.I0(Relational_Operator4_relop1),
        .I1(Delay6_out1_i_2_n_0),
        .I2(Delay6_out1_i_3_n_0),
        .I3(HDL_Counter2_count_reg[0]),
        .I4(Delay6_out1),
        .I5(HDL_Counter2_count_reg[7]),
        .O(\HDL_Counter2_count[0]_i_4_n_0 ));
  LUT6 #(
    .INIT(64'h55550001AAAAFFFE)) 
    \HDL_Counter2_count[0]_i_5 
       (.I0(Relational_Operator4_relop1),
        .I1(Delay6_out1_i_2_n_0),
        .I2(Delay6_out1_i_3_n_0),
        .I3(HDL_Counter2_count_reg[0]),
        .I4(Delay6_out1),
        .I5(HDL_Counter2_count_reg[6]),
        .O(\HDL_Counter2_count[0]_i_5_n_0 ));
  LUT6 #(
    .INIT(64'h55550001AAAAFFFE)) 
    \HDL_Counter2_count[0]_i_6 
       (.I0(Relational_Operator4_relop1),
        .I1(Delay6_out1_i_2_n_0),
        .I2(Delay6_out1_i_3_n_0),
        .I3(HDL_Counter2_count_reg[0]),
        .I4(Delay6_out1),
        .I5(HDL_Counter2_count_reg[5]),
        .O(\HDL_Counter2_count[0]_i_6_n_0 ));
  LUT6 #(
    .INIT(64'h55550001AAAAFFFE)) 
    \HDL_Counter2_count[0]_i_7 
       (.I0(Relational_Operator4_relop1),
        .I1(Delay6_out1_i_2_n_0),
        .I2(Delay6_out1_i_3_n_0),
        .I3(HDL_Counter2_count_reg[0]),
        .I4(Delay6_out1),
        .I5(HDL_Counter2_count_reg[4]),
        .O(\HDL_Counter2_count[0]_i_7_n_0 ));
  LUT6 #(
    .INIT(64'h55550001AAAAFFFE)) 
    \HDL_Counter2_count[0]_i_8 
       (.I0(Relational_Operator4_relop1),
        .I1(Delay6_out1_i_2_n_0),
        .I2(Delay6_out1_i_3_n_0),
        .I3(HDL_Counter2_count_reg[0]),
        .I4(Delay6_out1),
        .I5(HDL_Counter2_count_reg[3]),
        .O(\HDL_Counter2_count[0]_i_8_n_0 ));
  LUT6 #(
    .INIT(64'h55550001AAAAFFFE)) 
    \HDL_Counter2_count[0]_i_9 
       (.I0(Relational_Operator4_relop1),
        .I1(Delay6_out1_i_2_n_0),
        .I2(Delay6_out1_i_3_n_0),
        .I3(HDL_Counter2_count_reg[0]),
        .I4(Delay6_out1),
        .I5(HDL_Counter2_count_reg[2]),
        .O(\HDL_Counter2_count[0]_i_9_n_0 ));
  LUT6 #(
    .INIT(64'h55550001AAAAFFFE)) 
    \HDL_Counter2_count[16]_i_2 
       (.I0(Relational_Operator4_relop1),
        .I1(Delay6_out1_i_2_n_0),
        .I2(Delay6_out1_i_3_n_0),
        .I3(HDL_Counter2_count_reg[0]),
        .I4(Delay6_out1),
        .I5(HDL_Counter2_count_reg[19]),
        .O(\HDL_Counter2_count[16]_i_2_n_0 ));
  LUT6 #(
    .INIT(64'h55550001AAAAFFFE)) 
    \HDL_Counter2_count[16]_i_3 
       (.I0(Relational_Operator4_relop1),
        .I1(Delay6_out1_i_2_n_0),
        .I2(Delay6_out1_i_3_n_0),
        .I3(HDL_Counter2_count_reg[0]),
        .I4(Delay6_out1),
        .I5(HDL_Counter2_count_reg[18]),
        .O(\HDL_Counter2_count[16]_i_3_n_0 ));
  LUT6 #(
    .INIT(64'h55550001AAAAFFFE)) 
    \HDL_Counter2_count[16]_i_4 
       (.I0(Relational_Operator4_relop1),
        .I1(Delay6_out1_i_2_n_0),
        .I2(Delay6_out1_i_3_n_0),
        .I3(HDL_Counter2_count_reg[0]),
        .I4(Delay6_out1),
        .I5(HDL_Counter2_count_reg[17]),
        .O(\HDL_Counter2_count[16]_i_4_n_0 ));
  LUT6 #(
    .INIT(64'h55550001AAAAFFFE)) 
    \HDL_Counter2_count[16]_i_5 
       (.I0(Relational_Operator4_relop1),
        .I1(Delay6_out1_i_2_n_0),
        .I2(Delay6_out1_i_3_n_0),
        .I3(HDL_Counter2_count_reg[0]),
        .I4(Delay6_out1),
        .I5(HDL_Counter2_count_reg[16]),
        .O(\HDL_Counter2_count[16]_i_5_n_0 ));
  LUT6 #(
    .INIT(64'h55550001AAAAFFFE)) 
    \HDL_Counter2_count[8]_i_2 
       (.I0(Relational_Operator4_relop1),
        .I1(Delay6_out1_i_2_n_0),
        .I2(Delay6_out1_i_3_n_0),
        .I3(HDL_Counter2_count_reg[0]),
        .I4(Delay6_out1),
        .I5(HDL_Counter2_count_reg[15]),
        .O(\HDL_Counter2_count[8]_i_2_n_0 ));
  LUT6 #(
    .INIT(64'h55550001AAAAFFFE)) 
    \HDL_Counter2_count[8]_i_3 
       (.I0(Relational_Operator4_relop1),
        .I1(Delay6_out1_i_2_n_0),
        .I2(Delay6_out1_i_3_n_0),
        .I3(HDL_Counter2_count_reg[0]),
        .I4(Delay6_out1),
        .I5(HDL_Counter2_count_reg[14]),
        .O(\HDL_Counter2_count[8]_i_3_n_0 ));
  LUT6 #(
    .INIT(64'h55550001AAAAFFFE)) 
    \HDL_Counter2_count[8]_i_4 
       (.I0(Relational_Operator4_relop1),
        .I1(Delay6_out1_i_2_n_0),
        .I2(Delay6_out1_i_3_n_0),
        .I3(HDL_Counter2_count_reg[0]),
        .I4(Delay6_out1),
        .I5(HDL_Counter2_count_reg[13]),
        .O(\HDL_Counter2_count[8]_i_4_n_0 ));
  LUT6 #(
    .INIT(64'h55550001AAAAFFFE)) 
    \HDL_Counter2_count[8]_i_5 
       (.I0(Relational_Operator4_relop1),
        .I1(Delay6_out1_i_2_n_0),
        .I2(Delay6_out1_i_3_n_0),
        .I3(HDL_Counter2_count_reg[0]),
        .I4(Delay6_out1),
        .I5(HDL_Counter2_count_reg[12]),
        .O(\HDL_Counter2_count[8]_i_5_n_0 ));
  LUT6 #(
    .INIT(64'h55550001AAAAFFFE)) 
    \HDL_Counter2_count[8]_i_6 
       (.I0(Relational_Operator4_relop1),
        .I1(Delay6_out1_i_2_n_0),
        .I2(Delay6_out1_i_3_n_0),
        .I3(HDL_Counter2_count_reg[0]),
        .I4(Delay6_out1),
        .I5(HDL_Counter2_count_reg[11]),
        .O(\HDL_Counter2_count[8]_i_6_n_0 ));
  LUT6 #(
    .INIT(64'h55550001AAAAFFFE)) 
    \HDL_Counter2_count[8]_i_7 
       (.I0(Relational_Operator4_relop1),
        .I1(Delay6_out1_i_2_n_0),
        .I2(Delay6_out1_i_3_n_0),
        .I3(HDL_Counter2_count_reg[0]),
        .I4(Delay6_out1),
        .I5(HDL_Counter2_count_reg[10]),
        .O(\HDL_Counter2_count[8]_i_7_n_0 ));
  LUT6 #(
    .INIT(64'h55550001AAAAFFFE)) 
    \HDL_Counter2_count[8]_i_8 
       (.I0(Relational_Operator4_relop1),
        .I1(Delay6_out1_i_2_n_0),
        .I2(Delay6_out1_i_3_n_0),
        .I3(HDL_Counter2_count_reg[0]),
        .I4(Delay6_out1),
        .I5(HDL_Counter2_count_reg[9]),
        .O(\HDL_Counter2_count[8]_i_8_n_0 ));
  LUT6 #(
    .INIT(64'h55550001AAAAFFFE)) 
    \HDL_Counter2_count[8]_i_9 
       (.I0(Relational_Operator4_relop1),
        .I1(Delay6_out1_i_2_n_0),
        .I2(Delay6_out1_i_3_n_0),
        .I3(HDL_Counter2_count_reg[0]),
        .I4(Delay6_out1),
        .I5(HDL_Counter2_count_reg[8]),
        .O(\HDL_Counter2_count[8]_i_9_n_0 ));
  (* ADDER_THRESHOLD = "16" *) 
  CARRY8 \HDL_Counter2_count_reg[0]_i_2 
       (.CI(\HDL_Counter2_count[0]_i_3_n_0 ),
        .CI_TOP(1'b0),
        .CO({\HDL_Counter2_count_reg[0]_i_2_n_0 ,\HDL_Counter2_count_reg[0]_i_2_n_1 ,\HDL_Counter2_count_reg[0]_i_2_n_2 ,\HDL_Counter2_count_reg[0]_i_2_n_3 ,\HDL_Counter2_count_reg[0]_i_2_n_4 ,\HDL_Counter2_count_reg[0]_i_2_n_5 ,\HDL_Counter2_count_reg[0]_i_2_n_6 ,\HDL_Counter2_count_reg[0]_i_2_n_7 }),
        .DI({\HDL_Counter2_count[0]_i_3_n_0 ,\HDL_Counter2_count[0]_i_3_n_0 ,\HDL_Counter2_count[0]_i_3_n_0 ,\HDL_Counter2_count[0]_i_3_n_0 ,\HDL_Counter2_count[0]_i_3_n_0 ,\HDL_Counter2_count[0]_i_3_n_0 ,\HDL_Counter2_count[0]_i_3_n_0 ,HDL_Counter2_count_reg[0]}),
        .O(O),
        .S({\HDL_Counter2_count[0]_i_4_n_0 ,\HDL_Counter2_count[0]_i_5_n_0 ,\HDL_Counter2_count[0]_i_6_n_0 ,\HDL_Counter2_count[0]_i_7_n_0 ,\HDL_Counter2_count[0]_i_8_n_0 ,\HDL_Counter2_count[0]_i_9_n_0 ,\HDL_Counter2_count[0]_i_10_n_0 ,\HDL_Counter2_count[0]_i_11_n_0 }));
  (* ADDER_THRESHOLD = "16" *) 
  CARRY8 \HDL_Counter2_count_reg[16]_i_1 
       (.CI(\HDL_Counter2_count_reg[8]_i_1_n_0 ),
        .CI_TOP(1'b0),
        .CO({\NLW_HDL_Counter2_count_reg[16]_i_1_CO_UNCONNECTED [7:3],\HDL_Counter2_count_reg[16]_i_1_n_5 ,\HDL_Counter2_count_reg[16]_i_1_n_6 ,\HDL_Counter2_count_reg[16]_i_1_n_7 }),
        .DI({1'b0,1'b0,1'b0,1'b0,1'b0,\HDL_Counter2_count[0]_i_3_n_0 ,\HDL_Counter2_count[0]_i_3_n_0 ,\HDL_Counter2_count[0]_i_3_n_0 }),
        .O({\NLW_HDL_Counter2_count_reg[16]_i_1_O_UNCONNECTED [7:4],\HDL_Counter2_count_reg[0]_0 }),
        .S({1'b0,1'b0,1'b0,1'b0,\HDL_Counter2_count[16]_i_2_n_0 ,\HDL_Counter2_count[16]_i_3_n_0 ,\HDL_Counter2_count[16]_i_4_n_0 ,\HDL_Counter2_count[16]_i_5_n_0 }));
  (* ADDER_THRESHOLD = "16" *) 
  CARRY8 \HDL_Counter2_count_reg[8]_i_1 
       (.CI(\HDL_Counter2_count_reg[0]_i_2_n_0 ),
        .CI_TOP(1'b0),
        .CO({\HDL_Counter2_count_reg[8]_i_1_n_0 ,\HDL_Counter2_count_reg[8]_i_1_n_1 ,\HDL_Counter2_count_reg[8]_i_1_n_2 ,\HDL_Counter2_count_reg[8]_i_1_n_3 ,\HDL_Counter2_count_reg[8]_i_1_n_4 ,\HDL_Counter2_count_reg[8]_i_1_n_5 ,\HDL_Counter2_count_reg[8]_i_1_n_6 ,\HDL_Counter2_count_reg[8]_i_1_n_7 }),
        .DI({\HDL_Counter2_count[0]_i_3_n_0 ,\HDL_Counter2_count[0]_i_3_n_0 ,\HDL_Counter2_count[0]_i_3_n_0 ,\HDL_Counter2_count[0]_i_3_n_0 ,\HDL_Counter2_count[0]_i_3_n_0 ,\HDL_Counter2_count[0]_i_3_n_0 ,\HDL_Counter2_count[0]_i_3_n_0 ,\HDL_Counter2_count[0]_i_3_n_0 }),
        .O(\HDL_Counter2_count_reg[0] ),
        .S({\HDL_Counter2_count[8]_i_2_n_0 ,\HDL_Counter2_count[8]_i_3_n_0 ,\HDL_Counter2_count[8]_i_4_n_0 ,\HDL_Counter2_count[8]_i_5_n_0 ,\HDL_Counter2_count[8]_i_6_n_0 ,\HDL_Counter2_count[8]_i_7_n_0 ,\HDL_Counter2_count[8]_i_8_n_0 ,\HDL_Counter2_count[8]_i_9_n_0 }));
  (* COMPARATOR_THRESHOLD = "11" *) 
  CARRY8 Logical_Operator_out10_carry
       (.CI(1'b1),
        .CI_TOP(1'b0),
        .CO({Logical_Operator_out10_carry_n_0,Logical_Operator_out10_carry_n_1,Logical_Operator_out10_carry_n_2,Logical_Operator_out10_carry_n_3,Logical_Operator_out10_carry_n_4,Logical_Operator_out10_carry_n_5,Logical_Operator_out10_carry_n_6,Logical_Operator_out10_carry_n_7}),
        .DI({Logical_Operator_out10_carry_i_1__2_n_0,Logical_Operator_out10_carry_i_2__2_n_0,Logical_Operator_out10_carry_i_3__2_n_0,Logical_Operator_out10_carry_i_4__2_n_0,Logical_Operator_out10_carry_i_5__2_n_0,Logical_Operator_out10_carry_i_6__2_n_0,Logical_Operator_out10_carry_i_7__2_n_0,Logical_Operator_out10_carry_i_8__2_n_0}),
        .O(NLW_Logical_Operator_out10_carry_O_UNCONNECTED[7:0]),
        .S({Logical_Operator_out10_carry_i_9__2_n_0,Logical_Operator_out10_carry_i_10__2_n_0,Logical_Operator_out10_carry_i_11__2_n_0,Logical_Operator_out10_carry_i_12__2_n_0,Logical_Operator_out10_carry_i_13__2_n_0,Logical_Operator_out10_carry_i_14__2_n_0,Logical_Operator_out10_carry_i_15_n_0,Logical_Operator_out10_carry_i_16_n_0}));
  (* COMPARATOR_THRESHOLD = "11" *) 
  CARRY8 Logical_Operator_out10_carry__0
       (.CI(Logical_Operator_out10_carry_n_0),
        .CI_TOP(1'b0),
        .CO({NLW_Logical_Operator_out10_carry__0_CO_UNCONNECTED[7:2],Relational_Operator4_relop1,Logical_Operator_out10_carry__0_n_7}),
        .DI({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,Logical_Operator_out10_carry__0_i_1_n_0,Logical_Operator_out10_carry__0_i_2_n_0}),
        .O(NLW_Logical_Operator_out10_carry__0_O_UNCONNECTED[7:0]),
        .S({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,Logical_Operator_out10_carry__0_i_3_n_0,Logical_Operator_out10_carry__0_i_4_n_0}));
  LUT4 #(
    .INIT(16'h22B2)) 
    Logical_Operator_out10_carry__0_i_1
       (.I0(HDL_Counter2_count_reg[19]),
        .I1(maximum_counter_value_1[19]),
        .I2(HDL_Counter2_count_reg[18]),
        .I3(maximum_counter_value_1[18]),
        .O(Logical_Operator_out10_carry__0_i_1_n_0));
  LUT4 #(
    .INIT(16'h22B2)) 
    Logical_Operator_out10_carry__0_i_2
       (.I0(HDL_Counter2_count_reg[17]),
        .I1(maximum_counter_value_1[17]),
        .I2(HDL_Counter2_count_reg[16]),
        .I3(maximum_counter_value_1[16]),
        .O(Logical_Operator_out10_carry__0_i_2_n_0));
  LUT4 #(
    .INIT(16'h9009)) 
    Logical_Operator_out10_carry__0_i_3
       (.I0(HDL_Counter2_count_reg[18]),
        .I1(maximum_counter_value_1[18]),
        .I2(HDL_Counter2_count_reg[19]),
        .I3(maximum_counter_value_1[19]),
        .O(Logical_Operator_out10_carry__0_i_3_n_0));
  LUT4 #(
    .INIT(16'h9009)) 
    Logical_Operator_out10_carry__0_i_4
       (.I0(HDL_Counter2_count_reg[16]),
        .I1(maximum_counter_value_1[16]),
        .I2(HDL_Counter2_count_reg[17]),
        .I3(maximum_counter_value_1[17]),
        .O(Logical_Operator_out10_carry__0_i_4_n_0));
  LUT4 #(
    .INIT(16'h9009)) 
    Logical_Operator_out10_carry_i_10__2
       (.I0(HDL_Counter2_count_reg[12]),
        .I1(maximum_counter_value_1[12]),
        .I2(HDL_Counter2_count_reg[13]),
        .I3(maximum_counter_value_1[13]),
        .O(Logical_Operator_out10_carry_i_10__2_n_0));
  LUT4 #(
    .INIT(16'h9009)) 
    Logical_Operator_out10_carry_i_11__2
       (.I0(HDL_Counter2_count_reg[10]),
        .I1(maximum_counter_value_1[10]),
        .I2(HDL_Counter2_count_reg[11]),
        .I3(maximum_counter_value_1[11]),
        .O(Logical_Operator_out10_carry_i_11__2_n_0));
  LUT4 #(
    .INIT(16'h9009)) 
    Logical_Operator_out10_carry_i_12__2
       (.I0(HDL_Counter2_count_reg[9]),
        .I1(maximum_counter_value_1[9]),
        .I2(HDL_Counter2_count_reg[8]),
        .I3(maximum_counter_value_1[8]),
        .O(Logical_Operator_out10_carry_i_12__2_n_0));
  LUT4 #(
    .INIT(16'h9009)) 
    Logical_Operator_out10_carry_i_13__2
       (.I0(HDL_Counter2_count_reg[6]),
        .I1(maximum_counter_value_1[6]),
        .I2(HDL_Counter2_count_reg[7]),
        .I3(maximum_counter_value_1[7]),
        .O(Logical_Operator_out10_carry_i_13__2_n_0));
  LUT4 #(
    .INIT(16'h9009)) 
    Logical_Operator_out10_carry_i_14__2
       (.I0(HDL_Counter2_count_reg[4]),
        .I1(maximum_counter_value_1[4]),
        .I2(HDL_Counter2_count_reg[5]),
        .I3(maximum_counter_value_1[5]),
        .O(Logical_Operator_out10_carry_i_14__2_n_0));
  LUT4 #(
    .INIT(16'h9009)) 
    Logical_Operator_out10_carry_i_15
       (.I0(HDL_Counter2_count_reg[3]),
        .I1(maximum_counter_value_1[3]),
        .I2(HDL_Counter2_count_reg[2]),
        .I3(maximum_counter_value_1[2]),
        .O(Logical_Operator_out10_carry_i_15_n_0));
  LUT4 #(
    .INIT(16'h9009)) 
    Logical_Operator_out10_carry_i_16
       (.I0(HDL_Counter2_count_reg[0]),
        .I1(maximum_counter_value_1[0]),
        .I2(HDL_Counter2_count_reg[1]),
        .I3(maximum_counter_value_1[1]),
        .O(Logical_Operator_out10_carry_i_16_n_0));
  LUT4 #(
    .INIT(16'h22B2)) 
    Logical_Operator_out10_carry_i_1__2
       (.I0(HDL_Counter2_count_reg[15]),
        .I1(maximum_counter_value_1[15]),
        .I2(HDL_Counter2_count_reg[14]),
        .I3(maximum_counter_value_1[14]),
        .O(Logical_Operator_out10_carry_i_1__2_n_0));
  LUT4 #(
    .INIT(16'h22B2)) 
    Logical_Operator_out10_carry_i_2__2
       (.I0(HDL_Counter2_count_reg[13]),
        .I1(maximum_counter_value_1[13]),
        .I2(HDL_Counter2_count_reg[12]),
        .I3(maximum_counter_value_1[12]),
        .O(Logical_Operator_out10_carry_i_2__2_n_0));
  LUT4 #(
    .INIT(16'h22B2)) 
    Logical_Operator_out10_carry_i_3__2
       (.I0(HDL_Counter2_count_reg[11]),
        .I1(maximum_counter_value_1[11]),
        .I2(HDL_Counter2_count_reg[10]),
        .I3(maximum_counter_value_1[10]),
        .O(Logical_Operator_out10_carry_i_3__2_n_0));
  LUT4 #(
    .INIT(16'h22B2)) 
    Logical_Operator_out10_carry_i_4__2
       (.I0(HDL_Counter2_count_reg[9]),
        .I1(maximum_counter_value_1[9]),
        .I2(HDL_Counter2_count_reg[8]),
        .I3(maximum_counter_value_1[8]),
        .O(Logical_Operator_out10_carry_i_4__2_n_0));
  LUT4 #(
    .INIT(16'h22B2)) 
    Logical_Operator_out10_carry_i_5__2
       (.I0(HDL_Counter2_count_reg[7]),
        .I1(maximum_counter_value_1[7]),
        .I2(HDL_Counter2_count_reg[6]),
        .I3(maximum_counter_value_1[6]),
        .O(Logical_Operator_out10_carry_i_5__2_n_0));
  LUT4 #(
    .INIT(16'h22B2)) 
    Logical_Operator_out10_carry_i_6__2
       (.I0(HDL_Counter2_count_reg[5]),
        .I1(maximum_counter_value_1[5]),
        .I2(HDL_Counter2_count_reg[4]),
        .I3(maximum_counter_value_1[4]),
        .O(Logical_Operator_out10_carry_i_6__2_n_0));
  LUT4 #(
    .INIT(16'h22B2)) 
    Logical_Operator_out10_carry_i_7__2
       (.I0(HDL_Counter2_count_reg[3]),
        .I1(maximum_counter_value_1[3]),
        .I2(HDL_Counter2_count_reg[2]),
        .I3(maximum_counter_value_1[2]),
        .O(Logical_Operator_out10_carry_i_7__2_n_0));
  LUT4 #(
    .INIT(16'h22B2)) 
    Logical_Operator_out10_carry_i_8__2
       (.I0(HDL_Counter2_count_reg[1]),
        .I1(maximum_counter_value_1[1]),
        .I2(HDL_Counter2_count_reg[0]),
        .I3(maximum_counter_value_1[0]),
        .O(Logical_Operator_out10_carry_i_8__2_n_0));
  LUT4 #(
    .INIT(16'h9009)) 
    Logical_Operator_out10_carry_i_9__2
       (.I0(HDL_Counter2_count_reg[15]),
        .I1(maximum_counter_value_1[15]),
        .I2(HDL_Counter2_count_reg[14]),
        .I3(maximum_counter_value_1[14]),
        .O(Logical_Operator_out10_carry_i_9__2_n_0));
  CARRY8 Period_Center0_carry
       (.CI(1'b1),
        .CI_TOP(1'b0),
        .CO({NLW_Period_Center0_carry_CO_UNCONNECTED[7],CO,Period_Center0_carry_n_2,Period_Center0_carry_n_3,Period_Center0_carry_n_4,Period_Center0_carry_n_5,Period_Center0_carry_n_6,Period_Center0_carry_n_7}),
        .DI({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .O(NLW_Period_Center0_carry_O_UNCONNECTED[7:0]),
        .S({1'b0,Counter_Ctrl_out4_1_reg}));
endmodule

(* ORIG_REF_NAME = "PWM_SS_3L_ip_src_GenPWM" *) 
module zusys_PWM_SS_3L_ip_0_0_PWM_SS_3L_ip_src_GenPWM
   (PWM_en_AXI_2_reg_0,
    D,
    GenPWM_out5,
    Q,
    \Switch4_out1_1_reg[0]_0 ,
    \Switch5_out1_1_reg[0]_0 ,
    Demux_out1,
    Demux_out2,
    Demux_out3,
    RSTP,
    CEP,
    IPCORE_CLK,
    write_PWM_en_AXI,
    \HDL_Counter2_count_reg[19]_0 ,
    \max_counter_value_1_reg[19]_0 ,
    \maximum_counter_value_1_reg[8]_0 ,
    \delayMatch1_reg_reg[0][13]_0 ,
    \min_pulse_width_AXI_1_reg[13]_0 ,
    \delayMatch3_reg_reg[0][13]_0 ,
    \delayMatch5_reg_reg[0][13]_0 ,
    Mux_out1,
    delayMatch_1_reg,
    delayMatch_1_reg_1,
    delayMatch3_1_reg,
    delayMatch3_1_reg_1,
    delayMatch6_1_reg,
    delayMatch6_1_reg_1);
  output PWM_en_AXI_2_reg_0;
  output [0:0]D;
  output GenPWM_out5;
  output [1:0]Q;
  output [1:0]\Switch4_out1_1_reg[0]_0 ;
  output [1:0]\Switch5_out1_1_reg[0]_0 ;
  output [0:1]Demux_out1;
  output [0:1]Demux_out2;
  output [0:1]Demux_out3;
  input RSTP;
  input CEP;
  input IPCORE_CLK;
  input write_PWM_en_AXI;
  input \HDL_Counter2_count_reg[19]_0 ;
  input [19:0]\max_counter_value_1_reg[19]_0 ;
  input \maximum_counter_value_1_reg[8]_0 ;
  input [13:0]\delayMatch1_reg_reg[0][13]_0 ;
  input [13:0]\min_pulse_width_AXI_1_reg[13]_0 ;
  input [13:0]\delayMatch3_reg_reg[0][13]_0 ;
  input [13:0]\delayMatch5_reg_reg[0][13]_0 ;
  input [0:5]Mux_out1;
  input [0:0]delayMatch_1_reg;
  input [0:0]delayMatch_1_reg_1;
  input [0:0]delayMatch3_1_reg;
  input [0:0]delayMatch3_1_reg_1;
  input [0:0]delayMatch6_1_reg;
  input [0:0]delayMatch6_1_reg_1;

  wire CEP;
  wire [20:0]Counter_Ctrl_out3;
  wire Counter_Ctrl_out4;
  wire Counter_Ctrl_out5;
  wire [0:0]D;
  wire [13:0]Delay1_out1;
  wire \Delay1_out1[0]_i_1_n_0 ;
  wire \Delay1_out1[10]_i_1_n_0 ;
  wire \Delay1_out1[12]_i_1_n_0 ;
  wire \Delay1_out1[2]_i_1_n_0 ;
  wire \Delay1_out1[4]_i_1_n_0 ;
  wire \Delay1_out1[6]_i_1_n_0 ;
  wire \Delay1_out1[8]_i_1_n_0 ;
  wire [13:0]Delay2_out1;
  wire \Delay2_out1[0]_i_1_n_0 ;
  wire \Delay2_out1[10]_i_1_n_0 ;
  wire \Delay2_out1[12]_i_1_n_0 ;
  wire \Delay2_out1[2]_i_1_n_0 ;
  wire \Delay2_out1[4]_i_1_n_0 ;
  wire \Delay2_out1[6]_i_1_n_0 ;
  wire \Delay2_out1[8]_i_1_n_0 ;
  wire [13:0]Delay_out1;
  wire \Delay_out1[0]_i_1_n_0 ;
  wire \Delay_out1[10]_i_1_n_0 ;
  wire \Delay_out1[12]_i_1_n_0 ;
  wire \Delay_out1[2]_i_1_n_0 ;
  wire \Delay_out1[4]_i_1_n_0 ;
  wire \Delay_out1[6]_i_1_n_0 ;
  wire \Delay_out1[8]_i_1_n_0 ;
  wire [0:1]Demux_out1;
  wire [0:1]Demux_out2;
  wire [0:1]Demux_out3;
  wire GenPWM_out5;
  wire [19:0]HDL_Counter2_count_reg;
  wire \HDL_Counter2_count_reg[19]_0 ;
  wire IPCORE_CLK;
  wire [13:0]LimitPulseWidth_a_out1;
  wire [13:0]LimitPulseWidth_b_out1;
  wire [13:0]LimitPulseWidth_c_out1;
  wire [1:1]Modulator_a_out1;
  wire [1:1]Modulator_b_out1;
  wire [1:1]Modulator_c_out1;
  wire [0:5]Mux_out1;
  wire OR_out1__0;
  wire PWM_en_AXI_1;
  wire PWM_en_AXI_2_reg_0;
  wire [1:0]Q;
  wire RSTP;
  wire Saturation1_out110_in;
  wire [1:0]\Switch4_out1_1_reg[0]_0 ;
  wire Switch5_out1_1;
  wire [1:0]\Switch5_out1_1_reg[0]_0 ;
  wire [13:0]\delayMatch1_reg_reg[0][13]_0 ;
  wire [13:0]\delayMatch1_reg_reg[0]_0 ;
  wire [13:0]\delayMatch1_reg_reg[1]_1 ;
  wire [0:0]delayMatch3_1_reg;
  wire [0:0]delayMatch3_1_reg_1;
  wire [13:0]\delayMatch3_reg_reg[0][13]_0 ;
  wire [13:0]\delayMatch3_reg_reg[0]_2 ;
  wire [13:0]\delayMatch3_reg_reg[1]_3 ;
  wire [13:0]\delayMatch5_reg_reg[0][13]_0 ;
  wire [13:0]\delayMatch5_reg_reg[0]_4 ;
  wire [13:0]\delayMatch5_reg_reg[1]_5 ;
  wire [0:0]delayMatch6_1_reg;
  wire [0:0]delayMatch6_1_reg_1;
  wire [0:0]delayMatch_1_reg;
  wire [0:0]delayMatch_1_reg_1;
  wire [19:0]max_counter_value_1;
  wire [19:0]\max_counter_value_1_reg[19]_0 ;
  wire maximum_counter_value10_in;
  wire maximum_counter_value1__14;
  wire [19:0]maximum_counter_value_1;
  wire \maximum_counter_value_1[13]_i_1_n_0 ;
  wire \maximum_counter_value_1[15]_i_1_n_0 ;
  wire \maximum_counter_value_1[16]_i_1_n_0 ;
  wire \maximum_counter_value_1[17]_i_1_n_0 ;
  wire \maximum_counter_value_1[18]_i_1_n_0 ;
  wire \maximum_counter_value_1[18]_i_2_n_0 ;
  wire \maximum_counter_value_1[18]_i_3_n_0 ;
  wire \maximum_counter_value_1[19]_i_1_n_0 ;
  wire \maximum_counter_value_1[2]_i_1_n_0 ;
  wire \maximum_counter_value_1[4]_i_1_n_0 ;
  wire \maximum_counter_value_1[6]_i_1_n_0 ;
  wire \maximum_counter_value_1[7]_i_1_n_0 ;
  wire \maximum_counter_value_1[7]_i_2_n_0 ;
  wire \maximum_counter_value_1[8]_i_10_n_0 ;
  wire \maximum_counter_value_1[8]_i_11_n_0 ;
  wire \maximum_counter_value_1[8]_i_12_n_0 ;
  wire \maximum_counter_value_1[8]_i_5_n_0 ;
  wire \maximum_counter_value_1[8]_i_6_n_0 ;
  wire \maximum_counter_value_1[8]_i_7_n_0 ;
  wire \maximum_counter_value_1[8]_i_8_n_0 ;
  wire \maximum_counter_value_1[8]_i_9_n_0 ;
  wire \maximum_counter_value_1_reg[8]_0 ;
  wire [13:0]min_pulse_width;
  wire [13:0]\min_pulse_width_AXI_1_reg[13]_0 ;
  wire \minus_out1_1[13]_i_10_n_0 ;
  wire \minus_out1_1[13]_i_11_n_0 ;
  wire \minus_out1_1[13]_i_12_n_0 ;
  wire \minus_out1_1[13]_i_13_n_0 ;
  wire \minus_out1_1[13]_i_14_n_0 ;
  wire \minus_out1_1[13]_i_15_n_0 ;
  wire \minus_out1_1[13]_i_3_n_0 ;
  wire \minus_out1_1[13]_i_4_n_0 ;
  wire \minus_out1_1[13]_i_5_n_0 ;
  wire \minus_out1_1[13]_i_6_n_0 ;
  wire \minus_out1_1[13]_i_7_n_0 ;
  wire \minus_out1_1[13]_i_8__1_n_0 ;
  wire \minus_out1_1[13]_i_9__0_n_0 ;
  wire \minus_out1_1_reg[13]_i_2__0_n_2 ;
  wire \minus_out1_1_reg[13]_i_2__0_n_3 ;
  wire \minus_out1_1_reg[13]_i_2__0_n_4 ;
  wire \minus_out1_1_reg[13]_i_2__0_n_5 ;
  wire \minus_out1_1_reg[13]_i_2__0_n_6 ;
  wire \minus_out1_1_reg[13]_i_2__0_n_7 ;
  wire [20:0]modulating_signal_in_clock_cycles_1_reg__0;
  wire [20:0]modulating_signal_in_clock_cycles_1_reg__0_0;
  wire [8:5]p_1_in;
  wire [1:1]reduced_reg;
  wire [20:0]\reduced_reg_1_reg[1]_9 ;
  wire [0:0]reduced_reg__0;
  wire u_Counter_Ctrl_n_22;
  wire u_Counter_Ctrl_n_23;
  wire u_Counter_Ctrl_n_24;
  wire u_Counter_Ctrl_n_25;
  wire u_Counter_Ctrl_n_26;
  wire u_Counter_Ctrl_n_27;
  wire u_Counter_Ctrl_n_28;
  wire u_Counter_Ctrl_n_29;
  wire u_Counter_Ctrl_n_30;
  wire u_Counter_Ctrl_n_31;
  wire u_Counter_Ctrl_n_32;
  wire u_Counter_Ctrl_n_33;
  wire u_Counter_Ctrl_n_34;
  wire u_Counter_Ctrl_n_35;
  wire u_Counter_Ctrl_n_36;
  wire u_Counter_Ctrl_n_37;
  wire u_Counter_Ctrl_n_38;
  wire u_Counter_Ctrl_n_39;
  wire u_Counter_Ctrl_n_40;
  wire u_Counter_Ctrl_n_41;
  wire u_LimitPulseWidth_a_n_0;
  wire u_LimitPulseWidth_a_n_1;
  wire u_LimitPulseWidth_a_n_17;
  wire u_LimitPulseWidth_a_n_18;
  wire u_LimitPulseWidth_a_n_19;
  wire u_LimitPulseWidth_a_n_20;
  wire u_LimitPulseWidth_a_n_21;
  wire u_LimitPulseWidth_a_n_22;
  wire u_LimitPulseWidth_a_n_23;
  wire u_LimitPulseWidth_a_n_24;
  wire u_LimitPulseWidth_a_n_25;
  wire u_LimitPulseWidth_a_n_26;
  wire u_LimitPulseWidth_a_n_27;
  wire u_LimitPulseWidth_a_n_28;
  wire u_LimitPulseWidth_a_n_29;
  wire u_LimitPulseWidth_b_n_0;
  wire u_LimitPulseWidth_b_n_1;
  wire u_LimitPulseWidth_b_n_16;
  wire u_LimitPulseWidth_b_n_17;
  wire u_LimitPulseWidth_b_n_18;
  wire u_LimitPulseWidth_b_n_19;
  wire u_LimitPulseWidth_b_n_20;
  wire u_LimitPulseWidth_b_n_21;
  wire u_LimitPulseWidth_c_n_0;
  wire u_LimitPulseWidth_c_n_1;
  wire u_LimitPulseWidth_c_n_17;
  wire u_LimitPulseWidth_c_n_18;
  wire u_LimitPulseWidth_c_n_19;
  wire u_LimitPulseWidth_c_n_2;
  wire u_LimitPulseWidth_c_n_20;
  wire u_LimitPulseWidth_c_n_21;
  wire u_LimitPulseWidth_c_n_22;
  wire u_LimitPulseWidth_c_n_23;
  wire u_LimitPulseWidth_c_n_24;
  wire u_LimitPulseWidth_c_n_25;
  wire u_LimitPulseWidth_c_n_26;
  wire u_LimitPulseWidth_c_n_27;
  wire u_LimitPulseWidth_c_n_28;
  wire u_LimitPulseWidth_c_n_29;
  wire u_LimitPulseWidth_c_n_30;
  wire u_LimitPulseWidth_c_n_31;
  wire u_LimitPulseWidth_c_n_32;
  wire u_LimitPulseWidth_c_n_33;
  wire u_LimitPulseWidth_c_n_34;
  wire u_Modulator_a_n_21;
  wire u_Modulator_a_n_23;
  wire u_Modulator_a_n_24;
  wire u_Modulator_a_n_25;
  wire u_Modulator_a_n_26;
  wire u_Modulator_a_n_27;
  wire u_Modulator_a_n_28;
  wire u_Modulator_a_n_29;
  wire u_Modulator_a_n_30;
  wire u_Modulator_a_n_31;
  wire u_Modulator_a_n_32;
  wire u_Modulator_a_n_33;
  wire u_Modulator_a_n_34;
  wire u_Modulator_a_n_35;
  wire u_Modulator_a_n_36;
  wire u_Modulator_a_n_37;
  wire u_Modulator_a_n_38;
  wire u_Modulator_a_n_39;
  wire u_Modulator_a_n_40;
  wire u_Modulator_a_n_41;
  wire u_Modulator_a_n_42;
  wire u_Modulator_a_n_43;
  wire u_Modulator_a_n_44;
  wire u_Modulator_a_n_45;
  wire u_Modulator_a_n_46;
  wire u_Modulator_a_n_47;
  wire u_Modulator_a_n_48;
  wire u_Modulator_a_n_49;
  wire u_Modulator_a_n_50;
  wire u_Modulator_a_n_51;
  wire u_Modulator_a_n_52;
  wire u_Modulator_a_n_53;
  wire u_Modulator_a_n_54;
  wire u_Modulator_a_n_55;
  wire u_Modulator_a_n_56;
  wire u_Modulator_a_n_57;
  wire u_Modulator_a_n_58;
  wire u_Modulator_a_n_59;
  wire u_Modulator_a_n_60;
  wire u_Modulator_a_n_61;
  wire u_Modulator_a_n_62;
  wire u_Modulator_a_n_63;
  wire u_Modulator_a_n_64;
  wire u_Modulator_a_n_65;
  wire u_Modulator_a_n_66;
  wire u_Modulator_a_n_67;
  wire u_Modulator_a_n_68;
  wire u_Modulator_b_n_21;
  wire u_Modulator_c_n_21;
  wire write_PWM_en_AXI;
  wire [7:7]\NLW_minus_out1_1_reg[13]_i_2__0_CO_UNCONNECTED ;
  wire [7:0]\NLW_minus_out1_1_reg[13]_i_2__0_O_UNCONNECTED ;

  FDRE Counter_Ctrl_out4_1_reg
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Counter_Ctrl_out4),
        .Q(D),
        .R(RSTP));
  LUT5 #(
    .INIT(32'h40000000)) 
    Counter_Ctrl_out5_1_i_1
       (.I0(HDL_Counter2_count_reg[19]),
        .I1(PWM_en_AXI_2_reg_0),
        .I2(u_LimitPulseWidth_c_n_23),
        .I3(u_LimitPulseWidth_c_n_25),
        .I4(u_LimitPulseWidth_a_n_24),
        .O(Counter_Ctrl_out5));
  FDRE Counter_Ctrl_out5_1_reg
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Counter_Ctrl_out5),
        .Q(GenPWM_out5),
        .R(RSTP));
  LUT3 #(
    .INIT(8'hB8)) 
    \Delay1_out1[0]_i_1 
       (.I0(\delayMatch3_reg_reg[1]_3 [0]),
        .I1(u_LimitPulseWidth_b_n_1),
        .I2(Delay1_out1[0]),
        .O(\Delay1_out1[0]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair60" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \Delay1_out1[10]_i_1 
       (.I0(\delayMatch3_reg_reg[1]_3 [10]),
        .I1(u_LimitPulseWidth_b_n_1),
        .I2(Delay1_out1[10]),
        .O(\Delay1_out1[10]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair60" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \Delay1_out1[12]_i_1 
       (.I0(\delayMatch3_reg_reg[1]_3 [12]),
        .I1(u_LimitPulseWidth_b_n_1),
        .I2(Delay1_out1[12]),
        .O(\Delay1_out1[12]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair62" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \Delay1_out1[2]_i_1 
       (.I0(\delayMatch3_reg_reg[1]_3 [2]),
        .I1(u_LimitPulseWidth_b_n_1),
        .I2(Delay1_out1[2]),
        .O(\Delay1_out1[2]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair62" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \Delay1_out1[4]_i_1 
       (.I0(\delayMatch3_reg_reg[1]_3 [4]),
        .I1(u_LimitPulseWidth_b_n_1),
        .I2(Delay1_out1[4]),
        .O(\Delay1_out1[4]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair61" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \Delay1_out1[6]_i_1 
       (.I0(\delayMatch3_reg_reg[1]_3 [6]),
        .I1(u_LimitPulseWidth_b_n_1),
        .I2(Delay1_out1[6]),
        .O(\Delay1_out1[6]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair61" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \Delay1_out1[8]_i_1 
       (.I0(\delayMatch3_reg_reg[1]_3 [8]),
        .I1(u_LimitPulseWidth_b_n_1),
        .I2(Delay1_out1[8]),
        .O(\Delay1_out1[8]_i_1_n_0 ));
  FDRE \Delay1_out1_reg[0] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\Delay1_out1[0]_i_1_n_0 ),
        .Q(Delay1_out1[0]),
        .R(RSTP));
  FDRE \Delay1_out1_reg[10] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\Delay1_out1[10]_i_1_n_0 ),
        .Q(Delay1_out1[10]),
        .R(RSTP));
  FDRE \Delay1_out1_reg[11] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(u_LimitPulseWidth_b_n_16),
        .Q(Delay1_out1[11]),
        .R(RSTP));
  FDRE \Delay1_out1_reg[12] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\Delay1_out1[12]_i_1_n_0 ),
        .Q(Delay1_out1[12]),
        .R(RSTP));
  FDRE \Delay1_out1_reg[13] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(u_LimitPulseWidth_b_n_0),
        .Q(Delay1_out1[13]),
        .R(RSTP));
  FDRE \Delay1_out1_reg[1] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(u_LimitPulseWidth_b_n_21),
        .Q(Delay1_out1[1]),
        .R(RSTP));
  FDRE \Delay1_out1_reg[2] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\Delay1_out1[2]_i_1_n_0 ),
        .Q(Delay1_out1[2]),
        .R(RSTP));
  FDRE \Delay1_out1_reg[3] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(u_LimitPulseWidth_b_n_20),
        .Q(Delay1_out1[3]),
        .R(RSTP));
  FDRE \Delay1_out1_reg[4] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\Delay1_out1[4]_i_1_n_0 ),
        .Q(Delay1_out1[4]),
        .R(RSTP));
  FDRE \Delay1_out1_reg[5] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(u_LimitPulseWidth_b_n_19),
        .Q(Delay1_out1[5]),
        .R(RSTP));
  FDRE \Delay1_out1_reg[6] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\Delay1_out1[6]_i_1_n_0 ),
        .Q(Delay1_out1[6]),
        .R(RSTP));
  FDRE \Delay1_out1_reg[7] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(u_LimitPulseWidth_b_n_18),
        .Q(Delay1_out1[7]),
        .R(RSTP));
  FDRE \Delay1_out1_reg[8] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\Delay1_out1[8]_i_1_n_0 ),
        .Q(Delay1_out1[8]),
        .R(RSTP));
  FDRE \Delay1_out1_reg[9] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(u_LimitPulseWidth_b_n_17),
        .Q(Delay1_out1[9]),
        .R(RSTP));
  LUT3 #(
    .INIT(8'hB8)) 
    \Delay2_out1[0]_i_1 
       (.I0(\delayMatch5_reg_reg[1]_5 [0]),
        .I1(u_LimitPulseWidth_c_n_2),
        .I2(Delay2_out1[0]),
        .O(\Delay2_out1[0]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair57" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \Delay2_out1[10]_i_1 
       (.I0(\delayMatch5_reg_reg[1]_5 [10]),
        .I1(u_LimitPulseWidth_c_n_2),
        .I2(Delay2_out1[10]),
        .O(\Delay2_out1[10]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair57" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \Delay2_out1[12]_i_1 
       (.I0(\delayMatch5_reg_reg[1]_5 [12]),
        .I1(u_LimitPulseWidth_c_n_2),
        .I2(Delay2_out1[12]),
        .O(\Delay2_out1[12]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair59" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \Delay2_out1[2]_i_1 
       (.I0(\delayMatch5_reg_reg[1]_5 [2]),
        .I1(u_LimitPulseWidth_c_n_2),
        .I2(Delay2_out1[2]),
        .O(\Delay2_out1[2]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair59" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \Delay2_out1[4]_i_1 
       (.I0(\delayMatch5_reg_reg[1]_5 [4]),
        .I1(u_LimitPulseWidth_c_n_2),
        .I2(Delay2_out1[4]),
        .O(\Delay2_out1[4]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair58" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \Delay2_out1[6]_i_1 
       (.I0(\delayMatch5_reg_reg[1]_5 [6]),
        .I1(u_LimitPulseWidth_c_n_2),
        .I2(Delay2_out1[6]),
        .O(\Delay2_out1[6]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair58" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \Delay2_out1[8]_i_1 
       (.I0(\delayMatch5_reg_reg[1]_5 [8]),
        .I1(u_LimitPulseWidth_c_n_2),
        .I2(Delay2_out1[8]),
        .O(\Delay2_out1[8]_i_1_n_0 ));
  FDRE \Delay2_out1_reg[0] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\Delay2_out1[0]_i_1_n_0 ),
        .Q(Delay2_out1[0]),
        .R(RSTP));
  FDRE \Delay2_out1_reg[10] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\Delay2_out1[10]_i_1_n_0 ),
        .Q(Delay2_out1[10]),
        .R(RSTP));
  FDRE \Delay2_out1_reg[11] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(u_LimitPulseWidth_c_n_17),
        .Q(Delay2_out1[11]),
        .R(RSTP));
  FDRE \Delay2_out1_reg[12] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\Delay2_out1[12]_i_1_n_0 ),
        .Q(Delay2_out1[12]),
        .R(RSTP));
  FDRE \Delay2_out1_reg[13] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(u_LimitPulseWidth_c_n_1),
        .Q(Delay2_out1[13]),
        .R(RSTP));
  FDRE \Delay2_out1_reg[1] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(u_LimitPulseWidth_c_n_22),
        .Q(Delay2_out1[1]),
        .R(RSTP));
  FDRE \Delay2_out1_reg[2] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\Delay2_out1[2]_i_1_n_0 ),
        .Q(Delay2_out1[2]),
        .R(RSTP));
  FDRE \Delay2_out1_reg[3] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(u_LimitPulseWidth_c_n_21),
        .Q(Delay2_out1[3]),
        .R(RSTP));
  FDRE \Delay2_out1_reg[4] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\Delay2_out1[4]_i_1_n_0 ),
        .Q(Delay2_out1[4]),
        .R(RSTP));
  FDRE \Delay2_out1_reg[5] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(u_LimitPulseWidth_c_n_20),
        .Q(Delay2_out1[5]),
        .R(RSTP));
  FDRE \Delay2_out1_reg[6] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\Delay2_out1[6]_i_1_n_0 ),
        .Q(Delay2_out1[6]),
        .R(RSTP));
  FDRE \Delay2_out1_reg[7] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(u_LimitPulseWidth_c_n_19),
        .Q(Delay2_out1[7]),
        .R(RSTP));
  FDRE \Delay2_out1_reg[8] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\Delay2_out1[8]_i_1_n_0 ),
        .Q(Delay2_out1[8]),
        .R(RSTP));
  FDRE \Delay2_out1_reg[9] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(u_LimitPulseWidth_c_n_18),
        .Q(Delay2_out1[9]),
        .R(RSTP));
  LUT3 #(
    .INIT(8'hB8)) 
    \Delay_out1[0]_i_1 
       (.I0(\delayMatch1_reg_reg[1]_1 [0]),
        .I1(OR_out1__0),
        .I2(Delay_out1[0]),
        .O(\Delay_out1[0]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair63" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \Delay_out1[10]_i_1 
       (.I0(\delayMatch1_reg_reg[1]_1 [10]),
        .I1(OR_out1__0),
        .I2(Delay_out1[10]),
        .O(\Delay_out1[10]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair63" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \Delay_out1[12]_i_1 
       (.I0(\delayMatch1_reg_reg[1]_1 [12]),
        .I1(OR_out1__0),
        .I2(Delay_out1[12]),
        .O(\Delay_out1[12]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair65" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \Delay_out1[2]_i_1 
       (.I0(\delayMatch1_reg_reg[1]_1 [2]),
        .I1(OR_out1__0),
        .I2(Delay_out1[2]),
        .O(\Delay_out1[2]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair65" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \Delay_out1[4]_i_1 
       (.I0(\delayMatch1_reg_reg[1]_1 [4]),
        .I1(OR_out1__0),
        .I2(Delay_out1[4]),
        .O(\Delay_out1[4]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair64" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \Delay_out1[6]_i_1 
       (.I0(\delayMatch1_reg_reg[1]_1 [6]),
        .I1(OR_out1__0),
        .I2(Delay_out1[6]),
        .O(\Delay_out1[6]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair64" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \Delay_out1[8]_i_1 
       (.I0(\delayMatch1_reg_reg[1]_1 [8]),
        .I1(OR_out1__0),
        .I2(Delay_out1[8]),
        .O(\Delay_out1[8]_i_1_n_0 ));
  FDRE \Delay_out1_reg[0] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\Delay_out1[0]_i_1_n_0 ),
        .Q(Delay_out1[0]),
        .R(RSTP));
  FDRE \Delay_out1_reg[10] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\Delay_out1[10]_i_1_n_0 ),
        .Q(Delay_out1[10]),
        .R(RSTP));
  FDRE \Delay_out1_reg[11] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(u_LimitPulseWidth_a_n_18),
        .Q(Delay_out1[11]),
        .R(RSTP));
  FDRE \Delay_out1_reg[12] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\Delay_out1[12]_i_1_n_0 ),
        .Q(Delay_out1[12]),
        .R(RSTP));
  FDRE \Delay_out1_reg[13] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(u_LimitPulseWidth_a_n_1),
        .Q(Delay_out1[13]),
        .R(RSTP));
  FDRE \Delay_out1_reg[1] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(u_LimitPulseWidth_a_n_23),
        .Q(Delay_out1[1]),
        .R(RSTP));
  FDRE \Delay_out1_reg[2] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\Delay_out1[2]_i_1_n_0 ),
        .Q(Delay_out1[2]),
        .R(RSTP));
  FDRE \Delay_out1_reg[3] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(u_LimitPulseWidth_a_n_22),
        .Q(Delay_out1[3]),
        .R(RSTP));
  FDRE \Delay_out1_reg[4] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\Delay_out1[4]_i_1_n_0 ),
        .Q(Delay_out1[4]),
        .R(RSTP));
  FDRE \Delay_out1_reg[5] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(u_LimitPulseWidth_a_n_21),
        .Q(Delay_out1[5]),
        .R(RSTP));
  FDRE \Delay_out1_reg[6] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\Delay_out1[6]_i_1_n_0 ),
        .Q(Delay_out1[6]),
        .R(RSTP));
  FDRE \Delay_out1_reg[7] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(u_LimitPulseWidth_a_n_20),
        .Q(Delay_out1[7]),
        .R(RSTP));
  FDRE \Delay_out1_reg[8] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\Delay_out1[8]_i_1_n_0 ),
        .Q(Delay_out1[8]),
        .R(RSTP));
  FDRE \Delay_out1_reg[9] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(u_LimitPulseWidth_a_n_19),
        .Q(Delay_out1[9]),
        .R(RSTP));
  FDRE \HDL_Counter2_count_reg[0] 
       (.C(IPCORE_CLK),
        .CE(\HDL_Counter2_count_reg[19]_0 ),
        .D(u_Counter_Ctrl_n_29),
        .Q(HDL_Counter2_count_reg[0]),
        .R(RSTP));
  FDRE \HDL_Counter2_count_reg[10] 
       (.C(IPCORE_CLK),
        .CE(\HDL_Counter2_count_reg[19]_0 ),
        .D(u_Counter_Ctrl_n_35),
        .Q(HDL_Counter2_count_reg[10]),
        .R(RSTP));
  FDRE \HDL_Counter2_count_reg[11] 
       (.C(IPCORE_CLK),
        .CE(\HDL_Counter2_count_reg[19]_0 ),
        .D(u_Counter_Ctrl_n_34),
        .Q(HDL_Counter2_count_reg[11]),
        .R(RSTP));
  FDRE \HDL_Counter2_count_reg[12] 
       (.C(IPCORE_CLK),
        .CE(\HDL_Counter2_count_reg[19]_0 ),
        .D(u_Counter_Ctrl_n_33),
        .Q(HDL_Counter2_count_reg[12]),
        .R(RSTP));
  FDRE \HDL_Counter2_count_reg[13] 
       (.C(IPCORE_CLK),
        .CE(\HDL_Counter2_count_reg[19]_0 ),
        .D(u_Counter_Ctrl_n_32),
        .Q(HDL_Counter2_count_reg[13]),
        .R(RSTP));
  FDRE \HDL_Counter2_count_reg[14] 
       (.C(IPCORE_CLK),
        .CE(\HDL_Counter2_count_reg[19]_0 ),
        .D(u_Counter_Ctrl_n_31),
        .Q(HDL_Counter2_count_reg[14]),
        .R(RSTP));
  FDRE \HDL_Counter2_count_reg[15] 
       (.C(IPCORE_CLK),
        .CE(\HDL_Counter2_count_reg[19]_0 ),
        .D(u_Counter_Ctrl_n_30),
        .Q(HDL_Counter2_count_reg[15]),
        .R(RSTP));
  FDRE \HDL_Counter2_count_reg[16] 
       (.C(IPCORE_CLK),
        .CE(\HDL_Counter2_count_reg[19]_0 ),
        .D(u_Counter_Ctrl_n_41),
        .Q(HDL_Counter2_count_reg[16]),
        .R(RSTP));
  FDRE \HDL_Counter2_count_reg[17] 
       (.C(IPCORE_CLK),
        .CE(\HDL_Counter2_count_reg[19]_0 ),
        .D(u_Counter_Ctrl_n_40),
        .Q(HDL_Counter2_count_reg[17]),
        .R(RSTP));
  FDRE \HDL_Counter2_count_reg[18] 
       (.C(IPCORE_CLK),
        .CE(\HDL_Counter2_count_reg[19]_0 ),
        .D(u_Counter_Ctrl_n_39),
        .Q(HDL_Counter2_count_reg[18]),
        .R(RSTP));
  FDRE \HDL_Counter2_count_reg[19] 
       (.C(IPCORE_CLK),
        .CE(\HDL_Counter2_count_reg[19]_0 ),
        .D(u_Counter_Ctrl_n_38),
        .Q(HDL_Counter2_count_reg[19]),
        .R(RSTP));
  FDRE \HDL_Counter2_count_reg[1] 
       (.C(IPCORE_CLK),
        .CE(\HDL_Counter2_count_reg[19]_0 ),
        .D(u_Counter_Ctrl_n_28),
        .Q(HDL_Counter2_count_reg[1]),
        .R(RSTP));
  FDRE \HDL_Counter2_count_reg[2] 
       (.C(IPCORE_CLK),
        .CE(\HDL_Counter2_count_reg[19]_0 ),
        .D(u_Counter_Ctrl_n_27),
        .Q(HDL_Counter2_count_reg[2]),
        .R(RSTP));
  FDRE \HDL_Counter2_count_reg[3] 
       (.C(IPCORE_CLK),
        .CE(\HDL_Counter2_count_reg[19]_0 ),
        .D(u_Counter_Ctrl_n_26),
        .Q(HDL_Counter2_count_reg[3]),
        .R(RSTP));
  FDRE \HDL_Counter2_count_reg[4] 
       (.C(IPCORE_CLK),
        .CE(\HDL_Counter2_count_reg[19]_0 ),
        .D(u_Counter_Ctrl_n_25),
        .Q(HDL_Counter2_count_reg[4]),
        .R(RSTP));
  FDRE \HDL_Counter2_count_reg[5] 
       (.C(IPCORE_CLK),
        .CE(\HDL_Counter2_count_reg[19]_0 ),
        .D(u_Counter_Ctrl_n_24),
        .Q(HDL_Counter2_count_reg[5]),
        .R(RSTP));
  FDRE \HDL_Counter2_count_reg[6] 
       (.C(IPCORE_CLK),
        .CE(\HDL_Counter2_count_reg[19]_0 ),
        .D(u_Counter_Ctrl_n_23),
        .Q(HDL_Counter2_count_reg[6]),
        .R(RSTP));
  FDRE \HDL_Counter2_count_reg[7] 
       (.C(IPCORE_CLK),
        .CE(\HDL_Counter2_count_reg[19]_0 ),
        .D(u_Counter_Ctrl_n_22),
        .Q(HDL_Counter2_count_reg[7]),
        .R(RSTP));
  FDRE \HDL_Counter2_count_reg[8] 
       (.C(IPCORE_CLK),
        .CE(\HDL_Counter2_count_reg[19]_0 ),
        .D(u_Counter_Ctrl_n_37),
        .Q(HDL_Counter2_count_reg[8]),
        .R(RSTP));
  FDRE \HDL_Counter2_count_reg[9] 
       (.C(IPCORE_CLK),
        .CE(\HDL_Counter2_count_reg[19]_0 ),
        .D(u_Counter_Ctrl_n_36),
        .Q(HDL_Counter2_count_reg[9]),
        .R(RSTP));
  FDRE PWM_en_AXI_1_reg
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(write_PWM_en_AXI),
        .Q(PWM_en_AXI_1),
        .R(RSTP));
  FDRE PWM_en_AXI_2_reg
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(PWM_en_AXI_1),
        .Q(PWM_en_AXI_2_reg_0),
        .R(RSTP));
  LUT3 #(
    .INIT(8'hF4)) 
    \Switch3_out1_1[0]_i_1 
       (.I0(reduced_reg),
        .I1(CEP),
        .I2(RSTP),
        .O(Switch5_out1_1));
  FDRE \Switch3_out1_1_reg[0] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(u_Modulator_a_n_21),
        .Q(Q[1]),
        .R(Switch5_out1_1));
  FDRE \Switch3_out1_1_reg[1] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Modulator_a_out1),
        .Q(Q[0]),
        .R(Switch5_out1_1));
  FDRE \Switch4_out1_1_reg[0] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(u_Modulator_b_n_21),
        .Q(\Switch4_out1_1_reg[0]_0 [1]),
        .R(Switch5_out1_1));
  FDRE \Switch4_out1_1_reg[1] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Modulator_b_out1),
        .Q(\Switch4_out1_1_reg[0]_0 [0]),
        .R(Switch5_out1_1));
  FDRE \Switch5_out1_1_reg[0] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(u_Modulator_c_n_21),
        .Q(\Switch5_out1_1_reg[0]_0 [1]),
        .R(Switch5_out1_1));
  FDRE \Switch5_out1_1_reg[1] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Modulator_c_out1),
        .Q(\Switch5_out1_1_reg[0]_0 [0]),
        .R(Switch5_out1_1));
  FDRE \delayMatch1_reg_reg[0][0] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\delayMatch1_reg_reg[0][13]_0 [0]),
        .Q(\delayMatch1_reg_reg[0]_0 [0]),
        .R(RSTP));
  FDRE \delayMatch1_reg_reg[0][10] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\delayMatch1_reg_reg[0][13]_0 [10]),
        .Q(\delayMatch1_reg_reg[0]_0 [10]),
        .R(RSTP));
  FDRE \delayMatch1_reg_reg[0][11] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\delayMatch1_reg_reg[0][13]_0 [11]),
        .Q(\delayMatch1_reg_reg[0]_0 [11]),
        .R(RSTP));
  FDRE \delayMatch1_reg_reg[0][12] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\delayMatch1_reg_reg[0][13]_0 [12]),
        .Q(\delayMatch1_reg_reg[0]_0 [12]),
        .R(RSTP));
  FDRE \delayMatch1_reg_reg[0][13] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\delayMatch1_reg_reg[0][13]_0 [13]),
        .Q(\delayMatch1_reg_reg[0]_0 [13]),
        .R(RSTP));
  FDRE \delayMatch1_reg_reg[0][1] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\delayMatch1_reg_reg[0][13]_0 [1]),
        .Q(\delayMatch1_reg_reg[0]_0 [1]),
        .R(RSTP));
  FDRE \delayMatch1_reg_reg[0][2] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\delayMatch1_reg_reg[0][13]_0 [2]),
        .Q(\delayMatch1_reg_reg[0]_0 [2]),
        .R(RSTP));
  FDRE \delayMatch1_reg_reg[0][3] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\delayMatch1_reg_reg[0][13]_0 [3]),
        .Q(\delayMatch1_reg_reg[0]_0 [3]),
        .R(RSTP));
  FDRE \delayMatch1_reg_reg[0][4] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\delayMatch1_reg_reg[0][13]_0 [4]),
        .Q(\delayMatch1_reg_reg[0]_0 [4]),
        .R(RSTP));
  FDRE \delayMatch1_reg_reg[0][5] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\delayMatch1_reg_reg[0][13]_0 [5]),
        .Q(\delayMatch1_reg_reg[0]_0 [5]),
        .R(RSTP));
  FDRE \delayMatch1_reg_reg[0][6] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\delayMatch1_reg_reg[0][13]_0 [6]),
        .Q(\delayMatch1_reg_reg[0]_0 [6]),
        .R(RSTP));
  FDRE \delayMatch1_reg_reg[0][7] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\delayMatch1_reg_reg[0][13]_0 [7]),
        .Q(\delayMatch1_reg_reg[0]_0 [7]),
        .R(RSTP));
  FDRE \delayMatch1_reg_reg[0][8] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\delayMatch1_reg_reg[0][13]_0 [8]),
        .Q(\delayMatch1_reg_reg[0]_0 [8]),
        .R(RSTP));
  FDRE \delayMatch1_reg_reg[0][9] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\delayMatch1_reg_reg[0][13]_0 [9]),
        .Q(\delayMatch1_reg_reg[0]_0 [9]),
        .R(RSTP));
  FDRE \delayMatch1_reg_reg[1][0] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\delayMatch1_reg_reg[0]_0 [0]),
        .Q(\delayMatch1_reg_reg[1]_1 [0]),
        .R(RSTP));
  FDRE \delayMatch1_reg_reg[1][10] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\delayMatch1_reg_reg[0]_0 [10]),
        .Q(\delayMatch1_reg_reg[1]_1 [10]),
        .R(RSTP));
  FDRE \delayMatch1_reg_reg[1][11] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\delayMatch1_reg_reg[0]_0 [11]),
        .Q(\delayMatch1_reg_reg[1]_1 [11]),
        .R(RSTP));
  FDRE \delayMatch1_reg_reg[1][12] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\delayMatch1_reg_reg[0]_0 [12]),
        .Q(\delayMatch1_reg_reg[1]_1 [12]),
        .R(RSTP));
  FDRE \delayMatch1_reg_reg[1][13] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\delayMatch1_reg_reg[0]_0 [13]),
        .Q(\delayMatch1_reg_reg[1]_1 [13]),
        .R(RSTP));
  FDRE \delayMatch1_reg_reg[1][1] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\delayMatch1_reg_reg[0]_0 [1]),
        .Q(\delayMatch1_reg_reg[1]_1 [1]),
        .R(RSTP));
  FDRE \delayMatch1_reg_reg[1][2] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\delayMatch1_reg_reg[0]_0 [2]),
        .Q(\delayMatch1_reg_reg[1]_1 [2]),
        .R(RSTP));
  FDRE \delayMatch1_reg_reg[1][3] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\delayMatch1_reg_reg[0]_0 [3]),
        .Q(\delayMatch1_reg_reg[1]_1 [3]),
        .R(RSTP));
  FDRE \delayMatch1_reg_reg[1][4] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\delayMatch1_reg_reg[0]_0 [4]),
        .Q(\delayMatch1_reg_reg[1]_1 [4]),
        .R(RSTP));
  FDRE \delayMatch1_reg_reg[1][5] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\delayMatch1_reg_reg[0]_0 [5]),
        .Q(\delayMatch1_reg_reg[1]_1 [5]),
        .R(RSTP));
  FDRE \delayMatch1_reg_reg[1][6] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\delayMatch1_reg_reg[0]_0 [6]),
        .Q(\delayMatch1_reg_reg[1]_1 [6]),
        .R(RSTP));
  FDRE \delayMatch1_reg_reg[1][7] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\delayMatch1_reg_reg[0]_0 [7]),
        .Q(\delayMatch1_reg_reg[1]_1 [7]),
        .R(RSTP));
  FDRE \delayMatch1_reg_reg[1][8] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\delayMatch1_reg_reg[0]_0 [8]),
        .Q(\delayMatch1_reg_reg[1]_1 [8]),
        .R(RSTP));
  FDRE \delayMatch1_reg_reg[1][9] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\delayMatch1_reg_reg[0]_0 [9]),
        .Q(\delayMatch1_reg_reg[1]_1 [9]),
        .R(RSTP));
  (* SOFT_HLUTNM = "soft_lutpair69" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \delayMatch3_1_reg[0]_i_1 
       (.I0(Mux_out1[2]),
        .I1(GenPWM_out5),
        .I2(delayMatch3_1_reg),
        .O(Demux_out2[0]));
  (* SOFT_HLUTNM = "soft_lutpair69" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \delayMatch3_1_reg_1[0]_i_1 
       (.I0(Mux_out1[3]),
        .I1(GenPWM_out5),
        .I2(delayMatch3_1_reg_1),
        .O(Demux_out2[1]));
  FDRE \delayMatch3_reg_reg[0][0] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\delayMatch3_reg_reg[0][13]_0 [0]),
        .Q(\delayMatch3_reg_reg[0]_2 [0]),
        .R(RSTP));
  FDRE \delayMatch3_reg_reg[0][10] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\delayMatch3_reg_reg[0][13]_0 [10]),
        .Q(\delayMatch3_reg_reg[0]_2 [10]),
        .R(RSTP));
  FDRE \delayMatch3_reg_reg[0][11] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\delayMatch3_reg_reg[0][13]_0 [11]),
        .Q(\delayMatch3_reg_reg[0]_2 [11]),
        .R(RSTP));
  FDRE \delayMatch3_reg_reg[0][12] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\delayMatch3_reg_reg[0][13]_0 [12]),
        .Q(\delayMatch3_reg_reg[0]_2 [12]),
        .R(RSTP));
  FDRE \delayMatch3_reg_reg[0][13] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\delayMatch3_reg_reg[0][13]_0 [13]),
        .Q(\delayMatch3_reg_reg[0]_2 [13]),
        .R(RSTP));
  FDRE \delayMatch3_reg_reg[0][1] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\delayMatch3_reg_reg[0][13]_0 [1]),
        .Q(\delayMatch3_reg_reg[0]_2 [1]),
        .R(RSTP));
  FDRE \delayMatch3_reg_reg[0][2] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\delayMatch3_reg_reg[0][13]_0 [2]),
        .Q(\delayMatch3_reg_reg[0]_2 [2]),
        .R(RSTP));
  FDRE \delayMatch3_reg_reg[0][3] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\delayMatch3_reg_reg[0][13]_0 [3]),
        .Q(\delayMatch3_reg_reg[0]_2 [3]),
        .R(RSTP));
  FDRE \delayMatch3_reg_reg[0][4] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\delayMatch3_reg_reg[0][13]_0 [4]),
        .Q(\delayMatch3_reg_reg[0]_2 [4]),
        .R(RSTP));
  FDRE \delayMatch3_reg_reg[0][5] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\delayMatch3_reg_reg[0][13]_0 [5]),
        .Q(\delayMatch3_reg_reg[0]_2 [5]),
        .R(RSTP));
  FDRE \delayMatch3_reg_reg[0][6] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\delayMatch3_reg_reg[0][13]_0 [6]),
        .Q(\delayMatch3_reg_reg[0]_2 [6]),
        .R(RSTP));
  FDRE \delayMatch3_reg_reg[0][7] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\delayMatch3_reg_reg[0][13]_0 [7]),
        .Q(\delayMatch3_reg_reg[0]_2 [7]),
        .R(RSTP));
  FDRE \delayMatch3_reg_reg[0][8] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\delayMatch3_reg_reg[0][13]_0 [8]),
        .Q(\delayMatch3_reg_reg[0]_2 [8]),
        .R(RSTP));
  FDRE \delayMatch3_reg_reg[0][9] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\delayMatch3_reg_reg[0][13]_0 [9]),
        .Q(\delayMatch3_reg_reg[0]_2 [9]),
        .R(RSTP));
  FDRE \delayMatch3_reg_reg[1][0] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\delayMatch3_reg_reg[0]_2 [0]),
        .Q(\delayMatch3_reg_reg[1]_3 [0]),
        .R(RSTP));
  FDRE \delayMatch3_reg_reg[1][10] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\delayMatch3_reg_reg[0]_2 [10]),
        .Q(\delayMatch3_reg_reg[1]_3 [10]),
        .R(RSTP));
  FDRE \delayMatch3_reg_reg[1][11] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\delayMatch3_reg_reg[0]_2 [11]),
        .Q(\delayMatch3_reg_reg[1]_3 [11]),
        .R(RSTP));
  FDRE \delayMatch3_reg_reg[1][12] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\delayMatch3_reg_reg[0]_2 [12]),
        .Q(\delayMatch3_reg_reg[1]_3 [12]),
        .R(RSTP));
  FDRE \delayMatch3_reg_reg[1][13] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\delayMatch3_reg_reg[0]_2 [13]),
        .Q(\delayMatch3_reg_reg[1]_3 [13]),
        .R(RSTP));
  FDRE \delayMatch3_reg_reg[1][1] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\delayMatch3_reg_reg[0]_2 [1]),
        .Q(\delayMatch3_reg_reg[1]_3 [1]),
        .R(RSTP));
  FDRE \delayMatch3_reg_reg[1][2] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\delayMatch3_reg_reg[0]_2 [2]),
        .Q(\delayMatch3_reg_reg[1]_3 [2]),
        .R(RSTP));
  FDRE \delayMatch3_reg_reg[1][3] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\delayMatch3_reg_reg[0]_2 [3]),
        .Q(\delayMatch3_reg_reg[1]_3 [3]),
        .R(RSTP));
  FDRE \delayMatch3_reg_reg[1][4] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\delayMatch3_reg_reg[0]_2 [4]),
        .Q(\delayMatch3_reg_reg[1]_3 [4]),
        .R(RSTP));
  FDRE \delayMatch3_reg_reg[1][5] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\delayMatch3_reg_reg[0]_2 [5]),
        .Q(\delayMatch3_reg_reg[1]_3 [5]),
        .R(RSTP));
  FDRE \delayMatch3_reg_reg[1][6] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\delayMatch3_reg_reg[0]_2 [6]),
        .Q(\delayMatch3_reg_reg[1]_3 [6]),
        .R(RSTP));
  FDRE \delayMatch3_reg_reg[1][7] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\delayMatch3_reg_reg[0]_2 [7]),
        .Q(\delayMatch3_reg_reg[1]_3 [7]),
        .R(RSTP));
  FDRE \delayMatch3_reg_reg[1][8] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\delayMatch3_reg_reg[0]_2 [8]),
        .Q(\delayMatch3_reg_reg[1]_3 [8]),
        .R(RSTP));
  FDRE \delayMatch3_reg_reg[1][9] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\delayMatch3_reg_reg[0]_2 [9]),
        .Q(\delayMatch3_reg_reg[1]_3 [9]),
        .R(RSTP));
  FDRE \delayMatch5_reg_reg[0][0] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\delayMatch5_reg_reg[0][13]_0 [0]),
        .Q(\delayMatch5_reg_reg[0]_4 [0]),
        .R(RSTP));
  FDRE \delayMatch5_reg_reg[0][10] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\delayMatch5_reg_reg[0][13]_0 [10]),
        .Q(\delayMatch5_reg_reg[0]_4 [10]),
        .R(RSTP));
  FDRE \delayMatch5_reg_reg[0][11] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\delayMatch5_reg_reg[0][13]_0 [11]),
        .Q(\delayMatch5_reg_reg[0]_4 [11]),
        .R(RSTP));
  FDRE \delayMatch5_reg_reg[0][12] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\delayMatch5_reg_reg[0][13]_0 [12]),
        .Q(\delayMatch5_reg_reg[0]_4 [12]),
        .R(RSTP));
  FDRE \delayMatch5_reg_reg[0][13] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\delayMatch5_reg_reg[0][13]_0 [13]),
        .Q(\delayMatch5_reg_reg[0]_4 [13]),
        .R(RSTP));
  FDRE \delayMatch5_reg_reg[0][1] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\delayMatch5_reg_reg[0][13]_0 [1]),
        .Q(\delayMatch5_reg_reg[0]_4 [1]),
        .R(RSTP));
  FDRE \delayMatch5_reg_reg[0][2] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\delayMatch5_reg_reg[0][13]_0 [2]),
        .Q(\delayMatch5_reg_reg[0]_4 [2]),
        .R(RSTP));
  FDRE \delayMatch5_reg_reg[0][3] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\delayMatch5_reg_reg[0][13]_0 [3]),
        .Q(\delayMatch5_reg_reg[0]_4 [3]),
        .R(RSTP));
  FDRE \delayMatch5_reg_reg[0][4] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\delayMatch5_reg_reg[0][13]_0 [4]),
        .Q(\delayMatch5_reg_reg[0]_4 [4]),
        .R(RSTP));
  FDRE \delayMatch5_reg_reg[0][5] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\delayMatch5_reg_reg[0][13]_0 [5]),
        .Q(\delayMatch5_reg_reg[0]_4 [5]),
        .R(RSTP));
  FDRE \delayMatch5_reg_reg[0][6] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\delayMatch5_reg_reg[0][13]_0 [6]),
        .Q(\delayMatch5_reg_reg[0]_4 [6]),
        .R(RSTP));
  FDRE \delayMatch5_reg_reg[0][7] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\delayMatch5_reg_reg[0][13]_0 [7]),
        .Q(\delayMatch5_reg_reg[0]_4 [7]),
        .R(RSTP));
  FDRE \delayMatch5_reg_reg[0][8] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\delayMatch5_reg_reg[0][13]_0 [8]),
        .Q(\delayMatch5_reg_reg[0]_4 [8]),
        .R(RSTP));
  FDRE \delayMatch5_reg_reg[0][9] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\delayMatch5_reg_reg[0][13]_0 [9]),
        .Q(\delayMatch5_reg_reg[0]_4 [9]),
        .R(RSTP));
  FDRE \delayMatch5_reg_reg[1][0] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\delayMatch5_reg_reg[0]_4 [0]),
        .Q(\delayMatch5_reg_reg[1]_5 [0]),
        .R(RSTP));
  FDRE \delayMatch5_reg_reg[1][10] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\delayMatch5_reg_reg[0]_4 [10]),
        .Q(\delayMatch5_reg_reg[1]_5 [10]),
        .R(RSTP));
  FDRE \delayMatch5_reg_reg[1][11] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\delayMatch5_reg_reg[0]_4 [11]),
        .Q(\delayMatch5_reg_reg[1]_5 [11]),
        .R(RSTP));
  FDRE \delayMatch5_reg_reg[1][12] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\delayMatch5_reg_reg[0]_4 [12]),
        .Q(\delayMatch5_reg_reg[1]_5 [12]),
        .R(RSTP));
  FDRE \delayMatch5_reg_reg[1][13] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\delayMatch5_reg_reg[0]_4 [13]),
        .Q(\delayMatch5_reg_reg[1]_5 [13]),
        .R(RSTP));
  FDRE \delayMatch5_reg_reg[1][1] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\delayMatch5_reg_reg[0]_4 [1]),
        .Q(\delayMatch5_reg_reg[1]_5 [1]),
        .R(RSTP));
  FDRE \delayMatch5_reg_reg[1][2] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\delayMatch5_reg_reg[0]_4 [2]),
        .Q(\delayMatch5_reg_reg[1]_5 [2]),
        .R(RSTP));
  FDRE \delayMatch5_reg_reg[1][3] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\delayMatch5_reg_reg[0]_4 [3]),
        .Q(\delayMatch5_reg_reg[1]_5 [3]),
        .R(RSTP));
  FDRE \delayMatch5_reg_reg[1][4] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\delayMatch5_reg_reg[0]_4 [4]),
        .Q(\delayMatch5_reg_reg[1]_5 [4]),
        .R(RSTP));
  FDRE \delayMatch5_reg_reg[1][5] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\delayMatch5_reg_reg[0]_4 [5]),
        .Q(\delayMatch5_reg_reg[1]_5 [5]),
        .R(RSTP));
  FDRE \delayMatch5_reg_reg[1][6] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\delayMatch5_reg_reg[0]_4 [6]),
        .Q(\delayMatch5_reg_reg[1]_5 [6]),
        .R(RSTP));
  FDRE \delayMatch5_reg_reg[1][7] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\delayMatch5_reg_reg[0]_4 [7]),
        .Q(\delayMatch5_reg_reg[1]_5 [7]),
        .R(RSTP));
  FDRE \delayMatch5_reg_reg[1][8] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\delayMatch5_reg_reg[0]_4 [8]),
        .Q(\delayMatch5_reg_reg[1]_5 [8]),
        .R(RSTP));
  FDRE \delayMatch5_reg_reg[1][9] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\delayMatch5_reg_reg[0]_4 [9]),
        .Q(\delayMatch5_reg_reg[1]_5 [9]),
        .R(RSTP));
  (* SOFT_HLUTNM = "soft_lutpair70" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \delayMatch6_1_reg[0]_i_1 
       (.I0(Mux_out1[4]),
        .I1(GenPWM_out5),
        .I2(delayMatch6_1_reg),
        .O(Demux_out3[0]));
  (* SOFT_HLUTNM = "soft_lutpair70" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \delayMatch6_1_reg_1[0]_i_1 
       (.I0(Mux_out1[5]),
        .I1(GenPWM_out5),
        .I2(delayMatch6_1_reg_1),
        .O(Demux_out3[1]));
  (* SOFT_HLUTNM = "soft_lutpair68" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \delayMatch_1_reg[0]_i_1 
       (.I0(Mux_out1[0]),
        .I1(GenPWM_out5),
        .I2(delayMatch_1_reg),
        .O(Demux_out1[0]));
  (* SOFT_HLUTNM = "soft_lutpair68" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \delayMatch_1_reg_1[0]_i_1 
       (.I0(Mux_out1[1]),
        .I1(GenPWM_out5),
        .I2(delayMatch_1_reg_1),
        .O(Demux_out1[1]));
  FDRE \max_counter_value_1_reg[0] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\max_counter_value_1_reg[19]_0 [0]),
        .Q(max_counter_value_1[0]),
        .R(RSTP));
  FDRE \max_counter_value_1_reg[10] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\max_counter_value_1_reg[19]_0 [10]),
        .Q(max_counter_value_1[10]),
        .R(RSTP));
  FDRE \max_counter_value_1_reg[11] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\max_counter_value_1_reg[19]_0 [11]),
        .Q(max_counter_value_1[11]),
        .R(RSTP));
  FDRE \max_counter_value_1_reg[12] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\max_counter_value_1_reg[19]_0 [12]),
        .Q(max_counter_value_1[12]),
        .R(RSTP));
  FDRE \max_counter_value_1_reg[13] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\max_counter_value_1_reg[19]_0 [13]),
        .Q(max_counter_value_1[13]),
        .R(RSTP));
  FDRE \max_counter_value_1_reg[14] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\max_counter_value_1_reg[19]_0 [14]),
        .Q(max_counter_value_1[14]),
        .R(RSTP));
  FDRE \max_counter_value_1_reg[15] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\max_counter_value_1_reg[19]_0 [15]),
        .Q(max_counter_value_1[15]),
        .R(RSTP));
  FDRE \max_counter_value_1_reg[16] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\max_counter_value_1_reg[19]_0 [16]),
        .Q(max_counter_value_1[16]),
        .R(RSTP));
  FDRE \max_counter_value_1_reg[17] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\max_counter_value_1_reg[19]_0 [17]),
        .Q(max_counter_value_1[17]),
        .R(RSTP));
  FDRE \max_counter_value_1_reg[18] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\max_counter_value_1_reg[19]_0 [18]),
        .Q(max_counter_value_1[18]),
        .R(RSTP));
  FDRE \max_counter_value_1_reg[19] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\max_counter_value_1_reg[19]_0 [19]),
        .Q(max_counter_value_1[19]),
        .R(RSTP));
  FDRE \max_counter_value_1_reg[1] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\max_counter_value_1_reg[19]_0 [1]),
        .Q(max_counter_value_1[1]),
        .R(RSTP));
  FDRE \max_counter_value_1_reg[2] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\max_counter_value_1_reg[19]_0 [2]),
        .Q(max_counter_value_1[2]),
        .R(RSTP));
  FDRE \max_counter_value_1_reg[3] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\max_counter_value_1_reg[19]_0 [3]),
        .Q(max_counter_value_1[3]),
        .R(RSTP));
  FDRE \max_counter_value_1_reg[4] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\max_counter_value_1_reg[19]_0 [4]),
        .Q(max_counter_value_1[4]),
        .R(RSTP));
  FDRE \max_counter_value_1_reg[5] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\max_counter_value_1_reg[19]_0 [5]),
        .Q(max_counter_value_1[5]),
        .R(RSTP));
  FDRE \max_counter_value_1_reg[6] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\max_counter_value_1_reg[19]_0 [6]),
        .Q(max_counter_value_1[6]),
        .R(RSTP));
  FDRE \max_counter_value_1_reg[7] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\max_counter_value_1_reg[19]_0 [7]),
        .Q(max_counter_value_1[7]),
        .R(RSTP));
  FDRE \max_counter_value_1_reg[8] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\max_counter_value_1_reg[19]_0 [8]),
        .Q(max_counter_value_1[8]),
        .R(RSTP));
  FDRE \max_counter_value_1_reg[9] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\max_counter_value_1_reg[19]_0 [9]),
        .Q(max_counter_value_1[9]),
        .R(RSTP));
  (* SOFT_HLUTNM = "soft_lutpair71" *) 
  LUT2 #(
    .INIT(4'h8)) 
    \maximum_counter_value_1[13]_i_1 
       (.I0(\maximum_counter_value_1[18]_i_3_n_0 ),
        .I1(max_counter_value_1[13]),
        .O(\maximum_counter_value_1[13]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair55" *) 
  LUT2 #(
    .INIT(4'h8)) 
    \maximum_counter_value_1[15]_i_1 
       (.I0(\maximum_counter_value_1[18]_i_3_n_0 ),
        .I1(max_counter_value_1[15]),
        .O(\maximum_counter_value_1[15]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair56" *) 
  LUT2 #(
    .INIT(4'h8)) 
    \maximum_counter_value_1[16]_i_1 
       (.I0(\maximum_counter_value_1[18]_i_3_n_0 ),
        .I1(max_counter_value_1[16]),
        .O(\maximum_counter_value_1[16]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair71" *) 
  LUT2 #(
    .INIT(4'h8)) 
    \maximum_counter_value_1[17]_i_1 
       (.I0(\maximum_counter_value_1[18]_i_3_n_0 ),
        .I1(max_counter_value_1[17]),
        .O(\maximum_counter_value_1[17]_i_1_n_0 ));
  LUT3 #(
    .INIT(8'h08)) 
    \maximum_counter_value_1[18]_i_1 
       (.I0(maximum_counter_value10_in),
        .I1(CEP),
        .I2(RSTP),
        .O(\maximum_counter_value_1[18]_i_1_n_0 ));
  LUT2 #(
    .INIT(4'h8)) 
    \maximum_counter_value_1[18]_i_2 
       (.I0(\maximum_counter_value_1[18]_i_3_n_0 ),
        .I1(max_counter_value_1[18]),
        .O(\maximum_counter_value_1[18]_i_2_n_0 ));
  LUT6 #(
    .INIT(64'h00000000FFFFFFF7)) 
    \maximum_counter_value_1[18]_i_3 
       (.I0(\maximum_counter_value_1[8]_i_9_n_0 ),
        .I1(\maximum_counter_value_1[8]_i_8_n_0 ),
        .I2(max_counter_value_1[9]),
        .I3(max_counter_value_1[10]),
        .I4(max_counter_value_1[11]),
        .I5(RSTP),
        .O(\maximum_counter_value_1[18]_i_3_n_0 ));
  LUT4 #(
    .INIT(16'hFFA8)) 
    \maximum_counter_value_1[19]_i_1 
       (.I0(CEP),
        .I1(maximum_counter_value1__14),
        .I2(maximum_counter_value10_in),
        .I3(RSTP),
        .O(\maximum_counter_value_1[19]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair66" *) 
  LUT3 #(
    .INIT(8'h10)) 
    \maximum_counter_value_1[2]_i_1 
       (.I0(RSTP),
        .I1(maximum_counter_value10_in),
        .I2(max_counter_value_1[2]),
        .O(\maximum_counter_value_1[2]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair66" *) 
  LUT3 #(
    .INIT(8'h10)) 
    \maximum_counter_value_1[4]_i_1 
       (.I0(RSTP),
        .I1(maximum_counter_value10_in),
        .I2(max_counter_value_1[4]),
        .O(\maximum_counter_value_1[4]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair54" *) 
  LUT4 #(
    .INIT(16'h0F0E)) 
    \maximum_counter_value_1[5]_i_1 
       (.I0(max_counter_value_1[5]),
        .I1(maximum_counter_value10_in),
        .I2(RSTP),
        .I3(maximum_counter_value1__14),
        .O(p_1_in[5]));
  (* SOFT_HLUTNM = "soft_lutpair67" *) 
  LUT3 #(
    .INIT(8'h10)) 
    \maximum_counter_value_1[6]_i_1 
       (.I0(RSTP),
        .I1(maximum_counter_value10_in),
        .I2(max_counter_value_1[6]),
        .O(\maximum_counter_value_1[6]_i_1_n_0 ));
  LUT4 #(
    .INIT(16'h0020)) 
    \maximum_counter_value_1[7]_i_1 
       (.I0(maximum_counter_value1__14),
        .I1(maximum_counter_value10_in),
        .I2(CEP),
        .I3(RSTP),
        .O(\maximum_counter_value_1[7]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair67" *) 
  LUT3 #(
    .INIT(8'h10)) 
    \maximum_counter_value_1[7]_i_2 
       (.I0(RSTP),
        .I1(maximum_counter_value10_in),
        .I2(max_counter_value_1[7]),
        .O(\maximum_counter_value_1[7]_i_2_n_0 ));
  LUT2 #(
    .INIT(4'h7)) 
    \maximum_counter_value_1[8]_i_10 
       (.I0(max_counter_value_1[8]),
        .I1(max_counter_value_1[5]),
        .O(\maximum_counter_value_1[8]_i_10_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair53" *) 
  LUT2 #(
    .INIT(4'h1)) 
    \maximum_counter_value_1[8]_i_11 
       (.I0(max_counter_value_1[10]),
        .I1(max_counter_value_1[11]),
        .O(\maximum_counter_value_1[8]_i_11_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair55" *) 
  LUT4 #(
    .INIT(16'h0001)) 
    \maximum_counter_value_1[8]_i_12 
       (.I0(max_counter_value_1[15]),
        .I1(max_counter_value_1[14]),
        .I2(max_counter_value_1[13]),
        .I3(max_counter_value_1[12]),
        .O(\maximum_counter_value_1[8]_i_12_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair54" *) 
  LUT4 #(
    .INIT(16'h0F0E)) 
    \maximum_counter_value_1[8]_i_2 
       (.I0(max_counter_value_1[8]),
        .I1(maximum_counter_value10_in),
        .I2(RSTP),
        .I3(maximum_counter_value1__14),
        .O(p_1_in[8]));
  LUT6 #(
    .INIT(64'hFFFFFFFFFFA80000)) 
    \maximum_counter_value_1[8]_i_3 
       (.I0(max_counter_value_1[13]),
        .I1(\maximum_counter_value_1[8]_i_5_n_0 ),
        .I2(\maximum_counter_value_1[8]_i_6_n_0 ),
        .I3(max_counter_value_1[14]),
        .I4(\maximum_counter_value_1[8]_i_7_n_0 ),
        .I5(max_counter_value_1[19]),
        .O(maximum_counter_value10_in));
  (* SOFT_HLUTNM = "soft_lutpair53" *) 
  LUT5 #(
    .INIT(32'h01000000)) 
    \maximum_counter_value_1[8]_i_4 
       (.I0(max_counter_value_1[11]),
        .I1(max_counter_value_1[10]),
        .I2(max_counter_value_1[9]),
        .I3(\maximum_counter_value_1[8]_i_8_n_0 ),
        .I4(\maximum_counter_value_1[8]_i_9_n_0 ),
        .O(maximum_counter_value1__14));
  LUT6 #(
    .INIT(64'h0000FFFF0000FFFE)) 
    \maximum_counter_value_1[8]_i_5 
       (.I0(max_counter_value_1[4]),
        .I1(max_counter_value_1[1]),
        .I2(max_counter_value_1[3]),
        .I3(max_counter_value_1[2]),
        .I4(\maximum_counter_value_1[8]_i_10_n_0 ),
        .I5(max_counter_value_1[0]),
        .O(\maximum_counter_value_1[8]_i_5_n_0 ));
  LUT6 #(
    .INIT(64'hFFFFFDFDFFFDFDFD)) 
    \maximum_counter_value_1[8]_i_6 
       (.I0(\maximum_counter_value_1[8]_i_11_n_0 ),
        .I1(max_counter_value_1[9]),
        .I2(max_counter_value_1[12]),
        .I3(max_counter_value_1[7]),
        .I4(max_counter_value_1[8]),
        .I5(max_counter_value_1[6]),
        .O(\maximum_counter_value_1[8]_i_6_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair56" *) 
  LUT4 #(
    .INIT(16'h8000)) 
    \maximum_counter_value_1[8]_i_7 
       (.I0(max_counter_value_1[16]),
        .I1(max_counter_value_1[15]),
        .I2(max_counter_value_1[18]),
        .I3(max_counter_value_1[17]),
        .O(\maximum_counter_value_1[8]_i_7_n_0 ));
  LUT5 #(
    .INIT(32'h00010000)) 
    \maximum_counter_value_1[8]_i_8 
       (.I0(max_counter_value_1[16]),
        .I1(max_counter_value_1[17]),
        .I2(max_counter_value_1[18]),
        .I3(max_counter_value_1[19]),
        .I4(\maximum_counter_value_1[8]_i_12_n_0 ),
        .O(\maximum_counter_value_1[8]_i_8_n_0 ));
  LUT6 #(
    .INIT(64'hFFFFFFFF1FFFFFFF)) 
    \maximum_counter_value_1[8]_i_9 
       (.I0(max_counter_value_1[2]),
        .I1(max_counter_value_1[3]),
        .I2(max_counter_value_1[7]),
        .I3(max_counter_value_1[6]),
        .I4(max_counter_value_1[4]),
        .I5(\maximum_counter_value_1[8]_i_10_n_0 ),
        .O(\maximum_counter_value_1[8]_i_9_n_0 ));
  FDRE \maximum_counter_value_1_reg[0] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(max_counter_value_1[0]),
        .Q(maximum_counter_value_1[0]),
        .R(\maximum_counter_value_1[19]_i_1_n_0 ));
  FDRE \maximum_counter_value_1_reg[10] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(max_counter_value_1[10]),
        .Q(maximum_counter_value_1[10]),
        .R(\maximum_counter_value_1[19]_i_1_n_0 ));
  FDRE \maximum_counter_value_1_reg[11] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(max_counter_value_1[11]),
        .Q(maximum_counter_value_1[11]),
        .R(\maximum_counter_value_1[19]_i_1_n_0 ));
  FDRE \maximum_counter_value_1_reg[12] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(max_counter_value_1[12]),
        .Q(maximum_counter_value_1[12]),
        .R(\maximum_counter_value_1[19]_i_1_n_0 ));
  FDSE \maximum_counter_value_1_reg[13] 
       (.C(IPCORE_CLK),
        .CE(\maximum_counter_value_1_reg[8]_0 ),
        .D(\maximum_counter_value_1[13]_i_1_n_0 ),
        .Q(maximum_counter_value_1[13]),
        .S(\maximum_counter_value_1[18]_i_1_n_0 ));
  FDRE \maximum_counter_value_1_reg[14] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(max_counter_value_1[14]),
        .Q(maximum_counter_value_1[14]),
        .R(\maximum_counter_value_1[19]_i_1_n_0 ));
  FDSE \maximum_counter_value_1_reg[15] 
       (.C(IPCORE_CLK),
        .CE(\maximum_counter_value_1_reg[8]_0 ),
        .D(\maximum_counter_value_1[15]_i_1_n_0 ),
        .Q(maximum_counter_value_1[15]),
        .S(\maximum_counter_value_1[18]_i_1_n_0 ));
  FDSE \maximum_counter_value_1_reg[16] 
       (.C(IPCORE_CLK),
        .CE(\maximum_counter_value_1_reg[8]_0 ),
        .D(\maximum_counter_value_1[16]_i_1_n_0 ),
        .Q(maximum_counter_value_1[16]),
        .S(\maximum_counter_value_1[18]_i_1_n_0 ));
  FDSE \maximum_counter_value_1_reg[17] 
       (.C(IPCORE_CLK),
        .CE(\maximum_counter_value_1_reg[8]_0 ),
        .D(\maximum_counter_value_1[17]_i_1_n_0 ),
        .Q(maximum_counter_value_1[17]),
        .S(\maximum_counter_value_1[18]_i_1_n_0 ));
  FDSE \maximum_counter_value_1_reg[18] 
       (.C(IPCORE_CLK),
        .CE(\maximum_counter_value_1_reg[8]_0 ),
        .D(\maximum_counter_value_1[18]_i_2_n_0 ),
        .Q(maximum_counter_value_1[18]),
        .S(\maximum_counter_value_1[18]_i_1_n_0 ));
  FDRE \maximum_counter_value_1_reg[19] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(max_counter_value_1[19]),
        .Q(maximum_counter_value_1[19]),
        .R(\maximum_counter_value_1[19]_i_1_n_0 ));
  FDRE \maximum_counter_value_1_reg[1] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(max_counter_value_1[1]),
        .Q(maximum_counter_value_1[1]),
        .R(\maximum_counter_value_1[19]_i_1_n_0 ));
  FDSE \maximum_counter_value_1_reg[2] 
       (.C(IPCORE_CLK),
        .CE(\maximum_counter_value_1_reg[8]_0 ),
        .D(\maximum_counter_value_1[2]_i_1_n_0 ),
        .Q(maximum_counter_value_1[2]),
        .S(\maximum_counter_value_1[7]_i_1_n_0 ));
  FDRE \maximum_counter_value_1_reg[3] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(max_counter_value_1[3]),
        .Q(maximum_counter_value_1[3]),
        .R(\maximum_counter_value_1[19]_i_1_n_0 ));
  FDSE \maximum_counter_value_1_reg[4] 
       (.C(IPCORE_CLK),
        .CE(\maximum_counter_value_1_reg[8]_0 ),
        .D(\maximum_counter_value_1[4]_i_1_n_0 ),
        .Q(maximum_counter_value_1[4]),
        .S(\maximum_counter_value_1[7]_i_1_n_0 ));
  FDRE \maximum_counter_value_1_reg[5] 
       (.C(IPCORE_CLK),
        .CE(\maximum_counter_value_1_reg[8]_0 ),
        .D(p_1_in[5]),
        .Q(maximum_counter_value_1[5]),
        .R(1'b0));
  FDSE \maximum_counter_value_1_reg[6] 
       (.C(IPCORE_CLK),
        .CE(\maximum_counter_value_1_reg[8]_0 ),
        .D(\maximum_counter_value_1[6]_i_1_n_0 ),
        .Q(maximum_counter_value_1[6]),
        .S(\maximum_counter_value_1[7]_i_1_n_0 ));
  FDSE \maximum_counter_value_1_reg[7] 
       (.C(IPCORE_CLK),
        .CE(\maximum_counter_value_1_reg[8]_0 ),
        .D(\maximum_counter_value_1[7]_i_2_n_0 ),
        .Q(maximum_counter_value_1[7]),
        .S(\maximum_counter_value_1[7]_i_1_n_0 ));
  FDRE \maximum_counter_value_1_reg[8] 
       (.C(IPCORE_CLK),
        .CE(\maximum_counter_value_1_reg[8]_0 ),
        .D(p_1_in[8]),
        .Q(maximum_counter_value_1[8]),
        .R(1'b0));
  FDRE \maximum_counter_value_1_reg[9] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(max_counter_value_1[9]),
        .Q(maximum_counter_value_1[9]),
        .R(\maximum_counter_value_1[19]_i_1_n_0 ));
  FDRE \min_pulse_width_AXI_1_reg[0] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\min_pulse_width_AXI_1_reg[13]_0 [0]),
        .Q(min_pulse_width[0]),
        .R(RSTP));
  FDRE \min_pulse_width_AXI_1_reg[10] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\min_pulse_width_AXI_1_reg[13]_0 [10]),
        .Q(min_pulse_width[10]),
        .R(RSTP));
  FDRE \min_pulse_width_AXI_1_reg[11] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\min_pulse_width_AXI_1_reg[13]_0 [11]),
        .Q(min_pulse_width[11]),
        .R(RSTP));
  FDRE \min_pulse_width_AXI_1_reg[12] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\min_pulse_width_AXI_1_reg[13]_0 [12]),
        .Q(min_pulse_width[12]),
        .R(RSTP));
  FDRE \min_pulse_width_AXI_1_reg[13] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\min_pulse_width_AXI_1_reg[13]_0 [13]),
        .Q(min_pulse_width[13]),
        .R(RSTP));
  FDRE \min_pulse_width_AXI_1_reg[1] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\min_pulse_width_AXI_1_reg[13]_0 [1]),
        .Q(min_pulse_width[1]),
        .R(RSTP));
  FDRE \min_pulse_width_AXI_1_reg[2] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\min_pulse_width_AXI_1_reg[13]_0 [2]),
        .Q(min_pulse_width[2]),
        .R(RSTP));
  FDRE \min_pulse_width_AXI_1_reg[3] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\min_pulse_width_AXI_1_reg[13]_0 [3]),
        .Q(min_pulse_width[3]),
        .R(RSTP));
  FDRE \min_pulse_width_AXI_1_reg[4] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\min_pulse_width_AXI_1_reg[13]_0 [4]),
        .Q(min_pulse_width[4]),
        .R(RSTP));
  FDRE \min_pulse_width_AXI_1_reg[5] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\min_pulse_width_AXI_1_reg[13]_0 [5]),
        .Q(min_pulse_width[5]),
        .R(RSTP));
  FDRE \min_pulse_width_AXI_1_reg[6] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\min_pulse_width_AXI_1_reg[13]_0 [6]),
        .Q(min_pulse_width[6]),
        .R(RSTP));
  FDRE \min_pulse_width_AXI_1_reg[7] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\min_pulse_width_AXI_1_reg[13]_0 [7]),
        .Q(min_pulse_width[7]),
        .R(RSTP));
  FDRE \min_pulse_width_AXI_1_reg[8] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\min_pulse_width_AXI_1_reg[13]_0 [8]),
        .Q(min_pulse_width[8]),
        .R(RSTP));
  FDRE \min_pulse_width_AXI_1_reg[9] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\min_pulse_width_AXI_1_reg[13]_0 [9]),
        .Q(min_pulse_width[9]),
        .R(RSTP));
  LUT2 #(
    .INIT(4'h1)) 
    \minus_out1_1[13]_i_10 
       (.I0(min_pulse_width[10]),
        .I1(min_pulse_width[11]),
        .O(\minus_out1_1[13]_i_10_n_0 ));
  LUT2 #(
    .INIT(4'h1)) 
    \minus_out1_1[13]_i_11 
       (.I0(min_pulse_width[8]),
        .I1(min_pulse_width[9]),
        .O(\minus_out1_1[13]_i_11_n_0 ));
  LUT2 #(
    .INIT(4'h1)) 
    \minus_out1_1[13]_i_12 
       (.I0(min_pulse_width[6]),
        .I1(min_pulse_width[7]),
        .O(\minus_out1_1[13]_i_12_n_0 ));
  LUT2 #(
    .INIT(4'h1)) 
    \minus_out1_1[13]_i_13 
       (.I0(min_pulse_width[4]),
        .I1(min_pulse_width[5]),
        .O(\minus_out1_1[13]_i_13_n_0 ));
  LUT2 #(
    .INIT(4'h1)) 
    \minus_out1_1[13]_i_14 
       (.I0(min_pulse_width[2]),
        .I1(min_pulse_width[3]),
        .O(\minus_out1_1[13]_i_14_n_0 ));
  LUT2 #(
    .INIT(4'h1)) 
    \minus_out1_1[13]_i_15 
       (.I0(min_pulse_width[1]),
        .I1(min_pulse_width[0]),
        .O(\minus_out1_1[13]_i_15_n_0 ));
  LUT2 #(
    .INIT(4'hE)) 
    \minus_out1_1[13]_i_3 
       (.I0(min_pulse_width[10]),
        .I1(min_pulse_width[11]),
        .O(\minus_out1_1[13]_i_3_n_0 ));
  LUT2 #(
    .INIT(4'hE)) 
    \minus_out1_1[13]_i_4 
       (.I0(min_pulse_width[8]),
        .I1(min_pulse_width[9]),
        .O(\minus_out1_1[13]_i_4_n_0 ));
  LUT2 #(
    .INIT(4'hE)) 
    \minus_out1_1[13]_i_5 
       (.I0(min_pulse_width[6]),
        .I1(min_pulse_width[7]),
        .O(\minus_out1_1[13]_i_5_n_0 ));
  LUT2 #(
    .INIT(4'hE)) 
    \minus_out1_1[13]_i_6 
       (.I0(min_pulse_width[4]),
        .I1(min_pulse_width[5]),
        .O(\minus_out1_1[13]_i_6_n_0 ));
  LUT2 #(
    .INIT(4'hE)) 
    \minus_out1_1[13]_i_7 
       (.I0(min_pulse_width[2]),
        .I1(min_pulse_width[3]),
        .O(\minus_out1_1[13]_i_7_n_0 ));
  LUT2 #(
    .INIT(4'hE)) 
    \minus_out1_1[13]_i_8__1 
       (.I0(min_pulse_width[0]),
        .I1(min_pulse_width[1]),
        .O(\minus_out1_1[13]_i_8__1_n_0 ));
  LUT2 #(
    .INIT(4'h2)) 
    \minus_out1_1[13]_i_9__0 
       (.I0(min_pulse_width[12]),
        .I1(min_pulse_width[13]),
        .O(\minus_out1_1[13]_i_9__0_n_0 ));
  (* COMPARATOR_THRESHOLD = "11" *) 
  CARRY8 \minus_out1_1_reg[13]_i_2__0 
       (.CI(1'b0),
        .CI_TOP(1'b0),
        .CO({\NLW_minus_out1_1_reg[13]_i_2__0_CO_UNCONNECTED [7],Saturation1_out110_in,\minus_out1_1_reg[13]_i_2__0_n_2 ,\minus_out1_1_reg[13]_i_2__0_n_3 ,\minus_out1_1_reg[13]_i_2__0_n_4 ,\minus_out1_1_reg[13]_i_2__0_n_5 ,\minus_out1_1_reg[13]_i_2__0_n_6 ,\minus_out1_1_reg[13]_i_2__0_n_7 }),
        .DI({1'b0,1'b0,\minus_out1_1[13]_i_3_n_0 ,\minus_out1_1[13]_i_4_n_0 ,\minus_out1_1[13]_i_5_n_0 ,\minus_out1_1[13]_i_6_n_0 ,\minus_out1_1[13]_i_7_n_0 ,\minus_out1_1[13]_i_8__1_n_0 }),
        .O(\NLW_minus_out1_1_reg[13]_i_2__0_O_UNCONNECTED [7:0]),
        .S({1'b0,\minus_out1_1[13]_i_9__0_n_0 ,\minus_out1_1[13]_i_10_n_0 ,\minus_out1_1[13]_i_11_n_0 ,\minus_out1_1[13]_i_12_n_0 ,\minus_out1_1[13]_i_13_n_0 ,\minus_out1_1[13]_i_14_n_0 ,\minus_out1_1[13]_i_15_n_0 }));
  FDRE \reduced_reg_reg[0] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(PWM_en_AXI_2_reg_0),
        .Q(reduced_reg__0),
        .R(RSTP));
  FDRE \reduced_reg_reg[1] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(reduced_reg__0),
        .Q(reduced_reg),
        .R(RSTP));
  zusys_PWM_SS_3L_ip_0_0_PWM_SS_3L_ip_src_Counter_Ctrl u_Counter_Ctrl
       (.CEP(CEP),
        .CO(Counter_Ctrl_out4),
        .Counter_Ctrl_out3(Counter_Ctrl_out3),
        .Counter_Ctrl_out4_1_reg({u_LimitPulseWidth_c_n_28,u_LimitPulseWidth_c_n_29,u_LimitPulseWidth_c_n_30,u_LimitPulseWidth_c_n_31,u_LimitPulseWidth_c_n_32,u_LimitPulseWidth_c_n_33,u_LimitPulseWidth_c_n_34}),
        .HDL_Counter2_count_reg(HDL_Counter2_count_reg),
        .\HDL_Counter2_count_reg[0] ({u_Counter_Ctrl_n_30,u_Counter_Ctrl_n_31,u_Counter_Ctrl_n_32,u_Counter_Ctrl_n_33,u_Counter_Ctrl_n_34,u_Counter_Ctrl_n_35,u_Counter_Ctrl_n_36,u_Counter_Ctrl_n_37}),
        .\HDL_Counter2_count_reg[0]_0 ({u_Counter_Ctrl_n_38,u_Counter_Ctrl_n_39,u_Counter_Ctrl_n_40,u_Counter_Ctrl_n_41}),
        .IPCORE_CLK(IPCORE_CLK),
        .O({u_Counter_Ctrl_n_22,u_Counter_Ctrl_n_23,u_Counter_Ctrl_n_24,u_Counter_Ctrl_n_25,u_Counter_Ctrl_n_26,u_Counter_Ctrl_n_27,u_Counter_Ctrl_n_28,u_Counter_Ctrl_n_29}),
        .RSTP(RSTP),
        .S({u_Modulator_a_n_23,u_Modulator_a_n_24,u_Modulator_a_n_25,u_Modulator_a_n_26}),
        .maximum_counter_value_1(maximum_counter_value_1));
  zusys_PWM_SS_3L_ip_0_0_PWM_SS_3L_ip_src_LimitPulseWidth_a u_LimitPulseWidth_a
       (.B(LimitPulseWidth_a_out1),
        .CEP(CEP),
        .CO(Counter_Ctrl_out4),
        .D(PWM_en_AXI_2_reg_0),
        .\Delay_out1_reg[0] (u_LimitPulseWidth_c_n_25),
        .\Delay_out1_reg[0]_0 (u_LimitPulseWidth_c_n_23),
        .\Delay_out1_reg[13] (Delay_out1),
        .\Delay_out1_reg[13]_0 (\delayMatch1_reg_reg[1]_1 ),
        .\Delay_out1_reg[13]_1 (u_LimitPulseWidth_c_n_26),
        .\Delay_out1_reg[13]_2 (u_LimitPulseWidth_c_n_27),
        .\Delay_out1_reg[13]_3 (u_LimitPulseWidth_c_n_24),
        .HDL_Counter2_count_reg({HDL_Counter2_count_reg[19:13],HDL_Counter2_count_reg[11],HDL_Counter2_count_reg[4],HDL_Counter2_count_reg[2:0]}),
        .\HDL_Counter2_count_reg[11]_0 (u_LimitPulseWidth_a_n_24),
        .HDL_Counter2_count_reg_11_sp_1(u_LimitPulseWidth_a_n_17),
        .IPCORE_CLK(IPCORE_CLK),
        .OR_out1__0(OR_out1__0),
        .Q(min_pulse_width),
        .RSTP(RSTP),
        .\delayMatch1_reg_reg[1][11] (u_LimitPulseWidth_a_n_18),
        .\delayMatch1_reg_reg[1][13] (u_LimitPulseWidth_a_n_1),
        .\delayMatch1_reg_reg[1][1] (u_LimitPulseWidth_a_n_23),
        .\delayMatch1_reg_reg[1][3] (u_LimitPulseWidth_a_n_22),
        .\delayMatch1_reg_reg[1][5] (u_LimitPulseWidth_a_n_21),
        .\delayMatch1_reg_reg[1][7] (u_LimitPulseWidth_a_n_20),
        .\delayMatch1_reg_reg[1][9] (u_LimitPulseWidth_a_n_19),
        .\min_pulse_width_AXI_1_reg[0] (u_LimitPulseWidth_a_n_25),
        .\min_pulse_width_AXI_1_reg[10] (u_LimitPulseWidth_a_n_29),
        .\min_pulse_width_AXI_1_reg[4] (u_LimitPulseWidth_a_n_0),
        .\min_pulse_width_AXI_1_reg[5] (u_LimitPulseWidth_a_n_26),
        .\min_pulse_width_AXI_1_reg[8] (u_LimitPulseWidth_a_n_27),
        .\min_pulse_width_AXI_1_reg[9] (u_LimitPulseWidth_a_n_28),
        .\minus_out1_1_reg[12]_0 (u_LimitPulseWidth_c_n_0));
  zusys_PWM_SS_3L_ip_0_0_PWM_SS_3L_ip_src_LimitPulseWidth_b u_LimitPulseWidth_b
       (.B(LimitPulseWidth_b_out1),
        .CEP(CEP),
        .CO(Counter_Ctrl_out4),
        .D(PWM_en_AXI_2_reg_0),
        .\Delay1_out1_reg[0] (u_LimitPulseWidth_a_n_24),
        .\Delay1_out1_reg[0]_0 (u_LimitPulseWidth_c_n_25),
        .\Delay1_out1_reg[0]_1 (u_LimitPulseWidth_c_n_23),
        .\Delay1_out1_reg[13] (Delay1_out1),
        .\Delay1_out1_reg[13]_0 (\delayMatch3_reg_reg[1]_3 ),
        .\Delay1_out1_reg[13]_1 (u_LimitPulseWidth_a_n_17),
        .HDL_Counter2_count_reg(HDL_Counter2_count_reg[19]),
        .IPCORE_CLK(IPCORE_CLK),
        .PWM_en_AXI_2_reg(u_LimitPulseWidth_b_n_1),
        .Q(min_pulse_width),
        .RSTP(RSTP),
        .\delayMatch3_reg_reg[1][11] (u_LimitPulseWidth_b_n_16),
        .\delayMatch3_reg_reg[1][13] (u_LimitPulseWidth_b_n_0),
        .\delayMatch3_reg_reg[1][1] (u_LimitPulseWidth_b_n_21),
        .\delayMatch3_reg_reg[1][3] (u_LimitPulseWidth_b_n_20),
        .\delayMatch3_reg_reg[1][5] (u_LimitPulseWidth_b_n_19),
        .\delayMatch3_reg_reg[1][7] (u_LimitPulseWidth_b_n_18),
        .\delayMatch3_reg_reg[1][9] (u_LimitPulseWidth_b_n_17),
        .\minus_out1_1_reg[10]_0 (u_LimitPulseWidth_a_n_28),
        .\minus_out1_1_reg[11]_0 (u_LimitPulseWidth_a_n_29),
        .\minus_out1_1_reg[12]_0 (u_LimitPulseWidth_c_n_0),
        .\minus_out1_1_reg[5]_0 (u_LimitPulseWidth_a_n_25),
        .\minus_out1_1_reg[6]_0 (u_LimitPulseWidth_a_n_26),
        .\minus_out1_1_reg[7]_0 (u_LimitPulseWidth_a_n_0),
        .\minus_out1_1_reg[9]_0 (u_LimitPulseWidth_a_n_27));
  zusys_PWM_SS_3L_ip_0_0_PWM_SS_3L_ip_src_LimitPulseWidth_c u_LimitPulseWidth_c
       (.B(LimitPulseWidth_c_out1),
        .CEP(CEP),
        .CO(Saturation1_out110_in),
        .D(PWM_en_AXI_2_reg_0),
        .\Delay2_out1_reg[0] (u_LimitPulseWidth_a_n_24),
        .\Delay2_out1_reg[13] (Delay2_out1),
        .\Delay2_out1_reg[13]_0 (\delayMatch5_reg_reg[1]_5 ),
        .\Delay2_out1_reg[13]_1 (u_LimitPulseWidth_a_n_17),
        .\Delay2_out1_reg[13]_2 (Counter_Ctrl_out4),
        .HDL_Counter2_count_reg(HDL_Counter2_count_reg),
        .\HDL_Counter2_count_reg[18] ({u_LimitPulseWidth_c_n_28,u_LimitPulseWidth_c_n_29,u_LimitPulseWidth_c_n_30,u_LimitPulseWidth_c_n_31,u_LimitPulseWidth_c_n_32,u_LimitPulseWidth_c_n_33,u_LimitPulseWidth_c_n_34}),
        .HDL_Counter2_count_reg_10_sp_1(u_LimitPulseWidth_c_n_26),
        .HDL_Counter2_count_reg_13_sp_1(u_LimitPulseWidth_c_n_24),
        .HDL_Counter2_count_reg_16_sp_1(u_LimitPulseWidth_c_n_23),
        .HDL_Counter2_count_reg_1_sp_1(u_LimitPulseWidth_c_n_25),
        .HDL_Counter2_count_reg_7_sp_1(u_LimitPulseWidth_c_n_27),
        .IPCORE_CLK(IPCORE_CLK),
        .PWM_en_AXI_2_reg(u_LimitPulseWidth_c_n_2),
        .Q(min_pulse_width),
        .RSTP(RSTP),
        .\delayMatch5_reg_reg[1][11] (u_LimitPulseWidth_c_n_17),
        .\delayMatch5_reg_reg[1][13] (u_LimitPulseWidth_c_n_1),
        .\delayMatch5_reg_reg[1][1] (u_LimitPulseWidth_c_n_22),
        .\delayMatch5_reg_reg[1][3] (u_LimitPulseWidth_c_n_21),
        .\delayMatch5_reg_reg[1][5] (u_LimitPulseWidth_c_n_20),
        .\delayMatch5_reg_reg[1][7] (u_LimitPulseWidth_c_n_19),
        .\delayMatch5_reg_reg[1][9] (u_LimitPulseWidth_c_n_18),
        .maximum_counter_value_1(maximum_counter_value_1),
        .\min_pulse_width_AXI_1_reg[9] (u_LimitPulseWidth_c_n_0),
        .\minus_out1_1_reg[10]_0 (u_LimitPulseWidth_a_n_28),
        .\minus_out1_1_reg[11]_0 (u_LimitPulseWidth_a_n_29),
        .\minus_out1_1_reg[5]_0 (u_LimitPulseWidth_a_n_25),
        .\minus_out1_1_reg[6]_0 (u_LimitPulseWidth_a_n_26),
        .\minus_out1_1_reg[7]_0 (u_LimitPulseWidth_a_n_0),
        .\minus_out1_1_reg[9]_0 (u_LimitPulseWidth_a_n_27));
  zusys_PWM_SS_3L_ip_0_0_PWM_SS_3L_ip_src_Modulator_a u_Modulator_a
       (.AND_out10_carry__0_0(modulating_signal_in_clock_cycles_1_reg__0_0),
        .B(LimitPulseWidth_a_out1),
        .CEP(CEP),
        .Counter_Ctrl_out3(Counter_Ctrl_out3),
        .D({u_Modulator_a_n_21,Modulator_a_out1}),
        .DI(u_Modulator_a_n_27),
        .HDL_Counter2_count_reg(HDL_Counter2_count_reg),
        .IPCORE_CLK(IPCORE_CLK),
        .P(modulating_signal_in_clock_cycles_1_reg__0),
        .RSTP(RSTP),
        .S({u_Modulator_a_n_23,u_Modulator_a_n_24,u_Modulator_a_n_25,u_Modulator_a_n_26}),
        .maximum_counter_value_1(maximum_counter_value_1),
        .\reduced_reg_1_reg[1][20]_0 (u_Modulator_a_n_28),
        .\reduced_reg_1_reg[1]_9 (\reduced_reg_1_reg[1]_9 ),
        .\reduced_reg_reg[1][14]_0 ({u_Modulator_a_n_29,u_Modulator_a_n_30,u_Modulator_a_n_31,u_Modulator_a_n_32,u_Modulator_a_n_33,u_Modulator_a_n_34,u_Modulator_a_n_35,u_Modulator_a_n_36}),
        .\reduced_reg_reg[1][14]_1 ({u_Modulator_a_n_37,u_Modulator_a_n_38,u_Modulator_a_n_39,u_Modulator_a_n_40,u_Modulator_a_n_41,u_Modulator_a_n_42,u_Modulator_a_n_43,u_Modulator_a_n_44}),
        .\reduced_reg_reg[1][14]_2 ({u_Modulator_a_n_49,u_Modulator_a_n_50,u_Modulator_a_n_51,u_Modulator_a_n_52,u_Modulator_a_n_53,u_Modulator_a_n_54,u_Modulator_a_n_55,u_Modulator_a_n_56}),
        .\reduced_reg_reg[1][14]_3 ({u_Modulator_a_n_57,u_Modulator_a_n_58,u_Modulator_a_n_59,u_Modulator_a_n_60,u_Modulator_a_n_61,u_Modulator_a_n_62,u_Modulator_a_n_63,u_Modulator_a_n_64}),
        .\reduced_reg_reg[1][18]_0 ({u_Modulator_a_n_45,u_Modulator_a_n_46}),
        .\reduced_reg_reg[1][18]_1 ({u_Modulator_a_n_47,u_Modulator_a_n_48}),
        .\reduced_reg_reg[1][18]_2 ({u_Modulator_a_n_65,u_Modulator_a_n_66}),
        .\reduced_reg_reg[1][18]_3 ({u_Modulator_a_n_67,u_Modulator_a_n_68}));
  zusys_PWM_SS_3L_ip_0_0_PWM_SS_3L_ip_src_Modulator_b u_Modulator_b
       (.\AND_out10_inferred__0/i__carry__0_0 ({u_Modulator_a_n_37,u_Modulator_a_n_38,u_Modulator_a_n_39,u_Modulator_a_n_40,u_Modulator_a_n_41,u_Modulator_a_n_42,u_Modulator_a_n_43,u_Modulator_a_n_44}),
        .\AND_out10_inferred__0/i__carry__0_1 ({u_Modulator_a_n_29,u_Modulator_a_n_30,u_Modulator_a_n_31,u_Modulator_a_n_32,u_Modulator_a_n_33,u_Modulator_a_n_34,u_Modulator_a_n_35,u_Modulator_a_n_36}),
        .B(LimitPulseWidth_b_out1),
        .CEP(CEP),
        .D({u_Modulator_b_n_21,Modulator_b_out1}),
        .DI(u_Modulator_a_n_27),
        .IPCORE_CLK(IPCORE_CLK),
        .P(modulating_signal_in_clock_cycles_1_reg__0),
        .RSTP(RSTP),
        .\Switch4_out1_1_reg[0] ({u_Modulator_a_n_47,u_Modulator_a_n_48}),
        .\Switch4_out1_1_reg[0]_0 ({u_Modulator_a_n_45,u_Modulator_a_n_46}),
        .maximum_counter_value_1(maximum_counter_value_1),
        .\reduced_reg_1_reg[1]_9 (\reduced_reg_1_reg[1]_9 ));
  zusys_PWM_SS_3L_ip_0_0_PWM_SS_3L_ip_src_Modulator_c u_Modulator_c
       (.\AND_out10_inferred__0/i__carry__0_0 ({u_Modulator_a_n_57,u_Modulator_a_n_58,u_Modulator_a_n_59,u_Modulator_a_n_60,u_Modulator_a_n_61,u_Modulator_a_n_62,u_Modulator_a_n_63,u_Modulator_a_n_64}),
        .\AND_out10_inferred__0/i__carry__0_1 ({u_Modulator_a_n_49,u_Modulator_a_n_50,u_Modulator_a_n_51,u_Modulator_a_n_52,u_Modulator_a_n_53,u_Modulator_a_n_54,u_Modulator_a_n_55,u_Modulator_a_n_56}),
        .B(LimitPulseWidth_c_out1),
        .CEP(CEP),
        .D({u_Modulator_c_n_21,Modulator_c_out1}),
        .IPCORE_CLK(IPCORE_CLK),
        .P(modulating_signal_in_clock_cycles_1_reg__0_0),
        .RSTP(RSTP),
        .\Switch5_out1_1_reg[0] ({u_Modulator_a_n_67,u_Modulator_a_n_68}),
        .\Switch5_out1_1_reg[0]_0 ({u_Modulator_a_n_65,u_Modulator_a_n_66}),
        .\Switch5_out1_1_reg[1] (u_Modulator_a_n_28),
        .maximum_counter_value_1(maximum_counter_value_1),
        .\reduced_reg_1_reg[1]_9 (\reduced_reg_1_reg[1]_9 ));
endmodule

(* ORIG_REF_NAME = "PWM_SS_3L_ip_src_LimitPulseWidth_a" *) 
module zusys_PWM_SS_3L_ip_0_0_PWM_SS_3L_ip_src_LimitPulseWidth_a
   (\min_pulse_width_AXI_1_reg[4] ,
    \delayMatch1_reg_reg[1][13] ,
    OR_out1__0,
    B,
    HDL_Counter2_count_reg_11_sp_1,
    \delayMatch1_reg_reg[1][11] ,
    \delayMatch1_reg_reg[1][9] ,
    \delayMatch1_reg_reg[1][7] ,
    \delayMatch1_reg_reg[1][5] ,
    \delayMatch1_reg_reg[1][3] ,
    \delayMatch1_reg_reg[1][1] ,
    \HDL_Counter2_count_reg[11]_0 ,
    \min_pulse_width_AXI_1_reg[0] ,
    \min_pulse_width_AXI_1_reg[5] ,
    \min_pulse_width_AXI_1_reg[8] ,
    \min_pulse_width_AXI_1_reg[9] ,
    \min_pulse_width_AXI_1_reg[10] ,
    RSTP,
    CEP,
    IPCORE_CLK,
    Q,
    \minus_out1_1_reg[12]_0 ,
    \Delay_out1_reg[13] ,
    \Delay_out1_reg[13]_0 ,
    D,
    HDL_Counter2_count_reg,
    CO,
    \Delay_out1_reg[0] ,
    \Delay_out1_reg[0]_0 ,
    \Delay_out1_reg[13]_1 ,
    \Delay_out1_reg[13]_2 ,
    \Delay_out1_reg[13]_3 );
  output \min_pulse_width_AXI_1_reg[4] ;
  output \delayMatch1_reg_reg[1][13] ;
  output OR_out1__0;
  output [13:0]B;
  output HDL_Counter2_count_reg_11_sp_1;
  output \delayMatch1_reg_reg[1][11] ;
  output \delayMatch1_reg_reg[1][9] ;
  output \delayMatch1_reg_reg[1][7] ;
  output \delayMatch1_reg_reg[1][5] ;
  output \delayMatch1_reg_reg[1][3] ;
  output \delayMatch1_reg_reg[1][1] ;
  output \HDL_Counter2_count_reg[11]_0 ;
  output \min_pulse_width_AXI_1_reg[0] ;
  output \min_pulse_width_AXI_1_reg[5] ;
  output \min_pulse_width_AXI_1_reg[8] ;
  output \min_pulse_width_AXI_1_reg[9] ;
  output \min_pulse_width_AXI_1_reg[10] ;
  input RSTP;
  input CEP;
  input IPCORE_CLK;
  input [13:0]Q;
  input \minus_out1_1_reg[12]_0 ;
  input [13:0]\Delay_out1_reg[13] ;
  input [13:0]\Delay_out1_reg[13]_0 ;
  input [0:0]D;
  input [11:0]HDL_Counter2_count_reg;
  input [0:0]CO;
  input \Delay_out1_reg[0] ;
  input \Delay_out1_reg[0]_0 ;
  input \Delay_out1_reg[13]_1 ;
  input \Delay_out1_reg[13]_2 ;
  input \Delay_out1_reg[13]_3 ;

  wire [13:11]Add1_out1;
  wire [13:0]Add1_out1_1;
  wire \Add1_out1_1[13]_i_2_n_0 ;
  wire \Add1_out1_1[13]_i_3__1_n_0 ;
  wire \Add1_out1_1[13]_i_4_n_0 ;
  wire \Add1_out1_1_reg[13]_i_1_n_6 ;
  wire \Add1_out1_1_reg[13]_i_1_n_7 ;
  wire [13:1]Add2_out1;
  wire [13:1]Add2_out1_1;
  wire \Add2_out1_1[13]_i_2_n_0 ;
  wire \Add2_out1_1[13]_i_3_n_0 ;
  wire \Add2_out1_1[13]_i_4_n_0 ;
  wire \Add2_out1_1[13]_i_5_n_0 ;
  wire \Add2_out1_1[8]_i_10_n_0 ;
  wire \Add2_out1_1[8]_i_2_n_0 ;
  wire \Add2_out1_1[8]_i_3_n_0 ;
  wire \Add2_out1_1[8]_i_4_n_0 ;
  wire \Add2_out1_1[8]_i_5_n_0 ;
  wire \Add2_out1_1[8]_i_6_n_0 ;
  wire \Add2_out1_1[8]_i_7_n_0 ;
  wire \Add2_out1_1[8]_i_8_n_0 ;
  wire \Add2_out1_1[8]_i_9_n_0 ;
  wire \Add2_out1_1_reg[13]_i_1_n_4 ;
  wire \Add2_out1_1_reg[13]_i_1_n_5 ;
  wire \Add2_out1_1_reg[13]_i_1_n_6 ;
  wire \Add2_out1_1_reg[13]_i_1_n_7 ;
  wire \Add2_out1_1_reg[8]_i_1_n_0 ;
  wire \Add2_out1_1_reg[8]_i_1_n_1 ;
  wire \Add2_out1_1_reg[8]_i_1_n_2 ;
  wire \Add2_out1_1_reg[8]_i_1_n_3 ;
  wire \Add2_out1_1_reg[8]_i_1_n_4 ;
  wire \Add2_out1_1_reg[8]_i_1_n_5 ;
  wire \Add2_out1_1_reg[8]_i_1_n_6 ;
  wire \Add2_out1_1_reg[8]_i_1_n_7 ;
  wire [13:0]B;
  wire CEP;
  wire [0:0]CO;
  wire [0:0]D;
  wire \Delay_out1[13]_i_3_n_0 ;
  wire \Delay_out1[13]_i_4_n_0 ;
  wire \Delay_out1_reg[0] ;
  wire \Delay_out1_reg[0]_0 ;
  wire [13:0]\Delay_out1_reg[13] ;
  wire [13:0]\Delay_out1_reg[13]_0 ;
  wire \Delay_out1_reg[13]_1 ;
  wire \Delay_out1_reg[13]_2 ;
  wire \Delay_out1_reg[13]_3 ;
  wire [11:0]HDL_Counter2_count_reg;
  wire \HDL_Counter2_count_reg[11]_0 ;
  wire HDL_Counter2_count_reg_11_sn_1;
  wire IPCORE_CLK;
  wire Logical_Operator1_out10_carry_i_10__1_n_0;
  wire Logical_Operator1_out10_carry_i_11__1_n_0;
  wire Logical_Operator1_out10_carry_i_12__1_n_0;
  wire Logical_Operator1_out10_carry_i_13__1_n_0;
  wire Logical_Operator1_out10_carry_i_14__1_n_0;
  wire Logical_Operator1_out10_carry_i_1__1_n_0;
  wire Logical_Operator1_out10_carry_i_2__1_n_0;
  wire Logical_Operator1_out10_carry_i_3__1_n_0;
  wire Logical_Operator1_out10_carry_i_4__1_n_0;
  wire Logical_Operator1_out10_carry_i_5__1_n_0;
  wire Logical_Operator1_out10_carry_i_6__1_n_0;
  wire Logical_Operator1_out10_carry_i_7__1_n_0;
  wire Logical_Operator1_out10_carry_i_8__1_n_0;
  wire Logical_Operator1_out10_carry_i_9__1_n_0;
  wire Logical_Operator1_out10_carry_n_2;
  wire Logical_Operator1_out10_carry_n_3;
  wire Logical_Operator1_out10_carry_n_4;
  wire Logical_Operator1_out10_carry_n_5;
  wire Logical_Operator1_out10_carry_n_6;
  wire Logical_Operator1_out10_carry_n_7;
  wire \Logical_Operator1_out10_inferred__0/i__carry_n_2 ;
  wire \Logical_Operator1_out10_inferred__0/i__carry_n_3 ;
  wire \Logical_Operator1_out10_inferred__0/i__carry_n_4 ;
  wire \Logical_Operator1_out10_inferred__0/i__carry_n_5 ;
  wire \Logical_Operator1_out10_inferred__0/i__carry_n_6 ;
  wire \Logical_Operator1_out10_inferred__0/i__carry_n_7 ;
  wire Logical_Operator_out10_carry_i_10__1_n_0;
  wire Logical_Operator_out10_carry_i_11__1_n_0;
  wire Logical_Operator_out10_carry_i_12__1_n_0;
  wire Logical_Operator_out10_carry_i_13__1_n_0;
  wire Logical_Operator_out10_carry_i_14__1_n_0;
  wire Logical_Operator_out10_carry_i_1__1_n_0;
  wire Logical_Operator_out10_carry_i_2__1_n_0;
  wire Logical_Operator_out10_carry_i_3__1_n_0;
  wire Logical_Operator_out10_carry_i_4__1_n_0;
  wire Logical_Operator_out10_carry_i_5__1_n_0;
  wire Logical_Operator_out10_carry_i_6__1_n_0;
  wire Logical_Operator_out10_carry_i_7__1_n_0;
  wire Logical_Operator_out10_carry_i_8__1_n_0;
  wire Logical_Operator_out10_carry_i_9__1_n_0;
  wire Logical_Operator_out10_carry_n_2;
  wire Logical_Operator_out10_carry_n_3;
  wire Logical_Operator_out10_carry_n_4;
  wire Logical_Operator_out10_carry_n_5;
  wire Logical_Operator_out10_carry_n_6;
  wire Logical_Operator_out10_carry_n_7;
  wire Logical_Operator_out11_carry_i_1__1_n_0;
  wire Logical_Operator_out11_carry_i_2__1_n_0;
  wire Logical_Operator_out11_carry_i_3__1_n_0;
  wire Logical_Operator_out11_carry_i_4__1_n_0;
  wire Logical_Operator_out11_carry_i_5__1_n_0;
  wire Logical_Operator_out11_carry_i_6__1_n_0;
  wire Logical_Operator_out11_carry_i_7__1_n_0;
  wire Logical_Operator_out11_carry_i_8__1_n_0;
  wire Logical_Operator_out11_carry_i_9__1_n_0;
  wire Logical_Operator_out11_carry_n_2;
  wire Logical_Operator_out11_carry_n_3;
  wire Logical_Operator_out11_carry_n_4;
  wire Logical_Operator_out11_carry_n_5;
  wire Logical_Operator_out11_carry_n_6;
  wire Logical_Operator_out11_carry_n_7;
  wire Logical_Operator_out1__1;
  wire OR_out1__0;
  wire [13:0]Q;
  wire RSTP;
  wire Relational_Operator1_relop1;
  wire Relational_Operator2_relop1;
  wire Relational_Operator3_relop1;
  wire Relational_Operator_relop1;
  wire [12:0]Saturation1_out1;
  wire Saturation1_out110_in;
  wire [12:11]Saturation1_out1_1;
  wire \delayMatch1_reg_reg[1][11] ;
  wire \delayMatch1_reg_reg[1][13] ;
  wire \delayMatch1_reg_reg[1][1] ;
  wire \delayMatch1_reg_reg[1][3] ;
  wire \delayMatch1_reg_reg[1][5] ;
  wire \delayMatch1_reg_reg[1][7] ;
  wire \delayMatch1_reg_reg[1][9] ;
  wire i__carry_i_10_n_0;
  wire i__carry_i_11_n_0;
  wire i__carry_i_12_n_0;
  wire i__carry_i_13_n_0;
  wire i__carry_i_14_n_0;
  wire i__carry_i_1__1_n_0;
  wire i__carry_i_2__1_n_0;
  wire i__carry_i_3__1_n_0;
  wire i__carry_i_4__1_n_0;
  wire i__carry_i_5__1_n_0;
  wire i__carry_i_6__1_n_0;
  wire i__carry_i_7__1_n_0;
  wire i__carry_i_8__1_n_0;
  wire i__carry_i_9__1_n_0;
  wire \min_pulse_width_AXI_1_reg[0] ;
  wire \min_pulse_width_AXI_1_reg[10] ;
  wire \min_pulse_width_AXI_1_reg[4] ;
  wire \min_pulse_width_AXI_1_reg[5] ;
  wire \min_pulse_width_AXI_1_reg[8] ;
  wire \min_pulse_width_AXI_1_reg[9] ;
  wire [13:1]minus_out1;
  wire [13:1]minus_out1_1;
  wire \minus_out1_1[11]_i_3_n_0 ;
  wire \minus_out1_1[13]_i_10__0_n_0 ;
  wire \minus_out1_1[13]_i_11__0_n_0 ;
  wire \minus_out1_1[13]_i_12__0_n_0 ;
  wire \minus_out1_1[13]_i_13__0_n_0 ;
  wire \minus_out1_1[13]_i_14__0_n_0 ;
  wire \minus_out1_1[13]_i_15__1_n_0 ;
  wire \minus_out1_1[13]_i_16_n_0 ;
  wire \minus_out1_1[13]_i_4__0_n_0 ;
  wire \minus_out1_1[13]_i_5__0_n_0 ;
  wire \minus_out1_1[13]_i_6__0_n_0 ;
  wire \minus_out1_1[13]_i_7__0_n_0 ;
  wire \minus_out1_1[13]_i_8_n_0 ;
  wire \minus_out1_1[13]_i_9_n_0 ;
  wire \minus_out1_1[5]_i_3_n_0 ;
  wire \minus_out1_1_reg[12]_0 ;
  wire \minus_out1_1_reg[13]_i_3_n_2 ;
  wire \minus_out1_1_reg[13]_i_3_n_3 ;
  wire \minus_out1_1_reg[13]_i_3_n_4 ;
  wire \minus_out1_1_reg[13]_i_3_n_5 ;
  wire \minus_out1_1_reg[13]_i_3_n_6 ;
  wire \minus_out1_1_reg[13]_i_3_n_7 ;
  wire modulating_signal_in_clock_cycles_1_reg_i_17_n_0;
  wire modulating_signal_in_clock_cycles_1_reg_i_18_n_0;
  wire [7:2]\NLW_Add1_out1_1_reg[13]_i_1_CO_UNCONNECTED ;
  wire [7:3]\NLW_Add1_out1_1_reg[13]_i_1_O_UNCONNECTED ;
  wire [7:4]\NLW_Add2_out1_1_reg[13]_i_1_CO_UNCONNECTED ;
  wire [7:5]\NLW_Add2_out1_1_reg[13]_i_1_O_UNCONNECTED ;
  wire [7:7]NLW_Logical_Operator1_out10_carry_CO_UNCONNECTED;
  wire [7:0]NLW_Logical_Operator1_out10_carry_O_UNCONNECTED;
  wire [7:7]\NLW_Logical_Operator1_out10_inferred__0/i__carry_CO_UNCONNECTED ;
  wire [7:0]\NLW_Logical_Operator1_out10_inferred__0/i__carry_O_UNCONNECTED ;
  wire [7:7]NLW_Logical_Operator_out10_carry_CO_UNCONNECTED;
  wire [7:0]NLW_Logical_Operator_out10_carry_O_UNCONNECTED;
  wire [7:7]NLW_Logical_Operator_out11_carry_CO_UNCONNECTED;
  wire [7:0]NLW_Logical_Operator_out11_carry_O_UNCONNECTED;
  wire [7:7]\NLW_minus_out1_1_reg[13]_i_3_CO_UNCONNECTED ;
  wire [7:0]\NLW_minus_out1_1_reg[13]_i_3_O_UNCONNECTED ;

  assign HDL_Counter2_count_reg_11_sp_1 = HDL_Counter2_count_reg_11_sn_1;
  (* SOFT_HLUTNM = "soft_lutpair20" *) 
  LUT3 #(
    .INIT(8'h02)) 
    \Add1_out1_1[0]_i_1 
       (.I0(Q[0]),
        .I1(Saturation1_out110_in),
        .I2(Q[13]),
        .O(Saturation1_out1[0]));
  (* SOFT_HLUTNM = "soft_lutpair25" *) 
  LUT3 #(
    .INIT(8'h02)) 
    \Add1_out1_1[10]_i_1 
       (.I0(Q[10]),
        .I1(Saturation1_out110_in),
        .I2(Q[13]),
        .O(Saturation1_out1[10]));
  LUT3 #(
    .INIT(8'hBA)) 
    \Add1_out1_1[13]_i_2 
       (.I0(Saturation1_out110_in),
        .I1(Q[13]),
        .I2(Q[12]),
        .O(\Add1_out1_1[13]_i_2_n_0 ));
  LUT3 #(
    .INIT(8'h0D)) 
    \Add1_out1_1[13]_i_3__1 
       (.I0(Q[12]),
        .I1(Q[13]),
        .I2(Saturation1_out110_in),
        .O(\Add1_out1_1[13]_i_3__1_n_0 ));
  LUT3 #(
    .INIT(8'h02)) 
    \Add1_out1_1[13]_i_4 
       (.I0(Q[11]),
        .I1(Saturation1_out110_in),
        .I2(Q[13]),
        .O(\Add1_out1_1[13]_i_4_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair21" *) 
  LUT3 #(
    .INIT(8'h02)) 
    \Add1_out1_1[1]_i_1 
       (.I0(Q[1]),
        .I1(Saturation1_out110_in),
        .I2(Q[13]),
        .O(Saturation1_out1[1]));
  (* SOFT_HLUTNM = "soft_lutpair21" *) 
  LUT3 #(
    .INIT(8'h02)) 
    \Add1_out1_1[2]_i_1 
       (.I0(Q[2]),
        .I1(Saturation1_out110_in),
        .I2(Q[13]),
        .O(Saturation1_out1[2]));
  (* SOFT_HLUTNM = "soft_lutpair22" *) 
  LUT3 #(
    .INIT(8'h02)) 
    \Add1_out1_1[3]_i_1 
       (.I0(Q[3]),
        .I1(Saturation1_out110_in),
        .I2(Q[13]),
        .O(Saturation1_out1[3]));
  (* SOFT_HLUTNM = "soft_lutpair22" *) 
  LUT3 #(
    .INIT(8'h02)) 
    \Add1_out1_1[4]_i_1 
       (.I0(Q[4]),
        .I1(Saturation1_out110_in),
        .I2(Q[13]),
        .O(Saturation1_out1[4]));
  (* SOFT_HLUTNM = "soft_lutpair23" *) 
  LUT3 #(
    .INIT(8'h02)) 
    \Add1_out1_1[5]_i_1 
       (.I0(Q[5]),
        .I1(Saturation1_out110_in),
        .I2(Q[13]),
        .O(Saturation1_out1[5]));
  (* SOFT_HLUTNM = "soft_lutpair13" *) 
  LUT3 #(
    .INIT(8'h02)) 
    \Add1_out1_1[6]_i_1 
       (.I0(Q[6]),
        .I1(Saturation1_out110_in),
        .I2(Q[13]),
        .O(Saturation1_out1[6]));
  (* SOFT_HLUTNM = "soft_lutpair23" *) 
  LUT3 #(
    .INIT(8'h02)) 
    \Add1_out1_1[7]_i_1 
       (.I0(Q[7]),
        .I1(Saturation1_out110_in),
        .I2(Q[13]),
        .O(Saturation1_out1[7]));
  (* SOFT_HLUTNM = "soft_lutpair24" *) 
  LUT3 #(
    .INIT(8'h02)) 
    \Add1_out1_1[8]_i_1 
       (.I0(Q[8]),
        .I1(Saturation1_out110_in),
        .I2(Q[13]),
        .O(Saturation1_out1[8]));
  (* SOFT_HLUTNM = "soft_lutpair24" *) 
  LUT3 #(
    .INIT(8'h02)) 
    \Add1_out1_1[9]_i_1 
       (.I0(Q[9]),
        .I1(Saturation1_out110_in),
        .I2(Q[13]),
        .O(Saturation1_out1[9]));
  FDRE \Add1_out1_1_reg[0] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Saturation1_out1[0]),
        .Q(Add1_out1_1[0]),
        .R(RSTP));
  FDRE \Add1_out1_1_reg[10] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Saturation1_out1[10]),
        .Q(Add1_out1_1[10]),
        .R(RSTP));
  FDRE \Add1_out1_1_reg[11] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Add1_out1[11]),
        .Q(Add1_out1_1[11]),
        .R(RSTP));
  FDRE \Add1_out1_1_reg[12] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Add1_out1[12]),
        .Q(Add1_out1_1[12]),
        .R(RSTP));
  FDRE \Add1_out1_1_reg[13] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Add1_out1[13]),
        .Q(Add1_out1_1[13]),
        .R(RSTP));
  (* ADDER_THRESHOLD = "35" *) 
  CARRY8 \Add1_out1_1_reg[13]_i_1 
       (.CI(1'b0),
        .CI_TOP(1'b0),
        .CO({\NLW_Add1_out1_1_reg[13]_i_1_CO_UNCONNECTED [7:2],\Add1_out1_1_reg[13]_i_1_n_6 ,\Add1_out1_1_reg[13]_i_1_n_7 }),
        .DI({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,\Add1_out1_1[13]_i_2_n_0 ,1'b0}),
        .O({\NLW_Add1_out1_1_reg[13]_i_1_O_UNCONNECTED [7:3],Add1_out1}),
        .S({1'b0,1'b0,1'b0,1'b0,1'b0,1'b1,\Add1_out1_1[13]_i_3__1_n_0 ,\Add1_out1_1[13]_i_4_n_0 }));
  FDRE \Add1_out1_1_reg[1] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Saturation1_out1[1]),
        .Q(Add1_out1_1[1]),
        .R(RSTP));
  FDRE \Add1_out1_1_reg[2] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Saturation1_out1[2]),
        .Q(Add1_out1_1[2]),
        .R(RSTP));
  FDRE \Add1_out1_1_reg[3] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Saturation1_out1[3]),
        .Q(Add1_out1_1[3]),
        .R(RSTP));
  FDRE \Add1_out1_1_reg[4] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Saturation1_out1[4]),
        .Q(Add1_out1_1[4]),
        .R(RSTP));
  FDRE \Add1_out1_1_reg[5] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Saturation1_out1[5]),
        .Q(Add1_out1_1[5]),
        .R(RSTP));
  FDRE \Add1_out1_1_reg[6] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Saturation1_out1[6]),
        .Q(Add1_out1_1[6]),
        .R(RSTP));
  FDRE \Add1_out1_1_reg[7] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Saturation1_out1[7]),
        .Q(Add1_out1_1[7]),
        .R(RSTP));
  FDRE \Add1_out1_1_reg[8] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Saturation1_out1[8]),
        .Q(Add1_out1_1[8]),
        .R(RSTP));
  FDRE \Add1_out1_1_reg[9] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Saturation1_out1[9]),
        .Q(Add1_out1_1[9]),
        .R(RSTP));
  LUT3 #(
    .INIT(8'hBA)) 
    \Add2_out1_1[13]_i_2 
       (.I0(Saturation1_out110_in),
        .I1(Q[13]),
        .I2(Q[12]),
        .O(\Add2_out1_1[13]_i_2_n_0 ));
  LUT3 #(
    .INIT(8'hEF)) 
    \Add2_out1_1[13]_i_3 
       (.I0(Q[13]),
        .I1(Saturation1_out110_in),
        .I2(Q[11]),
        .O(\Add2_out1_1[13]_i_3_n_0 ));
  LUT3 #(
    .INIT(8'hEF)) 
    \Add2_out1_1[13]_i_4 
       (.I0(Q[13]),
        .I1(Saturation1_out110_in),
        .I2(Q[10]),
        .O(\Add2_out1_1[13]_i_4_n_0 ));
  LUT3 #(
    .INIT(8'hEF)) 
    \Add2_out1_1[13]_i_5 
       (.I0(Q[13]),
        .I1(Saturation1_out110_in),
        .I2(Q[9]),
        .O(\Add2_out1_1[13]_i_5_n_0 ));
  LUT3 #(
    .INIT(8'hEF)) 
    \Add2_out1_1[8]_i_10 
       (.I0(Q[13]),
        .I1(Saturation1_out110_in),
        .I2(Q[1]),
        .O(\Add2_out1_1[8]_i_10_n_0 ));
  LUT3 #(
    .INIT(8'hEF)) 
    \Add2_out1_1[8]_i_2 
       (.I0(Q[13]),
        .I1(Saturation1_out110_in),
        .I2(Q[0]),
        .O(\Add2_out1_1[8]_i_2_n_0 ));
  LUT3 #(
    .INIT(8'hEF)) 
    \Add2_out1_1[8]_i_3 
       (.I0(Q[13]),
        .I1(Saturation1_out110_in),
        .I2(Q[8]),
        .O(\Add2_out1_1[8]_i_3_n_0 ));
  LUT3 #(
    .INIT(8'hEF)) 
    \Add2_out1_1[8]_i_4 
       (.I0(Q[13]),
        .I1(Saturation1_out110_in),
        .I2(Q[7]),
        .O(\Add2_out1_1[8]_i_4_n_0 ));
  LUT3 #(
    .INIT(8'hEF)) 
    \Add2_out1_1[8]_i_5 
       (.I0(Q[13]),
        .I1(Saturation1_out110_in),
        .I2(Q[6]),
        .O(\Add2_out1_1[8]_i_5_n_0 ));
  LUT3 #(
    .INIT(8'hEF)) 
    \Add2_out1_1[8]_i_6 
       (.I0(Q[13]),
        .I1(Saturation1_out110_in),
        .I2(Q[5]),
        .O(\Add2_out1_1[8]_i_6_n_0 ));
  LUT3 #(
    .INIT(8'hEF)) 
    \Add2_out1_1[8]_i_7 
       (.I0(Q[13]),
        .I1(Saturation1_out110_in),
        .I2(Q[4]),
        .O(\Add2_out1_1[8]_i_7_n_0 ));
  LUT3 #(
    .INIT(8'hEF)) 
    \Add2_out1_1[8]_i_8 
       (.I0(Q[13]),
        .I1(Saturation1_out110_in),
        .I2(Q[3]),
        .O(\Add2_out1_1[8]_i_8_n_0 ));
  LUT3 #(
    .INIT(8'hEF)) 
    \Add2_out1_1[8]_i_9 
       (.I0(Q[13]),
        .I1(Saturation1_out110_in),
        .I2(Q[2]),
        .O(\Add2_out1_1[8]_i_9_n_0 ));
  FDRE \Add2_out1_1_reg[10] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Add2_out1[10]),
        .Q(Add2_out1_1[10]),
        .R(RSTP));
  FDRE \Add2_out1_1_reg[11] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Add2_out1[11]),
        .Q(Add2_out1_1[11]),
        .R(RSTP));
  FDRE \Add2_out1_1_reg[12] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Add2_out1[12]),
        .Q(Add2_out1_1[12]),
        .R(RSTP));
  FDRE \Add2_out1_1_reg[13] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Add2_out1[13]),
        .Q(Add2_out1_1[13]),
        .R(RSTP));
  (* ADDER_THRESHOLD = "35" *) 
  CARRY8 \Add2_out1_1_reg[13]_i_1 
       (.CI(\Add2_out1_1_reg[8]_i_1_n_0 ),
        .CI_TOP(1'b0),
        .CO({\NLW_Add2_out1_1_reg[13]_i_1_CO_UNCONNECTED [7:4],\Add2_out1_1_reg[13]_i_1_n_4 ,\Add2_out1_1_reg[13]_i_1_n_5 ,\Add2_out1_1_reg[13]_i_1_n_6 ,\Add2_out1_1_reg[13]_i_1_n_7 }),
        .DI({1'b0,1'b0,1'b0,1'b0,1'b1,1'b0,1'b0,1'b0}),
        .O({\NLW_Add2_out1_1_reg[13]_i_1_O_UNCONNECTED [7:5],Add2_out1[13:9]}),
        .S({1'b0,1'b0,1'b0,1'b1,\Add2_out1_1[13]_i_2_n_0 ,\Add2_out1_1[13]_i_3_n_0 ,\Add2_out1_1[13]_i_4_n_0 ,\Add2_out1_1[13]_i_5_n_0 }));
  FDRE \Add2_out1_1_reg[1] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Add2_out1[1]),
        .Q(Add2_out1_1[1]),
        .R(RSTP));
  FDRE \Add2_out1_1_reg[2] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Add2_out1[2]),
        .Q(Add2_out1_1[2]),
        .R(RSTP));
  FDRE \Add2_out1_1_reg[3] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Add2_out1[3]),
        .Q(Add2_out1_1[3]),
        .R(RSTP));
  FDRE \Add2_out1_1_reg[4] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Add2_out1[4]),
        .Q(Add2_out1_1[4]),
        .R(RSTP));
  FDRE \Add2_out1_1_reg[5] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Add2_out1[5]),
        .Q(Add2_out1_1[5]),
        .R(RSTP));
  FDRE \Add2_out1_1_reg[6] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Add2_out1[6]),
        .Q(Add2_out1_1[6]),
        .R(RSTP));
  FDRE \Add2_out1_1_reg[7] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Add2_out1[7]),
        .Q(Add2_out1_1[7]),
        .R(RSTP));
  FDRE \Add2_out1_1_reg[8] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Add2_out1[8]),
        .Q(Add2_out1_1[8]),
        .R(RSTP));
  (* ADDER_THRESHOLD = "35" *) 
  CARRY8 \Add2_out1_1_reg[8]_i_1 
       (.CI(\Add2_out1_1[8]_i_2_n_0 ),
        .CI_TOP(1'b0),
        .CO({\Add2_out1_1_reg[8]_i_1_n_0 ,\Add2_out1_1_reg[8]_i_1_n_1 ,\Add2_out1_1_reg[8]_i_1_n_2 ,\Add2_out1_1_reg[8]_i_1_n_3 ,\Add2_out1_1_reg[8]_i_1_n_4 ,\Add2_out1_1_reg[8]_i_1_n_5 ,\Add2_out1_1_reg[8]_i_1_n_6 ,\Add2_out1_1_reg[8]_i_1_n_7 }),
        .DI({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .O(Add2_out1[8:1]),
        .S({\Add2_out1_1[8]_i_3_n_0 ,\Add2_out1_1[8]_i_4_n_0 ,\Add2_out1_1[8]_i_5_n_0 ,\Add2_out1_1[8]_i_6_n_0 ,\Add2_out1_1[8]_i_7_n_0 ,\Add2_out1_1[8]_i_8_n_0 ,\Add2_out1_1[8]_i_9_n_0 ,\Add2_out1_1[8]_i_10_n_0 }));
  FDRE \Add2_out1_1_reg[9] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Add2_out1[9]),
        .Q(Add2_out1_1[9]),
        .R(RSTP));
  LUT6 #(
    .INIT(64'h0000000000000001)) 
    Counter_Ctrl_out5_1_i_4
       (.I0(HDL_Counter2_count_reg[4]),
        .I1(HDL_Counter2_count_reg[5]),
        .I2(HDL_Counter2_count_reg[6]),
        .I3(HDL_Counter2_count_reg[8]),
        .I4(HDL_Counter2_count_reg[10]),
        .I5(HDL_Counter2_count_reg[9]),
        .O(\HDL_Counter2_count_reg[11]_0 ));
  LUT6 #(
    .INIT(64'hAAAAFFBFAAAA0080)) 
    \Delay_out1[11]_i_1 
       (.I0(\Delay_out1_reg[13]_0 [11]),
        .I1(HDL_Counter2_count_reg_11_sn_1),
        .I2(D),
        .I3(HDL_Counter2_count_reg[11]),
        .I4(CO),
        .I5(\Delay_out1_reg[13] [11]),
        .O(\delayMatch1_reg_reg[1][11] ));
  LUT6 #(
    .INIT(64'hAAAAFFBFAAAA0080)) 
    \Delay_out1[13]_i_1 
       (.I0(\Delay_out1_reg[13]_0 [13]),
        .I1(HDL_Counter2_count_reg_11_sn_1),
        .I2(D),
        .I3(HDL_Counter2_count_reg[11]),
        .I4(CO),
        .I5(\Delay_out1_reg[13] [13]),
        .O(\delayMatch1_reg_reg[1][13] ));
  LUT6 #(
    .INIT(64'h8000000000000000)) 
    \Delay_out1[13]_i_2 
       (.I0(\HDL_Counter2_count_reg[11]_0 ),
        .I1(\Delay_out1_reg[13]_1 ),
        .I2(\Delay_out1[13]_i_3_n_0 ),
        .I3(\Delay_out1_reg[13]_2 ),
        .I4(\Delay_out1[13]_i_4_n_0 ),
        .I5(\Delay_out1_reg[13]_3 ),
        .O(HDL_Counter2_count_reg_11_sn_1));
  LUT4 #(
    .INIT(16'h0001)) 
    \Delay_out1[13]_i_3 
       (.I0(HDL_Counter2_count_reg[1]),
        .I1(HDL_Counter2_count_reg[0]),
        .I2(HDL_Counter2_count_reg[3]),
        .I3(HDL_Counter2_count_reg[2]),
        .O(\Delay_out1[13]_i_3_n_0 ));
  LUT3 #(
    .INIT(8'h31)) 
    \Delay_out1[13]_i_4 
       (.I0(HDL_Counter2_count_reg[7]),
        .I1(HDL_Counter2_count_reg[9]),
        .I2(HDL_Counter2_count_reg[8]),
        .O(\Delay_out1[13]_i_4_n_0 ));
  LUT6 #(
    .INIT(64'hAAAAFFBFAAAA0080)) 
    \Delay_out1[1]_i_1 
       (.I0(\Delay_out1_reg[13]_0 [1]),
        .I1(HDL_Counter2_count_reg_11_sn_1),
        .I2(D),
        .I3(HDL_Counter2_count_reg[11]),
        .I4(CO),
        .I5(\Delay_out1_reg[13] [1]),
        .O(\delayMatch1_reg_reg[1][1] ));
  LUT6 #(
    .INIT(64'hAAAAFFBFAAAA0080)) 
    \Delay_out1[3]_i_1 
       (.I0(\Delay_out1_reg[13]_0 [3]),
        .I1(HDL_Counter2_count_reg_11_sn_1),
        .I2(D),
        .I3(HDL_Counter2_count_reg[11]),
        .I4(CO),
        .I5(\Delay_out1_reg[13] [3]),
        .O(\delayMatch1_reg_reg[1][3] ));
  LUT6 #(
    .INIT(64'hAAAAFFBFAAAA0080)) 
    \Delay_out1[5]_i_1 
       (.I0(\Delay_out1_reg[13]_0 [5]),
        .I1(HDL_Counter2_count_reg_11_sn_1),
        .I2(D),
        .I3(HDL_Counter2_count_reg[11]),
        .I4(CO),
        .I5(\Delay_out1_reg[13] [5]),
        .O(\delayMatch1_reg_reg[1][5] ));
  LUT6 #(
    .INIT(64'hAAAAFFBFAAAA0080)) 
    \Delay_out1[7]_i_1 
       (.I0(\Delay_out1_reg[13]_0 [7]),
        .I1(HDL_Counter2_count_reg_11_sn_1),
        .I2(D),
        .I3(HDL_Counter2_count_reg[11]),
        .I4(CO),
        .I5(\Delay_out1_reg[13] [7]),
        .O(\delayMatch1_reg_reg[1][7] ));
  LUT6 #(
    .INIT(64'hAAAAFFBFAAAA0080)) 
    \Delay_out1[9]_i_1 
       (.I0(\Delay_out1_reg[13]_0 [9]),
        .I1(HDL_Counter2_count_reg_11_sn_1),
        .I2(D),
        .I3(HDL_Counter2_count_reg[11]),
        .I4(CO),
        .I5(\Delay_out1_reg[13] [9]),
        .O(\delayMatch1_reg_reg[1][9] ));
  (* COMPARATOR_THRESHOLD = "11" *) 
  CARRY8 Logical_Operator1_out10_carry
       (.CI(1'b0),
        .CI_TOP(1'b0),
        .CO({NLW_Logical_Operator1_out10_carry_CO_UNCONNECTED[7],Relational_Operator_relop1,Logical_Operator1_out10_carry_n_2,Logical_Operator1_out10_carry_n_3,Logical_Operator1_out10_carry_n_4,Logical_Operator1_out10_carry_n_5,Logical_Operator1_out10_carry_n_6,Logical_Operator1_out10_carry_n_7}),
        .DI({1'b0,Logical_Operator1_out10_carry_i_1__1_n_0,Logical_Operator1_out10_carry_i_2__1_n_0,Logical_Operator1_out10_carry_i_3__1_n_0,Logical_Operator1_out10_carry_i_4__1_n_0,Logical_Operator1_out10_carry_i_5__1_n_0,Logical_Operator1_out10_carry_i_6__1_n_0,Logical_Operator1_out10_carry_i_7__1_n_0}),
        .O(NLW_Logical_Operator1_out10_carry_O_UNCONNECTED[7:0]),
        .S({1'b0,Logical_Operator1_out10_carry_i_8__1_n_0,Logical_Operator1_out10_carry_i_9__1_n_0,Logical_Operator1_out10_carry_i_10__1_n_0,Logical_Operator1_out10_carry_i_11__1_n_0,Logical_Operator1_out10_carry_i_12__1_n_0,Logical_Operator1_out10_carry_i_13__1_n_0,Logical_Operator1_out10_carry_i_14__1_n_0}));
  LUT6 #(
    .INIT(64'hA95900000000A959)) 
    Logical_Operator1_out10_carry_i_10__1
       (.I0(minus_out1_1[8]),
        .I1(\Delay_out1_reg[13] [8]),
        .I2(OR_out1__0),
        .I3(\Delay_out1_reg[13]_0 [8]),
        .I4(\delayMatch1_reg_reg[1][9] ),
        .I5(minus_out1_1[9]),
        .O(Logical_Operator1_out10_carry_i_10__1_n_0));
  LUT6 #(
    .INIT(64'hA95900000000A959)) 
    Logical_Operator1_out10_carry_i_11__1
       (.I0(minus_out1_1[6]),
        .I1(\Delay_out1_reg[13] [6]),
        .I2(OR_out1__0),
        .I3(\Delay_out1_reg[13]_0 [6]),
        .I4(\delayMatch1_reg_reg[1][7] ),
        .I5(minus_out1_1[7]),
        .O(Logical_Operator1_out10_carry_i_11__1_n_0));
  LUT6 #(
    .INIT(64'hA95900000000A959)) 
    Logical_Operator1_out10_carry_i_12__1
       (.I0(minus_out1_1[4]),
        .I1(\Delay_out1_reg[13] [4]),
        .I2(OR_out1__0),
        .I3(\Delay_out1_reg[13]_0 [4]),
        .I4(\delayMatch1_reg_reg[1][5] ),
        .I5(minus_out1_1[5]),
        .O(Logical_Operator1_out10_carry_i_12__1_n_0));
  LUT6 #(
    .INIT(64'hA95900000000A959)) 
    Logical_Operator1_out10_carry_i_13__1
       (.I0(minus_out1_1[2]),
        .I1(\Delay_out1_reg[13] [2]),
        .I2(OR_out1__0),
        .I3(\Delay_out1_reg[13]_0 [2]),
        .I4(\delayMatch1_reg_reg[1][3] ),
        .I5(minus_out1_1[3]),
        .O(Logical_Operator1_out10_carry_i_13__1_n_0));
  LUT6 #(
    .INIT(64'hE21D00000000E21D)) 
    Logical_Operator1_out10_carry_i_14__1
       (.I0(\Delay_out1_reg[13] [0]),
        .I1(OR_out1__0),
        .I2(\Delay_out1_reg[13]_0 [0]),
        .I3(Add1_out1_1[0]),
        .I4(\delayMatch1_reg_reg[1][1] ),
        .I5(minus_out1_1[1]),
        .O(Logical_Operator1_out10_carry_i_14__1_n_0));
  LUT6 #(
    .INIT(64'h22222222BBB222B2)) 
    Logical_Operator1_out10_carry_i_1__1
       (.I0(minus_out1_1[13]),
        .I1(\delayMatch1_reg_reg[1][13] ),
        .I2(\Delay_out1_reg[13] [12]),
        .I3(OR_out1__0),
        .I4(\Delay_out1_reg[13]_0 [12]),
        .I5(minus_out1_1[12]),
        .O(Logical_Operator1_out10_carry_i_1__1_n_0));
  LUT6 #(
    .INIT(64'h22222222BBB222B2)) 
    Logical_Operator1_out10_carry_i_2__1
       (.I0(\delayMatch1_reg_reg[1][11] ),
        .I1(minus_out1_1[11]),
        .I2(\Delay_out1_reg[13] [10]),
        .I3(OR_out1__0),
        .I4(\Delay_out1_reg[13]_0 [10]),
        .I5(minus_out1_1[10]),
        .O(Logical_Operator1_out10_carry_i_2__1_n_0));
  LUT6 #(
    .INIT(64'h22222222BBB222B2)) 
    Logical_Operator1_out10_carry_i_3__1
       (.I0(\delayMatch1_reg_reg[1][9] ),
        .I1(minus_out1_1[9]),
        .I2(\Delay_out1_reg[13] [8]),
        .I3(OR_out1__0),
        .I4(\Delay_out1_reg[13]_0 [8]),
        .I5(minus_out1_1[8]),
        .O(Logical_Operator1_out10_carry_i_3__1_n_0));
  LUT6 #(
    .INIT(64'h22222222BBB222B2)) 
    Logical_Operator1_out10_carry_i_4__1
       (.I0(\delayMatch1_reg_reg[1][7] ),
        .I1(minus_out1_1[7]),
        .I2(\Delay_out1_reg[13] [6]),
        .I3(OR_out1__0),
        .I4(\Delay_out1_reg[13]_0 [6]),
        .I5(minus_out1_1[6]),
        .O(Logical_Operator1_out10_carry_i_4__1_n_0));
  LUT6 #(
    .INIT(64'h22222222BBB222B2)) 
    Logical_Operator1_out10_carry_i_5__1
       (.I0(\delayMatch1_reg_reg[1][5] ),
        .I1(minus_out1_1[5]),
        .I2(\Delay_out1_reg[13] [4]),
        .I3(OR_out1__0),
        .I4(\Delay_out1_reg[13]_0 [4]),
        .I5(minus_out1_1[4]),
        .O(Logical_Operator1_out10_carry_i_5__1_n_0));
  LUT6 #(
    .INIT(64'h22222222BBB222B2)) 
    Logical_Operator1_out10_carry_i_6__1
       (.I0(\delayMatch1_reg_reg[1][3] ),
        .I1(minus_out1_1[3]),
        .I2(\Delay_out1_reg[13] [2]),
        .I3(OR_out1__0),
        .I4(\Delay_out1_reg[13]_0 [2]),
        .I5(minus_out1_1[2]),
        .O(Logical_Operator1_out10_carry_i_6__1_n_0));
  LUT6 #(
    .INIT(64'h7577755510111000)) 
    Logical_Operator1_out10_carry_i_7__1
       (.I0(minus_out1_1[1]),
        .I1(Add1_out1_1[0]),
        .I2(\Delay_out1_reg[13]_0 [0]),
        .I3(OR_out1__0),
        .I4(\Delay_out1_reg[13] [0]),
        .I5(\delayMatch1_reg_reg[1][1] ),
        .O(Logical_Operator1_out10_carry_i_7__1_n_0));
  LUT6 #(
    .INIT(64'hA95900000000A959)) 
    Logical_Operator1_out10_carry_i_8__1
       (.I0(minus_out1_1[12]),
        .I1(\Delay_out1_reg[13] [12]),
        .I2(OR_out1__0),
        .I3(\Delay_out1_reg[13]_0 [12]),
        .I4(\delayMatch1_reg_reg[1][13] ),
        .I5(minus_out1_1[13]),
        .O(Logical_Operator1_out10_carry_i_8__1_n_0));
  LUT6 #(
    .INIT(64'hA95900000000A959)) 
    Logical_Operator1_out10_carry_i_9__1
       (.I0(minus_out1_1[10]),
        .I1(\Delay_out1_reg[13] [10]),
        .I2(OR_out1__0),
        .I3(\Delay_out1_reg[13]_0 [10]),
        .I4(\delayMatch1_reg_reg[1][11] ),
        .I5(minus_out1_1[11]),
        .O(Logical_Operator1_out10_carry_i_9__1_n_0));
  (* COMPARATOR_THRESHOLD = "11" *) 
  CARRY8 \Logical_Operator1_out10_inferred__0/i__carry 
       (.CI(1'b0),
        .CI_TOP(1'b0),
        .CO({\NLW_Logical_Operator1_out10_inferred__0/i__carry_CO_UNCONNECTED [7],Relational_Operator1_relop1,\Logical_Operator1_out10_inferred__0/i__carry_n_2 ,\Logical_Operator1_out10_inferred__0/i__carry_n_3 ,\Logical_Operator1_out10_inferred__0/i__carry_n_4 ,\Logical_Operator1_out10_inferred__0/i__carry_n_5 ,\Logical_Operator1_out10_inferred__0/i__carry_n_6 ,\Logical_Operator1_out10_inferred__0/i__carry_n_7 }),
        .DI({1'b0,i__carry_i_1__1_n_0,i__carry_i_2__1_n_0,i__carry_i_3__1_n_0,i__carry_i_4__1_n_0,i__carry_i_5__1_n_0,i__carry_i_6__1_n_0,i__carry_i_7__1_n_0}),
        .O(\NLW_Logical_Operator1_out10_inferred__0/i__carry_O_UNCONNECTED [7:0]),
        .S({1'b0,i__carry_i_8__1_n_0,i__carry_i_9__1_n_0,i__carry_i_10_n_0,i__carry_i_11_n_0,i__carry_i_12_n_0,i__carry_i_13_n_0,i__carry_i_14_n_0}));
  (* COMPARATOR_THRESHOLD = "11" *) 
  CARRY8 Logical_Operator_out10_carry
       (.CI(1'b0),
        .CI_TOP(1'b0),
        .CO({NLW_Logical_Operator_out10_carry_CO_UNCONNECTED[7],Relational_Operator3_relop1,Logical_Operator_out10_carry_n_2,Logical_Operator_out10_carry_n_3,Logical_Operator_out10_carry_n_4,Logical_Operator_out10_carry_n_5,Logical_Operator_out10_carry_n_6,Logical_Operator_out10_carry_n_7}),
        .DI({1'b0,Logical_Operator_out10_carry_i_1__1_n_0,Logical_Operator_out10_carry_i_2__1_n_0,Logical_Operator_out10_carry_i_3__1_n_0,Logical_Operator_out10_carry_i_4__1_n_0,Logical_Operator_out10_carry_i_5__1_n_0,Logical_Operator_out10_carry_i_6__1_n_0,Logical_Operator_out10_carry_i_7__1_n_0}),
        .O(NLW_Logical_Operator_out10_carry_O_UNCONNECTED[7:0]),
        .S({1'b0,Logical_Operator_out10_carry_i_8__1_n_0,Logical_Operator_out10_carry_i_9__1_n_0,Logical_Operator_out10_carry_i_10__1_n_0,Logical_Operator_out10_carry_i_11__1_n_0,Logical_Operator_out10_carry_i_12__1_n_0,Logical_Operator_out10_carry_i_13__1_n_0,Logical_Operator_out10_carry_i_14__1_n_0}));
  LUT6 #(
    .INIT(64'hA95900000000A959)) 
    Logical_Operator_out10_carry_i_10__1
       (.I0(Add2_out1_1[8]),
        .I1(\Delay_out1_reg[13] [8]),
        .I2(OR_out1__0),
        .I3(\Delay_out1_reg[13]_0 [8]),
        .I4(\delayMatch1_reg_reg[1][9] ),
        .I5(Add2_out1_1[9]),
        .O(Logical_Operator_out10_carry_i_10__1_n_0));
  LUT6 #(
    .INIT(64'hA95900000000A959)) 
    Logical_Operator_out10_carry_i_11__1
       (.I0(Add2_out1_1[6]),
        .I1(\Delay_out1_reg[13] [6]),
        .I2(OR_out1__0),
        .I3(\Delay_out1_reg[13]_0 [6]),
        .I4(\delayMatch1_reg_reg[1][7] ),
        .I5(Add2_out1_1[7]),
        .O(Logical_Operator_out10_carry_i_11__1_n_0));
  LUT6 #(
    .INIT(64'hA95900000000A959)) 
    Logical_Operator_out10_carry_i_12__1
       (.I0(Add2_out1_1[4]),
        .I1(\Delay_out1_reg[13] [4]),
        .I2(OR_out1__0),
        .I3(\Delay_out1_reg[13]_0 [4]),
        .I4(\delayMatch1_reg_reg[1][5] ),
        .I5(Add2_out1_1[5]),
        .O(Logical_Operator_out10_carry_i_12__1_n_0));
  LUT6 #(
    .INIT(64'hA95900000000A959)) 
    Logical_Operator_out10_carry_i_13__1
       (.I0(Add2_out1_1[2]),
        .I1(\Delay_out1_reg[13] [2]),
        .I2(OR_out1__0),
        .I3(\Delay_out1_reg[13]_0 [2]),
        .I4(\delayMatch1_reg_reg[1][3] ),
        .I5(Add2_out1_1[3]),
        .O(Logical_Operator_out10_carry_i_13__1_n_0));
  LUT6 #(
    .INIT(64'hE21D00000000E21D)) 
    Logical_Operator_out10_carry_i_14__1
       (.I0(\Delay_out1_reg[13] [0]),
        .I1(OR_out1__0),
        .I2(\Delay_out1_reg[13]_0 [0]),
        .I3(Add1_out1_1[0]),
        .I4(\delayMatch1_reg_reg[1][1] ),
        .I5(Add2_out1_1[1]),
        .O(Logical_Operator_out10_carry_i_14__1_n_0));
  LUT6 #(
    .INIT(64'h22222222BBB222B2)) 
    Logical_Operator_out10_carry_i_1__1
       (.I0(Add2_out1_1[13]),
        .I1(\delayMatch1_reg_reg[1][13] ),
        .I2(\Delay_out1_reg[13] [12]),
        .I3(OR_out1__0),
        .I4(\Delay_out1_reg[13]_0 [12]),
        .I5(Add2_out1_1[12]),
        .O(Logical_Operator_out10_carry_i_1__1_n_0));
  LUT6 #(
    .INIT(64'h22222222BBB222B2)) 
    Logical_Operator_out10_carry_i_2__1
       (.I0(\delayMatch1_reg_reg[1][11] ),
        .I1(Add2_out1_1[11]),
        .I2(\Delay_out1_reg[13] [10]),
        .I3(OR_out1__0),
        .I4(\Delay_out1_reg[13]_0 [10]),
        .I5(Add2_out1_1[10]),
        .O(Logical_Operator_out10_carry_i_2__1_n_0));
  LUT6 #(
    .INIT(64'h22222222BBB222B2)) 
    Logical_Operator_out10_carry_i_3__1
       (.I0(\delayMatch1_reg_reg[1][9] ),
        .I1(Add2_out1_1[9]),
        .I2(\Delay_out1_reg[13] [8]),
        .I3(OR_out1__0),
        .I4(\Delay_out1_reg[13]_0 [8]),
        .I5(Add2_out1_1[8]),
        .O(Logical_Operator_out10_carry_i_3__1_n_0));
  LUT6 #(
    .INIT(64'h22222222BBB222B2)) 
    Logical_Operator_out10_carry_i_4__1
       (.I0(\delayMatch1_reg_reg[1][7] ),
        .I1(Add2_out1_1[7]),
        .I2(\Delay_out1_reg[13] [6]),
        .I3(OR_out1__0),
        .I4(\Delay_out1_reg[13]_0 [6]),
        .I5(Add2_out1_1[6]),
        .O(Logical_Operator_out10_carry_i_4__1_n_0));
  LUT6 #(
    .INIT(64'h22222222BBB222B2)) 
    Logical_Operator_out10_carry_i_5__1
       (.I0(\delayMatch1_reg_reg[1][5] ),
        .I1(Add2_out1_1[5]),
        .I2(\Delay_out1_reg[13] [4]),
        .I3(OR_out1__0),
        .I4(\Delay_out1_reg[13]_0 [4]),
        .I5(Add2_out1_1[4]),
        .O(Logical_Operator_out10_carry_i_5__1_n_0));
  LUT6 #(
    .INIT(64'h22222222BBB222B2)) 
    Logical_Operator_out10_carry_i_6__1
       (.I0(\delayMatch1_reg_reg[1][3] ),
        .I1(Add2_out1_1[3]),
        .I2(\Delay_out1_reg[13] [2]),
        .I3(OR_out1__0),
        .I4(\Delay_out1_reg[13]_0 [2]),
        .I5(Add2_out1_1[2]),
        .O(Logical_Operator_out10_carry_i_6__1_n_0));
  LUT6 #(
    .INIT(64'h7577755510111000)) 
    Logical_Operator_out10_carry_i_7__1
       (.I0(Add2_out1_1[1]),
        .I1(Add1_out1_1[0]),
        .I2(\Delay_out1_reg[13]_0 [0]),
        .I3(OR_out1__0),
        .I4(\Delay_out1_reg[13] [0]),
        .I5(\delayMatch1_reg_reg[1][1] ),
        .O(Logical_Operator_out10_carry_i_7__1_n_0));
  LUT6 #(
    .INIT(64'hA95900000000A959)) 
    Logical_Operator_out10_carry_i_8__1
       (.I0(Add2_out1_1[12]),
        .I1(\Delay_out1_reg[13] [12]),
        .I2(OR_out1__0),
        .I3(\Delay_out1_reg[13]_0 [12]),
        .I4(\delayMatch1_reg_reg[1][13] ),
        .I5(Add2_out1_1[13]),
        .O(Logical_Operator_out10_carry_i_8__1_n_0));
  LUT6 #(
    .INIT(64'hA95900000000A959)) 
    Logical_Operator_out10_carry_i_9__1
       (.I0(Add2_out1_1[10]),
        .I1(\Delay_out1_reg[13] [10]),
        .I2(OR_out1__0),
        .I3(\Delay_out1_reg[13]_0 [10]),
        .I4(\delayMatch1_reg_reg[1][11] ),
        .I5(Add2_out1_1[11]),
        .O(Logical_Operator_out10_carry_i_9__1_n_0));
  (* COMPARATOR_THRESHOLD = "11" *) 
  CARRY8 Logical_Operator_out11_carry
       (.CI(1'b0),
        .CI_TOP(1'b0),
        .CO({NLW_Logical_Operator_out11_carry_CO_UNCONNECTED[7],Relational_Operator2_relop1,Logical_Operator_out11_carry_n_2,Logical_Operator_out11_carry_n_3,Logical_Operator_out11_carry_n_4,Logical_Operator_out11_carry_n_5,Logical_Operator_out11_carry_n_6,Logical_Operator_out11_carry_n_7}),
        .DI({1'b0,Logical_Operator_out11_carry_i_1__1_n_0,Logical_Operator_out11_carry_i_2__1_n_0,i__carry_i_3__1_n_0,i__carry_i_4__1_n_0,i__carry_i_5__1_n_0,i__carry_i_6__1_n_0,i__carry_i_7__1_n_0}),
        .O(NLW_Logical_Operator_out11_carry_O_UNCONNECTED[7:0]),
        .S({1'b0,Logical_Operator_out11_carry_i_3__1_n_0,Logical_Operator_out11_carry_i_4__1_n_0,Logical_Operator_out11_carry_i_5__1_n_0,Logical_Operator_out11_carry_i_6__1_n_0,Logical_Operator_out11_carry_i_7__1_n_0,Logical_Operator_out11_carry_i_8__1_n_0,Logical_Operator_out11_carry_i_9__1_n_0}));
  LUT6 #(
    .INIT(64'h222222B2B2B222B2)) 
    Logical_Operator_out11_carry_i_1__1
       (.I0(\delayMatch1_reg_reg[1][13] ),
        .I1(Add1_out1_1[13]),
        .I2(Add1_out1_1[12]),
        .I3(\Delay_out1_reg[13] [12]),
        .I4(OR_out1__0),
        .I5(\Delay_out1_reg[13]_0 [12]),
        .O(Logical_Operator_out11_carry_i_1__1_n_0));
  LUT6 #(
    .INIT(64'h222222B2B2B222B2)) 
    Logical_Operator_out11_carry_i_2__1
       (.I0(Add1_out1_1[11]),
        .I1(\delayMatch1_reg_reg[1][11] ),
        .I2(Add1_out1_1[10]),
        .I3(\Delay_out1_reg[13] [10]),
        .I4(OR_out1__0),
        .I5(\Delay_out1_reg[13]_0 [10]),
        .O(Logical_Operator_out11_carry_i_2__1_n_0));
  LUT6 #(
    .INIT(64'hA95900000000A959)) 
    Logical_Operator_out11_carry_i_3__1
       (.I0(Add1_out1_1[12]),
        .I1(\Delay_out1_reg[13] [12]),
        .I2(OR_out1__0),
        .I3(\Delay_out1_reg[13]_0 [12]),
        .I4(\delayMatch1_reg_reg[1][13] ),
        .I5(Add1_out1_1[13]),
        .O(Logical_Operator_out11_carry_i_3__1_n_0));
  LUT6 #(
    .INIT(64'hA95900000000A959)) 
    Logical_Operator_out11_carry_i_4__1
       (.I0(Add1_out1_1[10]),
        .I1(\Delay_out1_reg[13] [10]),
        .I2(OR_out1__0),
        .I3(\Delay_out1_reg[13]_0 [10]),
        .I4(\delayMatch1_reg_reg[1][11] ),
        .I5(Add1_out1_1[11]),
        .O(Logical_Operator_out11_carry_i_4__1_n_0));
  LUT6 #(
    .INIT(64'hA95900000000A959)) 
    Logical_Operator_out11_carry_i_5__1
       (.I0(Add1_out1_1[8]),
        .I1(\Delay_out1_reg[13] [8]),
        .I2(OR_out1__0),
        .I3(\Delay_out1_reg[13]_0 [8]),
        .I4(\delayMatch1_reg_reg[1][9] ),
        .I5(Add1_out1_1[9]),
        .O(Logical_Operator_out11_carry_i_5__1_n_0));
  LUT6 #(
    .INIT(64'hA95900000000A959)) 
    Logical_Operator_out11_carry_i_6__1
       (.I0(Add1_out1_1[6]),
        .I1(\Delay_out1_reg[13] [6]),
        .I2(OR_out1__0),
        .I3(\Delay_out1_reg[13]_0 [6]),
        .I4(\delayMatch1_reg_reg[1][7] ),
        .I5(Add1_out1_1[7]),
        .O(Logical_Operator_out11_carry_i_6__1_n_0));
  LUT6 #(
    .INIT(64'hA95900000000A959)) 
    Logical_Operator_out11_carry_i_7__1
       (.I0(Add1_out1_1[4]),
        .I1(\Delay_out1_reg[13] [4]),
        .I2(OR_out1__0),
        .I3(\Delay_out1_reg[13]_0 [4]),
        .I4(\delayMatch1_reg_reg[1][5] ),
        .I5(Add1_out1_1[5]),
        .O(Logical_Operator_out11_carry_i_7__1_n_0));
  LUT6 #(
    .INIT(64'hA95900000000A959)) 
    Logical_Operator_out11_carry_i_8__1
       (.I0(Add1_out1_1[2]),
        .I1(\Delay_out1_reg[13] [2]),
        .I2(OR_out1__0),
        .I3(\Delay_out1_reg[13]_0 [2]),
        .I4(\delayMatch1_reg_reg[1][3] ),
        .I5(Add1_out1_1[3]),
        .O(Logical_Operator_out11_carry_i_8__1_n_0));
  LUT6 #(
    .INIT(64'hE21D00000000E21D)) 
    Logical_Operator_out11_carry_i_9__1
       (.I0(\Delay_out1_reg[13] [0]),
        .I1(OR_out1__0),
        .I2(\Delay_out1_reg[13]_0 [0]),
        .I3(Add1_out1_1[0]),
        .I4(\delayMatch1_reg_reg[1][1] ),
        .I5(Add1_out1_1[1]),
        .O(Logical_Operator_out11_carry_i_9__1_n_0));
  (* SOFT_HLUTNM = "soft_lutpair25" *) 
  LUT3 #(
    .INIT(8'h02)) 
    \Saturation1_out1_1[11]_i_1 
       (.I0(Q[11]),
        .I1(Saturation1_out110_in),
        .I2(Q[13]),
        .O(Saturation1_out1[11]));
  (* SOFT_HLUTNM = "soft_lutpair18" *) 
  LUT3 #(
    .INIT(8'hBA)) 
    \Saturation1_out1_1[12]_i_1__1 
       (.I0(Saturation1_out110_in),
        .I1(Q[13]),
        .I2(Q[12]),
        .O(Saturation1_out1[12]));
  FDRE \Saturation1_out1_1_reg[11] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Saturation1_out1[11]),
        .Q(Saturation1_out1_1[11]),
        .R(RSTP));
  FDRE \Saturation1_out1_1_reg[12] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Saturation1_out1[12]),
        .Q(Saturation1_out1_1[12]),
        .R(RSTP));
  LUT6 #(
    .INIT(64'hA95900000000A959)) 
    i__carry_i_10
       (.I0(Add1_out1_1[8]),
        .I1(\Delay_out1_reg[13] [8]),
        .I2(OR_out1__0),
        .I3(\Delay_out1_reg[13]_0 [8]),
        .I4(\delayMatch1_reg_reg[1][9] ),
        .I5(Add1_out1_1[9]),
        .O(i__carry_i_10_n_0));
  LUT6 #(
    .INIT(64'hA95900000000A959)) 
    i__carry_i_11
       (.I0(Add1_out1_1[6]),
        .I1(\Delay_out1_reg[13] [6]),
        .I2(OR_out1__0),
        .I3(\Delay_out1_reg[13]_0 [6]),
        .I4(\delayMatch1_reg_reg[1][7] ),
        .I5(Add1_out1_1[7]),
        .O(i__carry_i_11_n_0));
  LUT6 #(
    .INIT(64'hA95900000000A959)) 
    i__carry_i_12
       (.I0(Add1_out1_1[4]),
        .I1(\Delay_out1_reg[13] [4]),
        .I2(OR_out1__0),
        .I3(\Delay_out1_reg[13]_0 [4]),
        .I4(\delayMatch1_reg_reg[1][5] ),
        .I5(Add1_out1_1[5]),
        .O(i__carry_i_12_n_0));
  LUT6 #(
    .INIT(64'hA95900000000A959)) 
    i__carry_i_13
       (.I0(Add1_out1_1[2]),
        .I1(\Delay_out1_reg[13] [2]),
        .I2(OR_out1__0),
        .I3(\Delay_out1_reg[13]_0 [2]),
        .I4(\delayMatch1_reg_reg[1][3] ),
        .I5(Add1_out1_1[3]),
        .O(i__carry_i_13_n_0));
  LUT6 #(
    .INIT(64'hE21D00000000E21D)) 
    i__carry_i_14
       (.I0(\Delay_out1_reg[13] [0]),
        .I1(OR_out1__0),
        .I2(\Delay_out1_reg[13]_0 [0]),
        .I3(Add1_out1_1[0]),
        .I4(\delayMatch1_reg_reg[1][1] ),
        .I5(Add1_out1_1[1]),
        .O(i__carry_i_14_n_0));
  LUT5 #(
    .INIT(32'hAAAEEEAE)) 
    i__carry_i_1__1
       (.I0(\delayMatch1_reg_reg[1][13] ),
        .I1(Saturation1_out1_1[12]),
        .I2(\Delay_out1_reg[13] [12]),
        .I3(OR_out1__0),
        .I4(\Delay_out1_reg[13]_0 [12]),
        .O(i__carry_i_1__1_n_0));
  LUT6 #(
    .INIT(64'h222222B2B2B222B2)) 
    i__carry_i_2__1
       (.I0(Saturation1_out1_1[11]),
        .I1(\delayMatch1_reg_reg[1][11] ),
        .I2(Add1_out1_1[10]),
        .I3(\Delay_out1_reg[13] [10]),
        .I4(OR_out1__0),
        .I5(\Delay_out1_reg[13]_0 [10]),
        .O(i__carry_i_2__1_n_0));
  LUT6 #(
    .INIT(64'h222222B2B2B222B2)) 
    i__carry_i_3__1
       (.I0(Add1_out1_1[9]),
        .I1(\delayMatch1_reg_reg[1][9] ),
        .I2(Add1_out1_1[8]),
        .I3(\Delay_out1_reg[13] [8]),
        .I4(OR_out1__0),
        .I5(\Delay_out1_reg[13]_0 [8]),
        .O(i__carry_i_3__1_n_0));
  LUT6 #(
    .INIT(64'h222222B2B2B222B2)) 
    i__carry_i_4__1
       (.I0(Add1_out1_1[7]),
        .I1(\delayMatch1_reg_reg[1][7] ),
        .I2(Add1_out1_1[6]),
        .I3(\Delay_out1_reg[13] [6]),
        .I4(OR_out1__0),
        .I5(\Delay_out1_reg[13]_0 [6]),
        .O(i__carry_i_4__1_n_0));
  LUT6 #(
    .INIT(64'h222222B2B2B222B2)) 
    i__carry_i_5__1
       (.I0(Add1_out1_1[5]),
        .I1(\delayMatch1_reg_reg[1][5] ),
        .I2(Add1_out1_1[4]),
        .I3(\Delay_out1_reg[13] [4]),
        .I4(OR_out1__0),
        .I5(\Delay_out1_reg[13]_0 [4]),
        .O(i__carry_i_5__1_n_0));
  LUT6 #(
    .INIT(64'h222222B2B2B222B2)) 
    i__carry_i_6__1
       (.I0(Add1_out1_1[3]),
        .I1(\delayMatch1_reg_reg[1][3] ),
        .I2(Add1_out1_1[2]),
        .I3(\Delay_out1_reg[13] [2]),
        .I4(OR_out1__0),
        .I5(\Delay_out1_reg[13]_0 [2]),
        .O(i__carry_i_6__1_n_0));
  LUT6 #(
    .INIT(64'h222222B2B2B222B2)) 
    i__carry_i_7__1
       (.I0(Add1_out1_1[1]),
        .I1(\delayMatch1_reg_reg[1][1] ),
        .I2(Add1_out1_1[0]),
        .I3(\Delay_out1_reg[13] [0]),
        .I4(OR_out1__0),
        .I5(\Delay_out1_reg[13]_0 [0]),
        .O(i__carry_i_7__1_n_0));
  LUT5 #(
    .INIT(32'h0000A959)) 
    i__carry_i_8__1
       (.I0(Saturation1_out1_1[12]),
        .I1(\Delay_out1_reg[13] [12]),
        .I2(OR_out1__0),
        .I3(\Delay_out1_reg[13]_0 [12]),
        .I4(\delayMatch1_reg_reg[1][13] ),
        .O(i__carry_i_8__1_n_0));
  LUT6 #(
    .INIT(64'hA95900000000A959)) 
    i__carry_i_9__1
       (.I0(Add1_out1_1[10]),
        .I1(\Delay_out1_reg[13] [10]),
        .I2(OR_out1__0),
        .I3(\Delay_out1_reg[13]_0 [10]),
        .I4(\delayMatch1_reg_reg[1][11] ),
        .I5(Saturation1_out1_1[11]),
        .O(i__carry_i_9__1_n_0));
  (* SOFT_HLUTNM = "soft_lutpair19" *) 
  LUT3 #(
    .INIT(8'h02)) 
    \minus_out1_1[10]_i_1__1 
       (.I0(\min_pulse_width_AXI_1_reg[9] ),
        .I1(Saturation1_out110_in),
        .I2(Q[13]),
        .O(minus_out1[10]));
  LUT6 #(
    .INIT(64'h00000001FFFFFFFE)) 
    \minus_out1_1[10]_i_2 
       (.I0(Q[9]),
        .I1(Q[7]),
        .I2(\min_pulse_width_AXI_1_reg[4] ),
        .I3(Q[6]),
        .I4(Q[8]),
        .I5(Q[10]),
        .O(\min_pulse_width_AXI_1_reg[9] ));
  (* SOFT_HLUTNM = "soft_lutpair20" *) 
  LUT3 #(
    .INIT(8'h02)) 
    \minus_out1_1[11]_i_1__1 
       (.I0(\min_pulse_width_AXI_1_reg[10] ),
        .I1(Saturation1_out110_in),
        .I2(Q[13]),
        .O(minus_out1[11]));
  LUT6 #(
    .INIT(64'h00000001FFFFFFFE)) 
    \minus_out1_1[11]_i_2 
       (.I0(Q[10]),
        .I1(Q[8]),
        .I2(\minus_out1_1[11]_i_3_n_0 ),
        .I3(Q[7]),
        .I4(Q[9]),
        .I5(Q[11]),
        .O(\min_pulse_width_AXI_1_reg[10] ));
  LUT6 #(
    .INIT(64'hFFFFFFFFFFFFFFFE)) 
    \minus_out1_1[11]_i_3 
       (.I0(Q[5]),
        .I1(Q[3]),
        .I2(\min_pulse_width_AXI_1_reg[0] ),
        .I3(Q[2]),
        .I4(Q[4]),
        .I5(Q[6]),
        .O(\minus_out1_1[11]_i_3_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair14" *) 
  LUT5 #(
    .INIT(32'hFFFF001E)) 
    \minus_out1_1[12]_i_1 
       (.I0(\minus_out1_1_reg[12]_0 ),
        .I1(Q[11]),
        .I2(Q[12]),
        .I3(Q[13]),
        .I4(Saturation1_out110_in),
        .O(minus_out1[12]));
  (* SOFT_HLUTNM = "soft_lutpair14" *) 
  LUT5 #(
    .INIT(32'hFFFF00FE)) 
    \minus_out1_1[13]_i_1 
       (.I0(Q[11]),
        .I1(\minus_out1_1_reg[12]_0 ),
        .I2(Q[12]),
        .I3(Q[13]),
        .I4(Saturation1_out110_in),
        .O(minus_out1[13]));
  LUT2 #(
    .INIT(4'h2)) 
    \minus_out1_1[13]_i_10__0 
       (.I0(Q[12]),
        .I1(Q[13]),
        .O(\minus_out1_1[13]_i_10__0_n_0 ));
  LUT2 #(
    .INIT(4'h1)) 
    \minus_out1_1[13]_i_11__0 
       (.I0(Q[10]),
        .I1(Q[11]),
        .O(\minus_out1_1[13]_i_11__0_n_0 ));
  LUT2 #(
    .INIT(4'h1)) 
    \minus_out1_1[13]_i_12__0 
       (.I0(Q[8]),
        .I1(Q[9]),
        .O(\minus_out1_1[13]_i_12__0_n_0 ));
  LUT2 #(
    .INIT(4'h1)) 
    \minus_out1_1[13]_i_13__0 
       (.I0(Q[6]),
        .I1(Q[7]),
        .O(\minus_out1_1[13]_i_13__0_n_0 ));
  LUT2 #(
    .INIT(4'h1)) 
    \minus_out1_1[13]_i_14__0 
       (.I0(Q[4]),
        .I1(Q[5]),
        .O(\minus_out1_1[13]_i_14__0_n_0 ));
  LUT2 #(
    .INIT(4'h1)) 
    \minus_out1_1[13]_i_15__1 
       (.I0(Q[2]),
        .I1(Q[3]),
        .O(\minus_out1_1[13]_i_15__1_n_0 ));
  LUT2 #(
    .INIT(4'h1)) 
    \minus_out1_1[13]_i_16 
       (.I0(Q[1]),
        .I1(Q[0]),
        .O(\minus_out1_1[13]_i_16_n_0 ));
  LUT2 #(
    .INIT(4'hE)) 
    \minus_out1_1[13]_i_4__0 
       (.I0(Q[10]),
        .I1(Q[11]),
        .O(\minus_out1_1[13]_i_4__0_n_0 ));
  LUT2 #(
    .INIT(4'hE)) 
    \minus_out1_1[13]_i_5__0 
       (.I0(Q[8]),
        .I1(Q[9]),
        .O(\minus_out1_1[13]_i_5__0_n_0 ));
  LUT2 #(
    .INIT(4'hE)) 
    \minus_out1_1[13]_i_6__0 
       (.I0(Q[6]),
        .I1(Q[7]),
        .O(\minus_out1_1[13]_i_6__0_n_0 ));
  LUT2 #(
    .INIT(4'hE)) 
    \minus_out1_1[13]_i_7__0 
       (.I0(Q[4]),
        .I1(Q[5]),
        .O(\minus_out1_1[13]_i_7__0_n_0 ));
  LUT2 #(
    .INIT(4'hE)) 
    \minus_out1_1[13]_i_8 
       (.I0(Q[2]),
        .I1(Q[3]),
        .O(\minus_out1_1[13]_i_8_n_0 ));
  LUT2 #(
    .INIT(4'hE)) 
    \minus_out1_1[13]_i_9 
       (.I0(Q[0]),
        .I1(Q[1]),
        .O(\minus_out1_1[13]_i_9_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair16" *) 
  LUT4 #(
    .INIT(16'h0006)) 
    \minus_out1_1[1]_i_1 
       (.I0(Q[1]),
        .I1(Q[0]),
        .I2(Saturation1_out110_in),
        .I3(Q[13]),
        .O(minus_out1[1]));
  (* SOFT_HLUTNM = "soft_lutpair16" *) 
  LUT5 #(
    .INIT(32'h00000056)) 
    \minus_out1_1[2]_i_1__1 
       (.I0(Q[2]),
        .I1(Q[0]),
        .I2(Q[1]),
        .I3(Saturation1_out110_in),
        .I4(Q[13]),
        .O(minus_out1[2]));
  (* SOFT_HLUTNM = "soft_lutpair15" *) 
  LUT5 #(
    .INIT(32'h00005556)) 
    \minus_out1_1[3]_i_1__1 
       (.I0(Q[3]),
        .I1(Q[1]),
        .I2(Q[0]),
        .I3(Q[2]),
        .I4(\minus_out1_1[5]_i_3_n_0 ),
        .O(minus_out1[3]));
  LUT6 #(
    .INIT(64'h0000000055555556)) 
    \minus_out1_1[4]_i_1__1 
       (.I0(Q[4]),
        .I1(Q[2]),
        .I2(Q[0]),
        .I3(Q[1]),
        .I4(Q[3]),
        .I5(\minus_out1_1[5]_i_3_n_0 ),
        .O(minus_out1[4]));
  LUT6 #(
    .INIT(64'h0000000055555556)) 
    \minus_out1_1[5]_i_1__1 
       (.I0(Q[5]),
        .I1(Q[3]),
        .I2(\min_pulse_width_AXI_1_reg[0] ),
        .I3(Q[2]),
        .I4(Q[4]),
        .I5(\minus_out1_1[5]_i_3_n_0 ),
        .O(minus_out1[5]));
  (* SOFT_HLUTNM = "soft_lutpair15" *) 
  LUT2 #(
    .INIT(4'hE)) 
    \minus_out1_1[5]_i_2 
       (.I0(Q[0]),
        .I1(Q[1]),
        .O(\min_pulse_width_AXI_1_reg[0] ));
  LUT2 #(
    .INIT(4'hE)) 
    \minus_out1_1[5]_i_3 
       (.I0(Q[13]),
        .I1(Saturation1_out110_in),
        .O(\minus_out1_1[5]_i_3_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair18" *) 
  LUT3 #(
    .INIT(8'h02)) 
    \minus_out1_1[6]_i_1__1 
       (.I0(\min_pulse_width_AXI_1_reg[5] ),
        .I1(Saturation1_out110_in),
        .I2(Q[13]),
        .O(minus_out1[6]));
  LUT6 #(
    .INIT(64'h00000001FFFFFFFE)) 
    \minus_out1_1[6]_i_2 
       (.I0(Q[5]),
        .I1(Q[3]),
        .I2(\min_pulse_width_AXI_1_reg[0] ),
        .I3(Q[2]),
        .I4(Q[4]),
        .I5(Q[6]),
        .O(\min_pulse_width_AXI_1_reg[5] ));
  (* SOFT_HLUTNM = "soft_lutpair13" *) 
  LUT5 #(
    .INIT(32'h0000001E)) 
    \minus_out1_1[7]_i_1 
       (.I0(Q[6]),
        .I1(\min_pulse_width_AXI_1_reg[4] ),
        .I2(Q[7]),
        .I3(Saturation1_out110_in),
        .I4(Q[13]),
        .O(minus_out1[7]));
  LUT6 #(
    .INIT(64'h00000000000001FE)) 
    \minus_out1_1[8]_i_1 
       (.I0(Q[7]),
        .I1(\min_pulse_width_AXI_1_reg[4] ),
        .I2(Q[6]),
        .I3(Q[8]),
        .I4(Saturation1_out110_in),
        .I5(Q[13]),
        .O(minus_out1[8]));
  LUT6 #(
    .INIT(64'hFFFFFFFFFFFFFFFE)) 
    \minus_out1_1[8]_i_2 
       (.I0(Q[4]),
        .I1(Q[2]),
        .I2(Q[0]),
        .I3(Q[1]),
        .I4(Q[3]),
        .I5(Q[5]),
        .O(\min_pulse_width_AXI_1_reg[4] ));
  (* SOFT_HLUTNM = "soft_lutpair19" *) 
  LUT3 #(
    .INIT(8'h02)) 
    \minus_out1_1[9]_i_1__1 
       (.I0(\min_pulse_width_AXI_1_reg[8] ),
        .I1(Saturation1_out110_in),
        .I2(Q[13]),
        .O(minus_out1[9]));
  LUT5 #(
    .INIT(32'h0001FFFE)) 
    \minus_out1_1[9]_i_2 
       (.I0(Q[8]),
        .I1(Q[6]),
        .I2(\min_pulse_width_AXI_1_reg[4] ),
        .I3(Q[7]),
        .I4(Q[9]),
        .O(\min_pulse_width_AXI_1_reg[8] ));
  FDRE \minus_out1_1_reg[10] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(minus_out1[10]),
        .Q(minus_out1_1[10]),
        .R(RSTP));
  FDRE \minus_out1_1_reg[11] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(minus_out1[11]),
        .Q(minus_out1_1[11]),
        .R(RSTP));
  FDRE \minus_out1_1_reg[12] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(minus_out1[12]),
        .Q(minus_out1_1[12]),
        .R(RSTP));
  FDRE \minus_out1_1_reg[13] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(minus_out1[13]),
        .Q(minus_out1_1[13]),
        .R(RSTP));
  (* COMPARATOR_THRESHOLD = "11" *) 
  CARRY8 \minus_out1_1_reg[13]_i_3 
       (.CI(1'b0),
        .CI_TOP(1'b0),
        .CO({\NLW_minus_out1_1_reg[13]_i_3_CO_UNCONNECTED [7],Saturation1_out110_in,\minus_out1_1_reg[13]_i_3_n_2 ,\minus_out1_1_reg[13]_i_3_n_3 ,\minus_out1_1_reg[13]_i_3_n_4 ,\minus_out1_1_reg[13]_i_3_n_5 ,\minus_out1_1_reg[13]_i_3_n_6 ,\minus_out1_1_reg[13]_i_3_n_7 }),
        .DI({1'b0,1'b0,\minus_out1_1[13]_i_4__0_n_0 ,\minus_out1_1[13]_i_5__0_n_0 ,\minus_out1_1[13]_i_6__0_n_0 ,\minus_out1_1[13]_i_7__0_n_0 ,\minus_out1_1[13]_i_8_n_0 ,\minus_out1_1[13]_i_9_n_0 }),
        .O(\NLW_minus_out1_1_reg[13]_i_3_O_UNCONNECTED [7:0]),
        .S({1'b0,\minus_out1_1[13]_i_10__0_n_0 ,\minus_out1_1[13]_i_11__0_n_0 ,\minus_out1_1[13]_i_12__0_n_0 ,\minus_out1_1[13]_i_13__0_n_0 ,\minus_out1_1[13]_i_14__0_n_0 ,\minus_out1_1[13]_i_15__1_n_0 ,\minus_out1_1[13]_i_16_n_0 }));
  FDRE \minus_out1_1_reg[1] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(minus_out1[1]),
        .Q(minus_out1_1[1]),
        .R(RSTP));
  FDRE \minus_out1_1_reg[2] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(minus_out1[2]),
        .Q(minus_out1_1[2]),
        .R(RSTP));
  FDRE \minus_out1_1_reg[3] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(minus_out1[3]),
        .Q(minus_out1_1[3]),
        .R(RSTP));
  FDRE \minus_out1_1_reg[4] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(minus_out1[4]),
        .Q(minus_out1_1[4]),
        .R(RSTP));
  FDRE \minus_out1_1_reg[5] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(minus_out1[5]),
        .Q(minus_out1_1[5]),
        .R(RSTP));
  FDRE \minus_out1_1_reg[6] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(minus_out1[6]),
        .Q(minus_out1_1[6]),
        .R(RSTP));
  FDRE \minus_out1_1_reg[7] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(minus_out1[7]),
        .Q(minus_out1_1[7]),
        .R(RSTP));
  FDRE \minus_out1_1_reg[8] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(minus_out1[8]),
        .Q(minus_out1_1[8]),
        .R(RSTP));
  FDRE \minus_out1_1_reg[9] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(minus_out1[9]),
        .Q(minus_out1_1[9]),
        .R(RSTP));
  LUT5 #(
    .INIT(32'hFFFF4540)) 
    modulating_signal_in_clock_cycles_1_reg_i_10__1
       (.I0(Logical_Operator_out1__1),
        .I1(\Delay_out1_reg[13]_0 [4]),
        .I2(OR_out1__0),
        .I3(\Delay_out1_reg[13] [4]),
        .I4(modulating_signal_in_clock_cycles_1_reg_i_17_n_0),
        .O(B[4]));
  LUT5 #(
    .INIT(32'hBABBBAAA)) 
    modulating_signal_in_clock_cycles_1_reg_i_11__1
       (.I0(modulating_signal_in_clock_cycles_1_reg_i_18_n_0),
        .I1(Logical_Operator_out1__1),
        .I2(\Delay_out1_reg[13]_0 [3]),
        .I3(OR_out1__0),
        .I4(\Delay_out1_reg[13] [3]),
        .O(B[3]));
  LUT5 #(
    .INIT(32'hFFFF4540)) 
    modulating_signal_in_clock_cycles_1_reg_i_12__1
       (.I0(Logical_Operator_out1__1),
        .I1(\Delay_out1_reg[13]_0 [2]),
        .I2(OR_out1__0),
        .I3(\Delay_out1_reg[13] [2]),
        .I4(modulating_signal_in_clock_cycles_1_reg_i_17_n_0),
        .O(B[2]));
  LUT5 #(
    .INIT(32'hFFFF4540)) 
    modulating_signal_in_clock_cycles_1_reg_i_13__1
       (.I0(Logical_Operator_out1__1),
        .I1(\Delay_out1_reg[13]_0 [1]),
        .I2(OR_out1__0),
        .I3(\Delay_out1_reg[13] [1]),
        .I4(modulating_signal_in_clock_cycles_1_reg_i_17_n_0),
        .O(B[1]));
  LUT6 #(
    .INIT(64'h00FFFFFFB8B8B8B8)) 
    modulating_signal_in_clock_cycles_1_reg_i_14__1
       (.I0(\Delay_out1_reg[13]_0 [0]),
        .I1(OR_out1__0),
        .I2(\Delay_out1_reg[13] [0]),
        .I3(Relational_Operator1_relop1),
        .I4(Relational_Operator_relop1),
        .I5(Logical_Operator_out1__1),
        .O(B[0]));
  (* SOFT_HLUTNM = "soft_lutpair17" *) 
  LUT4 #(
    .INIT(16'hFEEE)) 
    modulating_signal_in_clock_cycles_1_reg_i_15
       (.I0(Relational_Operator2_relop1),
        .I1(Relational_Operator3_relop1),
        .I2(Relational_Operator_relop1),
        .I3(Relational_Operator1_relop1),
        .O(Logical_Operator_out1__1));
  LUT6 #(
    .INIT(64'hFFFFFFFF00008000)) 
    modulating_signal_in_clock_cycles_1_reg_i_16
       (.I0(\HDL_Counter2_count_reg[11]_0 ),
        .I1(\Delay_out1_reg[0] ),
        .I2(\Delay_out1_reg[0]_0 ),
        .I3(D),
        .I4(HDL_Counter2_count_reg[11]),
        .I5(CO),
        .O(OR_out1__0));
  LUT3 #(
    .INIT(8'h70)) 
    modulating_signal_in_clock_cycles_1_reg_i_17
       (.I0(Relational_Operator1_relop1),
        .I1(Relational_Operator_relop1),
        .I2(Relational_Operator2_relop1),
        .O(modulating_signal_in_clock_cycles_1_reg_i_17_n_0));
  (* SOFT_HLUTNM = "soft_lutpair17" *) 
  LUT4 #(
    .INIT(16'h0070)) 
    modulating_signal_in_clock_cycles_1_reg_i_18
       (.I0(Relational_Operator1_relop1),
        .I1(Relational_Operator_relop1),
        .I2(Relational_Operator3_relop1),
        .I3(Relational_Operator2_relop1),
        .O(modulating_signal_in_clock_cycles_1_reg_i_18_n_0));
  LUT5 #(
    .INIT(32'hFFFF4540)) 
    modulating_signal_in_clock_cycles_1_reg_i_1__1
       (.I0(Logical_Operator_out1__1),
        .I1(\Delay_out1_reg[13]_0 [13]),
        .I2(OR_out1__0),
        .I3(\Delay_out1_reg[13] [13]),
        .I4(modulating_signal_in_clock_cycles_1_reg_i_17_n_0),
        .O(B[13]));
  LUT5 #(
    .INIT(32'hBABBBAAA)) 
    modulating_signal_in_clock_cycles_1_reg_i_2__1
       (.I0(modulating_signal_in_clock_cycles_1_reg_i_18_n_0),
        .I1(Logical_Operator_out1__1),
        .I2(\Delay_out1_reg[13]_0 [12]),
        .I3(OR_out1__0),
        .I4(\Delay_out1_reg[13] [12]),
        .O(B[12]));
  LUT5 #(
    .INIT(32'hFFFF4540)) 
    modulating_signal_in_clock_cycles_1_reg_i_3__1
       (.I0(Logical_Operator_out1__1),
        .I1(\Delay_out1_reg[13]_0 [11]),
        .I2(OR_out1__0),
        .I3(\Delay_out1_reg[13] [11]),
        .I4(modulating_signal_in_clock_cycles_1_reg_i_17_n_0),
        .O(B[11]));
  LUT5 #(
    .INIT(32'hFFFF4540)) 
    modulating_signal_in_clock_cycles_1_reg_i_4__1
       (.I0(Logical_Operator_out1__1),
        .I1(\Delay_out1_reg[13]_0 [10]),
        .I2(OR_out1__0),
        .I3(\Delay_out1_reg[13] [10]),
        .I4(modulating_signal_in_clock_cycles_1_reg_i_17_n_0),
        .O(B[10]));
  LUT5 #(
    .INIT(32'hFFFF4540)) 
    modulating_signal_in_clock_cycles_1_reg_i_5__1
       (.I0(Logical_Operator_out1__1),
        .I1(\Delay_out1_reg[13]_0 [9]),
        .I2(OR_out1__0),
        .I3(\Delay_out1_reg[13] [9]),
        .I4(modulating_signal_in_clock_cycles_1_reg_i_17_n_0),
        .O(B[9]));
  LUT5 #(
    .INIT(32'hFFFF4540)) 
    modulating_signal_in_clock_cycles_1_reg_i_6__1
       (.I0(Logical_Operator_out1__1),
        .I1(\Delay_out1_reg[13]_0 [8]),
        .I2(OR_out1__0),
        .I3(\Delay_out1_reg[13] [8]),
        .I4(modulating_signal_in_clock_cycles_1_reg_i_17_n_0),
        .O(B[8]));
  LUT5 #(
    .INIT(32'hFFFF4540)) 
    modulating_signal_in_clock_cycles_1_reg_i_7__1
       (.I0(Logical_Operator_out1__1),
        .I1(\Delay_out1_reg[13]_0 [7]),
        .I2(OR_out1__0),
        .I3(\Delay_out1_reg[13] [7]),
        .I4(modulating_signal_in_clock_cycles_1_reg_i_17_n_0),
        .O(B[7]));
  LUT5 #(
    .INIT(32'hFFFF4540)) 
    modulating_signal_in_clock_cycles_1_reg_i_8__1
       (.I0(Logical_Operator_out1__1),
        .I1(\Delay_out1_reg[13]_0 [6]),
        .I2(OR_out1__0),
        .I3(\Delay_out1_reg[13] [6]),
        .I4(modulating_signal_in_clock_cycles_1_reg_i_17_n_0),
        .O(B[6]));
  LUT5 #(
    .INIT(32'hBABBBAAA)) 
    modulating_signal_in_clock_cycles_1_reg_i_9__1
       (.I0(modulating_signal_in_clock_cycles_1_reg_i_18_n_0),
        .I1(Logical_Operator_out1__1),
        .I2(\Delay_out1_reg[13]_0 [5]),
        .I3(OR_out1__0),
        .I4(\Delay_out1_reg[13] [5]),
        .O(B[5]));
endmodule

(* ORIG_REF_NAME = "PWM_SS_3L_ip_src_LimitPulseWidth_b" *) 
module zusys_PWM_SS_3L_ip_0_0_PWM_SS_3L_ip_src_LimitPulseWidth_b
   (\delayMatch3_reg_reg[1][13] ,
    PWM_en_AXI_2_reg,
    B,
    \delayMatch3_reg_reg[1][11] ,
    \delayMatch3_reg_reg[1][9] ,
    \delayMatch3_reg_reg[1][7] ,
    \delayMatch3_reg_reg[1][5] ,
    \delayMatch3_reg_reg[1][3] ,
    \delayMatch3_reg_reg[1][1] ,
    RSTP,
    CEP,
    IPCORE_CLK,
    Q,
    \minus_out1_1_reg[7]_0 ,
    \minus_out1_1_reg[12]_0 ,
    \Delay1_out1_reg[13] ,
    \Delay1_out1_reg[13]_0 ,
    \Delay1_out1_reg[13]_1 ,
    D,
    HDL_Counter2_count_reg,
    CO,
    \Delay1_out1_reg[0] ,
    \Delay1_out1_reg[0]_0 ,
    \Delay1_out1_reg[0]_1 ,
    \minus_out1_1_reg[5]_0 ,
    \minus_out1_1_reg[6]_0 ,
    \minus_out1_1_reg[9]_0 ,
    \minus_out1_1_reg[10]_0 ,
    \minus_out1_1_reg[11]_0 );
  output \delayMatch3_reg_reg[1][13] ;
  output PWM_en_AXI_2_reg;
  output [13:0]B;
  output \delayMatch3_reg_reg[1][11] ;
  output \delayMatch3_reg_reg[1][9] ;
  output \delayMatch3_reg_reg[1][7] ;
  output \delayMatch3_reg_reg[1][5] ;
  output \delayMatch3_reg_reg[1][3] ;
  output \delayMatch3_reg_reg[1][1] ;
  input RSTP;
  input CEP;
  input IPCORE_CLK;
  input [13:0]Q;
  input \minus_out1_1_reg[7]_0 ;
  input \minus_out1_1_reg[12]_0 ;
  input [13:0]\Delay1_out1_reg[13] ;
  input [13:0]\Delay1_out1_reg[13]_0 ;
  input \Delay1_out1_reg[13]_1 ;
  input [0:0]D;
  input [0:0]HDL_Counter2_count_reg;
  input [0:0]CO;
  input \Delay1_out1_reg[0] ;
  input \Delay1_out1_reg[0]_0 ;
  input \Delay1_out1_reg[0]_1 ;
  input \minus_out1_1_reg[5]_0 ;
  input \minus_out1_1_reg[6]_0 ;
  input \minus_out1_1_reg[9]_0 ;
  input \minus_out1_1_reg[10]_0 ;
  input \minus_out1_1_reg[11]_0 ;

  wire [13:11]Add1_out1;
  wire [13:0]Add1_out1_1;
  wire \Add1_out1_1[13]_i_2__0_n_0 ;
  wire \Add1_out1_1[13]_i_3__0_n_0 ;
  wire \Add1_out1_1[13]_i_4__0_n_0 ;
  wire \Add1_out1_1_reg[13]_i_1__0_n_6 ;
  wire \Add1_out1_1_reg[13]_i_1__0_n_7 ;
  wire [13:1]Add2_out1;
  wire [13:1]Add2_out1_1;
  wire \Add2_out1_1[13]_i_2__0_n_0 ;
  wire \Add2_out1_1[13]_i_3__0_n_0 ;
  wire \Add2_out1_1[13]_i_4__0_n_0 ;
  wire \Add2_out1_1[13]_i_5__0_n_0 ;
  wire \Add2_out1_1[8]_i_10__0_n_0 ;
  wire \Add2_out1_1[8]_i_2__0_n_0 ;
  wire \Add2_out1_1[8]_i_3__0_n_0 ;
  wire \Add2_out1_1[8]_i_4__0_n_0 ;
  wire \Add2_out1_1[8]_i_5__0_n_0 ;
  wire \Add2_out1_1[8]_i_6__0_n_0 ;
  wire \Add2_out1_1[8]_i_7__0_n_0 ;
  wire \Add2_out1_1[8]_i_8__0_n_0 ;
  wire \Add2_out1_1[8]_i_9__0_n_0 ;
  wire \Add2_out1_1_reg[13]_i_1__0_n_4 ;
  wire \Add2_out1_1_reg[13]_i_1__0_n_5 ;
  wire \Add2_out1_1_reg[13]_i_1__0_n_6 ;
  wire \Add2_out1_1_reg[13]_i_1__0_n_7 ;
  wire \Add2_out1_1_reg[8]_i_1__0_n_0 ;
  wire \Add2_out1_1_reg[8]_i_1__0_n_1 ;
  wire \Add2_out1_1_reg[8]_i_1__0_n_2 ;
  wire \Add2_out1_1_reg[8]_i_1__0_n_3 ;
  wire \Add2_out1_1_reg[8]_i_1__0_n_4 ;
  wire \Add2_out1_1_reg[8]_i_1__0_n_5 ;
  wire \Add2_out1_1_reg[8]_i_1__0_n_6 ;
  wire \Add2_out1_1_reg[8]_i_1__0_n_7 ;
  wire [13:0]B;
  wire CEP;
  wire [0:0]CO;
  wire [0:0]D;
  wire \Delay1_out1_reg[0] ;
  wire \Delay1_out1_reg[0]_0 ;
  wire \Delay1_out1_reg[0]_1 ;
  wire [13:0]\Delay1_out1_reg[13] ;
  wire [13:0]\Delay1_out1_reg[13]_0 ;
  wire \Delay1_out1_reg[13]_1 ;
  wire [0:0]HDL_Counter2_count_reg;
  wire IPCORE_CLK;
  wire Logical_Operator1_out10_carry_i_10__0_n_0;
  wire Logical_Operator1_out10_carry_i_11__0_n_0;
  wire Logical_Operator1_out10_carry_i_12__0_n_0;
  wire Logical_Operator1_out10_carry_i_13__0_n_0;
  wire Logical_Operator1_out10_carry_i_14__0_n_0;
  wire Logical_Operator1_out10_carry_i_1__0_n_0;
  wire Logical_Operator1_out10_carry_i_2__0_n_0;
  wire Logical_Operator1_out10_carry_i_3__0_n_0;
  wire Logical_Operator1_out10_carry_i_4__0_n_0;
  wire Logical_Operator1_out10_carry_i_5__0_n_0;
  wire Logical_Operator1_out10_carry_i_6__0_n_0;
  wire Logical_Operator1_out10_carry_i_7__0_n_0;
  wire Logical_Operator1_out10_carry_i_8__0_n_0;
  wire Logical_Operator1_out10_carry_i_9__0_n_0;
  wire Logical_Operator1_out10_carry_n_2;
  wire Logical_Operator1_out10_carry_n_3;
  wire Logical_Operator1_out10_carry_n_4;
  wire Logical_Operator1_out10_carry_n_5;
  wire Logical_Operator1_out10_carry_n_6;
  wire Logical_Operator1_out10_carry_n_7;
  wire \Logical_Operator1_out10_inferred__0/i__carry_n_2 ;
  wire \Logical_Operator1_out10_inferred__0/i__carry_n_3 ;
  wire \Logical_Operator1_out10_inferred__0/i__carry_n_4 ;
  wire \Logical_Operator1_out10_inferred__0/i__carry_n_5 ;
  wire \Logical_Operator1_out10_inferred__0/i__carry_n_6 ;
  wire \Logical_Operator1_out10_inferred__0/i__carry_n_7 ;
  wire Logical_Operator_out10_carry_i_10__0_n_0;
  wire Logical_Operator_out10_carry_i_11__0_n_0;
  wire Logical_Operator_out10_carry_i_12__0_n_0;
  wire Logical_Operator_out10_carry_i_13__0_n_0;
  wire Logical_Operator_out10_carry_i_14__0_n_0;
  wire Logical_Operator_out10_carry_i_1__0_n_0;
  wire Logical_Operator_out10_carry_i_2__0_n_0;
  wire Logical_Operator_out10_carry_i_3__0_n_0;
  wire Logical_Operator_out10_carry_i_4__0_n_0;
  wire Logical_Operator_out10_carry_i_5__0_n_0;
  wire Logical_Operator_out10_carry_i_6__0_n_0;
  wire Logical_Operator_out10_carry_i_7__0_n_0;
  wire Logical_Operator_out10_carry_i_8__0_n_0;
  wire Logical_Operator_out10_carry_i_9__0_n_0;
  wire Logical_Operator_out10_carry_n_2;
  wire Logical_Operator_out10_carry_n_3;
  wire Logical_Operator_out10_carry_n_4;
  wire Logical_Operator_out10_carry_n_5;
  wire Logical_Operator_out10_carry_n_6;
  wire Logical_Operator_out10_carry_n_7;
  wire Logical_Operator_out11_carry_i_1__0_n_0;
  wire Logical_Operator_out11_carry_i_2__0_n_0;
  wire Logical_Operator_out11_carry_i_3__0_n_0;
  wire Logical_Operator_out11_carry_i_4__0_n_0;
  wire Logical_Operator_out11_carry_i_5__0_n_0;
  wire Logical_Operator_out11_carry_i_6__0_n_0;
  wire Logical_Operator_out11_carry_i_7__0_n_0;
  wire Logical_Operator_out11_carry_i_8__0_n_0;
  wire Logical_Operator_out11_carry_i_9__0_n_0;
  wire Logical_Operator_out11_carry_n_2;
  wire Logical_Operator_out11_carry_n_3;
  wire Logical_Operator_out11_carry_n_4;
  wire Logical_Operator_out11_carry_n_5;
  wire Logical_Operator_out11_carry_n_6;
  wire Logical_Operator_out11_carry_n_7;
  wire Logical_Operator_out1__1;
  wire PWM_en_AXI_2_reg;
  wire [13:0]Q;
  wire RSTP;
  wire Relational_Operator1_relop1;
  wire Relational_Operator2_relop1;
  wire Relational_Operator3_relop1;
  wire Relational_Operator_relop1;
  wire [12:0]Saturation1_out1;
  wire Saturation1_out110_in;
  wire [12:11]Saturation1_out1_1;
  wire \delayMatch3_reg_reg[1][11] ;
  wire \delayMatch3_reg_reg[1][13] ;
  wire \delayMatch3_reg_reg[1][1] ;
  wire \delayMatch3_reg_reg[1][3] ;
  wire \delayMatch3_reg_reg[1][5] ;
  wire \delayMatch3_reg_reg[1][7] ;
  wire \delayMatch3_reg_reg[1][9] ;
  wire i__carry_i_10__0_n_0;
  wire i__carry_i_11__0_n_0;
  wire i__carry_i_12__0_n_0;
  wire i__carry_i_13__0_n_0;
  wire i__carry_i_14__0_n_0;
  wire i__carry_i_1__0_n_0;
  wire i__carry_i_2__0_n_0;
  wire i__carry_i_3__0_n_0;
  wire i__carry_i_4__0_n_0;
  wire i__carry_i_5__0_n_0;
  wire i__carry_i_6__0_n_0;
  wire i__carry_i_7__0_n_0;
  wire i__carry_i_8__0_n_0;
  wire i__carry_i_9__0_n_0;
  wire [13:1]minus_out1;
  wire [13:1]minus_out1_1;
  wire \minus_out1_1[13]_i_10__1_n_0 ;
  wire \minus_out1_1[13]_i_11__1_n_0 ;
  wire \minus_out1_1[13]_i_12__1_n_0 ;
  wire \minus_out1_1[13]_i_13__1_n_0 ;
  wire \minus_out1_1[13]_i_14__1_n_0 ;
  wire \minus_out1_1[13]_i_15__0_n_0 ;
  wire \minus_out1_1[13]_i_3__0_n_0 ;
  wire \minus_out1_1[13]_i_4__1_n_0 ;
  wire \minus_out1_1[13]_i_5__1_n_0 ;
  wire \minus_out1_1[13]_i_6__1_n_0 ;
  wire \minus_out1_1[13]_i_7__1_n_0 ;
  wire \minus_out1_1[13]_i_8__0_n_0 ;
  wire \minus_out1_1[13]_i_9__1_n_0 ;
  wire \minus_out1_1[5]_i_2__0_n_0 ;
  wire \minus_out1_1_reg[10]_0 ;
  wire \minus_out1_1_reg[11]_0 ;
  wire \minus_out1_1_reg[12]_0 ;
  wire \minus_out1_1_reg[13]_i_2_n_2 ;
  wire \minus_out1_1_reg[13]_i_2_n_3 ;
  wire \minus_out1_1_reg[13]_i_2_n_4 ;
  wire \minus_out1_1_reg[13]_i_2_n_5 ;
  wire \minus_out1_1_reg[13]_i_2_n_6 ;
  wire \minus_out1_1_reg[13]_i_2_n_7 ;
  wire \minus_out1_1_reg[5]_0 ;
  wire \minus_out1_1_reg[6]_0 ;
  wire \minus_out1_1_reg[7]_0 ;
  wire \minus_out1_1_reg[9]_0 ;
  wire modulating_signal_in_clock_cycles_1_reg_i_17__0_n_0;
  wire modulating_signal_in_clock_cycles_1_reg_i_18__0_n_0;
  wire [7:2]\NLW_Add1_out1_1_reg[13]_i_1__0_CO_UNCONNECTED ;
  wire [7:3]\NLW_Add1_out1_1_reg[13]_i_1__0_O_UNCONNECTED ;
  wire [7:4]\NLW_Add2_out1_1_reg[13]_i_1__0_CO_UNCONNECTED ;
  wire [7:5]\NLW_Add2_out1_1_reg[13]_i_1__0_O_UNCONNECTED ;
  wire [7:7]NLW_Logical_Operator1_out10_carry_CO_UNCONNECTED;
  wire [7:0]NLW_Logical_Operator1_out10_carry_O_UNCONNECTED;
  wire [7:7]\NLW_Logical_Operator1_out10_inferred__0/i__carry_CO_UNCONNECTED ;
  wire [7:0]\NLW_Logical_Operator1_out10_inferred__0/i__carry_O_UNCONNECTED ;
  wire [7:7]NLW_Logical_Operator_out10_carry_CO_UNCONNECTED;
  wire [7:0]NLW_Logical_Operator_out10_carry_O_UNCONNECTED;
  wire [7:7]NLW_Logical_Operator_out11_carry_CO_UNCONNECTED;
  wire [7:0]NLW_Logical_Operator_out11_carry_O_UNCONNECTED;
  wire [7:7]\NLW_minus_out1_1_reg[13]_i_2_CO_UNCONNECTED ;
  wire [7:0]\NLW_minus_out1_1_reg[13]_i_2_O_UNCONNECTED ;

  (* SOFT_HLUTNM = "soft_lutpair32" *) 
  LUT3 #(
    .INIT(8'h02)) 
    \Add1_out1_1[0]_i_1__0 
       (.I0(Q[0]),
        .I1(Saturation1_out110_in),
        .I2(Q[13]),
        .O(Saturation1_out1[0]));
  (* SOFT_HLUTNM = "soft_lutpair37" *) 
  LUT3 #(
    .INIT(8'h02)) 
    \Add1_out1_1[10]_i_1__0 
       (.I0(Q[10]),
        .I1(Saturation1_out110_in),
        .I2(Q[13]),
        .O(Saturation1_out1[10]));
  LUT3 #(
    .INIT(8'hBA)) 
    \Add1_out1_1[13]_i_2__0 
       (.I0(Saturation1_out110_in),
        .I1(Q[13]),
        .I2(Q[12]),
        .O(\Add1_out1_1[13]_i_2__0_n_0 ));
  LUT3 #(
    .INIT(8'h0D)) 
    \Add1_out1_1[13]_i_3__0 
       (.I0(Q[12]),
        .I1(Q[13]),
        .I2(Saturation1_out110_in),
        .O(\Add1_out1_1[13]_i_3__0_n_0 ));
  LUT3 #(
    .INIT(8'h02)) 
    \Add1_out1_1[13]_i_4__0 
       (.I0(Q[11]),
        .I1(Saturation1_out110_in),
        .I2(Q[13]),
        .O(\Add1_out1_1[13]_i_4__0_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair33" *) 
  LUT3 #(
    .INIT(8'h02)) 
    \Add1_out1_1[1]_i_1__0 
       (.I0(Q[1]),
        .I1(Saturation1_out110_in),
        .I2(Q[13]),
        .O(Saturation1_out1[1]));
  (* SOFT_HLUTNM = "soft_lutpair33" *) 
  LUT3 #(
    .INIT(8'h02)) 
    \Add1_out1_1[2]_i_1__0 
       (.I0(Q[2]),
        .I1(Saturation1_out110_in),
        .I2(Q[13]),
        .O(Saturation1_out1[2]));
  (* SOFT_HLUTNM = "soft_lutpair34" *) 
  LUT3 #(
    .INIT(8'h02)) 
    \Add1_out1_1[3]_i_1__0 
       (.I0(Q[3]),
        .I1(Saturation1_out110_in),
        .I2(Q[13]),
        .O(Saturation1_out1[3]));
  (* SOFT_HLUTNM = "soft_lutpair34" *) 
  LUT3 #(
    .INIT(8'h02)) 
    \Add1_out1_1[4]_i_1__0 
       (.I0(Q[4]),
        .I1(Saturation1_out110_in),
        .I2(Q[13]),
        .O(Saturation1_out1[4]));
  (* SOFT_HLUTNM = "soft_lutpair35" *) 
  LUT3 #(
    .INIT(8'h02)) 
    \Add1_out1_1[5]_i_1__0 
       (.I0(Q[5]),
        .I1(Saturation1_out110_in),
        .I2(Q[13]),
        .O(Saturation1_out1[5]));
  (* SOFT_HLUTNM = "soft_lutpair26" *) 
  LUT3 #(
    .INIT(8'h02)) 
    \Add1_out1_1[6]_i_1__0 
       (.I0(Q[6]),
        .I1(Saturation1_out110_in),
        .I2(Q[13]),
        .O(Saturation1_out1[6]));
  (* SOFT_HLUTNM = "soft_lutpair35" *) 
  LUT3 #(
    .INIT(8'h02)) 
    \Add1_out1_1[7]_i_1__0 
       (.I0(Q[7]),
        .I1(Saturation1_out110_in),
        .I2(Q[13]),
        .O(Saturation1_out1[7]));
  (* SOFT_HLUTNM = "soft_lutpair36" *) 
  LUT3 #(
    .INIT(8'h02)) 
    \Add1_out1_1[8]_i_1__0 
       (.I0(Q[8]),
        .I1(Saturation1_out110_in),
        .I2(Q[13]),
        .O(Saturation1_out1[8]));
  (* SOFT_HLUTNM = "soft_lutpair36" *) 
  LUT3 #(
    .INIT(8'h02)) 
    \Add1_out1_1[9]_i_1__0 
       (.I0(Q[9]),
        .I1(Saturation1_out110_in),
        .I2(Q[13]),
        .O(Saturation1_out1[9]));
  FDRE \Add1_out1_1_reg[0] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Saturation1_out1[0]),
        .Q(Add1_out1_1[0]),
        .R(RSTP));
  FDRE \Add1_out1_1_reg[10] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Saturation1_out1[10]),
        .Q(Add1_out1_1[10]),
        .R(RSTP));
  FDRE \Add1_out1_1_reg[11] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Add1_out1[11]),
        .Q(Add1_out1_1[11]),
        .R(RSTP));
  FDRE \Add1_out1_1_reg[12] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Add1_out1[12]),
        .Q(Add1_out1_1[12]),
        .R(RSTP));
  FDRE \Add1_out1_1_reg[13] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Add1_out1[13]),
        .Q(Add1_out1_1[13]),
        .R(RSTP));
  (* ADDER_THRESHOLD = "35" *) 
  CARRY8 \Add1_out1_1_reg[13]_i_1__0 
       (.CI(1'b0),
        .CI_TOP(1'b0),
        .CO({\NLW_Add1_out1_1_reg[13]_i_1__0_CO_UNCONNECTED [7:2],\Add1_out1_1_reg[13]_i_1__0_n_6 ,\Add1_out1_1_reg[13]_i_1__0_n_7 }),
        .DI({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,\Add1_out1_1[13]_i_2__0_n_0 ,1'b0}),
        .O({\NLW_Add1_out1_1_reg[13]_i_1__0_O_UNCONNECTED [7:3],Add1_out1}),
        .S({1'b0,1'b0,1'b0,1'b0,1'b0,1'b1,\Add1_out1_1[13]_i_3__0_n_0 ,\Add1_out1_1[13]_i_4__0_n_0 }));
  FDRE \Add1_out1_1_reg[1] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Saturation1_out1[1]),
        .Q(Add1_out1_1[1]),
        .R(RSTP));
  FDRE \Add1_out1_1_reg[2] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Saturation1_out1[2]),
        .Q(Add1_out1_1[2]),
        .R(RSTP));
  FDRE \Add1_out1_1_reg[3] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Saturation1_out1[3]),
        .Q(Add1_out1_1[3]),
        .R(RSTP));
  FDRE \Add1_out1_1_reg[4] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Saturation1_out1[4]),
        .Q(Add1_out1_1[4]),
        .R(RSTP));
  FDRE \Add1_out1_1_reg[5] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Saturation1_out1[5]),
        .Q(Add1_out1_1[5]),
        .R(RSTP));
  FDRE \Add1_out1_1_reg[6] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Saturation1_out1[6]),
        .Q(Add1_out1_1[6]),
        .R(RSTP));
  FDRE \Add1_out1_1_reg[7] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Saturation1_out1[7]),
        .Q(Add1_out1_1[7]),
        .R(RSTP));
  FDRE \Add1_out1_1_reg[8] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Saturation1_out1[8]),
        .Q(Add1_out1_1[8]),
        .R(RSTP));
  FDRE \Add1_out1_1_reg[9] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Saturation1_out1[9]),
        .Q(Add1_out1_1[9]),
        .R(RSTP));
  LUT3 #(
    .INIT(8'hBA)) 
    \Add2_out1_1[13]_i_2__0 
       (.I0(Saturation1_out110_in),
        .I1(Q[13]),
        .I2(Q[12]),
        .O(\Add2_out1_1[13]_i_2__0_n_0 ));
  LUT3 #(
    .INIT(8'hEF)) 
    \Add2_out1_1[13]_i_3__0 
       (.I0(Q[13]),
        .I1(Saturation1_out110_in),
        .I2(Q[11]),
        .O(\Add2_out1_1[13]_i_3__0_n_0 ));
  LUT3 #(
    .INIT(8'hEF)) 
    \Add2_out1_1[13]_i_4__0 
       (.I0(Q[13]),
        .I1(Saturation1_out110_in),
        .I2(Q[10]),
        .O(\Add2_out1_1[13]_i_4__0_n_0 ));
  LUT3 #(
    .INIT(8'hEF)) 
    \Add2_out1_1[13]_i_5__0 
       (.I0(Q[13]),
        .I1(Saturation1_out110_in),
        .I2(Q[9]),
        .O(\Add2_out1_1[13]_i_5__0_n_0 ));
  LUT3 #(
    .INIT(8'hEF)) 
    \Add2_out1_1[8]_i_10__0 
       (.I0(Q[13]),
        .I1(Saturation1_out110_in),
        .I2(Q[1]),
        .O(\Add2_out1_1[8]_i_10__0_n_0 ));
  LUT3 #(
    .INIT(8'hEF)) 
    \Add2_out1_1[8]_i_2__0 
       (.I0(Q[13]),
        .I1(Saturation1_out110_in),
        .I2(Q[0]),
        .O(\Add2_out1_1[8]_i_2__0_n_0 ));
  LUT3 #(
    .INIT(8'hEF)) 
    \Add2_out1_1[8]_i_3__0 
       (.I0(Q[13]),
        .I1(Saturation1_out110_in),
        .I2(Q[8]),
        .O(\Add2_out1_1[8]_i_3__0_n_0 ));
  LUT3 #(
    .INIT(8'hEF)) 
    \Add2_out1_1[8]_i_4__0 
       (.I0(Q[13]),
        .I1(Saturation1_out110_in),
        .I2(Q[7]),
        .O(\Add2_out1_1[8]_i_4__0_n_0 ));
  LUT3 #(
    .INIT(8'hEF)) 
    \Add2_out1_1[8]_i_5__0 
       (.I0(Q[13]),
        .I1(Saturation1_out110_in),
        .I2(Q[6]),
        .O(\Add2_out1_1[8]_i_5__0_n_0 ));
  LUT3 #(
    .INIT(8'hEF)) 
    \Add2_out1_1[8]_i_6__0 
       (.I0(Q[13]),
        .I1(Saturation1_out110_in),
        .I2(Q[5]),
        .O(\Add2_out1_1[8]_i_6__0_n_0 ));
  LUT3 #(
    .INIT(8'hEF)) 
    \Add2_out1_1[8]_i_7__0 
       (.I0(Q[13]),
        .I1(Saturation1_out110_in),
        .I2(Q[4]),
        .O(\Add2_out1_1[8]_i_7__0_n_0 ));
  LUT3 #(
    .INIT(8'hEF)) 
    \Add2_out1_1[8]_i_8__0 
       (.I0(Q[13]),
        .I1(Saturation1_out110_in),
        .I2(Q[3]),
        .O(\Add2_out1_1[8]_i_8__0_n_0 ));
  LUT3 #(
    .INIT(8'hEF)) 
    \Add2_out1_1[8]_i_9__0 
       (.I0(Q[13]),
        .I1(Saturation1_out110_in),
        .I2(Q[2]),
        .O(\Add2_out1_1[8]_i_9__0_n_0 ));
  FDRE \Add2_out1_1_reg[10] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Add2_out1[10]),
        .Q(Add2_out1_1[10]),
        .R(RSTP));
  FDRE \Add2_out1_1_reg[11] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Add2_out1[11]),
        .Q(Add2_out1_1[11]),
        .R(RSTP));
  FDRE \Add2_out1_1_reg[12] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Add2_out1[12]),
        .Q(Add2_out1_1[12]),
        .R(RSTP));
  FDRE \Add2_out1_1_reg[13] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Add2_out1[13]),
        .Q(Add2_out1_1[13]),
        .R(RSTP));
  (* ADDER_THRESHOLD = "35" *) 
  CARRY8 \Add2_out1_1_reg[13]_i_1__0 
       (.CI(\Add2_out1_1_reg[8]_i_1__0_n_0 ),
        .CI_TOP(1'b0),
        .CO({\NLW_Add2_out1_1_reg[13]_i_1__0_CO_UNCONNECTED [7:4],\Add2_out1_1_reg[13]_i_1__0_n_4 ,\Add2_out1_1_reg[13]_i_1__0_n_5 ,\Add2_out1_1_reg[13]_i_1__0_n_6 ,\Add2_out1_1_reg[13]_i_1__0_n_7 }),
        .DI({1'b0,1'b0,1'b0,1'b0,1'b1,1'b0,1'b0,1'b0}),
        .O({\NLW_Add2_out1_1_reg[13]_i_1__0_O_UNCONNECTED [7:5],Add2_out1[13:9]}),
        .S({1'b0,1'b0,1'b0,1'b1,\Add2_out1_1[13]_i_2__0_n_0 ,\Add2_out1_1[13]_i_3__0_n_0 ,\Add2_out1_1[13]_i_4__0_n_0 ,\Add2_out1_1[13]_i_5__0_n_0 }));
  FDRE \Add2_out1_1_reg[1] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Add2_out1[1]),
        .Q(Add2_out1_1[1]),
        .R(RSTP));
  FDRE \Add2_out1_1_reg[2] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Add2_out1[2]),
        .Q(Add2_out1_1[2]),
        .R(RSTP));
  FDRE \Add2_out1_1_reg[3] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Add2_out1[3]),
        .Q(Add2_out1_1[3]),
        .R(RSTP));
  FDRE \Add2_out1_1_reg[4] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Add2_out1[4]),
        .Q(Add2_out1_1[4]),
        .R(RSTP));
  FDRE \Add2_out1_1_reg[5] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Add2_out1[5]),
        .Q(Add2_out1_1[5]),
        .R(RSTP));
  FDRE \Add2_out1_1_reg[6] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Add2_out1[6]),
        .Q(Add2_out1_1[6]),
        .R(RSTP));
  FDRE \Add2_out1_1_reg[7] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Add2_out1[7]),
        .Q(Add2_out1_1[7]),
        .R(RSTP));
  FDRE \Add2_out1_1_reg[8] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Add2_out1[8]),
        .Q(Add2_out1_1[8]),
        .R(RSTP));
  (* ADDER_THRESHOLD = "35" *) 
  CARRY8 \Add2_out1_1_reg[8]_i_1__0 
       (.CI(\Add2_out1_1[8]_i_2__0_n_0 ),
        .CI_TOP(1'b0),
        .CO({\Add2_out1_1_reg[8]_i_1__0_n_0 ,\Add2_out1_1_reg[8]_i_1__0_n_1 ,\Add2_out1_1_reg[8]_i_1__0_n_2 ,\Add2_out1_1_reg[8]_i_1__0_n_3 ,\Add2_out1_1_reg[8]_i_1__0_n_4 ,\Add2_out1_1_reg[8]_i_1__0_n_5 ,\Add2_out1_1_reg[8]_i_1__0_n_6 ,\Add2_out1_1_reg[8]_i_1__0_n_7 }),
        .DI({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .O(Add2_out1[8:1]),
        .S({\Add2_out1_1[8]_i_3__0_n_0 ,\Add2_out1_1[8]_i_4__0_n_0 ,\Add2_out1_1[8]_i_5__0_n_0 ,\Add2_out1_1[8]_i_6__0_n_0 ,\Add2_out1_1[8]_i_7__0_n_0 ,\Add2_out1_1[8]_i_8__0_n_0 ,\Add2_out1_1[8]_i_9__0_n_0 ,\Add2_out1_1[8]_i_10__0_n_0 }));
  FDRE \Add2_out1_1_reg[9] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Add2_out1[9]),
        .Q(Add2_out1_1[9]),
        .R(RSTP));
  LUT6 #(
    .INIT(64'hAAAAFFBFAAAA0080)) 
    \Delay1_out1[11]_i_1 
       (.I0(\Delay1_out1_reg[13]_0 [11]),
        .I1(\Delay1_out1_reg[13]_1 ),
        .I2(D),
        .I3(HDL_Counter2_count_reg),
        .I4(CO),
        .I5(\Delay1_out1_reg[13] [11]),
        .O(\delayMatch3_reg_reg[1][11] ));
  LUT6 #(
    .INIT(64'hAAAAFFBFAAAA0080)) 
    \Delay1_out1[13]_i_1 
       (.I0(\Delay1_out1_reg[13]_0 [13]),
        .I1(\Delay1_out1_reg[13]_1 ),
        .I2(D),
        .I3(HDL_Counter2_count_reg),
        .I4(CO),
        .I5(\Delay1_out1_reg[13] [13]),
        .O(\delayMatch3_reg_reg[1][13] ));
  LUT6 #(
    .INIT(64'hAAAAFFBFAAAA0080)) 
    \Delay1_out1[1]_i_1 
       (.I0(\Delay1_out1_reg[13]_0 [1]),
        .I1(\Delay1_out1_reg[13]_1 ),
        .I2(D),
        .I3(HDL_Counter2_count_reg),
        .I4(CO),
        .I5(\Delay1_out1_reg[13] [1]),
        .O(\delayMatch3_reg_reg[1][1] ));
  LUT6 #(
    .INIT(64'hAAAAFFBFAAAA0080)) 
    \Delay1_out1[3]_i_1 
       (.I0(\Delay1_out1_reg[13]_0 [3]),
        .I1(\Delay1_out1_reg[13]_1 ),
        .I2(D),
        .I3(HDL_Counter2_count_reg),
        .I4(CO),
        .I5(\Delay1_out1_reg[13] [3]),
        .O(\delayMatch3_reg_reg[1][3] ));
  LUT6 #(
    .INIT(64'hAAAAFFBFAAAA0080)) 
    \Delay1_out1[5]_i_1 
       (.I0(\Delay1_out1_reg[13]_0 [5]),
        .I1(\Delay1_out1_reg[13]_1 ),
        .I2(D),
        .I3(HDL_Counter2_count_reg),
        .I4(CO),
        .I5(\Delay1_out1_reg[13] [5]),
        .O(\delayMatch3_reg_reg[1][5] ));
  LUT6 #(
    .INIT(64'hAAAAFFBFAAAA0080)) 
    \Delay1_out1[7]_i_1 
       (.I0(\Delay1_out1_reg[13]_0 [7]),
        .I1(\Delay1_out1_reg[13]_1 ),
        .I2(D),
        .I3(HDL_Counter2_count_reg),
        .I4(CO),
        .I5(\Delay1_out1_reg[13] [7]),
        .O(\delayMatch3_reg_reg[1][7] ));
  LUT6 #(
    .INIT(64'hAAAAFFBFAAAA0080)) 
    \Delay1_out1[9]_i_1 
       (.I0(\Delay1_out1_reg[13]_0 [9]),
        .I1(\Delay1_out1_reg[13]_1 ),
        .I2(D),
        .I3(HDL_Counter2_count_reg),
        .I4(CO),
        .I5(\Delay1_out1_reg[13] [9]),
        .O(\delayMatch3_reg_reg[1][9] ));
  (* COMPARATOR_THRESHOLD = "11" *) 
  CARRY8 Logical_Operator1_out10_carry
       (.CI(1'b0),
        .CI_TOP(1'b0),
        .CO({NLW_Logical_Operator1_out10_carry_CO_UNCONNECTED[7],Relational_Operator_relop1,Logical_Operator1_out10_carry_n_2,Logical_Operator1_out10_carry_n_3,Logical_Operator1_out10_carry_n_4,Logical_Operator1_out10_carry_n_5,Logical_Operator1_out10_carry_n_6,Logical_Operator1_out10_carry_n_7}),
        .DI({1'b0,Logical_Operator1_out10_carry_i_1__0_n_0,Logical_Operator1_out10_carry_i_2__0_n_0,Logical_Operator1_out10_carry_i_3__0_n_0,Logical_Operator1_out10_carry_i_4__0_n_0,Logical_Operator1_out10_carry_i_5__0_n_0,Logical_Operator1_out10_carry_i_6__0_n_0,Logical_Operator1_out10_carry_i_7__0_n_0}),
        .O(NLW_Logical_Operator1_out10_carry_O_UNCONNECTED[7:0]),
        .S({1'b0,Logical_Operator1_out10_carry_i_8__0_n_0,Logical_Operator1_out10_carry_i_9__0_n_0,Logical_Operator1_out10_carry_i_10__0_n_0,Logical_Operator1_out10_carry_i_11__0_n_0,Logical_Operator1_out10_carry_i_12__0_n_0,Logical_Operator1_out10_carry_i_13__0_n_0,Logical_Operator1_out10_carry_i_14__0_n_0}));
  LUT6 #(
    .INIT(64'hA95900000000A959)) 
    Logical_Operator1_out10_carry_i_10__0
       (.I0(minus_out1_1[8]),
        .I1(\Delay1_out1_reg[13] [8]),
        .I2(PWM_en_AXI_2_reg),
        .I3(\Delay1_out1_reg[13]_0 [8]),
        .I4(\delayMatch3_reg_reg[1][9] ),
        .I5(minus_out1_1[9]),
        .O(Logical_Operator1_out10_carry_i_10__0_n_0));
  LUT6 #(
    .INIT(64'hA95900000000A959)) 
    Logical_Operator1_out10_carry_i_11__0
       (.I0(minus_out1_1[6]),
        .I1(\Delay1_out1_reg[13] [6]),
        .I2(PWM_en_AXI_2_reg),
        .I3(\Delay1_out1_reg[13]_0 [6]),
        .I4(\delayMatch3_reg_reg[1][7] ),
        .I5(minus_out1_1[7]),
        .O(Logical_Operator1_out10_carry_i_11__0_n_0));
  LUT6 #(
    .INIT(64'hA95900000000A959)) 
    Logical_Operator1_out10_carry_i_12__0
       (.I0(minus_out1_1[4]),
        .I1(\Delay1_out1_reg[13] [4]),
        .I2(PWM_en_AXI_2_reg),
        .I3(\Delay1_out1_reg[13]_0 [4]),
        .I4(\delayMatch3_reg_reg[1][5] ),
        .I5(minus_out1_1[5]),
        .O(Logical_Operator1_out10_carry_i_12__0_n_0));
  LUT6 #(
    .INIT(64'hA95900000000A959)) 
    Logical_Operator1_out10_carry_i_13__0
       (.I0(minus_out1_1[2]),
        .I1(\Delay1_out1_reg[13] [2]),
        .I2(PWM_en_AXI_2_reg),
        .I3(\Delay1_out1_reg[13]_0 [2]),
        .I4(\delayMatch3_reg_reg[1][3] ),
        .I5(minus_out1_1[3]),
        .O(Logical_Operator1_out10_carry_i_13__0_n_0));
  LUT6 #(
    .INIT(64'hE21D00000000E21D)) 
    Logical_Operator1_out10_carry_i_14__0
       (.I0(\Delay1_out1_reg[13] [0]),
        .I1(PWM_en_AXI_2_reg),
        .I2(\Delay1_out1_reg[13]_0 [0]),
        .I3(Add1_out1_1[0]),
        .I4(\delayMatch3_reg_reg[1][1] ),
        .I5(minus_out1_1[1]),
        .O(Logical_Operator1_out10_carry_i_14__0_n_0));
  LUT6 #(
    .INIT(64'h22222222BBB222B2)) 
    Logical_Operator1_out10_carry_i_1__0
       (.I0(minus_out1_1[13]),
        .I1(\delayMatch3_reg_reg[1][13] ),
        .I2(\Delay1_out1_reg[13] [12]),
        .I3(PWM_en_AXI_2_reg),
        .I4(\Delay1_out1_reg[13]_0 [12]),
        .I5(minus_out1_1[12]),
        .O(Logical_Operator1_out10_carry_i_1__0_n_0));
  LUT6 #(
    .INIT(64'h22222222BBB222B2)) 
    Logical_Operator1_out10_carry_i_2__0
       (.I0(\delayMatch3_reg_reg[1][11] ),
        .I1(minus_out1_1[11]),
        .I2(\Delay1_out1_reg[13] [10]),
        .I3(PWM_en_AXI_2_reg),
        .I4(\Delay1_out1_reg[13]_0 [10]),
        .I5(minus_out1_1[10]),
        .O(Logical_Operator1_out10_carry_i_2__0_n_0));
  LUT6 #(
    .INIT(64'h22222222BBB222B2)) 
    Logical_Operator1_out10_carry_i_3__0
       (.I0(\delayMatch3_reg_reg[1][9] ),
        .I1(minus_out1_1[9]),
        .I2(\Delay1_out1_reg[13] [8]),
        .I3(PWM_en_AXI_2_reg),
        .I4(\Delay1_out1_reg[13]_0 [8]),
        .I5(minus_out1_1[8]),
        .O(Logical_Operator1_out10_carry_i_3__0_n_0));
  LUT6 #(
    .INIT(64'h22222222BBB222B2)) 
    Logical_Operator1_out10_carry_i_4__0
       (.I0(\delayMatch3_reg_reg[1][7] ),
        .I1(minus_out1_1[7]),
        .I2(\Delay1_out1_reg[13] [6]),
        .I3(PWM_en_AXI_2_reg),
        .I4(\Delay1_out1_reg[13]_0 [6]),
        .I5(minus_out1_1[6]),
        .O(Logical_Operator1_out10_carry_i_4__0_n_0));
  LUT6 #(
    .INIT(64'h22222222BBB222B2)) 
    Logical_Operator1_out10_carry_i_5__0
       (.I0(\delayMatch3_reg_reg[1][5] ),
        .I1(minus_out1_1[5]),
        .I2(\Delay1_out1_reg[13] [4]),
        .I3(PWM_en_AXI_2_reg),
        .I4(\Delay1_out1_reg[13]_0 [4]),
        .I5(minus_out1_1[4]),
        .O(Logical_Operator1_out10_carry_i_5__0_n_0));
  LUT6 #(
    .INIT(64'h22222222BBB222B2)) 
    Logical_Operator1_out10_carry_i_6__0
       (.I0(\delayMatch3_reg_reg[1][3] ),
        .I1(minus_out1_1[3]),
        .I2(\Delay1_out1_reg[13] [2]),
        .I3(PWM_en_AXI_2_reg),
        .I4(\Delay1_out1_reg[13]_0 [2]),
        .I5(minus_out1_1[2]),
        .O(Logical_Operator1_out10_carry_i_6__0_n_0));
  LUT6 #(
    .INIT(64'h7577755510111000)) 
    Logical_Operator1_out10_carry_i_7__0
       (.I0(minus_out1_1[1]),
        .I1(Add1_out1_1[0]),
        .I2(\Delay1_out1_reg[13]_0 [0]),
        .I3(PWM_en_AXI_2_reg),
        .I4(\Delay1_out1_reg[13] [0]),
        .I5(\delayMatch3_reg_reg[1][1] ),
        .O(Logical_Operator1_out10_carry_i_7__0_n_0));
  LUT6 #(
    .INIT(64'hA95900000000A959)) 
    Logical_Operator1_out10_carry_i_8__0
       (.I0(minus_out1_1[12]),
        .I1(\Delay1_out1_reg[13] [12]),
        .I2(PWM_en_AXI_2_reg),
        .I3(\Delay1_out1_reg[13]_0 [12]),
        .I4(\delayMatch3_reg_reg[1][13] ),
        .I5(minus_out1_1[13]),
        .O(Logical_Operator1_out10_carry_i_8__0_n_0));
  LUT6 #(
    .INIT(64'hA95900000000A959)) 
    Logical_Operator1_out10_carry_i_9__0
       (.I0(minus_out1_1[10]),
        .I1(\Delay1_out1_reg[13] [10]),
        .I2(PWM_en_AXI_2_reg),
        .I3(\Delay1_out1_reg[13]_0 [10]),
        .I4(\delayMatch3_reg_reg[1][11] ),
        .I5(minus_out1_1[11]),
        .O(Logical_Operator1_out10_carry_i_9__0_n_0));
  (* COMPARATOR_THRESHOLD = "11" *) 
  CARRY8 \Logical_Operator1_out10_inferred__0/i__carry 
       (.CI(1'b0),
        .CI_TOP(1'b0),
        .CO({\NLW_Logical_Operator1_out10_inferred__0/i__carry_CO_UNCONNECTED [7],Relational_Operator1_relop1,\Logical_Operator1_out10_inferred__0/i__carry_n_2 ,\Logical_Operator1_out10_inferred__0/i__carry_n_3 ,\Logical_Operator1_out10_inferred__0/i__carry_n_4 ,\Logical_Operator1_out10_inferred__0/i__carry_n_5 ,\Logical_Operator1_out10_inferred__0/i__carry_n_6 ,\Logical_Operator1_out10_inferred__0/i__carry_n_7 }),
        .DI({1'b0,i__carry_i_1__0_n_0,i__carry_i_2__0_n_0,i__carry_i_3__0_n_0,i__carry_i_4__0_n_0,i__carry_i_5__0_n_0,i__carry_i_6__0_n_0,i__carry_i_7__0_n_0}),
        .O(\NLW_Logical_Operator1_out10_inferred__0/i__carry_O_UNCONNECTED [7:0]),
        .S({1'b0,i__carry_i_8__0_n_0,i__carry_i_9__0_n_0,i__carry_i_10__0_n_0,i__carry_i_11__0_n_0,i__carry_i_12__0_n_0,i__carry_i_13__0_n_0,i__carry_i_14__0_n_0}));
  (* COMPARATOR_THRESHOLD = "11" *) 
  CARRY8 Logical_Operator_out10_carry
       (.CI(1'b0),
        .CI_TOP(1'b0),
        .CO({NLW_Logical_Operator_out10_carry_CO_UNCONNECTED[7],Relational_Operator3_relop1,Logical_Operator_out10_carry_n_2,Logical_Operator_out10_carry_n_3,Logical_Operator_out10_carry_n_4,Logical_Operator_out10_carry_n_5,Logical_Operator_out10_carry_n_6,Logical_Operator_out10_carry_n_7}),
        .DI({1'b0,Logical_Operator_out10_carry_i_1__0_n_0,Logical_Operator_out10_carry_i_2__0_n_0,Logical_Operator_out10_carry_i_3__0_n_0,Logical_Operator_out10_carry_i_4__0_n_0,Logical_Operator_out10_carry_i_5__0_n_0,Logical_Operator_out10_carry_i_6__0_n_0,Logical_Operator_out10_carry_i_7__0_n_0}),
        .O(NLW_Logical_Operator_out10_carry_O_UNCONNECTED[7:0]),
        .S({1'b0,Logical_Operator_out10_carry_i_8__0_n_0,Logical_Operator_out10_carry_i_9__0_n_0,Logical_Operator_out10_carry_i_10__0_n_0,Logical_Operator_out10_carry_i_11__0_n_0,Logical_Operator_out10_carry_i_12__0_n_0,Logical_Operator_out10_carry_i_13__0_n_0,Logical_Operator_out10_carry_i_14__0_n_0}));
  LUT6 #(
    .INIT(64'hA95900000000A959)) 
    Logical_Operator_out10_carry_i_10__0
       (.I0(Add2_out1_1[8]),
        .I1(\Delay1_out1_reg[13] [8]),
        .I2(PWM_en_AXI_2_reg),
        .I3(\Delay1_out1_reg[13]_0 [8]),
        .I4(\delayMatch3_reg_reg[1][9] ),
        .I5(Add2_out1_1[9]),
        .O(Logical_Operator_out10_carry_i_10__0_n_0));
  LUT6 #(
    .INIT(64'hA95900000000A959)) 
    Logical_Operator_out10_carry_i_11__0
       (.I0(Add2_out1_1[6]),
        .I1(\Delay1_out1_reg[13] [6]),
        .I2(PWM_en_AXI_2_reg),
        .I3(\Delay1_out1_reg[13]_0 [6]),
        .I4(\delayMatch3_reg_reg[1][7] ),
        .I5(Add2_out1_1[7]),
        .O(Logical_Operator_out10_carry_i_11__0_n_0));
  LUT6 #(
    .INIT(64'hA95900000000A959)) 
    Logical_Operator_out10_carry_i_12__0
       (.I0(Add2_out1_1[4]),
        .I1(\Delay1_out1_reg[13] [4]),
        .I2(PWM_en_AXI_2_reg),
        .I3(\Delay1_out1_reg[13]_0 [4]),
        .I4(\delayMatch3_reg_reg[1][5] ),
        .I5(Add2_out1_1[5]),
        .O(Logical_Operator_out10_carry_i_12__0_n_0));
  LUT6 #(
    .INIT(64'hA95900000000A959)) 
    Logical_Operator_out10_carry_i_13__0
       (.I0(Add2_out1_1[2]),
        .I1(\Delay1_out1_reg[13] [2]),
        .I2(PWM_en_AXI_2_reg),
        .I3(\Delay1_out1_reg[13]_0 [2]),
        .I4(\delayMatch3_reg_reg[1][3] ),
        .I5(Add2_out1_1[3]),
        .O(Logical_Operator_out10_carry_i_13__0_n_0));
  LUT6 #(
    .INIT(64'hE21D00000000E21D)) 
    Logical_Operator_out10_carry_i_14__0
       (.I0(\Delay1_out1_reg[13] [0]),
        .I1(PWM_en_AXI_2_reg),
        .I2(\Delay1_out1_reg[13]_0 [0]),
        .I3(Add1_out1_1[0]),
        .I4(\delayMatch3_reg_reg[1][1] ),
        .I5(Add2_out1_1[1]),
        .O(Logical_Operator_out10_carry_i_14__0_n_0));
  LUT6 #(
    .INIT(64'h22222222BBB222B2)) 
    Logical_Operator_out10_carry_i_1__0
       (.I0(Add2_out1_1[13]),
        .I1(\delayMatch3_reg_reg[1][13] ),
        .I2(\Delay1_out1_reg[13] [12]),
        .I3(PWM_en_AXI_2_reg),
        .I4(\Delay1_out1_reg[13]_0 [12]),
        .I5(Add2_out1_1[12]),
        .O(Logical_Operator_out10_carry_i_1__0_n_0));
  LUT6 #(
    .INIT(64'h22222222BBB222B2)) 
    Logical_Operator_out10_carry_i_2__0
       (.I0(\delayMatch3_reg_reg[1][11] ),
        .I1(Add2_out1_1[11]),
        .I2(\Delay1_out1_reg[13] [10]),
        .I3(PWM_en_AXI_2_reg),
        .I4(\Delay1_out1_reg[13]_0 [10]),
        .I5(Add2_out1_1[10]),
        .O(Logical_Operator_out10_carry_i_2__0_n_0));
  LUT6 #(
    .INIT(64'h22222222BBB222B2)) 
    Logical_Operator_out10_carry_i_3__0
       (.I0(\delayMatch3_reg_reg[1][9] ),
        .I1(Add2_out1_1[9]),
        .I2(\Delay1_out1_reg[13] [8]),
        .I3(PWM_en_AXI_2_reg),
        .I4(\Delay1_out1_reg[13]_0 [8]),
        .I5(Add2_out1_1[8]),
        .O(Logical_Operator_out10_carry_i_3__0_n_0));
  LUT6 #(
    .INIT(64'h22222222BBB222B2)) 
    Logical_Operator_out10_carry_i_4__0
       (.I0(\delayMatch3_reg_reg[1][7] ),
        .I1(Add2_out1_1[7]),
        .I2(\Delay1_out1_reg[13] [6]),
        .I3(PWM_en_AXI_2_reg),
        .I4(\Delay1_out1_reg[13]_0 [6]),
        .I5(Add2_out1_1[6]),
        .O(Logical_Operator_out10_carry_i_4__0_n_0));
  LUT6 #(
    .INIT(64'h22222222BBB222B2)) 
    Logical_Operator_out10_carry_i_5__0
       (.I0(\delayMatch3_reg_reg[1][5] ),
        .I1(Add2_out1_1[5]),
        .I2(\Delay1_out1_reg[13] [4]),
        .I3(PWM_en_AXI_2_reg),
        .I4(\Delay1_out1_reg[13]_0 [4]),
        .I5(Add2_out1_1[4]),
        .O(Logical_Operator_out10_carry_i_5__0_n_0));
  LUT6 #(
    .INIT(64'h22222222BBB222B2)) 
    Logical_Operator_out10_carry_i_6__0
       (.I0(\delayMatch3_reg_reg[1][3] ),
        .I1(Add2_out1_1[3]),
        .I2(\Delay1_out1_reg[13] [2]),
        .I3(PWM_en_AXI_2_reg),
        .I4(\Delay1_out1_reg[13]_0 [2]),
        .I5(Add2_out1_1[2]),
        .O(Logical_Operator_out10_carry_i_6__0_n_0));
  LUT6 #(
    .INIT(64'h7577755510111000)) 
    Logical_Operator_out10_carry_i_7__0
       (.I0(Add2_out1_1[1]),
        .I1(Add1_out1_1[0]),
        .I2(\Delay1_out1_reg[13]_0 [0]),
        .I3(PWM_en_AXI_2_reg),
        .I4(\Delay1_out1_reg[13] [0]),
        .I5(\delayMatch3_reg_reg[1][1] ),
        .O(Logical_Operator_out10_carry_i_7__0_n_0));
  LUT6 #(
    .INIT(64'hA95900000000A959)) 
    Logical_Operator_out10_carry_i_8__0
       (.I0(Add2_out1_1[12]),
        .I1(\Delay1_out1_reg[13] [12]),
        .I2(PWM_en_AXI_2_reg),
        .I3(\Delay1_out1_reg[13]_0 [12]),
        .I4(\delayMatch3_reg_reg[1][13] ),
        .I5(Add2_out1_1[13]),
        .O(Logical_Operator_out10_carry_i_8__0_n_0));
  LUT6 #(
    .INIT(64'hA95900000000A959)) 
    Logical_Operator_out10_carry_i_9__0
       (.I0(Add2_out1_1[10]),
        .I1(\Delay1_out1_reg[13] [10]),
        .I2(PWM_en_AXI_2_reg),
        .I3(\Delay1_out1_reg[13]_0 [10]),
        .I4(\delayMatch3_reg_reg[1][11] ),
        .I5(Add2_out1_1[11]),
        .O(Logical_Operator_out10_carry_i_9__0_n_0));
  (* COMPARATOR_THRESHOLD = "11" *) 
  CARRY8 Logical_Operator_out11_carry
       (.CI(1'b0),
        .CI_TOP(1'b0),
        .CO({NLW_Logical_Operator_out11_carry_CO_UNCONNECTED[7],Relational_Operator2_relop1,Logical_Operator_out11_carry_n_2,Logical_Operator_out11_carry_n_3,Logical_Operator_out11_carry_n_4,Logical_Operator_out11_carry_n_5,Logical_Operator_out11_carry_n_6,Logical_Operator_out11_carry_n_7}),
        .DI({1'b0,Logical_Operator_out11_carry_i_1__0_n_0,Logical_Operator_out11_carry_i_2__0_n_0,i__carry_i_3__0_n_0,i__carry_i_4__0_n_0,i__carry_i_5__0_n_0,i__carry_i_6__0_n_0,i__carry_i_7__0_n_0}),
        .O(NLW_Logical_Operator_out11_carry_O_UNCONNECTED[7:0]),
        .S({1'b0,Logical_Operator_out11_carry_i_3__0_n_0,Logical_Operator_out11_carry_i_4__0_n_0,Logical_Operator_out11_carry_i_5__0_n_0,Logical_Operator_out11_carry_i_6__0_n_0,Logical_Operator_out11_carry_i_7__0_n_0,Logical_Operator_out11_carry_i_8__0_n_0,Logical_Operator_out11_carry_i_9__0_n_0}));
  LUT6 #(
    .INIT(64'h222222B2B2B222B2)) 
    Logical_Operator_out11_carry_i_1__0
       (.I0(\delayMatch3_reg_reg[1][13] ),
        .I1(Add1_out1_1[13]),
        .I2(Add1_out1_1[12]),
        .I3(\Delay1_out1_reg[13] [12]),
        .I4(PWM_en_AXI_2_reg),
        .I5(\Delay1_out1_reg[13]_0 [12]),
        .O(Logical_Operator_out11_carry_i_1__0_n_0));
  LUT6 #(
    .INIT(64'h222222B2B2B222B2)) 
    Logical_Operator_out11_carry_i_2__0
       (.I0(Add1_out1_1[11]),
        .I1(\delayMatch3_reg_reg[1][11] ),
        .I2(Add1_out1_1[10]),
        .I3(\Delay1_out1_reg[13] [10]),
        .I4(PWM_en_AXI_2_reg),
        .I5(\Delay1_out1_reg[13]_0 [10]),
        .O(Logical_Operator_out11_carry_i_2__0_n_0));
  LUT6 #(
    .INIT(64'hA95900000000A959)) 
    Logical_Operator_out11_carry_i_3__0
       (.I0(Add1_out1_1[12]),
        .I1(\Delay1_out1_reg[13] [12]),
        .I2(PWM_en_AXI_2_reg),
        .I3(\Delay1_out1_reg[13]_0 [12]),
        .I4(\delayMatch3_reg_reg[1][13] ),
        .I5(Add1_out1_1[13]),
        .O(Logical_Operator_out11_carry_i_3__0_n_0));
  LUT6 #(
    .INIT(64'hA95900000000A959)) 
    Logical_Operator_out11_carry_i_4__0
       (.I0(Add1_out1_1[10]),
        .I1(\Delay1_out1_reg[13] [10]),
        .I2(PWM_en_AXI_2_reg),
        .I3(\Delay1_out1_reg[13]_0 [10]),
        .I4(\delayMatch3_reg_reg[1][11] ),
        .I5(Add1_out1_1[11]),
        .O(Logical_Operator_out11_carry_i_4__0_n_0));
  LUT6 #(
    .INIT(64'hA95900000000A959)) 
    Logical_Operator_out11_carry_i_5__0
       (.I0(Add1_out1_1[8]),
        .I1(\Delay1_out1_reg[13] [8]),
        .I2(PWM_en_AXI_2_reg),
        .I3(\Delay1_out1_reg[13]_0 [8]),
        .I4(\delayMatch3_reg_reg[1][9] ),
        .I5(Add1_out1_1[9]),
        .O(Logical_Operator_out11_carry_i_5__0_n_0));
  LUT6 #(
    .INIT(64'hA95900000000A959)) 
    Logical_Operator_out11_carry_i_6__0
       (.I0(Add1_out1_1[6]),
        .I1(\Delay1_out1_reg[13] [6]),
        .I2(PWM_en_AXI_2_reg),
        .I3(\Delay1_out1_reg[13]_0 [6]),
        .I4(\delayMatch3_reg_reg[1][7] ),
        .I5(Add1_out1_1[7]),
        .O(Logical_Operator_out11_carry_i_6__0_n_0));
  LUT6 #(
    .INIT(64'hA95900000000A959)) 
    Logical_Operator_out11_carry_i_7__0
       (.I0(Add1_out1_1[4]),
        .I1(\Delay1_out1_reg[13] [4]),
        .I2(PWM_en_AXI_2_reg),
        .I3(\Delay1_out1_reg[13]_0 [4]),
        .I4(\delayMatch3_reg_reg[1][5] ),
        .I5(Add1_out1_1[5]),
        .O(Logical_Operator_out11_carry_i_7__0_n_0));
  LUT6 #(
    .INIT(64'hA95900000000A959)) 
    Logical_Operator_out11_carry_i_8__0
       (.I0(Add1_out1_1[2]),
        .I1(\Delay1_out1_reg[13] [2]),
        .I2(PWM_en_AXI_2_reg),
        .I3(\Delay1_out1_reg[13]_0 [2]),
        .I4(\delayMatch3_reg_reg[1][3] ),
        .I5(Add1_out1_1[3]),
        .O(Logical_Operator_out11_carry_i_8__0_n_0));
  LUT6 #(
    .INIT(64'hE21D00000000E21D)) 
    Logical_Operator_out11_carry_i_9__0
       (.I0(\Delay1_out1_reg[13] [0]),
        .I1(PWM_en_AXI_2_reg),
        .I2(\Delay1_out1_reg[13]_0 [0]),
        .I3(Add1_out1_1[0]),
        .I4(\delayMatch3_reg_reg[1][1] ),
        .I5(Add1_out1_1[1]),
        .O(Logical_Operator_out11_carry_i_9__0_n_0));
  (* SOFT_HLUTNM = "soft_lutpair37" *) 
  LUT3 #(
    .INIT(8'h02)) 
    \Saturation1_out1_1[11]_i_1__0 
       (.I0(Q[11]),
        .I1(Saturation1_out110_in),
        .I2(Q[13]),
        .O(Saturation1_out1[11]));
  (* SOFT_HLUTNM = "soft_lutpair30" *) 
  LUT3 #(
    .INIT(8'hBA)) 
    \Saturation1_out1_1[12]_i_1__0 
       (.I0(Saturation1_out110_in),
        .I1(Q[13]),
        .I2(Q[12]),
        .O(Saturation1_out1[12]));
  FDRE \Saturation1_out1_1_reg[11] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Saturation1_out1[11]),
        .Q(Saturation1_out1_1[11]),
        .R(RSTP));
  FDRE \Saturation1_out1_1_reg[12] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Saturation1_out1[12]),
        .Q(Saturation1_out1_1[12]),
        .R(RSTP));
  LUT6 #(
    .INIT(64'hA95900000000A959)) 
    i__carry_i_10__0
       (.I0(Add1_out1_1[8]),
        .I1(\Delay1_out1_reg[13] [8]),
        .I2(PWM_en_AXI_2_reg),
        .I3(\Delay1_out1_reg[13]_0 [8]),
        .I4(\delayMatch3_reg_reg[1][9] ),
        .I5(Add1_out1_1[9]),
        .O(i__carry_i_10__0_n_0));
  LUT6 #(
    .INIT(64'hA95900000000A959)) 
    i__carry_i_11__0
       (.I0(Add1_out1_1[6]),
        .I1(\Delay1_out1_reg[13] [6]),
        .I2(PWM_en_AXI_2_reg),
        .I3(\Delay1_out1_reg[13]_0 [6]),
        .I4(\delayMatch3_reg_reg[1][7] ),
        .I5(Add1_out1_1[7]),
        .O(i__carry_i_11__0_n_0));
  LUT6 #(
    .INIT(64'hA95900000000A959)) 
    i__carry_i_12__0
       (.I0(Add1_out1_1[4]),
        .I1(\Delay1_out1_reg[13] [4]),
        .I2(PWM_en_AXI_2_reg),
        .I3(\Delay1_out1_reg[13]_0 [4]),
        .I4(\delayMatch3_reg_reg[1][5] ),
        .I5(Add1_out1_1[5]),
        .O(i__carry_i_12__0_n_0));
  LUT6 #(
    .INIT(64'hA95900000000A959)) 
    i__carry_i_13__0
       (.I0(Add1_out1_1[2]),
        .I1(\Delay1_out1_reg[13] [2]),
        .I2(PWM_en_AXI_2_reg),
        .I3(\Delay1_out1_reg[13]_0 [2]),
        .I4(\delayMatch3_reg_reg[1][3] ),
        .I5(Add1_out1_1[3]),
        .O(i__carry_i_13__0_n_0));
  LUT6 #(
    .INIT(64'hE21D00000000E21D)) 
    i__carry_i_14__0
       (.I0(\Delay1_out1_reg[13] [0]),
        .I1(PWM_en_AXI_2_reg),
        .I2(\Delay1_out1_reg[13]_0 [0]),
        .I3(Add1_out1_1[0]),
        .I4(\delayMatch3_reg_reg[1][1] ),
        .I5(Add1_out1_1[1]),
        .O(i__carry_i_14__0_n_0));
  LUT5 #(
    .INIT(32'hAAAEEEAE)) 
    i__carry_i_1__0
       (.I0(\delayMatch3_reg_reg[1][13] ),
        .I1(Saturation1_out1_1[12]),
        .I2(\Delay1_out1_reg[13] [12]),
        .I3(PWM_en_AXI_2_reg),
        .I4(\Delay1_out1_reg[13]_0 [12]),
        .O(i__carry_i_1__0_n_0));
  LUT6 #(
    .INIT(64'h222222B2B2B222B2)) 
    i__carry_i_2__0
       (.I0(Saturation1_out1_1[11]),
        .I1(\delayMatch3_reg_reg[1][11] ),
        .I2(Add1_out1_1[10]),
        .I3(\Delay1_out1_reg[13] [10]),
        .I4(PWM_en_AXI_2_reg),
        .I5(\Delay1_out1_reg[13]_0 [10]),
        .O(i__carry_i_2__0_n_0));
  LUT6 #(
    .INIT(64'h222222B2B2B222B2)) 
    i__carry_i_3__0
       (.I0(Add1_out1_1[9]),
        .I1(\delayMatch3_reg_reg[1][9] ),
        .I2(Add1_out1_1[8]),
        .I3(\Delay1_out1_reg[13] [8]),
        .I4(PWM_en_AXI_2_reg),
        .I5(\Delay1_out1_reg[13]_0 [8]),
        .O(i__carry_i_3__0_n_0));
  LUT6 #(
    .INIT(64'h222222B2B2B222B2)) 
    i__carry_i_4__0
       (.I0(Add1_out1_1[7]),
        .I1(\delayMatch3_reg_reg[1][7] ),
        .I2(Add1_out1_1[6]),
        .I3(\Delay1_out1_reg[13] [6]),
        .I4(PWM_en_AXI_2_reg),
        .I5(\Delay1_out1_reg[13]_0 [6]),
        .O(i__carry_i_4__0_n_0));
  LUT6 #(
    .INIT(64'h222222B2B2B222B2)) 
    i__carry_i_5__0
       (.I0(Add1_out1_1[5]),
        .I1(\delayMatch3_reg_reg[1][5] ),
        .I2(Add1_out1_1[4]),
        .I3(\Delay1_out1_reg[13] [4]),
        .I4(PWM_en_AXI_2_reg),
        .I5(\Delay1_out1_reg[13]_0 [4]),
        .O(i__carry_i_5__0_n_0));
  LUT6 #(
    .INIT(64'h222222B2B2B222B2)) 
    i__carry_i_6__0
       (.I0(Add1_out1_1[3]),
        .I1(\delayMatch3_reg_reg[1][3] ),
        .I2(Add1_out1_1[2]),
        .I3(\Delay1_out1_reg[13] [2]),
        .I4(PWM_en_AXI_2_reg),
        .I5(\Delay1_out1_reg[13]_0 [2]),
        .O(i__carry_i_6__0_n_0));
  LUT6 #(
    .INIT(64'h222222B2B2B222B2)) 
    i__carry_i_7__0
       (.I0(Add1_out1_1[1]),
        .I1(\delayMatch3_reg_reg[1][1] ),
        .I2(Add1_out1_1[0]),
        .I3(\Delay1_out1_reg[13] [0]),
        .I4(PWM_en_AXI_2_reg),
        .I5(\Delay1_out1_reg[13]_0 [0]),
        .O(i__carry_i_7__0_n_0));
  LUT5 #(
    .INIT(32'h0000A959)) 
    i__carry_i_8__0
       (.I0(Saturation1_out1_1[12]),
        .I1(\Delay1_out1_reg[13] [12]),
        .I2(PWM_en_AXI_2_reg),
        .I3(\Delay1_out1_reg[13]_0 [12]),
        .I4(\delayMatch3_reg_reg[1][13] ),
        .O(i__carry_i_8__0_n_0));
  LUT6 #(
    .INIT(64'hA95900000000A959)) 
    i__carry_i_9__0
       (.I0(Add1_out1_1[10]),
        .I1(\Delay1_out1_reg[13] [10]),
        .I2(PWM_en_AXI_2_reg),
        .I3(\Delay1_out1_reg[13]_0 [10]),
        .I4(\delayMatch3_reg_reg[1][11] ),
        .I5(Saturation1_out1_1[11]),
        .O(i__carry_i_9__0_n_0));
  (* SOFT_HLUTNM = "soft_lutpair31" *) 
  LUT3 #(
    .INIT(8'h02)) 
    \minus_out1_1[10]_i_1__0 
       (.I0(\minus_out1_1_reg[10]_0 ),
        .I1(Saturation1_out110_in),
        .I2(Q[13]),
        .O(minus_out1[10]));
  (* SOFT_HLUTNM = "soft_lutpair32" *) 
  LUT3 #(
    .INIT(8'h02)) 
    \minus_out1_1[11]_i_1__0 
       (.I0(\minus_out1_1_reg[11]_0 ),
        .I1(Saturation1_out110_in),
        .I2(Q[13]),
        .O(minus_out1[11]));
  (* SOFT_HLUTNM = "soft_lutpair27" *) 
  LUT5 #(
    .INIT(32'hFFFF001E)) 
    \minus_out1_1[12]_i_1__0 
       (.I0(\minus_out1_1_reg[12]_0 ),
        .I1(Q[11]),
        .I2(Q[12]),
        .I3(Q[13]),
        .I4(Saturation1_out110_in),
        .O(minus_out1[12]));
  LUT2 #(
    .INIT(4'h1)) 
    \minus_out1_1[13]_i_10__1 
       (.I0(Q[10]),
        .I1(Q[11]),
        .O(\minus_out1_1[13]_i_10__1_n_0 ));
  LUT2 #(
    .INIT(4'h1)) 
    \minus_out1_1[13]_i_11__1 
       (.I0(Q[8]),
        .I1(Q[9]),
        .O(\minus_out1_1[13]_i_11__1_n_0 ));
  LUT2 #(
    .INIT(4'h1)) 
    \minus_out1_1[13]_i_12__1 
       (.I0(Q[6]),
        .I1(Q[7]),
        .O(\minus_out1_1[13]_i_12__1_n_0 ));
  LUT2 #(
    .INIT(4'h1)) 
    \minus_out1_1[13]_i_13__1 
       (.I0(Q[4]),
        .I1(Q[5]),
        .O(\minus_out1_1[13]_i_13__1_n_0 ));
  LUT2 #(
    .INIT(4'h1)) 
    \minus_out1_1[13]_i_14__1 
       (.I0(Q[2]),
        .I1(Q[3]),
        .O(\minus_out1_1[13]_i_14__1_n_0 ));
  LUT2 #(
    .INIT(4'h1)) 
    \minus_out1_1[13]_i_15__0 
       (.I0(Q[1]),
        .I1(Q[0]),
        .O(\minus_out1_1[13]_i_15__0_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair27" *) 
  LUT5 #(
    .INIT(32'hFFFF00FE)) 
    \minus_out1_1[13]_i_1__0 
       (.I0(Q[11]),
        .I1(\minus_out1_1_reg[12]_0 ),
        .I2(Q[12]),
        .I3(Q[13]),
        .I4(Saturation1_out110_in),
        .O(minus_out1[13]));
  LUT2 #(
    .INIT(4'hE)) 
    \minus_out1_1[13]_i_3__0 
       (.I0(Q[10]),
        .I1(Q[11]),
        .O(\minus_out1_1[13]_i_3__0_n_0 ));
  LUT2 #(
    .INIT(4'hE)) 
    \minus_out1_1[13]_i_4__1 
       (.I0(Q[8]),
        .I1(Q[9]),
        .O(\minus_out1_1[13]_i_4__1_n_0 ));
  LUT2 #(
    .INIT(4'hE)) 
    \minus_out1_1[13]_i_5__1 
       (.I0(Q[6]),
        .I1(Q[7]),
        .O(\minus_out1_1[13]_i_5__1_n_0 ));
  LUT2 #(
    .INIT(4'hE)) 
    \minus_out1_1[13]_i_6__1 
       (.I0(Q[4]),
        .I1(Q[5]),
        .O(\minus_out1_1[13]_i_6__1_n_0 ));
  LUT2 #(
    .INIT(4'hE)) 
    \minus_out1_1[13]_i_7__1 
       (.I0(Q[2]),
        .I1(Q[3]),
        .O(\minus_out1_1[13]_i_7__1_n_0 ));
  LUT2 #(
    .INIT(4'hE)) 
    \minus_out1_1[13]_i_8__0 
       (.I0(Q[0]),
        .I1(Q[1]),
        .O(\minus_out1_1[13]_i_8__0_n_0 ));
  LUT2 #(
    .INIT(4'h2)) 
    \minus_out1_1[13]_i_9__1 
       (.I0(Q[12]),
        .I1(Q[13]),
        .O(\minus_out1_1[13]_i_9__1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair28" *) 
  LUT4 #(
    .INIT(16'h0006)) 
    \minus_out1_1[1]_i_1__0 
       (.I0(Q[1]),
        .I1(Q[0]),
        .I2(Saturation1_out110_in),
        .I3(Q[13]),
        .O(minus_out1[1]));
  (* SOFT_HLUTNM = "soft_lutpair28" *) 
  LUT5 #(
    .INIT(32'h00000056)) 
    \minus_out1_1[2]_i_1__0 
       (.I0(Q[2]),
        .I1(Q[0]),
        .I2(Q[1]),
        .I3(Saturation1_out110_in),
        .I4(Q[13]),
        .O(minus_out1[2]));
  LUT5 #(
    .INIT(32'h00005556)) 
    \minus_out1_1[3]_i_1__0 
       (.I0(Q[3]),
        .I1(Q[1]),
        .I2(Q[0]),
        .I3(Q[2]),
        .I4(\minus_out1_1[5]_i_2__0_n_0 ),
        .O(minus_out1[3]));
  LUT6 #(
    .INIT(64'h0000000055555556)) 
    \minus_out1_1[4]_i_1__0 
       (.I0(Q[4]),
        .I1(Q[2]),
        .I2(Q[0]),
        .I3(Q[1]),
        .I4(Q[3]),
        .I5(\minus_out1_1[5]_i_2__0_n_0 ),
        .O(minus_out1[4]));
  LUT6 #(
    .INIT(64'h0000000055555556)) 
    \minus_out1_1[5]_i_1__0 
       (.I0(Q[5]),
        .I1(Q[3]),
        .I2(\minus_out1_1_reg[5]_0 ),
        .I3(Q[2]),
        .I4(Q[4]),
        .I5(\minus_out1_1[5]_i_2__0_n_0 ),
        .O(minus_out1[5]));
  LUT2 #(
    .INIT(4'hE)) 
    \minus_out1_1[5]_i_2__0 
       (.I0(Q[13]),
        .I1(Saturation1_out110_in),
        .O(\minus_out1_1[5]_i_2__0_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair30" *) 
  LUT3 #(
    .INIT(8'h02)) 
    \minus_out1_1[6]_i_1__0 
       (.I0(\minus_out1_1_reg[6]_0 ),
        .I1(Saturation1_out110_in),
        .I2(Q[13]),
        .O(minus_out1[6]));
  (* SOFT_HLUTNM = "soft_lutpair26" *) 
  LUT5 #(
    .INIT(32'h0000001E)) 
    \minus_out1_1[7]_i_1__0 
       (.I0(Q[6]),
        .I1(\minus_out1_1_reg[7]_0 ),
        .I2(Q[7]),
        .I3(Saturation1_out110_in),
        .I4(Q[13]),
        .O(minus_out1[7]));
  LUT6 #(
    .INIT(64'h00000000000001FE)) 
    \minus_out1_1[8]_i_1__0 
       (.I0(Q[7]),
        .I1(\minus_out1_1_reg[7]_0 ),
        .I2(Q[6]),
        .I3(Q[8]),
        .I4(Saturation1_out110_in),
        .I5(Q[13]),
        .O(minus_out1[8]));
  (* SOFT_HLUTNM = "soft_lutpair31" *) 
  LUT3 #(
    .INIT(8'h02)) 
    \minus_out1_1[9]_i_1__0 
       (.I0(\minus_out1_1_reg[9]_0 ),
        .I1(Saturation1_out110_in),
        .I2(Q[13]),
        .O(minus_out1[9]));
  FDRE \minus_out1_1_reg[10] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(minus_out1[10]),
        .Q(minus_out1_1[10]),
        .R(RSTP));
  FDRE \minus_out1_1_reg[11] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(minus_out1[11]),
        .Q(minus_out1_1[11]),
        .R(RSTP));
  FDRE \minus_out1_1_reg[12] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(minus_out1[12]),
        .Q(minus_out1_1[12]),
        .R(RSTP));
  FDRE \minus_out1_1_reg[13] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(minus_out1[13]),
        .Q(minus_out1_1[13]),
        .R(RSTP));
  (* COMPARATOR_THRESHOLD = "11" *) 
  CARRY8 \minus_out1_1_reg[13]_i_2 
       (.CI(1'b0),
        .CI_TOP(1'b0),
        .CO({\NLW_minus_out1_1_reg[13]_i_2_CO_UNCONNECTED [7],Saturation1_out110_in,\minus_out1_1_reg[13]_i_2_n_2 ,\minus_out1_1_reg[13]_i_2_n_3 ,\minus_out1_1_reg[13]_i_2_n_4 ,\minus_out1_1_reg[13]_i_2_n_5 ,\minus_out1_1_reg[13]_i_2_n_6 ,\minus_out1_1_reg[13]_i_2_n_7 }),
        .DI({1'b0,1'b0,\minus_out1_1[13]_i_3__0_n_0 ,\minus_out1_1[13]_i_4__1_n_0 ,\minus_out1_1[13]_i_5__1_n_0 ,\minus_out1_1[13]_i_6__1_n_0 ,\minus_out1_1[13]_i_7__1_n_0 ,\minus_out1_1[13]_i_8__0_n_0 }),
        .O(\NLW_minus_out1_1_reg[13]_i_2_O_UNCONNECTED [7:0]),
        .S({1'b0,\minus_out1_1[13]_i_9__1_n_0 ,\minus_out1_1[13]_i_10__1_n_0 ,\minus_out1_1[13]_i_11__1_n_0 ,\minus_out1_1[13]_i_12__1_n_0 ,\minus_out1_1[13]_i_13__1_n_0 ,\minus_out1_1[13]_i_14__1_n_0 ,\minus_out1_1[13]_i_15__0_n_0 }));
  FDRE \minus_out1_1_reg[1] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(minus_out1[1]),
        .Q(minus_out1_1[1]),
        .R(RSTP));
  FDRE \minus_out1_1_reg[2] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(minus_out1[2]),
        .Q(minus_out1_1[2]),
        .R(RSTP));
  FDRE \minus_out1_1_reg[3] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(minus_out1[3]),
        .Q(minus_out1_1[3]),
        .R(RSTP));
  FDRE \minus_out1_1_reg[4] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(minus_out1[4]),
        .Q(minus_out1_1[4]),
        .R(RSTP));
  FDRE \minus_out1_1_reg[5] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(minus_out1[5]),
        .Q(minus_out1_1[5]),
        .R(RSTP));
  FDRE \minus_out1_1_reg[6] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(minus_out1[6]),
        .Q(minus_out1_1[6]),
        .R(RSTP));
  FDRE \minus_out1_1_reg[7] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(minus_out1[7]),
        .Q(minus_out1_1[7]),
        .R(RSTP));
  FDRE \minus_out1_1_reg[8] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(minus_out1[8]),
        .Q(minus_out1_1[8]),
        .R(RSTP));
  FDRE \minus_out1_1_reg[9] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(minus_out1[9]),
        .Q(minus_out1_1[9]),
        .R(RSTP));
  LUT5 #(
    .INIT(32'hFFFF4540)) 
    modulating_signal_in_clock_cycles_1_reg_i_10__0
       (.I0(Logical_Operator_out1__1),
        .I1(\Delay1_out1_reg[13]_0 [4]),
        .I2(PWM_en_AXI_2_reg),
        .I3(\Delay1_out1_reg[13] [4]),
        .I4(modulating_signal_in_clock_cycles_1_reg_i_17__0_n_0),
        .O(B[4]));
  LUT5 #(
    .INIT(32'hBABBBAAA)) 
    modulating_signal_in_clock_cycles_1_reg_i_11__0
       (.I0(modulating_signal_in_clock_cycles_1_reg_i_18__0_n_0),
        .I1(Logical_Operator_out1__1),
        .I2(\Delay1_out1_reg[13]_0 [3]),
        .I3(PWM_en_AXI_2_reg),
        .I4(\Delay1_out1_reg[13] [3]),
        .O(B[3]));
  LUT5 #(
    .INIT(32'hFFFF4540)) 
    modulating_signal_in_clock_cycles_1_reg_i_12__0
       (.I0(Logical_Operator_out1__1),
        .I1(\Delay1_out1_reg[13]_0 [2]),
        .I2(PWM_en_AXI_2_reg),
        .I3(\Delay1_out1_reg[13] [2]),
        .I4(modulating_signal_in_clock_cycles_1_reg_i_17__0_n_0),
        .O(B[2]));
  LUT5 #(
    .INIT(32'hFFFF4540)) 
    modulating_signal_in_clock_cycles_1_reg_i_13__0
       (.I0(Logical_Operator_out1__1),
        .I1(\Delay1_out1_reg[13]_0 [1]),
        .I2(PWM_en_AXI_2_reg),
        .I3(\Delay1_out1_reg[13] [1]),
        .I4(modulating_signal_in_clock_cycles_1_reg_i_17__0_n_0),
        .O(B[1]));
  LUT6 #(
    .INIT(64'h00FFFFFFB8B8B8B8)) 
    modulating_signal_in_clock_cycles_1_reg_i_14__0
       (.I0(\Delay1_out1_reg[13]_0 [0]),
        .I1(PWM_en_AXI_2_reg),
        .I2(\Delay1_out1_reg[13] [0]),
        .I3(Relational_Operator1_relop1),
        .I4(Relational_Operator_relop1),
        .I5(Logical_Operator_out1__1),
        .O(B[0]));
  (* SOFT_HLUTNM = "soft_lutpair29" *) 
  LUT4 #(
    .INIT(16'hFEEE)) 
    modulating_signal_in_clock_cycles_1_reg_i_15__0
       (.I0(Relational_Operator2_relop1),
        .I1(Relational_Operator3_relop1),
        .I2(Relational_Operator_relop1),
        .I3(Relational_Operator1_relop1),
        .O(Logical_Operator_out1__1));
  LUT6 #(
    .INIT(64'hFFFFFFFF00008000)) 
    modulating_signal_in_clock_cycles_1_reg_i_16__0
       (.I0(\Delay1_out1_reg[0] ),
        .I1(\Delay1_out1_reg[0]_0 ),
        .I2(\Delay1_out1_reg[0]_1 ),
        .I3(D),
        .I4(HDL_Counter2_count_reg),
        .I5(CO),
        .O(PWM_en_AXI_2_reg));
  LUT3 #(
    .INIT(8'h70)) 
    modulating_signal_in_clock_cycles_1_reg_i_17__0
       (.I0(Relational_Operator1_relop1),
        .I1(Relational_Operator_relop1),
        .I2(Relational_Operator2_relop1),
        .O(modulating_signal_in_clock_cycles_1_reg_i_17__0_n_0));
  (* SOFT_HLUTNM = "soft_lutpair29" *) 
  LUT4 #(
    .INIT(16'h0070)) 
    modulating_signal_in_clock_cycles_1_reg_i_18__0
       (.I0(Relational_Operator1_relop1),
        .I1(Relational_Operator_relop1),
        .I2(Relational_Operator3_relop1),
        .I3(Relational_Operator2_relop1),
        .O(modulating_signal_in_clock_cycles_1_reg_i_18__0_n_0));
  LUT5 #(
    .INIT(32'hFFFF4540)) 
    modulating_signal_in_clock_cycles_1_reg_i_1__0
       (.I0(Logical_Operator_out1__1),
        .I1(\Delay1_out1_reg[13]_0 [13]),
        .I2(PWM_en_AXI_2_reg),
        .I3(\Delay1_out1_reg[13] [13]),
        .I4(modulating_signal_in_clock_cycles_1_reg_i_17__0_n_0),
        .O(B[13]));
  LUT5 #(
    .INIT(32'hBABBBAAA)) 
    modulating_signal_in_clock_cycles_1_reg_i_2__0
       (.I0(modulating_signal_in_clock_cycles_1_reg_i_18__0_n_0),
        .I1(Logical_Operator_out1__1),
        .I2(\Delay1_out1_reg[13]_0 [12]),
        .I3(PWM_en_AXI_2_reg),
        .I4(\Delay1_out1_reg[13] [12]),
        .O(B[12]));
  LUT5 #(
    .INIT(32'hFFFF4540)) 
    modulating_signal_in_clock_cycles_1_reg_i_3__0
       (.I0(Logical_Operator_out1__1),
        .I1(\Delay1_out1_reg[13]_0 [11]),
        .I2(PWM_en_AXI_2_reg),
        .I3(\Delay1_out1_reg[13] [11]),
        .I4(modulating_signal_in_clock_cycles_1_reg_i_17__0_n_0),
        .O(B[11]));
  LUT5 #(
    .INIT(32'hFFFF4540)) 
    modulating_signal_in_clock_cycles_1_reg_i_4__0
       (.I0(Logical_Operator_out1__1),
        .I1(\Delay1_out1_reg[13]_0 [10]),
        .I2(PWM_en_AXI_2_reg),
        .I3(\Delay1_out1_reg[13] [10]),
        .I4(modulating_signal_in_clock_cycles_1_reg_i_17__0_n_0),
        .O(B[10]));
  LUT5 #(
    .INIT(32'hFFFF4540)) 
    modulating_signal_in_clock_cycles_1_reg_i_5__0
       (.I0(Logical_Operator_out1__1),
        .I1(\Delay1_out1_reg[13]_0 [9]),
        .I2(PWM_en_AXI_2_reg),
        .I3(\Delay1_out1_reg[13] [9]),
        .I4(modulating_signal_in_clock_cycles_1_reg_i_17__0_n_0),
        .O(B[9]));
  LUT5 #(
    .INIT(32'hFFFF4540)) 
    modulating_signal_in_clock_cycles_1_reg_i_6__0
       (.I0(Logical_Operator_out1__1),
        .I1(\Delay1_out1_reg[13]_0 [8]),
        .I2(PWM_en_AXI_2_reg),
        .I3(\Delay1_out1_reg[13] [8]),
        .I4(modulating_signal_in_clock_cycles_1_reg_i_17__0_n_0),
        .O(B[8]));
  LUT5 #(
    .INIT(32'hFFFF4540)) 
    modulating_signal_in_clock_cycles_1_reg_i_7__0
       (.I0(Logical_Operator_out1__1),
        .I1(\Delay1_out1_reg[13]_0 [7]),
        .I2(PWM_en_AXI_2_reg),
        .I3(\Delay1_out1_reg[13] [7]),
        .I4(modulating_signal_in_clock_cycles_1_reg_i_17__0_n_0),
        .O(B[7]));
  LUT5 #(
    .INIT(32'hFFFF4540)) 
    modulating_signal_in_clock_cycles_1_reg_i_8__0
       (.I0(Logical_Operator_out1__1),
        .I1(\Delay1_out1_reg[13]_0 [6]),
        .I2(PWM_en_AXI_2_reg),
        .I3(\Delay1_out1_reg[13] [6]),
        .I4(modulating_signal_in_clock_cycles_1_reg_i_17__0_n_0),
        .O(B[6]));
  LUT5 #(
    .INIT(32'hBABBBAAA)) 
    modulating_signal_in_clock_cycles_1_reg_i_9__0
       (.I0(modulating_signal_in_clock_cycles_1_reg_i_18__0_n_0),
        .I1(Logical_Operator_out1__1),
        .I2(\Delay1_out1_reg[13]_0 [5]),
        .I3(PWM_en_AXI_2_reg),
        .I4(\Delay1_out1_reg[13] [5]),
        .O(B[5]));
endmodule

(* ORIG_REF_NAME = "PWM_SS_3L_ip_src_LimitPulseWidth_c" *) 
module zusys_PWM_SS_3L_ip_0_0_PWM_SS_3L_ip_src_LimitPulseWidth_c
   (\min_pulse_width_AXI_1_reg[9] ,
    \delayMatch5_reg_reg[1][13] ,
    PWM_en_AXI_2_reg,
    B,
    \delayMatch5_reg_reg[1][11] ,
    \delayMatch5_reg_reg[1][9] ,
    \delayMatch5_reg_reg[1][7] ,
    \delayMatch5_reg_reg[1][5] ,
    \delayMatch5_reg_reg[1][3] ,
    \delayMatch5_reg_reg[1][1] ,
    HDL_Counter2_count_reg_16_sp_1,
    HDL_Counter2_count_reg_13_sp_1,
    HDL_Counter2_count_reg_1_sp_1,
    HDL_Counter2_count_reg_10_sp_1,
    HDL_Counter2_count_reg_7_sp_1,
    \HDL_Counter2_count_reg[18] ,
    RSTP,
    CEP,
    IPCORE_CLK,
    Q,
    \minus_out1_1_reg[7]_0 ,
    CO,
    \Delay2_out1_reg[13] ,
    \Delay2_out1_reg[13]_0 ,
    \Delay2_out1_reg[13]_1 ,
    D,
    HDL_Counter2_count_reg,
    \Delay2_out1_reg[13]_2 ,
    maximum_counter_value_1,
    \Delay2_out1_reg[0] ,
    \minus_out1_1_reg[5]_0 ,
    \minus_out1_1_reg[6]_0 ,
    \minus_out1_1_reg[9]_0 ,
    \minus_out1_1_reg[10]_0 ,
    \minus_out1_1_reg[11]_0 );
  output \min_pulse_width_AXI_1_reg[9] ;
  output \delayMatch5_reg_reg[1][13] ;
  output PWM_en_AXI_2_reg;
  output [13:0]B;
  output \delayMatch5_reg_reg[1][11] ;
  output \delayMatch5_reg_reg[1][9] ;
  output \delayMatch5_reg_reg[1][7] ;
  output \delayMatch5_reg_reg[1][5] ;
  output \delayMatch5_reg_reg[1][3] ;
  output \delayMatch5_reg_reg[1][1] ;
  output HDL_Counter2_count_reg_16_sp_1;
  output HDL_Counter2_count_reg_13_sp_1;
  output HDL_Counter2_count_reg_1_sp_1;
  output HDL_Counter2_count_reg_10_sp_1;
  output HDL_Counter2_count_reg_7_sp_1;
  output [6:0]\HDL_Counter2_count_reg[18] ;
  input RSTP;
  input CEP;
  input IPCORE_CLK;
  input [13:0]Q;
  input \minus_out1_1_reg[7]_0 ;
  input [0:0]CO;
  input [13:0]\Delay2_out1_reg[13] ;
  input [13:0]\Delay2_out1_reg[13]_0 ;
  input \Delay2_out1_reg[13]_1 ;
  input [0:0]D;
  input [19:0]HDL_Counter2_count_reg;
  input [0:0]\Delay2_out1_reg[13]_2 ;
  input [19:0]maximum_counter_value_1;
  input \Delay2_out1_reg[0] ;
  input \minus_out1_1_reg[5]_0 ;
  input \minus_out1_1_reg[6]_0 ;
  input \minus_out1_1_reg[9]_0 ;
  input \minus_out1_1_reg[10]_0 ;
  input \minus_out1_1_reg[11]_0 ;

  wire [13:11]Add1_out1;
  wire [13:0]Add1_out1_1;
  wire \Add1_out1_1[13]_i_2__1_n_0 ;
  wire \Add1_out1_1[13]_i_3_n_0 ;
  wire \Add1_out1_1[13]_i_4__1_n_0 ;
  wire \Add1_out1_1_reg[13]_i_1__1_n_6 ;
  wire \Add1_out1_1_reg[13]_i_1__1_n_7 ;
  wire [13:1]Add2_out1;
  wire [13:1]Add2_out1_1;
  wire \Add2_out1_1[13]_i_2__1_n_0 ;
  wire \Add2_out1_1[13]_i_3__1_n_0 ;
  wire \Add2_out1_1[13]_i_4__1_n_0 ;
  wire \Add2_out1_1[13]_i_5__1_n_0 ;
  wire \Add2_out1_1[8]_i_10__1_n_0 ;
  wire \Add2_out1_1[8]_i_2__1_n_0 ;
  wire \Add2_out1_1[8]_i_3__1_n_0 ;
  wire \Add2_out1_1[8]_i_4__1_n_0 ;
  wire \Add2_out1_1[8]_i_5__1_n_0 ;
  wire \Add2_out1_1[8]_i_6__1_n_0 ;
  wire \Add2_out1_1[8]_i_7__1_n_0 ;
  wire \Add2_out1_1[8]_i_8__1_n_0 ;
  wire \Add2_out1_1[8]_i_9__1_n_0 ;
  wire \Add2_out1_1_reg[13]_i_1__1_n_4 ;
  wire \Add2_out1_1_reg[13]_i_1__1_n_5 ;
  wire \Add2_out1_1_reg[13]_i_1__1_n_6 ;
  wire \Add2_out1_1_reg[13]_i_1__1_n_7 ;
  wire \Add2_out1_1_reg[8]_i_1__1_n_0 ;
  wire \Add2_out1_1_reg[8]_i_1__1_n_1 ;
  wire \Add2_out1_1_reg[8]_i_1__1_n_2 ;
  wire \Add2_out1_1_reg[8]_i_1__1_n_3 ;
  wire \Add2_out1_1_reg[8]_i_1__1_n_4 ;
  wire \Add2_out1_1_reg[8]_i_1__1_n_5 ;
  wire \Add2_out1_1_reg[8]_i_1__1_n_6 ;
  wire \Add2_out1_1_reg[8]_i_1__1_n_7 ;
  wire [13:0]B;
  wire CEP;
  wire [0:0]CO;
  wire [0:0]D;
  wire \Delay2_out1_reg[0] ;
  wire [13:0]\Delay2_out1_reg[13] ;
  wire [13:0]\Delay2_out1_reg[13]_0 ;
  wire \Delay2_out1_reg[13]_1 ;
  wire [0:0]\Delay2_out1_reg[13]_2 ;
  wire [19:0]HDL_Counter2_count_reg;
  wire [6:0]\HDL_Counter2_count_reg[18] ;
  wire HDL_Counter2_count_reg_10_sn_1;
  wire HDL_Counter2_count_reg_13_sn_1;
  wire HDL_Counter2_count_reg_16_sn_1;
  wire HDL_Counter2_count_reg_1_sn_1;
  wire HDL_Counter2_count_reg_7_sn_1;
  wire IPCORE_CLK;
  wire Logical_Operator1_out10_carry_i_10_n_0;
  wire Logical_Operator1_out10_carry_i_11_n_0;
  wire Logical_Operator1_out10_carry_i_12_n_0;
  wire Logical_Operator1_out10_carry_i_13_n_0;
  wire Logical_Operator1_out10_carry_i_14_n_0;
  wire Logical_Operator1_out10_carry_i_1_n_0;
  wire Logical_Operator1_out10_carry_i_2_n_0;
  wire Logical_Operator1_out10_carry_i_3_n_0;
  wire Logical_Operator1_out10_carry_i_4_n_0;
  wire Logical_Operator1_out10_carry_i_5_n_0;
  wire Logical_Operator1_out10_carry_i_6_n_0;
  wire Logical_Operator1_out10_carry_i_7_n_0;
  wire Logical_Operator1_out10_carry_i_8_n_0;
  wire Logical_Operator1_out10_carry_i_9_n_0;
  wire Logical_Operator1_out10_carry_n_2;
  wire Logical_Operator1_out10_carry_n_3;
  wire Logical_Operator1_out10_carry_n_4;
  wire Logical_Operator1_out10_carry_n_5;
  wire Logical_Operator1_out10_carry_n_6;
  wire Logical_Operator1_out10_carry_n_7;
  wire \Logical_Operator1_out10_inferred__0/i__carry_n_2 ;
  wire \Logical_Operator1_out10_inferred__0/i__carry_n_3 ;
  wire \Logical_Operator1_out10_inferred__0/i__carry_n_4 ;
  wire \Logical_Operator1_out10_inferred__0/i__carry_n_5 ;
  wire \Logical_Operator1_out10_inferred__0/i__carry_n_6 ;
  wire \Logical_Operator1_out10_inferred__0/i__carry_n_7 ;
  wire Logical_Operator_out10_carry_i_10_n_0;
  wire Logical_Operator_out10_carry_i_11_n_0;
  wire Logical_Operator_out10_carry_i_12_n_0;
  wire Logical_Operator_out10_carry_i_13_n_0;
  wire Logical_Operator_out10_carry_i_14_n_0;
  wire Logical_Operator_out10_carry_i_1_n_0;
  wire Logical_Operator_out10_carry_i_2_n_0;
  wire Logical_Operator_out10_carry_i_3_n_0;
  wire Logical_Operator_out10_carry_i_4_n_0;
  wire Logical_Operator_out10_carry_i_5_n_0;
  wire Logical_Operator_out10_carry_i_6_n_0;
  wire Logical_Operator_out10_carry_i_7_n_0;
  wire Logical_Operator_out10_carry_i_8_n_0;
  wire Logical_Operator_out10_carry_i_9_n_0;
  wire Logical_Operator_out10_carry_n_2;
  wire Logical_Operator_out10_carry_n_3;
  wire Logical_Operator_out10_carry_n_4;
  wire Logical_Operator_out10_carry_n_5;
  wire Logical_Operator_out10_carry_n_6;
  wire Logical_Operator_out10_carry_n_7;
  wire Logical_Operator_out11_carry_i_1_n_0;
  wire Logical_Operator_out11_carry_i_2_n_0;
  wire Logical_Operator_out11_carry_i_3_n_0;
  wire Logical_Operator_out11_carry_i_4_n_0;
  wire Logical_Operator_out11_carry_i_5_n_0;
  wire Logical_Operator_out11_carry_i_6_n_0;
  wire Logical_Operator_out11_carry_i_7_n_0;
  wire Logical_Operator_out11_carry_i_8_n_0;
  wire Logical_Operator_out11_carry_i_9_n_0;
  wire Logical_Operator_out11_carry_n_2;
  wire Logical_Operator_out11_carry_n_3;
  wire Logical_Operator_out11_carry_n_4;
  wire Logical_Operator_out11_carry_n_5;
  wire Logical_Operator_out11_carry_n_6;
  wire Logical_Operator_out11_carry_n_7;
  wire Logical_Operator_out1__1;
  wire PWM_en_AXI_2_reg;
  wire [13:0]Q;
  wire RSTP;
  wire Relational_Operator1_relop1;
  wire Relational_Operator2_relop1;
  wire Relational_Operator3_relop1;
  wire Relational_Operator_relop1;
  wire [12:0]Saturation1_out1;
  wire [12:11]Saturation1_out1_1;
  wire \delayMatch5_reg_reg[1][11] ;
  wire \delayMatch5_reg_reg[1][13] ;
  wire \delayMatch5_reg_reg[1][1] ;
  wire \delayMatch5_reg_reg[1][3] ;
  wire \delayMatch5_reg_reg[1][5] ;
  wire \delayMatch5_reg_reg[1][7] ;
  wire \delayMatch5_reg_reg[1][9] ;
  wire i__carry_i_10__1_n_0;
  wire i__carry_i_11__1_n_0;
  wire i__carry_i_12__1_n_0;
  wire i__carry_i_13__1_n_0;
  wire i__carry_i_14__1_n_0;
  wire i__carry_i_1_n_0;
  wire i__carry_i_2_n_0;
  wire i__carry_i_3_n_0;
  wire i__carry_i_4_n_0;
  wire i__carry_i_5_n_0;
  wire i__carry_i_6_n_0;
  wire i__carry_i_7_n_0;
  wire i__carry_i_8_n_0;
  wire i__carry_i_9_n_0;
  wire [19:0]maximum_counter_value_1;
  wire \min_pulse_width_AXI_1_reg[9] ;
  wire [13:1]minus_out1;
  wire [13:1]minus_out1_1;
  wire \minus_out1_1[5]_i_2__1_n_0 ;
  wire \minus_out1_1_reg[10]_0 ;
  wire \minus_out1_1_reg[11]_0 ;
  wire \minus_out1_1_reg[5]_0 ;
  wire \minus_out1_1_reg[6]_0 ;
  wire \minus_out1_1_reg[7]_0 ;
  wire \minus_out1_1_reg[9]_0 ;
  wire modulating_signal_in_clock_cycles_1_reg_i_17__1_n_0;
  wire modulating_signal_in_clock_cycles_1_reg_i_18__1_n_0;
  wire [7:2]\NLW_Add1_out1_1_reg[13]_i_1__1_CO_UNCONNECTED ;
  wire [7:3]\NLW_Add1_out1_1_reg[13]_i_1__1_O_UNCONNECTED ;
  wire [7:4]\NLW_Add2_out1_1_reg[13]_i_1__1_CO_UNCONNECTED ;
  wire [7:5]\NLW_Add2_out1_1_reg[13]_i_1__1_O_UNCONNECTED ;
  wire [7:7]NLW_Logical_Operator1_out10_carry_CO_UNCONNECTED;
  wire [7:0]NLW_Logical_Operator1_out10_carry_O_UNCONNECTED;
  wire [7:7]\NLW_Logical_Operator1_out10_inferred__0/i__carry_CO_UNCONNECTED ;
  wire [7:0]\NLW_Logical_Operator1_out10_inferred__0/i__carry_O_UNCONNECTED ;
  wire [7:7]NLW_Logical_Operator_out10_carry_CO_UNCONNECTED;
  wire [7:0]NLW_Logical_Operator_out10_carry_O_UNCONNECTED;
  wire [7:7]NLW_Logical_Operator_out11_carry_CO_UNCONNECTED;
  wire [7:0]NLW_Logical_Operator_out11_carry_O_UNCONNECTED;

  assign HDL_Counter2_count_reg_10_sp_1 = HDL_Counter2_count_reg_10_sn_1;
  assign HDL_Counter2_count_reg_13_sp_1 = HDL_Counter2_count_reg_13_sn_1;
  assign HDL_Counter2_count_reg_16_sp_1 = HDL_Counter2_count_reg_16_sn_1;
  assign HDL_Counter2_count_reg_1_sp_1 = HDL_Counter2_count_reg_1_sn_1;
  assign HDL_Counter2_count_reg_7_sp_1 = HDL_Counter2_count_reg_7_sn_1;
  (* SOFT_HLUTNM = "soft_lutpair44" *) 
  LUT3 #(
    .INIT(8'h02)) 
    \Add1_out1_1[0]_i_1__1 
       (.I0(Q[0]),
        .I1(CO),
        .I2(Q[13]),
        .O(Saturation1_out1[0]));
  (* SOFT_HLUTNM = "soft_lutpair49" *) 
  LUT3 #(
    .INIT(8'h02)) 
    \Add1_out1_1[10]_i_1__1 
       (.I0(Q[10]),
        .I1(CO),
        .I2(Q[13]),
        .O(Saturation1_out1[10]));
  LUT3 #(
    .INIT(8'hBA)) 
    \Add1_out1_1[13]_i_2__1 
       (.I0(CO),
        .I1(Q[13]),
        .I2(Q[12]),
        .O(\Add1_out1_1[13]_i_2__1_n_0 ));
  LUT3 #(
    .INIT(8'h0D)) 
    \Add1_out1_1[13]_i_3 
       (.I0(Q[12]),
        .I1(Q[13]),
        .I2(CO),
        .O(\Add1_out1_1[13]_i_3_n_0 ));
  LUT3 #(
    .INIT(8'h02)) 
    \Add1_out1_1[13]_i_4__1 
       (.I0(Q[11]),
        .I1(CO),
        .I2(Q[13]),
        .O(\Add1_out1_1[13]_i_4__1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair45" *) 
  LUT3 #(
    .INIT(8'h02)) 
    \Add1_out1_1[1]_i_1__1 
       (.I0(Q[1]),
        .I1(CO),
        .I2(Q[13]),
        .O(Saturation1_out1[1]));
  (* SOFT_HLUTNM = "soft_lutpair45" *) 
  LUT3 #(
    .INIT(8'h02)) 
    \Add1_out1_1[2]_i_1__1 
       (.I0(Q[2]),
        .I1(CO),
        .I2(Q[13]),
        .O(Saturation1_out1[2]));
  (* SOFT_HLUTNM = "soft_lutpair46" *) 
  LUT3 #(
    .INIT(8'h02)) 
    \Add1_out1_1[3]_i_1__1 
       (.I0(Q[3]),
        .I1(CO),
        .I2(Q[13]),
        .O(Saturation1_out1[3]));
  (* SOFT_HLUTNM = "soft_lutpair46" *) 
  LUT3 #(
    .INIT(8'h02)) 
    \Add1_out1_1[4]_i_1__1 
       (.I0(Q[4]),
        .I1(CO),
        .I2(Q[13]),
        .O(Saturation1_out1[4]));
  (* SOFT_HLUTNM = "soft_lutpair47" *) 
  LUT3 #(
    .INIT(8'h02)) 
    \Add1_out1_1[5]_i_1__1 
       (.I0(Q[5]),
        .I1(CO),
        .I2(Q[13]),
        .O(Saturation1_out1[5]));
  (* SOFT_HLUTNM = "soft_lutpair38" *) 
  LUT3 #(
    .INIT(8'h02)) 
    \Add1_out1_1[6]_i_1__1 
       (.I0(Q[6]),
        .I1(CO),
        .I2(Q[13]),
        .O(Saturation1_out1[6]));
  (* SOFT_HLUTNM = "soft_lutpair47" *) 
  LUT3 #(
    .INIT(8'h02)) 
    \Add1_out1_1[7]_i_1__1 
       (.I0(Q[7]),
        .I1(CO),
        .I2(Q[13]),
        .O(Saturation1_out1[7]));
  (* SOFT_HLUTNM = "soft_lutpair48" *) 
  LUT3 #(
    .INIT(8'h02)) 
    \Add1_out1_1[8]_i_1__1 
       (.I0(Q[8]),
        .I1(CO),
        .I2(Q[13]),
        .O(Saturation1_out1[8]));
  (* SOFT_HLUTNM = "soft_lutpair48" *) 
  LUT3 #(
    .INIT(8'h02)) 
    \Add1_out1_1[9]_i_1__1 
       (.I0(Q[9]),
        .I1(CO),
        .I2(Q[13]),
        .O(Saturation1_out1[9]));
  FDRE \Add1_out1_1_reg[0] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Saturation1_out1[0]),
        .Q(Add1_out1_1[0]),
        .R(RSTP));
  FDRE \Add1_out1_1_reg[10] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Saturation1_out1[10]),
        .Q(Add1_out1_1[10]),
        .R(RSTP));
  FDRE \Add1_out1_1_reg[11] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Add1_out1[11]),
        .Q(Add1_out1_1[11]),
        .R(RSTP));
  FDRE \Add1_out1_1_reg[12] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Add1_out1[12]),
        .Q(Add1_out1_1[12]),
        .R(RSTP));
  FDRE \Add1_out1_1_reg[13] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Add1_out1[13]),
        .Q(Add1_out1_1[13]),
        .R(RSTP));
  (* ADDER_THRESHOLD = "35" *) 
  CARRY8 \Add1_out1_1_reg[13]_i_1__1 
       (.CI(1'b0),
        .CI_TOP(1'b0),
        .CO({\NLW_Add1_out1_1_reg[13]_i_1__1_CO_UNCONNECTED [7:2],\Add1_out1_1_reg[13]_i_1__1_n_6 ,\Add1_out1_1_reg[13]_i_1__1_n_7 }),
        .DI({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,\Add1_out1_1[13]_i_2__1_n_0 ,1'b0}),
        .O({\NLW_Add1_out1_1_reg[13]_i_1__1_O_UNCONNECTED [7:3],Add1_out1}),
        .S({1'b0,1'b0,1'b0,1'b0,1'b0,1'b1,\Add1_out1_1[13]_i_3_n_0 ,\Add1_out1_1[13]_i_4__1_n_0 }));
  FDRE \Add1_out1_1_reg[1] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Saturation1_out1[1]),
        .Q(Add1_out1_1[1]),
        .R(RSTP));
  FDRE \Add1_out1_1_reg[2] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Saturation1_out1[2]),
        .Q(Add1_out1_1[2]),
        .R(RSTP));
  FDRE \Add1_out1_1_reg[3] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Saturation1_out1[3]),
        .Q(Add1_out1_1[3]),
        .R(RSTP));
  FDRE \Add1_out1_1_reg[4] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Saturation1_out1[4]),
        .Q(Add1_out1_1[4]),
        .R(RSTP));
  FDRE \Add1_out1_1_reg[5] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Saturation1_out1[5]),
        .Q(Add1_out1_1[5]),
        .R(RSTP));
  FDRE \Add1_out1_1_reg[6] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Saturation1_out1[6]),
        .Q(Add1_out1_1[6]),
        .R(RSTP));
  FDRE \Add1_out1_1_reg[7] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Saturation1_out1[7]),
        .Q(Add1_out1_1[7]),
        .R(RSTP));
  FDRE \Add1_out1_1_reg[8] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Saturation1_out1[8]),
        .Q(Add1_out1_1[8]),
        .R(RSTP));
  FDRE \Add1_out1_1_reg[9] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Saturation1_out1[9]),
        .Q(Add1_out1_1[9]),
        .R(RSTP));
  LUT3 #(
    .INIT(8'hBA)) 
    \Add2_out1_1[13]_i_2__1 
       (.I0(CO),
        .I1(Q[13]),
        .I2(Q[12]),
        .O(\Add2_out1_1[13]_i_2__1_n_0 ));
  LUT3 #(
    .INIT(8'hEF)) 
    \Add2_out1_1[13]_i_3__1 
       (.I0(Q[13]),
        .I1(CO),
        .I2(Q[11]),
        .O(\Add2_out1_1[13]_i_3__1_n_0 ));
  LUT3 #(
    .INIT(8'hEF)) 
    \Add2_out1_1[13]_i_4__1 
       (.I0(Q[13]),
        .I1(CO),
        .I2(Q[10]),
        .O(\Add2_out1_1[13]_i_4__1_n_0 ));
  LUT3 #(
    .INIT(8'hEF)) 
    \Add2_out1_1[13]_i_5__1 
       (.I0(Q[13]),
        .I1(CO),
        .I2(Q[9]),
        .O(\Add2_out1_1[13]_i_5__1_n_0 ));
  LUT3 #(
    .INIT(8'hEF)) 
    \Add2_out1_1[8]_i_10__1 
       (.I0(Q[13]),
        .I1(CO),
        .I2(Q[1]),
        .O(\Add2_out1_1[8]_i_10__1_n_0 ));
  LUT3 #(
    .INIT(8'hEF)) 
    \Add2_out1_1[8]_i_2__1 
       (.I0(Q[13]),
        .I1(CO),
        .I2(Q[0]),
        .O(\Add2_out1_1[8]_i_2__1_n_0 ));
  LUT3 #(
    .INIT(8'hEF)) 
    \Add2_out1_1[8]_i_3__1 
       (.I0(Q[13]),
        .I1(CO),
        .I2(Q[8]),
        .O(\Add2_out1_1[8]_i_3__1_n_0 ));
  LUT3 #(
    .INIT(8'hEF)) 
    \Add2_out1_1[8]_i_4__1 
       (.I0(Q[13]),
        .I1(CO),
        .I2(Q[7]),
        .O(\Add2_out1_1[8]_i_4__1_n_0 ));
  LUT3 #(
    .INIT(8'hEF)) 
    \Add2_out1_1[8]_i_5__1 
       (.I0(Q[13]),
        .I1(CO),
        .I2(Q[6]),
        .O(\Add2_out1_1[8]_i_5__1_n_0 ));
  LUT3 #(
    .INIT(8'hEF)) 
    \Add2_out1_1[8]_i_6__1 
       (.I0(Q[13]),
        .I1(CO),
        .I2(Q[5]),
        .O(\Add2_out1_1[8]_i_6__1_n_0 ));
  LUT3 #(
    .INIT(8'hEF)) 
    \Add2_out1_1[8]_i_7__1 
       (.I0(Q[13]),
        .I1(CO),
        .I2(Q[4]),
        .O(\Add2_out1_1[8]_i_7__1_n_0 ));
  LUT3 #(
    .INIT(8'hEF)) 
    \Add2_out1_1[8]_i_8__1 
       (.I0(Q[13]),
        .I1(CO),
        .I2(Q[3]),
        .O(\Add2_out1_1[8]_i_8__1_n_0 ));
  LUT3 #(
    .INIT(8'hEF)) 
    \Add2_out1_1[8]_i_9__1 
       (.I0(Q[13]),
        .I1(CO),
        .I2(Q[2]),
        .O(\Add2_out1_1[8]_i_9__1_n_0 ));
  FDRE \Add2_out1_1_reg[10] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Add2_out1[10]),
        .Q(Add2_out1_1[10]),
        .R(RSTP));
  FDRE \Add2_out1_1_reg[11] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Add2_out1[11]),
        .Q(Add2_out1_1[11]),
        .R(RSTP));
  FDRE \Add2_out1_1_reg[12] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Add2_out1[12]),
        .Q(Add2_out1_1[12]),
        .R(RSTP));
  FDRE \Add2_out1_1_reg[13] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Add2_out1[13]),
        .Q(Add2_out1_1[13]),
        .R(RSTP));
  (* ADDER_THRESHOLD = "35" *) 
  CARRY8 \Add2_out1_1_reg[13]_i_1__1 
       (.CI(\Add2_out1_1_reg[8]_i_1__1_n_0 ),
        .CI_TOP(1'b0),
        .CO({\NLW_Add2_out1_1_reg[13]_i_1__1_CO_UNCONNECTED [7:4],\Add2_out1_1_reg[13]_i_1__1_n_4 ,\Add2_out1_1_reg[13]_i_1__1_n_5 ,\Add2_out1_1_reg[13]_i_1__1_n_6 ,\Add2_out1_1_reg[13]_i_1__1_n_7 }),
        .DI({1'b0,1'b0,1'b0,1'b0,1'b1,1'b0,1'b0,1'b0}),
        .O({\NLW_Add2_out1_1_reg[13]_i_1__1_O_UNCONNECTED [7:5],Add2_out1[13:9]}),
        .S({1'b0,1'b0,1'b0,1'b1,\Add2_out1_1[13]_i_2__1_n_0 ,\Add2_out1_1[13]_i_3__1_n_0 ,\Add2_out1_1[13]_i_4__1_n_0 ,\Add2_out1_1[13]_i_5__1_n_0 }));
  FDRE \Add2_out1_1_reg[1] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Add2_out1[1]),
        .Q(Add2_out1_1[1]),
        .R(RSTP));
  FDRE \Add2_out1_1_reg[2] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Add2_out1[2]),
        .Q(Add2_out1_1[2]),
        .R(RSTP));
  FDRE \Add2_out1_1_reg[3] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Add2_out1[3]),
        .Q(Add2_out1_1[3]),
        .R(RSTP));
  FDRE \Add2_out1_1_reg[4] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Add2_out1[4]),
        .Q(Add2_out1_1[4]),
        .R(RSTP));
  FDRE \Add2_out1_1_reg[5] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Add2_out1[5]),
        .Q(Add2_out1_1[5]),
        .R(RSTP));
  FDRE \Add2_out1_1_reg[6] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Add2_out1[6]),
        .Q(Add2_out1_1[6]),
        .R(RSTP));
  FDRE \Add2_out1_1_reg[7] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Add2_out1[7]),
        .Q(Add2_out1_1[7]),
        .R(RSTP));
  FDRE \Add2_out1_1_reg[8] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Add2_out1[8]),
        .Q(Add2_out1_1[8]),
        .R(RSTP));
  (* ADDER_THRESHOLD = "35" *) 
  CARRY8 \Add2_out1_1_reg[8]_i_1__1 
       (.CI(\Add2_out1_1[8]_i_2__1_n_0 ),
        .CI_TOP(1'b0),
        .CO({\Add2_out1_1_reg[8]_i_1__1_n_0 ,\Add2_out1_1_reg[8]_i_1__1_n_1 ,\Add2_out1_1_reg[8]_i_1__1_n_2 ,\Add2_out1_1_reg[8]_i_1__1_n_3 ,\Add2_out1_1_reg[8]_i_1__1_n_4 ,\Add2_out1_1_reg[8]_i_1__1_n_5 ,\Add2_out1_1_reg[8]_i_1__1_n_6 ,\Add2_out1_1_reg[8]_i_1__1_n_7 }),
        .DI({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .O(Add2_out1[8:1]),
        .S({\Add2_out1_1[8]_i_3__1_n_0 ,\Add2_out1_1[8]_i_4__1_n_0 ,\Add2_out1_1[8]_i_5__1_n_0 ,\Add2_out1_1[8]_i_6__1_n_0 ,\Add2_out1_1[8]_i_7__1_n_0 ,\Add2_out1_1[8]_i_8__1_n_0 ,\Add2_out1_1[8]_i_9__1_n_0 ,\Add2_out1_1[8]_i_10__1_n_0 }));
  FDRE \Add2_out1_1_reg[9] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Add2_out1[9]),
        .Q(Add2_out1_1[9]),
        .R(RSTP));
  LUT4 #(
    .INIT(16'h080A)) 
    Counter_Ctrl_out5_1_i_2
       (.I0(HDL_Counter2_count_reg_13_sn_1),
        .I1(HDL_Counter2_count_reg[16]),
        .I2(HDL_Counter2_count_reg[17]),
        .I3(HDL_Counter2_count_reg[15]),
        .O(HDL_Counter2_count_reg_16_sn_1));
  LUT6 #(
    .INIT(64'h0000000200000000)) 
    Counter_Ctrl_out5_1_i_3
       (.I0(HDL_Counter2_count_reg_10_sn_1),
        .I1(HDL_Counter2_count_reg[1]),
        .I2(HDL_Counter2_count_reg[0]),
        .I3(HDL_Counter2_count_reg[4]),
        .I4(HDL_Counter2_count_reg[2]),
        .I5(HDL_Counter2_count_reg_7_sn_1),
        .O(HDL_Counter2_count_reg_1_sn_1));
  LUT6 #(
    .INIT(64'h0000230000002323)) 
    Counter_Ctrl_out5_1_i_5
       (.I0(HDL_Counter2_count_reg[13]),
        .I1(HDL_Counter2_count_reg[14]),
        .I2(HDL_Counter2_count_reg[12]),
        .I3(HDL_Counter2_count_reg[10]),
        .I4(HDL_Counter2_count_reg[11]),
        .I5(HDL_Counter2_count_reg[9]),
        .O(HDL_Counter2_count_reg_13_sn_1));
  LUT4 #(
    .INIT(16'h0001)) 
    Counter_Ctrl_out5_1_i_6
       (.I0(HDL_Counter2_count_reg[10]),
        .I1(HDL_Counter2_count_reg[8]),
        .I2(HDL_Counter2_count_reg[7]),
        .I3(HDL_Counter2_count_reg[5]),
        .O(HDL_Counter2_count_reg_10_sn_1));
  LUT6 #(
    .INIT(64'h0000230000002323)) 
    Counter_Ctrl_out5_1_i_7
       (.I0(HDL_Counter2_count_reg[7]),
        .I1(HDL_Counter2_count_reg[8]),
        .I2(HDL_Counter2_count_reg[6]),
        .I3(HDL_Counter2_count_reg[4]),
        .I4(HDL_Counter2_count_reg[5]),
        .I5(HDL_Counter2_count_reg[3]),
        .O(HDL_Counter2_count_reg_7_sn_1));
  LUT6 #(
    .INIT(64'hAAAAFFBFAAAA0080)) 
    \Delay2_out1[11]_i_1 
       (.I0(\Delay2_out1_reg[13]_0 [11]),
        .I1(\Delay2_out1_reg[13]_1 ),
        .I2(D),
        .I3(HDL_Counter2_count_reg[19]),
        .I4(\Delay2_out1_reg[13]_2 ),
        .I5(\Delay2_out1_reg[13] [11]),
        .O(\delayMatch5_reg_reg[1][11] ));
  LUT6 #(
    .INIT(64'hAAAAFFBFAAAA0080)) 
    \Delay2_out1[13]_i_1 
       (.I0(\Delay2_out1_reg[13]_0 [13]),
        .I1(\Delay2_out1_reg[13]_1 ),
        .I2(D),
        .I3(HDL_Counter2_count_reg[19]),
        .I4(\Delay2_out1_reg[13]_2 ),
        .I5(\Delay2_out1_reg[13] [13]),
        .O(\delayMatch5_reg_reg[1][13] ));
  LUT6 #(
    .INIT(64'hAAAAFFBFAAAA0080)) 
    \Delay2_out1[1]_i_1 
       (.I0(\Delay2_out1_reg[13]_0 [1]),
        .I1(\Delay2_out1_reg[13]_1 ),
        .I2(D),
        .I3(HDL_Counter2_count_reg[19]),
        .I4(\Delay2_out1_reg[13]_2 ),
        .I5(\Delay2_out1_reg[13] [1]),
        .O(\delayMatch5_reg_reg[1][1] ));
  LUT6 #(
    .INIT(64'hAAAAFFBFAAAA0080)) 
    \Delay2_out1[3]_i_1 
       (.I0(\Delay2_out1_reg[13]_0 [3]),
        .I1(\Delay2_out1_reg[13]_1 ),
        .I2(D),
        .I3(HDL_Counter2_count_reg[19]),
        .I4(\Delay2_out1_reg[13]_2 ),
        .I5(\Delay2_out1_reg[13] [3]),
        .O(\delayMatch5_reg_reg[1][3] ));
  LUT6 #(
    .INIT(64'hAAAAFFBFAAAA0080)) 
    \Delay2_out1[5]_i_1 
       (.I0(\Delay2_out1_reg[13]_0 [5]),
        .I1(\Delay2_out1_reg[13]_1 ),
        .I2(D),
        .I3(HDL_Counter2_count_reg[19]),
        .I4(\Delay2_out1_reg[13]_2 ),
        .I5(\Delay2_out1_reg[13] [5]),
        .O(\delayMatch5_reg_reg[1][5] ));
  LUT6 #(
    .INIT(64'hAAAAFFBFAAAA0080)) 
    \Delay2_out1[7]_i_1 
       (.I0(\Delay2_out1_reg[13]_0 [7]),
        .I1(\Delay2_out1_reg[13]_1 ),
        .I2(D),
        .I3(HDL_Counter2_count_reg[19]),
        .I4(\Delay2_out1_reg[13]_2 ),
        .I5(\Delay2_out1_reg[13] [7]),
        .O(\delayMatch5_reg_reg[1][7] ));
  LUT6 #(
    .INIT(64'hAAAAFFBFAAAA0080)) 
    \Delay2_out1[9]_i_1 
       (.I0(\Delay2_out1_reg[13]_0 [9]),
        .I1(\Delay2_out1_reg[13]_1 ),
        .I2(D),
        .I3(HDL_Counter2_count_reg[19]),
        .I4(\Delay2_out1_reg[13]_2 ),
        .I5(\Delay2_out1_reg[13] [9]),
        .O(\delayMatch5_reg_reg[1][9] ));
  (* COMPARATOR_THRESHOLD = "11" *) 
  CARRY8 Logical_Operator1_out10_carry
       (.CI(1'b0),
        .CI_TOP(1'b0),
        .CO({NLW_Logical_Operator1_out10_carry_CO_UNCONNECTED[7],Relational_Operator_relop1,Logical_Operator1_out10_carry_n_2,Logical_Operator1_out10_carry_n_3,Logical_Operator1_out10_carry_n_4,Logical_Operator1_out10_carry_n_5,Logical_Operator1_out10_carry_n_6,Logical_Operator1_out10_carry_n_7}),
        .DI({1'b0,Logical_Operator1_out10_carry_i_1_n_0,Logical_Operator1_out10_carry_i_2_n_0,Logical_Operator1_out10_carry_i_3_n_0,Logical_Operator1_out10_carry_i_4_n_0,Logical_Operator1_out10_carry_i_5_n_0,Logical_Operator1_out10_carry_i_6_n_0,Logical_Operator1_out10_carry_i_7_n_0}),
        .O(NLW_Logical_Operator1_out10_carry_O_UNCONNECTED[7:0]),
        .S({1'b0,Logical_Operator1_out10_carry_i_8_n_0,Logical_Operator1_out10_carry_i_9_n_0,Logical_Operator1_out10_carry_i_10_n_0,Logical_Operator1_out10_carry_i_11_n_0,Logical_Operator1_out10_carry_i_12_n_0,Logical_Operator1_out10_carry_i_13_n_0,Logical_Operator1_out10_carry_i_14_n_0}));
  LUT6 #(
    .INIT(64'h22222222BBB222B2)) 
    Logical_Operator1_out10_carry_i_1
       (.I0(minus_out1_1[13]),
        .I1(\delayMatch5_reg_reg[1][13] ),
        .I2(\Delay2_out1_reg[13] [12]),
        .I3(PWM_en_AXI_2_reg),
        .I4(\Delay2_out1_reg[13]_0 [12]),
        .I5(minus_out1_1[12]),
        .O(Logical_Operator1_out10_carry_i_1_n_0));
  LUT6 #(
    .INIT(64'hA95900000000A959)) 
    Logical_Operator1_out10_carry_i_10
       (.I0(minus_out1_1[8]),
        .I1(\Delay2_out1_reg[13] [8]),
        .I2(PWM_en_AXI_2_reg),
        .I3(\Delay2_out1_reg[13]_0 [8]),
        .I4(\delayMatch5_reg_reg[1][9] ),
        .I5(minus_out1_1[9]),
        .O(Logical_Operator1_out10_carry_i_10_n_0));
  LUT6 #(
    .INIT(64'hA95900000000A959)) 
    Logical_Operator1_out10_carry_i_11
       (.I0(minus_out1_1[6]),
        .I1(\Delay2_out1_reg[13] [6]),
        .I2(PWM_en_AXI_2_reg),
        .I3(\Delay2_out1_reg[13]_0 [6]),
        .I4(\delayMatch5_reg_reg[1][7] ),
        .I5(minus_out1_1[7]),
        .O(Logical_Operator1_out10_carry_i_11_n_0));
  LUT6 #(
    .INIT(64'hA95900000000A959)) 
    Logical_Operator1_out10_carry_i_12
       (.I0(minus_out1_1[4]),
        .I1(\Delay2_out1_reg[13] [4]),
        .I2(PWM_en_AXI_2_reg),
        .I3(\Delay2_out1_reg[13]_0 [4]),
        .I4(\delayMatch5_reg_reg[1][5] ),
        .I5(minus_out1_1[5]),
        .O(Logical_Operator1_out10_carry_i_12_n_0));
  LUT6 #(
    .INIT(64'hA95900000000A959)) 
    Logical_Operator1_out10_carry_i_13
       (.I0(minus_out1_1[2]),
        .I1(\Delay2_out1_reg[13] [2]),
        .I2(PWM_en_AXI_2_reg),
        .I3(\Delay2_out1_reg[13]_0 [2]),
        .I4(\delayMatch5_reg_reg[1][3] ),
        .I5(minus_out1_1[3]),
        .O(Logical_Operator1_out10_carry_i_13_n_0));
  LUT6 #(
    .INIT(64'hE21D00000000E21D)) 
    Logical_Operator1_out10_carry_i_14
       (.I0(\Delay2_out1_reg[13] [0]),
        .I1(PWM_en_AXI_2_reg),
        .I2(\Delay2_out1_reg[13]_0 [0]),
        .I3(Add1_out1_1[0]),
        .I4(\delayMatch5_reg_reg[1][1] ),
        .I5(minus_out1_1[1]),
        .O(Logical_Operator1_out10_carry_i_14_n_0));
  LUT6 #(
    .INIT(64'h22222222BBB222B2)) 
    Logical_Operator1_out10_carry_i_2
       (.I0(\delayMatch5_reg_reg[1][11] ),
        .I1(minus_out1_1[11]),
        .I2(\Delay2_out1_reg[13] [10]),
        .I3(PWM_en_AXI_2_reg),
        .I4(\Delay2_out1_reg[13]_0 [10]),
        .I5(minus_out1_1[10]),
        .O(Logical_Operator1_out10_carry_i_2_n_0));
  LUT6 #(
    .INIT(64'h22222222BBB222B2)) 
    Logical_Operator1_out10_carry_i_3
       (.I0(\delayMatch5_reg_reg[1][9] ),
        .I1(minus_out1_1[9]),
        .I2(\Delay2_out1_reg[13] [8]),
        .I3(PWM_en_AXI_2_reg),
        .I4(\Delay2_out1_reg[13]_0 [8]),
        .I5(minus_out1_1[8]),
        .O(Logical_Operator1_out10_carry_i_3_n_0));
  LUT6 #(
    .INIT(64'h22222222BBB222B2)) 
    Logical_Operator1_out10_carry_i_4
       (.I0(\delayMatch5_reg_reg[1][7] ),
        .I1(minus_out1_1[7]),
        .I2(\Delay2_out1_reg[13] [6]),
        .I3(PWM_en_AXI_2_reg),
        .I4(\Delay2_out1_reg[13]_0 [6]),
        .I5(minus_out1_1[6]),
        .O(Logical_Operator1_out10_carry_i_4_n_0));
  LUT6 #(
    .INIT(64'h22222222BBB222B2)) 
    Logical_Operator1_out10_carry_i_5
       (.I0(\delayMatch5_reg_reg[1][5] ),
        .I1(minus_out1_1[5]),
        .I2(\Delay2_out1_reg[13] [4]),
        .I3(PWM_en_AXI_2_reg),
        .I4(\Delay2_out1_reg[13]_0 [4]),
        .I5(minus_out1_1[4]),
        .O(Logical_Operator1_out10_carry_i_5_n_0));
  LUT6 #(
    .INIT(64'h22222222BBB222B2)) 
    Logical_Operator1_out10_carry_i_6
       (.I0(\delayMatch5_reg_reg[1][3] ),
        .I1(minus_out1_1[3]),
        .I2(\Delay2_out1_reg[13] [2]),
        .I3(PWM_en_AXI_2_reg),
        .I4(\Delay2_out1_reg[13]_0 [2]),
        .I5(minus_out1_1[2]),
        .O(Logical_Operator1_out10_carry_i_6_n_0));
  LUT6 #(
    .INIT(64'h7577755510111000)) 
    Logical_Operator1_out10_carry_i_7
       (.I0(minus_out1_1[1]),
        .I1(Add1_out1_1[0]),
        .I2(\Delay2_out1_reg[13]_0 [0]),
        .I3(PWM_en_AXI_2_reg),
        .I4(\Delay2_out1_reg[13] [0]),
        .I5(\delayMatch5_reg_reg[1][1] ),
        .O(Logical_Operator1_out10_carry_i_7_n_0));
  LUT6 #(
    .INIT(64'hA95900000000A959)) 
    Logical_Operator1_out10_carry_i_8
       (.I0(minus_out1_1[12]),
        .I1(\Delay2_out1_reg[13] [12]),
        .I2(PWM_en_AXI_2_reg),
        .I3(\Delay2_out1_reg[13]_0 [12]),
        .I4(\delayMatch5_reg_reg[1][13] ),
        .I5(minus_out1_1[13]),
        .O(Logical_Operator1_out10_carry_i_8_n_0));
  LUT6 #(
    .INIT(64'hA95900000000A959)) 
    Logical_Operator1_out10_carry_i_9
       (.I0(minus_out1_1[10]),
        .I1(\Delay2_out1_reg[13] [10]),
        .I2(PWM_en_AXI_2_reg),
        .I3(\Delay2_out1_reg[13]_0 [10]),
        .I4(\delayMatch5_reg_reg[1][11] ),
        .I5(minus_out1_1[11]),
        .O(Logical_Operator1_out10_carry_i_9_n_0));
  (* COMPARATOR_THRESHOLD = "11" *) 
  CARRY8 \Logical_Operator1_out10_inferred__0/i__carry 
       (.CI(1'b0),
        .CI_TOP(1'b0),
        .CO({\NLW_Logical_Operator1_out10_inferred__0/i__carry_CO_UNCONNECTED [7],Relational_Operator1_relop1,\Logical_Operator1_out10_inferred__0/i__carry_n_2 ,\Logical_Operator1_out10_inferred__0/i__carry_n_3 ,\Logical_Operator1_out10_inferred__0/i__carry_n_4 ,\Logical_Operator1_out10_inferred__0/i__carry_n_5 ,\Logical_Operator1_out10_inferred__0/i__carry_n_6 ,\Logical_Operator1_out10_inferred__0/i__carry_n_7 }),
        .DI({1'b0,i__carry_i_1_n_0,i__carry_i_2_n_0,i__carry_i_3_n_0,i__carry_i_4_n_0,i__carry_i_5_n_0,i__carry_i_6_n_0,i__carry_i_7_n_0}),
        .O(\NLW_Logical_Operator1_out10_inferred__0/i__carry_O_UNCONNECTED [7:0]),
        .S({1'b0,i__carry_i_8_n_0,i__carry_i_9_n_0,i__carry_i_10__1_n_0,i__carry_i_11__1_n_0,i__carry_i_12__1_n_0,i__carry_i_13__1_n_0,i__carry_i_14__1_n_0}));
  (* COMPARATOR_THRESHOLD = "11" *) 
  CARRY8 Logical_Operator_out10_carry
       (.CI(1'b0),
        .CI_TOP(1'b0),
        .CO({NLW_Logical_Operator_out10_carry_CO_UNCONNECTED[7],Relational_Operator3_relop1,Logical_Operator_out10_carry_n_2,Logical_Operator_out10_carry_n_3,Logical_Operator_out10_carry_n_4,Logical_Operator_out10_carry_n_5,Logical_Operator_out10_carry_n_6,Logical_Operator_out10_carry_n_7}),
        .DI({1'b0,Logical_Operator_out10_carry_i_1_n_0,Logical_Operator_out10_carry_i_2_n_0,Logical_Operator_out10_carry_i_3_n_0,Logical_Operator_out10_carry_i_4_n_0,Logical_Operator_out10_carry_i_5_n_0,Logical_Operator_out10_carry_i_6_n_0,Logical_Operator_out10_carry_i_7_n_0}),
        .O(NLW_Logical_Operator_out10_carry_O_UNCONNECTED[7:0]),
        .S({1'b0,Logical_Operator_out10_carry_i_8_n_0,Logical_Operator_out10_carry_i_9_n_0,Logical_Operator_out10_carry_i_10_n_0,Logical_Operator_out10_carry_i_11_n_0,Logical_Operator_out10_carry_i_12_n_0,Logical_Operator_out10_carry_i_13_n_0,Logical_Operator_out10_carry_i_14_n_0}));
  LUT6 #(
    .INIT(64'h22222222BBB222B2)) 
    Logical_Operator_out10_carry_i_1
       (.I0(Add2_out1_1[13]),
        .I1(\delayMatch5_reg_reg[1][13] ),
        .I2(\Delay2_out1_reg[13] [12]),
        .I3(PWM_en_AXI_2_reg),
        .I4(\Delay2_out1_reg[13]_0 [12]),
        .I5(Add2_out1_1[12]),
        .O(Logical_Operator_out10_carry_i_1_n_0));
  LUT6 #(
    .INIT(64'hA95900000000A959)) 
    Logical_Operator_out10_carry_i_10
       (.I0(Add2_out1_1[8]),
        .I1(\Delay2_out1_reg[13] [8]),
        .I2(PWM_en_AXI_2_reg),
        .I3(\Delay2_out1_reg[13]_0 [8]),
        .I4(\delayMatch5_reg_reg[1][9] ),
        .I5(Add2_out1_1[9]),
        .O(Logical_Operator_out10_carry_i_10_n_0));
  LUT6 #(
    .INIT(64'hA95900000000A959)) 
    Logical_Operator_out10_carry_i_11
       (.I0(Add2_out1_1[6]),
        .I1(\Delay2_out1_reg[13] [6]),
        .I2(PWM_en_AXI_2_reg),
        .I3(\Delay2_out1_reg[13]_0 [6]),
        .I4(\delayMatch5_reg_reg[1][7] ),
        .I5(Add2_out1_1[7]),
        .O(Logical_Operator_out10_carry_i_11_n_0));
  LUT6 #(
    .INIT(64'hA95900000000A959)) 
    Logical_Operator_out10_carry_i_12
       (.I0(Add2_out1_1[4]),
        .I1(\Delay2_out1_reg[13] [4]),
        .I2(PWM_en_AXI_2_reg),
        .I3(\Delay2_out1_reg[13]_0 [4]),
        .I4(\delayMatch5_reg_reg[1][5] ),
        .I5(Add2_out1_1[5]),
        .O(Logical_Operator_out10_carry_i_12_n_0));
  LUT6 #(
    .INIT(64'hA95900000000A959)) 
    Logical_Operator_out10_carry_i_13
       (.I0(Add2_out1_1[2]),
        .I1(\Delay2_out1_reg[13] [2]),
        .I2(PWM_en_AXI_2_reg),
        .I3(\Delay2_out1_reg[13]_0 [2]),
        .I4(\delayMatch5_reg_reg[1][3] ),
        .I5(Add2_out1_1[3]),
        .O(Logical_Operator_out10_carry_i_13_n_0));
  LUT6 #(
    .INIT(64'hE21D00000000E21D)) 
    Logical_Operator_out10_carry_i_14
       (.I0(\Delay2_out1_reg[13] [0]),
        .I1(PWM_en_AXI_2_reg),
        .I2(\Delay2_out1_reg[13]_0 [0]),
        .I3(Add1_out1_1[0]),
        .I4(\delayMatch5_reg_reg[1][1] ),
        .I5(Add2_out1_1[1]),
        .O(Logical_Operator_out10_carry_i_14_n_0));
  LUT6 #(
    .INIT(64'h22222222BBB222B2)) 
    Logical_Operator_out10_carry_i_2
       (.I0(\delayMatch5_reg_reg[1][11] ),
        .I1(Add2_out1_1[11]),
        .I2(\Delay2_out1_reg[13] [10]),
        .I3(PWM_en_AXI_2_reg),
        .I4(\Delay2_out1_reg[13]_0 [10]),
        .I5(Add2_out1_1[10]),
        .O(Logical_Operator_out10_carry_i_2_n_0));
  LUT6 #(
    .INIT(64'h22222222BBB222B2)) 
    Logical_Operator_out10_carry_i_3
       (.I0(\delayMatch5_reg_reg[1][9] ),
        .I1(Add2_out1_1[9]),
        .I2(\Delay2_out1_reg[13] [8]),
        .I3(PWM_en_AXI_2_reg),
        .I4(\Delay2_out1_reg[13]_0 [8]),
        .I5(Add2_out1_1[8]),
        .O(Logical_Operator_out10_carry_i_3_n_0));
  LUT6 #(
    .INIT(64'h22222222BBB222B2)) 
    Logical_Operator_out10_carry_i_4
       (.I0(\delayMatch5_reg_reg[1][7] ),
        .I1(Add2_out1_1[7]),
        .I2(\Delay2_out1_reg[13] [6]),
        .I3(PWM_en_AXI_2_reg),
        .I4(\Delay2_out1_reg[13]_0 [6]),
        .I5(Add2_out1_1[6]),
        .O(Logical_Operator_out10_carry_i_4_n_0));
  LUT6 #(
    .INIT(64'h22222222BBB222B2)) 
    Logical_Operator_out10_carry_i_5
       (.I0(\delayMatch5_reg_reg[1][5] ),
        .I1(Add2_out1_1[5]),
        .I2(\Delay2_out1_reg[13] [4]),
        .I3(PWM_en_AXI_2_reg),
        .I4(\Delay2_out1_reg[13]_0 [4]),
        .I5(Add2_out1_1[4]),
        .O(Logical_Operator_out10_carry_i_5_n_0));
  LUT6 #(
    .INIT(64'h22222222BBB222B2)) 
    Logical_Operator_out10_carry_i_6
       (.I0(\delayMatch5_reg_reg[1][3] ),
        .I1(Add2_out1_1[3]),
        .I2(\Delay2_out1_reg[13] [2]),
        .I3(PWM_en_AXI_2_reg),
        .I4(\Delay2_out1_reg[13]_0 [2]),
        .I5(Add2_out1_1[2]),
        .O(Logical_Operator_out10_carry_i_6_n_0));
  LUT6 #(
    .INIT(64'h7577755510111000)) 
    Logical_Operator_out10_carry_i_7
       (.I0(Add2_out1_1[1]),
        .I1(Add1_out1_1[0]),
        .I2(\Delay2_out1_reg[13]_0 [0]),
        .I3(PWM_en_AXI_2_reg),
        .I4(\Delay2_out1_reg[13] [0]),
        .I5(\delayMatch5_reg_reg[1][1] ),
        .O(Logical_Operator_out10_carry_i_7_n_0));
  LUT6 #(
    .INIT(64'hA95900000000A959)) 
    Logical_Operator_out10_carry_i_8
       (.I0(Add2_out1_1[12]),
        .I1(\Delay2_out1_reg[13] [12]),
        .I2(PWM_en_AXI_2_reg),
        .I3(\Delay2_out1_reg[13]_0 [12]),
        .I4(\delayMatch5_reg_reg[1][13] ),
        .I5(Add2_out1_1[13]),
        .O(Logical_Operator_out10_carry_i_8_n_0));
  LUT6 #(
    .INIT(64'hA95900000000A959)) 
    Logical_Operator_out10_carry_i_9
       (.I0(Add2_out1_1[10]),
        .I1(\Delay2_out1_reg[13] [10]),
        .I2(PWM_en_AXI_2_reg),
        .I3(\Delay2_out1_reg[13]_0 [10]),
        .I4(\delayMatch5_reg_reg[1][11] ),
        .I5(Add2_out1_1[11]),
        .O(Logical_Operator_out10_carry_i_9_n_0));
  (* COMPARATOR_THRESHOLD = "11" *) 
  CARRY8 Logical_Operator_out11_carry
       (.CI(1'b0),
        .CI_TOP(1'b0),
        .CO({NLW_Logical_Operator_out11_carry_CO_UNCONNECTED[7],Relational_Operator2_relop1,Logical_Operator_out11_carry_n_2,Logical_Operator_out11_carry_n_3,Logical_Operator_out11_carry_n_4,Logical_Operator_out11_carry_n_5,Logical_Operator_out11_carry_n_6,Logical_Operator_out11_carry_n_7}),
        .DI({1'b0,Logical_Operator_out11_carry_i_1_n_0,Logical_Operator_out11_carry_i_2_n_0,i__carry_i_3_n_0,i__carry_i_4_n_0,i__carry_i_5_n_0,i__carry_i_6_n_0,i__carry_i_7_n_0}),
        .O(NLW_Logical_Operator_out11_carry_O_UNCONNECTED[7:0]),
        .S({1'b0,Logical_Operator_out11_carry_i_3_n_0,Logical_Operator_out11_carry_i_4_n_0,Logical_Operator_out11_carry_i_5_n_0,Logical_Operator_out11_carry_i_6_n_0,Logical_Operator_out11_carry_i_7_n_0,Logical_Operator_out11_carry_i_8_n_0,Logical_Operator_out11_carry_i_9_n_0}));
  LUT6 #(
    .INIT(64'h222222B2B2B222B2)) 
    Logical_Operator_out11_carry_i_1
       (.I0(\delayMatch5_reg_reg[1][13] ),
        .I1(Add1_out1_1[13]),
        .I2(Add1_out1_1[12]),
        .I3(\Delay2_out1_reg[13] [12]),
        .I4(PWM_en_AXI_2_reg),
        .I5(\Delay2_out1_reg[13]_0 [12]),
        .O(Logical_Operator_out11_carry_i_1_n_0));
  LUT6 #(
    .INIT(64'h222222B2B2B222B2)) 
    Logical_Operator_out11_carry_i_2
       (.I0(Add1_out1_1[11]),
        .I1(\delayMatch5_reg_reg[1][11] ),
        .I2(Add1_out1_1[10]),
        .I3(\Delay2_out1_reg[13] [10]),
        .I4(PWM_en_AXI_2_reg),
        .I5(\Delay2_out1_reg[13]_0 [10]),
        .O(Logical_Operator_out11_carry_i_2_n_0));
  LUT6 #(
    .INIT(64'hA95900000000A959)) 
    Logical_Operator_out11_carry_i_3
       (.I0(Add1_out1_1[12]),
        .I1(\Delay2_out1_reg[13] [12]),
        .I2(PWM_en_AXI_2_reg),
        .I3(\Delay2_out1_reg[13]_0 [12]),
        .I4(\delayMatch5_reg_reg[1][13] ),
        .I5(Add1_out1_1[13]),
        .O(Logical_Operator_out11_carry_i_3_n_0));
  LUT6 #(
    .INIT(64'hA95900000000A959)) 
    Logical_Operator_out11_carry_i_4
       (.I0(Add1_out1_1[10]),
        .I1(\Delay2_out1_reg[13] [10]),
        .I2(PWM_en_AXI_2_reg),
        .I3(\Delay2_out1_reg[13]_0 [10]),
        .I4(\delayMatch5_reg_reg[1][11] ),
        .I5(Add1_out1_1[11]),
        .O(Logical_Operator_out11_carry_i_4_n_0));
  LUT6 #(
    .INIT(64'hA95900000000A959)) 
    Logical_Operator_out11_carry_i_5
       (.I0(Add1_out1_1[8]),
        .I1(\Delay2_out1_reg[13] [8]),
        .I2(PWM_en_AXI_2_reg),
        .I3(\Delay2_out1_reg[13]_0 [8]),
        .I4(\delayMatch5_reg_reg[1][9] ),
        .I5(Add1_out1_1[9]),
        .O(Logical_Operator_out11_carry_i_5_n_0));
  LUT6 #(
    .INIT(64'hA95900000000A959)) 
    Logical_Operator_out11_carry_i_6
       (.I0(Add1_out1_1[6]),
        .I1(\Delay2_out1_reg[13] [6]),
        .I2(PWM_en_AXI_2_reg),
        .I3(\Delay2_out1_reg[13]_0 [6]),
        .I4(\delayMatch5_reg_reg[1][7] ),
        .I5(Add1_out1_1[7]),
        .O(Logical_Operator_out11_carry_i_6_n_0));
  LUT6 #(
    .INIT(64'hA95900000000A959)) 
    Logical_Operator_out11_carry_i_7
       (.I0(Add1_out1_1[4]),
        .I1(\Delay2_out1_reg[13] [4]),
        .I2(PWM_en_AXI_2_reg),
        .I3(\Delay2_out1_reg[13]_0 [4]),
        .I4(\delayMatch5_reg_reg[1][5] ),
        .I5(Add1_out1_1[5]),
        .O(Logical_Operator_out11_carry_i_7_n_0));
  LUT6 #(
    .INIT(64'hA95900000000A959)) 
    Logical_Operator_out11_carry_i_8
       (.I0(Add1_out1_1[2]),
        .I1(\Delay2_out1_reg[13] [2]),
        .I2(PWM_en_AXI_2_reg),
        .I3(\Delay2_out1_reg[13]_0 [2]),
        .I4(\delayMatch5_reg_reg[1][3] ),
        .I5(Add1_out1_1[3]),
        .O(Logical_Operator_out11_carry_i_8_n_0));
  LUT6 #(
    .INIT(64'hE21D00000000E21D)) 
    Logical_Operator_out11_carry_i_9
       (.I0(\Delay2_out1_reg[13] [0]),
        .I1(PWM_en_AXI_2_reg),
        .I2(\Delay2_out1_reg[13]_0 [0]),
        .I3(Add1_out1_1[0]),
        .I4(\delayMatch5_reg_reg[1][1] ),
        .I5(Add1_out1_1[1]),
        .O(Logical_Operator_out11_carry_i_9_n_0));
  LUT4 #(
    .INIT(16'h9009)) 
    Period_Center0_carry_i_1
       (.I0(HDL_Counter2_count_reg[18]),
        .I1(maximum_counter_value_1[18]),
        .I2(HDL_Counter2_count_reg[19]),
        .I3(maximum_counter_value_1[19]),
        .O(\HDL_Counter2_count_reg[18] [6]));
  LUT6 #(
    .INIT(64'h9009000000009009)) 
    Period_Center0_carry_i_2
       (.I0(maximum_counter_value_1[17]),
        .I1(HDL_Counter2_count_reg[17]),
        .I2(maximum_counter_value_1[16]),
        .I3(HDL_Counter2_count_reg[16]),
        .I4(HDL_Counter2_count_reg[15]),
        .I5(maximum_counter_value_1[15]),
        .O(\HDL_Counter2_count_reg[18] [5]));
  LUT6 #(
    .INIT(64'h9009000000009009)) 
    Period_Center0_carry_i_3
       (.I0(maximum_counter_value_1[13]),
        .I1(HDL_Counter2_count_reg[13]),
        .I2(maximum_counter_value_1[14]),
        .I3(HDL_Counter2_count_reg[14]),
        .I4(HDL_Counter2_count_reg[12]),
        .I5(maximum_counter_value_1[12]),
        .O(\HDL_Counter2_count_reg[18] [4]));
  LUT6 #(
    .INIT(64'h9009000000009009)) 
    Period_Center0_carry_i_4
       (.I0(maximum_counter_value_1[11]),
        .I1(HDL_Counter2_count_reg[11]),
        .I2(maximum_counter_value_1[10]),
        .I3(HDL_Counter2_count_reg[10]),
        .I4(HDL_Counter2_count_reg[9]),
        .I5(maximum_counter_value_1[9]),
        .O(\HDL_Counter2_count_reg[18] [3]));
  LUT6 #(
    .INIT(64'h9009000000009009)) 
    Period_Center0_carry_i_5
       (.I0(maximum_counter_value_1[7]),
        .I1(HDL_Counter2_count_reg[7]),
        .I2(maximum_counter_value_1[8]),
        .I3(HDL_Counter2_count_reg[8]),
        .I4(HDL_Counter2_count_reg[6]),
        .I5(maximum_counter_value_1[6]),
        .O(\HDL_Counter2_count_reg[18] [2]));
  LUT6 #(
    .INIT(64'h9009000000009009)) 
    Period_Center0_carry_i_6
       (.I0(maximum_counter_value_1[5]),
        .I1(HDL_Counter2_count_reg[5]),
        .I2(maximum_counter_value_1[4]),
        .I3(HDL_Counter2_count_reg[4]),
        .I4(HDL_Counter2_count_reg[3]),
        .I5(maximum_counter_value_1[3]),
        .O(\HDL_Counter2_count_reg[18] [1]));
  LUT6 #(
    .INIT(64'h9009000000009009)) 
    Period_Center0_carry_i_7
       (.I0(maximum_counter_value_1[1]),
        .I1(HDL_Counter2_count_reg[1]),
        .I2(maximum_counter_value_1[2]),
        .I3(HDL_Counter2_count_reg[2]),
        .I4(HDL_Counter2_count_reg[0]),
        .I5(maximum_counter_value_1[0]),
        .O(\HDL_Counter2_count_reg[18] [0]));
  (* SOFT_HLUTNM = "soft_lutpair49" *) 
  LUT3 #(
    .INIT(8'h02)) 
    \Saturation1_out1_1[11]_i_1__1 
       (.I0(Q[11]),
        .I1(CO),
        .I2(Q[13]),
        .O(Saturation1_out1[11]));
  (* SOFT_HLUTNM = "soft_lutpair42" *) 
  LUT3 #(
    .INIT(8'hBA)) 
    \Saturation1_out1_1[12]_i_1 
       (.I0(CO),
        .I1(Q[13]),
        .I2(Q[12]),
        .O(Saturation1_out1[12]));
  FDRE \Saturation1_out1_1_reg[11] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Saturation1_out1[11]),
        .Q(Saturation1_out1_1[11]),
        .R(RSTP));
  FDRE \Saturation1_out1_1_reg[12] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Saturation1_out1[12]),
        .Q(Saturation1_out1_1[12]),
        .R(RSTP));
  LUT5 #(
    .INIT(32'hAAAEEEAE)) 
    i__carry_i_1
       (.I0(\delayMatch5_reg_reg[1][13] ),
        .I1(Saturation1_out1_1[12]),
        .I2(\Delay2_out1_reg[13] [12]),
        .I3(PWM_en_AXI_2_reg),
        .I4(\Delay2_out1_reg[13]_0 [12]),
        .O(i__carry_i_1_n_0));
  LUT6 #(
    .INIT(64'hA95900000000A959)) 
    i__carry_i_10__1
       (.I0(Add1_out1_1[8]),
        .I1(\Delay2_out1_reg[13] [8]),
        .I2(PWM_en_AXI_2_reg),
        .I3(\Delay2_out1_reg[13]_0 [8]),
        .I4(\delayMatch5_reg_reg[1][9] ),
        .I5(Add1_out1_1[9]),
        .O(i__carry_i_10__1_n_0));
  LUT6 #(
    .INIT(64'hA95900000000A959)) 
    i__carry_i_11__1
       (.I0(Add1_out1_1[6]),
        .I1(\Delay2_out1_reg[13] [6]),
        .I2(PWM_en_AXI_2_reg),
        .I3(\Delay2_out1_reg[13]_0 [6]),
        .I4(\delayMatch5_reg_reg[1][7] ),
        .I5(Add1_out1_1[7]),
        .O(i__carry_i_11__1_n_0));
  LUT6 #(
    .INIT(64'hA95900000000A959)) 
    i__carry_i_12__1
       (.I0(Add1_out1_1[4]),
        .I1(\Delay2_out1_reg[13] [4]),
        .I2(PWM_en_AXI_2_reg),
        .I3(\Delay2_out1_reg[13]_0 [4]),
        .I4(\delayMatch5_reg_reg[1][5] ),
        .I5(Add1_out1_1[5]),
        .O(i__carry_i_12__1_n_0));
  LUT6 #(
    .INIT(64'hA95900000000A959)) 
    i__carry_i_13__1
       (.I0(Add1_out1_1[2]),
        .I1(\Delay2_out1_reg[13] [2]),
        .I2(PWM_en_AXI_2_reg),
        .I3(\Delay2_out1_reg[13]_0 [2]),
        .I4(\delayMatch5_reg_reg[1][3] ),
        .I5(Add1_out1_1[3]),
        .O(i__carry_i_13__1_n_0));
  LUT6 #(
    .INIT(64'hE21D00000000E21D)) 
    i__carry_i_14__1
       (.I0(\Delay2_out1_reg[13] [0]),
        .I1(PWM_en_AXI_2_reg),
        .I2(\Delay2_out1_reg[13]_0 [0]),
        .I3(Add1_out1_1[0]),
        .I4(\delayMatch5_reg_reg[1][1] ),
        .I5(Add1_out1_1[1]),
        .O(i__carry_i_14__1_n_0));
  LUT6 #(
    .INIT(64'h222222B2B2B222B2)) 
    i__carry_i_2
       (.I0(Saturation1_out1_1[11]),
        .I1(\delayMatch5_reg_reg[1][11] ),
        .I2(Add1_out1_1[10]),
        .I3(\Delay2_out1_reg[13] [10]),
        .I4(PWM_en_AXI_2_reg),
        .I5(\Delay2_out1_reg[13]_0 [10]),
        .O(i__carry_i_2_n_0));
  LUT6 #(
    .INIT(64'h222222B2B2B222B2)) 
    i__carry_i_3
       (.I0(Add1_out1_1[9]),
        .I1(\delayMatch5_reg_reg[1][9] ),
        .I2(Add1_out1_1[8]),
        .I3(\Delay2_out1_reg[13] [8]),
        .I4(PWM_en_AXI_2_reg),
        .I5(\Delay2_out1_reg[13]_0 [8]),
        .O(i__carry_i_3_n_0));
  LUT6 #(
    .INIT(64'h222222B2B2B222B2)) 
    i__carry_i_4
       (.I0(Add1_out1_1[7]),
        .I1(\delayMatch5_reg_reg[1][7] ),
        .I2(Add1_out1_1[6]),
        .I3(\Delay2_out1_reg[13] [6]),
        .I4(PWM_en_AXI_2_reg),
        .I5(\Delay2_out1_reg[13]_0 [6]),
        .O(i__carry_i_4_n_0));
  LUT6 #(
    .INIT(64'h222222B2B2B222B2)) 
    i__carry_i_5
       (.I0(Add1_out1_1[5]),
        .I1(\delayMatch5_reg_reg[1][5] ),
        .I2(Add1_out1_1[4]),
        .I3(\Delay2_out1_reg[13] [4]),
        .I4(PWM_en_AXI_2_reg),
        .I5(\Delay2_out1_reg[13]_0 [4]),
        .O(i__carry_i_5_n_0));
  LUT6 #(
    .INIT(64'h222222B2B2B222B2)) 
    i__carry_i_6
       (.I0(Add1_out1_1[3]),
        .I1(\delayMatch5_reg_reg[1][3] ),
        .I2(Add1_out1_1[2]),
        .I3(\Delay2_out1_reg[13] [2]),
        .I4(PWM_en_AXI_2_reg),
        .I5(\Delay2_out1_reg[13]_0 [2]),
        .O(i__carry_i_6_n_0));
  LUT6 #(
    .INIT(64'h222222B2B2B222B2)) 
    i__carry_i_7
       (.I0(Add1_out1_1[1]),
        .I1(\delayMatch5_reg_reg[1][1] ),
        .I2(Add1_out1_1[0]),
        .I3(\Delay2_out1_reg[13] [0]),
        .I4(PWM_en_AXI_2_reg),
        .I5(\Delay2_out1_reg[13]_0 [0]),
        .O(i__carry_i_7_n_0));
  LUT5 #(
    .INIT(32'h0000A959)) 
    i__carry_i_8
       (.I0(Saturation1_out1_1[12]),
        .I1(\Delay2_out1_reg[13] [12]),
        .I2(PWM_en_AXI_2_reg),
        .I3(\Delay2_out1_reg[13]_0 [12]),
        .I4(\delayMatch5_reg_reg[1][13] ),
        .O(i__carry_i_8_n_0));
  LUT6 #(
    .INIT(64'hA95900000000A959)) 
    i__carry_i_9
       (.I0(Add1_out1_1[10]),
        .I1(\Delay2_out1_reg[13] [10]),
        .I2(PWM_en_AXI_2_reg),
        .I3(\Delay2_out1_reg[13]_0 [10]),
        .I4(\delayMatch5_reg_reg[1][11] ),
        .I5(Saturation1_out1_1[11]),
        .O(i__carry_i_9_n_0));
  (* SOFT_HLUTNM = "soft_lutpair43" *) 
  LUT3 #(
    .INIT(8'h02)) 
    \minus_out1_1[10]_i_1 
       (.I0(\minus_out1_1_reg[10]_0 ),
        .I1(CO),
        .I2(Q[13]),
        .O(minus_out1[10]));
  (* SOFT_HLUTNM = "soft_lutpair44" *) 
  LUT3 #(
    .INIT(8'h02)) 
    \minus_out1_1[11]_i_1 
       (.I0(\minus_out1_1_reg[11]_0 ),
        .I1(CO),
        .I2(Q[13]),
        .O(minus_out1[11]));
  (* SOFT_HLUTNM = "soft_lutpair39" *) 
  LUT5 #(
    .INIT(32'hFFFF001E)) 
    \minus_out1_1[12]_i_1__1 
       (.I0(\min_pulse_width_AXI_1_reg[9] ),
        .I1(Q[11]),
        .I2(Q[12]),
        .I3(Q[13]),
        .I4(CO),
        .O(minus_out1[12]));
  (* SOFT_HLUTNM = "soft_lutpair39" *) 
  LUT5 #(
    .INIT(32'hFFFF00FE)) 
    \minus_out1_1[13]_i_1__1 
       (.I0(Q[11]),
        .I1(\min_pulse_width_AXI_1_reg[9] ),
        .I2(Q[12]),
        .I3(Q[13]),
        .I4(CO),
        .O(minus_out1[13]));
  LUT6 #(
    .INIT(64'hFFFFFFFFFFFFFFFE)) 
    \minus_out1_1[13]_i_2 
       (.I0(Q[9]),
        .I1(Q[7]),
        .I2(\minus_out1_1_reg[7]_0 ),
        .I3(Q[6]),
        .I4(Q[8]),
        .I5(Q[10]),
        .O(\min_pulse_width_AXI_1_reg[9] ));
  (* SOFT_HLUTNM = "soft_lutpair40" *) 
  LUT4 #(
    .INIT(16'h0006)) 
    \minus_out1_1[1]_i_1__1 
       (.I0(Q[1]),
        .I1(Q[0]),
        .I2(CO),
        .I3(Q[13]),
        .O(minus_out1[1]));
  (* SOFT_HLUTNM = "soft_lutpair40" *) 
  LUT5 #(
    .INIT(32'h00000056)) 
    \minus_out1_1[2]_i_1 
       (.I0(Q[2]),
        .I1(Q[0]),
        .I2(Q[1]),
        .I3(CO),
        .I4(Q[13]),
        .O(minus_out1[2]));
  LUT5 #(
    .INIT(32'h00005556)) 
    \minus_out1_1[3]_i_1 
       (.I0(Q[3]),
        .I1(Q[1]),
        .I2(Q[0]),
        .I3(Q[2]),
        .I4(\minus_out1_1[5]_i_2__1_n_0 ),
        .O(minus_out1[3]));
  LUT6 #(
    .INIT(64'h0000000055555556)) 
    \minus_out1_1[4]_i_1 
       (.I0(Q[4]),
        .I1(Q[2]),
        .I2(Q[0]),
        .I3(Q[1]),
        .I4(Q[3]),
        .I5(\minus_out1_1[5]_i_2__1_n_0 ),
        .O(minus_out1[4]));
  LUT6 #(
    .INIT(64'h0000000055555556)) 
    \minus_out1_1[5]_i_1 
       (.I0(Q[5]),
        .I1(Q[3]),
        .I2(\minus_out1_1_reg[5]_0 ),
        .I3(Q[2]),
        .I4(Q[4]),
        .I5(\minus_out1_1[5]_i_2__1_n_0 ),
        .O(minus_out1[5]));
  LUT2 #(
    .INIT(4'hE)) 
    \minus_out1_1[5]_i_2__1 
       (.I0(Q[13]),
        .I1(CO),
        .O(\minus_out1_1[5]_i_2__1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair42" *) 
  LUT3 #(
    .INIT(8'h02)) 
    \minus_out1_1[6]_i_1 
       (.I0(\minus_out1_1_reg[6]_0 ),
        .I1(CO),
        .I2(Q[13]),
        .O(minus_out1[6]));
  (* SOFT_HLUTNM = "soft_lutpair38" *) 
  LUT5 #(
    .INIT(32'h0000001E)) 
    \minus_out1_1[7]_i_1__1 
       (.I0(Q[6]),
        .I1(\minus_out1_1_reg[7]_0 ),
        .I2(Q[7]),
        .I3(CO),
        .I4(Q[13]),
        .O(minus_out1[7]));
  LUT6 #(
    .INIT(64'h00000000000001FE)) 
    \minus_out1_1[8]_i_1__1 
       (.I0(Q[7]),
        .I1(\minus_out1_1_reg[7]_0 ),
        .I2(Q[6]),
        .I3(Q[8]),
        .I4(CO),
        .I5(Q[13]),
        .O(minus_out1[8]));
  (* SOFT_HLUTNM = "soft_lutpair43" *) 
  LUT3 #(
    .INIT(8'h02)) 
    \minus_out1_1[9]_i_1 
       (.I0(\minus_out1_1_reg[9]_0 ),
        .I1(CO),
        .I2(Q[13]),
        .O(minus_out1[9]));
  FDRE \minus_out1_1_reg[10] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(minus_out1[10]),
        .Q(minus_out1_1[10]),
        .R(RSTP));
  FDRE \minus_out1_1_reg[11] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(minus_out1[11]),
        .Q(minus_out1_1[11]),
        .R(RSTP));
  FDRE \minus_out1_1_reg[12] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(minus_out1[12]),
        .Q(minus_out1_1[12]),
        .R(RSTP));
  FDRE \minus_out1_1_reg[13] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(minus_out1[13]),
        .Q(minus_out1_1[13]),
        .R(RSTP));
  FDRE \minus_out1_1_reg[1] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(minus_out1[1]),
        .Q(minus_out1_1[1]),
        .R(RSTP));
  FDRE \minus_out1_1_reg[2] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(minus_out1[2]),
        .Q(minus_out1_1[2]),
        .R(RSTP));
  FDRE \minus_out1_1_reg[3] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(minus_out1[3]),
        .Q(minus_out1_1[3]),
        .R(RSTP));
  FDRE \minus_out1_1_reg[4] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(minus_out1[4]),
        .Q(minus_out1_1[4]),
        .R(RSTP));
  FDRE \minus_out1_1_reg[5] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(minus_out1[5]),
        .Q(minus_out1_1[5]),
        .R(RSTP));
  FDRE \minus_out1_1_reg[6] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(minus_out1[6]),
        .Q(minus_out1_1[6]),
        .R(RSTP));
  FDRE \minus_out1_1_reg[7] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(minus_out1[7]),
        .Q(minus_out1_1[7]),
        .R(RSTP));
  FDRE \minus_out1_1_reg[8] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(minus_out1[8]),
        .Q(minus_out1_1[8]),
        .R(RSTP));
  FDRE \minus_out1_1_reg[9] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(minus_out1[9]),
        .Q(minus_out1_1[9]),
        .R(RSTP));
  LUT5 #(
    .INIT(32'hFFFF4540)) 
    modulating_signal_in_clock_cycles_1_reg_i_1
       (.I0(Logical_Operator_out1__1),
        .I1(\Delay2_out1_reg[13]_0 [13]),
        .I2(PWM_en_AXI_2_reg),
        .I3(\Delay2_out1_reg[13] [13]),
        .I4(modulating_signal_in_clock_cycles_1_reg_i_17__1_n_0),
        .O(B[13]));
  LUT5 #(
    .INIT(32'hFFFF4540)) 
    modulating_signal_in_clock_cycles_1_reg_i_10
       (.I0(Logical_Operator_out1__1),
        .I1(\Delay2_out1_reg[13]_0 [4]),
        .I2(PWM_en_AXI_2_reg),
        .I3(\Delay2_out1_reg[13] [4]),
        .I4(modulating_signal_in_clock_cycles_1_reg_i_17__1_n_0),
        .O(B[4]));
  LUT5 #(
    .INIT(32'hBABBBAAA)) 
    modulating_signal_in_clock_cycles_1_reg_i_11
       (.I0(modulating_signal_in_clock_cycles_1_reg_i_18__1_n_0),
        .I1(Logical_Operator_out1__1),
        .I2(\Delay2_out1_reg[13]_0 [3]),
        .I3(PWM_en_AXI_2_reg),
        .I4(\Delay2_out1_reg[13] [3]),
        .O(B[3]));
  LUT5 #(
    .INIT(32'hFFFF4540)) 
    modulating_signal_in_clock_cycles_1_reg_i_12
       (.I0(Logical_Operator_out1__1),
        .I1(\Delay2_out1_reg[13]_0 [2]),
        .I2(PWM_en_AXI_2_reg),
        .I3(\Delay2_out1_reg[13] [2]),
        .I4(modulating_signal_in_clock_cycles_1_reg_i_17__1_n_0),
        .O(B[2]));
  LUT5 #(
    .INIT(32'hFFFF4540)) 
    modulating_signal_in_clock_cycles_1_reg_i_13
       (.I0(Logical_Operator_out1__1),
        .I1(\Delay2_out1_reg[13]_0 [1]),
        .I2(PWM_en_AXI_2_reg),
        .I3(\Delay2_out1_reg[13] [1]),
        .I4(modulating_signal_in_clock_cycles_1_reg_i_17__1_n_0),
        .O(B[1]));
  LUT6 #(
    .INIT(64'h00FFFFFFB8B8B8B8)) 
    modulating_signal_in_clock_cycles_1_reg_i_14
       (.I0(\Delay2_out1_reg[13]_0 [0]),
        .I1(PWM_en_AXI_2_reg),
        .I2(\Delay2_out1_reg[13] [0]),
        .I3(Relational_Operator1_relop1),
        .I4(Relational_Operator_relop1),
        .I5(Logical_Operator_out1__1),
        .O(B[0]));
  (* SOFT_HLUTNM = "soft_lutpair41" *) 
  LUT4 #(
    .INIT(16'hFEEE)) 
    modulating_signal_in_clock_cycles_1_reg_i_15__1
       (.I0(Relational_Operator2_relop1),
        .I1(Relational_Operator3_relop1),
        .I2(Relational_Operator_relop1),
        .I3(Relational_Operator1_relop1),
        .O(Logical_Operator_out1__1));
  LUT6 #(
    .INIT(64'hFFFFFFFF00008000)) 
    modulating_signal_in_clock_cycles_1_reg_i_16__1
       (.I0(\Delay2_out1_reg[0] ),
        .I1(HDL_Counter2_count_reg_1_sn_1),
        .I2(HDL_Counter2_count_reg_16_sn_1),
        .I3(D),
        .I4(HDL_Counter2_count_reg[19]),
        .I5(\Delay2_out1_reg[13]_2 ),
        .O(PWM_en_AXI_2_reg));
  LUT3 #(
    .INIT(8'h70)) 
    modulating_signal_in_clock_cycles_1_reg_i_17__1
       (.I0(Relational_Operator1_relop1),
        .I1(Relational_Operator_relop1),
        .I2(Relational_Operator2_relop1),
        .O(modulating_signal_in_clock_cycles_1_reg_i_17__1_n_0));
  (* SOFT_HLUTNM = "soft_lutpair41" *) 
  LUT4 #(
    .INIT(16'h0070)) 
    modulating_signal_in_clock_cycles_1_reg_i_18__1
       (.I0(Relational_Operator1_relop1),
        .I1(Relational_Operator_relop1),
        .I2(Relational_Operator3_relop1),
        .I3(Relational_Operator2_relop1),
        .O(modulating_signal_in_clock_cycles_1_reg_i_18__1_n_0));
  LUT5 #(
    .INIT(32'hBABBBAAA)) 
    modulating_signal_in_clock_cycles_1_reg_i_2
       (.I0(modulating_signal_in_clock_cycles_1_reg_i_18__1_n_0),
        .I1(Logical_Operator_out1__1),
        .I2(\Delay2_out1_reg[13]_0 [12]),
        .I3(PWM_en_AXI_2_reg),
        .I4(\Delay2_out1_reg[13] [12]),
        .O(B[12]));
  LUT5 #(
    .INIT(32'hFFFF4540)) 
    modulating_signal_in_clock_cycles_1_reg_i_3
       (.I0(Logical_Operator_out1__1),
        .I1(\Delay2_out1_reg[13]_0 [11]),
        .I2(PWM_en_AXI_2_reg),
        .I3(\Delay2_out1_reg[13] [11]),
        .I4(modulating_signal_in_clock_cycles_1_reg_i_17__1_n_0),
        .O(B[11]));
  LUT5 #(
    .INIT(32'hFFFF4540)) 
    modulating_signal_in_clock_cycles_1_reg_i_4
       (.I0(Logical_Operator_out1__1),
        .I1(\Delay2_out1_reg[13]_0 [10]),
        .I2(PWM_en_AXI_2_reg),
        .I3(\Delay2_out1_reg[13] [10]),
        .I4(modulating_signal_in_clock_cycles_1_reg_i_17__1_n_0),
        .O(B[10]));
  LUT5 #(
    .INIT(32'hFFFF4540)) 
    modulating_signal_in_clock_cycles_1_reg_i_5
       (.I0(Logical_Operator_out1__1),
        .I1(\Delay2_out1_reg[13]_0 [9]),
        .I2(PWM_en_AXI_2_reg),
        .I3(\Delay2_out1_reg[13] [9]),
        .I4(modulating_signal_in_clock_cycles_1_reg_i_17__1_n_0),
        .O(B[9]));
  LUT5 #(
    .INIT(32'hFFFF4540)) 
    modulating_signal_in_clock_cycles_1_reg_i_6
       (.I0(Logical_Operator_out1__1),
        .I1(\Delay2_out1_reg[13]_0 [8]),
        .I2(PWM_en_AXI_2_reg),
        .I3(\Delay2_out1_reg[13] [8]),
        .I4(modulating_signal_in_clock_cycles_1_reg_i_17__1_n_0),
        .O(B[8]));
  LUT5 #(
    .INIT(32'hFFFF4540)) 
    modulating_signal_in_clock_cycles_1_reg_i_7
       (.I0(Logical_Operator_out1__1),
        .I1(\Delay2_out1_reg[13]_0 [7]),
        .I2(PWM_en_AXI_2_reg),
        .I3(\Delay2_out1_reg[13] [7]),
        .I4(modulating_signal_in_clock_cycles_1_reg_i_17__1_n_0),
        .O(B[7]));
  LUT5 #(
    .INIT(32'hFFFF4540)) 
    modulating_signal_in_clock_cycles_1_reg_i_8
       (.I0(Logical_Operator_out1__1),
        .I1(\Delay2_out1_reg[13]_0 [6]),
        .I2(PWM_en_AXI_2_reg),
        .I3(\Delay2_out1_reg[13] [6]),
        .I4(modulating_signal_in_clock_cycles_1_reg_i_17__1_n_0),
        .O(B[6]));
  LUT5 #(
    .INIT(32'hBABBBAAA)) 
    modulating_signal_in_clock_cycles_1_reg_i_9
       (.I0(modulating_signal_in_clock_cycles_1_reg_i_18__1_n_0),
        .I1(Logical_Operator_out1__1),
        .I2(\Delay2_out1_reg[13]_0 [5]),
        .I3(PWM_en_AXI_2_reg),
        .I4(\Delay2_out1_reg[13] [5]),
        .O(B[5]));
endmodule

(* ORIG_REF_NAME = "PWM_SS_3L_ip_src_Modulator_a" *) 
module zusys_PWM_SS_3L_ip_0_0_PWM_SS_3L_ip_src_Modulator_a
   (\reduced_reg_1_reg[1]_9 ,
    D,
    S,
    DI,
    \reduced_reg_1_reg[1][20]_0 ,
    \reduced_reg_reg[1][14]_0 ,
    \reduced_reg_reg[1][14]_1 ,
    \reduced_reg_reg[1][18]_0 ,
    \reduced_reg_reg[1][18]_1 ,
    \reduced_reg_reg[1][14]_2 ,
    \reduced_reg_reg[1][14]_3 ,
    \reduced_reg_reg[1][18]_2 ,
    \reduced_reg_reg[1][18]_3 ,
    CEP,
    IPCORE_CLK,
    RSTP,
    B,
    maximum_counter_value_1,
    HDL_Counter2_count_reg,
    Counter_Ctrl_out3,
    P,
    AND_out10_carry__0_0);
  output [20:0]\reduced_reg_1_reg[1]_9 ;
  output [1:0]D;
  output [3:0]S;
  output [0:0]DI;
  output [0:0]\reduced_reg_1_reg[1][20]_0 ;
  output [7:0]\reduced_reg_reg[1][14]_0 ;
  output [7:0]\reduced_reg_reg[1][14]_1 ;
  output [1:0]\reduced_reg_reg[1][18]_0 ;
  output [1:0]\reduced_reg_reg[1][18]_1 ;
  output [7:0]\reduced_reg_reg[1][14]_2 ;
  output [7:0]\reduced_reg_reg[1][14]_3 ;
  output [1:0]\reduced_reg_reg[1][18]_2 ;
  output [1:0]\reduced_reg_reg[1][18]_3 ;
  input CEP;
  input IPCORE_CLK;
  input RSTP;
  input [13:0]B;
  input [19:0]maximum_counter_value_1;
  input [19:0]HDL_Counter2_count_reg;
  input [20:0]Counter_Ctrl_out3;
  input [20:0]P;
  input [20:0]AND_out10_carry__0_0;

  wire [20:0]AND_out10_carry__0_0;
  wire AND_out10_carry__0_i_1_n_0;
  wire AND_out10_carry__0_i_2_n_0;
  wire AND_out10_carry__0_i_3_n_0;
  wire AND_out10_carry__0_i_4_n_0;
  wire AND_out10_carry__0_i_5_n_0;
  wire AND_out10_carry__0_i_6_n_0;
  wire AND_out10_carry__0_n_6;
  wire AND_out10_carry__0_n_7;
  wire AND_out10_carry_i_10_n_0;
  wire AND_out10_carry_i_11_n_0;
  wire AND_out10_carry_i_12_n_0;
  wire AND_out10_carry_i_13_n_0;
  wire AND_out10_carry_i_14_n_0;
  wire AND_out10_carry_i_15_n_0;
  wire AND_out10_carry_i_16_n_0;
  wire AND_out10_carry_i_1_n_0;
  wire AND_out10_carry_i_2_n_0;
  wire AND_out10_carry_i_3_n_0;
  wire AND_out10_carry_i_4_n_0;
  wire AND_out10_carry_i_5_n_0;
  wire AND_out10_carry_i_6_n_0;
  wire AND_out10_carry_i_7_n_0;
  wire AND_out10_carry_i_8_n_0;
  wire AND_out10_carry_i_9_n_0;
  wire AND_out10_carry_n_0;
  wire AND_out10_carry_n_1;
  wire AND_out10_carry_n_2;
  wire AND_out10_carry_n_3;
  wire AND_out10_carry_n_4;
  wire AND_out10_carry_n_5;
  wire AND_out10_carry_n_6;
  wire AND_out10_carry_n_7;
  wire \AND_out10_inferred__0/i__carry__0_n_6 ;
  wire \AND_out10_inferred__0/i__carry__0_n_7 ;
  wire \AND_out10_inferred__0/i__carry_n_0 ;
  wire \AND_out10_inferred__0/i__carry_n_1 ;
  wire \AND_out10_inferred__0/i__carry_n_2 ;
  wire \AND_out10_inferred__0/i__carry_n_3 ;
  wire \AND_out10_inferred__0/i__carry_n_4 ;
  wire \AND_out10_inferred__0/i__carry_n_5 ;
  wire \AND_out10_inferred__0/i__carry_n_6 ;
  wire \AND_out10_inferred__0/i__carry_n_7 ;
  wire [13:0]B;
  wire CEP;
  wire [20:0]Counter_Ctrl_out3;
  wire [1:0]D;
  wire [0:0]DI;
  wire [19:0]HDL_Counter2_count_reg;
  wire IPCORE_CLK;
  wire [20:0]P;
  wire RSTP;
  wire Relational_Operator1_relop1;
  wire Relational_Operator_relop1;
  wire [3:0]S;
  wire i__carry__0_i_1_n_0;
  wire i__carry__0_i_2_n_0;
  wire i__carry__0_i_3_n_0;
  wire i__carry__0_i_4_n_0;
  wire i__carry__0_i_5_n_0;
  wire i__carry_i_10__2_n_0;
  wire i__carry_i_11__2_n_0;
  wire i__carry_i_12__2_n_0;
  wire i__carry_i_13__2_n_0;
  wire i__carry_i_14__2_n_0;
  wire i__carry_i_15_n_0;
  wire i__carry_i_16_n_0;
  wire i__carry_i_1__2_n_0;
  wire i__carry_i_2__2_n_0;
  wire i__carry_i_3__2_n_0;
  wire i__carry_i_4__2_n_0;
  wire i__carry_i_5__2_n_0;
  wire i__carry_i_6__2_n_0;
  wire i__carry_i_7__2_n_0;
  wire i__carry_i_8__2_n_0;
  wire i__carry_i_9__2_n_0;
  wire [19:0]maximum_counter_value_1;
  wire [20:0]modulating_signal_in_clock_cycles_1_reg__0;
  wire modulating_signal_in_clock_cycles_1_reg_n_100;
  wire modulating_signal_in_clock_cycles_1_reg_n_101;
  wire modulating_signal_in_clock_cycles_1_reg_n_102;
  wire modulating_signal_in_clock_cycles_1_reg_n_103;
  wire modulating_signal_in_clock_cycles_1_reg_n_104;
  wire modulating_signal_in_clock_cycles_1_reg_n_105;
  wire modulating_signal_in_clock_cycles_1_reg_n_94;
  wire modulating_signal_in_clock_cycles_1_reg_n_95;
  wire modulating_signal_in_clock_cycles_1_reg_n_96;
  wire modulating_signal_in_clock_cycles_1_reg_n_97;
  wire modulating_signal_in_clock_cycles_1_reg_n_98;
  wire modulating_signal_in_clock_cycles_1_reg_n_99;
  wire [20:0]\reduced_reg_1_reg[0]_7 ;
  wire [0:0]\reduced_reg_1_reg[1][20]_0 ;
  wire [20:0]\reduced_reg_1_reg[1]_9 ;
  wire [19:0]\reduced_reg_reg[0]_6 ;
  wire [7:0]\reduced_reg_reg[1][14]_0 ;
  wire [7:0]\reduced_reg_reg[1][14]_1 ;
  wire [7:0]\reduced_reg_reg[1][14]_2 ;
  wire [7:0]\reduced_reg_reg[1][14]_3 ;
  wire [1:0]\reduced_reg_reg[1][18]_0 ;
  wire [1:0]\reduced_reg_reg[1][18]_1 ;
  wire [1:0]\reduced_reg_reg[1][18]_2 ;
  wire [1:0]\reduced_reg_reg[1][18]_3 ;
  wire [19:0]\reduced_reg_reg[1]_8 ;
  wire [7:0]NLW_AND_out10_carry_O_UNCONNECTED;
  wire [7:3]NLW_AND_out10_carry__0_CO_UNCONNECTED;
  wire [7:0]NLW_AND_out10_carry__0_O_UNCONNECTED;
  wire [7:0]\NLW_AND_out10_inferred__0/i__carry_O_UNCONNECTED ;
  wire [7:3]\NLW_AND_out10_inferred__0/i__carry__0_CO_UNCONNECTED ;
  wire [7:0]\NLW_AND_out10_inferred__0/i__carry__0_O_UNCONNECTED ;
  wire NLW_modulating_signal_in_clock_cycles_1_reg_CARRYCASCOUT_UNCONNECTED;
  wire NLW_modulating_signal_in_clock_cycles_1_reg_MULTSIGNOUT_UNCONNECTED;
  wire NLW_modulating_signal_in_clock_cycles_1_reg_OVERFLOW_UNCONNECTED;
  wire NLW_modulating_signal_in_clock_cycles_1_reg_PATTERNBDETECT_UNCONNECTED;
  wire NLW_modulating_signal_in_clock_cycles_1_reg_PATTERNDETECT_UNCONNECTED;
  wire NLW_modulating_signal_in_clock_cycles_1_reg_UNDERFLOW_UNCONNECTED;
  wire [29:0]NLW_modulating_signal_in_clock_cycles_1_reg_ACOUT_UNCONNECTED;
  wire [17:0]NLW_modulating_signal_in_clock_cycles_1_reg_BCOUT_UNCONNECTED;
  wire [3:0]NLW_modulating_signal_in_clock_cycles_1_reg_CARRYOUT_UNCONNECTED;
  wire [47:33]NLW_modulating_signal_in_clock_cycles_1_reg_P_UNCONNECTED;
  wire [47:0]NLW_modulating_signal_in_clock_cycles_1_reg_PCOUT_UNCONNECTED;
  wire [7:0]NLW_modulating_signal_in_clock_cycles_1_reg_XOROUT_UNCONNECTED;

  (* COMPARATOR_THRESHOLD = "11" *) 
  CARRY8 AND_out10_carry
       (.CI(1'b1),
        .CI_TOP(1'b0),
        .CO({AND_out10_carry_n_0,AND_out10_carry_n_1,AND_out10_carry_n_2,AND_out10_carry_n_3,AND_out10_carry_n_4,AND_out10_carry_n_5,AND_out10_carry_n_6,AND_out10_carry_n_7}),
        .DI({AND_out10_carry_i_1_n_0,AND_out10_carry_i_2_n_0,AND_out10_carry_i_3_n_0,AND_out10_carry_i_4_n_0,AND_out10_carry_i_5_n_0,AND_out10_carry_i_6_n_0,AND_out10_carry_i_7_n_0,AND_out10_carry_i_8_n_0}),
        .O(NLW_AND_out10_carry_O_UNCONNECTED[7:0]),
        .S({AND_out10_carry_i_9_n_0,AND_out10_carry_i_10_n_0,AND_out10_carry_i_11_n_0,AND_out10_carry_i_12_n_0,AND_out10_carry_i_13_n_0,AND_out10_carry_i_14_n_0,AND_out10_carry_i_15_n_0,AND_out10_carry_i_16_n_0}));
  (* COMPARATOR_THRESHOLD = "11" *) 
  CARRY8 AND_out10_carry__0
       (.CI(AND_out10_carry_n_0),
        .CI_TOP(1'b0),
        .CO({NLW_AND_out10_carry__0_CO_UNCONNECTED[7:3],Relational_Operator1_relop1,AND_out10_carry__0_n_6,AND_out10_carry__0_n_7}),
        .DI({1'b0,1'b0,1'b0,1'b0,1'b0,AND_out10_carry__0_i_1_n_0,AND_out10_carry__0_i_2_n_0,AND_out10_carry__0_i_3_n_0}),
        .O(NLW_AND_out10_carry__0_O_UNCONNECTED[7:0]),
        .S({1'b0,1'b0,1'b0,1'b0,1'b0,AND_out10_carry__0_i_4_n_0,AND_out10_carry__0_i_5_n_0,AND_out10_carry__0_i_6_n_0}));
  LUT2 #(
    .INIT(4'h2)) 
    AND_out10_carry__0_i_1
       (.I0(\reduced_reg_1_reg[1]_9 [20]),
        .I1(modulating_signal_in_clock_cycles_1_reg__0[20]),
        .O(AND_out10_carry__0_i_1_n_0));
  LUT2 #(
    .INIT(4'h2)) 
    AND_out10_carry__0_i_1__0
       (.I0(\reduced_reg_1_reg[1]_9 [20]),
        .I1(P[20]),
        .O(DI));
  LUT2 #(
    .INIT(4'h2)) 
    AND_out10_carry__0_i_1__1
       (.I0(\reduced_reg_1_reg[1]_9 [20]),
        .I1(AND_out10_carry__0_0[20]),
        .O(\reduced_reg_1_reg[1][20]_0 ));
  LUT4 #(
    .INIT(16'h2F02)) 
    AND_out10_carry__0_i_2
       (.I0(modulating_signal_in_clock_cycles_1_reg__0[18]),
        .I1(\reduced_reg_1_reg[1]_9 [18]),
        .I2(\reduced_reg_1_reg[1]_9 [19]),
        .I3(modulating_signal_in_clock_cycles_1_reg__0[19]),
        .O(AND_out10_carry__0_i_2_n_0));
  LUT4 #(
    .INIT(16'h2F02)) 
    AND_out10_carry__0_i_3
       (.I0(modulating_signal_in_clock_cycles_1_reg__0[16]),
        .I1(\reduced_reg_1_reg[1]_9 [16]),
        .I2(\reduced_reg_1_reg[1]_9 [17]),
        .I3(modulating_signal_in_clock_cycles_1_reg__0[17]),
        .O(AND_out10_carry__0_i_3_n_0));
  LUT2 #(
    .INIT(4'h9)) 
    AND_out10_carry__0_i_4
       (.I0(modulating_signal_in_clock_cycles_1_reg__0[20]),
        .I1(\reduced_reg_1_reg[1]_9 [20]),
        .O(AND_out10_carry__0_i_4_n_0));
  LUT4 #(
    .INIT(16'h9009)) 
    AND_out10_carry__0_i_5
       (.I0(modulating_signal_in_clock_cycles_1_reg__0[18]),
        .I1(\reduced_reg_1_reg[1]_9 [18]),
        .I2(modulating_signal_in_clock_cycles_1_reg__0[19]),
        .I3(\reduced_reg_1_reg[1]_9 [19]),
        .O(AND_out10_carry__0_i_5_n_0));
  LUT4 #(
    .INIT(16'h9009)) 
    AND_out10_carry__0_i_6
       (.I0(modulating_signal_in_clock_cycles_1_reg__0[16]),
        .I1(\reduced_reg_1_reg[1]_9 [16]),
        .I2(modulating_signal_in_clock_cycles_1_reg__0[17]),
        .I3(\reduced_reg_1_reg[1]_9 [17]),
        .O(AND_out10_carry__0_i_6_n_0));
  LUT4 #(
    .INIT(16'h2F02)) 
    AND_out10_carry_i_1
       (.I0(modulating_signal_in_clock_cycles_1_reg__0[14]),
        .I1(\reduced_reg_1_reg[1]_9 [14]),
        .I2(\reduced_reg_1_reg[1]_9 [15]),
        .I3(modulating_signal_in_clock_cycles_1_reg__0[15]),
        .O(AND_out10_carry_i_1_n_0));
  LUT4 #(
    .INIT(16'h9009)) 
    AND_out10_carry_i_10
       (.I0(modulating_signal_in_clock_cycles_1_reg__0[12]),
        .I1(\reduced_reg_1_reg[1]_9 [12]),
        .I2(modulating_signal_in_clock_cycles_1_reg__0[13]),
        .I3(\reduced_reg_1_reg[1]_9 [13]),
        .O(AND_out10_carry_i_10_n_0));
  LUT4 #(
    .INIT(16'h9009)) 
    AND_out10_carry_i_11
       (.I0(modulating_signal_in_clock_cycles_1_reg__0[10]),
        .I1(\reduced_reg_1_reg[1]_9 [10]),
        .I2(modulating_signal_in_clock_cycles_1_reg__0[11]),
        .I3(\reduced_reg_1_reg[1]_9 [11]),
        .O(AND_out10_carry_i_11_n_0));
  LUT4 #(
    .INIT(16'h9009)) 
    AND_out10_carry_i_12
       (.I0(modulating_signal_in_clock_cycles_1_reg__0[8]),
        .I1(\reduced_reg_1_reg[1]_9 [8]),
        .I2(modulating_signal_in_clock_cycles_1_reg__0[9]),
        .I3(\reduced_reg_1_reg[1]_9 [9]),
        .O(AND_out10_carry_i_12_n_0));
  LUT4 #(
    .INIT(16'h9009)) 
    AND_out10_carry_i_13
       (.I0(modulating_signal_in_clock_cycles_1_reg__0[6]),
        .I1(\reduced_reg_1_reg[1]_9 [6]),
        .I2(modulating_signal_in_clock_cycles_1_reg__0[7]),
        .I3(\reduced_reg_1_reg[1]_9 [7]),
        .O(AND_out10_carry_i_13_n_0));
  LUT4 #(
    .INIT(16'h9009)) 
    AND_out10_carry_i_14
       (.I0(modulating_signal_in_clock_cycles_1_reg__0[4]),
        .I1(\reduced_reg_1_reg[1]_9 [4]),
        .I2(modulating_signal_in_clock_cycles_1_reg__0[5]),
        .I3(\reduced_reg_1_reg[1]_9 [5]),
        .O(AND_out10_carry_i_14_n_0));
  LUT4 #(
    .INIT(16'h9009)) 
    AND_out10_carry_i_15
       (.I0(modulating_signal_in_clock_cycles_1_reg__0[2]),
        .I1(\reduced_reg_1_reg[1]_9 [2]),
        .I2(modulating_signal_in_clock_cycles_1_reg__0[3]),
        .I3(\reduced_reg_1_reg[1]_9 [3]),
        .O(AND_out10_carry_i_15_n_0));
  LUT4 #(
    .INIT(16'h9009)) 
    AND_out10_carry_i_16
       (.I0(modulating_signal_in_clock_cycles_1_reg__0[0]),
        .I1(\reduced_reg_1_reg[1]_9 [0]),
        .I2(modulating_signal_in_clock_cycles_1_reg__0[1]),
        .I3(\reduced_reg_1_reg[1]_9 [1]),
        .O(AND_out10_carry_i_16_n_0));
  LUT4 #(
    .INIT(16'h2F02)) 
    AND_out10_carry_i_2
       (.I0(modulating_signal_in_clock_cycles_1_reg__0[12]),
        .I1(\reduced_reg_1_reg[1]_9 [12]),
        .I2(\reduced_reg_1_reg[1]_9 [13]),
        .I3(modulating_signal_in_clock_cycles_1_reg__0[13]),
        .O(AND_out10_carry_i_2_n_0));
  LUT4 #(
    .INIT(16'h2F02)) 
    AND_out10_carry_i_3
       (.I0(modulating_signal_in_clock_cycles_1_reg__0[10]),
        .I1(\reduced_reg_1_reg[1]_9 [10]),
        .I2(\reduced_reg_1_reg[1]_9 [11]),
        .I3(modulating_signal_in_clock_cycles_1_reg__0[11]),
        .O(AND_out10_carry_i_3_n_0));
  LUT4 #(
    .INIT(16'h2F02)) 
    AND_out10_carry_i_4
       (.I0(modulating_signal_in_clock_cycles_1_reg__0[8]),
        .I1(\reduced_reg_1_reg[1]_9 [8]),
        .I2(\reduced_reg_1_reg[1]_9 [9]),
        .I3(modulating_signal_in_clock_cycles_1_reg__0[9]),
        .O(AND_out10_carry_i_4_n_0));
  LUT4 #(
    .INIT(16'h2F02)) 
    AND_out10_carry_i_5
       (.I0(modulating_signal_in_clock_cycles_1_reg__0[6]),
        .I1(\reduced_reg_1_reg[1]_9 [6]),
        .I2(\reduced_reg_1_reg[1]_9 [7]),
        .I3(modulating_signal_in_clock_cycles_1_reg__0[7]),
        .O(AND_out10_carry_i_5_n_0));
  LUT4 #(
    .INIT(16'h2F02)) 
    AND_out10_carry_i_6
       (.I0(modulating_signal_in_clock_cycles_1_reg__0[4]),
        .I1(\reduced_reg_1_reg[1]_9 [4]),
        .I2(\reduced_reg_1_reg[1]_9 [5]),
        .I3(modulating_signal_in_clock_cycles_1_reg__0[5]),
        .O(AND_out10_carry_i_6_n_0));
  LUT4 #(
    .INIT(16'h2F02)) 
    AND_out10_carry_i_7
       (.I0(modulating_signal_in_clock_cycles_1_reg__0[2]),
        .I1(\reduced_reg_1_reg[1]_9 [2]),
        .I2(\reduced_reg_1_reg[1]_9 [3]),
        .I3(modulating_signal_in_clock_cycles_1_reg__0[3]),
        .O(AND_out10_carry_i_7_n_0));
  LUT4 #(
    .INIT(16'h2F02)) 
    AND_out10_carry_i_8
       (.I0(modulating_signal_in_clock_cycles_1_reg__0[0]),
        .I1(\reduced_reg_1_reg[1]_9 [0]),
        .I2(\reduced_reg_1_reg[1]_9 [1]),
        .I3(modulating_signal_in_clock_cycles_1_reg__0[1]),
        .O(AND_out10_carry_i_8_n_0));
  LUT4 #(
    .INIT(16'h9009)) 
    AND_out10_carry_i_9
       (.I0(modulating_signal_in_clock_cycles_1_reg__0[14]),
        .I1(\reduced_reg_1_reg[1]_9 [14]),
        .I2(modulating_signal_in_clock_cycles_1_reg__0[15]),
        .I3(\reduced_reg_1_reg[1]_9 [15]),
        .O(AND_out10_carry_i_9_n_0));
  (* COMPARATOR_THRESHOLD = "11" *) 
  CARRY8 \AND_out10_inferred__0/i__carry 
       (.CI(1'b1),
        .CI_TOP(1'b0),
        .CO({\AND_out10_inferred__0/i__carry_n_0 ,\AND_out10_inferred__0/i__carry_n_1 ,\AND_out10_inferred__0/i__carry_n_2 ,\AND_out10_inferred__0/i__carry_n_3 ,\AND_out10_inferred__0/i__carry_n_4 ,\AND_out10_inferred__0/i__carry_n_5 ,\AND_out10_inferred__0/i__carry_n_6 ,\AND_out10_inferred__0/i__carry_n_7 }),
        .DI({i__carry_i_1__2_n_0,i__carry_i_2__2_n_0,i__carry_i_3__2_n_0,i__carry_i_4__2_n_0,i__carry_i_5__2_n_0,i__carry_i_6__2_n_0,i__carry_i_7__2_n_0,i__carry_i_8__2_n_0}),
        .O(\NLW_AND_out10_inferred__0/i__carry_O_UNCONNECTED [7:0]),
        .S({i__carry_i_9__2_n_0,i__carry_i_10__2_n_0,i__carry_i_11__2_n_0,i__carry_i_12__2_n_0,i__carry_i_13__2_n_0,i__carry_i_14__2_n_0,i__carry_i_15_n_0,i__carry_i_16_n_0}));
  (* COMPARATOR_THRESHOLD = "11" *) 
  CARRY8 \AND_out10_inferred__0/i__carry__0 
       (.CI(\AND_out10_inferred__0/i__carry_n_0 ),
        .CI_TOP(1'b0),
        .CO({\NLW_AND_out10_inferred__0/i__carry__0_CO_UNCONNECTED [7:3],Relational_Operator_relop1,\AND_out10_inferred__0/i__carry__0_n_6 ,\AND_out10_inferred__0/i__carry__0_n_7 }),
        .DI({1'b0,1'b0,1'b0,1'b0,1'b0,modulating_signal_in_clock_cycles_1_reg__0[20],i__carry__0_i_1_n_0,i__carry__0_i_2_n_0}),
        .O(\NLW_AND_out10_inferred__0/i__carry__0_O_UNCONNECTED [7:0]),
        .S({1'b0,1'b0,1'b0,1'b0,1'b0,i__carry__0_i_3_n_0,i__carry__0_i_4_n_0,i__carry__0_i_5_n_0}));
  LUT2 #(
    .INIT(4'h9)) 
    Add1_out1_carry__1_i_1
       (.I0(HDL_Counter2_count_reg[19]),
        .I1(maximum_counter_value_1[19]),
        .O(S[3]));
  LUT2 #(
    .INIT(4'h9)) 
    Add1_out1_carry__1_i_2
       (.I0(HDL_Counter2_count_reg[18]),
        .I1(maximum_counter_value_1[18]),
        .O(S[2]));
  LUT2 #(
    .INIT(4'h9)) 
    Add1_out1_carry__1_i_3
       (.I0(HDL_Counter2_count_reg[17]),
        .I1(maximum_counter_value_1[17]),
        .O(S[1]));
  LUT2 #(
    .INIT(4'h9)) 
    Add1_out1_carry__1_i_4
       (.I0(HDL_Counter2_count_reg[16]),
        .I1(maximum_counter_value_1[16]),
        .O(S[0]));
  (* SOFT_HLUTNM = "soft_lutpair50" *) 
  LUT2 #(
    .INIT(4'h2)) 
    \Switch3_out1_1[0]_i_2 
       (.I0(Relational_Operator1_relop1),
        .I1(Relational_Operator_relop1),
        .O(D[1]));
  (* SOFT_HLUTNM = "soft_lutpair50" *) 
  LUT1 #(
    .INIT(2'h2)) 
    \Switch3_out1_1[1]_i_1 
       (.I0(Relational_Operator1_relop1),
        .O(D[0]));
  LUT4 #(
    .INIT(16'h2F02)) 
    i__carry__0_i_1
       (.I0(\reduced_reg_reg[1]_8 [18]),
        .I1(modulating_signal_in_clock_cycles_1_reg__0[18]),
        .I2(modulating_signal_in_clock_cycles_1_reg__0[19]),
        .I3(\reduced_reg_reg[1]_8 [19]),
        .O(i__carry__0_i_1_n_0));
  LUT4 #(
    .INIT(16'h2F02)) 
    i__carry__0_i_1__0
       (.I0(\reduced_reg_reg[1]_8 [18]),
        .I1(P[18]),
        .I2(P[19]),
        .I3(\reduced_reg_reg[1]_8 [19]),
        .O(\reduced_reg_reg[1][18]_1 [1]));
  LUT4 #(
    .INIT(16'h2F02)) 
    i__carry__0_i_1__1
       (.I0(\reduced_reg_reg[1]_8 [18]),
        .I1(AND_out10_carry__0_0[18]),
        .I2(AND_out10_carry__0_0[19]),
        .I3(\reduced_reg_reg[1]_8 [19]),
        .O(\reduced_reg_reg[1][18]_3 [1]));
  LUT4 #(
    .INIT(16'h2F02)) 
    i__carry__0_i_2
       (.I0(\reduced_reg_reg[1]_8 [16]),
        .I1(modulating_signal_in_clock_cycles_1_reg__0[16]),
        .I2(modulating_signal_in_clock_cycles_1_reg__0[17]),
        .I3(\reduced_reg_reg[1]_8 [17]),
        .O(i__carry__0_i_2_n_0));
  LUT4 #(
    .INIT(16'h2F02)) 
    i__carry__0_i_2__0
       (.I0(\reduced_reg_reg[1]_8 [16]),
        .I1(P[16]),
        .I2(P[17]),
        .I3(\reduced_reg_reg[1]_8 [17]),
        .O(\reduced_reg_reg[1][18]_1 [0]));
  LUT4 #(
    .INIT(16'h2F02)) 
    i__carry__0_i_2__1
       (.I0(\reduced_reg_reg[1]_8 [16]),
        .I1(AND_out10_carry__0_0[16]),
        .I2(AND_out10_carry__0_0[17]),
        .I3(\reduced_reg_reg[1]_8 [17]),
        .O(\reduced_reg_reg[1][18]_3 [0]));
  LUT1 #(
    .INIT(2'h1)) 
    i__carry__0_i_3
       (.I0(modulating_signal_in_clock_cycles_1_reg__0[20]),
        .O(i__carry__0_i_3_n_0));
  LUT4 #(
    .INIT(16'h9009)) 
    i__carry__0_i_4
       (.I0(\reduced_reg_reg[1]_8 [18]),
        .I1(modulating_signal_in_clock_cycles_1_reg__0[18]),
        .I2(\reduced_reg_reg[1]_8 [19]),
        .I3(modulating_signal_in_clock_cycles_1_reg__0[19]),
        .O(i__carry__0_i_4_n_0));
  LUT4 #(
    .INIT(16'h9009)) 
    i__carry__0_i_4__0
       (.I0(\reduced_reg_reg[1]_8 [18]),
        .I1(P[18]),
        .I2(\reduced_reg_reg[1]_8 [19]),
        .I3(P[19]),
        .O(\reduced_reg_reg[1][18]_0 [1]));
  LUT4 #(
    .INIT(16'h9009)) 
    i__carry__0_i_4__1
       (.I0(\reduced_reg_reg[1]_8 [18]),
        .I1(AND_out10_carry__0_0[18]),
        .I2(\reduced_reg_reg[1]_8 [19]),
        .I3(AND_out10_carry__0_0[19]),
        .O(\reduced_reg_reg[1][18]_2 [1]));
  LUT4 #(
    .INIT(16'h9009)) 
    i__carry__0_i_5
       (.I0(\reduced_reg_reg[1]_8 [16]),
        .I1(modulating_signal_in_clock_cycles_1_reg__0[16]),
        .I2(\reduced_reg_reg[1]_8 [17]),
        .I3(modulating_signal_in_clock_cycles_1_reg__0[17]),
        .O(i__carry__0_i_5_n_0));
  LUT4 #(
    .INIT(16'h9009)) 
    i__carry__0_i_5__0
       (.I0(\reduced_reg_reg[1]_8 [16]),
        .I1(P[16]),
        .I2(\reduced_reg_reg[1]_8 [17]),
        .I3(P[17]),
        .O(\reduced_reg_reg[1][18]_0 [0]));
  LUT4 #(
    .INIT(16'h9009)) 
    i__carry__0_i_5__1
       (.I0(\reduced_reg_reg[1]_8 [16]),
        .I1(AND_out10_carry__0_0[16]),
        .I2(\reduced_reg_reg[1]_8 [17]),
        .I3(AND_out10_carry__0_0[17]),
        .O(\reduced_reg_reg[1][18]_2 [0]));
  LUT4 #(
    .INIT(16'h9009)) 
    i__carry_i_10__2
       (.I0(\reduced_reg_reg[1]_8 [12]),
        .I1(modulating_signal_in_clock_cycles_1_reg__0[12]),
        .I2(\reduced_reg_reg[1]_8 [13]),
        .I3(modulating_signal_in_clock_cycles_1_reg__0[13]),
        .O(i__carry_i_10__2_n_0));
  LUT4 #(
    .INIT(16'h9009)) 
    i__carry_i_10__3
       (.I0(\reduced_reg_reg[1]_8 [12]),
        .I1(P[12]),
        .I2(\reduced_reg_reg[1]_8 [13]),
        .I3(P[13]),
        .O(\reduced_reg_reg[1][14]_0 [6]));
  LUT4 #(
    .INIT(16'h9009)) 
    i__carry_i_10__4
       (.I0(\reduced_reg_reg[1]_8 [12]),
        .I1(AND_out10_carry__0_0[12]),
        .I2(\reduced_reg_reg[1]_8 [13]),
        .I3(AND_out10_carry__0_0[13]),
        .O(\reduced_reg_reg[1][14]_2 [6]));
  LUT4 #(
    .INIT(16'h9009)) 
    i__carry_i_11__2
       (.I0(\reduced_reg_reg[1]_8 [10]),
        .I1(modulating_signal_in_clock_cycles_1_reg__0[10]),
        .I2(\reduced_reg_reg[1]_8 [11]),
        .I3(modulating_signal_in_clock_cycles_1_reg__0[11]),
        .O(i__carry_i_11__2_n_0));
  LUT4 #(
    .INIT(16'h9009)) 
    i__carry_i_11__3
       (.I0(\reduced_reg_reg[1]_8 [10]),
        .I1(P[10]),
        .I2(\reduced_reg_reg[1]_8 [11]),
        .I3(P[11]),
        .O(\reduced_reg_reg[1][14]_0 [5]));
  LUT4 #(
    .INIT(16'h9009)) 
    i__carry_i_11__4
       (.I0(\reduced_reg_reg[1]_8 [10]),
        .I1(AND_out10_carry__0_0[10]),
        .I2(\reduced_reg_reg[1]_8 [11]),
        .I3(AND_out10_carry__0_0[11]),
        .O(\reduced_reg_reg[1][14]_2 [5]));
  LUT4 #(
    .INIT(16'h9009)) 
    i__carry_i_12__2
       (.I0(\reduced_reg_reg[1]_8 [8]),
        .I1(modulating_signal_in_clock_cycles_1_reg__0[8]),
        .I2(\reduced_reg_reg[1]_8 [9]),
        .I3(modulating_signal_in_clock_cycles_1_reg__0[9]),
        .O(i__carry_i_12__2_n_0));
  LUT4 #(
    .INIT(16'h9009)) 
    i__carry_i_12__3
       (.I0(\reduced_reg_reg[1]_8 [8]),
        .I1(P[8]),
        .I2(\reduced_reg_reg[1]_8 [9]),
        .I3(P[9]),
        .O(\reduced_reg_reg[1][14]_0 [4]));
  LUT4 #(
    .INIT(16'h9009)) 
    i__carry_i_12__4
       (.I0(\reduced_reg_reg[1]_8 [8]),
        .I1(AND_out10_carry__0_0[8]),
        .I2(\reduced_reg_reg[1]_8 [9]),
        .I3(AND_out10_carry__0_0[9]),
        .O(\reduced_reg_reg[1][14]_2 [4]));
  LUT4 #(
    .INIT(16'h9009)) 
    i__carry_i_13__2
       (.I0(\reduced_reg_reg[1]_8 [6]),
        .I1(modulating_signal_in_clock_cycles_1_reg__0[6]),
        .I2(\reduced_reg_reg[1]_8 [7]),
        .I3(modulating_signal_in_clock_cycles_1_reg__0[7]),
        .O(i__carry_i_13__2_n_0));
  LUT4 #(
    .INIT(16'h9009)) 
    i__carry_i_13__3
       (.I0(\reduced_reg_reg[1]_8 [6]),
        .I1(P[6]),
        .I2(\reduced_reg_reg[1]_8 [7]),
        .I3(P[7]),
        .O(\reduced_reg_reg[1][14]_0 [3]));
  LUT4 #(
    .INIT(16'h9009)) 
    i__carry_i_13__4
       (.I0(\reduced_reg_reg[1]_8 [6]),
        .I1(AND_out10_carry__0_0[6]),
        .I2(\reduced_reg_reg[1]_8 [7]),
        .I3(AND_out10_carry__0_0[7]),
        .O(\reduced_reg_reg[1][14]_2 [3]));
  LUT4 #(
    .INIT(16'h9009)) 
    i__carry_i_14__2
       (.I0(\reduced_reg_reg[1]_8 [4]),
        .I1(modulating_signal_in_clock_cycles_1_reg__0[4]),
        .I2(\reduced_reg_reg[1]_8 [5]),
        .I3(modulating_signal_in_clock_cycles_1_reg__0[5]),
        .O(i__carry_i_14__2_n_0));
  LUT4 #(
    .INIT(16'h9009)) 
    i__carry_i_14__3
       (.I0(\reduced_reg_reg[1]_8 [4]),
        .I1(P[4]),
        .I2(\reduced_reg_reg[1]_8 [5]),
        .I3(P[5]),
        .O(\reduced_reg_reg[1][14]_0 [2]));
  LUT4 #(
    .INIT(16'h9009)) 
    i__carry_i_14__4
       (.I0(\reduced_reg_reg[1]_8 [4]),
        .I1(AND_out10_carry__0_0[4]),
        .I2(\reduced_reg_reg[1]_8 [5]),
        .I3(AND_out10_carry__0_0[5]),
        .O(\reduced_reg_reg[1][14]_2 [2]));
  LUT4 #(
    .INIT(16'h9009)) 
    i__carry_i_15
       (.I0(\reduced_reg_reg[1]_8 [2]),
        .I1(modulating_signal_in_clock_cycles_1_reg__0[2]),
        .I2(\reduced_reg_reg[1]_8 [3]),
        .I3(modulating_signal_in_clock_cycles_1_reg__0[3]),
        .O(i__carry_i_15_n_0));
  LUT4 #(
    .INIT(16'h9009)) 
    i__carry_i_15__0
       (.I0(\reduced_reg_reg[1]_8 [2]),
        .I1(P[2]),
        .I2(\reduced_reg_reg[1]_8 [3]),
        .I3(P[3]),
        .O(\reduced_reg_reg[1][14]_0 [1]));
  LUT4 #(
    .INIT(16'h9009)) 
    i__carry_i_15__1
       (.I0(\reduced_reg_reg[1]_8 [2]),
        .I1(AND_out10_carry__0_0[2]),
        .I2(\reduced_reg_reg[1]_8 [3]),
        .I3(AND_out10_carry__0_0[3]),
        .O(\reduced_reg_reg[1][14]_2 [1]));
  LUT4 #(
    .INIT(16'h9009)) 
    i__carry_i_16
       (.I0(\reduced_reg_reg[1]_8 [0]),
        .I1(modulating_signal_in_clock_cycles_1_reg__0[0]),
        .I2(\reduced_reg_reg[1]_8 [1]),
        .I3(modulating_signal_in_clock_cycles_1_reg__0[1]),
        .O(i__carry_i_16_n_0));
  LUT4 #(
    .INIT(16'h9009)) 
    i__carry_i_16__0
       (.I0(\reduced_reg_reg[1]_8 [0]),
        .I1(P[0]),
        .I2(\reduced_reg_reg[1]_8 [1]),
        .I3(P[1]),
        .O(\reduced_reg_reg[1][14]_0 [0]));
  LUT4 #(
    .INIT(16'h9009)) 
    i__carry_i_16__1
       (.I0(\reduced_reg_reg[1]_8 [0]),
        .I1(AND_out10_carry__0_0[0]),
        .I2(\reduced_reg_reg[1]_8 [1]),
        .I3(AND_out10_carry__0_0[1]),
        .O(\reduced_reg_reg[1][14]_2 [0]));
  LUT4 #(
    .INIT(16'h2F02)) 
    i__carry_i_1__2
       (.I0(\reduced_reg_reg[1]_8 [14]),
        .I1(modulating_signal_in_clock_cycles_1_reg__0[14]),
        .I2(modulating_signal_in_clock_cycles_1_reg__0[15]),
        .I3(\reduced_reg_reg[1]_8 [15]),
        .O(i__carry_i_1__2_n_0));
  LUT4 #(
    .INIT(16'h2F02)) 
    i__carry_i_1__3
       (.I0(\reduced_reg_reg[1]_8 [14]),
        .I1(P[14]),
        .I2(P[15]),
        .I3(\reduced_reg_reg[1]_8 [15]),
        .O(\reduced_reg_reg[1][14]_1 [7]));
  LUT4 #(
    .INIT(16'h2F02)) 
    i__carry_i_1__4
       (.I0(\reduced_reg_reg[1]_8 [14]),
        .I1(AND_out10_carry__0_0[14]),
        .I2(AND_out10_carry__0_0[15]),
        .I3(\reduced_reg_reg[1]_8 [15]),
        .O(\reduced_reg_reg[1][14]_3 [7]));
  LUT4 #(
    .INIT(16'h2F02)) 
    i__carry_i_2__2
       (.I0(\reduced_reg_reg[1]_8 [12]),
        .I1(modulating_signal_in_clock_cycles_1_reg__0[12]),
        .I2(modulating_signal_in_clock_cycles_1_reg__0[13]),
        .I3(\reduced_reg_reg[1]_8 [13]),
        .O(i__carry_i_2__2_n_0));
  LUT4 #(
    .INIT(16'h2F02)) 
    i__carry_i_2__3
       (.I0(\reduced_reg_reg[1]_8 [12]),
        .I1(P[12]),
        .I2(P[13]),
        .I3(\reduced_reg_reg[1]_8 [13]),
        .O(\reduced_reg_reg[1][14]_1 [6]));
  LUT4 #(
    .INIT(16'h2F02)) 
    i__carry_i_2__4
       (.I0(\reduced_reg_reg[1]_8 [12]),
        .I1(AND_out10_carry__0_0[12]),
        .I2(AND_out10_carry__0_0[13]),
        .I3(\reduced_reg_reg[1]_8 [13]),
        .O(\reduced_reg_reg[1][14]_3 [6]));
  LUT4 #(
    .INIT(16'h2F02)) 
    i__carry_i_3__2
       (.I0(\reduced_reg_reg[1]_8 [10]),
        .I1(modulating_signal_in_clock_cycles_1_reg__0[10]),
        .I2(modulating_signal_in_clock_cycles_1_reg__0[11]),
        .I3(\reduced_reg_reg[1]_8 [11]),
        .O(i__carry_i_3__2_n_0));
  LUT4 #(
    .INIT(16'h2F02)) 
    i__carry_i_3__3
       (.I0(\reduced_reg_reg[1]_8 [10]),
        .I1(P[10]),
        .I2(P[11]),
        .I3(\reduced_reg_reg[1]_8 [11]),
        .O(\reduced_reg_reg[1][14]_1 [5]));
  LUT4 #(
    .INIT(16'h2F02)) 
    i__carry_i_3__4
       (.I0(\reduced_reg_reg[1]_8 [10]),
        .I1(AND_out10_carry__0_0[10]),
        .I2(AND_out10_carry__0_0[11]),
        .I3(\reduced_reg_reg[1]_8 [11]),
        .O(\reduced_reg_reg[1][14]_3 [5]));
  LUT4 #(
    .INIT(16'h2F02)) 
    i__carry_i_4__2
       (.I0(\reduced_reg_reg[1]_8 [8]),
        .I1(modulating_signal_in_clock_cycles_1_reg__0[8]),
        .I2(modulating_signal_in_clock_cycles_1_reg__0[9]),
        .I3(\reduced_reg_reg[1]_8 [9]),
        .O(i__carry_i_4__2_n_0));
  LUT4 #(
    .INIT(16'h2F02)) 
    i__carry_i_4__3
       (.I0(\reduced_reg_reg[1]_8 [8]),
        .I1(P[8]),
        .I2(P[9]),
        .I3(\reduced_reg_reg[1]_8 [9]),
        .O(\reduced_reg_reg[1][14]_1 [4]));
  LUT4 #(
    .INIT(16'h2F02)) 
    i__carry_i_4__4
       (.I0(\reduced_reg_reg[1]_8 [8]),
        .I1(AND_out10_carry__0_0[8]),
        .I2(AND_out10_carry__0_0[9]),
        .I3(\reduced_reg_reg[1]_8 [9]),
        .O(\reduced_reg_reg[1][14]_3 [4]));
  LUT4 #(
    .INIT(16'h2F02)) 
    i__carry_i_5__2
       (.I0(\reduced_reg_reg[1]_8 [6]),
        .I1(modulating_signal_in_clock_cycles_1_reg__0[6]),
        .I2(modulating_signal_in_clock_cycles_1_reg__0[7]),
        .I3(\reduced_reg_reg[1]_8 [7]),
        .O(i__carry_i_5__2_n_0));
  LUT4 #(
    .INIT(16'h2F02)) 
    i__carry_i_5__3
       (.I0(\reduced_reg_reg[1]_8 [6]),
        .I1(P[6]),
        .I2(P[7]),
        .I3(\reduced_reg_reg[1]_8 [7]),
        .O(\reduced_reg_reg[1][14]_1 [3]));
  LUT4 #(
    .INIT(16'h2F02)) 
    i__carry_i_5__4
       (.I0(\reduced_reg_reg[1]_8 [6]),
        .I1(AND_out10_carry__0_0[6]),
        .I2(AND_out10_carry__0_0[7]),
        .I3(\reduced_reg_reg[1]_8 [7]),
        .O(\reduced_reg_reg[1][14]_3 [3]));
  LUT4 #(
    .INIT(16'h2F02)) 
    i__carry_i_6__2
       (.I0(\reduced_reg_reg[1]_8 [4]),
        .I1(modulating_signal_in_clock_cycles_1_reg__0[4]),
        .I2(modulating_signal_in_clock_cycles_1_reg__0[5]),
        .I3(\reduced_reg_reg[1]_8 [5]),
        .O(i__carry_i_6__2_n_0));
  LUT4 #(
    .INIT(16'h2F02)) 
    i__carry_i_6__3
       (.I0(\reduced_reg_reg[1]_8 [4]),
        .I1(P[4]),
        .I2(P[5]),
        .I3(\reduced_reg_reg[1]_8 [5]),
        .O(\reduced_reg_reg[1][14]_1 [2]));
  LUT4 #(
    .INIT(16'h2F02)) 
    i__carry_i_6__4
       (.I0(\reduced_reg_reg[1]_8 [4]),
        .I1(AND_out10_carry__0_0[4]),
        .I2(AND_out10_carry__0_0[5]),
        .I3(\reduced_reg_reg[1]_8 [5]),
        .O(\reduced_reg_reg[1][14]_3 [2]));
  LUT4 #(
    .INIT(16'h2F02)) 
    i__carry_i_7__2
       (.I0(\reduced_reg_reg[1]_8 [2]),
        .I1(modulating_signal_in_clock_cycles_1_reg__0[2]),
        .I2(modulating_signal_in_clock_cycles_1_reg__0[3]),
        .I3(\reduced_reg_reg[1]_8 [3]),
        .O(i__carry_i_7__2_n_0));
  LUT4 #(
    .INIT(16'h2F02)) 
    i__carry_i_7__3
       (.I0(\reduced_reg_reg[1]_8 [2]),
        .I1(P[2]),
        .I2(P[3]),
        .I3(\reduced_reg_reg[1]_8 [3]),
        .O(\reduced_reg_reg[1][14]_1 [1]));
  LUT4 #(
    .INIT(16'h2F02)) 
    i__carry_i_7__4
       (.I0(\reduced_reg_reg[1]_8 [2]),
        .I1(AND_out10_carry__0_0[2]),
        .I2(AND_out10_carry__0_0[3]),
        .I3(\reduced_reg_reg[1]_8 [3]),
        .O(\reduced_reg_reg[1][14]_3 [1]));
  LUT4 #(
    .INIT(16'h2F02)) 
    i__carry_i_8__2
       (.I0(\reduced_reg_reg[1]_8 [0]),
        .I1(modulating_signal_in_clock_cycles_1_reg__0[0]),
        .I2(modulating_signal_in_clock_cycles_1_reg__0[1]),
        .I3(\reduced_reg_reg[1]_8 [1]),
        .O(i__carry_i_8__2_n_0));
  LUT4 #(
    .INIT(16'h2F02)) 
    i__carry_i_8__3
       (.I0(\reduced_reg_reg[1]_8 [0]),
        .I1(P[0]),
        .I2(P[1]),
        .I3(\reduced_reg_reg[1]_8 [1]),
        .O(\reduced_reg_reg[1][14]_1 [0]));
  LUT4 #(
    .INIT(16'h2F02)) 
    i__carry_i_8__4
       (.I0(\reduced_reg_reg[1]_8 [0]),
        .I1(AND_out10_carry__0_0[0]),
        .I2(AND_out10_carry__0_0[1]),
        .I3(\reduced_reg_reg[1]_8 [1]),
        .O(\reduced_reg_reg[1][14]_3 [0]));
  LUT4 #(
    .INIT(16'h9009)) 
    i__carry_i_9__2
       (.I0(\reduced_reg_reg[1]_8 [14]),
        .I1(modulating_signal_in_clock_cycles_1_reg__0[14]),
        .I2(\reduced_reg_reg[1]_8 [15]),
        .I3(modulating_signal_in_clock_cycles_1_reg__0[15]),
        .O(i__carry_i_9__2_n_0));
  LUT4 #(
    .INIT(16'h9009)) 
    i__carry_i_9__3
       (.I0(\reduced_reg_reg[1]_8 [14]),
        .I1(P[14]),
        .I2(\reduced_reg_reg[1]_8 [15]),
        .I3(P[15]),
        .O(\reduced_reg_reg[1][14]_0 [7]));
  LUT4 #(
    .INIT(16'h9009)) 
    i__carry_i_9__4
       (.I0(\reduced_reg_reg[1]_8 [14]),
        .I1(AND_out10_carry__0_0[14]),
        .I2(\reduced_reg_reg[1]_8 [15]),
        .I3(AND_out10_carry__0_0[15]),
        .O(\reduced_reg_reg[1][14]_2 [7]));
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
    modulating_signal_in_clock_cycles_1_reg
       (.A({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,maximum_counter_value_1}),
        .ACIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .ACOUT(NLW_modulating_signal_in_clock_cycles_1_reg_ACOUT_UNCONNECTED[29:0]),
        .ALUMODE({1'b0,1'b0,1'b0,1'b0}),
        .B({B[13],B[13],B[13],B[13],B}),
        .BCIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .BCOUT(NLW_modulating_signal_in_clock_cycles_1_reg_BCOUT_UNCONNECTED[17:0]),
        .C({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .CARRYCASCIN(1'b0),
        .CARRYCASCOUT(NLW_modulating_signal_in_clock_cycles_1_reg_CARRYCASCOUT_UNCONNECTED),
        .CARRYIN(1'b0),
        .CARRYINSEL({1'b0,1'b0,1'b0}),
        .CARRYOUT(NLW_modulating_signal_in_clock_cycles_1_reg_CARRYOUT_UNCONNECTED[3:0]),
        .CEA1(1'b0),
        .CEA2(CEP),
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
        .CEP(CEP),
        .CLK(IPCORE_CLK),
        .D({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .INMODE({1'b0,1'b0,1'b0,1'b0,1'b0}),
        .MULTSIGNIN(1'b0),
        .MULTSIGNOUT(NLW_modulating_signal_in_clock_cycles_1_reg_MULTSIGNOUT_UNCONNECTED),
        .OPMODE({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b1,1'b0,1'b1}),
        .OVERFLOW(NLW_modulating_signal_in_clock_cycles_1_reg_OVERFLOW_UNCONNECTED),
        .P({NLW_modulating_signal_in_clock_cycles_1_reg_P_UNCONNECTED[47:33],modulating_signal_in_clock_cycles_1_reg__0,modulating_signal_in_clock_cycles_1_reg_n_94,modulating_signal_in_clock_cycles_1_reg_n_95,modulating_signal_in_clock_cycles_1_reg_n_96,modulating_signal_in_clock_cycles_1_reg_n_97,modulating_signal_in_clock_cycles_1_reg_n_98,modulating_signal_in_clock_cycles_1_reg_n_99,modulating_signal_in_clock_cycles_1_reg_n_100,modulating_signal_in_clock_cycles_1_reg_n_101,modulating_signal_in_clock_cycles_1_reg_n_102,modulating_signal_in_clock_cycles_1_reg_n_103,modulating_signal_in_clock_cycles_1_reg_n_104,modulating_signal_in_clock_cycles_1_reg_n_105}),
        .PATTERNBDETECT(NLW_modulating_signal_in_clock_cycles_1_reg_PATTERNBDETECT_UNCONNECTED),
        .PATTERNDETECT(NLW_modulating_signal_in_clock_cycles_1_reg_PATTERNDETECT_UNCONNECTED),
        .PCIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .PCOUT(NLW_modulating_signal_in_clock_cycles_1_reg_PCOUT_UNCONNECTED[47:0]),
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
        .UNDERFLOW(NLW_modulating_signal_in_clock_cycles_1_reg_UNDERFLOW_UNCONNECTED),
        .XOROUT(NLW_modulating_signal_in_clock_cycles_1_reg_XOROUT_UNCONNECTED[7:0]));
  FDRE \reduced_reg_1_reg[0][0] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Counter_Ctrl_out3[0]),
        .Q(\reduced_reg_1_reg[0]_7 [0]),
        .R(RSTP));
  FDRE \reduced_reg_1_reg[0][10] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Counter_Ctrl_out3[10]),
        .Q(\reduced_reg_1_reg[0]_7 [10]),
        .R(RSTP));
  FDRE \reduced_reg_1_reg[0][11] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Counter_Ctrl_out3[11]),
        .Q(\reduced_reg_1_reg[0]_7 [11]),
        .R(RSTP));
  FDRE \reduced_reg_1_reg[0][12] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Counter_Ctrl_out3[12]),
        .Q(\reduced_reg_1_reg[0]_7 [12]),
        .R(RSTP));
  FDRE \reduced_reg_1_reg[0][13] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Counter_Ctrl_out3[13]),
        .Q(\reduced_reg_1_reg[0]_7 [13]),
        .R(RSTP));
  FDRE \reduced_reg_1_reg[0][14] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Counter_Ctrl_out3[14]),
        .Q(\reduced_reg_1_reg[0]_7 [14]),
        .R(RSTP));
  FDRE \reduced_reg_1_reg[0][15] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Counter_Ctrl_out3[15]),
        .Q(\reduced_reg_1_reg[0]_7 [15]),
        .R(RSTP));
  FDRE \reduced_reg_1_reg[0][16] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Counter_Ctrl_out3[16]),
        .Q(\reduced_reg_1_reg[0]_7 [16]),
        .R(RSTP));
  FDRE \reduced_reg_1_reg[0][17] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Counter_Ctrl_out3[17]),
        .Q(\reduced_reg_1_reg[0]_7 [17]),
        .R(RSTP));
  FDRE \reduced_reg_1_reg[0][18] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Counter_Ctrl_out3[18]),
        .Q(\reduced_reg_1_reg[0]_7 [18]),
        .R(RSTP));
  FDRE \reduced_reg_1_reg[0][19] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Counter_Ctrl_out3[19]),
        .Q(\reduced_reg_1_reg[0]_7 [19]),
        .R(RSTP));
  FDRE \reduced_reg_1_reg[0][1] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Counter_Ctrl_out3[1]),
        .Q(\reduced_reg_1_reg[0]_7 [1]),
        .R(RSTP));
  FDRE \reduced_reg_1_reg[0][20] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Counter_Ctrl_out3[20]),
        .Q(\reduced_reg_1_reg[0]_7 [20]),
        .R(RSTP));
  FDRE \reduced_reg_1_reg[0][2] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Counter_Ctrl_out3[2]),
        .Q(\reduced_reg_1_reg[0]_7 [2]),
        .R(RSTP));
  FDRE \reduced_reg_1_reg[0][3] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Counter_Ctrl_out3[3]),
        .Q(\reduced_reg_1_reg[0]_7 [3]),
        .R(RSTP));
  FDRE \reduced_reg_1_reg[0][4] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Counter_Ctrl_out3[4]),
        .Q(\reduced_reg_1_reg[0]_7 [4]),
        .R(RSTP));
  FDRE \reduced_reg_1_reg[0][5] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Counter_Ctrl_out3[5]),
        .Q(\reduced_reg_1_reg[0]_7 [5]),
        .R(RSTP));
  FDRE \reduced_reg_1_reg[0][6] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Counter_Ctrl_out3[6]),
        .Q(\reduced_reg_1_reg[0]_7 [6]),
        .R(RSTP));
  FDRE \reduced_reg_1_reg[0][7] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Counter_Ctrl_out3[7]),
        .Q(\reduced_reg_1_reg[0]_7 [7]),
        .R(RSTP));
  FDRE \reduced_reg_1_reg[0][8] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Counter_Ctrl_out3[8]),
        .Q(\reduced_reg_1_reg[0]_7 [8]),
        .R(RSTP));
  FDRE \reduced_reg_1_reg[0][9] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(Counter_Ctrl_out3[9]),
        .Q(\reduced_reg_1_reg[0]_7 [9]),
        .R(RSTP));
  FDRE \reduced_reg_1_reg[1][0] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\reduced_reg_1_reg[0]_7 [0]),
        .Q(\reduced_reg_1_reg[1]_9 [0]),
        .R(RSTP));
  FDRE \reduced_reg_1_reg[1][10] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\reduced_reg_1_reg[0]_7 [10]),
        .Q(\reduced_reg_1_reg[1]_9 [10]),
        .R(RSTP));
  FDRE \reduced_reg_1_reg[1][11] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\reduced_reg_1_reg[0]_7 [11]),
        .Q(\reduced_reg_1_reg[1]_9 [11]),
        .R(RSTP));
  FDRE \reduced_reg_1_reg[1][12] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\reduced_reg_1_reg[0]_7 [12]),
        .Q(\reduced_reg_1_reg[1]_9 [12]),
        .R(RSTP));
  FDRE \reduced_reg_1_reg[1][13] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\reduced_reg_1_reg[0]_7 [13]),
        .Q(\reduced_reg_1_reg[1]_9 [13]),
        .R(RSTP));
  FDRE \reduced_reg_1_reg[1][14] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\reduced_reg_1_reg[0]_7 [14]),
        .Q(\reduced_reg_1_reg[1]_9 [14]),
        .R(RSTP));
  FDRE \reduced_reg_1_reg[1][15] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\reduced_reg_1_reg[0]_7 [15]),
        .Q(\reduced_reg_1_reg[1]_9 [15]),
        .R(RSTP));
  FDRE \reduced_reg_1_reg[1][16] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\reduced_reg_1_reg[0]_7 [16]),
        .Q(\reduced_reg_1_reg[1]_9 [16]),
        .R(RSTP));
  FDRE \reduced_reg_1_reg[1][17] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\reduced_reg_1_reg[0]_7 [17]),
        .Q(\reduced_reg_1_reg[1]_9 [17]),
        .R(RSTP));
  FDRE \reduced_reg_1_reg[1][18] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\reduced_reg_1_reg[0]_7 [18]),
        .Q(\reduced_reg_1_reg[1]_9 [18]),
        .R(RSTP));
  FDRE \reduced_reg_1_reg[1][19] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\reduced_reg_1_reg[0]_7 [19]),
        .Q(\reduced_reg_1_reg[1]_9 [19]),
        .R(RSTP));
  FDRE \reduced_reg_1_reg[1][1] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\reduced_reg_1_reg[0]_7 [1]),
        .Q(\reduced_reg_1_reg[1]_9 [1]),
        .R(RSTP));
  FDRE \reduced_reg_1_reg[1][20] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\reduced_reg_1_reg[0]_7 [20]),
        .Q(\reduced_reg_1_reg[1]_9 [20]),
        .R(RSTP));
  FDRE \reduced_reg_1_reg[1][2] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\reduced_reg_1_reg[0]_7 [2]),
        .Q(\reduced_reg_1_reg[1]_9 [2]),
        .R(RSTP));
  FDRE \reduced_reg_1_reg[1][3] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\reduced_reg_1_reg[0]_7 [3]),
        .Q(\reduced_reg_1_reg[1]_9 [3]),
        .R(RSTP));
  FDRE \reduced_reg_1_reg[1][4] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\reduced_reg_1_reg[0]_7 [4]),
        .Q(\reduced_reg_1_reg[1]_9 [4]),
        .R(RSTP));
  FDRE \reduced_reg_1_reg[1][5] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\reduced_reg_1_reg[0]_7 [5]),
        .Q(\reduced_reg_1_reg[1]_9 [5]),
        .R(RSTP));
  FDRE \reduced_reg_1_reg[1][6] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\reduced_reg_1_reg[0]_7 [6]),
        .Q(\reduced_reg_1_reg[1]_9 [6]),
        .R(RSTP));
  FDRE \reduced_reg_1_reg[1][7] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\reduced_reg_1_reg[0]_7 [7]),
        .Q(\reduced_reg_1_reg[1]_9 [7]),
        .R(RSTP));
  FDRE \reduced_reg_1_reg[1][8] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\reduced_reg_1_reg[0]_7 [8]),
        .Q(\reduced_reg_1_reg[1]_9 [8]),
        .R(RSTP));
  FDRE \reduced_reg_1_reg[1][9] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\reduced_reg_1_reg[0]_7 [9]),
        .Q(\reduced_reg_1_reg[1]_9 [9]),
        .R(RSTP));
  FDRE \reduced_reg_reg[0][0] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(HDL_Counter2_count_reg[0]),
        .Q(\reduced_reg_reg[0]_6 [0]),
        .R(RSTP));
  FDRE \reduced_reg_reg[0][10] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(HDL_Counter2_count_reg[10]),
        .Q(\reduced_reg_reg[0]_6 [10]),
        .R(RSTP));
  FDRE \reduced_reg_reg[0][11] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(HDL_Counter2_count_reg[11]),
        .Q(\reduced_reg_reg[0]_6 [11]),
        .R(RSTP));
  FDRE \reduced_reg_reg[0][12] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(HDL_Counter2_count_reg[12]),
        .Q(\reduced_reg_reg[0]_6 [12]),
        .R(RSTP));
  FDRE \reduced_reg_reg[0][13] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(HDL_Counter2_count_reg[13]),
        .Q(\reduced_reg_reg[0]_6 [13]),
        .R(RSTP));
  FDRE \reduced_reg_reg[0][14] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(HDL_Counter2_count_reg[14]),
        .Q(\reduced_reg_reg[0]_6 [14]),
        .R(RSTP));
  FDRE \reduced_reg_reg[0][15] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(HDL_Counter2_count_reg[15]),
        .Q(\reduced_reg_reg[0]_6 [15]),
        .R(RSTP));
  FDRE \reduced_reg_reg[0][16] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(HDL_Counter2_count_reg[16]),
        .Q(\reduced_reg_reg[0]_6 [16]),
        .R(RSTP));
  FDRE \reduced_reg_reg[0][17] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(HDL_Counter2_count_reg[17]),
        .Q(\reduced_reg_reg[0]_6 [17]),
        .R(RSTP));
  FDRE \reduced_reg_reg[0][18] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(HDL_Counter2_count_reg[18]),
        .Q(\reduced_reg_reg[0]_6 [18]),
        .R(RSTP));
  FDRE \reduced_reg_reg[0][19] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(HDL_Counter2_count_reg[19]),
        .Q(\reduced_reg_reg[0]_6 [19]),
        .R(RSTP));
  FDRE \reduced_reg_reg[0][1] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(HDL_Counter2_count_reg[1]),
        .Q(\reduced_reg_reg[0]_6 [1]),
        .R(RSTP));
  FDRE \reduced_reg_reg[0][2] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(HDL_Counter2_count_reg[2]),
        .Q(\reduced_reg_reg[0]_6 [2]),
        .R(RSTP));
  FDRE \reduced_reg_reg[0][3] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(HDL_Counter2_count_reg[3]),
        .Q(\reduced_reg_reg[0]_6 [3]),
        .R(RSTP));
  FDRE \reduced_reg_reg[0][4] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(HDL_Counter2_count_reg[4]),
        .Q(\reduced_reg_reg[0]_6 [4]),
        .R(RSTP));
  FDRE \reduced_reg_reg[0][5] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(HDL_Counter2_count_reg[5]),
        .Q(\reduced_reg_reg[0]_6 [5]),
        .R(RSTP));
  FDRE \reduced_reg_reg[0][6] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(HDL_Counter2_count_reg[6]),
        .Q(\reduced_reg_reg[0]_6 [6]),
        .R(RSTP));
  FDRE \reduced_reg_reg[0][7] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(HDL_Counter2_count_reg[7]),
        .Q(\reduced_reg_reg[0]_6 [7]),
        .R(RSTP));
  FDRE \reduced_reg_reg[0][8] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(HDL_Counter2_count_reg[8]),
        .Q(\reduced_reg_reg[0]_6 [8]),
        .R(RSTP));
  FDRE \reduced_reg_reg[0][9] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(HDL_Counter2_count_reg[9]),
        .Q(\reduced_reg_reg[0]_6 [9]),
        .R(RSTP));
  FDRE \reduced_reg_reg[1][0] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\reduced_reg_reg[0]_6 [0]),
        .Q(\reduced_reg_reg[1]_8 [0]),
        .R(RSTP));
  FDRE \reduced_reg_reg[1][10] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\reduced_reg_reg[0]_6 [10]),
        .Q(\reduced_reg_reg[1]_8 [10]),
        .R(RSTP));
  FDRE \reduced_reg_reg[1][11] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\reduced_reg_reg[0]_6 [11]),
        .Q(\reduced_reg_reg[1]_8 [11]),
        .R(RSTP));
  FDRE \reduced_reg_reg[1][12] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\reduced_reg_reg[0]_6 [12]),
        .Q(\reduced_reg_reg[1]_8 [12]),
        .R(RSTP));
  FDRE \reduced_reg_reg[1][13] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\reduced_reg_reg[0]_6 [13]),
        .Q(\reduced_reg_reg[1]_8 [13]),
        .R(RSTP));
  FDRE \reduced_reg_reg[1][14] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\reduced_reg_reg[0]_6 [14]),
        .Q(\reduced_reg_reg[1]_8 [14]),
        .R(RSTP));
  FDRE \reduced_reg_reg[1][15] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\reduced_reg_reg[0]_6 [15]),
        .Q(\reduced_reg_reg[1]_8 [15]),
        .R(RSTP));
  FDRE \reduced_reg_reg[1][16] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\reduced_reg_reg[0]_6 [16]),
        .Q(\reduced_reg_reg[1]_8 [16]),
        .R(RSTP));
  FDRE \reduced_reg_reg[1][17] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\reduced_reg_reg[0]_6 [17]),
        .Q(\reduced_reg_reg[1]_8 [17]),
        .R(RSTP));
  FDRE \reduced_reg_reg[1][18] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\reduced_reg_reg[0]_6 [18]),
        .Q(\reduced_reg_reg[1]_8 [18]),
        .R(RSTP));
  FDRE \reduced_reg_reg[1][19] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\reduced_reg_reg[0]_6 [19]),
        .Q(\reduced_reg_reg[1]_8 [19]),
        .R(RSTP));
  FDRE \reduced_reg_reg[1][1] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\reduced_reg_reg[0]_6 [1]),
        .Q(\reduced_reg_reg[1]_8 [1]),
        .R(RSTP));
  FDRE \reduced_reg_reg[1][2] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\reduced_reg_reg[0]_6 [2]),
        .Q(\reduced_reg_reg[1]_8 [2]),
        .R(RSTP));
  FDRE \reduced_reg_reg[1][3] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\reduced_reg_reg[0]_6 [3]),
        .Q(\reduced_reg_reg[1]_8 [3]),
        .R(RSTP));
  FDRE \reduced_reg_reg[1][4] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\reduced_reg_reg[0]_6 [4]),
        .Q(\reduced_reg_reg[1]_8 [4]),
        .R(RSTP));
  FDRE \reduced_reg_reg[1][5] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\reduced_reg_reg[0]_6 [5]),
        .Q(\reduced_reg_reg[1]_8 [5]),
        .R(RSTP));
  FDRE \reduced_reg_reg[1][6] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\reduced_reg_reg[0]_6 [6]),
        .Q(\reduced_reg_reg[1]_8 [6]),
        .R(RSTP));
  FDRE \reduced_reg_reg[1][7] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\reduced_reg_reg[0]_6 [7]),
        .Q(\reduced_reg_reg[1]_8 [7]),
        .R(RSTP));
  FDRE \reduced_reg_reg[1][8] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\reduced_reg_reg[0]_6 [8]),
        .Q(\reduced_reg_reg[1]_8 [8]),
        .R(RSTP));
  FDRE \reduced_reg_reg[1][9] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(\reduced_reg_reg[0]_6 [9]),
        .Q(\reduced_reg_reg[1]_8 [9]),
        .R(RSTP));
endmodule

(* ORIG_REF_NAME = "PWM_SS_3L_ip_src_Modulator_b" *) 
module zusys_PWM_SS_3L_ip_0_0_PWM_SS_3L_ip_src_Modulator_b
   (P,
    D,
    CEP,
    IPCORE_CLK,
    RSTP,
    B,
    maximum_counter_value_1,
    DI,
    \AND_out10_inferred__0/i__carry__0_0 ,
    \AND_out10_inferred__0/i__carry__0_1 ,
    \Switch4_out1_1_reg[0] ,
    \Switch4_out1_1_reg[0]_0 ,
    \reduced_reg_1_reg[1]_9 );
  output [20:0]P;
  output [1:0]D;
  input CEP;
  input IPCORE_CLK;
  input RSTP;
  input [13:0]B;
  input [19:0]maximum_counter_value_1;
  input [0:0]DI;
  input [7:0]\AND_out10_inferred__0/i__carry__0_0 ;
  input [7:0]\AND_out10_inferred__0/i__carry__0_1 ;
  input [1:0]\Switch4_out1_1_reg[0] ;
  input [1:0]\Switch4_out1_1_reg[0]_0 ;
  input [20:0]\reduced_reg_1_reg[1]_9 ;

  wire AND_out10_carry__0_i_2__0_n_0;
  wire AND_out10_carry__0_i_3__0_n_0;
  wire AND_out10_carry__0_i_4__0_n_0;
  wire AND_out10_carry__0_i_5__0_n_0;
  wire AND_out10_carry__0_i_6__0_n_0;
  wire AND_out10_carry__0_n_6;
  wire AND_out10_carry__0_n_7;
  wire AND_out10_carry_i_10__0_n_0;
  wire AND_out10_carry_i_11__0_n_0;
  wire AND_out10_carry_i_12__0_n_0;
  wire AND_out10_carry_i_13__0_n_0;
  wire AND_out10_carry_i_14__0_n_0;
  wire AND_out10_carry_i_15__0_n_0;
  wire AND_out10_carry_i_16__0_n_0;
  wire AND_out10_carry_i_1__0_n_0;
  wire AND_out10_carry_i_2__0_n_0;
  wire AND_out10_carry_i_3__0_n_0;
  wire AND_out10_carry_i_4__0_n_0;
  wire AND_out10_carry_i_5__0_n_0;
  wire AND_out10_carry_i_6__0_n_0;
  wire AND_out10_carry_i_7__0_n_0;
  wire AND_out10_carry_i_8__0_n_0;
  wire AND_out10_carry_i_9__0_n_0;
  wire AND_out10_carry_n_0;
  wire AND_out10_carry_n_1;
  wire AND_out10_carry_n_2;
  wire AND_out10_carry_n_3;
  wire AND_out10_carry_n_4;
  wire AND_out10_carry_n_5;
  wire AND_out10_carry_n_6;
  wire AND_out10_carry_n_7;
  wire [7:0]\AND_out10_inferred__0/i__carry__0_0 ;
  wire [7:0]\AND_out10_inferred__0/i__carry__0_1 ;
  wire \AND_out10_inferred__0/i__carry__0_n_6 ;
  wire \AND_out10_inferred__0/i__carry__0_n_7 ;
  wire \AND_out10_inferred__0/i__carry_n_0 ;
  wire \AND_out10_inferred__0/i__carry_n_1 ;
  wire \AND_out10_inferred__0/i__carry_n_2 ;
  wire \AND_out10_inferred__0/i__carry_n_3 ;
  wire \AND_out10_inferred__0/i__carry_n_4 ;
  wire \AND_out10_inferred__0/i__carry_n_5 ;
  wire \AND_out10_inferred__0/i__carry_n_6 ;
  wire \AND_out10_inferred__0/i__carry_n_7 ;
  wire [13:0]B;
  wire CEP;
  wire [1:0]D;
  wire [0:0]DI;
  wire IPCORE_CLK;
  wire [20:0]P;
  wire RSTP;
  wire Relational_Operator1_relop1;
  wire Relational_Operator_relop1;
  wire [1:0]\Switch4_out1_1_reg[0] ;
  wire [1:0]\Switch4_out1_1_reg[0]_0 ;
  wire i__carry__0_i_3__0_n_0;
  wire [19:0]maximum_counter_value_1;
  wire modulating_signal_in_clock_cycles_1_reg_n_100;
  wire modulating_signal_in_clock_cycles_1_reg_n_101;
  wire modulating_signal_in_clock_cycles_1_reg_n_102;
  wire modulating_signal_in_clock_cycles_1_reg_n_103;
  wire modulating_signal_in_clock_cycles_1_reg_n_104;
  wire modulating_signal_in_clock_cycles_1_reg_n_105;
  wire modulating_signal_in_clock_cycles_1_reg_n_94;
  wire modulating_signal_in_clock_cycles_1_reg_n_95;
  wire modulating_signal_in_clock_cycles_1_reg_n_96;
  wire modulating_signal_in_clock_cycles_1_reg_n_97;
  wire modulating_signal_in_clock_cycles_1_reg_n_98;
  wire modulating_signal_in_clock_cycles_1_reg_n_99;
  wire [20:0]\reduced_reg_1_reg[1]_9 ;
  wire [7:0]NLW_AND_out10_carry_O_UNCONNECTED;
  wire [7:3]NLW_AND_out10_carry__0_CO_UNCONNECTED;
  wire [7:0]NLW_AND_out10_carry__0_O_UNCONNECTED;
  wire [7:0]\NLW_AND_out10_inferred__0/i__carry_O_UNCONNECTED ;
  wire [7:3]\NLW_AND_out10_inferred__0/i__carry__0_CO_UNCONNECTED ;
  wire [7:0]\NLW_AND_out10_inferred__0/i__carry__0_O_UNCONNECTED ;
  wire NLW_modulating_signal_in_clock_cycles_1_reg_CARRYCASCOUT_UNCONNECTED;
  wire NLW_modulating_signal_in_clock_cycles_1_reg_MULTSIGNOUT_UNCONNECTED;
  wire NLW_modulating_signal_in_clock_cycles_1_reg_OVERFLOW_UNCONNECTED;
  wire NLW_modulating_signal_in_clock_cycles_1_reg_PATTERNBDETECT_UNCONNECTED;
  wire NLW_modulating_signal_in_clock_cycles_1_reg_PATTERNDETECT_UNCONNECTED;
  wire NLW_modulating_signal_in_clock_cycles_1_reg_UNDERFLOW_UNCONNECTED;
  wire [29:0]NLW_modulating_signal_in_clock_cycles_1_reg_ACOUT_UNCONNECTED;
  wire [17:0]NLW_modulating_signal_in_clock_cycles_1_reg_BCOUT_UNCONNECTED;
  wire [3:0]NLW_modulating_signal_in_clock_cycles_1_reg_CARRYOUT_UNCONNECTED;
  wire [47:33]NLW_modulating_signal_in_clock_cycles_1_reg_P_UNCONNECTED;
  wire [47:0]NLW_modulating_signal_in_clock_cycles_1_reg_PCOUT_UNCONNECTED;
  wire [7:0]NLW_modulating_signal_in_clock_cycles_1_reg_XOROUT_UNCONNECTED;

  (* COMPARATOR_THRESHOLD = "11" *) 
  CARRY8 AND_out10_carry
       (.CI(1'b1),
        .CI_TOP(1'b0),
        .CO({AND_out10_carry_n_0,AND_out10_carry_n_1,AND_out10_carry_n_2,AND_out10_carry_n_3,AND_out10_carry_n_4,AND_out10_carry_n_5,AND_out10_carry_n_6,AND_out10_carry_n_7}),
        .DI({AND_out10_carry_i_1__0_n_0,AND_out10_carry_i_2__0_n_0,AND_out10_carry_i_3__0_n_0,AND_out10_carry_i_4__0_n_0,AND_out10_carry_i_5__0_n_0,AND_out10_carry_i_6__0_n_0,AND_out10_carry_i_7__0_n_0,AND_out10_carry_i_8__0_n_0}),
        .O(NLW_AND_out10_carry_O_UNCONNECTED[7:0]),
        .S({AND_out10_carry_i_9__0_n_0,AND_out10_carry_i_10__0_n_0,AND_out10_carry_i_11__0_n_0,AND_out10_carry_i_12__0_n_0,AND_out10_carry_i_13__0_n_0,AND_out10_carry_i_14__0_n_0,AND_out10_carry_i_15__0_n_0,AND_out10_carry_i_16__0_n_0}));
  (* COMPARATOR_THRESHOLD = "11" *) 
  CARRY8 AND_out10_carry__0
       (.CI(AND_out10_carry_n_0),
        .CI_TOP(1'b0),
        .CO({NLW_AND_out10_carry__0_CO_UNCONNECTED[7:3],Relational_Operator1_relop1,AND_out10_carry__0_n_6,AND_out10_carry__0_n_7}),
        .DI({1'b0,1'b0,1'b0,1'b0,1'b0,DI,AND_out10_carry__0_i_2__0_n_0,AND_out10_carry__0_i_3__0_n_0}),
        .O(NLW_AND_out10_carry__0_O_UNCONNECTED[7:0]),
        .S({1'b0,1'b0,1'b0,1'b0,1'b0,AND_out10_carry__0_i_4__0_n_0,AND_out10_carry__0_i_5__0_n_0,AND_out10_carry__0_i_6__0_n_0}));
  LUT4 #(
    .INIT(16'h2F02)) 
    AND_out10_carry__0_i_2__0
       (.I0(P[18]),
        .I1(\reduced_reg_1_reg[1]_9 [18]),
        .I2(\reduced_reg_1_reg[1]_9 [19]),
        .I3(P[19]),
        .O(AND_out10_carry__0_i_2__0_n_0));
  LUT4 #(
    .INIT(16'h2F02)) 
    AND_out10_carry__0_i_3__0
       (.I0(P[16]),
        .I1(\reduced_reg_1_reg[1]_9 [16]),
        .I2(\reduced_reg_1_reg[1]_9 [17]),
        .I3(P[17]),
        .O(AND_out10_carry__0_i_3__0_n_0));
  LUT2 #(
    .INIT(4'h9)) 
    AND_out10_carry__0_i_4__0
       (.I0(P[20]),
        .I1(\reduced_reg_1_reg[1]_9 [20]),
        .O(AND_out10_carry__0_i_4__0_n_0));
  LUT4 #(
    .INIT(16'h9009)) 
    AND_out10_carry__0_i_5__0
       (.I0(P[18]),
        .I1(\reduced_reg_1_reg[1]_9 [18]),
        .I2(P[19]),
        .I3(\reduced_reg_1_reg[1]_9 [19]),
        .O(AND_out10_carry__0_i_5__0_n_0));
  LUT4 #(
    .INIT(16'h9009)) 
    AND_out10_carry__0_i_6__0
       (.I0(P[16]),
        .I1(\reduced_reg_1_reg[1]_9 [16]),
        .I2(P[17]),
        .I3(\reduced_reg_1_reg[1]_9 [17]),
        .O(AND_out10_carry__0_i_6__0_n_0));
  LUT4 #(
    .INIT(16'h9009)) 
    AND_out10_carry_i_10__0
       (.I0(P[12]),
        .I1(\reduced_reg_1_reg[1]_9 [12]),
        .I2(P[13]),
        .I3(\reduced_reg_1_reg[1]_9 [13]),
        .O(AND_out10_carry_i_10__0_n_0));
  LUT4 #(
    .INIT(16'h9009)) 
    AND_out10_carry_i_11__0
       (.I0(P[10]),
        .I1(\reduced_reg_1_reg[1]_9 [10]),
        .I2(P[11]),
        .I3(\reduced_reg_1_reg[1]_9 [11]),
        .O(AND_out10_carry_i_11__0_n_0));
  LUT4 #(
    .INIT(16'h9009)) 
    AND_out10_carry_i_12__0
       (.I0(P[8]),
        .I1(\reduced_reg_1_reg[1]_9 [8]),
        .I2(P[9]),
        .I3(\reduced_reg_1_reg[1]_9 [9]),
        .O(AND_out10_carry_i_12__0_n_0));
  LUT4 #(
    .INIT(16'h9009)) 
    AND_out10_carry_i_13__0
       (.I0(P[6]),
        .I1(\reduced_reg_1_reg[1]_9 [6]),
        .I2(P[7]),
        .I3(\reduced_reg_1_reg[1]_9 [7]),
        .O(AND_out10_carry_i_13__0_n_0));
  LUT4 #(
    .INIT(16'h9009)) 
    AND_out10_carry_i_14__0
       (.I0(P[4]),
        .I1(\reduced_reg_1_reg[1]_9 [4]),
        .I2(P[5]),
        .I3(\reduced_reg_1_reg[1]_9 [5]),
        .O(AND_out10_carry_i_14__0_n_0));
  LUT4 #(
    .INIT(16'h9009)) 
    AND_out10_carry_i_15__0
       (.I0(P[2]),
        .I1(\reduced_reg_1_reg[1]_9 [2]),
        .I2(P[3]),
        .I3(\reduced_reg_1_reg[1]_9 [3]),
        .O(AND_out10_carry_i_15__0_n_0));
  LUT4 #(
    .INIT(16'h9009)) 
    AND_out10_carry_i_16__0
       (.I0(P[0]),
        .I1(\reduced_reg_1_reg[1]_9 [0]),
        .I2(P[1]),
        .I3(\reduced_reg_1_reg[1]_9 [1]),
        .O(AND_out10_carry_i_16__0_n_0));
  LUT4 #(
    .INIT(16'h2F02)) 
    AND_out10_carry_i_1__0
       (.I0(P[14]),
        .I1(\reduced_reg_1_reg[1]_9 [14]),
        .I2(\reduced_reg_1_reg[1]_9 [15]),
        .I3(P[15]),
        .O(AND_out10_carry_i_1__0_n_0));
  LUT4 #(
    .INIT(16'h2F02)) 
    AND_out10_carry_i_2__0
       (.I0(P[12]),
        .I1(\reduced_reg_1_reg[1]_9 [12]),
        .I2(\reduced_reg_1_reg[1]_9 [13]),
        .I3(P[13]),
        .O(AND_out10_carry_i_2__0_n_0));
  LUT4 #(
    .INIT(16'h2F02)) 
    AND_out10_carry_i_3__0
       (.I0(P[10]),
        .I1(\reduced_reg_1_reg[1]_9 [10]),
        .I2(\reduced_reg_1_reg[1]_9 [11]),
        .I3(P[11]),
        .O(AND_out10_carry_i_3__0_n_0));
  LUT4 #(
    .INIT(16'h2F02)) 
    AND_out10_carry_i_4__0
       (.I0(P[8]),
        .I1(\reduced_reg_1_reg[1]_9 [8]),
        .I2(\reduced_reg_1_reg[1]_9 [9]),
        .I3(P[9]),
        .O(AND_out10_carry_i_4__0_n_0));
  LUT4 #(
    .INIT(16'h2F02)) 
    AND_out10_carry_i_5__0
       (.I0(P[6]),
        .I1(\reduced_reg_1_reg[1]_9 [6]),
        .I2(\reduced_reg_1_reg[1]_9 [7]),
        .I3(P[7]),
        .O(AND_out10_carry_i_5__0_n_0));
  LUT4 #(
    .INIT(16'h2F02)) 
    AND_out10_carry_i_6__0
       (.I0(P[4]),
        .I1(\reduced_reg_1_reg[1]_9 [4]),
        .I2(\reduced_reg_1_reg[1]_9 [5]),
        .I3(P[5]),
        .O(AND_out10_carry_i_6__0_n_0));
  LUT4 #(
    .INIT(16'h2F02)) 
    AND_out10_carry_i_7__0
       (.I0(P[2]),
        .I1(\reduced_reg_1_reg[1]_9 [2]),
        .I2(\reduced_reg_1_reg[1]_9 [3]),
        .I3(P[3]),
        .O(AND_out10_carry_i_7__0_n_0));
  LUT4 #(
    .INIT(16'h2F02)) 
    AND_out10_carry_i_8__0
       (.I0(P[0]),
        .I1(\reduced_reg_1_reg[1]_9 [0]),
        .I2(\reduced_reg_1_reg[1]_9 [1]),
        .I3(P[1]),
        .O(AND_out10_carry_i_8__0_n_0));
  LUT4 #(
    .INIT(16'h9009)) 
    AND_out10_carry_i_9__0
       (.I0(P[14]),
        .I1(\reduced_reg_1_reg[1]_9 [14]),
        .I2(P[15]),
        .I3(\reduced_reg_1_reg[1]_9 [15]),
        .O(AND_out10_carry_i_9__0_n_0));
  (* COMPARATOR_THRESHOLD = "11" *) 
  CARRY8 \AND_out10_inferred__0/i__carry 
       (.CI(1'b1),
        .CI_TOP(1'b0),
        .CO({\AND_out10_inferred__0/i__carry_n_0 ,\AND_out10_inferred__0/i__carry_n_1 ,\AND_out10_inferred__0/i__carry_n_2 ,\AND_out10_inferred__0/i__carry_n_3 ,\AND_out10_inferred__0/i__carry_n_4 ,\AND_out10_inferred__0/i__carry_n_5 ,\AND_out10_inferred__0/i__carry_n_6 ,\AND_out10_inferred__0/i__carry_n_7 }),
        .DI(\AND_out10_inferred__0/i__carry__0_0 ),
        .O(\NLW_AND_out10_inferred__0/i__carry_O_UNCONNECTED [7:0]),
        .S(\AND_out10_inferred__0/i__carry__0_1 ));
  (* COMPARATOR_THRESHOLD = "11" *) 
  CARRY8 \AND_out10_inferred__0/i__carry__0 
       (.CI(\AND_out10_inferred__0/i__carry_n_0 ),
        .CI_TOP(1'b0),
        .CO({\NLW_AND_out10_inferred__0/i__carry__0_CO_UNCONNECTED [7:3],Relational_Operator_relop1,\AND_out10_inferred__0/i__carry__0_n_6 ,\AND_out10_inferred__0/i__carry__0_n_7 }),
        .DI({1'b0,1'b0,1'b0,1'b0,1'b0,P[20],\Switch4_out1_1_reg[0] }),
        .O(\NLW_AND_out10_inferred__0/i__carry__0_O_UNCONNECTED [7:0]),
        .S({1'b0,1'b0,1'b0,1'b0,1'b0,i__carry__0_i_3__0_n_0,\Switch4_out1_1_reg[0]_0 }));
  (* SOFT_HLUTNM = "soft_lutpair51" *) 
  LUT2 #(
    .INIT(4'h2)) 
    \Switch4_out1_1[0]_i_1 
       (.I0(Relational_Operator1_relop1),
        .I1(Relational_Operator_relop1),
        .O(D[1]));
  (* SOFT_HLUTNM = "soft_lutpair51" *) 
  LUT1 #(
    .INIT(2'h2)) 
    \Switch4_out1_1[1]_i_1 
       (.I0(Relational_Operator1_relop1),
        .O(D[0]));
  LUT1 #(
    .INIT(2'h1)) 
    i__carry__0_i_3__0
       (.I0(P[20]),
        .O(i__carry__0_i_3__0_n_0));
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
    modulating_signal_in_clock_cycles_1_reg
       (.A({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,maximum_counter_value_1}),
        .ACIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .ACOUT(NLW_modulating_signal_in_clock_cycles_1_reg_ACOUT_UNCONNECTED[29:0]),
        .ALUMODE({1'b0,1'b0,1'b0,1'b0}),
        .B({B[13],B[13],B[13],B[13],B}),
        .BCIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .BCOUT(NLW_modulating_signal_in_clock_cycles_1_reg_BCOUT_UNCONNECTED[17:0]),
        .C({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .CARRYCASCIN(1'b0),
        .CARRYCASCOUT(NLW_modulating_signal_in_clock_cycles_1_reg_CARRYCASCOUT_UNCONNECTED),
        .CARRYIN(1'b0),
        .CARRYINSEL({1'b0,1'b0,1'b0}),
        .CARRYOUT(NLW_modulating_signal_in_clock_cycles_1_reg_CARRYOUT_UNCONNECTED[3:0]),
        .CEA1(1'b0),
        .CEA2(CEP),
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
        .CEP(CEP),
        .CLK(IPCORE_CLK),
        .D({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .INMODE({1'b0,1'b0,1'b0,1'b0,1'b0}),
        .MULTSIGNIN(1'b0),
        .MULTSIGNOUT(NLW_modulating_signal_in_clock_cycles_1_reg_MULTSIGNOUT_UNCONNECTED),
        .OPMODE({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b1,1'b0,1'b1}),
        .OVERFLOW(NLW_modulating_signal_in_clock_cycles_1_reg_OVERFLOW_UNCONNECTED),
        .P({NLW_modulating_signal_in_clock_cycles_1_reg_P_UNCONNECTED[47:33],P,modulating_signal_in_clock_cycles_1_reg_n_94,modulating_signal_in_clock_cycles_1_reg_n_95,modulating_signal_in_clock_cycles_1_reg_n_96,modulating_signal_in_clock_cycles_1_reg_n_97,modulating_signal_in_clock_cycles_1_reg_n_98,modulating_signal_in_clock_cycles_1_reg_n_99,modulating_signal_in_clock_cycles_1_reg_n_100,modulating_signal_in_clock_cycles_1_reg_n_101,modulating_signal_in_clock_cycles_1_reg_n_102,modulating_signal_in_clock_cycles_1_reg_n_103,modulating_signal_in_clock_cycles_1_reg_n_104,modulating_signal_in_clock_cycles_1_reg_n_105}),
        .PATTERNBDETECT(NLW_modulating_signal_in_clock_cycles_1_reg_PATTERNBDETECT_UNCONNECTED),
        .PATTERNDETECT(NLW_modulating_signal_in_clock_cycles_1_reg_PATTERNDETECT_UNCONNECTED),
        .PCIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .PCOUT(NLW_modulating_signal_in_clock_cycles_1_reg_PCOUT_UNCONNECTED[47:0]),
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
        .UNDERFLOW(NLW_modulating_signal_in_clock_cycles_1_reg_UNDERFLOW_UNCONNECTED),
        .XOROUT(NLW_modulating_signal_in_clock_cycles_1_reg_XOROUT_UNCONNECTED[7:0]));
endmodule

(* ORIG_REF_NAME = "PWM_SS_3L_ip_src_Modulator_c" *) 
module zusys_PWM_SS_3L_ip_0_0_PWM_SS_3L_ip_src_Modulator_c
   (P,
    D,
    CEP,
    IPCORE_CLK,
    RSTP,
    B,
    maximum_counter_value_1,
    \Switch5_out1_1_reg[1] ,
    \AND_out10_inferred__0/i__carry__0_0 ,
    \AND_out10_inferred__0/i__carry__0_1 ,
    \Switch5_out1_1_reg[0] ,
    \Switch5_out1_1_reg[0]_0 ,
    \reduced_reg_1_reg[1]_9 );
  output [20:0]P;
  output [1:0]D;
  input CEP;
  input IPCORE_CLK;
  input RSTP;
  input [13:0]B;
  input [19:0]maximum_counter_value_1;
  input [0:0]\Switch5_out1_1_reg[1] ;
  input [7:0]\AND_out10_inferred__0/i__carry__0_0 ;
  input [7:0]\AND_out10_inferred__0/i__carry__0_1 ;
  input [1:0]\Switch5_out1_1_reg[0] ;
  input [1:0]\Switch5_out1_1_reg[0]_0 ;
  input [20:0]\reduced_reg_1_reg[1]_9 ;

  wire AND_out10_carry__0_i_2__1_n_0;
  wire AND_out10_carry__0_i_3__1_n_0;
  wire AND_out10_carry__0_i_4__1_n_0;
  wire AND_out10_carry__0_i_5__1_n_0;
  wire AND_out10_carry__0_i_6__1_n_0;
  wire AND_out10_carry__0_n_6;
  wire AND_out10_carry__0_n_7;
  wire AND_out10_carry_i_10__1_n_0;
  wire AND_out10_carry_i_11__1_n_0;
  wire AND_out10_carry_i_12__1_n_0;
  wire AND_out10_carry_i_13__1_n_0;
  wire AND_out10_carry_i_14__1_n_0;
  wire AND_out10_carry_i_15__1_n_0;
  wire AND_out10_carry_i_16__1_n_0;
  wire AND_out10_carry_i_1__1_n_0;
  wire AND_out10_carry_i_2__1_n_0;
  wire AND_out10_carry_i_3__1_n_0;
  wire AND_out10_carry_i_4__1_n_0;
  wire AND_out10_carry_i_5__1_n_0;
  wire AND_out10_carry_i_6__1_n_0;
  wire AND_out10_carry_i_7__1_n_0;
  wire AND_out10_carry_i_8__1_n_0;
  wire AND_out10_carry_i_9__1_n_0;
  wire AND_out10_carry_n_0;
  wire AND_out10_carry_n_1;
  wire AND_out10_carry_n_2;
  wire AND_out10_carry_n_3;
  wire AND_out10_carry_n_4;
  wire AND_out10_carry_n_5;
  wire AND_out10_carry_n_6;
  wire AND_out10_carry_n_7;
  wire [7:0]\AND_out10_inferred__0/i__carry__0_0 ;
  wire [7:0]\AND_out10_inferred__0/i__carry__0_1 ;
  wire \AND_out10_inferred__0/i__carry__0_n_6 ;
  wire \AND_out10_inferred__0/i__carry__0_n_7 ;
  wire \AND_out10_inferred__0/i__carry_n_0 ;
  wire \AND_out10_inferred__0/i__carry_n_1 ;
  wire \AND_out10_inferred__0/i__carry_n_2 ;
  wire \AND_out10_inferred__0/i__carry_n_3 ;
  wire \AND_out10_inferred__0/i__carry_n_4 ;
  wire \AND_out10_inferred__0/i__carry_n_5 ;
  wire \AND_out10_inferred__0/i__carry_n_6 ;
  wire \AND_out10_inferred__0/i__carry_n_7 ;
  wire [13:0]B;
  wire CEP;
  wire [1:0]D;
  wire IPCORE_CLK;
  wire [20:0]P;
  wire RSTP;
  wire Relational_Operator1_relop1;
  wire Relational_Operator_relop1;
  wire [1:0]\Switch5_out1_1_reg[0] ;
  wire [1:0]\Switch5_out1_1_reg[0]_0 ;
  wire [0:0]\Switch5_out1_1_reg[1] ;
  wire i__carry__0_i_3__1_n_0;
  wire [19:0]maximum_counter_value_1;
  wire modulating_signal_in_clock_cycles_1_reg_n_100;
  wire modulating_signal_in_clock_cycles_1_reg_n_101;
  wire modulating_signal_in_clock_cycles_1_reg_n_102;
  wire modulating_signal_in_clock_cycles_1_reg_n_103;
  wire modulating_signal_in_clock_cycles_1_reg_n_104;
  wire modulating_signal_in_clock_cycles_1_reg_n_105;
  wire modulating_signal_in_clock_cycles_1_reg_n_94;
  wire modulating_signal_in_clock_cycles_1_reg_n_95;
  wire modulating_signal_in_clock_cycles_1_reg_n_96;
  wire modulating_signal_in_clock_cycles_1_reg_n_97;
  wire modulating_signal_in_clock_cycles_1_reg_n_98;
  wire modulating_signal_in_clock_cycles_1_reg_n_99;
  wire [20:0]\reduced_reg_1_reg[1]_9 ;
  wire [7:0]NLW_AND_out10_carry_O_UNCONNECTED;
  wire [7:3]NLW_AND_out10_carry__0_CO_UNCONNECTED;
  wire [7:0]NLW_AND_out10_carry__0_O_UNCONNECTED;
  wire [7:0]\NLW_AND_out10_inferred__0/i__carry_O_UNCONNECTED ;
  wire [7:3]\NLW_AND_out10_inferred__0/i__carry__0_CO_UNCONNECTED ;
  wire [7:0]\NLW_AND_out10_inferred__0/i__carry__0_O_UNCONNECTED ;
  wire NLW_modulating_signal_in_clock_cycles_1_reg_CARRYCASCOUT_UNCONNECTED;
  wire NLW_modulating_signal_in_clock_cycles_1_reg_MULTSIGNOUT_UNCONNECTED;
  wire NLW_modulating_signal_in_clock_cycles_1_reg_OVERFLOW_UNCONNECTED;
  wire NLW_modulating_signal_in_clock_cycles_1_reg_PATTERNBDETECT_UNCONNECTED;
  wire NLW_modulating_signal_in_clock_cycles_1_reg_PATTERNDETECT_UNCONNECTED;
  wire NLW_modulating_signal_in_clock_cycles_1_reg_UNDERFLOW_UNCONNECTED;
  wire [29:0]NLW_modulating_signal_in_clock_cycles_1_reg_ACOUT_UNCONNECTED;
  wire [17:0]NLW_modulating_signal_in_clock_cycles_1_reg_BCOUT_UNCONNECTED;
  wire [3:0]NLW_modulating_signal_in_clock_cycles_1_reg_CARRYOUT_UNCONNECTED;
  wire [47:33]NLW_modulating_signal_in_clock_cycles_1_reg_P_UNCONNECTED;
  wire [47:0]NLW_modulating_signal_in_clock_cycles_1_reg_PCOUT_UNCONNECTED;
  wire [7:0]NLW_modulating_signal_in_clock_cycles_1_reg_XOROUT_UNCONNECTED;

  (* COMPARATOR_THRESHOLD = "11" *) 
  CARRY8 AND_out10_carry
       (.CI(1'b1),
        .CI_TOP(1'b0),
        .CO({AND_out10_carry_n_0,AND_out10_carry_n_1,AND_out10_carry_n_2,AND_out10_carry_n_3,AND_out10_carry_n_4,AND_out10_carry_n_5,AND_out10_carry_n_6,AND_out10_carry_n_7}),
        .DI({AND_out10_carry_i_1__1_n_0,AND_out10_carry_i_2__1_n_0,AND_out10_carry_i_3__1_n_0,AND_out10_carry_i_4__1_n_0,AND_out10_carry_i_5__1_n_0,AND_out10_carry_i_6__1_n_0,AND_out10_carry_i_7__1_n_0,AND_out10_carry_i_8__1_n_0}),
        .O(NLW_AND_out10_carry_O_UNCONNECTED[7:0]),
        .S({AND_out10_carry_i_9__1_n_0,AND_out10_carry_i_10__1_n_0,AND_out10_carry_i_11__1_n_0,AND_out10_carry_i_12__1_n_0,AND_out10_carry_i_13__1_n_0,AND_out10_carry_i_14__1_n_0,AND_out10_carry_i_15__1_n_0,AND_out10_carry_i_16__1_n_0}));
  (* COMPARATOR_THRESHOLD = "11" *) 
  CARRY8 AND_out10_carry__0
       (.CI(AND_out10_carry_n_0),
        .CI_TOP(1'b0),
        .CO({NLW_AND_out10_carry__0_CO_UNCONNECTED[7:3],Relational_Operator1_relop1,AND_out10_carry__0_n_6,AND_out10_carry__0_n_7}),
        .DI({1'b0,1'b0,1'b0,1'b0,1'b0,\Switch5_out1_1_reg[1] ,AND_out10_carry__0_i_2__1_n_0,AND_out10_carry__0_i_3__1_n_0}),
        .O(NLW_AND_out10_carry__0_O_UNCONNECTED[7:0]),
        .S({1'b0,1'b0,1'b0,1'b0,1'b0,AND_out10_carry__0_i_4__1_n_0,AND_out10_carry__0_i_5__1_n_0,AND_out10_carry__0_i_6__1_n_0}));
  LUT4 #(
    .INIT(16'h2F02)) 
    AND_out10_carry__0_i_2__1
       (.I0(P[18]),
        .I1(\reduced_reg_1_reg[1]_9 [18]),
        .I2(\reduced_reg_1_reg[1]_9 [19]),
        .I3(P[19]),
        .O(AND_out10_carry__0_i_2__1_n_0));
  LUT4 #(
    .INIT(16'h2F02)) 
    AND_out10_carry__0_i_3__1
       (.I0(P[16]),
        .I1(\reduced_reg_1_reg[1]_9 [16]),
        .I2(\reduced_reg_1_reg[1]_9 [17]),
        .I3(P[17]),
        .O(AND_out10_carry__0_i_3__1_n_0));
  LUT2 #(
    .INIT(4'h9)) 
    AND_out10_carry__0_i_4__1
       (.I0(P[20]),
        .I1(\reduced_reg_1_reg[1]_9 [20]),
        .O(AND_out10_carry__0_i_4__1_n_0));
  LUT4 #(
    .INIT(16'h9009)) 
    AND_out10_carry__0_i_5__1
       (.I0(P[18]),
        .I1(\reduced_reg_1_reg[1]_9 [18]),
        .I2(P[19]),
        .I3(\reduced_reg_1_reg[1]_9 [19]),
        .O(AND_out10_carry__0_i_5__1_n_0));
  LUT4 #(
    .INIT(16'h9009)) 
    AND_out10_carry__0_i_6__1
       (.I0(P[16]),
        .I1(\reduced_reg_1_reg[1]_9 [16]),
        .I2(P[17]),
        .I3(\reduced_reg_1_reg[1]_9 [17]),
        .O(AND_out10_carry__0_i_6__1_n_0));
  LUT4 #(
    .INIT(16'h9009)) 
    AND_out10_carry_i_10__1
       (.I0(P[12]),
        .I1(\reduced_reg_1_reg[1]_9 [12]),
        .I2(P[13]),
        .I3(\reduced_reg_1_reg[1]_9 [13]),
        .O(AND_out10_carry_i_10__1_n_0));
  LUT4 #(
    .INIT(16'h9009)) 
    AND_out10_carry_i_11__1
       (.I0(P[10]),
        .I1(\reduced_reg_1_reg[1]_9 [10]),
        .I2(P[11]),
        .I3(\reduced_reg_1_reg[1]_9 [11]),
        .O(AND_out10_carry_i_11__1_n_0));
  LUT4 #(
    .INIT(16'h9009)) 
    AND_out10_carry_i_12__1
       (.I0(P[8]),
        .I1(\reduced_reg_1_reg[1]_9 [8]),
        .I2(P[9]),
        .I3(\reduced_reg_1_reg[1]_9 [9]),
        .O(AND_out10_carry_i_12__1_n_0));
  LUT4 #(
    .INIT(16'h9009)) 
    AND_out10_carry_i_13__1
       (.I0(P[6]),
        .I1(\reduced_reg_1_reg[1]_9 [6]),
        .I2(P[7]),
        .I3(\reduced_reg_1_reg[1]_9 [7]),
        .O(AND_out10_carry_i_13__1_n_0));
  LUT4 #(
    .INIT(16'h9009)) 
    AND_out10_carry_i_14__1
       (.I0(P[4]),
        .I1(\reduced_reg_1_reg[1]_9 [4]),
        .I2(P[5]),
        .I3(\reduced_reg_1_reg[1]_9 [5]),
        .O(AND_out10_carry_i_14__1_n_0));
  LUT4 #(
    .INIT(16'h9009)) 
    AND_out10_carry_i_15__1
       (.I0(P[2]),
        .I1(\reduced_reg_1_reg[1]_9 [2]),
        .I2(P[3]),
        .I3(\reduced_reg_1_reg[1]_9 [3]),
        .O(AND_out10_carry_i_15__1_n_0));
  LUT4 #(
    .INIT(16'h9009)) 
    AND_out10_carry_i_16__1
       (.I0(P[0]),
        .I1(\reduced_reg_1_reg[1]_9 [0]),
        .I2(P[1]),
        .I3(\reduced_reg_1_reg[1]_9 [1]),
        .O(AND_out10_carry_i_16__1_n_0));
  LUT4 #(
    .INIT(16'h2F02)) 
    AND_out10_carry_i_1__1
       (.I0(P[14]),
        .I1(\reduced_reg_1_reg[1]_9 [14]),
        .I2(\reduced_reg_1_reg[1]_9 [15]),
        .I3(P[15]),
        .O(AND_out10_carry_i_1__1_n_0));
  LUT4 #(
    .INIT(16'h2F02)) 
    AND_out10_carry_i_2__1
       (.I0(P[12]),
        .I1(\reduced_reg_1_reg[1]_9 [12]),
        .I2(\reduced_reg_1_reg[1]_9 [13]),
        .I3(P[13]),
        .O(AND_out10_carry_i_2__1_n_0));
  LUT4 #(
    .INIT(16'h2F02)) 
    AND_out10_carry_i_3__1
       (.I0(P[10]),
        .I1(\reduced_reg_1_reg[1]_9 [10]),
        .I2(\reduced_reg_1_reg[1]_9 [11]),
        .I3(P[11]),
        .O(AND_out10_carry_i_3__1_n_0));
  LUT4 #(
    .INIT(16'h2F02)) 
    AND_out10_carry_i_4__1
       (.I0(P[8]),
        .I1(\reduced_reg_1_reg[1]_9 [8]),
        .I2(\reduced_reg_1_reg[1]_9 [9]),
        .I3(P[9]),
        .O(AND_out10_carry_i_4__1_n_0));
  LUT4 #(
    .INIT(16'h2F02)) 
    AND_out10_carry_i_5__1
       (.I0(P[6]),
        .I1(\reduced_reg_1_reg[1]_9 [6]),
        .I2(\reduced_reg_1_reg[1]_9 [7]),
        .I3(P[7]),
        .O(AND_out10_carry_i_5__1_n_0));
  LUT4 #(
    .INIT(16'h2F02)) 
    AND_out10_carry_i_6__1
       (.I0(P[4]),
        .I1(\reduced_reg_1_reg[1]_9 [4]),
        .I2(\reduced_reg_1_reg[1]_9 [5]),
        .I3(P[5]),
        .O(AND_out10_carry_i_6__1_n_0));
  LUT4 #(
    .INIT(16'h2F02)) 
    AND_out10_carry_i_7__1
       (.I0(P[2]),
        .I1(\reduced_reg_1_reg[1]_9 [2]),
        .I2(\reduced_reg_1_reg[1]_9 [3]),
        .I3(P[3]),
        .O(AND_out10_carry_i_7__1_n_0));
  LUT4 #(
    .INIT(16'h2F02)) 
    AND_out10_carry_i_8__1
       (.I0(P[0]),
        .I1(\reduced_reg_1_reg[1]_9 [0]),
        .I2(\reduced_reg_1_reg[1]_9 [1]),
        .I3(P[1]),
        .O(AND_out10_carry_i_8__1_n_0));
  LUT4 #(
    .INIT(16'h9009)) 
    AND_out10_carry_i_9__1
       (.I0(P[14]),
        .I1(\reduced_reg_1_reg[1]_9 [14]),
        .I2(P[15]),
        .I3(\reduced_reg_1_reg[1]_9 [15]),
        .O(AND_out10_carry_i_9__1_n_0));
  (* COMPARATOR_THRESHOLD = "11" *) 
  CARRY8 \AND_out10_inferred__0/i__carry 
       (.CI(1'b1),
        .CI_TOP(1'b0),
        .CO({\AND_out10_inferred__0/i__carry_n_0 ,\AND_out10_inferred__0/i__carry_n_1 ,\AND_out10_inferred__0/i__carry_n_2 ,\AND_out10_inferred__0/i__carry_n_3 ,\AND_out10_inferred__0/i__carry_n_4 ,\AND_out10_inferred__0/i__carry_n_5 ,\AND_out10_inferred__0/i__carry_n_6 ,\AND_out10_inferred__0/i__carry_n_7 }),
        .DI(\AND_out10_inferred__0/i__carry__0_0 ),
        .O(\NLW_AND_out10_inferred__0/i__carry_O_UNCONNECTED [7:0]),
        .S(\AND_out10_inferred__0/i__carry__0_1 ));
  (* COMPARATOR_THRESHOLD = "11" *) 
  CARRY8 \AND_out10_inferred__0/i__carry__0 
       (.CI(\AND_out10_inferred__0/i__carry_n_0 ),
        .CI_TOP(1'b0),
        .CO({\NLW_AND_out10_inferred__0/i__carry__0_CO_UNCONNECTED [7:3],Relational_Operator_relop1,\AND_out10_inferred__0/i__carry__0_n_6 ,\AND_out10_inferred__0/i__carry__0_n_7 }),
        .DI({1'b0,1'b0,1'b0,1'b0,1'b0,P[20],\Switch5_out1_1_reg[0] }),
        .O(\NLW_AND_out10_inferred__0/i__carry__0_O_UNCONNECTED [7:0]),
        .S({1'b0,1'b0,1'b0,1'b0,1'b0,i__carry__0_i_3__1_n_0,\Switch5_out1_1_reg[0]_0 }));
  (* SOFT_HLUTNM = "soft_lutpair52" *) 
  LUT2 #(
    .INIT(4'h2)) 
    \Switch5_out1_1[0]_i_1 
       (.I0(Relational_Operator1_relop1),
        .I1(Relational_Operator_relop1),
        .O(D[1]));
  (* SOFT_HLUTNM = "soft_lutpair52" *) 
  LUT1 #(
    .INIT(2'h2)) 
    \Switch5_out1_1[1]_i_1 
       (.I0(Relational_Operator1_relop1),
        .O(D[0]));
  LUT1 #(
    .INIT(2'h1)) 
    i__carry__0_i_3__1
       (.I0(P[20]),
        .O(i__carry__0_i_3__1_n_0));
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
    modulating_signal_in_clock_cycles_1_reg
       (.A({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,maximum_counter_value_1}),
        .ACIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .ACOUT(NLW_modulating_signal_in_clock_cycles_1_reg_ACOUT_UNCONNECTED[29:0]),
        .ALUMODE({1'b0,1'b0,1'b0,1'b0}),
        .B({B[13],B[13],B[13],B[13],B}),
        .BCIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .BCOUT(NLW_modulating_signal_in_clock_cycles_1_reg_BCOUT_UNCONNECTED[17:0]),
        .C({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .CARRYCASCIN(1'b0),
        .CARRYCASCOUT(NLW_modulating_signal_in_clock_cycles_1_reg_CARRYCASCOUT_UNCONNECTED),
        .CARRYIN(1'b0),
        .CARRYINSEL({1'b0,1'b0,1'b0}),
        .CARRYOUT(NLW_modulating_signal_in_clock_cycles_1_reg_CARRYOUT_UNCONNECTED[3:0]),
        .CEA1(1'b0),
        .CEA2(CEP),
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
        .CEP(CEP),
        .CLK(IPCORE_CLK),
        .D({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .INMODE({1'b0,1'b0,1'b0,1'b0,1'b0}),
        .MULTSIGNIN(1'b0),
        .MULTSIGNOUT(NLW_modulating_signal_in_clock_cycles_1_reg_MULTSIGNOUT_UNCONNECTED),
        .OPMODE({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b1,1'b0,1'b1}),
        .OVERFLOW(NLW_modulating_signal_in_clock_cycles_1_reg_OVERFLOW_UNCONNECTED),
        .P({NLW_modulating_signal_in_clock_cycles_1_reg_P_UNCONNECTED[47:33],P,modulating_signal_in_clock_cycles_1_reg_n_94,modulating_signal_in_clock_cycles_1_reg_n_95,modulating_signal_in_clock_cycles_1_reg_n_96,modulating_signal_in_clock_cycles_1_reg_n_97,modulating_signal_in_clock_cycles_1_reg_n_98,modulating_signal_in_clock_cycles_1_reg_n_99,modulating_signal_in_clock_cycles_1_reg_n_100,modulating_signal_in_clock_cycles_1_reg_n_101,modulating_signal_in_clock_cycles_1_reg_n_102,modulating_signal_in_clock_cycles_1_reg_n_103,modulating_signal_in_clock_cycles_1_reg_n_104,modulating_signal_in_clock_cycles_1_reg_n_105}),
        .PATTERNBDETECT(NLW_modulating_signal_in_clock_cycles_1_reg_PATTERNBDETECT_UNCONNECTED),
        .PATTERNDETECT(NLW_modulating_signal_in_clock_cycles_1_reg_PATTERNDETECT_UNCONNECTED),
        .PCIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .PCOUT(NLW_modulating_signal_in_clock_cycles_1_reg_PCOUT_UNCONNECTED[47:0]),
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
        .UNDERFLOW(NLW_modulating_signal_in_clock_cycles_1_reg_UNDERFLOW_UNCONNECTED),
        .XOROUT(NLW_modulating_signal_in_clock_cycles_1_reg_XOROUT_UNCONNECTED[7:0]));
endmodule

(* ORIG_REF_NAME = "PWM_SS_3L_ip_src_PWM_SS_Ctrl" *) 
module zusys_PWM_SS_3L_ip_0_0_PWM_SS_3L_ip_src_PWM_SS_Ctrl
   (D,
    Period_Center,
    Period_Start,
    SSa2_OUT,
    SSa1_OUT,
    SSb2_OUT,
    SSb1_OUT,
    SSc2_OUT,
    SSc1_OUT,
    RSTP,
    CEP,
    IPCORE_CLK,
    \reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2 ,
    \delayMatch2_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2 ,
    \delayMatch5_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2 ,
    \delayMatch8_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2 ,
    write_PWM_en_AXI,
    \HDL_Counter2_count_reg[19] ,
    \max_counter_value_1_reg[19] ,
    \maximum_counter_value_1_reg[8] ,
    \min_pulse_width_AXI_1_reg[13] ,
    SSc2_IN_External,
    SSc1_IN_External,
    SSb2_IN_External,
    SSb1_IN_External,
    SSa2_IN_External,
    SSa1_IN_External,
    \delayMatch1_reg_reg[0][13] ,
    m_u1_norm,
    \delayMatch3_reg_reg[0][13] ,
    m_u2_norm,
    \delayMatch5_reg_reg[0][13] ,
    m_u3_norm);
  output [0:0]D;
  output Period_Center;
  output Period_Start;
  output SSa2_OUT;
  output SSa1_OUT;
  output SSb2_OUT;
  output SSb1_OUT;
  output SSc2_OUT;
  output SSc1_OUT;
  input RSTP;
  input CEP;
  input IPCORE_CLK;
  input [1:0]\reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2 ;
  input [1:0]\delayMatch2_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2 ;
  input [1:0]\delayMatch5_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2 ;
  input [1:0]\delayMatch8_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2 ;
  input write_PWM_en_AXI;
  input \HDL_Counter2_count_reg[19] ;
  input [19:0]\max_counter_value_1_reg[19] ;
  input \maximum_counter_value_1_reg[8] ;
  input [13:0]\min_pulse_width_AXI_1_reg[13] ;
  input SSc2_IN_External;
  input SSc1_IN_External;
  input SSb2_IN_External;
  input SSb1_IN_External;
  input SSa2_IN_External;
  input SSa1_IN_External;
  input [13:0]\delayMatch1_reg_reg[0][13] ;
  input [13:0]m_u1_norm;
  input [13:0]\delayMatch3_reg_reg[0][13] ;
  input [13:0]m_u2_norm;
  input [13:0]\delayMatch5_reg_reg[0][13] ;
  input [13:0]m_u3_norm;

  wire CEP;
  wire [0:0]D;
  wire [0:1]Demux_out1;
  wire [0:1]Demux_out2;
  wire [0:1]Demux_out3;
  wire [0:1]GenPWM_out1;
  wire [0:1]GenPWM_out2;
  wire [0:1]GenPWM_out3;
  wire GenPWM_out4;
  wire GenPWM_out5;
  wire \HDL_Counter2_count_reg[19] ;
  wire IPCORE_CLK;
  wire [0:5]Mux_out1;
  wire Period_Center;
  wire Period_Start;
  wire RSTP;
  wire SSa1_IN_External;
  wire SSa1_OUT;
  wire SSa2_IN_External;
  wire SSa2_OUT;
  wire SSb1_IN_External;
  wire SSb1_OUT;
  wire SSb2_IN_External;
  wire SSb2_OUT;
  wire SSc1_IN_External;
  wire SSc1_OUT;
  wire SSc2_IN_External;
  wire SSc2_OUT;
  wire [13:0]U1_norm;
  wire [13:0]U2_norm;
  wire [13:0]U3_norm;
  wire [0:0]delayMatch1_reg;
  wire [13:0]\delayMatch1_reg_reg[0][13] ;
  wire [0:0]delayMatch2_reg;
  wire [1:0]\delayMatch2_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2 ;
  wire [0:0]delayMatch3_1_reg;
  wire [0:0]delayMatch3_1_reg_1;
  wire [13:0]\delayMatch3_reg_reg[0][13] ;
  wire [13:0]\delayMatch5_reg_reg[0][13] ;
  wire [1:0]\delayMatch5_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2 ;
  wire [0:0]delayMatch6_1_reg;
  wire [0:0]delayMatch6_1_reg_1;
  wire [1:0]\delayMatch8_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2 ;
  wire [0:0]delayMatch_1_reg;
  wire [0:0]delayMatch_1_reg_1;
  wire [0:1]delayMatch_1_reg_1__0;
  wire [0:1]delayMatch_1_reg_2;
  wire [0:1]delayMatch_1_reg_3;
  wire [0:1]delayMatch_1_reg_4;
  wire [0:1]delayMatch_1_reg_5;
  wire [0:1]delayMatch_1_reg__0;
  wire [13:0]m_u1_norm;
  wire [13:0]m_u2_norm;
  wire [13:0]m_u3_norm;
  wire [19:0]\max_counter_value_1_reg[19] ;
  wire \maximum_counter_value_1_reg[8] ;
  wire [13:0]\min_pulse_width_AXI_1_reg[13] ;
  wire [1:0]\reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2 ;
  wire write_PWM_en_AXI;

  LUT4 #(
    .INIT(16'hFE02)) 
    \delayMatch1_reg[0][0]_i_1 
       (.I0(\delayMatch1_reg_reg[0][13] [0]),
        .I1(\reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2 [0]),
        .I2(\reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2 [1]),
        .I3(m_u1_norm[0]),
        .O(U1_norm[0]));
  LUT4 #(
    .INIT(16'hFE02)) 
    \delayMatch1_reg[0][10]_i_1 
       (.I0(\delayMatch1_reg_reg[0][13] [10]),
        .I1(\reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2 [0]),
        .I2(\reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2 [1]),
        .I3(m_u1_norm[10]),
        .O(U1_norm[10]));
  LUT4 #(
    .INIT(16'hFE02)) 
    \delayMatch1_reg[0][11]_i_1 
       (.I0(\delayMatch1_reg_reg[0][13] [11]),
        .I1(\reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2 [0]),
        .I2(\reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2 [1]),
        .I3(m_u1_norm[11]),
        .O(U1_norm[11]));
  LUT4 #(
    .INIT(16'hFE02)) 
    \delayMatch1_reg[0][12]_i_1 
       (.I0(\delayMatch1_reg_reg[0][13] [12]),
        .I1(\reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2 [0]),
        .I2(\reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2 [1]),
        .I3(m_u1_norm[12]),
        .O(U1_norm[12]));
  LUT4 #(
    .INIT(16'hFE02)) 
    \delayMatch1_reg[0][13]_i_1 
       (.I0(\delayMatch1_reg_reg[0][13] [13]),
        .I1(\reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2 [0]),
        .I2(\reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2 [1]),
        .I3(m_u1_norm[13]),
        .O(U1_norm[13]));
  LUT4 #(
    .INIT(16'hFE02)) 
    \delayMatch1_reg[0][1]_i_1 
       (.I0(\delayMatch1_reg_reg[0][13] [1]),
        .I1(\reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2 [0]),
        .I2(\reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2 [1]),
        .I3(m_u1_norm[1]),
        .O(U1_norm[1]));
  LUT4 #(
    .INIT(16'hFE02)) 
    \delayMatch1_reg[0][2]_i_1 
       (.I0(\delayMatch1_reg_reg[0][13] [2]),
        .I1(\reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2 [0]),
        .I2(\reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2 [1]),
        .I3(m_u1_norm[2]),
        .O(U1_norm[2]));
  LUT4 #(
    .INIT(16'hFE02)) 
    \delayMatch1_reg[0][3]_i_1 
       (.I0(\delayMatch1_reg_reg[0][13] [3]),
        .I1(\reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2 [0]),
        .I2(\reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2 [1]),
        .I3(m_u1_norm[3]),
        .O(U1_norm[3]));
  LUT4 #(
    .INIT(16'hFE02)) 
    \delayMatch1_reg[0][4]_i_1 
       (.I0(\delayMatch1_reg_reg[0][13] [4]),
        .I1(\reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2 [0]),
        .I2(\reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2 [1]),
        .I3(m_u1_norm[4]),
        .O(U1_norm[4]));
  LUT4 #(
    .INIT(16'hFE02)) 
    \delayMatch1_reg[0][5]_i_1 
       (.I0(\delayMatch1_reg_reg[0][13] [5]),
        .I1(\reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2 [0]),
        .I2(\reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2 [1]),
        .I3(m_u1_norm[5]),
        .O(U1_norm[5]));
  LUT4 #(
    .INIT(16'hFE02)) 
    \delayMatch1_reg[0][6]_i_1 
       (.I0(\delayMatch1_reg_reg[0][13] [6]),
        .I1(\reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2 [0]),
        .I2(\reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2 [1]),
        .I3(m_u1_norm[6]),
        .O(U1_norm[6]));
  LUT4 #(
    .INIT(16'hFE02)) 
    \delayMatch1_reg[0][7]_i_1 
       (.I0(\delayMatch1_reg_reg[0][13] [7]),
        .I1(\reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2 [0]),
        .I2(\reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2 [1]),
        .I3(m_u1_norm[7]),
        .O(U1_norm[7]));
  LUT4 #(
    .INIT(16'hFE02)) 
    \delayMatch1_reg[0][8]_i_1 
       (.I0(\delayMatch1_reg_reg[0][13] [8]),
        .I1(\reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2 [0]),
        .I2(\reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2 [1]),
        .I3(m_u1_norm[8]),
        .O(U1_norm[8]));
  LUT4 #(
    .INIT(16'hFE02)) 
    \delayMatch1_reg[0][9]_i_1 
       (.I0(\delayMatch1_reg_reg[0][13] [9]),
        .I1(\reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2 [0]),
        .I2(\reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2 [1]),
        .I3(m_u1_norm[9]),
        .O(U1_norm[9]));
  FDRE \delayMatch1_reg_reg[0] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(GenPWM_out4),
        .Q(delayMatch1_reg),
        .R(RSTP));
  FDRE \delayMatch1_reg_reg[1] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(delayMatch1_reg),
        .Q(Period_Center),
        .R(RSTP));
  FDRE \delayMatch2_reg_reg[0] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(GenPWM_out5),
        .Q(delayMatch2_reg),
        .R(RSTP));
  FDRE \delayMatch2_reg_reg[1] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(delayMatch2_reg),
        .Q(Period_Start),
        .R(RSTP));
  LUT4 #(
    .INIT(16'hFE02)) 
    \delayMatch3_reg[0][0]_i_1 
       (.I0(\delayMatch3_reg_reg[0][13] [0]),
        .I1(\reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2 [0]),
        .I2(\reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2 [1]),
        .I3(m_u2_norm[0]),
        .O(U2_norm[0]));
  LUT4 #(
    .INIT(16'hFE02)) 
    \delayMatch3_reg[0][10]_i_1 
       (.I0(\delayMatch3_reg_reg[0][13] [10]),
        .I1(\reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2 [0]),
        .I2(\reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2 [1]),
        .I3(m_u2_norm[10]),
        .O(U2_norm[10]));
  LUT4 #(
    .INIT(16'hFE02)) 
    \delayMatch3_reg[0][11]_i_1 
       (.I0(\delayMatch3_reg_reg[0][13] [11]),
        .I1(\reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2 [0]),
        .I2(\reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2 [1]),
        .I3(m_u2_norm[11]),
        .O(U2_norm[11]));
  LUT4 #(
    .INIT(16'hFE02)) 
    \delayMatch3_reg[0][12]_i_1 
       (.I0(\delayMatch3_reg_reg[0][13] [12]),
        .I1(\reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2 [0]),
        .I2(\reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2 [1]),
        .I3(m_u2_norm[12]),
        .O(U2_norm[12]));
  LUT4 #(
    .INIT(16'hFE02)) 
    \delayMatch3_reg[0][13]_i_1 
       (.I0(\delayMatch3_reg_reg[0][13] [13]),
        .I1(\reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2 [0]),
        .I2(\reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2 [1]),
        .I3(m_u2_norm[13]),
        .O(U2_norm[13]));
  LUT4 #(
    .INIT(16'hFE02)) 
    \delayMatch3_reg[0][1]_i_1 
       (.I0(\delayMatch3_reg_reg[0][13] [1]),
        .I1(\reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2 [0]),
        .I2(\reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2 [1]),
        .I3(m_u2_norm[1]),
        .O(U2_norm[1]));
  LUT4 #(
    .INIT(16'hFE02)) 
    \delayMatch3_reg[0][2]_i_1 
       (.I0(\delayMatch3_reg_reg[0][13] [2]),
        .I1(\reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2 [0]),
        .I2(\reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2 [1]),
        .I3(m_u2_norm[2]),
        .O(U2_norm[2]));
  LUT4 #(
    .INIT(16'hFE02)) 
    \delayMatch3_reg[0][3]_i_1 
       (.I0(\delayMatch3_reg_reg[0][13] [3]),
        .I1(\reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2 [0]),
        .I2(\reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2 [1]),
        .I3(m_u2_norm[3]),
        .O(U2_norm[3]));
  LUT4 #(
    .INIT(16'hFE02)) 
    \delayMatch3_reg[0][4]_i_1 
       (.I0(\delayMatch3_reg_reg[0][13] [4]),
        .I1(\reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2 [0]),
        .I2(\reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2 [1]),
        .I3(m_u2_norm[4]),
        .O(U2_norm[4]));
  LUT4 #(
    .INIT(16'hFE02)) 
    \delayMatch3_reg[0][5]_i_1 
       (.I0(\delayMatch3_reg_reg[0][13] [5]),
        .I1(\reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2 [0]),
        .I2(\reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2 [1]),
        .I3(m_u2_norm[5]),
        .O(U2_norm[5]));
  LUT4 #(
    .INIT(16'hFE02)) 
    \delayMatch3_reg[0][6]_i_1 
       (.I0(\delayMatch3_reg_reg[0][13] [6]),
        .I1(\reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2 [0]),
        .I2(\reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2 [1]),
        .I3(m_u2_norm[6]),
        .O(U2_norm[6]));
  LUT4 #(
    .INIT(16'hFE02)) 
    \delayMatch3_reg[0][7]_i_1 
       (.I0(\delayMatch3_reg_reg[0][13] [7]),
        .I1(\reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2 [0]),
        .I2(\reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2 [1]),
        .I3(m_u2_norm[7]),
        .O(U2_norm[7]));
  LUT4 #(
    .INIT(16'hFE02)) 
    \delayMatch3_reg[0][8]_i_1 
       (.I0(\delayMatch3_reg_reg[0][13] [8]),
        .I1(\reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2 [0]),
        .I2(\reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2 [1]),
        .I3(m_u2_norm[8]),
        .O(U2_norm[8]));
  LUT4 #(
    .INIT(16'hFE02)) 
    \delayMatch3_reg[0][9]_i_1 
       (.I0(\delayMatch3_reg_reg[0][13] [9]),
        .I1(\reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2 [0]),
        .I2(\reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2 [1]),
        .I3(m_u2_norm[9]),
        .O(U2_norm[9]));
  LUT4 #(
    .INIT(16'hFE02)) 
    \delayMatch5_reg[0][0]_i_1 
       (.I0(\delayMatch5_reg_reg[0][13] [0]),
        .I1(\reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2 [0]),
        .I2(\reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2 [1]),
        .I3(m_u3_norm[0]),
        .O(U3_norm[0]));
  LUT4 #(
    .INIT(16'hFE02)) 
    \delayMatch5_reg[0][10]_i_1 
       (.I0(\delayMatch5_reg_reg[0][13] [10]),
        .I1(\reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2 [0]),
        .I2(\reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2 [1]),
        .I3(m_u3_norm[10]),
        .O(U3_norm[10]));
  LUT4 #(
    .INIT(16'hFE02)) 
    \delayMatch5_reg[0][11]_i_1 
       (.I0(\delayMatch5_reg_reg[0][13] [11]),
        .I1(\reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2 [0]),
        .I2(\reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2 [1]),
        .I3(m_u3_norm[11]),
        .O(U3_norm[11]));
  LUT4 #(
    .INIT(16'hFE02)) 
    \delayMatch5_reg[0][12]_i_1 
       (.I0(\delayMatch5_reg_reg[0][13] [12]),
        .I1(\reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2 [0]),
        .I2(\reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2 [1]),
        .I3(m_u3_norm[12]),
        .O(U3_norm[12]));
  LUT4 #(
    .INIT(16'hFE02)) 
    \delayMatch5_reg[0][13]_i_1 
       (.I0(\delayMatch5_reg_reg[0][13] [13]),
        .I1(\reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2 [0]),
        .I2(\reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2 [1]),
        .I3(m_u3_norm[13]),
        .O(U3_norm[13]));
  LUT4 #(
    .INIT(16'hFE02)) 
    \delayMatch5_reg[0][1]_i_1 
       (.I0(\delayMatch5_reg_reg[0][13] [1]),
        .I1(\reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2 [0]),
        .I2(\reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2 [1]),
        .I3(m_u3_norm[1]),
        .O(U3_norm[1]));
  LUT4 #(
    .INIT(16'hFE02)) 
    \delayMatch5_reg[0][2]_i_1 
       (.I0(\delayMatch5_reg_reg[0][13] [2]),
        .I1(\reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2 [0]),
        .I2(\reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2 [1]),
        .I3(m_u3_norm[2]),
        .O(U3_norm[2]));
  LUT4 #(
    .INIT(16'hFE02)) 
    \delayMatch5_reg[0][3]_i_1 
       (.I0(\delayMatch5_reg_reg[0][13] [3]),
        .I1(\reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2 [0]),
        .I2(\reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2 [1]),
        .I3(m_u3_norm[3]),
        .O(U3_norm[3]));
  LUT4 #(
    .INIT(16'hFE02)) 
    \delayMatch5_reg[0][4]_i_1 
       (.I0(\delayMatch5_reg_reg[0][13] [4]),
        .I1(\reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2 [0]),
        .I2(\reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2 [1]),
        .I3(m_u3_norm[4]),
        .O(U3_norm[4]));
  LUT4 #(
    .INIT(16'hFE02)) 
    \delayMatch5_reg[0][5]_i_1 
       (.I0(\delayMatch5_reg_reg[0][13] [5]),
        .I1(\reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2 [0]),
        .I2(\reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2 [1]),
        .I3(m_u3_norm[5]),
        .O(U3_norm[5]));
  LUT4 #(
    .INIT(16'hFE02)) 
    \delayMatch5_reg[0][6]_i_1 
       (.I0(\delayMatch5_reg_reg[0][13] [6]),
        .I1(\reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2 [0]),
        .I2(\reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2 [1]),
        .I3(m_u3_norm[6]),
        .O(U3_norm[6]));
  LUT4 #(
    .INIT(16'hFE02)) 
    \delayMatch5_reg[0][7]_i_1 
       (.I0(\delayMatch5_reg_reg[0][13] [7]),
        .I1(\reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2 [0]),
        .I2(\reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2 [1]),
        .I3(m_u3_norm[7]),
        .O(U3_norm[7]));
  LUT4 #(
    .INIT(16'hFE02)) 
    \delayMatch5_reg[0][8]_i_1 
       (.I0(\delayMatch5_reg_reg[0][13] [8]),
        .I1(\reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2 [0]),
        .I2(\reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2 [1]),
        .I3(m_u3_norm[8]),
        .O(U3_norm[8]));
  LUT4 #(
    .INIT(16'hFE02)) 
    \delayMatch5_reg[0][9]_i_1 
       (.I0(\delayMatch5_reg_reg[0][13] [9]),
        .I1(\reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2 [0]),
        .I2(\reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2 [1]),
        .I3(m_u3_norm[9]),
        .O(U3_norm[9]));
  FDRE \delayMatch_1_reg_1_reg[0] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(SSa2_IN_External),
        .Q(delayMatch_1_reg_1__0[0]),
        .R(RSTP));
  FDRE \delayMatch_1_reg_1_reg[1] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(delayMatch_1_reg_1__0[0]),
        .Q(delayMatch_1_reg_1__0[1]),
        .R(RSTP));
  FDRE \delayMatch_1_reg_1_reg[2] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(delayMatch_1_reg_1__0[1]),
        .Q(Mux_out1[1]),
        .R(RSTP));
  FDRE \delayMatch_1_reg_2_reg[0] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(SSb1_IN_External),
        .Q(delayMatch_1_reg_2[0]),
        .R(RSTP));
  FDRE \delayMatch_1_reg_2_reg[1] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(delayMatch_1_reg_2[0]),
        .Q(delayMatch_1_reg_2[1]),
        .R(RSTP));
  FDRE \delayMatch_1_reg_2_reg[2] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(delayMatch_1_reg_2[1]),
        .Q(Mux_out1[2]),
        .R(RSTP));
  FDRE \delayMatch_1_reg_3_reg[0] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(SSb2_IN_External),
        .Q(delayMatch_1_reg_3[0]),
        .R(RSTP));
  FDRE \delayMatch_1_reg_3_reg[1] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(delayMatch_1_reg_3[0]),
        .Q(delayMatch_1_reg_3[1]),
        .R(RSTP));
  FDRE \delayMatch_1_reg_3_reg[2] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(delayMatch_1_reg_3[1]),
        .Q(Mux_out1[3]),
        .R(RSTP));
  FDRE \delayMatch_1_reg_4_reg[0] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(SSc1_IN_External),
        .Q(delayMatch_1_reg_4[0]),
        .R(RSTP));
  FDRE \delayMatch_1_reg_4_reg[1] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(delayMatch_1_reg_4[0]),
        .Q(delayMatch_1_reg_4[1]),
        .R(RSTP));
  FDRE \delayMatch_1_reg_4_reg[2] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(delayMatch_1_reg_4[1]),
        .Q(Mux_out1[4]),
        .R(RSTP));
  FDRE \delayMatch_1_reg_5_reg[0] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(SSc2_IN_External),
        .Q(delayMatch_1_reg_5[0]),
        .R(RSTP));
  FDRE \delayMatch_1_reg_5_reg[1] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(delayMatch_1_reg_5[0]),
        .Q(delayMatch_1_reg_5[1]),
        .R(RSTP));
  FDRE \delayMatch_1_reg_5_reg[2] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(delayMatch_1_reg_5[1]),
        .Q(Mux_out1[5]),
        .R(RSTP));
  FDRE \delayMatch_1_reg_reg[0] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(SSa1_IN_External),
        .Q(delayMatch_1_reg__0[0]),
        .R(RSTP));
  FDRE \delayMatch_1_reg_reg[1] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(delayMatch_1_reg__0[0]),
        .Q(delayMatch_1_reg__0[1]),
        .R(RSTP));
  FDRE \delayMatch_1_reg_reg[2] 
       (.C(IPCORE_CLK),
        .CE(CEP),
        .D(delayMatch_1_reg__0[1]),
        .Q(Mux_out1[0]),
        .R(RSTP));
  zusys_PWM_SS_3L_ip_0_0_PWM_SS_3L_ip_src_Chose_SS u_Chose_SS
       (.CEP(CEP),
        .Demux_out1(Demux_out1),
        .Demux_out2(Demux_out2),
        .Demux_out3(Demux_out3),
        .IPCORE_CLK(IPCORE_CLK),
        .Q({GenPWM_out1[0],GenPWM_out1[1]}),
        .RSTP(RSTP),
        .SSa1_OUT(SSa1_OUT),
        .SSa2_OUT(SSa2_OUT),
        .SSb1_OUT(SSb1_OUT),
        .SSb1_OUT_0({GenPWM_out2[0],GenPWM_out2[1]}),
        .SSb2_OUT(SSb2_OUT),
        .SSc1_OUT(SSc1_OUT),
        .SSc1_OUT_0({GenPWM_out3[0],GenPWM_out3[1]}),
        .SSc2_OUT(SSc2_OUT),
        .\delayMatch2_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2_0 (\delayMatch2_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2 ),
        .delayMatch3_1_reg(delayMatch3_1_reg),
        .delayMatch3_1_reg_1(delayMatch3_1_reg_1),
        .\delayMatch5_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2_0 (\delayMatch5_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2 ),
        .delayMatch6_1_reg(delayMatch6_1_reg),
        .delayMatch6_1_reg_1(delayMatch6_1_reg_1),
        .\delayMatch8_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2_0 (\delayMatch8_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2 ),
        .delayMatch_1_reg(delayMatch_1_reg),
        .delayMatch_1_reg_1(delayMatch_1_reg_1),
        .\reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2_0 (\reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2 [1]));
  zusys_PWM_SS_3L_ip_0_0_PWM_SS_3L_ip_src_GenPWM u_GenPWM
       (.CEP(CEP),
        .D(GenPWM_out4),
        .Demux_out1(Demux_out1),
        .Demux_out2(Demux_out2),
        .Demux_out3(Demux_out3),
        .GenPWM_out5(GenPWM_out5),
        .\HDL_Counter2_count_reg[19]_0 (\HDL_Counter2_count_reg[19] ),
        .IPCORE_CLK(IPCORE_CLK),
        .Mux_out1(Mux_out1),
        .PWM_en_AXI_2_reg_0(D),
        .Q({GenPWM_out1[0],GenPWM_out1[1]}),
        .RSTP(RSTP),
        .\Switch4_out1_1_reg[0]_0 ({GenPWM_out2[0],GenPWM_out2[1]}),
        .\Switch5_out1_1_reg[0]_0 ({GenPWM_out3[0],GenPWM_out3[1]}),
        .\delayMatch1_reg_reg[0][13]_0 (U1_norm),
        .delayMatch3_1_reg(delayMatch3_1_reg),
        .delayMatch3_1_reg_1(delayMatch3_1_reg_1),
        .\delayMatch3_reg_reg[0][13]_0 (U2_norm),
        .\delayMatch5_reg_reg[0][13]_0 (U3_norm),
        .delayMatch6_1_reg(delayMatch6_1_reg),
        .delayMatch6_1_reg_1(delayMatch6_1_reg_1),
        .delayMatch_1_reg(delayMatch_1_reg),
        .delayMatch_1_reg_1(delayMatch_1_reg_1),
        .\max_counter_value_1_reg[19]_0 (\max_counter_value_1_reg[19] ),
        .\maximum_counter_value_1_reg[8]_0 (\maximum_counter_value_1_reg[8] ),
        .\min_pulse_width_AXI_1_reg[13]_0 (\min_pulse_width_AXI_1_reg[13] ),
        .write_PWM_en_AXI(write_PWM_en_AXI));
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
