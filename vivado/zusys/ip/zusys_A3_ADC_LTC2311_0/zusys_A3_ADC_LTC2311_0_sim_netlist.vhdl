-- Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
-- --------------------------------------------------------------------------------
-- Tool Version: Vivado v.2020.1.1 (win64) Build 2960000 Wed Aug  5 22:57:20 MDT 2020
-- Date        : Fri Jan 28 14:50:38 2022
-- Host        : enc177112 running 64-bit major release  (build 9200)
-- Command     : write_vhdl -force -mode funcsim
--               c:/GIT/UltraZohm/software/ultrazohm_sw_develop/vivado/zusys/ip/zusys_A3_ADC_LTC2311_0/zusys_A3_ADC_LTC2311_0_sim_netlist.vhdl
-- Design      : zusys_A3_ADC_LTC2311_0
-- Purpose     : This VHDL netlist is a functional simulation representation of the design and should not be modified or
--               synthesized. This netlist cannot be used for SDF annotated simulation.
-- Device      : xczu9eg-ffvc900-1-e
-- --------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity zusys_A3_ADC_LTC2311_0_ADC_LTC2311_v3_0_S00_AXI is
  port (
    axi_awready_reg_0 : out STD_LOGIC;
    RSTP : out STD_LOGIC;
    axi_wready_reg_0 : out STD_LOGIC;
    axi_arready_reg_0 : out STD_LOGIC;
    \ADC_CR_reg[3]_0\ : out STD_LOGIC_VECTOR ( 0 to 0 );
    s00_axi_bvalid : out STD_LOGIC;
    s00_axi_rvalid : out STD_LOGIC;
    \ADC_CR_reg[3]_1\ : out STD_LOGIC;
    S_AXI_ARESETN : out STD_LOGIC;
    E : out STD_LOGIC_VECTOR ( 0 to 0 );
    \S_SET_CONVERSION_reg[0]\ : out STD_LOGIC_VECTOR ( 7 downto 0 );
    \ADC_CHANNEL_reg[7]_0\ : out STD_LOGIC_VECTOR ( 7 downto 0 );
    \S_ENABLE_reg[0]\ : out STD_LOGIC;
    nxtstate : out STD_LOGIC_VECTOR ( 1 downto 0 );
    \ADC_MASTER_CHANNEL_reg[0]_0\ : out STD_LOGIC;
    \ADC_CR_reg[2]_0\ : out STD_LOGIC;
    CPHA : out STD_LOGIC;
    D : out STD_LOGIC_VECTOR ( 1 downto 0 );
    CPOL : out STD_LOGIC;
    Q : out STD_LOGIC_VECTOR ( 31 downto 0 );
    \ADC_CONV_VALUE_reg[30]_0\ : out STD_LOGIC_VECTOR ( 30 downto 0 );
    s00_axi_rdata : out STD_LOGIC_VECTOR ( 31 downto 0 );
    \S_SET_SAMPLES_reg[0]\ : out STD_LOGIC;
    \ADC_CR_reg[3]_2\ : out STD_LOGIC_VECTOR ( 0 to 0 );
    S_SCLK_IN : out STD_LOGIC;
    S_SET_CONVERSION : out STD_LOGIC;
    \ADC_MASTER_CHANNEL_reg[0]_1\ : out STD_LOGIC;
    \ADC_CR_reg[6]_0\ : out STD_LOGIC;
    S_SS_IN_N : out STD_LOGIC;
    s00_axi_aclk : in STD_LOGIC;
    RAW_VALID : in STD_LOGIC_VECTOR ( 0 to 0 );
    SI_VALID : in STD_LOGIC_VECTOR ( 0 to 0 );
    BUSY : in STD_LOGIC;
    s00_axi_wdata : in STD_LOGIC_VECTOR ( 31 downto 0 );
    s00_axi_aresetn : in STD_LOGIC;
    SET_CONVERSION : in STD_LOGIC;
    SET_OFFSET : in STD_LOGIC;
    SET_SAMPLE_TIME : in STD_LOGIC;
    SET_SAMPLES : in STD_LOGIC;
    s00_axi_wvalid : in STD_LOGIC;
    s00_axi_awvalid : in STD_LOGIC;
    s00_axi_bready : in STD_LOGIC;
    s00_axi_arvalid : in STD_LOGIC;
    s00_axi_rready : in STD_LOGIC;
    ENABLE : in STD_LOGIC;
    P_ADC_CR_IN : in STD_LOGIC_VECTOR ( 1 downto 0 );
    s00_axi_awaddr : in STD_LOGIC_VECTOR ( 3 downto 0 );
    s00_axi_araddr : in STD_LOGIC_VECTOR ( 3 downto 0 );
    s00_axi_wstrb : in STD_LOGIC_VECTOR ( 3 downto 0 );
    \ADC_SPI_CR_reg[3]_0\ : in STD_LOGIC_VECTOR ( 1 downto 0 );
    \ADC_SPI_CR_reg[5]_0\ : in STD_LOGIC;
    \curstate_reg[0]\ : in STD_LOGIC_VECTOR ( 1 downto 0 );
    TRIGGER_CNV : in STD_LOGIC_VECTOR ( 0 to 0 );
    S_TRIGGER_CNV_PIPE : in STD_LOGIC
  );
  attribute ORIG_REF_NAME : string;
  attribute ORIG_REF_NAME of zusys_A3_ADC_LTC2311_0_ADC_LTC2311_v3_0_S00_AXI : entity is "ADC_LTC2311_v3_0_S00_AXI";
end zusys_A3_ADC_LTC2311_0_ADC_LTC2311_v3_0_S00_AXI;

architecture STRUCTURE of zusys_A3_ADC_LTC2311_0_ADC_LTC2311_v3_0_S00_AXI is
  signal \ADC_AVAILABLE[15]_i_1_n_0\ : STD_LOGIC;
  signal \ADC_AVAILABLE[23]_i_1_n_0\ : STD_LOGIC;
  signal \ADC_AVAILABLE[31]_i_1_n_0\ : STD_LOGIC;
  signal \ADC_AVAILABLE[7]_i_1_n_0\ : STD_LOGIC;
  signal \ADC_AVAILABLE_reg_n_0_[10]\ : STD_LOGIC;
  signal \ADC_AVAILABLE_reg_n_0_[11]\ : STD_LOGIC;
  signal \ADC_AVAILABLE_reg_n_0_[12]\ : STD_LOGIC;
  signal \ADC_AVAILABLE_reg_n_0_[13]\ : STD_LOGIC;
  signal \ADC_AVAILABLE_reg_n_0_[14]\ : STD_LOGIC;
  signal \ADC_AVAILABLE_reg_n_0_[15]\ : STD_LOGIC;
  signal \ADC_AVAILABLE_reg_n_0_[16]\ : STD_LOGIC;
  signal \ADC_AVAILABLE_reg_n_0_[17]\ : STD_LOGIC;
  signal \ADC_AVAILABLE_reg_n_0_[18]\ : STD_LOGIC;
  signal \ADC_AVAILABLE_reg_n_0_[19]\ : STD_LOGIC;
  signal \ADC_AVAILABLE_reg_n_0_[1]\ : STD_LOGIC;
  signal \ADC_AVAILABLE_reg_n_0_[20]\ : STD_LOGIC;
  signal \ADC_AVAILABLE_reg_n_0_[21]\ : STD_LOGIC;
  signal \ADC_AVAILABLE_reg_n_0_[22]\ : STD_LOGIC;
  signal \ADC_AVAILABLE_reg_n_0_[23]\ : STD_LOGIC;
  signal \ADC_AVAILABLE_reg_n_0_[24]\ : STD_LOGIC;
  signal \ADC_AVAILABLE_reg_n_0_[25]\ : STD_LOGIC;
  signal \ADC_AVAILABLE_reg_n_0_[26]\ : STD_LOGIC;
  signal \ADC_AVAILABLE_reg_n_0_[27]\ : STD_LOGIC;
  signal \ADC_AVAILABLE_reg_n_0_[28]\ : STD_LOGIC;
  signal \ADC_AVAILABLE_reg_n_0_[29]\ : STD_LOGIC;
  signal \ADC_AVAILABLE_reg_n_0_[2]\ : STD_LOGIC;
  signal \ADC_AVAILABLE_reg_n_0_[30]\ : STD_LOGIC;
  signal \ADC_AVAILABLE_reg_n_0_[31]\ : STD_LOGIC;
  signal \ADC_AVAILABLE_reg_n_0_[3]\ : STD_LOGIC;
  signal \ADC_AVAILABLE_reg_n_0_[4]\ : STD_LOGIC;
  signal \ADC_AVAILABLE_reg_n_0_[5]\ : STD_LOGIC;
  signal \ADC_AVAILABLE_reg_n_0_[6]\ : STD_LOGIC;
  signal \ADC_AVAILABLE_reg_n_0_[7]\ : STD_LOGIC;
  signal \ADC_AVAILABLE_reg_n_0_[8]\ : STD_LOGIC;
  signal \ADC_AVAILABLE_reg_n_0_[9]\ : STD_LOGIC;
  signal \ADC_CHANNEL[15]_i_1_n_0\ : STD_LOGIC;
  signal \ADC_CHANNEL[23]_i_1_n_0\ : STD_LOGIC;
  signal \ADC_CHANNEL[31]_i_1_n_0\ : STD_LOGIC;
  signal \ADC_CHANNEL[7]_i_1_n_0\ : STD_LOGIC;
  signal \ADC_CONV_VALUE[15]_i_1_n_0\ : STD_LOGIC;
  signal \ADC_CONV_VALUE[23]_i_1_n_0\ : STD_LOGIC;
  signal \ADC_CONV_VALUE[31]_i_1_n_0\ : STD_LOGIC;
  signal \ADC_CONV_VALUE[7]_i_1_n_0\ : STD_LOGIC;
  signal \^adc_conv_value_reg[30]_0\ : STD_LOGIC_VECTOR ( 30 downto 0 );
  signal ADC_CR : STD_LOGIC_VECTOR ( 31 downto 3 );
  signal \ADC_CR[15]_i_1_n_0\ : STD_LOGIC;
  signal \ADC_CR[23]_i_1_n_0\ : STD_LOGIC;
  signal \ADC_CR[2]_i_1_n_0\ : STD_LOGIC;
  signal \ADC_CR[31]_i_1_n_0\ : STD_LOGIC;
  signal \ADC_CR[4]_i_1_n_0\ : STD_LOGIC;
  signal \ADC_CR[7]_i_1_n_0\ : STD_LOGIC;
  signal \^adc_cr_reg[3]_0\ : STD_LOGIC_VECTOR ( 0 to 0 );
  signal \ADC_CR_reg_n_0_[10]\ : STD_LOGIC;
  signal \ADC_CR_reg_n_0_[11]\ : STD_LOGIC;
  signal \ADC_CR_reg_n_0_[12]\ : STD_LOGIC;
  signal \ADC_CR_reg_n_0_[13]\ : STD_LOGIC;
  signal \ADC_CR_reg_n_0_[14]\ : STD_LOGIC;
  signal \ADC_CR_reg_n_0_[15]\ : STD_LOGIC;
  signal \ADC_CR_reg_n_0_[16]\ : STD_LOGIC;
  signal \ADC_CR_reg_n_0_[17]\ : STD_LOGIC;
  signal \ADC_CR_reg_n_0_[18]\ : STD_LOGIC;
  signal \ADC_CR_reg_n_0_[19]\ : STD_LOGIC;
  signal \ADC_CR_reg_n_0_[20]\ : STD_LOGIC;
  signal \ADC_CR_reg_n_0_[21]\ : STD_LOGIC;
  signal \ADC_CR_reg_n_0_[22]\ : STD_LOGIC;
  signal \ADC_CR_reg_n_0_[23]\ : STD_LOGIC;
  signal \ADC_CR_reg_n_0_[24]\ : STD_LOGIC;
  signal \ADC_CR_reg_n_0_[25]\ : STD_LOGIC;
  signal \ADC_CR_reg_n_0_[26]\ : STD_LOGIC;
  signal \ADC_CR_reg_n_0_[27]\ : STD_LOGIC;
  signal \ADC_CR_reg_n_0_[28]\ : STD_LOGIC;
  signal \ADC_CR_reg_n_0_[29]\ : STD_LOGIC;
  signal \ADC_CR_reg_n_0_[30]\ : STD_LOGIC;
  signal \ADC_CR_reg_n_0_[31]\ : STD_LOGIC;
  signal \ADC_CR_reg_n_0_[8]\ : STD_LOGIC;
  signal \ADC_CR_reg_n_0_[9]\ : STD_LOGIC;
  signal ADC_MASTER_BUSY : STD_LOGIC_VECTOR ( 0 to 0 );
  signal \ADC_MASTER_CHANNEL[15]_i_1_n_0\ : STD_LOGIC;
  signal \ADC_MASTER_CHANNEL[23]_i_1_n_0\ : STD_LOGIC;
  signal \ADC_MASTER_CHANNEL[31]_i_1_n_0\ : STD_LOGIC;
  signal \ADC_MASTER_CHANNEL[7]_i_1_n_0\ : STD_LOGIC;
  signal \ADC_MASTER_CHANNEL_reg_n_0_[10]\ : STD_LOGIC;
  signal \ADC_MASTER_CHANNEL_reg_n_0_[11]\ : STD_LOGIC;
  signal \ADC_MASTER_CHANNEL_reg_n_0_[12]\ : STD_LOGIC;
  signal \ADC_MASTER_CHANNEL_reg_n_0_[13]\ : STD_LOGIC;
  signal \ADC_MASTER_CHANNEL_reg_n_0_[14]\ : STD_LOGIC;
  signal \ADC_MASTER_CHANNEL_reg_n_0_[15]\ : STD_LOGIC;
  signal \ADC_MASTER_CHANNEL_reg_n_0_[16]\ : STD_LOGIC;
  signal \ADC_MASTER_CHANNEL_reg_n_0_[17]\ : STD_LOGIC;
  signal \ADC_MASTER_CHANNEL_reg_n_0_[18]\ : STD_LOGIC;
  signal \ADC_MASTER_CHANNEL_reg_n_0_[19]\ : STD_LOGIC;
  signal \ADC_MASTER_CHANNEL_reg_n_0_[1]\ : STD_LOGIC;
  signal \ADC_MASTER_CHANNEL_reg_n_0_[20]\ : STD_LOGIC;
  signal \ADC_MASTER_CHANNEL_reg_n_0_[21]\ : STD_LOGIC;
  signal \ADC_MASTER_CHANNEL_reg_n_0_[22]\ : STD_LOGIC;
  signal \ADC_MASTER_CHANNEL_reg_n_0_[23]\ : STD_LOGIC;
  signal \ADC_MASTER_CHANNEL_reg_n_0_[24]\ : STD_LOGIC;
  signal \ADC_MASTER_CHANNEL_reg_n_0_[25]\ : STD_LOGIC;
  signal \ADC_MASTER_CHANNEL_reg_n_0_[26]\ : STD_LOGIC;
  signal \ADC_MASTER_CHANNEL_reg_n_0_[27]\ : STD_LOGIC;
  signal \ADC_MASTER_CHANNEL_reg_n_0_[28]\ : STD_LOGIC;
  signal \ADC_MASTER_CHANNEL_reg_n_0_[29]\ : STD_LOGIC;
  signal \ADC_MASTER_CHANNEL_reg_n_0_[2]\ : STD_LOGIC;
  signal \ADC_MASTER_CHANNEL_reg_n_0_[30]\ : STD_LOGIC;
  signal \ADC_MASTER_CHANNEL_reg_n_0_[31]\ : STD_LOGIC;
  signal \ADC_MASTER_CHANNEL_reg_n_0_[3]\ : STD_LOGIC;
  signal \ADC_MASTER_CHANNEL_reg_n_0_[4]\ : STD_LOGIC;
  signal \ADC_MASTER_CHANNEL_reg_n_0_[5]\ : STD_LOGIC;
  signal \ADC_MASTER_CHANNEL_reg_n_0_[6]\ : STD_LOGIC;
  signal \ADC_MASTER_CHANNEL_reg_n_0_[7]\ : STD_LOGIC;
  signal \ADC_MASTER_CHANNEL_reg_n_0_[8]\ : STD_LOGIC;
  signal \ADC_MASTER_CHANNEL_reg_n_0_[9]\ : STD_LOGIC;
  signal ADC_MASTER_FINISH : STD_LOGIC_VECTOR ( 0 to 0 );
  signal ADC_MASTER_SI_FINISH : STD_LOGIC_VECTOR ( 0 to 0 );
  signal ADC_SPI_CR : STD_LOGIC_VECTOR ( 31 downto 7 );
  signal ADC_SPI_CR0_in : STD_LOGIC_VECTOR ( 5 downto 1 );
  signal \ADC_SPI_CR[15]_i_1_n_0\ : STD_LOGIC;
  signal \ADC_SPI_CR[23]_i_1_n_0\ : STD_LOGIC;
  signal \ADC_SPI_CR[31]_i_1_n_0\ : STD_LOGIC;
  signal \ADC_SPI_CR[31]_i_3_n_0\ : STD_LOGIC;
  signal \ADC_SPI_CR[6]_i_1_n_0\ : STD_LOGIC;
  signal \ADC_SPI_CR[7]_i_1_n_0\ : STD_LOGIC;
  signal \ADC_SPI_CR_reg_n_0_[10]\ : STD_LOGIC;
  signal \ADC_SPI_CR_reg_n_0_[11]\ : STD_LOGIC;
  signal \ADC_SPI_CR_reg_n_0_[12]\ : STD_LOGIC;
  signal \ADC_SPI_CR_reg_n_0_[13]\ : STD_LOGIC;
  signal \ADC_SPI_CR_reg_n_0_[14]\ : STD_LOGIC;
  signal \ADC_SPI_CR_reg_n_0_[15]\ : STD_LOGIC;
  signal \ADC_SPI_CR_reg_n_0_[16]\ : STD_LOGIC;
  signal \ADC_SPI_CR_reg_n_0_[17]\ : STD_LOGIC;
  signal \ADC_SPI_CR_reg_n_0_[18]\ : STD_LOGIC;
  signal \ADC_SPI_CR_reg_n_0_[19]\ : STD_LOGIC;
  signal \ADC_SPI_CR_reg_n_0_[1]\ : STD_LOGIC;
  signal \ADC_SPI_CR_reg_n_0_[20]\ : STD_LOGIC;
  signal \ADC_SPI_CR_reg_n_0_[21]\ : STD_LOGIC;
  signal \ADC_SPI_CR_reg_n_0_[22]\ : STD_LOGIC;
  signal \ADC_SPI_CR_reg_n_0_[23]\ : STD_LOGIC;
  signal \ADC_SPI_CR_reg_n_0_[24]\ : STD_LOGIC;
  signal \ADC_SPI_CR_reg_n_0_[25]\ : STD_LOGIC;
  signal \ADC_SPI_CR_reg_n_0_[26]\ : STD_LOGIC;
  signal \ADC_SPI_CR_reg_n_0_[27]\ : STD_LOGIC;
  signal \ADC_SPI_CR_reg_n_0_[28]\ : STD_LOGIC;
  signal \ADC_SPI_CR_reg_n_0_[29]\ : STD_LOGIC;
  signal \ADC_SPI_CR_reg_n_0_[30]\ : STD_LOGIC;
  signal \ADC_SPI_CR_reg_n_0_[31]\ : STD_LOGIC;
  signal \ADC_SPI_CR_reg_n_0_[3]\ : STD_LOGIC;
  signal \ADC_SPI_CR_reg_n_0_[5]\ : STD_LOGIC;
  signal \ADC_SPI_CR_reg_n_0_[8]\ : STD_LOGIC;
  signal \ADC_SPI_CR_reg_n_0_[9]\ : STD_LOGIC;
  signal \^cpha\ : STD_LOGIC;
  signal \^cpol\ : STD_LOGIC;
  signal \^d\ : STD_LOGIC_VECTOR ( 1 downto 0 );
  signal IS_BUSY : STD_LOGIC;
  signal \^q\ : STD_LOGIC_VECTOR ( 31 downto 0 );
  signal \^rstp\ : STD_LOGIC;
  signal S_ADC_AVAILABLE : STD_LOGIC;
  signal S_ADC_CHANNEL : STD_LOGIC_VECTOR ( 31 downto 0 );
  signal S_ADC_CONV_VALUE : STD_LOGIC_VECTOR ( 31 to 31 );
  signal S_ADC_CR : STD_LOGIC_VECTOR ( 7 downto 0 );
  signal S_ADC_MASTER_CHANNEL : STD_LOGIC;
  signal \^s_axi_aresetn\ : STD_LOGIC;
  signal \S_ENABLE0__4\ : STD_LOGIC;
  signal \S_ENABLE[0]_i_2_n_0\ : STD_LOGIC;
  signal \S_ENABLE[0]_i_4_n_0\ : STD_LOGIC;
  signal \S_SET_SAMPLES[0]_i_2_n_0\ : STD_LOGIC;
  signal S_SET_SAMPLE_TIME8_out : STD_LOGIC;
  signal aw_en_i_1_n_0 : STD_LOGIC;
  signal aw_en_reg_n_0 : STD_LOGIC;
  signal axi_arready0 : STD_LOGIC;
  signal \^axi_arready_reg_0\ : STD_LOGIC;
  signal axi_awready0 : STD_LOGIC;
  signal \^axi_awready_reg_0\ : STD_LOGIC;
  signal axi_bvalid_i_1_n_0 : STD_LOGIC;
  signal \axi_rdata[0]_i_4_n_0\ : STD_LOGIC;
  signal \axi_rdata[0]_i_5_n_0\ : STD_LOGIC;
  signal \axi_rdata[0]_i_6_n_0\ : STD_LOGIC;
  signal \axi_rdata[0]_i_7_n_0\ : STD_LOGIC;
  signal \axi_rdata[10]_i_2_n_0\ : STD_LOGIC;
  signal \axi_rdata[10]_i_3_n_0\ : STD_LOGIC;
  signal \axi_rdata[10]_i_4_n_0\ : STD_LOGIC;
  signal \axi_rdata[10]_i_5_n_0\ : STD_LOGIC;
  signal \axi_rdata[11]_i_2_n_0\ : STD_LOGIC;
  signal \axi_rdata[11]_i_3_n_0\ : STD_LOGIC;
  signal \axi_rdata[11]_i_4_n_0\ : STD_LOGIC;
  signal \axi_rdata[11]_i_5_n_0\ : STD_LOGIC;
  signal \axi_rdata[12]_i_2_n_0\ : STD_LOGIC;
  signal \axi_rdata[12]_i_3_n_0\ : STD_LOGIC;
  signal \axi_rdata[12]_i_4_n_0\ : STD_LOGIC;
  signal \axi_rdata[12]_i_5_n_0\ : STD_LOGIC;
  signal \axi_rdata[13]_i_2_n_0\ : STD_LOGIC;
  signal \axi_rdata[13]_i_3_n_0\ : STD_LOGIC;
  signal \axi_rdata[13]_i_4_n_0\ : STD_LOGIC;
  signal \axi_rdata[13]_i_5_n_0\ : STD_LOGIC;
  signal \axi_rdata[14]_i_2_n_0\ : STD_LOGIC;
  signal \axi_rdata[14]_i_3_n_0\ : STD_LOGIC;
  signal \axi_rdata[14]_i_4_n_0\ : STD_LOGIC;
  signal \axi_rdata[14]_i_5_n_0\ : STD_LOGIC;
  signal \axi_rdata[15]_i_2_n_0\ : STD_LOGIC;
  signal \axi_rdata[15]_i_3_n_0\ : STD_LOGIC;
  signal \axi_rdata[15]_i_4_n_0\ : STD_LOGIC;
  signal \axi_rdata[15]_i_5_n_0\ : STD_LOGIC;
  signal \axi_rdata[16]_i_2_n_0\ : STD_LOGIC;
  signal \axi_rdata[16]_i_3_n_0\ : STD_LOGIC;
  signal \axi_rdata[16]_i_4_n_0\ : STD_LOGIC;
  signal \axi_rdata[16]_i_5_n_0\ : STD_LOGIC;
  signal \axi_rdata[17]_i_2_n_0\ : STD_LOGIC;
  signal \axi_rdata[17]_i_3_n_0\ : STD_LOGIC;
  signal \axi_rdata[17]_i_4_n_0\ : STD_LOGIC;
  signal \axi_rdata[17]_i_5_n_0\ : STD_LOGIC;
  signal \axi_rdata[18]_i_2_n_0\ : STD_LOGIC;
  signal \axi_rdata[18]_i_3_n_0\ : STD_LOGIC;
  signal \axi_rdata[18]_i_4_n_0\ : STD_LOGIC;
  signal \axi_rdata[18]_i_5_n_0\ : STD_LOGIC;
  signal \axi_rdata[19]_i_2_n_0\ : STD_LOGIC;
  signal \axi_rdata[19]_i_3_n_0\ : STD_LOGIC;
  signal \axi_rdata[19]_i_4_n_0\ : STD_LOGIC;
  signal \axi_rdata[19]_i_5_n_0\ : STD_LOGIC;
  signal \axi_rdata[1]_i_2_n_0\ : STD_LOGIC;
  signal \axi_rdata[1]_i_3_n_0\ : STD_LOGIC;
  signal \axi_rdata[1]_i_4_n_0\ : STD_LOGIC;
  signal \axi_rdata[1]_i_5_n_0\ : STD_LOGIC;
  signal \axi_rdata[20]_i_2_n_0\ : STD_LOGIC;
  signal \axi_rdata[20]_i_3_n_0\ : STD_LOGIC;
  signal \axi_rdata[20]_i_4_n_0\ : STD_LOGIC;
  signal \axi_rdata[20]_i_5_n_0\ : STD_LOGIC;
  signal \axi_rdata[21]_i_2_n_0\ : STD_LOGIC;
  signal \axi_rdata[21]_i_3_n_0\ : STD_LOGIC;
  signal \axi_rdata[21]_i_4_n_0\ : STD_LOGIC;
  signal \axi_rdata[21]_i_5_n_0\ : STD_LOGIC;
  signal \axi_rdata[22]_i_2_n_0\ : STD_LOGIC;
  signal \axi_rdata[22]_i_3_n_0\ : STD_LOGIC;
  signal \axi_rdata[22]_i_4_n_0\ : STD_LOGIC;
  signal \axi_rdata[22]_i_5_n_0\ : STD_LOGIC;
  signal \axi_rdata[23]_i_2_n_0\ : STD_LOGIC;
  signal \axi_rdata[23]_i_3_n_0\ : STD_LOGIC;
  signal \axi_rdata[23]_i_4_n_0\ : STD_LOGIC;
  signal \axi_rdata[23]_i_5_n_0\ : STD_LOGIC;
  signal \axi_rdata[24]_i_2_n_0\ : STD_LOGIC;
  signal \axi_rdata[24]_i_3_n_0\ : STD_LOGIC;
  signal \axi_rdata[24]_i_4_n_0\ : STD_LOGIC;
  signal \axi_rdata[24]_i_5_n_0\ : STD_LOGIC;
  signal \axi_rdata[25]_i_2_n_0\ : STD_LOGIC;
  signal \axi_rdata[25]_i_3_n_0\ : STD_LOGIC;
  signal \axi_rdata[25]_i_4_n_0\ : STD_LOGIC;
  signal \axi_rdata[25]_i_5_n_0\ : STD_LOGIC;
  signal \axi_rdata[26]_i_2_n_0\ : STD_LOGIC;
  signal \axi_rdata[26]_i_3_n_0\ : STD_LOGIC;
  signal \axi_rdata[26]_i_4_n_0\ : STD_LOGIC;
  signal \axi_rdata[26]_i_5_n_0\ : STD_LOGIC;
  signal \axi_rdata[27]_i_2_n_0\ : STD_LOGIC;
  signal \axi_rdata[27]_i_3_n_0\ : STD_LOGIC;
  signal \axi_rdata[27]_i_4_n_0\ : STD_LOGIC;
  signal \axi_rdata[27]_i_5_n_0\ : STD_LOGIC;
  signal \axi_rdata[28]_i_2_n_0\ : STD_LOGIC;
  signal \axi_rdata[28]_i_3_n_0\ : STD_LOGIC;
  signal \axi_rdata[28]_i_4_n_0\ : STD_LOGIC;
  signal \axi_rdata[28]_i_5_n_0\ : STD_LOGIC;
  signal \axi_rdata[29]_i_2_n_0\ : STD_LOGIC;
  signal \axi_rdata[29]_i_3_n_0\ : STD_LOGIC;
  signal \axi_rdata[29]_i_4_n_0\ : STD_LOGIC;
  signal \axi_rdata[29]_i_5_n_0\ : STD_LOGIC;
  signal \axi_rdata[2]_i_2_n_0\ : STD_LOGIC;
  signal \axi_rdata[2]_i_3_n_0\ : STD_LOGIC;
  signal \axi_rdata[2]_i_4_n_0\ : STD_LOGIC;
  signal \axi_rdata[2]_i_5_n_0\ : STD_LOGIC;
  signal \axi_rdata[30]_i_2_n_0\ : STD_LOGIC;
  signal \axi_rdata[30]_i_3_n_0\ : STD_LOGIC;
  signal \axi_rdata[30]_i_4_n_0\ : STD_LOGIC;
  signal \axi_rdata[30]_i_5_n_0\ : STD_LOGIC;
  signal \axi_rdata[31]_i_3_n_0\ : STD_LOGIC;
  signal \axi_rdata[31]_i_4_n_0\ : STD_LOGIC;
  signal \axi_rdata[31]_i_5_n_0\ : STD_LOGIC;
  signal \axi_rdata[31]_i_6_n_0\ : STD_LOGIC;
  signal \axi_rdata[3]_i_2_n_0\ : STD_LOGIC;
  signal \axi_rdata[3]_i_3_n_0\ : STD_LOGIC;
  signal \axi_rdata[3]_i_4_n_0\ : STD_LOGIC;
  signal \axi_rdata[3]_i_5_n_0\ : STD_LOGIC;
  signal \axi_rdata[4]_i_2_n_0\ : STD_LOGIC;
  signal \axi_rdata[4]_i_3_n_0\ : STD_LOGIC;
  signal \axi_rdata[4]_i_4_n_0\ : STD_LOGIC;
  signal \axi_rdata[4]_i_5_n_0\ : STD_LOGIC;
  signal \axi_rdata[5]_i_2_n_0\ : STD_LOGIC;
  signal \axi_rdata[5]_i_3_n_0\ : STD_LOGIC;
  signal \axi_rdata[5]_i_4_n_0\ : STD_LOGIC;
  signal \axi_rdata[5]_i_5_n_0\ : STD_LOGIC;
  signal \axi_rdata[6]_i_2_n_0\ : STD_LOGIC;
  signal \axi_rdata[6]_i_3_n_0\ : STD_LOGIC;
  signal \axi_rdata[6]_i_4_n_0\ : STD_LOGIC;
  signal \axi_rdata[6]_i_5_n_0\ : STD_LOGIC;
  signal \axi_rdata[7]_i_2_n_0\ : STD_LOGIC;
  signal \axi_rdata[7]_i_3_n_0\ : STD_LOGIC;
  signal \axi_rdata[7]_i_4_n_0\ : STD_LOGIC;
  signal \axi_rdata[7]_i_5_n_0\ : STD_LOGIC;
  signal \axi_rdata[8]_i_2_n_0\ : STD_LOGIC;
  signal \axi_rdata[8]_i_3_n_0\ : STD_LOGIC;
  signal \axi_rdata[8]_i_4_n_0\ : STD_LOGIC;
  signal \axi_rdata[8]_i_5_n_0\ : STD_LOGIC;
  signal \axi_rdata[9]_i_2_n_0\ : STD_LOGIC;
  signal \axi_rdata[9]_i_3_n_0\ : STD_LOGIC;
  signal \axi_rdata[9]_i_4_n_0\ : STD_LOGIC;
  signal \axi_rdata[9]_i_5_n_0\ : STD_LOGIC;
  signal \axi_rdata_reg[0]_i_2_n_0\ : STD_LOGIC;
  signal \axi_rdata_reg[0]_i_3_n_0\ : STD_LOGIC;
  signal axi_rvalid_i_1_n_0 : STD_LOGIC;
  signal axi_wready0 : STD_LOGIC;
  signal \^axi_wready_reg_0\ : STD_LOGIC;
  signal \^nxtstate\ : STD_LOGIC_VECTOR ( 1 downto 0 );
  signal p_0_in : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal p_0_in13_in : STD_LOGIC;
  signal p_1_in : STD_LOGIC_VECTOR ( 31 downto 7 );
  signal reg_data_out : STD_LOGIC_VECTOR ( 31 downto 0 );
  signal \^s00_axi_bvalid\ : STD_LOGIC;
  signal \^s00_axi_rvalid\ : STD_LOGIC;
  signal sel0 : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal slv_reg10 : STD_LOGIC_VECTOR ( 31 downto 0 );
  signal \slv_reg10[15]_i_1_n_0\ : STD_LOGIC;
  signal \slv_reg10[23]_i_1_n_0\ : STD_LOGIC;
  signal \slv_reg10[31]_i_1_n_0\ : STD_LOGIC;
  signal \slv_reg10[7]_i_1_n_0\ : STD_LOGIC;
  signal slv_reg11 : STD_LOGIC_VECTOR ( 31 downto 0 );
  signal \slv_reg11[15]_i_1_n_0\ : STD_LOGIC;
  signal \slv_reg11[23]_i_1_n_0\ : STD_LOGIC;
  signal \slv_reg11[31]_i_1_n_0\ : STD_LOGIC;
  signal \slv_reg11[7]_i_1_n_0\ : STD_LOGIC;
  signal slv_reg12 : STD_LOGIC_VECTOR ( 31 downto 0 );
  signal \slv_reg12[15]_i_1_n_0\ : STD_LOGIC;
  signal \slv_reg12[23]_i_1_n_0\ : STD_LOGIC;
  signal \slv_reg12[31]_i_1_n_0\ : STD_LOGIC;
  signal \slv_reg12[7]_i_1_n_0\ : STD_LOGIC;
  signal slv_reg13 : STD_LOGIC_VECTOR ( 31 downto 0 );
  signal \slv_reg13[15]_i_1_n_0\ : STD_LOGIC;
  signal \slv_reg13[23]_i_1_n_0\ : STD_LOGIC;
  signal \slv_reg13[31]_i_1_n_0\ : STD_LOGIC;
  signal \slv_reg13[7]_i_1_n_0\ : STD_LOGIC;
  signal slv_reg14 : STD_LOGIC_VECTOR ( 31 downto 0 );
  signal \slv_reg14[15]_i_1_n_0\ : STD_LOGIC;
  signal \slv_reg14[23]_i_1_n_0\ : STD_LOGIC;
  signal \slv_reg14[31]_i_1_n_0\ : STD_LOGIC;
  signal \slv_reg14[7]_i_1_n_0\ : STD_LOGIC;
  signal slv_reg15 : STD_LOGIC_VECTOR ( 31 downto 0 );
  signal \slv_reg15[15]_i_1_n_0\ : STD_LOGIC;
  signal \slv_reg15[23]_i_1_n_0\ : STD_LOGIC;
  signal \slv_reg15[31]_i_1_n_0\ : STD_LOGIC;
  signal \slv_reg15[7]_i_1_n_0\ : STD_LOGIC;
  signal slv_reg_rden : STD_LOGIC;
  signal \slv_reg_wren__0\ : STD_LOGIC;
  attribute SOFT_HLUTNM : string;
  attribute SOFT_HLUTNM of \ADC_SPI_CR[1]_i_1\ : label is "soft_lutpair30";
  attribute SOFT_HLUTNM of \ADC_SPI_CR[31]_i_5\ : label is "soft_lutpair0";
  attribute SOFT_HLUTNM of \ADC_SPI_CR[3]_i_1\ : label is "soft_lutpair30";
  attribute SOFT_HLUTNM of \ADC_SPI_CR[6]_i_1\ : label is "soft_lutpair0";
  attribute SOFT_HLUTNM of \S_ADC_CR_IN[2]_i_2\ : label is "soft_lutpair4";
  attribute SOFT_HLUTNM of \S_ADC_SPI_CR_IN[3]_i_1\ : label is "soft_lutpair2";
  attribute SOFT_HLUTNM of \S_CONVERSION[107]_i_1\ : label is "soft_lutpair27";
  attribute SOFT_HLUTNM of \S_CONVERSION[125]_i_1\ : label is "soft_lutpair28";
  attribute SOFT_HLUTNM of \S_CONVERSION[143]_i_1\ : label is "soft_lutpair29";
  attribute SOFT_HLUTNM of \S_CONVERSION[17]_i_1\ : label is "soft_lutpair22";
  attribute SOFT_HLUTNM of \S_CONVERSION[35]_i_1\ : label is "soft_lutpair23";
  attribute SOFT_HLUTNM of \S_CONVERSION[53]_i_1\ : label is "soft_lutpair24";
  attribute SOFT_HLUTNM of \S_CONVERSION[71]_i_1\ : label is "soft_lutpair25";
  attribute SOFT_HLUTNM of \S_CONVERSION[89]_i_1\ : label is "soft_lutpair26";
  attribute SOFT_HLUTNM of \S_ENABLE[0]_i_3\ : label is "soft_lutpair5";
  attribute SOFT_HLUTNM of \S_ENABLE[0]_i_4\ : label is "soft_lutpair5";
  attribute SOFT_HLUTNM of \S_OFFSET[111]_i_1\ : label is "soft_lutpair28";
  attribute SOFT_HLUTNM of \S_OFFSET[127]_i_1\ : label is "soft_lutpair29";
  attribute SOFT_HLUTNM of \S_OFFSET[15]_i_1\ : label is "soft_lutpair22";
  attribute SOFT_HLUTNM of \S_OFFSET[31]_i_1\ : label is "soft_lutpair23";
  attribute SOFT_HLUTNM of \S_OFFSET[47]_i_1\ : label is "soft_lutpair24";
  attribute SOFT_HLUTNM of \S_OFFSET[63]_i_1\ : label is "soft_lutpair25";
  attribute SOFT_HLUTNM of \S_OFFSET[79]_i_1\ : label is "soft_lutpair26";
  attribute SOFT_HLUTNM of \S_OFFSET[95]_i_1\ : label is "soft_lutpair27";
  attribute SOFT_HLUTNM of \S_SCLK_IN[0]_i_1\ : label is "soft_lutpair2";
  attribute SOFT_HLUTNM of \S_SET_CONVERSION[0]_i_1\ : label is "soft_lutpair1";
  attribute SOFT_HLUTNM of \S_SET_CONVERSION[0]_i_2\ : label is "soft_lutpair6";
  attribute SOFT_HLUTNM of \S_SET_OFFSET[0]_i_1\ : label is "soft_lutpair6";
  attribute SOFT_HLUTNM of \S_SET_SAMPLES[0]_i_1\ : label is "soft_lutpair1";
  attribute SOFT_HLUTNM of \S_SET_SAMPLE_TIME[0]_i_1\ : label is "soft_lutpair4";
  attribute SOFT_HLUTNM of \S_SPI_MANUAL[0]_i_1\ : label is "soft_lutpair3";
  attribute SOFT_HLUTNM of \axi_rdata[10]_i_4\ : label is "soft_lutpair11";
  attribute SOFT_HLUTNM of \axi_rdata[11]_i_4\ : label is "soft_lutpair12";
  attribute SOFT_HLUTNM of \axi_rdata[12]_i_4\ : label is "soft_lutpair12";
  attribute SOFT_HLUTNM of \axi_rdata[13]_i_4\ : label is "soft_lutpair13";
  attribute SOFT_HLUTNM of \axi_rdata[14]_i_4\ : label is "soft_lutpair13";
  attribute SOFT_HLUTNM of \axi_rdata[15]_i_4\ : label is "soft_lutpair14";
  attribute SOFT_HLUTNM of \axi_rdata[16]_i_4\ : label is "soft_lutpair14";
  attribute SOFT_HLUTNM of \axi_rdata[17]_i_4\ : label is "soft_lutpair15";
  attribute SOFT_HLUTNM of \axi_rdata[18]_i_4\ : label is "soft_lutpair15";
  attribute SOFT_HLUTNM of \axi_rdata[19]_i_4\ : label is "soft_lutpair16";
  attribute SOFT_HLUTNM of \axi_rdata[1]_i_4\ : label is "soft_lutpair7";
  attribute SOFT_HLUTNM of \axi_rdata[20]_i_4\ : label is "soft_lutpair16";
  attribute SOFT_HLUTNM of \axi_rdata[21]_i_4\ : label is "soft_lutpair17";
  attribute SOFT_HLUTNM of \axi_rdata[22]_i_4\ : label is "soft_lutpair17";
  attribute SOFT_HLUTNM of \axi_rdata[23]_i_4\ : label is "soft_lutpair18";
  attribute SOFT_HLUTNM of \axi_rdata[24]_i_4\ : label is "soft_lutpair18";
  attribute SOFT_HLUTNM of \axi_rdata[25]_i_4\ : label is "soft_lutpair19";
  attribute SOFT_HLUTNM of \axi_rdata[26]_i_4\ : label is "soft_lutpair19";
  attribute SOFT_HLUTNM of \axi_rdata[27]_i_4\ : label is "soft_lutpair20";
  attribute SOFT_HLUTNM of \axi_rdata[28]_i_4\ : label is "soft_lutpair20";
  attribute SOFT_HLUTNM of \axi_rdata[29]_i_4\ : label is "soft_lutpair21";
  attribute SOFT_HLUTNM of \axi_rdata[2]_i_4\ : label is "soft_lutpair7";
  attribute SOFT_HLUTNM of \axi_rdata[30]_i_4\ : label is "soft_lutpair21";
  attribute SOFT_HLUTNM of \axi_rdata[3]_i_4\ : label is "soft_lutpair8";
  attribute SOFT_HLUTNM of \axi_rdata[4]_i_4\ : label is "soft_lutpair8";
  attribute SOFT_HLUTNM of \axi_rdata[5]_i_4\ : label is "soft_lutpair9";
  attribute SOFT_HLUTNM of \axi_rdata[6]_i_4\ : label is "soft_lutpair9";
  attribute SOFT_HLUTNM of \axi_rdata[7]_i_4\ : label is "soft_lutpair10";
  attribute SOFT_HLUTNM of \axi_rdata[8]_i_4\ : label is "soft_lutpair10";
  attribute SOFT_HLUTNM of \axi_rdata[9]_i_4\ : label is "soft_lutpair11";
  attribute SOFT_HLUTNM of \curstate[1]_i_1__0\ : label is "soft_lutpair3";
begin
  \ADC_CONV_VALUE_reg[30]_0\(30 downto 0) <= \^adc_conv_value_reg[30]_0\(30 downto 0);
  \ADC_CR_reg[3]_0\(0) <= \^adc_cr_reg[3]_0\(0);
  CPHA <= \^cpha\;
  CPOL <= \^cpol\;
  D(1 downto 0) <= \^d\(1 downto 0);
  Q(31 downto 0) <= \^q\(31 downto 0);
  RSTP <= \^rstp\;
  S_AXI_ARESETN <= \^s_axi_aresetn\;
  axi_arready_reg_0 <= \^axi_arready_reg_0\;
  axi_awready_reg_0 <= \^axi_awready_reg_0\;
  axi_wready_reg_0 <= \^axi_wready_reg_0\;
  nxtstate(1 downto 0) <= \^nxtstate\(1 downto 0);
  s00_axi_bvalid <= \^s00_axi_bvalid\;
  s00_axi_rvalid <= \^s00_axi_rvalid\;
\ADC_AVAILABLE[15]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0000000000008000"
    )
        port map (
      I0 => \slv_reg_wren__0\,
      I1 => p_0_in(3),
      I2 => p_0_in(0),
      I3 => s00_axi_wstrb(1),
      I4 => p_0_in(1),
      I5 => p_0_in(2),
      O => \ADC_AVAILABLE[15]_i_1_n_0\
    );
\ADC_AVAILABLE[23]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0000000000008000"
    )
        port map (
      I0 => \slv_reg_wren__0\,
      I1 => p_0_in(3),
      I2 => p_0_in(0),
      I3 => s00_axi_wstrb(2),
      I4 => p_0_in(1),
      I5 => p_0_in(2),
      O => \ADC_AVAILABLE[23]_i_1_n_0\
    );
\ADC_AVAILABLE[31]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0000000000008000"
    )
        port map (
      I0 => \slv_reg_wren__0\,
      I1 => p_0_in(3),
      I2 => p_0_in(0),
      I3 => s00_axi_wstrb(3),
      I4 => p_0_in(1),
      I5 => p_0_in(2),
      O => \ADC_AVAILABLE[31]_i_1_n_0\
    );
\ADC_AVAILABLE[7]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0000000000008000"
    )
        port map (
      I0 => \slv_reg_wren__0\,
      I1 => p_0_in(3),
      I2 => p_0_in(0),
      I3 => s00_axi_wstrb(0),
      I4 => p_0_in(1),
      I5 => p_0_in(2),
      O => \ADC_AVAILABLE[7]_i_1_n_0\
    );
\ADC_AVAILABLE_reg[0]\: unisim.vcomponents.FDSE
     port map (
      C => s00_axi_aclk,
      CE => \ADC_AVAILABLE[7]_i_1_n_0\,
      D => s00_axi_wdata(0),
      Q => S_ADC_AVAILABLE,
      S => \^rstp\
    );
\ADC_AVAILABLE_reg[10]\: unisim.vcomponents.FDSE
     port map (
      C => s00_axi_aclk,
      CE => \ADC_AVAILABLE[15]_i_1_n_0\,
      D => s00_axi_wdata(10),
      Q => \ADC_AVAILABLE_reg_n_0_[10]\,
      S => \^rstp\
    );
\ADC_AVAILABLE_reg[11]\: unisim.vcomponents.FDSE
     port map (
      C => s00_axi_aclk,
      CE => \ADC_AVAILABLE[15]_i_1_n_0\,
      D => s00_axi_wdata(11),
      Q => \ADC_AVAILABLE_reg_n_0_[11]\,
      S => \^rstp\
    );
\ADC_AVAILABLE_reg[12]\: unisim.vcomponents.FDSE
     port map (
      C => s00_axi_aclk,
      CE => \ADC_AVAILABLE[15]_i_1_n_0\,
      D => s00_axi_wdata(12),
      Q => \ADC_AVAILABLE_reg_n_0_[12]\,
      S => \^rstp\
    );
\ADC_AVAILABLE_reg[13]\: unisim.vcomponents.FDSE
     port map (
      C => s00_axi_aclk,
      CE => \ADC_AVAILABLE[15]_i_1_n_0\,
      D => s00_axi_wdata(13),
      Q => \ADC_AVAILABLE_reg_n_0_[13]\,
      S => \^rstp\
    );
\ADC_AVAILABLE_reg[14]\: unisim.vcomponents.FDSE
     port map (
      C => s00_axi_aclk,
      CE => \ADC_AVAILABLE[15]_i_1_n_0\,
      D => s00_axi_wdata(14),
      Q => \ADC_AVAILABLE_reg_n_0_[14]\,
      S => \^rstp\
    );
\ADC_AVAILABLE_reg[15]\: unisim.vcomponents.FDSE
     port map (
      C => s00_axi_aclk,
      CE => \ADC_AVAILABLE[15]_i_1_n_0\,
      D => s00_axi_wdata(15),
      Q => \ADC_AVAILABLE_reg_n_0_[15]\,
      S => \^rstp\
    );
\ADC_AVAILABLE_reg[16]\: unisim.vcomponents.FDSE
     port map (
      C => s00_axi_aclk,
      CE => \ADC_AVAILABLE[23]_i_1_n_0\,
      D => s00_axi_wdata(16),
      Q => \ADC_AVAILABLE_reg_n_0_[16]\,
      S => \^rstp\
    );
\ADC_AVAILABLE_reg[17]\: unisim.vcomponents.FDSE
     port map (
      C => s00_axi_aclk,
      CE => \ADC_AVAILABLE[23]_i_1_n_0\,
      D => s00_axi_wdata(17),
      Q => \ADC_AVAILABLE_reg_n_0_[17]\,
      S => \^rstp\
    );
\ADC_AVAILABLE_reg[18]\: unisim.vcomponents.FDSE
     port map (
      C => s00_axi_aclk,
      CE => \ADC_AVAILABLE[23]_i_1_n_0\,
      D => s00_axi_wdata(18),
      Q => \ADC_AVAILABLE_reg_n_0_[18]\,
      S => \^rstp\
    );
\ADC_AVAILABLE_reg[19]\: unisim.vcomponents.FDSE
     port map (
      C => s00_axi_aclk,
      CE => \ADC_AVAILABLE[23]_i_1_n_0\,
      D => s00_axi_wdata(19),
      Q => \ADC_AVAILABLE_reg_n_0_[19]\,
      S => \^rstp\
    );
\ADC_AVAILABLE_reg[1]\: unisim.vcomponents.FDSE
     port map (
      C => s00_axi_aclk,
      CE => \ADC_AVAILABLE[7]_i_1_n_0\,
      D => s00_axi_wdata(1),
      Q => \ADC_AVAILABLE_reg_n_0_[1]\,
      S => \^rstp\
    );
\ADC_AVAILABLE_reg[20]\: unisim.vcomponents.FDSE
     port map (
      C => s00_axi_aclk,
      CE => \ADC_AVAILABLE[23]_i_1_n_0\,
      D => s00_axi_wdata(20),
      Q => \ADC_AVAILABLE_reg_n_0_[20]\,
      S => \^rstp\
    );
\ADC_AVAILABLE_reg[21]\: unisim.vcomponents.FDSE
     port map (
      C => s00_axi_aclk,
      CE => \ADC_AVAILABLE[23]_i_1_n_0\,
      D => s00_axi_wdata(21),
      Q => \ADC_AVAILABLE_reg_n_0_[21]\,
      S => \^rstp\
    );
\ADC_AVAILABLE_reg[22]\: unisim.vcomponents.FDSE
     port map (
      C => s00_axi_aclk,
      CE => \ADC_AVAILABLE[23]_i_1_n_0\,
      D => s00_axi_wdata(22),
      Q => \ADC_AVAILABLE_reg_n_0_[22]\,
      S => \^rstp\
    );
\ADC_AVAILABLE_reg[23]\: unisim.vcomponents.FDSE
     port map (
      C => s00_axi_aclk,
      CE => \ADC_AVAILABLE[23]_i_1_n_0\,
      D => s00_axi_wdata(23),
      Q => \ADC_AVAILABLE_reg_n_0_[23]\,
      S => \^rstp\
    );
\ADC_AVAILABLE_reg[24]\: unisim.vcomponents.FDSE
     port map (
      C => s00_axi_aclk,
      CE => \ADC_AVAILABLE[31]_i_1_n_0\,
      D => s00_axi_wdata(24),
      Q => \ADC_AVAILABLE_reg_n_0_[24]\,
      S => \^rstp\
    );
\ADC_AVAILABLE_reg[25]\: unisim.vcomponents.FDSE
     port map (
      C => s00_axi_aclk,
      CE => \ADC_AVAILABLE[31]_i_1_n_0\,
      D => s00_axi_wdata(25),
      Q => \ADC_AVAILABLE_reg_n_0_[25]\,
      S => \^rstp\
    );
\ADC_AVAILABLE_reg[26]\: unisim.vcomponents.FDSE
     port map (
      C => s00_axi_aclk,
      CE => \ADC_AVAILABLE[31]_i_1_n_0\,
      D => s00_axi_wdata(26),
      Q => \ADC_AVAILABLE_reg_n_0_[26]\,
      S => \^rstp\
    );
\ADC_AVAILABLE_reg[27]\: unisim.vcomponents.FDSE
     port map (
      C => s00_axi_aclk,
      CE => \ADC_AVAILABLE[31]_i_1_n_0\,
      D => s00_axi_wdata(27),
      Q => \ADC_AVAILABLE_reg_n_0_[27]\,
      S => \^rstp\
    );
\ADC_AVAILABLE_reg[28]\: unisim.vcomponents.FDSE
     port map (
      C => s00_axi_aclk,
      CE => \ADC_AVAILABLE[31]_i_1_n_0\,
      D => s00_axi_wdata(28),
      Q => \ADC_AVAILABLE_reg_n_0_[28]\,
      S => \^rstp\
    );
\ADC_AVAILABLE_reg[29]\: unisim.vcomponents.FDSE
     port map (
      C => s00_axi_aclk,
      CE => \ADC_AVAILABLE[31]_i_1_n_0\,
      D => s00_axi_wdata(29),
      Q => \ADC_AVAILABLE_reg_n_0_[29]\,
      S => \^rstp\
    );
\ADC_AVAILABLE_reg[2]\: unisim.vcomponents.FDSE
     port map (
      C => s00_axi_aclk,
      CE => \ADC_AVAILABLE[7]_i_1_n_0\,
      D => s00_axi_wdata(2),
      Q => \ADC_AVAILABLE_reg_n_0_[2]\,
      S => \^rstp\
    );
\ADC_AVAILABLE_reg[30]\: unisim.vcomponents.FDSE
     port map (
      C => s00_axi_aclk,
      CE => \ADC_AVAILABLE[31]_i_1_n_0\,
      D => s00_axi_wdata(30),
      Q => \ADC_AVAILABLE_reg_n_0_[30]\,
      S => \^rstp\
    );
\ADC_AVAILABLE_reg[31]\: unisim.vcomponents.FDSE
     port map (
      C => s00_axi_aclk,
      CE => \ADC_AVAILABLE[31]_i_1_n_0\,
      D => s00_axi_wdata(31),
      Q => \ADC_AVAILABLE_reg_n_0_[31]\,
      S => \^rstp\
    );
\ADC_AVAILABLE_reg[3]\: unisim.vcomponents.FDSE
     port map (
      C => s00_axi_aclk,
      CE => \ADC_AVAILABLE[7]_i_1_n_0\,
      D => s00_axi_wdata(3),
      Q => \ADC_AVAILABLE_reg_n_0_[3]\,
      S => \^rstp\
    );
\ADC_AVAILABLE_reg[4]\: unisim.vcomponents.FDSE
     port map (
      C => s00_axi_aclk,
      CE => \ADC_AVAILABLE[7]_i_1_n_0\,
      D => s00_axi_wdata(4),
      Q => \ADC_AVAILABLE_reg_n_0_[4]\,
      S => \^rstp\
    );
\ADC_AVAILABLE_reg[5]\: unisim.vcomponents.FDSE
     port map (
      C => s00_axi_aclk,
      CE => \ADC_AVAILABLE[7]_i_1_n_0\,
      D => s00_axi_wdata(5),
      Q => \ADC_AVAILABLE_reg_n_0_[5]\,
      S => \^rstp\
    );
\ADC_AVAILABLE_reg[6]\: unisim.vcomponents.FDSE
     port map (
      C => s00_axi_aclk,
      CE => \ADC_AVAILABLE[7]_i_1_n_0\,
      D => s00_axi_wdata(6),
      Q => \ADC_AVAILABLE_reg_n_0_[6]\,
      S => \^rstp\
    );
\ADC_AVAILABLE_reg[7]\: unisim.vcomponents.FDSE
     port map (
      C => s00_axi_aclk,
      CE => \ADC_AVAILABLE[7]_i_1_n_0\,
      D => s00_axi_wdata(7),
      Q => \ADC_AVAILABLE_reg_n_0_[7]\,
      S => \^rstp\
    );
\ADC_AVAILABLE_reg[8]\: unisim.vcomponents.FDSE
     port map (
      C => s00_axi_aclk,
      CE => \ADC_AVAILABLE[15]_i_1_n_0\,
      D => s00_axi_wdata(8),
      Q => \ADC_AVAILABLE_reg_n_0_[8]\,
      S => \^rstp\
    );
\ADC_AVAILABLE_reg[9]\: unisim.vcomponents.FDSE
     port map (
      C => s00_axi_aclk,
      CE => \ADC_AVAILABLE[15]_i_1_n_0\,
      D => s00_axi_wdata(9),
      Q => \ADC_AVAILABLE_reg_n_0_[9]\,
      S => \^rstp\
    );
\ADC_CHANNEL[15]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0000000800000000"
    )
        port map (
      I0 => \slv_reg_wren__0\,
      I1 => s00_axi_wstrb(1),
      I2 => p_0_in(3),
      I3 => p_0_in(1),
      I4 => p_0_in(0),
      I5 => p_0_in(2),
      O => \ADC_CHANNEL[15]_i_1_n_0\
    );
\ADC_CHANNEL[23]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0000000800000000"
    )
        port map (
      I0 => \slv_reg_wren__0\,
      I1 => s00_axi_wstrb(2),
      I2 => p_0_in(3),
      I3 => p_0_in(1),
      I4 => p_0_in(0),
      I5 => p_0_in(2),
      O => \ADC_CHANNEL[23]_i_1_n_0\
    );
\ADC_CHANNEL[31]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0000000800000000"
    )
        port map (
      I0 => \slv_reg_wren__0\,
      I1 => s00_axi_wstrb(3),
      I2 => p_0_in(3),
      I3 => p_0_in(1),
      I4 => p_0_in(0),
      I5 => p_0_in(2),
      O => \ADC_CHANNEL[31]_i_1_n_0\
    );
\ADC_CHANNEL[7]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0000000800000000"
    )
        port map (
      I0 => \slv_reg_wren__0\,
      I1 => s00_axi_wstrb(0),
      I2 => p_0_in(3),
      I3 => p_0_in(1),
      I4 => p_0_in(0),
      I5 => p_0_in(2),
      O => \ADC_CHANNEL[7]_i_1_n_0\
    );
\ADC_CHANNEL_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \ADC_CHANNEL[7]_i_1_n_0\,
      D => s00_axi_wdata(0),
      Q => S_ADC_CHANNEL(0),
      R => \^rstp\
    );
\ADC_CHANNEL_reg[10]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \ADC_CHANNEL[15]_i_1_n_0\,
      D => s00_axi_wdata(10),
      Q => S_ADC_CHANNEL(10),
      R => \^rstp\
    );
\ADC_CHANNEL_reg[11]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \ADC_CHANNEL[15]_i_1_n_0\,
      D => s00_axi_wdata(11),
      Q => S_ADC_CHANNEL(11),
      R => \^rstp\
    );
\ADC_CHANNEL_reg[12]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \ADC_CHANNEL[15]_i_1_n_0\,
      D => s00_axi_wdata(12),
      Q => S_ADC_CHANNEL(12),
      R => \^rstp\
    );
\ADC_CHANNEL_reg[13]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \ADC_CHANNEL[15]_i_1_n_0\,
      D => s00_axi_wdata(13),
      Q => S_ADC_CHANNEL(13),
      R => \^rstp\
    );
\ADC_CHANNEL_reg[14]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \ADC_CHANNEL[15]_i_1_n_0\,
      D => s00_axi_wdata(14),
      Q => S_ADC_CHANNEL(14),
      R => \^rstp\
    );
\ADC_CHANNEL_reg[15]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \ADC_CHANNEL[15]_i_1_n_0\,
      D => s00_axi_wdata(15),
      Q => S_ADC_CHANNEL(15),
      R => \^rstp\
    );
\ADC_CHANNEL_reg[16]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \ADC_CHANNEL[23]_i_1_n_0\,
      D => s00_axi_wdata(16),
      Q => S_ADC_CHANNEL(16),
      R => \^rstp\
    );
\ADC_CHANNEL_reg[17]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \ADC_CHANNEL[23]_i_1_n_0\,
      D => s00_axi_wdata(17),
      Q => S_ADC_CHANNEL(17),
      R => \^rstp\
    );
\ADC_CHANNEL_reg[18]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \ADC_CHANNEL[23]_i_1_n_0\,
      D => s00_axi_wdata(18),
      Q => S_ADC_CHANNEL(18),
      R => \^rstp\
    );
\ADC_CHANNEL_reg[19]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \ADC_CHANNEL[23]_i_1_n_0\,
      D => s00_axi_wdata(19),
      Q => S_ADC_CHANNEL(19),
      R => \^rstp\
    );
\ADC_CHANNEL_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \ADC_CHANNEL[7]_i_1_n_0\,
      D => s00_axi_wdata(1),
      Q => S_ADC_CHANNEL(1),
      R => \^rstp\
    );
\ADC_CHANNEL_reg[20]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \ADC_CHANNEL[23]_i_1_n_0\,
      D => s00_axi_wdata(20),
      Q => S_ADC_CHANNEL(20),
      R => \^rstp\
    );
\ADC_CHANNEL_reg[21]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \ADC_CHANNEL[23]_i_1_n_0\,
      D => s00_axi_wdata(21),
      Q => S_ADC_CHANNEL(21),
      R => \^rstp\
    );
\ADC_CHANNEL_reg[22]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \ADC_CHANNEL[23]_i_1_n_0\,
      D => s00_axi_wdata(22),
      Q => S_ADC_CHANNEL(22),
      R => \^rstp\
    );
\ADC_CHANNEL_reg[23]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \ADC_CHANNEL[23]_i_1_n_0\,
      D => s00_axi_wdata(23),
      Q => S_ADC_CHANNEL(23),
      R => \^rstp\
    );
\ADC_CHANNEL_reg[24]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \ADC_CHANNEL[31]_i_1_n_0\,
      D => s00_axi_wdata(24),
      Q => S_ADC_CHANNEL(24),
      R => \^rstp\
    );
\ADC_CHANNEL_reg[25]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \ADC_CHANNEL[31]_i_1_n_0\,
      D => s00_axi_wdata(25),
      Q => S_ADC_CHANNEL(25),
      R => \^rstp\
    );
\ADC_CHANNEL_reg[26]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \ADC_CHANNEL[31]_i_1_n_0\,
      D => s00_axi_wdata(26),
      Q => S_ADC_CHANNEL(26),
      R => \^rstp\
    );
\ADC_CHANNEL_reg[27]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \ADC_CHANNEL[31]_i_1_n_0\,
      D => s00_axi_wdata(27),
      Q => S_ADC_CHANNEL(27),
      R => \^rstp\
    );
\ADC_CHANNEL_reg[28]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \ADC_CHANNEL[31]_i_1_n_0\,
      D => s00_axi_wdata(28),
      Q => S_ADC_CHANNEL(28),
      R => \^rstp\
    );
\ADC_CHANNEL_reg[29]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \ADC_CHANNEL[31]_i_1_n_0\,
      D => s00_axi_wdata(29),
      Q => S_ADC_CHANNEL(29),
      R => \^rstp\
    );
\ADC_CHANNEL_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \ADC_CHANNEL[7]_i_1_n_0\,
      D => s00_axi_wdata(2),
      Q => S_ADC_CHANNEL(2),
      R => \^rstp\
    );
\ADC_CHANNEL_reg[30]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \ADC_CHANNEL[31]_i_1_n_0\,
      D => s00_axi_wdata(30),
      Q => S_ADC_CHANNEL(30),
      R => \^rstp\
    );
\ADC_CHANNEL_reg[31]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \ADC_CHANNEL[31]_i_1_n_0\,
      D => s00_axi_wdata(31),
      Q => S_ADC_CHANNEL(31),
      R => \^rstp\
    );
\ADC_CHANNEL_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \ADC_CHANNEL[7]_i_1_n_0\,
      D => s00_axi_wdata(3),
      Q => S_ADC_CHANNEL(3),
      R => \^rstp\
    );
\ADC_CHANNEL_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \ADC_CHANNEL[7]_i_1_n_0\,
      D => s00_axi_wdata(4),
      Q => S_ADC_CHANNEL(4),
      R => \^rstp\
    );
\ADC_CHANNEL_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \ADC_CHANNEL[7]_i_1_n_0\,
      D => s00_axi_wdata(5),
      Q => S_ADC_CHANNEL(5),
      R => \^rstp\
    );
\ADC_CHANNEL_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \ADC_CHANNEL[7]_i_1_n_0\,
      D => s00_axi_wdata(6),
      Q => S_ADC_CHANNEL(6),
      R => \^rstp\
    );
\ADC_CHANNEL_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \ADC_CHANNEL[7]_i_1_n_0\,
      D => s00_axi_wdata(7),
      Q => S_ADC_CHANNEL(7),
      R => \^rstp\
    );
\ADC_CHANNEL_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \ADC_CHANNEL[15]_i_1_n_0\,
      D => s00_axi_wdata(8),
      Q => S_ADC_CHANNEL(8),
      R => \^rstp\
    );
\ADC_CHANNEL_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \ADC_CHANNEL[15]_i_1_n_0\,
      D => s00_axi_wdata(9),
      Q => S_ADC_CHANNEL(9),
      R => \^rstp\
    );
\ADC_CONV_VALUE[15]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0000000800000000"
    )
        port map (
      I0 => \slv_reg_wren__0\,
      I1 => p_0_in(3),
      I2 => p_0_in(1),
      I3 => p_0_in(0),
      I4 => p_0_in(2),
      I5 => s00_axi_wstrb(1),
      O => \ADC_CONV_VALUE[15]_i_1_n_0\
    );
\ADC_CONV_VALUE[23]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0000000800000000"
    )
        port map (
      I0 => \slv_reg_wren__0\,
      I1 => p_0_in(3),
      I2 => p_0_in(1),
      I3 => p_0_in(0),
      I4 => p_0_in(2),
      I5 => s00_axi_wstrb(2),
      O => \ADC_CONV_VALUE[23]_i_1_n_0\
    );
\ADC_CONV_VALUE[31]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0000000800000000"
    )
        port map (
      I0 => \slv_reg_wren__0\,
      I1 => p_0_in(3),
      I2 => p_0_in(1),
      I3 => p_0_in(0),
      I4 => p_0_in(2),
      I5 => s00_axi_wstrb(3),
      O => \ADC_CONV_VALUE[31]_i_1_n_0\
    );
\ADC_CONV_VALUE[7]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0000000800000000"
    )
        port map (
      I0 => \slv_reg_wren__0\,
      I1 => p_0_in(3),
      I2 => p_0_in(1),
      I3 => p_0_in(0),
      I4 => p_0_in(2),
      I5 => s00_axi_wstrb(0),
      O => \ADC_CONV_VALUE[7]_i_1_n_0\
    );
\ADC_CONV_VALUE_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \ADC_CONV_VALUE[7]_i_1_n_0\,
      D => s00_axi_wdata(0),
      Q => \^adc_conv_value_reg[30]_0\(0),
      R => \^rstp\
    );
\ADC_CONV_VALUE_reg[10]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \ADC_CONV_VALUE[15]_i_1_n_0\,
      D => s00_axi_wdata(10),
      Q => \^adc_conv_value_reg[30]_0\(10),
      R => \^rstp\
    );
\ADC_CONV_VALUE_reg[11]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \ADC_CONV_VALUE[15]_i_1_n_0\,
      D => s00_axi_wdata(11),
      Q => \^adc_conv_value_reg[30]_0\(11),
      R => \^rstp\
    );
\ADC_CONV_VALUE_reg[12]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \ADC_CONV_VALUE[15]_i_1_n_0\,
      D => s00_axi_wdata(12),
      Q => \^adc_conv_value_reg[30]_0\(12),
      R => \^rstp\
    );
\ADC_CONV_VALUE_reg[13]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \ADC_CONV_VALUE[15]_i_1_n_0\,
      D => s00_axi_wdata(13),
      Q => \^adc_conv_value_reg[30]_0\(13),
      R => \^rstp\
    );
\ADC_CONV_VALUE_reg[14]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \ADC_CONV_VALUE[15]_i_1_n_0\,
      D => s00_axi_wdata(14),
      Q => \^adc_conv_value_reg[30]_0\(14),
      R => \^rstp\
    );
\ADC_CONV_VALUE_reg[15]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \ADC_CONV_VALUE[15]_i_1_n_0\,
      D => s00_axi_wdata(15),
      Q => \^adc_conv_value_reg[30]_0\(15),
      R => \^rstp\
    );
\ADC_CONV_VALUE_reg[16]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \ADC_CONV_VALUE[23]_i_1_n_0\,
      D => s00_axi_wdata(16),
      Q => \^adc_conv_value_reg[30]_0\(16),
      R => \^rstp\
    );
\ADC_CONV_VALUE_reg[17]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \ADC_CONV_VALUE[23]_i_1_n_0\,
      D => s00_axi_wdata(17),
      Q => \^adc_conv_value_reg[30]_0\(17),
      R => \^rstp\
    );
\ADC_CONV_VALUE_reg[18]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \ADC_CONV_VALUE[23]_i_1_n_0\,
      D => s00_axi_wdata(18),
      Q => \^adc_conv_value_reg[30]_0\(18),
      R => \^rstp\
    );
\ADC_CONV_VALUE_reg[19]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \ADC_CONV_VALUE[23]_i_1_n_0\,
      D => s00_axi_wdata(19),
      Q => \^adc_conv_value_reg[30]_0\(19),
      R => \^rstp\
    );
\ADC_CONV_VALUE_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \ADC_CONV_VALUE[7]_i_1_n_0\,
      D => s00_axi_wdata(1),
      Q => \^adc_conv_value_reg[30]_0\(1),
      R => \^rstp\
    );
\ADC_CONV_VALUE_reg[20]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \ADC_CONV_VALUE[23]_i_1_n_0\,
      D => s00_axi_wdata(20),
      Q => \^adc_conv_value_reg[30]_0\(20),
      R => \^rstp\
    );
\ADC_CONV_VALUE_reg[21]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \ADC_CONV_VALUE[23]_i_1_n_0\,
      D => s00_axi_wdata(21),
      Q => \^adc_conv_value_reg[30]_0\(21),
      R => \^rstp\
    );
\ADC_CONV_VALUE_reg[22]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \ADC_CONV_VALUE[23]_i_1_n_0\,
      D => s00_axi_wdata(22),
      Q => \^adc_conv_value_reg[30]_0\(22),
      R => \^rstp\
    );
\ADC_CONV_VALUE_reg[23]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \ADC_CONV_VALUE[23]_i_1_n_0\,
      D => s00_axi_wdata(23),
      Q => \^adc_conv_value_reg[30]_0\(23),
      R => \^rstp\
    );
\ADC_CONV_VALUE_reg[24]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \ADC_CONV_VALUE[31]_i_1_n_0\,
      D => s00_axi_wdata(24),
      Q => \^adc_conv_value_reg[30]_0\(24),
      R => \^rstp\
    );
\ADC_CONV_VALUE_reg[25]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \ADC_CONV_VALUE[31]_i_1_n_0\,
      D => s00_axi_wdata(25),
      Q => \^adc_conv_value_reg[30]_0\(25),
      R => \^rstp\
    );
\ADC_CONV_VALUE_reg[26]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \ADC_CONV_VALUE[31]_i_1_n_0\,
      D => s00_axi_wdata(26),
      Q => \^adc_conv_value_reg[30]_0\(26),
      R => \^rstp\
    );
\ADC_CONV_VALUE_reg[27]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \ADC_CONV_VALUE[31]_i_1_n_0\,
      D => s00_axi_wdata(27),
      Q => \^adc_conv_value_reg[30]_0\(27),
      R => \^rstp\
    );
\ADC_CONV_VALUE_reg[28]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \ADC_CONV_VALUE[31]_i_1_n_0\,
      D => s00_axi_wdata(28),
      Q => \^adc_conv_value_reg[30]_0\(28),
      R => \^rstp\
    );
\ADC_CONV_VALUE_reg[29]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \ADC_CONV_VALUE[31]_i_1_n_0\,
      D => s00_axi_wdata(29),
      Q => \^adc_conv_value_reg[30]_0\(29),
      R => \^rstp\
    );
\ADC_CONV_VALUE_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \ADC_CONV_VALUE[7]_i_1_n_0\,
      D => s00_axi_wdata(2),
      Q => \^adc_conv_value_reg[30]_0\(2),
      R => \^rstp\
    );
\ADC_CONV_VALUE_reg[30]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \ADC_CONV_VALUE[31]_i_1_n_0\,
      D => s00_axi_wdata(30),
      Q => \^adc_conv_value_reg[30]_0\(30),
      R => \^rstp\
    );
\ADC_CONV_VALUE_reg[31]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \ADC_CONV_VALUE[31]_i_1_n_0\,
      D => s00_axi_wdata(31),
      Q => S_ADC_CONV_VALUE(31),
      R => \^rstp\
    );
\ADC_CONV_VALUE_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \ADC_CONV_VALUE[7]_i_1_n_0\,
      D => s00_axi_wdata(3),
      Q => \^adc_conv_value_reg[30]_0\(3),
      R => \^rstp\
    );
\ADC_CONV_VALUE_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \ADC_CONV_VALUE[7]_i_1_n_0\,
      D => s00_axi_wdata(4),
      Q => \^adc_conv_value_reg[30]_0\(4),
      R => \^rstp\
    );
\ADC_CONV_VALUE_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \ADC_CONV_VALUE[7]_i_1_n_0\,
      D => s00_axi_wdata(5),
      Q => \^adc_conv_value_reg[30]_0\(5),
      R => \^rstp\
    );
\ADC_CONV_VALUE_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \ADC_CONV_VALUE[7]_i_1_n_0\,
      D => s00_axi_wdata(6),
      Q => \^adc_conv_value_reg[30]_0\(6),
      R => \^rstp\
    );
\ADC_CONV_VALUE_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \ADC_CONV_VALUE[7]_i_1_n_0\,
      D => s00_axi_wdata(7),
      Q => \^adc_conv_value_reg[30]_0\(7),
      R => \^rstp\
    );
\ADC_CONV_VALUE_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \ADC_CONV_VALUE[15]_i_1_n_0\,
      D => s00_axi_wdata(8),
      Q => \^adc_conv_value_reg[30]_0\(8),
      R => \^rstp\
    );
\ADC_CONV_VALUE_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \ADC_CONV_VALUE[15]_i_1_n_0\,
      D => s00_axi_wdata(9),
      Q => \^adc_conv_value_reg[30]_0\(9),
      R => \^rstp\
    );
\ADC_CR[15]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"8A"
    )
        port map (
      I0 => ADC_CR(15),
      I1 => \^adc_cr_reg[3]_0\(0),
      I2 => s00_axi_aresetn,
      O => \ADC_CR[15]_i_1_n_0\
    );
\ADC_CR[15]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"00080000FFFFFFFF"
    )
        port map (
      I0 => \ADC_SPI_CR[31]_i_3_n_0\,
      I1 => s00_axi_wstrb(1),
      I2 => p_0_in(0),
      I3 => p_0_in(1),
      I4 => \slv_reg_wren__0\,
      I5 => \^s_axi_aresetn\,
      O => ADC_CR(15)
    );
\ADC_CR[23]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"8A"
    )
        port map (
      I0 => ADC_CR(23),
      I1 => \^adc_cr_reg[3]_0\(0),
      I2 => s00_axi_aresetn,
      O => \ADC_CR[23]_i_1_n_0\
    );
\ADC_CR[23]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"00080000FFFFFFFF"
    )
        port map (
      I0 => \ADC_SPI_CR[31]_i_3_n_0\,
      I1 => s00_axi_wstrb(2),
      I2 => p_0_in(0),
      I3 => p_0_in(1),
      I4 => \slv_reg_wren__0\,
      I5 => \^s_axi_aresetn\,
      O => ADC_CR(23)
    );
\ADC_CR[2]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"50505050D8085050"
    )
        port map (
      I0 => ADC_CR(3),
      I1 => s00_axi_wdata(2),
      I2 => S_ADC_CR(2),
      I3 => P_ADC_CR_IN(0),
      I4 => s00_axi_aresetn,
      I5 => \^adc_cr_reg[3]_0\(0),
      O => \ADC_CR[2]_i_1_n_0\
    );
\ADC_CR[31]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"8A"
    )
        port map (
      I0 => ADC_CR(31),
      I1 => \^adc_cr_reg[3]_0\(0),
      I2 => s00_axi_aresetn,
      O => \ADC_CR[31]_i_1_n_0\
    );
\ADC_CR[31]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"00080000FFFFFFFF"
    )
        port map (
      I0 => \ADC_SPI_CR[31]_i_3_n_0\,
      I1 => s00_axi_wstrb(3),
      I2 => p_0_in(0),
      I3 => p_0_in(1),
      I4 => \slv_reg_wren__0\,
      I5 => \^s_axi_aresetn\,
      O => ADC_CR(31)
    );
\ADC_CR[4]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"50505050D8085050"
    )
        port map (
      I0 => ADC_CR(3),
      I1 => s00_axi_wdata(4),
      I2 => S_ADC_CR(4),
      I3 => P_ADC_CR_IN(1),
      I4 => s00_axi_aresetn,
      I5 => \^adc_cr_reg[3]_0\(0),
      O => \ADC_CR[4]_i_1_n_0\
    );
\ADC_CR[7]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"8A"
    )
        port map (
      I0 => ADC_CR(3),
      I1 => \^adc_cr_reg[3]_0\(0),
      I2 => s00_axi_aresetn,
      O => \ADC_CR[7]_i_1_n_0\
    );
\ADC_CR[7]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"00080000FFFFFFFF"
    )
        port map (
      I0 => \ADC_SPI_CR[31]_i_3_n_0\,
      I1 => s00_axi_wstrb(0),
      I2 => p_0_in(0),
      I3 => p_0_in(1),
      I4 => \slv_reg_wren__0\,
      I5 => \^s_axi_aresetn\,
      O => ADC_CR(3)
    );
\ADC_CR_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => ADC_CR(3),
      D => s00_axi_wdata(0),
      Q => S_ADC_CR(0),
      R => \ADC_CR[7]_i_1_n_0\
    );
\ADC_CR_reg[10]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => ADC_CR(15),
      D => s00_axi_wdata(10),
      Q => \ADC_CR_reg_n_0_[10]\,
      R => \ADC_CR[15]_i_1_n_0\
    );
\ADC_CR_reg[11]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => ADC_CR(15),
      D => s00_axi_wdata(11),
      Q => \ADC_CR_reg_n_0_[11]\,
      R => \ADC_CR[15]_i_1_n_0\
    );
\ADC_CR_reg[12]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => ADC_CR(15),
      D => s00_axi_wdata(12),
      Q => \ADC_CR_reg_n_0_[12]\,
      R => \ADC_CR[15]_i_1_n_0\
    );
\ADC_CR_reg[13]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => ADC_CR(15),
      D => s00_axi_wdata(13),
      Q => \ADC_CR_reg_n_0_[13]\,
      R => \ADC_CR[15]_i_1_n_0\
    );
\ADC_CR_reg[14]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => ADC_CR(15),
      D => s00_axi_wdata(14),
      Q => \ADC_CR_reg_n_0_[14]\,
      R => \ADC_CR[15]_i_1_n_0\
    );
\ADC_CR_reg[15]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => ADC_CR(15),
      D => s00_axi_wdata(15),
      Q => \ADC_CR_reg_n_0_[15]\,
      R => \ADC_CR[15]_i_1_n_0\
    );
\ADC_CR_reg[16]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => ADC_CR(23),
      D => s00_axi_wdata(16),
      Q => \ADC_CR_reg_n_0_[16]\,
      R => \ADC_CR[23]_i_1_n_0\
    );
\ADC_CR_reg[17]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => ADC_CR(23),
      D => s00_axi_wdata(17),
      Q => \ADC_CR_reg_n_0_[17]\,
      R => \ADC_CR[23]_i_1_n_0\
    );
\ADC_CR_reg[18]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => ADC_CR(23),
      D => s00_axi_wdata(18),
      Q => \ADC_CR_reg_n_0_[18]\,
      R => \ADC_CR[23]_i_1_n_0\
    );
\ADC_CR_reg[19]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => ADC_CR(23),
      D => s00_axi_wdata(19),
      Q => \ADC_CR_reg_n_0_[19]\,
      R => \ADC_CR[23]_i_1_n_0\
    );
\ADC_CR_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => ADC_CR(3),
      D => s00_axi_wdata(1),
      Q => S_ADC_CR(1),
      R => \ADC_CR[7]_i_1_n_0\
    );
\ADC_CR_reg[20]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => ADC_CR(23),
      D => s00_axi_wdata(20),
      Q => \ADC_CR_reg_n_0_[20]\,
      R => \ADC_CR[23]_i_1_n_0\
    );
\ADC_CR_reg[21]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => ADC_CR(23),
      D => s00_axi_wdata(21),
      Q => \ADC_CR_reg_n_0_[21]\,
      R => \ADC_CR[23]_i_1_n_0\
    );
\ADC_CR_reg[22]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => ADC_CR(23),
      D => s00_axi_wdata(22),
      Q => \ADC_CR_reg_n_0_[22]\,
      R => \ADC_CR[23]_i_1_n_0\
    );
\ADC_CR_reg[23]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => ADC_CR(23),
      D => s00_axi_wdata(23),
      Q => \ADC_CR_reg_n_0_[23]\,
      R => \ADC_CR[23]_i_1_n_0\
    );
\ADC_CR_reg[24]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => ADC_CR(31),
      D => s00_axi_wdata(24),
      Q => \ADC_CR_reg_n_0_[24]\,
      R => \ADC_CR[31]_i_1_n_0\
    );
\ADC_CR_reg[25]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => ADC_CR(31),
      D => s00_axi_wdata(25),
      Q => \ADC_CR_reg_n_0_[25]\,
      R => \ADC_CR[31]_i_1_n_0\
    );
\ADC_CR_reg[26]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => ADC_CR(31),
      D => s00_axi_wdata(26),
      Q => \ADC_CR_reg_n_0_[26]\,
      R => \ADC_CR[31]_i_1_n_0\
    );
\ADC_CR_reg[27]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => ADC_CR(31),
      D => s00_axi_wdata(27),
      Q => \ADC_CR_reg_n_0_[27]\,
      R => \ADC_CR[31]_i_1_n_0\
    );
\ADC_CR_reg[28]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => ADC_CR(31),
      D => s00_axi_wdata(28),
      Q => \ADC_CR_reg_n_0_[28]\,
      R => \ADC_CR[31]_i_1_n_0\
    );
\ADC_CR_reg[29]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => ADC_CR(31),
      D => s00_axi_wdata(29),
      Q => \ADC_CR_reg_n_0_[29]\,
      R => \ADC_CR[31]_i_1_n_0\
    );
\ADC_CR_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => '1',
      D => \ADC_CR[2]_i_1_n_0\,
      Q => S_ADC_CR(2),
      R => '0'
    );
\ADC_CR_reg[30]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => ADC_CR(31),
      D => s00_axi_wdata(30),
      Q => \ADC_CR_reg_n_0_[30]\,
      R => \ADC_CR[31]_i_1_n_0\
    );
\ADC_CR_reg[31]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => ADC_CR(31),
      D => s00_axi_wdata(31),
      Q => \ADC_CR_reg_n_0_[31]\,
      R => \ADC_CR[31]_i_1_n_0\
    );
\ADC_CR_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => ADC_CR(3),
      D => s00_axi_wdata(3),
      Q => \^adc_cr_reg[3]_0\(0),
      R => \ADC_CR[7]_i_1_n_0\
    );
\ADC_CR_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => '1',
      D => \ADC_CR[4]_i_1_n_0\,
      Q => S_ADC_CR(4),
      R => '0'
    );
\ADC_CR_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => ADC_CR(3),
      D => s00_axi_wdata(5),
      Q => S_ADC_CR(5),
      R => \ADC_CR[7]_i_1_n_0\
    );
\ADC_CR_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => ADC_CR(3),
      D => s00_axi_wdata(6),
      Q => S_ADC_CR(6),
      R => \ADC_CR[7]_i_1_n_0\
    );
\ADC_CR_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => ADC_CR(3),
      D => s00_axi_wdata(7),
      Q => S_ADC_CR(7),
      R => \ADC_CR[7]_i_1_n_0\
    );
\ADC_CR_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => ADC_CR(15),
      D => s00_axi_wdata(8),
      Q => \ADC_CR_reg_n_0_[8]\,
      R => \ADC_CR[15]_i_1_n_0\
    );
\ADC_CR_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => ADC_CR(15),
      D => s00_axi_wdata(9),
      Q => \ADC_CR_reg_n_0_[9]\,
      R => \ADC_CR[15]_i_1_n_0\
    );
\ADC_MASTER_BUSY_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => '1',
      D => BUSY,
      Q => ADC_MASTER_BUSY(0),
      R => \^rstp\
    );
\ADC_MASTER_CHANNEL[15]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0000000000008000"
    )
        port map (
      I0 => \slv_reg_wren__0\,
      I1 => s00_axi_wstrb(1),
      I2 => p_0_in(0),
      I3 => p_0_in(1),
      I4 => p_0_in(2),
      I5 => p_0_in(3),
      O => \ADC_MASTER_CHANNEL[15]_i_1_n_0\
    );
\ADC_MASTER_CHANNEL[23]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0000000000008000"
    )
        port map (
      I0 => \slv_reg_wren__0\,
      I1 => s00_axi_wstrb(2),
      I2 => p_0_in(0),
      I3 => p_0_in(1),
      I4 => p_0_in(2),
      I5 => p_0_in(3),
      O => \ADC_MASTER_CHANNEL[23]_i_1_n_0\
    );
\ADC_MASTER_CHANNEL[31]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0000000000008000"
    )
        port map (
      I0 => \slv_reg_wren__0\,
      I1 => s00_axi_wstrb(3),
      I2 => p_0_in(0),
      I3 => p_0_in(1),
      I4 => p_0_in(2),
      I5 => p_0_in(3),
      O => \ADC_MASTER_CHANNEL[31]_i_1_n_0\
    );
\ADC_MASTER_CHANNEL[7]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0000000000008000"
    )
        port map (
      I0 => \slv_reg_wren__0\,
      I1 => s00_axi_wstrb(0),
      I2 => p_0_in(0),
      I3 => p_0_in(1),
      I4 => p_0_in(2),
      I5 => p_0_in(3),
      O => \ADC_MASTER_CHANNEL[7]_i_1_n_0\
    );
\ADC_MASTER_CHANNEL_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \ADC_MASTER_CHANNEL[7]_i_1_n_0\,
      D => s00_axi_wdata(0),
      Q => S_ADC_MASTER_CHANNEL,
      R => \^rstp\
    );
\ADC_MASTER_CHANNEL_reg[10]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \ADC_MASTER_CHANNEL[15]_i_1_n_0\,
      D => s00_axi_wdata(10),
      Q => \ADC_MASTER_CHANNEL_reg_n_0_[10]\,
      R => \^rstp\
    );
\ADC_MASTER_CHANNEL_reg[11]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \ADC_MASTER_CHANNEL[15]_i_1_n_0\,
      D => s00_axi_wdata(11),
      Q => \ADC_MASTER_CHANNEL_reg_n_0_[11]\,
      R => \^rstp\
    );
\ADC_MASTER_CHANNEL_reg[12]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \ADC_MASTER_CHANNEL[15]_i_1_n_0\,
      D => s00_axi_wdata(12),
      Q => \ADC_MASTER_CHANNEL_reg_n_0_[12]\,
      R => \^rstp\
    );
\ADC_MASTER_CHANNEL_reg[13]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \ADC_MASTER_CHANNEL[15]_i_1_n_0\,
      D => s00_axi_wdata(13),
      Q => \ADC_MASTER_CHANNEL_reg_n_0_[13]\,
      R => \^rstp\
    );
\ADC_MASTER_CHANNEL_reg[14]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \ADC_MASTER_CHANNEL[15]_i_1_n_0\,
      D => s00_axi_wdata(14),
      Q => \ADC_MASTER_CHANNEL_reg_n_0_[14]\,
      R => \^rstp\
    );
\ADC_MASTER_CHANNEL_reg[15]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \ADC_MASTER_CHANNEL[15]_i_1_n_0\,
      D => s00_axi_wdata(15),
      Q => \ADC_MASTER_CHANNEL_reg_n_0_[15]\,
      R => \^rstp\
    );
\ADC_MASTER_CHANNEL_reg[16]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \ADC_MASTER_CHANNEL[23]_i_1_n_0\,
      D => s00_axi_wdata(16),
      Q => \ADC_MASTER_CHANNEL_reg_n_0_[16]\,
      R => \^rstp\
    );
\ADC_MASTER_CHANNEL_reg[17]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \ADC_MASTER_CHANNEL[23]_i_1_n_0\,
      D => s00_axi_wdata(17),
      Q => \ADC_MASTER_CHANNEL_reg_n_0_[17]\,
      R => \^rstp\
    );
\ADC_MASTER_CHANNEL_reg[18]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \ADC_MASTER_CHANNEL[23]_i_1_n_0\,
      D => s00_axi_wdata(18),
      Q => \ADC_MASTER_CHANNEL_reg_n_0_[18]\,
      R => \^rstp\
    );
\ADC_MASTER_CHANNEL_reg[19]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \ADC_MASTER_CHANNEL[23]_i_1_n_0\,
      D => s00_axi_wdata(19),
      Q => \ADC_MASTER_CHANNEL_reg_n_0_[19]\,
      R => \^rstp\
    );
\ADC_MASTER_CHANNEL_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \ADC_MASTER_CHANNEL[7]_i_1_n_0\,
      D => s00_axi_wdata(1),
      Q => \ADC_MASTER_CHANNEL_reg_n_0_[1]\,
      R => \^rstp\
    );
\ADC_MASTER_CHANNEL_reg[20]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \ADC_MASTER_CHANNEL[23]_i_1_n_0\,
      D => s00_axi_wdata(20),
      Q => \ADC_MASTER_CHANNEL_reg_n_0_[20]\,
      R => \^rstp\
    );
\ADC_MASTER_CHANNEL_reg[21]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \ADC_MASTER_CHANNEL[23]_i_1_n_0\,
      D => s00_axi_wdata(21),
      Q => \ADC_MASTER_CHANNEL_reg_n_0_[21]\,
      R => \^rstp\
    );
\ADC_MASTER_CHANNEL_reg[22]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \ADC_MASTER_CHANNEL[23]_i_1_n_0\,
      D => s00_axi_wdata(22),
      Q => \ADC_MASTER_CHANNEL_reg_n_0_[22]\,
      R => \^rstp\
    );
\ADC_MASTER_CHANNEL_reg[23]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \ADC_MASTER_CHANNEL[23]_i_1_n_0\,
      D => s00_axi_wdata(23),
      Q => \ADC_MASTER_CHANNEL_reg_n_0_[23]\,
      R => \^rstp\
    );
\ADC_MASTER_CHANNEL_reg[24]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \ADC_MASTER_CHANNEL[31]_i_1_n_0\,
      D => s00_axi_wdata(24),
      Q => \ADC_MASTER_CHANNEL_reg_n_0_[24]\,
      R => \^rstp\
    );
\ADC_MASTER_CHANNEL_reg[25]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \ADC_MASTER_CHANNEL[31]_i_1_n_0\,
      D => s00_axi_wdata(25),
      Q => \ADC_MASTER_CHANNEL_reg_n_0_[25]\,
      R => \^rstp\
    );
\ADC_MASTER_CHANNEL_reg[26]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \ADC_MASTER_CHANNEL[31]_i_1_n_0\,
      D => s00_axi_wdata(26),
      Q => \ADC_MASTER_CHANNEL_reg_n_0_[26]\,
      R => \^rstp\
    );
\ADC_MASTER_CHANNEL_reg[27]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \ADC_MASTER_CHANNEL[31]_i_1_n_0\,
      D => s00_axi_wdata(27),
      Q => \ADC_MASTER_CHANNEL_reg_n_0_[27]\,
      R => \^rstp\
    );
\ADC_MASTER_CHANNEL_reg[28]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \ADC_MASTER_CHANNEL[31]_i_1_n_0\,
      D => s00_axi_wdata(28),
      Q => \ADC_MASTER_CHANNEL_reg_n_0_[28]\,
      R => \^rstp\
    );
\ADC_MASTER_CHANNEL_reg[29]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \ADC_MASTER_CHANNEL[31]_i_1_n_0\,
      D => s00_axi_wdata(29),
      Q => \ADC_MASTER_CHANNEL_reg_n_0_[29]\,
      R => \^rstp\
    );
\ADC_MASTER_CHANNEL_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \ADC_MASTER_CHANNEL[7]_i_1_n_0\,
      D => s00_axi_wdata(2),
      Q => \ADC_MASTER_CHANNEL_reg_n_0_[2]\,
      R => \^rstp\
    );
\ADC_MASTER_CHANNEL_reg[30]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \ADC_MASTER_CHANNEL[31]_i_1_n_0\,
      D => s00_axi_wdata(30),
      Q => \ADC_MASTER_CHANNEL_reg_n_0_[30]\,
      R => \^rstp\
    );
\ADC_MASTER_CHANNEL_reg[31]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \ADC_MASTER_CHANNEL[31]_i_1_n_0\,
      D => s00_axi_wdata(31),
      Q => \ADC_MASTER_CHANNEL_reg_n_0_[31]\,
      R => \^rstp\
    );
\ADC_MASTER_CHANNEL_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \ADC_MASTER_CHANNEL[7]_i_1_n_0\,
      D => s00_axi_wdata(3),
      Q => \ADC_MASTER_CHANNEL_reg_n_0_[3]\,
      R => \^rstp\
    );
\ADC_MASTER_CHANNEL_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \ADC_MASTER_CHANNEL[7]_i_1_n_0\,
      D => s00_axi_wdata(4),
      Q => \ADC_MASTER_CHANNEL_reg_n_0_[4]\,
      R => \^rstp\
    );
\ADC_MASTER_CHANNEL_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \ADC_MASTER_CHANNEL[7]_i_1_n_0\,
      D => s00_axi_wdata(5),
      Q => \ADC_MASTER_CHANNEL_reg_n_0_[5]\,
      R => \^rstp\
    );
\ADC_MASTER_CHANNEL_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \ADC_MASTER_CHANNEL[7]_i_1_n_0\,
      D => s00_axi_wdata(6),
      Q => \ADC_MASTER_CHANNEL_reg_n_0_[6]\,
      R => \^rstp\
    );
\ADC_MASTER_CHANNEL_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \ADC_MASTER_CHANNEL[7]_i_1_n_0\,
      D => s00_axi_wdata(7),
      Q => \ADC_MASTER_CHANNEL_reg_n_0_[7]\,
      R => \^rstp\
    );
\ADC_MASTER_CHANNEL_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \ADC_MASTER_CHANNEL[15]_i_1_n_0\,
      D => s00_axi_wdata(8),
      Q => \ADC_MASTER_CHANNEL_reg_n_0_[8]\,
      R => \^rstp\
    );
\ADC_MASTER_CHANNEL_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \ADC_MASTER_CHANNEL[15]_i_1_n_0\,
      D => s00_axi_wdata(9),
      Q => \ADC_MASTER_CHANNEL_reg_n_0_[9]\,
      R => \^rstp\
    );
\ADC_MASTER_FINISH_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => '1',
      D => RAW_VALID(0),
      Q => ADC_MASTER_FINISH(0),
      R => \^rstp\
    );
\ADC_MASTER_SI_FINISH_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => '1',
      D => SI_VALID(0),
      Q => ADC_MASTER_SI_FINISH(0),
      R => \^rstp\
    );
\ADC_SPI_CFGR[15]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0000000800000000"
    )
        port map (
      I0 => \slv_reg_wren__0\,
      I1 => s00_axi_wstrb(1),
      I2 => p_0_in(3),
      I3 => p_0_in(0),
      I4 => p_0_in(2),
      I5 => p_0_in(1),
      O => p_1_in(15)
    );
\ADC_SPI_CFGR[23]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0000000800000000"
    )
        port map (
      I0 => \slv_reg_wren__0\,
      I1 => s00_axi_wstrb(2),
      I2 => p_0_in(3),
      I3 => p_0_in(0),
      I4 => p_0_in(2),
      I5 => p_0_in(1),
      O => p_1_in(23)
    );
\ADC_SPI_CFGR[31]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0000000800000000"
    )
        port map (
      I0 => \slv_reg_wren__0\,
      I1 => s00_axi_wstrb(3),
      I2 => p_0_in(3),
      I3 => p_0_in(0),
      I4 => p_0_in(2),
      I5 => p_0_in(1),
      O => p_1_in(31)
    );
\ADC_SPI_CFGR[7]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0000000800000000"
    )
        port map (
      I0 => \slv_reg_wren__0\,
      I1 => s00_axi_wstrb(0),
      I2 => p_0_in(3),
      I3 => p_0_in(0),
      I4 => p_0_in(2),
      I5 => p_0_in(1),
      O => p_1_in(7)
    );
\ADC_SPI_CFGR_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(7),
      D => s00_axi_wdata(0),
      Q => \^q\(0),
      R => \^rstp\
    );
\ADC_SPI_CFGR_reg[10]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(15),
      D => s00_axi_wdata(10),
      Q => \^q\(10),
      R => \^rstp\
    );
\ADC_SPI_CFGR_reg[11]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(15),
      D => s00_axi_wdata(11),
      Q => \^q\(11),
      R => \^rstp\
    );
\ADC_SPI_CFGR_reg[12]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(15),
      D => s00_axi_wdata(12),
      Q => \^q\(12),
      R => \^rstp\
    );
\ADC_SPI_CFGR_reg[13]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(15),
      D => s00_axi_wdata(13),
      Q => \^q\(13),
      R => \^rstp\
    );
\ADC_SPI_CFGR_reg[14]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(15),
      D => s00_axi_wdata(14),
      Q => \^q\(14),
      R => \^rstp\
    );
\ADC_SPI_CFGR_reg[15]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(15),
      D => s00_axi_wdata(15),
      Q => \^q\(15),
      R => \^rstp\
    );
\ADC_SPI_CFGR_reg[16]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(23),
      D => s00_axi_wdata(16),
      Q => \^q\(16),
      R => \^rstp\
    );
\ADC_SPI_CFGR_reg[17]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(23),
      D => s00_axi_wdata(17),
      Q => \^q\(17),
      R => \^rstp\
    );
\ADC_SPI_CFGR_reg[18]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(23),
      D => s00_axi_wdata(18),
      Q => \^q\(18),
      R => \^rstp\
    );
\ADC_SPI_CFGR_reg[19]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(23),
      D => s00_axi_wdata(19),
      Q => \^q\(19),
      R => \^rstp\
    );
\ADC_SPI_CFGR_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(7),
      D => s00_axi_wdata(1),
      Q => \^q\(1),
      R => \^rstp\
    );
\ADC_SPI_CFGR_reg[20]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(23),
      D => s00_axi_wdata(20),
      Q => \^q\(20),
      R => \^rstp\
    );
\ADC_SPI_CFGR_reg[21]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(23),
      D => s00_axi_wdata(21),
      Q => \^q\(21),
      R => \^rstp\
    );
\ADC_SPI_CFGR_reg[22]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(23),
      D => s00_axi_wdata(22),
      Q => \^q\(22),
      R => \^rstp\
    );
\ADC_SPI_CFGR_reg[23]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(23),
      D => s00_axi_wdata(23),
      Q => \^q\(23),
      R => \^rstp\
    );
\ADC_SPI_CFGR_reg[24]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(31),
      D => s00_axi_wdata(24),
      Q => \^q\(24),
      R => \^rstp\
    );
\ADC_SPI_CFGR_reg[25]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(31),
      D => s00_axi_wdata(25),
      Q => \^q\(25),
      R => \^rstp\
    );
\ADC_SPI_CFGR_reg[26]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(31),
      D => s00_axi_wdata(26),
      Q => \^q\(26),
      R => \^rstp\
    );
\ADC_SPI_CFGR_reg[27]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(31),
      D => s00_axi_wdata(27),
      Q => \^q\(27),
      R => \^rstp\
    );
\ADC_SPI_CFGR_reg[28]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(31),
      D => s00_axi_wdata(28),
      Q => \^q\(28),
      R => \^rstp\
    );
\ADC_SPI_CFGR_reg[29]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(31),
      D => s00_axi_wdata(29),
      Q => \^q\(29),
      R => \^rstp\
    );
\ADC_SPI_CFGR_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(7),
      D => s00_axi_wdata(2),
      Q => \^q\(2),
      R => \^rstp\
    );
\ADC_SPI_CFGR_reg[30]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(31),
      D => s00_axi_wdata(30),
      Q => \^q\(30),
      R => \^rstp\
    );
\ADC_SPI_CFGR_reg[31]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(31),
      D => s00_axi_wdata(31),
      Q => \^q\(31),
      R => \^rstp\
    );
\ADC_SPI_CFGR_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(7),
      D => s00_axi_wdata(3),
      Q => \^q\(3),
      R => \^rstp\
    );
\ADC_SPI_CFGR_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(7),
      D => s00_axi_wdata(4),
      Q => \^q\(4),
      R => \^rstp\
    );
\ADC_SPI_CFGR_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(7),
      D => s00_axi_wdata(5),
      Q => \^q\(5),
      R => \^rstp\
    );
\ADC_SPI_CFGR_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(7),
      D => s00_axi_wdata(6),
      Q => \^q\(6),
      R => \^rstp\
    );
\ADC_SPI_CFGR_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(7),
      D => s00_axi_wdata(7),
      Q => \^q\(7),
      R => \^rstp\
    );
\ADC_SPI_CFGR_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(15),
      D => s00_axi_wdata(8),
      Q => \^q\(8),
      R => \^rstp\
    );
\ADC_SPI_CFGR_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(15),
      D => s00_axi_wdata(9),
      Q => \^q\(9),
      R => \^rstp\
    );
\ADC_SPI_CR[15]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"8A"
    )
        port map (
      I0 => ADC_SPI_CR(15),
      I1 => \^adc_cr_reg[3]_0\(0),
      I2 => s00_axi_aresetn,
      O => \ADC_SPI_CR[15]_i_1_n_0\
    );
\ADC_SPI_CR[15]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"20000000FFFFFFFF"
    )
        port map (
      I0 => \ADC_SPI_CR[31]_i_3_n_0\,
      I1 => p_0_in(1),
      I2 => p_0_in(0),
      I3 => s00_axi_wstrb(1),
      I4 => \slv_reg_wren__0\,
      I5 => \^s_axi_aresetn\,
      O => ADC_SPI_CR(15)
    );
\ADC_SPI_CR[1]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"40"
    )
        port map (
      I0 => \^adc_cr_reg[3]_0\(0),
      I1 => s00_axi_aresetn,
      I2 => \ADC_SPI_CR_reg[3]_0\(0),
      O => ADC_SPI_CR0_in(1)
    );
\ADC_SPI_CR[23]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"8A"
    )
        port map (
      I0 => ADC_SPI_CR(23),
      I1 => \^adc_cr_reg[3]_0\(0),
      I2 => s00_axi_aresetn,
      O => \ADC_SPI_CR[23]_i_1_n_0\
    );
\ADC_SPI_CR[23]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"20000000FFFFFFFF"
    )
        port map (
      I0 => \ADC_SPI_CR[31]_i_3_n_0\,
      I1 => p_0_in(1),
      I2 => p_0_in(0),
      I3 => s00_axi_wstrb(2),
      I4 => \slv_reg_wren__0\,
      I5 => \^s_axi_aresetn\,
      O => ADC_SPI_CR(23)
    );
\ADC_SPI_CR[31]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"8A"
    )
        port map (
      I0 => ADC_SPI_CR(31),
      I1 => \^adc_cr_reg[3]_0\(0),
      I2 => s00_axi_aresetn,
      O => \ADC_SPI_CR[31]_i_1_n_0\
    );
\ADC_SPI_CR[31]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"20000000FFFFFFFF"
    )
        port map (
      I0 => \ADC_SPI_CR[31]_i_3_n_0\,
      I1 => p_0_in(1),
      I2 => p_0_in(0),
      I3 => s00_axi_wstrb(3),
      I4 => \slv_reg_wren__0\,
      I5 => \^s_axi_aresetn\,
      O => ADC_SPI_CR(31)
    );
\ADC_SPI_CR[31]_i_3\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => p_0_in(2),
      I1 => p_0_in(3),
      O => \ADC_SPI_CR[31]_i_3_n_0\
    );
\ADC_SPI_CR[31]_i_4\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"8000"
    )
        port map (
      I0 => \^axi_awready_reg_0\,
      I1 => \^axi_wready_reg_0\,
      I2 => s00_axi_wvalid,
      I3 => s00_axi_awvalid,
      O => \slv_reg_wren__0\
    );
\ADC_SPI_CR[31]_i_5\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"2"
    )
        port map (
      I0 => s00_axi_aresetn,
      I1 => \^adc_cr_reg[3]_0\(0),
      O => \^s_axi_aresetn\
    );
\ADC_SPI_CR[3]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"40"
    )
        port map (
      I0 => \^adc_cr_reg[3]_0\(0),
      I1 => s00_axi_aresetn,
      I2 => \ADC_SPI_CR_reg[3]_0\(1),
      O => ADC_SPI_CR0_in(3)
    );
\ADC_SPI_CR[5]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"40"
    )
        port map (
      I0 => \^adc_cr_reg[3]_0\(0),
      I1 => s00_axi_aresetn,
      I2 => \ADC_SPI_CR_reg[5]_0\,
      O => ADC_SPI_CR0_in(5)
    );
\ADC_SPI_CR[6]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"EFFFEF00"
    )
        port map (
      I0 => s00_axi_wdata(6),
      I1 => \^adc_cr_reg[3]_0\(0),
      I2 => s00_axi_aresetn,
      I3 => ADC_SPI_CR(7),
      I4 => \^cpol\,
      O => \ADC_SPI_CR[6]_i_1_n_0\
    );
\ADC_SPI_CR[7]_i_1\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => \^s_axi_aresetn\,
      O => \ADC_SPI_CR[7]_i_1_n_0\
    );
\ADC_SPI_CR[7]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"20000000FFFFFFFF"
    )
        port map (
      I0 => \ADC_SPI_CR[31]_i_3_n_0\,
      I1 => p_0_in(1),
      I2 => p_0_in(0),
      I3 => s00_axi_wstrb(0),
      I4 => \slv_reg_wren__0\,
      I5 => \^s_axi_aresetn\,
      O => ADC_SPI_CR(7)
    );
\ADC_SPI_CR_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => ADC_SPI_CR(7),
      D => s00_axi_wdata(0),
      Q => \^d\(0),
      R => \ADC_SPI_CR[7]_i_1_n_0\
    );
\ADC_SPI_CR_reg[10]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => ADC_SPI_CR(15),
      D => s00_axi_wdata(10),
      Q => \ADC_SPI_CR_reg_n_0_[10]\,
      R => \ADC_SPI_CR[15]_i_1_n_0\
    );
\ADC_SPI_CR_reg[11]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => ADC_SPI_CR(15),
      D => s00_axi_wdata(11),
      Q => \ADC_SPI_CR_reg_n_0_[11]\,
      R => \ADC_SPI_CR[15]_i_1_n_0\
    );
\ADC_SPI_CR_reg[12]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => ADC_SPI_CR(15),
      D => s00_axi_wdata(12),
      Q => \ADC_SPI_CR_reg_n_0_[12]\,
      R => \ADC_SPI_CR[15]_i_1_n_0\
    );
\ADC_SPI_CR_reg[13]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => ADC_SPI_CR(15),
      D => s00_axi_wdata(13),
      Q => \ADC_SPI_CR_reg_n_0_[13]\,
      R => \ADC_SPI_CR[15]_i_1_n_0\
    );
\ADC_SPI_CR_reg[14]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => ADC_SPI_CR(15),
      D => s00_axi_wdata(14),
      Q => \ADC_SPI_CR_reg_n_0_[14]\,
      R => \ADC_SPI_CR[15]_i_1_n_0\
    );
\ADC_SPI_CR_reg[15]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => ADC_SPI_CR(15),
      D => s00_axi_wdata(15),
      Q => \ADC_SPI_CR_reg_n_0_[15]\,
      R => \ADC_SPI_CR[15]_i_1_n_0\
    );
\ADC_SPI_CR_reg[16]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => ADC_SPI_CR(23),
      D => s00_axi_wdata(16),
      Q => \ADC_SPI_CR_reg_n_0_[16]\,
      R => \ADC_SPI_CR[23]_i_1_n_0\
    );
\ADC_SPI_CR_reg[17]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => ADC_SPI_CR(23),
      D => s00_axi_wdata(17),
      Q => \ADC_SPI_CR_reg_n_0_[17]\,
      R => \ADC_SPI_CR[23]_i_1_n_0\
    );
\ADC_SPI_CR_reg[18]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => ADC_SPI_CR(23),
      D => s00_axi_wdata(18),
      Q => \ADC_SPI_CR_reg_n_0_[18]\,
      R => \ADC_SPI_CR[23]_i_1_n_0\
    );
\ADC_SPI_CR_reg[19]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => ADC_SPI_CR(23),
      D => s00_axi_wdata(19),
      Q => \ADC_SPI_CR_reg_n_0_[19]\,
      R => \ADC_SPI_CR[23]_i_1_n_0\
    );
\ADC_SPI_CR_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => '1',
      D => ADC_SPI_CR0_in(1),
      Q => \ADC_SPI_CR_reg_n_0_[1]\,
      R => '0'
    );
\ADC_SPI_CR_reg[20]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => ADC_SPI_CR(23),
      D => s00_axi_wdata(20),
      Q => \ADC_SPI_CR_reg_n_0_[20]\,
      R => \ADC_SPI_CR[23]_i_1_n_0\
    );
\ADC_SPI_CR_reg[21]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => ADC_SPI_CR(23),
      D => s00_axi_wdata(21),
      Q => \ADC_SPI_CR_reg_n_0_[21]\,
      R => \ADC_SPI_CR[23]_i_1_n_0\
    );
\ADC_SPI_CR_reg[22]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => ADC_SPI_CR(23),
      D => s00_axi_wdata(22),
      Q => \ADC_SPI_CR_reg_n_0_[22]\,
      R => \ADC_SPI_CR[23]_i_1_n_0\
    );
\ADC_SPI_CR_reg[23]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => ADC_SPI_CR(23),
      D => s00_axi_wdata(23),
      Q => \ADC_SPI_CR_reg_n_0_[23]\,
      R => \ADC_SPI_CR[23]_i_1_n_0\
    );
\ADC_SPI_CR_reg[24]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => ADC_SPI_CR(31),
      D => s00_axi_wdata(24),
      Q => \ADC_SPI_CR_reg_n_0_[24]\,
      R => \ADC_SPI_CR[31]_i_1_n_0\
    );
\ADC_SPI_CR_reg[25]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => ADC_SPI_CR(31),
      D => s00_axi_wdata(25),
      Q => \ADC_SPI_CR_reg_n_0_[25]\,
      R => \ADC_SPI_CR[31]_i_1_n_0\
    );
\ADC_SPI_CR_reg[26]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => ADC_SPI_CR(31),
      D => s00_axi_wdata(26),
      Q => \ADC_SPI_CR_reg_n_0_[26]\,
      R => \ADC_SPI_CR[31]_i_1_n_0\
    );
\ADC_SPI_CR_reg[27]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => ADC_SPI_CR(31),
      D => s00_axi_wdata(27),
      Q => \ADC_SPI_CR_reg_n_0_[27]\,
      R => \ADC_SPI_CR[31]_i_1_n_0\
    );
\ADC_SPI_CR_reg[28]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => ADC_SPI_CR(31),
      D => s00_axi_wdata(28),
      Q => \ADC_SPI_CR_reg_n_0_[28]\,
      R => \ADC_SPI_CR[31]_i_1_n_0\
    );
\ADC_SPI_CR_reg[29]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => ADC_SPI_CR(31),
      D => s00_axi_wdata(29),
      Q => \ADC_SPI_CR_reg_n_0_[29]\,
      R => \ADC_SPI_CR[31]_i_1_n_0\
    );
\ADC_SPI_CR_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => ADC_SPI_CR(7),
      D => s00_axi_wdata(2),
      Q => \^d\(1),
      R => \ADC_SPI_CR[7]_i_1_n_0\
    );
\ADC_SPI_CR_reg[30]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => ADC_SPI_CR(31),
      D => s00_axi_wdata(30),
      Q => \ADC_SPI_CR_reg_n_0_[30]\,
      R => \ADC_SPI_CR[31]_i_1_n_0\
    );
\ADC_SPI_CR_reg[31]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => ADC_SPI_CR(31),
      D => s00_axi_wdata(31),
      Q => \ADC_SPI_CR_reg_n_0_[31]\,
      R => \ADC_SPI_CR[31]_i_1_n_0\
    );
\ADC_SPI_CR_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => '1',
      D => ADC_SPI_CR0_in(3),
      Q => \ADC_SPI_CR_reg_n_0_[3]\,
      R => '0'
    );
\ADC_SPI_CR_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => ADC_SPI_CR(7),
      D => s00_axi_wdata(4),
      Q => p_0_in13_in,
      R => \ADC_SPI_CR[7]_i_1_n_0\
    );
\ADC_SPI_CR_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => '1',
      D => ADC_SPI_CR0_in(5),
      Q => \ADC_SPI_CR_reg_n_0_[5]\,
      R => '0'
    );
\ADC_SPI_CR_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => '1',
      D => \ADC_SPI_CR[6]_i_1_n_0\,
      Q => \^cpol\,
      R => '0'
    );
\ADC_SPI_CR_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => ADC_SPI_CR(7),
      D => s00_axi_wdata(7),
      Q => \^cpha\,
      R => \ADC_SPI_CR[7]_i_1_n_0\
    );
\ADC_SPI_CR_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => ADC_SPI_CR(15),
      D => s00_axi_wdata(8),
      Q => \ADC_SPI_CR_reg_n_0_[8]\,
      R => \ADC_SPI_CR[15]_i_1_n_0\
    );
\ADC_SPI_CR_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => ADC_SPI_CR(15),
      D => s00_axi_wdata(9),
      Q => \ADC_SPI_CR_reg_n_0_[9]\,
      R => \ADC_SPI_CR[15]_i_1_n_0\
    );
\S_ADC_CR_IN[2]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFFFFDF00000000"
    )
        port map (
      I0 => S_ADC_CR(2),
      I1 => IS_BUSY,
      I2 => S_ADC_CR(1),
      I3 => \^nxtstate\(0),
      I4 => \^nxtstate\(1),
      I5 => P_ADC_CR_IN(0),
      O => \ADC_CR_reg[2]_0\
    );
\S_ADC_CR_IN[2]_i_2\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"8"
    )
        port map (
      I0 => S_ADC_MASTER_CHANNEL,
      I1 => BUSY,
      O => IS_BUSY
    );
\S_ADC_CR_IN[4]_i_1\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => S_ADC_CR(4),
      O => S_SET_CONVERSION
    );
\S_ADC_SPI_CR_IN[3]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"0400"
    )
        port map (
      I0 => \^adc_cr_reg[3]_0\(0),
      I1 => s00_axi_aresetn,
      I2 => \^nxtstate\(0),
      I3 => \^nxtstate\(1),
      O => \ADC_CR_reg[3]_2\(0)
    );
\S_CONVERSION[107]_i_1\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"8"
    )
        port map (
      I0 => SET_CONVERSION,
      I1 => S_ADC_CHANNEL(5),
      O => \S_SET_CONVERSION_reg[0]\(5)
    );
\S_CONVERSION[125]_i_1\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"8"
    )
        port map (
      I0 => SET_CONVERSION,
      I1 => S_ADC_CHANNEL(6),
      O => \S_SET_CONVERSION_reg[0]\(6)
    );
\S_CONVERSION[143]_i_1\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"8"
    )
        port map (
      I0 => SET_CONVERSION,
      I1 => S_ADC_CHANNEL(7),
      O => \S_SET_CONVERSION_reg[0]\(7)
    );
\S_CONVERSION[17]_i_1\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"8"
    )
        port map (
      I0 => SET_CONVERSION,
      I1 => S_ADC_CHANNEL(0),
      O => \S_SET_CONVERSION_reg[0]\(0)
    );
\S_CONVERSION[35]_i_1\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"8"
    )
        port map (
      I0 => SET_CONVERSION,
      I1 => S_ADC_CHANNEL(1),
      O => \S_SET_CONVERSION_reg[0]\(1)
    );
\S_CONVERSION[53]_i_1\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"8"
    )
        port map (
      I0 => SET_CONVERSION,
      I1 => S_ADC_CHANNEL(2),
      O => \S_SET_CONVERSION_reg[0]\(2)
    );
\S_CONVERSION[71]_i_1\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"8"
    )
        port map (
      I0 => SET_CONVERSION,
      I1 => S_ADC_CHANNEL(3),
      O => \S_SET_CONVERSION_reg[0]\(3)
    );
\S_CONVERSION[89]_i_1\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"8"
    )
        port map (
      I0 => SET_CONVERSION,
      I1 => S_ADC_CHANNEL(4),
      O => \S_SET_CONVERSION_reg[0]\(4)
    );
\S_ENABLE[0]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFCC00AF00CC00A0"
    )
        port map (
      I0 => \S_ENABLE[0]_i_2_n_0\,
      I1 => \S_ENABLE0__4\,
      I2 => \S_ENABLE[0]_i_4_n_0\,
      I3 => \^nxtstate\(1),
      I4 => \^nxtstate\(0),
      I5 => ENABLE,
      O => \S_ENABLE_reg[0]\
    );
\S_ENABLE[0]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"808000008F800000"
    )
        port map (
      I0 => S_ADC_CR(2),
      I1 => S_ADC_MASTER_CHANNEL,
      I2 => S_ADC_CR(1),
      I3 => TRIGGER_CNV(0),
      I4 => S_ADC_AVAILABLE,
      I5 => S_TRIGGER_CNV_PIPE,
      O => \S_ENABLE[0]_i_2_n_0\
    );
\S_ENABLE[0]_i_3\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"8"
    )
        port map (
      I0 => S_ADC_MASTER_CHANNEL,
      I1 => S_ADC_AVAILABLE,
      O => \S_ENABLE0__4\
    );
\S_ENABLE[0]_i_4\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"7FFF"
    )
        port map (
      I0 => S_ADC_MASTER_CHANNEL,
      I1 => BUSY,
      I2 => S_ADC_CR(2),
      I3 => S_ADC_CR(1),
      O => \S_ENABLE[0]_i_4_n_0\
    );
\S_OFFSET[111]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"08"
    )
        port map (
      I0 => S_ADC_CHANNEL(6),
      I1 => SET_OFFSET,
      I2 => SET_CONVERSION,
      O => \ADC_CHANNEL_reg[7]_0\(6)
    );
\S_OFFSET[127]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"08"
    )
        port map (
      I0 => S_ADC_CHANNEL(7),
      I1 => SET_OFFSET,
      I2 => SET_CONVERSION,
      O => \ADC_CHANNEL_reg[7]_0\(7)
    );
\S_OFFSET[15]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"08"
    )
        port map (
      I0 => S_ADC_CHANNEL(0),
      I1 => SET_OFFSET,
      I2 => SET_CONVERSION,
      O => \ADC_CHANNEL_reg[7]_0\(0)
    );
\S_OFFSET[31]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"08"
    )
        port map (
      I0 => S_ADC_CHANNEL(1),
      I1 => SET_OFFSET,
      I2 => SET_CONVERSION,
      O => \ADC_CHANNEL_reg[7]_0\(1)
    );
\S_OFFSET[47]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"08"
    )
        port map (
      I0 => S_ADC_CHANNEL(2),
      I1 => SET_OFFSET,
      I2 => SET_CONVERSION,
      O => \ADC_CHANNEL_reg[7]_0\(2)
    );
\S_OFFSET[63]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"08"
    )
        port map (
      I0 => S_ADC_CHANNEL(3),
      I1 => SET_OFFSET,
      I2 => SET_CONVERSION,
      O => \ADC_CHANNEL_reg[7]_0\(3)
    );
\S_OFFSET[79]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"08"
    )
        port map (
      I0 => S_ADC_CHANNEL(4),
      I1 => SET_OFFSET,
      I2 => SET_CONVERSION,
      O => \ADC_CHANNEL_reg[7]_0\(4)
    );
\S_OFFSET[95]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"08"
    )
        port map (
      I0 => S_ADC_CHANNEL(5),
      I1 => SET_OFFSET,
      I2 => SET_CONVERSION,
      O => \ADC_CHANNEL_reg[7]_0\(5)
    );
\S_RX_OUT_BUFFER[127]_i_1\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"B"
    )
        port map (
      I0 => \^adc_cr_reg[3]_0\(0),
      I1 => s00_axi_aresetn,
      O => \^rstp\
    );
\S_SAMPLE_TIME[30]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0000000001000000"
    )
        port map (
      I0 => SET_CONVERSION,
      I1 => SET_OFFSET,
      I2 => \^adc_cr_reg[3]_0\(0),
      I3 => s00_axi_aresetn,
      I4 => SET_SAMPLE_TIME,
      I5 => SET_SAMPLES,
      O => E(0)
    );
\S_SCLK_IN[0]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"00004000"
    )
        port map (
      I0 => \^adc_cr_reg[3]_0\(0),
      I1 => s00_axi_aresetn,
      I2 => \^nxtstate\(1),
      I3 => S_ADC_MASTER_CHANNEL,
      I4 => \^nxtstate\(0),
      O => S_SCLK_IN
    );
\S_SET_CONVERSION[0]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"BF"
    )
        port map (
      I0 => \^adc_cr_reg[3]_0\(0),
      I1 => s00_axi_aresetn,
      I2 => S_ADC_CR(4),
      O => \ADC_CR_reg[3]_1\
    );
\S_SET_CONVERSION[0]_i_2\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"0008"
    )
        port map (
      I0 => S_ADC_MASTER_CHANNEL,
      I1 => S_ADC_CR(5),
      I2 => S_ADC_CR(6),
      I3 => S_ADC_CR(7),
      O => \ADC_MASTER_CHANNEL_reg[0]_1\
    );
\S_SET_OFFSET[0]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"0010"
    )
        port map (
      I0 => S_ADC_CR(6),
      I1 => S_ADC_CR(5),
      I2 => S_ADC_MASTER_CHANNEL,
      I3 => S_ADC_CR(7),
      O => \ADC_CR_reg[6]_0\
    );
\S_SET_SAMPLES[0]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"AAAAC0AA"
    )
        port map (
      I0 => SET_SAMPLES,
      I1 => \S_SET_SAMPLES[0]_i_2_n_0\,
      I2 => S_ADC_CR(4),
      I3 => s00_axi_aresetn,
      I4 => \^adc_cr_reg[3]_0\(0),
      O => \S_SET_SAMPLES_reg[0]\
    );
\S_SET_SAMPLES[0]_i_2\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"0008"
    )
        port map (
      I0 => S_ADC_CR(6),
      I1 => S_ADC_MASTER_CHANNEL,
      I2 => S_ADC_CR(5),
      I3 => S_ADC_CR(7),
      O => \S_SET_SAMPLES[0]_i_2_n_0\
    );
\S_SET_SAMPLE_TIME[0]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"2F20"
    )
        port map (
      I0 => S_ADC_MASTER_CHANNEL,
      I1 => S_ADC_CR(7),
      I2 => S_SET_SAMPLE_TIME8_out,
      I3 => SET_SAMPLE_TIME,
      O => \ADC_MASTER_CHANNEL_reg[0]_0\
    );
\S_SET_SAMPLE_TIME[0]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"4440404000000000"
    )
        port map (
      I0 => \^adc_cr_reg[3]_0\(0),
      I1 => s00_axi_aresetn,
      I2 => S_ADC_CR(7),
      I3 => S_ADC_CR(6),
      I4 => S_ADC_CR(5),
      I5 => S_ADC_CR(4),
      O => S_SET_SAMPLE_TIME8_out
    );
\S_SPI_MANUAL[0]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"0000A020"
    )
        port map (
      I0 => S_ADC_MASTER_CHANNEL,
      I1 => BUSY,
      I2 => p_0_in13_in,
      I3 => \curstate_reg[0]\(1),
      I4 => \curstate_reg[0]\(0),
      O => S_SS_IN_N
    );
aw_en_i_1: unisim.vcomponents.LUT6
    generic map(
      INIT => X"DFFF8AAA8AAA8AAA"
    )
        port map (
      I0 => aw_en_reg_n_0,
      I1 => \^axi_awready_reg_0\,
      I2 => s00_axi_awvalid,
      I3 => s00_axi_wvalid,
      I4 => s00_axi_bready,
      I5 => \^s00_axi_bvalid\,
      O => aw_en_i_1_n_0
    );
aw_en_reg: unisim.vcomponents.FDSE
     port map (
      C => s00_axi_aclk,
      CE => '1',
      D => aw_en_i_1_n_0,
      Q => aw_en_reg_n_0,
      S => \^rstp\
    );
\axi_araddr_reg[2]\: unisim.vcomponents.FDSE
     port map (
      C => s00_axi_aclk,
      CE => axi_arready0,
      D => s00_axi_araddr(0),
      Q => sel0(0),
      S => \^rstp\
    );
\axi_araddr_reg[3]\: unisim.vcomponents.FDSE
     port map (
      C => s00_axi_aclk,
      CE => axi_arready0,
      D => s00_axi_araddr(1),
      Q => sel0(1),
      S => \^rstp\
    );
\axi_araddr_reg[4]\: unisim.vcomponents.FDSE
     port map (
      C => s00_axi_aclk,
      CE => axi_arready0,
      D => s00_axi_araddr(2),
      Q => sel0(2),
      S => \^rstp\
    );
\axi_araddr_reg[5]\: unisim.vcomponents.FDSE
     port map (
      C => s00_axi_aclk,
      CE => axi_arready0,
      D => s00_axi_araddr(3),
      Q => sel0(3),
      S => \^rstp\
    );
axi_arready_i_1: unisim.vcomponents.LUT2
    generic map(
      INIT => X"2"
    )
        port map (
      I0 => s00_axi_arvalid,
      I1 => \^axi_arready_reg_0\,
      O => axi_arready0
    );
axi_arready_reg: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => '1',
      D => axi_arready0,
      Q => \^axi_arready_reg_0\,
      R => \^rstp\
    );
\axi_awaddr_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => axi_awready0,
      D => s00_axi_awaddr(0),
      Q => p_0_in(0),
      R => \^rstp\
    );
\axi_awaddr_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => axi_awready0,
      D => s00_axi_awaddr(1),
      Q => p_0_in(1),
      R => \^rstp\
    );
\axi_awaddr_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => axi_awready0,
      D => s00_axi_awaddr(2),
      Q => p_0_in(2),
      R => \^rstp\
    );
\axi_awaddr_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => axi_awready0,
      D => s00_axi_awaddr(3),
      Q => p_0_in(3),
      R => \^rstp\
    );
axi_awready_i_1: unisim.vcomponents.LUT4
    generic map(
      INIT => X"0800"
    )
        port map (
      I0 => s00_axi_wvalid,
      I1 => s00_axi_awvalid,
      I2 => \^axi_awready_reg_0\,
      I3 => aw_en_reg_n_0,
      O => axi_awready0
    );
axi_awready_reg: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => '1',
      D => axi_awready0,
      Q => \^axi_awready_reg_0\,
      R => \^rstp\
    );
axi_bvalid_i_1: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0000FFFF80008000"
    )
        port map (
      I0 => s00_axi_wvalid,
      I1 => s00_axi_awvalid,
      I2 => \^axi_wready_reg_0\,
      I3 => \^axi_awready_reg_0\,
      I4 => s00_axi_bready,
      I5 => \^s00_axi_bvalid\,
      O => axi_bvalid_i_1_n_0
    );
axi_bvalid_reg: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => '1',
      D => axi_bvalid_i_1_n_0,
      Q => \^s00_axi_bvalid\,
      R => \^rstp\
    );
\axi_rdata[0]_i_4\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => S_ADC_MASTER_CHANNEL,
      I1 => \^q\(0),
      I2 => sel0(1),
      I3 => \^d\(0),
      I4 => sel0(0),
      I5 => S_ADC_CR(0),
      O => \axi_rdata[0]_i_4_n_0\
    );
\axi_rdata[0]_i_5\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => ADC_MASTER_BUSY(0),
      I1 => ADC_MASTER_SI_FINISH(0),
      I2 => sel0(1),
      I3 => ADC_MASTER_FINISH(0),
      I4 => sel0(0),
      I5 => S_ADC_CHANNEL(0),
      O => \axi_rdata[0]_i_5_n_0\
    );
\axi_rdata[0]_i_6\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => slv_reg11(0),
      I1 => slv_reg10(0),
      I2 => sel0(1),
      I3 => S_ADC_AVAILABLE,
      I4 => sel0(0),
      I5 => \^adc_conv_value_reg[30]_0\(0),
      O => \axi_rdata[0]_i_6_n_0\
    );
\axi_rdata[0]_i_7\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => slv_reg15(0),
      I1 => slv_reg14(0),
      I2 => sel0(1),
      I3 => slv_reg13(0),
      I4 => sel0(0),
      I5 => slv_reg12(0),
      O => \axi_rdata[0]_i_7_n_0\
    );
\axi_rdata[10]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => \axi_rdata[10]_i_2_n_0\,
      I1 => \axi_rdata[10]_i_3_n_0\,
      I2 => sel0(3),
      I3 => \axi_rdata[10]_i_4_n_0\,
      I4 => sel0(2),
      I5 => \axi_rdata[10]_i_5_n_0\,
      O => reg_data_out(10)
    );
\axi_rdata[10]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => slv_reg15(10),
      I1 => slv_reg14(10),
      I2 => sel0(1),
      I3 => slv_reg13(10),
      I4 => sel0(0),
      I5 => slv_reg12(10),
      O => \axi_rdata[10]_i_2_n_0\
    );
\axi_rdata[10]_i_3\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => slv_reg11(10),
      I1 => slv_reg10(10),
      I2 => sel0(1),
      I3 => \ADC_AVAILABLE_reg_n_0_[10]\,
      I4 => sel0(0),
      I5 => \^adc_conv_value_reg[30]_0\(10),
      O => \axi_rdata[10]_i_3_n_0\
    );
\axi_rdata[10]_i_4\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"04"
    )
        port map (
      I0 => sel0(0),
      I1 => S_ADC_CHANNEL(10),
      I2 => sel0(1),
      O => \axi_rdata[10]_i_4_n_0\
    );
\axi_rdata[10]_i_5\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => \ADC_MASTER_CHANNEL_reg_n_0_[10]\,
      I1 => \^q\(10),
      I2 => sel0(1),
      I3 => \ADC_SPI_CR_reg_n_0_[10]\,
      I4 => sel0(0),
      I5 => \ADC_CR_reg_n_0_[10]\,
      O => \axi_rdata[10]_i_5_n_0\
    );
\axi_rdata[11]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => \axi_rdata[11]_i_2_n_0\,
      I1 => \axi_rdata[11]_i_3_n_0\,
      I2 => sel0(3),
      I3 => \axi_rdata[11]_i_4_n_0\,
      I4 => sel0(2),
      I5 => \axi_rdata[11]_i_5_n_0\,
      O => reg_data_out(11)
    );
\axi_rdata[11]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => slv_reg15(11),
      I1 => slv_reg14(11),
      I2 => sel0(1),
      I3 => slv_reg13(11),
      I4 => sel0(0),
      I5 => slv_reg12(11),
      O => \axi_rdata[11]_i_2_n_0\
    );
\axi_rdata[11]_i_3\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => slv_reg11(11),
      I1 => slv_reg10(11),
      I2 => sel0(1),
      I3 => \ADC_AVAILABLE_reg_n_0_[11]\,
      I4 => sel0(0),
      I5 => \^adc_conv_value_reg[30]_0\(11),
      O => \axi_rdata[11]_i_3_n_0\
    );
\axi_rdata[11]_i_4\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"04"
    )
        port map (
      I0 => sel0(0),
      I1 => S_ADC_CHANNEL(11),
      I2 => sel0(1),
      O => \axi_rdata[11]_i_4_n_0\
    );
\axi_rdata[11]_i_5\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => \ADC_MASTER_CHANNEL_reg_n_0_[11]\,
      I1 => \^q\(11),
      I2 => sel0(1),
      I3 => \ADC_SPI_CR_reg_n_0_[11]\,
      I4 => sel0(0),
      I5 => \ADC_CR_reg_n_0_[11]\,
      O => \axi_rdata[11]_i_5_n_0\
    );
\axi_rdata[12]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => \axi_rdata[12]_i_2_n_0\,
      I1 => \axi_rdata[12]_i_3_n_0\,
      I2 => sel0(3),
      I3 => \axi_rdata[12]_i_4_n_0\,
      I4 => sel0(2),
      I5 => \axi_rdata[12]_i_5_n_0\,
      O => reg_data_out(12)
    );
\axi_rdata[12]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => slv_reg15(12),
      I1 => slv_reg14(12),
      I2 => sel0(1),
      I3 => slv_reg13(12),
      I4 => sel0(0),
      I5 => slv_reg12(12),
      O => \axi_rdata[12]_i_2_n_0\
    );
\axi_rdata[12]_i_3\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => slv_reg11(12),
      I1 => slv_reg10(12),
      I2 => sel0(1),
      I3 => \ADC_AVAILABLE_reg_n_0_[12]\,
      I4 => sel0(0),
      I5 => \^adc_conv_value_reg[30]_0\(12),
      O => \axi_rdata[12]_i_3_n_0\
    );
\axi_rdata[12]_i_4\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"04"
    )
        port map (
      I0 => sel0(0),
      I1 => S_ADC_CHANNEL(12),
      I2 => sel0(1),
      O => \axi_rdata[12]_i_4_n_0\
    );
\axi_rdata[12]_i_5\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => \ADC_MASTER_CHANNEL_reg_n_0_[12]\,
      I1 => \^q\(12),
      I2 => sel0(1),
      I3 => \ADC_SPI_CR_reg_n_0_[12]\,
      I4 => sel0(0),
      I5 => \ADC_CR_reg_n_0_[12]\,
      O => \axi_rdata[12]_i_5_n_0\
    );
\axi_rdata[13]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => \axi_rdata[13]_i_2_n_0\,
      I1 => \axi_rdata[13]_i_3_n_0\,
      I2 => sel0(3),
      I3 => \axi_rdata[13]_i_4_n_0\,
      I4 => sel0(2),
      I5 => \axi_rdata[13]_i_5_n_0\,
      O => reg_data_out(13)
    );
\axi_rdata[13]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => slv_reg15(13),
      I1 => slv_reg14(13),
      I2 => sel0(1),
      I3 => slv_reg13(13),
      I4 => sel0(0),
      I5 => slv_reg12(13),
      O => \axi_rdata[13]_i_2_n_0\
    );
\axi_rdata[13]_i_3\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => slv_reg11(13),
      I1 => slv_reg10(13),
      I2 => sel0(1),
      I3 => \ADC_AVAILABLE_reg_n_0_[13]\,
      I4 => sel0(0),
      I5 => \^adc_conv_value_reg[30]_0\(13),
      O => \axi_rdata[13]_i_3_n_0\
    );
\axi_rdata[13]_i_4\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"04"
    )
        port map (
      I0 => sel0(0),
      I1 => S_ADC_CHANNEL(13),
      I2 => sel0(1),
      O => \axi_rdata[13]_i_4_n_0\
    );
\axi_rdata[13]_i_5\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => \ADC_MASTER_CHANNEL_reg_n_0_[13]\,
      I1 => \^q\(13),
      I2 => sel0(1),
      I3 => \ADC_SPI_CR_reg_n_0_[13]\,
      I4 => sel0(0),
      I5 => \ADC_CR_reg_n_0_[13]\,
      O => \axi_rdata[13]_i_5_n_0\
    );
\axi_rdata[14]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => \axi_rdata[14]_i_2_n_0\,
      I1 => \axi_rdata[14]_i_3_n_0\,
      I2 => sel0(3),
      I3 => \axi_rdata[14]_i_4_n_0\,
      I4 => sel0(2),
      I5 => \axi_rdata[14]_i_5_n_0\,
      O => reg_data_out(14)
    );
\axi_rdata[14]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => slv_reg15(14),
      I1 => slv_reg14(14),
      I2 => sel0(1),
      I3 => slv_reg13(14),
      I4 => sel0(0),
      I5 => slv_reg12(14),
      O => \axi_rdata[14]_i_2_n_0\
    );
\axi_rdata[14]_i_3\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => slv_reg11(14),
      I1 => slv_reg10(14),
      I2 => sel0(1),
      I3 => \ADC_AVAILABLE_reg_n_0_[14]\,
      I4 => sel0(0),
      I5 => \^adc_conv_value_reg[30]_0\(14),
      O => \axi_rdata[14]_i_3_n_0\
    );
\axi_rdata[14]_i_4\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"04"
    )
        port map (
      I0 => sel0(0),
      I1 => S_ADC_CHANNEL(14),
      I2 => sel0(1),
      O => \axi_rdata[14]_i_4_n_0\
    );
\axi_rdata[14]_i_5\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => \ADC_MASTER_CHANNEL_reg_n_0_[14]\,
      I1 => \^q\(14),
      I2 => sel0(1),
      I3 => \ADC_SPI_CR_reg_n_0_[14]\,
      I4 => sel0(0),
      I5 => \ADC_CR_reg_n_0_[14]\,
      O => \axi_rdata[14]_i_5_n_0\
    );
\axi_rdata[15]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => \axi_rdata[15]_i_2_n_0\,
      I1 => \axi_rdata[15]_i_3_n_0\,
      I2 => sel0(3),
      I3 => \axi_rdata[15]_i_4_n_0\,
      I4 => sel0(2),
      I5 => \axi_rdata[15]_i_5_n_0\,
      O => reg_data_out(15)
    );
\axi_rdata[15]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => slv_reg15(15),
      I1 => slv_reg14(15),
      I2 => sel0(1),
      I3 => slv_reg13(15),
      I4 => sel0(0),
      I5 => slv_reg12(15),
      O => \axi_rdata[15]_i_2_n_0\
    );
\axi_rdata[15]_i_3\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => slv_reg11(15),
      I1 => slv_reg10(15),
      I2 => sel0(1),
      I3 => \ADC_AVAILABLE_reg_n_0_[15]\,
      I4 => sel0(0),
      I5 => \^adc_conv_value_reg[30]_0\(15),
      O => \axi_rdata[15]_i_3_n_0\
    );
\axi_rdata[15]_i_4\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"04"
    )
        port map (
      I0 => sel0(0),
      I1 => S_ADC_CHANNEL(15),
      I2 => sel0(1),
      O => \axi_rdata[15]_i_4_n_0\
    );
\axi_rdata[15]_i_5\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => \ADC_MASTER_CHANNEL_reg_n_0_[15]\,
      I1 => \^q\(15),
      I2 => sel0(1),
      I3 => \ADC_SPI_CR_reg_n_0_[15]\,
      I4 => sel0(0),
      I5 => \ADC_CR_reg_n_0_[15]\,
      O => \axi_rdata[15]_i_5_n_0\
    );
\axi_rdata[16]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => \axi_rdata[16]_i_2_n_0\,
      I1 => \axi_rdata[16]_i_3_n_0\,
      I2 => sel0(3),
      I3 => \axi_rdata[16]_i_4_n_0\,
      I4 => sel0(2),
      I5 => \axi_rdata[16]_i_5_n_0\,
      O => reg_data_out(16)
    );
\axi_rdata[16]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => slv_reg15(16),
      I1 => slv_reg14(16),
      I2 => sel0(1),
      I3 => slv_reg13(16),
      I4 => sel0(0),
      I5 => slv_reg12(16),
      O => \axi_rdata[16]_i_2_n_0\
    );
\axi_rdata[16]_i_3\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => slv_reg11(16),
      I1 => slv_reg10(16),
      I2 => sel0(1),
      I3 => \ADC_AVAILABLE_reg_n_0_[16]\,
      I4 => sel0(0),
      I5 => \^adc_conv_value_reg[30]_0\(16),
      O => \axi_rdata[16]_i_3_n_0\
    );
\axi_rdata[16]_i_4\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"04"
    )
        port map (
      I0 => sel0(0),
      I1 => S_ADC_CHANNEL(16),
      I2 => sel0(1),
      O => \axi_rdata[16]_i_4_n_0\
    );
\axi_rdata[16]_i_5\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => \ADC_MASTER_CHANNEL_reg_n_0_[16]\,
      I1 => \^q\(16),
      I2 => sel0(1),
      I3 => \ADC_SPI_CR_reg_n_0_[16]\,
      I4 => sel0(0),
      I5 => \ADC_CR_reg_n_0_[16]\,
      O => \axi_rdata[16]_i_5_n_0\
    );
\axi_rdata[17]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => \axi_rdata[17]_i_2_n_0\,
      I1 => \axi_rdata[17]_i_3_n_0\,
      I2 => sel0(3),
      I3 => \axi_rdata[17]_i_4_n_0\,
      I4 => sel0(2),
      I5 => \axi_rdata[17]_i_5_n_0\,
      O => reg_data_out(17)
    );
\axi_rdata[17]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => slv_reg15(17),
      I1 => slv_reg14(17),
      I2 => sel0(1),
      I3 => slv_reg13(17),
      I4 => sel0(0),
      I5 => slv_reg12(17),
      O => \axi_rdata[17]_i_2_n_0\
    );
\axi_rdata[17]_i_3\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => slv_reg11(17),
      I1 => slv_reg10(17),
      I2 => sel0(1),
      I3 => \ADC_AVAILABLE_reg_n_0_[17]\,
      I4 => sel0(0),
      I5 => \^adc_conv_value_reg[30]_0\(17),
      O => \axi_rdata[17]_i_3_n_0\
    );
\axi_rdata[17]_i_4\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"04"
    )
        port map (
      I0 => sel0(0),
      I1 => S_ADC_CHANNEL(17),
      I2 => sel0(1),
      O => \axi_rdata[17]_i_4_n_0\
    );
\axi_rdata[17]_i_5\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => \ADC_MASTER_CHANNEL_reg_n_0_[17]\,
      I1 => \^q\(17),
      I2 => sel0(1),
      I3 => \ADC_SPI_CR_reg_n_0_[17]\,
      I4 => sel0(0),
      I5 => \ADC_CR_reg_n_0_[17]\,
      O => \axi_rdata[17]_i_5_n_0\
    );
\axi_rdata[18]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => \axi_rdata[18]_i_2_n_0\,
      I1 => \axi_rdata[18]_i_3_n_0\,
      I2 => sel0(3),
      I3 => \axi_rdata[18]_i_4_n_0\,
      I4 => sel0(2),
      I5 => \axi_rdata[18]_i_5_n_0\,
      O => reg_data_out(18)
    );
\axi_rdata[18]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => slv_reg15(18),
      I1 => slv_reg14(18),
      I2 => sel0(1),
      I3 => slv_reg13(18),
      I4 => sel0(0),
      I5 => slv_reg12(18),
      O => \axi_rdata[18]_i_2_n_0\
    );
\axi_rdata[18]_i_3\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => slv_reg11(18),
      I1 => slv_reg10(18),
      I2 => sel0(1),
      I3 => \ADC_AVAILABLE_reg_n_0_[18]\,
      I4 => sel0(0),
      I5 => \^adc_conv_value_reg[30]_0\(18),
      O => \axi_rdata[18]_i_3_n_0\
    );
\axi_rdata[18]_i_4\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"04"
    )
        port map (
      I0 => sel0(0),
      I1 => S_ADC_CHANNEL(18),
      I2 => sel0(1),
      O => \axi_rdata[18]_i_4_n_0\
    );
\axi_rdata[18]_i_5\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => \ADC_MASTER_CHANNEL_reg_n_0_[18]\,
      I1 => \^q\(18),
      I2 => sel0(1),
      I3 => \ADC_SPI_CR_reg_n_0_[18]\,
      I4 => sel0(0),
      I5 => \ADC_CR_reg_n_0_[18]\,
      O => \axi_rdata[18]_i_5_n_0\
    );
\axi_rdata[19]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => \axi_rdata[19]_i_2_n_0\,
      I1 => \axi_rdata[19]_i_3_n_0\,
      I2 => sel0(3),
      I3 => \axi_rdata[19]_i_4_n_0\,
      I4 => sel0(2),
      I5 => \axi_rdata[19]_i_5_n_0\,
      O => reg_data_out(19)
    );
\axi_rdata[19]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => slv_reg15(19),
      I1 => slv_reg14(19),
      I2 => sel0(1),
      I3 => slv_reg13(19),
      I4 => sel0(0),
      I5 => slv_reg12(19),
      O => \axi_rdata[19]_i_2_n_0\
    );
\axi_rdata[19]_i_3\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => slv_reg11(19),
      I1 => slv_reg10(19),
      I2 => sel0(1),
      I3 => \ADC_AVAILABLE_reg_n_0_[19]\,
      I4 => sel0(0),
      I5 => \^adc_conv_value_reg[30]_0\(19),
      O => \axi_rdata[19]_i_3_n_0\
    );
\axi_rdata[19]_i_4\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"04"
    )
        port map (
      I0 => sel0(0),
      I1 => S_ADC_CHANNEL(19),
      I2 => sel0(1),
      O => \axi_rdata[19]_i_4_n_0\
    );
\axi_rdata[19]_i_5\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => \ADC_MASTER_CHANNEL_reg_n_0_[19]\,
      I1 => \^q\(19),
      I2 => sel0(1),
      I3 => \ADC_SPI_CR_reg_n_0_[19]\,
      I4 => sel0(0),
      I5 => \ADC_CR_reg_n_0_[19]\,
      O => \axi_rdata[19]_i_5_n_0\
    );
\axi_rdata[1]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => \axi_rdata[1]_i_2_n_0\,
      I1 => \axi_rdata[1]_i_3_n_0\,
      I2 => sel0(3),
      I3 => \axi_rdata[1]_i_4_n_0\,
      I4 => sel0(2),
      I5 => \axi_rdata[1]_i_5_n_0\,
      O => reg_data_out(1)
    );
\axi_rdata[1]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => slv_reg15(1),
      I1 => slv_reg14(1),
      I2 => sel0(1),
      I3 => slv_reg13(1),
      I4 => sel0(0),
      I5 => slv_reg12(1),
      O => \axi_rdata[1]_i_2_n_0\
    );
\axi_rdata[1]_i_3\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => slv_reg11(1),
      I1 => slv_reg10(1),
      I2 => sel0(1),
      I3 => \ADC_AVAILABLE_reg_n_0_[1]\,
      I4 => sel0(0),
      I5 => \^adc_conv_value_reg[30]_0\(1),
      O => \axi_rdata[1]_i_3_n_0\
    );
\axi_rdata[1]_i_4\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"04"
    )
        port map (
      I0 => sel0(0),
      I1 => S_ADC_CHANNEL(1),
      I2 => sel0(1),
      O => \axi_rdata[1]_i_4_n_0\
    );
\axi_rdata[1]_i_5\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => \ADC_MASTER_CHANNEL_reg_n_0_[1]\,
      I1 => \^q\(1),
      I2 => sel0(1),
      I3 => \ADC_SPI_CR_reg_n_0_[1]\,
      I4 => sel0(0),
      I5 => S_ADC_CR(1),
      O => \axi_rdata[1]_i_5_n_0\
    );
\axi_rdata[20]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => \axi_rdata[20]_i_2_n_0\,
      I1 => \axi_rdata[20]_i_3_n_0\,
      I2 => sel0(3),
      I3 => \axi_rdata[20]_i_4_n_0\,
      I4 => sel0(2),
      I5 => \axi_rdata[20]_i_5_n_0\,
      O => reg_data_out(20)
    );
\axi_rdata[20]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => slv_reg15(20),
      I1 => slv_reg14(20),
      I2 => sel0(1),
      I3 => slv_reg13(20),
      I4 => sel0(0),
      I5 => slv_reg12(20),
      O => \axi_rdata[20]_i_2_n_0\
    );
\axi_rdata[20]_i_3\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => slv_reg11(20),
      I1 => slv_reg10(20),
      I2 => sel0(1),
      I3 => \ADC_AVAILABLE_reg_n_0_[20]\,
      I4 => sel0(0),
      I5 => \^adc_conv_value_reg[30]_0\(20),
      O => \axi_rdata[20]_i_3_n_0\
    );
\axi_rdata[20]_i_4\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"04"
    )
        port map (
      I0 => sel0(0),
      I1 => S_ADC_CHANNEL(20),
      I2 => sel0(1),
      O => \axi_rdata[20]_i_4_n_0\
    );
\axi_rdata[20]_i_5\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => \ADC_MASTER_CHANNEL_reg_n_0_[20]\,
      I1 => \^q\(20),
      I2 => sel0(1),
      I3 => \ADC_SPI_CR_reg_n_0_[20]\,
      I4 => sel0(0),
      I5 => \ADC_CR_reg_n_0_[20]\,
      O => \axi_rdata[20]_i_5_n_0\
    );
\axi_rdata[21]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => \axi_rdata[21]_i_2_n_0\,
      I1 => \axi_rdata[21]_i_3_n_0\,
      I2 => sel0(3),
      I3 => \axi_rdata[21]_i_4_n_0\,
      I4 => sel0(2),
      I5 => \axi_rdata[21]_i_5_n_0\,
      O => reg_data_out(21)
    );
\axi_rdata[21]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => slv_reg15(21),
      I1 => slv_reg14(21),
      I2 => sel0(1),
      I3 => slv_reg13(21),
      I4 => sel0(0),
      I5 => slv_reg12(21),
      O => \axi_rdata[21]_i_2_n_0\
    );
\axi_rdata[21]_i_3\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => slv_reg11(21),
      I1 => slv_reg10(21),
      I2 => sel0(1),
      I3 => \ADC_AVAILABLE_reg_n_0_[21]\,
      I4 => sel0(0),
      I5 => \^adc_conv_value_reg[30]_0\(21),
      O => \axi_rdata[21]_i_3_n_0\
    );
\axi_rdata[21]_i_4\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"04"
    )
        port map (
      I0 => sel0(0),
      I1 => S_ADC_CHANNEL(21),
      I2 => sel0(1),
      O => \axi_rdata[21]_i_4_n_0\
    );
\axi_rdata[21]_i_5\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => \ADC_MASTER_CHANNEL_reg_n_0_[21]\,
      I1 => \^q\(21),
      I2 => sel0(1),
      I3 => \ADC_SPI_CR_reg_n_0_[21]\,
      I4 => sel0(0),
      I5 => \ADC_CR_reg_n_0_[21]\,
      O => \axi_rdata[21]_i_5_n_0\
    );
\axi_rdata[22]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => \axi_rdata[22]_i_2_n_0\,
      I1 => \axi_rdata[22]_i_3_n_0\,
      I2 => sel0(3),
      I3 => \axi_rdata[22]_i_4_n_0\,
      I4 => sel0(2),
      I5 => \axi_rdata[22]_i_5_n_0\,
      O => reg_data_out(22)
    );
\axi_rdata[22]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => slv_reg15(22),
      I1 => slv_reg14(22),
      I2 => sel0(1),
      I3 => slv_reg13(22),
      I4 => sel0(0),
      I5 => slv_reg12(22),
      O => \axi_rdata[22]_i_2_n_0\
    );
\axi_rdata[22]_i_3\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => slv_reg11(22),
      I1 => slv_reg10(22),
      I2 => sel0(1),
      I3 => \ADC_AVAILABLE_reg_n_0_[22]\,
      I4 => sel0(0),
      I5 => \^adc_conv_value_reg[30]_0\(22),
      O => \axi_rdata[22]_i_3_n_0\
    );
\axi_rdata[22]_i_4\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"04"
    )
        port map (
      I0 => sel0(0),
      I1 => S_ADC_CHANNEL(22),
      I2 => sel0(1),
      O => \axi_rdata[22]_i_4_n_0\
    );
\axi_rdata[22]_i_5\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => \ADC_MASTER_CHANNEL_reg_n_0_[22]\,
      I1 => \^q\(22),
      I2 => sel0(1),
      I3 => \ADC_SPI_CR_reg_n_0_[22]\,
      I4 => sel0(0),
      I5 => \ADC_CR_reg_n_0_[22]\,
      O => \axi_rdata[22]_i_5_n_0\
    );
\axi_rdata[23]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => \axi_rdata[23]_i_2_n_0\,
      I1 => \axi_rdata[23]_i_3_n_0\,
      I2 => sel0(3),
      I3 => \axi_rdata[23]_i_4_n_0\,
      I4 => sel0(2),
      I5 => \axi_rdata[23]_i_5_n_0\,
      O => reg_data_out(23)
    );
\axi_rdata[23]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => slv_reg15(23),
      I1 => slv_reg14(23),
      I2 => sel0(1),
      I3 => slv_reg13(23),
      I4 => sel0(0),
      I5 => slv_reg12(23),
      O => \axi_rdata[23]_i_2_n_0\
    );
\axi_rdata[23]_i_3\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => slv_reg11(23),
      I1 => slv_reg10(23),
      I2 => sel0(1),
      I3 => \ADC_AVAILABLE_reg_n_0_[23]\,
      I4 => sel0(0),
      I5 => \^adc_conv_value_reg[30]_0\(23),
      O => \axi_rdata[23]_i_3_n_0\
    );
\axi_rdata[23]_i_4\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"04"
    )
        port map (
      I0 => sel0(0),
      I1 => S_ADC_CHANNEL(23),
      I2 => sel0(1),
      O => \axi_rdata[23]_i_4_n_0\
    );
\axi_rdata[23]_i_5\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => \ADC_MASTER_CHANNEL_reg_n_0_[23]\,
      I1 => \^q\(23),
      I2 => sel0(1),
      I3 => \ADC_SPI_CR_reg_n_0_[23]\,
      I4 => sel0(0),
      I5 => \ADC_CR_reg_n_0_[23]\,
      O => \axi_rdata[23]_i_5_n_0\
    );
\axi_rdata[24]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => \axi_rdata[24]_i_2_n_0\,
      I1 => \axi_rdata[24]_i_3_n_0\,
      I2 => sel0(3),
      I3 => \axi_rdata[24]_i_4_n_0\,
      I4 => sel0(2),
      I5 => \axi_rdata[24]_i_5_n_0\,
      O => reg_data_out(24)
    );
\axi_rdata[24]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => slv_reg15(24),
      I1 => slv_reg14(24),
      I2 => sel0(1),
      I3 => slv_reg13(24),
      I4 => sel0(0),
      I5 => slv_reg12(24),
      O => \axi_rdata[24]_i_2_n_0\
    );
\axi_rdata[24]_i_3\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => slv_reg11(24),
      I1 => slv_reg10(24),
      I2 => sel0(1),
      I3 => \ADC_AVAILABLE_reg_n_0_[24]\,
      I4 => sel0(0),
      I5 => \^adc_conv_value_reg[30]_0\(24),
      O => \axi_rdata[24]_i_3_n_0\
    );
\axi_rdata[24]_i_4\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"04"
    )
        port map (
      I0 => sel0(0),
      I1 => S_ADC_CHANNEL(24),
      I2 => sel0(1),
      O => \axi_rdata[24]_i_4_n_0\
    );
\axi_rdata[24]_i_5\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => \ADC_MASTER_CHANNEL_reg_n_0_[24]\,
      I1 => \^q\(24),
      I2 => sel0(1),
      I3 => \ADC_SPI_CR_reg_n_0_[24]\,
      I4 => sel0(0),
      I5 => \ADC_CR_reg_n_0_[24]\,
      O => \axi_rdata[24]_i_5_n_0\
    );
\axi_rdata[25]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => \axi_rdata[25]_i_2_n_0\,
      I1 => \axi_rdata[25]_i_3_n_0\,
      I2 => sel0(3),
      I3 => \axi_rdata[25]_i_4_n_0\,
      I4 => sel0(2),
      I5 => \axi_rdata[25]_i_5_n_0\,
      O => reg_data_out(25)
    );
\axi_rdata[25]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => slv_reg15(25),
      I1 => slv_reg14(25),
      I2 => sel0(1),
      I3 => slv_reg13(25),
      I4 => sel0(0),
      I5 => slv_reg12(25),
      O => \axi_rdata[25]_i_2_n_0\
    );
\axi_rdata[25]_i_3\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => slv_reg11(25),
      I1 => slv_reg10(25),
      I2 => sel0(1),
      I3 => \ADC_AVAILABLE_reg_n_0_[25]\,
      I4 => sel0(0),
      I5 => \^adc_conv_value_reg[30]_0\(25),
      O => \axi_rdata[25]_i_3_n_0\
    );
\axi_rdata[25]_i_4\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"04"
    )
        port map (
      I0 => sel0(0),
      I1 => S_ADC_CHANNEL(25),
      I2 => sel0(1),
      O => \axi_rdata[25]_i_4_n_0\
    );
\axi_rdata[25]_i_5\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => \ADC_MASTER_CHANNEL_reg_n_0_[25]\,
      I1 => \^q\(25),
      I2 => sel0(1),
      I3 => \ADC_SPI_CR_reg_n_0_[25]\,
      I4 => sel0(0),
      I5 => \ADC_CR_reg_n_0_[25]\,
      O => \axi_rdata[25]_i_5_n_0\
    );
\axi_rdata[26]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => \axi_rdata[26]_i_2_n_0\,
      I1 => \axi_rdata[26]_i_3_n_0\,
      I2 => sel0(3),
      I3 => \axi_rdata[26]_i_4_n_0\,
      I4 => sel0(2),
      I5 => \axi_rdata[26]_i_5_n_0\,
      O => reg_data_out(26)
    );
\axi_rdata[26]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => slv_reg15(26),
      I1 => slv_reg14(26),
      I2 => sel0(1),
      I3 => slv_reg13(26),
      I4 => sel0(0),
      I5 => slv_reg12(26),
      O => \axi_rdata[26]_i_2_n_0\
    );
\axi_rdata[26]_i_3\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => slv_reg11(26),
      I1 => slv_reg10(26),
      I2 => sel0(1),
      I3 => \ADC_AVAILABLE_reg_n_0_[26]\,
      I4 => sel0(0),
      I5 => \^adc_conv_value_reg[30]_0\(26),
      O => \axi_rdata[26]_i_3_n_0\
    );
\axi_rdata[26]_i_4\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"04"
    )
        port map (
      I0 => sel0(0),
      I1 => S_ADC_CHANNEL(26),
      I2 => sel0(1),
      O => \axi_rdata[26]_i_4_n_0\
    );
\axi_rdata[26]_i_5\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => \ADC_MASTER_CHANNEL_reg_n_0_[26]\,
      I1 => \^q\(26),
      I2 => sel0(1),
      I3 => \ADC_SPI_CR_reg_n_0_[26]\,
      I4 => sel0(0),
      I5 => \ADC_CR_reg_n_0_[26]\,
      O => \axi_rdata[26]_i_5_n_0\
    );
\axi_rdata[27]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => \axi_rdata[27]_i_2_n_0\,
      I1 => \axi_rdata[27]_i_3_n_0\,
      I2 => sel0(3),
      I3 => \axi_rdata[27]_i_4_n_0\,
      I4 => sel0(2),
      I5 => \axi_rdata[27]_i_5_n_0\,
      O => reg_data_out(27)
    );
\axi_rdata[27]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => slv_reg15(27),
      I1 => slv_reg14(27),
      I2 => sel0(1),
      I3 => slv_reg13(27),
      I4 => sel0(0),
      I5 => slv_reg12(27),
      O => \axi_rdata[27]_i_2_n_0\
    );
\axi_rdata[27]_i_3\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => slv_reg11(27),
      I1 => slv_reg10(27),
      I2 => sel0(1),
      I3 => \ADC_AVAILABLE_reg_n_0_[27]\,
      I4 => sel0(0),
      I5 => \^adc_conv_value_reg[30]_0\(27),
      O => \axi_rdata[27]_i_3_n_0\
    );
\axi_rdata[27]_i_4\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"04"
    )
        port map (
      I0 => sel0(0),
      I1 => S_ADC_CHANNEL(27),
      I2 => sel0(1),
      O => \axi_rdata[27]_i_4_n_0\
    );
\axi_rdata[27]_i_5\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => \ADC_MASTER_CHANNEL_reg_n_0_[27]\,
      I1 => \^q\(27),
      I2 => sel0(1),
      I3 => \ADC_SPI_CR_reg_n_0_[27]\,
      I4 => sel0(0),
      I5 => \ADC_CR_reg_n_0_[27]\,
      O => \axi_rdata[27]_i_5_n_0\
    );
\axi_rdata[28]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => \axi_rdata[28]_i_2_n_0\,
      I1 => \axi_rdata[28]_i_3_n_0\,
      I2 => sel0(3),
      I3 => \axi_rdata[28]_i_4_n_0\,
      I4 => sel0(2),
      I5 => \axi_rdata[28]_i_5_n_0\,
      O => reg_data_out(28)
    );
\axi_rdata[28]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => slv_reg15(28),
      I1 => slv_reg14(28),
      I2 => sel0(1),
      I3 => slv_reg13(28),
      I4 => sel0(0),
      I5 => slv_reg12(28),
      O => \axi_rdata[28]_i_2_n_0\
    );
\axi_rdata[28]_i_3\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => slv_reg11(28),
      I1 => slv_reg10(28),
      I2 => sel0(1),
      I3 => \ADC_AVAILABLE_reg_n_0_[28]\,
      I4 => sel0(0),
      I5 => \^adc_conv_value_reg[30]_0\(28),
      O => \axi_rdata[28]_i_3_n_0\
    );
\axi_rdata[28]_i_4\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"04"
    )
        port map (
      I0 => sel0(0),
      I1 => S_ADC_CHANNEL(28),
      I2 => sel0(1),
      O => \axi_rdata[28]_i_4_n_0\
    );
\axi_rdata[28]_i_5\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => \ADC_MASTER_CHANNEL_reg_n_0_[28]\,
      I1 => \^q\(28),
      I2 => sel0(1),
      I3 => \ADC_SPI_CR_reg_n_0_[28]\,
      I4 => sel0(0),
      I5 => \ADC_CR_reg_n_0_[28]\,
      O => \axi_rdata[28]_i_5_n_0\
    );
\axi_rdata[29]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => \axi_rdata[29]_i_2_n_0\,
      I1 => \axi_rdata[29]_i_3_n_0\,
      I2 => sel0(3),
      I3 => \axi_rdata[29]_i_4_n_0\,
      I4 => sel0(2),
      I5 => \axi_rdata[29]_i_5_n_0\,
      O => reg_data_out(29)
    );
\axi_rdata[29]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => slv_reg15(29),
      I1 => slv_reg14(29),
      I2 => sel0(1),
      I3 => slv_reg13(29),
      I4 => sel0(0),
      I5 => slv_reg12(29),
      O => \axi_rdata[29]_i_2_n_0\
    );
\axi_rdata[29]_i_3\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => slv_reg11(29),
      I1 => slv_reg10(29),
      I2 => sel0(1),
      I3 => \ADC_AVAILABLE_reg_n_0_[29]\,
      I4 => sel0(0),
      I5 => \^adc_conv_value_reg[30]_0\(29),
      O => \axi_rdata[29]_i_3_n_0\
    );
\axi_rdata[29]_i_4\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"04"
    )
        port map (
      I0 => sel0(0),
      I1 => S_ADC_CHANNEL(29),
      I2 => sel0(1),
      O => \axi_rdata[29]_i_4_n_0\
    );
\axi_rdata[29]_i_5\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => \ADC_MASTER_CHANNEL_reg_n_0_[29]\,
      I1 => \^q\(29),
      I2 => sel0(1),
      I3 => \ADC_SPI_CR_reg_n_0_[29]\,
      I4 => sel0(0),
      I5 => \ADC_CR_reg_n_0_[29]\,
      O => \axi_rdata[29]_i_5_n_0\
    );
\axi_rdata[2]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => \axi_rdata[2]_i_2_n_0\,
      I1 => \axi_rdata[2]_i_3_n_0\,
      I2 => sel0(3),
      I3 => \axi_rdata[2]_i_4_n_0\,
      I4 => sel0(2),
      I5 => \axi_rdata[2]_i_5_n_0\,
      O => reg_data_out(2)
    );
\axi_rdata[2]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => slv_reg15(2),
      I1 => slv_reg14(2),
      I2 => sel0(1),
      I3 => slv_reg13(2),
      I4 => sel0(0),
      I5 => slv_reg12(2),
      O => \axi_rdata[2]_i_2_n_0\
    );
\axi_rdata[2]_i_3\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => slv_reg11(2),
      I1 => slv_reg10(2),
      I2 => sel0(1),
      I3 => \ADC_AVAILABLE_reg_n_0_[2]\,
      I4 => sel0(0),
      I5 => \^adc_conv_value_reg[30]_0\(2),
      O => \axi_rdata[2]_i_3_n_0\
    );
\axi_rdata[2]_i_4\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"04"
    )
        port map (
      I0 => sel0(0),
      I1 => S_ADC_CHANNEL(2),
      I2 => sel0(1),
      O => \axi_rdata[2]_i_4_n_0\
    );
\axi_rdata[2]_i_5\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => \ADC_MASTER_CHANNEL_reg_n_0_[2]\,
      I1 => \^q\(2),
      I2 => sel0(1),
      I3 => \^d\(1),
      I4 => sel0(0),
      I5 => S_ADC_CR(2),
      O => \axi_rdata[2]_i_5_n_0\
    );
\axi_rdata[30]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => \axi_rdata[30]_i_2_n_0\,
      I1 => \axi_rdata[30]_i_3_n_0\,
      I2 => sel0(3),
      I3 => \axi_rdata[30]_i_4_n_0\,
      I4 => sel0(2),
      I5 => \axi_rdata[30]_i_5_n_0\,
      O => reg_data_out(30)
    );
\axi_rdata[30]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => slv_reg15(30),
      I1 => slv_reg14(30),
      I2 => sel0(1),
      I3 => slv_reg13(30),
      I4 => sel0(0),
      I5 => slv_reg12(30),
      O => \axi_rdata[30]_i_2_n_0\
    );
\axi_rdata[30]_i_3\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => slv_reg11(30),
      I1 => slv_reg10(30),
      I2 => sel0(1),
      I3 => \ADC_AVAILABLE_reg_n_0_[30]\,
      I4 => sel0(0),
      I5 => \^adc_conv_value_reg[30]_0\(30),
      O => \axi_rdata[30]_i_3_n_0\
    );
\axi_rdata[30]_i_4\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"04"
    )
        port map (
      I0 => sel0(0),
      I1 => S_ADC_CHANNEL(30),
      I2 => sel0(1),
      O => \axi_rdata[30]_i_4_n_0\
    );
\axi_rdata[30]_i_5\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => \ADC_MASTER_CHANNEL_reg_n_0_[30]\,
      I1 => \^q\(30),
      I2 => sel0(1),
      I3 => \ADC_SPI_CR_reg_n_0_[30]\,
      I4 => sel0(0),
      I5 => \ADC_CR_reg_n_0_[30]\,
      O => \axi_rdata[30]_i_5_n_0\
    );
\axi_rdata[31]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"08"
    )
        port map (
      I0 => s00_axi_arvalid,
      I1 => \^axi_arready_reg_0\,
      I2 => \^s00_axi_rvalid\,
      O => slv_reg_rden
    );
\axi_rdata[31]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => \axi_rdata[31]_i_3_n_0\,
      I1 => \axi_rdata[31]_i_4_n_0\,
      I2 => sel0(3),
      I3 => \axi_rdata[31]_i_5_n_0\,
      I4 => sel0(2),
      I5 => \axi_rdata[31]_i_6_n_0\,
      O => reg_data_out(31)
    );
\axi_rdata[31]_i_3\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => slv_reg15(31),
      I1 => slv_reg14(31),
      I2 => sel0(1),
      I3 => slv_reg13(31),
      I4 => sel0(0),
      I5 => slv_reg12(31),
      O => \axi_rdata[31]_i_3_n_0\
    );
\axi_rdata[31]_i_4\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => slv_reg11(31),
      I1 => slv_reg10(31),
      I2 => sel0(1),
      I3 => \ADC_AVAILABLE_reg_n_0_[31]\,
      I4 => sel0(0),
      I5 => S_ADC_CONV_VALUE(31),
      O => \axi_rdata[31]_i_4_n_0\
    );
\axi_rdata[31]_i_5\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"04"
    )
        port map (
      I0 => sel0(0),
      I1 => S_ADC_CHANNEL(31),
      I2 => sel0(1),
      O => \axi_rdata[31]_i_5_n_0\
    );
\axi_rdata[31]_i_6\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => \ADC_MASTER_CHANNEL_reg_n_0_[31]\,
      I1 => \^q\(31),
      I2 => sel0(1),
      I3 => \ADC_SPI_CR_reg_n_0_[31]\,
      I4 => sel0(0),
      I5 => \ADC_CR_reg_n_0_[31]\,
      O => \axi_rdata[31]_i_6_n_0\
    );
\axi_rdata[3]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => \axi_rdata[3]_i_2_n_0\,
      I1 => \axi_rdata[3]_i_3_n_0\,
      I2 => sel0(3),
      I3 => \axi_rdata[3]_i_4_n_0\,
      I4 => sel0(2),
      I5 => \axi_rdata[3]_i_5_n_0\,
      O => reg_data_out(3)
    );
\axi_rdata[3]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => slv_reg15(3),
      I1 => slv_reg14(3),
      I2 => sel0(1),
      I3 => slv_reg13(3),
      I4 => sel0(0),
      I5 => slv_reg12(3),
      O => \axi_rdata[3]_i_2_n_0\
    );
\axi_rdata[3]_i_3\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => slv_reg11(3),
      I1 => slv_reg10(3),
      I2 => sel0(1),
      I3 => \ADC_AVAILABLE_reg_n_0_[3]\,
      I4 => sel0(0),
      I5 => \^adc_conv_value_reg[30]_0\(3),
      O => \axi_rdata[3]_i_3_n_0\
    );
\axi_rdata[3]_i_4\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"04"
    )
        port map (
      I0 => sel0(0),
      I1 => S_ADC_CHANNEL(3),
      I2 => sel0(1),
      O => \axi_rdata[3]_i_4_n_0\
    );
\axi_rdata[3]_i_5\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => \ADC_MASTER_CHANNEL_reg_n_0_[3]\,
      I1 => \^q\(3),
      I2 => sel0(1),
      I3 => \ADC_SPI_CR_reg_n_0_[3]\,
      I4 => sel0(0),
      I5 => \^adc_cr_reg[3]_0\(0),
      O => \axi_rdata[3]_i_5_n_0\
    );
\axi_rdata[4]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => \axi_rdata[4]_i_2_n_0\,
      I1 => \axi_rdata[4]_i_3_n_0\,
      I2 => sel0(3),
      I3 => \axi_rdata[4]_i_4_n_0\,
      I4 => sel0(2),
      I5 => \axi_rdata[4]_i_5_n_0\,
      O => reg_data_out(4)
    );
\axi_rdata[4]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => slv_reg15(4),
      I1 => slv_reg14(4),
      I2 => sel0(1),
      I3 => slv_reg13(4),
      I4 => sel0(0),
      I5 => slv_reg12(4),
      O => \axi_rdata[4]_i_2_n_0\
    );
\axi_rdata[4]_i_3\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => slv_reg11(4),
      I1 => slv_reg10(4),
      I2 => sel0(1),
      I3 => \ADC_AVAILABLE_reg_n_0_[4]\,
      I4 => sel0(0),
      I5 => \^adc_conv_value_reg[30]_0\(4),
      O => \axi_rdata[4]_i_3_n_0\
    );
\axi_rdata[4]_i_4\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"04"
    )
        port map (
      I0 => sel0(0),
      I1 => S_ADC_CHANNEL(4),
      I2 => sel0(1),
      O => \axi_rdata[4]_i_4_n_0\
    );
\axi_rdata[4]_i_5\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => \ADC_MASTER_CHANNEL_reg_n_0_[4]\,
      I1 => \^q\(4),
      I2 => sel0(1),
      I3 => p_0_in13_in,
      I4 => sel0(0),
      I5 => S_ADC_CR(4),
      O => \axi_rdata[4]_i_5_n_0\
    );
\axi_rdata[5]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => \axi_rdata[5]_i_2_n_0\,
      I1 => \axi_rdata[5]_i_3_n_0\,
      I2 => sel0(3),
      I3 => \axi_rdata[5]_i_4_n_0\,
      I4 => sel0(2),
      I5 => \axi_rdata[5]_i_5_n_0\,
      O => reg_data_out(5)
    );
\axi_rdata[5]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => slv_reg15(5),
      I1 => slv_reg14(5),
      I2 => sel0(1),
      I3 => slv_reg13(5),
      I4 => sel0(0),
      I5 => slv_reg12(5),
      O => \axi_rdata[5]_i_2_n_0\
    );
\axi_rdata[5]_i_3\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => slv_reg11(5),
      I1 => slv_reg10(5),
      I2 => sel0(1),
      I3 => \ADC_AVAILABLE_reg_n_0_[5]\,
      I4 => sel0(0),
      I5 => \^adc_conv_value_reg[30]_0\(5),
      O => \axi_rdata[5]_i_3_n_0\
    );
\axi_rdata[5]_i_4\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"04"
    )
        port map (
      I0 => sel0(0),
      I1 => S_ADC_CHANNEL(5),
      I2 => sel0(1),
      O => \axi_rdata[5]_i_4_n_0\
    );
\axi_rdata[5]_i_5\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => \ADC_MASTER_CHANNEL_reg_n_0_[5]\,
      I1 => \^q\(5),
      I2 => sel0(1),
      I3 => \ADC_SPI_CR_reg_n_0_[5]\,
      I4 => sel0(0),
      I5 => S_ADC_CR(5),
      O => \axi_rdata[5]_i_5_n_0\
    );
\axi_rdata[6]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => \axi_rdata[6]_i_2_n_0\,
      I1 => \axi_rdata[6]_i_3_n_0\,
      I2 => sel0(3),
      I3 => \axi_rdata[6]_i_4_n_0\,
      I4 => sel0(2),
      I5 => \axi_rdata[6]_i_5_n_0\,
      O => reg_data_out(6)
    );
\axi_rdata[6]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => slv_reg15(6),
      I1 => slv_reg14(6),
      I2 => sel0(1),
      I3 => slv_reg13(6),
      I4 => sel0(0),
      I5 => slv_reg12(6),
      O => \axi_rdata[6]_i_2_n_0\
    );
\axi_rdata[6]_i_3\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => slv_reg11(6),
      I1 => slv_reg10(6),
      I2 => sel0(1),
      I3 => \ADC_AVAILABLE_reg_n_0_[6]\,
      I4 => sel0(0),
      I5 => \^adc_conv_value_reg[30]_0\(6),
      O => \axi_rdata[6]_i_3_n_0\
    );
\axi_rdata[6]_i_4\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"04"
    )
        port map (
      I0 => sel0(0),
      I1 => S_ADC_CHANNEL(6),
      I2 => sel0(1),
      O => \axi_rdata[6]_i_4_n_0\
    );
\axi_rdata[6]_i_5\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => \ADC_MASTER_CHANNEL_reg_n_0_[6]\,
      I1 => \^q\(6),
      I2 => sel0(1),
      I3 => \^cpol\,
      I4 => sel0(0),
      I5 => S_ADC_CR(6),
      O => \axi_rdata[6]_i_5_n_0\
    );
\axi_rdata[7]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => \axi_rdata[7]_i_2_n_0\,
      I1 => \axi_rdata[7]_i_3_n_0\,
      I2 => sel0(3),
      I3 => \axi_rdata[7]_i_4_n_0\,
      I4 => sel0(2),
      I5 => \axi_rdata[7]_i_5_n_0\,
      O => reg_data_out(7)
    );
\axi_rdata[7]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => slv_reg15(7),
      I1 => slv_reg14(7),
      I2 => sel0(1),
      I3 => slv_reg13(7),
      I4 => sel0(0),
      I5 => slv_reg12(7),
      O => \axi_rdata[7]_i_2_n_0\
    );
\axi_rdata[7]_i_3\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => slv_reg11(7),
      I1 => slv_reg10(7),
      I2 => sel0(1),
      I3 => \ADC_AVAILABLE_reg_n_0_[7]\,
      I4 => sel0(0),
      I5 => \^adc_conv_value_reg[30]_0\(7),
      O => \axi_rdata[7]_i_3_n_0\
    );
\axi_rdata[7]_i_4\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"04"
    )
        port map (
      I0 => sel0(0),
      I1 => S_ADC_CHANNEL(7),
      I2 => sel0(1),
      O => \axi_rdata[7]_i_4_n_0\
    );
\axi_rdata[7]_i_5\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => \ADC_MASTER_CHANNEL_reg_n_0_[7]\,
      I1 => \^q\(7),
      I2 => sel0(1),
      I3 => \^cpha\,
      I4 => sel0(0),
      I5 => S_ADC_CR(7),
      O => \axi_rdata[7]_i_5_n_0\
    );
\axi_rdata[8]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => \axi_rdata[8]_i_2_n_0\,
      I1 => \axi_rdata[8]_i_3_n_0\,
      I2 => sel0(3),
      I3 => \axi_rdata[8]_i_4_n_0\,
      I4 => sel0(2),
      I5 => \axi_rdata[8]_i_5_n_0\,
      O => reg_data_out(8)
    );
\axi_rdata[8]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => slv_reg15(8),
      I1 => slv_reg14(8),
      I2 => sel0(1),
      I3 => slv_reg13(8),
      I4 => sel0(0),
      I5 => slv_reg12(8),
      O => \axi_rdata[8]_i_2_n_0\
    );
\axi_rdata[8]_i_3\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => slv_reg11(8),
      I1 => slv_reg10(8),
      I2 => sel0(1),
      I3 => \ADC_AVAILABLE_reg_n_0_[8]\,
      I4 => sel0(0),
      I5 => \^adc_conv_value_reg[30]_0\(8),
      O => \axi_rdata[8]_i_3_n_0\
    );
\axi_rdata[8]_i_4\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"04"
    )
        port map (
      I0 => sel0(0),
      I1 => S_ADC_CHANNEL(8),
      I2 => sel0(1),
      O => \axi_rdata[8]_i_4_n_0\
    );
\axi_rdata[8]_i_5\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => \ADC_MASTER_CHANNEL_reg_n_0_[8]\,
      I1 => \^q\(8),
      I2 => sel0(1),
      I3 => \ADC_SPI_CR_reg_n_0_[8]\,
      I4 => sel0(0),
      I5 => \ADC_CR_reg_n_0_[8]\,
      O => \axi_rdata[8]_i_5_n_0\
    );
\axi_rdata[9]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => \axi_rdata[9]_i_2_n_0\,
      I1 => \axi_rdata[9]_i_3_n_0\,
      I2 => sel0(3),
      I3 => \axi_rdata[9]_i_4_n_0\,
      I4 => sel0(2),
      I5 => \axi_rdata[9]_i_5_n_0\,
      O => reg_data_out(9)
    );
\axi_rdata[9]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => slv_reg15(9),
      I1 => slv_reg14(9),
      I2 => sel0(1),
      I3 => slv_reg13(9),
      I4 => sel0(0),
      I5 => slv_reg12(9),
      O => \axi_rdata[9]_i_2_n_0\
    );
\axi_rdata[9]_i_3\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => slv_reg11(9),
      I1 => slv_reg10(9),
      I2 => sel0(1),
      I3 => \ADC_AVAILABLE_reg_n_0_[9]\,
      I4 => sel0(0),
      I5 => \^adc_conv_value_reg[30]_0\(9),
      O => \axi_rdata[9]_i_3_n_0\
    );
\axi_rdata[9]_i_4\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"04"
    )
        port map (
      I0 => sel0(0),
      I1 => S_ADC_CHANNEL(9),
      I2 => sel0(1),
      O => \axi_rdata[9]_i_4_n_0\
    );
\axi_rdata[9]_i_5\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => \ADC_MASTER_CHANNEL_reg_n_0_[9]\,
      I1 => \^q\(9),
      I2 => sel0(1),
      I3 => \ADC_SPI_CR_reg_n_0_[9]\,
      I4 => sel0(0),
      I5 => \ADC_CR_reg_n_0_[9]\,
      O => \axi_rdata[9]_i_5_n_0\
    );
\axi_rdata_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => slv_reg_rden,
      D => reg_data_out(0),
      Q => s00_axi_rdata(0),
      R => \^rstp\
    );
\axi_rdata_reg[0]_i_1\: unisim.vcomponents.MUXF8
     port map (
      I0 => \axi_rdata_reg[0]_i_2_n_0\,
      I1 => \axi_rdata_reg[0]_i_3_n_0\,
      O => reg_data_out(0),
      S => sel0(3)
    );
\axi_rdata_reg[0]_i_2\: unisim.vcomponents.MUXF7
     port map (
      I0 => \axi_rdata[0]_i_4_n_0\,
      I1 => \axi_rdata[0]_i_5_n_0\,
      O => \axi_rdata_reg[0]_i_2_n_0\,
      S => sel0(2)
    );
\axi_rdata_reg[0]_i_3\: unisim.vcomponents.MUXF7
     port map (
      I0 => \axi_rdata[0]_i_6_n_0\,
      I1 => \axi_rdata[0]_i_7_n_0\,
      O => \axi_rdata_reg[0]_i_3_n_0\,
      S => sel0(2)
    );
\axi_rdata_reg[10]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => slv_reg_rden,
      D => reg_data_out(10),
      Q => s00_axi_rdata(10),
      R => \^rstp\
    );
\axi_rdata_reg[11]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => slv_reg_rden,
      D => reg_data_out(11),
      Q => s00_axi_rdata(11),
      R => \^rstp\
    );
\axi_rdata_reg[12]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => slv_reg_rden,
      D => reg_data_out(12),
      Q => s00_axi_rdata(12),
      R => \^rstp\
    );
\axi_rdata_reg[13]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => slv_reg_rden,
      D => reg_data_out(13),
      Q => s00_axi_rdata(13),
      R => \^rstp\
    );
\axi_rdata_reg[14]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => slv_reg_rden,
      D => reg_data_out(14),
      Q => s00_axi_rdata(14),
      R => \^rstp\
    );
\axi_rdata_reg[15]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => slv_reg_rden,
      D => reg_data_out(15),
      Q => s00_axi_rdata(15),
      R => \^rstp\
    );
\axi_rdata_reg[16]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => slv_reg_rden,
      D => reg_data_out(16),
      Q => s00_axi_rdata(16),
      R => \^rstp\
    );
\axi_rdata_reg[17]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => slv_reg_rden,
      D => reg_data_out(17),
      Q => s00_axi_rdata(17),
      R => \^rstp\
    );
\axi_rdata_reg[18]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => slv_reg_rden,
      D => reg_data_out(18),
      Q => s00_axi_rdata(18),
      R => \^rstp\
    );
\axi_rdata_reg[19]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => slv_reg_rden,
      D => reg_data_out(19),
      Q => s00_axi_rdata(19),
      R => \^rstp\
    );
\axi_rdata_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => slv_reg_rden,
      D => reg_data_out(1),
      Q => s00_axi_rdata(1),
      R => \^rstp\
    );
\axi_rdata_reg[20]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => slv_reg_rden,
      D => reg_data_out(20),
      Q => s00_axi_rdata(20),
      R => \^rstp\
    );
\axi_rdata_reg[21]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => slv_reg_rden,
      D => reg_data_out(21),
      Q => s00_axi_rdata(21),
      R => \^rstp\
    );
\axi_rdata_reg[22]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => slv_reg_rden,
      D => reg_data_out(22),
      Q => s00_axi_rdata(22),
      R => \^rstp\
    );
\axi_rdata_reg[23]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => slv_reg_rden,
      D => reg_data_out(23),
      Q => s00_axi_rdata(23),
      R => \^rstp\
    );
\axi_rdata_reg[24]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => slv_reg_rden,
      D => reg_data_out(24),
      Q => s00_axi_rdata(24),
      R => \^rstp\
    );
\axi_rdata_reg[25]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => slv_reg_rden,
      D => reg_data_out(25),
      Q => s00_axi_rdata(25),
      R => \^rstp\
    );
\axi_rdata_reg[26]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => slv_reg_rden,
      D => reg_data_out(26),
      Q => s00_axi_rdata(26),
      R => \^rstp\
    );
\axi_rdata_reg[27]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => slv_reg_rden,
      D => reg_data_out(27),
      Q => s00_axi_rdata(27),
      R => \^rstp\
    );
\axi_rdata_reg[28]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => slv_reg_rden,
      D => reg_data_out(28),
      Q => s00_axi_rdata(28),
      R => \^rstp\
    );
\axi_rdata_reg[29]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => slv_reg_rden,
      D => reg_data_out(29),
      Q => s00_axi_rdata(29),
      R => \^rstp\
    );
\axi_rdata_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => slv_reg_rden,
      D => reg_data_out(2),
      Q => s00_axi_rdata(2),
      R => \^rstp\
    );
\axi_rdata_reg[30]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => slv_reg_rden,
      D => reg_data_out(30),
      Q => s00_axi_rdata(30),
      R => \^rstp\
    );
\axi_rdata_reg[31]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => slv_reg_rden,
      D => reg_data_out(31),
      Q => s00_axi_rdata(31),
      R => \^rstp\
    );
\axi_rdata_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => slv_reg_rden,
      D => reg_data_out(3),
      Q => s00_axi_rdata(3),
      R => \^rstp\
    );
\axi_rdata_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => slv_reg_rden,
      D => reg_data_out(4),
      Q => s00_axi_rdata(4),
      R => \^rstp\
    );
\axi_rdata_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => slv_reg_rden,
      D => reg_data_out(5),
      Q => s00_axi_rdata(5),
      R => \^rstp\
    );
\axi_rdata_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => slv_reg_rden,
      D => reg_data_out(6),
      Q => s00_axi_rdata(6),
      R => \^rstp\
    );
\axi_rdata_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => slv_reg_rden,
      D => reg_data_out(7),
      Q => s00_axi_rdata(7),
      R => \^rstp\
    );
\axi_rdata_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => slv_reg_rden,
      D => reg_data_out(8),
      Q => s00_axi_rdata(8),
      R => \^rstp\
    );
\axi_rdata_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => slv_reg_rden,
      D => reg_data_out(9),
      Q => s00_axi_rdata(9),
      R => \^rstp\
    );
axi_rvalid_i_1: unisim.vcomponents.LUT4
    generic map(
      INIT => X"08F8"
    )
        port map (
      I0 => \^axi_arready_reg_0\,
      I1 => s00_axi_arvalid,
      I2 => \^s00_axi_rvalid\,
      I3 => s00_axi_rready,
      O => axi_rvalid_i_1_n_0
    );
axi_rvalid_reg: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => '1',
      D => axi_rvalid_i_1_n_0,
      Q => \^s00_axi_rvalid\,
      R => \^rstp\
    );
axi_wready_i_1: unisim.vcomponents.LUT4
    generic map(
      INIT => X"0800"
    )
        port map (
      I0 => s00_axi_wvalid,
      I1 => s00_axi_awvalid,
      I2 => \^axi_wready_reg_0\,
      I3 => aw_en_reg_n_0,
      O => axi_wready0
    );
axi_wready_reg: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => '1',
      D => axi_wready0,
      Q => \^axi_wready_reg_0\,
      R => \^rstp\
    );
\curstate[0]_i_1__1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"3020202070707070"
    )
        port map (
      I0 => \curstate_reg[0]\(0),
      I1 => \curstate_reg[0]\(1),
      I2 => S_ADC_CR(0),
      I3 => S_ADC_MASTER_CHANNEL,
      I4 => BUSY,
      I5 => p_0_in13_in,
      O => \^nxtstate\(0)
    );
\curstate[1]_i_1__0\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"0000F070"
    )
        port map (
      I0 => S_ADC_MASTER_CHANNEL,
      I1 => BUSY,
      I2 => p_0_in13_in,
      I3 => \curstate_reg[0]\(1),
      I4 => \curstate_reg[0]\(0),
      O => \^nxtstate\(1)
    );
\slv_reg10[15]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0000000000008000"
    )
        port map (
      I0 => \slv_reg_wren__0\,
      I1 => p_0_in(3),
      I2 => s00_axi_wstrb(1),
      I3 => p_0_in(1),
      I4 => p_0_in(0),
      I5 => p_0_in(2),
      O => \slv_reg10[15]_i_1_n_0\
    );
\slv_reg10[23]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0000000000008000"
    )
        port map (
      I0 => \slv_reg_wren__0\,
      I1 => p_0_in(3),
      I2 => s00_axi_wstrb(2),
      I3 => p_0_in(1),
      I4 => p_0_in(0),
      I5 => p_0_in(2),
      O => \slv_reg10[23]_i_1_n_0\
    );
\slv_reg10[31]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0000000000008000"
    )
        port map (
      I0 => \slv_reg_wren__0\,
      I1 => p_0_in(3),
      I2 => s00_axi_wstrb(3),
      I3 => p_0_in(1),
      I4 => p_0_in(0),
      I5 => p_0_in(2),
      O => \slv_reg10[31]_i_1_n_0\
    );
\slv_reg10[7]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0000000000008000"
    )
        port map (
      I0 => \slv_reg_wren__0\,
      I1 => p_0_in(3),
      I2 => s00_axi_wstrb(0),
      I3 => p_0_in(1),
      I4 => p_0_in(0),
      I5 => p_0_in(2),
      O => \slv_reg10[7]_i_1_n_0\
    );
\slv_reg10_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg10[7]_i_1_n_0\,
      D => s00_axi_wdata(0),
      Q => slv_reg10(0),
      R => \^rstp\
    );
\slv_reg10_reg[10]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg10[15]_i_1_n_0\,
      D => s00_axi_wdata(10),
      Q => slv_reg10(10),
      R => \^rstp\
    );
\slv_reg10_reg[11]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg10[15]_i_1_n_0\,
      D => s00_axi_wdata(11),
      Q => slv_reg10(11),
      R => \^rstp\
    );
\slv_reg10_reg[12]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg10[15]_i_1_n_0\,
      D => s00_axi_wdata(12),
      Q => slv_reg10(12),
      R => \^rstp\
    );
\slv_reg10_reg[13]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg10[15]_i_1_n_0\,
      D => s00_axi_wdata(13),
      Q => slv_reg10(13),
      R => \^rstp\
    );
\slv_reg10_reg[14]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg10[15]_i_1_n_0\,
      D => s00_axi_wdata(14),
      Q => slv_reg10(14),
      R => \^rstp\
    );
\slv_reg10_reg[15]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg10[15]_i_1_n_0\,
      D => s00_axi_wdata(15),
      Q => slv_reg10(15),
      R => \^rstp\
    );
\slv_reg10_reg[16]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg10[23]_i_1_n_0\,
      D => s00_axi_wdata(16),
      Q => slv_reg10(16),
      R => \^rstp\
    );
\slv_reg10_reg[17]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg10[23]_i_1_n_0\,
      D => s00_axi_wdata(17),
      Q => slv_reg10(17),
      R => \^rstp\
    );
\slv_reg10_reg[18]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg10[23]_i_1_n_0\,
      D => s00_axi_wdata(18),
      Q => slv_reg10(18),
      R => \^rstp\
    );
\slv_reg10_reg[19]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg10[23]_i_1_n_0\,
      D => s00_axi_wdata(19),
      Q => slv_reg10(19),
      R => \^rstp\
    );
\slv_reg10_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg10[7]_i_1_n_0\,
      D => s00_axi_wdata(1),
      Q => slv_reg10(1),
      R => \^rstp\
    );
\slv_reg10_reg[20]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg10[23]_i_1_n_0\,
      D => s00_axi_wdata(20),
      Q => slv_reg10(20),
      R => \^rstp\
    );
\slv_reg10_reg[21]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg10[23]_i_1_n_0\,
      D => s00_axi_wdata(21),
      Q => slv_reg10(21),
      R => \^rstp\
    );
\slv_reg10_reg[22]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg10[23]_i_1_n_0\,
      D => s00_axi_wdata(22),
      Q => slv_reg10(22),
      R => \^rstp\
    );
\slv_reg10_reg[23]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg10[23]_i_1_n_0\,
      D => s00_axi_wdata(23),
      Q => slv_reg10(23),
      R => \^rstp\
    );
\slv_reg10_reg[24]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg10[31]_i_1_n_0\,
      D => s00_axi_wdata(24),
      Q => slv_reg10(24),
      R => \^rstp\
    );
\slv_reg10_reg[25]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg10[31]_i_1_n_0\,
      D => s00_axi_wdata(25),
      Q => slv_reg10(25),
      R => \^rstp\
    );
\slv_reg10_reg[26]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg10[31]_i_1_n_0\,
      D => s00_axi_wdata(26),
      Q => slv_reg10(26),
      R => \^rstp\
    );
\slv_reg10_reg[27]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg10[31]_i_1_n_0\,
      D => s00_axi_wdata(27),
      Q => slv_reg10(27),
      R => \^rstp\
    );
\slv_reg10_reg[28]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg10[31]_i_1_n_0\,
      D => s00_axi_wdata(28),
      Q => slv_reg10(28),
      R => \^rstp\
    );
\slv_reg10_reg[29]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg10[31]_i_1_n_0\,
      D => s00_axi_wdata(29),
      Q => slv_reg10(29),
      R => \^rstp\
    );
\slv_reg10_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg10[7]_i_1_n_0\,
      D => s00_axi_wdata(2),
      Q => slv_reg10(2),
      R => \^rstp\
    );
\slv_reg10_reg[30]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg10[31]_i_1_n_0\,
      D => s00_axi_wdata(30),
      Q => slv_reg10(30),
      R => \^rstp\
    );
\slv_reg10_reg[31]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg10[31]_i_1_n_0\,
      D => s00_axi_wdata(31),
      Q => slv_reg10(31),
      R => \^rstp\
    );
\slv_reg10_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg10[7]_i_1_n_0\,
      D => s00_axi_wdata(3),
      Q => slv_reg10(3),
      R => \^rstp\
    );
\slv_reg10_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg10[7]_i_1_n_0\,
      D => s00_axi_wdata(4),
      Q => slv_reg10(4),
      R => \^rstp\
    );
\slv_reg10_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg10[7]_i_1_n_0\,
      D => s00_axi_wdata(5),
      Q => slv_reg10(5),
      R => \^rstp\
    );
\slv_reg10_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg10[7]_i_1_n_0\,
      D => s00_axi_wdata(6),
      Q => slv_reg10(6),
      R => \^rstp\
    );
\slv_reg10_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg10[7]_i_1_n_0\,
      D => s00_axi_wdata(7),
      Q => slv_reg10(7),
      R => \^rstp\
    );
\slv_reg10_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg10[15]_i_1_n_0\,
      D => s00_axi_wdata(8),
      Q => slv_reg10(8),
      R => \^rstp\
    );
\slv_reg10_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg10[15]_i_1_n_0\,
      D => s00_axi_wdata(9),
      Q => slv_reg10(9),
      R => \^rstp\
    );
\slv_reg11[15]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0000000080000000"
    )
        port map (
      I0 => \slv_reg_wren__0\,
      I1 => s00_axi_wstrb(1),
      I2 => p_0_in(3),
      I3 => p_0_in(0),
      I4 => p_0_in(1),
      I5 => p_0_in(2),
      O => \slv_reg11[15]_i_1_n_0\
    );
\slv_reg11[23]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0000000080000000"
    )
        port map (
      I0 => \slv_reg_wren__0\,
      I1 => s00_axi_wstrb(2),
      I2 => p_0_in(3),
      I3 => p_0_in(0),
      I4 => p_0_in(1),
      I5 => p_0_in(2),
      O => \slv_reg11[23]_i_1_n_0\
    );
\slv_reg11[31]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0000000080000000"
    )
        port map (
      I0 => \slv_reg_wren__0\,
      I1 => s00_axi_wstrb(3),
      I2 => p_0_in(3),
      I3 => p_0_in(0),
      I4 => p_0_in(1),
      I5 => p_0_in(2),
      O => \slv_reg11[31]_i_1_n_0\
    );
\slv_reg11[7]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0000000080000000"
    )
        port map (
      I0 => \slv_reg_wren__0\,
      I1 => s00_axi_wstrb(0),
      I2 => p_0_in(3),
      I3 => p_0_in(0),
      I4 => p_0_in(1),
      I5 => p_0_in(2),
      O => \slv_reg11[7]_i_1_n_0\
    );
\slv_reg11_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg11[7]_i_1_n_0\,
      D => s00_axi_wdata(0),
      Q => slv_reg11(0),
      R => \^rstp\
    );
\slv_reg11_reg[10]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg11[15]_i_1_n_0\,
      D => s00_axi_wdata(10),
      Q => slv_reg11(10),
      R => \^rstp\
    );
\slv_reg11_reg[11]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg11[15]_i_1_n_0\,
      D => s00_axi_wdata(11),
      Q => slv_reg11(11),
      R => \^rstp\
    );
\slv_reg11_reg[12]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg11[15]_i_1_n_0\,
      D => s00_axi_wdata(12),
      Q => slv_reg11(12),
      R => \^rstp\
    );
\slv_reg11_reg[13]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg11[15]_i_1_n_0\,
      D => s00_axi_wdata(13),
      Q => slv_reg11(13),
      R => \^rstp\
    );
\slv_reg11_reg[14]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg11[15]_i_1_n_0\,
      D => s00_axi_wdata(14),
      Q => slv_reg11(14),
      R => \^rstp\
    );
\slv_reg11_reg[15]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg11[15]_i_1_n_0\,
      D => s00_axi_wdata(15),
      Q => slv_reg11(15),
      R => \^rstp\
    );
\slv_reg11_reg[16]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg11[23]_i_1_n_0\,
      D => s00_axi_wdata(16),
      Q => slv_reg11(16),
      R => \^rstp\
    );
\slv_reg11_reg[17]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg11[23]_i_1_n_0\,
      D => s00_axi_wdata(17),
      Q => slv_reg11(17),
      R => \^rstp\
    );
\slv_reg11_reg[18]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg11[23]_i_1_n_0\,
      D => s00_axi_wdata(18),
      Q => slv_reg11(18),
      R => \^rstp\
    );
\slv_reg11_reg[19]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg11[23]_i_1_n_0\,
      D => s00_axi_wdata(19),
      Q => slv_reg11(19),
      R => \^rstp\
    );
\slv_reg11_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg11[7]_i_1_n_0\,
      D => s00_axi_wdata(1),
      Q => slv_reg11(1),
      R => \^rstp\
    );
\slv_reg11_reg[20]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg11[23]_i_1_n_0\,
      D => s00_axi_wdata(20),
      Q => slv_reg11(20),
      R => \^rstp\
    );
\slv_reg11_reg[21]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg11[23]_i_1_n_0\,
      D => s00_axi_wdata(21),
      Q => slv_reg11(21),
      R => \^rstp\
    );
\slv_reg11_reg[22]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg11[23]_i_1_n_0\,
      D => s00_axi_wdata(22),
      Q => slv_reg11(22),
      R => \^rstp\
    );
\slv_reg11_reg[23]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg11[23]_i_1_n_0\,
      D => s00_axi_wdata(23),
      Q => slv_reg11(23),
      R => \^rstp\
    );
\slv_reg11_reg[24]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg11[31]_i_1_n_0\,
      D => s00_axi_wdata(24),
      Q => slv_reg11(24),
      R => \^rstp\
    );
\slv_reg11_reg[25]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg11[31]_i_1_n_0\,
      D => s00_axi_wdata(25),
      Q => slv_reg11(25),
      R => \^rstp\
    );
\slv_reg11_reg[26]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg11[31]_i_1_n_0\,
      D => s00_axi_wdata(26),
      Q => slv_reg11(26),
      R => \^rstp\
    );
\slv_reg11_reg[27]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg11[31]_i_1_n_0\,
      D => s00_axi_wdata(27),
      Q => slv_reg11(27),
      R => \^rstp\
    );
\slv_reg11_reg[28]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg11[31]_i_1_n_0\,
      D => s00_axi_wdata(28),
      Q => slv_reg11(28),
      R => \^rstp\
    );
\slv_reg11_reg[29]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg11[31]_i_1_n_0\,
      D => s00_axi_wdata(29),
      Q => slv_reg11(29),
      R => \^rstp\
    );
\slv_reg11_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg11[7]_i_1_n_0\,
      D => s00_axi_wdata(2),
      Q => slv_reg11(2),
      R => \^rstp\
    );
\slv_reg11_reg[30]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg11[31]_i_1_n_0\,
      D => s00_axi_wdata(30),
      Q => slv_reg11(30),
      R => \^rstp\
    );
\slv_reg11_reg[31]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg11[31]_i_1_n_0\,
      D => s00_axi_wdata(31),
      Q => slv_reg11(31),
      R => \^rstp\
    );
\slv_reg11_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg11[7]_i_1_n_0\,
      D => s00_axi_wdata(3),
      Q => slv_reg11(3),
      R => \^rstp\
    );
\slv_reg11_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg11[7]_i_1_n_0\,
      D => s00_axi_wdata(4),
      Q => slv_reg11(4),
      R => \^rstp\
    );
\slv_reg11_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg11[7]_i_1_n_0\,
      D => s00_axi_wdata(5),
      Q => slv_reg11(5),
      R => \^rstp\
    );
\slv_reg11_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg11[7]_i_1_n_0\,
      D => s00_axi_wdata(6),
      Q => slv_reg11(6),
      R => \^rstp\
    );
\slv_reg11_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg11[7]_i_1_n_0\,
      D => s00_axi_wdata(7),
      Q => slv_reg11(7),
      R => \^rstp\
    );
\slv_reg11_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg11[15]_i_1_n_0\,
      D => s00_axi_wdata(8),
      Q => slv_reg11(8),
      R => \^rstp\
    );
\slv_reg11_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg11[15]_i_1_n_0\,
      D => s00_axi_wdata(9),
      Q => slv_reg11(9),
      R => \^rstp\
    );
\slv_reg12[15]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0000000000008000"
    )
        port map (
      I0 => \slv_reg_wren__0\,
      I1 => p_0_in(3),
      I2 => s00_axi_wstrb(1),
      I3 => p_0_in(2),
      I4 => p_0_in(0),
      I5 => p_0_in(1),
      O => \slv_reg12[15]_i_1_n_0\
    );
\slv_reg12[23]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0000000000008000"
    )
        port map (
      I0 => \slv_reg_wren__0\,
      I1 => p_0_in(3),
      I2 => s00_axi_wstrb(2),
      I3 => p_0_in(2),
      I4 => p_0_in(0),
      I5 => p_0_in(1),
      O => \slv_reg12[23]_i_1_n_0\
    );
\slv_reg12[31]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0000000000008000"
    )
        port map (
      I0 => \slv_reg_wren__0\,
      I1 => p_0_in(3),
      I2 => s00_axi_wstrb(3),
      I3 => p_0_in(2),
      I4 => p_0_in(0),
      I5 => p_0_in(1),
      O => \slv_reg12[31]_i_1_n_0\
    );
\slv_reg12[7]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0000000000008000"
    )
        port map (
      I0 => \slv_reg_wren__0\,
      I1 => p_0_in(3),
      I2 => s00_axi_wstrb(0),
      I3 => p_0_in(2),
      I4 => p_0_in(0),
      I5 => p_0_in(1),
      O => \slv_reg12[7]_i_1_n_0\
    );
\slv_reg12_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg12[7]_i_1_n_0\,
      D => s00_axi_wdata(0),
      Q => slv_reg12(0),
      R => \^rstp\
    );
\slv_reg12_reg[10]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg12[15]_i_1_n_0\,
      D => s00_axi_wdata(10),
      Q => slv_reg12(10),
      R => \^rstp\
    );
\slv_reg12_reg[11]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg12[15]_i_1_n_0\,
      D => s00_axi_wdata(11),
      Q => slv_reg12(11),
      R => \^rstp\
    );
\slv_reg12_reg[12]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg12[15]_i_1_n_0\,
      D => s00_axi_wdata(12),
      Q => slv_reg12(12),
      R => \^rstp\
    );
\slv_reg12_reg[13]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg12[15]_i_1_n_0\,
      D => s00_axi_wdata(13),
      Q => slv_reg12(13),
      R => \^rstp\
    );
\slv_reg12_reg[14]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg12[15]_i_1_n_0\,
      D => s00_axi_wdata(14),
      Q => slv_reg12(14),
      R => \^rstp\
    );
\slv_reg12_reg[15]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg12[15]_i_1_n_0\,
      D => s00_axi_wdata(15),
      Q => slv_reg12(15),
      R => \^rstp\
    );
\slv_reg12_reg[16]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg12[23]_i_1_n_0\,
      D => s00_axi_wdata(16),
      Q => slv_reg12(16),
      R => \^rstp\
    );
\slv_reg12_reg[17]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg12[23]_i_1_n_0\,
      D => s00_axi_wdata(17),
      Q => slv_reg12(17),
      R => \^rstp\
    );
\slv_reg12_reg[18]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg12[23]_i_1_n_0\,
      D => s00_axi_wdata(18),
      Q => slv_reg12(18),
      R => \^rstp\
    );
\slv_reg12_reg[19]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg12[23]_i_1_n_0\,
      D => s00_axi_wdata(19),
      Q => slv_reg12(19),
      R => \^rstp\
    );
\slv_reg12_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg12[7]_i_1_n_0\,
      D => s00_axi_wdata(1),
      Q => slv_reg12(1),
      R => \^rstp\
    );
\slv_reg12_reg[20]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg12[23]_i_1_n_0\,
      D => s00_axi_wdata(20),
      Q => slv_reg12(20),
      R => \^rstp\
    );
\slv_reg12_reg[21]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg12[23]_i_1_n_0\,
      D => s00_axi_wdata(21),
      Q => slv_reg12(21),
      R => \^rstp\
    );
\slv_reg12_reg[22]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg12[23]_i_1_n_0\,
      D => s00_axi_wdata(22),
      Q => slv_reg12(22),
      R => \^rstp\
    );
\slv_reg12_reg[23]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg12[23]_i_1_n_0\,
      D => s00_axi_wdata(23),
      Q => slv_reg12(23),
      R => \^rstp\
    );
\slv_reg12_reg[24]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg12[31]_i_1_n_0\,
      D => s00_axi_wdata(24),
      Q => slv_reg12(24),
      R => \^rstp\
    );
\slv_reg12_reg[25]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg12[31]_i_1_n_0\,
      D => s00_axi_wdata(25),
      Q => slv_reg12(25),
      R => \^rstp\
    );
\slv_reg12_reg[26]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg12[31]_i_1_n_0\,
      D => s00_axi_wdata(26),
      Q => slv_reg12(26),
      R => \^rstp\
    );
\slv_reg12_reg[27]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg12[31]_i_1_n_0\,
      D => s00_axi_wdata(27),
      Q => slv_reg12(27),
      R => \^rstp\
    );
\slv_reg12_reg[28]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg12[31]_i_1_n_0\,
      D => s00_axi_wdata(28),
      Q => slv_reg12(28),
      R => \^rstp\
    );
\slv_reg12_reg[29]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg12[31]_i_1_n_0\,
      D => s00_axi_wdata(29),
      Q => slv_reg12(29),
      R => \^rstp\
    );
\slv_reg12_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg12[7]_i_1_n_0\,
      D => s00_axi_wdata(2),
      Q => slv_reg12(2),
      R => \^rstp\
    );
\slv_reg12_reg[30]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg12[31]_i_1_n_0\,
      D => s00_axi_wdata(30),
      Q => slv_reg12(30),
      R => \^rstp\
    );
\slv_reg12_reg[31]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg12[31]_i_1_n_0\,
      D => s00_axi_wdata(31),
      Q => slv_reg12(31),
      R => \^rstp\
    );
\slv_reg12_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg12[7]_i_1_n_0\,
      D => s00_axi_wdata(3),
      Q => slv_reg12(3),
      R => \^rstp\
    );
\slv_reg12_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg12[7]_i_1_n_0\,
      D => s00_axi_wdata(4),
      Q => slv_reg12(4),
      R => \^rstp\
    );
\slv_reg12_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg12[7]_i_1_n_0\,
      D => s00_axi_wdata(5),
      Q => slv_reg12(5),
      R => \^rstp\
    );
\slv_reg12_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg12[7]_i_1_n_0\,
      D => s00_axi_wdata(6),
      Q => slv_reg12(6),
      R => \^rstp\
    );
\slv_reg12_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg12[7]_i_1_n_0\,
      D => s00_axi_wdata(7),
      Q => slv_reg12(7),
      R => \^rstp\
    );
\slv_reg12_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg12[15]_i_1_n_0\,
      D => s00_axi_wdata(8),
      Q => slv_reg12(8),
      R => \^rstp\
    );
\slv_reg12_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg12[15]_i_1_n_0\,
      D => s00_axi_wdata(9),
      Q => slv_reg12(9),
      R => \^rstp\
    );
\slv_reg13[15]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0000000080000000"
    )
        port map (
      I0 => \slv_reg_wren__0\,
      I1 => p_0_in(2),
      I2 => p_0_in(3),
      I3 => p_0_in(0),
      I4 => s00_axi_wstrb(1),
      I5 => p_0_in(1),
      O => \slv_reg13[15]_i_1_n_0\
    );
\slv_reg13[23]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0000000080000000"
    )
        port map (
      I0 => \slv_reg_wren__0\,
      I1 => p_0_in(2),
      I2 => p_0_in(3),
      I3 => p_0_in(0),
      I4 => s00_axi_wstrb(2),
      I5 => p_0_in(1),
      O => \slv_reg13[23]_i_1_n_0\
    );
\slv_reg13[31]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0000000080000000"
    )
        port map (
      I0 => \slv_reg_wren__0\,
      I1 => p_0_in(2),
      I2 => p_0_in(3),
      I3 => p_0_in(0),
      I4 => s00_axi_wstrb(3),
      I5 => p_0_in(1),
      O => \slv_reg13[31]_i_1_n_0\
    );
\slv_reg13[7]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0000000080000000"
    )
        port map (
      I0 => \slv_reg_wren__0\,
      I1 => p_0_in(2),
      I2 => p_0_in(3),
      I3 => p_0_in(0),
      I4 => s00_axi_wstrb(0),
      I5 => p_0_in(1),
      O => \slv_reg13[7]_i_1_n_0\
    );
\slv_reg13_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg13[7]_i_1_n_0\,
      D => s00_axi_wdata(0),
      Q => slv_reg13(0),
      R => \^rstp\
    );
\slv_reg13_reg[10]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg13[15]_i_1_n_0\,
      D => s00_axi_wdata(10),
      Q => slv_reg13(10),
      R => \^rstp\
    );
\slv_reg13_reg[11]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg13[15]_i_1_n_0\,
      D => s00_axi_wdata(11),
      Q => slv_reg13(11),
      R => \^rstp\
    );
\slv_reg13_reg[12]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg13[15]_i_1_n_0\,
      D => s00_axi_wdata(12),
      Q => slv_reg13(12),
      R => \^rstp\
    );
\slv_reg13_reg[13]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg13[15]_i_1_n_0\,
      D => s00_axi_wdata(13),
      Q => slv_reg13(13),
      R => \^rstp\
    );
\slv_reg13_reg[14]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg13[15]_i_1_n_0\,
      D => s00_axi_wdata(14),
      Q => slv_reg13(14),
      R => \^rstp\
    );
\slv_reg13_reg[15]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg13[15]_i_1_n_0\,
      D => s00_axi_wdata(15),
      Q => slv_reg13(15),
      R => \^rstp\
    );
\slv_reg13_reg[16]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg13[23]_i_1_n_0\,
      D => s00_axi_wdata(16),
      Q => slv_reg13(16),
      R => \^rstp\
    );
\slv_reg13_reg[17]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg13[23]_i_1_n_0\,
      D => s00_axi_wdata(17),
      Q => slv_reg13(17),
      R => \^rstp\
    );
\slv_reg13_reg[18]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg13[23]_i_1_n_0\,
      D => s00_axi_wdata(18),
      Q => slv_reg13(18),
      R => \^rstp\
    );
\slv_reg13_reg[19]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg13[23]_i_1_n_0\,
      D => s00_axi_wdata(19),
      Q => slv_reg13(19),
      R => \^rstp\
    );
\slv_reg13_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg13[7]_i_1_n_0\,
      D => s00_axi_wdata(1),
      Q => slv_reg13(1),
      R => \^rstp\
    );
\slv_reg13_reg[20]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg13[23]_i_1_n_0\,
      D => s00_axi_wdata(20),
      Q => slv_reg13(20),
      R => \^rstp\
    );
\slv_reg13_reg[21]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg13[23]_i_1_n_0\,
      D => s00_axi_wdata(21),
      Q => slv_reg13(21),
      R => \^rstp\
    );
\slv_reg13_reg[22]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg13[23]_i_1_n_0\,
      D => s00_axi_wdata(22),
      Q => slv_reg13(22),
      R => \^rstp\
    );
\slv_reg13_reg[23]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg13[23]_i_1_n_0\,
      D => s00_axi_wdata(23),
      Q => slv_reg13(23),
      R => \^rstp\
    );
\slv_reg13_reg[24]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg13[31]_i_1_n_0\,
      D => s00_axi_wdata(24),
      Q => slv_reg13(24),
      R => \^rstp\
    );
\slv_reg13_reg[25]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg13[31]_i_1_n_0\,
      D => s00_axi_wdata(25),
      Q => slv_reg13(25),
      R => \^rstp\
    );
\slv_reg13_reg[26]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg13[31]_i_1_n_0\,
      D => s00_axi_wdata(26),
      Q => slv_reg13(26),
      R => \^rstp\
    );
\slv_reg13_reg[27]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg13[31]_i_1_n_0\,
      D => s00_axi_wdata(27),
      Q => slv_reg13(27),
      R => \^rstp\
    );
\slv_reg13_reg[28]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg13[31]_i_1_n_0\,
      D => s00_axi_wdata(28),
      Q => slv_reg13(28),
      R => \^rstp\
    );
\slv_reg13_reg[29]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg13[31]_i_1_n_0\,
      D => s00_axi_wdata(29),
      Q => slv_reg13(29),
      R => \^rstp\
    );
\slv_reg13_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg13[7]_i_1_n_0\,
      D => s00_axi_wdata(2),
      Q => slv_reg13(2),
      R => \^rstp\
    );
\slv_reg13_reg[30]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg13[31]_i_1_n_0\,
      D => s00_axi_wdata(30),
      Q => slv_reg13(30),
      R => \^rstp\
    );
\slv_reg13_reg[31]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg13[31]_i_1_n_0\,
      D => s00_axi_wdata(31),
      Q => slv_reg13(31),
      R => \^rstp\
    );
\slv_reg13_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg13[7]_i_1_n_0\,
      D => s00_axi_wdata(3),
      Q => slv_reg13(3),
      R => \^rstp\
    );
\slv_reg13_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg13[7]_i_1_n_0\,
      D => s00_axi_wdata(4),
      Q => slv_reg13(4),
      R => \^rstp\
    );
\slv_reg13_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg13[7]_i_1_n_0\,
      D => s00_axi_wdata(5),
      Q => slv_reg13(5),
      R => \^rstp\
    );
\slv_reg13_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg13[7]_i_1_n_0\,
      D => s00_axi_wdata(6),
      Q => slv_reg13(6),
      R => \^rstp\
    );
\slv_reg13_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg13[7]_i_1_n_0\,
      D => s00_axi_wdata(7),
      Q => slv_reg13(7),
      R => \^rstp\
    );
\slv_reg13_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg13[15]_i_1_n_0\,
      D => s00_axi_wdata(8),
      Q => slv_reg13(8),
      R => \^rstp\
    );
\slv_reg13_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg13[15]_i_1_n_0\,
      D => s00_axi_wdata(9),
      Q => slv_reg13(9),
      R => \^rstp\
    );
\slv_reg14[15]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0000000080000000"
    )
        port map (
      I0 => \slv_reg_wren__0\,
      I1 => p_0_in(2),
      I2 => p_0_in(3),
      I3 => s00_axi_wstrb(1),
      I4 => p_0_in(1),
      I5 => p_0_in(0),
      O => \slv_reg14[15]_i_1_n_0\
    );
\slv_reg14[23]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0000000080000000"
    )
        port map (
      I0 => \slv_reg_wren__0\,
      I1 => p_0_in(2),
      I2 => p_0_in(3),
      I3 => s00_axi_wstrb(2),
      I4 => p_0_in(1),
      I5 => p_0_in(0),
      O => \slv_reg14[23]_i_1_n_0\
    );
\slv_reg14[31]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0000000080000000"
    )
        port map (
      I0 => \slv_reg_wren__0\,
      I1 => p_0_in(2),
      I2 => p_0_in(3),
      I3 => s00_axi_wstrb(3),
      I4 => p_0_in(1),
      I5 => p_0_in(0),
      O => \slv_reg14[31]_i_1_n_0\
    );
\slv_reg14[7]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0000000080000000"
    )
        port map (
      I0 => \slv_reg_wren__0\,
      I1 => p_0_in(2),
      I2 => p_0_in(3),
      I3 => s00_axi_wstrb(0),
      I4 => p_0_in(1),
      I5 => p_0_in(0),
      O => \slv_reg14[7]_i_1_n_0\
    );
\slv_reg14_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg14[7]_i_1_n_0\,
      D => s00_axi_wdata(0),
      Q => slv_reg14(0),
      R => \^rstp\
    );
\slv_reg14_reg[10]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg14[15]_i_1_n_0\,
      D => s00_axi_wdata(10),
      Q => slv_reg14(10),
      R => \^rstp\
    );
\slv_reg14_reg[11]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg14[15]_i_1_n_0\,
      D => s00_axi_wdata(11),
      Q => slv_reg14(11),
      R => \^rstp\
    );
\slv_reg14_reg[12]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg14[15]_i_1_n_0\,
      D => s00_axi_wdata(12),
      Q => slv_reg14(12),
      R => \^rstp\
    );
\slv_reg14_reg[13]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg14[15]_i_1_n_0\,
      D => s00_axi_wdata(13),
      Q => slv_reg14(13),
      R => \^rstp\
    );
\slv_reg14_reg[14]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg14[15]_i_1_n_0\,
      D => s00_axi_wdata(14),
      Q => slv_reg14(14),
      R => \^rstp\
    );
\slv_reg14_reg[15]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg14[15]_i_1_n_0\,
      D => s00_axi_wdata(15),
      Q => slv_reg14(15),
      R => \^rstp\
    );
\slv_reg14_reg[16]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg14[23]_i_1_n_0\,
      D => s00_axi_wdata(16),
      Q => slv_reg14(16),
      R => \^rstp\
    );
\slv_reg14_reg[17]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg14[23]_i_1_n_0\,
      D => s00_axi_wdata(17),
      Q => slv_reg14(17),
      R => \^rstp\
    );
\slv_reg14_reg[18]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg14[23]_i_1_n_0\,
      D => s00_axi_wdata(18),
      Q => slv_reg14(18),
      R => \^rstp\
    );
\slv_reg14_reg[19]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg14[23]_i_1_n_0\,
      D => s00_axi_wdata(19),
      Q => slv_reg14(19),
      R => \^rstp\
    );
\slv_reg14_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg14[7]_i_1_n_0\,
      D => s00_axi_wdata(1),
      Q => slv_reg14(1),
      R => \^rstp\
    );
\slv_reg14_reg[20]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg14[23]_i_1_n_0\,
      D => s00_axi_wdata(20),
      Q => slv_reg14(20),
      R => \^rstp\
    );
\slv_reg14_reg[21]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg14[23]_i_1_n_0\,
      D => s00_axi_wdata(21),
      Q => slv_reg14(21),
      R => \^rstp\
    );
\slv_reg14_reg[22]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg14[23]_i_1_n_0\,
      D => s00_axi_wdata(22),
      Q => slv_reg14(22),
      R => \^rstp\
    );
\slv_reg14_reg[23]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg14[23]_i_1_n_0\,
      D => s00_axi_wdata(23),
      Q => slv_reg14(23),
      R => \^rstp\
    );
\slv_reg14_reg[24]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg14[31]_i_1_n_0\,
      D => s00_axi_wdata(24),
      Q => slv_reg14(24),
      R => \^rstp\
    );
\slv_reg14_reg[25]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg14[31]_i_1_n_0\,
      D => s00_axi_wdata(25),
      Q => slv_reg14(25),
      R => \^rstp\
    );
\slv_reg14_reg[26]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg14[31]_i_1_n_0\,
      D => s00_axi_wdata(26),
      Q => slv_reg14(26),
      R => \^rstp\
    );
\slv_reg14_reg[27]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg14[31]_i_1_n_0\,
      D => s00_axi_wdata(27),
      Q => slv_reg14(27),
      R => \^rstp\
    );
\slv_reg14_reg[28]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg14[31]_i_1_n_0\,
      D => s00_axi_wdata(28),
      Q => slv_reg14(28),
      R => \^rstp\
    );
\slv_reg14_reg[29]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg14[31]_i_1_n_0\,
      D => s00_axi_wdata(29),
      Q => slv_reg14(29),
      R => \^rstp\
    );
\slv_reg14_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg14[7]_i_1_n_0\,
      D => s00_axi_wdata(2),
      Q => slv_reg14(2),
      R => \^rstp\
    );
\slv_reg14_reg[30]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg14[31]_i_1_n_0\,
      D => s00_axi_wdata(30),
      Q => slv_reg14(30),
      R => \^rstp\
    );
\slv_reg14_reg[31]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg14[31]_i_1_n_0\,
      D => s00_axi_wdata(31),
      Q => slv_reg14(31),
      R => \^rstp\
    );
\slv_reg14_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg14[7]_i_1_n_0\,
      D => s00_axi_wdata(3),
      Q => slv_reg14(3),
      R => \^rstp\
    );
\slv_reg14_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg14[7]_i_1_n_0\,
      D => s00_axi_wdata(4),
      Q => slv_reg14(4),
      R => \^rstp\
    );
\slv_reg14_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg14[7]_i_1_n_0\,
      D => s00_axi_wdata(5),
      Q => slv_reg14(5),
      R => \^rstp\
    );
\slv_reg14_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg14[7]_i_1_n_0\,
      D => s00_axi_wdata(6),
      Q => slv_reg14(6),
      R => \^rstp\
    );
\slv_reg14_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg14[7]_i_1_n_0\,
      D => s00_axi_wdata(7),
      Q => slv_reg14(7),
      R => \^rstp\
    );
\slv_reg14_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg14[15]_i_1_n_0\,
      D => s00_axi_wdata(8),
      Q => slv_reg14(8),
      R => \^rstp\
    );
\slv_reg14_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg14[15]_i_1_n_0\,
      D => s00_axi_wdata(9),
      Q => slv_reg14(9),
      R => \^rstp\
    );
\slv_reg15[15]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"8000000000000000"
    )
        port map (
      I0 => \slv_reg_wren__0\,
      I1 => p_0_in(2),
      I2 => s00_axi_wstrb(1),
      I3 => p_0_in(0),
      I4 => p_0_in(1),
      I5 => p_0_in(3),
      O => \slv_reg15[15]_i_1_n_0\
    );
\slv_reg15[23]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"8000000000000000"
    )
        port map (
      I0 => \slv_reg_wren__0\,
      I1 => p_0_in(2),
      I2 => s00_axi_wstrb(2),
      I3 => p_0_in(0),
      I4 => p_0_in(1),
      I5 => p_0_in(3),
      O => \slv_reg15[23]_i_1_n_0\
    );
\slv_reg15[31]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"8000000000000000"
    )
        port map (
      I0 => \slv_reg_wren__0\,
      I1 => p_0_in(2),
      I2 => s00_axi_wstrb(3),
      I3 => p_0_in(0),
      I4 => p_0_in(1),
      I5 => p_0_in(3),
      O => \slv_reg15[31]_i_1_n_0\
    );
\slv_reg15[7]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"8000000000000000"
    )
        port map (
      I0 => \slv_reg_wren__0\,
      I1 => p_0_in(2),
      I2 => s00_axi_wstrb(0),
      I3 => p_0_in(0),
      I4 => p_0_in(1),
      I5 => p_0_in(3),
      O => \slv_reg15[7]_i_1_n_0\
    );
\slv_reg15_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg15[7]_i_1_n_0\,
      D => s00_axi_wdata(0),
      Q => slv_reg15(0),
      R => \^rstp\
    );
\slv_reg15_reg[10]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg15[15]_i_1_n_0\,
      D => s00_axi_wdata(10),
      Q => slv_reg15(10),
      R => \^rstp\
    );
\slv_reg15_reg[11]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg15[15]_i_1_n_0\,
      D => s00_axi_wdata(11),
      Q => slv_reg15(11),
      R => \^rstp\
    );
\slv_reg15_reg[12]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg15[15]_i_1_n_0\,
      D => s00_axi_wdata(12),
      Q => slv_reg15(12),
      R => \^rstp\
    );
\slv_reg15_reg[13]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg15[15]_i_1_n_0\,
      D => s00_axi_wdata(13),
      Q => slv_reg15(13),
      R => \^rstp\
    );
\slv_reg15_reg[14]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg15[15]_i_1_n_0\,
      D => s00_axi_wdata(14),
      Q => slv_reg15(14),
      R => \^rstp\
    );
\slv_reg15_reg[15]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg15[15]_i_1_n_0\,
      D => s00_axi_wdata(15),
      Q => slv_reg15(15),
      R => \^rstp\
    );
\slv_reg15_reg[16]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg15[23]_i_1_n_0\,
      D => s00_axi_wdata(16),
      Q => slv_reg15(16),
      R => \^rstp\
    );
\slv_reg15_reg[17]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg15[23]_i_1_n_0\,
      D => s00_axi_wdata(17),
      Q => slv_reg15(17),
      R => \^rstp\
    );
\slv_reg15_reg[18]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg15[23]_i_1_n_0\,
      D => s00_axi_wdata(18),
      Q => slv_reg15(18),
      R => \^rstp\
    );
\slv_reg15_reg[19]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg15[23]_i_1_n_0\,
      D => s00_axi_wdata(19),
      Q => slv_reg15(19),
      R => \^rstp\
    );
\slv_reg15_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg15[7]_i_1_n_0\,
      D => s00_axi_wdata(1),
      Q => slv_reg15(1),
      R => \^rstp\
    );
\slv_reg15_reg[20]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg15[23]_i_1_n_0\,
      D => s00_axi_wdata(20),
      Q => slv_reg15(20),
      R => \^rstp\
    );
\slv_reg15_reg[21]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg15[23]_i_1_n_0\,
      D => s00_axi_wdata(21),
      Q => slv_reg15(21),
      R => \^rstp\
    );
\slv_reg15_reg[22]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg15[23]_i_1_n_0\,
      D => s00_axi_wdata(22),
      Q => slv_reg15(22),
      R => \^rstp\
    );
\slv_reg15_reg[23]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg15[23]_i_1_n_0\,
      D => s00_axi_wdata(23),
      Q => slv_reg15(23),
      R => \^rstp\
    );
\slv_reg15_reg[24]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg15[31]_i_1_n_0\,
      D => s00_axi_wdata(24),
      Q => slv_reg15(24),
      R => \^rstp\
    );
\slv_reg15_reg[25]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg15[31]_i_1_n_0\,
      D => s00_axi_wdata(25),
      Q => slv_reg15(25),
      R => \^rstp\
    );
\slv_reg15_reg[26]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg15[31]_i_1_n_0\,
      D => s00_axi_wdata(26),
      Q => slv_reg15(26),
      R => \^rstp\
    );
\slv_reg15_reg[27]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg15[31]_i_1_n_0\,
      D => s00_axi_wdata(27),
      Q => slv_reg15(27),
      R => \^rstp\
    );
\slv_reg15_reg[28]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg15[31]_i_1_n_0\,
      D => s00_axi_wdata(28),
      Q => slv_reg15(28),
      R => \^rstp\
    );
\slv_reg15_reg[29]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg15[31]_i_1_n_0\,
      D => s00_axi_wdata(29),
      Q => slv_reg15(29),
      R => \^rstp\
    );
\slv_reg15_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg15[7]_i_1_n_0\,
      D => s00_axi_wdata(2),
      Q => slv_reg15(2),
      R => \^rstp\
    );
\slv_reg15_reg[30]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg15[31]_i_1_n_0\,
      D => s00_axi_wdata(30),
      Q => slv_reg15(30),
      R => \^rstp\
    );
\slv_reg15_reg[31]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg15[31]_i_1_n_0\,
      D => s00_axi_wdata(31),
      Q => slv_reg15(31),
      R => \^rstp\
    );
\slv_reg15_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg15[7]_i_1_n_0\,
      D => s00_axi_wdata(3),
      Q => slv_reg15(3),
      R => \^rstp\
    );
\slv_reg15_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg15[7]_i_1_n_0\,
      D => s00_axi_wdata(4),
      Q => slv_reg15(4),
      R => \^rstp\
    );
\slv_reg15_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg15[7]_i_1_n_0\,
      D => s00_axi_wdata(5),
      Q => slv_reg15(5),
      R => \^rstp\
    );
\slv_reg15_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg15[7]_i_1_n_0\,
      D => s00_axi_wdata(6),
      Q => slv_reg15(6),
      R => \^rstp\
    );
\slv_reg15_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg15[7]_i_1_n_0\,
      D => s00_axi_wdata(7),
      Q => slv_reg15(7),
      R => \^rstp\
    );
\slv_reg15_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg15[15]_i_1_n_0\,
      D => s00_axi_wdata(8),
      Q => slv_reg15(8),
      R => \^rstp\
    );
\slv_reg15_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \slv_reg15[15]_i_1_n_0\,
      D => s00_axi_wdata(9),
      Q => slv_reg15(9),
      R => \^rstp\
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity zusys_A3_ADC_LTC2311_0_MULT_ADD is
  port (
    P : out STD_LOGIC_VECTOR ( 0 to 0 );
    \S_RESULT_COUNTER_reg[0]_rep\ : out STD_LOGIC;
    SI_VALUE0 : out STD_LOGIC_VECTOR ( 127 downto 0 );
    \S_ENABLE_reg[0]\ : out STD_LOGIC;
    \S_ENABLE_reg[0]_0\ : out STD_LOGIC;
    CO : out STD_LOGIC_VECTOR ( 0 to 0 );
    \S_SAMPLE_TIME_COUNTER_reg[11]\ : out STD_LOGIC;
    \curstate_reg[0]\ : out STD_LOGIC;
    \S_SAMPLE_TIME_COUNTER_reg[23]\ : out STD_LOGIC;
    \S_SAMPLE_TIME_COUNTER_reg[17]\ : out STD_LOGIC;
    \S_CONV_COUNTER_reg[0]\ : out STD_LOGIC;
    CEP : in STD_LOGIC;
    s00_axi_aclk : in STD_LOGIC;
    RSTP : in STD_LOGIC;
    Q : in STD_LOGIC_VECTOR ( 15 downto 0 );
    DSP_ALU_INST : in STD_LOGIC_VECTOR ( 15 downto 0 );
    \SI_VALUE_reg[34]\ : in STD_LOGIC_VECTOR ( 3 downto 0 );
    \SI_VALUE_reg[209]\ : in STD_LOGIC;
    \SI_VALUE_reg[209]_0\ : in STD_LOGIC;
    \SI_VALUE_reg[273]\ : in STD_LOGIC;
    \SI_VALUE_reg[273]_0\ : in STD_LOGIC;
    \SI_VALUE_reg[206]\ : in STD_LOGIC;
    DSP_A_B_DATA_INST : in STD_LOGIC_VECTOR ( 3 downto 0 );
    ENABLE : in STD_LOGIC;
    SI_VALID_reg : in STD_LOGIC_VECTOR ( 1 downto 0 );
    SI_VALID_reg_0 : in STD_LOGIC_VECTOR ( 1 downto 0 );
    S_DUMMY_SAMPLE : in STD_LOGIC;
    \S_SAMPLE_TIME_COUNTER[30]_i_7\ : in STD_LOGIC_VECTOR ( 30 downto 0 );
    \SI_VALUE_reg[115]\ : in STD_LOGIC;
    SI_VALID_reg_i_8_0 : in STD_LOGIC_VECTOR ( 0 to 0 );
    SI_VALID_reg_i_8_1 : in STD_LOGIC;
    nxtstate3 : in STD_LOGIC_VECTOR ( 29 downto 0 );
    S : in STD_LOGIC_VECTOR ( 7 downto 0 );
    SI_VALID_reg_i_3_0 : in STD_LOGIC_VECTOR ( 7 downto 0 );
    SI_VALID_reg_i_3_1 : in STD_LOGIC_VECTOR ( 7 downto 0 );
    SI_VALID_reg_i_3_2 : in STD_LOGIC_VECTOR ( 6 downto 0 );
    SI_VALID_reg_i_3_3 : in STD_LOGIC_VECTOR ( 0 to 0 );
    DSP_A_B_DATA_INST_0 : in STD_LOGIC_VECTOR ( 143 downto 0 );
    \SI_VALUE_reg[279]\ : in STD_LOGIC
  );
  attribute ORIG_REF_NAME : string;
  attribute ORIG_REF_NAME of zusys_A3_ADC_LTC2311_0_MULT_ADD : entity is "MULT_ADD";
end zusys_A3_ADC_LTC2311_0_MULT_ADD;

architecture STRUCTURE of zusys_A3_ADC_LTC2311_0_MULT_ADD is
  signal \^co\ : STD_LOGIC_VECTOR ( 0 to 0 );
  signal \^p\ : STD_LOGIC_VECTOR ( 0 to 0 );
  signal RAW_VALID_i_3_n_0 : STD_LOGIC;
  signal SI_VALID_i_10_n_0 : STD_LOGIC;
  signal SI_VALID_i_11_n_0 : STD_LOGIC;
  signal SI_VALID_i_12_n_0 : STD_LOGIC;
  signal SI_VALID_i_13_n_0 : STD_LOGIC;
  signal SI_VALID_i_14_n_0 : STD_LOGIC;
  signal SI_VALID_i_15_n_0 : STD_LOGIC;
  signal SI_VALID_i_16_n_0 : STD_LOGIC;
  signal SI_VALID_i_17_n_0 : STD_LOGIC;
  signal SI_VALID_i_18_n_0 : STD_LOGIC;
  signal SI_VALID_i_19_n_0 : STD_LOGIC;
  signal SI_VALID_i_20_n_0 : STD_LOGIC;
  signal SI_VALID_i_21_n_0 : STD_LOGIC;
  signal SI_VALID_i_22_n_0 : STD_LOGIC;
  signal SI_VALID_i_23_n_0 : STD_LOGIC;
  signal SI_VALID_i_24_n_0 : STD_LOGIC;
  signal SI_VALID_i_25_n_0 : STD_LOGIC;
  signal SI_VALID_i_26_n_0 : STD_LOGIC;
  signal SI_VALID_i_27_n_0 : STD_LOGIC;
  signal SI_VALID_i_29_n_0 : STD_LOGIC;
  signal SI_VALID_i_31_n_0 : STD_LOGIC;
  signal SI_VALID_i_32_n_0 : STD_LOGIC;
  signal SI_VALID_i_33_n_0 : STD_LOGIC;
  signal SI_VALID_i_34_n_0 : STD_LOGIC;
  signal SI_VALID_i_35_n_0 : STD_LOGIC;
  signal SI_VALID_i_36_n_0 : STD_LOGIC;
  signal SI_VALID_i_37_n_0 : STD_LOGIC;
  signal SI_VALID_i_38_n_0 : STD_LOGIC;
  signal SI_VALID_i_39_n_0 : STD_LOGIC;
  signal SI_VALID_i_40_n_0 : STD_LOGIC;
  signal SI_VALID_i_41_n_0 : STD_LOGIC;
  signal SI_VALID_i_42_n_0 : STD_LOGIC;
  signal SI_VALID_i_43_n_0 : STD_LOGIC;
  signal SI_VALID_i_44_n_0 : STD_LOGIC;
  signal SI_VALID_i_45_n_0 : STD_LOGIC;
  signal SI_VALID_i_46_n_0 : STD_LOGIC;
  signal SI_VALID_i_47_n_0 : STD_LOGIC;
  signal SI_VALID_i_48_n_0 : STD_LOGIC;
  signal SI_VALID_i_6_n_0 : STD_LOGIC;
  signal SI_VALID_i_7_n_0 : STD_LOGIC;
  signal SI_VALID_i_9_n_0 : STD_LOGIC;
  signal SI_VALID_reg_i_3_n_1 : STD_LOGIC;
  signal SI_VALID_reg_i_3_n_2 : STD_LOGIC;
  signal SI_VALID_reg_i_3_n_3 : STD_LOGIC;
  signal SI_VALID_reg_i_3_n_4 : STD_LOGIC;
  signal SI_VALID_reg_i_3_n_5 : STD_LOGIC;
  signal SI_VALID_reg_i_3_n_6 : STD_LOGIC;
  signal SI_VALID_reg_i_3_n_7 : STD_LOGIC;
  signal SI_VALID_reg_i_8_n_0 : STD_LOGIC;
  signal SI_VALID_reg_i_8_n_1 : STD_LOGIC;
  signal SI_VALID_reg_i_8_n_2 : STD_LOGIC;
  signal SI_VALID_reg_i_8_n_3 : STD_LOGIC;
  signal SI_VALID_reg_i_8_n_4 : STD_LOGIC;
  signal SI_VALID_reg_i_8_n_5 : STD_LOGIC;
  signal SI_VALID_reg_i_8_n_6 : STD_LOGIC;
  signal SI_VALID_reg_i_8_n_7 : STD_LOGIC;
  signal \^si_value0\ : STD_LOGIC_VECTOR ( 127 downto 0 );
  signal \SI_VALUE[105]_i_2_n_0\ : STD_LOGIC;
  signal \SI_VALUE[106]_i_2_n_0\ : STD_LOGIC;
  signal \SI_VALUE[106]_i_3_n_0\ : STD_LOGIC;
  signal \SI_VALUE[107]_i_2_n_0\ : STD_LOGIC;
  signal \SI_VALUE[140]_i_2_n_0\ : STD_LOGIC;
  signal \SI_VALUE[141]_i_2_n_0\ : STD_LOGIC;
  signal \SI_VALUE[141]_i_3_n_0\ : STD_LOGIC;
  signal \SI_VALUE[141]_i_4_n_0\ : STD_LOGIC;
  signal \SI_VALUE[142]_i_2_n_0\ : STD_LOGIC;
  signal \SI_VALUE[142]_i_3_n_0\ : STD_LOGIC;
  signal \SI_VALUE[142]_i_4_n_0\ : STD_LOGIC;
  signal \SI_VALUE[142]_i_5_n_0\ : STD_LOGIC;
  signal \SI_VALUE[142]_i_6_n_0\ : STD_LOGIC;
  signal \SI_VALUE[142]_i_7_n_0\ : STD_LOGIC;
  signal \SI_VALUE[142]_i_8_n_0\ : STD_LOGIC;
  signal \SI_VALUE[175]_i_2_n_0\ : STD_LOGIC;
  signal \SI_VALUE[175]_i_3_n_0\ : STD_LOGIC;
  signal \SI_VALUE[175]_i_4_n_0\ : STD_LOGIC;
  signal \SI_VALUE[175]_i_5_n_0\ : STD_LOGIC;
  signal \SI_VALUE[175]_i_6_n_0\ : STD_LOGIC;
  signal \SI_VALUE[175]_i_7_n_0\ : STD_LOGIC;
  signal \SI_VALUE[176]_i_2_n_0\ : STD_LOGIC;
  signal \SI_VALUE[176]_i_3_n_0\ : STD_LOGIC;
  signal \SI_VALUE[176]_i_4_n_0\ : STD_LOGIC;
  signal \SI_VALUE[176]_i_5_n_0\ : STD_LOGIC;
  signal \SI_VALUE[176]_i_6_n_0\ : STD_LOGIC;
  signal \SI_VALUE[176]_i_7_n_0\ : STD_LOGIC;
  signal \SI_VALUE[177]_i_2_n_0\ : STD_LOGIC;
  signal \SI_VALUE[177]_i_3_n_0\ : STD_LOGIC;
  signal \SI_VALUE[177]_i_4_n_0\ : STD_LOGIC;
  signal \SI_VALUE[177]_i_5_n_0\ : STD_LOGIC;
  signal \SI_VALUE[177]_i_6_n_0\ : STD_LOGIC;
  signal \SI_VALUE[177]_i_7_n_0\ : STD_LOGIC;
  signal \SI_VALUE[177]_i_8_n_0\ : STD_LOGIC;
  signal \SI_VALUE[177]_i_9_n_0\ : STD_LOGIC;
  signal \SI_VALUE[178]_i_2_n_0\ : STD_LOGIC;
  signal \SI_VALUE[179]_i_2_n_0\ : STD_LOGIC;
  signal \SI_VALUE[180]_i_2_n_0\ : STD_LOGIC;
  signal \SI_VALUE[207]_i_2_n_0\ : STD_LOGIC;
  signal \SI_VALUE[211]_i_2_n_0\ : STD_LOGIC;
  signal \SI_VALUE[211]_i_3_n_0\ : STD_LOGIC;
  signal \SI_VALUE[211]_i_4_n_0\ : STD_LOGIC;
  signal \SI_VALUE[212]_i_2_n_0\ : STD_LOGIC;
  signal \SI_VALUE[212]_i_3_n_0\ : STD_LOGIC;
  signal \SI_VALUE[212]_i_4_n_0\ : STD_LOGIC;
  signal \SI_VALUE[245]_i_2_n_0\ : STD_LOGIC;
  signal \SI_VALUE[246]_i_2_n_0\ : STD_LOGIC;
  signal \SI_VALUE[247]_i_2_n_0\ : STD_LOGIC;
  signal \SI_VALUE[248]_i_2_n_0\ : STD_LOGIC;
  signal \SI_VALUE[248]_i_3_n_0\ : STD_LOGIC;
  signal \SI_VALUE[249]_i_2_n_0\ : STD_LOGIC;
  signal \SI_VALUE[250]_i_2_n_0\ : STD_LOGIC;
  signal \SI_VALUE[251]_i_2_n_0\ : STD_LOGIC;
  signal \SI_VALUE[252]_i_2_n_0\ : STD_LOGIC;
  signal \SI_VALUE[253]_i_2_n_0\ : STD_LOGIC;
  signal \SI_VALUE[254]_i_2_n_0\ : STD_LOGIC;
  signal \SI_VALUE[255]_i_2_n_0\ : STD_LOGIC;
  signal \SI_VALUE[256]_i_2_n_0\ : STD_LOGIC;
  signal \SI_VALUE[257]_i_2_n_0\ : STD_LOGIC;
  signal \SI_VALUE[258]_i_2_n_0\ : STD_LOGIC;
  signal \SI_VALUE[259]_i_2_n_0\ : STD_LOGIC;
  signal \SI_VALUE[260]_i_2_n_0\ : STD_LOGIC;
  signal \SI_VALUE[261]_i_2_n_0\ : STD_LOGIC;
  signal \SI_VALUE[262]_i_2_n_0\ : STD_LOGIC;
  signal \SI_VALUE[262]_i_3_n_0\ : STD_LOGIC;
  signal \SI_VALUE[263]_i_2_n_0\ : STD_LOGIC;
  signal \SI_VALUE[263]_i_3_n_0\ : STD_LOGIC;
  signal \SI_VALUE[264]_i_2_n_0\ : STD_LOGIC;
  signal \SI_VALUE[264]_i_3_n_0\ : STD_LOGIC;
  signal \SI_VALUE[265]_i_2_n_0\ : STD_LOGIC;
  signal \SI_VALUE[265]_i_3_n_0\ : STD_LOGIC;
  signal \SI_VALUE[266]_i_2_n_0\ : STD_LOGIC;
  signal \SI_VALUE[266]_i_3_n_0\ : STD_LOGIC;
  signal \SI_VALUE[266]_i_4_n_0\ : STD_LOGIC;
  signal \SI_VALUE[267]_i_2_n_0\ : STD_LOGIC;
  signal \SI_VALUE[267]_i_3_n_0\ : STD_LOGIC;
  signal \SI_VALUE[267]_i_4_n_0\ : STD_LOGIC;
  signal \SI_VALUE[268]_i_2_n_0\ : STD_LOGIC;
  signal \SI_VALUE[268]_i_3_n_0\ : STD_LOGIC;
  signal \SI_VALUE[268]_i_4_n_0\ : STD_LOGIC;
  signal \SI_VALUE[268]_i_5_n_0\ : STD_LOGIC;
  signal \SI_VALUE[269]_i_2_n_0\ : STD_LOGIC;
  signal \SI_VALUE[269]_i_3_n_0\ : STD_LOGIC;
  signal \SI_VALUE[269]_i_4_n_0\ : STD_LOGIC;
  signal \SI_VALUE[269]_i_5_n_0\ : STD_LOGIC;
  signal \SI_VALUE[270]_i_2_n_0\ : STD_LOGIC;
  signal \SI_VALUE[270]_i_4_n_0\ : STD_LOGIC;
  signal \SI_VALUE[270]_i_5_n_0\ : STD_LOGIC;
  signal \SI_VALUE[271]_i_2_n_0\ : STD_LOGIC;
  signal \SI_VALUE[271]_i_3_n_0\ : STD_LOGIC;
  signal \SI_VALUE[271]_i_4_n_0\ : STD_LOGIC;
  signal \SI_VALUE[271]_i_5_n_0\ : STD_LOGIC;
  signal \SI_VALUE[272]_i_2_n_0\ : STD_LOGIC;
  signal \SI_VALUE[272]_i_3_n_0\ : STD_LOGIC;
  signal \SI_VALUE[272]_i_4_n_0\ : STD_LOGIC;
  signal \SI_VALUE[272]_i_5_n_0\ : STD_LOGIC;
  signal \SI_VALUE[272]_i_6_n_0\ : STD_LOGIC;
  signal \SI_VALUE[273]_i_3_n_0\ : STD_LOGIC;
  signal \SI_VALUE[273]_i_5_n_0\ : STD_LOGIC;
  signal \SI_VALUE[273]_i_6_n_0\ : STD_LOGIC;
  signal \SI_VALUE[273]_i_7_n_0\ : STD_LOGIC;
  signal \SI_VALUE[274]_i_2_n_0\ : STD_LOGIC;
  signal \SI_VALUE[274]_i_3_n_0\ : STD_LOGIC;
  signal \SI_VALUE[274]_i_4_n_0\ : STD_LOGIC;
  signal \SI_VALUE[274]_i_5_n_0\ : STD_LOGIC;
  signal \SI_VALUE[275]_i_2_n_0\ : STD_LOGIC;
  signal \SI_VALUE[275]_i_3_n_0\ : STD_LOGIC;
  signal \SI_VALUE[275]_i_4_n_0\ : STD_LOGIC;
  signal \SI_VALUE[275]_i_5_n_0\ : STD_LOGIC;
  signal \SI_VALUE[276]_i_10_n_0\ : STD_LOGIC;
  signal \SI_VALUE[276]_i_2_n_0\ : STD_LOGIC;
  signal \SI_VALUE[276]_i_3_n_0\ : STD_LOGIC;
  signal \SI_VALUE[276]_i_4_n_0\ : STD_LOGIC;
  signal \SI_VALUE[276]_i_5_n_0\ : STD_LOGIC;
  signal \SI_VALUE[276]_i_6_n_0\ : STD_LOGIC;
  signal \SI_VALUE[276]_i_7_n_0\ : STD_LOGIC;
  signal \SI_VALUE[276]_i_8_n_0\ : STD_LOGIC;
  signal \SI_VALUE[276]_i_9_n_0\ : STD_LOGIC;
  signal \SI_VALUE[277]_i_2_n_0\ : STD_LOGIC;
  signal \SI_VALUE[277]_i_3_n_0\ : STD_LOGIC;
  signal \SI_VALUE[277]_i_4_n_0\ : STD_LOGIC;
  signal \SI_VALUE[277]_i_5_n_0\ : STD_LOGIC;
  signal \SI_VALUE[277]_i_6_n_0\ : STD_LOGIC;
  signal \SI_VALUE[277]_i_7_n_0\ : STD_LOGIC;
  signal \SI_VALUE[277]_i_8_n_0\ : STD_LOGIC;
  signal \SI_VALUE[278]_i_2_n_0\ : STD_LOGIC;
  signal \SI_VALUE[278]_i_3_n_0\ : STD_LOGIC;
  signal \SI_VALUE[278]_i_4_n_0\ : STD_LOGIC;
  signal \SI_VALUE[278]_i_5_n_0\ : STD_LOGIC;
  signal \SI_VALUE[278]_i_6_n_0\ : STD_LOGIC;
  signal \SI_VALUE[278]_i_7_n_0\ : STD_LOGIC;
  signal \SI_VALUE[278]_i_8_n_0\ : STD_LOGIC;
  signal \SI_VALUE[279]_i_10_n_0\ : STD_LOGIC;
  signal \SI_VALUE[279]_i_11_n_0\ : STD_LOGIC;
  signal \SI_VALUE[279]_i_4_n_0\ : STD_LOGIC;
  signal \SI_VALUE[279]_i_5_n_0\ : STD_LOGIC;
  signal \SI_VALUE[279]_i_8_n_0\ : STD_LOGIC;
  signal \SI_VALUE[279]_i_9_n_0\ : STD_LOGIC;
  signal \SI_VALUE[2]_i_2_n_0\ : STD_LOGIC;
  signal \^s_conv_counter_reg[0]\ : STD_LOGIC;
  signal \^s_enable_reg[0]\ : STD_LOGIC;
  signal \^s_enable_reg[0]_0\ : STD_LOGIC;
  signal S_MULT_reg_i_10_n_0 : STD_LOGIC;
  signal S_MULT_reg_i_11_n_0 : STD_LOGIC;
  signal S_MULT_reg_i_12_n_0 : STD_LOGIC;
  signal S_MULT_reg_i_13_n_0 : STD_LOGIC;
  signal S_MULT_reg_i_14_n_0 : STD_LOGIC;
  signal S_MULT_reg_i_15_n_0 : STD_LOGIC;
  signal S_MULT_reg_i_16_n_0 : STD_LOGIC;
  signal S_MULT_reg_i_17_n_0 : STD_LOGIC;
  signal S_MULT_reg_i_18_n_0 : STD_LOGIC;
  signal S_MULT_reg_i_19_n_0 : STD_LOGIC;
  signal S_MULT_reg_i_1_n_0 : STD_LOGIC;
  signal S_MULT_reg_i_21_n_0 : STD_LOGIC;
  signal S_MULT_reg_i_22_n_0 : STD_LOGIC;
  signal S_MULT_reg_i_23_n_0 : STD_LOGIC;
  signal S_MULT_reg_i_24_n_0 : STD_LOGIC;
  signal S_MULT_reg_i_25_n_0 : STD_LOGIC;
  signal S_MULT_reg_i_26_n_0 : STD_LOGIC;
  signal S_MULT_reg_i_27_n_0 : STD_LOGIC;
  signal S_MULT_reg_i_28_n_0 : STD_LOGIC;
  signal S_MULT_reg_i_29_n_0 : STD_LOGIC;
  signal S_MULT_reg_i_2_n_0 : STD_LOGIC;
  signal S_MULT_reg_i_30_n_0 : STD_LOGIC;
  signal S_MULT_reg_i_31_n_0 : STD_LOGIC;
  signal S_MULT_reg_i_32_n_0 : STD_LOGIC;
  signal S_MULT_reg_i_33_n_0 : STD_LOGIC;
  signal S_MULT_reg_i_34_n_0 : STD_LOGIC;
  signal S_MULT_reg_i_35_n_0 : STD_LOGIC;
  signal S_MULT_reg_i_36_n_0 : STD_LOGIC;
  signal S_MULT_reg_i_37_n_0 : STD_LOGIC;
  signal S_MULT_reg_i_38_n_0 : STD_LOGIC;
  signal S_MULT_reg_i_39_n_0 : STD_LOGIC;
  signal S_MULT_reg_i_3_n_0 : STD_LOGIC;
  signal S_MULT_reg_i_40_n_0 : STD_LOGIC;
  signal S_MULT_reg_i_41_n_0 : STD_LOGIC;
  signal S_MULT_reg_i_42_n_0 : STD_LOGIC;
  signal S_MULT_reg_i_43_n_0 : STD_LOGIC;
  signal S_MULT_reg_i_44_n_0 : STD_LOGIC;
  signal S_MULT_reg_i_45_n_0 : STD_LOGIC;
  signal S_MULT_reg_i_46_n_0 : STD_LOGIC;
  signal S_MULT_reg_i_47_n_0 : STD_LOGIC;
  signal S_MULT_reg_i_48_n_0 : STD_LOGIC;
  signal S_MULT_reg_i_49_n_0 : STD_LOGIC;
  signal S_MULT_reg_i_4_n_0 : STD_LOGIC;
  signal S_MULT_reg_i_50_n_0 : STD_LOGIC;
  signal S_MULT_reg_i_51_n_0 : STD_LOGIC;
  signal S_MULT_reg_i_52_n_0 : STD_LOGIC;
  signal S_MULT_reg_i_53_n_0 : STD_LOGIC;
  signal S_MULT_reg_i_54_n_0 : STD_LOGIC;
  signal S_MULT_reg_i_55_n_0 : STD_LOGIC;
  signal S_MULT_reg_i_56_n_0 : STD_LOGIC;
  signal S_MULT_reg_i_5_n_0 : STD_LOGIC;
  signal S_MULT_reg_i_6_n_0 : STD_LOGIC;
  signal S_MULT_reg_i_7_n_0 : STD_LOGIC;
  signal S_MULT_reg_i_8_n_0 : STD_LOGIC;
  signal S_MULT_reg_i_9_n_0 : STD_LOGIC;
  signal S_RESULT_S_C : STD_LOGIC_VECTOR ( 34 downto 0 );
  signal \^s_sample_time_counter_reg[11]\ : STD_LOGIC;
  signal \^s_sample_time_counter_reg[17]\ : STD_LOGIC;
  signal \^s_sample_time_counter_reg[23]\ : STD_LOGIC;
  signal \^curstate_reg[0]\ : STD_LOGIC;
  signal NLW_SI_VALID_reg_i_3_O_UNCONNECTED : STD_LOGIC_VECTOR ( 7 downto 0 );
  signal NLW_SI_VALID_reg_i_8_O_UNCONNECTED : STD_LOGIC_VECTOR ( 7 downto 0 );
  signal NLW_S_MULT_reg_CARRYCASCOUT_UNCONNECTED : STD_LOGIC;
  signal NLW_S_MULT_reg_MULTSIGNOUT_UNCONNECTED : STD_LOGIC;
  signal NLW_S_MULT_reg_OVERFLOW_UNCONNECTED : STD_LOGIC;
  signal NLW_S_MULT_reg_PATTERNBDETECT_UNCONNECTED : STD_LOGIC;
  signal NLW_S_MULT_reg_PATTERNDETECT_UNCONNECTED : STD_LOGIC;
  signal NLW_S_MULT_reg_UNDERFLOW_UNCONNECTED : STD_LOGIC;
  signal NLW_S_MULT_reg_ACOUT_UNCONNECTED : STD_LOGIC_VECTOR ( 29 downto 0 );
  signal NLW_S_MULT_reg_BCOUT_UNCONNECTED : STD_LOGIC_VECTOR ( 17 downto 0 );
  signal NLW_S_MULT_reg_CARRYOUT_UNCONNECTED : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal NLW_S_MULT_reg_P_UNCONNECTED : STD_LOGIC_VECTOR ( 47 downto 35 );
  signal NLW_S_MULT_reg_PCOUT_UNCONNECTED : STD_LOGIC_VECTOR ( 47 downto 0 );
  signal NLW_S_MULT_reg_XOROUT_UNCONNECTED : STD_LOGIC_VECTOR ( 7 downto 0 );
  attribute SOFT_HLUTNM : string;
  attribute SOFT_HLUTNM of RAW_VALID_i_3 : label is "soft_lutpair36";
  attribute SOFT_HLUTNM of SI_VALID_i_32 : label is "soft_lutpair34";
  attribute SOFT_HLUTNM of SI_VALID_i_4 : label is "soft_lutpair36";
  attribute COMPARATOR_THRESHOLD : integer;
  attribute COMPARATOR_THRESHOLD of SI_VALID_reg_i_3 : label is 11;
  attribute COMPARATOR_THRESHOLD of SI_VALID_reg_i_8 : label is 11;
  attribute SOFT_HLUTNM of \SI_VALUE[114]_i_1\ : label is "soft_lutpair52";
  attribute SOFT_HLUTNM of \SI_VALUE[115]_i_1\ : label is "soft_lutpair53";
  attribute SOFT_HLUTNM of \SI_VALUE[116]_i_1\ : label is "soft_lutpair54";
  attribute SOFT_HLUTNM of \SI_VALUE[117]_i_1\ : label is "soft_lutpair42";
  attribute SOFT_HLUTNM of \SI_VALUE[118]_i_1\ : label is "soft_lutpair41";
  attribute SOFT_HLUTNM of \SI_VALUE[119]_i_1\ : label is "soft_lutpair40";
  attribute SOFT_HLUTNM of \SI_VALUE[120]_i_1\ : label is "soft_lutpair44";
  attribute SOFT_HLUTNM of \SI_VALUE[121]_i_1\ : label is "soft_lutpair45";
  attribute SOFT_HLUTNM of \SI_VALUE[122]_i_1\ : label is "soft_lutpair46";
  attribute SOFT_HLUTNM of \SI_VALUE[123]_i_1\ : label is "soft_lutpair47";
  attribute SOFT_HLUTNM of \SI_VALUE[124]_i_1\ : label is "soft_lutpair48";
  attribute SOFT_HLUTNM of \SI_VALUE[125]_i_1\ : label is "soft_lutpair49";
  attribute SOFT_HLUTNM of \SI_VALUE[126]_i_1\ : label is "soft_lutpair50";
  attribute SOFT_HLUTNM of \SI_VALUE[127]_i_1\ : label is "soft_lutpair51";
  attribute SOFT_HLUTNM of \SI_VALUE[128]_i_1\ : label is "soft_lutpair39";
  attribute SOFT_HLUTNM of \SI_VALUE[129]_i_1\ : label is "soft_lutpair38";
  attribute SOFT_HLUTNM of \SI_VALUE[130]_i_1\ : label is "soft_lutpair37";
  attribute SOFT_HLUTNM of \SI_VALUE[131]_i_1\ : label is "soft_lutpair68";
  attribute SOFT_HLUTNM of \SI_VALUE[132]_i_1\ : label is "soft_lutpair67";
  attribute SOFT_HLUTNM of \SI_VALUE[133]_i_1\ : label is "soft_lutpair66";
  attribute SOFT_HLUTNM of \SI_VALUE[134]_i_1\ : label is "soft_lutpair65";
  attribute SOFT_HLUTNM of \SI_VALUE[135]_i_1\ : label is "soft_lutpair64";
  attribute SOFT_HLUTNM of \SI_VALUE[136]_i_1\ : label is "soft_lutpair63";
  attribute SOFT_HLUTNM of \SI_VALUE[137]_i_1\ : label is "soft_lutpair60";
  attribute SOFT_HLUTNM of \SI_VALUE[175]_i_2\ : label is "soft_lutpair55";
  attribute SOFT_HLUTNM of \SI_VALUE[18]_i_1\ : label is "soft_lutpair52";
  attribute SOFT_HLUTNM of \SI_VALUE[19]_i_1\ : label is "soft_lutpair53";
  attribute SOFT_HLUTNM of \SI_VALUE[207]_i_1\ : label is "soft_lutpair57";
  attribute SOFT_HLUTNM of \SI_VALUE[20]_i_1\ : label is "soft_lutpair54";
  attribute SOFT_HLUTNM of \SI_VALUE[211]_i_2\ : label is "soft_lutpair55";
  attribute SOFT_HLUTNM of \SI_VALUE[212]_i_2\ : label is "soft_lutpair58";
  attribute SOFT_HLUTNM of \SI_VALUE[21]_i_1\ : label is "soft_lutpair42";
  attribute SOFT_HLUTNM of \SI_VALUE[223]_i_1\ : label is "soft_lutpair62";
  attribute SOFT_HLUTNM of \SI_VALUE[224]_i_1\ : label is "soft_lutpair61";
  attribute SOFT_HLUTNM of \SI_VALUE[22]_i_1\ : label is "soft_lutpair41";
  attribute SOFT_HLUTNM of \SI_VALUE[23]_i_1\ : label is "soft_lutpair40";
  attribute SOFT_HLUTNM of \SI_VALUE[245]_i_2\ : label is "soft_lutpair43";
  attribute SOFT_HLUTNM of \SI_VALUE[248]_i_3\ : label is "soft_lutpair58";
  attribute SOFT_HLUTNM of \SI_VALUE[24]_i_1\ : label is "soft_lutpair44";
  attribute SOFT_HLUTNM of \SI_VALUE[255]_i_1\ : label is "soft_lutpair62";
  attribute SOFT_HLUTNM of \SI_VALUE[256]_i_1\ : label is "soft_lutpair61";
  attribute SOFT_HLUTNM of \SI_VALUE[259]_i_1\ : label is "soft_lutpair68";
  attribute SOFT_HLUTNM of \SI_VALUE[25]_i_1\ : label is "soft_lutpair45";
  attribute SOFT_HLUTNM of \SI_VALUE[260]_i_1\ : label is "soft_lutpair67";
  attribute SOFT_HLUTNM of \SI_VALUE[261]_i_1\ : label is "soft_lutpair66";
  attribute SOFT_HLUTNM of \SI_VALUE[262]_i_1\ : label is "soft_lutpair65";
  attribute SOFT_HLUTNM of \SI_VALUE[262]_i_3\ : label is "soft_lutpair56";
  attribute SOFT_HLUTNM of \SI_VALUE[263]_i_1\ : label is "soft_lutpair64";
  attribute SOFT_HLUTNM of \SI_VALUE[264]_i_1\ : label is "soft_lutpair63";
  attribute SOFT_HLUTNM of \SI_VALUE[264]_i_3\ : label is "soft_lutpair31";
  attribute SOFT_HLUTNM of \SI_VALUE[265]_i_3\ : label is "soft_lutpair31";
  attribute SOFT_HLUTNM of \SI_VALUE[26]_i_1\ : label is "soft_lutpair46";
  attribute SOFT_HLUTNM of \SI_VALUE[271]_i_3\ : label is "soft_lutpair57";
  attribute SOFT_HLUTNM of \SI_VALUE[274]_i_2\ : label is "soft_lutpair56";
  attribute SOFT_HLUTNM of \SI_VALUE[27]_i_1\ : label is "soft_lutpair47";
  attribute SOFT_HLUTNM of \SI_VALUE[28]_i_1\ : label is "soft_lutpair48";
  attribute SOFT_HLUTNM of \SI_VALUE[29]_i_1\ : label is "soft_lutpair49";
  attribute SOFT_HLUTNM of \SI_VALUE[30]_i_1\ : label is "soft_lutpair50";
  attribute SOFT_HLUTNM of \SI_VALUE[31]_i_1\ : label is "soft_lutpair51";
  attribute SOFT_HLUTNM of \SI_VALUE[32]_i_1\ : label is "soft_lutpair39";
  attribute SOFT_HLUTNM of \SI_VALUE[33]_i_1\ : label is "soft_lutpair38";
  attribute SOFT_HLUTNM of \SI_VALUE[34]_i_2\ : label is "soft_lutpair37";
  attribute SOFT_HLUTNM of \SI_VALUE[35]_i_1\ : label is "soft_lutpair34";
  attribute SOFT_HLUTNM of \SI_VALUE[37]_i_1\ : label is "soft_lutpair43";
  attribute SOFT_HLUTNM of \SI_VALUE[3]_i_1\ : label is "soft_lutpair59";
  attribute SOFT_HLUTNM of \SI_VALUE[4]_i_1\ : label is "soft_lutpair60";
  attribute SOFT_HLUTNM of \SI_VALUE[5]_i_1\ : label is "soft_lutpair59";
  attribute SOFT_HLUTNM of \SI_VALUE[6]_i_1\ : label is "soft_lutpair33";
  attribute SOFT_HLUTNM of \SI_VALUE[70]_i_1\ : label is "soft_lutpair33";
  attribute SOFT_HLUTNM of \SI_VALUE[71]_i_1\ : label is "soft_lutpair32";
  attribute SOFT_HLUTNM of \SI_VALUE[72]_i_1\ : label is "soft_lutpair35";
  attribute SOFT_HLUTNM of \SI_VALUE[7]_i_1\ : label is "soft_lutpair32";
  attribute SOFT_HLUTNM of \SI_VALUE[8]_i_1\ : label is "soft_lutpair35";
  attribute KEEP_HIERARCHY : string;
  attribute KEEP_HIERARCHY of S_MULT_reg : label is "yes";
begin
  CO(0) <= \^co\(0);
  P(0) <= \^p\(0);
  SI_VALUE0(127 downto 0) <= \^si_value0\(127 downto 0);
  \S_CONV_COUNTER_reg[0]\ <= \^s_conv_counter_reg[0]\;
  \S_ENABLE_reg[0]\ <= \^s_enable_reg[0]\;
  \S_ENABLE_reg[0]_0\ <= \^s_enable_reg[0]_0\;
  \S_SAMPLE_TIME_COUNTER_reg[11]\ <= \^s_sample_time_counter_reg[11]\;
  \S_SAMPLE_TIME_COUNTER_reg[17]\ <= \^s_sample_time_counter_reg[17]\;
  \S_SAMPLE_TIME_COUNTER_reg[23]\ <= \^s_sample_time_counter_reg[23]\;
  \curstate_reg[0]\ <= \^curstate_reg[0]\;
RAW_VALID_i_2: unisim.vcomponents.LUT6
    generic map(
      INIT => X"1055105510555555"
    )
        port map (
      I0 => RAW_VALID_i_3_n_0,
      I1 => ENABLE,
      I2 => \^co\(0),
      I3 => SI_VALID_reg(0),
      I4 => \^s_sample_time_counter_reg[11]\,
      I5 => SI_VALID_i_6_n_0,
      O => \^s_enable_reg[0]_0\
    );
RAW_VALID_i_3: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FF2200F0"
    )
        port map (
      I0 => SI_VALID_reg_0(1),
      I1 => SI_VALID_reg_0(0),
      I2 => ENABLE,
      I3 => SI_VALID_reg(0),
      I4 => SI_VALID_reg(1),
      O => RAW_VALID_i_3_n_0
    );
SI_VALID_i_10: unisim.vcomponents.LUT4
    generic map(
      INIT => X"22B2"
    )
        port map (
      I0 => SI_VALID_reg_i_3_2(4),
      I1 => nxtstate3(28),
      I2 => SI_VALID_reg_i_3_2(3),
      I3 => nxtstate3(27),
      O => SI_VALID_i_10_n_0
    );
SI_VALID_i_11: unisim.vcomponents.LUT4
    generic map(
      INIT => X"22B2"
    )
        port map (
      I0 => SI_VALID_reg_i_3_2(2),
      I1 => nxtstate3(26),
      I2 => SI_VALID_reg_i_3_2(1),
      I3 => nxtstate3(25),
      O => SI_VALID_i_11_n_0
    );
SI_VALID_i_12: unisim.vcomponents.LUT4
    generic map(
      INIT => X"22B2"
    )
        port map (
      I0 => SI_VALID_reg_i_3_2(0),
      I1 => nxtstate3(24),
      I2 => SI_VALID_reg_i_3_1(7),
      I3 => nxtstate3(23),
      O => SI_VALID_i_12_n_0
    );
SI_VALID_i_13: unisim.vcomponents.LUT4
    generic map(
      INIT => X"22B2"
    )
        port map (
      I0 => SI_VALID_reg_i_3_1(6),
      I1 => nxtstate3(22),
      I2 => SI_VALID_reg_i_3_1(5),
      I3 => nxtstate3(21),
      O => SI_VALID_i_13_n_0
    );
SI_VALID_i_14: unisim.vcomponents.LUT4
    generic map(
      INIT => X"22B2"
    )
        port map (
      I0 => SI_VALID_reg_i_3_1(4),
      I1 => nxtstate3(20),
      I2 => SI_VALID_reg_i_3_1(3),
      I3 => nxtstate3(19),
      O => SI_VALID_i_14_n_0
    );
SI_VALID_i_15: unisim.vcomponents.LUT4
    generic map(
      INIT => X"22B2"
    )
        port map (
      I0 => SI_VALID_reg_i_3_1(2),
      I1 => nxtstate3(18),
      I2 => SI_VALID_reg_i_3_1(1),
      I3 => nxtstate3(17),
      O => SI_VALID_i_15_n_0
    );
SI_VALID_i_16: unisim.vcomponents.LUT4
    generic map(
      INIT => X"22B2"
    )
        port map (
      I0 => SI_VALID_reg_i_3_1(0),
      I1 => nxtstate3(16),
      I2 => SI_VALID_reg_i_3_0(7),
      I3 => nxtstate3(15),
      O => SI_VALID_i_16_n_0
    );
SI_VALID_i_17: unisim.vcomponents.LUT4
    generic map(
      INIT => X"6006"
    )
        port map (
      I0 => SI_VALID_reg_i_3_2(6),
      I1 => SI_VALID_reg_i_3_3(0),
      I2 => nxtstate3(29),
      I3 => SI_VALID_reg_i_3_2(5),
      O => SI_VALID_i_17_n_0
    );
SI_VALID_i_18: unisim.vcomponents.LUT4
    generic map(
      INIT => X"9009"
    )
        port map (
      I0 => nxtstate3(28),
      I1 => SI_VALID_reg_i_3_2(4),
      I2 => nxtstate3(27),
      I3 => SI_VALID_reg_i_3_2(3),
      O => SI_VALID_i_18_n_0
    );
SI_VALID_i_19: unisim.vcomponents.LUT4
    generic map(
      INIT => X"9009"
    )
        port map (
      I0 => nxtstate3(26),
      I1 => SI_VALID_reg_i_3_2(2),
      I2 => nxtstate3(25),
      I3 => SI_VALID_reg_i_3_2(1),
      O => SI_VALID_i_19_n_0
    );
SI_VALID_i_2: unisim.vcomponents.LUT6
    generic map(
      INIT => X"00000000FFFFFF4F"
    )
        port map (
      I0 => ENABLE,
      I1 => \^co\(0),
      I2 => \^curstate_reg[0]\,
      I3 => \^s_sample_time_counter_reg[11]\,
      I4 => SI_VALID_i_6_n_0,
      I5 => SI_VALID_i_7_n_0,
      O => \^s_enable_reg[0]\
    );
SI_VALID_i_20: unisim.vcomponents.LUT4
    generic map(
      INIT => X"9009"
    )
        port map (
      I0 => nxtstate3(24),
      I1 => SI_VALID_reg_i_3_2(0),
      I2 => nxtstate3(23),
      I3 => SI_VALID_reg_i_3_1(7),
      O => SI_VALID_i_20_n_0
    );
SI_VALID_i_21: unisim.vcomponents.LUT4
    generic map(
      INIT => X"9009"
    )
        port map (
      I0 => nxtstate3(22),
      I1 => SI_VALID_reg_i_3_1(6),
      I2 => nxtstate3(21),
      I3 => SI_VALID_reg_i_3_1(5),
      O => SI_VALID_i_21_n_0
    );
SI_VALID_i_22: unisim.vcomponents.LUT4
    generic map(
      INIT => X"9009"
    )
        port map (
      I0 => nxtstate3(20),
      I1 => SI_VALID_reg_i_3_1(4),
      I2 => nxtstate3(19),
      I3 => SI_VALID_reg_i_3_1(3),
      O => SI_VALID_i_22_n_0
    );
SI_VALID_i_23: unisim.vcomponents.LUT4
    generic map(
      INIT => X"9009"
    )
        port map (
      I0 => nxtstate3(18),
      I1 => SI_VALID_reg_i_3_1(2),
      I2 => nxtstate3(17),
      I3 => SI_VALID_reg_i_3_1(1),
      O => SI_VALID_i_23_n_0
    );
SI_VALID_i_24: unisim.vcomponents.LUT4
    generic map(
      INIT => X"9009"
    )
        port map (
      I0 => nxtstate3(16),
      I1 => SI_VALID_reg_i_3_1(0),
      I2 => nxtstate3(15),
      I3 => SI_VALID_reg_i_3_0(7),
      O => SI_VALID_i_24_n_0
    );
SI_VALID_i_25: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FFFE"
    )
        port map (
      I0 => \S_SAMPLE_TIME_COUNTER[30]_i_7\(9),
      I1 => \S_SAMPLE_TIME_COUNTER[30]_i_7\(12),
      I2 => \S_SAMPLE_TIME_COUNTER[30]_i_7\(0),
      I3 => \S_SAMPLE_TIME_COUNTER[30]_i_7\(20),
      O => SI_VALID_i_25_n_0
    );
SI_VALID_i_26: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FFFE"
    )
        port map (
      I0 => \S_SAMPLE_TIME_COUNTER[30]_i_7\(13),
      I1 => \S_SAMPLE_TIME_COUNTER[30]_i_7\(14),
      I2 => \S_SAMPLE_TIME_COUNTER[30]_i_7\(4),
      I3 => \S_SAMPLE_TIME_COUNTER[30]_i_7\(16),
      O => SI_VALID_i_26_n_0
    );
SI_VALID_i_27: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FFFE"
    )
        port map (
      I0 => \S_SAMPLE_TIME_COUNTER[30]_i_7\(5),
      I1 => \S_SAMPLE_TIME_COUNTER[30]_i_7\(7),
      I2 => \S_SAMPLE_TIME_COUNTER[30]_i_7\(8),
      I3 => \S_SAMPLE_TIME_COUNTER[30]_i_7\(15),
      O => SI_VALID_i_27_n_0
    );
SI_VALID_i_28: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FFFE"
    )
        port map (
      I0 => \S_SAMPLE_TIME_COUNTER[30]_i_7\(23),
      I1 => \S_SAMPLE_TIME_COUNTER[30]_i_7\(28),
      I2 => \S_SAMPLE_TIME_COUNTER[30]_i_7\(2),
      I3 => \S_SAMPLE_TIME_COUNTER[30]_i_7\(30),
      O => \^s_sample_time_counter_reg[23]\
    );
SI_VALID_i_29: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FFFE"
    )
        port map (
      I0 => \S_SAMPLE_TIME_COUNTER[30]_i_7\(10),
      I1 => \S_SAMPLE_TIME_COUNTER[30]_i_7\(24),
      I2 => \S_SAMPLE_TIME_COUNTER[30]_i_7\(18),
      I3 => \S_SAMPLE_TIME_COUNTER[30]_i_7\(22),
      O => SI_VALID_i_29_n_0
    );
SI_VALID_i_30: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FFFE"
    )
        port map (
      I0 => \S_SAMPLE_TIME_COUNTER[30]_i_7\(17),
      I1 => \S_SAMPLE_TIME_COUNTER[30]_i_7\(25),
      I2 => \S_SAMPLE_TIME_COUNTER[30]_i_7\(3),
      I3 => \S_SAMPLE_TIME_COUNTER[30]_i_7\(29),
      O => \^s_sample_time_counter_reg[17]\
    );
SI_VALID_i_31: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FFFE"
    )
        port map (
      I0 => \S_SAMPLE_TIME_COUNTER[30]_i_7\(6),
      I1 => \S_SAMPLE_TIME_COUNTER[30]_i_7\(26),
      I2 => \S_SAMPLE_TIME_COUNTER[30]_i_7\(19),
      I3 => \S_SAMPLE_TIME_COUNTER[30]_i_7\(27),
      O => SI_VALID_i_31_n_0
    );
SI_VALID_i_32: unisim.vcomponents.LUT4
    generic map(
      INIT => X"0001"
    )
        port map (
      I0 => \SI_VALUE_reg[34]\(2),
      I1 => \SI_VALUE_reg[34]\(3),
      I2 => \SI_VALUE_reg[209]_0\,
      I3 => \SI_VALUE_reg[209]\,
      O => SI_VALID_i_32_n_0
    );
SI_VALID_i_33: unisim.vcomponents.LUT4
    generic map(
      INIT => X"22B2"
    )
        port map (
      I0 => SI_VALID_reg_i_3_0(6),
      I1 => nxtstate3(14),
      I2 => SI_VALID_reg_i_3_0(5),
      I3 => nxtstate3(13),
      O => SI_VALID_i_33_n_0
    );
SI_VALID_i_34: unisim.vcomponents.LUT4
    generic map(
      INIT => X"22B2"
    )
        port map (
      I0 => SI_VALID_reg_i_3_0(4),
      I1 => nxtstate3(12),
      I2 => SI_VALID_reg_i_3_0(3),
      I3 => nxtstate3(11),
      O => SI_VALID_i_34_n_0
    );
SI_VALID_i_35: unisim.vcomponents.LUT4
    generic map(
      INIT => X"22B2"
    )
        port map (
      I0 => SI_VALID_reg_i_3_0(2),
      I1 => nxtstate3(10),
      I2 => SI_VALID_reg_i_3_0(1),
      I3 => nxtstate3(9),
      O => SI_VALID_i_35_n_0
    );
SI_VALID_i_36: unisim.vcomponents.LUT4
    generic map(
      INIT => X"22B2"
    )
        port map (
      I0 => SI_VALID_reg_i_3_0(0),
      I1 => nxtstate3(8),
      I2 => S(7),
      I3 => nxtstate3(7),
      O => SI_VALID_i_36_n_0
    );
SI_VALID_i_37: unisim.vcomponents.LUT4
    generic map(
      INIT => X"22B2"
    )
        port map (
      I0 => S(6),
      I1 => nxtstate3(6),
      I2 => S(5),
      I3 => nxtstate3(5),
      O => SI_VALID_i_37_n_0
    );
SI_VALID_i_38: unisim.vcomponents.LUT4
    generic map(
      INIT => X"22B2"
    )
        port map (
      I0 => S(4),
      I1 => nxtstate3(4),
      I2 => S(3),
      I3 => nxtstate3(3),
      O => SI_VALID_i_38_n_0
    );
SI_VALID_i_39: unisim.vcomponents.LUT4
    generic map(
      INIT => X"22B2"
    )
        port map (
      I0 => S(2),
      I1 => nxtstate3(2),
      I2 => S(1),
      I3 => nxtstate3(1),
      O => SI_VALID_i_39_n_0
    );
SI_VALID_i_4: unisim.vcomponents.LUT2
    generic map(
      INIT => X"2"
    )
        port map (
      I0 => SI_VALID_reg(0),
      I1 => SI_VALID_reg(1),
      O => \^curstate_reg[0]\
    );
SI_VALID_i_40: unisim.vcomponents.LUT4
    generic map(
      INIT => X"B222"
    )
        port map (
      I0 => S(0),
      I1 => nxtstate3(0),
      I2 => SI_VALID_reg_i_8_1,
      I3 => SI_VALID_reg_i_8_0(0),
      O => SI_VALID_i_40_n_0
    );
SI_VALID_i_41: unisim.vcomponents.LUT4
    generic map(
      INIT => X"9009"
    )
        port map (
      I0 => nxtstate3(14),
      I1 => SI_VALID_reg_i_3_0(6),
      I2 => nxtstate3(13),
      I3 => SI_VALID_reg_i_3_0(5),
      O => SI_VALID_i_41_n_0
    );
SI_VALID_i_42: unisim.vcomponents.LUT4
    generic map(
      INIT => X"9009"
    )
        port map (
      I0 => nxtstate3(12),
      I1 => SI_VALID_reg_i_3_0(4),
      I2 => nxtstate3(11),
      I3 => SI_VALID_reg_i_3_0(3),
      O => SI_VALID_i_42_n_0
    );
SI_VALID_i_43: unisim.vcomponents.LUT4
    generic map(
      INIT => X"9009"
    )
        port map (
      I0 => nxtstate3(10),
      I1 => SI_VALID_reg_i_3_0(2),
      I2 => nxtstate3(9),
      I3 => SI_VALID_reg_i_3_0(1),
      O => SI_VALID_i_43_n_0
    );
SI_VALID_i_44: unisim.vcomponents.LUT4
    generic map(
      INIT => X"9009"
    )
        port map (
      I0 => nxtstate3(8),
      I1 => SI_VALID_reg_i_3_0(0),
      I2 => nxtstate3(7),
      I3 => S(7),
      O => SI_VALID_i_44_n_0
    );
SI_VALID_i_45: unisim.vcomponents.LUT4
    generic map(
      INIT => X"9009"
    )
        port map (
      I0 => nxtstate3(6),
      I1 => S(6),
      I2 => nxtstate3(5),
      I3 => S(5),
      O => SI_VALID_i_45_n_0
    );
SI_VALID_i_46: unisim.vcomponents.LUT4
    generic map(
      INIT => X"9009"
    )
        port map (
      I0 => nxtstate3(4),
      I1 => S(4),
      I2 => nxtstate3(3),
      I3 => S(3),
      O => SI_VALID_i_46_n_0
    );
SI_VALID_i_47: unisim.vcomponents.LUT4
    generic map(
      INIT => X"9009"
    )
        port map (
      I0 => nxtstate3(2),
      I1 => S(2),
      I2 => nxtstate3(1),
      I3 => S(1),
      O => SI_VALID_i_47_n_0
    );
SI_VALID_i_48: unisim.vcomponents.LUT4
    generic map(
      INIT => X"6006"
    )
        port map (
      I0 => SI_VALID_reg_i_8_0(0),
      I1 => SI_VALID_reg_i_8_1,
      I2 => nxtstate3(0),
      I3 => S(0),
      O => SI_VALID_i_48_n_0
    );
SI_VALID_i_5: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFFFFFFFFFFFFFE"
    )
        port map (
      I0 => SI_VALID_i_25_n_0,
      I1 => SI_VALID_i_26_n_0,
      I2 => SI_VALID_i_27_n_0,
      I3 => \S_SAMPLE_TIME_COUNTER[30]_i_7\(11),
      I4 => \S_SAMPLE_TIME_COUNTER[30]_i_7\(1),
      I5 => \S_SAMPLE_TIME_COUNTER[30]_i_7\(21),
      O => \^s_sample_time_counter_reg[11]\
    );
SI_VALID_i_6: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FFFE"
    )
        port map (
      I0 => \^s_sample_time_counter_reg[23]\,
      I1 => SI_VALID_i_29_n_0,
      I2 => \^s_sample_time_counter_reg[17]\,
      I3 => SI_VALID_i_31_n_0,
      O => SI_VALID_i_6_n_0
    );
SI_VALID_i_7: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0000DF00FF00DF00"
    )
        port map (
      I0 => S_DUMMY_SAMPLE,
      I1 => SI_VALID_reg_0(0),
      I2 => SI_VALID_reg_0(1),
      I3 => SI_VALID_reg(1),
      I4 => SI_VALID_reg(0),
      I5 => SI_VALID_i_32_n_0,
      O => SI_VALID_i_7_n_0
    );
SI_VALID_i_9: unisim.vcomponents.LUT4
    generic map(
      INIT => X"1171"
    )
        port map (
      I0 => SI_VALID_reg_i_3_3(0),
      I1 => SI_VALID_reg_i_3_2(6),
      I2 => SI_VALID_reg_i_3_2(5),
      I3 => nxtstate3(29),
      O => SI_VALID_i_9_n_0
    );
SI_VALID_reg_i_3: unisim.vcomponents.CARRY8
     port map (
      CI => SI_VALID_reg_i_8_n_0,
      CI_TOP => '0',
      CO(7) => \^co\(0),
      CO(6) => SI_VALID_reg_i_3_n_1,
      CO(5) => SI_VALID_reg_i_3_n_2,
      CO(4) => SI_VALID_reg_i_3_n_3,
      CO(3) => SI_VALID_reg_i_3_n_4,
      CO(2) => SI_VALID_reg_i_3_n_5,
      CO(1) => SI_VALID_reg_i_3_n_6,
      CO(0) => SI_VALID_reg_i_3_n_7,
      DI(7) => SI_VALID_i_9_n_0,
      DI(6) => SI_VALID_i_10_n_0,
      DI(5) => SI_VALID_i_11_n_0,
      DI(4) => SI_VALID_i_12_n_0,
      DI(3) => SI_VALID_i_13_n_0,
      DI(2) => SI_VALID_i_14_n_0,
      DI(1) => SI_VALID_i_15_n_0,
      DI(0) => SI_VALID_i_16_n_0,
      O(7 downto 0) => NLW_SI_VALID_reg_i_3_O_UNCONNECTED(7 downto 0),
      S(7) => SI_VALID_i_17_n_0,
      S(6) => SI_VALID_i_18_n_0,
      S(5) => SI_VALID_i_19_n_0,
      S(4) => SI_VALID_i_20_n_0,
      S(3) => SI_VALID_i_21_n_0,
      S(2) => SI_VALID_i_22_n_0,
      S(1) => SI_VALID_i_23_n_0,
      S(0) => SI_VALID_i_24_n_0
    );
SI_VALID_reg_i_8: unisim.vcomponents.CARRY8
     port map (
      CI => '1',
      CI_TOP => '0',
      CO(7) => SI_VALID_reg_i_8_n_0,
      CO(6) => SI_VALID_reg_i_8_n_1,
      CO(5) => SI_VALID_reg_i_8_n_2,
      CO(4) => SI_VALID_reg_i_8_n_3,
      CO(3) => SI_VALID_reg_i_8_n_4,
      CO(2) => SI_VALID_reg_i_8_n_5,
      CO(1) => SI_VALID_reg_i_8_n_6,
      CO(0) => SI_VALID_reg_i_8_n_7,
      DI(7) => SI_VALID_i_33_n_0,
      DI(6) => SI_VALID_i_34_n_0,
      DI(5) => SI_VALID_i_35_n_0,
      DI(4) => SI_VALID_i_36_n_0,
      DI(3) => SI_VALID_i_37_n_0,
      DI(2) => SI_VALID_i_38_n_0,
      DI(1) => SI_VALID_i_39_n_0,
      DI(0) => SI_VALID_i_40_n_0,
      O(7 downto 0) => NLW_SI_VALID_reg_i_8_O_UNCONNECTED(7 downto 0),
      S(7) => SI_VALID_i_41_n_0,
      S(6) => SI_VALID_i_42_n_0,
      S(5) => SI_VALID_i_43_n_0,
      S(4) => SI_VALID_i_44_n_0,
      S(3) => SI_VALID_i_45_n_0,
      S(2) => SI_VALID_i_46_n_0,
      S(1) => SI_VALID_i_47_n_0,
      S(0) => SI_VALID_i_48_n_0
    );
\SI_VALUE[0]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"00010000"
    )
        port map (
      I0 => \SI_VALUE_reg[34]\(3),
      I1 => \SI_VALUE_reg[34]\(2),
      I2 => \SI_VALUE_reg[34]\(1),
      I3 => \SI_VALUE_reg[34]\(0),
      I4 => S_RESULT_S_C(0),
      O => \^si_value0\(0)
    );
\SI_VALUE[105]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0101100001011333"
    )
        port map (
      I0 => \SI_VALUE[105]_i_2_n_0\,
      I1 => \SI_VALUE_reg[34]\(3),
      I2 => \SI_VALUE_reg[209]_0\,
      I3 => \SI_VALUE_reg[209]\,
      I4 => \SI_VALUE_reg[34]\(2),
      I5 => \SI_VALUE[177]_i_2_n_0\,
      O => \^si_value0\(47)
    );
\SI_VALUE[105]_i_2\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FF7CFF7F"
    )
        port map (
      I0 => S_RESULT_S_C(0),
      I1 => \SI_VALUE_reg[209]\,
      I2 => \SI_VALUE_reg[209]_0\,
      I3 => \SI_VALUE_reg[34]\(2),
      I4 => S_RESULT_S_C(1),
      O => \SI_VALUE[105]_i_2_n_0\
    );
\SI_VALUE[106]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0101100001011333"
    )
        port map (
      I0 => \SI_VALUE[106]_i_2_n_0\,
      I1 => \SI_VALUE_reg[34]\(3),
      I2 => \SI_VALUE_reg[209]_0\,
      I3 => \SI_VALUE_reg[209]\,
      I4 => \SI_VALUE_reg[34]\(2),
      I5 => \SI_VALUE[106]_i_3_n_0\,
      O => \^si_value0\(48)
    );
\SI_VALUE[106]_i_2\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"F3BEFFBE"
    )
        port map (
      I0 => \SI_VALUE[2]_i_2_n_0\,
      I1 => \SI_VALUE_reg[209]_0\,
      I2 => \SI_VALUE_reg[209]\,
      I3 => \SI_VALUE_reg[34]\(2),
      I4 => S_RESULT_S_C(0),
      O => \SI_VALUE[106]_i_2_n_0\
    );
\SI_VALUE[106]_i_3\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"AFEBA028"
    )
        port map (
      I0 => \SI_VALUE[142]_i_5_n_0\,
      I1 => \SI_VALUE_reg[209]_0\,
      I2 => \SI_VALUE_reg[34]\(2),
      I3 => \SI_VALUE_reg[209]\,
      I4 => \SI_VALUE[142]_i_6_n_0\,
      O => \SI_VALUE[106]_i_3_n_0\
    );
\SI_VALUE[107]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0101100001011333"
    )
        port map (
      I0 => \SI_VALUE[211]_i_2_n_0\,
      I1 => \SI_VALUE_reg[34]\(3),
      I2 => \SI_VALUE_reg[209]_0\,
      I3 => \SI_VALUE_reg[209]\,
      I4 => \SI_VALUE_reg[34]\(2),
      I5 => \SI_VALUE[107]_i_2_n_0\,
      O => \^si_value0\(49)
    );
\SI_VALUE[107]_i_2\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"AFEBA028"
    )
        port map (
      I0 => \SI_VALUE[175]_i_4_n_0\,
      I1 => \SI_VALUE_reg[209]_0\,
      I2 => \SI_VALUE_reg[34]\(2),
      I3 => \SI_VALUE_reg[209]\,
      I4 => \SI_VALUE[175]_i_5_n_0\,
      O => \SI_VALUE[107]_i_2_n_0\
    );
\SI_VALUE[108]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0101100001011333"
    )
        port map (
      I0 => \SI_VALUE[212]_i_2_n_0\,
      I1 => \SI_VALUE_reg[34]\(3),
      I2 => \SI_VALUE_reg[209]_0\,
      I3 => \SI_VALUE_reg[209]\,
      I4 => \SI_VALUE_reg[34]\(2),
      I5 => \SI_VALUE[140]_i_2_n_0\,
      O => \^si_value0\(50)
    );
\SI_VALUE[109]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0101100001011333"
    )
        port map (
      I0 => \SI_VALUE[141]_i_2_n_0\,
      I1 => \SI_VALUE_reg[34]\(3),
      I2 => \SI_VALUE_reg[209]_0\,
      I3 => \SI_VALUE_reg[209]\,
      I4 => \SI_VALUE_reg[34]\(2),
      I5 => \SI_VALUE[141]_i_3_n_0\,
      O => \^si_value0\(51)
    );
\SI_VALUE[10]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"4000000040000003"
    )
        port map (
      I0 => \SI_VALUE[106]_i_2_n_0\,
      I1 => \SI_VALUE_reg[34]\(3),
      I2 => \SI_VALUE_reg[209]_0\,
      I3 => \SI_VALUE_reg[209]\,
      I4 => \SI_VALUE_reg[34]\(2),
      I5 => \SI_VALUE[106]_i_3_n_0\,
      O => \^si_value0\(10)
    );
\SI_VALUE[110]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0101100001011333"
    )
        port map (
      I0 => \SI_VALUE[142]_i_2_n_0\,
      I1 => \SI_VALUE_reg[34]\(3),
      I2 => \SI_VALUE_reg[209]_0\,
      I3 => \SI_VALUE_reg[209]\,
      I4 => \SI_VALUE_reg[34]\(2),
      I5 => \SI_VALUE[142]_i_3_n_0\,
      O => \^si_value0\(52)
    );
\SI_VALUE[111]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0101100001011333"
    )
        port map (
      I0 => \SI_VALUE[175]_i_2_n_0\,
      I1 => \SI_VALUE_reg[34]\(3),
      I2 => \SI_VALUE_reg[209]_0\,
      I3 => \SI_VALUE_reg[209]\,
      I4 => \SI_VALUE_reg[34]\(2),
      I5 => \SI_VALUE[175]_i_3_n_0\,
      O => \^si_value0\(53)
    );
\SI_VALUE[112]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0101100001011333"
    )
        port map (
      I0 => \SI_VALUE[176]_i_2_n_0\,
      I1 => \SI_VALUE_reg[34]\(3),
      I2 => \SI_VALUE_reg[209]_0\,
      I3 => \SI_VALUE_reg[209]\,
      I4 => \SI_VALUE_reg[34]\(2),
      I5 => \SI_VALUE[176]_i_3_n_0\,
      O => \^si_value0\(54)
    );
\SI_VALUE[113]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0101100001011333"
    )
        port map (
      I0 => \SI_VALUE[177]_i_2_n_0\,
      I1 => \SI_VALUE_reg[34]\(3),
      I2 => \SI_VALUE_reg[209]_0\,
      I3 => \SI_VALUE_reg[209]\,
      I4 => \SI_VALUE_reg[34]\(2),
      I5 => \SI_VALUE[177]_i_3_n_0\,
      O => \^si_value0\(55)
    );
\SI_VALUE[114]_i_1\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => \SI_VALUE_reg[34]\(3),
      I1 => \SI_VALUE[178]_i_2_n_0\,
      O => \^si_value0\(56)
    );
\SI_VALUE[115]_i_1\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => \SI_VALUE_reg[34]\(3),
      I1 => \SI_VALUE[179]_i_2_n_0\,
      O => \^si_value0\(57)
    );
\SI_VALUE[116]_i_1\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => \SI_VALUE_reg[34]\(3),
      I1 => \SI_VALUE[180]_i_2_n_0\,
      O => \^si_value0\(58)
    );
\SI_VALUE[117]_i_1\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => \SI_VALUE_reg[34]\(3),
      I1 => \SI_VALUE[245]_i_2_n_0\,
      O => \^si_value0\(59)
    );
\SI_VALUE[118]_i_1\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => \SI_VALUE_reg[34]\(3),
      I1 => \SI_VALUE[246]_i_2_n_0\,
      O => \^si_value0\(60)
    );
\SI_VALUE[119]_i_1\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => \SI_VALUE_reg[34]\(3),
      I1 => \SI_VALUE[247]_i_2_n_0\,
      O => \^si_value0\(61)
    );
\SI_VALUE[11]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"4000000040000003"
    )
        port map (
      I0 => \SI_VALUE[211]_i_2_n_0\,
      I1 => \SI_VALUE_reg[34]\(3),
      I2 => \SI_VALUE_reg[209]_0\,
      I3 => \SI_VALUE_reg[209]\,
      I4 => \SI_VALUE_reg[34]\(2),
      I5 => \SI_VALUE[107]_i_2_n_0\,
      O => \^si_value0\(11)
    );
\SI_VALUE[120]_i_1\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => \SI_VALUE_reg[34]\(3),
      I1 => \SI_VALUE[248]_i_2_n_0\,
      O => \^si_value0\(62)
    );
\SI_VALUE[121]_i_1\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => \SI_VALUE_reg[34]\(3),
      I1 => \SI_VALUE[249]_i_2_n_0\,
      O => \^si_value0\(63)
    );
\SI_VALUE[122]_i_1\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => \SI_VALUE_reg[34]\(3),
      I1 => \SI_VALUE[250]_i_2_n_0\,
      O => \^si_value0\(64)
    );
\SI_VALUE[123]_i_1\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => \SI_VALUE_reg[34]\(3),
      I1 => \SI_VALUE[251]_i_2_n_0\,
      O => \^si_value0\(65)
    );
\SI_VALUE[124]_i_1\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => \SI_VALUE_reg[34]\(3),
      I1 => \SI_VALUE[252]_i_2_n_0\,
      O => \^si_value0\(66)
    );
\SI_VALUE[125]_i_1\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => \SI_VALUE_reg[34]\(3),
      I1 => \SI_VALUE[253]_i_2_n_0\,
      O => \^si_value0\(67)
    );
\SI_VALUE[126]_i_1\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => \SI_VALUE_reg[34]\(3),
      I1 => \SI_VALUE[254]_i_2_n_0\,
      O => \^si_value0\(68)
    );
\SI_VALUE[127]_i_1\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => \SI_VALUE_reg[34]\(3),
      I1 => \SI_VALUE[255]_i_2_n_0\,
      O => \^si_value0\(69)
    );
\SI_VALUE[128]_i_1\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => \SI_VALUE_reg[34]\(3),
      I1 => \SI_VALUE[256]_i_2_n_0\,
      O => \^si_value0\(70)
    );
\SI_VALUE[129]_i_1\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => \SI_VALUE_reg[34]\(3),
      I1 => \SI_VALUE[257]_i_2_n_0\,
      O => \^si_value0\(71)
    );
\SI_VALUE[12]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"4000000040000003"
    )
        port map (
      I0 => \SI_VALUE[212]_i_2_n_0\,
      I1 => \SI_VALUE_reg[34]\(3),
      I2 => \SI_VALUE_reg[209]_0\,
      I3 => \SI_VALUE_reg[209]\,
      I4 => \SI_VALUE_reg[34]\(2),
      I5 => \SI_VALUE[140]_i_2_n_0\,
      O => \^si_value0\(12)
    );
\SI_VALUE[130]_i_1\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => \SI_VALUE[258]_i_2_n_0\,
      I1 => \SI_VALUE_reg[34]\(3),
      O => \^si_value0\(72)
    );
\SI_VALUE[131]_i_1\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => \SI_VALUE[259]_i_2_n_0\,
      I1 => \SI_VALUE_reg[34]\(3),
      O => \^si_value0\(73)
    );
\SI_VALUE[132]_i_1\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => \SI_VALUE[260]_i_2_n_0\,
      I1 => \SI_VALUE_reg[34]\(3),
      O => \^si_value0\(74)
    );
\SI_VALUE[133]_i_1\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => \SI_VALUE[261]_i_2_n_0\,
      I1 => \SI_VALUE_reg[34]\(3),
      O => \^si_value0\(75)
    );
\SI_VALUE[134]_i_1\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => \SI_VALUE[262]_i_2_n_0\,
      I1 => \SI_VALUE_reg[34]\(3),
      O => \^si_value0\(76)
    );
\SI_VALUE[135]_i_1\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => \SI_VALUE[263]_i_2_n_0\,
      I1 => \SI_VALUE_reg[34]\(3),
      O => \^si_value0\(77)
    );
\SI_VALUE[136]_i_1\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => \SI_VALUE[264]_i_2_n_0\,
      I1 => \SI_VALUE_reg[34]\(3),
      O => \^si_value0\(78)
    );
\SI_VALUE[137]_i_1\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => \SI_VALUE[265]_i_2_n_0\,
      I1 => \SI_VALUE_reg[34]\(3),
      O => \^si_value0\(79)
    );
\SI_VALUE[138]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"000000005030503F"
    )
        port map (
      I0 => \SI_VALUE[274]_i_3_n_0\,
      I1 => \SI_VALUE[266]_i_2_n_0\,
      I2 => \SI_VALUE_reg[273]\,
      I3 => \SI_VALUE_reg[273]_0\,
      I4 => \SI_VALUE[274]_i_2_n_0\,
      I5 => \SI_VALUE_reg[34]\(3),
      O => \^si_value0\(80)
    );
\SI_VALUE[139]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"000000005030503F"
    )
        port map (
      I0 => \SI_VALUE[275]_i_3_n_0\,
      I1 => \SI_VALUE[267]_i_2_n_0\,
      I2 => \SI_VALUE_reg[273]\,
      I3 => \SI_VALUE_reg[273]_0\,
      I4 => \SI_VALUE[275]_i_2_n_0\,
      I5 => \SI_VALUE_reg[34]\(3),
      O => \^si_value0\(81)
    );
\SI_VALUE[13]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"4000000040000003"
    )
        port map (
      I0 => \SI_VALUE[141]_i_2_n_0\,
      I1 => \SI_VALUE_reg[34]\(3),
      I2 => \SI_VALUE_reg[209]_0\,
      I3 => \SI_VALUE_reg[209]\,
      I4 => \SI_VALUE_reg[34]\(2),
      I5 => \SI_VALUE[141]_i_3_n_0\,
      O => \^si_value0\(13)
    );
\SI_VALUE[140]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"414110004D4DD333"
    )
        port map (
      I0 => \SI_VALUE[212]_i_2_n_0\,
      I1 => \SI_VALUE_reg[34]\(3),
      I2 => \SI_VALUE_reg[209]_0\,
      I3 => \SI_VALUE_reg[209]\,
      I4 => \SI_VALUE_reg[34]\(2),
      I5 => \SI_VALUE[140]_i_2_n_0\,
      O => \^si_value0\(44)
    );
\SI_VALUE[140]_i_2\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"AFEBA028"
    )
        port map (
      I0 => \SI_VALUE[176]_i_4_n_0\,
      I1 => \SI_VALUE_reg[209]_0\,
      I2 => \SI_VALUE_reg[34]\(2),
      I3 => \SI_VALUE_reg[209]\,
      I4 => \SI_VALUE[176]_i_5_n_0\,
      O => \SI_VALUE[140]_i_2_n_0\
    );
\SI_VALUE[141]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"414110004D4DD333"
    )
        port map (
      I0 => \SI_VALUE[141]_i_2_n_0\,
      I1 => \SI_VALUE_reg[34]\(3),
      I2 => \SI_VALUE_reg[209]_0\,
      I3 => \SI_VALUE_reg[209]\,
      I4 => \SI_VALUE_reg[34]\(2),
      I5 => \SI_VALUE[141]_i_3_n_0\,
      O => \^si_value0\(45)
    );
\SI_VALUE[141]_i_2\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"AFEBA028"
    )
        port map (
      I0 => \SI_VALUE[141]_i_4_n_0\,
      I1 => \SI_VALUE_reg[209]_0\,
      I2 => \SI_VALUE_reg[34]\(2),
      I3 => \SI_VALUE_reg[209]\,
      I4 => \SI_VALUE[177]_i_4_n_0\,
      O => \SI_VALUE[141]_i_2_n_0\
    );
\SI_VALUE[141]_i_3\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"AFEBA028"
    )
        port map (
      I0 => \SI_VALUE[177]_i_5_n_0\,
      I1 => \SI_VALUE_reg[209]_0\,
      I2 => \SI_VALUE_reg[34]\(2),
      I3 => \SI_VALUE_reg[209]\,
      I4 => \SI_VALUE[177]_i_6_n_0\,
      O => \SI_VALUE[141]_i_3_n_0\
    );
\SI_VALUE[141]_i_4\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"C0FFFF55FFFFFF55"
    )
        port map (
      I0 => S_RESULT_S_C(1),
      I1 => \SI_VALUE_reg[34]\(2),
      I2 => \SI_VALUE_reg[34]\(3),
      I3 => \SI_VALUE_reg[209]_0\,
      I4 => \SI_VALUE_reg[209]\,
      I5 => S_RESULT_S_C(0),
      O => \SI_VALUE[141]_i_4_n_0\
    );
\SI_VALUE[142]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"414110004D4DD333"
    )
        port map (
      I0 => \SI_VALUE[142]_i_2_n_0\,
      I1 => \SI_VALUE_reg[34]\(3),
      I2 => \SI_VALUE_reg[209]_0\,
      I3 => \SI_VALUE_reg[209]\,
      I4 => \SI_VALUE_reg[34]\(2),
      I5 => \SI_VALUE[142]_i_3_n_0\,
      O => \^si_value0\(46)
    );
\SI_VALUE[142]_i_2\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"AFEBA028"
    )
        port map (
      I0 => \SI_VALUE[142]_i_4_n_0\,
      I1 => \SI_VALUE_reg[209]_0\,
      I2 => \SI_VALUE_reg[34]\(2),
      I3 => \SI_VALUE_reg[209]\,
      I4 => \SI_VALUE[142]_i_5_n_0\,
      O => \SI_VALUE[142]_i_2_n_0\
    );
\SI_VALUE[142]_i_3\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"AFEBA028"
    )
        port map (
      I0 => \SI_VALUE[142]_i_6_n_0\,
      I1 => \SI_VALUE_reg[209]_0\,
      I2 => \SI_VALUE_reg[34]\(2),
      I3 => \SI_VALUE_reg[209]\,
      I4 => \SI_VALUE[266]_i_3_n_0\,
      O => \SI_VALUE[142]_i_3_n_0\
    );
\SI_VALUE[142]_i_4\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFF1CDCFFFF1FDF"
    )
        port map (
      I0 => S_RESULT_S_C(0),
      I1 => \SI_VALUE_reg[209]\,
      I2 => \SI_VALUE_reg[209]_0\,
      I3 => S_RESULT_S_C(1),
      I4 => \SI_VALUE_reg[279]\,
      I5 => S_RESULT_S_C(2),
      O => \SI_VALUE[142]_i_4_n_0\
    );
\SI_VALUE[142]_i_5\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFCFDDFF00CFDD00"
    )
        port map (
      I0 => S_RESULT_S_C(3),
      I1 => \SI_VALUE_reg[279]\,
      I2 => S_RESULT_S_C(4),
      I3 => \SI_VALUE_reg[209]\,
      I4 => \SI_VALUE_reg[209]_0\,
      I5 => \SI_VALUE[142]_i_7_n_0\,
      O => \SI_VALUE[142]_i_5_n_0\
    );
\SI_VALUE[142]_i_6\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFCFDDFF00CFDD00"
    )
        port map (
      I0 => S_RESULT_S_C(7),
      I1 => \SI_VALUE_reg[279]\,
      I2 => S_RESULT_S_C(8),
      I3 => \SI_VALUE_reg[209]\,
      I4 => \SI_VALUE_reg[209]_0\,
      I5 => \SI_VALUE[142]_i_8_n_0\,
      O => \SI_VALUE[142]_i_6_n_0\
    );
\SI_VALUE[142]_i_7\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"C4444444F7777777"
    )
        port map (
      I0 => S_RESULT_S_C(5),
      I1 => \SI_VALUE_reg[209]\,
      I2 => \SI_VALUE_reg[209]_0\,
      I3 => \SI_VALUE_reg[34]\(3),
      I4 => \SI_VALUE_reg[34]\(2),
      I5 => S_RESULT_S_C(6),
      O => \SI_VALUE[142]_i_7_n_0\
    );
\SI_VALUE[142]_i_8\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"C4444444F7777777"
    )
        port map (
      I0 => S_RESULT_S_C(9),
      I1 => \SI_VALUE_reg[209]\,
      I2 => \SI_VALUE_reg[209]_0\,
      I3 => \SI_VALUE_reg[34]\(3),
      I4 => \SI_VALUE_reg[34]\(2),
      I5 => S_RESULT_S_C(10),
      O => \SI_VALUE[142]_i_8_n_0\
    );
\SI_VALUE[14]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"4000000040000003"
    )
        port map (
      I0 => \SI_VALUE[142]_i_2_n_0\,
      I1 => \SI_VALUE_reg[34]\(3),
      I2 => \SI_VALUE_reg[209]_0\,
      I3 => \SI_VALUE_reg[209]\,
      I4 => \SI_VALUE_reg[34]\(2),
      I5 => \SI_VALUE[142]_i_3_n_0\,
      O => \^si_value0\(14)
    );
\SI_VALUE[15]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"4000000040000003"
    )
        port map (
      I0 => \SI_VALUE[175]_i_2_n_0\,
      I1 => \SI_VALUE_reg[34]\(3),
      I2 => \SI_VALUE_reg[209]_0\,
      I3 => \SI_VALUE_reg[209]\,
      I4 => \SI_VALUE_reg[34]\(2),
      I5 => \SI_VALUE[175]_i_3_n_0\,
      O => \^si_value0\(15)
    );
\SI_VALUE[16]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"4000000040000003"
    )
        port map (
      I0 => \SI_VALUE[176]_i_2_n_0\,
      I1 => \SI_VALUE_reg[34]\(3),
      I2 => \SI_VALUE_reg[209]_0\,
      I3 => \SI_VALUE_reg[209]\,
      I4 => \SI_VALUE_reg[34]\(2),
      I5 => \SI_VALUE[176]_i_3_n_0\,
      O => \^si_value0\(16)
    );
\SI_VALUE[175]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"414110004D4DD333"
    )
        port map (
      I0 => \SI_VALUE[175]_i_2_n_0\,
      I1 => \SI_VALUE_reg[34]\(3),
      I2 => \SI_VALUE_reg[209]_0\,
      I3 => \SI_VALUE_reg[209]\,
      I4 => \SI_VALUE_reg[34]\(2),
      I5 => \SI_VALUE[175]_i_3_n_0\,
      O => \^si_value0\(82)
    );
\SI_VALUE[175]_i_2\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"AFEBA028"
    )
        port map (
      I0 => \SI_VALUE[211]_i_3_n_0\,
      I1 => \SI_VALUE_reg[209]_0\,
      I2 => \SI_VALUE_reg[34]\(2),
      I3 => \SI_VALUE_reg[209]\,
      I4 => \SI_VALUE[175]_i_4_n_0\,
      O => \SI_VALUE[175]_i_2_n_0\
    );
\SI_VALUE[175]_i_3\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"AFEBA028"
    )
        port map (
      I0 => \SI_VALUE[175]_i_5_n_0\,
      I1 => \SI_VALUE_reg[209]_0\,
      I2 => \SI_VALUE_reg[34]\(2),
      I3 => \SI_VALUE_reg[209]\,
      I4 => \SI_VALUE[267]_i_3_n_0\,
      O => \SI_VALUE[175]_i_3_n_0\
    );
\SI_VALUE[175]_i_4\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFCFDDFF00CFDD00"
    )
        port map (
      I0 => S_RESULT_S_C(4),
      I1 => \SI_VALUE_reg[279]\,
      I2 => S_RESULT_S_C(5),
      I3 => \SI_VALUE_reg[209]\,
      I4 => \SI_VALUE_reg[209]_0\,
      I5 => \SI_VALUE[175]_i_6_n_0\,
      O => \SI_VALUE[175]_i_4_n_0\
    );
\SI_VALUE[175]_i_5\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFCFDDFF00CFDD00"
    )
        port map (
      I0 => S_RESULT_S_C(8),
      I1 => \SI_VALUE_reg[279]\,
      I2 => S_RESULT_S_C(9),
      I3 => \SI_VALUE_reg[209]\,
      I4 => \SI_VALUE_reg[209]_0\,
      I5 => \SI_VALUE[175]_i_7_n_0\,
      O => \SI_VALUE[175]_i_5_n_0\
    );
\SI_VALUE[175]_i_6\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"C4444444F7777777"
    )
        port map (
      I0 => S_RESULT_S_C(6),
      I1 => \SI_VALUE_reg[209]\,
      I2 => \SI_VALUE_reg[209]_0\,
      I3 => \SI_VALUE_reg[34]\(3),
      I4 => \SI_VALUE_reg[34]\(2),
      I5 => S_RESULT_S_C(7),
      O => \SI_VALUE[175]_i_6_n_0\
    );
\SI_VALUE[175]_i_7\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"C4444444F7777777"
    )
        port map (
      I0 => S_RESULT_S_C(10),
      I1 => \SI_VALUE_reg[209]\,
      I2 => \SI_VALUE_reg[209]_0\,
      I3 => \SI_VALUE_reg[34]\(3),
      I4 => \SI_VALUE_reg[34]\(2),
      I5 => S_RESULT_S_C(11),
      O => \SI_VALUE[175]_i_7_n_0\
    );
\SI_VALUE[176]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"414110004D4DD333"
    )
        port map (
      I0 => \SI_VALUE[176]_i_2_n_0\,
      I1 => \SI_VALUE_reg[34]\(3),
      I2 => \SI_VALUE_reg[209]_0\,
      I3 => \SI_VALUE_reg[209]\,
      I4 => \SI_VALUE_reg[34]\(2),
      I5 => \SI_VALUE[176]_i_3_n_0\,
      O => \^si_value0\(83)
    );
\SI_VALUE[176]_i_2\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"AFEBA028"
    )
        port map (
      I0 => \SI_VALUE[212]_i_3_n_0\,
      I1 => \SI_VALUE_reg[209]_0\,
      I2 => \SI_VALUE_reg[34]\(2),
      I3 => \SI_VALUE_reg[209]\,
      I4 => \SI_VALUE[176]_i_4_n_0\,
      O => \SI_VALUE[176]_i_2_n_0\
    );
\SI_VALUE[176]_i_3\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"AFEBA028"
    )
        port map (
      I0 => \SI_VALUE[176]_i_5_n_0\,
      I1 => \SI_VALUE_reg[209]_0\,
      I2 => \SI_VALUE_reg[34]\(2),
      I3 => \SI_VALUE_reg[209]\,
      I4 => \SI_VALUE[268]_i_4_n_0\,
      O => \SI_VALUE[176]_i_3_n_0\
    );
\SI_VALUE[176]_i_4\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFCFDDFF00CFDD00"
    )
        port map (
      I0 => S_RESULT_S_C(5),
      I1 => \SI_VALUE_reg[279]\,
      I2 => S_RESULT_S_C(6),
      I3 => \SI_VALUE_reg[209]\,
      I4 => \SI_VALUE_reg[209]_0\,
      I5 => \SI_VALUE[176]_i_6_n_0\,
      O => \SI_VALUE[176]_i_4_n_0\
    );
\SI_VALUE[176]_i_5\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFCFDDFF00CFDD00"
    )
        port map (
      I0 => S_RESULT_S_C(9),
      I1 => \SI_VALUE_reg[279]\,
      I2 => S_RESULT_S_C(10),
      I3 => \SI_VALUE_reg[209]\,
      I4 => \SI_VALUE_reg[209]_0\,
      I5 => \SI_VALUE[176]_i_7_n_0\,
      O => \SI_VALUE[176]_i_5_n_0\
    );
\SI_VALUE[176]_i_6\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"C4444444F7777777"
    )
        port map (
      I0 => S_RESULT_S_C(7),
      I1 => \SI_VALUE_reg[209]\,
      I2 => \SI_VALUE_reg[209]_0\,
      I3 => \SI_VALUE_reg[34]\(3),
      I4 => \SI_VALUE_reg[34]\(2),
      I5 => S_RESULT_S_C(8),
      O => \SI_VALUE[176]_i_6_n_0\
    );
\SI_VALUE[176]_i_7\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"C4444444F7777777"
    )
        port map (
      I0 => S_RESULT_S_C(11),
      I1 => \SI_VALUE_reg[209]\,
      I2 => \SI_VALUE_reg[209]_0\,
      I3 => \SI_VALUE_reg[34]\(3),
      I4 => \SI_VALUE_reg[34]\(2),
      I5 => S_RESULT_S_C(12),
      O => \SI_VALUE[176]_i_7_n_0\
    );
\SI_VALUE[177]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"414110004D4DD333"
    )
        port map (
      I0 => \SI_VALUE[177]_i_2_n_0\,
      I1 => \SI_VALUE_reg[34]\(3),
      I2 => \SI_VALUE_reg[209]_0\,
      I3 => \SI_VALUE_reg[209]\,
      I4 => \SI_VALUE_reg[34]\(2),
      I5 => \SI_VALUE[177]_i_3_n_0\,
      O => \^si_value0\(84)
    );
\SI_VALUE[177]_i_2\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"AFEBA028"
    )
        port map (
      I0 => \SI_VALUE[177]_i_4_n_0\,
      I1 => \SI_VALUE_reg[209]_0\,
      I2 => \SI_VALUE_reg[34]\(2),
      I3 => \SI_VALUE_reg[209]\,
      I4 => \SI_VALUE[177]_i_5_n_0\,
      O => \SI_VALUE[177]_i_2_n_0\
    );
\SI_VALUE[177]_i_3\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"AFEBA028"
    )
        port map (
      I0 => \SI_VALUE[177]_i_6_n_0\,
      I1 => \SI_VALUE_reg[209]_0\,
      I2 => \SI_VALUE_reg[34]\(2),
      I3 => \SI_VALUE_reg[209]\,
      I4 => \SI_VALUE[269]_i_4_n_0\,
      O => \SI_VALUE[177]_i_3_n_0\
    );
\SI_VALUE[177]_i_4\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFCFDDFF00CFDD00"
    )
        port map (
      I0 => S_RESULT_S_C(2),
      I1 => \SI_VALUE_reg[279]\,
      I2 => S_RESULT_S_C(3),
      I3 => \SI_VALUE_reg[209]\,
      I4 => \SI_VALUE_reg[209]_0\,
      I5 => \SI_VALUE[177]_i_7_n_0\,
      O => \SI_VALUE[177]_i_4_n_0\
    );
\SI_VALUE[177]_i_5\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFCFDDFF00CFDD00"
    )
        port map (
      I0 => S_RESULT_S_C(6),
      I1 => \SI_VALUE_reg[279]\,
      I2 => S_RESULT_S_C(7),
      I3 => \SI_VALUE_reg[209]\,
      I4 => \SI_VALUE_reg[209]_0\,
      I5 => \SI_VALUE[177]_i_8_n_0\,
      O => \SI_VALUE[177]_i_5_n_0\
    );
\SI_VALUE[177]_i_6\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFCFDDFF00CFDD00"
    )
        port map (
      I0 => S_RESULT_S_C(10),
      I1 => \SI_VALUE_reg[279]\,
      I2 => S_RESULT_S_C(11),
      I3 => \SI_VALUE_reg[209]\,
      I4 => \SI_VALUE_reg[209]_0\,
      I5 => \SI_VALUE[177]_i_9_n_0\,
      O => \SI_VALUE[177]_i_6_n_0\
    );
\SI_VALUE[177]_i_7\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"C4444444F7777777"
    )
        port map (
      I0 => S_RESULT_S_C(4),
      I1 => \SI_VALUE_reg[209]\,
      I2 => \SI_VALUE_reg[209]_0\,
      I3 => \SI_VALUE_reg[34]\(3),
      I4 => \SI_VALUE_reg[34]\(2),
      I5 => S_RESULT_S_C(5),
      O => \SI_VALUE[177]_i_7_n_0\
    );
\SI_VALUE[177]_i_8\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"C4444444F7777777"
    )
        port map (
      I0 => S_RESULT_S_C(8),
      I1 => \SI_VALUE_reg[209]\,
      I2 => \SI_VALUE_reg[209]_0\,
      I3 => \SI_VALUE_reg[34]\(3),
      I4 => \SI_VALUE_reg[34]\(2),
      I5 => S_RESULT_S_C(9),
      O => \SI_VALUE[177]_i_8_n_0\
    );
\SI_VALUE[177]_i_9\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"C4444444F7777777"
    )
        port map (
      I0 => S_RESULT_S_C(12),
      I1 => \SI_VALUE_reg[209]\,
      I2 => \SI_VALUE_reg[209]_0\,
      I3 => \SI_VALUE_reg[34]\(3),
      I4 => \SI_VALUE_reg[34]\(2),
      I5 => S_RESULT_S_C(13),
      O => \SI_VALUE[177]_i_9_n_0\
    );
\SI_VALUE[178]_i_1\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => \SI_VALUE[178]_i_2_n_0\,
      O => \^si_value0\(85)
    );
\SI_VALUE[178]_i_2\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"0000FFB8"
    )
        port map (
      I0 => \SI_VALUE[266]_i_2_n_0\,
      I1 => \SI_VALUE_reg[273]_0\,
      I2 => \SI_VALUE[106]_i_3_n_0\,
      I3 => \SI_VALUE_reg[273]\,
      I4 => \^si_value0\(91),
      O => \SI_VALUE[178]_i_2_n_0\
    );
\SI_VALUE[179]_i_1\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => \SI_VALUE[179]_i_2_n_0\,
      O => \^si_value0\(86)
    );
\SI_VALUE[179]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFB80000FFB8FFB8"
    )
        port map (
      I0 => \SI_VALUE[267]_i_2_n_0\,
      I1 => \SI_VALUE_reg[273]_0\,
      I2 => \SI_VALUE[107]_i_2_n_0\,
      I3 => \SI_VALUE_reg[273]\,
      I4 => \SI_VALUE[211]_i_2_n_0\,
      I5 => \SI_VALUE_reg[115]\,
      O => \SI_VALUE[179]_i_2_n_0\
    );
\SI_VALUE[17]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"4000000040000003"
    )
        port map (
      I0 => \SI_VALUE[177]_i_2_n_0\,
      I1 => \SI_VALUE_reg[34]\(3),
      I2 => \SI_VALUE_reg[209]_0\,
      I3 => \SI_VALUE_reg[209]\,
      I4 => \SI_VALUE_reg[34]\(2),
      I5 => \SI_VALUE[177]_i_3_n_0\,
      O => \^si_value0\(17)
    );
\SI_VALUE[180]_i_1\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => \SI_VALUE[180]_i_2_n_0\,
      O => \^si_value0\(87)
    );
\SI_VALUE[180]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFB80000FFB8FFB8"
    )
        port map (
      I0 => \SI_VALUE[268]_i_2_n_0\,
      I1 => \SI_VALUE_reg[273]_0\,
      I2 => \SI_VALUE[140]_i_2_n_0\,
      I3 => \SI_VALUE_reg[273]\,
      I4 => \SI_VALUE[212]_i_2_n_0\,
      I5 => \SI_VALUE_reg[115]\,
      O => \SI_VALUE[180]_i_2_n_0\
    );
\SI_VALUE[18]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"40000101"
    )
        port map (
      I0 => \SI_VALUE[178]_i_2_n_0\,
      I1 => \SI_VALUE_reg[34]\(1),
      I2 => \SI_VALUE_reg[34]\(2),
      I3 => \SI_VALUE_reg[34]\(3),
      I4 => \SI_VALUE_reg[34]\(0),
      O => \^si_value0\(18)
    );
\SI_VALUE[19]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"40000101"
    )
        port map (
      I0 => \SI_VALUE[179]_i_2_n_0\,
      I1 => \SI_VALUE_reg[34]\(1),
      I2 => \SI_VALUE_reg[34]\(2),
      I3 => \SI_VALUE_reg[34]\(3),
      I4 => \SI_VALUE_reg[34]\(0),
      O => \^si_value0\(19)
    );
\SI_VALUE[1]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"00010000"
    )
        port map (
      I0 => \SI_VALUE_reg[34]\(2),
      I1 => \SI_VALUE_reg[34]\(0),
      I2 => \SI_VALUE_reg[34]\(1),
      I3 => \SI_VALUE_reg[34]\(3),
      I4 => S_RESULT_S_C(1),
      O => \^si_value0\(1)
    );
\SI_VALUE[207]_i_1\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => \SI_VALUE[207]_i_2_n_0\,
      O => \S_RESULT_COUNTER_reg[0]_rep\
    );
\SI_VALUE[207]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"C4444444F7777777"
    )
        port map (
      I0 => S_RESULT_S_C(32),
      I1 => \SI_VALUE_reg[209]\,
      I2 => \SI_VALUE_reg[209]_0\,
      I3 => \SI_VALUE_reg[34]\(3),
      I4 => \SI_VALUE_reg[34]\(2),
      I5 => \^p\(0),
      O => \SI_VALUE[207]_i_2_n_0\
    );
\SI_VALUE[209]_i_2\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"02000000"
    )
        port map (
      I0 => S_RESULT_S_C(34),
      I1 => \SI_VALUE_reg[34]\(3),
      I2 => \SI_VALUE_reg[209]_0\,
      I3 => \SI_VALUE_reg[209]\,
      I4 => \SI_VALUE_reg[34]\(2),
      O => \^si_value0\(90)
    );
\SI_VALUE[20]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"40000101"
    )
        port map (
      I0 => \SI_VALUE[180]_i_2_n_0\,
      I1 => \SI_VALUE_reg[34]\(1),
      I2 => \SI_VALUE_reg[34]\(2),
      I3 => \SI_VALUE_reg[34]\(3),
      I4 => \SI_VALUE_reg[34]\(0),
      O => \^si_value0\(20)
    );
\SI_VALUE[210]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"00080000"
    )
        port map (
      I0 => S_RESULT_S_C(0),
      I1 => \SI_VALUE_reg[34]\(2),
      I2 => \SI_VALUE_reg[34]\(3),
      I3 => \SI_VALUE_reg[209]\,
      I4 => \SI_VALUE_reg[209]_0\,
      O => \^si_value0\(91)
    );
\SI_VALUE[211]_i_1\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => \SI_VALUE[211]_i_2_n_0\,
      O => \^si_value0\(92)
    );
\SI_VALUE[211]_i_2\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FF9C"
    )
        port map (
      I0 => \SI_VALUE_reg[209]\,
      I1 => \SI_VALUE_reg[34]\(2),
      I2 => \SI_VALUE_reg[209]_0\,
      I3 => \SI_VALUE[211]_i_3_n_0\,
      O => \SI_VALUE[211]_i_2_n_0\
    );
\SI_VALUE[211]_i_3\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFCFDDFF00CFDD00"
    )
        port map (
      I0 => S_RESULT_S_C(0),
      I1 => \SI_VALUE_reg[279]\,
      I2 => S_RESULT_S_C(1),
      I3 => \SI_VALUE_reg[209]\,
      I4 => \SI_VALUE_reg[209]_0\,
      I5 => \SI_VALUE[211]_i_4_n_0\,
      O => \SI_VALUE[211]_i_3_n_0\
    );
\SI_VALUE[211]_i_4\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"C4444444F7777777"
    )
        port map (
      I0 => S_RESULT_S_C(2),
      I1 => \SI_VALUE_reg[209]\,
      I2 => \SI_VALUE_reg[209]_0\,
      I3 => \SI_VALUE_reg[34]\(3),
      I4 => \SI_VALUE_reg[34]\(2),
      I5 => S_RESULT_S_C(3),
      O => \SI_VALUE[211]_i_4_n_0\
    );
\SI_VALUE[212]_i_1\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => \SI_VALUE[212]_i_2_n_0\,
      O => \^si_value0\(36)
    );
\SI_VALUE[212]_i_2\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFDFF01C"
    )
        port map (
      I0 => S_RESULT_S_C(0),
      I1 => \SI_VALUE_reg[209]_0\,
      I2 => \SI_VALUE_reg[34]\(2),
      I3 => \SI_VALUE_reg[209]\,
      I4 => \SI_VALUE[212]_i_3_n_0\,
      O => \SI_VALUE[212]_i_2_n_0\
    );
\SI_VALUE[212]_i_3\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFCFDDFF00CFDD00"
    )
        port map (
      I0 => S_RESULT_S_C(1),
      I1 => \SI_VALUE_reg[279]\,
      I2 => S_RESULT_S_C(2),
      I3 => \SI_VALUE_reg[209]\,
      I4 => \SI_VALUE_reg[209]_0\,
      I5 => \SI_VALUE[212]_i_4_n_0\,
      O => \SI_VALUE[212]_i_3_n_0\
    );
\SI_VALUE[212]_i_4\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"C4444444F7777777"
    )
        port map (
      I0 => S_RESULT_S_C(3),
      I1 => \SI_VALUE_reg[209]\,
      I2 => \SI_VALUE_reg[209]_0\,
      I3 => \SI_VALUE_reg[34]\(3),
      I4 => \SI_VALUE_reg[34]\(2),
      I5 => S_RESULT_S_C(4),
      O => \SI_VALUE[212]_i_4_n_0\
    );
\SI_VALUE[21]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"40000101"
    )
        port map (
      I0 => \SI_VALUE[245]_i_2_n_0\,
      I1 => \SI_VALUE_reg[34]\(1),
      I2 => \SI_VALUE_reg[34]\(2),
      I3 => \SI_VALUE_reg[34]\(3),
      I4 => \SI_VALUE_reg[34]\(0),
      O => \^si_value0\(21)
    );
\SI_VALUE[223]_i_1\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => \SI_VALUE[255]_i_2_n_0\,
      O => \^si_value0\(88)
    );
\SI_VALUE[224]_i_1\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => \SI_VALUE[256]_i_2_n_0\,
      O => \^si_value0\(89)
    );
\SI_VALUE[22]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"40000101"
    )
        port map (
      I0 => \SI_VALUE[246]_i_2_n_0\,
      I1 => \SI_VALUE_reg[34]\(1),
      I2 => \SI_VALUE_reg[34]\(2),
      I3 => \SI_VALUE_reg[34]\(3),
      I4 => \SI_VALUE_reg[34]\(0),
      O => \^si_value0\(22)
    );
\SI_VALUE[23]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"40000101"
    )
        port map (
      I0 => \SI_VALUE[247]_i_2_n_0\,
      I1 => \SI_VALUE_reg[34]\(1),
      I2 => \SI_VALUE_reg[34]\(2),
      I3 => \SI_VALUE_reg[34]\(3),
      I4 => \SI_VALUE_reg[34]\(0),
      O => \^si_value0\(23)
    );
\SI_VALUE[245]_i_1\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => \SI_VALUE[245]_i_2_n_0\,
      O => \^si_value0\(93)
    );
\SI_VALUE[245]_i_2\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"B8FFB8CC"
    )
        port map (
      I0 => \SI_VALUE[141]_i_2_n_0\,
      I1 => \SI_VALUE_reg[273]\,
      I2 => \SI_VALUE[269]_i_2_n_0\,
      I3 => \SI_VALUE_reg[273]_0\,
      I4 => \SI_VALUE[141]_i_3_n_0\,
      O => \SI_VALUE[245]_i_2_n_0\
    );
\SI_VALUE[246]_i_1\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => \SI_VALUE[246]_i_2_n_0\,
      O => \^si_value0\(94)
    );
\SI_VALUE[246]_i_2\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"B8FFB8CC"
    )
        port map (
      I0 => \SI_VALUE[142]_i_2_n_0\,
      I1 => \SI_VALUE_reg[273]\,
      I2 => \SI_VALUE[270]_i_2_n_0\,
      I3 => \SI_VALUE_reg[273]_0\,
      I4 => \SI_VALUE[142]_i_3_n_0\,
      O => \SI_VALUE[246]_i_2_n_0\
    );
\SI_VALUE[247]_i_1\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => \SI_VALUE[247]_i_2_n_0\,
      O => \^si_value0\(95)
    );
\SI_VALUE[247]_i_2\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"B8FFB8CC"
    )
        port map (
      I0 => \SI_VALUE[175]_i_2_n_0\,
      I1 => \SI_VALUE_reg[273]\,
      I2 => \SI_VALUE[271]_i_2_n_0\,
      I3 => \SI_VALUE_reg[273]_0\,
      I4 => \SI_VALUE[175]_i_3_n_0\,
      O => \SI_VALUE[247]_i_2_n_0\
    );
\SI_VALUE[248]_i_1\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => \SI_VALUE[248]_i_2_n_0\,
      O => \^si_value0\(96)
    );
\SI_VALUE[248]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => \SI_VALUE[176]_i_2_n_0\,
      I1 => \SI_VALUE[248]_i_3_n_0\,
      I2 => \SI_VALUE_reg[273]\,
      I3 => \SI_VALUE[272]_i_3_n_0\,
      I4 => \SI_VALUE_reg[273]_0\,
      I5 => \SI_VALUE[176]_i_3_n_0\,
      O => \SI_VALUE[248]_i_2_n_0\
    );
\SI_VALUE[248]_i_3\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FFFD"
    )
        port map (
      I0 => S_RESULT_S_C(0),
      I1 => \SI_VALUE_reg[209]\,
      I2 => \SI_VALUE_reg[209]_0\,
      I3 => \SI_VALUE_reg[34]\(2),
      O => \SI_VALUE[248]_i_3_n_0\
    );
\SI_VALUE[249]_i_1\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => \SI_VALUE[249]_i_2_n_0\,
      O => \^si_value0\(97)
    );
\SI_VALUE[249]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => \SI_VALUE[177]_i_2_n_0\,
      I1 => \SI_VALUE[105]_i_2_n_0\,
      I2 => \SI_VALUE_reg[273]\,
      I3 => \SI_VALUE[273]_i_5_n_0\,
      I4 => \SI_VALUE_reg[273]_0\,
      I5 => \SI_VALUE[177]_i_3_n_0\,
      O => \SI_VALUE[249]_i_2_n_0\
    );
\SI_VALUE[24]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"40000001"
    )
        port map (
      I0 => \SI_VALUE[248]_i_2_n_0\,
      I1 => \SI_VALUE_reg[34]\(1),
      I2 => \SI_VALUE_reg[34]\(2),
      I3 => \SI_VALUE_reg[34]\(3),
      I4 => \SI_VALUE_reg[34]\(0),
      O => \^si_value0\(24)
    );
\SI_VALUE[250]_i_1\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => \SI_VALUE[250]_i_2_n_0\,
      O => \^si_value0\(98)
    );
\SI_VALUE[250]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => \SI_VALUE[106]_i_3_n_0\,
      I1 => \SI_VALUE[106]_i_2_n_0\,
      I2 => \SI_VALUE_reg[273]\,
      I3 => \SI_VALUE[274]_i_3_n_0\,
      I4 => \SI_VALUE_reg[273]_0\,
      I5 => \SI_VALUE[266]_i_2_n_0\,
      O => \SI_VALUE[250]_i_2_n_0\
    );
\SI_VALUE[251]_i_1\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => \SI_VALUE[251]_i_2_n_0\,
      O => \^si_value0\(99)
    );
\SI_VALUE[251]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => \SI_VALUE[107]_i_2_n_0\,
      I1 => \SI_VALUE[211]_i_2_n_0\,
      I2 => \SI_VALUE_reg[273]\,
      I3 => \SI_VALUE[275]_i_3_n_0\,
      I4 => \SI_VALUE_reg[273]_0\,
      I5 => \SI_VALUE[267]_i_2_n_0\,
      O => \SI_VALUE[251]_i_2_n_0\
    );
\SI_VALUE[252]_i_1\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => \SI_VALUE[252]_i_2_n_0\,
      O => \^si_value0\(100)
    );
\SI_VALUE[252]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => \SI_VALUE[140]_i_2_n_0\,
      I1 => \SI_VALUE[212]_i_2_n_0\,
      I2 => \SI_VALUE_reg[273]\,
      I3 => \SI_VALUE[276]_i_3_n_0\,
      I4 => \SI_VALUE_reg[273]_0\,
      I5 => \SI_VALUE[268]_i_2_n_0\,
      O => \SI_VALUE[252]_i_2_n_0\
    );
\SI_VALUE[253]_i_1\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => \SI_VALUE[253]_i_2_n_0\,
      O => \^si_value0\(101)
    );
\SI_VALUE[253]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => \SI_VALUE[141]_i_3_n_0\,
      I1 => \SI_VALUE[141]_i_2_n_0\,
      I2 => \SI_VALUE_reg[273]\,
      I3 => \SI_VALUE[277]_i_3_n_0\,
      I4 => \SI_VALUE_reg[273]_0\,
      I5 => \SI_VALUE[269]_i_2_n_0\,
      O => \SI_VALUE[253]_i_2_n_0\
    );
\SI_VALUE[254]_i_1\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => \SI_VALUE[254]_i_2_n_0\,
      O => \^si_value0\(102)
    );
\SI_VALUE[254]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => \SI_VALUE[142]_i_3_n_0\,
      I1 => \SI_VALUE[142]_i_2_n_0\,
      I2 => \SI_VALUE_reg[273]\,
      I3 => \SI_VALUE[278]_i_3_n_0\,
      I4 => \SI_VALUE_reg[273]_0\,
      I5 => \SI_VALUE[270]_i_2_n_0\,
      O => \SI_VALUE[254]_i_2_n_0\
    );
\SI_VALUE[255]_i_1\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"7"
    )
        port map (
      I0 => \SI_VALUE[271]_i_3_n_0\,
      I1 => \SI_VALUE[255]_i_2_n_0\,
      O => \^si_value0\(123)
    );
\SI_VALUE[255]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => \SI_VALUE[175]_i_3_n_0\,
      I1 => \SI_VALUE[175]_i_2_n_0\,
      I2 => \SI_VALUE_reg[273]\,
      I3 => \SI_VALUE[279]_i_5_n_0\,
      I4 => \SI_VALUE_reg[273]_0\,
      I5 => \SI_VALUE[271]_i_2_n_0\,
      O => \SI_VALUE[255]_i_2_n_0\
    );
\SI_VALUE[256]_i_1\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"7"
    )
        port map (
      I0 => \SI_VALUE[272]_i_4_n_0\,
      I1 => \SI_VALUE[256]_i_2_n_0\,
      O => \^si_value0\(124)
    );
\SI_VALUE[256]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => \SI_VALUE[176]_i_3_n_0\,
      I1 => \SI_VALUE[176]_i_2_n_0\,
      I2 => \SI_VALUE_reg[273]\,
      I3 => \SI_VALUE[272]_i_2_n_0\,
      I4 => \SI_VALUE_reg[273]_0\,
      I5 => \SI_VALUE[272]_i_3_n_0\,
      O => \SI_VALUE[256]_i_2_n_0\
    );
\SI_VALUE[257]_i_1\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => \SI_VALUE[257]_i_2_n_0\,
      O => \^si_value0\(103)
    );
\SI_VALUE[257]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => \SI_VALUE[177]_i_3_n_0\,
      I1 => \SI_VALUE[177]_i_2_n_0\,
      I2 => \SI_VALUE_reg[273]\,
      I3 => \SI_VALUE[273]_i_3_n_0\,
      I4 => \SI_VALUE_reg[273]_0\,
      I5 => \SI_VALUE[273]_i_5_n_0\,
      O => \SI_VALUE[257]_i_2_n_0\
    );
\SI_VALUE[258]_i_1\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => \SI_VALUE[258]_i_2_n_0\,
      O => \^si_value0\(104)
    );
\SI_VALUE[258]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => \SI_VALUE[266]_i_2_n_0\,
      I1 => \SI_VALUE[106]_i_3_n_0\,
      I2 => \SI_VALUE_reg[273]\,
      I3 => \SI_VALUE[274]_i_2_n_0\,
      I4 => \SI_VALUE_reg[273]_0\,
      I5 => \SI_VALUE[274]_i_3_n_0\,
      O => \SI_VALUE[258]_i_2_n_0\
    );
\SI_VALUE[259]_i_1\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => \SI_VALUE[259]_i_2_n_0\,
      O => \^si_value0\(105)
    );
\SI_VALUE[259]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => \SI_VALUE[267]_i_2_n_0\,
      I1 => \SI_VALUE[107]_i_2_n_0\,
      I2 => \SI_VALUE_reg[273]\,
      I3 => \SI_VALUE[275]_i_2_n_0\,
      I4 => \SI_VALUE_reg[273]_0\,
      I5 => \SI_VALUE[275]_i_3_n_0\,
      O => \SI_VALUE[259]_i_2_n_0\
    );
\SI_VALUE[25]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"40000001"
    )
        port map (
      I0 => \SI_VALUE[249]_i_2_n_0\,
      I1 => \SI_VALUE_reg[34]\(1),
      I2 => \SI_VALUE_reg[34]\(2),
      I3 => \SI_VALUE_reg[34]\(3),
      I4 => \SI_VALUE_reg[34]\(0),
      O => \^si_value0\(25)
    );
\SI_VALUE[260]_i_1\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => \SI_VALUE[260]_i_2_n_0\,
      O => \^si_value0\(106)
    );
\SI_VALUE[260]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => \SI_VALUE[268]_i_2_n_0\,
      I1 => \SI_VALUE[140]_i_2_n_0\,
      I2 => \SI_VALUE_reg[273]\,
      I3 => \SI_VALUE[276]_i_2_n_0\,
      I4 => \SI_VALUE_reg[273]_0\,
      I5 => \SI_VALUE[276]_i_3_n_0\,
      O => \SI_VALUE[260]_i_2_n_0\
    );
\SI_VALUE[261]_i_1\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => \SI_VALUE[261]_i_2_n_0\,
      O => \^si_value0\(107)
    );
\SI_VALUE[261]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => \SI_VALUE[269]_i_2_n_0\,
      I1 => \SI_VALUE[141]_i_3_n_0\,
      I2 => \SI_VALUE_reg[273]\,
      I3 => \SI_VALUE[277]_i_2_n_0\,
      I4 => \SI_VALUE_reg[273]_0\,
      I5 => \SI_VALUE[277]_i_3_n_0\,
      O => \SI_VALUE[261]_i_2_n_0\
    );
\SI_VALUE[262]_i_1\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => \SI_VALUE[262]_i_2_n_0\,
      O => \^si_value0\(108)
    );
\SI_VALUE[262]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => \SI_VALUE[270]_i_2_n_0\,
      I1 => \SI_VALUE[142]_i_3_n_0\,
      I2 => \SI_VALUE_reg[273]\,
      I3 => \SI_VALUE[262]_i_3_n_0\,
      I4 => \SI_VALUE_reg[273]_0\,
      I5 => \SI_VALUE[278]_i_3_n_0\,
      O => \SI_VALUE[262]_i_2_n_0\
    );
\SI_VALUE[262]_i_3\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"BEAF"
    )
        port map (
      I0 => \SI_VALUE[278]_i_2_n_0\,
      I1 => \SI_VALUE_reg[209]\,
      I2 => \SI_VALUE_reg[34]\(2),
      I3 => \SI_VALUE_reg[209]_0\,
      O => \SI_VALUE[262]_i_3_n_0\
    );
\SI_VALUE[263]_i_1\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => \SI_VALUE[263]_i_2_n_0\,
      O => \^si_value0\(109)
    );
\SI_VALUE[263]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => \SI_VALUE[271]_i_2_n_0\,
      I1 => \SI_VALUE[175]_i_3_n_0\,
      I2 => \SI_VALUE_reg[273]\,
      I3 => \SI_VALUE[263]_i_3_n_0\,
      I4 => \SI_VALUE_reg[273]_0\,
      I5 => \SI_VALUE[279]_i_5_n_0\,
      O => \SI_VALUE[263]_i_2_n_0\
    );
\SI_VALUE[263]_i_3\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"BBFFFFF0F0FFFFFF"
    )
        port map (
      I0 => \SI_VALUE_reg[34]\(3),
      I1 => S_RESULT_S_C(34),
      I2 => \SI_VALUE[207]_i_2_n_0\,
      I3 => \SI_VALUE_reg[209]\,
      I4 => \SI_VALUE_reg[34]\(2),
      I5 => \SI_VALUE_reg[209]_0\,
      O => \SI_VALUE[263]_i_3_n_0\
    );
\SI_VALUE[264]_i_1\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => \SI_VALUE[264]_i_2_n_0\,
      O => \^si_value0\(110)
    );
\SI_VALUE[264]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => \SI_VALUE[272]_i_3_n_0\,
      I1 => \SI_VALUE[176]_i_3_n_0\,
      I2 => \SI_VALUE_reg[273]\,
      I3 => \SI_VALUE[264]_i_3_n_0\,
      I4 => \SI_VALUE_reg[273]_0\,
      I5 => \SI_VALUE[272]_i_2_n_0\,
      O => \SI_VALUE[264]_i_2_n_0\
    );
\SI_VALUE[264]_i_3\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFF35FFF"
    )
        port map (
      I0 => \^p\(0),
      I1 => S_RESULT_S_C(34),
      I2 => \SI_VALUE_reg[209]\,
      I3 => \SI_VALUE_reg[34]\(2),
      I4 => \SI_VALUE_reg[209]_0\,
      O => \SI_VALUE[264]_i_3_n_0\
    );
\SI_VALUE[265]_i_1\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => \SI_VALUE[265]_i_2_n_0\,
      O => \^si_value0\(111)
    );
\SI_VALUE[265]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"A0A0AFAFCFC0CFC0"
    )
        port map (
      I0 => \SI_VALUE[273]_i_5_n_0\,
      I1 => \SI_VALUE[177]_i_3_n_0\,
      I2 => \SI_VALUE_reg[273]\,
      I3 => \SI_VALUE[273]_i_3_n_0\,
      I4 => \SI_VALUE[265]_i_3_n_0\,
      I5 => \SI_VALUE_reg[273]_0\,
      O => \SI_VALUE[265]_i_2_n_0\
    );
\SI_VALUE[265]_i_3\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"4000"
    )
        port map (
      I0 => \SI_VALUE_reg[209]_0\,
      I1 => \SI_VALUE_reg[209]\,
      I2 => S_RESULT_S_C(34),
      I3 => \SI_VALUE_reg[34]\(2),
      O => \SI_VALUE[265]_i_3_n_0\
    );
\SI_VALUE[266]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"5030503F"
    )
        port map (
      I0 => \SI_VALUE[274]_i_3_n_0\,
      I1 => \SI_VALUE[266]_i_2_n_0\,
      I2 => \SI_VALUE_reg[273]\,
      I3 => \SI_VALUE_reg[273]_0\,
      I4 => \SI_VALUE[274]_i_2_n_0\,
      O => \^si_value0\(112)
    );
\SI_VALUE[266]_i_2\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"AFEBA028"
    )
        port map (
      I0 => \SI_VALUE[266]_i_3_n_0\,
      I1 => \SI_VALUE_reg[209]_0\,
      I2 => \SI_VALUE_reg[34]\(2),
      I3 => \SI_VALUE_reg[209]\,
      I4 => \SI_VALUE[270]_i_4_n_0\,
      O => \SI_VALUE[266]_i_2_n_0\
    );
\SI_VALUE[266]_i_3\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFCFDDFF00CFDD00"
    )
        port map (
      I0 => S_RESULT_S_C(11),
      I1 => \SI_VALUE_reg[279]\,
      I2 => S_RESULT_S_C(12),
      I3 => \SI_VALUE_reg[209]\,
      I4 => \SI_VALUE_reg[209]_0\,
      I5 => \SI_VALUE[266]_i_4_n_0\,
      O => \SI_VALUE[266]_i_3_n_0\
    );
\SI_VALUE[266]_i_4\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"C4444444F7777777"
    )
        port map (
      I0 => S_RESULT_S_C(13),
      I1 => \SI_VALUE_reg[209]\,
      I2 => \SI_VALUE_reg[209]_0\,
      I3 => \SI_VALUE_reg[34]\(3),
      I4 => \SI_VALUE_reg[34]\(2),
      I5 => S_RESULT_S_C(14),
      O => \SI_VALUE[266]_i_4_n_0\
    );
\SI_VALUE[267]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"5030503F"
    )
        port map (
      I0 => \SI_VALUE[275]_i_3_n_0\,
      I1 => \SI_VALUE[267]_i_2_n_0\,
      I2 => \SI_VALUE_reg[273]\,
      I3 => \SI_VALUE_reg[273]_0\,
      I4 => \SI_VALUE[275]_i_2_n_0\,
      O => \^si_value0\(113)
    );
\SI_VALUE[267]_i_2\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"AFEBA028"
    )
        port map (
      I0 => \SI_VALUE[267]_i_3_n_0\,
      I1 => \SI_VALUE_reg[209]_0\,
      I2 => \SI_VALUE_reg[34]\(2),
      I3 => \SI_VALUE_reg[209]\,
      I4 => \SI_VALUE[271]_i_4_n_0\,
      O => \SI_VALUE[267]_i_2_n_0\
    );
\SI_VALUE[267]_i_3\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFCFDDFF00CFDD00"
    )
        port map (
      I0 => S_RESULT_S_C(12),
      I1 => \SI_VALUE_reg[279]\,
      I2 => S_RESULT_S_C(13),
      I3 => \SI_VALUE_reg[209]\,
      I4 => \SI_VALUE_reg[209]_0\,
      I5 => \SI_VALUE[267]_i_4_n_0\,
      O => \SI_VALUE[267]_i_3_n_0\
    );
\SI_VALUE[267]_i_4\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"C4444444F7777777"
    )
        port map (
      I0 => S_RESULT_S_C(14),
      I1 => \SI_VALUE_reg[209]\,
      I2 => \SI_VALUE_reg[209]_0\,
      I3 => \SI_VALUE_reg[34]\(3),
      I4 => \SI_VALUE_reg[34]\(2),
      I5 => S_RESULT_S_C(15),
      O => \SI_VALUE[267]_i_4_n_0\
    );
\SI_VALUE[268]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"470047FF"
    )
        port map (
      I0 => \SI_VALUE[276]_i_3_n_0\,
      I1 => \SI_VALUE_reg[273]_0\,
      I2 => \SI_VALUE[268]_i_2_n_0\,
      I3 => \SI_VALUE_reg[273]\,
      I4 => \SI_VALUE[268]_i_3_n_0\,
      O => \^si_value0\(114)
    );
\SI_VALUE[268]_i_2\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"AFEBA028"
    )
        port map (
      I0 => \SI_VALUE[268]_i_4_n_0\,
      I1 => \SI_VALUE_reg[209]_0\,
      I2 => \SI_VALUE_reg[34]\(2),
      I3 => \SI_VALUE_reg[209]\,
      I4 => \SI_VALUE[272]_i_5_n_0\,
      O => \SI_VALUE[268]_i_2_n_0\
    );
\SI_VALUE[268]_i_3\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FDEFFFDD5DE5AADD"
    )
        port map (
      I0 => \SI_VALUE_reg[34]\(3),
      I1 => \SI_VALUE[276]_i_5_n_0\,
      I2 => \SI_VALUE_reg[209]\,
      I3 => \SI_VALUE_reg[34]\(2),
      I4 => \SI_VALUE_reg[209]_0\,
      I5 => \SI_VALUE[276]_i_4_n_0\,
      O => \SI_VALUE[268]_i_3_n_0\
    );
\SI_VALUE[268]_i_4\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFCFDDFF00CFDD00"
    )
        port map (
      I0 => S_RESULT_S_C(13),
      I1 => \SI_VALUE_reg[279]\,
      I2 => S_RESULT_S_C(14),
      I3 => \SI_VALUE_reg[209]\,
      I4 => \SI_VALUE_reg[209]_0\,
      I5 => \SI_VALUE[268]_i_5_n_0\,
      O => \SI_VALUE[268]_i_4_n_0\
    );
\SI_VALUE[268]_i_5\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"C4444444F7777777"
    )
        port map (
      I0 => S_RESULT_S_C(15),
      I1 => \SI_VALUE_reg[209]\,
      I2 => \SI_VALUE_reg[209]_0\,
      I3 => \SI_VALUE_reg[34]\(3),
      I4 => \SI_VALUE_reg[34]\(2),
      I5 => S_RESULT_S_C(16),
      O => \SI_VALUE[268]_i_5_n_0\
    );
\SI_VALUE[269]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"470047FF"
    )
        port map (
      I0 => \SI_VALUE[277]_i_3_n_0\,
      I1 => \SI_VALUE_reg[273]_0\,
      I2 => \SI_VALUE[269]_i_2_n_0\,
      I3 => \SI_VALUE_reg[273]\,
      I4 => \SI_VALUE[269]_i_3_n_0\,
      O => \^si_value0\(115)
    );
\SI_VALUE[269]_i_2\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"AFEBA028"
    )
        port map (
      I0 => \SI_VALUE[269]_i_4_n_0\,
      I1 => \SI_VALUE_reg[209]_0\,
      I2 => \SI_VALUE_reg[34]\(2),
      I3 => \SI_VALUE_reg[209]\,
      I4 => \SI_VALUE[273]_i_6_n_0\,
      O => \SI_VALUE[269]_i_2_n_0\
    );
\SI_VALUE[269]_i_3\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFFFF7F5FF5AA7F"
    )
        port map (
      I0 => \SI_VALUE_reg[34]\(3),
      I1 => S_RESULT_S_C(34),
      I2 => \SI_VALUE_reg[209]\,
      I3 => \SI_VALUE_reg[34]\(2),
      I4 => \SI_VALUE_reg[209]_0\,
      I5 => \SI_VALUE[277]_i_4_n_0\,
      O => \SI_VALUE[269]_i_3_n_0\
    );
\SI_VALUE[269]_i_4\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFCFDDFF00CFDD00"
    )
        port map (
      I0 => S_RESULT_S_C(14),
      I1 => \SI_VALUE_reg[279]\,
      I2 => S_RESULT_S_C(15),
      I3 => \SI_VALUE_reg[209]\,
      I4 => \SI_VALUE_reg[209]_0\,
      I5 => \SI_VALUE[269]_i_5_n_0\,
      O => \SI_VALUE[269]_i_4_n_0\
    );
\SI_VALUE[269]_i_5\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"C4444444F7777777"
    )
        port map (
      I0 => S_RESULT_S_C(16),
      I1 => \SI_VALUE_reg[209]\,
      I2 => \SI_VALUE_reg[209]_0\,
      I3 => \SI_VALUE_reg[34]\(3),
      I4 => \SI_VALUE_reg[34]\(2),
      I5 => S_RESULT_S_C(17),
      O => \SI_VALUE[269]_i_5_n_0\
    );
\SI_VALUE[26]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"40000001"
    )
        port map (
      I0 => \SI_VALUE[250]_i_2_n_0\,
      I1 => \SI_VALUE_reg[34]\(1),
      I2 => \SI_VALUE_reg[34]\(2),
      I3 => \SI_VALUE_reg[34]\(3),
      I4 => \SI_VALUE_reg[34]\(0),
      O => \^si_value0\(26)
    );
\SI_VALUE[270]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"50305030503F5030"
    )
        port map (
      I0 => \SI_VALUE[278]_i_3_n_0\,
      I1 => \SI_VALUE[270]_i_2_n_0\,
      I2 => \SI_VALUE_reg[273]\,
      I3 => \SI_VALUE_reg[273]_0\,
      I4 => \SI_VALUE_reg[206]\,
      I5 => \SI_VALUE[278]_i_2_n_0\,
      O => \^si_value0\(116)
    );
\SI_VALUE[270]_i_2\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"AFEBA028"
    )
        port map (
      I0 => \SI_VALUE[270]_i_4_n_0\,
      I1 => \SI_VALUE_reg[209]_0\,
      I2 => \SI_VALUE_reg[34]\(2),
      I3 => \SI_VALUE_reg[209]\,
      I4 => \SI_VALUE[274]_i_4_n_0\,
      O => \SI_VALUE[270]_i_2_n_0\
    );
\SI_VALUE[270]_i_4\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFCFDDFF00CFDD00"
    )
        port map (
      I0 => S_RESULT_S_C(15),
      I1 => \SI_VALUE_reg[279]\,
      I2 => S_RESULT_S_C(16),
      I3 => \SI_VALUE_reg[209]\,
      I4 => \SI_VALUE_reg[209]_0\,
      I5 => \SI_VALUE[270]_i_5_n_0\,
      O => \SI_VALUE[270]_i_4_n_0\
    );
\SI_VALUE[270]_i_5\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"C4444444F7777777"
    )
        port map (
      I0 => S_RESULT_S_C(17),
      I1 => \SI_VALUE_reg[209]\,
      I2 => \SI_VALUE_reg[209]_0\,
      I3 => \SI_VALUE_reg[34]\(3),
      I4 => \SI_VALUE_reg[34]\(2),
      I5 => S_RESULT_S_C(18),
      O => \SI_VALUE[270]_i_5_n_0\
    );
\SI_VALUE[271]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"470047FF"
    )
        port map (
      I0 => \SI_VALUE[279]_i_5_n_0\,
      I1 => \SI_VALUE_reg[273]_0\,
      I2 => \SI_VALUE[271]_i_2_n_0\,
      I3 => \SI_VALUE_reg[273]\,
      I4 => \SI_VALUE[271]_i_3_n_0\,
      O => \^si_value0\(117)
    );
\SI_VALUE[271]_i_2\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"AFEBA028"
    )
        port map (
      I0 => \SI_VALUE[271]_i_4_n_0\,
      I1 => \SI_VALUE_reg[209]_0\,
      I2 => \SI_VALUE_reg[34]\(2),
      I3 => \SI_VALUE_reg[209]\,
      I4 => \SI_VALUE[275]_i_4_n_0\,
      O => \SI_VALUE[271]_i_2_n_0\
    );
\SI_VALUE[271]_i_3\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFFDFFBF"
    )
        port map (
      I0 => \SI_VALUE_reg[209]_0\,
      I1 => \SI_VALUE_reg[34]\(2),
      I2 => \SI_VALUE_reg[209]\,
      I3 => \SI_VALUE[207]_i_2_n_0\,
      I4 => \SI_VALUE_reg[34]\(3),
      O => \SI_VALUE[271]_i_3_n_0\
    );
\SI_VALUE[271]_i_4\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFCFDDFF00CFDD00"
    )
        port map (
      I0 => S_RESULT_S_C(16),
      I1 => \SI_VALUE_reg[279]\,
      I2 => S_RESULT_S_C(17),
      I3 => \SI_VALUE_reg[209]\,
      I4 => \SI_VALUE_reg[209]_0\,
      I5 => \SI_VALUE[271]_i_5_n_0\,
      O => \SI_VALUE[271]_i_4_n_0\
    );
\SI_VALUE[271]_i_5\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"C4444444F7777777"
    )
        port map (
      I0 => S_RESULT_S_C(18),
      I1 => \SI_VALUE_reg[209]\,
      I2 => \SI_VALUE_reg[209]_0\,
      I3 => \SI_VALUE_reg[34]\(3),
      I4 => \SI_VALUE_reg[34]\(2),
      I5 => S_RESULT_S_C(19),
      O => \SI_VALUE[271]_i_5_n_0\
    );
\SI_VALUE[272]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"470047FF"
    )
        port map (
      I0 => \SI_VALUE[272]_i_2_n_0\,
      I1 => \SI_VALUE_reg[273]_0\,
      I2 => \SI_VALUE[272]_i_3_n_0\,
      I3 => \SI_VALUE_reg[273]\,
      I4 => \SI_VALUE[272]_i_4_n_0\,
      O => \^si_value0\(118)
    );
\SI_VALUE[272]_i_2\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"AFEBA028"
    )
        port map (
      I0 => \SI_VALUE[276]_i_7_n_0\,
      I1 => \SI_VALUE_reg[209]_0\,
      I2 => \SI_VALUE_reg[34]\(2),
      I3 => \SI_VALUE_reg[209]\,
      I4 => \SI_VALUE[276]_i_4_n_0\,
      O => \SI_VALUE[272]_i_2_n_0\
    );
\SI_VALUE[272]_i_3\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"AFEBA028"
    )
        port map (
      I0 => \SI_VALUE[272]_i_5_n_0\,
      I1 => \SI_VALUE_reg[209]_0\,
      I2 => \SI_VALUE_reg[34]\(2),
      I3 => \SI_VALUE_reg[209]\,
      I4 => \SI_VALUE[276]_i_6_n_0\,
      O => \SI_VALUE[272]_i_3_n_0\
    );
\SI_VALUE[272]_i_4\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FDFFBFBFFDFFFFFF"
    )
        port map (
      I0 => \SI_VALUE_reg[209]_0\,
      I1 => \SI_VALUE_reg[34]\(2),
      I2 => \SI_VALUE_reg[209]\,
      I3 => S_RESULT_S_C(34),
      I4 => \SI_VALUE_reg[34]\(3),
      I5 => \^p\(0),
      O => \SI_VALUE[272]_i_4_n_0\
    );
\SI_VALUE[272]_i_5\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFCFDDFF00CFDD00"
    )
        port map (
      I0 => S_RESULT_S_C(17),
      I1 => \SI_VALUE_reg[279]\,
      I2 => S_RESULT_S_C(18),
      I3 => \SI_VALUE_reg[209]\,
      I4 => \SI_VALUE_reg[209]_0\,
      I5 => \SI_VALUE[272]_i_6_n_0\,
      O => \SI_VALUE[272]_i_5_n_0\
    );
\SI_VALUE[272]_i_6\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"C4444444F7777777"
    )
        port map (
      I0 => S_RESULT_S_C(19),
      I1 => \SI_VALUE_reg[209]\,
      I2 => \SI_VALUE_reg[209]_0\,
      I3 => \SI_VALUE_reg[34]\(3),
      I4 => \SI_VALUE_reg[34]\(2),
      I5 => S_RESULT_S_C(20),
      O => \SI_VALUE[272]_i_6_n_0\
    );
\SI_VALUE[273]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFFF202A"
    )
        port map (
      I0 => \SI_VALUE_reg[273]\,
      I1 => \SI_VALUE[273]_i_3_n_0\,
      I2 => \SI_VALUE_reg[273]_0\,
      I3 => \SI_VALUE[273]_i_5_n_0\,
      I4 => \^si_value0\(90),
      O => \^si_value0\(119)
    );
\SI_VALUE[273]_i_3\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"AFEBA028"
    )
        port map (
      I0 => \SI_VALUE[277]_i_6_n_0\,
      I1 => \SI_VALUE_reg[209]_0\,
      I2 => \SI_VALUE_reg[34]\(2),
      I3 => \SI_VALUE_reg[209]\,
      I4 => \SI_VALUE[277]_i_4_n_0\,
      O => \SI_VALUE[273]_i_3_n_0\
    );
\SI_VALUE[273]_i_5\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"AFEBA028"
    )
        port map (
      I0 => \SI_VALUE[273]_i_6_n_0\,
      I1 => \SI_VALUE_reg[209]_0\,
      I2 => \SI_VALUE_reg[34]\(2),
      I3 => \SI_VALUE_reg[209]\,
      I4 => \SI_VALUE[277]_i_5_n_0\,
      O => \SI_VALUE[273]_i_5_n_0\
    );
\SI_VALUE[273]_i_6\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFCFDDFF00CFDD00"
    )
        port map (
      I0 => S_RESULT_S_C(18),
      I1 => \SI_VALUE_reg[279]\,
      I2 => S_RESULT_S_C(19),
      I3 => \SI_VALUE_reg[209]\,
      I4 => \SI_VALUE_reg[209]_0\,
      I5 => \SI_VALUE[273]_i_7_n_0\,
      O => \SI_VALUE[273]_i_6_n_0\
    );
\SI_VALUE[273]_i_7\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"C4444444F7777777"
    )
        port map (
      I0 => S_RESULT_S_C(20),
      I1 => \SI_VALUE_reg[209]\,
      I2 => \SI_VALUE_reg[209]_0\,
      I3 => \SI_VALUE_reg[34]\(3),
      I4 => \SI_VALUE_reg[34]\(2),
      I5 => S_RESULT_S_C(21),
      O => \SI_VALUE[273]_i_7_n_0\
    );
\SI_VALUE[274]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"10444511DF7775DD"
    )
        port map (
      I0 => \SI_VALUE[274]_i_2_n_0\,
      I1 => \SI_VALUE_reg[34]\(2),
      I2 => \SI_VALUE_reg[209]\,
      I3 => \SI_VALUE_reg[209]_0\,
      I4 => \SI_VALUE_reg[34]\(3),
      I5 => \SI_VALUE[274]_i_3_n_0\,
      O => \^si_value0\(120)
    );
\SI_VALUE[274]_i_2\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"AFEBA028"
    )
        port map (
      I0 => \SI_VALUE[278]_i_6_n_0\,
      I1 => \SI_VALUE_reg[209]_0\,
      I2 => \SI_VALUE_reg[34]\(2),
      I3 => \SI_VALUE_reg[209]\,
      I4 => \SI_VALUE[278]_i_2_n_0\,
      O => \SI_VALUE[274]_i_2_n_0\
    );
\SI_VALUE[274]_i_3\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"AFEBA028"
    )
        port map (
      I0 => \SI_VALUE[274]_i_4_n_0\,
      I1 => \SI_VALUE_reg[209]_0\,
      I2 => \SI_VALUE_reg[34]\(2),
      I3 => \SI_VALUE_reg[209]\,
      I4 => \SI_VALUE[278]_i_5_n_0\,
      O => \SI_VALUE[274]_i_3_n_0\
    );
\SI_VALUE[274]_i_4\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFCFDDFF00CFDD00"
    )
        port map (
      I0 => S_RESULT_S_C(19),
      I1 => \SI_VALUE_reg[279]\,
      I2 => S_RESULT_S_C(20),
      I3 => \SI_VALUE_reg[209]\,
      I4 => \SI_VALUE_reg[209]_0\,
      I5 => \SI_VALUE[274]_i_5_n_0\,
      O => \SI_VALUE[274]_i_4_n_0\
    );
\SI_VALUE[274]_i_5\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"C4444444F7777777"
    )
        port map (
      I0 => S_RESULT_S_C(21),
      I1 => \SI_VALUE_reg[209]\,
      I2 => \SI_VALUE_reg[209]_0\,
      I3 => \SI_VALUE_reg[34]\(3),
      I4 => \SI_VALUE_reg[34]\(2),
      I5 => S_RESULT_S_C(22),
      O => \SI_VALUE[274]_i_5_n_0\
    );
\SI_VALUE[275]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"10444511DF7775DD"
    )
        port map (
      I0 => \SI_VALUE[275]_i_2_n_0\,
      I1 => \SI_VALUE_reg[34]\(2),
      I2 => \SI_VALUE_reg[209]\,
      I3 => \SI_VALUE_reg[209]_0\,
      I4 => \SI_VALUE_reg[34]\(3),
      I5 => \SI_VALUE[275]_i_3_n_0\,
      O => \^si_value0\(121)
    );
\SI_VALUE[275]_i_2\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"AFEBA028"
    )
        port map (
      I0 => \SI_VALUE[279]_i_9_n_0\,
      I1 => \SI_VALUE_reg[209]_0\,
      I2 => \SI_VALUE_reg[34]\(2),
      I3 => \SI_VALUE_reg[209]\,
      I4 => \SI_VALUE[279]_i_4_n_0\,
      O => \SI_VALUE[275]_i_2_n_0\
    );
\SI_VALUE[275]_i_3\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"AFEBA028"
    )
        port map (
      I0 => \SI_VALUE[275]_i_4_n_0\,
      I1 => \SI_VALUE_reg[209]_0\,
      I2 => \SI_VALUE_reg[34]\(2),
      I3 => \SI_VALUE_reg[209]\,
      I4 => \SI_VALUE[279]_i_8_n_0\,
      O => \SI_VALUE[275]_i_3_n_0\
    );
\SI_VALUE[275]_i_4\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFCFDDFF00CFDD00"
    )
        port map (
      I0 => S_RESULT_S_C(20),
      I1 => \SI_VALUE_reg[279]\,
      I2 => S_RESULT_S_C(21),
      I3 => \SI_VALUE_reg[209]\,
      I4 => \SI_VALUE_reg[209]_0\,
      I5 => \SI_VALUE[275]_i_5_n_0\,
      O => \SI_VALUE[275]_i_4_n_0\
    );
\SI_VALUE[275]_i_5\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"C4444444F7777777"
    )
        port map (
      I0 => S_RESULT_S_C(22),
      I1 => \SI_VALUE_reg[209]\,
      I2 => \SI_VALUE_reg[209]_0\,
      I3 => \SI_VALUE_reg[34]\(3),
      I4 => \SI_VALUE_reg[34]\(2),
      I5 => S_RESULT_S_C(23),
      O => \SI_VALUE[275]_i_5_n_0\
    );
\SI_VALUE[276]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"10444511DF7775DD"
    )
        port map (
      I0 => \SI_VALUE[276]_i_2_n_0\,
      I1 => \SI_VALUE_reg[34]\(2),
      I2 => \SI_VALUE_reg[209]\,
      I3 => \SI_VALUE_reg[209]_0\,
      I4 => \SI_VALUE_reg[34]\(3),
      I5 => \SI_VALUE[276]_i_3_n_0\,
      O => \^si_value0\(122)
    );
\SI_VALUE[276]_i_10\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"C4444444F7777777"
    )
        port map (
      I0 => S_RESULT_S_C(27),
      I1 => \SI_VALUE_reg[209]\,
      I2 => \SI_VALUE_reg[209]_0\,
      I3 => \SI_VALUE_reg[34]\(3),
      I4 => \SI_VALUE_reg[34]\(2),
      I5 => S_RESULT_S_C(28),
      O => \SI_VALUE[276]_i_10_n_0\
    );
\SI_VALUE[276]_i_2\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"AFEBA028"
    )
        port map (
      I0 => \SI_VALUE[276]_i_4_n_0\,
      I1 => \SI_VALUE_reg[209]_0\,
      I2 => \SI_VALUE_reg[34]\(2),
      I3 => \SI_VALUE_reg[209]\,
      I4 => \SI_VALUE[276]_i_5_n_0\,
      O => \SI_VALUE[276]_i_2_n_0\
    );
\SI_VALUE[276]_i_3\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"AFEBA028"
    )
        port map (
      I0 => \SI_VALUE[276]_i_6_n_0\,
      I1 => \SI_VALUE_reg[209]_0\,
      I2 => \SI_VALUE_reg[34]\(2),
      I3 => \SI_VALUE_reg[209]\,
      I4 => \SI_VALUE[276]_i_7_n_0\,
      O => \SI_VALUE[276]_i_3_n_0\
    );
\SI_VALUE[276]_i_4\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFCFDDFF00CFDD00"
    )
        port map (
      I0 => S_RESULT_S_C(29),
      I1 => \SI_VALUE_reg[279]\,
      I2 => S_RESULT_S_C(30),
      I3 => \SI_VALUE_reg[209]\,
      I4 => \SI_VALUE_reg[209]_0\,
      I5 => \SI_VALUE[276]_i_8_n_0\,
      O => \SI_VALUE[276]_i_4_n_0\
    );
\SI_VALUE[276]_i_5\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"F35F"
    )
        port map (
      I0 => S_RESULT_S_C(34),
      I1 => \^p\(0),
      I2 => \SI_VALUE_reg[209]_0\,
      I3 => \SI_VALUE_reg[209]\,
      O => \SI_VALUE[276]_i_5_n_0\
    );
\SI_VALUE[276]_i_6\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFCFDDFF00CFDD00"
    )
        port map (
      I0 => S_RESULT_S_C(21),
      I1 => \SI_VALUE_reg[279]\,
      I2 => S_RESULT_S_C(22),
      I3 => \SI_VALUE_reg[209]\,
      I4 => \SI_VALUE_reg[209]_0\,
      I5 => \SI_VALUE[276]_i_9_n_0\,
      O => \SI_VALUE[276]_i_6_n_0\
    );
\SI_VALUE[276]_i_7\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFCFDDFF00CFDD00"
    )
        port map (
      I0 => S_RESULT_S_C(25),
      I1 => \SI_VALUE_reg[279]\,
      I2 => S_RESULT_S_C(26),
      I3 => \SI_VALUE_reg[209]\,
      I4 => \SI_VALUE_reg[209]_0\,
      I5 => \SI_VALUE[276]_i_10_n_0\,
      O => \SI_VALUE[276]_i_7_n_0\
    );
\SI_VALUE[276]_i_8\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"C4444444F7777777"
    )
        port map (
      I0 => S_RESULT_S_C(31),
      I1 => \SI_VALUE_reg[209]\,
      I2 => \SI_VALUE_reg[209]_0\,
      I3 => \SI_VALUE_reg[34]\(3),
      I4 => \SI_VALUE_reg[34]\(2),
      I5 => S_RESULT_S_C(32),
      O => \SI_VALUE[276]_i_8_n_0\
    );
\SI_VALUE[276]_i_9\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"C4444444F7777777"
    )
        port map (
      I0 => S_RESULT_S_C(23),
      I1 => \SI_VALUE_reg[209]\,
      I2 => \SI_VALUE_reg[209]_0\,
      I3 => \SI_VALUE_reg[34]\(3),
      I4 => \SI_VALUE_reg[34]\(2),
      I5 => S_RESULT_S_C(24),
      O => \SI_VALUE[276]_i_9_n_0\
    );
\SI_VALUE[277]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"10444511DF7775DD"
    )
        port map (
      I0 => \SI_VALUE[277]_i_2_n_0\,
      I1 => \SI_VALUE_reg[34]\(2),
      I2 => \SI_VALUE_reg[209]\,
      I3 => \SI_VALUE_reg[209]_0\,
      I4 => \SI_VALUE_reg[34]\(3),
      I5 => \SI_VALUE[277]_i_3_n_0\,
      O => \^si_value0\(125)
    );
\SI_VALUE[277]_i_2\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"ACEBAFEB"
    )
        port map (
      I0 => \SI_VALUE[277]_i_4_n_0\,
      I1 => \SI_VALUE_reg[209]_0\,
      I2 => \SI_VALUE_reg[34]\(2),
      I3 => \SI_VALUE_reg[209]\,
      I4 => S_RESULT_S_C(34),
      O => \SI_VALUE[277]_i_2_n_0\
    );
\SI_VALUE[277]_i_3\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"AFEBA028"
    )
        port map (
      I0 => \SI_VALUE[277]_i_5_n_0\,
      I1 => \SI_VALUE_reg[209]_0\,
      I2 => \SI_VALUE_reg[34]\(2),
      I3 => \SI_VALUE_reg[209]\,
      I4 => \SI_VALUE[277]_i_6_n_0\,
      O => \SI_VALUE[277]_i_3_n_0\
    );
\SI_VALUE[277]_i_4\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFCFDDFF00CFDD00"
    )
        port map (
      I0 => S_RESULT_S_C(30),
      I1 => \SI_VALUE_reg[279]\,
      I2 => S_RESULT_S_C(31),
      I3 => \SI_VALUE_reg[209]\,
      I4 => \SI_VALUE_reg[209]_0\,
      I5 => \SI_VALUE[207]_i_2_n_0\,
      O => \SI_VALUE[277]_i_4_n_0\
    );
\SI_VALUE[277]_i_5\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFCFDDFF00CFDD00"
    )
        port map (
      I0 => S_RESULT_S_C(22),
      I1 => \SI_VALUE_reg[279]\,
      I2 => S_RESULT_S_C(23),
      I3 => \SI_VALUE_reg[209]\,
      I4 => \SI_VALUE_reg[209]_0\,
      I5 => \SI_VALUE[277]_i_7_n_0\,
      O => \SI_VALUE[277]_i_5_n_0\
    );
\SI_VALUE[277]_i_6\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFCFDDFF00CFDD00"
    )
        port map (
      I0 => S_RESULT_S_C(26),
      I1 => \SI_VALUE_reg[279]\,
      I2 => S_RESULT_S_C(27),
      I3 => \SI_VALUE_reg[209]\,
      I4 => \SI_VALUE_reg[209]_0\,
      I5 => \SI_VALUE[277]_i_8_n_0\,
      O => \SI_VALUE[277]_i_6_n_0\
    );
\SI_VALUE[277]_i_7\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"C4444444F7777777"
    )
        port map (
      I0 => S_RESULT_S_C(24),
      I1 => \SI_VALUE_reg[209]\,
      I2 => \SI_VALUE_reg[209]_0\,
      I3 => \SI_VALUE_reg[34]\(3),
      I4 => \SI_VALUE_reg[34]\(2),
      I5 => S_RESULT_S_C(25),
      O => \SI_VALUE[277]_i_7_n_0\
    );
\SI_VALUE[277]_i_8\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"C4444444F7777777"
    )
        port map (
      I0 => S_RESULT_S_C(28),
      I1 => \SI_VALUE_reg[209]\,
      I2 => \SI_VALUE_reg[209]_0\,
      I3 => \SI_VALUE_reg[34]\(3),
      I4 => \SI_VALUE_reg[34]\(2),
      I5 => S_RESULT_S_C(29),
      O => \SI_VALUE[277]_i_8_n_0\
    );
\SI_VALUE[278]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"00444100CF7771CC"
    )
        port map (
      I0 => \SI_VALUE[278]_i_2_n_0\,
      I1 => \SI_VALUE_reg[34]\(2),
      I2 => \SI_VALUE_reg[209]\,
      I3 => \SI_VALUE_reg[209]_0\,
      I4 => \SI_VALUE_reg[34]\(3),
      I5 => \SI_VALUE[278]_i_3_n_0\,
      O => \^si_value0\(126)
    );
\SI_VALUE[278]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFCFDDFF00CFDD00"
    )
        port map (
      I0 => S_RESULT_S_C(31),
      I1 => \SI_VALUE_reg[279]\,
      I2 => S_RESULT_S_C(32),
      I3 => \SI_VALUE_reg[209]\,
      I4 => \SI_VALUE_reg[209]_0\,
      I5 => \SI_VALUE[278]_i_4_n_0\,
      O => \SI_VALUE[278]_i_2_n_0\
    );
\SI_VALUE[278]_i_3\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"AFEBA028"
    )
        port map (
      I0 => \SI_VALUE[278]_i_5_n_0\,
      I1 => \SI_VALUE_reg[209]_0\,
      I2 => \SI_VALUE_reg[34]\(2),
      I3 => \SI_VALUE_reg[209]\,
      I4 => \SI_VALUE[278]_i_6_n_0\,
      O => \SI_VALUE[278]_i_3_n_0\
    );
\SI_VALUE[278]_i_4\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"C4444444F7777777"
    )
        port map (
      I0 => \^p\(0),
      I1 => \SI_VALUE_reg[209]\,
      I2 => \SI_VALUE_reg[209]_0\,
      I3 => \SI_VALUE_reg[34]\(3),
      I4 => \SI_VALUE_reg[34]\(2),
      I5 => S_RESULT_S_C(34),
      O => \SI_VALUE[278]_i_4_n_0\
    );
\SI_VALUE[278]_i_5\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFCFDDFF00CFDD00"
    )
        port map (
      I0 => S_RESULT_S_C(23),
      I1 => \SI_VALUE_reg[279]\,
      I2 => S_RESULT_S_C(24),
      I3 => \SI_VALUE_reg[209]\,
      I4 => \SI_VALUE_reg[209]_0\,
      I5 => \SI_VALUE[278]_i_7_n_0\,
      O => \SI_VALUE[278]_i_5_n_0\
    );
\SI_VALUE[278]_i_6\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFCFDDFF00CFDD00"
    )
        port map (
      I0 => S_RESULT_S_C(27),
      I1 => \SI_VALUE_reg[279]\,
      I2 => S_RESULT_S_C(28),
      I3 => \SI_VALUE_reg[209]\,
      I4 => \SI_VALUE_reg[209]_0\,
      I5 => \SI_VALUE[278]_i_8_n_0\,
      O => \SI_VALUE[278]_i_6_n_0\
    );
\SI_VALUE[278]_i_7\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"C4444444F7777777"
    )
        port map (
      I0 => S_RESULT_S_C(25),
      I1 => \SI_VALUE_reg[209]\,
      I2 => \SI_VALUE_reg[209]_0\,
      I3 => \SI_VALUE_reg[34]\(3),
      I4 => \SI_VALUE_reg[34]\(2),
      I5 => S_RESULT_S_C(26),
      O => \SI_VALUE[278]_i_7_n_0\
    );
\SI_VALUE[278]_i_8\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"C4444444F7777777"
    )
        port map (
      I0 => S_RESULT_S_C(29),
      I1 => \SI_VALUE_reg[209]\,
      I2 => \SI_VALUE_reg[209]_0\,
      I3 => \SI_VALUE_reg[34]\(3),
      I4 => \SI_VALUE_reg[34]\(2),
      I5 => S_RESULT_S_C(30),
      O => \SI_VALUE[278]_i_8_n_0\
    );
\SI_VALUE[279]_i_10\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"C4444444F7777777"
    )
        port map (
      I0 => S_RESULT_S_C(26),
      I1 => \SI_VALUE_reg[209]\,
      I2 => \SI_VALUE_reg[209]_0\,
      I3 => \SI_VALUE_reg[34]\(3),
      I4 => \SI_VALUE_reg[34]\(2),
      I5 => S_RESULT_S_C(27),
      O => \SI_VALUE[279]_i_10_n_0\
    );
\SI_VALUE[279]_i_11\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"C4444444F7777777"
    )
        port map (
      I0 => S_RESULT_S_C(30),
      I1 => \SI_VALUE_reg[209]\,
      I2 => \SI_VALUE_reg[209]_0\,
      I3 => \SI_VALUE_reg[34]\(3),
      I4 => \SI_VALUE_reg[34]\(2),
      I5 => S_RESULT_S_C(31),
      O => \SI_VALUE[279]_i_11_n_0\
    );
\SI_VALUE[279]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"00444100CF7771CC"
    )
        port map (
      I0 => \SI_VALUE[279]_i_4_n_0\,
      I1 => \SI_VALUE_reg[34]\(2),
      I2 => \SI_VALUE_reg[209]\,
      I3 => \SI_VALUE_reg[209]_0\,
      I4 => \SI_VALUE_reg[34]\(3),
      I5 => \SI_VALUE[279]_i_5_n_0\,
      O => \^si_value0\(127)
    );
\SI_VALUE[279]_i_4\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFFFFFF035FF35F"
    )
        port map (
      I0 => S_RESULT_S_C(32),
      I1 => \^p\(0),
      I2 => \SI_VALUE_reg[209]\,
      I3 => \SI_VALUE_reg[209]_0\,
      I4 => S_RESULT_S_C(34),
      I5 => \SI_VALUE_reg[279]\,
      O => \SI_VALUE[279]_i_4_n_0\
    );
\SI_VALUE[279]_i_5\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"AFEBA028"
    )
        port map (
      I0 => \SI_VALUE[279]_i_8_n_0\,
      I1 => \SI_VALUE_reg[209]_0\,
      I2 => \SI_VALUE_reg[34]\(2),
      I3 => \SI_VALUE_reg[209]\,
      I4 => \SI_VALUE[279]_i_9_n_0\,
      O => \SI_VALUE[279]_i_5_n_0\
    );
\SI_VALUE[279]_i_8\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFCFDDFF00CFDD00"
    )
        port map (
      I0 => S_RESULT_S_C(24),
      I1 => \SI_VALUE_reg[279]\,
      I2 => S_RESULT_S_C(25),
      I3 => \SI_VALUE_reg[209]\,
      I4 => \SI_VALUE_reg[209]_0\,
      I5 => \SI_VALUE[279]_i_10_n_0\,
      O => \SI_VALUE[279]_i_8_n_0\
    );
\SI_VALUE[279]_i_9\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFCFDDFF00CFDD00"
    )
        port map (
      I0 => S_RESULT_S_C(28),
      I1 => \SI_VALUE_reg[279]\,
      I2 => S_RESULT_S_C(29),
      I3 => \SI_VALUE_reg[209]\,
      I4 => \SI_VALUE_reg[209]_0\,
      I5 => \SI_VALUE[279]_i_11_n_0\,
      O => \SI_VALUE[279]_i_9_n_0\
    );
\SI_VALUE[27]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"40000001"
    )
        port map (
      I0 => \SI_VALUE[251]_i_2_n_0\,
      I1 => \SI_VALUE_reg[34]\(1),
      I2 => \SI_VALUE_reg[34]\(2),
      I3 => \SI_VALUE_reg[34]\(3),
      I4 => \SI_VALUE_reg[34]\(0),
      O => \^si_value0\(27)
    );
\SI_VALUE[28]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"40000001"
    )
        port map (
      I0 => \SI_VALUE[252]_i_2_n_0\,
      I1 => \SI_VALUE_reg[34]\(1),
      I2 => \SI_VALUE_reg[34]\(2),
      I3 => \SI_VALUE_reg[34]\(3),
      I4 => \SI_VALUE_reg[34]\(0),
      O => \^si_value0\(28)
    );
\SI_VALUE[29]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"40000001"
    )
        port map (
      I0 => \SI_VALUE[253]_i_2_n_0\,
      I1 => \SI_VALUE_reg[34]\(1),
      I2 => \SI_VALUE_reg[34]\(2),
      I3 => \SI_VALUE_reg[34]\(3),
      I4 => \SI_VALUE_reg[34]\(0),
      O => \^si_value0\(29)
    );
\SI_VALUE[2]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"00000001"
    )
        port map (
      I0 => \SI_VALUE[2]_i_2_n_0\,
      I1 => \SI_VALUE_reg[209]_0\,
      I2 => \SI_VALUE_reg[209]\,
      I3 => \SI_VALUE_reg[34]\(3),
      I4 => \SI_VALUE_reg[34]\(2),
      O => \^si_value0\(2)
    );
\SI_VALUE[2]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"C4444444F7777777"
    )
        port map (
      I0 => S_RESULT_S_C(1),
      I1 => \SI_VALUE_reg[209]\,
      I2 => \SI_VALUE_reg[209]_0\,
      I3 => \SI_VALUE_reg[34]\(3),
      I4 => \SI_VALUE_reg[34]\(2),
      I5 => S_RESULT_S_C(2),
      O => \SI_VALUE[2]_i_2_n_0\
    );
\SI_VALUE[30]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"40000001"
    )
        port map (
      I0 => \SI_VALUE[254]_i_2_n_0\,
      I1 => \SI_VALUE_reg[34]\(1),
      I2 => \SI_VALUE_reg[34]\(2),
      I3 => \SI_VALUE_reg[34]\(3),
      I4 => \SI_VALUE_reg[34]\(0),
      O => \^si_value0\(30)
    );
\SI_VALUE[31]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"40000001"
    )
        port map (
      I0 => \SI_VALUE[255]_i_2_n_0\,
      I1 => \SI_VALUE_reg[34]\(1),
      I2 => \SI_VALUE_reg[34]\(2),
      I3 => \SI_VALUE_reg[34]\(3),
      I4 => \SI_VALUE_reg[34]\(0),
      O => \^si_value0\(31)
    );
\SI_VALUE[32]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"00008001"
    )
        port map (
      I0 => \SI_VALUE_reg[34]\(3),
      I1 => \SI_VALUE_reg[34]\(2),
      I2 => \SI_VALUE_reg[34]\(0),
      I3 => \SI_VALUE_reg[34]\(1),
      I4 => \SI_VALUE[256]_i_2_n_0\,
      O => \^si_value0\(32)
    );
\SI_VALUE[33]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"00008001"
    )
        port map (
      I0 => \SI_VALUE_reg[34]\(3),
      I1 => \SI_VALUE_reg[34]\(2),
      I2 => \SI_VALUE_reg[34]\(0),
      I3 => \SI_VALUE_reg[34]\(1),
      I4 => \SI_VALUE[257]_i_2_n_0\,
      O => \^si_value0\(33)
    );
\SI_VALUE[34]_i_2\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"00008001"
    )
        port map (
      I0 => \SI_VALUE_reg[34]\(3),
      I1 => \SI_VALUE_reg[34]\(2),
      I2 => \SI_VALUE_reg[34]\(0),
      I3 => \SI_VALUE_reg[34]\(1),
      I4 => \SI_VALUE[258]_i_2_n_0\,
      O => \^si_value0\(34)
    );
\SI_VALUE[35]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"00004A15"
    )
        port map (
      I0 => \SI_VALUE_reg[34]\(2),
      I1 => \SI_VALUE_reg[209]\,
      I2 => \SI_VALUE_reg[209]_0\,
      I3 => \SI_VALUE_reg[34]\(3),
      I4 => \SI_VALUE[211]_i_2_n_0\,
      O => \^si_value0\(35)
    );
\SI_VALUE[37]_i_1\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => \SI_VALUE[141]_i_2_n_0\,
      O => \^si_value0\(37)
    );
\SI_VALUE[3]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"0001"
    )
        port map (
      I0 => \SI_VALUE_reg[34]\(2),
      I1 => \SI_VALUE_reg[209]\,
      I2 => \SI_VALUE_reg[34]\(3),
      I3 => \SI_VALUE[211]_i_2_n_0\,
      O => \^si_value0\(3)
    );
\SI_VALUE[4]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"0001"
    )
        port map (
      I0 => \SI_VALUE_reg[34]\(2),
      I1 => \SI_VALUE_reg[209]\,
      I2 => \SI_VALUE_reg[34]\(3),
      I3 => \SI_VALUE[212]_i_2_n_0\,
      O => \^si_value0\(4)
    );
\SI_VALUE[5]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"0001"
    )
        port map (
      I0 => \SI_VALUE_reg[34]\(2),
      I1 => \SI_VALUE_reg[209]\,
      I2 => \SI_VALUE_reg[34]\(3),
      I3 => \SI_VALUE[141]_i_2_n_0\,
      O => \^si_value0\(5)
    );
\SI_VALUE[6]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"00000001"
    )
        port map (
      I0 => \SI_VALUE_reg[34]\(2),
      I1 => \SI_VALUE_reg[209]\,
      I2 => \SI_VALUE_reg[209]_0\,
      I3 => \SI_VALUE_reg[34]\(3),
      I4 => \SI_VALUE[142]_i_2_n_0\,
      O => \^si_value0\(6)
    );
\SI_VALUE[70]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"00004A15"
    )
        port map (
      I0 => \SI_VALUE_reg[34]\(2),
      I1 => \SI_VALUE_reg[209]\,
      I2 => \SI_VALUE_reg[209]_0\,
      I3 => \SI_VALUE_reg[34]\(3),
      I4 => \SI_VALUE[142]_i_2_n_0\,
      O => \^si_value0\(38)
    );
\SI_VALUE[71]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"00004A15"
    )
        port map (
      I0 => \SI_VALUE_reg[34]\(2),
      I1 => \SI_VALUE_reg[209]\,
      I2 => \SI_VALUE_reg[209]_0\,
      I3 => \SI_VALUE_reg[34]\(3),
      I4 => \SI_VALUE[175]_i_2_n_0\,
      O => \^si_value0\(39)
    );
\SI_VALUE[72]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"00002295"
    )
        port map (
      I0 => \SI_VALUE_reg[34]\(3),
      I1 => \SI_VALUE_reg[209]_0\,
      I2 => \SI_VALUE_reg[209]\,
      I3 => \SI_VALUE_reg[34]\(2),
      I4 => \SI_VALUE[176]_i_2_n_0\,
      O => \^si_value0\(40)
    );
\SI_VALUE[73]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"414110004D4DD333"
    )
        port map (
      I0 => \SI_VALUE[105]_i_2_n_0\,
      I1 => \SI_VALUE_reg[34]\(3),
      I2 => \SI_VALUE_reg[209]_0\,
      I3 => \SI_VALUE_reg[209]\,
      I4 => \SI_VALUE_reg[34]\(2),
      I5 => \SI_VALUE[177]_i_2_n_0\,
      O => \^si_value0\(41)
    );
\SI_VALUE[74]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"414110004D4DD333"
    )
        port map (
      I0 => \SI_VALUE[106]_i_2_n_0\,
      I1 => \SI_VALUE_reg[34]\(3),
      I2 => \SI_VALUE_reg[209]_0\,
      I3 => \SI_VALUE_reg[209]\,
      I4 => \SI_VALUE_reg[34]\(2),
      I5 => \SI_VALUE[106]_i_3_n_0\,
      O => \^si_value0\(42)
    );
\SI_VALUE[75]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"414110004D4DD333"
    )
        port map (
      I0 => \SI_VALUE[211]_i_2_n_0\,
      I1 => \SI_VALUE_reg[34]\(3),
      I2 => \SI_VALUE_reg[209]_0\,
      I3 => \SI_VALUE_reg[209]\,
      I4 => \SI_VALUE_reg[34]\(2),
      I5 => \SI_VALUE[107]_i_2_n_0\,
      O => \^si_value0\(43)
    );
\SI_VALUE[7]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"00000001"
    )
        port map (
      I0 => \SI_VALUE_reg[34]\(2),
      I1 => \SI_VALUE_reg[209]\,
      I2 => \SI_VALUE_reg[209]_0\,
      I3 => \SI_VALUE_reg[34]\(3),
      I4 => \SI_VALUE[175]_i_2_n_0\,
      O => \^si_value0\(7)
    );
\SI_VALUE[8]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"00000001"
    )
        port map (
      I0 => \SI_VALUE_reg[34]\(3),
      I1 => \SI_VALUE_reg[209]_0\,
      I2 => \SI_VALUE_reg[209]\,
      I3 => \SI_VALUE_reg[34]\(2),
      I4 => \SI_VALUE[176]_i_2_n_0\,
      O => \^si_value0\(8)
    );
\SI_VALUE[9]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"4000000040000003"
    )
        port map (
      I0 => \SI_VALUE[105]_i_2_n_0\,
      I1 => \SI_VALUE_reg[34]\(3),
      I2 => \SI_VALUE_reg[209]_0\,
      I3 => \SI_VALUE_reg[209]\,
      I4 => \SI_VALUE_reg[34]\(2),
      I5 => \SI_VALUE[177]_i_2_n_0\,
      O => \^si_value0\(9)
    );
S_MULT_reg: unisim.vcomponents.DSP48E2
    generic map(
      ACASCREG => 1,
      ADREG => 1,
      ALUMODEREG => 0,
      AMULTSEL => "AD",
      AREG => 1,
      AUTORESET_PATDET => "NO_RESET",
      AUTORESET_PRIORITY => "RESET",
      A_INPUT => "DIRECT",
      BCASCREG => 2,
      BMULTSEL => "B",
      BREG => 2,
      B_INPUT => "DIRECT",
      CARRYINREG => 0,
      CARRYINSELREG => 0,
      CREG => 0,
      DREG => 1,
      INMODEREG => 0,
      MASK => X"3FFFFFFFFFFF",
      MREG => 0,
      OPMODEREG => 0,
      PATTERN => X"000000000000",
      PREADDINSEL => "A",
      PREG => 1,
      RND => X"000000000000",
      SEL_MASK => "MASK",
      SEL_PATTERN => "PATTERN",
      USE_MULT => "MULTIPLY",
      USE_PATTERN_DETECT => "NO_PATDET",
      USE_SIMD => "ONE48",
      USE_WIDEXOR => "FALSE",
      XORSIMD => "XOR24_48_96"
    )
        port map (
      A(29) => DSP_ALU_INST(15),
      A(28) => DSP_ALU_INST(15),
      A(27) => DSP_ALU_INST(15),
      A(26) => DSP_ALU_INST(15),
      A(25) => DSP_ALU_INST(15),
      A(24) => DSP_ALU_INST(15),
      A(23) => DSP_ALU_INST(15),
      A(22) => DSP_ALU_INST(15),
      A(21) => DSP_ALU_INST(15),
      A(20) => DSP_ALU_INST(15),
      A(19) => DSP_ALU_INST(15),
      A(18) => DSP_ALU_INST(15),
      A(17) => DSP_ALU_INST(15),
      A(16) => DSP_ALU_INST(15),
      A(15 downto 0) => DSP_ALU_INST(15 downto 0),
      ACIN(29 downto 0) => B"000000000000000000000000000000",
      ACOUT(29 downto 0) => NLW_S_MULT_reg_ACOUT_UNCONNECTED(29 downto 0),
      ALUMODE(3 downto 0) => B"0000",
      B(17) => S_MULT_reg_i_2_n_0,
      B(16) => S_MULT_reg_i_3_n_0,
      B(15) => S_MULT_reg_i_4_n_0,
      B(14) => S_MULT_reg_i_5_n_0,
      B(13) => S_MULT_reg_i_6_n_0,
      B(12) => S_MULT_reg_i_7_n_0,
      B(11) => S_MULT_reg_i_8_n_0,
      B(10) => S_MULT_reg_i_9_n_0,
      B(9) => S_MULT_reg_i_10_n_0,
      B(8) => S_MULT_reg_i_11_n_0,
      B(7) => S_MULT_reg_i_12_n_0,
      B(6) => S_MULT_reg_i_13_n_0,
      B(5) => S_MULT_reg_i_14_n_0,
      B(4) => S_MULT_reg_i_15_n_0,
      B(3) => S_MULT_reg_i_16_n_0,
      B(2) => S_MULT_reg_i_17_n_0,
      B(1) => S_MULT_reg_i_18_n_0,
      B(0) => S_MULT_reg_i_19_n_0,
      BCIN(17 downto 0) => B"000000000000000000",
      BCOUT(17 downto 0) => NLW_S_MULT_reg_BCOUT_UNCONNECTED(17 downto 0),
      C(47 downto 0) => B"000000000000000000000000000000000000000000000000",
      CARRYCASCIN => '0',
      CARRYCASCOUT => NLW_S_MULT_reg_CARRYCASCOUT_UNCONNECTED,
      CARRYIN => '0',
      CARRYINSEL(2 downto 0) => B"000",
      CARRYOUT(3 downto 0) => NLW_S_MULT_reg_CARRYOUT_UNCONNECTED(3 downto 0),
      CEA1 => '0',
      CEA2 => CEP,
      CEAD => CEP,
      CEALUMODE => '0',
      CEB1 => S_MULT_reg_i_1_n_0,
      CEB2 => CEP,
      CEC => '0',
      CECARRYIN => '0',
      CECTRL => '0',
      CED => CEP,
      CEINMODE => '0',
      CEM => '0',
      CEP => CEP,
      CLK => s00_axi_aclk,
      D(26) => Q(15),
      D(25) => Q(15),
      D(24) => Q(15),
      D(23) => Q(15),
      D(22) => Q(15),
      D(21) => Q(15),
      D(20) => Q(15),
      D(19) => Q(15),
      D(18) => Q(15),
      D(17) => Q(15),
      D(16) => Q(15),
      D(15 downto 0) => Q(15 downto 0),
      INMODE(4 downto 0) => B"00100",
      MULTSIGNIN => '0',
      MULTSIGNOUT => NLW_S_MULT_reg_MULTSIGNOUT_UNCONNECTED,
      OPMODE(8 downto 0) => B"000000101",
      OVERFLOW => NLW_S_MULT_reg_OVERFLOW_UNCONNECTED,
      P(47 downto 35) => NLW_S_MULT_reg_P_UNCONNECTED(47 downto 35),
      P(34) => S_RESULT_S_C(34),
      P(33) => \^p\(0),
      P(32 downto 0) => S_RESULT_S_C(32 downto 0),
      PATTERNBDETECT => NLW_S_MULT_reg_PATTERNBDETECT_UNCONNECTED,
      PATTERNDETECT => NLW_S_MULT_reg_PATTERNDETECT_UNCONNECTED,
      PCIN(47 downto 0) => B"000000000000000000000000000000000000000000000000",
      PCOUT(47 downto 0) => NLW_S_MULT_reg_PCOUT_UNCONNECTED(47 downto 0),
      RSTA => RSTP,
      RSTALLCARRYIN => '0',
      RSTALUMODE => '0',
      RSTB => RSTP,
      RSTC => '0',
      RSTCTRL => '0',
      RSTD => RSTP,
      RSTINMODE => '0',
      RSTM => '0',
      RSTP => RSTP,
      UNDERFLOW => NLW_S_MULT_reg_UNDERFLOW_UNCONNECTED,
      XOROUT(7 downto 0) => NLW_S_MULT_reg_XOROUT_UNCONNECTED(7 downto 0)
    );
S_MULT_reg_i_1: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0000000011111114"
    )
        port map (
      I0 => \^s_enable_reg[0]\,
      I1 => DSP_A_B_DATA_INST(3),
      I2 => DSP_A_B_DATA_INST(2),
      I3 => DSP_A_B_DATA_INST(1),
      I4 => DSP_A_B_DATA_INST(0),
      I5 => \^s_enable_reg[0]_0\,
      O => S_MULT_reg_i_1_n_0
    );
S_MULT_reg_i_10: unisim.vcomponents.LUT6
    generic map(
      INIT => X"8F808F8F8F808080"
    )
        port map (
      I0 => DSP_A_B_DATA_INST_0(135),
      I1 => \^s_conv_counter_reg[0]\,
      I2 => DSP_A_B_DATA_INST(3),
      I3 => S_MULT_reg_i_37_n_0,
      I4 => DSP_A_B_DATA_INST(2),
      I5 => S_MULT_reg_i_38_n_0,
      O => S_MULT_reg_i_10_n_0
    );
S_MULT_reg_i_11: unisim.vcomponents.LUT6
    generic map(
      INIT => X"8F808F8F8F808080"
    )
        port map (
      I0 => DSP_A_B_DATA_INST_0(134),
      I1 => \^s_conv_counter_reg[0]\,
      I2 => DSP_A_B_DATA_INST(3),
      I3 => S_MULT_reg_i_39_n_0,
      I4 => DSP_A_B_DATA_INST(2),
      I5 => S_MULT_reg_i_40_n_0,
      O => S_MULT_reg_i_11_n_0
    );
S_MULT_reg_i_12: unisim.vcomponents.LUT6
    generic map(
      INIT => X"8F808F8F8F808080"
    )
        port map (
      I0 => DSP_A_B_DATA_INST_0(133),
      I1 => \^s_conv_counter_reg[0]\,
      I2 => DSP_A_B_DATA_INST(3),
      I3 => S_MULT_reg_i_41_n_0,
      I4 => DSP_A_B_DATA_INST(2),
      I5 => S_MULT_reg_i_42_n_0,
      O => S_MULT_reg_i_12_n_0
    );
S_MULT_reg_i_13: unisim.vcomponents.LUT6
    generic map(
      INIT => X"8F808F8F8F808080"
    )
        port map (
      I0 => DSP_A_B_DATA_INST_0(132),
      I1 => \^s_conv_counter_reg[0]\,
      I2 => DSP_A_B_DATA_INST(3),
      I3 => S_MULT_reg_i_43_n_0,
      I4 => DSP_A_B_DATA_INST(2),
      I5 => S_MULT_reg_i_44_n_0,
      O => S_MULT_reg_i_13_n_0
    );
S_MULT_reg_i_14: unisim.vcomponents.LUT6
    generic map(
      INIT => X"8F808F8F8F808080"
    )
        port map (
      I0 => DSP_A_B_DATA_INST_0(131),
      I1 => \^s_conv_counter_reg[0]\,
      I2 => DSP_A_B_DATA_INST(3),
      I3 => S_MULT_reg_i_45_n_0,
      I4 => DSP_A_B_DATA_INST(2),
      I5 => S_MULT_reg_i_46_n_0,
      O => S_MULT_reg_i_14_n_0
    );
S_MULT_reg_i_15: unisim.vcomponents.LUT6
    generic map(
      INIT => X"8F808F8F8F808080"
    )
        port map (
      I0 => DSP_A_B_DATA_INST_0(130),
      I1 => \^s_conv_counter_reg[0]\,
      I2 => DSP_A_B_DATA_INST(3),
      I3 => S_MULT_reg_i_47_n_0,
      I4 => DSP_A_B_DATA_INST(2),
      I5 => S_MULT_reg_i_48_n_0,
      O => S_MULT_reg_i_15_n_0
    );
S_MULT_reg_i_16: unisim.vcomponents.LUT6
    generic map(
      INIT => X"8F808F8F8F808080"
    )
        port map (
      I0 => DSP_A_B_DATA_INST_0(129),
      I1 => \^s_conv_counter_reg[0]\,
      I2 => DSP_A_B_DATA_INST(3),
      I3 => S_MULT_reg_i_49_n_0,
      I4 => DSP_A_B_DATA_INST(2),
      I5 => S_MULT_reg_i_50_n_0,
      O => S_MULT_reg_i_16_n_0
    );
S_MULT_reg_i_17: unisim.vcomponents.LUT6
    generic map(
      INIT => X"8F808F8F8F808080"
    )
        port map (
      I0 => DSP_A_B_DATA_INST_0(128),
      I1 => \^s_conv_counter_reg[0]\,
      I2 => DSP_A_B_DATA_INST(3),
      I3 => S_MULT_reg_i_51_n_0,
      I4 => DSP_A_B_DATA_INST(2),
      I5 => S_MULT_reg_i_52_n_0,
      O => S_MULT_reg_i_17_n_0
    );
S_MULT_reg_i_18: unisim.vcomponents.LUT6
    generic map(
      INIT => X"8F808F8F8F808080"
    )
        port map (
      I0 => DSP_A_B_DATA_INST_0(127),
      I1 => \^s_conv_counter_reg[0]\,
      I2 => DSP_A_B_DATA_INST(3),
      I3 => S_MULT_reg_i_53_n_0,
      I4 => DSP_A_B_DATA_INST(2),
      I5 => S_MULT_reg_i_54_n_0,
      O => S_MULT_reg_i_18_n_0
    );
S_MULT_reg_i_19: unisim.vcomponents.LUT6
    generic map(
      INIT => X"8F808F8F8F808080"
    )
        port map (
      I0 => DSP_A_B_DATA_INST_0(126),
      I1 => \^s_conv_counter_reg[0]\,
      I2 => DSP_A_B_DATA_INST(3),
      I3 => S_MULT_reg_i_55_n_0,
      I4 => DSP_A_B_DATA_INST(2),
      I5 => S_MULT_reg_i_56_n_0,
      O => S_MULT_reg_i_19_n_0
    );
S_MULT_reg_i_2: unisim.vcomponents.LUT6
    generic map(
      INIT => X"8F808F8F8F808080"
    )
        port map (
      I0 => DSP_A_B_DATA_INST_0(143),
      I1 => \^s_conv_counter_reg[0]\,
      I2 => DSP_A_B_DATA_INST(3),
      I3 => S_MULT_reg_i_21_n_0,
      I4 => DSP_A_B_DATA_INST(2),
      I5 => S_MULT_reg_i_22_n_0,
      O => S_MULT_reg_i_2_n_0
    );
S_MULT_reg_i_20: unisim.vcomponents.LUT3
    generic map(
      INIT => X"01"
    )
        port map (
      I0 => DSP_A_B_DATA_INST(0),
      I1 => DSP_A_B_DATA_INST(1),
      I2 => DSP_A_B_DATA_INST(2),
      O => \^s_conv_counter_reg[0]\
    );
S_MULT_reg_i_21: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => DSP_A_B_DATA_INST_0(125),
      I1 => DSP_A_B_DATA_INST_0(107),
      I2 => DSP_A_B_DATA_INST(1),
      I3 => DSP_A_B_DATA_INST_0(89),
      I4 => DSP_A_B_DATA_INST(0),
      I5 => DSP_A_B_DATA_INST_0(71),
      O => S_MULT_reg_i_21_n_0
    );
S_MULT_reg_i_22: unisim.vcomponents.LUT5
    generic map(
      INIT => X"AFC0A0C0"
    )
        port map (
      I0 => DSP_A_B_DATA_INST_0(53),
      I1 => DSP_A_B_DATA_INST_0(35),
      I2 => DSP_A_B_DATA_INST(1),
      I3 => DSP_A_B_DATA_INST(0),
      I4 => DSP_A_B_DATA_INST_0(17),
      O => S_MULT_reg_i_22_n_0
    );
S_MULT_reg_i_23: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => DSP_A_B_DATA_INST_0(124),
      I1 => DSP_A_B_DATA_INST_0(106),
      I2 => DSP_A_B_DATA_INST(1),
      I3 => DSP_A_B_DATA_INST_0(88),
      I4 => DSP_A_B_DATA_INST(0),
      I5 => DSP_A_B_DATA_INST_0(70),
      O => S_MULT_reg_i_23_n_0
    );
S_MULT_reg_i_24: unisim.vcomponents.LUT5
    generic map(
      INIT => X"AFC0A0C0"
    )
        port map (
      I0 => DSP_A_B_DATA_INST_0(52),
      I1 => DSP_A_B_DATA_INST_0(34),
      I2 => DSP_A_B_DATA_INST(1),
      I3 => DSP_A_B_DATA_INST(0),
      I4 => DSP_A_B_DATA_INST_0(16),
      O => S_MULT_reg_i_24_n_0
    );
S_MULT_reg_i_25: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => DSP_A_B_DATA_INST_0(123),
      I1 => DSP_A_B_DATA_INST_0(105),
      I2 => DSP_A_B_DATA_INST(1),
      I3 => DSP_A_B_DATA_INST_0(87),
      I4 => DSP_A_B_DATA_INST(0),
      I5 => DSP_A_B_DATA_INST_0(69),
      O => S_MULT_reg_i_25_n_0
    );
S_MULT_reg_i_26: unisim.vcomponents.LUT5
    generic map(
      INIT => X"AFC0A0C0"
    )
        port map (
      I0 => DSP_A_B_DATA_INST_0(51),
      I1 => DSP_A_B_DATA_INST_0(33),
      I2 => DSP_A_B_DATA_INST(1),
      I3 => DSP_A_B_DATA_INST(0),
      I4 => DSP_A_B_DATA_INST_0(15),
      O => S_MULT_reg_i_26_n_0
    );
S_MULT_reg_i_27: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => DSP_A_B_DATA_INST_0(122),
      I1 => DSP_A_B_DATA_INST_0(104),
      I2 => DSP_A_B_DATA_INST(1),
      I3 => DSP_A_B_DATA_INST_0(86),
      I4 => DSP_A_B_DATA_INST(0),
      I5 => DSP_A_B_DATA_INST_0(68),
      O => S_MULT_reg_i_27_n_0
    );
S_MULT_reg_i_28: unisim.vcomponents.LUT5
    generic map(
      INIT => X"AFC0A0C0"
    )
        port map (
      I0 => DSP_A_B_DATA_INST_0(50),
      I1 => DSP_A_B_DATA_INST_0(32),
      I2 => DSP_A_B_DATA_INST(1),
      I3 => DSP_A_B_DATA_INST(0),
      I4 => DSP_A_B_DATA_INST_0(14),
      O => S_MULT_reg_i_28_n_0
    );
S_MULT_reg_i_29: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => DSP_A_B_DATA_INST_0(121),
      I1 => DSP_A_B_DATA_INST_0(103),
      I2 => DSP_A_B_DATA_INST(1),
      I3 => DSP_A_B_DATA_INST_0(85),
      I4 => DSP_A_B_DATA_INST(0),
      I5 => DSP_A_B_DATA_INST_0(67),
      O => S_MULT_reg_i_29_n_0
    );
S_MULT_reg_i_3: unisim.vcomponents.LUT6
    generic map(
      INIT => X"8F808F8F8F808080"
    )
        port map (
      I0 => DSP_A_B_DATA_INST_0(142),
      I1 => \^s_conv_counter_reg[0]\,
      I2 => DSP_A_B_DATA_INST(3),
      I3 => S_MULT_reg_i_23_n_0,
      I4 => DSP_A_B_DATA_INST(2),
      I5 => S_MULT_reg_i_24_n_0,
      O => S_MULT_reg_i_3_n_0
    );
S_MULT_reg_i_30: unisim.vcomponents.LUT5
    generic map(
      INIT => X"AFC0A0C0"
    )
        port map (
      I0 => DSP_A_B_DATA_INST_0(49),
      I1 => DSP_A_B_DATA_INST_0(31),
      I2 => DSP_A_B_DATA_INST(1),
      I3 => DSP_A_B_DATA_INST(0),
      I4 => DSP_A_B_DATA_INST_0(13),
      O => S_MULT_reg_i_30_n_0
    );
S_MULT_reg_i_31: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => DSP_A_B_DATA_INST_0(120),
      I1 => DSP_A_B_DATA_INST_0(102),
      I2 => DSP_A_B_DATA_INST(1),
      I3 => DSP_A_B_DATA_INST_0(84),
      I4 => DSP_A_B_DATA_INST(0),
      I5 => DSP_A_B_DATA_INST_0(66),
      O => S_MULT_reg_i_31_n_0
    );
S_MULT_reg_i_32: unisim.vcomponents.LUT5
    generic map(
      INIT => X"AFC0A0C0"
    )
        port map (
      I0 => DSP_A_B_DATA_INST_0(48),
      I1 => DSP_A_B_DATA_INST_0(30),
      I2 => DSP_A_B_DATA_INST(1),
      I3 => DSP_A_B_DATA_INST(0),
      I4 => DSP_A_B_DATA_INST_0(12),
      O => S_MULT_reg_i_32_n_0
    );
S_MULT_reg_i_33: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => DSP_A_B_DATA_INST_0(119),
      I1 => DSP_A_B_DATA_INST_0(101),
      I2 => DSP_A_B_DATA_INST(1),
      I3 => DSP_A_B_DATA_INST_0(83),
      I4 => DSP_A_B_DATA_INST(0),
      I5 => DSP_A_B_DATA_INST_0(65),
      O => S_MULT_reg_i_33_n_0
    );
S_MULT_reg_i_34: unisim.vcomponents.LUT5
    generic map(
      INIT => X"AFC0A0C0"
    )
        port map (
      I0 => DSP_A_B_DATA_INST_0(47),
      I1 => DSP_A_B_DATA_INST_0(29),
      I2 => DSP_A_B_DATA_INST(1),
      I3 => DSP_A_B_DATA_INST(0),
      I4 => DSP_A_B_DATA_INST_0(11),
      O => S_MULT_reg_i_34_n_0
    );
S_MULT_reg_i_35: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => DSP_A_B_DATA_INST_0(118),
      I1 => DSP_A_B_DATA_INST_0(100),
      I2 => DSP_A_B_DATA_INST(1),
      I3 => DSP_A_B_DATA_INST_0(82),
      I4 => DSP_A_B_DATA_INST(0),
      I5 => DSP_A_B_DATA_INST_0(64),
      O => S_MULT_reg_i_35_n_0
    );
S_MULT_reg_i_36: unisim.vcomponents.LUT5
    generic map(
      INIT => X"AFC0A0C0"
    )
        port map (
      I0 => DSP_A_B_DATA_INST_0(46),
      I1 => DSP_A_B_DATA_INST_0(28),
      I2 => DSP_A_B_DATA_INST(1),
      I3 => DSP_A_B_DATA_INST(0),
      I4 => DSP_A_B_DATA_INST_0(10),
      O => S_MULT_reg_i_36_n_0
    );
S_MULT_reg_i_37: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => DSP_A_B_DATA_INST_0(117),
      I1 => DSP_A_B_DATA_INST_0(99),
      I2 => DSP_A_B_DATA_INST(1),
      I3 => DSP_A_B_DATA_INST_0(81),
      I4 => DSP_A_B_DATA_INST(0),
      I5 => DSP_A_B_DATA_INST_0(63),
      O => S_MULT_reg_i_37_n_0
    );
S_MULT_reg_i_38: unisim.vcomponents.LUT5
    generic map(
      INIT => X"AFC0A0C0"
    )
        port map (
      I0 => DSP_A_B_DATA_INST_0(45),
      I1 => DSP_A_B_DATA_INST_0(27),
      I2 => DSP_A_B_DATA_INST(1),
      I3 => DSP_A_B_DATA_INST(0),
      I4 => DSP_A_B_DATA_INST_0(9),
      O => S_MULT_reg_i_38_n_0
    );
S_MULT_reg_i_39: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => DSP_A_B_DATA_INST_0(116),
      I1 => DSP_A_B_DATA_INST_0(98),
      I2 => DSP_A_B_DATA_INST(1),
      I3 => DSP_A_B_DATA_INST_0(80),
      I4 => DSP_A_B_DATA_INST(0),
      I5 => DSP_A_B_DATA_INST_0(62),
      O => S_MULT_reg_i_39_n_0
    );
S_MULT_reg_i_4: unisim.vcomponents.LUT6
    generic map(
      INIT => X"8F808F8F8F808080"
    )
        port map (
      I0 => DSP_A_B_DATA_INST_0(141),
      I1 => \^s_conv_counter_reg[0]\,
      I2 => DSP_A_B_DATA_INST(3),
      I3 => S_MULT_reg_i_25_n_0,
      I4 => DSP_A_B_DATA_INST(2),
      I5 => S_MULT_reg_i_26_n_0,
      O => S_MULT_reg_i_4_n_0
    );
S_MULT_reg_i_40: unisim.vcomponents.LUT5
    generic map(
      INIT => X"AFC0A0C0"
    )
        port map (
      I0 => DSP_A_B_DATA_INST_0(44),
      I1 => DSP_A_B_DATA_INST_0(26),
      I2 => DSP_A_B_DATA_INST(1),
      I3 => DSP_A_B_DATA_INST(0),
      I4 => DSP_A_B_DATA_INST_0(8),
      O => S_MULT_reg_i_40_n_0
    );
S_MULT_reg_i_41: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => DSP_A_B_DATA_INST_0(115),
      I1 => DSP_A_B_DATA_INST_0(97),
      I2 => DSP_A_B_DATA_INST(1),
      I3 => DSP_A_B_DATA_INST_0(79),
      I4 => DSP_A_B_DATA_INST(0),
      I5 => DSP_A_B_DATA_INST_0(61),
      O => S_MULT_reg_i_41_n_0
    );
S_MULT_reg_i_42: unisim.vcomponents.LUT5
    generic map(
      INIT => X"AFC0A0C0"
    )
        port map (
      I0 => DSP_A_B_DATA_INST_0(43),
      I1 => DSP_A_B_DATA_INST_0(25),
      I2 => DSP_A_B_DATA_INST(1),
      I3 => DSP_A_B_DATA_INST(0),
      I4 => DSP_A_B_DATA_INST_0(7),
      O => S_MULT_reg_i_42_n_0
    );
S_MULT_reg_i_43: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => DSP_A_B_DATA_INST_0(114),
      I1 => DSP_A_B_DATA_INST_0(96),
      I2 => DSP_A_B_DATA_INST(1),
      I3 => DSP_A_B_DATA_INST_0(78),
      I4 => DSP_A_B_DATA_INST(0),
      I5 => DSP_A_B_DATA_INST_0(60),
      O => S_MULT_reg_i_43_n_0
    );
S_MULT_reg_i_44: unisim.vcomponents.LUT5
    generic map(
      INIT => X"AFC0A0C0"
    )
        port map (
      I0 => DSP_A_B_DATA_INST_0(42),
      I1 => DSP_A_B_DATA_INST_0(24),
      I2 => DSP_A_B_DATA_INST(1),
      I3 => DSP_A_B_DATA_INST(0),
      I4 => DSP_A_B_DATA_INST_0(6),
      O => S_MULT_reg_i_44_n_0
    );
S_MULT_reg_i_45: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => DSP_A_B_DATA_INST_0(113),
      I1 => DSP_A_B_DATA_INST_0(95),
      I2 => DSP_A_B_DATA_INST(1),
      I3 => DSP_A_B_DATA_INST_0(77),
      I4 => DSP_A_B_DATA_INST(0),
      I5 => DSP_A_B_DATA_INST_0(59),
      O => S_MULT_reg_i_45_n_0
    );
S_MULT_reg_i_46: unisim.vcomponents.LUT5
    generic map(
      INIT => X"AFC0A0C0"
    )
        port map (
      I0 => DSP_A_B_DATA_INST_0(41),
      I1 => DSP_A_B_DATA_INST_0(23),
      I2 => DSP_A_B_DATA_INST(1),
      I3 => DSP_A_B_DATA_INST(0),
      I4 => DSP_A_B_DATA_INST_0(5),
      O => S_MULT_reg_i_46_n_0
    );
S_MULT_reg_i_47: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => DSP_A_B_DATA_INST_0(112),
      I1 => DSP_A_B_DATA_INST_0(94),
      I2 => DSP_A_B_DATA_INST(1),
      I3 => DSP_A_B_DATA_INST_0(76),
      I4 => DSP_A_B_DATA_INST(0),
      I5 => DSP_A_B_DATA_INST_0(58),
      O => S_MULT_reg_i_47_n_0
    );
S_MULT_reg_i_48: unisim.vcomponents.LUT5
    generic map(
      INIT => X"AFC0A0C0"
    )
        port map (
      I0 => DSP_A_B_DATA_INST_0(40),
      I1 => DSP_A_B_DATA_INST_0(22),
      I2 => DSP_A_B_DATA_INST(1),
      I3 => DSP_A_B_DATA_INST(0),
      I4 => DSP_A_B_DATA_INST_0(4),
      O => S_MULT_reg_i_48_n_0
    );
S_MULT_reg_i_49: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => DSP_A_B_DATA_INST_0(111),
      I1 => DSP_A_B_DATA_INST_0(93),
      I2 => DSP_A_B_DATA_INST(1),
      I3 => DSP_A_B_DATA_INST_0(75),
      I4 => DSP_A_B_DATA_INST(0),
      I5 => DSP_A_B_DATA_INST_0(57),
      O => S_MULT_reg_i_49_n_0
    );
S_MULT_reg_i_5: unisim.vcomponents.LUT6
    generic map(
      INIT => X"8F808F8F8F808080"
    )
        port map (
      I0 => DSP_A_B_DATA_INST_0(140),
      I1 => \^s_conv_counter_reg[0]\,
      I2 => DSP_A_B_DATA_INST(3),
      I3 => S_MULT_reg_i_27_n_0,
      I4 => DSP_A_B_DATA_INST(2),
      I5 => S_MULT_reg_i_28_n_0,
      O => S_MULT_reg_i_5_n_0
    );
S_MULT_reg_i_50: unisim.vcomponents.LUT5
    generic map(
      INIT => X"AFC0A0C0"
    )
        port map (
      I0 => DSP_A_B_DATA_INST_0(39),
      I1 => DSP_A_B_DATA_INST_0(21),
      I2 => DSP_A_B_DATA_INST(1),
      I3 => DSP_A_B_DATA_INST(0),
      I4 => DSP_A_B_DATA_INST_0(3),
      O => S_MULT_reg_i_50_n_0
    );
S_MULT_reg_i_51: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => DSP_A_B_DATA_INST_0(110),
      I1 => DSP_A_B_DATA_INST_0(92),
      I2 => DSP_A_B_DATA_INST(1),
      I3 => DSP_A_B_DATA_INST_0(74),
      I4 => DSP_A_B_DATA_INST(0),
      I5 => DSP_A_B_DATA_INST_0(56),
      O => S_MULT_reg_i_51_n_0
    );
S_MULT_reg_i_52: unisim.vcomponents.LUT5
    generic map(
      INIT => X"AFC0A0C0"
    )
        port map (
      I0 => DSP_A_B_DATA_INST_0(38),
      I1 => DSP_A_B_DATA_INST_0(20),
      I2 => DSP_A_B_DATA_INST(1),
      I3 => DSP_A_B_DATA_INST(0),
      I4 => DSP_A_B_DATA_INST_0(2),
      O => S_MULT_reg_i_52_n_0
    );
S_MULT_reg_i_53: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => DSP_A_B_DATA_INST_0(109),
      I1 => DSP_A_B_DATA_INST_0(91),
      I2 => DSP_A_B_DATA_INST(1),
      I3 => DSP_A_B_DATA_INST_0(73),
      I4 => DSP_A_B_DATA_INST(0),
      I5 => DSP_A_B_DATA_INST_0(55),
      O => S_MULT_reg_i_53_n_0
    );
S_MULT_reg_i_54: unisim.vcomponents.LUT5
    generic map(
      INIT => X"AFC0A0C0"
    )
        port map (
      I0 => DSP_A_B_DATA_INST_0(37),
      I1 => DSP_A_B_DATA_INST_0(19),
      I2 => DSP_A_B_DATA_INST(1),
      I3 => DSP_A_B_DATA_INST(0),
      I4 => DSP_A_B_DATA_INST_0(1),
      O => S_MULT_reg_i_54_n_0
    );
S_MULT_reg_i_55: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => DSP_A_B_DATA_INST_0(108),
      I1 => DSP_A_B_DATA_INST_0(90),
      I2 => DSP_A_B_DATA_INST(1),
      I3 => DSP_A_B_DATA_INST_0(72),
      I4 => DSP_A_B_DATA_INST(0),
      I5 => DSP_A_B_DATA_INST_0(54),
      O => S_MULT_reg_i_55_n_0
    );
S_MULT_reg_i_56: unisim.vcomponents.LUT5
    generic map(
      INIT => X"AFC0A0C0"
    )
        port map (
      I0 => DSP_A_B_DATA_INST_0(36),
      I1 => DSP_A_B_DATA_INST_0(18),
      I2 => DSP_A_B_DATA_INST(1),
      I3 => DSP_A_B_DATA_INST(0),
      I4 => DSP_A_B_DATA_INST_0(0),
      O => S_MULT_reg_i_56_n_0
    );
S_MULT_reg_i_6: unisim.vcomponents.LUT6
    generic map(
      INIT => X"8F808F8F8F808080"
    )
        port map (
      I0 => DSP_A_B_DATA_INST_0(139),
      I1 => \^s_conv_counter_reg[0]\,
      I2 => DSP_A_B_DATA_INST(3),
      I3 => S_MULT_reg_i_29_n_0,
      I4 => DSP_A_B_DATA_INST(2),
      I5 => S_MULT_reg_i_30_n_0,
      O => S_MULT_reg_i_6_n_0
    );
S_MULT_reg_i_7: unisim.vcomponents.LUT6
    generic map(
      INIT => X"8F808F8F8F808080"
    )
        port map (
      I0 => DSP_A_B_DATA_INST_0(138),
      I1 => \^s_conv_counter_reg[0]\,
      I2 => DSP_A_B_DATA_INST(3),
      I3 => S_MULT_reg_i_31_n_0,
      I4 => DSP_A_B_DATA_INST(2),
      I5 => S_MULT_reg_i_32_n_0,
      O => S_MULT_reg_i_7_n_0
    );
S_MULT_reg_i_8: unisim.vcomponents.LUT6
    generic map(
      INIT => X"8F808F8F8F808080"
    )
        port map (
      I0 => DSP_A_B_DATA_INST_0(137),
      I1 => \^s_conv_counter_reg[0]\,
      I2 => DSP_A_B_DATA_INST(3),
      I3 => S_MULT_reg_i_33_n_0,
      I4 => DSP_A_B_DATA_INST(2),
      I5 => S_MULT_reg_i_34_n_0,
      O => S_MULT_reg_i_8_n_0
    );
S_MULT_reg_i_9: unisim.vcomponents.LUT6
    generic map(
      INIT => X"8F808F8F8F808080"
    )
        port map (
      I0 => DSP_A_B_DATA_INST_0(136),
      I1 => \^s_conv_counter_reg[0]\,
      I2 => DSP_A_B_DATA_INST(3),
      I3 => S_MULT_reg_i_35_n_0,
      I4 => DSP_A_B_DATA_INST(2),
      I5 => S_MULT_reg_i_36_n_0,
      O => S_MULT_reg_i_9_n_0
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity zusys_A3_ADC_LTC2311_0_SPI_MASTER is
  port (
    S_SCLK : out STD_LOGIC;
    SS_N : out STD_LOGIC_VECTOR ( 0 to 0 );
    S_SPI_BUSY : out STD_LOGIC;
    E : out STD_LOGIC_VECTOR ( 0 to 0 );
    D : out STD_LOGIC_VECTOR ( 0 to 0 );
    \S_RX_OUT_BUFFER_reg[127]_0\ : out STD_LOGIC_VECTOR ( 15 downto 0 );
    RAW_VALUE : out STD_LOGIC_VECTOR ( 127 downto 0 );
    CPHA : in STD_LOGIC;
    s00_axi_aclk : in STD_LOGIC;
    CPOL : in STD_LOGIC;
    S_CPOL_reg_0 : in STD_LOGIC_VECTOR ( 0 to 0 );
    s00_axi_aresetn : in STD_LOGIC;
    \S_BIT_COUNT_reg[0]_0\ : in STD_LOGIC;
    S_AXI_ARESETN : in STD_LOGIC;
    \S_DEL_COUNT_reg[7]_0\ : in STD_LOGIC_VECTOR ( 31 downto 0 );
    S_SCLK_reg_0 : in STD_LOGIC;
    SCLK_IN : in STD_LOGIC;
    SS_IN_N : in STD_LOGIC;
    \S_SAMPLE_TIME_COUNTER_reg[0]\ : in STD_LOGIC;
    Q : in STD_LOGIC_VECTOR ( 1 downto 0 );
    \S_SAMPLE_TIME_COUNTER_reg[0]_0\ : in STD_LOGIC;
    \S_SAMPLE_TIME_COUNTER_reg[0]_1\ : in STD_LOGIC;
    \S_RAW_VALUE_S_C_reg[0]\ : in STD_LOGIC;
    \S_RAW_VALUE_S_C_reg[0]_0\ : in STD_LOGIC_VECTOR ( 3 downto 0 );
    RSTP : in STD_LOGIC;
    \S_RX_BUFFER_reg[112]_0\ : in STD_LOGIC_VECTOR ( 7 downto 0 )
  );
  attribute ORIG_REF_NAME : string;
  attribute ORIG_REF_NAME of zusys_A3_ADC_LTC2311_0_SPI_MASTER : entity is "SPI_MASTER";
end zusys_A3_ADC_LTC2311_0_SPI_MASTER;

architecture STRUCTURE of zusys_A3_ADC_LTC2311_0_SPI_MASTER is
  signal BUSY_i_1_n_0 : STD_LOGIC;
  signal BUSY_i_2_n_0 : STD_LOGIC;
  signal \^raw_value\ : STD_LOGIC_VECTOR ( 127 downto 0 );
  signal \^ss_n\ : STD_LOGIC_VECTOR ( 0 to 0 );
  signal SS_OUT_N1_out : STD_LOGIC;
  signal SS_OUT_N_i_10_n_0 : STD_LOGIC;
  signal SS_OUT_N_i_1_n_0 : STD_LOGIC;
  signal SS_OUT_N_i_2_n_0 : STD_LOGIC;
  signal SS_OUT_N_i_3_n_0 : STD_LOGIC;
  signal SS_OUT_N_i_4_n_0 : STD_LOGIC;
  signal SS_OUT_N_i_6_n_0 : STD_LOGIC;
  signal SS_OUT_N_i_7_n_0 : STD_LOGIC;
  signal SS_OUT_N_i_8_n_0 : STD_LOGIC;
  signal SS_OUT_N_i_9_n_0 : STD_LOGIC;
  signal S_BIT_COUNT : STD_LOGIC_VECTOR ( 5 downto 0 );
  signal \S_BIT_COUNT[0]_i_2_n_0\ : STD_LOGIC;
  signal \S_BIT_COUNT[4]_i_2_n_0\ : STD_LOGIC;
  signal \S_BIT_COUNT[4]_i_3_n_0\ : STD_LOGIC;
  signal \S_BIT_COUNT[5]_i_10_n_0\ : STD_LOGIC;
  signal \S_BIT_COUNT[5]_i_11_n_0\ : STD_LOGIC;
  signal \S_BIT_COUNT[5]_i_12_n_0\ : STD_LOGIC;
  signal \S_BIT_COUNT[5]_i_13_n_0\ : STD_LOGIC;
  signal \S_BIT_COUNT[5]_i_14_n_0\ : STD_LOGIC;
  signal \S_BIT_COUNT[5]_i_15_n_0\ : STD_LOGIC;
  signal \S_BIT_COUNT[5]_i_1_n_0\ : STD_LOGIC;
  signal \S_BIT_COUNT[5]_i_3_n_0\ : STD_LOGIC;
  signal \S_BIT_COUNT[5]_i_5_n_0\ : STD_LOGIC;
  signal \S_BIT_COUNT[5]_i_7_n_0\ : STD_LOGIC;
  signal \S_BIT_COUNT[5]_i_8_n_0\ : STD_LOGIC;
  signal \S_BIT_COUNT[5]_i_9_n_0\ : STD_LOGIC;
  signal \S_BIT_COUNT_reg[5]_i_6_n_0\ : STD_LOGIC;
  signal \S_BIT_COUNT_reg[5]_i_6_n_1\ : STD_LOGIC;
  signal \S_BIT_COUNT_reg[5]_i_6_n_2\ : STD_LOGIC;
  signal \S_BIT_COUNT_reg[5]_i_6_n_3\ : STD_LOGIC;
  signal \S_BIT_COUNT_reg[5]_i_6_n_4\ : STD_LOGIC;
  signal \S_BIT_COUNT_reg[5]_i_6_n_5\ : STD_LOGIC;
  signal \S_BIT_COUNT_reg[5]_i_6_n_6\ : STD_LOGIC;
  signal \S_BIT_COUNT_reg[5]_i_6_n_7\ : STD_LOGIC;
  signal \S_BIT_COUNT_reg_n_0_[0]\ : STD_LOGIC;
  signal \S_BIT_COUNT_reg_n_0_[1]\ : STD_LOGIC;
  signal \S_BIT_COUNT_reg_n_0_[2]\ : STD_LOGIC;
  signal \S_BIT_COUNT_reg_n_0_[3]\ : STD_LOGIC;
  signal \S_BIT_COUNT_reg_n_0_[4]\ : STD_LOGIC;
  signal \S_BIT_COUNT_reg_n_0_[5]\ : STD_LOGIC;
  signal S_CLK_DIV : STD_LOGIC_VECTOR ( 15 downto 0 );
  signal S_CPHA : STD_LOGIC;
  signal S_CPHA_reg_n_0 : STD_LOGIC;
  signal S_CPOL : STD_LOGIC;
  signal S_CPOL_reg_n_0 : STD_LOGIC;
  signal S_DEL_CLK : STD_LOGIC_VECTOR ( 16 downto 0 );
  signal S_DEL_CLK0 : STD_LOGIC_VECTOR ( 16 downto 1 );
  signal S_DEL_CLK1_in : STD_LOGIC_VECTOR ( 16 downto 0 );
  signal \S_DEL_CLK[15]_i_2_n_0\ : STD_LOGIC;
  signal \S_DEL_CLK[15]_i_3_n_0\ : STD_LOGIC;
  signal \S_DEL_CLK[15]_i_4_n_0\ : STD_LOGIC;
  signal \S_DEL_CLK[16]_i_10_n_0\ : STD_LOGIC;
  signal \S_DEL_CLK[16]_i_11_n_0\ : STD_LOGIC;
  signal \S_DEL_CLK[16]_i_12_n_0\ : STD_LOGIC;
  signal \S_DEL_CLK[16]_i_13_n_0\ : STD_LOGIC;
  signal \S_DEL_CLK[16]_i_3_n_0\ : STD_LOGIC;
  signal \S_DEL_CLK[16]_i_4_n_0\ : STD_LOGIC;
  signal \S_DEL_CLK[16]_i_6_n_0\ : STD_LOGIC;
  signal \S_DEL_CLK[16]_i_7_n_0\ : STD_LOGIC;
  signal \S_DEL_CLK[16]_i_8_n_0\ : STD_LOGIC;
  signal \S_DEL_CLK[16]_i_9_n_0\ : STD_LOGIC;
  signal \S_DEL_CLK[8]_i_10_n_0\ : STD_LOGIC;
  signal \S_DEL_CLK[8]_i_3_n_0\ : STD_LOGIC;
  signal \S_DEL_CLK[8]_i_4_n_0\ : STD_LOGIC;
  signal \S_DEL_CLK[8]_i_5_n_0\ : STD_LOGIC;
  signal \S_DEL_CLK[8]_i_6_n_0\ : STD_LOGIC;
  signal \S_DEL_CLK[8]_i_7_n_0\ : STD_LOGIC;
  signal \S_DEL_CLK[8]_i_8_n_0\ : STD_LOGIC;
  signal \S_DEL_CLK[8]_i_9_n_0\ : STD_LOGIC;
  signal \S_DEL_CLK_reg[16]_i_5_n_1\ : STD_LOGIC;
  signal \S_DEL_CLK_reg[16]_i_5_n_2\ : STD_LOGIC;
  signal \S_DEL_CLK_reg[16]_i_5_n_3\ : STD_LOGIC;
  signal \S_DEL_CLK_reg[16]_i_5_n_4\ : STD_LOGIC;
  signal \S_DEL_CLK_reg[16]_i_5_n_5\ : STD_LOGIC;
  signal \S_DEL_CLK_reg[16]_i_5_n_6\ : STD_LOGIC;
  signal \S_DEL_CLK_reg[16]_i_5_n_7\ : STD_LOGIC;
  signal \S_DEL_CLK_reg[8]_i_2_n_0\ : STD_LOGIC;
  signal \S_DEL_CLK_reg[8]_i_2_n_1\ : STD_LOGIC;
  signal \S_DEL_CLK_reg[8]_i_2_n_2\ : STD_LOGIC;
  signal \S_DEL_CLK_reg[8]_i_2_n_3\ : STD_LOGIC;
  signal \S_DEL_CLK_reg[8]_i_2_n_4\ : STD_LOGIC;
  signal \S_DEL_CLK_reg[8]_i_2_n_5\ : STD_LOGIC;
  signal \S_DEL_CLK_reg[8]_i_2_n_6\ : STD_LOGIC;
  signal \S_DEL_CLK_reg[8]_i_2_n_7\ : STD_LOGIC;
  signal S_DEL_COUNT : STD_LOGIC_VECTOR ( 8 downto 0 );
  signal S_DEL_COUNT1_in : STD_LOGIC_VECTOR ( 8 downto 0 );
  signal \S_DEL_COUNT[1]_i_2_n_0\ : STD_LOGIC;
  signal \S_DEL_COUNT[2]_i_2_n_0\ : STD_LOGIC;
  signal \S_DEL_COUNT[3]_i_2_n_0\ : STD_LOGIC;
  signal \S_DEL_COUNT[4]_i_2_n_0\ : STD_LOGIC;
  signal \S_DEL_COUNT[5]_i_2_n_0\ : STD_LOGIC;
  signal \S_DEL_COUNT[6]_i_2_n_0\ : STD_LOGIC;
  signal \S_DEL_COUNT[6]_i_3_n_0\ : STD_LOGIC;
  signal \S_DEL_COUNT[6]_i_4_n_0\ : STD_LOGIC;
  signal \S_DEL_COUNT[7]_i_2_n_0\ : STD_LOGIC;
  signal \S_DEL_COUNT[7]_i_3_n_0\ : STD_LOGIC;
  signal \S_DEL_COUNT[8]_i_1_n_0\ : STD_LOGIC;
  signal \S_DEL_COUNT[8]_i_3_n_0\ : STD_LOGIC;
  signal \S_DEL_COUNT[8]_i_4_n_0\ : STD_LOGIC;
  signal S_PRE_DELAY : STD_LOGIC_VECTOR ( 7 downto 0 );
  signal \S_RAW_VALUE_S_C[0]_i_2_n_0\ : STD_LOGIC;
  signal \S_RAW_VALUE_S_C[0]_i_3_n_0\ : STD_LOGIC;
  signal \S_RAW_VALUE_S_C[10]_i_2_n_0\ : STD_LOGIC;
  signal \S_RAW_VALUE_S_C[10]_i_3_n_0\ : STD_LOGIC;
  signal \S_RAW_VALUE_S_C[11]_i_2_n_0\ : STD_LOGIC;
  signal \S_RAW_VALUE_S_C[11]_i_3_n_0\ : STD_LOGIC;
  signal \S_RAW_VALUE_S_C[12]_i_2_n_0\ : STD_LOGIC;
  signal \S_RAW_VALUE_S_C[12]_i_3_n_0\ : STD_LOGIC;
  signal \S_RAW_VALUE_S_C[13]_i_2_n_0\ : STD_LOGIC;
  signal \S_RAW_VALUE_S_C[13]_i_3_n_0\ : STD_LOGIC;
  signal \S_RAW_VALUE_S_C[14]_i_2_n_0\ : STD_LOGIC;
  signal \S_RAW_VALUE_S_C[14]_i_3_n_0\ : STD_LOGIC;
  signal \S_RAW_VALUE_S_C[15]_i_4_n_0\ : STD_LOGIC;
  signal \S_RAW_VALUE_S_C[15]_i_5_n_0\ : STD_LOGIC;
  signal \S_RAW_VALUE_S_C[1]_i_2_n_0\ : STD_LOGIC;
  signal \S_RAW_VALUE_S_C[1]_i_3_n_0\ : STD_LOGIC;
  signal \S_RAW_VALUE_S_C[2]_i_2_n_0\ : STD_LOGIC;
  signal \S_RAW_VALUE_S_C[2]_i_3_n_0\ : STD_LOGIC;
  signal \S_RAW_VALUE_S_C[3]_i_2_n_0\ : STD_LOGIC;
  signal \S_RAW_VALUE_S_C[3]_i_3_n_0\ : STD_LOGIC;
  signal \S_RAW_VALUE_S_C[4]_i_2_n_0\ : STD_LOGIC;
  signal \S_RAW_VALUE_S_C[4]_i_3_n_0\ : STD_LOGIC;
  signal \S_RAW_VALUE_S_C[5]_i_2_n_0\ : STD_LOGIC;
  signal \S_RAW_VALUE_S_C[5]_i_3_n_0\ : STD_LOGIC;
  signal \S_RAW_VALUE_S_C[6]_i_2_n_0\ : STD_LOGIC;
  signal \S_RAW_VALUE_S_C[6]_i_3_n_0\ : STD_LOGIC;
  signal \S_RAW_VALUE_S_C[7]_i_2_n_0\ : STD_LOGIC;
  signal \S_RAW_VALUE_S_C[7]_i_3_n_0\ : STD_LOGIC;
  signal \S_RAW_VALUE_S_C[8]_i_2_n_0\ : STD_LOGIC;
  signal \S_RAW_VALUE_S_C[8]_i_3_n_0\ : STD_LOGIC;
  signal \S_RAW_VALUE_S_C[9]_i_2_n_0\ : STD_LOGIC;
  signal \S_RAW_VALUE_S_C[9]_i_3_n_0\ : STD_LOGIC;
  signal S_RX_BUFFER : STD_LOGIC;
  signal \S_RX_BUFFER_reg_n_0_[111]\ : STD_LOGIC;
  signal \S_RX_BUFFER_reg_n_0_[127]\ : STD_LOGIC;
  signal \S_RX_BUFFER_reg_n_0_[15]\ : STD_LOGIC;
  signal \S_RX_BUFFER_reg_n_0_[31]\ : STD_LOGIC;
  signal \S_RX_BUFFER_reg_n_0_[47]\ : STD_LOGIC;
  signal \S_RX_BUFFER_reg_n_0_[63]\ : STD_LOGIC;
  signal \S_RX_BUFFER_reg_n_0_[79]\ : STD_LOGIC;
  signal \S_RX_BUFFER_reg_n_0_[95]\ : STD_LOGIC;
  signal S_RX_OUT_BUFFER : STD_LOGIC;
  signal \S_RX_OUT_BUFFER[127]_i_3_n_0\ : STD_LOGIC;
  signal \^s_sclk\ : STD_LOGIC;
  signal S_SCLK_i_1_n_0 : STD_LOGIC;
  signal S_SCLK_i_2_n_0 : STD_LOGIC;
  signal S_SCLK_i_3_n_0 : STD_LOGIC;
  signal S_SCLK_i_4_n_0 : STD_LOGIC;
  signal S_SCLK_i_5_n_0 : STD_LOGIC;
  signal S_SCLK_i_6_n_0 : STD_LOGIC;
  signal S_SCLK_i_7_n_0 : STD_LOGIC;
  signal S_SCLK_i_8_n_0 : STD_LOGIC;
  signal S_SCLK_i_9_n_0 : STD_LOGIC;
  signal \^s_spi_busy\ : STD_LOGIC;
  signal curstate : STD_LOGIC_VECTOR ( 2 downto 0 );
  signal \curstate[0]_i_2_n_0\ : STD_LOGIC;
  signal \curstate[0]_i_3_n_0\ : STD_LOGIC;
  signal \curstate[0]_i_4_n_0\ : STD_LOGIC;
  signal \curstate[2]_i_2_n_0\ : STD_LOGIC;
  signal nxtstate : STD_LOGIC_VECTOR ( 2 downto 0 );
  signal nxtstate1 : STD_LOGIC;
  signal p_0_out : STD_LOGIC_VECTOR ( 127 downto 1 );
  signal \NLW_S_BIT_COUNT_reg[5]_i_4_CO_UNCONNECTED\ : STD_LOGIC_VECTOR ( 7 downto 1 );
  signal \NLW_S_BIT_COUNT_reg[5]_i_4_O_UNCONNECTED\ : STD_LOGIC_VECTOR ( 7 downto 0 );
  signal \NLW_S_BIT_COUNT_reg[5]_i_6_O_UNCONNECTED\ : STD_LOGIC_VECTOR ( 7 downto 0 );
  signal \NLW_S_DEL_CLK_reg[16]_i_5_CO_UNCONNECTED\ : STD_LOGIC_VECTOR ( 7 to 7 );
  attribute SOFT_HLUTNM : string;
  attribute SOFT_HLUTNM of BUSY_i_2 : label is "soft_lutpair82";
  attribute SOFT_HLUTNM of SS_OUT_N_i_3 : label is "soft_lutpair79";
  attribute SOFT_HLUTNM of SS_OUT_N_i_6 : label is "soft_lutpair77";
  attribute SOFT_HLUTNM of SS_OUT_N_i_8 : label is "soft_lutpair70";
  attribute SOFT_HLUTNM of SS_OUT_N_i_9 : label is "soft_lutpair82";
  attribute SOFT_HLUTNM of \S_BIT_COUNT[1]_i_1\ : label is "soft_lutpair81";
  attribute SOFT_HLUTNM of \S_BIT_COUNT[2]_i_1\ : label is "soft_lutpair74";
  attribute SOFT_HLUTNM of \S_BIT_COUNT[3]_i_1\ : label is "soft_lutpair74";
  attribute SOFT_HLUTNM of \S_BIT_COUNT[4]_i_3\ : label is "soft_lutpair78";
  attribute SOFT_HLUTNM of \S_BIT_COUNT[5]_i_2\ : label is "soft_lutpair81";
  attribute SOFT_HLUTNM of \S_BIT_COUNT[5]_i_3\ : label is "soft_lutpair75";
  attribute SOFT_HLUTNM of \S_BIT_COUNT[5]_i_5\ : label is "soft_lutpair78";
  attribute COMPARATOR_THRESHOLD : integer;
  attribute COMPARATOR_THRESHOLD of \S_BIT_COUNT_reg[5]_i_4\ : label is 11;
  attribute COMPARATOR_THRESHOLD of \S_BIT_COUNT_reg[5]_i_6\ : label is 11;
  attribute SOFT_HLUTNM of \S_DEL_CLK[15]_i_2\ : label is "soft_lutpair75";
  attribute SOFT_HLUTNM of \S_DEL_CLK[15]_i_4\ : label is "soft_lutpair80";
  attribute ADDER_THRESHOLD : integer;
  attribute ADDER_THRESHOLD of \S_DEL_CLK_reg[16]_i_5\ : label is 35;
  attribute ADDER_THRESHOLD of \S_DEL_CLK_reg[8]_i_2\ : label is 35;
  attribute SOFT_HLUTNM of \S_DEL_COUNT[2]_i_1\ : label is "soft_lutpair73";
  attribute SOFT_HLUTNM of \S_DEL_COUNT[4]_i_2\ : label is "soft_lutpair77";
  attribute SOFT_HLUTNM of \S_DEL_COUNT[6]_i_2\ : label is "soft_lutpair76";
  attribute SOFT_HLUTNM of \S_DEL_COUNT[6]_i_4\ : label is "soft_lutpair73";
  attribute SOFT_HLUTNM of \S_DEL_COUNT[7]_i_1\ : label is "soft_lutpair72";
  attribute SOFT_HLUTNM of \S_DEL_COUNT[8]_i_3\ : label is "soft_lutpair80";
  attribute SOFT_HLUTNM of \S_DEL_COUNT[8]_i_4\ : label is "soft_lutpair79";
  attribute SOFT_HLUTNM of S_SCLK_i_5 : label is "soft_lutpair69";
  attribute SOFT_HLUTNM of S_SCLK_i_6 : label is "soft_lutpair69";
  attribute SOFT_HLUTNM of S_SCLK_i_7 : label is "soft_lutpair70";
  attribute SOFT_HLUTNM of S_SCLK_i_8 : label is "soft_lutpair71";
  attribute SOFT_HLUTNM of \curstate[0]_i_2\ : label is "soft_lutpair71";
  attribute SOFT_HLUTNM of \curstate[0]_i_3\ : label is "soft_lutpair76";
  attribute SOFT_HLUTNM of \curstate[2]_i_2\ : label is "soft_lutpair72";
  attribute FSM_ENCODING : string;
  attribute FSM_ENCODING of \curstate_reg[0]\ : label is "auto";
  attribute FSM_SAFE_STATE : string;
  attribute FSM_SAFE_STATE of \curstate_reg[0]\ : label is "power_on_state";
  attribute FSM_ENCODING of \curstate_reg[1]\ : label is "auto";
  attribute FSM_SAFE_STATE of \curstate_reg[1]\ : label is "power_on_state";
  attribute FSM_ENCODING of \curstate_reg[2]\ : label is "auto";
  attribute FSM_SAFE_STATE of \curstate_reg[2]\ : label is "power_on_state";
begin
  RAW_VALUE(127 downto 0) <= \^raw_value\(127 downto 0);
  SS_N(0) <= \^ss_n\(0);
  S_SCLK <= \^s_sclk\;
  S_SPI_BUSY <= \^s_spi_busy\;
BUSY_i_1: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AAAAFBFFAAAA0800"
    )
        port map (
      I0 => nxtstate(0),
      I1 => s00_axi_aresetn,
      I2 => S_CPOL_reg_0(0),
      I3 => BUSY_i_2_n_0,
      I4 => SS_OUT_N1_out,
      I5 => \^s_spi_busy\,
      O => BUSY_i_1_n_0
    );
BUSY_i_2: unisim.vcomponents.LUT3
    generic map(
      INIT => X"80"
    )
        port map (
      I0 => curstate(1),
      I1 => curstate(0),
      I2 => \S_RX_OUT_BUFFER[127]_i_3_n_0\,
      O => BUSY_i_2_n_0
    );
BUSY_reg: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => '1',
      D => BUSY_i_1_n_0,
      Q => \^s_spi_busy\,
      R => '0'
    );
SS_OUT_N_i_1: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FF08FFFFFF080000"
    )
        port map (
      I0 => SS_OUT_N_i_2_n_0,
      I1 => curstate(2),
      I2 => SS_OUT_N_i_3_n_0,
      I3 => SS_OUT_N_i_4_n_0,
      I4 => SS_OUT_N1_out,
      I5 => \^ss_n\(0),
      O => SS_OUT_N_i_1_n_0
    );
SS_OUT_N_i_10: unisim.vcomponents.LUT2
    generic map(
      INIT => X"B"
    )
        port map (
      I0 => SS_IN_N,
      I1 => S_SCLK_reg_0,
      O => SS_OUT_N_i_10_n_0
    );
SS_OUT_N_i_2: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFFFFFF00000002"
    )
        port map (
      I0 => SS_OUT_N_i_6_n_0,
      I1 => S_DEL_COUNT(7),
      I2 => S_DEL_COUNT(6),
      I3 => S_DEL_COUNT(5),
      I4 => S_DEL_COUNT(4),
      I5 => S_DEL_COUNT(8),
      O => SS_OUT_N_i_2_n_0
    );
SS_OUT_N_i_3: unisim.vcomponents.LUT2
    generic map(
      INIT => X"E"
    )
        port map (
      I0 => curstate(0),
      I1 => curstate(1),
      O => SS_OUT_N_i_3_n_0
    );
SS_OUT_N_i_4: unisim.vcomponents.LUT6
    generic map(
      INIT => X"EFEEEEEEAAAAAAAA"
    )
        port map (
      I0 => SS_OUT_N_i_7_n_0,
      I1 => SS_OUT_N_i_8_n_0,
      I2 => \S_RX_OUT_BUFFER[127]_i_3_n_0\,
      I3 => nxtstate1,
      I4 => SS_OUT_N_i_9_n_0,
      I5 => SS_OUT_N_i_10_n_0,
      O => SS_OUT_N_i_4_n_0
    );
SS_OUT_N_i_5: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0000FE0300000000"
    )
        port map (
      I0 => SS_OUT_N_i_2_n_0,
      I1 => curstate(0),
      I2 => curstate(1),
      I3 => curstate(2),
      I4 => S_CPOL_reg_0(0),
      I5 => s00_axi_aresetn,
      O => SS_OUT_N1_out
    );
SS_OUT_N_i_6: unisim.vcomponents.LUT4
    generic map(
      INIT => X"0001"
    )
        port map (
      I0 => S_DEL_COUNT(1),
      I1 => S_DEL_COUNT(0),
      I2 => S_DEL_COUNT(3),
      I3 => S_DEL_COUNT(2),
      O => SS_OUT_N_i_6_n_0
    );
SS_OUT_N_i_7: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0C00505000000000"
    )
        port map (
      I0 => nxtstate1,
      I1 => SS_OUT_N_i_2_n_0,
      I2 => curstate(1),
      I3 => S_CPHA_reg_n_0,
      I4 => curstate(0),
      I5 => SS_OUT_N_i_10_n_0,
      O => SS_OUT_N_i_7_n_0
    );
SS_OUT_N_i_8: unisim.vcomponents.LUT4
    generic map(
      INIT => X"CCC1"
    )
        port map (
      I0 => \S_BIT_COUNT_reg[0]_0\,
      I1 => curstate(2),
      I2 => curstate(0),
      I3 => curstate(1),
      O => SS_OUT_N_i_8_n_0
    );
SS_OUT_N_i_9: unisim.vcomponents.LUT2
    generic map(
      INIT => X"8"
    )
        port map (
      I0 => curstate(0),
      I1 => curstate(1),
      O => SS_OUT_N_i_9_n_0
    );
SS_OUT_N_reg: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => '1',
      D => SS_OUT_N_i_1_n_0,
      Q => \^ss_n\(0),
      R => '0'
    );
\S_BIT_COUNT[0]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"F0F0FEF2"
    )
        port map (
      I0 => SS_OUT_N_i_2_n_0,
      I1 => curstate(1),
      I2 => \S_BIT_COUNT[4]_i_2_n_0\,
      I3 => \S_BIT_COUNT[0]_i_2_n_0\,
      I4 => \S_BIT_COUNT_reg_n_0_[0]\,
      O => S_BIT_COUNT(0)
    );
\S_BIT_COUNT[0]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"55555554FFFFFFFF"
    )
        port map (
      I0 => \S_BIT_COUNT_reg_n_0_[5]\,
      I1 => \S_BIT_COUNT_reg_n_0_[3]\,
      I2 => \S_BIT_COUNT_reg_n_0_[1]\,
      I3 => \S_BIT_COUNT_reg_n_0_[2]\,
      I4 => \S_BIT_COUNT_reg_n_0_[4]\,
      I5 => curstate(0),
      O => \S_BIT_COUNT[0]_i_2_n_0\
    );
\S_BIT_COUNT[1]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"82"
    )
        port map (
      I0 => nxtstate(1),
      I1 => \S_BIT_COUNT_reg_n_0_[1]\,
      I2 => \S_BIT_COUNT_reg_n_0_[0]\,
      O => S_BIT_COUNT(1)
    );
\S_BIT_COUNT[2]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"8882"
    )
        port map (
      I0 => nxtstate(1),
      I1 => \S_BIT_COUNT_reg_n_0_[2]\,
      I2 => \S_BIT_COUNT_reg_n_0_[0]\,
      I3 => \S_BIT_COUNT_reg_n_0_[1]\,
      O => S_BIT_COUNT(2)
    );
\S_BIT_COUNT[3]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"88888882"
    )
        port map (
      I0 => nxtstate(1),
      I1 => \S_BIT_COUNT_reg_n_0_[3]\,
      I2 => \S_BIT_COUNT_reg_n_0_[2]\,
      I3 => \S_BIT_COUNT_reg_n_0_[1]\,
      I4 => \S_BIT_COUNT_reg_n_0_[0]\,
      O => S_BIT_COUNT(3)
    );
\S_BIT_COUNT[4]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"F0F0FEF2"
    )
        port map (
      I0 => SS_OUT_N_i_2_n_0,
      I1 => curstate(1),
      I2 => \S_BIT_COUNT[4]_i_2_n_0\,
      I3 => \S_DEL_CLK[16]_i_3_n_0\,
      I4 => \S_BIT_COUNT[4]_i_3_n_0\,
      O => S_BIT_COUNT(4)
    );
\S_BIT_COUNT[4]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"E0F3E2E3E0E0E2E2"
    )
        port map (
      I0 => SS_OUT_N_i_2_n_0,
      I1 => curstate(1),
      I2 => curstate(2),
      I3 => S_DEL_COUNT(8),
      I4 => curstate(0),
      I5 => \curstate[2]_i_2_n_0\,
      O => \S_BIT_COUNT[4]_i_2_n_0\
    );
\S_BIT_COUNT[4]_i_3\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"0001FFFE"
    )
        port map (
      I0 => \S_BIT_COUNT_reg_n_0_[0]\,
      I1 => \S_BIT_COUNT_reg_n_0_[2]\,
      I2 => \S_BIT_COUNT_reg_n_0_[1]\,
      I3 => \S_BIT_COUNT_reg_n_0_[3]\,
      I4 => \S_BIT_COUNT_reg_n_0_[4]\,
      O => \S_BIT_COUNT[4]_i_3_n_0\
    );
\S_BIT_COUNT[5]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AABBAABAAAABAAAA"
    )
        port map (
      I0 => \S_BIT_COUNT[5]_i_3_n_0\,
      I1 => curstate(0),
      I2 => curstate(1),
      I3 => curstate(2),
      I4 => \S_BIT_COUNT_reg[0]_0\,
      I5 => nxtstate1,
      O => \S_BIT_COUNT[5]_i_1_n_0\
    );
\S_BIT_COUNT[5]_i_10\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => S_DEL_CLK(11),
      I1 => S_DEL_CLK(10),
      O => \S_BIT_COUNT[5]_i_10_n_0\
    );
\S_BIT_COUNT[5]_i_11\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => S_DEL_CLK(9),
      I1 => S_DEL_CLK(8),
      O => \S_BIT_COUNT[5]_i_11_n_0\
    );
\S_BIT_COUNT[5]_i_12\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => S_DEL_CLK(7),
      I1 => S_DEL_CLK(6),
      O => \S_BIT_COUNT[5]_i_12_n_0\
    );
\S_BIT_COUNT[5]_i_13\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => S_DEL_CLK(5),
      I1 => S_DEL_CLK(4),
      O => \S_BIT_COUNT[5]_i_13_n_0\
    );
\S_BIT_COUNT[5]_i_14\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => S_DEL_CLK(3),
      I1 => S_DEL_CLK(2),
      O => \S_BIT_COUNT[5]_i_14_n_0\
    );
\S_BIT_COUNT[5]_i_15\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => S_DEL_CLK(0),
      I1 => S_DEL_CLK(1),
      O => \S_BIT_COUNT[5]_i_15_n_0\
    );
\S_BIT_COUNT[5]_i_2\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"82"
    )
        port map (
      I0 => nxtstate(1),
      I1 => \S_BIT_COUNT_reg_n_0_[5]\,
      I2 => \S_BIT_COUNT[5]_i_5_n_0\,
      O => S_BIT_COUNT(5)
    );
\S_BIT_COUNT[5]_i_3\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"00000200"
    )
        port map (
      I0 => SS_OUT_N_i_2_n_0,
      I1 => curstate(2),
      I2 => curstate(1),
      I3 => curstate(0),
      I4 => S_CPHA_reg_n_0,
      O => \S_BIT_COUNT[5]_i_3_n_0\
    );
\S_BIT_COUNT[5]_i_5\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFFFFFFE"
    )
        port map (
      I0 => \S_BIT_COUNT_reg_n_0_[4]\,
      I1 => \S_BIT_COUNT_reg_n_0_[2]\,
      I2 => \S_BIT_COUNT_reg_n_0_[1]\,
      I3 => \S_BIT_COUNT_reg_n_0_[3]\,
      I4 => \S_BIT_COUNT_reg_n_0_[0]\,
      O => \S_BIT_COUNT[5]_i_5_n_0\
    );
\S_BIT_COUNT[5]_i_7\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => S_DEL_CLK(16),
      O => \S_BIT_COUNT[5]_i_7_n_0\
    );
\S_BIT_COUNT[5]_i_8\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => S_DEL_CLK(15),
      I1 => S_DEL_CLK(14),
      O => \S_BIT_COUNT[5]_i_8_n_0\
    );
\S_BIT_COUNT[5]_i_9\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => S_DEL_CLK(13),
      I1 => S_DEL_CLK(12),
      O => \S_BIT_COUNT[5]_i_9_n_0\
    );
\S_BIT_COUNT_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_BIT_COUNT[5]_i_1_n_0\,
      D => S_BIT_COUNT(0),
      Q => \S_BIT_COUNT_reg_n_0_[0]\,
      R => RSTP
    );
\S_BIT_COUNT_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_BIT_COUNT[5]_i_1_n_0\,
      D => S_BIT_COUNT(1),
      Q => \S_BIT_COUNT_reg_n_0_[1]\,
      R => RSTP
    );
\S_BIT_COUNT_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_BIT_COUNT[5]_i_1_n_0\,
      D => S_BIT_COUNT(2),
      Q => \S_BIT_COUNT_reg_n_0_[2]\,
      R => RSTP
    );
\S_BIT_COUNT_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_BIT_COUNT[5]_i_1_n_0\,
      D => S_BIT_COUNT(3),
      Q => \S_BIT_COUNT_reg_n_0_[3]\,
      R => RSTP
    );
\S_BIT_COUNT_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_BIT_COUNT[5]_i_1_n_0\,
      D => S_BIT_COUNT(4),
      Q => \S_BIT_COUNT_reg_n_0_[4]\,
      R => RSTP
    );
\S_BIT_COUNT_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_BIT_COUNT[5]_i_1_n_0\,
      D => S_BIT_COUNT(5),
      Q => \S_BIT_COUNT_reg_n_0_[5]\,
      R => RSTP
    );
\S_BIT_COUNT_reg[5]_i_4\: unisim.vcomponents.CARRY8
     port map (
      CI => \S_BIT_COUNT_reg[5]_i_6_n_0\,
      CI_TOP => '0',
      CO(7 downto 1) => \NLW_S_BIT_COUNT_reg[5]_i_4_CO_UNCONNECTED\(7 downto 1),
      CO(0) => nxtstate1,
      DI(7 downto 1) => B"0000000",
      DI(0) => S_DEL_CLK(16),
      O(7 downto 0) => \NLW_S_BIT_COUNT_reg[5]_i_4_O_UNCONNECTED\(7 downto 0),
      S(7 downto 1) => B"0000000",
      S(0) => \S_BIT_COUNT[5]_i_7_n_0\
    );
\S_BIT_COUNT_reg[5]_i_6\: unisim.vcomponents.CARRY8
     port map (
      CI => '1',
      CI_TOP => '0',
      CO(7) => \S_BIT_COUNT_reg[5]_i_6_n_0\,
      CO(6) => \S_BIT_COUNT_reg[5]_i_6_n_1\,
      CO(5) => \S_BIT_COUNT_reg[5]_i_6_n_2\,
      CO(4) => \S_BIT_COUNT_reg[5]_i_6_n_3\,
      CO(3) => \S_BIT_COUNT_reg[5]_i_6_n_4\,
      CO(2) => \S_BIT_COUNT_reg[5]_i_6_n_5\,
      CO(1) => \S_BIT_COUNT_reg[5]_i_6_n_6\,
      CO(0) => \S_BIT_COUNT_reg[5]_i_6_n_7\,
      DI(7 downto 0) => B"00000000",
      O(7 downto 0) => \NLW_S_BIT_COUNT_reg[5]_i_6_O_UNCONNECTED\(7 downto 0),
      S(7) => \S_BIT_COUNT[5]_i_8_n_0\,
      S(6) => \S_BIT_COUNT[5]_i_9_n_0\,
      S(5) => \S_BIT_COUNT[5]_i_10_n_0\,
      S(4) => \S_BIT_COUNT[5]_i_11_n_0\,
      S(3) => \S_BIT_COUNT[5]_i_12_n_0\,
      S(2) => \S_BIT_COUNT[5]_i_13_n_0\,
      S(1) => \S_BIT_COUNT[5]_i_14_n_0\,
      S(0) => \S_BIT_COUNT[5]_i_15_n_0\
    );
\S_CLK_DIV[15]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FE00FE03"
    )
        port map (
      I0 => SS_OUT_N_i_2_n_0,
      I1 => curstate(1),
      I2 => curstate(0),
      I3 => curstate(2),
      I4 => \S_BIT_COUNT_reg[0]_0\,
      O => S_CPHA
    );
\S_CLK_DIV_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_CPHA,
      D => \S_DEL_COUNT_reg[7]_0\(0),
      Q => S_CLK_DIV(0),
      R => RSTP
    );
\S_CLK_DIV_reg[10]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_CPHA,
      D => \S_DEL_COUNT_reg[7]_0\(10),
      Q => S_CLK_DIV(10),
      R => RSTP
    );
\S_CLK_DIV_reg[11]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_CPHA,
      D => \S_DEL_COUNT_reg[7]_0\(11),
      Q => S_CLK_DIV(11),
      R => RSTP
    );
\S_CLK_DIV_reg[12]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_CPHA,
      D => \S_DEL_COUNT_reg[7]_0\(12),
      Q => S_CLK_DIV(12),
      R => RSTP
    );
\S_CLK_DIV_reg[13]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_CPHA,
      D => \S_DEL_COUNT_reg[7]_0\(13),
      Q => S_CLK_DIV(13),
      R => RSTP
    );
\S_CLK_DIV_reg[14]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_CPHA,
      D => \S_DEL_COUNT_reg[7]_0\(14),
      Q => S_CLK_DIV(14),
      R => RSTP
    );
\S_CLK_DIV_reg[15]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_CPHA,
      D => \S_DEL_COUNT_reg[7]_0\(15),
      Q => S_CLK_DIV(15),
      R => RSTP
    );
\S_CLK_DIV_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_CPHA,
      D => \S_DEL_COUNT_reg[7]_0\(1),
      Q => S_CLK_DIV(1),
      R => RSTP
    );
\S_CLK_DIV_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_CPHA,
      D => \S_DEL_COUNT_reg[7]_0\(2),
      Q => S_CLK_DIV(2),
      R => RSTP
    );
\S_CLK_DIV_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_CPHA,
      D => \S_DEL_COUNT_reg[7]_0\(3),
      Q => S_CLK_DIV(3),
      R => RSTP
    );
\S_CLK_DIV_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_CPHA,
      D => \S_DEL_COUNT_reg[7]_0\(4),
      Q => S_CLK_DIV(4),
      R => RSTP
    );
\S_CLK_DIV_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_CPHA,
      D => \S_DEL_COUNT_reg[7]_0\(5),
      Q => S_CLK_DIV(5),
      R => RSTP
    );
\S_CLK_DIV_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_CPHA,
      D => \S_DEL_COUNT_reg[7]_0\(6),
      Q => S_CLK_DIV(6),
      R => RSTP
    );
\S_CLK_DIV_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_CPHA,
      D => \S_DEL_COUNT_reg[7]_0\(7),
      Q => S_CLK_DIV(7),
      R => RSTP
    );
\S_CLK_DIV_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_CPHA,
      D => \S_DEL_COUNT_reg[7]_0\(8),
      Q => S_CLK_DIV(8),
      R => RSTP
    );
\S_CLK_DIV_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_CPHA,
      D => \S_DEL_COUNT_reg[7]_0\(9),
      Q => S_CLK_DIV(9),
      R => RSTP
    );
S_CPHA_i_1: unisim.vcomponents.LUT3
    generic map(
      INIT => X"20"
    )
        port map (
      I0 => S_CPHA,
      I1 => S_CPOL_reg_0(0),
      I2 => s00_axi_aresetn,
      O => S_CPOL
    );
S_CPHA_reg: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_CPOL,
      D => CPHA,
      Q => S_CPHA_reg_n_0,
      R => '0'
    );
S_CPOL_reg: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_CPOL,
      D => CPOL,
      Q => S_CPOL_reg_n_0,
      R => '0'
    );
\S_DEL_CLK[0]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFF88F888F888F8"
    )
        port map (
      I0 => \S_DEL_CLK[15]_i_2_n_0\,
      I1 => S_CLK_DIV(0),
      I2 => \S_DEL_CLK[16]_i_4_n_0\,
      I3 => S_DEL_CLK(0),
      I4 => \S_DEL_COUNT_reg[7]_0\(0),
      I5 => \S_DEL_CLK[15]_i_3_n_0\,
      O => S_DEL_CLK1_in(0)
    );
\S_DEL_CLK[10]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFFF888F888F888"
    )
        port map (
      I0 => \S_DEL_CLK[15]_i_2_n_0\,
      I1 => S_CLK_DIV(10),
      I2 => \S_DEL_CLK[16]_i_4_n_0\,
      I3 => S_DEL_CLK0(10),
      I4 => \S_DEL_COUNT_reg[7]_0\(10),
      I5 => \S_DEL_CLK[15]_i_3_n_0\,
      O => S_DEL_CLK1_in(10)
    );
\S_DEL_CLK[11]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFFF888F888F888"
    )
        port map (
      I0 => \S_DEL_CLK[15]_i_2_n_0\,
      I1 => S_CLK_DIV(11),
      I2 => \S_DEL_CLK[16]_i_4_n_0\,
      I3 => S_DEL_CLK0(11),
      I4 => \S_DEL_COUNT_reg[7]_0\(11),
      I5 => \S_DEL_CLK[15]_i_3_n_0\,
      O => S_DEL_CLK1_in(11)
    );
\S_DEL_CLK[12]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFFF888F888F888"
    )
        port map (
      I0 => \S_DEL_CLK[15]_i_2_n_0\,
      I1 => S_CLK_DIV(12),
      I2 => \S_DEL_CLK[16]_i_4_n_0\,
      I3 => S_DEL_CLK0(12),
      I4 => \S_DEL_COUNT_reg[7]_0\(12),
      I5 => \S_DEL_CLK[15]_i_3_n_0\,
      O => S_DEL_CLK1_in(12)
    );
\S_DEL_CLK[13]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFFF888F888F888"
    )
        port map (
      I0 => \S_DEL_CLK[15]_i_2_n_0\,
      I1 => S_CLK_DIV(13),
      I2 => \S_DEL_CLK[16]_i_4_n_0\,
      I3 => S_DEL_CLK0(13),
      I4 => \S_DEL_COUNT_reg[7]_0\(13),
      I5 => \S_DEL_CLK[15]_i_3_n_0\,
      O => S_DEL_CLK1_in(13)
    );
\S_DEL_CLK[14]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFFF888F888F888"
    )
        port map (
      I0 => \S_DEL_CLK[15]_i_2_n_0\,
      I1 => S_CLK_DIV(14),
      I2 => \S_DEL_CLK[16]_i_4_n_0\,
      I3 => S_DEL_CLK0(14),
      I4 => \S_DEL_COUNT_reg[7]_0\(14),
      I5 => \S_DEL_CLK[15]_i_3_n_0\,
      O => S_DEL_CLK1_in(14)
    );
\S_DEL_CLK[15]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFFF888F888F888"
    )
        port map (
      I0 => \S_DEL_CLK[15]_i_2_n_0\,
      I1 => S_CLK_DIV(15),
      I2 => \S_DEL_CLK[16]_i_4_n_0\,
      I3 => S_DEL_CLK0(15),
      I4 => \S_DEL_COUNT_reg[7]_0\(15),
      I5 => \S_DEL_CLK[15]_i_3_n_0\,
      O => S_DEL_CLK1_in(15)
    );
\S_DEL_CLK[15]_i_2\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"02000000"
    )
        port map (
      I0 => SS_OUT_N_i_2_n_0,
      I1 => curstate(2),
      I2 => curstate(1),
      I3 => curstate(0),
      I4 => S_CPHA_reg_n_0,
      O => \S_DEL_CLK[15]_i_2_n_0\
    );
\S_DEL_CLK[15]_i_3\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"EEEEFEEEEEEEEEEE"
    )
        port map (
      I0 => \curstate[0]_i_3_n_0\,
      I1 => \S_DEL_CLK[15]_i_4_n_0\,
      I2 => curstate(1),
      I3 => nxtstate1,
      I4 => curstate(2),
      I5 => \S_DEL_CLK[16]_i_3_n_0\,
      O => \S_DEL_CLK[15]_i_3_n_0\
    );
\S_DEL_CLK[15]_i_4\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"0002"
    )
        port map (
      I0 => curstate(0),
      I1 => curstate(1),
      I2 => curstate(2),
      I3 => S_CPHA_reg_n_0,
      O => \S_DEL_CLK[15]_i_4_n_0\
    );
\S_DEL_CLK[16]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"0A0C0A00"
    )
        port map (
      I0 => \S_DEL_CLK[16]_i_3_n_0\,
      I1 => SS_OUT_N_i_2_n_0,
      I2 => curstate(2),
      I3 => curstate(1),
      I4 => curstate(0),
      O => nxtstate(1)
    );
\S_DEL_CLK[16]_i_10\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => S_DEL_CLK(12),
      O => \S_DEL_CLK[16]_i_10_n_0\
    );
\S_DEL_CLK[16]_i_11\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => S_DEL_CLK(11),
      O => \S_DEL_CLK[16]_i_11_n_0\
    );
\S_DEL_CLK[16]_i_12\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => S_DEL_CLK(10),
      O => \S_DEL_CLK[16]_i_12_n_0\
    );
\S_DEL_CLK[16]_i_13\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => S_DEL_CLK(9),
      O => \S_DEL_CLK[16]_i_13_n_0\
    );
\S_DEL_CLK[16]_i_2\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"8"
    )
        port map (
      I0 => \S_DEL_CLK[16]_i_4_n_0\,
      I1 => S_DEL_CLK0(16),
      O => S_DEL_CLK1_in(16)
    );
\S_DEL_CLK[16]_i_3\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"7"
    )
        port map (
      I0 => \S_RX_OUT_BUFFER[127]_i_3_n_0\,
      I1 => curstate(0),
      O => \S_DEL_CLK[16]_i_3_n_0\
    );
\S_DEL_CLK[16]_i_4\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FE03FECFFE03FE03"
    )
        port map (
      I0 => SS_OUT_N_i_2_n_0,
      I1 => curstate(1),
      I2 => curstate(0),
      I3 => curstate(2),
      I4 => nxtstate1,
      I5 => \S_DEL_CLK[16]_i_3_n_0\,
      O => \S_DEL_CLK[16]_i_4_n_0\
    );
\S_DEL_CLK[16]_i_6\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => S_DEL_CLK(16),
      O => \S_DEL_CLK[16]_i_6_n_0\
    );
\S_DEL_CLK[16]_i_7\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => S_DEL_CLK(15),
      O => \S_DEL_CLK[16]_i_7_n_0\
    );
\S_DEL_CLK[16]_i_8\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => S_DEL_CLK(14),
      O => \S_DEL_CLK[16]_i_8_n_0\
    );
\S_DEL_CLK[16]_i_9\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => S_DEL_CLK(13),
      O => \S_DEL_CLK[16]_i_9_n_0\
    );
\S_DEL_CLK[1]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFFF888F888F888"
    )
        port map (
      I0 => \S_DEL_CLK[15]_i_2_n_0\,
      I1 => S_CLK_DIV(1),
      I2 => \S_DEL_CLK[16]_i_4_n_0\,
      I3 => S_DEL_CLK0(1),
      I4 => \S_DEL_COUNT_reg[7]_0\(1),
      I5 => \S_DEL_CLK[15]_i_3_n_0\,
      O => S_DEL_CLK1_in(1)
    );
\S_DEL_CLK[2]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFFF888F888F888"
    )
        port map (
      I0 => \S_DEL_CLK[15]_i_2_n_0\,
      I1 => S_CLK_DIV(2),
      I2 => \S_DEL_CLK[16]_i_4_n_0\,
      I3 => S_DEL_CLK0(2),
      I4 => \S_DEL_COUNT_reg[7]_0\(2),
      I5 => \S_DEL_CLK[15]_i_3_n_0\,
      O => S_DEL_CLK1_in(2)
    );
\S_DEL_CLK[3]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFFF888F888F888"
    )
        port map (
      I0 => \S_DEL_CLK[15]_i_2_n_0\,
      I1 => S_CLK_DIV(3),
      I2 => \S_DEL_CLK[16]_i_4_n_0\,
      I3 => S_DEL_CLK0(3),
      I4 => \S_DEL_COUNT_reg[7]_0\(3),
      I5 => \S_DEL_CLK[15]_i_3_n_0\,
      O => S_DEL_CLK1_in(3)
    );
\S_DEL_CLK[4]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFFF888F888F888"
    )
        port map (
      I0 => \S_DEL_CLK[15]_i_2_n_0\,
      I1 => S_CLK_DIV(4),
      I2 => \S_DEL_CLK[16]_i_4_n_0\,
      I3 => S_DEL_CLK0(4),
      I4 => \S_DEL_COUNT_reg[7]_0\(4),
      I5 => \S_DEL_CLK[15]_i_3_n_0\,
      O => S_DEL_CLK1_in(4)
    );
\S_DEL_CLK[5]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFFF888F888F888"
    )
        port map (
      I0 => \S_DEL_CLK[15]_i_2_n_0\,
      I1 => S_CLK_DIV(5),
      I2 => \S_DEL_CLK[16]_i_4_n_0\,
      I3 => S_DEL_CLK0(5),
      I4 => \S_DEL_COUNT_reg[7]_0\(5),
      I5 => \S_DEL_CLK[15]_i_3_n_0\,
      O => S_DEL_CLK1_in(5)
    );
\S_DEL_CLK[6]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFFF888F888F888"
    )
        port map (
      I0 => \S_DEL_CLK[15]_i_2_n_0\,
      I1 => S_CLK_DIV(6),
      I2 => \S_DEL_CLK[16]_i_4_n_0\,
      I3 => S_DEL_CLK0(6),
      I4 => \S_DEL_COUNT_reg[7]_0\(6),
      I5 => \S_DEL_CLK[15]_i_3_n_0\,
      O => S_DEL_CLK1_in(6)
    );
\S_DEL_CLK[7]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFFF888F888F888"
    )
        port map (
      I0 => \S_DEL_CLK[15]_i_2_n_0\,
      I1 => S_CLK_DIV(7),
      I2 => \S_DEL_CLK[16]_i_4_n_0\,
      I3 => S_DEL_CLK0(7),
      I4 => \S_DEL_COUNT_reg[7]_0\(7),
      I5 => \S_DEL_CLK[15]_i_3_n_0\,
      O => S_DEL_CLK1_in(7)
    );
\S_DEL_CLK[8]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFFF888F888F888"
    )
        port map (
      I0 => \S_DEL_CLK[15]_i_2_n_0\,
      I1 => S_CLK_DIV(8),
      I2 => \S_DEL_CLK[16]_i_4_n_0\,
      I3 => S_DEL_CLK0(8),
      I4 => \S_DEL_COUNT_reg[7]_0\(8),
      I5 => \S_DEL_CLK[15]_i_3_n_0\,
      O => S_DEL_CLK1_in(8)
    );
\S_DEL_CLK[8]_i_10\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => S_DEL_CLK(1),
      O => \S_DEL_CLK[8]_i_10_n_0\
    );
\S_DEL_CLK[8]_i_3\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => S_DEL_CLK(8),
      O => \S_DEL_CLK[8]_i_3_n_0\
    );
\S_DEL_CLK[8]_i_4\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => S_DEL_CLK(7),
      O => \S_DEL_CLK[8]_i_4_n_0\
    );
\S_DEL_CLK[8]_i_5\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => S_DEL_CLK(6),
      O => \S_DEL_CLK[8]_i_5_n_0\
    );
\S_DEL_CLK[8]_i_6\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => S_DEL_CLK(5),
      O => \S_DEL_CLK[8]_i_6_n_0\
    );
\S_DEL_CLK[8]_i_7\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => S_DEL_CLK(4),
      O => \S_DEL_CLK[8]_i_7_n_0\
    );
\S_DEL_CLK[8]_i_8\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => S_DEL_CLK(3),
      O => \S_DEL_CLK[8]_i_8_n_0\
    );
\S_DEL_CLK[8]_i_9\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => S_DEL_CLK(2),
      O => \S_DEL_CLK[8]_i_9_n_0\
    );
\S_DEL_CLK[9]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFFF888F888F888"
    )
        port map (
      I0 => \S_DEL_CLK[15]_i_2_n_0\,
      I1 => S_CLK_DIV(9),
      I2 => \S_DEL_CLK[16]_i_4_n_0\,
      I3 => S_DEL_CLK0(9),
      I4 => \S_DEL_COUNT_reg[7]_0\(9),
      I5 => \S_DEL_CLK[15]_i_3_n_0\,
      O => S_DEL_CLK1_in(9)
    );
\S_DEL_CLK_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => nxtstate(1),
      D => S_DEL_CLK1_in(0),
      Q => S_DEL_CLK(0),
      R => RSTP
    );
\S_DEL_CLK_reg[10]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => nxtstate(1),
      D => S_DEL_CLK1_in(10),
      Q => S_DEL_CLK(10),
      R => RSTP
    );
\S_DEL_CLK_reg[11]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => nxtstate(1),
      D => S_DEL_CLK1_in(11),
      Q => S_DEL_CLK(11),
      R => RSTP
    );
\S_DEL_CLK_reg[12]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => nxtstate(1),
      D => S_DEL_CLK1_in(12),
      Q => S_DEL_CLK(12),
      R => RSTP
    );
\S_DEL_CLK_reg[13]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => nxtstate(1),
      D => S_DEL_CLK1_in(13),
      Q => S_DEL_CLK(13),
      R => RSTP
    );
\S_DEL_CLK_reg[14]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => nxtstate(1),
      D => S_DEL_CLK1_in(14),
      Q => S_DEL_CLK(14),
      R => RSTP
    );
\S_DEL_CLK_reg[15]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => nxtstate(1),
      D => S_DEL_CLK1_in(15),
      Q => S_DEL_CLK(15),
      R => RSTP
    );
\S_DEL_CLK_reg[16]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => nxtstate(1),
      D => S_DEL_CLK1_in(16),
      Q => S_DEL_CLK(16),
      R => RSTP
    );
\S_DEL_CLK_reg[16]_i_5\: unisim.vcomponents.CARRY8
     port map (
      CI => \S_DEL_CLK_reg[8]_i_2_n_0\,
      CI_TOP => '0',
      CO(7) => \NLW_S_DEL_CLK_reg[16]_i_5_CO_UNCONNECTED\(7),
      CO(6) => \S_DEL_CLK_reg[16]_i_5_n_1\,
      CO(5) => \S_DEL_CLK_reg[16]_i_5_n_2\,
      CO(4) => \S_DEL_CLK_reg[16]_i_5_n_3\,
      CO(3) => \S_DEL_CLK_reg[16]_i_5_n_4\,
      CO(2) => \S_DEL_CLK_reg[16]_i_5_n_5\,
      CO(1) => \S_DEL_CLK_reg[16]_i_5_n_6\,
      CO(0) => \S_DEL_CLK_reg[16]_i_5_n_7\,
      DI(7) => '0',
      DI(6 downto 0) => S_DEL_CLK(15 downto 9),
      O(7 downto 0) => S_DEL_CLK0(16 downto 9),
      S(7) => \S_DEL_CLK[16]_i_6_n_0\,
      S(6) => \S_DEL_CLK[16]_i_7_n_0\,
      S(5) => \S_DEL_CLK[16]_i_8_n_0\,
      S(4) => \S_DEL_CLK[16]_i_9_n_0\,
      S(3) => \S_DEL_CLK[16]_i_10_n_0\,
      S(2) => \S_DEL_CLK[16]_i_11_n_0\,
      S(1) => \S_DEL_CLK[16]_i_12_n_0\,
      S(0) => \S_DEL_CLK[16]_i_13_n_0\
    );
\S_DEL_CLK_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => nxtstate(1),
      D => S_DEL_CLK1_in(1),
      Q => S_DEL_CLK(1),
      R => RSTP
    );
\S_DEL_CLK_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => nxtstate(1),
      D => S_DEL_CLK1_in(2),
      Q => S_DEL_CLK(2),
      R => RSTP
    );
\S_DEL_CLK_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => nxtstate(1),
      D => S_DEL_CLK1_in(3),
      Q => S_DEL_CLK(3),
      R => RSTP
    );
\S_DEL_CLK_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => nxtstate(1),
      D => S_DEL_CLK1_in(4),
      Q => S_DEL_CLK(4),
      R => RSTP
    );
\S_DEL_CLK_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => nxtstate(1),
      D => S_DEL_CLK1_in(5),
      Q => S_DEL_CLK(5),
      R => RSTP
    );
\S_DEL_CLK_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => nxtstate(1),
      D => S_DEL_CLK1_in(6),
      Q => S_DEL_CLK(6),
      R => RSTP
    );
\S_DEL_CLK_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => nxtstate(1),
      D => S_DEL_CLK1_in(7),
      Q => S_DEL_CLK(7),
      R => RSTP
    );
\S_DEL_CLK_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => nxtstate(1),
      D => S_DEL_CLK1_in(8),
      Q => S_DEL_CLK(8),
      R => RSTP
    );
\S_DEL_CLK_reg[8]_i_2\: unisim.vcomponents.CARRY8
     port map (
      CI => S_DEL_CLK(0),
      CI_TOP => '0',
      CO(7) => \S_DEL_CLK_reg[8]_i_2_n_0\,
      CO(6) => \S_DEL_CLK_reg[8]_i_2_n_1\,
      CO(5) => \S_DEL_CLK_reg[8]_i_2_n_2\,
      CO(4) => \S_DEL_CLK_reg[8]_i_2_n_3\,
      CO(3) => \S_DEL_CLK_reg[8]_i_2_n_4\,
      CO(2) => \S_DEL_CLK_reg[8]_i_2_n_5\,
      CO(1) => \S_DEL_CLK_reg[8]_i_2_n_6\,
      CO(0) => \S_DEL_CLK_reg[8]_i_2_n_7\,
      DI(7 downto 0) => S_DEL_CLK(8 downto 1),
      O(7 downto 0) => S_DEL_CLK0(8 downto 1),
      S(7) => \S_DEL_CLK[8]_i_3_n_0\,
      S(6) => \S_DEL_CLK[8]_i_4_n_0\,
      S(5) => \S_DEL_CLK[8]_i_5_n_0\,
      S(4) => \S_DEL_CLK[8]_i_6_n_0\,
      S(3) => \S_DEL_CLK[8]_i_7_n_0\,
      S(2) => \S_DEL_CLK[8]_i_8_n_0\,
      S(1) => \S_DEL_CLK[8]_i_9_n_0\,
      S(0) => \S_DEL_CLK[8]_i_10_n_0\
    );
\S_DEL_CLK_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => nxtstate(1),
      D => S_DEL_CLK1_in(9),
      Q => S_DEL_CLK(9),
      R => RSTP
    );
\S_DEL_COUNT[0]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"F888FFFFF888F888"
    )
        port map (
      I0 => \S_DEL_COUNT[6]_i_2_n_0\,
      I1 => S_PRE_DELAY(0),
      I2 => S_RX_OUT_BUFFER,
      I3 => \S_DEL_COUNT_reg[7]_0\(24),
      I4 => S_DEL_COUNT(0),
      I5 => \S_DEL_COUNT[8]_i_4_n_0\,
      O => S_DEL_COUNT1_in(0)
    );
\S_DEL_COUNT[1]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"EBAA"
    )
        port map (
      I0 => \S_DEL_COUNT[1]_i_2_n_0\,
      I1 => S_DEL_COUNT(0),
      I2 => S_DEL_COUNT(1),
      I3 => \S_DEL_COUNT[8]_i_4_n_0\,
      O => S_DEL_COUNT1_in(1)
    );
\S_DEL_COUNT[1]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"88888888888888F8"
    )
        port map (
      I0 => \S_DEL_COUNT_reg[7]_0\(25),
      I1 => S_RX_OUT_BUFFER,
      I2 => S_PRE_DELAY(1),
      I3 => curstate(2),
      I4 => curstate(1),
      I5 => curstate(0),
      O => \S_DEL_COUNT[1]_i_2_n_0\
    );
\S_DEL_COUNT[2]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FEABAAAA"
    )
        port map (
      I0 => \S_DEL_COUNT[2]_i_2_n_0\,
      I1 => S_DEL_COUNT(1),
      I2 => S_DEL_COUNT(0),
      I3 => S_DEL_COUNT(2),
      I4 => \S_DEL_COUNT[8]_i_4_n_0\,
      O => S_DEL_COUNT1_in(2)
    );
\S_DEL_COUNT[2]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"88888888888888F8"
    )
        port map (
      I0 => \S_DEL_COUNT_reg[7]_0\(26),
      I1 => S_RX_OUT_BUFFER,
      I2 => S_PRE_DELAY(2),
      I3 => curstate(2),
      I4 => curstate(1),
      I5 => curstate(0),
      O => \S_DEL_COUNT[2]_i_2_n_0\
    );
\S_DEL_COUNT[3]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFEAAABAAAAAAAA"
    )
        port map (
      I0 => \S_DEL_COUNT[3]_i_2_n_0\,
      I1 => S_DEL_COUNT(0),
      I2 => S_DEL_COUNT(1),
      I3 => S_DEL_COUNT(2),
      I4 => S_DEL_COUNT(3),
      I5 => \S_DEL_COUNT[8]_i_4_n_0\,
      O => S_DEL_COUNT1_in(3)
    );
\S_DEL_COUNT[3]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"88888888888888F8"
    )
        port map (
      I0 => \S_DEL_COUNT_reg[7]_0\(27),
      I1 => S_RX_OUT_BUFFER,
      I2 => S_PRE_DELAY(3),
      I3 => curstate(2),
      I4 => curstate(1),
      I5 => curstate(0),
      O => \S_DEL_COUNT[3]_i_2_n_0\
    );
\S_DEL_COUNT[4]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"F888FFFFF888F888"
    )
        port map (
      I0 => \S_DEL_COUNT[6]_i_2_n_0\,
      I1 => S_PRE_DELAY(4),
      I2 => S_RX_OUT_BUFFER,
      I3 => \S_DEL_COUNT_reg[7]_0\(28),
      I4 => \S_DEL_COUNT[4]_i_2_n_0\,
      I5 => \S_DEL_COUNT[8]_i_4_n_0\,
      O => S_DEL_COUNT1_in(4)
    );
\S_DEL_COUNT[4]_i_2\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"0001FFFE"
    )
        port map (
      I0 => S_DEL_COUNT(3),
      I1 => S_DEL_COUNT(2),
      I2 => S_DEL_COUNT(1),
      I3 => S_DEL_COUNT(0),
      I4 => S_DEL_COUNT(4),
      O => \S_DEL_COUNT[4]_i_2_n_0\
    );
\S_DEL_COUNT[5]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"F888FFFFF888F888"
    )
        port map (
      I0 => \S_DEL_COUNT[6]_i_2_n_0\,
      I1 => S_PRE_DELAY(5),
      I2 => S_RX_OUT_BUFFER,
      I3 => \S_DEL_COUNT_reg[7]_0\(29),
      I4 => \S_DEL_COUNT[5]_i_2_n_0\,
      I5 => \S_DEL_COUNT[8]_i_4_n_0\,
      O => S_DEL_COUNT1_in(5)
    );
\S_DEL_COUNT[5]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"00000001FFFFFFFE"
    )
        port map (
      I0 => S_DEL_COUNT(4),
      I1 => S_DEL_COUNT(0),
      I2 => S_DEL_COUNT(1),
      I3 => S_DEL_COUNT(2),
      I4 => S_DEL_COUNT(3),
      I5 => S_DEL_COUNT(5),
      O => \S_DEL_COUNT[5]_i_2_n_0\
    );
\S_DEL_COUNT[6]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"F888FFFFF888F888"
    )
        port map (
      I0 => \S_DEL_COUNT[6]_i_2_n_0\,
      I1 => S_PRE_DELAY(6),
      I2 => S_RX_OUT_BUFFER,
      I3 => \S_DEL_COUNT_reg[7]_0\(30),
      I4 => \S_DEL_COUNT[6]_i_3_n_0\,
      I5 => \S_DEL_COUNT[8]_i_4_n_0\,
      O => S_DEL_COUNT1_in(6)
    );
\S_DEL_COUNT[6]_i_2\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"01"
    )
        port map (
      I0 => curstate(2),
      I1 => curstate(1),
      I2 => curstate(0),
      O => \S_DEL_COUNT[6]_i_2_n_0\
    );
\S_DEL_COUNT[6]_i_3\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"00000100FFFFFEFF"
    )
        port map (
      I0 => S_DEL_COUNT(5),
      I1 => S_DEL_COUNT(3),
      I2 => S_DEL_COUNT(2),
      I3 => \S_DEL_COUNT[6]_i_4_n_0\,
      I4 => S_DEL_COUNT(4),
      I5 => S_DEL_COUNT(6),
      O => \S_DEL_COUNT[6]_i_3_n_0\
    );
\S_DEL_COUNT[6]_i_4\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => S_DEL_COUNT(0),
      I1 => S_DEL_COUNT(1),
      O => \S_DEL_COUNT[6]_i_4_n_0\
    );
\S_DEL_COUNT[7]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FEABAAAA"
    )
        port map (
      I0 => \S_DEL_COUNT[7]_i_2_n_0\,
      I1 => S_DEL_COUNT(6),
      I2 => \S_DEL_COUNT[7]_i_3_n_0\,
      I3 => S_DEL_COUNT(7),
      I4 => \S_DEL_COUNT[8]_i_4_n_0\,
      O => S_DEL_COUNT1_in(7)
    );
\S_DEL_COUNT[7]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"88888888888888F8"
    )
        port map (
      I0 => \S_DEL_COUNT_reg[7]_0\(31),
      I1 => S_RX_OUT_BUFFER,
      I2 => S_PRE_DELAY(7),
      I3 => curstate(2),
      I4 => curstate(1),
      I5 => curstate(0),
      O => \S_DEL_COUNT[7]_i_2_n_0\
    );
\S_DEL_COUNT[7]_i_3\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFFFFFFFFFFFFFE"
    )
        port map (
      I0 => S_DEL_COUNT(4),
      I1 => S_DEL_COUNT(0),
      I2 => S_DEL_COUNT(1),
      I3 => S_DEL_COUNT(2),
      I4 => S_DEL_COUNT(3),
      I5 => S_DEL_COUNT(5),
      O => \S_DEL_COUNT[7]_i_3_n_0\
    );
\S_DEL_COUNT[8]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0000AAAEAAAE0000"
    )
        port map (
      I0 => \S_DEL_COUNT[8]_i_3_n_0\,
      I1 => \curstate[2]_i_2_n_0\,
      I2 => curstate(1),
      I3 => S_DEL_COUNT(8),
      I4 => nxtstate(2),
      I5 => nxtstate(0),
      O => \S_DEL_COUNT[8]_i_1_n_0\
    );
\S_DEL_COUNT[8]_i_2\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"82"
    )
        port map (
      I0 => \S_DEL_COUNT[8]_i_4_n_0\,
      I1 => S_DEL_COUNT(8),
      I2 => \curstate[2]_i_2_n_0\,
      O => S_DEL_COUNT1_in(8)
    );
\S_DEL_COUNT[8]_i_3\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"EAAF"
    )
        port map (
      I0 => curstate(2),
      I1 => \S_RX_OUT_BUFFER[127]_i_3_n_0\,
      I2 => curstate(0),
      I3 => curstate(1),
      O => \S_DEL_COUNT[8]_i_3_n_0\
    );
\S_DEL_COUNT[8]_i_4\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFFBAAFB"
    )
        port map (
      I0 => curstate(2),
      I1 => \S_BIT_COUNT_reg[0]_0\,
      I2 => curstate(0),
      I3 => curstate(1),
      I4 => \S_DEL_CLK[16]_i_3_n_0\,
      O => \S_DEL_COUNT[8]_i_4_n_0\
    );
\S_DEL_COUNT_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_DEL_COUNT[8]_i_1_n_0\,
      D => S_DEL_COUNT1_in(0),
      Q => S_DEL_COUNT(0),
      R => RSTP
    );
\S_DEL_COUNT_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_DEL_COUNT[8]_i_1_n_0\,
      D => S_DEL_COUNT1_in(1),
      Q => S_DEL_COUNT(1),
      R => RSTP
    );
\S_DEL_COUNT_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_DEL_COUNT[8]_i_1_n_0\,
      D => S_DEL_COUNT1_in(2),
      Q => S_DEL_COUNT(2),
      R => RSTP
    );
\S_DEL_COUNT_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_DEL_COUNT[8]_i_1_n_0\,
      D => S_DEL_COUNT1_in(3),
      Q => S_DEL_COUNT(3),
      R => RSTP
    );
\S_DEL_COUNT_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_DEL_COUNT[8]_i_1_n_0\,
      D => S_DEL_COUNT1_in(4),
      Q => S_DEL_COUNT(4),
      R => RSTP
    );
\S_DEL_COUNT_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_DEL_COUNT[8]_i_1_n_0\,
      D => S_DEL_COUNT1_in(5),
      Q => S_DEL_COUNT(5),
      R => RSTP
    );
\S_DEL_COUNT_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_DEL_COUNT[8]_i_1_n_0\,
      D => S_DEL_COUNT1_in(6),
      Q => S_DEL_COUNT(6),
      R => RSTP
    );
\S_DEL_COUNT_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_DEL_COUNT[8]_i_1_n_0\,
      D => S_DEL_COUNT1_in(7),
      Q => S_DEL_COUNT(7),
      R => RSTP
    );
\S_DEL_COUNT_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_DEL_COUNT[8]_i_1_n_0\,
      D => S_DEL_COUNT1_in(8),
      Q => S_DEL_COUNT(8),
      R => RSTP
    );
\S_PRE_DELAY_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_CPHA,
      D => \S_DEL_COUNT_reg[7]_0\(16),
      Q => S_PRE_DELAY(0),
      R => RSTP
    );
\S_PRE_DELAY_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_CPHA,
      D => \S_DEL_COUNT_reg[7]_0\(17),
      Q => S_PRE_DELAY(1),
      R => RSTP
    );
\S_PRE_DELAY_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_CPHA,
      D => \S_DEL_COUNT_reg[7]_0\(18),
      Q => S_PRE_DELAY(2),
      R => RSTP
    );
\S_PRE_DELAY_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_CPHA,
      D => \S_DEL_COUNT_reg[7]_0\(19),
      Q => S_PRE_DELAY(3),
      R => RSTP
    );
\S_PRE_DELAY_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_CPHA,
      D => \S_DEL_COUNT_reg[7]_0\(20),
      Q => S_PRE_DELAY(4),
      R => RSTP
    );
\S_PRE_DELAY_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_CPHA,
      D => \S_DEL_COUNT_reg[7]_0\(21),
      Q => S_PRE_DELAY(5),
      R => RSTP
    );
\S_PRE_DELAY_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_CPHA,
      D => \S_DEL_COUNT_reg[7]_0\(22),
      Q => S_PRE_DELAY(6),
      R => RSTP
    );
\S_PRE_DELAY_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_CPHA,
      D => \S_DEL_COUNT_reg[7]_0\(23),
      Q => S_PRE_DELAY(7),
      R => RSTP
    );
\S_RAW_VALUE_S_C[0]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"8F808F8F8F808080"
    )
        port map (
      I0 => \^raw_value\(112),
      I1 => \S_RAW_VALUE_S_C_reg[0]\,
      I2 => \S_RAW_VALUE_S_C_reg[0]_0\(3),
      I3 => \S_RAW_VALUE_S_C[0]_i_2_n_0\,
      I4 => \S_RAW_VALUE_S_C_reg[0]_0\(2),
      I5 => \S_RAW_VALUE_S_C[0]_i_3_n_0\,
      O => \S_RX_OUT_BUFFER_reg[127]_0\(0)
    );
\S_RAW_VALUE_S_C[0]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => \^raw_value\(96),
      I1 => \^raw_value\(80),
      I2 => \S_RAW_VALUE_S_C_reg[0]_0\(1),
      I3 => \^raw_value\(64),
      I4 => \S_RAW_VALUE_S_C_reg[0]_0\(0),
      I5 => \^raw_value\(48),
      O => \S_RAW_VALUE_S_C[0]_i_2_n_0\
    );
\S_RAW_VALUE_S_C[0]_i_3\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"AFC0A0C0"
    )
        port map (
      I0 => \^raw_value\(32),
      I1 => \^raw_value\(16),
      I2 => \S_RAW_VALUE_S_C_reg[0]_0\(1),
      I3 => \S_RAW_VALUE_S_C_reg[0]_0\(0),
      I4 => \^raw_value\(0),
      O => \S_RAW_VALUE_S_C[0]_i_3_n_0\
    );
\S_RAW_VALUE_S_C[10]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"8F808F8F8F808080"
    )
        port map (
      I0 => \^raw_value\(122),
      I1 => \S_RAW_VALUE_S_C_reg[0]\,
      I2 => \S_RAW_VALUE_S_C_reg[0]_0\(3),
      I3 => \S_RAW_VALUE_S_C[10]_i_2_n_0\,
      I4 => \S_RAW_VALUE_S_C_reg[0]_0\(2),
      I5 => \S_RAW_VALUE_S_C[10]_i_3_n_0\,
      O => \S_RX_OUT_BUFFER_reg[127]_0\(10)
    );
\S_RAW_VALUE_S_C[10]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => \^raw_value\(106),
      I1 => \^raw_value\(90),
      I2 => \S_RAW_VALUE_S_C_reg[0]_0\(1),
      I3 => \^raw_value\(74),
      I4 => \S_RAW_VALUE_S_C_reg[0]_0\(0),
      I5 => \^raw_value\(58),
      O => \S_RAW_VALUE_S_C[10]_i_2_n_0\
    );
\S_RAW_VALUE_S_C[10]_i_3\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"AFC0A0C0"
    )
        port map (
      I0 => \^raw_value\(42),
      I1 => \^raw_value\(26),
      I2 => \S_RAW_VALUE_S_C_reg[0]_0\(1),
      I3 => \S_RAW_VALUE_S_C_reg[0]_0\(0),
      I4 => \^raw_value\(10),
      O => \S_RAW_VALUE_S_C[10]_i_3_n_0\
    );
\S_RAW_VALUE_S_C[11]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"8F808F8F8F808080"
    )
        port map (
      I0 => \^raw_value\(123),
      I1 => \S_RAW_VALUE_S_C_reg[0]\,
      I2 => \S_RAW_VALUE_S_C_reg[0]_0\(3),
      I3 => \S_RAW_VALUE_S_C[11]_i_2_n_0\,
      I4 => \S_RAW_VALUE_S_C_reg[0]_0\(2),
      I5 => \S_RAW_VALUE_S_C[11]_i_3_n_0\,
      O => \S_RX_OUT_BUFFER_reg[127]_0\(11)
    );
\S_RAW_VALUE_S_C[11]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => \^raw_value\(107),
      I1 => \^raw_value\(91),
      I2 => \S_RAW_VALUE_S_C_reg[0]_0\(1),
      I3 => \^raw_value\(75),
      I4 => \S_RAW_VALUE_S_C_reg[0]_0\(0),
      I5 => \^raw_value\(59),
      O => \S_RAW_VALUE_S_C[11]_i_2_n_0\
    );
\S_RAW_VALUE_S_C[11]_i_3\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"AFC0A0C0"
    )
        port map (
      I0 => \^raw_value\(43),
      I1 => \^raw_value\(27),
      I2 => \S_RAW_VALUE_S_C_reg[0]_0\(1),
      I3 => \S_RAW_VALUE_S_C_reg[0]_0\(0),
      I4 => \^raw_value\(11),
      O => \S_RAW_VALUE_S_C[11]_i_3_n_0\
    );
\S_RAW_VALUE_S_C[12]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"8F808F8F8F808080"
    )
        port map (
      I0 => \^raw_value\(124),
      I1 => \S_RAW_VALUE_S_C_reg[0]\,
      I2 => \S_RAW_VALUE_S_C_reg[0]_0\(3),
      I3 => \S_RAW_VALUE_S_C[12]_i_2_n_0\,
      I4 => \S_RAW_VALUE_S_C_reg[0]_0\(2),
      I5 => \S_RAW_VALUE_S_C[12]_i_3_n_0\,
      O => \S_RX_OUT_BUFFER_reg[127]_0\(12)
    );
\S_RAW_VALUE_S_C[12]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => \^raw_value\(108),
      I1 => \^raw_value\(92),
      I2 => \S_RAW_VALUE_S_C_reg[0]_0\(1),
      I3 => \^raw_value\(76),
      I4 => \S_RAW_VALUE_S_C_reg[0]_0\(0),
      I5 => \^raw_value\(60),
      O => \S_RAW_VALUE_S_C[12]_i_2_n_0\
    );
\S_RAW_VALUE_S_C[12]_i_3\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"AFC0A0C0"
    )
        port map (
      I0 => \^raw_value\(44),
      I1 => \^raw_value\(28),
      I2 => \S_RAW_VALUE_S_C_reg[0]_0\(1),
      I3 => \S_RAW_VALUE_S_C_reg[0]_0\(0),
      I4 => \^raw_value\(12),
      O => \S_RAW_VALUE_S_C[12]_i_3_n_0\
    );
\S_RAW_VALUE_S_C[13]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"8F808F8F8F808080"
    )
        port map (
      I0 => \^raw_value\(125),
      I1 => \S_RAW_VALUE_S_C_reg[0]\,
      I2 => \S_RAW_VALUE_S_C_reg[0]_0\(3),
      I3 => \S_RAW_VALUE_S_C[13]_i_2_n_0\,
      I4 => \S_RAW_VALUE_S_C_reg[0]_0\(2),
      I5 => \S_RAW_VALUE_S_C[13]_i_3_n_0\,
      O => \S_RX_OUT_BUFFER_reg[127]_0\(13)
    );
\S_RAW_VALUE_S_C[13]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => \^raw_value\(109),
      I1 => \^raw_value\(93),
      I2 => \S_RAW_VALUE_S_C_reg[0]_0\(1),
      I3 => \^raw_value\(77),
      I4 => \S_RAW_VALUE_S_C_reg[0]_0\(0),
      I5 => \^raw_value\(61),
      O => \S_RAW_VALUE_S_C[13]_i_2_n_0\
    );
\S_RAW_VALUE_S_C[13]_i_3\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"AFC0A0C0"
    )
        port map (
      I0 => \^raw_value\(45),
      I1 => \^raw_value\(29),
      I2 => \S_RAW_VALUE_S_C_reg[0]_0\(1),
      I3 => \S_RAW_VALUE_S_C_reg[0]_0\(0),
      I4 => \^raw_value\(13),
      O => \S_RAW_VALUE_S_C[13]_i_3_n_0\
    );
\S_RAW_VALUE_S_C[14]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"8F808F8F8F808080"
    )
        port map (
      I0 => \^raw_value\(126),
      I1 => \S_RAW_VALUE_S_C_reg[0]\,
      I2 => \S_RAW_VALUE_S_C_reg[0]_0\(3),
      I3 => \S_RAW_VALUE_S_C[14]_i_2_n_0\,
      I4 => \S_RAW_VALUE_S_C_reg[0]_0\(2),
      I5 => \S_RAW_VALUE_S_C[14]_i_3_n_0\,
      O => \S_RX_OUT_BUFFER_reg[127]_0\(14)
    );
\S_RAW_VALUE_S_C[14]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => \^raw_value\(110),
      I1 => \^raw_value\(94),
      I2 => \S_RAW_VALUE_S_C_reg[0]_0\(1),
      I3 => \^raw_value\(78),
      I4 => \S_RAW_VALUE_S_C_reg[0]_0\(0),
      I5 => \^raw_value\(62),
      O => \S_RAW_VALUE_S_C[14]_i_2_n_0\
    );
\S_RAW_VALUE_S_C[14]_i_3\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"AFC0A0C0"
    )
        port map (
      I0 => \^raw_value\(46),
      I1 => \^raw_value\(30),
      I2 => \S_RAW_VALUE_S_C_reg[0]_0\(1),
      I3 => \S_RAW_VALUE_S_C_reg[0]_0\(0),
      I4 => \^raw_value\(14),
      O => \S_RAW_VALUE_S_C[14]_i_3_n_0\
    );
\S_RAW_VALUE_S_C[15]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"8F808F8F8F808080"
    )
        port map (
      I0 => \^raw_value\(127),
      I1 => \S_RAW_VALUE_S_C_reg[0]\,
      I2 => \S_RAW_VALUE_S_C_reg[0]_0\(3),
      I3 => \S_RAW_VALUE_S_C[15]_i_4_n_0\,
      I4 => \S_RAW_VALUE_S_C_reg[0]_0\(2),
      I5 => \S_RAW_VALUE_S_C[15]_i_5_n_0\,
      O => \S_RX_OUT_BUFFER_reg[127]_0\(15)
    );
\S_RAW_VALUE_S_C[15]_i_4\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => \^raw_value\(111),
      I1 => \^raw_value\(95),
      I2 => \S_RAW_VALUE_S_C_reg[0]_0\(1),
      I3 => \^raw_value\(79),
      I4 => \S_RAW_VALUE_S_C_reg[0]_0\(0),
      I5 => \^raw_value\(63),
      O => \S_RAW_VALUE_S_C[15]_i_4_n_0\
    );
\S_RAW_VALUE_S_C[15]_i_5\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"AFC0A0C0"
    )
        port map (
      I0 => \^raw_value\(47),
      I1 => \^raw_value\(31),
      I2 => \S_RAW_VALUE_S_C_reg[0]_0\(1),
      I3 => \S_RAW_VALUE_S_C_reg[0]_0\(0),
      I4 => \^raw_value\(15),
      O => \S_RAW_VALUE_S_C[15]_i_5_n_0\
    );
\S_RAW_VALUE_S_C[1]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"8F808F8F8F808080"
    )
        port map (
      I0 => \^raw_value\(113),
      I1 => \S_RAW_VALUE_S_C_reg[0]\,
      I2 => \S_RAW_VALUE_S_C_reg[0]_0\(3),
      I3 => \S_RAW_VALUE_S_C[1]_i_2_n_0\,
      I4 => \S_RAW_VALUE_S_C_reg[0]_0\(2),
      I5 => \S_RAW_VALUE_S_C[1]_i_3_n_0\,
      O => \S_RX_OUT_BUFFER_reg[127]_0\(1)
    );
\S_RAW_VALUE_S_C[1]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => \^raw_value\(97),
      I1 => \^raw_value\(81),
      I2 => \S_RAW_VALUE_S_C_reg[0]_0\(1),
      I3 => \^raw_value\(65),
      I4 => \S_RAW_VALUE_S_C_reg[0]_0\(0),
      I5 => \^raw_value\(49),
      O => \S_RAW_VALUE_S_C[1]_i_2_n_0\
    );
\S_RAW_VALUE_S_C[1]_i_3\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"AFC0A0C0"
    )
        port map (
      I0 => \^raw_value\(33),
      I1 => \^raw_value\(17),
      I2 => \S_RAW_VALUE_S_C_reg[0]_0\(1),
      I3 => \S_RAW_VALUE_S_C_reg[0]_0\(0),
      I4 => \^raw_value\(1),
      O => \S_RAW_VALUE_S_C[1]_i_3_n_0\
    );
\S_RAW_VALUE_S_C[2]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"8F808F8F8F808080"
    )
        port map (
      I0 => \^raw_value\(114),
      I1 => \S_RAW_VALUE_S_C_reg[0]\,
      I2 => \S_RAW_VALUE_S_C_reg[0]_0\(3),
      I3 => \S_RAW_VALUE_S_C[2]_i_2_n_0\,
      I4 => \S_RAW_VALUE_S_C_reg[0]_0\(2),
      I5 => \S_RAW_VALUE_S_C[2]_i_3_n_0\,
      O => \S_RX_OUT_BUFFER_reg[127]_0\(2)
    );
\S_RAW_VALUE_S_C[2]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => \^raw_value\(98),
      I1 => \^raw_value\(82),
      I2 => \S_RAW_VALUE_S_C_reg[0]_0\(1),
      I3 => \^raw_value\(66),
      I4 => \S_RAW_VALUE_S_C_reg[0]_0\(0),
      I5 => \^raw_value\(50),
      O => \S_RAW_VALUE_S_C[2]_i_2_n_0\
    );
\S_RAW_VALUE_S_C[2]_i_3\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"AFC0A0C0"
    )
        port map (
      I0 => \^raw_value\(34),
      I1 => \^raw_value\(18),
      I2 => \S_RAW_VALUE_S_C_reg[0]_0\(1),
      I3 => \S_RAW_VALUE_S_C_reg[0]_0\(0),
      I4 => \^raw_value\(2),
      O => \S_RAW_VALUE_S_C[2]_i_3_n_0\
    );
\S_RAW_VALUE_S_C[3]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"8F808F8F8F808080"
    )
        port map (
      I0 => \^raw_value\(115),
      I1 => \S_RAW_VALUE_S_C_reg[0]\,
      I2 => \S_RAW_VALUE_S_C_reg[0]_0\(3),
      I3 => \S_RAW_VALUE_S_C[3]_i_2_n_0\,
      I4 => \S_RAW_VALUE_S_C_reg[0]_0\(2),
      I5 => \S_RAW_VALUE_S_C[3]_i_3_n_0\,
      O => \S_RX_OUT_BUFFER_reg[127]_0\(3)
    );
\S_RAW_VALUE_S_C[3]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => \^raw_value\(99),
      I1 => \^raw_value\(83),
      I2 => \S_RAW_VALUE_S_C_reg[0]_0\(1),
      I3 => \^raw_value\(67),
      I4 => \S_RAW_VALUE_S_C_reg[0]_0\(0),
      I5 => \^raw_value\(51),
      O => \S_RAW_VALUE_S_C[3]_i_2_n_0\
    );
\S_RAW_VALUE_S_C[3]_i_3\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"AFC0A0C0"
    )
        port map (
      I0 => \^raw_value\(35),
      I1 => \^raw_value\(19),
      I2 => \S_RAW_VALUE_S_C_reg[0]_0\(1),
      I3 => \S_RAW_VALUE_S_C_reg[0]_0\(0),
      I4 => \^raw_value\(3),
      O => \S_RAW_VALUE_S_C[3]_i_3_n_0\
    );
\S_RAW_VALUE_S_C[4]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"8F808F8F8F808080"
    )
        port map (
      I0 => \^raw_value\(116),
      I1 => \S_RAW_VALUE_S_C_reg[0]\,
      I2 => \S_RAW_VALUE_S_C_reg[0]_0\(3),
      I3 => \S_RAW_VALUE_S_C[4]_i_2_n_0\,
      I4 => \S_RAW_VALUE_S_C_reg[0]_0\(2),
      I5 => \S_RAW_VALUE_S_C[4]_i_3_n_0\,
      O => \S_RX_OUT_BUFFER_reg[127]_0\(4)
    );
\S_RAW_VALUE_S_C[4]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => \^raw_value\(100),
      I1 => \^raw_value\(84),
      I2 => \S_RAW_VALUE_S_C_reg[0]_0\(1),
      I3 => \^raw_value\(68),
      I4 => \S_RAW_VALUE_S_C_reg[0]_0\(0),
      I5 => \^raw_value\(52),
      O => \S_RAW_VALUE_S_C[4]_i_2_n_0\
    );
\S_RAW_VALUE_S_C[4]_i_3\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"AFC0A0C0"
    )
        port map (
      I0 => \^raw_value\(36),
      I1 => \^raw_value\(20),
      I2 => \S_RAW_VALUE_S_C_reg[0]_0\(1),
      I3 => \S_RAW_VALUE_S_C_reg[0]_0\(0),
      I4 => \^raw_value\(4),
      O => \S_RAW_VALUE_S_C[4]_i_3_n_0\
    );
\S_RAW_VALUE_S_C[5]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"8F808F8F8F808080"
    )
        port map (
      I0 => \^raw_value\(117),
      I1 => \S_RAW_VALUE_S_C_reg[0]\,
      I2 => \S_RAW_VALUE_S_C_reg[0]_0\(3),
      I3 => \S_RAW_VALUE_S_C[5]_i_2_n_0\,
      I4 => \S_RAW_VALUE_S_C_reg[0]_0\(2),
      I5 => \S_RAW_VALUE_S_C[5]_i_3_n_0\,
      O => \S_RX_OUT_BUFFER_reg[127]_0\(5)
    );
\S_RAW_VALUE_S_C[5]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => \^raw_value\(101),
      I1 => \^raw_value\(85),
      I2 => \S_RAW_VALUE_S_C_reg[0]_0\(1),
      I3 => \^raw_value\(69),
      I4 => \S_RAW_VALUE_S_C_reg[0]_0\(0),
      I5 => \^raw_value\(53),
      O => \S_RAW_VALUE_S_C[5]_i_2_n_0\
    );
\S_RAW_VALUE_S_C[5]_i_3\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"AFC0A0C0"
    )
        port map (
      I0 => \^raw_value\(37),
      I1 => \^raw_value\(21),
      I2 => \S_RAW_VALUE_S_C_reg[0]_0\(1),
      I3 => \S_RAW_VALUE_S_C_reg[0]_0\(0),
      I4 => \^raw_value\(5),
      O => \S_RAW_VALUE_S_C[5]_i_3_n_0\
    );
\S_RAW_VALUE_S_C[6]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"8F808F8F8F808080"
    )
        port map (
      I0 => \^raw_value\(118),
      I1 => \S_RAW_VALUE_S_C_reg[0]\,
      I2 => \S_RAW_VALUE_S_C_reg[0]_0\(3),
      I3 => \S_RAW_VALUE_S_C[6]_i_2_n_0\,
      I4 => \S_RAW_VALUE_S_C_reg[0]_0\(2),
      I5 => \S_RAW_VALUE_S_C[6]_i_3_n_0\,
      O => \S_RX_OUT_BUFFER_reg[127]_0\(6)
    );
\S_RAW_VALUE_S_C[6]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => \^raw_value\(102),
      I1 => \^raw_value\(86),
      I2 => \S_RAW_VALUE_S_C_reg[0]_0\(1),
      I3 => \^raw_value\(70),
      I4 => \S_RAW_VALUE_S_C_reg[0]_0\(0),
      I5 => \^raw_value\(54),
      O => \S_RAW_VALUE_S_C[6]_i_2_n_0\
    );
\S_RAW_VALUE_S_C[6]_i_3\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"AFC0A0C0"
    )
        port map (
      I0 => \^raw_value\(38),
      I1 => \^raw_value\(22),
      I2 => \S_RAW_VALUE_S_C_reg[0]_0\(1),
      I3 => \S_RAW_VALUE_S_C_reg[0]_0\(0),
      I4 => \^raw_value\(6),
      O => \S_RAW_VALUE_S_C[6]_i_3_n_0\
    );
\S_RAW_VALUE_S_C[7]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"8F808F8F8F808080"
    )
        port map (
      I0 => \^raw_value\(119),
      I1 => \S_RAW_VALUE_S_C_reg[0]\,
      I2 => \S_RAW_VALUE_S_C_reg[0]_0\(3),
      I3 => \S_RAW_VALUE_S_C[7]_i_2_n_0\,
      I4 => \S_RAW_VALUE_S_C_reg[0]_0\(2),
      I5 => \S_RAW_VALUE_S_C[7]_i_3_n_0\,
      O => \S_RX_OUT_BUFFER_reg[127]_0\(7)
    );
\S_RAW_VALUE_S_C[7]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => \^raw_value\(103),
      I1 => \^raw_value\(87),
      I2 => \S_RAW_VALUE_S_C_reg[0]_0\(1),
      I3 => \^raw_value\(71),
      I4 => \S_RAW_VALUE_S_C_reg[0]_0\(0),
      I5 => \^raw_value\(55),
      O => \S_RAW_VALUE_S_C[7]_i_2_n_0\
    );
\S_RAW_VALUE_S_C[7]_i_3\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"AFC0A0C0"
    )
        port map (
      I0 => \^raw_value\(39),
      I1 => \^raw_value\(23),
      I2 => \S_RAW_VALUE_S_C_reg[0]_0\(1),
      I3 => \S_RAW_VALUE_S_C_reg[0]_0\(0),
      I4 => \^raw_value\(7),
      O => \S_RAW_VALUE_S_C[7]_i_3_n_0\
    );
\S_RAW_VALUE_S_C[8]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"8F808F8F8F808080"
    )
        port map (
      I0 => \^raw_value\(120),
      I1 => \S_RAW_VALUE_S_C_reg[0]\,
      I2 => \S_RAW_VALUE_S_C_reg[0]_0\(3),
      I3 => \S_RAW_VALUE_S_C[8]_i_2_n_0\,
      I4 => \S_RAW_VALUE_S_C_reg[0]_0\(2),
      I5 => \S_RAW_VALUE_S_C[8]_i_3_n_0\,
      O => \S_RX_OUT_BUFFER_reg[127]_0\(8)
    );
\S_RAW_VALUE_S_C[8]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => \^raw_value\(104),
      I1 => \^raw_value\(88),
      I2 => \S_RAW_VALUE_S_C_reg[0]_0\(1),
      I3 => \^raw_value\(72),
      I4 => \S_RAW_VALUE_S_C_reg[0]_0\(0),
      I5 => \^raw_value\(56),
      O => \S_RAW_VALUE_S_C[8]_i_2_n_0\
    );
\S_RAW_VALUE_S_C[8]_i_3\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"AFC0A0C0"
    )
        port map (
      I0 => \^raw_value\(40),
      I1 => \^raw_value\(24),
      I2 => \S_RAW_VALUE_S_C_reg[0]_0\(1),
      I3 => \S_RAW_VALUE_S_C_reg[0]_0\(0),
      I4 => \^raw_value\(8),
      O => \S_RAW_VALUE_S_C[8]_i_3_n_0\
    );
\S_RAW_VALUE_S_C[9]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"8F808F8F8F808080"
    )
        port map (
      I0 => \^raw_value\(121),
      I1 => \S_RAW_VALUE_S_C_reg[0]\,
      I2 => \S_RAW_VALUE_S_C_reg[0]_0\(3),
      I3 => \S_RAW_VALUE_S_C[9]_i_2_n_0\,
      I4 => \S_RAW_VALUE_S_C_reg[0]_0\(2),
      I5 => \S_RAW_VALUE_S_C[9]_i_3_n_0\,
      O => \S_RX_OUT_BUFFER_reg[127]_0\(9)
    );
\S_RAW_VALUE_S_C[9]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => \^raw_value\(105),
      I1 => \^raw_value\(89),
      I2 => \S_RAW_VALUE_S_C_reg[0]_0\(1),
      I3 => \^raw_value\(73),
      I4 => \S_RAW_VALUE_S_C_reg[0]_0\(0),
      I5 => \^raw_value\(57),
      O => \S_RAW_VALUE_S_C[9]_i_2_n_0\
    );
\S_RAW_VALUE_S_C[9]_i_3\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"AFC0A0C0"
    )
        port map (
      I0 => \^raw_value\(41),
      I1 => \^raw_value\(25),
      I2 => \S_RAW_VALUE_S_C_reg[0]_0\(1),
      I3 => \S_RAW_VALUE_S_C_reg[0]_0\(0),
      I4 => \^raw_value\(9),
      O => \S_RAW_VALUE_S_C[9]_i_3_n_0\
    );
\S_RX_BUFFER[127]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"00000A3000000A00"
    )
        port map (
      I0 => nxtstate1,
      I1 => S_CPHA_reg_n_0,
      I2 => curstate(0),
      I3 => curstate(1),
      I4 => curstate(2),
      I5 => SS_OUT_N_i_2_n_0,
      O => S_RX_BUFFER
    );
\S_RX_BUFFER_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_BUFFER,
      D => \S_RX_BUFFER_reg[112]_0\(0),
      Q => p_0_out(1),
      R => RSTP
    );
\S_RX_BUFFER_reg[100]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_BUFFER,
      D => p_0_out(100),
      Q => p_0_out(101),
      R => RSTP
    );
\S_RX_BUFFER_reg[101]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_BUFFER,
      D => p_0_out(101),
      Q => p_0_out(102),
      R => RSTP
    );
\S_RX_BUFFER_reg[102]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_BUFFER,
      D => p_0_out(102),
      Q => p_0_out(103),
      R => RSTP
    );
\S_RX_BUFFER_reg[103]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_BUFFER,
      D => p_0_out(103),
      Q => p_0_out(104),
      R => RSTP
    );
\S_RX_BUFFER_reg[104]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_BUFFER,
      D => p_0_out(104),
      Q => p_0_out(105),
      R => RSTP
    );
\S_RX_BUFFER_reg[105]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_BUFFER,
      D => p_0_out(105),
      Q => p_0_out(106),
      R => RSTP
    );
\S_RX_BUFFER_reg[106]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_BUFFER,
      D => p_0_out(106),
      Q => p_0_out(107),
      R => RSTP
    );
\S_RX_BUFFER_reg[107]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_BUFFER,
      D => p_0_out(107),
      Q => p_0_out(108),
      R => RSTP
    );
\S_RX_BUFFER_reg[108]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_BUFFER,
      D => p_0_out(108),
      Q => p_0_out(109),
      R => RSTP
    );
\S_RX_BUFFER_reg[109]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_BUFFER,
      D => p_0_out(109),
      Q => p_0_out(110),
      R => RSTP
    );
\S_RX_BUFFER_reg[10]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_BUFFER,
      D => p_0_out(10),
      Q => p_0_out(11),
      R => RSTP
    );
\S_RX_BUFFER_reg[110]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_BUFFER,
      D => p_0_out(110),
      Q => p_0_out(111),
      R => RSTP
    );
\S_RX_BUFFER_reg[111]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_BUFFER,
      D => p_0_out(111),
      Q => \S_RX_BUFFER_reg_n_0_[111]\,
      R => RSTP
    );
\S_RX_BUFFER_reg[112]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_BUFFER,
      D => \S_RX_BUFFER_reg[112]_0\(7),
      Q => p_0_out(113),
      R => RSTP
    );
\S_RX_BUFFER_reg[113]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_BUFFER,
      D => p_0_out(113),
      Q => p_0_out(114),
      R => RSTP
    );
\S_RX_BUFFER_reg[114]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_BUFFER,
      D => p_0_out(114),
      Q => p_0_out(115),
      R => RSTP
    );
\S_RX_BUFFER_reg[115]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_BUFFER,
      D => p_0_out(115),
      Q => p_0_out(116),
      R => RSTP
    );
\S_RX_BUFFER_reg[116]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_BUFFER,
      D => p_0_out(116),
      Q => p_0_out(117),
      R => RSTP
    );
\S_RX_BUFFER_reg[117]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_BUFFER,
      D => p_0_out(117),
      Q => p_0_out(118),
      R => RSTP
    );
\S_RX_BUFFER_reg[118]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_BUFFER,
      D => p_0_out(118),
      Q => p_0_out(119),
      R => RSTP
    );
\S_RX_BUFFER_reg[119]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_BUFFER,
      D => p_0_out(119),
      Q => p_0_out(120),
      R => RSTP
    );
\S_RX_BUFFER_reg[11]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_BUFFER,
      D => p_0_out(11),
      Q => p_0_out(12),
      R => RSTP
    );
\S_RX_BUFFER_reg[120]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_BUFFER,
      D => p_0_out(120),
      Q => p_0_out(121),
      R => RSTP
    );
\S_RX_BUFFER_reg[121]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_BUFFER,
      D => p_0_out(121),
      Q => p_0_out(122),
      R => RSTP
    );
\S_RX_BUFFER_reg[122]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_BUFFER,
      D => p_0_out(122),
      Q => p_0_out(123),
      R => RSTP
    );
\S_RX_BUFFER_reg[123]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_BUFFER,
      D => p_0_out(123),
      Q => p_0_out(124),
      R => RSTP
    );
\S_RX_BUFFER_reg[124]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_BUFFER,
      D => p_0_out(124),
      Q => p_0_out(125),
      R => RSTP
    );
\S_RX_BUFFER_reg[125]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_BUFFER,
      D => p_0_out(125),
      Q => p_0_out(126),
      R => RSTP
    );
\S_RX_BUFFER_reg[126]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_BUFFER,
      D => p_0_out(126),
      Q => p_0_out(127),
      R => RSTP
    );
\S_RX_BUFFER_reg[127]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_BUFFER,
      D => p_0_out(127),
      Q => \S_RX_BUFFER_reg_n_0_[127]\,
      R => RSTP
    );
\S_RX_BUFFER_reg[12]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_BUFFER,
      D => p_0_out(12),
      Q => p_0_out(13),
      R => RSTP
    );
\S_RX_BUFFER_reg[13]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_BUFFER,
      D => p_0_out(13),
      Q => p_0_out(14),
      R => RSTP
    );
\S_RX_BUFFER_reg[14]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_BUFFER,
      D => p_0_out(14),
      Q => p_0_out(15),
      R => RSTP
    );
\S_RX_BUFFER_reg[15]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_BUFFER,
      D => p_0_out(15),
      Q => \S_RX_BUFFER_reg_n_0_[15]\,
      R => RSTP
    );
\S_RX_BUFFER_reg[16]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_BUFFER,
      D => \S_RX_BUFFER_reg[112]_0\(1),
      Q => p_0_out(17),
      R => RSTP
    );
\S_RX_BUFFER_reg[17]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_BUFFER,
      D => p_0_out(17),
      Q => p_0_out(18),
      R => RSTP
    );
\S_RX_BUFFER_reg[18]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_BUFFER,
      D => p_0_out(18),
      Q => p_0_out(19),
      R => RSTP
    );
\S_RX_BUFFER_reg[19]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_BUFFER,
      D => p_0_out(19),
      Q => p_0_out(20),
      R => RSTP
    );
\S_RX_BUFFER_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_BUFFER,
      D => p_0_out(1),
      Q => p_0_out(2),
      R => RSTP
    );
\S_RX_BUFFER_reg[20]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_BUFFER,
      D => p_0_out(20),
      Q => p_0_out(21),
      R => RSTP
    );
\S_RX_BUFFER_reg[21]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_BUFFER,
      D => p_0_out(21),
      Q => p_0_out(22),
      R => RSTP
    );
\S_RX_BUFFER_reg[22]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_BUFFER,
      D => p_0_out(22),
      Q => p_0_out(23),
      R => RSTP
    );
\S_RX_BUFFER_reg[23]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_BUFFER,
      D => p_0_out(23),
      Q => p_0_out(24),
      R => RSTP
    );
\S_RX_BUFFER_reg[24]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_BUFFER,
      D => p_0_out(24),
      Q => p_0_out(25),
      R => RSTP
    );
\S_RX_BUFFER_reg[25]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_BUFFER,
      D => p_0_out(25),
      Q => p_0_out(26),
      R => RSTP
    );
\S_RX_BUFFER_reg[26]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_BUFFER,
      D => p_0_out(26),
      Q => p_0_out(27),
      R => RSTP
    );
\S_RX_BUFFER_reg[27]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_BUFFER,
      D => p_0_out(27),
      Q => p_0_out(28),
      R => RSTP
    );
\S_RX_BUFFER_reg[28]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_BUFFER,
      D => p_0_out(28),
      Q => p_0_out(29),
      R => RSTP
    );
\S_RX_BUFFER_reg[29]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_BUFFER,
      D => p_0_out(29),
      Q => p_0_out(30),
      R => RSTP
    );
\S_RX_BUFFER_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_BUFFER,
      D => p_0_out(2),
      Q => p_0_out(3),
      R => RSTP
    );
\S_RX_BUFFER_reg[30]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_BUFFER,
      D => p_0_out(30),
      Q => p_0_out(31),
      R => RSTP
    );
\S_RX_BUFFER_reg[31]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_BUFFER,
      D => p_0_out(31),
      Q => \S_RX_BUFFER_reg_n_0_[31]\,
      R => RSTP
    );
\S_RX_BUFFER_reg[32]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_BUFFER,
      D => \S_RX_BUFFER_reg[112]_0\(2),
      Q => p_0_out(33),
      R => RSTP
    );
\S_RX_BUFFER_reg[33]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_BUFFER,
      D => p_0_out(33),
      Q => p_0_out(34),
      R => RSTP
    );
\S_RX_BUFFER_reg[34]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_BUFFER,
      D => p_0_out(34),
      Q => p_0_out(35),
      R => RSTP
    );
\S_RX_BUFFER_reg[35]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_BUFFER,
      D => p_0_out(35),
      Q => p_0_out(36),
      R => RSTP
    );
\S_RX_BUFFER_reg[36]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_BUFFER,
      D => p_0_out(36),
      Q => p_0_out(37),
      R => RSTP
    );
\S_RX_BUFFER_reg[37]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_BUFFER,
      D => p_0_out(37),
      Q => p_0_out(38),
      R => RSTP
    );
\S_RX_BUFFER_reg[38]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_BUFFER,
      D => p_0_out(38),
      Q => p_0_out(39),
      R => RSTP
    );
\S_RX_BUFFER_reg[39]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_BUFFER,
      D => p_0_out(39),
      Q => p_0_out(40),
      R => RSTP
    );
\S_RX_BUFFER_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_BUFFER,
      D => p_0_out(3),
      Q => p_0_out(4),
      R => RSTP
    );
\S_RX_BUFFER_reg[40]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_BUFFER,
      D => p_0_out(40),
      Q => p_0_out(41),
      R => RSTP
    );
\S_RX_BUFFER_reg[41]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_BUFFER,
      D => p_0_out(41),
      Q => p_0_out(42),
      R => RSTP
    );
\S_RX_BUFFER_reg[42]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_BUFFER,
      D => p_0_out(42),
      Q => p_0_out(43),
      R => RSTP
    );
\S_RX_BUFFER_reg[43]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_BUFFER,
      D => p_0_out(43),
      Q => p_0_out(44),
      R => RSTP
    );
\S_RX_BUFFER_reg[44]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_BUFFER,
      D => p_0_out(44),
      Q => p_0_out(45),
      R => RSTP
    );
\S_RX_BUFFER_reg[45]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_BUFFER,
      D => p_0_out(45),
      Q => p_0_out(46),
      R => RSTP
    );
\S_RX_BUFFER_reg[46]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_BUFFER,
      D => p_0_out(46),
      Q => p_0_out(47),
      R => RSTP
    );
\S_RX_BUFFER_reg[47]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_BUFFER,
      D => p_0_out(47),
      Q => \S_RX_BUFFER_reg_n_0_[47]\,
      R => RSTP
    );
\S_RX_BUFFER_reg[48]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_BUFFER,
      D => \S_RX_BUFFER_reg[112]_0\(3),
      Q => p_0_out(49),
      R => RSTP
    );
\S_RX_BUFFER_reg[49]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_BUFFER,
      D => p_0_out(49),
      Q => p_0_out(50),
      R => RSTP
    );
\S_RX_BUFFER_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_BUFFER,
      D => p_0_out(4),
      Q => p_0_out(5),
      R => RSTP
    );
\S_RX_BUFFER_reg[50]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_BUFFER,
      D => p_0_out(50),
      Q => p_0_out(51),
      R => RSTP
    );
\S_RX_BUFFER_reg[51]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_BUFFER,
      D => p_0_out(51),
      Q => p_0_out(52),
      R => RSTP
    );
\S_RX_BUFFER_reg[52]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_BUFFER,
      D => p_0_out(52),
      Q => p_0_out(53),
      R => RSTP
    );
\S_RX_BUFFER_reg[53]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_BUFFER,
      D => p_0_out(53),
      Q => p_0_out(54),
      R => RSTP
    );
\S_RX_BUFFER_reg[54]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_BUFFER,
      D => p_0_out(54),
      Q => p_0_out(55),
      R => RSTP
    );
\S_RX_BUFFER_reg[55]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_BUFFER,
      D => p_0_out(55),
      Q => p_0_out(56),
      R => RSTP
    );
\S_RX_BUFFER_reg[56]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_BUFFER,
      D => p_0_out(56),
      Q => p_0_out(57),
      R => RSTP
    );
\S_RX_BUFFER_reg[57]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_BUFFER,
      D => p_0_out(57),
      Q => p_0_out(58),
      R => RSTP
    );
\S_RX_BUFFER_reg[58]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_BUFFER,
      D => p_0_out(58),
      Q => p_0_out(59),
      R => RSTP
    );
\S_RX_BUFFER_reg[59]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_BUFFER,
      D => p_0_out(59),
      Q => p_0_out(60),
      R => RSTP
    );
\S_RX_BUFFER_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_BUFFER,
      D => p_0_out(5),
      Q => p_0_out(6),
      R => RSTP
    );
\S_RX_BUFFER_reg[60]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_BUFFER,
      D => p_0_out(60),
      Q => p_0_out(61),
      R => RSTP
    );
\S_RX_BUFFER_reg[61]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_BUFFER,
      D => p_0_out(61),
      Q => p_0_out(62),
      R => RSTP
    );
\S_RX_BUFFER_reg[62]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_BUFFER,
      D => p_0_out(62),
      Q => p_0_out(63),
      R => RSTP
    );
\S_RX_BUFFER_reg[63]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_BUFFER,
      D => p_0_out(63),
      Q => \S_RX_BUFFER_reg_n_0_[63]\,
      R => RSTP
    );
\S_RX_BUFFER_reg[64]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_BUFFER,
      D => \S_RX_BUFFER_reg[112]_0\(4),
      Q => p_0_out(65),
      R => RSTP
    );
\S_RX_BUFFER_reg[65]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_BUFFER,
      D => p_0_out(65),
      Q => p_0_out(66),
      R => RSTP
    );
\S_RX_BUFFER_reg[66]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_BUFFER,
      D => p_0_out(66),
      Q => p_0_out(67),
      R => RSTP
    );
\S_RX_BUFFER_reg[67]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_BUFFER,
      D => p_0_out(67),
      Q => p_0_out(68),
      R => RSTP
    );
\S_RX_BUFFER_reg[68]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_BUFFER,
      D => p_0_out(68),
      Q => p_0_out(69),
      R => RSTP
    );
\S_RX_BUFFER_reg[69]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_BUFFER,
      D => p_0_out(69),
      Q => p_0_out(70),
      R => RSTP
    );
\S_RX_BUFFER_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_BUFFER,
      D => p_0_out(6),
      Q => p_0_out(7),
      R => RSTP
    );
\S_RX_BUFFER_reg[70]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_BUFFER,
      D => p_0_out(70),
      Q => p_0_out(71),
      R => RSTP
    );
\S_RX_BUFFER_reg[71]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_BUFFER,
      D => p_0_out(71),
      Q => p_0_out(72),
      R => RSTP
    );
\S_RX_BUFFER_reg[72]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_BUFFER,
      D => p_0_out(72),
      Q => p_0_out(73),
      R => RSTP
    );
\S_RX_BUFFER_reg[73]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_BUFFER,
      D => p_0_out(73),
      Q => p_0_out(74),
      R => RSTP
    );
\S_RX_BUFFER_reg[74]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_BUFFER,
      D => p_0_out(74),
      Q => p_0_out(75),
      R => RSTP
    );
\S_RX_BUFFER_reg[75]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_BUFFER,
      D => p_0_out(75),
      Q => p_0_out(76),
      R => RSTP
    );
\S_RX_BUFFER_reg[76]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_BUFFER,
      D => p_0_out(76),
      Q => p_0_out(77),
      R => RSTP
    );
\S_RX_BUFFER_reg[77]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_BUFFER,
      D => p_0_out(77),
      Q => p_0_out(78),
      R => RSTP
    );
\S_RX_BUFFER_reg[78]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_BUFFER,
      D => p_0_out(78),
      Q => p_0_out(79),
      R => RSTP
    );
\S_RX_BUFFER_reg[79]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_BUFFER,
      D => p_0_out(79),
      Q => \S_RX_BUFFER_reg_n_0_[79]\,
      R => RSTP
    );
\S_RX_BUFFER_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_BUFFER,
      D => p_0_out(7),
      Q => p_0_out(8),
      R => RSTP
    );
\S_RX_BUFFER_reg[80]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_BUFFER,
      D => \S_RX_BUFFER_reg[112]_0\(5),
      Q => p_0_out(81),
      R => RSTP
    );
\S_RX_BUFFER_reg[81]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_BUFFER,
      D => p_0_out(81),
      Q => p_0_out(82),
      R => RSTP
    );
\S_RX_BUFFER_reg[82]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_BUFFER,
      D => p_0_out(82),
      Q => p_0_out(83),
      R => RSTP
    );
\S_RX_BUFFER_reg[83]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_BUFFER,
      D => p_0_out(83),
      Q => p_0_out(84),
      R => RSTP
    );
\S_RX_BUFFER_reg[84]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_BUFFER,
      D => p_0_out(84),
      Q => p_0_out(85),
      R => RSTP
    );
\S_RX_BUFFER_reg[85]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_BUFFER,
      D => p_0_out(85),
      Q => p_0_out(86),
      R => RSTP
    );
\S_RX_BUFFER_reg[86]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_BUFFER,
      D => p_0_out(86),
      Q => p_0_out(87),
      R => RSTP
    );
\S_RX_BUFFER_reg[87]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_BUFFER,
      D => p_0_out(87),
      Q => p_0_out(88),
      R => RSTP
    );
\S_RX_BUFFER_reg[88]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_BUFFER,
      D => p_0_out(88),
      Q => p_0_out(89),
      R => RSTP
    );
\S_RX_BUFFER_reg[89]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_BUFFER,
      D => p_0_out(89),
      Q => p_0_out(90),
      R => RSTP
    );
\S_RX_BUFFER_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_BUFFER,
      D => p_0_out(8),
      Q => p_0_out(9),
      R => RSTP
    );
\S_RX_BUFFER_reg[90]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_BUFFER,
      D => p_0_out(90),
      Q => p_0_out(91),
      R => RSTP
    );
\S_RX_BUFFER_reg[91]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_BUFFER,
      D => p_0_out(91),
      Q => p_0_out(92),
      R => RSTP
    );
\S_RX_BUFFER_reg[92]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_BUFFER,
      D => p_0_out(92),
      Q => p_0_out(93),
      R => RSTP
    );
\S_RX_BUFFER_reg[93]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_BUFFER,
      D => p_0_out(93),
      Q => p_0_out(94),
      R => RSTP
    );
\S_RX_BUFFER_reg[94]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_BUFFER,
      D => p_0_out(94),
      Q => p_0_out(95),
      R => RSTP
    );
\S_RX_BUFFER_reg[95]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_BUFFER,
      D => p_0_out(95),
      Q => \S_RX_BUFFER_reg_n_0_[95]\,
      R => RSTP
    );
\S_RX_BUFFER_reg[96]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_BUFFER,
      D => \S_RX_BUFFER_reg[112]_0\(6),
      Q => p_0_out(97),
      R => RSTP
    );
\S_RX_BUFFER_reg[97]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_BUFFER,
      D => p_0_out(97),
      Q => p_0_out(98),
      R => RSTP
    );
\S_RX_BUFFER_reg[98]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_BUFFER,
      D => p_0_out(98),
      Q => p_0_out(99),
      R => RSTP
    );
\S_RX_BUFFER_reg[99]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_BUFFER,
      D => p_0_out(99),
      Q => p_0_out(100),
      R => RSTP
    );
\S_RX_BUFFER_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_BUFFER,
      D => p_0_out(9),
      Q => p_0_out(10),
      R => RSTP
    );
\S_RX_OUT_BUFFER[127]_i_2\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"0080"
    )
        port map (
      I0 => \S_RX_OUT_BUFFER[127]_i_3_n_0\,
      I1 => curstate(0),
      I2 => curstate(1),
      I3 => curstate(2),
      O => S_RX_OUT_BUFFER
    );
\S_RX_OUT_BUFFER[127]_i_3\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AAAAAAAAAAAAAAAB"
    )
        port map (
      I0 => \S_BIT_COUNT_reg_n_0_[5]\,
      I1 => \S_BIT_COUNT_reg_n_0_[0]\,
      I2 => \S_BIT_COUNT_reg_n_0_[3]\,
      I3 => \S_BIT_COUNT_reg_n_0_[1]\,
      I4 => \S_BIT_COUNT_reg_n_0_[2]\,
      I5 => \S_BIT_COUNT_reg_n_0_[4]\,
      O => \S_RX_OUT_BUFFER[127]_i_3_n_0\
    );
\S_RX_OUT_BUFFER_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_OUT_BUFFER,
      D => p_0_out(1),
      Q => \^raw_value\(0),
      R => RSTP
    );
\S_RX_OUT_BUFFER_reg[100]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_OUT_BUFFER,
      D => p_0_out(101),
      Q => \^raw_value\(100),
      R => RSTP
    );
\S_RX_OUT_BUFFER_reg[101]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_OUT_BUFFER,
      D => p_0_out(102),
      Q => \^raw_value\(101),
      R => RSTP
    );
\S_RX_OUT_BUFFER_reg[102]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_OUT_BUFFER,
      D => p_0_out(103),
      Q => \^raw_value\(102),
      R => RSTP
    );
\S_RX_OUT_BUFFER_reg[103]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_OUT_BUFFER,
      D => p_0_out(104),
      Q => \^raw_value\(103),
      R => RSTP
    );
\S_RX_OUT_BUFFER_reg[104]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_OUT_BUFFER,
      D => p_0_out(105),
      Q => \^raw_value\(104),
      R => RSTP
    );
\S_RX_OUT_BUFFER_reg[105]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_OUT_BUFFER,
      D => p_0_out(106),
      Q => \^raw_value\(105),
      R => RSTP
    );
\S_RX_OUT_BUFFER_reg[106]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_OUT_BUFFER,
      D => p_0_out(107),
      Q => \^raw_value\(106),
      R => RSTP
    );
\S_RX_OUT_BUFFER_reg[107]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_OUT_BUFFER,
      D => p_0_out(108),
      Q => \^raw_value\(107),
      R => RSTP
    );
\S_RX_OUT_BUFFER_reg[108]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_OUT_BUFFER,
      D => p_0_out(109),
      Q => \^raw_value\(108),
      R => RSTP
    );
\S_RX_OUT_BUFFER_reg[109]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_OUT_BUFFER,
      D => p_0_out(110),
      Q => \^raw_value\(109),
      R => RSTP
    );
\S_RX_OUT_BUFFER_reg[10]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_OUT_BUFFER,
      D => p_0_out(11),
      Q => \^raw_value\(10),
      R => RSTP
    );
\S_RX_OUT_BUFFER_reg[110]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_OUT_BUFFER,
      D => p_0_out(111),
      Q => \^raw_value\(110),
      R => RSTP
    );
\S_RX_OUT_BUFFER_reg[111]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_OUT_BUFFER,
      D => \S_RX_BUFFER_reg_n_0_[111]\,
      Q => \^raw_value\(111),
      R => RSTP
    );
\S_RX_OUT_BUFFER_reg[112]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_OUT_BUFFER,
      D => p_0_out(113),
      Q => \^raw_value\(112),
      R => RSTP
    );
\S_RX_OUT_BUFFER_reg[113]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_OUT_BUFFER,
      D => p_0_out(114),
      Q => \^raw_value\(113),
      R => RSTP
    );
\S_RX_OUT_BUFFER_reg[114]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_OUT_BUFFER,
      D => p_0_out(115),
      Q => \^raw_value\(114),
      R => RSTP
    );
\S_RX_OUT_BUFFER_reg[115]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_OUT_BUFFER,
      D => p_0_out(116),
      Q => \^raw_value\(115),
      R => RSTP
    );
\S_RX_OUT_BUFFER_reg[116]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_OUT_BUFFER,
      D => p_0_out(117),
      Q => \^raw_value\(116),
      R => RSTP
    );
\S_RX_OUT_BUFFER_reg[117]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_OUT_BUFFER,
      D => p_0_out(118),
      Q => \^raw_value\(117),
      R => RSTP
    );
\S_RX_OUT_BUFFER_reg[118]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_OUT_BUFFER,
      D => p_0_out(119),
      Q => \^raw_value\(118),
      R => RSTP
    );
\S_RX_OUT_BUFFER_reg[119]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_OUT_BUFFER,
      D => p_0_out(120),
      Q => \^raw_value\(119),
      R => RSTP
    );
\S_RX_OUT_BUFFER_reg[11]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_OUT_BUFFER,
      D => p_0_out(12),
      Q => \^raw_value\(11),
      R => RSTP
    );
\S_RX_OUT_BUFFER_reg[120]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_OUT_BUFFER,
      D => p_0_out(121),
      Q => \^raw_value\(120),
      R => RSTP
    );
\S_RX_OUT_BUFFER_reg[121]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_OUT_BUFFER,
      D => p_0_out(122),
      Q => \^raw_value\(121),
      R => RSTP
    );
\S_RX_OUT_BUFFER_reg[122]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_OUT_BUFFER,
      D => p_0_out(123),
      Q => \^raw_value\(122),
      R => RSTP
    );
\S_RX_OUT_BUFFER_reg[123]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_OUT_BUFFER,
      D => p_0_out(124),
      Q => \^raw_value\(123),
      R => RSTP
    );
\S_RX_OUT_BUFFER_reg[124]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_OUT_BUFFER,
      D => p_0_out(125),
      Q => \^raw_value\(124),
      R => RSTP
    );
\S_RX_OUT_BUFFER_reg[125]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_OUT_BUFFER,
      D => p_0_out(126),
      Q => \^raw_value\(125),
      R => RSTP
    );
\S_RX_OUT_BUFFER_reg[126]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_OUT_BUFFER,
      D => p_0_out(127),
      Q => \^raw_value\(126),
      R => RSTP
    );
\S_RX_OUT_BUFFER_reg[127]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_OUT_BUFFER,
      D => \S_RX_BUFFER_reg_n_0_[127]\,
      Q => \^raw_value\(127),
      R => RSTP
    );
\S_RX_OUT_BUFFER_reg[12]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_OUT_BUFFER,
      D => p_0_out(13),
      Q => \^raw_value\(12),
      R => RSTP
    );
\S_RX_OUT_BUFFER_reg[13]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_OUT_BUFFER,
      D => p_0_out(14),
      Q => \^raw_value\(13),
      R => RSTP
    );
\S_RX_OUT_BUFFER_reg[14]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_OUT_BUFFER,
      D => p_0_out(15),
      Q => \^raw_value\(14),
      R => RSTP
    );
\S_RX_OUT_BUFFER_reg[15]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_OUT_BUFFER,
      D => \S_RX_BUFFER_reg_n_0_[15]\,
      Q => \^raw_value\(15),
      R => RSTP
    );
\S_RX_OUT_BUFFER_reg[16]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_OUT_BUFFER,
      D => p_0_out(17),
      Q => \^raw_value\(16),
      R => RSTP
    );
\S_RX_OUT_BUFFER_reg[17]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_OUT_BUFFER,
      D => p_0_out(18),
      Q => \^raw_value\(17),
      R => RSTP
    );
\S_RX_OUT_BUFFER_reg[18]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_OUT_BUFFER,
      D => p_0_out(19),
      Q => \^raw_value\(18),
      R => RSTP
    );
\S_RX_OUT_BUFFER_reg[19]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_OUT_BUFFER,
      D => p_0_out(20),
      Q => \^raw_value\(19),
      R => RSTP
    );
\S_RX_OUT_BUFFER_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_OUT_BUFFER,
      D => p_0_out(2),
      Q => \^raw_value\(1),
      R => RSTP
    );
\S_RX_OUT_BUFFER_reg[20]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_OUT_BUFFER,
      D => p_0_out(21),
      Q => \^raw_value\(20),
      R => RSTP
    );
\S_RX_OUT_BUFFER_reg[21]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_OUT_BUFFER,
      D => p_0_out(22),
      Q => \^raw_value\(21),
      R => RSTP
    );
\S_RX_OUT_BUFFER_reg[22]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_OUT_BUFFER,
      D => p_0_out(23),
      Q => \^raw_value\(22),
      R => RSTP
    );
\S_RX_OUT_BUFFER_reg[23]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_OUT_BUFFER,
      D => p_0_out(24),
      Q => \^raw_value\(23),
      R => RSTP
    );
\S_RX_OUT_BUFFER_reg[24]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_OUT_BUFFER,
      D => p_0_out(25),
      Q => \^raw_value\(24),
      R => RSTP
    );
\S_RX_OUT_BUFFER_reg[25]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_OUT_BUFFER,
      D => p_0_out(26),
      Q => \^raw_value\(25),
      R => RSTP
    );
\S_RX_OUT_BUFFER_reg[26]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_OUT_BUFFER,
      D => p_0_out(27),
      Q => \^raw_value\(26),
      R => RSTP
    );
\S_RX_OUT_BUFFER_reg[27]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_OUT_BUFFER,
      D => p_0_out(28),
      Q => \^raw_value\(27),
      R => RSTP
    );
\S_RX_OUT_BUFFER_reg[28]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_OUT_BUFFER,
      D => p_0_out(29),
      Q => \^raw_value\(28),
      R => RSTP
    );
\S_RX_OUT_BUFFER_reg[29]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_OUT_BUFFER,
      D => p_0_out(30),
      Q => \^raw_value\(29),
      R => RSTP
    );
\S_RX_OUT_BUFFER_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_OUT_BUFFER,
      D => p_0_out(3),
      Q => \^raw_value\(2),
      R => RSTP
    );
\S_RX_OUT_BUFFER_reg[30]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_OUT_BUFFER,
      D => p_0_out(31),
      Q => \^raw_value\(30),
      R => RSTP
    );
\S_RX_OUT_BUFFER_reg[31]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_OUT_BUFFER,
      D => \S_RX_BUFFER_reg_n_0_[31]\,
      Q => \^raw_value\(31),
      R => RSTP
    );
\S_RX_OUT_BUFFER_reg[32]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_OUT_BUFFER,
      D => p_0_out(33),
      Q => \^raw_value\(32),
      R => RSTP
    );
\S_RX_OUT_BUFFER_reg[33]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_OUT_BUFFER,
      D => p_0_out(34),
      Q => \^raw_value\(33),
      R => RSTP
    );
\S_RX_OUT_BUFFER_reg[34]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_OUT_BUFFER,
      D => p_0_out(35),
      Q => \^raw_value\(34),
      R => RSTP
    );
\S_RX_OUT_BUFFER_reg[35]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_OUT_BUFFER,
      D => p_0_out(36),
      Q => \^raw_value\(35),
      R => RSTP
    );
\S_RX_OUT_BUFFER_reg[36]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_OUT_BUFFER,
      D => p_0_out(37),
      Q => \^raw_value\(36),
      R => RSTP
    );
\S_RX_OUT_BUFFER_reg[37]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_OUT_BUFFER,
      D => p_0_out(38),
      Q => \^raw_value\(37),
      R => RSTP
    );
\S_RX_OUT_BUFFER_reg[38]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_OUT_BUFFER,
      D => p_0_out(39),
      Q => \^raw_value\(38),
      R => RSTP
    );
\S_RX_OUT_BUFFER_reg[39]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_OUT_BUFFER,
      D => p_0_out(40),
      Q => \^raw_value\(39),
      R => RSTP
    );
\S_RX_OUT_BUFFER_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_OUT_BUFFER,
      D => p_0_out(4),
      Q => \^raw_value\(3),
      R => RSTP
    );
\S_RX_OUT_BUFFER_reg[40]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_OUT_BUFFER,
      D => p_0_out(41),
      Q => \^raw_value\(40),
      R => RSTP
    );
\S_RX_OUT_BUFFER_reg[41]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_OUT_BUFFER,
      D => p_0_out(42),
      Q => \^raw_value\(41),
      R => RSTP
    );
\S_RX_OUT_BUFFER_reg[42]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_OUT_BUFFER,
      D => p_0_out(43),
      Q => \^raw_value\(42),
      R => RSTP
    );
\S_RX_OUT_BUFFER_reg[43]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_OUT_BUFFER,
      D => p_0_out(44),
      Q => \^raw_value\(43),
      R => RSTP
    );
\S_RX_OUT_BUFFER_reg[44]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_OUT_BUFFER,
      D => p_0_out(45),
      Q => \^raw_value\(44),
      R => RSTP
    );
\S_RX_OUT_BUFFER_reg[45]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_OUT_BUFFER,
      D => p_0_out(46),
      Q => \^raw_value\(45),
      R => RSTP
    );
\S_RX_OUT_BUFFER_reg[46]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_OUT_BUFFER,
      D => p_0_out(47),
      Q => \^raw_value\(46),
      R => RSTP
    );
\S_RX_OUT_BUFFER_reg[47]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_OUT_BUFFER,
      D => \S_RX_BUFFER_reg_n_0_[47]\,
      Q => \^raw_value\(47),
      R => RSTP
    );
\S_RX_OUT_BUFFER_reg[48]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_OUT_BUFFER,
      D => p_0_out(49),
      Q => \^raw_value\(48),
      R => RSTP
    );
\S_RX_OUT_BUFFER_reg[49]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_OUT_BUFFER,
      D => p_0_out(50),
      Q => \^raw_value\(49),
      R => RSTP
    );
\S_RX_OUT_BUFFER_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_OUT_BUFFER,
      D => p_0_out(5),
      Q => \^raw_value\(4),
      R => RSTP
    );
\S_RX_OUT_BUFFER_reg[50]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_OUT_BUFFER,
      D => p_0_out(51),
      Q => \^raw_value\(50),
      R => RSTP
    );
\S_RX_OUT_BUFFER_reg[51]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_OUT_BUFFER,
      D => p_0_out(52),
      Q => \^raw_value\(51),
      R => RSTP
    );
\S_RX_OUT_BUFFER_reg[52]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_OUT_BUFFER,
      D => p_0_out(53),
      Q => \^raw_value\(52),
      R => RSTP
    );
\S_RX_OUT_BUFFER_reg[53]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_OUT_BUFFER,
      D => p_0_out(54),
      Q => \^raw_value\(53),
      R => RSTP
    );
\S_RX_OUT_BUFFER_reg[54]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_OUT_BUFFER,
      D => p_0_out(55),
      Q => \^raw_value\(54),
      R => RSTP
    );
\S_RX_OUT_BUFFER_reg[55]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_OUT_BUFFER,
      D => p_0_out(56),
      Q => \^raw_value\(55),
      R => RSTP
    );
\S_RX_OUT_BUFFER_reg[56]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_OUT_BUFFER,
      D => p_0_out(57),
      Q => \^raw_value\(56),
      R => RSTP
    );
\S_RX_OUT_BUFFER_reg[57]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_OUT_BUFFER,
      D => p_0_out(58),
      Q => \^raw_value\(57),
      R => RSTP
    );
\S_RX_OUT_BUFFER_reg[58]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_OUT_BUFFER,
      D => p_0_out(59),
      Q => \^raw_value\(58),
      R => RSTP
    );
\S_RX_OUT_BUFFER_reg[59]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_OUT_BUFFER,
      D => p_0_out(60),
      Q => \^raw_value\(59),
      R => RSTP
    );
\S_RX_OUT_BUFFER_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_OUT_BUFFER,
      D => p_0_out(6),
      Q => \^raw_value\(5),
      R => RSTP
    );
\S_RX_OUT_BUFFER_reg[60]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_OUT_BUFFER,
      D => p_0_out(61),
      Q => \^raw_value\(60),
      R => RSTP
    );
\S_RX_OUT_BUFFER_reg[61]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_OUT_BUFFER,
      D => p_0_out(62),
      Q => \^raw_value\(61),
      R => RSTP
    );
\S_RX_OUT_BUFFER_reg[62]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_OUT_BUFFER,
      D => p_0_out(63),
      Q => \^raw_value\(62),
      R => RSTP
    );
\S_RX_OUT_BUFFER_reg[63]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_OUT_BUFFER,
      D => \S_RX_BUFFER_reg_n_0_[63]\,
      Q => \^raw_value\(63),
      R => RSTP
    );
\S_RX_OUT_BUFFER_reg[64]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_OUT_BUFFER,
      D => p_0_out(65),
      Q => \^raw_value\(64),
      R => RSTP
    );
\S_RX_OUT_BUFFER_reg[65]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_OUT_BUFFER,
      D => p_0_out(66),
      Q => \^raw_value\(65),
      R => RSTP
    );
\S_RX_OUT_BUFFER_reg[66]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_OUT_BUFFER,
      D => p_0_out(67),
      Q => \^raw_value\(66),
      R => RSTP
    );
\S_RX_OUT_BUFFER_reg[67]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_OUT_BUFFER,
      D => p_0_out(68),
      Q => \^raw_value\(67),
      R => RSTP
    );
\S_RX_OUT_BUFFER_reg[68]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_OUT_BUFFER,
      D => p_0_out(69),
      Q => \^raw_value\(68),
      R => RSTP
    );
\S_RX_OUT_BUFFER_reg[69]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_OUT_BUFFER,
      D => p_0_out(70),
      Q => \^raw_value\(69),
      R => RSTP
    );
\S_RX_OUT_BUFFER_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_OUT_BUFFER,
      D => p_0_out(7),
      Q => \^raw_value\(6),
      R => RSTP
    );
\S_RX_OUT_BUFFER_reg[70]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_OUT_BUFFER,
      D => p_0_out(71),
      Q => \^raw_value\(70),
      R => RSTP
    );
\S_RX_OUT_BUFFER_reg[71]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_OUT_BUFFER,
      D => p_0_out(72),
      Q => \^raw_value\(71),
      R => RSTP
    );
\S_RX_OUT_BUFFER_reg[72]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_OUT_BUFFER,
      D => p_0_out(73),
      Q => \^raw_value\(72),
      R => RSTP
    );
\S_RX_OUT_BUFFER_reg[73]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_OUT_BUFFER,
      D => p_0_out(74),
      Q => \^raw_value\(73),
      R => RSTP
    );
\S_RX_OUT_BUFFER_reg[74]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_OUT_BUFFER,
      D => p_0_out(75),
      Q => \^raw_value\(74),
      R => RSTP
    );
\S_RX_OUT_BUFFER_reg[75]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_OUT_BUFFER,
      D => p_0_out(76),
      Q => \^raw_value\(75),
      R => RSTP
    );
\S_RX_OUT_BUFFER_reg[76]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_OUT_BUFFER,
      D => p_0_out(77),
      Q => \^raw_value\(76),
      R => RSTP
    );
\S_RX_OUT_BUFFER_reg[77]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_OUT_BUFFER,
      D => p_0_out(78),
      Q => \^raw_value\(77),
      R => RSTP
    );
\S_RX_OUT_BUFFER_reg[78]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_OUT_BUFFER,
      D => p_0_out(79),
      Q => \^raw_value\(78),
      R => RSTP
    );
\S_RX_OUT_BUFFER_reg[79]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_OUT_BUFFER,
      D => \S_RX_BUFFER_reg_n_0_[79]\,
      Q => \^raw_value\(79),
      R => RSTP
    );
\S_RX_OUT_BUFFER_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_OUT_BUFFER,
      D => p_0_out(8),
      Q => \^raw_value\(7),
      R => RSTP
    );
\S_RX_OUT_BUFFER_reg[80]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_OUT_BUFFER,
      D => p_0_out(81),
      Q => \^raw_value\(80),
      R => RSTP
    );
\S_RX_OUT_BUFFER_reg[81]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_OUT_BUFFER,
      D => p_0_out(82),
      Q => \^raw_value\(81),
      R => RSTP
    );
\S_RX_OUT_BUFFER_reg[82]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_OUT_BUFFER,
      D => p_0_out(83),
      Q => \^raw_value\(82),
      R => RSTP
    );
\S_RX_OUT_BUFFER_reg[83]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_OUT_BUFFER,
      D => p_0_out(84),
      Q => \^raw_value\(83),
      R => RSTP
    );
\S_RX_OUT_BUFFER_reg[84]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_OUT_BUFFER,
      D => p_0_out(85),
      Q => \^raw_value\(84),
      R => RSTP
    );
\S_RX_OUT_BUFFER_reg[85]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_OUT_BUFFER,
      D => p_0_out(86),
      Q => \^raw_value\(85),
      R => RSTP
    );
\S_RX_OUT_BUFFER_reg[86]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_OUT_BUFFER,
      D => p_0_out(87),
      Q => \^raw_value\(86),
      R => RSTP
    );
\S_RX_OUT_BUFFER_reg[87]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_OUT_BUFFER,
      D => p_0_out(88),
      Q => \^raw_value\(87),
      R => RSTP
    );
\S_RX_OUT_BUFFER_reg[88]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_OUT_BUFFER,
      D => p_0_out(89),
      Q => \^raw_value\(88),
      R => RSTP
    );
\S_RX_OUT_BUFFER_reg[89]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_OUT_BUFFER,
      D => p_0_out(90),
      Q => \^raw_value\(89),
      R => RSTP
    );
\S_RX_OUT_BUFFER_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_OUT_BUFFER,
      D => p_0_out(9),
      Q => \^raw_value\(8),
      R => RSTP
    );
\S_RX_OUT_BUFFER_reg[90]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_OUT_BUFFER,
      D => p_0_out(91),
      Q => \^raw_value\(90),
      R => RSTP
    );
\S_RX_OUT_BUFFER_reg[91]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_OUT_BUFFER,
      D => p_0_out(92),
      Q => \^raw_value\(91),
      R => RSTP
    );
\S_RX_OUT_BUFFER_reg[92]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_OUT_BUFFER,
      D => p_0_out(93),
      Q => \^raw_value\(92),
      R => RSTP
    );
\S_RX_OUT_BUFFER_reg[93]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_OUT_BUFFER,
      D => p_0_out(94),
      Q => \^raw_value\(93),
      R => RSTP
    );
\S_RX_OUT_BUFFER_reg[94]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_OUT_BUFFER,
      D => p_0_out(95),
      Q => \^raw_value\(94),
      R => RSTP
    );
\S_RX_OUT_BUFFER_reg[95]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_OUT_BUFFER,
      D => \S_RX_BUFFER_reg_n_0_[95]\,
      Q => \^raw_value\(95),
      R => RSTP
    );
\S_RX_OUT_BUFFER_reg[96]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_OUT_BUFFER,
      D => p_0_out(97),
      Q => \^raw_value\(96),
      R => RSTP
    );
\S_RX_OUT_BUFFER_reg[97]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_OUT_BUFFER,
      D => p_0_out(98),
      Q => \^raw_value\(97),
      R => RSTP
    );
\S_RX_OUT_BUFFER_reg[98]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_OUT_BUFFER,
      D => p_0_out(99),
      Q => \^raw_value\(98),
      R => RSTP
    );
\S_RX_OUT_BUFFER_reg[99]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_OUT_BUFFER,
      D => p_0_out(100),
      Q => \^raw_value\(99),
      R => RSTP
    );
\S_RX_OUT_BUFFER_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_RX_OUT_BUFFER,
      D => p_0_out(10),
      Q => \^raw_value\(9),
      R => RSTP
    );
\S_SAMPLE_TIME_COUNTER[30]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"00040004FF070307"
    )
        port map (
      I0 => \S_SAMPLE_TIME_COUNTER_reg[0]\,
      I1 => Q(0),
      I2 => Q(1),
      I3 => \S_SAMPLE_TIME_COUNTER_reg[0]_0\,
      I4 => \^ss_n\(0),
      I5 => \S_SAMPLE_TIME_COUNTER_reg[0]_1\,
      O => E(0)
    );
S_SCLK_i_1: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FEFFFE00"
    )
        port map (
      I0 => S_SCLK_i_2_n_0,
      I1 => S_SCLK_i_3_n_0,
      I2 => S_SCLK_i_4_n_0,
      I3 => S_SCLK_i_5_n_0,
      I4 => \^s_sclk\,
      O => S_SCLK_i_1_n_0
    );
S_SCLK_i_2: unisim.vcomponents.LUT6
    generic map(
      INIT => X"00AA0CAA00AA00AA"
    )
        port map (
      I0 => CPOL,
      I1 => \S_DEL_CLK[16]_i_3_n_0\,
      I2 => \^s_sclk\,
      I3 => S_AXI_ARESETN,
      I4 => curstate(2),
      I5 => curstate(1),
      O => S_SCLK_i_2_n_0
    );
S_SCLK_i_3: unisim.vcomponents.LUT6
    generic map(
      INIT => X"F222222200000000"
    )
        port map (
      I0 => S_SCLK_i_6_n_0,
      I1 => S_CPOL_reg_n_0,
      I2 => S_SCLK_i_7_n_0,
      I3 => S_SCLK_reg_0,
      I4 => SCLK_IN,
      I5 => S_AXI_ARESETN,
      O => S_SCLK_i_3_n_0
    );
S_SCLK_i_4: unisim.vcomponents.LUT6
    generic map(
      INIT => X"8888888880888080"
    )
        port map (
      I0 => S_AXI_ARESETN,
      I1 => S_CPOL_reg_n_0,
      I2 => S_SCLK_i_8_n_0,
      I3 => S_SCLK_reg_0,
      I4 => \S_DEL_COUNT[8]_i_3_n_0\,
      I5 => \curstate[0]_i_3_n_0\,
      O => S_SCLK_i_4_n_0
    );
S_SCLK_i_5: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFFF2203"
    )
        port map (
      I0 => SS_OUT_N_i_2_n_0,
      I1 => curstate(1),
      I2 => curstate(2),
      I3 => curstate(0),
      I4 => S_SCLK_i_9_n_0,
      O => S_SCLK_i_5_n_0
    );
S_SCLK_i_6: unisim.vcomponents.LUT4
    generic map(
      INIT => X"0200"
    )
        port map (
      I0 => curstate(0),
      I1 => curstate(1),
      I2 => curstate(2),
      I3 => SS_OUT_N_i_2_n_0,
      O => S_SCLK_i_6_n_0
    );
S_SCLK_i_7: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FAAAAABB"
    )
        port map (
      I0 => curstate(2),
      I1 => \S_BIT_COUNT_reg[0]_0\,
      I2 => \S_RX_OUT_BUFFER[127]_i_3_n_0\,
      I3 => curstate(0),
      I4 => curstate(1),
      O => S_SCLK_i_7_n_0
    );
S_SCLK_i_8: unisim.vcomponents.LUT4
    generic map(
      INIT => X"0100"
    )
        port map (
      I0 => curstate(0),
      I1 => curstate(1),
      I2 => curstate(2),
      I3 => \S_BIT_COUNT_reg[0]_0\,
      O => S_SCLK_i_8_n_0
    );
S_SCLK_i_9: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFF5D5D5F5F5D5D5"
    )
        port map (
      I0 => S_AXI_ARESETN,
      I1 => curstate(0),
      I2 => curstate(2),
      I3 => \S_DEL_CLK[16]_i_3_n_0\,
      I4 => curstate(1),
      I5 => nxtstate1,
      O => S_SCLK_i_9_n_0
    );
S_SCLK_reg: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => '1',
      D => S_SCLK_i_1_n_0,
      Q => \^s_sclk\,
      R => '0'
    );
\S_SPI_BUSY_PIPE[0]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"8A"
    )
        port map (
      I0 => \^s_spi_busy\,
      I1 => Q(1),
      I2 => Q(0),
      O => D(0)
    );
\curstate[0]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"FE"
    )
        port map (
      I0 => \curstate[0]_i_2_n_0\,
      I1 => \curstate[0]_i_3_n_0\,
      I2 => \curstate[0]_i_4_n_0\,
      O => nxtstate(0)
    );
\curstate[0]_i_2\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"00000A0C"
    )
        port map (
      I0 => nxtstate1,
      I1 => \S_BIT_COUNT_reg[0]_0\,
      I2 => curstate(2),
      I3 => curstate(1),
      I4 => curstate(0),
      O => \curstate[0]_i_2_n_0\
    );
\curstate[0]_i_3\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"00020000"
    )
        port map (
      I0 => \curstate[2]_i_2_n_0\,
      I1 => S_DEL_COUNT(8),
      I2 => curstate(2),
      I3 => curstate(1),
      I4 => curstate(0),
      O => \curstate[0]_i_3_n_0\
    );
\curstate[0]_i_4\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0011000F00000000"
    )
        port map (
      I0 => \S_RX_OUT_BUFFER[127]_i_3_n_0\,
      I1 => nxtstate1,
      I2 => S_CPHA_reg_n_0,
      I3 => curstate(2),
      I4 => curstate(1),
      I5 => curstate(0),
      O => \curstate[0]_i_4_n_0\
    );
\curstate[2]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFFFFFF00000020"
    )
        port map (
      I0 => \curstate[2]_i_2_n_0\,
      I1 => S_DEL_COUNT(8),
      I2 => curstate(2),
      I3 => curstate(1),
      I4 => curstate(0),
      I5 => S_RX_OUT_BUFFER,
      O => nxtstate(2)
    );
\curstate[2]_i_2\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"FE"
    )
        port map (
      I0 => S_DEL_COUNT(6),
      I1 => \S_DEL_COUNT[7]_i_3_n_0\,
      I2 => S_DEL_COUNT(7),
      O => \curstate[2]_i_2_n_0\
    );
\curstate_reg[0]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s00_axi_aclk,
      CE => '1',
      D => nxtstate(0),
      Q => curstate(0),
      R => RSTP
    );
\curstate_reg[1]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s00_axi_aclk,
      CE => '1',
      D => nxtstate(1),
      Q => curstate(1),
      R => RSTP
    );
\curstate_reg[2]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s00_axi_aclk,
      CE => '1',
      D => nxtstate(2),
      Q => curstate(2),
      R => RSTP
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity zusys_A3_ADC_LTC2311_0_ADC_CONTROLLER is
  port (
    S_SCLK : out STD_LOGIC;
    SS_N : out STD_LOGIC_VECTOR ( 0 to 0 );
    S_SPI_BUSY : out STD_LOGIC;
    SI_VALID : out STD_LOGIC_VECTOR ( 0 to 0 );
    \S_ENABLE_reg[0]\ : out STD_LOGIC;
    S_DUMMY_SAMPLE : out STD_LOGIC;
    RAW_VALID : out STD_LOGIC_VECTOR ( 0 to 0 );
    BUSY : out STD_LOGIC;
    S_MANUAL_reg_0 : out STD_LOGIC;
    S_SPI_ENABLE_reg_0 : out STD_LOGIC;
    \S_ENABLE_reg[0]_0\ : out STD_LOGIC;
    Q : out STD_LOGIC_VECTOR ( 1 downto 0 );
    \S_SAMPLE_COUNTER_reg[0]_0\ : out STD_LOGIC;
    \S_ENABLE_reg[0]_1\ : out STD_LOGIC;
    E : out STD_LOGIC_VECTOR ( 0 to 0 );
    S : out STD_LOGIC_VECTOR ( 7 downto 0 );
    \S_SAMPLE_COUNTER_reg[16]_0\ : out STD_LOGIC_VECTOR ( 7 downto 0 );
    \S_SAMPLE_COUNTER_reg[24]_0\ : out STD_LOGIC_VECTOR ( 7 downto 0 );
    \S_SAMPLE_COUNTER_reg[31]_0\ : out STD_LOGIC_VECTOR ( 6 downto 0 );
    RAW_VALUE : out STD_LOGIC_VECTOR ( 127 downto 0 );
    SI_VALUE : out STD_LOGIC_VECTOR ( 279 downto 0 );
    CPHA : in STD_LOGIC;
    s00_axi_aclk : in STD_LOGIC;
    CPOL : in STD_LOGIC;
    RSTP : in STD_LOGIC;
    S_DUMMY_SAMPLE_reg_0 : in STD_LOGIC;
    RAW_VALID_reg_0 : in STD_LOGIC;
    BUSY_reg_0 : in STD_LOGIC;
    S_MANUAL_reg_1 : in STD_LOGIC;
    S_SPI_ENABLE_reg_1 : in STD_LOGIC;
    S_CPOL_reg : in STD_LOGIC_VECTOR ( 0 to 0 );
    s00_axi_aresetn : in STD_LOGIC;
    S_AXI_ARESETN : in STD_LOGIC;
    \S_DEL_COUNT_reg[7]\ : in STD_LOGIC_VECTOR ( 31 downto 0 );
    SCLK_IN : in STD_LOGIC;
    SS_IN_N : in STD_LOGIC;
    ENABLE : in STD_LOGIC;
    SET_SAMPLES : in STD_LOGIC;
    SET_CONVERSION : in STD_LOGIC;
    SET_OFFSET : in STD_LOGIC;
    D : in STD_LOGIC_VECTOR ( 7 downto 0 );
    \S_SAMPLE_TIME_reg[30]_0\ : in STD_LOGIC_VECTOR ( 0 to 0 );
    \S_SAMPLE_TIME_reg[30]_1\ : in STD_LOGIC_VECTOR ( 30 downto 0 );
    \S_CONVERSION_reg[126]_0\ : in STD_LOGIC_VECTOR ( 7 downto 0 );
    \S_OFFSET_reg[112]_0\ : in STD_LOGIC_VECTOR ( 7 downto 0 )
  );
  attribute ORIG_REF_NAME : string;
  attribute ORIG_REF_NAME of zusys_A3_ADC_LTC2311_0_ADC_CONTROLLER : entity is "ADC_CONTROLLER";
end zusys_A3_ADC_LTC2311_0_ADC_CONTROLLER;

architecture STRUCTURE of zusys_A3_ADC_LTC2311_0_ADC_CONTROLLER is
  signal B : STD_LOGIC_VECTOR ( 3 downto 2 );
  signal CEB2 : STD_LOGIC;
  signal \^e\ : STD_LOGIC_VECTOR ( 0 to 0 );
  signal \^q\ : STD_LOGIC_VECTOR ( 1 downto 0 );
  signal \^s\ : STD_LOGIC_VECTOR ( 7 downto 0 );
  signal SI_VALID_i_1_n_0 : STD_LOGIC;
  signal SI_VALID_i_53_n_0 : STD_LOGIC;
  signal SI_VALID_i_54_n_0 : STD_LOGIC;
  signal SI_VALID_i_55_n_0 : STD_LOGIC;
  signal SI_VALID_i_56_n_0 : STD_LOGIC;
  signal SI_VALID_i_57_n_0 : STD_LOGIC;
  signal SI_VALID_i_58_n_0 : STD_LOGIC;
  signal SI_VALID_i_59_n_0 : STD_LOGIC;
  signal SI_VALID_i_60_n_0 : STD_LOGIC;
  signal SI_VALID_i_61_n_0 : STD_LOGIC;
  signal SI_VALID_i_62_n_0 : STD_LOGIC;
  signal SI_VALID_i_63_n_0 : STD_LOGIC;
  signal SI_VALID_i_64_n_0 : STD_LOGIC;
  signal SI_VALID_i_65_n_0 : STD_LOGIC;
  signal SI_VALID_i_66_n_0 : STD_LOGIC;
  signal SI_VALID_i_67_n_0 : STD_LOGIC;
  signal SI_VALID_i_68_n_0 : STD_LOGIC;
  signal SI_VALID_i_69_n_0 : STD_LOGIC;
  signal SI_VALID_i_70_n_0 : STD_LOGIC;
  signal SI_VALID_i_71_n_0 : STD_LOGIC;
  signal SI_VALID_i_72_n_0 : STD_LOGIC;
  signal SI_VALID_i_73_n_0 : STD_LOGIC;
  signal SI_VALID_i_74_n_0 : STD_LOGIC;
  signal SI_VALID_i_75_n_0 : STD_LOGIC;
  signal SI_VALID_i_76_n_0 : STD_LOGIC;
  signal SI_VALID_i_77_n_0 : STD_LOGIC;
  signal SI_VALID_i_78_n_0 : STD_LOGIC;
  signal SI_VALID_i_79_n_0 : STD_LOGIC;
  signal SI_VALID_i_80_n_0 : STD_LOGIC;
  signal SI_VALID_i_81_n_0 : STD_LOGIC;
  signal SI_VALID_i_82_n_0 : STD_LOGIC;
  signal SI_VALID_reg_i_49_n_1 : STD_LOGIC;
  signal SI_VALID_reg_i_49_n_3 : STD_LOGIC;
  signal SI_VALID_reg_i_49_n_4 : STD_LOGIC;
  signal SI_VALID_reg_i_49_n_5 : STD_LOGIC;
  signal SI_VALID_reg_i_49_n_6 : STD_LOGIC;
  signal SI_VALID_reg_i_49_n_7 : STD_LOGIC;
  signal SI_VALID_reg_i_50_n_0 : STD_LOGIC;
  signal SI_VALID_reg_i_50_n_1 : STD_LOGIC;
  signal SI_VALID_reg_i_50_n_2 : STD_LOGIC;
  signal SI_VALID_reg_i_50_n_3 : STD_LOGIC;
  signal SI_VALID_reg_i_50_n_4 : STD_LOGIC;
  signal SI_VALID_reg_i_50_n_5 : STD_LOGIC;
  signal SI_VALID_reg_i_50_n_6 : STD_LOGIC;
  signal SI_VALID_reg_i_50_n_7 : STD_LOGIC;
  signal SI_VALID_reg_i_51_n_0 : STD_LOGIC;
  signal SI_VALID_reg_i_51_n_1 : STD_LOGIC;
  signal SI_VALID_reg_i_51_n_2 : STD_LOGIC;
  signal SI_VALID_reg_i_51_n_3 : STD_LOGIC;
  signal SI_VALID_reg_i_51_n_4 : STD_LOGIC;
  signal SI_VALID_reg_i_51_n_5 : STD_LOGIC;
  signal SI_VALID_reg_i_51_n_6 : STD_LOGIC;
  signal SI_VALID_reg_i_51_n_7 : STD_LOGIC;
  signal SI_VALID_reg_i_52_n_0 : STD_LOGIC;
  signal SI_VALID_reg_i_52_n_1 : STD_LOGIC;
  signal SI_VALID_reg_i_52_n_2 : STD_LOGIC;
  signal SI_VALID_reg_i_52_n_3 : STD_LOGIC;
  signal SI_VALID_reg_i_52_n_4 : STD_LOGIC;
  signal SI_VALID_reg_i_52_n_5 : STD_LOGIC;
  signal SI_VALID_reg_i_52_n_6 : STD_LOGIC;
  signal SI_VALID_reg_i_52_n_7 : STD_LOGIC;
  signal SI_VALUE0 : STD_LOGIC_VECTOR ( 279 downto 0 );
  signal \SI_VALUE[180]_i_3_n_0\ : STD_LOGIC;
  signal \SI_VALUE[270]_i_3_n_0\ : STD_LOGIC;
  signal \SI_VALUE[273]_i_2_n_0\ : STD_LOGIC;
  signal \SI_VALUE[273]_i_4_n_0\ : STD_LOGIC;
  signal \SI_VALUE[279]_i_3_n_0\ : STD_LOGIC;
  signal \SI_VALUE[279]_i_6_n_0\ : STD_LOGIC;
  signal \SI_VALUE[279]_i_7_n_0\ : STD_LOGIC;
  signal \SI_VALUE[34]_i_1_n_0\ : STD_LOGIC;
  signal S_CE_CONVERSION : STD_LOGIC;
  signal S_CHANNEL_COUNTER : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal \S_CHANNEL_COUNTER[0]_i_1_n_0\ : STD_LOGIC;
  signal \S_CHANNEL_COUNTER[1]_i_1_n_0\ : STD_LOGIC;
  signal \S_CHANNEL_COUNTER[2]_i_1_n_0\ : STD_LOGIC;
  signal \S_CHANNEL_COUNTER[3]_i_1_n_0\ : STD_LOGIC;
  signal \S_CHANNEL_COUNTER[3]_i_2_n_0\ : STD_LOGIC;
  signal \S_CONVERSION_reg_n_0_[0]\ : STD_LOGIC;
  signal \S_CONVERSION_reg_n_0_[10]\ : STD_LOGIC;
  signal \S_CONVERSION_reg_n_0_[11]\ : STD_LOGIC;
  signal \S_CONVERSION_reg_n_0_[12]\ : STD_LOGIC;
  signal \S_CONVERSION_reg_n_0_[13]\ : STD_LOGIC;
  signal \S_CONVERSION_reg_n_0_[14]\ : STD_LOGIC;
  signal \S_CONVERSION_reg_n_0_[15]\ : STD_LOGIC;
  signal \S_CONVERSION_reg_n_0_[16]\ : STD_LOGIC;
  signal \S_CONVERSION_reg_n_0_[17]\ : STD_LOGIC;
  signal \S_CONVERSION_reg_n_0_[1]\ : STD_LOGIC;
  signal \S_CONVERSION_reg_n_0_[2]\ : STD_LOGIC;
  signal \S_CONVERSION_reg_n_0_[3]\ : STD_LOGIC;
  signal \S_CONVERSION_reg_n_0_[4]\ : STD_LOGIC;
  signal \S_CONVERSION_reg_n_0_[5]\ : STD_LOGIC;
  signal \S_CONVERSION_reg_n_0_[6]\ : STD_LOGIC;
  signal \S_CONVERSION_reg_n_0_[7]\ : STD_LOGIC;
  signal \S_CONVERSION_reg_n_0_[8]\ : STD_LOGIC;
  signal \S_CONVERSION_reg_n_0_[9]\ : STD_LOGIC;
  signal S_CONV_COUNTER : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal \S_CONV_COUNTER[0]_i_1_n_0\ : STD_LOGIC;
  signal \S_CONV_COUNTER[1]_i_1_n_0\ : STD_LOGIC;
  signal \S_CONV_COUNTER[2]_i_1_n_0\ : STD_LOGIC;
  signal \S_CONV_COUNTER[3]_i_1_n_0\ : STD_LOGIC;
  signal \S_CONV_COUNTER[3]_i_2_n_0\ : STD_LOGIC;
  signal \^s_dummy_sample\ : STD_LOGIC;
  signal \^s_enable_reg[0]\ : STD_LOGIC;
  signal \^s_enable_reg[0]_0\ : STD_LOGIC;
  signal \^s_enable_reg[0]_1\ : STD_LOGIC;
  signal \^s_manual_reg_0\ : STD_LOGIC;
  signal S_OFFSET : STD_LOGIC_VECTOR ( 127 downto 0 );
  signal S_OFFSET_S_C : STD_LOGIC;
  signal \S_OFFSET_S_C[0]_i_1_n_0\ : STD_LOGIC;
  signal \S_OFFSET_S_C[0]_i_2_n_0\ : STD_LOGIC;
  signal \S_OFFSET_S_C[0]_i_3_n_0\ : STD_LOGIC;
  signal \S_OFFSET_S_C[10]_i_1_n_0\ : STD_LOGIC;
  signal \S_OFFSET_S_C[10]_i_2_n_0\ : STD_LOGIC;
  signal \S_OFFSET_S_C[10]_i_3_n_0\ : STD_LOGIC;
  signal \S_OFFSET_S_C[11]_i_1_n_0\ : STD_LOGIC;
  signal \S_OFFSET_S_C[11]_i_2_n_0\ : STD_LOGIC;
  signal \S_OFFSET_S_C[11]_i_3_n_0\ : STD_LOGIC;
  signal \S_OFFSET_S_C[12]_i_1_n_0\ : STD_LOGIC;
  signal \S_OFFSET_S_C[12]_i_2_n_0\ : STD_LOGIC;
  signal \S_OFFSET_S_C[12]_i_3_n_0\ : STD_LOGIC;
  signal \S_OFFSET_S_C[13]_i_1_n_0\ : STD_LOGIC;
  signal \S_OFFSET_S_C[13]_i_2_n_0\ : STD_LOGIC;
  signal \S_OFFSET_S_C[13]_i_3_n_0\ : STD_LOGIC;
  signal \S_OFFSET_S_C[14]_i_1_n_0\ : STD_LOGIC;
  signal \S_OFFSET_S_C[14]_i_2_n_0\ : STD_LOGIC;
  signal \S_OFFSET_S_C[14]_i_3_n_0\ : STD_LOGIC;
  signal \S_OFFSET_S_C[15]_i_1_n_0\ : STD_LOGIC;
  signal \S_OFFSET_S_C[15]_i_2_n_0\ : STD_LOGIC;
  signal \S_OFFSET_S_C[15]_i_3_n_0\ : STD_LOGIC;
  signal \S_OFFSET_S_C[1]_i_1_n_0\ : STD_LOGIC;
  signal \S_OFFSET_S_C[1]_i_2_n_0\ : STD_LOGIC;
  signal \S_OFFSET_S_C[1]_i_3_n_0\ : STD_LOGIC;
  signal \S_OFFSET_S_C[2]_i_1_n_0\ : STD_LOGIC;
  signal \S_OFFSET_S_C[2]_i_2_n_0\ : STD_LOGIC;
  signal \S_OFFSET_S_C[2]_i_3_n_0\ : STD_LOGIC;
  signal \S_OFFSET_S_C[3]_i_1_n_0\ : STD_LOGIC;
  signal \S_OFFSET_S_C[3]_i_2_n_0\ : STD_LOGIC;
  signal \S_OFFSET_S_C[3]_i_3_n_0\ : STD_LOGIC;
  signal \S_OFFSET_S_C[4]_i_1_n_0\ : STD_LOGIC;
  signal \S_OFFSET_S_C[4]_i_2_n_0\ : STD_LOGIC;
  signal \S_OFFSET_S_C[4]_i_3_n_0\ : STD_LOGIC;
  signal \S_OFFSET_S_C[5]_i_1_n_0\ : STD_LOGIC;
  signal \S_OFFSET_S_C[5]_i_2_n_0\ : STD_LOGIC;
  signal \S_OFFSET_S_C[5]_i_3_n_0\ : STD_LOGIC;
  signal \S_OFFSET_S_C[6]_i_1_n_0\ : STD_LOGIC;
  signal \S_OFFSET_S_C[6]_i_2_n_0\ : STD_LOGIC;
  signal \S_OFFSET_S_C[6]_i_3_n_0\ : STD_LOGIC;
  signal \S_OFFSET_S_C[7]_i_1_n_0\ : STD_LOGIC;
  signal \S_OFFSET_S_C[7]_i_2_n_0\ : STD_LOGIC;
  signal \S_OFFSET_S_C[7]_i_3_n_0\ : STD_LOGIC;
  signal \S_OFFSET_S_C[8]_i_1_n_0\ : STD_LOGIC;
  signal \S_OFFSET_S_C[8]_i_2_n_0\ : STD_LOGIC;
  signal \S_OFFSET_S_C[8]_i_3_n_0\ : STD_LOGIC;
  signal \S_OFFSET_S_C[9]_i_1_n_0\ : STD_LOGIC;
  signal \S_OFFSET_S_C[9]_i_2_n_0\ : STD_LOGIC;
  signal \S_OFFSET_S_C[9]_i_3_n_0\ : STD_LOGIC;
  signal \S_OFFSET_S_C_reg_n_0_[0]\ : STD_LOGIC;
  signal \S_OFFSET_S_C_reg_n_0_[10]\ : STD_LOGIC;
  signal \S_OFFSET_S_C_reg_n_0_[11]\ : STD_LOGIC;
  signal \S_OFFSET_S_C_reg_n_0_[12]\ : STD_LOGIC;
  signal \S_OFFSET_S_C_reg_n_0_[13]\ : STD_LOGIC;
  signal \S_OFFSET_S_C_reg_n_0_[14]\ : STD_LOGIC;
  signal \S_OFFSET_S_C_reg_n_0_[15]\ : STD_LOGIC;
  signal \S_OFFSET_S_C_reg_n_0_[1]\ : STD_LOGIC;
  signal \S_OFFSET_S_C_reg_n_0_[2]\ : STD_LOGIC;
  signal \S_OFFSET_S_C_reg_n_0_[3]\ : STD_LOGIC;
  signal \S_OFFSET_S_C_reg_n_0_[4]\ : STD_LOGIC;
  signal \S_OFFSET_S_C_reg_n_0_[5]\ : STD_LOGIC;
  signal \S_OFFSET_S_C_reg_n_0_[6]\ : STD_LOGIC;
  signal \S_OFFSET_S_C_reg_n_0_[7]\ : STD_LOGIC;
  signal \S_OFFSET_S_C_reg_n_0_[8]\ : STD_LOGIC;
  signal \S_OFFSET_S_C_reg_n_0_[9]\ : STD_LOGIC;
  signal S_RAW_VALUE_S_C : STD_LOGIC_VECTOR ( 15 downto 0 );
  signal \S_RAW_VALUE_S_C[15]_i_3_n_0\ : STD_LOGIC;
  signal S_RESULT_COUNTER : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal \S_RESULT_COUNTER[0]_i_1_n_0\ : STD_LOGIC;
  signal \S_RESULT_COUNTER[0]_rep_i_1_n_0\ : STD_LOGIC;
  signal \S_RESULT_COUNTER[1]_i_1_n_0\ : STD_LOGIC;
  signal \S_RESULT_COUNTER[1]_rep_i_1_n_0\ : STD_LOGIC;
  signal \S_RESULT_COUNTER[3]_i_3_n_0\ : STD_LOGIC;
  signal \S_RESULT_COUNTER_reg[0]_rep_n_0\ : STD_LOGIC;
  signal \S_RESULT_COUNTER_reg[1]_rep_n_0\ : STD_LOGIC;
  signal S_RESULT_S_C : STD_LOGIC_VECTOR ( 33 to 33 );
  signal S_SAMPLES : STD_LOGIC;
  signal \S_SAMPLES_reg_n_0_[0]\ : STD_LOGIC;
  signal \S_SAMPLES_reg_n_0_[10]\ : STD_LOGIC;
  signal \S_SAMPLES_reg_n_0_[11]\ : STD_LOGIC;
  signal \S_SAMPLES_reg_n_0_[12]\ : STD_LOGIC;
  signal \S_SAMPLES_reg_n_0_[13]\ : STD_LOGIC;
  signal \S_SAMPLES_reg_n_0_[14]\ : STD_LOGIC;
  signal \S_SAMPLES_reg_n_0_[15]\ : STD_LOGIC;
  signal \S_SAMPLES_reg_n_0_[16]\ : STD_LOGIC;
  signal \S_SAMPLES_reg_n_0_[17]\ : STD_LOGIC;
  signal \S_SAMPLES_reg_n_0_[18]\ : STD_LOGIC;
  signal \S_SAMPLES_reg_n_0_[19]\ : STD_LOGIC;
  signal \S_SAMPLES_reg_n_0_[1]\ : STD_LOGIC;
  signal \S_SAMPLES_reg_n_0_[20]\ : STD_LOGIC;
  signal \S_SAMPLES_reg_n_0_[21]\ : STD_LOGIC;
  signal \S_SAMPLES_reg_n_0_[22]\ : STD_LOGIC;
  signal \S_SAMPLES_reg_n_0_[23]\ : STD_LOGIC;
  signal \S_SAMPLES_reg_n_0_[24]\ : STD_LOGIC;
  signal \S_SAMPLES_reg_n_0_[25]\ : STD_LOGIC;
  signal \S_SAMPLES_reg_n_0_[26]\ : STD_LOGIC;
  signal \S_SAMPLES_reg_n_0_[27]\ : STD_LOGIC;
  signal \S_SAMPLES_reg_n_0_[28]\ : STD_LOGIC;
  signal \S_SAMPLES_reg_n_0_[29]\ : STD_LOGIC;
  signal \S_SAMPLES_reg_n_0_[2]\ : STD_LOGIC;
  signal \S_SAMPLES_reg_n_0_[30]\ : STD_LOGIC;
  signal \S_SAMPLES_reg_n_0_[3]\ : STD_LOGIC;
  signal \S_SAMPLES_reg_n_0_[4]\ : STD_LOGIC;
  signal \S_SAMPLES_reg_n_0_[5]\ : STD_LOGIC;
  signal \S_SAMPLES_reg_n_0_[6]\ : STD_LOGIC;
  signal \S_SAMPLES_reg_n_0_[7]\ : STD_LOGIC;
  signal \S_SAMPLES_reg_n_0_[8]\ : STD_LOGIC;
  signal \S_SAMPLES_reg_n_0_[9]\ : STD_LOGIC;
  signal S_SAMPLE_COUNTER : STD_LOGIC;
  signal \S_SAMPLE_COUNTER[0]_i_1_n_0\ : STD_LOGIC;
  signal \S_SAMPLE_COUNTER[10]_i_1_n_0\ : STD_LOGIC;
  signal \S_SAMPLE_COUNTER[11]_i_1_n_0\ : STD_LOGIC;
  signal \S_SAMPLE_COUNTER[12]_i_1_n_0\ : STD_LOGIC;
  signal \S_SAMPLE_COUNTER[13]_i_1_n_0\ : STD_LOGIC;
  signal \S_SAMPLE_COUNTER[14]_i_1_n_0\ : STD_LOGIC;
  signal \S_SAMPLE_COUNTER[15]_i_1_n_0\ : STD_LOGIC;
  signal \S_SAMPLE_COUNTER[16]_i_1_n_0\ : STD_LOGIC;
  signal \S_SAMPLE_COUNTER[17]_i_1_n_0\ : STD_LOGIC;
  signal \S_SAMPLE_COUNTER[18]_i_1_n_0\ : STD_LOGIC;
  signal \S_SAMPLE_COUNTER[19]_i_1_n_0\ : STD_LOGIC;
  signal \S_SAMPLE_COUNTER[1]_i_1_n_0\ : STD_LOGIC;
  signal \S_SAMPLE_COUNTER[20]_i_1_n_0\ : STD_LOGIC;
  signal \S_SAMPLE_COUNTER[21]_i_1_n_0\ : STD_LOGIC;
  signal \S_SAMPLE_COUNTER[22]_i_1_n_0\ : STD_LOGIC;
  signal \S_SAMPLE_COUNTER[23]_i_1_n_0\ : STD_LOGIC;
  signal \S_SAMPLE_COUNTER[24]_i_1_n_0\ : STD_LOGIC;
  signal \S_SAMPLE_COUNTER[25]_i_1_n_0\ : STD_LOGIC;
  signal \S_SAMPLE_COUNTER[26]_i_1_n_0\ : STD_LOGIC;
  signal \S_SAMPLE_COUNTER[27]_i_1_n_0\ : STD_LOGIC;
  signal \S_SAMPLE_COUNTER[28]_i_1_n_0\ : STD_LOGIC;
  signal \S_SAMPLE_COUNTER[29]_i_1_n_0\ : STD_LOGIC;
  signal \S_SAMPLE_COUNTER[2]_i_1_n_0\ : STD_LOGIC;
  signal \S_SAMPLE_COUNTER[30]_i_1_n_0\ : STD_LOGIC;
  signal \S_SAMPLE_COUNTER[31]_i_1_n_0\ : STD_LOGIC;
  signal \S_SAMPLE_COUNTER[31]_i_3_n_0\ : STD_LOGIC;
  signal \S_SAMPLE_COUNTER[3]_i_1_n_0\ : STD_LOGIC;
  signal \S_SAMPLE_COUNTER[4]_i_1_n_0\ : STD_LOGIC;
  signal \S_SAMPLE_COUNTER[5]_i_1_n_0\ : STD_LOGIC;
  signal \S_SAMPLE_COUNTER[6]_i_1_n_0\ : STD_LOGIC;
  signal \S_SAMPLE_COUNTER[7]_i_1_n_0\ : STD_LOGIC;
  signal \S_SAMPLE_COUNTER[8]_i_1_n_0\ : STD_LOGIC;
  signal \S_SAMPLE_COUNTER[9]_i_1_n_0\ : STD_LOGIC;
  signal \^s_sample_counter_reg[0]_0\ : STD_LOGIC;
  signal \^s_sample_counter_reg[16]_0\ : STD_LOGIC_VECTOR ( 7 downto 0 );
  signal \S_SAMPLE_COUNTER_reg[16]_i_2_n_0\ : STD_LOGIC;
  signal \S_SAMPLE_COUNTER_reg[16]_i_2_n_1\ : STD_LOGIC;
  signal \S_SAMPLE_COUNTER_reg[16]_i_2_n_2\ : STD_LOGIC;
  signal \S_SAMPLE_COUNTER_reg[16]_i_2_n_3\ : STD_LOGIC;
  signal \S_SAMPLE_COUNTER_reg[16]_i_2_n_4\ : STD_LOGIC;
  signal \S_SAMPLE_COUNTER_reg[16]_i_2_n_5\ : STD_LOGIC;
  signal \S_SAMPLE_COUNTER_reg[16]_i_2_n_6\ : STD_LOGIC;
  signal \S_SAMPLE_COUNTER_reg[16]_i_2_n_7\ : STD_LOGIC;
  signal \^s_sample_counter_reg[24]_0\ : STD_LOGIC_VECTOR ( 7 downto 0 );
  signal \S_SAMPLE_COUNTER_reg[24]_i_2_n_0\ : STD_LOGIC;
  signal \S_SAMPLE_COUNTER_reg[24]_i_2_n_1\ : STD_LOGIC;
  signal \S_SAMPLE_COUNTER_reg[24]_i_2_n_2\ : STD_LOGIC;
  signal \S_SAMPLE_COUNTER_reg[24]_i_2_n_3\ : STD_LOGIC;
  signal \S_SAMPLE_COUNTER_reg[24]_i_2_n_4\ : STD_LOGIC;
  signal \S_SAMPLE_COUNTER_reg[24]_i_2_n_5\ : STD_LOGIC;
  signal \S_SAMPLE_COUNTER_reg[24]_i_2_n_6\ : STD_LOGIC;
  signal \S_SAMPLE_COUNTER_reg[24]_i_2_n_7\ : STD_LOGIC;
  signal \S_SAMPLE_COUNTER_reg[30]_i_2_n_2\ : STD_LOGIC;
  signal \S_SAMPLE_COUNTER_reg[30]_i_2_n_3\ : STD_LOGIC;
  signal \S_SAMPLE_COUNTER_reg[30]_i_2_n_4\ : STD_LOGIC;
  signal \S_SAMPLE_COUNTER_reg[30]_i_2_n_5\ : STD_LOGIC;
  signal \S_SAMPLE_COUNTER_reg[30]_i_2_n_6\ : STD_LOGIC;
  signal \S_SAMPLE_COUNTER_reg[30]_i_2_n_7\ : STD_LOGIC;
  signal \^s_sample_counter_reg[31]_0\ : STD_LOGIC_VECTOR ( 6 downto 0 );
  signal \S_SAMPLE_COUNTER_reg[8]_i_2_n_0\ : STD_LOGIC;
  signal \S_SAMPLE_COUNTER_reg[8]_i_2_n_1\ : STD_LOGIC;
  signal \S_SAMPLE_COUNTER_reg[8]_i_2_n_2\ : STD_LOGIC;
  signal \S_SAMPLE_COUNTER_reg[8]_i_2_n_3\ : STD_LOGIC;
  signal \S_SAMPLE_COUNTER_reg[8]_i_2_n_4\ : STD_LOGIC;
  signal \S_SAMPLE_COUNTER_reg[8]_i_2_n_5\ : STD_LOGIC;
  signal \S_SAMPLE_COUNTER_reg[8]_i_2_n_6\ : STD_LOGIC;
  signal \S_SAMPLE_COUNTER_reg[8]_i_2_n_7\ : STD_LOGIC;
  signal S_SAMPLE_TIME_COUNTER : STD_LOGIC_VECTOR ( 30 downto 0 );
  signal \S_SAMPLE_TIME_COUNTER0__0\ : STD_LOGIC_VECTOR ( 30 downto 1 );
  signal \S_SAMPLE_TIME_COUNTER[16]_i_10_n_0\ : STD_LOGIC;
  signal \S_SAMPLE_TIME_COUNTER[16]_i_3_n_0\ : STD_LOGIC;
  signal \S_SAMPLE_TIME_COUNTER[16]_i_4_n_0\ : STD_LOGIC;
  signal \S_SAMPLE_TIME_COUNTER[16]_i_5_n_0\ : STD_LOGIC;
  signal \S_SAMPLE_TIME_COUNTER[16]_i_6_n_0\ : STD_LOGIC;
  signal \S_SAMPLE_TIME_COUNTER[16]_i_7_n_0\ : STD_LOGIC;
  signal \S_SAMPLE_TIME_COUNTER[16]_i_8_n_0\ : STD_LOGIC;
  signal \S_SAMPLE_TIME_COUNTER[16]_i_9_n_0\ : STD_LOGIC;
  signal \S_SAMPLE_TIME_COUNTER[24]_i_10_n_0\ : STD_LOGIC;
  signal \S_SAMPLE_TIME_COUNTER[24]_i_3_n_0\ : STD_LOGIC;
  signal \S_SAMPLE_TIME_COUNTER[24]_i_4_n_0\ : STD_LOGIC;
  signal \S_SAMPLE_TIME_COUNTER[24]_i_5_n_0\ : STD_LOGIC;
  signal \S_SAMPLE_TIME_COUNTER[24]_i_6_n_0\ : STD_LOGIC;
  signal \S_SAMPLE_TIME_COUNTER[24]_i_7_n_0\ : STD_LOGIC;
  signal \S_SAMPLE_TIME_COUNTER[24]_i_8_n_0\ : STD_LOGIC;
  signal \S_SAMPLE_TIME_COUNTER[24]_i_9_n_0\ : STD_LOGIC;
  signal \S_SAMPLE_TIME_COUNTER[30]_i_10_n_0\ : STD_LOGIC;
  signal \S_SAMPLE_TIME_COUNTER[30]_i_11_n_0\ : STD_LOGIC;
  signal \S_SAMPLE_TIME_COUNTER[30]_i_12_n_0\ : STD_LOGIC;
  signal \S_SAMPLE_TIME_COUNTER[30]_i_13_n_0\ : STD_LOGIC;
  signal \S_SAMPLE_TIME_COUNTER[30]_i_3_n_0\ : STD_LOGIC;
  signal \S_SAMPLE_TIME_COUNTER[30]_i_4_n_0\ : STD_LOGIC;
  signal \S_SAMPLE_TIME_COUNTER[30]_i_6_n_0\ : STD_LOGIC;
  signal \S_SAMPLE_TIME_COUNTER[30]_i_7_n_0\ : STD_LOGIC;
  signal \S_SAMPLE_TIME_COUNTER[30]_i_8_n_0\ : STD_LOGIC;
  signal \S_SAMPLE_TIME_COUNTER[30]_i_9_n_0\ : STD_LOGIC;
  signal \S_SAMPLE_TIME_COUNTER[8]_i_10_n_0\ : STD_LOGIC;
  signal \S_SAMPLE_TIME_COUNTER[8]_i_3_n_0\ : STD_LOGIC;
  signal \S_SAMPLE_TIME_COUNTER[8]_i_4_n_0\ : STD_LOGIC;
  signal \S_SAMPLE_TIME_COUNTER[8]_i_5_n_0\ : STD_LOGIC;
  signal \S_SAMPLE_TIME_COUNTER[8]_i_6_n_0\ : STD_LOGIC;
  signal \S_SAMPLE_TIME_COUNTER[8]_i_7_n_0\ : STD_LOGIC;
  signal \S_SAMPLE_TIME_COUNTER[8]_i_8_n_0\ : STD_LOGIC;
  signal \S_SAMPLE_TIME_COUNTER[8]_i_9_n_0\ : STD_LOGIC;
  signal \S_SAMPLE_TIME_COUNTER_reg[16]_i_2_n_0\ : STD_LOGIC;
  signal \S_SAMPLE_TIME_COUNTER_reg[16]_i_2_n_1\ : STD_LOGIC;
  signal \S_SAMPLE_TIME_COUNTER_reg[16]_i_2_n_2\ : STD_LOGIC;
  signal \S_SAMPLE_TIME_COUNTER_reg[16]_i_2_n_3\ : STD_LOGIC;
  signal \S_SAMPLE_TIME_COUNTER_reg[16]_i_2_n_4\ : STD_LOGIC;
  signal \S_SAMPLE_TIME_COUNTER_reg[16]_i_2_n_5\ : STD_LOGIC;
  signal \S_SAMPLE_TIME_COUNTER_reg[16]_i_2_n_6\ : STD_LOGIC;
  signal \S_SAMPLE_TIME_COUNTER_reg[16]_i_2_n_7\ : STD_LOGIC;
  signal \S_SAMPLE_TIME_COUNTER_reg[24]_i_2_n_0\ : STD_LOGIC;
  signal \S_SAMPLE_TIME_COUNTER_reg[24]_i_2_n_1\ : STD_LOGIC;
  signal \S_SAMPLE_TIME_COUNTER_reg[24]_i_2_n_2\ : STD_LOGIC;
  signal \S_SAMPLE_TIME_COUNTER_reg[24]_i_2_n_3\ : STD_LOGIC;
  signal \S_SAMPLE_TIME_COUNTER_reg[24]_i_2_n_4\ : STD_LOGIC;
  signal \S_SAMPLE_TIME_COUNTER_reg[24]_i_2_n_5\ : STD_LOGIC;
  signal \S_SAMPLE_TIME_COUNTER_reg[24]_i_2_n_6\ : STD_LOGIC;
  signal \S_SAMPLE_TIME_COUNTER_reg[24]_i_2_n_7\ : STD_LOGIC;
  signal \S_SAMPLE_TIME_COUNTER_reg[30]_i_5_n_3\ : STD_LOGIC;
  signal \S_SAMPLE_TIME_COUNTER_reg[30]_i_5_n_4\ : STD_LOGIC;
  signal \S_SAMPLE_TIME_COUNTER_reg[30]_i_5_n_5\ : STD_LOGIC;
  signal \S_SAMPLE_TIME_COUNTER_reg[30]_i_5_n_6\ : STD_LOGIC;
  signal \S_SAMPLE_TIME_COUNTER_reg[30]_i_5_n_7\ : STD_LOGIC;
  signal \S_SAMPLE_TIME_COUNTER_reg[8]_i_2_n_0\ : STD_LOGIC;
  signal \S_SAMPLE_TIME_COUNTER_reg[8]_i_2_n_1\ : STD_LOGIC;
  signal \S_SAMPLE_TIME_COUNTER_reg[8]_i_2_n_2\ : STD_LOGIC;
  signal \S_SAMPLE_TIME_COUNTER_reg[8]_i_2_n_3\ : STD_LOGIC;
  signal \S_SAMPLE_TIME_COUNTER_reg[8]_i_2_n_4\ : STD_LOGIC;
  signal \S_SAMPLE_TIME_COUNTER_reg[8]_i_2_n_5\ : STD_LOGIC;
  signal \S_SAMPLE_TIME_COUNTER_reg[8]_i_2_n_6\ : STD_LOGIC;
  signal \S_SAMPLE_TIME_COUNTER_reg[8]_i_2_n_7\ : STD_LOGIC;
  signal \S_SAMPLE_TIME_reg_n_0_[0]\ : STD_LOGIC;
  signal \S_SAMPLE_TIME_reg_n_0_[10]\ : STD_LOGIC;
  signal \S_SAMPLE_TIME_reg_n_0_[11]\ : STD_LOGIC;
  signal \S_SAMPLE_TIME_reg_n_0_[12]\ : STD_LOGIC;
  signal \S_SAMPLE_TIME_reg_n_0_[13]\ : STD_LOGIC;
  signal \S_SAMPLE_TIME_reg_n_0_[14]\ : STD_LOGIC;
  signal \S_SAMPLE_TIME_reg_n_0_[15]\ : STD_LOGIC;
  signal \S_SAMPLE_TIME_reg_n_0_[16]\ : STD_LOGIC;
  signal \S_SAMPLE_TIME_reg_n_0_[17]\ : STD_LOGIC;
  signal \S_SAMPLE_TIME_reg_n_0_[18]\ : STD_LOGIC;
  signal \S_SAMPLE_TIME_reg_n_0_[19]\ : STD_LOGIC;
  signal \S_SAMPLE_TIME_reg_n_0_[1]\ : STD_LOGIC;
  signal \S_SAMPLE_TIME_reg_n_0_[20]\ : STD_LOGIC;
  signal \S_SAMPLE_TIME_reg_n_0_[21]\ : STD_LOGIC;
  signal \S_SAMPLE_TIME_reg_n_0_[22]\ : STD_LOGIC;
  signal \S_SAMPLE_TIME_reg_n_0_[23]\ : STD_LOGIC;
  signal \S_SAMPLE_TIME_reg_n_0_[24]\ : STD_LOGIC;
  signal \S_SAMPLE_TIME_reg_n_0_[25]\ : STD_LOGIC;
  signal \S_SAMPLE_TIME_reg_n_0_[26]\ : STD_LOGIC;
  signal \S_SAMPLE_TIME_reg_n_0_[27]\ : STD_LOGIC;
  signal \S_SAMPLE_TIME_reg_n_0_[28]\ : STD_LOGIC;
  signal \S_SAMPLE_TIME_reg_n_0_[29]\ : STD_LOGIC;
  signal \S_SAMPLE_TIME_reg_n_0_[2]\ : STD_LOGIC;
  signal \S_SAMPLE_TIME_reg_n_0_[30]\ : STD_LOGIC;
  signal \S_SAMPLE_TIME_reg_n_0_[3]\ : STD_LOGIC;
  signal \S_SAMPLE_TIME_reg_n_0_[4]\ : STD_LOGIC;
  signal \S_SAMPLE_TIME_reg_n_0_[5]\ : STD_LOGIC;
  signal \S_SAMPLE_TIME_reg_n_0_[6]\ : STD_LOGIC;
  signal \S_SAMPLE_TIME_reg_n_0_[7]\ : STD_LOGIC;
  signal \S_SAMPLE_TIME_reg_n_0_[8]\ : STD_LOGIC;
  signal \S_SAMPLE_TIME_reg_n_0_[9]\ : STD_LOGIC;
  signal S_SPI_BUSY_PIPE : STD_LOGIC_VECTOR ( 1 downto 0 );
  signal \S_SPI_BUSY_PIPE[1]_i_2_n_0\ : STD_LOGIC;
  signal \^s_spi_enable_reg_0\ : STD_LOGIC;
  signal V_SAMPLE_COUNTER2 : STD_LOGIC_VECTOR ( 31 downto 1 );
  signal data2 : STD_LOGIC_VECTOR ( 17 downto 0 );
  signal data3 : STD_LOGIC_VECTOR ( 17 downto 0 );
  signal data4 : STD_LOGIC_VECTOR ( 17 downto 0 );
  signal data5 : STD_LOGIC_VECTOR ( 17 downto 0 );
  signal data6 : STD_LOGIC_VECTOR ( 17 downto 0 );
  signal data7 : STD_LOGIC_VECTOR ( 17 downto 0 );
  signal data8 : STD_LOGIC_VECTOR ( 17 downto 0 );
  signal nxtstate : STD_LOGIC_VECTOR ( 1 downto 0 );
  signal nxtstate22_in : STD_LOGIC;
  signal nxtstate3 : STD_LOGIC_VECTOR ( 30 downto 1 );
  signal p_1_in : STD_LOGIC_VECTOR ( 279 downto 69 );
  signal p_2_in : STD_LOGIC_VECTOR ( 30 downto 0 );
  signal raw_to_si_n_1 : STD_LOGIC;
  signal raw_to_si_n_133 : STD_LOGIC;
  signal raw_to_si_n_134 : STD_LOGIC;
  signal raw_to_si_n_135 : STD_LOGIC;
  signal raw_to_si_n_136 : STD_LOGIC;
  signal raw_to_si_n_137 : STD_LOGIC;
  signal spi_n_10 : STD_LOGIC;
  signal spi_n_11 : STD_LOGIC;
  signal spi_n_12 : STD_LOGIC;
  signal spi_n_13 : STD_LOGIC;
  signal spi_n_14 : STD_LOGIC;
  signal spi_n_15 : STD_LOGIC;
  signal spi_n_16 : STD_LOGIC;
  signal spi_n_17 : STD_LOGIC;
  signal spi_n_18 : STD_LOGIC;
  signal spi_n_19 : STD_LOGIC;
  signal spi_n_20 : STD_LOGIC;
  signal spi_n_3 : STD_LOGIC;
  signal spi_n_4 : STD_LOGIC;
  signal spi_n_5 : STD_LOGIC;
  signal spi_n_6 : STD_LOGIC;
  signal spi_n_7 : STD_LOGIC;
  signal spi_n_8 : STD_LOGIC;
  signal spi_n_9 : STD_LOGIC;
  signal NLW_SI_VALID_reg_i_49_CO_UNCONNECTED : STD_LOGIC_VECTOR ( 7 downto 5 );
  signal NLW_SI_VALID_reg_i_49_O_UNCONNECTED : STD_LOGIC_VECTOR ( 7 downto 6 );
  signal \NLW_S_SAMPLE_COUNTER_reg[30]_i_2_CO_UNCONNECTED\ : STD_LOGIC_VECTOR ( 7 downto 6 );
  signal \NLW_S_SAMPLE_COUNTER_reg[30]_i_2_O_UNCONNECTED\ : STD_LOGIC_VECTOR ( 7 to 7 );
  signal \NLW_S_SAMPLE_TIME_COUNTER_reg[30]_i_5_CO_UNCONNECTED\ : STD_LOGIC_VECTOR ( 7 downto 5 );
  signal \NLW_S_SAMPLE_TIME_COUNTER_reg[30]_i_5_O_UNCONNECTED\ : STD_LOGIC_VECTOR ( 7 downto 6 );
  attribute SOFT_HLUTNM : string;
  attribute SOFT_HLUTNM of \SI_VALUE[180]_i_3\ : label is "soft_lutpair91";
  attribute SOFT_HLUTNM of \SI_VALUE[270]_i_3\ : label is "soft_lutpair91";
  attribute SOFT_HLUTNM of \SI_VALUE[273]_i_2\ : label is "soft_lutpair88";
  attribute SOFT_HLUTNM of \SI_VALUE[273]_i_4\ : label is "soft_lutpair88";
  attribute SOFT_HLUTNM of \SI_VALUE[279]_i_6\ : label is "soft_lutpair89";
  attribute SOFT_HLUTNM of \SI_VALUE[279]_i_7\ : label is "soft_lutpair89";
  attribute SOFT_HLUTNM of \S_CHANNEL_COUNTER[1]_i_1\ : label is "soft_lutpair108";
  attribute SOFT_HLUTNM of \S_CHANNEL_COUNTER[2]_i_1\ : label is "soft_lutpair85";
  attribute SOFT_HLUTNM of \S_CHANNEL_COUNTER[3]_i_2\ : label is "soft_lutpair85";
  attribute SOFT_HLUTNM of \S_CONV_COUNTER[0]_i_1\ : label is "soft_lutpair107";
  attribute SOFT_HLUTNM of \S_CONV_COUNTER[1]_i_1\ : label is "soft_lutpair107";
  attribute SOFT_HLUTNM of \S_CONV_COUNTER[2]_i_1\ : label is "soft_lutpair84";
  attribute SOFT_HLUTNM of \S_CONV_COUNTER[3]_i_2\ : label is "soft_lutpair84";
  attribute SOFT_HLUTNM of \S_RAW_VALUE_S_C[15]_i_3\ : label is "soft_lutpair108";
  attribute SOFT_HLUTNM of \S_RESULT_COUNTER[0]_i_1\ : label is "soft_lutpair90";
  attribute SOFT_HLUTNM of \S_RESULT_COUNTER[1]_i_1\ : label is "soft_lutpair90";
  attribute SOFT_HLUTNM of \S_RESULT_COUNTER[2]_i_1\ : label is "soft_lutpair83";
  attribute SOFT_HLUTNM of \S_RESULT_COUNTER[3]_i_2\ : label is "soft_lutpair83";
  attribute SOFT_HLUTNM of \S_RESULT_COUNTER[3]_i_3\ : label is "soft_lutpair87";
  attribute ORIG_CELL_NAME : string;
  attribute ORIG_CELL_NAME of \S_RESULT_COUNTER_reg[0]\ : label is "S_RESULT_COUNTER_reg[0]";
  attribute ORIG_CELL_NAME of \S_RESULT_COUNTER_reg[0]_rep\ : label is "S_RESULT_COUNTER_reg[0]";
  attribute ORIG_CELL_NAME of \S_RESULT_COUNTER_reg[1]\ : label is "S_RESULT_COUNTER_reg[1]";
  attribute ORIG_CELL_NAME of \S_RESULT_COUNTER_reg[1]_rep\ : label is "S_RESULT_COUNTER_reg[1]";
  attribute SOFT_HLUTNM of \S_SAMPLE_COUNTER[10]_i_1\ : label is "soft_lutpair102";
  attribute SOFT_HLUTNM of \S_SAMPLE_COUNTER[11]_i_1\ : label is "soft_lutpair101";
  attribute SOFT_HLUTNM of \S_SAMPLE_COUNTER[12]_i_1\ : label is "soft_lutpair101";
  attribute SOFT_HLUTNM of \S_SAMPLE_COUNTER[13]_i_1\ : label is "soft_lutpair100";
  attribute SOFT_HLUTNM of \S_SAMPLE_COUNTER[14]_i_1\ : label is "soft_lutpair100";
  attribute SOFT_HLUTNM of \S_SAMPLE_COUNTER[15]_i_1\ : label is "soft_lutpair99";
  attribute SOFT_HLUTNM of \S_SAMPLE_COUNTER[16]_i_1\ : label is "soft_lutpair99";
  attribute SOFT_HLUTNM of \S_SAMPLE_COUNTER[17]_i_1\ : label is "soft_lutpair98";
  attribute SOFT_HLUTNM of \S_SAMPLE_COUNTER[18]_i_1\ : label is "soft_lutpair98";
  attribute SOFT_HLUTNM of \S_SAMPLE_COUNTER[19]_i_1\ : label is "soft_lutpair97";
  attribute SOFT_HLUTNM of \S_SAMPLE_COUNTER[1]_i_1\ : label is "soft_lutpair106";
  attribute SOFT_HLUTNM of \S_SAMPLE_COUNTER[20]_i_1\ : label is "soft_lutpair97";
  attribute SOFT_HLUTNM of \S_SAMPLE_COUNTER[21]_i_1\ : label is "soft_lutpair96";
  attribute SOFT_HLUTNM of \S_SAMPLE_COUNTER[22]_i_1\ : label is "soft_lutpair96";
  attribute SOFT_HLUTNM of \S_SAMPLE_COUNTER[23]_i_1\ : label is "soft_lutpair95";
  attribute SOFT_HLUTNM of \S_SAMPLE_COUNTER[24]_i_1\ : label is "soft_lutpair95";
  attribute SOFT_HLUTNM of \S_SAMPLE_COUNTER[25]_i_1\ : label is "soft_lutpair94";
  attribute SOFT_HLUTNM of \S_SAMPLE_COUNTER[26]_i_1\ : label is "soft_lutpair94";
  attribute SOFT_HLUTNM of \S_SAMPLE_COUNTER[27]_i_1\ : label is "soft_lutpair93";
  attribute SOFT_HLUTNM of \S_SAMPLE_COUNTER[28]_i_1\ : label is "soft_lutpair93";
  attribute SOFT_HLUTNM of \S_SAMPLE_COUNTER[29]_i_1\ : label is "soft_lutpair92";
  attribute SOFT_HLUTNM of \S_SAMPLE_COUNTER[2]_i_1\ : label is "soft_lutpair106";
  attribute SOFT_HLUTNM of \S_SAMPLE_COUNTER[30]_i_1\ : label is "soft_lutpair92";
  attribute SOFT_HLUTNM of \S_SAMPLE_COUNTER[31]_i_3\ : label is "soft_lutpair86";
  attribute SOFT_HLUTNM of \S_SAMPLE_COUNTER[3]_i_1\ : label is "soft_lutpair105";
  attribute SOFT_HLUTNM of \S_SAMPLE_COUNTER[4]_i_1\ : label is "soft_lutpair105";
  attribute SOFT_HLUTNM of \S_SAMPLE_COUNTER[5]_i_1\ : label is "soft_lutpair104";
  attribute SOFT_HLUTNM of \S_SAMPLE_COUNTER[6]_i_1\ : label is "soft_lutpair104";
  attribute SOFT_HLUTNM of \S_SAMPLE_COUNTER[7]_i_1\ : label is "soft_lutpair103";
  attribute SOFT_HLUTNM of \S_SAMPLE_COUNTER[8]_i_1\ : label is "soft_lutpair103";
  attribute SOFT_HLUTNM of \S_SAMPLE_COUNTER[9]_i_1\ : label is "soft_lutpair102";
  attribute ADDER_THRESHOLD : integer;
  attribute ADDER_THRESHOLD of \S_SAMPLE_COUNTER_reg[16]_i_2\ : label is 35;
  attribute ADDER_THRESHOLD of \S_SAMPLE_COUNTER_reg[24]_i_2\ : label is 35;
  attribute ADDER_THRESHOLD of \S_SAMPLE_COUNTER_reg[30]_i_2\ : label is 35;
  attribute ADDER_THRESHOLD of \S_SAMPLE_COUNTER_reg[8]_i_2\ : label is 35;
  attribute ADDER_THRESHOLD of \S_SAMPLE_TIME_COUNTER_reg[16]_i_2\ : label is 35;
  attribute ADDER_THRESHOLD of \S_SAMPLE_TIME_COUNTER_reg[24]_i_2\ : label is 35;
  attribute ADDER_THRESHOLD of \S_SAMPLE_TIME_COUNTER_reg[30]_i_5\ : label is 35;
  attribute ADDER_THRESHOLD of \S_SAMPLE_TIME_COUNTER_reg[8]_i_2\ : label is 35;
  attribute SOFT_HLUTNM of \S_SPI_BUSY_PIPE[1]_i_2\ : label is "soft_lutpair86";
  attribute SOFT_HLUTNM of \curstate[1]_i_1\ : label is "soft_lutpair87";
  attribute FSM_ENCODING : string;
  attribute FSM_ENCODING of \curstate_reg[0]\ : label is "auto";
  attribute FSM_SAFE_STATE : string;
  attribute FSM_SAFE_STATE of \curstate_reg[0]\ : label is "power_on_state";
  attribute FSM_ENCODING of \curstate_reg[1]\ : label is "auto";
  attribute FSM_SAFE_STATE of \curstate_reg[1]\ : label is "power_on_state";
begin
  E(0) <= \^e\(0);
  Q(1 downto 0) <= \^q\(1 downto 0);
  S(7 downto 0) <= \^s\(7 downto 0);
  S_DUMMY_SAMPLE <= \^s_dummy_sample\;
  \S_ENABLE_reg[0]\ <= \^s_enable_reg[0]\;
  \S_ENABLE_reg[0]_0\ <= \^s_enable_reg[0]_0\;
  \S_ENABLE_reg[0]_1\ <= \^s_enable_reg[0]_1\;
  S_MANUAL_reg_0 <= \^s_manual_reg_0\;
  \S_SAMPLE_COUNTER_reg[0]_0\ <= \^s_sample_counter_reg[0]_0\;
  \S_SAMPLE_COUNTER_reg[16]_0\(7 downto 0) <= \^s_sample_counter_reg[16]_0\(7 downto 0);
  \S_SAMPLE_COUNTER_reg[24]_0\(7 downto 0) <= \^s_sample_counter_reg[24]_0\(7 downto 0);
  \S_SAMPLE_COUNTER_reg[31]_0\(6 downto 0) <= \^s_sample_counter_reg[31]_0\(6 downto 0);
  S_SPI_ENABLE_reg_0 <= \^s_spi_enable_reg_0\;
BUSY_reg: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => '1',
      D => BUSY_reg_0,
      Q => BUSY,
      R => RSTP
    );
RAW_VALID_reg: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => '1',
      D => RAW_VALID_reg_0,
      Q => RAW_VALID(0),
      R => RSTP
    );
SI_VALID_i_1: unisim.vcomponents.LUT4
    generic map(
      INIT => X"4055"
    )
        port map (
      I0 => \^s_enable_reg[0]_0\,
      I1 => \^q\(1),
      I2 => \^q\(0),
      I3 => \^s_enable_reg[0]\,
      O => SI_VALID_i_1_n_0
    );
SI_VALID_i_53: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => \S_SAMPLES_reg_n_0_[30]\,
      O => SI_VALID_i_53_n_0
    );
SI_VALID_i_54: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => \S_SAMPLES_reg_n_0_[29]\,
      O => SI_VALID_i_54_n_0
    );
SI_VALID_i_55: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => \S_SAMPLES_reg_n_0_[28]\,
      O => SI_VALID_i_55_n_0
    );
SI_VALID_i_56: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => \S_SAMPLES_reg_n_0_[27]\,
      O => SI_VALID_i_56_n_0
    );
SI_VALID_i_57: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => \S_SAMPLES_reg_n_0_[26]\,
      O => SI_VALID_i_57_n_0
    );
SI_VALID_i_58: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => \S_SAMPLES_reg_n_0_[25]\,
      O => SI_VALID_i_58_n_0
    );
SI_VALID_i_59: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => \S_SAMPLES_reg_n_0_[24]\,
      O => SI_VALID_i_59_n_0
    );
SI_VALID_i_60: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => \S_SAMPLES_reg_n_0_[23]\,
      O => SI_VALID_i_60_n_0
    );
SI_VALID_i_61: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => \S_SAMPLES_reg_n_0_[22]\,
      O => SI_VALID_i_61_n_0
    );
SI_VALID_i_62: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => \S_SAMPLES_reg_n_0_[21]\,
      O => SI_VALID_i_62_n_0
    );
SI_VALID_i_63: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => \S_SAMPLES_reg_n_0_[20]\,
      O => SI_VALID_i_63_n_0
    );
SI_VALID_i_64: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => \S_SAMPLES_reg_n_0_[19]\,
      O => SI_VALID_i_64_n_0
    );
SI_VALID_i_65: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => \S_SAMPLES_reg_n_0_[18]\,
      O => SI_VALID_i_65_n_0
    );
SI_VALID_i_66: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => \S_SAMPLES_reg_n_0_[17]\,
      O => SI_VALID_i_66_n_0
    );
SI_VALID_i_67: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => \S_SAMPLES_reg_n_0_[16]\,
      O => SI_VALID_i_67_n_0
    );
SI_VALID_i_68: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => \S_SAMPLES_reg_n_0_[15]\,
      O => SI_VALID_i_68_n_0
    );
SI_VALID_i_69: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => \S_SAMPLES_reg_n_0_[14]\,
      O => SI_VALID_i_69_n_0
    );
SI_VALID_i_70: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => \S_SAMPLES_reg_n_0_[13]\,
      O => SI_VALID_i_70_n_0
    );
SI_VALID_i_71: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => \S_SAMPLES_reg_n_0_[12]\,
      O => SI_VALID_i_71_n_0
    );
SI_VALID_i_72: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => \S_SAMPLES_reg_n_0_[11]\,
      O => SI_VALID_i_72_n_0
    );
SI_VALID_i_73: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => \S_SAMPLES_reg_n_0_[10]\,
      O => SI_VALID_i_73_n_0
    );
SI_VALID_i_74: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => \S_SAMPLES_reg_n_0_[9]\,
      O => SI_VALID_i_74_n_0
    );
SI_VALID_i_75: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => \S_SAMPLES_reg_n_0_[8]\,
      O => SI_VALID_i_75_n_0
    );
SI_VALID_i_76: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => \S_SAMPLES_reg_n_0_[7]\,
      O => SI_VALID_i_76_n_0
    );
SI_VALID_i_77: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => \S_SAMPLES_reg_n_0_[6]\,
      O => SI_VALID_i_77_n_0
    );
SI_VALID_i_78: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => \S_SAMPLES_reg_n_0_[5]\,
      O => SI_VALID_i_78_n_0
    );
SI_VALID_i_79: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => \S_SAMPLES_reg_n_0_[4]\,
      O => SI_VALID_i_79_n_0
    );
SI_VALID_i_80: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => \S_SAMPLES_reg_n_0_[3]\,
      O => SI_VALID_i_80_n_0
    );
SI_VALID_i_81: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => \S_SAMPLES_reg_n_0_[2]\,
      O => SI_VALID_i_81_n_0
    );
SI_VALID_i_82: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => \S_SAMPLES_reg_n_0_[1]\,
      O => SI_VALID_i_82_n_0
    );
SI_VALID_reg: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => SI_VALID_i_1_n_0,
      D => \^s_enable_reg[0]\,
      Q => SI_VALID(0),
      R => RSTP
    );
SI_VALID_reg_i_49: unisim.vcomponents.CARRY8
     port map (
      CI => SI_VALID_reg_i_50_n_0,
      CI_TOP => '0',
      CO(7) => NLW_SI_VALID_reg_i_49_CO_UNCONNECTED(7),
      CO(6) => SI_VALID_reg_i_49_n_1,
      CO(5) => NLW_SI_VALID_reg_i_49_CO_UNCONNECTED(5),
      CO(4) => SI_VALID_reg_i_49_n_3,
      CO(3) => SI_VALID_reg_i_49_n_4,
      CO(2) => SI_VALID_reg_i_49_n_5,
      CO(1) => SI_VALID_reg_i_49_n_6,
      CO(0) => SI_VALID_reg_i_49_n_7,
      DI(7 downto 6) => B"00",
      DI(5) => \S_SAMPLES_reg_n_0_[30]\,
      DI(4) => \S_SAMPLES_reg_n_0_[29]\,
      DI(3) => \S_SAMPLES_reg_n_0_[28]\,
      DI(2) => \S_SAMPLES_reg_n_0_[27]\,
      DI(1) => \S_SAMPLES_reg_n_0_[26]\,
      DI(0) => \S_SAMPLES_reg_n_0_[25]\,
      O(7 downto 6) => NLW_SI_VALID_reg_i_49_O_UNCONNECTED(7 downto 6),
      O(5 downto 0) => nxtstate3(30 downto 25),
      S(7 downto 6) => B"01",
      S(5) => SI_VALID_i_53_n_0,
      S(4) => SI_VALID_i_54_n_0,
      S(3) => SI_VALID_i_55_n_0,
      S(2) => SI_VALID_i_56_n_0,
      S(1) => SI_VALID_i_57_n_0,
      S(0) => SI_VALID_i_58_n_0
    );
SI_VALID_reg_i_50: unisim.vcomponents.CARRY8
     port map (
      CI => SI_VALID_reg_i_51_n_0,
      CI_TOP => '0',
      CO(7) => SI_VALID_reg_i_50_n_0,
      CO(6) => SI_VALID_reg_i_50_n_1,
      CO(5) => SI_VALID_reg_i_50_n_2,
      CO(4) => SI_VALID_reg_i_50_n_3,
      CO(3) => SI_VALID_reg_i_50_n_4,
      CO(2) => SI_VALID_reg_i_50_n_5,
      CO(1) => SI_VALID_reg_i_50_n_6,
      CO(0) => SI_VALID_reg_i_50_n_7,
      DI(7) => \S_SAMPLES_reg_n_0_[24]\,
      DI(6) => \S_SAMPLES_reg_n_0_[23]\,
      DI(5) => \S_SAMPLES_reg_n_0_[22]\,
      DI(4) => \S_SAMPLES_reg_n_0_[21]\,
      DI(3) => \S_SAMPLES_reg_n_0_[20]\,
      DI(2) => \S_SAMPLES_reg_n_0_[19]\,
      DI(1) => \S_SAMPLES_reg_n_0_[18]\,
      DI(0) => \S_SAMPLES_reg_n_0_[17]\,
      O(7 downto 0) => nxtstate3(24 downto 17),
      S(7) => SI_VALID_i_59_n_0,
      S(6) => SI_VALID_i_60_n_0,
      S(5) => SI_VALID_i_61_n_0,
      S(4) => SI_VALID_i_62_n_0,
      S(3) => SI_VALID_i_63_n_0,
      S(2) => SI_VALID_i_64_n_0,
      S(1) => SI_VALID_i_65_n_0,
      S(0) => SI_VALID_i_66_n_0
    );
SI_VALID_reg_i_51: unisim.vcomponents.CARRY8
     port map (
      CI => SI_VALID_reg_i_52_n_0,
      CI_TOP => '0',
      CO(7) => SI_VALID_reg_i_51_n_0,
      CO(6) => SI_VALID_reg_i_51_n_1,
      CO(5) => SI_VALID_reg_i_51_n_2,
      CO(4) => SI_VALID_reg_i_51_n_3,
      CO(3) => SI_VALID_reg_i_51_n_4,
      CO(2) => SI_VALID_reg_i_51_n_5,
      CO(1) => SI_VALID_reg_i_51_n_6,
      CO(0) => SI_VALID_reg_i_51_n_7,
      DI(7) => \S_SAMPLES_reg_n_0_[16]\,
      DI(6) => \S_SAMPLES_reg_n_0_[15]\,
      DI(5) => \S_SAMPLES_reg_n_0_[14]\,
      DI(4) => \S_SAMPLES_reg_n_0_[13]\,
      DI(3) => \S_SAMPLES_reg_n_0_[12]\,
      DI(2) => \S_SAMPLES_reg_n_0_[11]\,
      DI(1) => \S_SAMPLES_reg_n_0_[10]\,
      DI(0) => \S_SAMPLES_reg_n_0_[9]\,
      O(7 downto 0) => nxtstate3(16 downto 9),
      S(7) => SI_VALID_i_67_n_0,
      S(6) => SI_VALID_i_68_n_0,
      S(5) => SI_VALID_i_69_n_0,
      S(4) => SI_VALID_i_70_n_0,
      S(3) => SI_VALID_i_71_n_0,
      S(2) => SI_VALID_i_72_n_0,
      S(1) => SI_VALID_i_73_n_0,
      S(0) => SI_VALID_i_74_n_0
    );
SI_VALID_reg_i_52: unisim.vcomponents.CARRY8
     port map (
      CI => \S_SAMPLES_reg_n_0_[0]\,
      CI_TOP => '0',
      CO(7) => SI_VALID_reg_i_52_n_0,
      CO(6) => SI_VALID_reg_i_52_n_1,
      CO(5) => SI_VALID_reg_i_52_n_2,
      CO(4) => SI_VALID_reg_i_52_n_3,
      CO(3) => SI_VALID_reg_i_52_n_4,
      CO(2) => SI_VALID_reg_i_52_n_5,
      CO(1) => SI_VALID_reg_i_52_n_6,
      CO(0) => SI_VALID_reg_i_52_n_7,
      DI(7) => \S_SAMPLES_reg_n_0_[8]\,
      DI(6) => \S_SAMPLES_reg_n_0_[7]\,
      DI(5) => \S_SAMPLES_reg_n_0_[6]\,
      DI(4) => \S_SAMPLES_reg_n_0_[5]\,
      DI(3) => \S_SAMPLES_reg_n_0_[4]\,
      DI(2) => \S_SAMPLES_reg_n_0_[3]\,
      DI(1) => \S_SAMPLES_reg_n_0_[2]\,
      DI(0) => \S_SAMPLES_reg_n_0_[1]\,
      O(7 downto 0) => nxtstate3(8 downto 1),
      S(7) => SI_VALID_i_75_n_0,
      S(6) => SI_VALID_i_76_n_0,
      S(5) => SI_VALID_i_77_n_0,
      S(4) => SI_VALID_i_78_n_0,
      S(3) => SI_VALID_i_79_n_0,
      S(2) => SI_VALID_i_80_n_0,
      S(1) => SI_VALID_i_81_n_0,
      S(0) => SI_VALID_i_82_n_0
    );
\SI_VALUE[104]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"00010000"
    )
        port map (
      I0 => \SI_VALUE[279]_i_3_n_0\,
      I1 => S_RESULT_COUNTER(3),
      I2 => S_RESULT_COUNTER(2),
      I3 => \S_RESULT_COUNTER_reg[0]_rep_n_0\,
      I4 => \S_RESULT_COUNTER_reg[1]_rep_n_0\,
      O => p_1_in(104)
    );
\SI_VALUE[139]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"0008"
    )
        port map (
      I0 => \S_RESULT_COUNTER_reg[0]_rep_n_0\,
      I1 => \S_RESULT_COUNTER_reg[1]_rep_n_0\,
      I2 => S_RESULT_COUNTER(2),
      I3 => \SI_VALUE[279]_i_3_n_0\,
      O => p_1_in(139)
    );
\SI_VALUE[174]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"00000100"
    )
        port map (
      I0 => \SI_VALUE[279]_i_3_n_0\,
      I1 => \S_RESULT_COUNTER_reg[0]_rep_n_0\,
      I2 => S_RESULT_COUNTER(3),
      I3 => S_RESULT_COUNTER(2),
      I4 => \S_RESULT_COUNTER_reg[1]_rep_n_0\,
      O => p_1_in(174)
    );
\SI_VALUE[180]_i_3\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"40"
    )
        port map (
      I0 => S_RESULT_COUNTER(3),
      I1 => \S_RESULT_COUNTER_reg[1]_rep_n_0\,
      I2 => S_RESULT_COUNTER(2),
      O => \SI_VALUE[180]_i_3_n_0\
    );
\SI_VALUE[209]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"00001000"
    )
        port map (
      I0 => \SI_VALUE[279]_i_3_n_0\,
      I1 => \S_RESULT_COUNTER_reg[1]_rep_n_0\,
      I2 => \S_RESULT_COUNTER_reg[0]_rep_n_0\,
      I3 => S_RESULT_COUNTER(2),
      I4 => S_RESULT_COUNTER(3),
      O => p_1_in(209)
    );
\SI_VALUE[244]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"00100000"
    )
        port map (
      I0 => \SI_VALUE[279]_i_3_n_0\,
      I1 => S_RESULT_COUNTER(3),
      I2 => S_RESULT_COUNTER(2),
      I3 => \S_RESULT_COUNTER_reg[0]_rep_n_0\,
      I4 => \S_RESULT_COUNTER_reg[1]_rep_n_0\,
      O => p_1_in(244)
    );
\SI_VALUE[270]_i_3\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"C6"
    )
        port map (
      I0 => \S_RESULT_COUNTER_reg[1]_rep_n_0\,
      I1 => S_RESULT_COUNTER(2),
      I2 => \S_RESULT_COUNTER_reg[0]_rep_n_0\,
      O => \SI_VALUE[270]_i_3_n_0\
    );
\SI_VALUE[273]_i_2\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"224C"
    )
        port map (
      I0 => \S_RESULT_COUNTER_reg[1]_rep_n_0\,
      I1 => S_RESULT_COUNTER(3),
      I2 => \S_RESULT_COUNTER_reg[0]_rep_n_0\,
      I3 => S_RESULT_COUNTER(2),
      O => \SI_VALUE[273]_i_2_n_0\
    );
\SI_VALUE[273]_i_4\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"4AB5"
    )
        port map (
      I0 => S_RESULT_COUNTER(2),
      I1 => \S_RESULT_COUNTER_reg[0]_rep_n_0\,
      I2 => \S_RESULT_COUNTER_reg[1]_rep_n_0\,
      I3 => S_RESULT_COUNTER(3),
      O => \SI_VALUE[273]_i_4_n_0\
    );
\SI_VALUE[279]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"00004000"
    )
        port map (
      I0 => S_RESULT_COUNTER(3),
      I1 => \S_RESULT_COUNTER_reg[1]_rep_n_0\,
      I2 => \S_RESULT_COUNTER_reg[0]_rep_n_0\,
      I3 => S_RESULT_COUNTER(2),
      I4 => \SI_VALUE[279]_i_3_n_0\,
      O => p_1_in(279)
    );
\SI_VALUE[279]_i_3\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"F7F7F7F7FFFFFFF0"
    )
        port map (
      I0 => \^q\(0),
      I1 => \^q\(1),
      I2 => \^s_enable_reg[0]_0\,
      I3 => S_RESULT_COUNTER(3),
      I4 => \SI_VALUE[279]_i_6_n_0\,
      I5 => \^s_enable_reg[0]\,
      O => \SI_VALUE[279]_i_3_n_0\
    );
\SI_VALUE[279]_i_6\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"01"
    )
        port map (
      I0 => S_RESULT_COUNTER(2),
      I1 => \S_RESULT_COUNTER_reg[1]_rep_n_0\,
      I2 => \S_RESULT_COUNTER_reg[0]_rep_n_0\,
      O => \SI_VALUE[279]_i_6_n_0\
    );
\SI_VALUE[279]_i_7\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"8000"
    )
        port map (
      I0 => S_RESULT_COUNTER(2),
      I1 => S_RESULT_COUNTER(3),
      I2 => \S_RESULT_COUNTER_reg[0]_rep_n_0\,
      I3 => \S_RESULT_COUNTER_reg[1]_rep_n_0\,
      O => \SI_VALUE[279]_i_7_n_0\
    );
\SI_VALUE[34]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"80"
    )
        port map (
      I0 => \^s_enable_reg[0]\,
      I1 => \^q\(0),
      I2 => \^q\(1),
      O => \SI_VALUE[34]_i_1_n_0\
    );
\SI_VALUE[69]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"00000004"
    )
        port map (
      I0 => \S_RESULT_COUNTER_reg[1]_rep_n_0\,
      I1 => \S_RESULT_COUNTER_reg[0]_rep_n_0\,
      I2 => S_RESULT_COUNTER(3),
      I3 => S_RESULT_COUNTER(2),
      I4 => \SI_VALUE[279]_i_3_n_0\,
      O => p_1_in(69)
    );
\SI_VALUE_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \SI_VALUE[34]_i_1_n_0\,
      D => SI_VALUE0(0),
      Q => SI_VALUE(0),
      R => RSTP
    );
\SI_VALUE_reg[100]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(104),
      D => SI_VALUE0(228),
      Q => SI_VALUE(100),
      R => RSTP
    );
\SI_VALUE_reg[101]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(104),
      D => SI_VALUE0(229),
      Q => SI_VALUE(101),
      R => RSTP
    );
\SI_VALUE_reg[102]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(104),
      D => SI_VALUE0(230),
      Q => SI_VALUE(102),
      R => RSTP
    );
\SI_VALUE_reg[103]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(104),
      D => SI_VALUE0(231),
      Q => SI_VALUE(103),
      R => RSTP
    );
\SI_VALUE_reg[104]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(104),
      D => SI_VALUE0(232),
      Q => SI_VALUE(104),
      R => RSTP
    );
\SI_VALUE_reg[105]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(139),
      D => SI_VALUE0(105),
      Q => SI_VALUE(105),
      R => RSTP
    );
\SI_VALUE_reg[106]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(139),
      D => SI_VALUE0(106),
      Q => SI_VALUE(106),
      R => RSTP
    );
\SI_VALUE_reg[107]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(139),
      D => SI_VALUE0(107),
      Q => SI_VALUE(107),
      R => RSTP
    );
\SI_VALUE_reg[108]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(139),
      D => SI_VALUE0(108),
      Q => SI_VALUE(108),
      R => RSTP
    );
\SI_VALUE_reg[109]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(139),
      D => SI_VALUE0(109),
      Q => SI_VALUE(109),
      R => RSTP
    );
\SI_VALUE_reg[10]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \SI_VALUE[34]_i_1_n_0\,
      D => SI_VALUE0(10),
      Q => SI_VALUE(10),
      R => RSTP
    );
\SI_VALUE_reg[110]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(139),
      D => SI_VALUE0(110),
      Q => SI_VALUE(110),
      R => RSTP
    );
\SI_VALUE_reg[111]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(139),
      D => SI_VALUE0(111),
      Q => SI_VALUE(111),
      R => RSTP
    );
\SI_VALUE_reg[112]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(139),
      D => SI_VALUE0(112),
      Q => SI_VALUE(112),
      R => RSTP
    );
\SI_VALUE_reg[113]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(139),
      D => SI_VALUE0(113),
      Q => SI_VALUE(113),
      R => RSTP
    );
\SI_VALUE_reg[114]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(139),
      D => SI_VALUE0(114),
      Q => SI_VALUE(114),
      R => RSTP
    );
\SI_VALUE_reg[115]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(139),
      D => SI_VALUE0(115),
      Q => SI_VALUE(115),
      R => RSTP
    );
\SI_VALUE_reg[116]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(139),
      D => SI_VALUE0(116),
      Q => SI_VALUE(116),
      R => RSTP
    );
\SI_VALUE_reg[117]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(139),
      D => SI_VALUE0(117),
      Q => SI_VALUE(117),
      R => RSTP
    );
\SI_VALUE_reg[118]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(139),
      D => SI_VALUE0(118),
      Q => SI_VALUE(118),
      R => RSTP
    );
\SI_VALUE_reg[119]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(139),
      D => SI_VALUE0(119),
      Q => SI_VALUE(119),
      R => RSTP
    );
\SI_VALUE_reg[11]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \SI_VALUE[34]_i_1_n_0\,
      D => SI_VALUE0(11),
      Q => SI_VALUE(11),
      R => RSTP
    );
\SI_VALUE_reg[120]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(139),
      D => SI_VALUE0(120),
      Q => SI_VALUE(120),
      R => RSTP
    );
\SI_VALUE_reg[121]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(139),
      D => SI_VALUE0(121),
      Q => SI_VALUE(121),
      R => RSTP
    );
\SI_VALUE_reg[122]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(139),
      D => SI_VALUE0(122),
      Q => SI_VALUE(122),
      R => RSTP
    );
\SI_VALUE_reg[123]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(139),
      D => SI_VALUE0(123),
      Q => SI_VALUE(123),
      R => RSTP
    );
\SI_VALUE_reg[124]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(139),
      D => SI_VALUE0(124),
      Q => SI_VALUE(124),
      R => RSTP
    );
\SI_VALUE_reg[125]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(139),
      D => SI_VALUE0(125),
      Q => SI_VALUE(125),
      R => RSTP
    );
\SI_VALUE_reg[126]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(139),
      D => SI_VALUE0(126),
      Q => SI_VALUE(126),
      R => RSTP
    );
\SI_VALUE_reg[127]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(139),
      D => SI_VALUE0(127),
      Q => SI_VALUE(127),
      R => RSTP
    );
\SI_VALUE_reg[128]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(139),
      D => SI_VALUE0(128),
      Q => SI_VALUE(128),
      R => RSTP
    );
\SI_VALUE_reg[129]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(139),
      D => SI_VALUE0(129),
      Q => SI_VALUE(129),
      R => RSTP
    );
\SI_VALUE_reg[12]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \SI_VALUE[34]_i_1_n_0\,
      D => SI_VALUE0(12),
      Q => SI_VALUE(12),
      R => RSTP
    );
\SI_VALUE_reg[130]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(139),
      D => SI_VALUE0(130),
      Q => SI_VALUE(130),
      R => RSTP
    );
\SI_VALUE_reg[131]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(139),
      D => SI_VALUE0(131),
      Q => SI_VALUE(131),
      R => RSTP
    );
\SI_VALUE_reg[132]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(139),
      D => SI_VALUE0(132),
      Q => SI_VALUE(132),
      R => RSTP
    );
\SI_VALUE_reg[133]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(139),
      D => SI_VALUE0(133),
      Q => SI_VALUE(133),
      R => RSTP
    );
\SI_VALUE_reg[134]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(139),
      D => SI_VALUE0(134),
      Q => SI_VALUE(134),
      R => RSTP
    );
\SI_VALUE_reg[135]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(139),
      D => SI_VALUE0(135),
      Q => SI_VALUE(135),
      R => RSTP
    );
\SI_VALUE_reg[136]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(139),
      D => SI_VALUE0(136),
      Q => SI_VALUE(136),
      R => RSTP
    );
\SI_VALUE_reg[137]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(139),
      D => SI_VALUE0(137),
      Q => SI_VALUE(137),
      R => RSTP
    );
\SI_VALUE_reg[138]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(139),
      D => SI_VALUE0(138),
      Q => SI_VALUE(138),
      R => RSTP
    );
\SI_VALUE_reg[139]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(139),
      D => SI_VALUE0(139),
      Q => SI_VALUE(139),
      R => RSTP
    );
\SI_VALUE_reg[13]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \SI_VALUE[34]_i_1_n_0\,
      D => SI_VALUE0(13),
      Q => SI_VALUE(13),
      R => RSTP
    );
\SI_VALUE_reg[140]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(174),
      D => SI_VALUE0(76),
      Q => SI_VALUE(140),
      R => RSTP
    );
\SI_VALUE_reg[141]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(174),
      D => SI_VALUE0(77),
      Q => SI_VALUE(141),
      R => RSTP
    );
\SI_VALUE_reg[142]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(174),
      D => SI_VALUE0(78),
      Q => SI_VALUE(142),
      R => RSTP
    );
\SI_VALUE_reg[143]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(174),
      D => SI_VALUE0(143),
      Q => SI_VALUE(143),
      R => RSTP
    );
\SI_VALUE_reg[144]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(174),
      D => SI_VALUE0(144),
      Q => SI_VALUE(144),
      R => RSTP
    );
\SI_VALUE_reg[145]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(174),
      D => SI_VALUE0(145),
      Q => SI_VALUE(145),
      R => RSTP
    );
\SI_VALUE_reg[146]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(174),
      D => SI_VALUE0(146),
      Q => SI_VALUE(146),
      R => RSTP
    );
\SI_VALUE_reg[147]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(174),
      D => SI_VALUE0(147),
      Q => SI_VALUE(147),
      R => RSTP
    );
\SI_VALUE_reg[148]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(174),
      D => SI_VALUE0(148),
      Q => SI_VALUE(148),
      R => RSTP
    );
\SI_VALUE_reg[149]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(174),
      D => SI_VALUE0(213),
      Q => SI_VALUE(149),
      R => RSTP
    );
\SI_VALUE_reg[14]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \SI_VALUE[34]_i_1_n_0\,
      D => SI_VALUE0(14),
      Q => SI_VALUE(14),
      R => RSTP
    );
\SI_VALUE_reg[150]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(174),
      D => SI_VALUE0(214),
      Q => SI_VALUE(150),
      R => RSTP
    );
\SI_VALUE_reg[151]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(174),
      D => SI_VALUE0(215),
      Q => SI_VALUE(151),
      R => RSTP
    );
\SI_VALUE_reg[152]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(174),
      D => SI_VALUE0(216),
      Q => SI_VALUE(152),
      R => RSTP
    );
\SI_VALUE_reg[153]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(174),
      D => SI_VALUE0(217),
      Q => SI_VALUE(153),
      R => RSTP
    );
\SI_VALUE_reg[154]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(174),
      D => SI_VALUE0(218),
      Q => SI_VALUE(154),
      R => RSTP
    );
\SI_VALUE_reg[155]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(174),
      D => SI_VALUE0(219),
      Q => SI_VALUE(155),
      R => RSTP
    );
\SI_VALUE_reg[156]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(174),
      D => SI_VALUE0(220),
      Q => SI_VALUE(156),
      R => RSTP
    );
\SI_VALUE_reg[157]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(174),
      D => SI_VALUE0(221),
      Q => SI_VALUE(157),
      R => RSTP
    );
\SI_VALUE_reg[158]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(174),
      D => SI_VALUE0(222),
      Q => SI_VALUE(158),
      R => RSTP
    );
\SI_VALUE_reg[159]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(174),
      D => SI_VALUE0(191),
      Q => SI_VALUE(159),
      R => RSTP
    );
\SI_VALUE_reg[15]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \SI_VALUE[34]_i_1_n_0\,
      D => SI_VALUE0(15),
      Q => SI_VALUE(15),
      R => RSTP
    );
\SI_VALUE_reg[160]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(174),
      D => SI_VALUE0(192),
      Q => SI_VALUE(160),
      R => RSTP
    );
\SI_VALUE_reg[161]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(174),
      D => SI_VALUE0(225),
      Q => SI_VALUE(161),
      R => RSTP
    );
\SI_VALUE_reg[162]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(174),
      D => SI_VALUE0(226),
      Q => SI_VALUE(162),
      R => RSTP
    );
\SI_VALUE_reg[163]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(174),
      D => SI_VALUE0(227),
      Q => SI_VALUE(163),
      R => RSTP
    );
\SI_VALUE_reg[164]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(174),
      D => SI_VALUE0(228),
      Q => SI_VALUE(164),
      R => RSTP
    );
\SI_VALUE_reg[165]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(174),
      D => SI_VALUE0(229),
      Q => SI_VALUE(165),
      R => RSTP
    );
\SI_VALUE_reg[166]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(174),
      D => SI_VALUE0(230),
      Q => SI_VALUE(166),
      R => RSTP
    );
\SI_VALUE_reg[167]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(174),
      D => SI_VALUE0(231),
      Q => SI_VALUE(167),
      R => RSTP
    );
\SI_VALUE_reg[168]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(174),
      D => SI_VALUE0(232),
      Q => SI_VALUE(168),
      R => RSTP
    );
\SI_VALUE_reg[169]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(174),
      D => SI_VALUE0(233),
      Q => SI_VALUE(169),
      R => RSTP
    );
\SI_VALUE_reg[16]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \SI_VALUE[34]_i_1_n_0\,
      D => SI_VALUE0(16),
      Q => SI_VALUE(16),
      R => RSTP
    );
\SI_VALUE_reg[170]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(174),
      D => SI_VALUE0(234),
      Q => SI_VALUE(170),
      R => RSTP
    );
\SI_VALUE_reg[171]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(174),
      D => SI_VALUE0(235),
      Q => SI_VALUE(171),
      R => RSTP
    );
\SI_VALUE_reg[172]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(174),
      D => SI_VALUE0(236),
      Q => SI_VALUE(172),
      R => RSTP
    );
\SI_VALUE_reg[173]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(174),
      D => SI_VALUE0(237),
      Q => SI_VALUE(173),
      R => RSTP
    );
\SI_VALUE_reg[174]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(174),
      D => SI_VALUE0(238),
      Q => SI_VALUE(174),
      R => RSTP
    );
\SI_VALUE_reg[175]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(209),
      D => SI_VALUE0(143),
      Q => SI_VALUE(175),
      R => RSTP
    );
\SI_VALUE_reg[176]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(209),
      D => SI_VALUE0(144),
      Q => SI_VALUE(176),
      R => RSTP
    );
\SI_VALUE_reg[177]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(209),
      D => SI_VALUE0(145),
      Q => SI_VALUE(177),
      R => RSTP
    );
\SI_VALUE_reg[178]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(209),
      D => SI_VALUE0(146),
      Q => SI_VALUE(178),
      R => RSTP
    );
\SI_VALUE_reg[179]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(209),
      D => SI_VALUE0(147),
      Q => SI_VALUE(179),
      R => RSTP
    );
\SI_VALUE_reg[17]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \SI_VALUE[34]_i_1_n_0\,
      D => SI_VALUE0(17),
      Q => SI_VALUE(17),
      R => RSTP
    );
\SI_VALUE_reg[180]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(209),
      D => SI_VALUE0(148),
      Q => SI_VALUE(180),
      R => RSTP
    );
\SI_VALUE_reg[181]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(209),
      D => SI_VALUE0(213),
      Q => SI_VALUE(181),
      R => RSTP
    );
\SI_VALUE_reg[182]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(209),
      D => SI_VALUE0(214),
      Q => SI_VALUE(182),
      R => RSTP
    );
\SI_VALUE_reg[183]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(209),
      D => SI_VALUE0(215),
      Q => SI_VALUE(183),
      R => RSTP
    );
\SI_VALUE_reg[184]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(209),
      D => SI_VALUE0(216),
      Q => SI_VALUE(184),
      R => RSTP
    );
\SI_VALUE_reg[185]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(209),
      D => SI_VALUE0(217),
      Q => SI_VALUE(185),
      R => RSTP
    );
\SI_VALUE_reg[186]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(209),
      D => SI_VALUE0(218),
      Q => SI_VALUE(186),
      R => RSTP
    );
\SI_VALUE_reg[187]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(209),
      D => SI_VALUE0(219),
      Q => SI_VALUE(187),
      R => RSTP
    );
\SI_VALUE_reg[188]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(209),
      D => SI_VALUE0(220),
      Q => SI_VALUE(188),
      R => RSTP
    );
\SI_VALUE_reg[189]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(209),
      D => SI_VALUE0(221),
      Q => SI_VALUE(189),
      R => RSTP
    );
\SI_VALUE_reg[18]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \SI_VALUE[34]_i_1_n_0\,
      D => SI_VALUE0(18),
      Q => SI_VALUE(18),
      R => RSTP
    );
\SI_VALUE_reg[190]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(209),
      D => SI_VALUE0(222),
      Q => SI_VALUE(190),
      R => RSTP
    );
\SI_VALUE_reg[191]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(209),
      D => SI_VALUE0(191),
      Q => SI_VALUE(191),
      R => RSTP
    );
\SI_VALUE_reg[192]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(209),
      D => SI_VALUE0(192),
      Q => SI_VALUE(192),
      R => RSTP
    );
\SI_VALUE_reg[193]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(209),
      D => SI_VALUE0(225),
      Q => SI_VALUE(193),
      R => RSTP
    );
\SI_VALUE_reg[194]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(209),
      D => SI_VALUE0(226),
      Q => SI_VALUE(194),
      R => RSTP
    );
\SI_VALUE_reg[195]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(209),
      D => SI_VALUE0(227),
      Q => SI_VALUE(195),
      R => RSTP
    );
\SI_VALUE_reg[196]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(209),
      D => SI_VALUE0(228),
      Q => SI_VALUE(196),
      R => RSTP
    );
\SI_VALUE_reg[197]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(209),
      D => SI_VALUE0(229),
      Q => SI_VALUE(197),
      R => RSTP
    );
\SI_VALUE_reg[198]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(209),
      D => SI_VALUE0(230),
      Q => SI_VALUE(198),
      R => RSTP
    );
\SI_VALUE_reg[199]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(209),
      D => SI_VALUE0(231),
      Q => SI_VALUE(199),
      R => RSTP
    );
\SI_VALUE_reg[19]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \SI_VALUE[34]_i_1_n_0\,
      D => SI_VALUE0(19),
      Q => SI_VALUE(19),
      R => RSTP
    );
\SI_VALUE_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \SI_VALUE[34]_i_1_n_0\,
      D => SI_VALUE0(1),
      Q => SI_VALUE(1),
      R => RSTP
    );
\SI_VALUE_reg[200]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(209),
      D => SI_VALUE0(232),
      Q => SI_VALUE(200),
      R => RSTP
    );
\SI_VALUE_reg[201]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(209),
      D => SI_VALUE0(233),
      Q => SI_VALUE(201),
      R => RSTP
    );
\SI_VALUE_reg[202]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(209),
      D => SI_VALUE0(234),
      Q => SI_VALUE(202),
      R => RSTP
    );
\SI_VALUE_reg[203]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(209),
      D => SI_VALUE0(235),
      Q => SI_VALUE(203),
      R => RSTP
    );
\SI_VALUE_reg[204]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(209),
      D => SI_VALUE0(236),
      Q => SI_VALUE(204),
      R => RSTP
    );
\SI_VALUE_reg[205]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(209),
      D => SI_VALUE0(237),
      Q => SI_VALUE(205),
      R => RSTP
    );
\SI_VALUE_reg[206]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(209),
      D => SI_VALUE0(238),
      Q => SI_VALUE(206),
      R => RSTP
    );
\SI_VALUE_reg[207]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(209),
      D => raw_to_si_n_1,
      Q => SI_VALUE(207),
      R => RSTP
    );
\SI_VALUE_reg[208]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(209),
      D => S_RESULT_S_C(33),
      Q => SI_VALUE(208),
      R => RSTP
    );
\SI_VALUE_reg[209]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(209),
      D => SI_VALUE0(209),
      Q => SI_VALUE(209),
      R => RSTP
    );
\SI_VALUE_reg[20]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \SI_VALUE[34]_i_1_n_0\,
      D => SI_VALUE0(20),
      Q => SI_VALUE(20),
      R => RSTP
    );
\SI_VALUE_reg[210]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(244),
      D => SI_VALUE0(210),
      Q => SI_VALUE(210),
      R => RSTP
    );
\SI_VALUE_reg[211]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(244),
      D => SI_VALUE0(211),
      Q => SI_VALUE(211),
      R => RSTP
    );
\SI_VALUE_reg[212]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(244),
      D => SI_VALUE0(36),
      Q => SI_VALUE(212),
      R => RSTP
    );
\SI_VALUE_reg[213]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(244),
      D => SI_VALUE0(213),
      Q => SI_VALUE(213),
      R => RSTP
    );
\SI_VALUE_reg[214]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(244),
      D => SI_VALUE0(214),
      Q => SI_VALUE(214),
      R => RSTP
    );
\SI_VALUE_reg[215]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(244),
      D => SI_VALUE0(215),
      Q => SI_VALUE(215),
      R => RSTP
    );
\SI_VALUE_reg[216]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(244),
      D => SI_VALUE0(216),
      Q => SI_VALUE(216),
      R => RSTP
    );
\SI_VALUE_reg[217]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(244),
      D => SI_VALUE0(217),
      Q => SI_VALUE(217),
      R => RSTP
    );
\SI_VALUE_reg[218]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(244),
      D => SI_VALUE0(218),
      Q => SI_VALUE(218),
      R => RSTP
    );
\SI_VALUE_reg[219]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(244),
      D => SI_VALUE0(219),
      Q => SI_VALUE(219),
      R => RSTP
    );
\SI_VALUE_reg[21]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \SI_VALUE[34]_i_1_n_0\,
      D => SI_VALUE0(21),
      Q => SI_VALUE(21),
      R => RSTP
    );
\SI_VALUE_reg[220]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(244),
      D => SI_VALUE0(220),
      Q => SI_VALUE(220),
      R => RSTP
    );
\SI_VALUE_reg[221]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(244),
      D => SI_VALUE0(221),
      Q => SI_VALUE(221),
      R => RSTP
    );
\SI_VALUE_reg[222]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(244),
      D => SI_VALUE0(222),
      Q => SI_VALUE(222),
      R => RSTP
    );
\SI_VALUE_reg[223]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(244),
      D => SI_VALUE0(191),
      Q => SI_VALUE(223),
      R => RSTP
    );
\SI_VALUE_reg[224]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(244),
      D => SI_VALUE0(192),
      Q => SI_VALUE(224),
      R => RSTP
    );
\SI_VALUE_reg[225]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(244),
      D => SI_VALUE0(225),
      Q => SI_VALUE(225),
      R => RSTP
    );
\SI_VALUE_reg[226]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(244),
      D => SI_VALUE0(226),
      Q => SI_VALUE(226),
      R => RSTP
    );
\SI_VALUE_reg[227]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(244),
      D => SI_VALUE0(227),
      Q => SI_VALUE(227),
      R => RSTP
    );
\SI_VALUE_reg[228]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(244),
      D => SI_VALUE0(228),
      Q => SI_VALUE(228),
      R => RSTP
    );
\SI_VALUE_reg[229]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(244),
      D => SI_VALUE0(229),
      Q => SI_VALUE(229),
      R => RSTP
    );
\SI_VALUE_reg[22]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \SI_VALUE[34]_i_1_n_0\,
      D => SI_VALUE0(22),
      Q => SI_VALUE(22),
      R => RSTP
    );
\SI_VALUE_reg[230]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(244),
      D => SI_VALUE0(230),
      Q => SI_VALUE(230),
      R => RSTP
    );
\SI_VALUE_reg[231]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(244),
      D => SI_VALUE0(231),
      Q => SI_VALUE(231),
      R => RSTP
    );
\SI_VALUE_reg[232]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(244),
      D => SI_VALUE0(232),
      Q => SI_VALUE(232),
      R => RSTP
    );
\SI_VALUE_reg[233]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(244),
      D => SI_VALUE0(233),
      Q => SI_VALUE(233),
      R => RSTP
    );
\SI_VALUE_reg[234]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(244),
      D => SI_VALUE0(234),
      Q => SI_VALUE(234),
      R => RSTP
    );
\SI_VALUE_reg[235]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(244),
      D => SI_VALUE0(235),
      Q => SI_VALUE(235),
      R => RSTP
    );
\SI_VALUE_reg[236]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(244),
      D => SI_VALUE0(236),
      Q => SI_VALUE(236),
      R => RSTP
    );
\SI_VALUE_reg[237]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(244),
      D => SI_VALUE0(237),
      Q => SI_VALUE(237),
      R => RSTP
    );
\SI_VALUE_reg[238]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(244),
      D => SI_VALUE0(238),
      Q => SI_VALUE(238),
      R => RSTP
    );
\SI_VALUE_reg[239]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(244),
      D => SI_VALUE0(239),
      Q => SI_VALUE(239),
      R => RSTP
    );
\SI_VALUE_reg[23]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \SI_VALUE[34]_i_1_n_0\,
      D => SI_VALUE0(23),
      Q => SI_VALUE(23),
      R => RSTP
    );
\SI_VALUE_reg[240]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(244),
      D => SI_VALUE0(240),
      Q => SI_VALUE(240),
      R => RSTP
    );
\SI_VALUE_reg[241]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(244),
      D => SI_VALUE0(241),
      Q => SI_VALUE(241),
      R => RSTP
    );
\SI_VALUE_reg[242]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(244),
      D => SI_VALUE0(242),
      Q => SI_VALUE(242),
      R => RSTP
    );
\SI_VALUE_reg[243]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(244),
      D => SI_VALUE0(243),
      Q => SI_VALUE(243),
      R => RSTP
    );
\SI_VALUE_reg[244]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(244),
      D => SI_VALUE0(244),
      Q => SI_VALUE(244),
      R => RSTP
    );
\SI_VALUE_reg[245]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(279),
      D => SI_VALUE0(213),
      Q => SI_VALUE(245),
      R => RSTP
    );
\SI_VALUE_reg[246]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(279),
      D => SI_VALUE0(214),
      Q => SI_VALUE(246),
      R => RSTP
    );
\SI_VALUE_reg[247]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(279),
      D => SI_VALUE0(215),
      Q => SI_VALUE(247),
      R => RSTP
    );
\SI_VALUE_reg[248]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(279),
      D => SI_VALUE0(216),
      Q => SI_VALUE(248),
      R => RSTP
    );
\SI_VALUE_reg[249]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(279),
      D => SI_VALUE0(217),
      Q => SI_VALUE(249),
      R => RSTP
    );
\SI_VALUE_reg[24]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \SI_VALUE[34]_i_1_n_0\,
      D => SI_VALUE0(24),
      Q => SI_VALUE(24),
      R => RSTP
    );
\SI_VALUE_reg[250]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(279),
      D => SI_VALUE0(218),
      Q => SI_VALUE(250),
      R => RSTP
    );
\SI_VALUE_reg[251]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(279),
      D => SI_VALUE0(219),
      Q => SI_VALUE(251),
      R => RSTP
    );
\SI_VALUE_reg[252]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(279),
      D => SI_VALUE0(220),
      Q => SI_VALUE(252),
      R => RSTP
    );
\SI_VALUE_reg[253]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(279),
      D => SI_VALUE0(221),
      Q => SI_VALUE(253),
      R => RSTP
    );
\SI_VALUE_reg[254]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(279),
      D => SI_VALUE0(222),
      Q => SI_VALUE(254),
      R => RSTP
    );
\SI_VALUE_reg[255]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(279),
      D => SI_VALUE0(255),
      Q => SI_VALUE(255),
      R => RSTP
    );
\SI_VALUE_reg[256]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(279),
      D => SI_VALUE0(256),
      Q => SI_VALUE(256),
      R => RSTP
    );
\SI_VALUE_reg[257]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(279),
      D => SI_VALUE0(225),
      Q => SI_VALUE(257),
      R => RSTP
    );
\SI_VALUE_reg[258]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(279),
      D => SI_VALUE0(226),
      Q => SI_VALUE(258),
      R => RSTP
    );
\SI_VALUE_reg[259]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(279),
      D => SI_VALUE0(227),
      Q => SI_VALUE(259),
      R => RSTP
    );
\SI_VALUE_reg[25]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \SI_VALUE[34]_i_1_n_0\,
      D => SI_VALUE0(25),
      Q => SI_VALUE(25),
      R => RSTP
    );
\SI_VALUE_reg[260]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(279),
      D => SI_VALUE0(228),
      Q => SI_VALUE(260),
      R => RSTP
    );
\SI_VALUE_reg[261]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(279),
      D => SI_VALUE0(229),
      Q => SI_VALUE(261),
      R => RSTP
    );
\SI_VALUE_reg[262]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(279),
      D => SI_VALUE0(230),
      Q => SI_VALUE(262),
      R => RSTP
    );
\SI_VALUE_reg[263]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(279),
      D => SI_VALUE0(231),
      Q => SI_VALUE(263),
      R => RSTP
    );
\SI_VALUE_reg[264]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(279),
      D => SI_VALUE0(232),
      Q => SI_VALUE(264),
      R => RSTP
    );
\SI_VALUE_reg[265]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(279),
      D => SI_VALUE0(233),
      Q => SI_VALUE(265),
      R => RSTP
    );
\SI_VALUE_reg[266]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(279),
      D => SI_VALUE0(234),
      Q => SI_VALUE(266),
      R => RSTP
    );
\SI_VALUE_reg[267]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(279),
      D => SI_VALUE0(235),
      Q => SI_VALUE(267),
      R => RSTP
    );
\SI_VALUE_reg[268]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(279),
      D => SI_VALUE0(236),
      Q => SI_VALUE(268),
      R => RSTP
    );
\SI_VALUE_reg[269]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(279),
      D => SI_VALUE0(237),
      Q => SI_VALUE(269),
      R => RSTP
    );
\SI_VALUE_reg[26]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \SI_VALUE[34]_i_1_n_0\,
      D => SI_VALUE0(26),
      Q => SI_VALUE(26),
      R => RSTP
    );
\SI_VALUE_reg[270]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(279),
      D => SI_VALUE0(238),
      Q => SI_VALUE(270),
      R => RSTP
    );
\SI_VALUE_reg[271]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(279),
      D => SI_VALUE0(239),
      Q => SI_VALUE(271),
      R => RSTP
    );
\SI_VALUE_reg[272]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(279),
      D => SI_VALUE0(240),
      Q => SI_VALUE(272),
      R => RSTP
    );
\SI_VALUE_reg[273]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(279),
      D => SI_VALUE0(241),
      Q => SI_VALUE(273),
      R => RSTP
    );
\SI_VALUE_reg[274]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(279),
      D => SI_VALUE0(242),
      Q => SI_VALUE(274),
      R => RSTP
    );
\SI_VALUE_reg[275]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(279),
      D => SI_VALUE0(243),
      Q => SI_VALUE(275),
      R => RSTP
    );
\SI_VALUE_reg[276]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(279),
      D => SI_VALUE0(244),
      Q => SI_VALUE(276),
      R => RSTP
    );
\SI_VALUE_reg[277]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(279),
      D => SI_VALUE0(277),
      Q => SI_VALUE(277),
      R => RSTP
    );
\SI_VALUE_reg[278]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(279),
      D => SI_VALUE0(278),
      Q => SI_VALUE(278),
      R => RSTP
    );
\SI_VALUE_reg[279]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(279),
      D => SI_VALUE0(279),
      Q => SI_VALUE(279),
      R => RSTP
    );
\SI_VALUE_reg[27]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \SI_VALUE[34]_i_1_n_0\,
      D => SI_VALUE0(27),
      Q => SI_VALUE(27),
      R => RSTP
    );
\SI_VALUE_reg[28]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \SI_VALUE[34]_i_1_n_0\,
      D => SI_VALUE0(28),
      Q => SI_VALUE(28),
      R => RSTP
    );
\SI_VALUE_reg[29]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \SI_VALUE[34]_i_1_n_0\,
      D => SI_VALUE0(29),
      Q => SI_VALUE(29),
      R => RSTP
    );
\SI_VALUE_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \SI_VALUE[34]_i_1_n_0\,
      D => SI_VALUE0(2),
      Q => SI_VALUE(2),
      R => RSTP
    );
\SI_VALUE_reg[30]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \SI_VALUE[34]_i_1_n_0\,
      D => SI_VALUE0(30),
      Q => SI_VALUE(30),
      R => RSTP
    );
\SI_VALUE_reg[31]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \SI_VALUE[34]_i_1_n_0\,
      D => SI_VALUE0(31),
      Q => SI_VALUE(31),
      R => RSTP
    );
\SI_VALUE_reg[32]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \SI_VALUE[34]_i_1_n_0\,
      D => SI_VALUE0(32),
      Q => SI_VALUE(32),
      R => RSTP
    );
\SI_VALUE_reg[33]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \SI_VALUE[34]_i_1_n_0\,
      D => SI_VALUE0(33),
      Q => SI_VALUE(33),
      R => RSTP
    );
\SI_VALUE_reg[34]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \SI_VALUE[34]_i_1_n_0\,
      D => SI_VALUE0(34),
      Q => SI_VALUE(34),
      R => RSTP
    );
\SI_VALUE_reg[35]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(69),
      D => SI_VALUE0(35),
      Q => SI_VALUE(35),
      R => RSTP
    );
\SI_VALUE_reg[36]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(69),
      D => SI_VALUE0(36),
      Q => SI_VALUE(36),
      R => RSTP
    );
\SI_VALUE_reg[37]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(69),
      D => SI_VALUE0(37),
      Q => SI_VALUE(37),
      R => RSTP
    );
\SI_VALUE_reg[38]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(69),
      D => SI_VALUE0(38),
      Q => SI_VALUE(38),
      R => RSTP
    );
\SI_VALUE_reg[39]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(69),
      D => SI_VALUE0(39),
      Q => SI_VALUE(39),
      R => RSTP
    );
\SI_VALUE_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \SI_VALUE[34]_i_1_n_0\,
      D => SI_VALUE0(3),
      Q => SI_VALUE(3),
      R => RSTP
    );
\SI_VALUE_reg[40]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(69),
      D => SI_VALUE0(40),
      Q => SI_VALUE(40),
      R => RSTP
    );
\SI_VALUE_reg[41]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(69),
      D => SI_VALUE0(41),
      Q => SI_VALUE(41),
      R => RSTP
    );
\SI_VALUE_reg[42]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(69),
      D => SI_VALUE0(42),
      Q => SI_VALUE(42),
      R => RSTP
    );
\SI_VALUE_reg[43]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(69),
      D => SI_VALUE0(43),
      Q => SI_VALUE(43),
      R => RSTP
    );
\SI_VALUE_reg[44]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(69),
      D => SI_VALUE0(76),
      Q => SI_VALUE(44),
      R => RSTP
    );
\SI_VALUE_reg[45]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(69),
      D => SI_VALUE0(77),
      Q => SI_VALUE(45),
      R => RSTP
    );
\SI_VALUE_reg[46]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(69),
      D => SI_VALUE0(78),
      Q => SI_VALUE(46),
      R => RSTP
    );
\SI_VALUE_reg[47]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(69),
      D => SI_VALUE0(143),
      Q => SI_VALUE(47),
      R => RSTP
    );
\SI_VALUE_reg[48]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(69),
      D => SI_VALUE0(144),
      Q => SI_VALUE(48),
      R => RSTP
    );
\SI_VALUE_reg[49]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(69),
      D => SI_VALUE0(145),
      Q => SI_VALUE(49),
      R => RSTP
    );
\SI_VALUE_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \SI_VALUE[34]_i_1_n_0\,
      D => SI_VALUE0(4),
      Q => SI_VALUE(4),
      R => RSTP
    );
\SI_VALUE_reg[50]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(69),
      D => SI_VALUE0(146),
      Q => SI_VALUE(50),
      R => RSTP
    );
\SI_VALUE_reg[51]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(69),
      D => SI_VALUE0(147),
      Q => SI_VALUE(51),
      R => RSTP
    );
\SI_VALUE_reg[52]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(69),
      D => SI_VALUE0(148),
      Q => SI_VALUE(52),
      R => RSTP
    );
\SI_VALUE_reg[53]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(69),
      D => SI_VALUE0(213),
      Q => SI_VALUE(53),
      R => RSTP
    );
\SI_VALUE_reg[54]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(69),
      D => SI_VALUE0(214),
      Q => SI_VALUE(54),
      R => RSTP
    );
\SI_VALUE_reg[55]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(69),
      D => SI_VALUE0(215),
      Q => SI_VALUE(55),
      R => RSTP
    );
\SI_VALUE_reg[56]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(69),
      D => SI_VALUE0(216),
      Q => SI_VALUE(56),
      R => RSTP
    );
\SI_VALUE_reg[57]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(69),
      D => SI_VALUE0(217),
      Q => SI_VALUE(57),
      R => RSTP
    );
\SI_VALUE_reg[58]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(69),
      D => SI_VALUE0(218),
      Q => SI_VALUE(58),
      R => RSTP
    );
\SI_VALUE_reg[59]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(69),
      D => SI_VALUE0(219),
      Q => SI_VALUE(59),
      R => RSTP
    );
\SI_VALUE_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \SI_VALUE[34]_i_1_n_0\,
      D => SI_VALUE0(5),
      Q => SI_VALUE(5),
      R => RSTP
    );
\SI_VALUE_reg[60]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(69),
      D => SI_VALUE0(220),
      Q => SI_VALUE(60),
      R => RSTP
    );
\SI_VALUE_reg[61]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(69),
      D => SI_VALUE0(221),
      Q => SI_VALUE(61),
      R => RSTP
    );
\SI_VALUE_reg[62]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(69),
      D => SI_VALUE0(222),
      Q => SI_VALUE(62),
      R => RSTP
    );
\SI_VALUE_reg[63]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(69),
      D => SI_VALUE0(191),
      Q => SI_VALUE(63),
      R => RSTP
    );
\SI_VALUE_reg[64]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(69),
      D => SI_VALUE0(192),
      Q => SI_VALUE(64),
      R => RSTP
    );
\SI_VALUE_reg[65]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(69),
      D => SI_VALUE0(225),
      Q => SI_VALUE(65),
      R => RSTP
    );
\SI_VALUE_reg[66]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(69),
      D => SI_VALUE0(226),
      Q => SI_VALUE(66),
      R => RSTP
    );
\SI_VALUE_reg[67]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(69),
      D => SI_VALUE0(227),
      Q => SI_VALUE(67),
      R => RSTP
    );
\SI_VALUE_reg[68]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(69),
      D => SI_VALUE0(228),
      Q => SI_VALUE(68),
      R => RSTP
    );
\SI_VALUE_reg[69]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(69),
      D => SI_VALUE0(229),
      Q => SI_VALUE(69),
      R => RSTP
    );
\SI_VALUE_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \SI_VALUE[34]_i_1_n_0\,
      D => SI_VALUE0(6),
      Q => SI_VALUE(6),
      R => RSTP
    );
\SI_VALUE_reg[70]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(104),
      D => SI_VALUE0(38),
      Q => SI_VALUE(70),
      R => RSTP
    );
\SI_VALUE_reg[71]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(104),
      D => SI_VALUE0(39),
      Q => SI_VALUE(71),
      R => RSTP
    );
\SI_VALUE_reg[72]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(104),
      D => SI_VALUE0(40),
      Q => SI_VALUE(72),
      R => RSTP
    );
\SI_VALUE_reg[73]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(104),
      D => SI_VALUE0(41),
      Q => SI_VALUE(73),
      R => RSTP
    );
\SI_VALUE_reg[74]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(104),
      D => SI_VALUE0(42),
      Q => SI_VALUE(74),
      R => RSTP
    );
\SI_VALUE_reg[75]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(104),
      D => SI_VALUE0(43),
      Q => SI_VALUE(75),
      R => RSTP
    );
\SI_VALUE_reg[76]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(104),
      D => SI_VALUE0(76),
      Q => SI_VALUE(76),
      R => RSTP
    );
\SI_VALUE_reg[77]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(104),
      D => SI_VALUE0(77),
      Q => SI_VALUE(77),
      R => RSTP
    );
\SI_VALUE_reg[78]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(104),
      D => SI_VALUE0(78),
      Q => SI_VALUE(78),
      R => RSTP
    );
\SI_VALUE_reg[79]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(104),
      D => SI_VALUE0(143),
      Q => SI_VALUE(79),
      R => RSTP
    );
\SI_VALUE_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \SI_VALUE[34]_i_1_n_0\,
      D => SI_VALUE0(7),
      Q => SI_VALUE(7),
      R => RSTP
    );
\SI_VALUE_reg[80]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(104),
      D => SI_VALUE0(144),
      Q => SI_VALUE(80),
      R => RSTP
    );
\SI_VALUE_reg[81]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(104),
      D => SI_VALUE0(145),
      Q => SI_VALUE(81),
      R => RSTP
    );
\SI_VALUE_reg[82]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(104),
      D => SI_VALUE0(146),
      Q => SI_VALUE(82),
      R => RSTP
    );
\SI_VALUE_reg[83]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(104),
      D => SI_VALUE0(147),
      Q => SI_VALUE(83),
      R => RSTP
    );
\SI_VALUE_reg[84]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(104),
      D => SI_VALUE0(148),
      Q => SI_VALUE(84),
      R => RSTP
    );
\SI_VALUE_reg[85]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(104),
      D => SI_VALUE0(213),
      Q => SI_VALUE(85),
      R => RSTP
    );
\SI_VALUE_reg[86]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(104),
      D => SI_VALUE0(214),
      Q => SI_VALUE(86),
      R => RSTP
    );
\SI_VALUE_reg[87]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(104),
      D => SI_VALUE0(215),
      Q => SI_VALUE(87),
      R => RSTP
    );
\SI_VALUE_reg[88]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(104),
      D => SI_VALUE0(216),
      Q => SI_VALUE(88),
      R => RSTP
    );
\SI_VALUE_reg[89]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(104),
      D => SI_VALUE0(217),
      Q => SI_VALUE(89),
      R => RSTP
    );
\SI_VALUE_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \SI_VALUE[34]_i_1_n_0\,
      D => SI_VALUE0(8),
      Q => SI_VALUE(8),
      R => RSTP
    );
\SI_VALUE_reg[90]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(104),
      D => SI_VALUE0(218),
      Q => SI_VALUE(90),
      R => RSTP
    );
\SI_VALUE_reg[91]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(104),
      D => SI_VALUE0(219),
      Q => SI_VALUE(91),
      R => RSTP
    );
\SI_VALUE_reg[92]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(104),
      D => SI_VALUE0(220),
      Q => SI_VALUE(92),
      R => RSTP
    );
\SI_VALUE_reg[93]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(104),
      D => SI_VALUE0(221),
      Q => SI_VALUE(93),
      R => RSTP
    );
\SI_VALUE_reg[94]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(104),
      D => SI_VALUE0(222),
      Q => SI_VALUE(94),
      R => RSTP
    );
\SI_VALUE_reg[95]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(104),
      D => SI_VALUE0(191),
      Q => SI_VALUE(95),
      R => RSTP
    );
\SI_VALUE_reg[96]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(104),
      D => SI_VALUE0(192),
      Q => SI_VALUE(96),
      R => RSTP
    );
\SI_VALUE_reg[97]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(104),
      D => SI_VALUE0(225),
      Q => SI_VALUE(97),
      R => RSTP
    );
\SI_VALUE_reg[98]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(104),
      D => SI_VALUE0(226),
      Q => SI_VALUE(98),
      R => RSTP
    );
\SI_VALUE_reg[99]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => p_1_in(104),
      D => SI_VALUE0(227),
      Q => SI_VALUE(99),
      R => RSTP
    );
\SI_VALUE_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \SI_VALUE[34]_i_1_n_0\,
      D => SI_VALUE0(9),
      Q => SI_VALUE(9),
      R => RSTP
    );
S_CE_CONVERSION_reg: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => SI_VALID_i_1_n_0,
      D => nxtstate(1),
      Q => S_CE_CONVERSION,
      R => RSTP
    );
\S_CHANNEL_COUNTER[0]_i_1\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => S_CHANNEL_COUNTER(0),
      I1 => \^s_enable_reg[0]_0\,
      O => \S_CHANNEL_COUNTER[0]_i_1_n_0\
    );
\S_CHANNEL_COUNTER[1]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"09"
    )
        port map (
      I0 => S_CHANNEL_COUNTER(1),
      I1 => S_CHANNEL_COUNTER(0),
      I2 => \^s_enable_reg[0]_0\,
      O => \S_CHANNEL_COUNTER[1]_i_1_n_0\
    );
\S_CHANNEL_COUNTER[2]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"00E1"
    )
        port map (
      I0 => S_CHANNEL_COUNTER(0),
      I1 => S_CHANNEL_COUNTER(1),
      I2 => S_CHANNEL_COUNTER(2),
      I3 => \^s_enable_reg[0]_0\,
      O => \S_CHANNEL_COUNTER[2]_i_1_n_0\
    );
\S_CHANNEL_COUNTER[3]_i_1\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"B"
    )
        port map (
      I0 => S_OFFSET_S_C,
      I1 => \^s_enable_reg[0]_1\,
      O => \S_CHANNEL_COUNTER[3]_i_1_n_0\
    );
\S_CHANNEL_COUNTER[3]_i_2\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFFEAAAB"
    )
        port map (
      I0 => \^s_enable_reg[0]_0\,
      I1 => S_CHANNEL_COUNTER(1),
      I2 => S_CHANNEL_COUNTER(0),
      I3 => S_CHANNEL_COUNTER(2),
      I4 => S_CHANNEL_COUNTER(3),
      O => \S_CHANNEL_COUNTER[3]_i_2_n_0\
    );
\S_CHANNEL_COUNTER[3]_i_3\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FEFFFEFFFFFFFEFF"
    )
        port map (
      I0 => \S_SAMPLE_TIME_COUNTER[30]_i_7_n_0\,
      I1 => \S_SAMPLE_TIME_COUNTER[30]_i_6_n_0\,
      I2 => raw_to_si_n_133,
      I3 => raw_to_si_n_134,
      I4 => nxtstate22_in,
      I5 => ENABLE,
      O => \^s_enable_reg[0]_1\
    );
\S_CHANNEL_COUNTER_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_CHANNEL_COUNTER[3]_i_1_n_0\,
      D => \S_CHANNEL_COUNTER[0]_i_1_n_0\,
      Q => S_CHANNEL_COUNTER(0),
      R => RSTP
    );
\S_CHANNEL_COUNTER_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_CHANNEL_COUNTER[3]_i_1_n_0\,
      D => \S_CHANNEL_COUNTER[1]_i_1_n_0\,
      Q => S_CHANNEL_COUNTER(1),
      R => RSTP
    );
\S_CHANNEL_COUNTER_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_CHANNEL_COUNTER[3]_i_1_n_0\,
      D => \S_CHANNEL_COUNTER[2]_i_1_n_0\,
      Q => S_CHANNEL_COUNTER(2),
      R => RSTP
    );
\S_CHANNEL_COUNTER_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_CHANNEL_COUNTER[3]_i_1_n_0\,
      D => \S_CHANNEL_COUNTER[3]_i_2_n_0\,
      Q => S_CHANNEL_COUNTER(3),
      R => RSTP
    );
\S_CONVERSION_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_CONVERSION_reg[126]_0\(0),
      D => \S_SAMPLE_TIME_reg[30]_1\(0),
      Q => \S_CONVERSION_reg_n_0_[0]\,
      R => RSTP
    );
\S_CONVERSION_reg[100]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_CONVERSION_reg[126]_0\(5),
      D => \S_SAMPLE_TIME_reg[30]_1\(10),
      Q => data6(10),
      R => RSTP
    );
\S_CONVERSION_reg[101]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_CONVERSION_reg[126]_0\(5),
      D => \S_SAMPLE_TIME_reg[30]_1\(11),
      Q => data6(11),
      R => RSTP
    );
\S_CONVERSION_reg[102]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_CONVERSION_reg[126]_0\(5),
      D => \S_SAMPLE_TIME_reg[30]_1\(12),
      Q => data6(12),
      R => RSTP
    );
\S_CONVERSION_reg[103]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_CONVERSION_reg[126]_0\(5),
      D => \S_SAMPLE_TIME_reg[30]_1\(13),
      Q => data6(13),
      R => RSTP
    );
\S_CONVERSION_reg[104]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_CONVERSION_reg[126]_0\(5),
      D => \S_SAMPLE_TIME_reg[30]_1\(14),
      Q => data6(14),
      R => RSTP
    );
\S_CONVERSION_reg[105]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_CONVERSION_reg[126]_0\(5),
      D => \S_SAMPLE_TIME_reg[30]_1\(15),
      Q => data6(15),
      R => RSTP
    );
\S_CONVERSION_reg[106]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_CONVERSION_reg[126]_0\(5),
      D => \S_SAMPLE_TIME_reg[30]_1\(16),
      Q => data6(16),
      R => RSTP
    );
\S_CONVERSION_reg[107]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_CONVERSION_reg[126]_0\(5),
      D => \S_SAMPLE_TIME_reg[30]_1\(17),
      Q => data6(17),
      R => RSTP
    );
\S_CONVERSION_reg[108]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_CONVERSION_reg[126]_0\(6),
      D => \S_SAMPLE_TIME_reg[30]_1\(0),
      Q => data7(0),
      R => RSTP
    );
\S_CONVERSION_reg[109]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_CONVERSION_reg[126]_0\(6),
      D => \S_SAMPLE_TIME_reg[30]_1\(1),
      Q => data7(1),
      R => RSTP
    );
\S_CONVERSION_reg[10]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_CONVERSION_reg[126]_0\(0),
      D => \S_SAMPLE_TIME_reg[30]_1\(10),
      Q => \S_CONVERSION_reg_n_0_[10]\,
      R => RSTP
    );
\S_CONVERSION_reg[110]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_CONVERSION_reg[126]_0\(6),
      D => \S_SAMPLE_TIME_reg[30]_1\(2),
      Q => data7(2),
      R => RSTP
    );
\S_CONVERSION_reg[111]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_CONVERSION_reg[126]_0\(6),
      D => \S_SAMPLE_TIME_reg[30]_1\(3),
      Q => data7(3),
      R => RSTP
    );
\S_CONVERSION_reg[112]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_CONVERSION_reg[126]_0\(6),
      D => \S_SAMPLE_TIME_reg[30]_1\(4),
      Q => data7(4),
      R => RSTP
    );
\S_CONVERSION_reg[113]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_CONVERSION_reg[126]_0\(6),
      D => \S_SAMPLE_TIME_reg[30]_1\(5),
      Q => data7(5),
      R => RSTP
    );
\S_CONVERSION_reg[114]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_CONVERSION_reg[126]_0\(6),
      D => \S_SAMPLE_TIME_reg[30]_1\(6),
      Q => data7(6),
      R => RSTP
    );
\S_CONVERSION_reg[115]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_CONVERSION_reg[126]_0\(6),
      D => \S_SAMPLE_TIME_reg[30]_1\(7),
      Q => data7(7),
      R => RSTP
    );
\S_CONVERSION_reg[116]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_CONVERSION_reg[126]_0\(6),
      D => \S_SAMPLE_TIME_reg[30]_1\(8),
      Q => data7(8),
      R => RSTP
    );
\S_CONVERSION_reg[117]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_CONVERSION_reg[126]_0\(6),
      D => \S_SAMPLE_TIME_reg[30]_1\(9),
      Q => data7(9),
      R => RSTP
    );
\S_CONVERSION_reg[118]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_CONVERSION_reg[126]_0\(6),
      D => \S_SAMPLE_TIME_reg[30]_1\(10),
      Q => data7(10),
      R => RSTP
    );
\S_CONVERSION_reg[119]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_CONVERSION_reg[126]_0\(6),
      D => \S_SAMPLE_TIME_reg[30]_1\(11),
      Q => data7(11),
      R => RSTP
    );
\S_CONVERSION_reg[11]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_CONVERSION_reg[126]_0\(0),
      D => \S_SAMPLE_TIME_reg[30]_1\(11),
      Q => \S_CONVERSION_reg_n_0_[11]\,
      R => RSTP
    );
\S_CONVERSION_reg[120]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_CONVERSION_reg[126]_0\(6),
      D => \S_SAMPLE_TIME_reg[30]_1\(12),
      Q => data7(12),
      R => RSTP
    );
\S_CONVERSION_reg[121]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_CONVERSION_reg[126]_0\(6),
      D => \S_SAMPLE_TIME_reg[30]_1\(13),
      Q => data7(13),
      R => RSTP
    );
\S_CONVERSION_reg[122]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_CONVERSION_reg[126]_0\(6),
      D => \S_SAMPLE_TIME_reg[30]_1\(14),
      Q => data7(14),
      R => RSTP
    );
\S_CONVERSION_reg[123]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_CONVERSION_reg[126]_0\(6),
      D => \S_SAMPLE_TIME_reg[30]_1\(15),
      Q => data7(15),
      R => RSTP
    );
\S_CONVERSION_reg[124]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_CONVERSION_reg[126]_0\(6),
      D => \S_SAMPLE_TIME_reg[30]_1\(16),
      Q => data7(16),
      R => RSTP
    );
\S_CONVERSION_reg[125]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_CONVERSION_reg[126]_0\(6),
      D => \S_SAMPLE_TIME_reg[30]_1\(17),
      Q => data7(17),
      R => RSTP
    );
\S_CONVERSION_reg[126]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_CONVERSION_reg[126]_0\(7),
      D => \S_SAMPLE_TIME_reg[30]_1\(0),
      Q => data8(0),
      R => RSTP
    );
\S_CONVERSION_reg[127]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_CONVERSION_reg[126]_0\(7),
      D => \S_SAMPLE_TIME_reg[30]_1\(1),
      Q => data8(1),
      R => RSTP
    );
\S_CONVERSION_reg[128]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_CONVERSION_reg[126]_0\(7),
      D => \S_SAMPLE_TIME_reg[30]_1\(2),
      Q => data8(2),
      R => RSTP
    );
\S_CONVERSION_reg[129]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_CONVERSION_reg[126]_0\(7),
      D => \S_SAMPLE_TIME_reg[30]_1\(3),
      Q => data8(3),
      R => RSTP
    );
\S_CONVERSION_reg[12]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_CONVERSION_reg[126]_0\(0),
      D => \S_SAMPLE_TIME_reg[30]_1\(12),
      Q => \S_CONVERSION_reg_n_0_[12]\,
      R => RSTP
    );
\S_CONVERSION_reg[130]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_CONVERSION_reg[126]_0\(7),
      D => \S_SAMPLE_TIME_reg[30]_1\(4),
      Q => data8(4),
      R => RSTP
    );
\S_CONVERSION_reg[131]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_CONVERSION_reg[126]_0\(7),
      D => \S_SAMPLE_TIME_reg[30]_1\(5),
      Q => data8(5),
      R => RSTP
    );
\S_CONVERSION_reg[132]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_CONVERSION_reg[126]_0\(7),
      D => \S_SAMPLE_TIME_reg[30]_1\(6),
      Q => data8(6),
      R => RSTP
    );
\S_CONVERSION_reg[133]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_CONVERSION_reg[126]_0\(7),
      D => \S_SAMPLE_TIME_reg[30]_1\(7),
      Q => data8(7),
      R => RSTP
    );
\S_CONVERSION_reg[134]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_CONVERSION_reg[126]_0\(7),
      D => \S_SAMPLE_TIME_reg[30]_1\(8),
      Q => data8(8),
      R => RSTP
    );
\S_CONVERSION_reg[135]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_CONVERSION_reg[126]_0\(7),
      D => \S_SAMPLE_TIME_reg[30]_1\(9),
      Q => data8(9),
      R => RSTP
    );
\S_CONVERSION_reg[136]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_CONVERSION_reg[126]_0\(7),
      D => \S_SAMPLE_TIME_reg[30]_1\(10),
      Q => data8(10),
      R => RSTP
    );
\S_CONVERSION_reg[137]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_CONVERSION_reg[126]_0\(7),
      D => \S_SAMPLE_TIME_reg[30]_1\(11),
      Q => data8(11),
      R => RSTP
    );
\S_CONVERSION_reg[138]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_CONVERSION_reg[126]_0\(7),
      D => \S_SAMPLE_TIME_reg[30]_1\(12),
      Q => data8(12),
      R => RSTP
    );
\S_CONVERSION_reg[139]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_CONVERSION_reg[126]_0\(7),
      D => \S_SAMPLE_TIME_reg[30]_1\(13),
      Q => data8(13),
      R => RSTP
    );
\S_CONVERSION_reg[13]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_CONVERSION_reg[126]_0\(0),
      D => \S_SAMPLE_TIME_reg[30]_1\(13),
      Q => \S_CONVERSION_reg_n_0_[13]\,
      R => RSTP
    );
\S_CONVERSION_reg[140]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_CONVERSION_reg[126]_0\(7),
      D => \S_SAMPLE_TIME_reg[30]_1\(14),
      Q => data8(14),
      R => RSTP
    );
\S_CONVERSION_reg[141]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_CONVERSION_reg[126]_0\(7),
      D => \S_SAMPLE_TIME_reg[30]_1\(15),
      Q => data8(15),
      R => RSTP
    );
\S_CONVERSION_reg[142]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_CONVERSION_reg[126]_0\(7),
      D => \S_SAMPLE_TIME_reg[30]_1\(16),
      Q => data8(16),
      R => RSTP
    );
\S_CONVERSION_reg[143]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_CONVERSION_reg[126]_0\(7),
      D => \S_SAMPLE_TIME_reg[30]_1\(17),
      Q => data8(17),
      R => RSTP
    );
\S_CONVERSION_reg[14]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_CONVERSION_reg[126]_0\(0),
      D => \S_SAMPLE_TIME_reg[30]_1\(14),
      Q => \S_CONVERSION_reg_n_0_[14]\,
      R => RSTP
    );
\S_CONVERSION_reg[15]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_CONVERSION_reg[126]_0\(0),
      D => \S_SAMPLE_TIME_reg[30]_1\(15),
      Q => \S_CONVERSION_reg_n_0_[15]\,
      R => RSTP
    );
\S_CONVERSION_reg[16]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_CONVERSION_reg[126]_0\(0),
      D => \S_SAMPLE_TIME_reg[30]_1\(16),
      Q => \S_CONVERSION_reg_n_0_[16]\,
      R => RSTP
    );
\S_CONVERSION_reg[17]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_CONVERSION_reg[126]_0\(0),
      D => \S_SAMPLE_TIME_reg[30]_1\(17),
      Q => \S_CONVERSION_reg_n_0_[17]\,
      R => RSTP
    );
\S_CONVERSION_reg[18]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_CONVERSION_reg[126]_0\(1),
      D => \S_SAMPLE_TIME_reg[30]_1\(0),
      Q => data2(0),
      R => RSTP
    );
\S_CONVERSION_reg[19]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_CONVERSION_reg[126]_0\(1),
      D => \S_SAMPLE_TIME_reg[30]_1\(1),
      Q => data2(1),
      R => RSTP
    );
\S_CONVERSION_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_CONVERSION_reg[126]_0\(0),
      D => \S_SAMPLE_TIME_reg[30]_1\(1),
      Q => \S_CONVERSION_reg_n_0_[1]\,
      R => RSTP
    );
\S_CONVERSION_reg[20]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_CONVERSION_reg[126]_0\(1),
      D => \S_SAMPLE_TIME_reg[30]_1\(2),
      Q => data2(2),
      R => RSTP
    );
\S_CONVERSION_reg[21]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_CONVERSION_reg[126]_0\(1),
      D => \S_SAMPLE_TIME_reg[30]_1\(3),
      Q => data2(3),
      R => RSTP
    );
\S_CONVERSION_reg[22]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_CONVERSION_reg[126]_0\(1),
      D => \S_SAMPLE_TIME_reg[30]_1\(4),
      Q => data2(4),
      R => RSTP
    );
\S_CONVERSION_reg[23]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_CONVERSION_reg[126]_0\(1),
      D => \S_SAMPLE_TIME_reg[30]_1\(5),
      Q => data2(5),
      R => RSTP
    );
\S_CONVERSION_reg[24]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_CONVERSION_reg[126]_0\(1),
      D => \S_SAMPLE_TIME_reg[30]_1\(6),
      Q => data2(6),
      R => RSTP
    );
\S_CONVERSION_reg[25]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_CONVERSION_reg[126]_0\(1),
      D => \S_SAMPLE_TIME_reg[30]_1\(7),
      Q => data2(7),
      R => RSTP
    );
\S_CONVERSION_reg[26]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_CONVERSION_reg[126]_0\(1),
      D => \S_SAMPLE_TIME_reg[30]_1\(8),
      Q => data2(8),
      R => RSTP
    );
\S_CONVERSION_reg[27]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_CONVERSION_reg[126]_0\(1),
      D => \S_SAMPLE_TIME_reg[30]_1\(9),
      Q => data2(9),
      R => RSTP
    );
\S_CONVERSION_reg[28]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_CONVERSION_reg[126]_0\(1),
      D => \S_SAMPLE_TIME_reg[30]_1\(10),
      Q => data2(10),
      R => RSTP
    );
\S_CONVERSION_reg[29]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_CONVERSION_reg[126]_0\(1),
      D => \S_SAMPLE_TIME_reg[30]_1\(11),
      Q => data2(11),
      R => RSTP
    );
\S_CONVERSION_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_CONVERSION_reg[126]_0\(0),
      D => \S_SAMPLE_TIME_reg[30]_1\(2),
      Q => \S_CONVERSION_reg_n_0_[2]\,
      R => RSTP
    );
\S_CONVERSION_reg[30]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_CONVERSION_reg[126]_0\(1),
      D => \S_SAMPLE_TIME_reg[30]_1\(12),
      Q => data2(12),
      R => RSTP
    );
\S_CONVERSION_reg[31]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_CONVERSION_reg[126]_0\(1),
      D => \S_SAMPLE_TIME_reg[30]_1\(13),
      Q => data2(13),
      R => RSTP
    );
\S_CONVERSION_reg[32]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_CONVERSION_reg[126]_0\(1),
      D => \S_SAMPLE_TIME_reg[30]_1\(14),
      Q => data2(14),
      R => RSTP
    );
\S_CONVERSION_reg[33]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_CONVERSION_reg[126]_0\(1),
      D => \S_SAMPLE_TIME_reg[30]_1\(15),
      Q => data2(15),
      R => RSTP
    );
\S_CONVERSION_reg[34]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_CONVERSION_reg[126]_0\(1),
      D => \S_SAMPLE_TIME_reg[30]_1\(16),
      Q => data2(16),
      R => RSTP
    );
\S_CONVERSION_reg[35]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_CONVERSION_reg[126]_0\(1),
      D => \S_SAMPLE_TIME_reg[30]_1\(17),
      Q => data2(17),
      R => RSTP
    );
\S_CONVERSION_reg[36]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_CONVERSION_reg[126]_0\(2),
      D => \S_SAMPLE_TIME_reg[30]_1\(0),
      Q => data3(0),
      R => RSTP
    );
\S_CONVERSION_reg[37]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_CONVERSION_reg[126]_0\(2),
      D => \S_SAMPLE_TIME_reg[30]_1\(1),
      Q => data3(1),
      R => RSTP
    );
\S_CONVERSION_reg[38]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_CONVERSION_reg[126]_0\(2),
      D => \S_SAMPLE_TIME_reg[30]_1\(2),
      Q => data3(2),
      R => RSTP
    );
\S_CONVERSION_reg[39]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_CONVERSION_reg[126]_0\(2),
      D => \S_SAMPLE_TIME_reg[30]_1\(3),
      Q => data3(3),
      R => RSTP
    );
\S_CONVERSION_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_CONVERSION_reg[126]_0\(0),
      D => \S_SAMPLE_TIME_reg[30]_1\(3),
      Q => \S_CONVERSION_reg_n_0_[3]\,
      R => RSTP
    );
\S_CONVERSION_reg[40]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_CONVERSION_reg[126]_0\(2),
      D => \S_SAMPLE_TIME_reg[30]_1\(4),
      Q => data3(4),
      R => RSTP
    );
\S_CONVERSION_reg[41]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_CONVERSION_reg[126]_0\(2),
      D => \S_SAMPLE_TIME_reg[30]_1\(5),
      Q => data3(5),
      R => RSTP
    );
\S_CONVERSION_reg[42]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_CONVERSION_reg[126]_0\(2),
      D => \S_SAMPLE_TIME_reg[30]_1\(6),
      Q => data3(6),
      R => RSTP
    );
\S_CONVERSION_reg[43]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_CONVERSION_reg[126]_0\(2),
      D => \S_SAMPLE_TIME_reg[30]_1\(7),
      Q => data3(7),
      R => RSTP
    );
\S_CONVERSION_reg[44]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_CONVERSION_reg[126]_0\(2),
      D => \S_SAMPLE_TIME_reg[30]_1\(8),
      Q => data3(8),
      R => RSTP
    );
\S_CONVERSION_reg[45]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_CONVERSION_reg[126]_0\(2),
      D => \S_SAMPLE_TIME_reg[30]_1\(9),
      Q => data3(9),
      R => RSTP
    );
\S_CONVERSION_reg[46]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_CONVERSION_reg[126]_0\(2),
      D => \S_SAMPLE_TIME_reg[30]_1\(10),
      Q => data3(10),
      R => RSTP
    );
\S_CONVERSION_reg[47]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_CONVERSION_reg[126]_0\(2),
      D => \S_SAMPLE_TIME_reg[30]_1\(11),
      Q => data3(11),
      R => RSTP
    );
\S_CONVERSION_reg[48]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_CONVERSION_reg[126]_0\(2),
      D => \S_SAMPLE_TIME_reg[30]_1\(12),
      Q => data3(12),
      R => RSTP
    );
\S_CONVERSION_reg[49]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_CONVERSION_reg[126]_0\(2),
      D => \S_SAMPLE_TIME_reg[30]_1\(13),
      Q => data3(13),
      R => RSTP
    );
\S_CONVERSION_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_CONVERSION_reg[126]_0\(0),
      D => \S_SAMPLE_TIME_reg[30]_1\(4),
      Q => \S_CONVERSION_reg_n_0_[4]\,
      R => RSTP
    );
\S_CONVERSION_reg[50]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_CONVERSION_reg[126]_0\(2),
      D => \S_SAMPLE_TIME_reg[30]_1\(14),
      Q => data3(14),
      R => RSTP
    );
\S_CONVERSION_reg[51]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_CONVERSION_reg[126]_0\(2),
      D => \S_SAMPLE_TIME_reg[30]_1\(15),
      Q => data3(15),
      R => RSTP
    );
\S_CONVERSION_reg[52]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_CONVERSION_reg[126]_0\(2),
      D => \S_SAMPLE_TIME_reg[30]_1\(16),
      Q => data3(16),
      R => RSTP
    );
\S_CONVERSION_reg[53]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_CONVERSION_reg[126]_0\(2),
      D => \S_SAMPLE_TIME_reg[30]_1\(17),
      Q => data3(17),
      R => RSTP
    );
\S_CONVERSION_reg[54]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_CONVERSION_reg[126]_0\(3),
      D => \S_SAMPLE_TIME_reg[30]_1\(0),
      Q => data4(0),
      R => RSTP
    );
\S_CONVERSION_reg[55]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_CONVERSION_reg[126]_0\(3),
      D => \S_SAMPLE_TIME_reg[30]_1\(1),
      Q => data4(1),
      R => RSTP
    );
\S_CONVERSION_reg[56]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_CONVERSION_reg[126]_0\(3),
      D => \S_SAMPLE_TIME_reg[30]_1\(2),
      Q => data4(2),
      R => RSTP
    );
\S_CONVERSION_reg[57]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_CONVERSION_reg[126]_0\(3),
      D => \S_SAMPLE_TIME_reg[30]_1\(3),
      Q => data4(3),
      R => RSTP
    );
\S_CONVERSION_reg[58]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_CONVERSION_reg[126]_0\(3),
      D => \S_SAMPLE_TIME_reg[30]_1\(4),
      Q => data4(4),
      R => RSTP
    );
\S_CONVERSION_reg[59]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_CONVERSION_reg[126]_0\(3),
      D => \S_SAMPLE_TIME_reg[30]_1\(5),
      Q => data4(5),
      R => RSTP
    );
\S_CONVERSION_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_CONVERSION_reg[126]_0\(0),
      D => \S_SAMPLE_TIME_reg[30]_1\(5),
      Q => \S_CONVERSION_reg_n_0_[5]\,
      R => RSTP
    );
\S_CONVERSION_reg[60]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_CONVERSION_reg[126]_0\(3),
      D => \S_SAMPLE_TIME_reg[30]_1\(6),
      Q => data4(6),
      R => RSTP
    );
\S_CONVERSION_reg[61]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_CONVERSION_reg[126]_0\(3),
      D => \S_SAMPLE_TIME_reg[30]_1\(7),
      Q => data4(7),
      R => RSTP
    );
\S_CONVERSION_reg[62]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_CONVERSION_reg[126]_0\(3),
      D => \S_SAMPLE_TIME_reg[30]_1\(8),
      Q => data4(8),
      R => RSTP
    );
\S_CONVERSION_reg[63]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_CONVERSION_reg[126]_0\(3),
      D => \S_SAMPLE_TIME_reg[30]_1\(9),
      Q => data4(9),
      R => RSTP
    );
\S_CONVERSION_reg[64]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_CONVERSION_reg[126]_0\(3),
      D => \S_SAMPLE_TIME_reg[30]_1\(10),
      Q => data4(10),
      R => RSTP
    );
\S_CONVERSION_reg[65]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_CONVERSION_reg[126]_0\(3),
      D => \S_SAMPLE_TIME_reg[30]_1\(11),
      Q => data4(11),
      R => RSTP
    );
\S_CONVERSION_reg[66]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_CONVERSION_reg[126]_0\(3),
      D => \S_SAMPLE_TIME_reg[30]_1\(12),
      Q => data4(12),
      R => RSTP
    );
\S_CONVERSION_reg[67]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_CONVERSION_reg[126]_0\(3),
      D => \S_SAMPLE_TIME_reg[30]_1\(13),
      Q => data4(13),
      R => RSTP
    );
\S_CONVERSION_reg[68]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_CONVERSION_reg[126]_0\(3),
      D => \S_SAMPLE_TIME_reg[30]_1\(14),
      Q => data4(14),
      R => RSTP
    );
\S_CONVERSION_reg[69]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_CONVERSION_reg[126]_0\(3),
      D => \S_SAMPLE_TIME_reg[30]_1\(15),
      Q => data4(15),
      R => RSTP
    );
\S_CONVERSION_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_CONVERSION_reg[126]_0\(0),
      D => \S_SAMPLE_TIME_reg[30]_1\(6),
      Q => \S_CONVERSION_reg_n_0_[6]\,
      R => RSTP
    );
\S_CONVERSION_reg[70]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_CONVERSION_reg[126]_0\(3),
      D => \S_SAMPLE_TIME_reg[30]_1\(16),
      Q => data4(16),
      R => RSTP
    );
\S_CONVERSION_reg[71]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_CONVERSION_reg[126]_0\(3),
      D => \S_SAMPLE_TIME_reg[30]_1\(17),
      Q => data4(17),
      R => RSTP
    );
\S_CONVERSION_reg[72]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_CONVERSION_reg[126]_0\(4),
      D => \S_SAMPLE_TIME_reg[30]_1\(0),
      Q => data5(0),
      R => RSTP
    );
\S_CONVERSION_reg[73]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_CONVERSION_reg[126]_0\(4),
      D => \S_SAMPLE_TIME_reg[30]_1\(1),
      Q => data5(1),
      R => RSTP
    );
\S_CONVERSION_reg[74]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_CONVERSION_reg[126]_0\(4),
      D => \S_SAMPLE_TIME_reg[30]_1\(2),
      Q => data5(2),
      R => RSTP
    );
\S_CONVERSION_reg[75]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_CONVERSION_reg[126]_0\(4),
      D => \S_SAMPLE_TIME_reg[30]_1\(3),
      Q => data5(3),
      R => RSTP
    );
\S_CONVERSION_reg[76]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_CONVERSION_reg[126]_0\(4),
      D => \S_SAMPLE_TIME_reg[30]_1\(4),
      Q => data5(4),
      R => RSTP
    );
\S_CONVERSION_reg[77]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_CONVERSION_reg[126]_0\(4),
      D => \S_SAMPLE_TIME_reg[30]_1\(5),
      Q => data5(5),
      R => RSTP
    );
\S_CONVERSION_reg[78]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_CONVERSION_reg[126]_0\(4),
      D => \S_SAMPLE_TIME_reg[30]_1\(6),
      Q => data5(6),
      R => RSTP
    );
\S_CONVERSION_reg[79]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_CONVERSION_reg[126]_0\(4),
      D => \S_SAMPLE_TIME_reg[30]_1\(7),
      Q => data5(7),
      R => RSTP
    );
\S_CONVERSION_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_CONVERSION_reg[126]_0\(0),
      D => \S_SAMPLE_TIME_reg[30]_1\(7),
      Q => \S_CONVERSION_reg_n_0_[7]\,
      R => RSTP
    );
\S_CONVERSION_reg[80]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_CONVERSION_reg[126]_0\(4),
      D => \S_SAMPLE_TIME_reg[30]_1\(8),
      Q => data5(8),
      R => RSTP
    );
\S_CONVERSION_reg[81]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_CONVERSION_reg[126]_0\(4),
      D => \S_SAMPLE_TIME_reg[30]_1\(9),
      Q => data5(9),
      R => RSTP
    );
\S_CONVERSION_reg[82]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_CONVERSION_reg[126]_0\(4),
      D => \S_SAMPLE_TIME_reg[30]_1\(10),
      Q => data5(10),
      R => RSTP
    );
\S_CONVERSION_reg[83]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_CONVERSION_reg[126]_0\(4),
      D => \S_SAMPLE_TIME_reg[30]_1\(11),
      Q => data5(11),
      R => RSTP
    );
\S_CONVERSION_reg[84]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_CONVERSION_reg[126]_0\(4),
      D => \S_SAMPLE_TIME_reg[30]_1\(12),
      Q => data5(12),
      R => RSTP
    );
\S_CONVERSION_reg[85]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_CONVERSION_reg[126]_0\(4),
      D => \S_SAMPLE_TIME_reg[30]_1\(13),
      Q => data5(13),
      R => RSTP
    );
\S_CONVERSION_reg[86]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_CONVERSION_reg[126]_0\(4),
      D => \S_SAMPLE_TIME_reg[30]_1\(14),
      Q => data5(14),
      R => RSTP
    );
\S_CONVERSION_reg[87]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_CONVERSION_reg[126]_0\(4),
      D => \S_SAMPLE_TIME_reg[30]_1\(15),
      Q => data5(15),
      R => RSTP
    );
\S_CONVERSION_reg[88]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_CONVERSION_reg[126]_0\(4),
      D => \S_SAMPLE_TIME_reg[30]_1\(16),
      Q => data5(16),
      R => RSTP
    );
\S_CONVERSION_reg[89]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_CONVERSION_reg[126]_0\(4),
      D => \S_SAMPLE_TIME_reg[30]_1\(17),
      Q => data5(17),
      R => RSTP
    );
\S_CONVERSION_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_CONVERSION_reg[126]_0\(0),
      D => \S_SAMPLE_TIME_reg[30]_1\(8),
      Q => \S_CONVERSION_reg_n_0_[8]\,
      R => RSTP
    );
\S_CONVERSION_reg[90]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_CONVERSION_reg[126]_0\(5),
      D => \S_SAMPLE_TIME_reg[30]_1\(0),
      Q => data6(0),
      R => RSTP
    );
\S_CONVERSION_reg[91]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_CONVERSION_reg[126]_0\(5),
      D => \S_SAMPLE_TIME_reg[30]_1\(1),
      Q => data6(1),
      R => RSTP
    );
\S_CONVERSION_reg[92]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_CONVERSION_reg[126]_0\(5),
      D => \S_SAMPLE_TIME_reg[30]_1\(2),
      Q => data6(2),
      R => RSTP
    );
\S_CONVERSION_reg[93]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_CONVERSION_reg[126]_0\(5),
      D => \S_SAMPLE_TIME_reg[30]_1\(3),
      Q => data6(3),
      R => RSTP
    );
\S_CONVERSION_reg[94]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_CONVERSION_reg[126]_0\(5),
      D => \S_SAMPLE_TIME_reg[30]_1\(4),
      Q => data6(4),
      R => RSTP
    );
\S_CONVERSION_reg[95]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_CONVERSION_reg[126]_0\(5),
      D => \S_SAMPLE_TIME_reg[30]_1\(5),
      Q => data6(5),
      R => RSTP
    );
\S_CONVERSION_reg[96]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_CONVERSION_reg[126]_0\(5),
      D => \S_SAMPLE_TIME_reg[30]_1\(6),
      Q => data6(6),
      R => RSTP
    );
\S_CONVERSION_reg[97]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_CONVERSION_reg[126]_0\(5),
      D => \S_SAMPLE_TIME_reg[30]_1\(7),
      Q => data6(7),
      R => RSTP
    );
\S_CONVERSION_reg[98]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_CONVERSION_reg[126]_0\(5),
      D => \S_SAMPLE_TIME_reg[30]_1\(8),
      Q => data6(8),
      R => RSTP
    );
\S_CONVERSION_reg[99]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_CONVERSION_reg[126]_0\(5),
      D => \S_SAMPLE_TIME_reg[30]_1\(9),
      Q => data6(9),
      R => RSTP
    );
\S_CONVERSION_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_CONVERSION_reg[126]_0\(0),
      D => \S_SAMPLE_TIME_reg[30]_1\(9),
      Q => \S_CONVERSION_reg_n_0_[9]\,
      R => RSTP
    );
\S_CONV_COUNTER[0]_i_1\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"B"
    )
        port map (
      I0 => \^s_enable_reg[0]_0\,
      I1 => S_CONV_COUNTER(0),
      O => \S_CONV_COUNTER[0]_i_1_n_0\
    );
\S_CONV_COUNTER[1]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"41"
    )
        port map (
      I0 => \^s_enable_reg[0]_0\,
      I1 => S_CONV_COUNTER(0),
      I2 => S_CONV_COUNTER(1),
      O => \S_CONV_COUNTER[1]_i_1_n_0\
    );
\S_CONV_COUNTER[2]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"00E1"
    )
        port map (
      I0 => S_CONV_COUNTER(1),
      I1 => S_CONV_COUNTER(0),
      I2 => S_CONV_COUNTER(2),
      I3 => \^s_enable_reg[0]_0\,
      O => \S_CONV_COUNTER[2]_i_1_n_0\
    );
\S_CONV_COUNTER[3]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"040F040F0400040F"
    )
        port map (
      I0 => \^q\(1),
      I1 => \^q\(0),
      I2 => \^s_enable_reg[0]\,
      I3 => \^s_enable_reg[0]_0\,
      I4 => raw_to_si_n_137,
      I5 => S_CONV_COUNTER(3),
      O => \S_CONV_COUNTER[3]_i_1_n_0\
    );
\S_CONV_COUNTER[3]_i_2\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFFEAAAB"
    )
        port map (
      I0 => \^s_enable_reg[0]_0\,
      I1 => S_CONV_COUNTER(0),
      I2 => S_CONV_COUNTER(1),
      I3 => S_CONV_COUNTER(2),
      I4 => S_CONV_COUNTER(3),
      O => \S_CONV_COUNTER[3]_i_2_n_0\
    );
\S_CONV_COUNTER_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_CONV_COUNTER[3]_i_1_n_0\,
      D => \S_CONV_COUNTER[0]_i_1_n_0\,
      Q => S_CONV_COUNTER(0),
      R => RSTP
    );
\S_CONV_COUNTER_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_CONV_COUNTER[3]_i_1_n_0\,
      D => \S_CONV_COUNTER[1]_i_1_n_0\,
      Q => S_CONV_COUNTER(1),
      R => RSTP
    );
\S_CONV_COUNTER_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_CONV_COUNTER[3]_i_1_n_0\,
      D => \S_CONV_COUNTER[2]_i_1_n_0\,
      Q => S_CONV_COUNTER(2),
      R => RSTP
    );
\S_CONV_COUNTER_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_CONV_COUNTER[3]_i_1_n_0\,
      D => \S_CONV_COUNTER[3]_i_2_n_0\,
      Q => S_CONV_COUNTER(3),
      R => RSTP
    );
S_DUMMY_SAMPLE_reg: unisim.vcomponents.FDSE
     port map (
      C => s00_axi_aclk,
      CE => '1',
      D => S_DUMMY_SAMPLE_reg_0,
      Q => \^s_dummy_sample\,
      S => RSTP
    );
S_MANUAL_reg: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => '1',
      D => S_MANUAL_reg_1,
      Q => \^s_manual_reg_0\,
      R => '0'
    );
\S_OFFSET_S_C[0]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"8F808F8F8F808080"
    )
        port map (
      I0 => S_OFFSET(112),
      I1 => \S_RAW_VALUE_S_C[15]_i_3_n_0\,
      I2 => S_CHANNEL_COUNTER(3),
      I3 => \S_OFFSET_S_C[0]_i_2_n_0\,
      I4 => S_CHANNEL_COUNTER(2),
      I5 => \S_OFFSET_S_C[0]_i_3_n_0\,
      O => \S_OFFSET_S_C[0]_i_1_n_0\
    );
\S_OFFSET_S_C[0]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => S_OFFSET(96),
      I1 => S_OFFSET(80),
      I2 => S_CHANNEL_COUNTER(1),
      I3 => S_OFFSET(64),
      I4 => S_CHANNEL_COUNTER(0),
      I5 => S_OFFSET(48),
      O => \S_OFFSET_S_C[0]_i_2_n_0\
    );
\S_OFFSET_S_C[0]_i_3\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"AFC0A0C0"
    )
        port map (
      I0 => S_OFFSET(32),
      I1 => S_OFFSET(16),
      I2 => S_CHANNEL_COUNTER(1),
      I3 => S_CHANNEL_COUNTER(0),
      I4 => S_OFFSET(0),
      O => \S_OFFSET_S_C[0]_i_3_n_0\
    );
\S_OFFSET_S_C[10]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"8F808F8F8F808080"
    )
        port map (
      I0 => S_OFFSET(122),
      I1 => \S_RAW_VALUE_S_C[15]_i_3_n_0\,
      I2 => S_CHANNEL_COUNTER(3),
      I3 => \S_OFFSET_S_C[10]_i_2_n_0\,
      I4 => S_CHANNEL_COUNTER(2),
      I5 => \S_OFFSET_S_C[10]_i_3_n_0\,
      O => \S_OFFSET_S_C[10]_i_1_n_0\
    );
\S_OFFSET_S_C[10]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => S_OFFSET(106),
      I1 => S_OFFSET(90),
      I2 => S_CHANNEL_COUNTER(1),
      I3 => S_OFFSET(74),
      I4 => S_CHANNEL_COUNTER(0),
      I5 => S_OFFSET(58),
      O => \S_OFFSET_S_C[10]_i_2_n_0\
    );
\S_OFFSET_S_C[10]_i_3\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"AFC0A0C0"
    )
        port map (
      I0 => S_OFFSET(42),
      I1 => S_OFFSET(26),
      I2 => S_CHANNEL_COUNTER(1),
      I3 => S_CHANNEL_COUNTER(0),
      I4 => S_OFFSET(10),
      O => \S_OFFSET_S_C[10]_i_3_n_0\
    );
\S_OFFSET_S_C[11]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"8F808F8F8F808080"
    )
        port map (
      I0 => S_OFFSET(123),
      I1 => \S_RAW_VALUE_S_C[15]_i_3_n_0\,
      I2 => S_CHANNEL_COUNTER(3),
      I3 => \S_OFFSET_S_C[11]_i_2_n_0\,
      I4 => S_CHANNEL_COUNTER(2),
      I5 => \S_OFFSET_S_C[11]_i_3_n_0\,
      O => \S_OFFSET_S_C[11]_i_1_n_0\
    );
\S_OFFSET_S_C[11]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => S_OFFSET(107),
      I1 => S_OFFSET(91),
      I2 => S_CHANNEL_COUNTER(1),
      I3 => S_OFFSET(75),
      I4 => S_CHANNEL_COUNTER(0),
      I5 => S_OFFSET(59),
      O => \S_OFFSET_S_C[11]_i_2_n_0\
    );
\S_OFFSET_S_C[11]_i_3\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"AFC0A0C0"
    )
        port map (
      I0 => S_OFFSET(43),
      I1 => S_OFFSET(27),
      I2 => S_CHANNEL_COUNTER(1),
      I3 => S_CHANNEL_COUNTER(0),
      I4 => S_OFFSET(11),
      O => \S_OFFSET_S_C[11]_i_3_n_0\
    );
\S_OFFSET_S_C[12]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"8F808F8F8F808080"
    )
        port map (
      I0 => S_OFFSET(124),
      I1 => \S_RAW_VALUE_S_C[15]_i_3_n_0\,
      I2 => S_CHANNEL_COUNTER(3),
      I3 => \S_OFFSET_S_C[12]_i_2_n_0\,
      I4 => S_CHANNEL_COUNTER(2),
      I5 => \S_OFFSET_S_C[12]_i_3_n_0\,
      O => \S_OFFSET_S_C[12]_i_1_n_0\
    );
\S_OFFSET_S_C[12]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => S_OFFSET(108),
      I1 => S_OFFSET(92),
      I2 => S_CHANNEL_COUNTER(1),
      I3 => S_OFFSET(76),
      I4 => S_CHANNEL_COUNTER(0),
      I5 => S_OFFSET(60),
      O => \S_OFFSET_S_C[12]_i_2_n_0\
    );
\S_OFFSET_S_C[12]_i_3\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"AFC0A0C0"
    )
        port map (
      I0 => S_OFFSET(44),
      I1 => S_OFFSET(28),
      I2 => S_CHANNEL_COUNTER(1),
      I3 => S_CHANNEL_COUNTER(0),
      I4 => S_OFFSET(12),
      O => \S_OFFSET_S_C[12]_i_3_n_0\
    );
\S_OFFSET_S_C[13]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"8F808F8F8F808080"
    )
        port map (
      I0 => S_OFFSET(125),
      I1 => \S_RAW_VALUE_S_C[15]_i_3_n_0\,
      I2 => S_CHANNEL_COUNTER(3),
      I3 => \S_OFFSET_S_C[13]_i_2_n_0\,
      I4 => S_CHANNEL_COUNTER(2),
      I5 => \S_OFFSET_S_C[13]_i_3_n_0\,
      O => \S_OFFSET_S_C[13]_i_1_n_0\
    );
\S_OFFSET_S_C[13]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => S_OFFSET(109),
      I1 => S_OFFSET(93),
      I2 => S_CHANNEL_COUNTER(1),
      I3 => S_OFFSET(77),
      I4 => S_CHANNEL_COUNTER(0),
      I5 => S_OFFSET(61),
      O => \S_OFFSET_S_C[13]_i_2_n_0\
    );
\S_OFFSET_S_C[13]_i_3\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"AFC0A0C0"
    )
        port map (
      I0 => S_OFFSET(45),
      I1 => S_OFFSET(29),
      I2 => S_CHANNEL_COUNTER(1),
      I3 => S_CHANNEL_COUNTER(0),
      I4 => S_OFFSET(13),
      O => \S_OFFSET_S_C[13]_i_3_n_0\
    );
\S_OFFSET_S_C[14]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"8F808F8F8F808080"
    )
        port map (
      I0 => S_OFFSET(126),
      I1 => \S_RAW_VALUE_S_C[15]_i_3_n_0\,
      I2 => S_CHANNEL_COUNTER(3),
      I3 => \S_OFFSET_S_C[14]_i_2_n_0\,
      I4 => S_CHANNEL_COUNTER(2),
      I5 => \S_OFFSET_S_C[14]_i_3_n_0\,
      O => \S_OFFSET_S_C[14]_i_1_n_0\
    );
\S_OFFSET_S_C[14]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => S_OFFSET(110),
      I1 => S_OFFSET(94),
      I2 => S_CHANNEL_COUNTER(1),
      I3 => S_OFFSET(78),
      I4 => S_CHANNEL_COUNTER(0),
      I5 => S_OFFSET(62),
      O => \S_OFFSET_S_C[14]_i_2_n_0\
    );
\S_OFFSET_S_C[14]_i_3\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"AFC0A0C0"
    )
        port map (
      I0 => S_OFFSET(46),
      I1 => S_OFFSET(30),
      I2 => S_CHANNEL_COUNTER(1),
      I3 => S_CHANNEL_COUNTER(0),
      I4 => S_OFFSET(14),
      O => \S_OFFSET_S_C[14]_i_3_n_0\
    );
\S_OFFSET_S_C[15]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"8F808F8F8F808080"
    )
        port map (
      I0 => S_OFFSET(127),
      I1 => \S_RAW_VALUE_S_C[15]_i_3_n_0\,
      I2 => S_CHANNEL_COUNTER(3),
      I3 => \S_OFFSET_S_C[15]_i_2_n_0\,
      I4 => S_CHANNEL_COUNTER(2),
      I5 => \S_OFFSET_S_C[15]_i_3_n_0\,
      O => \S_OFFSET_S_C[15]_i_1_n_0\
    );
\S_OFFSET_S_C[15]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => S_OFFSET(111),
      I1 => S_OFFSET(95),
      I2 => S_CHANNEL_COUNTER(1),
      I3 => S_OFFSET(79),
      I4 => S_CHANNEL_COUNTER(0),
      I5 => S_OFFSET(63),
      O => \S_OFFSET_S_C[15]_i_2_n_0\
    );
\S_OFFSET_S_C[15]_i_3\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"AFC0A0C0"
    )
        port map (
      I0 => S_OFFSET(47),
      I1 => S_OFFSET(31),
      I2 => S_CHANNEL_COUNTER(1),
      I3 => S_CHANNEL_COUNTER(0),
      I4 => S_OFFSET(15),
      O => \S_OFFSET_S_C[15]_i_3_n_0\
    );
\S_OFFSET_S_C[1]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"8F808F8F8F808080"
    )
        port map (
      I0 => S_OFFSET(113),
      I1 => \S_RAW_VALUE_S_C[15]_i_3_n_0\,
      I2 => S_CHANNEL_COUNTER(3),
      I3 => \S_OFFSET_S_C[1]_i_2_n_0\,
      I4 => S_CHANNEL_COUNTER(2),
      I5 => \S_OFFSET_S_C[1]_i_3_n_0\,
      O => \S_OFFSET_S_C[1]_i_1_n_0\
    );
\S_OFFSET_S_C[1]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => S_OFFSET(97),
      I1 => S_OFFSET(81),
      I2 => S_CHANNEL_COUNTER(1),
      I3 => S_OFFSET(65),
      I4 => S_CHANNEL_COUNTER(0),
      I5 => S_OFFSET(49),
      O => \S_OFFSET_S_C[1]_i_2_n_0\
    );
\S_OFFSET_S_C[1]_i_3\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"AFC0A0C0"
    )
        port map (
      I0 => S_OFFSET(33),
      I1 => S_OFFSET(17),
      I2 => S_CHANNEL_COUNTER(1),
      I3 => S_CHANNEL_COUNTER(0),
      I4 => S_OFFSET(1),
      O => \S_OFFSET_S_C[1]_i_3_n_0\
    );
\S_OFFSET_S_C[2]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"8F808F8F8F808080"
    )
        port map (
      I0 => S_OFFSET(114),
      I1 => \S_RAW_VALUE_S_C[15]_i_3_n_0\,
      I2 => S_CHANNEL_COUNTER(3),
      I3 => \S_OFFSET_S_C[2]_i_2_n_0\,
      I4 => S_CHANNEL_COUNTER(2),
      I5 => \S_OFFSET_S_C[2]_i_3_n_0\,
      O => \S_OFFSET_S_C[2]_i_1_n_0\
    );
\S_OFFSET_S_C[2]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => S_OFFSET(98),
      I1 => S_OFFSET(82),
      I2 => S_CHANNEL_COUNTER(1),
      I3 => S_OFFSET(66),
      I4 => S_CHANNEL_COUNTER(0),
      I5 => S_OFFSET(50),
      O => \S_OFFSET_S_C[2]_i_2_n_0\
    );
\S_OFFSET_S_C[2]_i_3\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"AFC0A0C0"
    )
        port map (
      I0 => S_OFFSET(34),
      I1 => S_OFFSET(18),
      I2 => S_CHANNEL_COUNTER(1),
      I3 => S_CHANNEL_COUNTER(0),
      I4 => S_OFFSET(2),
      O => \S_OFFSET_S_C[2]_i_3_n_0\
    );
\S_OFFSET_S_C[3]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"8F808F8F8F808080"
    )
        port map (
      I0 => S_OFFSET(115),
      I1 => \S_RAW_VALUE_S_C[15]_i_3_n_0\,
      I2 => S_CHANNEL_COUNTER(3),
      I3 => \S_OFFSET_S_C[3]_i_2_n_0\,
      I4 => S_CHANNEL_COUNTER(2),
      I5 => \S_OFFSET_S_C[3]_i_3_n_0\,
      O => \S_OFFSET_S_C[3]_i_1_n_0\
    );
\S_OFFSET_S_C[3]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => S_OFFSET(99),
      I1 => S_OFFSET(83),
      I2 => S_CHANNEL_COUNTER(1),
      I3 => S_OFFSET(67),
      I4 => S_CHANNEL_COUNTER(0),
      I5 => S_OFFSET(51),
      O => \S_OFFSET_S_C[3]_i_2_n_0\
    );
\S_OFFSET_S_C[3]_i_3\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"AFC0A0C0"
    )
        port map (
      I0 => S_OFFSET(35),
      I1 => S_OFFSET(19),
      I2 => S_CHANNEL_COUNTER(1),
      I3 => S_CHANNEL_COUNTER(0),
      I4 => S_OFFSET(3),
      O => \S_OFFSET_S_C[3]_i_3_n_0\
    );
\S_OFFSET_S_C[4]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"8F808F8F8F808080"
    )
        port map (
      I0 => S_OFFSET(116),
      I1 => \S_RAW_VALUE_S_C[15]_i_3_n_0\,
      I2 => S_CHANNEL_COUNTER(3),
      I3 => \S_OFFSET_S_C[4]_i_2_n_0\,
      I4 => S_CHANNEL_COUNTER(2),
      I5 => \S_OFFSET_S_C[4]_i_3_n_0\,
      O => \S_OFFSET_S_C[4]_i_1_n_0\
    );
\S_OFFSET_S_C[4]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => S_OFFSET(100),
      I1 => S_OFFSET(84),
      I2 => S_CHANNEL_COUNTER(1),
      I3 => S_OFFSET(68),
      I4 => S_CHANNEL_COUNTER(0),
      I5 => S_OFFSET(52),
      O => \S_OFFSET_S_C[4]_i_2_n_0\
    );
\S_OFFSET_S_C[4]_i_3\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"AFC0A0C0"
    )
        port map (
      I0 => S_OFFSET(36),
      I1 => S_OFFSET(20),
      I2 => S_CHANNEL_COUNTER(1),
      I3 => S_CHANNEL_COUNTER(0),
      I4 => S_OFFSET(4),
      O => \S_OFFSET_S_C[4]_i_3_n_0\
    );
\S_OFFSET_S_C[5]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"8F808F8F8F808080"
    )
        port map (
      I0 => S_OFFSET(117),
      I1 => \S_RAW_VALUE_S_C[15]_i_3_n_0\,
      I2 => S_CHANNEL_COUNTER(3),
      I3 => \S_OFFSET_S_C[5]_i_2_n_0\,
      I4 => S_CHANNEL_COUNTER(2),
      I5 => \S_OFFSET_S_C[5]_i_3_n_0\,
      O => \S_OFFSET_S_C[5]_i_1_n_0\
    );
\S_OFFSET_S_C[5]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => S_OFFSET(101),
      I1 => S_OFFSET(85),
      I2 => S_CHANNEL_COUNTER(1),
      I3 => S_OFFSET(69),
      I4 => S_CHANNEL_COUNTER(0),
      I5 => S_OFFSET(53),
      O => \S_OFFSET_S_C[5]_i_2_n_0\
    );
\S_OFFSET_S_C[5]_i_3\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"AFC0A0C0"
    )
        port map (
      I0 => S_OFFSET(37),
      I1 => S_OFFSET(21),
      I2 => S_CHANNEL_COUNTER(1),
      I3 => S_CHANNEL_COUNTER(0),
      I4 => S_OFFSET(5),
      O => \S_OFFSET_S_C[5]_i_3_n_0\
    );
\S_OFFSET_S_C[6]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"8F808F8F8F808080"
    )
        port map (
      I0 => S_OFFSET(118),
      I1 => \S_RAW_VALUE_S_C[15]_i_3_n_0\,
      I2 => S_CHANNEL_COUNTER(3),
      I3 => \S_OFFSET_S_C[6]_i_2_n_0\,
      I4 => S_CHANNEL_COUNTER(2),
      I5 => \S_OFFSET_S_C[6]_i_3_n_0\,
      O => \S_OFFSET_S_C[6]_i_1_n_0\
    );
\S_OFFSET_S_C[6]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => S_OFFSET(102),
      I1 => S_OFFSET(86),
      I2 => S_CHANNEL_COUNTER(1),
      I3 => S_OFFSET(70),
      I4 => S_CHANNEL_COUNTER(0),
      I5 => S_OFFSET(54),
      O => \S_OFFSET_S_C[6]_i_2_n_0\
    );
\S_OFFSET_S_C[6]_i_3\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"AFC0A0C0"
    )
        port map (
      I0 => S_OFFSET(38),
      I1 => S_OFFSET(22),
      I2 => S_CHANNEL_COUNTER(1),
      I3 => S_CHANNEL_COUNTER(0),
      I4 => S_OFFSET(6),
      O => \S_OFFSET_S_C[6]_i_3_n_0\
    );
\S_OFFSET_S_C[7]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"8F808F8F8F808080"
    )
        port map (
      I0 => S_OFFSET(119),
      I1 => \S_RAW_VALUE_S_C[15]_i_3_n_0\,
      I2 => S_CHANNEL_COUNTER(3),
      I3 => \S_OFFSET_S_C[7]_i_2_n_0\,
      I4 => S_CHANNEL_COUNTER(2),
      I5 => \S_OFFSET_S_C[7]_i_3_n_0\,
      O => \S_OFFSET_S_C[7]_i_1_n_0\
    );
\S_OFFSET_S_C[7]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => S_OFFSET(103),
      I1 => S_OFFSET(87),
      I2 => S_CHANNEL_COUNTER(1),
      I3 => S_OFFSET(71),
      I4 => S_CHANNEL_COUNTER(0),
      I5 => S_OFFSET(55),
      O => \S_OFFSET_S_C[7]_i_2_n_0\
    );
\S_OFFSET_S_C[7]_i_3\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"AFC0A0C0"
    )
        port map (
      I0 => S_OFFSET(39),
      I1 => S_OFFSET(23),
      I2 => S_CHANNEL_COUNTER(1),
      I3 => S_CHANNEL_COUNTER(0),
      I4 => S_OFFSET(7),
      O => \S_OFFSET_S_C[7]_i_3_n_0\
    );
\S_OFFSET_S_C[8]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"8F808F8F8F808080"
    )
        port map (
      I0 => S_OFFSET(120),
      I1 => \S_RAW_VALUE_S_C[15]_i_3_n_0\,
      I2 => S_CHANNEL_COUNTER(3),
      I3 => \S_OFFSET_S_C[8]_i_2_n_0\,
      I4 => S_CHANNEL_COUNTER(2),
      I5 => \S_OFFSET_S_C[8]_i_3_n_0\,
      O => \S_OFFSET_S_C[8]_i_1_n_0\
    );
\S_OFFSET_S_C[8]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => S_OFFSET(104),
      I1 => S_OFFSET(88),
      I2 => S_CHANNEL_COUNTER(1),
      I3 => S_OFFSET(72),
      I4 => S_CHANNEL_COUNTER(0),
      I5 => S_OFFSET(56),
      O => \S_OFFSET_S_C[8]_i_2_n_0\
    );
\S_OFFSET_S_C[8]_i_3\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"AFC0A0C0"
    )
        port map (
      I0 => S_OFFSET(40),
      I1 => S_OFFSET(24),
      I2 => S_CHANNEL_COUNTER(1),
      I3 => S_CHANNEL_COUNTER(0),
      I4 => S_OFFSET(8),
      O => \S_OFFSET_S_C[8]_i_3_n_0\
    );
\S_OFFSET_S_C[9]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"8F808F8F8F808080"
    )
        port map (
      I0 => S_OFFSET(121),
      I1 => \S_RAW_VALUE_S_C[15]_i_3_n_0\,
      I2 => S_CHANNEL_COUNTER(3),
      I3 => \S_OFFSET_S_C[9]_i_2_n_0\,
      I4 => S_CHANNEL_COUNTER(2),
      I5 => \S_OFFSET_S_C[9]_i_3_n_0\,
      O => \S_OFFSET_S_C[9]_i_1_n_0\
    );
\S_OFFSET_S_C[9]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => S_OFFSET(105),
      I1 => S_OFFSET(89),
      I2 => S_CHANNEL_COUNTER(1),
      I3 => S_OFFSET(73),
      I4 => S_CHANNEL_COUNTER(0),
      I5 => S_OFFSET(57),
      O => \S_OFFSET_S_C[9]_i_2_n_0\
    );
\S_OFFSET_S_C[9]_i_3\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"AFC0A0C0"
    )
        port map (
      I0 => S_OFFSET(41),
      I1 => S_OFFSET(25),
      I2 => S_CHANNEL_COUNTER(1),
      I3 => S_CHANNEL_COUNTER(0),
      I4 => S_OFFSET(9),
      O => \S_OFFSET_S_C[9]_i_3_n_0\
    );
\S_OFFSET_S_C_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_OFFSET_S_C,
      D => \S_OFFSET_S_C[0]_i_1_n_0\,
      Q => \S_OFFSET_S_C_reg_n_0_[0]\,
      R => RSTP
    );
\S_OFFSET_S_C_reg[10]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_OFFSET_S_C,
      D => \S_OFFSET_S_C[10]_i_1_n_0\,
      Q => \S_OFFSET_S_C_reg_n_0_[10]\,
      R => RSTP
    );
\S_OFFSET_S_C_reg[11]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_OFFSET_S_C,
      D => \S_OFFSET_S_C[11]_i_1_n_0\,
      Q => \S_OFFSET_S_C_reg_n_0_[11]\,
      R => RSTP
    );
\S_OFFSET_S_C_reg[12]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_OFFSET_S_C,
      D => \S_OFFSET_S_C[12]_i_1_n_0\,
      Q => \S_OFFSET_S_C_reg_n_0_[12]\,
      R => RSTP
    );
\S_OFFSET_S_C_reg[13]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_OFFSET_S_C,
      D => \S_OFFSET_S_C[13]_i_1_n_0\,
      Q => \S_OFFSET_S_C_reg_n_0_[13]\,
      R => RSTP
    );
\S_OFFSET_S_C_reg[14]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_OFFSET_S_C,
      D => \S_OFFSET_S_C[14]_i_1_n_0\,
      Q => \S_OFFSET_S_C_reg_n_0_[14]\,
      R => RSTP
    );
\S_OFFSET_S_C_reg[15]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_OFFSET_S_C,
      D => \S_OFFSET_S_C[15]_i_1_n_0\,
      Q => \S_OFFSET_S_C_reg_n_0_[15]\,
      R => RSTP
    );
\S_OFFSET_S_C_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_OFFSET_S_C,
      D => \S_OFFSET_S_C[1]_i_1_n_0\,
      Q => \S_OFFSET_S_C_reg_n_0_[1]\,
      R => RSTP
    );
\S_OFFSET_S_C_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_OFFSET_S_C,
      D => \S_OFFSET_S_C[2]_i_1_n_0\,
      Q => \S_OFFSET_S_C_reg_n_0_[2]\,
      R => RSTP
    );
\S_OFFSET_S_C_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_OFFSET_S_C,
      D => \S_OFFSET_S_C[3]_i_1_n_0\,
      Q => \S_OFFSET_S_C_reg_n_0_[3]\,
      R => RSTP
    );
\S_OFFSET_S_C_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_OFFSET_S_C,
      D => \S_OFFSET_S_C[4]_i_1_n_0\,
      Q => \S_OFFSET_S_C_reg_n_0_[4]\,
      R => RSTP
    );
\S_OFFSET_S_C_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_OFFSET_S_C,
      D => \S_OFFSET_S_C[5]_i_1_n_0\,
      Q => \S_OFFSET_S_C_reg_n_0_[5]\,
      R => RSTP
    );
\S_OFFSET_S_C_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_OFFSET_S_C,
      D => \S_OFFSET_S_C[6]_i_1_n_0\,
      Q => \S_OFFSET_S_C_reg_n_0_[6]\,
      R => RSTP
    );
\S_OFFSET_S_C_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_OFFSET_S_C,
      D => \S_OFFSET_S_C[7]_i_1_n_0\,
      Q => \S_OFFSET_S_C_reg_n_0_[7]\,
      R => RSTP
    );
\S_OFFSET_S_C_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_OFFSET_S_C,
      D => \S_OFFSET_S_C[8]_i_1_n_0\,
      Q => \S_OFFSET_S_C_reg_n_0_[8]\,
      R => RSTP
    );
\S_OFFSET_S_C_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_OFFSET_S_C,
      D => \S_OFFSET_S_C[9]_i_1_n_0\,
      Q => \S_OFFSET_S_C_reg_n_0_[9]\,
      R => RSTP
    );
\S_OFFSET_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_OFFSET_reg[112]_0\(0),
      D => \S_SAMPLE_TIME_reg[30]_1\(0),
      Q => S_OFFSET(0),
      R => RSTP
    );
\S_OFFSET_reg[100]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_OFFSET_reg[112]_0\(6),
      D => \S_SAMPLE_TIME_reg[30]_1\(4),
      Q => S_OFFSET(100),
      R => RSTP
    );
\S_OFFSET_reg[101]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_OFFSET_reg[112]_0\(6),
      D => \S_SAMPLE_TIME_reg[30]_1\(5),
      Q => S_OFFSET(101),
      R => RSTP
    );
\S_OFFSET_reg[102]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_OFFSET_reg[112]_0\(6),
      D => \S_SAMPLE_TIME_reg[30]_1\(6),
      Q => S_OFFSET(102),
      R => RSTP
    );
\S_OFFSET_reg[103]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_OFFSET_reg[112]_0\(6),
      D => \S_SAMPLE_TIME_reg[30]_1\(7),
      Q => S_OFFSET(103),
      R => RSTP
    );
\S_OFFSET_reg[104]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_OFFSET_reg[112]_0\(6),
      D => \S_SAMPLE_TIME_reg[30]_1\(8),
      Q => S_OFFSET(104),
      R => RSTP
    );
\S_OFFSET_reg[105]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_OFFSET_reg[112]_0\(6),
      D => \S_SAMPLE_TIME_reg[30]_1\(9),
      Q => S_OFFSET(105),
      R => RSTP
    );
\S_OFFSET_reg[106]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_OFFSET_reg[112]_0\(6),
      D => \S_SAMPLE_TIME_reg[30]_1\(10),
      Q => S_OFFSET(106),
      R => RSTP
    );
\S_OFFSET_reg[107]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_OFFSET_reg[112]_0\(6),
      D => \S_SAMPLE_TIME_reg[30]_1\(11),
      Q => S_OFFSET(107),
      R => RSTP
    );
\S_OFFSET_reg[108]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_OFFSET_reg[112]_0\(6),
      D => \S_SAMPLE_TIME_reg[30]_1\(12),
      Q => S_OFFSET(108),
      R => RSTP
    );
\S_OFFSET_reg[109]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_OFFSET_reg[112]_0\(6),
      D => \S_SAMPLE_TIME_reg[30]_1\(13),
      Q => S_OFFSET(109),
      R => RSTP
    );
\S_OFFSET_reg[10]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_OFFSET_reg[112]_0\(0),
      D => \S_SAMPLE_TIME_reg[30]_1\(10),
      Q => S_OFFSET(10),
      R => RSTP
    );
\S_OFFSET_reg[110]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_OFFSET_reg[112]_0\(6),
      D => \S_SAMPLE_TIME_reg[30]_1\(14),
      Q => S_OFFSET(110),
      R => RSTP
    );
\S_OFFSET_reg[111]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_OFFSET_reg[112]_0\(6),
      D => \S_SAMPLE_TIME_reg[30]_1\(15),
      Q => S_OFFSET(111),
      R => RSTP
    );
\S_OFFSET_reg[112]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_OFFSET_reg[112]_0\(7),
      D => \S_SAMPLE_TIME_reg[30]_1\(0),
      Q => S_OFFSET(112),
      R => RSTP
    );
\S_OFFSET_reg[113]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_OFFSET_reg[112]_0\(7),
      D => \S_SAMPLE_TIME_reg[30]_1\(1),
      Q => S_OFFSET(113),
      R => RSTP
    );
\S_OFFSET_reg[114]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_OFFSET_reg[112]_0\(7),
      D => \S_SAMPLE_TIME_reg[30]_1\(2),
      Q => S_OFFSET(114),
      R => RSTP
    );
\S_OFFSET_reg[115]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_OFFSET_reg[112]_0\(7),
      D => \S_SAMPLE_TIME_reg[30]_1\(3),
      Q => S_OFFSET(115),
      R => RSTP
    );
\S_OFFSET_reg[116]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_OFFSET_reg[112]_0\(7),
      D => \S_SAMPLE_TIME_reg[30]_1\(4),
      Q => S_OFFSET(116),
      R => RSTP
    );
\S_OFFSET_reg[117]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_OFFSET_reg[112]_0\(7),
      D => \S_SAMPLE_TIME_reg[30]_1\(5),
      Q => S_OFFSET(117),
      R => RSTP
    );
\S_OFFSET_reg[118]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_OFFSET_reg[112]_0\(7),
      D => \S_SAMPLE_TIME_reg[30]_1\(6),
      Q => S_OFFSET(118),
      R => RSTP
    );
\S_OFFSET_reg[119]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_OFFSET_reg[112]_0\(7),
      D => \S_SAMPLE_TIME_reg[30]_1\(7),
      Q => S_OFFSET(119),
      R => RSTP
    );
\S_OFFSET_reg[11]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_OFFSET_reg[112]_0\(0),
      D => \S_SAMPLE_TIME_reg[30]_1\(11),
      Q => S_OFFSET(11),
      R => RSTP
    );
\S_OFFSET_reg[120]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_OFFSET_reg[112]_0\(7),
      D => \S_SAMPLE_TIME_reg[30]_1\(8),
      Q => S_OFFSET(120),
      R => RSTP
    );
\S_OFFSET_reg[121]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_OFFSET_reg[112]_0\(7),
      D => \S_SAMPLE_TIME_reg[30]_1\(9),
      Q => S_OFFSET(121),
      R => RSTP
    );
\S_OFFSET_reg[122]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_OFFSET_reg[112]_0\(7),
      D => \S_SAMPLE_TIME_reg[30]_1\(10),
      Q => S_OFFSET(122),
      R => RSTP
    );
\S_OFFSET_reg[123]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_OFFSET_reg[112]_0\(7),
      D => \S_SAMPLE_TIME_reg[30]_1\(11),
      Q => S_OFFSET(123),
      R => RSTP
    );
\S_OFFSET_reg[124]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_OFFSET_reg[112]_0\(7),
      D => \S_SAMPLE_TIME_reg[30]_1\(12),
      Q => S_OFFSET(124),
      R => RSTP
    );
\S_OFFSET_reg[125]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_OFFSET_reg[112]_0\(7),
      D => \S_SAMPLE_TIME_reg[30]_1\(13),
      Q => S_OFFSET(125),
      R => RSTP
    );
\S_OFFSET_reg[126]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_OFFSET_reg[112]_0\(7),
      D => \S_SAMPLE_TIME_reg[30]_1\(14),
      Q => S_OFFSET(126),
      R => RSTP
    );
\S_OFFSET_reg[127]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_OFFSET_reg[112]_0\(7),
      D => \S_SAMPLE_TIME_reg[30]_1\(15),
      Q => S_OFFSET(127),
      R => RSTP
    );
\S_OFFSET_reg[12]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_OFFSET_reg[112]_0\(0),
      D => \S_SAMPLE_TIME_reg[30]_1\(12),
      Q => S_OFFSET(12),
      R => RSTP
    );
\S_OFFSET_reg[13]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_OFFSET_reg[112]_0\(0),
      D => \S_SAMPLE_TIME_reg[30]_1\(13),
      Q => S_OFFSET(13),
      R => RSTP
    );
\S_OFFSET_reg[14]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_OFFSET_reg[112]_0\(0),
      D => \S_SAMPLE_TIME_reg[30]_1\(14),
      Q => S_OFFSET(14),
      R => RSTP
    );
\S_OFFSET_reg[15]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_OFFSET_reg[112]_0\(0),
      D => \S_SAMPLE_TIME_reg[30]_1\(15),
      Q => S_OFFSET(15),
      R => RSTP
    );
\S_OFFSET_reg[16]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_OFFSET_reg[112]_0\(1),
      D => \S_SAMPLE_TIME_reg[30]_1\(0),
      Q => S_OFFSET(16),
      R => RSTP
    );
\S_OFFSET_reg[17]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_OFFSET_reg[112]_0\(1),
      D => \S_SAMPLE_TIME_reg[30]_1\(1),
      Q => S_OFFSET(17),
      R => RSTP
    );
\S_OFFSET_reg[18]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_OFFSET_reg[112]_0\(1),
      D => \S_SAMPLE_TIME_reg[30]_1\(2),
      Q => S_OFFSET(18),
      R => RSTP
    );
\S_OFFSET_reg[19]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_OFFSET_reg[112]_0\(1),
      D => \S_SAMPLE_TIME_reg[30]_1\(3),
      Q => S_OFFSET(19),
      R => RSTP
    );
\S_OFFSET_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_OFFSET_reg[112]_0\(0),
      D => \S_SAMPLE_TIME_reg[30]_1\(1),
      Q => S_OFFSET(1),
      R => RSTP
    );
\S_OFFSET_reg[20]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_OFFSET_reg[112]_0\(1),
      D => \S_SAMPLE_TIME_reg[30]_1\(4),
      Q => S_OFFSET(20),
      R => RSTP
    );
\S_OFFSET_reg[21]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_OFFSET_reg[112]_0\(1),
      D => \S_SAMPLE_TIME_reg[30]_1\(5),
      Q => S_OFFSET(21),
      R => RSTP
    );
\S_OFFSET_reg[22]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_OFFSET_reg[112]_0\(1),
      D => \S_SAMPLE_TIME_reg[30]_1\(6),
      Q => S_OFFSET(22),
      R => RSTP
    );
\S_OFFSET_reg[23]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_OFFSET_reg[112]_0\(1),
      D => \S_SAMPLE_TIME_reg[30]_1\(7),
      Q => S_OFFSET(23),
      R => RSTP
    );
\S_OFFSET_reg[24]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_OFFSET_reg[112]_0\(1),
      D => \S_SAMPLE_TIME_reg[30]_1\(8),
      Q => S_OFFSET(24),
      R => RSTP
    );
\S_OFFSET_reg[25]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_OFFSET_reg[112]_0\(1),
      D => \S_SAMPLE_TIME_reg[30]_1\(9),
      Q => S_OFFSET(25),
      R => RSTP
    );
\S_OFFSET_reg[26]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_OFFSET_reg[112]_0\(1),
      D => \S_SAMPLE_TIME_reg[30]_1\(10),
      Q => S_OFFSET(26),
      R => RSTP
    );
\S_OFFSET_reg[27]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_OFFSET_reg[112]_0\(1),
      D => \S_SAMPLE_TIME_reg[30]_1\(11),
      Q => S_OFFSET(27),
      R => RSTP
    );
\S_OFFSET_reg[28]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_OFFSET_reg[112]_0\(1),
      D => \S_SAMPLE_TIME_reg[30]_1\(12),
      Q => S_OFFSET(28),
      R => RSTP
    );
\S_OFFSET_reg[29]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_OFFSET_reg[112]_0\(1),
      D => \S_SAMPLE_TIME_reg[30]_1\(13),
      Q => S_OFFSET(29),
      R => RSTP
    );
\S_OFFSET_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_OFFSET_reg[112]_0\(0),
      D => \S_SAMPLE_TIME_reg[30]_1\(2),
      Q => S_OFFSET(2),
      R => RSTP
    );
\S_OFFSET_reg[30]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_OFFSET_reg[112]_0\(1),
      D => \S_SAMPLE_TIME_reg[30]_1\(14),
      Q => S_OFFSET(30),
      R => RSTP
    );
\S_OFFSET_reg[31]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_OFFSET_reg[112]_0\(1),
      D => \S_SAMPLE_TIME_reg[30]_1\(15),
      Q => S_OFFSET(31),
      R => RSTP
    );
\S_OFFSET_reg[32]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_OFFSET_reg[112]_0\(2),
      D => \S_SAMPLE_TIME_reg[30]_1\(0),
      Q => S_OFFSET(32),
      R => RSTP
    );
\S_OFFSET_reg[33]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_OFFSET_reg[112]_0\(2),
      D => \S_SAMPLE_TIME_reg[30]_1\(1),
      Q => S_OFFSET(33),
      R => RSTP
    );
\S_OFFSET_reg[34]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_OFFSET_reg[112]_0\(2),
      D => \S_SAMPLE_TIME_reg[30]_1\(2),
      Q => S_OFFSET(34),
      R => RSTP
    );
\S_OFFSET_reg[35]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_OFFSET_reg[112]_0\(2),
      D => \S_SAMPLE_TIME_reg[30]_1\(3),
      Q => S_OFFSET(35),
      R => RSTP
    );
\S_OFFSET_reg[36]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_OFFSET_reg[112]_0\(2),
      D => \S_SAMPLE_TIME_reg[30]_1\(4),
      Q => S_OFFSET(36),
      R => RSTP
    );
\S_OFFSET_reg[37]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_OFFSET_reg[112]_0\(2),
      D => \S_SAMPLE_TIME_reg[30]_1\(5),
      Q => S_OFFSET(37),
      R => RSTP
    );
\S_OFFSET_reg[38]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_OFFSET_reg[112]_0\(2),
      D => \S_SAMPLE_TIME_reg[30]_1\(6),
      Q => S_OFFSET(38),
      R => RSTP
    );
\S_OFFSET_reg[39]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_OFFSET_reg[112]_0\(2),
      D => \S_SAMPLE_TIME_reg[30]_1\(7),
      Q => S_OFFSET(39),
      R => RSTP
    );
\S_OFFSET_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_OFFSET_reg[112]_0\(0),
      D => \S_SAMPLE_TIME_reg[30]_1\(3),
      Q => S_OFFSET(3),
      R => RSTP
    );
\S_OFFSET_reg[40]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_OFFSET_reg[112]_0\(2),
      D => \S_SAMPLE_TIME_reg[30]_1\(8),
      Q => S_OFFSET(40),
      R => RSTP
    );
\S_OFFSET_reg[41]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_OFFSET_reg[112]_0\(2),
      D => \S_SAMPLE_TIME_reg[30]_1\(9),
      Q => S_OFFSET(41),
      R => RSTP
    );
\S_OFFSET_reg[42]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_OFFSET_reg[112]_0\(2),
      D => \S_SAMPLE_TIME_reg[30]_1\(10),
      Q => S_OFFSET(42),
      R => RSTP
    );
\S_OFFSET_reg[43]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_OFFSET_reg[112]_0\(2),
      D => \S_SAMPLE_TIME_reg[30]_1\(11),
      Q => S_OFFSET(43),
      R => RSTP
    );
\S_OFFSET_reg[44]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_OFFSET_reg[112]_0\(2),
      D => \S_SAMPLE_TIME_reg[30]_1\(12),
      Q => S_OFFSET(44),
      R => RSTP
    );
\S_OFFSET_reg[45]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_OFFSET_reg[112]_0\(2),
      D => \S_SAMPLE_TIME_reg[30]_1\(13),
      Q => S_OFFSET(45),
      R => RSTP
    );
\S_OFFSET_reg[46]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_OFFSET_reg[112]_0\(2),
      D => \S_SAMPLE_TIME_reg[30]_1\(14),
      Q => S_OFFSET(46),
      R => RSTP
    );
\S_OFFSET_reg[47]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_OFFSET_reg[112]_0\(2),
      D => \S_SAMPLE_TIME_reg[30]_1\(15),
      Q => S_OFFSET(47),
      R => RSTP
    );
\S_OFFSET_reg[48]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_OFFSET_reg[112]_0\(3),
      D => \S_SAMPLE_TIME_reg[30]_1\(0),
      Q => S_OFFSET(48),
      R => RSTP
    );
\S_OFFSET_reg[49]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_OFFSET_reg[112]_0\(3),
      D => \S_SAMPLE_TIME_reg[30]_1\(1),
      Q => S_OFFSET(49),
      R => RSTP
    );
\S_OFFSET_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_OFFSET_reg[112]_0\(0),
      D => \S_SAMPLE_TIME_reg[30]_1\(4),
      Q => S_OFFSET(4),
      R => RSTP
    );
\S_OFFSET_reg[50]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_OFFSET_reg[112]_0\(3),
      D => \S_SAMPLE_TIME_reg[30]_1\(2),
      Q => S_OFFSET(50),
      R => RSTP
    );
\S_OFFSET_reg[51]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_OFFSET_reg[112]_0\(3),
      D => \S_SAMPLE_TIME_reg[30]_1\(3),
      Q => S_OFFSET(51),
      R => RSTP
    );
\S_OFFSET_reg[52]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_OFFSET_reg[112]_0\(3),
      D => \S_SAMPLE_TIME_reg[30]_1\(4),
      Q => S_OFFSET(52),
      R => RSTP
    );
\S_OFFSET_reg[53]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_OFFSET_reg[112]_0\(3),
      D => \S_SAMPLE_TIME_reg[30]_1\(5),
      Q => S_OFFSET(53),
      R => RSTP
    );
\S_OFFSET_reg[54]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_OFFSET_reg[112]_0\(3),
      D => \S_SAMPLE_TIME_reg[30]_1\(6),
      Q => S_OFFSET(54),
      R => RSTP
    );
\S_OFFSET_reg[55]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_OFFSET_reg[112]_0\(3),
      D => \S_SAMPLE_TIME_reg[30]_1\(7),
      Q => S_OFFSET(55),
      R => RSTP
    );
\S_OFFSET_reg[56]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_OFFSET_reg[112]_0\(3),
      D => \S_SAMPLE_TIME_reg[30]_1\(8),
      Q => S_OFFSET(56),
      R => RSTP
    );
\S_OFFSET_reg[57]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_OFFSET_reg[112]_0\(3),
      D => \S_SAMPLE_TIME_reg[30]_1\(9),
      Q => S_OFFSET(57),
      R => RSTP
    );
\S_OFFSET_reg[58]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_OFFSET_reg[112]_0\(3),
      D => \S_SAMPLE_TIME_reg[30]_1\(10),
      Q => S_OFFSET(58),
      R => RSTP
    );
\S_OFFSET_reg[59]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_OFFSET_reg[112]_0\(3),
      D => \S_SAMPLE_TIME_reg[30]_1\(11),
      Q => S_OFFSET(59),
      R => RSTP
    );
\S_OFFSET_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_OFFSET_reg[112]_0\(0),
      D => \S_SAMPLE_TIME_reg[30]_1\(5),
      Q => S_OFFSET(5),
      R => RSTP
    );
\S_OFFSET_reg[60]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_OFFSET_reg[112]_0\(3),
      D => \S_SAMPLE_TIME_reg[30]_1\(12),
      Q => S_OFFSET(60),
      R => RSTP
    );
\S_OFFSET_reg[61]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_OFFSET_reg[112]_0\(3),
      D => \S_SAMPLE_TIME_reg[30]_1\(13),
      Q => S_OFFSET(61),
      R => RSTP
    );
\S_OFFSET_reg[62]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_OFFSET_reg[112]_0\(3),
      D => \S_SAMPLE_TIME_reg[30]_1\(14),
      Q => S_OFFSET(62),
      R => RSTP
    );
\S_OFFSET_reg[63]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_OFFSET_reg[112]_0\(3),
      D => \S_SAMPLE_TIME_reg[30]_1\(15),
      Q => S_OFFSET(63),
      R => RSTP
    );
\S_OFFSET_reg[64]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_OFFSET_reg[112]_0\(4),
      D => \S_SAMPLE_TIME_reg[30]_1\(0),
      Q => S_OFFSET(64),
      R => RSTP
    );
\S_OFFSET_reg[65]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_OFFSET_reg[112]_0\(4),
      D => \S_SAMPLE_TIME_reg[30]_1\(1),
      Q => S_OFFSET(65),
      R => RSTP
    );
\S_OFFSET_reg[66]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_OFFSET_reg[112]_0\(4),
      D => \S_SAMPLE_TIME_reg[30]_1\(2),
      Q => S_OFFSET(66),
      R => RSTP
    );
\S_OFFSET_reg[67]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_OFFSET_reg[112]_0\(4),
      D => \S_SAMPLE_TIME_reg[30]_1\(3),
      Q => S_OFFSET(67),
      R => RSTP
    );
\S_OFFSET_reg[68]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_OFFSET_reg[112]_0\(4),
      D => \S_SAMPLE_TIME_reg[30]_1\(4),
      Q => S_OFFSET(68),
      R => RSTP
    );
\S_OFFSET_reg[69]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_OFFSET_reg[112]_0\(4),
      D => \S_SAMPLE_TIME_reg[30]_1\(5),
      Q => S_OFFSET(69),
      R => RSTP
    );
\S_OFFSET_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_OFFSET_reg[112]_0\(0),
      D => \S_SAMPLE_TIME_reg[30]_1\(6),
      Q => S_OFFSET(6),
      R => RSTP
    );
\S_OFFSET_reg[70]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_OFFSET_reg[112]_0\(4),
      D => \S_SAMPLE_TIME_reg[30]_1\(6),
      Q => S_OFFSET(70),
      R => RSTP
    );
\S_OFFSET_reg[71]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_OFFSET_reg[112]_0\(4),
      D => \S_SAMPLE_TIME_reg[30]_1\(7),
      Q => S_OFFSET(71),
      R => RSTP
    );
\S_OFFSET_reg[72]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_OFFSET_reg[112]_0\(4),
      D => \S_SAMPLE_TIME_reg[30]_1\(8),
      Q => S_OFFSET(72),
      R => RSTP
    );
\S_OFFSET_reg[73]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_OFFSET_reg[112]_0\(4),
      D => \S_SAMPLE_TIME_reg[30]_1\(9),
      Q => S_OFFSET(73),
      R => RSTP
    );
\S_OFFSET_reg[74]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_OFFSET_reg[112]_0\(4),
      D => \S_SAMPLE_TIME_reg[30]_1\(10),
      Q => S_OFFSET(74),
      R => RSTP
    );
\S_OFFSET_reg[75]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_OFFSET_reg[112]_0\(4),
      D => \S_SAMPLE_TIME_reg[30]_1\(11),
      Q => S_OFFSET(75),
      R => RSTP
    );
\S_OFFSET_reg[76]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_OFFSET_reg[112]_0\(4),
      D => \S_SAMPLE_TIME_reg[30]_1\(12),
      Q => S_OFFSET(76),
      R => RSTP
    );
\S_OFFSET_reg[77]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_OFFSET_reg[112]_0\(4),
      D => \S_SAMPLE_TIME_reg[30]_1\(13),
      Q => S_OFFSET(77),
      R => RSTP
    );
\S_OFFSET_reg[78]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_OFFSET_reg[112]_0\(4),
      D => \S_SAMPLE_TIME_reg[30]_1\(14),
      Q => S_OFFSET(78),
      R => RSTP
    );
\S_OFFSET_reg[79]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_OFFSET_reg[112]_0\(4),
      D => \S_SAMPLE_TIME_reg[30]_1\(15),
      Q => S_OFFSET(79),
      R => RSTP
    );
\S_OFFSET_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_OFFSET_reg[112]_0\(0),
      D => \S_SAMPLE_TIME_reg[30]_1\(7),
      Q => S_OFFSET(7),
      R => RSTP
    );
\S_OFFSET_reg[80]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_OFFSET_reg[112]_0\(5),
      D => \S_SAMPLE_TIME_reg[30]_1\(0),
      Q => S_OFFSET(80),
      R => RSTP
    );
\S_OFFSET_reg[81]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_OFFSET_reg[112]_0\(5),
      D => \S_SAMPLE_TIME_reg[30]_1\(1),
      Q => S_OFFSET(81),
      R => RSTP
    );
\S_OFFSET_reg[82]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_OFFSET_reg[112]_0\(5),
      D => \S_SAMPLE_TIME_reg[30]_1\(2),
      Q => S_OFFSET(82),
      R => RSTP
    );
\S_OFFSET_reg[83]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_OFFSET_reg[112]_0\(5),
      D => \S_SAMPLE_TIME_reg[30]_1\(3),
      Q => S_OFFSET(83),
      R => RSTP
    );
\S_OFFSET_reg[84]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_OFFSET_reg[112]_0\(5),
      D => \S_SAMPLE_TIME_reg[30]_1\(4),
      Q => S_OFFSET(84),
      R => RSTP
    );
\S_OFFSET_reg[85]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_OFFSET_reg[112]_0\(5),
      D => \S_SAMPLE_TIME_reg[30]_1\(5),
      Q => S_OFFSET(85),
      R => RSTP
    );
\S_OFFSET_reg[86]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_OFFSET_reg[112]_0\(5),
      D => \S_SAMPLE_TIME_reg[30]_1\(6),
      Q => S_OFFSET(86),
      R => RSTP
    );
\S_OFFSET_reg[87]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_OFFSET_reg[112]_0\(5),
      D => \S_SAMPLE_TIME_reg[30]_1\(7),
      Q => S_OFFSET(87),
      R => RSTP
    );
\S_OFFSET_reg[88]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_OFFSET_reg[112]_0\(5),
      D => \S_SAMPLE_TIME_reg[30]_1\(8),
      Q => S_OFFSET(88),
      R => RSTP
    );
\S_OFFSET_reg[89]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_OFFSET_reg[112]_0\(5),
      D => \S_SAMPLE_TIME_reg[30]_1\(9),
      Q => S_OFFSET(89),
      R => RSTP
    );
\S_OFFSET_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_OFFSET_reg[112]_0\(0),
      D => \S_SAMPLE_TIME_reg[30]_1\(8),
      Q => S_OFFSET(8),
      R => RSTP
    );
\S_OFFSET_reg[90]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_OFFSET_reg[112]_0\(5),
      D => \S_SAMPLE_TIME_reg[30]_1\(10),
      Q => S_OFFSET(90),
      R => RSTP
    );
\S_OFFSET_reg[91]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_OFFSET_reg[112]_0\(5),
      D => \S_SAMPLE_TIME_reg[30]_1\(11),
      Q => S_OFFSET(91),
      R => RSTP
    );
\S_OFFSET_reg[92]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_OFFSET_reg[112]_0\(5),
      D => \S_SAMPLE_TIME_reg[30]_1\(12),
      Q => S_OFFSET(92),
      R => RSTP
    );
\S_OFFSET_reg[93]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_OFFSET_reg[112]_0\(5),
      D => \S_SAMPLE_TIME_reg[30]_1\(13),
      Q => S_OFFSET(93),
      R => RSTP
    );
\S_OFFSET_reg[94]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_OFFSET_reg[112]_0\(5),
      D => \S_SAMPLE_TIME_reg[30]_1\(14),
      Q => S_OFFSET(94),
      R => RSTP
    );
\S_OFFSET_reg[95]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_OFFSET_reg[112]_0\(5),
      D => \S_SAMPLE_TIME_reg[30]_1\(15),
      Q => S_OFFSET(95),
      R => RSTP
    );
\S_OFFSET_reg[96]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_OFFSET_reg[112]_0\(6),
      D => \S_SAMPLE_TIME_reg[30]_1\(0),
      Q => S_OFFSET(96),
      R => RSTP
    );
\S_OFFSET_reg[97]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_OFFSET_reg[112]_0\(6),
      D => \S_SAMPLE_TIME_reg[30]_1\(1),
      Q => S_OFFSET(97),
      R => RSTP
    );
\S_OFFSET_reg[98]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_OFFSET_reg[112]_0\(6),
      D => \S_SAMPLE_TIME_reg[30]_1\(2),
      Q => S_OFFSET(98),
      R => RSTP
    );
\S_OFFSET_reg[99]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_OFFSET_reg[112]_0\(6),
      D => \S_SAMPLE_TIME_reg[30]_1\(3),
      Q => S_OFFSET(99),
      R => RSTP
    );
\S_OFFSET_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_OFFSET_reg[112]_0\(0),
      D => \S_SAMPLE_TIME_reg[30]_1\(9),
      Q => S_OFFSET(9),
      R => RSTP
    );
\S_RAW_VALUE_S_C[15]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0000000055555554"
    )
        port map (
      I0 => \^s_enable_reg[0]\,
      I1 => S_CHANNEL_COUNTER(2),
      I2 => S_CHANNEL_COUNTER(0),
      I3 => S_CHANNEL_COUNTER(1),
      I4 => S_CHANNEL_COUNTER(3),
      I5 => \^s_enable_reg[0]_0\,
      O => S_OFFSET_S_C
    );
\S_RAW_VALUE_S_C[15]_i_3\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"01"
    )
        port map (
      I0 => S_CHANNEL_COUNTER(1),
      I1 => S_CHANNEL_COUNTER(0),
      I2 => S_CHANNEL_COUNTER(2),
      O => \S_RAW_VALUE_S_C[15]_i_3_n_0\
    );
\S_RAW_VALUE_S_C_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_OFFSET_S_C,
      D => spi_n_20,
      Q => S_RAW_VALUE_S_C(0),
      R => RSTP
    );
\S_RAW_VALUE_S_C_reg[10]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_OFFSET_S_C,
      D => spi_n_10,
      Q => S_RAW_VALUE_S_C(10),
      R => RSTP
    );
\S_RAW_VALUE_S_C_reg[11]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_OFFSET_S_C,
      D => spi_n_9,
      Q => S_RAW_VALUE_S_C(11),
      R => RSTP
    );
\S_RAW_VALUE_S_C_reg[12]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_OFFSET_S_C,
      D => spi_n_8,
      Q => S_RAW_VALUE_S_C(12),
      R => RSTP
    );
\S_RAW_VALUE_S_C_reg[13]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_OFFSET_S_C,
      D => spi_n_7,
      Q => S_RAW_VALUE_S_C(13),
      R => RSTP
    );
\S_RAW_VALUE_S_C_reg[14]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_OFFSET_S_C,
      D => spi_n_6,
      Q => S_RAW_VALUE_S_C(14),
      R => RSTP
    );
\S_RAW_VALUE_S_C_reg[15]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_OFFSET_S_C,
      D => spi_n_5,
      Q => S_RAW_VALUE_S_C(15),
      R => RSTP
    );
\S_RAW_VALUE_S_C_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_OFFSET_S_C,
      D => spi_n_19,
      Q => S_RAW_VALUE_S_C(1),
      R => RSTP
    );
\S_RAW_VALUE_S_C_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_OFFSET_S_C,
      D => spi_n_18,
      Q => S_RAW_VALUE_S_C(2),
      R => RSTP
    );
\S_RAW_VALUE_S_C_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_OFFSET_S_C,
      D => spi_n_17,
      Q => S_RAW_VALUE_S_C(3),
      R => RSTP
    );
\S_RAW_VALUE_S_C_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_OFFSET_S_C,
      D => spi_n_16,
      Q => S_RAW_VALUE_S_C(4),
      R => RSTP
    );
\S_RAW_VALUE_S_C_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_OFFSET_S_C,
      D => spi_n_15,
      Q => S_RAW_VALUE_S_C(5),
      R => RSTP
    );
\S_RAW_VALUE_S_C_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_OFFSET_S_C,
      D => spi_n_14,
      Q => S_RAW_VALUE_S_C(6),
      R => RSTP
    );
\S_RAW_VALUE_S_C_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_OFFSET_S_C,
      D => spi_n_13,
      Q => S_RAW_VALUE_S_C(7),
      R => RSTP
    );
\S_RAW_VALUE_S_C_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_OFFSET_S_C,
      D => spi_n_12,
      Q => S_RAW_VALUE_S_C(8),
      R => RSTP
    );
\S_RAW_VALUE_S_C_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_OFFSET_S_C,
      D => spi_n_11,
      Q => S_RAW_VALUE_S_C(9),
      R => RSTP
    );
\S_RESULT_COUNTER[0]_i_1\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"B"
    )
        port map (
      I0 => \^s_enable_reg[0]_0\,
      I1 => S_RESULT_COUNTER(0),
      O => \S_RESULT_COUNTER[0]_i_1_n_0\
    );
\S_RESULT_COUNTER[0]_rep_i_1\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"B"
    )
        port map (
      I0 => \^s_enable_reg[0]_0\,
      I1 => S_RESULT_COUNTER(0),
      O => \S_RESULT_COUNTER[0]_rep_i_1_n_0\
    );
\S_RESULT_COUNTER[1]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"EB"
    )
        port map (
      I0 => \^s_enable_reg[0]_0\,
      I1 => S_RESULT_COUNTER(1),
      I2 => \S_RESULT_COUNTER_reg[0]_rep_n_0\,
      O => \S_RESULT_COUNTER[1]_i_1_n_0\
    );
\S_RESULT_COUNTER[1]_rep_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"EB"
    )
        port map (
      I0 => \^s_enable_reg[0]_0\,
      I1 => S_RESULT_COUNTER(1),
      I2 => \S_RESULT_COUNTER_reg[0]_rep_n_0\,
      O => \S_RESULT_COUNTER[1]_rep_i_1_n_0\
    );
\S_RESULT_COUNTER[2]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"00E1"
    )
        port map (
      I0 => \S_RESULT_COUNTER_reg[0]_rep_n_0\,
      I1 => S_RESULT_COUNTER(1),
      I2 => S_RESULT_COUNTER(2),
      I3 => \^s_enable_reg[0]_0\,
      O => B(2)
    );
\S_RESULT_COUNTER[3]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AAAAAAAAAAAAAAA8"
    )
        port map (
      I0 => \S_RESULT_COUNTER[3]_i_3_n_0\,
      I1 => \^s_enable_reg[0]_0\,
      I2 => S_RESULT_COUNTER(2),
      I3 => S_RESULT_COUNTER(3),
      I4 => S_RESULT_COUNTER(1),
      I5 => \S_RESULT_COUNTER_reg[0]_rep_n_0\,
      O => CEB2
    );
\S_RESULT_COUNTER[3]_i_2\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFFEAAAB"
    )
        port map (
      I0 => \^s_enable_reg[0]_0\,
      I1 => S_RESULT_COUNTER(2),
      I2 => S_RESULT_COUNTER(1),
      I3 => \S_RESULT_COUNTER_reg[0]_rep_n_0\,
      I4 => S_RESULT_COUNTER(3),
      O => B(3)
    );
\S_RESULT_COUNTER[3]_i_3\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"0455"
    )
        port map (
      I0 => \^s_enable_reg[0]\,
      I1 => \^q\(0),
      I2 => \^q\(1),
      I3 => \^s_enable_reg[0]_0\,
      O => \S_RESULT_COUNTER[3]_i_3_n_0\
    );
\S_RESULT_COUNTER_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => CEB2,
      D => \S_RESULT_COUNTER[0]_i_1_n_0\,
      Q => S_RESULT_COUNTER(0),
      R => RSTP
    );
\S_RESULT_COUNTER_reg[0]_rep\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => CEB2,
      D => \S_RESULT_COUNTER[0]_rep_i_1_n_0\,
      Q => \S_RESULT_COUNTER_reg[0]_rep_n_0\,
      R => RSTP
    );
\S_RESULT_COUNTER_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => CEB2,
      D => \S_RESULT_COUNTER[1]_i_1_n_0\,
      Q => S_RESULT_COUNTER(1),
      R => RSTP
    );
\S_RESULT_COUNTER_reg[1]_rep\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => CEB2,
      D => \S_RESULT_COUNTER[1]_rep_i_1_n_0\,
      Q => \S_RESULT_COUNTER_reg[1]_rep_n_0\,
      R => RSTP
    );
\S_RESULT_COUNTER_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => CEB2,
      D => B(2),
      Q => S_RESULT_COUNTER(2),
      R => RSTP
    );
\S_RESULT_COUNTER_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => CEB2,
      D => B(3),
      Q => S_RESULT_COUNTER(3),
      R => RSTP
    );
\S_SAMPLES[30]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"02"
    )
        port map (
      I0 => SET_SAMPLES,
      I1 => SET_CONVERSION,
      I2 => SET_OFFSET,
      O => S_SAMPLES
    );
\S_SAMPLES_reg[0]\: unisim.vcomponents.FDSE
     port map (
      C => s00_axi_aclk,
      CE => S_SAMPLES,
      D => \S_SAMPLE_TIME_reg[30]_1\(0),
      Q => \S_SAMPLES_reg_n_0_[0]\,
      S => RSTP
    );
\S_SAMPLES_reg[10]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_SAMPLES,
      D => \S_SAMPLE_TIME_reg[30]_1\(10),
      Q => \S_SAMPLES_reg_n_0_[10]\,
      R => RSTP
    );
\S_SAMPLES_reg[11]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_SAMPLES,
      D => \S_SAMPLE_TIME_reg[30]_1\(11),
      Q => \S_SAMPLES_reg_n_0_[11]\,
      R => RSTP
    );
\S_SAMPLES_reg[12]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_SAMPLES,
      D => \S_SAMPLE_TIME_reg[30]_1\(12),
      Q => \S_SAMPLES_reg_n_0_[12]\,
      R => RSTP
    );
\S_SAMPLES_reg[13]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_SAMPLES,
      D => \S_SAMPLE_TIME_reg[30]_1\(13),
      Q => \S_SAMPLES_reg_n_0_[13]\,
      R => RSTP
    );
\S_SAMPLES_reg[14]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_SAMPLES,
      D => \S_SAMPLE_TIME_reg[30]_1\(14),
      Q => \S_SAMPLES_reg_n_0_[14]\,
      R => RSTP
    );
\S_SAMPLES_reg[15]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_SAMPLES,
      D => \S_SAMPLE_TIME_reg[30]_1\(15),
      Q => \S_SAMPLES_reg_n_0_[15]\,
      R => RSTP
    );
\S_SAMPLES_reg[16]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_SAMPLES,
      D => \S_SAMPLE_TIME_reg[30]_1\(16),
      Q => \S_SAMPLES_reg_n_0_[16]\,
      R => RSTP
    );
\S_SAMPLES_reg[17]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_SAMPLES,
      D => \S_SAMPLE_TIME_reg[30]_1\(17),
      Q => \S_SAMPLES_reg_n_0_[17]\,
      R => RSTP
    );
\S_SAMPLES_reg[18]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_SAMPLES,
      D => \S_SAMPLE_TIME_reg[30]_1\(18),
      Q => \S_SAMPLES_reg_n_0_[18]\,
      R => RSTP
    );
\S_SAMPLES_reg[19]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_SAMPLES,
      D => \S_SAMPLE_TIME_reg[30]_1\(19),
      Q => \S_SAMPLES_reg_n_0_[19]\,
      R => RSTP
    );
\S_SAMPLES_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_SAMPLES,
      D => \S_SAMPLE_TIME_reg[30]_1\(1),
      Q => \S_SAMPLES_reg_n_0_[1]\,
      R => RSTP
    );
\S_SAMPLES_reg[20]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_SAMPLES,
      D => \S_SAMPLE_TIME_reg[30]_1\(20),
      Q => \S_SAMPLES_reg_n_0_[20]\,
      R => RSTP
    );
\S_SAMPLES_reg[21]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_SAMPLES,
      D => \S_SAMPLE_TIME_reg[30]_1\(21),
      Q => \S_SAMPLES_reg_n_0_[21]\,
      R => RSTP
    );
\S_SAMPLES_reg[22]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_SAMPLES,
      D => \S_SAMPLE_TIME_reg[30]_1\(22),
      Q => \S_SAMPLES_reg_n_0_[22]\,
      R => RSTP
    );
\S_SAMPLES_reg[23]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_SAMPLES,
      D => \S_SAMPLE_TIME_reg[30]_1\(23),
      Q => \S_SAMPLES_reg_n_0_[23]\,
      R => RSTP
    );
\S_SAMPLES_reg[24]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_SAMPLES,
      D => \S_SAMPLE_TIME_reg[30]_1\(24),
      Q => \S_SAMPLES_reg_n_0_[24]\,
      R => RSTP
    );
\S_SAMPLES_reg[25]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_SAMPLES,
      D => \S_SAMPLE_TIME_reg[30]_1\(25),
      Q => \S_SAMPLES_reg_n_0_[25]\,
      R => RSTP
    );
\S_SAMPLES_reg[26]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_SAMPLES,
      D => \S_SAMPLE_TIME_reg[30]_1\(26),
      Q => \S_SAMPLES_reg_n_0_[26]\,
      R => RSTP
    );
\S_SAMPLES_reg[27]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_SAMPLES,
      D => \S_SAMPLE_TIME_reg[30]_1\(27),
      Q => \S_SAMPLES_reg_n_0_[27]\,
      R => RSTP
    );
\S_SAMPLES_reg[28]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_SAMPLES,
      D => \S_SAMPLE_TIME_reg[30]_1\(28),
      Q => \S_SAMPLES_reg_n_0_[28]\,
      R => RSTP
    );
\S_SAMPLES_reg[29]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_SAMPLES,
      D => \S_SAMPLE_TIME_reg[30]_1\(29),
      Q => \S_SAMPLES_reg_n_0_[29]\,
      R => RSTP
    );
\S_SAMPLES_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_SAMPLES,
      D => \S_SAMPLE_TIME_reg[30]_1\(2),
      Q => \S_SAMPLES_reg_n_0_[2]\,
      R => RSTP
    );
\S_SAMPLES_reg[30]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_SAMPLES,
      D => \S_SAMPLE_TIME_reg[30]_1\(30),
      Q => \S_SAMPLES_reg_n_0_[30]\,
      R => RSTP
    );
\S_SAMPLES_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_SAMPLES,
      D => \S_SAMPLE_TIME_reg[30]_1\(3),
      Q => \S_SAMPLES_reg_n_0_[3]\,
      R => RSTP
    );
\S_SAMPLES_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_SAMPLES,
      D => \S_SAMPLE_TIME_reg[30]_1\(4),
      Q => \S_SAMPLES_reg_n_0_[4]\,
      R => RSTP
    );
\S_SAMPLES_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_SAMPLES,
      D => \S_SAMPLE_TIME_reg[30]_1\(5),
      Q => \S_SAMPLES_reg_n_0_[5]\,
      R => RSTP
    );
\S_SAMPLES_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_SAMPLES,
      D => \S_SAMPLE_TIME_reg[30]_1\(6),
      Q => \S_SAMPLES_reg_n_0_[6]\,
      R => RSTP
    );
\S_SAMPLES_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_SAMPLES,
      D => \S_SAMPLE_TIME_reg[30]_1\(7),
      Q => \S_SAMPLES_reg_n_0_[7]\,
      R => RSTP
    );
\S_SAMPLES_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_SAMPLES,
      D => \S_SAMPLE_TIME_reg[30]_1\(8),
      Q => \S_SAMPLES_reg_n_0_[8]\,
      R => RSTP
    );
\S_SAMPLES_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_SAMPLES,
      D => \S_SAMPLE_TIME_reg[30]_1\(9),
      Q => \S_SAMPLES_reg_n_0_[9]\,
      R => RSTP
    );
\S_SAMPLE_COUNTER[0]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AB"
    )
        port map (
      I0 => \^s_enable_reg[0]\,
      I1 => \^s_sample_counter_reg[0]_0\,
      I2 => V_SAMPLE_COUNTER2(31),
      O => \S_SAMPLE_COUNTER[0]_i_1_n_0\
    );
\S_SAMPLE_COUNTER[10]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AE"
    )
        port map (
      I0 => \^s_enable_reg[0]\,
      I1 => V_SAMPLE_COUNTER2(10),
      I2 => V_SAMPLE_COUNTER2(31),
      O => \S_SAMPLE_COUNTER[10]_i_1_n_0\
    );
\S_SAMPLE_COUNTER[11]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AE"
    )
        port map (
      I0 => \^s_enable_reg[0]\,
      I1 => V_SAMPLE_COUNTER2(11),
      I2 => V_SAMPLE_COUNTER2(31),
      O => \S_SAMPLE_COUNTER[11]_i_1_n_0\
    );
\S_SAMPLE_COUNTER[12]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AE"
    )
        port map (
      I0 => \^s_enable_reg[0]\,
      I1 => V_SAMPLE_COUNTER2(12),
      I2 => V_SAMPLE_COUNTER2(31),
      O => \S_SAMPLE_COUNTER[12]_i_1_n_0\
    );
\S_SAMPLE_COUNTER[13]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AE"
    )
        port map (
      I0 => \^s_enable_reg[0]\,
      I1 => V_SAMPLE_COUNTER2(13),
      I2 => V_SAMPLE_COUNTER2(31),
      O => \S_SAMPLE_COUNTER[13]_i_1_n_0\
    );
\S_SAMPLE_COUNTER[14]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AE"
    )
        port map (
      I0 => \^s_enable_reg[0]\,
      I1 => V_SAMPLE_COUNTER2(14),
      I2 => V_SAMPLE_COUNTER2(31),
      O => \S_SAMPLE_COUNTER[14]_i_1_n_0\
    );
\S_SAMPLE_COUNTER[15]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AE"
    )
        port map (
      I0 => \^s_enable_reg[0]\,
      I1 => V_SAMPLE_COUNTER2(15),
      I2 => V_SAMPLE_COUNTER2(31),
      O => \S_SAMPLE_COUNTER[15]_i_1_n_0\
    );
\S_SAMPLE_COUNTER[16]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AE"
    )
        port map (
      I0 => \^s_enable_reg[0]\,
      I1 => V_SAMPLE_COUNTER2(16),
      I2 => V_SAMPLE_COUNTER2(31),
      O => \S_SAMPLE_COUNTER[16]_i_1_n_0\
    );
\S_SAMPLE_COUNTER[17]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AE"
    )
        port map (
      I0 => \^s_enable_reg[0]\,
      I1 => V_SAMPLE_COUNTER2(17),
      I2 => V_SAMPLE_COUNTER2(31),
      O => \S_SAMPLE_COUNTER[17]_i_1_n_0\
    );
\S_SAMPLE_COUNTER[18]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AE"
    )
        port map (
      I0 => \^s_enable_reg[0]\,
      I1 => V_SAMPLE_COUNTER2(18),
      I2 => V_SAMPLE_COUNTER2(31),
      O => \S_SAMPLE_COUNTER[18]_i_1_n_0\
    );
\S_SAMPLE_COUNTER[19]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AE"
    )
        port map (
      I0 => \^s_enable_reg[0]\,
      I1 => V_SAMPLE_COUNTER2(19),
      I2 => V_SAMPLE_COUNTER2(31),
      O => \S_SAMPLE_COUNTER[19]_i_1_n_0\
    );
\S_SAMPLE_COUNTER[1]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AE"
    )
        port map (
      I0 => \^s_enable_reg[0]\,
      I1 => V_SAMPLE_COUNTER2(1),
      I2 => V_SAMPLE_COUNTER2(31),
      O => \S_SAMPLE_COUNTER[1]_i_1_n_0\
    );
\S_SAMPLE_COUNTER[20]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AE"
    )
        port map (
      I0 => \^s_enable_reg[0]\,
      I1 => V_SAMPLE_COUNTER2(20),
      I2 => V_SAMPLE_COUNTER2(31),
      O => \S_SAMPLE_COUNTER[20]_i_1_n_0\
    );
\S_SAMPLE_COUNTER[21]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AE"
    )
        port map (
      I0 => \^s_enable_reg[0]\,
      I1 => V_SAMPLE_COUNTER2(21),
      I2 => V_SAMPLE_COUNTER2(31),
      O => \S_SAMPLE_COUNTER[21]_i_1_n_0\
    );
\S_SAMPLE_COUNTER[22]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AE"
    )
        port map (
      I0 => \^s_enable_reg[0]\,
      I1 => V_SAMPLE_COUNTER2(22),
      I2 => V_SAMPLE_COUNTER2(31),
      O => \S_SAMPLE_COUNTER[22]_i_1_n_0\
    );
\S_SAMPLE_COUNTER[23]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AE"
    )
        port map (
      I0 => \^s_enable_reg[0]\,
      I1 => V_SAMPLE_COUNTER2(23),
      I2 => V_SAMPLE_COUNTER2(31),
      O => \S_SAMPLE_COUNTER[23]_i_1_n_0\
    );
\S_SAMPLE_COUNTER[24]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AE"
    )
        port map (
      I0 => \^s_enable_reg[0]\,
      I1 => V_SAMPLE_COUNTER2(24),
      I2 => V_SAMPLE_COUNTER2(31),
      O => \S_SAMPLE_COUNTER[24]_i_1_n_0\
    );
\S_SAMPLE_COUNTER[25]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AE"
    )
        port map (
      I0 => \^s_enable_reg[0]\,
      I1 => V_SAMPLE_COUNTER2(25),
      I2 => V_SAMPLE_COUNTER2(31),
      O => \S_SAMPLE_COUNTER[25]_i_1_n_0\
    );
\S_SAMPLE_COUNTER[26]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AE"
    )
        port map (
      I0 => \^s_enable_reg[0]\,
      I1 => V_SAMPLE_COUNTER2(26),
      I2 => V_SAMPLE_COUNTER2(31),
      O => \S_SAMPLE_COUNTER[26]_i_1_n_0\
    );
\S_SAMPLE_COUNTER[27]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AE"
    )
        port map (
      I0 => \^s_enable_reg[0]\,
      I1 => V_SAMPLE_COUNTER2(27),
      I2 => V_SAMPLE_COUNTER2(31),
      O => \S_SAMPLE_COUNTER[27]_i_1_n_0\
    );
\S_SAMPLE_COUNTER[28]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AE"
    )
        port map (
      I0 => \^s_enable_reg[0]\,
      I1 => V_SAMPLE_COUNTER2(28),
      I2 => V_SAMPLE_COUNTER2(31),
      O => \S_SAMPLE_COUNTER[28]_i_1_n_0\
    );
\S_SAMPLE_COUNTER[29]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AE"
    )
        port map (
      I0 => \^s_enable_reg[0]\,
      I1 => V_SAMPLE_COUNTER2(29),
      I2 => V_SAMPLE_COUNTER2(31),
      O => \S_SAMPLE_COUNTER[29]_i_1_n_0\
    );
\S_SAMPLE_COUNTER[2]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AE"
    )
        port map (
      I0 => \^s_enable_reg[0]\,
      I1 => V_SAMPLE_COUNTER2(2),
      I2 => V_SAMPLE_COUNTER2(31),
      O => \S_SAMPLE_COUNTER[2]_i_1_n_0\
    );
\S_SAMPLE_COUNTER[30]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"BA"
    )
        port map (
      I0 => \^s_enable_reg[0]\,
      I1 => V_SAMPLE_COUNTER2(31),
      I2 => V_SAMPLE_COUNTER2(30),
      O => \S_SAMPLE_COUNTER[30]_i_1_n_0\
    );
\S_SAMPLE_COUNTER[31]_i_1\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"8"
    )
        port map (
      I0 => \^s_enable_reg[0]\,
      I1 => S_SAMPLE_COUNTER,
      O => \S_SAMPLE_COUNTER[31]_i_1_n_0\
    );
\S_SAMPLE_COUNTER[31]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0000000004040444"
    )
        port map (
      I0 => S_CPOL_reg(0),
      I1 => s00_axi_aresetn,
      I2 => \S_SAMPLE_COUNTER[31]_i_3_n_0\,
      I3 => \^q\(0),
      I4 => \^q\(1),
      I5 => \^s_enable_reg[0]_0\,
      O => S_SAMPLE_COUNTER
    );
\S_SAMPLE_COUNTER[31]_i_3\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"F2FFF0FF"
    )
        port map (
      I0 => S_SPI_BUSY_PIPE(1),
      I1 => S_SPI_BUSY_PIPE(0),
      I2 => \^q\(0),
      I3 => \^q\(1),
      I4 => \^s_dummy_sample\,
      O => \S_SAMPLE_COUNTER[31]_i_3_n_0\
    );
\S_SAMPLE_COUNTER[3]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AE"
    )
        port map (
      I0 => \^s_enable_reg[0]\,
      I1 => V_SAMPLE_COUNTER2(3),
      I2 => V_SAMPLE_COUNTER2(31),
      O => \S_SAMPLE_COUNTER[3]_i_1_n_0\
    );
\S_SAMPLE_COUNTER[4]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AE"
    )
        port map (
      I0 => \^s_enable_reg[0]\,
      I1 => V_SAMPLE_COUNTER2(4),
      I2 => V_SAMPLE_COUNTER2(31),
      O => \S_SAMPLE_COUNTER[4]_i_1_n_0\
    );
\S_SAMPLE_COUNTER[5]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AE"
    )
        port map (
      I0 => \^s_enable_reg[0]\,
      I1 => V_SAMPLE_COUNTER2(5),
      I2 => V_SAMPLE_COUNTER2(31),
      O => \S_SAMPLE_COUNTER[5]_i_1_n_0\
    );
\S_SAMPLE_COUNTER[6]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AE"
    )
        port map (
      I0 => \^s_enable_reg[0]\,
      I1 => V_SAMPLE_COUNTER2(6),
      I2 => V_SAMPLE_COUNTER2(31),
      O => \S_SAMPLE_COUNTER[6]_i_1_n_0\
    );
\S_SAMPLE_COUNTER[7]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AE"
    )
        port map (
      I0 => \^s_enable_reg[0]\,
      I1 => V_SAMPLE_COUNTER2(7),
      I2 => V_SAMPLE_COUNTER2(31),
      O => \S_SAMPLE_COUNTER[7]_i_1_n_0\
    );
\S_SAMPLE_COUNTER[8]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AE"
    )
        port map (
      I0 => \^s_enable_reg[0]\,
      I1 => V_SAMPLE_COUNTER2(8),
      I2 => V_SAMPLE_COUNTER2(31),
      O => \S_SAMPLE_COUNTER[8]_i_1_n_0\
    );
\S_SAMPLE_COUNTER[9]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AE"
    )
        port map (
      I0 => \^s_enable_reg[0]\,
      I1 => V_SAMPLE_COUNTER2(9),
      I2 => V_SAMPLE_COUNTER2(31),
      O => \S_SAMPLE_COUNTER[9]_i_1_n_0\
    );
\S_SAMPLE_COUNTER_reg[0]\: unisim.vcomponents.FDSE
     port map (
      C => s00_axi_aclk,
      CE => S_SAMPLE_COUNTER,
      D => \S_SAMPLE_COUNTER[0]_i_1_n_0\,
      Q => \^s_sample_counter_reg[0]_0\,
      S => '0'
    );
\S_SAMPLE_COUNTER_reg[10]\: unisim.vcomponents.FDSE
     port map (
      C => s00_axi_aclk,
      CE => S_SAMPLE_COUNTER,
      D => \S_SAMPLE_COUNTER[10]_i_1_n_0\,
      Q => \^s_sample_counter_reg[16]_0\(1),
      S => '0'
    );
\S_SAMPLE_COUNTER_reg[11]\: unisim.vcomponents.FDSE
     port map (
      C => s00_axi_aclk,
      CE => S_SAMPLE_COUNTER,
      D => \S_SAMPLE_COUNTER[11]_i_1_n_0\,
      Q => \^s_sample_counter_reg[16]_0\(2),
      S => '0'
    );
\S_SAMPLE_COUNTER_reg[12]\: unisim.vcomponents.FDSE
     port map (
      C => s00_axi_aclk,
      CE => S_SAMPLE_COUNTER,
      D => \S_SAMPLE_COUNTER[12]_i_1_n_0\,
      Q => \^s_sample_counter_reg[16]_0\(3),
      S => '0'
    );
\S_SAMPLE_COUNTER_reg[13]\: unisim.vcomponents.FDSE
     port map (
      C => s00_axi_aclk,
      CE => S_SAMPLE_COUNTER,
      D => \S_SAMPLE_COUNTER[13]_i_1_n_0\,
      Q => \^s_sample_counter_reg[16]_0\(4),
      S => '0'
    );
\S_SAMPLE_COUNTER_reg[14]\: unisim.vcomponents.FDSE
     port map (
      C => s00_axi_aclk,
      CE => S_SAMPLE_COUNTER,
      D => \S_SAMPLE_COUNTER[14]_i_1_n_0\,
      Q => \^s_sample_counter_reg[16]_0\(5),
      S => '0'
    );
\S_SAMPLE_COUNTER_reg[15]\: unisim.vcomponents.FDSE
     port map (
      C => s00_axi_aclk,
      CE => S_SAMPLE_COUNTER,
      D => \S_SAMPLE_COUNTER[15]_i_1_n_0\,
      Q => \^s_sample_counter_reg[16]_0\(6),
      S => '0'
    );
\S_SAMPLE_COUNTER_reg[16]\: unisim.vcomponents.FDSE
     port map (
      C => s00_axi_aclk,
      CE => S_SAMPLE_COUNTER,
      D => \S_SAMPLE_COUNTER[16]_i_1_n_0\,
      Q => \^s_sample_counter_reg[16]_0\(7),
      S => '0'
    );
\S_SAMPLE_COUNTER_reg[16]_i_2\: unisim.vcomponents.CARRY8
     port map (
      CI => \S_SAMPLE_COUNTER_reg[8]_i_2_n_0\,
      CI_TOP => '0',
      CO(7) => \S_SAMPLE_COUNTER_reg[16]_i_2_n_0\,
      CO(6) => \S_SAMPLE_COUNTER_reg[16]_i_2_n_1\,
      CO(5) => \S_SAMPLE_COUNTER_reg[16]_i_2_n_2\,
      CO(4) => \S_SAMPLE_COUNTER_reg[16]_i_2_n_3\,
      CO(3) => \S_SAMPLE_COUNTER_reg[16]_i_2_n_4\,
      CO(2) => \S_SAMPLE_COUNTER_reg[16]_i_2_n_5\,
      CO(1) => \S_SAMPLE_COUNTER_reg[16]_i_2_n_6\,
      CO(0) => \S_SAMPLE_COUNTER_reg[16]_i_2_n_7\,
      DI(7 downto 0) => B"00000000",
      O(7 downto 0) => V_SAMPLE_COUNTER2(16 downto 9),
      S(7 downto 0) => \^s_sample_counter_reg[16]_0\(7 downto 0)
    );
\S_SAMPLE_COUNTER_reg[17]\: unisim.vcomponents.FDSE
     port map (
      C => s00_axi_aclk,
      CE => S_SAMPLE_COUNTER,
      D => \S_SAMPLE_COUNTER[17]_i_1_n_0\,
      Q => \^s_sample_counter_reg[24]_0\(0),
      S => '0'
    );
\S_SAMPLE_COUNTER_reg[18]\: unisim.vcomponents.FDSE
     port map (
      C => s00_axi_aclk,
      CE => S_SAMPLE_COUNTER,
      D => \S_SAMPLE_COUNTER[18]_i_1_n_0\,
      Q => \^s_sample_counter_reg[24]_0\(1),
      S => '0'
    );
\S_SAMPLE_COUNTER_reg[19]\: unisim.vcomponents.FDSE
     port map (
      C => s00_axi_aclk,
      CE => S_SAMPLE_COUNTER,
      D => \S_SAMPLE_COUNTER[19]_i_1_n_0\,
      Q => \^s_sample_counter_reg[24]_0\(2),
      S => '0'
    );
\S_SAMPLE_COUNTER_reg[1]\: unisim.vcomponents.FDSE
     port map (
      C => s00_axi_aclk,
      CE => S_SAMPLE_COUNTER,
      D => \S_SAMPLE_COUNTER[1]_i_1_n_0\,
      Q => \^s\(0),
      S => '0'
    );
\S_SAMPLE_COUNTER_reg[20]\: unisim.vcomponents.FDSE
     port map (
      C => s00_axi_aclk,
      CE => S_SAMPLE_COUNTER,
      D => \S_SAMPLE_COUNTER[20]_i_1_n_0\,
      Q => \^s_sample_counter_reg[24]_0\(3),
      S => '0'
    );
\S_SAMPLE_COUNTER_reg[21]\: unisim.vcomponents.FDSE
     port map (
      C => s00_axi_aclk,
      CE => S_SAMPLE_COUNTER,
      D => \S_SAMPLE_COUNTER[21]_i_1_n_0\,
      Q => \^s_sample_counter_reg[24]_0\(4),
      S => '0'
    );
\S_SAMPLE_COUNTER_reg[22]\: unisim.vcomponents.FDSE
     port map (
      C => s00_axi_aclk,
      CE => S_SAMPLE_COUNTER,
      D => \S_SAMPLE_COUNTER[22]_i_1_n_0\,
      Q => \^s_sample_counter_reg[24]_0\(5),
      S => '0'
    );
\S_SAMPLE_COUNTER_reg[23]\: unisim.vcomponents.FDSE
     port map (
      C => s00_axi_aclk,
      CE => S_SAMPLE_COUNTER,
      D => \S_SAMPLE_COUNTER[23]_i_1_n_0\,
      Q => \^s_sample_counter_reg[24]_0\(6),
      S => '0'
    );
\S_SAMPLE_COUNTER_reg[24]\: unisim.vcomponents.FDSE
     port map (
      C => s00_axi_aclk,
      CE => S_SAMPLE_COUNTER,
      D => \S_SAMPLE_COUNTER[24]_i_1_n_0\,
      Q => \^s_sample_counter_reg[24]_0\(7),
      S => '0'
    );
\S_SAMPLE_COUNTER_reg[24]_i_2\: unisim.vcomponents.CARRY8
     port map (
      CI => \S_SAMPLE_COUNTER_reg[16]_i_2_n_0\,
      CI_TOP => '0',
      CO(7) => \S_SAMPLE_COUNTER_reg[24]_i_2_n_0\,
      CO(6) => \S_SAMPLE_COUNTER_reg[24]_i_2_n_1\,
      CO(5) => \S_SAMPLE_COUNTER_reg[24]_i_2_n_2\,
      CO(4) => \S_SAMPLE_COUNTER_reg[24]_i_2_n_3\,
      CO(3) => \S_SAMPLE_COUNTER_reg[24]_i_2_n_4\,
      CO(2) => \S_SAMPLE_COUNTER_reg[24]_i_2_n_5\,
      CO(1) => \S_SAMPLE_COUNTER_reg[24]_i_2_n_6\,
      CO(0) => \S_SAMPLE_COUNTER_reg[24]_i_2_n_7\,
      DI(7 downto 0) => B"00000000",
      O(7 downto 0) => V_SAMPLE_COUNTER2(24 downto 17),
      S(7 downto 0) => \^s_sample_counter_reg[24]_0\(7 downto 0)
    );
\S_SAMPLE_COUNTER_reg[25]\: unisim.vcomponents.FDSE
     port map (
      C => s00_axi_aclk,
      CE => S_SAMPLE_COUNTER,
      D => \S_SAMPLE_COUNTER[25]_i_1_n_0\,
      Q => \^s_sample_counter_reg[31]_0\(0),
      S => '0'
    );
\S_SAMPLE_COUNTER_reg[26]\: unisim.vcomponents.FDSE
     port map (
      C => s00_axi_aclk,
      CE => S_SAMPLE_COUNTER,
      D => \S_SAMPLE_COUNTER[26]_i_1_n_0\,
      Q => \^s_sample_counter_reg[31]_0\(1),
      S => '0'
    );
\S_SAMPLE_COUNTER_reg[27]\: unisim.vcomponents.FDSE
     port map (
      C => s00_axi_aclk,
      CE => S_SAMPLE_COUNTER,
      D => \S_SAMPLE_COUNTER[27]_i_1_n_0\,
      Q => \^s_sample_counter_reg[31]_0\(2),
      S => '0'
    );
\S_SAMPLE_COUNTER_reg[28]\: unisim.vcomponents.FDSE
     port map (
      C => s00_axi_aclk,
      CE => S_SAMPLE_COUNTER,
      D => \S_SAMPLE_COUNTER[28]_i_1_n_0\,
      Q => \^s_sample_counter_reg[31]_0\(3),
      S => '0'
    );
\S_SAMPLE_COUNTER_reg[29]\: unisim.vcomponents.FDSE
     port map (
      C => s00_axi_aclk,
      CE => S_SAMPLE_COUNTER,
      D => \S_SAMPLE_COUNTER[29]_i_1_n_0\,
      Q => \^s_sample_counter_reg[31]_0\(4),
      S => '0'
    );
\S_SAMPLE_COUNTER_reg[2]\: unisim.vcomponents.FDSE
     port map (
      C => s00_axi_aclk,
      CE => S_SAMPLE_COUNTER,
      D => \S_SAMPLE_COUNTER[2]_i_1_n_0\,
      Q => \^s\(1),
      S => '0'
    );
\S_SAMPLE_COUNTER_reg[30]\: unisim.vcomponents.FDSE
     port map (
      C => s00_axi_aclk,
      CE => S_SAMPLE_COUNTER,
      D => \S_SAMPLE_COUNTER[30]_i_1_n_0\,
      Q => \^s_sample_counter_reg[31]_0\(5),
      S => '0'
    );
\S_SAMPLE_COUNTER_reg[30]_i_2\: unisim.vcomponents.CARRY8
     port map (
      CI => \S_SAMPLE_COUNTER_reg[24]_i_2_n_0\,
      CI_TOP => '0',
      CO(7 downto 6) => \NLW_S_SAMPLE_COUNTER_reg[30]_i_2_CO_UNCONNECTED\(7 downto 6),
      CO(5) => \S_SAMPLE_COUNTER_reg[30]_i_2_n_2\,
      CO(4) => \S_SAMPLE_COUNTER_reg[30]_i_2_n_3\,
      CO(3) => \S_SAMPLE_COUNTER_reg[30]_i_2_n_4\,
      CO(2) => \S_SAMPLE_COUNTER_reg[30]_i_2_n_5\,
      CO(1) => \S_SAMPLE_COUNTER_reg[30]_i_2_n_6\,
      CO(0) => \S_SAMPLE_COUNTER_reg[30]_i_2_n_7\,
      DI(7 downto 0) => B"00000000",
      O(7) => \NLW_S_SAMPLE_COUNTER_reg[30]_i_2_O_UNCONNECTED\(7),
      O(6 downto 0) => V_SAMPLE_COUNTER2(31 downto 25),
      S(7) => '0',
      S(6 downto 0) => \^s_sample_counter_reg[31]_0\(6 downto 0)
    );
\S_SAMPLE_COUNTER_reg[31]\: unisim.vcomponents.FDSE
     port map (
      C => s00_axi_aclk,
      CE => S_SAMPLE_COUNTER,
      D => '0',
      Q => \^s_sample_counter_reg[31]_0\(6),
      S => \S_SAMPLE_COUNTER[31]_i_1_n_0\
    );
\S_SAMPLE_COUNTER_reg[3]\: unisim.vcomponents.FDSE
     port map (
      C => s00_axi_aclk,
      CE => S_SAMPLE_COUNTER,
      D => \S_SAMPLE_COUNTER[3]_i_1_n_0\,
      Q => \^s\(2),
      S => '0'
    );
\S_SAMPLE_COUNTER_reg[4]\: unisim.vcomponents.FDSE
     port map (
      C => s00_axi_aclk,
      CE => S_SAMPLE_COUNTER,
      D => \S_SAMPLE_COUNTER[4]_i_1_n_0\,
      Q => \^s\(3),
      S => '0'
    );
\S_SAMPLE_COUNTER_reg[5]\: unisim.vcomponents.FDSE
     port map (
      C => s00_axi_aclk,
      CE => S_SAMPLE_COUNTER,
      D => \S_SAMPLE_COUNTER[5]_i_1_n_0\,
      Q => \^s\(4),
      S => '0'
    );
\S_SAMPLE_COUNTER_reg[6]\: unisim.vcomponents.FDSE
     port map (
      C => s00_axi_aclk,
      CE => S_SAMPLE_COUNTER,
      D => \S_SAMPLE_COUNTER[6]_i_1_n_0\,
      Q => \^s\(5),
      S => '0'
    );
\S_SAMPLE_COUNTER_reg[7]\: unisim.vcomponents.FDSE
     port map (
      C => s00_axi_aclk,
      CE => S_SAMPLE_COUNTER,
      D => \S_SAMPLE_COUNTER[7]_i_1_n_0\,
      Q => \^s\(6),
      S => '0'
    );
\S_SAMPLE_COUNTER_reg[8]\: unisim.vcomponents.FDSE
     port map (
      C => s00_axi_aclk,
      CE => S_SAMPLE_COUNTER,
      D => \S_SAMPLE_COUNTER[8]_i_1_n_0\,
      Q => \^s\(7),
      S => '0'
    );
\S_SAMPLE_COUNTER_reg[8]_i_2\: unisim.vcomponents.CARRY8
     port map (
      CI => \^s_sample_counter_reg[0]_0\,
      CI_TOP => '0',
      CO(7) => \S_SAMPLE_COUNTER_reg[8]_i_2_n_0\,
      CO(6) => \S_SAMPLE_COUNTER_reg[8]_i_2_n_1\,
      CO(5) => \S_SAMPLE_COUNTER_reg[8]_i_2_n_2\,
      CO(4) => \S_SAMPLE_COUNTER_reg[8]_i_2_n_3\,
      CO(3) => \S_SAMPLE_COUNTER_reg[8]_i_2_n_4\,
      CO(2) => \S_SAMPLE_COUNTER_reg[8]_i_2_n_5\,
      CO(1) => \S_SAMPLE_COUNTER_reg[8]_i_2_n_6\,
      CO(0) => \S_SAMPLE_COUNTER_reg[8]_i_2_n_7\,
      DI(7 downto 0) => B"00000000",
      O(7 downto 0) => V_SAMPLE_COUNTER2(8 downto 1),
      S(7 downto 0) => \^s\(7 downto 0)
    );
\S_SAMPLE_COUNTER_reg[9]\: unisim.vcomponents.FDSE
     port map (
      C => s00_axi_aclk,
      CE => S_SAMPLE_COUNTER,
      D => \S_SAMPLE_COUNTER[9]_i_1_n_0\,
      Q => \^s_sample_counter_reg[16]_0\(0),
      S => '0'
    );
\S_SAMPLE_TIME_COUNTER[0]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"1F001000FFE0FFEF"
    )
        port map (
      I0 => \^q\(1),
      I1 => \^q\(0),
      I2 => \^s_enable_reg[0]\,
      I3 => \S_SAMPLE_TIME_reg_n_0_[0]\,
      I4 => \^s_enable_reg[0]_0\,
      I5 => S_SAMPLE_TIME_COUNTER(0),
      O => p_2_in(0)
    );
\S_SAMPLE_TIME_COUNTER[10]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFE0FFEF1F001000"
    )
        port map (
      I0 => \^q\(1),
      I1 => \^q\(0),
      I2 => \^s_enable_reg[0]\,
      I3 => \S_SAMPLE_TIME_reg_n_0_[10]\,
      I4 => \^s_enable_reg[0]_0\,
      I5 => \S_SAMPLE_TIME_COUNTER0__0\(10),
      O => p_2_in(10)
    );
\S_SAMPLE_TIME_COUNTER[11]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFE0FFEF1F001000"
    )
        port map (
      I0 => \^q\(1),
      I1 => \^q\(0),
      I2 => \^s_enable_reg[0]\,
      I3 => \S_SAMPLE_TIME_reg_n_0_[11]\,
      I4 => \^s_enable_reg[0]_0\,
      I5 => \S_SAMPLE_TIME_COUNTER0__0\(11),
      O => p_2_in(11)
    );
\S_SAMPLE_TIME_COUNTER[12]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFE0FFEF1F001000"
    )
        port map (
      I0 => \^q\(1),
      I1 => \^q\(0),
      I2 => \^s_enable_reg[0]\,
      I3 => \S_SAMPLE_TIME_reg_n_0_[12]\,
      I4 => \^s_enable_reg[0]_0\,
      I5 => \S_SAMPLE_TIME_COUNTER0__0\(12),
      O => p_2_in(12)
    );
\S_SAMPLE_TIME_COUNTER[13]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFE0FFEF1F001000"
    )
        port map (
      I0 => \^q\(1),
      I1 => \^q\(0),
      I2 => \^s_enable_reg[0]\,
      I3 => \S_SAMPLE_TIME_reg_n_0_[13]\,
      I4 => \^s_enable_reg[0]_0\,
      I5 => \S_SAMPLE_TIME_COUNTER0__0\(13),
      O => p_2_in(13)
    );
\S_SAMPLE_TIME_COUNTER[14]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFE0FFEF1F001000"
    )
        port map (
      I0 => \^q\(1),
      I1 => \^q\(0),
      I2 => \^s_enable_reg[0]\,
      I3 => \S_SAMPLE_TIME_reg_n_0_[14]\,
      I4 => \^s_enable_reg[0]_0\,
      I5 => \S_SAMPLE_TIME_COUNTER0__0\(14),
      O => p_2_in(14)
    );
\S_SAMPLE_TIME_COUNTER[15]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFE0FFEF1F001000"
    )
        port map (
      I0 => \^q\(1),
      I1 => \^q\(0),
      I2 => \^s_enable_reg[0]\,
      I3 => \S_SAMPLE_TIME_reg_n_0_[15]\,
      I4 => \^s_enable_reg[0]_0\,
      I5 => \S_SAMPLE_TIME_COUNTER0__0\(15),
      O => p_2_in(15)
    );
\S_SAMPLE_TIME_COUNTER[16]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFE0FFEF1F001000"
    )
        port map (
      I0 => \^q\(1),
      I1 => \^q\(0),
      I2 => \^s_enable_reg[0]\,
      I3 => \S_SAMPLE_TIME_reg_n_0_[16]\,
      I4 => \^s_enable_reg[0]_0\,
      I5 => \S_SAMPLE_TIME_COUNTER0__0\(16),
      O => p_2_in(16)
    );
\S_SAMPLE_TIME_COUNTER[16]_i_10\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => S_SAMPLE_TIME_COUNTER(9),
      O => \S_SAMPLE_TIME_COUNTER[16]_i_10_n_0\
    );
\S_SAMPLE_TIME_COUNTER[16]_i_3\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => S_SAMPLE_TIME_COUNTER(16),
      O => \S_SAMPLE_TIME_COUNTER[16]_i_3_n_0\
    );
\S_SAMPLE_TIME_COUNTER[16]_i_4\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => S_SAMPLE_TIME_COUNTER(15),
      O => \S_SAMPLE_TIME_COUNTER[16]_i_4_n_0\
    );
\S_SAMPLE_TIME_COUNTER[16]_i_5\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => S_SAMPLE_TIME_COUNTER(14),
      O => \S_SAMPLE_TIME_COUNTER[16]_i_5_n_0\
    );
\S_SAMPLE_TIME_COUNTER[16]_i_6\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => S_SAMPLE_TIME_COUNTER(13),
      O => \S_SAMPLE_TIME_COUNTER[16]_i_6_n_0\
    );
\S_SAMPLE_TIME_COUNTER[16]_i_7\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => S_SAMPLE_TIME_COUNTER(12),
      O => \S_SAMPLE_TIME_COUNTER[16]_i_7_n_0\
    );
\S_SAMPLE_TIME_COUNTER[16]_i_8\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => S_SAMPLE_TIME_COUNTER(11),
      O => \S_SAMPLE_TIME_COUNTER[16]_i_8_n_0\
    );
\S_SAMPLE_TIME_COUNTER[16]_i_9\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => S_SAMPLE_TIME_COUNTER(10),
      O => \S_SAMPLE_TIME_COUNTER[16]_i_9_n_0\
    );
\S_SAMPLE_TIME_COUNTER[17]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFE0FFEF1F001000"
    )
        port map (
      I0 => \^q\(1),
      I1 => \^q\(0),
      I2 => \^s_enable_reg[0]\,
      I3 => \S_SAMPLE_TIME_reg_n_0_[17]\,
      I4 => \^s_enable_reg[0]_0\,
      I5 => \S_SAMPLE_TIME_COUNTER0__0\(17),
      O => p_2_in(17)
    );
\S_SAMPLE_TIME_COUNTER[18]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFE0FFEF1F001000"
    )
        port map (
      I0 => \^q\(1),
      I1 => \^q\(0),
      I2 => \^s_enable_reg[0]\,
      I3 => \S_SAMPLE_TIME_reg_n_0_[18]\,
      I4 => \^s_enable_reg[0]_0\,
      I5 => \S_SAMPLE_TIME_COUNTER0__0\(18),
      O => p_2_in(18)
    );
\S_SAMPLE_TIME_COUNTER[19]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFE0FFEF1F001000"
    )
        port map (
      I0 => \^q\(1),
      I1 => \^q\(0),
      I2 => \^s_enable_reg[0]\,
      I3 => \S_SAMPLE_TIME_reg_n_0_[19]\,
      I4 => \^s_enable_reg[0]_0\,
      I5 => \S_SAMPLE_TIME_COUNTER0__0\(19),
      O => p_2_in(19)
    );
\S_SAMPLE_TIME_COUNTER[1]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFE0FFEF1F001000"
    )
        port map (
      I0 => \^q\(1),
      I1 => \^q\(0),
      I2 => \^s_enable_reg[0]\,
      I3 => \S_SAMPLE_TIME_reg_n_0_[1]\,
      I4 => \^s_enable_reg[0]_0\,
      I5 => \S_SAMPLE_TIME_COUNTER0__0\(1),
      O => p_2_in(1)
    );
\S_SAMPLE_TIME_COUNTER[20]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFE0FFEF1F001000"
    )
        port map (
      I0 => \^q\(1),
      I1 => \^q\(0),
      I2 => \^s_enable_reg[0]\,
      I3 => \S_SAMPLE_TIME_reg_n_0_[20]\,
      I4 => \^s_enable_reg[0]_0\,
      I5 => \S_SAMPLE_TIME_COUNTER0__0\(20),
      O => p_2_in(20)
    );
\S_SAMPLE_TIME_COUNTER[21]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFE0FFEF1F001000"
    )
        port map (
      I0 => \^q\(1),
      I1 => \^q\(0),
      I2 => \^s_enable_reg[0]\,
      I3 => \S_SAMPLE_TIME_reg_n_0_[21]\,
      I4 => \^s_enable_reg[0]_0\,
      I5 => \S_SAMPLE_TIME_COUNTER0__0\(21),
      O => p_2_in(21)
    );
\S_SAMPLE_TIME_COUNTER[22]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFE0FFEF1F001000"
    )
        port map (
      I0 => \^q\(1),
      I1 => \^q\(0),
      I2 => \^s_enable_reg[0]\,
      I3 => \S_SAMPLE_TIME_reg_n_0_[22]\,
      I4 => \^s_enable_reg[0]_0\,
      I5 => \S_SAMPLE_TIME_COUNTER0__0\(22),
      O => p_2_in(22)
    );
\S_SAMPLE_TIME_COUNTER[23]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFE0FFEF1F001000"
    )
        port map (
      I0 => \^q\(1),
      I1 => \^q\(0),
      I2 => \^s_enable_reg[0]\,
      I3 => \S_SAMPLE_TIME_reg_n_0_[23]\,
      I4 => \^s_enable_reg[0]_0\,
      I5 => \S_SAMPLE_TIME_COUNTER0__0\(23),
      O => p_2_in(23)
    );
\S_SAMPLE_TIME_COUNTER[24]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFE0FFEF1F001000"
    )
        port map (
      I0 => \^q\(1),
      I1 => \^q\(0),
      I2 => \^s_enable_reg[0]\,
      I3 => \S_SAMPLE_TIME_reg_n_0_[24]\,
      I4 => \^s_enable_reg[0]_0\,
      I5 => \S_SAMPLE_TIME_COUNTER0__0\(24),
      O => p_2_in(24)
    );
\S_SAMPLE_TIME_COUNTER[24]_i_10\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => S_SAMPLE_TIME_COUNTER(17),
      O => \S_SAMPLE_TIME_COUNTER[24]_i_10_n_0\
    );
\S_SAMPLE_TIME_COUNTER[24]_i_3\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => S_SAMPLE_TIME_COUNTER(24),
      O => \S_SAMPLE_TIME_COUNTER[24]_i_3_n_0\
    );
\S_SAMPLE_TIME_COUNTER[24]_i_4\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => S_SAMPLE_TIME_COUNTER(23),
      O => \S_SAMPLE_TIME_COUNTER[24]_i_4_n_0\
    );
\S_SAMPLE_TIME_COUNTER[24]_i_5\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => S_SAMPLE_TIME_COUNTER(22),
      O => \S_SAMPLE_TIME_COUNTER[24]_i_5_n_0\
    );
\S_SAMPLE_TIME_COUNTER[24]_i_6\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => S_SAMPLE_TIME_COUNTER(21),
      O => \S_SAMPLE_TIME_COUNTER[24]_i_6_n_0\
    );
\S_SAMPLE_TIME_COUNTER[24]_i_7\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => S_SAMPLE_TIME_COUNTER(20),
      O => \S_SAMPLE_TIME_COUNTER[24]_i_7_n_0\
    );
\S_SAMPLE_TIME_COUNTER[24]_i_8\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => S_SAMPLE_TIME_COUNTER(19),
      O => \S_SAMPLE_TIME_COUNTER[24]_i_8_n_0\
    );
\S_SAMPLE_TIME_COUNTER[24]_i_9\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => S_SAMPLE_TIME_COUNTER(18),
      O => \S_SAMPLE_TIME_COUNTER[24]_i_9_n_0\
    );
\S_SAMPLE_TIME_COUNTER[25]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFE0FFEF1F001000"
    )
        port map (
      I0 => \^q\(1),
      I1 => \^q\(0),
      I2 => \^s_enable_reg[0]\,
      I3 => \S_SAMPLE_TIME_reg_n_0_[25]\,
      I4 => \^s_enable_reg[0]_0\,
      I5 => \S_SAMPLE_TIME_COUNTER0__0\(25),
      O => p_2_in(25)
    );
\S_SAMPLE_TIME_COUNTER[26]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFE0FFEF1F001000"
    )
        port map (
      I0 => \^q\(1),
      I1 => \^q\(0),
      I2 => \^s_enable_reg[0]\,
      I3 => \S_SAMPLE_TIME_reg_n_0_[26]\,
      I4 => \^s_enable_reg[0]_0\,
      I5 => \S_SAMPLE_TIME_COUNTER0__0\(26),
      O => p_2_in(26)
    );
\S_SAMPLE_TIME_COUNTER[27]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFE0FFEF1F001000"
    )
        port map (
      I0 => \^q\(1),
      I1 => \^q\(0),
      I2 => \^s_enable_reg[0]\,
      I3 => \S_SAMPLE_TIME_reg_n_0_[27]\,
      I4 => \^s_enable_reg[0]_0\,
      I5 => \S_SAMPLE_TIME_COUNTER0__0\(27),
      O => p_2_in(27)
    );
\S_SAMPLE_TIME_COUNTER[28]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFE0FFEF1F001000"
    )
        port map (
      I0 => \^q\(1),
      I1 => \^q\(0),
      I2 => \^s_enable_reg[0]\,
      I3 => \S_SAMPLE_TIME_reg_n_0_[28]\,
      I4 => \^s_enable_reg[0]_0\,
      I5 => \S_SAMPLE_TIME_COUNTER0__0\(28),
      O => p_2_in(28)
    );
\S_SAMPLE_TIME_COUNTER[29]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFE0FFEF1F001000"
    )
        port map (
      I0 => \^q\(1),
      I1 => \^q\(0),
      I2 => \^s_enable_reg[0]\,
      I3 => \S_SAMPLE_TIME_reg_n_0_[29]\,
      I4 => \^s_enable_reg[0]_0\,
      I5 => \S_SAMPLE_TIME_COUNTER0__0\(29),
      O => p_2_in(29)
    );
\S_SAMPLE_TIME_COUNTER[2]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFE0FFEF1F001000"
    )
        port map (
      I0 => \^q\(1),
      I1 => \^q\(0),
      I2 => \^s_enable_reg[0]\,
      I3 => \S_SAMPLE_TIME_reg_n_0_[2]\,
      I4 => \^s_enable_reg[0]_0\,
      I5 => \S_SAMPLE_TIME_COUNTER0__0\(2),
      O => p_2_in(2)
    );
\S_SAMPLE_TIME_COUNTER[30]_i_10\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => S_SAMPLE_TIME_COUNTER(28),
      O => \S_SAMPLE_TIME_COUNTER[30]_i_10_n_0\
    );
\S_SAMPLE_TIME_COUNTER[30]_i_11\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => S_SAMPLE_TIME_COUNTER(27),
      O => \S_SAMPLE_TIME_COUNTER[30]_i_11_n_0\
    );
\S_SAMPLE_TIME_COUNTER[30]_i_12\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => S_SAMPLE_TIME_COUNTER(26),
      O => \S_SAMPLE_TIME_COUNTER[30]_i_12_n_0\
    );
\S_SAMPLE_TIME_COUNTER[30]_i_13\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => S_SAMPLE_TIME_COUNTER(25),
      O => \S_SAMPLE_TIME_COUNTER[30]_i_13_n_0\
    );
\S_SAMPLE_TIME_COUNTER[30]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFE0FFEF1F001000"
    )
        port map (
      I0 => \^q\(1),
      I1 => \^q\(0),
      I2 => \^s_enable_reg[0]\,
      I3 => \S_SAMPLE_TIME_reg_n_0_[30]\,
      I4 => \^s_enable_reg[0]_0\,
      I5 => \S_SAMPLE_TIME_COUNTER0__0\(30),
      O => p_2_in(30)
    );
\S_SAMPLE_TIME_COUNTER[30]_i_3\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"2"
    )
        port map (
      I0 => nxtstate22_in,
      I1 => ENABLE,
      O => \S_SAMPLE_TIME_COUNTER[30]_i_3_n_0\
    );
\S_SAMPLE_TIME_COUNTER[30]_i_4\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"FE"
    )
        port map (
      I0 => raw_to_si_n_133,
      I1 => \S_SAMPLE_TIME_COUNTER[30]_i_6_n_0\,
      I2 => \S_SAMPLE_TIME_COUNTER[30]_i_7_n_0\,
      O => \S_SAMPLE_TIME_COUNTER[30]_i_4_n_0\
    );
\S_SAMPLE_TIME_COUNTER[30]_i_6\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFFFFFFE"
    )
        port map (
      I0 => S_SAMPLE_TIME_COUNTER(27),
      I1 => S_SAMPLE_TIME_COUNTER(19),
      I2 => S_SAMPLE_TIME_COUNTER(26),
      I3 => S_SAMPLE_TIME_COUNTER(6),
      I4 => raw_to_si_n_136,
      O => \S_SAMPLE_TIME_COUNTER[30]_i_6_n_0\
    );
\S_SAMPLE_TIME_COUNTER[30]_i_7\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFFFFFFE"
    )
        port map (
      I0 => S_SAMPLE_TIME_COUNTER(22),
      I1 => S_SAMPLE_TIME_COUNTER(18),
      I2 => S_SAMPLE_TIME_COUNTER(24),
      I3 => S_SAMPLE_TIME_COUNTER(10),
      I4 => raw_to_si_n_135,
      O => \S_SAMPLE_TIME_COUNTER[30]_i_7_n_0\
    );
\S_SAMPLE_TIME_COUNTER[30]_i_8\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => S_SAMPLE_TIME_COUNTER(30),
      O => \S_SAMPLE_TIME_COUNTER[30]_i_8_n_0\
    );
\S_SAMPLE_TIME_COUNTER[30]_i_9\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => S_SAMPLE_TIME_COUNTER(29),
      O => \S_SAMPLE_TIME_COUNTER[30]_i_9_n_0\
    );
\S_SAMPLE_TIME_COUNTER[3]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFE0FFEF1F001000"
    )
        port map (
      I0 => \^q\(1),
      I1 => \^q\(0),
      I2 => \^s_enable_reg[0]\,
      I3 => \S_SAMPLE_TIME_reg_n_0_[3]\,
      I4 => \^s_enable_reg[0]_0\,
      I5 => \S_SAMPLE_TIME_COUNTER0__0\(3),
      O => p_2_in(3)
    );
\S_SAMPLE_TIME_COUNTER[4]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFE0FFEF1F001000"
    )
        port map (
      I0 => \^q\(1),
      I1 => \^q\(0),
      I2 => \^s_enable_reg[0]\,
      I3 => \S_SAMPLE_TIME_reg_n_0_[4]\,
      I4 => \^s_enable_reg[0]_0\,
      I5 => \S_SAMPLE_TIME_COUNTER0__0\(4),
      O => p_2_in(4)
    );
\S_SAMPLE_TIME_COUNTER[5]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFE0FFEF1F001000"
    )
        port map (
      I0 => \^q\(1),
      I1 => \^q\(0),
      I2 => \^s_enable_reg[0]\,
      I3 => \S_SAMPLE_TIME_reg_n_0_[5]\,
      I4 => \^s_enable_reg[0]_0\,
      I5 => \S_SAMPLE_TIME_COUNTER0__0\(5),
      O => p_2_in(5)
    );
\S_SAMPLE_TIME_COUNTER[6]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFE0FFEF1F001000"
    )
        port map (
      I0 => \^q\(1),
      I1 => \^q\(0),
      I2 => \^s_enable_reg[0]\,
      I3 => \S_SAMPLE_TIME_reg_n_0_[6]\,
      I4 => \^s_enable_reg[0]_0\,
      I5 => \S_SAMPLE_TIME_COUNTER0__0\(6),
      O => p_2_in(6)
    );
\S_SAMPLE_TIME_COUNTER[7]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFE0FFEF1F001000"
    )
        port map (
      I0 => \^q\(1),
      I1 => \^q\(0),
      I2 => \^s_enable_reg[0]\,
      I3 => \S_SAMPLE_TIME_reg_n_0_[7]\,
      I4 => \^s_enable_reg[0]_0\,
      I5 => \S_SAMPLE_TIME_COUNTER0__0\(7),
      O => p_2_in(7)
    );
\S_SAMPLE_TIME_COUNTER[8]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFE0FFEF1F001000"
    )
        port map (
      I0 => \^q\(1),
      I1 => \^q\(0),
      I2 => \^s_enable_reg[0]\,
      I3 => \S_SAMPLE_TIME_reg_n_0_[8]\,
      I4 => \^s_enable_reg[0]_0\,
      I5 => \S_SAMPLE_TIME_COUNTER0__0\(8),
      O => p_2_in(8)
    );
\S_SAMPLE_TIME_COUNTER[8]_i_10\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => S_SAMPLE_TIME_COUNTER(1),
      O => \S_SAMPLE_TIME_COUNTER[8]_i_10_n_0\
    );
\S_SAMPLE_TIME_COUNTER[8]_i_3\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => S_SAMPLE_TIME_COUNTER(8),
      O => \S_SAMPLE_TIME_COUNTER[8]_i_3_n_0\
    );
\S_SAMPLE_TIME_COUNTER[8]_i_4\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => S_SAMPLE_TIME_COUNTER(7),
      O => \S_SAMPLE_TIME_COUNTER[8]_i_4_n_0\
    );
\S_SAMPLE_TIME_COUNTER[8]_i_5\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => S_SAMPLE_TIME_COUNTER(6),
      O => \S_SAMPLE_TIME_COUNTER[8]_i_5_n_0\
    );
\S_SAMPLE_TIME_COUNTER[8]_i_6\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => S_SAMPLE_TIME_COUNTER(5),
      O => \S_SAMPLE_TIME_COUNTER[8]_i_6_n_0\
    );
\S_SAMPLE_TIME_COUNTER[8]_i_7\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => S_SAMPLE_TIME_COUNTER(4),
      O => \S_SAMPLE_TIME_COUNTER[8]_i_7_n_0\
    );
\S_SAMPLE_TIME_COUNTER[8]_i_8\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => S_SAMPLE_TIME_COUNTER(3),
      O => \S_SAMPLE_TIME_COUNTER[8]_i_8_n_0\
    );
\S_SAMPLE_TIME_COUNTER[8]_i_9\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => S_SAMPLE_TIME_COUNTER(2),
      O => \S_SAMPLE_TIME_COUNTER[8]_i_9_n_0\
    );
\S_SAMPLE_TIME_COUNTER[9]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFE0FFEF1F001000"
    )
        port map (
      I0 => \^q\(1),
      I1 => \^q\(0),
      I2 => \^s_enable_reg[0]\,
      I3 => \S_SAMPLE_TIME_reg_n_0_[9]\,
      I4 => \^s_enable_reg[0]_0\,
      I5 => \S_SAMPLE_TIME_COUNTER0__0\(9),
      O => p_2_in(9)
    );
\S_SAMPLE_TIME_COUNTER_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => spi_n_3,
      D => p_2_in(0),
      Q => S_SAMPLE_TIME_COUNTER(0),
      R => RSTP
    );
\S_SAMPLE_TIME_COUNTER_reg[10]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => spi_n_3,
      D => p_2_in(10),
      Q => S_SAMPLE_TIME_COUNTER(10),
      R => RSTP
    );
\S_SAMPLE_TIME_COUNTER_reg[11]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => spi_n_3,
      D => p_2_in(11),
      Q => S_SAMPLE_TIME_COUNTER(11),
      R => RSTP
    );
\S_SAMPLE_TIME_COUNTER_reg[12]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => spi_n_3,
      D => p_2_in(12),
      Q => S_SAMPLE_TIME_COUNTER(12),
      R => RSTP
    );
\S_SAMPLE_TIME_COUNTER_reg[13]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => spi_n_3,
      D => p_2_in(13),
      Q => S_SAMPLE_TIME_COUNTER(13),
      R => RSTP
    );
\S_SAMPLE_TIME_COUNTER_reg[14]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => spi_n_3,
      D => p_2_in(14),
      Q => S_SAMPLE_TIME_COUNTER(14),
      R => RSTP
    );
\S_SAMPLE_TIME_COUNTER_reg[15]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => spi_n_3,
      D => p_2_in(15),
      Q => S_SAMPLE_TIME_COUNTER(15),
      R => RSTP
    );
\S_SAMPLE_TIME_COUNTER_reg[16]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => spi_n_3,
      D => p_2_in(16),
      Q => S_SAMPLE_TIME_COUNTER(16),
      R => RSTP
    );
\S_SAMPLE_TIME_COUNTER_reg[16]_i_2\: unisim.vcomponents.CARRY8
     port map (
      CI => \S_SAMPLE_TIME_COUNTER_reg[8]_i_2_n_0\,
      CI_TOP => '0',
      CO(7) => \S_SAMPLE_TIME_COUNTER_reg[16]_i_2_n_0\,
      CO(6) => \S_SAMPLE_TIME_COUNTER_reg[16]_i_2_n_1\,
      CO(5) => \S_SAMPLE_TIME_COUNTER_reg[16]_i_2_n_2\,
      CO(4) => \S_SAMPLE_TIME_COUNTER_reg[16]_i_2_n_3\,
      CO(3) => \S_SAMPLE_TIME_COUNTER_reg[16]_i_2_n_4\,
      CO(2) => \S_SAMPLE_TIME_COUNTER_reg[16]_i_2_n_5\,
      CO(1) => \S_SAMPLE_TIME_COUNTER_reg[16]_i_2_n_6\,
      CO(0) => \S_SAMPLE_TIME_COUNTER_reg[16]_i_2_n_7\,
      DI(7 downto 0) => S_SAMPLE_TIME_COUNTER(16 downto 9),
      O(7 downto 0) => \S_SAMPLE_TIME_COUNTER0__0\(16 downto 9),
      S(7) => \S_SAMPLE_TIME_COUNTER[16]_i_3_n_0\,
      S(6) => \S_SAMPLE_TIME_COUNTER[16]_i_4_n_0\,
      S(5) => \S_SAMPLE_TIME_COUNTER[16]_i_5_n_0\,
      S(4) => \S_SAMPLE_TIME_COUNTER[16]_i_6_n_0\,
      S(3) => \S_SAMPLE_TIME_COUNTER[16]_i_7_n_0\,
      S(2) => \S_SAMPLE_TIME_COUNTER[16]_i_8_n_0\,
      S(1) => \S_SAMPLE_TIME_COUNTER[16]_i_9_n_0\,
      S(0) => \S_SAMPLE_TIME_COUNTER[16]_i_10_n_0\
    );
\S_SAMPLE_TIME_COUNTER_reg[17]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => spi_n_3,
      D => p_2_in(17),
      Q => S_SAMPLE_TIME_COUNTER(17),
      R => RSTP
    );
\S_SAMPLE_TIME_COUNTER_reg[18]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => spi_n_3,
      D => p_2_in(18),
      Q => S_SAMPLE_TIME_COUNTER(18),
      R => RSTP
    );
\S_SAMPLE_TIME_COUNTER_reg[19]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => spi_n_3,
      D => p_2_in(19),
      Q => S_SAMPLE_TIME_COUNTER(19),
      R => RSTP
    );
\S_SAMPLE_TIME_COUNTER_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => spi_n_3,
      D => p_2_in(1),
      Q => S_SAMPLE_TIME_COUNTER(1),
      R => RSTP
    );
\S_SAMPLE_TIME_COUNTER_reg[20]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => spi_n_3,
      D => p_2_in(20),
      Q => S_SAMPLE_TIME_COUNTER(20),
      R => RSTP
    );
\S_SAMPLE_TIME_COUNTER_reg[21]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => spi_n_3,
      D => p_2_in(21),
      Q => S_SAMPLE_TIME_COUNTER(21),
      R => RSTP
    );
\S_SAMPLE_TIME_COUNTER_reg[22]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => spi_n_3,
      D => p_2_in(22),
      Q => S_SAMPLE_TIME_COUNTER(22),
      R => RSTP
    );
\S_SAMPLE_TIME_COUNTER_reg[23]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => spi_n_3,
      D => p_2_in(23),
      Q => S_SAMPLE_TIME_COUNTER(23),
      R => RSTP
    );
\S_SAMPLE_TIME_COUNTER_reg[24]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => spi_n_3,
      D => p_2_in(24),
      Q => S_SAMPLE_TIME_COUNTER(24),
      R => RSTP
    );
\S_SAMPLE_TIME_COUNTER_reg[24]_i_2\: unisim.vcomponents.CARRY8
     port map (
      CI => \S_SAMPLE_TIME_COUNTER_reg[16]_i_2_n_0\,
      CI_TOP => '0',
      CO(7) => \S_SAMPLE_TIME_COUNTER_reg[24]_i_2_n_0\,
      CO(6) => \S_SAMPLE_TIME_COUNTER_reg[24]_i_2_n_1\,
      CO(5) => \S_SAMPLE_TIME_COUNTER_reg[24]_i_2_n_2\,
      CO(4) => \S_SAMPLE_TIME_COUNTER_reg[24]_i_2_n_3\,
      CO(3) => \S_SAMPLE_TIME_COUNTER_reg[24]_i_2_n_4\,
      CO(2) => \S_SAMPLE_TIME_COUNTER_reg[24]_i_2_n_5\,
      CO(1) => \S_SAMPLE_TIME_COUNTER_reg[24]_i_2_n_6\,
      CO(0) => \S_SAMPLE_TIME_COUNTER_reg[24]_i_2_n_7\,
      DI(7 downto 0) => S_SAMPLE_TIME_COUNTER(24 downto 17),
      O(7 downto 0) => \S_SAMPLE_TIME_COUNTER0__0\(24 downto 17),
      S(7) => \S_SAMPLE_TIME_COUNTER[24]_i_3_n_0\,
      S(6) => \S_SAMPLE_TIME_COUNTER[24]_i_4_n_0\,
      S(5) => \S_SAMPLE_TIME_COUNTER[24]_i_5_n_0\,
      S(4) => \S_SAMPLE_TIME_COUNTER[24]_i_6_n_0\,
      S(3) => \S_SAMPLE_TIME_COUNTER[24]_i_7_n_0\,
      S(2) => \S_SAMPLE_TIME_COUNTER[24]_i_8_n_0\,
      S(1) => \S_SAMPLE_TIME_COUNTER[24]_i_9_n_0\,
      S(0) => \S_SAMPLE_TIME_COUNTER[24]_i_10_n_0\
    );
\S_SAMPLE_TIME_COUNTER_reg[25]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => spi_n_3,
      D => p_2_in(25),
      Q => S_SAMPLE_TIME_COUNTER(25),
      R => RSTP
    );
\S_SAMPLE_TIME_COUNTER_reg[26]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => spi_n_3,
      D => p_2_in(26),
      Q => S_SAMPLE_TIME_COUNTER(26),
      R => RSTP
    );
\S_SAMPLE_TIME_COUNTER_reg[27]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => spi_n_3,
      D => p_2_in(27),
      Q => S_SAMPLE_TIME_COUNTER(27),
      R => RSTP
    );
\S_SAMPLE_TIME_COUNTER_reg[28]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => spi_n_3,
      D => p_2_in(28),
      Q => S_SAMPLE_TIME_COUNTER(28),
      R => RSTP
    );
\S_SAMPLE_TIME_COUNTER_reg[29]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => spi_n_3,
      D => p_2_in(29),
      Q => S_SAMPLE_TIME_COUNTER(29),
      R => RSTP
    );
\S_SAMPLE_TIME_COUNTER_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => spi_n_3,
      D => p_2_in(2),
      Q => S_SAMPLE_TIME_COUNTER(2),
      R => RSTP
    );
\S_SAMPLE_TIME_COUNTER_reg[30]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => spi_n_3,
      D => p_2_in(30),
      Q => S_SAMPLE_TIME_COUNTER(30),
      R => RSTP
    );
\S_SAMPLE_TIME_COUNTER_reg[30]_i_5\: unisim.vcomponents.CARRY8
     port map (
      CI => \S_SAMPLE_TIME_COUNTER_reg[24]_i_2_n_0\,
      CI_TOP => '0',
      CO(7 downto 5) => \NLW_S_SAMPLE_TIME_COUNTER_reg[30]_i_5_CO_UNCONNECTED\(7 downto 5),
      CO(4) => \S_SAMPLE_TIME_COUNTER_reg[30]_i_5_n_3\,
      CO(3) => \S_SAMPLE_TIME_COUNTER_reg[30]_i_5_n_4\,
      CO(2) => \S_SAMPLE_TIME_COUNTER_reg[30]_i_5_n_5\,
      CO(1) => \S_SAMPLE_TIME_COUNTER_reg[30]_i_5_n_6\,
      CO(0) => \S_SAMPLE_TIME_COUNTER_reg[30]_i_5_n_7\,
      DI(7 downto 5) => B"000",
      DI(4 downto 0) => S_SAMPLE_TIME_COUNTER(29 downto 25),
      O(7 downto 6) => \NLW_S_SAMPLE_TIME_COUNTER_reg[30]_i_5_O_UNCONNECTED\(7 downto 6),
      O(5 downto 0) => \S_SAMPLE_TIME_COUNTER0__0\(30 downto 25),
      S(7 downto 6) => B"00",
      S(5) => \S_SAMPLE_TIME_COUNTER[30]_i_8_n_0\,
      S(4) => \S_SAMPLE_TIME_COUNTER[30]_i_9_n_0\,
      S(3) => \S_SAMPLE_TIME_COUNTER[30]_i_10_n_0\,
      S(2) => \S_SAMPLE_TIME_COUNTER[30]_i_11_n_0\,
      S(1) => \S_SAMPLE_TIME_COUNTER[30]_i_12_n_0\,
      S(0) => \S_SAMPLE_TIME_COUNTER[30]_i_13_n_0\
    );
\S_SAMPLE_TIME_COUNTER_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => spi_n_3,
      D => p_2_in(3),
      Q => S_SAMPLE_TIME_COUNTER(3),
      R => RSTP
    );
\S_SAMPLE_TIME_COUNTER_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => spi_n_3,
      D => p_2_in(4),
      Q => S_SAMPLE_TIME_COUNTER(4),
      R => RSTP
    );
\S_SAMPLE_TIME_COUNTER_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => spi_n_3,
      D => p_2_in(5),
      Q => S_SAMPLE_TIME_COUNTER(5),
      R => RSTP
    );
\S_SAMPLE_TIME_COUNTER_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => spi_n_3,
      D => p_2_in(6),
      Q => S_SAMPLE_TIME_COUNTER(6),
      R => RSTP
    );
\S_SAMPLE_TIME_COUNTER_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => spi_n_3,
      D => p_2_in(7),
      Q => S_SAMPLE_TIME_COUNTER(7),
      R => RSTP
    );
\S_SAMPLE_TIME_COUNTER_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => spi_n_3,
      D => p_2_in(8),
      Q => S_SAMPLE_TIME_COUNTER(8),
      R => RSTP
    );
\S_SAMPLE_TIME_COUNTER_reg[8]_i_2\: unisim.vcomponents.CARRY8
     port map (
      CI => S_SAMPLE_TIME_COUNTER(0),
      CI_TOP => '0',
      CO(7) => \S_SAMPLE_TIME_COUNTER_reg[8]_i_2_n_0\,
      CO(6) => \S_SAMPLE_TIME_COUNTER_reg[8]_i_2_n_1\,
      CO(5) => \S_SAMPLE_TIME_COUNTER_reg[8]_i_2_n_2\,
      CO(4) => \S_SAMPLE_TIME_COUNTER_reg[8]_i_2_n_3\,
      CO(3) => \S_SAMPLE_TIME_COUNTER_reg[8]_i_2_n_4\,
      CO(2) => \S_SAMPLE_TIME_COUNTER_reg[8]_i_2_n_5\,
      CO(1) => \S_SAMPLE_TIME_COUNTER_reg[8]_i_2_n_6\,
      CO(0) => \S_SAMPLE_TIME_COUNTER_reg[8]_i_2_n_7\,
      DI(7 downto 0) => S_SAMPLE_TIME_COUNTER(8 downto 1),
      O(7 downto 0) => \S_SAMPLE_TIME_COUNTER0__0\(8 downto 1),
      S(7) => \S_SAMPLE_TIME_COUNTER[8]_i_3_n_0\,
      S(6) => \S_SAMPLE_TIME_COUNTER[8]_i_4_n_0\,
      S(5) => \S_SAMPLE_TIME_COUNTER[8]_i_5_n_0\,
      S(4) => \S_SAMPLE_TIME_COUNTER[8]_i_6_n_0\,
      S(3) => \S_SAMPLE_TIME_COUNTER[8]_i_7_n_0\,
      S(2) => \S_SAMPLE_TIME_COUNTER[8]_i_8_n_0\,
      S(1) => \S_SAMPLE_TIME_COUNTER[8]_i_9_n_0\,
      S(0) => \S_SAMPLE_TIME_COUNTER[8]_i_10_n_0\
    );
\S_SAMPLE_TIME_COUNTER_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => spi_n_3,
      D => p_2_in(9),
      Q => S_SAMPLE_TIME_COUNTER(9),
      R => RSTP
    );
\S_SAMPLE_TIME_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_SAMPLE_TIME_reg[30]_0\(0),
      D => \S_SAMPLE_TIME_reg[30]_1\(0),
      Q => \S_SAMPLE_TIME_reg_n_0_[0]\,
      R => '0'
    );
\S_SAMPLE_TIME_reg[10]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_SAMPLE_TIME_reg[30]_0\(0),
      D => \S_SAMPLE_TIME_reg[30]_1\(10),
      Q => \S_SAMPLE_TIME_reg_n_0_[10]\,
      R => '0'
    );
\S_SAMPLE_TIME_reg[11]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_SAMPLE_TIME_reg[30]_0\(0),
      D => \S_SAMPLE_TIME_reg[30]_1\(11),
      Q => \S_SAMPLE_TIME_reg_n_0_[11]\,
      R => '0'
    );
\S_SAMPLE_TIME_reg[12]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_SAMPLE_TIME_reg[30]_0\(0),
      D => \S_SAMPLE_TIME_reg[30]_1\(12),
      Q => \S_SAMPLE_TIME_reg_n_0_[12]\,
      R => '0'
    );
\S_SAMPLE_TIME_reg[13]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_SAMPLE_TIME_reg[30]_0\(0),
      D => \S_SAMPLE_TIME_reg[30]_1\(13),
      Q => \S_SAMPLE_TIME_reg_n_0_[13]\,
      R => '0'
    );
\S_SAMPLE_TIME_reg[14]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_SAMPLE_TIME_reg[30]_0\(0),
      D => \S_SAMPLE_TIME_reg[30]_1\(14),
      Q => \S_SAMPLE_TIME_reg_n_0_[14]\,
      R => '0'
    );
\S_SAMPLE_TIME_reg[15]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_SAMPLE_TIME_reg[30]_0\(0),
      D => \S_SAMPLE_TIME_reg[30]_1\(15),
      Q => \S_SAMPLE_TIME_reg_n_0_[15]\,
      R => '0'
    );
\S_SAMPLE_TIME_reg[16]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_SAMPLE_TIME_reg[30]_0\(0),
      D => \S_SAMPLE_TIME_reg[30]_1\(16),
      Q => \S_SAMPLE_TIME_reg_n_0_[16]\,
      R => '0'
    );
\S_SAMPLE_TIME_reg[17]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_SAMPLE_TIME_reg[30]_0\(0),
      D => \S_SAMPLE_TIME_reg[30]_1\(17),
      Q => \S_SAMPLE_TIME_reg_n_0_[17]\,
      R => '0'
    );
\S_SAMPLE_TIME_reg[18]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_SAMPLE_TIME_reg[30]_0\(0),
      D => \S_SAMPLE_TIME_reg[30]_1\(18),
      Q => \S_SAMPLE_TIME_reg_n_0_[18]\,
      R => '0'
    );
\S_SAMPLE_TIME_reg[19]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_SAMPLE_TIME_reg[30]_0\(0),
      D => \S_SAMPLE_TIME_reg[30]_1\(19),
      Q => \S_SAMPLE_TIME_reg_n_0_[19]\,
      R => '0'
    );
\S_SAMPLE_TIME_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_SAMPLE_TIME_reg[30]_0\(0),
      D => \S_SAMPLE_TIME_reg[30]_1\(1),
      Q => \S_SAMPLE_TIME_reg_n_0_[1]\,
      R => '0'
    );
\S_SAMPLE_TIME_reg[20]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_SAMPLE_TIME_reg[30]_0\(0),
      D => \S_SAMPLE_TIME_reg[30]_1\(20),
      Q => \S_SAMPLE_TIME_reg_n_0_[20]\,
      R => '0'
    );
\S_SAMPLE_TIME_reg[21]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_SAMPLE_TIME_reg[30]_0\(0),
      D => \S_SAMPLE_TIME_reg[30]_1\(21),
      Q => \S_SAMPLE_TIME_reg_n_0_[21]\,
      R => '0'
    );
\S_SAMPLE_TIME_reg[22]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_SAMPLE_TIME_reg[30]_0\(0),
      D => \S_SAMPLE_TIME_reg[30]_1\(22),
      Q => \S_SAMPLE_TIME_reg_n_0_[22]\,
      R => '0'
    );
\S_SAMPLE_TIME_reg[23]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_SAMPLE_TIME_reg[30]_0\(0),
      D => \S_SAMPLE_TIME_reg[30]_1\(23),
      Q => \S_SAMPLE_TIME_reg_n_0_[23]\,
      R => '0'
    );
\S_SAMPLE_TIME_reg[24]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_SAMPLE_TIME_reg[30]_0\(0),
      D => \S_SAMPLE_TIME_reg[30]_1\(24),
      Q => \S_SAMPLE_TIME_reg_n_0_[24]\,
      R => '0'
    );
\S_SAMPLE_TIME_reg[25]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_SAMPLE_TIME_reg[30]_0\(0),
      D => \S_SAMPLE_TIME_reg[30]_1\(25),
      Q => \S_SAMPLE_TIME_reg_n_0_[25]\,
      R => '0'
    );
\S_SAMPLE_TIME_reg[26]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_SAMPLE_TIME_reg[30]_0\(0),
      D => \S_SAMPLE_TIME_reg[30]_1\(26),
      Q => \S_SAMPLE_TIME_reg_n_0_[26]\,
      R => '0'
    );
\S_SAMPLE_TIME_reg[27]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_SAMPLE_TIME_reg[30]_0\(0),
      D => \S_SAMPLE_TIME_reg[30]_1\(27),
      Q => \S_SAMPLE_TIME_reg_n_0_[27]\,
      R => '0'
    );
\S_SAMPLE_TIME_reg[28]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_SAMPLE_TIME_reg[30]_0\(0),
      D => \S_SAMPLE_TIME_reg[30]_1\(28),
      Q => \S_SAMPLE_TIME_reg_n_0_[28]\,
      R => '0'
    );
\S_SAMPLE_TIME_reg[29]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_SAMPLE_TIME_reg[30]_0\(0),
      D => \S_SAMPLE_TIME_reg[30]_1\(29),
      Q => \S_SAMPLE_TIME_reg_n_0_[29]\,
      R => '0'
    );
\S_SAMPLE_TIME_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_SAMPLE_TIME_reg[30]_0\(0),
      D => \S_SAMPLE_TIME_reg[30]_1\(2),
      Q => \S_SAMPLE_TIME_reg_n_0_[2]\,
      R => '0'
    );
\S_SAMPLE_TIME_reg[30]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_SAMPLE_TIME_reg[30]_0\(0),
      D => \S_SAMPLE_TIME_reg[30]_1\(30),
      Q => \S_SAMPLE_TIME_reg_n_0_[30]\,
      R => '0'
    );
\S_SAMPLE_TIME_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_SAMPLE_TIME_reg[30]_0\(0),
      D => \S_SAMPLE_TIME_reg[30]_1\(3),
      Q => \S_SAMPLE_TIME_reg_n_0_[3]\,
      R => '0'
    );
\S_SAMPLE_TIME_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_SAMPLE_TIME_reg[30]_0\(0),
      D => \S_SAMPLE_TIME_reg[30]_1\(4),
      Q => \S_SAMPLE_TIME_reg_n_0_[4]\,
      R => '0'
    );
\S_SAMPLE_TIME_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_SAMPLE_TIME_reg[30]_0\(0),
      D => \S_SAMPLE_TIME_reg[30]_1\(5),
      Q => \S_SAMPLE_TIME_reg_n_0_[5]\,
      R => '0'
    );
\S_SAMPLE_TIME_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_SAMPLE_TIME_reg[30]_0\(0),
      D => \S_SAMPLE_TIME_reg[30]_1\(6),
      Q => \S_SAMPLE_TIME_reg_n_0_[6]\,
      R => '0'
    );
\S_SAMPLE_TIME_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_SAMPLE_TIME_reg[30]_0\(0),
      D => \S_SAMPLE_TIME_reg[30]_1\(7),
      Q => \S_SAMPLE_TIME_reg_n_0_[7]\,
      R => '0'
    );
\S_SAMPLE_TIME_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_SAMPLE_TIME_reg[30]_0\(0),
      D => \S_SAMPLE_TIME_reg[30]_1\(8),
      Q => \S_SAMPLE_TIME_reg_n_0_[8]\,
      R => '0'
    );
\S_SAMPLE_TIME_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \S_SAMPLE_TIME_reg[30]_0\(0),
      D => \S_SAMPLE_TIME_reg[30]_1\(9),
      Q => \S_SAMPLE_TIME_reg_n_0_[9]\,
      R => '0'
    );
\S_SPI_BUSY_PIPE[1]_i_1\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"2"
    )
        port map (
      I0 => \^s_enable_reg[0]_0\,
      I1 => \^s_enable_reg[0]\,
      O => \^e\(0)
    );
\S_SPI_BUSY_PIPE[1]_i_2\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"8A"
    )
        port map (
      I0 => S_SPI_BUSY_PIPE(0),
      I1 => \^q\(1),
      I2 => \^q\(0),
      O => \S_SPI_BUSY_PIPE[1]_i_2_n_0\
    );
\S_SPI_BUSY_PIPE_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \^e\(0),
      D => spi_n_4,
      Q => S_SPI_BUSY_PIPE(0),
      R => RSTP
    );
\S_SPI_BUSY_PIPE_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => \^e\(0),
      D => \S_SPI_BUSY_PIPE[1]_i_2_n_0\,
      Q => S_SPI_BUSY_PIPE(1),
      R => RSTP
    );
S_SPI_ENABLE_reg: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => '1',
      D => S_SPI_ENABLE_reg_1,
      Q => \^s_spi_enable_reg_0\,
      R => RSTP
    );
\curstate[0]_i_1__0\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => \^s_enable_reg[0]_0\,
      O => nxtstate(0)
    );
\curstate[1]_i_1\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => \^s_enable_reg[0]\,
      O => nxtstate(1)
    );
\curstate_reg[0]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s00_axi_aclk,
      CE => '1',
      D => nxtstate(0),
      Q => \^q\(0),
      R => RSTP
    );
\curstate_reg[1]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s00_axi_aclk,
      CE => '1',
      D => nxtstate(1),
      Q => \^q\(1),
      R => RSTP
    );
raw_to_si: entity work.zusys_A3_ADC_LTC2311_0_MULT_ADD
     port map (
      CEP => S_CE_CONVERSION,
      CO(0) => nxtstate22_in,
      DSP_ALU_INST(15) => \S_OFFSET_S_C_reg_n_0_[15]\,
      DSP_ALU_INST(14) => \S_OFFSET_S_C_reg_n_0_[14]\,
      DSP_ALU_INST(13) => \S_OFFSET_S_C_reg_n_0_[13]\,
      DSP_ALU_INST(12) => \S_OFFSET_S_C_reg_n_0_[12]\,
      DSP_ALU_INST(11) => \S_OFFSET_S_C_reg_n_0_[11]\,
      DSP_ALU_INST(10) => \S_OFFSET_S_C_reg_n_0_[10]\,
      DSP_ALU_INST(9) => \S_OFFSET_S_C_reg_n_0_[9]\,
      DSP_ALU_INST(8) => \S_OFFSET_S_C_reg_n_0_[8]\,
      DSP_ALU_INST(7) => \S_OFFSET_S_C_reg_n_0_[7]\,
      DSP_ALU_INST(6) => \S_OFFSET_S_C_reg_n_0_[6]\,
      DSP_ALU_INST(5) => \S_OFFSET_S_C_reg_n_0_[5]\,
      DSP_ALU_INST(4) => \S_OFFSET_S_C_reg_n_0_[4]\,
      DSP_ALU_INST(3) => \S_OFFSET_S_C_reg_n_0_[3]\,
      DSP_ALU_INST(2) => \S_OFFSET_S_C_reg_n_0_[2]\,
      DSP_ALU_INST(1) => \S_OFFSET_S_C_reg_n_0_[1]\,
      DSP_ALU_INST(0) => \S_OFFSET_S_C_reg_n_0_[0]\,
      DSP_A_B_DATA_INST(3 downto 0) => S_CONV_COUNTER(3 downto 0),
      DSP_A_B_DATA_INST_0(143 downto 126) => data8(17 downto 0),
      DSP_A_B_DATA_INST_0(125 downto 108) => data7(17 downto 0),
      DSP_A_B_DATA_INST_0(107 downto 90) => data6(17 downto 0),
      DSP_A_B_DATA_INST_0(89 downto 72) => data5(17 downto 0),
      DSP_A_B_DATA_INST_0(71 downto 54) => data4(17 downto 0),
      DSP_A_B_DATA_INST_0(53 downto 36) => data3(17 downto 0),
      DSP_A_B_DATA_INST_0(35 downto 18) => data2(17 downto 0),
      DSP_A_B_DATA_INST_0(17) => \S_CONVERSION_reg_n_0_[17]\,
      DSP_A_B_DATA_INST_0(16) => \S_CONVERSION_reg_n_0_[16]\,
      DSP_A_B_DATA_INST_0(15) => \S_CONVERSION_reg_n_0_[15]\,
      DSP_A_B_DATA_INST_0(14) => \S_CONVERSION_reg_n_0_[14]\,
      DSP_A_B_DATA_INST_0(13) => \S_CONVERSION_reg_n_0_[13]\,
      DSP_A_B_DATA_INST_0(12) => \S_CONVERSION_reg_n_0_[12]\,
      DSP_A_B_DATA_INST_0(11) => \S_CONVERSION_reg_n_0_[11]\,
      DSP_A_B_DATA_INST_0(10) => \S_CONVERSION_reg_n_0_[10]\,
      DSP_A_B_DATA_INST_0(9) => \S_CONVERSION_reg_n_0_[9]\,
      DSP_A_B_DATA_INST_0(8) => \S_CONVERSION_reg_n_0_[8]\,
      DSP_A_B_DATA_INST_0(7) => \S_CONVERSION_reg_n_0_[7]\,
      DSP_A_B_DATA_INST_0(6) => \S_CONVERSION_reg_n_0_[6]\,
      DSP_A_B_DATA_INST_0(5) => \S_CONVERSION_reg_n_0_[5]\,
      DSP_A_B_DATA_INST_0(4) => \S_CONVERSION_reg_n_0_[4]\,
      DSP_A_B_DATA_INST_0(3) => \S_CONVERSION_reg_n_0_[3]\,
      DSP_A_B_DATA_INST_0(2) => \S_CONVERSION_reg_n_0_[2]\,
      DSP_A_B_DATA_INST_0(1) => \S_CONVERSION_reg_n_0_[1]\,
      DSP_A_B_DATA_INST_0(0) => \S_CONVERSION_reg_n_0_[0]\,
      ENABLE => ENABLE,
      P(0) => S_RESULT_S_C(33),
      Q(15 downto 0) => S_RAW_VALUE_S_C(15 downto 0),
      RSTP => RSTP,
      S(7 downto 0) => \^s\(7 downto 0),
      SI_VALID_reg(1 downto 0) => \^q\(1 downto 0),
      SI_VALID_reg_0(1 downto 0) => S_SPI_BUSY_PIPE(1 downto 0),
      SI_VALID_reg_i_3_0(7 downto 0) => \^s_sample_counter_reg[16]_0\(7 downto 0),
      SI_VALID_reg_i_3_1(7 downto 0) => \^s_sample_counter_reg[24]_0\(7 downto 0),
      SI_VALID_reg_i_3_2(6 downto 0) => \^s_sample_counter_reg[31]_0\(6 downto 0),
      SI_VALID_reg_i_3_3(0) => SI_VALID_reg_i_49_n_1,
      SI_VALID_reg_i_8_0(0) => \S_SAMPLES_reg_n_0_[0]\,
      SI_VALID_reg_i_8_1 => \^s_sample_counter_reg[0]_0\,
      SI_VALUE0(127 downto 125) => SI_VALUE0(279 downto 277),
      SI_VALUE0(124 downto 123) => SI_VALUE0(256 downto 255),
      SI_VALUE0(122 downto 103) => SI_VALUE0(244 downto 225),
      SI_VALUE0(102 downto 93) => SI_VALUE0(222 downto 213),
      SI_VALUE0(92 downto 90) => SI_VALUE0(211 downto 209),
      SI_VALUE0(89 downto 88) => SI_VALUE0(192 downto 191),
      SI_VALUE0(87 downto 82) => SI_VALUE0(148 downto 143),
      SI_VALUE0(81 downto 47) => SI_VALUE0(139 downto 105),
      SI_VALUE0(46 downto 44) => SI_VALUE0(78 downto 76),
      SI_VALUE0(43 downto 0) => SI_VALUE0(43 downto 0),
      \SI_VALUE_reg[115]\ => \SI_VALUE[180]_i_3_n_0\,
      \SI_VALUE_reg[206]\ => \SI_VALUE[270]_i_3_n_0\,
      \SI_VALUE_reg[209]\ => \S_RESULT_COUNTER_reg[0]_rep_n_0\,
      \SI_VALUE_reg[209]_0\ => \S_RESULT_COUNTER_reg[1]_rep_n_0\,
      \SI_VALUE_reg[273]\ => \SI_VALUE[273]_i_2_n_0\,
      \SI_VALUE_reg[273]_0\ => \SI_VALUE[273]_i_4_n_0\,
      \SI_VALUE_reg[279]\ => \SI_VALUE[279]_i_7_n_0\,
      \SI_VALUE_reg[34]\(3 downto 0) => S_RESULT_COUNTER(3 downto 0),
      \S_CONV_COUNTER_reg[0]\ => raw_to_si_n_137,
      S_DUMMY_SAMPLE => \^s_dummy_sample\,
      \S_ENABLE_reg[0]\ => \^s_enable_reg[0]\,
      \S_ENABLE_reg[0]_0\ => \^s_enable_reg[0]_0\,
      \S_RESULT_COUNTER_reg[0]_rep\ => raw_to_si_n_1,
      \S_SAMPLE_TIME_COUNTER[30]_i_7\(30 downto 0) => S_SAMPLE_TIME_COUNTER(30 downto 0),
      \S_SAMPLE_TIME_COUNTER_reg[11]\ => raw_to_si_n_133,
      \S_SAMPLE_TIME_COUNTER_reg[17]\ => raw_to_si_n_136,
      \S_SAMPLE_TIME_COUNTER_reg[23]\ => raw_to_si_n_135,
      \curstate_reg[0]\ => raw_to_si_n_134,
      nxtstate3(29 downto 0) => nxtstate3(30 downto 1),
      s00_axi_aclk => s00_axi_aclk
    );
spi: entity work.zusys_A3_ADC_LTC2311_0_SPI_MASTER
     port map (
      CPHA => CPHA,
      CPOL => CPOL,
      D(0) => spi_n_4,
      E(0) => spi_n_3,
      Q(1 downto 0) => \^q\(1 downto 0),
      RAW_VALUE(127 downto 0) => RAW_VALUE(127 downto 0),
      RSTP => RSTP,
      SCLK_IN => SCLK_IN,
      SS_IN_N => SS_IN_N,
      SS_N(0) => SS_N(0),
      S_AXI_ARESETN => S_AXI_ARESETN,
      \S_BIT_COUNT_reg[0]_0\ => \^s_spi_enable_reg_0\,
      S_CPOL_reg_0(0) => S_CPOL_reg(0),
      \S_DEL_COUNT_reg[7]_0\(31 downto 0) => \S_DEL_COUNT_reg[7]\(31 downto 0),
      \S_RAW_VALUE_S_C_reg[0]\ => \S_RAW_VALUE_S_C[15]_i_3_n_0\,
      \S_RAW_VALUE_S_C_reg[0]_0\(3 downto 0) => S_CHANNEL_COUNTER(3 downto 0),
      \S_RX_BUFFER_reg[112]_0\(7 downto 0) => D(7 downto 0),
      \S_RX_OUT_BUFFER_reg[127]_0\(15) => spi_n_5,
      \S_RX_OUT_BUFFER_reg[127]_0\(14) => spi_n_6,
      \S_RX_OUT_BUFFER_reg[127]_0\(13) => spi_n_7,
      \S_RX_OUT_BUFFER_reg[127]_0\(12) => spi_n_8,
      \S_RX_OUT_BUFFER_reg[127]_0\(11) => spi_n_9,
      \S_RX_OUT_BUFFER_reg[127]_0\(10) => spi_n_10,
      \S_RX_OUT_BUFFER_reg[127]_0\(9) => spi_n_11,
      \S_RX_OUT_BUFFER_reg[127]_0\(8) => spi_n_12,
      \S_RX_OUT_BUFFER_reg[127]_0\(7) => spi_n_13,
      \S_RX_OUT_BUFFER_reg[127]_0\(6) => spi_n_14,
      \S_RX_OUT_BUFFER_reg[127]_0\(5) => spi_n_15,
      \S_RX_OUT_BUFFER_reg[127]_0\(4) => spi_n_16,
      \S_RX_OUT_BUFFER_reg[127]_0\(3) => spi_n_17,
      \S_RX_OUT_BUFFER_reg[127]_0\(2) => spi_n_18,
      \S_RX_OUT_BUFFER_reg[127]_0\(1) => spi_n_19,
      \S_RX_OUT_BUFFER_reg[127]_0\(0) => spi_n_20,
      \S_SAMPLE_TIME_COUNTER_reg[0]\ => \S_SAMPLE_TIME_COUNTER[30]_i_3_n_0\,
      \S_SAMPLE_TIME_COUNTER_reg[0]_0\ => \S_SAMPLE_TIME_COUNTER[30]_i_4_n_0\,
      \S_SAMPLE_TIME_COUNTER_reg[0]_1\ => \^s_enable_reg[0]_0\,
      S_SCLK => S_SCLK,
      S_SCLK_reg_0 => \^s_manual_reg_0\,
      S_SPI_BUSY => S_SPI_BUSY,
      s00_axi_aclk => s00_axi_aclk,
      s00_axi_aresetn => s00_axi_aresetn
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity zusys_A3_ADC_LTC2311_0_ADC_LTC2311_v3_0 is
  port (
    \S_SAMPLE_COUNTER_reg[0]\ : out STD_LOGIC;
    s00_axi_awready : out STD_LOGIC;
    s00_axi_wready : out STD_LOGIC;
    s00_axi_arready : out STD_LOGIC;
    RAW_VALID : out STD_LOGIC_VECTOR ( 0 to 0 );
    SI_VALID : out STD_LOGIC_VECTOR ( 0 to 0 );
    s00_axi_rdata : out STD_LOGIC_VECTOR ( 31 downto 0 );
    RAW_VALUE : out STD_LOGIC_VECTOR ( 127 downto 0 );
    SS_N : out STD_LOGIC_VECTOR ( 0 to 0 );
    SAMPLE_COUNTER : out STD_LOGIC_VECTOR ( 30 downto 0 );
    SI_VALUE : out STD_LOGIC_VECTOR ( 279 downto 0 );
    SCLK_DIFF : out STD_LOGIC_VECTOR ( 1 downto 0 );
    s00_axi_rvalid : out STD_LOGIC;
    s00_axi_bvalid : out STD_LOGIC;
    s00_axi_aresetn : in STD_LOGIC;
    s00_axi_aclk : in STD_LOGIC;
    s00_axi_awaddr : in STD_LOGIC_VECTOR ( 3 downto 0 );
    s00_axi_wdata : in STD_LOGIC_VECTOR ( 31 downto 0 );
    s00_axi_araddr : in STD_LOGIC_VECTOR ( 3 downto 0 );
    MISO_DIFF : in STD_LOGIC_VECTOR ( 15 downto 0 );
    TRIGGER_CNV : in STD_LOGIC_VECTOR ( 0 to 0 );
    s00_axi_wvalid : in STD_LOGIC;
    s00_axi_awvalid : in STD_LOGIC;
    s00_axi_wstrb : in STD_LOGIC_VECTOR ( 3 downto 0 );
    s00_axi_arvalid : in STD_LOGIC;
    s00_axi_bready : in STD_LOGIC;
    s00_axi_rready : in STD_LOGIC
  );
  attribute ORIG_REF_NAME : string;
  attribute ORIG_REF_NAME of zusys_A3_ADC_LTC2311_0_ADC_LTC2311_v3_0 : entity is "ADC_LTC2311_v3_0";
end zusys_A3_ADC_LTC2311_0_ADC_LTC2311_v3_0;

architecture STRUCTURE of zusys_A3_ADC_LTC2311_0_ADC_LTC2311_v3_0 is
  signal ADC_LTC2311_v3_0_S00_AXI_inst_n_10 : STD_LOGIC;
  signal ADC_LTC2311_v3_0_S00_AXI_inst_n_11 : STD_LOGIC;
  signal ADC_LTC2311_v3_0_S00_AXI_inst_n_12 : STD_LOGIC;
  signal ADC_LTC2311_v3_0_S00_AXI_inst_n_13 : STD_LOGIC;
  signal ADC_LTC2311_v3_0_S00_AXI_inst_n_130 : STD_LOGIC;
  signal ADC_LTC2311_v3_0_S00_AXI_inst_n_131 : STD_LOGIC;
  signal ADC_LTC2311_v3_0_S00_AXI_inst_n_134 : STD_LOGIC;
  signal ADC_LTC2311_v3_0_S00_AXI_inst_n_135 : STD_LOGIC;
  signal ADC_LTC2311_v3_0_S00_AXI_inst_n_14 : STD_LOGIC;
  signal ADC_LTC2311_v3_0_S00_AXI_inst_n_15 : STD_LOGIC;
  signal ADC_LTC2311_v3_0_S00_AXI_inst_n_16 : STD_LOGIC;
  signal ADC_LTC2311_v3_0_S00_AXI_inst_n_17 : STD_LOGIC;
  signal ADC_LTC2311_v3_0_S00_AXI_inst_n_18 : STD_LOGIC;
  signal ADC_LTC2311_v3_0_S00_AXI_inst_n_19 : STD_LOGIC;
  signal ADC_LTC2311_v3_0_S00_AXI_inst_n_20 : STD_LOGIC;
  signal ADC_LTC2311_v3_0_S00_AXI_inst_n_21 : STD_LOGIC;
  signal ADC_LTC2311_v3_0_S00_AXI_inst_n_22 : STD_LOGIC;
  signal ADC_LTC2311_v3_0_S00_AXI_inst_n_23 : STD_LOGIC;
  signal ADC_LTC2311_v3_0_S00_AXI_inst_n_24 : STD_LOGIC;
  signal ADC_LTC2311_v3_0_S00_AXI_inst_n_25 : STD_LOGIC;
  signal ADC_LTC2311_v3_0_S00_AXI_inst_n_26 : STD_LOGIC;
  signal ADC_LTC2311_v3_0_S00_AXI_inst_n_29 : STD_LOGIC;
  signal ADC_LTC2311_v3_0_S00_AXI_inst_n_30 : STD_LOGIC;
  signal ADC_LTC2311_v3_0_S00_AXI_inst_n_32 : STD_LOGIC;
  signal ADC_LTC2311_v3_0_S00_AXI_inst_n_33 : STD_LOGIC;
  signal ADC_LTC2311_v3_0_S00_AXI_inst_n_51 : STD_LOGIC;
  signal ADC_LTC2311_v3_0_S00_AXI_inst_n_52 : STD_LOGIC;
  signal ADC_LTC2311_v3_0_S00_AXI_inst_n_53 : STD_LOGIC;
  signal ADC_LTC2311_v3_0_S00_AXI_inst_n_54 : STD_LOGIC;
  signal ADC_LTC2311_v3_0_S00_AXI_inst_n_55 : STD_LOGIC;
  signal ADC_LTC2311_v3_0_S00_AXI_inst_n_56 : STD_LOGIC;
  signal ADC_LTC2311_v3_0_S00_AXI_inst_n_57 : STD_LOGIC;
  signal ADC_LTC2311_v3_0_S00_AXI_inst_n_58 : STD_LOGIC;
  signal ADC_LTC2311_v3_0_S00_AXI_inst_n_59 : STD_LOGIC;
  signal ADC_LTC2311_v3_0_S00_AXI_inst_n_60 : STD_LOGIC;
  signal ADC_LTC2311_v3_0_S00_AXI_inst_n_61 : STD_LOGIC;
  signal ADC_LTC2311_v3_0_S00_AXI_inst_n_62 : STD_LOGIC;
  signal ADC_LTC2311_v3_0_S00_AXI_inst_n_63 : STD_LOGIC;
  signal ADC_LTC2311_v3_0_S00_AXI_inst_n_64 : STD_LOGIC;
  signal ADC_LTC2311_v3_0_S00_AXI_inst_n_65 : STD_LOGIC;
  signal ADC_LTC2311_v3_0_S00_AXI_inst_n_66 : STD_LOGIC;
  signal ADC_LTC2311_v3_0_S00_AXI_inst_n_7 : STD_LOGIC;
  signal BUSY : STD_LOGIC;
  signal \BUSY_i_1__0_n_0\ : STD_LOGIC;
  signal CPHA : STD_LOGIC;
  signal CPOL : STD_LOGIC;
  signal ENABLE : STD_LOGIC;
  signal \GEN_ADC_CONT[0].inst_adc_n_10\ : STD_LOGIC;
  signal \GEN_ADC_CONT[0].inst_adc_n_14\ : STD_LOGIC;
  signal \GEN_ADC_CONT[0].inst_adc_n_15\ : STD_LOGIC;
  signal \GEN_ADC_CONT[0].inst_adc_n_4\ : STD_LOGIC;
  signal \GEN_ADC_CONT[0].inst_adc_n_8\ : STD_LOGIC;
  signal \GEN_ADC_CONT[0].inst_adc_n_9\ : STD_LOGIC;
  signal MANUAL : STD_LOGIC;
  signal POST_DELAY : STD_LOGIC_VECTOR ( 7 downto 0 );
  signal PRE_DELAY : STD_LOGIC_VECTOR ( 7 downto 0 );
  signal P_ADC_CR_IN : STD_LOGIC_VECTOR ( 4 downto 2 );
  signal \^raw_valid\ : STD_LOGIC_VECTOR ( 0 to 0 );
  signal RAW_VALID_i_1_n_0 : STD_LOGIC;
  signal SCLK_IN : STD_LOGIC;
  signal SET_CONVERSION : STD_LOGIC;
  signal SET_OFFSET : STD_LOGIC;
  signal SET_SAMPLES : STD_LOGIC;
  signal SET_SAMPLE_TIME : STD_LOGIC;
  signal \^si_valid\ : STD_LOGIC_VECTOR ( 0 to 0 );
  signal SS_IN_N : STD_LOGIC;
  signal S_ADC_CONV_VALUE : STD_LOGIC_VECTOR ( 30 downto 0 );
  signal S_ADC_CR : STD_LOGIC_VECTOR ( 3 to 3 );
  signal \S_ADC_SPI_CR_IN[5]_i_1_n_0\ : STD_LOGIC;
  signal \S_ADC_SPI_CR_IN_reg_n_0_[1]\ : STD_LOGIC;
  signal \S_ADC_SPI_CR_IN_reg_n_0_[3]\ : STD_LOGIC;
  signal \S_ADC_SPI_CR_IN_reg_n_0_[5]\ : STD_LOGIC;
  signal S_AXI_ARESETN : STD_LOGIC;
  signal S_DUMMY_SAMPLE : STD_LOGIC;
  signal S_DUMMY_SAMPLE_i_1_n_0 : STD_LOGIC;
  signal S_MANUAL_i_1_n_0 : STD_LOGIC;
  signal S_MISO : STD_LOGIC_VECTOR ( 7 downto 0 );
  signal S_SAMPLE_TIME : STD_LOGIC;
  signal S_SCLK : STD_LOGIC;
  signal S_SCLK_IN : STD_LOGIC;
  signal S_SET_CONVERSION : STD_LOGIC;
  signal S_SPI_BUSY : STD_LOGIC;
  signal S_SPI_ENABLE_i_1_n_0 : STD_LOGIC;
  signal S_SS_IN_N : STD_LOGIC;
  signal S_TRIGGER_CNV_PIPE : STD_LOGIC;
  signal curstate : STD_LOGIC_VECTOR ( 1 downto 0 );
  signal curstate_0 : STD_LOGIC_VECTOR ( 1 downto 0 );
  signal nxtstate : STD_LOGIC_VECTOR ( 1 downto 0 );
  signal \raw_to_si/RSTD\ : STD_LOGIC;
  attribute FSM_ENCODING : string;
  attribute FSM_ENCODING of \curstate_reg[0]\ : label is "auto";
  attribute FSM_SAFE_STATE : string;
  attribute FSM_SAFE_STATE of \curstate_reg[0]\ : label is "power_on_state";
  attribute FSM_ENCODING of \curstate_reg[1]\ : label is "auto";
  attribute FSM_SAFE_STATE of \curstate_reg[1]\ : label is "power_on_state";
  attribute CAPACITANCE : string;
  attribute CAPACITANCE of \gen_diff.gen_diff1[0].OBUFDS_inst\ : label is "DONT_CARE";
  attribute XILINX_LEGACY_PRIM : string;
  attribute XILINX_LEGACY_PRIM of \gen_diff.gen_diff1[0].OBUFDS_inst\ : label is "OBUFDS";
  attribute box_type : string;
  attribute box_type of \gen_diff.gen_diff1[0].OBUFDS_inst\ : label is "PRIMITIVE";
  attribute CAPACITANCE of \gen_diff.gen_diff1[0].gen_diff2[0].IBUFDS_inst\ : label is "DONT_CARE";
  attribute IBUF_DELAY_VALUE : string;
  attribute IBUF_DELAY_VALUE of \gen_diff.gen_diff1[0].gen_diff2[0].IBUFDS_inst\ : label is "0";
  attribute IFD_DELAY_VALUE : string;
  attribute IFD_DELAY_VALUE of \gen_diff.gen_diff1[0].gen_diff2[0].IBUFDS_inst\ : label is "AUTO";
  attribute box_type of \gen_diff.gen_diff1[0].gen_diff2[0].IBUFDS_inst\ : label is "PRIMITIVE";
  attribute CAPACITANCE of \gen_diff.gen_diff1[0].gen_diff2[1].IBUFDS_inst\ : label is "DONT_CARE";
  attribute IBUF_DELAY_VALUE of \gen_diff.gen_diff1[0].gen_diff2[1].IBUFDS_inst\ : label is "0";
  attribute IFD_DELAY_VALUE of \gen_diff.gen_diff1[0].gen_diff2[1].IBUFDS_inst\ : label is "AUTO";
  attribute box_type of \gen_diff.gen_diff1[0].gen_diff2[1].IBUFDS_inst\ : label is "PRIMITIVE";
  attribute CAPACITANCE of \gen_diff.gen_diff1[0].gen_diff2[2].IBUFDS_inst\ : label is "DONT_CARE";
  attribute IBUF_DELAY_VALUE of \gen_diff.gen_diff1[0].gen_diff2[2].IBUFDS_inst\ : label is "0";
  attribute IFD_DELAY_VALUE of \gen_diff.gen_diff1[0].gen_diff2[2].IBUFDS_inst\ : label is "AUTO";
  attribute box_type of \gen_diff.gen_diff1[0].gen_diff2[2].IBUFDS_inst\ : label is "PRIMITIVE";
  attribute CAPACITANCE of \gen_diff.gen_diff1[0].gen_diff2[3].IBUFDS_inst\ : label is "DONT_CARE";
  attribute IBUF_DELAY_VALUE of \gen_diff.gen_diff1[0].gen_diff2[3].IBUFDS_inst\ : label is "0";
  attribute IFD_DELAY_VALUE of \gen_diff.gen_diff1[0].gen_diff2[3].IBUFDS_inst\ : label is "AUTO";
  attribute box_type of \gen_diff.gen_diff1[0].gen_diff2[3].IBUFDS_inst\ : label is "PRIMITIVE";
  attribute CAPACITANCE of \gen_diff.gen_diff1[0].gen_diff2[4].IBUFDS_inst\ : label is "DONT_CARE";
  attribute IBUF_DELAY_VALUE of \gen_diff.gen_diff1[0].gen_diff2[4].IBUFDS_inst\ : label is "0";
  attribute IFD_DELAY_VALUE of \gen_diff.gen_diff1[0].gen_diff2[4].IBUFDS_inst\ : label is "AUTO";
  attribute box_type of \gen_diff.gen_diff1[0].gen_diff2[4].IBUFDS_inst\ : label is "PRIMITIVE";
  attribute CAPACITANCE of \gen_diff.gen_diff1[0].gen_diff2[5].IBUFDS_inst\ : label is "DONT_CARE";
  attribute IBUF_DELAY_VALUE of \gen_diff.gen_diff1[0].gen_diff2[5].IBUFDS_inst\ : label is "0";
  attribute IFD_DELAY_VALUE of \gen_diff.gen_diff1[0].gen_diff2[5].IBUFDS_inst\ : label is "AUTO";
  attribute box_type of \gen_diff.gen_diff1[0].gen_diff2[5].IBUFDS_inst\ : label is "PRIMITIVE";
  attribute CAPACITANCE of \gen_diff.gen_diff1[0].gen_diff2[6].IBUFDS_inst\ : label is "DONT_CARE";
  attribute IBUF_DELAY_VALUE of \gen_diff.gen_diff1[0].gen_diff2[6].IBUFDS_inst\ : label is "0";
  attribute IFD_DELAY_VALUE of \gen_diff.gen_diff1[0].gen_diff2[6].IBUFDS_inst\ : label is "AUTO";
  attribute box_type of \gen_diff.gen_diff1[0].gen_diff2[6].IBUFDS_inst\ : label is "PRIMITIVE";
  attribute CAPACITANCE of \gen_diff.gen_diff1[0].gen_diff2[7].IBUFDS_inst\ : label is "DONT_CARE";
  attribute IBUF_DELAY_VALUE of \gen_diff.gen_diff1[0].gen_diff2[7].IBUFDS_inst\ : label is "0";
  attribute IFD_DELAY_VALUE of \gen_diff.gen_diff1[0].gen_diff2[7].IBUFDS_inst\ : label is "AUTO";
  attribute box_type of \gen_diff.gen_diff1[0].gen_diff2[7].IBUFDS_inst\ : label is "PRIMITIVE";
begin
  RAW_VALID(0) <= \^raw_valid\(0);
  SI_VALID(0) <= \^si_valid\(0);
ADC_LTC2311_v3_0_S00_AXI_inst: entity work.zusys_A3_ADC_LTC2311_0_ADC_LTC2311_v3_0_S00_AXI
     port map (
      \ADC_CHANNEL_reg[7]_0\(7) => ADC_LTC2311_v3_0_S00_AXI_inst_n_18,
      \ADC_CHANNEL_reg[7]_0\(6) => ADC_LTC2311_v3_0_S00_AXI_inst_n_19,
      \ADC_CHANNEL_reg[7]_0\(5) => ADC_LTC2311_v3_0_S00_AXI_inst_n_20,
      \ADC_CHANNEL_reg[7]_0\(4) => ADC_LTC2311_v3_0_S00_AXI_inst_n_21,
      \ADC_CHANNEL_reg[7]_0\(3) => ADC_LTC2311_v3_0_S00_AXI_inst_n_22,
      \ADC_CHANNEL_reg[7]_0\(2) => ADC_LTC2311_v3_0_S00_AXI_inst_n_23,
      \ADC_CHANNEL_reg[7]_0\(1) => ADC_LTC2311_v3_0_S00_AXI_inst_n_24,
      \ADC_CHANNEL_reg[7]_0\(0) => ADC_LTC2311_v3_0_S00_AXI_inst_n_25,
      \ADC_CONV_VALUE_reg[30]_0\(30 downto 0) => S_ADC_CONV_VALUE(30 downto 0),
      \ADC_CR_reg[2]_0\ => ADC_LTC2311_v3_0_S00_AXI_inst_n_30,
      \ADC_CR_reg[3]_0\(0) => S_ADC_CR(3),
      \ADC_CR_reg[3]_1\ => ADC_LTC2311_v3_0_S00_AXI_inst_n_7,
      \ADC_CR_reg[3]_2\(0) => ADC_LTC2311_v3_0_S00_AXI_inst_n_131,
      \ADC_CR_reg[6]_0\ => ADC_LTC2311_v3_0_S00_AXI_inst_n_135,
      \ADC_MASTER_CHANNEL_reg[0]_0\ => ADC_LTC2311_v3_0_S00_AXI_inst_n_29,
      \ADC_MASTER_CHANNEL_reg[0]_1\ => ADC_LTC2311_v3_0_S00_AXI_inst_n_134,
      \ADC_SPI_CR_reg[3]_0\(1) => \S_ADC_SPI_CR_IN_reg_n_0_[3]\,
      \ADC_SPI_CR_reg[3]_0\(0) => \S_ADC_SPI_CR_IN_reg_n_0_[1]\,
      \ADC_SPI_CR_reg[5]_0\ => \S_ADC_SPI_CR_IN_reg_n_0_[5]\,
      BUSY => BUSY,
      CPHA => CPHA,
      CPOL => CPOL,
      D(1) => ADC_LTC2311_v3_0_S00_AXI_inst_n_32,
      D(0) => ADC_LTC2311_v3_0_S00_AXI_inst_n_33,
      E(0) => S_SAMPLE_TIME,
      ENABLE => ENABLE,
      P_ADC_CR_IN(1) => P_ADC_CR_IN(4),
      P_ADC_CR_IN(0) => P_ADC_CR_IN(2),
      Q(31 downto 24) => POST_DELAY(7 downto 0),
      Q(23 downto 16) => PRE_DELAY(7 downto 0),
      Q(15) => ADC_LTC2311_v3_0_S00_AXI_inst_n_51,
      Q(14) => ADC_LTC2311_v3_0_S00_AXI_inst_n_52,
      Q(13) => ADC_LTC2311_v3_0_S00_AXI_inst_n_53,
      Q(12) => ADC_LTC2311_v3_0_S00_AXI_inst_n_54,
      Q(11) => ADC_LTC2311_v3_0_S00_AXI_inst_n_55,
      Q(10) => ADC_LTC2311_v3_0_S00_AXI_inst_n_56,
      Q(9) => ADC_LTC2311_v3_0_S00_AXI_inst_n_57,
      Q(8) => ADC_LTC2311_v3_0_S00_AXI_inst_n_58,
      Q(7) => ADC_LTC2311_v3_0_S00_AXI_inst_n_59,
      Q(6) => ADC_LTC2311_v3_0_S00_AXI_inst_n_60,
      Q(5) => ADC_LTC2311_v3_0_S00_AXI_inst_n_61,
      Q(4) => ADC_LTC2311_v3_0_S00_AXI_inst_n_62,
      Q(3) => ADC_LTC2311_v3_0_S00_AXI_inst_n_63,
      Q(2) => ADC_LTC2311_v3_0_S00_AXI_inst_n_64,
      Q(1) => ADC_LTC2311_v3_0_S00_AXI_inst_n_65,
      Q(0) => ADC_LTC2311_v3_0_S00_AXI_inst_n_66,
      RAW_VALID(0) => \^raw_valid\(0),
      RSTP => \raw_to_si/RSTD\,
      SET_CONVERSION => SET_CONVERSION,
      SET_OFFSET => SET_OFFSET,
      SET_SAMPLES => SET_SAMPLES,
      SET_SAMPLE_TIME => SET_SAMPLE_TIME,
      SI_VALID(0) => \^si_valid\(0),
      S_AXI_ARESETN => S_AXI_ARESETN,
      \S_ENABLE_reg[0]\ => ADC_LTC2311_v3_0_S00_AXI_inst_n_26,
      S_SCLK_IN => S_SCLK_IN,
      S_SET_CONVERSION => S_SET_CONVERSION,
      \S_SET_CONVERSION_reg[0]\(7) => ADC_LTC2311_v3_0_S00_AXI_inst_n_10,
      \S_SET_CONVERSION_reg[0]\(6) => ADC_LTC2311_v3_0_S00_AXI_inst_n_11,
      \S_SET_CONVERSION_reg[0]\(5) => ADC_LTC2311_v3_0_S00_AXI_inst_n_12,
      \S_SET_CONVERSION_reg[0]\(4) => ADC_LTC2311_v3_0_S00_AXI_inst_n_13,
      \S_SET_CONVERSION_reg[0]\(3) => ADC_LTC2311_v3_0_S00_AXI_inst_n_14,
      \S_SET_CONVERSION_reg[0]\(2) => ADC_LTC2311_v3_0_S00_AXI_inst_n_15,
      \S_SET_CONVERSION_reg[0]\(1) => ADC_LTC2311_v3_0_S00_AXI_inst_n_16,
      \S_SET_CONVERSION_reg[0]\(0) => ADC_LTC2311_v3_0_S00_AXI_inst_n_17,
      \S_SET_SAMPLES_reg[0]\ => ADC_LTC2311_v3_0_S00_AXI_inst_n_130,
      S_SS_IN_N => S_SS_IN_N,
      S_TRIGGER_CNV_PIPE => S_TRIGGER_CNV_PIPE,
      TRIGGER_CNV(0) => TRIGGER_CNV(0),
      axi_arready_reg_0 => s00_axi_arready,
      axi_awready_reg_0 => s00_axi_awready,
      axi_wready_reg_0 => s00_axi_wready,
      \curstate_reg[0]\(1 downto 0) => curstate(1 downto 0),
      nxtstate(1 downto 0) => nxtstate(1 downto 0),
      s00_axi_aclk => s00_axi_aclk,
      s00_axi_araddr(3 downto 0) => s00_axi_araddr(3 downto 0),
      s00_axi_aresetn => s00_axi_aresetn,
      s00_axi_arvalid => s00_axi_arvalid,
      s00_axi_awaddr(3 downto 0) => s00_axi_awaddr(3 downto 0),
      s00_axi_awvalid => s00_axi_awvalid,
      s00_axi_bready => s00_axi_bready,
      s00_axi_bvalid => s00_axi_bvalid,
      s00_axi_rdata(31 downto 0) => s00_axi_rdata(31 downto 0),
      s00_axi_rready => s00_axi_rready,
      s00_axi_rvalid => s00_axi_rvalid,
      s00_axi_wdata(31 downto 0) => s00_axi_wdata(31 downto 0),
      s00_axi_wstrb(3 downto 0) => s00_axi_wstrb(3 downto 0),
      s00_axi_wvalid => s00_axi_wvalid
    );
\BUSY_i_1__0\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"F7FF0002"
    )
        port map (
      I0 => \GEN_ADC_CONT[0].inst_adc_n_4\,
      I1 => curstate_0(0),
      I2 => curstate_0(1),
      I3 => \GEN_ADC_CONT[0].inst_adc_n_10\,
      I4 => BUSY,
      O => \BUSY_i_1__0_n_0\
    );
\GEN_ADC_CONT[0].inst_adc\: entity work.zusys_A3_ADC_LTC2311_0_ADC_CONTROLLER
     port map (
      BUSY => BUSY,
      BUSY_reg_0 => \BUSY_i_1__0_n_0\,
      CPHA => CPHA,
      CPOL => CPOL,
      D(7 downto 0) => S_MISO(7 downto 0),
      E(0) => \GEN_ADC_CONT[0].inst_adc_n_15\,
      ENABLE => ENABLE,
      Q(1 downto 0) => curstate_0(1 downto 0),
      RAW_VALID(0) => \^raw_valid\(0),
      RAW_VALID_reg_0 => RAW_VALID_i_1_n_0,
      RAW_VALUE(127 downto 0) => RAW_VALUE(127 downto 0),
      RSTP => \raw_to_si/RSTD\,
      S(7 downto 0) => SAMPLE_COUNTER(7 downto 0),
      SCLK_IN => SCLK_IN,
      SET_CONVERSION => SET_CONVERSION,
      SET_OFFSET => SET_OFFSET,
      SET_SAMPLES => SET_SAMPLES,
      SI_VALID(0) => \^si_valid\(0),
      SI_VALUE(279 downto 0) => SI_VALUE(279 downto 0),
      SS_IN_N => SS_IN_N,
      SS_N(0) => SS_N(0),
      S_AXI_ARESETN => S_AXI_ARESETN,
      \S_CONVERSION_reg[126]_0\(7) => ADC_LTC2311_v3_0_S00_AXI_inst_n_10,
      \S_CONVERSION_reg[126]_0\(6) => ADC_LTC2311_v3_0_S00_AXI_inst_n_11,
      \S_CONVERSION_reg[126]_0\(5) => ADC_LTC2311_v3_0_S00_AXI_inst_n_12,
      \S_CONVERSION_reg[126]_0\(4) => ADC_LTC2311_v3_0_S00_AXI_inst_n_13,
      \S_CONVERSION_reg[126]_0\(3) => ADC_LTC2311_v3_0_S00_AXI_inst_n_14,
      \S_CONVERSION_reg[126]_0\(2) => ADC_LTC2311_v3_0_S00_AXI_inst_n_15,
      \S_CONVERSION_reg[126]_0\(1) => ADC_LTC2311_v3_0_S00_AXI_inst_n_16,
      \S_CONVERSION_reg[126]_0\(0) => ADC_LTC2311_v3_0_S00_AXI_inst_n_17,
      S_CPOL_reg(0) => S_ADC_CR(3),
      \S_DEL_COUNT_reg[7]\(31 downto 24) => POST_DELAY(7 downto 0),
      \S_DEL_COUNT_reg[7]\(23 downto 16) => PRE_DELAY(7 downto 0),
      \S_DEL_COUNT_reg[7]\(15) => ADC_LTC2311_v3_0_S00_AXI_inst_n_51,
      \S_DEL_COUNT_reg[7]\(14) => ADC_LTC2311_v3_0_S00_AXI_inst_n_52,
      \S_DEL_COUNT_reg[7]\(13) => ADC_LTC2311_v3_0_S00_AXI_inst_n_53,
      \S_DEL_COUNT_reg[7]\(12) => ADC_LTC2311_v3_0_S00_AXI_inst_n_54,
      \S_DEL_COUNT_reg[7]\(11) => ADC_LTC2311_v3_0_S00_AXI_inst_n_55,
      \S_DEL_COUNT_reg[7]\(10) => ADC_LTC2311_v3_0_S00_AXI_inst_n_56,
      \S_DEL_COUNT_reg[7]\(9) => ADC_LTC2311_v3_0_S00_AXI_inst_n_57,
      \S_DEL_COUNT_reg[7]\(8) => ADC_LTC2311_v3_0_S00_AXI_inst_n_58,
      \S_DEL_COUNT_reg[7]\(7) => ADC_LTC2311_v3_0_S00_AXI_inst_n_59,
      \S_DEL_COUNT_reg[7]\(6) => ADC_LTC2311_v3_0_S00_AXI_inst_n_60,
      \S_DEL_COUNT_reg[7]\(5) => ADC_LTC2311_v3_0_S00_AXI_inst_n_61,
      \S_DEL_COUNT_reg[7]\(4) => ADC_LTC2311_v3_0_S00_AXI_inst_n_62,
      \S_DEL_COUNT_reg[7]\(3) => ADC_LTC2311_v3_0_S00_AXI_inst_n_63,
      \S_DEL_COUNT_reg[7]\(2) => ADC_LTC2311_v3_0_S00_AXI_inst_n_64,
      \S_DEL_COUNT_reg[7]\(1) => ADC_LTC2311_v3_0_S00_AXI_inst_n_65,
      \S_DEL_COUNT_reg[7]\(0) => ADC_LTC2311_v3_0_S00_AXI_inst_n_66,
      S_DUMMY_SAMPLE => S_DUMMY_SAMPLE,
      S_DUMMY_SAMPLE_reg_0 => S_DUMMY_SAMPLE_i_1_n_0,
      \S_ENABLE_reg[0]\ => \GEN_ADC_CONT[0].inst_adc_n_4\,
      \S_ENABLE_reg[0]_0\ => \GEN_ADC_CONT[0].inst_adc_n_10\,
      \S_ENABLE_reg[0]_1\ => \GEN_ADC_CONT[0].inst_adc_n_14\,
      S_MANUAL_reg_0 => \GEN_ADC_CONT[0].inst_adc_n_8\,
      S_MANUAL_reg_1 => S_MANUAL_i_1_n_0,
      \S_OFFSET_reg[112]_0\(7) => ADC_LTC2311_v3_0_S00_AXI_inst_n_18,
      \S_OFFSET_reg[112]_0\(6) => ADC_LTC2311_v3_0_S00_AXI_inst_n_19,
      \S_OFFSET_reg[112]_0\(5) => ADC_LTC2311_v3_0_S00_AXI_inst_n_20,
      \S_OFFSET_reg[112]_0\(4) => ADC_LTC2311_v3_0_S00_AXI_inst_n_21,
      \S_OFFSET_reg[112]_0\(3) => ADC_LTC2311_v3_0_S00_AXI_inst_n_22,
      \S_OFFSET_reg[112]_0\(2) => ADC_LTC2311_v3_0_S00_AXI_inst_n_23,
      \S_OFFSET_reg[112]_0\(1) => ADC_LTC2311_v3_0_S00_AXI_inst_n_24,
      \S_OFFSET_reg[112]_0\(0) => ADC_LTC2311_v3_0_S00_AXI_inst_n_25,
      \S_SAMPLE_COUNTER_reg[0]_0\ => \S_SAMPLE_COUNTER_reg[0]\,
      \S_SAMPLE_COUNTER_reg[16]_0\(7 downto 0) => SAMPLE_COUNTER(15 downto 8),
      \S_SAMPLE_COUNTER_reg[24]_0\(7 downto 0) => SAMPLE_COUNTER(23 downto 16),
      \S_SAMPLE_COUNTER_reg[31]_0\(6 downto 0) => SAMPLE_COUNTER(30 downto 24),
      \S_SAMPLE_TIME_reg[30]_0\(0) => S_SAMPLE_TIME,
      \S_SAMPLE_TIME_reg[30]_1\(30 downto 0) => S_ADC_CONV_VALUE(30 downto 0),
      S_SCLK => S_SCLK,
      S_SPI_BUSY => S_SPI_BUSY,
      S_SPI_ENABLE_reg_0 => \GEN_ADC_CONT[0].inst_adc_n_9\,
      S_SPI_ENABLE_reg_1 => S_SPI_ENABLE_i_1_n_0,
      s00_axi_aclk => s00_axi_aclk,
      s00_axi_aresetn => s00_axi_aresetn
    );
RAW_VALID_i_1: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FBFF0055"
    )
        port map (
      I0 => \GEN_ADC_CONT[0].inst_adc_n_4\,
      I1 => curstate_0(0),
      I2 => curstate_0(1),
      I3 => \GEN_ADC_CONT[0].inst_adc_n_10\,
      I4 => \^raw_valid\(0),
      O => RAW_VALID_i_1_n_0
    );
\S_ADC_CR_IN_reg[2]\: unisim.vcomponents.FDSE
     port map (
      C => s00_axi_aclk,
      CE => '1',
      D => ADC_LTC2311_v3_0_S00_AXI_inst_n_30,
      Q => P_ADC_CR_IN(2),
      S => \raw_to_si/RSTD\
    );
\S_ADC_CR_IN_reg[4]\: unisim.vcomponents.FDSE
     port map (
      C => s00_axi_aclk,
      CE => '1',
      D => S_SET_CONVERSION,
      Q => P_ADC_CR_IN(4),
      S => \raw_to_si/RSTD\
    );
\S_ADC_SPI_CR_IN[5]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"C4"
    )
        port map (
      I0 => nxtstate(0),
      I1 => nxtstate(1),
      I2 => \S_ADC_SPI_CR_IN_reg_n_0_[5]\,
      O => \S_ADC_SPI_CR_IN[5]_i_1_n_0\
    );
\S_ADC_SPI_CR_IN_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => ADC_LTC2311_v3_0_S00_AXI_inst_n_131,
      D => ADC_LTC2311_v3_0_S00_AXI_inst_n_33,
      Q => \S_ADC_SPI_CR_IN_reg_n_0_[1]\,
      R => '0'
    );
\S_ADC_SPI_CR_IN_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => ADC_LTC2311_v3_0_S00_AXI_inst_n_131,
      D => ADC_LTC2311_v3_0_S00_AXI_inst_n_32,
      Q => \S_ADC_SPI_CR_IN_reg_n_0_[3]\,
      R => '0'
    );
\S_ADC_SPI_CR_IN_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => '1',
      D => \S_ADC_SPI_CR_IN[5]_i_1_n_0\,
      Q => \S_ADC_SPI_CR_IN_reg_n_0_[5]\,
      R => \raw_to_si/RSTD\
    );
S_DUMMY_SAMPLE_i_1: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFDF0010"
    )
        port map (
      I0 => curstate_0(1),
      I1 => curstate_0(0),
      I2 => \GEN_ADC_CONT[0].inst_adc_n_4\,
      I3 => \GEN_ADC_CONT[0].inst_adc_n_10\,
      I4 => S_DUMMY_SAMPLE,
      O => S_DUMMY_SAMPLE_i_1_n_0
    );
\S_ENABLE_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => '1',
      D => ADC_LTC2311_v3_0_S00_AXI_inst_n_26,
      Q => ENABLE,
      R => \raw_to_si/RSTD\
    );
S_MANUAL_i_1: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FF8FFFFF00800000"
    )
        port map (
      I0 => MANUAL,
      I1 => \GEN_ADC_CONT[0].inst_adc_n_10\,
      I2 => \GEN_ADC_CONT[0].inst_adc_n_4\,
      I3 => S_ADC_CR(3),
      I4 => s00_axi_aresetn,
      I5 => \GEN_ADC_CONT[0].inst_adc_n_8\,
      O => S_MANUAL_i_1_n_0
    );
\S_SCLK_IN_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_SCLK_IN,
      D => ADC_LTC2311_v3_0_S00_AXI_inst_n_32,
      Q => SCLK_IN,
      R => '0'
    );
\S_SET_CONVERSION_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => '1',
      D => ADC_LTC2311_v3_0_S00_AXI_inst_n_134,
      Q => SET_CONVERSION,
      R => ADC_LTC2311_v3_0_S00_AXI_inst_n_7
    );
\S_SET_OFFSET_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => '1',
      D => ADC_LTC2311_v3_0_S00_AXI_inst_n_135,
      Q => SET_OFFSET,
      R => ADC_LTC2311_v3_0_S00_AXI_inst_n_7
    );
\S_SET_SAMPLES_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => '1',
      D => ADC_LTC2311_v3_0_S00_AXI_inst_n_130,
      Q => SET_SAMPLES,
      R => '0'
    );
\S_SET_SAMPLE_TIME_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => '1',
      D => ADC_LTC2311_v3_0_S00_AXI_inst_n_29,
      Q => SET_SAMPLE_TIME,
      R => '0'
    );
S_SPI_ENABLE_i_1: unisim.vcomponents.LUT6
    generic map(
      INIT => X"22F2F2F222020202"
    )
        port map (
      I0 => curstate_0(0),
      I1 => curstate_0(1),
      I2 => \GEN_ADC_CONT[0].inst_adc_n_14\,
      I3 => \GEN_ADC_CONT[0].inst_adc_n_15\,
      I4 => S_SPI_BUSY,
      I5 => \GEN_ADC_CONT[0].inst_adc_n_9\,
      O => S_SPI_ENABLE_i_1_n_0
    );
\S_SPI_MANUAL_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => '1',
      D => S_SS_IN_N,
      Q => MANUAL,
      R => \raw_to_si/RSTD\
    );
\S_SS_IN_N_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => S_SCLK_IN,
      D => ADC_LTC2311_v3_0_S00_AXI_inst_n_33,
      Q => SS_IN_N,
      R => '0'
    );
\S_TRIGGER_CNV_PIPE_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => s00_axi_aclk,
      CE => '1',
      D => TRIGGER_CNV(0),
      Q => S_TRIGGER_CNV_PIPE,
      R => \raw_to_si/RSTD\
    );
\curstate_reg[0]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s00_axi_aclk,
      CE => '1',
      D => nxtstate(0),
      Q => curstate(0),
      R => \raw_to_si/RSTD\
    );
\curstate_reg[1]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s00_axi_aclk,
      CE => '1',
      D => nxtstate(1),
      Q => curstate(1),
      R => \raw_to_si/RSTD\
    );
\gen_diff.gen_diff1[0].OBUFDS_inst\: unisim.vcomponents.OBUFDS
    generic map(
      IOSTANDARD => "DEFAULT"
    )
        port map (
      I => S_SCLK,
      O => SCLK_DIFF(0),
      OB => SCLK_DIFF(1)
    );
\gen_diff.gen_diff1[0].gen_diff2[0].IBUFDS_inst\: unisim.vcomponents.IBUFDS
    generic map(
      IOSTANDARD => "DEFAULT"
    )
        port map (
      I => MISO_DIFF(0),
      IB => MISO_DIFF(1),
      O => S_MISO(0)
    );
\gen_diff.gen_diff1[0].gen_diff2[1].IBUFDS_inst\: unisim.vcomponents.IBUFDS
    generic map(
      IOSTANDARD => "DEFAULT"
    )
        port map (
      I => MISO_DIFF(2),
      IB => MISO_DIFF(3),
      O => S_MISO(1)
    );
\gen_diff.gen_diff1[0].gen_diff2[2].IBUFDS_inst\: unisim.vcomponents.IBUFDS
    generic map(
      IOSTANDARD => "DEFAULT"
    )
        port map (
      I => MISO_DIFF(4),
      IB => MISO_DIFF(5),
      O => S_MISO(2)
    );
\gen_diff.gen_diff1[0].gen_diff2[3].IBUFDS_inst\: unisim.vcomponents.IBUFDS
    generic map(
      IOSTANDARD => "DEFAULT"
    )
        port map (
      I => MISO_DIFF(6),
      IB => MISO_DIFF(7),
      O => S_MISO(3)
    );
\gen_diff.gen_diff1[0].gen_diff2[4].IBUFDS_inst\: unisim.vcomponents.IBUFDS
    generic map(
      IOSTANDARD => "DEFAULT"
    )
        port map (
      I => MISO_DIFF(8),
      IB => MISO_DIFF(9),
      O => S_MISO(4)
    );
\gen_diff.gen_diff1[0].gen_diff2[5].IBUFDS_inst\: unisim.vcomponents.IBUFDS
    generic map(
      IOSTANDARD => "DEFAULT"
    )
        port map (
      I => MISO_DIFF(10),
      IB => MISO_DIFF(11),
      O => S_MISO(5)
    );
\gen_diff.gen_diff1[0].gen_diff2[6].IBUFDS_inst\: unisim.vcomponents.IBUFDS
    generic map(
      IOSTANDARD => "DEFAULT"
    )
        port map (
      I => MISO_DIFF(12),
      IB => MISO_DIFF(13),
      O => S_MISO(6)
    );
\gen_diff.gen_diff1[0].gen_diff2[7].IBUFDS_inst\: unisim.vcomponents.IBUFDS
    generic map(
      IOSTANDARD => "DEFAULT"
    )
        port map (
      I => MISO_DIFF(14),
      IB => MISO_DIFF(15),
      O => S_MISO(7)
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity zusys_A3_ADC_LTC2311_0 is
  port (
    RAW_VALUE : out STD_LOGIC_VECTOR ( 127 downto 0 );
    RAW_VALID : out STD_LOGIC_VECTOR ( 0 to 0 );
    SI_VALUE : out STD_LOGIC_VECTOR ( 279 downto 0 );
    SI_VALID : out STD_LOGIC_VECTOR ( 0 to 0 );
    TRIGGER_CNV : in STD_LOGIC_VECTOR ( 0 to 0 );
    SAMPLE_COUNTER : out STD_LOGIC_VECTOR ( 31 downto 0 );
    SS_N : out STD_LOGIC_VECTOR ( 0 to 0 );
    SCLK_DIFF : out STD_LOGIC_VECTOR ( 1 downto 0 );
    MISO_DIFF : in STD_LOGIC_VECTOR ( 15 downto 0 );
    s00_axi_aclk : in STD_LOGIC;
    s00_axi_aresetn : in STD_LOGIC;
    s00_axi_awaddr : in STD_LOGIC_VECTOR ( 5 downto 0 );
    s00_axi_awprot : in STD_LOGIC_VECTOR ( 2 downto 0 );
    s00_axi_awvalid : in STD_LOGIC;
    s00_axi_awready : out STD_LOGIC;
    s00_axi_wdata : in STD_LOGIC_VECTOR ( 31 downto 0 );
    s00_axi_wstrb : in STD_LOGIC_VECTOR ( 3 downto 0 );
    s00_axi_wvalid : in STD_LOGIC;
    s00_axi_wready : out STD_LOGIC;
    s00_axi_bresp : out STD_LOGIC_VECTOR ( 1 downto 0 );
    s00_axi_bvalid : out STD_LOGIC;
    s00_axi_bready : in STD_LOGIC;
    s00_axi_araddr : in STD_LOGIC_VECTOR ( 5 downto 0 );
    s00_axi_arprot : in STD_LOGIC_VECTOR ( 2 downto 0 );
    s00_axi_arvalid : in STD_LOGIC;
    s00_axi_arready : out STD_LOGIC;
    s00_axi_rdata : out STD_LOGIC_VECTOR ( 31 downto 0 );
    s00_axi_rresp : out STD_LOGIC_VECTOR ( 1 downto 0 );
    s00_axi_rvalid : out STD_LOGIC;
    s00_axi_rready : in STD_LOGIC
  );
  attribute NotValidForBitStream : boolean;
  attribute NotValidForBitStream of zusys_A3_ADC_LTC2311_0 : entity is true;
  attribute CHECK_LICENSE_TYPE : string;
  attribute CHECK_LICENSE_TYPE of zusys_A3_ADC_LTC2311_0 : entity is "zusys_A3_ADC_LTC2311_0,ADC_LTC2311_v3_0,{}";
  attribute downgradeipidentifiedwarnings : string;
  attribute downgradeipidentifiedwarnings of zusys_A3_ADC_LTC2311_0 : entity is "yes";
  attribute x_core_info : string;
  attribute x_core_info of zusys_A3_ADC_LTC2311_0 : entity is "ADC_LTC2311_v3_0,Vivado 2020.1.1";
end zusys_A3_ADC_LTC2311_0;

architecture STRUCTURE of zusys_A3_ADC_LTC2311_0 is
  signal \<const0>\ : STD_LOGIC;
  attribute x_interface_info : string;
  attribute x_interface_info of s00_axi_aclk : signal is "xilinx.com:signal:clock:1.0 S00_AXI_CLK CLK";
  attribute x_interface_parameter : string;
  attribute x_interface_parameter of s00_axi_aclk : signal is "XIL_INTERFACENAME S00_AXI_CLK, ASSOCIATED_BUSIF S00_AXI, ASSOCIATED_RESET s00_axi_aresetn, FREQ_HZ 100000000, FREQ_TOLERANCE_HZ 0, PHASE 0.000, CLK_DOMAIN zusys_zynq_ultra_ps_e_0_0_pl_clk0, INSERT_VIP 0";
  attribute x_interface_info of s00_axi_aresetn : signal is "xilinx.com:signal:reset:1.0 S00_AXI_RST RST";
  attribute x_interface_parameter of s00_axi_aresetn : signal is "XIL_INTERFACENAME S00_AXI_RST, POLARITY ACTIVE_LOW, INSERT_VIP 0";
  attribute x_interface_info of s00_axi_arready : signal is "xilinx.com:interface:aximm:1.0 S00_AXI ARREADY";
  attribute x_interface_info of s00_axi_arvalid : signal is "xilinx.com:interface:aximm:1.0 S00_AXI ARVALID";
  attribute x_interface_info of s00_axi_awready : signal is "xilinx.com:interface:aximm:1.0 S00_AXI AWREADY";
  attribute x_interface_info of s00_axi_awvalid : signal is "xilinx.com:interface:aximm:1.0 S00_AXI AWVALID";
  attribute x_interface_info of s00_axi_bready : signal is "xilinx.com:interface:aximm:1.0 S00_AXI BREADY";
  attribute x_interface_info of s00_axi_bvalid : signal is "xilinx.com:interface:aximm:1.0 S00_AXI BVALID";
  attribute x_interface_info of s00_axi_rready : signal is "xilinx.com:interface:aximm:1.0 S00_AXI RREADY";
  attribute x_interface_info of s00_axi_rvalid : signal is "xilinx.com:interface:aximm:1.0 S00_AXI RVALID";
  attribute x_interface_info of s00_axi_wready : signal is "xilinx.com:interface:aximm:1.0 S00_AXI WREADY";
  attribute x_interface_info of s00_axi_wvalid : signal is "xilinx.com:interface:aximm:1.0 S00_AXI WVALID";
  attribute x_interface_info of s00_axi_araddr : signal is "xilinx.com:interface:aximm:1.0 S00_AXI ARADDR";
  attribute x_interface_info of s00_axi_arprot : signal is "xilinx.com:interface:aximm:1.0 S00_AXI ARPROT";
  attribute x_interface_info of s00_axi_awaddr : signal is "xilinx.com:interface:aximm:1.0 S00_AXI AWADDR";
  attribute x_interface_parameter of s00_axi_awaddr : signal is "XIL_INTERFACENAME S00_AXI, WIZ_DATA_WIDTH 32, WIZ_NUM_REG 4, SUPPORTS_NARROW_BURST 0, DATA_WIDTH 32, PROTOCOL AXI4LITE, FREQ_HZ 100000000, ID_WIDTH 0, ADDR_WIDTH 6, AWUSER_WIDTH 0, ARUSER_WIDTH 0, WUSER_WIDTH 0, RUSER_WIDTH 0, BUSER_WIDTH 0, READ_WRITE_MODE READ_WRITE, HAS_BURST 0, HAS_LOCK 0, HAS_PROT 1, HAS_CACHE 0, HAS_QOS 0, HAS_REGION 0, HAS_WSTRB 1, HAS_BRESP 1, HAS_RRESP 1, NUM_READ_OUTSTANDING 8, NUM_WRITE_OUTSTANDING 8, MAX_BURST_LENGTH 1, PHASE 0.000, CLK_DOMAIN zusys_zynq_ultra_ps_e_0_0_pl_clk0, NUM_READ_THREADS 1, NUM_WRITE_THREADS 1, RUSER_BITS_PER_BYTE 0, WUSER_BITS_PER_BYTE 0, INSERT_VIP 0";
  attribute x_interface_info of s00_axi_awprot : signal is "xilinx.com:interface:aximm:1.0 S00_AXI AWPROT";
  attribute x_interface_info of s00_axi_bresp : signal is "xilinx.com:interface:aximm:1.0 S00_AXI BRESP";
  attribute x_interface_info of s00_axi_rdata : signal is "xilinx.com:interface:aximm:1.0 S00_AXI RDATA";
  attribute x_interface_info of s00_axi_rresp : signal is "xilinx.com:interface:aximm:1.0 S00_AXI RRESP";
  attribute x_interface_info of s00_axi_wdata : signal is "xilinx.com:interface:aximm:1.0 S00_AXI WDATA";
  attribute x_interface_info of s00_axi_wstrb : signal is "xilinx.com:interface:aximm:1.0 S00_AXI WSTRB";
begin
  s00_axi_bresp(1) <= \<const0>\;
  s00_axi_bresp(0) <= \<const0>\;
  s00_axi_rresp(1) <= \<const0>\;
  s00_axi_rresp(0) <= \<const0>\;
GND: unisim.vcomponents.GND
     port map (
      G => \<const0>\
    );
U0: entity work.zusys_A3_ADC_LTC2311_0_ADC_LTC2311_v3_0
     port map (
      MISO_DIFF(15 downto 0) => MISO_DIFF(15 downto 0),
      RAW_VALID(0) => RAW_VALID(0),
      RAW_VALUE(127 downto 0) => RAW_VALUE(127 downto 0),
      SAMPLE_COUNTER(30 downto 0) => SAMPLE_COUNTER(31 downto 1),
      SCLK_DIFF(1 downto 0) => SCLK_DIFF(1 downto 0),
      SI_VALID(0) => SI_VALID(0),
      SI_VALUE(279 downto 0) => SI_VALUE(279 downto 0),
      SS_N(0) => SS_N(0),
      \S_SAMPLE_COUNTER_reg[0]\ => SAMPLE_COUNTER(0),
      TRIGGER_CNV(0) => TRIGGER_CNV(0),
      s00_axi_aclk => s00_axi_aclk,
      s00_axi_araddr(3 downto 0) => s00_axi_araddr(5 downto 2),
      s00_axi_aresetn => s00_axi_aresetn,
      s00_axi_arready => s00_axi_arready,
      s00_axi_arvalid => s00_axi_arvalid,
      s00_axi_awaddr(3 downto 0) => s00_axi_awaddr(5 downto 2),
      s00_axi_awready => s00_axi_awready,
      s00_axi_awvalid => s00_axi_awvalid,
      s00_axi_bready => s00_axi_bready,
      s00_axi_bvalid => s00_axi_bvalid,
      s00_axi_rdata(31 downto 0) => s00_axi_rdata(31 downto 0),
      s00_axi_rready => s00_axi_rready,
      s00_axi_rvalid => s00_axi_rvalid,
      s00_axi_wdata(31 downto 0) => s00_axi_wdata(31 downto 0),
      s00_axi_wready => s00_axi_wready,
      s00_axi_wstrb(3 downto 0) => s00_axi_wstrb(3 downto 0),
      s00_axi_wvalid => s00_axi_wvalid
    );
end STRUCTURE;
