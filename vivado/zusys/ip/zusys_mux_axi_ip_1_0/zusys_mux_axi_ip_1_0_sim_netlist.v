// Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// --------------------------------------------------------------------------------
// Tool Version: Vivado v.2020.1.1 (win64) Build 2960000 Wed Aug  5 22:57:20 MDT 2020
// Date        : Fri Jan 28 14:45:37 2022
// Host        : enc177112 running 64-bit major release  (build 9200)
// Command     : write_verilog -force -mode funcsim
//               c:/GIT/UltraZohm/software/ultrazohm_sw_develop/vivado/zusys/ip/zusys_mux_axi_ip_1_0/zusys_mux_axi_ip_1_0_sim_netlist.v
// Design      : zusys_mux_axi_ip_1_0
// Purpose     : This verilog netlist is a functional simulation representation of the design and should not be modified
//               or synthesized. This netlist cannot be used for SDF annotated simulation.
// Device      : xczu9eg-ffvc900-1-e
// --------------------------------------------------------------------------------
`timescale 1 ps / 1 ps

(* CHECK_LICENSE_TYPE = "zusys_mux_axi_ip_1_0,mux_axi_ip,{}" *) (* downgradeipidentifiedwarnings = "yes" *) (* ip_definition_source = "package_project" *) 
(* x_core_info = "mux_axi_ip,Vivado 2020.1.1" *) 
(* NotValidForBitStream *)
module zusys_mux_axi_ip_1_0
   (IPCORE_CLK,
    IPCORE_RESETN,
    interrupts_in,
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
    interrupt_out_adc,
    interrupt_out_isr,
    select_out,
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
  input [7:0]interrupts_in;
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
  output interrupt_out_adc;
  output [7:0]interrupt_out_isr;
  output [3:0]select_out;
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
  wire [31:0]AXI4_Lite_RDATA;
  wire AXI4_Lite_RREADY;
  wire AXI4_Lite_RVALID;
  wire [31:0]AXI4_Lite_WDATA;
  wire AXI4_Lite_WREADY;
  wire [3:0]AXI4_Lite_WSTRB;
  wire AXI4_Lite_WVALID;
  wire IPCORE_CLK;
  wire IPCORE_RESETN;
  wire interrupt_out_adc;
  wire [7:0]interrupt_out_isr;
  wire [7:0]interrupts_in;
  wire [3:0]select_out;

  assign AXI4_Lite_BRESP[1] = \<const0> ;
  assign AXI4_Lite_BRESP[0] = \<const0> ;
  assign AXI4_Lite_RRESP[1] = \<const0> ;
  assign AXI4_Lite_RRESP[0] = \<const0> ;
  GND GND
       (.G(\<const0> ));
  zusys_mux_axi_ip_1_0_mux_axi_ip U0
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
        .AXI4_Lite_RDATA(AXI4_Lite_RDATA),
        .AXI4_Lite_RREADY(AXI4_Lite_RREADY),
        .AXI4_Lite_RVALID(AXI4_Lite_RVALID),
        .AXI4_Lite_WDATA(AXI4_Lite_WDATA),
        .AXI4_Lite_WREADY(AXI4_Lite_WREADY),
        .AXI4_Lite_WSTRB(AXI4_Lite_WSTRB),
        .AXI4_Lite_WVALID(AXI4_Lite_WVALID),
        .IPCORE_CLK(IPCORE_CLK),
        .IPCORE_RESETN(IPCORE_RESETN),
        .interrupt_out_adc(interrupt_out_adc),
        .interrupt_out_isr(interrupt_out_isr),
        .interrupts_in(interrupts_in),
        .select_out(select_out));
endmodule

(* ORIG_REF_NAME = "mux_axi_ip" *) 
module zusys_mux_axi_ip_1_0_mux_axi_ip
   (AXI4_Lite_RVALID,
    AXI4_Lite_BVALID,
    AXI4_Lite_WREADY,
    select_out,
    AXI4_Lite_RDATA,
    interrupt_out_adc,
    AXI4_Lite_ARREADY,
    AXI4_Lite_AWREADY,
    interrupt_out_isr,
    AXI4_Lite_ACLK,
    AXI4_Lite_AWADDR,
    IPCORE_CLK,
    AXI4_Lite_WDATA,
    AXI4_Lite_ARADDR,
    AXI4_Lite_ARVALID,
    AXI4_Lite_RREADY,
    AXI4_Lite_AWVALID,
    AXI4_Lite_WVALID,
    AXI4_Lite_ARESETN,
    interrupts_in,
    IPCORE_RESETN,
    AXI4_Lite_BREADY,
    AXI4_Lite_WSTRB);
  output AXI4_Lite_RVALID;
  output AXI4_Lite_BVALID;
  output AXI4_Lite_WREADY;
  output [3:0]select_out;
  output [31:0]AXI4_Lite_RDATA;
  output interrupt_out_adc;
  output AXI4_Lite_ARREADY;
  output AXI4_Lite_AWREADY;
  output [7:0]interrupt_out_isr;
  input AXI4_Lite_ACLK;
  input [13:0]AXI4_Lite_AWADDR;
  input IPCORE_CLK;
  input [31:0]AXI4_Lite_WDATA;
  input [13:0]AXI4_Lite_ARADDR;
  input AXI4_Lite_ARVALID;
  input AXI4_Lite_RREADY;
  input AXI4_Lite_AWVALID;
  input AXI4_Lite_WVALID;
  input AXI4_Lite_ARESETN;
  input [7:0]interrupts_in;
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
  wire [31:0]AXI4_Lite_RDATA;
  wire AXI4_Lite_RREADY;
  wire AXI4_Lite_RVALID;
  wire [31:0]AXI4_Lite_WDATA;
  wire AXI4_Lite_WREADY;
  wire [3:0]AXI4_Lite_WSTRB;
  wire AXI4_Lite_WVALID;
  wire [7:0]Delay_out1;
  wire IPCORE_CLK;
  wire IPCORE_RESETN;
  wire interrupt_out_adc;
  wire [7:0]interrupt_out_isr;
  wire [7:0]interrupts_in;
  wire [7:0]n_th_adc_interrupt;
  wire reset;
  wire reset_in;
  wire [3:0]select_out;
  wire u_mux_axi_ip_axi_lite_inst_n_10;
  wire u_mux_axi_ip_axi_lite_inst_n_19;
  wire u_mux_axi_ip_axi_lite_inst_n_20;
  wire u_mux_axi_ip_axi_lite_inst_n_21;
  wire u_mux_axi_ip_axi_lite_inst_n_22;
  wire u_mux_axi_ip_axi_lite_inst_n_23;
  wire u_mux_axi_ip_axi_lite_inst_n_24;
  wire u_mux_axi_ip_axi_lite_inst_n_25;
  wire u_mux_axi_ip_axi_lite_inst_n_26;
  wire u_mux_axi_ip_axi_lite_inst_n_3;
  wire u_mux_axi_ip_axi_lite_inst_n_4;
  wire u_mux_axi_ip_axi_lite_inst_n_46;
  wire u_mux_axi_ip_axi_lite_inst_n_5;
  wire u_mux_axi_ip_axi_lite_inst_n_6;
  wire u_mux_axi_ip_axi_lite_inst_n_7;
  wire u_mux_axi_ip_axi_lite_inst_n_8;
  wire u_mux_axi_ip_axi_lite_inst_n_9;
  wire \u_mux_axi_ip_axi_lite_module_inst/soft_reset ;
  wire \u_mux_axi_ip_src_mux_axi/u_Subsystem1/Detect_Rise_Positive_out1 ;
  wire \u_mux_axi_ip_src_mux_axi/u_Subsystem1/HDL_Counter_out1 ;
  wire \u_mux_axi_ip_src_mux_axi/u_Subsystem1/PipelineDelay_out1 ;
  wire \u_mux_axi_ip_src_mux_axi/u_Subsystem1/Relational_Operator_relop1 ;
  wire \u_mux_axi_ip_src_mux_axi/u_Subsystem1/u_Detect_Fall_Nonpositive2/U_k ;
  wire \u_mux_axi_ip_src_mux_axi/u_Subsystem1/u_Detect_Fall_Nonpositive2/U_k_1 ;
  wire \u_mux_axi_ip_src_mux_axi/u_Subsystem1/u_Detect_Rise_Positive/U_k_1 ;
  wire write_axi_enable;

  zusys_mux_axi_ip_1_0_mux_axi_ip_axi_lite u_mux_axi_ip_axi_lite_inst
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
        .CO(\u_mux_axi_ip_src_mux_axi/u_Subsystem1/Relational_Operator_relop1 ),
        .Detect_Rise_Positive_out1(\u_mux_axi_ip_src_mux_axi/u_Subsystem1/Detect_Rise_Positive_out1 ),
        .E(\u_mux_axi_ip_src_mux_axi/u_Subsystem1/HDL_Counter_out1 ),
        .\FSM_onehot_axi_lite_wstate_reg[2] ({AXI4_Lite_BVALID,AXI4_Lite_WREADY}),
        .FSM_sequential_axi_lite_rstate_reg(AXI4_Lite_RVALID),
        .\HDL_Counter_out10_inferred__0/i__carry (Delay_out1),
        .IPCORE_RESETN(IPCORE_RESETN),
        .PipelineDelay_out1(\u_mux_axi_ip_src_mux_axi/u_Subsystem1/PipelineDelay_out1 ),
        .Q(n_th_adc_interrupt),
        .S({u_mux_axi_ip_axi_lite_inst_n_3,u_mux_axi_ip_axi_lite_inst_n_4,u_mux_axi_ip_axi_lite_inst_n_5,u_mux_axi_ip_axi_lite_inst_n_6,u_mux_axi_ip_axi_lite_inst_n_7,u_mux_axi_ip_axi_lite_inst_n_8,u_mux_axi_ip_axi_lite_inst_n_9,u_mux_axi_ip_axi_lite_inst_n_10}),
        .SR(reset),
        .U_k(\u_mux_axi_ip_src_mux_axi/u_Subsystem1/u_Detect_Fall_Nonpositive2/U_k ),
        .U_k_1(\u_mux_axi_ip_src_mux_axi/u_Subsystem1/u_Detect_Fall_Nonpositive2/U_k_1 ),
        .U_k_1_0(\u_mux_axi_ip_src_mux_axi/u_Subsystem1/u_Detect_Rise_Positive/U_k_1 ),
        .data_reg_axi_enable_1_1_reg(u_mux_axi_ip_axi_lite_inst_n_46),
        .\data_reg_select_AXI_1_1_reg[3] (select_out),
        .\data_reg_select_n_th_adc_interrupt_1_1_reg[30] ({u_mux_axi_ip_axi_lite_inst_n_19,u_mux_axi_ip_axi_lite_inst_n_20,u_mux_axi_ip_axi_lite_inst_n_21,u_mux_axi_ip_axi_lite_inst_n_22,u_mux_axi_ip_axi_lite_inst_n_23,u_mux_axi_ip_axi_lite_inst_n_24,u_mux_axi_ip_axi_lite_inst_n_25,u_mux_axi_ip_axi_lite_inst_n_26}),
        .interrupt_out_adc(interrupt_out_adc),
        .interrupt_out_isr(interrupt_out_isr),
        .interrupts_in(interrupts_in),
        .reset_in(reset_in),
        .soft_reset(\u_mux_axi_ip_axi_lite_module_inst/soft_reset ),
        .write_axi_enable(write_axi_enable));
  zusys_mux_axi_ip_1_0_mux_axi_ip_dut u_mux_axi_ip_dut_inst
       (.CO(\u_mux_axi_ip_src_mux_axi/u_Subsystem1/Relational_Operator_relop1 ),
        .Detect_Rise_Positive_out1(\u_mux_axi_ip_src_mux_axi/u_Subsystem1/Detect_Rise_Positive_out1 ),
        .E(write_axi_enable),
        .\HDL_Counter_out10_inferred__0/i__carry (n_th_adc_interrupt),
        .\HDL_Counter_out1_reg[7] ({u_mux_axi_ip_axi_lite_inst_n_19,u_mux_axi_ip_axi_lite_inst_n_20,u_mux_axi_ip_axi_lite_inst_n_21,u_mux_axi_ip_axi_lite_inst_n_22,u_mux_axi_ip_axi_lite_inst_n_23,u_mux_axi_ip_axi_lite_inst_n_24,u_mux_axi_ip_axi_lite_inst_n_25,u_mux_axi_ip_axi_lite_inst_n_26}),
        .\HDL_Counter_out1_reg[7]_0 (u_mux_axi_ip_axi_lite_inst_n_46),
        .\HDL_Counter_out1_reg[7]_1 (\u_mux_axi_ip_src_mux_axi/u_Subsystem1/HDL_Counter_out1 ),
        .IPCORE_CLK(IPCORE_CLK),
        .PipelineDelay_out1(\u_mux_axi_ip_src_mux_axi/u_Subsystem1/PipelineDelay_out1 ),
        .Q(Delay_out1),
        .S({u_mux_axi_ip_axi_lite_inst_n_3,u_mux_axi_ip_axi_lite_inst_n_4,u_mux_axi_ip_axi_lite_inst_n_5,u_mux_axi_ip_axi_lite_inst_n_6,u_mux_axi_ip_axi_lite_inst_n_7,u_mux_axi_ip_axi_lite_inst_n_8,u_mux_axi_ip_axi_lite_inst_n_9,u_mux_axi_ip_axi_lite_inst_n_10}),
        .SR(reset),
        .U_k(\u_mux_axi_ip_src_mux_axi/u_Subsystem1/u_Detect_Fall_Nonpositive2/U_k ),
        .U_k_1(\u_mux_axi_ip_src_mux_axi/u_Subsystem1/u_Detect_Rise_Positive/U_k_1 ),
        .U_k_1_0(\u_mux_axi_ip_src_mux_axi/u_Subsystem1/u_Detect_Fall_Nonpositive2/U_k_1 ),
        .interrupt_out_adc(interrupt_out_adc));
  zusys_mux_axi_ip_1_0_mux_axi_ip_reset_sync u_mux_axi_ip_reset_sync_inst
       (.AXI4_Lite_ARESETN(AXI4_Lite_ARESETN),
        .IPCORE_CLK(IPCORE_CLK),
        .IPCORE_RESETN(IPCORE_RESETN),
        .SR(reset),
        .reset_in(reset_in),
        .soft_reset(\u_mux_axi_ip_axi_lite_module_inst/soft_reset ));
endmodule

(* ORIG_REF_NAME = "mux_axi_ip_addr_decoder" *) 
module zusys_mux_axi_ip_1_0_mux_axi_ip_addr_decoder
   (read_reg_ip_timestamp,
    data_reg_axi_enable_1_1_reg_0,
    S,
    Q,
    \data_reg_select_n_th_adc_interrupt_1_1_reg[30]_0 ,
    D,
    \data_reg_select_AXI_1_1_reg[30]_0 ,
    interrupt_out_isr,
    interrupt_out_adc,
    Detect_Rise_Positive_out1,
    E,
    data_reg_axi_enable_1_1_reg_1,
    SR,
    AXI4_Lite_ACLK,
    data_reg_axi_enable_1_1_reg_2,
    \AXI4_Lite_RDATA_tmp_reg[1] ,
    \AXI4_Lite_RDATA_tmp_reg[1]_0 ,
    U_k_1,
    U_k,
    U_k_1_0,
    interrupts_in,
    PipelineDelay_out1,
    CO,
    \HDL_Counter_out10_inferred__0/i__carry ,
    \data_reg_select_AXI_1_1_reg[31]_0 ,
    \data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0 ,
    \data_reg_select_n_th_adc_interrupt_1_1_reg[31]_1 );
  output [0:0]read_reg_ip_timestamp;
  output data_reg_axi_enable_1_1_reg_0;
  output [7:0]S;
  output [20:0]Q;
  output [7:0]\data_reg_select_n_th_adc_interrupt_1_1_reg[30]_0 ;
  output [16:0]D;
  output [17:0]\data_reg_select_AXI_1_1_reg[30]_0 ;
  output [7:0]interrupt_out_isr;
  output interrupt_out_adc;
  output Detect_Rise_Positive_out1;
  output [0:0]E;
  output [0:0]data_reg_axi_enable_1_1_reg_1;
  input [0:0]SR;
  input AXI4_Lite_ACLK;
  input data_reg_axi_enable_1_1_reg_2;
  input \AXI4_Lite_RDATA_tmp_reg[1] ;
  input \AXI4_Lite_RDATA_tmp_reg[1]_0 ;
  input U_k_1;
  input U_k;
  input U_k_1_0;
  input [7:0]interrupts_in;
  input PipelineDelay_out1;
  input [0:0]CO;
  input [7:0]\HDL_Counter_out10_inferred__0/i__carry ;
  input [0:0]\data_reg_select_AXI_1_1_reg[31]_0 ;
  input [31:0]\data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0 ;
  input [0:0]\data_reg_select_n_th_adc_interrupt_1_1_reg[31]_1 ;

  wire AXI4_Lite_ACLK;
  wire \AXI4_Lite_RDATA_tmp_reg[1] ;
  wire \AXI4_Lite_RDATA_tmp_reg[1]_0 ;
  wire [0:0]CO;
  wire [16:0]D;
  wire Detect_Rise_Positive_out1;
  wire [0:0]E;
  wire [7:0]\HDL_Counter_out10_inferred__0/i__carry ;
  wire PipelineDelay_out1;
  wire [20:0]Q;
  wire [7:0]S;
  wire [0:0]SR;
  wire U_k;
  wire U_k_1;
  wire U_k_1_0;
  wire data_reg_axi_enable_1_1_reg_0;
  wire [0:0]data_reg_axi_enable_1_1_reg_1;
  wire data_reg_axi_enable_1_1_reg_2;
  wire [17:0]\data_reg_select_AXI_1_1_reg[30]_0 ;
  wire [0:0]\data_reg_select_AXI_1_1_reg[31]_0 ;
  wire [7:0]\data_reg_select_n_th_adc_interrupt_1_1_reg[30]_0 ;
  wire [31:0]\data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0 ;
  wire [0:0]\data_reg_select_n_th_adc_interrupt_1_1_reg[31]_1 ;
  wire interrupt_out_adc;
  wire interrupt_out_adc_INST_0_i_10_n_0;
  wire interrupt_out_adc_INST_0_i_11_n_0;
  wire interrupt_out_adc_INST_0_i_1_n_0;
  wire interrupt_out_adc_INST_0_i_2_n_0;
  wire interrupt_out_adc_INST_0_i_3_n_0;
  wire interrupt_out_adc_INST_0_i_4_n_0;
  wire interrupt_out_adc_INST_0_i_5_n_0;
  wire interrupt_out_adc_INST_0_i_6_n_0;
  wire interrupt_out_adc_INST_0_i_7_n_0;
  wire interrupt_out_adc_INST_0_i_8_n_0;
  wire interrupt_out_adc_INST_0_i_9_n_0;
  wire [7:0]interrupt_out_isr;
  wire [7:0]interrupts_in;
  wire [31:8]n_th_adc_interrupt;
  wire [27:0]p_0_in;
  wire [0:0]read_reg_ip_timestamp;

  LUT4 #(
    .INIT(16'hF888)) 
    \AXI4_Lite_RDATA_tmp[11]_i_1 
       (.I0(p_0_in[20]),
        .I1(\AXI4_Lite_RDATA_tmp_reg[1] ),
        .I2(n_th_adc_interrupt[11]),
        .I3(\AXI4_Lite_RDATA_tmp_reg[1]_0 ),
        .O(D[8]));
  LUT4 #(
    .INIT(16'hF888)) 
    \AXI4_Lite_RDATA_tmp[12]_i_1 
       (.I0(p_0_in[19]),
        .I1(\AXI4_Lite_RDATA_tmp_reg[1] ),
        .I2(n_th_adc_interrupt[12]),
        .I3(\AXI4_Lite_RDATA_tmp_reg[1]_0 ),
        .O(D[9]));
  LUT4 #(
    .INIT(16'hF888)) 
    \AXI4_Lite_RDATA_tmp[13]_i_1 
       (.I0(p_0_in[18]),
        .I1(\AXI4_Lite_RDATA_tmp_reg[1] ),
        .I2(n_th_adc_interrupt[13]),
        .I3(\AXI4_Lite_RDATA_tmp_reg[1]_0 ),
        .O(D[10]));
  LUT4 #(
    .INIT(16'hF888)) 
    \AXI4_Lite_RDATA_tmp[15]_i_1 
       (.I0(p_0_in[16]),
        .I1(\AXI4_Lite_RDATA_tmp_reg[1] ),
        .I2(n_th_adc_interrupt[15]),
        .I3(\AXI4_Lite_RDATA_tmp_reg[1]_0 ),
        .O(D[11]));
  LUT4 #(
    .INIT(16'hF888)) 
    \AXI4_Lite_RDATA_tmp[19]_i_1 
       (.I0(p_0_in[12]),
        .I1(\AXI4_Lite_RDATA_tmp_reg[1] ),
        .I2(n_th_adc_interrupt[19]),
        .I3(\AXI4_Lite_RDATA_tmp_reg[1]_0 ),
        .O(D[12]));
  LUT4 #(
    .INIT(16'hF888)) 
    \AXI4_Lite_RDATA_tmp[1]_i_1 
       (.I0(\data_reg_select_AXI_1_1_reg[30]_0 [1]),
        .I1(\AXI4_Lite_RDATA_tmp_reg[1] ),
        .I2(Q[1]),
        .I3(\AXI4_Lite_RDATA_tmp_reg[1]_0 ),
        .O(D[0]));
  LUT4 #(
    .INIT(16'hF888)) 
    \AXI4_Lite_RDATA_tmp[20]_i_1 
       (.I0(p_0_in[11]),
        .I1(\AXI4_Lite_RDATA_tmp_reg[1] ),
        .I2(n_th_adc_interrupt[20]),
        .I3(\AXI4_Lite_RDATA_tmp_reg[1]_0 ),
        .O(D[13]));
  LUT4 #(
    .INIT(16'hF888)) 
    \AXI4_Lite_RDATA_tmp[21]_i_1 
       (.I0(p_0_in[10]),
        .I1(\AXI4_Lite_RDATA_tmp_reg[1] ),
        .I2(n_th_adc_interrupt[21]),
        .I3(\AXI4_Lite_RDATA_tmp_reg[1]_0 ),
        .O(D[14]));
  LUT4 #(
    .INIT(16'hF888)) 
    \AXI4_Lite_RDATA_tmp[25]_i_1 
       (.I0(p_0_in[6]),
        .I1(\AXI4_Lite_RDATA_tmp_reg[1] ),
        .I2(n_th_adc_interrupt[25]),
        .I3(\AXI4_Lite_RDATA_tmp_reg[1]_0 ),
        .O(D[15]));
  LUT4 #(
    .INIT(16'hF888)) 
    \AXI4_Lite_RDATA_tmp[2]_i_1 
       (.I0(\data_reg_select_AXI_1_1_reg[30]_0 [2]),
        .I1(\AXI4_Lite_RDATA_tmp_reg[1] ),
        .I2(Q[2]),
        .I3(\AXI4_Lite_RDATA_tmp_reg[1]_0 ),
        .O(D[1]));
  LUT4 #(
    .INIT(16'hF888)) 
    \AXI4_Lite_RDATA_tmp[31]_i_2 
       (.I0(p_0_in[0]),
        .I1(\AXI4_Lite_RDATA_tmp_reg[1] ),
        .I2(n_th_adc_interrupt[31]),
        .I3(\AXI4_Lite_RDATA_tmp_reg[1]_0 ),
        .O(D[16]));
  LUT4 #(
    .INIT(16'hF888)) 
    \AXI4_Lite_RDATA_tmp[3]_i_1 
       (.I0(\data_reg_select_AXI_1_1_reg[30]_0 [3]),
        .I1(\AXI4_Lite_RDATA_tmp_reg[1] ),
        .I2(Q[3]),
        .I3(\AXI4_Lite_RDATA_tmp_reg[1]_0 ),
        .O(D[2]));
  LUT4 #(
    .INIT(16'hF888)) 
    \AXI4_Lite_RDATA_tmp[4]_i_1 
       (.I0(p_0_in[27]),
        .I1(\AXI4_Lite_RDATA_tmp_reg[1] ),
        .I2(Q[4]),
        .I3(\AXI4_Lite_RDATA_tmp_reg[1]_0 ),
        .O(D[3]));
  LUT4 #(
    .INIT(16'hF888)) 
    \AXI4_Lite_RDATA_tmp[6]_i_1 
       (.I0(p_0_in[25]),
        .I1(\AXI4_Lite_RDATA_tmp_reg[1] ),
        .I2(Q[6]),
        .I3(\AXI4_Lite_RDATA_tmp_reg[1]_0 ),
        .O(D[4]));
  LUT4 #(
    .INIT(16'hF888)) 
    \AXI4_Lite_RDATA_tmp[7]_i_1 
       (.I0(p_0_in[24]),
        .I1(\AXI4_Lite_RDATA_tmp_reg[1] ),
        .I2(Q[7]),
        .I3(\AXI4_Lite_RDATA_tmp_reg[1]_0 ),
        .O(D[5]));
  LUT4 #(
    .INIT(16'hF888)) 
    \AXI4_Lite_RDATA_tmp[8]_i_1 
       (.I0(p_0_in[23]),
        .I1(\AXI4_Lite_RDATA_tmp_reg[1] ),
        .I2(n_th_adc_interrupt[8]),
        .I3(\AXI4_Lite_RDATA_tmp_reg[1]_0 ),
        .O(D[6]));
  LUT4 #(
    .INIT(16'hF888)) 
    \AXI4_Lite_RDATA_tmp[9]_i_1 
       (.I0(p_0_in[22]),
        .I1(\AXI4_Lite_RDATA_tmp_reg[1] ),
        .I2(n_th_adc_interrupt[9]),
        .I3(\AXI4_Lite_RDATA_tmp_reg[1]_0 ),
        .O(D[7]));
  (* SOFT_HLUTNM = "soft_lutpair1" *) 
  LUT3 #(
    .INIT(8'hF8)) 
    \HDL_Counter_out1[7]_i_1 
       (.I0(data_reg_axi_enable_1_1_reg_0),
        .I1(CO),
        .I2(SR),
        .O(data_reg_axi_enable_1_1_reg_1));
  (* SOFT_HLUTNM = "soft_lutpair1" *) 
  LUT2 #(
    .INIT(4'h8)) 
    \HDL_Counter_out1[7]_i_2 
       (.I0(data_reg_axi_enable_1_1_reg_0),
        .I1(PipelineDelay_out1),
        .O(E));
  (* SOFT_HLUTNM = "soft_lutpair0" *) 
  LUT3 #(
    .INIT(8'h40)) 
    PipelineDelay_out1_i_1
       (.I0(U_k_1_0),
        .I1(interrupt_out_adc_INST_0_i_2_n_0),
        .I2(interrupt_out_adc_INST_0_i_1_n_0),
        .O(Detect_Rise_Positive_out1));
  FDSE data_reg_axi_enable_1_1_reg
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(data_reg_axi_enable_1_1_reg_2),
        .Q(data_reg_axi_enable_1_1_reg_0),
        .S(SR));
  FDRE \data_reg_select_AXI_1_1_reg[0] 
       (.C(AXI4_Lite_ACLK),
        .CE(\data_reg_select_AXI_1_1_reg[31]_0 ),
        .D(\data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0 [0]),
        .Q(\data_reg_select_AXI_1_1_reg[30]_0 [0]),
        .R(SR));
  FDRE \data_reg_select_AXI_1_1_reg[10] 
       (.C(AXI4_Lite_ACLK),
        .CE(\data_reg_select_AXI_1_1_reg[31]_0 ),
        .D(\data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0 [10]),
        .Q(\data_reg_select_AXI_1_1_reg[30]_0 [5]),
        .R(SR));
  FDRE \data_reg_select_AXI_1_1_reg[11] 
       (.C(AXI4_Lite_ACLK),
        .CE(\data_reg_select_AXI_1_1_reg[31]_0 ),
        .D(\data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0 [11]),
        .Q(p_0_in[20]),
        .R(SR));
  FDRE \data_reg_select_AXI_1_1_reg[12] 
       (.C(AXI4_Lite_ACLK),
        .CE(\data_reg_select_AXI_1_1_reg[31]_0 ),
        .D(\data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0 [12]),
        .Q(p_0_in[19]),
        .R(SR));
  FDRE \data_reg_select_AXI_1_1_reg[13] 
       (.C(AXI4_Lite_ACLK),
        .CE(\data_reg_select_AXI_1_1_reg[31]_0 ),
        .D(\data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0 [13]),
        .Q(p_0_in[18]),
        .R(SR));
  FDRE \data_reg_select_AXI_1_1_reg[14] 
       (.C(AXI4_Lite_ACLK),
        .CE(\data_reg_select_AXI_1_1_reg[31]_0 ),
        .D(\data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0 [14]),
        .Q(\data_reg_select_AXI_1_1_reg[30]_0 [6]),
        .R(SR));
  FDRE \data_reg_select_AXI_1_1_reg[15] 
       (.C(AXI4_Lite_ACLK),
        .CE(\data_reg_select_AXI_1_1_reg[31]_0 ),
        .D(\data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0 [15]),
        .Q(p_0_in[16]),
        .R(SR));
  FDRE \data_reg_select_AXI_1_1_reg[16] 
       (.C(AXI4_Lite_ACLK),
        .CE(\data_reg_select_AXI_1_1_reg[31]_0 ),
        .D(\data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0 [16]),
        .Q(\data_reg_select_AXI_1_1_reg[30]_0 [7]),
        .R(SR));
  FDRE \data_reg_select_AXI_1_1_reg[17] 
       (.C(AXI4_Lite_ACLK),
        .CE(\data_reg_select_AXI_1_1_reg[31]_0 ),
        .D(\data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0 [17]),
        .Q(\data_reg_select_AXI_1_1_reg[30]_0 [8]),
        .R(SR));
  FDRE \data_reg_select_AXI_1_1_reg[18] 
       (.C(AXI4_Lite_ACLK),
        .CE(\data_reg_select_AXI_1_1_reg[31]_0 ),
        .D(\data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0 [18]),
        .Q(\data_reg_select_AXI_1_1_reg[30]_0 [9]),
        .R(SR));
  FDRE \data_reg_select_AXI_1_1_reg[19] 
       (.C(AXI4_Lite_ACLK),
        .CE(\data_reg_select_AXI_1_1_reg[31]_0 ),
        .D(\data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0 [19]),
        .Q(p_0_in[12]),
        .R(SR));
  FDRE \data_reg_select_AXI_1_1_reg[1] 
       (.C(AXI4_Lite_ACLK),
        .CE(\data_reg_select_AXI_1_1_reg[31]_0 ),
        .D(\data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0 [1]),
        .Q(\data_reg_select_AXI_1_1_reg[30]_0 [1]),
        .R(SR));
  FDRE \data_reg_select_AXI_1_1_reg[20] 
       (.C(AXI4_Lite_ACLK),
        .CE(\data_reg_select_AXI_1_1_reg[31]_0 ),
        .D(\data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0 [20]),
        .Q(p_0_in[11]),
        .R(SR));
  FDRE \data_reg_select_AXI_1_1_reg[21] 
       (.C(AXI4_Lite_ACLK),
        .CE(\data_reg_select_AXI_1_1_reg[31]_0 ),
        .D(\data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0 [21]),
        .Q(p_0_in[10]),
        .R(SR));
  FDRE \data_reg_select_AXI_1_1_reg[22] 
       (.C(AXI4_Lite_ACLK),
        .CE(\data_reg_select_AXI_1_1_reg[31]_0 ),
        .D(\data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0 [22]),
        .Q(\data_reg_select_AXI_1_1_reg[30]_0 [10]),
        .R(SR));
  FDRE \data_reg_select_AXI_1_1_reg[23] 
       (.C(AXI4_Lite_ACLK),
        .CE(\data_reg_select_AXI_1_1_reg[31]_0 ),
        .D(\data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0 [23]),
        .Q(\data_reg_select_AXI_1_1_reg[30]_0 [11]),
        .R(SR));
  FDRE \data_reg_select_AXI_1_1_reg[24] 
       (.C(AXI4_Lite_ACLK),
        .CE(\data_reg_select_AXI_1_1_reg[31]_0 ),
        .D(\data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0 [24]),
        .Q(\data_reg_select_AXI_1_1_reg[30]_0 [12]),
        .R(SR));
  FDRE \data_reg_select_AXI_1_1_reg[25] 
       (.C(AXI4_Lite_ACLK),
        .CE(\data_reg_select_AXI_1_1_reg[31]_0 ),
        .D(\data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0 [25]),
        .Q(p_0_in[6]),
        .R(SR));
  FDRE \data_reg_select_AXI_1_1_reg[26] 
       (.C(AXI4_Lite_ACLK),
        .CE(\data_reg_select_AXI_1_1_reg[31]_0 ),
        .D(\data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0 [26]),
        .Q(\data_reg_select_AXI_1_1_reg[30]_0 [13]),
        .R(SR));
  FDRE \data_reg_select_AXI_1_1_reg[27] 
       (.C(AXI4_Lite_ACLK),
        .CE(\data_reg_select_AXI_1_1_reg[31]_0 ),
        .D(\data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0 [27]),
        .Q(\data_reg_select_AXI_1_1_reg[30]_0 [14]),
        .R(SR));
  FDRE \data_reg_select_AXI_1_1_reg[28] 
       (.C(AXI4_Lite_ACLK),
        .CE(\data_reg_select_AXI_1_1_reg[31]_0 ),
        .D(\data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0 [28]),
        .Q(\data_reg_select_AXI_1_1_reg[30]_0 [15]),
        .R(SR));
  FDRE \data_reg_select_AXI_1_1_reg[29] 
       (.C(AXI4_Lite_ACLK),
        .CE(\data_reg_select_AXI_1_1_reg[31]_0 ),
        .D(\data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0 [29]),
        .Q(\data_reg_select_AXI_1_1_reg[30]_0 [16]),
        .R(SR));
  FDRE \data_reg_select_AXI_1_1_reg[2] 
       (.C(AXI4_Lite_ACLK),
        .CE(\data_reg_select_AXI_1_1_reg[31]_0 ),
        .D(\data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0 [2]),
        .Q(\data_reg_select_AXI_1_1_reg[30]_0 [2]),
        .R(SR));
  FDRE \data_reg_select_AXI_1_1_reg[30] 
       (.C(AXI4_Lite_ACLK),
        .CE(\data_reg_select_AXI_1_1_reg[31]_0 ),
        .D(\data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0 [30]),
        .Q(\data_reg_select_AXI_1_1_reg[30]_0 [17]),
        .R(SR));
  FDRE \data_reg_select_AXI_1_1_reg[31] 
       (.C(AXI4_Lite_ACLK),
        .CE(\data_reg_select_AXI_1_1_reg[31]_0 ),
        .D(\data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0 [31]),
        .Q(p_0_in[0]),
        .R(SR));
  FDRE \data_reg_select_AXI_1_1_reg[3] 
       (.C(AXI4_Lite_ACLK),
        .CE(\data_reg_select_AXI_1_1_reg[31]_0 ),
        .D(\data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0 [3]),
        .Q(\data_reg_select_AXI_1_1_reg[30]_0 [3]),
        .R(SR));
  FDRE \data_reg_select_AXI_1_1_reg[4] 
       (.C(AXI4_Lite_ACLK),
        .CE(\data_reg_select_AXI_1_1_reg[31]_0 ),
        .D(\data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0 [4]),
        .Q(p_0_in[27]),
        .R(SR));
  FDRE \data_reg_select_AXI_1_1_reg[5] 
       (.C(AXI4_Lite_ACLK),
        .CE(\data_reg_select_AXI_1_1_reg[31]_0 ),
        .D(\data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0 [5]),
        .Q(\data_reg_select_AXI_1_1_reg[30]_0 [4]),
        .R(SR));
  FDRE \data_reg_select_AXI_1_1_reg[6] 
       (.C(AXI4_Lite_ACLK),
        .CE(\data_reg_select_AXI_1_1_reg[31]_0 ),
        .D(\data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0 [6]),
        .Q(p_0_in[25]),
        .R(SR));
  FDRE \data_reg_select_AXI_1_1_reg[7] 
       (.C(AXI4_Lite_ACLK),
        .CE(\data_reg_select_AXI_1_1_reg[31]_0 ),
        .D(\data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0 [7]),
        .Q(p_0_in[24]),
        .R(SR));
  FDRE \data_reg_select_AXI_1_1_reg[8] 
       (.C(AXI4_Lite_ACLK),
        .CE(\data_reg_select_AXI_1_1_reg[31]_0 ),
        .D(\data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0 [8]),
        .Q(p_0_in[23]),
        .R(SR));
  FDRE \data_reg_select_AXI_1_1_reg[9] 
       (.C(AXI4_Lite_ACLK),
        .CE(\data_reg_select_AXI_1_1_reg[31]_0 ),
        .D(\data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0 [9]),
        .Q(p_0_in[22]),
        .R(SR));
  FDRE \data_reg_select_n_th_adc_interrupt_1_1_reg[0] 
       (.C(AXI4_Lite_ACLK),
        .CE(\data_reg_select_n_th_adc_interrupt_1_1_reg[31]_1 ),
        .D(\data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0 [0]),
        .Q(Q[0]),
        .R(SR));
  FDRE \data_reg_select_n_th_adc_interrupt_1_1_reg[10] 
       (.C(AXI4_Lite_ACLK),
        .CE(\data_reg_select_n_th_adc_interrupt_1_1_reg[31]_1 ),
        .D(\data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0 [10]),
        .Q(Q[8]),
        .R(SR));
  FDRE \data_reg_select_n_th_adc_interrupt_1_1_reg[11] 
       (.C(AXI4_Lite_ACLK),
        .CE(\data_reg_select_n_th_adc_interrupt_1_1_reg[31]_1 ),
        .D(\data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0 [11]),
        .Q(n_th_adc_interrupt[11]),
        .R(SR));
  FDRE \data_reg_select_n_th_adc_interrupt_1_1_reg[12] 
       (.C(AXI4_Lite_ACLK),
        .CE(\data_reg_select_n_th_adc_interrupt_1_1_reg[31]_1 ),
        .D(\data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0 [12]),
        .Q(n_th_adc_interrupt[12]),
        .R(SR));
  FDRE \data_reg_select_n_th_adc_interrupt_1_1_reg[13] 
       (.C(AXI4_Lite_ACLK),
        .CE(\data_reg_select_n_th_adc_interrupt_1_1_reg[31]_1 ),
        .D(\data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0 [13]),
        .Q(n_th_adc_interrupt[13]),
        .R(SR));
  FDRE \data_reg_select_n_th_adc_interrupt_1_1_reg[14] 
       (.C(AXI4_Lite_ACLK),
        .CE(\data_reg_select_n_th_adc_interrupt_1_1_reg[31]_1 ),
        .D(\data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0 [14]),
        .Q(Q[9]),
        .R(SR));
  FDRE \data_reg_select_n_th_adc_interrupt_1_1_reg[15] 
       (.C(AXI4_Lite_ACLK),
        .CE(\data_reg_select_n_th_adc_interrupt_1_1_reg[31]_1 ),
        .D(\data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0 [15]),
        .Q(n_th_adc_interrupt[15]),
        .R(SR));
  FDRE \data_reg_select_n_th_adc_interrupt_1_1_reg[16] 
       (.C(AXI4_Lite_ACLK),
        .CE(\data_reg_select_n_th_adc_interrupt_1_1_reg[31]_1 ),
        .D(\data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0 [16]),
        .Q(Q[10]),
        .R(SR));
  FDRE \data_reg_select_n_th_adc_interrupt_1_1_reg[17] 
       (.C(AXI4_Lite_ACLK),
        .CE(\data_reg_select_n_th_adc_interrupt_1_1_reg[31]_1 ),
        .D(\data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0 [17]),
        .Q(Q[11]),
        .R(SR));
  FDRE \data_reg_select_n_th_adc_interrupt_1_1_reg[18] 
       (.C(AXI4_Lite_ACLK),
        .CE(\data_reg_select_n_th_adc_interrupt_1_1_reg[31]_1 ),
        .D(\data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0 [18]),
        .Q(Q[12]),
        .R(SR));
  FDRE \data_reg_select_n_th_adc_interrupt_1_1_reg[19] 
       (.C(AXI4_Lite_ACLK),
        .CE(\data_reg_select_n_th_adc_interrupt_1_1_reg[31]_1 ),
        .D(\data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0 [19]),
        .Q(n_th_adc_interrupt[19]),
        .R(SR));
  FDRE \data_reg_select_n_th_adc_interrupt_1_1_reg[1] 
       (.C(AXI4_Lite_ACLK),
        .CE(\data_reg_select_n_th_adc_interrupt_1_1_reg[31]_1 ),
        .D(\data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0 [1]),
        .Q(Q[1]),
        .R(SR));
  FDRE \data_reg_select_n_th_adc_interrupt_1_1_reg[20] 
       (.C(AXI4_Lite_ACLK),
        .CE(\data_reg_select_n_th_adc_interrupt_1_1_reg[31]_1 ),
        .D(\data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0 [20]),
        .Q(n_th_adc_interrupt[20]),
        .R(SR));
  FDRE \data_reg_select_n_th_adc_interrupt_1_1_reg[21] 
       (.C(AXI4_Lite_ACLK),
        .CE(\data_reg_select_n_th_adc_interrupt_1_1_reg[31]_1 ),
        .D(\data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0 [21]),
        .Q(n_th_adc_interrupt[21]),
        .R(SR));
  FDRE \data_reg_select_n_th_adc_interrupt_1_1_reg[22] 
       (.C(AXI4_Lite_ACLK),
        .CE(\data_reg_select_n_th_adc_interrupt_1_1_reg[31]_1 ),
        .D(\data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0 [22]),
        .Q(Q[13]),
        .R(SR));
  FDRE \data_reg_select_n_th_adc_interrupt_1_1_reg[23] 
       (.C(AXI4_Lite_ACLK),
        .CE(\data_reg_select_n_th_adc_interrupt_1_1_reg[31]_1 ),
        .D(\data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0 [23]),
        .Q(Q[14]),
        .R(SR));
  FDRE \data_reg_select_n_th_adc_interrupt_1_1_reg[24] 
       (.C(AXI4_Lite_ACLK),
        .CE(\data_reg_select_n_th_adc_interrupt_1_1_reg[31]_1 ),
        .D(\data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0 [24]),
        .Q(Q[15]),
        .R(SR));
  FDRE \data_reg_select_n_th_adc_interrupt_1_1_reg[25] 
       (.C(AXI4_Lite_ACLK),
        .CE(\data_reg_select_n_th_adc_interrupt_1_1_reg[31]_1 ),
        .D(\data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0 [25]),
        .Q(n_th_adc_interrupt[25]),
        .R(SR));
  FDRE \data_reg_select_n_th_adc_interrupt_1_1_reg[26] 
       (.C(AXI4_Lite_ACLK),
        .CE(\data_reg_select_n_th_adc_interrupt_1_1_reg[31]_1 ),
        .D(\data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0 [26]),
        .Q(Q[16]),
        .R(SR));
  FDRE \data_reg_select_n_th_adc_interrupt_1_1_reg[27] 
       (.C(AXI4_Lite_ACLK),
        .CE(\data_reg_select_n_th_adc_interrupt_1_1_reg[31]_1 ),
        .D(\data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0 [27]),
        .Q(Q[17]),
        .R(SR));
  FDRE \data_reg_select_n_th_adc_interrupt_1_1_reg[28] 
       (.C(AXI4_Lite_ACLK),
        .CE(\data_reg_select_n_th_adc_interrupt_1_1_reg[31]_1 ),
        .D(\data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0 [28]),
        .Q(Q[18]),
        .R(SR));
  FDRE \data_reg_select_n_th_adc_interrupt_1_1_reg[29] 
       (.C(AXI4_Lite_ACLK),
        .CE(\data_reg_select_n_th_adc_interrupt_1_1_reg[31]_1 ),
        .D(\data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0 [29]),
        .Q(Q[19]),
        .R(SR));
  FDRE \data_reg_select_n_th_adc_interrupt_1_1_reg[2] 
       (.C(AXI4_Lite_ACLK),
        .CE(\data_reg_select_n_th_adc_interrupt_1_1_reg[31]_1 ),
        .D(\data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0 [2]),
        .Q(Q[2]),
        .R(SR));
  FDRE \data_reg_select_n_th_adc_interrupt_1_1_reg[30] 
       (.C(AXI4_Lite_ACLK),
        .CE(\data_reg_select_n_th_adc_interrupt_1_1_reg[31]_1 ),
        .D(\data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0 [30]),
        .Q(Q[20]),
        .R(SR));
  FDRE \data_reg_select_n_th_adc_interrupt_1_1_reg[31] 
       (.C(AXI4_Lite_ACLK),
        .CE(\data_reg_select_n_th_adc_interrupt_1_1_reg[31]_1 ),
        .D(\data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0 [31]),
        .Q(n_th_adc_interrupt[31]),
        .R(SR));
  FDRE \data_reg_select_n_th_adc_interrupt_1_1_reg[3] 
       (.C(AXI4_Lite_ACLK),
        .CE(\data_reg_select_n_th_adc_interrupt_1_1_reg[31]_1 ),
        .D(\data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0 [3]),
        .Q(Q[3]),
        .R(SR));
  FDRE \data_reg_select_n_th_adc_interrupt_1_1_reg[4] 
       (.C(AXI4_Lite_ACLK),
        .CE(\data_reg_select_n_th_adc_interrupt_1_1_reg[31]_1 ),
        .D(\data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0 [4]),
        .Q(Q[4]),
        .R(SR));
  FDRE \data_reg_select_n_th_adc_interrupt_1_1_reg[5] 
       (.C(AXI4_Lite_ACLK),
        .CE(\data_reg_select_n_th_adc_interrupt_1_1_reg[31]_1 ),
        .D(\data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0 [5]),
        .Q(Q[5]),
        .R(SR));
  FDRE \data_reg_select_n_th_adc_interrupt_1_1_reg[6] 
       (.C(AXI4_Lite_ACLK),
        .CE(\data_reg_select_n_th_adc_interrupt_1_1_reg[31]_1 ),
        .D(\data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0 [6]),
        .Q(Q[6]),
        .R(SR));
  FDRE \data_reg_select_n_th_adc_interrupt_1_1_reg[7] 
       (.C(AXI4_Lite_ACLK),
        .CE(\data_reg_select_n_th_adc_interrupt_1_1_reg[31]_1 ),
        .D(\data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0 [7]),
        .Q(Q[7]),
        .R(SR));
  FDRE \data_reg_select_n_th_adc_interrupt_1_1_reg[8] 
       (.C(AXI4_Lite_ACLK),
        .CE(\data_reg_select_n_th_adc_interrupt_1_1_reg[31]_1 ),
        .D(\data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0 [8]),
        .Q(n_th_adc_interrupt[8]),
        .R(SR));
  FDRE \data_reg_select_n_th_adc_interrupt_1_1_reg[9] 
       (.C(AXI4_Lite_ACLK),
        .CE(\data_reg_select_n_th_adc_interrupt_1_1_reg[31]_1 ),
        .D(\data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0 [9]),
        .Q(n_th_adc_interrupt[9]),
        .R(SR));
  LUT2 #(
    .INIT(4'h1)) 
    i__carry__0_i_1
       (.I0(Q[20]),
        .I1(n_th_adc_interrupt[31]),
        .O(\data_reg_select_n_th_adc_interrupt_1_1_reg[30]_0 [7]));
  LUT2 #(
    .INIT(4'h1)) 
    i__carry__0_i_2
       (.I0(Q[18]),
        .I1(Q[19]),
        .O(\data_reg_select_n_th_adc_interrupt_1_1_reg[30]_0 [6]));
  LUT2 #(
    .INIT(4'h1)) 
    i__carry__0_i_3
       (.I0(Q[16]),
        .I1(Q[17]),
        .O(\data_reg_select_n_th_adc_interrupt_1_1_reg[30]_0 [5]));
  LUT2 #(
    .INIT(4'h1)) 
    i__carry__0_i_4
       (.I0(Q[15]),
        .I1(n_th_adc_interrupt[25]),
        .O(\data_reg_select_n_th_adc_interrupt_1_1_reg[30]_0 [4]));
  LUT2 #(
    .INIT(4'h1)) 
    i__carry__0_i_5
       (.I0(Q[13]),
        .I1(Q[14]),
        .O(\data_reg_select_n_th_adc_interrupt_1_1_reg[30]_0 [3]));
  LUT2 #(
    .INIT(4'h1)) 
    i__carry__0_i_6
       (.I0(n_th_adc_interrupt[20]),
        .I1(n_th_adc_interrupt[21]),
        .O(\data_reg_select_n_th_adc_interrupt_1_1_reg[30]_0 [2]));
  LUT2 #(
    .INIT(4'h1)) 
    i__carry__0_i_7
       (.I0(Q[12]),
        .I1(n_th_adc_interrupt[19]),
        .O(\data_reg_select_n_th_adc_interrupt_1_1_reg[30]_0 [1]));
  LUT2 #(
    .INIT(4'h1)) 
    i__carry__0_i_8
       (.I0(Q[10]),
        .I1(Q[11]),
        .O(\data_reg_select_n_th_adc_interrupt_1_1_reg[30]_0 [0]));
  LUT4 #(
    .INIT(16'h9009)) 
    i__carry_i_10
       (.I0(Q[5]),
        .I1(\HDL_Counter_out10_inferred__0/i__carry [5]),
        .I2(Q[4]),
        .I3(\HDL_Counter_out10_inferred__0/i__carry [4]),
        .O(S[2]));
  LUT4 #(
    .INIT(16'h9009)) 
    i__carry_i_11
       (.I0(Q[3]),
        .I1(\HDL_Counter_out10_inferred__0/i__carry [3]),
        .I2(Q[2]),
        .I3(\HDL_Counter_out10_inferred__0/i__carry [2]),
        .O(S[1]));
  LUT4 #(
    .INIT(16'h9009)) 
    i__carry_i_12
       (.I0(Q[1]),
        .I1(\HDL_Counter_out10_inferred__0/i__carry [1]),
        .I2(Q[0]),
        .I3(\HDL_Counter_out10_inferred__0/i__carry [0]),
        .O(S[0]));
  LUT2 #(
    .INIT(4'h1)) 
    i__carry_i_5
       (.I0(Q[9]),
        .I1(n_th_adc_interrupt[15]),
        .O(S[7]));
  LUT2 #(
    .INIT(4'h1)) 
    i__carry_i_6
       (.I0(n_th_adc_interrupt[12]),
        .I1(n_th_adc_interrupt[13]),
        .O(S[6]));
  LUT2 #(
    .INIT(4'h1)) 
    i__carry_i_7
       (.I0(Q[8]),
        .I1(n_th_adc_interrupt[11]),
        .O(S[5]));
  LUT2 #(
    .INIT(4'h1)) 
    i__carry_i_8
       (.I0(n_th_adc_interrupt[8]),
        .I1(n_th_adc_interrupt[9]),
        .O(S[4]));
  LUT4 #(
    .INIT(16'h9009)) 
    i__carry_i_9
       (.I0(Q[7]),
        .I1(\HDL_Counter_out10_inferred__0/i__carry [7]),
        .I2(Q[6]),
        .I3(\HDL_Counter_out10_inferred__0/i__carry [6]),
        .O(S[3]));
  (* SOFT_HLUTNM = "soft_lutpair0" *) 
  LUT2 #(
    .INIT(4'h8)) 
    interrupt_out_adc_INST_0
       (.I0(interrupt_out_adc_INST_0_i_1_n_0),
        .I1(interrupt_out_adc_INST_0_i_2_n_0),
        .O(interrupt_out_adc));
  LUT3 #(
    .INIT(8'h80)) 
    interrupt_out_adc_INST_0_i_1
       (.I0(interrupt_out_adc_INST_0_i_3_n_0),
        .I1(interrupt_out_adc_INST_0_i_4_n_0),
        .I2(interrupt_out_adc_INST_0_i_5_n_0),
        .O(interrupt_out_adc_INST_0_i_1_n_0));
  LUT5 #(
    .INIT(32'h00000001)) 
    interrupt_out_adc_INST_0_i_10
       (.I0(\data_reg_select_AXI_1_1_reg[30]_0 [14]),
        .I1(\data_reg_select_AXI_1_1_reg[30]_0 [15]),
        .I2(\data_reg_select_AXI_1_1_reg[30]_0 [16]),
        .I3(\data_reg_select_AXI_1_1_reg[30]_0 [17]),
        .I4(p_0_in[0]),
        .O(interrupt_out_adc_INST_0_i_10_n_0));
  LUT4 #(
    .INIT(16'h0001)) 
    interrupt_out_adc_INST_0_i_11
       (.I0(\data_reg_select_AXI_1_1_reg[30]_0 [13]),
        .I1(p_0_in[6]),
        .I2(\data_reg_select_AXI_1_1_reg[30]_0 [12]),
        .I3(\data_reg_select_AXI_1_1_reg[30]_0 [11]),
        .O(interrupt_out_adc_INST_0_i_11_n_0));
  MUXF7 interrupt_out_adc_INST_0_i_2
       (.I0(interrupt_out_adc_INST_0_i_6_n_0),
        .I1(interrupt_out_adc_INST_0_i_7_n_0),
        .O(interrupt_out_adc_INST_0_i_2_n_0),
        .S(\data_reg_select_AXI_1_1_reg[30]_0 [0]));
  LUT5 #(
    .INIT(32'h00010000)) 
    interrupt_out_adc_INST_0_i_3
       (.I0(\data_reg_select_AXI_1_1_reg[30]_0 [3]),
        .I1(p_0_in[27]),
        .I2(\data_reg_select_AXI_1_1_reg[30]_0 [4]),
        .I3(p_0_in[25]),
        .I4(interrupt_out_adc_INST_0_i_8_n_0),
        .O(interrupt_out_adc_INST_0_i_3_n_0));
  LUT5 #(
    .INIT(32'h00010000)) 
    interrupt_out_adc_INST_0_i_4
       (.I0(p_0_in[20]),
        .I1(p_0_in[19]),
        .I2(p_0_in[18]),
        .I3(\data_reg_select_AXI_1_1_reg[30]_0 [6]),
        .I4(interrupt_out_adc_INST_0_i_9_n_0),
        .O(interrupt_out_adc_INST_0_i_4_n_0));
  LUT6 #(
    .INIT(64'h0000000000000008)) 
    interrupt_out_adc_INST_0_i_5
       (.I0(interrupt_out_adc_INST_0_i_10_n_0),
        .I1(interrupt_out_adc_INST_0_i_11_n_0),
        .I2(\data_reg_select_AXI_1_1_reg[30]_0 [10]),
        .I3(p_0_in[10]),
        .I4(p_0_in[11]),
        .I5(p_0_in[12]),
        .O(interrupt_out_adc_INST_0_i_5_n_0));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    interrupt_out_adc_INST_0_i_6
       (.I0(interrupts_in[6]),
        .I1(interrupts_in[2]),
        .I2(\data_reg_select_AXI_1_1_reg[30]_0 [1]),
        .I3(interrupts_in[4]),
        .I4(\data_reg_select_AXI_1_1_reg[30]_0 [2]),
        .I5(interrupts_in[0]),
        .O(interrupt_out_adc_INST_0_i_6_n_0));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    interrupt_out_adc_INST_0_i_7
       (.I0(interrupts_in[7]),
        .I1(interrupts_in[3]),
        .I2(\data_reg_select_AXI_1_1_reg[30]_0 [1]),
        .I3(interrupts_in[5]),
        .I4(\data_reg_select_AXI_1_1_reg[30]_0 [2]),
        .I5(interrupts_in[1]),
        .O(interrupt_out_adc_INST_0_i_7_n_0));
  LUT4 #(
    .INIT(16'h0001)) 
    interrupt_out_adc_INST_0_i_8
       (.I0(\data_reg_select_AXI_1_1_reg[30]_0 [5]),
        .I1(p_0_in[22]),
        .I2(p_0_in[23]),
        .I3(p_0_in[24]),
        .O(interrupt_out_adc_INST_0_i_8_n_0));
  LUT4 #(
    .INIT(16'h0001)) 
    interrupt_out_adc_INST_0_i_9
       (.I0(\data_reg_select_AXI_1_1_reg[30]_0 [9]),
        .I1(\data_reg_select_AXI_1_1_reg[30]_0 [8]),
        .I2(\data_reg_select_AXI_1_1_reg[30]_0 [7]),
        .I3(p_0_in[16]),
        .O(interrupt_out_adc_INST_0_i_9_n_0));
  LUT6 #(
    .INIT(64'h0001000000000000)) 
    \interrupt_out_isr[0]_INST_0 
       (.I0(\data_reg_select_AXI_1_1_reg[30]_0 [2]),
        .I1(\data_reg_select_AXI_1_1_reg[30]_0 [1]),
        .I2(\data_reg_select_AXI_1_1_reg[30]_0 [0]),
        .I3(U_k_1),
        .I4(U_k),
        .I5(interrupt_out_adc_INST_0_i_1_n_0),
        .O(interrupt_out_isr[0]));
  LUT6 #(
    .INIT(64'h0010000000000000)) 
    \interrupt_out_isr[1]_INST_0 
       (.I0(\data_reg_select_AXI_1_1_reg[30]_0 [2]),
        .I1(\data_reg_select_AXI_1_1_reg[30]_0 [1]),
        .I2(\data_reg_select_AXI_1_1_reg[30]_0 [0]),
        .I3(U_k_1),
        .I4(U_k),
        .I5(interrupt_out_adc_INST_0_i_1_n_0),
        .O(interrupt_out_isr[1]));
  LUT6 #(
    .INIT(64'h0004000000000000)) 
    \interrupt_out_isr[2]_INST_0 
       (.I0(\data_reg_select_AXI_1_1_reg[30]_0 [2]),
        .I1(\data_reg_select_AXI_1_1_reg[30]_0 [1]),
        .I2(\data_reg_select_AXI_1_1_reg[30]_0 [0]),
        .I3(U_k_1),
        .I4(U_k),
        .I5(interrupt_out_adc_INST_0_i_1_n_0),
        .O(interrupt_out_isr[2]));
  LUT6 #(
    .INIT(64'h0040000000000000)) 
    \interrupt_out_isr[3]_INST_0 
       (.I0(\data_reg_select_AXI_1_1_reg[30]_0 [2]),
        .I1(\data_reg_select_AXI_1_1_reg[30]_0 [1]),
        .I2(\data_reg_select_AXI_1_1_reg[30]_0 [0]),
        .I3(U_k_1),
        .I4(U_k),
        .I5(interrupt_out_adc_INST_0_i_1_n_0),
        .O(interrupt_out_isr[3]));
  LUT6 #(
    .INIT(64'h0004000000000000)) 
    \interrupt_out_isr[4]_INST_0 
       (.I0(\data_reg_select_AXI_1_1_reg[30]_0 [1]),
        .I1(\data_reg_select_AXI_1_1_reg[30]_0 [2]),
        .I2(\data_reg_select_AXI_1_1_reg[30]_0 [0]),
        .I3(U_k_1),
        .I4(U_k),
        .I5(interrupt_out_adc_INST_0_i_1_n_0),
        .O(interrupt_out_isr[4]));
  LUT6 #(
    .INIT(64'h0040000000000000)) 
    \interrupt_out_isr[5]_INST_0 
       (.I0(\data_reg_select_AXI_1_1_reg[30]_0 [1]),
        .I1(\data_reg_select_AXI_1_1_reg[30]_0 [2]),
        .I2(\data_reg_select_AXI_1_1_reg[30]_0 [0]),
        .I3(U_k_1),
        .I4(U_k),
        .I5(interrupt_out_adc_INST_0_i_1_n_0),
        .O(interrupt_out_isr[5]));
  LUT6 #(
    .INIT(64'h0008000000000000)) 
    \interrupt_out_isr[6]_INST_0 
       (.I0(\data_reg_select_AXI_1_1_reg[30]_0 [2]),
        .I1(\data_reg_select_AXI_1_1_reg[30]_0 [1]),
        .I2(\data_reg_select_AXI_1_1_reg[30]_0 [0]),
        .I3(U_k_1),
        .I4(U_k),
        .I5(interrupt_out_adc_INST_0_i_1_n_0),
        .O(interrupt_out_isr[6]));
  LUT6 #(
    .INIT(64'h0080000000000000)) 
    \interrupt_out_isr[7]_INST_0 
       (.I0(\data_reg_select_AXI_1_1_reg[30]_0 [2]),
        .I1(\data_reg_select_AXI_1_1_reg[30]_0 [1]),
        .I2(\data_reg_select_AXI_1_1_reg[30]_0 [0]),
        .I3(U_k_1),
        .I4(U_k),
        .I5(interrupt_out_adc_INST_0_i_1_n_0),
        .O(interrupt_out_isr[7]));
  FDRE \read_reg_ip_timestamp_reg[30] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(1'b1),
        .Q(read_reg_ip_timestamp),
        .R(SR));
endmodule

(* ORIG_REF_NAME = "mux_axi_ip_axi_lite" *) 
module zusys_mux_axi_ip_1_0_mux_axi_ip_axi_lite
   (FSM_sequential_axi_lite_rstate_reg,
    write_axi_enable,
    soft_reset,
    S,
    Q,
    \data_reg_select_n_th_adc_interrupt_1_1_reg[30] ,
    \data_reg_select_AXI_1_1_reg[3] ,
    AXI4_Lite_ARREADY,
    \FSM_onehot_axi_lite_wstate_reg[2] ,
    AXI4_Lite_AWREADY,
    interrupt_out_isr,
    interrupt_out_adc,
    Detect_Rise_Positive_out1,
    E,
    data_reg_axi_enable_1_1_reg,
    reset_in,
    AXI4_Lite_RDATA,
    AXI4_Lite_ACLK,
    SR,
    AXI4_Lite_ARADDR,
    AXI4_Lite_ARVALID,
    AXI4_Lite_RREADY,
    AXI4_Lite_AWVALID,
    AXI4_Lite_WVALID,
    AXI4_Lite_ARESETN,
    U_k_1,
    U_k,
    U_k_1_0,
    interrupts_in,
    PipelineDelay_out1,
    CO,
    IPCORE_RESETN,
    \HDL_Counter_out10_inferred__0/i__carry ,
    AXI4_Lite_BREADY,
    AXI4_Lite_WSTRB,
    AXI4_Lite_AWADDR,
    AXI4_Lite_WDATA);
  output FSM_sequential_axi_lite_rstate_reg;
  output write_axi_enable;
  output soft_reset;
  output [7:0]S;
  output [7:0]Q;
  output [7:0]\data_reg_select_n_th_adc_interrupt_1_1_reg[30] ;
  output [3:0]\data_reg_select_AXI_1_1_reg[3] ;
  output AXI4_Lite_ARREADY;
  output [1:0]\FSM_onehot_axi_lite_wstate_reg[2] ;
  output AXI4_Lite_AWREADY;
  output [7:0]interrupt_out_isr;
  output interrupt_out_adc;
  output Detect_Rise_Positive_out1;
  output [0:0]E;
  output [0:0]data_reg_axi_enable_1_1_reg;
  output reset_in;
  output [31:0]AXI4_Lite_RDATA;
  input AXI4_Lite_ACLK;
  input [0:0]SR;
  input [13:0]AXI4_Lite_ARADDR;
  input AXI4_Lite_ARVALID;
  input AXI4_Lite_RREADY;
  input AXI4_Lite_AWVALID;
  input AXI4_Lite_WVALID;
  input AXI4_Lite_ARESETN;
  input U_k_1;
  input U_k;
  input U_k_1_0;
  input [7:0]interrupts_in;
  input PipelineDelay_out1;
  input [0:0]CO;
  input IPCORE_RESETN;
  input [7:0]\HDL_Counter_out10_inferred__0/i__carry ;
  input AXI4_Lite_BREADY;
  input [3:0]AXI4_Lite_WSTRB;
  input [13:0]AXI4_Lite_AWADDR;
  input [31:0]AXI4_Lite_WDATA;

  wire AXI4_Lite_ACLK;
  wire [13:0]AXI4_Lite_ARADDR;
  wire AXI4_Lite_ARESETN;
  wire AXI4_Lite_ARREADY;
  wire AXI4_Lite_ARVALID;
  wire [13:0]AXI4_Lite_AWADDR;
  wire AXI4_Lite_AWREADY;
  wire AXI4_Lite_AWVALID;
  wire AXI4_Lite_BREADY;
  wire [31:0]AXI4_Lite_RDATA;
  wire AXI4_Lite_RREADY;
  wire [31:0]AXI4_Lite_WDATA;
  wire [3:0]AXI4_Lite_WSTRB;
  wire AXI4_Lite_WVALID;
  wire [0:0]CO;
  wire Detect_Rise_Positive_out1;
  wire [0:0]E;
  wire [1:0]\FSM_onehot_axi_lite_wstate_reg[2] ;
  wire FSM_sequential_axi_lite_rstate_reg;
  wire [7:0]\HDL_Counter_out10_inferred__0/i__carry ;
  wire IPCORE_RESETN;
  wire PipelineDelay_out1;
  wire [7:0]Q;
  wire [7:0]S;
  wire [0:0]SR;
  wire U_k;
  wire U_k_1;
  wire U_k_1_0;
  wire [31:1]data_read;
  wire [0:0]data_reg_axi_enable_1_1_reg;
  wire [3:0]\data_reg_select_AXI_1_1_reg[3] ;
  wire [7:0]\data_reg_select_n_th_adc_interrupt_1_1_reg[30] ;
  wire interrupt_out_adc;
  wire [7:0]interrupt_out_isr;
  wire [7:0]interrupts_in;
  wire [30:10]n_th_adc_interrupt;
  wire [26:1]p_0_in;
  wire [30:30]read_reg_ip_timestamp;
  wire reg_enb_select_AXI_1_1;
  wire reg_enb_select_n_th_adc_interrupt_1_1;
  wire reset_in;
  wire soft_reset;
  wire u_mux_axi_ip_axi_lite_module_inst_n_11;
  wire u_mux_axi_ip_axi_lite_module_inst_n_12;
  wire u_mux_axi_ip_axi_lite_module_inst_n_13;
  wire u_mux_axi_ip_axi_lite_module_inst_n_14;
  wire u_mux_axi_ip_axi_lite_module_inst_n_15;
  wire u_mux_axi_ip_axi_lite_module_inst_n_16;
  wire u_mux_axi_ip_axi_lite_module_inst_n_17;
  wire u_mux_axi_ip_axi_lite_module_inst_n_18;
  wire u_mux_axi_ip_axi_lite_module_inst_n_19;
  wire u_mux_axi_ip_axi_lite_module_inst_n_2;
  wire u_mux_axi_ip_axi_lite_module_inst_n_20;
  wire u_mux_axi_ip_axi_lite_module_inst_n_21;
  wire u_mux_axi_ip_axi_lite_module_inst_n_22;
  wire u_mux_axi_ip_axi_lite_module_inst_n_23;
  wire u_mux_axi_ip_axi_lite_module_inst_n_24;
  wire u_mux_axi_ip_axi_lite_module_inst_n_25;
  wire u_mux_axi_ip_axi_lite_module_inst_n_26;
  wire u_mux_axi_ip_axi_lite_module_inst_n_27;
  wire u_mux_axi_ip_axi_lite_module_inst_n_28;
  wire u_mux_axi_ip_axi_lite_module_inst_n_29;
  wire u_mux_axi_ip_axi_lite_module_inst_n_3;
  wire u_mux_axi_ip_axi_lite_module_inst_n_30;
  wire u_mux_axi_ip_axi_lite_module_inst_n_31;
  wire u_mux_axi_ip_axi_lite_module_inst_n_32;
  wire u_mux_axi_ip_axi_lite_module_inst_n_33;
  wire u_mux_axi_ip_axi_lite_module_inst_n_34;
  wire u_mux_axi_ip_axi_lite_module_inst_n_35;
  wire u_mux_axi_ip_axi_lite_module_inst_n_36;
  wire u_mux_axi_ip_axi_lite_module_inst_n_37;
  wire u_mux_axi_ip_axi_lite_module_inst_n_38;
  wire u_mux_axi_ip_axi_lite_module_inst_n_39;
  wire u_mux_axi_ip_axi_lite_module_inst_n_40;
  wire u_mux_axi_ip_axi_lite_module_inst_n_41;
  wire u_mux_axi_ip_axi_lite_module_inst_n_42;
  wire u_mux_axi_ip_axi_lite_module_inst_n_43;
  wire write_axi_enable;

  zusys_mux_axi_ip_1_0_mux_axi_ip_addr_decoder u_mux_axi_ip_addr_decoder_inst
       (.AXI4_Lite_ACLK(AXI4_Lite_ACLK),
        .\AXI4_Lite_RDATA_tmp_reg[1] (u_mux_axi_ip_axi_lite_module_inst_n_2),
        .\AXI4_Lite_RDATA_tmp_reg[1]_0 (u_mux_axi_ip_axi_lite_module_inst_n_3),
        .CO(CO),
        .D({data_read[31],data_read[25],data_read[21:19],data_read[15],data_read[13:11],data_read[9:6],data_read[4:1]}),
        .Detect_Rise_Positive_out1(Detect_Rise_Positive_out1),
        .E(E),
        .\HDL_Counter_out10_inferred__0/i__carry (\HDL_Counter_out10_inferred__0/i__carry ),
        .PipelineDelay_out1(PipelineDelay_out1),
        .Q({n_th_adc_interrupt[30:26],n_th_adc_interrupt[24:22],n_th_adc_interrupt[18:16],n_th_adc_interrupt[14],n_th_adc_interrupt[10],Q}),
        .S(S),
        .SR(SR),
        .U_k(U_k),
        .U_k_1(U_k_1),
        .U_k_1_0(U_k_1_0),
        .data_reg_axi_enable_1_1_reg_0(write_axi_enable),
        .data_reg_axi_enable_1_1_reg_1(data_reg_axi_enable_1_1_reg),
        .data_reg_axi_enable_1_1_reg_2(u_mux_axi_ip_axi_lite_module_inst_n_43),
        .\data_reg_select_AXI_1_1_reg[30]_0 ({p_0_in[1],p_0_in[2],p_0_in[3],p_0_in[4],p_0_in[5],p_0_in[7],p_0_in[8],p_0_in[9],p_0_in[13],p_0_in[14],p_0_in[15],p_0_in[17],p_0_in[21],p_0_in[26],\data_reg_select_AXI_1_1_reg[3] }),
        .\data_reg_select_AXI_1_1_reg[31]_0 (reg_enb_select_AXI_1_1),
        .\data_reg_select_n_th_adc_interrupt_1_1_reg[30]_0 (\data_reg_select_n_th_adc_interrupt_1_1_reg[30] ),
        .\data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0 ({u_mux_axi_ip_axi_lite_module_inst_n_11,u_mux_axi_ip_axi_lite_module_inst_n_12,u_mux_axi_ip_axi_lite_module_inst_n_13,u_mux_axi_ip_axi_lite_module_inst_n_14,u_mux_axi_ip_axi_lite_module_inst_n_15,u_mux_axi_ip_axi_lite_module_inst_n_16,u_mux_axi_ip_axi_lite_module_inst_n_17,u_mux_axi_ip_axi_lite_module_inst_n_18,u_mux_axi_ip_axi_lite_module_inst_n_19,u_mux_axi_ip_axi_lite_module_inst_n_20,u_mux_axi_ip_axi_lite_module_inst_n_21,u_mux_axi_ip_axi_lite_module_inst_n_22,u_mux_axi_ip_axi_lite_module_inst_n_23,u_mux_axi_ip_axi_lite_module_inst_n_24,u_mux_axi_ip_axi_lite_module_inst_n_25,u_mux_axi_ip_axi_lite_module_inst_n_26,u_mux_axi_ip_axi_lite_module_inst_n_27,u_mux_axi_ip_axi_lite_module_inst_n_28,u_mux_axi_ip_axi_lite_module_inst_n_29,u_mux_axi_ip_axi_lite_module_inst_n_30,u_mux_axi_ip_axi_lite_module_inst_n_31,u_mux_axi_ip_axi_lite_module_inst_n_32,u_mux_axi_ip_axi_lite_module_inst_n_33,u_mux_axi_ip_axi_lite_module_inst_n_34,u_mux_axi_ip_axi_lite_module_inst_n_35,u_mux_axi_ip_axi_lite_module_inst_n_36,u_mux_axi_ip_axi_lite_module_inst_n_37,u_mux_axi_ip_axi_lite_module_inst_n_38,u_mux_axi_ip_axi_lite_module_inst_n_39,u_mux_axi_ip_axi_lite_module_inst_n_40,u_mux_axi_ip_axi_lite_module_inst_n_41,u_mux_axi_ip_axi_lite_module_inst_n_42}),
        .\data_reg_select_n_th_adc_interrupt_1_1_reg[31]_1 (reg_enb_select_n_th_adc_interrupt_1_1),
        .interrupt_out_adc(interrupt_out_adc),
        .interrupt_out_isr(interrupt_out_isr),
        .interrupts_in(interrupts_in),
        .read_reg_ip_timestamp(read_reg_ip_timestamp));
  zusys_mux_axi_ip_1_0_mux_axi_ip_axi_lite_module u_mux_axi_ip_axi_lite_module_inst
       (.AXI4_Lite_ACLK(AXI4_Lite_ACLK),
        .AXI4_Lite_ARADDR(AXI4_Lite_ARADDR),
        .AXI4_Lite_ARADDR_2_sp_1(u_mux_axi_ip_axi_lite_module_inst_n_3),
        .AXI4_Lite_ARADDR_8_sp_1(u_mux_axi_ip_axi_lite_module_inst_n_2),
        .AXI4_Lite_ARESETN(AXI4_Lite_ARESETN),
        .AXI4_Lite_ARREADY(AXI4_Lite_ARREADY),
        .AXI4_Lite_ARVALID(AXI4_Lite_ARVALID),
        .AXI4_Lite_AWADDR(AXI4_Lite_AWADDR),
        .AXI4_Lite_AWREADY(AXI4_Lite_AWREADY),
        .AXI4_Lite_AWVALID(AXI4_Lite_AWVALID),
        .AXI4_Lite_BREADY(AXI4_Lite_BREADY),
        .AXI4_Lite_RDATA(AXI4_Lite_RDATA),
        .\AXI4_Lite_RDATA_tmp_reg[30]_0 ({p_0_in[1],p_0_in[2],p_0_in[3],p_0_in[4],p_0_in[5],p_0_in[7],p_0_in[8],p_0_in[9],p_0_in[13],p_0_in[14],p_0_in[15],p_0_in[17],p_0_in[21],p_0_in[26],\data_reg_select_AXI_1_1_reg[3] [0]}),
        .AXI4_Lite_RREADY(AXI4_Lite_RREADY),
        .AXI4_Lite_WDATA(AXI4_Lite_WDATA),
        .AXI4_Lite_WSTRB(AXI4_Lite_WSTRB),
        .AXI4_Lite_WVALID(AXI4_Lite_WVALID),
        .D({data_read[31],data_read[25],data_read[21:19],data_read[15],data_read[13:11],data_read[9:6],data_read[4:1]}),
        .\FSM_onehot_axi_lite_wstate_reg[2]_0 (\FSM_onehot_axi_lite_wstate_reg[2] ),
        .FSM_sequential_axi_lite_rstate_reg_0(FSM_sequential_axi_lite_rstate_reg),
        .IPCORE_RESETN(IPCORE_RESETN),
        .Q({n_th_adc_interrupt[30:26],n_th_adc_interrupt[24:22],n_th_adc_interrupt[18:16],n_th_adc_interrupt[14],n_th_adc_interrupt[10],Q[5],Q[0]}),
        .read_reg_ip_timestamp(read_reg_ip_timestamp),
        .reset_in(reset_in),
        .soft_reset(soft_reset),
        .\wdata_reg[0]_0 (u_mux_axi_ip_axi_lite_module_inst_n_43),
        .\wdata_reg[31]_0 ({u_mux_axi_ip_axi_lite_module_inst_n_11,u_mux_axi_ip_axi_lite_module_inst_n_12,u_mux_axi_ip_axi_lite_module_inst_n_13,u_mux_axi_ip_axi_lite_module_inst_n_14,u_mux_axi_ip_axi_lite_module_inst_n_15,u_mux_axi_ip_axi_lite_module_inst_n_16,u_mux_axi_ip_axi_lite_module_inst_n_17,u_mux_axi_ip_axi_lite_module_inst_n_18,u_mux_axi_ip_axi_lite_module_inst_n_19,u_mux_axi_ip_axi_lite_module_inst_n_20,u_mux_axi_ip_axi_lite_module_inst_n_21,u_mux_axi_ip_axi_lite_module_inst_n_22,u_mux_axi_ip_axi_lite_module_inst_n_23,u_mux_axi_ip_axi_lite_module_inst_n_24,u_mux_axi_ip_axi_lite_module_inst_n_25,u_mux_axi_ip_axi_lite_module_inst_n_26,u_mux_axi_ip_axi_lite_module_inst_n_27,u_mux_axi_ip_axi_lite_module_inst_n_28,u_mux_axi_ip_axi_lite_module_inst_n_29,u_mux_axi_ip_axi_lite_module_inst_n_30,u_mux_axi_ip_axi_lite_module_inst_n_31,u_mux_axi_ip_axi_lite_module_inst_n_32,u_mux_axi_ip_axi_lite_module_inst_n_33,u_mux_axi_ip_axi_lite_module_inst_n_34,u_mux_axi_ip_axi_lite_module_inst_n_35,u_mux_axi_ip_axi_lite_module_inst_n_36,u_mux_axi_ip_axi_lite_module_inst_n_37,u_mux_axi_ip_axi_lite_module_inst_n_38,u_mux_axi_ip_axi_lite_module_inst_n_39,u_mux_axi_ip_axi_lite_module_inst_n_40,u_mux_axi_ip_axi_lite_module_inst_n_41,u_mux_axi_ip_axi_lite_module_inst_n_42}),
        .wr_enb_1_reg_0(reg_enb_select_n_th_adc_interrupt_1_1),
        .wr_enb_1_reg_1(reg_enb_select_AXI_1_1),
        .write_axi_enable(write_axi_enable));
endmodule

(* ORIG_REF_NAME = "mux_axi_ip_axi_lite_module" *) 
module zusys_mux_axi_ip_1_0_mux_axi_ip_axi_lite_module
   (FSM_sequential_axi_lite_rstate_reg_0,
    soft_reset,
    AXI4_Lite_ARADDR_8_sp_1,
    AXI4_Lite_ARADDR_2_sp_1,
    wr_enb_1_reg_0,
    wr_enb_1_reg_1,
    AXI4_Lite_ARREADY,
    \FSM_onehot_axi_lite_wstate_reg[2]_0 ,
    AXI4_Lite_AWREADY,
    reset_in,
    \wdata_reg[31]_0 ,
    \wdata_reg[0]_0 ,
    AXI4_Lite_RDATA,
    AXI4_Lite_ACLK,
    D,
    \AXI4_Lite_RDATA_tmp_reg[30]_0 ,
    Q,
    read_reg_ip_timestamp,
    AXI4_Lite_ARADDR,
    write_axi_enable,
    AXI4_Lite_ARVALID,
    AXI4_Lite_RREADY,
    AXI4_Lite_AWVALID,
    AXI4_Lite_WVALID,
    AXI4_Lite_ARESETN,
    IPCORE_RESETN,
    AXI4_Lite_BREADY,
    AXI4_Lite_WSTRB,
    AXI4_Lite_AWADDR,
    AXI4_Lite_WDATA);
  output FSM_sequential_axi_lite_rstate_reg_0;
  output soft_reset;
  output AXI4_Lite_ARADDR_8_sp_1;
  output AXI4_Lite_ARADDR_2_sp_1;
  output [0:0]wr_enb_1_reg_0;
  output [0:0]wr_enb_1_reg_1;
  output AXI4_Lite_ARREADY;
  output [1:0]\FSM_onehot_axi_lite_wstate_reg[2]_0 ;
  output AXI4_Lite_AWREADY;
  output reset_in;
  output [31:0]\wdata_reg[31]_0 ;
  output \wdata_reg[0]_0 ;
  output [31:0]AXI4_Lite_RDATA;
  input AXI4_Lite_ACLK;
  input [16:0]D;
  input [14:0]\AXI4_Lite_RDATA_tmp_reg[30]_0 ;
  input [14:0]Q;
  input [0:0]read_reg_ip_timestamp;
  input [13:0]AXI4_Lite_ARADDR;
  input write_axi_enable;
  input AXI4_Lite_ARVALID;
  input AXI4_Lite_RREADY;
  input AXI4_Lite_AWVALID;
  input AXI4_Lite_WVALID;
  input AXI4_Lite_ARESETN;
  input IPCORE_RESETN;
  input AXI4_Lite_BREADY;
  input [3:0]AXI4_Lite_WSTRB;
  input [13:0]AXI4_Lite_AWADDR;
  input [31:0]AXI4_Lite_WDATA;

  wire AXI4_Lite_ACLK;
  wire [13:0]AXI4_Lite_ARADDR;
  wire AXI4_Lite_ARADDR_2_sn_1;
  wire AXI4_Lite_ARADDR_8_sn_1;
  wire AXI4_Lite_ARESETN;
  wire AXI4_Lite_ARREADY;
  wire AXI4_Lite_ARVALID;
  wire [13:0]AXI4_Lite_AWADDR;
  wire AXI4_Lite_AWREADY;
  wire AXI4_Lite_AWVALID;
  wire AXI4_Lite_BREADY;
  wire [31:0]AXI4_Lite_RDATA;
  wire \AXI4_Lite_RDATA_tmp[0]_i_2_n_0 ;
  wire \AXI4_Lite_RDATA_tmp[0]_i_3_n_0 ;
  wire \AXI4_Lite_RDATA_tmp[30]_i_2_n_0 ;
  wire \AXI4_Lite_RDATA_tmp[30]_i_3_n_0 ;
  wire \AXI4_Lite_RDATA_tmp[30]_i_4_n_0 ;
  wire \AXI4_Lite_RDATA_tmp[30]_i_5_n_0 ;
  wire \AXI4_Lite_RDATA_tmp[30]_i_6_n_0 ;
  wire [14:0]\AXI4_Lite_RDATA_tmp_reg[30]_0 ;
  wire AXI4_Lite_RREADY;
  wire [31:0]AXI4_Lite_WDATA;
  wire [3:0]AXI4_Lite_WSTRB;
  wire AXI4_Lite_WVALID;
  wire [16:0]D;
  wire [1:0]\FSM_onehot_axi_lite_wstate_reg[2]_0 ;
  wire \FSM_onehot_axi_lite_wstate_reg_n_0_[0] ;
  wire FSM_sequential_axi_lite_rstate_reg_0;
  wire IPCORE_RESETN;
  wire [14:0]Q;
  wire aw_transfer;
  wire axi_lite_rstate_next;
  wire [2:0]axi_lite_wstate_next;
  wire [30:0]data_read;
  wire data_reg_axi_enable_1_1_i_2_n_0;
  wire \data_reg_select_AXI_1_1[3]_i_3_n_0 ;
  wire \data_reg_select_AXI_1_1[3]_i_4_n_0 ;
  wire \data_reg_select_AXI_1_1[3]_i_5_n_0 ;
  wire \data_reg_select_AXI_1_1[3]_i_6_n_0 ;
  wire \data_reg_select_AXI_1_1[3]_i_7_n_0 ;
  wire \data_reg_select_AXI_1_1[3]_i_8_n_0 ;
  wire [0:0]read_reg_ip_timestamp;
  wire reset;
  wire reset_in;
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
  wire [0:0]wr_enb_1_reg_0;
  wire [0:0]wr_enb_1_reg_1;
  wire write_axi_enable;

  assign AXI4_Lite_ARADDR_2_sp_1 = AXI4_Lite_ARADDR_2_sn_1;
  assign AXI4_Lite_ARADDR_8_sp_1 = AXI4_Lite_ARADDR_8_sn_1;
  (* SOFT_HLUTNM = "soft_lutpair2" *) 
  LUT3 #(
    .INIT(8'h04)) 
    AXI4_Lite_ARREADY_INST_0
       (.I0(FSM_sequential_axi_lite_rstate_reg_0),
        .I1(\FSM_onehot_axi_lite_wstate_reg_n_0_[0] ),
        .I2(AXI4_Lite_AWVALID),
        .O(AXI4_Lite_ARREADY));
  (* SOFT_HLUTNM = "soft_lutpair3" *) 
  LUT2 #(
    .INIT(4'h2)) 
    AXI4_Lite_AWREADY_INST_0
       (.I0(\FSM_onehot_axi_lite_wstate_reg_n_0_[0] ),
        .I1(FSM_sequential_axi_lite_rstate_reg_0),
        .O(AXI4_Lite_AWREADY));
  LUT6 #(
    .INIT(64'hFFFFFFFFFFFFF888)) 
    \AXI4_Lite_RDATA_tmp[0]_i_1 
       (.I0(AXI4_Lite_ARADDR_8_sn_1),
        .I1(\AXI4_Lite_RDATA_tmp_reg[30]_0 [0]),
        .I2(Q[0]),
        .I3(AXI4_Lite_ARADDR_2_sn_1),
        .I4(\AXI4_Lite_RDATA_tmp[0]_i_2_n_0 ),
        .I5(\AXI4_Lite_RDATA_tmp[30]_i_2_n_0 ),
        .O(data_read[0]));
  LUT6 #(
    .INIT(64'h8F88888800000000)) 
    \AXI4_Lite_RDATA_tmp[0]_i_2 
       (.I0(\AXI4_Lite_RDATA_tmp[0]_i_3_n_0 ),
        .I1(\data_reg_select_AXI_1_1[3]_i_4_n_0 ),
        .I2(AXI4_Lite_ARADDR[6]),
        .I3(AXI4_Lite_ARADDR[0]),
        .I4(\data_reg_select_AXI_1_1[3]_i_3_n_0 ),
        .I5(write_axi_enable),
        .O(\AXI4_Lite_RDATA_tmp[0]_i_2_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair5" *) 
  LUT2 #(
    .INIT(4'h2)) 
    \AXI4_Lite_RDATA_tmp[0]_i_3 
       (.I0(sel0[0]),
        .I1(sel0[6]),
        .O(\AXI4_Lite_RDATA_tmp[0]_i_3_n_0 ));
  LUT5 #(
    .INIT(32'hFFEAEAEA)) 
    \AXI4_Lite_RDATA_tmp[10]_i_1 
       (.I0(\AXI4_Lite_RDATA_tmp[30]_i_2_n_0 ),
        .I1(AXI4_Lite_ARADDR_2_sn_1),
        .I2(Q[2]),
        .I3(\AXI4_Lite_RDATA_tmp_reg[30]_0 [2]),
        .I4(AXI4_Lite_ARADDR_8_sn_1),
        .O(data_read[10]));
  LUT5 #(
    .INIT(32'hFFEAEAEA)) 
    \AXI4_Lite_RDATA_tmp[14]_i_1 
       (.I0(\AXI4_Lite_RDATA_tmp[30]_i_2_n_0 ),
        .I1(AXI4_Lite_ARADDR_2_sn_1),
        .I2(Q[3]),
        .I3(\AXI4_Lite_RDATA_tmp_reg[30]_0 [3]),
        .I4(AXI4_Lite_ARADDR_8_sn_1),
        .O(data_read[14]));
  LUT5 #(
    .INIT(32'hFFEAEAEA)) 
    \AXI4_Lite_RDATA_tmp[16]_i_1 
       (.I0(\AXI4_Lite_RDATA_tmp[30]_i_2_n_0 ),
        .I1(AXI4_Lite_ARADDR_2_sn_1),
        .I2(Q[4]),
        .I3(\AXI4_Lite_RDATA_tmp_reg[30]_0 [4]),
        .I4(AXI4_Lite_ARADDR_8_sn_1),
        .O(data_read[16]));
  LUT5 #(
    .INIT(32'hFFEAEAEA)) 
    \AXI4_Lite_RDATA_tmp[17]_i_1 
       (.I0(\AXI4_Lite_RDATA_tmp[30]_i_2_n_0 ),
        .I1(AXI4_Lite_ARADDR_2_sn_1),
        .I2(Q[5]),
        .I3(\AXI4_Lite_RDATA_tmp_reg[30]_0 [5]),
        .I4(AXI4_Lite_ARADDR_8_sn_1),
        .O(data_read[17]));
  LUT5 #(
    .INIT(32'hFFEAEAEA)) 
    \AXI4_Lite_RDATA_tmp[18]_i_1 
       (.I0(\AXI4_Lite_RDATA_tmp[30]_i_2_n_0 ),
        .I1(AXI4_Lite_ARADDR_2_sn_1),
        .I2(Q[6]),
        .I3(\AXI4_Lite_RDATA_tmp_reg[30]_0 [6]),
        .I4(AXI4_Lite_ARADDR_8_sn_1),
        .O(data_read[18]));
  LUT5 #(
    .INIT(32'hFFEAEAEA)) 
    \AXI4_Lite_RDATA_tmp[22]_i_1 
       (.I0(\AXI4_Lite_RDATA_tmp[30]_i_2_n_0 ),
        .I1(AXI4_Lite_ARADDR_2_sn_1),
        .I2(Q[7]),
        .I3(\AXI4_Lite_RDATA_tmp_reg[30]_0 [7]),
        .I4(AXI4_Lite_ARADDR_8_sn_1),
        .O(data_read[22]));
  LUT5 #(
    .INIT(32'hFFEAEAEA)) 
    \AXI4_Lite_RDATA_tmp[23]_i_1 
       (.I0(\AXI4_Lite_RDATA_tmp[30]_i_2_n_0 ),
        .I1(AXI4_Lite_ARADDR_2_sn_1),
        .I2(Q[8]),
        .I3(\AXI4_Lite_RDATA_tmp_reg[30]_0 [8]),
        .I4(AXI4_Lite_ARADDR_8_sn_1),
        .O(data_read[23]));
  LUT5 #(
    .INIT(32'hFFEAEAEA)) 
    \AXI4_Lite_RDATA_tmp[24]_i_1 
       (.I0(\AXI4_Lite_RDATA_tmp[30]_i_2_n_0 ),
        .I1(AXI4_Lite_ARADDR_2_sn_1),
        .I2(Q[9]),
        .I3(\AXI4_Lite_RDATA_tmp_reg[30]_0 [9]),
        .I4(AXI4_Lite_ARADDR_8_sn_1),
        .O(data_read[24]));
  LUT5 #(
    .INIT(32'hFFEAEAEA)) 
    \AXI4_Lite_RDATA_tmp[26]_i_1 
       (.I0(\AXI4_Lite_RDATA_tmp[30]_i_2_n_0 ),
        .I1(AXI4_Lite_ARADDR_2_sn_1),
        .I2(Q[10]),
        .I3(\AXI4_Lite_RDATA_tmp_reg[30]_0 [10]),
        .I4(AXI4_Lite_ARADDR_8_sn_1),
        .O(data_read[26]));
  LUT5 #(
    .INIT(32'hFFEAEAEA)) 
    \AXI4_Lite_RDATA_tmp[27]_i_1 
       (.I0(\AXI4_Lite_RDATA_tmp[30]_i_2_n_0 ),
        .I1(AXI4_Lite_ARADDR_2_sn_1),
        .I2(Q[11]),
        .I3(\AXI4_Lite_RDATA_tmp_reg[30]_0 [11]),
        .I4(AXI4_Lite_ARADDR_8_sn_1),
        .O(data_read[27]));
  LUT5 #(
    .INIT(32'hFFEAEAEA)) 
    \AXI4_Lite_RDATA_tmp[28]_i_1 
       (.I0(\AXI4_Lite_RDATA_tmp[30]_i_2_n_0 ),
        .I1(AXI4_Lite_ARADDR_2_sn_1),
        .I2(Q[12]),
        .I3(\AXI4_Lite_RDATA_tmp_reg[30]_0 [12]),
        .I4(AXI4_Lite_ARADDR_8_sn_1),
        .O(data_read[28]));
  LUT5 #(
    .INIT(32'hFFEAEAEA)) 
    \AXI4_Lite_RDATA_tmp[29]_i_1 
       (.I0(\AXI4_Lite_RDATA_tmp[30]_i_2_n_0 ),
        .I1(AXI4_Lite_ARADDR_2_sn_1),
        .I2(Q[13]),
        .I3(\AXI4_Lite_RDATA_tmp_reg[30]_0 [13]),
        .I4(AXI4_Lite_ARADDR_8_sn_1),
        .O(data_read[29]));
  LUT5 #(
    .INIT(32'hFFEAEAEA)) 
    \AXI4_Lite_RDATA_tmp[30]_i_1 
       (.I0(\AXI4_Lite_RDATA_tmp[30]_i_2_n_0 ),
        .I1(AXI4_Lite_ARADDR_2_sn_1),
        .I2(Q[14]),
        .I3(\AXI4_Lite_RDATA_tmp_reg[30]_0 [14]),
        .I4(AXI4_Lite_ARADDR_8_sn_1),
        .O(data_read[30]));
  LUT5 #(
    .INIT(32'hF8880000)) 
    \AXI4_Lite_RDATA_tmp[30]_i_2 
       (.I0(\AXI4_Lite_RDATA_tmp[30]_i_3_n_0 ),
        .I1(\AXI4_Lite_RDATA_tmp[30]_i_4_n_0 ),
        .I2(\AXI4_Lite_RDATA_tmp[30]_i_5_n_0 ),
        .I3(\AXI4_Lite_RDATA_tmp[30]_i_6_n_0 ),
        .I4(read_reg_ip_timestamp),
        .O(\AXI4_Lite_RDATA_tmp[30]_i_2_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair5" *) 
  LUT3 #(
    .INIT(8'h04)) 
    \AXI4_Lite_RDATA_tmp[30]_i_3 
       (.I0(sel0[6]),
        .I1(sel0[1]),
        .I2(sel0[0]),
        .O(\AXI4_Lite_RDATA_tmp[30]_i_3_n_0 ));
  LUT6 #(
    .INIT(64'h0000000000020000)) 
    \AXI4_Lite_RDATA_tmp[30]_i_4 
       (.I0(soft_reset_i_3_n_0),
        .I1(sel0[13]),
        .I2(sel0[2]),
        .I3(sel0[3]),
        .I4(soft_reset_i_2_n_0),
        .I5(AXI4_Lite_ARVALID),
        .O(\AXI4_Lite_RDATA_tmp[30]_i_4_n_0 ));
  LUT3 #(
    .INIT(8'h04)) 
    \AXI4_Lite_RDATA_tmp[30]_i_5 
       (.I0(AXI4_Lite_ARADDR[6]),
        .I1(AXI4_Lite_ARADDR[1]),
        .I2(AXI4_Lite_ARADDR[0]),
        .O(\AXI4_Lite_RDATA_tmp[30]_i_5_n_0 ));
  LUT6 #(
    .INIT(64'h0000000200000000)) 
    \AXI4_Lite_RDATA_tmp[30]_i_6 
       (.I0(\data_reg_select_AXI_1_1[3]_i_7_n_0 ),
        .I1(AXI4_Lite_ARADDR[5]),
        .I2(AXI4_Lite_ARADDR[4]),
        .I3(AXI4_Lite_ARADDR[3]),
        .I4(AXI4_Lite_ARADDR[2]),
        .I5(\data_reg_select_AXI_1_1[3]_i_5_n_0 ),
        .O(\AXI4_Lite_RDATA_tmp[30]_i_6_n_0 ));
  LUT4 #(
    .INIT(16'h0400)) 
    \AXI4_Lite_RDATA_tmp[31]_i_1 
       (.I0(AXI4_Lite_AWVALID),
        .I1(AXI4_Lite_ARVALID),
        .I2(FSM_sequential_axi_lite_rstate_reg_0),
        .I3(\FSM_onehot_axi_lite_wstate_reg_n_0_[0] ),
        .O(top_rd_enb));
  LUT6 #(
    .INIT(64'hFF80808080808080)) 
    \AXI4_Lite_RDATA_tmp[31]_i_3 
       (.I0(\data_reg_select_AXI_1_1[3]_i_3_n_0 ),
        .I1(AXI4_Lite_ARADDR[0]),
        .I2(AXI4_Lite_ARADDR[6]),
        .I3(\data_reg_select_AXI_1_1[3]_i_4_n_0 ),
        .I4(sel0[0]),
        .I5(sel0[6]),
        .O(AXI4_Lite_ARADDR_2_sn_1));
  LUT5 #(
    .INIT(32'hFFEAEAEA)) 
    \AXI4_Lite_RDATA_tmp[5]_i_1 
       (.I0(\AXI4_Lite_RDATA_tmp[30]_i_2_n_0 ),
        .I1(AXI4_Lite_ARADDR_2_sn_1),
        .I2(Q[1]),
        .I3(\AXI4_Lite_RDATA_tmp_reg[30]_0 [1]),
        .I4(AXI4_Lite_ARADDR_8_sn_1),
        .O(data_read[5]));
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
        .D(D[8]),
        .Q(AXI4_Lite_RDATA[11]),
        .R(reset));
  FDRE \AXI4_Lite_RDATA_tmp_reg[12] 
       (.C(AXI4_Lite_ACLK),
        .CE(top_rd_enb),
        .D(D[9]),
        .Q(AXI4_Lite_RDATA[12]),
        .R(reset));
  FDRE \AXI4_Lite_RDATA_tmp_reg[13] 
       (.C(AXI4_Lite_ACLK),
        .CE(top_rd_enb),
        .D(D[10]),
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
        .D(D[11]),
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
        .D(D[12]),
        .Q(AXI4_Lite_RDATA[19]),
        .R(reset));
  FDRE \AXI4_Lite_RDATA_tmp_reg[1] 
       (.C(AXI4_Lite_ACLK),
        .CE(top_rd_enb),
        .D(D[0]),
        .Q(AXI4_Lite_RDATA[1]),
        .R(reset));
  FDRE \AXI4_Lite_RDATA_tmp_reg[20] 
       (.C(AXI4_Lite_ACLK),
        .CE(top_rd_enb),
        .D(D[13]),
        .Q(AXI4_Lite_RDATA[20]),
        .R(reset));
  FDRE \AXI4_Lite_RDATA_tmp_reg[21] 
       (.C(AXI4_Lite_ACLK),
        .CE(top_rd_enb),
        .D(D[14]),
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
  FDRE \AXI4_Lite_RDATA_tmp_reg[25] 
       (.C(AXI4_Lite_ACLK),
        .CE(top_rd_enb),
        .D(D[15]),
        .Q(AXI4_Lite_RDATA[25]),
        .R(reset));
  FDRE \AXI4_Lite_RDATA_tmp_reg[26] 
       (.C(AXI4_Lite_ACLK),
        .CE(top_rd_enb),
        .D(data_read[26]),
        .Q(AXI4_Lite_RDATA[26]),
        .R(reset));
  FDRE \AXI4_Lite_RDATA_tmp_reg[27] 
       (.C(AXI4_Lite_ACLK),
        .CE(top_rd_enb),
        .D(data_read[27]),
        .Q(AXI4_Lite_RDATA[27]),
        .R(reset));
  FDRE \AXI4_Lite_RDATA_tmp_reg[28] 
       (.C(AXI4_Lite_ACLK),
        .CE(top_rd_enb),
        .D(data_read[28]),
        .Q(AXI4_Lite_RDATA[28]),
        .R(reset));
  FDRE \AXI4_Lite_RDATA_tmp_reg[29] 
       (.C(AXI4_Lite_ACLK),
        .CE(top_rd_enb),
        .D(data_read[29]),
        .Q(AXI4_Lite_RDATA[29]),
        .R(reset));
  FDRE \AXI4_Lite_RDATA_tmp_reg[2] 
       (.C(AXI4_Lite_ACLK),
        .CE(top_rd_enb),
        .D(D[1]),
        .Q(AXI4_Lite_RDATA[2]),
        .R(reset));
  FDRE \AXI4_Lite_RDATA_tmp_reg[30] 
       (.C(AXI4_Lite_ACLK),
        .CE(top_rd_enb),
        .D(data_read[30]),
        .Q(AXI4_Lite_RDATA[30]),
        .R(reset));
  FDRE \AXI4_Lite_RDATA_tmp_reg[31] 
       (.C(AXI4_Lite_ACLK),
        .CE(top_rd_enb),
        .D(D[16]),
        .Q(AXI4_Lite_RDATA[31]),
        .R(reset));
  FDRE \AXI4_Lite_RDATA_tmp_reg[3] 
       (.C(AXI4_Lite_ACLK),
        .CE(top_rd_enb),
        .D(D[2]),
        .Q(AXI4_Lite_RDATA[3]),
        .R(reset));
  FDRE \AXI4_Lite_RDATA_tmp_reg[4] 
       (.C(AXI4_Lite_ACLK),
        .CE(top_rd_enb),
        .D(D[3]),
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
        .D(D[4]),
        .Q(AXI4_Lite_RDATA[6]),
        .R(reset));
  FDRE \AXI4_Lite_RDATA_tmp_reg[7] 
       (.C(AXI4_Lite_ACLK),
        .CE(top_rd_enb),
        .D(D[5]),
        .Q(AXI4_Lite_RDATA[7]),
        .R(reset));
  FDRE \AXI4_Lite_RDATA_tmp_reg[8] 
       (.C(AXI4_Lite_ACLK),
        .CE(top_rd_enb),
        .D(D[6]),
        .Q(AXI4_Lite_RDATA[8]),
        .R(reset));
  FDRE \AXI4_Lite_RDATA_tmp_reg[9] 
       (.C(AXI4_Lite_ACLK),
        .CE(top_rd_enb),
        .D(D[7]),
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
  (* SOFT_HLUTNM = "soft_lutpair3" *) 
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
  (* SOFT_HLUTNM = "soft_lutpair2" *) 
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
  (* SOFT_HLUTNM = "soft_lutpair4" *) 
  LUT4 #(
    .INIT(16'hBF80)) 
    data_reg_axi_enable_1_1_i_1
       (.I0(\wdata_reg[31]_0 [0]),
        .I1(data_reg_axi_enable_1_1_i_2_n_0),
        .I2(top_wr_enb),
        .I3(write_axi_enable),
        .O(\wdata_reg[0]_0 ));
  LUT6 #(
    .INIT(64'h08080808FF080808)) 
    data_reg_axi_enable_1_1_i_2
       (.I0(\data_reg_select_AXI_1_1[3]_i_3_n_0 ),
        .I1(AXI4_Lite_ARADDR[0]),
        .I2(AXI4_Lite_ARADDR[6]),
        .I3(\data_reg_select_AXI_1_1[3]_i_4_n_0 ),
        .I4(sel0[0]),
        .I5(sel0[6]),
        .O(data_reg_axi_enable_1_1_i_2_n_0));
  LUT2 #(
    .INIT(4'h8)) 
    \data_reg_select_AXI_1_1[3]_i_1 
       (.I0(AXI4_Lite_ARADDR_8_sn_1),
        .I1(top_wr_enb),
        .O(wr_enb_1_reg_1));
  LUT6 #(
    .INIT(64'h08080808FF080808)) 
    \data_reg_select_AXI_1_1[3]_i_2 
       (.I0(\data_reg_select_AXI_1_1[3]_i_3_n_0 ),
        .I1(AXI4_Lite_ARADDR[6]),
        .I2(AXI4_Lite_ARADDR[0]),
        .I3(\data_reg_select_AXI_1_1[3]_i_4_n_0 ),
        .I4(sel0[6]),
        .I5(sel0[0]),
        .O(AXI4_Lite_ARADDR_8_sn_1));
  LUT4 #(
    .INIT(16'h0080)) 
    \data_reg_select_AXI_1_1[3]_i_3 
       (.I0(\data_reg_select_AXI_1_1[3]_i_5_n_0 ),
        .I1(\data_reg_select_AXI_1_1[3]_i_6_n_0 ),
        .I2(\data_reg_select_AXI_1_1[3]_i_7_n_0 ),
        .I3(AXI4_Lite_ARADDR[1]),
        .O(\data_reg_select_AXI_1_1[3]_i_3_n_0 ));
  LUT5 #(
    .INIT(32'h00004000)) 
    \data_reg_select_AXI_1_1[3]_i_4 
       (.I0(AXI4_Lite_ARVALID),
        .I1(soft_reset_i_2_n_0),
        .I2(\data_reg_select_AXI_1_1[3]_i_8_n_0 ),
        .I3(soft_reset_i_3_n_0),
        .I4(sel0[1]),
        .O(\data_reg_select_AXI_1_1[3]_i_4_n_0 ));
  LUT4 #(
    .INIT(16'h0004)) 
    \data_reg_select_AXI_1_1[3]_i_5 
       (.I0(AXI4_Lite_ARADDR[13]),
        .I1(AXI4_Lite_ARVALID),
        .I2(AXI4_Lite_ARADDR[12]),
        .I3(AXI4_Lite_ARADDR[11]),
        .O(\data_reg_select_AXI_1_1[3]_i_5_n_0 ));
  LUT4 #(
    .INIT(16'h0001)) 
    \data_reg_select_AXI_1_1[3]_i_6 
       (.I0(AXI4_Lite_ARADDR[5]),
        .I1(AXI4_Lite_ARADDR[4]),
        .I2(AXI4_Lite_ARADDR[3]),
        .I3(AXI4_Lite_ARADDR[2]),
        .O(\data_reg_select_AXI_1_1[3]_i_6_n_0 ));
  LUT4 #(
    .INIT(16'h0001)) 
    \data_reg_select_AXI_1_1[3]_i_7 
       (.I0(AXI4_Lite_ARADDR[10]),
        .I1(AXI4_Lite_ARADDR[9]),
        .I2(AXI4_Lite_ARADDR[8]),
        .I3(AXI4_Lite_ARADDR[7]),
        .O(\data_reg_select_AXI_1_1[3]_i_7_n_0 ));
  LUT3 #(
    .INIT(8'h01)) 
    \data_reg_select_AXI_1_1[3]_i_8 
       (.I0(sel0[3]),
        .I1(sel0[2]),
        .I2(sel0[13]),
        .O(\data_reg_select_AXI_1_1[3]_i_8_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair4" *) 
  LUT2 #(
    .INIT(4'h8)) 
    \data_reg_select_n_th_adc_interrupt_1_1[31]_i_1 
       (.I0(AXI4_Lite_ARADDR_2_sn_1),
        .I1(top_wr_enb),
        .O(wr_enb_1_reg_0));
  LUT3 #(
    .INIT(8'hDF)) 
    reset_pipe_i_1
       (.I0(IPCORE_RESETN),
        .I1(soft_reset),
        .I2(AXI4_Lite_ARESETN),
        .O(reset_in));
  LUT6 #(
    .INIT(64'h0002000000000000)) 
    soft_reset_i_1
       (.I0(soft_reset_i_2_n_0),
        .I1(sel0[3]),
        .I2(sel0[2]),
        .I3(sel0[13]),
        .I4(soft_reset_i_3_n_0),
        .I5(soft_reset_i_4_n_0),
        .O(soft_reset_i_1_n_0));
  LUT4 #(
    .INIT(16'h0001)) 
    soft_reset_i_2
       (.I0(sel0[8]),
        .I1(sel0[7]),
        .I2(sel0[5]),
        .I3(sel0[4]),
        .O(soft_reset_i_2_n_0));
  LUT4 #(
    .INIT(16'h0001)) 
    soft_reset_i_3
       (.I0(sel0[12]),
        .I1(sel0[11]),
        .I2(sel0[10]),
        .I3(sel0[9]),
        .O(soft_reset_i_3_n_0));
  LUT6 #(
    .INIT(64'h0002000000000000)) 
    soft_reset_i_4
       (.I0(\wdata_reg[31]_0 [0]),
        .I1(sel0[6]),
        .I2(sel0[0]),
        .I3(sel0[1]),
        .I4(top_wr_enb),
        .I5(AXI4_Lite_ARESETN),
        .O(soft_reset_i_4_n_0));
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
endmodule

(* ORIG_REF_NAME = "mux_axi_ip_dut" *) 
module zusys_mux_axi_ip_1_0_mux_axi_ip_dut
   (U_k_1,
    U_k_1_0,
    U_k,
    PipelineDelay_out1,
    CO,
    Q,
    SR,
    E,
    interrupt_out_adc,
    IPCORE_CLK,
    Detect_Rise_Positive_out1,
    S,
    \HDL_Counter_out1_reg[7] ,
    \HDL_Counter_out10_inferred__0/i__carry ,
    \HDL_Counter_out1_reg[7]_0 ,
    \HDL_Counter_out1_reg[7]_1 );
  output U_k_1;
  output U_k_1_0;
  output U_k;
  output PipelineDelay_out1;
  output [0:0]CO;
  output [7:0]Q;
  input [0:0]SR;
  input [0:0]E;
  input interrupt_out_adc;
  input IPCORE_CLK;
  input Detect_Rise_Positive_out1;
  input [7:0]S;
  input [7:0]\HDL_Counter_out1_reg[7] ;
  input [7:0]\HDL_Counter_out10_inferred__0/i__carry ;
  input [0:0]\HDL_Counter_out1_reg[7]_0 ;
  input [0:0]\HDL_Counter_out1_reg[7]_1 ;

  wire [0:0]CO;
  wire Detect_Rise_Positive_out1;
  wire [0:0]E;
  wire [7:0]\HDL_Counter_out10_inferred__0/i__carry ;
  wire [7:0]\HDL_Counter_out1_reg[7] ;
  wire [0:0]\HDL_Counter_out1_reg[7]_0 ;
  wire [0:0]\HDL_Counter_out1_reg[7]_1 ;
  wire IPCORE_CLK;
  wire PipelineDelay_out1;
  wire [7:0]Q;
  wire [7:0]S;
  wire [0:0]SR;
  wire U_k;
  wire U_k_1;
  wire U_k_1_0;
  wire interrupt_out_adc;

  zusys_mux_axi_ip_1_0_mux_axi_ip_src_mux_axi u_mux_axi_ip_src_mux_axi
       (.CO(CO),
        .Detect_Rise_Positive_out1(Detect_Rise_Positive_out1),
        .E(E),
        .\HDL_Counter_out10_inferred__0/i__carry (\HDL_Counter_out10_inferred__0/i__carry ),
        .\HDL_Counter_out1_reg[7] (\HDL_Counter_out1_reg[7] ),
        .\HDL_Counter_out1_reg[7]_0 (\HDL_Counter_out1_reg[7]_0 ),
        .\HDL_Counter_out1_reg[7]_1 (\HDL_Counter_out1_reg[7]_1 ),
        .IPCORE_CLK(IPCORE_CLK),
        .PipelineDelay_out1(PipelineDelay_out1),
        .Q(Q),
        .S(S),
        .SR(SR),
        .U_k(U_k),
        .U_k_1(U_k_1),
        .U_k_1_0(U_k_1_0),
        .interrupt_out_adc(interrupt_out_adc));
endmodule

(* ORIG_REF_NAME = "mux_axi_ip_reset_sync" *) 
module zusys_mux_axi_ip_1_0_mux_axi_ip_reset_sync
   (SR,
    reset_in,
    IPCORE_CLK,
    AXI4_Lite_ARESETN,
    IPCORE_RESETN,
    soft_reset);
  output [0:0]SR;
  input reset_in;
  input IPCORE_CLK;
  input AXI4_Lite_ARESETN;
  input IPCORE_RESETN;
  input soft_reset;

  wire AXI4_Lite_ARESETN;
  wire IPCORE_CLK;
  wire IPCORE_RESETN;
  wire [0:0]SR;
  wire reset_in;
  wire reset_out_i_1_n_0;
  wire reset_pipe;
  wire soft_reset;

  LUT4 #(
    .INIT(16'hFFDF)) 
    reset_out_i_1
       (.I0(AXI4_Lite_ARESETN),
        .I1(reset_pipe),
        .I2(IPCORE_RESETN),
        .I3(soft_reset),
        .O(reset_out_i_1_n_0));
  FDRE reset_out_reg
       (.C(IPCORE_CLK),
        .CE(1'b1),
        .D(reset_out_i_1_n_0),
        .Q(SR),
        .R(1'b0));
  FDRE reset_pipe_reg
       (.C(IPCORE_CLK),
        .CE(1'b1),
        .D(reset_in),
        .Q(reset_pipe),
        .R(1'b0));
endmodule

(* ORIG_REF_NAME = "mux_axi_ip_src_Detect_Fall_Nonpositive2" *) 
module zusys_mux_axi_ip_1_0_mux_axi_ip_src_Detect_Fall_Nonpositive2
   (U_k_1_0,
    U_k,
    SR,
    E,
    IPCORE_CLK,
    Q);
  output U_k_1_0;
  output U_k;
  input [0:0]SR;
  input [0:0]E;
  input IPCORE_CLK;
  input [7:0]Q;

  wire [0:0]E;
  wire IPCORE_CLK;
  wire [7:0]Q;
  wire [0:0]SR;
  wire U_k;
  wire U_k_1_0;
  wire \interrupt_out_isr[7]_INST_0_i_2_n_0 ;

  FDRE U_k_1_reg
       (.C(IPCORE_CLK),
        .CE(E),
        .D(U_k),
        .Q(U_k_1_0),
        .R(SR));
  LUT5 #(
    .INIT(32'h00010000)) 
    \interrupt_out_isr[7]_INST_0_i_1 
       (.I0(Q[0]),
        .I1(Q[1]),
        .I2(Q[2]),
        .I3(Q[3]),
        .I4(\interrupt_out_isr[7]_INST_0_i_2_n_0 ),
        .O(U_k));
  LUT4 #(
    .INIT(16'h0001)) 
    \interrupt_out_isr[7]_INST_0_i_2 
       (.I0(Q[7]),
        .I1(Q[6]),
        .I2(Q[5]),
        .I3(Q[4]),
        .O(\interrupt_out_isr[7]_INST_0_i_2_n_0 ));
endmodule

(* ORIG_REF_NAME = "mux_axi_ip_src_Detect_Rise_Positive" *) 
module zusys_mux_axi_ip_1_0_mux_axi_ip_src_Detect_Rise_Positive
   (U_k_1,
    SR,
    E,
    interrupt_out_adc,
    IPCORE_CLK);
  output U_k_1;
  input [0:0]SR;
  input [0:0]E;
  input interrupt_out_adc;
  input IPCORE_CLK;

  wire [0:0]E;
  wire IPCORE_CLK;
  wire [0:0]SR;
  wire U_k_1;
  wire interrupt_out_adc;

  FDRE U_k_1_reg
       (.C(IPCORE_CLK),
        .CE(E),
        .D(interrupt_out_adc),
        .Q(U_k_1),
        .R(SR));
endmodule

(* ORIG_REF_NAME = "mux_axi_ip_src_Subsystem1" *) 
module zusys_mux_axi_ip_1_0_mux_axi_ip_src_Subsystem1
   (U_k_1,
    U_k_1_0,
    U_k,
    PipelineDelay_out1,
    CO,
    Q,
    SR,
    E,
    interrupt_out_adc,
    IPCORE_CLK,
    Detect_Rise_Positive_out1,
    S,
    \HDL_Counter_out1_reg[7]_0 ,
    \HDL_Counter_out10_inferred__0/i__carry_0 ,
    \HDL_Counter_out1_reg[7]_1 ,
    \HDL_Counter_out1_reg[7]_2 );
  output U_k_1;
  output U_k_1_0;
  output U_k;
  output PipelineDelay_out1;
  output [0:0]CO;
  output [7:0]Q;
  input [0:0]SR;
  input [0:0]E;
  input interrupt_out_adc;
  input IPCORE_CLK;
  input Detect_Rise_Positive_out1;
  input [7:0]S;
  input [7:0]\HDL_Counter_out1_reg[7]_0 ;
  input [7:0]\HDL_Counter_out10_inferred__0/i__carry_0 ;
  input [0:0]\HDL_Counter_out1_reg[7]_1 ;
  input [0:0]\HDL_Counter_out1_reg[7]_2 ;

  wire [0:0]CO;
  wire Detect_Rise_Positive_out1;
  wire [0:0]E;
  wire [7:0]\HDL_Counter_out10_inferred__0/i__carry_0 ;
  wire \HDL_Counter_out10_inferred__0/i__carry__0_n_1 ;
  wire \HDL_Counter_out10_inferred__0/i__carry__0_n_2 ;
  wire \HDL_Counter_out10_inferred__0/i__carry__0_n_3 ;
  wire \HDL_Counter_out10_inferred__0/i__carry__0_n_4 ;
  wire \HDL_Counter_out10_inferred__0/i__carry__0_n_5 ;
  wire \HDL_Counter_out10_inferred__0/i__carry__0_n_6 ;
  wire \HDL_Counter_out10_inferred__0/i__carry__0_n_7 ;
  wire \HDL_Counter_out10_inferred__0/i__carry_n_0 ;
  wire \HDL_Counter_out10_inferred__0/i__carry_n_1 ;
  wire \HDL_Counter_out10_inferred__0/i__carry_n_2 ;
  wire \HDL_Counter_out10_inferred__0/i__carry_n_3 ;
  wire \HDL_Counter_out10_inferred__0/i__carry_n_4 ;
  wire \HDL_Counter_out10_inferred__0/i__carry_n_5 ;
  wire \HDL_Counter_out10_inferred__0/i__carry_n_6 ;
  wire \HDL_Counter_out10_inferred__0/i__carry_n_7 ;
  wire \HDL_Counter_out1[7]_i_4_n_0 ;
  wire [7:0]HDL_Counter_out1_reg;
  wire [7:0]\HDL_Counter_out1_reg[7]_0 ;
  wire [0:0]\HDL_Counter_out1_reg[7]_1 ;
  wire [0:0]\HDL_Counter_out1_reg[7]_2 ;
  wire IPCORE_CLK;
  wire PipelineDelay_out1;
  wire [7:0]Q;
  wire [7:0]S;
  wire [0:0]SR;
  wire U_k;
  wire U_k_1;
  wire U_k_1_0;
  wire i__carry_i_1_n_0;
  wire i__carry_i_2_n_0;
  wire i__carry_i_3_n_0;
  wire i__carry_i_4_n_0;
  wire interrupt_out_adc;
  wire [7:0]p_0_in__0;
  wire [7:0]\NLW_HDL_Counter_out10_inferred__0/i__carry_O_UNCONNECTED ;
  wire [7:0]\NLW_HDL_Counter_out10_inferred__0/i__carry__0_O_UNCONNECTED ;

  FDRE \Delay_out1_reg[0] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(HDL_Counter_out1_reg[0]),
        .Q(Q[0]),
        .R(SR));
  FDRE \Delay_out1_reg[1] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(HDL_Counter_out1_reg[1]),
        .Q(Q[1]),
        .R(SR));
  FDRE \Delay_out1_reg[2] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(HDL_Counter_out1_reg[2]),
        .Q(Q[2]),
        .R(SR));
  FDRE \Delay_out1_reg[3] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(HDL_Counter_out1_reg[3]),
        .Q(Q[3]),
        .R(SR));
  FDRE \Delay_out1_reg[4] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(HDL_Counter_out1_reg[4]),
        .Q(Q[4]),
        .R(SR));
  FDRE \Delay_out1_reg[5] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(HDL_Counter_out1_reg[5]),
        .Q(Q[5]),
        .R(SR));
  FDRE \Delay_out1_reg[6] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(HDL_Counter_out1_reg[6]),
        .Q(Q[6]),
        .R(SR));
  FDRE \Delay_out1_reg[7] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(HDL_Counter_out1_reg[7]),
        .Q(Q[7]),
        .R(SR));
  (* COMPARATOR_THRESHOLD = "11" *) 
  CARRY8 \HDL_Counter_out10_inferred__0/i__carry 
       (.CI(1'b1),
        .CI_TOP(1'b0),
        .CO({\HDL_Counter_out10_inferred__0/i__carry_n_0 ,\HDL_Counter_out10_inferred__0/i__carry_n_1 ,\HDL_Counter_out10_inferred__0/i__carry_n_2 ,\HDL_Counter_out10_inferred__0/i__carry_n_3 ,\HDL_Counter_out10_inferred__0/i__carry_n_4 ,\HDL_Counter_out10_inferred__0/i__carry_n_5 ,\HDL_Counter_out10_inferred__0/i__carry_n_6 ,\HDL_Counter_out10_inferred__0/i__carry_n_7 }),
        .DI({1'b0,1'b0,1'b0,1'b0,i__carry_i_1_n_0,i__carry_i_2_n_0,i__carry_i_3_n_0,i__carry_i_4_n_0}),
        .O(\NLW_HDL_Counter_out10_inferred__0/i__carry_O_UNCONNECTED [7:0]),
        .S(S));
  (* COMPARATOR_THRESHOLD = "11" *) 
  CARRY8 \HDL_Counter_out10_inferred__0/i__carry__0 
       (.CI(\HDL_Counter_out10_inferred__0/i__carry_n_0 ),
        .CI_TOP(1'b0),
        .CO({CO,\HDL_Counter_out10_inferred__0/i__carry__0_n_1 ,\HDL_Counter_out10_inferred__0/i__carry__0_n_2 ,\HDL_Counter_out10_inferred__0/i__carry__0_n_3 ,\HDL_Counter_out10_inferred__0/i__carry__0_n_4 ,\HDL_Counter_out10_inferred__0/i__carry__0_n_5 ,\HDL_Counter_out10_inferred__0/i__carry__0_n_6 ,\HDL_Counter_out10_inferred__0/i__carry__0_n_7 }),
        .DI({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .O(\NLW_HDL_Counter_out10_inferred__0/i__carry__0_O_UNCONNECTED [7:0]),
        .S(\HDL_Counter_out1_reg[7]_0 ));
  LUT1 #(
    .INIT(2'h1)) 
    \HDL_Counter_out1[0]_i_1 
       (.I0(HDL_Counter_out1_reg[0]),
        .O(p_0_in__0[0]));
  (* SOFT_HLUTNM = "soft_lutpair7" *) 
  LUT2 #(
    .INIT(4'h6)) 
    \HDL_Counter_out1[1]_i_1 
       (.I0(HDL_Counter_out1_reg[0]),
        .I1(HDL_Counter_out1_reg[1]),
        .O(p_0_in__0[1]));
  (* SOFT_HLUTNM = "soft_lutpair7" *) 
  LUT3 #(
    .INIT(8'h78)) 
    \HDL_Counter_out1[2]_i_1 
       (.I0(HDL_Counter_out1_reg[1]),
        .I1(HDL_Counter_out1_reg[0]),
        .I2(HDL_Counter_out1_reg[2]),
        .O(p_0_in__0[2]));
  (* SOFT_HLUTNM = "soft_lutpair6" *) 
  LUT4 #(
    .INIT(16'h7F80)) 
    \HDL_Counter_out1[3]_i_1 
       (.I0(HDL_Counter_out1_reg[2]),
        .I1(HDL_Counter_out1_reg[0]),
        .I2(HDL_Counter_out1_reg[1]),
        .I3(HDL_Counter_out1_reg[3]),
        .O(p_0_in__0[3]));
  (* SOFT_HLUTNM = "soft_lutpair6" *) 
  LUT5 #(
    .INIT(32'h7FFF8000)) 
    \HDL_Counter_out1[4]_i_1 
       (.I0(HDL_Counter_out1_reg[3]),
        .I1(HDL_Counter_out1_reg[1]),
        .I2(HDL_Counter_out1_reg[0]),
        .I3(HDL_Counter_out1_reg[2]),
        .I4(HDL_Counter_out1_reg[4]),
        .O(p_0_in__0[4]));
  LUT6 #(
    .INIT(64'h7FFFFFFF80000000)) 
    \HDL_Counter_out1[5]_i_1 
       (.I0(HDL_Counter_out1_reg[4]),
        .I1(HDL_Counter_out1_reg[2]),
        .I2(HDL_Counter_out1_reg[0]),
        .I3(HDL_Counter_out1_reg[1]),
        .I4(HDL_Counter_out1_reg[3]),
        .I5(HDL_Counter_out1_reg[5]),
        .O(p_0_in__0[5]));
  (* SOFT_HLUTNM = "soft_lutpair8" *) 
  LUT2 #(
    .INIT(4'h9)) 
    \HDL_Counter_out1[6]_i_1 
       (.I0(\HDL_Counter_out1[7]_i_4_n_0 ),
        .I1(HDL_Counter_out1_reg[6]),
        .O(p_0_in__0[6]));
  (* SOFT_HLUTNM = "soft_lutpair8" *) 
  LUT3 #(
    .INIT(8'hD2)) 
    \HDL_Counter_out1[7]_i_3 
       (.I0(HDL_Counter_out1_reg[6]),
        .I1(\HDL_Counter_out1[7]_i_4_n_0 ),
        .I2(HDL_Counter_out1_reg[7]),
        .O(p_0_in__0[7]));
  LUT6 #(
    .INIT(64'h7FFFFFFFFFFFFFFF)) 
    \HDL_Counter_out1[7]_i_4 
       (.I0(HDL_Counter_out1_reg[4]),
        .I1(HDL_Counter_out1_reg[2]),
        .I2(HDL_Counter_out1_reg[0]),
        .I3(HDL_Counter_out1_reg[1]),
        .I4(HDL_Counter_out1_reg[3]),
        .I5(HDL_Counter_out1_reg[5]),
        .O(\HDL_Counter_out1[7]_i_4_n_0 ));
  FDRE \HDL_Counter_out1_reg[0] 
       (.C(IPCORE_CLK),
        .CE(\HDL_Counter_out1_reg[7]_2 ),
        .D(p_0_in__0[0]),
        .Q(HDL_Counter_out1_reg[0]),
        .R(\HDL_Counter_out1_reg[7]_1 ));
  FDRE \HDL_Counter_out1_reg[1] 
       (.C(IPCORE_CLK),
        .CE(\HDL_Counter_out1_reg[7]_2 ),
        .D(p_0_in__0[1]),
        .Q(HDL_Counter_out1_reg[1]),
        .R(\HDL_Counter_out1_reg[7]_1 ));
  FDRE \HDL_Counter_out1_reg[2] 
       (.C(IPCORE_CLK),
        .CE(\HDL_Counter_out1_reg[7]_2 ),
        .D(p_0_in__0[2]),
        .Q(HDL_Counter_out1_reg[2]),
        .R(\HDL_Counter_out1_reg[7]_1 ));
  FDRE \HDL_Counter_out1_reg[3] 
       (.C(IPCORE_CLK),
        .CE(\HDL_Counter_out1_reg[7]_2 ),
        .D(p_0_in__0[3]),
        .Q(HDL_Counter_out1_reg[3]),
        .R(\HDL_Counter_out1_reg[7]_1 ));
  FDRE \HDL_Counter_out1_reg[4] 
       (.C(IPCORE_CLK),
        .CE(\HDL_Counter_out1_reg[7]_2 ),
        .D(p_0_in__0[4]),
        .Q(HDL_Counter_out1_reg[4]),
        .R(\HDL_Counter_out1_reg[7]_1 ));
  FDRE \HDL_Counter_out1_reg[5] 
       (.C(IPCORE_CLK),
        .CE(\HDL_Counter_out1_reg[7]_2 ),
        .D(p_0_in__0[5]),
        .Q(HDL_Counter_out1_reg[5]),
        .R(\HDL_Counter_out1_reg[7]_1 ));
  FDRE \HDL_Counter_out1_reg[6] 
       (.C(IPCORE_CLK),
        .CE(\HDL_Counter_out1_reg[7]_2 ),
        .D(p_0_in__0[6]),
        .Q(HDL_Counter_out1_reg[6]),
        .R(\HDL_Counter_out1_reg[7]_1 ));
  FDRE \HDL_Counter_out1_reg[7] 
       (.C(IPCORE_CLK),
        .CE(\HDL_Counter_out1_reg[7]_2 ),
        .D(p_0_in__0[7]),
        .Q(HDL_Counter_out1_reg[7]),
        .R(\HDL_Counter_out1_reg[7]_1 ));
  FDRE PipelineDelay_out1_reg
       (.C(IPCORE_CLK),
        .CE(E),
        .D(Detect_Rise_Positive_out1),
        .Q(PipelineDelay_out1),
        .R(SR));
  LUT4 #(
    .INIT(16'h22B2)) 
    i__carry_i_1
       (.I0(Q[7]),
        .I1(\HDL_Counter_out10_inferred__0/i__carry_0 [7]),
        .I2(Q[6]),
        .I3(\HDL_Counter_out10_inferred__0/i__carry_0 [6]),
        .O(i__carry_i_1_n_0));
  LUT4 #(
    .INIT(16'h22B2)) 
    i__carry_i_2
       (.I0(Q[5]),
        .I1(\HDL_Counter_out10_inferred__0/i__carry_0 [5]),
        .I2(Q[4]),
        .I3(\HDL_Counter_out10_inferred__0/i__carry_0 [4]),
        .O(i__carry_i_2_n_0));
  LUT4 #(
    .INIT(16'h22B2)) 
    i__carry_i_3
       (.I0(Q[3]),
        .I1(\HDL_Counter_out10_inferred__0/i__carry_0 [3]),
        .I2(Q[2]),
        .I3(\HDL_Counter_out10_inferred__0/i__carry_0 [2]),
        .O(i__carry_i_3_n_0));
  LUT4 #(
    .INIT(16'h22B2)) 
    i__carry_i_4
       (.I0(Q[1]),
        .I1(\HDL_Counter_out10_inferred__0/i__carry_0 [1]),
        .I2(Q[0]),
        .I3(\HDL_Counter_out10_inferred__0/i__carry_0 [0]),
        .O(i__carry_i_4_n_0));
  zusys_mux_axi_ip_1_0_mux_axi_ip_src_Detect_Fall_Nonpositive2 u_Detect_Fall_Nonpositive2
       (.E(E),
        .IPCORE_CLK(IPCORE_CLK),
        .Q(HDL_Counter_out1_reg),
        .SR(SR),
        .U_k(U_k),
        .U_k_1_0(U_k_1_0));
  zusys_mux_axi_ip_1_0_mux_axi_ip_src_Detect_Rise_Positive u_Detect_Rise_Positive
       (.E(E),
        .IPCORE_CLK(IPCORE_CLK),
        .SR(SR),
        .U_k_1(U_k_1),
        .interrupt_out_adc(interrupt_out_adc));
endmodule

(* ORIG_REF_NAME = "mux_axi_ip_src_mux_axi" *) 
module zusys_mux_axi_ip_1_0_mux_axi_ip_src_mux_axi
   (U_k_1,
    U_k_1_0,
    U_k,
    PipelineDelay_out1,
    CO,
    Q,
    SR,
    E,
    interrupt_out_adc,
    IPCORE_CLK,
    Detect_Rise_Positive_out1,
    S,
    \HDL_Counter_out1_reg[7] ,
    \HDL_Counter_out10_inferred__0/i__carry ,
    \HDL_Counter_out1_reg[7]_0 ,
    \HDL_Counter_out1_reg[7]_1 );
  output U_k_1;
  output U_k_1_0;
  output U_k;
  output PipelineDelay_out1;
  output [0:0]CO;
  output [7:0]Q;
  input [0:0]SR;
  input [0:0]E;
  input interrupt_out_adc;
  input IPCORE_CLK;
  input Detect_Rise_Positive_out1;
  input [7:0]S;
  input [7:0]\HDL_Counter_out1_reg[7] ;
  input [7:0]\HDL_Counter_out10_inferred__0/i__carry ;
  input [0:0]\HDL_Counter_out1_reg[7]_0 ;
  input [0:0]\HDL_Counter_out1_reg[7]_1 ;

  wire [0:0]CO;
  wire Detect_Rise_Positive_out1;
  wire [0:0]E;
  wire [7:0]\HDL_Counter_out10_inferred__0/i__carry ;
  wire [7:0]\HDL_Counter_out1_reg[7] ;
  wire [0:0]\HDL_Counter_out1_reg[7]_0 ;
  wire [0:0]\HDL_Counter_out1_reg[7]_1 ;
  wire IPCORE_CLK;
  wire PipelineDelay_out1;
  wire [7:0]Q;
  wire [7:0]S;
  wire [0:0]SR;
  wire U_k;
  wire U_k_1;
  wire U_k_1_0;
  wire interrupt_out_adc;

  zusys_mux_axi_ip_1_0_mux_axi_ip_src_Subsystem1 u_Subsystem1
       (.CO(CO),
        .Detect_Rise_Positive_out1(Detect_Rise_Positive_out1),
        .E(E),
        .\HDL_Counter_out10_inferred__0/i__carry_0 (\HDL_Counter_out10_inferred__0/i__carry ),
        .\HDL_Counter_out1_reg[7]_0 (\HDL_Counter_out1_reg[7] ),
        .\HDL_Counter_out1_reg[7]_1 (\HDL_Counter_out1_reg[7]_0 ),
        .\HDL_Counter_out1_reg[7]_2 (\HDL_Counter_out1_reg[7]_1 ),
        .IPCORE_CLK(IPCORE_CLK),
        .PipelineDelay_out1(PipelineDelay_out1),
        .Q(Q),
        .S(S),
        .SR(SR),
        .U_k(U_k),
        .U_k_1(U_k_1),
        .U_k_1_0(U_k_1_0),
        .interrupt_out_adc(interrupt_out_adc));
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
