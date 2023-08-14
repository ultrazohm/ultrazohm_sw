-- Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
-- --------------------------------------------------------------------------------
-- Tool Version: Vivado v.2020.1.1 (win64) Build 2960000 Wed Aug  5 22:57:20 MDT 2020
-- Date        : Fri Jan 28 14:45:37 2022
-- Host        : enc177112 running 64-bit major release  (build 9200)
-- Command     : write_vhdl -force -mode funcsim
--               c:/GIT/UltraZohm/software/ultrazohm_sw_develop/vivado/zusys/ip/zusys_mux_axi_ip_1_0/zusys_mux_axi_ip_1_0_sim_netlist.vhdl
-- Design      : zusys_mux_axi_ip_1_0
-- Purpose     : This VHDL netlist is a functional simulation representation of the design and should not be modified or
--               synthesized. This netlist cannot be used for SDF annotated simulation.
-- Device      : xczu9eg-ffvc900-1-e
-- --------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity zusys_mux_axi_ip_1_0_mux_axi_ip_addr_decoder is
  port (
    read_reg_ip_timestamp : out STD_LOGIC_VECTOR ( 0 to 0 );
    data_reg_axi_enable_1_1_reg_0 : out STD_LOGIC;
    S : out STD_LOGIC_VECTOR ( 7 downto 0 );
    Q : out STD_LOGIC_VECTOR ( 20 downto 0 );
    \data_reg_select_n_th_adc_interrupt_1_1_reg[30]_0\ : out STD_LOGIC_VECTOR ( 7 downto 0 );
    D : out STD_LOGIC_VECTOR ( 16 downto 0 );
    \data_reg_select_AXI_1_1_reg[30]_0\ : out STD_LOGIC_VECTOR ( 17 downto 0 );
    interrupt_out_isr : out STD_LOGIC_VECTOR ( 7 downto 0 );
    interrupt_out_adc : out STD_LOGIC;
    Detect_Rise_Positive_out1 : out STD_LOGIC;
    E : out STD_LOGIC_VECTOR ( 0 to 0 );
    data_reg_axi_enable_1_1_reg_1 : out STD_LOGIC_VECTOR ( 0 to 0 );
    SR : in STD_LOGIC_VECTOR ( 0 to 0 );
    AXI4_Lite_ACLK : in STD_LOGIC;
    data_reg_axi_enable_1_1_reg_2 : in STD_LOGIC;
    \AXI4_Lite_RDATA_tmp_reg[1]\ : in STD_LOGIC;
    \AXI4_Lite_RDATA_tmp_reg[1]_0\ : in STD_LOGIC;
    U_k_1 : in STD_LOGIC;
    U_k : in STD_LOGIC;
    U_k_1_0 : in STD_LOGIC;
    interrupts_in : in STD_LOGIC_VECTOR ( 7 downto 0 );
    PipelineDelay_out1 : in STD_LOGIC;
    CO : in STD_LOGIC_VECTOR ( 0 to 0 );
    \HDL_Counter_out10_inferred__0/i__carry\ : in STD_LOGIC_VECTOR ( 7 downto 0 );
    \data_reg_select_AXI_1_1_reg[31]_0\ : in STD_LOGIC_VECTOR ( 0 to 0 );
    \data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0\ : in STD_LOGIC_VECTOR ( 31 downto 0 );
    \data_reg_select_n_th_adc_interrupt_1_1_reg[31]_1\ : in STD_LOGIC_VECTOR ( 0 to 0 )
  );
  attribute ORIG_REF_NAME : string;
  attribute ORIG_REF_NAME of zusys_mux_axi_ip_1_0_mux_axi_ip_addr_decoder : entity is "mux_axi_ip_addr_decoder";
end zusys_mux_axi_ip_1_0_mux_axi_ip_addr_decoder;

architecture STRUCTURE of zusys_mux_axi_ip_1_0_mux_axi_ip_addr_decoder is
  signal \^q\ : STD_LOGIC_VECTOR ( 20 downto 0 );
  signal \^data_reg_axi_enable_1_1_reg_0\ : STD_LOGIC;
  signal \^data_reg_select_axi_1_1_reg[30]_0\ : STD_LOGIC_VECTOR ( 17 downto 0 );
  signal interrupt_out_adc_INST_0_i_10_n_0 : STD_LOGIC;
  signal interrupt_out_adc_INST_0_i_11_n_0 : STD_LOGIC;
  signal interrupt_out_adc_INST_0_i_1_n_0 : STD_LOGIC;
  signal interrupt_out_adc_INST_0_i_2_n_0 : STD_LOGIC;
  signal interrupt_out_adc_INST_0_i_3_n_0 : STD_LOGIC;
  signal interrupt_out_adc_INST_0_i_4_n_0 : STD_LOGIC;
  signal interrupt_out_adc_INST_0_i_5_n_0 : STD_LOGIC;
  signal interrupt_out_adc_INST_0_i_6_n_0 : STD_LOGIC;
  signal interrupt_out_adc_INST_0_i_7_n_0 : STD_LOGIC;
  signal interrupt_out_adc_INST_0_i_8_n_0 : STD_LOGIC;
  signal interrupt_out_adc_INST_0_i_9_n_0 : STD_LOGIC;
  signal n_th_adc_interrupt : STD_LOGIC_VECTOR ( 31 downto 8 );
  signal p_0_in : STD_LOGIC_VECTOR ( 27 downto 0 );
  attribute SOFT_HLUTNM : string;
  attribute SOFT_HLUTNM of \HDL_Counter_out1[7]_i_1\ : label is "soft_lutpair1";
  attribute SOFT_HLUTNM of \HDL_Counter_out1[7]_i_2\ : label is "soft_lutpair1";
  attribute SOFT_HLUTNM of PipelineDelay_out1_i_1 : label is "soft_lutpair0";
  attribute SOFT_HLUTNM of interrupt_out_adc_INST_0 : label is "soft_lutpair0";
begin
  Q(20 downto 0) <= \^q\(20 downto 0);
  data_reg_axi_enable_1_1_reg_0 <= \^data_reg_axi_enable_1_1_reg_0\;
  \data_reg_select_AXI_1_1_reg[30]_0\(17 downto 0) <= \^data_reg_select_axi_1_1_reg[30]_0\(17 downto 0);
\AXI4_Lite_RDATA_tmp[11]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"F888"
    )
        port map (
      I0 => p_0_in(20),
      I1 => \AXI4_Lite_RDATA_tmp_reg[1]\,
      I2 => n_th_adc_interrupt(11),
      I3 => \AXI4_Lite_RDATA_tmp_reg[1]_0\,
      O => D(8)
    );
\AXI4_Lite_RDATA_tmp[12]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"F888"
    )
        port map (
      I0 => p_0_in(19),
      I1 => \AXI4_Lite_RDATA_tmp_reg[1]\,
      I2 => n_th_adc_interrupt(12),
      I3 => \AXI4_Lite_RDATA_tmp_reg[1]_0\,
      O => D(9)
    );
\AXI4_Lite_RDATA_tmp[13]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"F888"
    )
        port map (
      I0 => p_0_in(18),
      I1 => \AXI4_Lite_RDATA_tmp_reg[1]\,
      I2 => n_th_adc_interrupt(13),
      I3 => \AXI4_Lite_RDATA_tmp_reg[1]_0\,
      O => D(10)
    );
\AXI4_Lite_RDATA_tmp[15]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"F888"
    )
        port map (
      I0 => p_0_in(16),
      I1 => \AXI4_Lite_RDATA_tmp_reg[1]\,
      I2 => n_th_adc_interrupt(15),
      I3 => \AXI4_Lite_RDATA_tmp_reg[1]_0\,
      O => D(11)
    );
\AXI4_Lite_RDATA_tmp[19]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"F888"
    )
        port map (
      I0 => p_0_in(12),
      I1 => \AXI4_Lite_RDATA_tmp_reg[1]\,
      I2 => n_th_adc_interrupt(19),
      I3 => \AXI4_Lite_RDATA_tmp_reg[1]_0\,
      O => D(12)
    );
\AXI4_Lite_RDATA_tmp[1]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"F888"
    )
        port map (
      I0 => \^data_reg_select_axi_1_1_reg[30]_0\(1),
      I1 => \AXI4_Lite_RDATA_tmp_reg[1]\,
      I2 => \^q\(1),
      I3 => \AXI4_Lite_RDATA_tmp_reg[1]_0\,
      O => D(0)
    );
\AXI4_Lite_RDATA_tmp[20]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"F888"
    )
        port map (
      I0 => p_0_in(11),
      I1 => \AXI4_Lite_RDATA_tmp_reg[1]\,
      I2 => n_th_adc_interrupt(20),
      I3 => \AXI4_Lite_RDATA_tmp_reg[1]_0\,
      O => D(13)
    );
\AXI4_Lite_RDATA_tmp[21]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"F888"
    )
        port map (
      I0 => p_0_in(10),
      I1 => \AXI4_Lite_RDATA_tmp_reg[1]\,
      I2 => n_th_adc_interrupt(21),
      I3 => \AXI4_Lite_RDATA_tmp_reg[1]_0\,
      O => D(14)
    );
\AXI4_Lite_RDATA_tmp[25]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"F888"
    )
        port map (
      I0 => p_0_in(6),
      I1 => \AXI4_Lite_RDATA_tmp_reg[1]\,
      I2 => n_th_adc_interrupt(25),
      I3 => \AXI4_Lite_RDATA_tmp_reg[1]_0\,
      O => D(15)
    );
\AXI4_Lite_RDATA_tmp[2]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"F888"
    )
        port map (
      I0 => \^data_reg_select_axi_1_1_reg[30]_0\(2),
      I1 => \AXI4_Lite_RDATA_tmp_reg[1]\,
      I2 => \^q\(2),
      I3 => \AXI4_Lite_RDATA_tmp_reg[1]_0\,
      O => D(1)
    );
\AXI4_Lite_RDATA_tmp[31]_i_2\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"F888"
    )
        port map (
      I0 => p_0_in(0),
      I1 => \AXI4_Lite_RDATA_tmp_reg[1]\,
      I2 => n_th_adc_interrupt(31),
      I3 => \AXI4_Lite_RDATA_tmp_reg[1]_0\,
      O => D(16)
    );
\AXI4_Lite_RDATA_tmp[3]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"F888"
    )
        port map (
      I0 => \^data_reg_select_axi_1_1_reg[30]_0\(3),
      I1 => \AXI4_Lite_RDATA_tmp_reg[1]\,
      I2 => \^q\(3),
      I3 => \AXI4_Lite_RDATA_tmp_reg[1]_0\,
      O => D(2)
    );
\AXI4_Lite_RDATA_tmp[4]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"F888"
    )
        port map (
      I0 => p_0_in(27),
      I1 => \AXI4_Lite_RDATA_tmp_reg[1]\,
      I2 => \^q\(4),
      I3 => \AXI4_Lite_RDATA_tmp_reg[1]_0\,
      O => D(3)
    );
\AXI4_Lite_RDATA_tmp[6]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"F888"
    )
        port map (
      I0 => p_0_in(25),
      I1 => \AXI4_Lite_RDATA_tmp_reg[1]\,
      I2 => \^q\(6),
      I3 => \AXI4_Lite_RDATA_tmp_reg[1]_0\,
      O => D(4)
    );
\AXI4_Lite_RDATA_tmp[7]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"F888"
    )
        port map (
      I0 => p_0_in(24),
      I1 => \AXI4_Lite_RDATA_tmp_reg[1]\,
      I2 => \^q\(7),
      I3 => \AXI4_Lite_RDATA_tmp_reg[1]_0\,
      O => D(5)
    );
\AXI4_Lite_RDATA_tmp[8]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"F888"
    )
        port map (
      I0 => p_0_in(23),
      I1 => \AXI4_Lite_RDATA_tmp_reg[1]\,
      I2 => n_th_adc_interrupt(8),
      I3 => \AXI4_Lite_RDATA_tmp_reg[1]_0\,
      O => D(6)
    );
\AXI4_Lite_RDATA_tmp[9]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"F888"
    )
        port map (
      I0 => p_0_in(22),
      I1 => \AXI4_Lite_RDATA_tmp_reg[1]\,
      I2 => n_th_adc_interrupt(9),
      I3 => \AXI4_Lite_RDATA_tmp_reg[1]_0\,
      O => D(7)
    );
\HDL_Counter_out1[7]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"F8"
    )
        port map (
      I0 => \^data_reg_axi_enable_1_1_reg_0\,
      I1 => CO(0),
      I2 => SR(0),
      O => data_reg_axi_enable_1_1_reg_1(0)
    );
\HDL_Counter_out1[7]_i_2\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"8"
    )
        port map (
      I0 => \^data_reg_axi_enable_1_1_reg_0\,
      I1 => PipelineDelay_out1,
      O => E(0)
    );
PipelineDelay_out1_i_1: unisim.vcomponents.LUT3
    generic map(
      INIT => X"40"
    )
        port map (
      I0 => U_k_1_0,
      I1 => interrupt_out_adc_INST_0_i_2_n_0,
      I2 => interrupt_out_adc_INST_0_i_1_n_0,
      O => Detect_Rise_Positive_out1
    );
data_reg_axi_enable_1_1_reg: unisim.vcomponents.FDSE
     port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => data_reg_axi_enable_1_1_reg_2,
      Q => \^data_reg_axi_enable_1_1_reg_0\,
      S => SR(0)
    );
\data_reg_select_AXI_1_1_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \data_reg_select_AXI_1_1_reg[31]_0\(0),
      D => \data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0\(0),
      Q => \^data_reg_select_axi_1_1_reg[30]_0\(0),
      R => SR(0)
    );
\data_reg_select_AXI_1_1_reg[10]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \data_reg_select_AXI_1_1_reg[31]_0\(0),
      D => \data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0\(10),
      Q => \^data_reg_select_axi_1_1_reg[30]_0\(5),
      R => SR(0)
    );
\data_reg_select_AXI_1_1_reg[11]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \data_reg_select_AXI_1_1_reg[31]_0\(0),
      D => \data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0\(11),
      Q => p_0_in(20),
      R => SR(0)
    );
\data_reg_select_AXI_1_1_reg[12]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \data_reg_select_AXI_1_1_reg[31]_0\(0),
      D => \data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0\(12),
      Q => p_0_in(19),
      R => SR(0)
    );
\data_reg_select_AXI_1_1_reg[13]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \data_reg_select_AXI_1_1_reg[31]_0\(0),
      D => \data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0\(13),
      Q => p_0_in(18),
      R => SR(0)
    );
\data_reg_select_AXI_1_1_reg[14]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \data_reg_select_AXI_1_1_reg[31]_0\(0),
      D => \data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0\(14),
      Q => \^data_reg_select_axi_1_1_reg[30]_0\(6),
      R => SR(0)
    );
\data_reg_select_AXI_1_1_reg[15]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \data_reg_select_AXI_1_1_reg[31]_0\(0),
      D => \data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0\(15),
      Q => p_0_in(16),
      R => SR(0)
    );
\data_reg_select_AXI_1_1_reg[16]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \data_reg_select_AXI_1_1_reg[31]_0\(0),
      D => \data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0\(16),
      Q => \^data_reg_select_axi_1_1_reg[30]_0\(7),
      R => SR(0)
    );
\data_reg_select_AXI_1_1_reg[17]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \data_reg_select_AXI_1_1_reg[31]_0\(0),
      D => \data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0\(17),
      Q => \^data_reg_select_axi_1_1_reg[30]_0\(8),
      R => SR(0)
    );
\data_reg_select_AXI_1_1_reg[18]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \data_reg_select_AXI_1_1_reg[31]_0\(0),
      D => \data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0\(18),
      Q => \^data_reg_select_axi_1_1_reg[30]_0\(9),
      R => SR(0)
    );
\data_reg_select_AXI_1_1_reg[19]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \data_reg_select_AXI_1_1_reg[31]_0\(0),
      D => \data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0\(19),
      Q => p_0_in(12),
      R => SR(0)
    );
\data_reg_select_AXI_1_1_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \data_reg_select_AXI_1_1_reg[31]_0\(0),
      D => \data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0\(1),
      Q => \^data_reg_select_axi_1_1_reg[30]_0\(1),
      R => SR(0)
    );
\data_reg_select_AXI_1_1_reg[20]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \data_reg_select_AXI_1_1_reg[31]_0\(0),
      D => \data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0\(20),
      Q => p_0_in(11),
      R => SR(0)
    );
\data_reg_select_AXI_1_1_reg[21]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \data_reg_select_AXI_1_1_reg[31]_0\(0),
      D => \data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0\(21),
      Q => p_0_in(10),
      R => SR(0)
    );
\data_reg_select_AXI_1_1_reg[22]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \data_reg_select_AXI_1_1_reg[31]_0\(0),
      D => \data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0\(22),
      Q => \^data_reg_select_axi_1_1_reg[30]_0\(10),
      R => SR(0)
    );
\data_reg_select_AXI_1_1_reg[23]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \data_reg_select_AXI_1_1_reg[31]_0\(0),
      D => \data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0\(23),
      Q => \^data_reg_select_axi_1_1_reg[30]_0\(11),
      R => SR(0)
    );
\data_reg_select_AXI_1_1_reg[24]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \data_reg_select_AXI_1_1_reg[31]_0\(0),
      D => \data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0\(24),
      Q => \^data_reg_select_axi_1_1_reg[30]_0\(12),
      R => SR(0)
    );
\data_reg_select_AXI_1_1_reg[25]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \data_reg_select_AXI_1_1_reg[31]_0\(0),
      D => \data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0\(25),
      Q => p_0_in(6),
      R => SR(0)
    );
\data_reg_select_AXI_1_1_reg[26]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \data_reg_select_AXI_1_1_reg[31]_0\(0),
      D => \data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0\(26),
      Q => \^data_reg_select_axi_1_1_reg[30]_0\(13),
      R => SR(0)
    );
\data_reg_select_AXI_1_1_reg[27]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \data_reg_select_AXI_1_1_reg[31]_0\(0),
      D => \data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0\(27),
      Q => \^data_reg_select_axi_1_1_reg[30]_0\(14),
      R => SR(0)
    );
\data_reg_select_AXI_1_1_reg[28]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \data_reg_select_AXI_1_1_reg[31]_0\(0),
      D => \data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0\(28),
      Q => \^data_reg_select_axi_1_1_reg[30]_0\(15),
      R => SR(0)
    );
\data_reg_select_AXI_1_1_reg[29]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \data_reg_select_AXI_1_1_reg[31]_0\(0),
      D => \data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0\(29),
      Q => \^data_reg_select_axi_1_1_reg[30]_0\(16),
      R => SR(0)
    );
\data_reg_select_AXI_1_1_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \data_reg_select_AXI_1_1_reg[31]_0\(0),
      D => \data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0\(2),
      Q => \^data_reg_select_axi_1_1_reg[30]_0\(2),
      R => SR(0)
    );
\data_reg_select_AXI_1_1_reg[30]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \data_reg_select_AXI_1_1_reg[31]_0\(0),
      D => \data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0\(30),
      Q => \^data_reg_select_axi_1_1_reg[30]_0\(17),
      R => SR(0)
    );
\data_reg_select_AXI_1_1_reg[31]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \data_reg_select_AXI_1_1_reg[31]_0\(0),
      D => \data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0\(31),
      Q => p_0_in(0),
      R => SR(0)
    );
\data_reg_select_AXI_1_1_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \data_reg_select_AXI_1_1_reg[31]_0\(0),
      D => \data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0\(3),
      Q => \^data_reg_select_axi_1_1_reg[30]_0\(3),
      R => SR(0)
    );
\data_reg_select_AXI_1_1_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \data_reg_select_AXI_1_1_reg[31]_0\(0),
      D => \data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0\(4),
      Q => p_0_in(27),
      R => SR(0)
    );
\data_reg_select_AXI_1_1_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \data_reg_select_AXI_1_1_reg[31]_0\(0),
      D => \data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0\(5),
      Q => \^data_reg_select_axi_1_1_reg[30]_0\(4),
      R => SR(0)
    );
\data_reg_select_AXI_1_1_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \data_reg_select_AXI_1_1_reg[31]_0\(0),
      D => \data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0\(6),
      Q => p_0_in(25),
      R => SR(0)
    );
\data_reg_select_AXI_1_1_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \data_reg_select_AXI_1_1_reg[31]_0\(0),
      D => \data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0\(7),
      Q => p_0_in(24),
      R => SR(0)
    );
\data_reg_select_AXI_1_1_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \data_reg_select_AXI_1_1_reg[31]_0\(0),
      D => \data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0\(8),
      Q => p_0_in(23),
      R => SR(0)
    );
\data_reg_select_AXI_1_1_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \data_reg_select_AXI_1_1_reg[31]_0\(0),
      D => \data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0\(9),
      Q => p_0_in(22),
      R => SR(0)
    );
\data_reg_select_n_th_adc_interrupt_1_1_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \data_reg_select_n_th_adc_interrupt_1_1_reg[31]_1\(0),
      D => \data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0\(0),
      Q => \^q\(0),
      R => SR(0)
    );
\data_reg_select_n_th_adc_interrupt_1_1_reg[10]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \data_reg_select_n_th_adc_interrupt_1_1_reg[31]_1\(0),
      D => \data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0\(10),
      Q => \^q\(8),
      R => SR(0)
    );
\data_reg_select_n_th_adc_interrupt_1_1_reg[11]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \data_reg_select_n_th_adc_interrupt_1_1_reg[31]_1\(0),
      D => \data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0\(11),
      Q => n_th_adc_interrupt(11),
      R => SR(0)
    );
\data_reg_select_n_th_adc_interrupt_1_1_reg[12]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \data_reg_select_n_th_adc_interrupt_1_1_reg[31]_1\(0),
      D => \data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0\(12),
      Q => n_th_adc_interrupt(12),
      R => SR(0)
    );
\data_reg_select_n_th_adc_interrupt_1_1_reg[13]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \data_reg_select_n_th_adc_interrupt_1_1_reg[31]_1\(0),
      D => \data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0\(13),
      Q => n_th_adc_interrupt(13),
      R => SR(0)
    );
\data_reg_select_n_th_adc_interrupt_1_1_reg[14]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \data_reg_select_n_th_adc_interrupt_1_1_reg[31]_1\(0),
      D => \data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0\(14),
      Q => \^q\(9),
      R => SR(0)
    );
\data_reg_select_n_th_adc_interrupt_1_1_reg[15]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \data_reg_select_n_th_adc_interrupt_1_1_reg[31]_1\(0),
      D => \data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0\(15),
      Q => n_th_adc_interrupt(15),
      R => SR(0)
    );
\data_reg_select_n_th_adc_interrupt_1_1_reg[16]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \data_reg_select_n_th_adc_interrupt_1_1_reg[31]_1\(0),
      D => \data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0\(16),
      Q => \^q\(10),
      R => SR(0)
    );
\data_reg_select_n_th_adc_interrupt_1_1_reg[17]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \data_reg_select_n_th_adc_interrupt_1_1_reg[31]_1\(0),
      D => \data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0\(17),
      Q => \^q\(11),
      R => SR(0)
    );
\data_reg_select_n_th_adc_interrupt_1_1_reg[18]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \data_reg_select_n_th_adc_interrupt_1_1_reg[31]_1\(0),
      D => \data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0\(18),
      Q => \^q\(12),
      R => SR(0)
    );
\data_reg_select_n_th_adc_interrupt_1_1_reg[19]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \data_reg_select_n_th_adc_interrupt_1_1_reg[31]_1\(0),
      D => \data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0\(19),
      Q => n_th_adc_interrupt(19),
      R => SR(0)
    );
\data_reg_select_n_th_adc_interrupt_1_1_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \data_reg_select_n_th_adc_interrupt_1_1_reg[31]_1\(0),
      D => \data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0\(1),
      Q => \^q\(1),
      R => SR(0)
    );
\data_reg_select_n_th_adc_interrupt_1_1_reg[20]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \data_reg_select_n_th_adc_interrupt_1_1_reg[31]_1\(0),
      D => \data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0\(20),
      Q => n_th_adc_interrupt(20),
      R => SR(0)
    );
\data_reg_select_n_th_adc_interrupt_1_1_reg[21]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \data_reg_select_n_th_adc_interrupt_1_1_reg[31]_1\(0),
      D => \data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0\(21),
      Q => n_th_adc_interrupt(21),
      R => SR(0)
    );
\data_reg_select_n_th_adc_interrupt_1_1_reg[22]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \data_reg_select_n_th_adc_interrupt_1_1_reg[31]_1\(0),
      D => \data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0\(22),
      Q => \^q\(13),
      R => SR(0)
    );
\data_reg_select_n_th_adc_interrupt_1_1_reg[23]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \data_reg_select_n_th_adc_interrupt_1_1_reg[31]_1\(0),
      D => \data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0\(23),
      Q => \^q\(14),
      R => SR(0)
    );
\data_reg_select_n_th_adc_interrupt_1_1_reg[24]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \data_reg_select_n_th_adc_interrupt_1_1_reg[31]_1\(0),
      D => \data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0\(24),
      Q => \^q\(15),
      R => SR(0)
    );
\data_reg_select_n_th_adc_interrupt_1_1_reg[25]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \data_reg_select_n_th_adc_interrupt_1_1_reg[31]_1\(0),
      D => \data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0\(25),
      Q => n_th_adc_interrupt(25),
      R => SR(0)
    );
\data_reg_select_n_th_adc_interrupt_1_1_reg[26]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \data_reg_select_n_th_adc_interrupt_1_1_reg[31]_1\(0),
      D => \data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0\(26),
      Q => \^q\(16),
      R => SR(0)
    );
\data_reg_select_n_th_adc_interrupt_1_1_reg[27]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \data_reg_select_n_th_adc_interrupt_1_1_reg[31]_1\(0),
      D => \data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0\(27),
      Q => \^q\(17),
      R => SR(0)
    );
\data_reg_select_n_th_adc_interrupt_1_1_reg[28]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \data_reg_select_n_th_adc_interrupt_1_1_reg[31]_1\(0),
      D => \data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0\(28),
      Q => \^q\(18),
      R => SR(0)
    );
\data_reg_select_n_th_adc_interrupt_1_1_reg[29]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \data_reg_select_n_th_adc_interrupt_1_1_reg[31]_1\(0),
      D => \data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0\(29),
      Q => \^q\(19),
      R => SR(0)
    );
\data_reg_select_n_th_adc_interrupt_1_1_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \data_reg_select_n_th_adc_interrupt_1_1_reg[31]_1\(0),
      D => \data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0\(2),
      Q => \^q\(2),
      R => SR(0)
    );
\data_reg_select_n_th_adc_interrupt_1_1_reg[30]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \data_reg_select_n_th_adc_interrupt_1_1_reg[31]_1\(0),
      D => \data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0\(30),
      Q => \^q\(20),
      R => SR(0)
    );
\data_reg_select_n_th_adc_interrupt_1_1_reg[31]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \data_reg_select_n_th_adc_interrupt_1_1_reg[31]_1\(0),
      D => \data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0\(31),
      Q => n_th_adc_interrupt(31),
      R => SR(0)
    );
\data_reg_select_n_th_adc_interrupt_1_1_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \data_reg_select_n_th_adc_interrupt_1_1_reg[31]_1\(0),
      D => \data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0\(3),
      Q => \^q\(3),
      R => SR(0)
    );
\data_reg_select_n_th_adc_interrupt_1_1_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \data_reg_select_n_th_adc_interrupt_1_1_reg[31]_1\(0),
      D => \data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0\(4),
      Q => \^q\(4),
      R => SR(0)
    );
\data_reg_select_n_th_adc_interrupt_1_1_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \data_reg_select_n_th_adc_interrupt_1_1_reg[31]_1\(0),
      D => \data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0\(5),
      Q => \^q\(5),
      R => SR(0)
    );
\data_reg_select_n_th_adc_interrupt_1_1_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \data_reg_select_n_th_adc_interrupt_1_1_reg[31]_1\(0),
      D => \data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0\(6),
      Q => \^q\(6),
      R => SR(0)
    );
\data_reg_select_n_th_adc_interrupt_1_1_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \data_reg_select_n_th_adc_interrupt_1_1_reg[31]_1\(0),
      D => \data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0\(7),
      Q => \^q\(7),
      R => SR(0)
    );
\data_reg_select_n_th_adc_interrupt_1_1_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \data_reg_select_n_th_adc_interrupt_1_1_reg[31]_1\(0),
      D => \data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0\(8),
      Q => n_th_adc_interrupt(8),
      R => SR(0)
    );
\data_reg_select_n_th_adc_interrupt_1_1_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \data_reg_select_n_th_adc_interrupt_1_1_reg[31]_1\(0),
      D => \data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0\(9),
      Q => n_th_adc_interrupt(9),
      R => SR(0)
    );
\i__carry__0_i_1\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => \^q\(20),
      I1 => n_th_adc_interrupt(31),
      O => \data_reg_select_n_th_adc_interrupt_1_1_reg[30]_0\(7)
    );
\i__carry__0_i_2\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => \^q\(18),
      I1 => \^q\(19),
      O => \data_reg_select_n_th_adc_interrupt_1_1_reg[30]_0\(6)
    );
\i__carry__0_i_3\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => \^q\(16),
      I1 => \^q\(17),
      O => \data_reg_select_n_th_adc_interrupt_1_1_reg[30]_0\(5)
    );
\i__carry__0_i_4\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => \^q\(15),
      I1 => n_th_adc_interrupt(25),
      O => \data_reg_select_n_th_adc_interrupt_1_1_reg[30]_0\(4)
    );
\i__carry__0_i_5\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => \^q\(13),
      I1 => \^q\(14),
      O => \data_reg_select_n_th_adc_interrupt_1_1_reg[30]_0\(3)
    );
\i__carry__0_i_6\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => n_th_adc_interrupt(20),
      I1 => n_th_adc_interrupt(21),
      O => \data_reg_select_n_th_adc_interrupt_1_1_reg[30]_0\(2)
    );
\i__carry__0_i_7\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => \^q\(12),
      I1 => n_th_adc_interrupt(19),
      O => \data_reg_select_n_th_adc_interrupt_1_1_reg[30]_0\(1)
    );
\i__carry__0_i_8\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => \^q\(10),
      I1 => \^q\(11),
      O => \data_reg_select_n_th_adc_interrupt_1_1_reg[30]_0\(0)
    );
\i__carry_i_10\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"9009"
    )
        port map (
      I0 => \^q\(5),
      I1 => \HDL_Counter_out10_inferred__0/i__carry\(5),
      I2 => \^q\(4),
      I3 => \HDL_Counter_out10_inferred__0/i__carry\(4),
      O => S(2)
    );
\i__carry_i_11\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"9009"
    )
        port map (
      I0 => \^q\(3),
      I1 => \HDL_Counter_out10_inferred__0/i__carry\(3),
      I2 => \^q\(2),
      I3 => \HDL_Counter_out10_inferred__0/i__carry\(2),
      O => S(1)
    );
\i__carry_i_12\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"9009"
    )
        port map (
      I0 => \^q\(1),
      I1 => \HDL_Counter_out10_inferred__0/i__carry\(1),
      I2 => \^q\(0),
      I3 => \HDL_Counter_out10_inferred__0/i__carry\(0),
      O => S(0)
    );
\i__carry_i_5\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => \^q\(9),
      I1 => n_th_adc_interrupt(15),
      O => S(7)
    );
\i__carry_i_6\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => n_th_adc_interrupt(12),
      I1 => n_th_adc_interrupt(13),
      O => S(6)
    );
\i__carry_i_7\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => \^q\(8),
      I1 => n_th_adc_interrupt(11),
      O => S(5)
    );
\i__carry_i_8\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => n_th_adc_interrupt(8),
      I1 => n_th_adc_interrupt(9),
      O => S(4)
    );
\i__carry_i_9\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"9009"
    )
        port map (
      I0 => \^q\(7),
      I1 => \HDL_Counter_out10_inferred__0/i__carry\(7),
      I2 => \^q\(6),
      I3 => \HDL_Counter_out10_inferred__0/i__carry\(6),
      O => S(3)
    );
interrupt_out_adc_INST_0: unisim.vcomponents.LUT2
    generic map(
      INIT => X"8"
    )
        port map (
      I0 => interrupt_out_adc_INST_0_i_1_n_0,
      I1 => interrupt_out_adc_INST_0_i_2_n_0,
      O => interrupt_out_adc
    );
interrupt_out_adc_INST_0_i_1: unisim.vcomponents.LUT3
    generic map(
      INIT => X"80"
    )
        port map (
      I0 => interrupt_out_adc_INST_0_i_3_n_0,
      I1 => interrupt_out_adc_INST_0_i_4_n_0,
      I2 => interrupt_out_adc_INST_0_i_5_n_0,
      O => interrupt_out_adc_INST_0_i_1_n_0
    );
interrupt_out_adc_INST_0_i_10: unisim.vcomponents.LUT5
    generic map(
      INIT => X"00000001"
    )
        port map (
      I0 => \^data_reg_select_axi_1_1_reg[30]_0\(14),
      I1 => \^data_reg_select_axi_1_1_reg[30]_0\(15),
      I2 => \^data_reg_select_axi_1_1_reg[30]_0\(16),
      I3 => \^data_reg_select_axi_1_1_reg[30]_0\(17),
      I4 => p_0_in(0),
      O => interrupt_out_adc_INST_0_i_10_n_0
    );
interrupt_out_adc_INST_0_i_11: unisim.vcomponents.LUT4
    generic map(
      INIT => X"0001"
    )
        port map (
      I0 => \^data_reg_select_axi_1_1_reg[30]_0\(13),
      I1 => p_0_in(6),
      I2 => \^data_reg_select_axi_1_1_reg[30]_0\(12),
      I3 => \^data_reg_select_axi_1_1_reg[30]_0\(11),
      O => interrupt_out_adc_INST_0_i_11_n_0
    );
interrupt_out_adc_INST_0_i_2: unisim.vcomponents.MUXF7
     port map (
      I0 => interrupt_out_adc_INST_0_i_6_n_0,
      I1 => interrupt_out_adc_INST_0_i_7_n_0,
      O => interrupt_out_adc_INST_0_i_2_n_0,
      S => \^data_reg_select_axi_1_1_reg[30]_0\(0)
    );
interrupt_out_adc_INST_0_i_3: unisim.vcomponents.LUT5
    generic map(
      INIT => X"00010000"
    )
        port map (
      I0 => \^data_reg_select_axi_1_1_reg[30]_0\(3),
      I1 => p_0_in(27),
      I2 => \^data_reg_select_axi_1_1_reg[30]_0\(4),
      I3 => p_0_in(25),
      I4 => interrupt_out_adc_INST_0_i_8_n_0,
      O => interrupt_out_adc_INST_0_i_3_n_0
    );
interrupt_out_adc_INST_0_i_4: unisim.vcomponents.LUT5
    generic map(
      INIT => X"00010000"
    )
        port map (
      I0 => p_0_in(20),
      I1 => p_0_in(19),
      I2 => p_0_in(18),
      I3 => \^data_reg_select_axi_1_1_reg[30]_0\(6),
      I4 => interrupt_out_adc_INST_0_i_9_n_0,
      O => interrupt_out_adc_INST_0_i_4_n_0
    );
interrupt_out_adc_INST_0_i_5: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0000000000000008"
    )
        port map (
      I0 => interrupt_out_adc_INST_0_i_10_n_0,
      I1 => interrupt_out_adc_INST_0_i_11_n_0,
      I2 => \^data_reg_select_axi_1_1_reg[30]_0\(10),
      I3 => p_0_in(10),
      I4 => p_0_in(11),
      I5 => p_0_in(12),
      O => interrupt_out_adc_INST_0_i_5_n_0
    );
interrupt_out_adc_INST_0_i_6: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => interrupts_in(6),
      I1 => interrupts_in(2),
      I2 => \^data_reg_select_axi_1_1_reg[30]_0\(1),
      I3 => interrupts_in(4),
      I4 => \^data_reg_select_axi_1_1_reg[30]_0\(2),
      I5 => interrupts_in(0),
      O => interrupt_out_adc_INST_0_i_6_n_0
    );
interrupt_out_adc_INST_0_i_7: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => interrupts_in(7),
      I1 => interrupts_in(3),
      I2 => \^data_reg_select_axi_1_1_reg[30]_0\(1),
      I3 => interrupts_in(5),
      I4 => \^data_reg_select_axi_1_1_reg[30]_0\(2),
      I5 => interrupts_in(1),
      O => interrupt_out_adc_INST_0_i_7_n_0
    );
interrupt_out_adc_INST_0_i_8: unisim.vcomponents.LUT4
    generic map(
      INIT => X"0001"
    )
        port map (
      I0 => \^data_reg_select_axi_1_1_reg[30]_0\(5),
      I1 => p_0_in(22),
      I2 => p_0_in(23),
      I3 => p_0_in(24),
      O => interrupt_out_adc_INST_0_i_8_n_0
    );
interrupt_out_adc_INST_0_i_9: unisim.vcomponents.LUT4
    generic map(
      INIT => X"0001"
    )
        port map (
      I0 => \^data_reg_select_axi_1_1_reg[30]_0\(9),
      I1 => \^data_reg_select_axi_1_1_reg[30]_0\(8),
      I2 => \^data_reg_select_axi_1_1_reg[30]_0\(7),
      I3 => p_0_in(16),
      O => interrupt_out_adc_INST_0_i_9_n_0
    );
\interrupt_out_isr[0]_INST_0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0001000000000000"
    )
        port map (
      I0 => \^data_reg_select_axi_1_1_reg[30]_0\(2),
      I1 => \^data_reg_select_axi_1_1_reg[30]_0\(1),
      I2 => \^data_reg_select_axi_1_1_reg[30]_0\(0),
      I3 => U_k_1,
      I4 => U_k,
      I5 => interrupt_out_adc_INST_0_i_1_n_0,
      O => interrupt_out_isr(0)
    );
\interrupt_out_isr[1]_INST_0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0010000000000000"
    )
        port map (
      I0 => \^data_reg_select_axi_1_1_reg[30]_0\(2),
      I1 => \^data_reg_select_axi_1_1_reg[30]_0\(1),
      I2 => \^data_reg_select_axi_1_1_reg[30]_0\(0),
      I3 => U_k_1,
      I4 => U_k,
      I5 => interrupt_out_adc_INST_0_i_1_n_0,
      O => interrupt_out_isr(1)
    );
\interrupt_out_isr[2]_INST_0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0004000000000000"
    )
        port map (
      I0 => \^data_reg_select_axi_1_1_reg[30]_0\(2),
      I1 => \^data_reg_select_axi_1_1_reg[30]_0\(1),
      I2 => \^data_reg_select_axi_1_1_reg[30]_0\(0),
      I3 => U_k_1,
      I4 => U_k,
      I5 => interrupt_out_adc_INST_0_i_1_n_0,
      O => interrupt_out_isr(2)
    );
\interrupt_out_isr[3]_INST_0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0040000000000000"
    )
        port map (
      I0 => \^data_reg_select_axi_1_1_reg[30]_0\(2),
      I1 => \^data_reg_select_axi_1_1_reg[30]_0\(1),
      I2 => \^data_reg_select_axi_1_1_reg[30]_0\(0),
      I3 => U_k_1,
      I4 => U_k,
      I5 => interrupt_out_adc_INST_0_i_1_n_0,
      O => interrupt_out_isr(3)
    );
\interrupt_out_isr[4]_INST_0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0004000000000000"
    )
        port map (
      I0 => \^data_reg_select_axi_1_1_reg[30]_0\(1),
      I1 => \^data_reg_select_axi_1_1_reg[30]_0\(2),
      I2 => \^data_reg_select_axi_1_1_reg[30]_0\(0),
      I3 => U_k_1,
      I4 => U_k,
      I5 => interrupt_out_adc_INST_0_i_1_n_0,
      O => interrupt_out_isr(4)
    );
\interrupt_out_isr[5]_INST_0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0040000000000000"
    )
        port map (
      I0 => \^data_reg_select_axi_1_1_reg[30]_0\(1),
      I1 => \^data_reg_select_axi_1_1_reg[30]_0\(2),
      I2 => \^data_reg_select_axi_1_1_reg[30]_0\(0),
      I3 => U_k_1,
      I4 => U_k,
      I5 => interrupt_out_adc_INST_0_i_1_n_0,
      O => interrupt_out_isr(5)
    );
\interrupt_out_isr[6]_INST_0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0008000000000000"
    )
        port map (
      I0 => \^data_reg_select_axi_1_1_reg[30]_0\(2),
      I1 => \^data_reg_select_axi_1_1_reg[30]_0\(1),
      I2 => \^data_reg_select_axi_1_1_reg[30]_0\(0),
      I3 => U_k_1,
      I4 => U_k,
      I5 => interrupt_out_adc_INST_0_i_1_n_0,
      O => interrupt_out_isr(6)
    );
\interrupt_out_isr[7]_INST_0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0080000000000000"
    )
        port map (
      I0 => \^data_reg_select_axi_1_1_reg[30]_0\(2),
      I1 => \^data_reg_select_axi_1_1_reg[30]_0\(1),
      I2 => \^data_reg_select_axi_1_1_reg[30]_0\(0),
      I3 => U_k_1,
      I4 => U_k,
      I5 => interrupt_out_adc_INST_0_i_1_n_0,
      O => interrupt_out_isr(7)
    );
\read_reg_ip_timestamp_reg[30]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => '1',
      Q => read_reg_ip_timestamp(0),
      R => SR(0)
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity zusys_mux_axi_ip_1_0_mux_axi_ip_axi_lite_module is
  port (
    FSM_sequential_axi_lite_rstate_reg_0 : out STD_LOGIC;
    soft_reset : out STD_LOGIC;
    AXI4_Lite_ARADDR_8_sp_1 : out STD_LOGIC;
    AXI4_Lite_ARADDR_2_sp_1 : out STD_LOGIC;
    wr_enb_1_reg_0 : out STD_LOGIC_VECTOR ( 0 to 0 );
    wr_enb_1_reg_1 : out STD_LOGIC_VECTOR ( 0 to 0 );
    AXI4_Lite_ARREADY : out STD_LOGIC;
    \FSM_onehot_axi_lite_wstate_reg[2]_0\ : out STD_LOGIC_VECTOR ( 1 downto 0 );
    AXI4_Lite_AWREADY : out STD_LOGIC;
    reset_in : out STD_LOGIC;
    \wdata_reg[31]_0\ : out STD_LOGIC_VECTOR ( 31 downto 0 );
    \wdata_reg[0]_0\ : out STD_LOGIC;
    AXI4_Lite_RDATA : out STD_LOGIC_VECTOR ( 31 downto 0 );
    AXI4_Lite_ACLK : in STD_LOGIC;
    D : in STD_LOGIC_VECTOR ( 16 downto 0 );
    \AXI4_Lite_RDATA_tmp_reg[30]_0\ : in STD_LOGIC_VECTOR ( 14 downto 0 );
    Q : in STD_LOGIC_VECTOR ( 14 downto 0 );
    read_reg_ip_timestamp : in STD_LOGIC_VECTOR ( 0 to 0 );
    AXI4_Lite_ARADDR : in STD_LOGIC_VECTOR ( 13 downto 0 );
    write_axi_enable : in STD_LOGIC;
    AXI4_Lite_ARVALID : in STD_LOGIC;
    AXI4_Lite_RREADY : in STD_LOGIC;
    AXI4_Lite_AWVALID : in STD_LOGIC;
    AXI4_Lite_WVALID : in STD_LOGIC;
    AXI4_Lite_ARESETN : in STD_LOGIC;
    IPCORE_RESETN : in STD_LOGIC;
    AXI4_Lite_BREADY : in STD_LOGIC;
    AXI4_Lite_WSTRB : in STD_LOGIC_VECTOR ( 3 downto 0 );
    AXI4_Lite_AWADDR : in STD_LOGIC_VECTOR ( 13 downto 0 );
    AXI4_Lite_WDATA : in STD_LOGIC_VECTOR ( 31 downto 0 )
  );
  attribute ORIG_REF_NAME : string;
  attribute ORIG_REF_NAME of zusys_mux_axi_ip_1_0_mux_axi_ip_axi_lite_module : entity is "mux_axi_ip_axi_lite_module";
end zusys_mux_axi_ip_1_0_mux_axi_ip_axi_lite_module;

architecture STRUCTURE of zusys_mux_axi_ip_1_0_mux_axi_ip_axi_lite_module is
  signal AXI4_Lite_ARADDR_2_sn_1 : STD_LOGIC;
  signal AXI4_Lite_ARADDR_8_sn_1 : STD_LOGIC;
  signal \AXI4_Lite_RDATA_tmp[0]_i_2_n_0\ : STD_LOGIC;
  signal \AXI4_Lite_RDATA_tmp[0]_i_3_n_0\ : STD_LOGIC;
  signal \AXI4_Lite_RDATA_tmp[30]_i_2_n_0\ : STD_LOGIC;
  signal \AXI4_Lite_RDATA_tmp[30]_i_3_n_0\ : STD_LOGIC;
  signal \AXI4_Lite_RDATA_tmp[30]_i_4_n_0\ : STD_LOGIC;
  signal \AXI4_Lite_RDATA_tmp[30]_i_5_n_0\ : STD_LOGIC;
  signal \AXI4_Lite_RDATA_tmp[30]_i_6_n_0\ : STD_LOGIC;
  signal \^fsm_onehot_axi_lite_wstate_reg[2]_0\ : STD_LOGIC_VECTOR ( 1 downto 0 );
  signal \FSM_onehot_axi_lite_wstate_reg_n_0_[0]\ : STD_LOGIC;
  signal \^fsm_sequential_axi_lite_rstate_reg_0\ : STD_LOGIC;
  signal aw_transfer : STD_LOGIC;
  signal axi_lite_rstate_next : STD_LOGIC;
  signal axi_lite_wstate_next : STD_LOGIC_VECTOR ( 2 downto 0 );
  signal data_read : STD_LOGIC_VECTOR ( 30 downto 0 );
  signal data_reg_axi_enable_1_1_i_2_n_0 : STD_LOGIC;
  signal \data_reg_select_AXI_1_1[3]_i_3_n_0\ : STD_LOGIC;
  signal \data_reg_select_AXI_1_1[3]_i_4_n_0\ : STD_LOGIC;
  signal \data_reg_select_AXI_1_1[3]_i_5_n_0\ : STD_LOGIC;
  signal \data_reg_select_AXI_1_1[3]_i_6_n_0\ : STD_LOGIC;
  signal \data_reg_select_AXI_1_1[3]_i_7_n_0\ : STD_LOGIC;
  signal \data_reg_select_AXI_1_1[3]_i_8_n_0\ : STD_LOGIC;
  signal reset : STD_LOGIC;
  signal sel0 : STD_LOGIC_VECTOR ( 13 downto 0 );
  signal \^soft_reset\ : STD_LOGIC;
  signal soft_reset_i_1_n_0 : STD_LOGIC;
  signal soft_reset_i_2_n_0 : STD_LOGIC;
  signal soft_reset_i_3_n_0 : STD_LOGIC;
  signal soft_reset_i_4_n_0 : STD_LOGIC;
  signal top_rd_enb : STD_LOGIC;
  signal top_wr_enb : STD_LOGIC;
  signal w_transfer : STD_LOGIC;
  signal w_transfer_and_wstrb : STD_LOGIC;
  signal \^wdata_reg[31]_0\ : STD_LOGIC_VECTOR ( 31 downto 0 );
  attribute SOFT_HLUTNM : string;
  attribute SOFT_HLUTNM of AXI4_Lite_ARREADY_INST_0 : label is "soft_lutpair2";
  attribute SOFT_HLUTNM of AXI4_Lite_AWREADY_INST_0 : label is "soft_lutpair3";
  attribute SOFT_HLUTNM of \AXI4_Lite_RDATA_tmp[0]_i_3\ : label is "soft_lutpair5";
  attribute SOFT_HLUTNM of \AXI4_Lite_RDATA_tmp[30]_i_3\ : label is "soft_lutpair5";
  attribute SOFT_HLUTNM of \FSM_onehot_axi_lite_wstate[1]_i_2\ : label is "soft_lutpair3";
  attribute FSM_ENCODED_STATES : string;
  attribute FSM_ENCODED_STATES of \FSM_onehot_axi_lite_wstate_reg[0]\ : label is "iSTATE:010,iSTATE0:100,iSTATE1:001";
  attribute FSM_ENCODED_STATES of \FSM_onehot_axi_lite_wstate_reg[1]\ : label is "iSTATE:010,iSTATE0:100,iSTATE1:001";
  attribute FSM_ENCODED_STATES of \FSM_onehot_axi_lite_wstate_reg[2]\ : label is "iSTATE:010,iSTATE0:100,iSTATE1:001";
  attribute SOFT_HLUTNM of FSM_sequential_axi_lite_rstate_i_1 : label is "soft_lutpair2";
  attribute FSM_ENCODED_STATES of FSM_sequential_axi_lite_rstate_reg : label is "iSTATE:0,iSTATE0:1";
  attribute SOFT_HLUTNM of data_reg_axi_enable_1_1_i_1 : label is "soft_lutpair4";
  attribute SOFT_HLUTNM of \data_reg_select_n_th_adc_interrupt_1_1[31]_i_1\ : label is "soft_lutpair4";
begin
  AXI4_Lite_ARADDR_2_sp_1 <= AXI4_Lite_ARADDR_2_sn_1;
  AXI4_Lite_ARADDR_8_sp_1 <= AXI4_Lite_ARADDR_8_sn_1;
  \FSM_onehot_axi_lite_wstate_reg[2]_0\(1 downto 0) <= \^fsm_onehot_axi_lite_wstate_reg[2]_0\(1 downto 0);
  FSM_sequential_axi_lite_rstate_reg_0 <= \^fsm_sequential_axi_lite_rstate_reg_0\;
  soft_reset <= \^soft_reset\;
  \wdata_reg[31]_0\(31 downto 0) <= \^wdata_reg[31]_0\(31 downto 0);
AXI4_Lite_ARREADY_INST_0: unisim.vcomponents.LUT3
    generic map(
      INIT => X"04"
    )
        port map (
      I0 => \^fsm_sequential_axi_lite_rstate_reg_0\,
      I1 => \FSM_onehot_axi_lite_wstate_reg_n_0_[0]\,
      I2 => AXI4_Lite_AWVALID,
      O => AXI4_Lite_ARREADY
    );
AXI4_Lite_AWREADY_INST_0: unisim.vcomponents.LUT2
    generic map(
      INIT => X"2"
    )
        port map (
      I0 => \FSM_onehot_axi_lite_wstate_reg_n_0_[0]\,
      I1 => \^fsm_sequential_axi_lite_rstate_reg_0\,
      O => AXI4_Lite_AWREADY
    );
\AXI4_Lite_RDATA_tmp[0]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFFFFFFFFFFF888"
    )
        port map (
      I0 => AXI4_Lite_ARADDR_8_sn_1,
      I1 => \AXI4_Lite_RDATA_tmp_reg[30]_0\(0),
      I2 => Q(0),
      I3 => AXI4_Lite_ARADDR_2_sn_1,
      I4 => \AXI4_Lite_RDATA_tmp[0]_i_2_n_0\,
      I5 => \AXI4_Lite_RDATA_tmp[30]_i_2_n_0\,
      O => data_read(0)
    );
\AXI4_Lite_RDATA_tmp[0]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"8F88888800000000"
    )
        port map (
      I0 => \AXI4_Lite_RDATA_tmp[0]_i_3_n_0\,
      I1 => \data_reg_select_AXI_1_1[3]_i_4_n_0\,
      I2 => AXI4_Lite_ARADDR(6),
      I3 => AXI4_Lite_ARADDR(0),
      I4 => \data_reg_select_AXI_1_1[3]_i_3_n_0\,
      I5 => write_axi_enable,
      O => \AXI4_Lite_RDATA_tmp[0]_i_2_n_0\
    );
\AXI4_Lite_RDATA_tmp[0]_i_3\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"2"
    )
        port map (
      I0 => sel0(0),
      I1 => sel0(6),
      O => \AXI4_Lite_RDATA_tmp[0]_i_3_n_0\
    );
\AXI4_Lite_RDATA_tmp[10]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFEAEAEA"
    )
        port map (
      I0 => \AXI4_Lite_RDATA_tmp[30]_i_2_n_0\,
      I1 => AXI4_Lite_ARADDR_2_sn_1,
      I2 => Q(2),
      I3 => \AXI4_Lite_RDATA_tmp_reg[30]_0\(2),
      I4 => AXI4_Lite_ARADDR_8_sn_1,
      O => data_read(10)
    );
\AXI4_Lite_RDATA_tmp[14]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFEAEAEA"
    )
        port map (
      I0 => \AXI4_Lite_RDATA_tmp[30]_i_2_n_0\,
      I1 => AXI4_Lite_ARADDR_2_sn_1,
      I2 => Q(3),
      I3 => \AXI4_Lite_RDATA_tmp_reg[30]_0\(3),
      I4 => AXI4_Lite_ARADDR_8_sn_1,
      O => data_read(14)
    );
\AXI4_Lite_RDATA_tmp[16]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFEAEAEA"
    )
        port map (
      I0 => \AXI4_Lite_RDATA_tmp[30]_i_2_n_0\,
      I1 => AXI4_Lite_ARADDR_2_sn_1,
      I2 => Q(4),
      I3 => \AXI4_Lite_RDATA_tmp_reg[30]_0\(4),
      I4 => AXI4_Lite_ARADDR_8_sn_1,
      O => data_read(16)
    );
\AXI4_Lite_RDATA_tmp[17]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFEAEAEA"
    )
        port map (
      I0 => \AXI4_Lite_RDATA_tmp[30]_i_2_n_0\,
      I1 => AXI4_Lite_ARADDR_2_sn_1,
      I2 => Q(5),
      I3 => \AXI4_Lite_RDATA_tmp_reg[30]_0\(5),
      I4 => AXI4_Lite_ARADDR_8_sn_1,
      O => data_read(17)
    );
\AXI4_Lite_RDATA_tmp[18]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFEAEAEA"
    )
        port map (
      I0 => \AXI4_Lite_RDATA_tmp[30]_i_2_n_0\,
      I1 => AXI4_Lite_ARADDR_2_sn_1,
      I2 => Q(6),
      I3 => \AXI4_Lite_RDATA_tmp_reg[30]_0\(6),
      I4 => AXI4_Lite_ARADDR_8_sn_1,
      O => data_read(18)
    );
\AXI4_Lite_RDATA_tmp[22]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFEAEAEA"
    )
        port map (
      I0 => \AXI4_Lite_RDATA_tmp[30]_i_2_n_0\,
      I1 => AXI4_Lite_ARADDR_2_sn_1,
      I2 => Q(7),
      I3 => \AXI4_Lite_RDATA_tmp_reg[30]_0\(7),
      I4 => AXI4_Lite_ARADDR_8_sn_1,
      O => data_read(22)
    );
\AXI4_Lite_RDATA_tmp[23]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFEAEAEA"
    )
        port map (
      I0 => \AXI4_Lite_RDATA_tmp[30]_i_2_n_0\,
      I1 => AXI4_Lite_ARADDR_2_sn_1,
      I2 => Q(8),
      I3 => \AXI4_Lite_RDATA_tmp_reg[30]_0\(8),
      I4 => AXI4_Lite_ARADDR_8_sn_1,
      O => data_read(23)
    );
\AXI4_Lite_RDATA_tmp[24]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFEAEAEA"
    )
        port map (
      I0 => \AXI4_Lite_RDATA_tmp[30]_i_2_n_0\,
      I1 => AXI4_Lite_ARADDR_2_sn_1,
      I2 => Q(9),
      I3 => \AXI4_Lite_RDATA_tmp_reg[30]_0\(9),
      I4 => AXI4_Lite_ARADDR_8_sn_1,
      O => data_read(24)
    );
\AXI4_Lite_RDATA_tmp[26]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFEAEAEA"
    )
        port map (
      I0 => \AXI4_Lite_RDATA_tmp[30]_i_2_n_0\,
      I1 => AXI4_Lite_ARADDR_2_sn_1,
      I2 => Q(10),
      I3 => \AXI4_Lite_RDATA_tmp_reg[30]_0\(10),
      I4 => AXI4_Lite_ARADDR_8_sn_1,
      O => data_read(26)
    );
\AXI4_Lite_RDATA_tmp[27]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFEAEAEA"
    )
        port map (
      I0 => \AXI4_Lite_RDATA_tmp[30]_i_2_n_0\,
      I1 => AXI4_Lite_ARADDR_2_sn_1,
      I2 => Q(11),
      I3 => \AXI4_Lite_RDATA_tmp_reg[30]_0\(11),
      I4 => AXI4_Lite_ARADDR_8_sn_1,
      O => data_read(27)
    );
\AXI4_Lite_RDATA_tmp[28]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFEAEAEA"
    )
        port map (
      I0 => \AXI4_Lite_RDATA_tmp[30]_i_2_n_0\,
      I1 => AXI4_Lite_ARADDR_2_sn_1,
      I2 => Q(12),
      I3 => \AXI4_Lite_RDATA_tmp_reg[30]_0\(12),
      I4 => AXI4_Lite_ARADDR_8_sn_1,
      O => data_read(28)
    );
\AXI4_Lite_RDATA_tmp[29]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFEAEAEA"
    )
        port map (
      I0 => \AXI4_Lite_RDATA_tmp[30]_i_2_n_0\,
      I1 => AXI4_Lite_ARADDR_2_sn_1,
      I2 => Q(13),
      I3 => \AXI4_Lite_RDATA_tmp_reg[30]_0\(13),
      I4 => AXI4_Lite_ARADDR_8_sn_1,
      O => data_read(29)
    );
\AXI4_Lite_RDATA_tmp[30]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFEAEAEA"
    )
        port map (
      I0 => \AXI4_Lite_RDATA_tmp[30]_i_2_n_0\,
      I1 => AXI4_Lite_ARADDR_2_sn_1,
      I2 => Q(14),
      I3 => \AXI4_Lite_RDATA_tmp_reg[30]_0\(14),
      I4 => AXI4_Lite_ARADDR_8_sn_1,
      O => data_read(30)
    );
\AXI4_Lite_RDATA_tmp[30]_i_2\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"F8880000"
    )
        port map (
      I0 => \AXI4_Lite_RDATA_tmp[30]_i_3_n_0\,
      I1 => \AXI4_Lite_RDATA_tmp[30]_i_4_n_0\,
      I2 => \AXI4_Lite_RDATA_tmp[30]_i_5_n_0\,
      I3 => \AXI4_Lite_RDATA_tmp[30]_i_6_n_0\,
      I4 => read_reg_ip_timestamp(0),
      O => \AXI4_Lite_RDATA_tmp[30]_i_2_n_0\
    );
\AXI4_Lite_RDATA_tmp[30]_i_3\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"04"
    )
        port map (
      I0 => sel0(6),
      I1 => sel0(1),
      I2 => sel0(0),
      O => \AXI4_Lite_RDATA_tmp[30]_i_3_n_0\
    );
\AXI4_Lite_RDATA_tmp[30]_i_4\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0000000000020000"
    )
        port map (
      I0 => soft_reset_i_3_n_0,
      I1 => sel0(13),
      I2 => sel0(2),
      I3 => sel0(3),
      I4 => soft_reset_i_2_n_0,
      I5 => AXI4_Lite_ARVALID,
      O => \AXI4_Lite_RDATA_tmp[30]_i_4_n_0\
    );
\AXI4_Lite_RDATA_tmp[30]_i_5\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"04"
    )
        port map (
      I0 => AXI4_Lite_ARADDR(6),
      I1 => AXI4_Lite_ARADDR(1),
      I2 => AXI4_Lite_ARADDR(0),
      O => \AXI4_Lite_RDATA_tmp[30]_i_5_n_0\
    );
\AXI4_Lite_RDATA_tmp[30]_i_6\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0000000200000000"
    )
        port map (
      I0 => \data_reg_select_AXI_1_1[3]_i_7_n_0\,
      I1 => AXI4_Lite_ARADDR(5),
      I2 => AXI4_Lite_ARADDR(4),
      I3 => AXI4_Lite_ARADDR(3),
      I4 => AXI4_Lite_ARADDR(2),
      I5 => \data_reg_select_AXI_1_1[3]_i_5_n_0\,
      O => \AXI4_Lite_RDATA_tmp[30]_i_6_n_0\
    );
\AXI4_Lite_RDATA_tmp[31]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"0400"
    )
        port map (
      I0 => AXI4_Lite_AWVALID,
      I1 => AXI4_Lite_ARVALID,
      I2 => \^fsm_sequential_axi_lite_rstate_reg_0\,
      I3 => \FSM_onehot_axi_lite_wstate_reg_n_0_[0]\,
      O => top_rd_enb
    );
\AXI4_Lite_RDATA_tmp[31]_i_3\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FF80808080808080"
    )
        port map (
      I0 => \data_reg_select_AXI_1_1[3]_i_3_n_0\,
      I1 => AXI4_Lite_ARADDR(0),
      I2 => AXI4_Lite_ARADDR(6),
      I3 => \data_reg_select_AXI_1_1[3]_i_4_n_0\,
      I4 => sel0(0),
      I5 => sel0(6),
      O => AXI4_Lite_ARADDR_2_sn_1
    );
\AXI4_Lite_RDATA_tmp[5]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFEAEAEA"
    )
        port map (
      I0 => \AXI4_Lite_RDATA_tmp[30]_i_2_n_0\,
      I1 => AXI4_Lite_ARADDR_2_sn_1,
      I2 => Q(1),
      I3 => \AXI4_Lite_RDATA_tmp_reg[30]_0\(1),
      I4 => AXI4_Lite_ARADDR_8_sn_1,
      O => data_read(5)
    );
\AXI4_Lite_RDATA_tmp_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => top_rd_enb,
      D => data_read(0),
      Q => AXI4_Lite_RDATA(0),
      R => reset
    );
\AXI4_Lite_RDATA_tmp_reg[10]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => top_rd_enb,
      D => data_read(10),
      Q => AXI4_Lite_RDATA(10),
      R => reset
    );
\AXI4_Lite_RDATA_tmp_reg[11]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => top_rd_enb,
      D => D(8),
      Q => AXI4_Lite_RDATA(11),
      R => reset
    );
\AXI4_Lite_RDATA_tmp_reg[12]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => top_rd_enb,
      D => D(9),
      Q => AXI4_Lite_RDATA(12),
      R => reset
    );
\AXI4_Lite_RDATA_tmp_reg[13]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => top_rd_enb,
      D => D(10),
      Q => AXI4_Lite_RDATA(13),
      R => reset
    );
\AXI4_Lite_RDATA_tmp_reg[14]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => top_rd_enb,
      D => data_read(14),
      Q => AXI4_Lite_RDATA(14),
      R => reset
    );
\AXI4_Lite_RDATA_tmp_reg[15]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => top_rd_enb,
      D => D(11),
      Q => AXI4_Lite_RDATA(15),
      R => reset
    );
\AXI4_Lite_RDATA_tmp_reg[16]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => top_rd_enb,
      D => data_read(16),
      Q => AXI4_Lite_RDATA(16),
      R => reset
    );
\AXI4_Lite_RDATA_tmp_reg[17]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => top_rd_enb,
      D => data_read(17),
      Q => AXI4_Lite_RDATA(17),
      R => reset
    );
\AXI4_Lite_RDATA_tmp_reg[18]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => top_rd_enb,
      D => data_read(18),
      Q => AXI4_Lite_RDATA(18),
      R => reset
    );
\AXI4_Lite_RDATA_tmp_reg[19]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => top_rd_enb,
      D => D(12),
      Q => AXI4_Lite_RDATA(19),
      R => reset
    );
\AXI4_Lite_RDATA_tmp_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => top_rd_enb,
      D => D(0),
      Q => AXI4_Lite_RDATA(1),
      R => reset
    );
\AXI4_Lite_RDATA_tmp_reg[20]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => top_rd_enb,
      D => D(13),
      Q => AXI4_Lite_RDATA(20),
      R => reset
    );
\AXI4_Lite_RDATA_tmp_reg[21]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => top_rd_enb,
      D => D(14),
      Q => AXI4_Lite_RDATA(21),
      R => reset
    );
\AXI4_Lite_RDATA_tmp_reg[22]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => top_rd_enb,
      D => data_read(22),
      Q => AXI4_Lite_RDATA(22),
      R => reset
    );
\AXI4_Lite_RDATA_tmp_reg[23]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => top_rd_enb,
      D => data_read(23),
      Q => AXI4_Lite_RDATA(23),
      R => reset
    );
\AXI4_Lite_RDATA_tmp_reg[24]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => top_rd_enb,
      D => data_read(24),
      Q => AXI4_Lite_RDATA(24),
      R => reset
    );
\AXI4_Lite_RDATA_tmp_reg[25]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => top_rd_enb,
      D => D(15),
      Q => AXI4_Lite_RDATA(25),
      R => reset
    );
\AXI4_Lite_RDATA_tmp_reg[26]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => top_rd_enb,
      D => data_read(26),
      Q => AXI4_Lite_RDATA(26),
      R => reset
    );
\AXI4_Lite_RDATA_tmp_reg[27]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => top_rd_enb,
      D => data_read(27),
      Q => AXI4_Lite_RDATA(27),
      R => reset
    );
\AXI4_Lite_RDATA_tmp_reg[28]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => top_rd_enb,
      D => data_read(28),
      Q => AXI4_Lite_RDATA(28),
      R => reset
    );
\AXI4_Lite_RDATA_tmp_reg[29]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => top_rd_enb,
      D => data_read(29),
      Q => AXI4_Lite_RDATA(29),
      R => reset
    );
\AXI4_Lite_RDATA_tmp_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => top_rd_enb,
      D => D(1),
      Q => AXI4_Lite_RDATA(2),
      R => reset
    );
\AXI4_Lite_RDATA_tmp_reg[30]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => top_rd_enb,
      D => data_read(30),
      Q => AXI4_Lite_RDATA(30),
      R => reset
    );
\AXI4_Lite_RDATA_tmp_reg[31]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => top_rd_enb,
      D => D(16),
      Q => AXI4_Lite_RDATA(31),
      R => reset
    );
\AXI4_Lite_RDATA_tmp_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => top_rd_enb,
      D => D(2),
      Q => AXI4_Lite_RDATA(3),
      R => reset
    );
\AXI4_Lite_RDATA_tmp_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => top_rd_enb,
      D => D(3),
      Q => AXI4_Lite_RDATA(4),
      R => reset
    );
\AXI4_Lite_RDATA_tmp_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => top_rd_enb,
      D => data_read(5),
      Q => AXI4_Lite_RDATA(5),
      R => reset
    );
\AXI4_Lite_RDATA_tmp_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => top_rd_enb,
      D => D(4),
      Q => AXI4_Lite_RDATA(6),
      R => reset
    );
\AXI4_Lite_RDATA_tmp_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => top_rd_enb,
      D => D(5),
      Q => AXI4_Lite_RDATA(7),
      R => reset
    );
\AXI4_Lite_RDATA_tmp_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => top_rd_enb,
      D => D(6),
      Q => AXI4_Lite_RDATA(8),
      R => reset
    );
\AXI4_Lite_RDATA_tmp_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => top_rd_enb,
      D => D(7),
      Q => AXI4_Lite_RDATA(9),
      R => reset
    );
\FSM_onehot_axi_lite_wstate[0]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFC0D5C0"
    )
        port map (
      I0 => AXI4_Lite_AWVALID,
      I1 => AXI4_Lite_BREADY,
      I2 => \^fsm_onehot_axi_lite_wstate_reg[2]_0\(1),
      I3 => \FSM_onehot_axi_lite_wstate_reg_n_0_[0]\,
      I4 => \^fsm_sequential_axi_lite_rstate_reg_0\,
      O => axi_lite_wstate_next(0)
    );
\FSM_onehot_axi_lite_wstate[1]_i_1\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => AXI4_Lite_ARESETN,
      O => reset
    );
\FSM_onehot_axi_lite_wstate[1]_i_2\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"4444F444"
    )
        port map (
      I0 => AXI4_Lite_WVALID,
      I1 => \^fsm_onehot_axi_lite_wstate_reg[2]_0\(0),
      I2 => AXI4_Lite_AWVALID,
      I3 => \FSM_onehot_axi_lite_wstate_reg_n_0_[0]\,
      I4 => \^fsm_sequential_axi_lite_rstate_reg_0\,
      O => axi_lite_wstate_next(1)
    );
\FSM_onehot_axi_lite_wstate[2]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"8F88"
    )
        port map (
      I0 => \^fsm_onehot_axi_lite_wstate_reg[2]_0\(0),
      I1 => AXI4_Lite_WVALID,
      I2 => AXI4_Lite_BREADY,
      I3 => \^fsm_onehot_axi_lite_wstate_reg[2]_0\(1),
      O => axi_lite_wstate_next(2)
    );
\FSM_onehot_axi_lite_wstate_reg[0]\: unisim.vcomponents.FDSE
    generic map(
      INIT => '1'
    )
        port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => axi_lite_wstate_next(0),
      Q => \FSM_onehot_axi_lite_wstate_reg_n_0_[0]\,
      S => reset
    );
\FSM_onehot_axi_lite_wstate_reg[1]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => axi_lite_wstate_next(1),
      Q => \^fsm_onehot_axi_lite_wstate_reg[2]_0\(0),
      R => reset
    );
\FSM_onehot_axi_lite_wstate_reg[2]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => axi_lite_wstate_next(2),
      Q => \^fsm_onehot_axi_lite_wstate_reg[2]_0\(1),
      R => reset
    );
FSM_sequential_axi_lite_rstate_i_1: unisim.vcomponents.LUT5
    generic map(
      INIT => X"50505C50"
    )
        port map (
      I0 => AXI4_Lite_RREADY,
      I1 => \FSM_onehot_axi_lite_wstate_reg_n_0_[0]\,
      I2 => \^fsm_sequential_axi_lite_rstate_reg_0\,
      I3 => AXI4_Lite_ARVALID,
      I4 => AXI4_Lite_AWVALID,
      O => axi_lite_rstate_next
    );
FSM_sequential_axi_lite_rstate_reg: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => axi_lite_rstate_next,
      Q => \^fsm_sequential_axi_lite_rstate_reg_0\,
      R => reset
    );
data_reg_axi_enable_1_1_i_1: unisim.vcomponents.LUT4
    generic map(
      INIT => X"BF80"
    )
        port map (
      I0 => \^wdata_reg[31]_0\(0),
      I1 => data_reg_axi_enable_1_1_i_2_n_0,
      I2 => top_wr_enb,
      I3 => write_axi_enable,
      O => \wdata_reg[0]_0\
    );
data_reg_axi_enable_1_1_i_2: unisim.vcomponents.LUT6
    generic map(
      INIT => X"08080808FF080808"
    )
        port map (
      I0 => \data_reg_select_AXI_1_1[3]_i_3_n_0\,
      I1 => AXI4_Lite_ARADDR(0),
      I2 => AXI4_Lite_ARADDR(6),
      I3 => \data_reg_select_AXI_1_1[3]_i_4_n_0\,
      I4 => sel0(0),
      I5 => sel0(6),
      O => data_reg_axi_enable_1_1_i_2_n_0
    );
\data_reg_select_AXI_1_1[3]_i_1\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"8"
    )
        port map (
      I0 => AXI4_Lite_ARADDR_8_sn_1,
      I1 => top_wr_enb,
      O => wr_enb_1_reg_1(0)
    );
\data_reg_select_AXI_1_1[3]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"08080808FF080808"
    )
        port map (
      I0 => \data_reg_select_AXI_1_1[3]_i_3_n_0\,
      I1 => AXI4_Lite_ARADDR(6),
      I2 => AXI4_Lite_ARADDR(0),
      I3 => \data_reg_select_AXI_1_1[3]_i_4_n_0\,
      I4 => sel0(6),
      I5 => sel0(0),
      O => AXI4_Lite_ARADDR_8_sn_1
    );
\data_reg_select_AXI_1_1[3]_i_3\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"0080"
    )
        port map (
      I0 => \data_reg_select_AXI_1_1[3]_i_5_n_0\,
      I1 => \data_reg_select_AXI_1_1[3]_i_6_n_0\,
      I2 => \data_reg_select_AXI_1_1[3]_i_7_n_0\,
      I3 => AXI4_Lite_ARADDR(1),
      O => \data_reg_select_AXI_1_1[3]_i_3_n_0\
    );
\data_reg_select_AXI_1_1[3]_i_4\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"00004000"
    )
        port map (
      I0 => AXI4_Lite_ARVALID,
      I1 => soft_reset_i_2_n_0,
      I2 => \data_reg_select_AXI_1_1[3]_i_8_n_0\,
      I3 => soft_reset_i_3_n_0,
      I4 => sel0(1),
      O => \data_reg_select_AXI_1_1[3]_i_4_n_0\
    );
\data_reg_select_AXI_1_1[3]_i_5\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"0004"
    )
        port map (
      I0 => AXI4_Lite_ARADDR(13),
      I1 => AXI4_Lite_ARVALID,
      I2 => AXI4_Lite_ARADDR(12),
      I3 => AXI4_Lite_ARADDR(11),
      O => \data_reg_select_AXI_1_1[3]_i_5_n_0\
    );
\data_reg_select_AXI_1_1[3]_i_6\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"0001"
    )
        port map (
      I0 => AXI4_Lite_ARADDR(5),
      I1 => AXI4_Lite_ARADDR(4),
      I2 => AXI4_Lite_ARADDR(3),
      I3 => AXI4_Lite_ARADDR(2),
      O => \data_reg_select_AXI_1_1[3]_i_6_n_0\
    );
\data_reg_select_AXI_1_1[3]_i_7\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"0001"
    )
        port map (
      I0 => AXI4_Lite_ARADDR(10),
      I1 => AXI4_Lite_ARADDR(9),
      I2 => AXI4_Lite_ARADDR(8),
      I3 => AXI4_Lite_ARADDR(7),
      O => \data_reg_select_AXI_1_1[3]_i_7_n_0\
    );
\data_reg_select_AXI_1_1[3]_i_8\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"01"
    )
        port map (
      I0 => sel0(3),
      I1 => sel0(2),
      I2 => sel0(13),
      O => \data_reg_select_AXI_1_1[3]_i_8_n_0\
    );
\data_reg_select_n_th_adc_interrupt_1_1[31]_i_1\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"8"
    )
        port map (
      I0 => AXI4_Lite_ARADDR_2_sn_1,
      I1 => top_wr_enb,
      O => wr_enb_1_reg_0(0)
    );
reset_pipe_i_1: unisim.vcomponents.LUT3
    generic map(
      INIT => X"DF"
    )
        port map (
      I0 => IPCORE_RESETN,
      I1 => \^soft_reset\,
      I2 => AXI4_Lite_ARESETN,
      O => reset_in
    );
soft_reset_i_1: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0002000000000000"
    )
        port map (
      I0 => soft_reset_i_2_n_0,
      I1 => sel0(3),
      I2 => sel0(2),
      I3 => sel0(13),
      I4 => soft_reset_i_3_n_0,
      I5 => soft_reset_i_4_n_0,
      O => soft_reset_i_1_n_0
    );
soft_reset_i_2: unisim.vcomponents.LUT4
    generic map(
      INIT => X"0001"
    )
        port map (
      I0 => sel0(8),
      I1 => sel0(7),
      I2 => sel0(5),
      I3 => sel0(4),
      O => soft_reset_i_2_n_0
    );
soft_reset_i_3: unisim.vcomponents.LUT4
    generic map(
      INIT => X"0001"
    )
        port map (
      I0 => sel0(12),
      I1 => sel0(11),
      I2 => sel0(10),
      I3 => sel0(9),
      O => soft_reset_i_3_n_0
    );
soft_reset_i_4: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0002000000000000"
    )
        port map (
      I0 => \^wdata_reg[31]_0\(0),
      I1 => sel0(6),
      I2 => sel0(0),
      I3 => sel0(1),
      I4 => top_wr_enb,
      I5 => AXI4_Lite_ARESETN,
      O => soft_reset_i_4_n_0
    );
soft_reset_reg: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => soft_reset_i_1_n_0,
      Q => \^soft_reset\,
      R => '0'
    );
\waddr[15]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"40"
    )
        port map (
      I0 => \^fsm_sequential_axi_lite_rstate_reg_0\,
      I1 => \FSM_onehot_axi_lite_wstate_reg_n_0_[0]\,
      I2 => AXI4_Lite_AWVALID,
      O => aw_transfer
    );
\waddr_reg[10]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => aw_transfer,
      D => AXI4_Lite_AWADDR(8),
      Q => sel0(8),
      R => reset
    );
\waddr_reg[11]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => aw_transfer,
      D => AXI4_Lite_AWADDR(9),
      Q => sel0(9),
      R => reset
    );
\waddr_reg[12]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => aw_transfer,
      D => AXI4_Lite_AWADDR(10),
      Q => sel0(10),
      R => reset
    );
\waddr_reg[13]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => aw_transfer,
      D => AXI4_Lite_AWADDR(11),
      Q => sel0(11),
      R => reset
    );
\waddr_reg[14]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => aw_transfer,
      D => AXI4_Lite_AWADDR(12),
      Q => sel0(12),
      R => reset
    );
\waddr_reg[15]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => aw_transfer,
      D => AXI4_Lite_AWADDR(13),
      Q => sel0(13),
      R => reset
    );
\waddr_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => aw_transfer,
      D => AXI4_Lite_AWADDR(0),
      Q => sel0(0),
      R => reset
    );
\waddr_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => aw_transfer,
      D => AXI4_Lite_AWADDR(1),
      Q => sel0(1),
      R => reset
    );
\waddr_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => aw_transfer,
      D => AXI4_Lite_AWADDR(2),
      Q => sel0(2),
      R => reset
    );
\waddr_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => aw_transfer,
      D => AXI4_Lite_AWADDR(3),
      Q => sel0(3),
      R => reset
    );
\waddr_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => aw_transfer,
      D => AXI4_Lite_AWADDR(4),
      Q => sel0(4),
      R => reset
    );
\waddr_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => aw_transfer,
      D => AXI4_Lite_AWADDR(5),
      Q => sel0(5),
      R => reset
    );
\waddr_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => aw_transfer,
      D => AXI4_Lite_AWADDR(6),
      Q => sel0(6),
      R => reset
    );
\waddr_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => aw_transfer,
      D => AXI4_Lite_AWADDR(7),
      Q => sel0(7),
      R => reset
    );
\wdata[31]_i_1\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"8"
    )
        port map (
      I0 => AXI4_Lite_WVALID,
      I1 => \^fsm_onehot_axi_lite_wstate_reg[2]_0\(0),
      O => w_transfer
    );
\wdata_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => w_transfer,
      D => AXI4_Lite_WDATA(0),
      Q => \^wdata_reg[31]_0\(0),
      R => reset
    );
\wdata_reg[10]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => w_transfer,
      D => AXI4_Lite_WDATA(10),
      Q => \^wdata_reg[31]_0\(10),
      R => reset
    );
\wdata_reg[11]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => w_transfer,
      D => AXI4_Lite_WDATA(11),
      Q => \^wdata_reg[31]_0\(11),
      R => reset
    );
\wdata_reg[12]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => w_transfer,
      D => AXI4_Lite_WDATA(12),
      Q => \^wdata_reg[31]_0\(12),
      R => reset
    );
\wdata_reg[13]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => w_transfer,
      D => AXI4_Lite_WDATA(13),
      Q => \^wdata_reg[31]_0\(13),
      R => reset
    );
\wdata_reg[14]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => w_transfer,
      D => AXI4_Lite_WDATA(14),
      Q => \^wdata_reg[31]_0\(14),
      R => reset
    );
\wdata_reg[15]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => w_transfer,
      D => AXI4_Lite_WDATA(15),
      Q => \^wdata_reg[31]_0\(15),
      R => reset
    );
\wdata_reg[16]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => w_transfer,
      D => AXI4_Lite_WDATA(16),
      Q => \^wdata_reg[31]_0\(16),
      R => reset
    );
\wdata_reg[17]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => w_transfer,
      D => AXI4_Lite_WDATA(17),
      Q => \^wdata_reg[31]_0\(17),
      R => reset
    );
\wdata_reg[18]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => w_transfer,
      D => AXI4_Lite_WDATA(18),
      Q => \^wdata_reg[31]_0\(18),
      R => reset
    );
\wdata_reg[19]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => w_transfer,
      D => AXI4_Lite_WDATA(19),
      Q => \^wdata_reg[31]_0\(19),
      R => reset
    );
\wdata_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => w_transfer,
      D => AXI4_Lite_WDATA(1),
      Q => \^wdata_reg[31]_0\(1),
      R => reset
    );
\wdata_reg[20]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => w_transfer,
      D => AXI4_Lite_WDATA(20),
      Q => \^wdata_reg[31]_0\(20),
      R => reset
    );
\wdata_reg[21]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => w_transfer,
      D => AXI4_Lite_WDATA(21),
      Q => \^wdata_reg[31]_0\(21),
      R => reset
    );
\wdata_reg[22]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => w_transfer,
      D => AXI4_Lite_WDATA(22),
      Q => \^wdata_reg[31]_0\(22),
      R => reset
    );
\wdata_reg[23]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => w_transfer,
      D => AXI4_Lite_WDATA(23),
      Q => \^wdata_reg[31]_0\(23),
      R => reset
    );
\wdata_reg[24]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => w_transfer,
      D => AXI4_Lite_WDATA(24),
      Q => \^wdata_reg[31]_0\(24),
      R => reset
    );
\wdata_reg[25]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => w_transfer,
      D => AXI4_Lite_WDATA(25),
      Q => \^wdata_reg[31]_0\(25),
      R => reset
    );
\wdata_reg[26]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => w_transfer,
      D => AXI4_Lite_WDATA(26),
      Q => \^wdata_reg[31]_0\(26),
      R => reset
    );
\wdata_reg[27]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => w_transfer,
      D => AXI4_Lite_WDATA(27),
      Q => \^wdata_reg[31]_0\(27),
      R => reset
    );
\wdata_reg[28]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => w_transfer,
      D => AXI4_Lite_WDATA(28),
      Q => \^wdata_reg[31]_0\(28),
      R => reset
    );
\wdata_reg[29]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => w_transfer,
      D => AXI4_Lite_WDATA(29),
      Q => \^wdata_reg[31]_0\(29),
      R => reset
    );
\wdata_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => w_transfer,
      D => AXI4_Lite_WDATA(2),
      Q => \^wdata_reg[31]_0\(2),
      R => reset
    );
\wdata_reg[30]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => w_transfer,
      D => AXI4_Lite_WDATA(30),
      Q => \^wdata_reg[31]_0\(30),
      R => reset
    );
\wdata_reg[31]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => w_transfer,
      D => AXI4_Lite_WDATA(31),
      Q => \^wdata_reg[31]_0\(31),
      R => reset
    );
\wdata_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => w_transfer,
      D => AXI4_Lite_WDATA(3),
      Q => \^wdata_reg[31]_0\(3),
      R => reset
    );
\wdata_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => w_transfer,
      D => AXI4_Lite_WDATA(4),
      Q => \^wdata_reg[31]_0\(4),
      R => reset
    );
\wdata_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => w_transfer,
      D => AXI4_Lite_WDATA(5),
      Q => \^wdata_reg[31]_0\(5),
      R => reset
    );
\wdata_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => w_transfer,
      D => AXI4_Lite_WDATA(6),
      Q => \^wdata_reg[31]_0\(6),
      R => reset
    );
\wdata_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => w_transfer,
      D => AXI4_Lite_WDATA(7),
      Q => \^wdata_reg[31]_0\(7),
      R => reset
    );
\wdata_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => w_transfer,
      D => AXI4_Lite_WDATA(8),
      Q => \^wdata_reg[31]_0\(8),
      R => reset
    );
\wdata_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => w_transfer,
      D => AXI4_Lite_WDATA(9),
      Q => \^wdata_reg[31]_0\(9),
      R => reset
    );
wr_enb_1_i_1: unisim.vcomponents.LUT6
    generic map(
      INIT => X"8000000000000000"
    )
        port map (
      I0 => AXI4_Lite_WSTRB(2),
      I1 => AXI4_Lite_WSTRB(3),
      I2 => AXI4_Lite_WSTRB(0),
      I3 => AXI4_Lite_WSTRB(1),
      I4 => \^fsm_onehot_axi_lite_wstate_reg[2]_0\(0),
      I5 => AXI4_Lite_WVALID,
      O => w_transfer_and_wstrb
    );
wr_enb_1_reg: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => w_transfer_and_wstrb,
      Q => top_wr_enb,
      R => reset
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity zusys_mux_axi_ip_1_0_mux_axi_ip_reset_sync is
  port (
    SR : out STD_LOGIC_VECTOR ( 0 to 0 );
    reset_in : in STD_LOGIC;
    IPCORE_CLK : in STD_LOGIC;
    AXI4_Lite_ARESETN : in STD_LOGIC;
    IPCORE_RESETN : in STD_LOGIC;
    soft_reset : in STD_LOGIC
  );
  attribute ORIG_REF_NAME : string;
  attribute ORIG_REF_NAME of zusys_mux_axi_ip_1_0_mux_axi_ip_reset_sync : entity is "mux_axi_ip_reset_sync";
end zusys_mux_axi_ip_1_0_mux_axi_ip_reset_sync;

architecture STRUCTURE of zusys_mux_axi_ip_1_0_mux_axi_ip_reset_sync is
  signal reset_out_i_1_n_0 : STD_LOGIC;
  signal reset_pipe : STD_LOGIC;
begin
reset_out_i_1: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FFDF"
    )
        port map (
      I0 => AXI4_Lite_ARESETN,
      I1 => reset_pipe,
      I2 => IPCORE_RESETN,
      I3 => soft_reset,
      O => reset_out_i_1_n_0
    );
reset_out_reg: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => '1',
      D => reset_out_i_1_n_0,
      Q => SR(0),
      R => '0'
    );
reset_pipe_reg: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => '1',
      D => reset_in,
      Q => reset_pipe,
      R => '0'
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity zusys_mux_axi_ip_1_0_mux_axi_ip_src_Detect_Fall_Nonpositive2 is
  port (
    U_k_1_0 : out STD_LOGIC;
    U_k : out STD_LOGIC;
    SR : in STD_LOGIC_VECTOR ( 0 to 0 );
    E : in STD_LOGIC_VECTOR ( 0 to 0 );
    IPCORE_CLK : in STD_LOGIC;
    Q : in STD_LOGIC_VECTOR ( 7 downto 0 )
  );
  attribute ORIG_REF_NAME : string;
  attribute ORIG_REF_NAME of zusys_mux_axi_ip_1_0_mux_axi_ip_src_Detect_Fall_Nonpositive2 : entity is "mux_axi_ip_src_Detect_Fall_Nonpositive2";
end zusys_mux_axi_ip_1_0_mux_axi_ip_src_Detect_Fall_Nonpositive2;

architecture STRUCTURE of zusys_mux_axi_ip_1_0_mux_axi_ip_src_Detect_Fall_Nonpositive2 is
  signal \^u_k\ : STD_LOGIC;
  signal \interrupt_out_isr[7]_INST_0_i_2_n_0\ : STD_LOGIC;
begin
  U_k <= \^u_k\;
U_k_1_reg: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => \^u_k\,
      Q => U_k_1_0,
      R => SR(0)
    );
\interrupt_out_isr[7]_INST_0_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"00010000"
    )
        port map (
      I0 => Q(0),
      I1 => Q(1),
      I2 => Q(2),
      I3 => Q(3),
      I4 => \interrupt_out_isr[7]_INST_0_i_2_n_0\,
      O => \^u_k\
    );
\interrupt_out_isr[7]_INST_0_i_2\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"0001"
    )
        port map (
      I0 => Q(7),
      I1 => Q(6),
      I2 => Q(5),
      I3 => Q(4),
      O => \interrupt_out_isr[7]_INST_0_i_2_n_0\
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity zusys_mux_axi_ip_1_0_mux_axi_ip_src_Detect_Rise_Positive is
  port (
    U_k_1 : out STD_LOGIC;
    SR : in STD_LOGIC_VECTOR ( 0 to 0 );
    E : in STD_LOGIC_VECTOR ( 0 to 0 );
    interrupt_out_adc : in STD_LOGIC;
    IPCORE_CLK : in STD_LOGIC
  );
  attribute ORIG_REF_NAME : string;
  attribute ORIG_REF_NAME of zusys_mux_axi_ip_1_0_mux_axi_ip_src_Detect_Rise_Positive : entity is "mux_axi_ip_src_Detect_Rise_Positive";
end zusys_mux_axi_ip_1_0_mux_axi_ip_src_Detect_Rise_Positive;

architecture STRUCTURE of zusys_mux_axi_ip_1_0_mux_axi_ip_src_Detect_Rise_Positive is
begin
U_k_1_reg: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => interrupt_out_adc,
      Q => U_k_1,
      R => SR(0)
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity zusys_mux_axi_ip_1_0_mux_axi_ip_axi_lite is
  port (
    FSM_sequential_axi_lite_rstate_reg : out STD_LOGIC;
    write_axi_enable : out STD_LOGIC;
    soft_reset : out STD_LOGIC;
    S : out STD_LOGIC_VECTOR ( 7 downto 0 );
    Q : out STD_LOGIC_VECTOR ( 7 downto 0 );
    \data_reg_select_n_th_adc_interrupt_1_1_reg[30]\ : out STD_LOGIC_VECTOR ( 7 downto 0 );
    \data_reg_select_AXI_1_1_reg[3]\ : out STD_LOGIC_VECTOR ( 3 downto 0 );
    AXI4_Lite_ARREADY : out STD_LOGIC;
    \FSM_onehot_axi_lite_wstate_reg[2]\ : out STD_LOGIC_VECTOR ( 1 downto 0 );
    AXI4_Lite_AWREADY : out STD_LOGIC;
    interrupt_out_isr : out STD_LOGIC_VECTOR ( 7 downto 0 );
    interrupt_out_adc : out STD_LOGIC;
    Detect_Rise_Positive_out1 : out STD_LOGIC;
    E : out STD_LOGIC_VECTOR ( 0 to 0 );
    data_reg_axi_enable_1_1_reg : out STD_LOGIC_VECTOR ( 0 to 0 );
    reset_in : out STD_LOGIC;
    AXI4_Lite_RDATA : out STD_LOGIC_VECTOR ( 31 downto 0 );
    AXI4_Lite_ACLK : in STD_LOGIC;
    SR : in STD_LOGIC_VECTOR ( 0 to 0 );
    AXI4_Lite_ARADDR : in STD_LOGIC_VECTOR ( 13 downto 0 );
    AXI4_Lite_ARVALID : in STD_LOGIC;
    AXI4_Lite_RREADY : in STD_LOGIC;
    AXI4_Lite_AWVALID : in STD_LOGIC;
    AXI4_Lite_WVALID : in STD_LOGIC;
    AXI4_Lite_ARESETN : in STD_LOGIC;
    U_k_1 : in STD_LOGIC;
    U_k : in STD_LOGIC;
    U_k_1_0 : in STD_LOGIC;
    interrupts_in : in STD_LOGIC_VECTOR ( 7 downto 0 );
    PipelineDelay_out1 : in STD_LOGIC;
    CO : in STD_LOGIC_VECTOR ( 0 to 0 );
    IPCORE_RESETN : in STD_LOGIC;
    \HDL_Counter_out10_inferred__0/i__carry\ : in STD_LOGIC_VECTOR ( 7 downto 0 );
    AXI4_Lite_BREADY : in STD_LOGIC;
    AXI4_Lite_WSTRB : in STD_LOGIC_VECTOR ( 3 downto 0 );
    AXI4_Lite_AWADDR : in STD_LOGIC_VECTOR ( 13 downto 0 );
    AXI4_Lite_WDATA : in STD_LOGIC_VECTOR ( 31 downto 0 )
  );
  attribute ORIG_REF_NAME : string;
  attribute ORIG_REF_NAME of zusys_mux_axi_ip_1_0_mux_axi_ip_axi_lite : entity is "mux_axi_ip_axi_lite";
end zusys_mux_axi_ip_1_0_mux_axi_ip_axi_lite;

architecture STRUCTURE of zusys_mux_axi_ip_1_0_mux_axi_ip_axi_lite is
  signal \^q\ : STD_LOGIC_VECTOR ( 7 downto 0 );
  signal data_read : STD_LOGIC_VECTOR ( 31 downto 1 );
  signal \^data_reg_select_axi_1_1_reg[3]\ : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal n_th_adc_interrupt : STD_LOGIC_VECTOR ( 30 downto 10 );
  signal p_0_in : STD_LOGIC_VECTOR ( 26 downto 1 );
  signal read_reg_ip_timestamp : STD_LOGIC_VECTOR ( 30 to 30 );
  signal reg_enb_select_AXI_1_1 : STD_LOGIC;
  signal reg_enb_select_n_th_adc_interrupt_1_1 : STD_LOGIC;
  signal u_mux_axi_ip_axi_lite_module_inst_n_11 : STD_LOGIC;
  signal u_mux_axi_ip_axi_lite_module_inst_n_12 : STD_LOGIC;
  signal u_mux_axi_ip_axi_lite_module_inst_n_13 : STD_LOGIC;
  signal u_mux_axi_ip_axi_lite_module_inst_n_14 : STD_LOGIC;
  signal u_mux_axi_ip_axi_lite_module_inst_n_15 : STD_LOGIC;
  signal u_mux_axi_ip_axi_lite_module_inst_n_16 : STD_LOGIC;
  signal u_mux_axi_ip_axi_lite_module_inst_n_17 : STD_LOGIC;
  signal u_mux_axi_ip_axi_lite_module_inst_n_18 : STD_LOGIC;
  signal u_mux_axi_ip_axi_lite_module_inst_n_19 : STD_LOGIC;
  signal u_mux_axi_ip_axi_lite_module_inst_n_2 : STD_LOGIC;
  signal u_mux_axi_ip_axi_lite_module_inst_n_20 : STD_LOGIC;
  signal u_mux_axi_ip_axi_lite_module_inst_n_21 : STD_LOGIC;
  signal u_mux_axi_ip_axi_lite_module_inst_n_22 : STD_LOGIC;
  signal u_mux_axi_ip_axi_lite_module_inst_n_23 : STD_LOGIC;
  signal u_mux_axi_ip_axi_lite_module_inst_n_24 : STD_LOGIC;
  signal u_mux_axi_ip_axi_lite_module_inst_n_25 : STD_LOGIC;
  signal u_mux_axi_ip_axi_lite_module_inst_n_26 : STD_LOGIC;
  signal u_mux_axi_ip_axi_lite_module_inst_n_27 : STD_LOGIC;
  signal u_mux_axi_ip_axi_lite_module_inst_n_28 : STD_LOGIC;
  signal u_mux_axi_ip_axi_lite_module_inst_n_29 : STD_LOGIC;
  signal u_mux_axi_ip_axi_lite_module_inst_n_3 : STD_LOGIC;
  signal u_mux_axi_ip_axi_lite_module_inst_n_30 : STD_LOGIC;
  signal u_mux_axi_ip_axi_lite_module_inst_n_31 : STD_LOGIC;
  signal u_mux_axi_ip_axi_lite_module_inst_n_32 : STD_LOGIC;
  signal u_mux_axi_ip_axi_lite_module_inst_n_33 : STD_LOGIC;
  signal u_mux_axi_ip_axi_lite_module_inst_n_34 : STD_LOGIC;
  signal u_mux_axi_ip_axi_lite_module_inst_n_35 : STD_LOGIC;
  signal u_mux_axi_ip_axi_lite_module_inst_n_36 : STD_LOGIC;
  signal u_mux_axi_ip_axi_lite_module_inst_n_37 : STD_LOGIC;
  signal u_mux_axi_ip_axi_lite_module_inst_n_38 : STD_LOGIC;
  signal u_mux_axi_ip_axi_lite_module_inst_n_39 : STD_LOGIC;
  signal u_mux_axi_ip_axi_lite_module_inst_n_40 : STD_LOGIC;
  signal u_mux_axi_ip_axi_lite_module_inst_n_41 : STD_LOGIC;
  signal u_mux_axi_ip_axi_lite_module_inst_n_42 : STD_LOGIC;
  signal u_mux_axi_ip_axi_lite_module_inst_n_43 : STD_LOGIC;
  signal \^write_axi_enable\ : STD_LOGIC;
begin
  Q(7 downto 0) <= \^q\(7 downto 0);
  \data_reg_select_AXI_1_1_reg[3]\(3 downto 0) <= \^data_reg_select_axi_1_1_reg[3]\(3 downto 0);
  write_axi_enable <= \^write_axi_enable\;
u_mux_axi_ip_addr_decoder_inst: entity work.zusys_mux_axi_ip_1_0_mux_axi_ip_addr_decoder
     port map (
      AXI4_Lite_ACLK => AXI4_Lite_ACLK,
      \AXI4_Lite_RDATA_tmp_reg[1]\ => u_mux_axi_ip_axi_lite_module_inst_n_2,
      \AXI4_Lite_RDATA_tmp_reg[1]_0\ => u_mux_axi_ip_axi_lite_module_inst_n_3,
      CO(0) => CO(0),
      D(16) => data_read(31),
      D(15) => data_read(25),
      D(14 downto 12) => data_read(21 downto 19),
      D(11) => data_read(15),
      D(10 downto 8) => data_read(13 downto 11),
      D(7 downto 4) => data_read(9 downto 6),
      D(3 downto 0) => data_read(4 downto 1),
      Detect_Rise_Positive_out1 => Detect_Rise_Positive_out1,
      E(0) => E(0),
      \HDL_Counter_out10_inferred__0/i__carry\(7 downto 0) => \HDL_Counter_out10_inferred__0/i__carry\(7 downto 0),
      PipelineDelay_out1 => PipelineDelay_out1,
      Q(20 downto 16) => n_th_adc_interrupt(30 downto 26),
      Q(15 downto 13) => n_th_adc_interrupt(24 downto 22),
      Q(12 downto 10) => n_th_adc_interrupt(18 downto 16),
      Q(9) => n_th_adc_interrupt(14),
      Q(8) => n_th_adc_interrupt(10),
      Q(7 downto 0) => \^q\(7 downto 0),
      S(7 downto 0) => S(7 downto 0),
      SR(0) => SR(0),
      U_k => U_k,
      U_k_1 => U_k_1,
      U_k_1_0 => U_k_1_0,
      data_reg_axi_enable_1_1_reg_0 => \^write_axi_enable\,
      data_reg_axi_enable_1_1_reg_1(0) => data_reg_axi_enable_1_1_reg(0),
      data_reg_axi_enable_1_1_reg_2 => u_mux_axi_ip_axi_lite_module_inst_n_43,
      \data_reg_select_AXI_1_1_reg[30]_0\(17) => p_0_in(1),
      \data_reg_select_AXI_1_1_reg[30]_0\(16) => p_0_in(2),
      \data_reg_select_AXI_1_1_reg[30]_0\(15) => p_0_in(3),
      \data_reg_select_AXI_1_1_reg[30]_0\(14) => p_0_in(4),
      \data_reg_select_AXI_1_1_reg[30]_0\(13) => p_0_in(5),
      \data_reg_select_AXI_1_1_reg[30]_0\(12) => p_0_in(7),
      \data_reg_select_AXI_1_1_reg[30]_0\(11) => p_0_in(8),
      \data_reg_select_AXI_1_1_reg[30]_0\(10) => p_0_in(9),
      \data_reg_select_AXI_1_1_reg[30]_0\(9) => p_0_in(13),
      \data_reg_select_AXI_1_1_reg[30]_0\(8) => p_0_in(14),
      \data_reg_select_AXI_1_1_reg[30]_0\(7) => p_0_in(15),
      \data_reg_select_AXI_1_1_reg[30]_0\(6) => p_0_in(17),
      \data_reg_select_AXI_1_1_reg[30]_0\(5) => p_0_in(21),
      \data_reg_select_AXI_1_1_reg[30]_0\(4) => p_0_in(26),
      \data_reg_select_AXI_1_1_reg[30]_0\(3 downto 0) => \^data_reg_select_axi_1_1_reg[3]\(3 downto 0),
      \data_reg_select_AXI_1_1_reg[31]_0\(0) => reg_enb_select_AXI_1_1,
      \data_reg_select_n_th_adc_interrupt_1_1_reg[30]_0\(7 downto 0) => \data_reg_select_n_th_adc_interrupt_1_1_reg[30]\(7 downto 0),
      \data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0\(31) => u_mux_axi_ip_axi_lite_module_inst_n_11,
      \data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0\(30) => u_mux_axi_ip_axi_lite_module_inst_n_12,
      \data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0\(29) => u_mux_axi_ip_axi_lite_module_inst_n_13,
      \data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0\(28) => u_mux_axi_ip_axi_lite_module_inst_n_14,
      \data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0\(27) => u_mux_axi_ip_axi_lite_module_inst_n_15,
      \data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0\(26) => u_mux_axi_ip_axi_lite_module_inst_n_16,
      \data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0\(25) => u_mux_axi_ip_axi_lite_module_inst_n_17,
      \data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0\(24) => u_mux_axi_ip_axi_lite_module_inst_n_18,
      \data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0\(23) => u_mux_axi_ip_axi_lite_module_inst_n_19,
      \data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0\(22) => u_mux_axi_ip_axi_lite_module_inst_n_20,
      \data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0\(21) => u_mux_axi_ip_axi_lite_module_inst_n_21,
      \data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0\(20) => u_mux_axi_ip_axi_lite_module_inst_n_22,
      \data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0\(19) => u_mux_axi_ip_axi_lite_module_inst_n_23,
      \data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0\(18) => u_mux_axi_ip_axi_lite_module_inst_n_24,
      \data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0\(17) => u_mux_axi_ip_axi_lite_module_inst_n_25,
      \data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0\(16) => u_mux_axi_ip_axi_lite_module_inst_n_26,
      \data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0\(15) => u_mux_axi_ip_axi_lite_module_inst_n_27,
      \data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0\(14) => u_mux_axi_ip_axi_lite_module_inst_n_28,
      \data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0\(13) => u_mux_axi_ip_axi_lite_module_inst_n_29,
      \data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0\(12) => u_mux_axi_ip_axi_lite_module_inst_n_30,
      \data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0\(11) => u_mux_axi_ip_axi_lite_module_inst_n_31,
      \data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0\(10) => u_mux_axi_ip_axi_lite_module_inst_n_32,
      \data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0\(9) => u_mux_axi_ip_axi_lite_module_inst_n_33,
      \data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0\(8) => u_mux_axi_ip_axi_lite_module_inst_n_34,
      \data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0\(7) => u_mux_axi_ip_axi_lite_module_inst_n_35,
      \data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0\(6) => u_mux_axi_ip_axi_lite_module_inst_n_36,
      \data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0\(5) => u_mux_axi_ip_axi_lite_module_inst_n_37,
      \data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0\(4) => u_mux_axi_ip_axi_lite_module_inst_n_38,
      \data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0\(3) => u_mux_axi_ip_axi_lite_module_inst_n_39,
      \data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0\(2) => u_mux_axi_ip_axi_lite_module_inst_n_40,
      \data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0\(1) => u_mux_axi_ip_axi_lite_module_inst_n_41,
      \data_reg_select_n_th_adc_interrupt_1_1_reg[31]_0\(0) => u_mux_axi_ip_axi_lite_module_inst_n_42,
      \data_reg_select_n_th_adc_interrupt_1_1_reg[31]_1\(0) => reg_enb_select_n_th_adc_interrupt_1_1,
      interrupt_out_adc => interrupt_out_adc,
      interrupt_out_isr(7 downto 0) => interrupt_out_isr(7 downto 0),
      interrupts_in(7 downto 0) => interrupts_in(7 downto 0),
      read_reg_ip_timestamp(0) => read_reg_ip_timestamp(30)
    );
u_mux_axi_ip_axi_lite_module_inst: entity work.zusys_mux_axi_ip_1_0_mux_axi_ip_axi_lite_module
     port map (
      AXI4_Lite_ACLK => AXI4_Lite_ACLK,
      AXI4_Lite_ARADDR(13 downto 0) => AXI4_Lite_ARADDR(13 downto 0),
      AXI4_Lite_ARADDR_2_sp_1 => u_mux_axi_ip_axi_lite_module_inst_n_3,
      AXI4_Lite_ARADDR_8_sp_1 => u_mux_axi_ip_axi_lite_module_inst_n_2,
      AXI4_Lite_ARESETN => AXI4_Lite_ARESETN,
      AXI4_Lite_ARREADY => AXI4_Lite_ARREADY,
      AXI4_Lite_ARVALID => AXI4_Lite_ARVALID,
      AXI4_Lite_AWADDR(13 downto 0) => AXI4_Lite_AWADDR(13 downto 0),
      AXI4_Lite_AWREADY => AXI4_Lite_AWREADY,
      AXI4_Lite_AWVALID => AXI4_Lite_AWVALID,
      AXI4_Lite_BREADY => AXI4_Lite_BREADY,
      AXI4_Lite_RDATA(31 downto 0) => AXI4_Lite_RDATA(31 downto 0),
      \AXI4_Lite_RDATA_tmp_reg[30]_0\(14) => p_0_in(1),
      \AXI4_Lite_RDATA_tmp_reg[30]_0\(13) => p_0_in(2),
      \AXI4_Lite_RDATA_tmp_reg[30]_0\(12) => p_0_in(3),
      \AXI4_Lite_RDATA_tmp_reg[30]_0\(11) => p_0_in(4),
      \AXI4_Lite_RDATA_tmp_reg[30]_0\(10) => p_0_in(5),
      \AXI4_Lite_RDATA_tmp_reg[30]_0\(9) => p_0_in(7),
      \AXI4_Lite_RDATA_tmp_reg[30]_0\(8) => p_0_in(8),
      \AXI4_Lite_RDATA_tmp_reg[30]_0\(7) => p_0_in(9),
      \AXI4_Lite_RDATA_tmp_reg[30]_0\(6) => p_0_in(13),
      \AXI4_Lite_RDATA_tmp_reg[30]_0\(5) => p_0_in(14),
      \AXI4_Lite_RDATA_tmp_reg[30]_0\(4) => p_0_in(15),
      \AXI4_Lite_RDATA_tmp_reg[30]_0\(3) => p_0_in(17),
      \AXI4_Lite_RDATA_tmp_reg[30]_0\(2) => p_0_in(21),
      \AXI4_Lite_RDATA_tmp_reg[30]_0\(1) => p_0_in(26),
      \AXI4_Lite_RDATA_tmp_reg[30]_0\(0) => \^data_reg_select_axi_1_1_reg[3]\(0),
      AXI4_Lite_RREADY => AXI4_Lite_RREADY,
      AXI4_Lite_WDATA(31 downto 0) => AXI4_Lite_WDATA(31 downto 0),
      AXI4_Lite_WSTRB(3 downto 0) => AXI4_Lite_WSTRB(3 downto 0),
      AXI4_Lite_WVALID => AXI4_Lite_WVALID,
      D(16) => data_read(31),
      D(15) => data_read(25),
      D(14 downto 12) => data_read(21 downto 19),
      D(11) => data_read(15),
      D(10 downto 8) => data_read(13 downto 11),
      D(7 downto 4) => data_read(9 downto 6),
      D(3 downto 0) => data_read(4 downto 1),
      \FSM_onehot_axi_lite_wstate_reg[2]_0\(1 downto 0) => \FSM_onehot_axi_lite_wstate_reg[2]\(1 downto 0),
      FSM_sequential_axi_lite_rstate_reg_0 => FSM_sequential_axi_lite_rstate_reg,
      IPCORE_RESETN => IPCORE_RESETN,
      Q(14 downto 10) => n_th_adc_interrupt(30 downto 26),
      Q(9 downto 7) => n_th_adc_interrupt(24 downto 22),
      Q(6 downto 4) => n_th_adc_interrupt(18 downto 16),
      Q(3) => n_th_adc_interrupt(14),
      Q(2) => n_th_adc_interrupt(10),
      Q(1) => \^q\(5),
      Q(0) => \^q\(0),
      read_reg_ip_timestamp(0) => read_reg_ip_timestamp(30),
      reset_in => reset_in,
      soft_reset => soft_reset,
      \wdata_reg[0]_0\ => u_mux_axi_ip_axi_lite_module_inst_n_43,
      \wdata_reg[31]_0\(31) => u_mux_axi_ip_axi_lite_module_inst_n_11,
      \wdata_reg[31]_0\(30) => u_mux_axi_ip_axi_lite_module_inst_n_12,
      \wdata_reg[31]_0\(29) => u_mux_axi_ip_axi_lite_module_inst_n_13,
      \wdata_reg[31]_0\(28) => u_mux_axi_ip_axi_lite_module_inst_n_14,
      \wdata_reg[31]_0\(27) => u_mux_axi_ip_axi_lite_module_inst_n_15,
      \wdata_reg[31]_0\(26) => u_mux_axi_ip_axi_lite_module_inst_n_16,
      \wdata_reg[31]_0\(25) => u_mux_axi_ip_axi_lite_module_inst_n_17,
      \wdata_reg[31]_0\(24) => u_mux_axi_ip_axi_lite_module_inst_n_18,
      \wdata_reg[31]_0\(23) => u_mux_axi_ip_axi_lite_module_inst_n_19,
      \wdata_reg[31]_0\(22) => u_mux_axi_ip_axi_lite_module_inst_n_20,
      \wdata_reg[31]_0\(21) => u_mux_axi_ip_axi_lite_module_inst_n_21,
      \wdata_reg[31]_0\(20) => u_mux_axi_ip_axi_lite_module_inst_n_22,
      \wdata_reg[31]_0\(19) => u_mux_axi_ip_axi_lite_module_inst_n_23,
      \wdata_reg[31]_0\(18) => u_mux_axi_ip_axi_lite_module_inst_n_24,
      \wdata_reg[31]_0\(17) => u_mux_axi_ip_axi_lite_module_inst_n_25,
      \wdata_reg[31]_0\(16) => u_mux_axi_ip_axi_lite_module_inst_n_26,
      \wdata_reg[31]_0\(15) => u_mux_axi_ip_axi_lite_module_inst_n_27,
      \wdata_reg[31]_0\(14) => u_mux_axi_ip_axi_lite_module_inst_n_28,
      \wdata_reg[31]_0\(13) => u_mux_axi_ip_axi_lite_module_inst_n_29,
      \wdata_reg[31]_0\(12) => u_mux_axi_ip_axi_lite_module_inst_n_30,
      \wdata_reg[31]_0\(11) => u_mux_axi_ip_axi_lite_module_inst_n_31,
      \wdata_reg[31]_0\(10) => u_mux_axi_ip_axi_lite_module_inst_n_32,
      \wdata_reg[31]_0\(9) => u_mux_axi_ip_axi_lite_module_inst_n_33,
      \wdata_reg[31]_0\(8) => u_mux_axi_ip_axi_lite_module_inst_n_34,
      \wdata_reg[31]_0\(7) => u_mux_axi_ip_axi_lite_module_inst_n_35,
      \wdata_reg[31]_0\(6) => u_mux_axi_ip_axi_lite_module_inst_n_36,
      \wdata_reg[31]_0\(5) => u_mux_axi_ip_axi_lite_module_inst_n_37,
      \wdata_reg[31]_0\(4) => u_mux_axi_ip_axi_lite_module_inst_n_38,
      \wdata_reg[31]_0\(3) => u_mux_axi_ip_axi_lite_module_inst_n_39,
      \wdata_reg[31]_0\(2) => u_mux_axi_ip_axi_lite_module_inst_n_40,
      \wdata_reg[31]_0\(1) => u_mux_axi_ip_axi_lite_module_inst_n_41,
      \wdata_reg[31]_0\(0) => u_mux_axi_ip_axi_lite_module_inst_n_42,
      wr_enb_1_reg_0(0) => reg_enb_select_n_th_adc_interrupt_1_1,
      wr_enb_1_reg_1(0) => reg_enb_select_AXI_1_1,
      write_axi_enable => \^write_axi_enable\
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity zusys_mux_axi_ip_1_0_mux_axi_ip_src_Subsystem1 is
  port (
    U_k_1 : out STD_LOGIC;
    U_k_1_0 : out STD_LOGIC;
    U_k : out STD_LOGIC;
    PipelineDelay_out1 : out STD_LOGIC;
    CO : out STD_LOGIC_VECTOR ( 0 to 0 );
    Q : out STD_LOGIC_VECTOR ( 7 downto 0 );
    SR : in STD_LOGIC_VECTOR ( 0 to 0 );
    E : in STD_LOGIC_VECTOR ( 0 to 0 );
    interrupt_out_adc : in STD_LOGIC;
    IPCORE_CLK : in STD_LOGIC;
    Detect_Rise_Positive_out1 : in STD_LOGIC;
    S : in STD_LOGIC_VECTOR ( 7 downto 0 );
    \HDL_Counter_out1_reg[7]_0\ : in STD_LOGIC_VECTOR ( 7 downto 0 );
    \HDL_Counter_out10_inferred__0/i__carry_0\ : in STD_LOGIC_VECTOR ( 7 downto 0 );
    \HDL_Counter_out1_reg[7]_1\ : in STD_LOGIC_VECTOR ( 0 to 0 );
    \HDL_Counter_out1_reg[7]_2\ : in STD_LOGIC_VECTOR ( 0 to 0 )
  );
  attribute ORIG_REF_NAME : string;
  attribute ORIG_REF_NAME of zusys_mux_axi_ip_1_0_mux_axi_ip_src_Subsystem1 : entity is "mux_axi_ip_src_Subsystem1";
end zusys_mux_axi_ip_1_0_mux_axi_ip_src_Subsystem1;

architecture STRUCTURE of zusys_mux_axi_ip_1_0_mux_axi_ip_src_Subsystem1 is
  signal \HDL_Counter_out10_inferred__0/i__carry__0_n_1\ : STD_LOGIC;
  signal \HDL_Counter_out10_inferred__0/i__carry__0_n_2\ : STD_LOGIC;
  signal \HDL_Counter_out10_inferred__0/i__carry__0_n_3\ : STD_LOGIC;
  signal \HDL_Counter_out10_inferred__0/i__carry__0_n_4\ : STD_LOGIC;
  signal \HDL_Counter_out10_inferred__0/i__carry__0_n_5\ : STD_LOGIC;
  signal \HDL_Counter_out10_inferred__0/i__carry__0_n_6\ : STD_LOGIC;
  signal \HDL_Counter_out10_inferred__0/i__carry__0_n_7\ : STD_LOGIC;
  signal \HDL_Counter_out10_inferred__0/i__carry_n_0\ : STD_LOGIC;
  signal \HDL_Counter_out10_inferred__0/i__carry_n_1\ : STD_LOGIC;
  signal \HDL_Counter_out10_inferred__0/i__carry_n_2\ : STD_LOGIC;
  signal \HDL_Counter_out10_inferred__0/i__carry_n_3\ : STD_LOGIC;
  signal \HDL_Counter_out10_inferred__0/i__carry_n_4\ : STD_LOGIC;
  signal \HDL_Counter_out10_inferred__0/i__carry_n_5\ : STD_LOGIC;
  signal \HDL_Counter_out10_inferred__0/i__carry_n_6\ : STD_LOGIC;
  signal \HDL_Counter_out10_inferred__0/i__carry_n_7\ : STD_LOGIC;
  signal \HDL_Counter_out1[7]_i_4_n_0\ : STD_LOGIC;
  signal HDL_Counter_out1_reg : STD_LOGIC_VECTOR ( 7 downto 0 );
  signal \^q\ : STD_LOGIC_VECTOR ( 7 downto 0 );
  signal \i__carry_i_1_n_0\ : STD_LOGIC;
  signal \i__carry_i_2_n_0\ : STD_LOGIC;
  signal \i__carry_i_3_n_0\ : STD_LOGIC;
  signal \i__carry_i_4_n_0\ : STD_LOGIC;
  signal \p_0_in__0\ : STD_LOGIC_VECTOR ( 7 downto 0 );
  signal \NLW_HDL_Counter_out10_inferred__0/i__carry_O_UNCONNECTED\ : STD_LOGIC_VECTOR ( 7 downto 0 );
  signal \NLW_HDL_Counter_out10_inferred__0/i__carry__0_O_UNCONNECTED\ : STD_LOGIC_VECTOR ( 7 downto 0 );
  attribute COMPARATOR_THRESHOLD : integer;
  attribute COMPARATOR_THRESHOLD of \HDL_Counter_out10_inferred__0/i__carry\ : label is 11;
  attribute COMPARATOR_THRESHOLD of \HDL_Counter_out10_inferred__0/i__carry__0\ : label is 11;
  attribute SOFT_HLUTNM : string;
  attribute SOFT_HLUTNM of \HDL_Counter_out1[1]_i_1\ : label is "soft_lutpair7";
  attribute SOFT_HLUTNM of \HDL_Counter_out1[2]_i_1\ : label is "soft_lutpair7";
  attribute SOFT_HLUTNM of \HDL_Counter_out1[3]_i_1\ : label is "soft_lutpair6";
  attribute SOFT_HLUTNM of \HDL_Counter_out1[4]_i_1\ : label is "soft_lutpair6";
  attribute SOFT_HLUTNM of \HDL_Counter_out1[6]_i_1\ : label is "soft_lutpair8";
  attribute SOFT_HLUTNM of \HDL_Counter_out1[7]_i_3\ : label is "soft_lutpair8";
begin
  Q(7 downto 0) <= \^q\(7 downto 0);
\Delay_out1_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => HDL_Counter_out1_reg(0),
      Q => \^q\(0),
      R => SR(0)
    );
\Delay_out1_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => HDL_Counter_out1_reg(1),
      Q => \^q\(1),
      R => SR(0)
    );
\Delay_out1_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => HDL_Counter_out1_reg(2),
      Q => \^q\(2),
      R => SR(0)
    );
\Delay_out1_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => HDL_Counter_out1_reg(3),
      Q => \^q\(3),
      R => SR(0)
    );
\Delay_out1_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => HDL_Counter_out1_reg(4),
      Q => \^q\(4),
      R => SR(0)
    );
\Delay_out1_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => HDL_Counter_out1_reg(5),
      Q => \^q\(5),
      R => SR(0)
    );
\Delay_out1_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => HDL_Counter_out1_reg(6),
      Q => \^q\(6),
      R => SR(0)
    );
\Delay_out1_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => HDL_Counter_out1_reg(7),
      Q => \^q\(7),
      R => SR(0)
    );
\HDL_Counter_out10_inferred__0/i__carry\: unisim.vcomponents.CARRY8
     port map (
      CI => '1',
      CI_TOP => '0',
      CO(7) => \HDL_Counter_out10_inferred__0/i__carry_n_0\,
      CO(6) => \HDL_Counter_out10_inferred__0/i__carry_n_1\,
      CO(5) => \HDL_Counter_out10_inferred__0/i__carry_n_2\,
      CO(4) => \HDL_Counter_out10_inferred__0/i__carry_n_3\,
      CO(3) => \HDL_Counter_out10_inferred__0/i__carry_n_4\,
      CO(2) => \HDL_Counter_out10_inferred__0/i__carry_n_5\,
      CO(1) => \HDL_Counter_out10_inferred__0/i__carry_n_6\,
      CO(0) => \HDL_Counter_out10_inferred__0/i__carry_n_7\,
      DI(7 downto 4) => B"0000",
      DI(3) => \i__carry_i_1_n_0\,
      DI(2) => \i__carry_i_2_n_0\,
      DI(1) => \i__carry_i_3_n_0\,
      DI(0) => \i__carry_i_4_n_0\,
      O(7 downto 0) => \NLW_HDL_Counter_out10_inferred__0/i__carry_O_UNCONNECTED\(7 downto 0),
      S(7 downto 0) => S(7 downto 0)
    );
\HDL_Counter_out10_inferred__0/i__carry__0\: unisim.vcomponents.CARRY8
     port map (
      CI => \HDL_Counter_out10_inferred__0/i__carry_n_0\,
      CI_TOP => '0',
      CO(7) => CO(0),
      CO(6) => \HDL_Counter_out10_inferred__0/i__carry__0_n_1\,
      CO(5) => \HDL_Counter_out10_inferred__0/i__carry__0_n_2\,
      CO(4) => \HDL_Counter_out10_inferred__0/i__carry__0_n_3\,
      CO(3) => \HDL_Counter_out10_inferred__0/i__carry__0_n_4\,
      CO(2) => \HDL_Counter_out10_inferred__0/i__carry__0_n_5\,
      CO(1) => \HDL_Counter_out10_inferred__0/i__carry__0_n_6\,
      CO(0) => \HDL_Counter_out10_inferred__0/i__carry__0_n_7\,
      DI(7 downto 0) => B"00000000",
      O(7 downto 0) => \NLW_HDL_Counter_out10_inferred__0/i__carry__0_O_UNCONNECTED\(7 downto 0),
      S(7 downto 0) => \HDL_Counter_out1_reg[7]_0\(7 downto 0)
    );
\HDL_Counter_out1[0]_i_1\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => HDL_Counter_out1_reg(0),
      O => \p_0_in__0\(0)
    );
\HDL_Counter_out1[1]_i_1\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"6"
    )
        port map (
      I0 => HDL_Counter_out1_reg(0),
      I1 => HDL_Counter_out1_reg(1),
      O => \p_0_in__0\(1)
    );
\HDL_Counter_out1[2]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"78"
    )
        port map (
      I0 => HDL_Counter_out1_reg(1),
      I1 => HDL_Counter_out1_reg(0),
      I2 => HDL_Counter_out1_reg(2),
      O => \p_0_in__0\(2)
    );
\HDL_Counter_out1[3]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"7F80"
    )
        port map (
      I0 => HDL_Counter_out1_reg(2),
      I1 => HDL_Counter_out1_reg(0),
      I2 => HDL_Counter_out1_reg(1),
      I3 => HDL_Counter_out1_reg(3),
      O => \p_0_in__0\(3)
    );
\HDL_Counter_out1[4]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"7FFF8000"
    )
        port map (
      I0 => HDL_Counter_out1_reg(3),
      I1 => HDL_Counter_out1_reg(1),
      I2 => HDL_Counter_out1_reg(0),
      I3 => HDL_Counter_out1_reg(2),
      I4 => HDL_Counter_out1_reg(4),
      O => \p_0_in__0\(4)
    );
\HDL_Counter_out1[5]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"7FFFFFFF80000000"
    )
        port map (
      I0 => HDL_Counter_out1_reg(4),
      I1 => HDL_Counter_out1_reg(2),
      I2 => HDL_Counter_out1_reg(0),
      I3 => HDL_Counter_out1_reg(1),
      I4 => HDL_Counter_out1_reg(3),
      I5 => HDL_Counter_out1_reg(5),
      O => \p_0_in__0\(5)
    );
\HDL_Counter_out1[6]_i_1\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"9"
    )
        port map (
      I0 => \HDL_Counter_out1[7]_i_4_n_0\,
      I1 => HDL_Counter_out1_reg(6),
      O => \p_0_in__0\(6)
    );
\HDL_Counter_out1[7]_i_3\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"D2"
    )
        port map (
      I0 => HDL_Counter_out1_reg(6),
      I1 => \HDL_Counter_out1[7]_i_4_n_0\,
      I2 => HDL_Counter_out1_reg(7),
      O => \p_0_in__0\(7)
    );
\HDL_Counter_out1[7]_i_4\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"7FFFFFFFFFFFFFFF"
    )
        port map (
      I0 => HDL_Counter_out1_reg(4),
      I1 => HDL_Counter_out1_reg(2),
      I2 => HDL_Counter_out1_reg(0),
      I3 => HDL_Counter_out1_reg(1),
      I4 => HDL_Counter_out1_reg(3),
      I5 => HDL_Counter_out1_reg(5),
      O => \HDL_Counter_out1[7]_i_4_n_0\
    );
\HDL_Counter_out1_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => \HDL_Counter_out1_reg[7]_2\(0),
      D => \p_0_in__0\(0),
      Q => HDL_Counter_out1_reg(0),
      R => \HDL_Counter_out1_reg[7]_1\(0)
    );
\HDL_Counter_out1_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => \HDL_Counter_out1_reg[7]_2\(0),
      D => \p_0_in__0\(1),
      Q => HDL_Counter_out1_reg(1),
      R => \HDL_Counter_out1_reg[7]_1\(0)
    );
\HDL_Counter_out1_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => \HDL_Counter_out1_reg[7]_2\(0),
      D => \p_0_in__0\(2),
      Q => HDL_Counter_out1_reg(2),
      R => \HDL_Counter_out1_reg[7]_1\(0)
    );
\HDL_Counter_out1_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => \HDL_Counter_out1_reg[7]_2\(0),
      D => \p_0_in__0\(3),
      Q => HDL_Counter_out1_reg(3),
      R => \HDL_Counter_out1_reg[7]_1\(0)
    );
\HDL_Counter_out1_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => \HDL_Counter_out1_reg[7]_2\(0),
      D => \p_0_in__0\(4),
      Q => HDL_Counter_out1_reg(4),
      R => \HDL_Counter_out1_reg[7]_1\(0)
    );
\HDL_Counter_out1_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => \HDL_Counter_out1_reg[7]_2\(0),
      D => \p_0_in__0\(5),
      Q => HDL_Counter_out1_reg(5),
      R => \HDL_Counter_out1_reg[7]_1\(0)
    );
\HDL_Counter_out1_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => \HDL_Counter_out1_reg[7]_2\(0),
      D => \p_0_in__0\(6),
      Q => HDL_Counter_out1_reg(6),
      R => \HDL_Counter_out1_reg[7]_1\(0)
    );
\HDL_Counter_out1_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => \HDL_Counter_out1_reg[7]_2\(0),
      D => \p_0_in__0\(7),
      Q => HDL_Counter_out1_reg(7),
      R => \HDL_Counter_out1_reg[7]_1\(0)
    );
PipelineDelay_out1_reg: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => Detect_Rise_Positive_out1,
      Q => PipelineDelay_out1,
      R => SR(0)
    );
\i__carry_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"22B2"
    )
        port map (
      I0 => \^q\(7),
      I1 => \HDL_Counter_out10_inferred__0/i__carry_0\(7),
      I2 => \^q\(6),
      I3 => \HDL_Counter_out10_inferred__0/i__carry_0\(6),
      O => \i__carry_i_1_n_0\
    );
\i__carry_i_2\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"22B2"
    )
        port map (
      I0 => \^q\(5),
      I1 => \HDL_Counter_out10_inferred__0/i__carry_0\(5),
      I2 => \^q\(4),
      I3 => \HDL_Counter_out10_inferred__0/i__carry_0\(4),
      O => \i__carry_i_2_n_0\
    );
\i__carry_i_3\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"22B2"
    )
        port map (
      I0 => \^q\(3),
      I1 => \HDL_Counter_out10_inferred__0/i__carry_0\(3),
      I2 => \^q\(2),
      I3 => \HDL_Counter_out10_inferred__0/i__carry_0\(2),
      O => \i__carry_i_3_n_0\
    );
\i__carry_i_4\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"22B2"
    )
        port map (
      I0 => \^q\(1),
      I1 => \HDL_Counter_out10_inferred__0/i__carry_0\(1),
      I2 => \^q\(0),
      I3 => \HDL_Counter_out10_inferred__0/i__carry_0\(0),
      O => \i__carry_i_4_n_0\
    );
u_Detect_Fall_Nonpositive2: entity work.zusys_mux_axi_ip_1_0_mux_axi_ip_src_Detect_Fall_Nonpositive2
     port map (
      E(0) => E(0),
      IPCORE_CLK => IPCORE_CLK,
      Q(7 downto 0) => HDL_Counter_out1_reg(7 downto 0),
      SR(0) => SR(0),
      U_k => U_k,
      U_k_1_0 => U_k_1_0
    );
u_Detect_Rise_Positive: entity work.zusys_mux_axi_ip_1_0_mux_axi_ip_src_Detect_Rise_Positive
     port map (
      E(0) => E(0),
      IPCORE_CLK => IPCORE_CLK,
      SR(0) => SR(0),
      U_k_1 => U_k_1,
      interrupt_out_adc => interrupt_out_adc
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity zusys_mux_axi_ip_1_0_mux_axi_ip_src_mux_axi is
  port (
    U_k_1 : out STD_LOGIC;
    U_k_1_0 : out STD_LOGIC;
    U_k : out STD_LOGIC;
    PipelineDelay_out1 : out STD_LOGIC;
    CO : out STD_LOGIC_VECTOR ( 0 to 0 );
    Q : out STD_LOGIC_VECTOR ( 7 downto 0 );
    SR : in STD_LOGIC_VECTOR ( 0 to 0 );
    E : in STD_LOGIC_VECTOR ( 0 to 0 );
    interrupt_out_adc : in STD_LOGIC;
    IPCORE_CLK : in STD_LOGIC;
    Detect_Rise_Positive_out1 : in STD_LOGIC;
    S : in STD_LOGIC_VECTOR ( 7 downto 0 );
    \HDL_Counter_out1_reg[7]\ : in STD_LOGIC_VECTOR ( 7 downto 0 );
    \HDL_Counter_out10_inferred__0/i__carry\ : in STD_LOGIC_VECTOR ( 7 downto 0 );
    \HDL_Counter_out1_reg[7]_0\ : in STD_LOGIC_VECTOR ( 0 to 0 );
    \HDL_Counter_out1_reg[7]_1\ : in STD_LOGIC_VECTOR ( 0 to 0 )
  );
  attribute ORIG_REF_NAME : string;
  attribute ORIG_REF_NAME of zusys_mux_axi_ip_1_0_mux_axi_ip_src_mux_axi : entity is "mux_axi_ip_src_mux_axi";
end zusys_mux_axi_ip_1_0_mux_axi_ip_src_mux_axi;

architecture STRUCTURE of zusys_mux_axi_ip_1_0_mux_axi_ip_src_mux_axi is
begin
u_Subsystem1: entity work.zusys_mux_axi_ip_1_0_mux_axi_ip_src_Subsystem1
     port map (
      CO(0) => CO(0),
      Detect_Rise_Positive_out1 => Detect_Rise_Positive_out1,
      E(0) => E(0),
      \HDL_Counter_out10_inferred__0/i__carry_0\(7 downto 0) => \HDL_Counter_out10_inferred__0/i__carry\(7 downto 0),
      \HDL_Counter_out1_reg[7]_0\(7 downto 0) => \HDL_Counter_out1_reg[7]\(7 downto 0),
      \HDL_Counter_out1_reg[7]_1\(0) => \HDL_Counter_out1_reg[7]_0\(0),
      \HDL_Counter_out1_reg[7]_2\(0) => \HDL_Counter_out1_reg[7]_1\(0),
      IPCORE_CLK => IPCORE_CLK,
      PipelineDelay_out1 => PipelineDelay_out1,
      Q(7 downto 0) => Q(7 downto 0),
      S(7 downto 0) => S(7 downto 0),
      SR(0) => SR(0),
      U_k => U_k,
      U_k_1 => U_k_1,
      U_k_1_0 => U_k_1_0,
      interrupt_out_adc => interrupt_out_adc
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity zusys_mux_axi_ip_1_0_mux_axi_ip_dut is
  port (
    U_k_1 : out STD_LOGIC;
    U_k_1_0 : out STD_LOGIC;
    U_k : out STD_LOGIC;
    PipelineDelay_out1 : out STD_LOGIC;
    CO : out STD_LOGIC_VECTOR ( 0 to 0 );
    Q : out STD_LOGIC_VECTOR ( 7 downto 0 );
    SR : in STD_LOGIC_VECTOR ( 0 to 0 );
    E : in STD_LOGIC_VECTOR ( 0 to 0 );
    interrupt_out_adc : in STD_LOGIC;
    IPCORE_CLK : in STD_LOGIC;
    Detect_Rise_Positive_out1 : in STD_LOGIC;
    S : in STD_LOGIC_VECTOR ( 7 downto 0 );
    \HDL_Counter_out1_reg[7]\ : in STD_LOGIC_VECTOR ( 7 downto 0 );
    \HDL_Counter_out10_inferred__0/i__carry\ : in STD_LOGIC_VECTOR ( 7 downto 0 );
    \HDL_Counter_out1_reg[7]_0\ : in STD_LOGIC_VECTOR ( 0 to 0 );
    \HDL_Counter_out1_reg[7]_1\ : in STD_LOGIC_VECTOR ( 0 to 0 )
  );
  attribute ORIG_REF_NAME : string;
  attribute ORIG_REF_NAME of zusys_mux_axi_ip_1_0_mux_axi_ip_dut : entity is "mux_axi_ip_dut";
end zusys_mux_axi_ip_1_0_mux_axi_ip_dut;

architecture STRUCTURE of zusys_mux_axi_ip_1_0_mux_axi_ip_dut is
begin
u_mux_axi_ip_src_mux_axi: entity work.zusys_mux_axi_ip_1_0_mux_axi_ip_src_mux_axi
     port map (
      CO(0) => CO(0),
      Detect_Rise_Positive_out1 => Detect_Rise_Positive_out1,
      E(0) => E(0),
      \HDL_Counter_out10_inferred__0/i__carry\(7 downto 0) => \HDL_Counter_out10_inferred__0/i__carry\(7 downto 0),
      \HDL_Counter_out1_reg[7]\(7 downto 0) => \HDL_Counter_out1_reg[7]\(7 downto 0),
      \HDL_Counter_out1_reg[7]_0\(0) => \HDL_Counter_out1_reg[7]_0\(0),
      \HDL_Counter_out1_reg[7]_1\(0) => \HDL_Counter_out1_reg[7]_1\(0),
      IPCORE_CLK => IPCORE_CLK,
      PipelineDelay_out1 => PipelineDelay_out1,
      Q(7 downto 0) => Q(7 downto 0),
      S(7 downto 0) => S(7 downto 0),
      SR(0) => SR(0),
      U_k => U_k,
      U_k_1 => U_k_1,
      U_k_1_0 => U_k_1_0,
      interrupt_out_adc => interrupt_out_adc
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity zusys_mux_axi_ip_1_0_mux_axi_ip is
  port (
    AXI4_Lite_RVALID : out STD_LOGIC;
    AXI4_Lite_BVALID : out STD_LOGIC;
    AXI4_Lite_WREADY : out STD_LOGIC;
    select_out : out STD_LOGIC_VECTOR ( 3 downto 0 );
    AXI4_Lite_RDATA : out STD_LOGIC_VECTOR ( 31 downto 0 );
    interrupt_out_adc : out STD_LOGIC;
    AXI4_Lite_ARREADY : out STD_LOGIC;
    AXI4_Lite_AWREADY : out STD_LOGIC;
    interrupt_out_isr : out STD_LOGIC_VECTOR ( 7 downto 0 );
    AXI4_Lite_ACLK : in STD_LOGIC;
    AXI4_Lite_AWADDR : in STD_LOGIC_VECTOR ( 13 downto 0 );
    IPCORE_CLK : in STD_LOGIC;
    AXI4_Lite_WDATA : in STD_LOGIC_VECTOR ( 31 downto 0 );
    AXI4_Lite_ARADDR : in STD_LOGIC_VECTOR ( 13 downto 0 );
    AXI4_Lite_ARVALID : in STD_LOGIC;
    AXI4_Lite_RREADY : in STD_LOGIC;
    AXI4_Lite_AWVALID : in STD_LOGIC;
    AXI4_Lite_WVALID : in STD_LOGIC;
    AXI4_Lite_ARESETN : in STD_LOGIC;
    interrupts_in : in STD_LOGIC_VECTOR ( 7 downto 0 );
    IPCORE_RESETN : in STD_LOGIC;
    AXI4_Lite_BREADY : in STD_LOGIC;
    AXI4_Lite_WSTRB : in STD_LOGIC_VECTOR ( 3 downto 0 )
  );
  attribute ORIG_REF_NAME : string;
  attribute ORIG_REF_NAME of zusys_mux_axi_ip_1_0_mux_axi_ip : entity is "mux_axi_ip";
end zusys_mux_axi_ip_1_0_mux_axi_ip;

architecture STRUCTURE of zusys_mux_axi_ip_1_0_mux_axi_ip is
  signal Delay_out1 : STD_LOGIC_VECTOR ( 7 downto 0 );
  signal \^interrupt_out_adc\ : STD_LOGIC;
  signal n_th_adc_interrupt : STD_LOGIC_VECTOR ( 7 downto 0 );
  signal reset : STD_LOGIC;
  signal reset_in : STD_LOGIC;
  signal u_mux_axi_ip_axi_lite_inst_n_10 : STD_LOGIC;
  signal u_mux_axi_ip_axi_lite_inst_n_19 : STD_LOGIC;
  signal u_mux_axi_ip_axi_lite_inst_n_20 : STD_LOGIC;
  signal u_mux_axi_ip_axi_lite_inst_n_21 : STD_LOGIC;
  signal u_mux_axi_ip_axi_lite_inst_n_22 : STD_LOGIC;
  signal u_mux_axi_ip_axi_lite_inst_n_23 : STD_LOGIC;
  signal u_mux_axi_ip_axi_lite_inst_n_24 : STD_LOGIC;
  signal u_mux_axi_ip_axi_lite_inst_n_25 : STD_LOGIC;
  signal u_mux_axi_ip_axi_lite_inst_n_26 : STD_LOGIC;
  signal u_mux_axi_ip_axi_lite_inst_n_3 : STD_LOGIC;
  signal u_mux_axi_ip_axi_lite_inst_n_4 : STD_LOGIC;
  signal u_mux_axi_ip_axi_lite_inst_n_46 : STD_LOGIC;
  signal u_mux_axi_ip_axi_lite_inst_n_5 : STD_LOGIC;
  signal u_mux_axi_ip_axi_lite_inst_n_6 : STD_LOGIC;
  signal u_mux_axi_ip_axi_lite_inst_n_7 : STD_LOGIC;
  signal u_mux_axi_ip_axi_lite_inst_n_8 : STD_LOGIC;
  signal u_mux_axi_ip_axi_lite_inst_n_9 : STD_LOGIC;
  signal \u_mux_axi_ip_axi_lite_module_inst/soft_reset\ : STD_LOGIC;
  signal \u_mux_axi_ip_src_mux_axi/u_Subsystem1/Detect_Rise_Positive_out1\ : STD_LOGIC;
  signal \u_mux_axi_ip_src_mux_axi/u_Subsystem1/HDL_Counter_out1\ : STD_LOGIC;
  signal \u_mux_axi_ip_src_mux_axi/u_Subsystem1/PipelineDelay_out1\ : STD_LOGIC;
  signal \u_mux_axi_ip_src_mux_axi/u_Subsystem1/Relational_Operator_relop1\ : STD_LOGIC;
  signal \u_mux_axi_ip_src_mux_axi/u_Subsystem1/u_Detect_Fall_Nonpositive2/U_k\ : STD_LOGIC;
  signal \u_mux_axi_ip_src_mux_axi/u_Subsystem1/u_Detect_Fall_Nonpositive2/U_k_1\ : STD_LOGIC;
  signal \u_mux_axi_ip_src_mux_axi/u_Subsystem1/u_Detect_Rise_Positive/U_k_1\ : STD_LOGIC;
  signal write_axi_enable : STD_LOGIC;
begin
  interrupt_out_adc <= \^interrupt_out_adc\;
u_mux_axi_ip_axi_lite_inst: entity work.zusys_mux_axi_ip_1_0_mux_axi_ip_axi_lite
     port map (
      AXI4_Lite_ACLK => AXI4_Lite_ACLK,
      AXI4_Lite_ARADDR(13 downto 0) => AXI4_Lite_ARADDR(13 downto 0),
      AXI4_Lite_ARESETN => AXI4_Lite_ARESETN,
      AXI4_Lite_ARREADY => AXI4_Lite_ARREADY,
      AXI4_Lite_ARVALID => AXI4_Lite_ARVALID,
      AXI4_Lite_AWADDR(13 downto 0) => AXI4_Lite_AWADDR(13 downto 0),
      AXI4_Lite_AWREADY => AXI4_Lite_AWREADY,
      AXI4_Lite_AWVALID => AXI4_Lite_AWVALID,
      AXI4_Lite_BREADY => AXI4_Lite_BREADY,
      AXI4_Lite_RDATA(31 downto 0) => AXI4_Lite_RDATA(31 downto 0),
      AXI4_Lite_RREADY => AXI4_Lite_RREADY,
      AXI4_Lite_WDATA(31 downto 0) => AXI4_Lite_WDATA(31 downto 0),
      AXI4_Lite_WSTRB(3 downto 0) => AXI4_Lite_WSTRB(3 downto 0),
      AXI4_Lite_WVALID => AXI4_Lite_WVALID,
      CO(0) => \u_mux_axi_ip_src_mux_axi/u_Subsystem1/Relational_Operator_relop1\,
      Detect_Rise_Positive_out1 => \u_mux_axi_ip_src_mux_axi/u_Subsystem1/Detect_Rise_Positive_out1\,
      E(0) => \u_mux_axi_ip_src_mux_axi/u_Subsystem1/HDL_Counter_out1\,
      \FSM_onehot_axi_lite_wstate_reg[2]\(1) => AXI4_Lite_BVALID,
      \FSM_onehot_axi_lite_wstate_reg[2]\(0) => AXI4_Lite_WREADY,
      FSM_sequential_axi_lite_rstate_reg => AXI4_Lite_RVALID,
      \HDL_Counter_out10_inferred__0/i__carry\(7 downto 0) => Delay_out1(7 downto 0),
      IPCORE_RESETN => IPCORE_RESETN,
      PipelineDelay_out1 => \u_mux_axi_ip_src_mux_axi/u_Subsystem1/PipelineDelay_out1\,
      Q(7 downto 0) => n_th_adc_interrupt(7 downto 0),
      S(7) => u_mux_axi_ip_axi_lite_inst_n_3,
      S(6) => u_mux_axi_ip_axi_lite_inst_n_4,
      S(5) => u_mux_axi_ip_axi_lite_inst_n_5,
      S(4) => u_mux_axi_ip_axi_lite_inst_n_6,
      S(3) => u_mux_axi_ip_axi_lite_inst_n_7,
      S(2) => u_mux_axi_ip_axi_lite_inst_n_8,
      S(1) => u_mux_axi_ip_axi_lite_inst_n_9,
      S(0) => u_mux_axi_ip_axi_lite_inst_n_10,
      SR(0) => reset,
      U_k => \u_mux_axi_ip_src_mux_axi/u_Subsystem1/u_Detect_Fall_Nonpositive2/U_k\,
      U_k_1 => \u_mux_axi_ip_src_mux_axi/u_Subsystem1/u_Detect_Fall_Nonpositive2/U_k_1\,
      U_k_1_0 => \u_mux_axi_ip_src_mux_axi/u_Subsystem1/u_Detect_Rise_Positive/U_k_1\,
      data_reg_axi_enable_1_1_reg(0) => u_mux_axi_ip_axi_lite_inst_n_46,
      \data_reg_select_AXI_1_1_reg[3]\(3 downto 0) => select_out(3 downto 0),
      \data_reg_select_n_th_adc_interrupt_1_1_reg[30]\(7) => u_mux_axi_ip_axi_lite_inst_n_19,
      \data_reg_select_n_th_adc_interrupt_1_1_reg[30]\(6) => u_mux_axi_ip_axi_lite_inst_n_20,
      \data_reg_select_n_th_adc_interrupt_1_1_reg[30]\(5) => u_mux_axi_ip_axi_lite_inst_n_21,
      \data_reg_select_n_th_adc_interrupt_1_1_reg[30]\(4) => u_mux_axi_ip_axi_lite_inst_n_22,
      \data_reg_select_n_th_adc_interrupt_1_1_reg[30]\(3) => u_mux_axi_ip_axi_lite_inst_n_23,
      \data_reg_select_n_th_adc_interrupt_1_1_reg[30]\(2) => u_mux_axi_ip_axi_lite_inst_n_24,
      \data_reg_select_n_th_adc_interrupt_1_1_reg[30]\(1) => u_mux_axi_ip_axi_lite_inst_n_25,
      \data_reg_select_n_th_adc_interrupt_1_1_reg[30]\(0) => u_mux_axi_ip_axi_lite_inst_n_26,
      interrupt_out_adc => \^interrupt_out_adc\,
      interrupt_out_isr(7 downto 0) => interrupt_out_isr(7 downto 0),
      interrupts_in(7 downto 0) => interrupts_in(7 downto 0),
      reset_in => reset_in,
      soft_reset => \u_mux_axi_ip_axi_lite_module_inst/soft_reset\,
      write_axi_enable => write_axi_enable
    );
u_mux_axi_ip_dut_inst: entity work.zusys_mux_axi_ip_1_0_mux_axi_ip_dut
     port map (
      CO(0) => \u_mux_axi_ip_src_mux_axi/u_Subsystem1/Relational_Operator_relop1\,
      Detect_Rise_Positive_out1 => \u_mux_axi_ip_src_mux_axi/u_Subsystem1/Detect_Rise_Positive_out1\,
      E(0) => write_axi_enable,
      \HDL_Counter_out10_inferred__0/i__carry\(7 downto 0) => n_th_adc_interrupt(7 downto 0),
      \HDL_Counter_out1_reg[7]\(7) => u_mux_axi_ip_axi_lite_inst_n_19,
      \HDL_Counter_out1_reg[7]\(6) => u_mux_axi_ip_axi_lite_inst_n_20,
      \HDL_Counter_out1_reg[7]\(5) => u_mux_axi_ip_axi_lite_inst_n_21,
      \HDL_Counter_out1_reg[7]\(4) => u_mux_axi_ip_axi_lite_inst_n_22,
      \HDL_Counter_out1_reg[7]\(3) => u_mux_axi_ip_axi_lite_inst_n_23,
      \HDL_Counter_out1_reg[7]\(2) => u_mux_axi_ip_axi_lite_inst_n_24,
      \HDL_Counter_out1_reg[7]\(1) => u_mux_axi_ip_axi_lite_inst_n_25,
      \HDL_Counter_out1_reg[7]\(0) => u_mux_axi_ip_axi_lite_inst_n_26,
      \HDL_Counter_out1_reg[7]_0\(0) => u_mux_axi_ip_axi_lite_inst_n_46,
      \HDL_Counter_out1_reg[7]_1\(0) => \u_mux_axi_ip_src_mux_axi/u_Subsystem1/HDL_Counter_out1\,
      IPCORE_CLK => IPCORE_CLK,
      PipelineDelay_out1 => \u_mux_axi_ip_src_mux_axi/u_Subsystem1/PipelineDelay_out1\,
      Q(7 downto 0) => Delay_out1(7 downto 0),
      S(7) => u_mux_axi_ip_axi_lite_inst_n_3,
      S(6) => u_mux_axi_ip_axi_lite_inst_n_4,
      S(5) => u_mux_axi_ip_axi_lite_inst_n_5,
      S(4) => u_mux_axi_ip_axi_lite_inst_n_6,
      S(3) => u_mux_axi_ip_axi_lite_inst_n_7,
      S(2) => u_mux_axi_ip_axi_lite_inst_n_8,
      S(1) => u_mux_axi_ip_axi_lite_inst_n_9,
      S(0) => u_mux_axi_ip_axi_lite_inst_n_10,
      SR(0) => reset,
      U_k => \u_mux_axi_ip_src_mux_axi/u_Subsystem1/u_Detect_Fall_Nonpositive2/U_k\,
      U_k_1 => \u_mux_axi_ip_src_mux_axi/u_Subsystem1/u_Detect_Rise_Positive/U_k_1\,
      U_k_1_0 => \u_mux_axi_ip_src_mux_axi/u_Subsystem1/u_Detect_Fall_Nonpositive2/U_k_1\,
      interrupt_out_adc => \^interrupt_out_adc\
    );
u_mux_axi_ip_reset_sync_inst: entity work.zusys_mux_axi_ip_1_0_mux_axi_ip_reset_sync
     port map (
      AXI4_Lite_ARESETN => AXI4_Lite_ARESETN,
      IPCORE_CLK => IPCORE_CLK,
      IPCORE_RESETN => IPCORE_RESETN,
      SR(0) => reset,
      reset_in => reset_in,
      soft_reset => \u_mux_axi_ip_axi_lite_module_inst/soft_reset\
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity zusys_mux_axi_ip_1_0 is
  port (
    IPCORE_CLK : in STD_LOGIC;
    IPCORE_RESETN : in STD_LOGIC;
    interrupts_in : in STD_LOGIC_VECTOR ( 7 downto 0 );
    AXI4_Lite_ACLK : in STD_LOGIC;
    AXI4_Lite_ARESETN : in STD_LOGIC;
    AXI4_Lite_AWADDR : in STD_LOGIC_VECTOR ( 15 downto 0 );
    AXI4_Lite_AWVALID : in STD_LOGIC;
    AXI4_Lite_WDATA : in STD_LOGIC_VECTOR ( 31 downto 0 );
    AXI4_Lite_WSTRB : in STD_LOGIC_VECTOR ( 3 downto 0 );
    AXI4_Lite_WVALID : in STD_LOGIC;
    AXI4_Lite_BREADY : in STD_LOGIC;
    AXI4_Lite_ARADDR : in STD_LOGIC_VECTOR ( 15 downto 0 );
    AXI4_Lite_ARVALID : in STD_LOGIC;
    AXI4_Lite_RREADY : in STD_LOGIC;
    interrupt_out_adc : out STD_LOGIC;
    interrupt_out_isr : out STD_LOGIC_VECTOR ( 7 downto 0 );
    select_out : out STD_LOGIC_VECTOR ( 3 downto 0 );
    AXI4_Lite_AWREADY : out STD_LOGIC;
    AXI4_Lite_WREADY : out STD_LOGIC;
    AXI4_Lite_BRESP : out STD_LOGIC_VECTOR ( 1 downto 0 );
    AXI4_Lite_BVALID : out STD_LOGIC;
    AXI4_Lite_ARREADY : out STD_LOGIC;
    AXI4_Lite_RDATA : out STD_LOGIC_VECTOR ( 31 downto 0 );
    AXI4_Lite_RRESP : out STD_LOGIC_VECTOR ( 1 downto 0 );
    AXI4_Lite_RVALID : out STD_LOGIC
  );
  attribute NotValidForBitStream : boolean;
  attribute NotValidForBitStream of zusys_mux_axi_ip_1_0 : entity is true;
  attribute CHECK_LICENSE_TYPE : string;
  attribute CHECK_LICENSE_TYPE of zusys_mux_axi_ip_1_0 : entity is "zusys_mux_axi_ip_1_0,mux_axi_ip,{}";
  attribute downgradeipidentifiedwarnings : string;
  attribute downgradeipidentifiedwarnings of zusys_mux_axi_ip_1_0 : entity is "yes";
  attribute ip_definition_source : string;
  attribute ip_definition_source of zusys_mux_axi_ip_1_0 : entity is "package_project";
  attribute x_core_info : string;
  attribute x_core_info of zusys_mux_axi_ip_1_0 : entity is "mux_axi_ip,Vivado 2020.1.1";
end zusys_mux_axi_ip_1_0;

architecture STRUCTURE of zusys_mux_axi_ip_1_0 is
  signal \<const0>\ : STD_LOGIC;
  attribute x_interface_info : string;
  attribute x_interface_info of AXI4_Lite_ACLK : signal is "xilinx.com:signal:clock:1.0 AXI4_Lite_signal_clock CLK";
  attribute x_interface_parameter : string;
  attribute x_interface_parameter of AXI4_Lite_ACLK : signal is "XIL_INTERFACENAME AXI4_Lite_signal_clock, ASSOCIATED_BUSIF AXI4_Lite, ASSOCIATED_RESET AXI4_Lite_ARESETN, FREQ_HZ 100000000, FREQ_TOLERANCE_HZ 0, PHASE 0.000, CLK_DOMAIN zusys_zynq_ultra_ps_e_0_0_pl_clk0, INSERT_VIP 0";
  attribute x_interface_info of AXI4_Lite_ARESETN : signal is "xilinx.com:signal:reset:1.0 AXI4_Lite_signal_reset RST";
  attribute x_interface_parameter of AXI4_Lite_ARESETN : signal is "XIL_INTERFACENAME AXI4_Lite_signal_reset, POLARITY ACTIVE_LOW, INSERT_VIP 0";
  attribute x_interface_info of AXI4_Lite_ARREADY : signal is "xilinx.com:interface:aximm:1.0 AXI4_Lite ARREADY";
  attribute x_interface_info of AXI4_Lite_ARVALID : signal is "xilinx.com:interface:aximm:1.0 AXI4_Lite ARVALID";
  attribute x_interface_info of AXI4_Lite_AWREADY : signal is "xilinx.com:interface:aximm:1.0 AXI4_Lite AWREADY";
  attribute x_interface_info of AXI4_Lite_AWVALID : signal is "xilinx.com:interface:aximm:1.0 AXI4_Lite AWVALID";
  attribute x_interface_info of AXI4_Lite_BREADY : signal is "xilinx.com:interface:aximm:1.0 AXI4_Lite BREADY";
  attribute x_interface_info of AXI4_Lite_BVALID : signal is "xilinx.com:interface:aximm:1.0 AXI4_Lite BVALID";
  attribute x_interface_info of AXI4_Lite_RREADY : signal is "xilinx.com:interface:aximm:1.0 AXI4_Lite RREADY";
  attribute x_interface_info of AXI4_Lite_RVALID : signal is "xilinx.com:interface:aximm:1.0 AXI4_Lite RVALID";
  attribute x_interface_info of AXI4_Lite_WREADY : signal is "xilinx.com:interface:aximm:1.0 AXI4_Lite WREADY";
  attribute x_interface_info of AXI4_Lite_WVALID : signal is "xilinx.com:interface:aximm:1.0 AXI4_Lite WVALID";
  attribute x_interface_info of IPCORE_CLK : signal is "xilinx.com:signal:clock:1.0 IPCORE_CLK CLK";
  attribute x_interface_parameter of IPCORE_CLK : signal is "XIL_INTERFACENAME IPCORE_CLK, ASSOCIATED_RESET IPCORE_RESETN, FREQ_HZ 100000000, FREQ_TOLERANCE_HZ 0, PHASE 0.000, CLK_DOMAIN zusys_zynq_ultra_ps_e_0_0_pl_clk0, INSERT_VIP 0";
  attribute x_interface_info of IPCORE_RESETN : signal is "xilinx.com:signal:reset:1.0 IPCORE_RESETN RST";
  attribute x_interface_parameter of IPCORE_RESETN : signal is "XIL_INTERFACENAME IPCORE_RESETN, POLARITY ACTIVE_LOW, INSERT_VIP 0";
  attribute x_interface_info of AXI4_Lite_ARADDR : signal is "xilinx.com:interface:aximm:1.0 AXI4_Lite ARADDR";
  attribute x_interface_info of AXI4_Lite_AWADDR : signal is "xilinx.com:interface:aximm:1.0 AXI4_Lite AWADDR";
  attribute x_interface_parameter of AXI4_Lite_AWADDR : signal is "XIL_INTERFACENAME AXI4_Lite, DATA_WIDTH 32, PROTOCOL AXI4LITE, FREQ_HZ 100000000, ID_WIDTH 0, ADDR_WIDTH 16, AWUSER_WIDTH 0, ARUSER_WIDTH 0, WUSER_WIDTH 0, RUSER_WIDTH 0, BUSER_WIDTH 0, READ_WRITE_MODE READ_WRITE, HAS_BURST 0, HAS_LOCK 0, HAS_PROT 0, HAS_CACHE 0, HAS_QOS 0, HAS_REGION 0, HAS_WSTRB 1, HAS_BRESP 1, HAS_RRESP 1, SUPPORTS_NARROW_BURST 0, NUM_READ_OUTSTANDING 1, NUM_WRITE_OUTSTANDING 1, MAX_BURST_LENGTH 1, PHASE 0.000, CLK_DOMAIN zusys_zynq_ultra_ps_e_0_0_pl_clk0, NUM_READ_THREADS 1, NUM_WRITE_THREADS 1, RUSER_BITS_PER_BYTE 0, WUSER_BITS_PER_BYTE 0, INSERT_VIP 0";
  attribute x_interface_info of AXI4_Lite_BRESP : signal is "xilinx.com:interface:aximm:1.0 AXI4_Lite BRESP";
  attribute x_interface_info of AXI4_Lite_RDATA : signal is "xilinx.com:interface:aximm:1.0 AXI4_Lite RDATA";
  attribute x_interface_info of AXI4_Lite_RRESP : signal is "xilinx.com:interface:aximm:1.0 AXI4_Lite RRESP";
  attribute x_interface_info of AXI4_Lite_WDATA : signal is "xilinx.com:interface:aximm:1.0 AXI4_Lite WDATA";
  attribute x_interface_info of AXI4_Lite_WSTRB : signal is "xilinx.com:interface:aximm:1.0 AXI4_Lite WSTRB";
begin
  AXI4_Lite_BRESP(1) <= \<const0>\;
  AXI4_Lite_BRESP(0) <= \<const0>\;
  AXI4_Lite_RRESP(1) <= \<const0>\;
  AXI4_Lite_RRESP(0) <= \<const0>\;
GND: unisim.vcomponents.GND
     port map (
      G => \<const0>\
    );
U0: entity work.zusys_mux_axi_ip_1_0_mux_axi_ip
     port map (
      AXI4_Lite_ACLK => AXI4_Lite_ACLK,
      AXI4_Lite_ARADDR(13 downto 0) => AXI4_Lite_ARADDR(15 downto 2),
      AXI4_Lite_ARESETN => AXI4_Lite_ARESETN,
      AXI4_Lite_ARREADY => AXI4_Lite_ARREADY,
      AXI4_Lite_ARVALID => AXI4_Lite_ARVALID,
      AXI4_Lite_AWADDR(13 downto 0) => AXI4_Lite_AWADDR(15 downto 2),
      AXI4_Lite_AWREADY => AXI4_Lite_AWREADY,
      AXI4_Lite_AWVALID => AXI4_Lite_AWVALID,
      AXI4_Lite_BREADY => AXI4_Lite_BREADY,
      AXI4_Lite_BVALID => AXI4_Lite_BVALID,
      AXI4_Lite_RDATA(31 downto 0) => AXI4_Lite_RDATA(31 downto 0),
      AXI4_Lite_RREADY => AXI4_Lite_RREADY,
      AXI4_Lite_RVALID => AXI4_Lite_RVALID,
      AXI4_Lite_WDATA(31 downto 0) => AXI4_Lite_WDATA(31 downto 0),
      AXI4_Lite_WREADY => AXI4_Lite_WREADY,
      AXI4_Lite_WSTRB(3 downto 0) => AXI4_Lite_WSTRB(3 downto 0),
      AXI4_Lite_WVALID => AXI4_Lite_WVALID,
      IPCORE_CLK => IPCORE_CLK,
      IPCORE_RESETN => IPCORE_RESETN,
      interrupt_out_adc => interrupt_out_adc,
      interrupt_out_isr(7 downto 0) => interrupt_out_isr(7 downto 0),
      interrupts_in(7 downto 0) => interrupts_in(7 downto 0),
      select_out(3 downto 0) => select_out(3 downto 0)
    );
end STRUCTURE;
