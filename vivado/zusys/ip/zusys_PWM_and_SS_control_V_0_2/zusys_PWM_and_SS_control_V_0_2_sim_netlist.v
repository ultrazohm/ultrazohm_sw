// Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// --------------------------------------------------------------------------------
// Tool Version: Vivado v.2020.1.1 (win64) Build 2960000 Wed Aug  5 22:57:20 MDT 2020
// Date        : Fri Jan 28 14:43:25 2022
// Host        : enc177112 running 64-bit major release  (build 9200)
// Command     : write_verilog -force -mode funcsim -rename_top zusys_PWM_and_SS_control_V_0_2 -prefix
//               zusys_PWM_and_SS_control_V_0_2_ zusys_PWM_and_SS_control_V_0_0_sim_netlist.v
// Design      : zusys_PWM_and_SS_control_V_0_0
// Purpose     : This verilog netlist is a functional simulation representation of the design and should not be modified
//               or synthesized. This netlist cannot be used for SDF annotated simulation.
// Device      : xczu9eg-ffvc900-1-e
// --------------------------------------------------------------------------------
`timescale 1 ps / 1 ps

module zusys_PWM_and_SS_control_V_0_2_PWM_and_SS_control_V3_ip
   (FSM_sequential_axi_lite_rstate_reg,
    PWM_enb_out,
    Triangular_Max,
    Triangular_Min,
    \HDL_Counter2_count_reg[7] ,
    DI,
    S,
    Q,
    AXI4_Lite_RDATA,
    SS0_OUT,
    SS1_OUT,
    SS2_OUT,
    SS3_OUT,
    SS4_OUT,
    SS5_OUT,
    AXI4_Lite_ARREADY,
    AXI4_Lite_AWREADY,
    AXI4_Lite_ACLK,
    IPCORE_CLK,
    B,
    CO,
    AXI4_Lite_AWADDR,
    AXI4_Lite_WDATA,
    SS0_IN_External,
    SS1_IN_External,
    SS2_IN_External,
    SS3_IN_External,
    SS4_IN_External,
    SS5_IN_External,
    AXI4_Lite_ARVALID,
    AXI4_Lite_ARADDR,
    AXI4_Lite_RREADY,
    AXI4_Lite_AWVALID,
    AXI4_Lite_WVALID,
    AXI4_Lite_ARESETN,
    IPCORE_RESETN,
    AXI4_Lite_BREADY,
    AXI4_Lite_WSTRB,
    m_u1_norm,
    m_u2_norm,
    m_u3_norm);
  output FSM_sequential_axi_lite_rstate_reg;
  output PWM_enb_out;
  output Triangular_Max;
  output Triangular_Min;
  output [6:0]\HDL_Counter2_count_reg[7] ;
  output [1:0]DI;
  output [7:0]S;
  output [1:0]Q;
  output [26:0]AXI4_Lite_RDATA;
  output SS0_OUT;
  output SS1_OUT;
  output SS2_OUT;
  output SS3_OUT;
  output SS4_OUT;
  output SS5_OUT;
  output AXI4_Lite_ARREADY;
  output AXI4_Lite_AWREADY;
  input AXI4_Lite_ACLK;
  input IPCORE_CLK;
  input [7:0]B;
  input [0:0]CO;
  input [13:0]AXI4_Lite_AWADDR;
  input [24:0]AXI4_Lite_WDATA;
  input SS0_IN_External;
  input SS1_IN_External;
  input SS2_IN_External;
  input SS3_IN_External;
  input SS4_IN_External;
  input SS5_IN_External;
  input AXI4_Lite_ARVALID;
  input [13:0]AXI4_Lite_ARADDR;
  input AXI4_Lite_RREADY;
  input AXI4_Lite_AWVALID;
  input AXI4_Lite_WVALID;
  input AXI4_Lite_ARESETN;
  input IPCORE_RESETN;
  input AXI4_Lite_BREADY;
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
  wire [26:0]AXI4_Lite_RDATA;
  wire AXI4_Lite_RREADY;
  wire [24:0]AXI4_Lite_WDATA;
  wire [3:0]AXI4_Lite_WSTRB;
  wire AXI4_Lite_WVALID;
  wire [7:0]B;
  wire [0:0]CO;
  wire [1:0]DI;
  wire FSM_sequential_axi_lite_rstate_reg;
  wire [6:0]\HDL_Counter2_count_reg[7] ;
  wire IPCORE_CLK;
  wire IPCORE_RESETN;
  wire [1:0]Mode_rd_AXI_sig;
  wire [24:0]PWM_T_carrier_us_rd_AXI_sig;
  wire PWM_en_rd_AXI_sig;
  wire PWM_enb_out;
  wire [24:10]PWM_f_carrier_kHz_rd_AXI_sig;
  wire [17:0]PWM_min_pulse_width_rd_AXI_sig;
  wire [1:0]Q;
  wire [7:0]S;
  wire SS0_IN_External;
  wire SS0_OUT;
  wire SS1_IN_External;
  wire SS1_OUT;
  wire SS2_IN_External;
  wire SS2_OUT;
  wire SS3_IN_External;
  wire SS3_OUT;
  wire SS4_IN_External;
  wire SS4_OUT;
  wire SS5_IN_External;
  wire SS5_OUT;
  wire Triangular_Max;
  wire Triangular_Min;
  wire [13:0]m_u1_norm;
  wire [13:0]m_u2_norm;
  wire [13:0]m_u3_norm;
  wire reset;
  wire u_PWM_and_SS_control_V3_ip_axi_lite_inst_n_8;
  wire u_PWM_and_SS_control_V3_ip_dut_inst_n_20;
  wire u_PWM_and_SS_control_V3_ip_dut_inst_n_21;
  wire u_PWM_and_SS_control_V3_ip_dut_inst_n_22;
  wire u_PWM_and_SS_control_V3_ip_dut_inst_n_23;
  wire u_PWM_and_SS_control_V3_ip_dut_inst_n_24;
  wire u_PWM_and_SS_control_V3_ip_dut_inst_n_25;
  wire u_PWM_and_SS_control_V3_ip_dut_inst_n_26;
  wire u_PWM_and_SS_control_V3_ip_dut_inst_n_27;
  wire u_PWM_and_SS_control_V3_ip_dut_inst_n_28;
  wire u_PWM_and_SS_control_V3_ip_dut_inst_n_29;
  wire \u_PWM_and_SS_control_V3_ip_src_PWM_and_Switching_Signal_Control/u_GenPWM/PWM_en_AXI_1 ;
  wire [1:0]write_Mode_AXI;
  wire write_PWM_en_AXI;
  wire [17:0]write_PWM_min_pulse_width_AXI;
  wire [24:0]write_Scal_T_carrier_AXI;
  wire [24:0]write_Scal_f_carrier_AXI;
  wire [1:0]write_TriState_HB1_AXI;
  wire [1:0]write_TriState_HB2_AXI;
  wire [1:0]write_TriState_HB3_AXI;
  wire write_axi_enable;
  wire [13:0]write_m_u1_norm_AXI;
  wire [13:0]write_m_u2_norm_AXI;
  wire [13:0]write_m_u3_norm_AXI;

  zusys_PWM_and_SS_control_V_0_2_PWM_and_SS_control_V3_ip_axi_lite u_PWM_and_SS_control_V3_ip_axi_lite_inst
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
        .CEA1(write_axi_enable),
        .CEB2(u_PWM_and_SS_control_V3_ip_axi_lite_inst_n_8),
        .D({PWM_f_carrier_kHz_rd_AXI_sig,u_PWM_and_SS_control_V3_ip_dut_inst_n_20,u_PWM_and_SS_control_V3_ip_dut_inst_n_21,u_PWM_and_SS_control_V3_ip_dut_inst_n_22,u_PWM_and_SS_control_V3_ip_dut_inst_n_23,u_PWM_and_SS_control_V3_ip_dut_inst_n_24,u_PWM_and_SS_control_V3_ip_dut_inst_n_25,u_PWM_and_SS_control_V3_ip_dut_inst_n_26,u_PWM_and_SS_control_V3_ip_dut_inst_n_27,u_PWM_and_SS_control_V3_ip_dut_inst_n_28,u_PWM_and_SS_control_V3_ip_dut_inst_n_29}),
        .FSM_sequential_axi_lite_rstate_reg(FSM_sequential_axi_lite_rstate_reg),
        .IPCORE_RESETN(IPCORE_RESETN),
        .PWM_en_AXI_1(\u_PWM_and_SS_control_V3_ip_src_PWM_and_Switching_Signal_Control/u_GenPWM/PWM_en_AXI_1 ),
        .PWM_en_rd_AXI_sig(PWM_en_rd_AXI_sig),
        .Q(Q),
        .\read_reg_Mode_rd_AXI_reg[1] (Mode_rd_AXI_sig),
        .\read_reg_PWM_T_carrier_us_rd_AXI_reg[24] (PWM_T_carrier_us_rd_AXI_sig),
        .\read_reg_PWM_min_pulse_width_rd_AXI_reg[17] (PWM_min_pulse_width_rd_AXI_sig),
        .reset(reset),
        .write_PWM_en_AXI(write_PWM_en_AXI),
        .\write_reg_Mode_AXI_reg[1] (write_Mode_AXI),
        .\write_reg_PWM_min_pulse_width_AXI_reg[17] (write_PWM_min_pulse_width_AXI),
        .\write_reg_Scal_T_carrier_AXI_reg[24] (write_Scal_T_carrier_AXI),
        .\write_reg_Scal_f_carrier_AXI_reg[24] (write_Scal_f_carrier_AXI),
        .\write_reg_TriState_HB1_AXI_reg[1] (write_TriState_HB1_AXI),
        .\write_reg_TriState_HB2_AXI_reg[1] (write_TriState_HB2_AXI),
        .\write_reg_TriState_HB3_AXI_reg[1] (write_TriState_HB3_AXI),
        .\write_reg_m_u1_norm_AXI_reg[13] (write_m_u1_norm_AXI),
        .\write_reg_m_u2_norm_AXI_reg[13] (write_m_u2_norm_AXI),
        .\write_reg_m_u3_norm_AXI_reg[13] (write_m_u3_norm_AXI));
  zusys_PWM_and_SS_control_V_0_2_PWM_and_SS_control_V3_ip_dut u_PWM_and_SS_control_V3_ip_dut_inst
       (.B(B),
        .CEB2(u_PWM_and_SS_control_V3_ip_axi_lite_inst_n_8),
        .CO(CO),
        .D(write_Scal_f_carrier_AXI),
        .DI({DI[0],\HDL_Counter2_count_reg[7] [0]}),
        .E(write_axi_enable),
        .\HDL_Counter2_count_reg[0] (DI[1]),
        .\HDL_Counter2_count_reg[2] (\HDL_Counter2_count_reg[7] [1]),
        .\HDL_Counter2_count_reg[3] (\HDL_Counter2_count_reg[7] [2]),
        .\HDL_Counter2_count_reg[4] (\HDL_Counter2_count_reg[7] [3]),
        .\HDL_Counter2_count_reg[5] (\HDL_Counter2_count_reg[7] [4]),
        .\HDL_Counter2_count_reg[6] (\HDL_Counter2_count_reg[7] [5]),
        .\HDL_Counter2_count_reg[7] (\HDL_Counter2_count_reg[7] [6]),
        .IPCORE_CLK(IPCORE_CLK),
        .PWM_en_AXI_1(\u_PWM_and_SS_control_V3_ip_src_PWM_and_Switching_Signal_Control/u_GenPWM/PWM_en_AXI_1 ),
        .PWM_en_rd_AXI_sig(PWM_en_rd_AXI_sig),
        .PWM_enb_out(PWM_enb_out),
        .Q(PWM_T_carrier_us_rd_AXI_sig),
        .S(S),
        .SS0_IN_External(SS0_IN_External),
        .SS0_OUT(SS0_OUT),
        .SS1_IN_External(SS1_IN_External),
        .SS1_OUT(SS1_OUT),
        .SS2_IN_External(SS2_IN_External),
        .SS2_OUT(SS2_OUT),
        .SS3_IN_External(SS3_IN_External),
        .SS3_OUT(SS3_OUT),
        .SS4_IN_External(SS4_IN_External),
        .SS4_OUT(SS4_OUT),
        .SS5_IN_External(SS5_IN_External),
        .SS5_OUT(SS5_OUT),
        .\T_carrier_us_AXI_1_reg[24] (write_Scal_T_carrier_AXI),
        .Triangular_Max(Triangular_Max),
        .Triangular_Min(Triangular_Min),
        .\U1_norm_1_reg[13] (write_m_u1_norm_AXI),
        .\U2_norm_1_reg[13] (write_m_u2_norm_AXI),
        .\U3_norm_1_reg[13] (write_m_u3_norm_AXI),
        .\f_carrier_kHz_AXI_2_reg[24] ({PWM_f_carrier_kHz_rd_AXI_sig,u_PWM_and_SS_control_V3_ip_dut_inst_n_20,u_PWM_and_SS_control_V3_ip_dut_inst_n_21,u_PWM_and_SS_control_V3_ip_dut_inst_n_22,u_PWM_and_SS_control_V3_ip_dut_inst_n_23,u_PWM_and_SS_control_V3_ip_dut_inst_n_24,u_PWM_and_SS_control_V3_ip_dut_inst_n_25,u_PWM_and_SS_control_V3_ip_dut_inst_n_26,u_PWM_and_SS_control_V3_ip_dut_inst_n_27,u_PWM_and_SS_control_V3_ip_dut_inst_n_28,u_PWM_and_SS_control_V3_ip_dut_inst_n_29}),
        .m_u1_norm(m_u1_norm),
        .m_u2_norm(m_u2_norm),
        .m_u3_norm(m_u3_norm),
        .\min_pulse_width_AXI_1_reg[17] (write_PWM_min_pulse_width_AXI),
        .\min_pulse_width_AXI_2_reg[17] (PWM_min_pulse_width_rd_AXI_sig),
        .\reduced_reg_1_reg[0][1] (write_Mode_AXI),
        .\reduced_reg_1_reg[1][1] (Mode_rd_AXI_sig),
        .\reduced_reg_2_reg[0][1] (write_TriState_HB2_AXI),
        .\reduced_reg_3_reg[0][1] (write_TriState_HB3_AXI),
        .\reduced_reg_reg[0][1] (write_TriState_HB1_AXI),
        .reset(reset),
        .write_PWM_en_AXI(write_PWM_en_AXI));
endmodule

module zusys_PWM_and_SS_control_V_0_2_PWM_and_SS_control_V3_ip_addr_decoder
   (read_reg_ip_timestamp,
    read_reg_PWM_en_rd_AXI,
    CEA1,
    write_PWM_en_AXI,
    CEB2,
    \write_reg_Mode_AXI_reg[1]_0 ,
    \write_reg_Scal_f_carrier_AXI_reg[24]_0 ,
    \write_reg_Scal_T_carrier_AXI_reg[24]_0 ,
    \write_reg_PWM_min_pulse_width_AXI_reg[17]_0 ,
    \write_reg_m_u1_norm_AXI_reg[13]_0 ,
    \write_reg_m_u2_norm_AXI_reg[13]_0 ,
    \write_reg_m_u3_norm_AXI_reg[13]_0 ,
    \write_reg_TriState_HB1_AXI_reg[1]_0 ,
    \write_reg_TriState_HB2_AXI_reg[1]_0 ,
    \write_reg_TriState_HB3_AXI_reg[1]_0 ,
    \read_reg_PWM_f_carrier_kHz_rd_AXI_reg[24]_0 ,
    \read_reg_PWM_T_carrier_us_rd_AXI_reg[24]_0 ,
    \read_reg_PWM_min_pulse_width_rd_AXI_reg[17]_0 ,
    \read_reg_Mode_rd_AXI_reg[1]_0 ,
    SR,
    AXI4_Lite_ACLK,
    PWM_en_rd_AXI_sig,
    write_reg_axi_enable_reg_0,
    write_reg_PWM_en_AXI_reg_0,
    PWM_en_AXI_1,
    E,
    Q,
    \write_reg_Scal_f_carrier_AXI_reg[24]_1 ,
    \write_reg_Scal_T_carrier_AXI_reg[24]_1 ,
    \write_reg_PWM_min_pulse_width_AXI_reg[17]_1 ,
    \write_reg_m_u1_norm_AXI_reg[13]_1 ,
    \write_reg_m_u2_norm_AXI_reg[13]_1 ,
    \write_reg_m_u3_norm_AXI_reg[13]_1 ,
    \write_reg_TriState_HB1_AXI_reg[1]_1 ,
    \write_reg_TriState_HB2_AXI_reg[1]_1 ,
    \write_reg_TriState_HB3_AXI_reg[1]_1 ,
    D,
    \read_reg_PWM_T_carrier_us_rd_AXI_reg[24]_1 ,
    \read_reg_PWM_min_pulse_width_rd_AXI_reg[17]_1 ,
    \read_reg_Mode_rd_AXI_reg[1]_1 );
  output [0:0]read_reg_ip_timestamp;
  output read_reg_PWM_en_rd_AXI;
  output CEA1;
  output write_PWM_en_AXI;
  output CEB2;
  output [1:0]\write_reg_Mode_AXI_reg[1]_0 ;
  output [24:0]\write_reg_Scal_f_carrier_AXI_reg[24]_0 ;
  output [24:0]\write_reg_Scal_T_carrier_AXI_reg[24]_0 ;
  output [17:0]\write_reg_PWM_min_pulse_width_AXI_reg[17]_0 ;
  output [13:0]\write_reg_m_u1_norm_AXI_reg[13]_0 ;
  output [13:0]\write_reg_m_u2_norm_AXI_reg[13]_0 ;
  output [13:0]\write_reg_m_u3_norm_AXI_reg[13]_0 ;
  output [1:0]\write_reg_TriState_HB1_AXI_reg[1]_0 ;
  output [1:0]\write_reg_TriState_HB2_AXI_reg[1]_0 ;
  output [1:0]\write_reg_TriState_HB3_AXI_reg[1]_0 ;
  output [24:0]\read_reg_PWM_f_carrier_kHz_rd_AXI_reg[24]_0 ;
  output [24:0]\read_reg_PWM_T_carrier_us_rd_AXI_reg[24]_0 ;
  output [17:0]\read_reg_PWM_min_pulse_width_rd_AXI_reg[17]_0 ;
  output [1:0]\read_reg_Mode_rd_AXI_reg[1]_0 ;
  input [0:0]SR;
  input AXI4_Lite_ACLK;
  input PWM_en_rd_AXI_sig;
  input write_reg_axi_enable_reg_0;
  input write_reg_PWM_en_AXI_reg_0;
  input PWM_en_AXI_1;
  input [0:0]E;
  input [24:0]Q;
  input [0:0]\write_reg_Scal_f_carrier_AXI_reg[24]_1 ;
  input [0:0]\write_reg_Scal_T_carrier_AXI_reg[24]_1 ;
  input [0:0]\write_reg_PWM_min_pulse_width_AXI_reg[17]_1 ;
  input [0:0]\write_reg_m_u1_norm_AXI_reg[13]_1 ;
  input [0:0]\write_reg_m_u2_norm_AXI_reg[13]_1 ;
  input [0:0]\write_reg_m_u3_norm_AXI_reg[13]_1 ;
  input [0:0]\write_reg_TriState_HB1_AXI_reg[1]_1 ;
  input [0:0]\write_reg_TriState_HB2_AXI_reg[1]_1 ;
  input [0:0]\write_reg_TriState_HB3_AXI_reg[1]_1 ;
  input [24:0]D;
  input [24:0]\read_reg_PWM_T_carrier_us_rd_AXI_reg[24]_1 ;
  input [17:0]\read_reg_PWM_min_pulse_width_rd_AXI_reg[17]_1 ;
  input [1:0]\read_reg_Mode_rd_AXI_reg[1]_1 ;

  wire AXI4_Lite_ACLK;
  wire CEA1;
  wire CEB2;
  wire [24:0]D;
  wire [0:0]E;
  wire PWM_en_AXI_1;
  wire PWM_en_rd_AXI_sig;
  wire [24:0]Q;
  wire [0:0]SR;
  wire [1:0]\read_reg_Mode_rd_AXI_reg[1]_0 ;
  wire [1:0]\read_reg_Mode_rd_AXI_reg[1]_1 ;
  wire [24:0]\read_reg_PWM_T_carrier_us_rd_AXI_reg[24]_0 ;
  wire [24:0]\read_reg_PWM_T_carrier_us_rd_AXI_reg[24]_1 ;
  wire read_reg_PWM_en_rd_AXI;
  wire [24:0]\read_reg_PWM_f_carrier_kHz_rd_AXI_reg[24]_0 ;
  wire [17:0]\read_reg_PWM_min_pulse_width_rd_AXI_reg[17]_0 ;
  wire [17:0]\read_reg_PWM_min_pulse_width_rd_AXI_reg[17]_1 ;
  wire [0:0]read_reg_ip_timestamp;
  wire write_PWM_en_AXI;
  wire [1:0]\write_reg_Mode_AXI_reg[1]_0 ;
  wire write_reg_PWM_en_AXI_reg_0;
  wire [17:0]\write_reg_PWM_min_pulse_width_AXI_reg[17]_0 ;
  wire [0:0]\write_reg_PWM_min_pulse_width_AXI_reg[17]_1 ;
  wire [24:0]\write_reg_Scal_T_carrier_AXI_reg[24]_0 ;
  wire [0:0]\write_reg_Scal_T_carrier_AXI_reg[24]_1 ;
  wire [24:0]\write_reg_Scal_f_carrier_AXI_reg[24]_0 ;
  wire [0:0]\write_reg_Scal_f_carrier_AXI_reg[24]_1 ;
  wire [1:0]\write_reg_TriState_HB1_AXI_reg[1]_0 ;
  wire [0:0]\write_reg_TriState_HB1_AXI_reg[1]_1 ;
  wire [1:0]\write_reg_TriState_HB2_AXI_reg[1]_0 ;
  wire [0:0]\write_reg_TriState_HB2_AXI_reg[1]_1 ;
  wire [1:0]\write_reg_TriState_HB3_AXI_reg[1]_0 ;
  wire [0:0]\write_reg_TriState_HB3_AXI_reg[1]_1 ;
  wire write_reg_axi_enable_reg_0;
  wire [13:0]\write_reg_m_u1_norm_AXI_reg[13]_0 ;
  wire [0:0]\write_reg_m_u1_norm_AXI_reg[13]_1 ;
  wire [13:0]\write_reg_m_u2_norm_AXI_reg[13]_0 ;
  wire [0:0]\write_reg_m_u2_norm_AXI_reg[13]_1 ;
  wire [13:0]\write_reg_m_u3_norm_AXI_reg[13]_0 ;
  wire [0:0]\write_reg_m_u3_norm_AXI_reg[13]_1 ;

  LUT2 #(
    .INIT(4'h8)) 
    Product_mul_temp_i_1
       (.I0(CEA1),
        .I1(PWM_en_AXI_1),
        .O(CEB2));
  FDRE \read_reg_Mode_rd_AXI_reg[0] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(\read_reg_Mode_rd_AXI_reg[1]_1 [0]),
        .Q(\read_reg_Mode_rd_AXI_reg[1]_0 [0]),
        .R(SR));
  FDRE \read_reg_Mode_rd_AXI_reg[1] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(\read_reg_Mode_rd_AXI_reg[1]_1 [1]),
        .Q(\read_reg_Mode_rd_AXI_reg[1]_0 [1]),
        .R(SR));
  FDRE \read_reg_PWM_T_carrier_us_rd_AXI_reg[0] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(\read_reg_PWM_T_carrier_us_rd_AXI_reg[24]_1 [0]),
        .Q(\read_reg_PWM_T_carrier_us_rd_AXI_reg[24]_0 [0]),
        .R(SR));
  FDRE \read_reg_PWM_T_carrier_us_rd_AXI_reg[10] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(\read_reg_PWM_T_carrier_us_rd_AXI_reg[24]_1 [10]),
        .Q(\read_reg_PWM_T_carrier_us_rd_AXI_reg[24]_0 [10]),
        .R(SR));
  FDRE \read_reg_PWM_T_carrier_us_rd_AXI_reg[11] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(\read_reg_PWM_T_carrier_us_rd_AXI_reg[24]_1 [11]),
        .Q(\read_reg_PWM_T_carrier_us_rd_AXI_reg[24]_0 [11]),
        .R(SR));
  FDRE \read_reg_PWM_T_carrier_us_rd_AXI_reg[12] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(\read_reg_PWM_T_carrier_us_rd_AXI_reg[24]_1 [12]),
        .Q(\read_reg_PWM_T_carrier_us_rd_AXI_reg[24]_0 [12]),
        .R(SR));
  FDRE \read_reg_PWM_T_carrier_us_rd_AXI_reg[13] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(\read_reg_PWM_T_carrier_us_rd_AXI_reg[24]_1 [13]),
        .Q(\read_reg_PWM_T_carrier_us_rd_AXI_reg[24]_0 [13]),
        .R(SR));
  FDRE \read_reg_PWM_T_carrier_us_rd_AXI_reg[14] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(\read_reg_PWM_T_carrier_us_rd_AXI_reg[24]_1 [14]),
        .Q(\read_reg_PWM_T_carrier_us_rd_AXI_reg[24]_0 [14]),
        .R(SR));
  FDRE \read_reg_PWM_T_carrier_us_rd_AXI_reg[15] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(\read_reg_PWM_T_carrier_us_rd_AXI_reg[24]_1 [15]),
        .Q(\read_reg_PWM_T_carrier_us_rd_AXI_reg[24]_0 [15]),
        .R(SR));
  FDRE \read_reg_PWM_T_carrier_us_rd_AXI_reg[16] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(\read_reg_PWM_T_carrier_us_rd_AXI_reg[24]_1 [16]),
        .Q(\read_reg_PWM_T_carrier_us_rd_AXI_reg[24]_0 [16]),
        .R(SR));
  FDRE \read_reg_PWM_T_carrier_us_rd_AXI_reg[17] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(\read_reg_PWM_T_carrier_us_rd_AXI_reg[24]_1 [17]),
        .Q(\read_reg_PWM_T_carrier_us_rd_AXI_reg[24]_0 [17]),
        .R(SR));
  FDRE \read_reg_PWM_T_carrier_us_rd_AXI_reg[18] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(\read_reg_PWM_T_carrier_us_rd_AXI_reg[24]_1 [18]),
        .Q(\read_reg_PWM_T_carrier_us_rd_AXI_reg[24]_0 [18]),
        .R(SR));
  FDRE \read_reg_PWM_T_carrier_us_rd_AXI_reg[19] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(\read_reg_PWM_T_carrier_us_rd_AXI_reg[24]_1 [19]),
        .Q(\read_reg_PWM_T_carrier_us_rd_AXI_reg[24]_0 [19]),
        .R(SR));
  FDRE \read_reg_PWM_T_carrier_us_rd_AXI_reg[1] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(\read_reg_PWM_T_carrier_us_rd_AXI_reg[24]_1 [1]),
        .Q(\read_reg_PWM_T_carrier_us_rd_AXI_reg[24]_0 [1]),
        .R(SR));
  FDRE \read_reg_PWM_T_carrier_us_rd_AXI_reg[20] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(\read_reg_PWM_T_carrier_us_rd_AXI_reg[24]_1 [20]),
        .Q(\read_reg_PWM_T_carrier_us_rd_AXI_reg[24]_0 [20]),
        .R(SR));
  FDRE \read_reg_PWM_T_carrier_us_rd_AXI_reg[21] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(\read_reg_PWM_T_carrier_us_rd_AXI_reg[24]_1 [21]),
        .Q(\read_reg_PWM_T_carrier_us_rd_AXI_reg[24]_0 [21]),
        .R(SR));
  FDRE \read_reg_PWM_T_carrier_us_rd_AXI_reg[22] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(\read_reg_PWM_T_carrier_us_rd_AXI_reg[24]_1 [22]),
        .Q(\read_reg_PWM_T_carrier_us_rd_AXI_reg[24]_0 [22]),
        .R(SR));
  FDRE \read_reg_PWM_T_carrier_us_rd_AXI_reg[23] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(\read_reg_PWM_T_carrier_us_rd_AXI_reg[24]_1 [23]),
        .Q(\read_reg_PWM_T_carrier_us_rd_AXI_reg[24]_0 [23]),
        .R(SR));
  FDRE \read_reg_PWM_T_carrier_us_rd_AXI_reg[24] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(\read_reg_PWM_T_carrier_us_rd_AXI_reg[24]_1 [24]),
        .Q(\read_reg_PWM_T_carrier_us_rd_AXI_reg[24]_0 [24]),
        .R(SR));
  FDRE \read_reg_PWM_T_carrier_us_rd_AXI_reg[2] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(\read_reg_PWM_T_carrier_us_rd_AXI_reg[24]_1 [2]),
        .Q(\read_reg_PWM_T_carrier_us_rd_AXI_reg[24]_0 [2]),
        .R(SR));
  FDRE \read_reg_PWM_T_carrier_us_rd_AXI_reg[3] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(\read_reg_PWM_T_carrier_us_rd_AXI_reg[24]_1 [3]),
        .Q(\read_reg_PWM_T_carrier_us_rd_AXI_reg[24]_0 [3]),
        .R(SR));
  FDRE \read_reg_PWM_T_carrier_us_rd_AXI_reg[4] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(\read_reg_PWM_T_carrier_us_rd_AXI_reg[24]_1 [4]),
        .Q(\read_reg_PWM_T_carrier_us_rd_AXI_reg[24]_0 [4]),
        .R(SR));
  FDRE \read_reg_PWM_T_carrier_us_rd_AXI_reg[5] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(\read_reg_PWM_T_carrier_us_rd_AXI_reg[24]_1 [5]),
        .Q(\read_reg_PWM_T_carrier_us_rd_AXI_reg[24]_0 [5]),
        .R(SR));
  FDRE \read_reg_PWM_T_carrier_us_rd_AXI_reg[6] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(\read_reg_PWM_T_carrier_us_rd_AXI_reg[24]_1 [6]),
        .Q(\read_reg_PWM_T_carrier_us_rd_AXI_reg[24]_0 [6]),
        .R(SR));
  FDRE \read_reg_PWM_T_carrier_us_rd_AXI_reg[7] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(\read_reg_PWM_T_carrier_us_rd_AXI_reg[24]_1 [7]),
        .Q(\read_reg_PWM_T_carrier_us_rd_AXI_reg[24]_0 [7]),
        .R(SR));
  FDRE \read_reg_PWM_T_carrier_us_rd_AXI_reg[8] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(\read_reg_PWM_T_carrier_us_rd_AXI_reg[24]_1 [8]),
        .Q(\read_reg_PWM_T_carrier_us_rd_AXI_reg[24]_0 [8]),
        .R(SR));
  FDRE \read_reg_PWM_T_carrier_us_rd_AXI_reg[9] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(\read_reg_PWM_T_carrier_us_rd_AXI_reg[24]_1 [9]),
        .Q(\read_reg_PWM_T_carrier_us_rd_AXI_reg[24]_0 [9]),
        .R(SR));
  FDRE read_reg_PWM_en_rd_AXI_reg
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(PWM_en_rd_AXI_sig),
        .Q(read_reg_PWM_en_rd_AXI),
        .R(SR));
  FDRE \read_reg_PWM_f_carrier_kHz_rd_AXI_reg[0] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(D[0]),
        .Q(\read_reg_PWM_f_carrier_kHz_rd_AXI_reg[24]_0 [0]),
        .R(SR));
  FDRE \read_reg_PWM_f_carrier_kHz_rd_AXI_reg[10] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(D[10]),
        .Q(\read_reg_PWM_f_carrier_kHz_rd_AXI_reg[24]_0 [10]),
        .R(SR));
  FDRE \read_reg_PWM_f_carrier_kHz_rd_AXI_reg[11] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(D[11]),
        .Q(\read_reg_PWM_f_carrier_kHz_rd_AXI_reg[24]_0 [11]),
        .R(SR));
  FDRE \read_reg_PWM_f_carrier_kHz_rd_AXI_reg[12] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(D[12]),
        .Q(\read_reg_PWM_f_carrier_kHz_rd_AXI_reg[24]_0 [12]),
        .R(SR));
  FDRE \read_reg_PWM_f_carrier_kHz_rd_AXI_reg[13] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(D[13]),
        .Q(\read_reg_PWM_f_carrier_kHz_rd_AXI_reg[24]_0 [13]),
        .R(SR));
  FDRE \read_reg_PWM_f_carrier_kHz_rd_AXI_reg[14] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(D[14]),
        .Q(\read_reg_PWM_f_carrier_kHz_rd_AXI_reg[24]_0 [14]),
        .R(SR));
  FDRE \read_reg_PWM_f_carrier_kHz_rd_AXI_reg[15] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(D[15]),
        .Q(\read_reg_PWM_f_carrier_kHz_rd_AXI_reg[24]_0 [15]),
        .R(SR));
  FDRE \read_reg_PWM_f_carrier_kHz_rd_AXI_reg[16] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(D[16]),
        .Q(\read_reg_PWM_f_carrier_kHz_rd_AXI_reg[24]_0 [16]),
        .R(SR));
  FDRE \read_reg_PWM_f_carrier_kHz_rd_AXI_reg[17] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(D[17]),
        .Q(\read_reg_PWM_f_carrier_kHz_rd_AXI_reg[24]_0 [17]),
        .R(SR));
  FDRE \read_reg_PWM_f_carrier_kHz_rd_AXI_reg[18] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(D[18]),
        .Q(\read_reg_PWM_f_carrier_kHz_rd_AXI_reg[24]_0 [18]),
        .R(SR));
  FDRE \read_reg_PWM_f_carrier_kHz_rd_AXI_reg[19] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(D[19]),
        .Q(\read_reg_PWM_f_carrier_kHz_rd_AXI_reg[24]_0 [19]),
        .R(SR));
  FDRE \read_reg_PWM_f_carrier_kHz_rd_AXI_reg[1] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(D[1]),
        .Q(\read_reg_PWM_f_carrier_kHz_rd_AXI_reg[24]_0 [1]),
        .R(SR));
  FDRE \read_reg_PWM_f_carrier_kHz_rd_AXI_reg[20] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(D[20]),
        .Q(\read_reg_PWM_f_carrier_kHz_rd_AXI_reg[24]_0 [20]),
        .R(SR));
  FDRE \read_reg_PWM_f_carrier_kHz_rd_AXI_reg[21] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(D[21]),
        .Q(\read_reg_PWM_f_carrier_kHz_rd_AXI_reg[24]_0 [21]),
        .R(SR));
  FDRE \read_reg_PWM_f_carrier_kHz_rd_AXI_reg[22] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(D[22]),
        .Q(\read_reg_PWM_f_carrier_kHz_rd_AXI_reg[24]_0 [22]),
        .R(SR));
  FDRE \read_reg_PWM_f_carrier_kHz_rd_AXI_reg[23] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(D[23]),
        .Q(\read_reg_PWM_f_carrier_kHz_rd_AXI_reg[24]_0 [23]),
        .R(SR));
  FDRE \read_reg_PWM_f_carrier_kHz_rd_AXI_reg[24] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(D[24]),
        .Q(\read_reg_PWM_f_carrier_kHz_rd_AXI_reg[24]_0 [24]),
        .R(SR));
  FDRE \read_reg_PWM_f_carrier_kHz_rd_AXI_reg[2] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(D[2]),
        .Q(\read_reg_PWM_f_carrier_kHz_rd_AXI_reg[24]_0 [2]),
        .R(SR));
  FDRE \read_reg_PWM_f_carrier_kHz_rd_AXI_reg[3] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(D[3]),
        .Q(\read_reg_PWM_f_carrier_kHz_rd_AXI_reg[24]_0 [3]),
        .R(SR));
  FDRE \read_reg_PWM_f_carrier_kHz_rd_AXI_reg[4] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(D[4]),
        .Q(\read_reg_PWM_f_carrier_kHz_rd_AXI_reg[24]_0 [4]),
        .R(SR));
  FDRE \read_reg_PWM_f_carrier_kHz_rd_AXI_reg[5] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(D[5]),
        .Q(\read_reg_PWM_f_carrier_kHz_rd_AXI_reg[24]_0 [5]),
        .R(SR));
  FDRE \read_reg_PWM_f_carrier_kHz_rd_AXI_reg[6] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(D[6]),
        .Q(\read_reg_PWM_f_carrier_kHz_rd_AXI_reg[24]_0 [6]),
        .R(SR));
  FDRE \read_reg_PWM_f_carrier_kHz_rd_AXI_reg[7] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(D[7]),
        .Q(\read_reg_PWM_f_carrier_kHz_rd_AXI_reg[24]_0 [7]),
        .R(SR));
  FDRE \read_reg_PWM_f_carrier_kHz_rd_AXI_reg[8] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(D[8]),
        .Q(\read_reg_PWM_f_carrier_kHz_rd_AXI_reg[24]_0 [8]),
        .R(SR));
  FDRE \read_reg_PWM_f_carrier_kHz_rd_AXI_reg[9] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(D[9]),
        .Q(\read_reg_PWM_f_carrier_kHz_rd_AXI_reg[24]_0 [9]),
        .R(SR));
  FDRE \read_reg_PWM_min_pulse_width_rd_AXI_reg[0] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(\read_reg_PWM_min_pulse_width_rd_AXI_reg[17]_1 [0]),
        .Q(\read_reg_PWM_min_pulse_width_rd_AXI_reg[17]_0 [0]),
        .R(SR));
  FDRE \read_reg_PWM_min_pulse_width_rd_AXI_reg[10] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(\read_reg_PWM_min_pulse_width_rd_AXI_reg[17]_1 [10]),
        .Q(\read_reg_PWM_min_pulse_width_rd_AXI_reg[17]_0 [10]),
        .R(SR));
  FDRE \read_reg_PWM_min_pulse_width_rd_AXI_reg[11] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(\read_reg_PWM_min_pulse_width_rd_AXI_reg[17]_1 [11]),
        .Q(\read_reg_PWM_min_pulse_width_rd_AXI_reg[17]_0 [11]),
        .R(SR));
  FDRE \read_reg_PWM_min_pulse_width_rd_AXI_reg[12] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(\read_reg_PWM_min_pulse_width_rd_AXI_reg[17]_1 [12]),
        .Q(\read_reg_PWM_min_pulse_width_rd_AXI_reg[17]_0 [12]),
        .R(SR));
  FDRE \read_reg_PWM_min_pulse_width_rd_AXI_reg[13] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(\read_reg_PWM_min_pulse_width_rd_AXI_reg[17]_1 [13]),
        .Q(\read_reg_PWM_min_pulse_width_rd_AXI_reg[17]_0 [13]),
        .R(SR));
  FDRE \read_reg_PWM_min_pulse_width_rd_AXI_reg[14] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(\read_reg_PWM_min_pulse_width_rd_AXI_reg[17]_1 [14]),
        .Q(\read_reg_PWM_min_pulse_width_rd_AXI_reg[17]_0 [14]),
        .R(SR));
  FDRE \read_reg_PWM_min_pulse_width_rd_AXI_reg[15] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(\read_reg_PWM_min_pulse_width_rd_AXI_reg[17]_1 [15]),
        .Q(\read_reg_PWM_min_pulse_width_rd_AXI_reg[17]_0 [15]),
        .R(SR));
  FDRE \read_reg_PWM_min_pulse_width_rd_AXI_reg[16] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(\read_reg_PWM_min_pulse_width_rd_AXI_reg[17]_1 [16]),
        .Q(\read_reg_PWM_min_pulse_width_rd_AXI_reg[17]_0 [16]),
        .R(SR));
  FDRE \read_reg_PWM_min_pulse_width_rd_AXI_reg[17] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(\read_reg_PWM_min_pulse_width_rd_AXI_reg[17]_1 [17]),
        .Q(\read_reg_PWM_min_pulse_width_rd_AXI_reg[17]_0 [17]),
        .R(SR));
  FDRE \read_reg_PWM_min_pulse_width_rd_AXI_reg[1] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(\read_reg_PWM_min_pulse_width_rd_AXI_reg[17]_1 [1]),
        .Q(\read_reg_PWM_min_pulse_width_rd_AXI_reg[17]_0 [1]),
        .R(SR));
  FDRE \read_reg_PWM_min_pulse_width_rd_AXI_reg[2] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(\read_reg_PWM_min_pulse_width_rd_AXI_reg[17]_1 [2]),
        .Q(\read_reg_PWM_min_pulse_width_rd_AXI_reg[17]_0 [2]),
        .R(SR));
  FDRE \read_reg_PWM_min_pulse_width_rd_AXI_reg[3] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(\read_reg_PWM_min_pulse_width_rd_AXI_reg[17]_1 [3]),
        .Q(\read_reg_PWM_min_pulse_width_rd_AXI_reg[17]_0 [3]),
        .R(SR));
  FDRE \read_reg_PWM_min_pulse_width_rd_AXI_reg[4] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(\read_reg_PWM_min_pulse_width_rd_AXI_reg[17]_1 [4]),
        .Q(\read_reg_PWM_min_pulse_width_rd_AXI_reg[17]_0 [4]),
        .R(SR));
  FDRE \read_reg_PWM_min_pulse_width_rd_AXI_reg[5] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(\read_reg_PWM_min_pulse_width_rd_AXI_reg[17]_1 [5]),
        .Q(\read_reg_PWM_min_pulse_width_rd_AXI_reg[17]_0 [5]),
        .R(SR));
  FDRE \read_reg_PWM_min_pulse_width_rd_AXI_reg[6] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(\read_reg_PWM_min_pulse_width_rd_AXI_reg[17]_1 [6]),
        .Q(\read_reg_PWM_min_pulse_width_rd_AXI_reg[17]_0 [6]),
        .R(SR));
  FDRE \read_reg_PWM_min_pulse_width_rd_AXI_reg[7] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(\read_reg_PWM_min_pulse_width_rd_AXI_reg[17]_1 [7]),
        .Q(\read_reg_PWM_min_pulse_width_rd_AXI_reg[17]_0 [7]),
        .R(SR));
  FDRE \read_reg_PWM_min_pulse_width_rd_AXI_reg[8] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(\read_reg_PWM_min_pulse_width_rd_AXI_reg[17]_1 [8]),
        .Q(\read_reg_PWM_min_pulse_width_rd_AXI_reg[17]_0 [8]),
        .R(SR));
  FDRE \read_reg_PWM_min_pulse_width_rd_AXI_reg[9] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(\read_reg_PWM_min_pulse_width_rd_AXI_reg[17]_1 [9]),
        .Q(\read_reg_PWM_min_pulse_width_rd_AXI_reg[17]_0 [9]),
        .R(SR));
  FDRE \read_reg_ip_timestamp_reg[30] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(1'b1),
        .Q(read_reg_ip_timestamp),
        .R(SR));
  FDRE \write_reg_Mode_AXI_reg[0] 
       (.C(AXI4_Lite_ACLK),
        .CE(E),
        .D(Q[0]),
        .Q(\write_reg_Mode_AXI_reg[1]_0 [0]),
        .R(SR));
  FDRE \write_reg_Mode_AXI_reg[1] 
       (.C(AXI4_Lite_ACLK),
        .CE(E),
        .D(Q[1]),
        .Q(\write_reg_Mode_AXI_reg[1]_0 [1]),
        .R(SR));
  FDRE write_reg_PWM_en_AXI_reg
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(write_reg_PWM_en_AXI_reg_0),
        .Q(write_PWM_en_AXI),
        .R(SR));
  FDRE \write_reg_PWM_min_pulse_width_AXI_reg[0] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_PWM_min_pulse_width_AXI_reg[17]_1 ),
        .D(Q[0]),
        .Q(\write_reg_PWM_min_pulse_width_AXI_reg[17]_0 [0]),
        .R(SR));
  FDRE \write_reg_PWM_min_pulse_width_AXI_reg[10] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_PWM_min_pulse_width_AXI_reg[17]_1 ),
        .D(Q[10]),
        .Q(\write_reg_PWM_min_pulse_width_AXI_reg[17]_0 [10]),
        .R(SR));
  FDRE \write_reg_PWM_min_pulse_width_AXI_reg[11] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_PWM_min_pulse_width_AXI_reg[17]_1 ),
        .D(Q[11]),
        .Q(\write_reg_PWM_min_pulse_width_AXI_reg[17]_0 [11]),
        .R(SR));
  FDRE \write_reg_PWM_min_pulse_width_AXI_reg[12] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_PWM_min_pulse_width_AXI_reg[17]_1 ),
        .D(Q[12]),
        .Q(\write_reg_PWM_min_pulse_width_AXI_reg[17]_0 [12]),
        .R(SR));
  FDRE \write_reg_PWM_min_pulse_width_AXI_reg[13] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_PWM_min_pulse_width_AXI_reg[17]_1 ),
        .D(Q[13]),
        .Q(\write_reg_PWM_min_pulse_width_AXI_reg[17]_0 [13]),
        .R(SR));
  FDRE \write_reg_PWM_min_pulse_width_AXI_reg[14] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_PWM_min_pulse_width_AXI_reg[17]_1 ),
        .D(Q[14]),
        .Q(\write_reg_PWM_min_pulse_width_AXI_reg[17]_0 [14]),
        .R(SR));
  FDRE \write_reg_PWM_min_pulse_width_AXI_reg[15] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_PWM_min_pulse_width_AXI_reg[17]_1 ),
        .D(Q[15]),
        .Q(\write_reg_PWM_min_pulse_width_AXI_reg[17]_0 [15]),
        .R(SR));
  FDRE \write_reg_PWM_min_pulse_width_AXI_reg[16] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_PWM_min_pulse_width_AXI_reg[17]_1 ),
        .D(Q[16]),
        .Q(\write_reg_PWM_min_pulse_width_AXI_reg[17]_0 [16]),
        .R(SR));
  FDRE \write_reg_PWM_min_pulse_width_AXI_reg[17] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_PWM_min_pulse_width_AXI_reg[17]_1 ),
        .D(Q[17]),
        .Q(\write_reg_PWM_min_pulse_width_AXI_reg[17]_0 [17]),
        .R(SR));
  FDRE \write_reg_PWM_min_pulse_width_AXI_reg[1] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_PWM_min_pulse_width_AXI_reg[17]_1 ),
        .D(Q[1]),
        .Q(\write_reg_PWM_min_pulse_width_AXI_reg[17]_0 [1]),
        .R(SR));
  FDRE \write_reg_PWM_min_pulse_width_AXI_reg[2] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_PWM_min_pulse_width_AXI_reg[17]_1 ),
        .D(Q[2]),
        .Q(\write_reg_PWM_min_pulse_width_AXI_reg[17]_0 [2]),
        .R(SR));
  FDRE \write_reg_PWM_min_pulse_width_AXI_reg[3] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_PWM_min_pulse_width_AXI_reg[17]_1 ),
        .D(Q[3]),
        .Q(\write_reg_PWM_min_pulse_width_AXI_reg[17]_0 [3]),
        .R(SR));
  FDRE \write_reg_PWM_min_pulse_width_AXI_reg[4] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_PWM_min_pulse_width_AXI_reg[17]_1 ),
        .D(Q[4]),
        .Q(\write_reg_PWM_min_pulse_width_AXI_reg[17]_0 [4]),
        .R(SR));
  FDRE \write_reg_PWM_min_pulse_width_AXI_reg[5] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_PWM_min_pulse_width_AXI_reg[17]_1 ),
        .D(Q[5]),
        .Q(\write_reg_PWM_min_pulse_width_AXI_reg[17]_0 [5]),
        .R(SR));
  FDRE \write_reg_PWM_min_pulse_width_AXI_reg[6] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_PWM_min_pulse_width_AXI_reg[17]_1 ),
        .D(Q[6]),
        .Q(\write_reg_PWM_min_pulse_width_AXI_reg[17]_0 [6]),
        .R(SR));
  FDRE \write_reg_PWM_min_pulse_width_AXI_reg[7] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_PWM_min_pulse_width_AXI_reg[17]_1 ),
        .D(Q[7]),
        .Q(\write_reg_PWM_min_pulse_width_AXI_reg[17]_0 [7]),
        .R(SR));
  FDRE \write_reg_PWM_min_pulse_width_AXI_reg[8] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_PWM_min_pulse_width_AXI_reg[17]_1 ),
        .D(Q[8]),
        .Q(\write_reg_PWM_min_pulse_width_AXI_reg[17]_0 [8]),
        .R(SR));
  FDRE \write_reg_PWM_min_pulse_width_AXI_reg[9] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_PWM_min_pulse_width_AXI_reg[17]_1 ),
        .D(Q[9]),
        .Q(\write_reg_PWM_min_pulse_width_AXI_reg[17]_0 [9]),
        .R(SR));
  FDRE \write_reg_Scal_T_carrier_AXI_reg[0] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_Scal_T_carrier_AXI_reg[24]_1 ),
        .D(Q[0]),
        .Q(\write_reg_Scal_T_carrier_AXI_reg[24]_0 [0]),
        .R(SR));
  FDRE \write_reg_Scal_T_carrier_AXI_reg[10] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_Scal_T_carrier_AXI_reg[24]_1 ),
        .D(Q[10]),
        .Q(\write_reg_Scal_T_carrier_AXI_reg[24]_0 [10]),
        .R(SR));
  FDRE \write_reg_Scal_T_carrier_AXI_reg[11] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_Scal_T_carrier_AXI_reg[24]_1 ),
        .D(Q[11]),
        .Q(\write_reg_Scal_T_carrier_AXI_reg[24]_0 [11]),
        .R(SR));
  FDRE \write_reg_Scal_T_carrier_AXI_reg[12] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_Scal_T_carrier_AXI_reg[24]_1 ),
        .D(Q[12]),
        .Q(\write_reg_Scal_T_carrier_AXI_reg[24]_0 [12]),
        .R(SR));
  FDRE \write_reg_Scal_T_carrier_AXI_reg[13] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_Scal_T_carrier_AXI_reg[24]_1 ),
        .D(Q[13]),
        .Q(\write_reg_Scal_T_carrier_AXI_reg[24]_0 [13]),
        .R(SR));
  FDRE \write_reg_Scal_T_carrier_AXI_reg[14] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_Scal_T_carrier_AXI_reg[24]_1 ),
        .D(Q[14]),
        .Q(\write_reg_Scal_T_carrier_AXI_reg[24]_0 [14]),
        .R(SR));
  FDRE \write_reg_Scal_T_carrier_AXI_reg[15] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_Scal_T_carrier_AXI_reg[24]_1 ),
        .D(Q[15]),
        .Q(\write_reg_Scal_T_carrier_AXI_reg[24]_0 [15]),
        .R(SR));
  FDRE \write_reg_Scal_T_carrier_AXI_reg[16] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_Scal_T_carrier_AXI_reg[24]_1 ),
        .D(Q[16]),
        .Q(\write_reg_Scal_T_carrier_AXI_reg[24]_0 [16]),
        .R(SR));
  FDRE \write_reg_Scal_T_carrier_AXI_reg[17] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_Scal_T_carrier_AXI_reg[24]_1 ),
        .D(Q[17]),
        .Q(\write_reg_Scal_T_carrier_AXI_reg[24]_0 [17]),
        .R(SR));
  FDRE \write_reg_Scal_T_carrier_AXI_reg[18] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_Scal_T_carrier_AXI_reg[24]_1 ),
        .D(Q[18]),
        .Q(\write_reg_Scal_T_carrier_AXI_reg[24]_0 [18]),
        .R(SR));
  FDRE \write_reg_Scal_T_carrier_AXI_reg[19] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_Scal_T_carrier_AXI_reg[24]_1 ),
        .D(Q[19]),
        .Q(\write_reg_Scal_T_carrier_AXI_reg[24]_0 [19]),
        .R(SR));
  FDRE \write_reg_Scal_T_carrier_AXI_reg[1] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_Scal_T_carrier_AXI_reg[24]_1 ),
        .D(Q[1]),
        .Q(\write_reg_Scal_T_carrier_AXI_reg[24]_0 [1]),
        .R(SR));
  FDRE \write_reg_Scal_T_carrier_AXI_reg[20] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_Scal_T_carrier_AXI_reg[24]_1 ),
        .D(Q[20]),
        .Q(\write_reg_Scal_T_carrier_AXI_reg[24]_0 [20]),
        .R(SR));
  FDRE \write_reg_Scal_T_carrier_AXI_reg[21] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_Scal_T_carrier_AXI_reg[24]_1 ),
        .D(Q[21]),
        .Q(\write_reg_Scal_T_carrier_AXI_reg[24]_0 [21]),
        .R(SR));
  FDRE \write_reg_Scal_T_carrier_AXI_reg[22] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_Scal_T_carrier_AXI_reg[24]_1 ),
        .D(Q[22]),
        .Q(\write_reg_Scal_T_carrier_AXI_reg[24]_0 [22]),
        .R(SR));
  FDRE \write_reg_Scal_T_carrier_AXI_reg[23] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_Scal_T_carrier_AXI_reg[24]_1 ),
        .D(Q[23]),
        .Q(\write_reg_Scal_T_carrier_AXI_reg[24]_0 [23]),
        .R(SR));
  FDRE \write_reg_Scal_T_carrier_AXI_reg[24] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_Scal_T_carrier_AXI_reg[24]_1 ),
        .D(Q[24]),
        .Q(\write_reg_Scal_T_carrier_AXI_reg[24]_0 [24]),
        .R(SR));
  FDRE \write_reg_Scal_T_carrier_AXI_reg[2] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_Scal_T_carrier_AXI_reg[24]_1 ),
        .D(Q[2]),
        .Q(\write_reg_Scal_T_carrier_AXI_reg[24]_0 [2]),
        .R(SR));
  FDRE \write_reg_Scal_T_carrier_AXI_reg[3] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_Scal_T_carrier_AXI_reg[24]_1 ),
        .D(Q[3]),
        .Q(\write_reg_Scal_T_carrier_AXI_reg[24]_0 [3]),
        .R(SR));
  FDRE \write_reg_Scal_T_carrier_AXI_reg[4] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_Scal_T_carrier_AXI_reg[24]_1 ),
        .D(Q[4]),
        .Q(\write_reg_Scal_T_carrier_AXI_reg[24]_0 [4]),
        .R(SR));
  FDRE \write_reg_Scal_T_carrier_AXI_reg[5] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_Scal_T_carrier_AXI_reg[24]_1 ),
        .D(Q[5]),
        .Q(\write_reg_Scal_T_carrier_AXI_reg[24]_0 [5]),
        .R(SR));
  FDRE \write_reg_Scal_T_carrier_AXI_reg[6] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_Scal_T_carrier_AXI_reg[24]_1 ),
        .D(Q[6]),
        .Q(\write_reg_Scal_T_carrier_AXI_reg[24]_0 [6]),
        .R(SR));
  FDRE \write_reg_Scal_T_carrier_AXI_reg[7] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_Scal_T_carrier_AXI_reg[24]_1 ),
        .D(Q[7]),
        .Q(\write_reg_Scal_T_carrier_AXI_reg[24]_0 [7]),
        .R(SR));
  FDRE \write_reg_Scal_T_carrier_AXI_reg[8] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_Scal_T_carrier_AXI_reg[24]_1 ),
        .D(Q[8]),
        .Q(\write_reg_Scal_T_carrier_AXI_reg[24]_0 [8]),
        .R(SR));
  FDRE \write_reg_Scal_T_carrier_AXI_reg[9] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_Scal_T_carrier_AXI_reg[24]_1 ),
        .D(Q[9]),
        .Q(\write_reg_Scal_T_carrier_AXI_reg[24]_0 [9]),
        .R(SR));
  FDRE \write_reg_Scal_f_carrier_AXI_reg[0] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_Scal_f_carrier_AXI_reg[24]_1 ),
        .D(Q[0]),
        .Q(\write_reg_Scal_f_carrier_AXI_reg[24]_0 [0]),
        .R(SR));
  FDRE \write_reg_Scal_f_carrier_AXI_reg[10] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_Scal_f_carrier_AXI_reg[24]_1 ),
        .D(Q[10]),
        .Q(\write_reg_Scal_f_carrier_AXI_reg[24]_0 [10]),
        .R(SR));
  FDRE \write_reg_Scal_f_carrier_AXI_reg[11] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_Scal_f_carrier_AXI_reg[24]_1 ),
        .D(Q[11]),
        .Q(\write_reg_Scal_f_carrier_AXI_reg[24]_0 [11]),
        .R(SR));
  FDRE \write_reg_Scal_f_carrier_AXI_reg[12] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_Scal_f_carrier_AXI_reg[24]_1 ),
        .D(Q[12]),
        .Q(\write_reg_Scal_f_carrier_AXI_reg[24]_0 [12]),
        .R(SR));
  FDRE \write_reg_Scal_f_carrier_AXI_reg[13] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_Scal_f_carrier_AXI_reg[24]_1 ),
        .D(Q[13]),
        .Q(\write_reg_Scal_f_carrier_AXI_reg[24]_0 [13]),
        .R(SR));
  FDRE \write_reg_Scal_f_carrier_AXI_reg[14] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_Scal_f_carrier_AXI_reg[24]_1 ),
        .D(Q[14]),
        .Q(\write_reg_Scal_f_carrier_AXI_reg[24]_0 [14]),
        .R(SR));
  FDRE \write_reg_Scal_f_carrier_AXI_reg[15] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_Scal_f_carrier_AXI_reg[24]_1 ),
        .D(Q[15]),
        .Q(\write_reg_Scal_f_carrier_AXI_reg[24]_0 [15]),
        .R(SR));
  FDRE \write_reg_Scal_f_carrier_AXI_reg[16] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_Scal_f_carrier_AXI_reg[24]_1 ),
        .D(Q[16]),
        .Q(\write_reg_Scal_f_carrier_AXI_reg[24]_0 [16]),
        .R(SR));
  FDRE \write_reg_Scal_f_carrier_AXI_reg[17] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_Scal_f_carrier_AXI_reg[24]_1 ),
        .D(Q[17]),
        .Q(\write_reg_Scal_f_carrier_AXI_reg[24]_0 [17]),
        .R(SR));
  FDRE \write_reg_Scal_f_carrier_AXI_reg[18] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_Scal_f_carrier_AXI_reg[24]_1 ),
        .D(Q[18]),
        .Q(\write_reg_Scal_f_carrier_AXI_reg[24]_0 [18]),
        .R(SR));
  FDRE \write_reg_Scal_f_carrier_AXI_reg[19] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_Scal_f_carrier_AXI_reg[24]_1 ),
        .D(Q[19]),
        .Q(\write_reg_Scal_f_carrier_AXI_reg[24]_0 [19]),
        .R(SR));
  FDRE \write_reg_Scal_f_carrier_AXI_reg[1] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_Scal_f_carrier_AXI_reg[24]_1 ),
        .D(Q[1]),
        .Q(\write_reg_Scal_f_carrier_AXI_reg[24]_0 [1]),
        .R(SR));
  FDRE \write_reg_Scal_f_carrier_AXI_reg[20] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_Scal_f_carrier_AXI_reg[24]_1 ),
        .D(Q[20]),
        .Q(\write_reg_Scal_f_carrier_AXI_reg[24]_0 [20]),
        .R(SR));
  FDRE \write_reg_Scal_f_carrier_AXI_reg[21] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_Scal_f_carrier_AXI_reg[24]_1 ),
        .D(Q[21]),
        .Q(\write_reg_Scal_f_carrier_AXI_reg[24]_0 [21]),
        .R(SR));
  FDRE \write_reg_Scal_f_carrier_AXI_reg[22] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_Scal_f_carrier_AXI_reg[24]_1 ),
        .D(Q[22]),
        .Q(\write_reg_Scal_f_carrier_AXI_reg[24]_0 [22]),
        .R(SR));
  FDRE \write_reg_Scal_f_carrier_AXI_reg[23] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_Scal_f_carrier_AXI_reg[24]_1 ),
        .D(Q[23]),
        .Q(\write_reg_Scal_f_carrier_AXI_reg[24]_0 [23]),
        .R(SR));
  FDRE \write_reg_Scal_f_carrier_AXI_reg[24] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_Scal_f_carrier_AXI_reg[24]_1 ),
        .D(Q[24]),
        .Q(\write_reg_Scal_f_carrier_AXI_reg[24]_0 [24]),
        .R(SR));
  FDRE \write_reg_Scal_f_carrier_AXI_reg[2] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_Scal_f_carrier_AXI_reg[24]_1 ),
        .D(Q[2]),
        .Q(\write_reg_Scal_f_carrier_AXI_reg[24]_0 [2]),
        .R(SR));
  FDRE \write_reg_Scal_f_carrier_AXI_reg[3] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_Scal_f_carrier_AXI_reg[24]_1 ),
        .D(Q[3]),
        .Q(\write_reg_Scal_f_carrier_AXI_reg[24]_0 [3]),
        .R(SR));
  FDRE \write_reg_Scal_f_carrier_AXI_reg[4] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_Scal_f_carrier_AXI_reg[24]_1 ),
        .D(Q[4]),
        .Q(\write_reg_Scal_f_carrier_AXI_reg[24]_0 [4]),
        .R(SR));
  FDRE \write_reg_Scal_f_carrier_AXI_reg[5] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_Scal_f_carrier_AXI_reg[24]_1 ),
        .D(Q[5]),
        .Q(\write_reg_Scal_f_carrier_AXI_reg[24]_0 [5]),
        .R(SR));
  FDRE \write_reg_Scal_f_carrier_AXI_reg[6] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_Scal_f_carrier_AXI_reg[24]_1 ),
        .D(Q[6]),
        .Q(\write_reg_Scal_f_carrier_AXI_reg[24]_0 [6]),
        .R(SR));
  FDRE \write_reg_Scal_f_carrier_AXI_reg[7] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_Scal_f_carrier_AXI_reg[24]_1 ),
        .D(Q[7]),
        .Q(\write_reg_Scal_f_carrier_AXI_reg[24]_0 [7]),
        .R(SR));
  FDRE \write_reg_Scal_f_carrier_AXI_reg[8] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_Scal_f_carrier_AXI_reg[24]_1 ),
        .D(Q[8]),
        .Q(\write_reg_Scal_f_carrier_AXI_reg[24]_0 [8]),
        .R(SR));
  FDRE \write_reg_Scal_f_carrier_AXI_reg[9] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_Scal_f_carrier_AXI_reg[24]_1 ),
        .D(Q[9]),
        .Q(\write_reg_Scal_f_carrier_AXI_reg[24]_0 [9]),
        .R(SR));
  FDRE \write_reg_TriState_HB1_AXI_reg[0] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_TriState_HB1_AXI_reg[1]_1 ),
        .D(Q[0]),
        .Q(\write_reg_TriState_HB1_AXI_reg[1]_0 [0]),
        .R(SR));
  FDRE \write_reg_TriState_HB1_AXI_reg[1] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_TriState_HB1_AXI_reg[1]_1 ),
        .D(Q[1]),
        .Q(\write_reg_TriState_HB1_AXI_reg[1]_0 [1]),
        .R(SR));
  FDRE \write_reg_TriState_HB2_AXI_reg[0] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_TriState_HB2_AXI_reg[1]_1 ),
        .D(Q[0]),
        .Q(\write_reg_TriState_HB2_AXI_reg[1]_0 [0]),
        .R(SR));
  FDRE \write_reg_TriState_HB2_AXI_reg[1] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_TriState_HB2_AXI_reg[1]_1 ),
        .D(Q[1]),
        .Q(\write_reg_TriState_HB2_AXI_reg[1]_0 [1]),
        .R(SR));
  FDRE \write_reg_TriState_HB3_AXI_reg[0] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_TriState_HB3_AXI_reg[1]_1 ),
        .D(Q[0]),
        .Q(\write_reg_TriState_HB3_AXI_reg[1]_0 [0]),
        .R(SR));
  FDRE \write_reg_TriState_HB3_AXI_reg[1] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_TriState_HB3_AXI_reg[1]_1 ),
        .D(Q[1]),
        .Q(\write_reg_TriState_HB3_AXI_reg[1]_0 [1]),
        .R(SR));
  FDSE write_reg_axi_enable_reg
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(write_reg_axi_enable_reg_0),
        .Q(CEA1),
        .S(SR));
  FDRE \write_reg_m_u1_norm_AXI_reg[0] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_m_u1_norm_AXI_reg[13]_1 ),
        .D(Q[0]),
        .Q(\write_reg_m_u1_norm_AXI_reg[13]_0 [0]),
        .R(SR));
  FDRE \write_reg_m_u1_norm_AXI_reg[10] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_m_u1_norm_AXI_reg[13]_1 ),
        .D(Q[10]),
        .Q(\write_reg_m_u1_norm_AXI_reg[13]_0 [10]),
        .R(SR));
  FDRE \write_reg_m_u1_norm_AXI_reg[11] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_m_u1_norm_AXI_reg[13]_1 ),
        .D(Q[11]),
        .Q(\write_reg_m_u1_norm_AXI_reg[13]_0 [11]),
        .R(SR));
  FDRE \write_reg_m_u1_norm_AXI_reg[12] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_m_u1_norm_AXI_reg[13]_1 ),
        .D(Q[12]),
        .Q(\write_reg_m_u1_norm_AXI_reg[13]_0 [12]),
        .R(SR));
  FDRE \write_reg_m_u1_norm_AXI_reg[13] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_m_u1_norm_AXI_reg[13]_1 ),
        .D(Q[13]),
        .Q(\write_reg_m_u1_norm_AXI_reg[13]_0 [13]),
        .R(SR));
  FDRE \write_reg_m_u1_norm_AXI_reg[1] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_m_u1_norm_AXI_reg[13]_1 ),
        .D(Q[1]),
        .Q(\write_reg_m_u1_norm_AXI_reg[13]_0 [1]),
        .R(SR));
  FDRE \write_reg_m_u1_norm_AXI_reg[2] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_m_u1_norm_AXI_reg[13]_1 ),
        .D(Q[2]),
        .Q(\write_reg_m_u1_norm_AXI_reg[13]_0 [2]),
        .R(SR));
  FDRE \write_reg_m_u1_norm_AXI_reg[3] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_m_u1_norm_AXI_reg[13]_1 ),
        .D(Q[3]),
        .Q(\write_reg_m_u1_norm_AXI_reg[13]_0 [3]),
        .R(SR));
  FDRE \write_reg_m_u1_norm_AXI_reg[4] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_m_u1_norm_AXI_reg[13]_1 ),
        .D(Q[4]),
        .Q(\write_reg_m_u1_norm_AXI_reg[13]_0 [4]),
        .R(SR));
  FDRE \write_reg_m_u1_norm_AXI_reg[5] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_m_u1_norm_AXI_reg[13]_1 ),
        .D(Q[5]),
        .Q(\write_reg_m_u1_norm_AXI_reg[13]_0 [5]),
        .R(SR));
  FDRE \write_reg_m_u1_norm_AXI_reg[6] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_m_u1_norm_AXI_reg[13]_1 ),
        .D(Q[6]),
        .Q(\write_reg_m_u1_norm_AXI_reg[13]_0 [6]),
        .R(SR));
  FDRE \write_reg_m_u1_norm_AXI_reg[7] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_m_u1_norm_AXI_reg[13]_1 ),
        .D(Q[7]),
        .Q(\write_reg_m_u1_norm_AXI_reg[13]_0 [7]),
        .R(SR));
  FDRE \write_reg_m_u1_norm_AXI_reg[8] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_m_u1_norm_AXI_reg[13]_1 ),
        .D(Q[8]),
        .Q(\write_reg_m_u1_norm_AXI_reg[13]_0 [8]),
        .R(SR));
  FDRE \write_reg_m_u1_norm_AXI_reg[9] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_m_u1_norm_AXI_reg[13]_1 ),
        .D(Q[9]),
        .Q(\write_reg_m_u1_norm_AXI_reg[13]_0 [9]),
        .R(SR));
  FDRE \write_reg_m_u2_norm_AXI_reg[0] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_m_u2_norm_AXI_reg[13]_1 ),
        .D(Q[0]),
        .Q(\write_reg_m_u2_norm_AXI_reg[13]_0 [0]),
        .R(SR));
  FDRE \write_reg_m_u2_norm_AXI_reg[10] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_m_u2_norm_AXI_reg[13]_1 ),
        .D(Q[10]),
        .Q(\write_reg_m_u2_norm_AXI_reg[13]_0 [10]),
        .R(SR));
  FDRE \write_reg_m_u2_norm_AXI_reg[11] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_m_u2_norm_AXI_reg[13]_1 ),
        .D(Q[11]),
        .Q(\write_reg_m_u2_norm_AXI_reg[13]_0 [11]),
        .R(SR));
  FDRE \write_reg_m_u2_norm_AXI_reg[12] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_m_u2_norm_AXI_reg[13]_1 ),
        .D(Q[12]),
        .Q(\write_reg_m_u2_norm_AXI_reg[13]_0 [12]),
        .R(SR));
  FDRE \write_reg_m_u2_norm_AXI_reg[13] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_m_u2_norm_AXI_reg[13]_1 ),
        .D(Q[13]),
        .Q(\write_reg_m_u2_norm_AXI_reg[13]_0 [13]),
        .R(SR));
  FDRE \write_reg_m_u2_norm_AXI_reg[1] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_m_u2_norm_AXI_reg[13]_1 ),
        .D(Q[1]),
        .Q(\write_reg_m_u2_norm_AXI_reg[13]_0 [1]),
        .R(SR));
  FDRE \write_reg_m_u2_norm_AXI_reg[2] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_m_u2_norm_AXI_reg[13]_1 ),
        .D(Q[2]),
        .Q(\write_reg_m_u2_norm_AXI_reg[13]_0 [2]),
        .R(SR));
  FDRE \write_reg_m_u2_norm_AXI_reg[3] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_m_u2_norm_AXI_reg[13]_1 ),
        .D(Q[3]),
        .Q(\write_reg_m_u2_norm_AXI_reg[13]_0 [3]),
        .R(SR));
  FDRE \write_reg_m_u2_norm_AXI_reg[4] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_m_u2_norm_AXI_reg[13]_1 ),
        .D(Q[4]),
        .Q(\write_reg_m_u2_norm_AXI_reg[13]_0 [4]),
        .R(SR));
  FDRE \write_reg_m_u2_norm_AXI_reg[5] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_m_u2_norm_AXI_reg[13]_1 ),
        .D(Q[5]),
        .Q(\write_reg_m_u2_norm_AXI_reg[13]_0 [5]),
        .R(SR));
  FDRE \write_reg_m_u2_norm_AXI_reg[6] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_m_u2_norm_AXI_reg[13]_1 ),
        .D(Q[6]),
        .Q(\write_reg_m_u2_norm_AXI_reg[13]_0 [6]),
        .R(SR));
  FDRE \write_reg_m_u2_norm_AXI_reg[7] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_m_u2_norm_AXI_reg[13]_1 ),
        .D(Q[7]),
        .Q(\write_reg_m_u2_norm_AXI_reg[13]_0 [7]),
        .R(SR));
  FDRE \write_reg_m_u2_norm_AXI_reg[8] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_m_u2_norm_AXI_reg[13]_1 ),
        .D(Q[8]),
        .Q(\write_reg_m_u2_norm_AXI_reg[13]_0 [8]),
        .R(SR));
  FDRE \write_reg_m_u2_norm_AXI_reg[9] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_m_u2_norm_AXI_reg[13]_1 ),
        .D(Q[9]),
        .Q(\write_reg_m_u2_norm_AXI_reg[13]_0 [9]),
        .R(SR));
  FDRE \write_reg_m_u3_norm_AXI_reg[0] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_m_u3_norm_AXI_reg[13]_1 ),
        .D(Q[0]),
        .Q(\write_reg_m_u3_norm_AXI_reg[13]_0 [0]),
        .R(SR));
  FDRE \write_reg_m_u3_norm_AXI_reg[10] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_m_u3_norm_AXI_reg[13]_1 ),
        .D(Q[10]),
        .Q(\write_reg_m_u3_norm_AXI_reg[13]_0 [10]),
        .R(SR));
  FDRE \write_reg_m_u3_norm_AXI_reg[11] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_m_u3_norm_AXI_reg[13]_1 ),
        .D(Q[11]),
        .Q(\write_reg_m_u3_norm_AXI_reg[13]_0 [11]),
        .R(SR));
  FDRE \write_reg_m_u3_norm_AXI_reg[12] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_m_u3_norm_AXI_reg[13]_1 ),
        .D(Q[12]),
        .Q(\write_reg_m_u3_norm_AXI_reg[13]_0 [12]),
        .R(SR));
  FDRE \write_reg_m_u3_norm_AXI_reg[13] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_m_u3_norm_AXI_reg[13]_1 ),
        .D(Q[13]),
        .Q(\write_reg_m_u3_norm_AXI_reg[13]_0 [13]),
        .R(SR));
  FDRE \write_reg_m_u3_norm_AXI_reg[1] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_m_u3_norm_AXI_reg[13]_1 ),
        .D(Q[1]),
        .Q(\write_reg_m_u3_norm_AXI_reg[13]_0 [1]),
        .R(SR));
  FDRE \write_reg_m_u3_norm_AXI_reg[2] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_m_u3_norm_AXI_reg[13]_1 ),
        .D(Q[2]),
        .Q(\write_reg_m_u3_norm_AXI_reg[13]_0 [2]),
        .R(SR));
  FDRE \write_reg_m_u3_norm_AXI_reg[3] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_m_u3_norm_AXI_reg[13]_1 ),
        .D(Q[3]),
        .Q(\write_reg_m_u3_norm_AXI_reg[13]_0 [3]),
        .R(SR));
  FDRE \write_reg_m_u3_norm_AXI_reg[4] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_m_u3_norm_AXI_reg[13]_1 ),
        .D(Q[4]),
        .Q(\write_reg_m_u3_norm_AXI_reg[13]_0 [4]),
        .R(SR));
  FDRE \write_reg_m_u3_norm_AXI_reg[5] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_m_u3_norm_AXI_reg[13]_1 ),
        .D(Q[5]),
        .Q(\write_reg_m_u3_norm_AXI_reg[13]_0 [5]),
        .R(SR));
  FDRE \write_reg_m_u3_norm_AXI_reg[6] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_m_u3_norm_AXI_reg[13]_1 ),
        .D(Q[6]),
        .Q(\write_reg_m_u3_norm_AXI_reg[13]_0 [6]),
        .R(SR));
  FDRE \write_reg_m_u3_norm_AXI_reg[7] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_m_u3_norm_AXI_reg[13]_1 ),
        .D(Q[7]),
        .Q(\write_reg_m_u3_norm_AXI_reg[13]_0 [7]),
        .R(SR));
  FDRE \write_reg_m_u3_norm_AXI_reg[8] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_m_u3_norm_AXI_reg[13]_1 ),
        .D(Q[8]),
        .Q(\write_reg_m_u3_norm_AXI_reg[13]_0 [8]),
        .R(SR));
  FDRE \write_reg_m_u3_norm_AXI_reg[9] 
       (.C(AXI4_Lite_ACLK),
        .CE(\write_reg_m_u3_norm_AXI_reg[13]_1 ),
        .D(Q[9]),
        .Q(\write_reg_m_u3_norm_AXI_reg[13]_0 [9]),
        .R(SR));
endmodule

module zusys_PWM_and_SS_control_V_0_2_PWM_and_SS_control_V3_ip_axi_lite
   (FSM_sequential_axi_lite_rstate_reg,
    reset,
    CEA1,
    write_PWM_en_AXI,
    AXI4_Lite_ARREADY,
    Q,
    AXI4_Lite_AWREADY,
    CEB2,
    \write_reg_Mode_AXI_reg[1] ,
    \write_reg_Scal_f_carrier_AXI_reg[24] ,
    \write_reg_Scal_T_carrier_AXI_reg[24] ,
    \write_reg_PWM_min_pulse_width_AXI_reg[17] ,
    \write_reg_m_u1_norm_AXI_reg[13] ,
    \write_reg_m_u2_norm_AXI_reg[13] ,
    \write_reg_m_u3_norm_AXI_reg[13] ,
    \write_reg_TriState_HB1_AXI_reg[1] ,
    \write_reg_TriState_HB2_AXI_reg[1] ,
    \write_reg_TriState_HB3_AXI_reg[1] ,
    AXI4_Lite_RDATA,
    AXI4_Lite_ACLK,
    PWM_en_rd_AXI_sig,
    AXI4_Lite_ARVALID,
    AXI4_Lite_ARADDR,
    AXI4_Lite_RREADY,
    AXI4_Lite_AWVALID,
    AXI4_Lite_WVALID,
    AXI4_Lite_ARESETN,
    PWM_en_AXI_1,
    IPCORE_RESETN,
    AXI4_Lite_BREADY,
    AXI4_Lite_WSTRB,
    AXI4_Lite_AWADDR,
    AXI4_Lite_WDATA,
    D,
    \read_reg_PWM_T_carrier_us_rd_AXI_reg[24] ,
    \read_reg_PWM_min_pulse_width_rd_AXI_reg[17] ,
    \read_reg_Mode_rd_AXI_reg[1] );
  output FSM_sequential_axi_lite_rstate_reg;
  output reset;
  output CEA1;
  output write_PWM_en_AXI;
  output AXI4_Lite_ARREADY;
  output [1:0]Q;
  output AXI4_Lite_AWREADY;
  output CEB2;
  output [1:0]\write_reg_Mode_AXI_reg[1] ;
  output [24:0]\write_reg_Scal_f_carrier_AXI_reg[24] ;
  output [24:0]\write_reg_Scal_T_carrier_AXI_reg[24] ;
  output [17:0]\write_reg_PWM_min_pulse_width_AXI_reg[17] ;
  output [13:0]\write_reg_m_u1_norm_AXI_reg[13] ;
  output [13:0]\write_reg_m_u2_norm_AXI_reg[13] ;
  output [13:0]\write_reg_m_u3_norm_AXI_reg[13] ;
  output [1:0]\write_reg_TriState_HB1_AXI_reg[1] ;
  output [1:0]\write_reg_TriState_HB2_AXI_reg[1] ;
  output [1:0]\write_reg_TriState_HB3_AXI_reg[1] ;
  output [26:0]AXI4_Lite_RDATA;
  input AXI4_Lite_ACLK;
  input PWM_en_rd_AXI_sig;
  input AXI4_Lite_ARVALID;
  input [13:0]AXI4_Lite_ARADDR;
  input AXI4_Lite_RREADY;
  input AXI4_Lite_AWVALID;
  input AXI4_Lite_WVALID;
  input AXI4_Lite_ARESETN;
  input PWM_en_AXI_1;
  input IPCORE_RESETN;
  input AXI4_Lite_BREADY;
  input [3:0]AXI4_Lite_WSTRB;
  input [13:0]AXI4_Lite_AWADDR;
  input [24:0]AXI4_Lite_WDATA;
  input [24:0]D;
  input [24:0]\read_reg_PWM_T_carrier_us_rd_AXI_reg[24] ;
  input [17:0]\read_reg_PWM_min_pulse_width_rd_AXI_reg[17] ;
  input [1:0]\read_reg_Mode_rd_AXI_reg[1] ;

  wire AXI4_Lite_ACLK;
  wire [13:0]AXI4_Lite_ARADDR;
  wire AXI4_Lite_ARESETN;
  wire AXI4_Lite_ARREADY;
  wire AXI4_Lite_ARVALID;
  wire [13:0]AXI4_Lite_AWADDR;
  wire AXI4_Lite_AWREADY;
  wire AXI4_Lite_AWVALID;
  wire AXI4_Lite_BREADY;
  wire [26:0]AXI4_Lite_RDATA;
  wire AXI4_Lite_RREADY;
  wire [24:0]AXI4_Lite_WDATA;
  wire [3:0]AXI4_Lite_WSTRB;
  wire AXI4_Lite_WVALID;
  wire CEA1;
  wire CEB2;
  wire [24:0]D;
  wire FSM_sequential_axi_lite_rstate_reg;
  wire IPCORE_RESETN;
  wire PWM_en_AXI_1;
  wire PWM_en_rd_AXI_sig;
  wire [1:0]Q;
  wire [1:0]read_reg_Mode_rd_AXI;
  wire [1:0]\read_reg_Mode_rd_AXI_reg[1] ;
  wire [24:0]read_reg_PWM_T_carrier_us_rd_AXI;
  wire [24:0]\read_reg_PWM_T_carrier_us_rd_AXI_reg[24] ;
  wire read_reg_PWM_en_rd_AXI;
  wire [24:0]read_reg_PWM_f_carrier_kHz_rd_AXI;
  wire [17:0]read_reg_PWM_min_pulse_width_rd_AXI;
  wire [17:0]\read_reg_PWM_min_pulse_width_rd_AXI_reg[17] ;
  wire [30:30]read_reg_ip_timestamp;
  wire reg_enb_Mode_AXI;
  wire reg_enb_PWM_min_pulse_width_AXI;
  wire reg_enb_Scal_T_carrier_AXI;
  wire reg_enb_Scal_f_carrier_AXI;
  wire reg_enb_TriState_HB1_AXI;
  wire reg_enb_TriState_HB2_AXI;
  wire reg_enb_TriState_HB3_AXI;
  wire reg_enb_m_u1_norm_AXI;
  wire reg_enb_m_u2_norm_AXI;
  wire reg_enb_m_u3_norm_AXI;
  wire reset;
  wire u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_1;
  wire u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_10;
  wire u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_11;
  wire u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_12;
  wire u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_13;
  wire u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_14;
  wire u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_15;
  wire u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_16;
  wire u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_17;
  wire u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_18;
  wire u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_19;
  wire u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_2;
  wire u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_20;
  wire u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_21;
  wire u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_22;
  wire u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_23;
  wire u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_24;
  wire u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_25;
  wire u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_26;
  wire u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_27;
  wire u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_3;
  wire u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_4;
  wire u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_5;
  wire u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_6;
  wire u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_7;
  wire u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_8;
  wire u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_9;
  wire write_PWM_en_AXI;
  wire [1:0]\write_reg_Mode_AXI_reg[1] ;
  wire [17:0]\write_reg_PWM_min_pulse_width_AXI_reg[17] ;
  wire [24:0]\write_reg_Scal_T_carrier_AXI_reg[24] ;
  wire [24:0]\write_reg_Scal_f_carrier_AXI_reg[24] ;
  wire [1:0]\write_reg_TriState_HB1_AXI_reg[1] ;
  wire [1:0]\write_reg_TriState_HB2_AXI_reg[1] ;
  wire [1:0]\write_reg_TriState_HB3_AXI_reg[1] ;
  wire [13:0]\write_reg_m_u1_norm_AXI_reg[13] ;
  wire [13:0]\write_reg_m_u2_norm_AXI_reg[13] ;
  wire [13:0]\write_reg_m_u3_norm_AXI_reg[13] ;

  zusys_PWM_and_SS_control_V_0_2_PWM_and_SS_control_V3_ip_addr_decoder u_PWM_and_SS_control_V3_ip_addr_decoder_inst
       (.AXI4_Lite_ACLK(AXI4_Lite_ACLK),
        .CEA1(CEA1),
        .CEB2(CEB2),
        .D(D),
        .E(reg_enb_Mode_AXI),
        .PWM_en_AXI_1(PWM_en_AXI_1),
        .PWM_en_rd_AXI_sig(PWM_en_rd_AXI_sig),
        .Q({u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_2,u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_3,u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_4,u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_5,u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_6,u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_7,u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_8,u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_9,u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_10,u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_11,u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_12,u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_13,u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_14,u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_15,u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_16,u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_17,u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_18,u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_19,u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_20,u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_21,u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_22,u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_23,u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_24,u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_25,u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_26}),
        .SR(reset),
        .\read_reg_Mode_rd_AXI_reg[1]_0 (read_reg_Mode_rd_AXI),
        .\read_reg_Mode_rd_AXI_reg[1]_1 (\read_reg_Mode_rd_AXI_reg[1] ),
        .\read_reg_PWM_T_carrier_us_rd_AXI_reg[24]_0 (read_reg_PWM_T_carrier_us_rd_AXI),
        .\read_reg_PWM_T_carrier_us_rd_AXI_reg[24]_1 (\read_reg_PWM_T_carrier_us_rd_AXI_reg[24] ),
        .read_reg_PWM_en_rd_AXI(read_reg_PWM_en_rd_AXI),
        .\read_reg_PWM_f_carrier_kHz_rd_AXI_reg[24]_0 (read_reg_PWM_f_carrier_kHz_rd_AXI),
        .\read_reg_PWM_min_pulse_width_rd_AXI_reg[17]_0 (read_reg_PWM_min_pulse_width_rd_AXI),
        .\read_reg_PWM_min_pulse_width_rd_AXI_reg[17]_1 (\read_reg_PWM_min_pulse_width_rd_AXI_reg[17] ),
        .read_reg_ip_timestamp(read_reg_ip_timestamp),
        .write_PWM_en_AXI(write_PWM_en_AXI),
        .\write_reg_Mode_AXI_reg[1]_0 (\write_reg_Mode_AXI_reg[1] ),
        .write_reg_PWM_en_AXI_reg_0(u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_27),
        .\write_reg_PWM_min_pulse_width_AXI_reg[17]_0 (\write_reg_PWM_min_pulse_width_AXI_reg[17] ),
        .\write_reg_PWM_min_pulse_width_AXI_reg[17]_1 (reg_enb_PWM_min_pulse_width_AXI),
        .\write_reg_Scal_T_carrier_AXI_reg[24]_0 (\write_reg_Scal_T_carrier_AXI_reg[24] ),
        .\write_reg_Scal_T_carrier_AXI_reg[24]_1 (reg_enb_Scal_T_carrier_AXI),
        .\write_reg_Scal_f_carrier_AXI_reg[24]_0 (\write_reg_Scal_f_carrier_AXI_reg[24] ),
        .\write_reg_Scal_f_carrier_AXI_reg[24]_1 (reg_enb_Scal_f_carrier_AXI),
        .\write_reg_TriState_HB1_AXI_reg[1]_0 (\write_reg_TriState_HB1_AXI_reg[1] ),
        .\write_reg_TriState_HB1_AXI_reg[1]_1 (reg_enb_TriState_HB1_AXI),
        .\write_reg_TriState_HB2_AXI_reg[1]_0 (\write_reg_TriState_HB2_AXI_reg[1] ),
        .\write_reg_TriState_HB2_AXI_reg[1]_1 (reg_enb_TriState_HB2_AXI),
        .\write_reg_TriState_HB3_AXI_reg[1]_0 (\write_reg_TriState_HB3_AXI_reg[1] ),
        .\write_reg_TriState_HB3_AXI_reg[1]_1 (reg_enb_TriState_HB3_AXI),
        .write_reg_axi_enable_reg_0(u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_1),
        .\write_reg_m_u1_norm_AXI_reg[13]_0 (\write_reg_m_u1_norm_AXI_reg[13] ),
        .\write_reg_m_u1_norm_AXI_reg[13]_1 (reg_enb_m_u1_norm_AXI),
        .\write_reg_m_u2_norm_AXI_reg[13]_0 (\write_reg_m_u2_norm_AXI_reg[13] ),
        .\write_reg_m_u2_norm_AXI_reg[13]_1 (reg_enb_m_u2_norm_AXI),
        .\write_reg_m_u3_norm_AXI_reg[13]_0 (\write_reg_m_u3_norm_AXI_reg[13] ),
        .\write_reg_m_u3_norm_AXI_reg[13]_1 (reg_enb_m_u3_norm_AXI));
  zusys_PWM_and_SS_control_V_0_2_PWM_and_SS_control_V3_ip_axi_lite_module u_PWM_and_SS_control_V3_ip_axi_lite_module_inst
       (.AXI4_Lite_ACLK(AXI4_Lite_ACLK),
        .AXI4_Lite_ARADDR(AXI4_Lite_ARADDR),
        .\AXI4_Lite_ARADDR[3] (reg_enb_TriState_HB3_AXI),
        .\AXI4_Lite_ARADDR[3]_0 (reg_enb_m_u3_norm_AXI),
        .\AXI4_Lite_ARADDR[3]_1 (reg_enb_m_u2_norm_AXI),
        .\AXI4_Lite_ARADDR[3]_2 (reg_enb_PWM_min_pulse_width_AXI),
        .\AXI4_Lite_ARADDR[3]_3 (reg_enb_Scal_f_carrier_AXI),
        .\AXI4_Lite_ARADDR[4] (reg_enb_m_u1_norm_AXI),
        .\AXI4_Lite_ARADDR[6] (reg_enb_TriState_HB2_AXI),
        .\AXI4_Lite_ARADDR[6]_0 (reg_enb_TriState_HB1_AXI),
        .AXI4_Lite_ARESETN(AXI4_Lite_ARESETN),
        .AXI4_Lite_ARREADY(AXI4_Lite_ARREADY),
        .AXI4_Lite_ARVALID(AXI4_Lite_ARVALID),
        .AXI4_Lite_AWADDR(AXI4_Lite_AWADDR),
        .AXI4_Lite_AWREADY(AXI4_Lite_AWREADY),
        .AXI4_Lite_AWVALID(AXI4_Lite_AWVALID),
        .AXI4_Lite_BREADY(AXI4_Lite_BREADY),
        .AXI4_Lite_RDATA(AXI4_Lite_RDATA),
        .\AXI4_Lite_RDATA_tmp_reg[1]_0 (read_reg_Mode_rd_AXI),
        .\AXI4_Lite_RDATA_tmp_reg[24]_0 (read_reg_PWM_f_carrier_kHz_rd_AXI),
        .\AXI4_Lite_RDATA_tmp_reg[24]_1 (read_reg_PWM_T_carrier_us_rd_AXI),
        .\AXI4_Lite_RDATA_tmp_reg[30]_0 (read_reg_PWM_min_pulse_width_rd_AXI),
        .AXI4_Lite_RREADY(AXI4_Lite_RREADY),
        .AXI4_Lite_WDATA(AXI4_Lite_WDATA),
        .AXI4_Lite_WSTRB(AXI4_Lite_WSTRB),
        .AXI4_Lite_WVALID(AXI4_Lite_WVALID),
        .CEA1(CEA1),
        .E(reg_enb_Mode_AXI),
        .\FSM_onehot_axi_lite_wstate_reg[2]_0 (Q),
        .FSM_sequential_axi_lite_rstate_reg_0(FSM_sequential_axi_lite_rstate_reg),
        .IPCORE_RESETN(IPCORE_RESETN),
        .Q({u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_2,u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_3,u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_4,u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_5,u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_6,u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_7,u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_8,u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_9,u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_10,u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_11,u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_12,u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_13,u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_14,u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_15,u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_16,u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_17,u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_18,u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_19,u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_20,u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_21,u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_22,u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_23,u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_24,u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_25,u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_26}),
        .read_reg_PWM_en_rd_AXI(read_reg_PWM_en_rd_AXI),
        .read_reg_ip_timestamp(read_reg_ip_timestamp),
        .reset(reset),
        .\waddr_reg[3]_0 (reg_enb_Scal_T_carrier_AXI),
        .\wdata_reg[0]_0 (u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_1),
        .\wdata_reg[0]_1 (u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_27),
        .write_PWM_en_AXI(write_PWM_en_AXI));
endmodule

module zusys_PWM_and_SS_control_V_0_2_PWM_and_SS_control_V3_ip_axi_lite_module
   (FSM_sequential_axi_lite_rstate_reg_0,
    \wdata_reg[0]_0 ,
    Q,
    \wdata_reg[0]_1 ,
    \AXI4_Lite_ARADDR[3] ,
    \AXI4_Lite_ARADDR[6] ,
    \AXI4_Lite_ARADDR[6]_0 ,
    \AXI4_Lite_ARADDR[3]_0 ,
    \AXI4_Lite_ARADDR[3]_1 ,
    \AXI4_Lite_ARADDR[4] ,
    \AXI4_Lite_ARADDR[3]_2 ,
    \waddr_reg[3]_0 ,
    \AXI4_Lite_ARADDR[3]_3 ,
    E,
    AXI4_Lite_ARREADY,
    \FSM_onehot_axi_lite_wstate_reg[2]_0 ,
    AXI4_Lite_AWREADY,
    reset,
    AXI4_Lite_RDATA,
    AXI4_Lite_ACLK,
    CEA1,
    write_PWM_en_AXI,
    AXI4_Lite_ARVALID,
    AXI4_Lite_ARADDR,
    read_reg_PWM_en_rd_AXI,
    \AXI4_Lite_RDATA_tmp_reg[1]_0 ,
    \AXI4_Lite_RDATA_tmp_reg[24]_0 ,
    \AXI4_Lite_RDATA_tmp_reg[24]_1 ,
    \AXI4_Lite_RDATA_tmp_reg[30]_0 ,
    read_reg_ip_timestamp,
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
  output \wdata_reg[0]_0 ;
  output [24:0]Q;
  output \wdata_reg[0]_1 ;
  output [0:0]\AXI4_Lite_ARADDR[3] ;
  output [0:0]\AXI4_Lite_ARADDR[6] ;
  output [0:0]\AXI4_Lite_ARADDR[6]_0 ;
  output [0:0]\AXI4_Lite_ARADDR[3]_0 ;
  output [0:0]\AXI4_Lite_ARADDR[3]_1 ;
  output [0:0]\AXI4_Lite_ARADDR[4] ;
  output [0:0]\AXI4_Lite_ARADDR[3]_2 ;
  output [0:0]\waddr_reg[3]_0 ;
  output [0:0]\AXI4_Lite_ARADDR[3]_3 ;
  output [0:0]E;
  output AXI4_Lite_ARREADY;
  output [1:0]\FSM_onehot_axi_lite_wstate_reg[2]_0 ;
  output AXI4_Lite_AWREADY;
  output reset;
  output [26:0]AXI4_Lite_RDATA;
  input AXI4_Lite_ACLK;
  input CEA1;
  input write_PWM_en_AXI;
  input AXI4_Lite_ARVALID;
  input [13:0]AXI4_Lite_ARADDR;
  input read_reg_PWM_en_rd_AXI;
  input [1:0]\AXI4_Lite_RDATA_tmp_reg[1]_0 ;
  input [24:0]\AXI4_Lite_RDATA_tmp_reg[24]_0 ;
  input [24:0]\AXI4_Lite_RDATA_tmp_reg[24]_1 ;
  input [17:0]\AXI4_Lite_RDATA_tmp_reg[30]_0 ;
  input [0:0]read_reg_ip_timestamp;
  input AXI4_Lite_RREADY;
  input AXI4_Lite_AWVALID;
  input AXI4_Lite_WVALID;
  input AXI4_Lite_ARESETN;
  input IPCORE_RESETN;
  input AXI4_Lite_BREADY;
  input [3:0]AXI4_Lite_WSTRB;
  input [13:0]AXI4_Lite_AWADDR;
  input [24:0]AXI4_Lite_WDATA;

  wire AXI4_Lite_ACLK;
  wire [13:0]AXI4_Lite_ARADDR;
  wire [0:0]\AXI4_Lite_ARADDR[3] ;
  wire [0:0]\AXI4_Lite_ARADDR[3]_0 ;
  wire [0:0]\AXI4_Lite_ARADDR[3]_1 ;
  wire [0:0]\AXI4_Lite_ARADDR[3]_2 ;
  wire [0:0]\AXI4_Lite_ARADDR[3]_3 ;
  wire [0:0]\AXI4_Lite_ARADDR[4] ;
  wire [0:0]\AXI4_Lite_ARADDR[6] ;
  wire [0:0]\AXI4_Lite_ARADDR[6]_0 ;
  wire AXI4_Lite_ARESETN;
  wire AXI4_Lite_ARREADY;
  wire AXI4_Lite_ARVALID;
  wire [13:0]AXI4_Lite_AWADDR;
  wire AXI4_Lite_AWREADY;
  wire AXI4_Lite_AWVALID;
  wire AXI4_Lite_BREADY;
  wire [26:0]AXI4_Lite_RDATA;
  wire \AXI4_Lite_RDATA_tmp[0]_i_2_n_0 ;
  wire \AXI4_Lite_RDATA_tmp[0]_i_4_n_0 ;
  wire \AXI4_Lite_RDATA_tmp[0]_i_5_n_0 ;
  wire \AXI4_Lite_RDATA_tmp[10]_i_2_n_0 ;
  wire \AXI4_Lite_RDATA_tmp[11]_i_2_n_0 ;
  wire \AXI4_Lite_RDATA_tmp[13]_i_2_n_0 ;
  wire \AXI4_Lite_RDATA_tmp[16]_i_2_n_0 ;
  wire \AXI4_Lite_RDATA_tmp[16]_i_3_n_0 ;
  wire \AXI4_Lite_RDATA_tmp[1]_i_3_n_0 ;
  wire \AXI4_Lite_RDATA_tmp[23]_i_2_n_0 ;
  wire \AXI4_Lite_RDATA_tmp[24]_i_2_n_0 ;
  wire \AXI4_Lite_RDATA_tmp[24]_i_3_n_0 ;
  wire \AXI4_Lite_RDATA_tmp[24]_i_4_n_0 ;
  wire \AXI4_Lite_RDATA_tmp[30]_i_2_n_0 ;
  wire \AXI4_Lite_RDATA_tmp[30]_i_3_n_0 ;
  wire \AXI4_Lite_RDATA_tmp[30]_i_4_n_0 ;
  wire \AXI4_Lite_RDATA_tmp[30]_i_5_n_0 ;
  wire \AXI4_Lite_RDATA_tmp[30]_i_6_n_0 ;
  wire \AXI4_Lite_RDATA_tmp[30]_i_7_n_0 ;
  wire \AXI4_Lite_RDATA_tmp[30]_i_8_n_0 ;
  wire \AXI4_Lite_RDATA_tmp[31]_i_3_n_0 ;
  wire \AXI4_Lite_RDATA_tmp[31]_i_4_n_0 ;
  wire \AXI4_Lite_RDATA_tmp[31]_i_5_n_0 ;
  wire \AXI4_Lite_RDATA_tmp[31]_i_6_n_0 ;
  wire \AXI4_Lite_RDATA_tmp[31]_i_7_n_0 ;
  wire \AXI4_Lite_RDATA_tmp[31]_i_8_n_0 ;
  wire \AXI4_Lite_RDATA_tmp[31]_i_9_n_0 ;
  wire \AXI4_Lite_RDATA_tmp[4]_i_2_n_0 ;
  wire \AXI4_Lite_RDATA_tmp[5]_i_2_n_0 ;
  wire \AXI4_Lite_RDATA_tmp[6]_i_2_n_0 ;
  wire \AXI4_Lite_RDATA_tmp[8]_i_2_n_0 ;
  wire \AXI4_Lite_RDATA_tmp[9]_i_2_n_0 ;
  wire [1:0]\AXI4_Lite_RDATA_tmp_reg[1]_0 ;
  wire [24:0]\AXI4_Lite_RDATA_tmp_reg[24]_0 ;
  wire [24:0]\AXI4_Lite_RDATA_tmp_reg[24]_1 ;
  wire [17:0]\AXI4_Lite_RDATA_tmp_reg[30]_0 ;
  wire AXI4_Lite_RREADY;
  wire [24:0]AXI4_Lite_WDATA;
  wire [3:0]AXI4_Lite_WSTRB;
  wire AXI4_Lite_WVALID;
  wire CEA1;
  wire [0:0]E;
  wire [1:0]\FSM_onehot_axi_lite_wstate_reg[2]_0 ;
  wire \FSM_onehot_axi_lite_wstate_reg_n_0_[0] ;
  wire FSM_sequential_axi_lite_rstate_reg_0;
  wire IPCORE_RESETN;
  wire [24:0]Q;
  wire aw_transfer;
  wire axi_lite_rstate_next;
  wire [2:0]axi_lite_wstate_next;
  wire [31:0]data_read;
  wire decode_sel_Mode_rd_AXI;
  wire decode_sel_PWM_en_rd_AXI;
  wire read_reg_PWM_en_rd_AXI;
  wire [0:0]read_reg_ip_timestamp;
  wire reset;
  wire reset_0;
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
  wire [0:0]\waddr_reg[3]_0 ;
  wire \wdata_reg[0]_0 ;
  wire \wdata_reg[0]_1 ;
  wire write_PWM_en_AXI;
  wire \write_reg_Mode_AXI[1]_i_2_n_0 ;
  wire \write_reg_Mode_AXI[1]_i_3_n_0 ;
  wire \write_reg_Mode_AXI[1]_i_4_n_0 ;
  wire \write_reg_Mode_AXI[1]_i_5_n_0 ;
  wire \write_reg_Mode_AXI[1]_i_6_n_0 ;
  wire \write_reg_Mode_AXI[1]_i_7_n_0 ;
  wire \write_reg_Mode_AXI[1]_i_8_n_0 ;
  wire write_reg_PWM_en_AXI_i_2_n_0;
  wire write_reg_PWM_en_AXI_i_3_n_0;
  wire \write_reg_PWM_min_pulse_width_AXI[17]_i_2_n_0 ;
  wire \write_reg_PWM_min_pulse_width_AXI[17]_i_3_n_0 ;
  wire \write_reg_Scal_f_carrier_AXI[24]_i_2_n_0 ;
  wire \write_reg_Scal_f_carrier_AXI[24]_i_3_n_0 ;
  wire write_reg_axi_enable_i_2_n_0;
  wire write_reg_axi_enable_i_3_n_0;

  (* SOFT_HLUTNM = "soft_lutpair6" *) 
  LUT3 #(
    .INIT(8'h04)) 
    AXI4_Lite_ARREADY_INST_0
       (.I0(FSM_sequential_axi_lite_rstate_reg_0),
        .I1(\FSM_onehot_axi_lite_wstate_reg_n_0_[0] ),
        .I2(AXI4_Lite_AWVALID),
        .O(AXI4_Lite_ARREADY));
  (* SOFT_HLUTNM = "soft_lutpair7" *) 
  LUT2 #(
    .INIT(4'h2)) 
    AXI4_Lite_AWREADY_INST_0
       (.I0(\FSM_onehot_axi_lite_wstate_reg_n_0_[0] ),
        .I1(FSM_sequential_axi_lite_rstate_reg_0),
        .O(AXI4_Lite_AWREADY));
  LUT6 #(
    .INIT(64'hFFFFFFFFFFFFFF80)) 
    \AXI4_Lite_RDATA_tmp[0]_i_1 
       (.I0(\AXI4_Lite_RDATA_tmp[0]_i_2_n_0 ),
        .I1(decode_sel_PWM_en_rd_AXI),
        .I2(read_reg_PWM_en_rd_AXI),
        .I3(\AXI4_Lite_RDATA_tmp[16]_i_3_n_0 ),
        .I4(\AXI4_Lite_RDATA_tmp[0]_i_4_n_0 ),
        .I5(\AXI4_Lite_RDATA_tmp[0]_i_5_n_0 ),
        .O(data_read[0]));
  LUT2 #(
    .INIT(4'h7)) 
    \AXI4_Lite_RDATA_tmp[0]_i_2 
       (.I0(\AXI4_Lite_RDATA_tmp[31]_i_4_n_0 ),
        .I1(\AXI4_Lite_RDATA_tmp[30]_i_3_n_0 ),
        .O(\AXI4_Lite_RDATA_tmp[0]_i_2_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair1" *) 
  LUT5 #(
    .INIT(32'hB8000000)) 
    \AXI4_Lite_RDATA_tmp[0]_i_3 
       (.I0(AXI4_Lite_ARADDR[0]),
        .I1(AXI4_Lite_ARVALID),
        .I2(sel0[0]),
        .I3(\write_reg_Scal_f_carrier_AXI[24]_i_3_n_0 ),
        .I4(\AXI4_Lite_RDATA_tmp[31]_i_4_n_0 ),
        .O(decode_sel_PWM_en_rd_AXI));
  LUT6 #(
    .INIT(64'h00A0000000C00000)) 
    \AXI4_Lite_RDATA_tmp[0]_i_4 
       (.I0(\AXI4_Lite_RDATA_tmp_reg[24]_1 [0]),
        .I1(\AXI4_Lite_RDATA_tmp_reg[24]_0 [0]),
        .I2(\AXI4_Lite_RDATA_tmp[31]_i_4_n_0 ),
        .I3(\AXI4_Lite_RDATA_tmp[30]_i_4_n_0 ),
        .I4(\AXI4_Lite_RDATA_tmp[30]_i_3_n_0 ),
        .I5(\AXI4_Lite_RDATA_tmp[30]_i_5_n_0 ),
        .O(\AXI4_Lite_RDATA_tmp[0]_i_4_n_0 ));
  LUT5 #(
    .INIT(32'hA000C000)) 
    \AXI4_Lite_RDATA_tmp[0]_i_5 
       (.I0(\AXI4_Lite_RDATA_tmp_reg[1]_0 [0]),
        .I1(\AXI4_Lite_RDATA_tmp_reg[30]_0 [0]),
        .I2(\AXI4_Lite_RDATA_tmp[31]_i_4_n_0 ),
        .I3(\AXI4_Lite_RDATA_tmp[31]_i_3_n_0 ),
        .I4(\AXI4_Lite_RDATA_tmp[30]_i_5_n_0 ),
        .O(\AXI4_Lite_RDATA_tmp[0]_i_5_n_0 ));
  LUT6 #(
    .INIT(64'hFFFFFFF8FFF8FFF8)) 
    \AXI4_Lite_RDATA_tmp[10]_i_1 
       (.I0(\AXI4_Lite_RDATA_tmp[24]_i_4_n_0 ),
        .I1(\AXI4_Lite_RDATA_tmp_reg[24]_1 [10]),
        .I2(\AXI4_Lite_RDATA_tmp[10]_i_2_n_0 ),
        .I3(\AXI4_Lite_RDATA_tmp[16]_i_3_n_0 ),
        .I4(\AXI4_Lite_RDATA_tmp[24]_i_3_n_0 ),
        .I5(\AXI4_Lite_RDATA_tmp_reg[24]_0 [10]),
        .O(data_read[10]));
  LUT6 #(
    .INIT(64'h4700000000000000)) 
    \AXI4_Lite_RDATA_tmp[10]_i_2 
       (.I0(AXI4_Lite_ARADDR[0]),
        .I1(AXI4_Lite_ARVALID),
        .I2(sel0[0]),
        .I3(\AXI4_Lite_RDATA_tmp[31]_i_3_n_0 ),
        .I4(\AXI4_Lite_RDATA_tmp[31]_i_4_n_0 ),
        .I5(\AXI4_Lite_RDATA_tmp_reg[30]_0 [10]),
        .O(\AXI4_Lite_RDATA_tmp[10]_i_2_n_0 ));
  LUT6 #(
    .INIT(64'hFFFFFFF8FFF8FFF8)) 
    \AXI4_Lite_RDATA_tmp[11]_i_1 
       (.I0(\AXI4_Lite_RDATA_tmp[24]_i_4_n_0 ),
        .I1(\AXI4_Lite_RDATA_tmp_reg[24]_1 [11]),
        .I2(\AXI4_Lite_RDATA_tmp[11]_i_2_n_0 ),
        .I3(\AXI4_Lite_RDATA_tmp[16]_i_3_n_0 ),
        .I4(\AXI4_Lite_RDATA_tmp[24]_i_3_n_0 ),
        .I5(\AXI4_Lite_RDATA_tmp_reg[24]_0 [11]),
        .O(data_read[11]));
  LUT6 #(
    .INIT(64'h4700000000000000)) 
    \AXI4_Lite_RDATA_tmp[11]_i_2 
       (.I0(AXI4_Lite_ARADDR[0]),
        .I1(AXI4_Lite_ARVALID),
        .I2(sel0[0]),
        .I3(\AXI4_Lite_RDATA_tmp[31]_i_3_n_0 ),
        .I4(\AXI4_Lite_RDATA_tmp[31]_i_4_n_0 ),
        .I5(\AXI4_Lite_RDATA_tmp_reg[30]_0 [11]),
        .O(\AXI4_Lite_RDATA_tmp[11]_i_2_n_0 ));
  LUT6 #(
    .INIT(64'hFFFFF888F888F888)) 
    \AXI4_Lite_RDATA_tmp[12]_i_1 
       (.I0(\AXI4_Lite_RDATA_tmp[24]_i_3_n_0 ),
        .I1(\AXI4_Lite_RDATA_tmp_reg[24]_0 [12]),
        .I2(\AXI4_Lite_RDATA_tmp[24]_i_4_n_0 ),
        .I3(\AXI4_Lite_RDATA_tmp_reg[24]_1 [12]),
        .I4(\AXI4_Lite_RDATA_tmp_reg[30]_0 [12]),
        .I5(\AXI4_Lite_RDATA_tmp[23]_i_2_n_0 ),
        .O(data_read[12]));
  LUT6 #(
    .INIT(64'hFFFFFFF8FFF8FFF8)) 
    \AXI4_Lite_RDATA_tmp[13]_i_1 
       (.I0(\AXI4_Lite_RDATA_tmp[24]_i_4_n_0 ),
        .I1(\AXI4_Lite_RDATA_tmp_reg[24]_1 [13]),
        .I2(\AXI4_Lite_RDATA_tmp[13]_i_2_n_0 ),
        .I3(\AXI4_Lite_RDATA_tmp[16]_i_3_n_0 ),
        .I4(\AXI4_Lite_RDATA_tmp[24]_i_3_n_0 ),
        .I5(\AXI4_Lite_RDATA_tmp_reg[24]_0 [13]),
        .O(data_read[13]));
  LUT6 #(
    .INIT(64'h4700000000000000)) 
    \AXI4_Lite_RDATA_tmp[13]_i_2 
       (.I0(AXI4_Lite_ARADDR[0]),
        .I1(AXI4_Lite_ARVALID),
        .I2(sel0[0]),
        .I3(\AXI4_Lite_RDATA_tmp[31]_i_3_n_0 ),
        .I4(\AXI4_Lite_RDATA_tmp[31]_i_4_n_0 ),
        .I5(\AXI4_Lite_RDATA_tmp_reg[30]_0 [13]),
        .O(\AXI4_Lite_RDATA_tmp[13]_i_2_n_0 ));
  LUT6 #(
    .INIT(64'hFFFFF888F888F888)) 
    \AXI4_Lite_RDATA_tmp[14]_i_1 
       (.I0(\AXI4_Lite_RDATA_tmp[24]_i_3_n_0 ),
        .I1(\AXI4_Lite_RDATA_tmp_reg[24]_0 [14]),
        .I2(\AXI4_Lite_RDATA_tmp[24]_i_4_n_0 ),
        .I3(\AXI4_Lite_RDATA_tmp_reg[24]_1 [14]),
        .I4(\AXI4_Lite_RDATA_tmp_reg[30]_0 [14]),
        .I5(\AXI4_Lite_RDATA_tmp[23]_i_2_n_0 ),
        .O(data_read[14]));
  LUT6 #(
    .INIT(64'hFFFFF888F888F888)) 
    \AXI4_Lite_RDATA_tmp[15]_i_1 
       (.I0(\AXI4_Lite_RDATA_tmp[24]_i_3_n_0 ),
        .I1(\AXI4_Lite_RDATA_tmp_reg[24]_0 [15]),
        .I2(\AXI4_Lite_RDATA_tmp[24]_i_4_n_0 ),
        .I3(\AXI4_Lite_RDATA_tmp_reg[24]_1 [15]),
        .I4(\AXI4_Lite_RDATA_tmp_reg[30]_0 [15]),
        .I5(\AXI4_Lite_RDATA_tmp[23]_i_2_n_0 ),
        .O(data_read[15]));
  LUT6 #(
    .INIT(64'hFFFFFFF8FFF8FFF8)) 
    \AXI4_Lite_RDATA_tmp[16]_i_1 
       (.I0(\AXI4_Lite_RDATA_tmp[24]_i_4_n_0 ),
        .I1(\AXI4_Lite_RDATA_tmp_reg[24]_1 [16]),
        .I2(\AXI4_Lite_RDATA_tmp[16]_i_2_n_0 ),
        .I3(\AXI4_Lite_RDATA_tmp[16]_i_3_n_0 ),
        .I4(\AXI4_Lite_RDATA_tmp[24]_i_3_n_0 ),
        .I5(\AXI4_Lite_RDATA_tmp_reg[24]_0 [16]),
        .O(data_read[16]));
  LUT6 #(
    .INIT(64'h4700000000000000)) 
    \AXI4_Lite_RDATA_tmp[16]_i_2 
       (.I0(AXI4_Lite_ARADDR[0]),
        .I1(AXI4_Lite_ARVALID),
        .I2(sel0[0]),
        .I3(\AXI4_Lite_RDATA_tmp[31]_i_3_n_0 ),
        .I4(\AXI4_Lite_RDATA_tmp[31]_i_4_n_0 ),
        .I5(\AXI4_Lite_RDATA_tmp_reg[30]_0 [16]),
        .O(\AXI4_Lite_RDATA_tmp[16]_i_2_n_0 ));
  LUT6 #(
    .INIT(64'h0008008888888888)) 
    \AXI4_Lite_RDATA_tmp[16]_i_3 
       (.I0(\AXI4_Lite_RDATA_tmp[30]_i_6_n_0 ),
        .I1(\AXI4_Lite_RDATA_tmp[30]_i_7_n_0 ),
        .I2(\AXI4_Lite_RDATA_tmp[30]_i_5_n_0 ),
        .I3(\AXI4_Lite_RDATA_tmp[30]_i_3_n_0 ),
        .I4(\AXI4_Lite_RDATA_tmp[30]_i_4_n_0 ),
        .I5(\AXI4_Lite_RDATA_tmp[31]_i_4_n_0 ),
        .O(\AXI4_Lite_RDATA_tmp[16]_i_3_n_0 ));
  LUT6 #(
    .INIT(64'hFFFFF888F888F888)) 
    \AXI4_Lite_RDATA_tmp[17]_i_1 
       (.I0(\AXI4_Lite_RDATA_tmp[23]_i_2_n_0 ),
        .I1(\AXI4_Lite_RDATA_tmp_reg[30]_0 [17]),
        .I2(\AXI4_Lite_RDATA_tmp[24]_i_4_n_0 ),
        .I3(\AXI4_Lite_RDATA_tmp_reg[24]_1 [17]),
        .I4(\AXI4_Lite_RDATA_tmp_reg[24]_0 [17]),
        .I5(\AXI4_Lite_RDATA_tmp[24]_i_3_n_0 ),
        .O(data_read[17]));
  LUT6 #(
    .INIT(64'hFFFFFEEEFEEEFEEE)) 
    \AXI4_Lite_RDATA_tmp[18]_i_1 
       (.I0(\AXI4_Lite_RDATA_tmp[24]_i_2_n_0 ),
        .I1(data_read[31]),
        .I2(\AXI4_Lite_RDATA_tmp[24]_i_3_n_0 ),
        .I3(\AXI4_Lite_RDATA_tmp_reg[24]_0 [18]),
        .I4(\AXI4_Lite_RDATA_tmp_reg[24]_1 [18]),
        .I5(\AXI4_Lite_RDATA_tmp[24]_i_4_n_0 ),
        .O(data_read[18]));
  LUT6 #(
    .INIT(64'hFFFFF888F888F888)) 
    \AXI4_Lite_RDATA_tmp[19]_i_1 
       (.I0(\AXI4_Lite_RDATA_tmp[23]_i_2_n_0 ),
        .I1(\AXI4_Lite_RDATA_tmp_reg[30]_0 [17]),
        .I2(\AXI4_Lite_RDATA_tmp[24]_i_4_n_0 ),
        .I3(\AXI4_Lite_RDATA_tmp_reg[24]_1 [19]),
        .I4(\AXI4_Lite_RDATA_tmp_reg[24]_0 [19]),
        .I5(\AXI4_Lite_RDATA_tmp[24]_i_3_n_0 ),
        .O(data_read[19]));
  LUT6 #(
    .INIT(64'hFFFFFFF8FFF8FFF8)) 
    \AXI4_Lite_RDATA_tmp[1]_i_1 
       (.I0(\AXI4_Lite_RDATA_tmp_reg[1]_0 [1]),
        .I1(decode_sel_Mode_rd_AXI),
        .I2(\AXI4_Lite_RDATA_tmp[1]_i_3_n_0 ),
        .I3(\AXI4_Lite_RDATA_tmp[16]_i_3_n_0 ),
        .I4(\AXI4_Lite_RDATA_tmp[24]_i_3_n_0 ),
        .I5(\AXI4_Lite_RDATA_tmp_reg[24]_0 [1]),
        .O(data_read[1]));
  LUT6 #(
    .INIT(64'hA808000000000000)) 
    \AXI4_Lite_RDATA_tmp[1]_i_2 
       (.I0(\AXI4_Lite_RDATA_tmp[30]_i_5_n_0 ),
        .I1(sel0[1]),
        .I2(AXI4_Lite_ARVALID),
        .I3(AXI4_Lite_ARADDR[1]),
        .I4(\AXI4_Lite_RDATA_tmp[30]_i_3_n_0 ),
        .I5(\AXI4_Lite_RDATA_tmp[31]_i_4_n_0 ),
        .O(decode_sel_Mode_rd_AXI));
  LUT6 #(
    .INIT(64'h00C00000A0000000)) 
    \AXI4_Lite_RDATA_tmp[1]_i_3 
       (.I0(\AXI4_Lite_RDATA_tmp_reg[30]_0 [1]),
        .I1(\AXI4_Lite_RDATA_tmp_reg[24]_1 [1]),
        .I2(\AXI4_Lite_RDATA_tmp[31]_i_4_n_0 ),
        .I3(\AXI4_Lite_RDATA_tmp[30]_i_4_n_0 ),
        .I4(\AXI4_Lite_RDATA_tmp[30]_i_3_n_0 ),
        .I5(\AXI4_Lite_RDATA_tmp[30]_i_5_n_0 ),
        .O(\AXI4_Lite_RDATA_tmp[1]_i_3_n_0 ));
  LUT6 #(
    .INIT(64'hFFFFFEEEFEEEFEEE)) 
    \AXI4_Lite_RDATA_tmp[20]_i_1 
       (.I0(\AXI4_Lite_RDATA_tmp[24]_i_2_n_0 ),
        .I1(data_read[31]),
        .I2(\AXI4_Lite_RDATA_tmp[24]_i_3_n_0 ),
        .I3(\AXI4_Lite_RDATA_tmp_reg[24]_0 [20]),
        .I4(\AXI4_Lite_RDATA_tmp_reg[24]_1 [20]),
        .I5(\AXI4_Lite_RDATA_tmp[24]_i_4_n_0 ),
        .O(data_read[20]));
  LUT6 #(
    .INIT(64'hFFFFF888F888F888)) 
    \AXI4_Lite_RDATA_tmp[21]_i_1 
       (.I0(\AXI4_Lite_RDATA_tmp[23]_i_2_n_0 ),
        .I1(\AXI4_Lite_RDATA_tmp_reg[30]_0 [17]),
        .I2(\AXI4_Lite_RDATA_tmp[24]_i_4_n_0 ),
        .I3(\AXI4_Lite_RDATA_tmp_reg[24]_1 [21]),
        .I4(\AXI4_Lite_RDATA_tmp_reg[24]_0 [21]),
        .I5(\AXI4_Lite_RDATA_tmp[24]_i_3_n_0 ),
        .O(data_read[21]));
  LUT6 #(
    .INIT(64'hFFFFFEEEFEEEFEEE)) 
    \AXI4_Lite_RDATA_tmp[22]_i_1 
       (.I0(\AXI4_Lite_RDATA_tmp[24]_i_2_n_0 ),
        .I1(data_read[31]),
        .I2(\AXI4_Lite_RDATA_tmp[24]_i_3_n_0 ),
        .I3(\AXI4_Lite_RDATA_tmp_reg[24]_0 [22]),
        .I4(\AXI4_Lite_RDATA_tmp_reg[24]_1 [22]),
        .I5(\AXI4_Lite_RDATA_tmp[24]_i_4_n_0 ),
        .O(data_read[22]));
  LUT6 #(
    .INIT(64'hFFFFF888F888F888)) 
    \AXI4_Lite_RDATA_tmp[23]_i_1 
       (.I0(\AXI4_Lite_RDATA_tmp[23]_i_2_n_0 ),
        .I1(\AXI4_Lite_RDATA_tmp_reg[30]_0 [17]),
        .I2(\AXI4_Lite_RDATA_tmp[24]_i_4_n_0 ),
        .I3(\AXI4_Lite_RDATA_tmp_reg[24]_1 [23]),
        .I4(\AXI4_Lite_RDATA_tmp_reg[24]_0 [23]),
        .I5(\AXI4_Lite_RDATA_tmp[24]_i_3_n_0 ),
        .O(data_read[23]));
  LUT6 #(
    .INIT(64'h0000000080888000)) 
    \AXI4_Lite_RDATA_tmp[23]_i_2 
       (.I0(\AXI4_Lite_RDATA_tmp[31]_i_4_n_0 ),
        .I1(\AXI4_Lite_RDATA_tmp[30]_i_3_n_0 ),
        .I2(AXI4_Lite_ARADDR[1]),
        .I3(AXI4_Lite_ARVALID),
        .I4(sel0[1]),
        .I5(\AXI4_Lite_RDATA_tmp[30]_i_5_n_0 ),
        .O(\AXI4_Lite_RDATA_tmp[23]_i_2_n_0 ));
  LUT6 #(
    .INIT(64'hFFFFFEEEFEEEFEEE)) 
    \AXI4_Lite_RDATA_tmp[24]_i_1 
       (.I0(\AXI4_Lite_RDATA_tmp[24]_i_2_n_0 ),
        .I1(data_read[31]),
        .I2(\AXI4_Lite_RDATA_tmp[24]_i_3_n_0 ),
        .I3(\AXI4_Lite_RDATA_tmp_reg[24]_0 [24]),
        .I4(\AXI4_Lite_RDATA_tmp_reg[24]_1 [24]),
        .I5(\AXI4_Lite_RDATA_tmp[24]_i_4_n_0 ),
        .O(data_read[24]));
  LUT6 #(
    .INIT(64'h0008008888888888)) 
    \AXI4_Lite_RDATA_tmp[24]_i_2 
       (.I0(\AXI4_Lite_RDATA_tmp[30]_i_7_n_0 ),
        .I1(\AXI4_Lite_RDATA_tmp[30]_i_6_n_0 ),
        .I2(\AXI4_Lite_RDATA_tmp[30]_i_5_n_0 ),
        .I3(\AXI4_Lite_RDATA_tmp[30]_i_3_n_0 ),
        .I4(\AXI4_Lite_RDATA_tmp[30]_i_4_n_0 ),
        .I5(\AXI4_Lite_RDATA_tmp[31]_i_4_n_0 ),
        .O(\AXI4_Lite_RDATA_tmp[24]_i_2_n_0 ));
  LUT6 #(
    .INIT(64'h00000000202A0000)) 
    \AXI4_Lite_RDATA_tmp[24]_i_3 
       (.I0(\AXI4_Lite_RDATA_tmp[31]_i_4_n_0 ),
        .I1(AXI4_Lite_ARADDR[1]),
        .I2(AXI4_Lite_ARVALID),
        .I3(sel0[1]),
        .I4(\AXI4_Lite_RDATA_tmp[30]_i_3_n_0 ),
        .I5(\AXI4_Lite_RDATA_tmp[30]_i_5_n_0 ),
        .O(\AXI4_Lite_RDATA_tmp[24]_i_3_n_0 ));
  LUT6 #(
    .INIT(64'h202A000000000000)) 
    \AXI4_Lite_RDATA_tmp[24]_i_4 
       (.I0(\AXI4_Lite_RDATA_tmp[31]_i_4_n_0 ),
        .I1(AXI4_Lite_ARADDR[1]),
        .I2(AXI4_Lite_ARVALID),
        .I3(sel0[1]),
        .I4(\AXI4_Lite_RDATA_tmp[30]_i_3_n_0 ),
        .I5(\AXI4_Lite_RDATA_tmp[30]_i_5_n_0 ),
        .O(\AXI4_Lite_RDATA_tmp[24]_i_4_n_0 ));
  LUT6 #(
    .INIT(64'hFFFFF888F888F888)) 
    \AXI4_Lite_RDATA_tmp[2]_i_1 
       (.I0(\AXI4_Lite_RDATA_tmp[24]_i_3_n_0 ),
        .I1(\AXI4_Lite_RDATA_tmp_reg[24]_0 [2]),
        .I2(\AXI4_Lite_RDATA_tmp[24]_i_4_n_0 ),
        .I3(\AXI4_Lite_RDATA_tmp_reg[24]_1 [2]),
        .I4(\AXI4_Lite_RDATA_tmp_reg[30]_0 [2]),
        .I5(\AXI4_Lite_RDATA_tmp[23]_i_2_n_0 ),
        .O(data_read[2]));
  LUT6 #(
    .INIT(64'h0AAA0AAACAAA0AAA)) 
    \AXI4_Lite_RDATA_tmp[30]_i_1 
       (.I0(\AXI4_Lite_RDATA_tmp[30]_i_2_n_0 ),
        .I1(\AXI4_Lite_RDATA_tmp_reg[30]_0 [17]),
        .I2(\AXI4_Lite_RDATA_tmp[31]_i_4_n_0 ),
        .I3(\AXI4_Lite_RDATA_tmp[30]_i_3_n_0 ),
        .I4(\AXI4_Lite_RDATA_tmp[30]_i_4_n_0 ),
        .I5(\AXI4_Lite_RDATA_tmp[30]_i_5_n_0 ),
        .O(data_read[30]));
  LUT6 #(
    .INIT(64'h2A00AA00AA00AA00)) 
    \AXI4_Lite_RDATA_tmp[30]_i_2 
       (.I0(\AXI4_Lite_RDATA_tmp[30]_i_6_n_0 ),
        .I1(\AXI4_Lite_RDATA_tmp[31]_i_5_n_0 ),
        .I2(write_reg_PWM_en_AXI_i_2_n_0),
        .I3(\AXI4_Lite_RDATA_tmp[30]_i_7_n_0 ),
        .I4(\write_reg_Scal_f_carrier_AXI[24]_i_3_n_0 ),
        .I5(\AXI4_Lite_RDATA_tmp[30]_i_5_n_0 ),
        .O(\AXI4_Lite_RDATA_tmp[30]_i_2_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair8" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \AXI4_Lite_RDATA_tmp[30]_i_3 
       (.I0(AXI4_Lite_ARADDR[2]),
        .I1(AXI4_Lite_ARVALID),
        .I2(sel0[2]),
        .O(\AXI4_Lite_RDATA_tmp[30]_i_3_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair4" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \AXI4_Lite_RDATA_tmp[30]_i_4 
       (.I0(AXI4_Lite_ARADDR[1]),
        .I1(AXI4_Lite_ARVALID),
        .I2(sel0[1]),
        .O(\AXI4_Lite_RDATA_tmp[30]_i_4_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair1" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \AXI4_Lite_RDATA_tmp[30]_i_5 
       (.I0(AXI4_Lite_ARADDR[0]),
        .I1(AXI4_Lite_ARVALID),
        .I2(sel0[0]),
        .O(\AXI4_Lite_RDATA_tmp[30]_i_5_n_0 ));
  LUT6 #(
    .INIT(64'h0000000000000020)) 
    \AXI4_Lite_RDATA_tmp[30]_i_6 
       (.I0(read_reg_ip_timestamp),
        .I1(\write_reg_Mode_AXI[1]_i_8_n_0 ),
        .I2(\write_reg_Scal_f_carrier_AXI[24]_i_3_n_0 ),
        .I3(\AXI4_Lite_RDATA_tmp[30]_i_5_n_0 ),
        .I4(\AXI4_Lite_RDATA_tmp[31]_i_5_n_0 ),
        .I5(\write_reg_Mode_AXI[1]_i_7_n_0 ),
        .O(\AXI4_Lite_RDATA_tmp[30]_i_6_n_0 ));
  LUT5 #(
    .INIT(32'h00080000)) 
    \AXI4_Lite_RDATA_tmp[30]_i_7 
       (.I0(\AXI4_Lite_RDATA_tmp[31]_i_9_n_0 ),
        .I1(\AXI4_Lite_RDATA_tmp[31]_i_8_n_0 ),
        .I2(\write_reg_PWM_min_pulse_width_AXI[17]_i_3_n_0 ),
        .I3(\AXI4_Lite_RDATA_tmp[30]_i_8_n_0 ),
        .I4(\AXI4_Lite_RDATA_tmp[31]_i_6_n_0 ),
        .O(\AXI4_Lite_RDATA_tmp[30]_i_7_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair8" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \AXI4_Lite_RDATA_tmp[30]_i_8 
       (.I0(AXI4_Lite_ARADDR[10]),
        .I1(AXI4_Lite_ARVALID),
        .I2(sel0[10]),
        .O(\AXI4_Lite_RDATA_tmp[30]_i_8_n_0 ));
  LUT4 #(
    .INIT(16'h0400)) 
    \AXI4_Lite_RDATA_tmp[31]_i_1 
       (.I0(AXI4_Lite_AWVALID),
        .I1(AXI4_Lite_ARVALID),
        .I2(FSM_sequential_axi_lite_rstate_reg_0),
        .I3(\FSM_onehot_axi_lite_wstate_reg_n_0_[0] ),
        .O(top_rd_enb));
  LUT6 #(
    .INIT(64'h4700000000000000)) 
    \AXI4_Lite_RDATA_tmp[31]_i_2 
       (.I0(AXI4_Lite_ARADDR[0]),
        .I1(AXI4_Lite_ARVALID),
        .I2(sel0[0]),
        .I3(\AXI4_Lite_RDATA_tmp[31]_i_3_n_0 ),
        .I4(\AXI4_Lite_RDATA_tmp[31]_i_4_n_0 ),
        .I5(\AXI4_Lite_RDATA_tmp_reg[30]_0 [17]),
        .O(data_read[31]));
  (* SOFT_HLUTNM = "soft_lutpair3" *) 
  LUT5 #(
    .INIT(32'hCCA000A0)) 
    \AXI4_Lite_RDATA_tmp[31]_i_3 
       (.I0(sel0[1]),
        .I1(AXI4_Lite_ARADDR[1]),
        .I2(sel0[2]),
        .I3(AXI4_Lite_ARVALID),
        .I4(AXI4_Lite_ARADDR[2]),
        .O(\AXI4_Lite_RDATA_tmp[31]_i_3_n_0 ));
  LUT6 #(
    .INIT(64'h8000000000000000)) 
    \AXI4_Lite_RDATA_tmp[31]_i_4 
       (.I0(\AXI4_Lite_RDATA_tmp[31]_i_5_n_0 ),
        .I1(write_reg_PWM_en_AXI_i_2_n_0),
        .I2(\AXI4_Lite_RDATA_tmp[31]_i_6_n_0 ),
        .I3(\AXI4_Lite_RDATA_tmp[31]_i_7_n_0 ),
        .I4(\AXI4_Lite_RDATA_tmp[31]_i_8_n_0 ),
        .I5(\AXI4_Lite_RDATA_tmp[31]_i_9_n_0 ),
        .O(\AXI4_Lite_RDATA_tmp[31]_i_4_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair9" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \AXI4_Lite_RDATA_tmp[31]_i_5 
       (.I0(AXI4_Lite_ARADDR[3]),
        .I1(AXI4_Lite_ARVALID),
        .I2(sel0[3]),
        .O(\AXI4_Lite_RDATA_tmp[31]_i_5_n_0 ));
  LUT5 #(
    .INIT(32'h00053305)) 
    \AXI4_Lite_RDATA_tmp[31]_i_6 
       (.I0(sel0[5]),
        .I1(AXI4_Lite_ARADDR[5]),
        .I2(sel0[4]),
        .I3(AXI4_Lite_ARVALID),
        .I4(AXI4_Lite_ARADDR[4]),
        .O(\AXI4_Lite_RDATA_tmp[31]_i_6_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair2" *) 
  LUT5 #(
    .INIT(32'h00053305)) 
    \AXI4_Lite_RDATA_tmp[31]_i_7 
       (.I0(sel0[11]),
        .I1(AXI4_Lite_ARADDR[11]),
        .I2(sel0[10]),
        .I3(AXI4_Lite_ARVALID),
        .I4(AXI4_Lite_ARADDR[10]),
        .O(\AXI4_Lite_RDATA_tmp[31]_i_7_n_0 ));
  LUT5 #(
    .INIT(32'h00053305)) 
    \AXI4_Lite_RDATA_tmp[31]_i_8 
       (.I0(sel0[13]),
        .I1(AXI4_Lite_ARADDR[13]),
        .I2(sel0[8]),
        .I3(AXI4_Lite_ARVALID),
        .I4(AXI4_Lite_ARADDR[8]),
        .O(\AXI4_Lite_RDATA_tmp[31]_i_8_n_0 ));
  LUT5 #(
    .INIT(32'h00053305)) 
    \AXI4_Lite_RDATA_tmp[31]_i_9 
       (.I0(sel0[7]),
        .I1(AXI4_Lite_ARADDR[7]),
        .I2(sel0[12]),
        .I3(AXI4_Lite_ARVALID),
        .I4(AXI4_Lite_ARADDR[12]),
        .O(\AXI4_Lite_RDATA_tmp[31]_i_9_n_0 ));
  LUT6 #(
    .INIT(64'hFFFFF888F888F888)) 
    \AXI4_Lite_RDATA_tmp[3]_i_1 
       (.I0(\AXI4_Lite_RDATA_tmp[24]_i_3_n_0 ),
        .I1(\AXI4_Lite_RDATA_tmp_reg[24]_0 [3]),
        .I2(\AXI4_Lite_RDATA_tmp[24]_i_4_n_0 ),
        .I3(\AXI4_Lite_RDATA_tmp_reg[24]_1 [3]),
        .I4(\AXI4_Lite_RDATA_tmp_reg[30]_0 [3]),
        .I5(\AXI4_Lite_RDATA_tmp[23]_i_2_n_0 ),
        .O(data_read[3]));
  LUT6 #(
    .INIT(64'hFFFFFFF8FFF8FFF8)) 
    \AXI4_Lite_RDATA_tmp[4]_i_1 
       (.I0(\AXI4_Lite_RDATA_tmp[24]_i_4_n_0 ),
        .I1(\AXI4_Lite_RDATA_tmp_reg[24]_1 [4]),
        .I2(\AXI4_Lite_RDATA_tmp[4]_i_2_n_0 ),
        .I3(\AXI4_Lite_RDATA_tmp[16]_i_3_n_0 ),
        .I4(\AXI4_Lite_RDATA_tmp[24]_i_3_n_0 ),
        .I5(\AXI4_Lite_RDATA_tmp_reg[24]_0 [4]),
        .O(data_read[4]));
  LUT6 #(
    .INIT(64'h4700000000000000)) 
    \AXI4_Lite_RDATA_tmp[4]_i_2 
       (.I0(AXI4_Lite_ARADDR[0]),
        .I1(AXI4_Lite_ARVALID),
        .I2(sel0[0]),
        .I3(\AXI4_Lite_RDATA_tmp[31]_i_3_n_0 ),
        .I4(\AXI4_Lite_RDATA_tmp[31]_i_4_n_0 ),
        .I5(\AXI4_Lite_RDATA_tmp_reg[30]_0 [4]),
        .O(\AXI4_Lite_RDATA_tmp[4]_i_2_n_0 ));
  LUT6 #(
    .INIT(64'hFFFFFFF8FFF8FFF8)) 
    \AXI4_Lite_RDATA_tmp[5]_i_1 
       (.I0(\AXI4_Lite_RDATA_tmp[24]_i_4_n_0 ),
        .I1(\AXI4_Lite_RDATA_tmp_reg[24]_1 [5]),
        .I2(\AXI4_Lite_RDATA_tmp[5]_i_2_n_0 ),
        .I3(\AXI4_Lite_RDATA_tmp[16]_i_3_n_0 ),
        .I4(\AXI4_Lite_RDATA_tmp[24]_i_3_n_0 ),
        .I5(\AXI4_Lite_RDATA_tmp_reg[24]_0 [5]),
        .O(data_read[5]));
  LUT6 #(
    .INIT(64'h4700000000000000)) 
    \AXI4_Lite_RDATA_tmp[5]_i_2 
       (.I0(AXI4_Lite_ARADDR[0]),
        .I1(AXI4_Lite_ARVALID),
        .I2(sel0[0]),
        .I3(\AXI4_Lite_RDATA_tmp[31]_i_3_n_0 ),
        .I4(\AXI4_Lite_RDATA_tmp[31]_i_4_n_0 ),
        .I5(\AXI4_Lite_RDATA_tmp_reg[30]_0 [5]),
        .O(\AXI4_Lite_RDATA_tmp[5]_i_2_n_0 ));
  LUT6 #(
    .INIT(64'hFFFFFFF8FFF8FFF8)) 
    \AXI4_Lite_RDATA_tmp[6]_i_1 
       (.I0(\AXI4_Lite_RDATA_tmp[24]_i_4_n_0 ),
        .I1(\AXI4_Lite_RDATA_tmp_reg[24]_1 [6]),
        .I2(\AXI4_Lite_RDATA_tmp[6]_i_2_n_0 ),
        .I3(\AXI4_Lite_RDATA_tmp[16]_i_3_n_0 ),
        .I4(\AXI4_Lite_RDATA_tmp[24]_i_3_n_0 ),
        .I5(\AXI4_Lite_RDATA_tmp_reg[24]_0 [6]),
        .O(data_read[6]));
  LUT6 #(
    .INIT(64'h4700000000000000)) 
    \AXI4_Lite_RDATA_tmp[6]_i_2 
       (.I0(AXI4_Lite_ARADDR[0]),
        .I1(AXI4_Lite_ARVALID),
        .I2(sel0[0]),
        .I3(\AXI4_Lite_RDATA_tmp[31]_i_3_n_0 ),
        .I4(\AXI4_Lite_RDATA_tmp[31]_i_4_n_0 ),
        .I5(\AXI4_Lite_RDATA_tmp_reg[30]_0 [6]),
        .O(\AXI4_Lite_RDATA_tmp[6]_i_2_n_0 ));
  LUT6 #(
    .INIT(64'hFFFFF888F888F888)) 
    \AXI4_Lite_RDATA_tmp[7]_i_1 
       (.I0(\AXI4_Lite_RDATA_tmp[24]_i_3_n_0 ),
        .I1(\AXI4_Lite_RDATA_tmp_reg[24]_0 [7]),
        .I2(\AXI4_Lite_RDATA_tmp[24]_i_4_n_0 ),
        .I3(\AXI4_Lite_RDATA_tmp_reg[24]_1 [7]),
        .I4(\AXI4_Lite_RDATA_tmp_reg[30]_0 [7]),
        .I5(\AXI4_Lite_RDATA_tmp[23]_i_2_n_0 ),
        .O(data_read[7]));
  LUT6 #(
    .INIT(64'hFFFFFFF8FFF8FFF8)) 
    \AXI4_Lite_RDATA_tmp[8]_i_1 
       (.I0(\AXI4_Lite_RDATA_tmp[24]_i_4_n_0 ),
        .I1(\AXI4_Lite_RDATA_tmp_reg[24]_1 [8]),
        .I2(\AXI4_Lite_RDATA_tmp[8]_i_2_n_0 ),
        .I3(\AXI4_Lite_RDATA_tmp[16]_i_3_n_0 ),
        .I4(\AXI4_Lite_RDATA_tmp[24]_i_3_n_0 ),
        .I5(\AXI4_Lite_RDATA_tmp_reg[24]_0 [8]),
        .O(data_read[8]));
  LUT6 #(
    .INIT(64'h4700000000000000)) 
    \AXI4_Lite_RDATA_tmp[8]_i_2 
       (.I0(AXI4_Lite_ARADDR[0]),
        .I1(AXI4_Lite_ARVALID),
        .I2(sel0[0]),
        .I3(\AXI4_Lite_RDATA_tmp[31]_i_3_n_0 ),
        .I4(\AXI4_Lite_RDATA_tmp[31]_i_4_n_0 ),
        .I5(\AXI4_Lite_RDATA_tmp_reg[30]_0 [8]),
        .O(\AXI4_Lite_RDATA_tmp[8]_i_2_n_0 ));
  LUT6 #(
    .INIT(64'hFFFFFFF8FFF8FFF8)) 
    \AXI4_Lite_RDATA_tmp[9]_i_1 
       (.I0(\AXI4_Lite_RDATA_tmp[24]_i_4_n_0 ),
        .I1(\AXI4_Lite_RDATA_tmp_reg[24]_1 [9]),
        .I2(\AXI4_Lite_RDATA_tmp[9]_i_2_n_0 ),
        .I3(\AXI4_Lite_RDATA_tmp[16]_i_3_n_0 ),
        .I4(\AXI4_Lite_RDATA_tmp[24]_i_3_n_0 ),
        .I5(\AXI4_Lite_RDATA_tmp_reg[24]_0 [9]),
        .O(data_read[9]));
  LUT6 #(
    .INIT(64'h4700000000000000)) 
    \AXI4_Lite_RDATA_tmp[9]_i_2 
       (.I0(AXI4_Lite_ARADDR[0]),
        .I1(AXI4_Lite_ARVALID),
        .I2(sel0[0]),
        .I3(\AXI4_Lite_RDATA_tmp[31]_i_3_n_0 ),
        .I4(\AXI4_Lite_RDATA_tmp[31]_i_4_n_0 ),
        .I5(\AXI4_Lite_RDATA_tmp_reg[30]_0 [9]),
        .O(\AXI4_Lite_RDATA_tmp[9]_i_2_n_0 ));
  FDRE \AXI4_Lite_RDATA_tmp_reg[0] 
       (.C(AXI4_Lite_ACLK),
        .CE(top_rd_enb),
        .D(data_read[0]),
        .Q(AXI4_Lite_RDATA[0]),
        .R(reset_0));
  FDRE \AXI4_Lite_RDATA_tmp_reg[10] 
       (.C(AXI4_Lite_ACLK),
        .CE(top_rd_enb),
        .D(data_read[10]),
        .Q(AXI4_Lite_RDATA[10]),
        .R(reset_0));
  FDRE \AXI4_Lite_RDATA_tmp_reg[11] 
       (.C(AXI4_Lite_ACLK),
        .CE(top_rd_enb),
        .D(data_read[11]),
        .Q(AXI4_Lite_RDATA[11]),
        .R(reset_0));
  FDRE \AXI4_Lite_RDATA_tmp_reg[12] 
       (.C(AXI4_Lite_ACLK),
        .CE(top_rd_enb),
        .D(data_read[12]),
        .Q(AXI4_Lite_RDATA[12]),
        .R(reset_0));
  FDRE \AXI4_Lite_RDATA_tmp_reg[13] 
       (.C(AXI4_Lite_ACLK),
        .CE(top_rd_enb),
        .D(data_read[13]),
        .Q(AXI4_Lite_RDATA[13]),
        .R(reset_0));
  FDRE \AXI4_Lite_RDATA_tmp_reg[14] 
       (.C(AXI4_Lite_ACLK),
        .CE(top_rd_enb),
        .D(data_read[14]),
        .Q(AXI4_Lite_RDATA[14]),
        .R(reset_0));
  FDRE \AXI4_Lite_RDATA_tmp_reg[15] 
       (.C(AXI4_Lite_ACLK),
        .CE(top_rd_enb),
        .D(data_read[15]),
        .Q(AXI4_Lite_RDATA[15]),
        .R(reset_0));
  FDRE \AXI4_Lite_RDATA_tmp_reg[16] 
       (.C(AXI4_Lite_ACLK),
        .CE(top_rd_enb),
        .D(data_read[16]),
        .Q(AXI4_Lite_RDATA[16]),
        .R(reset_0));
  FDRE \AXI4_Lite_RDATA_tmp_reg[17] 
       (.C(AXI4_Lite_ACLK),
        .CE(top_rd_enb),
        .D(data_read[17]),
        .Q(AXI4_Lite_RDATA[17]),
        .R(reset_0));
  FDRE \AXI4_Lite_RDATA_tmp_reg[18] 
       (.C(AXI4_Lite_ACLK),
        .CE(top_rd_enb),
        .D(data_read[18]),
        .Q(AXI4_Lite_RDATA[18]),
        .R(reset_0));
  FDRE \AXI4_Lite_RDATA_tmp_reg[19] 
       (.C(AXI4_Lite_ACLK),
        .CE(top_rd_enb),
        .D(data_read[19]),
        .Q(AXI4_Lite_RDATA[19]),
        .R(reset_0));
  FDRE \AXI4_Lite_RDATA_tmp_reg[1] 
       (.C(AXI4_Lite_ACLK),
        .CE(top_rd_enb),
        .D(data_read[1]),
        .Q(AXI4_Lite_RDATA[1]),
        .R(reset_0));
  FDRE \AXI4_Lite_RDATA_tmp_reg[20] 
       (.C(AXI4_Lite_ACLK),
        .CE(top_rd_enb),
        .D(data_read[20]),
        .Q(AXI4_Lite_RDATA[20]),
        .R(reset_0));
  FDRE \AXI4_Lite_RDATA_tmp_reg[21] 
       (.C(AXI4_Lite_ACLK),
        .CE(top_rd_enb),
        .D(data_read[21]),
        .Q(AXI4_Lite_RDATA[21]),
        .R(reset_0));
  FDRE \AXI4_Lite_RDATA_tmp_reg[22] 
       (.C(AXI4_Lite_ACLK),
        .CE(top_rd_enb),
        .D(data_read[22]),
        .Q(AXI4_Lite_RDATA[22]),
        .R(reset_0));
  FDRE \AXI4_Lite_RDATA_tmp_reg[23] 
       (.C(AXI4_Lite_ACLK),
        .CE(top_rd_enb),
        .D(data_read[23]),
        .Q(AXI4_Lite_RDATA[23]),
        .R(reset_0));
  FDRE \AXI4_Lite_RDATA_tmp_reg[24] 
       (.C(AXI4_Lite_ACLK),
        .CE(top_rd_enb),
        .D(data_read[24]),
        .Q(AXI4_Lite_RDATA[24]),
        .R(reset_0));
  FDRE \AXI4_Lite_RDATA_tmp_reg[2] 
       (.C(AXI4_Lite_ACLK),
        .CE(top_rd_enb),
        .D(data_read[2]),
        .Q(AXI4_Lite_RDATA[2]),
        .R(reset_0));
  FDRE \AXI4_Lite_RDATA_tmp_reg[30] 
       (.C(AXI4_Lite_ACLK),
        .CE(top_rd_enb),
        .D(data_read[30]),
        .Q(AXI4_Lite_RDATA[25]),
        .R(reset_0));
  FDRE \AXI4_Lite_RDATA_tmp_reg[31] 
       (.C(AXI4_Lite_ACLK),
        .CE(top_rd_enb),
        .D(data_read[31]),
        .Q(AXI4_Lite_RDATA[26]),
        .R(reset_0));
  FDRE \AXI4_Lite_RDATA_tmp_reg[3] 
       (.C(AXI4_Lite_ACLK),
        .CE(top_rd_enb),
        .D(data_read[3]),
        .Q(AXI4_Lite_RDATA[3]),
        .R(reset_0));
  FDRE \AXI4_Lite_RDATA_tmp_reg[4] 
       (.C(AXI4_Lite_ACLK),
        .CE(top_rd_enb),
        .D(data_read[4]),
        .Q(AXI4_Lite_RDATA[4]),
        .R(reset_0));
  FDRE \AXI4_Lite_RDATA_tmp_reg[5] 
       (.C(AXI4_Lite_ACLK),
        .CE(top_rd_enb),
        .D(data_read[5]),
        .Q(AXI4_Lite_RDATA[5]),
        .R(reset_0));
  FDRE \AXI4_Lite_RDATA_tmp_reg[6] 
       (.C(AXI4_Lite_ACLK),
        .CE(top_rd_enb),
        .D(data_read[6]),
        .Q(AXI4_Lite_RDATA[6]),
        .R(reset_0));
  FDRE \AXI4_Lite_RDATA_tmp_reg[7] 
       (.C(AXI4_Lite_ACLK),
        .CE(top_rd_enb),
        .D(data_read[7]),
        .Q(AXI4_Lite_RDATA[7]),
        .R(reset_0));
  FDRE \AXI4_Lite_RDATA_tmp_reg[8] 
       (.C(AXI4_Lite_ACLK),
        .CE(top_rd_enb),
        .D(data_read[8]),
        .Q(AXI4_Lite_RDATA[8]),
        .R(reset_0));
  FDRE \AXI4_Lite_RDATA_tmp_reg[9] 
       (.C(AXI4_Lite_ACLK),
        .CE(top_rd_enb),
        .D(data_read[9]),
        .Q(AXI4_Lite_RDATA[9]),
        .R(reset_0));
  LUT5 #(
    .INIT(32'hFF8A8A8A)) 
    \FSM_onehot_axi_lite_wstate[0]_i_1 
       (.I0(\FSM_onehot_axi_lite_wstate_reg_n_0_[0] ),
        .I1(FSM_sequential_axi_lite_rstate_reg_0),
        .I2(AXI4_Lite_AWVALID),
        .I3(AXI4_Lite_BREADY),
        .I4(\FSM_onehot_axi_lite_wstate_reg[2]_0 [1]),
        .O(axi_lite_wstate_next[0]));
  LUT1 #(
    .INIT(2'h1)) 
    \FSM_onehot_axi_lite_wstate[1]_i_1 
       (.I0(AXI4_Lite_ARESETN),
        .O(reset_0));
  (* SOFT_HLUTNM = "soft_lutpair7" *) 
  LUT5 #(
    .INIT(32'h08FF0808)) 
    \FSM_onehot_axi_lite_wstate[1]_i_2 
       (.I0(AXI4_Lite_AWVALID),
        .I1(\FSM_onehot_axi_lite_wstate_reg_n_0_[0] ),
        .I2(FSM_sequential_axi_lite_rstate_reg_0),
        .I3(AXI4_Lite_WVALID),
        .I4(\FSM_onehot_axi_lite_wstate_reg[2]_0 [0]),
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
        .S(reset_0));
  (* FSM_ENCODED_STATES = "iSTATE:010,iSTATE0:100,iSTATE1:001" *) 
  FDRE #(
    .INIT(1'b0)) 
    \FSM_onehot_axi_lite_wstate_reg[1] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(axi_lite_wstate_next[1]),
        .Q(\FSM_onehot_axi_lite_wstate_reg[2]_0 [0]),
        .R(reset_0));
  (* FSM_ENCODED_STATES = "iSTATE:010,iSTATE0:100,iSTATE1:001" *) 
  FDRE #(
    .INIT(1'b0)) 
    \FSM_onehot_axi_lite_wstate_reg[2] 
       (.C(AXI4_Lite_ACLK),
        .CE(1'b1),
        .D(axi_lite_wstate_next[2]),
        .Q(\FSM_onehot_axi_lite_wstate_reg[2]_0 [1]),
        .R(reset_0));
  (* SOFT_HLUTNM = "soft_lutpair6" *) 
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
        .R(reset_0));
  LUT3 #(
    .INIT(8'hDF)) 
    Switch6_out1_1_i_1
       (.I0(AXI4_Lite_ARESETN),
        .I1(soft_reset),
        .I2(IPCORE_RESETN),
        .O(reset));
  LUT6 #(
    .INIT(64'h0100000000000000)) 
    soft_reset_i_1
       (.I0(sel0[2]),
        .I1(sel0[1]),
        .I2(sel0[0]),
        .I3(soft_reset_i_2_n_0),
        .I4(soft_reset_i_3_n_0),
        .I5(soft_reset_i_4_n_0),
        .O(soft_reset_i_1_n_0));
  LUT4 #(
    .INIT(16'h0001)) 
    soft_reset_i_2
       (.I0(sel0[6]),
        .I1(sel0[5]),
        .I2(sel0[4]),
        .I3(sel0[3]),
        .O(soft_reset_i_2_n_0));
  LUT4 #(
    .INIT(16'h0001)) 
    soft_reset_i_3
       (.I0(sel0[10]),
        .I1(sel0[9]),
        .I2(sel0[8]),
        .I3(sel0[7]),
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
        .R(reset_0));
  FDRE \waddr_reg[11] 
       (.C(AXI4_Lite_ACLK),
        .CE(aw_transfer),
        .D(AXI4_Lite_AWADDR[9]),
        .Q(sel0[9]),
        .R(reset_0));
  FDRE \waddr_reg[12] 
       (.C(AXI4_Lite_ACLK),
        .CE(aw_transfer),
        .D(AXI4_Lite_AWADDR[10]),
        .Q(sel0[10]),
        .R(reset_0));
  FDRE \waddr_reg[13] 
       (.C(AXI4_Lite_ACLK),
        .CE(aw_transfer),
        .D(AXI4_Lite_AWADDR[11]),
        .Q(sel0[11]),
        .R(reset_0));
  FDRE \waddr_reg[14] 
       (.C(AXI4_Lite_ACLK),
        .CE(aw_transfer),
        .D(AXI4_Lite_AWADDR[12]),
        .Q(sel0[12]),
        .R(reset_0));
  FDRE \waddr_reg[15] 
       (.C(AXI4_Lite_ACLK),
        .CE(aw_transfer),
        .D(AXI4_Lite_AWADDR[13]),
        .Q(sel0[13]),
        .R(reset_0));
  FDRE \waddr_reg[2] 
       (.C(AXI4_Lite_ACLK),
        .CE(aw_transfer),
        .D(AXI4_Lite_AWADDR[0]),
        .Q(sel0[0]),
        .R(reset_0));
  FDRE \waddr_reg[3] 
       (.C(AXI4_Lite_ACLK),
        .CE(aw_transfer),
        .D(AXI4_Lite_AWADDR[1]),
        .Q(sel0[1]),
        .R(reset_0));
  FDRE \waddr_reg[4] 
       (.C(AXI4_Lite_ACLK),
        .CE(aw_transfer),
        .D(AXI4_Lite_AWADDR[2]),
        .Q(sel0[2]),
        .R(reset_0));
  FDRE \waddr_reg[5] 
       (.C(AXI4_Lite_ACLK),
        .CE(aw_transfer),
        .D(AXI4_Lite_AWADDR[3]),
        .Q(sel0[3]),
        .R(reset_0));
  FDRE \waddr_reg[6] 
       (.C(AXI4_Lite_ACLK),
        .CE(aw_transfer),
        .D(AXI4_Lite_AWADDR[4]),
        .Q(sel0[4]),
        .R(reset_0));
  FDRE \waddr_reg[7] 
       (.C(AXI4_Lite_ACLK),
        .CE(aw_transfer),
        .D(AXI4_Lite_AWADDR[5]),
        .Q(sel0[5]),
        .R(reset_0));
  FDRE \waddr_reg[8] 
       (.C(AXI4_Lite_ACLK),
        .CE(aw_transfer),
        .D(AXI4_Lite_AWADDR[6]),
        .Q(sel0[6]),
        .R(reset_0));
  FDRE \waddr_reg[9] 
       (.C(AXI4_Lite_ACLK),
        .CE(aw_transfer),
        .D(AXI4_Lite_AWADDR[7]),
        .Q(sel0[7]),
        .R(reset_0));
  LUT2 #(
    .INIT(4'h8)) 
    \wdata[24]_i_1 
       (.I0(\FSM_onehot_axi_lite_wstate_reg[2]_0 [0]),
        .I1(AXI4_Lite_WVALID),
        .O(w_transfer));
  FDRE \wdata_reg[0] 
       (.C(AXI4_Lite_ACLK),
        .CE(w_transfer),
        .D(AXI4_Lite_WDATA[0]),
        .Q(Q[0]),
        .R(reset_0));
  FDRE \wdata_reg[10] 
       (.C(AXI4_Lite_ACLK),
        .CE(w_transfer),
        .D(AXI4_Lite_WDATA[10]),
        .Q(Q[10]),
        .R(reset_0));
  FDRE \wdata_reg[11] 
       (.C(AXI4_Lite_ACLK),
        .CE(w_transfer),
        .D(AXI4_Lite_WDATA[11]),
        .Q(Q[11]),
        .R(reset_0));
  FDRE \wdata_reg[12] 
       (.C(AXI4_Lite_ACLK),
        .CE(w_transfer),
        .D(AXI4_Lite_WDATA[12]),
        .Q(Q[12]),
        .R(reset_0));
  FDRE \wdata_reg[13] 
       (.C(AXI4_Lite_ACLK),
        .CE(w_transfer),
        .D(AXI4_Lite_WDATA[13]),
        .Q(Q[13]),
        .R(reset_0));
  FDRE \wdata_reg[14] 
       (.C(AXI4_Lite_ACLK),
        .CE(w_transfer),
        .D(AXI4_Lite_WDATA[14]),
        .Q(Q[14]),
        .R(reset_0));
  FDRE \wdata_reg[15] 
       (.C(AXI4_Lite_ACLK),
        .CE(w_transfer),
        .D(AXI4_Lite_WDATA[15]),
        .Q(Q[15]),
        .R(reset_0));
  FDRE \wdata_reg[16] 
       (.C(AXI4_Lite_ACLK),
        .CE(w_transfer),
        .D(AXI4_Lite_WDATA[16]),
        .Q(Q[16]),
        .R(reset_0));
  FDRE \wdata_reg[17] 
       (.C(AXI4_Lite_ACLK),
        .CE(w_transfer),
        .D(AXI4_Lite_WDATA[17]),
        .Q(Q[17]),
        .R(reset_0));
  FDRE \wdata_reg[18] 
       (.C(AXI4_Lite_ACLK),
        .CE(w_transfer),
        .D(AXI4_Lite_WDATA[18]),
        .Q(Q[18]),
        .R(reset_0));
  FDRE \wdata_reg[19] 
       (.C(AXI4_Lite_ACLK),
        .CE(w_transfer),
        .D(AXI4_Lite_WDATA[19]),
        .Q(Q[19]),
        .R(reset_0));
  FDRE \wdata_reg[1] 
       (.C(AXI4_Lite_ACLK),
        .CE(w_transfer),
        .D(AXI4_Lite_WDATA[1]),
        .Q(Q[1]),
        .R(reset_0));
  FDRE \wdata_reg[20] 
       (.C(AXI4_Lite_ACLK),
        .CE(w_transfer),
        .D(AXI4_Lite_WDATA[20]),
        .Q(Q[20]),
        .R(reset_0));
  FDRE \wdata_reg[21] 
       (.C(AXI4_Lite_ACLK),
        .CE(w_transfer),
        .D(AXI4_Lite_WDATA[21]),
        .Q(Q[21]),
        .R(reset_0));
  FDRE \wdata_reg[22] 
       (.C(AXI4_Lite_ACLK),
        .CE(w_transfer),
        .D(AXI4_Lite_WDATA[22]),
        .Q(Q[22]),
        .R(reset_0));
  FDRE \wdata_reg[23] 
       (.C(AXI4_Lite_ACLK),
        .CE(w_transfer),
        .D(AXI4_Lite_WDATA[23]),
        .Q(Q[23]),
        .R(reset_0));
  FDRE \wdata_reg[24] 
       (.C(AXI4_Lite_ACLK),
        .CE(w_transfer),
        .D(AXI4_Lite_WDATA[24]),
        .Q(Q[24]),
        .R(reset_0));
  FDRE \wdata_reg[2] 
       (.C(AXI4_Lite_ACLK),
        .CE(w_transfer),
        .D(AXI4_Lite_WDATA[2]),
        .Q(Q[2]),
        .R(reset_0));
  FDRE \wdata_reg[3] 
       (.C(AXI4_Lite_ACLK),
        .CE(w_transfer),
        .D(AXI4_Lite_WDATA[3]),
        .Q(Q[3]),
        .R(reset_0));
  FDRE \wdata_reg[4] 
       (.C(AXI4_Lite_ACLK),
        .CE(w_transfer),
        .D(AXI4_Lite_WDATA[4]),
        .Q(Q[4]),
        .R(reset_0));
  FDRE \wdata_reg[5] 
       (.C(AXI4_Lite_ACLK),
        .CE(w_transfer),
        .D(AXI4_Lite_WDATA[5]),
        .Q(Q[5]),
        .R(reset_0));
  FDRE \wdata_reg[6] 
       (.C(AXI4_Lite_ACLK),
        .CE(w_transfer),
        .D(AXI4_Lite_WDATA[6]),
        .Q(Q[6]),
        .R(reset_0));
  FDRE \wdata_reg[7] 
       (.C(AXI4_Lite_ACLK),
        .CE(w_transfer),
        .D(AXI4_Lite_WDATA[7]),
        .Q(Q[7]),
        .R(reset_0));
  FDRE \wdata_reg[8] 
       (.C(AXI4_Lite_ACLK),
        .CE(w_transfer),
        .D(AXI4_Lite_WDATA[8]),
        .Q(Q[8]),
        .R(reset_0));
  FDRE \wdata_reg[9] 
       (.C(AXI4_Lite_ACLK),
        .CE(w_transfer),
        .D(AXI4_Lite_WDATA[9]),
        .Q(Q[9]),
        .R(reset_0));
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
        .R(reset_0));
  (* SOFT_HLUTNM = "soft_lutpair0" *) 
  LUT5 #(
    .INIT(32'h20000000)) 
    \write_reg_Mode_AXI[1]_i_1 
       (.I0(\write_reg_Mode_AXI[1]_i_2_n_0 ),
        .I1(\write_reg_Mode_AXI[1]_i_3_n_0 ),
        .I2(\write_reg_Mode_AXI[1]_i_4_n_0 ),
        .I3(\write_reg_Mode_AXI[1]_i_5_n_0 ),
        .I4(\write_reg_Mode_AXI[1]_i_6_n_0 ),
        .O(E));
  LUT6 #(
    .INIT(64'h00002020000A202A)) 
    \write_reg_Mode_AXI[1]_i_2 
       (.I0(\AXI4_Lite_RDATA_tmp[30]_i_5_n_0 ),
        .I1(AXI4_Lite_ARADDR[2]),
        .I2(AXI4_Lite_ARVALID),
        .I3(sel0[2]),
        .I4(AXI4_Lite_ARADDR[1]),
        .I5(sel0[1]),
        .O(\write_reg_Mode_AXI[1]_i_2_n_0 ));
  LUT6 #(
    .INIT(64'hFFFFFF305050FF30)) 
    \write_reg_Mode_AXI[1]_i_3 
       (.I0(AXI4_Lite_ARADDR[4]),
        .I1(sel0[4]),
        .I2(\AXI4_Lite_RDATA_tmp[31]_i_5_n_0 ),
        .I3(sel0[5]),
        .I4(AXI4_Lite_ARVALID),
        .I5(AXI4_Lite_ARADDR[5]),
        .O(\write_reg_Mode_AXI[1]_i_3_n_0 ));
  LUT6 #(
    .INIT(64'hFFFFFF305050FF30)) 
    \write_reg_Mode_AXI[1]_i_4 
       (.I0(AXI4_Lite_ARADDR[7]),
        .I1(sel0[7]),
        .I2(\write_reg_Mode_AXI[1]_i_7_n_0 ),
        .I3(sel0[8]),
        .I4(AXI4_Lite_ARVALID),
        .I5(AXI4_Lite_ARADDR[8]),
        .O(\write_reg_Mode_AXI[1]_i_4_n_0 ));
  LUT6 #(
    .INIT(64'h303F101F30351015)) 
    \write_reg_Mode_AXI[1]_i_5 
       (.I0(\write_reg_Mode_AXI[1]_i_8_n_0 ),
        .I1(AXI4_Lite_ARADDR[11]),
        .I2(AXI4_Lite_ARVALID),
        .I3(sel0[11]),
        .I4(AXI4_Lite_ARADDR[10]),
        .I5(sel0[10]),
        .O(\write_reg_Mode_AXI[1]_i_5_n_0 ));
  LUT2 #(
    .INIT(4'h8)) 
    \write_reg_Mode_AXI[1]_i_6 
       (.I0(\AXI4_Lite_RDATA_tmp[30]_i_7_n_0 ),
        .I1(top_wr_enb),
        .O(\write_reg_Mode_AXI[1]_i_6_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair5" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \write_reg_Mode_AXI[1]_i_7 
       (.I0(AXI4_Lite_ARADDR[6]),
        .I1(AXI4_Lite_ARVALID),
        .I2(sel0[6]),
        .O(\write_reg_Mode_AXI[1]_i_7_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair9" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \write_reg_Mode_AXI[1]_i_8 
       (.I0(AXI4_Lite_ARADDR[9]),
        .I1(AXI4_Lite_ARVALID),
        .I2(sel0[9]),
        .O(\write_reg_Mode_AXI[1]_i_8_n_0 ));
  LUT5 #(
    .INIT(32'hBFFF8000)) 
    write_reg_PWM_en_AXI_i_1
       (.I0(Q[0]),
        .I1(write_reg_PWM_en_AXI_i_2_n_0),
        .I2(write_reg_PWM_en_AXI_i_3_n_0),
        .I3(\write_reg_Mode_AXI[1]_i_6_n_0 ),
        .I4(write_PWM_en_AXI),
        .O(\wdata_reg[0]_1 ));
  (* SOFT_HLUTNM = "soft_lutpair5" *) 
  LUT5 #(
    .INIT(32'h000ACC0A)) 
    write_reg_PWM_en_AXI_i_2
       (.I0(sel0[6]),
        .I1(AXI4_Lite_ARADDR[6]),
        .I2(sel0[9]),
        .I3(AXI4_Lite_ARVALID),
        .I4(AXI4_Lite_ARADDR[9]),
        .O(write_reg_PWM_en_AXI_i_2_n_0));
  LUT6 #(
    .INIT(64'h0044034700000000)) 
    write_reg_PWM_en_AXI_i_3
       (.I0(AXI4_Lite_ARADDR[3]),
        .I1(AXI4_Lite_ARVALID),
        .I2(sel0[3]),
        .I3(AXI4_Lite_ARADDR[0]),
        .I4(sel0[0]),
        .I5(write_reg_axi_enable_i_2_n_0),
        .O(write_reg_PWM_en_AXI_i_3_n_0));
  LUT6 #(
    .INIT(64'h0010000000000000)) 
    \write_reg_PWM_min_pulse_width_AXI[17]_i_1 
       (.I0(\AXI4_Lite_RDATA_tmp[30]_i_4_n_0 ),
        .I1(\AXI4_Lite_RDATA_tmp[30]_i_5_n_0 ),
        .I2(\AXI4_Lite_RDATA_tmp[30]_i_3_n_0 ),
        .I3(\write_reg_Mode_AXI[1]_i_3_n_0 ),
        .I4(\write_reg_PWM_min_pulse_width_AXI[17]_i_2_n_0 ),
        .I5(\write_reg_Mode_AXI[1]_i_6_n_0 ),
        .O(\AXI4_Lite_ARADDR[3]_2 ));
  LUT6 #(
    .INIT(64'h00E200FF00000000)) 
    \write_reg_PWM_min_pulse_width_AXI[17]_i_2 
       (.I0(sel0[10]),
        .I1(AXI4_Lite_ARVALID),
        .I2(AXI4_Lite_ARADDR[10]),
        .I3(\write_reg_PWM_min_pulse_width_AXI[17]_i_3_n_0 ),
        .I4(\write_reg_Mode_AXI[1]_i_8_n_0 ),
        .I5(\write_reg_Mode_AXI[1]_i_4_n_0 ),
        .O(\write_reg_PWM_min_pulse_width_AXI[17]_i_2_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair2" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \write_reg_PWM_min_pulse_width_AXI[17]_i_3 
       (.I0(AXI4_Lite_ARADDR[11]),
        .I1(AXI4_Lite_ARVALID),
        .I2(sel0[11]),
        .O(\write_reg_PWM_min_pulse_width_AXI[17]_i_3_n_0 ));
  LUT6 #(
    .INIT(64'h0800000000000000)) 
    \write_reg_Scal_T_carrier_AXI[24]_i_1 
       (.I0(\write_reg_Scal_f_carrier_AXI[24]_i_3_n_0 ),
        .I1(\write_reg_Scal_f_carrier_AXI[24]_i_2_n_0 ),
        .I2(\write_reg_Mode_AXI[1]_i_3_n_0 ),
        .I3(\write_reg_Mode_AXI[1]_i_4_n_0 ),
        .I4(\write_reg_Mode_AXI[1]_i_5_n_0 ),
        .I5(\write_reg_Mode_AXI[1]_i_6_n_0 ),
        .O(\waddr_reg[3]_0 ));
  LUT6 #(
    .INIT(64'h0400000000000000)) 
    \write_reg_Scal_f_carrier_AXI[24]_i_1 
       (.I0(\write_reg_Scal_f_carrier_AXI[24]_i_2_n_0 ),
        .I1(\write_reg_Scal_f_carrier_AXI[24]_i_3_n_0 ),
        .I2(\write_reg_Mode_AXI[1]_i_3_n_0 ),
        .I3(\write_reg_Mode_AXI[1]_i_4_n_0 ),
        .I4(\write_reg_Mode_AXI[1]_i_5_n_0 ),
        .I5(\write_reg_Mode_AXI[1]_i_6_n_0 ),
        .O(\AXI4_Lite_ARADDR[3]_3 ));
  LUT6 #(
    .INIT(64'hFFFFFFC0A0A0FFC0)) 
    \write_reg_Scal_f_carrier_AXI[24]_i_2 
       (.I0(AXI4_Lite_ARADDR[1]),
        .I1(sel0[1]),
        .I2(\AXI4_Lite_RDATA_tmp[30]_i_5_n_0 ),
        .I3(sel0[2]),
        .I4(AXI4_Lite_ARVALID),
        .I5(AXI4_Lite_ARADDR[2]),
        .O(\write_reg_Scal_f_carrier_AXI[24]_i_2_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair3" *) 
  LUT5 #(
    .INIT(32'h000ACC0A)) 
    \write_reg_Scal_f_carrier_AXI[24]_i_3 
       (.I0(sel0[1]),
        .I1(AXI4_Lite_ARADDR[1]),
        .I2(sel0[2]),
        .I3(AXI4_Lite_ARVALID),
        .I4(AXI4_Lite_ARADDR[2]),
        .O(\write_reg_Scal_f_carrier_AXI[24]_i_3_n_0 ));
  LUT6 #(
    .INIT(64'h0002000000000000)) 
    \write_reg_TriState_HB1_AXI[1]_i_1 
       (.I0(\write_reg_Mode_AXI[1]_i_3_n_0 ),
        .I1(\AXI4_Lite_RDATA_tmp[30]_i_3_n_0 ),
        .I2(\AXI4_Lite_RDATA_tmp[30]_i_5_n_0 ),
        .I3(\AXI4_Lite_RDATA_tmp[30]_i_4_n_0 ),
        .I4(\write_reg_Mode_AXI[1]_i_6_n_0 ),
        .I5(\write_reg_PWM_min_pulse_width_AXI[17]_i_2_n_0 ),
        .O(\AXI4_Lite_ARADDR[6]_0 ));
  (* SOFT_HLUTNM = "soft_lutpair0" *) 
  LUT5 #(
    .INIT(32'h80000000)) 
    \write_reg_TriState_HB2_AXI[1]_i_1 
       (.I0(\write_reg_Mode_AXI[1]_i_3_n_0 ),
        .I1(\write_reg_Mode_AXI[1]_i_2_n_0 ),
        .I2(\write_reg_Mode_AXI[1]_i_6_n_0 ),
        .I3(\write_reg_Mode_AXI[1]_i_5_n_0 ),
        .I4(\write_reg_Mode_AXI[1]_i_4_n_0 ),
        .O(\AXI4_Lite_ARADDR[6] ));
  LUT6 #(
    .INIT(64'h4000000000000000)) 
    \write_reg_TriState_HB3_AXI[1]_i_1 
       (.I0(\write_reg_Scal_f_carrier_AXI[24]_i_2_n_0 ),
        .I1(\write_reg_Mode_AXI[1]_i_3_n_0 ),
        .I2(\write_reg_Scal_f_carrier_AXI[24]_i_3_n_0 ),
        .I3(\write_reg_Mode_AXI[1]_i_6_n_0 ),
        .I4(\write_reg_Mode_AXI[1]_i_5_n_0 ),
        .I5(\write_reg_Mode_AXI[1]_i_4_n_0 ),
        .O(\AXI4_Lite_ARADDR[3] ));
  LUT5 #(
    .INIT(32'hBFFF8000)) 
    write_reg_axi_enable_i_1
       (.I0(Q[0]),
        .I1(write_reg_axi_enable_i_2_n_0),
        .I2(write_reg_axi_enable_i_3_n_0),
        .I3(\write_reg_Mode_AXI[1]_i_6_n_0 ),
        .I4(CEA1),
        .O(\wdata_reg[0]_0 ));
  (* SOFT_HLUTNM = "soft_lutpair4" *) 
  LUT5 #(
    .INIT(32'h00053305)) 
    write_reg_axi_enable_i_2
       (.I0(sel0[1]),
        .I1(AXI4_Lite_ARADDR[1]),
        .I2(sel0[2]),
        .I3(AXI4_Lite_ARVALID),
        .I4(AXI4_Lite_ARADDR[2]),
        .O(write_reg_axi_enable_i_2_n_0));
  LUT6 #(
    .INIT(64'h0004000000040404)) 
    write_reg_axi_enable_i_3
       (.I0(\AXI4_Lite_RDATA_tmp[31]_i_5_n_0 ),
        .I1(\AXI4_Lite_RDATA_tmp[30]_i_5_n_0 ),
        .I2(\write_reg_Mode_AXI[1]_i_8_n_0 ),
        .I3(AXI4_Lite_ARADDR[6]),
        .I4(AXI4_Lite_ARVALID),
        .I5(sel0[6]),
        .O(write_reg_axi_enable_i_3_n_0));
  LUT6 #(
    .INIT(64'h0020000000000000)) 
    \write_reg_m_u1_norm_AXI[13]_i_1 
       (.I0(\AXI4_Lite_RDATA_tmp[30]_i_3_n_0 ),
        .I1(\AXI4_Lite_RDATA_tmp[30]_i_4_n_0 ),
        .I2(\AXI4_Lite_RDATA_tmp[30]_i_5_n_0 ),
        .I3(\write_reg_Mode_AXI[1]_i_3_n_0 ),
        .I4(\write_reg_PWM_min_pulse_width_AXI[17]_i_2_n_0 ),
        .I5(\write_reg_Mode_AXI[1]_i_6_n_0 ),
        .O(\AXI4_Lite_ARADDR[4] ));
  LUT6 #(
    .INIT(64'h0020000000000000)) 
    \write_reg_m_u2_norm_AXI[13]_i_1 
       (.I0(\AXI4_Lite_RDATA_tmp[30]_i_4_n_0 ),
        .I1(\AXI4_Lite_RDATA_tmp[30]_i_5_n_0 ),
        .I2(\AXI4_Lite_RDATA_tmp[30]_i_3_n_0 ),
        .I3(\write_reg_Mode_AXI[1]_i_3_n_0 ),
        .I4(\write_reg_PWM_min_pulse_width_AXI[17]_i_2_n_0 ),
        .I5(\write_reg_Mode_AXI[1]_i_6_n_0 ),
        .O(\AXI4_Lite_ARADDR[3]_1 ));
  LUT6 #(
    .INIT(64'h0080000000000000)) 
    \write_reg_m_u3_norm_AXI[13]_i_1 
       (.I0(\AXI4_Lite_RDATA_tmp[30]_i_4_n_0 ),
        .I1(\AXI4_Lite_RDATA_tmp[30]_i_3_n_0 ),
        .I2(\AXI4_Lite_RDATA_tmp[30]_i_5_n_0 ),
        .I3(\write_reg_Mode_AXI[1]_i_3_n_0 ),
        .I4(\write_reg_PWM_min_pulse_width_AXI[17]_i_2_n_0 ),
        .I5(\write_reg_Mode_AXI[1]_i_6_n_0 ),
        .O(\AXI4_Lite_ARADDR[3]_0 ));
endmodule

module zusys_PWM_and_SS_control_V_0_2_PWM_and_SS_control_V3_ip_dut
   (PWM_en_AXI_1,
    PWM_en_rd_AXI_sig,
    PWM_enb_out,
    Triangular_Max,
    Triangular_Min,
    \f_carrier_kHz_AXI_2_reg[24] ,
    DI,
    \HDL_Counter2_count_reg[2] ,
    \HDL_Counter2_count_reg[3] ,
    \HDL_Counter2_count_reg[4] ,
    \HDL_Counter2_count_reg[5] ,
    \HDL_Counter2_count_reg[6] ,
    \HDL_Counter2_count_reg[7] ,
    S,
    \HDL_Counter2_count_reg[0] ,
    Q,
    \min_pulse_width_AXI_2_reg[17] ,
    \reduced_reg_1_reg[1][1] ,
    SS0_OUT,
    SS1_OUT,
    SS2_OUT,
    SS3_OUT,
    SS4_OUT,
    SS5_OUT,
    reset,
    E,
    IPCORE_CLK,
    CEB2,
    B,
    D,
    write_PWM_en_AXI,
    CO,
    \T_carrier_us_AXI_1_reg[24] ,
    \min_pulse_width_AXI_1_reg[17] ,
    \reduced_reg_1_reg[0][1] ,
    SS0_IN_External,
    \reduced_reg_reg[0][1] ,
    SS1_IN_External,
    SS2_IN_External,
    \reduced_reg_2_reg[0][1] ,
    SS3_IN_External,
    SS4_IN_External,
    \reduced_reg_3_reg[0][1] ,
    SS5_IN_External,
    \U1_norm_1_reg[13] ,
    m_u1_norm,
    \U2_norm_1_reg[13] ,
    m_u2_norm,
    \U3_norm_1_reg[13] ,
    m_u3_norm);
  output PWM_en_AXI_1;
  output PWM_en_rd_AXI_sig;
  output PWM_enb_out;
  output Triangular_Max;
  output Triangular_Min;
  output [24:0]\f_carrier_kHz_AXI_2_reg[24] ;
  output [1:0]DI;
  output \HDL_Counter2_count_reg[2] ;
  output \HDL_Counter2_count_reg[3] ;
  output \HDL_Counter2_count_reg[4] ;
  output \HDL_Counter2_count_reg[5] ;
  output \HDL_Counter2_count_reg[6] ;
  output \HDL_Counter2_count_reg[7] ;
  output [7:0]S;
  output [0:0]\HDL_Counter2_count_reg[0] ;
  output [24:0]Q;
  output [17:0]\min_pulse_width_AXI_2_reg[17] ;
  output [1:0]\reduced_reg_1_reg[1][1] ;
  output SS0_OUT;
  output SS1_OUT;
  output SS2_OUT;
  output SS3_OUT;
  output SS4_OUT;
  output SS5_OUT;
  input reset;
  input [0:0]E;
  input IPCORE_CLK;
  input CEB2;
  input [7:0]B;
  input [24:0]D;
  input write_PWM_en_AXI;
  input [0:0]CO;
  input [24:0]\T_carrier_us_AXI_1_reg[24] ;
  input [17:0]\min_pulse_width_AXI_1_reg[17] ;
  input [1:0]\reduced_reg_1_reg[0][1] ;
  input SS0_IN_External;
  input [1:0]\reduced_reg_reg[0][1] ;
  input SS1_IN_External;
  input SS2_IN_External;
  input [1:0]\reduced_reg_2_reg[0][1] ;
  input SS3_IN_External;
  input SS4_IN_External;
  input [1:0]\reduced_reg_3_reg[0][1] ;
  input SS5_IN_External;
  input [13:0]\U1_norm_1_reg[13] ;
  input [13:0]m_u1_norm;
  input [13:0]\U2_norm_1_reg[13] ;
  input [13:0]m_u2_norm;
  input [13:0]\U3_norm_1_reg[13] ;
  input [13:0]m_u3_norm;

  wire [7:0]B;
  wire CEB2;
  wire [0:0]CO;
  wire [24:0]D;
  wire [1:0]DI;
  wire [0:0]E;
  wire [0:0]\HDL_Counter2_count_reg[0] ;
  wire \HDL_Counter2_count_reg[2] ;
  wire \HDL_Counter2_count_reg[3] ;
  wire \HDL_Counter2_count_reg[4] ;
  wire \HDL_Counter2_count_reg[5] ;
  wire \HDL_Counter2_count_reg[6] ;
  wire \HDL_Counter2_count_reg[7] ;
  wire IPCORE_CLK;
  wire PWM_en_AXI_1;
  wire PWM_en_rd_AXI_sig;
  wire PWM_enb_out;
  wire [24:0]Q;
  wire [7:0]S;
  wire SS0_IN_External;
  wire SS0_OUT;
  wire SS1_IN_External;
  wire SS1_OUT;
  wire SS2_IN_External;
  wire SS2_OUT;
  wire SS3_IN_External;
  wire SS3_OUT;
  wire SS4_IN_External;
  wire SS4_OUT;
  wire SS5_IN_External;
  wire SS5_OUT;
  wire [24:0]\T_carrier_us_AXI_1_reg[24] ;
  wire Triangular_Max;
  wire Triangular_Min;
  wire [13:0]\U1_norm_1_reg[13] ;
  wire [13:0]\U2_norm_1_reg[13] ;
  wire [13:0]\U3_norm_1_reg[13] ;
  wire [24:0]\f_carrier_kHz_AXI_2_reg[24] ;
  wire [13:0]m_u1_norm;
  wire [13:0]m_u2_norm;
  wire [13:0]m_u3_norm;
  wire [17:0]\min_pulse_width_AXI_1_reg[17] ;
  wire [17:0]\min_pulse_width_AXI_2_reg[17] ;
  wire [1:0]\reduced_reg_1_reg[0][1] ;
  wire [1:0]\reduced_reg_1_reg[1][1] ;
  wire [1:0]\reduced_reg_2_reg[0][1] ;
  wire [1:0]\reduced_reg_3_reg[0][1] ;
  wire [1:0]\reduced_reg_reg[0][1] ;
  wire reset;
  wire write_PWM_en_AXI;

  zusys_PWM_and_SS_control_V_0_2_PWM_and_SS_control_V3_ip_src_PWM_and_Switching_Signal_Control u_PWM_and_SS_control_V3_ip_src_PWM_and_Switching_Signal_Control
       (.B(B),
        .CEB2(CEB2),
        .CO(CO),
        .D(D),
        .DI(DI[1]),
        .E(E),
        .\HDL_Counter2_count_reg[0] (DI[0]),
        .\HDL_Counter2_count_reg[0]_0 (\HDL_Counter2_count_reg[0] ),
        .\HDL_Counter2_count_reg[2] (\HDL_Counter2_count_reg[2] ),
        .\HDL_Counter2_count_reg[3] (\HDL_Counter2_count_reg[3] ),
        .\HDL_Counter2_count_reg[4] (\HDL_Counter2_count_reg[4] ),
        .\HDL_Counter2_count_reg[5] (\HDL_Counter2_count_reg[5] ),
        .\HDL_Counter2_count_reg[6] (\HDL_Counter2_count_reg[6] ),
        .\HDL_Counter2_count_reg[7] (\HDL_Counter2_count_reg[7] ),
        .IPCORE_CLK(IPCORE_CLK),
        .PWM_en_AXI_1_reg(PWM_en_AXI_1),
        .PWM_en_rd_AXI_sig(PWM_en_rd_AXI_sig),
        .PWM_enb_out(PWM_enb_out),
        .\Product_mul_temp[-1111111103] (\f_carrier_kHz_AXI_2_reg[24] [8]),
        .\Product_mul_temp[-1111111104] (\f_carrier_kHz_AXI_2_reg[24] [7]),
        .\Product_mul_temp[-1111111105] (\f_carrier_kHz_AXI_2_reg[24] [6]),
        .\Product_mul_temp[-1111111106] (\f_carrier_kHz_AXI_2_reg[24] [5]),
        .\Product_mul_temp[-1111111107] (\f_carrier_kHz_AXI_2_reg[24] [4]),
        .\Product_mul_temp[-1111111108] (\f_carrier_kHz_AXI_2_reg[24] [3]),
        .\Product_mul_temp[-1111111109] (\f_carrier_kHz_AXI_2_reg[24] [2]),
        .\Product_mul_temp[-1111111110] (\f_carrier_kHz_AXI_2_reg[24] [1]),
        .\Product_mul_temp[-1111111111] (\f_carrier_kHz_AXI_2_reg[24] [0]),
        .Q(Q),
        .S(S),
        .SS0_IN_External(SS0_IN_External),
        .SS0_OUT(SS0_OUT),
        .SS1_IN_External(SS1_IN_External),
        .SS1_OUT(SS1_OUT),
        .SS2_IN_External(SS2_IN_External),
        .SS2_OUT(SS2_OUT),
        .SS3_IN_External(SS3_IN_External),
        .SS3_OUT(SS3_OUT),
        .SS4_IN_External(SS4_IN_External),
        .SS4_OUT(SS4_OUT),
        .SS5_IN_External(SS5_IN_External),
        .SS5_OUT(SS5_OUT),
        .\T_carrier_us_AXI_1_reg[24] (\T_carrier_us_AXI_1_reg[24] ),
        .Triangular_Max(Triangular_Max),
        .Triangular_Min(Triangular_Min),
        .\U1_norm_1_reg[13] (\U1_norm_1_reg[13] ),
        .\U2_norm_1_reg[13] (\U2_norm_1_reg[13] ),
        .\U3_norm_1_reg[13] (\U3_norm_1_reg[13] ),
        .\f_carrier_kHz_AXI_2_reg[24] (\f_carrier_kHz_AXI_2_reg[24] [24:9]),
        .m_u1_norm(m_u1_norm),
        .m_u2_norm(m_u2_norm),
        .m_u3_norm(m_u3_norm),
        .\min_pulse_width_AXI_1_reg[17] (\min_pulse_width_AXI_1_reg[17] ),
        .\min_pulse_width_AXI_2_reg[17] (\min_pulse_width_AXI_2_reg[17] ),
        .\reduced_reg_1_reg[0][1] (\reduced_reg_1_reg[0][1] ),
        .\reduced_reg_1_reg[1][1] (\reduced_reg_1_reg[1][1] ),
        .\reduced_reg_2_reg[0][1] (\reduced_reg_2_reg[0][1] ),
        .\reduced_reg_3_reg[0][1] (\reduced_reg_3_reg[0][1] ),
        .\reduced_reg_reg[0][1] (\reduced_reg_reg[0][1] ),
        .reset(reset),
        .write_PWM_en_AXI(write_PWM_en_AXI));
endmodule

module zusys_PWM_and_SS_control_V_0_2_PWM_and_SS_control_V3_ip_src_Counter_Ctrl
   (P,
    \Product_mul_temp[-1111111111]_0 ,
    \Product_mul_temp[-1111111110]_0 ,
    \Product_mul_temp[-1111111109]_0 ,
    \Product_mul_temp[-1111111108]_0 ,
    \Product_mul_temp[-1111111107]_0 ,
    \Product_mul_temp[-1111111106]_0 ,
    \Product_mul_temp[-1111111105]_0 ,
    \Product_mul_temp[-1111111104]_0 ,
    \Product_mul_temp[-1111111103]_0 ,
    \Product_mul_temp[-1111111102]_0 ,
    CO,
    O,
    DI,
    \HDL_Counter2_count_reg[0] ,
    \HDL_Counter2_count_reg[0]_0 ,
    \HDL_Counter2_count_reg[15] ,
    \HDL_Counter2_count_reg[0]_1 ,
    \HDL_Counter2_count_reg[0]_2 ,
    \Delay2_out1_reg[12] ,
    \U3_norm_1_reg[13] ,
    Allow_assymetrical_anew_reference_value__0,
    \Delay2_out1_reg[12]_0 ,
    \U3_norm_1_reg[13]_0 ,
    \U3_norm_1_reg[12] ,
    \U3_norm_1_reg[12]_0 ,
    \Delay2_out1_reg[12]_1 ,
    \U3_norm_1_reg[10] ,
    \U3_norm_1_reg[9] ,
    \Delay1_out1_reg[12] ,
    \U2_norm_1_reg[13] ,
    \Delay1_out1_reg[12]_0 ,
    \U2_norm_1_reg[13]_0 ,
    \U2_norm_1_reg[12] ,
    \U2_norm_1_reg[12]_0 ,
    \Delay1_out1_reg[12]_1 ,
    \U2_norm_1_reg[10] ,
    \U2_norm_1_reg[9] ,
    \Delay_out1_reg[12] ,
    Relational_Operator_1_cast,
    \Delay_out1_reg[12]_0 ,
    \U1_norm_1_reg[12] ,
    \U1_norm_1_reg[11] ,
    \U1_norm_1_reg[10] ,
    \U1_norm_1_reg[9] ,
    Switch6_out1,
    \Delay2_out1_reg[12]_2 ,
    \Delay1_out1_reg[12]_2 ,
    \Delay_out1_reg[12]_1 ,
    \Delay_out1_reg[12]_2 ,
    reset,
    E,
    IPCORE_CLK,
    CEB2,
    B,
    D,
    Q,
    S,
    HDL_Counter2_count_reg_7_sp_1,
    HDL_Counter2_count_reg,
    Delay6_out1_reg_0,
    \HDL_Counter2_count_reg[7]_0 ,
    \HDL_Counter2_count_reg[7]_1 ,
    \HDL_Counter2_count_reg[7]_2 ,
    \HDL_Counter2_count_reg[7]_3 ,
    Delay6_out1_reg_1,
    Add_out1,
    \Delay2_out1_reg[13] ,
    \Delay2_out1_reg[13]_0 ,
    Switch9_out12_carry,
    Switch9_out12_carry_0,
    \Delay2_out1_reg[13]_1 ,
    Saturation_out1,
    \Delay1_out1_reg[13] ,
    \Delay1_out1_reg[13]_0 ,
    Switch8_out12_carry,
    Switch8_out12_carry_0,
    \Delay_out1_reg[13] ,
    \Delay_out1_reg[13]_0 ,
    Switch7_out12_carry,
    Switch7_out12_carry_0,
    Switch7_out12_carry_i_6,
    Switch7_out12_carry_i_6_0,
    Switch7_out12_carry_i_6_1,
    Logical_Operator_out10_carry__0_0);
  output [5:0]P;
  output \Product_mul_temp[-1111111111]_0 ;
  output \Product_mul_temp[-1111111110]_0 ;
  output \Product_mul_temp[-1111111109]_0 ;
  output \Product_mul_temp[-1111111108]_0 ;
  output \Product_mul_temp[-1111111107]_0 ;
  output \Product_mul_temp[-1111111106]_0 ;
  output \Product_mul_temp[-1111111105]_0 ;
  output \Product_mul_temp[-1111111104]_0 ;
  output \Product_mul_temp[-1111111103]_0 ;
  output [0:0]\Product_mul_temp[-1111111102]_0 ;
  output [0:0]CO;
  output [7:0]O;
  output [0:0]DI;
  output [7:0]\HDL_Counter2_count_reg[0] ;
  output [3:0]\HDL_Counter2_count_reg[0]_0 ;
  output [7:0]\HDL_Counter2_count_reg[15] ;
  output [0:0]\HDL_Counter2_count_reg[0]_1 ;
  output [1:0]\HDL_Counter2_count_reg[0]_2 ;
  output [6:0]\Delay2_out1_reg[12] ;
  output \U3_norm_1_reg[13] ;
  output Allow_assymetrical_anew_reference_value__0;
  output [6:0]\Delay2_out1_reg[12]_0 ;
  output [1:0]\U3_norm_1_reg[13]_0 ;
  output [0:0]\U3_norm_1_reg[12] ;
  output [12:0]\U3_norm_1_reg[12]_0 ;
  output [6:0]\Delay2_out1_reg[12]_1 ;
  output [7:0]\U3_norm_1_reg[10] ;
  output [7:0]\U3_norm_1_reg[9] ;
  output [6:0]\Delay1_out1_reg[12] ;
  output \U2_norm_1_reg[13] ;
  output [6:0]\Delay1_out1_reg[12]_0 ;
  output [1:0]\U2_norm_1_reg[13]_0 ;
  output [0:0]\U2_norm_1_reg[12] ;
  output [12:0]\U2_norm_1_reg[12]_0 ;
  output [6:0]\Delay1_out1_reg[12]_1 ;
  output [7:0]\U2_norm_1_reg[10] ;
  output [7:0]\U2_norm_1_reg[9] ;
  output [6:0]\Delay_out1_reg[12] ;
  output [13:0]Relational_Operator_1_cast;
  output [6:0]\Delay_out1_reg[12]_0 ;
  output [0:0]\U1_norm_1_reg[12] ;
  output [0:0]\U1_norm_1_reg[11] ;
  output [5:0]\U1_norm_1_reg[10] ;
  output [5:0]\U1_norm_1_reg[9] ;
  output Switch6_out1;
  output [0:0]\Delay2_out1_reg[12]_2 ;
  output [0:0]\Delay1_out1_reg[12]_2 ;
  output [0:0]\Delay_out1_reg[12]_1 ;
  output [0:0]\Delay_out1_reg[12]_2 ;
  input reset;
  input [0:0]E;
  input IPCORE_CLK;
  input CEB2;
  input [15:0]B;
  input [24:0]D;
  input [9:0]Q;
  input [0:0]S;
  input HDL_Counter2_count_reg_7_sp_1;
  input [12:0]HDL_Counter2_count_reg;
  input Delay6_out1_reg_0;
  input \HDL_Counter2_count_reg[7]_0 ;
  input \HDL_Counter2_count_reg[7]_1 ;
  input \HDL_Counter2_count_reg[7]_2 ;
  input \HDL_Counter2_count_reg[7]_3 ;
  input Delay6_out1_reg_1;
  input [13:0]Add_out1;
  input [13:0]\Delay2_out1_reg[13] ;
  input [13:0]\Delay2_out1_reg[13]_0 ;
  input [0:0]Switch9_out12_carry;
  input [0:0]Switch9_out12_carry_0;
  input \Delay2_out1_reg[13]_1 ;
  input [12:0]Saturation_out1;
  input [13:0]\Delay1_out1_reg[13] ;
  input [13:0]\Delay1_out1_reg[13]_0 ;
  input [0:0]Switch8_out12_carry;
  input [0:0]Switch8_out12_carry_0;
  input [13:0]\Delay_out1_reg[13] ;
  input [13:0]\Delay_out1_reg[13]_0 ;
  input [0:0]Switch7_out12_carry;
  input [0:0]Switch7_out12_carry_0;
  input Switch7_out12_carry_i_6;
  input Switch7_out12_carry_i_6_0;
  input Switch7_out12_carry_i_6_1;
  input [24:0]Logical_Operator_out10_carry__0_0;

  wire [13:0]Add_out1;
  wire Allow_assymetrical_anew_reference_value__0;
  wire [15:0]B;
  wire CEB2;
  wire [0:0]CO;
  wire [24:0]D;
  wire [0:0]DI;
  wire [6:0]\Delay1_out1_reg[12] ;
  wire [6:0]\Delay1_out1_reg[12]_0 ;
  wire [6:0]\Delay1_out1_reg[12]_1 ;
  wire [0:0]\Delay1_out1_reg[12]_2 ;
  wire [13:0]\Delay1_out1_reg[13] ;
  wire [13:0]\Delay1_out1_reg[13]_0 ;
  wire [6:0]\Delay2_out1_reg[12] ;
  wire [6:0]\Delay2_out1_reg[12]_0 ;
  wire [6:0]\Delay2_out1_reg[12]_1 ;
  wire [0:0]\Delay2_out1_reg[12]_2 ;
  wire [13:0]\Delay2_out1_reg[13] ;
  wire [13:0]\Delay2_out1_reg[13]_0 ;
  wire \Delay2_out1_reg[13]_1 ;
  wire Delay6_out1;
  wire Delay6_out1_i_2_n_0;
  wire Delay6_out1_i_3_n_0;
  wire Delay6_out1_i_4_n_0;
  wire Delay6_out1_i_5_n_0;
  wire Delay6_out1_i_6_n_0;
  wire Delay6_out1_reg_0;
  wire Delay6_out1_reg_1;
  wire [6:0]\Delay_out1_reg[12] ;
  wire [6:0]\Delay_out1_reg[12]_0 ;
  wire [0:0]\Delay_out1_reg[12]_1 ;
  wire [0:0]\Delay_out1_reg[12]_2 ;
  wire [13:0]\Delay_out1_reg[13] ;
  wire [13:0]\Delay_out1_reg[13]_0 ;
  wire [0:0]E;
  wire \HDL_Counter2_count[0]_i_2_n_0 ;
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
  wire [0:0]HDL_Counter2_count_next;
  wire [12:0]HDL_Counter2_count_reg;
  wire [7:0]\HDL_Counter2_count_reg[0] ;
  wire [3:0]\HDL_Counter2_count_reg[0]_0 ;
  wire [0:0]\HDL_Counter2_count_reg[0]_1 ;
  wire [1:0]\HDL_Counter2_count_reg[0]_2 ;
  wire \HDL_Counter2_count_reg[0]_i_1_n_0 ;
  wire \HDL_Counter2_count_reg[0]_i_1_n_1 ;
  wire \HDL_Counter2_count_reg[0]_i_1_n_2 ;
  wire \HDL_Counter2_count_reg[0]_i_1_n_3 ;
  wire \HDL_Counter2_count_reg[0]_i_1_n_4 ;
  wire \HDL_Counter2_count_reg[0]_i_1_n_5 ;
  wire \HDL_Counter2_count_reg[0]_i_1_n_6 ;
  wire \HDL_Counter2_count_reg[0]_i_1_n_7 ;
  wire [7:0]\HDL_Counter2_count_reg[15] ;
  wire \HDL_Counter2_count_reg[16]_i_1_n_5 ;
  wire \HDL_Counter2_count_reg[16]_i_1_n_6 ;
  wire \HDL_Counter2_count_reg[16]_i_1_n_7 ;
  wire \HDL_Counter2_count_reg[7]_0 ;
  wire \HDL_Counter2_count_reg[7]_1 ;
  wire \HDL_Counter2_count_reg[7]_2 ;
  wire \HDL_Counter2_count_reg[7]_3 ;
  wire \HDL_Counter2_count_reg[8]_i_1_n_0 ;
  wire \HDL_Counter2_count_reg[8]_i_1_n_1 ;
  wire \HDL_Counter2_count_reg[8]_i_1_n_2 ;
  wire \HDL_Counter2_count_reg[8]_i_1_n_3 ;
  wire \HDL_Counter2_count_reg[8]_i_1_n_4 ;
  wire \HDL_Counter2_count_reg[8]_i_1_n_5 ;
  wire \HDL_Counter2_count_reg[8]_i_1_n_6 ;
  wire \HDL_Counter2_count_reg[8]_i_1_n_7 ;
  wire HDL_Counter2_count_reg_7_sn_1;
  wire IPCORE_CLK;
  wire [24:0]Logical_Operator_out10_carry__0_0;
  wire Logical_Operator_out10_carry__0_i_1_n_0;
  wire Logical_Operator_out10_carry__0_i_2_n_0;
  wire Logical_Operator_out10_carry__0_i_3_n_0;
  wire Logical_Operator_out10_carry__0_i_4_n_0;
  wire Logical_Operator_out10_carry__0_i_5_n_0;
  wire Logical_Operator_out10_carry__0_i_6_n_0;
  wire Logical_Operator_out10_carry__0_i_7_n_0;
  wire Logical_Operator_out10_carry__0_n_4;
  wire Logical_Operator_out10_carry__0_n_5;
  wire Logical_Operator_out10_carry__0_n_6;
  wire Logical_Operator_out10_carry__0_n_7;
  wire Logical_Operator_out10_carry_i_10__1_n_0;
  wire Logical_Operator_out10_carry_i_11__2_n_0;
  wire Logical_Operator_out10_carry_i_12__2_n_0;
  wire Logical_Operator_out10_carry_i_13__2_n_0;
  wire Logical_Operator_out10_carry_i_14__2_n_0;
  wire Logical_Operator_out10_carry_i_15__2_n_0;
  wire Logical_Operator_out10_carry_i_16__0_n_0;
  wire Logical_Operator_out10_carry_i_1_n_0;
  wire Logical_Operator_out10_carry_i_2__1_n_0;
  wire Logical_Operator_out10_carry_i_3__2_n_0;
  wire Logical_Operator_out10_carry_i_4__2_n_0;
  wire Logical_Operator_out10_carry_i_5__2_n_0;
  wire Logical_Operator_out10_carry_i_6__2_n_0;
  wire Logical_Operator_out10_carry_i_7__2_n_0;
  wire Logical_Operator_out10_carry_i_8__0_n_0;
  wire Logical_Operator_out10_carry_i_9_n_0;
  wire Logical_Operator_out10_carry_n_0;
  wire Logical_Operator_out10_carry_n_1;
  wire Logical_Operator_out10_carry_n_2;
  wire Logical_Operator_out10_carry_n_3;
  wire Logical_Operator_out10_carry_n_4;
  wire Logical_Operator_out10_carry_n_5;
  wire Logical_Operator_out10_carry_n_6;
  wire Logical_Operator_out10_carry_n_7;
  wire [7:0]O;
  wire [5:0]P;
  wire Period_CenterMax0_carry_i_1_n_0;
  wire Period_CenterMax0_carry_i_2_n_0;
  wire Period_CenterMax0_carry_i_3_n_0;
  wire Period_CenterMax0_carry_i_4_n_0;
  wire Period_CenterMax0_carry_i_5_n_0;
  wire Period_CenterMax0_carry_i_6_n_0;
  wire Period_CenterMax0_carry_i_7_n_0;
  wire Period_CenterMax0_carry_i_8_n_0;
  wire Period_CenterMax0_carry_n_0;
  wire Period_CenterMax0_carry_n_1;
  wire Period_CenterMax0_carry_n_2;
  wire Period_CenterMax0_carry_n_3;
  wire Period_CenterMax0_carry_n_4;
  wire Period_CenterMax0_carry_n_5;
  wire Period_CenterMax0_carry_n_6;
  wire Period_CenterMax0_carry_n_7;
  wire [9:0]Product_mul_temp0_out;
  wire [0:0]\Product_mul_temp[-1111111102]_0 ;
  wire \Product_mul_temp[-1111111103]_0 ;
  wire \Product_mul_temp[-1111111104]_0 ;
  wire \Product_mul_temp[-1111111105]_0 ;
  wire \Product_mul_temp[-1111111106]_0 ;
  wire \Product_mul_temp[-1111111107]_0 ;
  wire \Product_mul_temp[-1111111108]_0 ;
  wire \Product_mul_temp[-1111111109]_0 ;
  wire \Product_mul_temp[-1111111110]_0 ;
  wire \Product_mul_temp[-1111111111]_0 ;
  wire [8:0]Product_mul_temp__0;
  wire Product_mul_temp__0_carry__0_i_1_n_0;
  wire Product_mul_temp__0_carry__0_i_2_n_0;
  wire Product_mul_temp__0_carry__0_i_3_n_0;
  wire Product_mul_temp__0_carry__0_i_4_n_0;
  wire Product_mul_temp__0_carry__0_i_5_n_0;
  wire Product_mul_temp__0_carry__0_i_6_n_0;
  wire Product_mul_temp__0_carry__0_n_14;
  wire Product_mul_temp__0_carry__0_n_7;
  wire Product_mul_temp__0_carry_i_10_n_0;
  wire Product_mul_temp__0_carry_i_11_n_0;
  wire Product_mul_temp__0_carry_i_12_n_0;
  wire Product_mul_temp__0_carry_i_13_n_0;
  wire Product_mul_temp__0_carry_i_14_n_0;
  wire Product_mul_temp__0_carry_i_15_n_0;
  wire Product_mul_temp__0_carry_i_16_n_0;
  wire Product_mul_temp__0_carry_i_17_n_0;
  wire Product_mul_temp__0_carry_i_18_n_0;
  wire Product_mul_temp__0_carry_i_19_n_0;
  wire Product_mul_temp__0_carry_i_1_n_0;
  wire Product_mul_temp__0_carry_i_20_n_0;
  wire Product_mul_temp__0_carry_i_2_n_0;
  wire Product_mul_temp__0_carry_i_3_n_0;
  wire Product_mul_temp__0_carry_i_4_n_0;
  wire Product_mul_temp__0_carry_i_5_n_0;
  wire Product_mul_temp__0_carry_i_6_n_0;
  wire Product_mul_temp__0_carry_i_7_n_0;
  wire Product_mul_temp__0_carry_i_8_n_0;
  wire Product_mul_temp__0_carry_i_9_n_0;
  wire Product_mul_temp__0_carry_n_0;
  wire Product_mul_temp__0_carry_n_1;
  wire Product_mul_temp__0_carry_n_2;
  wire Product_mul_temp__0_carry_n_3;
  wire Product_mul_temp__0_carry_n_4;
  wire Product_mul_temp__0_carry_n_5;
  wire Product_mul_temp__0_carry_n_6;
  wire Product_mul_temp__0_carry_n_7;
  wire \Product_mul_temp_inferred__0/i__carry__0_n_7 ;
  wire \Product_mul_temp_inferred__0/i__carry_n_0 ;
  wire \Product_mul_temp_inferred__0/i__carry_n_1 ;
  wire \Product_mul_temp_inferred__0/i__carry_n_2 ;
  wire \Product_mul_temp_inferred__0/i__carry_n_3 ;
  wire \Product_mul_temp_inferred__0/i__carry_n_4 ;
  wire \Product_mul_temp_inferred__0/i__carry_n_5 ;
  wire \Product_mul_temp_inferred__0/i__carry_n_6 ;
  wire \Product_mul_temp_inferred__0/i__carry_n_7 ;
  wire Product_mul_temp_n_100;
  wire Product_mul_temp_n_101;
  wire Product_mul_temp_n_102;
  wire Product_mul_temp_n_103;
  wire Product_mul_temp_n_104;
  wire Product_mul_temp_n_105;
  wire Product_mul_temp_n_58;
  wire Product_mul_temp_n_59;
  wire Product_mul_temp_n_60;
  wire Product_mul_temp_n_61;
  wire Product_mul_temp_n_62;
  wire Product_mul_temp_n_63;
  wire Product_mul_temp_n_64;
  wire Product_mul_temp_n_65;
  wire Product_mul_temp_n_66;
  wire Product_mul_temp_n_67;
  wire Product_mul_temp_n_68;
  wire Product_mul_temp_n_69;
  wire Product_mul_temp_n_70;
  wire Product_mul_temp_n_71;
  wire Product_mul_temp_n_72;
  wire Product_mul_temp_n_73;
  wire Product_mul_temp_n_74;
  wire Product_mul_temp_n_75;
  wire Product_mul_temp_n_76;
  wire Product_mul_temp_n_77;
  wire Product_mul_temp_n_78;
  wire Product_mul_temp_n_79;
  wire Product_mul_temp_n_80;
  wire Product_mul_temp_n_81;
  wire Product_mul_temp_n_82;
  wire Product_mul_temp_n_83;
  wire Product_mul_temp_n_84;
  wire Product_mul_temp_n_85;
  wire Product_mul_temp_n_86;
  wire Product_mul_temp_n_87;
  wire Product_mul_temp_n_88;
  wire Product_mul_temp_n_89;
  wire Product_mul_temp_n_90;
  wire Product_mul_temp_n_97;
  wire Product_mul_temp_n_98;
  wire Product_mul_temp_n_99;
  wire [9:0]Q;
  wire Relational_Operator4_relop1;
  wire [13:0]Relational_Operator_1_cast;
  wire [0:0]S;
  wire [12:0]Saturation_out1;
  wire Switch6_out1;
  wire Switch6_out1_1_i_3_n_0;
  wire Switch6_out1_1_i_4_n_0;
  wire Switch6_out1_1_i_5_n_0;
  wire Switch6_out1_1_i_6_n_0;
  wire Switch6_out1_1_i_7_n_0;
  wire Switch6_out1_1_i_8_n_0;
  wire [0:0]Switch7_out12_carry;
  wire [0:0]Switch7_out12_carry_0;
  wire Switch7_out12_carry_i_6;
  wire Switch7_out12_carry_i_6_0;
  wire Switch7_out12_carry_i_6_1;
  wire [0:0]Switch8_out12_carry;
  wire [0:0]Switch8_out12_carry_0;
  wire [0:0]Switch9_out12_carry;
  wire [0:0]Switch9_out12_carry_0;
  wire [5:0]\U1_norm_1_reg[10] ;
  wire [0:0]\U1_norm_1_reg[11] ;
  wire [0:0]\U1_norm_1_reg[12] ;
  wire [5:0]\U1_norm_1_reg[9] ;
  wire [7:0]\U2_norm_1_reg[10] ;
  wire [0:0]\U2_norm_1_reg[12] ;
  wire [12:0]\U2_norm_1_reg[12]_0 ;
  wire \U2_norm_1_reg[13] ;
  wire [1:0]\U2_norm_1_reg[13]_0 ;
  wire [7:0]\U2_norm_1_reg[9] ;
  wire [7:0]\U3_norm_1_reg[10] ;
  wire [0:0]\U3_norm_1_reg[12] ;
  wire [12:0]\U3_norm_1_reg[12]_0 ;
  wire \U3_norm_1_reg[13] ;
  wire [1:0]\U3_norm_1_reg[13]_0 ;
  wire [7:0]\U3_norm_1_reg[9] ;
  wire dir_ctrl;
  wire i__carry__0_i_1__0_n_0;
  wire i__carry__0_i_2_n_0;
  wire i__carry_i_1__3_n_0;
  wire i__carry_i_2__3_n_0;
  wire i__carry_i_3__3_n_0;
  wire i__carry_i_4__3_n_0;
  wire i__carry_i_5__3_n_0;
  wire i__carry_i_6__3_n_0;
  wire i__carry_i_7__3_n_0;
  wire i__carry_i_8__3_n_0;
  wire reset;
  wire [7:3]\NLW_HDL_Counter2_count_reg[16]_i_1_CO_UNCONNECTED ;
  wire [7:4]\NLW_HDL_Counter2_count_reg[16]_i_1_O_UNCONNECTED ;
  wire [7:0]NLW_Logical_Operator_out10_carry_O_UNCONNECTED;
  wire [7:5]NLW_Logical_Operator_out10_carry__0_CO_UNCONNECTED;
  wire [7:0]NLW_Logical_Operator_out10_carry__0_O_UNCONNECTED;
  wire [7:0]NLW_Period_CenterMax0_carry_O_UNCONNECTED;
  wire [7:1]NLW_Period_CenterMax0_carry__0_CO_UNCONNECTED;
  wire [7:0]NLW_Period_CenterMax0_carry__0_O_UNCONNECTED;
  wire NLW_Product_mul_temp_CARRYCASCOUT_UNCONNECTED;
  wire NLW_Product_mul_temp_MULTSIGNOUT_UNCONNECTED;
  wire NLW_Product_mul_temp_OVERFLOW_UNCONNECTED;
  wire NLW_Product_mul_temp_PATTERNBDETECT_UNCONNECTED;
  wire NLW_Product_mul_temp_PATTERNDETECT_UNCONNECTED;
  wire NLW_Product_mul_temp_UNDERFLOW_UNCONNECTED;
  wire [29:0]NLW_Product_mul_temp_ACOUT_UNCONNECTED;
  wire [17:0]NLW_Product_mul_temp_BCOUT_UNCONNECTED;
  wire [3:0]NLW_Product_mul_temp_CARRYOUT_UNCONNECTED;
  wire [47:0]NLW_Product_mul_temp_PCOUT_UNCONNECTED;
  wire [7:0]NLW_Product_mul_temp_XOROUT_UNCONNECTED;
  wire [7:1]NLW_Product_mul_temp__0_carry__0_CO_UNCONNECTED;
  wire [7:2]NLW_Product_mul_temp__0_carry__0_O_UNCONNECTED;
  wire [7:1]\NLW_Product_mul_temp_inferred__0/i__carry__0_CO_UNCONNECTED ;
  wire [7:2]\NLW_Product_mul_temp_inferred__0/i__carry__0_O_UNCONNECTED ;

  assign HDL_Counter2_count_reg_7_sn_1 = HDL_Counter2_count_reg_7_sp_1;
  LUT5 #(
    .INIT(32'hAAEFAA20)) 
    \Delay1_out1[0]_i_1 
       (.I0(\Delay1_out1_reg[13]_0 [0]),
        .I1(HDL_Counter2_count_reg[12]),
        .I2(\Delay2_out1_reg[13]_1 ),
        .I3(CO),
        .I4(\Delay1_out1_reg[13] [0]),
        .O(\U2_norm_1_reg[12]_0 [0]));
  LUT5 #(
    .INIT(32'hAAEFAA20)) 
    \Delay1_out1[10]_i_1 
       (.I0(\Delay1_out1_reg[13]_0 [10]),
        .I1(HDL_Counter2_count_reg[12]),
        .I2(\Delay2_out1_reg[13]_1 ),
        .I3(CO),
        .I4(\Delay1_out1_reg[13] [10]),
        .O(\U2_norm_1_reg[12]_0 [10]));
  LUT5 #(
    .INIT(32'hAAEFAA20)) 
    \Delay1_out1[11]_i_1 
       (.I0(\Delay1_out1_reg[13]_0 [11]),
        .I1(HDL_Counter2_count_reg[12]),
        .I2(\Delay2_out1_reg[13]_1 ),
        .I3(CO),
        .I4(\Delay1_out1_reg[13] [11]),
        .O(\U2_norm_1_reg[12]_0 [11]));
  LUT5 #(
    .INIT(32'hAAEFAA20)) 
    \Delay1_out1[12]_i_1 
       (.I0(\Delay1_out1_reg[13]_0 [12]),
        .I1(HDL_Counter2_count_reg[12]),
        .I2(\Delay2_out1_reg[13]_1 ),
        .I3(CO),
        .I4(\Delay1_out1_reg[13] [12]),
        .O(\U2_norm_1_reg[12]_0 [12]));
  LUT5 #(
    .INIT(32'hAAEFAA20)) 
    \Delay1_out1[13]_i_1 
       (.I0(\Delay1_out1_reg[13]_0 [13]),
        .I1(HDL_Counter2_count_reg[12]),
        .I2(\Delay2_out1_reg[13]_1 ),
        .I3(CO),
        .I4(\Delay1_out1_reg[13] [13]),
        .O(\U2_norm_1_reg[13] ));
  LUT5 #(
    .INIT(32'hAAEFAA20)) 
    \Delay1_out1[1]_i_1 
       (.I0(\Delay1_out1_reg[13]_0 [1]),
        .I1(HDL_Counter2_count_reg[12]),
        .I2(\Delay2_out1_reg[13]_1 ),
        .I3(CO),
        .I4(\Delay1_out1_reg[13] [1]),
        .O(\U2_norm_1_reg[12]_0 [1]));
  LUT5 #(
    .INIT(32'hAAEFAA20)) 
    \Delay1_out1[2]_i_1 
       (.I0(\Delay1_out1_reg[13]_0 [2]),
        .I1(HDL_Counter2_count_reg[12]),
        .I2(\Delay2_out1_reg[13]_1 ),
        .I3(CO),
        .I4(\Delay1_out1_reg[13] [2]),
        .O(\U2_norm_1_reg[12]_0 [2]));
  LUT5 #(
    .INIT(32'hAAEFAA20)) 
    \Delay1_out1[3]_i_1 
       (.I0(\Delay1_out1_reg[13]_0 [3]),
        .I1(HDL_Counter2_count_reg[12]),
        .I2(\Delay2_out1_reg[13]_1 ),
        .I3(CO),
        .I4(\Delay1_out1_reg[13] [3]),
        .O(\U2_norm_1_reg[12]_0 [3]));
  LUT5 #(
    .INIT(32'hAAEFAA20)) 
    \Delay1_out1[4]_i_1 
       (.I0(\Delay1_out1_reg[13]_0 [4]),
        .I1(HDL_Counter2_count_reg[12]),
        .I2(\Delay2_out1_reg[13]_1 ),
        .I3(CO),
        .I4(\Delay1_out1_reg[13] [4]),
        .O(\U2_norm_1_reg[12]_0 [4]));
  LUT5 #(
    .INIT(32'hAAEFAA20)) 
    \Delay1_out1[5]_i_1 
       (.I0(\Delay1_out1_reg[13]_0 [5]),
        .I1(HDL_Counter2_count_reg[12]),
        .I2(\Delay2_out1_reg[13]_1 ),
        .I3(CO),
        .I4(\Delay1_out1_reg[13] [5]),
        .O(\U2_norm_1_reg[12]_0 [5]));
  LUT5 #(
    .INIT(32'hAAEFAA20)) 
    \Delay1_out1[6]_i_1 
       (.I0(\Delay1_out1_reg[13]_0 [6]),
        .I1(HDL_Counter2_count_reg[12]),
        .I2(\Delay2_out1_reg[13]_1 ),
        .I3(CO),
        .I4(\Delay1_out1_reg[13] [6]),
        .O(\U2_norm_1_reg[12]_0 [6]));
  LUT5 #(
    .INIT(32'hAAEFAA20)) 
    \Delay1_out1[7]_i_1 
       (.I0(\Delay1_out1_reg[13]_0 [7]),
        .I1(HDL_Counter2_count_reg[12]),
        .I2(\Delay2_out1_reg[13]_1 ),
        .I3(CO),
        .I4(\Delay1_out1_reg[13] [7]),
        .O(\U2_norm_1_reg[12]_0 [7]));
  LUT5 #(
    .INIT(32'hAAEFAA20)) 
    \Delay1_out1[8]_i_1 
       (.I0(\Delay1_out1_reg[13]_0 [8]),
        .I1(HDL_Counter2_count_reg[12]),
        .I2(\Delay2_out1_reg[13]_1 ),
        .I3(CO),
        .I4(\Delay1_out1_reg[13] [8]),
        .O(\U2_norm_1_reg[12]_0 [8]));
  LUT5 #(
    .INIT(32'hAAEFAA20)) 
    \Delay1_out1[9]_i_1 
       (.I0(\Delay1_out1_reg[13]_0 [9]),
        .I1(HDL_Counter2_count_reg[12]),
        .I2(\Delay2_out1_reg[13]_1 ),
        .I3(CO),
        .I4(\Delay1_out1_reg[13] [9]),
        .O(\U2_norm_1_reg[12]_0 [9]));
  LUT5 #(
    .INIT(32'hAAEFAA20)) 
    \Delay2_out1[0]_i_1 
       (.I0(\Delay2_out1_reg[13]_0 [0]),
        .I1(HDL_Counter2_count_reg[12]),
        .I2(\Delay2_out1_reg[13]_1 ),
        .I3(CO),
        .I4(\Delay2_out1_reg[13] [0]),
        .O(\U3_norm_1_reg[12]_0 [0]));
  LUT5 #(
    .INIT(32'hAAEFAA20)) 
    \Delay2_out1[10]_i_1 
       (.I0(\Delay2_out1_reg[13]_0 [10]),
        .I1(HDL_Counter2_count_reg[12]),
        .I2(\Delay2_out1_reg[13]_1 ),
        .I3(CO),
        .I4(\Delay2_out1_reg[13] [10]),
        .O(\U3_norm_1_reg[12]_0 [10]));
  LUT5 #(
    .INIT(32'hAAEFAA20)) 
    \Delay2_out1[11]_i_1 
       (.I0(\Delay2_out1_reg[13]_0 [11]),
        .I1(HDL_Counter2_count_reg[12]),
        .I2(\Delay2_out1_reg[13]_1 ),
        .I3(CO),
        .I4(\Delay2_out1_reg[13] [11]),
        .O(\U3_norm_1_reg[12]_0 [11]));
  LUT5 #(
    .INIT(32'hAAEFAA20)) 
    \Delay2_out1[12]_i_1 
       (.I0(\Delay2_out1_reg[13]_0 [12]),
        .I1(HDL_Counter2_count_reg[12]),
        .I2(\Delay2_out1_reg[13]_1 ),
        .I3(CO),
        .I4(\Delay2_out1_reg[13] [12]),
        .O(\U3_norm_1_reg[12]_0 [12]));
  LUT5 #(
    .INIT(32'hAAEFAA20)) 
    \Delay2_out1[13]_i_1 
       (.I0(\Delay2_out1_reg[13]_0 [13]),
        .I1(HDL_Counter2_count_reg[12]),
        .I2(\Delay2_out1_reg[13]_1 ),
        .I3(CO),
        .I4(\Delay2_out1_reg[13] [13]),
        .O(\U3_norm_1_reg[13] ));
  LUT5 #(
    .INIT(32'hAAEFAA20)) 
    \Delay2_out1[1]_i_1 
       (.I0(\Delay2_out1_reg[13]_0 [1]),
        .I1(HDL_Counter2_count_reg[12]),
        .I2(\Delay2_out1_reg[13]_1 ),
        .I3(CO),
        .I4(\Delay2_out1_reg[13] [1]),
        .O(\U3_norm_1_reg[12]_0 [1]));
  LUT5 #(
    .INIT(32'hAAEFAA20)) 
    \Delay2_out1[2]_i_1 
       (.I0(\Delay2_out1_reg[13]_0 [2]),
        .I1(HDL_Counter2_count_reg[12]),
        .I2(\Delay2_out1_reg[13]_1 ),
        .I3(CO),
        .I4(\Delay2_out1_reg[13] [2]),
        .O(\U3_norm_1_reg[12]_0 [2]));
  LUT5 #(
    .INIT(32'hAAEFAA20)) 
    \Delay2_out1[3]_i_1 
       (.I0(\Delay2_out1_reg[13]_0 [3]),
        .I1(HDL_Counter2_count_reg[12]),
        .I2(\Delay2_out1_reg[13]_1 ),
        .I3(CO),
        .I4(\Delay2_out1_reg[13] [3]),
        .O(\U3_norm_1_reg[12]_0 [3]));
  LUT5 #(
    .INIT(32'hAAEFAA20)) 
    \Delay2_out1[4]_i_1 
       (.I0(\Delay2_out1_reg[13]_0 [4]),
        .I1(HDL_Counter2_count_reg[12]),
        .I2(\Delay2_out1_reg[13]_1 ),
        .I3(CO),
        .I4(\Delay2_out1_reg[13] [4]),
        .O(\U3_norm_1_reg[12]_0 [4]));
  LUT5 #(
    .INIT(32'hAAEFAA20)) 
    \Delay2_out1[5]_i_1 
       (.I0(\Delay2_out1_reg[13]_0 [5]),
        .I1(HDL_Counter2_count_reg[12]),
        .I2(\Delay2_out1_reg[13]_1 ),
        .I3(CO),
        .I4(\Delay2_out1_reg[13] [5]),
        .O(\U3_norm_1_reg[12]_0 [5]));
  LUT5 #(
    .INIT(32'hAAEFAA20)) 
    \Delay2_out1[6]_i_1 
       (.I0(\Delay2_out1_reg[13]_0 [6]),
        .I1(HDL_Counter2_count_reg[12]),
        .I2(\Delay2_out1_reg[13]_1 ),
        .I3(CO),
        .I4(\Delay2_out1_reg[13] [6]),
        .O(\U3_norm_1_reg[12]_0 [6]));
  LUT5 #(
    .INIT(32'hAAEFAA20)) 
    \Delay2_out1[7]_i_1 
       (.I0(\Delay2_out1_reg[13]_0 [7]),
        .I1(HDL_Counter2_count_reg[12]),
        .I2(\Delay2_out1_reg[13]_1 ),
        .I3(CO),
        .I4(\Delay2_out1_reg[13] [7]),
        .O(\U3_norm_1_reg[12]_0 [7]));
  LUT5 #(
    .INIT(32'hAAEFAA20)) 
    \Delay2_out1[8]_i_1 
       (.I0(\Delay2_out1_reg[13]_0 [8]),
        .I1(HDL_Counter2_count_reg[12]),
        .I2(\Delay2_out1_reg[13]_1 ),
        .I3(CO),
        .I4(\Delay2_out1_reg[13] [8]),
        .O(\U3_norm_1_reg[12]_0 [8]));
  LUT5 #(
    .INIT(32'hAAEFAA20)) 
    \Delay2_out1[9]_i_1 
       (.I0(\Delay2_out1_reg[13]_0 [9]),
        .I1(HDL_Counter2_count_reg[12]),
        .I2(\Delay2_out1_reg[13]_1 ),
        .I3(CO),
        .I4(\Delay2_out1_reg[13] [9]),
        .O(\U3_norm_1_reg[12]_0 [9]));
  (* SOFT_HLUTNM = "soft_lutpair10" *) 
  LUT5 #(
    .INIT(32'h55550001)) 
    Delay6_out1_i_1
       (.I0(Relational_Operator4_relop1),
        .I1(Delay6_out1_i_2_n_0),
        .I2(Delay6_out1_i_3_n_0),
        .I3(HDL_Counter2_count_reg_7_sn_1),
        .I4(Delay6_out1),
        .O(dir_ctrl));
  LUT5 #(
    .INIT(32'hFFFFFFFE)) 
    Delay6_out1_i_2
       (.I0(HDL_Counter2_count_reg[6]),
        .I1(HDL_Counter2_count_reg[3]),
        .I2(HDL_Counter2_count_reg[8]),
        .I3(HDL_Counter2_count_reg[5]),
        .I4(Delay6_out1_i_4_n_0),
        .O(Delay6_out1_i_2_n_0));
  LUT5 #(
    .INIT(32'hFFFFFFFE)) 
    Delay6_out1_i_3
       (.I0(Delay6_out1_reg_1),
        .I1(Delay6_out1_reg_0),
        .I2(HDL_Counter2_count_reg[11]),
        .I3(Delay6_out1_i_5_n_0),
        .I4(Delay6_out1_i_6_n_0),
        .O(Delay6_out1_i_3_n_0));
  LUT4 #(
    .INIT(16'hFFFE)) 
    Delay6_out1_i_4
       (.I0(HDL_Counter2_count_reg[1]),
        .I1(HDL_Counter2_count_reg[4]),
        .I2(\HDL_Counter2_count_reg[7]_1 ),
        .I3(HDL_Counter2_count_reg[2]),
        .O(Delay6_out1_i_4_n_0));
  LUT4 #(
    .INIT(16'hFFFE)) 
    Delay6_out1_i_5
       (.I0(\HDL_Counter2_count_reg[7]_3 ),
        .I1(\HDL_Counter2_count_reg[7]_0 ),
        .I2(HDL_Counter2_count_reg[0]),
        .I3(\HDL_Counter2_count_reg[7]_2 ),
        .O(Delay6_out1_i_5_n_0));
  (* SOFT_HLUTNM = "soft_lutpair11" *) 
  LUT4 #(
    .INIT(16'hFFFE)) 
    Delay6_out1_i_6
       (.I0(HDL_Counter2_count_reg[9]),
        .I1(HDL_Counter2_count_reg[12]),
        .I2(HDL_Counter2_count_reg[7]),
        .I3(HDL_Counter2_count_reg[10]),
        .O(Delay6_out1_i_6_n_0));
  FDRE Delay6_out1_reg
       (.C(IPCORE_CLK),
        .CE(E),
        .D(dir_ctrl),
        .Q(Delay6_out1),
        .R(reset));
  LUT5 #(
    .INIT(32'hAAEFAA20)) 
    \Delay_out1[0]_i_1 
       (.I0(\Delay_out1_reg[13]_0 [0]),
        .I1(HDL_Counter2_count_reg[12]),
        .I2(\Delay2_out1_reg[13]_1 ),
        .I3(CO),
        .I4(\Delay_out1_reg[13] [0]),
        .O(Relational_Operator_1_cast[0]));
  LUT5 #(
    .INIT(32'hAAEFAA20)) 
    \Delay_out1[10]_i_1 
       (.I0(\Delay_out1_reg[13]_0 [10]),
        .I1(HDL_Counter2_count_reg[12]),
        .I2(\Delay2_out1_reg[13]_1 ),
        .I3(CO),
        .I4(\Delay_out1_reg[13] [10]),
        .O(Relational_Operator_1_cast[10]));
  LUT5 #(
    .INIT(32'hAAEFAA20)) 
    \Delay_out1[11]_i_1 
       (.I0(\Delay_out1_reg[13]_0 [11]),
        .I1(HDL_Counter2_count_reg[12]),
        .I2(\Delay2_out1_reg[13]_1 ),
        .I3(CO),
        .I4(\Delay_out1_reg[13] [11]),
        .O(Relational_Operator_1_cast[11]));
  LUT5 #(
    .INIT(32'hAAEFAA20)) 
    \Delay_out1[12]_i_1 
       (.I0(\Delay_out1_reg[13]_0 [12]),
        .I1(HDL_Counter2_count_reg[12]),
        .I2(\Delay2_out1_reg[13]_1 ),
        .I3(CO),
        .I4(\Delay_out1_reg[13] [12]),
        .O(Relational_Operator_1_cast[12]));
  LUT5 #(
    .INIT(32'hAAEFAA20)) 
    \Delay_out1[13]_i_1 
       (.I0(\Delay_out1_reg[13]_0 [13]),
        .I1(HDL_Counter2_count_reg[12]),
        .I2(\Delay2_out1_reg[13]_1 ),
        .I3(CO),
        .I4(\Delay_out1_reg[13] [13]),
        .O(Relational_Operator_1_cast[13]));
  LUT5 #(
    .INIT(32'hAAEFAA20)) 
    \Delay_out1[1]_i_1 
       (.I0(\Delay_out1_reg[13]_0 [1]),
        .I1(HDL_Counter2_count_reg[12]),
        .I2(\Delay2_out1_reg[13]_1 ),
        .I3(CO),
        .I4(\Delay_out1_reg[13] [1]),
        .O(Relational_Operator_1_cast[1]));
  LUT5 #(
    .INIT(32'hAAEFAA20)) 
    \Delay_out1[2]_i_1 
       (.I0(\Delay_out1_reg[13]_0 [2]),
        .I1(HDL_Counter2_count_reg[12]),
        .I2(\Delay2_out1_reg[13]_1 ),
        .I3(CO),
        .I4(\Delay_out1_reg[13] [2]),
        .O(Relational_Operator_1_cast[2]));
  LUT5 #(
    .INIT(32'hAAEFAA20)) 
    \Delay_out1[3]_i_1 
       (.I0(\Delay_out1_reg[13]_0 [3]),
        .I1(HDL_Counter2_count_reg[12]),
        .I2(\Delay2_out1_reg[13]_1 ),
        .I3(CO),
        .I4(\Delay_out1_reg[13] [3]),
        .O(Relational_Operator_1_cast[3]));
  LUT5 #(
    .INIT(32'hAAEFAA20)) 
    \Delay_out1[4]_i_1 
       (.I0(\Delay_out1_reg[13]_0 [4]),
        .I1(HDL_Counter2_count_reg[12]),
        .I2(\Delay2_out1_reg[13]_1 ),
        .I3(CO),
        .I4(\Delay_out1_reg[13] [4]),
        .O(Relational_Operator_1_cast[4]));
  LUT5 #(
    .INIT(32'hAAEFAA20)) 
    \Delay_out1[5]_i_1 
       (.I0(\Delay_out1_reg[13]_0 [5]),
        .I1(HDL_Counter2_count_reg[12]),
        .I2(\Delay2_out1_reg[13]_1 ),
        .I3(CO),
        .I4(\Delay_out1_reg[13] [5]),
        .O(Relational_Operator_1_cast[5]));
  LUT5 #(
    .INIT(32'hAAEFAA20)) 
    \Delay_out1[6]_i_1 
       (.I0(\Delay_out1_reg[13]_0 [6]),
        .I1(HDL_Counter2_count_reg[12]),
        .I2(\Delay2_out1_reg[13]_1 ),
        .I3(CO),
        .I4(\Delay_out1_reg[13] [6]),
        .O(Relational_Operator_1_cast[6]));
  LUT5 #(
    .INIT(32'hAAEFAA20)) 
    \Delay_out1[7]_i_1 
       (.I0(\Delay_out1_reg[13]_0 [7]),
        .I1(HDL_Counter2_count_reg[12]),
        .I2(\Delay2_out1_reg[13]_1 ),
        .I3(CO),
        .I4(\Delay_out1_reg[13] [7]),
        .O(Relational_Operator_1_cast[7]));
  LUT5 #(
    .INIT(32'hAAEFAA20)) 
    \Delay_out1[8]_i_1 
       (.I0(\Delay_out1_reg[13]_0 [8]),
        .I1(HDL_Counter2_count_reg[12]),
        .I2(\Delay2_out1_reg[13]_1 ),
        .I3(CO),
        .I4(\Delay_out1_reg[13] [8]),
        .O(Relational_Operator_1_cast[8]));
  LUT5 #(
    .INIT(32'hAAEFAA20)) 
    \Delay_out1[9]_i_1 
       (.I0(\Delay_out1_reg[13]_0 [9]),
        .I1(HDL_Counter2_count_reg[12]),
        .I2(\Delay2_out1_reg[13]_1 ),
        .I3(CO),
        .I4(\Delay_out1_reg[13] [9]),
        .O(Relational_Operator_1_cast[9]));
  LUT6 #(
    .INIT(64'h55550001AAAAFFFE)) 
    \HDL_Counter2_count[0]_i_2 
       (.I0(Relational_Operator4_relop1),
        .I1(Delay6_out1_i_2_n_0),
        .I2(Delay6_out1_i_3_n_0),
        .I3(HDL_Counter2_count_reg_7_sn_1),
        .I4(Delay6_out1),
        .I5(\HDL_Counter2_count_reg[7]_0 ),
        .O(\HDL_Counter2_count[0]_i_2_n_0 ));
  LUT6 #(
    .INIT(64'h55550001AAAAFFFE)) 
    \HDL_Counter2_count[0]_i_3 
       (.I0(Relational_Operator4_relop1),
        .I1(Delay6_out1_i_2_n_0),
        .I2(Delay6_out1_i_3_n_0),
        .I3(HDL_Counter2_count_reg_7_sn_1),
        .I4(Delay6_out1),
        .I5(\HDL_Counter2_count_reg[7]_1 ),
        .O(\HDL_Counter2_count[0]_i_3_n_0 ));
  LUT6 #(
    .INIT(64'h55550001AAAAFFFE)) 
    \HDL_Counter2_count[0]_i_4 
       (.I0(Relational_Operator4_relop1),
        .I1(Delay6_out1_i_2_n_0),
        .I2(Delay6_out1_i_3_n_0),
        .I3(HDL_Counter2_count_reg_7_sn_1),
        .I4(Delay6_out1),
        .I5(\HDL_Counter2_count_reg[7]_2 ),
        .O(\HDL_Counter2_count[0]_i_4_n_0 ));
  LUT6 #(
    .INIT(64'h55550001AAAAFFFE)) 
    \HDL_Counter2_count[0]_i_5 
       (.I0(Relational_Operator4_relop1),
        .I1(Delay6_out1_i_2_n_0),
        .I2(Delay6_out1_i_3_n_0),
        .I3(HDL_Counter2_count_reg_7_sn_1),
        .I4(Delay6_out1),
        .I5(\HDL_Counter2_count_reg[7]_3 ),
        .O(\HDL_Counter2_count[0]_i_5_n_0 ));
  LUT6 #(
    .INIT(64'h55550001AAAAFFFE)) 
    \HDL_Counter2_count[0]_i_6 
       (.I0(Relational_Operator4_relop1),
        .I1(Delay6_out1_i_2_n_0),
        .I2(Delay6_out1_i_3_n_0),
        .I3(HDL_Counter2_count_reg_7_sn_1),
        .I4(Delay6_out1),
        .I5(Delay6_out1_reg_1),
        .O(\HDL_Counter2_count[0]_i_6_n_0 ));
  LUT6 #(
    .INIT(64'h55550001AAAAFFFE)) 
    \HDL_Counter2_count[0]_i_7 
       (.I0(Relational_Operator4_relop1),
        .I1(Delay6_out1_i_2_n_0),
        .I2(Delay6_out1_i_3_n_0),
        .I3(HDL_Counter2_count_reg_7_sn_1),
        .I4(Delay6_out1),
        .I5(Delay6_out1_reg_0),
        .O(\HDL_Counter2_count[0]_i_7_n_0 ));
  LUT6 #(
    .INIT(64'h55550001AAAAFFFE)) 
    \HDL_Counter2_count[0]_i_8 
       (.I0(Relational_Operator4_relop1),
        .I1(Delay6_out1_i_2_n_0),
        .I2(Delay6_out1_i_3_n_0),
        .I3(HDL_Counter2_count_reg_7_sn_1),
        .I4(Delay6_out1),
        .I5(HDL_Counter2_count_reg[0]),
        .O(\HDL_Counter2_count[0]_i_8_n_0 ));
  LUT5 #(
    .INIT(32'hAA55FF01)) 
    \HDL_Counter2_count[0]_i_9 
       (.I0(Relational_Operator4_relop1),
        .I1(Delay6_out1_i_2_n_0),
        .I2(Delay6_out1_i_3_n_0),
        .I3(HDL_Counter2_count_reg_7_sn_1),
        .I4(Delay6_out1),
        .O(\HDL_Counter2_count[0]_i_9_n_0 ));
  LUT6 #(
    .INIT(64'h55550001AAAAFFFE)) 
    \HDL_Counter2_count[16]_i_2 
       (.I0(Relational_Operator4_relop1),
        .I1(Delay6_out1_i_2_n_0),
        .I2(Delay6_out1_i_3_n_0),
        .I3(HDL_Counter2_count_reg_7_sn_1),
        .I4(Delay6_out1),
        .I5(HDL_Counter2_count_reg[12]),
        .O(\HDL_Counter2_count[16]_i_2_n_0 ));
  LUT6 #(
    .INIT(64'h55550001AAAAFFFE)) 
    \HDL_Counter2_count[16]_i_3 
       (.I0(Relational_Operator4_relop1),
        .I1(Delay6_out1_i_2_n_0),
        .I2(Delay6_out1_i_3_n_0),
        .I3(HDL_Counter2_count_reg_7_sn_1),
        .I4(Delay6_out1),
        .I5(HDL_Counter2_count_reg[11]),
        .O(\HDL_Counter2_count[16]_i_3_n_0 ));
  LUT6 #(
    .INIT(64'h55550001AAAAFFFE)) 
    \HDL_Counter2_count[16]_i_4 
       (.I0(Relational_Operator4_relop1),
        .I1(Delay6_out1_i_2_n_0),
        .I2(Delay6_out1_i_3_n_0),
        .I3(HDL_Counter2_count_reg_7_sn_1),
        .I4(Delay6_out1),
        .I5(HDL_Counter2_count_reg[10]),
        .O(\HDL_Counter2_count[16]_i_4_n_0 ));
  LUT6 #(
    .INIT(64'h55550001AAAAFFFE)) 
    \HDL_Counter2_count[16]_i_5 
       (.I0(Relational_Operator4_relop1),
        .I1(Delay6_out1_i_2_n_0),
        .I2(Delay6_out1_i_3_n_0),
        .I3(HDL_Counter2_count_reg_7_sn_1),
        .I4(Delay6_out1),
        .I5(HDL_Counter2_count_reg[9]),
        .O(\HDL_Counter2_count[16]_i_5_n_0 ));
  LUT6 #(
    .INIT(64'h55550001AAAAFFFE)) 
    \HDL_Counter2_count[8]_i_2 
       (.I0(Relational_Operator4_relop1),
        .I1(Delay6_out1_i_2_n_0),
        .I2(Delay6_out1_i_3_n_0),
        .I3(HDL_Counter2_count_reg_7_sn_1),
        .I4(Delay6_out1),
        .I5(HDL_Counter2_count_reg[8]),
        .O(\HDL_Counter2_count[8]_i_2_n_0 ));
  LUT6 #(
    .INIT(64'h55550001AAAAFFFE)) 
    \HDL_Counter2_count[8]_i_3 
       (.I0(Relational_Operator4_relop1),
        .I1(Delay6_out1_i_2_n_0),
        .I2(Delay6_out1_i_3_n_0),
        .I3(HDL_Counter2_count_reg_7_sn_1),
        .I4(Delay6_out1),
        .I5(HDL_Counter2_count_reg[7]),
        .O(\HDL_Counter2_count[8]_i_3_n_0 ));
  LUT6 #(
    .INIT(64'h55550001AAAAFFFE)) 
    \HDL_Counter2_count[8]_i_4 
       (.I0(Relational_Operator4_relop1),
        .I1(Delay6_out1_i_2_n_0),
        .I2(Delay6_out1_i_3_n_0),
        .I3(HDL_Counter2_count_reg_7_sn_1),
        .I4(Delay6_out1),
        .I5(HDL_Counter2_count_reg[6]),
        .O(\HDL_Counter2_count[8]_i_4_n_0 ));
  LUT6 #(
    .INIT(64'h55550001AAAAFFFE)) 
    \HDL_Counter2_count[8]_i_5 
       (.I0(Relational_Operator4_relop1),
        .I1(Delay6_out1_i_2_n_0),
        .I2(Delay6_out1_i_3_n_0),
        .I3(HDL_Counter2_count_reg_7_sn_1),
        .I4(Delay6_out1),
        .I5(HDL_Counter2_count_reg[5]),
        .O(\HDL_Counter2_count[8]_i_5_n_0 ));
  LUT6 #(
    .INIT(64'h55550001AAAAFFFE)) 
    \HDL_Counter2_count[8]_i_6 
       (.I0(Relational_Operator4_relop1),
        .I1(Delay6_out1_i_2_n_0),
        .I2(Delay6_out1_i_3_n_0),
        .I3(HDL_Counter2_count_reg_7_sn_1),
        .I4(Delay6_out1),
        .I5(HDL_Counter2_count_reg[4]),
        .O(\HDL_Counter2_count[8]_i_6_n_0 ));
  LUT6 #(
    .INIT(64'h55550001AAAAFFFE)) 
    \HDL_Counter2_count[8]_i_7 
       (.I0(Relational_Operator4_relop1),
        .I1(Delay6_out1_i_2_n_0),
        .I2(Delay6_out1_i_3_n_0),
        .I3(HDL_Counter2_count_reg_7_sn_1),
        .I4(Delay6_out1),
        .I5(HDL_Counter2_count_reg[3]),
        .O(\HDL_Counter2_count[8]_i_7_n_0 ));
  LUT6 #(
    .INIT(64'h55550001AAAAFFFE)) 
    \HDL_Counter2_count[8]_i_8 
       (.I0(Relational_Operator4_relop1),
        .I1(Delay6_out1_i_2_n_0),
        .I2(Delay6_out1_i_3_n_0),
        .I3(HDL_Counter2_count_reg_7_sn_1),
        .I4(Delay6_out1),
        .I5(HDL_Counter2_count_reg[2]),
        .O(\HDL_Counter2_count[8]_i_8_n_0 ));
  LUT6 #(
    .INIT(64'h55550001AAAAFFFE)) 
    \HDL_Counter2_count[8]_i_9 
       (.I0(Relational_Operator4_relop1),
        .I1(Delay6_out1_i_2_n_0),
        .I2(Delay6_out1_i_3_n_0),
        .I3(HDL_Counter2_count_reg_7_sn_1),
        .I4(Delay6_out1),
        .I5(HDL_Counter2_count_reg[1]),
        .O(\HDL_Counter2_count[8]_i_9_n_0 ));
  LUT2 #(
    .INIT(4'h9)) 
    HDL_Counter2_count_next_carry__0_i_1
       (.I0(HDL_Counter2_count_reg[8]),
        .I1(HDL_Counter2_count_reg[9]),
        .O(\HDL_Counter2_count_reg[15] [7]));
  LUT2 #(
    .INIT(4'h9)) 
    HDL_Counter2_count_next_carry__0_i_2
       (.I0(HDL_Counter2_count_reg[7]),
        .I1(HDL_Counter2_count_reg[8]),
        .O(\HDL_Counter2_count_reg[15] [6]));
  LUT2 #(
    .INIT(4'h9)) 
    HDL_Counter2_count_next_carry__0_i_3
       (.I0(HDL_Counter2_count_reg[6]),
        .I1(HDL_Counter2_count_reg[7]),
        .O(\HDL_Counter2_count_reg[15] [5]));
  LUT2 #(
    .INIT(4'h9)) 
    HDL_Counter2_count_next_carry__0_i_4
       (.I0(HDL_Counter2_count_reg[5]),
        .I1(HDL_Counter2_count_reg[6]),
        .O(\HDL_Counter2_count_reg[15] [4]));
  LUT2 #(
    .INIT(4'h9)) 
    HDL_Counter2_count_next_carry__0_i_5
       (.I0(HDL_Counter2_count_reg[4]),
        .I1(HDL_Counter2_count_reg[5]),
        .O(\HDL_Counter2_count_reg[15] [3]));
  LUT2 #(
    .INIT(4'h9)) 
    HDL_Counter2_count_next_carry__0_i_6
       (.I0(HDL_Counter2_count_reg[3]),
        .I1(HDL_Counter2_count_reg[4]),
        .O(\HDL_Counter2_count_reg[15] [2]));
  LUT2 #(
    .INIT(4'h9)) 
    HDL_Counter2_count_next_carry__0_i_7
       (.I0(HDL_Counter2_count_reg[2]),
        .I1(HDL_Counter2_count_reg[3]),
        .O(\HDL_Counter2_count_reg[15] [1]));
  LUT2 #(
    .INIT(4'h9)) 
    HDL_Counter2_count_next_carry__0_i_8
       (.I0(HDL_Counter2_count_reg[1]),
        .I1(HDL_Counter2_count_reg[2]),
        .O(\HDL_Counter2_count_reg[15] [0]));
  LUT5 #(
    .INIT(32'h55550001)) 
    HDL_Counter2_count_next_carry_i_1
       (.I0(Relational_Operator4_relop1),
        .I1(Delay6_out1_i_2_n_0),
        .I2(Delay6_out1_i_3_n_0),
        .I3(HDL_Counter2_count_reg_7_sn_1),
        .I4(Delay6_out1),
        .O(\HDL_Counter2_count_reg[0]_1 ));
  LUT6 #(
    .INIT(64'h55550001AAAAFFFE)) 
    HDL_Counter2_count_next_carry_i_10
       (.I0(Relational_Operator4_relop1),
        .I1(Delay6_out1_i_2_n_0),
        .I2(Delay6_out1_i_3_n_0),
        .I3(HDL_Counter2_count_reg_7_sn_1),
        .I4(Delay6_out1),
        .I5(HDL_Counter2_count_reg[0]),
        .O(\HDL_Counter2_count_reg[0]_2 [0]));
  LUT5 #(
    .INIT(32'hAAAAFFFE)) 
    HDL_Counter2_count_next_carry_i_2
       (.I0(Relational_Operator4_relop1),
        .I1(Delay6_out1_i_2_n_0),
        .I2(Delay6_out1_i_3_n_0),
        .I3(HDL_Counter2_count_reg_7_sn_1),
        .I4(Delay6_out1),
        .O(DI));
  LUT6 #(
    .INIT(64'h55550001AAAAFFFE)) 
    HDL_Counter2_count_next_carry_i_9
       (.I0(Relational_Operator4_relop1),
        .I1(Delay6_out1_i_2_n_0),
        .I2(Delay6_out1_i_3_n_0),
        .I3(HDL_Counter2_count_reg_7_sn_1),
        .I4(Delay6_out1),
        .I5(Delay6_out1_reg_0),
        .O(\HDL_Counter2_count_reg[0]_2 [1]));
  (* ADDER_THRESHOLD = "16" *) 
  CARRY8 \HDL_Counter2_count_reg[0]_i_1 
       (.CI(DI),
        .CI_TOP(1'b0),
        .CO({\HDL_Counter2_count_reg[0]_i_1_n_0 ,\HDL_Counter2_count_reg[0]_i_1_n_1 ,\HDL_Counter2_count_reg[0]_i_1_n_2 ,\HDL_Counter2_count_reg[0]_i_1_n_3 ,\HDL_Counter2_count_reg[0]_i_1_n_4 ,\HDL_Counter2_count_reg[0]_i_1_n_5 ,\HDL_Counter2_count_reg[0]_i_1_n_6 ,\HDL_Counter2_count_reg[0]_i_1_n_7 }),
        .DI({DI,DI,DI,DI,DI,DI,DI,HDL_Counter2_count_reg_7_sn_1}),
        .O(O),
        .S({\HDL_Counter2_count[0]_i_2_n_0 ,\HDL_Counter2_count[0]_i_3_n_0 ,\HDL_Counter2_count[0]_i_4_n_0 ,\HDL_Counter2_count[0]_i_5_n_0 ,\HDL_Counter2_count[0]_i_6_n_0 ,\HDL_Counter2_count[0]_i_7_n_0 ,\HDL_Counter2_count[0]_i_8_n_0 ,\HDL_Counter2_count[0]_i_9_n_0 }));
  (* ADDER_THRESHOLD = "16" *) 
  CARRY8 \HDL_Counter2_count_reg[16]_i_1 
       (.CI(\HDL_Counter2_count_reg[8]_i_1_n_0 ),
        .CI_TOP(1'b0),
        .CO({\NLW_HDL_Counter2_count_reg[16]_i_1_CO_UNCONNECTED [7:3],\HDL_Counter2_count_reg[16]_i_1_n_5 ,\HDL_Counter2_count_reg[16]_i_1_n_6 ,\HDL_Counter2_count_reg[16]_i_1_n_7 }),
        .DI({1'b0,1'b0,1'b0,1'b0,1'b0,DI,DI,DI}),
        .O({\NLW_HDL_Counter2_count_reg[16]_i_1_O_UNCONNECTED [7:4],\HDL_Counter2_count_reg[0]_0 }),
        .S({1'b0,1'b0,1'b0,1'b0,\HDL_Counter2_count[16]_i_2_n_0 ,\HDL_Counter2_count[16]_i_3_n_0 ,\HDL_Counter2_count[16]_i_4_n_0 ,\HDL_Counter2_count[16]_i_5_n_0 }));
  (* ADDER_THRESHOLD = "16" *) 
  CARRY8 \HDL_Counter2_count_reg[8]_i_1 
       (.CI(\HDL_Counter2_count_reg[0]_i_1_n_0 ),
        .CI_TOP(1'b0),
        .CO({\HDL_Counter2_count_reg[8]_i_1_n_0 ,\HDL_Counter2_count_reg[8]_i_1_n_1 ,\HDL_Counter2_count_reg[8]_i_1_n_2 ,\HDL_Counter2_count_reg[8]_i_1_n_3 ,\HDL_Counter2_count_reg[8]_i_1_n_4 ,\HDL_Counter2_count_reg[8]_i_1_n_5 ,\HDL_Counter2_count_reg[8]_i_1_n_6 ,\HDL_Counter2_count_reg[8]_i_1_n_7 }),
        .DI({DI,DI,DI,DI,DI,DI,DI,DI}),
        .O(\HDL_Counter2_count_reg[0] ),
        .S({\HDL_Counter2_count[8]_i_2_n_0 ,\HDL_Counter2_count[8]_i_3_n_0 ,\HDL_Counter2_count[8]_i_4_n_0 ,\HDL_Counter2_count[8]_i_5_n_0 ,\HDL_Counter2_count[8]_i_6_n_0 ,\HDL_Counter2_count[8]_i_7_n_0 ,\HDL_Counter2_count[8]_i_8_n_0 ,\HDL_Counter2_count[8]_i_9_n_0 }));
  (* COMPARATOR_THRESHOLD = "11" *) 
  CARRY8 Logical_Operator_out10_carry
       (.CI(1'b1),
        .CI_TOP(1'b0),
        .CO({Logical_Operator_out10_carry_n_0,Logical_Operator_out10_carry_n_1,Logical_Operator_out10_carry_n_2,Logical_Operator_out10_carry_n_3,Logical_Operator_out10_carry_n_4,Logical_Operator_out10_carry_n_5,Logical_Operator_out10_carry_n_6,Logical_Operator_out10_carry_n_7}),
        .DI({Logical_Operator_out10_carry_i_1_n_0,Logical_Operator_out10_carry_i_2__1_n_0,Logical_Operator_out10_carry_i_3__2_n_0,Logical_Operator_out10_carry_i_4__2_n_0,Logical_Operator_out10_carry_i_5__2_n_0,Logical_Operator_out10_carry_i_6__2_n_0,Logical_Operator_out10_carry_i_7__2_n_0,Logical_Operator_out10_carry_i_8__0_n_0}),
        .O(NLW_Logical_Operator_out10_carry_O_UNCONNECTED[7:0]),
        .S({Logical_Operator_out10_carry_i_9_n_0,Logical_Operator_out10_carry_i_10__1_n_0,Logical_Operator_out10_carry_i_11__2_n_0,Logical_Operator_out10_carry_i_12__2_n_0,Logical_Operator_out10_carry_i_13__2_n_0,Logical_Operator_out10_carry_i_14__2_n_0,Logical_Operator_out10_carry_i_15__2_n_0,Logical_Operator_out10_carry_i_16__0_n_0}));
  (* COMPARATOR_THRESHOLD = "11" *) 
  CARRY8 Logical_Operator_out10_carry__0
       (.CI(Logical_Operator_out10_carry_n_0),
        .CI_TOP(1'b0),
        .CO({NLW_Logical_Operator_out10_carry__0_CO_UNCONNECTED[7:5],Relational_Operator4_relop1,Logical_Operator_out10_carry__0_n_4,Logical_Operator_out10_carry__0_n_5,Logical_Operator_out10_carry__0_n_6,Logical_Operator_out10_carry__0_n_7}),
        .DI({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,Logical_Operator_out10_carry__0_i_1_n_0,Logical_Operator_out10_carry__0_i_2_n_0}),
        .O(NLW_Logical_Operator_out10_carry__0_O_UNCONNECTED[7:0]),
        .S({1'b0,1'b0,1'b0,Logical_Operator_out10_carry__0_i_3_n_0,Logical_Operator_out10_carry__0_i_4_n_0,Logical_Operator_out10_carry__0_i_5_n_0,Logical_Operator_out10_carry__0_i_6_n_0,Logical_Operator_out10_carry__0_i_7_n_0}));
  LUT4 #(
    .INIT(16'h22B2)) 
    Logical_Operator_out10_carry__0_i_1
       (.I0(HDL_Counter2_count_reg[12]),
        .I1(Logical_Operator_out10_carry__0_0[19]),
        .I2(HDL_Counter2_count_reg[11]),
        .I3(Logical_Operator_out10_carry__0_0[18]),
        .O(Logical_Operator_out10_carry__0_i_1_n_0));
  LUT4 #(
    .INIT(16'h22B2)) 
    Logical_Operator_out10_carry__0_i_2
       (.I0(HDL_Counter2_count_reg[10]),
        .I1(Logical_Operator_out10_carry__0_0[17]),
        .I2(HDL_Counter2_count_reg[9]),
        .I3(Logical_Operator_out10_carry__0_0[16]),
        .O(Logical_Operator_out10_carry__0_i_2_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    Logical_Operator_out10_carry__0_i_3
       (.I0(Logical_Operator_out10_carry__0_0[24]),
        .O(Logical_Operator_out10_carry__0_i_3_n_0));
  LUT2 #(
    .INIT(4'h1)) 
    Logical_Operator_out10_carry__0_i_4
       (.I0(Logical_Operator_out10_carry__0_0[23]),
        .I1(Logical_Operator_out10_carry__0_0[22]),
        .O(Logical_Operator_out10_carry__0_i_4_n_0));
  LUT2 #(
    .INIT(4'h1)) 
    Logical_Operator_out10_carry__0_i_5
       (.I0(Logical_Operator_out10_carry__0_0[21]),
        .I1(Logical_Operator_out10_carry__0_0[20]),
        .O(Logical_Operator_out10_carry__0_i_5_n_0));
  LUT4 #(
    .INIT(16'h9009)) 
    Logical_Operator_out10_carry__0_i_6
       (.I0(HDL_Counter2_count_reg[11]),
        .I1(Logical_Operator_out10_carry__0_0[18]),
        .I2(HDL_Counter2_count_reg[12]),
        .I3(Logical_Operator_out10_carry__0_0[19]),
        .O(Logical_Operator_out10_carry__0_i_6_n_0));
  LUT4 #(
    .INIT(16'h9009)) 
    Logical_Operator_out10_carry__0_i_7
       (.I0(HDL_Counter2_count_reg[9]),
        .I1(Logical_Operator_out10_carry__0_0[16]),
        .I2(HDL_Counter2_count_reg[10]),
        .I3(Logical_Operator_out10_carry__0_0[17]),
        .O(Logical_Operator_out10_carry__0_i_7_n_0));
  LUT4 #(
    .INIT(16'h22B2)) 
    Logical_Operator_out10_carry_i_1
       (.I0(HDL_Counter2_count_reg[8]),
        .I1(Logical_Operator_out10_carry__0_0[15]),
        .I2(HDL_Counter2_count_reg[7]),
        .I3(Logical_Operator_out10_carry__0_0[14]),
        .O(Logical_Operator_out10_carry_i_1_n_0));
  LUT6 #(
    .INIT(64'h9990009000099909)) 
    Logical_Operator_out10_carry_i_10
       (.I0(\U3_norm_1_reg[12]_0 [11]),
        .I1(Saturation_out1[11]),
        .I2(\Delay2_out1_reg[13] [10]),
        .I3(Allow_assymetrical_anew_reference_value__0),
        .I4(\Delay2_out1_reg[13]_0 [10]),
        .I5(Saturation_out1[10]),
        .O(\Delay2_out1_reg[12]_1 [5]));
  LUT6 #(
    .INIT(64'h9990009000099909)) 
    Logical_Operator_out10_carry_i_10__0
       (.I0(\U2_norm_1_reg[12]_0 [11]),
        .I1(Saturation_out1[11]),
        .I2(\Delay1_out1_reg[13] [10]),
        .I3(Allow_assymetrical_anew_reference_value__0),
        .I4(\Delay1_out1_reg[13]_0 [10]),
        .I5(Saturation_out1[10]),
        .O(\Delay1_out1_reg[12]_1 [5]));
  LUT4 #(
    .INIT(16'h9009)) 
    Logical_Operator_out10_carry_i_10__1
       (.I0(HDL_Counter2_count_reg[5]),
        .I1(Logical_Operator_out10_carry__0_0[12]),
        .I2(HDL_Counter2_count_reg[6]),
        .I3(Logical_Operator_out10_carry__0_0[13]),
        .O(Logical_Operator_out10_carry_i_10__1_n_0));
  LUT5 #(
    .INIT(32'h0000A959)) 
    Logical_Operator_out10_carry_i_10__2
       (.I0(Saturation_out1[12]),
        .I1(\Delay_out1_reg[13] [12]),
        .I2(Allow_assymetrical_anew_reference_value__0),
        .I3(\Delay_out1_reg[13]_0 [12]),
        .I4(Relational_Operator_1_cast[13]),
        .O(\Delay_out1_reg[12]_2 ));
  LUT6 #(
    .INIT(64'h9990009000099909)) 
    Logical_Operator_out10_carry_i_11
       (.I0(\U3_norm_1_reg[12]_0 [9]),
        .I1(Saturation_out1[9]),
        .I2(\Delay2_out1_reg[13] [8]),
        .I3(Allow_assymetrical_anew_reference_value__0),
        .I4(\Delay2_out1_reg[13]_0 [8]),
        .I5(Saturation_out1[8]),
        .O(\Delay2_out1_reg[12]_1 [4]));
  LUT6 #(
    .INIT(64'h9990009000099909)) 
    Logical_Operator_out10_carry_i_11__0
       (.I0(\U2_norm_1_reg[12]_0 [9]),
        .I1(Saturation_out1[9]),
        .I2(\Delay1_out1_reg[13] [8]),
        .I3(Allow_assymetrical_anew_reference_value__0),
        .I4(\Delay1_out1_reg[13]_0 [8]),
        .I5(Saturation_out1[8]),
        .O(\Delay1_out1_reg[12]_1 [4]));
  LUT4 #(
    .INIT(16'h9009)) 
    Logical_Operator_out10_carry_i_11__2
       (.I0(HDL_Counter2_count_reg[3]),
        .I1(Logical_Operator_out10_carry__0_0[10]),
        .I2(HDL_Counter2_count_reg[4]),
        .I3(Logical_Operator_out10_carry__0_0[11]),
        .O(Logical_Operator_out10_carry_i_11__2_n_0));
  LUT6 #(
    .INIT(64'h9990009000099909)) 
    Logical_Operator_out10_carry_i_12
       (.I0(\U3_norm_1_reg[12]_0 [7]),
        .I1(Saturation_out1[7]),
        .I2(\Delay2_out1_reg[13] [6]),
        .I3(Allow_assymetrical_anew_reference_value__0),
        .I4(\Delay2_out1_reg[13]_0 [6]),
        .I5(Saturation_out1[6]),
        .O(\Delay2_out1_reg[12]_1 [3]));
  LUT6 #(
    .INIT(64'h9990009000099909)) 
    Logical_Operator_out10_carry_i_12__0
       (.I0(\U2_norm_1_reg[12]_0 [7]),
        .I1(Saturation_out1[7]),
        .I2(\Delay1_out1_reg[13] [6]),
        .I3(Allow_assymetrical_anew_reference_value__0),
        .I4(\Delay1_out1_reg[13]_0 [6]),
        .I5(Saturation_out1[6]),
        .O(\Delay1_out1_reg[12]_1 [3]));
  LUT4 #(
    .INIT(16'h9009)) 
    Logical_Operator_out10_carry_i_12__2
       (.I0(HDL_Counter2_count_reg[2]),
        .I1(Logical_Operator_out10_carry__0_0[9]),
        .I2(HDL_Counter2_count_reg[1]),
        .I3(Logical_Operator_out10_carry__0_0[8]),
        .O(Logical_Operator_out10_carry_i_12__2_n_0));
  LUT6 #(
    .INIT(64'h9990009000099909)) 
    Logical_Operator_out10_carry_i_13
       (.I0(\U3_norm_1_reg[12]_0 [5]),
        .I1(Saturation_out1[5]),
        .I2(\Delay2_out1_reg[13] [4]),
        .I3(Allow_assymetrical_anew_reference_value__0),
        .I4(\Delay2_out1_reg[13]_0 [4]),
        .I5(Saturation_out1[4]),
        .O(\Delay2_out1_reg[12]_1 [2]));
  LUT6 #(
    .INIT(64'h9990009000099909)) 
    Logical_Operator_out10_carry_i_13__0
       (.I0(\U2_norm_1_reg[12]_0 [5]),
        .I1(Saturation_out1[5]),
        .I2(\Delay1_out1_reg[13] [4]),
        .I3(Allow_assymetrical_anew_reference_value__0),
        .I4(\Delay1_out1_reg[13]_0 [4]),
        .I5(Saturation_out1[4]),
        .O(\Delay1_out1_reg[12]_1 [2]));
  LUT4 #(
    .INIT(16'h9009)) 
    Logical_Operator_out10_carry_i_13__2
       (.I0(\HDL_Counter2_count_reg[7]_1 ),
        .I1(Logical_Operator_out10_carry__0_0[6]),
        .I2(\HDL_Counter2_count_reg[7]_0 ),
        .I3(Logical_Operator_out10_carry__0_0[7]),
        .O(Logical_Operator_out10_carry_i_13__2_n_0));
  LUT6 #(
    .INIT(64'h9990009000099909)) 
    Logical_Operator_out10_carry_i_14
       (.I0(\U3_norm_1_reg[12]_0 [3]),
        .I1(Saturation_out1[3]),
        .I2(\Delay2_out1_reg[13] [2]),
        .I3(Allow_assymetrical_anew_reference_value__0),
        .I4(\Delay2_out1_reg[13]_0 [2]),
        .I5(Saturation_out1[2]),
        .O(\Delay2_out1_reg[12]_1 [1]));
  LUT6 #(
    .INIT(64'h9990009000099909)) 
    Logical_Operator_out10_carry_i_14__0
       (.I0(\U2_norm_1_reg[12]_0 [3]),
        .I1(Saturation_out1[3]),
        .I2(\Delay1_out1_reg[13] [2]),
        .I3(Allow_assymetrical_anew_reference_value__0),
        .I4(\Delay1_out1_reg[13]_0 [2]),
        .I5(Saturation_out1[2]),
        .O(\Delay1_out1_reg[12]_1 [1]));
  LUT4 #(
    .INIT(16'h9009)) 
    Logical_Operator_out10_carry_i_14__2
       (.I0(\HDL_Counter2_count_reg[7]_3 ),
        .I1(Logical_Operator_out10_carry__0_0[4]),
        .I2(\HDL_Counter2_count_reg[7]_2 ),
        .I3(Logical_Operator_out10_carry__0_0[5]),
        .O(Logical_Operator_out10_carry_i_14__2_n_0));
  LUT6 #(
    .INIT(64'h9990009000099909)) 
    Logical_Operator_out10_carry_i_15
       (.I0(\U3_norm_1_reg[12]_0 [1]),
        .I1(Saturation_out1[1]),
        .I2(\Delay2_out1_reg[13] [0]),
        .I3(Allow_assymetrical_anew_reference_value__0),
        .I4(\Delay2_out1_reg[13]_0 [0]),
        .I5(Saturation_out1[0]),
        .O(\Delay2_out1_reg[12]_1 [0]));
  LUT6 #(
    .INIT(64'h9990009000099909)) 
    Logical_Operator_out10_carry_i_15__0
       (.I0(\U2_norm_1_reg[12]_0 [1]),
        .I1(Saturation_out1[1]),
        .I2(\Delay1_out1_reg[13] [0]),
        .I3(Allow_assymetrical_anew_reference_value__0),
        .I4(\Delay1_out1_reg[13]_0 [0]),
        .I5(Saturation_out1[0]),
        .O(\Delay1_out1_reg[12]_1 [0]));
  LUT4 #(
    .INIT(16'h9009)) 
    Logical_Operator_out10_carry_i_15__2
       (.I0(Delay6_out1_reg_1),
        .I1(Logical_Operator_out10_carry__0_0[3]),
        .I2(Delay6_out1_reg_0),
        .I3(Logical_Operator_out10_carry__0_0[2]),
        .O(Logical_Operator_out10_carry_i_15__2_n_0));
  LUT4 #(
    .INIT(16'h9009)) 
    Logical_Operator_out10_carry_i_16__0
       (.I0(HDL_Counter2_count_reg_7_sn_1),
        .I1(Logical_Operator_out10_carry__0_0[0]),
        .I2(HDL_Counter2_count_reg[0]),
        .I3(Logical_Operator_out10_carry__0_0[1]),
        .O(Logical_Operator_out10_carry_i_16__0_n_0));
  LUT5 #(
    .INIT(32'hFFFF4000)) 
    Logical_Operator_out10_carry_i_19
       (.I0(HDL_Counter2_count_reg[12]),
        .I1(Switch7_out12_carry_i_6),
        .I2(Switch7_out12_carry_i_6_0),
        .I3(Switch7_out12_carry_i_6_1),
        .I4(CO),
        .O(Allow_assymetrical_anew_reference_value__0));
  LUT5 #(
    .INIT(32'hAAAEEEAE)) 
    Logical_Operator_out10_carry_i_1__0
       (.I0(\U3_norm_1_reg[13] ),
        .I1(Saturation_out1[12]),
        .I2(\Delay2_out1_reg[13] [12]),
        .I3(Allow_assymetrical_anew_reference_value__0),
        .I4(\Delay2_out1_reg[13]_0 [12]),
        .O(\Delay2_out1_reg[12]_2 ));
  LUT5 #(
    .INIT(32'hAAAEEEAE)) 
    Logical_Operator_out10_carry_i_1__1
       (.I0(\U2_norm_1_reg[13] ),
        .I1(Saturation_out1[12]),
        .I2(\Delay1_out1_reg[13] [12]),
        .I3(Allow_assymetrical_anew_reference_value__0),
        .I4(\Delay1_out1_reg[13]_0 [12]),
        .O(\Delay1_out1_reg[12]_2 ));
  LUT4 #(
    .INIT(16'h22B2)) 
    Logical_Operator_out10_carry_i_2__1
       (.I0(HDL_Counter2_count_reg[6]),
        .I1(Logical_Operator_out10_carry__0_0[13]),
        .I2(HDL_Counter2_count_reg[5]),
        .I3(Logical_Operator_out10_carry__0_0[12]),
        .O(Logical_Operator_out10_carry_i_2__1_n_0));
  LUT5 #(
    .INIT(32'hAAAEEEAE)) 
    Logical_Operator_out10_carry_i_2__2
       (.I0(Relational_Operator_1_cast[13]),
        .I1(Saturation_out1[12]),
        .I2(\Delay_out1_reg[13] [12]),
        .I3(Allow_assymetrical_anew_reference_value__0),
        .I4(\Delay_out1_reg[13]_0 [12]),
        .O(\Delay_out1_reg[12]_1 ));
  LUT4 #(
    .INIT(16'h22B2)) 
    Logical_Operator_out10_carry_i_3__2
       (.I0(HDL_Counter2_count_reg[4]),
        .I1(Logical_Operator_out10_carry__0_0[11]),
        .I2(HDL_Counter2_count_reg[3]),
        .I3(Logical_Operator_out10_carry__0_0[10]),
        .O(Logical_Operator_out10_carry_i_3__2_n_0));
  LUT4 #(
    .INIT(16'h22B2)) 
    Logical_Operator_out10_carry_i_4__2
       (.I0(HDL_Counter2_count_reg[2]),
        .I1(Logical_Operator_out10_carry__0_0[9]),
        .I2(HDL_Counter2_count_reg[1]),
        .I3(Logical_Operator_out10_carry__0_0[8]),
        .O(Logical_Operator_out10_carry_i_4__2_n_0));
  LUT4 #(
    .INIT(16'h22B2)) 
    Logical_Operator_out10_carry_i_5__2
       (.I0(\HDL_Counter2_count_reg[7]_0 ),
        .I1(Logical_Operator_out10_carry__0_0[7]),
        .I2(\HDL_Counter2_count_reg[7]_1 ),
        .I3(Logical_Operator_out10_carry__0_0[6]),
        .O(Logical_Operator_out10_carry_i_5__2_n_0));
  LUT4 #(
    .INIT(16'h22B2)) 
    Logical_Operator_out10_carry_i_6__2
       (.I0(\HDL_Counter2_count_reg[7]_2 ),
        .I1(Logical_Operator_out10_carry__0_0[5]),
        .I2(\HDL_Counter2_count_reg[7]_3 ),
        .I3(Logical_Operator_out10_carry__0_0[4]),
        .O(Logical_Operator_out10_carry_i_6__2_n_0));
  LUT4 #(
    .INIT(16'h22B2)) 
    Logical_Operator_out10_carry_i_7__2
       (.I0(Delay6_out1_reg_1),
        .I1(Logical_Operator_out10_carry__0_0[3]),
        .I2(Delay6_out1_reg_0),
        .I3(Logical_Operator_out10_carry__0_0[2]),
        .O(Logical_Operator_out10_carry_i_7__2_n_0));
  LUT4 #(
    .INIT(16'h22B2)) 
    Logical_Operator_out10_carry_i_8__0
       (.I0(HDL_Counter2_count_reg[0]),
        .I1(Logical_Operator_out10_carry__0_0[1]),
        .I2(HDL_Counter2_count_reg_7_sn_1),
        .I3(Logical_Operator_out10_carry__0_0[0]),
        .O(Logical_Operator_out10_carry_i_8__0_n_0));
  LUT4 #(
    .INIT(16'h9009)) 
    Logical_Operator_out10_carry_i_9
       (.I0(HDL_Counter2_count_reg[8]),
        .I1(Logical_Operator_out10_carry__0_0[15]),
        .I2(HDL_Counter2_count_reg[7]),
        .I3(Logical_Operator_out10_carry__0_0[14]),
        .O(Logical_Operator_out10_carry_i_9_n_0));
  LUT5 #(
    .INIT(32'h54040151)) 
    Logical_Operator_out10_carry_i_9__0
       (.I0(\U3_norm_1_reg[13] ),
        .I1(\Delay2_out1_reg[13] [12]),
        .I2(Allow_assymetrical_anew_reference_value__0),
        .I3(\Delay2_out1_reg[13]_0 [12]),
        .I4(Saturation_out1[12]),
        .O(\Delay2_out1_reg[12]_1 [6]));
  LUT5 #(
    .INIT(32'h54040151)) 
    Logical_Operator_out10_carry_i_9__1
       (.I0(\U2_norm_1_reg[13] ),
        .I1(\Delay1_out1_reg[13] [12]),
        .I2(Allow_assymetrical_anew_reference_value__0),
        .I3(\Delay1_out1_reg[13]_0 [12]),
        .I4(Saturation_out1[12]),
        .O(\Delay1_out1_reg[12]_1 [6]));
  CARRY8 Period_CenterMax0_carry
       (.CI(1'b1),
        .CI_TOP(1'b0),
        .CO({Period_CenterMax0_carry_n_0,Period_CenterMax0_carry_n_1,Period_CenterMax0_carry_n_2,Period_CenterMax0_carry_n_3,Period_CenterMax0_carry_n_4,Period_CenterMax0_carry_n_5,Period_CenterMax0_carry_n_6,Period_CenterMax0_carry_n_7}),
        .DI({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .O(NLW_Period_CenterMax0_carry_O_UNCONNECTED[7:0]),
        .S({Period_CenterMax0_carry_i_1_n_0,Period_CenterMax0_carry_i_2_n_0,Period_CenterMax0_carry_i_3_n_0,Period_CenterMax0_carry_i_4_n_0,Period_CenterMax0_carry_i_5_n_0,Period_CenterMax0_carry_i_6_n_0,Period_CenterMax0_carry_i_7_n_0,Period_CenterMax0_carry_i_8_n_0}));
  CARRY8 Period_CenterMax0_carry__0
       (.CI(Period_CenterMax0_carry_n_0),
        .CI_TOP(1'b0),
        .CO({NLW_Period_CenterMax0_carry__0_CO_UNCONNECTED[7:1],CO}),
        .DI({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .O(NLW_Period_CenterMax0_carry__0_O_UNCONNECTED[7:0]),
        .S({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,S}));
  LUT3 #(
    .INIT(8'h01)) 
    Period_CenterMax0_carry_i_1
       (.I0(Logical_Operator_out10_carry__0_0[23]),
        .I1(Logical_Operator_out10_carry__0_0[22]),
        .I2(Logical_Operator_out10_carry__0_0[21]),
        .O(Period_CenterMax0_carry_i_1_n_0));
  LUT5 #(
    .INIT(32'h41000041)) 
    Period_CenterMax0_carry_i_2
       (.I0(Logical_Operator_out10_carry__0_0[20]),
        .I1(Logical_Operator_out10_carry__0_0[19]),
        .I2(HDL_Counter2_count_reg[12]),
        .I3(HDL_Counter2_count_reg[11]),
        .I4(Logical_Operator_out10_carry__0_0[18]),
        .O(Period_CenterMax0_carry_i_2_n_0));
  LUT6 #(
    .INIT(64'h9009000000009009)) 
    Period_CenterMax0_carry_i_3
       (.I0(Logical_Operator_out10_carry__0_0[17]),
        .I1(HDL_Counter2_count_reg[10]),
        .I2(Logical_Operator_out10_carry__0_0[16]),
        .I3(HDL_Counter2_count_reg[9]),
        .I4(HDL_Counter2_count_reg[8]),
        .I5(Logical_Operator_out10_carry__0_0[15]),
        .O(Period_CenterMax0_carry_i_3_n_0));
  LUT6 #(
    .INIT(64'h9009000000009009)) 
    Period_CenterMax0_carry_i_4
       (.I0(Logical_Operator_out10_carry__0_0[13]),
        .I1(HDL_Counter2_count_reg[6]),
        .I2(Logical_Operator_out10_carry__0_0[14]),
        .I3(HDL_Counter2_count_reg[7]),
        .I4(HDL_Counter2_count_reg[5]),
        .I5(Logical_Operator_out10_carry__0_0[12]),
        .O(Period_CenterMax0_carry_i_4_n_0));
  LUT6 #(
    .INIT(64'h9009000000009009)) 
    Period_CenterMax0_carry_i_5
       (.I0(Logical_Operator_out10_carry__0_0[11]),
        .I1(HDL_Counter2_count_reg[4]),
        .I2(Logical_Operator_out10_carry__0_0[10]),
        .I3(HDL_Counter2_count_reg[3]),
        .I4(HDL_Counter2_count_reg[2]),
        .I5(Logical_Operator_out10_carry__0_0[9]),
        .O(Period_CenterMax0_carry_i_5_n_0));
  LUT6 #(
    .INIT(64'h9009000000009009)) 
    Period_CenterMax0_carry_i_6
       (.I0(Logical_Operator_out10_carry__0_0[7]),
        .I1(\HDL_Counter2_count_reg[7]_0 ),
        .I2(Logical_Operator_out10_carry__0_0[8]),
        .I3(HDL_Counter2_count_reg[1]),
        .I4(\HDL_Counter2_count_reg[7]_1 ),
        .I5(Logical_Operator_out10_carry__0_0[6]),
        .O(Period_CenterMax0_carry_i_6_n_0));
  LUT6 #(
    .INIT(64'h9009000000009009)) 
    Period_CenterMax0_carry_i_7
       (.I0(Logical_Operator_out10_carry__0_0[5]),
        .I1(\HDL_Counter2_count_reg[7]_2 ),
        .I2(Logical_Operator_out10_carry__0_0[4]),
        .I3(\HDL_Counter2_count_reg[7]_3 ),
        .I4(Delay6_out1_reg_1),
        .I5(Logical_Operator_out10_carry__0_0[3]),
        .O(Period_CenterMax0_carry_i_7_n_0));
  LUT6 #(
    .INIT(64'h9009000000009009)) 
    Period_CenterMax0_carry_i_8
       (.I0(Logical_Operator_out10_carry__0_0[1]),
        .I1(HDL_Counter2_count_reg[0]),
        .I2(Logical_Operator_out10_carry__0_0[2]),
        .I3(Delay6_out1_reg_0),
        .I4(HDL_Counter2_count_reg_7_sn_1),
        .I5(Logical_Operator_out10_carry__0_0[0]),
        .O(Period_CenterMax0_carry_i_8_n_0));
  (* KEEP_HIERARCHY = "yes" *) 
  (* METHODOLOGY_DRC_VIOS = "{SYNTH-11 {cell *THIS*}}" *) 
  DSP48E2 #(
    .ACASCREG(2),
    .ADREG(1),
    .ALUMODEREG(0),
    .AMULTSEL("A"),
    .AREG(2),
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
    Product_mul_temp
       (.A({1'b0,1'b0,1'b0,1'b0,1'b0,D}),
        .ACIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .ACOUT(NLW_Product_mul_temp_ACOUT_UNCONNECTED[29:0]),
        .ALUMODE({1'b0,1'b0,1'b0,1'b0}),
        .B({1'b0,B,HDL_Counter2_count_next}),
        .BCIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .BCOUT(NLW_Product_mul_temp_BCOUT_UNCONNECTED[17:0]),
        .C({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .CARRYCASCIN(1'b0),
        .CARRYCASCOUT(NLW_Product_mul_temp_CARRYCASCOUT_UNCONNECTED),
        .CARRYIN(1'b0),
        .CARRYINSEL({1'b0,1'b0,1'b0}),
        .CARRYOUT(NLW_Product_mul_temp_CARRYOUT_UNCONNECTED[3:0]),
        .CEA1(E),
        .CEA2(E),
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
        .CLK(IPCORE_CLK),
        .D({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .INMODE({1'b0,1'b0,1'b0,1'b0,1'b0}),
        .MULTSIGNIN(1'b0),
        .MULTSIGNOUT(NLW_Product_mul_temp_MULTSIGNOUT_UNCONNECTED),
        .OPMODE({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b1,1'b0,1'b1}),
        .OVERFLOW(NLW_Product_mul_temp_OVERFLOW_UNCONNECTED),
        .P({Product_mul_temp_n_58,Product_mul_temp_n_59,Product_mul_temp_n_60,Product_mul_temp_n_61,Product_mul_temp_n_62,Product_mul_temp_n_63,Product_mul_temp_n_64,Product_mul_temp_n_65,Product_mul_temp_n_66,Product_mul_temp_n_67,Product_mul_temp_n_68,Product_mul_temp_n_69,Product_mul_temp_n_70,Product_mul_temp_n_71,Product_mul_temp_n_72,Product_mul_temp_n_73,Product_mul_temp_n_74,Product_mul_temp_n_75,Product_mul_temp_n_76,Product_mul_temp_n_77,Product_mul_temp_n_78,Product_mul_temp_n_79,Product_mul_temp_n_80,Product_mul_temp_n_81,Product_mul_temp_n_82,Product_mul_temp_n_83,Product_mul_temp_n_84,Product_mul_temp_n_85,Product_mul_temp_n_86,Product_mul_temp_n_87,Product_mul_temp_n_88,Product_mul_temp_n_89,Product_mul_temp_n_90,P,Product_mul_temp_n_97,Product_mul_temp_n_98,Product_mul_temp_n_99,Product_mul_temp_n_100,Product_mul_temp_n_101,Product_mul_temp_n_102,Product_mul_temp_n_103,Product_mul_temp_n_104,Product_mul_temp_n_105}),
        .PATTERNBDETECT(NLW_Product_mul_temp_PATTERNBDETECT_UNCONNECTED),
        .PATTERNDETECT(NLW_Product_mul_temp_PATTERNDETECT_UNCONNECTED),
        .PCIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .PCOUT(NLW_Product_mul_temp_PCOUT_UNCONNECTED[47:0]),
        .RSTA(reset),
        .RSTALLCARRYIN(1'b0),
        .RSTALUMODE(1'b0),
        .RSTB(reset),
        .RSTC(1'b0),
        .RSTCTRL(1'b0),
        .RSTD(1'b0),
        .RSTINMODE(1'b0),
        .RSTM(1'b0),
        .RSTP(1'b0),
        .UNDERFLOW(NLW_Product_mul_temp_UNDERFLOW_UNCONNECTED),
        .XOROUT(NLW_Product_mul_temp_XOROUT_UNCONNECTED[7:0]));
  FDRE \Product_mul_temp[-1111111102] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(Q[9]),
        .Q(\Product_mul_temp[-1111111102]_0 ),
        .R(reset));
  FDRE \Product_mul_temp[-1111111103] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(Q[8]),
        .Q(\Product_mul_temp[-1111111103]_0 ),
        .R(reset));
  FDRE \Product_mul_temp[-1111111104] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(Q[7]),
        .Q(\Product_mul_temp[-1111111104]_0 ),
        .R(reset));
  FDRE \Product_mul_temp[-1111111105] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(Q[6]),
        .Q(\Product_mul_temp[-1111111105]_0 ),
        .R(reset));
  FDRE \Product_mul_temp[-1111111106] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(Q[5]),
        .Q(\Product_mul_temp[-1111111106]_0 ),
        .R(reset));
  FDRE \Product_mul_temp[-1111111107] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(Q[4]),
        .Q(\Product_mul_temp[-1111111107]_0 ),
        .R(reset));
  FDRE \Product_mul_temp[-1111111108] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(Q[3]),
        .Q(\Product_mul_temp[-1111111108]_0 ),
        .R(reset));
  FDRE \Product_mul_temp[-1111111109] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(Q[2]),
        .Q(\Product_mul_temp[-1111111109]_0 ),
        .R(reset));
  FDRE \Product_mul_temp[-1111111110] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(Q[1]),
        .Q(\Product_mul_temp[-1111111110]_0 ),
        .R(reset));
  FDRE \Product_mul_temp[-1111111111] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(Q[0]),
        .Q(\Product_mul_temp[-1111111111]_0 ),
        .R(reset));
  CARRY8 Product_mul_temp__0_carry
       (.CI(1'b0),
        .CI_TOP(1'b0),
        .CO({Product_mul_temp__0_carry_n_0,Product_mul_temp__0_carry_n_1,Product_mul_temp__0_carry_n_2,Product_mul_temp__0_carry_n_3,Product_mul_temp__0_carry_n_4,Product_mul_temp__0_carry_n_5,Product_mul_temp__0_carry_n_6,Product_mul_temp__0_carry_n_7}),
        .DI({Product_mul_temp__0_carry_i_1_n_0,Product_mul_temp__0_carry_i_2_n_0,Product_mul_temp__0_carry_i_3_n_0,Product_mul_temp__0_carry_i_4_n_0,Product_mul_temp__0_carry_i_5_n_0,Product_mul_temp__0_carry_i_6_n_0,Product_mul_temp__0_carry_i_7_n_0,1'b0}),
        .O(Product_mul_temp__0[7:0]),
        .S({Product_mul_temp__0_carry_i_8_n_0,Product_mul_temp__0_carry_i_9_n_0,Product_mul_temp__0_carry_i_10_n_0,Product_mul_temp__0_carry_i_11_n_0,Product_mul_temp__0_carry_i_12_n_0,Product_mul_temp__0_carry_i_13_n_0,Product_mul_temp__0_carry_i_14_n_0,Product_mul_temp__0_carry_i_15_n_0}));
  CARRY8 Product_mul_temp__0_carry__0
       (.CI(Product_mul_temp__0_carry_n_0),
        .CI_TOP(1'b0),
        .CO({NLW_Product_mul_temp__0_carry__0_CO_UNCONNECTED[7:1],Product_mul_temp__0_carry__0_n_7}),
        .DI({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,Product_mul_temp__0_carry__0_i_1_n_0}),
        .O({NLW_Product_mul_temp__0_carry__0_O_UNCONNECTED[7:2],Product_mul_temp__0_carry__0_n_14,Product_mul_temp__0[8]}),
        .S({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,Product_mul_temp__0_carry__0_i_2_n_0,Product_mul_temp__0_carry__0_i_3_n_0}));
  LUT6 #(
    .INIT(64'hF888800080008000)) 
    Product_mul_temp__0_carry__0_i_1
       (.I0(HDL_Counter2_count_reg[11]),
        .I1(\Product_mul_temp[-1111111105]_0 ),
        .I2(\Product_mul_temp[-1111111104]_0 ),
        .I3(HDL_Counter2_count_reg[10]),
        .I4(\Product_mul_temp[-1111111106]_0 ),
        .I5(HDL_Counter2_count_reg[12]),
        .O(Product_mul_temp__0_carry__0_i_1_n_0));
  LUT4 #(
    .INIT(16'h6A95)) 
    Product_mul_temp__0_carry__0_i_2
       (.I0(Product_mul_temp__0_carry__0_i_4_n_0),
        .I1(\Product_mul_temp[-1111111102]_0 ),
        .I2(HDL_Counter2_count_reg[10]),
        .I3(Product_mul_temp__0_carry__0_i_5_n_0),
        .O(Product_mul_temp__0_carry__0_i_2_n_0));
  LUT6 #(
    .INIT(64'h956A6A956A956A95)) 
    Product_mul_temp__0_carry__0_i_3
       (.I0(Product_mul_temp__0_carry__0_i_1_n_0),
        .I1(HDL_Counter2_count_reg[11]),
        .I2(\Product_mul_temp[-1111111104]_0 ),
        .I3(Product_mul_temp__0_carry__0_i_6_n_0),
        .I4(\Product_mul_temp[-1111111103]_0 ),
        .I5(HDL_Counter2_count_reg[10]),
        .O(Product_mul_temp__0_carry__0_i_3_n_0));
  (* SOFT_HLUTNM = "soft_lutpair12" *) 
  LUT4 #(
    .INIT(16'h7888)) 
    Product_mul_temp__0_carry__0_i_4
       (.I0(HDL_Counter2_count_reg[12]),
        .I1(\Product_mul_temp[-1111111104]_0 ),
        .I2(HDL_Counter2_count_reg[11]),
        .I3(\Product_mul_temp[-1111111103]_0 ),
        .O(Product_mul_temp__0_carry__0_i_4_n_0));
  LUT6 #(
    .INIT(64'hF888800080008000)) 
    Product_mul_temp__0_carry__0_i_5
       (.I0(HDL_Counter2_count_reg[11]),
        .I1(\Product_mul_temp[-1111111104]_0 ),
        .I2(\Product_mul_temp[-1111111105]_0 ),
        .I3(HDL_Counter2_count_reg[12]),
        .I4(\Product_mul_temp[-1111111103]_0 ),
        .I5(HDL_Counter2_count_reg[10]),
        .O(Product_mul_temp__0_carry__0_i_5_n_0));
  LUT2 #(
    .INIT(4'h7)) 
    Product_mul_temp__0_carry__0_i_6
       (.I0(\Product_mul_temp[-1111111105]_0 ),
        .I1(HDL_Counter2_count_reg[12]),
        .O(Product_mul_temp__0_carry__0_i_6_n_0));
  LUT6 #(
    .INIT(64'hF880808088000000)) 
    Product_mul_temp__0_carry_i_1
       (.I0(HDL_Counter2_count_reg[11]),
        .I1(\Product_mul_temp[-1111111106]_0 ),
        .I2(\Product_mul_temp[-1111111105]_0 ),
        .I3(HDL_Counter2_count_reg[12]),
        .I4(\Product_mul_temp[-1111111107]_0 ),
        .I5(HDL_Counter2_count_reg[10]),
        .O(Product_mul_temp__0_carry_i_1_n_0));
  LUT6 #(
    .INIT(64'h956A6A956A956A95)) 
    Product_mul_temp__0_carry_i_10
       (.I0(Product_mul_temp__0_carry_i_3_n_0),
        .I1(HDL_Counter2_count_reg[11]),
        .I2(\Product_mul_temp[-1111111107]_0 ),
        .I3(Product_mul_temp__0_carry_i_18_n_0),
        .I4(\Product_mul_temp[-1111111106]_0 ),
        .I5(HDL_Counter2_count_reg[10]),
        .O(Product_mul_temp__0_carry_i_10_n_0));
  LUT6 #(
    .INIT(64'h956A6A6A6A959595)) 
    Product_mul_temp__0_carry_i_11
       (.I0(Product_mul_temp__0_carry_i_4_n_0),
        .I1(HDL_Counter2_count_reg[11]),
        .I2(\Product_mul_temp[-1111111108]_0 ),
        .I3(HDL_Counter2_count_reg[12]),
        .I4(\Product_mul_temp[-1111111109]_0 ),
        .I5(Product_mul_temp__0_carry_i_19_n_0),
        .O(Product_mul_temp__0_carry_i_11_n_0));
  LUT6 #(
    .INIT(64'h6A6A6A95C03FC03F)) 
    Product_mul_temp__0_carry_i_12
       (.I0(\Product_mul_temp[-1111111109]_0 ),
        .I1(\Product_mul_temp[-1111111108]_0 ),
        .I2(HDL_Counter2_count_reg[10]),
        .I3(Product_mul_temp__0_carry_i_20_n_0),
        .I4(\Product_mul_temp[-1111111111]_0 ),
        .I5(HDL_Counter2_count_reg[11]),
        .O(Product_mul_temp__0_carry_i_12_n_0));
  LUT6 #(
    .INIT(64'h8777788878887888)) 
    Product_mul_temp__0_carry_i_13
       (.I0(\Product_mul_temp[-1111111111]_0 ),
        .I1(HDL_Counter2_count_reg[12]),
        .I2(\Product_mul_temp[-1111111110]_0 ),
        .I3(HDL_Counter2_count_reg[11]),
        .I4(HDL_Counter2_count_reg[10]),
        .I5(\Product_mul_temp[-1111111109]_0 ),
        .O(Product_mul_temp__0_carry_i_13_n_0));
  LUT4 #(
    .INIT(16'h7888)) 
    Product_mul_temp__0_carry_i_14
       (.I0(HDL_Counter2_count_reg[10]),
        .I1(\Product_mul_temp[-1111111110]_0 ),
        .I2(HDL_Counter2_count_reg[11]),
        .I3(\Product_mul_temp[-1111111111]_0 ),
        .O(Product_mul_temp__0_carry_i_14_n_0));
  LUT2 #(
    .INIT(4'h8)) 
    Product_mul_temp__0_carry_i_15
       (.I0(\Product_mul_temp[-1111111111]_0 ),
        .I1(HDL_Counter2_count_reg[10]),
        .O(Product_mul_temp__0_carry_i_15_n_0));
  (* SOFT_HLUTNM = "soft_lutpair14" *) 
  LUT2 #(
    .INIT(4'h7)) 
    Product_mul_temp__0_carry_i_16
       (.I0(\Product_mul_temp[-1111111104]_0 ),
        .I1(HDL_Counter2_count_reg[10]),
        .O(Product_mul_temp__0_carry_i_16_n_0));
  LUT2 #(
    .INIT(4'h7)) 
    Product_mul_temp__0_carry_i_17
       (.I0(\Product_mul_temp[-1111111106]_0 ),
        .I1(HDL_Counter2_count_reg[11]),
        .O(Product_mul_temp__0_carry_i_17_n_0));
  (* SOFT_HLUTNM = "soft_lutpair12" *) 
  LUT2 #(
    .INIT(4'h7)) 
    Product_mul_temp__0_carry_i_18
       (.I0(\Product_mul_temp[-1111111108]_0 ),
        .I1(HDL_Counter2_count_reg[12]),
        .O(Product_mul_temp__0_carry_i_18_n_0));
  (* SOFT_HLUTNM = "soft_lutpair14" *) 
  LUT2 #(
    .INIT(4'h7)) 
    Product_mul_temp__0_carry_i_19
       (.I0(\Product_mul_temp[-1111111107]_0 ),
        .I1(HDL_Counter2_count_reg[10]),
        .O(Product_mul_temp__0_carry_i_19_n_0));
  LUT6 #(
    .INIT(64'hF888800080008000)) 
    Product_mul_temp__0_carry_i_2
       (.I0(\Product_mul_temp[-1111111107]_0 ),
        .I1(HDL_Counter2_count_reg[11]),
        .I2(\Product_mul_temp[-1111111108]_0 ),
        .I3(HDL_Counter2_count_reg[12]),
        .I4(\Product_mul_temp[-1111111106]_0 ),
        .I5(HDL_Counter2_count_reg[10]),
        .O(Product_mul_temp__0_carry_i_2_n_0));
  (* SOFT_HLUTNM = "soft_lutpair11" *) 
  LUT2 #(
    .INIT(4'h7)) 
    Product_mul_temp__0_carry_i_20
       (.I0(\Product_mul_temp[-1111111110]_0 ),
        .I1(HDL_Counter2_count_reg[12]),
        .O(Product_mul_temp__0_carry_i_20_n_0));
  LUT6 #(
    .INIT(64'hF888800080008000)) 
    Product_mul_temp__0_carry_i_3
       (.I0(HDL_Counter2_count_reg[11]),
        .I1(\Product_mul_temp[-1111111108]_0 ),
        .I2(\Product_mul_temp[-1111111107]_0 ),
        .I3(HDL_Counter2_count_reg[10]),
        .I4(\Product_mul_temp[-1111111109]_0 ),
        .I5(HDL_Counter2_count_reg[12]),
        .O(Product_mul_temp__0_carry_i_3_n_0));
  LUT6 #(
    .INIT(64'hF880808088000000)) 
    Product_mul_temp__0_carry_i_4
       (.I0(HDL_Counter2_count_reg[11]),
        .I1(\Product_mul_temp[-1111111109]_0 ),
        .I2(\Product_mul_temp[-1111111108]_0 ),
        .I3(HDL_Counter2_count_reg[12]),
        .I4(\Product_mul_temp[-1111111110]_0 ),
        .I5(HDL_Counter2_count_reg[10]),
        .O(Product_mul_temp__0_carry_i_4_n_0));
  LUT6 #(
    .INIT(64'h8777788878887888)) 
    Product_mul_temp__0_carry_i_5
       (.I0(HDL_Counter2_count_reg[10]),
        .I1(\Product_mul_temp[-1111111108]_0 ),
        .I2(\Product_mul_temp[-1111111109]_0 ),
        .I3(HDL_Counter2_count_reg[11]),
        .I4(\Product_mul_temp[-1111111110]_0 ),
        .I5(HDL_Counter2_count_reg[12]),
        .O(Product_mul_temp__0_carry_i_5_n_0));
  LUT4 #(
    .INIT(16'h7888)) 
    Product_mul_temp__0_carry_i_6
       (.I0(HDL_Counter2_count_reg[11]),
        .I1(\Product_mul_temp[-1111111110]_0 ),
        .I2(HDL_Counter2_count_reg[12]),
        .I3(\Product_mul_temp[-1111111111]_0 ),
        .O(Product_mul_temp__0_carry_i_6_n_0));
  LUT2 #(
    .INIT(4'h8)) 
    Product_mul_temp__0_carry_i_7
       (.I0(\Product_mul_temp[-1111111110]_0 ),
        .I1(HDL_Counter2_count_reg[10]),
        .O(Product_mul_temp__0_carry_i_7_n_0));
  LUT6 #(
    .INIT(64'h956A6A6A6A959595)) 
    Product_mul_temp__0_carry_i_8
       (.I0(Product_mul_temp__0_carry_i_1_n_0),
        .I1(HDL_Counter2_count_reg[11]),
        .I2(\Product_mul_temp[-1111111105]_0 ),
        .I3(HDL_Counter2_count_reg[12]),
        .I4(\Product_mul_temp[-1111111106]_0 ),
        .I5(Product_mul_temp__0_carry_i_16_n_0),
        .O(Product_mul_temp__0_carry_i_8_n_0));
  LUT6 #(
    .INIT(64'h956A6A956A956A95)) 
    Product_mul_temp__0_carry_i_9
       (.I0(Product_mul_temp__0_carry_i_2_n_0),
        .I1(HDL_Counter2_count_reg[12]),
        .I2(\Product_mul_temp[-1111111107]_0 ),
        .I3(Product_mul_temp__0_carry_i_17_n_0),
        .I4(\Product_mul_temp[-1111111105]_0 ),
        .I5(HDL_Counter2_count_reg[10]),
        .O(Product_mul_temp__0_carry_i_9_n_0));
  (* SOFT_HLUTNM = "soft_lutpair10" *) 
  LUT1 #(
    .INIT(2'h1)) 
    Product_mul_temp_i_2
       (.I0(HDL_Counter2_count_reg_7_sn_1),
        .O(HDL_Counter2_count_next));
  (* ADDER_THRESHOLD = "35" *) 
  CARRY8 \Product_mul_temp_inferred__0/i__carry 
       (.CI(1'b0),
        .CI_TOP(1'b0),
        .CO({\Product_mul_temp_inferred__0/i__carry_n_0 ,\Product_mul_temp_inferred__0/i__carry_n_1 ,\Product_mul_temp_inferred__0/i__carry_n_2 ,\Product_mul_temp_inferred__0/i__carry_n_3 ,\Product_mul_temp_inferred__0/i__carry_n_4 ,\Product_mul_temp_inferred__0/i__carry_n_5 ,\Product_mul_temp_inferred__0/i__carry_n_6 ,\Product_mul_temp_inferred__0/i__carry_n_7 }),
        .DI({Product_mul_temp_n_81,Product_mul_temp_n_82,Product_mul_temp_n_83,Product_mul_temp_n_84,Product_mul_temp_n_85,Product_mul_temp_n_86,Product_mul_temp_n_87,Product_mul_temp_n_88}),
        .O(Product_mul_temp0_out[7:0]),
        .S({i__carry_i_1__3_n_0,i__carry_i_2__3_n_0,i__carry_i_3__3_n_0,i__carry_i_4__3_n_0,i__carry_i_5__3_n_0,i__carry_i_6__3_n_0,i__carry_i_7__3_n_0,i__carry_i_8__3_n_0}));
  (* ADDER_THRESHOLD = "35" *) 
  CARRY8 \Product_mul_temp_inferred__0/i__carry__0 
       (.CI(\Product_mul_temp_inferred__0/i__carry_n_0 ),
        .CI_TOP(1'b0),
        .CO({\NLW_Product_mul_temp_inferred__0/i__carry__0_CO_UNCONNECTED [7:1],\Product_mul_temp_inferred__0/i__carry__0_n_7 }),
        .DI({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,Product_mul_temp_n_80}),
        .O({\NLW_Product_mul_temp_inferred__0/i__carry__0_O_UNCONNECTED [7:2],Product_mul_temp0_out[9:8]}),
        .S({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,i__carry__0_i_1__0_n_0,i__carry__0_i_2_n_0}));
  LUT6 #(
    .INIT(64'h8000000000000000)) 
    Switch6_out1_1_i_2
       (.I0(Switch6_out1_1_i_3_n_0),
        .I1(Switch6_out1_1_i_4_n_0),
        .I2(Switch6_out1_1_i_5_n_0),
        .I3(Switch6_out1_1_i_6_n_0),
        .I4(Switch6_out1_1_i_7_n_0),
        .I5(Switch6_out1_1_i_8_n_0),
        .O(Switch6_out1));
  LUT6 #(
    .INIT(64'h0000000000000001)) 
    Switch6_out1_1_i_3
       (.I0(P[2]),
        .I1(P[4]),
        .I2(P[5]),
        .I3(Product_mul_temp_n_89),
        .I4(P[1]),
        .I5(P[0]),
        .O(Switch6_out1_1_i_3_n_0));
  (* SOFT_HLUTNM = "soft_lutpair13" *) 
  LUT4 #(
    .INIT(16'h0001)) 
    Switch6_out1_1_i_4
       (.I0(Product_mul_temp0_out[9]),
        .I1(Product_mul_temp0_out[8]),
        .I2(Product_mul_temp0_out[6]),
        .I3(Product_mul_temp0_out[5]),
        .O(Switch6_out1_1_i_4_n_0));
  LUT3 #(
    .INIT(8'h01)) 
    Switch6_out1_1_i_5
       (.I0(Product_mul_temp0_out[3]),
        .I1(Product_mul_temp0_out[2]),
        .I2(Product_mul_temp0_out[0]),
        .O(Switch6_out1_1_i_5_n_0));
  LUT6 #(
    .INIT(64'h0000230000002323)) 
    Switch6_out1_1_i_6
       (.I0(Product_mul_temp_n_89),
        .I1(Product_mul_temp0_out[0]),
        .I2(Product_mul_temp_n_90),
        .I3(P[4]),
        .I4(P[5]),
        .I5(P[3]),
        .O(Switch6_out1_1_i_6_n_0));
  (* SOFT_HLUTNM = "soft_lutpair13" *) 
  LUT3 #(
    .INIT(8'h31)) 
    Switch6_out1_1_i_7
       (.I0(Product_mul_temp0_out[7]),
        .I1(Product_mul_temp0_out[9]),
        .I2(Product_mul_temp0_out[8]),
        .O(Switch6_out1_1_i_7_n_0));
  LUT6 #(
    .INIT(64'h0000230000002323)) 
    Switch6_out1_1_i_8
       (.I0(Product_mul_temp0_out[5]),
        .I1(Product_mul_temp0_out[6]),
        .I2(Product_mul_temp0_out[4]),
        .I3(Product_mul_temp0_out[2]),
        .I4(Product_mul_temp0_out[3]),
        .I5(Product_mul_temp0_out[1]),
        .O(Switch6_out1_1_i_8_n_0));
  LUT6 #(
    .INIT(64'hFCFCC040FCFCC0F4)) 
    Switch7_out12_carry__0_i_2
       (.I0(Relational_Operator_1_cast[11]),
        .I1(Product_mul_temp0_out[8]),
        .I2(Product_mul_temp0_out[9]),
        .I3(Switch7_out12_carry_0),
        .I4(Switch7_out12_carry),
        .I5(Relational_Operator_1_cast[12]),
        .O(\U1_norm_1_reg[11] ));
  LUT6 #(
    .INIT(64'h0201000030CC32CD)) 
    Switch7_out12_carry__0_i_4
       (.I0(Relational_Operator_1_cast[12]),
        .I1(Switch7_out12_carry),
        .I2(Switch7_out12_carry_0),
        .I3(Product_mul_temp0_out[9]),
        .I4(Relational_Operator_1_cast[11]),
        .I5(Product_mul_temp0_out[8]),
        .O(\U1_norm_1_reg[12] ));
  LUT6 #(
    .INIT(64'hFCFCFC40FCFCFCF4)) 
    Switch7_out12_carry_i_1
       (.I0(Relational_Operator_1_cast[9]),
        .I1(Product_mul_temp0_out[6]),
        .I2(Product_mul_temp0_out[7]),
        .I3(Switch7_out12_carry),
        .I4(Switch7_out12_carry_0),
        .I5(Relational_Operator_1_cast[10]),
        .O(\U1_norm_1_reg[9] [5]));
  LUT6 #(
    .INIT(64'h0201000000FC02FD)) 
    Switch7_out12_carry_i_10
       (.I0(Relational_Operator_1_cast[8]),
        .I1(Switch7_out12_carry_0),
        .I2(Switch7_out12_carry),
        .I3(Product_mul_temp0_out[5]),
        .I4(Relational_Operator_1_cast[7]),
        .I5(Product_mul_temp0_out[4]),
        .O(\U1_norm_1_reg[10] [4]));
  LUT6 #(
    .INIT(64'h020D000C00F002F1)) 
    Switch7_out12_carry_i_11
       (.I0(Relational_Operator_1_cast[6]),
        .I1(Switch7_out12_carry_0),
        .I2(Switch7_out12_carry),
        .I3(Product_mul_temp0_out[3]),
        .I4(Relational_Operator_1_cast[5]),
        .I5(Product_mul_temp0_out[2]),
        .O(\U1_norm_1_reg[10] [3]));
  LUT6 #(
    .INIT(64'h020D000C00F002F1)) 
    Switch7_out12_carry_i_12
       (.I0(Relational_Operator_1_cast[4]),
        .I1(Switch7_out12_carry_0),
        .I2(Switch7_out12_carry),
        .I3(Product_mul_temp0_out[1]),
        .I4(Relational_Operator_1_cast[3]),
        .I5(Product_mul_temp0_out[0]),
        .O(\U1_norm_1_reg[10] [2]));
  LUT6 #(
    .INIT(64'h0201000000FC02FD)) 
    Switch7_out12_carry_i_13
       (.I0(Relational_Operator_1_cast[2]),
        .I1(Switch7_out12_carry_0),
        .I2(Switch7_out12_carry),
        .I3(Product_mul_temp_n_89),
        .I4(Relational_Operator_1_cast[1]),
        .I5(Product_mul_temp_n_90),
        .O(\U1_norm_1_reg[10] [1]));
  LUT5 #(
    .INIT(32'h000C02F1)) 
    Switch7_out12_carry_i_14
       (.I0(Relational_Operator_1_cast[0]),
        .I1(Switch7_out12_carry_0),
        .I2(Switch7_out12_carry),
        .I3(P[5]),
        .I4(P[4]),
        .O(\U1_norm_1_reg[10] [0]));
  LUT6 #(
    .INIT(64'hFCFCFC40FCFCFCF4)) 
    Switch7_out12_carry_i_2
       (.I0(Relational_Operator_1_cast[7]),
        .I1(Product_mul_temp0_out[4]),
        .I2(Product_mul_temp0_out[5]),
        .I3(Switch7_out12_carry),
        .I4(Switch7_out12_carry_0),
        .I5(Relational_Operator_1_cast[8]),
        .O(\U1_norm_1_reg[9] [4]));
  LUT6 #(
    .INIT(64'hFCF0FC40FCF0FCF4)) 
    Switch7_out12_carry_i_3
       (.I0(Relational_Operator_1_cast[5]),
        .I1(Product_mul_temp0_out[2]),
        .I2(Product_mul_temp0_out[3]),
        .I3(Switch7_out12_carry),
        .I4(Switch7_out12_carry_0),
        .I5(Relational_Operator_1_cast[6]),
        .O(\U1_norm_1_reg[9] [3]));
  LUT6 #(
    .INIT(64'hFCF0FC40FCF0FCF4)) 
    Switch7_out12_carry_i_4
       (.I0(Relational_Operator_1_cast[3]),
        .I1(Product_mul_temp0_out[0]),
        .I2(Product_mul_temp0_out[1]),
        .I3(Switch7_out12_carry),
        .I4(Switch7_out12_carry_0),
        .I5(Relational_Operator_1_cast[4]),
        .O(\U1_norm_1_reg[9] [2]));
  LUT6 #(
    .INIT(64'hFCFCFC40FCFCFCF4)) 
    Switch7_out12_carry_i_5
       (.I0(Relational_Operator_1_cast[1]),
        .I1(Product_mul_temp_n_90),
        .I2(Product_mul_temp_n_89),
        .I3(Switch7_out12_carry),
        .I4(Switch7_out12_carry_0),
        .I5(Relational_Operator_1_cast[2]),
        .O(\U1_norm_1_reg[9] [1]));
  LUT4 #(
    .INIT(16'hE0EE)) 
    Switch7_out12_carry_i_7
       (.I0(P[3]),
        .I1(P[2]),
        .I2(Switch7_out12_carry),
        .I3(Switch7_out12_carry_0),
        .O(\U1_norm_1_reg[9] [0]));
  LUT6 #(
    .INIT(64'h0201000000FC02FD)) 
    Switch7_out12_carry_i_9
       (.I0(Relational_Operator_1_cast[10]),
        .I1(Switch7_out12_carry_0),
        .I2(Switch7_out12_carry),
        .I3(Product_mul_temp0_out[7]),
        .I4(Relational_Operator_1_cast[9]),
        .I5(Product_mul_temp0_out[6]),
        .O(\U1_norm_1_reg[10] [5]));
  LUT5 #(
    .INIT(32'h000000B8)) 
    Switch8_out12_carry__0_i_1
       (.I0(\Delay1_out1_reg[13]_0 [13]),
        .I1(Allow_assymetrical_anew_reference_value__0),
        .I2(\Delay1_out1_reg[13] [13]),
        .I3(Switch8_out12_carry),
        .I4(Switch8_out12_carry_0),
        .O(\U2_norm_1_reg[13]_0 [1]));
  LUT6 #(
    .INIT(64'hFCFCC040FCFCC0F4)) 
    Switch8_out12_carry__0_i_2
       (.I0(\U2_norm_1_reg[12]_0 [11]),
        .I1(Product_mul_temp0_out[8]),
        .I2(Product_mul_temp0_out[9]),
        .I3(Switch8_out12_carry),
        .I4(Switch8_out12_carry_0),
        .I5(\U2_norm_1_reg[12]_0 [12]),
        .O(\U2_norm_1_reg[13]_0 [0]));
  LUT6 #(
    .INIT(64'h0201000030CC32CD)) 
    Switch8_out12_carry__0_i_4
       (.I0(\U2_norm_1_reg[12]_0 [12]),
        .I1(Switch8_out12_carry_0),
        .I2(Switch8_out12_carry),
        .I3(Product_mul_temp0_out[9]),
        .I4(\U2_norm_1_reg[12]_0 [11]),
        .I5(Product_mul_temp0_out[8]),
        .O(\U2_norm_1_reg[12] ));
  LUT6 #(
    .INIT(64'hFCFCFC40FCFCFCF4)) 
    Switch8_out12_carry_i_1
       (.I0(\U2_norm_1_reg[12]_0 [9]),
        .I1(Product_mul_temp0_out[6]),
        .I2(Product_mul_temp0_out[7]),
        .I3(Switch8_out12_carry_0),
        .I4(Switch8_out12_carry),
        .I5(\U2_norm_1_reg[12]_0 [10]),
        .O(\U2_norm_1_reg[9] [7]));
  LUT6 #(
    .INIT(64'h0201000000FC02FD)) 
    Switch8_out12_carry_i_10
       (.I0(\U2_norm_1_reg[12]_0 [8]),
        .I1(Switch8_out12_carry),
        .I2(Switch8_out12_carry_0),
        .I3(Product_mul_temp0_out[5]),
        .I4(\U2_norm_1_reg[12]_0 [7]),
        .I5(Product_mul_temp0_out[4]),
        .O(\U2_norm_1_reg[10] [6]));
  LUT6 #(
    .INIT(64'h020D000C00F002F1)) 
    Switch8_out12_carry_i_11
       (.I0(\U2_norm_1_reg[12]_0 [6]),
        .I1(Switch8_out12_carry),
        .I2(Switch8_out12_carry_0),
        .I3(Product_mul_temp0_out[3]),
        .I4(\U2_norm_1_reg[12]_0 [5]),
        .I5(Product_mul_temp0_out[2]),
        .O(\U2_norm_1_reg[10] [5]));
  LUT6 #(
    .INIT(64'h020D000C00F002F1)) 
    Switch8_out12_carry_i_12
       (.I0(\U2_norm_1_reg[12]_0 [4]),
        .I1(Switch8_out12_carry),
        .I2(Switch8_out12_carry_0),
        .I3(Product_mul_temp0_out[1]),
        .I4(\U2_norm_1_reg[12]_0 [3]),
        .I5(Product_mul_temp0_out[0]),
        .O(\U2_norm_1_reg[10] [4]));
  LUT6 #(
    .INIT(64'h0201000000FC02FD)) 
    Switch8_out12_carry_i_13
       (.I0(\U2_norm_1_reg[12]_0 [2]),
        .I1(Switch8_out12_carry),
        .I2(Switch8_out12_carry_0),
        .I3(Product_mul_temp_n_89),
        .I4(\U2_norm_1_reg[12]_0 [1]),
        .I5(Product_mul_temp_n_90),
        .O(\U2_norm_1_reg[10] [3]));
  LUT5 #(
    .INIT(32'h000C02F1)) 
    Switch8_out12_carry_i_14
       (.I0(\U2_norm_1_reg[12]_0 [0]),
        .I1(Switch8_out12_carry),
        .I2(Switch8_out12_carry_0),
        .I3(P[5]),
        .I4(P[4]),
        .O(\U2_norm_1_reg[10] [2]));
  LUT4 #(
    .INIT(16'h200D)) 
    Switch8_out12_carry_i_15
       (.I0(Switch8_out12_carry),
        .I1(Switch8_out12_carry_0),
        .I2(P[2]),
        .I3(P[3]),
        .O(\U2_norm_1_reg[10] [1]));
  LUT4 #(
    .INIT(16'h020D)) 
    Switch8_out12_carry_i_16
       (.I0(Switch8_out12_carry),
        .I1(Switch8_out12_carry_0),
        .I2(P[0]),
        .I3(P[1]),
        .O(\U2_norm_1_reg[10] [0]));
  LUT6 #(
    .INIT(64'hFCFCFC40FCFCFCF4)) 
    Switch8_out12_carry_i_2
       (.I0(\U2_norm_1_reg[12]_0 [7]),
        .I1(Product_mul_temp0_out[4]),
        .I2(Product_mul_temp0_out[5]),
        .I3(Switch8_out12_carry_0),
        .I4(Switch8_out12_carry),
        .I5(\U2_norm_1_reg[12]_0 [8]),
        .O(\U2_norm_1_reg[9] [6]));
  LUT6 #(
    .INIT(64'hFCF0FC40FCF0FCF4)) 
    Switch8_out12_carry_i_3
       (.I0(\U2_norm_1_reg[12]_0 [5]),
        .I1(Product_mul_temp0_out[2]),
        .I2(Product_mul_temp0_out[3]),
        .I3(Switch8_out12_carry_0),
        .I4(Switch8_out12_carry),
        .I5(\U2_norm_1_reg[12]_0 [6]),
        .O(\U2_norm_1_reg[9] [5]));
  LUT6 #(
    .INIT(64'hFCF0FC40FCF0FCF4)) 
    Switch8_out12_carry_i_4
       (.I0(\U2_norm_1_reg[12]_0 [3]),
        .I1(Product_mul_temp0_out[0]),
        .I2(Product_mul_temp0_out[1]),
        .I3(Switch8_out12_carry_0),
        .I4(Switch8_out12_carry),
        .I5(\U2_norm_1_reg[12]_0 [4]),
        .O(\U2_norm_1_reg[9] [4]));
  LUT6 #(
    .INIT(64'hFCFCFC40FCFCFCF4)) 
    Switch8_out12_carry_i_5
       (.I0(\U2_norm_1_reg[12]_0 [1]),
        .I1(Product_mul_temp_n_90),
        .I2(Product_mul_temp_n_89),
        .I3(Switch8_out12_carry_0),
        .I4(Switch8_out12_carry),
        .I5(\U2_norm_1_reg[12]_0 [2]),
        .O(\U2_norm_1_reg[9] [3]));
  LUT5 #(
    .INIT(32'hECE8ECEE)) 
    Switch8_out12_carry_i_6
       (.I0(P[4]),
        .I1(P[5]),
        .I2(Switch8_out12_carry_0),
        .I3(Switch8_out12_carry),
        .I4(\U2_norm_1_reg[12]_0 [0]),
        .O(\U2_norm_1_reg[9] [2]));
  LUT4 #(
    .INIT(16'hE0EE)) 
    Switch8_out12_carry_i_7
       (.I0(P[3]),
        .I1(P[2]),
        .I2(Switch8_out12_carry_0),
        .I3(Switch8_out12_carry),
        .O(\U2_norm_1_reg[9] [1]));
  LUT4 #(
    .INIT(16'hFDD0)) 
    Switch8_out12_carry_i_8
       (.I0(Switch8_out12_carry),
        .I1(Switch8_out12_carry_0),
        .I2(P[0]),
        .I3(P[1]),
        .O(\U2_norm_1_reg[9] [0]));
  LUT6 #(
    .INIT(64'h0201000000FC02FD)) 
    Switch8_out12_carry_i_9
       (.I0(\U2_norm_1_reg[12]_0 [10]),
        .I1(Switch8_out12_carry),
        .I2(Switch8_out12_carry_0),
        .I3(Product_mul_temp0_out[7]),
        .I4(\U2_norm_1_reg[12]_0 [9]),
        .I5(Product_mul_temp0_out[6]),
        .O(\U2_norm_1_reg[10] [7]));
  LUT5 #(
    .INIT(32'h000000B8)) 
    Switch9_out12_carry__0_i_1
       (.I0(\Delay2_out1_reg[13]_0 [13]),
        .I1(Allow_assymetrical_anew_reference_value__0),
        .I2(\Delay2_out1_reg[13] [13]),
        .I3(Switch9_out12_carry),
        .I4(Switch9_out12_carry_0),
        .O(\U3_norm_1_reg[13]_0 [1]));
  LUT6 #(
    .INIT(64'hFCFCC040FCFCC0F4)) 
    Switch9_out12_carry__0_i_2
       (.I0(\U3_norm_1_reg[12]_0 [11]),
        .I1(Product_mul_temp0_out[8]),
        .I2(Product_mul_temp0_out[9]),
        .I3(Switch9_out12_carry),
        .I4(Switch9_out12_carry_0),
        .I5(\U3_norm_1_reg[12]_0 [12]),
        .O(\U3_norm_1_reg[13]_0 [0]));
  LUT6 #(
    .INIT(64'h0201000030CC32CD)) 
    Switch9_out12_carry__0_i_4
       (.I0(\U3_norm_1_reg[12]_0 [12]),
        .I1(Switch9_out12_carry_0),
        .I2(Switch9_out12_carry),
        .I3(Product_mul_temp0_out[9]),
        .I4(\U3_norm_1_reg[12]_0 [11]),
        .I5(Product_mul_temp0_out[8]),
        .O(\U3_norm_1_reg[12] ));
  LUT6 #(
    .INIT(64'hFCFCFC40FCFCFCF4)) 
    Switch9_out12_carry_i_1
       (.I0(\U3_norm_1_reg[12]_0 [9]),
        .I1(Product_mul_temp0_out[6]),
        .I2(Product_mul_temp0_out[7]),
        .I3(Switch9_out12_carry_0),
        .I4(Switch9_out12_carry),
        .I5(\U3_norm_1_reg[12]_0 [10]),
        .O(\U3_norm_1_reg[9] [7]));
  LUT6 #(
    .INIT(64'h0201000000FC02FD)) 
    Switch9_out12_carry_i_10
       (.I0(\U3_norm_1_reg[12]_0 [8]),
        .I1(Switch9_out12_carry),
        .I2(Switch9_out12_carry_0),
        .I3(Product_mul_temp0_out[5]),
        .I4(\U3_norm_1_reg[12]_0 [7]),
        .I5(Product_mul_temp0_out[4]),
        .O(\U3_norm_1_reg[10] [6]));
  LUT6 #(
    .INIT(64'h020D000C00F002F1)) 
    Switch9_out12_carry_i_11
       (.I0(\U3_norm_1_reg[12]_0 [6]),
        .I1(Switch9_out12_carry),
        .I2(Switch9_out12_carry_0),
        .I3(Product_mul_temp0_out[3]),
        .I4(\U3_norm_1_reg[12]_0 [5]),
        .I5(Product_mul_temp0_out[2]),
        .O(\U3_norm_1_reg[10] [5]));
  LUT6 #(
    .INIT(64'h020D000C00F002F1)) 
    Switch9_out12_carry_i_12
       (.I0(\U3_norm_1_reg[12]_0 [4]),
        .I1(Switch9_out12_carry),
        .I2(Switch9_out12_carry_0),
        .I3(Product_mul_temp0_out[1]),
        .I4(\U3_norm_1_reg[12]_0 [3]),
        .I5(Product_mul_temp0_out[0]),
        .O(\U3_norm_1_reg[10] [4]));
  LUT6 #(
    .INIT(64'h0201000000FC02FD)) 
    Switch9_out12_carry_i_13
       (.I0(\U3_norm_1_reg[12]_0 [2]),
        .I1(Switch9_out12_carry),
        .I2(Switch9_out12_carry_0),
        .I3(Product_mul_temp_n_89),
        .I4(\U3_norm_1_reg[12]_0 [1]),
        .I5(Product_mul_temp_n_90),
        .O(\U3_norm_1_reg[10] [3]));
  LUT5 #(
    .INIT(32'h000C02F1)) 
    Switch9_out12_carry_i_14
       (.I0(\U3_norm_1_reg[12]_0 [0]),
        .I1(Switch9_out12_carry),
        .I2(Switch9_out12_carry_0),
        .I3(P[5]),
        .I4(P[4]),
        .O(\U3_norm_1_reg[10] [2]));
  LUT4 #(
    .INIT(16'h200D)) 
    Switch9_out12_carry_i_15
       (.I0(Switch9_out12_carry),
        .I1(Switch9_out12_carry_0),
        .I2(P[2]),
        .I3(P[3]),
        .O(\U3_norm_1_reg[10] [1]));
  LUT4 #(
    .INIT(16'h020D)) 
    Switch9_out12_carry_i_16
       (.I0(Switch9_out12_carry),
        .I1(Switch9_out12_carry_0),
        .I2(P[0]),
        .I3(P[1]),
        .O(\U3_norm_1_reg[10] [0]));
  LUT6 #(
    .INIT(64'hFCFCFC40FCFCFCF4)) 
    Switch9_out12_carry_i_2
       (.I0(\U3_norm_1_reg[12]_0 [7]),
        .I1(Product_mul_temp0_out[4]),
        .I2(Product_mul_temp0_out[5]),
        .I3(Switch9_out12_carry_0),
        .I4(Switch9_out12_carry),
        .I5(\U3_norm_1_reg[12]_0 [8]),
        .O(\U3_norm_1_reg[9] [6]));
  LUT6 #(
    .INIT(64'hFCF0FC40FCF0FCF4)) 
    Switch9_out12_carry_i_3
       (.I0(\U3_norm_1_reg[12]_0 [5]),
        .I1(Product_mul_temp0_out[2]),
        .I2(Product_mul_temp0_out[3]),
        .I3(Switch9_out12_carry_0),
        .I4(Switch9_out12_carry),
        .I5(\U3_norm_1_reg[12]_0 [6]),
        .O(\U3_norm_1_reg[9] [5]));
  LUT6 #(
    .INIT(64'hFCF0FC40FCF0FCF4)) 
    Switch9_out12_carry_i_4
       (.I0(\U3_norm_1_reg[12]_0 [3]),
        .I1(Product_mul_temp0_out[0]),
        .I2(Product_mul_temp0_out[1]),
        .I3(Switch9_out12_carry_0),
        .I4(Switch9_out12_carry),
        .I5(\U3_norm_1_reg[12]_0 [4]),
        .O(\U3_norm_1_reg[9] [4]));
  LUT6 #(
    .INIT(64'hFCFCFC40FCFCFCF4)) 
    Switch9_out12_carry_i_5
       (.I0(\U3_norm_1_reg[12]_0 [1]),
        .I1(Product_mul_temp_n_90),
        .I2(Product_mul_temp_n_89),
        .I3(Switch9_out12_carry_0),
        .I4(Switch9_out12_carry),
        .I5(\U3_norm_1_reg[12]_0 [2]),
        .O(\U3_norm_1_reg[9] [3]));
  LUT5 #(
    .INIT(32'hECE8ECEE)) 
    Switch9_out12_carry_i_6
       (.I0(P[4]),
        .I1(P[5]),
        .I2(Switch9_out12_carry_0),
        .I3(Switch9_out12_carry),
        .I4(\U3_norm_1_reg[12]_0 [0]),
        .O(\U3_norm_1_reg[9] [2]));
  LUT4 #(
    .INIT(16'hE0EE)) 
    Switch9_out12_carry_i_7
       (.I0(P[3]),
        .I1(P[2]),
        .I2(Switch9_out12_carry_0),
        .I3(Switch9_out12_carry),
        .O(\U3_norm_1_reg[9] [1]));
  LUT4 #(
    .INIT(16'hFDD0)) 
    Switch9_out12_carry_i_8
       (.I0(Switch9_out12_carry),
        .I1(Switch9_out12_carry_0),
        .I2(P[0]),
        .I3(P[1]),
        .O(\U3_norm_1_reg[9] [0]));
  LUT6 #(
    .INIT(64'h0201000000FC02FD)) 
    Switch9_out12_carry_i_9
       (.I0(\U3_norm_1_reg[12]_0 [10]),
        .I1(Switch9_out12_carry),
        .I2(Switch9_out12_carry_0),
        .I3(Product_mul_temp0_out[7]),
        .I4(\U3_norm_1_reg[12]_0 [9]),
        .I5(Product_mul_temp0_out[6]),
        .O(\U3_norm_1_reg[10] [7]));
  LUT2 #(
    .INIT(4'h9)) 
    i__carry__0_i_1__0
       (.I0(Product_mul_temp_n_79),
        .I1(Product_mul_temp__0_carry__0_n_14),
        .O(i__carry__0_i_1__0_n_0));
  LUT2 #(
    .INIT(4'h6)) 
    i__carry__0_i_2
       (.I0(Product_mul_temp_n_80),
        .I1(Product_mul_temp__0[8]),
        .O(i__carry__0_i_2_n_0));
  LUT6 #(
    .INIT(64'h22222222BBB222B2)) 
    i__carry_i_1
       (.I0(Add_out1[13]),
        .I1(\U3_norm_1_reg[13] ),
        .I2(\Delay2_out1_reg[13] [12]),
        .I3(Allow_assymetrical_anew_reference_value__0),
        .I4(\Delay2_out1_reg[13]_0 [12]),
        .I5(Add_out1[12]),
        .O(\Delay2_out1_reg[12] [6]));
  LUT6 #(
    .INIT(64'h9990009000099909)) 
    i__carry_i_10
       (.I0(\U3_norm_1_reg[12]_0 [9]),
        .I1(Add_out1[9]),
        .I2(\Delay2_out1_reg[13] [8]),
        .I3(Allow_assymetrical_anew_reference_value__0),
        .I4(\Delay2_out1_reg[13]_0 [8]),
        .I5(Add_out1[8]),
        .O(\Delay2_out1_reg[12]_0 [4]));
  LUT6 #(
    .INIT(64'h9990009000099909)) 
    i__carry_i_10__0
       (.I0(\U2_norm_1_reg[12]_0 [9]),
        .I1(Add_out1[9]),
        .I2(\Delay1_out1_reg[13] [8]),
        .I3(Allow_assymetrical_anew_reference_value__0),
        .I4(\Delay1_out1_reg[13]_0 [8]),
        .I5(Add_out1[8]),
        .O(\Delay1_out1_reg[12]_0 [4]));
  LUT6 #(
    .INIT(64'hA95900000000A959)) 
    i__carry_i_10__1
       (.I0(Add_out1[8]),
        .I1(\Delay_out1_reg[13] [8]),
        .I2(Allow_assymetrical_anew_reference_value__0),
        .I3(\Delay_out1_reg[13]_0 [8]),
        .I4(Relational_Operator_1_cast[9]),
        .I5(Add_out1[9]),
        .O(\Delay_out1_reg[12]_0 [4]));
  LUT6 #(
    .INIT(64'h9990009000099909)) 
    i__carry_i_11
       (.I0(\U3_norm_1_reg[12]_0 [7]),
        .I1(Add_out1[7]),
        .I2(\Delay2_out1_reg[13] [6]),
        .I3(Allow_assymetrical_anew_reference_value__0),
        .I4(\Delay2_out1_reg[13]_0 [6]),
        .I5(Add_out1[6]),
        .O(\Delay2_out1_reg[12]_0 [3]));
  LUT6 #(
    .INIT(64'h9990009000099909)) 
    i__carry_i_11__0
       (.I0(\U2_norm_1_reg[12]_0 [7]),
        .I1(Add_out1[7]),
        .I2(\Delay1_out1_reg[13] [6]),
        .I3(Allow_assymetrical_anew_reference_value__0),
        .I4(\Delay1_out1_reg[13]_0 [6]),
        .I5(Add_out1[6]),
        .O(\Delay1_out1_reg[12]_0 [3]));
  LUT6 #(
    .INIT(64'hA95900000000A959)) 
    i__carry_i_11__1
       (.I0(Add_out1[6]),
        .I1(\Delay_out1_reg[13] [6]),
        .I2(Allow_assymetrical_anew_reference_value__0),
        .I3(\Delay_out1_reg[13]_0 [6]),
        .I4(Relational_Operator_1_cast[7]),
        .I5(Add_out1[7]),
        .O(\Delay_out1_reg[12]_0 [3]));
  LUT6 #(
    .INIT(64'h9990009000099909)) 
    i__carry_i_12
       (.I0(\U3_norm_1_reg[12]_0 [5]),
        .I1(Add_out1[5]),
        .I2(\Delay2_out1_reg[13] [4]),
        .I3(Allow_assymetrical_anew_reference_value__0),
        .I4(\Delay2_out1_reg[13]_0 [4]),
        .I5(Add_out1[4]),
        .O(\Delay2_out1_reg[12]_0 [2]));
  LUT6 #(
    .INIT(64'h9990009000099909)) 
    i__carry_i_12__0
       (.I0(\U2_norm_1_reg[12]_0 [5]),
        .I1(Add_out1[5]),
        .I2(\Delay1_out1_reg[13] [4]),
        .I3(Allow_assymetrical_anew_reference_value__0),
        .I4(\Delay1_out1_reg[13]_0 [4]),
        .I5(Add_out1[4]),
        .O(\Delay1_out1_reg[12]_0 [2]));
  LUT6 #(
    .INIT(64'hA95900000000A959)) 
    i__carry_i_12__1
       (.I0(Add_out1[4]),
        .I1(\Delay_out1_reg[13] [4]),
        .I2(Allow_assymetrical_anew_reference_value__0),
        .I3(\Delay_out1_reg[13]_0 [4]),
        .I4(Relational_Operator_1_cast[5]),
        .I5(Add_out1[5]),
        .O(\Delay_out1_reg[12]_0 [2]));
  LUT6 #(
    .INIT(64'h9990009000099909)) 
    i__carry_i_13
       (.I0(\U3_norm_1_reg[12]_0 [3]),
        .I1(Add_out1[3]),
        .I2(\Delay2_out1_reg[13] [2]),
        .I3(Allow_assymetrical_anew_reference_value__0),
        .I4(\Delay2_out1_reg[13]_0 [2]),
        .I5(Add_out1[2]),
        .O(\Delay2_out1_reg[12]_0 [1]));
  LUT6 #(
    .INIT(64'h9990009000099909)) 
    i__carry_i_13__0
       (.I0(\U2_norm_1_reg[12]_0 [3]),
        .I1(Add_out1[3]),
        .I2(\Delay1_out1_reg[13] [2]),
        .I3(Allow_assymetrical_anew_reference_value__0),
        .I4(\Delay1_out1_reg[13]_0 [2]),
        .I5(Add_out1[2]),
        .O(\Delay1_out1_reg[12]_0 [1]));
  LUT6 #(
    .INIT(64'hA95900000000A959)) 
    i__carry_i_13__1
       (.I0(Add_out1[2]),
        .I1(\Delay_out1_reg[13] [2]),
        .I2(Allow_assymetrical_anew_reference_value__0),
        .I3(\Delay_out1_reg[13]_0 [2]),
        .I4(Relational_Operator_1_cast[3]),
        .I5(Add_out1[3]),
        .O(\Delay_out1_reg[12]_0 [1]));
  LUT6 #(
    .INIT(64'h9990009000099909)) 
    i__carry_i_14
       (.I0(\U3_norm_1_reg[12]_0 [1]),
        .I1(Add_out1[1]),
        .I2(\Delay2_out1_reg[13] [0]),
        .I3(Allow_assymetrical_anew_reference_value__0),
        .I4(\Delay2_out1_reg[13]_0 [0]),
        .I5(Add_out1[0]),
        .O(\Delay2_out1_reg[12]_0 [0]));
  LUT6 #(
    .INIT(64'h9990009000099909)) 
    i__carry_i_14__0
       (.I0(\U2_norm_1_reg[12]_0 [1]),
        .I1(Add_out1[1]),
        .I2(\Delay1_out1_reg[13] [0]),
        .I3(Allow_assymetrical_anew_reference_value__0),
        .I4(\Delay1_out1_reg[13]_0 [0]),
        .I5(Add_out1[0]),
        .O(\Delay1_out1_reg[12]_0 [0]));
  LUT6 #(
    .INIT(64'hA95900000000A959)) 
    i__carry_i_14__1
       (.I0(Add_out1[0]),
        .I1(\Delay_out1_reg[13] [0]),
        .I2(Allow_assymetrical_anew_reference_value__0),
        .I3(\Delay_out1_reg[13]_0 [0]),
        .I4(Relational_Operator_1_cast[1]),
        .I5(Add_out1[1]),
        .O(\Delay_out1_reg[12]_0 [0]));
  LUT6 #(
    .INIT(64'h22222222BBB222B2)) 
    i__carry_i_1__0
       (.I0(Add_out1[13]),
        .I1(\U2_norm_1_reg[13] ),
        .I2(\Delay1_out1_reg[13] [12]),
        .I3(Allow_assymetrical_anew_reference_value__0),
        .I4(\Delay1_out1_reg[13]_0 [12]),
        .I5(Add_out1[12]),
        .O(\Delay1_out1_reg[12] [6]));
  LUT6 #(
    .INIT(64'h22222222BBB222B2)) 
    i__carry_i_1__1
       (.I0(Add_out1[13]),
        .I1(Relational_Operator_1_cast[13]),
        .I2(\Delay_out1_reg[13] [12]),
        .I3(Allow_assymetrical_anew_reference_value__0),
        .I4(\Delay_out1_reg[13]_0 [12]),
        .I5(Add_out1[12]),
        .O(\Delay_out1_reg[12] [6]));
  LUT2 #(
    .INIT(4'h6)) 
    i__carry_i_1__3
       (.I0(Product_mul_temp_n_81),
        .I1(Product_mul_temp__0[7]),
        .O(i__carry_i_1__3_n_0));
  LUT6 #(
    .INIT(64'h22222222BBB222B2)) 
    i__carry_i_2
       (.I0(\U3_norm_1_reg[12]_0 [11]),
        .I1(Add_out1[11]),
        .I2(\Delay2_out1_reg[13] [10]),
        .I3(Allow_assymetrical_anew_reference_value__0),
        .I4(\Delay2_out1_reg[13]_0 [10]),
        .I5(Add_out1[10]),
        .O(\Delay2_out1_reg[12] [5]));
  LUT6 #(
    .INIT(64'h22222222BBB222B2)) 
    i__carry_i_2__0
       (.I0(\U2_norm_1_reg[12]_0 [11]),
        .I1(Add_out1[11]),
        .I2(\Delay1_out1_reg[13] [10]),
        .I3(Allow_assymetrical_anew_reference_value__0),
        .I4(\Delay1_out1_reg[13]_0 [10]),
        .I5(Add_out1[10]),
        .O(\Delay1_out1_reg[12] [5]));
  LUT6 #(
    .INIT(64'h22222222BBB222B2)) 
    i__carry_i_2__1
       (.I0(Relational_Operator_1_cast[11]),
        .I1(Add_out1[11]),
        .I2(\Delay_out1_reg[13] [10]),
        .I3(Allow_assymetrical_anew_reference_value__0),
        .I4(\Delay_out1_reg[13]_0 [10]),
        .I5(Add_out1[10]),
        .O(\Delay_out1_reg[12] [5]));
  LUT2 #(
    .INIT(4'h6)) 
    i__carry_i_2__3
       (.I0(Product_mul_temp_n_82),
        .I1(Product_mul_temp__0[6]),
        .O(i__carry_i_2__3_n_0));
  LUT6 #(
    .INIT(64'h22222222BBB222B2)) 
    i__carry_i_3
       (.I0(\U3_norm_1_reg[12]_0 [9]),
        .I1(Add_out1[9]),
        .I2(\Delay2_out1_reg[13] [8]),
        .I3(Allow_assymetrical_anew_reference_value__0),
        .I4(\Delay2_out1_reg[13]_0 [8]),
        .I5(Add_out1[8]),
        .O(\Delay2_out1_reg[12] [4]));
  LUT6 #(
    .INIT(64'h22222222BBB222B2)) 
    i__carry_i_3__0
       (.I0(\U2_norm_1_reg[12]_0 [9]),
        .I1(Add_out1[9]),
        .I2(\Delay1_out1_reg[13] [8]),
        .I3(Allow_assymetrical_anew_reference_value__0),
        .I4(\Delay1_out1_reg[13]_0 [8]),
        .I5(Add_out1[8]),
        .O(\Delay1_out1_reg[12] [4]));
  LUT6 #(
    .INIT(64'h22222222BBB222B2)) 
    i__carry_i_3__1
       (.I0(Relational_Operator_1_cast[9]),
        .I1(Add_out1[9]),
        .I2(\Delay_out1_reg[13] [8]),
        .I3(Allow_assymetrical_anew_reference_value__0),
        .I4(\Delay_out1_reg[13]_0 [8]),
        .I5(Add_out1[8]),
        .O(\Delay_out1_reg[12] [4]));
  LUT2 #(
    .INIT(4'h6)) 
    i__carry_i_3__3
       (.I0(Product_mul_temp_n_83),
        .I1(Product_mul_temp__0[5]),
        .O(i__carry_i_3__3_n_0));
  LUT6 #(
    .INIT(64'h22222222BBB222B2)) 
    i__carry_i_4
       (.I0(\U3_norm_1_reg[12]_0 [7]),
        .I1(Add_out1[7]),
        .I2(\Delay2_out1_reg[13] [6]),
        .I3(Allow_assymetrical_anew_reference_value__0),
        .I4(\Delay2_out1_reg[13]_0 [6]),
        .I5(Add_out1[6]),
        .O(\Delay2_out1_reg[12] [3]));
  LUT6 #(
    .INIT(64'h22222222BBB222B2)) 
    i__carry_i_4__0
       (.I0(\U2_norm_1_reg[12]_0 [7]),
        .I1(Add_out1[7]),
        .I2(\Delay1_out1_reg[13] [6]),
        .I3(Allow_assymetrical_anew_reference_value__0),
        .I4(\Delay1_out1_reg[13]_0 [6]),
        .I5(Add_out1[6]),
        .O(\Delay1_out1_reg[12] [3]));
  LUT6 #(
    .INIT(64'h22222222BBB222B2)) 
    i__carry_i_4__1
       (.I0(Relational_Operator_1_cast[7]),
        .I1(Add_out1[7]),
        .I2(\Delay_out1_reg[13] [6]),
        .I3(Allow_assymetrical_anew_reference_value__0),
        .I4(\Delay_out1_reg[13]_0 [6]),
        .I5(Add_out1[6]),
        .O(\Delay_out1_reg[12] [3]));
  LUT2 #(
    .INIT(4'h6)) 
    i__carry_i_4__3
       (.I0(Product_mul_temp_n_84),
        .I1(Product_mul_temp__0[4]),
        .O(i__carry_i_4__3_n_0));
  LUT6 #(
    .INIT(64'h22222222BBB222B2)) 
    i__carry_i_5
       (.I0(\U3_norm_1_reg[12]_0 [5]),
        .I1(Add_out1[5]),
        .I2(\Delay2_out1_reg[13] [4]),
        .I3(Allow_assymetrical_anew_reference_value__0),
        .I4(\Delay2_out1_reg[13]_0 [4]),
        .I5(Add_out1[4]),
        .O(\Delay2_out1_reg[12] [2]));
  LUT6 #(
    .INIT(64'h22222222BBB222B2)) 
    i__carry_i_5__0
       (.I0(\U2_norm_1_reg[12]_0 [5]),
        .I1(Add_out1[5]),
        .I2(\Delay1_out1_reg[13] [4]),
        .I3(Allow_assymetrical_anew_reference_value__0),
        .I4(\Delay1_out1_reg[13]_0 [4]),
        .I5(Add_out1[4]),
        .O(\Delay1_out1_reg[12] [2]));
  LUT6 #(
    .INIT(64'h22222222BBB222B2)) 
    i__carry_i_5__1
       (.I0(Relational_Operator_1_cast[5]),
        .I1(Add_out1[5]),
        .I2(\Delay_out1_reg[13] [4]),
        .I3(Allow_assymetrical_anew_reference_value__0),
        .I4(\Delay_out1_reg[13]_0 [4]),
        .I5(Add_out1[4]),
        .O(\Delay_out1_reg[12] [2]));
  LUT2 #(
    .INIT(4'h6)) 
    i__carry_i_5__3
       (.I0(Product_mul_temp_n_85),
        .I1(Product_mul_temp__0[3]),
        .O(i__carry_i_5__3_n_0));
  LUT6 #(
    .INIT(64'h22222222BBB222B2)) 
    i__carry_i_6
       (.I0(\U3_norm_1_reg[12]_0 [3]),
        .I1(Add_out1[3]),
        .I2(\Delay2_out1_reg[13] [2]),
        .I3(Allow_assymetrical_anew_reference_value__0),
        .I4(\Delay2_out1_reg[13]_0 [2]),
        .I5(Add_out1[2]),
        .O(\Delay2_out1_reg[12] [1]));
  LUT6 #(
    .INIT(64'h22222222BBB222B2)) 
    i__carry_i_6__0
       (.I0(\U2_norm_1_reg[12]_0 [3]),
        .I1(Add_out1[3]),
        .I2(\Delay1_out1_reg[13] [2]),
        .I3(Allow_assymetrical_anew_reference_value__0),
        .I4(\Delay1_out1_reg[13]_0 [2]),
        .I5(Add_out1[2]),
        .O(\Delay1_out1_reg[12] [1]));
  LUT6 #(
    .INIT(64'h22222222BBB222B2)) 
    i__carry_i_6__1
       (.I0(Relational_Operator_1_cast[3]),
        .I1(Add_out1[3]),
        .I2(\Delay_out1_reg[13] [2]),
        .I3(Allow_assymetrical_anew_reference_value__0),
        .I4(\Delay_out1_reg[13]_0 [2]),
        .I5(Add_out1[2]),
        .O(\Delay_out1_reg[12] [1]));
  LUT2 #(
    .INIT(4'h6)) 
    i__carry_i_6__3
       (.I0(Product_mul_temp_n_86),
        .I1(Product_mul_temp__0[2]),
        .O(i__carry_i_6__3_n_0));
  LUT6 #(
    .INIT(64'h22222222BBB222B2)) 
    i__carry_i_7
       (.I0(\U3_norm_1_reg[12]_0 [1]),
        .I1(Add_out1[1]),
        .I2(\Delay2_out1_reg[13] [0]),
        .I3(Allow_assymetrical_anew_reference_value__0),
        .I4(\Delay2_out1_reg[13]_0 [0]),
        .I5(Add_out1[0]),
        .O(\Delay2_out1_reg[12] [0]));
  LUT6 #(
    .INIT(64'h22222222BBB222B2)) 
    i__carry_i_7__0
       (.I0(\U2_norm_1_reg[12]_0 [1]),
        .I1(Add_out1[1]),
        .I2(\Delay1_out1_reg[13] [0]),
        .I3(Allow_assymetrical_anew_reference_value__0),
        .I4(\Delay1_out1_reg[13]_0 [0]),
        .I5(Add_out1[0]),
        .O(\Delay1_out1_reg[12] [0]));
  LUT6 #(
    .INIT(64'h22222222BBB222B2)) 
    i__carry_i_7__1
       (.I0(Relational_Operator_1_cast[1]),
        .I1(Add_out1[1]),
        .I2(\Delay_out1_reg[13] [0]),
        .I3(Allow_assymetrical_anew_reference_value__0),
        .I4(\Delay_out1_reg[13]_0 [0]),
        .I5(Add_out1[0]),
        .O(\Delay_out1_reg[12] [0]));
  LUT2 #(
    .INIT(4'h6)) 
    i__carry_i_7__3
       (.I0(Product_mul_temp_n_87),
        .I1(Product_mul_temp__0[1]),
        .O(i__carry_i_7__3_n_0));
  LUT6 #(
    .INIT(64'h9990009000099909)) 
    i__carry_i_8
       (.I0(\U3_norm_1_reg[13] ),
        .I1(Add_out1[13]),
        .I2(\Delay2_out1_reg[13] [12]),
        .I3(Allow_assymetrical_anew_reference_value__0),
        .I4(\Delay2_out1_reg[13]_0 [12]),
        .I5(Add_out1[12]),
        .O(\Delay2_out1_reg[12]_0 [6]));
  LUT6 #(
    .INIT(64'h9990009000099909)) 
    i__carry_i_8__0
       (.I0(\U2_norm_1_reg[13] ),
        .I1(Add_out1[13]),
        .I2(\Delay1_out1_reg[13] [12]),
        .I3(Allow_assymetrical_anew_reference_value__0),
        .I4(\Delay1_out1_reg[13]_0 [12]),
        .I5(Add_out1[12]),
        .O(\Delay1_out1_reg[12]_0 [6]));
  LUT6 #(
    .INIT(64'hA95900000000A959)) 
    i__carry_i_8__1
       (.I0(Add_out1[12]),
        .I1(\Delay_out1_reg[13] [12]),
        .I2(Allow_assymetrical_anew_reference_value__0),
        .I3(\Delay_out1_reg[13]_0 [12]),
        .I4(Relational_Operator_1_cast[13]),
        .I5(Add_out1[13]),
        .O(\Delay_out1_reg[12]_0 [6]));
  LUT2 #(
    .INIT(4'h6)) 
    i__carry_i_8__3
       (.I0(Product_mul_temp_n_88),
        .I1(Product_mul_temp__0[0]),
        .O(i__carry_i_8__3_n_0));
  LUT6 #(
    .INIT(64'h9990009000099909)) 
    i__carry_i_9
       (.I0(\U3_norm_1_reg[12]_0 [11]),
        .I1(Add_out1[11]),
        .I2(\Delay2_out1_reg[13] [10]),
        .I3(Allow_assymetrical_anew_reference_value__0),
        .I4(\Delay2_out1_reg[13]_0 [10]),
        .I5(Add_out1[10]),
        .O(\Delay2_out1_reg[12]_0 [5]));
  LUT6 #(
    .INIT(64'h9990009000099909)) 
    i__carry_i_9__0
       (.I0(\U2_norm_1_reg[12]_0 [11]),
        .I1(Add_out1[11]),
        .I2(\Delay1_out1_reg[13] [10]),
        .I3(Allow_assymetrical_anew_reference_value__0),
        .I4(\Delay1_out1_reg[13]_0 [10]),
        .I5(Add_out1[10]),
        .O(\Delay1_out1_reg[12]_0 [5]));
  LUT6 #(
    .INIT(64'hA95900000000A959)) 
    i__carry_i_9__1
       (.I0(Add_out1[10]),
        .I1(\Delay_out1_reg[13] [10]),
        .I2(Allow_assymetrical_anew_reference_value__0),
        .I3(\Delay_out1_reg[13]_0 [10]),
        .I4(Relational_Operator_1_cast[11]),
        .I5(Add_out1[11]),
        .O(\Delay_out1_reg[12]_0 [5]));
endmodule

module zusys_PWM_and_SS_control_V_0_2_PWM_and_SS_control_V3_ip_src_GenPWM
   (PWM_en_AXI_1_reg_0,
    GenPWM_out1,
    GenPWM_out2,
    GenPWM_out3,
    GenPWM_out4,
    GenPWM_out5,
    GenPWM_out6,
    PWM_en_rd_AXI_sig,
    PWM_enb_out,
    Triangular_Max,
    Triangular_Min,
    \Product_mul_temp[-1111111111] ,
    \Product_mul_temp[-1111111110] ,
    \Product_mul_temp[-1111111109] ,
    \Product_mul_temp[-1111111108] ,
    \Product_mul_temp[-1111111107] ,
    \Product_mul_temp[-1111111106] ,
    \Product_mul_temp[-1111111105] ,
    \Product_mul_temp[-1111111104] ,
    \Product_mul_temp[-1111111103] ,
    \f_carrier_kHz_AXI_2_reg[24]_0 ,
    DI,
    \HDL_Counter2_count_reg[2]_0 ,
    \HDL_Counter2_count_reg[3]_0 ,
    \HDL_Counter2_count_reg[4]_0 ,
    \HDL_Counter2_count_reg[5]_0 ,
    \HDL_Counter2_count_reg[6]_0 ,
    \HDL_Counter2_count_reg[7]_0 ,
    S,
    \HDL_Counter2_count_reg[0]_0 ,
    Q,
    \min_pulse_width_AXI_2_reg[17]_0 ,
    reset,
    E,
    IPCORE_CLK,
    CEB2,
    B,
    D,
    write_PWM_en_AXI,
    CO,
    \T_carrier_us_AXI_1_reg[24]_0 ,
    \min_pulse_width_AXI_1_reg[17]_0 ,
    \U1_norm_1_reg[13]_0 ,
    \U2_norm_1_reg[13]_0 ,
    \U3_norm_1_reg[13]_0 );
  output PWM_en_AXI_1_reg_0;
  output GenPWM_out1;
  output GenPWM_out2;
  output GenPWM_out3;
  output GenPWM_out4;
  output GenPWM_out5;
  output GenPWM_out6;
  output PWM_en_rd_AXI_sig;
  output PWM_enb_out;
  output Triangular_Max;
  output Triangular_Min;
  output \Product_mul_temp[-1111111111] ;
  output \Product_mul_temp[-1111111110] ;
  output \Product_mul_temp[-1111111109] ;
  output \Product_mul_temp[-1111111108] ;
  output \Product_mul_temp[-1111111107] ;
  output \Product_mul_temp[-1111111106] ;
  output \Product_mul_temp[-1111111105] ;
  output \Product_mul_temp[-1111111104] ;
  output \Product_mul_temp[-1111111103] ;
  output [15:0]\f_carrier_kHz_AXI_2_reg[24]_0 ;
  output [1:0]DI;
  output \HDL_Counter2_count_reg[2]_0 ;
  output \HDL_Counter2_count_reg[3]_0 ;
  output \HDL_Counter2_count_reg[4]_0 ;
  output \HDL_Counter2_count_reg[5]_0 ;
  output \HDL_Counter2_count_reg[6]_0 ;
  output \HDL_Counter2_count_reg[7]_0 ;
  output [7:0]S;
  output [0:0]\HDL_Counter2_count_reg[0]_0 ;
  output [24:0]Q;
  output [17:0]\min_pulse_width_AXI_2_reg[17]_0 ;
  input reset;
  input [0:0]E;
  input IPCORE_CLK;
  input CEB2;
  input [7:0]B;
  input [24:0]D;
  input write_PWM_en_AXI;
  input [0:0]CO;
  input [24:0]\T_carrier_us_AXI_1_reg[24]_0 ;
  input [17:0]\min_pulse_width_AXI_1_reg[17]_0 ;
  input [13:0]\U1_norm_1_reg[13]_0 ;
  input [13:0]\U2_norm_1_reg[13]_0 ;
  input [13:0]\U3_norm_1_reg[13]_0 ;

  wire [17:4]Add_out1;
  wire Allow_assymetrical_anew_reference_value__0;
  wire [7:0]B;
  wire CEB2;
  wire [0:0]CO;
  wire Counter_Ctrl_out3;
  wire Counter_Ctrl_out4;
  wire [24:0]D;
  wire [1:0]DI;
  wire [13:0]Delay1_out1;
  wire [13:0]Delay2_out1;
  wire [13:0]Delay_out1;
  wire Demux1_out2_i_1_n_0;
  wire Demux2_out2_i_1_n_0;
  wire Demux_out2_i_1_n_0;
  wire [0:0]E;
  wire GenPWM_out1;
  wire GenPWM_out2;
  wire GenPWM_out3;
  wire GenPWM_out4;
  wire GenPWM_out5;
  wire GenPWM_out6;
  wire [16:9]HDL_Counter2_count_next;
  wire HDL_Counter2_count_next_carry__0_n_1;
  wire HDL_Counter2_count_next_carry__0_n_2;
  wire HDL_Counter2_count_next_carry__0_n_3;
  wire HDL_Counter2_count_next_carry__0_n_4;
  wire HDL_Counter2_count_next_carry__0_n_5;
  wire HDL_Counter2_count_next_carry__0_n_6;
  wire HDL_Counter2_count_next_carry__0_n_7;
  wire [19:1]HDL_Counter2_count_reg;
  wire [0:0]\HDL_Counter2_count_reg[0]_0 ;
  wire \HDL_Counter2_count_reg[2]_0 ;
  wire \HDL_Counter2_count_reg[3]_0 ;
  wire \HDL_Counter2_count_reg[4]_0 ;
  wire \HDL_Counter2_count_reg[5]_0 ;
  wire \HDL_Counter2_count_reg[6]_0 ;
  wire \HDL_Counter2_count_reg[7]_0 ;
  wire IPCORE_CLK;
  wire PWM_en_AXI_1_reg_0;
  wire PWM_en_rd_AXI_sig;
  wire PWM_enb_out;
  wire \Product_mul_temp[-1111111103] ;
  wire \Product_mul_temp[-1111111104] ;
  wire \Product_mul_temp[-1111111105] ;
  wire \Product_mul_temp[-1111111106] ;
  wire \Product_mul_temp[-1111111107] ;
  wire \Product_mul_temp[-1111111108] ;
  wire \Product_mul_temp[-1111111109] ;
  wire \Product_mul_temp[-1111111110] ;
  wire \Product_mul_temp[-1111111111] ;
  wire [24:0]Q;
  wire Relational_Operator1_relop1;
  wire Relational_Operator1_relop1_1;
  wire Relational_Operator1_relop1_3;
  wire Relational_Operator1_relop1_5;
  wire Relational_Operator2_relop1;
  wire [17:4]Relational_Operator_1_cast;
  wire Relational_Operator_relop1;
  wire Relational_Operator_relop1_0;
  wire Relational_Operator_relop1_2;
  wire Relational_Operator_relop1_4;
  wire [7:0]S;
  wire [16:4]Saturation_out1;
  wire Switch3_out1_0;
  wire Switch4_out1_0;
  wire Switch5_out1_0;
  wire Switch6_out1;
  wire Switch7_out12_carry__0_n_7;
  wire Switch7_out12_carry_n_0;
  wire Switch7_out12_carry_n_1;
  wire Switch7_out12_carry_n_2;
  wire Switch7_out12_carry_n_3;
  wire Switch7_out12_carry_n_4;
  wire Switch7_out12_carry_n_5;
  wire Switch7_out12_carry_n_6;
  wire Switch7_out12_carry_n_7;
  wire Switch8_out12_carry__0_n_7;
  wire Switch8_out12_carry_n_0;
  wire Switch8_out12_carry_n_1;
  wire Switch8_out12_carry_n_2;
  wire Switch8_out12_carry_n_3;
  wire Switch8_out12_carry_n_4;
  wire Switch8_out12_carry_n_5;
  wire Switch8_out12_carry_n_6;
  wire Switch8_out12_carry_n_7;
  wire Switch9_out12_carry__0_n_7;
  wire Switch9_out12_carry_n_0;
  wire Switch9_out12_carry_n_1;
  wire Switch9_out12_carry_n_2;
  wire Switch9_out12_carry_n_3;
  wire Switch9_out12_carry_n_4;
  wire Switch9_out12_carry_n_5;
  wire Switch9_out12_carry_n_6;
  wire Switch9_out12_carry_n_7;
  wire [24:0]T_carrier_us;
  wire [24:0]\T_carrier_us_AXI_1_reg[24]_0 ;
  wire Triangular_Max;
  wire Triangular_Min;
  wire [13:0]U1_norm_1;
  wire [13:0]\U1_norm_1_reg[13]_0 ;
  wire [13:0]U2_norm_1;
  wire [13:0]\U2_norm_1_reg[13]_0 ;
  wire [13:0]U3_norm_1;
  wire [13:0]\U3_norm_1_reg[13]_0 ;
  wire [24:0]f_carrier_kHz;
  wire [15:0]\f_carrier_kHz_AXI_2_reg[24]_0 ;
  wire i__carry__0_i_1_n_0;
  wire [17:0]min_pulse_width;
  wire [17:0]\min_pulse_width_AXI_1_reg[17]_0 ;
  wire [17:0]\min_pulse_width_AXI_2_reg[17]_0 ;
  wire reset;
  wire u_Counter_Ctrl_n_0;
  wire u_Counter_Ctrl_n_1;
  wire u_Counter_Ctrl_n_100;
  wire u_Counter_Ctrl_n_101;
  wire u_Counter_Ctrl_n_102;
  wire u_Counter_Ctrl_n_103;
  wire u_Counter_Ctrl_n_104;
  wire u_Counter_Ctrl_n_105;
  wire u_Counter_Ctrl_n_106;
  wire u_Counter_Ctrl_n_107;
  wire u_Counter_Ctrl_n_108;
  wire u_Counter_Ctrl_n_109;
  wire u_Counter_Ctrl_n_110;
  wire u_Counter_Ctrl_n_111;
  wire u_Counter_Ctrl_n_112;
  wire u_Counter_Ctrl_n_113;
  wire u_Counter_Ctrl_n_114;
  wire u_Counter_Ctrl_n_115;
  wire u_Counter_Ctrl_n_116;
  wire u_Counter_Ctrl_n_117;
  wire u_Counter_Ctrl_n_118;
  wire u_Counter_Ctrl_n_119;
  wire u_Counter_Ctrl_n_120;
  wire u_Counter_Ctrl_n_121;
  wire u_Counter_Ctrl_n_122;
  wire u_Counter_Ctrl_n_123;
  wire u_Counter_Ctrl_n_124;
  wire u_Counter_Ctrl_n_125;
  wire u_Counter_Ctrl_n_126;
  wire u_Counter_Ctrl_n_127;
  wire u_Counter_Ctrl_n_128;
  wire u_Counter_Ctrl_n_129;
  wire u_Counter_Ctrl_n_130;
  wire u_Counter_Ctrl_n_131;
  wire u_Counter_Ctrl_n_132;
  wire u_Counter_Ctrl_n_133;
  wire u_Counter_Ctrl_n_134;
  wire u_Counter_Ctrl_n_135;
  wire u_Counter_Ctrl_n_136;
  wire u_Counter_Ctrl_n_137;
  wire u_Counter_Ctrl_n_138;
  wire u_Counter_Ctrl_n_139;
  wire u_Counter_Ctrl_n_140;
  wire u_Counter_Ctrl_n_141;
  wire u_Counter_Ctrl_n_142;
  wire u_Counter_Ctrl_n_143;
  wire u_Counter_Ctrl_n_144;
  wire u_Counter_Ctrl_n_145;
  wire u_Counter_Ctrl_n_146;
  wire u_Counter_Ctrl_n_147;
  wire u_Counter_Ctrl_n_148;
  wire u_Counter_Ctrl_n_149;
  wire u_Counter_Ctrl_n_150;
  wire u_Counter_Ctrl_n_151;
  wire u_Counter_Ctrl_n_152;
  wire u_Counter_Ctrl_n_153;
  wire u_Counter_Ctrl_n_154;
  wire u_Counter_Ctrl_n_155;
  wire u_Counter_Ctrl_n_156;
  wire u_Counter_Ctrl_n_157;
  wire u_Counter_Ctrl_n_158;
  wire u_Counter_Ctrl_n_159;
  wire u_Counter_Ctrl_n_160;
  wire u_Counter_Ctrl_n_161;
  wire u_Counter_Ctrl_n_162;
  wire u_Counter_Ctrl_n_163;
  wire u_Counter_Ctrl_n_164;
  wire u_Counter_Ctrl_n_17;
  wire u_Counter_Ctrl_n_179;
  wire u_Counter_Ctrl_n_18;
  wire u_Counter_Ctrl_n_180;
  wire u_Counter_Ctrl_n_181;
  wire u_Counter_Ctrl_n_182;
  wire u_Counter_Ctrl_n_183;
  wire u_Counter_Ctrl_n_184;
  wire u_Counter_Ctrl_n_185;
  wire u_Counter_Ctrl_n_186;
  wire u_Counter_Ctrl_n_187;
  wire u_Counter_Ctrl_n_188;
  wire u_Counter_Ctrl_n_189;
  wire u_Counter_Ctrl_n_19;
  wire u_Counter_Ctrl_n_190;
  wire u_Counter_Ctrl_n_191;
  wire u_Counter_Ctrl_n_192;
  wire u_Counter_Ctrl_n_193;
  wire u_Counter_Ctrl_n_194;
  wire u_Counter_Ctrl_n_195;
  wire u_Counter_Ctrl_n_196;
  wire u_Counter_Ctrl_n_197;
  wire u_Counter_Ctrl_n_198;
  wire u_Counter_Ctrl_n_199;
  wire u_Counter_Ctrl_n_2;
  wire u_Counter_Ctrl_n_20;
  wire u_Counter_Ctrl_n_201;
  wire u_Counter_Ctrl_n_202;
  wire u_Counter_Ctrl_n_203;
  wire u_Counter_Ctrl_n_204;
  wire u_Counter_Ctrl_n_21;
  wire u_Counter_Ctrl_n_22;
  wire u_Counter_Ctrl_n_23;
  wire u_Counter_Ctrl_n_24;
  wire u_Counter_Ctrl_n_26;
  wire u_Counter_Ctrl_n_27;
  wire u_Counter_Ctrl_n_28;
  wire u_Counter_Ctrl_n_29;
  wire u_Counter_Ctrl_n_3;
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
  wire u_Counter_Ctrl_n_4;
  wire u_Counter_Ctrl_n_40;
  wire u_Counter_Ctrl_n_41;
  wire u_Counter_Ctrl_n_42;
  wire u_Counter_Ctrl_n_43;
  wire u_Counter_Ctrl_n_44;
  wire u_Counter_Ctrl_n_45;
  wire u_Counter_Ctrl_n_49;
  wire u_Counter_Ctrl_n_5;
  wire u_Counter_Ctrl_n_50;
  wire u_Counter_Ctrl_n_51;
  wire u_Counter_Ctrl_n_52;
  wire u_Counter_Ctrl_n_53;
  wire u_Counter_Ctrl_n_54;
  wire u_Counter_Ctrl_n_55;
  wire u_Counter_Ctrl_n_56;
  wire u_Counter_Ctrl_n_58;
  wire u_Counter_Ctrl_n_59;
  wire u_Counter_Ctrl_n_60;
  wire u_Counter_Ctrl_n_61;
  wire u_Counter_Ctrl_n_62;
  wire u_Counter_Ctrl_n_63;
  wire u_Counter_Ctrl_n_64;
  wire u_Counter_Ctrl_n_65;
  wire u_Counter_Ctrl_n_66;
  wire u_Counter_Ctrl_n_67;
  wire u_Counter_Ctrl_n_68;
  wire u_Counter_Ctrl_n_69;
  wire u_Counter_Ctrl_n_70;
  wire u_Counter_Ctrl_n_71;
  wire u_Counter_Ctrl_n_72;
  wire u_Counter_Ctrl_n_73;
  wire u_Counter_Ctrl_n_74;
  wire u_Counter_Ctrl_n_75;
  wire u_Counter_Ctrl_n_76;
  wire u_Counter_Ctrl_n_77;
  wire u_Counter_Ctrl_n_78;
  wire u_Counter_Ctrl_n_79;
  wire u_Counter_Ctrl_n_80;
  wire u_Counter_Ctrl_n_81;
  wire u_Counter_Ctrl_n_82;
  wire u_Counter_Ctrl_n_83;
  wire u_Counter_Ctrl_n_84;
  wire u_Counter_Ctrl_n_85;
  wire u_Counter_Ctrl_n_86;
  wire u_Counter_Ctrl_n_87;
  wire u_Counter_Ctrl_n_88;
  wire u_Counter_Ctrl_n_89;
  wire u_Counter_Ctrl_n_90;
  wire u_Counter_Ctrl_n_91;
  wire u_Counter_Ctrl_n_92;
  wire u_Counter_Ctrl_n_93;
  wire u_Counter_Ctrl_n_94;
  wire u_Counter_Ctrl_n_95;
  wire u_Counter_Ctrl_n_96;
  wire u_Counter_Ctrl_n_97;
  wire u_Counter_Ctrl_n_98;
  wire u_Counter_Ctrl_n_99;
  wire u_LimitPulseWidth_n_1;
  wire u_LimitPulseWidth_n_17;
  wire u_LimitPulseWidth_n_18;
  wire u_LimitPulseWidth_n_19;
  wire u_LimitPulseWidth_n_20;
  wire u_LimitPulseWidth_n_21;
  wire u_LimitPulseWidth_n_22;
  wire u_LimitPulseWidth_n_23;
  wire u_LimitPulseWidth_n_24;
  wire u_LimitPulseWidth_n_38;
  wire u_LimitPulseWidth_n_39;
  wire u_LimitPulseWidth_n_40;
  wire u_LimitPulseWidth_n_41;
  wire u_LimitPulseWidth_n_42;
  wire u_LimitPulseWidth_n_43;
  wire u_LimitPulseWidth_n_44;
  wire u_LimitPulseWidth_n_45;
  wire u_LimitPulseWidth_n_46;
  wire u_LimitPulseWidth_n_47;
  wire u_LimitPulseWidth_n_48;
  wire u_LimitPulseWidth_n_49;
  wire u_LimitPulseWidth_n_50;
  wire u_LimitPulseWidth_n_51;
  wire u_LimitPulseWidth_n_52;
  wire u_LimitPulseWidth_n_53;
  wire u_LimitPulseWidth_n_54;
  wire u_LimitPulseWidth_n_55;
  wire u_LimitPulseWidth_n_56;
  wire u_LimitPulseWidth_n_57;
  wire u_LimitPulseWidth_n_58;
  wire write_PWM_en_AXI;
  wire [7:7]NLW_HDL_Counter2_count_next_carry__0_CO_UNCONNECTED;
  wire [7:0]NLW_Switch7_out12_carry_O_UNCONNECTED;
  wire [7:2]NLW_Switch7_out12_carry__0_CO_UNCONNECTED;
  wire [7:0]NLW_Switch7_out12_carry__0_O_UNCONNECTED;
  wire [7:0]NLW_Switch8_out12_carry_O_UNCONNECTED;
  wire [7:2]NLW_Switch8_out12_carry__0_CO_UNCONNECTED;
  wire [7:0]NLW_Switch8_out12_carry__0_O_UNCONNECTED;
  wire [7:0]NLW_Switch9_out12_carry_O_UNCONNECTED;
  wire [7:2]NLW_Switch9_out12_carry__0_CO_UNCONNECTED;
  wire [7:0]NLW_Switch9_out12_carry__0_O_UNCONNECTED;

  FDRE Counter_Ctrl_out3_1_reg
       (.C(IPCORE_CLK),
        .CE(E),
        .D(Counter_Ctrl_out3),
        .Q(Triangular_Max),
        .R(reset));
  LUT4 #(
    .INIT(16'h0080)) 
    Counter_Ctrl_out4_1_i_1
       (.I0(u_LimitPulseWidth_n_52),
        .I1(u_LimitPulseWidth_n_53),
        .I2(u_LimitPulseWidth_n_51),
        .I3(HDL_Counter2_count_reg[19]),
        .O(Counter_Ctrl_out4));
  FDRE Counter_Ctrl_out4_1_reg
       (.C(IPCORE_CLK),
        .CE(E),
        .D(Counter_Ctrl_out4),
        .Q(Triangular_Min),
        .R(reset));
  FDRE \Delay1_out1_reg[0] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(u_Counter_Ctrl_n_134),
        .Q(Delay1_out1[0]),
        .R(reset));
  FDRE \Delay1_out1_reg[10] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(u_Counter_Ctrl_n_124),
        .Q(Delay1_out1[10]),
        .R(reset));
  FDRE \Delay1_out1_reg[11] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(u_Counter_Ctrl_n_123),
        .Q(Delay1_out1[11]),
        .R(reset));
  FDRE \Delay1_out1_reg[12] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(u_Counter_Ctrl_n_122),
        .Q(Delay1_out1[12]),
        .R(reset));
  FDRE \Delay1_out1_reg[13] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(u_Counter_Ctrl_n_111),
        .Q(Delay1_out1[13]),
        .R(reset));
  FDRE \Delay1_out1_reg[1] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(u_Counter_Ctrl_n_133),
        .Q(Delay1_out1[1]),
        .R(reset));
  FDRE \Delay1_out1_reg[2] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(u_Counter_Ctrl_n_132),
        .Q(Delay1_out1[2]),
        .R(reset));
  FDRE \Delay1_out1_reg[3] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(u_Counter_Ctrl_n_131),
        .Q(Delay1_out1[3]),
        .R(reset));
  FDRE \Delay1_out1_reg[4] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(u_Counter_Ctrl_n_130),
        .Q(Delay1_out1[4]),
        .R(reset));
  FDRE \Delay1_out1_reg[5] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(u_Counter_Ctrl_n_129),
        .Q(Delay1_out1[5]),
        .R(reset));
  FDRE \Delay1_out1_reg[6] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(u_Counter_Ctrl_n_128),
        .Q(Delay1_out1[6]),
        .R(reset));
  FDRE \Delay1_out1_reg[7] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(u_Counter_Ctrl_n_127),
        .Q(Delay1_out1[7]),
        .R(reset));
  FDRE \Delay1_out1_reg[8] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(u_Counter_Ctrl_n_126),
        .Q(Delay1_out1[8]),
        .R(reset));
  FDRE \Delay1_out1_reg[9] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(u_Counter_Ctrl_n_125),
        .Q(Delay1_out1[9]),
        .R(reset));
  FDRE \Delay2_out1_reg[0] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(u_Counter_Ctrl_n_80),
        .Q(Delay2_out1[0]),
        .R(reset));
  FDRE \Delay2_out1_reg[10] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(u_Counter_Ctrl_n_70),
        .Q(Delay2_out1[10]),
        .R(reset));
  FDRE \Delay2_out1_reg[11] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(u_Counter_Ctrl_n_69),
        .Q(Delay2_out1[11]),
        .R(reset));
  FDRE \Delay2_out1_reg[12] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(u_Counter_Ctrl_n_68),
        .Q(Delay2_out1[12]),
        .R(reset));
  FDRE \Delay2_out1_reg[13] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(u_Counter_Ctrl_n_56),
        .Q(Delay2_out1[13]),
        .R(reset));
  FDRE \Delay2_out1_reg[1] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(u_Counter_Ctrl_n_79),
        .Q(Delay2_out1[1]),
        .R(reset));
  FDRE \Delay2_out1_reg[2] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(u_Counter_Ctrl_n_78),
        .Q(Delay2_out1[2]),
        .R(reset));
  FDRE \Delay2_out1_reg[3] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(u_Counter_Ctrl_n_77),
        .Q(Delay2_out1[3]),
        .R(reset));
  FDRE \Delay2_out1_reg[4] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(u_Counter_Ctrl_n_76),
        .Q(Delay2_out1[4]),
        .R(reset));
  FDRE \Delay2_out1_reg[5] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(u_Counter_Ctrl_n_75),
        .Q(Delay2_out1[5]),
        .R(reset));
  FDRE \Delay2_out1_reg[6] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(u_Counter_Ctrl_n_74),
        .Q(Delay2_out1[6]),
        .R(reset));
  FDRE \Delay2_out1_reg[7] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(u_Counter_Ctrl_n_73),
        .Q(Delay2_out1[7]),
        .R(reset));
  FDRE \Delay2_out1_reg[8] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(u_Counter_Ctrl_n_72),
        .Q(Delay2_out1[8]),
        .R(reset));
  FDRE \Delay2_out1_reg[9] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(u_Counter_Ctrl_n_71),
        .Q(Delay2_out1[9]),
        .R(reset));
  FDRE \Delay_out1_reg[0] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(Relational_Operator_1_cast[4]),
        .Q(Delay_out1[0]),
        .R(reset));
  FDRE \Delay_out1_reg[10] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(Relational_Operator_1_cast[14]),
        .Q(Delay_out1[10]),
        .R(reset));
  FDRE \Delay_out1_reg[11] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(Relational_Operator_1_cast[15]),
        .Q(Delay_out1[11]),
        .R(reset));
  FDRE \Delay_out1_reg[12] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(Relational_Operator_1_cast[16]),
        .Q(Delay_out1[12]),
        .R(reset));
  FDRE \Delay_out1_reg[13] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(Relational_Operator_1_cast[17]),
        .Q(Delay_out1[13]),
        .R(reset));
  FDRE \Delay_out1_reg[1] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(Relational_Operator_1_cast[5]),
        .Q(Delay_out1[1]),
        .R(reset));
  FDRE \Delay_out1_reg[2] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(Relational_Operator_1_cast[6]),
        .Q(Delay_out1[2]),
        .R(reset));
  FDRE \Delay_out1_reg[3] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(Relational_Operator_1_cast[7]),
        .Q(Delay_out1[3]),
        .R(reset));
  FDRE \Delay_out1_reg[4] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(Relational_Operator_1_cast[8]),
        .Q(Delay_out1[4]),
        .R(reset));
  FDRE \Delay_out1_reg[5] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(Relational_Operator_1_cast[9]),
        .Q(Delay_out1[5]),
        .R(reset));
  FDRE \Delay_out1_reg[6] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(Relational_Operator_1_cast[10]),
        .Q(Delay_out1[6]),
        .R(reset));
  FDRE \Delay_out1_reg[7] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(Relational_Operator_1_cast[11]),
        .Q(Delay_out1[7]),
        .R(reset));
  FDRE \Delay_out1_reg[8] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(Relational_Operator_1_cast[12]),
        .Q(Delay_out1[8]),
        .R(reset));
  FDRE \Delay_out1_reg[9] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(Relational_Operator_1_cast[13]),
        .Q(Delay_out1[9]),
        .R(reset));
  (* SOFT_HLUTNM = "soft_lutpair24" *) 
  LUT2 #(
    .INIT(4'h2)) 
    Demux1_out1_i_1
       (.I0(PWM_en_AXI_1_reg_0),
        .I1(Relational_Operator1_relop1),
        .O(Switch4_out1_0));
  FDRE Demux1_out1_reg
       (.C(IPCORE_CLK),
        .CE(E),
        .D(Switch4_out1_0),
        .Q(GenPWM_out3),
        .R(reset));
  (* SOFT_HLUTNM = "soft_lutpair24" *) 
  LUT2 #(
    .INIT(4'h8)) 
    Demux1_out2_i_1
       (.I0(PWM_en_AXI_1_reg_0),
        .I1(Relational_Operator1_relop1),
        .O(Demux1_out2_i_1_n_0));
  FDRE Demux1_out2_reg
       (.C(IPCORE_CLK),
        .CE(E),
        .D(Demux1_out2_i_1_n_0),
        .Q(GenPWM_out4),
        .R(reset));
  (* SOFT_HLUTNM = "soft_lutpair25" *) 
  LUT2 #(
    .INIT(4'h2)) 
    Demux2_out1_i_1
       (.I0(PWM_en_AXI_1_reg_0),
        .I1(Relational_Operator2_relop1),
        .O(Switch5_out1_0));
  FDRE Demux2_out1_reg
       (.C(IPCORE_CLK),
        .CE(E),
        .D(Switch5_out1_0),
        .Q(GenPWM_out5),
        .R(reset));
  (* SOFT_HLUTNM = "soft_lutpair25" *) 
  LUT2 #(
    .INIT(4'h8)) 
    Demux2_out2_i_1
       (.I0(PWM_en_AXI_1_reg_0),
        .I1(Relational_Operator2_relop1),
        .O(Demux2_out2_i_1_n_0));
  FDRE Demux2_out2_reg
       (.C(IPCORE_CLK),
        .CE(E),
        .D(Demux2_out2_i_1_n_0),
        .Q(GenPWM_out6),
        .R(reset));
  (* SOFT_HLUTNM = "soft_lutpair23" *) 
  LUT2 #(
    .INIT(4'h2)) 
    Demux_out1_i_1
       (.I0(PWM_en_AXI_1_reg_0),
        .I1(Relational_Operator_relop1),
        .O(Switch3_out1_0));
  FDRE Demux_out1_reg
       (.C(IPCORE_CLK),
        .CE(E),
        .D(Switch3_out1_0),
        .Q(GenPWM_out1),
        .R(reset));
  (* SOFT_HLUTNM = "soft_lutpair23" *) 
  LUT2 #(
    .INIT(4'h8)) 
    Demux_out2_i_1
       (.I0(PWM_en_AXI_1_reg_0),
        .I1(Relational_Operator_relop1),
        .O(Demux_out2_i_1_n_0));
  FDRE Demux_out2_reg
       (.C(IPCORE_CLK),
        .CE(E),
        .D(Demux_out2_i_1_n_0),
        .Q(GenPWM_out2),
        .R(reset));
  CARRY8 HDL_Counter2_count_next_carry__0
       (.CI(CO),
        .CI_TOP(1'b0),
        .CO({NLW_HDL_Counter2_count_next_carry__0_CO_UNCONNECTED[7],HDL_Counter2_count_next_carry__0_n_1,HDL_Counter2_count_next_carry__0_n_2,HDL_Counter2_count_next_carry__0_n_3,HDL_Counter2_count_next_carry__0_n_4,HDL_Counter2_count_next_carry__0_n_5,HDL_Counter2_count_next_carry__0_n_6,HDL_Counter2_count_next_carry__0_n_7}),
        .DI({1'b0,HDL_Counter2_count_reg[14:8]}),
        .O(HDL_Counter2_count_next),
        .S({u_Counter_Ctrl_n_38,u_Counter_Ctrl_n_39,u_Counter_Ctrl_n_40,u_Counter_Ctrl_n_41,u_Counter_Ctrl_n_42,u_Counter_Ctrl_n_43,u_Counter_Ctrl_n_44,u_Counter_Ctrl_n_45}));
  LUT2 #(
    .INIT(4'h9)) 
    HDL_Counter2_count_next_carry_i_3
       (.I0(\HDL_Counter2_count_reg[7]_0 ),
        .I1(HDL_Counter2_count_reg[8]),
        .O(S[7]));
  LUT2 #(
    .INIT(4'h9)) 
    HDL_Counter2_count_next_carry_i_4
       (.I0(\HDL_Counter2_count_reg[6]_0 ),
        .I1(\HDL_Counter2_count_reg[7]_0 ),
        .O(S[6]));
  LUT2 #(
    .INIT(4'h9)) 
    HDL_Counter2_count_next_carry_i_5
       (.I0(\HDL_Counter2_count_reg[5]_0 ),
        .I1(\HDL_Counter2_count_reg[6]_0 ),
        .O(S[5]));
  LUT2 #(
    .INIT(4'h9)) 
    HDL_Counter2_count_next_carry_i_6
       (.I0(\HDL_Counter2_count_reg[4]_0 ),
        .I1(\HDL_Counter2_count_reg[5]_0 ),
        .O(S[4]));
  LUT2 #(
    .INIT(4'h9)) 
    HDL_Counter2_count_next_carry_i_7
       (.I0(\HDL_Counter2_count_reg[3]_0 ),
        .I1(\HDL_Counter2_count_reg[4]_0 ),
        .O(S[3]));
  LUT2 #(
    .INIT(4'h9)) 
    HDL_Counter2_count_next_carry_i_8
       (.I0(\HDL_Counter2_count_reg[2]_0 ),
        .I1(\HDL_Counter2_count_reg[3]_0 ),
        .O(S[2]));
  FDRE \HDL_Counter2_count_reg[0] 
       (.C(IPCORE_CLK),
        .CE(CEB2),
        .D(u_Counter_Ctrl_n_24),
        .Q(DI[0]),
        .R(reset));
  FDRE \HDL_Counter2_count_reg[10] 
       (.C(IPCORE_CLK),
        .CE(CEB2),
        .D(u_Counter_Ctrl_n_31),
        .Q(HDL_Counter2_count_reg[10]),
        .R(reset));
  FDRE \HDL_Counter2_count_reg[11] 
       (.C(IPCORE_CLK),
        .CE(CEB2),
        .D(u_Counter_Ctrl_n_30),
        .Q(HDL_Counter2_count_reg[11]),
        .R(reset));
  FDRE \HDL_Counter2_count_reg[12] 
       (.C(IPCORE_CLK),
        .CE(CEB2),
        .D(u_Counter_Ctrl_n_29),
        .Q(HDL_Counter2_count_reg[12]),
        .R(reset));
  FDRE \HDL_Counter2_count_reg[13] 
       (.C(IPCORE_CLK),
        .CE(CEB2),
        .D(u_Counter_Ctrl_n_28),
        .Q(HDL_Counter2_count_reg[13]),
        .R(reset));
  FDRE \HDL_Counter2_count_reg[14] 
       (.C(IPCORE_CLK),
        .CE(CEB2),
        .D(u_Counter_Ctrl_n_27),
        .Q(HDL_Counter2_count_reg[14]),
        .R(reset));
  FDRE \HDL_Counter2_count_reg[15] 
       (.C(IPCORE_CLK),
        .CE(CEB2),
        .D(u_Counter_Ctrl_n_26),
        .Q(HDL_Counter2_count_reg[15]),
        .R(reset));
  FDRE \HDL_Counter2_count_reg[16] 
       (.C(IPCORE_CLK),
        .CE(CEB2),
        .D(u_Counter_Ctrl_n_37),
        .Q(HDL_Counter2_count_reg[16]),
        .R(reset));
  FDRE \HDL_Counter2_count_reg[17] 
       (.C(IPCORE_CLK),
        .CE(CEB2),
        .D(u_Counter_Ctrl_n_36),
        .Q(HDL_Counter2_count_reg[17]),
        .R(reset));
  FDRE \HDL_Counter2_count_reg[18] 
       (.C(IPCORE_CLK),
        .CE(CEB2),
        .D(u_Counter_Ctrl_n_35),
        .Q(HDL_Counter2_count_reg[18]),
        .R(reset));
  FDRE \HDL_Counter2_count_reg[19] 
       (.C(IPCORE_CLK),
        .CE(CEB2),
        .D(u_Counter_Ctrl_n_34),
        .Q(HDL_Counter2_count_reg[19]),
        .R(reset));
  FDRE \HDL_Counter2_count_reg[1] 
       (.C(IPCORE_CLK),
        .CE(CEB2),
        .D(u_Counter_Ctrl_n_23),
        .Q(HDL_Counter2_count_reg[1]),
        .R(reset));
  FDRE \HDL_Counter2_count_reg[2] 
       (.C(IPCORE_CLK),
        .CE(CEB2),
        .D(u_Counter_Ctrl_n_22),
        .Q(\HDL_Counter2_count_reg[2]_0 ),
        .R(reset));
  FDRE \HDL_Counter2_count_reg[3] 
       (.C(IPCORE_CLK),
        .CE(CEB2),
        .D(u_Counter_Ctrl_n_21),
        .Q(\HDL_Counter2_count_reg[3]_0 ),
        .R(reset));
  FDRE \HDL_Counter2_count_reg[4] 
       (.C(IPCORE_CLK),
        .CE(CEB2),
        .D(u_Counter_Ctrl_n_20),
        .Q(\HDL_Counter2_count_reg[4]_0 ),
        .R(reset));
  FDRE \HDL_Counter2_count_reg[5] 
       (.C(IPCORE_CLK),
        .CE(CEB2),
        .D(u_Counter_Ctrl_n_19),
        .Q(\HDL_Counter2_count_reg[5]_0 ),
        .R(reset));
  FDRE \HDL_Counter2_count_reg[6] 
       (.C(IPCORE_CLK),
        .CE(CEB2),
        .D(u_Counter_Ctrl_n_18),
        .Q(\HDL_Counter2_count_reg[6]_0 ),
        .R(reset));
  FDRE \HDL_Counter2_count_reg[7] 
       (.C(IPCORE_CLK),
        .CE(CEB2),
        .D(u_Counter_Ctrl_n_17),
        .Q(\HDL_Counter2_count_reg[7]_0 ),
        .R(reset));
  FDRE \HDL_Counter2_count_reg[8] 
       (.C(IPCORE_CLK),
        .CE(CEB2),
        .D(u_Counter_Ctrl_n_33),
        .Q(HDL_Counter2_count_reg[8]),
        .R(reset));
  FDRE \HDL_Counter2_count_reg[9] 
       (.C(IPCORE_CLK),
        .CE(CEB2),
        .D(u_Counter_Ctrl_n_32),
        .Q(HDL_Counter2_count_reg[9]),
        .R(reset));
  FDRE PWM_en_AXI_1_reg
       (.C(IPCORE_CLK),
        .CE(E),
        .D(write_PWM_en_AXI),
        .Q(PWM_en_AXI_1_reg_0),
        .R(reset));
  FDRE PWM_en_AXI_2_reg
       (.C(IPCORE_CLK),
        .CE(E),
        .D(PWM_en_AXI_1_reg_0),
        .Q(PWM_en_rd_AXI_sig),
        .R(reset));
  FDRE Switch6_out1_1_reg
       (.C(IPCORE_CLK),
        .CE(E),
        .D(Switch6_out1),
        .Q(PWM_enb_out),
        .R(reset));
  (* COMPARATOR_THRESHOLD = "11" *) 
  CARRY8 Switch7_out12_carry
       (.CI(1'b1),
        .CI_TOP(1'b0),
        .CO({Switch7_out12_carry_n_0,Switch7_out12_carry_n_1,Switch7_out12_carry_n_2,Switch7_out12_carry_n_3,Switch7_out12_carry_n_4,Switch7_out12_carry_n_5,Switch7_out12_carry_n_6,Switch7_out12_carry_n_7}),
        .DI({u_Counter_Ctrl_n_194,u_Counter_Ctrl_n_195,u_Counter_Ctrl_n_196,u_Counter_Ctrl_n_197,u_Counter_Ctrl_n_198,u_LimitPulseWidth_n_48,u_Counter_Ctrl_n_199,u_LimitPulseWidth_n_49}),
        .O(NLW_Switch7_out12_carry_O_UNCONNECTED[7:0]),
        .S({u_Counter_Ctrl_n_188,u_Counter_Ctrl_n_189,u_Counter_Ctrl_n_190,u_Counter_Ctrl_n_191,u_Counter_Ctrl_n_192,u_Counter_Ctrl_n_193,u_LimitPulseWidth_n_54,u_LimitPulseWidth_n_55}));
  (* COMPARATOR_THRESHOLD = "11" *) 
  CARRY8 Switch7_out12_carry__0
       (.CI(Switch7_out12_carry_n_0),
        .CI_TOP(1'b0),
        .CO({NLW_Switch7_out12_carry__0_CO_UNCONNECTED[7:2],Relational_Operator_relop1,Switch7_out12_carry__0_n_7}),
        .DI({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,u_LimitPulseWidth_n_46,u_Counter_Ctrl_n_187}),
        .O(NLW_Switch7_out12_carry__0_O_UNCONNECTED[7:0]),
        .S({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,u_LimitPulseWidth_n_47,u_Counter_Ctrl_n_186}));
  (* COMPARATOR_THRESHOLD = "11" *) 
  CARRY8 Switch8_out12_carry
       (.CI(1'b1),
        .CI_TOP(1'b0),
        .CO({Switch8_out12_carry_n_0,Switch8_out12_carry_n_1,Switch8_out12_carry_n_2,Switch8_out12_carry_n_3,Switch8_out12_carry_n_4,Switch8_out12_carry_n_5,Switch8_out12_carry_n_6,Switch8_out12_carry_n_7}),
        .DI({u_Counter_Ctrl_n_150,u_Counter_Ctrl_n_151,u_Counter_Ctrl_n_152,u_Counter_Ctrl_n_153,u_Counter_Ctrl_n_154,u_Counter_Ctrl_n_155,u_Counter_Ctrl_n_156,u_Counter_Ctrl_n_157}),
        .O(NLW_Switch8_out12_carry_O_UNCONNECTED[7:0]),
        .S({u_Counter_Ctrl_n_142,u_Counter_Ctrl_n_143,u_Counter_Ctrl_n_144,u_Counter_Ctrl_n_145,u_Counter_Ctrl_n_146,u_Counter_Ctrl_n_147,u_Counter_Ctrl_n_148,u_Counter_Ctrl_n_149}));
  (* COMPARATOR_THRESHOLD = "11" *) 
  CARRY8 Switch8_out12_carry__0
       (.CI(Switch8_out12_carry_n_0),
        .CI_TOP(1'b0),
        .CO({NLW_Switch8_out12_carry__0_CO_UNCONNECTED[7:2],Relational_Operator1_relop1,Switch8_out12_carry__0_n_7}),
        .DI({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,u_Counter_Ctrl_n_119,u_Counter_Ctrl_n_120}),
        .O(NLW_Switch8_out12_carry__0_O_UNCONNECTED[7:0]),
        .S({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,u_LimitPulseWidth_n_38,u_Counter_Ctrl_n_121}));
  (* COMPARATOR_THRESHOLD = "11" *) 
  CARRY8 Switch9_out12_carry
       (.CI(1'b1),
        .CI_TOP(1'b0),
        .CO({Switch9_out12_carry_n_0,Switch9_out12_carry_n_1,Switch9_out12_carry_n_2,Switch9_out12_carry_n_3,Switch9_out12_carry_n_4,Switch9_out12_carry_n_5,Switch9_out12_carry_n_6,Switch9_out12_carry_n_7}),
        .DI({u_Counter_Ctrl_n_96,u_Counter_Ctrl_n_97,u_Counter_Ctrl_n_98,u_Counter_Ctrl_n_99,u_Counter_Ctrl_n_100,u_Counter_Ctrl_n_101,u_Counter_Ctrl_n_102,u_Counter_Ctrl_n_103}),
        .O(NLW_Switch9_out12_carry_O_UNCONNECTED[7:0]),
        .S({u_Counter_Ctrl_n_88,u_Counter_Ctrl_n_89,u_Counter_Ctrl_n_90,u_Counter_Ctrl_n_91,u_Counter_Ctrl_n_92,u_Counter_Ctrl_n_93,u_Counter_Ctrl_n_94,u_Counter_Ctrl_n_95}));
  (* COMPARATOR_THRESHOLD = "11" *) 
  CARRY8 Switch9_out12_carry__0
       (.CI(Switch9_out12_carry_n_0),
        .CI_TOP(1'b0),
        .CO({NLW_Switch9_out12_carry__0_CO_UNCONNECTED[7:2],Relational_Operator2_relop1,Switch9_out12_carry__0_n_7}),
        .DI({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,u_Counter_Ctrl_n_65,u_Counter_Ctrl_n_66}),
        .O(NLW_Switch9_out12_carry__0_O_UNCONNECTED[7:0]),
        .S({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,u_LimitPulseWidth_n_17,u_Counter_Ctrl_n_67}));
  FDRE \T_carrier_us_AXI_1_reg[0] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(\T_carrier_us_AXI_1_reg[24]_0 [0]),
        .Q(T_carrier_us[0]),
        .R(reset));
  FDRE \T_carrier_us_AXI_1_reg[10] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(\T_carrier_us_AXI_1_reg[24]_0 [10]),
        .Q(T_carrier_us[10]),
        .R(reset));
  FDRE \T_carrier_us_AXI_1_reg[11] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(\T_carrier_us_AXI_1_reg[24]_0 [11]),
        .Q(T_carrier_us[11]),
        .R(reset));
  FDRE \T_carrier_us_AXI_1_reg[12] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(\T_carrier_us_AXI_1_reg[24]_0 [12]),
        .Q(T_carrier_us[12]),
        .R(reset));
  FDRE \T_carrier_us_AXI_1_reg[13] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(\T_carrier_us_AXI_1_reg[24]_0 [13]),
        .Q(T_carrier_us[13]),
        .R(reset));
  FDRE \T_carrier_us_AXI_1_reg[14] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(\T_carrier_us_AXI_1_reg[24]_0 [14]),
        .Q(T_carrier_us[14]),
        .R(reset));
  FDRE \T_carrier_us_AXI_1_reg[15] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(\T_carrier_us_AXI_1_reg[24]_0 [15]),
        .Q(T_carrier_us[15]),
        .R(reset));
  FDRE \T_carrier_us_AXI_1_reg[16] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(\T_carrier_us_AXI_1_reg[24]_0 [16]),
        .Q(T_carrier_us[16]),
        .R(reset));
  FDRE \T_carrier_us_AXI_1_reg[17] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(\T_carrier_us_AXI_1_reg[24]_0 [17]),
        .Q(T_carrier_us[17]),
        .R(reset));
  FDRE \T_carrier_us_AXI_1_reg[18] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(\T_carrier_us_AXI_1_reg[24]_0 [18]),
        .Q(T_carrier_us[18]),
        .R(reset));
  FDRE \T_carrier_us_AXI_1_reg[19] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(\T_carrier_us_AXI_1_reg[24]_0 [19]),
        .Q(T_carrier_us[19]),
        .R(reset));
  FDRE \T_carrier_us_AXI_1_reg[1] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(\T_carrier_us_AXI_1_reg[24]_0 [1]),
        .Q(T_carrier_us[1]),
        .R(reset));
  FDRE \T_carrier_us_AXI_1_reg[20] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(\T_carrier_us_AXI_1_reg[24]_0 [20]),
        .Q(T_carrier_us[20]),
        .R(reset));
  FDRE \T_carrier_us_AXI_1_reg[21] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(\T_carrier_us_AXI_1_reg[24]_0 [21]),
        .Q(T_carrier_us[21]),
        .R(reset));
  FDRE \T_carrier_us_AXI_1_reg[22] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(\T_carrier_us_AXI_1_reg[24]_0 [22]),
        .Q(T_carrier_us[22]),
        .R(reset));
  FDRE \T_carrier_us_AXI_1_reg[23] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(\T_carrier_us_AXI_1_reg[24]_0 [23]),
        .Q(T_carrier_us[23]),
        .R(reset));
  FDRE \T_carrier_us_AXI_1_reg[24] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(\T_carrier_us_AXI_1_reg[24]_0 [24]),
        .Q(T_carrier_us[24]),
        .R(reset));
  FDRE \T_carrier_us_AXI_1_reg[2] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(\T_carrier_us_AXI_1_reg[24]_0 [2]),
        .Q(T_carrier_us[2]),
        .R(reset));
  FDRE \T_carrier_us_AXI_1_reg[3] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(\T_carrier_us_AXI_1_reg[24]_0 [3]),
        .Q(T_carrier_us[3]),
        .R(reset));
  FDRE \T_carrier_us_AXI_1_reg[4] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(\T_carrier_us_AXI_1_reg[24]_0 [4]),
        .Q(T_carrier_us[4]),
        .R(reset));
  FDRE \T_carrier_us_AXI_1_reg[5] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(\T_carrier_us_AXI_1_reg[24]_0 [5]),
        .Q(T_carrier_us[5]),
        .R(reset));
  FDRE \T_carrier_us_AXI_1_reg[6] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(\T_carrier_us_AXI_1_reg[24]_0 [6]),
        .Q(T_carrier_us[6]),
        .R(reset));
  FDRE \T_carrier_us_AXI_1_reg[7] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(\T_carrier_us_AXI_1_reg[24]_0 [7]),
        .Q(T_carrier_us[7]),
        .R(reset));
  FDRE \T_carrier_us_AXI_1_reg[8] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(\T_carrier_us_AXI_1_reg[24]_0 [8]),
        .Q(T_carrier_us[8]),
        .R(reset));
  FDRE \T_carrier_us_AXI_1_reg[9] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(\T_carrier_us_AXI_1_reg[24]_0 [9]),
        .Q(T_carrier_us[9]),
        .R(reset));
  FDRE \T_carrier_us_AXI_2_reg[0] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(T_carrier_us[0]),
        .Q(Q[0]),
        .R(reset));
  FDRE \T_carrier_us_AXI_2_reg[10] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(T_carrier_us[10]),
        .Q(Q[10]),
        .R(reset));
  FDRE \T_carrier_us_AXI_2_reg[11] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(T_carrier_us[11]),
        .Q(Q[11]),
        .R(reset));
  FDRE \T_carrier_us_AXI_2_reg[12] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(T_carrier_us[12]),
        .Q(Q[12]),
        .R(reset));
  FDRE \T_carrier_us_AXI_2_reg[13] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(T_carrier_us[13]),
        .Q(Q[13]),
        .R(reset));
  FDRE \T_carrier_us_AXI_2_reg[14] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(T_carrier_us[14]),
        .Q(Q[14]),
        .R(reset));
  FDRE \T_carrier_us_AXI_2_reg[15] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(T_carrier_us[15]),
        .Q(Q[15]),
        .R(reset));
  FDRE \T_carrier_us_AXI_2_reg[16] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(T_carrier_us[16]),
        .Q(Q[16]),
        .R(reset));
  FDRE \T_carrier_us_AXI_2_reg[17] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(T_carrier_us[17]),
        .Q(Q[17]),
        .R(reset));
  FDRE \T_carrier_us_AXI_2_reg[18] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(T_carrier_us[18]),
        .Q(Q[18]),
        .R(reset));
  FDRE \T_carrier_us_AXI_2_reg[19] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(T_carrier_us[19]),
        .Q(Q[19]),
        .R(reset));
  FDRE \T_carrier_us_AXI_2_reg[1] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(T_carrier_us[1]),
        .Q(Q[1]),
        .R(reset));
  FDRE \T_carrier_us_AXI_2_reg[20] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(T_carrier_us[20]),
        .Q(Q[20]),
        .R(reset));
  FDRE \T_carrier_us_AXI_2_reg[21] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(T_carrier_us[21]),
        .Q(Q[21]),
        .R(reset));
  FDRE \T_carrier_us_AXI_2_reg[22] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(T_carrier_us[22]),
        .Q(Q[22]),
        .R(reset));
  FDRE \T_carrier_us_AXI_2_reg[23] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(T_carrier_us[23]),
        .Q(Q[23]),
        .R(reset));
  FDRE \T_carrier_us_AXI_2_reg[24] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(T_carrier_us[24]),
        .Q(Q[24]),
        .R(reset));
  FDRE \T_carrier_us_AXI_2_reg[2] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(T_carrier_us[2]),
        .Q(Q[2]),
        .R(reset));
  FDRE \T_carrier_us_AXI_2_reg[3] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(T_carrier_us[3]),
        .Q(Q[3]),
        .R(reset));
  FDRE \T_carrier_us_AXI_2_reg[4] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(T_carrier_us[4]),
        .Q(Q[4]),
        .R(reset));
  FDRE \T_carrier_us_AXI_2_reg[5] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(T_carrier_us[5]),
        .Q(Q[5]),
        .R(reset));
  FDRE \T_carrier_us_AXI_2_reg[6] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(T_carrier_us[6]),
        .Q(Q[6]),
        .R(reset));
  FDRE \T_carrier_us_AXI_2_reg[7] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(T_carrier_us[7]),
        .Q(Q[7]),
        .R(reset));
  FDRE \T_carrier_us_AXI_2_reg[8] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(T_carrier_us[8]),
        .Q(Q[8]),
        .R(reset));
  FDRE \T_carrier_us_AXI_2_reg[9] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(T_carrier_us[9]),
        .Q(Q[9]),
        .R(reset));
  FDRE \U1_norm_1_reg[0] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(\U1_norm_1_reg[13]_0 [0]),
        .Q(U1_norm_1[0]),
        .R(reset));
  FDRE \U1_norm_1_reg[10] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(\U1_norm_1_reg[13]_0 [10]),
        .Q(U1_norm_1[10]),
        .R(reset));
  FDRE \U1_norm_1_reg[11] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(\U1_norm_1_reg[13]_0 [11]),
        .Q(U1_norm_1[11]),
        .R(reset));
  FDRE \U1_norm_1_reg[12] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(\U1_norm_1_reg[13]_0 [12]),
        .Q(U1_norm_1[12]),
        .R(reset));
  FDRE \U1_norm_1_reg[13] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(\U1_norm_1_reg[13]_0 [13]),
        .Q(U1_norm_1[13]),
        .R(reset));
  FDRE \U1_norm_1_reg[1] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(\U1_norm_1_reg[13]_0 [1]),
        .Q(U1_norm_1[1]),
        .R(reset));
  FDRE \U1_norm_1_reg[2] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(\U1_norm_1_reg[13]_0 [2]),
        .Q(U1_norm_1[2]),
        .R(reset));
  FDRE \U1_norm_1_reg[3] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(\U1_norm_1_reg[13]_0 [3]),
        .Q(U1_norm_1[3]),
        .R(reset));
  FDRE \U1_norm_1_reg[4] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(\U1_norm_1_reg[13]_0 [4]),
        .Q(U1_norm_1[4]),
        .R(reset));
  FDRE \U1_norm_1_reg[5] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(\U1_norm_1_reg[13]_0 [5]),
        .Q(U1_norm_1[5]),
        .R(reset));
  FDRE \U1_norm_1_reg[6] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(\U1_norm_1_reg[13]_0 [6]),
        .Q(U1_norm_1[6]),
        .R(reset));
  FDRE \U1_norm_1_reg[7] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(\U1_norm_1_reg[13]_0 [7]),
        .Q(U1_norm_1[7]),
        .R(reset));
  FDRE \U1_norm_1_reg[8] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(\U1_norm_1_reg[13]_0 [8]),
        .Q(U1_norm_1[8]),
        .R(reset));
  FDRE \U1_norm_1_reg[9] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(\U1_norm_1_reg[13]_0 [9]),
        .Q(U1_norm_1[9]),
        .R(reset));
  FDRE \U2_norm_1_reg[0] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(\U2_norm_1_reg[13]_0 [0]),
        .Q(U2_norm_1[0]),
        .R(reset));
  FDRE \U2_norm_1_reg[10] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(\U2_norm_1_reg[13]_0 [10]),
        .Q(U2_norm_1[10]),
        .R(reset));
  FDRE \U2_norm_1_reg[11] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(\U2_norm_1_reg[13]_0 [11]),
        .Q(U2_norm_1[11]),
        .R(reset));
  FDRE \U2_norm_1_reg[12] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(\U2_norm_1_reg[13]_0 [12]),
        .Q(U2_norm_1[12]),
        .R(reset));
  FDRE \U2_norm_1_reg[13] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(\U2_norm_1_reg[13]_0 [13]),
        .Q(U2_norm_1[13]),
        .R(reset));
  FDRE \U2_norm_1_reg[1] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(\U2_norm_1_reg[13]_0 [1]),
        .Q(U2_norm_1[1]),
        .R(reset));
  FDRE \U2_norm_1_reg[2] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(\U2_norm_1_reg[13]_0 [2]),
        .Q(U2_norm_1[2]),
        .R(reset));
  FDRE \U2_norm_1_reg[3] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(\U2_norm_1_reg[13]_0 [3]),
        .Q(U2_norm_1[3]),
        .R(reset));
  FDRE \U2_norm_1_reg[4] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(\U2_norm_1_reg[13]_0 [4]),
        .Q(U2_norm_1[4]),
        .R(reset));
  FDRE \U2_norm_1_reg[5] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(\U2_norm_1_reg[13]_0 [5]),
        .Q(U2_norm_1[5]),
        .R(reset));
  FDRE \U2_norm_1_reg[6] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(\U2_norm_1_reg[13]_0 [6]),
        .Q(U2_norm_1[6]),
        .R(reset));
  FDRE \U2_norm_1_reg[7] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(\U2_norm_1_reg[13]_0 [7]),
        .Q(U2_norm_1[7]),
        .R(reset));
  FDRE \U2_norm_1_reg[8] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(\U2_norm_1_reg[13]_0 [8]),
        .Q(U2_norm_1[8]),
        .R(reset));
  FDRE \U2_norm_1_reg[9] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(\U2_norm_1_reg[13]_0 [9]),
        .Q(U2_norm_1[9]),
        .R(reset));
  FDRE \U3_norm_1_reg[0] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(\U3_norm_1_reg[13]_0 [0]),
        .Q(U3_norm_1[0]),
        .R(reset));
  FDRE \U3_norm_1_reg[10] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(\U3_norm_1_reg[13]_0 [10]),
        .Q(U3_norm_1[10]),
        .R(reset));
  FDRE \U3_norm_1_reg[11] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(\U3_norm_1_reg[13]_0 [11]),
        .Q(U3_norm_1[11]),
        .R(reset));
  FDRE \U3_norm_1_reg[12] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(\U3_norm_1_reg[13]_0 [12]),
        .Q(U3_norm_1[12]),
        .R(reset));
  FDRE \U3_norm_1_reg[13] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(\U3_norm_1_reg[13]_0 [13]),
        .Q(U3_norm_1[13]),
        .R(reset));
  FDRE \U3_norm_1_reg[1] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(\U3_norm_1_reg[13]_0 [1]),
        .Q(U3_norm_1[1]),
        .R(reset));
  FDRE \U3_norm_1_reg[2] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(\U3_norm_1_reg[13]_0 [2]),
        .Q(U3_norm_1[2]),
        .R(reset));
  FDRE \U3_norm_1_reg[3] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(\U3_norm_1_reg[13]_0 [3]),
        .Q(U3_norm_1[3]),
        .R(reset));
  FDRE \U3_norm_1_reg[4] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(\U3_norm_1_reg[13]_0 [4]),
        .Q(U3_norm_1[4]),
        .R(reset));
  FDRE \U3_norm_1_reg[5] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(\U3_norm_1_reg[13]_0 [5]),
        .Q(U3_norm_1[5]),
        .R(reset));
  FDRE \U3_norm_1_reg[6] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(\U3_norm_1_reg[13]_0 [6]),
        .Q(U3_norm_1[6]),
        .R(reset));
  FDRE \U3_norm_1_reg[7] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(\U3_norm_1_reg[13]_0 [7]),
        .Q(U3_norm_1[7]),
        .R(reset));
  FDRE \U3_norm_1_reg[8] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(\U3_norm_1_reg[13]_0 [8]),
        .Q(U3_norm_1[8]),
        .R(reset));
  FDRE \U3_norm_1_reg[9] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(\U3_norm_1_reg[13]_0 [9]),
        .Q(U3_norm_1[9]),
        .R(reset));
  FDRE \f_carrier_kHz_AXI_1_reg[0] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(D[0]),
        .Q(f_carrier_kHz[0]),
        .R(reset));
  FDRE \f_carrier_kHz_AXI_1_reg[10] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(D[10]),
        .Q(f_carrier_kHz[10]),
        .R(reset));
  FDRE \f_carrier_kHz_AXI_1_reg[11] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(D[11]),
        .Q(f_carrier_kHz[11]),
        .R(reset));
  FDRE \f_carrier_kHz_AXI_1_reg[12] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(D[12]),
        .Q(f_carrier_kHz[12]),
        .R(reset));
  FDRE \f_carrier_kHz_AXI_1_reg[13] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(D[13]),
        .Q(f_carrier_kHz[13]),
        .R(reset));
  FDRE \f_carrier_kHz_AXI_1_reg[14] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(D[14]),
        .Q(f_carrier_kHz[14]),
        .R(reset));
  FDRE \f_carrier_kHz_AXI_1_reg[15] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(D[15]),
        .Q(f_carrier_kHz[15]),
        .R(reset));
  FDRE \f_carrier_kHz_AXI_1_reg[16] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(D[16]),
        .Q(f_carrier_kHz[16]),
        .R(reset));
  FDRE \f_carrier_kHz_AXI_1_reg[17] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(D[17]),
        .Q(f_carrier_kHz[17]),
        .R(reset));
  FDRE \f_carrier_kHz_AXI_1_reg[18] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(D[18]),
        .Q(f_carrier_kHz[18]),
        .R(reset));
  FDRE \f_carrier_kHz_AXI_1_reg[19] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(D[19]),
        .Q(f_carrier_kHz[19]),
        .R(reset));
  FDRE \f_carrier_kHz_AXI_1_reg[1] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(D[1]),
        .Q(f_carrier_kHz[1]),
        .R(reset));
  FDRE \f_carrier_kHz_AXI_1_reg[20] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(D[20]),
        .Q(f_carrier_kHz[20]),
        .R(reset));
  FDRE \f_carrier_kHz_AXI_1_reg[21] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(D[21]),
        .Q(f_carrier_kHz[21]),
        .R(reset));
  FDRE \f_carrier_kHz_AXI_1_reg[22] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(D[22]),
        .Q(f_carrier_kHz[22]),
        .R(reset));
  FDRE \f_carrier_kHz_AXI_1_reg[23] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(D[23]),
        .Q(f_carrier_kHz[23]),
        .R(reset));
  FDRE \f_carrier_kHz_AXI_1_reg[24] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(D[24]),
        .Q(f_carrier_kHz[24]),
        .R(reset));
  FDRE \f_carrier_kHz_AXI_1_reg[2] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(D[2]),
        .Q(f_carrier_kHz[2]),
        .R(reset));
  FDRE \f_carrier_kHz_AXI_1_reg[3] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(D[3]),
        .Q(f_carrier_kHz[3]),
        .R(reset));
  FDRE \f_carrier_kHz_AXI_1_reg[4] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(D[4]),
        .Q(f_carrier_kHz[4]),
        .R(reset));
  FDRE \f_carrier_kHz_AXI_1_reg[5] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(D[5]),
        .Q(f_carrier_kHz[5]),
        .R(reset));
  FDRE \f_carrier_kHz_AXI_1_reg[6] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(D[6]),
        .Q(f_carrier_kHz[6]),
        .R(reset));
  FDRE \f_carrier_kHz_AXI_1_reg[7] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(D[7]),
        .Q(f_carrier_kHz[7]),
        .R(reset));
  FDRE \f_carrier_kHz_AXI_1_reg[8] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(D[8]),
        .Q(f_carrier_kHz[8]),
        .R(reset));
  FDRE \f_carrier_kHz_AXI_1_reg[9] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(D[9]),
        .Q(f_carrier_kHz[9]),
        .R(reset));
  FDRE \f_carrier_kHz_AXI_2_reg[10] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(f_carrier_kHz[10]),
        .Q(\f_carrier_kHz_AXI_2_reg[24]_0 [1]),
        .R(reset));
  FDRE \f_carrier_kHz_AXI_2_reg[11] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(f_carrier_kHz[11]),
        .Q(\f_carrier_kHz_AXI_2_reg[24]_0 [2]),
        .R(reset));
  FDRE \f_carrier_kHz_AXI_2_reg[12] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(f_carrier_kHz[12]),
        .Q(\f_carrier_kHz_AXI_2_reg[24]_0 [3]),
        .R(reset));
  FDRE \f_carrier_kHz_AXI_2_reg[13] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(f_carrier_kHz[13]),
        .Q(\f_carrier_kHz_AXI_2_reg[24]_0 [4]),
        .R(reset));
  FDRE \f_carrier_kHz_AXI_2_reg[14] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(f_carrier_kHz[14]),
        .Q(\f_carrier_kHz_AXI_2_reg[24]_0 [5]),
        .R(reset));
  FDRE \f_carrier_kHz_AXI_2_reg[15] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(f_carrier_kHz[15]),
        .Q(\f_carrier_kHz_AXI_2_reg[24]_0 [6]),
        .R(reset));
  FDRE \f_carrier_kHz_AXI_2_reg[16] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(f_carrier_kHz[16]),
        .Q(\f_carrier_kHz_AXI_2_reg[24]_0 [7]),
        .R(reset));
  FDRE \f_carrier_kHz_AXI_2_reg[17] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(f_carrier_kHz[17]),
        .Q(\f_carrier_kHz_AXI_2_reg[24]_0 [8]),
        .R(reset));
  FDRE \f_carrier_kHz_AXI_2_reg[18] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(f_carrier_kHz[18]),
        .Q(\f_carrier_kHz_AXI_2_reg[24]_0 [9]),
        .R(reset));
  FDRE \f_carrier_kHz_AXI_2_reg[19] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(f_carrier_kHz[19]),
        .Q(\f_carrier_kHz_AXI_2_reg[24]_0 [10]),
        .R(reset));
  FDRE \f_carrier_kHz_AXI_2_reg[20] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(f_carrier_kHz[20]),
        .Q(\f_carrier_kHz_AXI_2_reg[24]_0 [11]),
        .R(reset));
  FDRE \f_carrier_kHz_AXI_2_reg[21] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(f_carrier_kHz[21]),
        .Q(\f_carrier_kHz_AXI_2_reg[24]_0 [12]),
        .R(reset));
  FDRE \f_carrier_kHz_AXI_2_reg[22] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(f_carrier_kHz[22]),
        .Q(\f_carrier_kHz_AXI_2_reg[24]_0 [13]),
        .R(reset));
  FDRE \f_carrier_kHz_AXI_2_reg[23] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(f_carrier_kHz[23]),
        .Q(\f_carrier_kHz_AXI_2_reg[24]_0 [14]),
        .R(reset));
  FDRE \f_carrier_kHz_AXI_2_reg[24] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(f_carrier_kHz[24]),
        .Q(\f_carrier_kHz_AXI_2_reg[24]_0 [15]),
        .R(reset));
  LUT2 #(
    .INIT(4'h2)) 
    i__carry__0_i_1
       (.I0(min_pulse_width[16]),
        .I1(min_pulse_width[17]),
        .O(i__carry__0_i_1_n_0));
  FDRE \min_pulse_width_AXI_1_reg[0] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(\min_pulse_width_AXI_1_reg[17]_0 [0]),
        .Q(min_pulse_width[0]),
        .R(reset));
  FDRE \min_pulse_width_AXI_1_reg[10] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(\min_pulse_width_AXI_1_reg[17]_0 [10]),
        .Q(min_pulse_width[10]),
        .R(reset));
  FDRE \min_pulse_width_AXI_1_reg[11] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(\min_pulse_width_AXI_1_reg[17]_0 [11]),
        .Q(min_pulse_width[11]),
        .R(reset));
  FDRE \min_pulse_width_AXI_1_reg[12] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(\min_pulse_width_AXI_1_reg[17]_0 [12]),
        .Q(min_pulse_width[12]),
        .R(reset));
  FDRE \min_pulse_width_AXI_1_reg[13] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(\min_pulse_width_AXI_1_reg[17]_0 [13]),
        .Q(min_pulse_width[13]),
        .R(reset));
  FDRE \min_pulse_width_AXI_1_reg[14] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(\min_pulse_width_AXI_1_reg[17]_0 [14]),
        .Q(min_pulse_width[14]),
        .R(reset));
  FDRE \min_pulse_width_AXI_1_reg[15] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(\min_pulse_width_AXI_1_reg[17]_0 [15]),
        .Q(min_pulse_width[15]),
        .R(reset));
  FDRE \min_pulse_width_AXI_1_reg[16] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(\min_pulse_width_AXI_1_reg[17]_0 [16]),
        .Q(min_pulse_width[16]),
        .R(reset));
  FDRE \min_pulse_width_AXI_1_reg[17] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(\min_pulse_width_AXI_1_reg[17]_0 [17]),
        .Q(min_pulse_width[17]),
        .R(reset));
  FDRE \min_pulse_width_AXI_1_reg[1] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(\min_pulse_width_AXI_1_reg[17]_0 [1]),
        .Q(min_pulse_width[1]),
        .R(reset));
  FDRE \min_pulse_width_AXI_1_reg[2] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(\min_pulse_width_AXI_1_reg[17]_0 [2]),
        .Q(min_pulse_width[2]),
        .R(reset));
  FDRE \min_pulse_width_AXI_1_reg[3] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(\min_pulse_width_AXI_1_reg[17]_0 [3]),
        .Q(min_pulse_width[3]),
        .R(reset));
  FDRE \min_pulse_width_AXI_1_reg[4] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(\min_pulse_width_AXI_1_reg[17]_0 [4]),
        .Q(min_pulse_width[4]),
        .R(reset));
  FDRE \min_pulse_width_AXI_1_reg[5] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(\min_pulse_width_AXI_1_reg[17]_0 [5]),
        .Q(min_pulse_width[5]),
        .R(reset));
  FDRE \min_pulse_width_AXI_1_reg[6] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(\min_pulse_width_AXI_1_reg[17]_0 [6]),
        .Q(min_pulse_width[6]),
        .R(reset));
  FDRE \min_pulse_width_AXI_1_reg[7] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(\min_pulse_width_AXI_1_reg[17]_0 [7]),
        .Q(min_pulse_width[7]),
        .R(reset));
  FDRE \min_pulse_width_AXI_1_reg[8] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(\min_pulse_width_AXI_1_reg[17]_0 [8]),
        .Q(min_pulse_width[8]),
        .R(reset));
  FDRE \min_pulse_width_AXI_1_reg[9] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(\min_pulse_width_AXI_1_reg[17]_0 [9]),
        .Q(min_pulse_width[9]),
        .R(reset));
  FDRE \min_pulse_width_AXI_2_reg[0] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(min_pulse_width[0]),
        .Q(\min_pulse_width_AXI_2_reg[17]_0 [0]),
        .R(reset));
  FDRE \min_pulse_width_AXI_2_reg[10] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(min_pulse_width[10]),
        .Q(\min_pulse_width_AXI_2_reg[17]_0 [10]),
        .R(reset));
  FDRE \min_pulse_width_AXI_2_reg[11] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(min_pulse_width[11]),
        .Q(\min_pulse_width_AXI_2_reg[17]_0 [11]),
        .R(reset));
  FDRE \min_pulse_width_AXI_2_reg[12] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(min_pulse_width[12]),
        .Q(\min_pulse_width_AXI_2_reg[17]_0 [12]),
        .R(reset));
  FDRE \min_pulse_width_AXI_2_reg[13] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(min_pulse_width[13]),
        .Q(\min_pulse_width_AXI_2_reg[17]_0 [13]),
        .R(reset));
  FDRE \min_pulse_width_AXI_2_reg[14] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(min_pulse_width[14]),
        .Q(\min_pulse_width_AXI_2_reg[17]_0 [14]),
        .R(reset));
  FDRE \min_pulse_width_AXI_2_reg[15] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(min_pulse_width[15]),
        .Q(\min_pulse_width_AXI_2_reg[17]_0 [15]),
        .R(reset));
  FDRE \min_pulse_width_AXI_2_reg[16] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(min_pulse_width[16]),
        .Q(\min_pulse_width_AXI_2_reg[17]_0 [16]),
        .R(reset));
  FDRE \min_pulse_width_AXI_2_reg[17] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(min_pulse_width[17]),
        .Q(\min_pulse_width_AXI_2_reg[17]_0 [17]),
        .R(reset));
  FDRE \min_pulse_width_AXI_2_reg[1] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(min_pulse_width[1]),
        .Q(\min_pulse_width_AXI_2_reg[17]_0 [1]),
        .R(reset));
  FDRE \min_pulse_width_AXI_2_reg[2] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(min_pulse_width[2]),
        .Q(\min_pulse_width_AXI_2_reg[17]_0 [2]),
        .R(reset));
  FDRE \min_pulse_width_AXI_2_reg[3] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(min_pulse_width[3]),
        .Q(\min_pulse_width_AXI_2_reg[17]_0 [3]),
        .R(reset));
  FDRE \min_pulse_width_AXI_2_reg[4] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(min_pulse_width[4]),
        .Q(\min_pulse_width_AXI_2_reg[17]_0 [4]),
        .R(reset));
  FDRE \min_pulse_width_AXI_2_reg[5] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(min_pulse_width[5]),
        .Q(\min_pulse_width_AXI_2_reg[17]_0 [5]),
        .R(reset));
  FDRE \min_pulse_width_AXI_2_reg[6] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(min_pulse_width[6]),
        .Q(\min_pulse_width_AXI_2_reg[17]_0 [6]),
        .R(reset));
  FDRE \min_pulse_width_AXI_2_reg[7] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(min_pulse_width[7]),
        .Q(\min_pulse_width_AXI_2_reg[17]_0 [7]),
        .R(reset));
  FDRE \min_pulse_width_AXI_2_reg[8] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(min_pulse_width[8]),
        .Q(\min_pulse_width_AXI_2_reg[17]_0 [8]),
        .R(reset));
  FDRE \min_pulse_width_AXI_2_reg[9] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(min_pulse_width[9]),
        .Q(\min_pulse_width_AXI_2_reg[17]_0 [9]),
        .R(reset));
  zusys_PWM_and_SS_control_V_0_2_PWM_and_SS_control_V3_ip_src_Counter_Ctrl u_Counter_Ctrl
       (.Add_out1(Add_out1),
        .Allow_assymetrical_anew_reference_value__0(Allow_assymetrical_anew_reference_value__0),
        .B({HDL_Counter2_count_next,B}),
        .CEB2(CEB2),
        .CO(Counter_Ctrl_out3),
        .D(D),
        .DI(DI[1]),
        .\Delay1_out1_reg[12] ({u_Counter_Ctrl_n_104,u_Counter_Ctrl_n_105,u_Counter_Ctrl_n_106,u_Counter_Ctrl_n_107,u_Counter_Ctrl_n_108,u_Counter_Ctrl_n_109,u_Counter_Ctrl_n_110}),
        .\Delay1_out1_reg[12]_0 ({u_Counter_Ctrl_n_112,u_Counter_Ctrl_n_113,u_Counter_Ctrl_n_114,u_Counter_Ctrl_n_115,u_Counter_Ctrl_n_116,u_Counter_Ctrl_n_117,u_Counter_Ctrl_n_118}),
        .\Delay1_out1_reg[12]_1 ({u_Counter_Ctrl_n_135,u_Counter_Ctrl_n_136,u_Counter_Ctrl_n_137,u_Counter_Ctrl_n_138,u_Counter_Ctrl_n_139,u_Counter_Ctrl_n_140,u_Counter_Ctrl_n_141}),
        .\Delay1_out1_reg[12]_2 (u_Counter_Ctrl_n_202),
        .\Delay1_out1_reg[13] (Delay1_out1),
        .\Delay1_out1_reg[13]_0 (U2_norm_1),
        .\Delay2_out1_reg[12] ({u_Counter_Ctrl_n_49,u_Counter_Ctrl_n_50,u_Counter_Ctrl_n_51,u_Counter_Ctrl_n_52,u_Counter_Ctrl_n_53,u_Counter_Ctrl_n_54,u_Counter_Ctrl_n_55}),
        .\Delay2_out1_reg[12]_0 ({u_Counter_Ctrl_n_58,u_Counter_Ctrl_n_59,u_Counter_Ctrl_n_60,u_Counter_Ctrl_n_61,u_Counter_Ctrl_n_62,u_Counter_Ctrl_n_63,u_Counter_Ctrl_n_64}),
        .\Delay2_out1_reg[12]_1 ({u_Counter_Ctrl_n_81,u_Counter_Ctrl_n_82,u_Counter_Ctrl_n_83,u_Counter_Ctrl_n_84,u_Counter_Ctrl_n_85,u_Counter_Ctrl_n_86,u_Counter_Ctrl_n_87}),
        .\Delay2_out1_reg[12]_2 (u_Counter_Ctrl_n_201),
        .\Delay2_out1_reg[13] (Delay2_out1),
        .\Delay2_out1_reg[13]_0 (U3_norm_1),
        .\Delay2_out1_reg[13]_1 (u_LimitPulseWidth_n_50),
        .Delay6_out1_reg_0(\HDL_Counter2_count_reg[2]_0 ),
        .Delay6_out1_reg_1(\HDL_Counter2_count_reg[3]_0 ),
        .\Delay_out1_reg[12] ({u_Counter_Ctrl_n_158,u_Counter_Ctrl_n_159,u_Counter_Ctrl_n_160,u_Counter_Ctrl_n_161,u_Counter_Ctrl_n_162,u_Counter_Ctrl_n_163,u_Counter_Ctrl_n_164}),
        .\Delay_out1_reg[12]_0 ({u_Counter_Ctrl_n_179,u_Counter_Ctrl_n_180,u_Counter_Ctrl_n_181,u_Counter_Ctrl_n_182,u_Counter_Ctrl_n_183,u_Counter_Ctrl_n_184,u_Counter_Ctrl_n_185}),
        .\Delay_out1_reg[12]_1 (u_Counter_Ctrl_n_203),
        .\Delay_out1_reg[12]_2 (u_Counter_Ctrl_n_204),
        .\Delay_out1_reg[13] (Delay_out1),
        .\Delay_out1_reg[13]_0 (U1_norm_1),
        .E(E),
        .HDL_Counter2_count_reg({HDL_Counter2_count_reg[19:8],HDL_Counter2_count_reg[1]}),
        .\HDL_Counter2_count_reg[0] ({u_Counter_Ctrl_n_26,u_Counter_Ctrl_n_27,u_Counter_Ctrl_n_28,u_Counter_Ctrl_n_29,u_Counter_Ctrl_n_30,u_Counter_Ctrl_n_31,u_Counter_Ctrl_n_32,u_Counter_Ctrl_n_33}),
        .\HDL_Counter2_count_reg[0]_0 ({u_Counter_Ctrl_n_34,u_Counter_Ctrl_n_35,u_Counter_Ctrl_n_36,u_Counter_Ctrl_n_37}),
        .\HDL_Counter2_count_reg[0]_1 (\HDL_Counter2_count_reg[0]_0 ),
        .\HDL_Counter2_count_reg[0]_2 (S[1:0]),
        .\HDL_Counter2_count_reg[15] ({u_Counter_Ctrl_n_38,u_Counter_Ctrl_n_39,u_Counter_Ctrl_n_40,u_Counter_Ctrl_n_41,u_Counter_Ctrl_n_42,u_Counter_Ctrl_n_43,u_Counter_Ctrl_n_44,u_Counter_Ctrl_n_45}),
        .\HDL_Counter2_count_reg[7]_0 (\HDL_Counter2_count_reg[7]_0 ),
        .\HDL_Counter2_count_reg[7]_1 (\HDL_Counter2_count_reg[6]_0 ),
        .\HDL_Counter2_count_reg[7]_2 (\HDL_Counter2_count_reg[5]_0 ),
        .\HDL_Counter2_count_reg[7]_3 (\HDL_Counter2_count_reg[4]_0 ),
        .HDL_Counter2_count_reg_7_sp_1(DI[0]),
        .IPCORE_CLK(IPCORE_CLK),
        .Logical_Operator_out10_carry__0_0(T_carrier_us),
        .O({u_Counter_Ctrl_n_17,u_Counter_Ctrl_n_18,u_Counter_Ctrl_n_19,u_Counter_Ctrl_n_20,u_Counter_Ctrl_n_21,u_Counter_Ctrl_n_22,u_Counter_Ctrl_n_23,u_Counter_Ctrl_n_24}),
        .P({u_Counter_Ctrl_n_0,u_Counter_Ctrl_n_1,u_Counter_Ctrl_n_2,u_Counter_Ctrl_n_3,u_Counter_Ctrl_n_4,u_Counter_Ctrl_n_5}),
        .\Product_mul_temp[-1111111102]_0 (\f_carrier_kHz_AXI_2_reg[24]_0 [0]),
        .\Product_mul_temp[-1111111103]_0 (\Product_mul_temp[-1111111103] ),
        .\Product_mul_temp[-1111111104]_0 (\Product_mul_temp[-1111111104] ),
        .\Product_mul_temp[-1111111105]_0 (\Product_mul_temp[-1111111105] ),
        .\Product_mul_temp[-1111111106]_0 (\Product_mul_temp[-1111111106] ),
        .\Product_mul_temp[-1111111107]_0 (\Product_mul_temp[-1111111107] ),
        .\Product_mul_temp[-1111111108]_0 (\Product_mul_temp[-1111111108] ),
        .\Product_mul_temp[-1111111109]_0 (\Product_mul_temp[-1111111109] ),
        .\Product_mul_temp[-1111111110]_0 (\Product_mul_temp[-1111111110] ),
        .\Product_mul_temp[-1111111111]_0 (\Product_mul_temp[-1111111111] ),
        .Q(f_carrier_kHz[9:0]),
        .Relational_Operator_1_cast(Relational_Operator_1_cast),
        .S(u_LimitPulseWidth_n_56),
        .Saturation_out1(Saturation_out1),
        .Switch6_out1(Switch6_out1),
        .Switch7_out12_carry(Relational_Operator1_relop1_1),
        .Switch7_out12_carry_0(Relational_Operator_relop1_0),
        .Switch7_out12_carry_i_6(u_LimitPulseWidth_n_51),
        .Switch7_out12_carry_i_6_0(u_LimitPulseWidth_n_53),
        .Switch7_out12_carry_i_6_1(u_LimitPulseWidth_n_52),
        .Switch8_out12_carry(Relational_Operator_relop1_2),
        .Switch8_out12_carry_0(Relational_Operator1_relop1_3),
        .Switch9_out12_carry(Relational_Operator_relop1_4),
        .Switch9_out12_carry_0(Relational_Operator1_relop1_5),
        .\U1_norm_1_reg[10] ({u_Counter_Ctrl_n_188,u_Counter_Ctrl_n_189,u_Counter_Ctrl_n_190,u_Counter_Ctrl_n_191,u_Counter_Ctrl_n_192,u_Counter_Ctrl_n_193}),
        .\U1_norm_1_reg[11] (u_Counter_Ctrl_n_187),
        .\U1_norm_1_reg[12] (u_Counter_Ctrl_n_186),
        .\U1_norm_1_reg[9] ({u_Counter_Ctrl_n_194,u_Counter_Ctrl_n_195,u_Counter_Ctrl_n_196,u_Counter_Ctrl_n_197,u_Counter_Ctrl_n_198,u_Counter_Ctrl_n_199}),
        .\U2_norm_1_reg[10] ({u_Counter_Ctrl_n_142,u_Counter_Ctrl_n_143,u_Counter_Ctrl_n_144,u_Counter_Ctrl_n_145,u_Counter_Ctrl_n_146,u_Counter_Ctrl_n_147,u_Counter_Ctrl_n_148,u_Counter_Ctrl_n_149}),
        .\U2_norm_1_reg[12] (u_Counter_Ctrl_n_121),
        .\U2_norm_1_reg[12]_0 ({u_Counter_Ctrl_n_122,u_Counter_Ctrl_n_123,u_Counter_Ctrl_n_124,u_Counter_Ctrl_n_125,u_Counter_Ctrl_n_126,u_Counter_Ctrl_n_127,u_Counter_Ctrl_n_128,u_Counter_Ctrl_n_129,u_Counter_Ctrl_n_130,u_Counter_Ctrl_n_131,u_Counter_Ctrl_n_132,u_Counter_Ctrl_n_133,u_Counter_Ctrl_n_134}),
        .\U2_norm_1_reg[13] (u_Counter_Ctrl_n_111),
        .\U2_norm_1_reg[13]_0 ({u_Counter_Ctrl_n_119,u_Counter_Ctrl_n_120}),
        .\U2_norm_1_reg[9] ({u_Counter_Ctrl_n_150,u_Counter_Ctrl_n_151,u_Counter_Ctrl_n_152,u_Counter_Ctrl_n_153,u_Counter_Ctrl_n_154,u_Counter_Ctrl_n_155,u_Counter_Ctrl_n_156,u_Counter_Ctrl_n_157}),
        .\U3_norm_1_reg[10] ({u_Counter_Ctrl_n_88,u_Counter_Ctrl_n_89,u_Counter_Ctrl_n_90,u_Counter_Ctrl_n_91,u_Counter_Ctrl_n_92,u_Counter_Ctrl_n_93,u_Counter_Ctrl_n_94,u_Counter_Ctrl_n_95}),
        .\U3_norm_1_reg[12] (u_Counter_Ctrl_n_67),
        .\U3_norm_1_reg[12]_0 ({u_Counter_Ctrl_n_68,u_Counter_Ctrl_n_69,u_Counter_Ctrl_n_70,u_Counter_Ctrl_n_71,u_Counter_Ctrl_n_72,u_Counter_Ctrl_n_73,u_Counter_Ctrl_n_74,u_Counter_Ctrl_n_75,u_Counter_Ctrl_n_76,u_Counter_Ctrl_n_77,u_Counter_Ctrl_n_78,u_Counter_Ctrl_n_79,u_Counter_Ctrl_n_80}),
        .\U3_norm_1_reg[13] (u_Counter_Ctrl_n_56),
        .\U3_norm_1_reg[13]_0 ({u_Counter_Ctrl_n_65,u_Counter_Ctrl_n_66}),
        .\U3_norm_1_reg[9] ({u_Counter_Ctrl_n_96,u_Counter_Ctrl_n_97,u_Counter_Ctrl_n_98,u_Counter_Ctrl_n_99,u_Counter_Ctrl_n_100,u_Counter_Ctrl_n_101,u_Counter_Ctrl_n_102,u_Counter_Ctrl_n_103}),
        .reset(reset));
  zusys_PWM_and_SS_control_V_0_2_PWM_and_SS_control_V3_ip_src_LimitPulseWidth u_LimitPulseWidth
       (.Add_out1(Add_out1),
        .Allow_assymetrical_anew_reference_value__0(Allow_assymetrical_anew_reference_value__0),
        .Counter_Ctrl_out3_1_reg(T_carrier_us[24]),
        .Counter_Ctrl_out4_1_reg(DI[0]),
        .Counter_Ctrl_out4_1_reg_0(\HDL_Counter2_count_reg[4]_0 ),
        .Counter_Ctrl_out4_1_reg_1(\HDL_Counter2_count_reg[2]_0 ),
        .D({u_Counter_Ctrl_n_69,u_Counter_Ctrl_n_71,u_Counter_Ctrl_n_73,u_Counter_Ctrl_n_75,u_Counter_Ctrl_n_77,u_Counter_Ctrl_n_79}),
        .DI({u_LimitPulseWidth_n_18,u_LimitPulseWidth_n_19,u_LimitPulseWidth_n_20,u_LimitPulseWidth_n_21,u_LimitPulseWidth_n_22,u_LimitPulseWidth_n_23,u_LimitPulseWidth_n_24}),
        .\Delay1_out1_reg[10] ({u_LimitPulseWidth_n_39,u_LimitPulseWidth_n_40,u_LimitPulseWidth_n_41,u_LimitPulseWidth_n_42,u_LimitPulseWidth_n_43,u_LimitPulseWidth_n_44,u_LimitPulseWidth_n_45}),
        .\Delay1_out1_reg[13] (u_LimitPulseWidth_n_38),
        .\Delay2_out1_reg[13] (u_LimitPulseWidth_n_17),
        .\Delay_out1[13]_i_2_0 (\HDL_Counter2_count_reg[7]_0 ),
        .\Delay_out1[13]_i_2_1 (\HDL_Counter2_count_reg[6]_0 ),
        .\Delay_out1[13]_i_2_2 (\HDL_Counter2_count_reg[5]_0 ),
        .\Delay_out1[13]_i_2_3 (\HDL_Counter2_count_reg[3]_0 ),
        .\Delay_out1_reg[0] ({u_LimitPulseWidth_n_48,u_LimitPulseWidth_n_49}),
        .\Delay_out1_reg[12] (Relational_Operator_relop1_0),
        .\Delay_out1_reg[13] (u_LimitPulseWidth_n_47),
        .HDL_Counter2_count_reg({HDL_Counter2_count_reg[18:8],HDL_Counter2_count_reg[1]}),
        .\HDL_Counter2_count_reg[11]_0 (u_LimitPulseWidth_n_51),
        .\HDL_Counter2_count_reg[16] (u_LimitPulseWidth_n_52),
        .HDL_Counter2_count_reg_11_sp_1(u_LimitPulseWidth_n_50),
        .HDL_Counter2_count_reg_1_sp_1(u_LimitPulseWidth_n_53),
        .IPCORE_CLK({u_LimitPulseWidth_n_54,u_LimitPulseWidth_n_55}),
        .Logical_Operator_out10_carry_0({u_Counter_Ctrl_n_123,u_Counter_Ctrl_n_125,u_Counter_Ctrl_n_127,u_Counter_Ctrl_n_129,u_Counter_Ctrl_n_131,u_Counter_Ctrl_n_133}),
        .Logical_Operator_out10_carry_1({Relational_Operator_1_cast[15],Relational_Operator_1_cast[13],Relational_Operator_1_cast[11],Relational_Operator_1_cast[9],Relational_Operator_1_cast[7],Relational_Operator_1_cast[5]}),
        .P({u_Counter_Ctrl_n_0,u_Counter_Ctrl_n_1,u_Counter_Ctrl_n_2,u_Counter_Ctrl_n_3,u_Counter_Ctrl_n_4,u_Counter_Ctrl_n_5}),
        .Q(min_pulse_width),
        .S(i__carry__0_i_1_n_0),
        .Saturation_out1(Saturation_out1),
        .Switch7_out12_carry__0({U1_norm_1[13],U1_norm_1[10],U1_norm_1[8],U1_norm_1[6],U1_norm_1[4],U1_norm_1[2],U1_norm_1[0]}),
        .Switch7_out12_carry__0_0({Delay_out1[13],Delay_out1[10],Delay_out1[8],Delay_out1[6],Delay_out1[4],Delay_out1[2],Delay_out1[0]}),
        .Switch7_out12_carry_i_7(u_Counter_Ctrl_n_203),
        .Switch7_out12_carry_i_7_0(u_Counter_Ctrl_n_204),
        .Switch7_out12_carry_i_7_1({u_Counter_Ctrl_n_158,u_Counter_Ctrl_n_159,u_Counter_Ctrl_n_160,u_Counter_Ctrl_n_161,u_Counter_Ctrl_n_162,u_Counter_Ctrl_n_163,u_Counter_Ctrl_n_164}),
        .Switch7_out12_carry_i_7_2({u_Counter_Ctrl_n_179,u_Counter_Ctrl_n_180,u_Counter_Ctrl_n_181,u_Counter_Ctrl_n_182,u_Counter_Ctrl_n_183,u_Counter_Ctrl_n_184,u_Counter_Ctrl_n_185}),
        .Switch8_out12_carry__0(Relational_Operator1_relop1_3),
        .Switch8_out12_carry__0_0(Relational_Operator_relop1_2),
        .Switch8_out12_carry__0_1({Delay1_out1[13],Delay1_out1[10],Delay1_out1[8],Delay1_out1[6],Delay1_out1[4],Delay1_out1[2],Delay1_out1[0]}),
        .Switch8_out12_carry__0_2({U2_norm_1[13],U2_norm_1[10],U2_norm_1[8],U2_norm_1[6],U2_norm_1[4],U2_norm_1[2],U2_norm_1[0]}),
        .Switch9_out12_carry__0(Relational_Operator1_relop1_5),
        .Switch9_out12_carry__0_0(Relational_Operator_relop1_4),
        .Switch9_out12_carry__0_1({Delay2_out1[13],Delay2_out1[10],Delay2_out1[8],Delay2_out1[6],Delay2_out1[4],Delay2_out1[2],Delay2_out1[0]}),
        .Switch9_out12_carry__0_2({U3_norm_1[13],U3_norm_1[10],U3_norm_1[8],U3_norm_1[6],U3_norm_1[4],U3_norm_1[2],U3_norm_1[0]}),
        .\T_carrier_us_AXI_1_reg[24] (u_LimitPulseWidth_n_56),
        .\U1_norm_1_reg[13] (u_LimitPulseWidth_n_46),
        .\min_pulse_width_AXI_1_reg[17] (u_LimitPulseWidth_n_57),
        .\min_pulse_width_AXI_1_reg[17]_0 (u_LimitPulseWidth_n_58),
        .\min_pulse_width_AXI_1_reg[1] (Relational_Operator1_relop1_1),
        .\min_pulse_width_AXI_1_reg[1]_0 (u_LimitPulseWidth_n_1));
  zusys_PWM_and_SS_control_V_0_2_PWM_and_SS_control_V3_ip_src_LimitPulseWidth1 u_LimitPulseWidth1
       (.DI({u_Counter_Ctrl_n_202,u_LimitPulseWidth_n_39,u_LimitPulseWidth_n_40,u_LimitPulseWidth_n_41,u_LimitPulseWidth_n_42,u_LimitPulseWidth_n_43,u_LimitPulseWidth_n_44,u_LimitPulseWidth_n_45}),
        .\Delay1_out1_reg[12] (Relational_Operator_relop1_2),
        .S({u_Counter_Ctrl_n_135,u_Counter_Ctrl_n_136,u_Counter_Ctrl_n_137,u_Counter_Ctrl_n_138,u_Counter_Ctrl_n_139,u_Counter_Ctrl_n_140,u_Counter_Ctrl_n_141,u_LimitPulseWidth_n_58}),
        .Switch8_out12_carry_i_7(u_LimitPulseWidth_n_1),
        .Switch8_out12_carry_i_7_0({u_Counter_Ctrl_n_104,u_Counter_Ctrl_n_105,u_Counter_Ctrl_n_106,u_Counter_Ctrl_n_107,u_Counter_Ctrl_n_108,u_Counter_Ctrl_n_109,u_Counter_Ctrl_n_110}),
        .Switch8_out12_carry_i_7_1({u_Counter_Ctrl_n_112,u_Counter_Ctrl_n_113,u_Counter_Ctrl_n_114,u_Counter_Ctrl_n_115,u_Counter_Ctrl_n_116,u_Counter_Ctrl_n_117,u_Counter_Ctrl_n_118}),
        .\min_pulse_width_AXI_1_reg[1] (Relational_Operator1_relop1_3));
  zusys_PWM_and_SS_control_V_0_2_PWM_and_SS_control_V3_ip_src_LimitPulseWidth2 u_LimitPulseWidth2
       (.DI({u_Counter_Ctrl_n_201,u_LimitPulseWidth_n_18,u_LimitPulseWidth_n_19,u_LimitPulseWidth_n_20,u_LimitPulseWidth_n_21,u_LimitPulseWidth_n_22,u_LimitPulseWidth_n_23,u_LimitPulseWidth_n_24}),
        .\Delay2_out1_reg[12] (Relational_Operator_relop1_4),
        .S({u_Counter_Ctrl_n_81,u_Counter_Ctrl_n_82,u_Counter_Ctrl_n_83,u_Counter_Ctrl_n_84,u_Counter_Ctrl_n_85,u_Counter_Ctrl_n_86,u_Counter_Ctrl_n_87,u_LimitPulseWidth_n_57}),
        .Switch9_out12_carry_i_7(u_LimitPulseWidth_n_1),
        .Switch9_out12_carry_i_7_0({u_Counter_Ctrl_n_49,u_Counter_Ctrl_n_50,u_Counter_Ctrl_n_51,u_Counter_Ctrl_n_52,u_Counter_Ctrl_n_53,u_Counter_Ctrl_n_54,u_Counter_Ctrl_n_55}),
        .Switch9_out12_carry_i_7_1({u_Counter_Ctrl_n_58,u_Counter_Ctrl_n_59,u_Counter_Ctrl_n_60,u_Counter_Ctrl_n_61,u_Counter_Ctrl_n_62,u_Counter_Ctrl_n_63,u_Counter_Ctrl_n_64}),
        .\min_pulse_width_AXI_1_reg[1] (Relational_Operator1_relop1_5));
endmodule

module zusys_PWM_and_SS_control_V_0_2_PWM_and_SS_control_V3_ip_src_LimitPulseWidth
   (\min_pulse_width_AXI_1_reg[1] ,
    \min_pulse_width_AXI_1_reg[1]_0 ,
    \Delay_out1_reg[12] ,
    Add_out1,
    \Delay2_out1_reg[13] ,
    DI,
    Saturation_out1,
    \Delay1_out1_reg[13] ,
    \Delay1_out1_reg[10] ,
    \U1_norm_1_reg[13] ,
    \Delay_out1_reg[13] ,
    \Delay_out1_reg[0] ,
    HDL_Counter2_count_reg_11_sp_1,
    \HDL_Counter2_count_reg[11]_0 ,
    \HDL_Counter2_count_reg[16] ,
    HDL_Counter2_count_reg_1_sp_1,
    IPCORE_CLK,
    \T_carrier_us_AXI_1_reg[24] ,
    \min_pulse_width_AXI_1_reg[17] ,
    \min_pulse_width_AXI_1_reg[17]_0 ,
    S,
    Switch7_out12_carry_i_7,
    Switch7_out12_carry_i_7_0,
    Switch7_out12_carry_i_7_1,
    Switch7_out12_carry_i_7_2,
    Q,
    Switch9_out12_carry__0,
    Switch9_out12_carry__0_0,
    Switch9_out12_carry__0_1,
    Allow_assymetrical_anew_reference_value__0,
    Switch9_out12_carry__0_2,
    D,
    Switch8_out12_carry__0,
    Switch8_out12_carry__0_0,
    Switch8_out12_carry__0_1,
    Switch8_out12_carry__0_2,
    Logical_Operator_out10_carry_0,
    Switch7_out12_carry__0,
    Switch7_out12_carry__0_0,
    Logical_Operator_out10_carry_1,
    P,
    HDL_Counter2_count_reg,
    Counter_Ctrl_out4_1_reg,
    Counter_Ctrl_out4_1_reg_0,
    Counter_Ctrl_out4_1_reg_1,
    \Delay_out1[13]_i_2_0 ,
    \Delay_out1[13]_i_2_1 ,
    \Delay_out1[13]_i_2_2 ,
    \Delay_out1[13]_i_2_3 ,
    Counter_Ctrl_out3_1_reg);
  output [0:0]\min_pulse_width_AXI_1_reg[1] ;
  output \min_pulse_width_AXI_1_reg[1]_0 ;
  output [0:0]\Delay_out1_reg[12] ;
  output [13:0]Add_out1;
  output [0:0]\Delay2_out1_reg[13] ;
  output [6:0]DI;
  output [12:0]Saturation_out1;
  output [0:0]\Delay1_out1_reg[13] ;
  output [6:0]\Delay1_out1_reg[10] ;
  output [0:0]\U1_norm_1_reg[13] ;
  output [0:0]\Delay_out1_reg[13] ;
  output [1:0]\Delay_out1_reg[0] ;
  output HDL_Counter2_count_reg_11_sp_1;
  output \HDL_Counter2_count_reg[11]_0 ;
  output \HDL_Counter2_count_reg[16] ;
  output HDL_Counter2_count_reg_1_sp_1;
  output [1:0]IPCORE_CLK;
  output [0:0]\T_carrier_us_AXI_1_reg[24] ;
  output [0:0]\min_pulse_width_AXI_1_reg[17] ;
  output [0:0]\min_pulse_width_AXI_1_reg[17]_0 ;
  input [0:0]S;
  input [0:0]Switch7_out12_carry_i_7;
  input [0:0]Switch7_out12_carry_i_7_0;
  input [6:0]Switch7_out12_carry_i_7_1;
  input [6:0]Switch7_out12_carry_i_7_2;
  input [17:0]Q;
  input [0:0]Switch9_out12_carry__0;
  input [0:0]Switch9_out12_carry__0_0;
  input [6:0]Switch9_out12_carry__0_1;
  input Allow_assymetrical_anew_reference_value__0;
  input [6:0]Switch9_out12_carry__0_2;
  input [5:0]D;
  input [0:0]Switch8_out12_carry__0;
  input [0:0]Switch8_out12_carry__0_0;
  input [6:0]Switch8_out12_carry__0_1;
  input [6:0]Switch8_out12_carry__0_2;
  input [5:0]Logical_Operator_out10_carry_0;
  input [6:0]Switch7_out12_carry__0;
  input [6:0]Switch7_out12_carry__0_0;
  input [5:0]Logical_Operator_out10_carry_1;
  input [5:0]P;
  input [11:0]HDL_Counter2_count_reg;
  input Counter_Ctrl_out4_1_reg;
  input Counter_Ctrl_out4_1_reg_0;
  input Counter_Ctrl_out4_1_reg_1;
  input \Delay_out1[13]_i_2_0 ;
  input \Delay_out1[13]_i_2_1 ;
  input \Delay_out1[13]_i_2_2 ;
  input \Delay_out1[13]_i_2_3 ;
  input [0:0]Counter_Ctrl_out3_1_reg;

  wire [13:0]Add_out1;
  wire Allow_assymetrical_anew_reference_value__0;
  wire [0:0]Counter_Ctrl_out3_1_reg;
  wire Counter_Ctrl_out4_1_i_5_n_0;
  wire Counter_Ctrl_out4_1_i_6_n_0;
  wire Counter_Ctrl_out4_1_i_7_n_0;
  wire Counter_Ctrl_out4_1_reg;
  wire Counter_Ctrl_out4_1_reg_0;
  wire Counter_Ctrl_out4_1_reg_1;
  wire [5:0]D;
  wire [6:0]DI;
  wire [6:0]\Delay1_out1_reg[10] ;
  wire [0:0]\Delay1_out1_reg[13] ;
  wire [0:0]\Delay2_out1_reg[13] ;
  wire \Delay_out1[13]_i_2_0 ;
  wire \Delay_out1[13]_i_2_1 ;
  wire \Delay_out1[13]_i_2_2 ;
  wire \Delay_out1[13]_i_2_3 ;
  wire \Delay_out1[13]_i_3_n_0 ;
  wire \Delay_out1[13]_i_4_n_0 ;
  wire [1:0]\Delay_out1_reg[0] ;
  wire [0:0]\Delay_out1_reg[12] ;
  wire [0:0]\Delay_out1_reg[13] ;
  wire [11:0]HDL_Counter2_count_reg;
  wire \HDL_Counter2_count_reg[11]_0 ;
  wire \HDL_Counter2_count_reg[16] ;
  wire HDL_Counter2_count_reg_11_sn_1;
  wire HDL_Counter2_count_reg_1_sn_1;
  wire [1:0]IPCORE_CLK;
  wire [5:0]Logical_Operator_out10_carry_0;
  wire [5:0]Logical_Operator_out10_carry_1;
  wire Logical_Operator_out10_carry_i_11__1_n_0;
  wire Logical_Operator_out10_carry_i_12__1_n_0;
  wire Logical_Operator_out10_carry_i_13__1_n_0;
  wire Logical_Operator_out10_carry_i_14__1_n_0;
  wire Logical_Operator_out10_carry_i_15__1_n_0;
  wire Logical_Operator_out10_carry_i_16_n_0;
  wire Logical_Operator_out10_carry_i_17_n_0;
  wire Logical_Operator_out10_carry_i_3__1_n_0;
  wire Logical_Operator_out10_carry_i_4__1_n_0;
  wire Logical_Operator_out10_carry_i_5__1_n_0;
  wire Logical_Operator_out10_carry_i_6__1_n_0;
  wire Logical_Operator_out10_carry_i_7__1_n_0;
  wire Logical_Operator_out10_carry_i_8_n_0;
  wire Logical_Operator_out10_carry_i_9__2_n_0;
  wire Logical_Operator_out10_carry_n_1;
  wire Logical_Operator_out10_carry_n_2;
  wire Logical_Operator_out10_carry_n_3;
  wire Logical_Operator_out10_carry_n_4;
  wire Logical_Operator_out10_carry_n_5;
  wire Logical_Operator_out10_carry_n_6;
  wire Logical_Operator_out10_carry_n_7;
  wire \Logical_Operator_out10_inferred__0/i__carry_n_2 ;
  wire \Logical_Operator_out10_inferred__0/i__carry_n_3 ;
  wire \Logical_Operator_out10_inferred__0/i__carry_n_4 ;
  wire \Logical_Operator_out10_inferred__0/i__carry_n_5 ;
  wire \Logical_Operator_out10_inferred__0/i__carry_n_6 ;
  wire \Logical_Operator_out10_inferred__0/i__carry_n_7 ;
  wire Logical_Operator_out1__0;
  wire [5:0]P;
  wire [17:0]Q;
  wire [0:0]S;
  wire [12:0]Saturation_out1;
  wire Saturation_out110_in;
  wire \Saturation_out11_inferred__0/i__carry_n_0 ;
  wire \Saturation_out11_inferred__0/i__carry_n_1 ;
  wire \Saturation_out11_inferred__0/i__carry_n_2 ;
  wire \Saturation_out11_inferred__0/i__carry_n_3 ;
  wire \Saturation_out11_inferred__0/i__carry_n_4 ;
  wire \Saturation_out11_inferred__0/i__carry_n_5 ;
  wire \Saturation_out11_inferred__0/i__carry_n_6 ;
  wire \Saturation_out11_inferred__0/i__carry_n_7 ;
  wire [6:0]Switch7_out12_carry__0;
  wire [6:0]Switch7_out12_carry__0_0;
  wire Switch7_out12_carry_i_17_n_0;
  wire [0:0]Switch7_out12_carry_i_7;
  wire [0:0]Switch7_out12_carry_i_7_0;
  wire [6:0]Switch7_out12_carry_i_7_1;
  wire [6:0]Switch7_out12_carry_i_7_2;
  wire [0:0]Switch8_out12_carry__0;
  wire [0:0]Switch8_out12_carry__0_0;
  wire [6:0]Switch8_out12_carry__0_1;
  wire [6:0]Switch8_out12_carry__0_2;
  wire [0:0]Switch9_out12_carry__0;
  wire [0:0]Switch9_out12_carry__0_0;
  wire [6:0]Switch9_out12_carry__0_1;
  wire [6:0]Switch9_out12_carry__0_2;
  wire [0:0]\T_carrier_us_AXI_1_reg[24] ;
  wire [0:0]\U1_norm_1_reg[13] ;
  wire i__carry_i_10__2_n_0;
  wire i__carry_i_11__2_n_0;
  wire i__carry_i_12__2_n_0;
  wire i__carry_i_13__2_n_0;
  wire i__carry_i_14__2_n_0;
  wire i__carry_i_15_n_0;
  wire i__carry_i_16__0_n_0;
  wire i__carry_i_16__0_n_1;
  wire i__carry_i_16__0_n_2;
  wire i__carry_i_16__0_n_3;
  wire i__carry_i_16__0_n_4;
  wire i__carry_i_16__0_n_5;
  wire i__carry_i_16__0_n_6;
  wire i__carry_i_16__0_n_7;
  wire i__carry_i_16_n_0;
  wire i__carry_i_17_n_0;
  wire i__carry_i_17_n_1;
  wire i__carry_i_17_n_2;
  wire i__carry_i_17_n_3;
  wire i__carry_i_17_n_4;
  wire i__carry_i_17_n_5;
  wire i__carry_i_17_n_6;
  wire i__carry_i_17_n_7;
  wire i__carry_i_18_n_0;
  wire i__carry_i_19_n_0;
  wire i__carry_i_1__2_n_0;
  wire i__carry_i_20_n_0;
  wire i__carry_i_21_n_0;
  wire i__carry_i_22_n_0;
  wire i__carry_i_23_n_0;
  wire i__carry_i_24_n_0;
  wire i__carry_i_25_n_0;
  wire i__carry_i_26_n_0;
  wire i__carry_i_27_n_0;
  wire i__carry_i_28_n_0;
  wire i__carry_i_29_n_0;
  wire i__carry_i_2__2_n_0;
  wire i__carry_i_30_n_0;
  wire i__carry_i_31_n_0;
  wire i__carry_i_32_n_0;
  wire i__carry_i_33_n_0;
  wire i__carry_i_34_n_0;
  wire i__carry_i_35_n_0;
  wire i__carry_i_3__2_n_0;
  wire i__carry_i_4__2_n_0;
  wire i__carry_i_5__2_n_0;
  wire i__carry_i_6__2_n_0;
  wire i__carry_i_7__2_n_0;
  wire i__carry_i_8__2_n_0;
  wire i__carry_i_9__2_n_0;
  wire [0:0]\min_pulse_width_AXI_1_reg[17] ;
  wire [0:0]\min_pulse_width_AXI_1_reg[17]_0 ;
  wire [0:0]\min_pulse_width_AXI_1_reg[1] ;
  wire \min_pulse_width_AXI_1_reg[1]_0 ;
  wire [7:0]NLW_Logical_Operator_out10_carry_O_UNCONNECTED;
  wire [7:7]\NLW_Logical_Operator_out10_inferred__0/i__carry_CO_UNCONNECTED ;
  wire [7:0]\NLW_Logical_Operator_out10_inferred__0/i__carry_O_UNCONNECTED ;
  wire [7:0]\NLW_Saturation_out11_inferred__0/i__carry_O_UNCONNECTED ;
  wire [7:1]\NLW_Saturation_out11_inferred__0/i__carry__0_CO_UNCONNECTED ;
  wire [7:0]\NLW_Saturation_out11_inferred__0/i__carry__0_O_UNCONNECTED ;
  wire [7:0]NLW_i__carry_i_15__0_CO_UNCONNECTED;
  wire [7:1]NLW_i__carry_i_15__0_O_UNCONNECTED;
  wire [2:0]NLW_i__carry_i_17_O_UNCONNECTED;

  assign HDL_Counter2_count_reg_11_sp_1 = HDL_Counter2_count_reg_11_sn_1;
  assign HDL_Counter2_count_reg_1_sp_1 = HDL_Counter2_count_reg_1_sn_1;
  (* SOFT_HLUTNM = "soft_lutpair15" *) 
  LUT4 #(
    .INIT(16'h080A)) 
    Counter_Ctrl_out4_1_i_2
       (.I0(Counter_Ctrl_out4_1_i_5_n_0),
        .I1(HDL_Counter2_count_reg[9]),
        .I2(HDL_Counter2_count_reg[10]),
        .I3(HDL_Counter2_count_reg[8]),
        .O(\HDL_Counter2_count_reg[16] ));
  LUT6 #(
    .INIT(64'h0000000200000000)) 
    Counter_Ctrl_out4_1_i_3
       (.I0(Counter_Ctrl_out4_1_i_6_n_0),
        .I1(HDL_Counter2_count_reg[0]),
        .I2(Counter_Ctrl_out4_1_reg),
        .I3(Counter_Ctrl_out4_1_reg_0),
        .I4(Counter_Ctrl_out4_1_reg_1),
        .I5(Counter_Ctrl_out4_1_i_7_n_0),
        .O(HDL_Counter2_count_reg_1_sn_1));
  LUT6 #(
    .INIT(64'h0000000000000001)) 
    Counter_Ctrl_out4_1_i_4
       (.I0(HDL_Counter2_count_reg[4]),
        .I1(HDL_Counter2_count_reg[6]),
        .I2(HDL_Counter2_count_reg[7]),
        .I3(HDL_Counter2_count_reg[9]),
        .I4(HDL_Counter2_count_reg[11]),
        .I5(HDL_Counter2_count_reg[10]),
        .O(\HDL_Counter2_count_reg[11]_0 ));
  LUT6 #(
    .INIT(64'h0000230000002323)) 
    Counter_Ctrl_out4_1_i_5
       (.I0(HDL_Counter2_count_reg[6]),
        .I1(HDL_Counter2_count_reg[7]),
        .I2(HDL_Counter2_count_reg[5]),
        .I3(HDL_Counter2_count_reg[3]),
        .I4(HDL_Counter2_count_reg[4]),
        .I5(HDL_Counter2_count_reg[2]),
        .O(Counter_Ctrl_out4_1_i_5_n_0));
  LUT4 #(
    .INIT(16'h0001)) 
    Counter_Ctrl_out4_1_i_6
       (.I0(HDL_Counter2_count_reg[3]),
        .I1(HDL_Counter2_count_reg[1]),
        .I2(\Delay_out1[13]_i_2_0 ),
        .I3(\Delay_out1[13]_i_2_2 ),
        .O(Counter_Ctrl_out4_1_i_6_n_0));
  LUT6 #(
    .INIT(64'h0000230000002323)) 
    Counter_Ctrl_out4_1_i_7
       (.I0(\Delay_out1[13]_i_2_0 ),
        .I1(HDL_Counter2_count_reg[1]),
        .I2(\Delay_out1[13]_i_2_1 ),
        .I3(Counter_Ctrl_out4_1_reg_0),
        .I4(\Delay_out1[13]_i_2_2 ),
        .I5(\Delay_out1[13]_i_2_3 ),
        .O(Counter_Ctrl_out4_1_i_7_n_0));
  LUT6 #(
    .INIT(64'h8000000000000000)) 
    \Delay_out1[13]_i_2 
       (.I0(\HDL_Counter2_count_reg[11]_0 ),
        .I1(Counter_Ctrl_out4_1_i_6_n_0),
        .I2(\Delay_out1[13]_i_3_n_0 ),
        .I3(Counter_Ctrl_out4_1_i_7_n_0),
        .I4(\Delay_out1[13]_i_4_n_0 ),
        .I5(Counter_Ctrl_out4_1_i_5_n_0),
        .O(HDL_Counter2_count_reg_11_sn_1));
  LUT4 #(
    .INIT(16'h0001)) 
    \Delay_out1[13]_i_3 
       (.I0(HDL_Counter2_count_reg[0]),
        .I1(Counter_Ctrl_out4_1_reg),
        .I2(Counter_Ctrl_out4_1_reg_0),
        .I3(Counter_Ctrl_out4_1_reg_1),
        .O(\Delay_out1[13]_i_3_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair15" *) 
  LUT3 #(
    .INIT(8'h31)) 
    \Delay_out1[13]_i_4 
       (.I0(HDL_Counter2_count_reg[8]),
        .I1(HDL_Counter2_count_reg[10]),
        .I2(HDL_Counter2_count_reg[9]),
        .O(\Delay_out1[13]_i_4_n_0 ));
  (* COMPARATOR_THRESHOLD = "11" *) 
  CARRY8 Logical_Operator_out10_carry
       (.CI(\min_pulse_width_AXI_1_reg[1]_0 ),
        .CI_TOP(1'b0),
        .CO({\min_pulse_width_AXI_1_reg[1] ,Logical_Operator_out10_carry_n_1,Logical_Operator_out10_carry_n_2,Logical_Operator_out10_carry_n_3,Logical_Operator_out10_carry_n_4,Logical_Operator_out10_carry_n_5,Logical_Operator_out10_carry_n_6,Logical_Operator_out10_carry_n_7}),
        .DI({Switch7_out12_carry_i_7,Logical_Operator_out10_carry_i_3__1_n_0,Logical_Operator_out10_carry_i_4__1_n_0,Logical_Operator_out10_carry_i_5__1_n_0,Logical_Operator_out10_carry_i_6__1_n_0,Logical_Operator_out10_carry_i_7__1_n_0,Logical_Operator_out10_carry_i_8_n_0,Logical_Operator_out10_carry_i_9__2_n_0}),
        .O(NLW_Logical_Operator_out10_carry_O_UNCONNECTED[7:0]),
        .S({Switch7_out12_carry_i_7_0,Logical_Operator_out10_carry_i_11__1_n_0,Logical_Operator_out10_carry_i_12__1_n_0,Logical_Operator_out10_carry_i_13__1_n_0,Logical_Operator_out10_carry_i_14__1_n_0,Logical_Operator_out10_carry_i_15__1_n_0,Logical_Operator_out10_carry_i_16_n_0,Logical_Operator_out10_carry_i_17_n_0}));
  LUT6 #(
    .INIT(64'hA95900000000A959)) 
    Logical_Operator_out10_carry_i_11__1
       (.I0(Saturation_out1[10]),
        .I1(Switch7_out12_carry__0_0[5]),
        .I2(Allow_assymetrical_anew_reference_value__0),
        .I3(Switch7_out12_carry__0[5]),
        .I4(Logical_Operator_out10_carry_1[5]),
        .I5(Saturation_out1[11]),
        .O(Logical_Operator_out10_carry_i_11__1_n_0));
  LUT6 #(
    .INIT(64'hA95900000000A959)) 
    Logical_Operator_out10_carry_i_12__1
       (.I0(Saturation_out1[8]),
        .I1(Switch7_out12_carry__0_0[4]),
        .I2(Allow_assymetrical_anew_reference_value__0),
        .I3(Switch7_out12_carry__0[4]),
        .I4(Logical_Operator_out10_carry_1[4]),
        .I5(Saturation_out1[9]),
        .O(Logical_Operator_out10_carry_i_12__1_n_0));
  LUT6 #(
    .INIT(64'hA95900000000A959)) 
    Logical_Operator_out10_carry_i_13__1
       (.I0(Saturation_out1[6]),
        .I1(Switch7_out12_carry__0_0[3]),
        .I2(Allow_assymetrical_anew_reference_value__0),
        .I3(Switch7_out12_carry__0[3]),
        .I4(Logical_Operator_out10_carry_1[3]),
        .I5(Saturation_out1[7]),
        .O(Logical_Operator_out10_carry_i_13__1_n_0));
  LUT6 #(
    .INIT(64'hA95900000000A959)) 
    Logical_Operator_out10_carry_i_14__1
       (.I0(Saturation_out1[4]),
        .I1(Switch7_out12_carry__0_0[2]),
        .I2(Allow_assymetrical_anew_reference_value__0),
        .I3(Switch7_out12_carry__0[2]),
        .I4(Logical_Operator_out10_carry_1[2]),
        .I5(Saturation_out1[5]),
        .O(Logical_Operator_out10_carry_i_14__1_n_0));
  LUT6 #(
    .INIT(64'hA95900000000A959)) 
    Logical_Operator_out10_carry_i_15__1
       (.I0(Saturation_out1[2]),
        .I1(Switch7_out12_carry__0_0[1]),
        .I2(Allow_assymetrical_anew_reference_value__0),
        .I3(Switch7_out12_carry__0[1]),
        .I4(Logical_Operator_out10_carry_1[1]),
        .I5(Saturation_out1[3]),
        .O(Logical_Operator_out10_carry_i_15__1_n_0));
  LUT6 #(
    .INIT(64'hA95900000000A959)) 
    Logical_Operator_out10_carry_i_16
       (.I0(Saturation_out1[0]),
        .I1(Switch7_out12_carry__0_0[0]),
        .I2(Allow_assymetrical_anew_reference_value__0),
        .I3(Switch7_out12_carry__0[0]),
        .I4(Logical_Operator_out10_carry_1[0]),
        .I5(Saturation_out1[1]),
        .O(Logical_Operator_out10_carry_i_16_n_0));
  LUT4 #(
    .INIT(16'hEEEF)) 
    Logical_Operator_out10_carry_i_16__1
       (.I0(Q[17]),
        .I1(Saturation_out110_in),
        .I2(Q[3]),
        .I3(Q[2]),
        .O(\min_pulse_width_AXI_1_reg[17] ));
  LUT4 #(
    .INIT(16'hEEEF)) 
    Logical_Operator_out10_carry_i_16__2
       (.I0(Q[17]),
        .I1(Saturation_out110_in),
        .I2(Q[3]),
        .I3(Q[2]),
        .O(\min_pulse_width_AXI_1_reg[17]_0 ));
  LUT4 #(
    .INIT(16'hEEEF)) 
    Logical_Operator_out10_carry_i_17
       (.I0(Q[17]),
        .I1(Saturation_out110_in),
        .I2(Q[3]),
        .I3(Q[2]),
        .O(Logical_Operator_out10_carry_i_17_n_0));
  (* SOFT_HLUTNM = "soft_lutpair16" *) 
  LUT3 #(
    .INIT(8'hF2)) 
    Logical_Operator_out10_carry_i_18
       (.I0(Q[16]),
        .I1(Q[17]),
        .I2(Saturation_out110_in),
        .O(Saturation_out1[12]));
  LUT4 #(
    .INIT(16'h000E)) 
    Logical_Operator_out10_carry_i_1__2
       (.I0(Q[1]),
        .I1(Q[0]),
        .I2(Q[17]),
        .I3(Saturation_out110_in),
        .O(\min_pulse_width_AXI_1_reg[1]_0 ));
  LUT6 #(
    .INIT(64'h222222B2B2B222B2)) 
    Logical_Operator_out10_carry_i_2
       (.I0(Saturation_out1[11]),
        .I1(D[5]),
        .I2(Saturation_out1[10]),
        .I3(Switch9_out12_carry__0_1[5]),
        .I4(Allow_assymetrical_anew_reference_value__0),
        .I5(Switch9_out12_carry__0_2[5]),
        .O(DI[6]));
  (* SOFT_HLUTNM = "soft_lutpair18" *) 
  LUT3 #(
    .INIT(8'h02)) 
    Logical_Operator_out10_carry_i_20
       (.I0(Q[15]),
        .I1(Q[17]),
        .I2(Saturation_out110_in),
        .O(Saturation_out1[11]));
  (* SOFT_HLUTNM = "soft_lutpair16" *) 
  LUT3 #(
    .INIT(8'h02)) 
    Logical_Operator_out10_carry_i_21
       (.I0(Q[14]),
        .I1(Q[17]),
        .I2(Saturation_out110_in),
        .O(Saturation_out1[10]));
  (* SOFT_HLUTNM = "soft_lutpair19" *) 
  LUT3 #(
    .INIT(8'h02)) 
    Logical_Operator_out10_carry_i_22
       (.I0(Q[13]),
        .I1(Q[17]),
        .I2(Saturation_out110_in),
        .O(Saturation_out1[9]));
  (* SOFT_HLUTNM = "soft_lutpair18" *) 
  LUT3 #(
    .INIT(8'h02)) 
    Logical_Operator_out10_carry_i_23
       (.I0(Q[12]),
        .I1(Q[17]),
        .I2(Saturation_out110_in),
        .O(Saturation_out1[8]));
  (* SOFT_HLUTNM = "soft_lutpair20" *) 
  LUT3 #(
    .INIT(8'h02)) 
    Logical_Operator_out10_carry_i_24
       (.I0(Q[11]),
        .I1(Q[17]),
        .I2(Saturation_out110_in),
        .O(Saturation_out1[7]));
  (* SOFT_HLUTNM = "soft_lutpair19" *) 
  LUT3 #(
    .INIT(8'h02)) 
    Logical_Operator_out10_carry_i_25
       (.I0(Q[10]),
        .I1(Q[17]),
        .I2(Saturation_out110_in),
        .O(Saturation_out1[6]));
  (* SOFT_HLUTNM = "soft_lutpair21" *) 
  LUT3 #(
    .INIT(8'h02)) 
    Logical_Operator_out10_carry_i_26
       (.I0(Q[9]),
        .I1(Q[17]),
        .I2(Saturation_out110_in),
        .O(Saturation_out1[5]));
  (* SOFT_HLUTNM = "soft_lutpair20" *) 
  LUT3 #(
    .INIT(8'h02)) 
    Logical_Operator_out10_carry_i_27
       (.I0(Q[8]),
        .I1(Q[17]),
        .I2(Saturation_out110_in),
        .O(Saturation_out1[4]));
  (* SOFT_HLUTNM = "soft_lutpair22" *) 
  LUT3 #(
    .INIT(8'h02)) 
    Logical_Operator_out10_carry_i_28
       (.I0(Q[7]),
        .I1(Q[17]),
        .I2(Saturation_out110_in),
        .O(Saturation_out1[3]));
  (* SOFT_HLUTNM = "soft_lutpair21" *) 
  LUT3 #(
    .INIT(8'h02)) 
    Logical_Operator_out10_carry_i_29
       (.I0(Q[6]),
        .I1(Q[17]),
        .I2(Saturation_out110_in),
        .O(Saturation_out1[2]));
  LUT6 #(
    .INIT(64'h222222B2B2B222B2)) 
    Logical_Operator_out10_carry_i_2__0
       (.I0(Saturation_out1[11]),
        .I1(Logical_Operator_out10_carry_0[5]),
        .I2(Saturation_out1[10]),
        .I3(Switch8_out12_carry__0_1[5]),
        .I4(Allow_assymetrical_anew_reference_value__0),
        .I5(Switch8_out12_carry__0_2[5]),
        .O(\Delay1_out1_reg[10] [6]));
  LUT6 #(
    .INIT(64'h222222B2B2B222B2)) 
    Logical_Operator_out10_carry_i_3
       (.I0(Saturation_out1[9]),
        .I1(D[4]),
        .I2(Saturation_out1[8]),
        .I3(Switch9_out12_carry__0_1[4]),
        .I4(Allow_assymetrical_anew_reference_value__0),
        .I5(Switch9_out12_carry__0_2[4]),
        .O(DI[5]));
  LUT3 #(
    .INIT(8'h02)) 
    Logical_Operator_out10_carry_i_30
       (.I0(Q[5]),
        .I1(Q[17]),
        .I2(Saturation_out110_in),
        .O(Saturation_out1[1]));
  (* SOFT_HLUTNM = "soft_lutpair22" *) 
  LUT3 #(
    .INIT(8'h02)) 
    Logical_Operator_out10_carry_i_31
       (.I0(Q[4]),
        .I1(Q[17]),
        .I2(Saturation_out110_in),
        .O(Saturation_out1[0]));
  LUT6 #(
    .INIT(64'h222222B2B2B222B2)) 
    Logical_Operator_out10_carry_i_3__0
       (.I0(Saturation_out1[9]),
        .I1(Logical_Operator_out10_carry_0[4]),
        .I2(Saturation_out1[8]),
        .I3(Switch8_out12_carry__0_1[4]),
        .I4(Allow_assymetrical_anew_reference_value__0),
        .I5(Switch8_out12_carry__0_2[4]),
        .O(\Delay1_out1_reg[10] [5]));
  LUT6 #(
    .INIT(64'h222222B2B2B222B2)) 
    Logical_Operator_out10_carry_i_3__1
       (.I0(Saturation_out1[11]),
        .I1(Logical_Operator_out10_carry_1[5]),
        .I2(Saturation_out1[10]),
        .I3(Switch7_out12_carry__0_0[5]),
        .I4(Allow_assymetrical_anew_reference_value__0),
        .I5(Switch7_out12_carry__0[5]),
        .O(Logical_Operator_out10_carry_i_3__1_n_0));
  LUT6 #(
    .INIT(64'h222222B2B2B222B2)) 
    Logical_Operator_out10_carry_i_4
       (.I0(Saturation_out1[7]),
        .I1(D[3]),
        .I2(Saturation_out1[6]),
        .I3(Switch9_out12_carry__0_1[3]),
        .I4(Allow_assymetrical_anew_reference_value__0),
        .I5(Switch9_out12_carry__0_2[3]),
        .O(DI[4]));
  LUT6 #(
    .INIT(64'h222222B2B2B222B2)) 
    Logical_Operator_out10_carry_i_4__0
       (.I0(Saturation_out1[7]),
        .I1(Logical_Operator_out10_carry_0[3]),
        .I2(Saturation_out1[6]),
        .I3(Switch8_out12_carry__0_1[3]),
        .I4(Allow_assymetrical_anew_reference_value__0),
        .I5(Switch8_out12_carry__0_2[3]),
        .O(\Delay1_out1_reg[10] [4]));
  LUT6 #(
    .INIT(64'h222222B2B2B222B2)) 
    Logical_Operator_out10_carry_i_4__1
       (.I0(Saturation_out1[9]),
        .I1(Logical_Operator_out10_carry_1[4]),
        .I2(Saturation_out1[8]),
        .I3(Switch7_out12_carry__0_0[4]),
        .I4(Allow_assymetrical_anew_reference_value__0),
        .I5(Switch7_out12_carry__0[4]),
        .O(Logical_Operator_out10_carry_i_4__1_n_0));
  LUT6 #(
    .INIT(64'h222222B2B2B222B2)) 
    Logical_Operator_out10_carry_i_5
       (.I0(Saturation_out1[5]),
        .I1(D[2]),
        .I2(Saturation_out1[4]),
        .I3(Switch9_out12_carry__0_1[2]),
        .I4(Allow_assymetrical_anew_reference_value__0),
        .I5(Switch9_out12_carry__0_2[2]),
        .O(DI[3]));
  LUT6 #(
    .INIT(64'h222222B2B2B222B2)) 
    Logical_Operator_out10_carry_i_5__0
       (.I0(Saturation_out1[5]),
        .I1(Logical_Operator_out10_carry_0[2]),
        .I2(Saturation_out1[4]),
        .I3(Switch8_out12_carry__0_1[2]),
        .I4(Allow_assymetrical_anew_reference_value__0),
        .I5(Switch8_out12_carry__0_2[2]),
        .O(\Delay1_out1_reg[10] [3]));
  LUT6 #(
    .INIT(64'h222222B2B2B222B2)) 
    Logical_Operator_out10_carry_i_5__1
       (.I0(Saturation_out1[7]),
        .I1(Logical_Operator_out10_carry_1[3]),
        .I2(Saturation_out1[6]),
        .I3(Switch7_out12_carry__0_0[3]),
        .I4(Allow_assymetrical_anew_reference_value__0),
        .I5(Switch7_out12_carry__0[3]),
        .O(Logical_Operator_out10_carry_i_5__1_n_0));
  LUT6 #(
    .INIT(64'h222222B2B2B222B2)) 
    Logical_Operator_out10_carry_i_6
       (.I0(Saturation_out1[3]),
        .I1(D[1]),
        .I2(Saturation_out1[2]),
        .I3(Switch9_out12_carry__0_1[1]),
        .I4(Allow_assymetrical_anew_reference_value__0),
        .I5(Switch9_out12_carry__0_2[1]),
        .O(DI[2]));
  LUT6 #(
    .INIT(64'h222222B2B2B222B2)) 
    Logical_Operator_out10_carry_i_6__0
       (.I0(Saturation_out1[3]),
        .I1(Logical_Operator_out10_carry_0[1]),
        .I2(Saturation_out1[2]),
        .I3(Switch8_out12_carry__0_1[1]),
        .I4(Allow_assymetrical_anew_reference_value__0),
        .I5(Switch8_out12_carry__0_2[1]),
        .O(\Delay1_out1_reg[10] [2]));
  LUT6 #(
    .INIT(64'h222222B2B2B222B2)) 
    Logical_Operator_out10_carry_i_6__1
       (.I0(Saturation_out1[5]),
        .I1(Logical_Operator_out10_carry_1[2]),
        .I2(Saturation_out1[4]),
        .I3(Switch7_out12_carry__0_0[2]),
        .I4(Allow_assymetrical_anew_reference_value__0),
        .I5(Switch7_out12_carry__0[2]),
        .O(Logical_Operator_out10_carry_i_6__1_n_0));
  LUT6 #(
    .INIT(64'h222222B2B2B222B2)) 
    Logical_Operator_out10_carry_i_7
       (.I0(Saturation_out1[1]),
        .I1(D[0]),
        .I2(Saturation_out1[0]),
        .I3(Switch9_out12_carry__0_1[0]),
        .I4(Allow_assymetrical_anew_reference_value__0),
        .I5(Switch9_out12_carry__0_2[0]),
        .O(DI[1]));
  LUT6 #(
    .INIT(64'h222222B2B2B222B2)) 
    Logical_Operator_out10_carry_i_7__0
       (.I0(Saturation_out1[1]),
        .I1(Logical_Operator_out10_carry_0[0]),
        .I2(Saturation_out1[0]),
        .I3(Switch8_out12_carry__0_1[0]),
        .I4(Allow_assymetrical_anew_reference_value__0),
        .I5(Switch8_out12_carry__0_2[0]),
        .O(\Delay1_out1_reg[10] [1]));
  LUT6 #(
    .INIT(64'h222222B2B2B222B2)) 
    Logical_Operator_out10_carry_i_7__1
       (.I0(Saturation_out1[3]),
        .I1(Logical_Operator_out10_carry_1[1]),
        .I2(Saturation_out1[2]),
        .I3(Switch7_out12_carry__0_0[1]),
        .I4(Allow_assymetrical_anew_reference_value__0),
        .I5(Switch7_out12_carry__0[1]),
        .O(Logical_Operator_out10_carry_i_7__1_n_0));
  LUT6 #(
    .INIT(64'h222222B2B2B222B2)) 
    Logical_Operator_out10_carry_i_8
       (.I0(Saturation_out1[1]),
        .I1(Logical_Operator_out10_carry_1[0]),
        .I2(Saturation_out1[0]),
        .I3(Switch7_out12_carry__0_0[0]),
        .I4(Allow_assymetrical_anew_reference_value__0),
        .I5(Switch7_out12_carry__0[0]),
        .O(Logical_Operator_out10_carry_i_8_n_0));
  LUT4 #(
    .INIT(16'h000E)) 
    Logical_Operator_out10_carry_i_8__1
       (.I0(Q[2]),
        .I1(Q[3]),
        .I2(Saturation_out110_in),
        .I3(Q[17]),
        .O(DI[0]));
  LUT4 #(
    .INIT(16'h000E)) 
    Logical_Operator_out10_carry_i_8__2
       (.I0(Q[2]),
        .I1(Q[3]),
        .I2(Saturation_out110_in),
        .I3(Q[17]),
        .O(\Delay1_out1_reg[10] [0]));
  LUT4 #(
    .INIT(16'h000E)) 
    Logical_Operator_out10_carry_i_9__2
       (.I0(Q[2]),
        .I1(Q[3]),
        .I2(Saturation_out110_in),
        .I3(Q[17]),
        .O(Logical_Operator_out10_carry_i_9__2_n_0));
  (* COMPARATOR_THRESHOLD = "11" *) 
  CARRY8 \Logical_Operator_out10_inferred__0/i__carry 
       (.CI(1'b0),
        .CI_TOP(1'b0),
        .CO({\NLW_Logical_Operator_out10_inferred__0/i__carry_CO_UNCONNECTED [7],\Delay_out1_reg[12] ,\Logical_Operator_out10_inferred__0/i__carry_n_2 ,\Logical_Operator_out10_inferred__0/i__carry_n_3 ,\Logical_Operator_out10_inferred__0/i__carry_n_4 ,\Logical_Operator_out10_inferred__0/i__carry_n_5 ,\Logical_Operator_out10_inferred__0/i__carry_n_6 ,\Logical_Operator_out10_inferred__0/i__carry_n_7 }),
        .DI({1'b0,Switch7_out12_carry_i_7_1}),
        .O(\NLW_Logical_Operator_out10_inferred__0/i__carry_O_UNCONNECTED [7:0]),
        .S({1'b0,Switch7_out12_carry_i_7_2}));
  LUT1 #(
    .INIT(2'h1)) 
    Period_CenterMax0_carry__0_i_1
       (.I0(Counter_Ctrl_out3_1_reg),
        .O(\T_carrier_us_AXI_1_reg[24] ));
  (* COMPARATOR_THRESHOLD = "11" *) 
  CARRY8 \Saturation_out11_inferred__0/i__carry 
       (.CI(1'b0),
        .CI_TOP(1'b0),
        .CO({\Saturation_out11_inferred__0/i__carry_n_0 ,\Saturation_out11_inferred__0/i__carry_n_1 ,\Saturation_out11_inferred__0/i__carry_n_2 ,\Saturation_out11_inferred__0/i__carry_n_3 ,\Saturation_out11_inferred__0/i__carry_n_4 ,\Saturation_out11_inferred__0/i__carry_n_5 ,\Saturation_out11_inferred__0/i__carry_n_6 ,\Saturation_out11_inferred__0/i__carry_n_7 }),
        .DI({i__carry_i_1__2_n_0,i__carry_i_2__2_n_0,i__carry_i_3__2_n_0,i__carry_i_4__2_n_0,i__carry_i_5__2_n_0,i__carry_i_6__2_n_0,i__carry_i_7__2_n_0,i__carry_i_8__2_n_0}),
        .O(\NLW_Saturation_out11_inferred__0/i__carry_O_UNCONNECTED [7:0]),
        .S({i__carry_i_9__2_n_0,i__carry_i_10__2_n_0,i__carry_i_11__2_n_0,i__carry_i_12__2_n_0,i__carry_i_13__2_n_0,i__carry_i_14__2_n_0,i__carry_i_15_n_0,i__carry_i_16_n_0}));
  (* COMPARATOR_THRESHOLD = "11" *) 
  CARRY8 \Saturation_out11_inferred__0/i__carry__0 
       (.CI(\Saturation_out11_inferred__0/i__carry_n_0 ),
        .CI_TOP(1'b0),
        .CO({\NLW_Saturation_out11_inferred__0/i__carry__0_CO_UNCONNECTED [7:1],Saturation_out110_in}),
        .DI({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .O(\NLW_Saturation_out11_inferred__0/i__carry__0_O_UNCONNECTED [7:0]),
        .S({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,S}));
  LUT5 #(
    .INIT(32'h000000B8)) 
    Switch7_out12_carry__0_i_1
       (.I0(Switch7_out12_carry__0[6]),
        .I1(Allow_assymetrical_anew_reference_value__0),
        .I2(Switch7_out12_carry__0_0[6]),
        .I3(\Delay_out1_reg[12] ),
        .I4(\min_pulse_width_AXI_1_reg[1] ),
        .O(\U1_norm_1_reg[13] ));
  LUT5 #(
    .INIT(32'hEEEFFFEF)) 
    Switch7_out12_carry__0_i_3
       (.I0(\min_pulse_width_AXI_1_reg[1] ),
        .I1(\Delay_out1_reg[12] ),
        .I2(Switch7_out12_carry__0_0[6]),
        .I3(Allow_assymetrical_anew_reference_value__0),
        .I4(Switch7_out12_carry__0[6]),
        .O(\Delay_out1_reg[13] ));
  LUT4 #(
    .INIT(16'h200D)) 
    Switch7_out12_carry_i_15
       (.I0(\Delay_out1_reg[12] ),
        .I1(\min_pulse_width_AXI_1_reg[1] ),
        .I2(P[2]),
        .I3(P[3]),
        .O(IPCORE_CLK[1]));
  LUT4 #(
    .INIT(16'h020D)) 
    Switch7_out12_carry_i_16
       (.I0(\Delay_out1_reg[12] ),
        .I1(\min_pulse_width_AXI_1_reg[1] ),
        .I2(P[0]),
        .I3(P[1]),
        .O(IPCORE_CLK[0]));
  (* SOFT_HLUTNM = "soft_lutpair17" *) 
  LUT3 #(
    .INIT(8'h8A)) 
    Switch7_out12_carry_i_17
       (.I0(P[4]),
        .I1(\min_pulse_width_AXI_1_reg[1] ),
        .I2(\Delay_out1_reg[12] ),
        .O(Switch7_out12_carry_i_17_n_0));
  (* SOFT_HLUTNM = "soft_lutpair17" *) 
  LUT2 #(
    .INIT(4'hE)) 
    Switch7_out12_carry_i_18
       (.I0(\Delay_out1_reg[12] ),
        .I1(\min_pulse_width_AXI_1_reg[1] ),
        .O(Logical_Operator_out1__0));
  LUT6 #(
    .INIT(64'hE8E8E8EEEEEEE8EE)) 
    Switch7_out12_carry_i_6
       (.I0(Switch7_out12_carry_i_17_n_0),
        .I1(P[5]),
        .I2(Logical_Operator_out1__0),
        .I3(Switch7_out12_carry__0_0[0]),
        .I4(Allow_assymetrical_anew_reference_value__0),
        .I5(Switch7_out12_carry__0[0]),
        .O(\Delay_out1_reg[0] [1]));
  LUT4 #(
    .INIT(16'hFDD0)) 
    Switch7_out12_carry_i_8
       (.I0(\Delay_out1_reg[12] ),
        .I1(\min_pulse_width_AXI_1_reg[1] ),
        .I2(P[0]),
        .I3(P[1]),
        .O(\Delay_out1_reg[0] [0]));
  LUT5 #(
    .INIT(32'hEEEFFFEF)) 
    Switch8_out12_carry__0_i_3
       (.I0(Switch8_out12_carry__0),
        .I1(Switch8_out12_carry__0_0),
        .I2(Switch8_out12_carry__0_1[6]),
        .I3(Allow_assymetrical_anew_reference_value__0),
        .I4(Switch8_out12_carry__0_2[6]),
        .O(\Delay1_out1_reg[13] ));
  LUT5 #(
    .INIT(32'hEEEFFFEF)) 
    Switch9_out12_carry__0_i_3
       (.I0(Switch9_out12_carry__0),
        .I1(Switch9_out12_carry__0_0),
        .I2(Switch9_out12_carry__0_1[6]),
        .I3(Allow_assymetrical_anew_reference_value__0),
        .I4(Switch9_out12_carry__0_2[6]),
        .O(\Delay2_out1_reg[13] ));
  LUT2 #(
    .INIT(4'h1)) 
    i__carry_i_10__2
       (.I0(Q[13]),
        .I1(Q[12]),
        .O(i__carry_i_10__2_n_0));
  LUT2 #(
    .INIT(4'h1)) 
    i__carry_i_11__2
       (.I0(Q[11]),
        .I1(Q[10]),
        .O(i__carry_i_11__2_n_0));
  LUT2 #(
    .INIT(4'h1)) 
    i__carry_i_12__2
       (.I0(Q[9]),
        .I1(Q[8]),
        .O(i__carry_i_12__2_n_0));
  LUT2 #(
    .INIT(4'h1)) 
    i__carry_i_13__2
       (.I0(Q[7]),
        .I1(Q[6]),
        .O(i__carry_i_13__2_n_0));
  LUT2 #(
    .INIT(4'h1)) 
    i__carry_i_14__2
       (.I0(Q[5]),
        .I1(Q[4]),
        .O(i__carry_i_14__2_n_0));
  LUT2 #(
    .INIT(4'h1)) 
    i__carry_i_15
       (.I0(Q[3]),
        .I1(Q[2]),
        .O(i__carry_i_15_n_0));
  (* ADDER_THRESHOLD = "35" *) 
  CARRY8 i__carry_i_15__0
       (.CI(i__carry_i_16__0_n_0),
        .CI_TOP(1'b0),
        .CO(NLW_i__carry_i_15__0_CO_UNCONNECTED[7:0]),
        .DI({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .O({NLW_i__carry_i_15__0_O_UNCONNECTED[7:1],Add_out1[13]}),
        .S({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,i__carry_i_18_n_0}));
  LUT2 #(
    .INIT(4'h1)) 
    i__carry_i_16
       (.I0(Q[1]),
        .I1(Q[0]),
        .O(i__carry_i_16_n_0));
  (* ADDER_THRESHOLD = "35" *) 
  CARRY8 i__carry_i_16__0
       (.CI(i__carry_i_17_n_0),
        .CI_TOP(1'b0),
        .CO({i__carry_i_16__0_n_0,i__carry_i_16__0_n_1,i__carry_i_16__0_n_2,i__carry_i_16__0_n_3,i__carry_i_16__0_n_4,i__carry_i_16__0_n_5,i__carry_i_16__0_n_6,i__carry_i_16__0_n_7}),
        .DI({i__carry_i_19_n_0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .O(Add_out1[12:5]),
        .S({Q[16],i__carry_i_20_n_0,i__carry_i_21_n_0,i__carry_i_22_n_0,i__carry_i_23_n_0,i__carry_i_24_n_0,i__carry_i_25_n_0,i__carry_i_26_n_0}));
  (* ADDER_THRESHOLD = "35" *) 
  CARRY8 i__carry_i_17
       (.CI(i__carry_i_27_n_0),
        .CI_TOP(1'b0),
        .CO({i__carry_i_17_n_0,i__carry_i_17_n_1,i__carry_i_17_n_2,i__carry_i_17_n_3,i__carry_i_17_n_4,i__carry_i_17_n_5,i__carry_i_17_n_6,i__carry_i_17_n_7}),
        .DI({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .O({Add_out1[4:0],NLW_i__carry_i_17_O_UNCONNECTED[2:0]}),
        .S({i__carry_i_28_n_0,i__carry_i_29_n_0,i__carry_i_30_n_0,i__carry_i_31_n_0,i__carry_i_32_n_0,i__carry_i_33_n_0,i__carry_i_34_n_0,i__carry_i_35_n_0}));
  LUT1 #(
    .INIT(2'h1)) 
    i__carry_i_18
       (.I0(Q[17]),
        .O(i__carry_i_18_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    i__carry_i_19
       (.I0(Q[16]),
        .O(i__carry_i_19_n_0));
  LUT2 #(
    .INIT(4'hE)) 
    i__carry_i_1__2
       (.I0(Q[14]),
        .I1(Q[15]),
        .O(i__carry_i_1__2_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    i__carry_i_20
       (.I0(Q[15]),
        .O(i__carry_i_20_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    i__carry_i_21
       (.I0(Q[14]),
        .O(i__carry_i_21_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    i__carry_i_22
       (.I0(Q[13]),
        .O(i__carry_i_22_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    i__carry_i_23
       (.I0(Q[12]),
        .O(i__carry_i_23_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    i__carry_i_24
       (.I0(Q[11]),
        .O(i__carry_i_24_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    i__carry_i_25
       (.I0(Q[10]),
        .O(i__carry_i_25_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    i__carry_i_26
       (.I0(Q[9]),
        .O(i__carry_i_26_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    i__carry_i_27
       (.I0(Q[0]),
        .O(i__carry_i_27_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    i__carry_i_28
       (.I0(Q[8]),
        .O(i__carry_i_28_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    i__carry_i_29
       (.I0(Q[7]),
        .O(i__carry_i_29_n_0));
  LUT2 #(
    .INIT(4'hE)) 
    i__carry_i_2__2
       (.I0(Q[12]),
        .I1(Q[13]),
        .O(i__carry_i_2__2_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    i__carry_i_30
       (.I0(Q[6]),
        .O(i__carry_i_30_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    i__carry_i_31
       (.I0(Q[5]),
        .O(i__carry_i_31_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    i__carry_i_32
       (.I0(Q[4]),
        .O(i__carry_i_32_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    i__carry_i_33
       (.I0(Q[3]),
        .O(i__carry_i_33_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    i__carry_i_34
       (.I0(Q[2]),
        .O(i__carry_i_34_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    i__carry_i_35
       (.I0(Q[1]),
        .O(i__carry_i_35_n_0));
  LUT2 #(
    .INIT(4'hE)) 
    i__carry_i_3__2
       (.I0(Q[10]),
        .I1(Q[11]),
        .O(i__carry_i_3__2_n_0));
  LUT2 #(
    .INIT(4'hE)) 
    i__carry_i_4__2
       (.I0(Q[8]),
        .I1(Q[9]),
        .O(i__carry_i_4__2_n_0));
  LUT2 #(
    .INIT(4'hE)) 
    i__carry_i_5__2
       (.I0(Q[6]),
        .I1(Q[7]),
        .O(i__carry_i_5__2_n_0));
  LUT2 #(
    .INIT(4'hE)) 
    i__carry_i_6__2
       (.I0(Q[4]),
        .I1(Q[5]),
        .O(i__carry_i_6__2_n_0));
  LUT2 #(
    .INIT(4'hE)) 
    i__carry_i_7__2
       (.I0(Q[2]),
        .I1(Q[3]),
        .O(i__carry_i_7__2_n_0));
  LUT2 #(
    .INIT(4'hE)) 
    i__carry_i_8__2
       (.I0(Q[0]),
        .I1(Q[1]),
        .O(i__carry_i_8__2_n_0));
  LUT2 #(
    .INIT(4'h1)) 
    i__carry_i_9__2
       (.I0(Q[15]),
        .I1(Q[14]),
        .O(i__carry_i_9__2_n_0));
endmodule

module zusys_PWM_and_SS_control_V_0_2_PWM_and_SS_control_V3_ip_src_LimitPulseWidth1
   (\min_pulse_width_AXI_1_reg[1] ,
    \Delay1_out1_reg[12] ,
    Switch8_out12_carry_i_7,
    DI,
    S,
    Switch8_out12_carry_i_7_0,
    Switch8_out12_carry_i_7_1);
  output [0:0]\min_pulse_width_AXI_1_reg[1] ;
  output [0:0]\Delay1_out1_reg[12] ;
  input Switch8_out12_carry_i_7;
  input [7:0]DI;
  input [7:0]S;
  input [6:0]Switch8_out12_carry_i_7_0;
  input [6:0]Switch8_out12_carry_i_7_1;

  wire [7:0]DI;
  wire [0:0]\Delay1_out1_reg[12] ;
  wire Logical_Operator_out10_carry_n_1;
  wire Logical_Operator_out10_carry_n_2;
  wire Logical_Operator_out10_carry_n_3;
  wire Logical_Operator_out10_carry_n_4;
  wire Logical_Operator_out10_carry_n_5;
  wire Logical_Operator_out10_carry_n_6;
  wire Logical_Operator_out10_carry_n_7;
  wire \Logical_Operator_out10_inferred__0/i__carry_n_2 ;
  wire \Logical_Operator_out10_inferred__0/i__carry_n_3 ;
  wire \Logical_Operator_out10_inferred__0/i__carry_n_4 ;
  wire \Logical_Operator_out10_inferred__0/i__carry_n_5 ;
  wire \Logical_Operator_out10_inferred__0/i__carry_n_6 ;
  wire \Logical_Operator_out10_inferred__0/i__carry_n_7 ;
  wire [7:0]S;
  wire Switch8_out12_carry_i_7;
  wire [6:0]Switch8_out12_carry_i_7_0;
  wire [6:0]Switch8_out12_carry_i_7_1;
  wire [0:0]\min_pulse_width_AXI_1_reg[1] ;
  wire [7:0]NLW_Logical_Operator_out10_carry_O_UNCONNECTED;
  wire [7:7]\NLW_Logical_Operator_out10_inferred__0/i__carry_CO_UNCONNECTED ;
  wire [7:0]\NLW_Logical_Operator_out10_inferred__0/i__carry_O_UNCONNECTED ;

  (* COMPARATOR_THRESHOLD = "11" *) 
  CARRY8 Logical_Operator_out10_carry
       (.CI(Switch8_out12_carry_i_7),
        .CI_TOP(1'b0),
        .CO({\min_pulse_width_AXI_1_reg[1] ,Logical_Operator_out10_carry_n_1,Logical_Operator_out10_carry_n_2,Logical_Operator_out10_carry_n_3,Logical_Operator_out10_carry_n_4,Logical_Operator_out10_carry_n_5,Logical_Operator_out10_carry_n_6,Logical_Operator_out10_carry_n_7}),
        .DI(DI),
        .O(NLW_Logical_Operator_out10_carry_O_UNCONNECTED[7:0]),
        .S(S));
  (* COMPARATOR_THRESHOLD = "11" *) 
  CARRY8 \Logical_Operator_out10_inferred__0/i__carry 
       (.CI(1'b0),
        .CI_TOP(1'b0),
        .CO({\NLW_Logical_Operator_out10_inferred__0/i__carry_CO_UNCONNECTED [7],\Delay1_out1_reg[12] ,\Logical_Operator_out10_inferred__0/i__carry_n_2 ,\Logical_Operator_out10_inferred__0/i__carry_n_3 ,\Logical_Operator_out10_inferred__0/i__carry_n_4 ,\Logical_Operator_out10_inferred__0/i__carry_n_5 ,\Logical_Operator_out10_inferred__0/i__carry_n_6 ,\Logical_Operator_out10_inferred__0/i__carry_n_7 }),
        .DI({1'b0,Switch8_out12_carry_i_7_0}),
        .O(\NLW_Logical_Operator_out10_inferred__0/i__carry_O_UNCONNECTED [7:0]),
        .S({1'b0,Switch8_out12_carry_i_7_1}));
endmodule

module zusys_PWM_and_SS_control_V_0_2_PWM_and_SS_control_V3_ip_src_LimitPulseWidth2
   (\min_pulse_width_AXI_1_reg[1] ,
    \Delay2_out1_reg[12] ,
    Switch9_out12_carry_i_7,
    DI,
    S,
    Switch9_out12_carry_i_7_0,
    Switch9_out12_carry_i_7_1);
  output [0:0]\min_pulse_width_AXI_1_reg[1] ;
  output [0:0]\Delay2_out1_reg[12] ;
  input Switch9_out12_carry_i_7;
  input [7:0]DI;
  input [7:0]S;
  input [6:0]Switch9_out12_carry_i_7_0;
  input [6:0]Switch9_out12_carry_i_7_1;

  wire [7:0]DI;
  wire [0:0]\Delay2_out1_reg[12] ;
  wire Logical_Operator_out10_carry_n_1;
  wire Logical_Operator_out10_carry_n_2;
  wire Logical_Operator_out10_carry_n_3;
  wire Logical_Operator_out10_carry_n_4;
  wire Logical_Operator_out10_carry_n_5;
  wire Logical_Operator_out10_carry_n_6;
  wire Logical_Operator_out10_carry_n_7;
  wire \Logical_Operator_out10_inferred__0/i__carry_n_2 ;
  wire \Logical_Operator_out10_inferred__0/i__carry_n_3 ;
  wire \Logical_Operator_out10_inferred__0/i__carry_n_4 ;
  wire \Logical_Operator_out10_inferred__0/i__carry_n_5 ;
  wire \Logical_Operator_out10_inferred__0/i__carry_n_6 ;
  wire \Logical_Operator_out10_inferred__0/i__carry_n_7 ;
  wire [7:0]S;
  wire Switch9_out12_carry_i_7;
  wire [6:0]Switch9_out12_carry_i_7_0;
  wire [6:0]Switch9_out12_carry_i_7_1;
  wire [0:0]\min_pulse_width_AXI_1_reg[1] ;
  wire [7:0]NLW_Logical_Operator_out10_carry_O_UNCONNECTED;
  wire [7:7]\NLW_Logical_Operator_out10_inferred__0/i__carry_CO_UNCONNECTED ;
  wire [7:0]\NLW_Logical_Operator_out10_inferred__0/i__carry_O_UNCONNECTED ;

  (* COMPARATOR_THRESHOLD = "11" *) 
  CARRY8 Logical_Operator_out10_carry
       (.CI(Switch9_out12_carry_i_7),
        .CI_TOP(1'b0),
        .CO({\min_pulse_width_AXI_1_reg[1] ,Logical_Operator_out10_carry_n_1,Logical_Operator_out10_carry_n_2,Logical_Operator_out10_carry_n_3,Logical_Operator_out10_carry_n_4,Logical_Operator_out10_carry_n_5,Logical_Operator_out10_carry_n_6,Logical_Operator_out10_carry_n_7}),
        .DI(DI),
        .O(NLW_Logical_Operator_out10_carry_O_UNCONNECTED[7:0]),
        .S(S));
  (* COMPARATOR_THRESHOLD = "11" *) 
  CARRY8 \Logical_Operator_out10_inferred__0/i__carry 
       (.CI(1'b0),
        .CI_TOP(1'b0),
        .CO({\NLW_Logical_Operator_out10_inferred__0/i__carry_CO_UNCONNECTED [7],\Delay2_out1_reg[12] ,\Logical_Operator_out10_inferred__0/i__carry_n_2 ,\Logical_Operator_out10_inferred__0/i__carry_n_3 ,\Logical_Operator_out10_inferred__0/i__carry_n_4 ,\Logical_Operator_out10_inferred__0/i__carry_n_5 ,\Logical_Operator_out10_inferred__0/i__carry_n_6 ,\Logical_Operator_out10_inferred__0/i__carry_n_7 }),
        .DI({1'b0,Switch9_out12_carry_i_7_0}),
        .O(\NLW_Logical_Operator_out10_inferred__0/i__carry_O_UNCONNECTED [7:0]),
        .S({1'b0,Switch9_out12_carry_i_7_1}));
endmodule

module zusys_PWM_and_SS_control_V_0_2_PWM_and_SS_control_V3_ip_src_PWM_and_Switching_Signal_Control
   (PWM_en_AXI_1_reg,
    PWM_en_rd_AXI_sig,
    PWM_enb_out,
    Triangular_Max,
    Triangular_Min,
    \Product_mul_temp[-1111111111] ,
    \Product_mul_temp[-1111111110] ,
    \Product_mul_temp[-1111111109] ,
    \Product_mul_temp[-1111111108] ,
    \Product_mul_temp[-1111111107] ,
    \Product_mul_temp[-1111111106] ,
    \Product_mul_temp[-1111111105] ,
    \Product_mul_temp[-1111111104] ,
    \Product_mul_temp[-1111111103] ,
    \f_carrier_kHz_AXI_2_reg[24] ,
    \HDL_Counter2_count_reg[0] ,
    \HDL_Counter2_count_reg[2] ,
    \HDL_Counter2_count_reg[3] ,
    \HDL_Counter2_count_reg[4] ,
    \HDL_Counter2_count_reg[5] ,
    \HDL_Counter2_count_reg[6] ,
    \HDL_Counter2_count_reg[7] ,
    DI,
    S,
    \HDL_Counter2_count_reg[0]_0 ,
    Q,
    \min_pulse_width_AXI_2_reg[17] ,
    \reduced_reg_1_reg[1][1] ,
    SS0_OUT,
    SS1_OUT,
    SS2_OUT,
    SS3_OUT,
    SS4_OUT,
    SS5_OUT,
    reset,
    E,
    IPCORE_CLK,
    CEB2,
    B,
    D,
    write_PWM_en_AXI,
    CO,
    \T_carrier_us_AXI_1_reg[24] ,
    \min_pulse_width_AXI_1_reg[17] ,
    \reduced_reg_1_reg[0][1] ,
    SS0_IN_External,
    \reduced_reg_reg[0][1] ,
    SS1_IN_External,
    SS2_IN_External,
    \reduced_reg_2_reg[0][1] ,
    SS3_IN_External,
    SS4_IN_External,
    \reduced_reg_3_reg[0][1] ,
    SS5_IN_External,
    \U1_norm_1_reg[13] ,
    m_u1_norm,
    \U2_norm_1_reg[13] ,
    m_u2_norm,
    \U3_norm_1_reg[13] ,
    m_u3_norm);
  output PWM_en_AXI_1_reg;
  output PWM_en_rd_AXI_sig;
  output PWM_enb_out;
  output Triangular_Max;
  output Triangular_Min;
  output \Product_mul_temp[-1111111111] ;
  output \Product_mul_temp[-1111111110] ;
  output \Product_mul_temp[-1111111109] ;
  output \Product_mul_temp[-1111111108] ;
  output \Product_mul_temp[-1111111107] ;
  output \Product_mul_temp[-1111111106] ;
  output \Product_mul_temp[-1111111105] ;
  output \Product_mul_temp[-1111111104] ;
  output \Product_mul_temp[-1111111103] ;
  output [15:0]\f_carrier_kHz_AXI_2_reg[24] ;
  output \HDL_Counter2_count_reg[0] ;
  output \HDL_Counter2_count_reg[2] ;
  output \HDL_Counter2_count_reg[3] ;
  output \HDL_Counter2_count_reg[4] ;
  output \HDL_Counter2_count_reg[5] ;
  output \HDL_Counter2_count_reg[6] ;
  output \HDL_Counter2_count_reg[7] ;
  output [0:0]DI;
  output [7:0]S;
  output [0:0]\HDL_Counter2_count_reg[0]_0 ;
  output [24:0]Q;
  output [17:0]\min_pulse_width_AXI_2_reg[17] ;
  output [1:0]\reduced_reg_1_reg[1][1] ;
  output SS0_OUT;
  output SS1_OUT;
  output SS2_OUT;
  output SS3_OUT;
  output SS4_OUT;
  output SS5_OUT;
  input reset;
  input [0:0]E;
  input IPCORE_CLK;
  input CEB2;
  input [7:0]B;
  input [24:0]D;
  input write_PWM_en_AXI;
  input [0:0]CO;
  input [24:0]\T_carrier_us_AXI_1_reg[24] ;
  input [17:0]\min_pulse_width_AXI_1_reg[17] ;
  input [1:0]\reduced_reg_1_reg[0][1] ;
  input SS0_IN_External;
  input [1:0]\reduced_reg_reg[0][1] ;
  input SS1_IN_External;
  input SS2_IN_External;
  input [1:0]\reduced_reg_2_reg[0][1] ;
  input SS3_IN_External;
  input SS4_IN_External;
  input [1:0]\reduced_reg_3_reg[0][1] ;
  input SS5_IN_External;
  input [13:0]\U1_norm_1_reg[13] ;
  input [13:0]m_u1_norm;
  input [13:0]\U2_norm_1_reg[13] ;
  input [13:0]m_u2_norm;
  input [13:0]\U3_norm_1_reg[13] ;
  input [13:0]m_u3_norm;

  wire [7:0]B;
  wire CEB2;
  wire [0:0]CO;
  wire [24:0]D;
  wire [0:0]DI;
  wire [0:0]E;
  wire GenPWM_out1;
  wire GenPWM_out2;
  wire GenPWM_out3;
  wire GenPWM_out4;
  wire GenPWM_out5;
  wire GenPWM_out6;
  wire \HDL_Counter2_count_reg[0] ;
  wire [0:0]\HDL_Counter2_count_reg[0]_0 ;
  wire \HDL_Counter2_count_reg[2] ;
  wire \HDL_Counter2_count_reg[3] ;
  wire \HDL_Counter2_count_reg[4] ;
  wire \HDL_Counter2_count_reg[5] ;
  wire \HDL_Counter2_count_reg[6] ;
  wire \HDL_Counter2_count_reg[7] ;
  wire IPCORE_CLK;
  wire PWM_en_AXI_1_reg;
  wire PWM_en_rd_AXI_sig;
  wire PWM_enb_out;
  wire \Product_mul_temp[-1111111103] ;
  wire \Product_mul_temp[-1111111104] ;
  wire \Product_mul_temp[-1111111105] ;
  wire \Product_mul_temp[-1111111106] ;
  wire \Product_mul_temp[-1111111107] ;
  wire \Product_mul_temp[-1111111108] ;
  wire \Product_mul_temp[-1111111109] ;
  wire \Product_mul_temp[-1111111110] ;
  wire \Product_mul_temp[-1111111111] ;
  wire [24:0]Q;
  wire [7:0]S;
  wire SS0_IN_External;
  wire SS0_OUT;
  wire SS1_IN_External;
  wire SS1_OUT;
  wire SS2_IN_External;
  wire SS2_OUT;
  wire SS3_IN_External;
  wire SS3_OUT;
  wire SS4_IN_External;
  wire SS4_OUT;
  wire SS5_IN_External;
  wire SS5_OUT;
  wire [24:0]\T_carrier_us_AXI_1_reg[24] ;
  wire Triangular_Max;
  wire Triangular_Min;
  wire [13:0]U1_norm;
  wire [13:0]\U1_norm_1_reg[13] ;
  wire [13:0]U2_norm;
  wire [13:0]\U2_norm_1_reg[13] ;
  wire [13:0]U3_norm;
  wire [13:0]\U3_norm_1_reg[13] ;
  wire [15:0]\f_carrier_kHz_AXI_2_reg[24] ;
  wire [13:0]m_u1_norm;
  wire [13:0]m_u2_norm;
  wire [13:0]m_u3_norm;
  wire [17:0]\min_pulse_width_AXI_1_reg[17] ;
  wire [17:0]\min_pulse_width_AXI_2_reg[17] ;
  wire [1:0]\reduced_reg_1_reg[0][1] ;
  wire [1:0]\reduced_reg_1_reg[1][1] ;
  wire [1:0]\reduced_reg_2_reg[0][1] ;
  wire [1:0]\reduced_reg_3_reg[0][1] ;
  wire [1:0]\reduced_reg_reg[0][1] ;
  wire reset;
  wire write_PWM_en_AXI;

  LUT4 #(
    .INIT(16'hFE02)) 
    \U1_norm_1[0]_i_1 
       (.I0(\U1_norm_1_reg[13] [0]),
        .I1(\reduced_reg_1_reg[0][1] [0]),
        .I2(\reduced_reg_1_reg[0][1] [1]),
        .I3(m_u1_norm[0]),
        .O(U1_norm[0]));
  LUT4 #(
    .INIT(16'hFE02)) 
    \U1_norm_1[10]_i_1 
       (.I0(\U1_norm_1_reg[13] [10]),
        .I1(\reduced_reg_1_reg[0][1] [0]),
        .I2(\reduced_reg_1_reg[0][1] [1]),
        .I3(m_u1_norm[10]),
        .O(U1_norm[10]));
  LUT4 #(
    .INIT(16'hFE02)) 
    \U1_norm_1[11]_i_1 
       (.I0(\U1_norm_1_reg[13] [11]),
        .I1(\reduced_reg_1_reg[0][1] [0]),
        .I2(\reduced_reg_1_reg[0][1] [1]),
        .I3(m_u1_norm[11]),
        .O(U1_norm[11]));
  LUT4 #(
    .INIT(16'hFE02)) 
    \U1_norm_1[12]_i_1 
       (.I0(\U1_norm_1_reg[13] [12]),
        .I1(\reduced_reg_1_reg[0][1] [0]),
        .I2(\reduced_reg_1_reg[0][1] [1]),
        .I3(m_u1_norm[12]),
        .O(U1_norm[12]));
  LUT4 #(
    .INIT(16'hFE02)) 
    \U1_norm_1[13]_i_1 
       (.I0(\U1_norm_1_reg[13] [13]),
        .I1(\reduced_reg_1_reg[0][1] [0]),
        .I2(\reduced_reg_1_reg[0][1] [1]),
        .I3(m_u1_norm[13]),
        .O(U1_norm[13]));
  LUT4 #(
    .INIT(16'hFE02)) 
    \U1_norm_1[1]_i_1 
       (.I0(\U1_norm_1_reg[13] [1]),
        .I1(\reduced_reg_1_reg[0][1] [0]),
        .I2(\reduced_reg_1_reg[0][1] [1]),
        .I3(m_u1_norm[1]),
        .O(U1_norm[1]));
  LUT4 #(
    .INIT(16'hFE02)) 
    \U1_norm_1[2]_i_1 
       (.I0(\U1_norm_1_reg[13] [2]),
        .I1(\reduced_reg_1_reg[0][1] [0]),
        .I2(\reduced_reg_1_reg[0][1] [1]),
        .I3(m_u1_norm[2]),
        .O(U1_norm[2]));
  LUT4 #(
    .INIT(16'hFE02)) 
    \U1_norm_1[3]_i_1 
       (.I0(\U1_norm_1_reg[13] [3]),
        .I1(\reduced_reg_1_reg[0][1] [0]),
        .I2(\reduced_reg_1_reg[0][1] [1]),
        .I3(m_u1_norm[3]),
        .O(U1_norm[3]));
  LUT4 #(
    .INIT(16'hFE02)) 
    \U1_norm_1[4]_i_1 
       (.I0(\U1_norm_1_reg[13] [4]),
        .I1(\reduced_reg_1_reg[0][1] [0]),
        .I2(\reduced_reg_1_reg[0][1] [1]),
        .I3(m_u1_norm[4]),
        .O(U1_norm[4]));
  LUT4 #(
    .INIT(16'hFE02)) 
    \U1_norm_1[5]_i_1 
       (.I0(\U1_norm_1_reg[13] [5]),
        .I1(\reduced_reg_1_reg[0][1] [0]),
        .I2(\reduced_reg_1_reg[0][1] [1]),
        .I3(m_u1_norm[5]),
        .O(U1_norm[5]));
  LUT4 #(
    .INIT(16'hFE02)) 
    \U1_norm_1[6]_i_1 
       (.I0(\U1_norm_1_reg[13] [6]),
        .I1(\reduced_reg_1_reg[0][1] [0]),
        .I2(\reduced_reg_1_reg[0][1] [1]),
        .I3(m_u1_norm[6]),
        .O(U1_norm[6]));
  LUT4 #(
    .INIT(16'hFE02)) 
    \U1_norm_1[7]_i_1 
       (.I0(\U1_norm_1_reg[13] [7]),
        .I1(\reduced_reg_1_reg[0][1] [0]),
        .I2(\reduced_reg_1_reg[0][1] [1]),
        .I3(m_u1_norm[7]),
        .O(U1_norm[7]));
  LUT4 #(
    .INIT(16'hFE02)) 
    \U1_norm_1[8]_i_1 
       (.I0(\U1_norm_1_reg[13] [8]),
        .I1(\reduced_reg_1_reg[0][1] [0]),
        .I2(\reduced_reg_1_reg[0][1] [1]),
        .I3(m_u1_norm[8]),
        .O(U1_norm[8]));
  LUT4 #(
    .INIT(16'hFE02)) 
    \U1_norm_1[9]_i_1 
       (.I0(\U1_norm_1_reg[13] [9]),
        .I1(\reduced_reg_1_reg[0][1] [0]),
        .I2(\reduced_reg_1_reg[0][1] [1]),
        .I3(m_u1_norm[9]),
        .O(U1_norm[9]));
  LUT4 #(
    .INIT(16'hFE02)) 
    \U2_norm_1[0]_i_1 
       (.I0(\U2_norm_1_reg[13] [0]),
        .I1(\reduced_reg_1_reg[0][1] [0]),
        .I2(\reduced_reg_1_reg[0][1] [1]),
        .I3(m_u2_norm[0]),
        .O(U2_norm[0]));
  LUT4 #(
    .INIT(16'hFE02)) 
    \U2_norm_1[10]_i_1 
       (.I0(\U2_norm_1_reg[13] [10]),
        .I1(\reduced_reg_1_reg[0][1] [0]),
        .I2(\reduced_reg_1_reg[0][1] [1]),
        .I3(m_u2_norm[10]),
        .O(U2_norm[10]));
  LUT4 #(
    .INIT(16'hFE02)) 
    \U2_norm_1[11]_i_1 
       (.I0(\U2_norm_1_reg[13] [11]),
        .I1(\reduced_reg_1_reg[0][1] [0]),
        .I2(\reduced_reg_1_reg[0][1] [1]),
        .I3(m_u2_norm[11]),
        .O(U2_norm[11]));
  LUT4 #(
    .INIT(16'hFE02)) 
    \U2_norm_1[12]_i_1 
       (.I0(\U2_norm_1_reg[13] [12]),
        .I1(\reduced_reg_1_reg[0][1] [0]),
        .I2(\reduced_reg_1_reg[0][1] [1]),
        .I3(m_u2_norm[12]),
        .O(U2_norm[12]));
  LUT4 #(
    .INIT(16'hFE02)) 
    \U2_norm_1[13]_i_1 
       (.I0(\U2_norm_1_reg[13] [13]),
        .I1(\reduced_reg_1_reg[0][1] [0]),
        .I2(\reduced_reg_1_reg[0][1] [1]),
        .I3(m_u2_norm[13]),
        .O(U2_norm[13]));
  LUT4 #(
    .INIT(16'hFE02)) 
    \U2_norm_1[1]_i_1 
       (.I0(\U2_norm_1_reg[13] [1]),
        .I1(\reduced_reg_1_reg[0][1] [0]),
        .I2(\reduced_reg_1_reg[0][1] [1]),
        .I3(m_u2_norm[1]),
        .O(U2_norm[1]));
  LUT4 #(
    .INIT(16'hFE02)) 
    \U2_norm_1[2]_i_1 
       (.I0(\U2_norm_1_reg[13] [2]),
        .I1(\reduced_reg_1_reg[0][1] [0]),
        .I2(\reduced_reg_1_reg[0][1] [1]),
        .I3(m_u2_norm[2]),
        .O(U2_norm[2]));
  LUT4 #(
    .INIT(16'hFE02)) 
    \U2_norm_1[3]_i_1 
       (.I0(\U2_norm_1_reg[13] [3]),
        .I1(\reduced_reg_1_reg[0][1] [0]),
        .I2(\reduced_reg_1_reg[0][1] [1]),
        .I3(m_u2_norm[3]),
        .O(U2_norm[3]));
  LUT4 #(
    .INIT(16'hFE02)) 
    \U2_norm_1[4]_i_1 
       (.I0(\U2_norm_1_reg[13] [4]),
        .I1(\reduced_reg_1_reg[0][1] [0]),
        .I2(\reduced_reg_1_reg[0][1] [1]),
        .I3(m_u2_norm[4]),
        .O(U2_norm[4]));
  LUT4 #(
    .INIT(16'hFE02)) 
    \U2_norm_1[5]_i_1 
       (.I0(\U2_norm_1_reg[13] [5]),
        .I1(\reduced_reg_1_reg[0][1] [0]),
        .I2(\reduced_reg_1_reg[0][1] [1]),
        .I3(m_u2_norm[5]),
        .O(U2_norm[5]));
  LUT4 #(
    .INIT(16'hFE02)) 
    \U2_norm_1[6]_i_1 
       (.I0(\U2_norm_1_reg[13] [6]),
        .I1(\reduced_reg_1_reg[0][1] [0]),
        .I2(\reduced_reg_1_reg[0][1] [1]),
        .I3(m_u2_norm[6]),
        .O(U2_norm[6]));
  LUT4 #(
    .INIT(16'hFE02)) 
    \U2_norm_1[7]_i_1 
       (.I0(\U2_norm_1_reg[13] [7]),
        .I1(\reduced_reg_1_reg[0][1] [0]),
        .I2(\reduced_reg_1_reg[0][1] [1]),
        .I3(m_u2_norm[7]),
        .O(U2_norm[7]));
  LUT4 #(
    .INIT(16'hFE02)) 
    \U2_norm_1[8]_i_1 
       (.I0(\U2_norm_1_reg[13] [8]),
        .I1(\reduced_reg_1_reg[0][1] [0]),
        .I2(\reduced_reg_1_reg[0][1] [1]),
        .I3(m_u2_norm[8]),
        .O(U2_norm[8]));
  LUT4 #(
    .INIT(16'hFE02)) 
    \U2_norm_1[9]_i_1 
       (.I0(\U2_norm_1_reg[13] [9]),
        .I1(\reduced_reg_1_reg[0][1] [0]),
        .I2(\reduced_reg_1_reg[0][1] [1]),
        .I3(m_u2_norm[9]),
        .O(U2_norm[9]));
  LUT4 #(
    .INIT(16'hFE02)) 
    \U3_norm_1[0]_i_1 
       (.I0(\U3_norm_1_reg[13] [0]),
        .I1(\reduced_reg_1_reg[0][1] [0]),
        .I2(\reduced_reg_1_reg[0][1] [1]),
        .I3(m_u3_norm[0]),
        .O(U3_norm[0]));
  LUT4 #(
    .INIT(16'hFE02)) 
    \U3_norm_1[10]_i_1 
       (.I0(\U3_norm_1_reg[13] [10]),
        .I1(\reduced_reg_1_reg[0][1] [0]),
        .I2(\reduced_reg_1_reg[0][1] [1]),
        .I3(m_u3_norm[10]),
        .O(U3_norm[10]));
  LUT4 #(
    .INIT(16'hFE02)) 
    \U3_norm_1[11]_i_1 
       (.I0(\U3_norm_1_reg[13] [11]),
        .I1(\reduced_reg_1_reg[0][1] [0]),
        .I2(\reduced_reg_1_reg[0][1] [1]),
        .I3(m_u3_norm[11]),
        .O(U3_norm[11]));
  LUT4 #(
    .INIT(16'hFE02)) 
    \U3_norm_1[12]_i_1 
       (.I0(\U3_norm_1_reg[13] [12]),
        .I1(\reduced_reg_1_reg[0][1] [0]),
        .I2(\reduced_reg_1_reg[0][1] [1]),
        .I3(m_u3_norm[12]),
        .O(U3_norm[12]));
  LUT4 #(
    .INIT(16'hFE02)) 
    \U3_norm_1[13]_i_1 
       (.I0(\U3_norm_1_reg[13] [13]),
        .I1(\reduced_reg_1_reg[0][1] [0]),
        .I2(\reduced_reg_1_reg[0][1] [1]),
        .I3(m_u3_norm[13]),
        .O(U3_norm[13]));
  LUT4 #(
    .INIT(16'hFE02)) 
    \U3_norm_1[1]_i_1 
       (.I0(\U3_norm_1_reg[13] [1]),
        .I1(\reduced_reg_1_reg[0][1] [0]),
        .I2(\reduced_reg_1_reg[0][1] [1]),
        .I3(m_u3_norm[1]),
        .O(U3_norm[1]));
  LUT4 #(
    .INIT(16'hFE02)) 
    \U3_norm_1[2]_i_1 
       (.I0(\U3_norm_1_reg[13] [2]),
        .I1(\reduced_reg_1_reg[0][1] [0]),
        .I2(\reduced_reg_1_reg[0][1] [1]),
        .I3(m_u3_norm[2]),
        .O(U3_norm[2]));
  LUT4 #(
    .INIT(16'hFE02)) 
    \U3_norm_1[3]_i_1 
       (.I0(\U3_norm_1_reg[13] [3]),
        .I1(\reduced_reg_1_reg[0][1] [0]),
        .I2(\reduced_reg_1_reg[0][1] [1]),
        .I3(m_u3_norm[3]),
        .O(U3_norm[3]));
  LUT4 #(
    .INIT(16'hFE02)) 
    \U3_norm_1[4]_i_1 
       (.I0(\U3_norm_1_reg[13] [4]),
        .I1(\reduced_reg_1_reg[0][1] [0]),
        .I2(\reduced_reg_1_reg[0][1] [1]),
        .I3(m_u3_norm[4]),
        .O(U3_norm[4]));
  LUT4 #(
    .INIT(16'hFE02)) 
    \U3_norm_1[5]_i_1 
       (.I0(\U3_norm_1_reg[13] [5]),
        .I1(\reduced_reg_1_reg[0][1] [0]),
        .I2(\reduced_reg_1_reg[0][1] [1]),
        .I3(m_u3_norm[5]),
        .O(U3_norm[5]));
  LUT4 #(
    .INIT(16'hFE02)) 
    \U3_norm_1[6]_i_1 
       (.I0(\U3_norm_1_reg[13] [6]),
        .I1(\reduced_reg_1_reg[0][1] [0]),
        .I2(\reduced_reg_1_reg[0][1] [1]),
        .I3(m_u3_norm[6]),
        .O(U3_norm[6]));
  LUT4 #(
    .INIT(16'hFE02)) 
    \U3_norm_1[7]_i_1 
       (.I0(\U3_norm_1_reg[13] [7]),
        .I1(\reduced_reg_1_reg[0][1] [0]),
        .I2(\reduced_reg_1_reg[0][1] [1]),
        .I3(m_u3_norm[7]),
        .O(U3_norm[7]));
  LUT4 #(
    .INIT(16'hFE02)) 
    \U3_norm_1[8]_i_1 
       (.I0(\U3_norm_1_reg[13] [8]),
        .I1(\reduced_reg_1_reg[0][1] [0]),
        .I2(\reduced_reg_1_reg[0][1] [1]),
        .I3(m_u3_norm[8]),
        .O(U3_norm[8]));
  LUT4 #(
    .INIT(16'hFE02)) 
    \U3_norm_1[9]_i_1 
       (.I0(\U3_norm_1_reg[13] [9]),
        .I1(\reduced_reg_1_reg[0][1] [0]),
        .I2(\reduced_reg_1_reg[0][1] [1]),
        .I3(m_u3_norm[9]),
        .O(U3_norm[9]));
  zusys_PWM_and_SS_control_V_0_2_PWM_and_SS_control_V3_ip_src_GenPWM u_GenPWM
       (.B(B),
        .CEB2(CEB2),
        .CO(CO),
        .D(D),
        .DI({DI,\HDL_Counter2_count_reg[0] }),
        .E(E),
        .GenPWM_out1(GenPWM_out1),
        .GenPWM_out2(GenPWM_out2),
        .GenPWM_out3(GenPWM_out3),
        .GenPWM_out4(GenPWM_out4),
        .GenPWM_out5(GenPWM_out5),
        .GenPWM_out6(GenPWM_out6),
        .\HDL_Counter2_count_reg[0]_0 (\HDL_Counter2_count_reg[0]_0 ),
        .\HDL_Counter2_count_reg[2]_0 (\HDL_Counter2_count_reg[2] ),
        .\HDL_Counter2_count_reg[3]_0 (\HDL_Counter2_count_reg[3] ),
        .\HDL_Counter2_count_reg[4]_0 (\HDL_Counter2_count_reg[4] ),
        .\HDL_Counter2_count_reg[5]_0 (\HDL_Counter2_count_reg[5] ),
        .\HDL_Counter2_count_reg[6]_0 (\HDL_Counter2_count_reg[6] ),
        .\HDL_Counter2_count_reg[7]_0 (\HDL_Counter2_count_reg[7] ),
        .IPCORE_CLK(IPCORE_CLK),
        .PWM_en_AXI_1_reg_0(PWM_en_AXI_1_reg),
        .PWM_en_rd_AXI_sig(PWM_en_rd_AXI_sig),
        .PWM_enb_out(PWM_enb_out),
        .\Product_mul_temp[-1111111103] (\Product_mul_temp[-1111111103] ),
        .\Product_mul_temp[-1111111104] (\Product_mul_temp[-1111111104] ),
        .\Product_mul_temp[-1111111105] (\Product_mul_temp[-1111111105] ),
        .\Product_mul_temp[-1111111106] (\Product_mul_temp[-1111111106] ),
        .\Product_mul_temp[-1111111107] (\Product_mul_temp[-1111111107] ),
        .\Product_mul_temp[-1111111108] (\Product_mul_temp[-1111111108] ),
        .\Product_mul_temp[-1111111109] (\Product_mul_temp[-1111111109] ),
        .\Product_mul_temp[-1111111110] (\Product_mul_temp[-1111111110] ),
        .\Product_mul_temp[-1111111111] (\Product_mul_temp[-1111111111] ),
        .Q(Q),
        .S(S),
        .\T_carrier_us_AXI_1_reg[24]_0 (\T_carrier_us_AXI_1_reg[24] ),
        .Triangular_Max(Triangular_Max),
        .Triangular_Min(Triangular_Min),
        .\U1_norm_1_reg[13]_0 (U1_norm),
        .\U2_norm_1_reg[13]_0 (U2_norm),
        .\U3_norm_1_reg[13]_0 (U3_norm),
        .\f_carrier_kHz_AXI_2_reg[24]_0 (\f_carrier_kHz_AXI_2_reg[24] ),
        .\min_pulse_width_AXI_1_reg[17]_0 (\min_pulse_width_AXI_1_reg[17] ),
        .\min_pulse_width_AXI_2_reg[17]_0 (\min_pulse_width_AXI_2_reg[17] ),
        .reset(reset),
        .write_PWM_en_AXI(write_PWM_en_AXI));
  zusys_PWM_and_SS_control_V_0_2_PWM_and_SS_control_V3_ip_src_VSI_Control_Signal_Switch u_VSI_Control_Signal_Switch
       (.E(E),
        .GenPWM_out1(GenPWM_out1),
        .GenPWM_out2(GenPWM_out2),
        .GenPWM_out3(GenPWM_out3),
        .GenPWM_out4(GenPWM_out4),
        .GenPWM_out5(GenPWM_out5),
        .GenPWM_out6(GenPWM_out6),
        .IPCORE_CLK(IPCORE_CLK),
        .Q(\reduced_reg_1_reg[1][1] ),
        .SS0_IN_External(SS0_IN_External),
        .SS0_OUT(SS0_OUT),
        .SS1_IN_External(SS1_IN_External),
        .SS1_OUT(SS1_OUT),
        .SS2_IN_External(SS2_IN_External),
        .SS2_OUT(SS2_OUT),
        .SS3_IN_External(SS3_IN_External),
        .SS3_OUT(SS3_OUT),
        .SS4_IN_External(SS4_IN_External),
        .SS4_OUT(SS4_OUT),
        .SS5_IN_External(SS5_IN_External),
        .SS5_OUT(SS5_OUT),
        .\reduced_reg_1_reg[0][1]_0 (\reduced_reg_1_reg[0][1] ),
        .\reduced_reg_2_reg[0][1]_0 (\reduced_reg_2_reg[0][1] ),
        .\reduced_reg_3_reg[0][1]_0 (\reduced_reg_3_reg[0][1] ),
        .\reduced_reg_reg[0][1]_0 (\reduced_reg_reg[0][1] ),
        .reset(reset));
endmodule

module zusys_PWM_and_SS_control_V_0_2_PWM_and_SS_control_V3_ip_src_VSI_Control_Signal_Switch
   (Q,
    SS0_OUT,
    SS1_OUT,
    SS2_OUT,
    SS3_OUT,
    SS4_OUT,
    SS5_OUT,
    reset,
    E,
    \reduced_reg_1_reg[0][1]_0 ,
    IPCORE_CLK,
    SS0_IN_External,
    \reduced_reg_reg[0][1]_0 ,
    SS1_IN_External,
    SS2_IN_External,
    \reduced_reg_2_reg[0][1]_0 ,
    SS3_IN_External,
    SS4_IN_External,
    \reduced_reg_3_reg[0][1]_0 ,
    SS5_IN_External,
    GenPWM_out1,
    GenPWM_out2,
    GenPWM_out3,
    GenPWM_out4,
    GenPWM_out5,
    GenPWM_out6);
  output [1:0]Q;
  output SS0_OUT;
  output SS1_OUT;
  output SS2_OUT;
  output SS3_OUT;
  output SS4_OUT;
  output SS5_OUT;
  input reset;
  input [0:0]E;
  input [1:0]\reduced_reg_1_reg[0][1]_0 ;
  input IPCORE_CLK;
  input SS0_IN_External;
  input [1:0]\reduced_reg_reg[0][1]_0 ;
  input SS1_IN_External;
  input SS2_IN_External;
  input [1:0]\reduced_reg_2_reg[0][1]_0 ;
  input SS3_IN_External;
  input SS4_IN_External;
  input [1:0]\reduced_reg_3_reg[0][1]_0 ;
  input SS5_IN_External;
  input GenPWM_out1;
  input GenPWM_out2;
  input GenPWM_out3;
  input GenPWM_out4;
  input GenPWM_out5;
  input GenPWM_out6;

  wire [0:0]E;
  wire GenPWM_out1;
  wire GenPWM_out2;
  wire GenPWM_out3;
  wire GenPWM_out4;
  wire GenPWM_out5;
  wire GenPWM_out6;
  wire IPCORE_CLK;
  wire [1:0]Q;
  wire SS0_IN_External;
  wire SS0_OUT;
  wire SS1_IN_External;
  wire SS1_OUT;
  wire SS2_IN_External;
  wire SS2_OUT;
  wire SS3_IN_External;
  wire SS3_OUT;
  wire SS4_IN_External;
  wire SS4_OUT;
  wire SS5_IN_External;
  wire SS5_OUT;
  wire [1:1]delayMatch12_reg;
  wire \delayMatch12_reg_reg_n_0_[0] ;
  wire [1:1]delayMatch15_reg;
  wire \delayMatch15_reg_reg_n_0_[0] ;
  wire [1:1]delayMatch3_reg;
  wire \delayMatch3_reg_reg_n_0_[0] ;
  wire [1:1]delayMatch6_reg;
  wire \delayMatch6_reg_reg_n_0_[0] ;
  wire [1:1]delayMatch9_reg;
  wire \delayMatch9_reg_reg_n_0_[0] ;
  wire [1:1]delayMatch_reg;
  wire [1:0]\delayMatch_reg_reg[0]_0 ;
  wire \delayMatch_reg_reg_n_0_[0] ;
  wire [1:0]\reduced_reg_1_reg[0][1]_0 ;
  wire [1:0]\reduced_reg_2_reg[0][1]_0 ;
  wire [1:0]\reduced_reg_2_reg[0]_2 ;
  wire \reduced_reg_2_reg_n_0_[1][0] ;
  wire \reduced_reg_2_reg_n_0_[1][1] ;
  wire [1:0]\reduced_reg_3_reg[0][1]_0 ;
  wire [1:0]\reduced_reg_3_reg[0]_3 ;
  wire \reduced_reg_3_reg_n_0_[1][0] ;
  wire \reduced_reg_3_reg_n_0_[1][1] ;
  wire [1:0]\reduced_reg_reg[0][1]_0 ;
  wire [1:0]\reduced_reg_reg[0]_1 ;
  wire \reduced_reg_reg_n_0_[1][0] ;
  wire \reduced_reg_reg_n_0_[1][1] ;
  wire reset;

  LUT5 #(
    .INIT(32'h000000E2)) 
    Switch10_out1
       (.I0(GenPWM_out5),
        .I1(Q[1]),
        .I2(delayMatch12_reg),
        .I3(\reduced_reg_3_reg_n_0_[1][0] ),
        .I4(\reduced_reg_3_reg_n_0_[1][1] ),
        .O(SS4_OUT));
  LUT5 #(
    .INIT(32'h000000E2)) 
    Switch11_out1
       (.I0(GenPWM_out6),
        .I1(Q[1]),
        .I2(delayMatch15_reg),
        .I3(\reduced_reg_3_reg_n_0_[1][0] ),
        .I4(\reduced_reg_3_reg_n_0_[1][1] ),
        .O(SS5_OUT));
  LUT5 #(
    .INIT(32'h000000E2)) 
    Switch6_out1
       (.I0(GenPWM_out1),
        .I1(Q[1]),
        .I2(delayMatch_reg),
        .I3(\reduced_reg_reg_n_0_[1][0] ),
        .I4(\reduced_reg_reg_n_0_[1][1] ),
        .O(SS0_OUT));
  LUT5 #(
    .INIT(32'h000000E2)) 
    Switch7_out1
       (.I0(GenPWM_out2),
        .I1(Q[1]),
        .I2(delayMatch3_reg),
        .I3(\reduced_reg_reg_n_0_[1][0] ),
        .I4(\reduced_reg_reg_n_0_[1][1] ),
        .O(SS1_OUT));
  LUT5 #(
    .INIT(32'h000000E2)) 
    Switch8_out1
       (.I0(GenPWM_out3),
        .I1(Q[1]),
        .I2(delayMatch6_reg),
        .I3(\reduced_reg_2_reg_n_0_[1][0] ),
        .I4(\reduced_reg_2_reg_n_0_[1][1] ),
        .O(SS2_OUT));
  LUT5 #(
    .INIT(32'h000000E2)) 
    Switch9_out1
       (.I0(GenPWM_out4),
        .I1(Q[1]),
        .I2(delayMatch9_reg),
        .I3(\reduced_reg_2_reg_n_0_[1][0] ),
        .I4(\reduced_reg_2_reg_n_0_[1][1] ),
        .O(SS3_OUT));
  FDRE \delayMatch12_reg_reg[0] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(SS4_IN_External),
        .Q(\delayMatch12_reg_reg_n_0_[0] ),
        .R(reset));
  FDRE \delayMatch12_reg_reg[1] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(\delayMatch12_reg_reg_n_0_[0] ),
        .Q(delayMatch12_reg),
        .R(reset));
  FDRE \delayMatch15_reg_reg[0] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(SS5_IN_External),
        .Q(\delayMatch15_reg_reg_n_0_[0] ),
        .R(reset));
  FDRE \delayMatch15_reg_reg[1] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(\delayMatch15_reg_reg_n_0_[0] ),
        .Q(delayMatch15_reg),
        .R(reset));
  FDRE \delayMatch3_reg_reg[0] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(SS1_IN_External),
        .Q(\delayMatch3_reg_reg_n_0_[0] ),
        .R(reset));
  FDRE \delayMatch3_reg_reg[1] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(\delayMatch3_reg_reg_n_0_[0] ),
        .Q(delayMatch3_reg),
        .R(reset));
  FDRE \delayMatch6_reg_reg[0] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(SS2_IN_External),
        .Q(\delayMatch6_reg_reg_n_0_[0] ),
        .R(reset));
  FDRE \delayMatch6_reg_reg[1] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(\delayMatch6_reg_reg_n_0_[0] ),
        .Q(delayMatch6_reg),
        .R(reset));
  FDRE \delayMatch9_reg_reg[0] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(SS3_IN_External),
        .Q(\delayMatch9_reg_reg_n_0_[0] ),
        .R(reset));
  FDRE \delayMatch9_reg_reg[1] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(\delayMatch9_reg_reg_n_0_[0] ),
        .Q(delayMatch9_reg),
        .R(reset));
  FDRE \delayMatch_reg_reg[0] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(SS0_IN_External),
        .Q(\delayMatch_reg_reg_n_0_[0] ),
        .R(reset));
  FDRE \delayMatch_reg_reg[1] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(\delayMatch_reg_reg_n_0_[0] ),
        .Q(delayMatch_reg),
        .R(reset));
  FDRE \reduced_reg_1_reg[0][0] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(\reduced_reg_1_reg[0][1]_0 [0]),
        .Q(\delayMatch_reg_reg[0]_0 [0]),
        .R(reset));
  FDRE \reduced_reg_1_reg[0][1] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(\reduced_reg_1_reg[0][1]_0 [1]),
        .Q(\delayMatch_reg_reg[0]_0 [1]),
        .R(reset));
  FDRE \reduced_reg_1_reg[1][0] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(\delayMatch_reg_reg[0]_0 [0]),
        .Q(Q[0]),
        .R(reset));
  FDRE \reduced_reg_1_reg[1][1] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(\delayMatch_reg_reg[0]_0 [1]),
        .Q(Q[1]),
        .R(reset));
  FDRE \reduced_reg_2_reg[0][0] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(\reduced_reg_2_reg[0][1]_0 [0]),
        .Q(\reduced_reg_2_reg[0]_2 [0]),
        .R(reset));
  FDRE \reduced_reg_2_reg[0][1] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(\reduced_reg_2_reg[0][1]_0 [1]),
        .Q(\reduced_reg_2_reg[0]_2 [1]),
        .R(reset));
  FDRE \reduced_reg_2_reg[1][0] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(\reduced_reg_2_reg[0]_2 [0]),
        .Q(\reduced_reg_2_reg_n_0_[1][0] ),
        .R(reset));
  FDRE \reduced_reg_2_reg[1][1] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(\reduced_reg_2_reg[0]_2 [1]),
        .Q(\reduced_reg_2_reg_n_0_[1][1] ),
        .R(reset));
  FDRE \reduced_reg_3_reg[0][0] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(\reduced_reg_3_reg[0][1]_0 [0]),
        .Q(\reduced_reg_3_reg[0]_3 [0]),
        .R(reset));
  FDRE \reduced_reg_3_reg[0][1] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(\reduced_reg_3_reg[0][1]_0 [1]),
        .Q(\reduced_reg_3_reg[0]_3 [1]),
        .R(reset));
  FDRE \reduced_reg_3_reg[1][0] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(\reduced_reg_3_reg[0]_3 [0]),
        .Q(\reduced_reg_3_reg_n_0_[1][0] ),
        .R(reset));
  FDRE \reduced_reg_3_reg[1][1] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(\reduced_reg_3_reg[0]_3 [1]),
        .Q(\reduced_reg_3_reg_n_0_[1][1] ),
        .R(reset));
  FDRE \reduced_reg_reg[0][0] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(\reduced_reg_reg[0][1]_0 [0]),
        .Q(\reduced_reg_reg[0]_1 [0]),
        .R(reset));
  FDRE \reduced_reg_reg[0][1] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(\reduced_reg_reg[0][1]_0 [1]),
        .Q(\reduced_reg_reg[0]_1 [1]),
        .R(reset));
  FDRE \reduced_reg_reg[1][0] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(\reduced_reg_reg[0]_1 [0]),
        .Q(\reduced_reg_reg_n_0_[1][0] ),
        .R(reset));
  FDRE \reduced_reg_reg[1][1] 
       (.C(IPCORE_CLK),
        .CE(E),
        .D(\reduced_reg_reg[0]_1 [1]),
        .Q(\reduced_reg_reg_n_0_[1][1] ),
        .R(reset));
endmodule

(* CHECK_LICENSE_TYPE = "zusys_PWM_and_SS_control_V_0_0,PWM_and_SS_control_V3_ip,{}" *) (* downgradeipidentifiedwarnings = "yes" *) (* ip_definition_source = "package_project" *) 
(* x_core_info = "PWM_and_SS_control_V3_ip,Vivado 2020.1.1" *) 
(* NotValidForBitStream *)
module zusys_PWM_and_SS_control_V_0_2
   (IPCORE_CLK,
    IPCORE_RESETN,
    m_u1_norm,
    m_u2_norm,
    m_u3_norm,
    SS0_IN_External,
    SS1_IN_External,
    SS2_IN_External,
    SS3_IN_External,
    SS4_IN_External,
    SS5_IN_External,
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
    SS0_OUT,
    SS1_OUT,
    SS2_OUT,
    SS3_OUT,
    SS4_OUT,
    SS5_OUT,
    PWM_enb_out,
    Triangular_Max,
    Triangular_Min,
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
  input SS0_IN_External;
  input SS1_IN_External;
  input SS2_IN_External;
  input SS3_IN_External;
  input SS4_IN_External;
  input SS5_IN_External;
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
  output SS0_OUT;
  output SS1_OUT;
  output SS2_OUT;
  output SS3_OUT;
  output SS4_OUT;
  output SS5_OUT;
  output PWM_enb_out;
  output Triangular_Max;
  output Triangular_Min;
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
  wire PWM_enb_out;
  wire SS0_IN_External;
  wire SS0_OUT;
  wire SS1_IN_External;
  wire SS1_OUT;
  wire SS2_IN_External;
  wire SS2_OUT;
  wire SS3_IN_External;
  wire SS3_OUT;
  wire SS4_IN_External;
  wire SS4_OUT;
  wire SS5_IN_External;
  wire SS5_OUT;
  wire Triangular_Max;
  wire Triangular_Min;
  wire U0_n_11;
  wire U0_n_12;
  wire U0_n_13;
  wire U0_n_14;
  wire U0_n_15;
  wire U0_n_16;
  wire U0_n_17;
  wire U0_n_18;
  wire U0_n_19;
  wire U0_n_20;
  wire [13:0]m_u1_norm;
  wire [13:0]m_u2_norm;
  wire [13:0]m_u3_norm;
  wire [8:1]\u_PWM_and_SS_control_V3_ip_dut_inst/u_PWM_and_SS_control_V3_ip_src_PWM_and_Switching_Signal_Control/u_GenPWM/HDL_Counter2_count_next ;
  wire [7:0]\u_PWM_and_SS_control_V3_ip_dut_inst/u_PWM_and_SS_control_V3_ip_src_PWM_and_Switching_Signal_Control/u_GenPWM/HDL_Counter2_count_reg ;
  wire \u_PWM_and_SS_control_V3_ip_src_PWM_and_Switching_Signal_Control/u_GenPWM/HDL_Counter2_count_next_carry_n_0 ;
  wire \u_PWM_and_SS_control_V3_ip_src_PWM_and_Switching_Signal_Control/u_GenPWM/HDL_Counter2_count_next_carry_n_1 ;
  wire \u_PWM_and_SS_control_V3_ip_src_PWM_and_Switching_Signal_Control/u_GenPWM/HDL_Counter2_count_next_carry_n_2 ;
  wire \u_PWM_and_SS_control_V3_ip_src_PWM_and_Switching_Signal_Control/u_GenPWM/HDL_Counter2_count_next_carry_n_3 ;
  wire \u_PWM_and_SS_control_V3_ip_src_PWM_and_Switching_Signal_Control/u_GenPWM/HDL_Counter2_count_next_carry_n_4 ;
  wire \u_PWM_and_SS_control_V3_ip_src_PWM_and_Switching_Signal_Control/u_GenPWM/HDL_Counter2_count_next_carry_n_5 ;
  wire \u_PWM_and_SS_control_V3_ip_src_PWM_and_Switching_Signal_Control/u_GenPWM/HDL_Counter2_count_next_carry_n_6 ;
  wire \u_PWM_and_SS_control_V3_ip_src_PWM_and_Switching_Signal_Control/u_GenPWM/HDL_Counter2_count_next_carry_n_7 ;

  assign AXI4_Lite_BRESP[1] = \<const0> ;
  assign AXI4_Lite_BRESP[0] = \<const0> ;
  assign AXI4_Lite_RDATA[31] = \^AXI4_Lite_RDATA [27];
  assign AXI4_Lite_RDATA[30] = \^AXI4_Lite_RDATA [29];
  assign AXI4_Lite_RDATA[29] = \^AXI4_Lite_RDATA [29];
  assign AXI4_Lite_RDATA[28] = \^AXI4_Lite_RDATA [29];
  assign AXI4_Lite_RDATA[27] = \^AXI4_Lite_RDATA [27];
  assign AXI4_Lite_RDATA[26] = \^AXI4_Lite_RDATA [29];
  assign AXI4_Lite_RDATA[25] = \^AXI4_Lite_RDATA [29];
  assign AXI4_Lite_RDATA[24:0] = \^AXI4_Lite_RDATA [24:0];
  assign AXI4_Lite_RRESP[1] = \<const0> ;
  assign AXI4_Lite_RRESP[0] = \<const0> ;
  GND GND
       (.G(\<const0> ));
  zusys_PWM_and_SS_control_V_0_2_PWM_and_SS_control_V3_ip U0
       (.AXI4_Lite_ACLK(AXI4_Lite_ACLK),
        .AXI4_Lite_ARADDR(AXI4_Lite_ARADDR[15:2]),
        .AXI4_Lite_ARESETN(AXI4_Lite_ARESETN),
        .AXI4_Lite_ARREADY(AXI4_Lite_ARREADY),
        .AXI4_Lite_ARVALID(AXI4_Lite_ARVALID),
        .AXI4_Lite_AWADDR(AXI4_Lite_AWADDR[15:2]),
        .AXI4_Lite_AWREADY(AXI4_Lite_AWREADY),
        .AXI4_Lite_AWVALID(AXI4_Lite_AWVALID),
        .AXI4_Lite_BREADY(AXI4_Lite_BREADY),
        .AXI4_Lite_RDATA({\^AXI4_Lite_RDATA [27],\^AXI4_Lite_RDATA [29],\^AXI4_Lite_RDATA [24:0]}),
        .AXI4_Lite_RREADY(AXI4_Lite_RREADY),
        .AXI4_Lite_WDATA(AXI4_Lite_WDATA[24:0]),
        .AXI4_Lite_WSTRB(AXI4_Lite_WSTRB),
        .AXI4_Lite_WVALID(AXI4_Lite_WVALID),
        .B(\u_PWM_and_SS_control_V3_ip_dut_inst/u_PWM_and_SS_control_V3_ip_src_PWM_and_Switching_Signal_Control/u_GenPWM/HDL_Counter2_count_next ),
        .CO(\u_PWM_and_SS_control_V3_ip_src_PWM_and_Switching_Signal_Control/u_GenPWM/HDL_Counter2_count_next_carry_n_0 ),
        .DI({U0_n_11,U0_n_12}),
        .FSM_sequential_axi_lite_rstate_reg(AXI4_Lite_RVALID),
        .\HDL_Counter2_count_reg[7] ({\u_PWM_and_SS_control_V3_ip_dut_inst/u_PWM_and_SS_control_V3_ip_src_PWM_and_Switching_Signal_Control/u_GenPWM/HDL_Counter2_count_reg [7:2],\u_PWM_and_SS_control_V3_ip_dut_inst/u_PWM_and_SS_control_V3_ip_src_PWM_and_Switching_Signal_Control/u_GenPWM/HDL_Counter2_count_reg [0]}),
        .IPCORE_CLK(IPCORE_CLK),
        .IPCORE_RESETN(IPCORE_RESETN),
        .PWM_enb_out(PWM_enb_out),
        .Q({AXI4_Lite_BVALID,AXI4_Lite_WREADY}),
        .S({U0_n_13,U0_n_14,U0_n_15,U0_n_16,U0_n_17,U0_n_18,U0_n_19,U0_n_20}),
        .SS0_IN_External(SS0_IN_External),
        .SS0_OUT(SS0_OUT),
        .SS1_IN_External(SS1_IN_External),
        .SS1_OUT(SS1_OUT),
        .SS2_IN_External(SS2_IN_External),
        .SS2_OUT(SS2_OUT),
        .SS3_IN_External(SS3_IN_External),
        .SS3_OUT(SS3_OUT),
        .SS4_IN_External(SS4_IN_External),
        .SS4_OUT(SS4_OUT),
        .SS5_IN_External(SS5_IN_External),
        .SS5_OUT(SS5_OUT),
        .Triangular_Max(Triangular_Max),
        .Triangular_Min(Triangular_Min),
        .m_u1_norm(m_u1_norm),
        .m_u2_norm(m_u2_norm),
        .m_u3_norm(m_u3_norm));
  CARRY8 \u_PWM_and_SS_control_V3_ip_src_PWM_and_Switching_Signal_Control/u_GenPWM/HDL_Counter2_count_next_carry 
       (.CI(\u_PWM_and_SS_control_V3_ip_dut_inst/u_PWM_and_SS_control_V3_ip_src_PWM_and_Switching_Signal_Control/u_GenPWM/HDL_Counter2_count_reg [0]),
        .CI_TOP(1'b0),
        .CO({\u_PWM_and_SS_control_V3_ip_src_PWM_and_Switching_Signal_Control/u_GenPWM/HDL_Counter2_count_next_carry_n_0 ,\u_PWM_and_SS_control_V3_ip_src_PWM_and_Switching_Signal_Control/u_GenPWM/HDL_Counter2_count_next_carry_n_1 ,\u_PWM_and_SS_control_V3_ip_src_PWM_and_Switching_Signal_Control/u_GenPWM/HDL_Counter2_count_next_carry_n_2 ,\u_PWM_and_SS_control_V3_ip_src_PWM_and_Switching_Signal_Control/u_GenPWM/HDL_Counter2_count_next_carry_n_3 ,\u_PWM_and_SS_control_V3_ip_src_PWM_and_Switching_Signal_Control/u_GenPWM/HDL_Counter2_count_next_carry_n_4 ,\u_PWM_and_SS_control_V3_ip_src_PWM_and_Switching_Signal_Control/u_GenPWM/HDL_Counter2_count_next_carry_n_5 ,\u_PWM_and_SS_control_V3_ip_src_PWM_and_Switching_Signal_Control/u_GenPWM/HDL_Counter2_count_next_carry_n_6 ,\u_PWM_and_SS_control_V3_ip_src_PWM_and_Switching_Signal_Control/u_GenPWM/HDL_Counter2_count_next_carry_n_7 }),
        .DI({\u_PWM_and_SS_control_V3_ip_dut_inst/u_PWM_and_SS_control_V3_ip_src_PWM_and_Switching_Signal_Control/u_GenPWM/HDL_Counter2_count_reg [7:2],U0_n_11,U0_n_12}),
        .O(\u_PWM_and_SS_control_V3_ip_dut_inst/u_PWM_and_SS_control_V3_ip_src_PWM_and_Switching_Signal_Control/u_GenPWM/HDL_Counter2_count_next ),
        .S({U0_n_13,U0_n_14,U0_n_15,U0_n_16,U0_n_17,U0_n_18,U0_n_19,U0_n_20}));
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
