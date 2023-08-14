// Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// --------------------------------------------------------------------------------
// Tool Version: Vivado v.2020.1.1 (win64) Build 2960000 Wed Aug  5 22:57:20 MDT 2020
// Date        : Fri Jan 28 14:50:37 2022
// Host        : enc177112 running 64-bit major release  (build 9200)
// Command     : write_verilog -force -mode funcsim
//               c:/GIT/UltraZohm/software/ultrazohm_sw_develop/vivado/zusys/ip/zusys_A3_ADC_LTC2311_0/zusys_A3_ADC_LTC2311_0_sim_netlist.v
// Design      : zusys_A3_ADC_LTC2311_0
// Purpose     : This verilog netlist is a functional simulation representation of the design and should not be modified
//               or synthesized. This netlist cannot be used for SDF annotated simulation.
// Device      : xczu9eg-ffvc900-1-e
// --------------------------------------------------------------------------------
`timescale 1 ps / 1 ps

(* CHECK_LICENSE_TYPE = "zusys_A3_ADC_LTC2311_0,ADC_LTC2311_v3_0,{}" *) (* downgradeipidentifiedwarnings = "yes" *) (* x_core_info = "ADC_LTC2311_v3_0,Vivado 2020.1.1" *) 
(* NotValidForBitStream *)
module zusys_A3_ADC_LTC2311_0
   (RAW_VALUE,
    RAW_VALID,
    SI_VALUE,
    SI_VALID,
    TRIGGER_CNV,
    SAMPLE_COUNTER,
    SS_N,
    SCLK_DIFF,
    MISO_DIFF,
    s00_axi_aclk,
    s00_axi_aresetn,
    s00_axi_awaddr,
    s00_axi_awprot,
    s00_axi_awvalid,
    s00_axi_awready,
    s00_axi_wdata,
    s00_axi_wstrb,
    s00_axi_wvalid,
    s00_axi_wready,
    s00_axi_bresp,
    s00_axi_bvalid,
    s00_axi_bready,
    s00_axi_araddr,
    s00_axi_arprot,
    s00_axi_arvalid,
    s00_axi_arready,
    s00_axi_rdata,
    s00_axi_rresp,
    s00_axi_rvalid,
    s00_axi_rready);
  output [127:0]RAW_VALUE;
  output [0:0]RAW_VALID;
  output [279:0]SI_VALUE;
  output [0:0]SI_VALID;
  input [0:0]TRIGGER_CNV;
  output [31:0]SAMPLE_COUNTER;
  output [0:0]SS_N;
  output [1:0]SCLK_DIFF;
  input [15:0]MISO_DIFF;
  (* x_interface_info = "xilinx.com:signal:clock:1.0 S00_AXI_CLK CLK" *) (* x_interface_parameter = "XIL_INTERFACENAME S00_AXI_CLK, ASSOCIATED_BUSIF S00_AXI, ASSOCIATED_RESET s00_axi_aresetn, FREQ_HZ 100000000, FREQ_TOLERANCE_HZ 0, PHASE 0.000, CLK_DOMAIN zusys_zynq_ultra_ps_e_0_0_pl_clk0, INSERT_VIP 0" *) input s00_axi_aclk;
  (* x_interface_info = "xilinx.com:signal:reset:1.0 S00_AXI_RST RST" *) (* x_interface_parameter = "XIL_INTERFACENAME S00_AXI_RST, POLARITY ACTIVE_LOW, INSERT_VIP 0" *) input s00_axi_aresetn;
  (* x_interface_info = "xilinx.com:interface:aximm:1.0 S00_AXI AWADDR" *) (* x_interface_parameter = "XIL_INTERFACENAME S00_AXI, WIZ_DATA_WIDTH 32, WIZ_NUM_REG 4, SUPPORTS_NARROW_BURST 0, DATA_WIDTH 32, PROTOCOL AXI4LITE, FREQ_HZ 100000000, ID_WIDTH 0, ADDR_WIDTH 6, AWUSER_WIDTH 0, ARUSER_WIDTH 0, WUSER_WIDTH 0, RUSER_WIDTH 0, BUSER_WIDTH 0, READ_WRITE_MODE READ_WRITE, HAS_BURST 0, HAS_LOCK 0, HAS_PROT 1, HAS_CACHE 0, HAS_QOS 0, HAS_REGION 0, HAS_WSTRB 1, HAS_BRESP 1, HAS_RRESP 1, NUM_READ_OUTSTANDING 8, NUM_WRITE_OUTSTANDING 8, MAX_BURST_LENGTH 1, PHASE 0.000, CLK_DOMAIN zusys_zynq_ultra_ps_e_0_0_pl_clk0, NUM_READ_THREADS 1, NUM_WRITE_THREADS 1, RUSER_BITS_PER_BYTE 0, WUSER_BITS_PER_BYTE 0, INSERT_VIP 0" *) input [5:0]s00_axi_awaddr;
  (* x_interface_info = "xilinx.com:interface:aximm:1.0 S00_AXI AWPROT" *) input [2:0]s00_axi_awprot;
  (* x_interface_info = "xilinx.com:interface:aximm:1.0 S00_AXI AWVALID" *) input s00_axi_awvalid;
  (* x_interface_info = "xilinx.com:interface:aximm:1.0 S00_AXI AWREADY" *) output s00_axi_awready;
  (* x_interface_info = "xilinx.com:interface:aximm:1.0 S00_AXI WDATA" *) input [31:0]s00_axi_wdata;
  (* x_interface_info = "xilinx.com:interface:aximm:1.0 S00_AXI WSTRB" *) input [3:0]s00_axi_wstrb;
  (* x_interface_info = "xilinx.com:interface:aximm:1.0 S00_AXI WVALID" *) input s00_axi_wvalid;
  (* x_interface_info = "xilinx.com:interface:aximm:1.0 S00_AXI WREADY" *) output s00_axi_wready;
  (* x_interface_info = "xilinx.com:interface:aximm:1.0 S00_AXI BRESP" *) output [1:0]s00_axi_bresp;
  (* x_interface_info = "xilinx.com:interface:aximm:1.0 S00_AXI BVALID" *) output s00_axi_bvalid;
  (* x_interface_info = "xilinx.com:interface:aximm:1.0 S00_AXI BREADY" *) input s00_axi_bready;
  (* x_interface_info = "xilinx.com:interface:aximm:1.0 S00_AXI ARADDR" *) input [5:0]s00_axi_araddr;
  (* x_interface_info = "xilinx.com:interface:aximm:1.0 S00_AXI ARPROT" *) input [2:0]s00_axi_arprot;
  (* x_interface_info = "xilinx.com:interface:aximm:1.0 S00_AXI ARVALID" *) input s00_axi_arvalid;
  (* x_interface_info = "xilinx.com:interface:aximm:1.0 S00_AXI ARREADY" *) output s00_axi_arready;
  (* x_interface_info = "xilinx.com:interface:aximm:1.0 S00_AXI RDATA" *) output [31:0]s00_axi_rdata;
  (* x_interface_info = "xilinx.com:interface:aximm:1.0 S00_AXI RRESP" *) output [1:0]s00_axi_rresp;
  (* x_interface_info = "xilinx.com:interface:aximm:1.0 S00_AXI RVALID" *) output s00_axi_rvalid;
  (* x_interface_info = "xilinx.com:interface:aximm:1.0 S00_AXI RREADY" *) input s00_axi_rready;

  wire \<const0> ;
  (* DIFF_TERM_ADV = "TERM_100" *) (* IBUF_LOW_PWR *) wire [15:0]MISO_DIFF;
  wire [0:0]RAW_VALID;
  wire [127:0]RAW_VALUE;
  wire [31:0]SAMPLE_COUNTER;
  (* SLEW = "SLOW" *) wire [1:0]SCLK_DIFF;
  wire [0:0]SI_VALID;
  wire [279:0]SI_VALUE;
  wire [0:0]SS_N;
  wire [0:0]TRIGGER_CNV;
  wire s00_axi_aclk;
  wire [5:0]s00_axi_araddr;
  wire s00_axi_aresetn;
  wire s00_axi_arready;
  wire s00_axi_arvalid;
  wire [5:0]s00_axi_awaddr;
  wire s00_axi_awready;
  wire s00_axi_awvalid;
  wire s00_axi_bready;
  wire s00_axi_bvalid;
  wire [31:0]s00_axi_rdata;
  wire s00_axi_rready;
  wire s00_axi_rvalid;
  wire [31:0]s00_axi_wdata;
  wire s00_axi_wready;
  wire [3:0]s00_axi_wstrb;
  wire s00_axi_wvalid;

  assign s00_axi_bresp[1] = \<const0> ;
  assign s00_axi_bresp[0] = \<const0> ;
  assign s00_axi_rresp[1] = \<const0> ;
  assign s00_axi_rresp[0] = \<const0> ;
  GND GND
       (.G(\<const0> ));
  zusys_A3_ADC_LTC2311_0_ADC_LTC2311_v3_0 U0
       (.MISO_DIFF(MISO_DIFF),
        .RAW_VALID(RAW_VALID),
        .RAW_VALUE(RAW_VALUE),
        .SAMPLE_COUNTER(SAMPLE_COUNTER[31:1]),
        .SCLK_DIFF(SCLK_DIFF),
        .SI_VALID(SI_VALID),
        .SI_VALUE(SI_VALUE),
        .SS_N(SS_N),
        .\S_SAMPLE_COUNTER_reg[0] (SAMPLE_COUNTER[0]),
        .TRIGGER_CNV(TRIGGER_CNV),
        .s00_axi_aclk(s00_axi_aclk),
        .s00_axi_araddr(s00_axi_araddr[5:2]),
        .s00_axi_aresetn(s00_axi_aresetn),
        .s00_axi_arready(s00_axi_arready),
        .s00_axi_arvalid(s00_axi_arvalid),
        .s00_axi_awaddr(s00_axi_awaddr[5:2]),
        .s00_axi_awready(s00_axi_awready),
        .s00_axi_awvalid(s00_axi_awvalid),
        .s00_axi_bready(s00_axi_bready),
        .s00_axi_bvalid(s00_axi_bvalid),
        .s00_axi_rdata(s00_axi_rdata),
        .s00_axi_rready(s00_axi_rready),
        .s00_axi_rvalid(s00_axi_rvalid),
        .s00_axi_wdata(s00_axi_wdata),
        .s00_axi_wready(s00_axi_wready),
        .s00_axi_wstrb(s00_axi_wstrb),
        .s00_axi_wvalid(s00_axi_wvalid));
endmodule

(* ORIG_REF_NAME = "ADC_CONTROLLER" *) 
module zusys_A3_ADC_LTC2311_0_ADC_CONTROLLER
   (S_SCLK,
    SS_N,
    S_SPI_BUSY,
    SI_VALID,
    \S_ENABLE_reg[0] ,
    S_DUMMY_SAMPLE,
    RAW_VALID,
    BUSY,
    S_MANUAL_reg_0,
    S_SPI_ENABLE_reg_0,
    \S_ENABLE_reg[0]_0 ,
    Q,
    \S_SAMPLE_COUNTER_reg[0]_0 ,
    \S_ENABLE_reg[0]_1 ,
    E,
    S,
    \S_SAMPLE_COUNTER_reg[16]_0 ,
    \S_SAMPLE_COUNTER_reg[24]_0 ,
    \S_SAMPLE_COUNTER_reg[31]_0 ,
    RAW_VALUE,
    SI_VALUE,
    CPHA,
    s00_axi_aclk,
    CPOL,
    RSTP,
    S_DUMMY_SAMPLE_reg_0,
    RAW_VALID_reg_0,
    BUSY_reg_0,
    S_MANUAL_reg_1,
    S_SPI_ENABLE_reg_1,
    S_CPOL_reg,
    s00_axi_aresetn,
    S_AXI_ARESETN,
    \S_DEL_COUNT_reg[7] ,
    SCLK_IN,
    SS_IN_N,
    ENABLE,
    SET_SAMPLES,
    SET_CONVERSION,
    SET_OFFSET,
    D,
    \S_SAMPLE_TIME_reg[30]_0 ,
    \S_SAMPLE_TIME_reg[30]_1 ,
    \S_CONVERSION_reg[126]_0 ,
    \S_OFFSET_reg[112]_0 );
  output S_SCLK;
  output [0:0]SS_N;
  output S_SPI_BUSY;
  output [0:0]SI_VALID;
  output \S_ENABLE_reg[0] ;
  output S_DUMMY_SAMPLE;
  output [0:0]RAW_VALID;
  output BUSY;
  output S_MANUAL_reg_0;
  output S_SPI_ENABLE_reg_0;
  output \S_ENABLE_reg[0]_0 ;
  output [1:0]Q;
  output \S_SAMPLE_COUNTER_reg[0]_0 ;
  output \S_ENABLE_reg[0]_1 ;
  output [0:0]E;
  output [7:0]S;
  output [7:0]\S_SAMPLE_COUNTER_reg[16]_0 ;
  output [7:0]\S_SAMPLE_COUNTER_reg[24]_0 ;
  output [6:0]\S_SAMPLE_COUNTER_reg[31]_0 ;
  output [127:0]RAW_VALUE;
  output [279:0]SI_VALUE;
  input CPHA;
  input s00_axi_aclk;
  input CPOL;
  input RSTP;
  input S_DUMMY_SAMPLE_reg_0;
  input RAW_VALID_reg_0;
  input BUSY_reg_0;
  input S_MANUAL_reg_1;
  input S_SPI_ENABLE_reg_1;
  input [0:0]S_CPOL_reg;
  input s00_axi_aresetn;
  input S_AXI_ARESETN;
  input [31:0]\S_DEL_COUNT_reg[7] ;
  input SCLK_IN;
  input SS_IN_N;
  input ENABLE;
  input SET_SAMPLES;
  input SET_CONVERSION;
  input SET_OFFSET;
  input [7:0]D;
  input [0:0]\S_SAMPLE_TIME_reg[30]_0 ;
  input [30:0]\S_SAMPLE_TIME_reg[30]_1 ;
  input [7:0]\S_CONVERSION_reg[126]_0 ;
  input [7:0]\S_OFFSET_reg[112]_0 ;

  wire [3:2]B;
  wire BUSY;
  wire BUSY_reg_0;
  wire CEB2;
  wire CPHA;
  wire CPOL;
  wire [7:0]D;
  wire [0:0]E;
  wire ENABLE;
  wire [1:0]Q;
  wire [0:0]RAW_VALID;
  wire RAW_VALID_reg_0;
  wire [127:0]RAW_VALUE;
  wire RSTP;
  wire [7:0]S;
  wire SCLK_IN;
  wire SET_CONVERSION;
  wire SET_OFFSET;
  wire SET_SAMPLES;
  wire [0:0]SI_VALID;
  wire SI_VALID_i_1_n_0;
  wire SI_VALID_i_53_n_0;
  wire SI_VALID_i_54_n_0;
  wire SI_VALID_i_55_n_0;
  wire SI_VALID_i_56_n_0;
  wire SI_VALID_i_57_n_0;
  wire SI_VALID_i_58_n_0;
  wire SI_VALID_i_59_n_0;
  wire SI_VALID_i_60_n_0;
  wire SI_VALID_i_61_n_0;
  wire SI_VALID_i_62_n_0;
  wire SI_VALID_i_63_n_0;
  wire SI_VALID_i_64_n_0;
  wire SI_VALID_i_65_n_0;
  wire SI_VALID_i_66_n_0;
  wire SI_VALID_i_67_n_0;
  wire SI_VALID_i_68_n_0;
  wire SI_VALID_i_69_n_0;
  wire SI_VALID_i_70_n_0;
  wire SI_VALID_i_71_n_0;
  wire SI_VALID_i_72_n_0;
  wire SI_VALID_i_73_n_0;
  wire SI_VALID_i_74_n_0;
  wire SI_VALID_i_75_n_0;
  wire SI_VALID_i_76_n_0;
  wire SI_VALID_i_77_n_0;
  wire SI_VALID_i_78_n_0;
  wire SI_VALID_i_79_n_0;
  wire SI_VALID_i_80_n_0;
  wire SI_VALID_i_81_n_0;
  wire SI_VALID_i_82_n_0;
  wire SI_VALID_reg_i_49_n_1;
  wire SI_VALID_reg_i_49_n_3;
  wire SI_VALID_reg_i_49_n_4;
  wire SI_VALID_reg_i_49_n_5;
  wire SI_VALID_reg_i_49_n_6;
  wire SI_VALID_reg_i_49_n_7;
  wire SI_VALID_reg_i_50_n_0;
  wire SI_VALID_reg_i_50_n_1;
  wire SI_VALID_reg_i_50_n_2;
  wire SI_VALID_reg_i_50_n_3;
  wire SI_VALID_reg_i_50_n_4;
  wire SI_VALID_reg_i_50_n_5;
  wire SI_VALID_reg_i_50_n_6;
  wire SI_VALID_reg_i_50_n_7;
  wire SI_VALID_reg_i_51_n_0;
  wire SI_VALID_reg_i_51_n_1;
  wire SI_VALID_reg_i_51_n_2;
  wire SI_VALID_reg_i_51_n_3;
  wire SI_VALID_reg_i_51_n_4;
  wire SI_VALID_reg_i_51_n_5;
  wire SI_VALID_reg_i_51_n_6;
  wire SI_VALID_reg_i_51_n_7;
  wire SI_VALID_reg_i_52_n_0;
  wire SI_VALID_reg_i_52_n_1;
  wire SI_VALID_reg_i_52_n_2;
  wire SI_VALID_reg_i_52_n_3;
  wire SI_VALID_reg_i_52_n_4;
  wire SI_VALID_reg_i_52_n_5;
  wire SI_VALID_reg_i_52_n_6;
  wire SI_VALID_reg_i_52_n_7;
  wire [279:0]SI_VALUE;
  wire [279:0]SI_VALUE0;
  wire \SI_VALUE[180]_i_3_n_0 ;
  wire \SI_VALUE[270]_i_3_n_0 ;
  wire \SI_VALUE[273]_i_2_n_0 ;
  wire \SI_VALUE[273]_i_4_n_0 ;
  wire \SI_VALUE[279]_i_3_n_0 ;
  wire \SI_VALUE[279]_i_6_n_0 ;
  wire \SI_VALUE[279]_i_7_n_0 ;
  wire \SI_VALUE[34]_i_1_n_0 ;
  wire SS_IN_N;
  wire [0:0]SS_N;
  wire S_AXI_ARESETN;
  wire S_CE_CONVERSION;
  wire [3:0]S_CHANNEL_COUNTER;
  wire \S_CHANNEL_COUNTER[0]_i_1_n_0 ;
  wire \S_CHANNEL_COUNTER[1]_i_1_n_0 ;
  wire \S_CHANNEL_COUNTER[2]_i_1_n_0 ;
  wire \S_CHANNEL_COUNTER[3]_i_1_n_0 ;
  wire \S_CHANNEL_COUNTER[3]_i_2_n_0 ;
  wire [7:0]\S_CONVERSION_reg[126]_0 ;
  wire \S_CONVERSION_reg_n_0_[0] ;
  wire \S_CONVERSION_reg_n_0_[10] ;
  wire \S_CONVERSION_reg_n_0_[11] ;
  wire \S_CONVERSION_reg_n_0_[12] ;
  wire \S_CONVERSION_reg_n_0_[13] ;
  wire \S_CONVERSION_reg_n_0_[14] ;
  wire \S_CONVERSION_reg_n_0_[15] ;
  wire \S_CONVERSION_reg_n_0_[16] ;
  wire \S_CONVERSION_reg_n_0_[17] ;
  wire \S_CONVERSION_reg_n_0_[1] ;
  wire \S_CONVERSION_reg_n_0_[2] ;
  wire \S_CONVERSION_reg_n_0_[3] ;
  wire \S_CONVERSION_reg_n_0_[4] ;
  wire \S_CONVERSION_reg_n_0_[5] ;
  wire \S_CONVERSION_reg_n_0_[6] ;
  wire \S_CONVERSION_reg_n_0_[7] ;
  wire \S_CONVERSION_reg_n_0_[8] ;
  wire \S_CONVERSION_reg_n_0_[9] ;
  wire [3:0]S_CONV_COUNTER;
  wire \S_CONV_COUNTER[0]_i_1_n_0 ;
  wire \S_CONV_COUNTER[1]_i_1_n_0 ;
  wire \S_CONV_COUNTER[2]_i_1_n_0 ;
  wire \S_CONV_COUNTER[3]_i_1_n_0 ;
  wire \S_CONV_COUNTER[3]_i_2_n_0 ;
  wire [0:0]S_CPOL_reg;
  wire [31:0]\S_DEL_COUNT_reg[7] ;
  wire S_DUMMY_SAMPLE;
  wire S_DUMMY_SAMPLE_reg_0;
  wire \S_ENABLE_reg[0] ;
  wire \S_ENABLE_reg[0]_0 ;
  wire \S_ENABLE_reg[0]_1 ;
  wire S_MANUAL_reg_0;
  wire S_MANUAL_reg_1;
  wire [127:0]S_OFFSET;
  wire S_OFFSET_S_C;
  wire \S_OFFSET_S_C[0]_i_1_n_0 ;
  wire \S_OFFSET_S_C[0]_i_2_n_0 ;
  wire \S_OFFSET_S_C[0]_i_3_n_0 ;
  wire \S_OFFSET_S_C[10]_i_1_n_0 ;
  wire \S_OFFSET_S_C[10]_i_2_n_0 ;
  wire \S_OFFSET_S_C[10]_i_3_n_0 ;
  wire \S_OFFSET_S_C[11]_i_1_n_0 ;
  wire \S_OFFSET_S_C[11]_i_2_n_0 ;
  wire \S_OFFSET_S_C[11]_i_3_n_0 ;
  wire \S_OFFSET_S_C[12]_i_1_n_0 ;
  wire \S_OFFSET_S_C[12]_i_2_n_0 ;
  wire \S_OFFSET_S_C[12]_i_3_n_0 ;
  wire \S_OFFSET_S_C[13]_i_1_n_0 ;
  wire \S_OFFSET_S_C[13]_i_2_n_0 ;
  wire \S_OFFSET_S_C[13]_i_3_n_0 ;
  wire \S_OFFSET_S_C[14]_i_1_n_0 ;
  wire \S_OFFSET_S_C[14]_i_2_n_0 ;
  wire \S_OFFSET_S_C[14]_i_3_n_0 ;
  wire \S_OFFSET_S_C[15]_i_1_n_0 ;
  wire \S_OFFSET_S_C[15]_i_2_n_0 ;
  wire \S_OFFSET_S_C[15]_i_3_n_0 ;
  wire \S_OFFSET_S_C[1]_i_1_n_0 ;
  wire \S_OFFSET_S_C[1]_i_2_n_0 ;
  wire \S_OFFSET_S_C[1]_i_3_n_0 ;
  wire \S_OFFSET_S_C[2]_i_1_n_0 ;
  wire \S_OFFSET_S_C[2]_i_2_n_0 ;
  wire \S_OFFSET_S_C[2]_i_3_n_0 ;
  wire \S_OFFSET_S_C[3]_i_1_n_0 ;
  wire \S_OFFSET_S_C[3]_i_2_n_0 ;
  wire \S_OFFSET_S_C[3]_i_3_n_0 ;
  wire \S_OFFSET_S_C[4]_i_1_n_0 ;
  wire \S_OFFSET_S_C[4]_i_2_n_0 ;
  wire \S_OFFSET_S_C[4]_i_3_n_0 ;
  wire \S_OFFSET_S_C[5]_i_1_n_0 ;
  wire \S_OFFSET_S_C[5]_i_2_n_0 ;
  wire \S_OFFSET_S_C[5]_i_3_n_0 ;
  wire \S_OFFSET_S_C[6]_i_1_n_0 ;
  wire \S_OFFSET_S_C[6]_i_2_n_0 ;
  wire \S_OFFSET_S_C[6]_i_3_n_0 ;
  wire \S_OFFSET_S_C[7]_i_1_n_0 ;
  wire \S_OFFSET_S_C[7]_i_2_n_0 ;
  wire \S_OFFSET_S_C[7]_i_3_n_0 ;
  wire \S_OFFSET_S_C[8]_i_1_n_0 ;
  wire \S_OFFSET_S_C[8]_i_2_n_0 ;
  wire \S_OFFSET_S_C[8]_i_3_n_0 ;
  wire \S_OFFSET_S_C[9]_i_1_n_0 ;
  wire \S_OFFSET_S_C[9]_i_2_n_0 ;
  wire \S_OFFSET_S_C[9]_i_3_n_0 ;
  wire \S_OFFSET_S_C_reg_n_0_[0] ;
  wire \S_OFFSET_S_C_reg_n_0_[10] ;
  wire \S_OFFSET_S_C_reg_n_0_[11] ;
  wire \S_OFFSET_S_C_reg_n_0_[12] ;
  wire \S_OFFSET_S_C_reg_n_0_[13] ;
  wire \S_OFFSET_S_C_reg_n_0_[14] ;
  wire \S_OFFSET_S_C_reg_n_0_[15] ;
  wire \S_OFFSET_S_C_reg_n_0_[1] ;
  wire \S_OFFSET_S_C_reg_n_0_[2] ;
  wire \S_OFFSET_S_C_reg_n_0_[3] ;
  wire \S_OFFSET_S_C_reg_n_0_[4] ;
  wire \S_OFFSET_S_C_reg_n_0_[5] ;
  wire \S_OFFSET_S_C_reg_n_0_[6] ;
  wire \S_OFFSET_S_C_reg_n_0_[7] ;
  wire \S_OFFSET_S_C_reg_n_0_[8] ;
  wire \S_OFFSET_S_C_reg_n_0_[9] ;
  wire [7:0]\S_OFFSET_reg[112]_0 ;
  wire [15:0]S_RAW_VALUE_S_C;
  wire \S_RAW_VALUE_S_C[15]_i_3_n_0 ;
  wire [3:0]S_RESULT_COUNTER;
  wire \S_RESULT_COUNTER[0]_i_1_n_0 ;
  wire \S_RESULT_COUNTER[0]_rep_i_1_n_0 ;
  wire \S_RESULT_COUNTER[1]_i_1_n_0 ;
  wire \S_RESULT_COUNTER[1]_rep_i_1_n_0 ;
  wire \S_RESULT_COUNTER[3]_i_3_n_0 ;
  wire \S_RESULT_COUNTER_reg[0]_rep_n_0 ;
  wire \S_RESULT_COUNTER_reg[1]_rep_n_0 ;
  wire [33:33]S_RESULT_S_C;
  wire S_SAMPLES;
  wire \S_SAMPLES_reg_n_0_[0] ;
  wire \S_SAMPLES_reg_n_0_[10] ;
  wire \S_SAMPLES_reg_n_0_[11] ;
  wire \S_SAMPLES_reg_n_0_[12] ;
  wire \S_SAMPLES_reg_n_0_[13] ;
  wire \S_SAMPLES_reg_n_0_[14] ;
  wire \S_SAMPLES_reg_n_0_[15] ;
  wire \S_SAMPLES_reg_n_0_[16] ;
  wire \S_SAMPLES_reg_n_0_[17] ;
  wire \S_SAMPLES_reg_n_0_[18] ;
  wire \S_SAMPLES_reg_n_0_[19] ;
  wire \S_SAMPLES_reg_n_0_[1] ;
  wire \S_SAMPLES_reg_n_0_[20] ;
  wire \S_SAMPLES_reg_n_0_[21] ;
  wire \S_SAMPLES_reg_n_0_[22] ;
  wire \S_SAMPLES_reg_n_0_[23] ;
  wire \S_SAMPLES_reg_n_0_[24] ;
  wire \S_SAMPLES_reg_n_0_[25] ;
  wire \S_SAMPLES_reg_n_0_[26] ;
  wire \S_SAMPLES_reg_n_0_[27] ;
  wire \S_SAMPLES_reg_n_0_[28] ;
  wire \S_SAMPLES_reg_n_0_[29] ;
  wire \S_SAMPLES_reg_n_0_[2] ;
  wire \S_SAMPLES_reg_n_0_[30] ;
  wire \S_SAMPLES_reg_n_0_[3] ;
  wire \S_SAMPLES_reg_n_0_[4] ;
  wire \S_SAMPLES_reg_n_0_[5] ;
  wire \S_SAMPLES_reg_n_0_[6] ;
  wire \S_SAMPLES_reg_n_0_[7] ;
  wire \S_SAMPLES_reg_n_0_[8] ;
  wire \S_SAMPLES_reg_n_0_[9] ;
  wire S_SAMPLE_COUNTER;
  wire \S_SAMPLE_COUNTER[0]_i_1_n_0 ;
  wire \S_SAMPLE_COUNTER[10]_i_1_n_0 ;
  wire \S_SAMPLE_COUNTER[11]_i_1_n_0 ;
  wire \S_SAMPLE_COUNTER[12]_i_1_n_0 ;
  wire \S_SAMPLE_COUNTER[13]_i_1_n_0 ;
  wire \S_SAMPLE_COUNTER[14]_i_1_n_0 ;
  wire \S_SAMPLE_COUNTER[15]_i_1_n_0 ;
  wire \S_SAMPLE_COUNTER[16]_i_1_n_0 ;
  wire \S_SAMPLE_COUNTER[17]_i_1_n_0 ;
  wire \S_SAMPLE_COUNTER[18]_i_1_n_0 ;
  wire \S_SAMPLE_COUNTER[19]_i_1_n_0 ;
  wire \S_SAMPLE_COUNTER[1]_i_1_n_0 ;
  wire \S_SAMPLE_COUNTER[20]_i_1_n_0 ;
  wire \S_SAMPLE_COUNTER[21]_i_1_n_0 ;
  wire \S_SAMPLE_COUNTER[22]_i_1_n_0 ;
  wire \S_SAMPLE_COUNTER[23]_i_1_n_0 ;
  wire \S_SAMPLE_COUNTER[24]_i_1_n_0 ;
  wire \S_SAMPLE_COUNTER[25]_i_1_n_0 ;
  wire \S_SAMPLE_COUNTER[26]_i_1_n_0 ;
  wire \S_SAMPLE_COUNTER[27]_i_1_n_0 ;
  wire \S_SAMPLE_COUNTER[28]_i_1_n_0 ;
  wire \S_SAMPLE_COUNTER[29]_i_1_n_0 ;
  wire \S_SAMPLE_COUNTER[2]_i_1_n_0 ;
  wire \S_SAMPLE_COUNTER[30]_i_1_n_0 ;
  wire \S_SAMPLE_COUNTER[31]_i_1_n_0 ;
  wire \S_SAMPLE_COUNTER[31]_i_3_n_0 ;
  wire \S_SAMPLE_COUNTER[3]_i_1_n_0 ;
  wire \S_SAMPLE_COUNTER[4]_i_1_n_0 ;
  wire \S_SAMPLE_COUNTER[5]_i_1_n_0 ;
  wire \S_SAMPLE_COUNTER[6]_i_1_n_0 ;
  wire \S_SAMPLE_COUNTER[7]_i_1_n_0 ;
  wire \S_SAMPLE_COUNTER[8]_i_1_n_0 ;
  wire \S_SAMPLE_COUNTER[9]_i_1_n_0 ;
  wire \S_SAMPLE_COUNTER_reg[0]_0 ;
  wire [7:0]\S_SAMPLE_COUNTER_reg[16]_0 ;
  wire \S_SAMPLE_COUNTER_reg[16]_i_2_n_0 ;
  wire \S_SAMPLE_COUNTER_reg[16]_i_2_n_1 ;
  wire \S_SAMPLE_COUNTER_reg[16]_i_2_n_2 ;
  wire \S_SAMPLE_COUNTER_reg[16]_i_2_n_3 ;
  wire \S_SAMPLE_COUNTER_reg[16]_i_2_n_4 ;
  wire \S_SAMPLE_COUNTER_reg[16]_i_2_n_5 ;
  wire \S_SAMPLE_COUNTER_reg[16]_i_2_n_6 ;
  wire \S_SAMPLE_COUNTER_reg[16]_i_2_n_7 ;
  wire [7:0]\S_SAMPLE_COUNTER_reg[24]_0 ;
  wire \S_SAMPLE_COUNTER_reg[24]_i_2_n_0 ;
  wire \S_SAMPLE_COUNTER_reg[24]_i_2_n_1 ;
  wire \S_SAMPLE_COUNTER_reg[24]_i_2_n_2 ;
  wire \S_SAMPLE_COUNTER_reg[24]_i_2_n_3 ;
  wire \S_SAMPLE_COUNTER_reg[24]_i_2_n_4 ;
  wire \S_SAMPLE_COUNTER_reg[24]_i_2_n_5 ;
  wire \S_SAMPLE_COUNTER_reg[24]_i_2_n_6 ;
  wire \S_SAMPLE_COUNTER_reg[24]_i_2_n_7 ;
  wire \S_SAMPLE_COUNTER_reg[30]_i_2_n_2 ;
  wire \S_SAMPLE_COUNTER_reg[30]_i_2_n_3 ;
  wire \S_SAMPLE_COUNTER_reg[30]_i_2_n_4 ;
  wire \S_SAMPLE_COUNTER_reg[30]_i_2_n_5 ;
  wire \S_SAMPLE_COUNTER_reg[30]_i_2_n_6 ;
  wire \S_SAMPLE_COUNTER_reg[30]_i_2_n_7 ;
  wire [6:0]\S_SAMPLE_COUNTER_reg[31]_0 ;
  wire \S_SAMPLE_COUNTER_reg[8]_i_2_n_0 ;
  wire \S_SAMPLE_COUNTER_reg[8]_i_2_n_1 ;
  wire \S_SAMPLE_COUNTER_reg[8]_i_2_n_2 ;
  wire \S_SAMPLE_COUNTER_reg[8]_i_2_n_3 ;
  wire \S_SAMPLE_COUNTER_reg[8]_i_2_n_4 ;
  wire \S_SAMPLE_COUNTER_reg[8]_i_2_n_5 ;
  wire \S_SAMPLE_COUNTER_reg[8]_i_2_n_6 ;
  wire \S_SAMPLE_COUNTER_reg[8]_i_2_n_7 ;
  wire [30:0]S_SAMPLE_TIME_COUNTER;
  wire [30:1]S_SAMPLE_TIME_COUNTER0__0;
  wire \S_SAMPLE_TIME_COUNTER[16]_i_10_n_0 ;
  wire \S_SAMPLE_TIME_COUNTER[16]_i_3_n_0 ;
  wire \S_SAMPLE_TIME_COUNTER[16]_i_4_n_0 ;
  wire \S_SAMPLE_TIME_COUNTER[16]_i_5_n_0 ;
  wire \S_SAMPLE_TIME_COUNTER[16]_i_6_n_0 ;
  wire \S_SAMPLE_TIME_COUNTER[16]_i_7_n_0 ;
  wire \S_SAMPLE_TIME_COUNTER[16]_i_8_n_0 ;
  wire \S_SAMPLE_TIME_COUNTER[16]_i_9_n_0 ;
  wire \S_SAMPLE_TIME_COUNTER[24]_i_10_n_0 ;
  wire \S_SAMPLE_TIME_COUNTER[24]_i_3_n_0 ;
  wire \S_SAMPLE_TIME_COUNTER[24]_i_4_n_0 ;
  wire \S_SAMPLE_TIME_COUNTER[24]_i_5_n_0 ;
  wire \S_SAMPLE_TIME_COUNTER[24]_i_6_n_0 ;
  wire \S_SAMPLE_TIME_COUNTER[24]_i_7_n_0 ;
  wire \S_SAMPLE_TIME_COUNTER[24]_i_8_n_0 ;
  wire \S_SAMPLE_TIME_COUNTER[24]_i_9_n_0 ;
  wire \S_SAMPLE_TIME_COUNTER[30]_i_10_n_0 ;
  wire \S_SAMPLE_TIME_COUNTER[30]_i_11_n_0 ;
  wire \S_SAMPLE_TIME_COUNTER[30]_i_12_n_0 ;
  wire \S_SAMPLE_TIME_COUNTER[30]_i_13_n_0 ;
  wire \S_SAMPLE_TIME_COUNTER[30]_i_3_n_0 ;
  wire \S_SAMPLE_TIME_COUNTER[30]_i_4_n_0 ;
  wire \S_SAMPLE_TIME_COUNTER[30]_i_6_n_0 ;
  wire \S_SAMPLE_TIME_COUNTER[30]_i_7_n_0 ;
  wire \S_SAMPLE_TIME_COUNTER[30]_i_8_n_0 ;
  wire \S_SAMPLE_TIME_COUNTER[30]_i_9_n_0 ;
  wire \S_SAMPLE_TIME_COUNTER[8]_i_10_n_0 ;
  wire \S_SAMPLE_TIME_COUNTER[8]_i_3_n_0 ;
  wire \S_SAMPLE_TIME_COUNTER[8]_i_4_n_0 ;
  wire \S_SAMPLE_TIME_COUNTER[8]_i_5_n_0 ;
  wire \S_SAMPLE_TIME_COUNTER[8]_i_6_n_0 ;
  wire \S_SAMPLE_TIME_COUNTER[8]_i_7_n_0 ;
  wire \S_SAMPLE_TIME_COUNTER[8]_i_8_n_0 ;
  wire \S_SAMPLE_TIME_COUNTER[8]_i_9_n_0 ;
  wire \S_SAMPLE_TIME_COUNTER_reg[16]_i_2_n_0 ;
  wire \S_SAMPLE_TIME_COUNTER_reg[16]_i_2_n_1 ;
  wire \S_SAMPLE_TIME_COUNTER_reg[16]_i_2_n_2 ;
  wire \S_SAMPLE_TIME_COUNTER_reg[16]_i_2_n_3 ;
  wire \S_SAMPLE_TIME_COUNTER_reg[16]_i_2_n_4 ;
  wire \S_SAMPLE_TIME_COUNTER_reg[16]_i_2_n_5 ;
  wire \S_SAMPLE_TIME_COUNTER_reg[16]_i_2_n_6 ;
  wire \S_SAMPLE_TIME_COUNTER_reg[16]_i_2_n_7 ;
  wire \S_SAMPLE_TIME_COUNTER_reg[24]_i_2_n_0 ;
  wire \S_SAMPLE_TIME_COUNTER_reg[24]_i_2_n_1 ;
  wire \S_SAMPLE_TIME_COUNTER_reg[24]_i_2_n_2 ;
  wire \S_SAMPLE_TIME_COUNTER_reg[24]_i_2_n_3 ;
  wire \S_SAMPLE_TIME_COUNTER_reg[24]_i_2_n_4 ;
  wire \S_SAMPLE_TIME_COUNTER_reg[24]_i_2_n_5 ;
  wire \S_SAMPLE_TIME_COUNTER_reg[24]_i_2_n_6 ;
  wire \S_SAMPLE_TIME_COUNTER_reg[24]_i_2_n_7 ;
  wire \S_SAMPLE_TIME_COUNTER_reg[30]_i_5_n_3 ;
  wire \S_SAMPLE_TIME_COUNTER_reg[30]_i_5_n_4 ;
  wire \S_SAMPLE_TIME_COUNTER_reg[30]_i_5_n_5 ;
  wire \S_SAMPLE_TIME_COUNTER_reg[30]_i_5_n_6 ;
  wire \S_SAMPLE_TIME_COUNTER_reg[30]_i_5_n_7 ;
  wire \S_SAMPLE_TIME_COUNTER_reg[8]_i_2_n_0 ;
  wire \S_SAMPLE_TIME_COUNTER_reg[8]_i_2_n_1 ;
  wire \S_SAMPLE_TIME_COUNTER_reg[8]_i_2_n_2 ;
  wire \S_SAMPLE_TIME_COUNTER_reg[8]_i_2_n_3 ;
  wire \S_SAMPLE_TIME_COUNTER_reg[8]_i_2_n_4 ;
  wire \S_SAMPLE_TIME_COUNTER_reg[8]_i_2_n_5 ;
  wire \S_SAMPLE_TIME_COUNTER_reg[8]_i_2_n_6 ;
  wire \S_SAMPLE_TIME_COUNTER_reg[8]_i_2_n_7 ;
  wire [0:0]\S_SAMPLE_TIME_reg[30]_0 ;
  wire [30:0]\S_SAMPLE_TIME_reg[30]_1 ;
  wire \S_SAMPLE_TIME_reg_n_0_[0] ;
  wire \S_SAMPLE_TIME_reg_n_0_[10] ;
  wire \S_SAMPLE_TIME_reg_n_0_[11] ;
  wire \S_SAMPLE_TIME_reg_n_0_[12] ;
  wire \S_SAMPLE_TIME_reg_n_0_[13] ;
  wire \S_SAMPLE_TIME_reg_n_0_[14] ;
  wire \S_SAMPLE_TIME_reg_n_0_[15] ;
  wire \S_SAMPLE_TIME_reg_n_0_[16] ;
  wire \S_SAMPLE_TIME_reg_n_0_[17] ;
  wire \S_SAMPLE_TIME_reg_n_0_[18] ;
  wire \S_SAMPLE_TIME_reg_n_0_[19] ;
  wire \S_SAMPLE_TIME_reg_n_0_[1] ;
  wire \S_SAMPLE_TIME_reg_n_0_[20] ;
  wire \S_SAMPLE_TIME_reg_n_0_[21] ;
  wire \S_SAMPLE_TIME_reg_n_0_[22] ;
  wire \S_SAMPLE_TIME_reg_n_0_[23] ;
  wire \S_SAMPLE_TIME_reg_n_0_[24] ;
  wire \S_SAMPLE_TIME_reg_n_0_[25] ;
  wire \S_SAMPLE_TIME_reg_n_0_[26] ;
  wire \S_SAMPLE_TIME_reg_n_0_[27] ;
  wire \S_SAMPLE_TIME_reg_n_0_[28] ;
  wire \S_SAMPLE_TIME_reg_n_0_[29] ;
  wire \S_SAMPLE_TIME_reg_n_0_[2] ;
  wire \S_SAMPLE_TIME_reg_n_0_[30] ;
  wire \S_SAMPLE_TIME_reg_n_0_[3] ;
  wire \S_SAMPLE_TIME_reg_n_0_[4] ;
  wire \S_SAMPLE_TIME_reg_n_0_[5] ;
  wire \S_SAMPLE_TIME_reg_n_0_[6] ;
  wire \S_SAMPLE_TIME_reg_n_0_[7] ;
  wire \S_SAMPLE_TIME_reg_n_0_[8] ;
  wire \S_SAMPLE_TIME_reg_n_0_[9] ;
  wire S_SCLK;
  wire S_SPI_BUSY;
  wire [1:0]S_SPI_BUSY_PIPE;
  wire \S_SPI_BUSY_PIPE[1]_i_2_n_0 ;
  wire S_SPI_ENABLE_reg_0;
  wire S_SPI_ENABLE_reg_1;
  wire [31:1]V_SAMPLE_COUNTER2;
  wire [17:0]data2;
  wire [17:0]data3;
  wire [17:0]data4;
  wire [17:0]data5;
  wire [17:0]data6;
  wire [17:0]data7;
  wire [17:0]data8;
  wire [1:0]nxtstate;
  wire nxtstate22_in;
  wire [30:1]nxtstate3;
  wire [279:69]p_1_in;
  wire [30:0]p_2_in;
  wire raw_to_si_n_1;
  wire raw_to_si_n_133;
  wire raw_to_si_n_134;
  wire raw_to_si_n_135;
  wire raw_to_si_n_136;
  wire raw_to_si_n_137;
  wire s00_axi_aclk;
  wire s00_axi_aresetn;
  wire spi_n_10;
  wire spi_n_11;
  wire spi_n_12;
  wire spi_n_13;
  wire spi_n_14;
  wire spi_n_15;
  wire spi_n_16;
  wire spi_n_17;
  wire spi_n_18;
  wire spi_n_19;
  wire spi_n_20;
  wire spi_n_3;
  wire spi_n_4;
  wire spi_n_5;
  wire spi_n_6;
  wire spi_n_7;
  wire spi_n_8;
  wire spi_n_9;
  wire [7:5]NLW_SI_VALID_reg_i_49_CO_UNCONNECTED;
  wire [7:6]NLW_SI_VALID_reg_i_49_O_UNCONNECTED;
  wire [7:6]\NLW_S_SAMPLE_COUNTER_reg[30]_i_2_CO_UNCONNECTED ;
  wire [7:7]\NLW_S_SAMPLE_COUNTER_reg[30]_i_2_O_UNCONNECTED ;
  wire [7:5]\NLW_S_SAMPLE_TIME_COUNTER_reg[30]_i_5_CO_UNCONNECTED ;
  wire [7:6]\NLW_S_SAMPLE_TIME_COUNTER_reg[30]_i_5_O_UNCONNECTED ;

  FDRE BUSY_reg
       (.C(s00_axi_aclk),
        .CE(1'b1),
        .D(BUSY_reg_0),
        .Q(BUSY),
        .R(RSTP));
  FDRE RAW_VALID_reg
       (.C(s00_axi_aclk),
        .CE(1'b1),
        .D(RAW_VALID_reg_0),
        .Q(RAW_VALID),
        .R(RSTP));
  LUT4 #(
    .INIT(16'h4055)) 
    SI_VALID_i_1
       (.I0(\S_ENABLE_reg[0]_0 ),
        .I1(Q[1]),
        .I2(Q[0]),
        .I3(\S_ENABLE_reg[0] ),
        .O(SI_VALID_i_1_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    SI_VALID_i_53
       (.I0(\S_SAMPLES_reg_n_0_[30] ),
        .O(SI_VALID_i_53_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    SI_VALID_i_54
       (.I0(\S_SAMPLES_reg_n_0_[29] ),
        .O(SI_VALID_i_54_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    SI_VALID_i_55
       (.I0(\S_SAMPLES_reg_n_0_[28] ),
        .O(SI_VALID_i_55_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    SI_VALID_i_56
       (.I0(\S_SAMPLES_reg_n_0_[27] ),
        .O(SI_VALID_i_56_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    SI_VALID_i_57
       (.I0(\S_SAMPLES_reg_n_0_[26] ),
        .O(SI_VALID_i_57_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    SI_VALID_i_58
       (.I0(\S_SAMPLES_reg_n_0_[25] ),
        .O(SI_VALID_i_58_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    SI_VALID_i_59
       (.I0(\S_SAMPLES_reg_n_0_[24] ),
        .O(SI_VALID_i_59_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    SI_VALID_i_60
       (.I0(\S_SAMPLES_reg_n_0_[23] ),
        .O(SI_VALID_i_60_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    SI_VALID_i_61
       (.I0(\S_SAMPLES_reg_n_0_[22] ),
        .O(SI_VALID_i_61_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    SI_VALID_i_62
       (.I0(\S_SAMPLES_reg_n_0_[21] ),
        .O(SI_VALID_i_62_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    SI_VALID_i_63
       (.I0(\S_SAMPLES_reg_n_0_[20] ),
        .O(SI_VALID_i_63_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    SI_VALID_i_64
       (.I0(\S_SAMPLES_reg_n_0_[19] ),
        .O(SI_VALID_i_64_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    SI_VALID_i_65
       (.I0(\S_SAMPLES_reg_n_0_[18] ),
        .O(SI_VALID_i_65_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    SI_VALID_i_66
       (.I0(\S_SAMPLES_reg_n_0_[17] ),
        .O(SI_VALID_i_66_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    SI_VALID_i_67
       (.I0(\S_SAMPLES_reg_n_0_[16] ),
        .O(SI_VALID_i_67_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    SI_VALID_i_68
       (.I0(\S_SAMPLES_reg_n_0_[15] ),
        .O(SI_VALID_i_68_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    SI_VALID_i_69
       (.I0(\S_SAMPLES_reg_n_0_[14] ),
        .O(SI_VALID_i_69_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    SI_VALID_i_70
       (.I0(\S_SAMPLES_reg_n_0_[13] ),
        .O(SI_VALID_i_70_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    SI_VALID_i_71
       (.I0(\S_SAMPLES_reg_n_0_[12] ),
        .O(SI_VALID_i_71_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    SI_VALID_i_72
       (.I0(\S_SAMPLES_reg_n_0_[11] ),
        .O(SI_VALID_i_72_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    SI_VALID_i_73
       (.I0(\S_SAMPLES_reg_n_0_[10] ),
        .O(SI_VALID_i_73_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    SI_VALID_i_74
       (.I0(\S_SAMPLES_reg_n_0_[9] ),
        .O(SI_VALID_i_74_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    SI_VALID_i_75
       (.I0(\S_SAMPLES_reg_n_0_[8] ),
        .O(SI_VALID_i_75_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    SI_VALID_i_76
       (.I0(\S_SAMPLES_reg_n_0_[7] ),
        .O(SI_VALID_i_76_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    SI_VALID_i_77
       (.I0(\S_SAMPLES_reg_n_0_[6] ),
        .O(SI_VALID_i_77_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    SI_VALID_i_78
       (.I0(\S_SAMPLES_reg_n_0_[5] ),
        .O(SI_VALID_i_78_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    SI_VALID_i_79
       (.I0(\S_SAMPLES_reg_n_0_[4] ),
        .O(SI_VALID_i_79_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    SI_VALID_i_80
       (.I0(\S_SAMPLES_reg_n_0_[3] ),
        .O(SI_VALID_i_80_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    SI_VALID_i_81
       (.I0(\S_SAMPLES_reg_n_0_[2] ),
        .O(SI_VALID_i_81_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    SI_VALID_i_82
       (.I0(\S_SAMPLES_reg_n_0_[1] ),
        .O(SI_VALID_i_82_n_0));
  FDRE SI_VALID_reg
       (.C(s00_axi_aclk),
        .CE(SI_VALID_i_1_n_0),
        .D(\S_ENABLE_reg[0] ),
        .Q(SI_VALID),
        .R(RSTP));
  CARRY8 SI_VALID_reg_i_49
       (.CI(SI_VALID_reg_i_50_n_0),
        .CI_TOP(1'b0),
        .CO({NLW_SI_VALID_reg_i_49_CO_UNCONNECTED[7],SI_VALID_reg_i_49_n_1,NLW_SI_VALID_reg_i_49_CO_UNCONNECTED[5],SI_VALID_reg_i_49_n_3,SI_VALID_reg_i_49_n_4,SI_VALID_reg_i_49_n_5,SI_VALID_reg_i_49_n_6,SI_VALID_reg_i_49_n_7}),
        .DI({1'b0,1'b0,\S_SAMPLES_reg_n_0_[30] ,\S_SAMPLES_reg_n_0_[29] ,\S_SAMPLES_reg_n_0_[28] ,\S_SAMPLES_reg_n_0_[27] ,\S_SAMPLES_reg_n_0_[26] ,\S_SAMPLES_reg_n_0_[25] }),
        .O({NLW_SI_VALID_reg_i_49_O_UNCONNECTED[7:6],nxtstate3[30:25]}),
        .S({1'b0,1'b1,SI_VALID_i_53_n_0,SI_VALID_i_54_n_0,SI_VALID_i_55_n_0,SI_VALID_i_56_n_0,SI_VALID_i_57_n_0,SI_VALID_i_58_n_0}));
  CARRY8 SI_VALID_reg_i_50
       (.CI(SI_VALID_reg_i_51_n_0),
        .CI_TOP(1'b0),
        .CO({SI_VALID_reg_i_50_n_0,SI_VALID_reg_i_50_n_1,SI_VALID_reg_i_50_n_2,SI_VALID_reg_i_50_n_3,SI_VALID_reg_i_50_n_4,SI_VALID_reg_i_50_n_5,SI_VALID_reg_i_50_n_6,SI_VALID_reg_i_50_n_7}),
        .DI({\S_SAMPLES_reg_n_0_[24] ,\S_SAMPLES_reg_n_0_[23] ,\S_SAMPLES_reg_n_0_[22] ,\S_SAMPLES_reg_n_0_[21] ,\S_SAMPLES_reg_n_0_[20] ,\S_SAMPLES_reg_n_0_[19] ,\S_SAMPLES_reg_n_0_[18] ,\S_SAMPLES_reg_n_0_[17] }),
        .O(nxtstate3[24:17]),
        .S({SI_VALID_i_59_n_0,SI_VALID_i_60_n_0,SI_VALID_i_61_n_0,SI_VALID_i_62_n_0,SI_VALID_i_63_n_0,SI_VALID_i_64_n_0,SI_VALID_i_65_n_0,SI_VALID_i_66_n_0}));
  CARRY8 SI_VALID_reg_i_51
       (.CI(SI_VALID_reg_i_52_n_0),
        .CI_TOP(1'b0),
        .CO({SI_VALID_reg_i_51_n_0,SI_VALID_reg_i_51_n_1,SI_VALID_reg_i_51_n_2,SI_VALID_reg_i_51_n_3,SI_VALID_reg_i_51_n_4,SI_VALID_reg_i_51_n_5,SI_VALID_reg_i_51_n_6,SI_VALID_reg_i_51_n_7}),
        .DI({\S_SAMPLES_reg_n_0_[16] ,\S_SAMPLES_reg_n_0_[15] ,\S_SAMPLES_reg_n_0_[14] ,\S_SAMPLES_reg_n_0_[13] ,\S_SAMPLES_reg_n_0_[12] ,\S_SAMPLES_reg_n_0_[11] ,\S_SAMPLES_reg_n_0_[10] ,\S_SAMPLES_reg_n_0_[9] }),
        .O(nxtstate3[16:9]),
        .S({SI_VALID_i_67_n_0,SI_VALID_i_68_n_0,SI_VALID_i_69_n_0,SI_VALID_i_70_n_0,SI_VALID_i_71_n_0,SI_VALID_i_72_n_0,SI_VALID_i_73_n_0,SI_VALID_i_74_n_0}));
  CARRY8 SI_VALID_reg_i_52
       (.CI(\S_SAMPLES_reg_n_0_[0] ),
        .CI_TOP(1'b0),
        .CO({SI_VALID_reg_i_52_n_0,SI_VALID_reg_i_52_n_1,SI_VALID_reg_i_52_n_2,SI_VALID_reg_i_52_n_3,SI_VALID_reg_i_52_n_4,SI_VALID_reg_i_52_n_5,SI_VALID_reg_i_52_n_6,SI_VALID_reg_i_52_n_7}),
        .DI({\S_SAMPLES_reg_n_0_[8] ,\S_SAMPLES_reg_n_0_[7] ,\S_SAMPLES_reg_n_0_[6] ,\S_SAMPLES_reg_n_0_[5] ,\S_SAMPLES_reg_n_0_[4] ,\S_SAMPLES_reg_n_0_[3] ,\S_SAMPLES_reg_n_0_[2] ,\S_SAMPLES_reg_n_0_[1] }),
        .O(nxtstate3[8:1]),
        .S({SI_VALID_i_75_n_0,SI_VALID_i_76_n_0,SI_VALID_i_77_n_0,SI_VALID_i_78_n_0,SI_VALID_i_79_n_0,SI_VALID_i_80_n_0,SI_VALID_i_81_n_0,SI_VALID_i_82_n_0}));
  LUT5 #(
    .INIT(32'h00010000)) 
    \SI_VALUE[104]_i_1 
       (.I0(\SI_VALUE[279]_i_3_n_0 ),
        .I1(S_RESULT_COUNTER[3]),
        .I2(S_RESULT_COUNTER[2]),
        .I3(\S_RESULT_COUNTER_reg[0]_rep_n_0 ),
        .I4(\S_RESULT_COUNTER_reg[1]_rep_n_0 ),
        .O(p_1_in[104]));
  LUT4 #(
    .INIT(16'h0008)) 
    \SI_VALUE[139]_i_1 
       (.I0(\S_RESULT_COUNTER_reg[0]_rep_n_0 ),
        .I1(\S_RESULT_COUNTER_reg[1]_rep_n_0 ),
        .I2(S_RESULT_COUNTER[2]),
        .I3(\SI_VALUE[279]_i_3_n_0 ),
        .O(p_1_in[139]));
  LUT5 #(
    .INIT(32'h00000100)) 
    \SI_VALUE[174]_i_1 
       (.I0(\SI_VALUE[279]_i_3_n_0 ),
        .I1(\S_RESULT_COUNTER_reg[0]_rep_n_0 ),
        .I2(S_RESULT_COUNTER[3]),
        .I3(S_RESULT_COUNTER[2]),
        .I4(\S_RESULT_COUNTER_reg[1]_rep_n_0 ),
        .O(p_1_in[174]));
  (* SOFT_HLUTNM = "soft_lutpair91" *) 
  LUT3 #(
    .INIT(8'h40)) 
    \SI_VALUE[180]_i_3 
       (.I0(S_RESULT_COUNTER[3]),
        .I1(\S_RESULT_COUNTER_reg[1]_rep_n_0 ),
        .I2(S_RESULT_COUNTER[2]),
        .O(\SI_VALUE[180]_i_3_n_0 ));
  LUT5 #(
    .INIT(32'h00001000)) 
    \SI_VALUE[209]_i_1 
       (.I0(\SI_VALUE[279]_i_3_n_0 ),
        .I1(\S_RESULT_COUNTER_reg[1]_rep_n_0 ),
        .I2(\S_RESULT_COUNTER_reg[0]_rep_n_0 ),
        .I3(S_RESULT_COUNTER[2]),
        .I4(S_RESULT_COUNTER[3]),
        .O(p_1_in[209]));
  LUT5 #(
    .INIT(32'h00100000)) 
    \SI_VALUE[244]_i_1 
       (.I0(\SI_VALUE[279]_i_3_n_0 ),
        .I1(S_RESULT_COUNTER[3]),
        .I2(S_RESULT_COUNTER[2]),
        .I3(\S_RESULT_COUNTER_reg[0]_rep_n_0 ),
        .I4(\S_RESULT_COUNTER_reg[1]_rep_n_0 ),
        .O(p_1_in[244]));
  (* SOFT_HLUTNM = "soft_lutpair91" *) 
  LUT3 #(
    .INIT(8'hC6)) 
    \SI_VALUE[270]_i_3 
       (.I0(\S_RESULT_COUNTER_reg[1]_rep_n_0 ),
        .I1(S_RESULT_COUNTER[2]),
        .I2(\S_RESULT_COUNTER_reg[0]_rep_n_0 ),
        .O(\SI_VALUE[270]_i_3_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair88" *) 
  LUT4 #(
    .INIT(16'h224C)) 
    \SI_VALUE[273]_i_2 
       (.I0(\S_RESULT_COUNTER_reg[1]_rep_n_0 ),
        .I1(S_RESULT_COUNTER[3]),
        .I2(\S_RESULT_COUNTER_reg[0]_rep_n_0 ),
        .I3(S_RESULT_COUNTER[2]),
        .O(\SI_VALUE[273]_i_2_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair88" *) 
  LUT4 #(
    .INIT(16'h4AB5)) 
    \SI_VALUE[273]_i_4 
       (.I0(S_RESULT_COUNTER[2]),
        .I1(\S_RESULT_COUNTER_reg[0]_rep_n_0 ),
        .I2(\S_RESULT_COUNTER_reg[1]_rep_n_0 ),
        .I3(S_RESULT_COUNTER[3]),
        .O(\SI_VALUE[273]_i_4_n_0 ));
  LUT5 #(
    .INIT(32'h00004000)) 
    \SI_VALUE[279]_i_1 
       (.I0(S_RESULT_COUNTER[3]),
        .I1(\S_RESULT_COUNTER_reg[1]_rep_n_0 ),
        .I2(\S_RESULT_COUNTER_reg[0]_rep_n_0 ),
        .I3(S_RESULT_COUNTER[2]),
        .I4(\SI_VALUE[279]_i_3_n_0 ),
        .O(p_1_in[279]));
  LUT6 #(
    .INIT(64'hF7F7F7F7FFFFFFF0)) 
    \SI_VALUE[279]_i_3 
       (.I0(Q[0]),
        .I1(Q[1]),
        .I2(\S_ENABLE_reg[0]_0 ),
        .I3(S_RESULT_COUNTER[3]),
        .I4(\SI_VALUE[279]_i_6_n_0 ),
        .I5(\S_ENABLE_reg[0] ),
        .O(\SI_VALUE[279]_i_3_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair89" *) 
  LUT3 #(
    .INIT(8'h01)) 
    \SI_VALUE[279]_i_6 
       (.I0(S_RESULT_COUNTER[2]),
        .I1(\S_RESULT_COUNTER_reg[1]_rep_n_0 ),
        .I2(\S_RESULT_COUNTER_reg[0]_rep_n_0 ),
        .O(\SI_VALUE[279]_i_6_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair89" *) 
  LUT4 #(
    .INIT(16'h8000)) 
    \SI_VALUE[279]_i_7 
       (.I0(S_RESULT_COUNTER[2]),
        .I1(S_RESULT_COUNTER[3]),
        .I2(\S_RESULT_COUNTER_reg[0]_rep_n_0 ),
        .I3(\S_RESULT_COUNTER_reg[1]_rep_n_0 ),
        .O(\SI_VALUE[279]_i_7_n_0 ));
  LUT3 #(
    .INIT(8'h80)) 
    \SI_VALUE[34]_i_1 
       (.I0(\S_ENABLE_reg[0] ),
        .I1(Q[0]),
        .I2(Q[1]),
        .O(\SI_VALUE[34]_i_1_n_0 ));
  LUT5 #(
    .INIT(32'h00000004)) 
    \SI_VALUE[69]_i_1 
       (.I0(\S_RESULT_COUNTER_reg[1]_rep_n_0 ),
        .I1(\S_RESULT_COUNTER_reg[0]_rep_n_0 ),
        .I2(S_RESULT_COUNTER[3]),
        .I3(S_RESULT_COUNTER[2]),
        .I4(\SI_VALUE[279]_i_3_n_0 ),
        .O(p_1_in[69]));
  FDRE \SI_VALUE_reg[0] 
       (.C(s00_axi_aclk),
        .CE(\SI_VALUE[34]_i_1_n_0 ),
        .D(SI_VALUE0[0]),
        .Q(SI_VALUE[0]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[100] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[104]),
        .D(SI_VALUE0[228]),
        .Q(SI_VALUE[100]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[101] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[104]),
        .D(SI_VALUE0[229]),
        .Q(SI_VALUE[101]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[102] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[104]),
        .D(SI_VALUE0[230]),
        .Q(SI_VALUE[102]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[103] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[104]),
        .D(SI_VALUE0[231]),
        .Q(SI_VALUE[103]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[104] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[104]),
        .D(SI_VALUE0[232]),
        .Q(SI_VALUE[104]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[105] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[139]),
        .D(SI_VALUE0[105]),
        .Q(SI_VALUE[105]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[106] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[139]),
        .D(SI_VALUE0[106]),
        .Q(SI_VALUE[106]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[107] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[139]),
        .D(SI_VALUE0[107]),
        .Q(SI_VALUE[107]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[108] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[139]),
        .D(SI_VALUE0[108]),
        .Q(SI_VALUE[108]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[109] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[139]),
        .D(SI_VALUE0[109]),
        .Q(SI_VALUE[109]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[10] 
       (.C(s00_axi_aclk),
        .CE(\SI_VALUE[34]_i_1_n_0 ),
        .D(SI_VALUE0[10]),
        .Q(SI_VALUE[10]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[110] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[139]),
        .D(SI_VALUE0[110]),
        .Q(SI_VALUE[110]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[111] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[139]),
        .D(SI_VALUE0[111]),
        .Q(SI_VALUE[111]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[112] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[139]),
        .D(SI_VALUE0[112]),
        .Q(SI_VALUE[112]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[113] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[139]),
        .D(SI_VALUE0[113]),
        .Q(SI_VALUE[113]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[114] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[139]),
        .D(SI_VALUE0[114]),
        .Q(SI_VALUE[114]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[115] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[139]),
        .D(SI_VALUE0[115]),
        .Q(SI_VALUE[115]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[116] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[139]),
        .D(SI_VALUE0[116]),
        .Q(SI_VALUE[116]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[117] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[139]),
        .D(SI_VALUE0[117]),
        .Q(SI_VALUE[117]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[118] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[139]),
        .D(SI_VALUE0[118]),
        .Q(SI_VALUE[118]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[119] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[139]),
        .D(SI_VALUE0[119]),
        .Q(SI_VALUE[119]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[11] 
       (.C(s00_axi_aclk),
        .CE(\SI_VALUE[34]_i_1_n_0 ),
        .D(SI_VALUE0[11]),
        .Q(SI_VALUE[11]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[120] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[139]),
        .D(SI_VALUE0[120]),
        .Q(SI_VALUE[120]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[121] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[139]),
        .D(SI_VALUE0[121]),
        .Q(SI_VALUE[121]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[122] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[139]),
        .D(SI_VALUE0[122]),
        .Q(SI_VALUE[122]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[123] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[139]),
        .D(SI_VALUE0[123]),
        .Q(SI_VALUE[123]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[124] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[139]),
        .D(SI_VALUE0[124]),
        .Q(SI_VALUE[124]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[125] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[139]),
        .D(SI_VALUE0[125]),
        .Q(SI_VALUE[125]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[126] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[139]),
        .D(SI_VALUE0[126]),
        .Q(SI_VALUE[126]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[127] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[139]),
        .D(SI_VALUE0[127]),
        .Q(SI_VALUE[127]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[128] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[139]),
        .D(SI_VALUE0[128]),
        .Q(SI_VALUE[128]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[129] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[139]),
        .D(SI_VALUE0[129]),
        .Q(SI_VALUE[129]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[12] 
       (.C(s00_axi_aclk),
        .CE(\SI_VALUE[34]_i_1_n_0 ),
        .D(SI_VALUE0[12]),
        .Q(SI_VALUE[12]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[130] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[139]),
        .D(SI_VALUE0[130]),
        .Q(SI_VALUE[130]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[131] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[139]),
        .D(SI_VALUE0[131]),
        .Q(SI_VALUE[131]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[132] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[139]),
        .D(SI_VALUE0[132]),
        .Q(SI_VALUE[132]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[133] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[139]),
        .D(SI_VALUE0[133]),
        .Q(SI_VALUE[133]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[134] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[139]),
        .D(SI_VALUE0[134]),
        .Q(SI_VALUE[134]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[135] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[139]),
        .D(SI_VALUE0[135]),
        .Q(SI_VALUE[135]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[136] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[139]),
        .D(SI_VALUE0[136]),
        .Q(SI_VALUE[136]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[137] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[139]),
        .D(SI_VALUE0[137]),
        .Q(SI_VALUE[137]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[138] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[139]),
        .D(SI_VALUE0[138]),
        .Q(SI_VALUE[138]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[139] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[139]),
        .D(SI_VALUE0[139]),
        .Q(SI_VALUE[139]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[13] 
       (.C(s00_axi_aclk),
        .CE(\SI_VALUE[34]_i_1_n_0 ),
        .D(SI_VALUE0[13]),
        .Q(SI_VALUE[13]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[140] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[174]),
        .D(SI_VALUE0[76]),
        .Q(SI_VALUE[140]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[141] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[174]),
        .D(SI_VALUE0[77]),
        .Q(SI_VALUE[141]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[142] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[174]),
        .D(SI_VALUE0[78]),
        .Q(SI_VALUE[142]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[143] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[174]),
        .D(SI_VALUE0[143]),
        .Q(SI_VALUE[143]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[144] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[174]),
        .D(SI_VALUE0[144]),
        .Q(SI_VALUE[144]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[145] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[174]),
        .D(SI_VALUE0[145]),
        .Q(SI_VALUE[145]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[146] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[174]),
        .D(SI_VALUE0[146]),
        .Q(SI_VALUE[146]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[147] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[174]),
        .D(SI_VALUE0[147]),
        .Q(SI_VALUE[147]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[148] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[174]),
        .D(SI_VALUE0[148]),
        .Q(SI_VALUE[148]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[149] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[174]),
        .D(SI_VALUE0[213]),
        .Q(SI_VALUE[149]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[14] 
       (.C(s00_axi_aclk),
        .CE(\SI_VALUE[34]_i_1_n_0 ),
        .D(SI_VALUE0[14]),
        .Q(SI_VALUE[14]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[150] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[174]),
        .D(SI_VALUE0[214]),
        .Q(SI_VALUE[150]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[151] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[174]),
        .D(SI_VALUE0[215]),
        .Q(SI_VALUE[151]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[152] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[174]),
        .D(SI_VALUE0[216]),
        .Q(SI_VALUE[152]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[153] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[174]),
        .D(SI_VALUE0[217]),
        .Q(SI_VALUE[153]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[154] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[174]),
        .D(SI_VALUE0[218]),
        .Q(SI_VALUE[154]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[155] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[174]),
        .D(SI_VALUE0[219]),
        .Q(SI_VALUE[155]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[156] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[174]),
        .D(SI_VALUE0[220]),
        .Q(SI_VALUE[156]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[157] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[174]),
        .D(SI_VALUE0[221]),
        .Q(SI_VALUE[157]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[158] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[174]),
        .D(SI_VALUE0[222]),
        .Q(SI_VALUE[158]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[159] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[174]),
        .D(SI_VALUE0[191]),
        .Q(SI_VALUE[159]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[15] 
       (.C(s00_axi_aclk),
        .CE(\SI_VALUE[34]_i_1_n_0 ),
        .D(SI_VALUE0[15]),
        .Q(SI_VALUE[15]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[160] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[174]),
        .D(SI_VALUE0[192]),
        .Q(SI_VALUE[160]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[161] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[174]),
        .D(SI_VALUE0[225]),
        .Q(SI_VALUE[161]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[162] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[174]),
        .D(SI_VALUE0[226]),
        .Q(SI_VALUE[162]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[163] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[174]),
        .D(SI_VALUE0[227]),
        .Q(SI_VALUE[163]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[164] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[174]),
        .D(SI_VALUE0[228]),
        .Q(SI_VALUE[164]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[165] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[174]),
        .D(SI_VALUE0[229]),
        .Q(SI_VALUE[165]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[166] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[174]),
        .D(SI_VALUE0[230]),
        .Q(SI_VALUE[166]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[167] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[174]),
        .D(SI_VALUE0[231]),
        .Q(SI_VALUE[167]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[168] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[174]),
        .D(SI_VALUE0[232]),
        .Q(SI_VALUE[168]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[169] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[174]),
        .D(SI_VALUE0[233]),
        .Q(SI_VALUE[169]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[16] 
       (.C(s00_axi_aclk),
        .CE(\SI_VALUE[34]_i_1_n_0 ),
        .D(SI_VALUE0[16]),
        .Q(SI_VALUE[16]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[170] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[174]),
        .D(SI_VALUE0[234]),
        .Q(SI_VALUE[170]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[171] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[174]),
        .D(SI_VALUE0[235]),
        .Q(SI_VALUE[171]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[172] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[174]),
        .D(SI_VALUE0[236]),
        .Q(SI_VALUE[172]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[173] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[174]),
        .D(SI_VALUE0[237]),
        .Q(SI_VALUE[173]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[174] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[174]),
        .D(SI_VALUE0[238]),
        .Q(SI_VALUE[174]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[175] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[209]),
        .D(SI_VALUE0[143]),
        .Q(SI_VALUE[175]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[176] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[209]),
        .D(SI_VALUE0[144]),
        .Q(SI_VALUE[176]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[177] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[209]),
        .D(SI_VALUE0[145]),
        .Q(SI_VALUE[177]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[178] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[209]),
        .D(SI_VALUE0[146]),
        .Q(SI_VALUE[178]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[179] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[209]),
        .D(SI_VALUE0[147]),
        .Q(SI_VALUE[179]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[17] 
       (.C(s00_axi_aclk),
        .CE(\SI_VALUE[34]_i_1_n_0 ),
        .D(SI_VALUE0[17]),
        .Q(SI_VALUE[17]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[180] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[209]),
        .D(SI_VALUE0[148]),
        .Q(SI_VALUE[180]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[181] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[209]),
        .D(SI_VALUE0[213]),
        .Q(SI_VALUE[181]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[182] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[209]),
        .D(SI_VALUE0[214]),
        .Q(SI_VALUE[182]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[183] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[209]),
        .D(SI_VALUE0[215]),
        .Q(SI_VALUE[183]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[184] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[209]),
        .D(SI_VALUE0[216]),
        .Q(SI_VALUE[184]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[185] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[209]),
        .D(SI_VALUE0[217]),
        .Q(SI_VALUE[185]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[186] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[209]),
        .D(SI_VALUE0[218]),
        .Q(SI_VALUE[186]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[187] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[209]),
        .D(SI_VALUE0[219]),
        .Q(SI_VALUE[187]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[188] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[209]),
        .D(SI_VALUE0[220]),
        .Q(SI_VALUE[188]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[189] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[209]),
        .D(SI_VALUE0[221]),
        .Q(SI_VALUE[189]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[18] 
       (.C(s00_axi_aclk),
        .CE(\SI_VALUE[34]_i_1_n_0 ),
        .D(SI_VALUE0[18]),
        .Q(SI_VALUE[18]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[190] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[209]),
        .D(SI_VALUE0[222]),
        .Q(SI_VALUE[190]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[191] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[209]),
        .D(SI_VALUE0[191]),
        .Q(SI_VALUE[191]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[192] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[209]),
        .D(SI_VALUE0[192]),
        .Q(SI_VALUE[192]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[193] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[209]),
        .D(SI_VALUE0[225]),
        .Q(SI_VALUE[193]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[194] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[209]),
        .D(SI_VALUE0[226]),
        .Q(SI_VALUE[194]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[195] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[209]),
        .D(SI_VALUE0[227]),
        .Q(SI_VALUE[195]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[196] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[209]),
        .D(SI_VALUE0[228]),
        .Q(SI_VALUE[196]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[197] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[209]),
        .D(SI_VALUE0[229]),
        .Q(SI_VALUE[197]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[198] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[209]),
        .D(SI_VALUE0[230]),
        .Q(SI_VALUE[198]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[199] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[209]),
        .D(SI_VALUE0[231]),
        .Q(SI_VALUE[199]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[19] 
       (.C(s00_axi_aclk),
        .CE(\SI_VALUE[34]_i_1_n_0 ),
        .D(SI_VALUE0[19]),
        .Q(SI_VALUE[19]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[1] 
       (.C(s00_axi_aclk),
        .CE(\SI_VALUE[34]_i_1_n_0 ),
        .D(SI_VALUE0[1]),
        .Q(SI_VALUE[1]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[200] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[209]),
        .D(SI_VALUE0[232]),
        .Q(SI_VALUE[200]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[201] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[209]),
        .D(SI_VALUE0[233]),
        .Q(SI_VALUE[201]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[202] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[209]),
        .D(SI_VALUE0[234]),
        .Q(SI_VALUE[202]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[203] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[209]),
        .D(SI_VALUE0[235]),
        .Q(SI_VALUE[203]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[204] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[209]),
        .D(SI_VALUE0[236]),
        .Q(SI_VALUE[204]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[205] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[209]),
        .D(SI_VALUE0[237]),
        .Q(SI_VALUE[205]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[206] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[209]),
        .D(SI_VALUE0[238]),
        .Q(SI_VALUE[206]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[207] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[209]),
        .D(raw_to_si_n_1),
        .Q(SI_VALUE[207]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[208] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[209]),
        .D(S_RESULT_S_C),
        .Q(SI_VALUE[208]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[209] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[209]),
        .D(SI_VALUE0[209]),
        .Q(SI_VALUE[209]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[20] 
       (.C(s00_axi_aclk),
        .CE(\SI_VALUE[34]_i_1_n_0 ),
        .D(SI_VALUE0[20]),
        .Q(SI_VALUE[20]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[210] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[244]),
        .D(SI_VALUE0[210]),
        .Q(SI_VALUE[210]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[211] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[244]),
        .D(SI_VALUE0[211]),
        .Q(SI_VALUE[211]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[212] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[244]),
        .D(SI_VALUE0[36]),
        .Q(SI_VALUE[212]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[213] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[244]),
        .D(SI_VALUE0[213]),
        .Q(SI_VALUE[213]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[214] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[244]),
        .D(SI_VALUE0[214]),
        .Q(SI_VALUE[214]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[215] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[244]),
        .D(SI_VALUE0[215]),
        .Q(SI_VALUE[215]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[216] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[244]),
        .D(SI_VALUE0[216]),
        .Q(SI_VALUE[216]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[217] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[244]),
        .D(SI_VALUE0[217]),
        .Q(SI_VALUE[217]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[218] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[244]),
        .D(SI_VALUE0[218]),
        .Q(SI_VALUE[218]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[219] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[244]),
        .D(SI_VALUE0[219]),
        .Q(SI_VALUE[219]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[21] 
       (.C(s00_axi_aclk),
        .CE(\SI_VALUE[34]_i_1_n_0 ),
        .D(SI_VALUE0[21]),
        .Q(SI_VALUE[21]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[220] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[244]),
        .D(SI_VALUE0[220]),
        .Q(SI_VALUE[220]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[221] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[244]),
        .D(SI_VALUE0[221]),
        .Q(SI_VALUE[221]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[222] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[244]),
        .D(SI_VALUE0[222]),
        .Q(SI_VALUE[222]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[223] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[244]),
        .D(SI_VALUE0[191]),
        .Q(SI_VALUE[223]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[224] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[244]),
        .D(SI_VALUE0[192]),
        .Q(SI_VALUE[224]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[225] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[244]),
        .D(SI_VALUE0[225]),
        .Q(SI_VALUE[225]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[226] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[244]),
        .D(SI_VALUE0[226]),
        .Q(SI_VALUE[226]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[227] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[244]),
        .D(SI_VALUE0[227]),
        .Q(SI_VALUE[227]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[228] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[244]),
        .D(SI_VALUE0[228]),
        .Q(SI_VALUE[228]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[229] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[244]),
        .D(SI_VALUE0[229]),
        .Q(SI_VALUE[229]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[22] 
       (.C(s00_axi_aclk),
        .CE(\SI_VALUE[34]_i_1_n_0 ),
        .D(SI_VALUE0[22]),
        .Q(SI_VALUE[22]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[230] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[244]),
        .D(SI_VALUE0[230]),
        .Q(SI_VALUE[230]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[231] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[244]),
        .D(SI_VALUE0[231]),
        .Q(SI_VALUE[231]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[232] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[244]),
        .D(SI_VALUE0[232]),
        .Q(SI_VALUE[232]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[233] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[244]),
        .D(SI_VALUE0[233]),
        .Q(SI_VALUE[233]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[234] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[244]),
        .D(SI_VALUE0[234]),
        .Q(SI_VALUE[234]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[235] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[244]),
        .D(SI_VALUE0[235]),
        .Q(SI_VALUE[235]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[236] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[244]),
        .D(SI_VALUE0[236]),
        .Q(SI_VALUE[236]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[237] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[244]),
        .D(SI_VALUE0[237]),
        .Q(SI_VALUE[237]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[238] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[244]),
        .D(SI_VALUE0[238]),
        .Q(SI_VALUE[238]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[239] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[244]),
        .D(SI_VALUE0[239]),
        .Q(SI_VALUE[239]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[23] 
       (.C(s00_axi_aclk),
        .CE(\SI_VALUE[34]_i_1_n_0 ),
        .D(SI_VALUE0[23]),
        .Q(SI_VALUE[23]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[240] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[244]),
        .D(SI_VALUE0[240]),
        .Q(SI_VALUE[240]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[241] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[244]),
        .D(SI_VALUE0[241]),
        .Q(SI_VALUE[241]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[242] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[244]),
        .D(SI_VALUE0[242]),
        .Q(SI_VALUE[242]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[243] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[244]),
        .D(SI_VALUE0[243]),
        .Q(SI_VALUE[243]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[244] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[244]),
        .D(SI_VALUE0[244]),
        .Q(SI_VALUE[244]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[245] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[279]),
        .D(SI_VALUE0[213]),
        .Q(SI_VALUE[245]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[246] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[279]),
        .D(SI_VALUE0[214]),
        .Q(SI_VALUE[246]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[247] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[279]),
        .D(SI_VALUE0[215]),
        .Q(SI_VALUE[247]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[248] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[279]),
        .D(SI_VALUE0[216]),
        .Q(SI_VALUE[248]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[249] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[279]),
        .D(SI_VALUE0[217]),
        .Q(SI_VALUE[249]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[24] 
       (.C(s00_axi_aclk),
        .CE(\SI_VALUE[34]_i_1_n_0 ),
        .D(SI_VALUE0[24]),
        .Q(SI_VALUE[24]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[250] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[279]),
        .D(SI_VALUE0[218]),
        .Q(SI_VALUE[250]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[251] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[279]),
        .D(SI_VALUE0[219]),
        .Q(SI_VALUE[251]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[252] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[279]),
        .D(SI_VALUE0[220]),
        .Q(SI_VALUE[252]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[253] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[279]),
        .D(SI_VALUE0[221]),
        .Q(SI_VALUE[253]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[254] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[279]),
        .D(SI_VALUE0[222]),
        .Q(SI_VALUE[254]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[255] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[279]),
        .D(SI_VALUE0[255]),
        .Q(SI_VALUE[255]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[256] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[279]),
        .D(SI_VALUE0[256]),
        .Q(SI_VALUE[256]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[257] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[279]),
        .D(SI_VALUE0[225]),
        .Q(SI_VALUE[257]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[258] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[279]),
        .D(SI_VALUE0[226]),
        .Q(SI_VALUE[258]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[259] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[279]),
        .D(SI_VALUE0[227]),
        .Q(SI_VALUE[259]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[25] 
       (.C(s00_axi_aclk),
        .CE(\SI_VALUE[34]_i_1_n_0 ),
        .D(SI_VALUE0[25]),
        .Q(SI_VALUE[25]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[260] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[279]),
        .D(SI_VALUE0[228]),
        .Q(SI_VALUE[260]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[261] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[279]),
        .D(SI_VALUE0[229]),
        .Q(SI_VALUE[261]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[262] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[279]),
        .D(SI_VALUE0[230]),
        .Q(SI_VALUE[262]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[263] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[279]),
        .D(SI_VALUE0[231]),
        .Q(SI_VALUE[263]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[264] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[279]),
        .D(SI_VALUE0[232]),
        .Q(SI_VALUE[264]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[265] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[279]),
        .D(SI_VALUE0[233]),
        .Q(SI_VALUE[265]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[266] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[279]),
        .D(SI_VALUE0[234]),
        .Q(SI_VALUE[266]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[267] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[279]),
        .D(SI_VALUE0[235]),
        .Q(SI_VALUE[267]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[268] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[279]),
        .D(SI_VALUE0[236]),
        .Q(SI_VALUE[268]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[269] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[279]),
        .D(SI_VALUE0[237]),
        .Q(SI_VALUE[269]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[26] 
       (.C(s00_axi_aclk),
        .CE(\SI_VALUE[34]_i_1_n_0 ),
        .D(SI_VALUE0[26]),
        .Q(SI_VALUE[26]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[270] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[279]),
        .D(SI_VALUE0[238]),
        .Q(SI_VALUE[270]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[271] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[279]),
        .D(SI_VALUE0[239]),
        .Q(SI_VALUE[271]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[272] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[279]),
        .D(SI_VALUE0[240]),
        .Q(SI_VALUE[272]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[273] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[279]),
        .D(SI_VALUE0[241]),
        .Q(SI_VALUE[273]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[274] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[279]),
        .D(SI_VALUE0[242]),
        .Q(SI_VALUE[274]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[275] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[279]),
        .D(SI_VALUE0[243]),
        .Q(SI_VALUE[275]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[276] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[279]),
        .D(SI_VALUE0[244]),
        .Q(SI_VALUE[276]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[277] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[279]),
        .D(SI_VALUE0[277]),
        .Q(SI_VALUE[277]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[278] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[279]),
        .D(SI_VALUE0[278]),
        .Q(SI_VALUE[278]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[279] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[279]),
        .D(SI_VALUE0[279]),
        .Q(SI_VALUE[279]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[27] 
       (.C(s00_axi_aclk),
        .CE(\SI_VALUE[34]_i_1_n_0 ),
        .D(SI_VALUE0[27]),
        .Q(SI_VALUE[27]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[28] 
       (.C(s00_axi_aclk),
        .CE(\SI_VALUE[34]_i_1_n_0 ),
        .D(SI_VALUE0[28]),
        .Q(SI_VALUE[28]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[29] 
       (.C(s00_axi_aclk),
        .CE(\SI_VALUE[34]_i_1_n_0 ),
        .D(SI_VALUE0[29]),
        .Q(SI_VALUE[29]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[2] 
       (.C(s00_axi_aclk),
        .CE(\SI_VALUE[34]_i_1_n_0 ),
        .D(SI_VALUE0[2]),
        .Q(SI_VALUE[2]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[30] 
       (.C(s00_axi_aclk),
        .CE(\SI_VALUE[34]_i_1_n_0 ),
        .D(SI_VALUE0[30]),
        .Q(SI_VALUE[30]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[31] 
       (.C(s00_axi_aclk),
        .CE(\SI_VALUE[34]_i_1_n_0 ),
        .D(SI_VALUE0[31]),
        .Q(SI_VALUE[31]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[32] 
       (.C(s00_axi_aclk),
        .CE(\SI_VALUE[34]_i_1_n_0 ),
        .D(SI_VALUE0[32]),
        .Q(SI_VALUE[32]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[33] 
       (.C(s00_axi_aclk),
        .CE(\SI_VALUE[34]_i_1_n_0 ),
        .D(SI_VALUE0[33]),
        .Q(SI_VALUE[33]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[34] 
       (.C(s00_axi_aclk),
        .CE(\SI_VALUE[34]_i_1_n_0 ),
        .D(SI_VALUE0[34]),
        .Q(SI_VALUE[34]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[35] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[69]),
        .D(SI_VALUE0[35]),
        .Q(SI_VALUE[35]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[36] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[69]),
        .D(SI_VALUE0[36]),
        .Q(SI_VALUE[36]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[37] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[69]),
        .D(SI_VALUE0[37]),
        .Q(SI_VALUE[37]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[38] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[69]),
        .D(SI_VALUE0[38]),
        .Q(SI_VALUE[38]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[39] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[69]),
        .D(SI_VALUE0[39]),
        .Q(SI_VALUE[39]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[3] 
       (.C(s00_axi_aclk),
        .CE(\SI_VALUE[34]_i_1_n_0 ),
        .D(SI_VALUE0[3]),
        .Q(SI_VALUE[3]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[40] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[69]),
        .D(SI_VALUE0[40]),
        .Q(SI_VALUE[40]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[41] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[69]),
        .D(SI_VALUE0[41]),
        .Q(SI_VALUE[41]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[42] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[69]),
        .D(SI_VALUE0[42]),
        .Q(SI_VALUE[42]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[43] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[69]),
        .D(SI_VALUE0[43]),
        .Q(SI_VALUE[43]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[44] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[69]),
        .D(SI_VALUE0[76]),
        .Q(SI_VALUE[44]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[45] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[69]),
        .D(SI_VALUE0[77]),
        .Q(SI_VALUE[45]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[46] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[69]),
        .D(SI_VALUE0[78]),
        .Q(SI_VALUE[46]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[47] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[69]),
        .D(SI_VALUE0[143]),
        .Q(SI_VALUE[47]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[48] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[69]),
        .D(SI_VALUE0[144]),
        .Q(SI_VALUE[48]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[49] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[69]),
        .D(SI_VALUE0[145]),
        .Q(SI_VALUE[49]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[4] 
       (.C(s00_axi_aclk),
        .CE(\SI_VALUE[34]_i_1_n_0 ),
        .D(SI_VALUE0[4]),
        .Q(SI_VALUE[4]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[50] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[69]),
        .D(SI_VALUE0[146]),
        .Q(SI_VALUE[50]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[51] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[69]),
        .D(SI_VALUE0[147]),
        .Q(SI_VALUE[51]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[52] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[69]),
        .D(SI_VALUE0[148]),
        .Q(SI_VALUE[52]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[53] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[69]),
        .D(SI_VALUE0[213]),
        .Q(SI_VALUE[53]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[54] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[69]),
        .D(SI_VALUE0[214]),
        .Q(SI_VALUE[54]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[55] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[69]),
        .D(SI_VALUE0[215]),
        .Q(SI_VALUE[55]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[56] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[69]),
        .D(SI_VALUE0[216]),
        .Q(SI_VALUE[56]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[57] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[69]),
        .D(SI_VALUE0[217]),
        .Q(SI_VALUE[57]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[58] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[69]),
        .D(SI_VALUE0[218]),
        .Q(SI_VALUE[58]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[59] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[69]),
        .D(SI_VALUE0[219]),
        .Q(SI_VALUE[59]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[5] 
       (.C(s00_axi_aclk),
        .CE(\SI_VALUE[34]_i_1_n_0 ),
        .D(SI_VALUE0[5]),
        .Q(SI_VALUE[5]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[60] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[69]),
        .D(SI_VALUE0[220]),
        .Q(SI_VALUE[60]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[61] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[69]),
        .D(SI_VALUE0[221]),
        .Q(SI_VALUE[61]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[62] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[69]),
        .D(SI_VALUE0[222]),
        .Q(SI_VALUE[62]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[63] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[69]),
        .D(SI_VALUE0[191]),
        .Q(SI_VALUE[63]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[64] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[69]),
        .D(SI_VALUE0[192]),
        .Q(SI_VALUE[64]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[65] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[69]),
        .D(SI_VALUE0[225]),
        .Q(SI_VALUE[65]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[66] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[69]),
        .D(SI_VALUE0[226]),
        .Q(SI_VALUE[66]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[67] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[69]),
        .D(SI_VALUE0[227]),
        .Q(SI_VALUE[67]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[68] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[69]),
        .D(SI_VALUE0[228]),
        .Q(SI_VALUE[68]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[69] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[69]),
        .D(SI_VALUE0[229]),
        .Q(SI_VALUE[69]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[6] 
       (.C(s00_axi_aclk),
        .CE(\SI_VALUE[34]_i_1_n_0 ),
        .D(SI_VALUE0[6]),
        .Q(SI_VALUE[6]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[70] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[104]),
        .D(SI_VALUE0[38]),
        .Q(SI_VALUE[70]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[71] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[104]),
        .D(SI_VALUE0[39]),
        .Q(SI_VALUE[71]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[72] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[104]),
        .D(SI_VALUE0[40]),
        .Q(SI_VALUE[72]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[73] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[104]),
        .D(SI_VALUE0[41]),
        .Q(SI_VALUE[73]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[74] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[104]),
        .D(SI_VALUE0[42]),
        .Q(SI_VALUE[74]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[75] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[104]),
        .D(SI_VALUE0[43]),
        .Q(SI_VALUE[75]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[76] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[104]),
        .D(SI_VALUE0[76]),
        .Q(SI_VALUE[76]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[77] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[104]),
        .D(SI_VALUE0[77]),
        .Q(SI_VALUE[77]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[78] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[104]),
        .D(SI_VALUE0[78]),
        .Q(SI_VALUE[78]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[79] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[104]),
        .D(SI_VALUE0[143]),
        .Q(SI_VALUE[79]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[7] 
       (.C(s00_axi_aclk),
        .CE(\SI_VALUE[34]_i_1_n_0 ),
        .D(SI_VALUE0[7]),
        .Q(SI_VALUE[7]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[80] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[104]),
        .D(SI_VALUE0[144]),
        .Q(SI_VALUE[80]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[81] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[104]),
        .D(SI_VALUE0[145]),
        .Q(SI_VALUE[81]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[82] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[104]),
        .D(SI_VALUE0[146]),
        .Q(SI_VALUE[82]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[83] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[104]),
        .D(SI_VALUE0[147]),
        .Q(SI_VALUE[83]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[84] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[104]),
        .D(SI_VALUE0[148]),
        .Q(SI_VALUE[84]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[85] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[104]),
        .D(SI_VALUE0[213]),
        .Q(SI_VALUE[85]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[86] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[104]),
        .D(SI_VALUE0[214]),
        .Q(SI_VALUE[86]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[87] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[104]),
        .D(SI_VALUE0[215]),
        .Q(SI_VALUE[87]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[88] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[104]),
        .D(SI_VALUE0[216]),
        .Q(SI_VALUE[88]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[89] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[104]),
        .D(SI_VALUE0[217]),
        .Q(SI_VALUE[89]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[8] 
       (.C(s00_axi_aclk),
        .CE(\SI_VALUE[34]_i_1_n_0 ),
        .D(SI_VALUE0[8]),
        .Q(SI_VALUE[8]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[90] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[104]),
        .D(SI_VALUE0[218]),
        .Q(SI_VALUE[90]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[91] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[104]),
        .D(SI_VALUE0[219]),
        .Q(SI_VALUE[91]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[92] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[104]),
        .D(SI_VALUE0[220]),
        .Q(SI_VALUE[92]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[93] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[104]),
        .D(SI_VALUE0[221]),
        .Q(SI_VALUE[93]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[94] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[104]),
        .D(SI_VALUE0[222]),
        .Q(SI_VALUE[94]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[95] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[104]),
        .D(SI_VALUE0[191]),
        .Q(SI_VALUE[95]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[96] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[104]),
        .D(SI_VALUE0[192]),
        .Q(SI_VALUE[96]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[97] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[104]),
        .D(SI_VALUE0[225]),
        .Q(SI_VALUE[97]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[98] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[104]),
        .D(SI_VALUE0[226]),
        .Q(SI_VALUE[98]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[99] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[104]),
        .D(SI_VALUE0[227]),
        .Q(SI_VALUE[99]),
        .R(RSTP));
  FDRE \SI_VALUE_reg[9] 
       (.C(s00_axi_aclk),
        .CE(\SI_VALUE[34]_i_1_n_0 ),
        .D(SI_VALUE0[9]),
        .Q(SI_VALUE[9]),
        .R(RSTP));
  FDRE S_CE_CONVERSION_reg
       (.C(s00_axi_aclk),
        .CE(SI_VALID_i_1_n_0),
        .D(nxtstate[1]),
        .Q(S_CE_CONVERSION),
        .R(RSTP));
  LUT2 #(
    .INIT(4'h1)) 
    \S_CHANNEL_COUNTER[0]_i_1 
       (.I0(S_CHANNEL_COUNTER[0]),
        .I1(\S_ENABLE_reg[0]_0 ),
        .O(\S_CHANNEL_COUNTER[0]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair108" *) 
  LUT3 #(
    .INIT(8'h09)) 
    \S_CHANNEL_COUNTER[1]_i_1 
       (.I0(S_CHANNEL_COUNTER[1]),
        .I1(S_CHANNEL_COUNTER[0]),
        .I2(\S_ENABLE_reg[0]_0 ),
        .O(\S_CHANNEL_COUNTER[1]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair85" *) 
  LUT4 #(
    .INIT(16'h00E1)) 
    \S_CHANNEL_COUNTER[2]_i_1 
       (.I0(S_CHANNEL_COUNTER[0]),
        .I1(S_CHANNEL_COUNTER[1]),
        .I2(S_CHANNEL_COUNTER[2]),
        .I3(\S_ENABLE_reg[0]_0 ),
        .O(\S_CHANNEL_COUNTER[2]_i_1_n_0 ));
  LUT2 #(
    .INIT(4'hB)) 
    \S_CHANNEL_COUNTER[3]_i_1 
       (.I0(S_OFFSET_S_C),
        .I1(\S_ENABLE_reg[0]_1 ),
        .O(\S_CHANNEL_COUNTER[3]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair85" *) 
  LUT5 #(
    .INIT(32'hFFFEAAAB)) 
    \S_CHANNEL_COUNTER[3]_i_2 
       (.I0(\S_ENABLE_reg[0]_0 ),
        .I1(S_CHANNEL_COUNTER[1]),
        .I2(S_CHANNEL_COUNTER[0]),
        .I3(S_CHANNEL_COUNTER[2]),
        .I4(S_CHANNEL_COUNTER[3]),
        .O(\S_CHANNEL_COUNTER[3]_i_2_n_0 ));
  LUT6 #(
    .INIT(64'hFEFFFEFFFFFFFEFF)) 
    \S_CHANNEL_COUNTER[3]_i_3 
       (.I0(\S_SAMPLE_TIME_COUNTER[30]_i_7_n_0 ),
        .I1(\S_SAMPLE_TIME_COUNTER[30]_i_6_n_0 ),
        .I2(raw_to_si_n_133),
        .I3(raw_to_si_n_134),
        .I4(nxtstate22_in),
        .I5(ENABLE),
        .O(\S_ENABLE_reg[0]_1 ));
  FDRE \S_CHANNEL_COUNTER_reg[0] 
       (.C(s00_axi_aclk),
        .CE(\S_CHANNEL_COUNTER[3]_i_1_n_0 ),
        .D(\S_CHANNEL_COUNTER[0]_i_1_n_0 ),
        .Q(S_CHANNEL_COUNTER[0]),
        .R(RSTP));
  FDRE \S_CHANNEL_COUNTER_reg[1] 
       (.C(s00_axi_aclk),
        .CE(\S_CHANNEL_COUNTER[3]_i_1_n_0 ),
        .D(\S_CHANNEL_COUNTER[1]_i_1_n_0 ),
        .Q(S_CHANNEL_COUNTER[1]),
        .R(RSTP));
  FDRE \S_CHANNEL_COUNTER_reg[2] 
       (.C(s00_axi_aclk),
        .CE(\S_CHANNEL_COUNTER[3]_i_1_n_0 ),
        .D(\S_CHANNEL_COUNTER[2]_i_1_n_0 ),
        .Q(S_CHANNEL_COUNTER[2]),
        .R(RSTP));
  FDRE \S_CHANNEL_COUNTER_reg[3] 
       (.C(s00_axi_aclk),
        .CE(\S_CHANNEL_COUNTER[3]_i_1_n_0 ),
        .D(\S_CHANNEL_COUNTER[3]_i_2_n_0 ),
        .Q(S_CHANNEL_COUNTER[3]),
        .R(RSTP));
  FDRE \S_CONVERSION_reg[0] 
       (.C(s00_axi_aclk),
        .CE(\S_CONVERSION_reg[126]_0 [0]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [0]),
        .Q(\S_CONVERSION_reg_n_0_[0] ),
        .R(RSTP));
  FDRE \S_CONVERSION_reg[100] 
       (.C(s00_axi_aclk),
        .CE(\S_CONVERSION_reg[126]_0 [5]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [10]),
        .Q(data6[10]),
        .R(RSTP));
  FDRE \S_CONVERSION_reg[101] 
       (.C(s00_axi_aclk),
        .CE(\S_CONVERSION_reg[126]_0 [5]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [11]),
        .Q(data6[11]),
        .R(RSTP));
  FDRE \S_CONVERSION_reg[102] 
       (.C(s00_axi_aclk),
        .CE(\S_CONVERSION_reg[126]_0 [5]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [12]),
        .Q(data6[12]),
        .R(RSTP));
  FDRE \S_CONVERSION_reg[103] 
       (.C(s00_axi_aclk),
        .CE(\S_CONVERSION_reg[126]_0 [5]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [13]),
        .Q(data6[13]),
        .R(RSTP));
  FDRE \S_CONVERSION_reg[104] 
       (.C(s00_axi_aclk),
        .CE(\S_CONVERSION_reg[126]_0 [5]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [14]),
        .Q(data6[14]),
        .R(RSTP));
  FDRE \S_CONVERSION_reg[105] 
       (.C(s00_axi_aclk),
        .CE(\S_CONVERSION_reg[126]_0 [5]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [15]),
        .Q(data6[15]),
        .R(RSTP));
  FDRE \S_CONVERSION_reg[106] 
       (.C(s00_axi_aclk),
        .CE(\S_CONVERSION_reg[126]_0 [5]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [16]),
        .Q(data6[16]),
        .R(RSTP));
  FDRE \S_CONVERSION_reg[107] 
       (.C(s00_axi_aclk),
        .CE(\S_CONVERSION_reg[126]_0 [5]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [17]),
        .Q(data6[17]),
        .R(RSTP));
  FDRE \S_CONVERSION_reg[108] 
       (.C(s00_axi_aclk),
        .CE(\S_CONVERSION_reg[126]_0 [6]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [0]),
        .Q(data7[0]),
        .R(RSTP));
  FDRE \S_CONVERSION_reg[109] 
       (.C(s00_axi_aclk),
        .CE(\S_CONVERSION_reg[126]_0 [6]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [1]),
        .Q(data7[1]),
        .R(RSTP));
  FDRE \S_CONVERSION_reg[10] 
       (.C(s00_axi_aclk),
        .CE(\S_CONVERSION_reg[126]_0 [0]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [10]),
        .Q(\S_CONVERSION_reg_n_0_[10] ),
        .R(RSTP));
  FDRE \S_CONVERSION_reg[110] 
       (.C(s00_axi_aclk),
        .CE(\S_CONVERSION_reg[126]_0 [6]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [2]),
        .Q(data7[2]),
        .R(RSTP));
  FDRE \S_CONVERSION_reg[111] 
       (.C(s00_axi_aclk),
        .CE(\S_CONVERSION_reg[126]_0 [6]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [3]),
        .Q(data7[3]),
        .R(RSTP));
  FDRE \S_CONVERSION_reg[112] 
       (.C(s00_axi_aclk),
        .CE(\S_CONVERSION_reg[126]_0 [6]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [4]),
        .Q(data7[4]),
        .R(RSTP));
  FDRE \S_CONVERSION_reg[113] 
       (.C(s00_axi_aclk),
        .CE(\S_CONVERSION_reg[126]_0 [6]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [5]),
        .Q(data7[5]),
        .R(RSTP));
  FDRE \S_CONVERSION_reg[114] 
       (.C(s00_axi_aclk),
        .CE(\S_CONVERSION_reg[126]_0 [6]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [6]),
        .Q(data7[6]),
        .R(RSTP));
  FDRE \S_CONVERSION_reg[115] 
       (.C(s00_axi_aclk),
        .CE(\S_CONVERSION_reg[126]_0 [6]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [7]),
        .Q(data7[7]),
        .R(RSTP));
  FDRE \S_CONVERSION_reg[116] 
       (.C(s00_axi_aclk),
        .CE(\S_CONVERSION_reg[126]_0 [6]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [8]),
        .Q(data7[8]),
        .R(RSTP));
  FDRE \S_CONVERSION_reg[117] 
       (.C(s00_axi_aclk),
        .CE(\S_CONVERSION_reg[126]_0 [6]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [9]),
        .Q(data7[9]),
        .R(RSTP));
  FDRE \S_CONVERSION_reg[118] 
       (.C(s00_axi_aclk),
        .CE(\S_CONVERSION_reg[126]_0 [6]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [10]),
        .Q(data7[10]),
        .R(RSTP));
  FDRE \S_CONVERSION_reg[119] 
       (.C(s00_axi_aclk),
        .CE(\S_CONVERSION_reg[126]_0 [6]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [11]),
        .Q(data7[11]),
        .R(RSTP));
  FDRE \S_CONVERSION_reg[11] 
       (.C(s00_axi_aclk),
        .CE(\S_CONVERSION_reg[126]_0 [0]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [11]),
        .Q(\S_CONVERSION_reg_n_0_[11] ),
        .R(RSTP));
  FDRE \S_CONVERSION_reg[120] 
       (.C(s00_axi_aclk),
        .CE(\S_CONVERSION_reg[126]_0 [6]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [12]),
        .Q(data7[12]),
        .R(RSTP));
  FDRE \S_CONVERSION_reg[121] 
       (.C(s00_axi_aclk),
        .CE(\S_CONVERSION_reg[126]_0 [6]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [13]),
        .Q(data7[13]),
        .R(RSTP));
  FDRE \S_CONVERSION_reg[122] 
       (.C(s00_axi_aclk),
        .CE(\S_CONVERSION_reg[126]_0 [6]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [14]),
        .Q(data7[14]),
        .R(RSTP));
  FDRE \S_CONVERSION_reg[123] 
       (.C(s00_axi_aclk),
        .CE(\S_CONVERSION_reg[126]_0 [6]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [15]),
        .Q(data7[15]),
        .R(RSTP));
  FDRE \S_CONVERSION_reg[124] 
       (.C(s00_axi_aclk),
        .CE(\S_CONVERSION_reg[126]_0 [6]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [16]),
        .Q(data7[16]),
        .R(RSTP));
  FDRE \S_CONVERSION_reg[125] 
       (.C(s00_axi_aclk),
        .CE(\S_CONVERSION_reg[126]_0 [6]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [17]),
        .Q(data7[17]),
        .R(RSTP));
  FDRE \S_CONVERSION_reg[126] 
       (.C(s00_axi_aclk),
        .CE(\S_CONVERSION_reg[126]_0 [7]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [0]),
        .Q(data8[0]),
        .R(RSTP));
  FDRE \S_CONVERSION_reg[127] 
       (.C(s00_axi_aclk),
        .CE(\S_CONVERSION_reg[126]_0 [7]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [1]),
        .Q(data8[1]),
        .R(RSTP));
  FDRE \S_CONVERSION_reg[128] 
       (.C(s00_axi_aclk),
        .CE(\S_CONVERSION_reg[126]_0 [7]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [2]),
        .Q(data8[2]),
        .R(RSTP));
  FDRE \S_CONVERSION_reg[129] 
       (.C(s00_axi_aclk),
        .CE(\S_CONVERSION_reg[126]_0 [7]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [3]),
        .Q(data8[3]),
        .R(RSTP));
  FDRE \S_CONVERSION_reg[12] 
       (.C(s00_axi_aclk),
        .CE(\S_CONVERSION_reg[126]_0 [0]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [12]),
        .Q(\S_CONVERSION_reg_n_0_[12] ),
        .R(RSTP));
  FDRE \S_CONVERSION_reg[130] 
       (.C(s00_axi_aclk),
        .CE(\S_CONVERSION_reg[126]_0 [7]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [4]),
        .Q(data8[4]),
        .R(RSTP));
  FDRE \S_CONVERSION_reg[131] 
       (.C(s00_axi_aclk),
        .CE(\S_CONVERSION_reg[126]_0 [7]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [5]),
        .Q(data8[5]),
        .R(RSTP));
  FDRE \S_CONVERSION_reg[132] 
       (.C(s00_axi_aclk),
        .CE(\S_CONVERSION_reg[126]_0 [7]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [6]),
        .Q(data8[6]),
        .R(RSTP));
  FDRE \S_CONVERSION_reg[133] 
       (.C(s00_axi_aclk),
        .CE(\S_CONVERSION_reg[126]_0 [7]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [7]),
        .Q(data8[7]),
        .R(RSTP));
  FDRE \S_CONVERSION_reg[134] 
       (.C(s00_axi_aclk),
        .CE(\S_CONVERSION_reg[126]_0 [7]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [8]),
        .Q(data8[8]),
        .R(RSTP));
  FDRE \S_CONVERSION_reg[135] 
       (.C(s00_axi_aclk),
        .CE(\S_CONVERSION_reg[126]_0 [7]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [9]),
        .Q(data8[9]),
        .R(RSTP));
  FDRE \S_CONVERSION_reg[136] 
       (.C(s00_axi_aclk),
        .CE(\S_CONVERSION_reg[126]_0 [7]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [10]),
        .Q(data8[10]),
        .R(RSTP));
  FDRE \S_CONVERSION_reg[137] 
       (.C(s00_axi_aclk),
        .CE(\S_CONVERSION_reg[126]_0 [7]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [11]),
        .Q(data8[11]),
        .R(RSTP));
  FDRE \S_CONVERSION_reg[138] 
       (.C(s00_axi_aclk),
        .CE(\S_CONVERSION_reg[126]_0 [7]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [12]),
        .Q(data8[12]),
        .R(RSTP));
  FDRE \S_CONVERSION_reg[139] 
       (.C(s00_axi_aclk),
        .CE(\S_CONVERSION_reg[126]_0 [7]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [13]),
        .Q(data8[13]),
        .R(RSTP));
  FDRE \S_CONVERSION_reg[13] 
       (.C(s00_axi_aclk),
        .CE(\S_CONVERSION_reg[126]_0 [0]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [13]),
        .Q(\S_CONVERSION_reg_n_0_[13] ),
        .R(RSTP));
  FDRE \S_CONVERSION_reg[140] 
       (.C(s00_axi_aclk),
        .CE(\S_CONVERSION_reg[126]_0 [7]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [14]),
        .Q(data8[14]),
        .R(RSTP));
  FDRE \S_CONVERSION_reg[141] 
       (.C(s00_axi_aclk),
        .CE(\S_CONVERSION_reg[126]_0 [7]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [15]),
        .Q(data8[15]),
        .R(RSTP));
  FDRE \S_CONVERSION_reg[142] 
       (.C(s00_axi_aclk),
        .CE(\S_CONVERSION_reg[126]_0 [7]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [16]),
        .Q(data8[16]),
        .R(RSTP));
  FDRE \S_CONVERSION_reg[143] 
       (.C(s00_axi_aclk),
        .CE(\S_CONVERSION_reg[126]_0 [7]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [17]),
        .Q(data8[17]),
        .R(RSTP));
  FDRE \S_CONVERSION_reg[14] 
       (.C(s00_axi_aclk),
        .CE(\S_CONVERSION_reg[126]_0 [0]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [14]),
        .Q(\S_CONVERSION_reg_n_0_[14] ),
        .R(RSTP));
  FDRE \S_CONVERSION_reg[15] 
       (.C(s00_axi_aclk),
        .CE(\S_CONVERSION_reg[126]_0 [0]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [15]),
        .Q(\S_CONVERSION_reg_n_0_[15] ),
        .R(RSTP));
  FDRE \S_CONVERSION_reg[16] 
       (.C(s00_axi_aclk),
        .CE(\S_CONVERSION_reg[126]_0 [0]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [16]),
        .Q(\S_CONVERSION_reg_n_0_[16] ),
        .R(RSTP));
  FDRE \S_CONVERSION_reg[17] 
       (.C(s00_axi_aclk),
        .CE(\S_CONVERSION_reg[126]_0 [0]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [17]),
        .Q(\S_CONVERSION_reg_n_0_[17] ),
        .R(RSTP));
  FDRE \S_CONVERSION_reg[18] 
       (.C(s00_axi_aclk),
        .CE(\S_CONVERSION_reg[126]_0 [1]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [0]),
        .Q(data2[0]),
        .R(RSTP));
  FDRE \S_CONVERSION_reg[19] 
       (.C(s00_axi_aclk),
        .CE(\S_CONVERSION_reg[126]_0 [1]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [1]),
        .Q(data2[1]),
        .R(RSTP));
  FDRE \S_CONVERSION_reg[1] 
       (.C(s00_axi_aclk),
        .CE(\S_CONVERSION_reg[126]_0 [0]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [1]),
        .Q(\S_CONVERSION_reg_n_0_[1] ),
        .R(RSTP));
  FDRE \S_CONVERSION_reg[20] 
       (.C(s00_axi_aclk),
        .CE(\S_CONVERSION_reg[126]_0 [1]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [2]),
        .Q(data2[2]),
        .R(RSTP));
  FDRE \S_CONVERSION_reg[21] 
       (.C(s00_axi_aclk),
        .CE(\S_CONVERSION_reg[126]_0 [1]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [3]),
        .Q(data2[3]),
        .R(RSTP));
  FDRE \S_CONVERSION_reg[22] 
       (.C(s00_axi_aclk),
        .CE(\S_CONVERSION_reg[126]_0 [1]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [4]),
        .Q(data2[4]),
        .R(RSTP));
  FDRE \S_CONVERSION_reg[23] 
       (.C(s00_axi_aclk),
        .CE(\S_CONVERSION_reg[126]_0 [1]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [5]),
        .Q(data2[5]),
        .R(RSTP));
  FDRE \S_CONVERSION_reg[24] 
       (.C(s00_axi_aclk),
        .CE(\S_CONVERSION_reg[126]_0 [1]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [6]),
        .Q(data2[6]),
        .R(RSTP));
  FDRE \S_CONVERSION_reg[25] 
       (.C(s00_axi_aclk),
        .CE(\S_CONVERSION_reg[126]_0 [1]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [7]),
        .Q(data2[7]),
        .R(RSTP));
  FDRE \S_CONVERSION_reg[26] 
       (.C(s00_axi_aclk),
        .CE(\S_CONVERSION_reg[126]_0 [1]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [8]),
        .Q(data2[8]),
        .R(RSTP));
  FDRE \S_CONVERSION_reg[27] 
       (.C(s00_axi_aclk),
        .CE(\S_CONVERSION_reg[126]_0 [1]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [9]),
        .Q(data2[9]),
        .R(RSTP));
  FDRE \S_CONVERSION_reg[28] 
       (.C(s00_axi_aclk),
        .CE(\S_CONVERSION_reg[126]_0 [1]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [10]),
        .Q(data2[10]),
        .R(RSTP));
  FDRE \S_CONVERSION_reg[29] 
       (.C(s00_axi_aclk),
        .CE(\S_CONVERSION_reg[126]_0 [1]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [11]),
        .Q(data2[11]),
        .R(RSTP));
  FDRE \S_CONVERSION_reg[2] 
       (.C(s00_axi_aclk),
        .CE(\S_CONVERSION_reg[126]_0 [0]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [2]),
        .Q(\S_CONVERSION_reg_n_0_[2] ),
        .R(RSTP));
  FDRE \S_CONVERSION_reg[30] 
       (.C(s00_axi_aclk),
        .CE(\S_CONVERSION_reg[126]_0 [1]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [12]),
        .Q(data2[12]),
        .R(RSTP));
  FDRE \S_CONVERSION_reg[31] 
       (.C(s00_axi_aclk),
        .CE(\S_CONVERSION_reg[126]_0 [1]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [13]),
        .Q(data2[13]),
        .R(RSTP));
  FDRE \S_CONVERSION_reg[32] 
       (.C(s00_axi_aclk),
        .CE(\S_CONVERSION_reg[126]_0 [1]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [14]),
        .Q(data2[14]),
        .R(RSTP));
  FDRE \S_CONVERSION_reg[33] 
       (.C(s00_axi_aclk),
        .CE(\S_CONVERSION_reg[126]_0 [1]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [15]),
        .Q(data2[15]),
        .R(RSTP));
  FDRE \S_CONVERSION_reg[34] 
       (.C(s00_axi_aclk),
        .CE(\S_CONVERSION_reg[126]_0 [1]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [16]),
        .Q(data2[16]),
        .R(RSTP));
  FDRE \S_CONVERSION_reg[35] 
       (.C(s00_axi_aclk),
        .CE(\S_CONVERSION_reg[126]_0 [1]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [17]),
        .Q(data2[17]),
        .R(RSTP));
  FDRE \S_CONVERSION_reg[36] 
       (.C(s00_axi_aclk),
        .CE(\S_CONVERSION_reg[126]_0 [2]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [0]),
        .Q(data3[0]),
        .R(RSTP));
  FDRE \S_CONVERSION_reg[37] 
       (.C(s00_axi_aclk),
        .CE(\S_CONVERSION_reg[126]_0 [2]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [1]),
        .Q(data3[1]),
        .R(RSTP));
  FDRE \S_CONVERSION_reg[38] 
       (.C(s00_axi_aclk),
        .CE(\S_CONVERSION_reg[126]_0 [2]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [2]),
        .Q(data3[2]),
        .R(RSTP));
  FDRE \S_CONVERSION_reg[39] 
       (.C(s00_axi_aclk),
        .CE(\S_CONVERSION_reg[126]_0 [2]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [3]),
        .Q(data3[3]),
        .R(RSTP));
  FDRE \S_CONVERSION_reg[3] 
       (.C(s00_axi_aclk),
        .CE(\S_CONVERSION_reg[126]_0 [0]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [3]),
        .Q(\S_CONVERSION_reg_n_0_[3] ),
        .R(RSTP));
  FDRE \S_CONVERSION_reg[40] 
       (.C(s00_axi_aclk),
        .CE(\S_CONVERSION_reg[126]_0 [2]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [4]),
        .Q(data3[4]),
        .R(RSTP));
  FDRE \S_CONVERSION_reg[41] 
       (.C(s00_axi_aclk),
        .CE(\S_CONVERSION_reg[126]_0 [2]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [5]),
        .Q(data3[5]),
        .R(RSTP));
  FDRE \S_CONVERSION_reg[42] 
       (.C(s00_axi_aclk),
        .CE(\S_CONVERSION_reg[126]_0 [2]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [6]),
        .Q(data3[6]),
        .R(RSTP));
  FDRE \S_CONVERSION_reg[43] 
       (.C(s00_axi_aclk),
        .CE(\S_CONVERSION_reg[126]_0 [2]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [7]),
        .Q(data3[7]),
        .R(RSTP));
  FDRE \S_CONVERSION_reg[44] 
       (.C(s00_axi_aclk),
        .CE(\S_CONVERSION_reg[126]_0 [2]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [8]),
        .Q(data3[8]),
        .R(RSTP));
  FDRE \S_CONVERSION_reg[45] 
       (.C(s00_axi_aclk),
        .CE(\S_CONVERSION_reg[126]_0 [2]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [9]),
        .Q(data3[9]),
        .R(RSTP));
  FDRE \S_CONVERSION_reg[46] 
       (.C(s00_axi_aclk),
        .CE(\S_CONVERSION_reg[126]_0 [2]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [10]),
        .Q(data3[10]),
        .R(RSTP));
  FDRE \S_CONVERSION_reg[47] 
       (.C(s00_axi_aclk),
        .CE(\S_CONVERSION_reg[126]_0 [2]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [11]),
        .Q(data3[11]),
        .R(RSTP));
  FDRE \S_CONVERSION_reg[48] 
       (.C(s00_axi_aclk),
        .CE(\S_CONVERSION_reg[126]_0 [2]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [12]),
        .Q(data3[12]),
        .R(RSTP));
  FDRE \S_CONVERSION_reg[49] 
       (.C(s00_axi_aclk),
        .CE(\S_CONVERSION_reg[126]_0 [2]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [13]),
        .Q(data3[13]),
        .R(RSTP));
  FDRE \S_CONVERSION_reg[4] 
       (.C(s00_axi_aclk),
        .CE(\S_CONVERSION_reg[126]_0 [0]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [4]),
        .Q(\S_CONVERSION_reg_n_0_[4] ),
        .R(RSTP));
  FDRE \S_CONVERSION_reg[50] 
       (.C(s00_axi_aclk),
        .CE(\S_CONVERSION_reg[126]_0 [2]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [14]),
        .Q(data3[14]),
        .R(RSTP));
  FDRE \S_CONVERSION_reg[51] 
       (.C(s00_axi_aclk),
        .CE(\S_CONVERSION_reg[126]_0 [2]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [15]),
        .Q(data3[15]),
        .R(RSTP));
  FDRE \S_CONVERSION_reg[52] 
       (.C(s00_axi_aclk),
        .CE(\S_CONVERSION_reg[126]_0 [2]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [16]),
        .Q(data3[16]),
        .R(RSTP));
  FDRE \S_CONVERSION_reg[53] 
       (.C(s00_axi_aclk),
        .CE(\S_CONVERSION_reg[126]_0 [2]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [17]),
        .Q(data3[17]),
        .R(RSTP));
  FDRE \S_CONVERSION_reg[54] 
       (.C(s00_axi_aclk),
        .CE(\S_CONVERSION_reg[126]_0 [3]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [0]),
        .Q(data4[0]),
        .R(RSTP));
  FDRE \S_CONVERSION_reg[55] 
       (.C(s00_axi_aclk),
        .CE(\S_CONVERSION_reg[126]_0 [3]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [1]),
        .Q(data4[1]),
        .R(RSTP));
  FDRE \S_CONVERSION_reg[56] 
       (.C(s00_axi_aclk),
        .CE(\S_CONVERSION_reg[126]_0 [3]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [2]),
        .Q(data4[2]),
        .R(RSTP));
  FDRE \S_CONVERSION_reg[57] 
       (.C(s00_axi_aclk),
        .CE(\S_CONVERSION_reg[126]_0 [3]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [3]),
        .Q(data4[3]),
        .R(RSTP));
  FDRE \S_CONVERSION_reg[58] 
       (.C(s00_axi_aclk),
        .CE(\S_CONVERSION_reg[126]_0 [3]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [4]),
        .Q(data4[4]),
        .R(RSTP));
  FDRE \S_CONVERSION_reg[59] 
       (.C(s00_axi_aclk),
        .CE(\S_CONVERSION_reg[126]_0 [3]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [5]),
        .Q(data4[5]),
        .R(RSTP));
  FDRE \S_CONVERSION_reg[5] 
       (.C(s00_axi_aclk),
        .CE(\S_CONVERSION_reg[126]_0 [0]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [5]),
        .Q(\S_CONVERSION_reg_n_0_[5] ),
        .R(RSTP));
  FDRE \S_CONVERSION_reg[60] 
       (.C(s00_axi_aclk),
        .CE(\S_CONVERSION_reg[126]_0 [3]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [6]),
        .Q(data4[6]),
        .R(RSTP));
  FDRE \S_CONVERSION_reg[61] 
       (.C(s00_axi_aclk),
        .CE(\S_CONVERSION_reg[126]_0 [3]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [7]),
        .Q(data4[7]),
        .R(RSTP));
  FDRE \S_CONVERSION_reg[62] 
       (.C(s00_axi_aclk),
        .CE(\S_CONVERSION_reg[126]_0 [3]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [8]),
        .Q(data4[8]),
        .R(RSTP));
  FDRE \S_CONVERSION_reg[63] 
       (.C(s00_axi_aclk),
        .CE(\S_CONVERSION_reg[126]_0 [3]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [9]),
        .Q(data4[9]),
        .R(RSTP));
  FDRE \S_CONVERSION_reg[64] 
       (.C(s00_axi_aclk),
        .CE(\S_CONVERSION_reg[126]_0 [3]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [10]),
        .Q(data4[10]),
        .R(RSTP));
  FDRE \S_CONVERSION_reg[65] 
       (.C(s00_axi_aclk),
        .CE(\S_CONVERSION_reg[126]_0 [3]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [11]),
        .Q(data4[11]),
        .R(RSTP));
  FDRE \S_CONVERSION_reg[66] 
       (.C(s00_axi_aclk),
        .CE(\S_CONVERSION_reg[126]_0 [3]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [12]),
        .Q(data4[12]),
        .R(RSTP));
  FDRE \S_CONVERSION_reg[67] 
       (.C(s00_axi_aclk),
        .CE(\S_CONVERSION_reg[126]_0 [3]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [13]),
        .Q(data4[13]),
        .R(RSTP));
  FDRE \S_CONVERSION_reg[68] 
       (.C(s00_axi_aclk),
        .CE(\S_CONVERSION_reg[126]_0 [3]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [14]),
        .Q(data4[14]),
        .R(RSTP));
  FDRE \S_CONVERSION_reg[69] 
       (.C(s00_axi_aclk),
        .CE(\S_CONVERSION_reg[126]_0 [3]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [15]),
        .Q(data4[15]),
        .R(RSTP));
  FDRE \S_CONVERSION_reg[6] 
       (.C(s00_axi_aclk),
        .CE(\S_CONVERSION_reg[126]_0 [0]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [6]),
        .Q(\S_CONVERSION_reg_n_0_[6] ),
        .R(RSTP));
  FDRE \S_CONVERSION_reg[70] 
       (.C(s00_axi_aclk),
        .CE(\S_CONVERSION_reg[126]_0 [3]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [16]),
        .Q(data4[16]),
        .R(RSTP));
  FDRE \S_CONVERSION_reg[71] 
       (.C(s00_axi_aclk),
        .CE(\S_CONVERSION_reg[126]_0 [3]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [17]),
        .Q(data4[17]),
        .R(RSTP));
  FDRE \S_CONVERSION_reg[72] 
       (.C(s00_axi_aclk),
        .CE(\S_CONVERSION_reg[126]_0 [4]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [0]),
        .Q(data5[0]),
        .R(RSTP));
  FDRE \S_CONVERSION_reg[73] 
       (.C(s00_axi_aclk),
        .CE(\S_CONVERSION_reg[126]_0 [4]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [1]),
        .Q(data5[1]),
        .R(RSTP));
  FDRE \S_CONVERSION_reg[74] 
       (.C(s00_axi_aclk),
        .CE(\S_CONVERSION_reg[126]_0 [4]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [2]),
        .Q(data5[2]),
        .R(RSTP));
  FDRE \S_CONVERSION_reg[75] 
       (.C(s00_axi_aclk),
        .CE(\S_CONVERSION_reg[126]_0 [4]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [3]),
        .Q(data5[3]),
        .R(RSTP));
  FDRE \S_CONVERSION_reg[76] 
       (.C(s00_axi_aclk),
        .CE(\S_CONVERSION_reg[126]_0 [4]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [4]),
        .Q(data5[4]),
        .R(RSTP));
  FDRE \S_CONVERSION_reg[77] 
       (.C(s00_axi_aclk),
        .CE(\S_CONVERSION_reg[126]_0 [4]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [5]),
        .Q(data5[5]),
        .R(RSTP));
  FDRE \S_CONVERSION_reg[78] 
       (.C(s00_axi_aclk),
        .CE(\S_CONVERSION_reg[126]_0 [4]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [6]),
        .Q(data5[6]),
        .R(RSTP));
  FDRE \S_CONVERSION_reg[79] 
       (.C(s00_axi_aclk),
        .CE(\S_CONVERSION_reg[126]_0 [4]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [7]),
        .Q(data5[7]),
        .R(RSTP));
  FDRE \S_CONVERSION_reg[7] 
       (.C(s00_axi_aclk),
        .CE(\S_CONVERSION_reg[126]_0 [0]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [7]),
        .Q(\S_CONVERSION_reg_n_0_[7] ),
        .R(RSTP));
  FDRE \S_CONVERSION_reg[80] 
       (.C(s00_axi_aclk),
        .CE(\S_CONVERSION_reg[126]_0 [4]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [8]),
        .Q(data5[8]),
        .R(RSTP));
  FDRE \S_CONVERSION_reg[81] 
       (.C(s00_axi_aclk),
        .CE(\S_CONVERSION_reg[126]_0 [4]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [9]),
        .Q(data5[9]),
        .R(RSTP));
  FDRE \S_CONVERSION_reg[82] 
       (.C(s00_axi_aclk),
        .CE(\S_CONVERSION_reg[126]_0 [4]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [10]),
        .Q(data5[10]),
        .R(RSTP));
  FDRE \S_CONVERSION_reg[83] 
       (.C(s00_axi_aclk),
        .CE(\S_CONVERSION_reg[126]_0 [4]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [11]),
        .Q(data5[11]),
        .R(RSTP));
  FDRE \S_CONVERSION_reg[84] 
       (.C(s00_axi_aclk),
        .CE(\S_CONVERSION_reg[126]_0 [4]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [12]),
        .Q(data5[12]),
        .R(RSTP));
  FDRE \S_CONVERSION_reg[85] 
       (.C(s00_axi_aclk),
        .CE(\S_CONVERSION_reg[126]_0 [4]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [13]),
        .Q(data5[13]),
        .R(RSTP));
  FDRE \S_CONVERSION_reg[86] 
       (.C(s00_axi_aclk),
        .CE(\S_CONVERSION_reg[126]_0 [4]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [14]),
        .Q(data5[14]),
        .R(RSTP));
  FDRE \S_CONVERSION_reg[87] 
       (.C(s00_axi_aclk),
        .CE(\S_CONVERSION_reg[126]_0 [4]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [15]),
        .Q(data5[15]),
        .R(RSTP));
  FDRE \S_CONVERSION_reg[88] 
       (.C(s00_axi_aclk),
        .CE(\S_CONVERSION_reg[126]_0 [4]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [16]),
        .Q(data5[16]),
        .R(RSTP));
  FDRE \S_CONVERSION_reg[89] 
       (.C(s00_axi_aclk),
        .CE(\S_CONVERSION_reg[126]_0 [4]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [17]),
        .Q(data5[17]),
        .R(RSTP));
  FDRE \S_CONVERSION_reg[8] 
       (.C(s00_axi_aclk),
        .CE(\S_CONVERSION_reg[126]_0 [0]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [8]),
        .Q(\S_CONVERSION_reg_n_0_[8] ),
        .R(RSTP));
  FDRE \S_CONVERSION_reg[90] 
       (.C(s00_axi_aclk),
        .CE(\S_CONVERSION_reg[126]_0 [5]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [0]),
        .Q(data6[0]),
        .R(RSTP));
  FDRE \S_CONVERSION_reg[91] 
       (.C(s00_axi_aclk),
        .CE(\S_CONVERSION_reg[126]_0 [5]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [1]),
        .Q(data6[1]),
        .R(RSTP));
  FDRE \S_CONVERSION_reg[92] 
       (.C(s00_axi_aclk),
        .CE(\S_CONVERSION_reg[126]_0 [5]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [2]),
        .Q(data6[2]),
        .R(RSTP));
  FDRE \S_CONVERSION_reg[93] 
       (.C(s00_axi_aclk),
        .CE(\S_CONVERSION_reg[126]_0 [5]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [3]),
        .Q(data6[3]),
        .R(RSTP));
  FDRE \S_CONVERSION_reg[94] 
       (.C(s00_axi_aclk),
        .CE(\S_CONVERSION_reg[126]_0 [5]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [4]),
        .Q(data6[4]),
        .R(RSTP));
  FDRE \S_CONVERSION_reg[95] 
       (.C(s00_axi_aclk),
        .CE(\S_CONVERSION_reg[126]_0 [5]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [5]),
        .Q(data6[5]),
        .R(RSTP));
  FDRE \S_CONVERSION_reg[96] 
       (.C(s00_axi_aclk),
        .CE(\S_CONVERSION_reg[126]_0 [5]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [6]),
        .Q(data6[6]),
        .R(RSTP));
  FDRE \S_CONVERSION_reg[97] 
       (.C(s00_axi_aclk),
        .CE(\S_CONVERSION_reg[126]_0 [5]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [7]),
        .Q(data6[7]),
        .R(RSTP));
  FDRE \S_CONVERSION_reg[98] 
       (.C(s00_axi_aclk),
        .CE(\S_CONVERSION_reg[126]_0 [5]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [8]),
        .Q(data6[8]),
        .R(RSTP));
  FDRE \S_CONVERSION_reg[99] 
       (.C(s00_axi_aclk),
        .CE(\S_CONVERSION_reg[126]_0 [5]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [9]),
        .Q(data6[9]),
        .R(RSTP));
  FDRE \S_CONVERSION_reg[9] 
       (.C(s00_axi_aclk),
        .CE(\S_CONVERSION_reg[126]_0 [0]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [9]),
        .Q(\S_CONVERSION_reg_n_0_[9] ),
        .R(RSTP));
  (* SOFT_HLUTNM = "soft_lutpair107" *) 
  LUT2 #(
    .INIT(4'hB)) 
    \S_CONV_COUNTER[0]_i_1 
       (.I0(\S_ENABLE_reg[0]_0 ),
        .I1(S_CONV_COUNTER[0]),
        .O(\S_CONV_COUNTER[0]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair107" *) 
  LUT3 #(
    .INIT(8'h41)) 
    \S_CONV_COUNTER[1]_i_1 
       (.I0(\S_ENABLE_reg[0]_0 ),
        .I1(S_CONV_COUNTER[0]),
        .I2(S_CONV_COUNTER[1]),
        .O(\S_CONV_COUNTER[1]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair84" *) 
  LUT4 #(
    .INIT(16'h00E1)) 
    \S_CONV_COUNTER[2]_i_1 
       (.I0(S_CONV_COUNTER[1]),
        .I1(S_CONV_COUNTER[0]),
        .I2(S_CONV_COUNTER[2]),
        .I3(\S_ENABLE_reg[0]_0 ),
        .O(\S_CONV_COUNTER[2]_i_1_n_0 ));
  LUT6 #(
    .INIT(64'h040F040F0400040F)) 
    \S_CONV_COUNTER[3]_i_1 
       (.I0(Q[1]),
        .I1(Q[0]),
        .I2(\S_ENABLE_reg[0] ),
        .I3(\S_ENABLE_reg[0]_0 ),
        .I4(raw_to_si_n_137),
        .I5(S_CONV_COUNTER[3]),
        .O(\S_CONV_COUNTER[3]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair84" *) 
  LUT5 #(
    .INIT(32'hFFFEAAAB)) 
    \S_CONV_COUNTER[3]_i_2 
       (.I0(\S_ENABLE_reg[0]_0 ),
        .I1(S_CONV_COUNTER[0]),
        .I2(S_CONV_COUNTER[1]),
        .I3(S_CONV_COUNTER[2]),
        .I4(S_CONV_COUNTER[3]),
        .O(\S_CONV_COUNTER[3]_i_2_n_0 ));
  FDRE \S_CONV_COUNTER_reg[0] 
       (.C(s00_axi_aclk),
        .CE(\S_CONV_COUNTER[3]_i_1_n_0 ),
        .D(\S_CONV_COUNTER[0]_i_1_n_0 ),
        .Q(S_CONV_COUNTER[0]),
        .R(RSTP));
  FDRE \S_CONV_COUNTER_reg[1] 
       (.C(s00_axi_aclk),
        .CE(\S_CONV_COUNTER[3]_i_1_n_0 ),
        .D(\S_CONV_COUNTER[1]_i_1_n_0 ),
        .Q(S_CONV_COUNTER[1]),
        .R(RSTP));
  FDRE \S_CONV_COUNTER_reg[2] 
       (.C(s00_axi_aclk),
        .CE(\S_CONV_COUNTER[3]_i_1_n_0 ),
        .D(\S_CONV_COUNTER[2]_i_1_n_0 ),
        .Q(S_CONV_COUNTER[2]),
        .R(RSTP));
  FDRE \S_CONV_COUNTER_reg[3] 
       (.C(s00_axi_aclk),
        .CE(\S_CONV_COUNTER[3]_i_1_n_0 ),
        .D(\S_CONV_COUNTER[3]_i_2_n_0 ),
        .Q(S_CONV_COUNTER[3]),
        .R(RSTP));
  FDSE S_DUMMY_SAMPLE_reg
       (.C(s00_axi_aclk),
        .CE(1'b1),
        .D(S_DUMMY_SAMPLE_reg_0),
        .Q(S_DUMMY_SAMPLE),
        .S(RSTP));
  FDRE S_MANUAL_reg
       (.C(s00_axi_aclk),
        .CE(1'b1),
        .D(S_MANUAL_reg_1),
        .Q(S_MANUAL_reg_0),
        .R(1'b0));
  LUT6 #(
    .INIT(64'h8F808F8F8F808080)) 
    \S_OFFSET_S_C[0]_i_1 
       (.I0(S_OFFSET[112]),
        .I1(\S_RAW_VALUE_S_C[15]_i_3_n_0 ),
        .I2(S_CHANNEL_COUNTER[3]),
        .I3(\S_OFFSET_S_C[0]_i_2_n_0 ),
        .I4(S_CHANNEL_COUNTER[2]),
        .I5(\S_OFFSET_S_C[0]_i_3_n_0 ),
        .O(\S_OFFSET_S_C[0]_i_1_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \S_OFFSET_S_C[0]_i_2 
       (.I0(S_OFFSET[96]),
        .I1(S_OFFSET[80]),
        .I2(S_CHANNEL_COUNTER[1]),
        .I3(S_OFFSET[64]),
        .I4(S_CHANNEL_COUNTER[0]),
        .I5(S_OFFSET[48]),
        .O(\S_OFFSET_S_C[0]_i_2_n_0 ));
  LUT5 #(
    .INIT(32'hAFC0A0C0)) 
    \S_OFFSET_S_C[0]_i_3 
       (.I0(S_OFFSET[32]),
        .I1(S_OFFSET[16]),
        .I2(S_CHANNEL_COUNTER[1]),
        .I3(S_CHANNEL_COUNTER[0]),
        .I4(S_OFFSET[0]),
        .O(\S_OFFSET_S_C[0]_i_3_n_0 ));
  LUT6 #(
    .INIT(64'h8F808F8F8F808080)) 
    \S_OFFSET_S_C[10]_i_1 
       (.I0(S_OFFSET[122]),
        .I1(\S_RAW_VALUE_S_C[15]_i_3_n_0 ),
        .I2(S_CHANNEL_COUNTER[3]),
        .I3(\S_OFFSET_S_C[10]_i_2_n_0 ),
        .I4(S_CHANNEL_COUNTER[2]),
        .I5(\S_OFFSET_S_C[10]_i_3_n_0 ),
        .O(\S_OFFSET_S_C[10]_i_1_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \S_OFFSET_S_C[10]_i_2 
       (.I0(S_OFFSET[106]),
        .I1(S_OFFSET[90]),
        .I2(S_CHANNEL_COUNTER[1]),
        .I3(S_OFFSET[74]),
        .I4(S_CHANNEL_COUNTER[0]),
        .I5(S_OFFSET[58]),
        .O(\S_OFFSET_S_C[10]_i_2_n_0 ));
  LUT5 #(
    .INIT(32'hAFC0A0C0)) 
    \S_OFFSET_S_C[10]_i_3 
       (.I0(S_OFFSET[42]),
        .I1(S_OFFSET[26]),
        .I2(S_CHANNEL_COUNTER[1]),
        .I3(S_CHANNEL_COUNTER[0]),
        .I4(S_OFFSET[10]),
        .O(\S_OFFSET_S_C[10]_i_3_n_0 ));
  LUT6 #(
    .INIT(64'h8F808F8F8F808080)) 
    \S_OFFSET_S_C[11]_i_1 
       (.I0(S_OFFSET[123]),
        .I1(\S_RAW_VALUE_S_C[15]_i_3_n_0 ),
        .I2(S_CHANNEL_COUNTER[3]),
        .I3(\S_OFFSET_S_C[11]_i_2_n_0 ),
        .I4(S_CHANNEL_COUNTER[2]),
        .I5(\S_OFFSET_S_C[11]_i_3_n_0 ),
        .O(\S_OFFSET_S_C[11]_i_1_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \S_OFFSET_S_C[11]_i_2 
       (.I0(S_OFFSET[107]),
        .I1(S_OFFSET[91]),
        .I2(S_CHANNEL_COUNTER[1]),
        .I3(S_OFFSET[75]),
        .I4(S_CHANNEL_COUNTER[0]),
        .I5(S_OFFSET[59]),
        .O(\S_OFFSET_S_C[11]_i_2_n_0 ));
  LUT5 #(
    .INIT(32'hAFC0A0C0)) 
    \S_OFFSET_S_C[11]_i_3 
       (.I0(S_OFFSET[43]),
        .I1(S_OFFSET[27]),
        .I2(S_CHANNEL_COUNTER[1]),
        .I3(S_CHANNEL_COUNTER[0]),
        .I4(S_OFFSET[11]),
        .O(\S_OFFSET_S_C[11]_i_3_n_0 ));
  LUT6 #(
    .INIT(64'h8F808F8F8F808080)) 
    \S_OFFSET_S_C[12]_i_1 
       (.I0(S_OFFSET[124]),
        .I1(\S_RAW_VALUE_S_C[15]_i_3_n_0 ),
        .I2(S_CHANNEL_COUNTER[3]),
        .I3(\S_OFFSET_S_C[12]_i_2_n_0 ),
        .I4(S_CHANNEL_COUNTER[2]),
        .I5(\S_OFFSET_S_C[12]_i_3_n_0 ),
        .O(\S_OFFSET_S_C[12]_i_1_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \S_OFFSET_S_C[12]_i_2 
       (.I0(S_OFFSET[108]),
        .I1(S_OFFSET[92]),
        .I2(S_CHANNEL_COUNTER[1]),
        .I3(S_OFFSET[76]),
        .I4(S_CHANNEL_COUNTER[0]),
        .I5(S_OFFSET[60]),
        .O(\S_OFFSET_S_C[12]_i_2_n_0 ));
  LUT5 #(
    .INIT(32'hAFC0A0C0)) 
    \S_OFFSET_S_C[12]_i_3 
       (.I0(S_OFFSET[44]),
        .I1(S_OFFSET[28]),
        .I2(S_CHANNEL_COUNTER[1]),
        .I3(S_CHANNEL_COUNTER[0]),
        .I4(S_OFFSET[12]),
        .O(\S_OFFSET_S_C[12]_i_3_n_0 ));
  LUT6 #(
    .INIT(64'h8F808F8F8F808080)) 
    \S_OFFSET_S_C[13]_i_1 
       (.I0(S_OFFSET[125]),
        .I1(\S_RAW_VALUE_S_C[15]_i_3_n_0 ),
        .I2(S_CHANNEL_COUNTER[3]),
        .I3(\S_OFFSET_S_C[13]_i_2_n_0 ),
        .I4(S_CHANNEL_COUNTER[2]),
        .I5(\S_OFFSET_S_C[13]_i_3_n_0 ),
        .O(\S_OFFSET_S_C[13]_i_1_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \S_OFFSET_S_C[13]_i_2 
       (.I0(S_OFFSET[109]),
        .I1(S_OFFSET[93]),
        .I2(S_CHANNEL_COUNTER[1]),
        .I3(S_OFFSET[77]),
        .I4(S_CHANNEL_COUNTER[0]),
        .I5(S_OFFSET[61]),
        .O(\S_OFFSET_S_C[13]_i_2_n_0 ));
  LUT5 #(
    .INIT(32'hAFC0A0C0)) 
    \S_OFFSET_S_C[13]_i_3 
       (.I0(S_OFFSET[45]),
        .I1(S_OFFSET[29]),
        .I2(S_CHANNEL_COUNTER[1]),
        .I3(S_CHANNEL_COUNTER[0]),
        .I4(S_OFFSET[13]),
        .O(\S_OFFSET_S_C[13]_i_3_n_0 ));
  LUT6 #(
    .INIT(64'h8F808F8F8F808080)) 
    \S_OFFSET_S_C[14]_i_1 
       (.I0(S_OFFSET[126]),
        .I1(\S_RAW_VALUE_S_C[15]_i_3_n_0 ),
        .I2(S_CHANNEL_COUNTER[3]),
        .I3(\S_OFFSET_S_C[14]_i_2_n_0 ),
        .I4(S_CHANNEL_COUNTER[2]),
        .I5(\S_OFFSET_S_C[14]_i_3_n_0 ),
        .O(\S_OFFSET_S_C[14]_i_1_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \S_OFFSET_S_C[14]_i_2 
       (.I0(S_OFFSET[110]),
        .I1(S_OFFSET[94]),
        .I2(S_CHANNEL_COUNTER[1]),
        .I3(S_OFFSET[78]),
        .I4(S_CHANNEL_COUNTER[0]),
        .I5(S_OFFSET[62]),
        .O(\S_OFFSET_S_C[14]_i_2_n_0 ));
  LUT5 #(
    .INIT(32'hAFC0A0C0)) 
    \S_OFFSET_S_C[14]_i_3 
       (.I0(S_OFFSET[46]),
        .I1(S_OFFSET[30]),
        .I2(S_CHANNEL_COUNTER[1]),
        .I3(S_CHANNEL_COUNTER[0]),
        .I4(S_OFFSET[14]),
        .O(\S_OFFSET_S_C[14]_i_3_n_0 ));
  LUT6 #(
    .INIT(64'h8F808F8F8F808080)) 
    \S_OFFSET_S_C[15]_i_1 
       (.I0(S_OFFSET[127]),
        .I1(\S_RAW_VALUE_S_C[15]_i_3_n_0 ),
        .I2(S_CHANNEL_COUNTER[3]),
        .I3(\S_OFFSET_S_C[15]_i_2_n_0 ),
        .I4(S_CHANNEL_COUNTER[2]),
        .I5(\S_OFFSET_S_C[15]_i_3_n_0 ),
        .O(\S_OFFSET_S_C[15]_i_1_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \S_OFFSET_S_C[15]_i_2 
       (.I0(S_OFFSET[111]),
        .I1(S_OFFSET[95]),
        .I2(S_CHANNEL_COUNTER[1]),
        .I3(S_OFFSET[79]),
        .I4(S_CHANNEL_COUNTER[0]),
        .I5(S_OFFSET[63]),
        .O(\S_OFFSET_S_C[15]_i_2_n_0 ));
  LUT5 #(
    .INIT(32'hAFC0A0C0)) 
    \S_OFFSET_S_C[15]_i_3 
       (.I0(S_OFFSET[47]),
        .I1(S_OFFSET[31]),
        .I2(S_CHANNEL_COUNTER[1]),
        .I3(S_CHANNEL_COUNTER[0]),
        .I4(S_OFFSET[15]),
        .O(\S_OFFSET_S_C[15]_i_3_n_0 ));
  LUT6 #(
    .INIT(64'h8F808F8F8F808080)) 
    \S_OFFSET_S_C[1]_i_1 
       (.I0(S_OFFSET[113]),
        .I1(\S_RAW_VALUE_S_C[15]_i_3_n_0 ),
        .I2(S_CHANNEL_COUNTER[3]),
        .I3(\S_OFFSET_S_C[1]_i_2_n_0 ),
        .I4(S_CHANNEL_COUNTER[2]),
        .I5(\S_OFFSET_S_C[1]_i_3_n_0 ),
        .O(\S_OFFSET_S_C[1]_i_1_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \S_OFFSET_S_C[1]_i_2 
       (.I0(S_OFFSET[97]),
        .I1(S_OFFSET[81]),
        .I2(S_CHANNEL_COUNTER[1]),
        .I3(S_OFFSET[65]),
        .I4(S_CHANNEL_COUNTER[0]),
        .I5(S_OFFSET[49]),
        .O(\S_OFFSET_S_C[1]_i_2_n_0 ));
  LUT5 #(
    .INIT(32'hAFC0A0C0)) 
    \S_OFFSET_S_C[1]_i_3 
       (.I0(S_OFFSET[33]),
        .I1(S_OFFSET[17]),
        .I2(S_CHANNEL_COUNTER[1]),
        .I3(S_CHANNEL_COUNTER[0]),
        .I4(S_OFFSET[1]),
        .O(\S_OFFSET_S_C[1]_i_3_n_0 ));
  LUT6 #(
    .INIT(64'h8F808F8F8F808080)) 
    \S_OFFSET_S_C[2]_i_1 
       (.I0(S_OFFSET[114]),
        .I1(\S_RAW_VALUE_S_C[15]_i_3_n_0 ),
        .I2(S_CHANNEL_COUNTER[3]),
        .I3(\S_OFFSET_S_C[2]_i_2_n_0 ),
        .I4(S_CHANNEL_COUNTER[2]),
        .I5(\S_OFFSET_S_C[2]_i_3_n_0 ),
        .O(\S_OFFSET_S_C[2]_i_1_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \S_OFFSET_S_C[2]_i_2 
       (.I0(S_OFFSET[98]),
        .I1(S_OFFSET[82]),
        .I2(S_CHANNEL_COUNTER[1]),
        .I3(S_OFFSET[66]),
        .I4(S_CHANNEL_COUNTER[0]),
        .I5(S_OFFSET[50]),
        .O(\S_OFFSET_S_C[2]_i_2_n_0 ));
  LUT5 #(
    .INIT(32'hAFC0A0C0)) 
    \S_OFFSET_S_C[2]_i_3 
       (.I0(S_OFFSET[34]),
        .I1(S_OFFSET[18]),
        .I2(S_CHANNEL_COUNTER[1]),
        .I3(S_CHANNEL_COUNTER[0]),
        .I4(S_OFFSET[2]),
        .O(\S_OFFSET_S_C[2]_i_3_n_0 ));
  LUT6 #(
    .INIT(64'h8F808F8F8F808080)) 
    \S_OFFSET_S_C[3]_i_1 
       (.I0(S_OFFSET[115]),
        .I1(\S_RAW_VALUE_S_C[15]_i_3_n_0 ),
        .I2(S_CHANNEL_COUNTER[3]),
        .I3(\S_OFFSET_S_C[3]_i_2_n_0 ),
        .I4(S_CHANNEL_COUNTER[2]),
        .I5(\S_OFFSET_S_C[3]_i_3_n_0 ),
        .O(\S_OFFSET_S_C[3]_i_1_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \S_OFFSET_S_C[3]_i_2 
       (.I0(S_OFFSET[99]),
        .I1(S_OFFSET[83]),
        .I2(S_CHANNEL_COUNTER[1]),
        .I3(S_OFFSET[67]),
        .I4(S_CHANNEL_COUNTER[0]),
        .I5(S_OFFSET[51]),
        .O(\S_OFFSET_S_C[3]_i_2_n_0 ));
  LUT5 #(
    .INIT(32'hAFC0A0C0)) 
    \S_OFFSET_S_C[3]_i_3 
       (.I0(S_OFFSET[35]),
        .I1(S_OFFSET[19]),
        .I2(S_CHANNEL_COUNTER[1]),
        .I3(S_CHANNEL_COUNTER[0]),
        .I4(S_OFFSET[3]),
        .O(\S_OFFSET_S_C[3]_i_3_n_0 ));
  LUT6 #(
    .INIT(64'h8F808F8F8F808080)) 
    \S_OFFSET_S_C[4]_i_1 
       (.I0(S_OFFSET[116]),
        .I1(\S_RAW_VALUE_S_C[15]_i_3_n_0 ),
        .I2(S_CHANNEL_COUNTER[3]),
        .I3(\S_OFFSET_S_C[4]_i_2_n_0 ),
        .I4(S_CHANNEL_COUNTER[2]),
        .I5(\S_OFFSET_S_C[4]_i_3_n_0 ),
        .O(\S_OFFSET_S_C[4]_i_1_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \S_OFFSET_S_C[4]_i_2 
       (.I0(S_OFFSET[100]),
        .I1(S_OFFSET[84]),
        .I2(S_CHANNEL_COUNTER[1]),
        .I3(S_OFFSET[68]),
        .I4(S_CHANNEL_COUNTER[0]),
        .I5(S_OFFSET[52]),
        .O(\S_OFFSET_S_C[4]_i_2_n_0 ));
  LUT5 #(
    .INIT(32'hAFC0A0C0)) 
    \S_OFFSET_S_C[4]_i_3 
       (.I0(S_OFFSET[36]),
        .I1(S_OFFSET[20]),
        .I2(S_CHANNEL_COUNTER[1]),
        .I3(S_CHANNEL_COUNTER[0]),
        .I4(S_OFFSET[4]),
        .O(\S_OFFSET_S_C[4]_i_3_n_0 ));
  LUT6 #(
    .INIT(64'h8F808F8F8F808080)) 
    \S_OFFSET_S_C[5]_i_1 
       (.I0(S_OFFSET[117]),
        .I1(\S_RAW_VALUE_S_C[15]_i_3_n_0 ),
        .I2(S_CHANNEL_COUNTER[3]),
        .I3(\S_OFFSET_S_C[5]_i_2_n_0 ),
        .I4(S_CHANNEL_COUNTER[2]),
        .I5(\S_OFFSET_S_C[5]_i_3_n_0 ),
        .O(\S_OFFSET_S_C[5]_i_1_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \S_OFFSET_S_C[5]_i_2 
       (.I0(S_OFFSET[101]),
        .I1(S_OFFSET[85]),
        .I2(S_CHANNEL_COUNTER[1]),
        .I3(S_OFFSET[69]),
        .I4(S_CHANNEL_COUNTER[0]),
        .I5(S_OFFSET[53]),
        .O(\S_OFFSET_S_C[5]_i_2_n_0 ));
  LUT5 #(
    .INIT(32'hAFC0A0C0)) 
    \S_OFFSET_S_C[5]_i_3 
       (.I0(S_OFFSET[37]),
        .I1(S_OFFSET[21]),
        .I2(S_CHANNEL_COUNTER[1]),
        .I3(S_CHANNEL_COUNTER[0]),
        .I4(S_OFFSET[5]),
        .O(\S_OFFSET_S_C[5]_i_3_n_0 ));
  LUT6 #(
    .INIT(64'h8F808F8F8F808080)) 
    \S_OFFSET_S_C[6]_i_1 
       (.I0(S_OFFSET[118]),
        .I1(\S_RAW_VALUE_S_C[15]_i_3_n_0 ),
        .I2(S_CHANNEL_COUNTER[3]),
        .I3(\S_OFFSET_S_C[6]_i_2_n_0 ),
        .I4(S_CHANNEL_COUNTER[2]),
        .I5(\S_OFFSET_S_C[6]_i_3_n_0 ),
        .O(\S_OFFSET_S_C[6]_i_1_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \S_OFFSET_S_C[6]_i_2 
       (.I0(S_OFFSET[102]),
        .I1(S_OFFSET[86]),
        .I2(S_CHANNEL_COUNTER[1]),
        .I3(S_OFFSET[70]),
        .I4(S_CHANNEL_COUNTER[0]),
        .I5(S_OFFSET[54]),
        .O(\S_OFFSET_S_C[6]_i_2_n_0 ));
  LUT5 #(
    .INIT(32'hAFC0A0C0)) 
    \S_OFFSET_S_C[6]_i_3 
       (.I0(S_OFFSET[38]),
        .I1(S_OFFSET[22]),
        .I2(S_CHANNEL_COUNTER[1]),
        .I3(S_CHANNEL_COUNTER[0]),
        .I4(S_OFFSET[6]),
        .O(\S_OFFSET_S_C[6]_i_3_n_0 ));
  LUT6 #(
    .INIT(64'h8F808F8F8F808080)) 
    \S_OFFSET_S_C[7]_i_1 
       (.I0(S_OFFSET[119]),
        .I1(\S_RAW_VALUE_S_C[15]_i_3_n_0 ),
        .I2(S_CHANNEL_COUNTER[3]),
        .I3(\S_OFFSET_S_C[7]_i_2_n_0 ),
        .I4(S_CHANNEL_COUNTER[2]),
        .I5(\S_OFFSET_S_C[7]_i_3_n_0 ),
        .O(\S_OFFSET_S_C[7]_i_1_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \S_OFFSET_S_C[7]_i_2 
       (.I0(S_OFFSET[103]),
        .I1(S_OFFSET[87]),
        .I2(S_CHANNEL_COUNTER[1]),
        .I3(S_OFFSET[71]),
        .I4(S_CHANNEL_COUNTER[0]),
        .I5(S_OFFSET[55]),
        .O(\S_OFFSET_S_C[7]_i_2_n_0 ));
  LUT5 #(
    .INIT(32'hAFC0A0C0)) 
    \S_OFFSET_S_C[7]_i_3 
       (.I0(S_OFFSET[39]),
        .I1(S_OFFSET[23]),
        .I2(S_CHANNEL_COUNTER[1]),
        .I3(S_CHANNEL_COUNTER[0]),
        .I4(S_OFFSET[7]),
        .O(\S_OFFSET_S_C[7]_i_3_n_0 ));
  LUT6 #(
    .INIT(64'h8F808F8F8F808080)) 
    \S_OFFSET_S_C[8]_i_1 
       (.I0(S_OFFSET[120]),
        .I1(\S_RAW_VALUE_S_C[15]_i_3_n_0 ),
        .I2(S_CHANNEL_COUNTER[3]),
        .I3(\S_OFFSET_S_C[8]_i_2_n_0 ),
        .I4(S_CHANNEL_COUNTER[2]),
        .I5(\S_OFFSET_S_C[8]_i_3_n_0 ),
        .O(\S_OFFSET_S_C[8]_i_1_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \S_OFFSET_S_C[8]_i_2 
       (.I0(S_OFFSET[104]),
        .I1(S_OFFSET[88]),
        .I2(S_CHANNEL_COUNTER[1]),
        .I3(S_OFFSET[72]),
        .I4(S_CHANNEL_COUNTER[0]),
        .I5(S_OFFSET[56]),
        .O(\S_OFFSET_S_C[8]_i_2_n_0 ));
  LUT5 #(
    .INIT(32'hAFC0A0C0)) 
    \S_OFFSET_S_C[8]_i_3 
       (.I0(S_OFFSET[40]),
        .I1(S_OFFSET[24]),
        .I2(S_CHANNEL_COUNTER[1]),
        .I3(S_CHANNEL_COUNTER[0]),
        .I4(S_OFFSET[8]),
        .O(\S_OFFSET_S_C[8]_i_3_n_0 ));
  LUT6 #(
    .INIT(64'h8F808F8F8F808080)) 
    \S_OFFSET_S_C[9]_i_1 
       (.I0(S_OFFSET[121]),
        .I1(\S_RAW_VALUE_S_C[15]_i_3_n_0 ),
        .I2(S_CHANNEL_COUNTER[3]),
        .I3(\S_OFFSET_S_C[9]_i_2_n_0 ),
        .I4(S_CHANNEL_COUNTER[2]),
        .I5(\S_OFFSET_S_C[9]_i_3_n_0 ),
        .O(\S_OFFSET_S_C[9]_i_1_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \S_OFFSET_S_C[9]_i_2 
       (.I0(S_OFFSET[105]),
        .I1(S_OFFSET[89]),
        .I2(S_CHANNEL_COUNTER[1]),
        .I3(S_OFFSET[73]),
        .I4(S_CHANNEL_COUNTER[0]),
        .I5(S_OFFSET[57]),
        .O(\S_OFFSET_S_C[9]_i_2_n_0 ));
  LUT5 #(
    .INIT(32'hAFC0A0C0)) 
    \S_OFFSET_S_C[9]_i_3 
       (.I0(S_OFFSET[41]),
        .I1(S_OFFSET[25]),
        .I2(S_CHANNEL_COUNTER[1]),
        .I3(S_CHANNEL_COUNTER[0]),
        .I4(S_OFFSET[9]),
        .O(\S_OFFSET_S_C[9]_i_3_n_0 ));
  FDRE \S_OFFSET_S_C_reg[0] 
       (.C(s00_axi_aclk),
        .CE(S_OFFSET_S_C),
        .D(\S_OFFSET_S_C[0]_i_1_n_0 ),
        .Q(\S_OFFSET_S_C_reg_n_0_[0] ),
        .R(RSTP));
  FDRE \S_OFFSET_S_C_reg[10] 
       (.C(s00_axi_aclk),
        .CE(S_OFFSET_S_C),
        .D(\S_OFFSET_S_C[10]_i_1_n_0 ),
        .Q(\S_OFFSET_S_C_reg_n_0_[10] ),
        .R(RSTP));
  FDRE \S_OFFSET_S_C_reg[11] 
       (.C(s00_axi_aclk),
        .CE(S_OFFSET_S_C),
        .D(\S_OFFSET_S_C[11]_i_1_n_0 ),
        .Q(\S_OFFSET_S_C_reg_n_0_[11] ),
        .R(RSTP));
  FDRE \S_OFFSET_S_C_reg[12] 
       (.C(s00_axi_aclk),
        .CE(S_OFFSET_S_C),
        .D(\S_OFFSET_S_C[12]_i_1_n_0 ),
        .Q(\S_OFFSET_S_C_reg_n_0_[12] ),
        .R(RSTP));
  FDRE \S_OFFSET_S_C_reg[13] 
       (.C(s00_axi_aclk),
        .CE(S_OFFSET_S_C),
        .D(\S_OFFSET_S_C[13]_i_1_n_0 ),
        .Q(\S_OFFSET_S_C_reg_n_0_[13] ),
        .R(RSTP));
  FDRE \S_OFFSET_S_C_reg[14] 
       (.C(s00_axi_aclk),
        .CE(S_OFFSET_S_C),
        .D(\S_OFFSET_S_C[14]_i_1_n_0 ),
        .Q(\S_OFFSET_S_C_reg_n_0_[14] ),
        .R(RSTP));
  FDRE \S_OFFSET_S_C_reg[15] 
       (.C(s00_axi_aclk),
        .CE(S_OFFSET_S_C),
        .D(\S_OFFSET_S_C[15]_i_1_n_0 ),
        .Q(\S_OFFSET_S_C_reg_n_0_[15] ),
        .R(RSTP));
  FDRE \S_OFFSET_S_C_reg[1] 
       (.C(s00_axi_aclk),
        .CE(S_OFFSET_S_C),
        .D(\S_OFFSET_S_C[1]_i_1_n_0 ),
        .Q(\S_OFFSET_S_C_reg_n_0_[1] ),
        .R(RSTP));
  FDRE \S_OFFSET_S_C_reg[2] 
       (.C(s00_axi_aclk),
        .CE(S_OFFSET_S_C),
        .D(\S_OFFSET_S_C[2]_i_1_n_0 ),
        .Q(\S_OFFSET_S_C_reg_n_0_[2] ),
        .R(RSTP));
  FDRE \S_OFFSET_S_C_reg[3] 
       (.C(s00_axi_aclk),
        .CE(S_OFFSET_S_C),
        .D(\S_OFFSET_S_C[3]_i_1_n_0 ),
        .Q(\S_OFFSET_S_C_reg_n_0_[3] ),
        .R(RSTP));
  FDRE \S_OFFSET_S_C_reg[4] 
       (.C(s00_axi_aclk),
        .CE(S_OFFSET_S_C),
        .D(\S_OFFSET_S_C[4]_i_1_n_0 ),
        .Q(\S_OFFSET_S_C_reg_n_0_[4] ),
        .R(RSTP));
  FDRE \S_OFFSET_S_C_reg[5] 
       (.C(s00_axi_aclk),
        .CE(S_OFFSET_S_C),
        .D(\S_OFFSET_S_C[5]_i_1_n_0 ),
        .Q(\S_OFFSET_S_C_reg_n_0_[5] ),
        .R(RSTP));
  FDRE \S_OFFSET_S_C_reg[6] 
       (.C(s00_axi_aclk),
        .CE(S_OFFSET_S_C),
        .D(\S_OFFSET_S_C[6]_i_1_n_0 ),
        .Q(\S_OFFSET_S_C_reg_n_0_[6] ),
        .R(RSTP));
  FDRE \S_OFFSET_S_C_reg[7] 
       (.C(s00_axi_aclk),
        .CE(S_OFFSET_S_C),
        .D(\S_OFFSET_S_C[7]_i_1_n_0 ),
        .Q(\S_OFFSET_S_C_reg_n_0_[7] ),
        .R(RSTP));
  FDRE \S_OFFSET_S_C_reg[8] 
       (.C(s00_axi_aclk),
        .CE(S_OFFSET_S_C),
        .D(\S_OFFSET_S_C[8]_i_1_n_0 ),
        .Q(\S_OFFSET_S_C_reg_n_0_[8] ),
        .R(RSTP));
  FDRE \S_OFFSET_S_C_reg[9] 
       (.C(s00_axi_aclk),
        .CE(S_OFFSET_S_C),
        .D(\S_OFFSET_S_C[9]_i_1_n_0 ),
        .Q(\S_OFFSET_S_C_reg_n_0_[9] ),
        .R(RSTP));
  FDRE \S_OFFSET_reg[0] 
       (.C(s00_axi_aclk),
        .CE(\S_OFFSET_reg[112]_0 [0]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [0]),
        .Q(S_OFFSET[0]),
        .R(RSTP));
  FDRE \S_OFFSET_reg[100] 
       (.C(s00_axi_aclk),
        .CE(\S_OFFSET_reg[112]_0 [6]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [4]),
        .Q(S_OFFSET[100]),
        .R(RSTP));
  FDRE \S_OFFSET_reg[101] 
       (.C(s00_axi_aclk),
        .CE(\S_OFFSET_reg[112]_0 [6]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [5]),
        .Q(S_OFFSET[101]),
        .R(RSTP));
  FDRE \S_OFFSET_reg[102] 
       (.C(s00_axi_aclk),
        .CE(\S_OFFSET_reg[112]_0 [6]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [6]),
        .Q(S_OFFSET[102]),
        .R(RSTP));
  FDRE \S_OFFSET_reg[103] 
       (.C(s00_axi_aclk),
        .CE(\S_OFFSET_reg[112]_0 [6]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [7]),
        .Q(S_OFFSET[103]),
        .R(RSTP));
  FDRE \S_OFFSET_reg[104] 
       (.C(s00_axi_aclk),
        .CE(\S_OFFSET_reg[112]_0 [6]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [8]),
        .Q(S_OFFSET[104]),
        .R(RSTP));
  FDRE \S_OFFSET_reg[105] 
       (.C(s00_axi_aclk),
        .CE(\S_OFFSET_reg[112]_0 [6]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [9]),
        .Q(S_OFFSET[105]),
        .R(RSTP));
  FDRE \S_OFFSET_reg[106] 
       (.C(s00_axi_aclk),
        .CE(\S_OFFSET_reg[112]_0 [6]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [10]),
        .Q(S_OFFSET[106]),
        .R(RSTP));
  FDRE \S_OFFSET_reg[107] 
       (.C(s00_axi_aclk),
        .CE(\S_OFFSET_reg[112]_0 [6]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [11]),
        .Q(S_OFFSET[107]),
        .R(RSTP));
  FDRE \S_OFFSET_reg[108] 
       (.C(s00_axi_aclk),
        .CE(\S_OFFSET_reg[112]_0 [6]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [12]),
        .Q(S_OFFSET[108]),
        .R(RSTP));
  FDRE \S_OFFSET_reg[109] 
       (.C(s00_axi_aclk),
        .CE(\S_OFFSET_reg[112]_0 [6]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [13]),
        .Q(S_OFFSET[109]),
        .R(RSTP));
  FDRE \S_OFFSET_reg[10] 
       (.C(s00_axi_aclk),
        .CE(\S_OFFSET_reg[112]_0 [0]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [10]),
        .Q(S_OFFSET[10]),
        .R(RSTP));
  FDRE \S_OFFSET_reg[110] 
       (.C(s00_axi_aclk),
        .CE(\S_OFFSET_reg[112]_0 [6]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [14]),
        .Q(S_OFFSET[110]),
        .R(RSTP));
  FDRE \S_OFFSET_reg[111] 
       (.C(s00_axi_aclk),
        .CE(\S_OFFSET_reg[112]_0 [6]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [15]),
        .Q(S_OFFSET[111]),
        .R(RSTP));
  FDRE \S_OFFSET_reg[112] 
       (.C(s00_axi_aclk),
        .CE(\S_OFFSET_reg[112]_0 [7]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [0]),
        .Q(S_OFFSET[112]),
        .R(RSTP));
  FDRE \S_OFFSET_reg[113] 
       (.C(s00_axi_aclk),
        .CE(\S_OFFSET_reg[112]_0 [7]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [1]),
        .Q(S_OFFSET[113]),
        .R(RSTP));
  FDRE \S_OFFSET_reg[114] 
       (.C(s00_axi_aclk),
        .CE(\S_OFFSET_reg[112]_0 [7]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [2]),
        .Q(S_OFFSET[114]),
        .R(RSTP));
  FDRE \S_OFFSET_reg[115] 
       (.C(s00_axi_aclk),
        .CE(\S_OFFSET_reg[112]_0 [7]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [3]),
        .Q(S_OFFSET[115]),
        .R(RSTP));
  FDRE \S_OFFSET_reg[116] 
       (.C(s00_axi_aclk),
        .CE(\S_OFFSET_reg[112]_0 [7]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [4]),
        .Q(S_OFFSET[116]),
        .R(RSTP));
  FDRE \S_OFFSET_reg[117] 
       (.C(s00_axi_aclk),
        .CE(\S_OFFSET_reg[112]_0 [7]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [5]),
        .Q(S_OFFSET[117]),
        .R(RSTP));
  FDRE \S_OFFSET_reg[118] 
       (.C(s00_axi_aclk),
        .CE(\S_OFFSET_reg[112]_0 [7]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [6]),
        .Q(S_OFFSET[118]),
        .R(RSTP));
  FDRE \S_OFFSET_reg[119] 
       (.C(s00_axi_aclk),
        .CE(\S_OFFSET_reg[112]_0 [7]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [7]),
        .Q(S_OFFSET[119]),
        .R(RSTP));
  FDRE \S_OFFSET_reg[11] 
       (.C(s00_axi_aclk),
        .CE(\S_OFFSET_reg[112]_0 [0]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [11]),
        .Q(S_OFFSET[11]),
        .R(RSTP));
  FDRE \S_OFFSET_reg[120] 
       (.C(s00_axi_aclk),
        .CE(\S_OFFSET_reg[112]_0 [7]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [8]),
        .Q(S_OFFSET[120]),
        .R(RSTP));
  FDRE \S_OFFSET_reg[121] 
       (.C(s00_axi_aclk),
        .CE(\S_OFFSET_reg[112]_0 [7]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [9]),
        .Q(S_OFFSET[121]),
        .R(RSTP));
  FDRE \S_OFFSET_reg[122] 
       (.C(s00_axi_aclk),
        .CE(\S_OFFSET_reg[112]_0 [7]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [10]),
        .Q(S_OFFSET[122]),
        .R(RSTP));
  FDRE \S_OFFSET_reg[123] 
       (.C(s00_axi_aclk),
        .CE(\S_OFFSET_reg[112]_0 [7]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [11]),
        .Q(S_OFFSET[123]),
        .R(RSTP));
  FDRE \S_OFFSET_reg[124] 
       (.C(s00_axi_aclk),
        .CE(\S_OFFSET_reg[112]_0 [7]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [12]),
        .Q(S_OFFSET[124]),
        .R(RSTP));
  FDRE \S_OFFSET_reg[125] 
       (.C(s00_axi_aclk),
        .CE(\S_OFFSET_reg[112]_0 [7]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [13]),
        .Q(S_OFFSET[125]),
        .R(RSTP));
  FDRE \S_OFFSET_reg[126] 
       (.C(s00_axi_aclk),
        .CE(\S_OFFSET_reg[112]_0 [7]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [14]),
        .Q(S_OFFSET[126]),
        .R(RSTP));
  FDRE \S_OFFSET_reg[127] 
       (.C(s00_axi_aclk),
        .CE(\S_OFFSET_reg[112]_0 [7]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [15]),
        .Q(S_OFFSET[127]),
        .R(RSTP));
  FDRE \S_OFFSET_reg[12] 
       (.C(s00_axi_aclk),
        .CE(\S_OFFSET_reg[112]_0 [0]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [12]),
        .Q(S_OFFSET[12]),
        .R(RSTP));
  FDRE \S_OFFSET_reg[13] 
       (.C(s00_axi_aclk),
        .CE(\S_OFFSET_reg[112]_0 [0]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [13]),
        .Q(S_OFFSET[13]),
        .R(RSTP));
  FDRE \S_OFFSET_reg[14] 
       (.C(s00_axi_aclk),
        .CE(\S_OFFSET_reg[112]_0 [0]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [14]),
        .Q(S_OFFSET[14]),
        .R(RSTP));
  FDRE \S_OFFSET_reg[15] 
       (.C(s00_axi_aclk),
        .CE(\S_OFFSET_reg[112]_0 [0]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [15]),
        .Q(S_OFFSET[15]),
        .R(RSTP));
  FDRE \S_OFFSET_reg[16] 
       (.C(s00_axi_aclk),
        .CE(\S_OFFSET_reg[112]_0 [1]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [0]),
        .Q(S_OFFSET[16]),
        .R(RSTP));
  FDRE \S_OFFSET_reg[17] 
       (.C(s00_axi_aclk),
        .CE(\S_OFFSET_reg[112]_0 [1]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [1]),
        .Q(S_OFFSET[17]),
        .R(RSTP));
  FDRE \S_OFFSET_reg[18] 
       (.C(s00_axi_aclk),
        .CE(\S_OFFSET_reg[112]_0 [1]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [2]),
        .Q(S_OFFSET[18]),
        .R(RSTP));
  FDRE \S_OFFSET_reg[19] 
       (.C(s00_axi_aclk),
        .CE(\S_OFFSET_reg[112]_0 [1]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [3]),
        .Q(S_OFFSET[19]),
        .R(RSTP));
  FDRE \S_OFFSET_reg[1] 
       (.C(s00_axi_aclk),
        .CE(\S_OFFSET_reg[112]_0 [0]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [1]),
        .Q(S_OFFSET[1]),
        .R(RSTP));
  FDRE \S_OFFSET_reg[20] 
       (.C(s00_axi_aclk),
        .CE(\S_OFFSET_reg[112]_0 [1]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [4]),
        .Q(S_OFFSET[20]),
        .R(RSTP));
  FDRE \S_OFFSET_reg[21] 
       (.C(s00_axi_aclk),
        .CE(\S_OFFSET_reg[112]_0 [1]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [5]),
        .Q(S_OFFSET[21]),
        .R(RSTP));
  FDRE \S_OFFSET_reg[22] 
       (.C(s00_axi_aclk),
        .CE(\S_OFFSET_reg[112]_0 [1]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [6]),
        .Q(S_OFFSET[22]),
        .R(RSTP));
  FDRE \S_OFFSET_reg[23] 
       (.C(s00_axi_aclk),
        .CE(\S_OFFSET_reg[112]_0 [1]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [7]),
        .Q(S_OFFSET[23]),
        .R(RSTP));
  FDRE \S_OFFSET_reg[24] 
       (.C(s00_axi_aclk),
        .CE(\S_OFFSET_reg[112]_0 [1]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [8]),
        .Q(S_OFFSET[24]),
        .R(RSTP));
  FDRE \S_OFFSET_reg[25] 
       (.C(s00_axi_aclk),
        .CE(\S_OFFSET_reg[112]_0 [1]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [9]),
        .Q(S_OFFSET[25]),
        .R(RSTP));
  FDRE \S_OFFSET_reg[26] 
       (.C(s00_axi_aclk),
        .CE(\S_OFFSET_reg[112]_0 [1]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [10]),
        .Q(S_OFFSET[26]),
        .R(RSTP));
  FDRE \S_OFFSET_reg[27] 
       (.C(s00_axi_aclk),
        .CE(\S_OFFSET_reg[112]_0 [1]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [11]),
        .Q(S_OFFSET[27]),
        .R(RSTP));
  FDRE \S_OFFSET_reg[28] 
       (.C(s00_axi_aclk),
        .CE(\S_OFFSET_reg[112]_0 [1]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [12]),
        .Q(S_OFFSET[28]),
        .R(RSTP));
  FDRE \S_OFFSET_reg[29] 
       (.C(s00_axi_aclk),
        .CE(\S_OFFSET_reg[112]_0 [1]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [13]),
        .Q(S_OFFSET[29]),
        .R(RSTP));
  FDRE \S_OFFSET_reg[2] 
       (.C(s00_axi_aclk),
        .CE(\S_OFFSET_reg[112]_0 [0]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [2]),
        .Q(S_OFFSET[2]),
        .R(RSTP));
  FDRE \S_OFFSET_reg[30] 
       (.C(s00_axi_aclk),
        .CE(\S_OFFSET_reg[112]_0 [1]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [14]),
        .Q(S_OFFSET[30]),
        .R(RSTP));
  FDRE \S_OFFSET_reg[31] 
       (.C(s00_axi_aclk),
        .CE(\S_OFFSET_reg[112]_0 [1]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [15]),
        .Q(S_OFFSET[31]),
        .R(RSTP));
  FDRE \S_OFFSET_reg[32] 
       (.C(s00_axi_aclk),
        .CE(\S_OFFSET_reg[112]_0 [2]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [0]),
        .Q(S_OFFSET[32]),
        .R(RSTP));
  FDRE \S_OFFSET_reg[33] 
       (.C(s00_axi_aclk),
        .CE(\S_OFFSET_reg[112]_0 [2]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [1]),
        .Q(S_OFFSET[33]),
        .R(RSTP));
  FDRE \S_OFFSET_reg[34] 
       (.C(s00_axi_aclk),
        .CE(\S_OFFSET_reg[112]_0 [2]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [2]),
        .Q(S_OFFSET[34]),
        .R(RSTP));
  FDRE \S_OFFSET_reg[35] 
       (.C(s00_axi_aclk),
        .CE(\S_OFFSET_reg[112]_0 [2]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [3]),
        .Q(S_OFFSET[35]),
        .R(RSTP));
  FDRE \S_OFFSET_reg[36] 
       (.C(s00_axi_aclk),
        .CE(\S_OFFSET_reg[112]_0 [2]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [4]),
        .Q(S_OFFSET[36]),
        .R(RSTP));
  FDRE \S_OFFSET_reg[37] 
       (.C(s00_axi_aclk),
        .CE(\S_OFFSET_reg[112]_0 [2]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [5]),
        .Q(S_OFFSET[37]),
        .R(RSTP));
  FDRE \S_OFFSET_reg[38] 
       (.C(s00_axi_aclk),
        .CE(\S_OFFSET_reg[112]_0 [2]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [6]),
        .Q(S_OFFSET[38]),
        .R(RSTP));
  FDRE \S_OFFSET_reg[39] 
       (.C(s00_axi_aclk),
        .CE(\S_OFFSET_reg[112]_0 [2]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [7]),
        .Q(S_OFFSET[39]),
        .R(RSTP));
  FDRE \S_OFFSET_reg[3] 
       (.C(s00_axi_aclk),
        .CE(\S_OFFSET_reg[112]_0 [0]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [3]),
        .Q(S_OFFSET[3]),
        .R(RSTP));
  FDRE \S_OFFSET_reg[40] 
       (.C(s00_axi_aclk),
        .CE(\S_OFFSET_reg[112]_0 [2]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [8]),
        .Q(S_OFFSET[40]),
        .R(RSTP));
  FDRE \S_OFFSET_reg[41] 
       (.C(s00_axi_aclk),
        .CE(\S_OFFSET_reg[112]_0 [2]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [9]),
        .Q(S_OFFSET[41]),
        .R(RSTP));
  FDRE \S_OFFSET_reg[42] 
       (.C(s00_axi_aclk),
        .CE(\S_OFFSET_reg[112]_0 [2]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [10]),
        .Q(S_OFFSET[42]),
        .R(RSTP));
  FDRE \S_OFFSET_reg[43] 
       (.C(s00_axi_aclk),
        .CE(\S_OFFSET_reg[112]_0 [2]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [11]),
        .Q(S_OFFSET[43]),
        .R(RSTP));
  FDRE \S_OFFSET_reg[44] 
       (.C(s00_axi_aclk),
        .CE(\S_OFFSET_reg[112]_0 [2]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [12]),
        .Q(S_OFFSET[44]),
        .R(RSTP));
  FDRE \S_OFFSET_reg[45] 
       (.C(s00_axi_aclk),
        .CE(\S_OFFSET_reg[112]_0 [2]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [13]),
        .Q(S_OFFSET[45]),
        .R(RSTP));
  FDRE \S_OFFSET_reg[46] 
       (.C(s00_axi_aclk),
        .CE(\S_OFFSET_reg[112]_0 [2]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [14]),
        .Q(S_OFFSET[46]),
        .R(RSTP));
  FDRE \S_OFFSET_reg[47] 
       (.C(s00_axi_aclk),
        .CE(\S_OFFSET_reg[112]_0 [2]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [15]),
        .Q(S_OFFSET[47]),
        .R(RSTP));
  FDRE \S_OFFSET_reg[48] 
       (.C(s00_axi_aclk),
        .CE(\S_OFFSET_reg[112]_0 [3]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [0]),
        .Q(S_OFFSET[48]),
        .R(RSTP));
  FDRE \S_OFFSET_reg[49] 
       (.C(s00_axi_aclk),
        .CE(\S_OFFSET_reg[112]_0 [3]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [1]),
        .Q(S_OFFSET[49]),
        .R(RSTP));
  FDRE \S_OFFSET_reg[4] 
       (.C(s00_axi_aclk),
        .CE(\S_OFFSET_reg[112]_0 [0]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [4]),
        .Q(S_OFFSET[4]),
        .R(RSTP));
  FDRE \S_OFFSET_reg[50] 
       (.C(s00_axi_aclk),
        .CE(\S_OFFSET_reg[112]_0 [3]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [2]),
        .Q(S_OFFSET[50]),
        .R(RSTP));
  FDRE \S_OFFSET_reg[51] 
       (.C(s00_axi_aclk),
        .CE(\S_OFFSET_reg[112]_0 [3]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [3]),
        .Q(S_OFFSET[51]),
        .R(RSTP));
  FDRE \S_OFFSET_reg[52] 
       (.C(s00_axi_aclk),
        .CE(\S_OFFSET_reg[112]_0 [3]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [4]),
        .Q(S_OFFSET[52]),
        .R(RSTP));
  FDRE \S_OFFSET_reg[53] 
       (.C(s00_axi_aclk),
        .CE(\S_OFFSET_reg[112]_0 [3]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [5]),
        .Q(S_OFFSET[53]),
        .R(RSTP));
  FDRE \S_OFFSET_reg[54] 
       (.C(s00_axi_aclk),
        .CE(\S_OFFSET_reg[112]_0 [3]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [6]),
        .Q(S_OFFSET[54]),
        .R(RSTP));
  FDRE \S_OFFSET_reg[55] 
       (.C(s00_axi_aclk),
        .CE(\S_OFFSET_reg[112]_0 [3]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [7]),
        .Q(S_OFFSET[55]),
        .R(RSTP));
  FDRE \S_OFFSET_reg[56] 
       (.C(s00_axi_aclk),
        .CE(\S_OFFSET_reg[112]_0 [3]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [8]),
        .Q(S_OFFSET[56]),
        .R(RSTP));
  FDRE \S_OFFSET_reg[57] 
       (.C(s00_axi_aclk),
        .CE(\S_OFFSET_reg[112]_0 [3]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [9]),
        .Q(S_OFFSET[57]),
        .R(RSTP));
  FDRE \S_OFFSET_reg[58] 
       (.C(s00_axi_aclk),
        .CE(\S_OFFSET_reg[112]_0 [3]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [10]),
        .Q(S_OFFSET[58]),
        .R(RSTP));
  FDRE \S_OFFSET_reg[59] 
       (.C(s00_axi_aclk),
        .CE(\S_OFFSET_reg[112]_0 [3]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [11]),
        .Q(S_OFFSET[59]),
        .R(RSTP));
  FDRE \S_OFFSET_reg[5] 
       (.C(s00_axi_aclk),
        .CE(\S_OFFSET_reg[112]_0 [0]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [5]),
        .Q(S_OFFSET[5]),
        .R(RSTP));
  FDRE \S_OFFSET_reg[60] 
       (.C(s00_axi_aclk),
        .CE(\S_OFFSET_reg[112]_0 [3]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [12]),
        .Q(S_OFFSET[60]),
        .R(RSTP));
  FDRE \S_OFFSET_reg[61] 
       (.C(s00_axi_aclk),
        .CE(\S_OFFSET_reg[112]_0 [3]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [13]),
        .Q(S_OFFSET[61]),
        .R(RSTP));
  FDRE \S_OFFSET_reg[62] 
       (.C(s00_axi_aclk),
        .CE(\S_OFFSET_reg[112]_0 [3]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [14]),
        .Q(S_OFFSET[62]),
        .R(RSTP));
  FDRE \S_OFFSET_reg[63] 
       (.C(s00_axi_aclk),
        .CE(\S_OFFSET_reg[112]_0 [3]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [15]),
        .Q(S_OFFSET[63]),
        .R(RSTP));
  FDRE \S_OFFSET_reg[64] 
       (.C(s00_axi_aclk),
        .CE(\S_OFFSET_reg[112]_0 [4]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [0]),
        .Q(S_OFFSET[64]),
        .R(RSTP));
  FDRE \S_OFFSET_reg[65] 
       (.C(s00_axi_aclk),
        .CE(\S_OFFSET_reg[112]_0 [4]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [1]),
        .Q(S_OFFSET[65]),
        .R(RSTP));
  FDRE \S_OFFSET_reg[66] 
       (.C(s00_axi_aclk),
        .CE(\S_OFFSET_reg[112]_0 [4]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [2]),
        .Q(S_OFFSET[66]),
        .R(RSTP));
  FDRE \S_OFFSET_reg[67] 
       (.C(s00_axi_aclk),
        .CE(\S_OFFSET_reg[112]_0 [4]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [3]),
        .Q(S_OFFSET[67]),
        .R(RSTP));
  FDRE \S_OFFSET_reg[68] 
       (.C(s00_axi_aclk),
        .CE(\S_OFFSET_reg[112]_0 [4]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [4]),
        .Q(S_OFFSET[68]),
        .R(RSTP));
  FDRE \S_OFFSET_reg[69] 
       (.C(s00_axi_aclk),
        .CE(\S_OFFSET_reg[112]_0 [4]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [5]),
        .Q(S_OFFSET[69]),
        .R(RSTP));
  FDRE \S_OFFSET_reg[6] 
       (.C(s00_axi_aclk),
        .CE(\S_OFFSET_reg[112]_0 [0]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [6]),
        .Q(S_OFFSET[6]),
        .R(RSTP));
  FDRE \S_OFFSET_reg[70] 
       (.C(s00_axi_aclk),
        .CE(\S_OFFSET_reg[112]_0 [4]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [6]),
        .Q(S_OFFSET[70]),
        .R(RSTP));
  FDRE \S_OFFSET_reg[71] 
       (.C(s00_axi_aclk),
        .CE(\S_OFFSET_reg[112]_0 [4]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [7]),
        .Q(S_OFFSET[71]),
        .R(RSTP));
  FDRE \S_OFFSET_reg[72] 
       (.C(s00_axi_aclk),
        .CE(\S_OFFSET_reg[112]_0 [4]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [8]),
        .Q(S_OFFSET[72]),
        .R(RSTP));
  FDRE \S_OFFSET_reg[73] 
       (.C(s00_axi_aclk),
        .CE(\S_OFFSET_reg[112]_0 [4]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [9]),
        .Q(S_OFFSET[73]),
        .R(RSTP));
  FDRE \S_OFFSET_reg[74] 
       (.C(s00_axi_aclk),
        .CE(\S_OFFSET_reg[112]_0 [4]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [10]),
        .Q(S_OFFSET[74]),
        .R(RSTP));
  FDRE \S_OFFSET_reg[75] 
       (.C(s00_axi_aclk),
        .CE(\S_OFFSET_reg[112]_0 [4]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [11]),
        .Q(S_OFFSET[75]),
        .R(RSTP));
  FDRE \S_OFFSET_reg[76] 
       (.C(s00_axi_aclk),
        .CE(\S_OFFSET_reg[112]_0 [4]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [12]),
        .Q(S_OFFSET[76]),
        .R(RSTP));
  FDRE \S_OFFSET_reg[77] 
       (.C(s00_axi_aclk),
        .CE(\S_OFFSET_reg[112]_0 [4]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [13]),
        .Q(S_OFFSET[77]),
        .R(RSTP));
  FDRE \S_OFFSET_reg[78] 
       (.C(s00_axi_aclk),
        .CE(\S_OFFSET_reg[112]_0 [4]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [14]),
        .Q(S_OFFSET[78]),
        .R(RSTP));
  FDRE \S_OFFSET_reg[79] 
       (.C(s00_axi_aclk),
        .CE(\S_OFFSET_reg[112]_0 [4]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [15]),
        .Q(S_OFFSET[79]),
        .R(RSTP));
  FDRE \S_OFFSET_reg[7] 
       (.C(s00_axi_aclk),
        .CE(\S_OFFSET_reg[112]_0 [0]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [7]),
        .Q(S_OFFSET[7]),
        .R(RSTP));
  FDRE \S_OFFSET_reg[80] 
       (.C(s00_axi_aclk),
        .CE(\S_OFFSET_reg[112]_0 [5]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [0]),
        .Q(S_OFFSET[80]),
        .R(RSTP));
  FDRE \S_OFFSET_reg[81] 
       (.C(s00_axi_aclk),
        .CE(\S_OFFSET_reg[112]_0 [5]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [1]),
        .Q(S_OFFSET[81]),
        .R(RSTP));
  FDRE \S_OFFSET_reg[82] 
       (.C(s00_axi_aclk),
        .CE(\S_OFFSET_reg[112]_0 [5]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [2]),
        .Q(S_OFFSET[82]),
        .R(RSTP));
  FDRE \S_OFFSET_reg[83] 
       (.C(s00_axi_aclk),
        .CE(\S_OFFSET_reg[112]_0 [5]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [3]),
        .Q(S_OFFSET[83]),
        .R(RSTP));
  FDRE \S_OFFSET_reg[84] 
       (.C(s00_axi_aclk),
        .CE(\S_OFFSET_reg[112]_0 [5]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [4]),
        .Q(S_OFFSET[84]),
        .R(RSTP));
  FDRE \S_OFFSET_reg[85] 
       (.C(s00_axi_aclk),
        .CE(\S_OFFSET_reg[112]_0 [5]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [5]),
        .Q(S_OFFSET[85]),
        .R(RSTP));
  FDRE \S_OFFSET_reg[86] 
       (.C(s00_axi_aclk),
        .CE(\S_OFFSET_reg[112]_0 [5]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [6]),
        .Q(S_OFFSET[86]),
        .R(RSTP));
  FDRE \S_OFFSET_reg[87] 
       (.C(s00_axi_aclk),
        .CE(\S_OFFSET_reg[112]_0 [5]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [7]),
        .Q(S_OFFSET[87]),
        .R(RSTP));
  FDRE \S_OFFSET_reg[88] 
       (.C(s00_axi_aclk),
        .CE(\S_OFFSET_reg[112]_0 [5]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [8]),
        .Q(S_OFFSET[88]),
        .R(RSTP));
  FDRE \S_OFFSET_reg[89] 
       (.C(s00_axi_aclk),
        .CE(\S_OFFSET_reg[112]_0 [5]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [9]),
        .Q(S_OFFSET[89]),
        .R(RSTP));
  FDRE \S_OFFSET_reg[8] 
       (.C(s00_axi_aclk),
        .CE(\S_OFFSET_reg[112]_0 [0]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [8]),
        .Q(S_OFFSET[8]),
        .R(RSTP));
  FDRE \S_OFFSET_reg[90] 
       (.C(s00_axi_aclk),
        .CE(\S_OFFSET_reg[112]_0 [5]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [10]),
        .Q(S_OFFSET[90]),
        .R(RSTP));
  FDRE \S_OFFSET_reg[91] 
       (.C(s00_axi_aclk),
        .CE(\S_OFFSET_reg[112]_0 [5]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [11]),
        .Q(S_OFFSET[91]),
        .R(RSTP));
  FDRE \S_OFFSET_reg[92] 
       (.C(s00_axi_aclk),
        .CE(\S_OFFSET_reg[112]_0 [5]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [12]),
        .Q(S_OFFSET[92]),
        .R(RSTP));
  FDRE \S_OFFSET_reg[93] 
       (.C(s00_axi_aclk),
        .CE(\S_OFFSET_reg[112]_0 [5]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [13]),
        .Q(S_OFFSET[93]),
        .R(RSTP));
  FDRE \S_OFFSET_reg[94] 
       (.C(s00_axi_aclk),
        .CE(\S_OFFSET_reg[112]_0 [5]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [14]),
        .Q(S_OFFSET[94]),
        .R(RSTP));
  FDRE \S_OFFSET_reg[95] 
       (.C(s00_axi_aclk),
        .CE(\S_OFFSET_reg[112]_0 [5]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [15]),
        .Q(S_OFFSET[95]),
        .R(RSTP));
  FDRE \S_OFFSET_reg[96] 
       (.C(s00_axi_aclk),
        .CE(\S_OFFSET_reg[112]_0 [6]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [0]),
        .Q(S_OFFSET[96]),
        .R(RSTP));
  FDRE \S_OFFSET_reg[97] 
       (.C(s00_axi_aclk),
        .CE(\S_OFFSET_reg[112]_0 [6]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [1]),
        .Q(S_OFFSET[97]),
        .R(RSTP));
  FDRE \S_OFFSET_reg[98] 
       (.C(s00_axi_aclk),
        .CE(\S_OFFSET_reg[112]_0 [6]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [2]),
        .Q(S_OFFSET[98]),
        .R(RSTP));
  FDRE \S_OFFSET_reg[99] 
       (.C(s00_axi_aclk),
        .CE(\S_OFFSET_reg[112]_0 [6]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [3]),
        .Q(S_OFFSET[99]),
        .R(RSTP));
  FDRE \S_OFFSET_reg[9] 
       (.C(s00_axi_aclk),
        .CE(\S_OFFSET_reg[112]_0 [0]),
        .D(\S_SAMPLE_TIME_reg[30]_1 [9]),
        .Q(S_OFFSET[9]),
        .R(RSTP));
  LUT6 #(
    .INIT(64'h0000000055555554)) 
    \S_RAW_VALUE_S_C[15]_i_1 
       (.I0(\S_ENABLE_reg[0] ),
        .I1(S_CHANNEL_COUNTER[2]),
        .I2(S_CHANNEL_COUNTER[0]),
        .I3(S_CHANNEL_COUNTER[1]),
        .I4(S_CHANNEL_COUNTER[3]),
        .I5(\S_ENABLE_reg[0]_0 ),
        .O(S_OFFSET_S_C));
  (* SOFT_HLUTNM = "soft_lutpair108" *) 
  LUT3 #(
    .INIT(8'h01)) 
    \S_RAW_VALUE_S_C[15]_i_3 
       (.I0(S_CHANNEL_COUNTER[1]),
        .I1(S_CHANNEL_COUNTER[0]),
        .I2(S_CHANNEL_COUNTER[2]),
        .O(\S_RAW_VALUE_S_C[15]_i_3_n_0 ));
  FDRE \S_RAW_VALUE_S_C_reg[0] 
       (.C(s00_axi_aclk),
        .CE(S_OFFSET_S_C),
        .D(spi_n_20),
        .Q(S_RAW_VALUE_S_C[0]),
        .R(RSTP));
  FDRE \S_RAW_VALUE_S_C_reg[10] 
       (.C(s00_axi_aclk),
        .CE(S_OFFSET_S_C),
        .D(spi_n_10),
        .Q(S_RAW_VALUE_S_C[10]),
        .R(RSTP));
  FDRE \S_RAW_VALUE_S_C_reg[11] 
       (.C(s00_axi_aclk),
        .CE(S_OFFSET_S_C),
        .D(spi_n_9),
        .Q(S_RAW_VALUE_S_C[11]),
        .R(RSTP));
  FDRE \S_RAW_VALUE_S_C_reg[12] 
       (.C(s00_axi_aclk),
        .CE(S_OFFSET_S_C),
        .D(spi_n_8),
        .Q(S_RAW_VALUE_S_C[12]),
        .R(RSTP));
  FDRE \S_RAW_VALUE_S_C_reg[13] 
       (.C(s00_axi_aclk),
        .CE(S_OFFSET_S_C),
        .D(spi_n_7),
        .Q(S_RAW_VALUE_S_C[13]),
        .R(RSTP));
  FDRE \S_RAW_VALUE_S_C_reg[14] 
       (.C(s00_axi_aclk),
        .CE(S_OFFSET_S_C),
        .D(spi_n_6),
        .Q(S_RAW_VALUE_S_C[14]),
        .R(RSTP));
  FDRE \S_RAW_VALUE_S_C_reg[15] 
       (.C(s00_axi_aclk),
        .CE(S_OFFSET_S_C),
        .D(spi_n_5),
        .Q(S_RAW_VALUE_S_C[15]),
        .R(RSTP));
  FDRE \S_RAW_VALUE_S_C_reg[1] 
       (.C(s00_axi_aclk),
        .CE(S_OFFSET_S_C),
        .D(spi_n_19),
        .Q(S_RAW_VALUE_S_C[1]),
        .R(RSTP));
  FDRE \S_RAW_VALUE_S_C_reg[2] 
       (.C(s00_axi_aclk),
        .CE(S_OFFSET_S_C),
        .D(spi_n_18),
        .Q(S_RAW_VALUE_S_C[2]),
        .R(RSTP));
  FDRE \S_RAW_VALUE_S_C_reg[3] 
       (.C(s00_axi_aclk),
        .CE(S_OFFSET_S_C),
        .D(spi_n_17),
        .Q(S_RAW_VALUE_S_C[3]),
        .R(RSTP));
  FDRE \S_RAW_VALUE_S_C_reg[4] 
       (.C(s00_axi_aclk),
        .CE(S_OFFSET_S_C),
        .D(spi_n_16),
        .Q(S_RAW_VALUE_S_C[4]),
        .R(RSTP));
  FDRE \S_RAW_VALUE_S_C_reg[5] 
       (.C(s00_axi_aclk),
        .CE(S_OFFSET_S_C),
        .D(spi_n_15),
        .Q(S_RAW_VALUE_S_C[5]),
        .R(RSTP));
  FDRE \S_RAW_VALUE_S_C_reg[6] 
       (.C(s00_axi_aclk),
        .CE(S_OFFSET_S_C),
        .D(spi_n_14),
        .Q(S_RAW_VALUE_S_C[6]),
        .R(RSTP));
  FDRE \S_RAW_VALUE_S_C_reg[7] 
       (.C(s00_axi_aclk),
        .CE(S_OFFSET_S_C),
        .D(spi_n_13),
        .Q(S_RAW_VALUE_S_C[7]),
        .R(RSTP));
  FDRE \S_RAW_VALUE_S_C_reg[8] 
       (.C(s00_axi_aclk),
        .CE(S_OFFSET_S_C),
        .D(spi_n_12),
        .Q(S_RAW_VALUE_S_C[8]),
        .R(RSTP));
  FDRE \S_RAW_VALUE_S_C_reg[9] 
       (.C(s00_axi_aclk),
        .CE(S_OFFSET_S_C),
        .D(spi_n_11),
        .Q(S_RAW_VALUE_S_C[9]),
        .R(RSTP));
  (* SOFT_HLUTNM = "soft_lutpair90" *) 
  LUT2 #(
    .INIT(4'hB)) 
    \S_RESULT_COUNTER[0]_i_1 
       (.I0(\S_ENABLE_reg[0]_0 ),
        .I1(S_RESULT_COUNTER[0]),
        .O(\S_RESULT_COUNTER[0]_i_1_n_0 ));
  LUT2 #(
    .INIT(4'hB)) 
    \S_RESULT_COUNTER[0]_rep_i_1 
       (.I0(\S_ENABLE_reg[0]_0 ),
        .I1(S_RESULT_COUNTER[0]),
        .O(\S_RESULT_COUNTER[0]_rep_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair90" *) 
  LUT3 #(
    .INIT(8'hEB)) 
    \S_RESULT_COUNTER[1]_i_1 
       (.I0(\S_ENABLE_reg[0]_0 ),
        .I1(S_RESULT_COUNTER[1]),
        .I2(\S_RESULT_COUNTER_reg[0]_rep_n_0 ),
        .O(\S_RESULT_COUNTER[1]_i_1_n_0 ));
  LUT3 #(
    .INIT(8'hEB)) 
    \S_RESULT_COUNTER[1]_rep_i_1 
       (.I0(\S_ENABLE_reg[0]_0 ),
        .I1(S_RESULT_COUNTER[1]),
        .I2(\S_RESULT_COUNTER_reg[0]_rep_n_0 ),
        .O(\S_RESULT_COUNTER[1]_rep_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair83" *) 
  LUT4 #(
    .INIT(16'h00E1)) 
    \S_RESULT_COUNTER[2]_i_1 
       (.I0(\S_RESULT_COUNTER_reg[0]_rep_n_0 ),
        .I1(S_RESULT_COUNTER[1]),
        .I2(S_RESULT_COUNTER[2]),
        .I3(\S_ENABLE_reg[0]_0 ),
        .O(B[2]));
  LUT6 #(
    .INIT(64'hAAAAAAAAAAAAAAA8)) 
    \S_RESULT_COUNTER[3]_i_1 
       (.I0(\S_RESULT_COUNTER[3]_i_3_n_0 ),
        .I1(\S_ENABLE_reg[0]_0 ),
        .I2(S_RESULT_COUNTER[2]),
        .I3(S_RESULT_COUNTER[3]),
        .I4(S_RESULT_COUNTER[1]),
        .I5(\S_RESULT_COUNTER_reg[0]_rep_n_0 ),
        .O(CEB2));
  (* SOFT_HLUTNM = "soft_lutpair83" *) 
  LUT5 #(
    .INIT(32'hFFFEAAAB)) 
    \S_RESULT_COUNTER[3]_i_2 
       (.I0(\S_ENABLE_reg[0]_0 ),
        .I1(S_RESULT_COUNTER[2]),
        .I2(S_RESULT_COUNTER[1]),
        .I3(\S_RESULT_COUNTER_reg[0]_rep_n_0 ),
        .I4(S_RESULT_COUNTER[3]),
        .O(B[3]));
  (* SOFT_HLUTNM = "soft_lutpair87" *) 
  LUT4 #(
    .INIT(16'h0455)) 
    \S_RESULT_COUNTER[3]_i_3 
       (.I0(\S_ENABLE_reg[0] ),
        .I1(Q[0]),
        .I2(Q[1]),
        .I3(\S_ENABLE_reg[0]_0 ),
        .O(\S_RESULT_COUNTER[3]_i_3_n_0 ));
  (* ORIG_CELL_NAME = "S_RESULT_COUNTER_reg[0]" *) 
  FDRE \S_RESULT_COUNTER_reg[0] 
       (.C(s00_axi_aclk),
        .CE(CEB2),
        .D(\S_RESULT_COUNTER[0]_i_1_n_0 ),
        .Q(S_RESULT_COUNTER[0]),
        .R(RSTP));
  (* ORIG_CELL_NAME = "S_RESULT_COUNTER_reg[0]" *) 
  FDRE \S_RESULT_COUNTER_reg[0]_rep 
       (.C(s00_axi_aclk),
        .CE(CEB2),
        .D(\S_RESULT_COUNTER[0]_rep_i_1_n_0 ),
        .Q(\S_RESULT_COUNTER_reg[0]_rep_n_0 ),
        .R(RSTP));
  (* ORIG_CELL_NAME = "S_RESULT_COUNTER_reg[1]" *) 
  FDRE \S_RESULT_COUNTER_reg[1] 
       (.C(s00_axi_aclk),
        .CE(CEB2),
        .D(\S_RESULT_COUNTER[1]_i_1_n_0 ),
        .Q(S_RESULT_COUNTER[1]),
        .R(RSTP));
  (* ORIG_CELL_NAME = "S_RESULT_COUNTER_reg[1]" *) 
  FDRE \S_RESULT_COUNTER_reg[1]_rep 
       (.C(s00_axi_aclk),
        .CE(CEB2),
        .D(\S_RESULT_COUNTER[1]_rep_i_1_n_0 ),
        .Q(\S_RESULT_COUNTER_reg[1]_rep_n_0 ),
        .R(RSTP));
  FDRE \S_RESULT_COUNTER_reg[2] 
       (.C(s00_axi_aclk),
        .CE(CEB2),
        .D(B[2]),
        .Q(S_RESULT_COUNTER[2]),
        .R(RSTP));
  FDRE \S_RESULT_COUNTER_reg[3] 
       (.C(s00_axi_aclk),
        .CE(CEB2),
        .D(B[3]),
        .Q(S_RESULT_COUNTER[3]),
        .R(RSTP));
  LUT3 #(
    .INIT(8'h02)) 
    \S_SAMPLES[30]_i_1 
       (.I0(SET_SAMPLES),
        .I1(SET_CONVERSION),
        .I2(SET_OFFSET),
        .O(S_SAMPLES));
  FDSE \S_SAMPLES_reg[0] 
       (.C(s00_axi_aclk),
        .CE(S_SAMPLES),
        .D(\S_SAMPLE_TIME_reg[30]_1 [0]),
        .Q(\S_SAMPLES_reg_n_0_[0] ),
        .S(RSTP));
  FDRE \S_SAMPLES_reg[10] 
       (.C(s00_axi_aclk),
        .CE(S_SAMPLES),
        .D(\S_SAMPLE_TIME_reg[30]_1 [10]),
        .Q(\S_SAMPLES_reg_n_0_[10] ),
        .R(RSTP));
  FDRE \S_SAMPLES_reg[11] 
       (.C(s00_axi_aclk),
        .CE(S_SAMPLES),
        .D(\S_SAMPLE_TIME_reg[30]_1 [11]),
        .Q(\S_SAMPLES_reg_n_0_[11] ),
        .R(RSTP));
  FDRE \S_SAMPLES_reg[12] 
       (.C(s00_axi_aclk),
        .CE(S_SAMPLES),
        .D(\S_SAMPLE_TIME_reg[30]_1 [12]),
        .Q(\S_SAMPLES_reg_n_0_[12] ),
        .R(RSTP));
  FDRE \S_SAMPLES_reg[13] 
       (.C(s00_axi_aclk),
        .CE(S_SAMPLES),
        .D(\S_SAMPLE_TIME_reg[30]_1 [13]),
        .Q(\S_SAMPLES_reg_n_0_[13] ),
        .R(RSTP));
  FDRE \S_SAMPLES_reg[14] 
       (.C(s00_axi_aclk),
        .CE(S_SAMPLES),
        .D(\S_SAMPLE_TIME_reg[30]_1 [14]),
        .Q(\S_SAMPLES_reg_n_0_[14] ),
        .R(RSTP));
  FDRE \S_SAMPLES_reg[15] 
       (.C(s00_axi_aclk),
        .CE(S_SAMPLES),
        .D(\S_SAMPLE_TIME_reg[30]_1 [15]),
        .Q(\S_SAMPLES_reg_n_0_[15] ),
        .R(RSTP));
  FDRE \S_SAMPLES_reg[16] 
       (.C(s00_axi_aclk),
        .CE(S_SAMPLES),
        .D(\S_SAMPLE_TIME_reg[30]_1 [16]),
        .Q(\S_SAMPLES_reg_n_0_[16] ),
        .R(RSTP));
  FDRE \S_SAMPLES_reg[17] 
       (.C(s00_axi_aclk),
        .CE(S_SAMPLES),
        .D(\S_SAMPLE_TIME_reg[30]_1 [17]),
        .Q(\S_SAMPLES_reg_n_0_[17] ),
        .R(RSTP));
  FDRE \S_SAMPLES_reg[18] 
       (.C(s00_axi_aclk),
        .CE(S_SAMPLES),
        .D(\S_SAMPLE_TIME_reg[30]_1 [18]),
        .Q(\S_SAMPLES_reg_n_0_[18] ),
        .R(RSTP));
  FDRE \S_SAMPLES_reg[19] 
       (.C(s00_axi_aclk),
        .CE(S_SAMPLES),
        .D(\S_SAMPLE_TIME_reg[30]_1 [19]),
        .Q(\S_SAMPLES_reg_n_0_[19] ),
        .R(RSTP));
  FDRE \S_SAMPLES_reg[1] 
       (.C(s00_axi_aclk),
        .CE(S_SAMPLES),
        .D(\S_SAMPLE_TIME_reg[30]_1 [1]),
        .Q(\S_SAMPLES_reg_n_0_[1] ),
        .R(RSTP));
  FDRE \S_SAMPLES_reg[20] 
       (.C(s00_axi_aclk),
        .CE(S_SAMPLES),
        .D(\S_SAMPLE_TIME_reg[30]_1 [20]),
        .Q(\S_SAMPLES_reg_n_0_[20] ),
        .R(RSTP));
  FDRE \S_SAMPLES_reg[21] 
       (.C(s00_axi_aclk),
        .CE(S_SAMPLES),
        .D(\S_SAMPLE_TIME_reg[30]_1 [21]),
        .Q(\S_SAMPLES_reg_n_0_[21] ),
        .R(RSTP));
  FDRE \S_SAMPLES_reg[22] 
       (.C(s00_axi_aclk),
        .CE(S_SAMPLES),
        .D(\S_SAMPLE_TIME_reg[30]_1 [22]),
        .Q(\S_SAMPLES_reg_n_0_[22] ),
        .R(RSTP));
  FDRE \S_SAMPLES_reg[23] 
       (.C(s00_axi_aclk),
        .CE(S_SAMPLES),
        .D(\S_SAMPLE_TIME_reg[30]_1 [23]),
        .Q(\S_SAMPLES_reg_n_0_[23] ),
        .R(RSTP));
  FDRE \S_SAMPLES_reg[24] 
       (.C(s00_axi_aclk),
        .CE(S_SAMPLES),
        .D(\S_SAMPLE_TIME_reg[30]_1 [24]),
        .Q(\S_SAMPLES_reg_n_0_[24] ),
        .R(RSTP));
  FDRE \S_SAMPLES_reg[25] 
       (.C(s00_axi_aclk),
        .CE(S_SAMPLES),
        .D(\S_SAMPLE_TIME_reg[30]_1 [25]),
        .Q(\S_SAMPLES_reg_n_0_[25] ),
        .R(RSTP));
  FDRE \S_SAMPLES_reg[26] 
       (.C(s00_axi_aclk),
        .CE(S_SAMPLES),
        .D(\S_SAMPLE_TIME_reg[30]_1 [26]),
        .Q(\S_SAMPLES_reg_n_0_[26] ),
        .R(RSTP));
  FDRE \S_SAMPLES_reg[27] 
       (.C(s00_axi_aclk),
        .CE(S_SAMPLES),
        .D(\S_SAMPLE_TIME_reg[30]_1 [27]),
        .Q(\S_SAMPLES_reg_n_0_[27] ),
        .R(RSTP));
  FDRE \S_SAMPLES_reg[28] 
       (.C(s00_axi_aclk),
        .CE(S_SAMPLES),
        .D(\S_SAMPLE_TIME_reg[30]_1 [28]),
        .Q(\S_SAMPLES_reg_n_0_[28] ),
        .R(RSTP));
  FDRE \S_SAMPLES_reg[29] 
       (.C(s00_axi_aclk),
        .CE(S_SAMPLES),
        .D(\S_SAMPLE_TIME_reg[30]_1 [29]),
        .Q(\S_SAMPLES_reg_n_0_[29] ),
        .R(RSTP));
  FDRE \S_SAMPLES_reg[2] 
       (.C(s00_axi_aclk),
        .CE(S_SAMPLES),
        .D(\S_SAMPLE_TIME_reg[30]_1 [2]),
        .Q(\S_SAMPLES_reg_n_0_[2] ),
        .R(RSTP));
  FDRE \S_SAMPLES_reg[30] 
       (.C(s00_axi_aclk),
        .CE(S_SAMPLES),
        .D(\S_SAMPLE_TIME_reg[30]_1 [30]),
        .Q(\S_SAMPLES_reg_n_0_[30] ),
        .R(RSTP));
  FDRE \S_SAMPLES_reg[3] 
       (.C(s00_axi_aclk),
        .CE(S_SAMPLES),
        .D(\S_SAMPLE_TIME_reg[30]_1 [3]),
        .Q(\S_SAMPLES_reg_n_0_[3] ),
        .R(RSTP));
  FDRE \S_SAMPLES_reg[4] 
       (.C(s00_axi_aclk),
        .CE(S_SAMPLES),
        .D(\S_SAMPLE_TIME_reg[30]_1 [4]),
        .Q(\S_SAMPLES_reg_n_0_[4] ),
        .R(RSTP));
  FDRE \S_SAMPLES_reg[5] 
       (.C(s00_axi_aclk),
        .CE(S_SAMPLES),
        .D(\S_SAMPLE_TIME_reg[30]_1 [5]),
        .Q(\S_SAMPLES_reg_n_0_[5] ),
        .R(RSTP));
  FDRE \S_SAMPLES_reg[6] 
       (.C(s00_axi_aclk),
        .CE(S_SAMPLES),
        .D(\S_SAMPLE_TIME_reg[30]_1 [6]),
        .Q(\S_SAMPLES_reg_n_0_[6] ),
        .R(RSTP));
  FDRE \S_SAMPLES_reg[7] 
       (.C(s00_axi_aclk),
        .CE(S_SAMPLES),
        .D(\S_SAMPLE_TIME_reg[30]_1 [7]),
        .Q(\S_SAMPLES_reg_n_0_[7] ),
        .R(RSTP));
  FDRE \S_SAMPLES_reg[8] 
       (.C(s00_axi_aclk),
        .CE(S_SAMPLES),
        .D(\S_SAMPLE_TIME_reg[30]_1 [8]),
        .Q(\S_SAMPLES_reg_n_0_[8] ),
        .R(RSTP));
  FDRE \S_SAMPLES_reg[9] 
       (.C(s00_axi_aclk),
        .CE(S_SAMPLES),
        .D(\S_SAMPLE_TIME_reg[30]_1 [9]),
        .Q(\S_SAMPLES_reg_n_0_[9] ),
        .R(RSTP));
  LUT3 #(
    .INIT(8'hAB)) 
    \S_SAMPLE_COUNTER[0]_i_1 
       (.I0(\S_ENABLE_reg[0] ),
        .I1(\S_SAMPLE_COUNTER_reg[0]_0 ),
        .I2(V_SAMPLE_COUNTER2[31]),
        .O(\S_SAMPLE_COUNTER[0]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair102" *) 
  LUT3 #(
    .INIT(8'hAE)) 
    \S_SAMPLE_COUNTER[10]_i_1 
       (.I0(\S_ENABLE_reg[0] ),
        .I1(V_SAMPLE_COUNTER2[10]),
        .I2(V_SAMPLE_COUNTER2[31]),
        .O(\S_SAMPLE_COUNTER[10]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair101" *) 
  LUT3 #(
    .INIT(8'hAE)) 
    \S_SAMPLE_COUNTER[11]_i_1 
       (.I0(\S_ENABLE_reg[0] ),
        .I1(V_SAMPLE_COUNTER2[11]),
        .I2(V_SAMPLE_COUNTER2[31]),
        .O(\S_SAMPLE_COUNTER[11]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair101" *) 
  LUT3 #(
    .INIT(8'hAE)) 
    \S_SAMPLE_COUNTER[12]_i_1 
       (.I0(\S_ENABLE_reg[0] ),
        .I1(V_SAMPLE_COUNTER2[12]),
        .I2(V_SAMPLE_COUNTER2[31]),
        .O(\S_SAMPLE_COUNTER[12]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair100" *) 
  LUT3 #(
    .INIT(8'hAE)) 
    \S_SAMPLE_COUNTER[13]_i_1 
       (.I0(\S_ENABLE_reg[0] ),
        .I1(V_SAMPLE_COUNTER2[13]),
        .I2(V_SAMPLE_COUNTER2[31]),
        .O(\S_SAMPLE_COUNTER[13]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair100" *) 
  LUT3 #(
    .INIT(8'hAE)) 
    \S_SAMPLE_COUNTER[14]_i_1 
       (.I0(\S_ENABLE_reg[0] ),
        .I1(V_SAMPLE_COUNTER2[14]),
        .I2(V_SAMPLE_COUNTER2[31]),
        .O(\S_SAMPLE_COUNTER[14]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair99" *) 
  LUT3 #(
    .INIT(8'hAE)) 
    \S_SAMPLE_COUNTER[15]_i_1 
       (.I0(\S_ENABLE_reg[0] ),
        .I1(V_SAMPLE_COUNTER2[15]),
        .I2(V_SAMPLE_COUNTER2[31]),
        .O(\S_SAMPLE_COUNTER[15]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair99" *) 
  LUT3 #(
    .INIT(8'hAE)) 
    \S_SAMPLE_COUNTER[16]_i_1 
       (.I0(\S_ENABLE_reg[0] ),
        .I1(V_SAMPLE_COUNTER2[16]),
        .I2(V_SAMPLE_COUNTER2[31]),
        .O(\S_SAMPLE_COUNTER[16]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair98" *) 
  LUT3 #(
    .INIT(8'hAE)) 
    \S_SAMPLE_COUNTER[17]_i_1 
       (.I0(\S_ENABLE_reg[0] ),
        .I1(V_SAMPLE_COUNTER2[17]),
        .I2(V_SAMPLE_COUNTER2[31]),
        .O(\S_SAMPLE_COUNTER[17]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair98" *) 
  LUT3 #(
    .INIT(8'hAE)) 
    \S_SAMPLE_COUNTER[18]_i_1 
       (.I0(\S_ENABLE_reg[0] ),
        .I1(V_SAMPLE_COUNTER2[18]),
        .I2(V_SAMPLE_COUNTER2[31]),
        .O(\S_SAMPLE_COUNTER[18]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair97" *) 
  LUT3 #(
    .INIT(8'hAE)) 
    \S_SAMPLE_COUNTER[19]_i_1 
       (.I0(\S_ENABLE_reg[0] ),
        .I1(V_SAMPLE_COUNTER2[19]),
        .I2(V_SAMPLE_COUNTER2[31]),
        .O(\S_SAMPLE_COUNTER[19]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair106" *) 
  LUT3 #(
    .INIT(8'hAE)) 
    \S_SAMPLE_COUNTER[1]_i_1 
       (.I0(\S_ENABLE_reg[0] ),
        .I1(V_SAMPLE_COUNTER2[1]),
        .I2(V_SAMPLE_COUNTER2[31]),
        .O(\S_SAMPLE_COUNTER[1]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair97" *) 
  LUT3 #(
    .INIT(8'hAE)) 
    \S_SAMPLE_COUNTER[20]_i_1 
       (.I0(\S_ENABLE_reg[0] ),
        .I1(V_SAMPLE_COUNTER2[20]),
        .I2(V_SAMPLE_COUNTER2[31]),
        .O(\S_SAMPLE_COUNTER[20]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair96" *) 
  LUT3 #(
    .INIT(8'hAE)) 
    \S_SAMPLE_COUNTER[21]_i_1 
       (.I0(\S_ENABLE_reg[0] ),
        .I1(V_SAMPLE_COUNTER2[21]),
        .I2(V_SAMPLE_COUNTER2[31]),
        .O(\S_SAMPLE_COUNTER[21]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair96" *) 
  LUT3 #(
    .INIT(8'hAE)) 
    \S_SAMPLE_COUNTER[22]_i_1 
       (.I0(\S_ENABLE_reg[0] ),
        .I1(V_SAMPLE_COUNTER2[22]),
        .I2(V_SAMPLE_COUNTER2[31]),
        .O(\S_SAMPLE_COUNTER[22]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair95" *) 
  LUT3 #(
    .INIT(8'hAE)) 
    \S_SAMPLE_COUNTER[23]_i_1 
       (.I0(\S_ENABLE_reg[0] ),
        .I1(V_SAMPLE_COUNTER2[23]),
        .I2(V_SAMPLE_COUNTER2[31]),
        .O(\S_SAMPLE_COUNTER[23]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair95" *) 
  LUT3 #(
    .INIT(8'hAE)) 
    \S_SAMPLE_COUNTER[24]_i_1 
       (.I0(\S_ENABLE_reg[0] ),
        .I1(V_SAMPLE_COUNTER2[24]),
        .I2(V_SAMPLE_COUNTER2[31]),
        .O(\S_SAMPLE_COUNTER[24]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair94" *) 
  LUT3 #(
    .INIT(8'hAE)) 
    \S_SAMPLE_COUNTER[25]_i_1 
       (.I0(\S_ENABLE_reg[0] ),
        .I1(V_SAMPLE_COUNTER2[25]),
        .I2(V_SAMPLE_COUNTER2[31]),
        .O(\S_SAMPLE_COUNTER[25]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair94" *) 
  LUT3 #(
    .INIT(8'hAE)) 
    \S_SAMPLE_COUNTER[26]_i_1 
       (.I0(\S_ENABLE_reg[0] ),
        .I1(V_SAMPLE_COUNTER2[26]),
        .I2(V_SAMPLE_COUNTER2[31]),
        .O(\S_SAMPLE_COUNTER[26]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair93" *) 
  LUT3 #(
    .INIT(8'hAE)) 
    \S_SAMPLE_COUNTER[27]_i_1 
       (.I0(\S_ENABLE_reg[0] ),
        .I1(V_SAMPLE_COUNTER2[27]),
        .I2(V_SAMPLE_COUNTER2[31]),
        .O(\S_SAMPLE_COUNTER[27]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair93" *) 
  LUT3 #(
    .INIT(8'hAE)) 
    \S_SAMPLE_COUNTER[28]_i_1 
       (.I0(\S_ENABLE_reg[0] ),
        .I1(V_SAMPLE_COUNTER2[28]),
        .I2(V_SAMPLE_COUNTER2[31]),
        .O(\S_SAMPLE_COUNTER[28]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair92" *) 
  LUT3 #(
    .INIT(8'hAE)) 
    \S_SAMPLE_COUNTER[29]_i_1 
       (.I0(\S_ENABLE_reg[0] ),
        .I1(V_SAMPLE_COUNTER2[29]),
        .I2(V_SAMPLE_COUNTER2[31]),
        .O(\S_SAMPLE_COUNTER[29]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair106" *) 
  LUT3 #(
    .INIT(8'hAE)) 
    \S_SAMPLE_COUNTER[2]_i_1 
       (.I0(\S_ENABLE_reg[0] ),
        .I1(V_SAMPLE_COUNTER2[2]),
        .I2(V_SAMPLE_COUNTER2[31]),
        .O(\S_SAMPLE_COUNTER[2]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair92" *) 
  LUT3 #(
    .INIT(8'hBA)) 
    \S_SAMPLE_COUNTER[30]_i_1 
       (.I0(\S_ENABLE_reg[0] ),
        .I1(V_SAMPLE_COUNTER2[31]),
        .I2(V_SAMPLE_COUNTER2[30]),
        .O(\S_SAMPLE_COUNTER[30]_i_1_n_0 ));
  LUT2 #(
    .INIT(4'h8)) 
    \S_SAMPLE_COUNTER[31]_i_1 
       (.I0(\S_ENABLE_reg[0] ),
        .I1(S_SAMPLE_COUNTER),
        .O(\S_SAMPLE_COUNTER[31]_i_1_n_0 ));
  LUT6 #(
    .INIT(64'h0000000004040444)) 
    \S_SAMPLE_COUNTER[31]_i_2 
       (.I0(S_CPOL_reg),
        .I1(s00_axi_aresetn),
        .I2(\S_SAMPLE_COUNTER[31]_i_3_n_0 ),
        .I3(Q[0]),
        .I4(Q[1]),
        .I5(\S_ENABLE_reg[0]_0 ),
        .O(S_SAMPLE_COUNTER));
  (* SOFT_HLUTNM = "soft_lutpair86" *) 
  LUT5 #(
    .INIT(32'hF2FFF0FF)) 
    \S_SAMPLE_COUNTER[31]_i_3 
       (.I0(S_SPI_BUSY_PIPE[1]),
        .I1(S_SPI_BUSY_PIPE[0]),
        .I2(Q[0]),
        .I3(Q[1]),
        .I4(S_DUMMY_SAMPLE),
        .O(\S_SAMPLE_COUNTER[31]_i_3_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair105" *) 
  LUT3 #(
    .INIT(8'hAE)) 
    \S_SAMPLE_COUNTER[3]_i_1 
       (.I0(\S_ENABLE_reg[0] ),
        .I1(V_SAMPLE_COUNTER2[3]),
        .I2(V_SAMPLE_COUNTER2[31]),
        .O(\S_SAMPLE_COUNTER[3]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair105" *) 
  LUT3 #(
    .INIT(8'hAE)) 
    \S_SAMPLE_COUNTER[4]_i_1 
       (.I0(\S_ENABLE_reg[0] ),
        .I1(V_SAMPLE_COUNTER2[4]),
        .I2(V_SAMPLE_COUNTER2[31]),
        .O(\S_SAMPLE_COUNTER[4]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair104" *) 
  LUT3 #(
    .INIT(8'hAE)) 
    \S_SAMPLE_COUNTER[5]_i_1 
       (.I0(\S_ENABLE_reg[0] ),
        .I1(V_SAMPLE_COUNTER2[5]),
        .I2(V_SAMPLE_COUNTER2[31]),
        .O(\S_SAMPLE_COUNTER[5]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair104" *) 
  LUT3 #(
    .INIT(8'hAE)) 
    \S_SAMPLE_COUNTER[6]_i_1 
       (.I0(\S_ENABLE_reg[0] ),
        .I1(V_SAMPLE_COUNTER2[6]),
        .I2(V_SAMPLE_COUNTER2[31]),
        .O(\S_SAMPLE_COUNTER[6]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair103" *) 
  LUT3 #(
    .INIT(8'hAE)) 
    \S_SAMPLE_COUNTER[7]_i_1 
       (.I0(\S_ENABLE_reg[0] ),
        .I1(V_SAMPLE_COUNTER2[7]),
        .I2(V_SAMPLE_COUNTER2[31]),
        .O(\S_SAMPLE_COUNTER[7]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair103" *) 
  LUT3 #(
    .INIT(8'hAE)) 
    \S_SAMPLE_COUNTER[8]_i_1 
       (.I0(\S_ENABLE_reg[0] ),
        .I1(V_SAMPLE_COUNTER2[8]),
        .I2(V_SAMPLE_COUNTER2[31]),
        .O(\S_SAMPLE_COUNTER[8]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair102" *) 
  LUT3 #(
    .INIT(8'hAE)) 
    \S_SAMPLE_COUNTER[9]_i_1 
       (.I0(\S_ENABLE_reg[0] ),
        .I1(V_SAMPLE_COUNTER2[9]),
        .I2(V_SAMPLE_COUNTER2[31]),
        .O(\S_SAMPLE_COUNTER[9]_i_1_n_0 ));
  FDSE \S_SAMPLE_COUNTER_reg[0] 
       (.C(s00_axi_aclk),
        .CE(S_SAMPLE_COUNTER),
        .D(\S_SAMPLE_COUNTER[0]_i_1_n_0 ),
        .Q(\S_SAMPLE_COUNTER_reg[0]_0 ),
        .S(1'b0));
  FDSE \S_SAMPLE_COUNTER_reg[10] 
       (.C(s00_axi_aclk),
        .CE(S_SAMPLE_COUNTER),
        .D(\S_SAMPLE_COUNTER[10]_i_1_n_0 ),
        .Q(\S_SAMPLE_COUNTER_reg[16]_0 [1]),
        .S(1'b0));
  FDSE \S_SAMPLE_COUNTER_reg[11] 
       (.C(s00_axi_aclk),
        .CE(S_SAMPLE_COUNTER),
        .D(\S_SAMPLE_COUNTER[11]_i_1_n_0 ),
        .Q(\S_SAMPLE_COUNTER_reg[16]_0 [2]),
        .S(1'b0));
  FDSE \S_SAMPLE_COUNTER_reg[12] 
       (.C(s00_axi_aclk),
        .CE(S_SAMPLE_COUNTER),
        .D(\S_SAMPLE_COUNTER[12]_i_1_n_0 ),
        .Q(\S_SAMPLE_COUNTER_reg[16]_0 [3]),
        .S(1'b0));
  FDSE \S_SAMPLE_COUNTER_reg[13] 
       (.C(s00_axi_aclk),
        .CE(S_SAMPLE_COUNTER),
        .D(\S_SAMPLE_COUNTER[13]_i_1_n_0 ),
        .Q(\S_SAMPLE_COUNTER_reg[16]_0 [4]),
        .S(1'b0));
  FDSE \S_SAMPLE_COUNTER_reg[14] 
       (.C(s00_axi_aclk),
        .CE(S_SAMPLE_COUNTER),
        .D(\S_SAMPLE_COUNTER[14]_i_1_n_0 ),
        .Q(\S_SAMPLE_COUNTER_reg[16]_0 [5]),
        .S(1'b0));
  FDSE \S_SAMPLE_COUNTER_reg[15] 
       (.C(s00_axi_aclk),
        .CE(S_SAMPLE_COUNTER),
        .D(\S_SAMPLE_COUNTER[15]_i_1_n_0 ),
        .Q(\S_SAMPLE_COUNTER_reg[16]_0 [6]),
        .S(1'b0));
  FDSE \S_SAMPLE_COUNTER_reg[16] 
       (.C(s00_axi_aclk),
        .CE(S_SAMPLE_COUNTER),
        .D(\S_SAMPLE_COUNTER[16]_i_1_n_0 ),
        .Q(\S_SAMPLE_COUNTER_reg[16]_0 [7]),
        .S(1'b0));
  (* ADDER_THRESHOLD = "35" *) 
  CARRY8 \S_SAMPLE_COUNTER_reg[16]_i_2 
       (.CI(\S_SAMPLE_COUNTER_reg[8]_i_2_n_0 ),
        .CI_TOP(1'b0),
        .CO({\S_SAMPLE_COUNTER_reg[16]_i_2_n_0 ,\S_SAMPLE_COUNTER_reg[16]_i_2_n_1 ,\S_SAMPLE_COUNTER_reg[16]_i_2_n_2 ,\S_SAMPLE_COUNTER_reg[16]_i_2_n_3 ,\S_SAMPLE_COUNTER_reg[16]_i_2_n_4 ,\S_SAMPLE_COUNTER_reg[16]_i_2_n_5 ,\S_SAMPLE_COUNTER_reg[16]_i_2_n_6 ,\S_SAMPLE_COUNTER_reg[16]_i_2_n_7 }),
        .DI({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .O(V_SAMPLE_COUNTER2[16:9]),
        .S(\S_SAMPLE_COUNTER_reg[16]_0 ));
  FDSE \S_SAMPLE_COUNTER_reg[17] 
       (.C(s00_axi_aclk),
        .CE(S_SAMPLE_COUNTER),
        .D(\S_SAMPLE_COUNTER[17]_i_1_n_0 ),
        .Q(\S_SAMPLE_COUNTER_reg[24]_0 [0]),
        .S(1'b0));
  FDSE \S_SAMPLE_COUNTER_reg[18] 
       (.C(s00_axi_aclk),
        .CE(S_SAMPLE_COUNTER),
        .D(\S_SAMPLE_COUNTER[18]_i_1_n_0 ),
        .Q(\S_SAMPLE_COUNTER_reg[24]_0 [1]),
        .S(1'b0));
  FDSE \S_SAMPLE_COUNTER_reg[19] 
       (.C(s00_axi_aclk),
        .CE(S_SAMPLE_COUNTER),
        .D(\S_SAMPLE_COUNTER[19]_i_1_n_0 ),
        .Q(\S_SAMPLE_COUNTER_reg[24]_0 [2]),
        .S(1'b0));
  FDSE \S_SAMPLE_COUNTER_reg[1] 
       (.C(s00_axi_aclk),
        .CE(S_SAMPLE_COUNTER),
        .D(\S_SAMPLE_COUNTER[1]_i_1_n_0 ),
        .Q(S[0]),
        .S(1'b0));
  FDSE \S_SAMPLE_COUNTER_reg[20] 
       (.C(s00_axi_aclk),
        .CE(S_SAMPLE_COUNTER),
        .D(\S_SAMPLE_COUNTER[20]_i_1_n_0 ),
        .Q(\S_SAMPLE_COUNTER_reg[24]_0 [3]),
        .S(1'b0));
  FDSE \S_SAMPLE_COUNTER_reg[21] 
       (.C(s00_axi_aclk),
        .CE(S_SAMPLE_COUNTER),
        .D(\S_SAMPLE_COUNTER[21]_i_1_n_0 ),
        .Q(\S_SAMPLE_COUNTER_reg[24]_0 [4]),
        .S(1'b0));
  FDSE \S_SAMPLE_COUNTER_reg[22] 
       (.C(s00_axi_aclk),
        .CE(S_SAMPLE_COUNTER),
        .D(\S_SAMPLE_COUNTER[22]_i_1_n_0 ),
        .Q(\S_SAMPLE_COUNTER_reg[24]_0 [5]),
        .S(1'b0));
  FDSE \S_SAMPLE_COUNTER_reg[23] 
       (.C(s00_axi_aclk),
        .CE(S_SAMPLE_COUNTER),
        .D(\S_SAMPLE_COUNTER[23]_i_1_n_0 ),
        .Q(\S_SAMPLE_COUNTER_reg[24]_0 [6]),
        .S(1'b0));
  FDSE \S_SAMPLE_COUNTER_reg[24] 
       (.C(s00_axi_aclk),
        .CE(S_SAMPLE_COUNTER),
        .D(\S_SAMPLE_COUNTER[24]_i_1_n_0 ),
        .Q(\S_SAMPLE_COUNTER_reg[24]_0 [7]),
        .S(1'b0));
  (* ADDER_THRESHOLD = "35" *) 
  CARRY8 \S_SAMPLE_COUNTER_reg[24]_i_2 
       (.CI(\S_SAMPLE_COUNTER_reg[16]_i_2_n_0 ),
        .CI_TOP(1'b0),
        .CO({\S_SAMPLE_COUNTER_reg[24]_i_2_n_0 ,\S_SAMPLE_COUNTER_reg[24]_i_2_n_1 ,\S_SAMPLE_COUNTER_reg[24]_i_2_n_2 ,\S_SAMPLE_COUNTER_reg[24]_i_2_n_3 ,\S_SAMPLE_COUNTER_reg[24]_i_2_n_4 ,\S_SAMPLE_COUNTER_reg[24]_i_2_n_5 ,\S_SAMPLE_COUNTER_reg[24]_i_2_n_6 ,\S_SAMPLE_COUNTER_reg[24]_i_2_n_7 }),
        .DI({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .O(V_SAMPLE_COUNTER2[24:17]),
        .S(\S_SAMPLE_COUNTER_reg[24]_0 ));
  FDSE \S_SAMPLE_COUNTER_reg[25] 
       (.C(s00_axi_aclk),
        .CE(S_SAMPLE_COUNTER),
        .D(\S_SAMPLE_COUNTER[25]_i_1_n_0 ),
        .Q(\S_SAMPLE_COUNTER_reg[31]_0 [0]),
        .S(1'b0));
  FDSE \S_SAMPLE_COUNTER_reg[26] 
       (.C(s00_axi_aclk),
        .CE(S_SAMPLE_COUNTER),
        .D(\S_SAMPLE_COUNTER[26]_i_1_n_0 ),
        .Q(\S_SAMPLE_COUNTER_reg[31]_0 [1]),
        .S(1'b0));
  FDSE \S_SAMPLE_COUNTER_reg[27] 
       (.C(s00_axi_aclk),
        .CE(S_SAMPLE_COUNTER),
        .D(\S_SAMPLE_COUNTER[27]_i_1_n_0 ),
        .Q(\S_SAMPLE_COUNTER_reg[31]_0 [2]),
        .S(1'b0));
  FDSE \S_SAMPLE_COUNTER_reg[28] 
       (.C(s00_axi_aclk),
        .CE(S_SAMPLE_COUNTER),
        .D(\S_SAMPLE_COUNTER[28]_i_1_n_0 ),
        .Q(\S_SAMPLE_COUNTER_reg[31]_0 [3]),
        .S(1'b0));
  FDSE \S_SAMPLE_COUNTER_reg[29] 
       (.C(s00_axi_aclk),
        .CE(S_SAMPLE_COUNTER),
        .D(\S_SAMPLE_COUNTER[29]_i_1_n_0 ),
        .Q(\S_SAMPLE_COUNTER_reg[31]_0 [4]),
        .S(1'b0));
  FDSE \S_SAMPLE_COUNTER_reg[2] 
       (.C(s00_axi_aclk),
        .CE(S_SAMPLE_COUNTER),
        .D(\S_SAMPLE_COUNTER[2]_i_1_n_0 ),
        .Q(S[1]),
        .S(1'b0));
  FDSE \S_SAMPLE_COUNTER_reg[30] 
       (.C(s00_axi_aclk),
        .CE(S_SAMPLE_COUNTER),
        .D(\S_SAMPLE_COUNTER[30]_i_1_n_0 ),
        .Q(\S_SAMPLE_COUNTER_reg[31]_0 [5]),
        .S(1'b0));
  (* ADDER_THRESHOLD = "35" *) 
  CARRY8 \S_SAMPLE_COUNTER_reg[30]_i_2 
       (.CI(\S_SAMPLE_COUNTER_reg[24]_i_2_n_0 ),
        .CI_TOP(1'b0),
        .CO({\NLW_S_SAMPLE_COUNTER_reg[30]_i_2_CO_UNCONNECTED [7:6],\S_SAMPLE_COUNTER_reg[30]_i_2_n_2 ,\S_SAMPLE_COUNTER_reg[30]_i_2_n_3 ,\S_SAMPLE_COUNTER_reg[30]_i_2_n_4 ,\S_SAMPLE_COUNTER_reg[30]_i_2_n_5 ,\S_SAMPLE_COUNTER_reg[30]_i_2_n_6 ,\S_SAMPLE_COUNTER_reg[30]_i_2_n_7 }),
        .DI({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .O({\NLW_S_SAMPLE_COUNTER_reg[30]_i_2_O_UNCONNECTED [7],V_SAMPLE_COUNTER2[31:25]}),
        .S({1'b0,\S_SAMPLE_COUNTER_reg[31]_0 }));
  FDSE \S_SAMPLE_COUNTER_reg[31] 
       (.C(s00_axi_aclk),
        .CE(S_SAMPLE_COUNTER),
        .D(1'b0),
        .Q(\S_SAMPLE_COUNTER_reg[31]_0 [6]),
        .S(\S_SAMPLE_COUNTER[31]_i_1_n_0 ));
  FDSE \S_SAMPLE_COUNTER_reg[3] 
       (.C(s00_axi_aclk),
        .CE(S_SAMPLE_COUNTER),
        .D(\S_SAMPLE_COUNTER[3]_i_1_n_0 ),
        .Q(S[2]),
        .S(1'b0));
  FDSE \S_SAMPLE_COUNTER_reg[4] 
       (.C(s00_axi_aclk),
        .CE(S_SAMPLE_COUNTER),
        .D(\S_SAMPLE_COUNTER[4]_i_1_n_0 ),
        .Q(S[3]),
        .S(1'b0));
  FDSE \S_SAMPLE_COUNTER_reg[5] 
       (.C(s00_axi_aclk),
        .CE(S_SAMPLE_COUNTER),
        .D(\S_SAMPLE_COUNTER[5]_i_1_n_0 ),
        .Q(S[4]),
        .S(1'b0));
  FDSE \S_SAMPLE_COUNTER_reg[6] 
       (.C(s00_axi_aclk),
        .CE(S_SAMPLE_COUNTER),
        .D(\S_SAMPLE_COUNTER[6]_i_1_n_0 ),
        .Q(S[5]),
        .S(1'b0));
  FDSE \S_SAMPLE_COUNTER_reg[7] 
       (.C(s00_axi_aclk),
        .CE(S_SAMPLE_COUNTER),
        .D(\S_SAMPLE_COUNTER[7]_i_1_n_0 ),
        .Q(S[6]),
        .S(1'b0));
  FDSE \S_SAMPLE_COUNTER_reg[8] 
       (.C(s00_axi_aclk),
        .CE(S_SAMPLE_COUNTER),
        .D(\S_SAMPLE_COUNTER[8]_i_1_n_0 ),
        .Q(S[7]),
        .S(1'b0));
  (* ADDER_THRESHOLD = "35" *) 
  CARRY8 \S_SAMPLE_COUNTER_reg[8]_i_2 
       (.CI(\S_SAMPLE_COUNTER_reg[0]_0 ),
        .CI_TOP(1'b0),
        .CO({\S_SAMPLE_COUNTER_reg[8]_i_2_n_0 ,\S_SAMPLE_COUNTER_reg[8]_i_2_n_1 ,\S_SAMPLE_COUNTER_reg[8]_i_2_n_2 ,\S_SAMPLE_COUNTER_reg[8]_i_2_n_3 ,\S_SAMPLE_COUNTER_reg[8]_i_2_n_4 ,\S_SAMPLE_COUNTER_reg[8]_i_2_n_5 ,\S_SAMPLE_COUNTER_reg[8]_i_2_n_6 ,\S_SAMPLE_COUNTER_reg[8]_i_2_n_7 }),
        .DI({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .O(V_SAMPLE_COUNTER2[8:1]),
        .S(S));
  FDSE \S_SAMPLE_COUNTER_reg[9] 
       (.C(s00_axi_aclk),
        .CE(S_SAMPLE_COUNTER),
        .D(\S_SAMPLE_COUNTER[9]_i_1_n_0 ),
        .Q(\S_SAMPLE_COUNTER_reg[16]_0 [0]),
        .S(1'b0));
  LUT6 #(
    .INIT(64'h1F001000FFE0FFEF)) 
    \S_SAMPLE_TIME_COUNTER[0]_i_1 
       (.I0(Q[1]),
        .I1(Q[0]),
        .I2(\S_ENABLE_reg[0] ),
        .I3(\S_SAMPLE_TIME_reg_n_0_[0] ),
        .I4(\S_ENABLE_reg[0]_0 ),
        .I5(S_SAMPLE_TIME_COUNTER[0]),
        .O(p_2_in[0]));
  LUT6 #(
    .INIT(64'hFFE0FFEF1F001000)) 
    \S_SAMPLE_TIME_COUNTER[10]_i_1 
       (.I0(Q[1]),
        .I1(Q[0]),
        .I2(\S_ENABLE_reg[0] ),
        .I3(\S_SAMPLE_TIME_reg_n_0_[10] ),
        .I4(\S_ENABLE_reg[0]_0 ),
        .I5(S_SAMPLE_TIME_COUNTER0__0[10]),
        .O(p_2_in[10]));
  LUT6 #(
    .INIT(64'hFFE0FFEF1F001000)) 
    \S_SAMPLE_TIME_COUNTER[11]_i_1 
       (.I0(Q[1]),
        .I1(Q[0]),
        .I2(\S_ENABLE_reg[0] ),
        .I3(\S_SAMPLE_TIME_reg_n_0_[11] ),
        .I4(\S_ENABLE_reg[0]_0 ),
        .I5(S_SAMPLE_TIME_COUNTER0__0[11]),
        .O(p_2_in[11]));
  LUT6 #(
    .INIT(64'hFFE0FFEF1F001000)) 
    \S_SAMPLE_TIME_COUNTER[12]_i_1 
       (.I0(Q[1]),
        .I1(Q[0]),
        .I2(\S_ENABLE_reg[0] ),
        .I3(\S_SAMPLE_TIME_reg_n_0_[12] ),
        .I4(\S_ENABLE_reg[0]_0 ),
        .I5(S_SAMPLE_TIME_COUNTER0__0[12]),
        .O(p_2_in[12]));
  LUT6 #(
    .INIT(64'hFFE0FFEF1F001000)) 
    \S_SAMPLE_TIME_COUNTER[13]_i_1 
       (.I0(Q[1]),
        .I1(Q[0]),
        .I2(\S_ENABLE_reg[0] ),
        .I3(\S_SAMPLE_TIME_reg_n_0_[13] ),
        .I4(\S_ENABLE_reg[0]_0 ),
        .I5(S_SAMPLE_TIME_COUNTER0__0[13]),
        .O(p_2_in[13]));
  LUT6 #(
    .INIT(64'hFFE0FFEF1F001000)) 
    \S_SAMPLE_TIME_COUNTER[14]_i_1 
       (.I0(Q[1]),
        .I1(Q[0]),
        .I2(\S_ENABLE_reg[0] ),
        .I3(\S_SAMPLE_TIME_reg_n_0_[14] ),
        .I4(\S_ENABLE_reg[0]_0 ),
        .I5(S_SAMPLE_TIME_COUNTER0__0[14]),
        .O(p_2_in[14]));
  LUT6 #(
    .INIT(64'hFFE0FFEF1F001000)) 
    \S_SAMPLE_TIME_COUNTER[15]_i_1 
       (.I0(Q[1]),
        .I1(Q[0]),
        .I2(\S_ENABLE_reg[0] ),
        .I3(\S_SAMPLE_TIME_reg_n_0_[15] ),
        .I4(\S_ENABLE_reg[0]_0 ),
        .I5(S_SAMPLE_TIME_COUNTER0__0[15]),
        .O(p_2_in[15]));
  LUT6 #(
    .INIT(64'hFFE0FFEF1F001000)) 
    \S_SAMPLE_TIME_COUNTER[16]_i_1 
       (.I0(Q[1]),
        .I1(Q[0]),
        .I2(\S_ENABLE_reg[0] ),
        .I3(\S_SAMPLE_TIME_reg_n_0_[16] ),
        .I4(\S_ENABLE_reg[0]_0 ),
        .I5(S_SAMPLE_TIME_COUNTER0__0[16]),
        .O(p_2_in[16]));
  LUT1 #(
    .INIT(2'h1)) 
    \S_SAMPLE_TIME_COUNTER[16]_i_10 
       (.I0(S_SAMPLE_TIME_COUNTER[9]),
        .O(\S_SAMPLE_TIME_COUNTER[16]_i_10_n_0 ));
  LUT1 #(
    .INIT(2'h1)) 
    \S_SAMPLE_TIME_COUNTER[16]_i_3 
       (.I0(S_SAMPLE_TIME_COUNTER[16]),
        .O(\S_SAMPLE_TIME_COUNTER[16]_i_3_n_0 ));
  LUT1 #(
    .INIT(2'h1)) 
    \S_SAMPLE_TIME_COUNTER[16]_i_4 
       (.I0(S_SAMPLE_TIME_COUNTER[15]),
        .O(\S_SAMPLE_TIME_COUNTER[16]_i_4_n_0 ));
  LUT1 #(
    .INIT(2'h1)) 
    \S_SAMPLE_TIME_COUNTER[16]_i_5 
       (.I0(S_SAMPLE_TIME_COUNTER[14]),
        .O(\S_SAMPLE_TIME_COUNTER[16]_i_5_n_0 ));
  LUT1 #(
    .INIT(2'h1)) 
    \S_SAMPLE_TIME_COUNTER[16]_i_6 
       (.I0(S_SAMPLE_TIME_COUNTER[13]),
        .O(\S_SAMPLE_TIME_COUNTER[16]_i_6_n_0 ));
  LUT1 #(
    .INIT(2'h1)) 
    \S_SAMPLE_TIME_COUNTER[16]_i_7 
       (.I0(S_SAMPLE_TIME_COUNTER[12]),
        .O(\S_SAMPLE_TIME_COUNTER[16]_i_7_n_0 ));
  LUT1 #(
    .INIT(2'h1)) 
    \S_SAMPLE_TIME_COUNTER[16]_i_8 
       (.I0(S_SAMPLE_TIME_COUNTER[11]),
        .O(\S_SAMPLE_TIME_COUNTER[16]_i_8_n_0 ));
  LUT1 #(
    .INIT(2'h1)) 
    \S_SAMPLE_TIME_COUNTER[16]_i_9 
       (.I0(S_SAMPLE_TIME_COUNTER[10]),
        .O(\S_SAMPLE_TIME_COUNTER[16]_i_9_n_0 ));
  LUT6 #(
    .INIT(64'hFFE0FFEF1F001000)) 
    \S_SAMPLE_TIME_COUNTER[17]_i_1 
       (.I0(Q[1]),
        .I1(Q[0]),
        .I2(\S_ENABLE_reg[0] ),
        .I3(\S_SAMPLE_TIME_reg_n_0_[17] ),
        .I4(\S_ENABLE_reg[0]_0 ),
        .I5(S_SAMPLE_TIME_COUNTER0__0[17]),
        .O(p_2_in[17]));
  LUT6 #(
    .INIT(64'hFFE0FFEF1F001000)) 
    \S_SAMPLE_TIME_COUNTER[18]_i_1 
       (.I0(Q[1]),
        .I1(Q[0]),
        .I2(\S_ENABLE_reg[0] ),
        .I3(\S_SAMPLE_TIME_reg_n_0_[18] ),
        .I4(\S_ENABLE_reg[0]_0 ),
        .I5(S_SAMPLE_TIME_COUNTER0__0[18]),
        .O(p_2_in[18]));
  LUT6 #(
    .INIT(64'hFFE0FFEF1F001000)) 
    \S_SAMPLE_TIME_COUNTER[19]_i_1 
       (.I0(Q[1]),
        .I1(Q[0]),
        .I2(\S_ENABLE_reg[0] ),
        .I3(\S_SAMPLE_TIME_reg_n_0_[19] ),
        .I4(\S_ENABLE_reg[0]_0 ),
        .I5(S_SAMPLE_TIME_COUNTER0__0[19]),
        .O(p_2_in[19]));
  LUT6 #(
    .INIT(64'hFFE0FFEF1F001000)) 
    \S_SAMPLE_TIME_COUNTER[1]_i_1 
       (.I0(Q[1]),
        .I1(Q[0]),
        .I2(\S_ENABLE_reg[0] ),
        .I3(\S_SAMPLE_TIME_reg_n_0_[1] ),
        .I4(\S_ENABLE_reg[0]_0 ),
        .I5(S_SAMPLE_TIME_COUNTER0__0[1]),
        .O(p_2_in[1]));
  LUT6 #(
    .INIT(64'hFFE0FFEF1F001000)) 
    \S_SAMPLE_TIME_COUNTER[20]_i_1 
       (.I0(Q[1]),
        .I1(Q[0]),
        .I2(\S_ENABLE_reg[0] ),
        .I3(\S_SAMPLE_TIME_reg_n_0_[20] ),
        .I4(\S_ENABLE_reg[0]_0 ),
        .I5(S_SAMPLE_TIME_COUNTER0__0[20]),
        .O(p_2_in[20]));
  LUT6 #(
    .INIT(64'hFFE0FFEF1F001000)) 
    \S_SAMPLE_TIME_COUNTER[21]_i_1 
       (.I0(Q[1]),
        .I1(Q[0]),
        .I2(\S_ENABLE_reg[0] ),
        .I3(\S_SAMPLE_TIME_reg_n_0_[21] ),
        .I4(\S_ENABLE_reg[0]_0 ),
        .I5(S_SAMPLE_TIME_COUNTER0__0[21]),
        .O(p_2_in[21]));
  LUT6 #(
    .INIT(64'hFFE0FFEF1F001000)) 
    \S_SAMPLE_TIME_COUNTER[22]_i_1 
       (.I0(Q[1]),
        .I1(Q[0]),
        .I2(\S_ENABLE_reg[0] ),
        .I3(\S_SAMPLE_TIME_reg_n_0_[22] ),
        .I4(\S_ENABLE_reg[0]_0 ),
        .I5(S_SAMPLE_TIME_COUNTER0__0[22]),
        .O(p_2_in[22]));
  LUT6 #(
    .INIT(64'hFFE0FFEF1F001000)) 
    \S_SAMPLE_TIME_COUNTER[23]_i_1 
       (.I0(Q[1]),
        .I1(Q[0]),
        .I2(\S_ENABLE_reg[0] ),
        .I3(\S_SAMPLE_TIME_reg_n_0_[23] ),
        .I4(\S_ENABLE_reg[0]_0 ),
        .I5(S_SAMPLE_TIME_COUNTER0__0[23]),
        .O(p_2_in[23]));
  LUT6 #(
    .INIT(64'hFFE0FFEF1F001000)) 
    \S_SAMPLE_TIME_COUNTER[24]_i_1 
       (.I0(Q[1]),
        .I1(Q[0]),
        .I2(\S_ENABLE_reg[0] ),
        .I3(\S_SAMPLE_TIME_reg_n_0_[24] ),
        .I4(\S_ENABLE_reg[0]_0 ),
        .I5(S_SAMPLE_TIME_COUNTER0__0[24]),
        .O(p_2_in[24]));
  LUT1 #(
    .INIT(2'h1)) 
    \S_SAMPLE_TIME_COUNTER[24]_i_10 
       (.I0(S_SAMPLE_TIME_COUNTER[17]),
        .O(\S_SAMPLE_TIME_COUNTER[24]_i_10_n_0 ));
  LUT1 #(
    .INIT(2'h1)) 
    \S_SAMPLE_TIME_COUNTER[24]_i_3 
       (.I0(S_SAMPLE_TIME_COUNTER[24]),
        .O(\S_SAMPLE_TIME_COUNTER[24]_i_3_n_0 ));
  LUT1 #(
    .INIT(2'h1)) 
    \S_SAMPLE_TIME_COUNTER[24]_i_4 
       (.I0(S_SAMPLE_TIME_COUNTER[23]),
        .O(\S_SAMPLE_TIME_COUNTER[24]_i_4_n_0 ));
  LUT1 #(
    .INIT(2'h1)) 
    \S_SAMPLE_TIME_COUNTER[24]_i_5 
       (.I0(S_SAMPLE_TIME_COUNTER[22]),
        .O(\S_SAMPLE_TIME_COUNTER[24]_i_5_n_0 ));
  LUT1 #(
    .INIT(2'h1)) 
    \S_SAMPLE_TIME_COUNTER[24]_i_6 
       (.I0(S_SAMPLE_TIME_COUNTER[21]),
        .O(\S_SAMPLE_TIME_COUNTER[24]_i_6_n_0 ));
  LUT1 #(
    .INIT(2'h1)) 
    \S_SAMPLE_TIME_COUNTER[24]_i_7 
       (.I0(S_SAMPLE_TIME_COUNTER[20]),
        .O(\S_SAMPLE_TIME_COUNTER[24]_i_7_n_0 ));
  LUT1 #(
    .INIT(2'h1)) 
    \S_SAMPLE_TIME_COUNTER[24]_i_8 
       (.I0(S_SAMPLE_TIME_COUNTER[19]),
        .O(\S_SAMPLE_TIME_COUNTER[24]_i_8_n_0 ));
  LUT1 #(
    .INIT(2'h1)) 
    \S_SAMPLE_TIME_COUNTER[24]_i_9 
       (.I0(S_SAMPLE_TIME_COUNTER[18]),
        .O(\S_SAMPLE_TIME_COUNTER[24]_i_9_n_0 ));
  LUT6 #(
    .INIT(64'hFFE0FFEF1F001000)) 
    \S_SAMPLE_TIME_COUNTER[25]_i_1 
       (.I0(Q[1]),
        .I1(Q[0]),
        .I2(\S_ENABLE_reg[0] ),
        .I3(\S_SAMPLE_TIME_reg_n_0_[25] ),
        .I4(\S_ENABLE_reg[0]_0 ),
        .I5(S_SAMPLE_TIME_COUNTER0__0[25]),
        .O(p_2_in[25]));
  LUT6 #(
    .INIT(64'hFFE0FFEF1F001000)) 
    \S_SAMPLE_TIME_COUNTER[26]_i_1 
       (.I0(Q[1]),
        .I1(Q[0]),
        .I2(\S_ENABLE_reg[0] ),
        .I3(\S_SAMPLE_TIME_reg_n_0_[26] ),
        .I4(\S_ENABLE_reg[0]_0 ),
        .I5(S_SAMPLE_TIME_COUNTER0__0[26]),
        .O(p_2_in[26]));
  LUT6 #(
    .INIT(64'hFFE0FFEF1F001000)) 
    \S_SAMPLE_TIME_COUNTER[27]_i_1 
       (.I0(Q[1]),
        .I1(Q[0]),
        .I2(\S_ENABLE_reg[0] ),
        .I3(\S_SAMPLE_TIME_reg_n_0_[27] ),
        .I4(\S_ENABLE_reg[0]_0 ),
        .I5(S_SAMPLE_TIME_COUNTER0__0[27]),
        .O(p_2_in[27]));
  LUT6 #(
    .INIT(64'hFFE0FFEF1F001000)) 
    \S_SAMPLE_TIME_COUNTER[28]_i_1 
       (.I0(Q[1]),
        .I1(Q[0]),
        .I2(\S_ENABLE_reg[0] ),
        .I3(\S_SAMPLE_TIME_reg_n_0_[28] ),
        .I4(\S_ENABLE_reg[0]_0 ),
        .I5(S_SAMPLE_TIME_COUNTER0__0[28]),
        .O(p_2_in[28]));
  LUT6 #(
    .INIT(64'hFFE0FFEF1F001000)) 
    \S_SAMPLE_TIME_COUNTER[29]_i_1 
       (.I0(Q[1]),
        .I1(Q[0]),
        .I2(\S_ENABLE_reg[0] ),
        .I3(\S_SAMPLE_TIME_reg_n_0_[29] ),
        .I4(\S_ENABLE_reg[0]_0 ),
        .I5(S_SAMPLE_TIME_COUNTER0__0[29]),
        .O(p_2_in[29]));
  LUT6 #(
    .INIT(64'hFFE0FFEF1F001000)) 
    \S_SAMPLE_TIME_COUNTER[2]_i_1 
       (.I0(Q[1]),
        .I1(Q[0]),
        .I2(\S_ENABLE_reg[0] ),
        .I3(\S_SAMPLE_TIME_reg_n_0_[2] ),
        .I4(\S_ENABLE_reg[0]_0 ),
        .I5(S_SAMPLE_TIME_COUNTER0__0[2]),
        .O(p_2_in[2]));
  LUT1 #(
    .INIT(2'h1)) 
    \S_SAMPLE_TIME_COUNTER[30]_i_10 
       (.I0(S_SAMPLE_TIME_COUNTER[28]),
        .O(\S_SAMPLE_TIME_COUNTER[30]_i_10_n_0 ));
  LUT1 #(
    .INIT(2'h1)) 
    \S_SAMPLE_TIME_COUNTER[30]_i_11 
       (.I0(S_SAMPLE_TIME_COUNTER[27]),
        .O(\S_SAMPLE_TIME_COUNTER[30]_i_11_n_0 ));
  LUT1 #(
    .INIT(2'h1)) 
    \S_SAMPLE_TIME_COUNTER[30]_i_12 
       (.I0(S_SAMPLE_TIME_COUNTER[26]),
        .O(\S_SAMPLE_TIME_COUNTER[30]_i_12_n_0 ));
  LUT1 #(
    .INIT(2'h1)) 
    \S_SAMPLE_TIME_COUNTER[30]_i_13 
       (.I0(S_SAMPLE_TIME_COUNTER[25]),
        .O(\S_SAMPLE_TIME_COUNTER[30]_i_13_n_0 ));
  LUT6 #(
    .INIT(64'hFFE0FFEF1F001000)) 
    \S_SAMPLE_TIME_COUNTER[30]_i_2 
       (.I0(Q[1]),
        .I1(Q[0]),
        .I2(\S_ENABLE_reg[0] ),
        .I3(\S_SAMPLE_TIME_reg_n_0_[30] ),
        .I4(\S_ENABLE_reg[0]_0 ),
        .I5(S_SAMPLE_TIME_COUNTER0__0[30]),
        .O(p_2_in[30]));
  LUT2 #(
    .INIT(4'h2)) 
    \S_SAMPLE_TIME_COUNTER[30]_i_3 
       (.I0(nxtstate22_in),
        .I1(ENABLE),
        .O(\S_SAMPLE_TIME_COUNTER[30]_i_3_n_0 ));
  LUT3 #(
    .INIT(8'hFE)) 
    \S_SAMPLE_TIME_COUNTER[30]_i_4 
       (.I0(raw_to_si_n_133),
        .I1(\S_SAMPLE_TIME_COUNTER[30]_i_6_n_0 ),
        .I2(\S_SAMPLE_TIME_COUNTER[30]_i_7_n_0 ),
        .O(\S_SAMPLE_TIME_COUNTER[30]_i_4_n_0 ));
  LUT5 #(
    .INIT(32'hFFFFFFFE)) 
    \S_SAMPLE_TIME_COUNTER[30]_i_6 
       (.I0(S_SAMPLE_TIME_COUNTER[27]),
        .I1(S_SAMPLE_TIME_COUNTER[19]),
        .I2(S_SAMPLE_TIME_COUNTER[26]),
        .I3(S_SAMPLE_TIME_COUNTER[6]),
        .I4(raw_to_si_n_136),
        .O(\S_SAMPLE_TIME_COUNTER[30]_i_6_n_0 ));
  LUT5 #(
    .INIT(32'hFFFFFFFE)) 
    \S_SAMPLE_TIME_COUNTER[30]_i_7 
       (.I0(S_SAMPLE_TIME_COUNTER[22]),
        .I1(S_SAMPLE_TIME_COUNTER[18]),
        .I2(S_SAMPLE_TIME_COUNTER[24]),
        .I3(S_SAMPLE_TIME_COUNTER[10]),
        .I4(raw_to_si_n_135),
        .O(\S_SAMPLE_TIME_COUNTER[30]_i_7_n_0 ));
  LUT1 #(
    .INIT(2'h1)) 
    \S_SAMPLE_TIME_COUNTER[30]_i_8 
       (.I0(S_SAMPLE_TIME_COUNTER[30]),
        .O(\S_SAMPLE_TIME_COUNTER[30]_i_8_n_0 ));
  LUT1 #(
    .INIT(2'h1)) 
    \S_SAMPLE_TIME_COUNTER[30]_i_9 
       (.I0(S_SAMPLE_TIME_COUNTER[29]),
        .O(\S_SAMPLE_TIME_COUNTER[30]_i_9_n_0 ));
  LUT6 #(
    .INIT(64'hFFE0FFEF1F001000)) 
    \S_SAMPLE_TIME_COUNTER[3]_i_1 
       (.I0(Q[1]),
        .I1(Q[0]),
        .I2(\S_ENABLE_reg[0] ),
        .I3(\S_SAMPLE_TIME_reg_n_0_[3] ),
        .I4(\S_ENABLE_reg[0]_0 ),
        .I5(S_SAMPLE_TIME_COUNTER0__0[3]),
        .O(p_2_in[3]));
  LUT6 #(
    .INIT(64'hFFE0FFEF1F001000)) 
    \S_SAMPLE_TIME_COUNTER[4]_i_1 
       (.I0(Q[1]),
        .I1(Q[0]),
        .I2(\S_ENABLE_reg[0] ),
        .I3(\S_SAMPLE_TIME_reg_n_0_[4] ),
        .I4(\S_ENABLE_reg[0]_0 ),
        .I5(S_SAMPLE_TIME_COUNTER0__0[4]),
        .O(p_2_in[4]));
  LUT6 #(
    .INIT(64'hFFE0FFEF1F001000)) 
    \S_SAMPLE_TIME_COUNTER[5]_i_1 
       (.I0(Q[1]),
        .I1(Q[0]),
        .I2(\S_ENABLE_reg[0] ),
        .I3(\S_SAMPLE_TIME_reg_n_0_[5] ),
        .I4(\S_ENABLE_reg[0]_0 ),
        .I5(S_SAMPLE_TIME_COUNTER0__0[5]),
        .O(p_2_in[5]));
  LUT6 #(
    .INIT(64'hFFE0FFEF1F001000)) 
    \S_SAMPLE_TIME_COUNTER[6]_i_1 
       (.I0(Q[1]),
        .I1(Q[0]),
        .I2(\S_ENABLE_reg[0] ),
        .I3(\S_SAMPLE_TIME_reg_n_0_[6] ),
        .I4(\S_ENABLE_reg[0]_0 ),
        .I5(S_SAMPLE_TIME_COUNTER0__0[6]),
        .O(p_2_in[6]));
  LUT6 #(
    .INIT(64'hFFE0FFEF1F001000)) 
    \S_SAMPLE_TIME_COUNTER[7]_i_1 
       (.I0(Q[1]),
        .I1(Q[0]),
        .I2(\S_ENABLE_reg[0] ),
        .I3(\S_SAMPLE_TIME_reg_n_0_[7] ),
        .I4(\S_ENABLE_reg[0]_0 ),
        .I5(S_SAMPLE_TIME_COUNTER0__0[7]),
        .O(p_2_in[7]));
  LUT6 #(
    .INIT(64'hFFE0FFEF1F001000)) 
    \S_SAMPLE_TIME_COUNTER[8]_i_1 
       (.I0(Q[1]),
        .I1(Q[0]),
        .I2(\S_ENABLE_reg[0] ),
        .I3(\S_SAMPLE_TIME_reg_n_0_[8] ),
        .I4(\S_ENABLE_reg[0]_0 ),
        .I5(S_SAMPLE_TIME_COUNTER0__0[8]),
        .O(p_2_in[8]));
  LUT1 #(
    .INIT(2'h1)) 
    \S_SAMPLE_TIME_COUNTER[8]_i_10 
       (.I0(S_SAMPLE_TIME_COUNTER[1]),
        .O(\S_SAMPLE_TIME_COUNTER[8]_i_10_n_0 ));
  LUT1 #(
    .INIT(2'h1)) 
    \S_SAMPLE_TIME_COUNTER[8]_i_3 
       (.I0(S_SAMPLE_TIME_COUNTER[8]),
        .O(\S_SAMPLE_TIME_COUNTER[8]_i_3_n_0 ));
  LUT1 #(
    .INIT(2'h1)) 
    \S_SAMPLE_TIME_COUNTER[8]_i_4 
       (.I0(S_SAMPLE_TIME_COUNTER[7]),
        .O(\S_SAMPLE_TIME_COUNTER[8]_i_4_n_0 ));
  LUT1 #(
    .INIT(2'h1)) 
    \S_SAMPLE_TIME_COUNTER[8]_i_5 
       (.I0(S_SAMPLE_TIME_COUNTER[6]),
        .O(\S_SAMPLE_TIME_COUNTER[8]_i_5_n_0 ));
  LUT1 #(
    .INIT(2'h1)) 
    \S_SAMPLE_TIME_COUNTER[8]_i_6 
       (.I0(S_SAMPLE_TIME_COUNTER[5]),
        .O(\S_SAMPLE_TIME_COUNTER[8]_i_6_n_0 ));
  LUT1 #(
    .INIT(2'h1)) 
    \S_SAMPLE_TIME_COUNTER[8]_i_7 
       (.I0(S_SAMPLE_TIME_COUNTER[4]),
        .O(\S_SAMPLE_TIME_COUNTER[8]_i_7_n_0 ));
  LUT1 #(
    .INIT(2'h1)) 
    \S_SAMPLE_TIME_COUNTER[8]_i_8 
       (.I0(S_SAMPLE_TIME_COUNTER[3]),
        .O(\S_SAMPLE_TIME_COUNTER[8]_i_8_n_0 ));
  LUT1 #(
    .INIT(2'h1)) 
    \S_SAMPLE_TIME_COUNTER[8]_i_9 
       (.I0(S_SAMPLE_TIME_COUNTER[2]),
        .O(\S_SAMPLE_TIME_COUNTER[8]_i_9_n_0 ));
  LUT6 #(
    .INIT(64'hFFE0FFEF1F001000)) 
    \S_SAMPLE_TIME_COUNTER[9]_i_1 
       (.I0(Q[1]),
        .I1(Q[0]),
        .I2(\S_ENABLE_reg[0] ),
        .I3(\S_SAMPLE_TIME_reg_n_0_[9] ),
        .I4(\S_ENABLE_reg[0]_0 ),
        .I5(S_SAMPLE_TIME_COUNTER0__0[9]),
        .O(p_2_in[9]));
  FDRE \S_SAMPLE_TIME_COUNTER_reg[0] 
       (.C(s00_axi_aclk),
        .CE(spi_n_3),
        .D(p_2_in[0]),
        .Q(S_SAMPLE_TIME_COUNTER[0]),
        .R(RSTP));
  FDRE \S_SAMPLE_TIME_COUNTER_reg[10] 
       (.C(s00_axi_aclk),
        .CE(spi_n_3),
        .D(p_2_in[10]),
        .Q(S_SAMPLE_TIME_COUNTER[10]),
        .R(RSTP));
  FDRE \S_SAMPLE_TIME_COUNTER_reg[11] 
       (.C(s00_axi_aclk),
        .CE(spi_n_3),
        .D(p_2_in[11]),
        .Q(S_SAMPLE_TIME_COUNTER[11]),
        .R(RSTP));
  FDRE \S_SAMPLE_TIME_COUNTER_reg[12] 
       (.C(s00_axi_aclk),
        .CE(spi_n_3),
        .D(p_2_in[12]),
        .Q(S_SAMPLE_TIME_COUNTER[12]),
        .R(RSTP));
  FDRE \S_SAMPLE_TIME_COUNTER_reg[13] 
       (.C(s00_axi_aclk),
        .CE(spi_n_3),
        .D(p_2_in[13]),
        .Q(S_SAMPLE_TIME_COUNTER[13]),
        .R(RSTP));
  FDRE \S_SAMPLE_TIME_COUNTER_reg[14] 
       (.C(s00_axi_aclk),
        .CE(spi_n_3),
        .D(p_2_in[14]),
        .Q(S_SAMPLE_TIME_COUNTER[14]),
        .R(RSTP));
  FDRE \S_SAMPLE_TIME_COUNTER_reg[15] 
       (.C(s00_axi_aclk),
        .CE(spi_n_3),
        .D(p_2_in[15]),
        .Q(S_SAMPLE_TIME_COUNTER[15]),
        .R(RSTP));
  FDRE \S_SAMPLE_TIME_COUNTER_reg[16] 
       (.C(s00_axi_aclk),
        .CE(spi_n_3),
        .D(p_2_in[16]),
        .Q(S_SAMPLE_TIME_COUNTER[16]),
        .R(RSTP));
  (* ADDER_THRESHOLD = "35" *) 
  CARRY8 \S_SAMPLE_TIME_COUNTER_reg[16]_i_2 
       (.CI(\S_SAMPLE_TIME_COUNTER_reg[8]_i_2_n_0 ),
        .CI_TOP(1'b0),
        .CO({\S_SAMPLE_TIME_COUNTER_reg[16]_i_2_n_0 ,\S_SAMPLE_TIME_COUNTER_reg[16]_i_2_n_1 ,\S_SAMPLE_TIME_COUNTER_reg[16]_i_2_n_2 ,\S_SAMPLE_TIME_COUNTER_reg[16]_i_2_n_3 ,\S_SAMPLE_TIME_COUNTER_reg[16]_i_2_n_4 ,\S_SAMPLE_TIME_COUNTER_reg[16]_i_2_n_5 ,\S_SAMPLE_TIME_COUNTER_reg[16]_i_2_n_6 ,\S_SAMPLE_TIME_COUNTER_reg[16]_i_2_n_7 }),
        .DI(S_SAMPLE_TIME_COUNTER[16:9]),
        .O(S_SAMPLE_TIME_COUNTER0__0[16:9]),
        .S({\S_SAMPLE_TIME_COUNTER[16]_i_3_n_0 ,\S_SAMPLE_TIME_COUNTER[16]_i_4_n_0 ,\S_SAMPLE_TIME_COUNTER[16]_i_5_n_0 ,\S_SAMPLE_TIME_COUNTER[16]_i_6_n_0 ,\S_SAMPLE_TIME_COUNTER[16]_i_7_n_0 ,\S_SAMPLE_TIME_COUNTER[16]_i_8_n_0 ,\S_SAMPLE_TIME_COUNTER[16]_i_9_n_0 ,\S_SAMPLE_TIME_COUNTER[16]_i_10_n_0 }));
  FDRE \S_SAMPLE_TIME_COUNTER_reg[17] 
       (.C(s00_axi_aclk),
        .CE(spi_n_3),
        .D(p_2_in[17]),
        .Q(S_SAMPLE_TIME_COUNTER[17]),
        .R(RSTP));
  FDRE \S_SAMPLE_TIME_COUNTER_reg[18] 
       (.C(s00_axi_aclk),
        .CE(spi_n_3),
        .D(p_2_in[18]),
        .Q(S_SAMPLE_TIME_COUNTER[18]),
        .R(RSTP));
  FDRE \S_SAMPLE_TIME_COUNTER_reg[19] 
       (.C(s00_axi_aclk),
        .CE(spi_n_3),
        .D(p_2_in[19]),
        .Q(S_SAMPLE_TIME_COUNTER[19]),
        .R(RSTP));
  FDRE \S_SAMPLE_TIME_COUNTER_reg[1] 
       (.C(s00_axi_aclk),
        .CE(spi_n_3),
        .D(p_2_in[1]),
        .Q(S_SAMPLE_TIME_COUNTER[1]),
        .R(RSTP));
  FDRE \S_SAMPLE_TIME_COUNTER_reg[20] 
       (.C(s00_axi_aclk),
        .CE(spi_n_3),
        .D(p_2_in[20]),
        .Q(S_SAMPLE_TIME_COUNTER[20]),
        .R(RSTP));
  FDRE \S_SAMPLE_TIME_COUNTER_reg[21] 
       (.C(s00_axi_aclk),
        .CE(spi_n_3),
        .D(p_2_in[21]),
        .Q(S_SAMPLE_TIME_COUNTER[21]),
        .R(RSTP));
  FDRE \S_SAMPLE_TIME_COUNTER_reg[22] 
       (.C(s00_axi_aclk),
        .CE(spi_n_3),
        .D(p_2_in[22]),
        .Q(S_SAMPLE_TIME_COUNTER[22]),
        .R(RSTP));
  FDRE \S_SAMPLE_TIME_COUNTER_reg[23] 
       (.C(s00_axi_aclk),
        .CE(spi_n_3),
        .D(p_2_in[23]),
        .Q(S_SAMPLE_TIME_COUNTER[23]),
        .R(RSTP));
  FDRE \S_SAMPLE_TIME_COUNTER_reg[24] 
       (.C(s00_axi_aclk),
        .CE(spi_n_3),
        .D(p_2_in[24]),
        .Q(S_SAMPLE_TIME_COUNTER[24]),
        .R(RSTP));
  (* ADDER_THRESHOLD = "35" *) 
  CARRY8 \S_SAMPLE_TIME_COUNTER_reg[24]_i_2 
       (.CI(\S_SAMPLE_TIME_COUNTER_reg[16]_i_2_n_0 ),
        .CI_TOP(1'b0),
        .CO({\S_SAMPLE_TIME_COUNTER_reg[24]_i_2_n_0 ,\S_SAMPLE_TIME_COUNTER_reg[24]_i_2_n_1 ,\S_SAMPLE_TIME_COUNTER_reg[24]_i_2_n_2 ,\S_SAMPLE_TIME_COUNTER_reg[24]_i_2_n_3 ,\S_SAMPLE_TIME_COUNTER_reg[24]_i_2_n_4 ,\S_SAMPLE_TIME_COUNTER_reg[24]_i_2_n_5 ,\S_SAMPLE_TIME_COUNTER_reg[24]_i_2_n_6 ,\S_SAMPLE_TIME_COUNTER_reg[24]_i_2_n_7 }),
        .DI(S_SAMPLE_TIME_COUNTER[24:17]),
        .O(S_SAMPLE_TIME_COUNTER0__0[24:17]),
        .S({\S_SAMPLE_TIME_COUNTER[24]_i_3_n_0 ,\S_SAMPLE_TIME_COUNTER[24]_i_4_n_0 ,\S_SAMPLE_TIME_COUNTER[24]_i_5_n_0 ,\S_SAMPLE_TIME_COUNTER[24]_i_6_n_0 ,\S_SAMPLE_TIME_COUNTER[24]_i_7_n_0 ,\S_SAMPLE_TIME_COUNTER[24]_i_8_n_0 ,\S_SAMPLE_TIME_COUNTER[24]_i_9_n_0 ,\S_SAMPLE_TIME_COUNTER[24]_i_10_n_0 }));
  FDRE \S_SAMPLE_TIME_COUNTER_reg[25] 
       (.C(s00_axi_aclk),
        .CE(spi_n_3),
        .D(p_2_in[25]),
        .Q(S_SAMPLE_TIME_COUNTER[25]),
        .R(RSTP));
  FDRE \S_SAMPLE_TIME_COUNTER_reg[26] 
       (.C(s00_axi_aclk),
        .CE(spi_n_3),
        .D(p_2_in[26]),
        .Q(S_SAMPLE_TIME_COUNTER[26]),
        .R(RSTP));
  FDRE \S_SAMPLE_TIME_COUNTER_reg[27] 
       (.C(s00_axi_aclk),
        .CE(spi_n_3),
        .D(p_2_in[27]),
        .Q(S_SAMPLE_TIME_COUNTER[27]),
        .R(RSTP));
  FDRE \S_SAMPLE_TIME_COUNTER_reg[28] 
       (.C(s00_axi_aclk),
        .CE(spi_n_3),
        .D(p_2_in[28]),
        .Q(S_SAMPLE_TIME_COUNTER[28]),
        .R(RSTP));
  FDRE \S_SAMPLE_TIME_COUNTER_reg[29] 
       (.C(s00_axi_aclk),
        .CE(spi_n_3),
        .D(p_2_in[29]),
        .Q(S_SAMPLE_TIME_COUNTER[29]),
        .R(RSTP));
  FDRE \S_SAMPLE_TIME_COUNTER_reg[2] 
       (.C(s00_axi_aclk),
        .CE(spi_n_3),
        .D(p_2_in[2]),
        .Q(S_SAMPLE_TIME_COUNTER[2]),
        .R(RSTP));
  FDRE \S_SAMPLE_TIME_COUNTER_reg[30] 
       (.C(s00_axi_aclk),
        .CE(spi_n_3),
        .D(p_2_in[30]),
        .Q(S_SAMPLE_TIME_COUNTER[30]),
        .R(RSTP));
  (* ADDER_THRESHOLD = "35" *) 
  CARRY8 \S_SAMPLE_TIME_COUNTER_reg[30]_i_5 
       (.CI(\S_SAMPLE_TIME_COUNTER_reg[24]_i_2_n_0 ),
        .CI_TOP(1'b0),
        .CO({\NLW_S_SAMPLE_TIME_COUNTER_reg[30]_i_5_CO_UNCONNECTED [7:5],\S_SAMPLE_TIME_COUNTER_reg[30]_i_5_n_3 ,\S_SAMPLE_TIME_COUNTER_reg[30]_i_5_n_4 ,\S_SAMPLE_TIME_COUNTER_reg[30]_i_5_n_5 ,\S_SAMPLE_TIME_COUNTER_reg[30]_i_5_n_6 ,\S_SAMPLE_TIME_COUNTER_reg[30]_i_5_n_7 }),
        .DI({1'b0,1'b0,1'b0,S_SAMPLE_TIME_COUNTER[29:25]}),
        .O({\NLW_S_SAMPLE_TIME_COUNTER_reg[30]_i_5_O_UNCONNECTED [7:6],S_SAMPLE_TIME_COUNTER0__0[30:25]}),
        .S({1'b0,1'b0,\S_SAMPLE_TIME_COUNTER[30]_i_8_n_0 ,\S_SAMPLE_TIME_COUNTER[30]_i_9_n_0 ,\S_SAMPLE_TIME_COUNTER[30]_i_10_n_0 ,\S_SAMPLE_TIME_COUNTER[30]_i_11_n_0 ,\S_SAMPLE_TIME_COUNTER[30]_i_12_n_0 ,\S_SAMPLE_TIME_COUNTER[30]_i_13_n_0 }));
  FDRE \S_SAMPLE_TIME_COUNTER_reg[3] 
       (.C(s00_axi_aclk),
        .CE(spi_n_3),
        .D(p_2_in[3]),
        .Q(S_SAMPLE_TIME_COUNTER[3]),
        .R(RSTP));
  FDRE \S_SAMPLE_TIME_COUNTER_reg[4] 
       (.C(s00_axi_aclk),
        .CE(spi_n_3),
        .D(p_2_in[4]),
        .Q(S_SAMPLE_TIME_COUNTER[4]),
        .R(RSTP));
  FDRE \S_SAMPLE_TIME_COUNTER_reg[5] 
       (.C(s00_axi_aclk),
        .CE(spi_n_3),
        .D(p_2_in[5]),
        .Q(S_SAMPLE_TIME_COUNTER[5]),
        .R(RSTP));
  FDRE \S_SAMPLE_TIME_COUNTER_reg[6] 
       (.C(s00_axi_aclk),
        .CE(spi_n_3),
        .D(p_2_in[6]),
        .Q(S_SAMPLE_TIME_COUNTER[6]),
        .R(RSTP));
  FDRE \S_SAMPLE_TIME_COUNTER_reg[7] 
       (.C(s00_axi_aclk),
        .CE(spi_n_3),
        .D(p_2_in[7]),
        .Q(S_SAMPLE_TIME_COUNTER[7]),
        .R(RSTP));
  FDRE \S_SAMPLE_TIME_COUNTER_reg[8] 
       (.C(s00_axi_aclk),
        .CE(spi_n_3),
        .D(p_2_in[8]),
        .Q(S_SAMPLE_TIME_COUNTER[8]),
        .R(RSTP));
  (* ADDER_THRESHOLD = "35" *) 
  CARRY8 \S_SAMPLE_TIME_COUNTER_reg[8]_i_2 
       (.CI(S_SAMPLE_TIME_COUNTER[0]),
        .CI_TOP(1'b0),
        .CO({\S_SAMPLE_TIME_COUNTER_reg[8]_i_2_n_0 ,\S_SAMPLE_TIME_COUNTER_reg[8]_i_2_n_1 ,\S_SAMPLE_TIME_COUNTER_reg[8]_i_2_n_2 ,\S_SAMPLE_TIME_COUNTER_reg[8]_i_2_n_3 ,\S_SAMPLE_TIME_COUNTER_reg[8]_i_2_n_4 ,\S_SAMPLE_TIME_COUNTER_reg[8]_i_2_n_5 ,\S_SAMPLE_TIME_COUNTER_reg[8]_i_2_n_6 ,\S_SAMPLE_TIME_COUNTER_reg[8]_i_2_n_7 }),
        .DI(S_SAMPLE_TIME_COUNTER[8:1]),
        .O(S_SAMPLE_TIME_COUNTER0__0[8:1]),
        .S({\S_SAMPLE_TIME_COUNTER[8]_i_3_n_0 ,\S_SAMPLE_TIME_COUNTER[8]_i_4_n_0 ,\S_SAMPLE_TIME_COUNTER[8]_i_5_n_0 ,\S_SAMPLE_TIME_COUNTER[8]_i_6_n_0 ,\S_SAMPLE_TIME_COUNTER[8]_i_7_n_0 ,\S_SAMPLE_TIME_COUNTER[8]_i_8_n_0 ,\S_SAMPLE_TIME_COUNTER[8]_i_9_n_0 ,\S_SAMPLE_TIME_COUNTER[8]_i_10_n_0 }));
  FDRE \S_SAMPLE_TIME_COUNTER_reg[9] 
       (.C(s00_axi_aclk),
        .CE(spi_n_3),
        .D(p_2_in[9]),
        .Q(S_SAMPLE_TIME_COUNTER[9]),
        .R(RSTP));
  FDRE \S_SAMPLE_TIME_reg[0] 
       (.C(s00_axi_aclk),
        .CE(\S_SAMPLE_TIME_reg[30]_0 ),
        .D(\S_SAMPLE_TIME_reg[30]_1 [0]),
        .Q(\S_SAMPLE_TIME_reg_n_0_[0] ),
        .R(1'b0));
  FDRE \S_SAMPLE_TIME_reg[10] 
       (.C(s00_axi_aclk),
        .CE(\S_SAMPLE_TIME_reg[30]_0 ),
        .D(\S_SAMPLE_TIME_reg[30]_1 [10]),
        .Q(\S_SAMPLE_TIME_reg_n_0_[10] ),
        .R(1'b0));
  FDRE \S_SAMPLE_TIME_reg[11] 
       (.C(s00_axi_aclk),
        .CE(\S_SAMPLE_TIME_reg[30]_0 ),
        .D(\S_SAMPLE_TIME_reg[30]_1 [11]),
        .Q(\S_SAMPLE_TIME_reg_n_0_[11] ),
        .R(1'b0));
  FDRE \S_SAMPLE_TIME_reg[12] 
       (.C(s00_axi_aclk),
        .CE(\S_SAMPLE_TIME_reg[30]_0 ),
        .D(\S_SAMPLE_TIME_reg[30]_1 [12]),
        .Q(\S_SAMPLE_TIME_reg_n_0_[12] ),
        .R(1'b0));
  FDRE \S_SAMPLE_TIME_reg[13] 
       (.C(s00_axi_aclk),
        .CE(\S_SAMPLE_TIME_reg[30]_0 ),
        .D(\S_SAMPLE_TIME_reg[30]_1 [13]),
        .Q(\S_SAMPLE_TIME_reg_n_0_[13] ),
        .R(1'b0));
  FDRE \S_SAMPLE_TIME_reg[14] 
       (.C(s00_axi_aclk),
        .CE(\S_SAMPLE_TIME_reg[30]_0 ),
        .D(\S_SAMPLE_TIME_reg[30]_1 [14]),
        .Q(\S_SAMPLE_TIME_reg_n_0_[14] ),
        .R(1'b0));
  FDRE \S_SAMPLE_TIME_reg[15] 
       (.C(s00_axi_aclk),
        .CE(\S_SAMPLE_TIME_reg[30]_0 ),
        .D(\S_SAMPLE_TIME_reg[30]_1 [15]),
        .Q(\S_SAMPLE_TIME_reg_n_0_[15] ),
        .R(1'b0));
  FDRE \S_SAMPLE_TIME_reg[16] 
       (.C(s00_axi_aclk),
        .CE(\S_SAMPLE_TIME_reg[30]_0 ),
        .D(\S_SAMPLE_TIME_reg[30]_1 [16]),
        .Q(\S_SAMPLE_TIME_reg_n_0_[16] ),
        .R(1'b0));
  FDRE \S_SAMPLE_TIME_reg[17] 
       (.C(s00_axi_aclk),
        .CE(\S_SAMPLE_TIME_reg[30]_0 ),
        .D(\S_SAMPLE_TIME_reg[30]_1 [17]),
        .Q(\S_SAMPLE_TIME_reg_n_0_[17] ),
        .R(1'b0));
  FDRE \S_SAMPLE_TIME_reg[18] 
       (.C(s00_axi_aclk),
        .CE(\S_SAMPLE_TIME_reg[30]_0 ),
        .D(\S_SAMPLE_TIME_reg[30]_1 [18]),
        .Q(\S_SAMPLE_TIME_reg_n_0_[18] ),
        .R(1'b0));
  FDRE \S_SAMPLE_TIME_reg[19] 
       (.C(s00_axi_aclk),
        .CE(\S_SAMPLE_TIME_reg[30]_0 ),
        .D(\S_SAMPLE_TIME_reg[30]_1 [19]),
        .Q(\S_SAMPLE_TIME_reg_n_0_[19] ),
        .R(1'b0));
  FDRE \S_SAMPLE_TIME_reg[1] 
       (.C(s00_axi_aclk),
        .CE(\S_SAMPLE_TIME_reg[30]_0 ),
        .D(\S_SAMPLE_TIME_reg[30]_1 [1]),
        .Q(\S_SAMPLE_TIME_reg_n_0_[1] ),
        .R(1'b0));
  FDRE \S_SAMPLE_TIME_reg[20] 
       (.C(s00_axi_aclk),
        .CE(\S_SAMPLE_TIME_reg[30]_0 ),
        .D(\S_SAMPLE_TIME_reg[30]_1 [20]),
        .Q(\S_SAMPLE_TIME_reg_n_0_[20] ),
        .R(1'b0));
  FDRE \S_SAMPLE_TIME_reg[21] 
       (.C(s00_axi_aclk),
        .CE(\S_SAMPLE_TIME_reg[30]_0 ),
        .D(\S_SAMPLE_TIME_reg[30]_1 [21]),
        .Q(\S_SAMPLE_TIME_reg_n_0_[21] ),
        .R(1'b0));
  FDRE \S_SAMPLE_TIME_reg[22] 
       (.C(s00_axi_aclk),
        .CE(\S_SAMPLE_TIME_reg[30]_0 ),
        .D(\S_SAMPLE_TIME_reg[30]_1 [22]),
        .Q(\S_SAMPLE_TIME_reg_n_0_[22] ),
        .R(1'b0));
  FDRE \S_SAMPLE_TIME_reg[23] 
       (.C(s00_axi_aclk),
        .CE(\S_SAMPLE_TIME_reg[30]_0 ),
        .D(\S_SAMPLE_TIME_reg[30]_1 [23]),
        .Q(\S_SAMPLE_TIME_reg_n_0_[23] ),
        .R(1'b0));
  FDRE \S_SAMPLE_TIME_reg[24] 
       (.C(s00_axi_aclk),
        .CE(\S_SAMPLE_TIME_reg[30]_0 ),
        .D(\S_SAMPLE_TIME_reg[30]_1 [24]),
        .Q(\S_SAMPLE_TIME_reg_n_0_[24] ),
        .R(1'b0));
  FDRE \S_SAMPLE_TIME_reg[25] 
       (.C(s00_axi_aclk),
        .CE(\S_SAMPLE_TIME_reg[30]_0 ),
        .D(\S_SAMPLE_TIME_reg[30]_1 [25]),
        .Q(\S_SAMPLE_TIME_reg_n_0_[25] ),
        .R(1'b0));
  FDRE \S_SAMPLE_TIME_reg[26] 
       (.C(s00_axi_aclk),
        .CE(\S_SAMPLE_TIME_reg[30]_0 ),
        .D(\S_SAMPLE_TIME_reg[30]_1 [26]),
        .Q(\S_SAMPLE_TIME_reg_n_0_[26] ),
        .R(1'b0));
  FDRE \S_SAMPLE_TIME_reg[27] 
       (.C(s00_axi_aclk),
        .CE(\S_SAMPLE_TIME_reg[30]_0 ),
        .D(\S_SAMPLE_TIME_reg[30]_1 [27]),
        .Q(\S_SAMPLE_TIME_reg_n_0_[27] ),
        .R(1'b0));
  FDRE \S_SAMPLE_TIME_reg[28] 
       (.C(s00_axi_aclk),
        .CE(\S_SAMPLE_TIME_reg[30]_0 ),
        .D(\S_SAMPLE_TIME_reg[30]_1 [28]),
        .Q(\S_SAMPLE_TIME_reg_n_0_[28] ),
        .R(1'b0));
  FDRE \S_SAMPLE_TIME_reg[29] 
       (.C(s00_axi_aclk),
        .CE(\S_SAMPLE_TIME_reg[30]_0 ),
        .D(\S_SAMPLE_TIME_reg[30]_1 [29]),
        .Q(\S_SAMPLE_TIME_reg_n_0_[29] ),
        .R(1'b0));
  FDRE \S_SAMPLE_TIME_reg[2] 
       (.C(s00_axi_aclk),
        .CE(\S_SAMPLE_TIME_reg[30]_0 ),
        .D(\S_SAMPLE_TIME_reg[30]_1 [2]),
        .Q(\S_SAMPLE_TIME_reg_n_0_[2] ),
        .R(1'b0));
  FDRE \S_SAMPLE_TIME_reg[30] 
       (.C(s00_axi_aclk),
        .CE(\S_SAMPLE_TIME_reg[30]_0 ),
        .D(\S_SAMPLE_TIME_reg[30]_1 [30]),
        .Q(\S_SAMPLE_TIME_reg_n_0_[30] ),
        .R(1'b0));
  FDRE \S_SAMPLE_TIME_reg[3] 
       (.C(s00_axi_aclk),
        .CE(\S_SAMPLE_TIME_reg[30]_0 ),
        .D(\S_SAMPLE_TIME_reg[30]_1 [3]),
        .Q(\S_SAMPLE_TIME_reg_n_0_[3] ),
        .R(1'b0));
  FDRE \S_SAMPLE_TIME_reg[4] 
       (.C(s00_axi_aclk),
        .CE(\S_SAMPLE_TIME_reg[30]_0 ),
        .D(\S_SAMPLE_TIME_reg[30]_1 [4]),
        .Q(\S_SAMPLE_TIME_reg_n_0_[4] ),
        .R(1'b0));
  FDRE \S_SAMPLE_TIME_reg[5] 
       (.C(s00_axi_aclk),
        .CE(\S_SAMPLE_TIME_reg[30]_0 ),
        .D(\S_SAMPLE_TIME_reg[30]_1 [5]),
        .Q(\S_SAMPLE_TIME_reg_n_0_[5] ),
        .R(1'b0));
  FDRE \S_SAMPLE_TIME_reg[6] 
       (.C(s00_axi_aclk),
        .CE(\S_SAMPLE_TIME_reg[30]_0 ),
        .D(\S_SAMPLE_TIME_reg[30]_1 [6]),
        .Q(\S_SAMPLE_TIME_reg_n_0_[6] ),
        .R(1'b0));
  FDRE \S_SAMPLE_TIME_reg[7] 
       (.C(s00_axi_aclk),
        .CE(\S_SAMPLE_TIME_reg[30]_0 ),
        .D(\S_SAMPLE_TIME_reg[30]_1 [7]),
        .Q(\S_SAMPLE_TIME_reg_n_0_[7] ),
        .R(1'b0));
  FDRE \S_SAMPLE_TIME_reg[8] 
       (.C(s00_axi_aclk),
        .CE(\S_SAMPLE_TIME_reg[30]_0 ),
        .D(\S_SAMPLE_TIME_reg[30]_1 [8]),
        .Q(\S_SAMPLE_TIME_reg_n_0_[8] ),
        .R(1'b0));
  FDRE \S_SAMPLE_TIME_reg[9] 
       (.C(s00_axi_aclk),
        .CE(\S_SAMPLE_TIME_reg[30]_0 ),
        .D(\S_SAMPLE_TIME_reg[30]_1 [9]),
        .Q(\S_SAMPLE_TIME_reg_n_0_[9] ),
        .R(1'b0));
  LUT2 #(
    .INIT(4'h2)) 
    \S_SPI_BUSY_PIPE[1]_i_1 
       (.I0(\S_ENABLE_reg[0]_0 ),
        .I1(\S_ENABLE_reg[0] ),
        .O(E));
  (* SOFT_HLUTNM = "soft_lutpair86" *) 
  LUT3 #(
    .INIT(8'h8A)) 
    \S_SPI_BUSY_PIPE[1]_i_2 
       (.I0(S_SPI_BUSY_PIPE[0]),
        .I1(Q[1]),
        .I2(Q[0]),
        .O(\S_SPI_BUSY_PIPE[1]_i_2_n_0 ));
  FDRE \S_SPI_BUSY_PIPE_reg[0] 
       (.C(s00_axi_aclk),
        .CE(E),
        .D(spi_n_4),
        .Q(S_SPI_BUSY_PIPE[0]),
        .R(RSTP));
  FDRE \S_SPI_BUSY_PIPE_reg[1] 
       (.C(s00_axi_aclk),
        .CE(E),
        .D(\S_SPI_BUSY_PIPE[1]_i_2_n_0 ),
        .Q(S_SPI_BUSY_PIPE[1]),
        .R(RSTP));
  FDRE S_SPI_ENABLE_reg
       (.C(s00_axi_aclk),
        .CE(1'b1),
        .D(S_SPI_ENABLE_reg_1),
        .Q(S_SPI_ENABLE_reg_0),
        .R(RSTP));
  LUT1 #(
    .INIT(2'h1)) 
    \curstate[0]_i_1__0 
       (.I0(\S_ENABLE_reg[0]_0 ),
        .O(nxtstate[0]));
  (* SOFT_HLUTNM = "soft_lutpair87" *) 
  LUT1 #(
    .INIT(2'h1)) 
    \curstate[1]_i_1 
       (.I0(\S_ENABLE_reg[0] ),
        .O(nxtstate[1]));
  (* FSM_ENCODING = "auto" *) 
  (* FSM_SAFE_STATE = "power_on_state" *) 
  FDRE #(
    .INIT(1'b0)) 
    \curstate_reg[0] 
       (.C(s00_axi_aclk),
        .CE(1'b1),
        .D(nxtstate[0]),
        .Q(Q[0]),
        .R(RSTP));
  (* FSM_ENCODING = "auto" *) 
  (* FSM_SAFE_STATE = "power_on_state" *) 
  FDRE #(
    .INIT(1'b0)) 
    \curstate_reg[1] 
       (.C(s00_axi_aclk),
        .CE(1'b1),
        .D(nxtstate[1]),
        .Q(Q[1]),
        .R(RSTP));
  zusys_A3_ADC_LTC2311_0_MULT_ADD raw_to_si
       (.CEP(S_CE_CONVERSION),
        .CO(nxtstate22_in),
        .DSP_ALU_INST({\S_OFFSET_S_C_reg_n_0_[15] ,\S_OFFSET_S_C_reg_n_0_[14] ,\S_OFFSET_S_C_reg_n_0_[13] ,\S_OFFSET_S_C_reg_n_0_[12] ,\S_OFFSET_S_C_reg_n_0_[11] ,\S_OFFSET_S_C_reg_n_0_[10] ,\S_OFFSET_S_C_reg_n_0_[9] ,\S_OFFSET_S_C_reg_n_0_[8] ,\S_OFFSET_S_C_reg_n_0_[7] ,\S_OFFSET_S_C_reg_n_0_[6] ,\S_OFFSET_S_C_reg_n_0_[5] ,\S_OFFSET_S_C_reg_n_0_[4] ,\S_OFFSET_S_C_reg_n_0_[3] ,\S_OFFSET_S_C_reg_n_0_[2] ,\S_OFFSET_S_C_reg_n_0_[1] ,\S_OFFSET_S_C_reg_n_0_[0] }),
        .DSP_A_B_DATA_INST(S_CONV_COUNTER),
        .DSP_A_B_DATA_INST_0({data8,data7,data6,data5,data4,data3,data2,\S_CONVERSION_reg_n_0_[17] ,\S_CONVERSION_reg_n_0_[16] ,\S_CONVERSION_reg_n_0_[15] ,\S_CONVERSION_reg_n_0_[14] ,\S_CONVERSION_reg_n_0_[13] ,\S_CONVERSION_reg_n_0_[12] ,\S_CONVERSION_reg_n_0_[11] ,\S_CONVERSION_reg_n_0_[10] ,\S_CONVERSION_reg_n_0_[9] ,\S_CONVERSION_reg_n_0_[8] ,\S_CONVERSION_reg_n_0_[7] ,\S_CONVERSION_reg_n_0_[6] ,\S_CONVERSION_reg_n_0_[5] ,\S_CONVERSION_reg_n_0_[4] ,\S_CONVERSION_reg_n_0_[3] ,\S_CONVERSION_reg_n_0_[2] ,\S_CONVERSION_reg_n_0_[1] ,\S_CONVERSION_reg_n_0_[0] }),
        .ENABLE(ENABLE),
        .P(S_RESULT_S_C),
        .Q(S_RAW_VALUE_S_C),
        .RSTP(RSTP),
        .S(S),
        .SI_VALID_reg(Q),
        .SI_VALID_reg_0(S_SPI_BUSY_PIPE),
        .SI_VALID_reg_i_3_0(\S_SAMPLE_COUNTER_reg[16]_0 ),
        .SI_VALID_reg_i_3_1(\S_SAMPLE_COUNTER_reg[24]_0 ),
        .SI_VALID_reg_i_3_2(\S_SAMPLE_COUNTER_reg[31]_0 ),
        .SI_VALID_reg_i_3_3(SI_VALID_reg_i_49_n_1),
        .SI_VALID_reg_i_8_0(\S_SAMPLES_reg_n_0_[0] ),
        .SI_VALID_reg_i_8_1(\S_SAMPLE_COUNTER_reg[0]_0 ),
        .SI_VALUE0({SI_VALUE0[279:277],SI_VALUE0[256:255],SI_VALUE0[244:225],SI_VALUE0[222:213],SI_VALUE0[211:209],SI_VALUE0[192:191],SI_VALUE0[148:143],SI_VALUE0[139:105],SI_VALUE0[78:76],SI_VALUE0[43:0]}),
        .\SI_VALUE_reg[115] (\SI_VALUE[180]_i_3_n_0 ),
        .\SI_VALUE_reg[206] (\SI_VALUE[270]_i_3_n_0 ),
        .\SI_VALUE_reg[209] (\S_RESULT_COUNTER_reg[0]_rep_n_0 ),
        .\SI_VALUE_reg[209]_0 (\S_RESULT_COUNTER_reg[1]_rep_n_0 ),
        .\SI_VALUE_reg[273] (\SI_VALUE[273]_i_2_n_0 ),
        .\SI_VALUE_reg[273]_0 (\SI_VALUE[273]_i_4_n_0 ),
        .\SI_VALUE_reg[279] (\SI_VALUE[279]_i_7_n_0 ),
        .\SI_VALUE_reg[34] (S_RESULT_COUNTER),
        .\S_CONV_COUNTER_reg[0] (raw_to_si_n_137),
        .S_DUMMY_SAMPLE(S_DUMMY_SAMPLE),
        .\S_ENABLE_reg[0] (\S_ENABLE_reg[0] ),
        .\S_ENABLE_reg[0]_0 (\S_ENABLE_reg[0]_0 ),
        .\S_RESULT_COUNTER_reg[0]_rep (raw_to_si_n_1),
        .\S_SAMPLE_TIME_COUNTER[30]_i_7 (S_SAMPLE_TIME_COUNTER),
        .\S_SAMPLE_TIME_COUNTER_reg[11] (raw_to_si_n_133),
        .\S_SAMPLE_TIME_COUNTER_reg[17] (raw_to_si_n_136),
        .\S_SAMPLE_TIME_COUNTER_reg[23] (raw_to_si_n_135),
        .\curstate_reg[0] (raw_to_si_n_134),
        .nxtstate3(nxtstate3),
        .s00_axi_aclk(s00_axi_aclk));
  zusys_A3_ADC_LTC2311_0_SPI_MASTER spi
       (.CPHA(CPHA),
        .CPOL(CPOL),
        .D(spi_n_4),
        .E(spi_n_3),
        .Q(Q),
        .RAW_VALUE(RAW_VALUE),
        .RSTP(RSTP),
        .SCLK_IN(SCLK_IN),
        .SS_IN_N(SS_IN_N),
        .SS_N(SS_N),
        .S_AXI_ARESETN(S_AXI_ARESETN),
        .\S_BIT_COUNT_reg[0]_0 (S_SPI_ENABLE_reg_0),
        .S_CPOL_reg_0(S_CPOL_reg),
        .\S_DEL_COUNT_reg[7]_0 (\S_DEL_COUNT_reg[7] ),
        .\S_RAW_VALUE_S_C_reg[0] (\S_RAW_VALUE_S_C[15]_i_3_n_0 ),
        .\S_RAW_VALUE_S_C_reg[0]_0 (S_CHANNEL_COUNTER),
        .\S_RX_BUFFER_reg[112]_0 (D),
        .\S_RX_OUT_BUFFER_reg[127]_0 ({spi_n_5,spi_n_6,spi_n_7,spi_n_8,spi_n_9,spi_n_10,spi_n_11,spi_n_12,spi_n_13,spi_n_14,spi_n_15,spi_n_16,spi_n_17,spi_n_18,spi_n_19,spi_n_20}),
        .\S_SAMPLE_TIME_COUNTER_reg[0] (\S_SAMPLE_TIME_COUNTER[30]_i_3_n_0 ),
        .\S_SAMPLE_TIME_COUNTER_reg[0]_0 (\S_SAMPLE_TIME_COUNTER[30]_i_4_n_0 ),
        .\S_SAMPLE_TIME_COUNTER_reg[0]_1 (\S_ENABLE_reg[0]_0 ),
        .S_SCLK(S_SCLK),
        .S_SCLK_reg_0(S_MANUAL_reg_0),
        .S_SPI_BUSY(S_SPI_BUSY),
        .s00_axi_aclk(s00_axi_aclk),
        .s00_axi_aresetn(s00_axi_aresetn));
endmodule

(* ORIG_REF_NAME = "ADC_LTC2311_v3_0" *) 
module zusys_A3_ADC_LTC2311_0_ADC_LTC2311_v3_0
   (\S_SAMPLE_COUNTER_reg[0] ,
    s00_axi_awready,
    s00_axi_wready,
    s00_axi_arready,
    RAW_VALID,
    SI_VALID,
    s00_axi_rdata,
    RAW_VALUE,
    SS_N,
    SAMPLE_COUNTER,
    SI_VALUE,
    SCLK_DIFF,
    s00_axi_rvalid,
    s00_axi_bvalid,
    s00_axi_aresetn,
    s00_axi_aclk,
    s00_axi_awaddr,
    s00_axi_wdata,
    s00_axi_araddr,
    MISO_DIFF,
    TRIGGER_CNV,
    s00_axi_wvalid,
    s00_axi_awvalid,
    s00_axi_wstrb,
    s00_axi_arvalid,
    s00_axi_bready,
    s00_axi_rready);
  output \S_SAMPLE_COUNTER_reg[0] ;
  output s00_axi_awready;
  output s00_axi_wready;
  output s00_axi_arready;
  output [0:0]RAW_VALID;
  output [0:0]SI_VALID;
  output [31:0]s00_axi_rdata;
  output [127:0]RAW_VALUE;
  output [0:0]SS_N;
  output [30:0]SAMPLE_COUNTER;
  output [279:0]SI_VALUE;
  output [1:0]SCLK_DIFF;
  output s00_axi_rvalid;
  output s00_axi_bvalid;
  input s00_axi_aresetn;
  input s00_axi_aclk;
  input [3:0]s00_axi_awaddr;
  input [31:0]s00_axi_wdata;
  input [3:0]s00_axi_araddr;
  input [15:0]MISO_DIFF;
  input [0:0]TRIGGER_CNV;
  input s00_axi_wvalid;
  input s00_axi_awvalid;
  input [3:0]s00_axi_wstrb;
  input s00_axi_arvalid;
  input s00_axi_bready;
  input s00_axi_rready;

  wire ADC_LTC2311_v3_0_S00_AXI_inst_n_10;
  wire ADC_LTC2311_v3_0_S00_AXI_inst_n_11;
  wire ADC_LTC2311_v3_0_S00_AXI_inst_n_12;
  wire ADC_LTC2311_v3_0_S00_AXI_inst_n_13;
  wire ADC_LTC2311_v3_0_S00_AXI_inst_n_130;
  wire ADC_LTC2311_v3_0_S00_AXI_inst_n_131;
  wire ADC_LTC2311_v3_0_S00_AXI_inst_n_134;
  wire ADC_LTC2311_v3_0_S00_AXI_inst_n_135;
  wire ADC_LTC2311_v3_0_S00_AXI_inst_n_14;
  wire ADC_LTC2311_v3_0_S00_AXI_inst_n_15;
  wire ADC_LTC2311_v3_0_S00_AXI_inst_n_16;
  wire ADC_LTC2311_v3_0_S00_AXI_inst_n_17;
  wire ADC_LTC2311_v3_0_S00_AXI_inst_n_18;
  wire ADC_LTC2311_v3_0_S00_AXI_inst_n_19;
  wire ADC_LTC2311_v3_0_S00_AXI_inst_n_20;
  wire ADC_LTC2311_v3_0_S00_AXI_inst_n_21;
  wire ADC_LTC2311_v3_0_S00_AXI_inst_n_22;
  wire ADC_LTC2311_v3_0_S00_AXI_inst_n_23;
  wire ADC_LTC2311_v3_0_S00_AXI_inst_n_24;
  wire ADC_LTC2311_v3_0_S00_AXI_inst_n_25;
  wire ADC_LTC2311_v3_0_S00_AXI_inst_n_26;
  wire ADC_LTC2311_v3_0_S00_AXI_inst_n_29;
  wire ADC_LTC2311_v3_0_S00_AXI_inst_n_30;
  wire ADC_LTC2311_v3_0_S00_AXI_inst_n_32;
  wire ADC_LTC2311_v3_0_S00_AXI_inst_n_33;
  wire ADC_LTC2311_v3_0_S00_AXI_inst_n_51;
  wire ADC_LTC2311_v3_0_S00_AXI_inst_n_52;
  wire ADC_LTC2311_v3_0_S00_AXI_inst_n_53;
  wire ADC_LTC2311_v3_0_S00_AXI_inst_n_54;
  wire ADC_LTC2311_v3_0_S00_AXI_inst_n_55;
  wire ADC_LTC2311_v3_0_S00_AXI_inst_n_56;
  wire ADC_LTC2311_v3_0_S00_AXI_inst_n_57;
  wire ADC_LTC2311_v3_0_S00_AXI_inst_n_58;
  wire ADC_LTC2311_v3_0_S00_AXI_inst_n_59;
  wire ADC_LTC2311_v3_0_S00_AXI_inst_n_60;
  wire ADC_LTC2311_v3_0_S00_AXI_inst_n_61;
  wire ADC_LTC2311_v3_0_S00_AXI_inst_n_62;
  wire ADC_LTC2311_v3_0_S00_AXI_inst_n_63;
  wire ADC_LTC2311_v3_0_S00_AXI_inst_n_64;
  wire ADC_LTC2311_v3_0_S00_AXI_inst_n_65;
  wire ADC_LTC2311_v3_0_S00_AXI_inst_n_66;
  wire ADC_LTC2311_v3_0_S00_AXI_inst_n_7;
  wire BUSY;
  wire BUSY_i_1__0_n_0;
  wire CPHA;
  wire CPOL;
  wire ENABLE;
  wire \GEN_ADC_CONT[0].inst_adc_n_10 ;
  wire \GEN_ADC_CONT[0].inst_adc_n_14 ;
  wire \GEN_ADC_CONT[0].inst_adc_n_15 ;
  wire \GEN_ADC_CONT[0].inst_adc_n_4 ;
  wire \GEN_ADC_CONT[0].inst_adc_n_8 ;
  wire \GEN_ADC_CONT[0].inst_adc_n_9 ;
  wire MANUAL;
  wire [15:0]MISO_DIFF;
  wire [7:0]POST_DELAY;
  wire [7:0]PRE_DELAY;
  wire [4:2]P_ADC_CR_IN;
  wire [0:0]RAW_VALID;
  wire RAW_VALID_i_1_n_0;
  wire [127:0]RAW_VALUE;
  wire [30:0]SAMPLE_COUNTER;
  wire [1:0]SCLK_DIFF;
  wire SCLK_IN;
  wire SET_CONVERSION;
  wire SET_OFFSET;
  wire SET_SAMPLES;
  wire SET_SAMPLE_TIME;
  wire [0:0]SI_VALID;
  wire [279:0]SI_VALUE;
  wire SS_IN_N;
  wire [0:0]SS_N;
  wire [30:0]S_ADC_CONV_VALUE;
  wire [3:3]S_ADC_CR;
  wire \S_ADC_SPI_CR_IN[5]_i_1_n_0 ;
  wire \S_ADC_SPI_CR_IN_reg_n_0_[1] ;
  wire \S_ADC_SPI_CR_IN_reg_n_0_[3] ;
  wire \S_ADC_SPI_CR_IN_reg_n_0_[5] ;
  wire S_AXI_ARESETN;
  wire S_DUMMY_SAMPLE;
  wire S_DUMMY_SAMPLE_i_1_n_0;
  wire S_MANUAL_i_1_n_0;
  wire [7:0]S_MISO;
  wire \S_SAMPLE_COUNTER_reg[0] ;
  wire S_SAMPLE_TIME;
  wire S_SCLK;
  wire S_SCLK_IN;
  wire S_SET_CONVERSION;
  wire S_SPI_BUSY;
  wire S_SPI_ENABLE_i_1_n_0;
  wire S_SS_IN_N;
  wire S_TRIGGER_CNV_PIPE;
  wire [0:0]TRIGGER_CNV;
  wire [1:0]curstate;
  wire [1:0]curstate_0;
  wire [1:0]nxtstate;
  wire \raw_to_si/RSTD ;
  wire s00_axi_aclk;
  wire [3:0]s00_axi_araddr;
  wire s00_axi_aresetn;
  wire s00_axi_arready;
  wire s00_axi_arvalid;
  wire [3:0]s00_axi_awaddr;
  wire s00_axi_awready;
  wire s00_axi_awvalid;
  wire s00_axi_bready;
  wire s00_axi_bvalid;
  wire [31:0]s00_axi_rdata;
  wire s00_axi_rready;
  wire s00_axi_rvalid;
  wire [31:0]s00_axi_wdata;
  wire s00_axi_wready;
  wire [3:0]s00_axi_wstrb;
  wire s00_axi_wvalid;

  zusys_A3_ADC_LTC2311_0_ADC_LTC2311_v3_0_S00_AXI ADC_LTC2311_v3_0_S00_AXI_inst
       (.\ADC_CHANNEL_reg[7]_0 ({ADC_LTC2311_v3_0_S00_AXI_inst_n_18,ADC_LTC2311_v3_0_S00_AXI_inst_n_19,ADC_LTC2311_v3_0_S00_AXI_inst_n_20,ADC_LTC2311_v3_0_S00_AXI_inst_n_21,ADC_LTC2311_v3_0_S00_AXI_inst_n_22,ADC_LTC2311_v3_0_S00_AXI_inst_n_23,ADC_LTC2311_v3_0_S00_AXI_inst_n_24,ADC_LTC2311_v3_0_S00_AXI_inst_n_25}),
        .\ADC_CONV_VALUE_reg[30]_0 (S_ADC_CONV_VALUE),
        .\ADC_CR_reg[2]_0 (ADC_LTC2311_v3_0_S00_AXI_inst_n_30),
        .\ADC_CR_reg[3]_0 (S_ADC_CR),
        .\ADC_CR_reg[3]_1 (ADC_LTC2311_v3_0_S00_AXI_inst_n_7),
        .\ADC_CR_reg[3]_2 (ADC_LTC2311_v3_0_S00_AXI_inst_n_131),
        .\ADC_CR_reg[6]_0 (ADC_LTC2311_v3_0_S00_AXI_inst_n_135),
        .\ADC_MASTER_CHANNEL_reg[0]_0 (ADC_LTC2311_v3_0_S00_AXI_inst_n_29),
        .\ADC_MASTER_CHANNEL_reg[0]_1 (ADC_LTC2311_v3_0_S00_AXI_inst_n_134),
        .\ADC_SPI_CR_reg[3]_0 ({\S_ADC_SPI_CR_IN_reg_n_0_[3] ,\S_ADC_SPI_CR_IN_reg_n_0_[1] }),
        .\ADC_SPI_CR_reg[5]_0 (\S_ADC_SPI_CR_IN_reg_n_0_[5] ),
        .BUSY(BUSY),
        .CPHA(CPHA),
        .CPOL(CPOL),
        .D({ADC_LTC2311_v3_0_S00_AXI_inst_n_32,ADC_LTC2311_v3_0_S00_AXI_inst_n_33}),
        .E(S_SAMPLE_TIME),
        .ENABLE(ENABLE),
        .P_ADC_CR_IN({P_ADC_CR_IN[4],P_ADC_CR_IN[2]}),
        .Q({POST_DELAY,PRE_DELAY,ADC_LTC2311_v3_0_S00_AXI_inst_n_51,ADC_LTC2311_v3_0_S00_AXI_inst_n_52,ADC_LTC2311_v3_0_S00_AXI_inst_n_53,ADC_LTC2311_v3_0_S00_AXI_inst_n_54,ADC_LTC2311_v3_0_S00_AXI_inst_n_55,ADC_LTC2311_v3_0_S00_AXI_inst_n_56,ADC_LTC2311_v3_0_S00_AXI_inst_n_57,ADC_LTC2311_v3_0_S00_AXI_inst_n_58,ADC_LTC2311_v3_0_S00_AXI_inst_n_59,ADC_LTC2311_v3_0_S00_AXI_inst_n_60,ADC_LTC2311_v3_0_S00_AXI_inst_n_61,ADC_LTC2311_v3_0_S00_AXI_inst_n_62,ADC_LTC2311_v3_0_S00_AXI_inst_n_63,ADC_LTC2311_v3_0_S00_AXI_inst_n_64,ADC_LTC2311_v3_0_S00_AXI_inst_n_65,ADC_LTC2311_v3_0_S00_AXI_inst_n_66}),
        .RAW_VALID(RAW_VALID),
        .RSTP(\raw_to_si/RSTD ),
        .SET_CONVERSION(SET_CONVERSION),
        .SET_OFFSET(SET_OFFSET),
        .SET_SAMPLES(SET_SAMPLES),
        .SET_SAMPLE_TIME(SET_SAMPLE_TIME),
        .SI_VALID(SI_VALID),
        .S_AXI_ARESETN(S_AXI_ARESETN),
        .\S_ENABLE_reg[0] (ADC_LTC2311_v3_0_S00_AXI_inst_n_26),
        .S_SCLK_IN(S_SCLK_IN),
        .S_SET_CONVERSION(S_SET_CONVERSION),
        .\S_SET_CONVERSION_reg[0] ({ADC_LTC2311_v3_0_S00_AXI_inst_n_10,ADC_LTC2311_v3_0_S00_AXI_inst_n_11,ADC_LTC2311_v3_0_S00_AXI_inst_n_12,ADC_LTC2311_v3_0_S00_AXI_inst_n_13,ADC_LTC2311_v3_0_S00_AXI_inst_n_14,ADC_LTC2311_v3_0_S00_AXI_inst_n_15,ADC_LTC2311_v3_0_S00_AXI_inst_n_16,ADC_LTC2311_v3_0_S00_AXI_inst_n_17}),
        .\S_SET_SAMPLES_reg[0] (ADC_LTC2311_v3_0_S00_AXI_inst_n_130),
        .S_SS_IN_N(S_SS_IN_N),
        .S_TRIGGER_CNV_PIPE(S_TRIGGER_CNV_PIPE),
        .TRIGGER_CNV(TRIGGER_CNV),
        .axi_arready_reg_0(s00_axi_arready),
        .axi_awready_reg_0(s00_axi_awready),
        .axi_wready_reg_0(s00_axi_wready),
        .\curstate_reg[0] (curstate),
        .nxtstate(nxtstate),
        .s00_axi_aclk(s00_axi_aclk),
        .s00_axi_araddr(s00_axi_araddr),
        .s00_axi_aresetn(s00_axi_aresetn),
        .s00_axi_arvalid(s00_axi_arvalid),
        .s00_axi_awaddr(s00_axi_awaddr),
        .s00_axi_awvalid(s00_axi_awvalid),
        .s00_axi_bready(s00_axi_bready),
        .s00_axi_bvalid(s00_axi_bvalid),
        .s00_axi_rdata(s00_axi_rdata),
        .s00_axi_rready(s00_axi_rready),
        .s00_axi_rvalid(s00_axi_rvalid),
        .s00_axi_wdata(s00_axi_wdata),
        .s00_axi_wstrb(s00_axi_wstrb),
        .s00_axi_wvalid(s00_axi_wvalid));
  LUT5 #(
    .INIT(32'hF7FF0002)) 
    BUSY_i_1__0
       (.I0(\GEN_ADC_CONT[0].inst_adc_n_4 ),
        .I1(curstate_0[0]),
        .I2(curstate_0[1]),
        .I3(\GEN_ADC_CONT[0].inst_adc_n_10 ),
        .I4(BUSY),
        .O(BUSY_i_1__0_n_0));
  zusys_A3_ADC_LTC2311_0_ADC_CONTROLLER \GEN_ADC_CONT[0].inst_adc 
       (.BUSY(BUSY),
        .BUSY_reg_0(BUSY_i_1__0_n_0),
        .CPHA(CPHA),
        .CPOL(CPOL),
        .D(S_MISO),
        .E(\GEN_ADC_CONT[0].inst_adc_n_15 ),
        .ENABLE(ENABLE),
        .Q(curstate_0),
        .RAW_VALID(RAW_VALID),
        .RAW_VALID_reg_0(RAW_VALID_i_1_n_0),
        .RAW_VALUE(RAW_VALUE),
        .RSTP(\raw_to_si/RSTD ),
        .S(SAMPLE_COUNTER[7:0]),
        .SCLK_IN(SCLK_IN),
        .SET_CONVERSION(SET_CONVERSION),
        .SET_OFFSET(SET_OFFSET),
        .SET_SAMPLES(SET_SAMPLES),
        .SI_VALID(SI_VALID),
        .SI_VALUE(SI_VALUE),
        .SS_IN_N(SS_IN_N),
        .SS_N(SS_N),
        .S_AXI_ARESETN(S_AXI_ARESETN),
        .\S_CONVERSION_reg[126]_0 ({ADC_LTC2311_v3_0_S00_AXI_inst_n_10,ADC_LTC2311_v3_0_S00_AXI_inst_n_11,ADC_LTC2311_v3_0_S00_AXI_inst_n_12,ADC_LTC2311_v3_0_S00_AXI_inst_n_13,ADC_LTC2311_v3_0_S00_AXI_inst_n_14,ADC_LTC2311_v3_0_S00_AXI_inst_n_15,ADC_LTC2311_v3_0_S00_AXI_inst_n_16,ADC_LTC2311_v3_0_S00_AXI_inst_n_17}),
        .S_CPOL_reg(S_ADC_CR),
        .\S_DEL_COUNT_reg[7] ({POST_DELAY,PRE_DELAY,ADC_LTC2311_v3_0_S00_AXI_inst_n_51,ADC_LTC2311_v3_0_S00_AXI_inst_n_52,ADC_LTC2311_v3_0_S00_AXI_inst_n_53,ADC_LTC2311_v3_0_S00_AXI_inst_n_54,ADC_LTC2311_v3_0_S00_AXI_inst_n_55,ADC_LTC2311_v3_0_S00_AXI_inst_n_56,ADC_LTC2311_v3_0_S00_AXI_inst_n_57,ADC_LTC2311_v3_0_S00_AXI_inst_n_58,ADC_LTC2311_v3_0_S00_AXI_inst_n_59,ADC_LTC2311_v3_0_S00_AXI_inst_n_60,ADC_LTC2311_v3_0_S00_AXI_inst_n_61,ADC_LTC2311_v3_0_S00_AXI_inst_n_62,ADC_LTC2311_v3_0_S00_AXI_inst_n_63,ADC_LTC2311_v3_0_S00_AXI_inst_n_64,ADC_LTC2311_v3_0_S00_AXI_inst_n_65,ADC_LTC2311_v3_0_S00_AXI_inst_n_66}),
        .S_DUMMY_SAMPLE(S_DUMMY_SAMPLE),
        .S_DUMMY_SAMPLE_reg_0(S_DUMMY_SAMPLE_i_1_n_0),
        .\S_ENABLE_reg[0] (\GEN_ADC_CONT[0].inst_adc_n_4 ),
        .\S_ENABLE_reg[0]_0 (\GEN_ADC_CONT[0].inst_adc_n_10 ),
        .\S_ENABLE_reg[0]_1 (\GEN_ADC_CONT[0].inst_adc_n_14 ),
        .S_MANUAL_reg_0(\GEN_ADC_CONT[0].inst_adc_n_8 ),
        .S_MANUAL_reg_1(S_MANUAL_i_1_n_0),
        .\S_OFFSET_reg[112]_0 ({ADC_LTC2311_v3_0_S00_AXI_inst_n_18,ADC_LTC2311_v3_0_S00_AXI_inst_n_19,ADC_LTC2311_v3_0_S00_AXI_inst_n_20,ADC_LTC2311_v3_0_S00_AXI_inst_n_21,ADC_LTC2311_v3_0_S00_AXI_inst_n_22,ADC_LTC2311_v3_0_S00_AXI_inst_n_23,ADC_LTC2311_v3_0_S00_AXI_inst_n_24,ADC_LTC2311_v3_0_S00_AXI_inst_n_25}),
        .\S_SAMPLE_COUNTER_reg[0]_0 (\S_SAMPLE_COUNTER_reg[0] ),
        .\S_SAMPLE_COUNTER_reg[16]_0 (SAMPLE_COUNTER[15:8]),
        .\S_SAMPLE_COUNTER_reg[24]_0 (SAMPLE_COUNTER[23:16]),
        .\S_SAMPLE_COUNTER_reg[31]_0 (SAMPLE_COUNTER[30:24]),
        .\S_SAMPLE_TIME_reg[30]_0 (S_SAMPLE_TIME),
        .\S_SAMPLE_TIME_reg[30]_1 (S_ADC_CONV_VALUE),
        .S_SCLK(S_SCLK),
        .S_SPI_BUSY(S_SPI_BUSY),
        .S_SPI_ENABLE_reg_0(\GEN_ADC_CONT[0].inst_adc_n_9 ),
        .S_SPI_ENABLE_reg_1(S_SPI_ENABLE_i_1_n_0),
        .s00_axi_aclk(s00_axi_aclk),
        .s00_axi_aresetn(s00_axi_aresetn));
  LUT5 #(
    .INIT(32'hFBFF0055)) 
    RAW_VALID_i_1
       (.I0(\GEN_ADC_CONT[0].inst_adc_n_4 ),
        .I1(curstate_0[0]),
        .I2(curstate_0[1]),
        .I3(\GEN_ADC_CONT[0].inst_adc_n_10 ),
        .I4(RAW_VALID),
        .O(RAW_VALID_i_1_n_0));
  FDSE \S_ADC_CR_IN_reg[2] 
       (.C(s00_axi_aclk),
        .CE(1'b1),
        .D(ADC_LTC2311_v3_0_S00_AXI_inst_n_30),
        .Q(P_ADC_CR_IN[2]),
        .S(\raw_to_si/RSTD ));
  FDSE \S_ADC_CR_IN_reg[4] 
       (.C(s00_axi_aclk),
        .CE(1'b1),
        .D(S_SET_CONVERSION),
        .Q(P_ADC_CR_IN[4]),
        .S(\raw_to_si/RSTD ));
  LUT3 #(
    .INIT(8'hC4)) 
    \S_ADC_SPI_CR_IN[5]_i_1 
       (.I0(nxtstate[0]),
        .I1(nxtstate[1]),
        .I2(\S_ADC_SPI_CR_IN_reg_n_0_[5] ),
        .O(\S_ADC_SPI_CR_IN[5]_i_1_n_0 ));
  FDRE \S_ADC_SPI_CR_IN_reg[1] 
       (.C(s00_axi_aclk),
        .CE(ADC_LTC2311_v3_0_S00_AXI_inst_n_131),
        .D(ADC_LTC2311_v3_0_S00_AXI_inst_n_33),
        .Q(\S_ADC_SPI_CR_IN_reg_n_0_[1] ),
        .R(1'b0));
  FDRE \S_ADC_SPI_CR_IN_reg[3] 
       (.C(s00_axi_aclk),
        .CE(ADC_LTC2311_v3_0_S00_AXI_inst_n_131),
        .D(ADC_LTC2311_v3_0_S00_AXI_inst_n_32),
        .Q(\S_ADC_SPI_CR_IN_reg_n_0_[3] ),
        .R(1'b0));
  FDRE \S_ADC_SPI_CR_IN_reg[5] 
       (.C(s00_axi_aclk),
        .CE(1'b1),
        .D(\S_ADC_SPI_CR_IN[5]_i_1_n_0 ),
        .Q(\S_ADC_SPI_CR_IN_reg_n_0_[5] ),
        .R(\raw_to_si/RSTD ));
  LUT5 #(
    .INIT(32'hFFDF0010)) 
    S_DUMMY_SAMPLE_i_1
       (.I0(curstate_0[1]),
        .I1(curstate_0[0]),
        .I2(\GEN_ADC_CONT[0].inst_adc_n_4 ),
        .I3(\GEN_ADC_CONT[0].inst_adc_n_10 ),
        .I4(S_DUMMY_SAMPLE),
        .O(S_DUMMY_SAMPLE_i_1_n_0));
  FDRE \S_ENABLE_reg[0] 
       (.C(s00_axi_aclk),
        .CE(1'b1),
        .D(ADC_LTC2311_v3_0_S00_AXI_inst_n_26),
        .Q(ENABLE),
        .R(\raw_to_si/RSTD ));
  LUT6 #(
    .INIT(64'hFF8FFFFF00800000)) 
    S_MANUAL_i_1
       (.I0(MANUAL),
        .I1(\GEN_ADC_CONT[0].inst_adc_n_10 ),
        .I2(\GEN_ADC_CONT[0].inst_adc_n_4 ),
        .I3(S_ADC_CR),
        .I4(s00_axi_aresetn),
        .I5(\GEN_ADC_CONT[0].inst_adc_n_8 ),
        .O(S_MANUAL_i_1_n_0));
  FDRE \S_SCLK_IN_reg[0] 
       (.C(s00_axi_aclk),
        .CE(S_SCLK_IN),
        .D(ADC_LTC2311_v3_0_S00_AXI_inst_n_32),
        .Q(SCLK_IN),
        .R(1'b0));
  FDRE \S_SET_CONVERSION_reg[0] 
       (.C(s00_axi_aclk),
        .CE(1'b1),
        .D(ADC_LTC2311_v3_0_S00_AXI_inst_n_134),
        .Q(SET_CONVERSION),
        .R(ADC_LTC2311_v3_0_S00_AXI_inst_n_7));
  FDRE \S_SET_OFFSET_reg[0] 
       (.C(s00_axi_aclk),
        .CE(1'b1),
        .D(ADC_LTC2311_v3_0_S00_AXI_inst_n_135),
        .Q(SET_OFFSET),
        .R(ADC_LTC2311_v3_0_S00_AXI_inst_n_7));
  FDRE \S_SET_SAMPLES_reg[0] 
       (.C(s00_axi_aclk),
        .CE(1'b1),
        .D(ADC_LTC2311_v3_0_S00_AXI_inst_n_130),
        .Q(SET_SAMPLES),
        .R(1'b0));
  FDRE \S_SET_SAMPLE_TIME_reg[0] 
       (.C(s00_axi_aclk),
        .CE(1'b1),
        .D(ADC_LTC2311_v3_0_S00_AXI_inst_n_29),
        .Q(SET_SAMPLE_TIME),
        .R(1'b0));
  LUT6 #(
    .INIT(64'h22F2F2F222020202)) 
    S_SPI_ENABLE_i_1
       (.I0(curstate_0[0]),
        .I1(curstate_0[1]),
        .I2(\GEN_ADC_CONT[0].inst_adc_n_14 ),
        .I3(\GEN_ADC_CONT[0].inst_adc_n_15 ),
        .I4(S_SPI_BUSY),
        .I5(\GEN_ADC_CONT[0].inst_adc_n_9 ),
        .O(S_SPI_ENABLE_i_1_n_0));
  FDRE \S_SPI_MANUAL_reg[0] 
       (.C(s00_axi_aclk),
        .CE(1'b1),
        .D(S_SS_IN_N),
        .Q(MANUAL),
        .R(\raw_to_si/RSTD ));
  FDRE \S_SS_IN_N_reg[0] 
       (.C(s00_axi_aclk),
        .CE(S_SCLK_IN),
        .D(ADC_LTC2311_v3_0_S00_AXI_inst_n_33),
        .Q(SS_IN_N),
        .R(1'b0));
  FDRE \S_TRIGGER_CNV_PIPE_reg[0] 
       (.C(s00_axi_aclk),
        .CE(1'b1),
        .D(TRIGGER_CNV),
        .Q(S_TRIGGER_CNV_PIPE),
        .R(\raw_to_si/RSTD ));
  (* FSM_ENCODING = "auto" *) 
  (* FSM_SAFE_STATE = "power_on_state" *) 
  FDRE #(
    .INIT(1'b0)) 
    \curstate_reg[0] 
       (.C(s00_axi_aclk),
        .CE(1'b1),
        .D(nxtstate[0]),
        .Q(curstate[0]),
        .R(\raw_to_si/RSTD ));
  (* FSM_ENCODING = "auto" *) 
  (* FSM_SAFE_STATE = "power_on_state" *) 
  FDRE #(
    .INIT(1'b0)) 
    \curstate_reg[1] 
       (.C(s00_axi_aclk),
        .CE(1'b1),
        .D(nxtstate[1]),
        .Q(curstate[1]),
        .R(\raw_to_si/RSTD ));
  (* CAPACITANCE = "DONT_CARE" *) 
  (* XILINX_LEGACY_PRIM = "OBUFDS" *) 
  (* box_type = "PRIMITIVE" *) 
  OBUFDS #(
    .IOSTANDARD("DEFAULT")) 
    \gen_diff.gen_diff1[0].OBUFDS_inst 
       (.I(S_SCLK),
        .O(SCLK_DIFF[0]),
        .OB(SCLK_DIFF[1]));
  (* CAPACITANCE = "DONT_CARE" *) 
  (* IBUF_DELAY_VALUE = "0" *) 
  (* IFD_DELAY_VALUE = "AUTO" *) 
  (* box_type = "PRIMITIVE" *) 
  IBUFDS #(
    .IOSTANDARD("DEFAULT")) 
    \gen_diff.gen_diff1[0].gen_diff2[0].IBUFDS_inst 
       (.I(MISO_DIFF[0]),
        .IB(MISO_DIFF[1]),
        .O(S_MISO[0]));
  (* CAPACITANCE = "DONT_CARE" *) 
  (* IBUF_DELAY_VALUE = "0" *) 
  (* IFD_DELAY_VALUE = "AUTO" *) 
  (* box_type = "PRIMITIVE" *) 
  IBUFDS #(
    .IOSTANDARD("DEFAULT")) 
    \gen_diff.gen_diff1[0].gen_diff2[1].IBUFDS_inst 
       (.I(MISO_DIFF[2]),
        .IB(MISO_DIFF[3]),
        .O(S_MISO[1]));
  (* CAPACITANCE = "DONT_CARE" *) 
  (* IBUF_DELAY_VALUE = "0" *) 
  (* IFD_DELAY_VALUE = "AUTO" *) 
  (* box_type = "PRIMITIVE" *) 
  IBUFDS #(
    .IOSTANDARD("DEFAULT")) 
    \gen_diff.gen_diff1[0].gen_diff2[2].IBUFDS_inst 
       (.I(MISO_DIFF[4]),
        .IB(MISO_DIFF[5]),
        .O(S_MISO[2]));
  (* CAPACITANCE = "DONT_CARE" *) 
  (* IBUF_DELAY_VALUE = "0" *) 
  (* IFD_DELAY_VALUE = "AUTO" *) 
  (* box_type = "PRIMITIVE" *) 
  IBUFDS #(
    .IOSTANDARD("DEFAULT")) 
    \gen_diff.gen_diff1[0].gen_diff2[3].IBUFDS_inst 
       (.I(MISO_DIFF[6]),
        .IB(MISO_DIFF[7]),
        .O(S_MISO[3]));
  (* CAPACITANCE = "DONT_CARE" *) 
  (* IBUF_DELAY_VALUE = "0" *) 
  (* IFD_DELAY_VALUE = "AUTO" *) 
  (* box_type = "PRIMITIVE" *) 
  IBUFDS #(
    .IOSTANDARD("DEFAULT")) 
    \gen_diff.gen_diff1[0].gen_diff2[4].IBUFDS_inst 
       (.I(MISO_DIFF[8]),
        .IB(MISO_DIFF[9]),
        .O(S_MISO[4]));
  (* CAPACITANCE = "DONT_CARE" *) 
  (* IBUF_DELAY_VALUE = "0" *) 
  (* IFD_DELAY_VALUE = "AUTO" *) 
  (* box_type = "PRIMITIVE" *) 
  IBUFDS #(
    .IOSTANDARD("DEFAULT")) 
    \gen_diff.gen_diff1[0].gen_diff2[5].IBUFDS_inst 
       (.I(MISO_DIFF[10]),
        .IB(MISO_DIFF[11]),
        .O(S_MISO[5]));
  (* CAPACITANCE = "DONT_CARE" *) 
  (* IBUF_DELAY_VALUE = "0" *) 
  (* IFD_DELAY_VALUE = "AUTO" *) 
  (* box_type = "PRIMITIVE" *) 
  IBUFDS #(
    .IOSTANDARD("DEFAULT")) 
    \gen_diff.gen_diff1[0].gen_diff2[6].IBUFDS_inst 
       (.I(MISO_DIFF[12]),
        .IB(MISO_DIFF[13]),
        .O(S_MISO[6]));
  (* CAPACITANCE = "DONT_CARE" *) 
  (* IBUF_DELAY_VALUE = "0" *) 
  (* IFD_DELAY_VALUE = "AUTO" *) 
  (* box_type = "PRIMITIVE" *) 
  IBUFDS #(
    .IOSTANDARD("DEFAULT")) 
    \gen_diff.gen_diff1[0].gen_diff2[7].IBUFDS_inst 
       (.I(MISO_DIFF[14]),
        .IB(MISO_DIFF[15]),
        .O(S_MISO[7]));
endmodule

(* ORIG_REF_NAME = "ADC_LTC2311_v3_0_S00_AXI" *) 
module zusys_A3_ADC_LTC2311_0_ADC_LTC2311_v3_0_S00_AXI
   (axi_awready_reg_0,
    RSTP,
    axi_wready_reg_0,
    axi_arready_reg_0,
    \ADC_CR_reg[3]_0 ,
    s00_axi_bvalid,
    s00_axi_rvalid,
    \ADC_CR_reg[3]_1 ,
    S_AXI_ARESETN,
    E,
    \S_SET_CONVERSION_reg[0] ,
    \ADC_CHANNEL_reg[7]_0 ,
    \S_ENABLE_reg[0] ,
    nxtstate,
    \ADC_MASTER_CHANNEL_reg[0]_0 ,
    \ADC_CR_reg[2]_0 ,
    CPHA,
    D,
    CPOL,
    Q,
    \ADC_CONV_VALUE_reg[30]_0 ,
    s00_axi_rdata,
    \S_SET_SAMPLES_reg[0] ,
    \ADC_CR_reg[3]_2 ,
    S_SCLK_IN,
    S_SET_CONVERSION,
    \ADC_MASTER_CHANNEL_reg[0]_1 ,
    \ADC_CR_reg[6]_0 ,
    S_SS_IN_N,
    s00_axi_aclk,
    RAW_VALID,
    SI_VALID,
    BUSY,
    s00_axi_wdata,
    s00_axi_aresetn,
    SET_CONVERSION,
    SET_OFFSET,
    SET_SAMPLE_TIME,
    SET_SAMPLES,
    s00_axi_wvalid,
    s00_axi_awvalid,
    s00_axi_bready,
    s00_axi_arvalid,
    s00_axi_rready,
    ENABLE,
    P_ADC_CR_IN,
    s00_axi_awaddr,
    s00_axi_araddr,
    s00_axi_wstrb,
    \ADC_SPI_CR_reg[3]_0 ,
    \ADC_SPI_CR_reg[5]_0 ,
    \curstate_reg[0] ,
    TRIGGER_CNV,
    S_TRIGGER_CNV_PIPE);
  output axi_awready_reg_0;
  output RSTP;
  output axi_wready_reg_0;
  output axi_arready_reg_0;
  output [0:0]\ADC_CR_reg[3]_0 ;
  output s00_axi_bvalid;
  output s00_axi_rvalid;
  output \ADC_CR_reg[3]_1 ;
  output S_AXI_ARESETN;
  output [0:0]E;
  output [7:0]\S_SET_CONVERSION_reg[0] ;
  output [7:0]\ADC_CHANNEL_reg[7]_0 ;
  output \S_ENABLE_reg[0] ;
  output [1:0]nxtstate;
  output \ADC_MASTER_CHANNEL_reg[0]_0 ;
  output \ADC_CR_reg[2]_0 ;
  output CPHA;
  output [1:0]D;
  output CPOL;
  output [31:0]Q;
  output [30:0]\ADC_CONV_VALUE_reg[30]_0 ;
  output [31:0]s00_axi_rdata;
  output \S_SET_SAMPLES_reg[0] ;
  output [0:0]\ADC_CR_reg[3]_2 ;
  output S_SCLK_IN;
  output S_SET_CONVERSION;
  output \ADC_MASTER_CHANNEL_reg[0]_1 ;
  output \ADC_CR_reg[6]_0 ;
  output S_SS_IN_N;
  input s00_axi_aclk;
  input [0:0]RAW_VALID;
  input [0:0]SI_VALID;
  input BUSY;
  input [31:0]s00_axi_wdata;
  input s00_axi_aresetn;
  input SET_CONVERSION;
  input SET_OFFSET;
  input SET_SAMPLE_TIME;
  input SET_SAMPLES;
  input s00_axi_wvalid;
  input s00_axi_awvalid;
  input s00_axi_bready;
  input s00_axi_arvalid;
  input s00_axi_rready;
  input ENABLE;
  input [1:0]P_ADC_CR_IN;
  input [3:0]s00_axi_awaddr;
  input [3:0]s00_axi_araddr;
  input [3:0]s00_axi_wstrb;
  input [1:0]\ADC_SPI_CR_reg[3]_0 ;
  input \ADC_SPI_CR_reg[5]_0 ;
  input [1:0]\curstate_reg[0] ;
  input [0:0]TRIGGER_CNV;
  input S_TRIGGER_CNV_PIPE;

  wire \ADC_AVAILABLE[15]_i_1_n_0 ;
  wire \ADC_AVAILABLE[23]_i_1_n_0 ;
  wire \ADC_AVAILABLE[31]_i_1_n_0 ;
  wire \ADC_AVAILABLE[7]_i_1_n_0 ;
  wire \ADC_AVAILABLE_reg_n_0_[10] ;
  wire \ADC_AVAILABLE_reg_n_0_[11] ;
  wire \ADC_AVAILABLE_reg_n_0_[12] ;
  wire \ADC_AVAILABLE_reg_n_0_[13] ;
  wire \ADC_AVAILABLE_reg_n_0_[14] ;
  wire \ADC_AVAILABLE_reg_n_0_[15] ;
  wire \ADC_AVAILABLE_reg_n_0_[16] ;
  wire \ADC_AVAILABLE_reg_n_0_[17] ;
  wire \ADC_AVAILABLE_reg_n_0_[18] ;
  wire \ADC_AVAILABLE_reg_n_0_[19] ;
  wire \ADC_AVAILABLE_reg_n_0_[1] ;
  wire \ADC_AVAILABLE_reg_n_0_[20] ;
  wire \ADC_AVAILABLE_reg_n_0_[21] ;
  wire \ADC_AVAILABLE_reg_n_0_[22] ;
  wire \ADC_AVAILABLE_reg_n_0_[23] ;
  wire \ADC_AVAILABLE_reg_n_0_[24] ;
  wire \ADC_AVAILABLE_reg_n_0_[25] ;
  wire \ADC_AVAILABLE_reg_n_0_[26] ;
  wire \ADC_AVAILABLE_reg_n_0_[27] ;
  wire \ADC_AVAILABLE_reg_n_0_[28] ;
  wire \ADC_AVAILABLE_reg_n_0_[29] ;
  wire \ADC_AVAILABLE_reg_n_0_[2] ;
  wire \ADC_AVAILABLE_reg_n_0_[30] ;
  wire \ADC_AVAILABLE_reg_n_0_[31] ;
  wire \ADC_AVAILABLE_reg_n_0_[3] ;
  wire \ADC_AVAILABLE_reg_n_0_[4] ;
  wire \ADC_AVAILABLE_reg_n_0_[5] ;
  wire \ADC_AVAILABLE_reg_n_0_[6] ;
  wire \ADC_AVAILABLE_reg_n_0_[7] ;
  wire \ADC_AVAILABLE_reg_n_0_[8] ;
  wire \ADC_AVAILABLE_reg_n_0_[9] ;
  wire \ADC_CHANNEL[15]_i_1_n_0 ;
  wire \ADC_CHANNEL[23]_i_1_n_0 ;
  wire \ADC_CHANNEL[31]_i_1_n_0 ;
  wire \ADC_CHANNEL[7]_i_1_n_0 ;
  wire [7:0]\ADC_CHANNEL_reg[7]_0 ;
  wire \ADC_CONV_VALUE[15]_i_1_n_0 ;
  wire \ADC_CONV_VALUE[23]_i_1_n_0 ;
  wire \ADC_CONV_VALUE[31]_i_1_n_0 ;
  wire \ADC_CONV_VALUE[7]_i_1_n_0 ;
  wire [30:0]\ADC_CONV_VALUE_reg[30]_0 ;
  wire [31:3]ADC_CR;
  wire \ADC_CR[15]_i_1_n_0 ;
  wire \ADC_CR[23]_i_1_n_0 ;
  wire \ADC_CR[2]_i_1_n_0 ;
  wire \ADC_CR[31]_i_1_n_0 ;
  wire \ADC_CR[4]_i_1_n_0 ;
  wire \ADC_CR[7]_i_1_n_0 ;
  wire \ADC_CR_reg[2]_0 ;
  wire [0:0]\ADC_CR_reg[3]_0 ;
  wire \ADC_CR_reg[3]_1 ;
  wire [0:0]\ADC_CR_reg[3]_2 ;
  wire \ADC_CR_reg[6]_0 ;
  wire \ADC_CR_reg_n_0_[10] ;
  wire \ADC_CR_reg_n_0_[11] ;
  wire \ADC_CR_reg_n_0_[12] ;
  wire \ADC_CR_reg_n_0_[13] ;
  wire \ADC_CR_reg_n_0_[14] ;
  wire \ADC_CR_reg_n_0_[15] ;
  wire \ADC_CR_reg_n_0_[16] ;
  wire \ADC_CR_reg_n_0_[17] ;
  wire \ADC_CR_reg_n_0_[18] ;
  wire \ADC_CR_reg_n_0_[19] ;
  wire \ADC_CR_reg_n_0_[20] ;
  wire \ADC_CR_reg_n_0_[21] ;
  wire \ADC_CR_reg_n_0_[22] ;
  wire \ADC_CR_reg_n_0_[23] ;
  wire \ADC_CR_reg_n_0_[24] ;
  wire \ADC_CR_reg_n_0_[25] ;
  wire \ADC_CR_reg_n_0_[26] ;
  wire \ADC_CR_reg_n_0_[27] ;
  wire \ADC_CR_reg_n_0_[28] ;
  wire \ADC_CR_reg_n_0_[29] ;
  wire \ADC_CR_reg_n_0_[30] ;
  wire \ADC_CR_reg_n_0_[31] ;
  wire \ADC_CR_reg_n_0_[8] ;
  wire \ADC_CR_reg_n_0_[9] ;
  wire [0:0]ADC_MASTER_BUSY;
  wire \ADC_MASTER_CHANNEL[15]_i_1_n_0 ;
  wire \ADC_MASTER_CHANNEL[23]_i_1_n_0 ;
  wire \ADC_MASTER_CHANNEL[31]_i_1_n_0 ;
  wire \ADC_MASTER_CHANNEL[7]_i_1_n_0 ;
  wire \ADC_MASTER_CHANNEL_reg[0]_0 ;
  wire \ADC_MASTER_CHANNEL_reg[0]_1 ;
  wire \ADC_MASTER_CHANNEL_reg_n_0_[10] ;
  wire \ADC_MASTER_CHANNEL_reg_n_0_[11] ;
  wire \ADC_MASTER_CHANNEL_reg_n_0_[12] ;
  wire \ADC_MASTER_CHANNEL_reg_n_0_[13] ;
  wire \ADC_MASTER_CHANNEL_reg_n_0_[14] ;
  wire \ADC_MASTER_CHANNEL_reg_n_0_[15] ;
  wire \ADC_MASTER_CHANNEL_reg_n_0_[16] ;
  wire \ADC_MASTER_CHANNEL_reg_n_0_[17] ;
  wire \ADC_MASTER_CHANNEL_reg_n_0_[18] ;
  wire \ADC_MASTER_CHANNEL_reg_n_0_[19] ;
  wire \ADC_MASTER_CHANNEL_reg_n_0_[1] ;
  wire \ADC_MASTER_CHANNEL_reg_n_0_[20] ;
  wire \ADC_MASTER_CHANNEL_reg_n_0_[21] ;
  wire \ADC_MASTER_CHANNEL_reg_n_0_[22] ;
  wire \ADC_MASTER_CHANNEL_reg_n_0_[23] ;
  wire \ADC_MASTER_CHANNEL_reg_n_0_[24] ;
  wire \ADC_MASTER_CHANNEL_reg_n_0_[25] ;
  wire \ADC_MASTER_CHANNEL_reg_n_0_[26] ;
  wire \ADC_MASTER_CHANNEL_reg_n_0_[27] ;
  wire \ADC_MASTER_CHANNEL_reg_n_0_[28] ;
  wire \ADC_MASTER_CHANNEL_reg_n_0_[29] ;
  wire \ADC_MASTER_CHANNEL_reg_n_0_[2] ;
  wire \ADC_MASTER_CHANNEL_reg_n_0_[30] ;
  wire \ADC_MASTER_CHANNEL_reg_n_0_[31] ;
  wire \ADC_MASTER_CHANNEL_reg_n_0_[3] ;
  wire \ADC_MASTER_CHANNEL_reg_n_0_[4] ;
  wire \ADC_MASTER_CHANNEL_reg_n_0_[5] ;
  wire \ADC_MASTER_CHANNEL_reg_n_0_[6] ;
  wire \ADC_MASTER_CHANNEL_reg_n_0_[7] ;
  wire \ADC_MASTER_CHANNEL_reg_n_0_[8] ;
  wire \ADC_MASTER_CHANNEL_reg_n_0_[9] ;
  wire [0:0]ADC_MASTER_FINISH;
  wire [0:0]ADC_MASTER_SI_FINISH;
  wire [31:7]ADC_SPI_CR;
  wire [5:1]ADC_SPI_CR0_in;
  wire \ADC_SPI_CR[15]_i_1_n_0 ;
  wire \ADC_SPI_CR[23]_i_1_n_0 ;
  wire \ADC_SPI_CR[31]_i_1_n_0 ;
  wire \ADC_SPI_CR[31]_i_3_n_0 ;
  wire \ADC_SPI_CR[6]_i_1_n_0 ;
  wire \ADC_SPI_CR[7]_i_1_n_0 ;
  wire [1:0]\ADC_SPI_CR_reg[3]_0 ;
  wire \ADC_SPI_CR_reg[5]_0 ;
  wire \ADC_SPI_CR_reg_n_0_[10] ;
  wire \ADC_SPI_CR_reg_n_0_[11] ;
  wire \ADC_SPI_CR_reg_n_0_[12] ;
  wire \ADC_SPI_CR_reg_n_0_[13] ;
  wire \ADC_SPI_CR_reg_n_0_[14] ;
  wire \ADC_SPI_CR_reg_n_0_[15] ;
  wire \ADC_SPI_CR_reg_n_0_[16] ;
  wire \ADC_SPI_CR_reg_n_0_[17] ;
  wire \ADC_SPI_CR_reg_n_0_[18] ;
  wire \ADC_SPI_CR_reg_n_0_[19] ;
  wire \ADC_SPI_CR_reg_n_0_[1] ;
  wire \ADC_SPI_CR_reg_n_0_[20] ;
  wire \ADC_SPI_CR_reg_n_0_[21] ;
  wire \ADC_SPI_CR_reg_n_0_[22] ;
  wire \ADC_SPI_CR_reg_n_0_[23] ;
  wire \ADC_SPI_CR_reg_n_0_[24] ;
  wire \ADC_SPI_CR_reg_n_0_[25] ;
  wire \ADC_SPI_CR_reg_n_0_[26] ;
  wire \ADC_SPI_CR_reg_n_0_[27] ;
  wire \ADC_SPI_CR_reg_n_0_[28] ;
  wire \ADC_SPI_CR_reg_n_0_[29] ;
  wire \ADC_SPI_CR_reg_n_0_[30] ;
  wire \ADC_SPI_CR_reg_n_0_[31] ;
  wire \ADC_SPI_CR_reg_n_0_[3] ;
  wire \ADC_SPI_CR_reg_n_0_[5] ;
  wire \ADC_SPI_CR_reg_n_0_[8] ;
  wire \ADC_SPI_CR_reg_n_0_[9] ;
  wire BUSY;
  wire CPHA;
  wire CPOL;
  wire [1:0]D;
  wire [0:0]E;
  wire ENABLE;
  wire IS_BUSY;
  wire [1:0]P_ADC_CR_IN;
  wire [31:0]Q;
  wire [0:0]RAW_VALID;
  wire RSTP;
  wire SET_CONVERSION;
  wire SET_OFFSET;
  wire SET_SAMPLES;
  wire SET_SAMPLE_TIME;
  wire [0:0]SI_VALID;
  wire S_ADC_AVAILABLE;
  wire [31:0]S_ADC_CHANNEL;
  wire [31:31]S_ADC_CONV_VALUE;
  wire [7:0]S_ADC_CR;
  wire S_ADC_MASTER_CHANNEL;
  wire S_AXI_ARESETN;
  wire S_ENABLE0__4;
  wire \S_ENABLE[0]_i_2_n_0 ;
  wire \S_ENABLE[0]_i_4_n_0 ;
  wire \S_ENABLE_reg[0] ;
  wire S_SCLK_IN;
  wire S_SET_CONVERSION;
  wire [7:0]\S_SET_CONVERSION_reg[0] ;
  wire \S_SET_SAMPLES[0]_i_2_n_0 ;
  wire \S_SET_SAMPLES_reg[0] ;
  wire S_SET_SAMPLE_TIME8_out;
  wire S_SS_IN_N;
  wire S_TRIGGER_CNV_PIPE;
  wire [0:0]TRIGGER_CNV;
  wire aw_en_i_1_n_0;
  wire aw_en_reg_n_0;
  wire axi_arready0;
  wire axi_arready_reg_0;
  wire axi_awready0;
  wire axi_awready_reg_0;
  wire axi_bvalid_i_1_n_0;
  wire \axi_rdata[0]_i_4_n_0 ;
  wire \axi_rdata[0]_i_5_n_0 ;
  wire \axi_rdata[0]_i_6_n_0 ;
  wire \axi_rdata[0]_i_7_n_0 ;
  wire \axi_rdata[10]_i_2_n_0 ;
  wire \axi_rdata[10]_i_3_n_0 ;
  wire \axi_rdata[10]_i_4_n_0 ;
  wire \axi_rdata[10]_i_5_n_0 ;
  wire \axi_rdata[11]_i_2_n_0 ;
  wire \axi_rdata[11]_i_3_n_0 ;
  wire \axi_rdata[11]_i_4_n_0 ;
  wire \axi_rdata[11]_i_5_n_0 ;
  wire \axi_rdata[12]_i_2_n_0 ;
  wire \axi_rdata[12]_i_3_n_0 ;
  wire \axi_rdata[12]_i_4_n_0 ;
  wire \axi_rdata[12]_i_5_n_0 ;
  wire \axi_rdata[13]_i_2_n_0 ;
  wire \axi_rdata[13]_i_3_n_0 ;
  wire \axi_rdata[13]_i_4_n_0 ;
  wire \axi_rdata[13]_i_5_n_0 ;
  wire \axi_rdata[14]_i_2_n_0 ;
  wire \axi_rdata[14]_i_3_n_0 ;
  wire \axi_rdata[14]_i_4_n_0 ;
  wire \axi_rdata[14]_i_5_n_0 ;
  wire \axi_rdata[15]_i_2_n_0 ;
  wire \axi_rdata[15]_i_3_n_0 ;
  wire \axi_rdata[15]_i_4_n_0 ;
  wire \axi_rdata[15]_i_5_n_0 ;
  wire \axi_rdata[16]_i_2_n_0 ;
  wire \axi_rdata[16]_i_3_n_0 ;
  wire \axi_rdata[16]_i_4_n_0 ;
  wire \axi_rdata[16]_i_5_n_0 ;
  wire \axi_rdata[17]_i_2_n_0 ;
  wire \axi_rdata[17]_i_3_n_0 ;
  wire \axi_rdata[17]_i_4_n_0 ;
  wire \axi_rdata[17]_i_5_n_0 ;
  wire \axi_rdata[18]_i_2_n_0 ;
  wire \axi_rdata[18]_i_3_n_0 ;
  wire \axi_rdata[18]_i_4_n_0 ;
  wire \axi_rdata[18]_i_5_n_0 ;
  wire \axi_rdata[19]_i_2_n_0 ;
  wire \axi_rdata[19]_i_3_n_0 ;
  wire \axi_rdata[19]_i_4_n_0 ;
  wire \axi_rdata[19]_i_5_n_0 ;
  wire \axi_rdata[1]_i_2_n_0 ;
  wire \axi_rdata[1]_i_3_n_0 ;
  wire \axi_rdata[1]_i_4_n_0 ;
  wire \axi_rdata[1]_i_5_n_0 ;
  wire \axi_rdata[20]_i_2_n_0 ;
  wire \axi_rdata[20]_i_3_n_0 ;
  wire \axi_rdata[20]_i_4_n_0 ;
  wire \axi_rdata[20]_i_5_n_0 ;
  wire \axi_rdata[21]_i_2_n_0 ;
  wire \axi_rdata[21]_i_3_n_0 ;
  wire \axi_rdata[21]_i_4_n_0 ;
  wire \axi_rdata[21]_i_5_n_0 ;
  wire \axi_rdata[22]_i_2_n_0 ;
  wire \axi_rdata[22]_i_3_n_0 ;
  wire \axi_rdata[22]_i_4_n_0 ;
  wire \axi_rdata[22]_i_5_n_0 ;
  wire \axi_rdata[23]_i_2_n_0 ;
  wire \axi_rdata[23]_i_3_n_0 ;
  wire \axi_rdata[23]_i_4_n_0 ;
  wire \axi_rdata[23]_i_5_n_0 ;
  wire \axi_rdata[24]_i_2_n_0 ;
  wire \axi_rdata[24]_i_3_n_0 ;
  wire \axi_rdata[24]_i_4_n_0 ;
  wire \axi_rdata[24]_i_5_n_0 ;
  wire \axi_rdata[25]_i_2_n_0 ;
  wire \axi_rdata[25]_i_3_n_0 ;
  wire \axi_rdata[25]_i_4_n_0 ;
  wire \axi_rdata[25]_i_5_n_0 ;
  wire \axi_rdata[26]_i_2_n_0 ;
  wire \axi_rdata[26]_i_3_n_0 ;
  wire \axi_rdata[26]_i_4_n_0 ;
  wire \axi_rdata[26]_i_5_n_0 ;
  wire \axi_rdata[27]_i_2_n_0 ;
  wire \axi_rdata[27]_i_3_n_0 ;
  wire \axi_rdata[27]_i_4_n_0 ;
  wire \axi_rdata[27]_i_5_n_0 ;
  wire \axi_rdata[28]_i_2_n_0 ;
  wire \axi_rdata[28]_i_3_n_0 ;
  wire \axi_rdata[28]_i_4_n_0 ;
  wire \axi_rdata[28]_i_5_n_0 ;
  wire \axi_rdata[29]_i_2_n_0 ;
  wire \axi_rdata[29]_i_3_n_0 ;
  wire \axi_rdata[29]_i_4_n_0 ;
  wire \axi_rdata[29]_i_5_n_0 ;
  wire \axi_rdata[2]_i_2_n_0 ;
  wire \axi_rdata[2]_i_3_n_0 ;
  wire \axi_rdata[2]_i_4_n_0 ;
  wire \axi_rdata[2]_i_5_n_0 ;
  wire \axi_rdata[30]_i_2_n_0 ;
  wire \axi_rdata[30]_i_3_n_0 ;
  wire \axi_rdata[30]_i_4_n_0 ;
  wire \axi_rdata[30]_i_5_n_0 ;
  wire \axi_rdata[31]_i_3_n_0 ;
  wire \axi_rdata[31]_i_4_n_0 ;
  wire \axi_rdata[31]_i_5_n_0 ;
  wire \axi_rdata[31]_i_6_n_0 ;
  wire \axi_rdata[3]_i_2_n_0 ;
  wire \axi_rdata[3]_i_3_n_0 ;
  wire \axi_rdata[3]_i_4_n_0 ;
  wire \axi_rdata[3]_i_5_n_0 ;
  wire \axi_rdata[4]_i_2_n_0 ;
  wire \axi_rdata[4]_i_3_n_0 ;
  wire \axi_rdata[4]_i_4_n_0 ;
  wire \axi_rdata[4]_i_5_n_0 ;
  wire \axi_rdata[5]_i_2_n_0 ;
  wire \axi_rdata[5]_i_3_n_0 ;
  wire \axi_rdata[5]_i_4_n_0 ;
  wire \axi_rdata[5]_i_5_n_0 ;
  wire \axi_rdata[6]_i_2_n_0 ;
  wire \axi_rdata[6]_i_3_n_0 ;
  wire \axi_rdata[6]_i_4_n_0 ;
  wire \axi_rdata[6]_i_5_n_0 ;
  wire \axi_rdata[7]_i_2_n_0 ;
  wire \axi_rdata[7]_i_3_n_0 ;
  wire \axi_rdata[7]_i_4_n_0 ;
  wire \axi_rdata[7]_i_5_n_0 ;
  wire \axi_rdata[8]_i_2_n_0 ;
  wire \axi_rdata[8]_i_3_n_0 ;
  wire \axi_rdata[8]_i_4_n_0 ;
  wire \axi_rdata[8]_i_5_n_0 ;
  wire \axi_rdata[9]_i_2_n_0 ;
  wire \axi_rdata[9]_i_3_n_0 ;
  wire \axi_rdata[9]_i_4_n_0 ;
  wire \axi_rdata[9]_i_5_n_0 ;
  wire \axi_rdata_reg[0]_i_2_n_0 ;
  wire \axi_rdata_reg[0]_i_3_n_0 ;
  wire axi_rvalid_i_1_n_0;
  wire axi_wready0;
  wire axi_wready_reg_0;
  wire [1:0]\curstate_reg[0] ;
  wire [1:0]nxtstate;
  wire [3:0]p_0_in;
  wire p_0_in13_in;
  wire [31:7]p_1_in;
  wire [31:0]reg_data_out;
  wire s00_axi_aclk;
  wire [3:0]s00_axi_araddr;
  wire s00_axi_aresetn;
  wire s00_axi_arvalid;
  wire [3:0]s00_axi_awaddr;
  wire s00_axi_awvalid;
  wire s00_axi_bready;
  wire s00_axi_bvalid;
  wire [31:0]s00_axi_rdata;
  wire s00_axi_rready;
  wire s00_axi_rvalid;
  wire [31:0]s00_axi_wdata;
  wire [3:0]s00_axi_wstrb;
  wire s00_axi_wvalid;
  wire [3:0]sel0;
  wire [31:0]slv_reg10;
  wire \slv_reg10[15]_i_1_n_0 ;
  wire \slv_reg10[23]_i_1_n_0 ;
  wire \slv_reg10[31]_i_1_n_0 ;
  wire \slv_reg10[7]_i_1_n_0 ;
  wire [31:0]slv_reg11;
  wire \slv_reg11[15]_i_1_n_0 ;
  wire \slv_reg11[23]_i_1_n_0 ;
  wire \slv_reg11[31]_i_1_n_0 ;
  wire \slv_reg11[7]_i_1_n_0 ;
  wire [31:0]slv_reg12;
  wire \slv_reg12[15]_i_1_n_0 ;
  wire \slv_reg12[23]_i_1_n_0 ;
  wire \slv_reg12[31]_i_1_n_0 ;
  wire \slv_reg12[7]_i_1_n_0 ;
  wire [31:0]slv_reg13;
  wire \slv_reg13[15]_i_1_n_0 ;
  wire \slv_reg13[23]_i_1_n_0 ;
  wire \slv_reg13[31]_i_1_n_0 ;
  wire \slv_reg13[7]_i_1_n_0 ;
  wire [31:0]slv_reg14;
  wire \slv_reg14[15]_i_1_n_0 ;
  wire \slv_reg14[23]_i_1_n_0 ;
  wire \slv_reg14[31]_i_1_n_0 ;
  wire \slv_reg14[7]_i_1_n_0 ;
  wire [31:0]slv_reg15;
  wire \slv_reg15[15]_i_1_n_0 ;
  wire \slv_reg15[23]_i_1_n_0 ;
  wire \slv_reg15[31]_i_1_n_0 ;
  wire \slv_reg15[7]_i_1_n_0 ;
  wire slv_reg_rden;
  wire slv_reg_wren__0;

  LUT6 #(
    .INIT(64'h0000000000008000)) 
    \ADC_AVAILABLE[15]_i_1 
       (.I0(slv_reg_wren__0),
        .I1(p_0_in[3]),
        .I2(p_0_in[0]),
        .I3(s00_axi_wstrb[1]),
        .I4(p_0_in[1]),
        .I5(p_0_in[2]),
        .O(\ADC_AVAILABLE[15]_i_1_n_0 ));
  LUT6 #(
    .INIT(64'h0000000000008000)) 
    \ADC_AVAILABLE[23]_i_1 
       (.I0(slv_reg_wren__0),
        .I1(p_0_in[3]),
        .I2(p_0_in[0]),
        .I3(s00_axi_wstrb[2]),
        .I4(p_0_in[1]),
        .I5(p_0_in[2]),
        .O(\ADC_AVAILABLE[23]_i_1_n_0 ));
  LUT6 #(
    .INIT(64'h0000000000008000)) 
    \ADC_AVAILABLE[31]_i_1 
       (.I0(slv_reg_wren__0),
        .I1(p_0_in[3]),
        .I2(p_0_in[0]),
        .I3(s00_axi_wstrb[3]),
        .I4(p_0_in[1]),
        .I5(p_0_in[2]),
        .O(\ADC_AVAILABLE[31]_i_1_n_0 ));
  LUT6 #(
    .INIT(64'h0000000000008000)) 
    \ADC_AVAILABLE[7]_i_1 
       (.I0(slv_reg_wren__0),
        .I1(p_0_in[3]),
        .I2(p_0_in[0]),
        .I3(s00_axi_wstrb[0]),
        .I4(p_0_in[1]),
        .I5(p_0_in[2]),
        .O(\ADC_AVAILABLE[7]_i_1_n_0 ));
  FDSE \ADC_AVAILABLE_reg[0] 
       (.C(s00_axi_aclk),
        .CE(\ADC_AVAILABLE[7]_i_1_n_0 ),
        .D(s00_axi_wdata[0]),
        .Q(S_ADC_AVAILABLE),
        .S(RSTP));
  FDSE \ADC_AVAILABLE_reg[10] 
       (.C(s00_axi_aclk),
        .CE(\ADC_AVAILABLE[15]_i_1_n_0 ),
        .D(s00_axi_wdata[10]),
        .Q(\ADC_AVAILABLE_reg_n_0_[10] ),
        .S(RSTP));
  FDSE \ADC_AVAILABLE_reg[11] 
       (.C(s00_axi_aclk),
        .CE(\ADC_AVAILABLE[15]_i_1_n_0 ),
        .D(s00_axi_wdata[11]),
        .Q(\ADC_AVAILABLE_reg_n_0_[11] ),
        .S(RSTP));
  FDSE \ADC_AVAILABLE_reg[12] 
       (.C(s00_axi_aclk),
        .CE(\ADC_AVAILABLE[15]_i_1_n_0 ),
        .D(s00_axi_wdata[12]),
        .Q(\ADC_AVAILABLE_reg_n_0_[12] ),
        .S(RSTP));
  FDSE \ADC_AVAILABLE_reg[13] 
       (.C(s00_axi_aclk),
        .CE(\ADC_AVAILABLE[15]_i_1_n_0 ),
        .D(s00_axi_wdata[13]),
        .Q(\ADC_AVAILABLE_reg_n_0_[13] ),
        .S(RSTP));
  FDSE \ADC_AVAILABLE_reg[14] 
       (.C(s00_axi_aclk),
        .CE(\ADC_AVAILABLE[15]_i_1_n_0 ),
        .D(s00_axi_wdata[14]),
        .Q(\ADC_AVAILABLE_reg_n_0_[14] ),
        .S(RSTP));
  FDSE \ADC_AVAILABLE_reg[15] 
       (.C(s00_axi_aclk),
        .CE(\ADC_AVAILABLE[15]_i_1_n_0 ),
        .D(s00_axi_wdata[15]),
        .Q(\ADC_AVAILABLE_reg_n_0_[15] ),
        .S(RSTP));
  FDSE \ADC_AVAILABLE_reg[16] 
       (.C(s00_axi_aclk),
        .CE(\ADC_AVAILABLE[23]_i_1_n_0 ),
        .D(s00_axi_wdata[16]),
        .Q(\ADC_AVAILABLE_reg_n_0_[16] ),
        .S(RSTP));
  FDSE \ADC_AVAILABLE_reg[17] 
       (.C(s00_axi_aclk),
        .CE(\ADC_AVAILABLE[23]_i_1_n_0 ),
        .D(s00_axi_wdata[17]),
        .Q(\ADC_AVAILABLE_reg_n_0_[17] ),
        .S(RSTP));
  FDSE \ADC_AVAILABLE_reg[18] 
       (.C(s00_axi_aclk),
        .CE(\ADC_AVAILABLE[23]_i_1_n_0 ),
        .D(s00_axi_wdata[18]),
        .Q(\ADC_AVAILABLE_reg_n_0_[18] ),
        .S(RSTP));
  FDSE \ADC_AVAILABLE_reg[19] 
       (.C(s00_axi_aclk),
        .CE(\ADC_AVAILABLE[23]_i_1_n_0 ),
        .D(s00_axi_wdata[19]),
        .Q(\ADC_AVAILABLE_reg_n_0_[19] ),
        .S(RSTP));
  FDSE \ADC_AVAILABLE_reg[1] 
       (.C(s00_axi_aclk),
        .CE(\ADC_AVAILABLE[7]_i_1_n_0 ),
        .D(s00_axi_wdata[1]),
        .Q(\ADC_AVAILABLE_reg_n_0_[1] ),
        .S(RSTP));
  FDSE \ADC_AVAILABLE_reg[20] 
       (.C(s00_axi_aclk),
        .CE(\ADC_AVAILABLE[23]_i_1_n_0 ),
        .D(s00_axi_wdata[20]),
        .Q(\ADC_AVAILABLE_reg_n_0_[20] ),
        .S(RSTP));
  FDSE \ADC_AVAILABLE_reg[21] 
       (.C(s00_axi_aclk),
        .CE(\ADC_AVAILABLE[23]_i_1_n_0 ),
        .D(s00_axi_wdata[21]),
        .Q(\ADC_AVAILABLE_reg_n_0_[21] ),
        .S(RSTP));
  FDSE \ADC_AVAILABLE_reg[22] 
       (.C(s00_axi_aclk),
        .CE(\ADC_AVAILABLE[23]_i_1_n_0 ),
        .D(s00_axi_wdata[22]),
        .Q(\ADC_AVAILABLE_reg_n_0_[22] ),
        .S(RSTP));
  FDSE \ADC_AVAILABLE_reg[23] 
       (.C(s00_axi_aclk),
        .CE(\ADC_AVAILABLE[23]_i_1_n_0 ),
        .D(s00_axi_wdata[23]),
        .Q(\ADC_AVAILABLE_reg_n_0_[23] ),
        .S(RSTP));
  FDSE \ADC_AVAILABLE_reg[24] 
       (.C(s00_axi_aclk),
        .CE(\ADC_AVAILABLE[31]_i_1_n_0 ),
        .D(s00_axi_wdata[24]),
        .Q(\ADC_AVAILABLE_reg_n_0_[24] ),
        .S(RSTP));
  FDSE \ADC_AVAILABLE_reg[25] 
       (.C(s00_axi_aclk),
        .CE(\ADC_AVAILABLE[31]_i_1_n_0 ),
        .D(s00_axi_wdata[25]),
        .Q(\ADC_AVAILABLE_reg_n_0_[25] ),
        .S(RSTP));
  FDSE \ADC_AVAILABLE_reg[26] 
       (.C(s00_axi_aclk),
        .CE(\ADC_AVAILABLE[31]_i_1_n_0 ),
        .D(s00_axi_wdata[26]),
        .Q(\ADC_AVAILABLE_reg_n_0_[26] ),
        .S(RSTP));
  FDSE \ADC_AVAILABLE_reg[27] 
       (.C(s00_axi_aclk),
        .CE(\ADC_AVAILABLE[31]_i_1_n_0 ),
        .D(s00_axi_wdata[27]),
        .Q(\ADC_AVAILABLE_reg_n_0_[27] ),
        .S(RSTP));
  FDSE \ADC_AVAILABLE_reg[28] 
       (.C(s00_axi_aclk),
        .CE(\ADC_AVAILABLE[31]_i_1_n_0 ),
        .D(s00_axi_wdata[28]),
        .Q(\ADC_AVAILABLE_reg_n_0_[28] ),
        .S(RSTP));
  FDSE \ADC_AVAILABLE_reg[29] 
       (.C(s00_axi_aclk),
        .CE(\ADC_AVAILABLE[31]_i_1_n_0 ),
        .D(s00_axi_wdata[29]),
        .Q(\ADC_AVAILABLE_reg_n_0_[29] ),
        .S(RSTP));
  FDSE \ADC_AVAILABLE_reg[2] 
       (.C(s00_axi_aclk),
        .CE(\ADC_AVAILABLE[7]_i_1_n_0 ),
        .D(s00_axi_wdata[2]),
        .Q(\ADC_AVAILABLE_reg_n_0_[2] ),
        .S(RSTP));
  FDSE \ADC_AVAILABLE_reg[30] 
       (.C(s00_axi_aclk),
        .CE(\ADC_AVAILABLE[31]_i_1_n_0 ),
        .D(s00_axi_wdata[30]),
        .Q(\ADC_AVAILABLE_reg_n_0_[30] ),
        .S(RSTP));
  FDSE \ADC_AVAILABLE_reg[31] 
       (.C(s00_axi_aclk),
        .CE(\ADC_AVAILABLE[31]_i_1_n_0 ),
        .D(s00_axi_wdata[31]),
        .Q(\ADC_AVAILABLE_reg_n_0_[31] ),
        .S(RSTP));
  FDSE \ADC_AVAILABLE_reg[3] 
       (.C(s00_axi_aclk),
        .CE(\ADC_AVAILABLE[7]_i_1_n_0 ),
        .D(s00_axi_wdata[3]),
        .Q(\ADC_AVAILABLE_reg_n_0_[3] ),
        .S(RSTP));
  FDSE \ADC_AVAILABLE_reg[4] 
       (.C(s00_axi_aclk),
        .CE(\ADC_AVAILABLE[7]_i_1_n_0 ),
        .D(s00_axi_wdata[4]),
        .Q(\ADC_AVAILABLE_reg_n_0_[4] ),
        .S(RSTP));
  FDSE \ADC_AVAILABLE_reg[5] 
       (.C(s00_axi_aclk),
        .CE(\ADC_AVAILABLE[7]_i_1_n_0 ),
        .D(s00_axi_wdata[5]),
        .Q(\ADC_AVAILABLE_reg_n_0_[5] ),
        .S(RSTP));
  FDSE \ADC_AVAILABLE_reg[6] 
       (.C(s00_axi_aclk),
        .CE(\ADC_AVAILABLE[7]_i_1_n_0 ),
        .D(s00_axi_wdata[6]),
        .Q(\ADC_AVAILABLE_reg_n_0_[6] ),
        .S(RSTP));
  FDSE \ADC_AVAILABLE_reg[7] 
       (.C(s00_axi_aclk),
        .CE(\ADC_AVAILABLE[7]_i_1_n_0 ),
        .D(s00_axi_wdata[7]),
        .Q(\ADC_AVAILABLE_reg_n_0_[7] ),
        .S(RSTP));
  FDSE \ADC_AVAILABLE_reg[8] 
       (.C(s00_axi_aclk),
        .CE(\ADC_AVAILABLE[15]_i_1_n_0 ),
        .D(s00_axi_wdata[8]),
        .Q(\ADC_AVAILABLE_reg_n_0_[8] ),
        .S(RSTP));
  FDSE \ADC_AVAILABLE_reg[9] 
       (.C(s00_axi_aclk),
        .CE(\ADC_AVAILABLE[15]_i_1_n_0 ),
        .D(s00_axi_wdata[9]),
        .Q(\ADC_AVAILABLE_reg_n_0_[9] ),
        .S(RSTP));
  LUT6 #(
    .INIT(64'h0000000800000000)) 
    \ADC_CHANNEL[15]_i_1 
       (.I0(slv_reg_wren__0),
        .I1(s00_axi_wstrb[1]),
        .I2(p_0_in[3]),
        .I3(p_0_in[1]),
        .I4(p_0_in[0]),
        .I5(p_0_in[2]),
        .O(\ADC_CHANNEL[15]_i_1_n_0 ));
  LUT6 #(
    .INIT(64'h0000000800000000)) 
    \ADC_CHANNEL[23]_i_1 
       (.I0(slv_reg_wren__0),
        .I1(s00_axi_wstrb[2]),
        .I2(p_0_in[3]),
        .I3(p_0_in[1]),
        .I4(p_0_in[0]),
        .I5(p_0_in[2]),
        .O(\ADC_CHANNEL[23]_i_1_n_0 ));
  LUT6 #(
    .INIT(64'h0000000800000000)) 
    \ADC_CHANNEL[31]_i_1 
       (.I0(slv_reg_wren__0),
        .I1(s00_axi_wstrb[3]),
        .I2(p_0_in[3]),
        .I3(p_0_in[1]),
        .I4(p_0_in[0]),
        .I5(p_0_in[2]),
        .O(\ADC_CHANNEL[31]_i_1_n_0 ));
  LUT6 #(
    .INIT(64'h0000000800000000)) 
    \ADC_CHANNEL[7]_i_1 
       (.I0(slv_reg_wren__0),
        .I1(s00_axi_wstrb[0]),
        .I2(p_0_in[3]),
        .I3(p_0_in[1]),
        .I4(p_0_in[0]),
        .I5(p_0_in[2]),
        .O(\ADC_CHANNEL[7]_i_1_n_0 ));
  FDRE \ADC_CHANNEL_reg[0] 
       (.C(s00_axi_aclk),
        .CE(\ADC_CHANNEL[7]_i_1_n_0 ),
        .D(s00_axi_wdata[0]),
        .Q(S_ADC_CHANNEL[0]),
        .R(RSTP));
  FDRE \ADC_CHANNEL_reg[10] 
       (.C(s00_axi_aclk),
        .CE(\ADC_CHANNEL[15]_i_1_n_0 ),
        .D(s00_axi_wdata[10]),
        .Q(S_ADC_CHANNEL[10]),
        .R(RSTP));
  FDRE \ADC_CHANNEL_reg[11] 
       (.C(s00_axi_aclk),
        .CE(\ADC_CHANNEL[15]_i_1_n_0 ),
        .D(s00_axi_wdata[11]),
        .Q(S_ADC_CHANNEL[11]),
        .R(RSTP));
  FDRE \ADC_CHANNEL_reg[12] 
       (.C(s00_axi_aclk),
        .CE(\ADC_CHANNEL[15]_i_1_n_0 ),
        .D(s00_axi_wdata[12]),
        .Q(S_ADC_CHANNEL[12]),
        .R(RSTP));
  FDRE \ADC_CHANNEL_reg[13] 
       (.C(s00_axi_aclk),
        .CE(\ADC_CHANNEL[15]_i_1_n_0 ),
        .D(s00_axi_wdata[13]),
        .Q(S_ADC_CHANNEL[13]),
        .R(RSTP));
  FDRE \ADC_CHANNEL_reg[14] 
       (.C(s00_axi_aclk),
        .CE(\ADC_CHANNEL[15]_i_1_n_0 ),
        .D(s00_axi_wdata[14]),
        .Q(S_ADC_CHANNEL[14]),
        .R(RSTP));
  FDRE \ADC_CHANNEL_reg[15] 
       (.C(s00_axi_aclk),
        .CE(\ADC_CHANNEL[15]_i_1_n_0 ),
        .D(s00_axi_wdata[15]),
        .Q(S_ADC_CHANNEL[15]),
        .R(RSTP));
  FDRE \ADC_CHANNEL_reg[16] 
       (.C(s00_axi_aclk),
        .CE(\ADC_CHANNEL[23]_i_1_n_0 ),
        .D(s00_axi_wdata[16]),
        .Q(S_ADC_CHANNEL[16]),
        .R(RSTP));
  FDRE \ADC_CHANNEL_reg[17] 
       (.C(s00_axi_aclk),
        .CE(\ADC_CHANNEL[23]_i_1_n_0 ),
        .D(s00_axi_wdata[17]),
        .Q(S_ADC_CHANNEL[17]),
        .R(RSTP));
  FDRE \ADC_CHANNEL_reg[18] 
       (.C(s00_axi_aclk),
        .CE(\ADC_CHANNEL[23]_i_1_n_0 ),
        .D(s00_axi_wdata[18]),
        .Q(S_ADC_CHANNEL[18]),
        .R(RSTP));
  FDRE \ADC_CHANNEL_reg[19] 
       (.C(s00_axi_aclk),
        .CE(\ADC_CHANNEL[23]_i_1_n_0 ),
        .D(s00_axi_wdata[19]),
        .Q(S_ADC_CHANNEL[19]),
        .R(RSTP));
  FDRE \ADC_CHANNEL_reg[1] 
       (.C(s00_axi_aclk),
        .CE(\ADC_CHANNEL[7]_i_1_n_0 ),
        .D(s00_axi_wdata[1]),
        .Q(S_ADC_CHANNEL[1]),
        .R(RSTP));
  FDRE \ADC_CHANNEL_reg[20] 
       (.C(s00_axi_aclk),
        .CE(\ADC_CHANNEL[23]_i_1_n_0 ),
        .D(s00_axi_wdata[20]),
        .Q(S_ADC_CHANNEL[20]),
        .R(RSTP));
  FDRE \ADC_CHANNEL_reg[21] 
       (.C(s00_axi_aclk),
        .CE(\ADC_CHANNEL[23]_i_1_n_0 ),
        .D(s00_axi_wdata[21]),
        .Q(S_ADC_CHANNEL[21]),
        .R(RSTP));
  FDRE \ADC_CHANNEL_reg[22] 
       (.C(s00_axi_aclk),
        .CE(\ADC_CHANNEL[23]_i_1_n_0 ),
        .D(s00_axi_wdata[22]),
        .Q(S_ADC_CHANNEL[22]),
        .R(RSTP));
  FDRE \ADC_CHANNEL_reg[23] 
       (.C(s00_axi_aclk),
        .CE(\ADC_CHANNEL[23]_i_1_n_0 ),
        .D(s00_axi_wdata[23]),
        .Q(S_ADC_CHANNEL[23]),
        .R(RSTP));
  FDRE \ADC_CHANNEL_reg[24] 
       (.C(s00_axi_aclk),
        .CE(\ADC_CHANNEL[31]_i_1_n_0 ),
        .D(s00_axi_wdata[24]),
        .Q(S_ADC_CHANNEL[24]),
        .R(RSTP));
  FDRE \ADC_CHANNEL_reg[25] 
       (.C(s00_axi_aclk),
        .CE(\ADC_CHANNEL[31]_i_1_n_0 ),
        .D(s00_axi_wdata[25]),
        .Q(S_ADC_CHANNEL[25]),
        .R(RSTP));
  FDRE \ADC_CHANNEL_reg[26] 
       (.C(s00_axi_aclk),
        .CE(\ADC_CHANNEL[31]_i_1_n_0 ),
        .D(s00_axi_wdata[26]),
        .Q(S_ADC_CHANNEL[26]),
        .R(RSTP));
  FDRE \ADC_CHANNEL_reg[27] 
       (.C(s00_axi_aclk),
        .CE(\ADC_CHANNEL[31]_i_1_n_0 ),
        .D(s00_axi_wdata[27]),
        .Q(S_ADC_CHANNEL[27]),
        .R(RSTP));
  FDRE \ADC_CHANNEL_reg[28] 
       (.C(s00_axi_aclk),
        .CE(\ADC_CHANNEL[31]_i_1_n_0 ),
        .D(s00_axi_wdata[28]),
        .Q(S_ADC_CHANNEL[28]),
        .R(RSTP));
  FDRE \ADC_CHANNEL_reg[29] 
       (.C(s00_axi_aclk),
        .CE(\ADC_CHANNEL[31]_i_1_n_0 ),
        .D(s00_axi_wdata[29]),
        .Q(S_ADC_CHANNEL[29]),
        .R(RSTP));
  FDRE \ADC_CHANNEL_reg[2] 
       (.C(s00_axi_aclk),
        .CE(\ADC_CHANNEL[7]_i_1_n_0 ),
        .D(s00_axi_wdata[2]),
        .Q(S_ADC_CHANNEL[2]),
        .R(RSTP));
  FDRE \ADC_CHANNEL_reg[30] 
       (.C(s00_axi_aclk),
        .CE(\ADC_CHANNEL[31]_i_1_n_0 ),
        .D(s00_axi_wdata[30]),
        .Q(S_ADC_CHANNEL[30]),
        .R(RSTP));
  FDRE \ADC_CHANNEL_reg[31] 
       (.C(s00_axi_aclk),
        .CE(\ADC_CHANNEL[31]_i_1_n_0 ),
        .D(s00_axi_wdata[31]),
        .Q(S_ADC_CHANNEL[31]),
        .R(RSTP));
  FDRE \ADC_CHANNEL_reg[3] 
       (.C(s00_axi_aclk),
        .CE(\ADC_CHANNEL[7]_i_1_n_0 ),
        .D(s00_axi_wdata[3]),
        .Q(S_ADC_CHANNEL[3]),
        .R(RSTP));
  FDRE \ADC_CHANNEL_reg[4] 
       (.C(s00_axi_aclk),
        .CE(\ADC_CHANNEL[7]_i_1_n_0 ),
        .D(s00_axi_wdata[4]),
        .Q(S_ADC_CHANNEL[4]),
        .R(RSTP));
  FDRE \ADC_CHANNEL_reg[5] 
       (.C(s00_axi_aclk),
        .CE(\ADC_CHANNEL[7]_i_1_n_0 ),
        .D(s00_axi_wdata[5]),
        .Q(S_ADC_CHANNEL[5]),
        .R(RSTP));
  FDRE \ADC_CHANNEL_reg[6] 
       (.C(s00_axi_aclk),
        .CE(\ADC_CHANNEL[7]_i_1_n_0 ),
        .D(s00_axi_wdata[6]),
        .Q(S_ADC_CHANNEL[6]),
        .R(RSTP));
  FDRE \ADC_CHANNEL_reg[7] 
       (.C(s00_axi_aclk),
        .CE(\ADC_CHANNEL[7]_i_1_n_0 ),
        .D(s00_axi_wdata[7]),
        .Q(S_ADC_CHANNEL[7]),
        .R(RSTP));
  FDRE \ADC_CHANNEL_reg[8] 
       (.C(s00_axi_aclk),
        .CE(\ADC_CHANNEL[15]_i_1_n_0 ),
        .D(s00_axi_wdata[8]),
        .Q(S_ADC_CHANNEL[8]),
        .R(RSTP));
  FDRE \ADC_CHANNEL_reg[9] 
       (.C(s00_axi_aclk),
        .CE(\ADC_CHANNEL[15]_i_1_n_0 ),
        .D(s00_axi_wdata[9]),
        .Q(S_ADC_CHANNEL[9]),
        .R(RSTP));
  LUT6 #(
    .INIT(64'h0000000800000000)) 
    \ADC_CONV_VALUE[15]_i_1 
       (.I0(slv_reg_wren__0),
        .I1(p_0_in[3]),
        .I2(p_0_in[1]),
        .I3(p_0_in[0]),
        .I4(p_0_in[2]),
        .I5(s00_axi_wstrb[1]),
        .O(\ADC_CONV_VALUE[15]_i_1_n_0 ));
  LUT6 #(
    .INIT(64'h0000000800000000)) 
    \ADC_CONV_VALUE[23]_i_1 
       (.I0(slv_reg_wren__0),
        .I1(p_0_in[3]),
        .I2(p_0_in[1]),
        .I3(p_0_in[0]),
        .I4(p_0_in[2]),
        .I5(s00_axi_wstrb[2]),
        .O(\ADC_CONV_VALUE[23]_i_1_n_0 ));
  LUT6 #(
    .INIT(64'h0000000800000000)) 
    \ADC_CONV_VALUE[31]_i_1 
       (.I0(slv_reg_wren__0),
        .I1(p_0_in[3]),
        .I2(p_0_in[1]),
        .I3(p_0_in[0]),
        .I4(p_0_in[2]),
        .I5(s00_axi_wstrb[3]),
        .O(\ADC_CONV_VALUE[31]_i_1_n_0 ));
  LUT6 #(
    .INIT(64'h0000000800000000)) 
    \ADC_CONV_VALUE[7]_i_1 
       (.I0(slv_reg_wren__0),
        .I1(p_0_in[3]),
        .I2(p_0_in[1]),
        .I3(p_0_in[0]),
        .I4(p_0_in[2]),
        .I5(s00_axi_wstrb[0]),
        .O(\ADC_CONV_VALUE[7]_i_1_n_0 ));
  FDRE \ADC_CONV_VALUE_reg[0] 
       (.C(s00_axi_aclk),
        .CE(\ADC_CONV_VALUE[7]_i_1_n_0 ),
        .D(s00_axi_wdata[0]),
        .Q(\ADC_CONV_VALUE_reg[30]_0 [0]),
        .R(RSTP));
  FDRE \ADC_CONV_VALUE_reg[10] 
       (.C(s00_axi_aclk),
        .CE(\ADC_CONV_VALUE[15]_i_1_n_0 ),
        .D(s00_axi_wdata[10]),
        .Q(\ADC_CONV_VALUE_reg[30]_0 [10]),
        .R(RSTP));
  FDRE \ADC_CONV_VALUE_reg[11] 
       (.C(s00_axi_aclk),
        .CE(\ADC_CONV_VALUE[15]_i_1_n_0 ),
        .D(s00_axi_wdata[11]),
        .Q(\ADC_CONV_VALUE_reg[30]_0 [11]),
        .R(RSTP));
  FDRE \ADC_CONV_VALUE_reg[12] 
       (.C(s00_axi_aclk),
        .CE(\ADC_CONV_VALUE[15]_i_1_n_0 ),
        .D(s00_axi_wdata[12]),
        .Q(\ADC_CONV_VALUE_reg[30]_0 [12]),
        .R(RSTP));
  FDRE \ADC_CONV_VALUE_reg[13] 
       (.C(s00_axi_aclk),
        .CE(\ADC_CONV_VALUE[15]_i_1_n_0 ),
        .D(s00_axi_wdata[13]),
        .Q(\ADC_CONV_VALUE_reg[30]_0 [13]),
        .R(RSTP));
  FDRE \ADC_CONV_VALUE_reg[14] 
       (.C(s00_axi_aclk),
        .CE(\ADC_CONV_VALUE[15]_i_1_n_0 ),
        .D(s00_axi_wdata[14]),
        .Q(\ADC_CONV_VALUE_reg[30]_0 [14]),
        .R(RSTP));
  FDRE \ADC_CONV_VALUE_reg[15] 
       (.C(s00_axi_aclk),
        .CE(\ADC_CONV_VALUE[15]_i_1_n_0 ),
        .D(s00_axi_wdata[15]),
        .Q(\ADC_CONV_VALUE_reg[30]_0 [15]),
        .R(RSTP));
  FDRE \ADC_CONV_VALUE_reg[16] 
       (.C(s00_axi_aclk),
        .CE(\ADC_CONV_VALUE[23]_i_1_n_0 ),
        .D(s00_axi_wdata[16]),
        .Q(\ADC_CONV_VALUE_reg[30]_0 [16]),
        .R(RSTP));
  FDRE \ADC_CONV_VALUE_reg[17] 
       (.C(s00_axi_aclk),
        .CE(\ADC_CONV_VALUE[23]_i_1_n_0 ),
        .D(s00_axi_wdata[17]),
        .Q(\ADC_CONV_VALUE_reg[30]_0 [17]),
        .R(RSTP));
  FDRE \ADC_CONV_VALUE_reg[18] 
       (.C(s00_axi_aclk),
        .CE(\ADC_CONV_VALUE[23]_i_1_n_0 ),
        .D(s00_axi_wdata[18]),
        .Q(\ADC_CONV_VALUE_reg[30]_0 [18]),
        .R(RSTP));
  FDRE \ADC_CONV_VALUE_reg[19] 
       (.C(s00_axi_aclk),
        .CE(\ADC_CONV_VALUE[23]_i_1_n_0 ),
        .D(s00_axi_wdata[19]),
        .Q(\ADC_CONV_VALUE_reg[30]_0 [19]),
        .R(RSTP));
  FDRE \ADC_CONV_VALUE_reg[1] 
       (.C(s00_axi_aclk),
        .CE(\ADC_CONV_VALUE[7]_i_1_n_0 ),
        .D(s00_axi_wdata[1]),
        .Q(\ADC_CONV_VALUE_reg[30]_0 [1]),
        .R(RSTP));
  FDRE \ADC_CONV_VALUE_reg[20] 
       (.C(s00_axi_aclk),
        .CE(\ADC_CONV_VALUE[23]_i_1_n_0 ),
        .D(s00_axi_wdata[20]),
        .Q(\ADC_CONV_VALUE_reg[30]_0 [20]),
        .R(RSTP));
  FDRE \ADC_CONV_VALUE_reg[21] 
       (.C(s00_axi_aclk),
        .CE(\ADC_CONV_VALUE[23]_i_1_n_0 ),
        .D(s00_axi_wdata[21]),
        .Q(\ADC_CONV_VALUE_reg[30]_0 [21]),
        .R(RSTP));
  FDRE \ADC_CONV_VALUE_reg[22] 
       (.C(s00_axi_aclk),
        .CE(\ADC_CONV_VALUE[23]_i_1_n_0 ),
        .D(s00_axi_wdata[22]),
        .Q(\ADC_CONV_VALUE_reg[30]_0 [22]),
        .R(RSTP));
  FDRE \ADC_CONV_VALUE_reg[23] 
       (.C(s00_axi_aclk),
        .CE(\ADC_CONV_VALUE[23]_i_1_n_0 ),
        .D(s00_axi_wdata[23]),
        .Q(\ADC_CONV_VALUE_reg[30]_0 [23]),
        .R(RSTP));
  FDRE \ADC_CONV_VALUE_reg[24] 
       (.C(s00_axi_aclk),
        .CE(\ADC_CONV_VALUE[31]_i_1_n_0 ),
        .D(s00_axi_wdata[24]),
        .Q(\ADC_CONV_VALUE_reg[30]_0 [24]),
        .R(RSTP));
  FDRE \ADC_CONV_VALUE_reg[25] 
       (.C(s00_axi_aclk),
        .CE(\ADC_CONV_VALUE[31]_i_1_n_0 ),
        .D(s00_axi_wdata[25]),
        .Q(\ADC_CONV_VALUE_reg[30]_0 [25]),
        .R(RSTP));
  FDRE \ADC_CONV_VALUE_reg[26] 
       (.C(s00_axi_aclk),
        .CE(\ADC_CONV_VALUE[31]_i_1_n_0 ),
        .D(s00_axi_wdata[26]),
        .Q(\ADC_CONV_VALUE_reg[30]_0 [26]),
        .R(RSTP));
  FDRE \ADC_CONV_VALUE_reg[27] 
       (.C(s00_axi_aclk),
        .CE(\ADC_CONV_VALUE[31]_i_1_n_0 ),
        .D(s00_axi_wdata[27]),
        .Q(\ADC_CONV_VALUE_reg[30]_0 [27]),
        .R(RSTP));
  FDRE \ADC_CONV_VALUE_reg[28] 
       (.C(s00_axi_aclk),
        .CE(\ADC_CONV_VALUE[31]_i_1_n_0 ),
        .D(s00_axi_wdata[28]),
        .Q(\ADC_CONV_VALUE_reg[30]_0 [28]),
        .R(RSTP));
  FDRE \ADC_CONV_VALUE_reg[29] 
       (.C(s00_axi_aclk),
        .CE(\ADC_CONV_VALUE[31]_i_1_n_0 ),
        .D(s00_axi_wdata[29]),
        .Q(\ADC_CONV_VALUE_reg[30]_0 [29]),
        .R(RSTP));
  FDRE \ADC_CONV_VALUE_reg[2] 
       (.C(s00_axi_aclk),
        .CE(\ADC_CONV_VALUE[7]_i_1_n_0 ),
        .D(s00_axi_wdata[2]),
        .Q(\ADC_CONV_VALUE_reg[30]_0 [2]),
        .R(RSTP));
  FDRE \ADC_CONV_VALUE_reg[30] 
       (.C(s00_axi_aclk),
        .CE(\ADC_CONV_VALUE[31]_i_1_n_0 ),
        .D(s00_axi_wdata[30]),
        .Q(\ADC_CONV_VALUE_reg[30]_0 [30]),
        .R(RSTP));
  FDRE \ADC_CONV_VALUE_reg[31] 
       (.C(s00_axi_aclk),
        .CE(\ADC_CONV_VALUE[31]_i_1_n_0 ),
        .D(s00_axi_wdata[31]),
        .Q(S_ADC_CONV_VALUE),
        .R(RSTP));
  FDRE \ADC_CONV_VALUE_reg[3] 
       (.C(s00_axi_aclk),
        .CE(\ADC_CONV_VALUE[7]_i_1_n_0 ),
        .D(s00_axi_wdata[3]),
        .Q(\ADC_CONV_VALUE_reg[30]_0 [3]),
        .R(RSTP));
  FDRE \ADC_CONV_VALUE_reg[4] 
       (.C(s00_axi_aclk),
        .CE(\ADC_CONV_VALUE[7]_i_1_n_0 ),
        .D(s00_axi_wdata[4]),
        .Q(\ADC_CONV_VALUE_reg[30]_0 [4]),
        .R(RSTP));
  FDRE \ADC_CONV_VALUE_reg[5] 
       (.C(s00_axi_aclk),
        .CE(\ADC_CONV_VALUE[7]_i_1_n_0 ),
        .D(s00_axi_wdata[5]),
        .Q(\ADC_CONV_VALUE_reg[30]_0 [5]),
        .R(RSTP));
  FDRE \ADC_CONV_VALUE_reg[6] 
       (.C(s00_axi_aclk),
        .CE(\ADC_CONV_VALUE[7]_i_1_n_0 ),
        .D(s00_axi_wdata[6]),
        .Q(\ADC_CONV_VALUE_reg[30]_0 [6]),
        .R(RSTP));
  FDRE \ADC_CONV_VALUE_reg[7] 
       (.C(s00_axi_aclk),
        .CE(\ADC_CONV_VALUE[7]_i_1_n_0 ),
        .D(s00_axi_wdata[7]),
        .Q(\ADC_CONV_VALUE_reg[30]_0 [7]),
        .R(RSTP));
  FDRE \ADC_CONV_VALUE_reg[8] 
       (.C(s00_axi_aclk),
        .CE(\ADC_CONV_VALUE[15]_i_1_n_0 ),
        .D(s00_axi_wdata[8]),
        .Q(\ADC_CONV_VALUE_reg[30]_0 [8]),
        .R(RSTP));
  FDRE \ADC_CONV_VALUE_reg[9] 
       (.C(s00_axi_aclk),
        .CE(\ADC_CONV_VALUE[15]_i_1_n_0 ),
        .D(s00_axi_wdata[9]),
        .Q(\ADC_CONV_VALUE_reg[30]_0 [9]),
        .R(RSTP));
  LUT3 #(
    .INIT(8'h8A)) 
    \ADC_CR[15]_i_1 
       (.I0(ADC_CR[15]),
        .I1(\ADC_CR_reg[3]_0 ),
        .I2(s00_axi_aresetn),
        .O(\ADC_CR[15]_i_1_n_0 ));
  LUT6 #(
    .INIT(64'h00080000FFFFFFFF)) 
    \ADC_CR[15]_i_2 
       (.I0(\ADC_SPI_CR[31]_i_3_n_0 ),
        .I1(s00_axi_wstrb[1]),
        .I2(p_0_in[0]),
        .I3(p_0_in[1]),
        .I4(slv_reg_wren__0),
        .I5(S_AXI_ARESETN),
        .O(ADC_CR[15]));
  LUT3 #(
    .INIT(8'h8A)) 
    \ADC_CR[23]_i_1 
       (.I0(ADC_CR[23]),
        .I1(\ADC_CR_reg[3]_0 ),
        .I2(s00_axi_aresetn),
        .O(\ADC_CR[23]_i_1_n_0 ));
  LUT6 #(
    .INIT(64'h00080000FFFFFFFF)) 
    \ADC_CR[23]_i_2 
       (.I0(\ADC_SPI_CR[31]_i_3_n_0 ),
        .I1(s00_axi_wstrb[2]),
        .I2(p_0_in[0]),
        .I3(p_0_in[1]),
        .I4(slv_reg_wren__0),
        .I5(S_AXI_ARESETN),
        .O(ADC_CR[23]));
  LUT6 #(
    .INIT(64'h50505050D8085050)) 
    \ADC_CR[2]_i_1 
       (.I0(ADC_CR[3]),
        .I1(s00_axi_wdata[2]),
        .I2(S_ADC_CR[2]),
        .I3(P_ADC_CR_IN[0]),
        .I4(s00_axi_aresetn),
        .I5(\ADC_CR_reg[3]_0 ),
        .O(\ADC_CR[2]_i_1_n_0 ));
  LUT3 #(
    .INIT(8'h8A)) 
    \ADC_CR[31]_i_1 
       (.I0(ADC_CR[31]),
        .I1(\ADC_CR_reg[3]_0 ),
        .I2(s00_axi_aresetn),
        .O(\ADC_CR[31]_i_1_n_0 ));
  LUT6 #(
    .INIT(64'h00080000FFFFFFFF)) 
    \ADC_CR[31]_i_2 
       (.I0(\ADC_SPI_CR[31]_i_3_n_0 ),
        .I1(s00_axi_wstrb[3]),
        .I2(p_0_in[0]),
        .I3(p_0_in[1]),
        .I4(slv_reg_wren__0),
        .I5(S_AXI_ARESETN),
        .O(ADC_CR[31]));
  LUT6 #(
    .INIT(64'h50505050D8085050)) 
    \ADC_CR[4]_i_1 
       (.I0(ADC_CR[3]),
        .I1(s00_axi_wdata[4]),
        .I2(S_ADC_CR[4]),
        .I3(P_ADC_CR_IN[1]),
        .I4(s00_axi_aresetn),
        .I5(\ADC_CR_reg[3]_0 ),
        .O(\ADC_CR[4]_i_1_n_0 ));
  LUT3 #(
    .INIT(8'h8A)) 
    \ADC_CR[7]_i_1 
       (.I0(ADC_CR[3]),
        .I1(\ADC_CR_reg[3]_0 ),
        .I2(s00_axi_aresetn),
        .O(\ADC_CR[7]_i_1_n_0 ));
  LUT6 #(
    .INIT(64'h00080000FFFFFFFF)) 
    \ADC_CR[7]_i_2 
       (.I0(\ADC_SPI_CR[31]_i_3_n_0 ),
        .I1(s00_axi_wstrb[0]),
        .I2(p_0_in[0]),
        .I3(p_0_in[1]),
        .I4(slv_reg_wren__0),
        .I5(S_AXI_ARESETN),
        .O(ADC_CR[3]));
  FDRE \ADC_CR_reg[0] 
       (.C(s00_axi_aclk),
        .CE(ADC_CR[3]),
        .D(s00_axi_wdata[0]),
        .Q(S_ADC_CR[0]),
        .R(\ADC_CR[7]_i_1_n_0 ));
  FDRE \ADC_CR_reg[10] 
       (.C(s00_axi_aclk),
        .CE(ADC_CR[15]),
        .D(s00_axi_wdata[10]),
        .Q(\ADC_CR_reg_n_0_[10] ),
        .R(\ADC_CR[15]_i_1_n_0 ));
  FDRE \ADC_CR_reg[11] 
       (.C(s00_axi_aclk),
        .CE(ADC_CR[15]),
        .D(s00_axi_wdata[11]),
        .Q(\ADC_CR_reg_n_0_[11] ),
        .R(\ADC_CR[15]_i_1_n_0 ));
  FDRE \ADC_CR_reg[12] 
       (.C(s00_axi_aclk),
        .CE(ADC_CR[15]),
        .D(s00_axi_wdata[12]),
        .Q(\ADC_CR_reg_n_0_[12] ),
        .R(\ADC_CR[15]_i_1_n_0 ));
  FDRE \ADC_CR_reg[13] 
       (.C(s00_axi_aclk),
        .CE(ADC_CR[15]),
        .D(s00_axi_wdata[13]),
        .Q(\ADC_CR_reg_n_0_[13] ),
        .R(\ADC_CR[15]_i_1_n_0 ));
  FDRE \ADC_CR_reg[14] 
       (.C(s00_axi_aclk),
        .CE(ADC_CR[15]),
        .D(s00_axi_wdata[14]),
        .Q(\ADC_CR_reg_n_0_[14] ),
        .R(\ADC_CR[15]_i_1_n_0 ));
  FDRE \ADC_CR_reg[15] 
       (.C(s00_axi_aclk),
        .CE(ADC_CR[15]),
        .D(s00_axi_wdata[15]),
        .Q(\ADC_CR_reg_n_0_[15] ),
        .R(\ADC_CR[15]_i_1_n_0 ));
  FDRE \ADC_CR_reg[16] 
       (.C(s00_axi_aclk),
        .CE(ADC_CR[23]),
        .D(s00_axi_wdata[16]),
        .Q(\ADC_CR_reg_n_0_[16] ),
        .R(\ADC_CR[23]_i_1_n_0 ));
  FDRE \ADC_CR_reg[17] 
       (.C(s00_axi_aclk),
        .CE(ADC_CR[23]),
        .D(s00_axi_wdata[17]),
        .Q(\ADC_CR_reg_n_0_[17] ),
        .R(\ADC_CR[23]_i_1_n_0 ));
  FDRE \ADC_CR_reg[18] 
       (.C(s00_axi_aclk),
        .CE(ADC_CR[23]),
        .D(s00_axi_wdata[18]),
        .Q(\ADC_CR_reg_n_0_[18] ),
        .R(\ADC_CR[23]_i_1_n_0 ));
  FDRE \ADC_CR_reg[19] 
       (.C(s00_axi_aclk),
        .CE(ADC_CR[23]),
        .D(s00_axi_wdata[19]),
        .Q(\ADC_CR_reg_n_0_[19] ),
        .R(\ADC_CR[23]_i_1_n_0 ));
  FDRE \ADC_CR_reg[1] 
       (.C(s00_axi_aclk),
        .CE(ADC_CR[3]),
        .D(s00_axi_wdata[1]),
        .Q(S_ADC_CR[1]),
        .R(\ADC_CR[7]_i_1_n_0 ));
  FDRE \ADC_CR_reg[20] 
       (.C(s00_axi_aclk),
        .CE(ADC_CR[23]),
        .D(s00_axi_wdata[20]),
        .Q(\ADC_CR_reg_n_0_[20] ),
        .R(\ADC_CR[23]_i_1_n_0 ));
  FDRE \ADC_CR_reg[21] 
       (.C(s00_axi_aclk),
        .CE(ADC_CR[23]),
        .D(s00_axi_wdata[21]),
        .Q(\ADC_CR_reg_n_0_[21] ),
        .R(\ADC_CR[23]_i_1_n_0 ));
  FDRE \ADC_CR_reg[22] 
       (.C(s00_axi_aclk),
        .CE(ADC_CR[23]),
        .D(s00_axi_wdata[22]),
        .Q(\ADC_CR_reg_n_0_[22] ),
        .R(\ADC_CR[23]_i_1_n_0 ));
  FDRE \ADC_CR_reg[23] 
       (.C(s00_axi_aclk),
        .CE(ADC_CR[23]),
        .D(s00_axi_wdata[23]),
        .Q(\ADC_CR_reg_n_0_[23] ),
        .R(\ADC_CR[23]_i_1_n_0 ));
  FDRE \ADC_CR_reg[24] 
       (.C(s00_axi_aclk),
        .CE(ADC_CR[31]),
        .D(s00_axi_wdata[24]),
        .Q(\ADC_CR_reg_n_0_[24] ),
        .R(\ADC_CR[31]_i_1_n_0 ));
  FDRE \ADC_CR_reg[25] 
       (.C(s00_axi_aclk),
        .CE(ADC_CR[31]),
        .D(s00_axi_wdata[25]),
        .Q(\ADC_CR_reg_n_0_[25] ),
        .R(\ADC_CR[31]_i_1_n_0 ));
  FDRE \ADC_CR_reg[26] 
       (.C(s00_axi_aclk),
        .CE(ADC_CR[31]),
        .D(s00_axi_wdata[26]),
        .Q(\ADC_CR_reg_n_0_[26] ),
        .R(\ADC_CR[31]_i_1_n_0 ));
  FDRE \ADC_CR_reg[27] 
       (.C(s00_axi_aclk),
        .CE(ADC_CR[31]),
        .D(s00_axi_wdata[27]),
        .Q(\ADC_CR_reg_n_0_[27] ),
        .R(\ADC_CR[31]_i_1_n_0 ));
  FDRE \ADC_CR_reg[28] 
       (.C(s00_axi_aclk),
        .CE(ADC_CR[31]),
        .D(s00_axi_wdata[28]),
        .Q(\ADC_CR_reg_n_0_[28] ),
        .R(\ADC_CR[31]_i_1_n_0 ));
  FDRE \ADC_CR_reg[29] 
       (.C(s00_axi_aclk),
        .CE(ADC_CR[31]),
        .D(s00_axi_wdata[29]),
        .Q(\ADC_CR_reg_n_0_[29] ),
        .R(\ADC_CR[31]_i_1_n_0 ));
  FDRE \ADC_CR_reg[2] 
       (.C(s00_axi_aclk),
        .CE(1'b1),
        .D(\ADC_CR[2]_i_1_n_0 ),
        .Q(S_ADC_CR[2]),
        .R(1'b0));
  FDRE \ADC_CR_reg[30] 
       (.C(s00_axi_aclk),
        .CE(ADC_CR[31]),
        .D(s00_axi_wdata[30]),
        .Q(\ADC_CR_reg_n_0_[30] ),
        .R(\ADC_CR[31]_i_1_n_0 ));
  FDRE \ADC_CR_reg[31] 
       (.C(s00_axi_aclk),
        .CE(ADC_CR[31]),
        .D(s00_axi_wdata[31]),
        .Q(\ADC_CR_reg_n_0_[31] ),
        .R(\ADC_CR[31]_i_1_n_0 ));
  FDRE \ADC_CR_reg[3] 
       (.C(s00_axi_aclk),
        .CE(ADC_CR[3]),
        .D(s00_axi_wdata[3]),
        .Q(\ADC_CR_reg[3]_0 ),
        .R(\ADC_CR[7]_i_1_n_0 ));
  FDRE \ADC_CR_reg[4] 
       (.C(s00_axi_aclk),
        .CE(1'b1),
        .D(\ADC_CR[4]_i_1_n_0 ),
        .Q(S_ADC_CR[4]),
        .R(1'b0));
  FDRE \ADC_CR_reg[5] 
       (.C(s00_axi_aclk),
        .CE(ADC_CR[3]),
        .D(s00_axi_wdata[5]),
        .Q(S_ADC_CR[5]),
        .R(\ADC_CR[7]_i_1_n_0 ));
  FDRE \ADC_CR_reg[6] 
       (.C(s00_axi_aclk),
        .CE(ADC_CR[3]),
        .D(s00_axi_wdata[6]),
        .Q(S_ADC_CR[6]),
        .R(\ADC_CR[7]_i_1_n_0 ));
  FDRE \ADC_CR_reg[7] 
       (.C(s00_axi_aclk),
        .CE(ADC_CR[3]),
        .D(s00_axi_wdata[7]),
        .Q(S_ADC_CR[7]),
        .R(\ADC_CR[7]_i_1_n_0 ));
  FDRE \ADC_CR_reg[8] 
       (.C(s00_axi_aclk),
        .CE(ADC_CR[15]),
        .D(s00_axi_wdata[8]),
        .Q(\ADC_CR_reg_n_0_[8] ),
        .R(\ADC_CR[15]_i_1_n_0 ));
  FDRE \ADC_CR_reg[9] 
       (.C(s00_axi_aclk),
        .CE(ADC_CR[15]),
        .D(s00_axi_wdata[9]),
        .Q(\ADC_CR_reg_n_0_[9] ),
        .R(\ADC_CR[15]_i_1_n_0 ));
  FDRE \ADC_MASTER_BUSY_reg[0] 
       (.C(s00_axi_aclk),
        .CE(1'b1),
        .D(BUSY),
        .Q(ADC_MASTER_BUSY),
        .R(RSTP));
  LUT6 #(
    .INIT(64'h0000000000008000)) 
    \ADC_MASTER_CHANNEL[15]_i_1 
       (.I0(slv_reg_wren__0),
        .I1(s00_axi_wstrb[1]),
        .I2(p_0_in[0]),
        .I3(p_0_in[1]),
        .I4(p_0_in[2]),
        .I5(p_0_in[3]),
        .O(\ADC_MASTER_CHANNEL[15]_i_1_n_0 ));
  LUT6 #(
    .INIT(64'h0000000000008000)) 
    \ADC_MASTER_CHANNEL[23]_i_1 
       (.I0(slv_reg_wren__0),
        .I1(s00_axi_wstrb[2]),
        .I2(p_0_in[0]),
        .I3(p_0_in[1]),
        .I4(p_0_in[2]),
        .I5(p_0_in[3]),
        .O(\ADC_MASTER_CHANNEL[23]_i_1_n_0 ));
  LUT6 #(
    .INIT(64'h0000000000008000)) 
    \ADC_MASTER_CHANNEL[31]_i_1 
       (.I0(slv_reg_wren__0),
        .I1(s00_axi_wstrb[3]),
        .I2(p_0_in[0]),
        .I3(p_0_in[1]),
        .I4(p_0_in[2]),
        .I5(p_0_in[3]),
        .O(\ADC_MASTER_CHANNEL[31]_i_1_n_0 ));
  LUT6 #(
    .INIT(64'h0000000000008000)) 
    \ADC_MASTER_CHANNEL[7]_i_1 
       (.I0(slv_reg_wren__0),
        .I1(s00_axi_wstrb[0]),
        .I2(p_0_in[0]),
        .I3(p_0_in[1]),
        .I4(p_0_in[2]),
        .I5(p_0_in[3]),
        .O(\ADC_MASTER_CHANNEL[7]_i_1_n_0 ));
  FDRE \ADC_MASTER_CHANNEL_reg[0] 
       (.C(s00_axi_aclk),
        .CE(\ADC_MASTER_CHANNEL[7]_i_1_n_0 ),
        .D(s00_axi_wdata[0]),
        .Q(S_ADC_MASTER_CHANNEL),
        .R(RSTP));
  FDRE \ADC_MASTER_CHANNEL_reg[10] 
       (.C(s00_axi_aclk),
        .CE(\ADC_MASTER_CHANNEL[15]_i_1_n_0 ),
        .D(s00_axi_wdata[10]),
        .Q(\ADC_MASTER_CHANNEL_reg_n_0_[10] ),
        .R(RSTP));
  FDRE \ADC_MASTER_CHANNEL_reg[11] 
       (.C(s00_axi_aclk),
        .CE(\ADC_MASTER_CHANNEL[15]_i_1_n_0 ),
        .D(s00_axi_wdata[11]),
        .Q(\ADC_MASTER_CHANNEL_reg_n_0_[11] ),
        .R(RSTP));
  FDRE \ADC_MASTER_CHANNEL_reg[12] 
       (.C(s00_axi_aclk),
        .CE(\ADC_MASTER_CHANNEL[15]_i_1_n_0 ),
        .D(s00_axi_wdata[12]),
        .Q(\ADC_MASTER_CHANNEL_reg_n_0_[12] ),
        .R(RSTP));
  FDRE \ADC_MASTER_CHANNEL_reg[13] 
       (.C(s00_axi_aclk),
        .CE(\ADC_MASTER_CHANNEL[15]_i_1_n_0 ),
        .D(s00_axi_wdata[13]),
        .Q(\ADC_MASTER_CHANNEL_reg_n_0_[13] ),
        .R(RSTP));
  FDRE \ADC_MASTER_CHANNEL_reg[14] 
       (.C(s00_axi_aclk),
        .CE(\ADC_MASTER_CHANNEL[15]_i_1_n_0 ),
        .D(s00_axi_wdata[14]),
        .Q(\ADC_MASTER_CHANNEL_reg_n_0_[14] ),
        .R(RSTP));
  FDRE \ADC_MASTER_CHANNEL_reg[15] 
       (.C(s00_axi_aclk),
        .CE(\ADC_MASTER_CHANNEL[15]_i_1_n_0 ),
        .D(s00_axi_wdata[15]),
        .Q(\ADC_MASTER_CHANNEL_reg_n_0_[15] ),
        .R(RSTP));
  FDRE \ADC_MASTER_CHANNEL_reg[16] 
       (.C(s00_axi_aclk),
        .CE(\ADC_MASTER_CHANNEL[23]_i_1_n_0 ),
        .D(s00_axi_wdata[16]),
        .Q(\ADC_MASTER_CHANNEL_reg_n_0_[16] ),
        .R(RSTP));
  FDRE \ADC_MASTER_CHANNEL_reg[17] 
       (.C(s00_axi_aclk),
        .CE(\ADC_MASTER_CHANNEL[23]_i_1_n_0 ),
        .D(s00_axi_wdata[17]),
        .Q(\ADC_MASTER_CHANNEL_reg_n_0_[17] ),
        .R(RSTP));
  FDRE \ADC_MASTER_CHANNEL_reg[18] 
       (.C(s00_axi_aclk),
        .CE(\ADC_MASTER_CHANNEL[23]_i_1_n_0 ),
        .D(s00_axi_wdata[18]),
        .Q(\ADC_MASTER_CHANNEL_reg_n_0_[18] ),
        .R(RSTP));
  FDRE \ADC_MASTER_CHANNEL_reg[19] 
       (.C(s00_axi_aclk),
        .CE(\ADC_MASTER_CHANNEL[23]_i_1_n_0 ),
        .D(s00_axi_wdata[19]),
        .Q(\ADC_MASTER_CHANNEL_reg_n_0_[19] ),
        .R(RSTP));
  FDRE \ADC_MASTER_CHANNEL_reg[1] 
       (.C(s00_axi_aclk),
        .CE(\ADC_MASTER_CHANNEL[7]_i_1_n_0 ),
        .D(s00_axi_wdata[1]),
        .Q(\ADC_MASTER_CHANNEL_reg_n_0_[1] ),
        .R(RSTP));
  FDRE \ADC_MASTER_CHANNEL_reg[20] 
       (.C(s00_axi_aclk),
        .CE(\ADC_MASTER_CHANNEL[23]_i_1_n_0 ),
        .D(s00_axi_wdata[20]),
        .Q(\ADC_MASTER_CHANNEL_reg_n_0_[20] ),
        .R(RSTP));
  FDRE \ADC_MASTER_CHANNEL_reg[21] 
       (.C(s00_axi_aclk),
        .CE(\ADC_MASTER_CHANNEL[23]_i_1_n_0 ),
        .D(s00_axi_wdata[21]),
        .Q(\ADC_MASTER_CHANNEL_reg_n_0_[21] ),
        .R(RSTP));
  FDRE \ADC_MASTER_CHANNEL_reg[22] 
       (.C(s00_axi_aclk),
        .CE(\ADC_MASTER_CHANNEL[23]_i_1_n_0 ),
        .D(s00_axi_wdata[22]),
        .Q(\ADC_MASTER_CHANNEL_reg_n_0_[22] ),
        .R(RSTP));
  FDRE \ADC_MASTER_CHANNEL_reg[23] 
       (.C(s00_axi_aclk),
        .CE(\ADC_MASTER_CHANNEL[23]_i_1_n_0 ),
        .D(s00_axi_wdata[23]),
        .Q(\ADC_MASTER_CHANNEL_reg_n_0_[23] ),
        .R(RSTP));
  FDRE \ADC_MASTER_CHANNEL_reg[24] 
       (.C(s00_axi_aclk),
        .CE(\ADC_MASTER_CHANNEL[31]_i_1_n_0 ),
        .D(s00_axi_wdata[24]),
        .Q(\ADC_MASTER_CHANNEL_reg_n_0_[24] ),
        .R(RSTP));
  FDRE \ADC_MASTER_CHANNEL_reg[25] 
       (.C(s00_axi_aclk),
        .CE(\ADC_MASTER_CHANNEL[31]_i_1_n_0 ),
        .D(s00_axi_wdata[25]),
        .Q(\ADC_MASTER_CHANNEL_reg_n_0_[25] ),
        .R(RSTP));
  FDRE \ADC_MASTER_CHANNEL_reg[26] 
       (.C(s00_axi_aclk),
        .CE(\ADC_MASTER_CHANNEL[31]_i_1_n_0 ),
        .D(s00_axi_wdata[26]),
        .Q(\ADC_MASTER_CHANNEL_reg_n_0_[26] ),
        .R(RSTP));
  FDRE \ADC_MASTER_CHANNEL_reg[27] 
       (.C(s00_axi_aclk),
        .CE(\ADC_MASTER_CHANNEL[31]_i_1_n_0 ),
        .D(s00_axi_wdata[27]),
        .Q(\ADC_MASTER_CHANNEL_reg_n_0_[27] ),
        .R(RSTP));
  FDRE \ADC_MASTER_CHANNEL_reg[28] 
       (.C(s00_axi_aclk),
        .CE(\ADC_MASTER_CHANNEL[31]_i_1_n_0 ),
        .D(s00_axi_wdata[28]),
        .Q(\ADC_MASTER_CHANNEL_reg_n_0_[28] ),
        .R(RSTP));
  FDRE \ADC_MASTER_CHANNEL_reg[29] 
       (.C(s00_axi_aclk),
        .CE(\ADC_MASTER_CHANNEL[31]_i_1_n_0 ),
        .D(s00_axi_wdata[29]),
        .Q(\ADC_MASTER_CHANNEL_reg_n_0_[29] ),
        .R(RSTP));
  FDRE \ADC_MASTER_CHANNEL_reg[2] 
       (.C(s00_axi_aclk),
        .CE(\ADC_MASTER_CHANNEL[7]_i_1_n_0 ),
        .D(s00_axi_wdata[2]),
        .Q(\ADC_MASTER_CHANNEL_reg_n_0_[2] ),
        .R(RSTP));
  FDRE \ADC_MASTER_CHANNEL_reg[30] 
       (.C(s00_axi_aclk),
        .CE(\ADC_MASTER_CHANNEL[31]_i_1_n_0 ),
        .D(s00_axi_wdata[30]),
        .Q(\ADC_MASTER_CHANNEL_reg_n_0_[30] ),
        .R(RSTP));
  FDRE \ADC_MASTER_CHANNEL_reg[31] 
       (.C(s00_axi_aclk),
        .CE(\ADC_MASTER_CHANNEL[31]_i_1_n_0 ),
        .D(s00_axi_wdata[31]),
        .Q(\ADC_MASTER_CHANNEL_reg_n_0_[31] ),
        .R(RSTP));
  FDRE \ADC_MASTER_CHANNEL_reg[3] 
       (.C(s00_axi_aclk),
        .CE(\ADC_MASTER_CHANNEL[7]_i_1_n_0 ),
        .D(s00_axi_wdata[3]),
        .Q(\ADC_MASTER_CHANNEL_reg_n_0_[3] ),
        .R(RSTP));
  FDRE \ADC_MASTER_CHANNEL_reg[4] 
       (.C(s00_axi_aclk),
        .CE(\ADC_MASTER_CHANNEL[7]_i_1_n_0 ),
        .D(s00_axi_wdata[4]),
        .Q(\ADC_MASTER_CHANNEL_reg_n_0_[4] ),
        .R(RSTP));
  FDRE \ADC_MASTER_CHANNEL_reg[5] 
       (.C(s00_axi_aclk),
        .CE(\ADC_MASTER_CHANNEL[7]_i_1_n_0 ),
        .D(s00_axi_wdata[5]),
        .Q(\ADC_MASTER_CHANNEL_reg_n_0_[5] ),
        .R(RSTP));
  FDRE \ADC_MASTER_CHANNEL_reg[6] 
       (.C(s00_axi_aclk),
        .CE(\ADC_MASTER_CHANNEL[7]_i_1_n_0 ),
        .D(s00_axi_wdata[6]),
        .Q(\ADC_MASTER_CHANNEL_reg_n_0_[6] ),
        .R(RSTP));
  FDRE \ADC_MASTER_CHANNEL_reg[7] 
       (.C(s00_axi_aclk),
        .CE(\ADC_MASTER_CHANNEL[7]_i_1_n_0 ),
        .D(s00_axi_wdata[7]),
        .Q(\ADC_MASTER_CHANNEL_reg_n_0_[7] ),
        .R(RSTP));
  FDRE \ADC_MASTER_CHANNEL_reg[8] 
       (.C(s00_axi_aclk),
        .CE(\ADC_MASTER_CHANNEL[15]_i_1_n_0 ),
        .D(s00_axi_wdata[8]),
        .Q(\ADC_MASTER_CHANNEL_reg_n_0_[8] ),
        .R(RSTP));
  FDRE \ADC_MASTER_CHANNEL_reg[9] 
       (.C(s00_axi_aclk),
        .CE(\ADC_MASTER_CHANNEL[15]_i_1_n_0 ),
        .D(s00_axi_wdata[9]),
        .Q(\ADC_MASTER_CHANNEL_reg_n_0_[9] ),
        .R(RSTP));
  FDRE \ADC_MASTER_FINISH_reg[0] 
       (.C(s00_axi_aclk),
        .CE(1'b1),
        .D(RAW_VALID),
        .Q(ADC_MASTER_FINISH),
        .R(RSTP));
  FDRE \ADC_MASTER_SI_FINISH_reg[0] 
       (.C(s00_axi_aclk),
        .CE(1'b1),
        .D(SI_VALID),
        .Q(ADC_MASTER_SI_FINISH),
        .R(RSTP));
  LUT6 #(
    .INIT(64'h0000000800000000)) 
    \ADC_SPI_CFGR[15]_i_1 
       (.I0(slv_reg_wren__0),
        .I1(s00_axi_wstrb[1]),
        .I2(p_0_in[3]),
        .I3(p_0_in[0]),
        .I4(p_0_in[2]),
        .I5(p_0_in[1]),
        .O(p_1_in[15]));
  LUT6 #(
    .INIT(64'h0000000800000000)) 
    \ADC_SPI_CFGR[23]_i_1 
       (.I0(slv_reg_wren__0),
        .I1(s00_axi_wstrb[2]),
        .I2(p_0_in[3]),
        .I3(p_0_in[0]),
        .I4(p_0_in[2]),
        .I5(p_0_in[1]),
        .O(p_1_in[23]));
  LUT6 #(
    .INIT(64'h0000000800000000)) 
    \ADC_SPI_CFGR[31]_i_1 
       (.I0(slv_reg_wren__0),
        .I1(s00_axi_wstrb[3]),
        .I2(p_0_in[3]),
        .I3(p_0_in[0]),
        .I4(p_0_in[2]),
        .I5(p_0_in[1]),
        .O(p_1_in[31]));
  LUT6 #(
    .INIT(64'h0000000800000000)) 
    \ADC_SPI_CFGR[7]_i_1 
       (.I0(slv_reg_wren__0),
        .I1(s00_axi_wstrb[0]),
        .I2(p_0_in[3]),
        .I3(p_0_in[0]),
        .I4(p_0_in[2]),
        .I5(p_0_in[1]),
        .O(p_1_in[7]));
  FDRE \ADC_SPI_CFGR_reg[0] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[7]),
        .D(s00_axi_wdata[0]),
        .Q(Q[0]),
        .R(RSTP));
  FDRE \ADC_SPI_CFGR_reg[10] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[15]),
        .D(s00_axi_wdata[10]),
        .Q(Q[10]),
        .R(RSTP));
  FDRE \ADC_SPI_CFGR_reg[11] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[15]),
        .D(s00_axi_wdata[11]),
        .Q(Q[11]),
        .R(RSTP));
  FDRE \ADC_SPI_CFGR_reg[12] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[15]),
        .D(s00_axi_wdata[12]),
        .Q(Q[12]),
        .R(RSTP));
  FDRE \ADC_SPI_CFGR_reg[13] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[15]),
        .D(s00_axi_wdata[13]),
        .Q(Q[13]),
        .R(RSTP));
  FDRE \ADC_SPI_CFGR_reg[14] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[15]),
        .D(s00_axi_wdata[14]),
        .Q(Q[14]),
        .R(RSTP));
  FDRE \ADC_SPI_CFGR_reg[15] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[15]),
        .D(s00_axi_wdata[15]),
        .Q(Q[15]),
        .R(RSTP));
  FDRE \ADC_SPI_CFGR_reg[16] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[23]),
        .D(s00_axi_wdata[16]),
        .Q(Q[16]),
        .R(RSTP));
  FDRE \ADC_SPI_CFGR_reg[17] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[23]),
        .D(s00_axi_wdata[17]),
        .Q(Q[17]),
        .R(RSTP));
  FDRE \ADC_SPI_CFGR_reg[18] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[23]),
        .D(s00_axi_wdata[18]),
        .Q(Q[18]),
        .R(RSTP));
  FDRE \ADC_SPI_CFGR_reg[19] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[23]),
        .D(s00_axi_wdata[19]),
        .Q(Q[19]),
        .R(RSTP));
  FDRE \ADC_SPI_CFGR_reg[1] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[7]),
        .D(s00_axi_wdata[1]),
        .Q(Q[1]),
        .R(RSTP));
  FDRE \ADC_SPI_CFGR_reg[20] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[23]),
        .D(s00_axi_wdata[20]),
        .Q(Q[20]),
        .R(RSTP));
  FDRE \ADC_SPI_CFGR_reg[21] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[23]),
        .D(s00_axi_wdata[21]),
        .Q(Q[21]),
        .R(RSTP));
  FDRE \ADC_SPI_CFGR_reg[22] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[23]),
        .D(s00_axi_wdata[22]),
        .Q(Q[22]),
        .R(RSTP));
  FDRE \ADC_SPI_CFGR_reg[23] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[23]),
        .D(s00_axi_wdata[23]),
        .Q(Q[23]),
        .R(RSTP));
  FDRE \ADC_SPI_CFGR_reg[24] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[31]),
        .D(s00_axi_wdata[24]),
        .Q(Q[24]),
        .R(RSTP));
  FDRE \ADC_SPI_CFGR_reg[25] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[31]),
        .D(s00_axi_wdata[25]),
        .Q(Q[25]),
        .R(RSTP));
  FDRE \ADC_SPI_CFGR_reg[26] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[31]),
        .D(s00_axi_wdata[26]),
        .Q(Q[26]),
        .R(RSTP));
  FDRE \ADC_SPI_CFGR_reg[27] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[31]),
        .D(s00_axi_wdata[27]),
        .Q(Q[27]),
        .R(RSTP));
  FDRE \ADC_SPI_CFGR_reg[28] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[31]),
        .D(s00_axi_wdata[28]),
        .Q(Q[28]),
        .R(RSTP));
  FDRE \ADC_SPI_CFGR_reg[29] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[31]),
        .D(s00_axi_wdata[29]),
        .Q(Q[29]),
        .R(RSTP));
  FDRE \ADC_SPI_CFGR_reg[2] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[7]),
        .D(s00_axi_wdata[2]),
        .Q(Q[2]),
        .R(RSTP));
  FDRE \ADC_SPI_CFGR_reg[30] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[31]),
        .D(s00_axi_wdata[30]),
        .Q(Q[30]),
        .R(RSTP));
  FDRE \ADC_SPI_CFGR_reg[31] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[31]),
        .D(s00_axi_wdata[31]),
        .Q(Q[31]),
        .R(RSTP));
  FDRE \ADC_SPI_CFGR_reg[3] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[7]),
        .D(s00_axi_wdata[3]),
        .Q(Q[3]),
        .R(RSTP));
  FDRE \ADC_SPI_CFGR_reg[4] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[7]),
        .D(s00_axi_wdata[4]),
        .Q(Q[4]),
        .R(RSTP));
  FDRE \ADC_SPI_CFGR_reg[5] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[7]),
        .D(s00_axi_wdata[5]),
        .Q(Q[5]),
        .R(RSTP));
  FDRE \ADC_SPI_CFGR_reg[6] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[7]),
        .D(s00_axi_wdata[6]),
        .Q(Q[6]),
        .R(RSTP));
  FDRE \ADC_SPI_CFGR_reg[7] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[7]),
        .D(s00_axi_wdata[7]),
        .Q(Q[7]),
        .R(RSTP));
  FDRE \ADC_SPI_CFGR_reg[8] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[15]),
        .D(s00_axi_wdata[8]),
        .Q(Q[8]),
        .R(RSTP));
  FDRE \ADC_SPI_CFGR_reg[9] 
       (.C(s00_axi_aclk),
        .CE(p_1_in[15]),
        .D(s00_axi_wdata[9]),
        .Q(Q[9]),
        .R(RSTP));
  LUT3 #(
    .INIT(8'h8A)) 
    \ADC_SPI_CR[15]_i_1 
       (.I0(ADC_SPI_CR[15]),
        .I1(\ADC_CR_reg[3]_0 ),
        .I2(s00_axi_aresetn),
        .O(\ADC_SPI_CR[15]_i_1_n_0 ));
  LUT6 #(
    .INIT(64'h20000000FFFFFFFF)) 
    \ADC_SPI_CR[15]_i_2 
       (.I0(\ADC_SPI_CR[31]_i_3_n_0 ),
        .I1(p_0_in[1]),
        .I2(p_0_in[0]),
        .I3(s00_axi_wstrb[1]),
        .I4(slv_reg_wren__0),
        .I5(S_AXI_ARESETN),
        .O(ADC_SPI_CR[15]));
  (* SOFT_HLUTNM = "soft_lutpair30" *) 
  LUT3 #(
    .INIT(8'h40)) 
    \ADC_SPI_CR[1]_i_1 
       (.I0(\ADC_CR_reg[3]_0 ),
        .I1(s00_axi_aresetn),
        .I2(\ADC_SPI_CR_reg[3]_0 [0]),
        .O(ADC_SPI_CR0_in[1]));
  LUT3 #(
    .INIT(8'h8A)) 
    \ADC_SPI_CR[23]_i_1 
       (.I0(ADC_SPI_CR[23]),
        .I1(\ADC_CR_reg[3]_0 ),
        .I2(s00_axi_aresetn),
        .O(\ADC_SPI_CR[23]_i_1_n_0 ));
  LUT6 #(
    .INIT(64'h20000000FFFFFFFF)) 
    \ADC_SPI_CR[23]_i_2 
       (.I0(\ADC_SPI_CR[31]_i_3_n_0 ),
        .I1(p_0_in[1]),
        .I2(p_0_in[0]),
        .I3(s00_axi_wstrb[2]),
        .I4(slv_reg_wren__0),
        .I5(S_AXI_ARESETN),
        .O(ADC_SPI_CR[23]));
  LUT3 #(
    .INIT(8'h8A)) 
    \ADC_SPI_CR[31]_i_1 
       (.I0(ADC_SPI_CR[31]),
        .I1(\ADC_CR_reg[3]_0 ),
        .I2(s00_axi_aresetn),
        .O(\ADC_SPI_CR[31]_i_1_n_0 ));
  LUT6 #(
    .INIT(64'h20000000FFFFFFFF)) 
    \ADC_SPI_CR[31]_i_2 
       (.I0(\ADC_SPI_CR[31]_i_3_n_0 ),
        .I1(p_0_in[1]),
        .I2(p_0_in[0]),
        .I3(s00_axi_wstrb[3]),
        .I4(slv_reg_wren__0),
        .I5(S_AXI_ARESETN),
        .O(ADC_SPI_CR[31]));
  LUT2 #(
    .INIT(4'h1)) 
    \ADC_SPI_CR[31]_i_3 
       (.I0(p_0_in[2]),
        .I1(p_0_in[3]),
        .O(\ADC_SPI_CR[31]_i_3_n_0 ));
  LUT4 #(
    .INIT(16'h8000)) 
    \ADC_SPI_CR[31]_i_4 
       (.I0(axi_awready_reg_0),
        .I1(axi_wready_reg_0),
        .I2(s00_axi_wvalid),
        .I3(s00_axi_awvalid),
        .O(slv_reg_wren__0));
  (* SOFT_HLUTNM = "soft_lutpair0" *) 
  LUT2 #(
    .INIT(4'h2)) 
    \ADC_SPI_CR[31]_i_5 
       (.I0(s00_axi_aresetn),
        .I1(\ADC_CR_reg[3]_0 ),
        .O(S_AXI_ARESETN));
  (* SOFT_HLUTNM = "soft_lutpair30" *) 
  LUT3 #(
    .INIT(8'h40)) 
    \ADC_SPI_CR[3]_i_1 
       (.I0(\ADC_CR_reg[3]_0 ),
        .I1(s00_axi_aresetn),
        .I2(\ADC_SPI_CR_reg[3]_0 [1]),
        .O(ADC_SPI_CR0_in[3]));
  LUT3 #(
    .INIT(8'h40)) 
    \ADC_SPI_CR[5]_i_1 
       (.I0(\ADC_CR_reg[3]_0 ),
        .I1(s00_axi_aresetn),
        .I2(\ADC_SPI_CR_reg[5]_0 ),
        .O(ADC_SPI_CR0_in[5]));
  (* SOFT_HLUTNM = "soft_lutpair0" *) 
  LUT5 #(
    .INIT(32'hEFFFEF00)) 
    \ADC_SPI_CR[6]_i_1 
       (.I0(s00_axi_wdata[6]),
        .I1(\ADC_CR_reg[3]_0 ),
        .I2(s00_axi_aresetn),
        .I3(ADC_SPI_CR[7]),
        .I4(CPOL),
        .O(\ADC_SPI_CR[6]_i_1_n_0 ));
  LUT1 #(
    .INIT(2'h1)) 
    \ADC_SPI_CR[7]_i_1 
       (.I0(S_AXI_ARESETN),
        .O(\ADC_SPI_CR[7]_i_1_n_0 ));
  LUT6 #(
    .INIT(64'h20000000FFFFFFFF)) 
    \ADC_SPI_CR[7]_i_2 
       (.I0(\ADC_SPI_CR[31]_i_3_n_0 ),
        .I1(p_0_in[1]),
        .I2(p_0_in[0]),
        .I3(s00_axi_wstrb[0]),
        .I4(slv_reg_wren__0),
        .I5(S_AXI_ARESETN),
        .O(ADC_SPI_CR[7]));
  FDRE \ADC_SPI_CR_reg[0] 
       (.C(s00_axi_aclk),
        .CE(ADC_SPI_CR[7]),
        .D(s00_axi_wdata[0]),
        .Q(D[0]),
        .R(\ADC_SPI_CR[7]_i_1_n_0 ));
  FDRE \ADC_SPI_CR_reg[10] 
       (.C(s00_axi_aclk),
        .CE(ADC_SPI_CR[15]),
        .D(s00_axi_wdata[10]),
        .Q(\ADC_SPI_CR_reg_n_0_[10] ),
        .R(\ADC_SPI_CR[15]_i_1_n_0 ));
  FDRE \ADC_SPI_CR_reg[11] 
       (.C(s00_axi_aclk),
        .CE(ADC_SPI_CR[15]),
        .D(s00_axi_wdata[11]),
        .Q(\ADC_SPI_CR_reg_n_0_[11] ),
        .R(\ADC_SPI_CR[15]_i_1_n_0 ));
  FDRE \ADC_SPI_CR_reg[12] 
       (.C(s00_axi_aclk),
        .CE(ADC_SPI_CR[15]),
        .D(s00_axi_wdata[12]),
        .Q(\ADC_SPI_CR_reg_n_0_[12] ),
        .R(\ADC_SPI_CR[15]_i_1_n_0 ));
  FDRE \ADC_SPI_CR_reg[13] 
       (.C(s00_axi_aclk),
        .CE(ADC_SPI_CR[15]),
        .D(s00_axi_wdata[13]),
        .Q(\ADC_SPI_CR_reg_n_0_[13] ),
        .R(\ADC_SPI_CR[15]_i_1_n_0 ));
  FDRE \ADC_SPI_CR_reg[14] 
       (.C(s00_axi_aclk),
        .CE(ADC_SPI_CR[15]),
        .D(s00_axi_wdata[14]),
        .Q(\ADC_SPI_CR_reg_n_0_[14] ),
        .R(\ADC_SPI_CR[15]_i_1_n_0 ));
  FDRE \ADC_SPI_CR_reg[15] 
       (.C(s00_axi_aclk),
        .CE(ADC_SPI_CR[15]),
        .D(s00_axi_wdata[15]),
        .Q(\ADC_SPI_CR_reg_n_0_[15] ),
        .R(\ADC_SPI_CR[15]_i_1_n_0 ));
  FDRE \ADC_SPI_CR_reg[16] 
       (.C(s00_axi_aclk),
        .CE(ADC_SPI_CR[23]),
        .D(s00_axi_wdata[16]),
        .Q(\ADC_SPI_CR_reg_n_0_[16] ),
        .R(\ADC_SPI_CR[23]_i_1_n_0 ));
  FDRE \ADC_SPI_CR_reg[17] 
       (.C(s00_axi_aclk),
        .CE(ADC_SPI_CR[23]),
        .D(s00_axi_wdata[17]),
        .Q(\ADC_SPI_CR_reg_n_0_[17] ),
        .R(\ADC_SPI_CR[23]_i_1_n_0 ));
  FDRE \ADC_SPI_CR_reg[18] 
       (.C(s00_axi_aclk),
        .CE(ADC_SPI_CR[23]),
        .D(s00_axi_wdata[18]),
        .Q(\ADC_SPI_CR_reg_n_0_[18] ),
        .R(\ADC_SPI_CR[23]_i_1_n_0 ));
  FDRE \ADC_SPI_CR_reg[19] 
       (.C(s00_axi_aclk),
        .CE(ADC_SPI_CR[23]),
        .D(s00_axi_wdata[19]),
        .Q(\ADC_SPI_CR_reg_n_0_[19] ),
        .R(\ADC_SPI_CR[23]_i_1_n_0 ));
  FDRE \ADC_SPI_CR_reg[1] 
       (.C(s00_axi_aclk),
        .CE(1'b1),
        .D(ADC_SPI_CR0_in[1]),
        .Q(\ADC_SPI_CR_reg_n_0_[1] ),
        .R(1'b0));
  FDRE \ADC_SPI_CR_reg[20] 
       (.C(s00_axi_aclk),
        .CE(ADC_SPI_CR[23]),
        .D(s00_axi_wdata[20]),
        .Q(\ADC_SPI_CR_reg_n_0_[20] ),
        .R(\ADC_SPI_CR[23]_i_1_n_0 ));
  FDRE \ADC_SPI_CR_reg[21] 
       (.C(s00_axi_aclk),
        .CE(ADC_SPI_CR[23]),
        .D(s00_axi_wdata[21]),
        .Q(\ADC_SPI_CR_reg_n_0_[21] ),
        .R(\ADC_SPI_CR[23]_i_1_n_0 ));
  FDRE \ADC_SPI_CR_reg[22] 
       (.C(s00_axi_aclk),
        .CE(ADC_SPI_CR[23]),
        .D(s00_axi_wdata[22]),
        .Q(\ADC_SPI_CR_reg_n_0_[22] ),
        .R(\ADC_SPI_CR[23]_i_1_n_0 ));
  FDRE \ADC_SPI_CR_reg[23] 
       (.C(s00_axi_aclk),
        .CE(ADC_SPI_CR[23]),
        .D(s00_axi_wdata[23]),
        .Q(\ADC_SPI_CR_reg_n_0_[23] ),
        .R(\ADC_SPI_CR[23]_i_1_n_0 ));
  FDRE \ADC_SPI_CR_reg[24] 
       (.C(s00_axi_aclk),
        .CE(ADC_SPI_CR[31]),
        .D(s00_axi_wdata[24]),
        .Q(\ADC_SPI_CR_reg_n_0_[24] ),
        .R(\ADC_SPI_CR[31]_i_1_n_0 ));
  FDRE \ADC_SPI_CR_reg[25] 
       (.C(s00_axi_aclk),
        .CE(ADC_SPI_CR[31]),
        .D(s00_axi_wdata[25]),
        .Q(\ADC_SPI_CR_reg_n_0_[25] ),
        .R(\ADC_SPI_CR[31]_i_1_n_0 ));
  FDRE \ADC_SPI_CR_reg[26] 
       (.C(s00_axi_aclk),
        .CE(ADC_SPI_CR[31]),
        .D(s00_axi_wdata[26]),
        .Q(\ADC_SPI_CR_reg_n_0_[26] ),
        .R(\ADC_SPI_CR[31]_i_1_n_0 ));
  FDRE \ADC_SPI_CR_reg[27] 
       (.C(s00_axi_aclk),
        .CE(ADC_SPI_CR[31]),
        .D(s00_axi_wdata[27]),
        .Q(\ADC_SPI_CR_reg_n_0_[27] ),
        .R(\ADC_SPI_CR[31]_i_1_n_0 ));
  FDRE \ADC_SPI_CR_reg[28] 
       (.C(s00_axi_aclk),
        .CE(ADC_SPI_CR[31]),
        .D(s00_axi_wdata[28]),
        .Q(\ADC_SPI_CR_reg_n_0_[28] ),
        .R(\ADC_SPI_CR[31]_i_1_n_0 ));
  FDRE \ADC_SPI_CR_reg[29] 
       (.C(s00_axi_aclk),
        .CE(ADC_SPI_CR[31]),
        .D(s00_axi_wdata[29]),
        .Q(\ADC_SPI_CR_reg_n_0_[29] ),
        .R(\ADC_SPI_CR[31]_i_1_n_0 ));
  FDRE \ADC_SPI_CR_reg[2] 
       (.C(s00_axi_aclk),
        .CE(ADC_SPI_CR[7]),
        .D(s00_axi_wdata[2]),
        .Q(D[1]),
        .R(\ADC_SPI_CR[7]_i_1_n_0 ));
  FDRE \ADC_SPI_CR_reg[30] 
       (.C(s00_axi_aclk),
        .CE(ADC_SPI_CR[31]),
        .D(s00_axi_wdata[30]),
        .Q(\ADC_SPI_CR_reg_n_0_[30] ),
        .R(\ADC_SPI_CR[31]_i_1_n_0 ));
  FDRE \ADC_SPI_CR_reg[31] 
       (.C(s00_axi_aclk),
        .CE(ADC_SPI_CR[31]),
        .D(s00_axi_wdata[31]),
        .Q(\ADC_SPI_CR_reg_n_0_[31] ),
        .R(\ADC_SPI_CR[31]_i_1_n_0 ));
  FDRE \ADC_SPI_CR_reg[3] 
       (.C(s00_axi_aclk),
        .CE(1'b1),
        .D(ADC_SPI_CR0_in[3]),
        .Q(\ADC_SPI_CR_reg_n_0_[3] ),
        .R(1'b0));
  FDRE \ADC_SPI_CR_reg[4] 
       (.C(s00_axi_aclk),
        .CE(ADC_SPI_CR[7]),
        .D(s00_axi_wdata[4]),
        .Q(p_0_in13_in),
        .R(\ADC_SPI_CR[7]_i_1_n_0 ));
  FDRE \ADC_SPI_CR_reg[5] 
       (.C(s00_axi_aclk),
        .CE(1'b1),
        .D(ADC_SPI_CR0_in[5]),
        .Q(\ADC_SPI_CR_reg_n_0_[5] ),
        .R(1'b0));
  FDRE \ADC_SPI_CR_reg[6] 
       (.C(s00_axi_aclk),
        .CE(1'b1),
        .D(\ADC_SPI_CR[6]_i_1_n_0 ),
        .Q(CPOL),
        .R(1'b0));
  FDRE \ADC_SPI_CR_reg[7] 
       (.C(s00_axi_aclk),
        .CE(ADC_SPI_CR[7]),
        .D(s00_axi_wdata[7]),
        .Q(CPHA),
        .R(\ADC_SPI_CR[7]_i_1_n_0 ));
  FDRE \ADC_SPI_CR_reg[8] 
       (.C(s00_axi_aclk),
        .CE(ADC_SPI_CR[15]),
        .D(s00_axi_wdata[8]),
        .Q(\ADC_SPI_CR_reg_n_0_[8] ),
        .R(\ADC_SPI_CR[15]_i_1_n_0 ));
  FDRE \ADC_SPI_CR_reg[9] 
       (.C(s00_axi_aclk),
        .CE(ADC_SPI_CR[15]),
        .D(s00_axi_wdata[9]),
        .Q(\ADC_SPI_CR_reg_n_0_[9] ),
        .R(\ADC_SPI_CR[15]_i_1_n_0 ));
  LUT6 #(
    .INIT(64'hFFFFFFDF00000000)) 
    \S_ADC_CR_IN[2]_i_1 
       (.I0(S_ADC_CR[2]),
        .I1(IS_BUSY),
        .I2(S_ADC_CR[1]),
        .I3(nxtstate[0]),
        .I4(nxtstate[1]),
        .I5(P_ADC_CR_IN[0]),
        .O(\ADC_CR_reg[2]_0 ));
  (* SOFT_HLUTNM = "soft_lutpair4" *) 
  LUT2 #(
    .INIT(4'h8)) 
    \S_ADC_CR_IN[2]_i_2 
       (.I0(S_ADC_MASTER_CHANNEL),
        .I1(BUSY),
        .O(IS_BUSY));
  LUT1 #(
    .INIT(2'h1)) 
    \S_ADC_CR_IN[4]_i_1 
       (.I0(S_ADC_CR[4]),
        .O(S_SET_CONVERSION));
  (* SOFT_HLUTNM = "soft_lutpair2" *) 
  LUT4 #(
    .INIT(16'h0400)) 
    \S_ADC_SPI_CR_IN[3]_i_1 
       (.I0(\ADC_CR_reg[3]_0 ),
        .I1(s00_axi_aresetn),
        .I2(nxtstate[0]),
        .I3(nxtstate[1]),
        .O(\ADC_CR_reg[3]_2 ));
  (* SOFT_HLUTNM = "soft_lutpair27" *) 
  LUT2 #(
    .INIT(4'h8)) 
    \S_CONVERSION[107]_i_1 
       (.I0(SET_CONVERSION),
        .I1(S_ADC_CHANNEL[5]),
        .O(\S_SET_CONVERSION_reg[0] [5]));
  (* SOFT_HLUTNM = "soft_lutpair28" *) 
  LUT2 #(
    .INIT(4'h8)) 
    \S_CONVERSION[125]_i_1 
       (.I0(SET_CONVERSION),
        .I1(S_ADC_CHANNEL[6]),
        .O(\S_SET_CONVERSION_reg[0] [6]));
  (* SOFT_HLUTNM = "soft_lutpair29" *) 
  LUT2 #(
    .INIT(4'h8)) 
    \S_CONVERSION[143]_i_1 
       (.I0(SET_CONVERSION),
        .I1(S_ADC_CHANNEL[7]),
        .O(\S_SET_CONVERSION_reg[0] [7]));
  (* SOFT_HLUTNM = "soft_lutpair22" *) 
  LUT2 #(
    .INIT(4'h8)) 
    \S_CONVERSION[17]_i_1 
       (.I0(SET_CONVERSION),
        .I1(S_ADC_CHANNEL[0]),
        .O(\S_SET_CONVERSION_reg[0] [0]));
  (* SOFT_HLUTNM = "soft_lutpair23" *) 
  LUT2 #(
    .INIT(4'h8)) 
    \S_CONVERSION[35]_i_1 
       (.I0(SET_CONVERSION),
        .I1(S_ADC_CHANNEL[1]),
        .O(\S_SET_CONVERSION_reg[0] [1]));
  (* SOFT_HLUTNM = "soft_lutpair24" *) 
  LUT2 #(
    .INIT(4'h8)) 
    \S_CONVERSION[53]_i_1 
       (.I0(SET_CONVERSION),
        .I1(S_ADC_CHANNEL[2]),
        .O(\S_SET_CONVERSION_reg[0] [2]));
  (* SOFT_HLUTNM = "soft_lutpair25" *) 
  LUT2 #(
    .INIT(4'h8)) 
    \S_CONVERSION[71]_i_1 
       (.I0(SET_CONVERSION),
        .I1(S_ADC_CHANNEL[3]),
        .O(\S_SET_CONVERSION_reg[0] [3]));
  (* SOFT_HLUTNM = "soft_lutpair26" *) 
  LUT2 #(
    .INIT(4'h8)) 
    \S_CONVERSION[89]_i_1 
       (.I0(SET_CONVERSION),
        .I1(S_ADC_CHANNEL[4]),
        .O(\S_SET_CONVERSION_reg[0] [4]));
  LUT6 #(
    .INIT(64'hFFCC00AF00CC00A0)) 
    \S_ENABLE[0]_i_1 
       (.I0(\S_ENABLE[0]_i_2_n_0 ),
        .I1(S_ENABLE0__4),
        .I2(\S_ENABLE[0]_i_4_n_0 ),
        .I3(nxtstate[1]),
        .I4(nxtstate[0]),
        .I5(ENABLE),
        .O(\S_ENABLE_reg[0] ));
  LUT6 #(
    .INIT(64'h808000008F800000)) 
    \S_ENABLE[0]_i_2 
       (.I0(S_ADC_CR[2]),
        .I1(S_ADC_MASTER_CHANNEL),
        .I2(S_ADC_CR[1]),
        .I3(TRIGGER_CNV),
        .I4(S_ADC_AVAILABLE),
        .I5(S_TRIGGER_CNV_PIPE),
        .O(\S_ENABLE[0]_i_2_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair5" *) 
  LUT2 #(
    .INIT(4'h8)) 
    \S_ENABLE[0]_i_3 
       (.I0(S_ADC_MASTER_CHANNEL),
        .I1(S_ADC_AVAILABLE),
        .O(S_ENABLE0__4));
  (* SOFT_HLUTNM = "soft_lutpair5" *) 
  LUT4 #(
    .INIT(16'h7FFF)) 
    \S_ENABLE[0]_i_4 
       (.I0(S_ADC_MASTER_CHANNEL),
        .I1(BUSY),
        .I2(S_ADC_CR[2]),
        .I3(S_ADC_CR[1]),
        .O(\S_ENABLE[0]_i_4_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair28" *) 
  LUT3 #(
    .INIT(8'h08)) 
    \S_OFFSET[111]_i_1 
       (.I0(S_ADC_CHANNEL[6]),
        .I1(SET_OFFSET),
        .I2(SET_CONVERSION),
        .O(\ADC_CHANNEL_reg[7]_0 [6]));
  (* SOFT_HLUTNM = "soft_lutpair29" *) 
  LUT3 #(
    .INIT(8'h08)) 
    \S_OFFSET[127]_i_1 
       (.I0(S_ADC_CHANNEL[7]),
        .I1(SET_OFFSET),
        .I2(SET_CONVERSION),
        .O(\ADC_CHANNEL_reg[7]_0 [7]));
  (* SOFT_HLUTNM = "soft_lutpair22" *) 
  LUT3 #(
    .INIT(8'h08)) 
    \S_OFFSET[15]_i_1 
       (.I0(S_ADC_CHANNEL[0]),
        .I1(SET_OFFSET),
        .I2(SET_CONVERSION),
        .O(\ADC_CHANNEL_reg[7]_0 [0]));
  (* SOFT_HLUTNM = "soft_lutpair23" *) 
  LUT3 #(
    .INIT(8'h08)) 
    \S_OFFSET[31]_i_1 
       (.I0(S_ADC_CHANNEL[1]),
        .I1(SET_OFFSET),
        .I2(SET_CONVERSION),
        .O(\ADC_CHANNEL_reg[7]_0 [1]));
  (* SOFT_HLUTNM = "soft_lutpair24" *) 
  LUT3 #(
    .INIT(8'h08)) 
    \S_OFFSET[47]_i_1 
       (.I0(S_ADC_CHANNEL[2]),
        .I1(SET_OFFSET),
        .I2(SET_CONVERSION),
        .O(\ADC_CHANNEL_reg[7]_0 [2]));
  (* SOFT_HLUTNM = "soft_lutpair25" *) 
  LUT3 #(
    .INIT(8'h08)) 
    \S_OFFSET[63]_i_1 
       (.I0(S_ADC_CHANNEL[3]),
        .I1(SET_OFFSET),
        .I2(SET_CONVERSION),
        .O(\ADC_CHANNEL_reg[7]_0 [3]));
  (* SOFT_HLUTNM = "soft_lutpair26" *) 
  LUT3 #(
    .INIT(8'h08)) 
    \S_OFFSET[79]_i_1 
       (.I0(S_ADC_CHANNEL[4]),
        .I1(SET_OFFSET),
        .I2(SET_CONVERSION),
        .O(\ADC_CHANNEL_reg[7]_0 [4]));
  (* SOFT_HLUTNM = "soft_lutpair27" *) 
  LUT3 #(
    .INIT(8'h08)) 
    \S_OFFSET[95]_i_1 
       (.I0(S_ADC_CHANNEL[5]),
        .I1(SET_OFFSET),
        .I2(SET_CONVERSION),
        .O(\ADC_CHANNEL_reg[7]_0 [5]));
  LUT2 #(
    .INIT(4'hB)) 
    \S_RX_OUT_BUFFER[127]_i_1 
       (.I0(\ADC_CR_reg[3]_0 ),
        .I1(s00_axi_aresetn),
        .O(RSTP));
  LUT6 #(
    .INIT(64'h0000000001000000)) 
    \S_SAMPLE_TIME[30]_i_1 
       (.I0(SET_CONVERSION),
        .I1(SET_OFFSET),
        .I2(\ADC_CR_reg[3]_0 ),
        .I3(s00_axi_aresetn),
        .I4(SET_SAMPLE_TIME),
        .I5(SET_SAMPLES),
        .O(E));
  (* SOFT_HLUTNM = "soft_lutpair2" *) 
  LUT5 #(
    .INIT(32'h00004000)) 
    \S_SCLK_IN[0]_i_1 
       (.I0(\ADC_CR_reg[3]_0 ),
        .I1(s00_axi_aresetn),
        .I2(nxtstate[1]),
        .I3(S_ADC_MASTER_CHANNEL),
        .I4(nxtstate[0]),
        .O(S_SCLK_IN));
  (* SOFT_HLUTNM = "soft_lutpair1" *) 
  LUT3 #(
    .INIT(8'hBF)) 
    \S_SET_CONVERSION[0]_i_1 
       (.I0(\ADC_CR_reg[3]_0 ),
        .I1(s00_axi_aresetn),
        .I2(S_ADC_CR[4]),
        .O(\ADC_CR_reg[3]_1 ));
  (* SOFT_HLUTNM = "soft_lutpair6" *) 
  LUT4 #(
    .INIT(16'h0008)) 
    \S_SET_CONVERSION[0]_i_2 
       (.I0(S_ADC_MASTER_CHANNEL),
        .I1(S_ADC_CR[5]),
        .I2(S_ADC_CR[6]),
        .I3(S_ADC_CR[7]),
        .O(\ADC_MASTER_CHANNEL_reg[0]_1 ));
  (* SOFT_HLUTNM = "soft_lutpair6" *) 
  LUT4 #(
    .INIT(16'h0010)) 
    \S_SET_OFFSET[0]_i_1 
       (.I0(S_ADC_CR[6]),
        .I1(S_ADC_CR[5]),
        .I2(S_ADC_MASTER_CHANNEL),
        .I3(S_ADC_CR[7]),
        .O(\ADC_CR_reg[6]_0 ));
  (* SOFT_HLUTNM = "soft_lutpair1" *) 
  LUT5 #(
    .INIT(32'hAAAAC0AA)) 
    \S_SET_SAMPLES[0]_i_1 
       (.I0(SET_SAMPLES),
        .I1(\S_SET_SAMPLES[0]_i_2_n_0 ),
        .I2(S_ADC_CR[4]),
        .I3(s00_axi_aresetn),
        .I4(\ADC_CR_reg[3]_0 ),
        .O(\S_SET_SAMPLES_reg[0] ));
  LUT4 #(
    .INIT(16'h0008)) 
    \S_SET_SAMPLES[0]_i_2 
       (.I0(S_ADC_CR[6]),
        .I1(S_ADC_MASTER_CHANNEL),
        .I2(S_ADC_CR[5]),
        .I3(S_ADC_CR[7]),
        .O(\S_SET_SAMPLES[0]_i_2_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair4" *) 
  LUT4 #(
    .INIT(16'h2F20)) 
    \S_SET_SAMPLE_TIME[0]_i_1 
       (.I0(S_ADC_MASTER_CHANNEL),
        .I1(S_ADC_CR[7]),
        .I2(S_SET_SAMPLE_TIME8_out),
        .I3(SET_SAMPLE_TIME),
        .O(\ADC_MASTER_CHANNEL_reg[0]_0 ));
  LUT6 #(
    .INIT(64'h4440404000000000)) 
    \S_SET_SAMPLE_TIME[0]_i_2 
       (.I0(\ADC_CR_reg[3]_0 ),
        .I1(s00_axi_aresetn),
        .I2(S_ADC_CR[7]),
        .I3(S_ADC_CR[6]),
        .I4(S_ADC_CR[5]),
        .I5(S_ADC_CR[4]),
        .O(S_SET_SAMPLE_TIME8_out));
  (* SOFT_HLUTNM = "soft_lutpair3" *) 
  LUT5 #(
    .INIT(32'h0000A020)) 
    \S_SPI_MANUAL[0]_i_1 
       (.I0(S_ADC_MASTER_CHANNEL),
        .I1(BUSY),
        .I2(p_0_in13_in),
        .I3(\curstate_reg[0] [1]),
        .I4(\curstate_reg[0] [0]),
        .O(S_SS_IN_N));
  LUT6 #(
    .INIT(64'hDFFF8AAA8AAA8AAA)) 
    aw_en_i_1
       (.I0(aw_en_reg_n_0),
        .I1(axi_awready_reg_0),
        .I2(s00_axi_awvalid),
        .I3(s00_axi_wvalid),
        .I4(s00_axi_bready),
        .I5(s00_axi_bvalid),
        .O(aw_en_i_1_n_0));
  FDSE aw_en_reg
       (.C(s00_axi_aclk),
        .CE(1'b1),
        .D(aw_en_i_1_n_0),
        .Q(aw_en_reg_n_0),
        .S(RSTP));
  FDSE \axi_araddr_reg[2] 
       (.C(s00_axi_aclk),
        .CE(axi_arready0),
        .D(s00_axi_araddr[0]),
        .Q(sel0[0]),
        .S(RSTP));
  FDSE \axi_araddr_reg[3] 
       (.C(s00_axi_aclk),
        .CE(axi_arready0),
        .D(s00_axi_araddr[1]),
        .Q(sel0[1]),
        .S(RSTP));
  FDSE \axi_araddr_reg[4] 
       (.C(s00_axi_aclk),
        .CE(axi_arready0),
        .D(s00_axi_araddr[2]),
        .Q(sel0[2]),
        .S(RSTP));
  FDSE \axi_araddr_reg[5] 
       (.C(s00_axi_aclk),
        .CE(axi_arready0),
        .D(s00_axi_araddr[3]),
        .Q(sel0[3]),
        .S(RSTP));
  LUT2 #(
    .INIT(4'h2)) 
    axi_arready_i_1
       (.I0(s00_axi_arvalid),
        .I1(axi_arready_reg_0),
        .O(axi_arready0));
  FDRE axi_arready_reg
       (.C(s00_axi_aclk),
        .CE(1'b1),
        .D(axi_arready0),
        .Q(axi_arready_reg_0),
        .R(RSTP));
  FDRE \axi_awaddr_reg[2] 
       (.C(s00_axi_aclk),
        .CE(axi_awready0),
        .D(s00_axi_awaddr[0]),
        .Q(p_0_in[0]),
        .R(RSTP));
  FDRE \axi_awaddr_reg[3] 
       (.C(s00_axi_aclk),
        .CE(axi_awready0),
        .D(s00_axi_awaddr[1]),
        .Q(p_0_in[1]),
        .R(RSTP));
  FDRE \axi_awaddr_reg[4] 
       (.C(s00_axi_aclk),
        .CE(axi_awready0),
        .D(s00_axi_awaddr[2]),
        .Q(p_0_in[2]),
        .R(RSTP));
  FDRE \axi_awaddr_reg[5] 
       (.C(s00_axi_aclk),
        .CE(axi_awready0),
        .D(s00_axi_awaddr[3]),
        .Q(p_0_in[3]),
        .R(RSTP));
  LUT4 #(
    .INIT(16'h0800)) 
    axi_awready_i_1
       (.I0(s00_axi_wvalid),
        .I1(s00_axi_awvalid),
        .I2(axi_awready_reg_0),
        .I3(aw_en_reg_n_0),
        .O(axi_awready0));
  FDRE axi_awready_reg
       (.C(s00_axi_aclk),
        .CE(1'b1),
        .D(axi_awready0),
        .Q(axi_awready_reg_0),
        .R(RSTP));
  LUT6 #(
    .INIT(64'h0000FFFF80008000)) 
    axi_bvalid_i_1
       (.I0(s00_axi_wvalid),
        .I1(s00_axi_awvalid),
        .I2(axi_wready_reg_0),
        .I3(axi_awready_reg_0),
        .I4(s00_axi_bready),
        .I5(s00_axi_bvalid),
        .O(axi_bvalid_i_1_n_0));
  FDRE axi_bvalid_reg
       (.C(s00_axi_aclk),
        .CE(1'b1),
        .D(axi_bvalid_i_1_n_0),
        .Q(s00_axi_bvalid),
        .R(RSTP));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \axi_rdata[0]_i_4 
       (.I0(S_ADC_MASTER_CHANNEL),
        .I1(Q[0]),
        .I2(sel0[1]),
        .I3(D[0]),
        .I4(sel0[0]),
        .I5(S_ADC_CR[0]),
        .O(\axi_rdata[0]_i_4_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \axi_rdata[0]_i_5 
       (.I0(ADC_MASTER_BUSY),
        .I1(ADC_MASTER_SI_FINISH),
        .I2(sel0[1]),
        .I3(ADC_MASTER_FINISH),
        .I4(sel0[0]),
        .I5(S_ADC_CHANNEL[0]),
        .O(\axi_rdata[0]_i_5_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \axi_rdata[0]_i_6 
       (.I0(slv_reg11[0]),
        .I1(slv_reg10[0]),
        .I2(sel0[1]),
        .I3(S_ADC_AVAILABLE),
        .I4(sel0[0]),
        .I5(\ADC_CONV_VALUE_reg[30]_0 [0]),
        .O(\axi_rdata[0]_i_6_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \axi_rdata[0]_i_7 
       (.I0(slv_reg15[0]),
        .I1(slv_reg14[0]),
        .I2(sel0[1]),
        .I3(slv_reg13[0]),
        .I4(sel0[0]),
        .I5(slv_reg12[0]),
        .O(\axi_rdata[0]_i_7_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \axi_rdata[10]_i_1 
       (.I0(\axi_rdata[10]_i_2_n_0 ),
        .I1(\axi_rdata[10]_i_3_n_0 ),
        .I2(sel0[3]),
        .I3(\axi_rdata[10]_i_4_n_0 ),
        .I4(sel0[2]),
        .I5(\axi_rdata[10]_i_5_n_0 ),
        .O(reg_data_out[10]));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \axi_rdata[10]_i_2 
       (.I0(slv_reg15[10]),
        .I1(slv_reg14[10]),
        .I2(sel0[1]),
        .I3(slv_reg13[10]),
        .I4(sel0[0]),
        .I5(slv_reg12[10]),
        .O(\axi_rdata[10]_i_2_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \axi_rdata[10]_i_3 
       (.I0(slv_reg11[10]),
        .I1(slv_reg10[10]),
        .I2(sel0[1]),
        .I3(\ADC_AVAILABLE_reg_n_0_[10] ),
        .I4(sel0[0]),
        .I5(\ADC_CONV_VALUE_reg[30]_0 [10]),
        .O(\axi_rdata[10]_i_3_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair11" *) 
  LUT3 #(
    .INIT(8'h04)) 
    \axi_rdata[10]_i_4 
       (.I0(sel0[0]),
        .I1(S_ADC_CHANNEL[10]),
        .I2(sel0[1]),
        .O(\axi_rdata[10]_i_4_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \axi_rdata[10]_i_5 
       (.I0(\ADC_MASTER_CHANNEL_reg_n_0_[10] ),
        .I1(Q[10]),
        .I2(sel0[1]),
        .I3(\ADC_SPI_CR_reg_n_0_[10] ),
        .I4(sel0[0]),
        .I5(\ADC_CR_reg_n_0_[10] ),
        .O(\axi_rdata[10]_i_5_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \axi_rdata[11]_i_1 
       (.I0(\axi_rdata[11]_i_2_n_0 ),
        .I1(\axi_rdata[11]_i_3_n_0 ),
        .I2(sel0[3]),
        .I3(\axi_rdata[11]_i_4_n_0 ),
        .I4(sel0[2]),
        .I5(\axi_rdata[11]_i_5_n_0 ),
        .O(reg_data_out[11]));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \axi_rdata[11]_i_2 
       (.I0(slv_reg15[11]),
        .I1(slv_reg14[11]),
        .I2(sel0[1]),
        .I3(slv_reg13[11]),
        .I4(sel0[0]),
        .I5(slv_reg12[11]),
        .O(\axi_rdata[11]_i_2_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \axi_rdata[11]_i_3 
       (.I0(slv_reg11[11]),
        .I1(slv_reg10[11]),
        .I2(sel0[1]),
        .I3(\ADC_AVAILABLE_reg_n_0_[11] ),
        .I4(sel0[0]),
        .I5(\ADC_CONV_VALUE_reg[30]_0 [11]),
        .O(\axi_rdata[11]_i_3_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair12" *) 
  LUT3 #(
    .INIT(8'h04)) 
    \axi_rdata[11]_i_4 
       (.I0(sel0[0]),
        .I1(S_ADC_CHANNEL[11]),
        .I2(sel0[1]),
        .O(\axi_rdata[11]_i_4_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \axi_rdata[11]_i_5 
       (.I0(\ADC_MASTER_CHANNEL_reg_n_0_[11] ),
        .I1(Q[11]),
        .I2(sel0[1]),
        .I3(\ADC_SPI_CR_reg_n_0_[11] ),
        .I4(sel0[0]),
        .I5(\ADC_CR_reg_n_0_[11] ),
        .O(\axi_rdata[11]_i_5_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \axi_rdata[12]_i_1 
       (.I0(\axi_rdata[12]_i_2_n_0 ),
        .I1(\axi_rdata[12]_i_3_n_0 ),
        .I2(sel0[3]),
        .I3(\axi_rdata[12]_i_4_n_0 ),
        .I4(sel0[2]),
        .I5(\axi_rdata[12]_i_5_n_0 ),
        .O(reg_data_out[12]));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \axi_rdata[12]_i_2 
       (.I0(slv_reg15[12]),
        .I1(slv_reg14[12]),
        .I2(sel0[1]),
        .I3(slv_reg13[12]),
        .I4(sel0[0]),
        .I5(slv_reg12[12]),
        .O(\axi_rdata[12]_i_2_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \axi_rdata[12]_i_3 
       (.I0(slv_reg11[12]),
        .I1(slv_reg10[12]),
        .I2(sel0[1]),
        .I3(\ADC_AVAILABLE_reg_n_0_[12] ),
        .I4(sel0[0]),
        .I5(\ADC_CONV_VALUE_reg[30]_0 [12]),
        .O(\axi_rdata[12]_i_3_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair12" *) 
  LUT3 #(
    .INIT(8'h04)) 
    \axi_rdata[12]_i_4 
       (.I0(sel0[0]),
        .I1(S_ADC_CHANNEL[12]),
        .I2(sel0[1]),
        .O(\axi_rdata[12]_i_4_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \axi_rdata[12]_i_5 
       (.I0(\ADC_MASTER_CHANNEL_reg_n_0_[12] ),
        .I1(Q[12]),
        .I2(sel0[1]),
        .I3(\ADC_SPI_CR_reg_n_0_[12] ),
        .I4(sel0[0]),
        .I5(\ADC_CR_reg_n_0_[12] ),
        .O(\axi_rdata[12]_i_5_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \axi_rdata[13]_i_1 
       (.I0(\axi_rdata[13]_i_2_n_0 ),
        .I1(\axi_rdata[13]_i_3_n_0 ),
        .I2(sel0[3]),
        .I3(\axi_rdata[13]_i_4_n_0 ),
        .I4(sel0[2]),
        .I5(\axi_rdata[13]_i_5_n_0 ),
        .O(reg_data_out[13]));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \axi_rdata[13]_i_2 
       (.I0(slv_reg15[13]),
        .I1(slv_reg14[13]),
        .I2(sel0[1]),
        .I3(slv_reg13[13]),
        .I4(sel0[0]),
        .I5(slv_reg12[13]),
        .O(\axi_rdata[13]_i_2_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \axi_rdata[13]_i_3 
       (.I0(slv_reg11[13]),
        .I1(slv_reg10[13]),
        .I2(sel0[1]),
        .I3(\ADC_AVAILABLE_reg_n_0_[13] ),
        .I4(sel0[0]),
        .I5(\ADC_CONV_VALUE_reg[30]_0 [13]),
        .O(\axi_rdata[13]_i_3_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair13" *) 
  LUT3 #(
    .INIT(8'h04)) 
    \axi_rdata[13]_i_4 
       (.I0(sel0[0]),
        .I1(S_ADC_CHANNEL[13]),
        .I2(sel0[1]),
        .O(\axi_rdata[13]_i_4_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \axi_rdata[13]_i_5 
       (.I0(\ADC_MASTER_CHANNEL_reg_n_0_[13] ),
        .I1(Q[13]),
        .I2(sel0[1]),
        .I3(\ADC_SPI_CR_reg_n_0_[13] ),
        .I4(sel0[0]),
        .I5(\ADC_CR_reg_n_0_[13] ),
        .O(\axi_rdata[13]_i_5_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \axi_rdata[14]_i_1 
       (.I0(\axi_rdata[14]_i_2_n_0 ),
        .I1(\axi_rdata[14]_i_3_n_0 ),
        .I2(sel0[3]),
        .I3(\axi_rdata[14]_i_4_n_0 ),
        .I4(sel0[2]),
        .I5(\axi_rdata[14]_i_5_n_0 ),
        .O(reg_data_out[14]));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \axi_rdata[14]_i_2 
       (.I0(slv_reg15[14]),
        .I1(slv_reg14[14]),
        .I2(sel0[1]),
        .I3(slv_reg13[14]),
        .I4(sel0[0]),
        .I5(slv_reg12[14]),
        .O(\axi_rdata[14]_i_2_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \axi_rdata[14]_i_3 
       (.I0(slv_reg11[14]),
        .I1(slv_reg10[14]),
        .I2(sel0[1]),
        .I3(\ADC_AVAILABLE_reg_n_0_[14] ),
        .I4(sel0[0]),
        .I5(\ADC_CONV_VALUE_reg[30]_0 [14]),
        .O(\axi_rdata[14]_i_3_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair13" *) 
  LUT3 #(
    .INIT(8'h04)) 
    \axi_rdata[14]_i_4 
       (.I0(sel0[0]),
        .I1(S_ADC_CHANNEL[14]),
        .I2(sel0[1]),
        .O(\axi_rdata[14]_i_4_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \axi_rdata[14]_i_5 
       (.I0(\ADC_MASTER_CHANNEL_reg_n_0_[14] ),
        .I1(Q[14]),
        .I2(sel0[1]),
        .I3(\ADC_SPI_CR_reg_n_0_[14] ),
        .I4(sel0[0]),
        .I5(\ADC_CR_reg_n_0_[14] ),
        .O(\axi_rdata[14]_i_5_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \axi_rdata[15]_i_1 
       (.I0(\axi_rdata[15]_i_2_n_0 ),
        .I1(\axi_rdata[15]_i_3_n_0 ),
        .I2(sel0[3]),
        .I3(\axi_rdata[15]_i_4_n_0 ),
        .I4(sel0[2]),
        .I5(\axi_rdata[15]_i_5_n_0 ),
        .O(reg_data_out[15]));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \axi_rdata[15]_i_2 
       (.I0(slv_reg15[15]),
        .I1(slv_reg14[15]),
        .I2(sel0[1]),
        .I3(slv_reg13[15]),
        .I4(sel0[0]),
        .I5(slv_reg12[15]),
        .O(\axi_rdata[15]_i_2_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \axi_rdata[15]_i_3 
       (.I0(slv_reg11[15]),
        .I1(slv_reg10[15]),
        .I2(sel0[1]),
        .I3(\ADC_AVAILABLE_reg_n_0_[15] ),
        .I4(sel0[0]),
        .I5(\ADC_CONV_VALUE_reg[30]_0 [15]),
        .O(\axi_rdata[15]_i_3_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair14" *) 
  LUT3 #(
    .INIT(8'h04)) 
    \axi_rdata[15]_i_4 
       (.I0(sel0[0]),
        .I1(S_ADC_CHANNEL[15]),
        .I2(sel0[1]),
        .O(\axi_rdata[15]_i_4_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \axi_rdata[15]_i_5 
       (.I0(\ADC_MASTER_CHANNEL_reg_n_0_[15] ),
        .I1(Q[15]),
        .I2(sel0[1]),
        .I3(\ADC_SPI_CR_reg_n_0_[15] ),
        .I4(sel0[0]),
        .I5(\ADC_CR_reg_n_0_[15] ),
        .O(\axi_rdata[15]_i_5_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \axi_rdata[16]_i_1 
       (.I0(\axi_rdata[16]_i_2_n_0 ),
        .I1(\axi_rdata[16]_i_3_n_0 ),
        .I2(sel0[3]),
        .I3(\axi_rdata[16]_i_4_n_0 ),
        .I4(sel0[2]),
        .I5(\axi_rdata[16]_i_5_n_0 ),
        .O(reg_data_out[16]));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \axi_rdata[16]_i_2 
       (.I0(slv_reg15[16]),
        .I1(slv_reg14[16]),
        .I2(sel0[1]),
        .I3(slv_reg13[16]),
        .I4(sel0[0]),
        .I5(slv_reg12[16]),
        .O(\axi_rdata[16]_i_2_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \axi_rdata[16]_i_3 
       (.I0(slv_reg11[16]),
        .I1(slv_reg10[16]),
        .I2(sel0[1]),
        .I3(\ADC_AVAILABLE_reg_n_0_[16] ),
        .I4(sel0[0]),
        .I5(\ADC_CONV_VALUE_reg[30]_0 [16]),
        .O(\axi_rdata[16]_i_3_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair14" *) 
  LUT3 #(
    .INIT(8'h04)) 
    \axi_rdata[16]_i_4 
       (.I0(sel0[0]),
        .I1(S_ADC_CHANNEL[16]),
        .I2(sel0[1]),
        .O(\axi_rdata[16]_i_4_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \axi_rdata[16]_i_5 
       (.I0(\ADC_MASTER_CHANNEL_reg_n_0_[16] ),
        .I1(Q[16]),
        .I2(sel0[1]),
        .I3(\ADC_SPI_CR_reg_n_0_[16] ),
        .I4(sel0[0]),
        .I5(\ADC_CR_reg_n_0_[16] ),
        .O(\axi_rdata[16]_i_5_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \axi_rdata[17]_i_1 
       (.I0(\axi_rdata[17]_i_2_n_0 ),
        .I1(\axi_rdata[17]_i_3_n_0 ),
        .I2(sel0[3]),
        .I3(\axi_rdata[17]_i_4_n_0 ),
        .I4(sel0[2]),
        .I5(\axi_rdata[17]_i_5_n_0 ),
        .O(reg_data_out[17]));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \axi_rdata[17]_i_2 
       (.I0(slv_reg15[17]),
        .I1(slv_reg14[17]),
        .I2(sel0[1]),
        .I3(slv_reg13[17]),
        .I4(sel0[0]),
        .I5(slv_reg12[17]),
        .O(\axi_rdata[17]_i_2_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \axi_rdata[17]_i_3 
       (.I0(slv_reg11[17]),
        .I1(slv_reg10[17]),
        .I2(sel0[1]),
        .I3(\ADC_AVAILABLE_reg_n_0_[17] ),
        .I4(sel0[0]),
        .I5(\ADC_CONV_VALUE_reg[30]_0 [17]),
        .O(\axi_rdata[17]_i_3_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair15" *) 
  LUT3 #(
    .INIT(8'h04)) 
    \axi_rdata[17]_i_4 
       (.I0(sel0[0]),
        .I1(S_ADC_CHANNEL[17]),
        .I2(sel0[1]),
        .O(\axi_rdata[17]_i_4_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \axi_rdata[17]_i_5 
       (.I0(\ADC_MASTER_CHANNEL_reg_n_0_[17] ),
        .I1(Q[17]),
        .I2(sel0[1]),
        .I3(\ADC_SPI_CR_reg_n_0_[17] ),
        .I4(sel0[0]),
        .I5(\ADC_CR_reg_n_0_[17] ),
        .O(\axi_rdata[17]_i_5_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \axi_rdata[18]_i_1 
       (.I0(\axi_rdata[18]_i_2_n_0 ),
        .I1(\axi_rdata[18]_i_3_n_0 ),
        .I2(sel0[3]),
        .I3(\axi_rdata[18]_i_4_n_0 ),
        .I4(sel0[2]),
        .I5(\axi_rdata[18]_i_5_n_0 ),
        .O(reg_data_out[18]));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \axi_rdata[18]_i_2 
       (.I0(slv_reg15[18]),
        .I1(slv_reg14[18]),
        .I2(sel0[1]),
        .I3(slv_reg13[18]),
        .I4(sel0[0]),
        .I5(slv_reg12[18]),
        .O(\axi_rdata[18]_i_2_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \axi_rdata[18]_i_3 
       (.I0(slv_reg11[18]),
        .I1(slv_reg10[18]),
        .I2(sel0[1]),
        .I3(\ADC_AVAILABLE_reg_n_0_[18] ),
        .I4(sel0[0]),
        .I5(\ADC_CONV_VALUE_reg[30]_0 [18]),
        .O(\axi_rdata[18]_i_3_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair15" *) 
  LUT3 #(
    .INIT(8'h04)) 
    \axi_rdata[18]_i_4 
       (.I0(sel0[0]),
        .I1(S_ADC_CHANNEL[18]),
        .I2(sel0[1]),
        .O(\axi_rdata[18]_i_4_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \axi_rdata[18]_i_5 
       (.I0(\ADC_MASTER_CHANNEL_reg_n_0_[18] ),
        .I1(Q[18]),
        .I2(sel0[1]),
        .I3(\ADC_SPI_CR_reg_n_0_[18] ),
        .I4(sel0[0]),
        .I5(\ADC_CR_reg_n_0_[18] ),
        .O(\axi_rdata[18]_i_5_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \axi_rdata[19]_i_1 
       (.I0(\axi_rdata[19]_i_2_n_0 ),
        .I1(\axi_rdata[19]_i_3_n_0 ),
        .I2(sel0[3]),
        .I3(\axi_rdata[19]_i_4_n_0 ),
        .I4(sel0[2]),
        .I5(\axi_rdata[19]_i_5_n_0 ),
        .O(reg_data_out[19]));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \axi_rdata[19]_i_2 
       (.I0(slv_reg15[19]),
        .I1(slv_reg14[19]),
        .I2(sel0[1]),
        .I3(slv_reg13[19]),
        .I4(sel0[0]),
        .I5(slv_reg12[19]),
        .O(\axi_rdata[19]_i_2_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \axi_rdata[19]_i_3 
       (.I0(slv_reg11[19]),
        .I1(slv_reg10[19]),
        .I2(sel0[1]),
        .I3(\ADC_AVAILABLE_reg_n_0_[19] ),
        .I4(sel0[0]),
        .I5(\ADC_CONV_VALUE_reg[30]_0 [19]),
        .O(\axi_rdata[19]_i_3_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair16" *) 
  LUT3 #(
    .INIT(8'h04)) 
    \axi_rdata[19]_i_4 
       (.I0(sel0[0]),
        .I1(S_ADC_CHANNEL[19]),
        .I2(sel0[1]),
        .O(\axi_rdata[19]_i_4_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \axi_rdata[19]_i_5 
       (.I0(\ADC_MASTER_CHANNEL_reg_n_0_[19] ),
        .I1(Q[19]),
        .I2(sel0[1]),
        .I3(\ADC_SPI_CR_reg_n_0_[19] ),
        .I4(sel0[0]),
        .I5(\ADC_CR_reg_n_0_[19] ),
        .O(\axi_rdata[19]_i_5_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \axi_rdata[1]_i_1 
       (.I0(\axi_rdata[1]_i_2_n_0 ),
        .I1(\axi_rdata[1]_i_3_n_0 ),
        .I2(sel0[3]),
        .I3(\axi_rdata[1]_i_4_n_0 ),
        .I4(sel0[2]),
        .I5(\axi_rdata[1]_i_5_n_0 ),
        .O(reg_data_out[1]));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \axi_rdata[1]_i_2 
       (.I0(slv_reg15[1]),
        .I1(slv_reg14[1]),
        .I2(sel0[1]),
        .I3(slv_reg13[1]),
        .I4(sel0[0]),
        .I5(slv_reg12[1]),
        .O(\axi_rdata[1]_i_2_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \axi_rdata[1]_i_3 
       (.I0(slv_reg11[1]),
        .I1(slv_reg10[1]),
        .I2(sel0[1]),
        .I3(\ADC_AVAILABLE_reg_n_0_[1] ),
        .I4(sel0[0]),
        .I5(\ADC_CONV_VALUE_reg[30]_0 [1]),
        .O(\axi_rdata[1]_i_3_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair7" *) 
  LUT3 #(
    .INIT(8'h04)) 
    \axi_rdata[1]_i_4 
       (.I0(sel0[0]),
        .I1(S_ADC_CHANNEL[1]),
        .I2(sel0[1]),
        .O(\axi_rdata[1]_i_4_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \axi_rdata[1]_i_5 
       (.I0(\ADC_MASTER_CHANNEL_reg_n_0_[1] ),
        .I1(Q[1]),
        .I2(sel0[1]),
        .I3(\ADC_SPI_CR_reg_n_0_[1] ),
        .I4(sel0[0]),
        .I5(S_ADC_CR[1]),
        .O(\axi_rdata[1]_i_5_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \axi_rdata[20]_i_1 
       (.I0(\axi_rdata[20]_i_2_n_0 ),
        .I1(\axi_rdata[20]_i_3_n_0 ),
        .I2(sel0[3]),
        .I3(\axi_rdata[20]_i_4_n_0 ),
        .I4(sel0[2]),
        .I5(\axi_rdata[20]_i_5_n_0 ),
        .O(reg_data_out[20]));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \axi_rdata[20]_i_2 
       (.I0(slv_reg15[20]),
        .I1(slv_reg14[20]),
        .I2(sel0[1]),
        .I3(slv_reg13[20]),
        .I4(sel0[0]),
        .I5(slv_reg12[20]),
        .O(\axi_rdata[20]_i_2_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \axi_rdata[20]_i_3 
       (.I0(slv_reg11[20]),
        .I1(slv_reg10[20]),
        .I2(sel0[1]),
        .I3(\ADC_AVAILABLE_reg_n_0_[20] ),
        .I4(sel0[0]),
        .I5(\ADC_CONV_VALUE_reg[30]_0 [20]),
        .O(\axi_rdata[20]_i_3_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair16" *) 
  LUT3 #(
    .INIT(8'h04)) 
    \axi_rdata[20]_i_4 
       (.I0(sel0[0]),
        .I1(S_ADC_CHANNEL[20]),
        .I2(sel0[1]),
        .O(\axi_rdata[20]_i_4_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \axi_rdata[20]_i_5 
       (.I0(\ADC_MASTER_CHANNEL_reg_n_0_[20] ),
        .I1(Q[20]),
        .I2(sel0[1]),
        .I3(\ADC_SPI_CR_reg_n_0_[20] ),
        .I4(sel0[0]),
        .I5(\ADC_CR_reg_n_0_[20] ),
        .O(\axi_rdata[20]_i_5_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \axi_rdata[21]_i_1 
       (.I0(\axi_rdata[21]_i_2_n_0 ),
        .I1(\axi_rdata[21]_i_3_n_0 ),
        .I2(sel0[3]),
        .I3(\axi_rdata[21]_i_4_n_0 ),
        .I4(sel0[2]),
        .I5(\axi_rdata[21]_i_5_n_0 ),
        .O(reg_data_out[21]));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \axi_rdata[21]_i_2 
       (.I0(slv_reg15[21]),
        .I1(slv_reg14[21]),
        .I2(sel0[1]),
        .I3(slv_reg13[21]),
        .I4(sel0[0]),
        .I5(slv_reg12[21]),
        .O(\axi_rdata[21]_i_2_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \axi_rdata[21]_i_3 
       (.I0(slv_reg11[21]),
        .I1(slv_reg10[21]),
        .I2(sel0[1]),
        .I3(\ADC_AVAILABLE_reg_n_0_[21] ),
        .I4(sel0[0]),
        .I5(\ADC_CONV_VALUE_reg[30]_0 [21]),
        .O(\axi_rdata[21]_i_3_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair17" *) 
  LUT3 #(
    .INIT(8'h04)) 
    \axi_rdata[21]_i_4 
       (.I0(sel0[0]),
        .I1(S_ADC_CHANNEL[21]),
        .I2(sel0[1]),
        .O(\axi_rdata[21]_i_4_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \axi_rdata[21]_i_5 
       (.I0(\ADC_MASTER_CHANNEL_reg_n_0_[21] ),
        .I1(Q[21]),
        .I2(sel0[1]),
        .I3(\ADC_SPI_CR_reg_n_0_[21] ),
        .I4(sel0[0]),
        .I5(\ADC_CR_reg_n_0_[21] ),
        .O(\axi_rdata[21]_i_5_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \axi_rdata[22]_i_1 
       (.I0(\axi_rdata[22]_i_2_n_0 ),
        .I1(\axi_rdata[22]_i_3_n_0 ),
        .I2(sel0[3]),
        .I3(\axi_rdata[22]_i_4_n_0 ),
        .I4(sel0[2]),
        .I5(\axi_rdata[22]_i_5_n_0 ),
        .O(reg_data_out[22]));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \axi_rdata[22]_i_2 
       (.I0(slv_reg15[22]),
        .I1(slv_reg14[22]),
        .I2(sel0[1]),
        .I3(slv_reg13[22]),
        .I4(sel0[0]),
        .I5(slv_reg12[22]),
        .O(\axi_rdata[22]_i_2_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \axi_rdata[22]_i_3 
       (.I0(slv_reg11[22]),
        .I1(slv_reg10[22]),
        .I2(sel0[1]),
        .I3(\ADC_AVAILABLE_reg_n_0_[22] ),
        .I4(sel0[0]),
        .I5(\ADC_CONV_VALUE_reg[30]_0 [22]),
        .O(\axi_rdata[22]_i_3_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair17" *) 
  LUT3 #(
    .INIT(8'h04)) 
    \axi_rdata[22]_i_4 
       (.I0(sel0[0]),
        .I1(S_ADC_CHANNEL[22]),
        .I2(sel0[1]),
        .O(\axi_rdata[22]_i_4_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \axi_rdata[22]_i_5 
       (.I0(\ADC_MASTER_CHANNEL_reg_n_0_[22] ),
        .I1(Q[22]),
        .I2(sel0[1]),
        .I3(\ADC_SPI_CR_reg_n_0_[22] ),
        .I4(sel0[0]),
        .I5(\ADC_CR_reg_n_0_[22] ),
        .O(\axi_rdata[22]_i_5_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \axi_rdata[23]_i_1 
       (.I0(\axi_rdata[23]_i_2_n_0 ),
        .I1(\axi_rdata[23]_i_3_n_0 ),
        .I2(sel0[3]),
        .I3(\axi_rdata[23]_i_4_n_0 ),
        .I4(sel0[2]),
        .I5(\axi_rdata[23]_i_5_n_0 ),
        .O(reg_data_out[23]));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \axi_rdata[23]_i_2 
       (.I0(slv_reg15[23]),
        .I1(slv_reg14[23]),
        .I2(sel0[1]),
        .I3(slv_reg13[23]),
        .I4(sel0[0]),
        .I5(slv_reg12[23]),
        .O(\axi_rdata[23]_i_2_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \axi_rdata[23]_i_3 
       (.I0(slv_reg11[23]),
        .I1(slv_reg10[23]),
        .I2(sel0[1]),
        .I3(\ADC_AVAILABLE_reg_n_0_[23] ),
        .I4(sel0[0]),
        .I5(\ADC_CONV_VALUE_reg[30]_0 [23]),
        .O(\axi_rdata[23]_i_3_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair18" *) 
  LUT3 #(
    .INIT(8'h04)) 
    \axi_rdata[23]_i_4 
       (.I0(sel0[0]),
        .I1(S_ADC_CHANNEL[23]),
        .I2(sel0[1]),
        .O(\axi_rdata[23]_i_4_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \axi_rdata[23]_i_5 
       (.I0(\ADC_MASTER_CHANNEL_reg_n_0_[23] ),
        .I1(Q[23]),
        .I2(sel0[1]),
        .I3(\ADC_SPI_CR_reg_n_0_[23] ),
        .I4(sel0[0]),
        .I5(\ADC_CR_reg_n_0_[23] ),
        .O(\axi_rdata[23]_i_5_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \axi_rdata[24]_i_1 
       (.I0(\axi_rdata[24]_i_2_n_0 ),
        .I1(\axi_rdata[24]_i_3_n_0 ),
        .I2(sel0[3]),
        .I3(\axi_rdata[24]_i_4_n_0 ),
        .I4(sel0[2]),
        .I5(\axi_rdata[24]_i_5_n_0 ),
        .O(reg_data_out[24]));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \axi_rdata[24]_i_2 
       (.I0(slv_reg15[24]),
        .I1(slv_reg14[24]),
        .I2(sel0[1]),
        .I3(slv_reg13[24]),
        .I4(sel0[0]),
        .I5(slv_reg12[24]),
        .O(\axi_rdata[24]_i_2_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \axi_rdata[24]_i_3 
       (.I0(slv_reg11[24]),
        .I1(slv_reg10[24]),
        .I2(sel0[1]),
        .I3(\ADC_AVAILABLE_reg_n_0_[24] ),
        .I4(sel0[0]),
        .I5(\ADC_CONV_VALUE_reg[30]_0 [24]),
        .O(\axi_rdata[24]_i_3_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair18" *) 
  LUT3 #(
    .INIT(8'h04)) 
    \axi_rdata[24]_i_4 
       (.I0(sel0[0]),
        .I1(S_ADC_CHANNEL[24]),
        .I2(sel0[1]),
        .O(\axi_rdata[24]_i_4_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \axi_rdata[24]_i_5 
       (.I0(\ADC_MASTER_CHANNEL_reg_n_0_[24] ),
        .I1(Q[24]),
        .I2(sel0[1]),
        .I3(\ADC_SPI_CR_reg_n_0_[24] ),
        .I4(sel0[0]),
        .I5(\ADC_CR_reg_n_0_[24] ),
        .O(\axi_rdata[24]_i_5_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \axi_rdata[25]_i_1 
       (.I0(\axi_rdata[25]_i_2_n_0 ),
        .I1(\axi_rdata[25]_i_3_n_0 ),
        .I2(sel0[3]),
        .I3(\axi_rdata[25]_i_4_n_0 ),
        .I4(sel0[2]),
        .I5(\axi_rdata[25]_i_5_n_0 ),
        .O(reg_data_out[25]));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \axi_rdata[25]_i_2 
       (.I0(slv_reg15[25]),
        .I1(slv_reg14[25]),
        .I2(sel0[1]),
        .I3(slv_reg13[25]),
        .I4(sel0[0]),
        .I5(slv_reg12[25]),
        .O(\axi_rdata[25]_i_2_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \axi_rdata[25]_i_3 
       (.I0(slv_reg11[25]),
        .I1(slv_reg10[25]),
        .I2(sel0[1]),
        .I3(\ADC_AVAILABLE_reg_n_0_[25] ),
        .I4(sel0[0]),
        .I5(\ADC_CONV_VALUE_reg[30]_0 [25]),
        .O(\axi_rdata[25]_i_3_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair19" *) 
  LUT3 #(
    .INIT(8'h04)) 
    \axi_rdata[25]_i_4 
       (.I0(sel0[0]),
        .I1(S_ADC_CHANNEL[25]),
        .I2(sel0[1]),
        .O(\axi_rdata[25]_i_4_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \axi_rdata[25]_i_5 
       (.I0(\ADC_MASTER_CHANNEL_reg_n_0_[25] ),
        .I1(Q[25]),
        .I2(sel0[1]),
        .I3(\ADC_SPI_CR_reg_n_0_[25] ),
        .I4(sel0[0]),
        .I5(\ADC_CR_reg_n_0_[25] ),
        .O(\axi_rdata[25]_i_5_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \axi_rdata[26]_i_1 
       (.I0(\axi_rdata[26]_i_2_n_0 ),
        .I1(\axi_rdata[26]_i_3_n_0 ),
        .I2(sel0[3]),
        .I3(\axi_rdata[26]_i_4_n_0 ),
        .I4(sel0[2]),
        .I5(\axi_rdata[26]_i_5_n_0 ),
        .O(reg_data_out[26]));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \axi_rdata[26]_i_2 
       (.I0(slv_reg15[26]),
        .I1(slv_reg14[26]),
        .I2(sel0[1]),
        .I3(slv_reg13[26]),
        .I4(sel0[0]),
        .I5(slv_reg12[26]),
        .O(\axi_rdata[26]_i_2_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \axi_rdata[26]_i_3 
       (.I0(slv_reg11[26]),
        .I1(slv_reg10[26]),
        .I2(sel0[1]),
        .I3(\ADC_AVAILABLE_reg_n_0_[26] ),
        .I4(sel0[0]),
        .I5(\ADC_CONV_VALUE_reg[30]_0 [26]),
        .O(\axi_rdata[26]_i_3_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair19" *) 
  LUT3 #(
    .INIT(8'h04)) 
    \axi_rdata[26]_i_4 
       (.I0(sel0[0]),
        .I1(S_ADC_CHANNEL[26]),
        .I2(sel0[1]),
        .O(\axi_rdata[26]_i_4_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \axi_rdata[26]_i_5 
       (.I0(\ADC_MASTER_CHANNEL_reg_n_0_[26] ),
        .I1(Q[26]),
        .I2(sel0[1]),
        .I3(\ADC_SPI_CR_reg_n_0_[26] ),
        .I4(sel0[0]),
        .I5(\ADC_CR_reg_n_0_[26] ),
        .O(\axi_rdata[26]_i_5_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \axi_rdata[27]_i_1 
       (.I0(\axi_rdata[27]_i_2_n_0 ),
        .I1(\axi_rdata[27]_i_3_n_0 ),
        .I2(sel0[3]),
        .I3(\axi_rdata[27]_i_4_n_0 ),
        .I4(sel0[2]),
        .I5(\axi_rdata[27]_i_5_n_0 ),
        .O(reg_data_out[27]));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \axi_rdata[27]_i_2 
       (.I0(slv_reg15[27]),
        .I1(slv_reg14[27]),
        .I2(sel0[1]),
        .I3(slv_reg13[27]),
        .I4(sel0[0]),
        .I5(slv_reg12[27]),
        .O(\axi_rdata[27]_i_2_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \axi_rdata[27]_i_3 
       (.I0(slv_reg11[27]),
        .I1(slv_reg10[27]),
        .I2(sel0[1]),
        .I3(\ADC_AVAILABLE_reg_n_0_[27] ),
        .I4(sel0[0]),
        .I5(\ADC_CONV_VALUE_reg[30]_0 [27]),
        .O(\axi_rdata[27]_i_3_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair20" *) 
  LUT3 #(
    .INIT(8'h04)) 
    \axi_rdata[27]_i_4 
       (.I0(sel0[0]),
        .I1(S_ADC_CHANNEL[27]),
        .I2(sel0[1]),
        .O(\axi_rdata[27]_i_4_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \axi_rdata[27]_i_5 
       (.I0(\ADC_MASTER_CHANNEL_reg_n_0_[27] ),
        .I1(Q[27]),
        .I2(sel0[1]),
        .I3(\ADC_SPI_CR_reg_n_0_[27] ),
        .I4(sel0[0]),
        .I5(\ADC_CR_reg_n_0_[27] ),
        .O(\axi_rdata[27]_i_5_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \axi_rdata[28]_i_1 
       (.I0(\axi_rdata[28]_i_2_n_0 ),
        .I1(\axi_rdata[28]_i_3_n_0 ),
        .I2(sel0[3]),
        .I3(\axi_rdata[28]_i_4_n_0 ),
        .I4(sel0[2]),
        .I5(\axi_rdata[28]_i_5_n_0 ),
        .O(reg_data_out[28]));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \axi_rdata[28]_i_2 
       (.I0(slv_reg15[28]),
        .I1(slv_reg14[28]),
        .I2(sel0[1]),
        .I3(slv_reg13[28]),
        .I4(sel0[0]),
        .I5(slv_reg12[28]),
        .O(\axi_rdata[28]_i_2_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \axi_rdata[28]_i_3 
       (.I0(slv_reg11[28]),
        .I1(slv_reg10[28]),
        .I2(sel0[1]),
        .I3(\ADC_AVAILABLE_reg_n_0_[28] ),
        .I4(sel0[0]),
        .I5(\ADC_CONV_VALUE_reg[30]_0 [28]),
        .O(\axi_rdata[28]_i_3_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair20" *) 
  LUT3 #(
    .INIT(8'h04)) 
    \axi_rdata[28]_i_4 
       (.I0(sel0[0]),
        .I1(S_ADC_CHANNEL[28]),
        .I2(sel0[1]),
        .O(\axi_rdata[28]_i_4_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \axi_rdata[28]_i_5 
       (.I0(\ADC_MASTER_CHANNEL_reg_n_0_[28] ),
        .I1(Q[28]),
        .I2(sel0[1]),
        .I3(\ADC_SPI_CR_reg_n_0_[28] ),
        .I4(sel0[0]),
        .I5(\ADC_CR_reg_n_0_[28] ),
        .O(\axi_rdata[28]_i_5_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \axi_rdata[29]_i_1 
       (.I0(\axi_rdata[29]_i_2_n_0 ),
        .I1(\axi_rdata[29]_i_3_n_0 ),
        .I2(sel0[3]),
        .I3(\axi_rdata[29]_i_4_n_0 ),
        .I4(sel0[2]),
        .I5(\axi_rdata[29]_i_5_n_0 ),
        .O(reg_data_out[29]));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \axi_rdata[29]_i_2 
       (.I0(slv_reg15[29]),
        .I1(slv_reg14[29]),
        .I2(sel0[1]),
        .I3(slv_reg13[29]),
        .I4(sel0[0]),
        .I5(slv_reg12[29]),
        .O(\axi_rdata[29]_i_2_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \axi_rdata[29]_i_3 
       (.I0(slv_reg11[29]),
        .I1(slv_reg10[29]),
        .I2(sel0[1]),
        .I3(\ADC_AVAILABLE_reg_n_0_[29] ),
        .I4(sel0[0]),
        .I5(\ADC_CONV_VALUE_reg[30]_0 [29]),
        .O(\axi_rdata[29]_i_3_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair21" *) 
  LUT3 #(
    .INIT(8'h04)) 
    \axi_rdata[29]_i_4 
       (.I0(sel0[0]),
        .I1(S_ADC_CHANNEL[29]),
        .I2(sel0[1]),
        .O(\axi_rdata[29]_i_4_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \axi_rdata[29]_i_5 
       (.I0(\ADC_MASTER_CHANNEL_reg_n_0_[29] ),
        .I1(Q[29]),
        .I2(sel0[1]),
        .I3(\ADC_SPI_CR_reg_n_0_[29] ),
        .I4(sel0[0]),
        .I5(\ADC_CR_reg_n_0_[29] ),
        .O(\axi_rdata[29]_i_5_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \axi_rdata[2]_i_1 
       (.I0(\axi_rdata[2]_i_2_n_0 ),
        .I1(\axi_rdata[2]_i_3_n_0 ),
        .I2(sel0[3]),
        .I3(\axi_rdata[2]_i_4_n_0 ),
        .I4(sel0[2]),
        .I5(\axi_rdata[2]_i_5_n_0 ),
        .O(reg_data_out[2]));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \axi_rdata[2]_i_2 
       (.I0(slv_reg15[2]),
        .I1(slv_reg14[2]),
        .I2(sel0[1]),
        .I3(slv_reg13[2]),
        .I4(sel0[0]),
        .I5(slv_reg12[2]),
        .O(\axi_rdata[2]_i_2_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \axi_rdata[2]_i_3 
       (.I0(slv_reg11[2]),
        .I1(slv_reg10[2]),
        .I2(sel0[1]),
        .I3(\ADC_AVAILABLE_reg_n_0_[2] ),
        .I4(sel0[0]),
        .I5(\ADC_CONV_VALUE_reg[30]_0 [2]),
        .O(\axi_rdata[2]_i_3_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair7" *) 
  LUT3 #(
    .INIT(8'h04)) 
    \axi_rdata[2]_i_4 
       (.I0(sel0[0]),
        .I1(S_ADC_CHANNEL[2]),
        .I2(sel0[1]),
        .O(\axi_rdata[2]_i_4_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \axi_rdata[2]_i_5 
       (.I0(\ADC_MASTER_CHANNEL_reg_n_0_[2] ),
        .I1(Q[2]),
        .I2(sel0[1]),
        .I3(D[1]),
        .I4(sel0[0]),
        .I5(S_ADC_CR[2]),
        .O(\axi_rdata[2]_i_5_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \axi_rdata[30]_i_1 
       (.I0(\axi_rdata[30]_i_2_n_0 ),
        .I1(\axi_rdata[30]_i_3_n_0 ),
        .I2(sel0[3]),
        .I3(\axi_rdata[30]_i_4_n_0 ),
        .I4(sel0[2]),
        .I5(\axi_rdata[30]_i_5_n_0 ),
        .O(reg_data_out[30]));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \axi_rdata[30]_i_2 
       (.I0(slv_reg15[30]),
        .I1(slv_reg14[30]),
        .I2(sel0[1]),
        .I3(slv_reg13[30]),
        .I4(sel0[0]),
        .I5(slv_reg12[30]),
        .O(\axi_rdata[30]_i_2_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \axi_rdata[30]_i_3 
       (.I0(slv_reg11[30]),
        .I1(slv_reg10[30]),
        .I2(sel0[1]),
        .I3(\ADC_AVAILABLE_reg_n_0_[30] ),
        .I4(sel0[0]),
        .I5(\ADC_CONV_VALUE_reg[30]_0 [30]),
        .O(\axi_rdata[30]_i_3_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair21" *) 
  LUT3 #(
    .INIT(8'h04)) 
    \axi_rdata[30]_i_4 
       (.I0(sel0[0]),
        .I1(S_ADC_CHANNEL[30]),
        .I2(sel0[1]),
        .O(\axi_rdata[30]_i_4_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \axi_rdata[30]_i_5 
       (.I0(\ADC_MASTER_CHANNEL_reg_n_0_[30] ),
        .I1(Q[30]),
        .I2(sel0[1]),
        .I3(\ADC_SPI_CR_reg_n_0_[30] ),
        .I4(sel0[0]),
        .I5(\ADC_CR_reg_n_0_[30] ),
        .O(\axi_rdata[30]_i_5_n_0 ));
  LUT3 #(
    .INIT(8'h08)) 
    \axi_rdata[31]_i_1 
       (.I0(s00_axi_arvalid),
        .I1(axi_arready_reg_0),
        .I2(s00_axi_rvalid),
        .O(slv_reg_rden));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \axi_rdata[31]_i_2 
       (.I0(\axi_rdata[31]_i_3_n_0 ),
        .I1(\axi_rdata[31]_i_4_n_0 ),
        .I2(sel0[3]),
        .I3(\axi_rdata[31]_i_5_n_0 ),
        .I4(sel0[2]),
        .I5(\axi_rdata[31]_i_6_n_0 ),
        .O(reg_data_out[31]));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \axi_rdata[31]_i_3 
       (.I0(slv_reg15[31]),
        .I1(slv_reg14[31]),
        .I2(sel0[1]),
        .I3(slv_reg13[31]),
        .I4(sel0[0]),
        .I5(slv_reg12[31]),
        .O(\axi_rdata[31]_i_3_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \axi_rdata[31]_i_4 
       (.I0(slv_reg11[31]),
        .I1(slv_reg10[31]),
        .I2(sel0[1]),
        .I3(\ADC_AVAILABLE_reg_n_0_[31] ),
        .I4(sel0[0]),
        .I5(S_ADC_CONV_VALUE),
        .O(\axi_rdata[31]_i_4_n_0 ));
  LUT3 #(
    .INIT(8'h04)) 
    \axi_rdata[31]_i_5 
       (.I0(sel0[0]),
        .I1(S_ADC_CHANNEL[31]),
        .I2(sel0[1]),
        .O(\axi_rdata[31]_i_5_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \axi_rdata[31]_i_6 
       (.I0(\ADC_MASTER_CHANNEL_reg_n_0_[31] ),
        .I1(Q[31]),
        .I2(sel0[1]),
        .I3(\ADC_SPI_CR_reg_n_0_[31] ),
        .I4(sel0[0]),
        .I5(\ADC_CR_reg_n_0_[31] ),
        .O(\axi_rdata[31]_i_6_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \axi_rdata[3]_i_1 
       (.I0(\axi_rdata[3]_i_2_n_0 ),
        .I1(\axi_rdata[3]_i_3_n_0 ),
        .I2(sel0[3]),
        .I3(\axi_rdata[3]_i_4_n_0 ),
        .I4(sel0[2]),
        .I5(\axi_rdata[3]_i_5_n_0 ),
        .O(reg_data_out[3]));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \axi_rdata[3]_i_2 
       (.I0(slv_reg15[3]),
        .I1(slv_reg14[3]),
        .I2(sel0[1]),
        .I3(slv_reg13[3]),
        .I4(sel0[0]),
        .I5(slv_reg12[3]),
        .O(\axi_rdata[3]_i_2_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \axi_rdata[3]_i_3 
       (.I0(slv_reg11[3]),
        .I1(slv_reg10[3]),
        .I2(sel0[1]),
        .I3(\ADC_AVAILABLE_reg_n_0_[3] ),
        .I4(sel0[0]),
        .I5(\ADC_CONV_VALUE_reg[30]_0 [3]),
        .O(\axi_rdata[3]_i_3_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair8" *) 
  LUT3 #(
    .INIT(8'h04)) 
    \axi_rdata[3]_i_4 
       (.I0(sel0[0]),
        .I1(S_ADC_CHANNEL[3]),
        .I2(sel0[1]),
        .O(\axi_rdata[3]_i_4_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \axi_rdata[3]_i_5 
       (.I0(\ADC_MASTER_CHANNEL_reg_n_0_[3] ),
        .I1(Q[3]),
        .I2(sel0[1]),
        .I3(\ADC_SPI_CR_reg_n_0_[3] ),
        .I4(sel0[0]),
        .I5(\ADC_CR_reg[3]_0 ),
        .O(\axi_rdata[3]_i_5_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \axi_rdata[4]_i_1 
       (.I0(\axi_rdata[4]_i_2_n_0 ),
        .I1(\axi_rdata[4]_i_3_n_0 ),
        .I2(sel0[3]),
        .I3(\axi_rdata[4]_i_4_n_0 ),
        .I4(sel0[2]),
        .I5(\axi_rdata[4]_i_5_n_0 ),
        .O(reg_data_out[4]));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \axi_rdata[4]_i_2 
       (.I0(slv_reg15[4]),
        .I1(slv_reg14[4]),
        .I2(sel0[1]),
        .I3(slv_reg13[4]),
        .I4(sel0[0]),
        .I5(slv_reg12[4]),
        .O(\axi_rdata[4]_i_2_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \axi_rdata[4]_i_3 
       (.I0(slv_reg11[4]),
        .I1(slv_reg10[4]),
        .I2(sel0[1]),
        .I3(\ADC_AVAILABLE_reg_n_0_[4] ),
        .I4(sel0[0]),
        .I5(\ADC_CONV_VALUE_reg[30]_0 [4]),
        .O(\axi_rdata[4]_i_3_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair8" *) 
  LUT3 #(
    .INIT(8'h04)) 
    \axi_rdata[4]_i_4 
       (.I0(sel0[0]),
        .I1(S_ADC_CHANNEL[4]),
        .I2(sel0[1]),
        .O(\axi_rdata[4]_i_4_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \axi_rdata[4]_i_5 
       (.I0(\ADC_MASTER_CHANNEL_reg_n_0_[4] ),
        .I1(Q[4]),
        .I2(sel0[1]),
        .I3(p_0_in13_in),
        .I4(sel0[0]),
        .I5(S_ADC_CR[4]),
        .O(\axi_rdata[4]_i_5_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \axi_rdata[5]_i_1 
       (.I0(\axi_rdata[5]_i_2_n_0 ),
        .I1(\axi_rdata[5]_i_3_n_0 ),
        .I2(sel0[3]),
        .I3(\axi_rdata[5]_i_4_n_0 ),
        .I4(sel0[2]),
        .I5(\axi_rdata[5]_i_5_n_0 ),
        .O(reg_data_out[5]));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \axi_rdata[5]_i_2 
       (.I0(slv_reg15[5]),
        .I1(slv_reg14[5]),
        .I2(sel0[1]),
        .I3(slv_reg13[5]),
        .I4(sel0[0]),
        .I5(slv_reg12[5]),
        .O(\axi_rdata[5]_i_2_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \axi_rdata[5]_i_3 
       (.I0(slv_reg11[5]),
        .I1(slv_reg10[5]),
        .I2(sel0[1]),
        .I3(\ADC_AVAILABLE_reg_n_0_[5] ),
        .I4(sel0[0]),
        .I5(\ADC_CONV_VALUE_reg[30]_0 [5]),
        .O(\axi_rdata[5]_i_3_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair9" *) 
  LUT3 #(
    .INIT(8'h04)) 
    \axi_rdata[5]_i_4 
       (.I0(sel0[0]),
        .I1(S_ADC_CHANNEL[5]),
        .I2(sel0[1]),
        .O(\axi_rdata[5]_i_4_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \axi_rdata[5]_i_5 
       (.I0(\ADC_MASTER_CHANNEL_reg_n_0_[5] ),
        .I1(Q[5]),
        .I2(sel0[1]),
        .I3(\ADC_SPI_CR_reg_n_0_[5] ),
        .I4(sel0[0]),
        .I5(S_ADC_CR[5]),
        .O(\axi_rdata[5]_i_5_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \axi_rdata[6]_i_1 
       (.I0(\axi_rdata[6]_i_2_n_0 ),
        .I1(\axi_rdata[6]_i_3_n_0 ),
        .I2(sel0[3]),
        .I3(\axi_rdata[6]_i_4_n_0 ),
        .I4(sel0[2]),
        .I5(\axi_rdata[6]_i_5_n_0 ),
        .O(reg_data_out[6]));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \axi_rdata[6]_i_2 
       (.I0(slv_reg15[6]),
        .I1(slv_reg14[6]),
        .I2(sel0[1]),
        .I3(slv_reg13[6]),
        .I4(sel0[0]),
        .I5(slv_reg12[6]),
        .O(\axi_rdata[6]_i_2_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \axi_rdata[6]_i_3 
       (.I0(slv_reg11[6]),
        .I1(slv_reg10[6]),
        .I2(sel0[1]),
        .I3(\ADC_AVAILABLE_reg_n_0_[6] ),
        .I4(sel0[0]),
        .I5(\ADC_CONV_VALUE_reg[30]_0 [6]),
        .O(\axi_rdata[6]_i_3_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair9" *) 
  LUT3 #(
    .INIT(8'h04)) 
    \axi_rdata[6]_i_4 
       (.I0(sel0[0]),
        .I1(S_ADC_CHANNEL[6]),
        .I2(sel0[1]),
        .O(\axi_rdata[6]_i_4_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \axi_rdata[6]_i_5 
       (.I0(\ADC_MASTER_CHANNEL_reg_n_0_[6] ),
        .I1(Q[6]),
        .I2(sel0[1]),
        .I3(CPOL),
        .I4(sel0[0]),
        .I5(S_ADC_CR[6]),
        .O(\axi_rdata[6]_i_5_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \axi_rdata[7]_i_1 
       (.I0(\axi_rdata[7]_i_2_n_0 ),
        .I1(\axi_rdata[7]_i_3_n_0 ),
        .I2(sel0[3]),
        .I3(\axi_rdata[7]_i_4_n_0 ),
        .I4(sel0[2]),
        .I5(\axi_rdata[7]_i_5_n_0 ),
        .O(reg_data_out[7]));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \axi_rdata[7]_i_2 
       (.I0(slv_reg15[7]),
        .I1(slv_reg14[7]),
        .I2(sel0[1]),
        .I3(slv_reg13[7]),
        .I4(sel0[0]),
        .I5(slv_reg12[7]),
        .O(\axi_rdata[7]_i_2_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \axi_rdata[7]_i_3 
       (.I0(slv_reg11[7]),
        .I1(slv_reg10[7]),
        .I2(sel0[1]),
        .I3(\ADC_AVAILABLE_reg_n_0_[7] ),
        .I4(sel0[0]),
        .I5(\ADC_CONV_VALUE_reg[30]_0 [7]),
        .O(\axi_rdata[7]_i_3_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair10" *) 
  LUT3 #(
    .INIT(8'h04)) 
    \axi_rdata[7]_i_4 
       (.I0(sel0[0]),
        .I1(S_ADC_CHANNEL[7]),
        .I2(sel0[1]),
        .O(\axi_rdata[7]_i_4_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \axi_rdata[7]_i_5 
       (.I0(\ADC_MASTER_CHANNEL_reg_n_0_[7] ),
        .I1(Q[7]),
        .I2(sel0[1]),
        .I3(CPHA),
        .I4(sel0[0]),
        .I5(S_ADC_CR[7]),
        .O(\axi_rdata[7]_i_5_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \axi_rdata[8]_i_1 
       (.I0(\axi_rdata[8]_i_2_n_0 ),
        .I1(\axi_rdata[8]_i_3_n_0 ),
        .I2(sel0[3]),
        .I3(\axi_rdata[8]_i_4_n_0 ),
        .I4(sel0[2]),
        .I5(\axi_rdata[8]_i_5_n_0 ),
        .O(reg_data_out[8]));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \axi_rdata[8]_i_2 
       (.I0(slv_reg15[8]),
        .I1(slv_reg14[8]),
        .I2(sel0[1]),
        .I3(slv_reg13[8]),
        .I4(sel0[0]),
        .I5(slv_reg12[8]),
        .O(\axi_rdata[8]_i_2_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \axi_rdata[8]_i_3 
       (.I0(slv_reg11[8]),
        .I1(slv_reg10[8]),
        .I2(sel0[1]),
        .I3(\ADC_AVAILABLE_reg_n_0_[8] ),
        .I4(sel0[0]),
        .I5(\ADC_CONV_VALUE_reg[30]_0 [8]),
        .O(\axi_rdata[8]_i_3_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair10" *) 
  LUT3 #(
    .INIT(8'h04)) 
    \axi_rdata[8]_i_4 
       (.I0(sel0[0]),
        .I1(S_ADC_CHANNEL[8]),
        .I2(sel0[1]),
        .O(\axi_rdata[8]_i_4_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \axi_rdata[8]_i_5 
       (.I0(\ADC_MASTER_CHANNEL_reg_n_0_[8] ),
        .I1(Q[8]),
        .I2(sel0[1]),
        .I3(\ADC_SPI_CR_reg_n_0_[8] ),
        .I4(sel0[0]),
        .I5(\ADC_CR_reg_n_0_[8] ),
        .O(\axi_rdata[8]_i_5_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \axi_rdata[9]_i_1 
       (.I0(\axi_rdata[9]_i_2_n_0 ),
        .I1(\axi_rdata[9]_i_3_n_0 ),
        .I2(sel0[3]),
        .I3(\axi_rdata[9]_i_4_n_0 ),
        .I4(sel0[2]),
        .I5(\axi_rdata[9]_i_5_n_0 ),
        .O(reg_data_out[9]));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \axi_rdata[9]_i_2 
       (.I0(slv_reg15[9]),
        .I1(slv_reg14[9]),
        .I2(sel0[1]),
        .I3(slv_reg13[9]),
        .I4(sel0[0]),
        .I5(slv_reg12[9]),
        .O(\axi_rdata[9]_i_2_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \axi_rdata[9]_i_3 
       (.I0(slv_reg11[9]),
        .I1(slv_reg10[9]),
        .I2(sel0[1]),
        .I3(\ADC_AVAILABLE_reg_n_0_[9] ),
        .I4(sel0[0]),
        .I5(\ADC_CONV_VALUE_reg[30]_0 [9]),
        .O(\axi_rdata[9]_i_3_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair11" *) 
  LUT3 #(
    .INIT(8'h04)) 
    \axi_rdata[9]_i_4 
       (.I0(sel0[0]),
        .I1(S_ADC_CHANNEL[9]),
        .I2(sel0[1]),
        .O(\axi_rdata[9]_i_4_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \axi_rdata[9]_i_5 
       (.I0(\ADC_MASTER_CHANNEL_reg_n_0_[9] ),
        .I1(Q[9]),
        .I2(sel0[1]),
        .I3(\ADC_SPI_CR_reg_n_0_[9] ),
        .I4(sel0[0]),
        .I5(\ADC_CR_reg_n_0_[9] ),
        .O(\axi_rdata[9]_i_5_n_0 ));
  FDRE \axi_rdata_reg[0] 
       (.C(s00_axi_aclk),
        .CE(slv_reg_rden),
        .D(reg_data_out[0]),
        .Q(s00_axi_rdata[0]),
        .R(RSTP));
  MUXF8 \axi_rdata_reg[0]_i_1 
       (.I0(\axi_rdata_reg[0]_i_2_n_0 ),
        .I1(\axi_rdata_reg[0]_i_3_n_0 ),
        .O(reg_data_out[0]),
        .S(sel0[3]));
  MUXF7 \axi_rdata_reg[0]_i_2 
       (.I0(\axi_rdata[0]_i_4_n_0 ),
        .I1(\axi_rdata[0]_i_5_n_0 ),
        .O(\axi_rdata_reg[0]_i_2_n_0 ),
        .S(sel0[2]));
  MUXF7 \axi_rdata_reg[0]_i_3 
       (.I0(\axi_rdata[0]_i_6_n_0 ),
        .I1(\axi_rdata[0]_i_7_n_0 ),
        .O(\axi_rdata_reg[0]_i_3_n_0 ),
        .S(sel0[2]));
  FDRE \axi_rdata_reg[10] 
       (.C(s00_axi_aclk),
        .CE(slv_reg_rden),
        .D(reg_data_out[10]),
        .Q(s00_axi_rdata[10]),
        .R(RSTP));
  FDRE \axi_rdata_reg[11] 
       (.C(s00_axi_aclk),
        .CE(slv_reg_rden),
        .D(reg_data_out[11]),
        .Q(s00_axi_rdata[11]),
        .R(RSTP));
  FDRE \axi_rdata_reg[12] 
       (.C(s00_axi_aclk),
        .CE(slv_reg_rden),
        .D(reg_data_out[12]),
        .Q(s00_axi_rdata[12]),
        .R(RSTP));
  FDRE \axi_rdata_reg[13] 
       (.C(s00_axi_aclk),
        .CE(slv_reg_rden),
        .D(reg_data_out[13]),
        .Q(s00_axi_rdata[13]),
        .R(RSTP));
  FDRE \axi_rdata_reg[14] 
       (.C(s00_axi_aclk),
        .CE(slv_reg_rden),
        .D(reg_data_out[14]),
        .Q(s00_axi_rdata[14]),
        .R(RSTP));
  FDRE \axi_rdata_reg[15] 
       (.C(s00_axi_aclk),
        .CE(slv_reg_rden),
        .D(reg_data_out[15]),
        .Q(s00_axi_rdata[15]),
        .R(RSTP));
  FDRE \axi_rdata_reg[16] 
       (.C(s00_axi_aclk),
        .CE(slv_reg_rden),
        .D(reg_data_out[16]),
        .Q(s00_axi_rdata[16]),
        .R(RSTP));
  FDRE \axi_rdata_reg[17] 
       (.C(s00_axi_aclk),
        .CE(slv_reg_rden),
        .D(reg_data_out[17]),
        .Q(s00_axi_rdata[17]),
        .R(RSTP));
  FDRE \axi_rdata_reg[18] 
       (.C(s00_axi_aclk),
        .CE(slv_reg_rden),
        .D(reg_data_out[18]),
        .Q(s00_axi_rdata[18]),
        .R(RSTP));
  FDRE \axi_rdata_reg[19] 
       (.C(s00_axi_aclk),
        .CE(slv_reg_rden),
        .D(reg_data_out[19]),
        .Q(s00_axi_rdata[19]),
        .R(RSTP));
  FDRE \axi_rdata_reg[1] 
       (.C(s00_axi_aclk),
        .CE(slv_reg_rden),
        .D(reg_data_out[1]),
        .Q(s00_axi_rdata[1]),
        .R(RSTP));
  FDRE \axi_rdata_reg[20] 
       (.C(s00_axi_aclk),
        .CE(slv_reg_rden),
        .D(reg_data_out[20]),
        .Q(s00_axi_rdata[20]),
        .R(RSTP));
  FDRE \axi_rdata_reg[21] 
       (.C(s00_axi_aclk),
        .CE(slv_reg_rden),
        .D(reg_data_out[21]),
        .Q(s00_axi_rdata[21]),
        .R(RSTP));
  FDRE \axi_rdata_reg[22] 
       (.C(s00_axi_aclk),
        .CE(slv_reg_rden),
        .D(reg_data_out[22]),
        .Q(s00_axi_rdata[22]),
        .R(RSTP));
  FDRE \axi_rdata_reg[23] 
       (.C(s00_axi_aclk),
        .CE(slv_reg_rden),
        .D(reg_data_out[23]),
        .Q(s00_axi_rdata[23]),
        .R(RSTP));
  FDRE \axi_rdata_reg[24] 
       (.C(s00_axi_aclk),
        .CE(slv_reg_rden),
        .D(reg_data_out[24]),
        .Q(s00_axi_rdata[24]),
        .R(RSTP));
  FDRE \axi_rdata_reg[25] 
       (.C(s00_axi_aclk),
        .CE(slv_reg_rden),
        .D(reg_data_out[25]),
        .Q(s00_axi_rdata[25]),
        .R(RSTP));
  FDRE \axi_rdata_reg[26] 
       (.C(s00_axi_aclk),
        .CE(slv_reg_rden),
        .D(reg_data_out[26]),
        .Q(s00_axi_rdata[26]),
        .R(RSTP));
  FDRE \axi_rdata_reg[27] 
       (.C(s00_axi_aclk),
        .CE(slv_reg_rden),
        .D(reg_data_out[27]),
        .Q(s00_axi_rdata[27]),
        .R(RSTP));
  FDRE \axi_rdata_reg[28] 
       (.C(s00_axi_aclk),
        .CE(slv_reg_rden),
        .D(reg_data_out[28]),
        .Q(s00_axi_rdata[28]),
        .R(RSTP));
  FDRE \axi_rdata_reg[29] 
       (.C(s00_axi_aclk),
        .CE(slv_reg_rden),
        .D(reg_data_out[29]),
        .Q(s00_axi_rdata[29]),
        .R(RSTP));
  FDRE \axi_rdata_reg[2] 
       (.C(s00_axi_aclk),
        .CE(slv_reg_rden),
        .D(reg_data_out[2]),
        .Q(s00_axi_rdata[2]),
        .R(RSTP));
  FDRE \axi_rdata_reg[30] 
       (.C(s00_axi_aclk),
        .CE(slv_reg_rden),
        .D(reg_data_out[30]),
        .Q(s00_axi_rdata[30]),
        .R(RSTP));
  FDRE \axi_rdata_reg[31] 
       (.C(s00_axi_aclk),
        .CE(slv_reg_rden),
        .D(reg_data_out[31]),
        .Q(s00_axi_rdata[31]),
        .R(RSTP));
  FDRE \axi_rdata_reg[3] 
       (.C(s00_axi_aclk),
        .CE(slv_reg_rden),
        .D(reg_data_out[3]),
        .Q(s00_axi_rdata[3]),
        .R(RSTP));
  FDRE \axi_rdata_reg[4] 
       (.C(s00_axi_aclk),
        .CE(slv_reg_rden),
        .D(reg_data_out[4]),
        .Q(s00_axi_rdata[4]),
        .R(RSTP));
  FDRE \axi_rdata_reg[5] 
       (.C(s00_axi_aclk),
        .CE(slv_reg_rden),
        .D(reg_data_out[5]),
        .Q(s00_axi_rdata[5]),
        .R(RSTP));
  FDRE \axi_rdata_reg[6] 
       (.C(s00_axi_aclk),
        .CE(slv_reg_rden),
        .D(reg_data_out[6]),
        .Q(s00_axi_rdata[6]),
        .R(RSTP));
  FDRE \axi_rdata_reg[7] 
       (.C(s00_axi_aclk),
        .CE(slv_reg_rden),
        .D(reg_data_out[7]),
        .Q(s00_axi_rdata[7]),
        .R(RSTP));
  FDRE \axi_rdata_reg[8] 
       (.C(s00_axi_aclk),
        .CE(slv_reg_rden),
        .D(reg_data_out[8]),
        .Q(s00_axi_rdata[8]),
        .R(RSTP));
  FDRE \axi_rdata_reg[9] 
       (.C(s00_axi_aclk),
        .CE(slv_reg_rden),
        .D(reg_data_out[9]),
        .Q(s00_axi_rdata[9]),
        .R(RSTP));
  LUT4 #(
    .INIT(16'h08F8)) 
    axi_rvalid_i_1
       (.I0(axi_arready_reg_0),
        .I1(s00_axi_arvalid),
        .I2(s00_axi_rvalid),
        .I3(s00_axi_rready),
        .O(axi_rvalid_i_1_n_0));
  FDRE axi_rvalid_reg
       (.C(s00_axi_aclk),
        .CE(1'b1),
        .D(axi_rvalid_i_1_n_0),
        .Q(s00_axi_rvalid),
        .R(RSTP));
  LUT4 #(
    .INIT(16'h0800)) 
    axi_wready_i_1
       (.I0(s00_axi_wvalid),
        .I1(s00_axi_awvalid),
        .I2(axi_wready_reg_0),
        .I3(aw_en_reg_n_0),
        .O(axi_wready0));
  FDRE axi_wready_reg
       (.C(s00_axi_aclk),
        .CE(1'b1),
        .D(axi_wready0),
        .Q(axi_wready_reg_0),
        .R(RSTP));
  LUT6 #(
    .INIT(64'h3020202070707070)) 
    \curstate[0]_i_1__1 
       (.I0(\curstate_reg[0] [0]),
        .I1(\curstate_reg[0] [1]),
        .I2(S_ADC_CR[0]),
        .I3(S_ADC_MASTER_CHANNEL),
        .I4(BUSY),
        .I5(p_0_in13_in),
        .O(nxtstate[0]));
  (* SOFT_HLUTNM = "soft_lutpair3" *) 
  LUT5 #(
    .INIT(32'h0000F070)) 
    \curstate[1]_i_1__0 
       (.I0(S_ADC_MASTER_CHANNEL),
        .I1(BUSY),
        .I2(p_0_in13_in),
        .I3(\curstate_reg[0] [1]),
        .I4(\curstate_reg[0] [0]),
        .O(nxtstate[1]));
  LUT6 #(
    .INIT(64'h0000000000008000)) 
    \slv_reg10[15]_i_1 
       (.I0(slv_reg_wren__0),
        .I1(p_0_in[3]),
        .I2(s00_axi_wstrb[1]),
        .I3(p_0_in[1]),
        .I4(p_0_in[0]),
        .I5(p_0_in[2]),
        .O(\slv_reg10[15]_i_1_n_0 ));
  LUT6 #(
    .INIT(64'h0000000000008000)) 
    \slv_reg10[23]_i_1 
       (.I0(slv_reg_wren__0),
        .I1(p_0_in[3]),
        .I2(s00_axi_wstrb[2]),
        .I3(p_0_in[1]),
        .I4(p_0_in[0]),
        .I5(p_0_in[2]),
        .O(\slv_reg10[23]_i_1_n_0 ));
  LUT6 #(
    .INIT(64'h0000000000008000)) 
    \slv_reg10[31]_i_1 
       (.I0(slv_reg_wren__0),
        .I1(p_0_in[3]),
        .I2(s00_axi_wstrb[3]),
        .I3(p_0_in[1]),
        .I4(p_0_in[0]),
        .I5(p_0_in[2]),
        .O(\slv_reg10[31]_i_1_n_0 ));
  LUT6 #(
    .INIT(64'h0000000000008000)) 
    \slv_reg10[7]_i_1 
       (.I0(slv_reg_wren__0),
        .I1(p_0_in[3]),
        .I2(s00_axi_wstrb[0]),
        .I3(p_0_in[1]),
        .I4(p_0_in[0]),
        .I5(p_0_in[2]),
        .O(\slv_reg10[7]_i_1_n_0 ));
  FDRE \slv_reg10_reg[0] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg10[7]_i_1_n_0 ),
        .D(s00_axi_wdata[0]),
        .Q(slv_reg10[0]),
        .R(RSTP));
  FDRE \slv_reg10_reg[10] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg10[15]_i_1_n_0 ),
        .D(s00_axi_wdata[10]),
        .Q(slv_reg10[10]),
        .R(RSTP));
  FDRE \slv_reg10_reg[11] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg10[15]_i_1_n_0 ),
        .D(s00_axi_wdata[11]),
        .Q(slv_reg10[11]),
        .R(RSTP));
  FDRE \slv_reg10_reg[12] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg10[15]_i_1_n_0 ),
        .D(s00_axi_wdata[12]),
        .Q(slv_reg10[12]),
        .R(RSTP));
  FDRE \slv_reg10_reg[13] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg10[15]_i_1_n_0 ),
        .D(s00_axi_wdata[13]),
        .Q(slv_reg10[13]),
        .R(RSTP));
  FDRE \slv_reg10_reg[14] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg10[15]_i_1_n_0 ),
        .D(s00_axi_wdata[14]),
        .Q(slv_reg10[14]),
        .R(RSTP));
  FDRE \slv_reg10_reg[15] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg10[15]_i_1_n_0 ),
        .D(s00_axi_wdata[15]),
        .Q(slv_reg10[15]),
        .R(RSTP));
  FDRE \slv_reg10_reg[16] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg10[23]_i_1_n_0 ),
        .D(s00_axi_wdata[16]),
        .Q(slv_reg10[16]),
        .R(RSTP));
  FDRE \slv_reg10_reg[17] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg10[23]_i_1_n_0 ),
        .D(s00_axi_wdata[17]),
        .Q(slv_reg10[17]),
        .R(RSTP));
  FDRE \slv_reg10_reg[18] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg10[23]_i_1_n_0 ),
        .D(s00_axi_wdata[18]),
        .Q(slv_reg10[18]),
        .R(RSTP));
  FDRE \slv_reg10_reg[19] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg10[23]_i_1_n_0 ),
        .D(s00_axi_wdata[19]),
        .Q(slv_reg10[19]),
        .R(RSTP));
  FDRE \slv_reg10_reg[1] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg10[7]_i_1_n_0 ),
        .D(s00_axi_wdata[1]),
        .Q(slv_reg10[1]),
        .R(RSTP));
  FDRE \slv_reg10_reg[20] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg10[23]_i_1_n_0 ),
        .D(s00_axi_wdata[20]),
        .Q(slv_reg10[20]),
        .R(RSTP));
  FDRE \slv_reg10_reg[21] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg10[23]_i_1_n_0 ),
        .D(s00_axi_wdata[21]),
        .Q(slv_reg10[21]),
        .R(RSTP));
  FDRE \slv_reg10_reg[22] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg10[23]_i_1_n_0 ),
        .D(s00_axi_wdata[22]),
        .Q(slv_reg10[22]),
        .R(RSTP));
  FDRE \slv_reg10_reg[23] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg10[23]_i_1_n_0 ),
        .D(s00_axi_wdata[23]),
        .Q(slv_reg10[23]),
        .R(RSTP));
  FDRE \slv_reg10_reg[24] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg10[31]_i_1_n_0 ),
        .D(s00_axi_wdata[24]),
        .Q(slv_reg10[24]),
        .R(RSTP));
  FDRE \slv_reg10_reg[25] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg10[31]_i_1_n_0 ),
        .D(s00_axi_wdata[25]),
        .Q(slv_reg10[25]),
        .R(RSTP));
  FDRE \slv_reg10_reg[26] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg10[31]_i_1_n_0 ),
        .D(s00_axi_wdata[26]),
        .Q(slv_reg10[26]),
        .R(RSTP));
  FDRE \slv_reg10_reg[27] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg10[31]_i_1_n_0 ),
        .D(s00_axi_wdata[27]),
        .Q(slv_reg10[27]),
        .R(RSTP));
  FDRE \slv_reg10_reg[28] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg10[31]_i_1_n_0 ),
        .D(s00_axi_wdata[28]),
        .Q(slv_reg10[28]),
        .R(RSTP));
  FDRE \slv_reg10_reg[29] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg10[31]_i_1_n_0 ),
        .D(s00_axi_wdata[29]),
        .Q(slv_reg10[29]),
        .R(RSTP));
  FDRE \slv_reg10_reg[2] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg10[7]_i_1_n_0 ),
        .D(s00_axi_wdata[2]),
        .Q(slv_reg10[2]),
        .R(RSTP));
  FDRE \slv_reg10_reg[30] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg10[31]_i_1_n_0 ),
        .D(s00_axi_wdata[30]),
        .Q(slv_reg10[30]),
        .R(RSTP));
  FDRE \slv_reg10_reg[31] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg10[31]_i_1_n_0 ),
        .D(s00_axi_wdata[31]),
        .Q(slv_reg10[31]),
        .R(RSTP));
  FDRE \slv_reg10_reg[3] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg10[7]_i_1_n_0 ),
        .D(s00_axi_wdata[3]),
        .Q(slv_reg10[3]),
        .R(RSTP));
  FDRE \slv_reg10_reg[4] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg10[7]_i_1_n_0 ),
        .D(s00_axi_wdata[4]),
        .Q(slv_reg10[4]),
        .R(RSTP));
  FDRE \slv_reg10_reg[5] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg10[7]_i_1_n_0 ),
        .D(s00_axi_wdata[5]),
        .Q(slv_reg10[5]),
        .R(RSTP));
  FDRE \slv_reg10_reg[6] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg10[7]_i_1_n_0 ),
        .D(s00_axi_wdata[6]),
        .Q(slv_reg10[6]),
        .R(RSTP));
  FDRE \slv_reg10_reg[7] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg10[7]_i_1_n_0 ),
        .D(s00_axi_wdata[7]),
        .Q(slv_reg10[7]),
        .R(RSTP));
  FDRE \slv_reg10_reg[8] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg10[15]_i_1_n_0 ),
        .D(s00_axi_wdata[8]),
        .Q(slv_reg10[8]),
        .R(RSTP));
  FDRE \slv_reg10_reg[9] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg10[15]_i_1_n_0 ),
        .D(s00_axi_wdata[9]),
        .Q(slv_reg10[9]),
        .R(RSTP));
  LUT6 #(
    .INIT(64'h0000000080000000)) 
    \slv_reg11[15]_i_1 
       (.I0(slv_reg_wren__0),
        .I1(s00_axi_wstrb[1]),
        .I2(p_0_in[3]),
        .I3(p_0_in[0]),
        .I4(p_0_in[1]),
        .I5(p_0_in[2]),
        .O(\slv_reg11[15]_i_1_n_0 ));
  LUT6 #(
    .INIT(64'h0000000080000000)) 
    \slv_reg11[23]_i_1 
       (.I0(slv_reg_wren__0),
        .I1(s00_axi_wstrb[2]),
        .I2(p_0_in[3]),
        .I3(p_0_in[0]),
        .I4(p_0_in[1]),
        .I5(p_0_in[2]),
        .O(\slv_reg11[23]_i_1_n_0 ));
  LUT6 #(
    .INIT(64'h0000000080000000)) 
    \slv_reg11[31]_i_1 
       (.I0(slv_reg_wren__0),
        .I1(s00_axi_wstrb[3]),
        .I2(p_0_in[3]),
        .I3(p_0_in[0]),
        .I4(p_0_in[1]),
        .I5(p_0_in[2]),
        .O(\slv_reg11[31]_i_1_n_0 ));
  LUT6 #(
    .INIT(64'h0000000080000000)) 
    \slv_reg11[7]_i_1 
       (.I0(slv_reg_wren__0),
        .I1(s00_axi_wstrb[0]),
        .I2(p_0_in[3]),
        .I3(p_0_in[0]),
        .I4(p_0_in[1]),
        .I5(p_0_in[2]),
        .O(\slv_reg11[7]_i_1_n_0 ));
  FDRE \slv_reg11_reg[0] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg11[7]_i_1_n_0 ),
        .D(s00_axi_wdata[0]),
        .Q(slv_reg11[0]),
        .R(RSTP));
  FDRE \slv_reg11_reg[10] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg11[15]_i_1_n_0 ),
        .D(s00_axi_wdata[10]),
        .Q(slv_reg11[10]),
        .R(RSTP));
  FDRE \slv_reg11_reg[11] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg11[15]_i_1_n_0 ),
        .D(s00_axi_wdata[11]),
        .Q(slv_reg11[11]),
        .R(RSTP));
  FDRE \slv_reg11_reg[12] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg11[15]_i_1_n_0 ),
        .D(s00_axi_wdata[12]),
        .Q(slv_reg11[12]),
        .R(RSTP));
  FDRE \slv_reg11_reg[13] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg11[15]_i_1_n_0 ),
        .D(s00_axi_wdata[13]),
        .Q(slv_reg11[13]),
        .R(RSTP));
  FDRE \slv_reg11_reg[14] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg11[15]_i_1_n_0 ),
        .D(s00_axi_wdata[14]),
        .Q(slv_reg11[14]),
        .R(RSTP));
  FDRE \slv_reg11_reg[15] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg11[15]_i_1_n_0 ),
        .D(s00_axi_wdata[15]),
        .Q(slv_reg11[15]),
        .R(RSTP));
  FDRE \slv_reg11_reg[16] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg11[23]_i_1_n_0 ),
        .D(s00_axi_wdata[16]),
        .Q(slv_reg11[16]),
        .R(RSTP));
  FDRE \slv_reg11_reg[17] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg11[23]_i_1_n_0 ),
        .D(s00_axi_wdata[17]),
        .Q(slv_reg11[17]),
        .R(RSTP));
  FDRE \slv_reg11_reg[18] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg11[23]_i_1_n_0 ),
        .D(s00_axi_wdata[18]),
        .Q(slv_reg11[18]),
        .R(RSTP));
  FDRE \slv_reg11_reg[19] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg11[23]_i_1_n_0 ),
        .D(s00_axi_wdata[19]),
        .Q(slv_reg11[19]),
        .R(RSTP));
  FDRE \slv_reg11_reg[1] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg11[7]_i_1_n_0 ),
        .D(s00_axi_wdata[1]),
        .Q(slv_reg11[1]),
        .R(RSTP));
  FDRE \slv_reg11_reg[20] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg11[23]_i_1_n_0 ),
        .D(s00_axi_wdata[20]),
        .Q(slv_reg11[20]),
        .R(RSTP));
  FDRE \slv_reg11_reg[21] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg11[23]_i_1_n_0 ),
        .D(s00_axi_wdata[21]),
        .Q(slv_reg11[21]),
        .R(RSTP));
  FDRE \slv_reg11_reg[22] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg11[23]_i_1_n_0 ),
        .D(s00_axi_wdata[22]),
        .Q(slv_reg11[22]),
        .R(RSTP));
  FDRE \slv_reg11_reg[23] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg11[23]_i_1_n_0 ),
        .D(s00_axi_wdata[23]),
        .Q(slv_reg11[23]),
        .R(RSTP));
  FDRE \slv_reg11_reg[24] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg11[31]_i_1_n_0 ),
        .D(s00_axi_wdata[24]),
        .Q(slv_reg11[24]),
        .R(RSTP));
  FDRE \slv_reg11_reg[25] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg11[31]_i_1_n_0 ),
        .D(s00_axi_wdata[25]),
        .Q(slv_reg11[25]),
        .R(RSTP));
  FDRE \slv_reg11_reg[26] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg11[31]_i_1_n_0 ),
        .D(s00_axi_wdata[26]),
        .Q(slv_reg11[26]),
        .R(RSTP));
  FDRE \slv_reg11_reg[27] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg11[31]_i_1_n_0 ),
        .D(s00_axi_wdata[27]),
        .Q(slv_reg11[27]),
        .R(RSTP));
  FDRE \slv_reg11_reg[28] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg11[31]_i_1_n_0 ),
        .D(s00_axi_wdata[28]),
        .Q(slv_reg11[28]),
        .R(RSTP));
  FDRE \slv_reg11_reg[29] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg11[31]_i_1_n_0 ),
        .D(s00_axi_wdata[29]),
        .Q(slv_reg11[29]),
        .R(RSTP));
  FDRE \slv_reg11_reg[2] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg11[7]_i_1_n_0 ),
        .D(s00_axi_wdata[2]),
        .Q(slv_reg11[2]),
        .R(RSTP));
  FDRE \slv_reg11_reg[30] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg11[31]_i_1_n_0 ),
        .D(s00_axi_wdata[30]),
        .Q(slv_reg11[30]),
        .R(RSTP));
  FDRE \slv_reg11_reg[31] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg11[31]_i_1_n_0 ),
        .D(s00_axi_wdata[31]),
        .Q(slv_reg11[31]),
        .R(RSTP));
  FDRE \slv_reg11_reg[3] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg11[7]_i_1_n_0 ),
        .D(s00_axi_wdata[3]),
        .Q(slv_reg11[3]),
        .R(RSTP));
  FDRE \slv_reg11_reg[4] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg11[7]_i_1_n_0 ),
        .D(s00_axi_wdata[4]),
        .Q(slv_reg11[4]),
        .R(RSTP));
  FDRE \slv_reg11_reg[5] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg11[7]_i_1_n_0 ),
        .D(s00_axi_wdata[5]),
        .Q(slv_reg11[5]),
        .R(RSTP));
  FDRE \slv_reg11_reg[6] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg11[7]_i_1_n_0 ),
        .D(s00_axi_wdata[6]),
        .Q(slv_reg11[6]),
        .R(RSTP));
  FDRE \slv_reg11_reg[7] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg11[7]_i_1_n_0 ),
        .D(s00_axi_wdata[7]),
        .Q(slv_reg11[7]),
        .R(RSTP));
  FDRE \slv_reg11_reg[8] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg11[15]_i_1_n_0 ),
        .D(s00_axi_wdata[8]),
        .Q(slv_reg11[8]),
        .R(RSTP));
  FDRE \slv_reg11_reg[9] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg11[15]_i_1_n_0 ),
        .D(s00_axi_wdata[9]),
        .Q(slv_reg11[9]),
        .R(RSTP));
  LUT6 #(
    .INIT(64'h0000000000008000)) 
    \slv_reg12[15]_i_1 
       (.I0(slv_reg_wren__0),
        .I1(p_0_in[3]),
        .I2(s00_axi_wstrb[1]),
        .I3(p_0_in[2]),
        .I4(p_0_in[0]),
        .I5(p_0_in[1]),
        .O(\slv_reg12[15]_i_1_n_0 ));
  LUT6 #(
    .INIT(64'h0000000000008000)) 
    \slv_reg12[23]_i_1 
       (.I0(slv_reg_wren__0),
        .I1(p_0_in[3]),
        .I2(s00_axi_wstrb[2]),
        .I3(p_0_in[2]),
        .I4(p_0_in[0]),
        .I5(p_0_in[1]),
        .O(\slv_reg12[23]_i_1_n_0 ));
  LUT6 #(
    .INIT(64'h0000000000008000)) 
    \slv_reg12[31]_i_1 
       (.I0(slv_reg_wren__0),
        .I1(p_0_in[3]),
        .I2(s00_axi_wstrb[3]),
        .I3(p_0_in[2]),
        .I4(p_0_in[0]),
        .I5(p_0_in[1]),
        .O(\slv_reg12[31]_i_1_n_0 ));
  LUT6 #(
    .INIT(64'h0000000000008000)) 
    \slv_reg12[7]_i_1 
       (.I0(slv_reg_wren__0),
        .I1(p_0_in[3]),
        .I2(s00_axi_wstrb[0]),
        .I3(p_0_in[2]),
        .I4(p_0_in[0]),
        .I5(p_0_in[1]),
        .O(\slv_reg12[7]_i_1_n_0 ));
  FDRE \slv_reg12_reg[0] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg12[7]_i_1_n_0 ),
        .D(s00_axi_wdata[0]),
        .Q(slv_reg12[0]),
        .R(RSTP));
  FDRE \slv_reg12_reg[10] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg12[15]_i_1_n_0 ),
        .D(s00_axi_wdata[10]),
        .Q(slv_reg12[10]),
        .R(RSTP));
  FDRE \slv_reg12_reg[11] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg12[15]_i_1_n_0 ),
        .D(s00_axi_wdata[11]),
        .Q(slv_reg12[11]),
        .R(RSTP));
  FDRE \slv_reg12_reg[12] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg12[15]_i_1_n_0 ),
        .D(s00_axi_wdata[12]),
        .Q(slv_reg12[12]),
        .R(RSTP));
  FDRE \slv_reg12_reg[13] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg12[15]_i_1_n_0 ),
        .D(s00_axi_wdata[13]),
        .Q(slv_reg12[13]),
        .R(RSTP));
  FDRE \slv_reg12_reg[14] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg12[15]_i_1_n_0 ),
        .D(s00_axi_wdata[14]),
        .Q(slv_reg12[14]),
        .R(RSTP));
  FDRE \slv_reg12_reg[15] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg12[15]_i_1_n_0 ),
        .D(s00_axi_wdata[15]),
        .Q(slv_reg12[15]),
        .R(RSTP));
  FDRE \slv_reg12_reg[16] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg12[23]_i_1_n_0 ),
        .D(s00_axi_wdata[16]),
        .Q(slv_reg12[16]),
        .R(RSTP));
  FDRE \slv_reg12_reg[17] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg12[23]_i_1_n_0 ),
        .D(s00_axi_wdata[17]),
        .Q(slv_reg12[17]),
        .R(RSTP));
  FDRE \slv_reg12_reg[18] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg12[23]_i_1_n_0 ),
        .D(s00_axi_wdata[18]),
        .Q(slv_reg12[18]),
        .R(RSTP));
  FDRE \slv_reg12_reg[19] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg12[23]_i_1_n_0 ),
        .D(s00_axi_wdata[19]),
        .Q(slv_reg12[19]),
        .R(RSTP));
  FDRE \slv_reg12_reg[1] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg12[7]_i_1_n_0 ),
        .D(s00_axi_wdata[1]),
        .Q(slv_reg12[1]),
        .R(RSTP));
  FDRE \slv_reg12_reg[20] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg12[23]_i_1_n_0 ),
        .D(s00_axi_wdata[20]),
        .Q(slv_reg12[20]),
        .R(RSTP));
  FDRE \slv_reg12_reg[21] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg12[23]_i_1_n_0 ),
        .D(s00_axi_wdata[21]),
        .Q(slv_reg12[21]),
        .R(RSTP));
  FDRE \slv_reg12_reg[22] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg12[23]_i_1_n_0 ),
        .D(s00_axi_wdata[22]),
        .Q(slv_reg12[22]),
        .R(RSTP));
  FDRE \slv_reg12_reg[23] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg12[23]_i_1_n_0 ),
        .D(s00_axi_wdata[23]),
        .Q(slv_reg12[23]),
        .R(RSTP));
  FDRE \slv_reg12_reg[24] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg12[31]_i_1_n_0 ),
        .D(s00_axi_wdata[24]),
        .Q(slv_reg12[24]),
        .R(RSTP));
  FDRE \slv_reg12_reg[25] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg12[31]_i_1_n_0 ),
        .D(s00_axi_wdata[25]),
        .Q(slv_reg12[25]),
        .R(RSTP));
  FDRE \slv_reg12_reg[26] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg12[31]_i_1_n_0 ),
        .D(s00_axi_wdata[26]),
        .Q(slv_reg12[26]),
        .R(RSTP));
  FDRE \slv_reg12_reg[27] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg12[31]_i_1_n_0 ),
        .D(s00_axi_wdata[27]),
        .Q(slv_reg12[27]),
        .R(RSTP));
  FDRE \slv_reg12_reg[28] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg12[31]_i_1_n_0 ),
        .D(s00_axi_wdata[28]),
        .Q(slv_reg12[28]),
        .R(RSTP));
  FDRE \slv_reg12_reg[29] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg12[31]_i_1_n_0 ),
        .D(s00_axi_wdata[29]),
        .Q(slv_reg12[29]),
        .R(RSTP));
  FDRE \slv_reg12_reg[2] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg12[7]_i_1_n_0 ),
        .D(s00_axi_wdata[2]),
        .Q(slv_reg12[2]),
        .R(RSTP));
  FDRE \slv_reg12_reg[30] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg12[31]_i_1_n_0 ),
        .D(s00_axi_wdata[30]),
        .Q(slv_reg12[30]),
        .R(RSTP));
  FDRE \slv_reg12_reg[31] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg12[31]_i_1_n_0 ),
        .D(s00_axi_wdata[31]),
        .Q(slv_reg12[31]),
        .R(RSTP));
  FDRE \slv_reg12_reg[3] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg12[7]_i_1_n_0 ),
        .D(s00_axi_wdata[3]),
        .Q(slv_reg12[3]),
        .R(RSTP));
  FDRE \slv_reg12_reg[4] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg12[7]_i_1_n_0 ),
        .D(s00_axi_wdata[4]),
        .Q(slv_reg12[4]),
        .R(RSTP));
  FDRE \slv_reg12_reg[5] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg12[7]_i_1_n_0 ),
        .D(s00_axi_wdata[5]),
        .Q(slv_reg12[5]),
        .R(RSTP));
  FDRE \slv_reg12_reg[6] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg12[7]_i_1_n_0 ),
        .D(s00_axi_wdata[6]),
        .Q(slv_reg12[6]),
        .R(RSTP));
  FDRE \slv_reg12_reg[7] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg12[7]_i_1_n_0 ),
        .D(s00_axi_wdata[7]),
        .Q(slv_reg12[7]),
        .R(RSTP));
  FDRE \slv_reg12_reg[8] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg12[15]_i_1_n_0 ),
        .D(s00_axi_wdata[8]),
        .Q(slv_reg12[8]),
        .R(RSTP));
  FDRE \slv_reg12_reg[9] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg12[15]_i_1_n_0 ),
        .D(s00_axi_wdata[9]),
        .Q(slv_reg12[9]),
        .R(RSTP));
  LUT6 #(
    .INIT(64'h0000000080000000)) 
    \slv_reg13[15]_i_1 
       (.I0(slv_reg_wren__0),
        .I1(p_0_in[2]),
        .I2(p_0_in[3]),
        .I3(p_0_in[0]),
        .I4(s00_axi_wstrb[1]),
        .I5(p_0_in[1]),
        .O(\slv_reg13[15]_i_1_n_0 ));
  LUT6 #(
    .INIT(64'h0000000080000000)) 
    \slv_reg13[23]_i_1 
       (.I0(slv_reg_wren__0),
        .I1(p_0_in[2]),
        .I2(p_0_in[3]),
        .I3(p_0_in[0]),
        .I4(s00_axi_wstrb[2]),
        .I5(p_0_in[1]),
        .O(\slv_reg13[23]_i_1_n_0 ));
  LUT6 #(
    .INIT(64'h0000000080000000)) 
    \slv_reg13[31]_i_1 
       (.I0(slv_reg_wren__0),
        .I1(p_0_in[2]),
        .I2(p_0_in[3]),
        .I3(p_0_in[0]),
        .I4(s00_axi_wstrb[3]),
        .I5(p_0_in[1]),
        .O(\slv_reg13[31]_i_1_n_0 ));
  LUT6 #(
    .INIT(64'h0000000080000000)) 
    \slv_reg13[7]_i_1 
       (.I0(slv_reg_wren__0),
        .I1(p_0_in[2]),
        .I2(p_0_in[3]),
        .I3(p_0_in[0]),
        .I4(s00_axi_wstrb[0]),
        .I5(p_0_in[1]),
        .O(\slv_reg13[7]_i_1_n_0 ));
  FDRE \slv_reg13_reg[0] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg13[7]_i_1_n_0 ),
        .D(s00_axi_wdata[0]),
        .Q(slv_reg13[0]),
        .R(RSTP));
  FDRE \slv_reg13_reg[10] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg13[15]_i_1_n_0 ),
        .D(s00_axi_wdata[10]),
        .Q(slv_reg13[10]),
        .R(RSTP));
  FDRE \slv_reg13_reg[11] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg13[15]_i_1_n_0 ),
        .D(s00_axi_wdata[11]),
        .Q(slv_reg13[11]),
        .R(RSTP));
  FDRE \slv_reg13_reg[12] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg13[15]_i_1_n_0 ),
        .D(s00_axi_wdata[12]),
        .Q(slv_reg13[12]),
        .R(RSTP));
  FDRE \slv_reg13_reg[13] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg13[15]_i_1_n_0 ),
        .D(s00_axi_wdata[13]),
        .Q(slv_reg13[13]),
        .R(RSTP));
  FDRE \slv_reg13_reg[14] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg13[15]_i_1_n_0 ),
        .D(s00_axi_wdata[14]),
        .Q(slv_reg13[14]),
        .R(RSTP));
  FDRE \slv_reg13_reg[15] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg13[15]_i_1_n_0 ),
        .D(s00_axi_wdata[15]),
        .Q(slv_reg13[15]),
        .R(RSTP));
  FDRE \slv_reg13_reg[16] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg13[23]_i_1_n_0 ),
        .D(s00_axi_wdata[16]),
        .Q(slv_reg13[16]),
        .R(RSTP));
  FDRE \slv_reg13_reg[17] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg13[23]_i_1_n_0 ),
        .D(s00_axi_wdata[17]),
        .Q(slv_reg13[17]),
        .R(RSTP));
  FDRE \slv_reg13_reg[18] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg13[23]_i_1_n_0 ),
        .D(s00_axi_wdata[18]),
        .Q(slv_reg13[18]),
        .R(RSTP));
  FDRE \slv_reg13_reg[19] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg13[23]_i_1_n_0 ),
        .D(s00_axi_wdata[19]),
        .Q(slv_reg13[19]),
        .R(RSTP));
  FDRE \slv_reg13_reg[1] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg13[7]_i_1_n_0 ),
        .D(s00_axi_wdata[1]),
        .Q(slv_reg13[1]),
        .R(RSTP));
  FDRE \slv_reg13_reg[20] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg13[23]_i_1_n_0 ),
        .D(s00_axi_wdata[20]),
        .Q(slv_reg13[20]),
        .R(RSTP));
  FDRE \slv_reg13_reg[21] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg13[23]_i_1_n_0 ),
        .D(s00_axi_wdata[21]),
        .Q(slv_reg13[21]),
        .R(RSTP));
  FDRE \slv_reg13_reg[22] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg13[23]_i_1_n_0 ),
        .D(s00_axi_wdata[22]),
        .Q(slv_reg13[22]),
        .R(RSTP));
  FDRE \slv_reg13_reg[23] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg13[23]_i_1_n_0 ),
        .D(s00_axi_wdata[23]),
        .Q(slv_reg13[23]),
        .R(RSTP));
  FDRE \slv_reg13_reg[24] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg13[31]_i_1_n_0 ),
        .D(s00_axi_wdata[24]),
        .Q(slv_reg13[24]),
        .R(RSTP));
  FDRE \slv_reg13_reg[25] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg13[31]_i_1_n_0 ),
        .D(s00_axi_wdata[25]),
        .Q(slv_reg13[25]),
        .R(RSTP));
  FDRE \slv_reg13_reg[26] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg13[31]_i_1_n_0 ),
        .D(s00_axi_wdata[26]),
        .Q(slv_reg13[26]),
        .R(RSTP));
  FDRE \slv_reg13_reg[27] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg13[31]_i_1_n_0 ),
        .D(s00_axi_wdata[27]),
        .Q(slv_reg13[27]),
        .R(RSTP));
  FDRE \slv_reg13_reg[28] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg13[31]_i_1_n_0 ),
        .D(s00_axi_wdata[28]),
        .Q(slv_reg13[28]),
        .R(RSTP));
  FDRE \slv_reg13_reg[29] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg13[31]_i_1_n_0 ),
        .D(s00_axi_wdata[29]),
        .Q(slv_reg13[29]),
        .R(RSTP));
  FDRE \slv_reg13_reg[2] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg13[7]_i_1_n_0 ),
        .D(s00_axi_wdata[2]),
        .Q(slv_reg13[2]),
        .R(RSTP));
  FDRE \slv_reg13_reg[30] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg13[31]_i_1_n_0 ),
        .D(s00_axi_wdata[30]),
        .Q(slv_reg13[30]),
        .R(RSTP));
  FDRE \slv_reg13_reg[31] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg13[31]_i_1_n_0 ),
        .D(s00_axi_wdata[31]),
        .Q(slv_reg13[31]),
        .R(RSTP));
  FDRE \slv_reg13_reg[3] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg13[7]_i_1_n_0 ),
        .D(s00_axi_wdata[3]),
        .Q(slv_reg13[3]),
        .R(RSTP));
  FDRE \slv_reg13_reg[4] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg13[7]_i_1_n_0 ),
        .D(s00_axi_wdata[4]),
        .Q(slv_reg13[4]),
        .R(RSTP));
  FDRE \slv_reg13_reg[5] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg13[7]_i_1_n_0 ),
        .D(s00_axi_wdata[5]),
        .Q(slv_reg13[5]),
        .R(RSTP));
  FDRE \slv_reg13_reg[6] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg13[7]_i_1_n_0 ),
        .D(s00_axi_wdata[6]),
        .Q(slv_reg13[6]),
        .R(RSTP));
  FDRE \slv_reg13_reg[7] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg13[7]_i_1_n_0 ),
        .D(s00_axi_wdata[7]),
        .Q(slv_reg13[7]),
        .R(RSTP));
  FDRE \slv_reg13_reg[8] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg13[15]_i_1_n_0 ),
        .D(s00_axi_wdata[8]),
        .Q(slv_reg13[8]),
        .R(RSTP));
  FDRE \slv_reg13_reg[9] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg13[15]_i_1_n_0 ),
        .D(s00_axi_wdata[9]),
        .Q(slv_reg13[9]),
        .R(RSTP));
  LUT6 #(
    .INIT(64'h0000000080000000)) 
    \slv_reg14[15]_i_1 
       (.I0(slv_reg_wren__0),
        .I1(p_0_in[2]),
        .I2(p_0_in[3]),
        .I3(s00_axi_wstrb[1]),
        .I4(p_0_in[1]),
        .I5(p_0_in[0]),
        .O(\slv_reg14[15]_i_1_n_0 ));
  LUT6 #(
    .INIT(64'h0000000080000000)) 
    \slv_reg14[23]_i_1 
       (.I0(slv_reg_wren__0),
        .I1(p_0_in[2]),
        .I2(p_0_in[3]),
        .I3(s00_axi_wstrb[2]),
        .I4(p_0_in[1]),
        .I5(p_0_in[0]),
        .O(\slv_reg14[23]_i_1_n_0 ));
  LUT6 #(
    .INIT(64'h0000000080000000)) 
    \slv_reg14[31]_i_1 
       (.I0(slv_reg_wren__0),
        .I1(p_0_in[2]),
        .I2(p_0_in[3]),
        .I3(s00_axi_wstrb[3]),
        .I4(p_0_in[1]),
        .I5(p_0_in[0]),
        .O(\slv_reg14[31]_i_1_n_0 ));
  LUT6 #(
    .INIT(64'h0000000080000000)) 
    \slv_reg14[7]_i_1 
       (.I0(slv_reg_wren__0),
        .I1(p_0_in[2]),
        .I2(p_0_in[3]),
        .I3(s00_axi_wstrb[0]),
        .I4(p_0_in[1]),
        .I5(p_0_in[0]),
        .O(\slv_reg14[7]_i_1_n_0 ));
  FDRE \slv_reg14_reg[0] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg14[7]_i_1_n_0 ),
        .D(s00_axi_wdata[0]),
        .Q(slv_reg14[0]),
        .R(RSTP));
  FDRE \slv_reg14_reg[10] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg14[15]_i_1_n_0 ),
        .D(s00_axi_wdata[10]),
        .Q(slv_reg14[10]),
        .R(RSTP));
  FDRE \slv_reg14_reg[11] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg14[15]_i_1_n_0 ),
        .D(s00_axi_wdata[11]),
        .Q(slv_reg14[11]),
        .R(RSTP));
  FDRE \slv_reg14_reg[12] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg14[15]_i_1_n_0 ),
        .D(s00_axi_wdata[12]),
        .Q(slv_reg14[12]),
        .R(RSTP));
  FDRE \slv_reg14_reg[13] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg14[15]_i_1_n_0 ),
        .D(s00_axi_wdata[13]),
        .Q(slv_reg14[13]),
        .R(RSTP));
  FDRE \slv_reg14_reg[14] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg14[15]_i_1_n_0 ),
        .D(s00_axi_wdata[14]),
        .Q(slv_reg14[14]),
        .R(RSTP));
  FDRE \slv_reg14_reg[15] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg14[15]_i_1_n_0 ),
        .D(s00_axi_wdata[15]),
        .Q(slv_reg14[15]),
        .R(RSTP));
  FDRE \slv_reg14_reg[16] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg14[23]_i_1_n_0 ),
        .D(s00_axi_wdata[16]),
        .Q(slv_reg14[16]),
        .R(RSTP));
  FDRE \slv_reg14_reg[17] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg14[23]_i_1_n_0 ),
        .D(s00_axi_wdata[17]),
        .Q(slv_reg14[17]),
        .R(RSTP));
  FDRE \slv_reg14_reg[18] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg14[23]_i_1_n_0 ),
        .D(s00_axi_wdata[18]),
        .Q(slv_reg14[18]),
        .R(RSTP));
  FDRE \slv_reg14_reg[19] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg14[23]_i_1_n_0 ),
        .D(s00_axi_wdata[19]),
        .Q(slv_reg14[19]),
        .R(RSTP));
  FDRE \slv_reg14_reg[1] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg14[7]_i_1_n_0 ),
        .D(s00_axi_wdata[1]),
        .Q(slv_reg14[1]),
        .R(RSTP));
  FDRE \slv_reg14_reg[20] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg14[23]_i_1_n_0 ),
        .D(s00_axi_wdata[20]),
        .Q(slv_reg14[20]),
        .R(RSTP));
  FDRE \slv_reg14_reg[21] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg14[23]_i_1_n_0 ),
        .D(s00_axi_wdata[21]),
        .Q(slv_reg14[21]),
        .R(RSTP));
  FDRE \slv_reg14_reg[22] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg14[23]_i_1_n_0 ),
        .D(s00_axi_wdata[22]),
        .Q(slv_reg14[22]),
        .R(RSTP));
  FDRE \slv_reg14_reg[23] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg14[23]_i_1_n_0 ),
        .D(s00_axi_wdata[23]),
        .Q(slv_reg14[23]),
        .R(RSTP));
  FDRE \slv_reg14_reg[24] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg14[31]_i_1_n_0 ),
        .D(s00_axi_wdata[24]),
        .Q(slv_reg14[24]),
        .R(RSTP));
  FDRE \slv_reg14_reg[25] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg14[31]_i_1_n_0 ),
        .D(s00_axi_wdata[25]),
        .Q(slv_reg14[25]),
        .R(RSTP));
  FDRE \slv_reg14_reg[26] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg14[31]_i_1_n_0 ),
        .D(s00_axi_wdata[26]),
        .Q(slv_reg14[26]),
        .R(RSTP));
  FDRE \slv_reg14_reg[27] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg14[31]_i_1_n_0 ),
        .D(s00_axi_wdata[27]),
        .Q(slv_reg14[27]),
        .R(RSTP));
  FDRE \slv_reg14_reg[28] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg14[31]_i_1_n_0 ),
        .D(s00_axi_wdata[28]),
        .Q(slv_reg14[28]),
        .R(RSTP));
  FDRE \slv_reg14_reg[29] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg14[31]_i_1_n_0 ),
        .D(s00_axi_wdata[29]),
        .Q(slv_reg14[29]),
        .R(RSTP));
  FDRE \slv_reg14_reg[2] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg14[7]_i_1_n_0 ),
        .D(s00_axi_wdata[2]),
        .Q(slv_reg14[2]),
        .R(RSTP));
  FDRE \slv_reg14_reg[30] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg14[31]_i_1_n_0 ),
        .D(s00_axi_wdata[30]),
        .Q(slv_reg14[30]),
        .R(RSTP));
  FDRE \slv_reg14_reg[31] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg14[31]_i_1_n_0 ),
        .D(s00_axi_wdata[31]),
        .Q(slv_reg14[31]),
        .R(RSTP));
  FDRE \slv_reg14_reg[3] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg14[7]_i_1_n_0 ),
        .D(s00_axi_wdata[3]),
        .Q(slv_reg14[3]),
        .R(RSTP));
  FDRE \slv_reg14_reg[4] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg14[7]_i_1_n_0 ),
        .D(s00_axi_wdata[4]),
        .Q(slv_reg14[4]),
        .R(RSTP));
  FDRE \slv_reg14_reg[5] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg14[7]_i_1_n_0 ),
        .D(s00_axi_wdata[5]),
        .Q(slv_reg14[5]),
        .R(RSTP));
  FDRE \slv_reg14_reg[6] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg14[7]_i_1_n_0 ),
        .D(s00_axi_wdata[6]),
        .Q(slv_reg14[6]),
        .R(RSTP));
  FDRE \slv_reg14_reg[7] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg14[7]_i_1_n_0 ),
        .D(s00_axi_wdata[7]),
        .Q(slv_reg14[7]),
        .R(RSTP));
  FDRE \slv_reg14_reg[8] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg14[15]_i_1_n_0 ),
        .D(s00_axi_wdata[8]),
        .Q(slv_reg14[8]),
        .R(RSTP));
  FDRE \slv_reg14_reg[9] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg14[15]_i_1_n_0 ),
        .D(s00_axi_wdata[9]),
        .Q(slv_reg14[9]),
        .R(RSTP));
  LUT6 #(
    .INIT(64'h8000000000000000)) 
    \slv_reg15[15]_i_1 
       (.I0(slv_reg_wren__0),
        .I1(p_0_in[2]),
        .I2(s00_axi_wstrb[1]),
        .I3(p_0_in[0]),
        .I4(p_0_in[1]),
        .I5(p_0_in[3]),
        .O(\slv_reg15[15]_i_1_n_0 ));
  LUT6 #(
    .INIT(64'h8000000000000000)) 
    \slv_reg15[23]_i_1 
       (.I0(slv_reg_wren__0),
        .I1(p_0_in[2]),
        .I2(s00_axi_wstrb[2]),
        .I3(p_0_in[0]),
        .I4(p_0_in[1]),
        .I5(p_0_in[3]),
        .O(\slv_reg15[23]_i_1_n_0 ));
  LUT6 #(
    .INIT(64'h8000000000000000)) 
    \slv_reg15[31]_i_1 
       (.I0(slv_reg_wren__0),
        .I1(p_0_in[2]),
        .I2(s00_axi_wstrb[3]),
        .I3(p_0_in[0]),
        .I4(p_0_in[1]),
        .I5(p_0_in[3]),
        .O(\slv_reg15[31]_i_1_n_0 ));
  LUT6 #(
    .INIT(64'h8000000000000000)) 
    \slv_reg15[7]_i_1 
       (.I0(slv_reg_wren__0),
        .I1(p_0_in[2]),
        .I2(s00_axi_wstrb[0]),
        .I3(p_0_in[0]),
        .I4(p_0_in[1]),
        .I5(p_0_in[3]),
        .O(\slv_reg15[7]_i_1_n_0 ));
  FDRE \slv_reg15_reg[0] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg15[7]_i_1_n_0 ),
        .D(s00_axi_wdata[0]),
        .Q(slv_reg15[0]),
        .R(RSTP));
  FDRE \slv_reg15_reg[10] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg15[15]_i_1_n_0 ),
        .D(s00_axi_wdata[10]),
        .Q(slv_reg15[10]),
        .R(RSTP));
  FDRE \slv_reg15_reg[11] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg15[15]_i_1_n_0 ),
        .D(s00_axi_wdata[11]),
        .Q(slv_reg15[11]),
        .R(RSTP));
  FDRE \slv_reg15_reg[12] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg15[15]_i_1_n_0 ),
        .D(s00_axi_wdata[12]),
        .Q(slv_reg15[12]),
        .R(RSTP));
  FDRE \slv_reg15_reg[13] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg15[15]_i_1_n_0 ),
        .D(s00_axi_wdata[13]),
        .Q(slv_reg15[13]),
        .R(RSTP));
  FDRE \slv_reg15_reg[14] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg15[15]_i_1_n_0 ),
        .D(s00_axi_wdata[14]),
        .Q(slv_reg15[14]),
        .R(RSTP));
  FDRE \slv_reg15_reg[15] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg15[15]_i_1_n_0 ),
        .D(s00_axi_wdata[15]),
        .Q(slv_reg15[15]),
        .R(RSTP));
  FDRE \slv_reg15_reg[16] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg15[23]_i_1_n_0 ),
        .D(s00_axi_wdata[16]),
        .Q(slv_reg15[16]),
        .R(RSTP));
  FDRE \slv_reg15_reg[17] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg15[23]_i_1_n_0 ),
        .D(s00_axi_wdata[17]),
        .Q(slv_reg15[17]),
        .R(RSTP));
  FDRE \slv_reg15_reg[18] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg15[23]_i_1_n_0 ),
        .D(s00_axi_wdata[18]),
        .Q(slv_reg15[18]),
        .R(RSTP));
  FDRE \slv_reg15_reg[19] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg15[23]_i_1_n_0 ),
        .D(s00_axi_wdata[19]),
        .Q(slv_reg15[19]),
        .R(RSTP));
  FDRE \slv_reg15_reg[1] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg15[7]_i_1_n_0 ),
        .D(s00_axi_wdata[1]),
        .Q(slv_reg15[1]),
        .R(RSTP));
  FDRE \slv_reg15_reg[20] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg15[23]_i_1_n_0 ),
        .D(s00_axi_wdata[20]),
        .Q(slv_reg15[20]),
        .R(RSTP));
  FDRE \slv_reg15_reg[21] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg15[23]_i_1_n_0 ),
        .D(s00_axi_wdata[21]),
        .Q(slv_reg15[21]),
        .R(RSTP));
  FDRE \slv_reg15_reg[22] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg15[23]_i_1_n_0 ),
        .D(s00_axi_wdata[22]),
        .Q(slv_reg15[22]),
        .R(RSTP));
  FDRE \slv_reg15_reg[23] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg15[23]_i_1_n_0 ),
        .D(s00_axi_wdata[23]),
        .Q(slv_reg15[23]),
        .R(RSTP));
  FDRE \slv_reg15_reg[24] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg15[31]_i_1_n_0 ),
        .D(s00_axi_wdata[24]),
        .Q(slv_reg15[24]),
        .R(RSTP));
  FDRE \slv_reg15_reg[25] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg15[31]_i_1_n_0 ),
        .D(s00_axi_wdata[25]),
        .Q(slv_reg15[25]),
        .R(RSTP));
  FDRE \slv_reg15_reg[26] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg15[31]_i_1_n_0 ),
        .D(s00_axi_wdata[26]),
        .Q(slv_reg15[26]),
        .R(RSTP));
  FDRE \slv_reg15_reg[27] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg15[31]_i_1_n_0 ),
        .D(s00_axi_wdata[27]),
        .Q(slv_reg15[27]),
        .R(RSTP));
  FDRE \slv_reg15_reg[28] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg15[31]_i_1_n_0 ),
        .D(s00_axi_wdata[28]),
        .Q(slv_reg15[28]),
        .R(RSTP));
  FDRE \slv_reg15_reg[29] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg15[31]_i_1_n_0 ),
        .D(s00_axi_wdata[29]),
        .Q(slv_reg15[29]),
        .R(RSTP));
  FDRE \slv_reg15_reg[2] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg15[7]_i_1_n_0 ),
        .D(s00_axi_wdata[2]),
        .Q(slv_reg15[2]),
        .R(RSTP));
  FDRE \slv_reg15_reg[30] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg15[31]_i_1_n_0 ),
        .D(s00_axi_wdata[30]),
        .Q(slv_reg15[30]),
        .R(RSTP));
  FDRE \slv_reg15_reg[31] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg15[31]_i_1_n_0 ),
        .D(s00_axi_wdata[31]),
        .Q(slv_reg15[31]),
        .R(RSTP));
  FDRE \slv_reg15_reg[3] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg15[7]_i_1_n_0 ),
        .D(s00_axi_wdata[3]),
        .Q(slv_reg15[3]),
        .R(RSTP));
  FDRE \slv_reg15_reg[4] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg15[7]_i_1_n_0 ),
        .D(s00_axi_wdata[4]),
        .Q(slv_reg15[4]),
        .R(RSTP));
  FDRE \slv_reg15_reg[5] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg15[7]_i_1_n_0 ),
        .D(s00_axi_wdata[5]),
        .Q(slv_reg15[5]),
        .R(RSTP));
  FDRE \slv_reg15_reg[6] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg15[7]_i_1_n_0 ),
        .D(s00_axi_wdata[6]),
        .Q(slv_reg15[6]),
        .R(RSTP));
  FDRE \slv_reg15_reg[7] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg15[7]_i_1_n_0 ),
        .D(s00_axi_wdata[7]),
        .Q(slv_reg15[7]),
        .R(RSTP));
  FDRE \slv_reg15_reg[8] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg15[15]_i_1_n_0 ),
        .D(s00_axi_wdata[8]),
        .Q(slv_reg15[8]),
        .R(RSTP));
  FDRE \slv_reg15_reg[9] 
       (.C(s00_axi_aclk),
        .CE(\slv_reg15[15]_i_1_n_0 ),
        .D(s00_axi_wdata[9]),
        .Q(slv_reg15[9]),
        .R(RSTP));
endmodule

(* ORIG_REF_NAME = "MULT_ADD" *) 
module zusys_A3_ADC_LTC2311_0_MULT_ADD
   (P,
    \S_RESULT_COUNTER_reg[0]_rep ,
    SI_VALUE0,
    \S_ENABLE_reg[0] ,
    \S_ENABLE_reg[0]_0 ,
    CO,
    \S_SAMPLE_TIME_COUNTER_reg[11] ,
    \curstate_reg[0] ,
    \S_SAMPLE_TIME_COUNTER_reg[23] ,
    \S_SAMPLE_TIME_COUNTER_reg[17] ,
    \S_CONV_COUNTER_reg[0] ,
    CEP,
    s00_axi_aclk,
    RSTP,
    Q,
    DSP_ALU_INST,
    \SI_VALUE_reg[34] ,
    \SI_VALUE_reg[209] ,
    \SI_VALUE_reg[209]_0 ,
    \SI_VALUE_reg[273] ,
    \SI_VALUE_reg[273]_0 ,
    \SI_VALUE_reg[206] ,
    DSP_A_B_DATA_INST,
    ENABLE,
    SI_VALID_reg,
    SI_VALID_reg_0,
    S_DUMMY_SAMPLE,
    \S_SAMPLE_TIME_COUNTER[30]_i_7 ,
    \SI_VALUE_reg[115] ,
    SI_VALID_reg_i_8_0,
    SI_VALID_reg_i_8_1,
    nxtstate3,
    S,
    SI_VALID_reg_i_3_0,
    SI_VALID_reg_i_3_1,
    SI_VALID_reg_i_3_2,
    SI_VALID_reg_i_3_3,
    DSP_A_B_DATA_INST_0,
    \SI_VALUE_reg[279] );
  output [0:0]P;
  output \S_RESULT_COUNTER_reg[0]_rep ;
  output [127:0]SI_VALUE0;
  output \S_ENABLE_reg[0] ;
  output \S_ENABLE_reg[0]_0 ;
  output [0:0]CO;
  output \S_SAMPLE_TIME_COUNTER_reg[11] ;
  output \curstate_reg[0] ;
  output \S_SAMPLE_TIME_COUNTER_reg[23] ;
  output \S_SAMPLE_TIME_COUNTER_reg[17] ;
  output \S_CONV_COUNTER_reg[0] ;
  input CEP;
  input s00_axi_aclk;
  input RSTP;
  input [15:0]Q;
  input [15:0]DSP_ALU_INST;
  input [3:0]\SI_VALUE_reg[34] ;
  input \SI_VALUE_reg[209] ;
  input \SI_VALUE_reg[209]_0 ;
  input \SI_VALUE_reg[273] ;
  input \SI_VALUE_reg[273]_0 ;
  input \SI_VALUE_reg[206] ;
  input [3:0]DSP_A_B_DATA_INST;
  input ENABLE;
  input [1:0]SI_VALID_reg;
  input [1:0]SI_VALID_reg_0;
  input S_DUMMY_SAMPLE;
  input [30:0]\S_SAMPLE_TIME_COUNTER[30]_i_7 ;
  input \SI_VALUE_reg[115] ;
  input [0:0]SI_VALID_reg_i_8_0;
  input SI_VALID_reg_i_8_1;
  input [29:0]nxtstate3;
  input [7:0]S;
  input [7:0]SI_VALID_reg_i_3_0;
  input [7:0]SI_VALID_reg_i_3_1;
  input [6:0]SI_VALID_reg_i_3_2;
  input [0:0]SI_VALID_reg_i_3_3;
  input [143:0]DSP_A_B_DATA_INST_0;
  input \SI_VALUE_reg[279] ;

  wire CEP;
  wire [0:0]CO;
  wire [15:0]DSP_ALU_INST;
  wire [3:0]DSP_A_B_DATA_INST;
  wire [143:0]DSP_A_B_DATA_INST_0;
  wire ENABLE;
  wire [0:0]P;
  wire [15:0]Q;
  wire RAW_VALID_i_3_n_0;
  wire RSTP;
  wire [7:0]S;
  wire SI_VALID_i_10_n_0;
  wire SI_VALID_i_11_n_0;
  wire SI_VALID_i_12_n_0;
  wire SI_VALID_i_13_n_0;
  wire SI_VALID_i_14_n_0;
  wire SI_VALID_i_15_n_0;
  wire SI_VALID_i_16_n_0;
  wire SI_VALID_i_17_n_0;
  wire SI_VALID_i_18_n_0;
  wire SI_VALID_i_19_n_0;
  wire SI_VALID_i_20_n_0;
  wire SI_VALID_i_21_n_0;
  wire SI_VALID_i_22_n_0;
  wire SI_VALID_i_23_n_0;
  wire SI_VALID_i_24_n_0;
  wire SI_VALID_i_25_n_0;
  wire SI_VALID_i_26_n_0;
  wire SI_VALID_i_27_n_0;
  wire SI_VALID_i_29_n_0;
  wire SI_VALID_i_31_n_0;
  wire SI_VALID_i_32_n_0;
  wire SI_VALID_i_33_n_0;
  wire SI_VALID_i_34_n_0;
  wire SI_VALID_i_35_n_0;
  wire SI_VALID_i_36_n_0;
  wire SI_VALID_i_37_n_0;
  wire SI_VALID_i_38_n_0;
  wire SI_VALID_i_39_n_0;
  wire SI_VALID_i_40_n_0;
  wire SI_VALID_i_41_n_0;
  wire SI_VALID_i_42_n_0;
  wire SI_VALID_i_43_n_0;
  wire SI_VALID_i_44_n_0;
  wire SI_VALID_i_45_n_0;
  wire SI_VALID_i_46_n_0;
  wire SI_VALID_i_47_n_0;
  wire SI_VALID_i_48_n_0;
  wire SI_VALID_i_6_n_0;
  wire SI_VALID_i_7_n_0;
  wire SI_VALID_i_9_n_0;
  wire [1:0]SI_VALID_reg;
  wire [1:0]SI_VALID_reg_0;
  wire [7:0]SI_VALID_reg_i_3_0;
  wire [7:0]SI_VALID_reg_i_3_1;
  wire [6:0]SI_VALID_reg_i_3_2;
  wire [0:0]SI_VALID_reg_i_3_3;
  wire SI_VALID_reg_i_3_n_1;
  wire SI_VALID_reg_i_3_n_2;
  wire SI_VALID_reg_i_3_n_3;
  wire SI_VALID_reg_i_3_n_4;
  wire SI_VALID_reg_i_3_n_5;
  wire SI_VALID_reg_i_3_n_6;
  wire SI_VALID_reg_i_3_n_7;
  wire [0:0]SI_VALID_reg_i_8_0;
  wire SI_VALID_reg_i_8_1;
  wire SI_VALID_reg_i_8_n_0;
  wire SI_VALID_reg_i_8_n_1;
  wire SI_VALID_reg_i_8_n_2;
  wire SI_VALID_reg_i_8_n_3;
  wire SI_VALID_reg_i_8_n_4;
  wire SI_VALID_reg_i_8_n_5;
  wire SI_VALID_reg_i_8_n_6;
  wire SI_VALID_reg_i_8_n_7;
  wire [127:0]SI_VALUE0;
  wire \SI_VALUE[105]_i_2_n_0 ;
  wire \SI_VALUE[106]_i_2_n_0 ;
  wire \SI_VALUE[106]_i_3_n_0 ;
  wire \SI_VALUE[107]_i_2_n_0 ;
  wire \SI_VALUE[140]_i_2_n_0 ;
  wire \SI_VALUE[141]_i_2_n_0 ;
  wire \SI_VALUE[141]_i_3_n_0 ;
  wire \SI_VALUE[141]_i_4_n_0 ;
  wire \SI_VALUE[142]_i_2_n_0 ;
  wire \SI_VALUE[142]_i_3_n_0 ;
  wire \SI_VALUE[142]_i_4_n_0 ;
  wire \SI_VALUE[142]_i_5_n_0 ;
  wire \SI_VALUE[142]_i_6_n_0 ;
  wire \SI_VALUE[142]_i_7_n_0 ;
  wire \SI_VALUE[142]_i_8_n_0 ;
  wire \SI_VALUE[175]_i_2_n_0 ;
  wire \SI_VALUE[175]_i_3_n_0 ;
  wire \SI_VALUE[175]_i_4_n_0 ;
  wire \SI_VALUE[175]_i_5_n_0 ;
  wire \SI_VALUE[175]_i_6_n_0 ;
  wire \SI_VALUE[175]_i_7_n_0 ;
  wire \SI_VALUE[176]_i_2_n_0 ;
  wire \SI_VALUE[176]_i_3_n_0 ;
  wire \SI_VALUE[176]_i_4_n_0 ;
  wire \SI_VALUE[176]_i_5_n_0 ;
  wire \SI_VALUE[176]_i_6_n_0 ;
  wire \SI_VALUE[176]_i_7_n_0 ;
  wire \SI_VALUE[177]_i_2_n_0 ;
  wire \SI_VALUE[177]_i_3_n_0 ;
  wire \SI_VALUE[177]_i_4_n_0 ;
  wire \SI_VALUE[177]_i_5_n_0 ;
  wire \SI_VALUE[177]_i_6_n_0 ;
  wire \SI_VALUE[177]_i_7_n_0 ;
  wire \SI_VALUE[177]_i_8_n_0 ;
  wire \SI_VALUE[177]_i_9_n_0 ;
  wire \SI_VALUE[178]_i_2_n_0 ;
  wire \SI_VALUE[179]_i_2_n_0 ;
  wire \SI_VALUE[180]_i_2_n_0 ;
  wire \SI_VALUE[207]_i_2_n_0 ;
  wire \SI_VALUE[211]_i_2_n_0 ;
  wire \SI_VALUE[211]_i_3_n_0 ;
  wire \SI_VALUE[211]_i_4_n_0 ;
  wire \SI_VALUE[212]_i_2_n_0 ;
  wire \SI_VALUE[212]_i_3_n_0 ;
  wire \SI_VALUE[212]_i_4_n_0 ;
  wire \SI_VALUE[245]_i_2_n_0 ;
  wire \SI_VALUE[246]_i_2_n_0 ;
  wire \SI_VALUE[247]_i_2_n_0 ;
  wire \SI_VALUE[248]_i_2_n_0 ;
  wire \SI_VALUE[248]_i_3_n_0 ;
  wire \SI_VALUE[249]_i_2_n_0 ;
  wire \SI_VALUE[250]_i_2_n_0 ;
  wire \SI_VALUE[251]_i_2_n_0 ;
  wire \SI_VALUE[252]_i_2_n_0 ;
  wire \SI_VALUE[253]_i_2_n_0 ;
  wire \SI_VALUE[254]_i_2_n_0 ;
  wire \SI_VALUE[255]_i_2_n_0 ;
  wire \SI_VALUE[256]_i_2_n_0 ;
  wire \SI_VALUE[257]_i_2_n_0 ;
  wire \SI_VALUE[258]_i_2_n_0 ;
  wire \SI_VALUE[259]_i_2_n_0 ;
  wire \SI_VALUE[260]_i_2_n_0 ;
  wire \SI_VALUE[261]_i_2_n_0 ;
  wire \SI_VALUE[262]_i_2_n_0 ;
  wire \SI_VALUE[262]_i_3_n_0 ;
  wire \SI_VALUE[263]_i_2_n_0 ;
  wire \SI_VALUE[263]_i_3_n_0 ;
  wire \SI_VALUE[264]_i_2_n_0 ;
  wire \SI_VALUE[264]_i_3_n_0 ;
  wire \SI_VALUE[265]_i_2_n_0 ;
  wire \SI_VALUE[265]_i_3_n_0 ;
  wire \SI_VALUE[266]_i_2_n_0 ;
  wire \SI_VALUE[266]_i_3_n_0 ;
  wire \SI_VALUE[266]_i_4_n_0 ;
  wire \SI_VALUE[267]_i_2_n_0 ;
  wire \SI_VALUE[267]_i_3_n_0 ;
  wire \SI_VALUE[267]_i_4_n_0 ;
  wire \SI_VALUE[268]_i_2_n_0 ;
  wire \SI_VALUE[268]_i_3_n_0 ;
  wire \SI_VALUE[268]_i_4_n_0 ;
  wire \SI_VALUE[268]_i_5_n_0 ;
  wire \SI_VALUE[269]_i_2_n_0 ;
  wire \SI_VALUE[269]_i_3_n_0 ;
  wire \SI_VALUE[269]_i_4_n_0 ;
  wire \SI_VALUE[269]_i_5_n_0 ;
  wire \SI_VALUE[270]_i_2_n_0 ;
  wire \SI_VALUE[270]_i_4_n_0 ;
  wire \SI_VALUE[270]_i_5_n_0 ;
  wire \SI_VALUE[271]_i_2_n_0 ;
  wire \SI_VALUE[271]_i_3_n_0 ;
  wire \SI_VALUE[271]_i_4_n_0 ;
  wire \SI_VALUE[271]_i_5_n_0 ;
  wire \SI_VALUE[272]_i_2_n_0 ;
  wire \SI_VALUE[272]_i_3_n_0 ;
  wire \SI_VALUE[272]_i_4_n_0 ;
  wire \SI_VALUE[272]_i_5_n_0 ;
  wire \SI_VALUE[272]_i_6_n_0 ;
  wire \SI_VALUE[273]_i_3_n_0 ;
  wire \SI_VALUE[273]_i_5_n_0 ;
  wire \SI_VALUE[273]_i_6_n_0 ;
  wire \SI_VALUE[273]_i_7_n_0 ;
  wire \SI_VALUE[274]_i_2_n_0 ;
  wire \SI_VALUE[274]_i_3_n_0 ;
  wire \SI_VALUE[274]_i_4_n_0 ;
  wire \SI_VALUE[274]_i_5_n_0 ;
  wire \SI_VALUE[275]_i_2_n_0 ;
  wire \SI_VALUE[275]_i_3_n_0 ;
  wire \SI_VALUE[275]_i_4_n_0 ;
  wire \SI_VALUE[275]_i_5_n_0 ;
  wire \SI_VALUE[276]_i_10_n_0 ;
  wire \SI_VALUE[276]_i_2_n_0 ;
  wire \SI_VALUE[276]_i_3_n_0 ;
  wire \SI_VALUE[276]_i_4_n_0 ;
  wire \SI_VALUE[276]_i_5_n_0 ;
  wire \SI_VALUE[276]_i_6_n_0 ;
  wire \SI_VALUE[276]_i_7_n_0 ;
  wire \SI_VALUE[276]_i_8_n_0 ;
  wire \SI_VALUE[276]_i_9_n_0 ;
  wire \SI_VALUE[277]_i_2_n_0 ;
  wire \SI_VALUE[277]_i_3_n_0 ;
  wire \SI_VALUE[277]_i_4_n_0 ;
  wire \SI_VALUE[277]_i_5_n_0 ;
  wire \SI_VALUE[277]_i_6_n_0 ;
  wire \SI_VALUE[277]_i_7_n_0 ;
  wire \SI_VALUE[277]_i_8_n_0 ;
  wire \SI_VALUE[278]_i_2_n_0 ;
  wire \SI_VALUE[278]_i_3_n_0 ;
  wire \SI_VALUE[278]_i_4_n_0 ;
  wire \SI_VALUE[278]_i_5_n_0 ;
  wire \SI_VALUE[278]_i_6_n_0 ;
  wire \SI_VALUE[278]_i_7_n_0 ;
  wire \SI_VALUE[278]_i_8_n_0 ;
  wire \SI_VALUE[279]_i_10_n_0 ;
  wire \SI_VALUE[279]_i_11_n_0 ;
  wire \SI_VALUE[279]_i_4_n_0 ;
  wire \SI_VALUE[279]_i_5_n_0 ;
  wire \SI_VALUE[279]_i_8_n_0 ;
  wire \SI_VALUE[279]_i_9_n_0 ;
  wire \SI_VALUE[2]_i_2_n_0 ;
  wire \SI_VALUE_reg[115] ;
  wire \SI_VALUE_reg[206] ;
  wire \SI_VALUE_reg[209] ;
  wire \SI_VALUE_reg[209]_0 ;
  wire \SI_VALUE_reg[273] ;
  wire \SI_VALUE_reg[273]_0 ;
  wire \SI_VALUE_reg[279] ;
  wire [3:0]\SI_VALUE_reg[34] ;
  wire \S_CONV_COUNTER_reg[0] ;
  wire S_DUMMY_SAMPLE;
  wire \S_ENABLE_reg[0] ;
  wire \S_ENABLE_reg[0]_0 ;
  wire S_MULT_reg_i_10_n_0;
  wire S_MULT_reg_i_11_n_0;
  wire S_MULT_reg_i_12_n_0;
  wire S_MULT_reg_i_13_n_0;
  wire S_MULT_reg_i_14_n_0;
  wire S_MULT_reg_i_15_n_0;
  wire S_MULT_reg_i_16_n_0;
  wire S_MULT_reg_i_17_n_0;
  wire S_MULT_reg_i_18_n_0;
  wire S_MULT_reg_i_19_n_0;
  wire S_MULT_reg_i_1_n_0;
  wire S_MULT_reg_i_21_n_0;
  wire S_MULT_reg_i_22_n_0;
  wire S_MULT_reg_i_23_n_0;
  wire S_MULT_reg_i_24_n_0;
  wire S_MULT_reg_i_25_n_0;
  wire S_MULT_reg_i_26_n_0;
  wire S_MULT_reg_i_27_n_0;
  wire S_MULT_reg_i_28_n_0;
  wire S_MULT_reg_i_29_n_0;
  wire S_MULT_reg_i_2_n_0;
  wire S_MULT_reg_i_30_n_0;
  wire S_MULT_reg_i_31_n_0;
  wire S_MULT_reg_i_32_n_0;
  wire S_MULT_reg_i_33_n_0;
  wire S_MULT_reg_i_34_n_0;
  wire S_MULT_reg_i_35_n_0;
  wire S_MULT_reg_i_36_n_0;
  wire S_MULT_reg_i_37_n_0;
  wire S_MULT_reg_i_38_n_0;
  wire S_MULT_reg_i_39_n_0;
  wire S_MULT_reg_i_3_n_0;
  wire S_MULT_reg_i_40_n_0;
  wire S_MULT_reg_i_41_n_0;
  wire S_MULT_reg_i_42_n_0;
  wire S_MULT_reg_i_43_n_0;
  wire S_MULT_reg_i_44_n_0;
  wire S_MULT_reg_i_45_n_0;
  wire S_MULT_reg_i_46_n_0;
  wire S_MULT_reg_i_47_n_0;
  wire S_MULT_reg_i_48_n_0;
  wire S_MULT_reg_i_49_n_0;
  wire S_MULT_reg_i_4_n_0;
  wire S_MULT_reg_i_50_n_0;
  wire S_MULT_reg_i_51_n_0;
  wire S_MULT_reg_i_52_n_0;
  wire S_MULT_reg_i_53_n_0;
  wire S_MULT_reg_i_54_n_0;
  wire S_MULT_reg_i_55_n_0;
  wire S_MULT_reg_i_56_n_0;
  wire S_MULT_reg_i_5_n_0;
  wire S_MULT_reg_i_6_n_0;
  wire S_MULT_reg_i_7_n_0;
  wire S_MULT_reg_i_8_n_0;
  wire S_MULT_reg_i_9_n_0;
  wire \S_RESULT_COUNTER_reg[0]_rep ;
  wire [34:0]S_RESULT_S_C;
  wire [30:0]\S_SAMPLE_TIME_COUNTER[30]_i_7 ;
  wire \S_SAMPLE_TIME_COUNTER_reg[11] ;
  wire \S_SAMPLE_TIME_COUNTER_reg[17] ;
  wire \S_SAMPLE_TIME_COUNTER_reg[23] ;
  wire \curstate_reg[0] ;
  wire [29:0]nxtstate3;
  wire s00_axi_aclk;
  wire [7:0]NLW_SI_VALID_reg_i_3_O_UNCONNECTED;
  wire [7:0]NLW_SI_VALID_reg_i_8_O_UNCONNECTED;
  wire NLW_S_MULT_reg_CARRYCASCOUT_UNCONNECTED;
  wire NLW_S_MULT_reg_MULTSIGNOUT_UNCONNECTED;
  wire NLW_S_MULT_reg_OVERFLOW_UNCONNECTED;
  wire NLW_S_MULT_reg_PATTERNBDETECT_UNCONNECTED;
  wire NLW_S_MULT_reg_PATTERNDETECT_UNCONNECTED;
  wire NLW_S_MULT_reg_UNDERFLOW_UNCONNECTED;
  wire [29:0]NLW_S_MULT_reg_ACOUT_UNCONNECTED;
  wire [17:0]NLW_S_MULT_reg_BCOUT_UNCONNECTED;
  wire [3:0]NLW_S_MULT_reg_CARRYOUT_UNCONNECTED;
  wire [47:35]NLW_S_MULT_reg_P_UNCONNECTED;
  wire [47:0]NLW_S_MULT_reg_PCOUT_UNCONNECTED;
  wire [7:0]NLW_S_MULT_reg_XOROUT_UNCONNECTED;

  LUT6 #(
    .INIT(64'h1055105510555555)) 
    RAW_VALID_i_2
       (.I0(RAW_VALID_i_3_n_0),
        .I1(ENABLE),
        .I2(CO),
        .I3(SI_VALID_reg[0]),
        .I4(\S_SAMPLE_TIME_COUNTER_reg[11] ),
        .I5(SI_VALID_i_6_n_0),
        .O(\S_ENABLE_reg[0]_0 ));
  (* SOFT_HLUTNM = "soft_lutpair36" *) 
  LUT5 #(
    .INIT(32'hFF2200F0)) 
    RAW_VALID_i_3
       (.I0(SI_VALID_reg_0[1]),
        .I1(SI_VALID_reg_0[0]),
        .I2(ENABLE),
        .I3(SI_VALID_reg[0]),
        .I4(SI_VALID_reg[1]),
        .O(RAW_VALID_i_3_n_0));
  LUT4 #(
    .INIT(16'h22B2)) 
    SI_VALID_i_10
       (.I0(SI_VALID_reg_i_3_2[4]),
        .I1(nxtstate3[28]),
        .I2(SI_VALID_reg_i_3_2[3]),
        .I3(nxtstate3[27]),
        .O(SI_VALID_i_10_n_0));
  LUT4 #(
    .INIT(16'h22B2)) 
    SI_VALID_i_11
       (.I0(SI_VALID_reg_i_3_2[2]),
        .I1(nxtstate3[26]),
        .I2(SI_VALID_reg_i_3_2[1]),
        .I3(nxtstate3[25]),
        .O(SI_VALID_i_11_n_0));
  LUT4 #(
    .INIT(16'h22B2)) 
    SI_VALID_i_12
       (.I0(SI_VALID_reg_i_3_2[0]),
        .I1(nxtstate3[24]),
        .I2(SI_VALID_reg_i_3_1[7]),
        .I3(nxtstate3[23]),
        .O(SI_VALID_i_12_n_0));
  LUT4 #(
    .INIT(16'h22B2)) 
    SI_VALID_i_13
       (.I0(SI_VALID_reg_i_3_1[6]),
        .I1(nxtstate3[22]),
        .I2(SI_VALID_reg_i_3_1[5]),
        .I3(nxtstate3[21]),
        .O(SI_VALID_i_13_n_0));
  LUT4 #(
    .INIT(16'h22B2)) 
    SI_VALID_i_14
       (.I0(SI_VALID_reg_i_3_1[4]),
        .I1(nxtstate3[20]),
        .I2(SI_VALID_reg_i_3_1[3]),
        .I3(nxtstate3[19]),
        .O(SI_VALID_i_14_n_0));
  LUT4 #(
    .INIT(16'h22B2)) 
    SI_VALID_i_15
       (.I0(SI_VALID_reg_i_3_1[2]),
        .I1(nxtstate3[18]),
        .I2(SI_VALID_reg_i_3_1[1]),
        .I3(nxtstate3[17]),
        .O(SI_VALID_i_15_n_0));
  LUT4 #(
    .INIT(16'h22B2)) 
    SI_VALID_i_16
       (.I0(SI_VALID_reg_i_3_1[0]),
        .I1(nxtstate3[16]),
        .I2(SI_VALID_reg_i_3_0[7]),
        .I3(nxtstate3[15]),
        .O(SI_VALID_i_16_n_0));
  LUT4 #(
    .INIT(16'h6006)) 
    SI_VALID_i_17
       (.I0(SI_VALID_reg_i_3_2[6]),
        .I1(SI_VALID_reg_i_3_3),
        .I2(nxtstate3[29]),
        .I3(SI_VALID_reg_i_3_2[5]),
        .O(SI_VALID_i_17_n_0));
  LUT4 #(
    .INIT(16'h9009)) 
    SI_VALID_i_18
       (.I0(nxtstate3[28]),
        .I1(SI_VALID_reg_i_3_2[4]),
        .I2(nxtstate3[27]),
        .I3(SI_VALID_reg_i_3_2[3]),
        .O(SI_VALID_i_18_n_0));
  LUT4 #(
    .INIT(16'h9009)) 
    SI_VALID_i_19
       (.I0(nxtstate3[26]),
        .I1(SI_VALID_reg_i_3_2[2]),
        .I2(nxtstate3[25]),
        .I3(SI_VALID_reg_i_3_2[1]),
        .O(SI_VALID_i_19_n_0));
  LUT6 #(
    .INIT(64'h00000000FFFFFF4F)) 
    SI_VALID_i_2
       (.I0(ENABLE),
        .I1(CO),
        .I2(\curstate_reg[0] ),
        .I3(\S_SAMPLE_TIME_COUNTER_reg[11] ),
        .I4(SI_VALID_i_6_n_0),
        .I5(SI_VALID_i_7_n_0),
        .O(\S_ENABLE_reg[0] ));
  LUT4 #(
    .INIT(16'h9009)) 
    SI_VALID_i_20
       (.I0(nxtstate3[24]),
        .I1(SI_VALID_reg_i_3_2[0]),
        .I2(nxtstate3[23]),
        .I3(SI_VALID_reg_i_3_1[7]),
        .O(SI_VALID_i_20_n_0));
  LUT4 #(
    .INIT(16'h9009)) 
    SI_VALID_i_21
       (.I0(nxtstate3[22]),
        .I1(SI_VALID_reg_i_3_1[6]),
        .I2(nxtstate3[21]),
        .I3(SI_VALID_reg_i_3_1[5]),
        .O(SI_VALID_i_21_n_0));
  LUT4 #(
    .INIT(16'h9009)) 
    SI_VALID_i_22
       (.I0(nxtstate3[20]),
        .I1(SI_VALID_reg_i_3_1[4]),
        .I2(nxtstate3[19]),
        .I3(SI_VALID_reg_i_3_1[3]),
        .O(SI_VALID_i_22_n_0));
  LUT4 #(
    .INIT(16'h9009)) 
    SI_VALID_i_23
       (.I0(nxtstate3[18]),
        .I1(SI_VALID_reg_i_3_1[2]),
        .I2(nxtstate3[17]),
        .I3(SI_VALID_reg_i_3_1[1]),
        .O(SI_VALID_i_23_n_0));
  LUT4 #(
    .INIT(16'h9009)) 
    SI_VALID_i_24
       (.I0(nxtstate3[16]),
        .I1(SI_VALID_reg_i_3_1[0]),
        .I2(nxtstate3[15]),
        .I3(SI_VALID_reg_i_3_0[7]),
        .O(SI_VALID_i_24_n_0));
  LUT4 #(
    .INIT(16'hFFFE)) 
    SI_VALID_i_25
       (.I0(\S_SAMPLE_TIME_COUNTER[30]_i_7 [9]),
        .I1(\S_SAMPLE_TIME_COUNTER[30]_i_7 [12]),
        .I2(\S_SAMPLE_TIME_COUNTER[30]_i_7 [0]),
        .I3(\S_SAMPLE_TIME_COUNTER[30]_i_7 [20]),
        .O(SI_VALID_i_25_n_0));
  LUT4 #(
    .INIT(16'hFFFE)) 
    SI_VALID_i_26
       (.I0(\S_SAMPLE_TIME_COUNTER[30]_i_7 [13]),
        .I1(\S_SAMPLE_TIME_COUNTER[30]_i_7 [14]),
        .I2(\S_SAMPLE_TIME_COUNTER[30]_i_7 [4]),
        .I3(\S_SAMPLE_TIME_COUNTER[30]_i_7 [16]),
        .O(SI_VALID_i_26_n_0));
  LUT4 #(
    .INIT(16'hFFFE)) 
    SI_VALID_i_27
       (.I0(\S_SAMPLE_TIME_COUNTER[30]_i_7 [5]),
        .I1(\S_SAMPLE_TIME_COUNTER[30]_i_7 [7]),
        .I2(\S_SAMPLE_TIME_COUNTER[30]_i_7 [8]),
        .I3(\S_SAMPLE_TIME_COUNTER[30]_i_7 [15]),
        .O(SI_VALID_i_27_n_0));
  LUT4 #(
    .INIT(16'hFFFE)) 
    SI_VALID_i_28
       (.I0(\S_SAMPLE_TIME_COUNTER[30]_i_7 [23]),
        .I1(\S_SAMPLE_TIME_COUNTER[30]_i_7 [28]),
        .I2(\S_SAMPLE_TIME_COUNTER[30]_i_7 [2]),
        .I3(\S_SAMPLE_TIME_COUNTER[30]_i_7 [30]),
        .O(\S_SAMPLE_TIME_COUNTER_reg[23] ));
  LUT4 #(
    .INIT(16'hFFFE)) 
    SI_VALID_i_29
       (.I0(\S_SAMPLE_TIME_COUNTER[30]_i_7 [10]),
        .I1(\S_SAMPLE_TIME_COUNTER[30]_i_7 [24]),
        .I2(\S_SAMPLE_TIME_COUNTER[30]_i_7 [18]),
        .I3(\S_SAMPLE_TIME_COUNTER[30]_i_7 [22]),
        .O(SI_VALID_i_29_n_0));
  LUT4 #(
    .INIT(16'hFFFE)) 
    SI_VALID_i_30
       (.I0(\S_SAMPLE_TIME_COUNTER[30]_i_7 [17]),
        .I1(\S_SAMPLE_TIME_COUNTER[30]_i_7 [25]),
        .I2(\S_SAMPLE_TIME_COUNTER[30]_i_7 [3]),
        .I3(\S_SAMPLE_TIME_COUNTER[30]_i_7 [29]),
        .O(\S_SAMPLE_TIME_COUNTER_reg[17] ));
  LUT4 #(
    .INIT(16'hFFFE)) 
    SI_VALID_i_31
       (.I0(\S_SAMPLE_TIME_COUNTER[30]_i_7 [6]),
        .I1(\S_SAMPLE_TIME_COUNTER[30]_i_7 [26]),
        .I2(\S_SAMPLE_TIME_COUNTER[30]_i_7 [19]),
        .I3(\S_SAMPLE_TIME_COUNTER[30]_i_7 [27]),
        .O(SI_VALID_i_31_n_0));
  (* SOFT_HLUTNM = "soft_lutpair34" *) 
  LUT4 #(
    .INIT(16'h0001)) 
    SI_VALID_i_32
       (.I0(\SI_VALUE_reg[34] [2]),
        .I1(\SI_VALUE_reg[34] [3]),
        .I2(\SI_VALUE_reg[209]_0 ),
        .I3(\SI_VALUE_reg[209] ),
        .O(SI_VALID_i_32_n_0));
  LUT4 #(
    .INIT(16'h22B2)) 
    SI_VALID_i_33
       (.I0(SI_VALID_reg_i_3_0[6]),
        .I1(nxtstate3[14]),
        .I2(SI_VALID_reg_i_3_0[5]),
        .I3(nxtstate3[13]),
        .O(SI_VALID_i_33_n_0));
  LUT4 #(
    .INIT(16'h22B2)) 
    SI_VALID_i_34
       (.I0(SI_VALID_reg_i_3_0[4]),
        .I1(nxtstate3[12]),
        .I2(SI_VALID_reg_i_3_0[3]),
        .I3(nxtstate3[11]),
        .O(SI_VALID_i_34_n_0));
  LUT4 #(
    .INIT(16'h22B2)) 
    SI_VALID_i_35
       (.I0(SI_VALID_reg_i_3_0[2]),
        .I1(nxtstate3[10]),
        .I2(SI_VALID_reg_i_3_0[1]),
        .I3(nxtstate3[9]),
        .O(SI_VALID_i_35_n_0));
  LUT4 #(
    .INIT(16'h22B2)) 
    SI_VALID_i_36
       (.I0(SI_VALID_reg_i_3_0[0]),
        .I1(nxtstate3[8]),
        .I2(S[7]),
        .I3(nxtstate3[7]),
        .O(SI_VALID_i_36_n_0));
  LUT4 #(
    .INIT(16'h22B2)) 
    SI_VALID_i_37
       (.I0(S[6]),
        .I1(nxtstate3[6]),
        .I2(S[5]),
        .I3(nxtstate3[5]),
        .O(SI_VALID_i_37_n_0));
  LUT4 #(
    .INIT(16'h22B2)) 
    SI_VALID_i_38
       (.I0(S[4]),
        .I1(nxtstate3[4]),
        .I2(S[3]),
        .I3(nxtstate3[3]),
        .O(SI_VALID_i_38_n_0));
  LUT4 #(
    .INIT(16'h22B2)) 
    SI_VALID_i_39
       (.I0(S[2]),
        .I1(nxtstate3[2]),
        .I2(S[1]),
        .I3(nxtstate3[1]),
        .O(SI_VALID_i_39_n_0));
  (* SOFT_HLUTNM = "soft_lutpair36" *) 
  LUT2 #(
    .INIT(4'h2)) 
    SI_VALID_i_4
       (.I0(SI_VALID_reg[0]),
        .I1(SI_VALID_reg[1]),
        .O(\curstate_reg[0] ));
  LUT4 #(
    .INIT(16'hB222)) 
    SI_VALID_i_40
       (.I0(S[0]),
        .I1(nxtstate3[0]),
        .I2(SI_VALID_reg_i_8_1),
        .I3(SI_VALID_reg_i_8_0),
        .O(SI_VALID_i_40_n_0));
  LUT4 #(
    .INIT(16'h9009)) 
    SI_VALID_i_41
       (.I0(nxtstate3[14]),
        .I1(SI_VALID_reg_i_3_0[6]),
        .I2(nxtstate3[13]),
        .I3(SI_VALID_reg_i_3_0[5]),
        .O(SI_VALID_i_41_n_0));
  LUT4 #(
    .INIT(16'h9009)) 
    SI_VALID_i_42
       (.I0(nxtstate3[12]),
        .I1(SI_VALID_reg_i_3_0[4]),
        .I2(nxtstate3[11]),
        .I3(SI_VALID_reg_i_3_0[3]),
        .O(SI_VALID_i_42_n_0));
  LUT4 #(
    .INIT(16'h9009)) 
    SI_VALID_i_43
       (.I0(nxtstate3[10]),
        .I1(SI_VALID_reg_i_3_0[2]),
        .I2(nxtstate3[9]),
        .I3(SI_VALID_reg_i_3_0[1]),
        .O(SI_VALID_i_43_n_0));
  LUT4 #(
    .INIT(16'h9009)) 
    SI_VALID_i_44
       (.I0(nxtstate3[8]),
        .I1(SI_VALID_reg_i_3_0[0]),
        .I2(nxtstate3[7]),
        .I3(S[7]),
        .O(SI_VALID_i_44_n_0));
  LUT4 #(
    .INIT(16'h9009)) 
    SI_VALID_i_45
       (.I0(nxtstate3[6]),
        .I1(S[6]),
        .I2(nxtstate3[5]),
        .I3(S[5]),
        .O(SI_VALID_i_45_n_0));
  LUT4 #(
    .INIT(16'h9009)) 
    SI_VALID_i_46
       (.I0(nxtstate3[4]),
        .I1(S[4]),
        .I2(nxtstate3[3]),
        .I3(S[3]),
        .O(SI_VALID_i_46_n_0));
  LUT4 #(
    .INIT(16'h9009)) 
    SI_VALID_i_47
       (.I0(nxtstate3[2]),
        .I1(S[2]),
        .I2(nxtstate3[1]),
        .I3(S[1]),
        .O(SI_VALID_i_47_n_0));
  LUT4 #(
    .INIT(16'h6006)) 
    SI_VALID_i_48
       (.I0(SI_VALID_reg_i_8_0),
        .I1(SI_VALID_reg_i_8_1),
        .I2(nxtstate3[0]),
        .I3(S[0]),
        .O(SI_VALID_i_48_n_0));
  LUT6 #(
    .INIT(64'hFFFFFFFFFFFFFFFE)) 
    SI_VALID_i_5
       (.I0(SI_VALID_i_25_n_0),
        .I1(SI_VALID_i_26_n_0),
        .I2(SI_VALID_i_27_n_0),
        .I3(\S_SAMPLE_TIME_COUNTER[30]_i_7 [11]),
        .I4(\S_SAMPLE_TIME_COUNTER[30]_i_7 [1]),
        .I5(\S_SAMPLE_TIME_COUNTER[30]_i_7 [21]),
        .O(\S_SAMPLE_TIME_COUNTER_reg[11] ));
  LUT4 #(
    .INIT(16'hFFFE)) 
    SI_VALID_i_6
       (.I0(\S_SAMPLE_TIME_COUNTER_reg[23] ),
        .I1(SI_VALID_i_29_n_0),
        .I2(\S_SAMPLE_TIME_COUNTER_reg[17] ),
        .I3(SI_VALID_i_31_n_0),
        .O(SI_VALID_i_6_n_0));
  LUT6 #(
    .INIT(64'h0000DF00FF00DF00)) 
    SI_VALID_i_7
       (.I0(S_DUMMY_SAMPLE),
        .I1(SI_VALID_reg_0[0]),
        .I2(SI_VALID_reg_0[1]),
        .I3(SI_VALID_reg[1]),
        .I4(SI_VALID_reg[0]),
        .I5(SI_VALID_i_32_n_0),
        .O(SI_VALID_i_7_n_0));
  LUT4 #(
    .INIT(16'h1171)) 
    SI_VALID_i_9
       (.I0(SI_VALID_reg_i_3_3),
        .I1(SI_VALID_reg_i_3_2[6]),
        .I2(SI_VALID_reg_i_3_2[5]),
        .I3(nxtstate3[29]),
        .O(SI_VALID_i_9_n_0));
  (* COMPARATOR_THRESHOLD = "11" *) 
  CARRY8 SI_VALID_reg_i_3
       (.CI(SI_VALID_reg_i_8_n_0),
        .CI_TOP(1'b0),
        .CO({CO,SI_VALID_reg_i_3_n_1,SI_VALID_reg_i_3_n_2,SI_VALID_reg_i_3_n_3,SI_VALID_reg_i_3_n_4,SI_VALID_reg_i_3_n_5,SI_VALID_reg_i_3_n_6,SI_VALID_reg_i_3_n_7}),
        .DI({SI_VALID_i_9_n_0,SI_VALID_i_10_n_0,SI_VALID_i_11_n_0,SI_VALID_i_12_n_0,SI_VALID_i_13_n_0,SI_VALID_i_14_n_0,SI_VALID_i_15_n_0,SI_VALID_i_16_n_0}),
        .O(NLW_SI_VALID_reg_i_3_O_UNCONNECTED[7:0]),
        .S({SI_VALID_i_17_n_0,SI_VALID_i_18_n_0,SI_VALID_i_19_n_0,SI_VALID_i_20_n_0,SI_VALID_i_21_n_0,SI_VALID_i_22_n_0,SI_VALID_i_23_n_0,SI_VALID_i_24_n_0}));
  (* COMPARATOR_THRESHOLD = "11" *) 
  CARRY8 SI_VALID_reg_i_8
       (.CI(1'b1),
        .CI_TOP(1'b0),
        .CO({SI_VALID_reg_i_8_n_0,SI_VALID_reg_i_8_n_1,SI_VALID_reg_i_8_n_2,SI_VALID_reg_i_8_n_3,SI_VALID_reg_i_8_n_4,SI_VALID_reg_i_8_n_5,SI_VALID_reg_i_8_n_6,SI_VALID_reg_i_8_n_7}),
        .DI({SI_VALID_i_33_n_0,SI_VALID_i_34_n_0,SI_VALID_i_35_n_0,SI_VALID_i_36_n_0,SI_VALID_i_37_n_0,SI_VALID_i_38_n_0,SI_VALID_i_39_n_0,SI_VALID_i_40_n_0}),
        .O(NLW_SI_VALID_reg_i_8_O_UNCONNECTED[7:0]),
        .S({SI_VALID_i_41_n_0,SI_VALID_i_42_n_0,SI_VALID_i_43_n_0,SI_VALID_i_44_n_0,SI_VALID_i_45_n_0,SI_VALID_i_46_n_0,SI_VALID_i_47_n_0,SI_VALID_i_48_n_0}));
  LUT5 #(
    .INIT(32'h00010000)) 
    \SI_VALUE[0]_i_1 
       (.I0(\SI_VALUE_reg[34] [3]),
        .I1(\SI_VALUE_reg[34] [2]),
        .I2(\SI_VALUE_reg[34] [1]),
        .I3(\SI_VALUE_reg[34] [0]),
        .I4(S_RESULT_S_C[0]),
        .O(SI_VALUE0[0]));
  LUT6 #(
    .INIT(64'h0101100001011333)) 
    \SI_VALUE[105]_i_1 
       (.I0(\SI_VALUE[105]_i_2_n_0 ),
        .I1(\SI_VALUE_reg[34] [3]),
        .I2(\SI_VALUE_reg[209]_0 ),
        .I3(\SI_VALUE_reg[209] ),
        .I4(\SI_VALUE_reg[34] [2]),
        .I5(\SI_VALUE[177]_i_2_n_0 ),
        .O(SI_VALUE0[47]));
  LUT5 #(
    .INIT(32'hFF7CFF7F)) 
    \SI_VALUE[105]_i_2 
       (.I0(S_RESULT_S_C[0]),
        .I1(\SI_VALUE_reg[209] ),
        .I2(\SI_VALUE_reg[209]_0 ),
        .I3(\SI_VALUE_reg[34] [2]),
        .I4(S_RESULT_S_C[1]),
        .O(\SI_VALUE[105]_i_2_n_0 ));
  LUT6 #(
    .INIT(64'h0101100001011333)) 
    \SI_VALUE[106]_i_1 
       (.I0(\SI_VALUE[106]_i_2_n_0 ),
        .I1(\SI_VALUE_reg[34] [3]),
        .I2(\SI_VALUE_reg[209]_0 ),
        .I3(\SI_VALUE_reg[209] ),
        .I4(\SI_VALUE_reg[34] [2]),
        .I5(\SI_VALUE[106]_i_3_n_0 ),
        .O(SI_VALUE0[48]));
  LUT5 #(
    .INIT(32'hF3BEFFBE)) 
    \SI_VALUE[106]_i_2 
       (.I0(\SI_VALUE[2]_i_2_n_0 ),
        .I1(\SI_VALUE_reg[209]_0 ),
        .I2(\SI_VALUE_reg[209] ),
        .I3(\SI_VALUE_reg[34] [2]),
        .I4(S_RESULT_S_C[0]),
        .O(\SI_VALUE[106]_i_2_n_0 ));
  LUT5 #(
    .INIT(32'hAFEBA028)) 
    \SI_VALUE[106]_i_3 
       (.I0(\SI_VALUE[142]_i_5_n_0 ),
        .I1(\SI_VALUE_reg[209]_0 ),
        .I2(\SI_VALUE_reg[34] [2]),
        .I3(\SI_VALUE_reg[209] ),
        .I4(\SI_VALUE[142]_i_6_n_0 ),
        .O(\SI_VALUE[106]_i_3_n_0 ));
  LUT6 #(
    .INIT(64'h0101100001011333)) 
    \SI_VALUE[107]_i_1 
       (.I0(\SI_VALUE[211]_i_2_n_0 ),
        .I1(\SI_VALUE_reg[34] [3]),
        .I2(\SI_VALUE_reg[209]_0 ),
        .I3(\SI_VALUE_reg[209] ),
        .I4(\SI_VALUE_reg[34] [2]),
        .I5(\SI_VALUE[107]_i_2_n_0 ),
        .O(SI_VALUE0[49]));
  LUT5 #(
    .INIT(32'hAFEBA028)) 
    \SI_VALUE[107]_i_2 
       (.I0(\SI_VALUE[175]_i_4_n_0 ),
        .I1(\SI_VALUE_reg[209]_0 ),
        .I2(\SI_VALUE_reg[34] [2]),
        .I3(\SI_VALUE_reg[209] ),
        .I4(\SI_VALUE[175]_i_5_n_0 ),
        .O(\SI_VALUE[107]_i_2_n_0 ));
  LUT6 #(
    .INIT(64'h0101100001011333)) 
    \SI_VALUE[108]_i_1 
       (.I0(\SI_VALUE[212]_i_2_n_0 ),
        .I1(\SI_VALUE_reg[34] [3]),
        .I2(\SI_VALUE_reg[209]_0 ),
        .I3(\SI_VALUE_reg[209] ),
        .I4(\SI_VALUE_reg[34] [2]),
        .I5(\SI_VALUE[140]_i_2_n_0 ),
        .O(SI_VALUE0[50]));
  LUT6 #(
    .INIT(64'h0101100001011333)) 
    \SI_VALUE[109]_i_1 
       (.I0(\SI_VALUE[141]_i_2_n_0 ),
        .I1(\SI_VALUE_reg[34] [3]),
        .I2(\SI_VALUE_reg[209]_0 ),
        .I3(\SI_VALUE_reg[209] ),
        .I4(\SI_VALUE_reg[34] [2]),
        .I5(\SI_VALUE[141]_i_3_n_0 ),
        .O(SI_VALUE0[51]));
  LUT6 #(
    .INIT(64'h4000000040000003)) 
    \SI_VALUE[10]_i_1 
       (.I0(\SI_VALUE[106]_i_2_n_0 ),
        .I1(\SI_VALUE_reg[34] [3]),
        .I2(\SI_VALUE_reg[209]_0 ),
        .I3(\SI_VALUE_reg[209] ),
        .I4(\SI_VALUE_reg[34] [2]),
        .I5(\SI_VALUE[106]_i_3_n_0 ),
        .O(SI_VALUE0[10]));
  LUT6 #(
    .INIT(64'h0101100001011333)) 
    \SI_VALUE[110]_i_1 
       (.I0(\SI_VALUE[142]_i_2_n_0 ),
        .I1(\SI_VALUE_reg[34] [3]),
        .I2(\SI_VALUE_reg[209]_0 ),
        .I3(\SI_VALUE_reg[209] ),
        .I4(\SI_VALUE_reg[34] [2]),
        .I5(\SI_VALUE[142]_i_3_n_0 ),
        .O(SI_VALUE0[52]));
  LUT6 #(
    .INIT(64'h0101100001011333)) 
    \SI_VALUE[111]_i_1 
       (.I0(\SI_VALUE[175]_i_2_n_0 ),
        .I1(\SI_VALUE_reg[34] [3]),
        .I2(\SI_VALUE_reg[209]_0 ),
        .I3(\SI_VALUE_reg[209] ),
        .I4(\SI_VALUE_reg[34] [2]),
        .I5(\SI_VALUE[175]_i_3_n_0 ),
        .O(SI_VALUE0[53]));
  LUT6 #(
    .INIT(64'h0101100001011333)) 
    \SI_VALUE[112]_i_1 
       (.I0(\SI_VALUE[176]_i_2_n_0 ),
        .I1(\SI_VALUE_reg[34] [3]),
        .I2(\SI_VALUE_reg[209]_0 ),
        .I3(\SI_VALUE_reg[209] ),
        .I4(\SI_VALUE_reg[34] [2]),
        .I5(\SI_VALUE[176]_i_3_n_0 ),
        .O(SI_VALUE0[54]));
  LUT6 #(
    .INIT(64'h0101100001011333)) 
    \SI_VALUE[113]_i_1 
       (.I0(\SI_VALUE[177]_i_2_n_0 ),
        .I1(\SI_VALUE_reg[34] [3]),
        .I2(\SI_VALUE_reg[209]_0 ),
        .I3(\SI_VALUE_reg[209] ),
        .I4(\SI_VALUE_reg[34] [2]),
        .I5(\SI_VALUE[177]_i_3_n_0 ),
        .O(SI_VALUE0[55]));
  (* SOFT_HLUTNM = "soft_lutpair52" *) 
  LUT2 #(
    .INIT(4'h1)) 
    \SI_VALUE[114]_i_1 
       (.I0(\SI_VALUE_reg[34] [3]),
        .I1(\SI_VALUE[178]_i_2_n_0 ),
        .O(SI_VALUE0[56]));
  (* SOFT_HLUTNM = "soft_lutpair53" *) 
  LUT2 #(
    .INIT(4'h1)) 
    \SI_VALUE[115]_i_1 
       (.I0(\SI_VALUE_reg[34] [3]),
        .I1(\SI_VALUE[179]_i_2_n_0 ),
        .O(SI_VALUE0[57]));
  (* SOFT_HLUTNM = "soft_lutpair54" *) 
  LUT2 #(
    .INIT(4'h1)) 
    \SI_VALUE[116]_i_1 
       (.I0(\SI_VALUE_reg[34] [3]),
        .I1(\SI_VALUE[180]_i_2_n_0 ),
        .O(SI_VALUE0[58]));
  (* SOFT_HLUTNM = "soft_lutpair42" *) 
  LUT2 #(
    .INIT(4'h1)) 
    \SI_VALUE[117]_i_1 
       (.I0(\SI_VALUE_reg[34] [3]),
        .I1(\SI_VALUE[245]_i_2_n_0 ),
        .O(SI_VALUE0[59]));
  (* SOFT_HLUTNM = "soft_lutpair41" *) 
  LUT2 #(
    .INIT(4'h1)) 
    \SI_VALUE[118]_i_1 
       (.I0(\SI_VALUE_reg[34] [3]),
        .I1(\SI_VALUE[246]_i_2_n_0 ),
        .O(SI_VALUE0[60]));
  (* SOFT_HLUTNM = "soft_lutpair40" *) 
  LUT2 #(
    .INIT(4'h1)) 
    \SI_VALUE[119]_i_1 
       (.I0(\SI_VALUE_reg[34] [3]),
        .I1(\SI_VALUE[247]_i_2_n_0 ),
        .O(SI_VALUE0[61]));
  LUT6 #(
    .INIT(64'h4000000040000003)) 
    \SI_VALUE[11]_i_1 
       (.I0(\SI_VALUE[211]_i_2_n_0 ),
        .I1(\SI_VALUE_reg[34] [3]),
        .I2(\SI_VALUE_reg[209]_0 ),
        .I3(\SI_VALUE_reg[209] ),
        .I4(\SI_VALUE_reg[34] [2]),
        .I5(\SI_VALUE[107]_i_2_n_0 ),
        .O(SI_VALUE0[11]));
  (* SOFT_HLUTNM = "soft_lutpair44" *) 
  LUT2 #(
    .INIT(4'h1)) 
    \SI_VALUE[120]_i_1 
       (.I0(\SI_VALUE_reg[34] [3]),
        .I1(\SI_VALUE[248]_i_2_n_0 ),
        .O(SI_VALUE0[62]));
  (* SOFT_HLUTNM = "soft_lutpair45" *) 
  LUT2 #(
    .INIT(4'h1)) 
    \SI_VALUE[121]_i_1 
       (.I0(\SI_VALUE_reg[34] [3]),
        .I1(\SI_VALUE[249]_i_2_n_0 ),
        .O(SI_VALUE0[63]));
  (* SOFT_HLUTNM = "soft_lutpair46" *) 
  LUT2 #(
    .INIT(4'h1)) 
    \SI_VALUE[122]_i_1 
       (.I0(\SI_VALUE_reg[34] [3]),
        .I1(\SI_VALUE[250]_i_2_n_0 ),
        .O(SI_VALUE0[64]));
  (* SOFT_HLUTNM = "soft_lutpair47" *) 
  LUT2 #(
    .INIT(4'h1)) 
    \SI_VALUE[123]_i_1 
       (.I0(\SI_VALUE_reg[34] [3]),
        .I1(\SI_VALUE[251]_i_2_n_0 ),
        .O(SI_VALUE0[65]));
  (* SOFT_HLUTNM = "soft_lutpair48" *) 
  LUT2 #(
    .INIT(4'h1)) 
    \SI_VALUE[124]_i_1 
       (.I0(\SI_VALUE_reg[34] [3]),
        .I1(\SI_VALUE[252]_i_2_n_0 ),
        .O(SI_VALUE0[66]));
  (* SOFT_HLUTNM = "soft_lutpair49" *) 
  LUT2 #(
    .INIT(4'h1)) 
    \SI_VALUE[125]_i_1 
       (.I0(\SI_VALUE_reg[34] [3]),
        .I1(\SI_VALUE[253]_i_2_n_0 ),
        .O(SI_VALUE0[67]));
  (* SOFT_HLUTNM = "soft_lutpair50" *) 
  LUT2 #(
    .INIT(4'h1)) 
    \SI_VALUE[126]_i_1 
       (.I0(\SI_VALUE_reg[34] [3]),
        .I1(\SI_VALUE[254]_i_2_n_0 ),
        .O(SI_VALUE0[68]));
  (* SOFT_HLUTNM = "soft_lutpair51" *) 
  LUT2 #(
    .INIT(4'h1)) 
    \SI_VALUE[127]_i_1 
       (.I0(\SI_VALUE_reg[34] [3]),
        .I1(\SI_VALUE[255]_i_2_n_0 ),
        .O(SI_VALUE0[69]));
  (* SOFT_HLUTNM = "soft_lutpair39" *) 
  LUT2 #(
    .INIT(4'h1)) 
    \SI_VALUE[128]_i_1 
       (.I0(\SI_VALUE_reg[34] [3]),
        .I1(\SI_VALUE[256]_i_2_n_0 ),
        .O(SI_VALUE0[70]));
  (* SOFT_HLUTNM = "soft_lutpair38" *) 
  LUT2 #(
    .INIT(4'h1)) 
    \SI_VALUE[129]_i_1 
       (.I0(\SI_VALUE_reg[34] [3]),
        .I1(\SI_VALUE[257]_i_2_n_0 ),
        .O(SI_VALUE0[71]));
  LUT6 #(
    .INIT(64'h4000000040000003)) 
    \SI_VALUE[12]_i_1 
       (.I0(\SI_VALUE[212]_i_2_n_0 ),
        .I1(\SI_VALUE_reg[34] [3]),
        .I2(\SI_VALUE_reg[209]_0 ),
        .I3(\SI_VALUE_reg[209] ),
        .I4(\SI_VALUE_reg[34] [2]),
        .I5(\SI_VALUE[140]_i_2_n_0 ),
        .O(SI_VALUE0[12]));
  (* SOFT_HLUTNM = "soft_lutpair37" *) 
  LUT2 #(
    .INIT(4'h1)) 
    \SI_VALUE[130]_i_1 
       (.I0(\SI_VALUE[258]_i_2_n_0 ),
        .I1(\SI_VALUE_reg[34] [3]),
        .O(SI_VALUE0[72]));
  (* SOFT_HLUTNM = "soft_lutpair68" *) 
  LUT2 #(
    .INIT(4'h1)) 
    \SI_VALUE[131]_i_1 
       (.I0(\SI_VALUE[259]_i_2_n_0 ),
        .I1(\SI_VALUE_reg[34] [3]),
        .O(SI_VALUE0[73]));
  (* SOFT_HLUTNM = "soft_lutpair67" *) 
  LUT2 #(
    .INIT(4'h1)) 
    \SI_VALUE[132]_i_1 
       (.I0(\SI_VALUE[260]_i_2_n_0 ),
        .I1(\SI_VALUE_reg[34] [3]),
        .O(SI_VALUE0[74]));
  (* SOFT_HLUTNM = "soft_lutpair66" *) 
  LUT2 #(
    .INIT(4'h1)) 
    \SI_VALUE[133]_i_1 
       (.I0(\SI_VALUE[261]_i_2_n_0 ),
        .I1(\SI_VALUE_reg[34] [3]),
        .O(SI_VALUE0[75]));
  (* SOFT_HLUTNM = "soft_lutpair65" *) 
  LUT2 #(
    .INIT(4'h1)) 
    \SI_VALUE[134]_i_1 
       (.I0(\SI_VALUE[262]_i_2_n_0 ),
        .I1(\SI_VALUE_reg[34] [3]),
        .O(SI_VALUE0[76]));
  (* SOFT_HLUTNM = "soft_lutpair64" *) 
  LUT2 #(
    .INIT(4'h1)) 
    \SI_VALUE[135]_i_1 
       (.I0(\SI_VALUE[263]_i_2_n_0 ),
        .I1(\SI_VALUE_reg[34] [3]),
        .O(SI_VALUE0[77]));
  (* SOFT_HLUTNM = "soft_lutpair63" *) 
  LUT2 #(
    .INIT(4'h1)) 
    \SI_VALUE[136]_i_1 
       (.I0(\SI_VALUE[264]_i_2_n_0 ),
        .I1(\SI_VALUE_reg[34] [3]),
        .O(SI_VALUE0[78]));
  (* SOFT_HLUTNM = "soft_lutpair60" *) 
  LUT2 #(
    .INIT(4'h1)) 
    \SI_VALUE[137]_i_1 
       (.I0(\SI_VALUE[265]_i_2_n_0 ),
        .I1(\SI_VALUE_reg[34] [3]),
        .O(SI_VALUE0[79]));
  LUT6 #(
    .INIT(64'h000000005030503F)) 
    \SI_VALUE[138]_i_1 
       (.I0(\SI_VALUE[274]_i_3_n_0 ),
        .I1(\SI_VALUE[266]_i_2_n_0 ),
        .I2(\SI_VALUE_reg[273] ),
        .I3(\SI_VALUE_reg[273]_0 ),
        .I4(\SI_VALUE[274]_i_2_n_0 ),
        .I5(\SI_VALUE_reg[34] [3]),
        .O(SI_VALUE0[80]));
  LUT6 #(
    .INIT(64'h000000005030503F)) 
    \SI_VALUE[139]_i_2 
       (.I0(\SI_VALUE[275]_i_3_n_0 ),
        .I1(\SI_VALUE[267]_i_2_n_0 ),
        .I2(\SI_VALUE_reg[273] ),
        .I3(\SI_VALUE_reg[273]_0 ),
        .I4(\SI_VALUE[275]_i_2_n_0 ),
        .I5(\SI_VALUE_reg[34] [3]),
        .O(SI_VALUE0[81]));
  LUT6 #(
    .INIT(64'h4000000040000003)) 
    \SI_VALUE[13]_i_1 
       (.I0(\SI_VALUE[141]_i_2_n_0 ),
        .I1(\SI_VALUE_reg[34] [3]),
        .I2(\SI_VALUE_reg[209]_0 ),
        .I3(\SI_VALUE_reg[209] ),
        .I4(\SI_VALUE_reg[34] [2]),
        .I5(\SI_VALUE[141]_i_3_n_0 ),
        .O(SI_VALUE0[13]));
  LUT6 #(
    .INIT(64'h414110004D4DD333)) 
    \SI_VALUE[140]_i_1 
       (.I0(\SI_VALUE[212]_i_2_n_0 ),
        .I1(\SI_VALUE_reg[34] [3]),
        .I2(\SI_VALUE_reg[209]_0 ),
        .I3(\SI_VALUE_reg[209] ),
        .I4(\SI_VALUE_reg[34] [2]),
        .I5(\SI_VALUE[140]_i_2_n_0 ),
        .O(SI_VALUE0[44]));
  LUT5 #(
    .INIT(32'hAFEBA028)) 
    \SI_VALUE[140]_i_2 
       (.I0(\SI_VALUE[176]_i_4_n_0 ),
        .I1(\SI_VALUE_reg[209]_0 ),
        .I2(\SI_VALUE_reg[34] [2]),
        .I3(\SI_VALUE_reg[209] ),
        .I4(\SI_VALUE[176]_i_5_n_0 ),
        .O(\SI_VALUE[140]_i_2_n_0 ));
  LUT6 #(
    .INIT(64'h414110004D4DD333)) 
    \SI_VALUE[141]_i_1 
       (.I0(\SI_VALUE[141]_i_2_n_0 ),
        .I1(\SI_VALUE_reg[34] [3]),
        .I2(\SI_VALUE_reg[209]_0 ),
        .I3(\SI_VALUE_reg[209] ),
        .I4(\SI_VALUE_reg[34] [2]),
        .I5(\SI_VALUE[141]_i_3_n_0 ),
        .O(SI_VALUE0[45]));
  LUT5 #(
    .INIT(32'hAFEBA028)) 
    \SI_VALUE[141]_i_2 
       (.I0(\SI_VALUE[141]_i_4_n_0 ),
        .I1(\SI_VALUE_reg[209]_0 ),
        .I2(\SI_VALUE_reg[34] [2]),
        .I3(\SI_VALUE_reg[209] ),
        .I4(\SI_VALUE[177]_i_4_n_0 ),
        .O(\SI_VALUE[141]_i_2_n_0 ));
  LUT5 #(
    .INIT(32'hAFEBA028)) 
    \SI_VALUE[141]_i_3 
       (.I0(\SI_VALUE[177]_i_5_n_0 ),
        .I1(\SI_VALUE_reg[209]_0 ),
        .I2(\SI_VALUE_reg[34] [2]),
        .I3(\SI_VALUE_reg[209] ),
        .I4(\SI_VALUE[177]_i_6_n_0 ),
        .O(\SI_VALUE[141]_i_3_n_0 ));
  LUT6 #(
    .INIT(64'hC0FFFF55FFFFFF55)) 
    \SI_VALUE[141]_i_4 
       (.I0(S_RESULT_S_C[1]),
        .I1(\SI_VALUE_reg[34] [2]),
        .I2(\SI_VALUE_reg[34] [3]),
        .I3(\SI_VALUE_reg[209]_0 ),
        .I4(\SI_VALUE_reg[209] ),
        .I5(S_RESULT_S_C[0]),
        .O(\SI_VALUE[141]_i_4_n_0 ));
  LUT6 #(
    .INIT(64'h414110004D4DD333)) 
    \SI_VALUE[142]_i_1 
       (.I0(\SI_VALUE[142]_i_2_n_0 ),
        .I1(\SI_VALUE_reg[34] [3]),
        .I2(\SI_VALUE_reg[209]_0 ),
        .I3(\SI_VALUE_reg[209] ),
        .I4(\SI_VALUE_reg[34] [2]),
        .I5(\SI_VALUE[142]_i_3_n_0 ),
        .O(SI_VALUE0[46]));
  LUT5 #(
    .INIT(32'hAFEBA028)) 
    \SI_VALUE[142]_i_2 
       (.I0(\SI_VALUE[142]_i_4_n_0 ),
        .I1(\SI_VALUE_reg[209]_0 ),
        .I2(\SI_VALUE_reg[34] [2]),
        .I3(\SI_VALUE_reg[209] ),
        .I4(\SI_VALUE[142]_i_5_n_0 ),
        .O(\SI_VALUE[142]_i_2_n_0 ));
  LUT5 #(
    .INIT(32'hAFEBA028)) 
    \SI_VALUE[142]_i_3 
       (.I0(\SI_VALUE[142]_i_6_n_0 ),
        .I1(\SI_VALUE_reg[209]_0 ),
        .I2(\SI_VALUE_reg[34] [2]),
        .I3(\SI_VALUE_reg[209] ),
        .I4(\SI_VALUE[266]_i_3_n_0 ),
        .O(\SI_VALUE[142]_i_3_n_0 ));
  LUT6 #(
    .INIT(64'hFFFF1CDCFFFF1FDF)) 
    \SI_VALUE[142]_i_4 
       (.I0(S_RESULT_S_C[0]),
        .I1(\SI_VALUE_reg[209] ),
        .I2(\SI_VALUE_reg[209]_0 ),
        .I3(S_RESULT_S_C[1]),
        .I4(\SI_VALUE_reg[279] ),
        .I5(S_RESULT_S_C[2]),
        .O(\SI_VALUE[142]_i_4_n_0 ));
  LUT6 #(
    .INIT(64'hFFCFDDFF00CFDD00)) 
    \SI_VALUE[142]_i_5 
       (.I0(S_RESULT_S_C[3]),
        .I1(\SI_VALUE_reg[279] ),
        .I2(S_RESULT_S_C[4]),
        .I3(\SI_VALUE_reg[209] ),
        .I4(\SI_VALUE_reg[209]_0 ),
        .I5(\SI_VALUE[142]_i_7_n_0 ),
        .O(\SI_VALUE[142]_i_5_n_0 ));
  LUT6 #(
    .INIT(64'hFFCFDDFF00CFDD00)) 
    \SI_VALUE[142]_i_6 
       (.I0(S_RESULT_S_C[7]),
        .I1(\SI_VALUE_reg[279] ),
        .I2(S_RESULT_S_C[8]),
        .I3(\SI_VALUE_reg[209] ),
        .I4(\SI_VALUE_reg[209]_0 ),
        .I5(\SI_VALUE[142]_i_8_n_0 ),
        .O(\SI_VALUE[142]_i_6_n_0 ));
  LUT6 #(
    .INIT(64'hC4444444F7777777)) 
    \SI_VALUE[142]_i_7 
       (.I0(S_RESULT_S_C[5]),
        .I1(\SI_VALUE_reg[209] ),
        .I2(\SI_VALUE_reg[209]_0 ),
        .I3(\SI_VALUE_reg[34] [3]),
        .I4(\SI_VALUE_reg[34] [2]),
        .I5(S_RESULT_S_C[6]),
        .O(\SI_VALUE[142]_i_7_n_0 ));
  LUT6 #(
    .INIT(64'hC4444444F7777777)) 
    \SI_VALUE[142]_i_8 
       (.I0(S_RESULT_S_C[9]),
        .I1(\SI_VALUE_reg[209] ),
        .I2(\SI_VALUE_reg[209]_0 ),
        .I3(\SI_VALUE_reg[34] [3]),
        .I4(\SI_VALUE_reg[34] [2]),
        .I5(S_RESULT_S_C[10]),
        .O(\SI_VALUE[142]_i_8_n_0 ));
  LUT6 #(
    .INIT(64'h4000000040000003)) 
    \SI_VALUE[14]_i_1 
       (.I0(\SI_VALUE[142]_i_2_n_0 ),
        .I1(\SI_VALUE_reg[34] [3]),
        .I2(\SI_VALUE_reg[209]_0 ),
        .I3(\SI_VALUE_reg[209] ),
        .I4(\SI_VALUE_reg[34] [2]),
        .I5(\SI_VALUE[142]_i_3_n_0 ),
        .O(SI_VALUE0[14]));
  LUT6 #(
    .INIT(64'h4000000040000003)) 
    \SI_VALUE[15]_i_1 
       (.I0(\SI_VALUE[175]_i_2_n_0 ),
        .I1(\SI_VALUE_reg[34] [3]),
        .I2(\SI_VALUE_reg[209]_0 ),
        .I3(\SI_VALUE_reg[209] ),
        .I4(\SI_VALUE_reg[34] [2]),
        .I5(\SI_VALUE[175]_i_3_n_0 ),
        .O(SI_VALUE0[15]));
  LUT6 #(
    .INIT(64'h4000000040000003)) 
    \SI_VALUE[16]_i_1 
       (.I0(\SI_VALUE[176]_i_2_n_0 ),
        .I1(\SI_VALUE_reg[34] [3]),
        .I2(\SI_VALUE_reg[209]_0 ),
        .I3(\SI_VALUE_reg[209] ),
        .I4(\SI_VALUE_reg[34] [2]),
        .I5(\SI_VALUE[176]_i_3_n_0 ),
        .O(SI_VALUE0[16]));
  LUT6 #(
    .INIT(64'h414110004D4DD333)) 
    \SI_VALUE[175]_i_1 
       (.I0(\SI_VALUE[175]_i_2_n_0 ),
        .I1(\SI_VALUE_reg[34] [3]),
        .I2(\SI_VALUE_reg[209]_0 ),
        .I3(\SI_VALUE_reg[209] ),
        .I4(\SI_VALUE_reg[34] [2]),
        .I5(\SI_VALUE[175]_i_3_n_0 ),
        .O(SI_VALUE0[82]));
  (* SOFT_HLUTNM = "soft_lutpair55" *) 
  LUT5 #(
    .INIT(32'hAFEBA028)) 
    \SI_VALUE[175]_i_2 
       (.I0(\SI_VALUE[211]_i_3_n_0 ),
        .I1(\SI_VALUE_reg[209]_0 ),
        .I2(\SI_VALUE_reg[34] [2]),
        .I3(\SI_VALUE_reg[209] ),
        .I4(\SI_VALUE[175]_i_4_n_0 ),
        .O(\SI_VALUE[175]_i_2_n_0 ));
  LUT5 #(
    .INIT(32'hAFEBA028)) 
    \SI_VALUE[175]_i_3 
       (.I0(\SI_VALUE[175]_i_5_n_0 ),
        .I1(\SI_VALUE_reg[209]_0 ),
        .I2(\SI_VALUE_reg[34] [2]),
        .I3(\SI_VALUE_reg[209] ),
        .I4(\SI_VALUE[267]_i_3_n_0 ),
        .O(\SI_VALUE[175]_i_3_n_0 ));
  LUT6 #(
    .INIT(64'hFFCFDDFF00CFDD00)) 
    \SI_VALUE[175]_i_4 
       (.I0(S_RESULT_S_C[4]),
        .I1(\SI_VALUE_reg[279] ),
        .I2(S_RESULT_S_C[5]),
        .I3(\SI_VALUE_reg[209] ),
        .I4(\SI_VALUE_reg[209]_0 ),
        .I5(\SI_VALUE[175]_i_6_n_0 ),
        .O(\SI_VALUE[175]_i_4_n_0 ));
  LUT6 #(
    .INIT(64'hFFCFDDFF00CFDD00)) 
    \SI_VALUE[175]_i_5 
       (.I0(S_RESULT_S_C[8]),
        .I1(\SI_VALUE_reg[279] ),
        .I2(S_RESULT_S_C[9]),
        .I3(\SI_VALUE_reg[209] ),
        .I4(\SI_VALUE_reg[209]_0 ),
        .I5(\SI_VALUE[175]_i_7_n_0 ),
        .O(\SI_VALUE[175]_i_5_n_0 ));
  LUT6 #(
    .INIT(64'hC4444444F7777777)) 
    \SI_VALUE[175]_i_6 
       (.I0(S_RESULT_S_C[6]),
        .I1(\SI_VALUE_reg[209] ),
        .I2(\SI_VALUE_reg[209]_0 ),
        .I3(\SI_VALUE_reg[34] [3]),
        .I4(\SI_VALUE_reg[34] [2]),
        .I5(S_RESULT_S_C[7]),
        .O(\SI_VALUE[175]_i_6_n_0 ));
  LUT6 #(
    .INIT(64'hC4444444F7777777)) 
    \SI_VALUE[175]_i_7 
       (.I0(S_RESULT_S_C[10]),
        .I1(\SI_VALUE_reg[209] ),
        .I2(\SI_VALUE_reg[209]_0 ),
        .I3(\SI_VALUE_reg[34] [3]),
        .I4(\SI_VALUE_reg[34] [2]),
        .I5(S_RESULT_S_C[11]),
        .O(\SI_VALUE[175]_i_7_n_0 ));
  LUT6 #(
    .INIT(64'h414110004D4DD333)) 
    \SI_VALUE[176]_i_1 
       (.I0(\SI_VALUE[176]_i_2_n_0 ),
        .I1(\SI_VALUE_reg[34] [3]),
        .I2(\SI_VALUE_reg[209]_0 ),
        .I3(\SI_VALUE_reg[209] ),
        .I4(\SI_VALUE_reg[34] [2]),
        .I5(\SI_VALUE[176]_i_3_n_0 ),
        .O(SI_VALUE0[83]));
  LUT5 #(
    .INIT(32'hAFEBA028)) 
    \SI_VALUE[176]_i_2 
       (.I0(\SI_VALUE[212]_i_3_n_0 ),
        .I1(\SI_VALUE_reg[209]_0 ),
        .I2(\SI_VALUE_reg[34] [2]),
        .I3(\SI_VALUE_reg[209] ),
        .I4(\SI_VALUE[176]_i_4_n_0 ),
        .O(\SI_VALUE[176]_i_2_n_0 ));
  LUT5 #(
    .INIT(32'hAFEBA028)) 
    \SI_VALUE[176]_i_3 
       (.I0(\SI_VALUE[176]_i_5_n_0 ),
        .I1(\SI_VALUE_reg[209]_0 ),
        .I2(\SI_VALUE_reg[34] [2]),
        .I3(\SI_VALUE_reg[209] ),
        .I4(\SI_VALUE[268]_i_4_n_0 ),
        .O(\SI_VALUE[176]_i_3_n_0 ));
  LUT6 #(
    .INIT(64'hFFCFDDFF00CFDD00)) 
    \SI_VALUE[176]_i_4 
       (.I0(S_RESULT_S_C[5]),
        .I1(\SI_VALUE_reg[279] ),
        .I2(S_RESULT_S_C[6]),
        .I3(\SI_VALUE_reg[209] ),
        .I4(\SI_VALUE_reg[209]_0 ),
        .I5(\SI_VALUE[176]_i_6_n_0 ),
        .O(\SI_VALUE[176]_i_4_n_0 ));
  LUT6 #(
    .INIT(64'hFFCFDDFF00CFDD00)) 
    \SI_VALUE[176]_i_5 
       (.I0(S_RESULT_S_C[9]),
        .I1(\SI_VALUE_reg[279] ),
        .I2(S_RESULT_S_C[10]),
        .I3(\SI_VALUE_reg[209] ),
        .I4(\SI_VALUE_reg[209]_0 ),
        .I5(\SI_VALUE[176]_i_7_n_0 ),
        .O(\SI_VALUE[176]_i_5_n_0 ));
  LUT6 #(
    .INIT(64'hC4444444F7777777)) 
    \SI_VALUE[176]_i_6 
       (.I0(S_RESULT_S_C[7]),
        .I1(\SI_VALUE_reg[209] ),
        .I2(\SI_VALUE_reg[209]_0 ),
        .I3(\SI_VALUE_reg[34] [3]),
        .I4(\SI_VALUE_reg[34] [2]),
        .I5(S_RESULT_S_C[8]),
        .O(\SI_VALUE[176]_i_6_n_0 ));
  LUT6 #(
    .INIT(64'hC4444444F7777777)) 
    \SI_VALUE[176]_i_7 
       (.I0(S_RESULT_S_C[11]),
        .I1(\SI_VALUE_reg[209] ),
        .I2(\SI_VALUE_reg[209]_0 ),
        .I3(\SI_VALUE_reg[34] [3]),
        .I4(\SI_VALUE_reg[34] [2]),
        .I5(S_RESULT_S_C[12]),
        .O(\SI_VALUE[176]_i_7_n_0 ));
  LUT6 #(
    .INIT(64'h414110004D4DD333)) 
    \SI_VALUE[177]_i_1 
       (.I0(\SI_VALUE[177]_i_2_n_0 ),
        .I1(\SI_VALUE_reg[34] [3]),
        .I2(\SI_VALUE_reg[209]_0 ),
        .I3(\SI_VALUE_reg[209] ),
        .I4(\SI_VALUE_reg[34] [2]),
        .I5(\SI_VALUE[177]_i_3_n_0 ),
        .O(SI_VALUE0[84]));
  LUT5 #(
    .INIT(32'hAFEBA028)) 
    \SI_VALUE[177]_i_2 
       (.I0(\SI_VALUE[177]_i_4_n_0 ),
        .I1(\SI_VALUE_reg[209]_0 ),
        .I2(\SI_VALUE_reg[34] [2]),
        .I3(\SI_VALUE_reg[209] ),
        .I4(\SI_VALUE[177]_i_5_n_0 ),
        .O(\SI_VALUE[177]_i_2_n_0 ));
  LUT5 #(
    .INIT(32'hAFEBA028)) 
    \SI_VALUE[177]_i_3 
       (.I0(\SI_VALUE[177]_i_6_n_0 ),
        .I1(\SI_VALUE_reg[209]_0 ),
        .I2(\SI_VALUE_reg[34] [2]),
        .I3(\SI_VALUE_reg[209] ),
        .I4(\SI_VALUE[269]_i_4_n_0 ),
        .O(\SI_VALUE[177]_i_3_n_0 ));
  LUT6 #(
    .INIT(64'hFFCFDDFF00CFDD00)) 
    \SI_VALUE[177]_i_4 
       (.I0(S_RESULT_S_C[2]),
        .I1(\SI_VALUE_reg[279] ),
        .I2(S_RESULT_S_C[3]),
        .I3(\SI_VALUE_reg[209] ),
        .I4(\SI_VALUE_reg[209]_0 ),
        .I5(\SI_VALUE[177]_i_7_n_0 ),
        .O(\SI_VALUE[177]_i_4_n_0 ));
  LUT6 #(
    .INIT(64'hFFCFDDFF00CFDD00)) 
    \SI_VALUE[177]_i_5 
       (.I0(S_RESULT_S_C[6]),
        .I1(\SI_VALUE_reg[279] ),
        .I2(S_RESULT_S_C[7]),
        .I3(\SI_VALUE_reg[209] ),
        .I4(\SI_VALUE_reg[209]_0 ),
        .I5(\SI_VALUE[177]_i_8_n_0 ),
        .O(\SI_VALUE[177]_i_5_n_0 ));
  LUT6 #(
    .INIT(64'hFFCFDDFF00CFDD00)) 
    \SI_VALUE[177]_i_6 
       (.I0(S_RESULT_S_C[10]),
        .I1(\SI_VALUE_reg[279] ),
        .I2(S_RESULT_S_C[11]),
        .I3(\SI_VALUE_reg[209] ),
        .I4(\SI_VALUE_reg[209]_0 ),
        .I5(\SI_VALUE[177]_i_9_n_0 ),
        .O(\SI_VALUE[177]_i_6_n_0 ));
  LUT6 #(
    .INIT(64'hC4444444F7777777)) 
    \SI_VALUE[177]_i_7 
       (.I0(S_RESULT_S_C[4]),
        .I1(\SI_VALUE_reg[209] ),
        .I2(\SI_VALUE_reg[209]_0 ),
        .I3(\SI_VALUE_reg[34] [3]),
        .I4(\SI_VALUE_reg[34] [2]),
        .I5(S_RESULT_S_C[5]),
        .O(\SI_VALUE[177]_i_7_n_0 ));
  LUT6 #(
    .INIT(64'hC4444444F7777777)) 
    \SI_VALUE[177]_i_8 
       (.I0(S_RESULT_S_C[8]),
        .I1(\SI_VALUE_reg[209] ),
        .I2(\SI_VALUE_reg[209]_0 ),
        .I3(\SI_VALUE_reg[34] [3]),
        .I4(\SI_VALUE_reg[34] [2]),
        .I5(S_RESULT_S_C[9]),
        .O(\SI_VALUE[177]_i_8_n_0 ));
  LUT6 #(
    .INIT(64'hC4444444F7777777)) 
    \SI_VALUE[177]_i_9 
       (.I0(S_RESULT_S_C[12]),
        .I1(\SI_VALUE_reg[209] ),
        .I2(\SI_VALUE_reg[209]_0 ),
        .I3(\SI_VALUE_reg[34] [3]),
        .I4(\SI_VALUE_reg[34] [2]),
        .I5(S_RESULT_S_C[13]),
        .O(\SI_VALUE[177]_i_9_n_0 ));
  LUT1 #(
    .INIT(2'h1)) 
    \SI_VALUE[178]_i_1 
       (.I0(\SI_VALUE[178]_i_2_n_0 ),
        .O(SI_VALUE0[85]));
  LUT5 #(
    .INIT(32'h0000FFB8)) 
    \SI_VALUE[178]_i_2 
       (.I0(\SI_VALUE[266]_i_2_n_0 ),
        .I1(\SI_VALUE_reg[273]_0 ),
        .I2(\SI_VALUE[106]_i_3_n_0 ),
        .I3(\SI_VALUE_reg[273] ),
        .I4(SI_VALUE0[91]),
        .O(\SI_VALUE[178]_i_2_n_0 ));
  LUT1 #(
    .INIT(2'h1)) 
    \SI_VALUE[179]_i_1 
       (.I0(\SI_VALUE[179]_i_2_n_0 ),
        .O(SI_VALUE0[86]));
  LUT6 #(
    .INIT(64'hFFB80000FFB8FFB8)) 
    \SI_VALUE[179]_i_2 
       (.I0(\SI_VALUE[267]_i_2_n_0 ),
        .I1(\SI_VALUE_reg[273]_0 ),
        .I2(\SI_VALUE[107]_i_2_n_0 ),
        .I3(\SI_VALUE_reg[273] ),
        .I4(\SI_VALUE[211]_i_2_n_0 ),
        .I5(\SI_VALUE_reg[115] ),
        .O(\SI_VALUE[179]_i_2_n_0 ));
  LUT6 #(
    .INIT(64'h4000000040000003)) 
    \SI_VALUE[17]_i_1 
       (.I0(\SI_VALUE[177]_i_2_n_0 ),
        .I1(\SI_VALUE_reg[34] [3]),
        .I2(\SI_VALUE_reg[209]_0 ),
        .I3(\SI_VALUE_reg[209] ),
        .I4(\SI_VALUE_reg[34] [2]),
        .I5(\SI_VALUE[177]_i_3_n_0 ),
        .O(SI_VALUE0[17]));
  LUT1 #(
    .INIT(2'h1)) 
    \SI_VALUE[180]_i_1 
       (.I0(\SI_VALUE[180]_i_2_n_0 ),
        .O(SI_VALUE0[87]));
  LUT6 #(
    .INIT(64'hFFB80000FFB8FFB8)) 
    \SI_VALUE[180]_i_2 
       (.I0(\SI_VALUE[268]_i_2_n_0 ),
        .I1(\SI_VALUE_reg[273]_0 ),
        .I2(\SI_VALUE[140]_i_2_n_0 ),
        .I3(\SI_VALUE_reg[273] ),
        .I4(\SI_VALUE[212]_i_2_n_0 ),
        .I5(\SI_VALUE_reg[115] ),
        .O(\SI_VALUE[180]_i_2_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair52" *) 
  LUT5 #(
    .INIT(32'h40000101)) 
    \SI_VALUE[18]_i_1 
       (.I0(\SI_VALUE[178]_i_2_n_0 ),
        .I1(\SI_VALUE_reg[34] [1]),
        .I2(\SI_VALUE_reg[34] [2]),
        .I3(\SI_VALUE_reg[34] [3]),
        .I4(\SI_VALUE_reg[34] [0]),
        .O(SI_VALUE0[18]));
  (* SOFT_HLUTNM = "soft_lutpair53" *) 
  LUT5 #(
    .INIT(32'h40000101)) 
    \SI_VALUE[19]_i_1 
       (.I0(\SI_VALUE[179]_i_2_n_0 ),
        .I1(\SI_VALUE_reg[34] [1]),
        .I2(\SI_VALUE_reg[34] [2]),
        .I3(\SI_VALUE_reg[34] [3]),
        .I4(\SI_VALUE_reg[34] [0]),
        .O(SI_VALUE0[19]));
  LUT5 #(
    .INIT(32'h00010000)) 
    \SI_VALUE[1]_i_1 
       (.I0(\SI_VALUE_reg[34] [2]),
        .I1(\SI_VALUE_reg[34] [0]),
        .I2(\SI_VALUE_reg[34] [1]),
        .I3(\SI_VALUE_reg[34] [3]),
        .I4(S_RESULT_S_C[1]),
        .O(SI_VALUE0[1]));
  (* SOFT_HLUTNM = "soft_lutpair57" *) 
  LUT1 #(
    .INIT(2'h1)) 
    \SI_VALUE[207]_i_1 
       (.I0(\SI_VALUE[207]_i_2_n_0 ),
        .O(\S_RESULT_COUNTER_reg[0]_rep ));
  LUT6 #(
    .INIT(64'hC4444444F7777777)) 
    \SI_VALUE[207]_i_2 
       (.I0(S_RESULT_S_C[32]),
        .I1(\SI_VALUE_reg[209] ),
        .I2(\SI_VALUE_reg[209]_0 ),
        .I3(\SI_VALUE_reg[34] [3]),
        .I4(\SI_VALUE_reg[34] [2]),
        .I5(P),
        .O(\SI_VALUE[207]_i_2_n_0 ));
  LUT5 #(
    .INIT(32'h02000000)) 
    \SI_VALUE[209]_i_2 
       (.I0(S_RESULT_S_C[34]),
        .I1(\SI_VALUE_reg[34] [3]),
        .I2(\SI_VALUE_reg[209]_0 ),
        .I3(\SI_VALUE_reg[209] ),
        .I4(\SI_VALUE_reg[34] [2]),
        .O(SI_VALUE0[90]));
  (* SOFT_HLUTNM = "soft_lutpair54" *) 
  LUT5 #(
    .INIT(32'h40000101)) 
    \SI_VALUE[20]_i_1 
       (.I0(\SI_VALUE[180]_i_2_n_0 ),
        .I1(\SI_VALUE_reg[34] [1]),
        .I2(\SI_VALUE_reg[34] [2]),
        .I3(\SI_VALUE_reg[34] [3]),
        .I4(\SI_VALUE_reg[34] [0]),
        .O(SI_VALUE0[20]));
  LUT5 #(
    .INIT(32'h00080000)) 
    \SI_VALUE[210]_i_1 
       (.I0(S_RESULT_S_C[0]),
        .I1(\SI_VALUE_reg[34] [2]),
        .I2(\SI_VALUE_reg[34] [3]),
        .I3(\SI_VALUE_reg[209] ),
        .I4(\SI_VALUE_reg[209]_0 ),
        .O(SI_VALUE0[91]));
  LUT1 #(
    .INIT(2'h1)) 
    \SI_VALUE[211]_i_1 
       (.I0(\SI_VALUE[211]_i_2_n_0 ),
        .O(SI_VALUE0[92]));
  (* SOFT_HLUTNM = "soft_lutpair55" *) 
  LUT4 #(
    .INIT(16'hFF9C)) 
    \SI_VALUE[211]_i_2 
       (.I0(\SI_VALUE_reg[209] ),
        .I1(\SI_VALUE_reg[34] [2]),
        .I2(\SI_VALUE_reg[209]_0 ),
        .I3(\SI_VALUE[211]_i_3_n_0 ),
        .O(\SI_VALUE[211]_i_2_n_0 ));
  LUT6 #(
    .INIT(64'hFFCFDDFF00CFDD00)) 
    \SI_VALUE[211]_i_3 
       (.I0(S_RESULT_S_C[0]),
        .I1(\SI_VALUE_reg[279] ),
        .I2(S_RESULT_S_C[1]),
        .I3(\SI_VALUE_reg[209] ),
        .I4(\SI_VALUE_reg[209]_0 ),
        .I5(\SI_VALUE[211]_i_4_n_0 ),
        .O(\SI_VALUE[211]_i_3_n_0 ));
  LUT6 #(
    .INIT(64'hC4444444F7777777)) 
    \SI_VALUE[211]_i_4 
       (.I0(S_RESULT_S_C[2]),
        .I1(\SI_VALUE_reg[209] ),
        .I2(\SI_VALUE_reg[209]_0 ),
        .I3(\SI_VALUE_reg[34] [3]),
        .I4(\SI_VALUE_reg[34] [2]),
        .I5(S_RESULT_S_C[3]),
        .O(\SI_VALUE[211]_i_4_n_0 ));
  LUT1 #(
    .INIT(2'h1)) 
    \SI_VALUE[212]_i_1 
       (.I0(\SI_VALUE[212]_i_2_n_0 ),
        .O(SI_VALUE0[36]));
  (* SOFT_HLUTNM = "soft_lutpair58" *) 
  LUT5 #(
    .INIT(32'hFFDFF01C)) 
    \SI_VALUE[212]_i_2 
       (.I0(S_RESULT_S_C[0]),
        .I1(\SI_VALUE_reg[209]_0 ),
        .I2(\SI_VALUE_reg[34] [2]),
        .I3(\SI_VALUE_reg[209] ),
        .I4(\SI_VALUE[212]_i_3_n_0 ),
        .O(\SI_VALUE[212]_i_2_n_0 ));
  LUT6 #(
    .INIT(64'hFFCFDDFF00CFDD00)) 
    \SI_VALUE[212]_i_3 
       (.I0(S_RESULT_S_C[1]),
        .I1(\SI_VALUE_reg[279] ),
        .I2(S_RESULT_S_C[2]),
        .I3(\SI_VALUE_reg[209] ),
        .I4(\SI_VALUE_reg[209]_0 ),
        .I5(\SI_VALUE[212]_i_4_n_0 ),
        .O(\SI_VALUE[212]_i_3_n_0 ));
  LUT6 #(
    .INIT(64'hC4444444F7777777)) 
    \SI_VALUE[212]_i_4 
       (.I0(S_RESULT_S_C[3]),
        .I1(\SI_VALUE_reg[209] ),
        .I2(\SI_VALUE_reg[209]_0 ),
        .I3(\SI_VALUE_reg[34] [3]),
        .I4(\SI_VALUE_reg[34] [2]),
        .I5(S_RESULT_S_C[4]),
        .O(\SI_VALUE[212]_i_4_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair42" *) 
  LUT5 #(
    .INIT(32'h40000101)) 
    \SI_VALUE[21]_i_1 
       (.I0(\SI_VALUE[245]_i_2_n_0 ),
        .I1(\SI_VALUE_reg[34] [1]),
        .I2(\SI_VALUE_reg[34] [2]),
        .I3(\SI_VALUE_reg[34] [3]),
        .I4(\SI_VALUE_reg[34] [0]),
        .O(SI_VALUE0[21]));
  (* SOFT_HLUTNM = "soft_lutpair62" *) 
  LUT1 #(
    .INIT(2'h1)) 
    \SI_VALUE[223]_i_1 
       (.I0(\SI_VALUE[255]_i_2_n_0 ),
        .O(SI_VALUE0[88]));
  (* SOFT_HLUTNM = "soft_lutpair61" *) 
  LUT1 #(
    .INIT(2'h1)) 
    \SI_VALUE[224]_i_1 
       (.I0(\SI_VALUE[256]_i_2_n_0 ),
        .O(SI_VALUE0[89]));
  (* SOFT_HLUTNM = "soft_lutpair41" *) 
  LUT5 #(
    .INIT(32'h40000101)) 
    \SI_VALUE[22]_i_1 
       (.I0(\SI_VALUE[246]_i_2_n_0 ),
        .I1(\SI_VALUE_reg[34] [1]),
        .I2(\SI_VALUE_reg[34] [2]),
        .I3(\SI_VALUE_reg[34] [3]),
        .I4(\SI_VALUE_reg[34] [0]),
        .O(SI_VALUE0[22]));
  (* SOFT_HLUTNM = "soft_lutpair40" *) 
  LUT5 #(
    .INIT(32'h40000101)) 
    \SI_VALUE[23]_i_1 
       (.I0(\SI_VALUE[247]_i_2_n_0 ),
        .I1(\SI_VALUE_reg[34] [1]),
        .I2(\SI_VALUE_reg[34] [2]),
        .I3(\SI_VALUE_reg[34] [3]),
        .I4(\SI_VALUE_reg[34] [0]),
        .O(SI_VALUE0[23]));
  LUT1 #(
    .INIT(2'h1)) 
    \SI_VALUE[245]_i_1 
       (.I0(\SI_VALUE[245]_i_2_n_0 ),
        .O(SI_VALUE0[93]));
  (* SOFT_HLUTNM = "soft_lutpair43" *) 
  LUT5 #(
    .INIT(32'hB8FFB8CC)) 
    \SI_VALUE[245]_i_2 
       (.I0(\SI_VALUE[141]_i_2_n_0 ),
        .I1(\SI_VALUE_reg[273] ),
        .I2(\SI_VALUE[269]_i_2_n_0 ),
        .I3(\SI_VALUE_reg[273]_0 ),
        .I4(\SI_VALUE[141]_i_3_n_0 ),
        .O(\SI_VALUE[245]_i_2_n_0 ));
  LUT1 #(
    .INIT(2'h1)) 
    \SI_VALUE[246]_i_1 
       (.I0(\SI_VALUE[246]_i_2_n_0 ),
        .O(SI_VALUE0[94]));
  LUT5 #(
    .INIT(32'hB8FFB8CC)) 
    \SI_VALUE[246]_i_2 
       (.I0(\SI_VALUE[142]_i_2_n_0 ),
        .I1(\SI_VALUE_reg[273] ),
        .I2(\SI_VALUE[270]_i_2_n_0 ),
        .I3(\SI_VALUE_reg[273]_0 ),
        .I4(\SI_VALUE[142]_i_3_n_0 ),
        .O(\SI_VALUE[246]_i_2_n_0 ));
  LUT1 #(
    .INIT(2'h1)) 
    \SI_VALUE[247]_i_1 
       (.I0(\SI_VALUE[247]_i_2_n_0 ),
        .O(SI_VALUE0[95]));
  LUT5 #(
    .INIT(32'hB8FFB8CC)) 
    \SI_VALUE[247]_i_2 
       (.I0(\SI_VALUE[175]_i_2_n_0 ),
        .I1(\SI_VALUE_reg[273] ),
        .I2(\SI_VALUE[271]_i_2_n_0 ),
        .I3(\SI_VALUE_reg[273]_0 ),
        .I4(\SI_VALUE[175]_i_3_n_0 ),
        .O(\SI_VALUE[247]_i_2_n_0 ));
  LUT1 #(
    .INIT(2'h1)) 
    \SI_VALUE[248]_i_1 
       (.I0(\SI_VALUE[248]_i_2_n_0 ),
        .O(SI_VALUE0[96]));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \SI_VALUE[248]_i_2 
       (.I0(\SI_VALUE[176]_i_2_n_0 ),
        .I1(\SI_VALUE[248]_i_3_n_0 ),
        .I2(\SI_VALUE_reg[273] ),
        .I3(\SI_VALUE[272]_i_3_n_0 ),
        .I4(\SI_VALUE_reg[273]_0 ),
        .I5(\SI_VALUE[176]_i_3_n_0 ),
        .O(\SI_VALUE[248]_i_2_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair58" *) 
  LUT4 #(
    .INIT(16'hFFFD)) 
    \SI_VALUE[248]_i_3 
       (.I0(S_RESULT_S_C[0]),
        .I1(\SI_VALUE_reg[209] ),
        .I2(\SI_VALUE_reg[209]_0 ),
        .I3(\SI_VALUE_reg[34] [2]),
        .O(\SI_VALUE[248]_i_3_n_0 ));
  LUT1 #(
    .INIT(2'h1)) 
    \SI_VALUE[249]_i_1 
       (.I0(\SI_VALUE[249]_i_2_n_0 ),
        .O(SI_VALUE0[97]));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \SI_VALUE[249]_i_2 
       (.I0(\SI_VALUE[177]_i_2_n_0 ),
        .I1(\SI_VALUE[105]_i_2_n_0 ),
        .I2(\SI_VALUE_reg[273] ),
        .I3(\SI_VALUE[273]_i_5_n_0 ),
        .I4(\SI_VALUE_reg[273]_0 ),
        .I5(\SI_VALUE[177]_i_3_n_0 ),
        .O(\SI_VALUE[249]_i_2_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair44" *) 
  LUT5 #(
    .INIT(32'h40000001)) 
    \SI_VALUE[24]_i_1 
       (.I0(\SI_VALUE[248]_i_2_n_0 ),
        .I1(\SI_VALUE_reg[34] [1]),
        .I2(\SI_VALUE_reg[34] [2]),
        .I3(\SI_VALUE_reg[34] [3]),
        .I4(\SI_VALUE_reg[34] [0]),
        .O(SI_VALUE0[24]));
  LUT1 #(
    .INIT(2'h1)) 
    \SI_VALUE[250]_i_1 
       (.I0(\SI_VALUE[250]_i_2_n_0 ),
        .O(SI_VALUE0[98]));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \SI_VALUE[250]_i_2 
       (.I0(\SI_VALUE[106]_i_3_n_0 ),
        .I1(\SI_VALUE[106]_i_2_n_0 ),
        .I2(\SI_VALUE_reg[273] ),
        .I3(\SI_VALUE[274]_i_3_n_0 ),
        .I4(\SI_VALUE_reg[273]_0 ),
        .I5(\SI_VALUE[266]_i_2_n_0 ),
        .O(\SI_VALUE[250]_i_2_n_0 ));
  LUT1 #(
    .INIT(2'h1)) 
    \SI_VALUE[251]_i_1 
       (.I0(\SI_VALUE[251]_i_2_n_0 ),
        .O(SI_VALUE0[99]));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \SI_VALUE[251]_i_2 
       (.I0(\SI_VALUE[107]_i_2_n_0 ),
        .I1(\SI_VALUE[211]_i_2_n_0 ),
        .I2(\SI_VALUE_reg[273] ),
        .I3(\SI_VALUE[275]_i_3_n_0 ),
        .I4(\SI_VALUE_reg[273]_0 ),
        .I5(\SI_VALUE[267]_i_2_n_0 ),
        .O(\SI_VALUE[251]_i_2_n_0 ));
  LUT1 #(
    .INIT(2'h1)) 
    \SI_VALUE[252]_i_1 
       (.I0(\SI_VALUE[252]_i_2_n_0 ),
        .O(SI_VALUE0[100]));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \SI_VALUE[252]_i_2 
       (.I0(\SI_VALUE[140]_i_2_n_0 ),
        .I1(\SI_VALUE[212]_i_2_n_0 ),
        .I2(\SI_VALUE_reg[273] ),
        .I3(\SI_VALUE[276]_i_3_n_0 ),
        .I4(\SI_VALUE_reg[273]_0 ),
        .I5(\SI_VALUE[268]_i_2_n_0 ),
        .O(\SI_VALUE[252]_i_2_n_0 ));
  LUT1 #(
    .INIT(2'h1)) 
    \SI_VALUE[253]_i_1 
       (.I0(\SI_VALUE[253]_i_2_n_0 ),
        .O(SI_VALUE0[101]));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \SI_VALUE[253]_i_2 
       (.I0(\SI_VALUE[141]_i_3_n_0 ),
        .I1(\SI_VALUE[141]_i_2_n_0 ),
        .I2(\SI_VALUE_reg[273] ),
        .I3(\SI_VALUE[277]_i_3_n_0 ),
        .I4(\SI_VALUE_reg[273]_0 ),
        .I5(\SI_VALUE[269]_i_2_n_0 ),
        .O(\SI_VALUE[253]_i_2_n_0 ));
  LUT1 #(
    .INIT(2'h1)) 
    \SI_VALUE[254]_i_1 
       (.I0(\SI_VALUE[254]_i_2_n_0 ),
        .O(SI_VALUE0[102]));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \SI_VALUE[254]_i_2 
       (.I0(\SI_VALUE[142]_i_3_n_0 ),
        .I1(\SI_VALUE[142]_i_2_n_0 ),
        .I2(\SI_VALUE_reg[273] ),
        .I3(\SI_VALUE[278]_i_3_n_0 ),
        .I4(\SI_VALUE_reg[273]_0 ),
        .I5(\SI_VALUE[270]_i_2_n_0 ),
        .O(\SI_VALUE[254]_i_2_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair62" *) 
  LUT2 #(
    .INIT(4'h7)) 
    \SI_VALUE[255]_i_1 
       (.I0(\SI_VALUE[271]_i_3_n_0 ),
        .I1(\SI_VALUE[255]_i_2_n_0 ),
        .O(SI_VALUE0[123]));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \SI_VALUE[255]_i_2 
       (.I0(\SI_VALUE[175]_i_3_n_0 ),
        .I1(\SI_VALUE[175]_i_2_n_0 ),
        .I2(\SI_VALUE_reg[273] ),
        .I3(\SI_VALUE[279]_i_5_n_0 ),
        .I4(\SI_VALUE_reg[273]_0 ),
        .I5(\SI_VALUE[271]_i_2_n_0 ),
        .O(\SI_VALUE[255]_i_2_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair61" *) 
  LUT2 #(
    .INIT(4'h7)) 
    \SI_VALUE[256]_i_1 
       (.I0(\SI_VALUE[272]_i_4_n_0 ),
        .I1(\SI_VALUE[256]_i_2_n_0 ),
        .O(SI_VALUE0[124]));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \SI_VALUE[256]_i_2 
       (.I0(\SI_VALUE[176]_i_3_n_0 ),
        .I1(\SI_VALUE[176]_i_2_n_0 ),
        .I2(\SI_VALUE_reg[273] ),
        .I3(\SI_VALUE[272]_i_2_n_0 ),
        .I4(\SI_VALUE_reg[273]_0 ),
        .I5(\SI_VALUE[272]_i_3_n_0 ),
        .O(\SI_VALUE[256]_i_2_n_0 ));
  LUT1 #(
    .INIT(2'h1)) 
    \SI_VALUE[257]_i_1 
       (.I0(\SI_VALUE[257]_i_2_n_0 ),
        .O(SI_VALUE0[103]));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \SI_VALUE[257]_i_2 
       (.I0(\SI_VALUE[177]_i_3_n_0 ),
        .I1(\SI_VALUE[177]_i_2_n_0 ),
        .I2(\SI_VALUE_reg[273] ),
        .I3(\SI_VALUE[273]_i_3_n_0 ),
        .I4(\SI_VALUE_reg[273]_0 ),
        .I5(\SI_VALUE[273]_i_5_n_0 ),
        .O(\SI_VALUE[257]_i_2_n_0 ));
  LUT1 #(
    .INIT(2'h1)) 
    \SI_VALUE[258]_i_1 
       (.I0(\SI_VALUE[258]_i_2_n_0 ),
        .O(SI_VALUE0[104]));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \SI_VALUE[258]_i_2 
       (.I0(\SI_VALUE[266]_i_2_n_0 ),
        .I1(\SI_VALUE[106]_i_3_n_0 ),
        .I2(\SI_VALUE_reg[273] ),
        .I3(\SI_VALUE[274]_i_2_n_0 ),
        .I4(\SI_VALUE_reg[273]_0 ),
        .I5(\SI_VALUE[274]_i_3_n_0 ),
        .O(\SI_VALUE[258]_i_2_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair68" *) 
  LUT1 #(
    .INIT(2'h1)) 
    \SI_VALUE[259]_i_1 
       (.I0(\SI_VALUE[259]_i_2_n_0 ),
        .O(SI_VALUE0[105]));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \SI_VALUE[259]_i_2 
       (.I0(\SI_VALUE[267]_i_2_n_0 ),
        .I1(\SI_VALUE[107]_i_2_n_0 ),
        .I2(\SI_VALUE_reg[273] ),
        .I3(\SI_VALUE[275]_i_2_n_0 ),
        .I4(\SI_VALUE_reg[273]_0 ),
        .I5(\SI_VALUE[275]_i_3_n_0 ),
        .O(\SI_VALUE[259]_i_2_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair45" *) 
  LUT5 #(
    .INIT(32'h40000001)) 
    \SI_VALUE[25]_i_1 
       (.I0(\SI_VALUE[249]_i_2_n_0 ),
        .I1(\SI_VALUE_reg[34] [1]),
        .I2(\SI_VALUE_reg[34] [2]),
        .I3(\SI_VALUE_reg[34] [3]),
        .I4(\SI_VALUE_reg[34] [0]),
        .O(SI_VALUE0[25]));
  (* SOFT_HLUTNM = "soft_lutpair67" *) 
  LUT1 #(
    .INIT(2'h1)) 
    \SI_VALUE[260]_i_1 
       (.I0(\SI_VALUE[260]_i_2_n_0 ),
        .O(SI_VALUE0[106]));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \SI_VALUE[260]_i_2 
       (.I0(\SI_VALUE[268]_i_2_n_0 ),
        .I1(\SI_VALUE[140]_i_2_n_0 ),
        .I2(\SI_VALUE_reg[273] ),
        .I3(\SI_VALUE[276]_i_2_n_0 ),
        .I4(\SI_VALUE_reg[273]_0 ),
        .I5(\SI_VALUE[276]_i_3_n_0 ),
        .O(\SI_VALUE[260]_i_2_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair66" *) 
  LUT1 #(
    .INIT(2'h1)) 
    \SI_VALUE[261]_i_1 
       (.I0(\SI_VALUE[261]_i_2_n_0 ),
        .O(SI_VALUE0[107]));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \SI_VALUE[261]_i_2 
       (.I0(\SI_VALUE[269]_i_2_n_0 ),
        .I1(\SI_VALUE[141]_i_3_n_0 ),
        .I2(\SI_VALUE_reg[273] ),
        .I3(\SI_VALUE[277]_i_2_n_0 ),
        .I4(\SI_VALUE_reg[273]_0 ),
        .I5(\SI_VALUE[277]_i_3_n_0 ),
        .O(\SI_VALUE[261]_i_2_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair65" *) 
  LUT1 #(
    .INIT(2'h1)) 
    \SI_VALUE[262]_i_1 
       (.I0(\SI_VALUE[262]_i_2_n_0 ),
        .O(SI_VALUE0[108]));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \SI_VALUE[262]_i_2 
       (.I0(\SI_VALUE[270]_i_2_n_0 ),
        .I1(\SI_VALUE[142]_i_3_n_0 ),
        .I2(\SI_VALUE_reg[273] ),
        .I3(\SI_VALUE[262]_i_3_n_0 ),
        .I4(\SI_VALUE_reg[273]_0 ),
        .I5(\SI_VALUE[278]_i_3_n_0 ),
        .O(\SI_VALUE[262]_i_2_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair56" *) 
  LUT4 #(
    .INIT(16'hBEAF)) 
    \SI_VALUE[262]_i_3 
       (.I0(\SI_VALUE[278]_i_2_n_0 ),
        .I1(\SI_VALUE_reg[209] ),
        .I2(\SI_VALUE_reg[34] [2]),
        .I3(\SI_VALUE_reg[209]_0 ),
        .O(\SI_VALUE[262]_i_3_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair64" *) 
  LUT1 #(
    .INIT(2'h1)) 
    \SI_VALUE[263]_i_1 
       (.I0(\SI_VALUE[263]_i_2_n_0 ),
        .O(SI_VALUE0[109]));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \SI_VALUE[263]_i_2 
       (.I0(\SI_VALUE[271]_i_2_n_0 ),
        .I1(\SI_VALUE[175]_i_3_n_0 ),
        .I2(\SI_VALUE_reg[273] ),
        .I3(\SI_VALUE[263]_i_3_n_0 ),
        .I4(\SI_VALUE_reg[273]_0 ),
        .I5(\SI_VALUE[279]_i_5_n_0 ),
        .O(\SI_VALUE[263]_i_2_n_0 ));
  LUT6 #(
    .INIT(64'hBBFFFFF0F0FFFFFF)) 
    \SI_VALUE[263]_i_3 
       (.I0(\SI_VALUE_reg[34] [3]),
        .I1(S_RESULT_S_C[34]),
        .I2(\SI_VALUE[207]_i_2_n_0 ),
        .I3(\SI_VALUE_reg[209] ),
        .I4(\SI_VALUE_reg[34] [2]),
        .I5(\SI_VALUE_reg[209]_0 ),
        .O(\SI_VALUE[263]_i_3_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair63" *) 
  LUT1 #(
    .INIT(2'h1)) 
    \SI_VALUE[264]_i_1 
       (.I0(\SI_VALUE[264]_i_2_n_0 ),
        .O(SI_VALUE0[110]));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \SI_VALUE[264]_i_2 
       (.I0(\SI_VALUE[272]_i_3_n_0 ),
        .I1(\SI_VALUE[176]_i_3_n_0 ),
        .I2(\SI_VALUE_reg[273] ),
        .I3(\SI_VALUE[264]_i_3_n_0 ),
        .I4(\SI_VALUE_reg[273]_0 ),
        .I5(\SI_VALUE[272]_i_2_n_0 ),
        .O(\SI_VALUE[264]_i_2_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair31" *) 
  LUT5 #(
    .INIT(32'hFFF35FFF)) 
    \SI_VALUE[264]_i_3 
       (.I0(P),
        .I1(S_RESULT_S_C[34]),
        .I2(\SI_VALUE_reg[209] ),
        .I3(\SI_VALUE_reg[34] [2]),
        .I4(\SI_VALUE_reg[209]_0 ),
        .O(\SI_VALUE[264]_i_3_n_0 ));
  LUT1 #(
    .INIT(2'h1)) 
    \SI_VALUE[265]_i_1 
       (.I0(\SI_VALUE[265]_i_2_n_0 ),
        .O(SI_VALUE0[111]));
  LUT6 #(
    .INIT(64'hA0A0AFAFCFC0CFC0)) 
    \SI_VALUE[265]_i_2 
       (.I0(\SI_VALUE[273]_i_5_n_0 ),
        .I1(\SI_VALUE[177]_i_3_n_0 ),
        .I2(\SI_VALUE_reg[273] ),
        .I3(\SI_VALUE[273]_i_3_n_0 ),
        .I4(\SI_VALUE[265]_i_3_n_0 ),
        .I5(\SI_VALUE_reg[273]_0 ),
        .O(\SI_VALUE[265]_i_2_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair31" *) 
  LUT4 #(
    .INIT(16'h4000)) 
    \SI_VALUE[265]_i_3 
       (.I0(\SI_VALUE_reg[209]_0 ),
        .I1(\SI_VALUE_reg[209] ),
        .I2(S_RESULT_S_C[34]),
        .I3(\SI_VALUE_reg[34] [2]),
        .O(\SI_VALUE[265]_i_3_n_0 ));
  LUT5 #(
    .INIT(32'h5030503F)) 
    \SI_VALUE[266]_i_1 
       (.I0(\SI_VALUE[274]_i_3_n_0 ),
        .I1(\SI_VALUE[266]_i_2_n_0 ),
        .I2(\SI_VALUE_reg[273] ),
        .I3(\SI_VALUE_reg[273]_0 ),
        .I4(\SI_VALUE[274]_i_2_n_0 ),
        .O(SI_VALUE0[112]));
  LUT5 #(
    .INIT(32'hAFEBA028)) 
    \SI_VALUE[266]_i_2 
       (.I0(\SI_VALUE[266]_i_3_n_0 ),
        .I1(\SI_VALUE_reg[209]_0 ),
        .I2(\SI_VALUE_reg[34] [2]),
        .I3(\SI_VALUE_reg[209] ),
        .I4(\SI_VALUE[270]_i_4_n_0 ),
        .O(\SI_VALUE[266]_i_2_n_0 ));
  LUT6 #(
    .INIT(64'hFFCFDDFF00CFDD00)) 
    \SI_VALUE[266]_i_3 
       (.I0(S_RESULT_S_C[11]),
        .I1(\SI_VALUE_reg[279] ),
        .I2(S_RESULT_S_C[12]),
        .I3(\SI_VALUE_reg[209] ),
        .I4(\SI_VALUE_reg[209]_0 ),
        .I5(\SI_VALUE[266]_i_4_n_0 ),
        .O(\SI_VALUE[266]_i_3_n_0 ));
  LUT6 #(
    .INIT(64'hC4444444F7777777)) 
    \SI_VALUE[266]_i_4 
       (.I0(S_RESULT_S_C[13]),
        .I1(\SI_VALUE_reg[209] ),
        .I2(\SI_VALUE_reg[209]_0 ),
        .I3(\SI_VALUE_reg[34] [3]),
        .I4(\SI_VALUE_reg[34] [2]),
        .I5(S_RESULT_S_C[14]),
        .O(\SI_VALUE[266]_i_4_n_0 ));
  LUT5 #(
    .INIT(32'h5030503F)) 
    \SI_VALUE[267]_i_1 
       (.I0(\SI_VALUE[275]_i_3_n_0 ),
        .I1(\SI_VALUE[267]_i_2_n_0 ),
        .I2(\SI_VALUE_reg[273] ),
        .I3(\SI_VALUE_reg[273]_0 ),
        .I4(\SI_VALUE[275]_i_2_n_0 ),
        .O(SI_VALUE0[113]));
  LUT5 #(
    .INIT(32'hAFEBA028)) 
    \SI_VALUE[267]_i_2 
       (.I0(\SI_VALUE[267]_i_3_n_0 ),
        .I1(\SI_VALUE_reg[209]_0 ),
        .I2(\SI_VALUE_reg[34] [2]),
        .I3(\SI_VALUE_reg[209] ),
        .I4(\SI_VALUE[271]_i_4_n_0 ),
        .O(\SI_VALUE[267]_i_2_n_0 ));
  LUT6 #(
    .INIT(64'hFFCFDDFF00CFDD00)) 
    \SI_VALUE[267]_i_3 
       (.I0(S_RESULT_S_C[12]),
        .I1(\SI_VALUE_reg[279] ),
        .I2(S_RESULT_S_C[13]),
        .I3(\SI_VALUE_reg[209] ),
        .I4(\SI_VALUE_reg[209]_0 ),
        .I5(\SI_VALUE[267]_i_4_n_0 ),
        .O(\SI_VALUE[267]_i_3_n_0 ));
  LUT6 #(
    .INIT(64'hC4444444F7777777)) 
    \SI_VALUE[267]_i_4 
       (.I0(S_RESULT_S_C[14]),
        .I1(\SI_VALUE_reg[209] ),
        .I2(\SI_VALUE_reg[209]_0 ),
        .I3(\SI_VALUE_reg[34] [3]),
        .I4(\SI_VALUE_reg[34] [2]),
        .I5(S_RESULT_S_C[15]),
        .O(\SI_VALUE[267]_i_4_n_0 ));
  LUT5 #(
    .INIT(32'h470047FF)) 
    \SI_VALUE[268]_i_1 
       (.I0(\SI_VALUE[276]_i_3_n_0 ),
        .I1(\SI_VALUE_reg[273]_0 ),
        .I2(\SI_VALUE[268]_i_2_n_0 ),
        .I3(\SI_VALUE_reg[273] ),
        .I4(\SI_VALUE[268]_i_3_n_0 ),
        .O(SI_VALUE0[114]));
  LUT5 #(
    .INIT(32'hAFEBA028)) 
    \SI_VALUE[268]_i_2 
       (.I0(\SI_VALUE[268]_i_4_n_0 ),
        .I1(\SI_VALUE_reg[209]_0 ),
        .I2(\SI_VALUE_reg[34] [2]),
        .I3(\SI_VALUE_reg[209] ),
        .I4(\SI_VALUE[272]_i_5_n_0 ),
        .O(\SI_VALUE[268]_i_2_n_0 ));
  LUT6 #(
    .INIT(64'hFDEFFFDD5DE5AADD)) 
    \SI_VALUE[268]_i_3 
       (.I0(\SI_VALUE_reg[34] [3]),
        .I1(\SI_VALUE[276]_i_5_n_0 ),
        .I2(\SI_VALUE_reg[209] ),
        .I3(\SI_VALUE_reg[34] [2]),
        .I4(\SI_VALUE_reg[209]_0 ),
        .I5(\SI_VALUE[276]_i_4_n_0 ),
        .O(\SI_VALUE[268]_i_3_n_0 ));
  LUT6 #(
    .INIT(64'hFFCFDDFF00CFDD00)) 
    \SI_VALUE[268]_i_4 
       (.I0(S_RESULT_S_C[13]),
        .I1(\SI_VALUE_reg[279] ),
        .I2(S_RESULT_S_C[14]),
        .I3(\SI_VALUE_reg[209] ),
        .I4(\SI_VALUE_reg[209]_0 ),
        .I5(\SI_VALUE[268]_i_5_n_0 ),
        .O(\SI_VALUE[268]_i_4_n_0 ));
  LUT6 #(
    .INIT(64'hC4444444F7777777)) 
    \SI_VALUE[268]_i_5 
       (.I0(S_RESULT_S_C[15]),
        .I1(\SI_VALUE_reg[209] ),
        .I2(\SI_VALUE_reg[209]_0 ),
        .I3(\SI_VALUE_reg[34] [3]),
        .I4(\SI_VALUE_reg[34] [2]),
        .I5(S_RESULT_S_C[16]),
        .O(\SI_VALUE[268]_i_5_n_0 ));
  LUT5 #(
    .INIT(32'h470047FF)) 
    \SI_VALUE[269]_i_1 
       (.I0(\SI_VALUE[277]_i_3_n_0 ),
        .I1(\SI_VALUE_reg[273]_0 ),
        .I2(\SI_VALUE[269]_i_2_n_0 ),
        .I3(\SI_VALUE_reg[273] ),
        .I4(\SI_VALUE[269]_i_3_n_0 ),
        .O(SI_VALUE0[115]));
  LUT5 #(
    .INIT(32'hAFEBA028)) 
    \SI_VALUE[269]_i_2 
       (.I0(\SI_VALUE[269]_i_4_n_0 ),
        .I1(\SI_VALUE_reg[209]_0 ),
        .I2(\SI_VALUE_reg[34] [2]),
        .I3(\SI_VALUE_reg[209] ),
        .I4(\SI_VALUE[273]_i_6_n_0 ),
        .O(\SI_VALUE[269]_i_2_n_0 ));
  LUT6 #(
    .INIT(64'hFFFFFF7F5FF5AA7F)) 
    \SI_VALUE[269]_i_3 
       (.I0(\SI_VALUE_reg[34] [3]),
        .I1(S_RESULT_S_C[34]),
        .I2(\SI_VALUE_reg[209] ),
        .I3(\SI_VALUE_reg[34] [2]),
        .I4(\SI_VALUE_reg[209]_0 ),
        .I5(\SI_VALUE[277]_i_4_n_0 ),
        .O(\SI_VALUE[269]_i_3_n_0 ));
  LUT6 #(
    .INIT(64'hFFCFDDFF00CFDD00)) 
    \SI_VALUE[269]_i_4 
       (.I0(S_RESULT_S_C[14]),
        .I1(\SI_VALUE_reg[279] ),
        .I2(S_RESULT_S_C[15]),
        .I3(\SI_VALUE_reg[209] ),
        .I4(\SI_VALUE_reg[209]_0 ),
        .I5(\SI_VALUE[269]_i_5_n_0 ),
        .O(\SI_VALUE[269]_i_4_n_0 ));
  LUT6 #(
    .INIT(64'hC4444444F7777777)) 
    \SI_VALUE[269]_i_5 
       (.I0(S_RESULT_S_C[16]),
        .I1(\SI_VALUE_reg[209] ),
        .I2(\SI_VALUE_reg[209]_0 ),
        .I3(\SI_VALUE_reg[34] [3]),
        .I4(\SI_VALUE_reg[34] [2]),
        .I5(S_RESULT_S_C[17]),
        .O(\SI_VALUE[269]_i_5_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair46" *) 
  LUT5 #(
    .INIT(32'h40000001)) 
    \SI_VALUE[26]_i_1 
       (.I0(\SI_VALUE[250]_i_2_n_0 ),
        .I1(\SI_VALUE_reg[34] [1]),
        .I2(\SI_VALUE_reg[34] [2]),
        .I3(\SI_VALUE_reg[34] [3]),
        .I4(\SI_VALUE_reg[34] [0]),
        .O(SI_VALUE0[26]));
  LUT6 #(
    .INIT(64'h50305030503F5030)) 
    \SI_VALUE[270]_i_1 
       (.I0(\SI_VALUE[278]_i_3_n_0 ),
        .I1(\SI_VALUE[270]_i_2_n_0 ),
        .I2(\SI_VALUE_reg[273] ),
        .I3(\SI_VALUE_reg[273]_0 ),
        .I4(\SI_VALUE_reg[206] ),
        .I5(\SI_VALUE[278]_i_2_n_0 ),
        .O(SI_VALUE0[116]));
  LUT5 #(
    .INIT(32'hAFEBA028)) 
    \SI_VALUE[270]_i_2 
       (.I0(\SI_VALUE[270]_i_4_n_0 ),
        .I1(\SI_VALUE_reg[209]_0 ),
        .I2(\SI_VALUE_reg[34] [2]),
        .I3(\SI_VALUE_reg[209] ),
        .I4(\SI_VALUE[274]_i_4_n_0 ),
        .O(\SI_VALUE[270]_i_2_n_0 ));
  LUT6 #(
    .INIT(64'hFFCFDDFF00CFDD00)) 
    \SI_VALUE[270]_i_4 
       (.I0(S_RESULT_S_C[15]),
        .I1(\SI_VALUE_reg[279] ),
        .I2(S_RESULT_S_C[16]),
        .I3(\SI_VALUE_reg[209] ),
        .I4(\SI_VALUE_reg[209]_0 ),
        .I5(\SI_VALUE[270]_i_5_n_0 ),
        .O(\SI_VALUE[270]_i_4_n_0 ));
  LUT6 #(
    .INIT(64'hC4444444F7777777)) 
    \SI_VALUE[270]_i_5 
       (.I0(S_RESULT_S_C[17]),
        .I1(\SI_VALUE_reg[209] ),
        .I2(\SI_VALUE_reg[209]_0 ),
        .I3(\SI_VALUE_reg[34] [3]),
        .I4(\SI_VALUE_reg[34] [2]),
        .I5(S_RESULT_S_C[18]),
        .O(\SI_VALUE[270]_i_5_n_0 ));
  LUT5 #(
    .INIT(32'h470047FF)) 
    \SI_VALUE[271]_i_1 
       (.I0(\SI_VALUE[279]_i_5_n_0 ),
        .I1(\SI_VALUE_reg[273]_0 ),
        .I2(\SI_VALUE[271]_i_2_n_0 ),
        .I3(\SI_VALUE_reg[273] ),
        .I4(\SI_VALUE[271]_i_3_n_0 ),
        .O(SI_VALUE0[117]));
  LUT5 #(
    .INIT(32'hAFEBA028)) 
    \SI_VALUE[271]_i_2 
       (.I0(\SI_VALUE[271]_i_4_n_0 ),
        .I1(\SI_VALUE_reg[209]_0 ),
        .I2(\SI_VALUE_reg[34] [2]),
        .I3(\SI_VALUE_reg[209] ),
        .I4(\SI_VALUE[275]_i_4_n_0 ),
        .O(\SI_VALUE[271]_i_2_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair57" *) 
  LUT5 #(
    .INIT(32'hFFFDFFBF)) 
    \SI_VALUE[271]_i_3 
       (.I0(\SI_VALUE_reg[209]_0 ),
        .I1(\SI_VALUE_reg[34] [2]),
        .I2(\SI_VALUE_reg[209] ),
        .I3(\SI_VALUE[207]_i_2_n_0 ),
        .I4(\SI_VALUE_reg[34] [3]),
        .O(\SI_VALUE[271]_i_3_n_0 ));
  LUT6 #(
    .INIT(64'hFFCFDDFF00CFDD00)) 
    \SI_VALUE[271]_i_4 
       (.I0(S_RESULT_S_C[16]),
        .I1(\SI_VALUE_reg[279] ),
        .I2(S_RESULT_S_C[17]),
        .I3(\SI_VALUE_reg[209] ),
        .I4(\SI_VALUE_reg[209]_0 ),
        .I5(\SI_VALUE[271]_i_5_n_0 ),
        .O(\SI_VALUE[271]_i_4_n_0 ));
  LUT6 #(
    .INIT(64'hC4444444F7777777)) 
    \SI_VALUE[271]_i_5 
       (.I0(S_RESULT_S_C[18]),
        .I1(\SI_VALUE_reg[209] ),
        .I2(\SI_VALUE_reg[209]_0 ),
        .I3(\SI_VALUE_reg[34] [3]),
        .I4(\SI_VALUE_reg[34] [2]),
        .I5(S_RESULT_S_C[19]),
        .O(\SI_VALUE[271]_i_5_n_0 ));
  LUT5 #(
    .INIT(32'h470047FF)) 
    \SI_VALUE[272]_i_1 
       (.I0(\SI_VALUE[272]_i_2_n_0 ),
        .I1(\SI_VALUE_reg[273]_0 ),
        .I2(\SI_VALUE[272]_i_3_n_0 ),
        .I3(\SI_VALUE_reg[273] ),
        .I4(\SI_VALUE[272]_i_4_n_0 ),
        .O(SI_VALUE0[118]));
  LUT5 #(
    .INIT(32'hAFEBA028)) 
    \SI_VALUE[272]_i_2 
       (.I0(\SI_VALUE[276]_i_7_n_0 ),
        .I1(\SI_VALUE_reg[209]_0 ),
        .I2(\SI_VALUE_reg[34] [2]),
        .I3(\SI_VALUE_reg[209] ),
        .I4(\SI_VALUE[276]_i_4_n_0 ),
        .O(\SI_VALUE[272]_i_2_n_0 ));
  LUT5 #(
    .INIT(32'hAFEBA028)) 
    \SI_VALUE[272]_i_3 
       (.I0(\SI_VALUE[272]_i_5_n_0 ),
        .I1(\SI_VALUE_reg[209]_0 ),
        .I2(\SI_VALUE_reg[34] [2]),
        .I3(\SI_VALUE_reg[209] ),
        .I4(\SI_VALUE[276]_i_6_n_0 ),
        .O(\SI_VALUE[272]_i_3_n_0 ));
  LUT6 #(
    .INIT(64'hFDFFBFBFFDFFFFFF)) 
    \SI_VALUE[272]_i_4 
       (.I0(\SI_VALUE_reg[209]_0 ),
        .I1(\SI_VALUE_reg[34] [2]),
        .I2(\SI_VALUE_reg[209] ),
        .I3(S_RESULT_S_C[34]),
        .I4(\SI_VALUE_reg[34] [3]),
        .I5(P),
        .O(\SI_VALUE[272]_i_4_n_0 ));
  LUT6 #(
    .INIT(64'hFFCFDDFF00CFDD00)) 
    \SI_VALUE[272]_i_5 
       (.I0(S_RESULT_S_C[17]),
        .I1(\SI_VALUE_reg[279] ),
        .I2(S_RESULT_S_C[18]),
        .I3(\SI_VALUE_reg[209] ),
        .I4(\SI_VALUE_reg[209]_0 ),
        .I5(\SI_VALUE[272]_i_6_n_0 ),
        .O(\SI_VALUE[272]_i_5_n_0 ));
  LUT6 #(
    .INIT(64'hC4444444F7777777)) 
    \SI_VALUE[272]_i_6 
       (.I0(S_RESULT_S_C[19]),
        .I1(\SI_VALUE_reg[209] ),
        .I2(\SI_VALUE_reg[209]_0 ),
        .I3(\SI_VALUE_reg[34] [3]),
        .I4(\SI_VALUE_reg[34] [2]),
        .I5(S_RESULT_S_C[20]),
        .O(\SI_VALUE[272]_i_6_n_0 ));
  LUT5 #(
    .INIT(32'hFFFF202A)) 
    \SI_VALUE[273]_i_1 
       (.I0(\SI_VALUE_reg[273] ),
        .I1(\SI_VALUE[273]_i_3_n_0 ),
        .I2(\SI_VALUE_reg[273]_0 ),
        .I3(\SI_VALUE[273]_i_5_n_0 ),
        .I4(SI_VALUE0[90]),
        .O(SI_VALUE0[119]));
  LUT5 #(
    .INIT(32'hAFEBA028)) 
    \SI_VALUE[273]_i_3 
       (.I0(\SI_VALUE[277]_i_6_n_0 ),
        .I1(\SI_VALUE_reg[209]_0 ),
        .I2(\SI_VALUE_reg[34] [2]),
        .I3(\SI_VALUE_reg[209] ),
        .I4(\SI_VALUE[277]_i_4_n_0 ),
        .O(\SI_VALUE[273]_i_3_n_0 ));
  LUT5 #(
    .INIT(32'hAFEBA028)) 
    \SI_VALUE[273]_i_5 
       (.I0(\SI_VALUE[273]_i_6_n_0 ),
        .I1(\SI_VALUE_reg[209]_0 ),
        .I2(\SI_VALUE_reg[34] [2]),
        .I3(\SI_VALUE_reg[209] ),
        .I4(\SI_VALUE[277]_i_5_n_0 ),
        .O(\SI_VALUE[273]_i_5_n_0 ));
  LUT6 #(
    .INIT(64'hFFCFDDFF00CFDD00)) 
    \SI_VALUE[273]_i_6 
       (.I0(S_RESULT_S_C[18]),
        .I1(\SI_VALUE_reg[279] ),
        .I2(S_RESULT_S_C[19]),
        .I3(\SI_VALUE_reg[209] ),
        .I4(\SI_VALUE_reg[209]_0 ),
        .I5(\SI_VALUE[273]_i_7_n_0 ),
        .O(\SI_VALUE[273]_i_6_n_0 ));
  LUT6 #(
    .INIT(64'hC4444444F7777777)) 
    \SI_VALUE[273]_i_7 
       (.I0(S_RESULT_S_C[20]),
        .I1(\SI_VALUE_reg[209] ),
        .I2(\SI_VALUE_reg[209]_0 ),
        .I3(\SI_VALUE_reg[34] [3]),
        .I4(\SI_VALUE_reg[34] [2]),
        .I5(S_RESULT_S_C[21]),
        .O(\SI_VALUE[273]_i_7_n_0 ));
  LUT6 #(
    .INIT(64'h10444511DF7775DD)) 
    \SI_VALUE[274]_i_1 
       (.I0(\SI_VALUE[274]_i_2_n_0 ),
        .I1(\SI_VALUE_reg[34] [2]),
        .I2(\SI_VALUE_reg[209] ),
        .I3(\SI_VALUE_reg[209]_0 ),
        .I4(\SI_VALUE_reg[34] [3]),
        .I5(\SI_VALUE[274]_i_3_n_0 ),
        .O(SI_VALUE0[120]));
  (* SOFT_HLUTNM = "soft_lutpair56" *) 
  LUT5 #(
    .INIT(32'hAFEBA028)) 
    \SI_VALUE[274]_i_2 
       (.I0(\SI_VALUE[278]_i_6_n_0 ),
        .I1(\SI_VALUE_reg[209]_0 ),
        .I2(\SI_VALUE_reg[34] [2]),
        .I3(\SI_VALUE_reg[209] ),
        .I4(\SI_VALUE[278]_i_2_n_0 ),
        .O(\SI_VALUE[274]_i_2_n_0 ));
  LUT5 #(
    .INIT(32'hAFEBA028)) 
    \SI_VALUE[274]_i_3 
       (.I0(\SI_VALUE[274]_i_4_n_0 ),
        .I1(\SI_VALUE_reg[209]_0 ),
        .I2(\SI_VALUE_reg[34] [2]),
        .I3(\SI_VALUE_reg[209] ),
        .I4(\SI_VALUE[278]_i_5_n_0 ),
        .O(\SI_VALUE[274]_i_3_n_0 ));
  LUT6 #(
    .INIT(64'hFFCFDDFF00CFDD00)) 
    \SI_VALUE[274]_i_4 
       (.I0(S_RESULT_S_C[19]),
        .I1(\SI_VALUE_reg[279] ),
        .I2(S_RESULT_S_C[20]),
        .I3(\SI_VALUE_reg[209] ),
        .I4(\SI_VALUE_reg[209]_0 ),
        .I5(\SI_VALUE[274]_i_5_n_0 ),
        .O(\SI_VALUE[274]_i_4_n_0 ));
  LUT6 #(
    .INIT(64'hC4444444F7777777)) 
    \SI_VALUE[274]_i_5 
       (.I0(S_RESULT_S_C[21]),
        .I1(\SI_VALUE_reg[209] ),
        .I2(\SI_VALUE_reg[209]_0 ),
        .I3(\SI_VALUE_reg[34] [3]),
        .I4(\SI_VALUE_reg[34] [2]),
        .I5(S_RESULT_S_C[22]),
        .O(\SI_VALUE[274]_i_5_n_0 ));
  LUT6 #(
    .INIT(64'h10444511DF7775DD)) 
    \SI_VALUE[275]_i_1 
       (.I0(\SI_VALUE[275]_i_2_n_0 ),
        .I1(\SI_VALUE_reg[34] [2]),
        .I2(\SI_VALUE_reg[209] ),
        .I3(\SI_VALUE_reg[209]_0 ),
        .I4(\SI_VALUE_reg[34] [3]),
        .I5(\SI_VALUE[275]_i_3_n_0 ),
        .O(SI_VALUE0[121]));
  LUT5 #(
    .INIT(32'hAFEBA028)) 
    \SI_VALUE[275]_i_2 
       (.I0(\SI_VALUE[279]_i_9_n_0 ),
        .I1(\SI_VALUE_reg[209]_0 ),
        .I2(\SI_VALUE_reg[34] [2]),
        .I3(\SI_VALUE_reg[209] ),
        .I4(\SI_VALUE[279]_i_4_n_0 ),
        .O(\SI_VALUE[275]_i_2_n_0 ));
  LUT5 #(
    .INIT(32'hAFEBA028)) 
    \SI_VALUE[275]_i_3 
       (.I0(\SI_VALUE[275]_i_4_n_0 ),
        .I1(\SI_VALUE_reg[209]_0 ),
        .I2(\SI_VALUE_reg[34] [2]),
        .I3(\SI_VALUE_reg[209] ),
        .I4(\SI_VALUE[279]_i_8_n_0 ),
        .O(\SI_VALUE[275]_i_3_n_0 ));
  LUT6 #(
    .INIT(64'hFFCFDDFF00CFDD00)) 
    \SI_VALUE[275]_i_4 
       (.I0(S_RESULT_S_C[20]),
        .I1(\SI_VALUE_reg[279] ),
        .I2(S_RESULT_S_C[21]),
        .I3(\SI_VALUE_reg[209] ),
        .I4(\SI_VALUE_reg[209]_0 ),
        .I5(\SI_VALUE[275]_i_5_n_0 ),
        .O(\SI_VALUE[275]_i_4_n_0 ));
  LUT6 #(
    .INIT(64'hC4444444F7777777)) 
    \SI_VALUE[275]_i_5 
       (.I0(S_RESULT_S_C[22]),
        .I1(\SI_VALUE_reg[209] ),
        .I2(\SI_VALUE_reg[209]_0 ),
        .I3(\SI_VALUE_reg[34] [3]),
        .I4(\SI_VALUE_reg[34] [2]),
        .I5(S_RESULT_S_C[23]),
        .O(\SI_VALUE[275]_i_5_n_0 ));
  LUT6 #(
    .INIT(64'h10444511DF7775DD)) 
    \SI_VALUE[276]_i_1 
       (.I0(\SI_VALUE[276]_i_2_n_0 ),
        .I1(\SI_VALUE_reg[34] [2]),
        .I2(\SI_VALUE_reg[209] ),
        .I3(\SI_VALUE_reg[209]_0 ),
        .I4(\SI_VALUE_reg[34] [3]),
        .I5(\SI_VALUE[276]_i_3_n_0 ),
        .O(SI_VALUE0[122]));
  LUT6 #(
    .INIT(64'hC4444444F7777777)) 
    \SI_VALUE[276]_i_10 
       (.I0(S_RESULT_S_C[27]),
        .I1(\SI_VALUE_reg[209] ),
        .I2(\SI_VALUE_reg[209]_0 ),
        .I3(\SI_VALUE_reg[34] [3]),
        .I4(\SI_VALUE_reg[34] [2]),
        .I5(S_RESULT_S_C[28]),
        .O(\SI_VALUE[276]_i_10_n_0 ));
  LUT5 #(
    .INIT(32'hAFEBA028)) 
    \SI_VALUE[276]_i_2 
       (.I0(\SI_VALUE[276]_i_4_n_0 ),
        .I1(\SI_VALUE_reg[209]_0 ),
        .I2(\SI_VALUE_reg[34] [2]),
        .I3(\SI_VALUE_reg[209] ),
        .I4(\SI_VALUE[276]_i_5_n_0 ),
        .O(\SI_VALUE[276]_i_2_n_0 ));
  LUT5 #(
    .INIT(32'hAFEBA028)) 
    \SI_VALUE[276]_i_3 
       (.I0(\SI_VALUE[276]_i_6_n_0 ),
        .I1(\SI_VALUE_reg[209]_0 ),
        .I2(\SI_VALUE_reg[34] [2]),
        .I3(\SI_VALUE_reg[209] ),
        .I4(\SI_VALUE[276]_i_7_n_0 ),
        .O(\SI_VALUE[276]_i_3_n_0 ));
  LUT6 #(
    .INIT(64'hFFCFDDFF00CFDD00)) 
    \SI_VALUE[276]_i_4 
       (.I0(S_RESULT_S_C[29]),
        .I1(\SI_VALUE_reg[279] ),
        .I2(S_RESULT_S_C[30]),
        .I3(\SI_VALUE_reg[209] ),
        .I4(\SI_VALUE_reg[209]_0 ),
        .I5(\SI_VALUE[276]_i_8_n_0 ),
        .O(\SI_VALUE[276]_i_4_n_0 ));
  LUT4 #(
    .INIT(16'hF35F)) 
    \SI_VALUE[276]_i_5 
       (.I0(S_RESULT_S_C[34]),
        .I1(P),
        .I2(\SI_VALUE_reg[209]_0 ),
        .I3(\SI_VALUE_reg[209] ),
        .O(\SI_VALUE[276]_i_5_n_0 ));
  LUT6 #(
    .INIT(64'hFFCFDDFF00CFDD00)) 
    \SI_VALUE[276]_i_6 
       (.I0(S_RESULT_S_C[21]),
        .I1(\SI_VALUE_reg[279] ),
        .I2(S_RESULT_S_C[22]),
        .I3(\SI_VALUE_reg[209] ),
        .I4(\SI_VALUE_reg[209]_0 ),
        .I5(\SI_VALUE[276]_i_9_n_0 ),
        .O(\SI_VALUE[276]_i_6_n_0 ));
  LUT6 #(
    .INIT(64'hFFCFDDFF00CFDD00)) 
    \SI_VALUE[276]_i_7 
       (.I0(S_RESULT_S_C[25]),
        .I1(\SI_VALUE_reg[279] ),
        .I2(S_RESULT_S_C[26]),
        .I3(\SI_VALUE_reg[209] ),
        .I4(\SI_VALUE_reg[209]_0 ),
        .I5(\SI_VALUE[276]_i_10_n_0 ),
        .O(\SI_VALUE[276]_i_7_n_0 ));
  LUT6 #(
    .INIT(64'hC4444444F7777777)) 
    \SI_VALUE[276]_i_8 
       (.I0(S_RESULT_S_C[31]),
        .I1(\SI_VALUE_reg[209] ),
        .I2(\SI_VALUE_reg[209]_0 ),
        .I3(\SI_VALUE_reg[34] [3]),
        .I4(\SI_VALUE_reg[34] [2]),
        .I5(S_RESULT_S_C[32]),
        .O(\SI_VALUE[276]_i_8_n_0 ));
  LUT6 #(
    .INIT(64'hC4444444F7777777)) 
    \SI_VALUE[276]_i_9 
       (.I0(S_RESULT_S_C[23]),
        .I1(\SI_VALUE_reg[209] ),
        .I2(\SI_VALUE_reg[209]_0 ),
        .I3(\SI_VALUE_reg[34] [3]),
        .I4(\SI_VALUE_reg[34] [2]),
        .I5(S_RESULT_S_C[24]),
        .O(\SI_VALUE[276]_i_9_n_0 ));
  LUT6 #(
    .INIT(64'h10444511DF7775DD)) 
    \SI_VALUE[277]_i_1 
       (.I0(\SI_VALUE[277]_i_2_n_0 ),
        .I1(\SI_VALUE_reg[34] [2]),
        .I2(\SI_VALUE_reg[209] ),
        .I3(\SI_VALUE_reg[209]_0 ),
        .I4(\SI_VALUE_reg[34] [3]),
        .I5(\SI_VALUE[277]_i_3_n_0 ),
        .O(SI_VALUE0[125]));
  LUT5 #(
    .INIT(32'hACEBAFEB)) 
    \SI_VALUE[277]_i_2 
       (.I0(\SI_VALUE[277]_i_4_n_0 ),
        .I1(\SI_VALUE_reg[209]_0 ),
        .I2(\SI_VALUE_reg[34] [2]),
        .I3(\SI_VALUE_reg[209] ),
        .I4(S_RESULT_S_C[34]),
        .O(\SI_VALUE[277]_i_2_n_0 ));
  LUT5 #(
    .INIT(32'hAFEBA028)) 
    \SI_VALUE[277]_i_3 
       (.I0(\SI_VALUE[277]_i_5_n_0 ),
        .I1(\SI_VALUE_reg[209]_0 ),
        .I2(\SI_VALUE_reg[34] [2]),
        .I3(\SI_VALUE_reg[209] ),
        .I4(\SI_VALUE[277]_i_6_n_0 ),
        .O(\SI_VALUE[277]_i_3_n_0 ));
  LUT6 #(
    .INIT(64'hFFCFDDFF00CFDD00)) 
    \SI_VALUE[277]_i_4 
       (.I0(S_RESULT_S_C[30]),
        .I1(\SI_VALUE_reg[279] ),
        .I2(S_RESULT_S_C[31]),
        .I3(\SI_VALUE_reg[209] ),
        .I4(\SI_VALUE_reg[209]_0 ),
        .I5(\SI_VALUE[207]_i_2_n_0 ),
        .O(\SI_VALUE[277]_i_4_n_0 ));
  LUT6 #(
    .INIT(64'hFFCFDDFF00CFDD00)) 
    \SI_VALUE[277]_i_5 
       (.I0(S_RESULT_S_C[22]),
        .I1(\SI_VALUE_reg[279] ),
        .I2(S_RESULT_S_C[23]),
        .I3(\SI_VALUE_reg[209] ),
        .I4(\SI_VALUE_reg[209]_0 ),
        .I5(\SI_VALUE[277]_i_7_n_0 ),
        .O(\SI_VALUE[277]_i_5_n_0 ));
  LUT6 #(
    .INIT(64'hFFCFDDFF00CFDD00)) 
    \SI_VALUE[277]_i_6 
       (.I0(S_RESULT_S_C[26]),
        .I1(\SI_VALUE_reg[279] ),
        .I2(S_RESULT_S_C[27]),
        .I3(\SI_VALUE_reg[209] ),
        .I4(\SI_VALUE_reg[209]_0 ),
        .I5(\SI_VALUE[277]_i_8_n_0 ),
        .O(\SI_VALUE[277]_i_6_n_0 ));
  LUT6 #(
    .INIT(64'hC4444444F7777777)) 
    \SI_VALUE[277]_i_7 
       (.I0(S_RESULT_S_C[24]),
        .I1(\SI_VALUE_reg[209] ),
        .I2(\SI_VALUE_reg[209]_0 ),
        .I3(\SI_VALUE_reg[34] [3]),
        .I4(\SI_VALUE_reg[34] [2]),
        .I5(S_RESULT_S_C[25]),
        .O(\SI_VALUE[277]_i_7_n_0 ));
  LUT6 #(
    .INIT(64'hC4444444F7777777)) 
    \SI_VALUE[277]_i_8 
       (.I0(S_RESULT_S_C[28]),
        .I1(\SI_VALUE_reg[209] ),
        .I2(\SI_VALUE_reg[209]_0 ),
        .I3(\SI_VALUE_reg[34] [3]),
        .I4(\SI_VALUE_reg[34] [2]),
        .I5(S_RESULT_S_C[29]),
        .O(\SI_VALUE[277]_i_8_n_0 ));
  LUT6 #(
    .INIT(64'h00444100CF7771CC)) 
    \SI_VALUE[278]_i_1 
       (.I0(\SI_VALUE[278]_i_2_n_0 ),
        .I1(\SI_VALUE_reg[34] [2]),
        .I2(\SI_VALUE_reg[209] ),
        .I3(\SI_VALUE_reg[209]_0 ),
        .I4(\SI_VALUE_reg[34] [3]),
        .I5(\SI_VALUE[278]_i_3_n_0 ),
        .O(SI_VALUE0[126]));
  LUT6 #(
    .INIT(64'hFFCFDDFF00CFDD00)) 
    \SI_VALUE[278]_i_2 
       (.I0(S_RESULT_S_C[31]),
        .I1(\SI_VALUE_reg[279] ),
        .I2(S_RESULT_S_C[32]),
        .I3(\SI_VALUE_reg[209] ),
        .I4(\SI_VALUE_reg[209]_0 ),
        .I5(\SI_VALUE[278]_i_4_n_0 ),
        .O(\SI_VALUE[278]_i_2_n_0 ));
  LUT5 #(
    .INIT(32'hAFEBA028)) 
    \SI_VALUE[278]_i_3 
       (.I0(\SI_VALUE[278]_i_5_n_0 ),
        .I1(\SI_VALUE_reg[209]_0 ),
        .I2(\SI_VALUE_reg[34] [2]),
        .I3(\SI_VALUE_reg[209] ),
        .I4(\SI_VALUE[278]_i_6_n_0 ),
        .O(\SI_VALUE[278]_i_3_n_0 ));
  LUT6 #(
    .INIT(64'hC4444444F7777777)) 
    \SI_VALUE[278]_i_4 
       (.I0(P),
        .I1(\SI_VALUE_reg[209] ),
        .I2(\SI_VALUE_reg[209]_0 ),
        .I3(\SI_VALUE_reg[34] [3]),
        .I4(\SI_VALUE_reg[34] [2]),
        .I5(S_RESULT_S_C[34]),
        .O(\SI_VALUE[278]_i_4_n_0 ));
  LUT6 #(
    .INIT(64'hFFCFDDFF00CFDD00)) 
    \SI_VALUE[278]_i_5 
       (.I0(S_RESULT_S_C[23]),
        .I1(\SI_VALUE_reg[279] ),
        .I2(S_RESULT_S_C[24]),
        .I3(\SI_VALUE_reg[209] ),
        .I4(\SI_VALUE_reg[209]_0 ),
        .I5(\SI_VALUE[278]_i_7_n_0 ),
        .O(\SI_VALUE[278]_i_5_n_0 ));
  LUT6 #(
    .INIT(64'hFFCFDDFF00CFDD00)) 
    \SI_VALUE[278]_i_6 
       (.I0(S_RESULT_S_C[27]),
        .I1(\SI_VALUE_reg[279] ),
        .I2(S_RESULT_S_C[28]),
        .I3(\SI_VALUE_reg[209] ),
        .I4(\SI_VALUE_reg[209]_0 ),
        .I5(\SI_VALUE[278]_i_8_n_0 ),
        .O(\SI_VALUE[278]_i_6_n_0 ));
  LUT6 #(
    .INIT(64'hC4444444F7777777)) 
    \SI_VALUE[278]_i_7 
       (.I0(S_RESULT_S_C[25]),
        .I1(\SI_VALUE_reg[209] ),
        .I2(\SI_VALUE_reg[209]_0 ),
        .I3(\SI_VALUE_reg[34] [3]),
        .I4(\SI_VALUE_reg[34] [2]),
        .I5(S_RESULT_S_C[26]),
        .O(\SI_VALUE[278]_i_7_n_0 ));
  LUT6 #(
    .INIT(64'hC4444444F7777777)) 
    \SI_VALUE[278]_i_8 
       (.I0(S_RESULT_S_C[29]),
        .I1(\SI_VALUE_reg[209] ),
        .I2(\SI_VALUE_reg[209]_0 ),
        .I3(\SI_VALUE_reg[34] [3]),
        .I4(\SI_VALUE_reg[34] [2]),
        .I5(S_RESULT_S_C[30]),
        .O(\SI_VALUE[278]_i_8_n_0 ));
  LUT6 #(
    .INIT(64'hC4444444F7777777)) 
    \SI_VALUE[279]_i_10 
       (.I0(S_RESULT_S_C[26]),
        .I1(\SI_VALUE_reg[209] ),
        .I2(\SI_VALUE_reg[209]_0 ),
        .I3(\SI_VALUE_reg[34] [3]),
        .I4(\SI_VALUE_reg[34] [2]),
        .I5(S_RESULT_S_C[27]),
        .O(\SI_VALUE[279]_i_10_n_0 ));
  LUT6 #(
    .INIT(64'hC4444444F7777777)) 
    \SI_VALUE[279]_i_11 
       (.I0(S_RESULT_S_C[30]),
        .I1(\SI_VALUE_reg[209] ),
        .I2(\SI_VALUE_reg[209]_0 ),
        .I3(\SI_VALUE_reg[34] [3]),
        .I4(\SI_VALUE_reg[34] [2]),
        .I5(S_RESULT_S_C[31]),
        .O(\SI_VALUE[279]_i_11_n_0 ));
  LUT6 #(
    .INIT(64'h00444100CF7771CC)) 
    \SI_VALUE[279]_i_2 
       (.I0(\SI_VALUE[279]_i_4_n_0 ),
        .I1(\SI_VALUE_reg[34] [2]),
        .I2(\SI_VALUE_reg[209] ),
        .I3(\SI_VALUE_reg[209]_0 ),
        .I4(\SI_VALUE_reg[34] [3]),
        .I5(\SI_VALUE[279]_i_5_n_0 ),
        .O(SI_VALUE0[127]));
  LUT6 #(
    .INIT(64'hFFFFFFFF035FF35F)) 
    \SI_VALUE[279]_i_4 
       (.I0(S_RESULT_S_C[32]),
        .I1(P),
        .I2(\SI_VALUE_reg[209] ),
        .I3(\SI_VALUE_reg[209]_0 ),
        .I4(S_RESULT_S_C[34]),
        .I5(\SI_VALUE_reg[279] ),
        .O(\SI_VALUE[279]_i_4_n_0 ));
  LUT5 #(
    .INIT(32'hAFEBA028)) 
    \SI_VALUE[279]_i_5 
       (.I0(\SI_VALUE[279]_i_8_n_0 ),
        .I1(\SI_VALUE_reg[209]_0 ),
        .I2(\SI_VALUE_reg[34] [2]),
        .I3(\SI_VALUE_reg[209] ),
        .I4(\SI_VALUE[279]_i_9_n_0 ),
        .O(\SI_VALUE[279]_i_5_n_0 ));
  LUT6 #(
    .INIT(64'hFFCFDDFF00CFDD00)) 
    \SI_VALUE[279]_i_8 
       (.I0(S_RESULT_S_C[24]),
        .I1(\SI_VALUE_reg[279] ),
        .I2(S_RESULT_S_C[25]),
        .I3(\SI_VALUE_reg[209] ),
        .I4(\SI_VALUE_reg[209]_0 ),
        .I5(\SI_VALUE[279]_i_10_n_0 ),
        .O(\SI_VALUE[279]_i_8_n_0 ));
  LUT6 #(
    .INIT(64'hFFCFDDFF00CFDD00)) 
    \SI_VALUE[279]_i_9 
       (.I0(S_RESULT_S_C[28]),
        .I1(\SI_VALUE_reg[279] ),
        .I2(S_RESULT_S_C[29]),
        .I3(\SI_VALUE_reg[209] ),
        .I4(\SI_VALUE_reg[209]_0 ),
        .I5(\SI_VALUE[279]_i_11_n_0 ),
        .O(\SI_VALUE[279]_i_9_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair47" *) 
  LUT5 #(
    .INIT(32'h40000001)) 
    \SI_VALUE[27]_i_1 
       (.I0(\SI_VALUE[251]_i_2_n_0 ),
        .I1(\SI_VALUE_reg[34] [1]),
        .I2(\SI_VALUE_reg[34] [2]),
        .I3(\SI_VALUE_reg[34] [3]),
        .I4(\SI_VALUE_reg[34] [0]),
        .O(SI_VALUE0[27]));
  (* SOFT_HLUTNM = "soft_lutpair48" *) 
  LUT5 #(
    .INIT(32'h40000001)) 
    \SI_VALUE[28]_i_1 
       (.I0(\SI_VALUE[252]_i_2_n_0 ),
        .I1(\SI_VALUE_reg[34] [1]),
        .I2(\SI_VALUE_reg[34] [2]),
        .I3(\SI_VALUE_reg[34] [3]),
        .I4(\SI_VALUE_reg[34] [0]),
        .O(SI_VALUE0[28]));
  (* SOFT_HLUTNM = "soft_lutpair49" *) 
  LUT5 #(
    .INIT(32'h40000001)) 
    \SI_VALUE[29]_i_1 
       (.I0(\SI_VALUE[253]_i_2_n_0 ),
        .I1(\SI_VALUE_reg[34] [1]),
        .I2(\SI_VALUE_reg[34] [2]),
        .I3(\SI_VALUE_reg[34] [3]),
        .I4(\SI_VALUE_reg[34] [0]),
        .O(SI_VALUE0[29]));
  LUT5 #(
    .INIT(32'h00000001)) 
    \SI_VALUE[2]_i_1 
       (.I0(\SI_VALUE[2]_i_2_n_0 ),
        .I1(\SI_VALUE_reg[209]_0 ),
        .I2(\SI_VALUE_reg[209] ),
        .I3(\SI_VALUE_reg[34] [3]),
        .I4(\SI_VALUE_reg[34] [2]),
        .O(SI_VALUE0[2]));
  LUT6 #(
    .INIT(64'hC4444444F7777777)) 
    \SI_VALUE[2]_i_2 
       (.I0(S_RESULT_S_C[1]),
        .I1(\SI_VALUE_reg[209] ),
        .I2(\SI_VALUE_reg[209]_0 ),
        .I3(\SI_VALUE_reg[34] [3]),
        .I4(\SI_VALUE_reg[34] [2]),
        .I5(S_RESULT_S_C[2]),
        .O(\SI_VALUE[2]_i_2_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair50" *) 
  LUT5 #(
    .INIT(32'h40000001)) 
    \SI_VALUE[30]_i_1 
       (.I0(\SI_VALUE[254]_i_2_n_0 ),
        .I1(\SI_VALUE_reg[34] [1]),
        .I2(\SI_VALUE_reg[34] [2]),
        .I3(\SI_VALUE_reg[34] [3]),
        .I4(\SI_VALUE_reg[34] [0]),
        .O(SI_VALUE0[30]));
  (* SOFT_HLUTNM = "soft_lutpair51" *) 
  LUT5 #(
    .INIT(32'h40000001)) 
    \SI_VALUE[31]_i_1 
       (.I0(\SI_VALUE[255]_i_2_n_0 ),
        .I1(\SI_VALUE_reg[34] [1]),
        .I2(\SI_VALUE_reg[34] [2]),
        .I3(\SI_VALUE_reg[34] [3]),
        .I4(\SI_VALUE_reg[34] [0]),
        .O(SI_VALUE0[31]));
  (* SOFT_HLUTNM = "soft_lutpair39" *) 
  LUT5 #(
    .INIT(32'h00008001)) 
    \SI_VALUE[32]_i_1 
       (.I0(\SI_VALUE_reg[34] [3]),
        .I1(\SI_VALUE_reg[34] [2]),
        .I2(\SI_VALUE_reg[34] [0]),
        .I3(\SI_VALUE_reg[34] [1]),
        .I4(\SI_VALUE[256]_i_2_n_0 ),
        .O(SI_VALUE0[32]));
  (* SOFT_HLUTNM = "soft_lutpair38" *) 
  LUT5 #(
    .INIT(32'h00008001)) 
    \SI_VALUE[33]_i_1 
       (.I0(\SI_VALUE_reg[34] [3]),
        .I1(\SI_VALUE_reg[34] [2]),
        .I2(\SI_VALUE_reg[34] [0]),
        .I3(\SI_VALUE_reg[34] [1]),
        .I4(\SI_VALUE[257]_i_2_n_0 ),
        .O(SI_VALUE0[33]));
  (* SOFT_HLUTNM = "soft_lutpair37" *) 
  LUT5 #(
    .INIT(32'h00008001)) 
    \SI_VALUE[34]_i_2 
       (.I0(\SI_VALUE_reg[34] [3]),
        .I1(\SI_VALUE_reg[34] [2]),
        .I2(\SI_VALUE_reg[34] [0]),
        .I3(\SI_VALUE_reg[34] [1]),
        .I4(\SI_VALUE[258]_i_2_n_0 ),
        .O(SI_VALUE0[34]));
  (* SOFT_HLUTNM = "soft_lutpair34" *) 
  LUT5 #(
    .INIT(32'h00004A15)) 
    \SI_VALUE[35]_i_1 
       (.I0(\SI_VALUE_reg[34] [2]),
        .I1(\SI_VALUE_reg[209] ),
        .I2(\SI_VALUE_reg[209]_0 ),
        .I3(\SI_VALUE_reg[34] [3]),
        .I4(\SI_VALUE[211]_i_2_n_0 ),
        .O(SI_VALUE0[35]));
  (* SOFT_HLUTNM = "soft_lutpair43" *) 
  LUT1 #(
    .INIT(2'h1)) 
    \SI_VALUE[37]_i_1 
       (.I0(\SI_VALUE[141]_i_2_n_0 ),
        .O(SI_VALUE0[37]));
  (* SOFT_HLUTNM = "soft_lutpair59" *) 
  LUT4 #(
    .INIT(16'h0001)) 
    \SI_VALUE[3]_i_1 
       (.I0(\SI_VALUE_reg[34] [2]),
        .I1(\SI_VALUE_reg[209] ),
        .I2(\SI_VALUE_reg[34] [3]),
        .I3(\SI_VALUE[211]_i_2_n_0 ),
        .O(SI_VALUE0[3]));
  (* SOFT_HLUTNM = "soft_lutpair60" *) 
  LUT4 #(
    .INIT(16'h0001)) 
    \SI_VALUE[4]_i_1 
       (.I0(\SI_VALUE_reg[34] [2]),
        .I1(\SI_VALUE_reg[209] ),
        .I2(\SI_VALUE_reg[34] [3]),
        .I3(\SI_VALUE[212]_i_2_n_0 ),
        .O(SI_VALUE0[4]));
  (* SOFT_HLUTNM = "soft_lutpair59" *) 
  LUT4 #(
    .INIT(16'h0001)) 
    \SI_VALUE[5]_i_1 
       (.I0(\SI_VALUE_reg[34] [2]),
        .I1(\SI_VALUE_reg[209] ),
        .I2(\SI_VALUE_reg[34] [3]),
        .I3(\SI_VALUE[141]_i_2_n_0 ),
        .O(SI_VALUE0[5]));
  (* SOFT_HLUTNM = "soft_lutpair33" *) 
  LUT5 #(
    .INIT(32'h00000001)) 
    \SI_VALUE[6]_i_1 
       (.I0(\SI_VALUE_reg[34] [2]),
        .I1(\SI_VALUE_reg[209] ),
        .I2(\SI_VALUE_reg[209]_0 ),
        .I3(\SI_VALUE_reg[34] [3]),
        .I4(\SI_VALUE[142]_i_2_n_0 ),
        .O(SI_VALUE0[6]));
  (* SOFT_HLUTNM = "soft_lutpair33" *) 
  LUT5 #(
    .INIT(32'h00004A15)) 
    \SI_VALUE[70]_i_1 
       (.I0(\SI_VALUE_reg[34] [2]),
        .I1(\SI_VALUE_reg[209] ),
        .I2(\SI_VALUE_reg[209]_0 ),
        .I3(\SI_VALUE_reg[34] [3]),
        .I4(\SI_VALUE[142]_i_2_n_0 ),
        .O(SI_VALUE0[38]));
  (* SOFT_HLUTNM = "soft_lutpair32" *) 
  LUT5 #(
    .INIT(32'h00004A15)) 
    \SI_VALUE[71]_i_1 
       (.I0(\SI_VALUE_reg[34] [2]),
        .I1(\SI_VALUE_reg[209] ),
        .I2(\SI_VALUE_reg[209]_0 ),
        .I3(\SI_VALUE_reg[34] [3]),
        .I4(\SI_VALUE[175]_i_2_n_0 ),
        .O(SI_VALUE0[39]));
  (* SOFT_HLUTNM = "soft_lutpair35" *) 
  LUT5 #(
    .INIT(32'h00002295)) 
    \SI_VALUE[72]_i_1 
       (.I0(\SI_VALUE_reg[34] [3]),
        .I1(\SI_VALUE_reg[209]_0 ),
        .I2(\SI_VALUE_reg[209] ),
        .I3(\SI_VALUE_reg[34] [2]),
        .I4(\SI_VALUE[176]_i_2_n_0 ),
        .O(SI_VALUE0[40]));
  LUT6 #(
    .INIT(64'h414110004D4DD333)) 
    \SI_VALUE[73]_i_1 
       (.I0(\SI_VALUE[105]_i_2_n_0 ),
        .I1(\SI_VALUE_reg[34] [3]),
        .I2(\SI_VALUE_reg[209]_0 ),
        .I3(\SI_VALUE_reg[209] ),
        .I4(\SI_VALUE_reg[34] [2]),
        .I5(\SI_VALUE[177]_i_2_n_0 ),
        .O(SI_VALUE0[41]));
  LUT6 #(
    .INIT(64'h414110004D4DD333)) 
    \SI_VALUE[74]_i_1 
       (.I0(\SI_VALUE[106]_i_2_n_0 ),
        .I1(\SI_VALUE_reg[34] [3]),
        .I2(\SI_VALUE_reg[209]_0 ),
        .I3(\SI_VALUE_reg[209] ),
        .I4(\SI_VALUE_reg[34] [2]),
        .I5(\SI_VALUE[106]_i_3_n_0 ),
        .O(SI_VALUE0[42]));
  LUT6 #(
    .INIT(64'h414110004D4DD333)) 
    \SI_VALUE[75]_i_1 
       (.I0(\SI_VALUE[211]_i_2_n_0 ),
        .I1(\SI_VALUE_reg[34] [3]),
        .I2(\SI_VALUE_reg[209]_0 ),
        .I3(\SI_VALUE_reg[209] ),
        .I4(\SI_VALUE_reg[34] [2]),
        .I5(\SI_VALUE[107]_i_2_n_0 ),
        .O(SI_VALUE0[43]));
  (* SOFT_HLUTNM = "soft_lutpair32" *) 
  LUT5 #(
    .INIT(32'h00000001)) 
    \SI_VALUE[7]_i_1 
       (.I0(\SI_VALUE_reg[34] [2]),
        .I1(\SI_VALUE_reg[209] ),
        .I2(\SI_VALUE_reg[209]_0 ),
        .I3(\SI_VALUE_reg[34] [3]),
        .I4(\SI_VALUE[175]_i_2_n_0 ),
        .O(SI_VALUE0[7]));
  (* SOFT_HLUTNM = "soft_lutpair35" *) 
  LUT5 #(
    .INIT(32'h00000001)) 
    \SI_VALUE[8]_i_1 
       (.I0(\SI_VALUE_reg[34] [3]),
        .I1(\SI_VALUE_reg[209]_0 ),
        .I2(\SI_VALUE_reg[209] ),
        .I3(\SI_VALUE_reg[34] [2]),
        .I4(\SI_VALUE[176]_i_2_n_0 ),
        .O(SI_VALUE0[8]));
  LUT6 #(
    .INIT(64'h4000000040000003)) 
    \SI_VALUE[9]_i_1 
       (.I0(\SI_VALUE[105]_i_2_n_0 ),
        .I1(\SI_VALUE_reg[34] [3]),
        .I2(\SI_VALUE_reg[209]_0 ),
        .I3(\SI_VALUE_reg[209] ),
        .I4(\SI_VALUE_reg[34] [2]),
        .I5(\SI_VALUE[177]_i_2_n_0 ),
        .O(SI_VALUE0[9]));
  (* KEEP_HIERARCHY = "yes" *) 
  DSP48E2 #(
    .ACASCREG(1),
    .ADREG(1),
    .ALUMODEREG(0),
    .AMULTSEL("AD"),
    .AREG(1),
    .AUTORESET_PATDET("NO_RESET"),
    .AUTORESET_PRIORITY("RESET"),
    .A_INPUT("DIRECT"),
    .BCASCREG(2),
    .BMULTSEL("B"),
    .BREG(2),
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
    S_MULT_reg
       (.A({DSP_ALU_INST[15],DSP_ALU_INST[15],DSP_ALU_INST[15],DSP_ALU_INST[15],DSP_ALU_INST[15],DSP_ALU_INST[15],DSP_ALU_INST[15],DSP_ALU_INST[15],DSP_ALU_INST[15],DSP_ALU_INST[15],DSP_ALU_INST[15],DSP_ALU_INST[15],DSP_ALU_INST[15],DSP_ALU_INST[15],DSP_ALU_INST}),
        .ACIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .ACOUT(NLW_S_MULT_reg_ACOUT_UNCONNECTED[29:0]),
        .ALUMODE({1'b0,1'b0,1'b0,1'b0}),
        .B({S_MULT_reg_i_2_n_0,S_MULT_reg_i_3_n_0,S_MULT_reg_i_4_n_0,S_MULT_reg_i_5_n_0,S_MULT_reg_i_6_n_0,S_MULT_reg_i_7_n_0,S_MULT_reg_i_8_n_0,S_MULT_reg_i_9_n_0,S_MULT_reg_i_10_n_0,S_MULT_reg_i_11_n_0,S_MULT_reg_i_12_n_0,S_MULT_reg_i_13_n_0,S_MULT_reg_i_14_n_0,S_MULT_reg_i_15_n_0,S_MULT_reg_i_16_n_0,S_MULT_reg_i_17_n_0,S_MULT_reg_i_18_n_0,S_MULT_reg_i_19_n_0}),
        .BCIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .BCOUT(NLW_S_MULT_reg_BCOUT_UNCONNECTED[17:0]),
        .C({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .CARRYCASCIN(1'b0),
        .CARRYCASCOUT(NLW_S_MULT_reg_CARRYCASCOUT_UNCONNECTED),
        .CARRYIN(1'b0),
        .CARRYINSEL({1'b0,1'b0,1'b0}),
        .CARRYOUT(NLW_S_MULT_reg_CARRYOUT_UNCONNECTED[3:0]),
        .CEA1(1'b0),
        .CEA2(CEP),
        .CEAD(CEP),
        .CEALUMODE(1'b0),
        .CEB1(S_MULT_reg_i_1_n_0),
        .CEB2(CEP),
        .CEC(1'b0),
        .CECARRYIN(1'b0),
        .CECTRL(1'b0),
        .CED(CEP),
        .CEINMODE(1'b0),
        .CEM(1'b0),
        .CEP(CEP),
        .CLK(s00_axi_aclk),
        .D({Q[15],Q[15],Q[15],Q[15],Q[15],Q[15],Q[15],Q[15],Q[15],Q[15],Q[15],Q}),
        .INMODE({1'b0,1'b0,1'b1,1'b0,1'b0}),
        .MULTSIGNIN(1'b0),
        .MULTSIGNOUT(NLW_S_MULT_reg_MULTSIGNOUT_UNCONNECTED),
        .OPMODE({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b1,1'b0,1'b1}),
        .OVERFLOW(NLW_S_MULT_reg_OVERFLOW_UNCONNECTED),
        .P({NLW_S_MULT_reg_P_UNCONNECTED[47:35],S_RESULT_S_C[34],P,S_RESULT_S_C[32:0]}),
        .PATTERNBDETECT(NLW_S_MULT_reg_PATTERNBDETECT_UNCONNECTED),
        .PATTERNDETECT(NLW_S_MULT_reg_PATTERNDETECT_UNCONNECTED),
        .PCIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .PCOUT(NLW_S_MULT_reg_PCOUT_UNCONNECTED[47:0]),
        .RSTA(RSTP),
        .RSTALLCARRYIN(1'b0),
        .RSTALUMODE(1'b0),
        .RSTB(RSTP),
        .RSTC(1'b0),
        .RSTCTRL(1'b0),
        .RSTD(RSTP),
        .RSTINMODE(1'b0),
        .RSTM(1'b0),
        .RSTP(RSTP),
        .UNDERFLOW(NLW_S_MULT_reg_UNDERFLOW_UNCONNECTED),
        .XOROUT(NLW_S_MULT_reg_XOROUT_UNCONNECTED[7:0]));
  LUT6 #(
    .INIT(64'h0000000011111114)) 
    S_MULT_reg_i_1
       (.I0(\S_ENABLE_reg[0] ),
        .I1(DSP_A_B_DATA_INST[3]),
        .I2(DSP_A_B_DATA_INST[2]),
        .I3(DSP_A_B_DATA_INST[1]),
        .I4(DSP_A_B_DATA_INST[0]),
        .I5(\S_ENABLE_reg[0]_0 ),
        .O(S_MULT_reg_i_1_n_0));
  LUT6 #(
    .INIT(64'h8F808F8F8F808080)) 
    S_MULT_reg_i_10
       (.I0(DSP_A_B_DATA_INST_0[135]),
        .I1(\S_CONV_COUNTER_reg[0] ),
        .I2(DSP_A_B_DATA_INST[3]),
        .I3(S_MULT_reg_i_37_n_0),
        .I4(DSP_A_B_DATA_INST[2]),
        .I5(S_MULT_reg_i_38_n_0),
        .O(S_MULT_reg_i_10_n_0));
  LUT6 #(
    .INIT(64'h8F808F8F8F808080)) 
    S_MULT_reg_i_11
       (.I0(DSP_A_B_DATA_INST_0[134]),
        .I1(\S_CONV_COUNTER_reg[0] ),
        .I2(DSP_A_B_DATA_INST[3]),
        .I3(S_MULT_reg_i_39_n_0),
        .I4(DSP_A_B_DATA_INST[2]),
        .I5(S_MULT_reg_i_40_n_0),
        .O(S_MULT_reg_i_11_n_0));
  LUT6 #(
    .INIT(64'h8F808F8F8F808080)) 
    S_MULT_reg_i_12
       (.I0(DSP_A_B_DATA_INST_0[133]),
        .I1(\S_CONV_COUNTER_reg[0] ),
        .I2(DSP_A_B_DATA_INST[3]),
        .I3(S_MULT_reg_i_41_n_0),
        .I4(DSP_A_B_DATA_INST[2]),
        .I5(S_MULT_reg_i_42_n_0),
        .O(S_MULT_reg_i_12_n_0));
  LUT6 #(
    .INIT(64'h8F808F8F8F808080)) 
    S_MULT_reg_i_13
       (.I0(DSP_A_B_DATA_INST_0[132]),
        .I1(\S_CONV_COUNTER_reg[0] ),
        .I2(DSP_A_B_DATA_INST[3]),
        .I3(S_MULT_reg_i_43_n_0),
        .I4(DSP_A_B_DATA_INST[2]),
        .I5(S_MULT_reg_i_44_n_0),
        .O(S_MULT_reg_i_13_n_0));
  LUT6 #(
    .INIT(64'h8F808F8F8F808080)) 
    S_MULT_reg_i_14
       (.I0(DSP_A_B_DATA_INST_0[131]),
        .I1(\S_CONV_COUNTER_reg[0] ),
        .I2(DSP_A_B_DATA_INST[3]),
        .I3(S_MULT_reg_i_45_n_0),
        .I4(DSP_A_B_DATA_INST[2]),
        .I5(S_MULT_reg_i_46_n_0),
        .O(S_MULT_reg_i_14_n_0));
  LUT6 #(
    .INIT(64'h8F808F8F8F808080)) 
    S_MULT_reg_i_15
       (.I0(DSP_A_B_DATA_INST_0[130]),
        .I1(\S_CONV_COUNTER_reg[0] ),
        .I2(DSP_A_B_DATA_INST[3]),
        .I3(S_MULT_reg_i_47_n_0),
        .I4(DSP_A_B_DATA_INST[2]),
        .I5(S_MULT_reg_i_48_n_0),
        .O(S_MULT_reg_i_15_n_0));
  LUT6 #(
    .INIT(64'h8F808F8F8F808080)) 
    S_MULT_reg_i_16
       (.I0(DSP_A_B_DATA_INST_0[129]),
        .I1(\S_CONV_COUNTER_reg[0] ),
        .I2(DSP_A_B_DATA_INST[3]),
        .I3(S_MULT_reg_i_49_n_0),
        .I4(DSP_A_B_DATA_INST[2]),
        .I5(S_MULT_reg_i_50_n_0),
        .O(S_MULT_reg_i_16_n_0));
  LUT6 #(
    .INIT(64'h8F808F8F8F808080)) 
    S_MULT_reg_i_17
       (.I0(DSP_A_B_DATA_INST_0[128]),
        .I1(\S_CONV_COUNTER_reg[0] ),
        .I2(DSP_A_B_DATA_INST[3]),
        .I3(S_MULT_reg_i_51_n_0),
        .I4(DSP_A_B_DATA_INST[2]),
        .I5(S_MULT_reg_i_52_n_0),
        .O(S_MULT_reg_i_17_n_0));
  LUT6 #(
    .INIT(64'h8F808F8F8F808080)) 
    S_MULT_reg_i_18
       (.I0(DSP_A_B_DATA_INST_0[127]),
        .I1(\S_CONV_COUNTER_reg[0] ),
        .I2(DSP_A_B_DATA_INST[3]),
        .I3(S_MULT_reg_i_53_n_0),
        .I4(DSP_A_B_DATA_INST[2]),
        .I5(S_MULT_reg_i_54_n_0),
        .O(S_MULT_reg_i_18_n_0));
  LUT6 #(
    .INIT(64'h8F808F8F8F808080)) 
    S_MULT_reg_i_19
       (.I0(DSP_A_B_DATA_INST_0[126]),
        .I1(\S_CONV_COUNTER_reg[0] ),
        .I2(DSP_A_B_DATA_INST[3]),
        .I3(S_MULT_reg_i_55_n_0),
        .I4(DSP_A_B_DATA_INST[2]),
        .I5(S_MULT_reg_i_56_n_0),
        .O(S_MULT_reg_i_19_n_0));
  LUT6 #(
    .INIT(64'h8F808F8F8F808080)) 
    S_MULT_reg_i_2
       (.I0(DSP_A_B_DATA_INST_0[143]),
        .I1(\S_CONV_COUNTER_reg[0] ),
        .I2(DSP_A_B_DATA_INST[3]),
        .I3(S_MULT_reg_i_21_n_0),
        .I4(DSP_A_B_DATA_INST[2]),
        .I5(S_MULT_reg_i_22_n_0),
        .O(S_MULT_reg_i_2_n_0));
  LUT3 #(
    .INIT(8'h01)) 
    S_MULT_reg_i_20
       (.I0(DSP_A_B_DATA_INST[0]),
        .I1(DSP_A_B_DATA_INST[1]),
        .I2(DSP_A_B_DATA_INST[2]),
        .O(\S_CONV_COUNTER_reg[0] ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    S_MULT_reg_i_21
       (.I0(DSP_A_B_DATA_INST_0[125]),
        .I1(DSP_A_B_DATA_INST_0[107]),
        .I2(DSP_A_B_DATA_INST[1]),
        .I3(DSP_A_B_DATA_INST_0[89]),
        .I4(DSP_A_B_DATA_INST[0]),
        .I5(DSP_A_B_DATA_INST_0[71]),
        .O(S_MULT_reg_i_21_n_0));
  LUT5 #(
    .INIT(32'hAFC0A0C0)) 
    S_MULT_reg_i_22
       (.I0(DSP_A_B_DATA_INST_0[53]),
        .I1(DSP_A_B_DATA_INST_0[35]),
        .I2(DSP_A_B_DATA_INST[1]),
        .I3(DSP_A_B_DATA_INST[0]),
        .I4(DSP_A_B_DATA_INST_0[17]),
        .O(S_MULT_reg_i_22_n_0));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    S_MULT_reg_i_23
       (.I0(DSP_A_B_DATA_INST_0[124]),
        .I1(DSP_A_B_DATA_INST_0[106]),
        .I2(DSP_A_B_DATA_INST[1]),
        .I3(DSP_A_B_DATA_INST_0[88]),
        .I4(DSP_A_B_DATA_INST[0]),
        .I5(DSP_A_B_DATA_INST_0[70]),
        .O(S_MULT_reg_i_23_n_0));
  LUT5 #(
    .INIT(32'hAFC0A0C0)) 
    S_MULT_reg_i_24
       (.I0(DSP_A_B_DATA_INST_0[52]),
        .I1(DSP_A_B_DATA_INST_0[34]),
        .I2(DSP_A_B_DATA_INST[1]),
        .I3(DSP_A_B_DATA_INST[0]),
        .I4(DSP_A_B_DATA_INST_0[16]),
        .O(S_MULT_reg_i_24_n_0));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    S_MULT_reg_i_25
       (.I0(DSP_A_B_DATA_INST_0[123]),
        .I1(DSP_A_B_DATA_INST_0[105]),
        .I2(DSP_A_B_DATA_INST[1]),
        .I3(DSP_A_B_DATA_INST_0[87]),
        .I4(DSP_A_B_DATA_INST[0]),
        .I5(DSP_A_B_DATA_INST_0[69]),
        .O(S_MULT_reg_i_25_n_0));
  LUT5 #(
    .INIT(32'hAFC0A0C0)) 
    S_MULT_reg_i_26
       (.I0(DSP_A_B_DATA_INST_0[51]),
        .I1(DSP_A_B_DATA_INST_0[33]),
        .I2(DSP_A_B_DATA_INST[1]),
        .I3(DSP_A_B_DATA_INST[0]),
        .I4(DSP_A_B_DATA_INST_0[15]),
        .O(S_MULT_reg_i_26_n_0));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    S_MULT_reg_i_27
       (.I0(DSP_A_B_DATA_INST_0[122]),
        .I1(DSP_A_B_DATA_INST_0[104]),
        .I2(DSP_A_B_DATA_INST[1]),
        .I3(DSP_A_B_DATA_INST_0[86]),
        .I4(DSP_A_B_DATA_INST[0]),
        .I5(DSP_A_B_DATA_INST_0[68]),
        .O(S_MULT_reg_i_27_n_0));
  LUT5 #(
    .INIT(32'hAFC0A0C0)) 
    S_MULT_reg_i_28
       (.I0(DSP_A_B_DATA_INST_0[50]),
        .I1(DSP_A_B_DATA_INST_0[32]),
        .I2(DSP_A_B_DATA_INST[1]),
        .I3(DSP_A_B_DATA_INST[0]),
        .I4(DSP_A_B_DATA_INST_0[14]),
        .O(S_MULT_reg_i_28_n_0));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    S_MULT_reg_i_29
       (.I0(DSP_A_B_DATA_INST_0[121]),
        .I1(DSP_A_B_DATA_INST_0[103]),
        .I2(DSP_A_B_DATA_INST[1]),
        .I3(DSP_A_B_DATA_INST_0[85]),
        .I4(DSP_A_B_DATA_INST[0]),
        .I5(DSP_A_B_DATA_INST_0[67]),
        .O(S_MULT_reg_i_29_n_0));
  LUT6 #(
    .INIT(64'h8F808F8F8F808080)) 
    S_MULT_reg_i_3
       (.I0(DSP_A_B_DATA_INST_0[142]),
        .I1(\S_CONV_COUNTER_reg[0] ),
        .I2(DSP_A_B_DATA_INST[3]),
        .I3(S_MULT_reg_i_23_n_0),
        .I4(DSP_A_B_DATA_INST[2]),
        .I5(S_MULT_reg_i_24_n_0),
        .O(S_MULT_reg_i_3_n_0));
  LUT5 #(
    .INIT(32'hAFC0A0C0)) 
    S_MULT_reg_i_30
       (.I0(DSP_A_B_DATA_INST_0[49]),
        .I1(DSP_A_B_DATA_INST_0[31]),
        .I2(DSP_A_B_DATA_INST[1]),
        .I3(DSP_A_B_DATA_INST[0]),
        .I4(DSP_A_B_DATA_INST_0[13]),
        .O(S_MULT_reg_i_30_n_0));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    S_MULT_reg_i_31
       (.I0(DSP_A_B_DATA_INST_0[120]),
        .I1(DSP_A_B_DATA_INST_0[102]),
        .I2(DSP_A_B_DATA_INST[1]),
        .I3(DSP_A_B_DATA_INST_0[84]),
        .I4(DSP_A_B_DATA_INST[0]),
        .I5(DSP_A_B_DATA_INST_0[66]),
        .O(S_MULT_reg_i_31_n_0));
  LUT5 #(
    .INIT(32'hAFC0A0C0)) 
    S_MULT_reg_i_32
       (.I0(DSP_A_B_DATA_INST_0[48]),
        .I1(DSP_A_B_DATA_INST_0[30]),
        .I2(DSP_A_B_DATA_INST[1]),
        .I3(DSP_A_B_DATA_INST[0]),
        .I4(DSP_A_B_DATA_INST_0[12]),
        .O(S_MULT_reg_i_32_n_0));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    S_MULT_reg_i_33
       (.I0(DSP_A_B_DATA_INST_0[119]),
        .I1(DSP_A_B_DATA_INST_0[101]),
        .I2(DSP_A_B_DATA_INST[1]),
        .I3(DSP_A_B_DATA_INST_0[83]),
        .I4(DSP_A_B_DATA_INST[0]),
        .I5(DSP_A_B_DATA_INST_0[65]),
        .O(S_MULT_reg_i_33_n_0));
  LUT5 #(
    .INIT(32'hAFC0A0C0)) 
    S_MULT_reg_i_34
       (.I0(DSP_A_B_DATA_INST_0[47]),
        .I1(DSP_A_B_DATA_INST_0[29]),
        .I2(DSP_A_B_DATA_INST[1]),
        .I3(DSP_A_B_DATA_INST[0]),
        .I4(DSP_A_B_DATA_INST_0[11]),
        .O(S_MULT_reg_i_34_n_0));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    S_MULT_reg_i_35
       (.I0(DSP_A_B_DATA_INST_0[118]),
        .I1(DSP_A_B_DATA_INST_0[100]),
        .I2(DSP_A_B_DATA_INST[1]),
        .I3(DSP_A_B_DATA_INST_0[82]),
        .I4(DSP_A_B_DATA_INST[0]),
        .I5(DSP_A_B_DATA_INST_0[64]),
        .O(S_MULT_reg_i_35_n_0));
  LUT5 #(
    .INIT(32'hAFC0A0C0)) 
    S_MULT_reg_i_36
       (.I0(DSP_A_B_DATA_INST_0[46]),
        .I1(DSP_A_B_DATA_INST_0[28]),
        .I2(DSP_A_B_DATA_INST[1]),
        .I3(DSP_A_B_DATA_INST[0]),
        .I4(DSP_A_B_DATA_INST_0[10]),
        .O(S_MULT_reg_i_36_n_0));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    S_MULT_reg_i_37
       (.I0(DSP_A_B_DATA_INST_0[117]),
        .I1(DSP_A_B_DATA_INST_0[99]),
        .I2(DSP_A_B_DATA_INST[1]),
        .I3(DSP_A_B_DATA_INST_0[81]),
        .I4(DSP_A_B_DATA_INST[0]),
        .I5(DSP_A_B_DATA_INST_0[63]),
        .O(S_MULT_reg_i_37_n_0));
  LUT5 #(
    .INIT(32'hAFC0A0C0)) 
    S_MULT_reg_i_38
       (.I0(DSP_A_B_DATA_INST_0[45]),
        .I1(DSP_A_B_DATA_INST_0[27]),
        .I2(DSP_A_B_DATA_INST[1]),
        .I3(DSP_A_B_DATA_INST[0]),
        .I4(DSP_A_B_DATA_INST_0[9]),
        .O(S_MULT_reg_i_38_n_0));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    S_MULT_reg_i_39
       (.I0(DSP_A_B_DATA_INST_0[116]),
        .I1(DSP_A_B_DATA_INST_0[98]),
        .I2(DSP_A_B_DATA_INST[1]),
        .I3(DSP_A_B_DATA_INST_0[80]),
        .I4(DSP_A_B_DATA_INST[0]),
        .I5(DSP_A_B_DATA_INST_0[62]),
        .O(S_MULT_reg_i_39_n_0));
  LUT6 #(
    .INIT(64'h8F808F8F8F808080)) 
    S_MULT_reg_i_4
       (.I0(DSP_A_B_DATA_INST_0[141]),
        .I1(\S_CONV_COUNTER_reg[0] ),
        .I2(DSP_A_B_DATA_INST[3]),
        .I3(S_MULT_reg_i_25_n_0),
        .I4(DSP_A_B_DATA_INST[2]),
        .I5(S_MULT_reg_i_26_n_0),
        .O(S_MULT_reg_i_4_n_0));
  LUT5 #(
    .INIT(32'hAFC0A0C0)) 
    S_MULT_reg_i_40
       (.I0(DSP_A_B_DATA_INST_0[44]),
        .I1(DSP_A_B_DATA_INST_0[26]),
        .I2(DSP_A_B_DATA_INST[1]),
        .I3(DSP_A_B_DATA_INST[0]),
        .I4(DSP_A_B_DATA_INST_0[8]),
        .O(S_MULT_reg_i_40_n_0));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    S_MULT_reg_i_41
       (.I0(DSP_A_B_DATA_INST_0[115]),
        .I1(DSP_A_B_DATA_INST_0[97]),
        .I2(DSP_A_B_DATA_INST[1]),
        .I3(DSP_A_B_DATA_INST_0[79]),
        .I4(DSP_A_B_DATA_INST[0]),
        .I5(DSP_A_B_DATA_INST_0[61]),
        .O(S_MULT_reg_i_41_n_0));
  LUT5 #(
    .INIT(32'hAFC0A0C0)) 
    S_MULT_reg_i_42
       (.I0(DSP_A_B_DATA_INST_0[43]),
        .I1(DSP_A_B_DATA_INST_0[25]),
        .I2(DSP_A_B_DATA_INST[1]),
        .I3(DSP_A_B_DATA_INST[0]),
        .I4(DSP_A_B_DATA_INST_0[7]),
        .O(S_MULT_reg_i_42_n_0));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    S_MULT_reg_i_43
       (.I0(DSP_A_B_DATA_INST_0[114]),
        .I1(DSP_A_B_DATA_INST_0[96]),
        .I2(DSP_A_B_DATA_INST[1]),
        .I3(DSP_A_B_DATA_INST_0[78]),
        .I4(DSP_A_B_DATA_INST[0]),
        .I5(DSP_A_B_DATA_INST_0[60]),
        .O(S_MULT_reg_i_43_n_0));
  LUT5 #(
    .INIT(32'hAFC0A0C0)) 
    S_MULT_reg_i_44
       (.I0(DSP_A_B_DATA_INST_0[42]),
        .I1(DSP_A_B_DATA_INST_0[24]),
        .I2(DSP_A_B_DATA_INST[1]),
        .I3(DSP_A_B_DATA_INST[0]),
        .I4(DSP_A_B_DATA_INST_0[6]),
        .O(S_MULT_reg_i_44_n_0));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    S_MULT_reg_i_45
       (.I0(DSP_A_B_DATA_INST_0[113]),
        .I1(DSP_A_B_DATA_INST_0[95]),
        .I2(DSP_A_B_DATA_INST[1]),
        .I3(DSP_A_B_DATA_INST_0[77]),
        .I4(DSP_A_B_DATA_INST[0]),
        .I5(DSP_A_B_DATA_INST_0[59]),
        .O(S_MULT_reg_i_45_n_0));
  LUT5 #(
    .INIT(32'hAFC0A0C0)) 
    S_MULT_reg_i_46
       (.I0(DSP_A_B_DATA_INST_0[41]),
        .I1(DSP_A_B_DATA_INST_0[23]),
        .I2(DSP_A_B_DATA_INST[1]),
        .I3(DSP_A_B_DATA_INST[0]),
        .I4(DSP_A_B_DATA_INST_0[5]),
        .O(S_MULT_reg_i_46_n_0));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    S_MULT_reg_i_47
       (.I0(DSP_A_B_DATA_INST_0[112]),
        .I1(DSP_A_B_DATA_INST_0[94]),
        .I2(DSP_A_B_DATA_INST[1]),
        .I3(DSP_A_B_DATA_INST_0[76]),
        .I4(DSP_A_B_DATA_INST[0]),
        .I5(DSP_A_B_DATA_INST_0[58]),
        .O(S_MULT_reg_i_47_n_0));
  LUT5 #(
    .INIT(32'hAFC0A0C0)) 
    S_MULT_reg_i_48
       (.I0(DSP_A_B_DATA_INST_0[40]),
        .I1(DSP_A_B_DATA_INST_0[22]),
        .I2(DSP_A_B_DATA_INST[1]),
        .I3(DSP_A_B_DATA_INST[0]),
        .I4(DSP_A_B_DATA_INST_0[4]),
        .O(S_MULT_reg_i_48_n_0));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    S_MULT_reg_i_49
       (.I0(DSP_A_B_DATA_INST_0[111]),
        .I1(DSP_A_B_DATA_INST_0[93]),
        .I2(DSP_A_B_DATA_INST[1]),
        .I3(DSP_A_B_DATA_INST_0[75]),
        .I4(DSP_A_B_DATA_INST[0]),
        .I5(DSP_A_B_DATA_INST_0[57]),
        .O(S_MULT_reg_i_49_n_0));
  LUT6 #(
    .INIT(64'h8F808F8F8F808080)) 
    S_MULT_reg_i_5
       (.I0(DSP_A_B_DATA_INST_0[140]),
        .I1(\S_CONV_COUNTER_reg[0] ),
        .I2(DSP_A_B_DATA_INST[3]),
        .I3(S_MULT_reg_i_27_n_0),
        .I4(DSP_A_B_DATA_INST[2]),
        .I5(S_MULT_reg_i_28_n_0),
        .O(S_MULT_reg_i_5_n_0));
  LUT5 #(
    .INIT(32'hAFC0A0C0)) 
    S_MULT_reg_i_50
       (.I0(DSP_A_B_DATA_INST_0[39]),
        .I1(DSP_A_B_DATA_INST_0[21]),
        .I2(DSP_A_B_DATA_INST[1]),
        .I3(DSP_A_B_DATA_INST[0]),
        .I4(DSP_A_B_DATA_INST_0[3]),
        .O(S_MULT_reg_i_50_n_0));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    S_MULT_reg_i_51
       (.I0(DSP_A_B_DATA_INST_0[110]),
        .I1(DSP_A_B_DATA_INST_0[92]),
        .I2(DSP_A_B_DATA_INST[1]),
        .I3(DSP_A_B_DATA_INST_0[74]),
        .I4(DSP_A_B_DATA_INST[0]),
        .I5(DSP_A_B_DATA_INST_0[56]),
        .O(S_MULT_reg_i_51_n_0));
  LUT5 #(
    .INIT(32'hAFC0A0C0)) 
    S_MULT_reg_i_52
       (.I0(DSP_A_B_DATA_INST_0[38]),
        .I1(DSP_A_B_DATA_INST_0[20]),
        .I2(DSP_A_B_DATA_INST[1]),
        .I3(DSP_A_B_DATA_INST[0]),
        .I4(DSP_A_B_DATA_INST_0[2]),
        .O(S_MULT_reg_i_52_n_0));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    S_MULT_reg_i_53
       (.I0(DSP_A_B_DATA_INST_0[109]),
        .I1(DSP_A_B_DATA_INST_0[91]),
        .I2(DSP_A_B_DATA_INST[1]),
        .I3(DSP_A_B_DATA_INST_0[73]),
        .I4(DSP_A_B_DATA_INST[0]),
        .I5(DSP_A_B_DATA_INST_0[55]),
        .O(S_MULT_reg_i_53_n_0));
  LUT5 #(
    .INIT(32'hAFC0A0C0)) 
    S_MULT_reg_i_54
       (.I0(DSP_A_B_DATA_INST_0[37]),
        .I1(DSP_A_B_DATA_INST_0[19]),
        .I2(DSP_A_B_DATA_INST[1]),
        .I3(DSP_A_B_DATA_INST[0]),
        .I4(DSP_A_B_DATA_INST_0[1]),
        .O(S_MULT_reg_i_54_n_0));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    S_MULT_reg_i_55
       (.I0(DSP_A_B_DATA_INST_0[108]),
        .I1(DSP_A_B_DATA_INST_0[90]),
        .I2(DSP_A_B_DATA_INST[1]),
        .I3(DSP_A_B_DATA_INST_0[72]),
        .I4(DSP_A_B_DATA_INST[0]),
        .I5(DSP_A_B_DATA_INST_0[54]),
        .O(S_MULT_reg_i_55_n_0));
  LUT5 #(
    .INIT(32'hAFC0A0C0)) 
    S_MULT_reg_i_56
       (.I0(DSP_A_B_DATA_INST_0[36]),
        .I1(DSP_A_B_DATA_INST_0[18]),
        .I2(DSP_A_B_DATA_INST[1]),
        .I3(DSP_A_B_DATA_INST[0]),
        .I4(DSP_A_B_DATA_INST_0[0]),
        .O(S_MULT_reg_i_56_n_0));
  LUT6 #(
    .INIT(64'h8F808F8F8F808080)) 
    S_MULT_reg_i_6
       (.I0(DSP_A_B_DATA_INST_0[139]),
        .I1(\S_CONV_COUNTER_reg[0] ),
        .I2(DSP_A_B_DATA_INST[3]),
        .I3(S_MULT_reg_i_29_n_0),
        .I4(DSP_A_B_DATA_INST[2]),
        .I5(S_MULT_reg_i_30_n_0),
        .O(S_MULT_reg_i_6_n_0));
  LUT6 #(
    .INIT(64'h8F808F8F8F808080)) 
    S_MULT_reg_i_7
       (.I0(DSP_A_B_DATA_INST_0[138]),
        .I1(\S_CONV_COUNTER_reg[0] ),
        .I2(DSP_A_B_DATA_INST[3]),
        .I3(S_MULT_reg_i_31_n_0),
        .I4(DSP_A_B_DATA_INST[2]),
        .I5(S_MULT_reg_i_32_n_0),
        .O(S_MULT_reg_i_7_n_0));
  LUT6 #(
    .INIT(64'h8F808F8F8F808080)) 
    S_MULT_reg_i_8
       (.I0(DSP_A_B_DATA_INST_0[137]),
        .I1(\S_CONV_COUNTER_reg[0] ),
        .I2(DSP_A_B_DATA_INST[3]),
        .I3(S_MULT_reg_i_33_n_0),
        .I4(DSP_A_B_DATA_INST[2]),
        .I5(S_MULT_reg_i_34_n_0),
        .O(S_MULT_reg_i_8_n_0));
  LUT6 #(
    .INIT(64'h8F808F8F8F808080)) 
    S_MULT_reg_i_9
       (.I0(DSP_A_B_DATA_INST_0[136]),
        .I1(\S_CONV_COUNTER_reg[0] ),
        .I2(DSP_A_B_DATA_INST[3]),
        .I3(S_MULT_reg_i_35_n_0),
        .I4(DSP_A_B_DATA_INST[2]),
        .I5(S_MULT_reg_i_36_n_0),
        .O(S_MULT_reg_i_9_n_0));
endmodule

(* ORIG_REF_NAME = "SPI_MASTER" *) 
module zusys_A3_ADC_LTC2311_0_SPI_MASTER
   (S_SCLK,
    SS_N,
    S_SPI_BUSY,
    E,
    D,
    \S_RX_OUT_BUFFER_reg[127]_0 ,
    RAW_VALUE,
    CPHA,
    s00_axi_aclk,
    CPOL,
    S_CPOL_reg_0,
    s00_axi_aresetn,
    \S_BIT_COUNT_reg[0]_0 ,
    S_AXI_ARESETN,
    \S_DEL_COUNT_reg[7]_0 ,
    S_SCLK_reg_0,
    SCLK_IN,
    SS_IN_N,
    \S_SAMPLE_TIME_COUNTER_reg[0] ,
    Q,
    \S_SAMPLE_TIME_COUNTER_reg[0]_0 ,
    \S_SAMPLE_TIME_COUNTER_reg[0]_1 ,
    \S_RAW_VALUE_S_C_reg[0] ,
    \S_RAW_VALUE_S_C_reg[0]_0 ,
    RSTP,
    \S_RX_BUFFER_reg[112]_0 );
  output S_SCLK;
  output [0:0]SS_N;
  output S_SPI_BUSY;
  output [0:0]E;
  output [0:0]D;
  output [15:0]\S_RX_OUT_BUFFER_reg[127]_0 ;
  output [127:0]RAW_VALUE;
  input CPHA;
  input s00_axi_aclk;
  input CPOL;
  input [0:0]S_CPOL_reg_0;
  input s00_axi_aresetn;
  input \S_BIT_COUNT_reg[0]_0 ;
  input S_AXI_ARESETN;
  input [31:0]\S_DEL_COUNT_reg[7]_0 ;
  input S_SCLK_reg_0;
  input SCLK_IN;
  input SS_IN_N;
  input \S_SAMPLE_TIME_COUNTER_reg[0] ;
  input [1:0]Q;
  input \S_SAMPLE_TIME_COUNTER_reg[0]_0 ;
  input \S_SAMPLE_TIME_COUNTER_reg[0]_1 ;
  input \S_RAW_VALUE_S_C_reg[0] ;
  input [3:0]\S_RAW_VALUE_S_C_reg[0]_0 ;
  input RSTP;
  input [7:0]\S_RX_BUFFER_reg[112]_0 ;

  wire BUSY_i_1_n_0;
  wire BUSY_i_2_n_0;
  wire CPHA;
  wire CPOL;
  wire [0:0]D;
  wire [0:0]E;
  wire [1:0]Q;
  wire [127:0]RAW_VALUE;
  wire RSTP;
  wire SCLK_IN;
  wire SS_IN_N;
  wire [0:0]SS_N;
  wire SS_OUT_N1_out;
  wire SS_OUT_N_i_10_n_0;
  wire SS_OUT_N_i_1_n_0;
  wire SS_OUT_N_i_2_n_0;
  wire SS_OUT_N_i_3_n_0;
  wire SS_OUT_N_i_4_n_0;
  wire SS_OUT_N_i_6_n_0;
  wire SS_OUT_N_i_7_n_0;
  wire SS_OUT_N_i_8_n_0;
  wire SS_OUT_N_i_9_n_0;
  wire S_AXI_ARESETN;
  wire [5:0]S_BIT_COUNT;
  wire \S_BIT_COUNT[0]_i_2_n_0 ;
  wire \S_BIT_COUNT[4]_i_2_n_0 ;
  wire \S_BIT_COUNT[4]_i_3_n_0 ;
  wire \S_BIT_COUNT[5]_i_10_n_0 ;
  wire \S_BIT_COUNT[5]_i_11_n_0 ;
  wire \S_BIT_COUNT[5]_i_12_n_0 ;
  wire \S_BIT_COUNT[5]_i_13_n_0 ;
  wire \S_BIT_COUNT[5]_i_14_n_0 ;
  wire \S_BIT_COUNT[5]_i_15_n_0 ;
  wire \S_BIT_COUNT[5]_i_1_n_0 ;
  wire \S_BIT_COUNT[5]_i_3_n_0 ;
  wire \S_BIT_COUNT[5]_i_5_n_0 ;
  wire \S_BIT_COUNT[5]_i_7_n_0 ;
  wire \S_BIT_COUNT[5]_i_8_n_0 ;
  wire \S_BIT_COUNT[5]_i_9_n_0 ;
  wire \S_BIT_COUNT_reg[0]_0 ;
  wire \S_BIT_COUNT_reg[5]_i_6_n_0 ;
  wire \S_BIT_COUNT_reg[5]_i_6_n_1 ;
  wire \S_BIT_COUNT_reg[5]_i_6_n_2 ;
  wire \S_BIT_COUNT_reg[5]_i_6_n_3 ;
  wire \S_BIT_COUNT_reg[5]_i_6_n_4 ;
  wire \S_BIT_COUNT_reg[5]_i_6_n_5 ;
  wire \S_BIT_COUNT_reg[5]_i_6_n_6 ;
  wire \S_BIT_COUNT_reg[5]_i_6_n_7 ;
  wire \S_BIT_COUNT_reg_n_0_[0] ;
  wire \S_BIT_COUNT_reg_n_0_[1] ;
  wire \S_BIT_COUNT_reg_n_0_[2] ;
  wire \S_BIT_COUNT_reg_n_0_[3] ;
  wire \S_BIT_COUNT_reg_n_0_[4] ;
  wire \S_BIT_COUNT_reg_n_0_[5] ;
  wire [15:0]S_CLK_DIV;
  wire S_CPHA;
  wire S_CPHA_reg_n_0;
  wire S_CPOL;
  wire [0:0]S_CPOL_reg_0;
  wire S_CPOL_reg_n_0;
  wire [16:0]S_DEL_CLK;
  wire [16:1]S_DEL_CLK0;
  wire [16:0]S_DEL_CLK1_in;
  wire \S_DEL_CLK[15]_i_2_n_0 ;
  wire \S_DEL_CLK[15]_i_3_n_0 ;
  wire \S_DEL_CLK[15]_i_4_n_0 ;
  wire \S_DEL_CLK[16]_i_10_n_0 ;
  wire \S_DEL_CLK[16]_i_11_n_0 ;
  wire \S_DEL_CLK[16]_i_12_n_0 ;
  wire \S_DEL_CLK[16]_i_13_n_0 ;
  wire \S_DEL_CLK[16]_i_3_n_0 ;
  wire \S_DEL_CLK[16]_i_4_n_0 ;
  wire \S_DEL_CLK[16]_i_6_n_0 ;
  wire \S_DEL_CLK[16]_i_7_n_0 ;
  wire \S_DEL_CLK[16]_i_8_n_0 ;
  wire \S_DEL_CLK[16]_i_9_n_0 ;
  wire \S_DEL_CLK[8]_i_10_n_0 ;
  wire \S_DEL_CLK[8]_i_3_n_0 ;
  wire \S_DEL_CLK[8]_i_4_n_0 ;
  wire \S_DEL_CLK[8]_i_5_n_0 ;
  wire \S_DEL_CLK[8]_i_6_n_0 ;
  wire \S_DEL_CLK[8]_i_7_n_0 ;
  wire \S_DEL_CLK[8]_i_8_n_0 ;
  wire \S_DEL_CLK[8]_i_9_n_0 ;
  wire \S_DEL_CLK_reg[16]_i_5_n_1 ;
  wire \S_DEL_CLK_reg[16]_i_5_n_2 ;
  wire \S_DEL_CLK_reg[16]_i_5_n_3 ;
  wire \S_DEL_CLK_reg[16]_i_5_n_4 ;
  wire \S_DEL_CLK_reg[16]_i_5_n_5 ;
  wire \S_DEL_CLK_reg[16]_i_5_n_6 ;
  wire \S_DEL_CLK_reg[16]_i_5_n_7 ;
  wire \S_DEL_CLK_reg[8]_i_2_n_0 ;
  wire \S_DEL_CLK_reg[8]_i_2_n_1 ;
  wire \S_DEL_CLK_reg[8]_i_2_n_2 ;
  wire \S_DEL_CLK_reg[8]_i_2_n_3 ;
  wire \S_DEL_CLK_reg[8]_i_2_n_4 ;
  wire \S_DEL_CLK_reg[8]_i_2_n_5 ;
  wire \S_DEL_CLK_reg[8]_i_2_n_6 ;
  wire \S_DEL_CLK_reg[8]_i_2_n_7 ;
  wire [8:0]S_DEL_COUNT;
  wire [8:0]S_DEL_COUNT1_in;
  wire \S_DEL_COUNT[1]_i_2_n_0 ;
  wire \S_DEL_COUNT[2]_i_2_n_0 ;
  wire \S_DEL_COUNT[3]_i_2_n_0 ;
  wire \S_DEL_COUNT[4]_i_2_n_0 ;
  wire \S_DEL_COUNT[5]_i_2_n_0 ;
  wire \S_DEL_COUNT[6]_i_2_n_0 ;
  wire \S_DEL_COUNT[6]_i_3_n_0 ;
  wire \S_DEL_COUNT[6]_i_4_n_0 ;
  wire \S_DEL_COUNT[7]_i_2_n_0 ;
  wire \S_DEL_COUNT[7]_i_3_n_0 ;
  wire \S_DEL_COUNT[8]_i_1_n_0 ;
  wire \S_DEL_COUNT[8]_i_3_n_0 ;
  wire \S_DEL_COUNT[8]_i_4_n_0 ;
  wire [31:0]\S_DEL_COUNT_reg[7]_0 ;
  wire [7:0]S_PRE_DELAY;
  wire \S_RAW_VALUE_S_C[0]_i_2_n_0 ;
  wire \S_RAW_VALUE_S_C[0]_i_3_n_0 ;
  wire \S_RAW_VALUE_S_C[10]_i_2_n_0 ;
  wire \S_RAW_VALUE_S_C[10]_i_3_n_0 ;
  wire \S_RAW_VALUE_S_C[11]_i_2_n_0 ;
  wire \S_RAW_VALUE_S_C[11]_i_3_n_0 ;
  wire \S_RAW_VALUE_S_C[12]_i_2_n_0 ;
  wire \S_RAW_VALUE_S_C[12]_i_3_n_0 ;
  wire \S_RAW_VALUE_S_C[13]_i_2_n_0 ;
  wire \S_RAW_VALUE_S_C[13]_i_3_n_0 ;
  wire \S_RAW_VALUE_S_C[14]_i_2_n_0 ;
  wire \S_RAW_VALUE_S_C[14]_i_3_n_0 ;
  wire \S_RAW_VALUE_S_C[15]_i_4_n_0 ;
  wire \S_RAW_VALUE_S_C[15]_i_5_n_0 ;
  wire \S_RAW_VALUE_S_C[1]_i_2_n_0 ;
  wire \S_RAW_VALUE_S_C[1]_i_3_n_0 ;
  wire \S_RAW_VALUE_S_C[2]_i_2_n_0 ;
  wire \S_RAW_VALUE_S_C[2]_i_3_n_0 ;
  wire \S_RAW_VALUE_S_C[3]_i_2_n_0 ;
  wire \S_RAW_VALUE_S_C[3]_i_3_n_0 ;
  wire \S_RAW_VALUE_S_C[4]_i_2_n_0 ;
  wire \S_RAW_VALUE_S_C[4]_i_3_n_0 ;
  wire \S_RAW_VALUE_S_C[5]_i_2_n_0 ;
  wire \S_RAW_VALUE_S_C[5]_i_3_n_0 ;
  wire \S_RAW_VALUE_S_C[6]_i_2_n_0 ;
  wire \S_RAW_VALUE_S_C[6]_i_3_n_0 ;
  wire \S_RAW_VALUE_S_C[7]_i_2_n_0 ;
  wire \S_RAW_VALUE_S_C[7]_i_3_n_0 ;
  wire \S_RAW_VALUE_S_C[8]_i_2_n_0 ;
  wire \S_RAW_VALUE_S_C[8]_i_3_n_0 ;
  wire \S_RAW_VALUE_S_C[9]_i_2_n_0 ;
  wire \S_RAW_VALUE_S_C[9]_i_3_n_0 ;
  wire \S_RAW_VALUE_S_C_reg[0] ;
  wire [3:0]\S_RAW_VALUE_S_C_reg[0]_0 ;
  wire S_RX_BUFFER;
  wire [7:0]\S_RX_BUFFER_reg[112]_0 ;
  wire \S_RX_BUFFER_reg_n_0_[111] ;
  wire \S_RX_BUFFER_reg_n_0_[127] ;
  wire \S_RX_BUFFER_reg_n_0_[15] ;
  wire \S_RX_BUFFER_reg_n_0_[31] ;
  wire \S_RX_BUFFER_reg_n_0_[47] ;
  wire \S_RX_BUFFER_reg_n_0_[63] ;
  wire \S_RX_BUFFER_reg_n_0_[79] ;
  wire \S_RX_BUFFER_reg_n_0_[95] ;
  wire S_RX_OUT_BUFFER;
  wire \S_RX_OUT_BUFFER[127]_i_3_n_0 ;
  wire [15:0]\S_RX_OUT_BUFFER_reg[127]_0 ;
  wire \S_SAMPLE_TIME_COUNTER_reg[0] ;
  wire \S_SAMPLE_TIME_COUNTER_reg[0]_0 ;
  wire \S_SAMPLE_TIME_COUNTER_reg[0]_1 ;
  wire S_SCLK;
  wire S_SCLK_i_1_n_0;
  wire S_SCLK_i_2_n_0;
  wire S_SCLK_i_3_n_0;
  wire S_SCLK_i_4_n_0;
  wire S_SCLK_i_5_n_0;
  wire S_SCLK_i_6_n_0;
  wire S_SCLK_i_7_n_0;
  wire S_SCLK_i_8_n_0;
  wire S_SCLK_i_9_n_0;
  wire S_SCLK_reg_0;
  wire S_SPI_BUSY;
  wire [2:0]curstate;
  wire \curstate[0]_i_2_n_0 ;
  wire \curstate[0]_i_3_n_0 ;
  wire \curstate[0]_i_4_n_0 ;
  wire \curstate[2]_i_2_n_0 ;
  wire [2:0]nxtstate;
  wire nxtstate1;
  wire [127:1]p_0_out;
  wire s00_axi_aclk;
  wire s00_axi_aresetn;
  wire [7:1]\NLW_S_BIT_COUNT_reg[5]_i_4_CO_UNCONNECTED ;
  wire [7:0]\NLW_S_BIT_COUNT_reg[5]_i_4_O_UNCONNECTED ;
  wire [7:0]\NLW_S_BIT_COUNT_reg[5]_i_6_O_UNCONNECTED ;
  wire [7:7]\NLW_S_DEL_CLK_reg[16]_i_5_CO_UNCONNECTED ;

  LUT6 #(
    .INIT(64'hAAAAFBFFAAAA0800)) 
    BUSY_i_1
       (.I0(nxtstate[0]),
        .I1(s00_axi_aresetn),
        .I2(S_CPOL_reg_0),
        .I3(BUSY_i_2_n_0),
        .I4(SS_OUT_N1_out),
        .I5(S_SPI_BUSY),
        .O(BUSY_i_1_n_0));
  (* SOFT_HLUTNM = "soft_lutpair82" *) 
  LUT3 #(
    .INIT(8'h80)) 
    BUSY_i_2
       (.I0(curstate[1]),
        .I1(curstate[0]),
        .I2(\S_RX_OUT_BUFFER[127]_i_3_n_0 ),
        .O(BUSY_i_2_n_0));
  FDRE BUSY_reg
       (.C(s00_axi_aclk),
        .CE(1'b1),
        .D(BUSY_i_1_n_0),
        .Q(S_SPI_BUSY),
        .R(1'b0));
  LUT6 #(
    .INIT(64'hFF08FFFFFF080000)) 
    SS_OUT_N_i_1
       (.I0(SS_OUT_N_i_2_n_0),
        .I1(curstate[2]),
        .I2(SS_OUT_N_i_3_n_0),
        .I3(SS_OUT_N_i_4_n_0),
        .I4(SS_OUT_N1_out),
        .I5(SS_N),
        .O(SS_OUT_N_i_1_n_0));
  LUT2 #(
    .INIT(4'hB)) 
    SS_OUT_N_i_10
       (.I0(SS_IN_N),
        .I1(S_SCLK_reg_0),
        .O(SS_OUT_N_i_10_n_0));
  LUT6 #(
    .INIT(64'hFFFFFFFF00000002)) 
    SS_OUT_N_i_2
       (.I0(SS_OUT_N_i_6_n_0),
        .I1(S_DEL_COUNT[7]),
        .I2(S_DEL_COUNT[6]),
        .I3(S_DEL_COUNT[5]),
        .I4(S_DEL_COUNT[4]),
        .I5(S_DEL_COUNT[8]),
        .O(SS_OUT_N_i_2_n_0));
  (* SOFT_HLUTNM = "soft_lutpair79" *) 
  LUT2 #(
    .INIT(4'hE)) 
    SS_OUT_N_i_3
       (.I0(curstate[0]),
        .I1(curstate[1]),
        .O(SS_OUT_N_i_3_n_0));
  LUT6 #(
    .INIT(64'hEFEEEEEEAAAAAAAA)) 
    SS_OUT_N_i_4
       (.I0(SS_OUT_N_i_7_n_0),
        .I1(SS_OUT_N_i_8_n_0),
        .I2(\S_RX_OUT_BUFFER[127]_i_3_n_0 ),
        .I3(nxtstate1),
        .I4(SS_OUT_N_i_9_n_0),
        .I5(SS_OUT_N_i_10_n_0),
        .O(SS_OUT_N_i_4_n_0));
  LUT6 #(
    .INIT(64'h0000FE0300000000)) 
    SS_OUT_N_i_5
       (.I0(SS_OUT_N_i_2_n_0),
        .I1(curstate[0]),
        .I2(curstate[1]),
        .I3(curstate[2]),
        .I4(S_CPOL_reg_0),
        .I5(s00_axi_aresetn),
        .O(SS_OUT_N1_out));
  (* SOFT_HLUTNM = "soft_lutpair77" *) 
  LUT4 #(
    .INIT(16'h0001)) 
    SS_OUT_N_i_6
       (.I0(S_DEL_COUNT[1]),
        .I1(S_DEL_COUNT[0]),
        .I2(S_DEL_COUNT[3]),
        .I3(S_DEL_COUNT[2]),
        .O(SS_OUT_N_i_6_n_0));
  LUT6 #(
    .INIT(64'h0C00505000000000)) 
    SS_OUT_N_i_7
       (.I0(nxtstate1),
        .I1(SS_OUT_N_i_2_n_0),
        .I2(curstate[1]),
        .I3(S_CPHA_reg_n_0),
        .I4(curstate[0]),
        .I5(SS_OUT_N_i_10_n_0),
        .O(SS_OUT_N_i_7_n_0));
  (* SOFT_HLUTNM = "soft_lutpair70" *) 
  LUT4 #(
    .INIT(16'hCCC1)) 
    SS_OUT_N_i_8
       (.I0(\S_BIT_COUNT_reg[0]_0 ),
        .I1(curstate[2]),
        .I2(curstate[0]),
        .I3(curstate[1]),
        .O(SS_OUT_N_i_8_n_0));
  (* SOFT_HLUTNM = "soft_lutpair82" *) 
  LUT2 #(
    .INIT(4'h8)) 
    SS_OUT_N_i_9
       (.I0(curstate[0]),
        .I1(curstate[1]),
        .O(SS_OUT_N_i_9_n_0));
  FDRE SS_OUT_N_reg
       (.C(s00_axi_aclk),
        .CE(1'b1),
        .D(SS_OUT_N_i_1_n_0),
        .Q(SS_N),
        .R(1'b0));
  LUT5 #(
    .INIT(32'hF0F0FEF2)) 
    \S_BIT_COUNT[0]_i_1 
       (.I0(SS_OUT_N_i_2_n_0),
        .I1(curstate[1]),
        .I2(\S_BIT_COUNT[4]_i_2_n_0 ),
        .I3(\S_BIT_COUNT[0]_i_2_n_0 ),
        .I4(\S_BIT_COUNT_reg_n_0_[0] ),
        .O(S_BIT_COUNT[0]));
  LUT6 #(
    .INIT(64'h55555554FFFFFFFF)) 
    \S_BIT_COUNT[0]_i_2 
       (.I0(\S_BIT_COUNT_reg_n_0_[5] ),
        .I1(\S_BIT_COUNT_reg_n_0_[3] ),
        .I2(\S_BIT_COUNT_reg_n_0_[1] ),
        .I3(\S_BIT_COUNT_reg_n_0_[2] ),
        .I4(\S_BIT_COUNT_reg_n_0_[4] ),
        .I5(curstate[0]),
        .O(\S_BIT_COUNT[0]_i_2_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair81" *) 
  LUT3 #(
    .INIT(8'h82)) 
    \S_BIT_COUNT[1]_i_1 
       (.I0(nxtstate[1]),
        .I1(\S_BIT_COUNT_reg_n_0_[1] ),
        .I2(\S_BIT_COUNT_reg_n_0_[0] ),
        .O(S_BIT_COUNT[1]));
  (* SOFT_HLUTNM = "soft_lutpair74" *) 
  LUT4 #(
    .INIT(16'h8882)) 
    \S_BIT_COUNT[2]_i_1 
       (.I0(nxtstate[1]),
        .I1(\S_BIT_COUNT_reg_n_0_[2] ),
        .I2(\S_BIT_COUNT_reg_n_0_[0] ),
        .I3(\S_BIT_COUNT_reg_n_0_[1] ),
        .O(S_BIT_COUNT[2]));
  (* SOFT_HLUTNM = "soft_lutpair74" *) 
  LUT5 #(
    .INIT(32'h88888882)) 
    \S_BIT_COUNT[3]_i_1 
       (.I0(nxtstate[1]),
        .I1(\S_BIT_COUNT_reg_n_0_[3] ),
        .I2(\S_BIT_COUNT_reg_n_0_[2] ),
        .I3(\S_BIT_COUNT_reg_n_0_[1] ),
        .I4(\S_BIT_COUNT_reg_n_0_[0] ),
        .O(S_BIT_COUNT[3]));
  LUT5 #(
    .INIT(32'hF0F0FEF2)) 
    \S_BIT_COUNT[4]_i_1 
       (.I0(SS_OUT_N_i_2_n_0),
        .I1(curstate[1]),
        .I2(\S_BIT_COUNT[4]_i_2_n_0 ),
        .I3(\S_DEL_CLK[16]_i_3_n_0 ),
        .I4(\S_BIT_COUNT[4]_i_3_n_0 ),
        .O(S_BIT_COUNT[4]));
  LUT6 #(
    .INIT(64'hE0F3E2E3E0E0E2E2)) 
    \S_BIT_COUNT[4]_i_2 
       (.I0(SS_OUT_N_i_2_n_0),
        .I1(curstate[1]),
        .I2(curstate[2]),
        .I3(S_DEL_COUNT[8]),
        .I4(curstate[0]),
        .I5(\curstate[2]_i_2_n_0 ),
        .O(\S_BIT_COUNT[4]_i_2_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair78" *) 
  LUT5 #(
    .INIT(32'h0001FFFE)) 
    \S_BIT_COUNT[4]_i_3 
       (.I0(\S_BIT_COUNT_reg_n_0_[0] ),
        .I1(\S_BIT_COUNT_reg_n_0_[2] ),
        .I2(\S_BIT_COUNT_reg_n_0_[1] ),
        .I3(\S_BIT_COUNT_reg_n_0_[3] ),
        .I4(\S_BIT_COUNT_reg_n_0_[4] ),
        .O(\S_BIT_COUNT[4]_i_3_n_0 ));
  LUT6 #(
    .INIT(64'hAABBAABAAAABAAAA)) 
    \S_BIT_COUNT[5]_i_1 
       (.I0(\S_BIT_COUNT[5]_i_3_n_0 ),
        .I1(curstate[0]),
        .I2(curstate[1]),
        .I3(curstate[2]),
        .I4(\S_BIT_COUNT_reg[0]_0 ),
        .I5(nxtstate1),
        .O(\S_BIT_COUNT[5]_i_1_n_0 ));
  LUT2 #(
    .INIT(4'h1)) 
    \S_BIT_COUNT[5]_i_10 
       (.I0(S_DEL_CLK[11]),
        .I1(S_DEL_CLK[10]),
        .O(\S_BIT_COUNT[5]_i_10_n_0 ));
  LUT2 #(
    .INIT(4'h1)) 
    \S_BIT_COUNT[5]_i_11 
       (.I0(S_DEL_CLK[9]),
        .I1(S_DEL_CLK[8]),
        .O(\S_BIT_COUNT[5]_i_11_n_0 ));
  LUT2 #(
    .INIT(4'h1)) 
    \S_BIT_COUNT[5]_i_12 
       (.I0(S_DEL_CLK[7]),
        .I1(S_DEL_CLK[6]),
        .O(\S_BIT_COUNT[5]_i_12_n_0 ));
  LUT2 #(
    .INIT(4'h1)) 
    \S_BIT_COUNT[5]_i_13 
       (.I0(S_DEL_CLK[5]),
        .I1(S_DEL_CLK[4]),
        .O(\S_BIT_COUNT[5]_i_13_n_0 ));
  LUT2 #(
    .INIT(4'h1)) 
    \S_BIT_COUNT[5]_i_14 
       (.I0(S_DEL_CLK[3]),
        .I1(S_DEL_CLK[2]),
        .O(\S_BIT_COUNT[5]_i_14_n_0 ));
  LUT2 #(
    .INIT(4'h1)) 
    \S_BIT_COUNT[5]_i_15 
       (.I0(S_DEL_CLK[0]),
        .I1(S_DEL_CLK[1]),
        .O(\S_BIT_COUNT[5]_i_15_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair81" *) 
  LUT3 #(
    .INIT(8'h82)) 
    \S_BIT_COUNT[5]_i_2 
       (.I0(nxtstate[1]),
        .I1(\S_BIT_COUNT_reg_n_0_[5] ),
        .I2(\S_BIT_COUNT[5]_i_5_n_0 ),
        .O(S_BIT_COUNT[5]));
  (* SOFT_HLUTNM = "soft_lutpair75" *) 
  LUT5 #(
    .INIT(32'h00000200)) 
    \S_BIT_COUNT[5]_i_3 
       (.I0(SS_OUT_N_i_2_n_0),
        .I1(curstate[2]),
        .I2(curstate[1]),
        .I3(curstate[0]),
        .I4(S_CPHA_reg_n_0),
        .O(\S_BIT_COUNT[5]_i_3_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair78" *) 
  LUT5 #(
    .INIT(32'hFFFFFFFE)) 
    \S_BIT_COUNT[5]_i_5 
       (.I0(\S_BIT_COUNT_reg_n_0_[4] ),
        .I1(\S_BIT_COUNT_reg_n_0_[2] ),
        .I2(\S_BIT_COUNT_reg_n_0_[1] ),
        .I3(\S_BIT_COUNT_reg_n_0_[3] ),
        .I4(\S_BIT_COUNT_reg_n_0_[0] ),
        .O(\S_BIT_COUNT[5]_i_5_n_0 ));
  LUT1 #(
    .INIT(2'h1)) 
    \S_BIT_COUNT[5]_i_7 
       (.I0(S_DEL_CLK[16]),
        .O(\S_BIT_COUNT[5]_i_7_n_0 ));
  LUT2 #(
    .INIT(4'h1)) 
    \S_BIT_COUNT[5]_i_8 
       (.I0(S_DEL_CLK[15]),
        .I1(S_DEL_CLK[14]),
        .O(\S_BIT_COUNT[5]_i_8_n_0 ));
  LUT2 #(
    .INIT(4'h1)) 
    \S_BIT_COUNT[5]_i_9 
       (.I0(S_DEL_CLK[13]),
        .I1(S_DEL_CLK[12]),
        .O(\S_BIT_COUNT[5]_i_9_n_0 ));
  FDRE \S_BIT_COUNT_reg[0] 
       (.C(s00_axi_aclk),
        .CE(\S_BIT_COUNT[5]_i_1_n_0 ),
        .D(S_BIT_COUNT[0]),
        .Q(\S_BIT_COUNT_reg_n_0_[0] ),
        .R(RSTP));
  FDRE \S_BIT_COUNT_reg[1] 
       (.C(s00_axi_aclk),
        .CE(\S_BIT_COUNT[5]_i_1_n_0 ),
        .D(S_BIT_COUNT[1]),
        .Q(\S_BIT_COUNT_reg_n_0_[1] ),
        .R(RSTP));
  FDRE \S_BIT_COUNT_reg[2] 
       (.C(s00_axi_aclk),
        .CE(\S_BIT_COUNT[5]_i_1_n_0 ),
        .D(S_BIT_COUNT[2]),
        .Q(\S_BIT_COUNT_reg_n_0_[2] ),
        .R(RSTP));
  FDRE \S_BIT_COUNT_reg[3] 
       (.C(s00_axi_aclk),
        .CE(\S_BIT_COUNT[5]_i_1_n_0 ),
        .D(S_BIT_COUNT[3]),
        .Q(\S_BIT_COUNT_reg_n_0_[3] ),
        .R(RSTP));
  FDRE \S_BIT_COUNT_reg[4] 
       (.C(s00_axi_aclk),
        .CE(\S_BIT_COUNT[5]_i_1_n_0 ),
        .D(S_BIT_COUNT[4]),
        .Q(\S_BIT_COUNT_reg_n_0_[4] ),
        .R(RSTP));
  FDRE \S_BIT_COUNT_reg[5] 
       (.C(s00_axi_aclk),
        .CE(\S_BIT_COUNT[5]_i_1_n_0 ),
        .D(S_BIT_COUNT[5]),
        .Q(\S_BIT_COUNT_reg_n_0_[5] ),
        .R(RSTP));
  (* COMPARATOR_THRESHOLD = "11" *) 
  CARRY8 \S_BIT_COUNT_reg[5]_i_4 
       (.CI(\S_BIT_COUNT_reg[5]_i_6_n_0 ),
        .CI_TOP(1'b0),
        .CO({\NLW_S_BIT_COUNT_reg[5]_i_4_CO_UNCONNECTED [7:1],nxtstate1}),
        .DI({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,S_DEL_CLK[16]}),
        .O(\NLW_S_BIT_COUNT_reg[5]_i_4_O_UNCONNECTED [7:0]),
        .S({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,\S_BIT_COUNT[5]_i_7_n_0 }));
  (* COMPARATOR_THRESHOLD = "11" *) 
  CARRY8 \S_BIT_COUNT_reg[5]_i_6 
       (.CI(1'b1),
        .CI_TOP(1'b0),
        .CO({\S_BIT_COUNT_reg[5]_i_6_n_0 ,\S_BIT_COUNT_reg[5]_i_6_n_1 ,\S_BIT_COUNT_reg[5]_i_6_n_2 ,\S_BIT_COUNT_reg[5]_i_6_n_3 ,\S_BIT_COUNT_reg[5]_i_6_n_4 ,\S_BIT_COUNT_reg[5]_i_6_n_5 ,\S_BIT_COUNT_reg[5]_i_6_n_6 ,\S_BIT_COUNT_reg[5]_i_6_n_7 }),
        .DI({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .O(\NLW_S_BIT_COUNT_reg[5]_i_6_O_UNCONNECTED [7:0]),
        .S({\S_BIT_COUNT[5]_i_8_n_0 ,\S_BIT_COUNT[5]_i_9_n_0 ,\S_BIT_COUNT[5]_i_10_n_0 ,\S_BIT_COUNT[5]_i_11_n_0 ,\S_BIT_COUNT[5]_i_12_n_0 ,\S_BIT_COUNT[5]_i_13_n_0 ,\S_BIT_COUNT[5]_i_14_n_0 ,\S_BIT_COUNT[5]_i_15_n_0 }));
  LUT5 #(
    .INIT(32'hFE00FE03)) 
    \S_CLK_DIV[15]_i_1 
       (.I0(SS_OUT_N_i_2_n_0),
        .I1(curstate[1]),
        .I2(curstate[0]),
        .I3(curstate[2]),
        .I4(\S_BIT_COUNT_reg[0]_0 ),
        .O(S_CPHA));
  FDRE \S_CLK_DIV_reg[0] 
       (.C(s00_axi_aclk),
        .CE(S_CPHA),
        .D(\S_DEL_COUNT_reg[7]_0 [0]),
        .Q(S_CLK_DIV[0]),
        .R(RSTP));
  FDRE \S_CLK_DIV_reg[10] 
       (.C(s00_axi_aclk),
        .CE(S_CPHA),
        .D(\S_DEL_COUNT_reg[7]_0 [10]),
        .Q(S_CLK_DIV[10]),
        .R(RSTP));
  FDRE \S_CLK_DIV_reg[11] 
       (.C(s00_axi_aclk),
        .CE(S_CPHA),
        .D(\S_DEL_COUNT_reg[7]_0 [11]),
        .Q(S_CLK_DIV[11]),
        .R(RSTP));
  FDRE \S_CLK_DIV_reg[12] 
       (.C(s00_axi_aclk),
        .CE(S_CPHA),
        .D(\S_DEL_COUNT_reg[7]_0 [12]),
        .Q(S_CLK_DIV[12]),
        .R(RSTP));
  FDRE \S_CLK_DIV_reg[13] 
       (.C(s00_axi_aclk),
        .CE(S_CPHA),
        .D(\S_DEL_COUNT_reg[7]_0 [13]),
        .Q(S_CLK_DIV[13]),
        .R(RSTP));
  FDRE \S_CLK_DIV_reg[14] 
       (.C(s00_axi_aclk),
        .CE(S_CPHA),
        .D(\S_DEL_COUNT_reg[7]_0 [14]),
        .Q(S_CLK_DIV[14]),
        .R(RSTP));
  FDRE \S_CLK_DIV_reg[15] 
       (.C(s00_axi_aclk),
        .CE(S_CPHA),
        .D(\S_DEL_COUNT_reg[7]_0 [15]),
        .Q(S_CLK_DIV[15]),
        .R(RSTP));
  FDRE \S_CLK_DIV_reg[1] 
       (.C(s00_axi_aclk),
        .CE(S_CPHA),
        .D(\S_DEL_COUNT_reg[7]_0 [1]),
        .Q(S_CLK_DIV[1]),
        .R(RSTP));
  FDRE \S_CLK_DIV_reg[2] 
       (.C(s00_axi_aclk),
        .CE(S_CPHA),
        .D(\S_DEL_COUNT_reg[7]_0 [2]),
        .Q(S_CLK_DIV[2]),
        .R(RSTP));
  FDRE \S_CLK_DIV_reg[3] 
       (.C(s00_axi_aclk),
        .CE(S_CPHA),
        .D(\S_DEL_COUNT_reg[7]_0 [3]),
        .Q(S_CLK_DIV[3]),
        .R(RSTP));
  FDRE \S_CLK_DIV_reg[4] 
       (.C(s00_axi_aclk),
        .CE(S_CPHA),
        .D(\S_DEL_COUNT_reg[7]_0 [4]),
        .Q(S_CLK_DIV[4]),
        .R(RSTP));
  FDRE \S_CLK_DIV_reg[5] 
       (.C(s00_axi_aclk),
        .CE(S_CPHA),
        .D(\S_DEL_COUNT_reg[7]_0 [5]),
        .Q(S_CLK_DIV[5]),
        .R(RSTP));
  FDRE \S_CLK_DIV_reg[6] 
       (.C(s00_axi_aclk),
        .CE(S_CPHA),
        .D(\S_DEL_COUNT_reg[7]_0 [6]),
        .Q(S_CLK_DIV[6]),
        .R(RSTP));
  FDRE \S_CLK_DIV_reg[7] 
       (.C(s00_axi_aclk),
        .CE(S_CPHA),
        .D(\S_DEL_COUNT_reg[7]_0 [7]),
        .Q(S_CLK_DIV[7]),
        .R(RSTP));
  FDRE \S_CLK_DIV_reg[8] 
       (.C(s00_axi_aclk),
        .CE(S_CPHA),
        .D(\S_DEL_COUNT_reg[7]_0 [8]),
        .Q(S_CLK_DIV[8]),
        .R(RSTP));
  FDRE \S_CLK_DIV_reg[9] 
       (.C(s00_axi_aclk),
        .CE(S_CPHA),
        .D(\S_DEL_COUNT_reg[7]_0 [9]),
        .Q(S_CLK_DIV[9]),
        .R(RSTP));
  LUT3 #(
    .INIT(8'h20)) 
    S_CPHA_i_1
       (.I0(S_CPHA),
        .I1(S_CPOL_reg_0),
        .I2(s00_axi_aresetn),
        .O(S_CPOL));
  FDRE S_CPHA_reg
       (.C(s00_axi_aclk),
        .CE(S_CPOL),
        .D(CPHA),
        .Q(S_CPHA_reg_n_0),
        .R(1'b0));
  FDRE S_CPOL_reg
       (.C(s00_axi_aclk),
        .CE(S_CPOL),
        .D(CPOL),
        .Q(S_CPOL_reg_n_0),
        .R(1'b0));
  LUT6 #(
    .INIT(64'hFFFF88F888F888F8)) 
    \S_DEL_CLK[0]_i_1 
       (.I0(\S_DEL_CLK[15]_i_2_n_0 ),
        .I1(S_CLK_DIV[0]),
        .I2(\S_DEL_CLK[16]_i_4_n_0 ),
        .I3(S_DEL_CLK[0]),
        .I4(\S_DEL_COUNT_reg[7]_0 [0]),
        .I5(\S_DEL_CLK[15]_i_3_n_0 ),
        .O(S_DEL_CLK1_in[0]));
  LUT6 #(
    .INIT(64'hFFFFF888F888F888)) 
    \S_DEL_CLK[10]_i_1 
       (.I0(\S_DEL_CLK[15]_i_2_n_0 ),
        .I1(S_CLK_DIV[10]),
        .I2(\S_DEL_CLK[16]_i_4_n_0 ),
        .I3(S_DEL_CLK0[10]),
        .I4(\S_DEL_COUNT_reg[7]_0 [10]),
        .I5(\S_DEL_CLK[15]_i_3_n_0 ),
        .O(S_DEL_CLK1_in[10]));
  LUT6 #(
    .INIT(64'hFFFFF888F888F888)) 
    \S_DEL_CLK[11]_i_1 
       (.I0(\S_DEL_CLK[15]_i_2_n_0 ),
        .I1(S_CLK_DIV[11]),
        .I2(\S_DEL_CLK[16]_i_4_n_0 ),
        .I3(S_DEL_CLK0[11]),
        .I4(\S_DEL_COUNT_reg[7]_0 [11]),
        .I5(\S_DEL_CLK[15]_i_3_n_0 ),
        .O(S_DEL_CLK1_in[11]));
  LUT6 #(
    .INIT(64'hFFFFF888F888F888)) 
    \S_DEL_CLK[12]_i_1 
       (.I0(\S_DEL_CLK[15]_i_2_n_0 ),
        .I1(S_CLK_DIV[12]),
        .I2(\S_DEL_CLK[16]_i_4_n_0 ),
        .I3(S_DEL_CLK0[12]),
        .I4(\S_DEL_COUNT_reg[7]_0 [12]),
        .I5(\S_DEL_CLK[15]_i_3_n_0 ),
        .O(S_DEL_CLK1_in[12]));
  LUT6 #(
    .INIT(64'hFFFFF888F888F888)) 
    \S_DEL_CLK[13]_i_1 
       (.I0(\S_DEL_CLK[15]_i_2_n_0 ),
        .I1(S_CLK_DIV[13]),
        .I2(\S_DEL_CLK[16]_i_4_n_0 ),
        .I3(S_DEL_CLK0[13]),
        .I4(\S_DEL_COUNT_reg[7]_0 [13]),
        .I5(\S_DEL_CLK[15]_i_3_n_0 ),
        .O(S_DEL_CLK1_in[13]));
  LUT6 #(
    .INIT(64'hFFFFF888F888F888)) 
    \S_DEL_CLK[14]_i_1 
       (.I0(\S_DEL_CLK[15]_i_2_n_0 ),
        .I1(S_CLK_DIV[14]),
        .I2(\S_DEL_CLK[16]_i_4_n_0 ),
        .I3(S_DEL_CLK0[14]),
        .I4(\S_DEL_COUNT_reg[7]_0 [14]),
        .I5(\S_DEL_CLK[15]_i_3_n_0 ),
        .O(S_DEL_CLK1_in[14]));
  LUT6 #(
    .INIT(64'hFFFFF888F888F888)) 
    \S_DEL_CLK[15]_i_1 
       (.I0(\S_DEL_CLK[15]_i_2_n_0 ),
        .I1(S_CLK_DIV[15]),
        .I2(\S_DEL_CLK[16]_i_4_n_0 ),
        .I3(S_DEL_CLK0[15]),
        .I4(\S_DEL_COUNT_reg[7]_0 [15]),
        .I5(\S_DEL_CLK[15]_i_3_n_0 ),
        .O(S_DEL_CLK1_in[15]));
  (* SOFT_HLUTNM = "soft_lutpair75" *) 
  LUT5 #(
    .INIT(32'h02000000)) 
    \S_DEL_CLK[15]_i_2 
       (.I0(SS_OUT_N_i_2_n_0),
        .I1(curstate[2]),
        .I2(curstate[1]),
        .I3(curstate[0]),
        .I4(S_CPHA_reg_n_0),
        .O(\S_DEL_CLK[15]_i_2_n_0 ));
  LUT6 #(
    .INIT(64'hEEEEFEEEEEEEEEEE)) 
    \S_DEL_CLK[15]_i_3 
       (.I0(\curstate[0]_i_3_n_0 ),
        .I1(\S_DEL_CLK[15]_i_4_n_0 ),
        .I2(curstate[1]),
        .I3(nxtstate1),
        .I4(curstate[2]),
        .I5(\S_DEL_CLK[16]_i_3_n_0 ),
        .O(\S_DEL_CLK[15]_i_3_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair80" *) 
  LUT4 #(
    .INIT(16'h0002)) 
    \S_DEL_CLK[15]_i_4 
       (.I0(curstate[0]),
        .I1(curstate[1]),
        .I2(curstate[2]),
        .I3(S_CPHA_reg_n_0),
        .O(\S_DEL_CLK[15]_i_4_n_0 ));
  LUT5 #(
    .INIT(32'h0A0C0A00)) 
    \S_DEL_CLK[16]_i_1 
       (.I0(\S_DEL_CLK[16]_i_3_n_0 ),
        .I1(SS_OUT_N_i_2_n_0),
        .I2(curstate[2]),
        .I3(curstate[1]),
        .I4(curstate[0]),
        .O(nxtstate[1]));
  LUT1 #(
    .INIT(2'h1)) 
    \S_DEL_CLK[16]_i_10 
       (.I0(S_DEL_CLK[12]),
        .O(\S_DEL_CLK[16]_i_10_n_0 ));
  LUT1 #(
    .INIT(2'h1)) 
    \S_DEL_CLK[16]_i_11 
       (.I0(S_DEL_CLK[11]),
        .O(\S_DEL_CLK[16]_i_11_n_0 ));
  LUT1 #(
    .INIT(2'h1)) 
    \S_DEL_CLK[16]_i_12 
       (.I0(S_DEL_CLK[10]),
        .O(\S_DEL_CLK[16]_i_12_n_0 ));
  LUT1 #(
    .INIT(2'h1)) 
    \S_DEL_CLK[16]_i_13 
       (.I0(S_DEL_CLK[9]),
        .O(\S_DEL_CLK[16]_i_13_n_0 ));
  LUT2 #(
    .INIT(4'h8)) 
    \S_DEL_CLK[16]_i_2 
       (.I0(\S_DEL_CLK[16]_i_4_n_0 ),
        .I1(S_DEL_CLK0[16]),
        .O(S_DEL_CLK1_in[16]));
  LUT2 #(
    .INIT(4'h7)) 
    \S_DEL_CLK[16]_i_3 
       (.I0(\S_RX_OUT_BUFFER[127]_i_3_n_0 ),
        .I1(curstate[0]),
        .O(\S_DEL_CLK[16]_i_3_n_0 ));
  LUT6 #(
    .INIT(64'hFE03FECFFE03FE03)) 
    \S_DEL_CLK[16]_i_4 
       (.I0(SS_OUT_N_i_2_n_0),
        .I1(curstate[1]),
        .I2(curstate[0]),
        .I3(curstate[2]),
        .I4(nxtstate1),
        .I5(\S_DEL_CLK[16]_i_3_n_0 ),
        .O(\S_DEL_CLK[16]_i_4_n_0 ));
  LUT1 #(
    .INIT(2'h1)) 
    \S_DEL_CLK[16]_i_6 
       (.I0(S_DEL_CLK[16]),
        .O(\S_DEL_CLK[16]_i_6_n_0 ));
  LUT1 #(
    .INIT(2'h1)) 
    \S_DEL_CLK[16]_i_7 
       (.I0(S_DEL_CLK[15]),
        .O(\S_DEL_CLK[16]_i_7_n_0 ));
  LUT1 #(
    .INIT(2'h1)) 
    \S_DEL_CLK[16]_i_8 
       (.I0(S_DEL_CLK[14]),
        .O(\S_DEL_CLK[16]_i_8_n_0 ));
  LUT1 #(
    .INIT(2'h1)) 
    \S_DEL_CLK[16]_i_9 
       (.I0(S_DEL_CLK[13]),
        .O(\S_DEL_CLK[16]_i_9_n_0 ));
  LUT6 #(
    .INIT(64'hFFFFF888F888F888)) 
    \S_DEL_CLK[1]_i_1 
       (.I0(\S_DEL_CLK[15]_i_2_n_0 ),
        .I1(S_CLK_DIV[1]),
        .I2(\S_DEL_CLK[16]_i_4_n_0 ),
        .I3(S_DEL_CLK0[1]),
        .I4(\S_DEL_COUNT_reg[7]_0 [1]),
        .I5(\S_DEL_CLK[15]_i_3_n_0 ),
        .O(S_DEL_CLK1_in[1]));
  LUT6 #(
    .INIT(64'hFFFFF888F888F888)) 
    \S_DEL_CLK[2]_i_1 
       (.I0(\S_DEL_CLK[15]_i_2_n_0 ),
        .I1(S_CLK_DIV[2]),
        .I2(\S_DEL_CLK[16]_i_4_n_0 ),
        .I3(S_DEL_CLK0[2]),
        .I4(\S_DEL_COUNT_reg[7]_0 [2]),
        .I5(\S_DEL_CLK[15]_i_3_n_0 ),
        .O(S_DEL_CLK1_in[2]));
  LUT6 #(
    .INIT(64'hFFFFF888F888F888)) 
    \S_DEL_CLK[3]_i_1 
       (.I0(\S_DEL_CLK[15]_i_2_n_0 ),
        .I1(S_CLK_DIV[3]),
        .I2(\S_DEL_CLK[16]_i_4_n_0 ),
        .I3(S_DEL_CLK0[3]),
        .I4(\S_DEL_COUNT_reg[7]_0 [3]),
        .I5(\S_DEL_CLK[15]_i_3_n_0 ),
        .O(S_DEL_CLK1_in[3]));
  LUT6 #(
    .INIT(64'hFFFFF888F888F888)) 
    \S_DEL_CLK[4]_i_1 
       (.I0(\S_DEL_CLK[15]_i_2_n_0 ),
        .I1(S_CLK_DIV[4]),
        .I2(\S_DEL_CLK[16]_i_4_n_0 ),
        .I3(S_DEL_CLK0[4]),
        .I4(\S_DEL_COUNT_reg[7]_0 [4]),
        .I5(\S_DEL_CLK[15]_i_3_n_0 ),
        .O(S_DEL_CLK1_in[4]));
  LUT6 #(
    .INIT(64'hFFFFF888F888F888)) 
    \S_DEL_CLK[5]_i_1 
       (.I0(\S_DEL_CLK[15]_i_2_n_0 ),
        .I1(S_CLK_DIV[5]),
        .I2(\S_DEL_CLK[16]_i_4_n_0 ),
        .I3(S_DEL_CLK0[5]),
        .I4(\S_DEL_COUNT_reg[7]_0 [5]),
        .I5(\S_DEL_CLK[15]_i_3_n_0 ),
        .O(S_DEL_CLK1_in[5]));
  LUT6 #(
    .INIT(64'hFFFFF888F888F888)) 
    \S_DEL_CLK[6]_i_1 
       (.I0(\S_DEL_CLK[15]_i_2_n_0 ),
        .I1(S_CLK_DIV[6]),
        .I2(\S_DEL_CLK[16]_i_4_n_0 ),
        .I3(S_DEL_CLK0[6]),
        .I4(\S_DEL_COUNT_reg[7]_0 [6]),
        .I5(\S_DEL_CLK[15]_i_3_n_0 ),
        .O(S_DEL_CLK1_in[6]));
  LUT6 #(
    .INIT(64'hFFFFF888F888F888)) 
    \S_DEL_CLK[7]_i_1 
       (.I0(\S_DEL_CLK[15]_i_2_n_0 ),
        .I1(S_CLK_DIV[7]),
        .I2(\S_DEL_CLK[16]_i_4_n_0 ),
        .I3(S_DEL_CLK0[7]),
        .I4(\S_DEL_COUNT_reg[7]_0 [7]),
        .I5(\S_DEL_CLK[15]_i_3_n_0 ),
        .O(S_DEL_CLK1_in[7]));
  LUT6 #(
    .INIT(64'hFFFFF888F888F888)) 
    \S_DEL_CLK[8]_i_1 
       (.I0(\S_DEL_CLK[15]_i_2_n_0 ),
        .I1(S_CLK_DIV[8]),
        .I2(\S_DEL_CLK[16]_i_4_n_0 ),
        .I3(S_DEL_CLK0[8]),
        .I4(\S_DEL_COUNT_reg[7]_0 [8]),
        .I5(\S_DEL_CLK[15]_i_3_n_0 ),
        .O(S_DEL_CLK1_in[8]));
  LUT1 #(
    .INIT(2'h1)) 
    \S_DEL_CLK[8]_i_10 
       (.I0(S_DEL_CLK[1]),
        .O(\S_DEL_CLK[8]_i_10_n_0 ));
  LUT1 #(
    .INIT(2'h1)) 
    \S_DEL_CLK[8]_i_3 
       (.I0(S_DEL_CLK[8]),
        .O(\S_DEL_CLK[8]_i_3_n_0 ));
  LUT1 #(
    .INIT(2'h1)) 
    \S_DEL_CLK[8]_i_4 
       (.I0(S_DEL_CLK[7]),
        .O(\S_DEL_CLK[8]_i_4_n_0 ));
  LUT1 #(
    .INIT(2'h1)) 
    \S_DEL_CLK[8]_i_5 
       (.I0(S_DEL_CLK[6]),
        .O(\S_DEL_CLK[8]_i_5_n_0 ));
  LUT1 #(
    .INIT(2'h1)) 
    \S_DEL_CLK[8]_i_6 
       (.I0(S_DEL_CLK[5]),
        .O(\S_DEL_CLK[8]_i_6_n_0 ));
  LUT1 #(
    .INIT(2'h1)) 
    \S_DEL_CLK[8]_i_7 
       (.I0(S_DEL_CLK[4]),
        .O(\S_DEL_CLK[8]_i_7_n_0 ));
  LUT1 #(
    .INIT(2'h1)) 
    \S_DEL_CLK[8]_i_8 
       (.I0(S_DEL_CLK[3]),
        .O(\S_DEL_CLK[8]_i_8_n_0 ));
  LUT1 #(
    .INIT(2'h1)) 
    \S_DEL_CLK[8]_i_9 
       (.I0(S_DEL_CLK[2]),
        .O(\S_DEL_CLK[8]_i_9_n_0 ));
  LUT6 #(
    .INIT(64'hFFFFF888F888F888)) 
    \S_DEL_CLK[9]_i_1 
       (.I0(\S_DEL_CLK[15]_i_2_n_0 ),
        .I1(S_CLK_DIV[9]),
        .I2(\S_DEL_CLK[16]_i_4_n_0 ),
        .I3(S_DEL_CLK0[9]),
        .I4(\S_DEL_COUNT_reg[7]_0 [9]),
        .I5(\S_DEL_CLK[15]_i_3_n_0 ),
        .O(S_DEL_CLK1_in[9]));
  FDRE \S_DEL_CLK_reg[0] 
       (.C(s00_axi_aclk),
        .CE(nxtstate[1]),
        .D(S_DEL_CLK1_in[0]),
        .Q(S_DEL_CLK[0]),
        .R(RSTP));
  FDRE \S_DEL_CLK_reg[10] 
       (.C(s00_axi_aclk),
        .CE(nxtstate[1]),
        .D(S_DEL_CLK1_in[10]),
        .Q(S_DEL_CLK[10]),
        .R(RSTP));
  FDRE \S_DEL_CLK_reg[11] 
       (.C(s00_axi_aclk),
        .CE(nxtstate[1]),
        .D(S_DEL_CLK1_in[11]),
        .Q(S_DEL_CLK[11]),
        .R(RSTP));
  FDRE \S_DEL_CLK_reg[12] 
       (.C(s00_axi_aclk),
        .CE(nxtstate[1]),
        .D(S_DEL_CLK1_in[12]),
        .Q(S_DEL_CLK[12]),
        .R(RSTP));
  FDRE \S_DEL_CLK_reg[13] 
       (.C(s00_axi_aclk),
        .CE(nxtstate[1]),
        .D(S_DEL_CLK1_in[13]),
        .Q(S_DEL_CLK[13]),
        .R(RSTP));
  FDRE \S_DEL_CLK_reg[14] 
       (.C(s00_axi_aclk),
        .CE(nxtstate[1]),
        .D(S_DEL_CLK1_in[14]),
        .Q(S_DEL_CLK[14]),
        .R(RSTP));
  FDRE \S_DEL_CLK_reg[15] 
       (.C(s00_axi_aclk),
        .CE(nxtstate[1]),
        .D(S_DEL_CLK1_in[15]),
        .Q(S_DEL_CLK[15]),
        .R(RSTP));
  FDRE \S_DEL_CLK_reg[16] 
       (.C(s00_axi_aclk),
        .CE(nxtstate[1]),
        .D(S_DEL_CLK1_in[16]),
        .Q(S_DEL_CLK[16]),
        .R(RSTP));
  (* ADDER_THRESHOLD = "35" *) 
  CARRY8 \S_DEL_CLK_reg[16]_i_5 
       (.CI(\S_DEL_CLK_reg[8]_i_2_n_0 ),
        .CI_TOP(1'b0),
        .CO({\NLW_S_DEL_CLK_reg[16]_i_5_CO_UNCONNECTED [7],\S_DEL_CLK_reg[16]_i_5_n_1 ,\S_DEL_CLK_reg[16]_i_5_n_2 ,\S_DEL_CLK_reg[16]_i_5_n_3 ,\S_DEL_CLK_reg[16]_i_5_n_4 ,\S_DEL_CLK_reg[16]_i_5_n_5 ,\S_DEL_CLK_reg[16]_i_5_n_6 ,\S_DEL_CLK_reg[16]_i_5_n_7 }),
        .DI({1'b0,S_DEL_CLK[15:9]}),
        .O(S_DEL_CLK0[16:9]),
        .S({\S_DEL_CLK[16]_i_6_n_0 ,\S_DEL_CLK[16]_i_7_n_0 ,\S_DEL_CLK[16]_i_8_n_0 ,\S_DEL_CLK[16]_i_9_n_0 ,\S_DEL_CLK[16]_i_10_n_0 ,\S_DEL_CLK[16]_i_11_n_0 ,\S_DEL_CLK[16]_i_12_n_0 ,\S_DEL_CLK[16]_i_13_n_0 }));
  FDRE \S_DEL_CLK_reg[1] 
       (.C(s00_axi_aclk),
        .CE(nxtstate[1]),
        .D(S_DEL_CLK1_in[1]),
        .Q(S_DEL_CLK[1]),
        .R(RSTP));
  FDRE \S_DEL_CLK_reg[2] 
       (.C(s00_axi_aclk),
        .CE(nxtstate[1]),
        .D(S_DEL_CLK1_in[2]),
        .Q(S_DEL_CLK[2]),
        .R(RSTP));
  FDRE \S_DEL_CLK_reg[3] 
       (.C(s00_axi_aclk),
        .CE(nxtstate[1]),
        .D(S_DEL_CLK1_in[3]),
        .Q(S_DEL_CLK[3]),
        .R(RSTP));
  FDRE \S_DEL_CLK_reg[4] 
       (.C(s00_axi_aclk),
        .CE(nxtstate[1]),
        .D(S_DEL_CLK1_in[4]),
        .Q(S_DEL_CLK[4]),
        .R(RSTP));
  FDRE \S_DEL_CLK_reg[5] 
       (.C(s00_axi_aclk),
        .CE(nxtstate[1]),
        .D(S_DEL_CLK1_in[5]),
        .Q(S_DEL_CLK[5]),
        .R(RSTP));
  FDRE \S_DEL_CLK_reg[6] 
       (.C(s00_axi_aclk),
        .CE(nxtstate[1]),
        .D(S_DEL_CLK1_in[6]),
        .Q(S_DEL_CLK[6]),
        .R(RSTP));
  FDRE \S_DEL_CLK_reg[7] 
       (.C(s00_axi_aclk),
        .CE(nxtstate[1]),
        .D(S_DEL_CLK1_in[7]),
        .Q(S_DEL_CLK[7]),
        .R(RSTP));
  FDRE \S_DEL_CLK_reg[8] 
       (.C(s00_axi_aclk),
        .CE(nxtstate[1]),
        .D(S_DEL_CLK1_in[8]),
        .Q(S_DEL_CLK[8]),
        .R(RSTP));
  (* ADDER_THRESHOLD = "35" *) 
  CARRY8 \S_DEL_CLK_reg[8]_i_2 
       (.CI(S_DEL_CLK[0]),
        .CI_TOP(1'b0),
        .CO({\S_DEL_CLK_reg[8]_i_2_n_0 ,\S_DEL_CLK_reg[8]_i_2_n_1 ,\S_DEL_CLK_reg[8]_i_2_n_2 ,\S_DEL_CLK_reg[8]_i_2_n_3 ,\S_DEL_CLK_reg[8]_i_2_n_4 ,\S_DEL_CLK_reg[8]_i_2_n_5 ,\S_DEL_CLK_reg[8]_i_2_n_6 ,\S_DEL_CLK_reg[8]_i_2_n_7 }),
        .DI(S_DEL_CLK[8:1]),
        .O(S_DEL_CLK0[8:1]),
        .S({\S_DEL_CLK[8]_i_3_n_0 ,\S_DEL_CLK[8]_i_4_n_0 ,\S_DEL_CLK[8]_i_5_n_0 ,\S_DEL_CLK[8]_i_6_n_0 ,\S_DEL_CLK[8]_i_7_n_0 ,\S_DEL_CLK[8]_i_8_n_0 ,\S_DEL_CLK[8]_i_9_n_0 ,\S_DEL_CLK[8]_i_10_n_0 }));
  FDRE \S_DEL_CLK_reg[9] 
       (.C(s00_axi_aclk),
        .CE(nxtstate[1]),
        .D(S_DEL_CLK1_in[9]),
        .Q(S_DEL_CLK[9]),
        .R(RSTP));
  LUT6 #(
    .INIT(64'hF888FFFFF888F888)) 
    \S_DEL_COUNT[0]_i_1 
       (.I0(\S_DEL_COUNT[6]_i_2_n_0 ),
        .I1(S_PRE_DELAY[0]),
        .I2(S_RX_OUT_BUFFER),
        .I3(\S_DEL_COUNT_reg[7]_0 [24]),
        .I4(S_DEL_COUNT[0]),
        .I5(\S_DEL_COUNT[8]_i_4_n_0 ),
        .O(S_DEL_COUNT1_in[0]));
  LUT4 #(
    .INIT(16'hEBAA)) 
    \S_DEL_COUNT[1]_i_1 
       (.I0(\S_DEL_COUNT[1]_i_2_n_0 ),
        .I1(S_DEL_COUNT[0]),
        .I2(S_DEL_COUNT[1]),
        .I3(\S_DEL_COUNT[8]_i_4_n_0 ),
        .O(S_DEL_COUNT1_in[1]));
  LUT6 #(
    .INIT(64'h88888888888888F8)) 
    \S_DEL_COUNT[1]_i_2 
       (.I0(\S_DEL_COUNT_reg[7]_0 [25]),
        .I1(S_RX_OUT_BUFFER),
        .I2(S_PRE_DELAY[1]),
        .I3(curstate[2]),
        .I4(curstate[1]),
        .I5(curstate[0]),
        .O(\S_DEL_COUNT[1]_i_2_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair73" *) 
  LUT5 #(
    .INIT(32'hFEABAAAA)) 
    \S_DEL_COUNT[2]_i_1 
       (.I0(\S_DEL_COUNT[2]_i_2_n_0 ),
        .I1(S_DEL_COUNT[1]),
        .I2(S_DEL_COUNT[0]),
        .I3(S_DEL_COUNT[2]),
        .I4(\S_DEL_COUNT[8]_i_4_n_0 ),
        .O(S_DEL_COUNT1_in[2]));
  LUT6 #(
    .INIT(64'h88888888888888F8)) 
    \S_DEL_COUNT[2]_i_2 
       (.I0(\S_DEL_COUNT_reg[7]_0 [26]),
        .I1(S_RX_OUT_BUFFER),
        .I2(S_PRE_DELAY[2]),
        .I3(curstate[2]),
        .I4(curstate[1]),
        .I5(curstate[0]),
        .O(\S_DEL_COUNT[2]_i_2_n_0 ));
  LUT6 #(
    .INIT(64'hFFFEAAABAAAAAAAA)) 
    \S_DEL_COUNT[3]_i_1 
       (.I0(\S_DEL_COUNT[3]_i_2_n_0 ),
        .I1(S_DEL_COUNT[0]),
        .I2(S_DEL_COUNT[1]),
        .I3(S_DEL_COUNT[2]),
        .I4(S_DEL_COUNT[3]),
        .I5(\S_DEL_COUNT[8]_i_4_n_0 ),
        .O(S_DEL_COUNT1_in[3]));
  LUT6 #(
    .INIT(64'h88888888888888F8)) 
    \S_DEL_COUNT[3]_i_2 
       (.I0(\S_DEL_COUNT_reg[7]_0 [27]),
        .I1(S_RX_OUT_BUFFER),
        .I2(S_PRE_DELAY[3]),
        .I3(curstate[2]),
        .I4(curstate[1]),
        .I5(curstate[0]),
        .O(\S_DEL_COUNT[3]_i_2_n_0 ));
  LUT6 #(
    .INIT(64'hF888FFFFF888F888)) 
    \S_DEL_COUNT[4]_i_1 
       (.I0(\S_DEL_COUNT[6]_i_2_n_0 ),
        .I1(S_PRE_DELAY[4]),
        .I2(S_RX_OUT_BUFFER),
        .I3(\S_DEL_COUNT_reg[7]_0 [28]),
        .I4(\S_DEL_COUNT[4]_i_2_n_0 ),
        .I5(\S_DEL_COUNT[8]_i_4_n_0 ),
        .O(S_DEL_COUNT1_in[4]));
  (* SOFT_HLUTNM = "soft_lutpair77" *) 
  LUT5 #(
    .INIT(32'h0001FFFE)) 
    \S_DEL_COUNT[4]_i_2 
       (.I0(S_DEL_COUNT[3]),
        .I1(S_DEL_COUNT[2]),
        .I2(S_DEL_COUNT[1]),
        .I3(S_DEL_COUNT[0]),
        .I4(S_DEL_COUNT[4]),
        .O(\S_DEL_COUNT[4]_i_2_n_0 ));
  LUT6 #(
    .INIT(64'hF888FFFFF888F888)) 
    \S_DEL_COUNT[5]_i_1 
       (.I0(\S_DEL_COUNT[6]_i_2_n_0 ),
        .I1(S_PRE_DELAY[5]),
        .I2(S_RX_OUT_BUFFER),
        .I3(\S_DEL_COUNT_reg[7]_0 [29]),
        .I4(\S_DEL_COUNT[5]_i_2_n_0 ),
        .I5(\S_DEL_COUNT[8]_i_4_n_0 ),
        .O(S_DEL_COUNT1_in[5]));
  LUT6 #(
    .INIT(64'h00000001FFFFFFFE)) 
    \S_DEL_COUNT[5]_i_2 
       (.I0(S_DEL_COUNT[4]),
        .I1(S_DEL_COUNT[0]),
        .I2(S_DEL_COUNT[1]),
        .I3(S_DEL_COUNT[2]),
        .I4(S_DEL_COUNT[3]),
        .I5(S_DEL_COUNT[5]),
        .O(\S_DEL_COUNT[5]_i_2_n_0 ));
  LUT6 #(
    .INIT(64'hF888FFFFF888F888)) 
    \S_DEL_COUNT[6]_i_1 
       (.I0(\S_DEL_COUNT[6]_i_2_n_0 ),
        .I1(S_PRE_DELAY[6]),
        .I2(S_RX_OUT_BUFFER),
        .I3(\S_DEL_COUNT_reg[7]_0 [30]),
        .I4(\S_DEL_COUNT[6]_i_3_n_0 ),
        .I5(\S_DEL_COUNT[8]_i_4_n_0 ),
        .O(S_DEL_COUNT1_in[6]));
  (* SOFT_HLUTNM = "soft_lutpair76" *) 
  LUT3 #(
    .INIT(8'h01)) 
    \S_DEL_COUNT[6]_i_2 
       (.I0(curstate[2]),
        .I1(curstate[1]),
        .I2(curstate[0]),
        .O(\S_DEL_COUNT[6]_i_2_n_0 ));
  LUT6 #(
    .INIT(64'h00000100FFFFFEFF)) 
    \S_DEL_COUNT[6]_i_3 
       (.I0(S_DEL_COUNT[5]),
        .I1(S_DEL_COUNT[3]),
        .I2(S_DEL_COUNT[2]),
        .I3(\S_DEL_COUNT[6]_i_4_n_0 ),
        .I4(S_DEL_COUNT[4]),
        .I5(S_DEL_COUNT[6]),
        .O(\S_DEL_COUNT[6]_i_3_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair73" *) 
  LUT2 #(
    .INIT(4'h1)) 
    \S_DEL_COUNT[6]_i_4 
       (.I0(S_DEL_COUNT[0]),
        .I1(S_DEL_COUNT[1]),
        .O(\S_DEL_COUNT[6]_i_4_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair72" *) 
  LUT5 #(
    .INIT(32'hFEABAAAA)) 
    \S_DEL_COUNT[7]_i_1 
       (.I0(\S_DEL_COUNT[7]_i_2_n_0 ),
        .I1(S_DEL_COUNT[6]),
        .I2(\S_DEL_COUNT[7]_i_3_n_0 ),
        .I3(S_DEL_COUNT[7]),
        .I4(\S_DEL_COUNT[8]_i_4_n_0 ),
        .O(S_DEL_COUNT1_in[7]));
  LUT6 #(
    .INIT(64'h88888888888888F8)) 
    \S_DEL_COUNT[7]_i_2 
       (.I0(\S_DEL_COUNT_reg[7]_0 [31]),
        .I1(S_RX_OUT_BUFFER),
        .I2(S_PRE_DELAY[7]),
        .I3(curstate[2]),
        .I4(curstate[1]),
        .I5(curstate[0]),
        .O(\S_DEL_COUNT[7]_i_2_n_0 ));
  LUT6 #(
    .INIT(64'hFFFFFFFFFFFFFFFE)) 
    \S_DEL_COUNT[7]_i_3 
       (.I0(S_DEL_COUNT[4]),
        .I1(S_DEL_COUNT[0]),
        .I2(S_DEL_COUNT[1]),
        .I3(S_DEL_COUNT[2]),
        .I4(S_DEL_COUNT[3]),
        .I5(S_DEL_COUNT[5]),
        .O(\S_DEL_COUNT[7]_i_3_n_0 ));
  LUT6 #(
    .INIT(64'h0000AAAEAAAE0000)) 
    \S_DEL_COUNT[8]_i_1 
       (.I0(\S_DEL_COUNT[8]_i_3_n_0 ),
        .I1(\curstate[2]_i_2_n_0 ),
        .I2(curstate[1]),
        .I3(S_DEL_COUNT[8]),
        .I4(nxtstate[2]),
        .I5(nxtstate[0]),
        .O(\S_DEL_COUNT[8]_i_1_n_0 ));
  LUT3 #(
    .INIT(8'h82)) 
    \S_DEL_COUNT[8]_i_2 
       (.I0(\S_DEL_COUNT[8]_i_4_n_0 ),
        .I1(S_DEL_COUNT[8]),
        .I2(\curstate[2]_i_2_n_0 ),
        .O(S_DEL_COUNT1_in[8]));
  (* SOFT_HLUTNM = "soft_lutpair80" *) 
  LUT4 #(
    .INIT(16'hEAAF)) 
    \S_DEL_COUNT[8]_i_3 
       (.I0(curstate[2]),
        .I1(\S_RX_OUT_BUFFER[127]_i_3_n_0 ),
        .I2(curstate[0]),
        .I3(curstate[1]),
        .O(\S_DEL_COUNT[8]_i_3_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair79" *) 
  LUT5 #(
    .INIT(32'hFFFBAAFB)) 
    \S_DEL_COUNT[8]_i_4 
       (.I0(curstate[2]),
        .I1(\S_BIT_COUNT_reg[0]_0 ),
        .I2(curstate[0]),
        .I3(curstate[1]),
        .I4(\S_DEL_CLK[16]_i_3_n_0 ),
        .O(\S_DEL_COUNT[8]_i_4_n_0 ));
  FDRE \S_DEL_COUNT_reg[0] 
       (.C(s00_axi_aclk),
        .CE(\S_DEL_COUNT[8]_i_1_n_0 ),
        .D(S_DEL_COUNT1_in[0]),
        .Q(S_DEL_COUNT[0]),
        .R(RSTP));
  FDRE \S_DEL_COUNT_reg[1] 
       (.C(s00_axi_aclk),
        .CE(\S_DEL_COUNT[8]_i_1_n_0 ),
        .D(S_DEL_COUNT1_in[1]),
        .Q(S_DEL_COUNT[1]),
        .R(RSTP));
  FDRE \S_DEL_COUNT_reg[2] 
       (.C(s00_axi_aclk),
        .CE(\S_DEL_COUNT[8]_i_1_n_0 ),
        .D(S_DEL_COUNT1_in[2]),
        .Q(S_DEL_COUNT[2]),
        .R(RSTP));
  FDRE \S_DEL_COUNT_reg[3] 
       (.C(s00_axi_aclk),
        .CE(\S_DEL_COUNT[8]_i_1_n_0 ),
        .D(S_DEL_COUNT1_in[3]),
        .Q(S_DEL_COUNT[3]),
        .R(RSTP));
  FDRE \S_DEL_COUNT_reg[4] 
       (.C(s00_axi_aclk),
        .CE(\S_DEL_COUNT[8]_i_1_n_0 ),
        .D(S_DEL_COUNT1_in[4]),
        .Q(S_DEL_COUNT[4]),
        .R(RSTP));
  FDRE \S_DEL_COUNT_reg[5] 
       (.C(s00_axi_aclk),
        .CE(\S_DEL_COUNT[8]_i_1_n_0 ),
        .D(S_DEL_COUNT1_in[5]),
        .Q(S_DEL_COUNT[5]),
        .R(RSTP));
  FDRE \S_DEL_COUNT_reg[6] 
       (.C(s00_axi_aclk),
        .CE(\S_DEL_COUNT[8]_i_1_n_0 ),
        .D(S_DEL_COUNT1_in[6]),
        .Q(S_DEL_COUNT[6]),
        .R(RSTP));
  FDRE \S_DEL_COUNT_reg[7] 
       (.C(s00_axi_aclk),
        .CE(\S_DEL_COUNT[8]_i_1_n_0 ),
        .D(S_DEL_COUNT1_in[7]),
        .Q(S_DEL_COUNT[7]),
        .R(RSTP));
  FDRE \S_DEL_COUNT_reg[8] 
       (.C(s00_axi_aclk),
        .CE(\S_DEL_COUNT[8]_i_1_n_0 ),
        .D(S_DEL_COUNT1_in[8]),
        .Q(S_DEL_COUNT[8]),
        .R(RSTP));
  FDRE \S_PRE_DELAY_reg[0] 
       (.C(s00_axi_aclk),
        .CE(S_CPHA),
        .D(\S_DEL_COUNT_reg[7]_0 [16]),
        .Q(S_PRE_DELAY[0]),
        .R(RSTP));
  FDRE \S_PRE_DELAY_reg[1] 
       (.C(s00_axi_aclk),
        .CE(S_CPHA),
        .D(\S_DEL_COUNT_reg[7]_0 [17]),
        .Q(S_PRE_DELAY[1]),
        .R(RSTP));
  FDRE \S_PRE_DELAY_reg[2] 
       (.C(s00_axi_aclk),
        .CE(S_CPHA),
        .D(\S_DEL_COUNT_reg[7]_0 [18]),
        .Q(S_PRE_DELAY[2]),
        .R(RSTP));
  FDRE \S_PRE_DELAY_reg[3] 
       (.C(s00_axi_aclk),
        .CE(S_CPHA),
        .D(\S_DEL_COUNT_reg[7]_0 [19]),
        .Q(S_PRE_DELAY[3]),
        .R(RSTP));
  FDRE \S_PRE_DELAY_reg[4] 
       (.C(s00_axi_aclk),
        .CE(S_CPHA),
        .D(\S_DEL_COUNT_reg[7]_0 [20]),
        .Q(S_PRE_DELAY[4]),
        .R(RSTP));
  FDRE \S_PRE_DELAY_reg[5] 
       (.C(s00_axi_aclk),
        .CE(S_CPHA),
        .D(\S_DEL_COUNT_reg[7]_0 [21]),
        .Q(S_PRE_DELAY[5]),
        .R(RSTP));
  FDRE \S_PRE_DELAY_reg[6] 
       (.C(s00_axi_aclk),
        .CE(S_CPHA),
        .D(\S_DEL_COUNT_reg[7]_0 [22]),
        .Q(S_PRE_DELAY[6]),
        .R(RSTP));
  FDRE \S_PRE_DELAY_reg[7] 
       (.C(s00_axi_aclk),
        .CE(S_CPHA),
        .D(\S_DEL_COUNT_reg[7]_0 [23]),
        .Q(S_PRE_DELAY[7]),
        .R(RSTP));
  LUT6 #(
    .INIT(64'h8F808F8F8F808080)) 
    \S_RAW_VALUE_S_C[0]_i_1 
       (.I0(RAW_VALUE[112]),
        .I1(\S_RAW_VALUE_S_C_reg[0] ),
        .I2(\S_RAW_VALUE_S_C_reg[0]_0 [3]),
        .I3(\S_RAW_VALUE_S_C[0]_i_2_n_0 ),
        .I4(\S_RAW_VALUE_S_C_reg[0]_0 [2]),
        .I5(\S_RAW_VALUE_S_C[0]_i_3_n_0 ),
        .O(\S_RX_OUT_BUFFER_reg[127]_0 [0]));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \S_RAW_VALUE_S_C[0]_i_2 
       (.I0(RAW_VALUE[96]),
        .I1(RAW_VALUE[80]),
        .I2(\S_RAW_VALUE_S_C_reg[0]_0 [1]),
        .I3(RAW_VALUE[64]),
        .I4(\S_RAW_VALUE_S_C_reg[0]_0 [0]),
        .I5(RAW_VALUE[48]),
        .O(\S_RAW_VALUE_S_C[0]_i_2_n_0 ));
  LUT5 #(
    .INIT(32'hAFC0A0C0)) 
    \S_RAW_VALUE_S_C[0]_i_3 
       (.I0(RAW_VALUE[32]),
        .I1(RAW_VALUE[16]),
        .I2(\S_RAW_VALUE_S_C_reg[0]_0 [1]),
        .I3(\S_RAW_VALUE_S_C_reg[0]_0 [0]),
        .I4(RAW_VALUE[0]),
        .O(\S_RAW_VALUE_S_C[0]_i_3_n_0 ));
  LUT6 #(
    .INIT(64'h8F808F8F8F808080)) 
    \S_RAW_VALUE_S_C[10]_i_1 
       (.I0(RAW_VALUE[122]),
        .I1(\S_RAW_VALUE_S_C_reg[0] ),
        .I2(\S_RAW_VALUE_S_C_reg[0]_0 [3]),
        .I3(\S_RAW_VALUE_S_C[10]_i_2_n_0 ),
        .I4(\S_RAW_VALUE_S_C_reg[0]_0 [2]),
        .I5(\S_RAW_VALUE_S_C[10]_i_3_n_0 ),
        .O(\S_RX_OUT_BUFFER_reg[127]_0 [10]));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \S_RAW_VALUE_S_C[10]_i_2 
       (.I0(RAW_VALUE[106]),
        .I1(RAW_VALUE[90]),
        .I2(\S_RAW_VALUE_S_C_reg[0]_0 [1]),
        .I3(RAW_VALUE[74]),
        .I4(\S_RAW_VALUE_S_C_reg[0]_0 [0]),
        .I5(RAW_VALUE[58]),
        .O(\S_RAW_VALUE_S_C[10]_i_2_n_0 ));
  LUT5 #(
    .INIT(32'hAFC0A0C0)) 
    \S_RAW_VALUE_S_C[10]_i_3 
       (.I0(RAW_VALUE[42]),
        .I1(RAW_VALUE[26]),
        .I2(\S_RAW_VALUE_S_C_reg[0]_0 [1]),
        .I3(\S_RAW_VALUE_S_C_reg[0]_0 [0]),
        .I4(RAW_VALUE[10]),
        .O(\S_RAW_VALUE_S_C[10]_i_3_n_0 ));
  LUT6 #(
    .INIT(64'h8F808F8F8F808080)) 
    \S_RAW_VALUE_S_C[11]_i_1 
       (.I0(RAW_VALUE[123]),
        .I1(\S_RAW_VALUE_S_C_reg[0] ),
        .I2(\S_RAW_VALUE_S_C_reg[0]_0 [3]),
        .I3(\S_RAW_VALUE_S_C[11]_i_2_n_0 ),
        .I4(\S_RAW_VALUE_S_C_reg[0]_0 [2]),
        .I5(\S_RAW_VALUE_S_C[11]_i_3_n_0 ),
        .O(\S_RX_OUT_BUFFER_reg[127]_0 [11]));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \S_RAW_VALUE_S_C[11]_i_2 
       (.I0(RAW_VALUE[107]),
        .I1(RAW_VALUE[91]),
        .I2(\S_RAW_VALUE_S_C_reg[0]_0 [1]),
        .I3(RAW_VALUE[75]),
        .I4(\S_RAW_VALUE_S_C_reg[0]_0 [0]),
        .I5(RAW_VALUE[59]),
        .O(\S_RAW_VALUE_S_C[11]_i_2_n_0 ));
  LUT5 #(
    .INIT(32'hAFC0A0C0)) 
    \S_RAW_VALUE_S_C[11]_i_3 
       (.I0(RAW_VALUE[43]),
        .I1(RAW_VALUE[27]),
        .I2(\S_RAW_VALUE_S_C_reg[0]_0 [1]),
        .I3(\S_RAW_VALUE_S_C_reg[0]_0 [0]),
        .I4(RAW_VALUE[11]),
        .O(\S_RAW_VALUE_S_C[11]_i_3_n_0 ));
  LUT6 #(
    .INIT(64'h8F808F8F8F808080)) 
    \S_RAW_VALUE_S_C[12]_i_1 
       (.I0(RAW_VALUE[124]),
        .I1(\S_RAW_VALUE_S_C_reg[0] ),
        .I2(\S_RAW_VALUE_S_C_reg[0]_0 [3]),
        .I3(\S_RAW_VALUE_S_C[12]_i_2_n_0 ),
        .I4(\S_RAW_VALUE_S_C_reg[0]_0 [2]),
        .I5(\S_RAW_VALUE_S_C[12]_i_3_n_0 ),
        .O(\S_RX_OUT_BUFFER_reg[127]_0 [12]));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \S_RAW_VALUE_S_C[12]_i_2 
       (.I0(RAW_VALUE[108]),
        .I1(RAW_VALUE[92]),
        .I2(\S_RAW_VALUE_S_C_reg[0]_0 [1]),
        .I3(RAW_VALUE[76]),
        .I4(\S_RAW_VALUE_S_C_reg[0]_0 [0]),
        .I5(RAW_VALUE[60]),
        .O(\S_RAW_VALUE_S_C[12]_i_2_n_0 ));
  LUT5 #(
    .INIT(32'hAFC0A0C0)) 
    \S_RAW_VALUE_S_C[12]_i_3 
       (.I0(RAW_VALUE[44]),
        .I1(RAW_VALUE[28]),
        .I2(\S_RAW_VALUE_S_C_reg[0]_0 [1]),
        .I3(\S_RAW_VALUE_S_C_reg[0]_0 [0]),
        .I4(RAW_VALUE[12]),
        .O(\S_RAW_VALUE_S_C[12]_i_3_n_0 ));
  LUT6 #(
    .INIT(64'h8F808F8F8F808080)) 
    \S_RAW_VALUE_S_C[13]_i_1 
       (.I0(RAW_VALUE[125]),
        .I1(\S_RAW_VALUE_S_C_reg[0] ),
        .I2(\S_RAW_VALUE_S_C_reg[0]_0 [3]),
        .I3(\S_RAW_VALUE_S_C[13]_i_2_n_0 ),
        .I4(\S_RAW_VALUE_S_C_reg[0]_0 [2]),
        .I5(\S_RAW_VALUE_S_C[13]_i_3_n_0 ),
        .O(\S_RX_OUT_BUFFER_reg[127]_0 [13]));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \S_RAW_VALUE_S_C[13]_i_2 
       (.I0(RAW_VALUE[109]),
        .I1(RAW_VALUE[93]),
        .I2(\S_RAW_VALUE_S_C_reg[0]_0 [1]),
        .I3(RAW_VALUE[77]),
        .I4(\S_RAW_VALUE_S_C_reg[0]_0 [0]),
        .I5(RAW_VALUE[61]),
        .O(\S_RAW_VALUE_S_C[13]_i_2_n_0 ));
  LUT5 #(
    .INIT(32'hAFC0A0C0)) 
    \S_RAW_VALUE_S_C[13]_i_3 
       (.I0(RAW_VALUE[45]),
        .I1(RAW_VALUE[29]),
        .I2(\S_RAW_VALUE_S_C_reg[0]_0 [1]),
        .I3(\S_RAW_VALUE_S_C_reg[0]_0 [0]),
        .I4(RAW_VALUE[13]),
        .O(\S_RAW_VALUE_S_C[13]_i_3_n_0 ));
  LUT6 #(
    .INIT(64'h8F808F8F8F808080)) 
    \S_RAW_VALUE_S_C[14]_i_1 
       (.I0(RAW_VALUE[126]),
        .I1(\S_RAW_VALUE_S_C_reg[0] ),
        .I2(\S_RAW_VALUE_S_C_reg[0]_0 [3]),
        .I3(\S_RAW_VALUE_S_C[14]_i_2_n_0 ),
        .I4(\S_RAW_VALUE_S_C_reg[0]_0 [2]),
        .I5(\S_RAW_VALUE_S_C[14]_i_3_n_0 ),
        .O(\S_RX_OUT_BUFFER_reg[127]_0 [14]));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \S_RAW_VALUE_S_C[14]_i_2 
       (.I0(RAW_VALUE[110]),
        .I1(RAW_VALUE[94]),
        .I2(\S_RAW_VALUE_S_C_reg[0]_0 [1]),
        .I3(RAW_VALUE[78]),
        .I4(\S_RAW_VALUE_S_C_reg[0]_0 [0]),
        .I5(RAW_VALUE[62]),
        .O(\S_RAW_VALUE_S_C[14]_i_2_n_0 ));
  LUT5 #(
    .INIT(32'hAFC0A0C0)) 
    \S_RAW_VALUE_S_C[14]_i_3 
       (.I0(RAW_VALUE[46]),
        .I1(RAW_VALUE[30]),
        .I2(\S_RAW_VALUE_S_C_reg[0]_0 [1]),
        .I3(\S_RAW_VALUE_S_C_reg[0]_0 [0]),
        .I4(RAW_VALUE[14]),
        .O(\S_RAW_VALUE_S_C[14]_i_3_n_0 ));
  LUT6 #(
    .INIT(64'h8F808F8F8F808080)) 
    \S_RAW_VALUE_S_C[15]_i_2 
       (.I0(RAW_VALUE[127]),
        .I1(\S_RAW_VALUE_S_C_reg[0] ),
        .I2(\S_RAW_VALUE_S_C_reg[0]_0 [3]),
        .I3(\S_RAW_VALUE_S_C[15]_i_4_n_0 ),
        .I4(\S_RAW_VALUE_S_C_reg[0]_0 [2]),
        .I5(\S_RAW_VALUE_S_C[15]_i_5_n_0 ),
        .O(\S_RX_OUT_BUFFER_reg[127]_0 [15]));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \S_RAW_VALUE_S_C[15]_i_4 
       (.I0(RAW_VALUE[111]),
        .I1(RAW_VALUE[95]),
        .I2(\S_RAW_VALUE_S_C_reg[0]_0 [1]),
        .I3(RAW_VALUE[79]),
        .I4(\S_RAW_VALUE_S_C_reg[0]_0 [0]),
        .I5(RAW_VALUE[63]),
        .O(\S_RAW_VALUE_S_C[15]_i_4_n_0 ));
  LUT5 #(
    .INIT(32'hAFC0A0C0)) 
    \S_RAW_VALUE_S_C[15]_i_5 
       (.I0(RAW_VALUE[47]),
        .I1(RAW_VALUE[31]),
        .I2(\S_RAW_VALUE_S_C_reg[0]_0 [1]),
        .I3(\S_RAW_VALUE_S_C_reg[0]_0 [0]),
        .I4(RAW_VALUE[15]),
        .O(\S_RAW_VALUE_S_C[15]_i_5_n_0 ));
  LUT6 #(
    .INIT(64'h8F808F8F8F808080)) 
    \S_RAW_VALUE_S_C[1]_i_1 
       (.I0(RAW_VALUE[113]),
        .I1(\S_RAW_VALUE_S_C_reg[0] ),
        .I2(\S_RAW_VALUE_S_C_reg[0]_0 [3]),
        .I3(\S_RAW_VALUE_S_C[1]_i_2_n_0 ),
        .I4(\S_RAW_VALUE_S_C_reg[0]_0 [2]),
        .I5(\S_RAW_VALUE_S_C[1]_i_3_n_0 ),
        .O(\S_RX_OUT_BUFFER_reg[127]_0 [1]));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \S_RAW_VALUE_S_C[1]_i_2 
       (.I0(RAW_VALUE[97]),
        .I1(RAW_VALUE[81]),
        .I2(\S_RAW_VALUE_S_C_reg[0]_0 [1]),
        .I3(RAW_VALUE[65]),
        .I4(\S_RAW_VALUE_S_C_reg[0]_0 [0]),
        .I5(RAW_VALUE[49]),
        .O(\S_RAW_VALUE_S_C[1]_i_2_n_0 ));
  LUT5 #(
    .INIT(32'hAFC0A0C0)) 
    \S_RAW_VALUE_S_C[1]_i_3 
       (.I0(RAW_VALUE[33]),
        .I1(RAW_VALUE[17]),
        .I2(\S_RAW_VALUE_S_C_reg[0]_0 [1]),
        .I3(\S_RAW_VALUE_S_C_reg[0]_0 [0]),
        .I4(RAW_VALUE[1]),
        .O(\S_RAW_VALUE_S_C[1]_i_3_n_0 ));
  LUT6 #(
    .INIT(64'h8F808F8F8F808080)) 
    \S_RAW_VALUE_S_C[2]_i_1 
       (.I0(RAW_VALUE[114]),
        .I1(\S_RAW_VALUE_S_C_reg[0] ),
        .I2(\S_RAW_VALUE_S_C_reg[0]_0 [3]),
        .I3(\S_RAW_VALUE_S_C[2]_i_2_n_0 ),
        .I4(\S_RAW_VALUE_S_C_reg[0]_0 [2]),
        .I5(\S_RAW_VALUE_S_C[2]_i_3_n_0 ),
        .O(\S_RX_OUT_BUFFER_reg[127]_0 [2]));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \S_RAW_VALUE_S_C[2]_i_2 
       (.I0(RAW_VALUE[98]),
        .I1(RAW_VALUE[82]),
        .I2(\S_RAW_VALUE_S_C_reg[0]_0 [1]),
        .I3(RAW_VALUE[66]),
        .I4(\S_RAW_VALUE_S_C_reg[0]_0 [0]),
        .I5(RAW_VALUE[50]),
        .O(\S_RAW_VALUE_S_C[2]_i_2_n_0 ));
  LUT5 #(
    .INIT(32'hAFC0A0C0)) 
    \S_RAW_VALUE_S_C[2]_i_3 
       (.I0(RAW_VALUE[34]),
        .I1(RAW_VALUE[18]),
        .I2(\S_RAW_VALUE_S_C_reg[0]_0 [1]),
        .I3(\S_RAW_VALUE_S_C_reg[0]_0 [0]),
        .I4(RAW_VALUE[2]),
        .O(\S_RAW_VALUE_S_C[2]_i_3_n_0 ));
  LUT6 #(
    .INIT(64'h8F808F8F8F808080)) 
    \S_RAW_VALUE_S_C[3]_i_1 
       (.I0(RAW_VALUE[115]),
        .I1(\S_RAW_VALUE_S_C_reg[0] ),
        .I2(\S_RAW_VALUE_S_C_reg[0]_0 [3]),
        .I3(\S_RAW_VALUE_S_C[3]_i_2_n_0 ),
        .I4(\S_RAW_VALUE_S_C_reg[0]_0 [2]),
        .I5(\S_RAW_VALUE_S_C[3]_i_3_n_0 ),
        .O(\S_RX_OUT_BUFFER_reg[127]_0 [3]));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \S_RAW_VALUE_S_C[3]_i_2 
       (.I0(RAW_VALUE[99]),
        .I1(RAW_VALUE[83]),
        .I2(\S_RAW_VALUE_S_C_reg[0]_0 [1]),
        .I3(RAW_VALUE[67]),
        .I4(\S_RAW_VALUE_S_C_reg[0]_0 [0]),
        .I5(RAW_VALUE[51]),
        .O(\S_RAW_VALUE_S_C[3]_i_2_n_0 ));
  LUT5 #(
    .INIT(32'hAFC0A0C0)) 
    \S_RAW_VALUE_S_C[3]_i_3 
       (.I0(RAW_VALUE[35]),
        .I1(RAW_VALUE[19]),
        .I2(\S_RAW_VALUE_S_C_reg[0]_0 [1]),
        .I3(\S_RAW_VALUE_S_C_reg[0]_0 [0]),
        .I4(RAW_VALUE[3]),
        .O(\S_RAW_VALUE_S_C[3]_i_3_n_0 ));
  LUT6 #(
    .INIT(64'h8F808F8F8F808080)) 
    \S_RAW_VALUE_S_C[4]_i_1 
       (.I0(RAW_VALUE[116]),
        .I1(\S_RAW_VALUE_S_C_reg[0] ),
        .I2(\S_RAW_VALUE_S_C_reg[0]_0 [3]),
        .I3(\S_RAW_VALUE_S_C[4]_i_2_n_0 ),
        .I4(\S_RAW_VALUE_S_C_reg[0]_0 [2]),
        .I5(\S_RAW_VALUE_S_C[4]_i_3_n_0 ),
        .O(\S_RX_OUT_BUFFER_reg[127]_0 [4]));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \S_RAW_VALUE_S_C[4]_i_2 
       (.I0(RAW_VALUE[100]),
        .I1(RAW_VALUE[84]),
        .I2(\S_RAW_VALUE_S_C_reg[0]_0 [1]),
        .I3(RAW_VALUE[68]),
        .I4(\S_RAW_VALUE_S_C_reg[0]_0 [0]),
        .I5(RAW_VALUE[52]),
        .O(\S_RAW_VALUE_S_C[4]_i_2_n_0 ));
  LUT5 #(
    .INIT(32'hAFC0A0C0)) 
    \S_RAW_VALUE_S_C[4]_i_3 
       (.I0(RAW_VALUE[36]),
        .I1(RAW_VALUE[20]),
        .I2(\S_RAW_VALUE_S_C_reg[0]_0 [1]),
        .I3(\S_RAW_VALUE_S_C_reg[0]_0 [0]),
        .I4(RAW_VALUE[4]),
        .O(\S_RAW_VALUE_S_C[4]_i_3_n_0 ));
  LUT6 #(
    .INIT(64'h8F808F8F8F808080)) 
    \S_RAW_VALUE_S_C[5]_i_1 
       (.I0(RAW_VALUE[117]),
        .I1(\S_RAW_VALUE_S_C_reg[0] ),
        .I2(\S_RAW_VALUE_S_C_reg[0]_0 [3]),
        .I3(\S_RAW_VALUE_S_C[5]_i_2_n_0 ),
        .I4(\S_RAW_VALUE_S_C_reg[0]_0 [2]),
        .I5(\S_RAW_VALUE_S_C[5]_i_3_n_0 ),
        .O(\S_RX_OUT_BUFFER_reg[127]_0 [5]));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \S_RAW_VALUE_S_C[5]_i_2 
       (.I0(RAW_VALUE[101]),
        .I1(RAW_VALUE[85]),
        .I2(\S_RAW_VALUE_S_C_reg[0]_0 [1]),
        .I3(RAW_VALUE[69]),
        .I4(\S_RAW_VALUE_S_C_reg[0]_0 [0]),
        .I5(RAW_VALUE[53]),
        .O(\S_RAW_VALUE_S_C[5]_i_2_n_0 ));
  LUT5 #(
    .INIT(32'hAFC0A0C0)) 
    \S_RAW_VALUE_S_C[5]_i_3 
       (.I0(RAW_VALUE[37]),
        .I1(RAW_VALUE[21]),
        .I2(\S_RAW_VALUE_S_C_reg[0]_0 [1]),
        .I3(\S_RAW_VALUE_S_C_reg[0]_0 [0]),
        .I4(RAW_VALUE[5]),
        .O(\S_RAW_VALUE_S_C[5]_i_3_n_0 ));
  LUT6 #(
    .INIT(64'h8F808F8F8F808080)) 
    \S_RAW_VALUE_S_C[6]_i_1 
       (.I0(RAW_VALUE[118]),
        .I1(\S_RAW_VALUE_S_C_reg[0] ),
        .I2(\S_RAW_VALUE_S_C_reg[0]_0 [3]),
        .I3(\S_RAW_VALUE_S_C[6]_i_2_n_0 ),
        .I4(\S_RAW_VALUE_S_C_reg[0]_0 [2]),
        .I5(\S_RAW_VALUE_S_C[6]_i_3_n_0 ),
        .O(\S_RX_OUT_BUFFER_reg[127]_0 [6]));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \S_RAW_VALUE_S_C[6]_i_2 
       (.I0(RAW_VALUE[102]),
        .I1(RAW_VALUE[86]),
        .I2(\S_RAW_VALUE_S_C_reg[0]_0 [1]),
        .I3(RAW_VALUE[70]),
        .I4(\S_RAW_VALUE_S_C_reg[0]_0 [0]),
        .I5(RAW_VALUE[54]),
        .O(\S_RAW_VALUE_S_C[6]_i_2_n_0 ));
  LUT5 #(
    .INIT(32'hAFC0A0C0)) 
    \S_RAW_VALUE_S_C[6]_i_3 
       (.I0(RAW_VALUE[38]),
        .I1(RAW_VALUE[22]),
        .I2(\S_RAW_VALUE_S_C_reg[0]_0 [1]),
        .I3(\S_RAW_VALUE_S_C_reg[0]_0 [0]),
        .I4(RAW_VALUE[6]),
        .O(\S_RAW_VALUE_S_C[6]_i_3_n_0 ));
  LUT6 #(
    .INIT(64'h8F808F8F8F808080)) 
    \S_RAW_VALUE_S_C[7]_i_1 
       (.I0(RAW_VALUE[119]),
        .I1(\S_RAW_VALUE_S_C_reg[0] ),
        .I2(\S_RAW_VALUE_S_C_reg[0]_0 [3]),
        .I3(\S_RAW_VALUE_S_C[7]_i_2_n_0 ),
        .I4(\S_RAW_VALUE_S_C_reg[0]_0 [2]),
        .I5(\S_RAW_VALUE_S_C[7]_i_3_n_0 ),
        .O(\S_RX_OUT_BUFFER_reg[127]_0 [7]));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \S_RAW_VALUE_S_C[7]_i_2 
       (.I0(RAW_VALUE[103]),
        .I1(RAW_VALUE[87]),
        .I2(\S_RAW_VALUE_S_C_reg[0]_0 [1]),
        .I3(RAW_VALUE[71]),
        .I4(\S_RAW_VALUE_S_C_reg[0]_0 [0]),
        .I5(RAW_VALUE[55]),
        .O(\S_RAW_VALUE_S_C[7]_i_2_n_0 ));
  LUT5 #(
    .INIT(32'hAFC0A0C0)) 
    \S_RAW_VALUE_S_C[7]_i_3 
       (.I0(RAW_VALUE[39]),
        .I1(RAW_VALUE[23]),
        .I2(\S_RAW_VALUE_S_C_reg[0]_0 [1]),
        .I3(\S_RAW_VALUE_S_C_reg[0]_0 [0]),
        .I4(RAW_VALUE[7]),
        .O(\S_RAW_VALUE_S_C[7]_i_3_n_0 ));
  LUT6 #(
    .INIT(64'h8F808F8F8F808080)) 
    \S_RAW_VALUE_S_C[8]_i_1 
       (.I0(RAW_VALUE[120]),
        .I1(\S_RAW_VALUE_S_C_reg[0] ),
        .I2(\S_RAW_VALUE_S_C_reg[0]_0 [3]),
        .I3(\S_RAW_VALUE_S_C[8]_i_2_n_0 ),
        .I4(\S_RAW_VALUE_S_C_reg[0]_0 [2]),
        .I5(\S_RAW_VALUE_S_C[8]_i_3_n_0 ),
        .O(\S_RX_OUT_BUFFER_reg[127]_0 [8]));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \S_RAW_VALUE_S_C[8]_i_2 
       (.I0(RAW_VALUE[104]),
        .I1(RAW_VALUE[88]),
        .I2(\S_RAW_VALUE_S_C_reg[0]_0 [1]),
        .I3(RAW_VALUE[72]),
        .I4(\S_RAW_VALUE_S_C_reg[0]_0 [0]),
        .I5(RAW_VALUE[56]),
        .O(\S_RAW_VALUE_S_C[8]_i_2_n_0 ));
  LUT5 #(
    .INIT(32'hAFC0A0C0)) 
    \S_RAW_VALUE_S_C[8]_i_3 
       (.I0(RAW_VALUE[40]),
        .I1(RAW_VALUE[24]),
        .I2(\S_RAW_VALUE_S_C_reg[0]_0 [1]),
        .I3(\S_RAW_VALUE_S_C_reg[0]_0 [0]),
        .I4(RAW_VALUE[8]),
        .O(\S_RAW_VALUE_S_C[8]_i_3_n_0 ));
  LUT6 #(
    .INIT(64'h8F808F8F8F808080)) 
    \S_RAW_VALUE_S_C[9]_i_1 
       (.I0(RAW_VALUE[121]),
        .I1(\S_RAW_VALUE_S_C_reg[0] ),
        .I2(\S_RAW_VALUE_S_C_reg[0]_0 [3]),
        .I3(\S_RAW_VALUE_S_C[9]_i_2_n_0 ),
        .I4(\S_RAW_VALUE_S_C_reg[0]_0 [2]),
        .I5(\S_RAW_VALUE_S_C[9]_i_3_n_0 ),
        .O(\S_RX_OUT_BUFFER_reg[127]_0 [9]));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \S_RAW_VALUE_S_C[9]_i_2 
       (.I0(RAW_VALUE[105]),
        .I1(RAW_VALUE[89]),
        .I2(\S_RAW_VALUE_S_C_reg[0]_0 [1]),
        .I3(RAW_VALUE[73]),
        .I4(\S_RAW_VALUE_S_C_reg[0]_0 [0]),
        .I5(RAW_VALUE[57]),
        .O(\S_RAW_VALUE_S_C[9]_i_2_n_0 ));
  LUT5 #(
    .INIT(32'hAFC0A0C0)) 
    \S_RAW_VALUE_S_C[9]_i_3 
       (.I0(RAW_VALUE[41]),
        .I1(RAW_VALUE[25]),
        .I2(\S_RAW_VALUE_S_C_reg[0]_0 [1]),
        .I3(\S_RAW_VALUE_S_C_reg[0]_0 [0]),
        .I4(RAW_VALUE[9]),
        .O(\S_RAW_VALUE_S_C[9]_i_3_n_0 ));
  LUT6 #(
    .INIT(64'h00000A3000000A00)) 
    \S_RX_BUFFER[127]_i_1 
       (.I0(nxtstate1),
        .I1(S_CPHA_reg_n_0),
        .I2(curstate[0]),
        .I3(curstate[1]),
        .I4(curstate[2]),
        .I5(SS_OUT_N_i_2_n_0),
        .O(S_RX_BUFFER));
  FDRE \S_RX_BUFFER_reg[0] 
       (.C(s00_axi_aclk),
        .CE(S_RX_BUFFER),
        .D(\S_RX_BUFFER_reg[112]_0 [0]),
        .Q(p_0_out[1]),
        .R(RSTP));
  FDRE \S_RX_BUFFER_reg[100] 
       (.C(s00_axi_aclk),
        .CE(S_RX_BUFFER),
        .D(p_0_out[100]),
        .Q(p_0_out[101]),
        .R(RSTP));
  FDRE \S_RX_BUFFER_reg[101] 
       (.C(s00_axi_aclk),
        .CE(S_RX_BUFFER),
        .D(p_0_out[101]),
        .Q(p_0_out[102]),
        .R(RSTP));
  FDRE \S_RX_BUFFER_reg[102] 
       (.C(s00_axi_aclk),
        .CE(S_RX_BUFFER),
        .D(p_0_out[102]),
        .Q(p_0_out[103]),
        .R(RSTP));
  FDRE \S_RX_BUFFER_reg[103] 
       (.C(s00_axi_aclk),
        .CE(S_RX_BUFFER),
        .D(p_0_out[103]),
        .Q(p_0_out[104]),
        .R(RSTP));
  FDRE \S_RX_BUFFER_reg[104] 
       (.C(s00_axi_aclk),
        .CE(S_RX_BUFFER),
        .D(p_0_out[104]),
        .Q(p_0_out[105]),
        .R(RSTP));
  FDRE \S_RX_BUFFER_reg[105] 
       (.C(s00_axi_aclk),
        .CE(S_RX_BUFFER),
        .D(p_0_out[105]),
        .Q(p_0_out[106]),
        .R(RSTP));
  FDRE \S_RX_BUFFER_reg[106] 
       (.C(s00_axi_aclk),
        .CE(S_RX_BUFFER),
        .D(p_0_out[106]),
        .Q(p_0_out[107]),
        .R(RSTP));
  FDRE \S_RX_BUFFER_reg[107] 
       (.C(s00_axi_aclk),
        .CE(S_RX_BUFFER),
        .D(p_0_out[107]),
        .Q(p_0_out[108]),
        .R(RSTP));
  FDRE \S_RX_BUFFER_reg[108] 
       (.C(s00_axi_aclk),
        .CE(S_RX_BUFFER),
        .D(p_0_out[108]),
        .Q(p_0_out[109]),
        .R(RSTP));
  FDRE \S_RX_BUFFER_reg[109] 
       (.C(s00_axi_aclk),
        .CE(S_RX_BUFFER),
        .D(p_0_out[109]),
        .Q(p_0_out[110]),
        .R(RSTP));
  FDRE \S_RX_BUFFER_reg[10] 
       (.C(s00_axi_aclk),
        .CE(S_RX_BUFFER),
        .D(p_0_out[10]),
        .Q(p_0_out[11]),
        .R(RSTP));
  FDRE \S_RX_BUFFER_reg[110] 
       (.C(s00_axi_aclk),
        .CE(S_RX_BUFFER),
        .D(p_0_out[110]),
        .Q(p_0_out[111]),
        .R(RSTP));
  FDRE \S_RX_BUFFER_reg[111] 
       (.C(s00_axi_aclk),
        .CE(S_RX_BUFFER),
        .D(p_0_out[111]),
        .Q(\S_RX_BUFFER_reg_n_0_[111] ),
        .R(RSTP));
  FDRE \S_RX_BUFFER_reg[112] 
       (.C(s00_axi_aclk),
        .CE(S_RX_BUFFER),
        .D(\S_RX_BUFFER_reg[112]_0 [7]),
        .Q(p_0_out[113]),
        .R(RSTP));
  FDRE \S_RX_BUFFER_reg[113] 
       (.C(s00_axi_aclk),
        .CE(S_RX_BUFFER),
        .D(p_0_out[113]),
        .Q(p_0_out[114]),
        .R(RSTP));
  FDRE \S_RX_BUFFER_reg[114] 
       (.C(s00_axi_aclk),
        .CE(S_RX_BUFFER),
        .D(p_0_out[114]),
        .Q(p_0_out[115]),
        .R(RSTP));
  FDRE \S_RX_BUFFER_reg[115] 
       (.C(s00_axi_aclk),
        .CE(S_RX_BUFFER),
        .D(p_0_out[115]),
        .Q(p_0_out[116]),
        .R(RSTP));
  FDRE \S_RX_BUFFER_reg[116] 
       (.C(s00_axi_aclk),
        .CE(S_RX_BUFFER),
        .D(p_0_out[116]),
        .Q(p_0_out[117]),
        .R(RSTP));
  FDRE \S_RX_BUFFER_reg[117] 
       (.C(s00_axi_aclk),
        .CE(S_RX_BUFFER),
        .D(p_0_out[117]),
        .Q(p_0_out[118]),
        .R(RSTP));
  FDRE \S_RX_BUFFER_reg[118] 
       (.C(s00_axi_aclk),
        .CE(S_RX_BUFFER),
        .D(p_0_out[118]),
        .Q(p_0_out[119]),
        .R(RSTP));
  FDRE \S_RX_BUFFER_reg[119] 
       (.C(s00_axi_aclk),
        .CE(S_RX_BUFFER),
        .D(p_0_out[119]),
        .Q(p_0_out[120]),
        .R(RSTP));
  FDRE \S_RX_BUFFER_reg[11] 
       (.C(s00_axi_aclk),
        .CE(S_RX_BUFFER),
        .D(p_0_out[11]),
        .Q(p_0_out[12]),
        .R(RSTP));
  FDRE \S_RX_BUFFER_reg[120] 
       (.C(s00_axi_aclk),
        .CE(S_RX_BUFFER),
        .D(p_0_out[120]),
        .Q(p_0_out[121]),
        .R(RSTP));
  FDRE \S_RX_BUFFER_reg[121] 
       (.C(s00_axi_aclk),
        .CE(S_RX_BUFFER),
        .D(p_0_out[121]),
        .Q(p_0_out[122]),
        .R(RSTP));
  FDRE \S_RX_BUFFER_reg[122] 
       (.C(s00_axi_aclk),
        .CE(S_RX_BUFFER),
        .D(p_0_out[122]),
        .Q(p_0_out[123]),
        .R(RSTP));
  FDRE \S_RX_BUFFER_reg[123] 
       (.C(s00_axi_aclk),
        .CE(S_RX_BUFFER),
        .D(p_0_out[123]),
        .Q(p_0_out[124]),
        .R(RSTP));
  FDRE \S_RX_BUFFER_reg[124] 
       (.C(s00_axi_aclk),
        .CE(S_RX_BUFFER),
        .D(p_0_out[124]),
        .Q(p_0_out[125]),
        .R(RSTP));
  FDRE \S_RX_BUFFER_reg[125] 
       (.C(s00_axi_aclk),
        .CE(S_RX_BUFFER),
        .D(p_0_out[125]),
        .Q(p_0_out[126]),
        .R(RSTP));
  FDRE \S_RX_BUFFER_reg[126] 
       (.C(s00_axi_aclk),
        .CE(S_RX_BUFFER),
        .D(p_0_out[126]),
        .Q(p_0_out[127]),
        .R(RSTP));
  FDRE \S_RX_BUFFER_reg[127] 
       (.C(s00_axi_aclk),
        .CE(S_RX_BUFFER),
        .D(p_0_out[127]),
        .Q(\S_RX_BUFFER_reg_n_0_[127] ),
        .R(RSTP));
  FDRE \S_RX_BUFFER_reg[12] 
       (.C(s00_axi_aclk),
        .CE(S_RX_BUFFER),
        .D(p_0_out[12]),
        .Q(p_0_out[13]),
        .R(RSTP));
  FDRE \S_RX_BUFFER_reg[13] 
       (.C(s00_axi_aclk),
        .CE(S_RX_BUFFER),
        .D(p_0_out[13]),
        .Q(p_0_out[14]),
        .R(RSTP));
  FDRE \S_RX_BUFFER_reg[14] 
       (.C(s00_axi_aclk),
        .CE(S_RX_BUFFER),
        .D(p_0_out[14]),
        .Q(p_0_out[15]),
        .R(RSTP));
  FDRE \S_RX_BUFFER_reg[15] 
       (.C(s00_axi_aclk),
        .CE(S_RX_BUFFER),
        .D(p_0_out[15]),
        .Q(\S_RX_BUFFER_reg_n_0_[15] ),
        .R(RSTP));
  FDRE \S_RX_BUFFER_reg[16] 
       (.C(s00_axi_aclk),
        .CE(S_RX_BUFFER),
        .D(\S_RX_BUFFER_reg[112]_0 [1]),
        .Q(p_0_out[17]),
        .R(RSTP));
  FDRE \S_RX_BUFFER_reg[17] 
       (.C(s00_axi_aclk),
        .CE(S_RX_BUFFER),
        .D(p_0_out[17]),
        .Q(p_0_out[18]),
        .R(RSTP));
  FDRE \S_RX_BUFFER_reg[18] 
       (.C(s00_axi_aclk),
        .CE(S_RX_BUFFER),
        .D(p_0_out[18]),
        .Q(p_0_out[19]),
        .R(RSTP));
  FDRE \S_RX_BUFFER_reg[19] 
       (.C(s00_axi_aclk),
        .CE(S_RX_BUFFER),
        .D(p_0_out[19]),
        .Q(p_0_out[20]),
        .R(RSTP));
  FDRE \S_RX_BUFFER_reg[1] 
       (.C(s00_axi_aclk),
        .CE(S_RX_BUFFER),
        .D(p_0_out[1]),
        .Q(p_0_out[2]),
        .R(RSTP));
  FDRE \S_RX_BUFFER_reg[20] 
       (.C(s00_axi_aclk),
        .CE(S_RX_BUFFER),
        .D(p_0_out[20]),
        .Q(p_0_out[21]),
        .R(RSTP));
  FDRE \S_RX_BUFFER_reg[21] 
       (.C(s00_axi_aclk),
        .CE(S_RX_BUFFER),
        .D(p_0_out[21]),
        .Q(p_0_out[22]),
        .R(RSTP));
  FDRE \S_RX_BUFFER_reg[22] 
       (.C(s00_axi_aclk),
        .CE(S_RX_BUFFER),
        .D(p_0_out[22]),
        .Q(p_0_out[23]),
        .R(RSTP));
  FDRE \S_RX_BUFFER_reg[23] 
       (.C(s00_axi_aclk),
        .CE(S_RX_BUFFER),
        .D(p_0_out[23]),
        .Q(p_0_out[24]),
        .R(RSTP));
  FDRE \S_RX_BUFFER_reg[24] 
       (.C(s00_axi_aclk),
        .CE(S_RX_BUFFER),
        .D(p_0_out[24]),
        .Q(p_0_out[25]),
        .R(RSTP));
  FDRE \S_RX_BUFFER_reg[25] 
       (.C(s00_axi_aclk),
        .CE(S_RX_BUFFER),
        .D(p_0_out[25]),
        .Q(p_0_out[26]),
        .R(RSTP));
  FDRE \S_RX_BUFFER_reg[26] 
       (.C(s00_axi_aclk),
        .CE(S_RX_BUFFER),
        .D(p_0_out[26]),
        .Q(p_0_out[27]),
        .R(RSTP));
  FDRE \S_RX_BUFFER_reg[27] 
       (.C(s00_axi_aclk),
        .CE(S_RX_BUFFER),
        .D(p_0_out[27]),
        .Q(p_0_out[28]),
        .R(RSTP));
  FDRE \S_RX_BUFFER_reg[28] 
       (.C(s00_axi_aclk),
        .CE(S_RX_BUFFER),
        .D(p_0_out[28]),
        .Q(p_0_out[29]),
        .R(RSTP));
  FDRE \S_RX_BUFFER_reg[29] 
       (.C(s00_axi_aclk),
        .CE(S_RX_BUFFER),
        .D(p_0_out[29]),
        .Q(p_0_out[30]),
        .R(RSTP));
  FDRE \S_RX_BUFFER_reg[2] 
       (.C(s00_axi_aclk),
        .CE(S_RX_BUFFER),
        .D(p_0_out[2]),
        .Q(p_0_out[3]),
        .R(RSTP));
  FDRE \S_RX_BUFFER_reg[30] 
       (.C(s00_axi_aclk),
        .CE(S_RX_BUFFER),
        .D(p_0_out[30]),
        .Q(p_0_out[31]),
        .R(RSTP));
  FDRE \S_RX_BUFFER_reg[31] 
       (.C(s00_axi_aclk),
        .CE(S_RX_BUFFER),
        .D(p_0_out[31]),
        .Q(\S_RX_BUFFER_reg_n_0_[31] ),
        .R(RSTP));
  FDRE \S_RX_BUFFER_reg[32] 
       (.C(s00_axi_aclk),
        .CE(S_RX_BUFFER),
        .D(\S_RX_BUFFER_reg[112]_0 [2]),
        .Q(p_0_out[33]),
        .R(RSTP));
  FDRE \S_RX_BUFFER_reg[33] 
       (.C(s00_axi_aclk),
        .CE(S_RX_BUFFER),
        .D(p_0_out[33]),
        .Q(p_0_out[34]),
        .R(RSTP));
  FDRE \S_RX_BUFFER_reg[34] 
       (.C(s00_axi_aclk),
        .CE(S_RX_BUFFER),
        .D(p_0_out[34]),
        .Q(p_0_out[35]),
        .R(RSTP));
  FDRE \S_RX_BUFFER_reg[35] 
       (.C(s00_axi_aclk),
        .CE(S_RX_BUFFER),
        .D(p_0_out[35]),
        .Q(p_0_out[36]),
        .R(RSTP));
  FDRE \S_RX_BUFFER_reg[36] 
       (.C(s00_axi_aclk),
        .CE(S_RX_BUFFER),
        .D(p_0_out[36]),
        .Q(p_0_out[37]),
        .R(RSTP));
  FDRE \S_RX_BUFFER_reg[37] 
       (.C(s00_axi_aclk),
        .CE(S_RX_BUFFER),
        .D(p_0_out[37]),
        .Q(p_0_out[38]),
        .R(RSTP));
  FDRE \S_RX_BUFFER_reg[38] 
       (.C(s00_axi_aclk),
        .CE(S_RX_BUFFER),
        .D(p_0_out[38]),
        .Q(p_0_out[39]),
        .R(RSTP));
  FDRE \S_RX_BUFFER_reg[39] 
       (.C(s00_axi_aclk),
        .CE(S_RX_BUFFER),
        .D(p_0_out[39]),
        .Q(p_0_out[40]),
        .R(RSTP));
  FDRE \S_RX_BUFFER_reg[3] 
       (.C(s00_axi_aclk),
        .CE(S_RX_BUFFER),
        .D(p_0_out[3]),
        .Q(p_0_out[4]),
        .R(RSTP));
  FDRE \S_RX_BUFFER_reg[40] 
       (.C(s00_axi_aclk),
        .CE(S_RX_BUFFER),
        .D(p_0_out[40]),
        .Q(p_0_out[41]),
        .R(RSTP));
  FDRE \S_RX_BUFFER_reg[41] 
       (.C(s00_axi_aclk),
        .CE(S_RX_BUFFER),
        .D(p_0_out[41]),
        .Q(p_0_out[42]),
        .R(RSTP));
  FDRE \S_RX_BUFFER_reg[42] 
       (.C(s00_axi_aclk),
        .CE(S_RX_BUFFER),
        .D(p_0_out[42]),
        .Q(p_0_out[43]),
        .R(RSTP));
  FDRE \S_RX_BUFFER_reg[43] 
       (.C(s00_axi_aclk),
        .CE(S_RX_BUFFER),
        .D(p_0_out[43]),
        .Q(p_0_out[44]),
        .R(RSTP));
  FDRE \S_RX_BUFFER_reg[44] 
       (.C(s00_axi_aclk),
        .CE(S_RX_BUFFER),
        .D(p_0_out[44]),
        .Q(p_0_out[45]),
        .R(RSTP));
  FDRE \S_RX_BUFFER_reg[45] 
       (.C(s00_axi_aclk),
        .CE(S_RX_BUFFER),
        .D(p_0_out[45]),
        .Q(p_0_out[46]),
        .R(RSTP));
  FDRE \S_RX_BUFFER_reg[46] 
       (.C(s00_axi_aclk),
        .CE(S_RX_BUFFER),
        .D(p_0_out[46]),
        .Q(p_0_out[47]),
        .R(RSTP));
  FDRE \S_RX_BUFFER_reg[47] 
       (.C(s00_axi_aclk),
        .CE(S_RX_BUFFER),
        .D(p_0_out[47]),
        .Q(\S_RX_BUFFER_reg_n_0_[47] ),
        .R(RSTP));
  FDRE \S_RX_BUFFER_reg[48] 
       (.C(s00_axi_aclk),
        .CE(S_RX_BUFFER),
        .D(\S_RX_BUFFER_reg[112]_0 [3]),
        .Q(p_0_out[49]),
        .R(RSTP));
  FDRE \S_RX_BUFFER_reg[49] 
       (.C(s00_axi_aclk),
        .CE(S_RX_BUFFER),
        .D(p_0_out[49]),
        .Q(p_0_out[50]),
        .R(RSTP));
  FDRE \S_RX_BUFFER_reg[4] 
       (.C(s00_axi_aclk),
        .CE(S_RX_BUFFER),
        .D(p_0_out[4]),
        .Q(p_0_out[5]),
        .R(RSTP));
  FDRE \S_RX_BUFFER_reg[50] 
       (.C(s00_axi_aclk),
        .CE(S_RX_BUFFER),
        .D(p_0_out[50]),
        .Q(p_0_out[51]),
        .R(RSTP));
  FDRE \S_RX_BUFFER_reg[51] 
       (.C(s00_axi_aclk),
        .CE(S_RX_BUFFER),
        .D(p_0_out[51]),
        .Q(p_0_out[52]),
        .R(RSTP));
  FDRE \S_RX_BUFFER_reg[52] 
       (.C(s00_axi_aclk),
        .CE(S_RX_BUFFER),
        .D(p_0_out[52]),
        .Q(p_0_out[53]),
        .R(RSTP));
  FDRE \S_RX_BUFFER_reg[53] 
       (.C(s00_axi_aclk),
        .CE(S_RX_BUFFER),
        .D(p_0_out[53]),
        .Q(p_0_out[54]),
        .R(RSTP));
  FDRE \S_RX_BUFFER_reg[54] 
       (.C(s00_axi_aclk),
        .CE(S_RX_BUFFER),
        .D(p_0_out[54]),
        .Q(p_0_out[55]),
        .R(RSTP));
  FDRE \S_RX_BUFFER_reg[55] 
       (.C(s00_axi_aclk),
        .CE(S_RX_BUFFER),
        .D(p_0_out[55]),
        .Q(p_0_out[56]),
        .R(RSTP));
  FDRE \S_RX_BUFFER_reg[56] 
       (.C(s00_axi_aclk),
        .CE(S_RX_BUFFER),
        .D(p_0_out[56]),
        .Q(p_0_out[57]),
        .R(RSTP));
  FDRE \S_RX_BUFFER_reg[57] 
       (.C(s00_axi_aclk),
        .CE(S_RX_BUFFER),
        .D(p_0_out[57]),
        .Q(p_0_out[58]),
        .R(RSTP));
  FDRE \S_RX_BUFFER_reg[58] 
       (.C(s00_axi_aclk),
        .CE(S_RX_BUFFER),
        .D(p_0_out[58]),
        .Q(p_0_out[59]),
        .R(RSTP));
  FDRE \S_RX_BUFFER_reg[59] 
       (.C(s00_axi_aclk),
        .CE(S_RX_BUFFER),
        .D(p_0_out[59]),
        .Q(p_0_out[60]),
        .R(RSTP));
  FDRE \S_RX_BUFFER_reg[5] 
       (.C(s00_axi_aclk),
        .CE(S_RX_BUFFER),
        .D(p_0_out[5]),
        .Q(p_0_out[6]),
        .R(RSTP));
  FDRE \S_RX_BUFFER_reg[60] 
       (.C(s00_axi_aclk),
        .CE(S_RX_BUFFER),
        .D(p_0_out[60]),
        .Q(p_0_out[61]),
        .R(RSTP));
  FDRE \S_RX_BUFFER_reg[61] 
       (.C(s00_axi_aclk),
        .CE(S_RX_BUFFER),
        .D(p_0_out[61]),
        .Q(p_0_out[62]),
        .R(RSTP));
  FDRE \S_RX_BUFFER_reg[62] 
       (.C(s00_axi_aclk),
        .CE(S_RX_BUFFER),
        .D(p_0_out[62]),
        .Q(p_0_out[63]),
        .R(RSTP));
  FDRE \S_RX_BUFFER_reg[63] 
       (.C(s00_axi_aclk),
        .CE(S_RX_BUFFER),
        .D(p_0_out[63]),
        .Q(\S_RX_BUFFER_reg_n_0_[63] ),
        .R(RSTP));
  FDRE \S_RX_BUFFER_reg[64] 
       (.C(s00_axi_aclk),
        .CE(S_RX_BUFFER),
        .D(\S_RX_BUFFER_reg[112]_0 [4]),
        .Q(p_0_out[65]),
        .R(RSTP));
  FDRE \S_RX_BUFFER_reg[65] 
       (.C(s00_axi_aclk),
        .CE(S_RX_BUFFER),
        .D(p_0_out[65]),
        .Q(p_0_out[66]),
        .R(RSTP));
  FDRE \S_RX_BUFFER_reg[66] 
       (.C(s00_axi_aclk),
        .CE(S_RX_BUFFER),
        .D(p_0_out[66]),
        .Q(p_0_out[67]),
        .R(RSTP));
  FDRE \S_RX_BUFFER_reg[67] 
       (.C(s00_axi_aclk),
        .CE(S_RX_BUFFER),
        .D(p_0_out[67]),
        .Q(p_0_out[68]),
        .R(RSTP));
  FDRE \S_RX_BUFFER_reg[68] 
       (.C(s00_axi_aclk),
        .CE(S_RX_BUFFER),
        .D(p_0_out[68]),
        .Q(p_0_out[69]),
        .R(RSTP));
  FDRE \S_RX_BUFFER_reg[69] 
       (.C(s00_axi_aclk),
        .CE(S_RX_BUFFER),
        .D(p_0_out[69]),
        .Q(p_0_out[70]),
        .R(RSTP));
  FDRE \S_RX_BUFFER_reg[6] 
       (.C(s00_axi_aclk),
        .CE(S_RX_BUFFER),
        .D(p_0_out[6]),
        .Q(p_0_out[7]),
        .R(RSTP));
  FDRE \S_RX_BUFFER_reg[70] 
       (.C(s00_axi_aclk),
        .CE(S_RX_BUFFER),
        .D(p_0_out[70]),
        .Q(p_0_out[71]),
        .R(RSTP));
  FDRE \S_RX_BUFFER_reg[71] 
       (.C(s00_axi_aclk),
        .CE(S_RX_BUFFER),
        .D(p_0_out[71]),
        .Q(p_0_out[72]),
        .R(RSTP));
  FDRE \S_RX_BUFFER_reg[72] 
       (.C(s00_axi_aclk),
        .CE(S_RX_BUFFER),
        .D(p_0_out[72]),
        .Q(p_0_out[73]),
        .R(RSTP));
  FDRE \S_RX_BUFFER_reg[73] 
       (.C(s00_axi_aclk),
        .CE(S_RX_BUFFER),
        .D(p_0_out[73]),
        .Q(p_0_out[74]),
        .R(RSTP));
  FDRE \S_RX_BUFFER_reg[74] 
       (.C(s00_axi_aclk),
        .CE(S_RX_BUFFER),
        .D(p_0_out[74]),
        .Q(p_0_out[75]),
        .R(RSTP));
  FDRE \S_RX_BUFFER_reg[75] 
       (.C(s00_axi_aclk),
        .CE(S_RX_BUFFER),
        .D(p_0_out[75]),
        .Q(p_0_out[76]),
        .R(RSTP));
  FDRE \S_RX_BUFFER_reg[76] 
       (.C(s00_axi_aclk),
        .CE(S_RX_BUFFER),
        .D(p_0_out[76]),
        .Q(p_0_out[77]),
        .R(RSTP));
  FDRE \S_RX_BUFFER_reg[77] 
       (.C(s00_axi_aclk),
        .CE(S_RX_BUFFER),
        .D(p_0_out[77]),
        .Q(p_0_out[78]),
        .R(RSTP));
  FDRE \S_RX_BUFFER_reg[78] 
       (.C(s00_axi_aclk),
        .CE(S_RX_BUFFER),
        .D(p_0_out[78]),
        .Q(p_0_out[79]),
        .R(RSTP));
  FDRE \S_RX_BUFFER_reg[79] 
       (.C(s00_axi_aclk),
        .CE(S_RX_BUFFER),
        .D(p_0_out[79]),
        .Q(\S_RX_BUFFER_reg_n_0_[79] ),
        .R(RSTP));
  FDRE \S_RX_BUFFER_reg[7] 
       (.C(s00_axi_aclk),
        .CE(S_RX_BUFFER),
        .D(p_0_out[7]),
        .Q(p_0_out[8]),
        .R(RSTP));
  FDRE \S_RX_BUFFER_reg[80] 
       (.C(s00_axi_aclk),
        .CE(S_RX_BUFFER),
        .D(\S_RX_BUFFER_reg[112]_0 [5]),
        .Q(p_0_out[81]),
        .R(RSTP));
  FDRE \S_RX_BUFFER_reg[81] 
       (.C(s00_axi_aclk),
        .CE(S_RX_BUFFER),
        .D(p_0_out[81]),
        .Q(p_0_out[82]),
        .R(RSTP));
  FDRE \S_RX_BUFFER_reg[82] 
       (.C(s00_axi_aclk),
        .CE(S_RX_BUFFER),
        .D(p_0_out[82]),
        .Q(p_0_out[83]),
        .R(RSTP));
  FDRE \S_RX_BUFFER_reg[83] 
       (.C(s00_axi_aclk),
        .CE(S_RX_BUFFER),
        .D(p_0_out[83]),
        .Q(p_0_out[84]),
        .R(RSTP));
  FDRE \S_RX_BUFFER_reg[84] 
       (.C(s00_axi_aclk),
        .CE(S_RX_BUFFER),
        .D(p_0_out[84]),
        .Q(p_0_out[85]),
        .R(RSTP));
  FDRE \S_RX_BUFFER_reg[85] 
       (.C(s00_axi_aclk),
        .CE(S_RX_BUFFER),
        .D(p_0_out[85]),
        .Q(p_0_out[86]),
        .R(RSTP));
  FDRE \S_RX_BUFFER_reg[86] 
       (.C(s00_axi_aclk),
        .CE(S_RX_BUFFER),
        .D(p_0_out[86]),
        .Q(p_0_out[87]),
        .R(RSTP));
  FDRE \S_RX_BUFFER_reg[87] 
       (.C(s00_axi_aclk),
        .CE(S_RX_BUFFER),
        .D(p_0_out[87]),
        .Q(p_0_out[88]),
        .R(RSTP));
  FDRE \S_RX_BUFFER_reg[88] 
       (.C(s00_axi_aclk),
        .CE(S_RX_BUFFER),
        .D(p_0_out[88]),
        .Q(p_0_out[89]),
        .R(RSTP));
  FDRE \S_RX_BUFFER_reg[89] 
       (.C(s00_axi_aclk),
        .CE(S_RX_BUFFER),
        .D(p_0_out[89]),
        .Q(p_0_out[90]),
        .R(RSTP));
  FDRE \S_RX_BUFFER_reg[8] 
       (.C(s00_axi_aclk),
        .CE(S_RX_BUFFER),
        .D(p_0_out[8]),
        .Q(p_0_out[9]),
        .R(RSTP));
  FDRE \S_RX_BUFFER_reg[90] 
       (.C(s00_axi_aclk),
        .CE(S_RX_BUFFER),
        .D(p_0_out[90]),
        .Q(p_0_out[91]),
        .R(RSTP));
  FDRE \S_RX_BUFFER_reg[91] 
       (.C(s00_axi_aclk),
        .CE(S_RX_BUFFER),
        .D(p_0_out[91]),
        .Q(p_0_out[92]),
        .R(RSTP));
  FDRE \S_RX_BUFFER_reg[92] 
       (.C(s00_axi_aclk),
        .CE(S_RX_BUFFER),
        .D(p_0_out[92]),
        .Q(p_0_out[93]),
        .R(RSTP));
  FDRE \S_RX_BUFFER_reg[93] 
       (.C(s00_axi_aclk),
        .CE(S_RX_BUFFER),
        .D(p_0_out[93]),
        .Q(p_0_out[94]),
        .R(RSTP));
  FDRE \S_RX_BUFFER_reg[94] 
       (.C(s00_axi_aclk),
        .CE(S_RX_BUFFER),
        .D(p_0_out[94]),
        .Q(p_0_out[95]),
        .R(RSTP));
  FDRE \S_RX_BUFFER_reg[95] 
       (.C(s00_axi_aclk),
        .CE(S_RX_BUFFER),
        .D(p_0_out[95]),
        .Q(\S_RX_BUFFER_reg_n_0_[95] ),
        .R(RSTP));
  FDRE \S_RX_BUFFER_reg[96] 
       (.C(s00_axi_aclk),
        .CE(S_RX_BUFFER),
        .D(\S_RX_BUFFER_reg[112]_0 [6]),
        .Q(p_0_out[97]),
        .R(RSTP));
  FDRE \S_RX_BUFFER_reg[97] 
       (.C(s00_axi_aclk),
        .CE(S_RX_BUFFER),
        .D(p_0_out[97]),
        .Q(p_0_out[98]),
        .R(RSTP));
  FDRE \S_RX_BUFFER_reg[98] 
       (.C(s00_axi_aclk),
        .CE(S_RX_BUFFER),
        .D(p_0_out[98]),
        .Q(p_0_out[99]),
        .R(RSTP));
  FDRE \S_RX_BUFFER_reg[99] 
       (.C(s00_axi_aclk),
        .CE(S_RX_BUFFER),
        .D(p_0_out[99]),
        .Q(p_0_out[100]),
        .R(RSTP));
  FDRE \S_RX_BUFFER_reg[9] 
       (.C(s00_axi_aclk),
        .CE(S_RX_BUFFER),
        .D(p_0_out[9]),
        .Q(p_0_out[10]),
        .R(RSTP));
  LUT4 #(
    .INIT(16'h0080)) 
    \S_RX_OUT_BUFFER[127]_i_2 
       (.I0(\S_RX_OUT_BUFFER[127]_i_3_n_0 ),
        .I1(curstate[0]),
        .I2(curstate[1]),
        .I3(curstate[2]),
        .O(S_RX_OUT_BUFFER));
  LUT6 #(
    .INIT(64'hAAAAAAAAAAAAAAAB)) 
    \S_RX_OUT_BUFFER[127]_i_3 
       (.I0(\S_BIT_COUNT_reg_n_0_[5] ),
        .I1(\S_BIT_COUNT_reg_n_0_[0] ),
        .I2(\S_BIT_COUNT_reg_n_0_[3] ),
        .I3(\S_BIT_COUNT_reg_n_0_[1] ),
        .I4(\S_BIT_COUNT_reg_n_0_[2] ),
        .I5(\S_BIT_COUNT_reg_n_0_[4] ),
        .O(\S_RX_OUT_BUFFER[127]_i_3_n_0 ));
  FDRE \S_RX_OUT_BUFFER_reg[0] 
       (.C(s00_axi_aclk),
        .CE(S_RX_OUT_BUFFER),
        .D(p_0_out[1]),
        .Q(RAW_VALUE[0]),
        .R(RSTP));
  FDRE \S_RX_OUT_BUFFER_reg[100] 
       (.C(s00_axi_aclk),
        .CE(S_RX_OUT_BUFFER),
        .D(p_0_out[101]),
        .Q(RAW_VALUE[100]),
        .R(RSTP));
  FDRE \S_RX_OUT_BUFFER_reg[101] 
       (.C(s00_axi_aclk),
        .CE(S_RX_OUT_BUFFER),
        .D(p_0_out[102]),
        .Q(RAW_VALUE[101]),
        .R(RSTP));
  FDRE \S_RX_OUT_BUFFER_reg[102] 
       (.C(s00_axi_aclk),
        .CE(S_RX_OUT_BUFFER),
        .D(p_0_out[103]),
        .Q(RAW_VALUE[102]),
        .R(RSTP));
  FDRE \S_RX_OUT_BUFFER_reg[103] 
       (.C(s00_axi_aclk),
        .CE(S_RX_OUT_BUFFER),
        .D(p_0_out[104]),
        .Q(RAW_VALUE[103]),
        .R(RSTP));
  FDRE \S_RX_OUT_BUFFER_reg[104] 
       (.C(s00_axi_aclk),
        .CE(S_RX_OUT_BUFFER),
        .D(p_0_out[105]),
        .Q(RAW_VALUE[104]),
        .R(RSTP));
  FDRE \S_RX_OUT_BUFFER_reg[105] 
       (.C(s00_axi_aclk),
        .CE(S_RX_OUT_BUFFER),
        .D(p_0_out[106]),
        .Q(RAW_VALUE[105]),
        .R(RSTP));
  FDRE \S_RX_OUT_BUFFER_reg[106] 
       (.C(s00_axi_aclk),
        .CE(S_RX_OUT_BUFFER),
        .D(p_0_out[107]),
        .Q(RAW_VALUE[106]),
        .R(RSTP));
  FDRE \S_RX_OUT_BUFFER_reg[107] 
       (.C(s00_axi_aclk),
        .CE(S_RX_OUT_BUFFER),
        .D(p_0_out[108]),
        .Q(RAW_VALUE[107]),
        .R(RSTP));
  FDRE \S_RX_OUT_BUFFER_reg[108] 
       (.C(s00_axi_aclk),
        .CE(S_RX_OUT_BUFFER),
        .D(p_0_out[109]),
        .Q(RAW_VALUE[108]),
        .R(RSTP));
  FDRE \S_RX_OUT_BUFFER_reg[109] 
       (.C(s00_axi_aclk),
        .CE(S_RX_OUT_BUFFER),
        .D(p_0_out[110]),
        .Q(RAW_VALUE[109]),
        .R(RSTP));
  FDRE \S_RX_OUT_BUFFER_reg[10] 
       (.C(s00_axi_aclk),
        .CE(S_RX_OUT_BUFFER),
        .D(p_0_out[11]),
        .Q(RAW_VALUE[10]),
        .R(RSTP));
  FDRE \S_RX_OUT_BUFFER_reg[110] 
       (.C(s00_axi_aclk),
        .CE(S_RX_OUT_BUFFER),
        .D(p_0_out[111]),
        .Q(RAW_VALUE[110]),
        .R(RSTP));
  FDRE \S_RX_OUT_BUFFER_reg[111] 
       (.C(s00_axi_aclk),
        .CE(S_RX_OUT_BUFFER),
        .D(\S_RX_BUFFER_reg_n_0_[111] ),
        .Q(RAW_VALUE[111]),
        .R(RSTP));
  FDRE \S_RX_OUT_BUFFER_reg[112] 
       (.C(s00_axi_aclk),
        .CE(S_RX_OUT_BUFFER),
        .D(p_0_out[113]),
        .Q(RAW_VALUE[112]),
        .R(RSTP));
  FDRE \S_RX_OUT_BUFFER_reg[113] 
       (.C(s00_axi_aclk),
        .CE(S_RX_OUT_BUFFER),
        .D(p_0_out[114]),
        .Q(RAW_VALUE[113]),
        .R(RSTP));
  FDRE \S_RX_OUT_BUFFER_reg[114] 
       (.C(s00_axi_aclk),
        .CE(S_RX_OUT_BUFFER),
        .D(p_0_out[115]),
        .Q(RAW_VALUE[114]),
        .R(RSTP));
  FDRE \S_RX_OUT_BUFFER_reg[115] 
       (.C(s00_axi_aclk),
        .CE(S_RX_OUT_BUFFER),
        .D(p_0_out[116]),
        .Q(RAW_VALUE[115]),
        .R(RSTP));
  FDRE \S_RX_OUT_BUFFER_reg[116] 
       (.C(s00_axi_aclk),
        .CE(S_RX_OUT_BUFFER),
        .D(p_0_out[117]),
        .Q(RAW_VALUE[116]),
        .R(RSTP));
  FDRE \S_RX_OUT_BUFFER_reg[117] 
       (.C(s00_axi_aclk),
        .CE(S_RX_OUT_BUFFER),
        .D(p_0_out[118]),
        .Q(RAW_VALUE[117]),
        .R(RSTP));
  FDRE \S_RX_OUT_BUFFER_reg[118] 
       (.C(s00_axi_aclk),
        .CE(S_RX_OUT_BUFFER),
        .D(p_0_out[119]),
        .Q(RAW_VALUE[118]),
        .R(RSTP));
  FDRE \S_RX_OUT_BUFFER_reg[119] 
       (.C(s00_axi_aclk),
        .CE(S_RX_OUT_BUFFER),
        .D(p_0_out[120]),
        .Q(RAW_VALUE[119]),
        .R(RSTP));
  FDRE \S_RX_OUT_BUFFER_reg[11] 
       (.C(s00_axi_aclk),
        .CE(S_RX_OUT_BUFFER),
        .D(p_0_out[12]),
        .Q(RAW_VALUE[11]),
        .R(RSTP));
  FDRE \S_RX_OUT_BUFFER_reg[120] 
       (.C(s00_axi_aclk),
        .CE(S_RX_OUT_BUFFER),
        .D(p_0_out[121]),
        .Q(RAW_VALUE[120]),
        .R(RSTP));
  FDRE \S_RX_OUT_BUFFER_reg[121] 
       (.C(s00_axi_aclk),
        .CE(S_RX_OUT_BUFFER),
        .D(p_0_out[122]),
        .Q(RAW_VALUE[121]),
        .R(RSTP));
  FDRE \S_RX_OUT_BUFFER_reg[122] 
       (.C(s00_axi_aclk),
        .CE(S_RX_OUT_BUFFER),
        .D(p_0_out[123]),
        .Q(RAW_VALUE[122]),
        .R(RSTP));
  FDRE \S_RX_OUT_BUFFER_reg[123] 
       (.C(s00_axi_aclk),
        .CE(S_RX_OUT_BUFFER),
        .D(p_0_out[124]),
        .Q(RAW_VALUE[123]),
        .R(RSTP));
  FDRE \S_RX_OUT_BUFFER_reg[124] 
       (.C(s00_axi_aclk),
        .CE(S_RX_OUT_BUFFER),
        .D(p_0_out[125]),
        .Q(RAW_VALUE[124]),
        .R(RSTP));
  FDRE \S_RX_OUT_BUFFER_reg[125] 
       (.C(s00_axi_aclk),
        .CE(S_RX_OUT_BUFFER),
        .D(p_0_out[126]),
        .Q(RAW_VALUE[125]),
        .R(RSTP));
  FDRE \S_RX_OUT_BUFFER_reg[126] 
       (.C(s00_axi_aclk),
        .CE(S_RX_OUT_BUFFER),
        .D(p_0_out[127]),
        .Q(RAW_VALUE[126]),
        .R(RSTP));
  FDRE \S_RX_OUT_BUFFER_reg[127] 
       (.C(s00_axi_aclk),
        .CE(S_RX_OUT_BUFFER),
        .D(\S_RX_BUFFER_reg_n_0_[127] ),
        .Q(RAW_VALUE[127]),
        .R(RSTP));
  FDRE \S_RX_OUT_BUFFER_reg[12] 
       (.C(s00_axi_aclk),
        .CE(S_RX_OUT_BUFFER),
        .D(p_0_out[13]),
        .Q(RAW_VALUE[12]),
        .R(RSTP));
  FDRE \S_RX_OUT_BUFFER_reg[13] 
       (.C(s00_axi_aclk),
        .CE(S_RX_OUT_BUFFER),
        .D(p_0_out[14]),
        .Q(RAW_VALUE[13]),
        .R(RSTP));
  FDRE \S_RX_OUT_BUFFER_reg[14] 
       (.C(s00_axi_aclk),
        .CE(S_RX_OUT_BUFFER),
        .D(p_0_out[15]),
        .Q(RAW_VALUE[14]),
        .R(RSTP));
  FDRE \S_RX_OUT_BUFFER_reg[15] 
       (.C(s00_axi_aclk),
        .CE(S_RX_OUT_BUFFER),
        .D(\S_RX_BUFFER_reg_n_0_[15] ),
        .Q(RAW_VALUE[15]),
        .R(RSTP));
  FDRE \S_RX_OUT_BUFFER_reg[16] 
       (.C(s00_axi_aclk),
        .CE(S_RX_OUT_BUFFER),
        .D(p_0_out[17]),
        .Q(RAW_VALUE[16]),
        .R(RSTP));
  FDRE \S_RX_OUT_BUFFER_reg[17] 
       (.C(s00_axi_aclk),
        .CE(S_RX_OUT_BUFFER),
        .D(p_0_out[18]),
        .Q(RAW_VALUE[17]),
        .R(RSTP));
  FDRE \S_RX_OUT_BUFFER_reg[18] 
       (.C(s00_axi_aclk),
        .CE(S_RX_OUT_BUFFER),
        .D(p_0_out[19]),
        .Q(RAW_VALUE[18]),
        .R(RSTP));
  FDRE \S_RX_OUT_BUFFER_reg[19] 
       (.C(s00_axi_aclk),
        .CE(S_RX_OUT_BUFFER),
        .D(p_0_out[20]),
        .Q(RAW_VALUE[19]),
        .R(RSTP));
  FDRE \S_RX_OUT_BUFFER_reg[1] 
       (.C(s00_axi_aclk),
        .CE(S_RX_OUT_BUFFER),
        .D(p_0_out[2]),
        .Q(RAW_VALUE[1]),
        .R(RSTP));
  FDRE \S_RX_OUT_BUFFER_reg[20] 
       (.C(s00_axi_aclk),
        .CE(S_RX_OUT_BUFFER),
        .D(p_0_out[21]),
        .Q(RAW_VALUE[20]),
        .R(RSTP));
  FDRE \S_RX_OUT_BUFFER_reg[21] 
       (.C(s00_axi_aclk),
        .CE(S_RX_OUT_BUFFER),
        .D(p_0_out[22]),
        .Q(RAW_VALUE[21]),
        .R(RSTP));
  FDRE \S_RX_OUT_BUFFER_reg[22] 
       (.C(s00_axi_aclk),
        .CE(S_RX_OUT_BUFFER),
        .D(p_0_out[23]),
        .Q(RAW_VALUE[22]),
        .R(RSTP));
  FDRE \S_RX_OUT_BUFFER_reg[23] 
       (.C(s00_axi_aclk),
        .CE(S_RX_OUT_BUFFER),
        .D(p_0_out[24]),
        .Q(RAW_VALUE[23]),
        .R(RSTP));
  FDRE \S_RX_OUT_BUFFER_reg[24] 
       (.C(s00_axi_aclk),
        .CE(S_RX_OUT_BUFFER),
        .D(p_0_out[25]),
        .Q(RAW_VALUE[24]),
        .R(RSTP));
  FDRE \S_RX_OUT_BUFFER_reg[25] 
       (.C(s00_axi_aclk),
        .CE(S_RX_OUT_BUFFER),
        .D(p_0_out[26]),
        .Q(RAW_VALUE[25]),
        .R(RSTP));
  FDRE \S_RX_OUT_BUFFER_reg[26] 
       (.C(s00_axi_aclk),
        .CE(S_RX_OUT_BUFFER),
        .D(p_0_out[27]),
        .Q(RAW_VALUE[26]),
        .R(RSTP));
  FDRE \S_RX_OUT_BUFFER_reg[27] 
       (.C(s00_axi_aclk),
        .CE(S_RX_OUT_BUFFER),
        .D(p_0_out[28]),
        .Q(RAW_VALUE[27]),
        .R(RSTP));
  FDRE \S_RX_OUT_BUFFER_reg[28] 
       (.C(s00_axi_aclk),
        .CE(S_RX_OUT_BUFFER),
        .D(p_0_out[29]),
        .Q(RAW_VALUE[28]),
        .R(RSTP));
  FDRE \S_RX_OUT_BUFFER_reg[29] 
       (.C(s00_axi_aclk),
        .CE(S_RX_OUT_BUFFER),
        .D(p_0_out[30]),
        .Q(RAW_VALUE[29]),
        .R(RSTP));
  FDRE \S_RX_OUT_BUFFER_reg[2] 
       (.C(s00_axi_aclk),
        .CE(S_RX_OUT_BUFFER),
        .D(p_0_out[3]),
        .Q(RAW_VALUE[2]),
        .R(RSTP));
  FDRE \S_RX_OUT_BUFFER_reg[30] 
       (.C(s00_axi_aclk),
        .CE(S_RX_OUT_BUFFER),
        .D(p_0_out[31]),
        .Q(RAW_VALUE[30]),
        .R(RSTP));
  FDRE \S_RX_OUT_BUFFER_reg[31] 
       (.C(s00_axi_aclk),
        .CE(S_RX_OUT_BUFFER),
        .D(\S_RX_BUFFER_reg_n_0_[31] ),
        .Q(RAW_VALUE[31]),
        .R(RSTP));
  FDRE \S_RX_OUT_BUFFER_reg[32] 
       (.C(s00_axi_aclk),
        .CE(S_RX_OUT_BUFFER),
        .D(p_0_out[33]),
        .Q(RAW_VALUE[32]),
        .R(RSTP));
  FDRE \S_RX_OUT_BUFFER_reg[33] 
       (.C(s00_axi_aclk),
        .CE(S_RX_OUT_BUFFER),
        .D(p_0_out[34]),
        .Q(RAW_VALUE[33]),
        .R(RSTP));
  FDRE \S_RX_OUT_BUFFER_reg[34] 
       (.C(s00_axi_aclk),
        .CE(S_RX_OUT_BUFFER),
        .D(p_0_out[35]),
        .Q(RAW_VALUE[34]),
        .R(RSTP));
  FDRE \S_RX_OUT_BUFFER_reg[35] 
       (.C(s00_axi_aclk),
        .CE(S_RX_OUT_BUFFER),
        .D(p_0_out[36]),
        .Q(RAW_VALUE[35]),
        .R(RSTP));
  FDRE \S_RX_OUT_BUFFER_reg[36] 
       (.C(s00_axi_aclk),
        .CE(S_RX_OUT_BUFFER),
        .D(p_0_out[37]),
        .Q(RAW_VALUE[36]),
        .R(RSTP));
  FDRE \S_RX_OUT_BUFFER_reg[37] 
       (.C(s00_axi_aclk),
        .CE(S_RX_OUT_BUFFER),
        .D(p_0_out[38]),
        .Q(RAW_VALUE[37]),
        .R(RSTP));
  FDRE \S_RX_OUT_BUFFER_reg[38] 
       (.C(s00_axi_aclk),
        .CE(S_RX_OUT_BUFFER),
        .D(p_0_out[39]),
        .Q(RAW_VALUE[38]),
        .R(RSTP));
  FDRE \S_RX_OUT_BUFFER_reg[39] 
       (.C(s00_axi_aclk),
        .CE(S_RX_OUT_BUFFER),
        .D(p_0_out[40]),
        .Q(RAW_VALUE[39]),
        .R(RSTP));
  FDRE \S_RX_OUT_BUFFER_reg[3] 
       (.C(s00_axi_aclk),
        .CE(S_RX_OUT_BUFFER),
        .D(p_0_out[4]),
        .Q(RAW_VALUE[3]),
        .R(RSTP));
  FDRE \S_RX_OUT_BUFFER_reg[40] 
       (.C(s00_axi_aclk),
        .CE(S_RX_OUT_BUFFER),
        .D(p_0_out[41]),
        .Q(RAW_VALUE[40]),
        .R(RSTP));
  FDRE \S_RX_OUT_BUFFER_reg[41] 
       (.C(s00_axi_aclk),
        .CE(S_RX_OUT_BUFFER),
        .D(p_0_out[42]),
        .Q(RAW_VALUE[41]),
        .R(RSTP));
  FDRE \S_RX_OUT_BUFFER_reg[42] 
       (.C(s00_axi_aclk),
        .CE(S_RX_OUT_BUFFER),
        .D(p_0_out[43]),
        .Q(RAW_VALUE[42]),
        .R(RSTP));
  FDRE \S_RX_OUT_BUFFER_reg[43] 
       (.C(s00_axi_aclk),
        .CE(S_RX_OUT_BUFFER),
        .D(p_0_out[44]),
        .Q(RAW_VALUE[43]),
        .R(RSTP));
  FDRE \S_RX_OUT_BUFFER_reg[44] 
       (.C(s00_axi_aclk),
        .CE(S_RX_OUT_BUFFER),
        .D(p_0_out[45]),
        .Q(RAW_VALUE[44]),
        .R(RSTP));
  FDRE \S_RX_OUT_BUFFER_reg[45] 
       (.C(s00_axi_aclk),
        .CE(S_RX_OUT_BUFFER),
        .D(p_0_out[46]),
        .Q(RAW_VALUE[45]),
        .R(RSTP));
  FDRE \S_RX_OUT_BUFFER_reg[46] 
       (.C(s00_axi_aclk),
        .CE(S_RX_OUT_BUFFER),
        .D(p_0_out[47]),
        .Q(RAW_VALUE[46]),
        .R(RSTP));
  FDRE \S_RX_OUT_BUFFER_reg[47] 
       (.C(s00_axi_aclk),
        .CE(S_RX_OUT_BUFFER),
        .D(\S_RX_BUFFER_reg_n_0_[47] ),
        .Q(RAW_VALUE[47]),
        .R(RSTP));
  FDRE \S_RX_OUT_BUFFER_reg[48] 
       (.C(s00_axi_aclk),
        .CE(S_RX_OUT_BUFFER),
        .D(p_0_out[49]),
        .Q(RAW_VALUE[48]),
        .R(RSTP));
  FDRE \S_RX_OUT_BUFFER_reg[49] 
       (.C(s00_axi_aclk),
        .CE(S_RX_OUT_BUFFER),
        .D(p_0_out[50]),
        .Q(RAW_VALUE[49]),
        .R(RSTP));
  FDRE \S_RX_OUT_BUFFER_reg[4] 
       (.C(s00_axi_aclk),
        .CE(S_RX_OUT_BUFFER),
        .D(p_0_out[5]),
        .Q(RAW_VALUE[4]),
        .R(RSTP));
  FDRE \S_RX_OUT_BUFFER_reg[50] 
       (.C(s00_axi_aclk),
        .CE(S_RX_OUT_BUFFER),
        .D(p_0_out[51]),
        .Q(RAW_VALUE[50]),
        .R(RSTP));
  FDRE \S_RX_OUT_BUFFER_reg[51] 
       (.C(s00_axi_aclk),
        .CE(S_RX_OUT_BUFFER),
        .D(p_0_out[52]),
        .Q(RAW_VALUE[51]),
        .R(RSTP));
  FDRE \S_RX_OUT_BUFFER_reg[52] 
       (.C(s00_axi_aclk),
        .CE(S_RX_OUT_BUFFER),
        .D(p_0_out[53]),
        .Q(RAW_VALUE[52]),
        .R(RSTP));
  FDRE \S_RX_OUT_BUFFER_reg[53] 
       (.C(s00_axi_aclk),
        .CE(S_RX_OUT_BUFFER),
        .D(p_0_out[54]),
        .Q(RAW_VALUE[53]),
        .R(RSTP));
  FDRE \S_RX_OUT_BUFFER_reg[54] 
       (.C(s00_axi_aclk),
        .CE(S_RX_OUT_BUFFER),
        .D(p_0_out[55]),
        .Q(RAW_VALUE[54]),
        .R(RSTP));
  FDRE \S_RX_OUT_BUFFER_reg[55] 
       (.C(s00_axi_aclk),
        .CE(S_RX_OUT_BUFFER),
        .D(p_0_out[56]),
        .Q(RAW_VALUE[55]),
        .R(RSTP));
  FDRE \S_RX_OUT_BUFFER_reg[56] 
       (.C(s00_axi_aclk),
        .CE(S_RX_OUT_BUFFER),
        .D(p_0_out[57]),
        .Q(RAW_VALUE[56]),
        .R(RSTP));
  FDRE \S_RX_OUT_BUFFER_reg[57] 
       (.C(s00_axi_aclk),
        .CE(S_RX_OUT_BUFFER),
        .D(p_0_out[58]),
        .Q(RAW_VALUE[57]),
        .R(RSTP));
  FDRE \S_RX_OUT_BUFFER_reg[58] 
       (.C(s00_axi_aclk),
        .CE(S_RX_OUT_BUFFER),
        .D(p_0_out[59]),
        .Q(RAW_VALUE[58]),
        .R(RSTP));
  FDRE \S_RX_OUT_BUFFER_reg[59] 
       (.C(s00_axi_aclk),
        .CE(S_RX_OUT_BUFFER),
        .D(p_0_out[60]),
        .Q(RAW_VALUE[59]),
        .R(RSTP));
  FDRE \S_RX_OUT_BUFFER_reg[5] 
       (.C(s00_axi_aclk),
        .CE(S_RX_OUT_BUFFER),
        .D(p_0_out[6]),
        .Q(RAW_VALUE[5]),
        .R(RSTP));
  FDRE \S_RX_OUT_BUFFER_reg[60] 
       (.C(s00_axi_aclk),
        .CE(S_RX_OUT_BUFFER),
        .D(p_0_out[61]),
        .Q(RAW_VALUE[60]),
        .R(RSTP));
  FDRE \S_RX_OUT_BUFFER_reg[61] 
       (.C(s00_axi_aclk),
        .CE(S_RX_OUT_BUFFER),
        .D(p_0_out[62]),
        .Q(RAW_VALUE[61]),
        .R(RSTP));
  FDRE \S_RX_OUT_BUFFER_reg[62] 
       (.C(s00_axi_aclk),
        .CE(S_RX_OUT_BUFFER),
        .D(p_0_out[63]),
        .Q(RAW_VALUE[62]),
        .R(RSTP));
  FDRE \S_RX_OUT_BUFFER_reg[63] 
       (.C(s00_axi_aclk),
        .CE(S_RX_OUT_BUFFER),
        .D(\S_RX_BUFFER_reg_n_0_[63] ),
        .Q(RAW_VALUE[63]),
        .R(RSTP));
  FDRE \S_RX_OUT_BUFFER_reg[64] 
       (.C(s00_axi_aclk),
        .CE(S_RX_OUT_BUFFER),
        .D(p_0_out[65]),
        .Q(RAW_VALUE[64]),
        .R(RSTP));
  FDRE \S_RX_OUT_BUFFER_reg[65] 
       (.C(s00_axi_aclk),
        .CE(S_RX_OUT_BUFFER),
        .D(p_0_out[66]),
        .Q(RAW_VALUE[65]),
        .R(RSTP));
  FDRE \S_RX_OUT_BUFFER_reg[66] 
       (.C(s00_axi_aclk),
        .CE(S_RX_OUT_BUFFER),
        .D(p_0_out[67]),
        .Q(RAW_VALUE[66]),
        .R(RSTP));
  FDRE \S_RX_OUT_BUFFER_reg[67] 
       (.C(s00_axi_aclk),
        .CE(S_RX_OUT_BUFFER),
        .D(p_0_out[68]),
        .Q(RAW_VALUE[67]),
        .R(RSTP));
  FDRE \S_RX_OUT_BUFFER_reg[68] 
       (.C(s00_axi_aclk),
        .CE(S_RX_OUT_BUFFER),
        .D(p_0_out[69]),
        .Q(RAW_VALUE[68]),
        .R(RSTP));
  FDRE \S_RX_OUT_BUFFER_reg[69] 
       (.C(s00_axi_aclk),
        .CE(S_RX_OUT_BUFFER),
        .D(p_0_out[70]),
        .Q(RAW_VALUE[69]),
        .R(RSTP));
  FDRE \S_RX_OUT_BUFFER_reg[6] 
       (.C(s00_axi_aclk),
        .CE(S_RX_OUT_BUFFER),
        .D(p_0_out[7]),
        .Q(RAW_VALUE[6]),
        .R(RSTP));
  FDRE \S_RX_OUT_BUFFER_reg[70] 
       (.C(s00_axi_aclk),
        .CE(S_RX_OUT_BUFFER),
        .D(p_0_out[71]),
        .Q(RAW_VALUE[70]),
        .R(RSTP));
  FDRE \S_RX_OUT_BUFFER_reg[71] 
       (.C(s00_axi_aclk),
        .CE(S_RX_OUT_BUFFER),
        .D(p_0_out[72]),
        .Q(RAW_VALUE[71]),
        .R(RSTP));
  FDRE \S_RX_OUT_BUFFER_reg[72] 
       (.C(s00_axi_aclk),
        .CE(S_RX_OUT_BUFFER),
        .D(p_0_out[73]),
        .Q(RAW_VALUE[72]),
        .R(RSTP));
  FDRE \S_RX_OUT_BUFFER_reg[73] 
       (.C(s00_axi_aclk),
        .CE(S_RX_OUT_BUFFER),
        .D(p_0_out[74]),
        .Q(RAW_VALUE[73]),
        .R(RSTP));
  FDRE \S_RX_OUT_BUFFER_reg[74] 
       (.C(s00_axi_aclk),
        .CE(S_RX_OUT_BUFFER),
        .D(p_0_out[75]),
        .Q(RAW_VALUE[74]),
        .R(RSTP));
  FDRE \S_RX_OUT_BUFFER_reg[75] 
       (.C(s00_axi_aclk),
        .CE(S_RX_OUT_BUFFER),
        .D(p_0_out[76]),
        .Q(RAW_VALUE[75]),
        .R(RSTP));
  FDRE \S_RX_OUT_BUFFER_reg[76] 
       (.C(s00_axi_aclk),
        .CE(S_RX_OUT_BUFFER),
        .D(p_0_out[77]),
        .Q(RAW_VALUE[76]),
        .R(RSTP));
  FDRE \S_RX_OUT_BUFFER_reg[77] 
       (.C(s00_axi_aclk),
        .CE(S_RX_OUT_BUFFER),
        .D(p_0_out[78]),
        .Q(RAW_VALUE[77]),
        .R(RSTP));
  FDRE \S_RX_OUT_BUFFER_reg[78] 
       (.C(s00_axi_aclk),
        .CE(S_RX_OUT_BUFFER),
        .D(p_0_out[79]),
        .Q(RAW_VALUE[78]),
        .R(RSTP));
  FDRE \S_RX_OUT_BUFFER_reg[79] 
       (.C(s00_axi_aclk),
        .CE(S_RX_OUT_BUFFER),
        .D(\S_RX_BUFFER_reg_n_0_[79] ),
        .Q(RAW_VALUE[79]),
        .R(RSTP));
  FDRE \S_RX_OUT_BUFFER_reg[7] 
       (.C(s00_axi_aclk),
        .CE(S_RX_OUT_BUFFER),
        .D(p_0_out[8]),
        .Q(RAW_VALUE[7]),
        .R(RSTP));
  FDRE \S_RX_OUT_BUFFER_reg[80] 
       (.C(s00_axi_aclk),
        .CE(S_RX_OUT_BUFFER),
        .D(p_0_out[81]),
        .Q(RAW_VALUE[80]),
        .R(RSTP));
  FDRE \S_RX_OUT_BUFFER_reg[81] 
       (.C(s00_axi_aclk),
        .CE(S_RX_OUT_BUFFER),
        .D(p_0_out[82]),
        .Q(RAW_VALUE[81]),
        .R(RSTP));
  FDRE \S_RX_OUT_BUFFER_reg[82] 
       (.C(s00_axi_aclk),
        .CE(S_RX_OUT_BUFFER),
        .D(p_0_out[83]),
        .Q(RAW_VALUE[82]),
        .R(RSTP));
  FDRE \S_RX_OUT_BUFFER_reg[83] 
       (.C(s00_axi_aclk),
        .CE(S_RX_OUT_BUFFER),
        .D(p_0_out[84]),
        .Q(RAW_VALUE[83]),
        .R(RSTP));
  FDRE \S_RX_OUT_BUFFER_reg[84] 
       (.C(s00_axi_aclk),
        .CE(S_RX_OUT_BUFFER),
        .D(p_0_out[85]),
        .Q(RAW_VALUE[84]),
        .R(RSTP));
  FDRE \S_RX_OUT_BUFFER_reg[85] 
       (.C(s00_axi_aclk),
        .CE(S_RX_OUT_BUFFER),
        .D(p_0_out[86]),
        .Q(RAW_VALUE[85]),
        .R(RSTP));
  FDRE \S_RX_OUT_BUFFER_reg[86] 
       (.C(s00_axi_aclk),
        .CE(S_RX_OUT_BUFFER),
        .D(p_0_out[87]),
        .Q(RAW_VALUE[86]),
        .R(RSTP));
  FDRE \S_RX_OUT_BUFFER_reg[87] 
       (.C(s00_axi_aclk),
        .CE(S_RX_OUT_BUFFER),
        .D(p_0_out[88]),
        .Q(RAW_VALUE[87]),
        .R(RSTP));
  FDRE \S_RX_OUT_BUFFER_reg[88] 
       (.C(s00_axi_aclk),
        .CE(S_RX_OUT_BUFFER),
        .D(p_0_out[89]),
        .Q(RAW_VALUE[88]),
        .R(RSTP));
  FDRE \S_RX_OUT_BUFFER_reg[89] 
       (.C(s00_axi_aclk),
        .CE(S_RX_OUT_BUFFER),
        .D(p_0_out[90]),
        .Q(RAW_VALUE[89]),
        .R(RSTP));
  FDRE \S_RX_OUT_BUFFER_reg[8] 
       (.C(s00_axi_aclk),
        .CE(S_RX_OUT_BUFFER),
        .D(p_0_out[9]),
        .Q(RAW_VALUE[8]),
        .R(RSTP));
  FDRE \S_RX_OUT_BUFFER_reg[90] 
       (.C(s00_axi_aclk),
        .CE(S_RX_OUT_BUFFER),
        .D(p_0_out[91]),
        .Q(RAW_VALUE[90]),
        .R(RSTP));
  FDRE \S_RX_OUT_BUFFER_reg[91] 
       (.C(s00_axi_aclk),
        .CE(S_RX_OUT_BUFFER),
        .D(p_0_out[92]),
        .Q(RAW_VALUE[91]),
        .R(RSTP));
  FDRE \S_RX_OUT_BUFFER_reg[92] 
       (.C(s00_axi_aclk),
        .CE(S_RX_OUT_BUFFER),
        .D(p_0_out[93]),
        .Q(RAW_VALUE[92]),
        .R(RSTP));
  FDRE \S_RX_OUT_BUFFER_reg[93] 
       (.C(s00_axi_aclk),
        .CE(S_RX_OUT_BUFFER),
        .D(p_0_out[94]),
        .Q(RAW_VALUE[93]),
        .R(RSTP));
  FDRE \S_RX_OUT_BUFFER_reg[94] 
       (.C(s00_axi_aclk),
        .CE(S_RX_OUT_BUFFER),
        .D(p_0_out[95]),
        .Q(RAW_VALUE[94]),
        .R(RSTP));
  FDRE \S_RX_OUT_BUFFER_reg[95] 
       (.C(s00_axi_aclk),
        .CE(S_RX_OUT_BUFFER),
        .D(\S_RX_BUFFER_reg_n_0_[95] ),
        .Q(RAW_VALUE[95]),
        .R(RSTP));
  FDRE \S_RX_OUT_BUFFER_reg[96] 
       (.C(s00_axi_aclk),
        .CE(S_RX_OUT_BUFFER),
        .D(p_0_out[97]),
        .Q(RAW_VALUE[96]),
        .R(RSTP));
  FDRE \S_RX_OUT_BUFFER_reg[97] 
       (.C(s00_axi_aclk),
        .CE(S_RX_OUT_BUFFER),
        .D(p_0_out[98]),
        .Q(RAW_VALUE[97]),
        .R(RSTP));
  FDRE \S_RX_OUT_BUFFER_reg[98] 
       (.C(s00_axi_aclk),
        .CE(S_RX_OUT_BUFFER),
        .D(p_0_out[99]),
        .Q(RAW_VALUE[98]),
        .R(RSTP));
  FDRE \S_RX_OUT_BUFFER_reg[99] 
       (.C(s00_axi_aclk),
        .CE(S_RX_OUT_BUFFER),
        .D(p_0_out[100]),
        .Q(RAW_VALUE[99]),
        .R(RSTP));
  FDRE \S_RX_OUT_BUFFER_reg[9] 
       (.C(s00_axi_aclk),
        .CE(S_RX_OUT_BUFFER),
        .D(p_0_out[10]),
        .Q(RAW_VALUE[9]),
        .R(RSTP));
  LUT6 #(
    .INIT(64'h00040004FF070307)) 
    \S_SAMPLE_TIME_COUNTER[30]_i_1 
       (.I0(\S_SAMPLE_TIME_COUNTER_reg[0] ),
        .I1(Q[0]),
        .I2(Q[1]),
        .I3(\S_SAMPLE_TIME_COUNTER_reg[0]_0 ),
        .I4(SS_N),
        .I5(\S_SAMPLE_TIME_COUNTER_reg[0]_1 ),
        .O(E));
  LUT5 #(
    .INIT(32'hFEFFFE00)) 
    S_SCLK_i_1
       (.I0(S_SCLK_i_2_n_0),
        .I1(S_SCLK_i_3_n_0),
        .I2(S_SCLK_i_4_n_0),
        .I3(S_SCLK_i_5_n_0),
        .I4(S_SCLK),
        .O(S_SCLK_i_1_n_0));
  LUT6 #(
    .INIT(64'h00AA0CAA00AA00AA)) 
    S_SCLK_i_2
       (.I0(CPOL),
        .I1(\S_DEL_CLK[16]_i_3_n_0 ),
        .I2(S_SCLK),
        .I3(S_AXI_ARESETN),
        .I4(curstate[2]),
        .I5(curstate[1]),
        .O(S_SCLK_i_2_n_0));
  LUT6 #(
    .INIT(64'hF222222200000000)) 
    S_SCLK_i_3
       (.I0(S_SCLK_i_6_n_0),
        .I1(S_CPOL_reg_n_0),
        .I2(S_SCLK_i_7_n_0),
        .I3(S_SCLK_reg_0),
        .I4(SCLK_IN),
        .I5(S_AXI_ARESETN),
        .O(S_SCLK_i_3_n_0));
  LUT6 #(
    .INIT(64'h8888888880888080)) 
    S_SCLK_i_4
       (.I0(S_AXI_ARESETN),
        .I1(S_CPOL_reg_n_0),
        .I2(S_SCLK_i_8_n_0),
        .I3(S_SCLK_reg_0),
        .I4(\S_DEL_COUNT[8]_i_3_n_0 ),
        .I5(\curstate[0]_i_3_n_0 ),
        .O(S_SCLK_i_4_n_0));
  (* SOFT_HLUTNM = "soft_lutpair69" *) 
  LUT5 #(
    .INIT(32'hFFFF2203)) 
    S_SCLK_i_5
       (.I0(SS_OUT_N_i_2_n_0),
        .I1(curstate[1]),
        .I2(curstate[2]),
        .I3(curstate[0]),
        .I4(S_SCLK_i_9_n_0),
        .O(S_SCLK_i_5_n_0));
  (* SOFT_HLUTNM = "soft_lutpair69" *) 
  LUT4 #(
    .INIT(16'h0200)) 
    S_SCLK_i_6
       (.I0(curstate[0]),
        .I1(curstate[1]),
        .I2(curstate[2]),
        .I3(SS_OUT_N_i_2_n_0),
        .O(S_SCLK_i_6_n_0));
  (* SOFT_HLUTNM = "soft_lutpair70" *) 
  LUT5 #(
    .INIT(32'hFAAAAABB)) 
    S_SCLK_i_7
       (.I0(curstate[2]),
        .I1(\S_BIT_COUNT_reg[0]_0 ),
        .I2(\S_RX_OUT_BUFFER[127]_i_3_n_0 ),
        .I3(curstate[0]),
        .I4(curstate[1]),
        .O(S_SCLK_i_7_n_0));
  (* SOFT_HLUTNM = "soft_lutpair71" *) 
  LUT4 #(
    .INIT(16'h0100)) 
    S_SCLK_i_8
       (.I0(curstate[0]),
        .I1(curstate[1]),
        .I2(curstate[2]),
        .I3(\S_BIT_COUNT_reg[0]_0 ),
        .O(S_SCLK_i_8_n_0));
  LUT6 #(
    .INIT(64'hFFF5D5D5F5F5D5D5)) 
    S_SCLK_i_9
       (.I0(S_AXI_ARESETN),
        .I1(curstate[0]),
        .I2(curstate[2]),
        .I3(\S_DEL_CLK[16]_i_3_n_0 ),
        .I4(curstate[1]),
        .I5(nxtstate1),
        .O(S_SCLK_i_9_n_0));
  FDRE S_SCLK_reg
       (.C(s00_axi_aclk),
        .CE(1'b1),
        .D(S_SCLK_i_1_n_0),
        .Q(S_SCLK),
        .R(1'b0));
  LUT3 #(
    .INIT(8'h8A)) 
    \S_SPI_BUSY_PIPE[0]_i_1 
       (.I0(S_SPI_BUSY),
        .I1(Q[1]),
        .I2(Q[0]),
        .O(D));
  LUT3 #(
    .INIT(8'hFE)) 
    \curstate[0]_i_1 
       (.I0(\curstate[0]_i_2_n_0 ),
        .I1(\curstate[0]_i_3_n_0 ),
        .I2(\curstate[0]_i_4_n_0 ),
        .O(nxtstate[0]));
  (* SOFT_HLUTNM = "soft_lutpair71" *) 
  LUT5 #(
    .INIT(32'h00000A0C)) 
    \curstate[0]_i_2 
       (.I0(nxtstate1),
        .I1(\S_BIT_COUNT_reg[0]_0 ),
        .I2(curstate[2]),
        .I3(curstate[1]),
        .I4(curstate[0]),
        .O(\curstate[0]_i_2_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair76" *) 
  LUT5 #(
    .INIT(32'h00020000)) 
    \curstate[0]_i_3 
       (.I0(\curstate[2]_i_2_n_0 ),
        .I1(S_DEL_COUNT[8]),
        .I2(curstate[2]),
        .I3(curstate[1]),
        .I4(curstate[0]),
        .O(\curstate[0]_i_3_n_0 ));
  LUT6 #(
    .INIT(64'h0011000F00000000)) 
    \curstate[0]_i_4 
       (.I0(\S_RX_OUT_BUFFER[127]_i_3_n_0 ),
        .I1(nxtstate1),
        .I2(S_CPHA_reg_n_0),
        .I3(curstate[2]),
        .I4(curstate[1]),
        .I5(curstate[0]),
        .O(\curstate[0]_i_4_n_0 ));
  LUT6 #(
    .INIT(64'hFFFFFFFF00000020)) 
    \curstate[2]_i_1 
       (.I0(\curstate[2]_i_2_n_0 ),
        .I1(S_DEL_COUNT[8]),
        .I2(curstate[2]),
        .I3(curstate[1]),
        .I4(curstate[0]),
        .I5(S_RX_OUT_BUFFER),
        .O(nxtstate[2]));
  (* SOFT_HLUTNM = "soft_lutpair72" *) 
  LUT3 #(
    .INIT(8'hFE)) 
    \curstate[2]_i_2 
       (.I0(S_DEL_COUNT[6]),
        .I1(\S_DEL_COUNT[7]_i_3_n_0 ),
        .I2(S_DEL_COUNT[7]),
        .O(\curstate[2]_i_2_n_0 ));
  (* FSM_ENCODING = "auto" *) 
  (* FSM_SAFE_STATE = "power_on_state" *) 
  FDRE #(
    .INIT(1'b0)) 
    \curstate_reg[0] 
       (.C(s00_axi_aclk),
        .CE(1'b1),
        .D(nxtstate[0]),
        .Q(curstate[0]),
        .R(RSTP));
  (* FSM_ENCODING = "auto" *) 
  (* FSM_SAFE_STATE = "power_on_state" *) 
  FDRE #(
    .INIT(1'b0)) 
    \curstate_reg[1] 
       (.C(s00_axi_aclk),
        .CE(1'b1),
        .D(nxtstate[1]),
        .Q(curstate[1]),
        .R(RSTP));
  (* FSM_ENCODING = "auto" *) 
  (* FSM_SAFE_STATE = "power_on_state" *) 
  FDRE #(
    .INIT(1'b0)) 
    \curstate_reg[2] 
       (.C(s00_axi_aclk),
        .CE(1'b1),
        .D(nxtstate[2]),
        .Q(curstate[2]),
        .R(RSTP));
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
