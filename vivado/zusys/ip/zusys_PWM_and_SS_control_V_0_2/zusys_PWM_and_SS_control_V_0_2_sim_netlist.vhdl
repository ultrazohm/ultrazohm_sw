-- Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
-- --------------------------------------------------------------------------------
-- Tool Version: Vivado v.2020.1.1 (win64) Build 2960000 Wed Aug  5 22:57:20 MDT 2020
-- Date        : Fri Jan 28 14:43:25 2022
-- Host        : enc177112 running 64-bit major release  (build 9200)
-- Command     : write_vhdl -force -mode funcsim -rename_top zusys_PWM_and_SS_control_V_0_2 -prefix
--               zusys_PWM_and_SS_control_V_0_2_ zusys_PWM_and_SS_control_V_0_0_sim_netlist.vhdl
-- Design      : zusys_PWM_and_SS_control_V_0_0
-- Purpose     : This VHDL netlist is a functional simulation representation of the design and should not be modified or
--               synthesized. This netlist cannot be used for SDF annotated simulation.
-- Device      : xczu9eg-ffvc900-1-e
-- --------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity zusys_PWM_and_SS_control_V_0_2_PWM_and_SS_control_V3_ip_addr_decoder is
  port (
    read_reg_ip_timestamp : out STD_LOGIC_VECTOR ( 0 to 0 );
    read_reg_PWM_en_rd_AXI : out STD_LOGIC;
    CEA1 : out STD_LOGIC;
    write_PWM_en_AXI : out STD_LOGIC;
    CEB2 : out STD_LOGIC;
    \write_reg_Mode_AXI_reg[1]_0\ : out STD_LOGIC_VECTOR ( 1 downto 0 );
    \write_reg_Scal_f_carrier_AXI_reg[24]_0\ : out STD_LOGIC_VECTOR ( 24 downto 0 );
    \write_reg_Scal_T_carrier_AXI_reg[24]_0\ : out STD_LOGIC_VECTOR ( 24 downto 0 );
    \write_reg_PWM_min_pulse_width_AXI_reg[17]_0\ : out STD_LOGIC_VECTOR ( 17 downto 0 );
    \write_reg_m_u1_norm_AXI_reg[13]_0\ : out STD_LOGIC_VECTOR ( 13 downto 0 );
    \write_reg_m_u2_norm_AXI_reg[13]_0\ : out STD_LOGIC_VECTOR ( 13 downto 0 );
    \write_reg_m_u3_norm_AXI_reg[13]_0\ : out STD_LOGIC_VECTOR ( 13 downto 0 );
    \write_reg_TriState_HB1_AXI_reg[1]_0\ : out STD_LOGIC_VECTOR ( 1 downto 0 );
    \write_reg_TriState_HB2_AXI_reg[1]_0\ : out STD_LOGIC_VECTOR ( 1 downto 0 );
    \write_reg_TriState_HB3_AXI_reg[1]_0\ : out STD_LOGIC_VECTOR ( 1 downto 0 );
    \read_reg_PWM_f_carrier_kHz_rd_AXI_reg[24]_0\ : out STD_LOGIC_VECTOR ( 24 downto 0 );
    \read_reg_PWM_T_carrier_us_rd_AXI_reg[24]_0\ : out STD_LOGIC_VECTOR ( 24 downto 0 );
    \read_reg_PWM_min_pulse_width_rd_AXI_reg[17]_0\ : out STD_LOGIC_VECTOR ( 17 downto 0 );
    \read_reg_Mode_rd_AXI_reg[1]_0\ : out STD_LOGIC_VECTOR ( 1 downto 0 );
    SR : in STD_LOGIC_VECTOR ( 0 to 0 );
    AXI4_Lite_ACLK : in STD_LOGIC;
    PWM_en_rd_AXI_sig : in STD_LOGIC;
    write_reg_axi_enable_reg_0 : in STD_LOGIC;
    write_reg_PWM_en_AXI_reg_0 : in STD_LOGIC;
    PWM_en_AXI_1 : in STD_LOGIC;
    E : in STD_LOGIC_VECTOR ( 0 to 0 );
    Q : in STD_LOGIC_VECTOR ( 24 downto 0 );
    \write_reg_Scal_f_carrier_AXI_reg[24]_1\ : in STD_LOGIC_VECTOR ( 0 to 0 );
    \write_reg_Scal_T_carrier_AXI_reg[24]_1\ : in STD_LOGIC_VECTOR ( 0 to 0 );
    \write_reg_PWM_min_pulse_width_AXI_reg[17]_1\ : in STD_LOGIC_VECTOR ( 0 to 0 );
    \write_reg_m_u1_norm_AXI_reg[13]_1\ : in STD_LOGIC_VECTOR ( 0 to 0 );
    \write_reg_m_u2_norm_AXI_reg[13]_1\ : in STD_LOGIC_VECTOR ( 0 to 0 );
    \write_reg_m_u3_norm_AXI_reg[13]_1\ : in STD_LOGIC_VECTOR ( 0 to 0 );
    \write_reg_TriState_HB1_AXI_reg[1]_1\ : in STD_LOGIC_VECTOR ( 0 to 0 );
    \write_reg_TriState_HB2_AXI_reg[1]_1\ : in STD_LOGIC_VECTOR ( 0 to 0 );
    \write_reg_TriState_HB3_AXI_reg[1]_1\ : in STD_LOGIC_VECTOR ( 0 to 0 );
    D : in STD_LOGIC_VECTOR ( 24 downto 0 );
    \read_reg_PWM_T_carrier_us_rd_AXI_reg[24]_1\ : in STD_LOGIC_VECTOR ( 24 downto 0 );
    \read_reg_PWM_min_pulse_width_rd_AXI_reg[17]_1\ : in STD_LOGIC_VECTOR ( 17 downto 0 );
    \read_reg_Mode_rd_AXI_reg[1]_1\ : in STD_LOGIC_VECTOR ( 1 downto 0 )
  );
end zusys_PWM_and_SS_control_V_0_2_PWM_and_SS_control_V3_ip_addr_decoder;

architecture STRUCTURE of zusys_PWM_and_SS_control_V_0_2_PWM_and_SS_control_V3_ip_addr_decoder is
  signal \^cea1\ : STD_LOGIC;
begin
  CEA1 <= \^cea1\;
Product_mul_temp_i_1: unisim.vcomponents.LUT2
    generic map(
      INIT => X"8"
    )
        port map (
      I0 => \^cea1\,
      I1 => PWM_en_AXI_1,
      O => CEB2
    );
\read_reg_Mode_rd_AXI_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => \read_reg_Mode_rd_AXI_reg[1]_1\(0),
      Q => \read_reg_Mode_rd_AXI_reg[1]_0\(0),
      R => SR(0)
    );
\read_reg_Mode_rd_AXI_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => \read_reg_Mode_rd_AXI_reg[1]_1\(1),
      Q => \read_reg_Mode_rd_AXI_reg[1]_0\(1),
      R => SR(0)
    );
\read_reg_PWM_T_carrier_us_rd_AXI_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => \read_reg_PWM_T_carrier_us_rd_AXI_reg[24]_1\(0),
      Q => \read_reg_PWM_T_carrier_us_rd_AXI_reg[24]_0\(0),
      R => SR(0)
    );
\read_reg_PWM_T_carrier_us_rd_AXI_reg[10]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => \read_reg_PWM_T_carrier_us_rd_AXI_reg[24]_1\(10),
      Q => \read_reg_PWM_T_carrier_us_rd_AXI_reg[24]_0\(10),
      R => SR(0)
    );
\read_reg_PWM_T_carrier_us_rd_AXI_reg[11]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => \read_reg_PWM_T_carrier_us_rd_AXI_reg[24]_1\(11),
      Q => \read_reg_PWM_T_carrier_us_rd_AXI_reg[24]_0\(11),
      R => SR(0)
    );
\read_reg_PWM_T_carrier_us_rd_AXI_reg[12]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => \read_reg_PWM_T_carrier_us_rd_AXI_reg[24]_1\(12),
      Q => \read_reg_PWM_T_carrier_us_rd_AXI_reg[24]_0\(12),
      R => SR(0)
    );
\read_reg_PWM_T_carrier_us_rd_AXI_reg[13]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => \read_reg_PWM_T_carrier_us_rd_AXI_reg[24]_1\(13),
      Q => \read_reg_PWM_T_carrier_us_rd_AXI_reg[24]_0\(13),
      R => SR(0)
    );
\read_reg_PWM_T_carrier_us_rd_AXI_reg[14]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => \read_reg_PWM_T_carrier_us_rd_AXI_reg[24]_1\(14),
      Q => \read_reg_PWM_T_carrier_us_rd_AXI_reg[24]_0\(14),
      R => SR(0)
    );
\read_reg_PWM_T_carrier_us_rd_AXI_reg[15]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => \read_reg_PWM_T_carrier_us_rd_AXI_reg[24]_1\(15),
      Q => \read_reg_PWM_T_carrier_us_rd_AXI_reg[24]_0\(15),
      R => SR(0)
    );
\read_reg_PWM_T_carrier_us_rd_AXI_reg[16]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => \read_reg_PWM_T_carrier_us_rd_AXI_reg[24]_1\(16),
      Q => \read_reg_PWM_T_carrier_us_rd_AXI_reg[24]_0\(16),
      R => SR(0)
    );
\read_reg_PWM_T_carrier_us_rd_AXI_reg[17]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => \read_reg_PWM_T_carrier_us_rd_AXI_reg[24]_1\(17),
      Q => \read_reg_PWM_T_carrier_us_rd_AXI_reg[24]_0\(17),
      R => SR(0)
    );
\read_reg_PWM_T_carrier_us_rd_AXI_reg[18]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => \read_reg_PWM_T_carrier_us_rd_AXI_reg[24]_1\(18),
      Q => \read_reg_PWM_T_carrier_us_rd_AXI_reg[24]_0\(18),
      R => SR(0)
    );
\read_reg_PWM_T_carrier_us_rd_AXI_reg[19]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => \read_reg_PWM_T_carrier_us_rd_AXI_reg[24]_1\(19),
      Q => \read_reg_PWM_T_carrier_us_rd_AXI_reg[24]_0\(19),
      R => SR(0)
    );
\read_reg_PWM_T_carrier_us_rd_AXI_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => \read_reg_PWM_T_carrier_us_rd_AXI_reg[24]_1\(1),
      Q => \read_reg_PWM_T_carrier_us_rd_AXI_reg[24]_0\(1),
      R => SR(0)
    );
\read_reg_PWM_T_carrier_us_rd_AXI_reg[20]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => \read_reg_PWM_T_carrier_us_rd_AXI_reg[24]_1\(20),
      Q => \read_reg_PWM_T_carrier_us_rd_AXI_reg[24]_0\(20),
      R => SR(0)
    );
\read_reg_PWM_T_carrier_us_rd_AXI_reg[21]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => \read_reg_PWM_T_carrier_us_rd_AXI_reg[24]_1\(21),
      Q => \read_reg_PWM_T_carrier_us_rd_AXI_reg[24]_0\(21),
      R => SR(0)
    );
\read_reg_PWM_T_carrier_us_rd_AXI_reg[22]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => \read_reg_PWM_T_carrier_us_rd_AXI_reg[24]_1\(22),
      Q => \read_reg_PWM_T_carrier_us_rd_AXI_reg[24]_0\(22),
      R => SR(0)
    );
\read_reg_PWM_T_carrier_us_rd_AXI_reg[23]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => \read_reg_PWM_T_carrier_us_rd_AXI_reg[24]_1\(23),
      Q => \read_reg_PWM_T_carrier_us_rd_AXI_reg[24]_0\(23),
      R => SR(0)
    );
\read_reg_PWM_T_carrier_us_rd_AXI_reg[24]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => \read_reg_PWM_T_carrier_us_rd_AXI_reg[24]_1\(24),
      Q => \read_reg_PWM_T_carrier_us_rd_AXI_reg[24]_0\(24),
      R => SR(0)
    );
\read_reg_PWM_T_carrier_us_rd_AXI_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => \read_reg_PWM_T_carrier_us_rd_AXI_reg[24]_1\(2),
      Q => \read_reg_PWM_T_carrier_us_rd_AXI_reg[24]_0\(2),
      R => SR(0)
    );
\read_reg_PWM_T_carrier_us_rd_AXI_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => \read_reg_PWM_T_carrier_us_rd_AXI_reg[24]_1\(3),
      Q => \read_reg_PWM_T_carrier_us_rd_AXI_reg[24]_0\(3),
      R => SR(0)
    );
\read_reg_PWM_T_carrier_us_rd_AXI_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => \read_reg_PWM_T_carrier_us_rd_AXI_reg[24]_1\(4),
      Q => \read_reg_PWM_T_carrier_us_rd_AXI_reg[24]_0\(4),
      R => SR(0)
    );
\read_reg_PWM_T_carrier_us_rd_AXI_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => \read_reg_PWM_T_carrier_us_rd_AXI_reg[24]_1\(5),
      Q => \read_reg_PWM_T_carrier_us_rd_AXI_reg[24]_0\(5),
      R => SR(0)
    );
\read_reg_PWM_T_carrier_us_rd_AXI_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => \read_reg_PWM_T_carrier_us_rd_AXI_reg[24]_1\(6),
      Q => \read_reg_PWM_T_carrier_us_rd_AXI_reg[24]_0\(6),
      R => SR(0)
    );
\read_reg_PWM_T_carrier_us_rd_AXI_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => \read_reg_PWM_T_carrier_us_rd_AXI_reg[24]_1\(7),
      Q => \read_reg_PWM_T_carrier_us_rd_AXI_reg[24]_0\(7),
      R => SR(0)
    );
\read_reg_PWM_T_carrier_us_rd_AXI_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => \read_reg_PWM_T_carrier_us_rd_AXI_reg[24]_1\(8),
      Q => \read_reg_PWM_T_carrier_us_rd_AXI_reg[24]_0\(8),
      R => SR(0)
    );
\read_reg_PWM_T_carrier_us_rd_AXI_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => \read_reg_PWM_T_carrier_us_rd_AXI_reg[24]_1\(9),
      Q => \read_reg_PWM_T_carrier_us_rd_AXI_reg[24]_0\(9),
      R => SR(0)
    );
read_reg_PWM_en_rd_AXI_reg: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => PWM_en_rd_AXI_sig,
      Q => read_reg_PWM_en_rd_AXI,
      R => SR(0)
    );
\read_reg_PWM_f_carrier_kHz_rd_AXI_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => D(0),
      Q => \read_reg_PWM_f_carrier_kHz_rd_AXI_reg[24]_0\(0),
      R => SR(0)
    );
\read_reg_PWM_f_carrier_kHz_rd_AXI_reg[10]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => D(10),
      Q => \read_reg_PWM_f_carrier_kHz_rd_AXI_reg[24]_0\(10),
      R => SR(0)
    );
\read_reg_PWM_f_carrier_kHz_rd_AXI_reg[11]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => D(11),
      Q => \read_reg_PWM_f_carrier_kHz_rd_AXI_reg[24]_0\(11),
      R => SR(0)
    );
\read_reg_PWM_f_carrier_kHz_rd_AXI_reg[12]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => D(12),
      Q => \read_reg_PWM_f_carrier_kHz_rd_AXI_reg[24]_0\(12),
      R => SR(0)
    );
\read_reg_PWM_f_carrier_kHz_rd_AXI_reg[13]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => D(13),
      Q => \read_reg_PWM_f_carrier_kHz_rd_AXI_reg[24]_0\(13),
      R => SR(0)
    );
\read_reg_PWM_f_carrier_kHz_rd_AXI_reg[14]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => D(14),
      Q => \read_reg_PWM_f_carrier_kHz_rd_AXI_reg[24]_0\(14),
      R => SR(0)
    );
\read_reg_PWM_f_carrier_kHz_rd_AXI_reg[15]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => D(15),
      Q => \read_reg_PWM_f_carrier_kHz_rd_AXI_reg[24]_0\(15),
      R => SR(0)
    );
\read_reg_PWM_f_carrier_kHz_rd_AXI_reg[16]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => D(16),
      Q => \read_reg_PWM_f_carrier_kHz_rd_AXI_reg[24]_0\(16),
      R => SR(0)
    );
\read_reg_PWM_f_carrier_kHz_rd_AXI_reg[17]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => D(17),
      Q => \read_reg_PWM_f_carrier_kHz_rd_AXI_reg[24]_0\(17),
      R => SR(0)
    );
\read_reg_PWM_f_carrier_kHz_rd_AXI_reg[18]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => D(18),
      Q => \read_reg_PWM_f_carrier_kHz_rd_AXI_reg[24]_0\(18),
      R => SR(0)
    );
\read_reg_PWM_f_carrier_kHz_rd_AXI_reg[19]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => D(19),
      Q => \read_reg_PWM_f_carrier_kHz_rd_AXI_reg[24]_0\(19),
      R => SR(0)
    );
\read_reg_PWM_f_carrier_kHz_rd_AXI_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => D(1),
      Q => \read_reg_PWM_f_carrier_kHz_rd_AXI_reg[24]_0\(1),
      R => SR(0)
    );
\read_reg_PWM_f_carrier_kHz_rd_AXI_reg[20]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => D(20),
      Q => \read_reg_PWM_f_carrier_kHz_rd_AXI_reg[24]_0\(20),
      R => SR(0)
    );
\read_reg_PWM_f_carrier_kHz_rd_AXI_reg[21]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => D(21),
      Q => \read_reg_PWM_f_carrier_kHz_rd_AXI_reg[24]_0\(21),
      R => SR(0)
    );
\read_reg_PWM_f_carrier_kHz_rd_AXI_reg[22]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => D(22),
      Q => \read_reg_PWM_f_carrier_kHz_rd_AXI_reg[24]_0\(22),
      R => SR(0)
    );
\read_reg_PWM_f_carrier_kHz_rd_AXI_reg[23]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => D(23),
      Q => \read_reg_PWM_f_carrier_kHz_rd_AXI_reg[24]_0\(23),
      R => SR(0)
    );
\read_reg_PWM_f_carrier_kHz_rd_AXI_reg[24]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => D(24),
      Q => \read_reg_PWM_f_carrier_kHz_rd_AXI_reg[24]_0\(24),
      R => SR(0)
    );
\read_reg_PWM_f_carrier_kHz_rd_AXI_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => D(2),
      Q => \read_reg_PWM_f_carrier_kHz_rd_AXI_reg[24]_0\(2),
      R => SR(0)
    );
\read_reg_PWM_f_carrier_kHz_rd_AXI_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => D(3),
      Q => \read_reg_PWM_f_carrier_kHz_rd_AXI_reg[24]_0\(3),
      R => SR(0)
    );
\read_reg_PWM_f_carrier_kHz_rd_AXI_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => D(4),
      Q => \read_reg_PWM_f_carrier_kHz_rd_AXI_reg[24]_0\(4),
      R => SR(0)
    );
\read_reg_PWM_f_carrier_kHz_rd_AXI_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => D(5),
      Q => \read_reg_PWM_f_carrier_kHz_rd_AXI_reg[24]_0\(5),
      R => SR(0)
    );
\read_reg_PWM_f_carrier_kHz_rd_AXI_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => D(6),
      Q => \read_reg_PWM_f_carrier_kHz_rd_AXI_reg[24]_0\(6),
      R => SR(0)
    );
\read_reg_PWM_f_carrier_kHz_rd_AXI_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => D(7),
      Q => \read_reg_PWM_f_carrier_kHz_rd_AXI_reg[24]_0\(7),
      R => SR(0)
    );
\read_reg_PWM_f_carrier_kHz_rd_AXI_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => D(8),
      Q => \read_reg_PWM_f_carrier_kHz_rd_AXI_reg[24]_0\(8),
      R => SR(0)
    );
\read_reg_PWM_f_carrier_kHz_rd_AXI_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => D(9),
      Q => \read_reg_PWM_f_carrier_kHz_rd_AXI_reg[24]_0\(9),
      R => SR(0)
    );
\read_reg_PWM_min_pulse_width_rd_AXI_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => \read_reg_PWM_min_pulse_width_rd_AXI_reg[17]_1\(0),
      Q => \read_reg_PWM_min_pulse_width_rd_AXI_reg[17]_0\(0),
      R => SR(0)
    );
\read_reg_PWM_min_pulse_width_rd_AXI_reg[10]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => \read_reg_PWM_min_pulse_width_rd_AXI_reg[17]_1\(10),
      Q => \read_reg_PWM_min_pulse_width_rd_AXI_reg[17]_0\(10),
      R => SR(0)
    );
\read_reg_PWM_min_pulse_width_rd_AXI_reg[11]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => \read_reg_PWM_min_pulse_width_rd_AXI_reg[17]_1\(11),
      Q => \read_reg_PWM_min_pulse_width_rd_AXI_reg[17]_0\(11),
      R => SR(0)
    );
\read_reg_PWM_min_pulse_width_rd_AXI_reg[12]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => \read_reg_PWM_min_pulse_width_rd_AXI_reg[17]_1\(12),
      Q => \read_reg_PWM_min_pulse_width_rd_AXI_reg[17]_0\(12),
      R => SR(0)
    );
\read_reg_PWM_min_pulse_width_rd_AXI_reg[13]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => \read_reg_PWM_min_pulse_width_rd_AXI_reg[17]_1\(13),
      Q => \read_reg_PWM_min_pulse_width_rd_AXI_reg[17]_0\(13),
      R => SR(0)
    );
\read_reg_PWM_min_pulse_width_rd_AXI_reg[14]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => \read_reg_PWM_min_pulse_width_rd_AXI_reg[17]_1\(14),
      Q => \read_reg_PWM_min_pulse_width_rd_AXI_reg[17]_0\(14),
      R => SR(0)
    );
\read_reg_PWM_min_pulse_width_rd_AXI_reg[15]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => \read_reg_PWM_min_pulse_width_rd_AXI_reg[17]_1\(15),
      Q => \read_reg_PWM_min_pulse_width_rd_AXI_reg[17]_0\(15),
      R => SR(0)
    );
\read_reg_PWM_min_pulse_width_rd_AXI_reg[16]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => \read_reg_PWM_min_pulse_width_rd_AXI_reg[17]_1\(16),
      Q => \read_reg_PWM_min_pulse_width_rd_AXI_reg[17]_0\(16),
      R => SR(0)
    );
\read_reg_PWM_min_pulse_width_rd_AXI_reg[17]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => \read_reg_PWM_min_pulse_width_rd_AXI_reg[17]_1\(17),
      Q => \read_reg_PWM_min_pulse_width_rd_AXI_reg[17]_0\(17),
      R => SR(0)
    );
\read_reg_PWM_min_pulse_width_rd_AXI_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => \read_reg_PWM_min_pulse_width_rd_AXI_reg[17]_1\(1),
      Q => \read_reg_PWM_min_pulse_width_rd_AXI_reg[17]_0\(1),
      R => SR(0)
    );
\read_reg_PWM_min_pulse_width_rd_AXI_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => \read_reg_PWM_min_pulse_width_rd_AXI_reg[17]_1\(2),
      Q => \read_reg_PWM_min_pulse_width_rd_AXI_reg[17]_0\(2),
      R => SR(0)
    );
\read_reg_PWM_min_pulse_width_rd_AXI_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => \read_reg_PWM_min_pulse_width_rd_AXI_reg[17]_1\(3),
      Q => \read_reg_PWM_min_pulse_width_rd_AXI_reg[17]_0\(3),
      R => SR(0)
    );
\read_reg_PWM_min_pulse_width_rd_AXI_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => \read_reg_PWM_min_pulse_width_rd_AXI_reg[17]_1\(4),
      Q => \read_reg_PWM_min_pulse_width_rd_AXI_reg[17]_0\(4),
      R => SR(0)
    );
\read_reg_PWM_min_pulse_width_rd_AXI_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => \read_reg_PWM_min_pulse_width_rd_AXI_reg[17]_1\(5),
      Q => \read_reg_PWM_min_pulse_width_rd_AXI_reg[17]_0\(5),
      R => SR(0)
    );
\read_reg_PWM_min_pulse_width_rd_AXI_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => \read_reg_PWM_min_pulse_width_rd_AXI_reg[17]_1\(6),
      Q => \read_reg_PWM_min_pulse_width_rd_AXI_reg[17]_0\(6),
      R => SR(0)
    );
\read_reg_PWM_min_pulse_width_rd_AXI_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => \read_reg_PWM_min_pulse_width_rd_AXI_reg[17]_1\(7),
      Q => \read_reg_PWM_min_pulse_width_rd_AXI_reg[17]_0\(7),
      R => SR(0)
    );
\read_reg_PWM_min_pulse_width_rd_AXI_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => \read_reg_PWM_min_pulse_width_rd_AXI_reg[17]_1\(8),
      Q => \read_reg_PWM_min_pulse_width_rd_AXI_reg[17]_0\(8),
      R => SR(0)
    );
\read_reg_PWM_min_pulse_width_rd_AXI_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => \read_reg_PWM_min_pulse_width_rd_AXI_reg[17]_1\(9),
      Q => \read_reg_PWM_min_pulse_width_rd_AXI_reg[17]_0\(9),
      R => SR(0)
    );
\read_reg_ip_timestamp_reg[30]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => '1',
      Q => read_reg_ip_timestamp(0),
      R => SR(0)
    );
\write_reg_Mode_AXI_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => E(0),
      D => Q(0),
      Q => \write_reg_Mode_AXI_reg[1]_0\(0),
      R => SR(0)
    );
\write_reg_Mode_AXI_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => E(0),
      D => Q(1),
      Q => \write_reg_Mode_AXI_reg[1]_0\(1),
      R => SR(0)
    );
write_reg_PWM_en_AXI_reg: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => write_reg_PWM_en_AXI_reg_0,
      Q => write_PWM_en_AXI,
      R => SR(0)
    );
\write_reg_PWM_min_pulse_width_AXI_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \write_reg_PWM_min_pulse_width_AXI_reg[17]_1\(0),
      D => Q(0),
      Q => \write_reg_PWM_min_pulse_width_AXI_reg[17]_0\(0),
      R => SR(0)
    );
\write_reg_PWM_min_pulse_width_AXI_reg[10]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \write_reg_PWM_min_pulse_width_AXI_reg[17]_1\(0),
      D => Q(10),
      Q => \write_reg_PWM_min_pulse_width_AXI_reg[17]_0\(10),
      R => SR(0)
    );
\write_reg_PWM_min_pulse_width_AXI_reg[11]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \write_reg_PWM_min_pulse_width_AXI_reg[17]_1\(0),
      D => Q(11),
      Q => \write_reg_PWM_min_pulse_width_AXI_reg[17]_0\(11),
      R => SR(0)
    );
\write_reg_PWM_min_pulse_width_AXI_reg[12]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \write_reg_PWM_min_pulse_width_AXI_reg[17]_1\(0),
      D => Q(12),
      Q => \write_reg_PWM_min_pulse_width_AXI_reg[17]_0\(12),
      R => SR(0)
    );
\write_reg_PWM_min_pulse_width_AXI_reg[13]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \write_reg_PWM_min_pulse_width_AXI_reg[17]_1\(0),
      D => Q(13),
      Q => \write_reg_PWM_min_pulse_width_AXI_reg[17]_0\(13),
      R => SR(0)
    );
\write_reg_PWM_min_pulse_width_AXI_reg[14]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \write_reg_PWM_min_pulse_width_AXI_reg[17]_1\(0),
      D => Q(14),
      Q => \write_reg_PWM_min_pulse_width_AXI_reg[17]_0\(14),
      R => SR(0)
    );
\write_reg_PWM_min_pulse_width_AXI_reg[15]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \write_reg_PWM_min_pulse_width_AXI_reg[17]_1\(0),
      D => Q(15),
      Q => \write_reg_PWM_min_pulse_width_AXI_reg[17]_0\(15),
      R => SR(0)
    );
\write_reg_PWM_min_pulse_width_AXI_reg[16]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \write_reg_PWM_min_pulse_width_AXI_reg[17]_1\(0),
      D => Q(16),
      Q => \write_reg_PWM_min_pulse_width_AXI_reg[17]_0\(16),
      R => SR(0)
    );
\write_reg_PWM_min_pulse_width_AXI_reg[17]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \write_reg_PWM_min_pulse_width_AXI_reg[17]_1\(0),
      D => Q(17),
      Q => \write_reg_PWM_min_pulse_width_AXI_reg[17]_0\(17),
      R => SR(0)
    );
\write_reg_PWM_min_pulse_width_AXI_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \write_reg_PWM_min_pulse_width_AXI_reg[17]_1\(0),
      D => Q(1),
      Q => \write_reg_PWM_min_pulse_width_AXI_reg[17]_0\(1),
      R => SR(0)
    );
\write_reg_PWM_min_pulse_width_AXI_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \write_reg_PWM_min_pulse_width_AXI_reg[17]_1\(0),
      D => Q(2),
      Q => \write_reg_PWM_min_pulse_width_AXI_reg[17]_0\(2),
      R => SR(0)
    );
\write_reg_PWM_min_pulse_width_AXI_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \write_reg_PWM_min_pulse_width_AXI_reg[17]_1\(0),
      D => Q(3),
      Q => \write_reg_PWM_min_pulse_width_AXI_reg[17]_0\(3),
      R => SR(0)
    );
\write_reg_PWM_min_pulse_width_AXI_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \write_reg_PWM_min_pulse_width_AXI_reg[17]_1\(0),
      D => Q(4),
      Q => \write_reg_PWM_min_pulse_width_AXI_reg[17]_0\(4),
      R => SR(0)
    );
\write_reg_PWM_min_pulse_width_AXI_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \write_reg_PWM_min_pulse_width_AXI_reg[17]_1\(0),
      D => Q(5),
      Q => \write_reg_PWM_min_pulse_width_AXI_reg[17]_0\(5),
      R => SR(0)
    );
\write_reg_PWM_min_pulse_width_AXI_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \write_reg_PWM_min_pulse_width_AXI_reg[17]_1\(0),
      D => Q(6),
      Q => \write_reg_PWM_min_pulse_width_AXI_reg[17]_0\(6),
      R => SR(0)
    );
\write_reg_PWM_min_pulse_width_AXI_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \write_reg_PWM_min_pulse_width_AXI_reg[17]_1\(0),
      D => Q(7),
      Q => \write_reg_PWM_min_pulse_width_AXI_reg[17]_0\(7),
      R => SR(0)
    );
\write_reg_PWM_min_pulse_width_AXI_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \write_reg_PWM_min_pulse_width_AXI_reg[17]_1\(0),
      D => Q(8),
      Q => \write_reg_PWM_min_pulse_width_AXI_reg[17]_0\(8),
      R => SR(0)
    );
\write_reg_PWM_min_pulse_width_AXI_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \write_reg_PWM_min_pulse_width_AXI_reg[17]_1\(0),
      D => Q(9),
      Q => \write_reg_PWM_min_pulse_width_AXI_reg[17]_0\(9),
      R => SR(0)
    );
\write_reg_Scal_T_carrier_AXI_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \write_reg_Scal_T_carrier_AXI_reg[24]_1\(0),
      D => Q(0),
      Q => \write_reg_Scal_T_carrier_AXI_reg[24]_0\(0),
      R => SR(0)
    );
\write_reg_Scal_T_carrier_AXI_reg[10]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \write_reg_Scal_T_carrier_AXI_reg[24]_1\(0),
      D => Q(10),
      Q => \write_reg_Scal_T_carrier_AXI_reg[24]_0\(10),
      R => SR(0)
    );
\write_reg_Scal_T_carrier_AXI_reg[11]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \write_reg_Scal_T_carrier_AXI_reg[24]_1\(0),
      D => Q(11),
      Q => \write_reg_Scal_T_carrier_AXI_reg[24]_0\(11),
      R => SR(0)
    );
\write_reg_Scal_T_carrier_AXI_reg[12]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \write_reg_Scal_T_carrier_AXI_reg[24]_1\(0),
      D => Q(12),
      Q => \write_reg_Scal_T_carrier_AXI_reg[24]_0\(12),
      R => SR(0)
    );
\write_reg_Scal_T_carrier_AXI_reg[13]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \write_reg_Scal_T_carrier_AXI_reg[24]_1\(0),
      D => Q(13),
      Q => \write_reg_Scal_T_carrier_AXI_reg[24]_0\(13),
      R => SR(0)
    );
\write_reg_Scal_T_carrier_AXI_reg[14]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \write_reg_Scal_T_carrier_AXI_reg[24]_1\(0),
      D => Q(14),
      Q => \write_reg_Scal_T_carrier_AXI_reg[24]_0\(14),
      R => SR(0)
    );
\write_reg_Scal_T_carrier_AXI_reg[15]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \write_reg_Scal_T_carrier_AXI_reg[24]_1\(0),
      D => Q(15),
      Q => \write_reg_Scal_T_carrier_AXI_reg[24]_0\(15),
      R => SR(0)
    );
\write_reg_Scal_T_carrier_AXI_reg[16]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \write_reg_Scal_T_carrier_AXI_reg[24]_1\(0),
      D => Q(16),
      Q => \write_reg_Scal_T_carrier_AXI_reg[24]_0\(16),
      R => SR(0)
    );
\write_reg_Scal_T_carrier_AXI_reg[17]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \write_reg_Scal_T_carrier_AXI_reg[24]_1\(0),
      D => Q(17),
      Q => \write_reg_Scal_T_carrier_AXI_reg[24]_0\(17),
      R => SR(0)
    );
\write_reg_Scal_T_carrier_AXI_reg[18]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \write_reg_Scal_T_carrier_AXI_reg[24]_1\(0),
      D => Q(18),
      Q => \write_reg_Scal_T_carrier_AXI_reg[24]_0\(18),
      R => SR(0)
    );
\write_reg_Scal_T_carrier_AXI_reg[19]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \write_reg_Scal_T_carrier_AXI_reg[24]_1\(0),
      D => Q(19),
      Q => \write_reg_Scal_T_carrier_AXI_reg[24]_0\(19),
      R => SR(0)
    );
\write_reg_Scal_T_carrier_AXI_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \write_reg_Scal_T_carrier_AXI_reg[24]_1\(0),
      D => Q(1),
      Q => \write_reg_Scal_T_carrier_AXI_reg[24]_0\(1),
      R => SR(0)
    );
\write_reg_Scal_T_carrier_AXI_reg[20]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \write_reg_Scal_T_carrier_AXI_reg[24]_1\(0),
      D => Q(20),
      Q => \write_reg_Scal_T_carrier_AXI_reg[24]_0\(20),
      R => SR(0)
    );
\write_reg_Scal_T_carrier_AXI_reg[21]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \write_reg_Scal_T_carrier_AXI_reg[24]_1\(0),
      D => Q(21),
      Q => \write_reg_Scal_T_carrier_AXI_reg[24]_0\(21),
      R => SR(0)
    );
\write_reg_Scal_T_carrier_AXI_reg[22]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \write_reg_Scal_T_carrier_AXI_reg[24]_1\(0),
      D => Q(22),
      Q => \write_reg_Scal_T_carrier_AXI_reg[24]_0\(22),
      R => SR(0)
    );
\write_reg_Scal_T_carrier_AXI_reg[23]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \write_reg_Scal_T_carrier_AXI_reg[24]_1\(0),
      D => Q(23),
      Q => \write_reg_Scal_T_carrier_AXI_reg[24]_0\(23),
      R => SR(0)
    );
\write_reg_Scal_T_carrier_AXI_reg[24]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \write_reg_Scal_T_carrier_AXI_reg[24]_1\(0),
      D => Q(24),
      Q => \write_reg_Scal_T_carrier_AXI_reg[24]_0\(24),
      R => SR(0)
    );
\write_reg_Scal_T_carrier_AXI_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \write_reg_Scal_T_carrier_AXI_reg[24]_1\(0),
      D => Q(2),
      Q => \write_reg_Scal_T_carrier_AXI_reg[24]_0\(2),
      R => SR(0)
    );
\write_reg_Scal_T_carrier_AXI_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \write_reg_Scal_T_carrier_AXI_reg[24]_1\(0),
      D => Q(3),
      Q => \write_reg_Scal_T_carrier_AXI_reg[24]_0\(3),
      R => SR(0)
    );
\write_reg_Scal_T_carrier_AXI_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \write_reg_Scal_T_carrier_AXI_reg[24]_1\(0),
      D => Q(4),
      Q => \write_reg_Scal_T_carrier_AXI_reg[24]_0\(4),
      R => SR(0)
    );
\write_reg_Scal_T_carrier_AXI_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \write_reg_Scal_T_carrier_AXI_reg[24]_1\(0),
      D => Q(5),
      Q => \write_reg_Scal_T_carrier_AXI_reg[24]_0\(5),
      R => SR(0)
    );
\write_reg_Scal_T_carrier_AXI_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \write_reg_Scal_T_carrier_AXI_reg[24]_1\(0),
      D => Q(6),
      Q => \write_reg_Scal_T_carrier_AXI_reg[24]_0\(6),
      R => SR(0)
    );
\write_reg_Scal_T_carrier_AXI_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \write_reg_Scal_T_carrier_AXI_reg[24]_1\(0),
      D => Q(7),
      Q => \write_reg_Scal_T_carrier_AXI_reg[24]_0\(7),
      R => SR(0)
    );
\write_reg_Scal_T_carrier_AXI_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \write_reg_Scal_T_carrier_AXI_reg[24]_1\(0),
      D => Q(8),
      Q => \write_reg_Scal_T_carrier_AXI_reg[24]_0\(8),
      R => SR(0)
    );
\write_reg_Scal_T_carrier_AXI_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \write_reg_Scal_T_carrier_AXI_reg[24]_1\(0),
      D => Q(9),
      Q => \write_reg_Scal_T_carrier_AXI_reg[24]_0\(9),
      R => SR(0)
    );
\write_reg_Scal_f_carrier_AXI_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \write_reg_Scal_f_carrier_AXI_reg[24]_1\(0),
      D => Q(0),
      Q => \write_reg_Scal_f_carrier_AXI_reg[24]_0\(0),
      R => SR(0)
    );
\write_reg_Scal_f_carrier_AXI_reg[10]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \write_reg_Scal_f_carrier_AXI_reg[24]_1\(0),
      D => Q(10),
      Q => \write_reg_Scal_f_carrier_AXI_reg[24]_0\(10),
      R => SR(0)
    );
\write_reg_Scal_f_carrier_AXI_reg[11]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \write_reg_Scal_f_carrier_AXI_reg[24]_1\(0),
      D => Q(11),
      Q => \write_reg_Scal_f_carrier_AXI_reg[24]_0\(11),
      R => SR(0)
    );
\write_reg_Scal_f_carrier_AXI_reg[12]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \write_reg_Scal_f_carrier_AXI_reg[24]_1\(0),
      D => Q(12),
      Q => \write_reg_Scal_f_carrier_AXI_reg[24]_0\(12),
      R => SR(0)
    );
\write_reg_Scal_f_carrier_AXI_reg[13]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \write_reg_Scal_f_carrier_AXI_reg[24]_1\(0),
      D => Q(13),
      Q => \write_reg_Scal_f_carrier_AXI_reg[24]_0\(13),
      R => SR(0)
    );
\write_reg_Scal_f_carrier_AXI_reg[14]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \write_reg_Scal_f_carrier_AXI_reg[24]_1\(0),
      D => Q(14),
      Q => \write_reg_Scal_f_carrier_AXI_reg[24]_0\(14),
      R => SR(0)
    );
\write_reg_Scal_f_carrier_AXI_reg[15]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \write_reg_Scal_f_carrier_AXI_reg[24]_1\(0),
      D => Q(15),
      Q => \write_reg_Scal_f_carrier_AXI_reg[24]_0\(15),
      R => SR(0)
    );
\write_reg_Scal_f_carrier_AXI_reg[16]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \write_reg_Scal_f_carrier_AXI_reg[24]_1\(0),
      D => Q(16),
      Q => \write_reg_Scal_f_carrier_AXI_reg[24]_0\(16),
      R => SR(0)
    );
\write_reg_Scal_f_carrier_AXI_reg[17]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \write_reg_Scal_f_carrier_AXI_reg[24]_1\(0),
      D => Q(17),
      Q => \write_reg_Scal_f_carrier_AXI_reg[24]_0\(17),
      R => SR(0)
    );
\write_reg_Scal_f_carrier_AXI_reg[18]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \write_reg_Scal_f_carrier_AXI_reg[24]_1\(0),
      D => Q(18),
      Q => \write_reg_Scal_f_carrier_AXI_reg[24]_0\(18),
      R => SR(0)
    );
\write_reg_Scal_f_carrier_AXI_reg[19]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \write_reg_Scal_f_carrier_AXI_reg[24]_1\(0),
      D => Q(19),
      Q => \write_reg_Scal_f_carrier_AXI_reg[24]_0\(19),
      R => SR(0)
    );
\write_reg_Scal_f_carrier_AXI_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \write_reg_Scal_f_carrier_AXI_reg[24]_1\(0),
      D => Q(1),
      Q => \write_reg_Scal_f_carrier_AXI_reg[24]_0\(1),
      R => SR(0)
    );
\write_reg_Scal_f_carrier_AXI_reg[20]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \write_reg_Scal_f_carrier_AXI_reg[24]_1\(0),
      D => Q(20),
      Q => \write_reg_Scal_f_carrier_AXI_reg[24]_0\(20),
      R => SR(0)
    );
\write_reg_Scal_f_carrier_AXI_reg[21]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \write_reg_Scal_f_carrier_AXI_reg[24]_1\(0),
      D => Q(21),
      Q => \write_reg_Scal_f_carrier_AXI_reg[24]_0\(21),
      R => SR(0)
    );
\write_reg_Scal_f_carrier_AXI_reg[22]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \write_reg_Scal_f_carrier_AXI_reg[24]_1\(0),
      D => Q(22),
      Q => \write_reg_Scal_f_carrier_AXI_reg[24]_0\(22),
      R => SR(0)
    );
\write_reg_Scal_f_carrier_AXI_reg[23]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \write_reg_Scal_f_carrier_AXI_reg[24]_1\(0),
      D => Q(23),
      Q => \write_reg_Scal_f_carrier_AXI_reg[24]_0\(23),
      R => SR(0)
    );
\write_reg_Scal_f_carrier_AXI_reg[24]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \write_reg_Scal_f_carrier_AXI_reg[24]_1\(0),
      D => Q(24),
      Q => \write_reg_Scal_f_carrier_AXI_reg[24]_0\(24),
      R => SR(0)
    );
\write_reg_Scal_f_carrier_AXI_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \write_reg_Scal_f_carrier_AXI_reg[24]_1\(0),
      D => Q(2),
      Q => \write_reg_Scal_f_carrier_AXI_reg[24]_0\(2),
      R => SR(0)
    );
\write_reg_Scal_f_carrier_AXI_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \write_reg_Scal_f_carrier_AXI_reg[24]_1\(0),
      D => Q(3),
      Q => \write_reg_Scal_f_carrier_AXI_reg[24]_0\(3),
      R => SR(0)
    );
\write_reg_Scal_f_carrier_AXI_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \write_reg_Scal_f_carrier_AXI_reg[24]_1\(0),
      D => Q(4),
      Q => \write_reg_Scal_f_carrier_AXI_reg[24]_0\(4),
      R => SR(0)
    );
\write_reg_Scal_f_carrier_AXI_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \write_reg_Scal_f_carrier_AXI_reg[24]_1\(0),
      D => Q(5),
      Q => \write_reg_Scal_f_carrier_AXI_reg[24]_0\(5),
      R => SR(0)
    );
\write_reg_Scal_f_carrier_AXI_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \write_reg_Scal_f_carrier_AXI_reg[24]_1\(0),
      D => Q(6),
      Q => \write_reg_Scal_f_carrier_AXI_reg[24]_0\(6),
      R => SR(0)
    );
\write_reg_Scal_f_carrier_AXI_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \write_reg_Scal_f_carrier_AXI_reg[24]_1\(0),
      D => Q(7),
      Q => \write_reg_Scal_f_carrier_AXI_reg[24]_0\(7),
      R => SR(0)
    );
\write_reg_Scal_f_carrier_AXI_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \write_reg_Scal_f_carrier_AXI_reg[24]_1\(0),
      D => Q(8),
      Q => \write_reg_Scal_f_carrier_AXI_reg[24]_0\(8),
      R => SR(0)
    );
\write_reg_Scal_f_carrier_AXI_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \write_reg_Scal_f_carrier_AXI_reg[24]_1\(0),
      D => Q(9),
      Q => \write_reg_Scal_f_carrier_AXI_reg[24]_0\(9),
      R => SR(0)
    );
\write_reg_TriState_HB1_AXI_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \write_reg_TriState_HB1_AXI_reg[1]_1\(0),
      D => Q(0),
      Q => \write_reg_TriState_HB1_AXI_reg[1]_0\(0),
      R => SR(0)
    );
\write_reg_TriState_HB1_AXI_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \write_reg_TriState_HB1_AXI_reg[1]_1\(0),
      D => Q(1),
      Q => \write_reg_TriState_HB1_AXI_reg[1]_0\(1),
      R => SR(0)
    );
\write_reg_TriState_HB2_AXI_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \write_reg_TriState_HB2_AXI_reg[1]_1\(0),
      D => Q(0),
      Q => \write_reg_TriState_HB2_AXI_reg[1]_0\(0),
      R => SR(0)
    );
\write_reg_TriState_HB2_AXI_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \write_reg_TriState_HB2_AXI_reg[1]_1\(0),
      D => Q(1),
      Q => \write_reg_TriState_HB2_AXI_reg[1]_0\(1),
      R => SR(0)
    );
\write_reg_TriState_HB3_AXI_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \write_reg_TriState_HB3_AXI_reg[1]_1\(0),
      D => Q(0),
      Q => \write_reg_TriState_HB3_AXI_reg[1]_0\(0),
      R => SR(0)
    );
\write_reg_TriState_HB3_AXI_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \write_reg_TriState_HB3_AXI_reg[1]_1\(0),
      D => Q(1),
      Q => \write_reg_TriState_HB3_AXI_reg[1]_0\(1),
      R => SR(0)
    );
write_reg_axi_enable_reg: unisim.vcomponents.FDSE
     port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => write_reg_axi_enable_reg_0,
      Q => \^cea1\,
      S => SR(0)
    );
\write_reg_m_u1_norm_AXI_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \write_reg_m_u1_norm_AXI_reg[13]_1\(0),
      D => Q(0),
      Q => \write_reg_m_u1_norm_AXI_reg[13]_0\(0),
      R => SR(0)
    );
\write_reg_m_u1_norm_AXI_reg[10]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \write_reg_m_u1_norm_AXI_reg[13]_1\(0),
      D => Q(10),
      Q => \write_reg_m_u1_norm_AXI_reg[13]_0\(10),
      R => SR(0)
    );
\write_reg_m_u1_norm_AXI_reg[11]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \write_reg_m_u1_norm_AXI_reg[13]_1\(0),
      D => Q(11),
      Q => \write_reg_m_u1_norm_AXI_reg[13]_0\(11),
      R => SR(0)
    );
\write_reg_m_u1_norm_AXI_reg[12]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \write_reg_m_u1_norm_AXI_reg[13]_1\(0),
      D => Q(12),
      Q => \write_reg_m_u1_norm_AXI_reg[13]_0\(12),
      R => SR(0)
    );
\write_reg_m_u1_norm_AXI_reg[13]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \write_reg_m_u1_norm_AXI_reg[13]_1\(0),
      D => Q(13),
      Q => \write_reg_m_u1_norm_AXI_reg[13]_0\(13),
      R => SR(0)
    );
\write_reg_m_u1_norm_AXI_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \write_reg_m_u1_norm_AXI_reg[13]_1\(0),
      D => Q(1),
      Q => \write_reg_m_u1_norm_AXI_reg[13]_0\(1),
      R => SR(0)
    );
\write_reg_m_u1_norm_AXI_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \write_reg_m_u1_norm_AXI_reg[13]_1\(0),
      D => Q(2),
      Q => \write_reg_m_u1_norm_AXI_reg[13]_0\(2),
      R => SR(0)
    );
\write_reg_m_u1_norm_AXI_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \write_reg_m_u1_norm_AXI_reg[13]_1\(0),
      D => Q(3),
      Q => \write_reg_m_u1_norm_AXI_reg[13]_0\(3),
      R => SR(0)
    );
\write_reg_m_u1_norm_AXI_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \write_reg_m_u1_norm_AXI_reg[13]_1\(0),
      D => Q(4),
      Q => \write_reg_m_u1_norm_AXI_reg[13]_0\(4),
      R => SR(0)
    );
\write_reg_m_u1_norm_AXI_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \write_reg_m_u1_norm_AXI_reg[13]_1\(0),
      D => Q(5),
      Q => \write_reg_m_u1_norm_AXI_reg[13]_0\(5),
      R => SR(0)
    );
\write_reg_m_u1_norm_AXI_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \write_reg_m_u1_norm_AXI_reg[13]_1\(0),
      D => Q(6),
      Q => \write_reg_m_u1_norm_AXI_reg[13]_0\(6),
      R => SR(0)
    );
\write_reg_m_u1_norm_AXI_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \write_reg_m_u1_norm_AXI_reg[13]_1\(0),
      D => Q(7),
      Q => \write_reg_m_u1_norm_AXI_reg[13]_0\(7),
      R => SR(0)
    );
\write_reg_m_u1_norm_AXI_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \write_reg_m_u1_norm_AXI_reg[13]_1\(0),
      D => Q(8),
      Q => \write_reg_m_u1_norm_AXI_reg[13]_0\(8),
      R => SR(0)
    );
\write_reg_m_u1_norm_AXI_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \write_reg_m_u1_norm_AXI_reg[13]_1\(0),
      D => Q(9),
      Q => \write_reg_m_u1_norm_AXI_reg[13]_0\(9),
      R => SR(0)
    );
\write_reg_m_u2_norm_AXI_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \write_reg_m_u2_norm_AXI_reg[13]_1\(0),
      D => Q(0),
      Q => \write_reg_m_u2_norm_AXI_reg[13]_0\(0),
      R => SR(0)
    );
\write_reg_m_u2_norm_AXI_reg[10]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \write_reg_m_u2_norm_AXI_reg[13]_1\(0),
      D => Q(10),
      Q => \write_reg_m_u2_norm_AXI_reg[13]_0\(10),
      R => SR(0)
    );
\write_reg_m_u2_norm_AXI_reg[11]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \write_reg_m_u2_norm_AXI_reg[13]_1\(0),
      D => Q(11),
      Q => \write_reg_m_u2_norm_AXI_reg[13]_0\(11),
      R => SR(0)
    );
\write_reg_m_u2_norm_AXI_reg[12]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \write_reg_m_u2_norm_AXI_reg[13]_1\(0),
      D => Q(12),
      Q => \write_reg_m_u2_norm_AXI_reg[13]_0\(12),
      R => SR(0)
    );
\write_reg_m_u2_norm_AXI_reg[13]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \write_reg_m_u2_norm_AXI_reg[13]_1\(0),
      D => Q(13),
      Q => \write_reg_m_u2_norm_AXI_reg[13]_0\(13),
      R => SR(0)
    );
\write_reg_m_u2_norm_AXI_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \write_reg_m_u2_norm_AXI_reg[13]_1\(0),
      D => Q(1),
      Q => \write_reg_m_u2_norm_AXI_reg[13]_0\(1),
      R => SR(0)
    );
\write_reg_m_u2_norm_AXI_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \write_reg_m_u2_norm_AXI_reg[13]_1\(0),
      D => Q(2),
      Q => \write_reg_m_u2_norm_AXI_reg[13]_0\(2),
      R => SR(0)
    );
\write_reg_m_u2_norm_AXI_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \write_reg_m_u2_norm_AXI_reg[13]_1\(0),
      D => Q(3),
      Q => \write_reg_m_u2_norm_AXI_reg[13]_0\(3),
      R => SR(0)
    );
\write_reg_m_u2_norm_AXI_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \write_reg_m_u2_norm_AXI_reg[13]_1\(0),
      D => Q(4),
      Q => \write_reg_m_u2_norm_AXI_reg[13]_0\(4),
      R => SR(0)
    );
\write_reg_m_u2_norm_AXI_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \write_reg_m_u2_norm_AXI_reg[13]_1\(0),
      D => Q(5),
      Q => \write_reg_m_u2_norm_AXI_reg[13]_0\(5),
      R => SR(0)
    );
\write_reg_m_u2_norm_AXI_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \write_reg_m_u2_norm_AXI_reg[13]_1\(0),
      D => Q(6),
      Q => \write_reg_m_u2_norm_AXI_reg[13]_0\(6),
      R => SR(0)
    );
\write_reg_m_u2_norm_AXI_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \write_reg_m_u2_norm_AXI_reg[13]_1\(0),
      D => Q(7),
      Q => \write_reg_m_u2_norm_AXI_reg[13]_0\(7),
      R => SR(0)
    );
\write_reg_m_u2_norm_AXI_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \write_reg_m_u2_norm_AXI_reg[13]_1\(0),
      D => Q(8),
      Q => \write_reg_m_u2_norm_AXI_reg[13]_0\(8),
      R => SR(0)
    );
\write_reg_m_u2_norm_AXI_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \write_reg_m_u2_norm_AXI_reg[13]_1\(0),
      D => Q(9),
      Q => \write_reg_m_u2_norm_AXI_reg[13]_0\(9),
      R => SR(0)
    );
\write_reg_m_u3_norm_AXI_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \write_reg_m_u3_norm_AXI_reg[13]_1\(0),
      D => Q(0),
      Q => \write_reg_m_u3_norm_AXI_reg[13]_0\(0),
      R => SR(0)
    );
\write_reg_m_u3_norm_AXI_reg[10]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \write_reg_m_u3_norm_AXI_reg[13]_1\(0),
      D => Q(10),
      Q => \write_reg_m_u3_norm_AXI_reg[13]_0\(10),
      R => SR(0)
    );
\write_reg_m_u3_norm_AXI_reg[11]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \write_reg_m_u3_norm_AXI_reg[13]_1\(0),
      D => Q(11),
      Q => \write_reg_m_u3_norm_AXI_reg[13]_0\(11),
      R => SR(0)
    );
\write_reg_m_u3_norm_AXI_reg[12]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \write_reg_m_u3_norm_AXI_reg[13]_1\(0),
      D => Q(12),
      Q => \write_reg_m_u3_norm_AXI_reg[13]_0\(12),
      R => SR(0)
    );
\write_reg_m_u3_norm_AXI_reg[13]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \write_reg_m_u3_norm_AXI_reg[13]_1\(0),
      D => Q(13),
      Q => \write_reg_m_u3_norm_AXI_reg[13]_0\(13),
      R => SR(0)
    );
\write_reg_m_u3_norm_AXI_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \write_reg_m_u3_norm_AXI_reg[13]_1\(0),
      D => Q(1),
      Q => \write_reg_m_u3_norm_AXI_reg[13]_0\(1),
      R => SR(0)
    );
\write_reg_m_u3_norm_AXI_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \write_reg_m_u3_norm_AXI_reg[13]_1\(0),
      D => Q(2),
      Q => \write_reg_m_u3_norm_AXI_reg[13]_0\(2),
      R => SR(0)
    );
\write_reg_m_u3_norm_AXI_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \write_reg_m_u3_norm_AXI_reg[13]_1\(0),
      D => Q(3),
      Q => \write_reg_m_u3_norm_AXI_reg[13]_0\(3),
      R => SR(0)
    );
\write_reg_m_u3_norm_AXI_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \write_reg_m_u3_norm_AXI_reg[13]_1\(0),
      D => Q(4),
      Q => \write_reg_m_u3_norm_AXI_reg[13]_0\(4),
      R => SR(0)
    );
\write_reg_m_u3_norm_AXI_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \write_reg_m_u3_norm_AXI_reg[13]_1\(0),
      D => Q(5),
      Q => \write_reg_m_u3_norm_AXI_reg[13]_0\(5),
      R => SR(0)
    );
\write_reg_m_u3_norm_AXI_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \write_reg_m_u3_norm_AXI_reg[13]_1\(0),
      D => Q(6),
      Q => \write_reg_m_u3_norm_AXI_reg[13]_0\(6),
      R => SR(0)
    );
\write_reg_m_u3_norm_AXI_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \write_reg_m_u3_norm_AXI_reg[13]_1\(0),
      D => Q(7),
      Q => \write_reg_m_u3_norm_AXI_reg[13]_0\(7),
      R => SR(0)
    );
\write_reg_m_u3_norm_AXI_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \write_reg_m_u3_norm_AXI_reg[13]_1\(0),
      D => Q(8),
      Q => \write_reg_m_u3_norm_AXI_reg[13]_0\(8),
      R => SR(0)
    );
\write_reg_m_u3_norm_AXI_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \write_reg_m_u3_norm_AXI_reg[13]_1\(0),
      D => Q(9),
      Q => \write_reg_m_u3_norm_AXI_reg[13]_0\(9),
      R => SR(0)
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity zusys_PWM_and_SS_control_V_0_2_PWM_and_SS_control_V3_ip_axi_lite_module is
  port (
    FSM_sequential_axi_lite_rstate_reg_0 : out STD_LOGIC;
    \wdata_reg[0]_0\ : out STD_LOGIC;
    Q : out STD_LOGIC_VECTOR ( 24 downto 0 );
    \wdata_reg[0]_1\ : out STD_LOGIC;
    \AXI4_Lite_ARADDR[3]\ : out STD_LOGIC_VECTOR ( 0 to 0 );
    \AXI4_Lite_ARADDR[6]\ : out STD_LOGIC_VECTOR ( 0 to 0 );
    \AXI4_Lite_ARADDR[6]_0\ : out STD_LOGIC_VECTOR ( 0 to 0 );
    \AXI4_Lite_ARADDR[3]_0\ : out STD_LOGIC_VECTOR ( 0 to 0 );
    \AXI4_Lite_ARADDR[3]_1\ : out STD_LOGIC_VECTOR ( 0 to 0 );
    \AXI4_Lite_ARADDR[4]\ : out STD_LOGIC_VECTOR ( 0 to 0 );
    \AXI4_Lite_ARADDR[3]_2\ : out STD_LOGIC_VECTOR ( 0 to 0 );
    \waddr_reg[3]_0\ : out STD_LOGIC_VECTOR ( 0 to 0 );
    \AXI4_Lite_ARADDR[3]_3\ : out STD_LOGIC_VECTOR ( 0 to 0 );
    E : out STD_LOGIC_VECTOR ( 0 to 0 );
    AXI4_Lite_ARREADY : out STD_LOGIC;
    \FSM_onehot_axi_lite_wstate_reg[2]_0\ : out STD_LOGIC_VECTOR ( 1 downto 0 );
    AXI4_Lite_AWREADY : out STD_LOGIC;
    reset : out STD_LOGIC;
    AXI4_Lite_RDATA : out STD_LOGIC_VECTOR ( 26 downto 0 );
    AXI4_Lite_ACLK : in STD_LOGIC;
    CEA1 : in STD_LOGIC;
    write_PWM_en_AXI : in STD_LOGIC;
    AXI4_Lite_ARVALID : in STD_LOGIC;
    AXI4_Lite_ARADDR : in STD_LOGIC_VECTOR ( 13 downto 0 );
    read_reg_PWM_en_rd_AXI : in STD_LOGIC;
    \AXI4_Lite_RDATA_tmp_reg[1]_0\ : in STD_LOGIC_VECTOR ( 1 downto 0 );
    \AXI4_Lite_RDATA_tmp_reg[24]_0\ : in STD_LOGIC_VECTOR ( 24 downto 0 );
    \AXI4_Lite_RDATA_tmp_reg[24]_1\ : in STD_LOGIC_VECTOR ( 24 downto 0 );
    \AXI4_Lite_RDATA_tmp_reg[30]_0\ : in STD_LOGIC_VECTOR ( 17 downto 0 );
    read_reg_ip_timestamp : in STD_LOGIC_VECTOR ( 0 to 0 );
    AXI4_Lite_RREADY : in STD_LOGIC;
    AXI4_Lite_AWVALID : in STD_LOGIC;
    AXI4_Lite_WVALID : in STD_LOGIC;
    AXI4_Lite_ARESETN : in STD_LOGIC;
    IPCORE_RESETN : in STD_LOGIC;
    AXI4_Lite_BREADY : in STD_LOGIC;
    AXI4_Lite_WSTRB : in STD_LOGIC_VECTOR ( 3 downto 0 );
    AXI4_Lite_AWADDR : in STD_LOGIC_VECTOR ( 13 downto 0 );
    AXI4_Lite_WDATA : in STD_LOGIC_VECTOR ( 24 downto 0 )
  );
end zusys_PWM_and_SS_control_V_0_2_PWM_and_SS_control_V3_ip_axi_lite_module;

architecture STRUCTURE of zusys_PWM_and_SS_control_V_0_2_PWM_and_SS_control_V3_ip_axi_lite_module is
  signal \AXI4_Lite_RDATA_tmp[0]_i_2_n_0\ : STD_LOGIC;
  signal \AXI4_Lite_RDATA_tmp[0]_i_4_n_0\ : STD_LOGIC;
  signal \AXI4_Lite_RDATA_tmp[0]_i_5_n_0\ : STD_LOGIC;
  signal \AXI4_Lite_RDATA_tmp[10]_i_2_n_0\ : STD_LOGIC;
  signal \AXI4_Lite_RDATA_tmp[11]_i_2_n_0\ : STD_LOGIC;
  signal \AXI4_Lite_RDATA_tmp[13]_i_2_n_0\ : STD_LOGIC;
  signal \AXI4_Lite_RDATA_tmp[16]_i_2_n_0\ : STD_LOGIC;
  signal \AXI4_Lite_RDATA_tmp[16]_i_3_n_0\ : STD_LOGIC;
  signal \AXI4_Lite_RDATA_tmp[1]_i_3_n_0\ : STD_LOGIC;
  signal \AXI4_Lite_RDATA_tmp[23]_i_2_n_0\ : STD_LOGIC;
  signal \AXI4_Lite_RDATA_tmp[24]_i_2_n_0\ : STD_LOGIC;
  signal \AXI4_Lite_RDATA_tmp[24]_i_3_n_0\ : STD_LOGIC;
  signal \AXI4_Lite_RDATA_tmp[24]_i_4_n_0\ : STD_LOGIC;
  signal \AXI4_Lite_RDATA_tmp[30]_i_2_n_0\ : STD_LOGIC;
  signal \AXI4_Lite_RDATA_tmp[30]_i_3_n_0\ : STD_LOGIC;
  signal \AXI4_Lite_RDATA_tmp[30]_i_4_n_0\ : STD_LOGIC;
  signal \AXI4_Lite_RDATA_tmp[30]_i_5_n_0\ : STD_LOGIC;
  signal \AXI4_Lite_RDATA_tmp[30]_i_6_n_0\ : STD_LOGIC;
  signal \AXI4_Lite_RDATA_tmp[30]_i_7_n_0\ : STD_LOGIC;
  signal \AXI4_Lite_RDATA_tmp[30]_i_8_n_0\ : STD_LOGIC;
  signal \AXI4_Lite_RDATA_tmp[31]_i_3_n_0\ : STD_LOGIC;
  signal \AXI4_Lite_RDATA_tmp[31]_i_4_n_0\ : STD_LOGIC;
  signal \AXI4_Lite_RDATA_tmp[31]_i_5_n_0\ : STD_LOGIC;
  signal \AXI4_Lite_RDATA_tmp[31]_i_6_n_0\ : STD_LOGIC;
  signal \AXI4_Lite_RDATA_tmp[31]_i_7_n_0\ : STD_LOGIC;
  signal \AXI4_Lite_RDATA_tmp[31]_i_8_n_0\ : STD_LOGIC;
  signal \AXI4_Lite_RDATA_tmp[31]_i_9_n_0\ : STD_LOGIC;
  signal \AXI4_Lite_RDATA_tmp[4]_i_2_n_0\ : STD_LOGIC;
  signal \AXI4_Lite_RDATA_tmp[5]_i_2_n_0\ : STD_LOGIC;
  signal \AXI4_Lite_RDATA_tmp[6]_i_2_n_0\ : STD_LOGIC;
  signal \AXI4_Lite_RDATA_tmp[8]_i_2_n_0\ : STD_LOGIC;
  signal \AXI4_Lite_RDATA_tmp[9]_i_2_n_0\ : STD_LOGIC;
  signal \^fsm_onehot_axi_lite_wstate_reg[2]_0\ : STD_LOGIC_VECTOR ( 1 downto 0 );
  signal \FSM_onehot_axi_lite_wstate_reg_n_0_[0]\ : STD_LOGIC;
  signal \^fsm_sequential_axi_lite_rstate_reg_0\ : STD_LOGIC;
  signal \^q\ : STD_LOGIC_VECTOR ( 24 downto 0 );
  signal aw_transfer : STD_LOGIC;
  signal axi_lite_rstate_next : STD_LOGIC;
  signal axi_lite_wstate_next : STD_LOGIC_VECTOR ( 2 downto 0 );
  signal data_read : STD_LOGIC_VECTOR ( 31 downto 0 );
  signal decode_sel_Mode_rd_AXI : STD_LOGIC;
  signal decode_sel_PWM_en_rd_AXI : STD_LOGIC;
  signal reset_0 : STD_LOGIC;
  signal sel0 : STD_LOGIC_VECTOR ( 13 downto 0 );
  signal soft_reset : STD_LOGIC;
  signal soft_reset_i_1_n_0 : STD_LOGIC;
  signal soft_reset_i_2_n_0 : STD_LOGIC;
  signal soft_reset_i_3_n_0 : STD_LOGIC;
  signal soft_reset_i_4_n_0 : STD_LOGIC;
  signal top_rd_enb : STD_LOGIC;
  signal top_wr_enb : STD_LOGIC;
  signal w_transfer : STD_LOGIC;
  signal w_transfer_and_wstrb : STD_LOGIC;
  signal \write_reg_Mode_AXI[1]_i_2_n_0\ : STD_LOGIC;
  signal \write_reg_Mode_AXI[1]_i_3_n_0\ : STD_LOGIC;
  signal \write_reg_Mode_AXI[1]_i_4_n_0\ : STD_LOGIC;
  signal \write_reg_Mode_AXI[1]_i_5_n_0\ : STD_LOGIC;
  signal \write_reg_Mode_AXI[1]_i_6_n_0\ : STD_LOGIC;
  signal \write_reg_Mode_AXI[1]_i_7_n_0\ : STD_LOGIC;
  signal \write_reg_Mode_AXI[1]_i_8_n_0\ : STD_LOGIC;
  signal write_reg_PWM_en_AXI_i_2_n_0 : STD_LOGIC;
  signal write_reg_PWM_en_AXI_i_3_n_0 : STD_LOGIC;
  signal \write_reg_PWM_min_pulse_width_AXI[17]_i_2_n_0\ : STD_LOGIC;
  signal \write_reg_PWM_min_pulse_width_AXI[17]_i_3_n_0\ : STD_LOGIC;
  signal \write_reg_Scal_f_carrier_AXI[24]_i_2_n_0\ : STD_LOGIC;
  signal \write_reg_Scal_f_carrier_AXI[24]_i_3_n_0\ : STD_LOGIC;
  signal write_reg_axi_enable_i_2_n_0 : STD_LOGIC;
  signal write_reg_axi_enable_i_3_n_0 : STD_LOGIC;
  attribute SOFT_HLUTNM : string;
  attribute SOFT_HLUTNM of AXI4_Lite_ARREADY_INST_0 : label is "soft_lutpair6";
  attribute SOFT_HLUTNM of AXI4_Lite_AWREADY_INST_0 : label is "soft_lutpair7";
  attribute SOFT_HLUTNM of \AXI4_Lite_RDATA_tmp[0]_i_3\ : label is "soft_lutpair1";
  attribute SOFT_HLUTNM of \AXI4_Lite_RDATA_tmp[30]_i_3\ : label is "soft_lutpair8";
  attribute SOFT_HLUTNM of \AXI4_Lite_RDATA_tmp[30]_i_4\ : label is "soft_lutpair4";
  attribute SOFT_HLUTNM of \AXI4_Lite_RDATA_tmp[30]_i_5\ : label is "soft_lutpair1";
  attribute SOFT_HLUTNM of \AXI4_Lite_RDATA_tmp[30]_i_8\ : label is "soft_lutpair8";
  attribute SOFT_HLUTNM of \AXI4_Lite_RDATA_tmp[31]_i_3\ : label is "soft_lutpair3";
  attribute SOFT_HLUTNM of \AXI4_Lite_RDATA_tmp[31]_i_5\ : label is "soft_lutpair9";
  attribute SOFT_HLUTNM of \AXI4_Lite_RDATA_tmp[31]_i_7\ : label is "soft_lutpair2";
  attribute SOFT_HLUTNM of \FSM_onehot_axi_lite_wstate[1]_i_2\ : label is "soft_lutpair7";
  attribute FSM_ENCODED_STATES : string;
  attribute FSM_ENCODED_STATES of \FSM_onehot_axi_lite_wstate_reg[0]\ : label is "iSTATE:010,iSTATE0:100,iSTATE1:001";
  attribute FSM_ENCODED_STATES of \FSM_onehot_axi_lite_wstate_reg[1]\ : label is "iSTATE:010,iSTATE0:100,iSTATE1:001";
  attribute FSM_ENCODED_STATES of \FSM_onehot_axi_lite_wstate_reg[2]\ : label is "iSTATE:010,iSTATE0:100,iSTATE1:001";
  attribute SOFT_HLUTNM of FSM_sequential_axi_lite_rstate_i_1 : label is "soft_lutpair6";
  attribute FSM_ENCODED_STATES of FSM_sequential_axi_lite_rstate_reg : label is "iSTATE:0,iSTATE0:1";
  attribute SOFT_HLUTNM of \write_reg_Mode_AXI[1]_i_1\ : label is "soft_lutpair0";
  attribute SOFT_HLUTNM of \write_reg_Mode_AXI[1]_i_7\ : label is "soft_lutpair5";
  attribute SOFT_HLUTNM of \write_reg_Mode_AXI[1]_i_8\ : label is "soft_lutpair9";
  attribute SOFT_HLUTNM of write_reg_PWM_en_AXI_i_2 : label is "soft_lutpair5";
  attribute SOFT_HLUTNM of \write_reg_PWM_min_pulse_width_AXI[17]_i_3\ : label is "soft_lutpair2";
  attribute SOFT_HLUTNM of \write_reg_Scal_f_carrier_AXI[24]_i_3\ : label is "soft_lutpair3";
  attribute SOFT_HLUTNM of \write_reg_TriState_HB2_AXI[1]_i_1\ : label is "soft_lutpair0";
  attribute SOFT_HLUTNM of write_reg_axi_enable_i_2 : label is "soft_lutpair4";
begin
  \FSM_onehot_axi_lite_wstate_reg[2]_0\(1 downto 0) <= \^fsm_onehot_axi_lite_wstate_reg[2]_0\(1 downto 0);
  FSM_sequential_axi_lite_rstate_reg_0 <= \^fsm_sequential_axi_lite_rstate_reg_0\;
  Q(24 downto 0) <= \^q\(24 downto 0);
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
      INIT => X"FFFFFFFFFFFFFF80"
    )
        port map (
      I0 => \AXI4_Lite_RDATA_tmp[0]_i_2_n_0\,
      I1 => decode_sel_PWM_en_rd_AXI,
      I2 => read_reg_PWM_en_rd_AXI,
      I3 => \AXI4_Lite_RDATA_tmp[16]_i_3_n_0\,
      I4 => \AXI4_Lite_RDATA_tmp[0]_i_4_n_0\,
      I5 => \AXI4_Lite_RDATA_tmp[0]_i_5_n_0\,
      O => data_read(0)
    );
\AXI4_Lite_RDATA_tmp[0]_i_2\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"7"
    )
        port map (
      I0 => \AXI4_Lite_RDATA_tmp[31]_i_4_n_0\,
      I1 => \AXI4_Lite_RDATA_tmp[30]_i_3_n_0\,
      O => \AXI4_Lite_RDATA_tmp[0]_i_2_n_0\
    );
\AXI4_Lite_RDATA_tmp[0]_i_3\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"B8000000"
    )
        port map (
      I0 => AXI4_Lite_ARADDR(0),
      I1 => AXI4_Lite_ARVALID,
      I2 => sel0(0),
      I3 => \write_reg_Scal_f_carrier_AXI[24]_i_3_n_0\,
      I4 => \AXI4_Lite_RDATA_tmp[31]_i_4_n_0\,
      O => decode_sel_PWM_en_rd_AXI
    );
\AXI4_Lite_RDATA_tmp[0]_i_4\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"00A0000000C00000"
    )
        port map (
      I0 => \AXI4_Lite_RDATA_tmp_reg[24]_1\(0),
      I1 => \AXI4_Lite_RDATA_tmp_reg[24]_0\(0),
      I2 => \AXI4_Lite_RDATA_tmp[31]_i_4_n_0\,
      I3 => \AXI4_Lite_RDATA_tmp[30]_i_4_n_0\,
      I4 => \AXI4_Lite_RDATA_tmp[30]_i_3_n_0\,
      I5 => \AXI4_Lite_RDATA_tmp[30]_i_5_n_0\,
      O => \AXI4_Lite_RDATA_tmp[0]_i_4_n_0\
    );
\AXI4_Lite_RDATA_tmp[0]_i_5\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"A000C000"
    )
        port map (
      I0 => \AXI4_Lite_RDATA_tmp_reg[1]_0\(0),
      I1 => \AXI4_Lite_RDATA_tmp_reg[30]_0\(0),
      I2 => \AXI4_Lite_RDATA_tmp[31]_i_4_n_0\,
      I3 => \AXI4_Lite_RDATA_tmp[31]_i_3_n_0\,
      I4 => \AXI4_Lite_RDATA_tmp[30]_i_5_n_0\,
      O => \AXI4_Lite_RDATA_tmp[0]_i_5_n_0\
    );
\AXI4_Lite_RDATA_tmp[10]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFFFFF8FFF8FFF8"
    )
        port map (
      I0 => \AXI4_Lite_RDATA_tmp[24]_i_4_n_0\,
      I1 => \AXI4_Lite_RDATA_tmp_reg[24]_1\(10),
      I2 => \AXI4_Lite_RDATA_tmp[10]_i_2_n_0\,
      I3 => \AXI4_Lite_RDATA_tmp[16]_i_3_n_0\,
      I4 => \AXI4_Lite_RDATA_tmp[24]_i_3_n_0\,
      I5 => \AXI4_Lite_RDATA_tmp_reg[24]_0\(10),
      O => data_read(10)
    );
\AXI4_Lite_RDATA_tmp[10]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"4700000000000000"
    )
        port map (
      I0 => AXI4_Lite_ARADDR(0),
      I1 => AXI4_Lite_ARVALID,
      I2 => sel0(0),
      I3 => \AXI4_Lite_RDATA_tmp[31]_i_3_n_0\,
      I4 => \AXI4_Lite_RDATA_tmp[31]_i_4_n_0\,
      I5 => \AXI4_Lite_RDATA_tmp_reg[30]_0\(10),
      O => \AXI4_Lite_RDATA_tmp[10]_i_2_n_0\
    );
\AXI4_Lite_RDATA_tmp[11]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFFFFF8FFF8FFF8"
    )
        port map (
      I0 => \AXI4_Lite_RDATA_tmp[24]_i_4_n_0\,
      I1 => \AXI4_Lite_RDATA_tmp_reg[24]_1\(11),
      I2 => \AXI4_Lite_RDATA_tmp[11]_i_2_n_0\,
      I3 => \AXI4_Lite_RDATA_tmp[16]_i_3_n_0\,
      I4 => \AXI4_Lite_RDATA_tmp[24]_i_3_n_0\,
      I5 => \AXI4_Lite_RDATA_tmp_reg[24]_0\(11),
      O => data_read(11)
    );
\AXI4_Lite_RDATA_tmp[11]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"4700000000000000"
    )
        port map (
      I0 => AXI4_Lite_ARADDR(0),
      I1 => AXI4_Lite_ARVALID,
      I2 => sel0(0),
      I3 => \AXI4_Lite_RDATA_tmp[31]_i_3_n_0\,
      I4 => \AXI4_Lite_RDATA_tmp[31]_i_4_n_0\,
      I5 => \AXI4_Lite_RDATA_tmp_reg[30]_0\(11),
      O => \AXI4_Lite_RDATA_tmp[11]_i_2_n_0\
    );
\AXI4_Lite_RDATA_tmp[12]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFFF888F888F888"
    )
        port map (
      I0 => \AXI4_Lite_RDATA_tmp[24]_i_3_n_0\,
      I1 => \AXI4_Lite_RDATA_tmp_reg[24]_0\(12),
      I2 => \AXI4_Lite_RDATA_tmp[24]_i_4_n_0\,
      I3 => \AXI4_Lite_RDATA_tmp_reg[24]_1\(12),
      I4 => \AXI4_Lite_RDATA_tmp_reg[30]_0\(12),
      I5 => \AXI4_Lite_RDATA_tmp[23]_i_2_n_0\,
      O => data_read(12)
    );
\AXI4_Lite_RDATA_tmp[13]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFFFFF8FFF8FFF8"
    )
        port map (
      I0 => \AXI4_Lite_RDATA_tmp[24]_i_4_n_0\,
      I1 => \AXI4_Lite_RDATA_tmp_reg[24]_1\(13),
      I2 => \AXI4_Lite_RDATA_tmp[13]_i_2_n_0\,
      I3 => \AXI4_Lite_RDATA_tmp[16]_i_3_n_0\,
      I4 => \AXI4_Lite_RDATA_tmp[24]_i_3_n_0\,
      I5 => \AXI4_Lite_RDATA_tmp_reg[24]_0\(13),
      O => data_read(13)
    );
\AXI4_Lite_RDATA_tmp[13]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"4700000000000000"
    )
        port map (
      I0 => AXI4_Lite_ARADDR(0),
      I1 => AXI4_Lite_ARVALID,
      I2 => sel0(0),
      I3 => \AXI4_Lite_RDATA_tmp[31]_i_3_n_0\,
      I4 => \AXI4_Lite_RDATA_tmp[31]_i_4_n_0\,
      I5 => \AXI4_Lite_RDATA_tmp_reg[30]_0\(13),
      O => \AXI4_Lite_RDATA_tmp[13]_i_2_n_0\
    );
\AXI4_Lite_RDATA_tmp[14]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFFF888F888F888"
    )
        port map (
      I0 => \AXI4_Lite_RDATA_tmp[24]_i_3_n_0\,
      I1 => \AXI4_Lite_RDATA_tmp_reg[24]_0\(14),
      I2 => \AXI4_Lite_RDATA_tmp[24]_i_4_n_0\,
      I3 => \AXI4_Lite_RDATA_tmp_reg[24]_1\(14),
      I4 => \AXI4_Lite_RDATA_tmp_reg[30]_0\(14),
      I5 => \AXI4_Lite_RDATA_tmp[23]_i_2_n_0\,
      O => data_read(14)
    );
\AXI4_Lite_RDATA_tmp[15]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFFF888F888F888"
    )
        port map (
      I0 => \AXI4_Lite_RDATA_tmp[24]_i_3_n_0\,
      I1 => \AXI4_Lite_RDATA_tmp_reg[24]_0\(15),
      I2 => \AXI4_Lite_RDATA_tmp[24]_i_4_n_0\,
      I3 => \AXI4_Lite_RDATA_tmp_reg[24]_1\(15),
      I4 => \AXI4_Lite_RDATA_tmp_reg[30]_0\(15),
      I5 => \AXI4_Lite_RDATA_tmp[23]_i_2_n_0\,
      O => data_read(15)
    );
\AXI4_Lite_RDATA_tmp[16]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFFFFF8FFF8FFF8"
    )
        port map (
      I0 => \AXI4_Lite_RDATA_tmp[24]_i_4_n_0\,
      I1 => \AXI4_Lite_RDATA_tmp_reg[24]_1\(16),
      I2 => \AXI4_Lite_RDATA_tmp[16]_i_2_n_0\,
      I3 => \AXI4_Lite_RDATA_tmp[16]_i_3_n_0\,
      I4 => \AXI4_Lite_RDATA_tmp[24]_i_3_n_0\,
      I5 => \AXI4_Lite_RDATA_tmp_reg[24]_0\(16),
      O => data_read(16)
    );
\AXI4_Lite_RDATA_tmp[16]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"4700000000000000"
    )
        port map (
      I0 => AXI4_Lite_ARADDR(0),
      I1 => AXI4_Lite_ARVALID,
      I2 => sel0(0),
      I3 => \AXI4_Lite_RDATA_tmp[31]_i_3_n_0\,
      I4 => \AXI4_Lite_RDATA_tmp[31]_i_4_n_0\,
      I5 => \AXI4_Lite_RDATA_tmp_reg[30]_0\(16),
      O => \AXI4_Lite_RDATA_tmp[16]_i_2_n_0\
    );
\AXI4_Lite_RDATA_tmp[16]_i_3\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0008008888888888"
    )
        port map (
      I0 => \AXI4_Lite_RDATA_tmp[30]_i_6_n_0\,
      I1 => \AXI4_Lite_RDATA_tmp[30]_i_7_n_0\,
      I2 => \AXI4_Lite_RDATA_tmp[30]_i_5_n_0\,
      I3 => \AXI4_Lite_RDATA_tmp[30]_i_3_n_0\,
      I4 => \AXI4_Lite_RDATA_tmp[30]_i_4_n_0\,
      I5 => \AXI4_Lite_RDATA_tmp[31]_i_4_n_0\,
      O => \AXI4_Lite_RDATA_tmp[16]_i_3_n_0\
    );
\AXI4_Lite_RDATA_tmp[17]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFFF888F888F888"
    )
        port map (
      I0 => \AXI4_Lite_RDATA_tmp[23]_i_2_n_0\,
      I1 => \AXI4_Lite_RDATA_tmp_reg[30]_0\(17),
      I2 => \AXI4_Lite_RDATA_tmp[24]_i_4_n_0\,
      I3 => \AXI4_Lite_RDATA_tmp_reg[24]_1\(17),
      I4 => \AXI4_Lite_RDATA_tmp_reg[24]_0\(17),
      I5 => \AXI4_Lite_RDATA_tmp[24]_i_3_n_0\,
      O => data_read(17)
    );
\AXI4_Lite_RDATA_tmp[18]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFFFEEEFEEEFEEE"
    )
        port map (
      I0 => \AXI4_Lite_RDATA_tmp[24]_i_2_n_0\,
      I1 => data_read(31),
      I2 => \AXI4_Lite_RDATA_tmp[24]_i_3_n_0\,
      I3 => \AXI4_Lite_RDATA_tmp_reg[24]_0\(18),
      I4 => \AXI4_Lite_RDATA_tmp_reg[24]_1\(18),
      I5 => \AXI4_Lite_RDATA_tmp[24]_i_4_n_0\,
      O => data_read(18)
    );
\AXI4_Lite_RDATA_tmp[19]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFFF888F888F888"
    )
        port map (
      I0 => \AXI4_Lite_RDATA_tmp[23]_i_2_n_0\,
      I1 => \AXI4_Lite_RDATA_tmp_reg[30]_0\(17),
      I2 => \AXI4_Lite_RDATA_tmp[24]_i_4_n_0\,
      I3 => \AXI4_Lite_RDATA_tmp_reg[24]_1\(19),
      I4 => \AXI4_Lite_RDATA_tmp_reg[24]_0\(19),
      I5 => \AXI4_Lite_RDATA_tmp[24]_i_3_n_0\,
      O => data_read(19)
    );
\AXI4_Lite_RDATA_tmp[1]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFFFFF8FFF8FFF8"
    )
        port map (
      I0 => \AXI4_Lite_RDATA_tmp_reg[1]_0\(1),
      I1 => decode_sel_Mode_rd_AXI,
      I2 => \AXI4_Lite_RDATA_tmp[1]_i_3_n_0\,
      I3 => \AXI4_Lite_RDATA_tmp[16]_i_3_n_0\,
      I4 => \AXI4_Lite_RDATA_tmp[24]_i_3_n_0\,
      I5 => \AXI4_Lite_RDATA_tmp_reg[24]_0\(1),
      O => data_read(1)
    );
\AXI4_Lite_RDATA_tmp[1]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"A808000000000000"
    )
        port map (
      I0 => \AXI4_Lite_RDATA_tmp[30]_i_5_n_0\,
      I1 => sel0(1),
      I2 => AXI4_Lite_ARVALID,
      I3 => AXI4_Lite_ARADDR(1),
      I4 => \AXI4_Lite_RDATA_tmp[30]_i_3_n_0\,
      I5 => \AXI4_Lite_RDATA_tmp[31]_i_4_n_0\,
      O => decode_sel_Mode_rd_AXI
    );
\AXI4_Lite_RDATA_tmp[1]_i_3\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"00C00000A0000000"
    )
        port map (
      I0 => \AXI4_Lite_RDATA_tmp_reg[30]_0\(1),
      I1 => \AXI4_Lite_RDATA_tmp_reg[24]_1\(1),
      I2 => \AXI4_Lite_RDATA_tmp[31]_i_4_n_0\,
      I3 => \AXI4_Lite_RDATA_tmp[30]_i_4_n_0\,
      I4 => \AXI4_Lite_RDATA_tmp[30]_i_3_n_0\,
      I5 => \AXI4_Lite_RDATA_tmp[30]_i_5_n_0\,
      O => \AXI4_Lite_RDATA_tmp[1]_i_3_n_0\
    );
\AXI4_Lite_RDATA_tmp[20]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFFFEEEFEEEFEEE"
    )
        port map (
      I0 => \AXI4_Lite_RDATA_tmp[24]_i_2_n_0\,
      I1 => data_read(31),
      I2 => \AXI4_Lite_RDATA_tmp[24]_i_3_n_0\,
      I3 => \AXI4_Lite_RDATA_tmp_reg[24]_0\(20),
      I4 => \AXI4_Lite_RDATA_tmp_reg[24]_1\(20),
      I5 => \AXI4_Lite_RDATA_tmp[24]_i_4_n_0\,
      O => data_read(20)
    );
\AXI4_Lite_RDATA_tmp[21]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFFF888F888F888"
    )
        port map (
      I0 => \AXI4_Lite_RDATA_tmp[23]_i_2_n_0\,
      I1 => \AXI4_Lite_RDATA_tmp_reg[30]_0\(17),
      I2 => \AXI4_Lite_RDATA_tmp[24]_i_4_n_0\,
      I3 => \AXI4_Lite_RDATA_tmp_reg[24]_1\(21),
      I4 => \AXI4_Lite_RDATA_tmp_reg[24]_0\(21),
      I5 => \AXI4_Lite_RDATA_tmp[24]_i_3_n_0\,
      O => data_read(21)
    );
\AXI4_Lite_RDATA_tmp[22]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFFFEEEFEEEFEEE"
    )
        port map (
      I0 => \AXI4_Lite_RDATA_tmp[24]_i_2_n_0\,
      I1 => data_read(31),
      I2 => \AXI4_Lite_RDATA_tmp[24]_i_3_n_0\,
      I3 => \AXI4_Lite_RDATA_tmp_reg[24]_0\(22),
      I4 => \AXI4_Lite_RDATA_tmp_reg[24]_1\(22),
      I5 => \AXI4_Lite_RDATA_tmp[24]_i_4_n_0\,
      O => data_read(22)
    );
\AXI4_Lite_RDATA_tmp[23]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFFF888F888F888"
    )
        port map (
      I0 => \AXI4_Lite_RDATA_tmp[23]_i_2_n_0\,
      I1 => \AXI4_Lite_RDATA_tmp_reg[30]_0\(17),
      I2 => \AXI4_Lite_RDATA_tmp[24]_i_4_n_0\,
      I3 => \AXI4_Lite_RDATA_tmp_reg[24]_1\(23),
      I4 => \AXI4_Lite_RDATA_tmp_reg[24]_0\(23),
      I5 => \AXI4_Lite_RDATA_tmp[24]_i_3_n_0\,
      O => data_read(23)
    );
\AXI4_Lite_RDATA_tmp[23]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0000000080888000"
    )
        port map (
      I0 => \AXI4_Lite_RDATA_tmp[31]_i_4_n_0\,
      I1 => \AXI4_Lite_RDATA_tmp[30]_i_3_n_0\,
      I2 => AXI4_Lite_ARADDR(1),
      I3 => AXI4_Lite_ARVALID,
      I4 => sel0(1),
      I5 => \AXI4_Lite_RDATA_tmp[30]_i_5_n_0\,
      O => \AXI4_Lite_RDATA_tmp[23]_i_2_n_0\
    );
\AXI4_Lite_RDATA_tmp[24]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFFFEEEFEEEFEEE"
    )
        port map (
      I0 => \AXI4_Lite_RDATA_tmp[24]_i_2_n_0\,
      I1 => data_read(31),
      I2 => \AXI4_Lite_RDATA_tmp[24]_i_3_n_0\,
      I3 => \AXI4_Lite_RDATA_tmp_reg[24]_0\(24),
      I4 => \AXI4_Lite_RDATA_tmp_reg[24]_1\(24),
      I5 => \AXI4_Lite_RDATA_tmp[24]_i_4_n_0\,
      O => data_read(24)
    );
\AXI4_Lite_RDATA_tmp[24]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0008008888888888"
    )
        port map (
      I0 => \AXI4_Lite_RDATA_tmp[30]_i_7_n_0\,
      I1 => \AXI4_Lite_RDATA_tmp[30]_i_6_n_0\,
      I2 => \AXI4_Lite_RDATA_tmp[30]_i_5_n_0\,
      I3 => \AXI4_Lite_RDATA_tmp[30]_i_3_n_0\,
      I4 => \AXI4_Lite_RDATA_tmp[30]_i_4_n_0\,
      I5 => \AXI4_Lite_RDATA_tmp[31]_i_4_n_0\,
      O => \AXI4_Lite_RDATA_tmp[24]_i_2_n_0\
    );
\AXI4_Lite_RDATA_tmp[24]_i_3\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"00000000202A0000"
    )
        port map (
      I0 => \AXI4_Lite_RDATA_tmp[31]_i_4_n_0\,
      I1 => AXI4_Lite_ARADDR(1),
      I2 => AXI4_Lite_ARVALID,
      I3 => sel0(1),
      I4 => \AXI4_Lite_RDATA_tmp[30]_i_3_n_0\,
      I5 => \AXI4_Lite_RDATA_tmp[30]_i_5_n_0\,
      O => \AXI4_Lite_RDATA_tmp[24]_i_3_n_0\
    );
\AXI4_Lite_RDATA_tmp[24]_i_4\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"202A000000000000"
    )
        port map (
      I0 => \AXI4_Lite_RDATA_tmp[31]_i_4_n_0\,
      I1 => AXI4_Lite_ARADDR(1),
      I2 => AXI4_Lite_ARVALID,
      I3 => sel0(1),
      I4 => \AXI4_Lite_RDATA_tmp[30]_i_3_n_0\,
      I5 => \AXI4_Lite_RDATA_tmp[30]_i_5_n_0\,
      O => \AXI4_Lite_RDATA_tmp[24]_i_4_n_0\
    );
\AXI4_Lite_RDATA_tmp[2]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFFF888F888F888"
    )
        port map (
      I0 => \AXI4_Lite_RDATA_tmp[24]_i_3_n_0\,
      I1 => \AXI4_Lite_RDATA_tmp_reg[24]_0\(2),
      I2 => \AXI4_Lite_RDATA_tmp[24]_i_4_n_0\,
      I3 => \AXI4_Lite_RDATA_tmp_reg[24]_1\(2),
      I4 => \AXI4_Lite_RDATA_tmp_reg[30]_0\(2),
      I5 => \AXI4_Lite_RDATA_tmp[23]_i_2_n_0\,
      O => data_read(2)
    );
\AXI4_Lite_RDATA_tmp[30]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0AAA0AAACAAA0AAA"
    )
        port map (
      I0 => \AXI4_Lite_RDATA_tmp[30]_i_2_n_0\,
      I1 => \AXI4_Lite_RDATA_tmp_reg[30]_0\(17),
      I2 => \AXI4_Lite_RDATA_tmp[31]_i_4_n_0\,
      I3 => \AXI4_Lite_RDATA_tmp[30]_i_3_n_0\,
      I4 => \AXI4_Lite_RDATA_tmp[30]_i_4_n_0\,
      I5 => \AXI4_Lite_RDATA_tmp[30]_i_5_n_0\,
      O => data_read(30)
    );
\AXI4_Lite_RDATA_tmp[30]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"2A00AA00AA00AA00"
    )
        port map (
      I0 => \AXI4_Lite_RDATA_tmp[30]_i_6_n_0\,
      I1 => \AXI4_Lite_RDATA_tmp[31]_i_5_n_0\,
      I2 => write_reg_PWM_en_AXI_i_2_n_0,
      I3 => \AXI4_Lite_RDATA_tmp[30]_i_7_n_0\,
      I4 => \write_reg_Scal_f_carrier_AXI[24]_i_3_n_0\,
      I5 => \AXI4_Lite_RDATA_tmp[30]_i_5_n_0\,
      O => \AXI4_Lite_RDATA_tmp[30]_i_2_n_0\
    );
\AXI4_Lite_RDATA_tmp[30]_i_3\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"B8"
    )
        port map (
      I0 => AXI4_Lite_ARADDR(2),
      I1 => AXI4_Lite_ARVALID,
      I2 => sel0(2),
      O => \AXI4_Lite_RDATA_tmp[30]_i_3_n_0\
    );
\AXI4_Lite_RDATA_tmp[30]_i_4\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"B8"
    )
        port map (
      I0 => AXI4_Lite_ARADDR(1),
      I1 => AXI4_Lite_ARVALID,
      I2 => sel0(1),
      O => \AXI4_Lite_RDATA_tmp[30]_i_4_n_0\
    );
\AXI4_Lite_RDATA_tmp[30]_i_5\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"B8"
    )
        port map (
      I0 => AXI4_Lite_ARADDR(0),
      I1 => AXI4_Lite_ARVALID,
      I2 => sel0(0),
      O => \AXI4_Lite_RDATA_tmp[30]_i_5_n_0\
    );
\AXI4_Lite_RDATA_tmp[30]_i_6\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0000000000000020"
    )
        port map (
      I0 => read_reg_ip_timestamp(0),
      I1 => \write_reg_Mode_AXI[1]_i_8_n_0\,
      I2 => \write_reg_Scal_f_carrier_AXI[24]_i_3_n_0\,
      I3 => \AXI4_Lite_RDATA_tmp[30]_i_5_n_0\,
      I4 => \AXI4_Lite_RDATA_tmp[31]_i_5_n_0\,
      I5 => \write_reg_Mode_AXI[1]_i_7_n_0\,
      O => \AXI4_Lite_RDATA_tmp[30]_i_6_n_0\
    );
\AXI4_Lite_RDATA_tmp[30]_i_7\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"00080000"
    )
        port map (
      I0 => \AXI4_Lite_RDATA_tmp[31]_i_9_n_0\,
      I1 => \AXI4_Lite_RDATA_tmp[31]_i_8_n_0\,
      I2 => \write_reg_PWM_min_pulse_width_AXI[17]_i_3_n_0\,
      I3 => \AXI4_Lite_RDATA_tmp[30]_i_8_n_0\,
      I4 => \AXI4_Lite_RDATA_tmp[31]_i_6_n_0\,
      O => \AXI4_Lite_RDATA_tmp[30]_i_7_n_0\
    );
\AXI4_Lite_RDATA_tmp[30]_i_8\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"B8"
    )
        port map (
      I0 => AXI4_Lite_ARADDR(10),
      I1 => AXI4_Lite_ARVALID,
      I2 => sel0(10),
      O => \AXI4_Lite_RDATA_tmp[30]_i_8_n_0\
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
\AXI4_Lite_RDATA_tmp[31]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"4700000000000000"
    )
        port map (
      I0 => AXI4_Lite_ARADDR(0),
      I1 => AXI4_Lite_ARVALID,
      I2 => sel0(0),
      I3 => \AXI4_Lite_RDATA_tmp[31]_i_3_n_0\,
      I4 => \AXI4_Lite_RDATA_tmp[31]_i_4_n_0\,
      I5 => \AXI4_Lite_RDATA_tmp_reg[30]_0\(17),
      O => data_read(31)
    );
\AXI4_Lite_RDATA_tmp[31]_i_3\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"CCA000A0"
    )
        port map (
      I0 => sel0(1),
      I1 => AXI4_Lite_ARADDR(1),
      I2 => sel0(2),
      I3 => AXI4_Lite_ARVALID,
      I4 => AXI4_Lite_ARADDR(2),
      O => \AXI4_Lite_RDATA_tmp[31]_i_3_n_0\
    );
\AXI4_Lite_RDATA_tmp[31]_i_4\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"8000000000000000"
    )
        port map (
      I0 => \AXI4_Lite_RDATA_tmp[31]_i_5_n_0\,
      I1 => write_reg_PWM_en_AXI_i_2_n_0,
      I2 => \AXI4_Lite_RDATA_tmp[31]_i_6_n_0\,
      I3 => \AXI4_Lite_RDATA_tmp[31]_i_7_n_0\,
      I4 => \AXI4_Lite_RDATA_tmp[31]_i_8_n_0\,
      I5 => \AXI4_Lite_RDATA_tmp[31]_i_9_n_0\,
      O => \AXI4_Lite_RDATA_tmp[31]_i_4_n_0\
    );
\AXI4_Lite_RDATA_tmp[31]_i_5\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"B8"
    )
        port map (
      I0 => AXI4_Lite_ARADDR(3),
      I1 => AXI4_Lite_ARVALID,
      I2 => sel0(3),
      O => \AXI4_Lite_RDATA_tmp[31]_i_5_n_0\
    );
\AXI4_Lite_RDATA_tmp[31]_i_6\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"00053305"
    )
        port map (
      I0 => sel0(5),
      I1 => AXI4_Lite_ARADDR(5),
      I2 => sel0(4),
      I3 => AXI4_Lite_ARVALID,
      I4 => AXI4_Lite_ARADDR(4),
      O => \AXI4_Lite_RDATA_tmp[31]_i_6_n_0\
    );
\AXI4_Lite_RDATA_tmp[31]_i_7\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"00053305"
    )
        port map (
      I0 => sel0(11),
      I1 => AXI4_Lite_ARADDR(11),
      I2 => sel0(10),
      I3 => AXI4_Lite_ARVALID,
      I4 => AXI4_Lite_ARADDR(10),
      O => \AXI4_Lite_RDATA_tmp[31]_i_7_n_0\
    );
\AXI4_Lite_RDATA_tmp[31]_i_8\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"00053305"
    )
        port map (
      I0 => sel0(13),
      I1 => AXI4_Lite_ARADDR(13),
      I2 => sel0(8),
      I3 => AXI4_Lite_ARVALID,
      I4 => AXI4_Lite_ARADDR(8),
      O => \AXI4_Lite_RDATA_tmp[31]_i_8_n_0\
    );
\AXI4_Lite_RDATA_tmp[31]_i_9\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"00053305"
    )
        port map (
      I0 => sel0(7),
      I1 => AXI4_Lite_ARADDR(7),
      I2 => sel0(12),
      I3 => AXI4_Lite_ARVALID,
      I4 => AXI4_Lite_ARADDR(12),
      O => \AXI4_Lite_RDATA_tmp[31]_i_9_n_0\
    );
\AXI4_Lite_RDATA_tmp[3]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFFF888F888F888"
    )
        port map (
      I0 => \AXI4_Lite_RDATA_tmp[24]_i_3_n_0\,
      I1 => \AXI4_Lite_RDATA_tmp_reg[24]_0\(3),
      I2 => \AXI4_Lite_RDATA_tmp[24]_i_4_n_0\,
      I3 => \AXI4_Lite_RDATA_tmp_reg[24]_1\(3),
      I4 => \AXI4_Lite_RDATA_tmp_reg[30]_0\(3),
      I5 => \AXI4_Lite_RDATA_tmp[23]_i_2_n_0\,
      O => data_read(3)
    );
\AXI4_Lite_RDATA_tmp[4]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFFFFF8FFF8FFF8"
    )
        port map (
      I0 => \AXI4_Lite_RDATA_tmp[24]_i_4_n_0\,
      I1 => \AXI4_Lite_RDATA_tmp_reg[24]_1\(4),
      I2 => \AXI4_Lite_RDATA_tmp[4]_i_2_n_0\,
      I3 => \AXI4_Lite_RDATA_tmp[16]_i_3_n_0\,
      I4 => \AXI4_Lite_RDATA_tmp[24]_i_3_n_0\,
      I5 => \AXI4_Lite_RDATA_tmp_reg[24]_0\(4),
      O => data_read(4)
    );
\AXI4_Lite_RDATA_tmp[4]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"4700000000000000"
    )
        port map (
      I0 => AXI4_Lite_ARADDR(0),
      I1 => AXI4_Lite_ARVALID,
      I2 => sel0(0),
      I3 => \AXI4_Lite_RDATA_tmp[31]_i_3_n_0\,
      I4 => \AXI4_Lite_RDATA_tmp[31]_i_4_n_0\,
      I5 => \AXI4_Lite_RDATA_tmp_reg[30]_0\(4),
      O => \AXI4_Lite_RDATA_tmp[4]_i_2_n_0\
    );
\AXI4_Lite_RDATA_tmp[5]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFFFFF8FFF8FFF8"
    )
        port map (
      I0 => \AXI4_Lite_RDATA_tmp[24]_i_4_n_0\,
      I1 => \AXI4_Lite_RDATA_tmp_reg[24]_1\(5),
      I2 => \AXI4_Lite_RDATA_tmp[5]_i_2_n_0\,
      I3 => \AXI4_Lite_RDATA_tmp[16]_i_3_n_0\,
      I4 => \AXI4_Lite_RDATA_tmp[24]_i_3_n_0\,
      I5 => \AXI4_Lite_RDATA_tmp_reg[24]_0\(5),
      O => data_read(5)
    );
\AXI4_Lite_RDATA_tmp[5]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"4700000000000000"
    )
        port map (
      I0 => AXI4_Lite_ARADDR(0),
      I1 => AXI4_Lite_ARVALID,
      I2 => sel0(0),
      I3 => \AXI4_Lite_RDATA_tmp[31]_i_3_n_0\,
      I4 => \AXI4_Lite_RDATA_tmp[31]_i_4_n_0\,
      I5 => \AXI4_Lite_RDATA_tmp_reg[30]_0\(5),
      O => \AXI4_Lite_RDATA_tmp[5]_i_2_n_0\
    );
\AXI4_Lite_RDATA_tmp[6]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFFFFF8FFF8FFF8"
    )
        port map (
      I0 => \AXI4_Lite_RDATA_tmp[24]_i_4_n_0\,
      I1 => \AXI4_Lite_RDATA_tmp_reg[24]_1\(6),
      I2 => \AXI4_Lite_RDATA_tmp[6]_i_2_n_0\,
      I3 => \AXI4_Lite_RDATA_tmp[16]_i_3_n_0\,
      I4 => \AXI4_Lite_RDATA_tmp[24]_i_3_n_0\,
      I5 => \AXI4_Lite_RDATA_tmp_reg[24]_0\(6),
      O => data_read(6)
    );
\AXI4_Lite_RDATA_tmp[6]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"4700000000000000"
    )
        port map (
      I0 => AXI4_Lite_ARADDR(0),
      I1 => AXI4_Lite_ARVALID,
      I2 => sel0(0),
      I3 => \AXI4_Lite_RDATA_tmp[31]_i_3_n_0\,
      I4 => \AXI4_Lite_RDATA_tmp[31]_i_4_n_0\,
      I5 => \AXI4_Lite_RDATA_tmp_reg[30]_0\(6),
      O => \AXI4_Lite_RDATA_tmp[6]_i_2_n_0\
    );
\AXI4_Lite_RDATA_tmp[7]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFFF888F888F888"
    )
        port map (
      I0 => \AXI4_Lite_RDATA_tmp[24]_i_3_n_0\,
      I1 => \AXI4_Lite_RDATA_tmp_reg[24]_0\(7),
      I2 => \AXI4_Lite_RDATA_tmp[24]_i_4_n_0\,
      I3 => \AXI4_Lite_RDATA_tmp_reg[24]_1\(7),
      I4 => \AXI4_Lite_RDATA_tmp_reg[30]_0\(7),
      I5 => \AXI4_Lite_RDATA_tmp[23]_i_2_n_0\,
      O => data_read(7)
    );
\AXI4_Lite_RDATA_tmp[8]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFFFFF8FFF8FFF8"
    )
        port map (
      I0 => \AXI4_Lite_RDATA_tmp[24]_i_4_n_0\,
      I1 => \AXI4_Lite_RDATA_tmp_reg[24]_1\(8),
      I2 => \AXI4_Lite_RDATA_tmp[8]_i_2_n_0\,
      I3 => \AXI4_Lite_RDATA_tmp[16]_i_3_n_0\,
      I4 => \AXI4_Lite_RDATA_tmp[24]_i_3_n_0\,
      I5 => \AXI4_Lite_RDATA_tmp_reg[24]_0\(8),
      O => data_read(8)
    );
\AXI4_Lite_RDATA_tmp[8]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"4700000000000000"
    )
        port map (
      I0 => AXI4_Lite_ARADDR(0),
      I1 => AXI4_Lite_ARVALID,
      I2 => sel0(0),
      I3 => \AXI4_Lite_RDATA_tmp[31]_i_3_n_0\,
      I4 => \AXI4_Lite_RDATA_tmp[31]_i_4_n_0\,
      I5 => \AXI4_Lite_RDATA_tmp_reg[30]_0\(8),
      O => \AXI4_Lite_RDATA_tmp[8]_i_2_n_0\
    );
\AXI4_Lite_RDATA_tmp[9]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFFFFF8FFF8FFF8"
    )
        port map (
      I0 => \AXI4_Lite_RDATA_tmp[24]_i_4_n_0\,
      I1 => \AXI4_Lite_RDATA_tmp_reg[24]_1\(9),
      I2 => \AXI4_Lite_RDATA_tmp[9]_i_2_n_0\,
      I3 => \AXI4_Lite_RDATA_tmp[16]_i_3_n_0\,
      I4 => \AXI4_Lite_RDATA_tmp[24]_i_3_n_0\,
      I5 => \AXI4_Lite_RDATA_tmp_reg[24]_0\(9),
      O => data_read(9)
    );
\AXI4_Lite_RDATA_tmp[9]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"4700000000000000"
    )
        port map (
      I0 => AXI4_Lite_ARADDR(0),
      I1 => AXI4_Lite_ARVALID,
      I2 => sel0(0),
      I3 => \AXI4_Lite_RDATA_tmp[31]_i_3_n_0\,
      I4 => \AXI4_Lite_RDATA_tmp[31]_i_4_n_0\,
      I5 => \AXI4_Lite_RDATA_tmp_reg[30]_0\(9),
      O => \AXI4_Lite_RDATA_tmp[9]_i_2_n_0\
    );
\AXI4_Lite_RDATA_tmp_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => top_rd_enb,
      D => data_read(0),
      Q => AXI4_Lite_RDATA(0),
      R => reset_0
    );
\AXI4_Lite_RDATA_tmp_reg[10]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => top_rd_enb,
      D => data_read(10),
      Q => AXI4_Lite_RDATA(10),
      R => reset_0
    );
\AXI4_Lite_RDATA_tmp_reg[11]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => top_rd_enb,
      D => data_read(11),
      Q => AXI4_Lite_RDATA(11),
      R => reset_0
    );
\AXI4_Lite_RDATA_tmp_reg[12]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => top_rd_enb,
      D => data_read(12),
      Q => AXI4_Lite_RDATA(12),
      R => reset_0
    );
\AXI4_Lite_RDATA_tmp_reg[13]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => top_rd_enb,
      D => data_read(13),
      Q => AXI4_Lite_RDATA(13),
      R => reset_0
    );
\AXI4_Lite_RDATA_tmp_reg[14]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => top_rd_enb,
      D => data_read(14),
      Q => AXI4_Lite_RDATA(14),
      R => reset_0
    );
\AXI4_Lite_RDATA_tmp_reg[15]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => top_rd_enb,
      D => data_read(15),
      Q => AXI4_Lite_RDATA(15),
      R => reset_0
    );
\AXI4_Lite_RDATA_tmp_reg[16]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => top_rd_enb,
      D => data_read(16),
      Q => AXI4_Lite_RDATA(16),
      R => reset_0
    );
\AXI4_Lite_RDATA_tmp_reg[17]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => top_rd_enb,
      D => data_read(17),
      Q => AXI4_Lite_RDATA(17),
      R => reset_0
    );
\AXI4_Lite_RDATA_tmp_reg[18]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => top_rd_enb,
      D => data_read(18),
      Q => AXI4_Lite_RDATA(18),
      R => reset_0
    );
\AXI4_Lite_RDATA_tmp_reg[19]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => top_rd_enb,
      D => data_read(19),
      Q => AXI4_Lite_RDATA(19),
      R => reset_0
    );
\AXI4_Lite_RDATA_tmp_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => top_rd_enb,
      D => data_read(1),
      Q => AXI4_Lite_RDATA(1),
      R => reset_0
    );
\AXI4_Lite_RDATA_tmp_reg[20]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => top_rd_enb,
      D => data_read(20),
      Q => AXI4_Lite_RDATA(20),
      R => reset_0
    );
\AXI4_Lite_RDATA_tmp_reg[21]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => top_rd_enb,
      D => data_read(21),
      Q => AXI4_Lite_RDATA(21),
      R => reset_0
    );
\AXI4_Lite_RDATA_tmp_reg[22]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => top_rd_enb,
      D => data_read(22),
      Q => AXI4_Lite_RDATA(22),
      R => reset_0
    );
\AXI4_Lite_RDATA_tmp_reg[23]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => top_rd_enb,
      D => data_read(23),
      Q => AXI4_Lite_RDATA(23),
      R => reset_0
    );
\AXI4_Lite_RDATA_tmp_reg[24]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => top_rd_enb,
      D => data_read(24),
      Q => AXI4_Lite_RDATA(24),
      R => reset_0
    );
\AXI4_Lite_RDATA_tmp_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => top_rd_enb,
      D => data_read(2),
      Q => AXI4_Lite_RDATA(2),
      R => reset_0
    );
\AXI4_Lite_RDATA_tmp_reg[30]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => top_rd_enb,
      D => data_read(30),
      Q => AXI4_Lite_RDATA(25),
      R => reset_0
    );
\AXI4_Lite_RDATA_tmp_reg[31]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => top_rd_enb,
      D => data_read(31),
      Q => AXI4_Lite_RDATA(26),
      R => reset_0
    );
\AXI4_Lite_RDATA_tmp_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => top_rd_enb,
      D => data_read(3),
      Q => AXI4_Lite_RDATA(3),
      R => reset_0
    );
\AXI4_Lite_RDATA_tmp_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => top_rd_enb,
      D => data_read(4),
      Q => AXI4_Lite_RDATA(4),
      R => reset_0
    );
\AXI4_Lite_RDATA_tmp_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => top_rd_enb,
      D => data_read(5),
      Q => AXI4_Lite_RDATA(5),
      R => reset_0
    );
\AXI4_Lite_RDATA_tmp_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => top_rd_enb,
      D => data_read(6),
      Q => AXI4_Lite_RDATA(6),
      R => reset_0
    );
\AXI4_Lite_RDATA_tmp_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => top_rd_enb,
      D => data_read(7),
      Q => AXI4_Lite_RDATA(7),
      R => reset_0
    );
\AXI4_Lite_RDATA_tmp_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => top_rd_enb,
      D => data_read(8),
      Q => AXI4_Lite_RDATA(8),
      R => reset_0
    );
\AXI4_Lite_RDATA_tmp_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => top_rd_enb,
      D => data_read(9),
      Q => AXI4_Lite_RDATA(9),
      R => reset_0
    );
\FSM_onehot_axi_lite_wstate[0]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FF8A8A8A"
    )
        port map (
      I0 => \FSM_onehot_axi_lite_wstate_reg_n_0_[0]\,
      I1 => \^fsm_sequential_axi_lite_rstate_reg_0\,
      I2 => AXI4_Lite_AWVALID,
      I3 => AXI4_Lite_BREADY,
      I4 => \^fsm_onehot_axi_lite_wstate_reg[2]_0\(1),
      O => axi_lite_wstate_next(0)
    );
\FSM_onehot_axi_lite_wstate[1]_i_1\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => AXI4_Lite_ARESETN,
      O => reset_0
    );
\FSM_onehot_axi_lite_wstate[1]_i_2\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"08FF0808"
    )
        port map (
      I0 => AXI4_Lite_AWVALID,
      I1 => \FSM_onehot_axi_lite_wstate_reg_n_0_[0]\,
      I2 => \^fsm_sequential_axi_lite_rstate_reg_0\,
      I3 => AXI4_Lite_WVALID,
      I4 => \^fsm_onehot_axi_lite_wstate_reg[2]_0\(0),
      O => axi_lite_wstate_next(1)
    );
\FSM_onehot_axi_lite_wstate[2]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"F444"
    )
        port map (
      I0 => AXI4_Lite_BREADY,
      I1 => \^fsm_onehot_axi_lite_wstate_reg[2]_0\(1),
      I2 => AXI4_Lite_WVALID,
      I3 => \^fsm_onehot_axi_lite_wstate_reg[2]_0\(0),
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
      S => reset_0
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
      R => reset_0
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
      R => reset_0
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
      R => reset_0
    );
Switch6_out1_1_i_1: unisim.vcomponents.LUT3
    generic map(
      INIT => X"DF"
    )
        port map (
      I0 => AXI4_Lite_ARESETN,
      I1 => soft_reset,
      I2 => IPCORE_RESETN,
      O => reset
    );
soft_reset_i_1: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0100000000000000"
    )
        port map (
      I0 => sel0(2),
      I1 => sel0(1),
      I2 => sel0(0),
      I3 => soft_reset_i_2_n_0,
      I4 => soft_reset_i_3_n_0,
      I5 => soft_reset_i_4_n_0,
      O => soft_reset_i_1_n_0
    );
soft_reset_i_2: unisim.vcomponents.LUT4
    generic map(
      INIT => X"0001"
    )
        port map (
      I0 => sel0(6),
      I1 => sel0(5),
      I2 => sel0(4),
      I3 => sel0(3),
      O => soft_reset_i_2_n_0
    );
soft_reset_i_3: unisim.vcomponents.LUT4
    generic map(
      INIT => X"0001"
    )
        port map (
      I0 => sel0(10),
      I1 => sel0(9),
      I2 => sel0(8),
      I3 => sel0(7),
      O => soft_reset_i_3_n_0
    );
soft_reset_i_4: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0010000000000000"
    )
        port map (
      I0 => sel0(11),
      I1 => sel0(12),
      I2 => \^q\(0),
      I3 => sel0(13),
      I4 => top_wr_enb,
      I5 => AXI4_Lite_ARESETN,
      O => soft_reset_i_4_n_0
    );
soft_reset_reg: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => soft_reset_i_1_n_0,
      Q => soft_reset,
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
      R => reset_0
    );
\waddr_reg[11]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => aw_transfer,
      D => AXI4_Lite_AWADDR(9),
      Q => sel0(9),
      R => reset_0
    );
\waddr_reg[12]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => aw_transfer,
      D => AXI4_Lite_AWADDR(10),
      Q => sel0(10),
      R => reset_0
    );
\waddr_reg[13]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => aw_transfer,
      D => AXI4_Lite_AWADDR(11),
      Q => sel0(11),
      R => reset_0
    );
\waddr_reg[14]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => aw_transfer,
      D => AXI4_Lite_AWADDR(12),
      Q => sel0(12),
      R => reset_0
    );
\waddr_reg[15]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => aw_transfer,
      D => AXI4_Lite_AWADDR(13),
      Q => sel0(13),
      R => reset_0
    );
\waddr_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => aw_transfer,
      D => AXI4_Lite_AWADDR(0),
      Q => sel0(0),
      R => reset_0
    );
\waddr_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => aw_transfer,
      D => AXI4_Lite_AWADDR(1),
      Q => sel0(1),
      R => reset_0
    );
\waddr_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => aw_transfer,
      D => AXI4_Lite_AWADDR(2),
      Q => sel0(2),
      R => reset_0
    );
\waddr_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => aw_transfer,
      D => AXI4_Lite_AWADDR(3),
      Q => sel0(3),
      R => reset_0
    );
\waddr_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => aw_transfer,
      D => AXI4_Lite_AWADDR(4),
      Q => sel0(4),
      R => reset_0
    );
\waddr_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => aw_transfer,
      D => AXI4_Lite_AWADDR(5),
      Q => sel0(5),
      R => reset_0
    );
\waddr_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => aw_transfer,
      D => AXI4_Lite_AWADDR(6),
      Q => sel0(6),
      R => reset_0
    );
\waddr_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => aw_transfer,
      D => AXI4_Lite_AWADDR(7),
      Q => sel0(7),
      R => reset_0
    );
\wdata[24]_i_1\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"8"
    )
        port map (
      I0 => \^fsm_onehot_axi_lite_wstate_reg[2]_0\(0),
      I1 => AXI4_Lite_WVALID,
      O => w_transfer
    );
\wdata_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => w_transfer,
      D => AXI4_Lite_WDATA(0),
      Q => \^q\(0),
      R => reset_0
    );
\wdata_reg[10]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => w_transfer,
      D => AXI4_Lite_WDATA(10),
      Q => \^q\(10),
      R => reset_0
    );
\wdata_reg[11]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => w_transfer,
      D => AXI4_Lite_WDATA(11),
      Q => \^q\(11),
      R => reset_0
    );
\wdata_reg[12]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => w_transfer,
      D => AXI4_Lite_WDATA(12),
      Q => \^q\(12),
      R => reset_0
    );
\wdata_reg[13]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => w_transfer,
      D => AXI4_Lite_WDATA(13),
      Q => \^q\(13),
      R => reset_0
    );
\wdata_reg[14]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => w_transfer,
      D => AXI4_Lite_WDATA(14),
      Q => \^q\(14),
      R => reset_0
    );
\wdata_reg[15]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => w_transfer,
      D => AXI4_Lite_WDATA(15),
      Q => \^q\(15),
      R => reset_0
    );
\wdata_reg[16]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => w_transfer,
      D => AXI4_Lite_WDATA(16),
      Q => \^q\(16),
      R => reset_0
    );
\wdata_reg[17]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => w_transfer,
      D => AXI4_Lite_WDATA(17),
      Q => \^q\(17),
      R => reset_0
    );
\wdata_reg[18]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => w_transfer,
      D => AXI4_Lite_WDATA(18),
      Q => \^q\(18),
      R => reset_0
    );
\wdata_reg[19]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => w_transfer,
      D => AXI4_Lite_WDATA(19),
      Q => \^q\(19),
      R => reset_0
    );
\wdata_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => w_transfer,
      D => AXI4_Lite_WDATA(1),
      Q => \^q\(1),
      R => reset_0
    );
\wdata_reg[20]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => w_transfer,
      D => AXI4_Lite_WDATA(20),
      Q => \^q\(20),
      R => reset_0
    );
\wdata_reg[21]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => w_transfer,
      D => AXI4_Lite_WDATA(21),
      Q => \^q\(21),
      R => reset_0
    );
\wdata_reg[22]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => w_transfer,
      D => AXI4_Lite_WDATA(22),
      Q => \^q\(22),
      R => reset_0
    );
\wdata_reg[23]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => w_transfer,
      D => AXI4_Lite_WDATA(23),
      Q => \^q\(23),
      R => reset_0
    );
\wdata_reg[24]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => w_transfer,
      D => AXI4_Lite_WDATA(24),
      Q => \^q\(24),
      R => reset_0
    );
\wdata_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => w_transfer,
      D => AXI4_Lite_WDATA(2),
      Q => \^q\(2),
      R => reset_0
    );
\wdata_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => w_transfer,
      D => AXI4_Lite_WDATA(3),
      Q => \^q\(3),
      R => reset_0
    );
\wdata_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => w_transfer,
      D => AXI4_Lite_WDATA(4),
      Q => \^q\(4),
      R => reset_0
    );
\wdata_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => w_transfer,
      D => AXI4_Lite_WDATA(5),
      Q => \^q\(5),
      R => reset_0
    );
\wdata_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => w_transfer,
      D => AXI4_Lite_WDATA(6),
      Q => \^q\(6),
      R => reset_0
    );
\wdata_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => w_transfer,
      D => AXI4_Lite_WDATA(7),
      Q => \^q\(7),
      R => reset_0
    );
\wdata_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => w_transfer,
      D => AXI4_Lite_WDATA(8),
      Q => \^q\(8),
      R => reset_0
    );
\wdata_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => w_transfer,
      D => AXI4_Lite_WDATA(9),
      Q => \^q\(9),
      R => reset_0
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
      R => reset_0
    );
\write_reg_Mode_AXI[1]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"20000000"
    )
        port map (
      I0 => \write_reg_Mode_AXI[1]_i_2_n_0\,
      I1 => \write_reg_Mode_AXI[1]_i_3_n_0\,
      I2 => \write_reg_Mode_AXI[1]_i_4_n_0\,
      I3 => \write_reg_Mode_AXI[1]_i_5_n_0\,
      I4 => \write_reg_Mode_AXI[1]_i_6_n_0\,
      O => E(0)
    );
\write_reg_Mode_AXI[1]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"00002020000A202A"
    )
        port map (
      I0 => \AXI4_Lite_RDATA_tmp[30]_i_5_n_0\,
      I1 => AXI4_Lite_ARADDR(2),
      I2 => AXI4_Lite_ARVALID,
      I3 => sel0(2),
      I4 => AXI4_Lite_ARADDR(1),
      I5 => sel0(1),
      O => \write_reg_Mode_AXI[1]_i_2_n_0\
    );
\write_reg_Mode_AXI[1]_i_3\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFFFF305050FF30"
    )
        port map (
      I0 => AXI4_Lite_ARADDR(4),
      I1 => sel0(4),
      I2 => \AXI4_Lite_RDATA_tmp[31]_i_5_n_0\,
      I3 => sel0(5),
      I4 => AXI4_Lite_ARVALID,
      I5 => AXI4_Lite_ARADDR(5),
      O => \write_reg_Mode_AXI[1]_i_3_n_0\
    );
\write_reg_Mode_AXI[1]_i_4\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFFFF305050FF30"
    )
        port map (
      I0 => AXI4_Lite_ARADDR(7),
      I1 => sel0(7),
      I2 => \write_reg_Mode_AXI[1]_i_7_n_0\,
      I3 => sel0(8),
      I4 => AXI4_Lite_ARVALID,
      I5 => AXI4_Lite_ARADDR(8),
      O => \write_reg_Mode_AXI[1]_i_4_n_0\
    );
\write_reg_Mode_AXI[1]_i_5\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"303F101F30351015"
    )
        port map (
      I0 => \write_reg_Mode_AXI[1]_i_8_n_0\,
      I1 => AXI4_Lite_ARADDR(11),
      I2 => AXI4_Lite_ARVALID,
      I3 => sel0(11),
      I4 => AXI4_Lite_ARADDR(10),
      I5 => sel0(10),
      O => \write_reg_Mode_AXI[1]_i_5_n_0\
    );
\write_reg_Mode_AXI[1]_i_6\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"8"
    )
        port map (
      I0 => \AXI4_Lite_RDATA_tmp[30]_i_7_n_0\,
      I1 => top_wr_enb,
      O => \write_reg_Mode_AXI[1]_i_6_n_0\
    );
\write_reg_Mode_AXI[1]_i_7\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"B8"
    )
        port map (
      I0 => AXI4_Lite_ARADDR(6),
      I1 => AXI4_Lite_ARVALID,
      I2 => sel0(6),
      O => \write_reg_Mode_AXI[1]_i_7_n_0\
    );
\write_reg_Mode_AXI[1]_i_8\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"B8"
    )
        port map (
      I0 => AXI4_Lite_ARADDR(9),
      I1 => AXI4_Lite_ARVALID,
      I2 => sel0(9),
      O => \write_reg_Mode_AXI[1]_i_8_n_0\
    );
write_reg_PWM_en_AXI_i_1: unisim.vcomponents.LUT5
    generic map(
      INIT => X"BFFF8000"
    )
        port map (
      I0 => \^q\(0),
      I1 => write_reg_PWM_en_AXI_i_2_n_0,
      I2 => write_reg_PWM_en_AXI_i_3_n_0,
      I3 => \write_reg_Mode_AXI[1]_i_6_n_0\,
      I4 => write_PWM_en_AXI,
      O => \wdata_reg[0]_1\
    );
write_reg_PWM_en_AXI_i_2: unisim.vcomponents.LUT5
    generic map(
      INIT => X"000ACC0A"
    )
        port map (
      I0 => sel0(6),
      I1 => AXI4_Lite_ARADDR(6),
      I2 => sel0(9),
      I3 => AXI4_Lite_ARVALID,
      I4 => AXI4_Lite_ARADDR(9),
      O => write_reg_PWM_en_AXI_i_2_n_0
    );
write_reg_PWM_en_AXI_i_3: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0044034700000000"
    )
        port map (
      I0 => AXI4_Lite_ARADDR(3),
      I1 => AXI4_Lite_ARVALID,
      I2 => sel0(3),
      I3 => AXI4_Lite_ARADDR(0),
      I4 => sel0(0),
      I5 => write_reg_axi_enable_i_2_n_0,
      O => write_reg_PWM_en_AXI_i_3_n_0
    );
\write_reg_PWM_min_pulse_width_AXI[17]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0010000000000000"
    )
        port map (
      I0 => \AXI4_Lite_RDATA_tmp[30]_i_4_n_0\,
      I1 => \AXI4_Lite_RDATA_tmp[30]_i_5_n_0\,
      I2 => \AXI4_Lite_RDATA_tmp[30]_i_3_n_0\,
      I3 => \write_reg_Mode_AXI[1]_i_3_n_0\,
      I4 => \write_reg_PWM_min_pulse_width_AXI[17]_i_2_n_0\,
      I5 => \write_reg_Mode_AXI[1]_i_6_n_0\,
      O => \AXI4_Lite_ARADDR[3]_2\(0)
    );
\write_reg_PWM_min_pulse_width_AXI[17]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"00E200FF00000000"
    )
        port map (
      I0 => sel0(10),
      I1 => AXI4_Lite_ARVALID,
      I2 => AXI4_Lite_ARADDR(10),
      I3 => \write_reg_PWM_min_pulse_width_AXI[17]_i_3_n_0\,
      I4 => \write_reg_Mode_AXI[1]_i_8_n_0\,
      I5 => \write_reg_Mode_AXI[1]_i_4_n_0\,
      O => \write_reg_PWM_min_pulse_width_AXI[17]_i_2_n_0\
    );
\write_reg_PWM_min_pulse_width_AXI[17]_i_3\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"B8"
    )
        port map (
      I0 => AXI4_Lite_ARADDR(11),
      I1 => AXI4_Lite_ARVALID,
      I2 => sel0(11),
      O => \write_reg_PWM_min_pulse_width_AXI[17]_i_3_n_0\
    );
\write_reg_Scal_T_carrier_AXI[24]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0800000000000000"
    )
        port map (
      I0 => \write_reg_Scal_f_carrier_AXI[24]_i_3_n_0\,
      I1 => \write_reg_Scal_f_carrier_AXI[24]_i_2_n_0\,
      I2 => \write_reg_Mode_AXI[1]_i_3_n_0\,
      I3 => \write_reg_Mode_AXI[1]_i_4_n_0\,
      I4 => \write_reg_Mode_AXI[1]_i_5_n_0\,
      I5 => \write_reg_Mode_AXI[1]_i_6_n_0\,
      O => \waddr_reg[3]_0\(0)
    );
\write_reg_Scal_f_carrier_AXI[24]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0400000000000000"
    )
        port map (
      I0 => \write_reg_Scal_f_carrier_AXI[24]_i_2_n_0\,
      I1 => \write_reg_Scal_f_carrier_AXI[24]_i_3_n_0\,
      I2 => \write_reg_Mode_AXI[1]_i_3_n_0\,
      I3 => \write_reg_Mode_AXI[1]_i_4_n_0\,
      I4 => \write_reg_Mode_AXI[1]_i_5_n_0\,
      I5 => \write_reg_Mode_AXI[1]_i_6_n_0\,
      O => \AXI4_Lite_ARADDR[3]_3\(0)
    );
\write_reg_Scal_f_carrier_AXI[24]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFFFFC0A0A0FFC0"
    )
        port map (
      I0 => AXI4_Lite_ARADDR(1),
      I1 => sel0(1),
      I2 => \AXI4_Lite_RDATA_tmp[30]_i_5_n_0\,
      I3 => sel0(2),
      I4 => AXI4_Lite_ARVALID,
      I5 => AXI4_Lite_ARADDR(2),
      O => \write_reg_Scal_f_carrier_AXI[24]_i_2_n_0\
    );
\write_reg_Scal_f_carrier_AXI[24]_i_3\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"000ACC0A"
    )
        port map (
      I0 => sel0(1),
      I1 => AXI4_Lite_ARADDR(1),
      I2 => sel0(2),
      I3 => AXI4_Lite_ARVALID,
      I4 => AXI4_Lite_ARADDR(2),
      O => \write_reg_Scal_f_carrier_AXI[24]_i_3_n_0\
    );
\write_reg_TriState_HB1_AXI[1]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0002000000000000"
    )
        port map (
      I0 => \write_reg_Mode_AXI[1]_i_3_n_0\,
      I1 => \AXI4_Lite_RDATA_tmp[30]_i_3_n_0\,
      I2 => \AXI4_Lite_RDATA_tmp[30]_i_5_n_0\,
      I3 => \AXI4_Lite_RDATA_tmp[30]_i_4_n_0\,
      I4 => \write_reg_Mode_AXI[1]_i_6_n_0\,
      I5 => \write_reg_PWM_min_pulse_width_AXI[17]_i_2_n_0\,
      O => \AXI4_Lite_ARADDR[6]_0\(0)
    );
\write_reg_TriState_HB2_AXI[1]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"80000000"
    )
        port map (
      I0 => \write_reg_Mode_AXI[1]_i_3_n_0\,
      I1 => \write_reg_Mode_AXI[1]_i_2_n_0\,
      I2 => \write_reg_Mode_AXI[1]_i_6_n_0\,
      I3 => \write_reg_Mode_AXI[1]_i_5_n_0\,
      I4 => \write_reg_Mode_AXI[1]_i_4_n_0\,
      O => \AXI4_Lite_ARADDR[6]\(0)
    );
\write_reg_TriState_HB3_AXI[1]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"4000000000000000"
    )
        port map (
      I0 => \write_reg_Scal_f_carrier_AXI[24]_i_2_n_0\,
      I1 => \write_reg_Mode_AXI[1]_i_3_n_0\,
      I2 => \write_reg_Scal_f_carrier_AXI[24]_i_3_n_0\,
      I3 => \write_reg_Mode_AXI[1]_i_6_n_0\,
      I4 => \write_reg_Mode_AXI[1]_i_5_n_0\,
      I5 => \write_reg_Mode_AXI[1]_i_4_n_0\,
      O => \AXI4_Lite_ARADDR[3]\(0)
    );
write_reg_axi_enable_i_1: unisim.vcomponents.LUT5
    generic map(
      INIT => X"BFFF8000"
    )
        port map (
      I0 => \^q\(0),
      I1 => write_reg_axi_enable_i_2_n_0,
      I2 => write_reg_axi_enable_i_3_n_0,
      I3 => \write_reg_Mode_AXI[1]_i_6_n_0\,
      I4 => CEA1,
      O => \wdata_reg[0]_0\
    );
write_reg_axi_enable_i_2: unisim.vcomponents.LUT5
    generic map(
      INIT => X"00053305"
    )
        port map (
      I0 => sel0(1),
      I1 => AXI4_Lite_ARADDR(1),
      I2 => sel0(2),
      I3 => AXI4_Lite_ARVALID,
      I4 => AXI4_Lite_ARADDR(2),
      O => write_reg_axi_enable_i_2_n_0
    );
write_reg_axi_enable_i_3: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0004000000040404"
    )
        port map (
      I0 => \AXI4_Lite_RDATA_tmp[31]_i_5_n_0\,
      I1 => \AXI4_Lite_RDATA_tmp[30]_i_5_n_0\,
      I2 => \write_reg_Mode_AXI[1]_i_8_n_0\,
      I3 => AXI4_Lite_ARADDR(6),
      I4 => AXI4_Lite_ARVALID,
      I5 => sel0(6),
      O => write_reg_axi_enable_i_3_n_0
    );
\write_reg_m_u1_norm_AXI[13]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0020000000000000"
    )
        port map (
      I0 => \AXI4_Lite_RDATA_tmp[30]_i_3_n_0\,
      I1 => \AXI4_Lite_RDATA_tmp[30]_i_4_n_0\,
      I2 => \AXI4_Lite_RDATA_tmp[30]_i_5_n_0\,
      I3 => \write_reg_Mode_AXI[1]_i_3_n_0\,
      I4 => \write_reg_PWM_min_pulse_width_AXI[17]_i_2_n_0\,
      I5 => \write_reg_Mode_AXI[1]_i_6_n_0\,
      O => \AXI4_Lite_ARADDR[4]\(0)
    );
\write_reg_m_u2_norm_AXI[13]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0020000000000000"
    )
        port map (
      I0 => \AXI4_Lite_RDATA_tmp[30]_i_4_n_0\,
      I1 => \AXI4_Lite_RDATA_tmp[30]_i_5_n_0\,
      I2 => \AXI4_Lite_RDATA_tmp[30]_i_3_n_0\,
      I3 => \write_reg_Mode_AXI[1]_i_3_n_0\,
      I4 => \write_reg_PWM_min_pulse_width_AXI[17]_i_2_n_0\,
      I5 => \write_reg_Mode_AXI[1]_i_6_n_0\,
      O => \AXI4_Lite_ARADDR[3]_1\(0)
    );
\write_reg_m_u3_norm_AXI[13]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0080000000000000"
    )
        port map (
      I0 => \AXI4_Lite_RDATA_tmp[30]_i_4_n_0\,
      I1 => \AXI4_Lite_RDATA_tmp[30]_i_3_n_0\,
      I2 => \AXI4_Lite_RDATA_tmp[30]_i_5_n_0\,
      I3 => \write_reg_Mode_AXI[1]_i_3_n_0\,
      I4 => \write_reg_PWM_min_pulse_width_AXI[17]_i_2_n_0\,
      I5 => \write_reg_Mode_AXI[1]_i_6_n_0\,
      O => \AXI4_Lite_ARADDR[3]_0\(0)
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity zusys_PWM_and_SS_control_V_0_2_PWM_and_SS_control_V3_ip_src_Counter_Ctrl is
  port (
    P : out STD_LOGIC_VECTOR ( 5 downto 0 );
    \Product_mul_temp[-1111111111]_0\ : out STD_LOGIC;
    \Product_mul_temp[-1111111110]_0\ : out STD_LOGIC;
    \Product_mul_temp[-1111111109]_0\ : out STD_LOGIC;
    \Product_mul_temp[-1111111108]_0\ : out STD_LOGIC;
    \Product_mul_temp[-1111111107]_0\ : out STD_LOGIC;
    \Product_mul_temp[-1111111106]_0\ : out STD_LOGIC;
    \Product_mul_temp[-1111111105]_0\ : out STD_LOGIC;
    \Product_mul_temp[-1111111104]_0\ : out STD_LOGIC;
    \Product_mul_temp[-1111111103]_0\ : out STD_LOGIC;
    \Product_mul_temp[-1111111102]_0\ : out STD_LOGIC_VECTOR ( 0 to 0 );
    CO : out STD_LOGIC_VECTOR ( 0 to 0 );
    O : out STD_LOGIC_VECTOR ( 7 downto 0 );
    DI : out STD_LOGIC_VECTOR ( 0 to 0 );
    \HDL_Counter2_count_reg[0]\ : out STD_LOGIC_VECTOR ( 7 downto 0 );
    \HDL_Counter2_count_reg[0]_0\ : out STD_LOGIC_VECTOR ( 3 downto 0 );
    \HDL_Counter2_count_reg[15]\ : out STD_LOGIC_VECTOR ( 7 downto 0 );
    \HDL_Counter2_count_reg[0]_1\ : out STD_LOGIC_VECTOR ( 0 to 0 );
    \HDL_Counter2_count_reg[0]_2\ : out STD_LOGIC_VECTOR ( 1 downto 0 );
    \Delay2_out1_reg[12]\ : out STD_LOGIC_VECTOR ( 6 downto 0 );
    \U3_norm_1_reg[13]\ : out STD_LOGIC;
    \Allow_assymetrical_anew_reference_value__0\ : out STD_LOGIC;
    \Delay2_out1_reg[12]_0\ : out STD_LOGIC_VECTOR ( 6 downto 0 );
    \U3_norm_1_reg[13]_0\ : out STD_LOGIC_VECTOR ( 1 downto 0 );
    \U3_norm_1_reg[12]\ : out STD_LOGIC_VECTOR ( 0 to 0 );
    \U3_norm_1_reg[12]_0\ : out STD_LOGIC_VECTOR ( 12 downto 0 );
    \Delay2_out1_reg[12]_1\ : out STD_LOGIC_VECTOR ( 6 downto 0 );
    \U3_norm_1_reg[10]\ : out STD_LOGIC_VECTOR ( 7 downto 0 );
    \U3_norm_1_reg[9]\ : out STD_LOGIC_VECTOR ( 7 downto 0 );
    \Delay1_out1_reg[12]\ : out STD_LOGIC_VECTOR ( 6 downto 0 );
    \U2_norm_1_reg[13]\ : out STD_LOGIC;
    \Delay1_out1_reg[12]_0\ : out STD_LOGIC_VECTOR ( 6 downto 0 );
    \U2_norm_1_reg[13]_0\ : out STD_LOGIC_VECTOR ( 1 downto 0 );
    \U2_norm_1_reg[12]\ : out STD_LOGIC_VECTOR ( 0 to 0 );
    \U2_norm_1_reg[12]_0\ : out STD_LOGIC_VECTOR ( 12 downto 0 );
    \Delay1_out1_reg[12]_1\ : out STD_LOGIC_VECTOR ( 6 downto 0 );
    \U2_norm_1_reg[10]\ : out STD_LOGIC_VECTOR ( 7 downto 0 );
    \U2_norm_1_reg[9]\ : out STD_LOGIC_VECTOR ( 7 downto 0 );
    \Delay_out1_reg[12]\ : out STD_LOGIC_VECTOR ( 6 downto 0 );
    Relational_Operator_1_cast : out STD_LOGIC_VECTOR ( 13 downto 0 );
    \Delay_out1_reg[12]_0\ : out STD_LOGIC_VECTOR ( 6 downto 0 );
    \U1_norm_1_reg[12]\ : out STD_LOGIC_VECTOR ( 0 to 0 );
    \U1_norm_1_reg[11]\ : out STD_LOGIC_VECTOR ( 0 to 0 );
    \U1_norm_1_reg[10]\ : out STD_LOGIC_VECTOR ( 5 downto 0 );
    \U1_norm_1_reg[9]\ : out STD_LOGIC_VECTOR ( 5 downto 0 );
    Switch6_out1 : out STD_LOGIC;
    \Delay2_out1_reg[12]_2\ : out STD_LOGIC_VECTOR ( 0 to 0 );
    \Delay1_out1_reg[12]_2\ : out STD_LOGIC_VECTOR ( 0 to 0 );
    \Delay_out1_reg[12]_1\ : out STD_LOGIC_VECTOR ( 0 to 0 );
    \Delay_out1_reg[12]_2\ : out STD_LOGIC_VECTOR ( 0 to 0 );
    reset : in STD_LOGIC;
    E : in STD_LOGIC_VECTOR ( 0 to 0 );
    IPCORE_CLK : in STD_LOGIC;
    CEB2 : in STD_LOGIC;
    B : in STD_LOGIC_VECTOR ( 15 downto 0 );
    D : in STD_LOGIC_VECTOR ( 24 downto 0 );
    Q : in STD_LOGIC_VECTOR ( 9 downto 0 );
    S : in STD_LOGIC_VECTOR ( 0 to 0 );
    HDL_Counter2_count_reg_7_sp_1 : in STD_LOGIC;
    HDL_Counter2_count_reg : in STD_LOGIC_VECTOR ( 12 downto 0 );
    Delay6_out1_reg_0 : in STD_LOGIC;
    \HDL_Counter2_count_reg[7]_0\ : in STD_LOGIC;
    \HDL_Counter2_count_reg[7]_1\ : in STD_LOGIC;
    \HDL_Counter2_count_reg[7]_2\ : in STD_LOGIC;
    \HDL_Counter2_count_reg[7]_3\ : in STD_LOGIC;
    Delay6_out1_reg_1 : in STD_LOGIC;
    Add_out1 : in STD_LOGIC_VECTOR ( 13 downto 0 );
    \Delay2_out1_reg[13]\ : in STD_LOGIC_VECTOR ( 13 downto 0 );
    \Delay2_out1_reg[13]_0\ : in STD_LOGIC_VECTOR ( 13 downto 0 );
    Switch9_out12_carry : in STD_LOGIC_VECTOR ( 0 to 0 );
    Switch9_out12_carry_0 : in STD_LOGIC_VECTOR ( 0 to 0 );
    \Delay2_out1_reg[13]_1\ : in STD_LOGIC;
    Saturation_out1 : in STD_LOGIC_VECTOR ( 12 downto 0 );
    \Delay1_out1_reg[13]\ : in STD_LOGIC_VECTOR ( 13 downto 0 );
    \Delay1_out1_reg[13]_0\ : in STD_LOGIC_VECTOR ( 13 downto 0 );
    Switch8_out12_carry : in STD_LOGIC_VECTOR ( 0 to 0 );
    Switch8_out12_carry_0 : in STD_LOGIC_VECTOR ( 0 to 0 );
    \Delay_out1_reg[13]\ : in STD_LOGIC_VECTOR ( 13 downto 0 );
    \Delay_out1_reg[13]_0\ : in STD_LOGIC_VECTOR ( 13 downto 0 );
    Switch7_out12_carry : in STD_LOGIC_VECTOR ( 0 to 0 );
    Switch7_out12_carry_0 : in STD_LOGIC_VECTOR ( 0 to 0 );
    Switch7_out12_carry_i_6 : in STD_LOGIC;
    Switch7_out12_carry_i_6_0 : in STD_LOGIC;
    Switch7_out12_carry_i_6_1 : in STD_LOGIC;
    \Logical_Operator_out10_carry__0_0\ : in STD_LOGIC_VECTOR ( 24 downto 0 )
  );
end zusys_PWM_and_SS_control_V_0_2_PWM_and_SS_control_V3_ip_src_Counter_Ctrl;

architecture STRUCTURE of zusys_PWM_and_SS_control_V_0_2_PWM_and_SS_control_V3_ip_src_Counter_Ctrl is
  signal \^allow_assymetrical_anew_reference_value__0\ : STD_LOGIC;
  signal \^co\ : STD_LOGIC_VECTOR ( 0 to 0 );
  signal \^di\ : STD_LOGIC_VECTOR ( 0 to 0 );
  signal Delay6_out1 : STD_LOGIC;
  signal Delay6_out1_i_2_n_0 : STD_LOGIC;
  signal Delay6_out1_i_3_n_0 : STD_LOGIC;
  signal Delay6_out1_i_4_n_0 : STD_LOGIC;
  signal Delay6_out1_i_5_n_0 : STD_LOGIC;
  signal Delay6_out1_i_6_n_0 : STD_LOGIC;
  signal \HDL_Counter2_count[0]_i_2_n_0\ : STD_LOGIC;
  signal \HDL_Counter2_count[0]_i_3_n_0\ : STD_LOGIC;
  signal \HDL_Counter2_count[0]_i_4_n_0\ : STD_LOGIC;
  signal \HDL_Counter2_count[0]_i_5_n_0\ : STD_LOGIC;
  signal \HDL_Counter2_count[0]_i_6_n_0\ : STD_LOGIC;
  signal \HDL_Counter2_count[0]_i_7_n_0\ : STD_LOGIC;
  signal \HDL_Counter2_count[0]_i_8_n_0\ : STD_LOGIC;
  signal \HDL_Counter2_count[0]_i_9_n_0\ : STD_LOGIC;
  signal \HDL_Counter2_count[16]_i_2_n_0\ : STD_LOGIC;
  signal \HDL_Counter2_count[16]_i_3_n_0\ : STD_LOGIC;
  signal \HDL_Counter2_count[16]_i_4_n_0\ : STD_LOGIC;
  signal \HDL_Counter2_count[16]_i_5_n_0\ : STD_LOGIC;
  signal \HDL_Counter2_count[8]_i_2_n_0\ : STD_LOGIC;
  signal \HDL_Counter2_count[8]_i_3_n_0\ : STD_LOGIC;
  signal \HDL_Counter2_count[8]_i_4_n_0\ : STD_LOGIC;
  signal \HDL_Counter2_count[8]_i_5_n_0\ : STD_LOGIC;
  signal \HDL_Counter2_count[8]_i_6_n_0\ : STD_LOGIC;
  signal \HDL_Counter2_count[8]_i_7_n_0\ : STD_LOGIC;
  signal \HDL_Counter2_count[8]_i_8_n_0\ : STD_LOGIC;
  signal \HDL_Counter2_count[8]_i_9_n_0\ : STD_LOGIC;
  signal HDL_Counter2_count_next : STD_LOGIC_VECTOR ( 0 to 0 );
  signal \HDL_Counter2_count_reg[0]_i_1_n_0\ : STD_LOGIC;
  signal \HDL_Counter2_count_reg[0]_i_1_n_1\ : STD_LOGIC;
  signal \HDL_Counter2_count_reg[0]_i_1_n_2\ : STD_LOGIC;
  signal \HDL_Counter2_count_reg[0]_i_1_n_3\ : STD_LOGIC;
  signal \HDL_Counter2_count_reg[0]_i_1_n_4\ : STD_LOGIC;
  signal \HDL_Counter2_count_reg[0]_i_1_n_5\ : STD_LOGIC;
  signal \HDL_Counter2_count_reg[0]_i_1_n_6\ : STD_LOGIC;
  signal \HDL_Counter2_count_reg[0]_i_1_n_7\ : STD_LOGIC;
  signal \HDL_Counter2_count_reg[16]_i_1_n_5\ : STD_LOGIC;
  signal \HDL_Counter2_count_reg[16]_i_1_n_6\ : STD_LOGIC;
  signal \HDL_Counter2_count_reg[16]_i_1_n_7\ : STD_LOGIC;
  signal \HDL_Counter2_count_reg[8]_i_1_n_0\ : STD_LOGIC;
  signal \HDL_Counter2_count_reg[8]_i_1_n_1\ : STD_LOGIC;
  signal \HDL_Counter2_count_reg[8]_i_1_n_2\ : STD_LOGIC;
  signal \HDL_Counter2_count_reg[8]_i_1_n_3\ : STD_LOGIC;
  signal \HDL_Counter2_count_reg[8]_i_1_n_4\ : STD_LOGIC;
  signal \HDL_Counter2_count_reg[8]_i_1_n_5\ : STD_LOGIC;
  signal \HDL_Counter2_count_reg[8]_i_1_n_6\ : STD_LOGIC;
  signal \HDL_Counter2_count_reg[8]_i_1_n_7\ : STD_LOGIC;
  signal HDL_Counter2_count_reg_7_sn_1 : STD_LOGIC;
  signal \Logical_Operator_out10_carry__0_i_1_n_0\ : STD_LOGIC;
  signal \Logical_Operator_out10_carry__0_i_2_n_0\ : STD_LOGIC;
  signal \Logical_Operator_out10_carry__0_i_3_n_0\ : STD_LOGIC;
  signal \Logical_Operator_out10_carry__0_i_4_n_0\ : STD_LOGIC;
  signal \Logical_Operator_out10_carry__0_i_5_n_0\ : STD_LOGIC;
  signal \Logical_Operator_out10_carry__0_i_6_n_0\ : STD_LOGIC;
  signal \Logical_Operator_out10_carry__0_i_7_n_0\ : STD_LOGIC;
  signal \Logical_Operator_out10_carry__0_n_4\ : STD_LOGIC;
  signal \Logical_Operator_out10_carry__0_n_5\ : STD_LOGIC;
  signal \Logical_Operator_out10_carry__0_n_6\ : STD_LOGIC;
  signal \Logical_Operator_out10_carry__0_n_7\ : STD_LOGIC;
  signal \Logical_Operator_out10_carry_i_10__1_n_0\ : STD_LOGIC;
  signal \Logical_Operator_out10_carry_i_11__2_n_0\ : STD_LOGIC;
  signal \Logical_Operator_out10_carry_i_12__2_n_0\ : STD_LOGIC;
  signal \Logical_Operator_out10_carry_i_13__2_n_0\ : STD_LOGIC;
  signal \Logical_Operator_out10_carry_i_14__2_n_0\ : STD_LOGIC;
  signal \Logical_Operator_out10_carry_i_15__2_n_0\ : STD_LOGIC;
  signal \Logical_Operator_out10_carry_i_16__0_n_0\ : STD_LOGIC;
  signal Logical_Operator_out10_carry_i_1_n_0 : STD_LOGIC;
  signal \Logical_Operator_out10_carry_i_2__1_n_0\ : STD_LOGIC;
  signal \Logical_Operator_out10_carry_i_3__2_n_0\ : STD_LOGIC;
  signal \Logical_Operator_out10_carry_i_4__2_n_0\ : STD_LOGIC;
  signal \Logical_Operator_out10_carry_i_5__2_n_0\ : STD_LOGIC;
  signal \Logical_Operator_out10_carry_i_6__2_n_0\ : STD_LOGIC;
  signal \Logical_Operator_out10_carry_i_7__2_n_0\ : STD_LOGIC;
  signal \Logical_Operator_out10_carry_i_8__0_n_0\ : STD_LOGIC;
  signal Logical_Operator_out10_carry_i_9_n_0 : STD_LOGIC;
  signal Logical_Operator_out10_carry_n_0 : STD_LOGIC;
  signal Logical_Operator_out10_carry_n_1 : STD_LOGIC;
  signal Logical_Operator_out10_carry_n_2 : STD_LOGIC;
  signal Logical_Operator_out10_carry_n_3 : STD_LOGIC;
  signal Logical_Operator_out10_carry_n_4 : STD_LOGIC;
  signal Logical_Operator_out10_carry_n_5 : STD_LOGIC;
  signal Logical_Operator_out10_carry_n_6 : STD_LOGIC;
  signal Logical_Operator_out10_carry_n_7 : STD_LOGIC;
  signal \^p\ : STD_LOGIC_VECTOR ( 5 downto 0 );
  signal Period_CenterMax0_carry_i_1_n_0 : STD_LOGIC;
  signal Period_CenterMax0_carry_i_2_n_0 : STD_LOGIC;
  signal Period_CenterMax0_carry_i_3_n_0 : STD_LOGIC;
  signal Period_CenterMax0_carry_i_4_n_0 : STD_LOGIC;
  signal Period_CenterMax0_carry_i_5_n_0 : STD_LOGIC;
  signal Period_CenterMax0_carry_i_6_n_0 : STD_LOGIC;
  signal Period_CenterMax0_carry_i_7_n_0 : STD_LOGIC;
  signal Period_CenterMax0_carry_i_8_n_0 : STD_LOGIC;
  signal Period_CenterMax0_carry_n_0 : STD_LOGIC;
  signal Period_CenterMax0_carry_n_1 : STD_LOGIC;
  signal Period_CenterMax0_carry_n_2 : STD_LOGIC;
  signal Period_CenterMax0_carry_n_3 : STD_LOGIC;
  signal Period_CenterMax0_carry_n_4 : STD_LOGIC;
  signal Period_CenterMax0_carry_n_5 : STD_LOGIC;
  signal Period_CenterMax0_carry_n_6 : STD_LOGIC;
  signal Period_CenterMax0_carry_n_7 : STD_LOGIC;
  signal Product_mul_temp0_out : STD_LOGIC_VECTOR ( 9 downto 0 );
  signal \^product_mul_temp[-1111111102]_0\ : STD_LOGIC_VECTOR ( 0 to 0 );
  signal \^product_mul_temp[-1111111103]_0\ : STD_LOGIC;
  signal \^product_mul_temp[-1111111104]_0\ : STD_LOGIC;
  signal \^product_mul_temp[-1111111105]_0\ : STD_LOGIC;
  signal \^product_mul_temp[-1111111106]_0\ : STD_LOGIC;
  signal \^product_mul_temp[-1111111107]_0\ : STD_LOGIC;
  signal \^product_mul_temp[-1111111108]_0\ : STD_LOGIC;
  signal \^product_mul_temp[-1111111109]_0\ : STD_LOGIC;
  signal \^product_mul_temp[-1111111110]_0\ : STD_LOGIC;
  signal \^product_mul_temp[-1111111111]_0\ : STD_LOGIC;
  signal \Product_mul_temp__0\ : STD_LOGIC_VECTOR ( 8 downto 0 );
  signal \Product_mul_temp__0_carry__0_i_1_n_0\ : STD_LOGIC;
  signal \Product_mul_temp__0_carry__0_i_2_n_0\ : STD_LOGIC;
  signal \Product_mul_temp__0_carry__0_i_3_n_0\ : STD_LOGIC;
  signal \Product_mul_temp__0_carry__0_i_4_n_0\ : STD_LOGIC;
  signal \Product_mul_temp__0_carry__0_i_5_n_0\ : STD_LOGIC;
  signal \Product_mul_temp__0_carry__0_i_6_n_0\ : STD_LOGIC;
  signal \Product_mul_temp__0_carry__0_n_14\ : STD_LOGIC;
  signal \Product_mul_temp__0_carry__0_n_7\ : STD_LOGIC;
  signal \Product_mul_temp__0_carry_i_10_n_0\ : STD_LOGIC;
  signal \Product_mul_temp__0_carry_i_11_n_0\ : STD_LOGIC;
  signal \Product_mul_temp__0_carry_i_12_n_0\ : STD_LOGIC;
  signal \Product_mul_temp__0_carry_i_13_n_0\ : STD_LOGIC;
  signal \Product_mul_temp__0_carry_i_14_n_0\ : STD_LOGIC;
  signal \Product_mul_temp__0_carry_i_15_n_0\ : STD_LOGIC;
  signal \Product_mul_temp__0_carry_i_16_n_0\ : STD_LOGIC;
  signal \Product_mul_temp__0_carry_i_17_n_0\ : STD_LOGIC;
  signal \Product_mul_temp__0_carry_i_18_n_0\ : STD_LOGIC;
  signal \Product_mul_temp__0_carry_i_19_n_0\ : STD_LOGIC;
  signal \Product_mul_temp__0_carry_i_1_n_0\ : STD_LOGIC;
  signal \Product_mul_temp__0_carry_i_20_n_0\ : STD_LOGIC;
  signal \Product_mul_temp__0_carry_i_2_n_0\ : STD_LOGIC;
  signal \Product_mul_temp__0_carry_i_3_n_0\ : STD_LOGIC;
  signal \Product_mul_temp__0_carry_i_4_n_0\ : STD_LOGIC;
  signal \Product_mul_temp__0_carry_i_5_n_0\ : STD_LOGIC;
  signal \Product_mul_temp__0_carry_i_6_n_0\ : STD_LOGIC;
  signal \Product_mul_temp__0_carry_i_7_n_0\ : STD_LOGIC;
  signal \Product_mul_temp__0_carry_i_8_n_0\ : STD_LOGIC;
  signal \Product_mul_temp__0_carry_i_9_n_0\ : STD_LOGIC;
  signal \Product_mul_temp__0_carry_n_0\ : STD_LOGIC;
  signal \Product_mul_temp__0_carry_n_1\ : STD_LOGIC;
  signal \Product_mul_temp__0_carry_n_2\ : STD_LOGIC;
  signal \Product_mul_temp__0_carry_n_3\ : STD_LOGIC;
  signal \Product_mul_temp__0_carry_n_4\ : STD_LOGIC;
  signal \Product_mul_temp__0_carry_n_5\ : STD_LOGIC;
  signal \Product_mul_temp__0_carry_n_6\ : STD_LOGIC;
  signal \Product_mul_temp__0_carry_n_7\ : STD_LOGIC;
  signal \Product_mul_temp_inferred__0/i__carry__0_n_7\ : STD_LOGIC;
  signal \Product_mul_temp_inferred__0/i__carry_n_0\ : STD_LOGIC;
  signal \Product_mul_temp_inferred__0/i__carry_n_1\ : STD_LOGIC;
  signal \Product_mul_temp_inferred__0/i__carry_n_2\ : STD_LOGIC;
  signal \Product_mul_temp_inferred__0/i__carry_n_3\ : STD_LOGIC;
  signal \Product_mul_temp_inferred__0/i__carry_n_4\ : STD_LOGIC;
  signal \Product_mul_temp_inferred__0/i__carry_n_5\ : STD_LOGIC;
  signal \Product_mul_temp_inferred__0/i__carry_n_6\ : STD_LOGIC;
  signal \Product_mul_temp_inferred__0/i__carry_n_7\ : STD_LOGIC;
  signal Product_mul_temp_n_100 : STD_LOGIC;
  signal Product_mul_temp_n_101 : STD_LOGIC;
  signal Product_mul_temp_n_102 : STD_LOGIC;
  signal Product_mul_temp_n_103 : STD_LOGIC;
  signal Product_mul_temp_n_104 : STD_LOGIC;
  signal Product_mul_temp_n_105 : STD_LOGIC;
  signal Product_mul_temp_n_58 : STD_LOGIC;
  signal Product_mul_temp_n_59 : STD_LOGIC;
  signal Product_mul_temp_n_60 : STD_LOGIC;
  signal Product_mul_temp_n_61 : STD_LOGIC;
  signal Product_mul_temp_n_62 : STD_LOGIC;
  signal Product_mul_temp_n_63 : STD_LOGIC;
  signal Product_mul_temp_n_64 : STD_LOGIC;
  signal Product_mul_temp_n_65 : STD_LOGIC;
  signal Product_mul_temp_n_66 : STD_LOGIC;
  signal Product_mul_temp_n_67 : STD_LOGIC;
  signal Product_mul_temp_n_68 : STD_LOGIC;
  signal Product_mul_temp_n_69 : STD_LOGIC;
  signal Product_mul_temp_n_70 : STD_LOGIC;
  signal Product_mul_temp_n_71 : STD_LOGIC;
  signal Product_mul_temp_n_72 : STD_LOGIC;
  signal Product_mul_temp_n_73 : STD_LOGIC;
  signal Product_mul_temp_n_74 : STD_LOGIC;
  signal Product_mul_temp_n_75 : STD_LOGIC;
  signal Product_mul_temp_n_76 : STD_LOGIC;
  signal Product_mul_temp_n_77 : STD_LOGIC;
  signal Product_mul_temp_n_78 : STD_LOGIC;
  signal Product_mul_temp_n_79 : STD_LOGIC;
  signal Product_mul_temp_n_80 : STD_LOGIC;
  signal Product_mul_temp_n_81 : STD_LOGIC;
  signal Product_mul_temp_n_82 : STD_LOGIC;
  signal Product_mul_temp_n_83 : STD_LOGIC;
  signal Product_mul_temp_n_84 : STD_LOGIC;
  signal Product_mul_temp_n_85 : STD_LOGIC;
  signal Product_mul_temp_n_86 : STD_LOGIC;
  signal Product_mul_temp_n_87 : STD_LOGIC;
  signal Product_mul_temp_n_88 : STD_LOGIC;
  signal Product_mul_temp_n_89 : STD_LOGIC;
  signal Product_mul_temp_n_90 : STD_LOGIC;
  signal Product_mul_temp_n_97 : STD_LOGIC;
  signal Product_mul_temp_n_98 : STD_LOGIC;
  signal Product_mul_temp_n_99 : STD_LOGIC;
  signal Relational_Operator4_relop1 : STD_LOGIC;
  signal \^relational_operator_1_cast\ : STD_LOGIC_VECTOR ( 13 downto 0 );
  signal Switch6_out1_1_i_3_n_0 : STD_LOGIC;
  signal Switch6_out1_1_i_4_n_0 : STD_LOGIC;
  signal Switch6_out1_1_i_5_n_0 : STD_LOGIC;
  signal Switch6_out1_1_i_6_n_0 : STD_LOGIC;
  signal Switch6_out1_1_i_7_n_0 : STD_LOGIC;
  signal Switch6_out1_1_i_8_n_0 : STD_LOGIC;
  signal \^u2_norm_1_reg[12]_0\ : STD_LOGIC_VECTOR ( 12 downto 0 );
  signal \^u2_norm_1_reg[13]\ : STD_LOGIC;
  signal \^u3_norm_1_reg[12]_0\ : STD_LOGIC_VECTOR ( 12 downto 0 );
  signal \^u3_norm_1_reg[13]\ : STD_LOGIC;
  signal dir_ctrl : STD_LOGIC;
  signal \i__carry__0_i_1__0_n_0\ : STD_LOGIC;
  signal \i__carry__0_i_2_n_0\ : STD_LOGIC;
  signal \i__carry_i_1__3_n_0\ : STD_LOGIC;
  signal \i__carry_i_2__3_n_0\ : STD_LOGIC;
  signal \i__carry_i_3__3_n_0\ : STD_LOGIC;
  signal \i__carry_i_4__3_n_0\ : STD_LOGIC;
  signal \i__carry_i_5__3_n_0\ : STD_LOGIC;
  signal \i__carry_i_6__3_n_0\ : STD_LOGIC;
  signal \i__carry_i_7__3_n_0\ : STD_LOGIC;
  signal \i__carry_i_8__3_n_0\ : STD_LOGIC;
  signal \NLW_HDL_Counter2_count_reg[16]_i_1_CO_UNCONNECTED\ : STD_LOGIC_VECTOR ( 7 downto 3 );
  signal \NLW_HDL_Counter2_count_reg[16]_i_1_O_UNCONNECTED\ : STD_LOGIC_VECTOR ( 7 downto 4 );
  signal NLW_Logical_Operator_out10_carry_O_UNCONNECTED : STD_LOGIC_VECTOR ( 7 downto 0 );
  signal \NLW_Logical_Operator_out10_carry__0_CO_UNCONNECTED\ : STD_LOGIC_VECTOR ( 7 downto 5 );
  signal \NLW_Logical_Operator_out10_carry__0_O_UNCONNECTED\ : STD_LOGIC_VECTOR ( 7 downto 0 );
  signal NLW_Period_CenterMax0_carry_O_UNCONNECTED : STD_LOGIC_VECTOR ( 7 downto 0 );
  signal \NLW_Period_CenterMax0_carry__0_CO_UNCONNECTED\ : STD_LOGIC_VECTOR ( 7 downto 1 );
  signal \NLW_Period_CenterMax0_carry__0_O_UNCONNECTED\ : STD_LOGIC_VECTOR ( 7 downto 0 );
  signal NLW_Product_mul_temp_CARRYCASCOUT_UNCONNECTED : STD_LOGIC;
  signal NLW_Product_mul_temp_MULTSIGNOUT_UNCONNECTED : STD_LOGIC;
  signal NLW_Product_mul_temp_OVERFLOW_UNCONNECTED : STD_LOGIC;
  signal NLW_Product_mul_temp_PATTERNBDETECT_UNCONNECTED : STD_LOGIC;
  signal NLW_Product_mul_temp_PATTERNDETECT_UNCONNECTED : STD_LOGIC;
  signal NLW_Product_mul_temp_UNDERFLOW_UNCONNECTED : STD_LOGIC;
  signal NLW_Product_mul_temp_ACOUT_UNCONNECTED : STD_LOGIC_VECTOR ( 29 downto 0 );
  signal NLW_Product_mul_temp_BCOUT_UNCONNECTED : STD_LOGIC_VECTOR ( 17 downto 0 );
  signal NLW_Product_mul_temp_CARRYOUT_UNCONNECTED : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal NLW_Product_mul_temp_PCOUT_UNCONNECTED : STD_LOGIC_VECTOR ( 47 downto 0 );
  signal NLW_Product_mul_temp_XOROUT_UNCONNECTED : STD_LOGIC_VECTOR ( 7 downto 0 );
  signal \NLW_Product_mul_temp__0_carry__0_CO_UNCONNECTED\ : STD_LOGIC_VECTOR ( 7 downto 1 );
  signal \NLW_Product_mul_temp__0_carry__0_O_UNCONNECTED\ : STD_LOGIC_VECTOR ( 7 downto 2 );
  signal \NLW_Product_mul_temp_inferred__0/i__carry__0_CO_UNCONNECTED\ : STD_LOGIC_VECTOR ( 7 downto 1 );
  signal \NLW_Product_mul_temp_inferred__0/i__carry__0_O_UNCONNECTED\ : STD_LOGIC_VECTOR ( 7 downto 2 );
  attribute SOFT_HLUTNM : string;
  attribute SOFT_HLUTNM of Delay6_out1_i_1 : label is "soft_lutpair10";
  attribute SOFT_HLUTNM of Delay6_out1_i_6 : label is "soft_lutpair11";
  attribute ADDER_THRESHOLD : integer;
  attribute ADDER_THRESHOLD of \HDL_Counter2_count_reg[0]_i_1\ : label is 16;
  attribute ADDER_THRESHOLD of \HDL_Counter2_count_reg[16]_i_1\ : label is 16;
  attribute ADDER_THRESHOLD of \HDL_Counter2_count_reg[8]_i_1\ : label is 16;
  attribute COMPARATOR_THRESHOLD : integer;
  attribute COMPARATOR_THRESHOLD of Logical_Operator_out10_carry : label is 11;
  attribute COMPARATOR_THRESHOLD of \Logical_Operator_out10_carry__0\ : label is 11;
  attribute KEEP_HIERARCHY : string;
  attribute KEEP_HIERARCHY of Product_mul_temp : label is "yes";
  attribute METHODOLOGY_DRC_VIOS : string;
  attribute METHODOLOGY_DRC_VIOS of Product_mul_temp : label is "{SYNTH-11 {cell *THIS*}}";
  attribute SOFT_HLUTNM of \Product_mul_temp__0_carry__0_i_4\ : label is "soft_lutpair12";
  attribute SOFT_HLUTNM of \Product_mul_temp__0_carry_i_16\ : label is "soft_lutpair14";
  attribute SOFT_HLUTNM of \Product_mul_temp__0_carry_i_18\ : label is "soft_lutpair12";
  attribute SOFT_HLUTNM of \Product_mul_temp__0_carry_i_19\ : label is "soft_lutpair14";
  attribute SOFT_HLUTNM of \Product_mul_temp__0_carry_i_20\ : label is "soft_lutpair11";
  attribute SOFT_HLUTNM of Product_mul_temp_i_2 : label is "soft_lutpair10";
  attribute ADDER_THRESHOLD of \Product_mul_temp_inferred__0/i__carry\ : label is 35;
  attribute ADDER_THRESHOLD of \Product_mul_temp_inferred__0/i__carry__0\ : label is 35;
  attribute SOFT_HLUTNM of Switch6_out1_1_i_4 : label is "soft_lutpair13";
  attribute SOFT_HLUTNM of Switch6_out1_1_i_7 : label is "soft_lutpair13";
begin
  \Allow_assymetrical_anew_reference_value__0\ <= \^allow_assymetrical_anew_reference_value__0\;
  CO(0) <= \^co\(0);
  DI(0) <= \^di\(0);
  HDL_Counter2_count_reg_7_sn_1 <= HDL_Counter2_count_reg_7_sp_1;
  P(5 downto 0) <= \^p\(5 downto 0);
  \Product_mul_temp[-1111111102]_0\(0) <= \^product_mul_temp[-1111111102]_0\(0);
  \Product_mul_temp[-1111111103]_0\ <= \^product_mul_temp[-1111111103]_0\;
  \Product_mul_temp[-1111111104]_0\ <= \^product_mul_temp[-1111111104]_0\;
  \Product_mul_temp[-1111111105]_0\ <= \^product_mul_temp[-1111111105]_0\;
  \Product_mul_temp[-1111111106]_0\ <= \^product_mul_temp[-1111111106]_0\;
  \Product_mul_temp[-1111111107]_0\ <= \^product_mul_temp[-1111111107]_0\;
  \Product_mul_temp[-1111111108]_0\ <= \^product_mul_temp[-1111111108]_0\;
  \Product_mul_temp[-1111111109]_0\ <= \^product_mul_temp[-1111111109]_0\;
  \Product_mul_temp[-1111111110]_0\ <= \^product_mul_temp[-1111111110]_0\;
  \Product_mul_temp[-1111111111]_0\ <= \^product_mul_temp[-1111111111]_0\;
  Relational_Operator_1_cast(13 downto 0) <= \^relational_operator_1_cast\(13 downto 0);
  \U2_norm_1_reg[12]_0\(12 downto 0) <= \^u2_norm_1_reg[12]_0\(12 downto 0);
  \U2_norm_1_reg[13]\ <= \^u2_norm_1_reg[13]\;
  \U3_norm_1_reg[12]_0\(12 downto 0) <= \^u3_norm_1_reg[12]_0\(12 downto 0);
  \U3_norm_1_reg[13]\ <= \^u3_norm_1_reg[13]\;
\Delay1_out1[0]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"AAEFAA20"
    )
        port map (
      I0 => \Delay1_out1_reg[13]_0\(0),
      I1 => HDL_Counter2_count_reg(12),
      I2 => \Delay2_out1_reg[13]_1\,
      I3 => \^co\(0),
      I4 => \Delay1_out1_reg[13]\(0),
      O => \^u2_norm_1_reg[12]_0\(0)
    );
\Delay1_out1[10]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"AAEFAA20"
    )
        port map (
      I0 => \Delay1_out1_reg[13]_0\(10),
      I1 => HDL_Counter2_count_reg(12),
      I2 => \Delay2_out1_reg[13]_1\,
      I3 => \^co\(0),
      I4 => \Delay1_out1_reg[13]\(10),
      O => \^u2_norm_1_reg[12]_0\(10)
    );
\Delay1_out1[11]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"AAEFAA20"
    )
        port map (
      I0 => \Delay1_out1_reg[13]_0\(11),
      I1 => HDL_Counter2_count_reg(12),
      I2 => \Delay2_out1_reg[13]_1\,
      I3 => \^co\(0),
      I4 => \Delay1_out1_reg[13]\(11),
      O => \^u2_norm_1_reg[12]_0\(11)
    );
\Delay1_out1[12]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"AAEFAA20"
    )
        port map (
      I0 => \Delay1_out1_reg[13]_0\(12),
      I1 => HDL_Counter2_count_reg(12),
      I2 => \Delay2_out1_reg[13]_1\,
      I3 => \^co\(0),
      I4 => \Delay1_out1_reg[13]\(12),
      O => \^u2_norm_1_reg[12]_0\(12)
    );
\Delay1_out1[13]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"AAEFAA20"
    )
        port map (
      I0 => \Delay1_out1_reg[13]_0\(13),
      I1 => HDL_Counter2_count_reg(12),
      I2 => \Delay2_out1_reg[13]_1\,
      I3 => \^co\(0),
      I4 => \Delay1_out1_reg[13]\(13),
      O => \^u2_norm_1_reg[13]\
    );
\Delay1_out1[1]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"AAEFAA20"
    )
        port map (
      I0 => \Delay1_out1_reg[13]_0\(1),
      I1 => HDL_Counter2_count_reg(12),
      I2 => \Delay2_out1_reg[13]_1\,
      I3 => \^co\(0),
      I4 => \Delay1_out1_reg[13]\(1),
      O => \^u2_norm_1_reg[12]_0\(1)
    );
\Delay1_out1[2]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"AAEFAA20"
    )
        port map (
      I0 => \Delay1_out1_reg[13]_0\(2),
      I1 => HDL_Counter2_count_reg(12),
      I2 => \Delay2_out1_reg[13]_1\,
      I3 => \^co\(0),
      I4 => \Delay1_out1_reg[13]\(2),
      O => \^u2_norm_1_reg[12]_0\(2)
    );
\Delay1_out1[3]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"AAEFAA20"
    )
        port map (
      I0 => \Delay1_out1_reg[13]_0\(3),
      I1 => HDL_Counter2_count_reg(12),
      I2 => \Delay2_out1_reg[13]_1\,
      I3 => \^co\(0),
      I4 => \Delay1_out1_reg[13]\(3),
      O => \^u2_norm_1_reg[12]_0\(3)
    );
\Delay1_out1[4]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"AAEFAA20"
    )
        port map (
      I0 => \Delay1_out1_reg[13]_0\(4),
      I1 => HDL_Counter2_count_reg(12),
      I2 => \Delay2_out1_reg[13]_1\,
      I3 => \^co\(0),
      I4 => \Delay1_out1_reg[13]\(4),
      O => \^u2_norm_1_reg[12]_0\(4)
    );
\Delay1_out1[5]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"AAEFAA20"
    )
        port map (
      I0 => \Delay1_out1_reg[13]_0\(5),
      I1 => HDL_Counter2_count_reg(12),
      I2 => \Delay2_out1_reg[13]_1\,
      I3 => \^co\(0),
      I4 => \Delay1_out1_reg[13]\(5),
      O => \^u2_norm_1_reg[12]_0\(5)
    );
\Delay1_out1[6]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"AAEFAA20"
    )
        port map (
      I0 => \Delay1_out1_reg[13]_0\(6),
      I1 => HDL_Counter2_count_reg(12),
      I2 => \Delay2_out1_reg[13]_1\,
      I3 => \^co\(0),
      I4 => \Delay1_out1_reg[13]\(6),
      O => \^u2_norm_1_reg[12]_0\(6)
    );
\Delay1_out1[7]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"AAEFAA20"
    )
        port map (
      I0 => \Delay1_out1_reg[13]_0\(7),
      I1 => HDL_Counter2_count_reg(12),
      I2 => \Delay2_out1_reg[13]_1\,
      I3 => \^co\(0),
      I4 => \Delay1_out1_reg[13]\(7),
      O => \^u2_norm_1_reg[12]_0\(7)
    );
\Delay1_out1[8]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"AAEFAA20"
    )
        port map (
      I0 => \Delay1_out1_reg[13]_0\(8),
      I1 => HDL_Counter2_count_reg(12),
      I2 => \Delay2_out1_reg[13]_1\,
      I3 => \^co\(0),
      I4 => \Delay1_out1_reg[13]\(8),
      O => \^u2_norm_1_reg[12]_0\(8)
    );
\Delay1_out1[9]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"AAEFAA20"
    )
        port map (
      I0 => \Delay1_out1_reg[13]_0\(9),
      I1 => HDL_Counter2_count_reg(12),
      I2 => \Delay2_out1_reg[13]_1\,
      I3 => \^co\(0),
      I4 => \Delay1_out1_reg[13]\(9),
      O => \^u2_norm_1_reg[12]_0\(9)
    );
\Delay2_out1[0]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"AAEFAA20"
    )
        port map (
      I0 => \Delay2_out1_reg[13]_0\(0),
      I1 => HDL_Counter2_count_reg(12),
      I2 => \Delay2_out1_reg[13]_1\,
      I3 => \^co\(0),
      I4 => \Delay2_out1_reg[13]\(0),
      O => \^u3_norm_1_reg[12]_0\(0)
    );
\Delay2_out1[10]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"AAEFAA20"
    )
        port map (
      I0 => \Delay2_out1_reg[13]_0\(10),
      I1 => HDL_Counter2_count_reg(12),
      I2 => \Delay2_out1_reg[13]_1\,
      I3 => \^co\(0),
      I4 => \Delay2_out1_reg[13]\(10),
      O => \^u3_norm_1_reg[12]_0\(10)
    );
\Delay2_out1[11]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"AAEFAA20"
    )
        port map (
      I0 => \Delay2_out1_reg[13]_0\(11),
      I1 => HDL_Counter2_count_reg(12),
      I2 => \Delay2_out1_reg[13]_1\,
      I3 => \^co\(0),
      I4 => \Delay2_out1_reg[13]\(11),
      O => \^u3_norm_1_reg[12]_0\(11)
    );
\Delay2_out1[12]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"AAEFAA20"
    )
        port map (
      I0 => \Delay2_out1_reg[13]_0\(12),
      I1 => HDL_Counter2_count_reg(12),
      I2 => \Delay2_out1_reg[13]_1\,
      I3 => \^co\(0),
      I4 => \Delay2_out1_reg[13]\(12),
      O => \^u3_norm_1_reg[12]_0\(12)
    );
\Delay2_out1[13]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"AAEFAA20"
    )
        port map (
      I0 => \Delay2_out1_reg[13]_0\(13),
      I1 => HDL_Counter2_count_reg(12),
      I2 => \Delay2_out1_reg[13]_1\,
      I3 => \^co\(0),
      I4 => \Delay2_out1_reg[13]\(13),
      O => \^u3_norm_1_reg[13]\
    );
\Delay2_out1[1]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"AAEFAA20"
    )
        port map (
      I0 => \Delay2_out1_reg[13]_0\(1),
      I1 => HDL_Counter2_count_reg(12),
      I2 => \Delay2_out1_reg[13]_1\,
      I3 => \^co\(0),
      I4 => \Delay2_out1_reg[13]\(1),
      O => \^u3_norm_1_reg[12]_0\(1)
    );
\Delay2_out1[2]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"AAEFAA20"
    )
        port map (
      I0 => \Delay2_out1_reg[13]_0\(2),
      I1 => HDL_Counter2_count_reg(12),
      I2 => \Delay2_out1_reg[13]_1\,
      I3 => \^co\(0),
      I4 => \Delay2_out1_reg[13]\(2),
      O => \^u3_norm_1_reg[12]_0\(2)
    );
\Delay2_out1[3]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"AAEFAA20"
    )
        port map (
      I0 => \Delay2_out1_reg[13]_0\(3),
      I1 => HDL_Counter2_count_reg(12),
      I2 => \Delay2_out1_reg[13]_1\,
      I3 => \^co\(0),
      I4 => \Delay2_out1_reg[13]\(3),
      O => \^u3_norm_1_reg[12]_0\(3)
    );
\Delay2_out1[4]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"AAEFAA20"
    )
        port map (
      I0 => \Delay2_out1_reg[13]_0\(4),
      I1 => HDL_Counter2_count_reg(12),
      I2 => \Delay2_out1_reg[13]_1\,
      I3 => \^co\(0),
      I4 => \Delay2_out1_reg[13]\(4),
      O => \^u3_norm_1_reg[12]_0\(4)
    );
\Delay2_out1[5]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"AAEFAA20"
    )
        port map (
      I0 => \Delay2_out1_reg[13]_0\(5),
      I1 => HDL_Counter2_count_reg(12),
      I2 => \Delay2_out1_reg[13]_1\,
      I3 => \^co\(0),
      I4 => \Delay2_out1_reg[13]\(5),
      O => \^u3_norm_1_reg[12]_0\(5)
    );
\Delay2_out1[6]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"AAEFAA20"
    )
        port map (
      I0 => \Delay2_out1_reg[13]_0\(6),
      I1 => HDL_Counter2_count_reg(12),
      I2 => \Delay2_out1_reg[13]_1\,
      I3 => \^co\(0),
      I4 => \Delay2_out1_reg[13]\(6),
      O => \^u3_norm_1_reg[12]_0\(6)
    );
\Delay2_out1[7]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"AAEFAA20"
    )
        port map (
      I0 => \Delay2_out1_reg[13]_0\(7),
      I1 => HDL_Counter2_count_reg(12),
      I2 => \Delay2_out1_reg[13]_1\,
      I3 => \^co\(0),
      I4 => \Delay2_out1_reg[13]\(7),
      O => \^u3_norm_1_reg[12]_0\(7)
    );
\Delay2_out1[8]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"AAEFAA20"
    )
        port map (
      I0 => \Delay2_out1_reg[13]_0\(8),
      I1 => HDL_Counter2_count_reg(12),
      I2 => \Delay2_out1_reg[13]_1\,
      I3 => \^co\(0),
      I4 => \Delay2_out1_reg[13]\(8),
      O => \^u3_norm_1_reg[12]_0\(8)
    );
\Delay2_out1[9]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"AAEFAA20"
    )
        port map (
      I0 => \Delay2_out1_reg[13]_0\(9),
      I1 => HDL_Counter2_count_reg(12),
      I2 => \Delay2_out1_reg[13]_1\,
      I3 => \^co\(0),
      I4 => \Delay2_out1_reg[13]\(9),
      O => \^u3_norm_1_reg[12]_0\(9)
    );
Delay6_out1_i_1: unisim.vcomponents.LUT5
    generic map(
      INIT => X"55550001"
    )
        port map (
      I0 => Relational_Operator4_relop1,
      I1 => Delay6_out1_i_2_n_0,
      I2 => Delay6_out1_i_3_n_0,
      I3 => HDL_Counter2_count_reg_7_sn_1,
      I4 => Delay6_out1,
      O => dir_ctrl
    );
Delay6_out1_i_2: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFFFFFFE"
    )
        port map (
      I0 => HDL_Counter2_count_reg(6),
      I1 => HDL_Counter2_count_reg(3),
      I2 => HDL_Counter2_count_reg(8),
      I3 => HDL_Counter2_count_reg(5),
      I4 => Delay6_out1_i_4_n_0,
      O => Delay6_out1_i_2_n_0
    );
Delay6_out1_i_3: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFFFFFFE"
    )
        port map (
      I0 => Delay6_out1_reg_1,
      I1 => Delay6_out1_reg_0,
      I2 => HDL_Counter2_count_reg(11),
      I3 => Delay6_out1_i_5_n_0,
      I4 => Delay6_out1_i_6_n_0,
      O => Delay6_out1_i_3_n_0
    );
Delay6_out1_i_4: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FFFE"
    )
        port map (
      I0 => HDL_Counter2_count_reg(1),
      I1 => HDL_Counter2_count_reg(4),
      I2 => \HDL_Counter2_count_reg[7]_1\,
      I3 => HDL_Counter2_count_reg(2),
      O => Delay6_out1_i_4_n_0
    );
Delay6_out1_i_5: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FFFE"
    )
        port map (
      I0 => \HDL_Counter2_count_reg[7]_3\,
      I1 => \HDL_Counter2_count_reg[7]_0\,
      I2 => HDL_Counter2_count_reg(0),
      I3 => \HDL_Counter2_count_reg[7]_2\,
      O => Delay6_out1_i_5_n_0
    );
Delay6_out1_i_6: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FFFE"
    )
        port map (
      I0 => HDL_Counter2_count_reg(9),
      I1 => HDL_Counter2_count_reg(12),
      I2 => HDL_Counter2_count_reg(7),
      I3 => HDL_Counter2_count_reg(10),
      O => Delay6_out1_i_6_n_0
    );
Delay6_out1_reg: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => dir_ctrl,
      Q => Delay6_out1,
      R => reset
    );
\Delay_out1[0]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"AAEFAA20"
    )
        port map (
      I0 => \Delay_out1_reg[13]_0\(0),
      I1 => HDL_Counter2_count_reg(12),
      I2 => \Delay2_out1_reg[13]_1\,
      I3 => \^co\(0),
      I4 => \Delay_out1_reg[13]\(0),
      O => \^relational_operator_1_cast\(0)
    );
\Delay_out1[10]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"AAEFAA20"
    )
        port map (
      I0 => \Delay_out1_reg[13]_0\(10),
      I1 => HDL_Counter2_count_reg(12),
      I2 => \Delay2_out1_reg[13]_1\,
      I3 => \^co\(0),
      I4 => \Delay_out1_reg[13]\(10),
      O => \^relational_operator_1_cast\(10)
    );
\Delay_out1[11]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"AAEFAA20"
    )
        port map (
      I0 => \Delay_out1_reg[13]_0\(11),
      I1 => HDL_Counter2_count_reg(12),
      I2 => \Delay2_out1_reg[13]_1\,
      I3 => \^co\(0),
      I4 => \Delay_out1_reg[13]\(11),
      O => \^relational_operator_1_cast\(11)
    );
\Delay_out1[12]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"AAEFAA20"
    )
        port map (
      I0 => \Delay_out1_reg[13]_0\(12),
      I1 => HDL_Counter2_count_reg(12),
      I2 => \Delay2_out1_reg[13]_1\,
      I3 => \^co\(0),
      I4 => \Delay_out1_reg[13]\(12),
      O => \^relational_operator_1_cast\(12)
    );
\Delay_out1[13]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"AAEFAA20"
    )
        port map (
      I0 => \Delay_out1_reg[13]_0\(13),
      I1 => HDL_Counter2_count_reg(12),
      I2 => \Delay2_out1_reg[13]_1\,
      I3 => \^co\(0),
      I4 => \Delay_out1_reg[13]\(13),
      O => \^relational_operator_1_cast\(13)
    );
\Delay_out1[1]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"AAEFAA20"
    )
        port map (
      I0 => \Delay_out1_reg[13]_0\(1),
      I1 => HDL_Counter2_count_reg(12),
      I2 => \Delay2_out1_reg[13]_1\,
      I3 => \^co\(0),
      I4 => \Delay_out1_reg[13]\(1),
      O => \^relational_operator_1_cast\(1)
    );
\Delay_out1[2]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"AAEFAA20"
    )
        port map (
      I0 => \Delay_out1_reg[13]_0\(2),
      I1 => HDL_Counter2_count_reg(12),
      I2 => \Delay2_out1_reg[13]_1\,
      I3 => \^co\(0),
      I4 => \Delay_out1_reg[13]\(2),
      O => \^relational_operator_1_cast\(2)
    );
\Delay_out1[3]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"AAEFAA20"
    )
        port map (
      I0 => \Delay_out1_reg[13]_0\(3),
      I1 => HDL_Counter2_count_reg(12),
      I2 => \Delay2_out1_reg[13]_1\,
      I3 => \^co\(0),
      I4 => \Delay_out1_reg[13]\(3),
      O => \^relational_operator_1_cast\(3)
    );
\Delay_out1[4]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"AAEFAA20"
    )
        port map (
      I0 => \Delay_out1_reg[13]_0\(4),
      I1 => HDL_Counter2_count_reg(12),
      I2 => \Delay2_out1_reg[13]_1\,
      I3 => \^co\(0),
      I4 => \Delay_out1_reg[13]\(4),
      O => \^relational_operator_1_cast\(4)
    );
\Delay_out1[5]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"AAEFAA20"
    )
        port map (
      I0 => \Delay_out1_reg[13]_0\(5),
      I1 => HDL_Counter2_count_reg(12),
      I2 => \Delay2_out1_reg[13]_1\,
      I3 => \^co\(0),
      I4 => \Delay_out1_reg[13]\(5),
      O => \^relational_operator_1_cast\(5)
    );
\Delay_out1[6]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"AAEFAA20"
    )
        port map (
      I0 => \Delay_out1_reg[13]_0\(6),
      I1 => HDL_Counter2_count_reg(12),
      I2 => \Delay2_out1_reg[13]_1\,
      I3 => \^co\(0),
      I4 => \Delay_out1_reg[13]\(6),
      O => \^relational_operator_1_cast\(6)
    );
\Delay_out1[7]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"AAEFAA20"
    )
        port map (
      I0 => \Delay_out1_reg[13]_0\(7),
      I1 => HDL_Counter2_count_reg(12),
      I2 => \Delay2_out1_reg[13]_1\,
      I3 => \^co\(0),
      I4 => \Delay_out1_reg[13]\(7),
      O => \^relational_operator_1_cast\(7)
    );
\Delay_out1[8]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"AAEFAA20"
    )
        port map (
      I0 => \Delay_out1_reg[13]_0\(8),
      I1 => HDL_Counter2_count_reg(12),
      I2 => \Delay2_out1_reg[13]_1\,
      I3 => \^co\(0),
      I4 => \Delay_out1_reg[13]\(8),
      O => \^relational_operator_1_cast\(8)
    );
\Delay_out1[9]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"AAEFAA20"
    )
        port map (
      I0 => \Delay_out1_reg[13]_0\(9),
      I1 => HDL_Counter2_count_reg(12),
      I2 => \Delay2_out1_reg[13]_1\,
      I3 => \^co\(0),
      I4 => \Delay_out1_reg[13]\(9),
      O => \^relational_operator_1_cast\(9)
    );
\HDL_Counter2_count[0]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"55550001AAAAFFFE"
    )
        port map (
      I0 => Relational_Operator4_relop1,
      I1 => Delay6_out1_i_2_n_0,
      I2 => Delay6_out1_i_3_n_0,
      I3 => HDL_Counter2_count_reg_7_sn_1,
      I4 => Delay6_out1,
      I5 => \HDL_Counter2_count_reg[7]_0\,
      O => \HDL_Counter2_count[0]_i_2_n_0\
    );
\HDL_Counter2_count[0]_i_3\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"55550001AAAAFFFE"
    )
        port map (
      I0 => Relational_Operator4_relop1,
      I1 => Delay6_out1_i_2_n_0,
      I2 => Delay6_out1_i_3_n_0,
      I3 => HDL_Counter2_count_reg_7_sn_1,
      I4 => Delay6_out1,
      I5 => \HDL_Counter2_count_reg[7]_1\,
      O => \HDL_Counter2_count[0]_i_3_n_0\
    );
\HDL_Counter2_count[0]_i_4\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"55550001AAAAFFFE"
    )
        port map (
      I0 => Relational_Operator4_relop1,
      I1 => Delay6_out1_i_2_n_0,
      I2 => Delay6_out1_i_3_n_0,
      I3 => HDL_Counter2_count_reg_7_sn_1,
      I4 => Delay6_out1,
      I5 => \HDL_Counter2_count_reg[7]_2\,
      O => \HDL_Counter2_count[0]_i_4_n_0\
    );
\HDL_Counter2_count[0]_i_5\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"55550001AAAAFFFE"
    )
        port map (
      I0 => Relational_Operator4_relop1,
      I1 => Delay6_out1_i_2_n_0,
      I2 => Delay6_out1_i_3_n_0,
      I3 => HDL_Counter2_count_reg_7_sn_1,
      I4 => Delay6_out1,
      I5 => \HDL_Counter2_count_reg[7]_3\,
      O => \HDL_Counter2_count[0]_i_5_n_0\
    );
\HDL_Counter2_count[0]_i_6\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"55550001AAAAFFFE"
    )
        port map (
      I0 => Relational_Operator4_relop1,
      I1 => Delay6_out1_i_2_n_0,
      I2 => Delay6_out1_i_3_n_0,
      I3 => HDL_Counter2_count_reg_7_sn_1,
      I4 => Delay6_out1,
      I5 => Delay6_out1_reg_1,
      O => \HDL_Counter2_count[0]_i_6_n_0\
    );
\HDL_Counter2_count[0]_i_7\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"55550001AAAAFFFE"
    )
        port map (
      I0 => Relational_Operator4_relop1,
      I1 => Delay6_out1_i_2_n_0,
      I2 => Delay6_out1_i_3_n_0,
      I3 => HDL_Counter2_count_reg_7_sn_1,
      I4 => Delay6_out1,
      I5 => Delay6_out1_reg_0,
      O => \HDL_Counter2_count[0]_i_7_n_0\
    );
\HDL_Counter2_count[0]_i_8\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"55550001AAAAFFFE"
    )
        port map (
      I0 => Relational_Operator4_relop1,
      I1 => Delay6_out1_i_2_n_0,
      I2 => Delay6_out1_i_3_n_0,
      I3 => HDL_Counter2_count_reg_7_sn_1,
      I4 => Delay6_out1,
      I5 => HDL_Counter2_count_reg(0),
      O => \HDL_Counter2_count[0]_i_8_n_0\
    );
\HDL_Counter2_count[0]_i_9\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"AA55FF01"
    )
        port map (
      I0 => Relational_Operator4_relop1,
      I1 => Delay6_out1_i_2_n_0,
      I2 => Delay6_out1_i_3_n_0,
      I3 => HDL_Counter2_count_reg_7_sn_1,
      I4 => Delay6_out1,
      O => \HDL_Counter2_count[0]_i_9_n_0\
    );
\HDL_Counter2_count[16]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"55550001AAAAFFFE"
    )
        port map (
      I0 => Relational_Operator4_relop1,
      I1 => Delay6_out1_i_2_n_0,
      I2 => Delay6_out1_i_3_n_0,
      I3 => HDL_Counter2_count_reg_7_sn_1,
      I4 => Delay6_out1,
      I5 => HDL_Counter2_count_reg(12),
      O => \HDL_Counter2_count[16]_i_2_n_0\
    );
\HDL_Counter2_count[16]_i_3\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"55550001AAAAFFFE"
    )
        port map (
      I0 => Relational_Operator4_relop1,
      I1 => Delay6_out1_i_2_n_0,
      I2 => Delay6_out1_i_3_n_0,
      I3 => HDL_Counter2_count_reg_7_sn_1,
      I4 => Delay6_out1,
      I5 => HDL_Counter2_count_reg(11),
      O => \HDL_Counter2_count[16]_i_3_n_0\
    );
\HDL_Counter2_count[16]_i_4\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"55550001AAAAFFFE"
    )
        port map (
      I0 => Relational_Operator4_relop1,
      I1 => Delay6_out1_i_2_n_0,
      I2 => Delay6_out1_i_3_n_0,
      I3 => HDL_Counter2_count_reg_7_sn_1,
      I4 => Delay6_out1,
      I5 => HDL_Counter2_count_reg(10),
      O => \HDL_Counter2_count[16]_i_4_n_0\
    );
\HDL_Counter2_count[16]_i_5\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"55550001AAAAFFFE"
    )
        port map (
      I0 => Relational_Operator4_relop1,
      I1 => Delay6_out1_i_2_n_0,
      I2 => Delay6_out1_i_3_n_0,
      I3 => HDL_Counter2_count_reg_7_sn_1,
      I4 => Delay6_out1,
      I5 => HDL_Counter2_count_reg(9),
      O => \HDL_Counter2_count[16]_i_5_n_0\
    );
\HDL_Counter2_count[8]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"55550001AAAAFFFE"
    )
        port map (
      I0 => Relational_Operator4_relop1,
      I1 => Delay6_out1_i_2_n_0,
      I2 => Delay6_out1_i_3_n_0,
      I3 => HDL_Counter2_count_reg_7_sn_1,
      I4 => Delay6_out1,
      I5 => HDL_Counter2_count_reg(8),
      O => \HDL_Counter2_count[8]_i_2_n_0\
    );
\HDL_Counter2_count[8]_i_3\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"55550001AAAAFFFE"
    )
        port map (
      I0 => Relational_Operator4_relop1,
      I1 => Delay6_out1_i_2_n_0,
      I2 => Delay6_out1_i_3_n_0,
      I3 => HDL_Counter2_count_reg_7_sn_1,
      I4 => Delay6_out1,
      I5 => HDL_Counter2_count_reg(7),
      O => \HDL_Counter2_count[8]_i_3_n_0\
    );
\HDL_Counter2_count[8]_i_4\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"55550001AAAAFFFE"
    )
        port map (
      I0 => Relational_Operator4_relop1,
      I1 => Delay6_out1_i_2_n_0,
      I2 => Delay6_out1_i_3_n_0,
      I3 => HDL_Counter2_count_reg_7_sn_1,
      I4 => Delay6_out1,
      I5 => HDL_Counter2_count_reg(6),
      O => \HDL_Counter2_count[8]_i_4_n_0\
    );
\HDL_Counter2_count[8]_i_5\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"55550001AAAAFFFE"
    )
        port map (
      I0 => Relational_Operator4_relop1,
      I1 => Delay6_out1_i_2_n_0,
      I2 => Delay6_out1_i_3_n_0,
      I3 => HDL_Counter2_count_reg_7_sn_1,
      I4 => Delay6_out1,
      I5 => HDL_Counter2_count_reg(5),
      O => \HDL_Counter2_count[8]_i_5_n_0\
    );
\HDL_Counter2_count[8]_i_6\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"55550001AAAAFFFE"
    )
        port map (
      I0 => Relational_Operator4_relop1,
      I1 => Delay6_out1_i_2_n_0,
      I2 => Delay6_out1_i_3_n_0,
      I3 => HDL_Counter2_count_reg_7_sn_1,
      I4 => Delay6_out1,
      I5 => HDL_Counter2_count_reg(4),
      O => \HDL_Counter2_count[8]_i_6_n_0\
    );
\HDL_Counter2_count[8]_i_7\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"55550001AAAAFFFE"
    )
        port map (
      I0 => Relational_Operator4_relop1,
      I1 => Delay6_out1_i_2_n_0,
      I2 => Delay6_out1_i_3_n_0,
      I3 => HDL_Counter2_count_reg_7_sn_1,
      I4 => Delay6_out1,
      I5 => HDL_Counter2_count_reg(3),
      O => \HDL_Counter2_count[8]_i_7_n_0\
    );
\HDL_Counter2_count[8]_i_8\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"55550001AAAAFFFE"
    )
        port map (
      I0 => Relational_Operator4_relop1,
      I1 => Delay6_out1_i_2_n_0,
      I2 => Delay6_out1_i_3_n_0,
      I3 => HDL_Counter2_count_reg_7_sn_1,
      I4 => Delay6_out1,
      I5 => HDL_Counter2_count_reg(2),
      O => \HDL_Counter2_count[8]_i_8_n_0\
    );
\HDL_Counter2_count[8]_i_9\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"55550001AAAAFFFE"
    )
        port map (
      I0 => Relational_Operator4_relop1,
      I1 => Delay6_out1_i_2_n_0,
      I2 => Delay6_out1_i_3_n_0,
      I3 => HDL_Counter2_count_reg_7_sn_1,
      I4 => Delay6_out1,
      I5 => HDL_Counter2_count_reg(1),
      O => \HDL_Counter2_count[8]_i_9_n_0\
    );
\HDL_Counter2_count_next_carry__0_i_1\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"9"
    )
        port map (
      I0 => HDL_Counter2_count_reg(8),
      I1 => HDL_Counter2_count_reg(9),
      O => \HDL_Counter2_count_reg[15]\(7)
    );
\HDL_Counter2_count_next_carry__0_i_2\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"9"
    )
        port map (
      I0 => HDL_Counter2_count_reg(7),
      I1 => HDL_Counter2_count_reg(8),
      O => \HDL_Counter2_count_reg[15]\(6)
    );
\HDL_Counter2_count_next_carry__0_i_3\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"9"
    )
        port map (
      I0 => HDL_Counter2_count_reg(6),
      I1 => HDL_Counter2_count_reg(7),
      O => \HDL_Counter2_count_reg[15]\(5)
    );
\HDL_Counter2_count_next_carry__0_i_4\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"9"
    )
        port map (
      I0 => HDL_Counter2_count_reg(5),
      I1 => HDL_Counter2_count_reg(6),
      O => \HDL_Counter2_count_reg[15]\(4)
    );
\HDL_Counter2_count_next_carry__0_i_5\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"9"
    )
        port map (
      I0 => HDL_Counter2_count_reg(4),
      I1 => HDL_Counter2_count_reg(5),
      O => \HDL_Counter2_count_reg[15]\(3)
    );
\HDL_Counter2_count_next_carry__0_i_6\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"9"
    )
        port map (
      I0 => HDL_Counter2_count_reg(3),
      I1 => HDL_Counter2_count_reg(4),
      O => \HDL_Counter2_count_reg[15]\(2)
    );
\HDL_Counter2_count_next_carry__0_i_7\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"9"
    )
        port map (
      I0 => HDL_Counter2_count_reg(2),
      I1 => HDL_Counter2_count_reg(3),
      O => \HDL_Counter2_count_reg[15]\(1)
    );
\HDL_Counter2_count_next_carry__0_i_8\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"9"
    )
        port map (
      I0 => HDL_Counter2_count_reg(1),
      I1 => HDL_Counter2_count_reg(2),
      O => \HDL_Counter2_count_reg[15]\(0)
    );
HDL_Counter2_count_next_carry_i_1: unisim.vcomponents.LUT5
    generic map(
      INIT => X"55550001"
    )
        port map (
      I0 => Relational_Operator4_relop1,
      I1 => Delay6_out1_i_2_n_0,
      I2 => Delay6_out1_i_3_n_0,
      I3 => HDL_Counter2_count_reg_7_sn_1,
      I4 => Delay6_out1,
      O => \HDL_Counter2_count_reg[0]_1\(0)
    );
HDL_Counter2_count_next_carry_i_10: unisim.vcomponents.LUT6
    generic map(
      INIT => X"55550001AAAAFFFE"
    )
        port map (
      I0 => Relational_Operator4_relop1,
      I1 => Delay6_out1_i_2_n_0,
      I2 => Delay6_out1_i_3_n_0,
      I3 => HDL_Counter2_count_reg_7_sn_1,
      I4 => Delay6_out1,
      I5 => HDL_Counter2_count_reg(0),
      O => \HDL_Counter2_count_reg[0]_2\(0)
    );
HDL_Counter2_count_next_carry_i_2: unisim.vcomponents.LUT5
    generic map(
      INIT => X"AAAAFFFE"
    )
        port map (
      I0 => Relational_Operator4_relop1,
      I1 => Delay6_out1_i_2_n_0,
      I2 => Delay6_out1_i_3_n_0,
      I3 => HDL_Counter2_count_reg_7_sn_1,
      I4 => Delay6_out1,
      O => \^di\(0)
    );
HDL_Counter2_count_next_carry_i_9: unisim.vcomponents.LUT6
    generic map(
      INIT => X"55550001AAAAFFFE"
    )
        port map (
      I0 => Relational_Operator4_relop1,
      I1 => Delay6_out1_i_2_n_0,
      I2 => Delay6_out1_i_3_n_0,
      I3 => HDL_Counter2_count_reg_7_sn_1,
      I4 => Delay6_out1,
      I5 => Delay6_out1_reg_0,
      O => \HDL_Counter2_count_reg[0]_2\(1)
    );
\HDL_Counter2_count_reg[0]_i_1\: unisim.vcomponents.CARRY8
     port map (
      CI => \^di\(0),
      CI_TOP => '0',
      CO(7) => \HDL_Counter2_count_reg[0]_i_1_n_0\,
      CO(6) => \HDL_Counter2_count_reg[0]_i_1_n_1\,
      CO(5) => \HDL_Counter2_count_reg[0]_i_1_n_2\,
      CO(4) => \HDL_Counter2_count_reg[0]_i_1_n_3\,
      CO(3) => \HDL_Counter2_count_reg[0]_i_1_n_4\,
      CO(2) => \HDL_Counter2_count_reg[0]_i_1_n_5\,
      CO(1) => \HDL_Counter2_count_reg[0]_i_1_n_6\,
      CO(0) => \HDL_Counter2_count_reg[0]_i_1_n_7\,
      DI(7) => \^di\(0),
      DI(6) => \^di\(0),
      DI(5) => \^di\(0),
      DI(4) => \^di\(0),
      DI(3) => \^di\(0),
      DI(2) => \^di\(0),
      DI(1) => \^di\(0),
      DI(0) => HDL_Counter2_count_reg_7_sn_1,
      O(7 downto 0) => O(7 downto 0),
      S(7) => \HDL_Counter2_count[0]_i_2_n_0\,
      S(6) => \HDL_Counter2_count[0]_i_3_n_0\,
      S(5) => \HDL_Counter2_count[0]_i_4_n_0\,
      S(4) => \HDL_Counter2_count[0]_i_5_n_0\,
      S(3) => \HDL_Counter2_count[0]_i_6_n_0\,
      S(2) => \HDL_Counter2_count[0]_i_7_n_0\,
      S(1) => \HDL_Counter2_count[0]_i_8_n_0\,
      S(0) => \HDL_Counter2_count[0]_i_9_n_0\
    );
\HDL_Counter2_count_reg[16]_i_1\: unisim.vcomponents.CARRY8
     port map (
      CI => \HDL_Counter2_count_reg[8]_i_1_n_0\,
      CI_TOP => '0',
      CO(7 downto 3) => \NLW_HDL_Counter2_count_reg[16]_i_1_CO_UNCONNECTED\(7 downto 3),
      CO(2) => \HDL_Counter2_count_reg[16]_i_1_n_5\,
      CO(1) => \HDL_Counter2_count_reg[16]_i_1_n_6\,
      CO(0) => \HDL_Counter2_count_reg[16]_i_1_n_7\,
      DI(7 downto 3) => B"00000",
      DI(2) => \^di\(0),
      DI(1) => \^di\(0),
      DI(0) => \^di\(0),
      O(7 downto 4) => \NLW_HDL_Counter2_count_reg[16]_i_1_O_UNCONNECTED\(7 downto 4),
      O(3 downto 0) => \HDL_Counter2_count_reg[0]_0\(3 downto 0),
      S(7 downto 4) => B"0000",
      S(3) => \HDL_Counter2_count[16]_i_2_n_0\,
      S(2) => \HDL_Counter2_count[16]_i_3_n_0\,
      S(1) => \HDL_Counter2_count[16]_i_4_n_0\,
      S(0) => \HDL_Counter2_count[16]_i_5_n_0\
    );
\HDL_Counter2_count_reg[8]_i_1\: unisim.vcomponents.CARRY8
     port map (
      CI => \HDL_Counter2_count_reg[0]_i_1_n_0\,
      CI_TOP => '0',
      CO(7) => \HDL_Counter2_count_reg[8]_i_1_n_0\,
      CO(6) => \HDL_Counter2_count_reg[8]_i_1_n_1\,
      CO(5) => \HDL_Counter2_count_reg[8]_i_1_n_2\,
      CO(4) => \HDL_Counter2_count_reg[8]_i_1_n_3\,
      CO(3) => \HDL_Counter2_count_reg[8]_i_1_n_4\,
      CO(2) => \HDL_Counter2_count_reg[8]_i_1_n_5\,
      CO(1) => \HDL_Counter2_count_reg[8]_i_1_n_6\,
      CO(0) => \HDL_Counter2_count_reg[8]_i_1_n_7\,
      DI(7) => \^di\(0),
      DI(6) => \^di\(0),
      DI(5) => \^di\(0),
      DI(4) => \^di\(0),
      DI(3) => \^di\(0),
      DI(2) => \^di\(0),
      DI(1) => \^di\(0),
      DI(0) => \^di\(0),
      O(7 downto 0) => \HDL_Counter2_count_reg[0]\(7 downto 0),
      S(7) => \HDL_Counter2_count[8]_i_2_n_0\,
      S(6) => \HDL_Counter2_count[8]_i_3_n_0\,
      S(5) => \HDL_Counter2_count[8]_i_4_n_0\,
      S(4) => \HDL_Counter2_count[8]_i_5_n_0\,
      S(3) => \HDL_Counter2_count[8]_i_6_n_0\,
      S(2) => \HDL_Counter2_count[8]_i_7_n_0\,
      S(1) => \HDL_Counter2_count[8]_i_8_n_0\,
      S(0) => \HDL_Counter2_count[8]_i_9_n_0\
    );
Logical_Operator_out10_carry: unisim.vcomponents.CARRY8
     port map (
      CI => '1',
      CI_TOP => '0',
      CO(7) => Logical_Operator_out10_carry_n_0,
      CO(6) => Logical_Operator_out10_carry_n_1,
      CO(5) => Logical_Operator_out10_carry_n_2,
      CO(4) => Logical_Operator_out10_carry_n_3,
      CO(3) => Logical_Operator_out10_carry_n_4,
      CO(2) => Logical_Operator_out10_carry_n_5,
      CO(1) => Logical_Operator_out10_carry_n_6,
      CO(0) => Logical_Operator_out10_carry_n_7,
      DI(7) => Logical_Operator_out10_carry_i_1_n_0,
      DI(6) => \Logical_Operator_out10_carry_i_2__1_n_0\,
      DI(5) => \Logical_Operator_out10_carry_i_3__2_n_0\,
      DI(4) => \Logical_Operator_out10_carry_i_4__2_n_0\,
      DI(3) => \Logical_Operator_out10_carry_i_5__2_n_0\,
      DI(2) => \Logical_Operator_out10_carry_i_6__2_n_0\,
      DI(1) => \Logical_Operator_out10_carry_i_7__2_n_0\,
      DI(0) => \Logical_Operator_out10_carry_i_8__0_n_0\,
      O(7 downto 0) => NLW_Logical_Operator_out10_carry_O_UNCONNECTED(7 downto 0),
      S(7) => Logical_Operator_out10_carry_i_9_n_0,
      S(6) => \Logical_Operator_out10_carry_i_10__1_n_0\,
      S(5) => \Logical_Operator_out10_carry_i_11__2_n_0\,
      S(4) => \Logical_Operator_out10_carry_i_12__2_n_0\,
      S(3) => \Logical_Operator_out10_carry_i_13__2_n_0\,
      S(2) => \Logical_Operator_out10_carry_i_14__2_n_0\,
      S(1) => \Logical_Operator_out10_carry_i_15__2_n_0\,
      S(0) => \Logical_Operator_out10_carry_i_16__0_n_0\
    );
\Logical_Operator_out10_carry__0\: unisim.vcomponents.CARRY8
     port map (
      CI => Logical_Operator_out10_carry_n_0,
      CI_TOP => '0',
      CO(7 downto 5) => \NLW_Logical_Operator_out10_carry__0_CO_UNCONNECTED\(7 downto 5),
      CO(4) => Relational_Operator4_relop1,
      CO(3) => \Logical_Operator_out10_carry__0_n_4\,
      CO(2) => \Logical_Operator_out10_carry__0_n_5\,
      CO(1) => \Logical_Operator_out10_carry__0_n_6\,
      CO(0) => \Logical_Operator_out10_carry__0_n_7\,
      DI(7 downto 2) => B"000000",
      DI(1) => \Logical_Operator_out10_carry__0_i_1_n_0\,
      DI(0) => \Logical_Operator_out10_carry__0_i_2_n_0\,
      O(7 downto 0) => \NLW_Logical_Operator_out10_carry__0_O_UNCONNECTED\(7 downto 0),
      S(7 downto 5) => B"000",
      S(4) => \Logical_Operator_out10_carry__0_i_3_n_0\,
      S(3) => \Logical_Operator_out10_carry__0_i_4_n_0\,
      S(2) => \Logical_Operator_out10_carry__0_i_5_n_0\,
      S(1) => \Logical_Operator_out10_carry__0_i_6_n_0\,
      S(0) => \Logical_Operator_out10_carry__0_i_7_n_0\
    );
\Logical_Operator_out10_carry__0_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"22B2"
    )
        port map (
      I0 => HDL_Counter2_count_reg(12),
      I1 => \Logical_Operator_out10_carry__0_0\(19),
      I2 => HDL_Counter2_count_reg(11),
      I3 => \Logical_Operator_out10_carry__0_0\(18),
      O => \Logical_Operator_out10_carry__0_i_1_n_0\
    );
\Logical_Operator_out10_carry__0_i_2\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"22B2"
    )
        port map (
      I0 => HDL_Counter2_count_reg(10),
      I1 => \Logical_Operator_out10_carry__0_0\(17),
      I2 => HDL_Counter2_count_reg(9),
      I3 => \Logical_Operator_out10_carry__0_0\(16),
      O => \Logical_Operator_out10_carry__0_i_2_n_0\
    );
\Logical_Operator_out10_carry__0_i_3\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => \Logical_Operator_out10_carry__0_0\(24),
      O => \Logical_Operator_out10_carry__0_i_3_n_0\
    );
\Logical_Operator_out10_carry__0_i_4\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => \Logical_Operator_out10_carry__0_0\(23),
      I1 => \Logical_Operator_out10_carry__0_0\(22),
      O => \Logical_Operator_out10_carry__0_i_4_n_0\
    );
\Logical_Operator_out10_carry__0_i_5\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => \Logical_Operator_out10_carry__0_0\(21),
      I1 => \Logical_Operator_out10_carry__0_0\(20),
      O => \Logical_Operator_out10_carry__0_i_5_n_0\
    );
\Logical_Operator_out10_carry__0_i_6\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"9009"
    )
        port map (
      I0 => HDL_Counter2_count_reg(11),
      I1 => \Logical_Operator_out10_carry__0_0\(18),
      I2 => HDL_Counter2_count_reg(12),
      I3 => \Logical_Operator_out10_carry__0_0\(19),
      O => \Logical_Operator_out10_carry__0_i_6_n_0\
    );
\Logical_Operator_out10_carry__0_i_7\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"9009"
    )
        port map (
      I0 => HDL_Counter2_count_reg(9),
      I1 => \Logical_Operator_out10_carry__0_0\(16),
      I2 => HDL_Counter2_count_reg(10),
      I3 => \Logical_Operator_out10_carry__0_0\(17),
      O => \Logical_Operator_out10_carry__0_i_7_n_0\
    );
Logical_Operator_out10_carry_i_1: unisim.vcomponents.LUT4
    generic map(
      INIT => X"22B2"
    )
        port map (
      I0 => HDL_Counter2_count_reg(8),
      I1 => \Logical_Operator_out10_carry__0_0\(15),
      I2 => HDL_Counter2_count_reg(7),
      I3 => \Logical_Operator_out10_carry__0_0\(14),
      O => Logical_Operator_out10_carry_i_1_n_0
    );
Logical_Operator_out10_carry_i_10: unisim.vcomponents.LUT6
    generic map(
      INIT => X"9990009000099909"
    )
        port map (
      I0 => \^u3_norm_1_reg[12]_0\(11),
      I1 => Saturation_out1(11),
      I2 => \Delay2_out1_reg[13]\(10),
      I3 => \^allow_assymetrical_anew_reference_value__0\,
      I4 => \Delay2_out1_reg[13]_0\(10),
      I5 => Saturation_out1(10),
      O => \Delay2_out1_reg[12]_1\(5)
    );
\Logical_Operator_out10_carry_i_10__0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"9990009000099909"
    )
        port map (
      I0 => \^u2_norm_1_reg[12]_0\(11),
      I1 => Saturation_out1(11),
      I2 => \Delay1_out1_reg[13]\(10),
      I3 => \^allow_assymetrical_anew_reference_value__0\,
      I4 => \Delay1_out1_reg[13]_0\(10),
      I5 => Saturation_out1(10),
      O => \Delay1_out1_reg[12]_1\(5)
    );
\Logical_Operator_out10_carry_i_10__1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"9009"
    )
        port map (
      I0 => HDL_Counter2_count_reg(5),
      I1 => \Logical_Operator_out10_carry__0_0\(12),
      I2 => HDL_Counter2_count_reg(6),
      I3 => \Logical_Operator_out10_carry__0_0\(13),
      O => \Logical_Operator_out10_carry_i_10__1_n_0\
    );
\Logical_Operator_out10_carry_i_10__2\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"0000A959"
    )
        port map (
      I0 => Saturation_out1(12),
      I1 => \Delay_out1_reg[13]\(12),
      I2 => \^allow_assymetrical_anew_reference_value__0\,
      I3 => \Delay_out1_reg[13]_0\(12),
      I4 => \^relational_operator_1_cast\(13),
      O => \Delay_out1_reg[12]_2\(0)
    );
Logical_Operator_out10_carry_i_11: unisim.vcomponents.LUT6
    generic map(
      INIT => X"9990009000099909"
    )
        port map (
      I0 => \^u3_norm_1_reg[12]_0\(9),
      I1 => Saturation_out1(9),
      I2 => \Delay2_out1_reg[13]\(8),
      I3 => \^allow_assymetrical_anew_reference_value__0\,
      I4 => \Delay2_out1_reg[13]_0\(8),
      I5 => Saturation_out1(8),
      O => \Delay2_out1_reg[12]_1\(4)
    );
\Logical_Operator_out10_carry_i_11__0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"9990009000099909"
    )
        port map (
      I0 => \^u2_norm_1_reg[12]_0\(9),
      I1 => Saturation_out1(9),
      I2 => \Delay1_out1_reg[13]\(8),
      I3 => \^allow_assymetrical_anew_reference_value__0\,
      I4 => \Delay1_out1_reg[13]_0\(8),
      I5 => Saturation_out1(8),
      O => \Delay1_out1_reg[12]_1\(4)
    );
\Logical_Operator_out10_carry_i_11__2\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"9009"
    )
        port map (
      I0 => HDL_Counter2_count_reg(3),
      I1 => \Logical_Operator_out10_carry__0_0\(10),
      I2 => HDL_Counter2_count_reg(4),
      I3 => \Logical_Operator_out10_carry__0_0\(11),
      O => \Logical_Operator_out10_carry_i_11__2_n_0\
    );
Logical_Operator_out10_carry_i_12: unisim.vcomponents.LUT6
    generic map(
      INIT => X"9990009000099909"
    )
        port map (
      I0 => \^u3_norm_1_reg[12]_0\(7),
      I1 => Saturation_out1(7),
      I2 => \Delay2_out1_reg[13]\(6),
      I3 => \^allow_assymetrical_anew_reference_value__0\,
      I4 => \Delay2_out1_reg[13]_0\(6),
      I5 => Saturation_out1(6),
      O => \Delay2_out1_reg[12]_1\(3)
    );
\Logical_Operator_out10_carry_i_12__0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"9990009000099909"
    )
        port map (
      I0 => \^u2_norm_1_reg[12]_0\(7),
      I1 => Saturation_out1(7),
      I2 => \Delay1_out1_reg[13]\(6),
      I3 => \^allow_assymetrical_anew_reference_value__0\,
      I4 => \Delay1_out1_reg[13]_0\(6),
      I5 => Saturation_out1(6),
      O => \Delay1_out1_reg[12]_1\(3)
    );
\Logical_Operator_out10_carry_i_12__2\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"9009"
    )
        port map (
      I0 => HDL_Counter2_count_reg(2),
      I1 => \Logical_Operator_out10_carry__0_0\(9),
      I2 => HDL_Counter2_count_reg(1),
      I3 => \Logical_Operator_out10_carry__0_0\(8),
      O => \Logical_Operator_out10_carry_i_12__2_n_0\
    );
Logical_Operator_out10_carry_i_13: unisim.vcomponents.LUT6
    generic map(
      INIT => X"9990009000099909"
    )
        port map (
      I0 => \^u3_norm_1_reg[12]_0\(5),
      I1 => Saturation_out1(5),
      I2 => \Delay2_out1_reg[13]\(4),
      I3 => \^allow_assymetrical_anew_reference_value__0\,
      I4 => \Delay2_out1_reg[13]_0\(4),
      I5 => Saturation_out1(4),
      O => \Delay2_out1_reg[12]_1\(2)
    );
\Logical_Operator_out10_carry_i_13__0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"9990009000099909"
    )
        port map (
      I0 => \^u2_norm_1_reg[12]_0\(5),
      I1 => Saturation_out1(5),
      I2 => \Delay1_out1_reg[13]\(4),
      I3 => \^allow_assymetrical_anew_reference_value__0\,
      I4 => \Delay1_out1_reg[13]_0\(4),
      I5 => Saturation_out1(4),
      O => \Delay1_out1_reg[12]_1\(2)
    );
\Logical_Operator_out10_carry_i_13__2\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"9009"
    )
        port map (
      I0 => \HDL_Counter2_count_reg[7]_1\,
      I1 => \Logical_Operator_out10_carry__0_0\(6),
      I2 => \HDL_Counter2_count_reg[7]_0\,
      I3 => \Logical_Operator_out10_carry__0_0\(7),
      O => \Logical_Operator_out10_carry_i_13__2_n_0\
    );
Logical_Operator_out10_carry_i_14: unisim.vcomponents.LUT6
    generic map(
      INIT => X"9990009000099909"
    )
        port map (
      I0 => \^u3_norm_1_reg[12]_0\(3),
      I1 => Saturation_out1(3),
      I2 => \Delay2_out1_reg[13]\(2),
      I3 => \^allow_assymetrical_anew_reference_value__0\,
      I4 => \Delay2_out1_reg[13]_0\(2),
      I5 => Saturation_out1(2),
      O => \Delay2_out1_reg[12]_1\(1)
    );
\Logical_Operator_out10_carry_i_14__0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"9990009000099909"
    )
        port map (
      I0 => \^u2_norm_1_reg[12]_0\(3),
      I1 => Saturation_out1(3),
      I2 => \Delay1_out1_reg[13]\(2),
      I3 => \^allow_assymetrical_anew_reference_value__0\,
      I4 => \Delay1_out1_reg[13]_0\(2),
      I5 => Saturation_out1(2),
      O => \Delay1_out1_reg[12]_1\(1)
    );
\Logical_Operator_out10_carry_i_14__2\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"9009"
    )
        port map (
      I0 => \HDL_Counter2_count_reg[7]_3\,
      I1 => \Logical_Operator_out10_carry__0_0\(4),
      I2 => \HDL_Counter2_count_reg[7]_2\,
      I3 => \Logical_Operator_out10_carry__0_0\(5),
      O => \Logical_Operator_out10_carry_i_14__2_n_0\
    );
Logical_Operator_out10_carry_i_15: unisim.vcomponents.LUT6
    generic map(
      INIT => X"9990009000099909"
    )
        port map (
      I0 => \^u3_norm_1_reg[12]_0\(1),
      I1 => Saturation_out1(1),
      I2 => \Delay2_out1_reg[13]\(0),
      I3 => \^allow_assymetrical_anew_reference_value__0\,
      I4 => \Delay2_out1_reg[13]_0\(0),
      I5 => Saturation_out1(0),
      O => \Delay2_out1_reg[12]_1\(0)
    );
\Logical_Operator_out10_carry_i_15__0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"9990009000099909"
    )
        port map (
      I0 => \^u2_norm_1_reg[12]_0\(1),
      I1 => Saturation_out1(1),
      I2 => \Delay1_out1_reg[13]\(0),
      I3 => \^allow_assymetrical_anew_reference_value__0\,
      I4 => \Delay1_out1_reg[13]_0\(0),
      I5 => Saturation_out1(0),
      O => \Delay1_out1_reg[12]_1\(0)
    );
\Logical_Operator_out10_carry_i_15__2\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"9009"
    )
        port map (
      I0 => Delay6_out1_reg_1,
      I1 => \Logical_Operator_out10_carry__0_0\(3),
      I2 => Delay6_out1_reg_0,
      I3 => \Logical_Operator_out10_carry__0_0\(2),
      O => \Logical_Operator_out10_carry_i_15__2_n_0\
    );
\Logical_Operator_out10_carry_i_16__0\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"9009"
    )
        port map (
      I0 => HDL_Counter2_count_reg_7_sn_1,
      I1 => \Logical_Operator_out10_carry__0_0\(0),
      I2 => HDL_Counter2_count_reg(0),
      I3 => \Logical_Operator_out10_carry__0_0\(1),
      O => \Logical_Operator_out10_carry_i_16__0_n_0\
    );
Logical_Operator_out10_carry_i_19: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFFF4000"
    )
        port map (
      I0 => HDL_Counter2_count_reg(12),
      I1 => Switch7_out12_carry_i_6,
      I2 => Switch7_out12_carry_i_6_0,
      I3 => Switch7_out12_carry_i_6_1,
      I4 => \^co\(0),
      O => \^allow_assymetrical_anew_reference_value__0\
    );
\Logical_Operator_out10_carry_i_1__0\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"AAAEEEAE"
    )
        port map (
      I0 => \^u3_norm_1_reg[13]\,
      I1 => Saturation_out1(12),
      I2 => \Delay2_out1_reg[13]\(12),
      I3 => \^allow_assymetrical_anew_reference_value__0\,
      I4 => \Delay2_out1_reg[13]_0\(12),
      O => \Delay2_out1_reg[12]_2\(0)
    );
\Logical_Operator_out10_carry_i_1__1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"AAAEEEAE"
    )
        port map (
      I0 => \^u2_norm_1_reg[13]\,
      I1 => Saturation_out1(12),
      I2 => \Delay1_out1_reg[13]\(12),
      I3 => \^allow_assymetrical_anew_reference_value__0\,
      I4 => \Delay1_out1_reg[13]_0\(12),
      O => \Delay1_out1_reg[12]_2\(0)
    );
\Logical_Operator_out10_carry_i_2__1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"22B2"
    )
        port map (
      I0 => HDL_Counter2_count_reg(6),
      I1 => \Logical_Operator_out10_carry__0_0\(13),
      I2 => HDL_Counter2_count_reg(5),
      I3 => \Logical_Operator_out10_carry__0_0\(12),
      O => \Logical_Operator_out10_carry_i_2__1_n_0\
    );
\Logical_Operator_out10_carry_i_2__2\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"AAAEEEAE"
    )
        port map (
      I0 => \^relational_operator_1_cast\(13),
      I1 => Saturation_out1(12),
      I2 => \Delay_out1_reg[13]\(12),
      I3 => \^allow_assymetrical_anew_reference_value__0\,
      I4 => \Delay_out1_reg[13]_0\(12),
      O => \Delay_out1_reg[12]_1\(0)
    );
\Logical_Operator_out10_carry_i_3__2\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"22B2"
    )
        port map (
      I0 => HDL_Counter2_count_reg(4),
      I1 => \Logical_Operator_out10_carry__0_0\(11),
      I2 => HDL_Counter2_count_reg(3),
      I3 => \Logical_Operator_out10_carry__0_0\(10),
      O => \Logical_Operator_out10_carry_i_3__2_n_0\
    );
\Logical_Operator_out10_carry_i_4__2\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"22B2"
    )
        port map (
      I0 => HDL_Counter2_count_reg(2),
      I1 => \Logical_Operator_out10_carry__0_0\(9),
      I2 => HDL_Counter2_count_reg(1),
      I3 => \Logical_Operator_out10_carry__0_0\(8),
      O => \Logical_Operator_out10_carry_i_4__2_n_0\
    );
\Logical_Operator_out10_carry_i_5__2\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"22B2"
    )
        port map (
      I0 => \HDL_Counter2_count_reg[7]_0\,
      I1 => \Logical_Operator_out10_carry__0_0\(7),
      I2 => \HDL_Counter2_count_reg[7]_1\,
      I3 => \Logical_Operator_out10_carry__0_0\(6),
      O => \Logical_Operator_out10_carry_i_5__2_n_0\
    );
\Logical_Operator_out10_carry_i_6__2\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"22B2"
    )
        port map (
      I0 => \HDL_Counter2_count_reg[7]_2\,
      I1 => \Logical_Operator_out10_carry__0_0\(5),
      I2 => \HDL_Counter2_count_reg[7]_3\,
      I3 => \Logical_Operator_out10_carry__0_0\(4),
      O => \Logical_Operator_out10_carry_i_6__2_n_0\
    );
\Logical_Operator_out10_carry_i_7__2\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"22B2"
    )
        port map (
      I0 => Delay6_out1_reg_1,
      I1 => \Logical_Operator_out10_carry__0_0\(3),
      I2 => Delay6_out1_reg_0,
      I3 => \Logical_Operator_out10_carry__0_0\(2),
      O => \Logical_Operator_out10_carry_i_7__2_n_0\
    );
\Logical_Operator_out10_carry_i_8__0\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"22B2"
    )
        port map (
      I0 => HDL_Counter2_count_reg(0),
      I1 => \Logical_Operator_out10_carry__0_0\(1),
      I2 => HDL_Counter2_count_reg_7_sn_1,
      I3 => \Logical_Operator_out10_carry__0_0\(0),
      O => \Logical_Operator_out10_carry_i_8__0_n_0\
    );
Logical_Operator_out10_carry_i_9: unisim.vcomponents.LUT4
    generic map(
      INIT => X"9009"
    )
        port map (
      I0 => HDL_Counter2_count_reg(8),
      I1 => \Logical_Operator_out10_carry__0_0\(15),
      I2 => HDL_Counter2_count_reg(7),
      I3 => \Logical_Operator_out10_carry__0_0\(14),
      O => Logical_Operator_out10_carry_i_9_n_0
    );
\Logical_Operator_out10_carry_i_9__0\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"54040151"
    )
        port map (
      I0 => \^u3_norm_1_reg[13]\,
      I1 => \Delay2_out1_reg[13]\(12),
      I2 => \^allow_assymetrical_anew_reference_value__0\,
      I3 => \Delay2_out1_reg[13]_0\(12),
      I4 => Saturation_out1(12),
      O => \Delay2_out1_reg[12]_1\(6)
    );
\Logical_Operator_out10_carry_i_9__1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"54040151"
    )
        port map (
      I0 => \^u2_norm_1_reg[13]\,
      I1 => \Delay1_out1_reg[13]\(12),
      I2 => \^allow_assymetrical_anew_reference_value__0\,
      I3 => \Delay1_out1_reg[13]_0\(12),
      I4 => Saturation_out1(12),
      O => \Delay1_out1_reg[12]_1\(6)
    );
Period_CenterMax0_carry: unisim.vcomponents.CARRY8
     port map (
      CI => '1',
      CI_TOP => '0',
      CO(7) => Period_CenterMax0_carry_n_0,
      CO(6) => Period_CenterMax0_carry_n_1,
      CO(5) => Period_CenterMax0_carry_n_2,
      CO(4) => Period_CenterMax0_carry_n_3,
      CO(3) => Period_CenterMax0_carry_n_4,
      CO(2) => Period_CenterMax0_carry_n_5,
      CO(1) => Period_CenterMax0_carry_n_6,
      CO(0) => Period_CenterMax0_carry_n_7,
      DI(7 downto 0) => B"00000000",
      O(7 downto 0) => NLW_Period_CenterMax0_carry_O_UNCONNECTED(7 downto 0),
      S(7) => Period_CenterMax0_carry_i_1_n_0,
      S(6) => Period_CenterMax0_carry_i_2_n_0,
      S(5) => Period_CenterMax0_carry_i_3_n_0,
      S(4) => Period_CenterMax0_carry_i_4_n_0,
      S(3) => Period_CenterMax0_carry_i_5_n_0,
      S(2) => Period_CenterMax0_carry_i_6_n_0,
      S(1) => Period_CenterMax0_carry_i_7_n_0,
      S(0) => Period_CenterMax0_carry_i_8_n_0
    );
\Period_CenterMax0_carry__0\: unisim.vcomponents.CARRY8
     port map (
      CI => Period_CenterMax0_carry_n_0,
      CI_TOP => '0',
      CO(7 downto 1) => \NLW_Period_CenterMax0_carry__0_CO_UNCONNECTED\(7 downto 1),
      CO(0) => \^co\(0),
      DI(7 downto 0) => B"00000000",
      O(7 downto 0) => \NLW_Period_CenterMax0_carry__0_O_UNCONNECTED\(7 downto 0),
      S(7 downto 1) => B"0000000",
      S(0) => S(0)
    );
Period_CenterMax0_carry_i_1: unisim.vcomponents.LUT3
    generic map(
      INIT => X"01"
    )
        port map (
      I0 => \Logical_Operator_out10_carry__0_0\(23),
      I1 => \Logical_Operator_out10_carry__0_0\(22),
      I2 => \Logical_Operator_out10_carry__0_0\(21),
      O => Period_CenterMax0_carry_i_1_n_0
    );
Period_CenterMax0_carry_i_2: unisim.vcomponents.LUT5
    generic map(
      INIT => X"41000041"
    )
        port map (
      I0 => \Logical_Operator_out10_carry__0_0\(20),
      I1 => \Logical_Operator_out10_carry__0_0\(19),
      I2 => HDL_Counter2_count_reg(12),
      I3 => HDL_Counter2_count_reg(11),
      I4 => \Logical_Operator_out10_carry__0_0\(18),
      O => Period_CenterMax0_carry_i_2_n_0
    );
Period_CenterMax0_carry_i_3: unisim.vcomponents.LUT6
    generic map(
      INIT => X"9009000000009009"
    )
        port map (
      I0 => \Logical_Operator_out10_carry__0_0\(17),
      I1 => HDL_Counter2_count_reg(10),
      I2 => \Logical_Operator_out10_carry__0_0\(16),
      I3 => HDL_Counter2_count_reg(9),
      I4 => HDL_Counter2_count_reg(8),
      I5 => \Logical_Operator_out10_carry__0_0\(15),
      O => Period_CenterMax0_carry_i_3_n_0
    );
Period_CenterMax0_carry_i_4: unisim.vcomponents.LUT6
    generic map(
      INIT => X"9009000000009009"
    )
        port map (
      I0 => \Logical_Operator_out10_carry__0_0\(13),
      I1 => HDL_Counter2_count_reg(6),
      I2 => \Logical_Operator_out10_carry__0_0\(14),
      I3 => HDL_Counter2_count_reg(7),
      I4 => HDL_Counter2_count_reg(5),
      I5 => \Logical_Operator_out10_carry__0_0\(12),
      O => Period_CenterMax0_carry_i_4_n_0
    );
Period_CenterMax0_carry_i_5: unisim.vcomponents.LUT6
    generic map(
      INIT => X"9009000000009009"
    )
        port map (
      I0 => \Logical_Operator_out10_carry__0_0\(11),
      I1 => HDL_Counter2_count_reg(4),
      I2 => \Logical_Operator_out10_carry__0_0\(10),
      I3 => HDL_Counter2_count_reg(3),
      I4 => HDL_Counter2_count_reg(2),
      I5 => \Logical_Operator_out10_carry__0_0\(9),
      O => Period_CenterMax0_carry_i_5_n_0
    );
Period_CenterMax0_carry_i_6: unisim.vcomponents.LUT6
    generic map(
      INIT => X"9009000000009009"
    )
        port map (
      I0 => \Logical_Operator_out10_carry__0_0\(7),
      I1 => \HDL_Counter2_count_reg[7]_0\,
      I2 => \Logical_Operator_out10_carry__0_0\(8),
      I3 => HDL_Counter2_count_reg(1),
      I4 => \HDL_Counter2_count_reg[7]_1\,
      I5 => \Logical_Operator_out10_carry__0_0\(6),
      O => Period_CenterMax0_carry_i_6_n_0
    );
Period_CenterMax0_carry_i_7: unisim.vcomponents.LUT6
    generic map(
      INIT => X"9009000000009009"
    )
        port map (
      I0 => \Logical_Operator_out10_carry__0_0\(5),
      I1 => \HDL_Counter2_count_reg[7]_2\,
      I2 => \Logical_Operator_out10_carry__0_0\(4),
      I3 => \HDL_Counter2_count_reg[7]_3\,
      I4 => Delay6_out1_reg_1,
      I5 => \Logical_Operator_out10_carry__0_0\(3),
      O => Period_CenterMax0_carry_i_7_n_0
    );
Period_CenterMax0_carry_i_8: unisim.vcomponents.LUT6
    generic map(
      INIT => X"9009000000009009"
    )
        port map (
      I0 => \Logical_Operator_out10_carry__0_0\(1),
      I1 => HDL_Counter2_count_reg(0),
      I2 => \Logical_Operator_out10_carry__0_0\(2),
      I3 => Delay6_out1_reg_0,
      I4 => HDL_Counter2_count_reg_7_sn_1,
      I5 => \Logical_Operator_out10_carry__0_0\(0),
      O => Period_CenterMax0_carry_i_8_n_0
    );
Product_mul_temp: unisim.vcomponents.DSP48E2
    generic map(
      ACASCREG => 2,
      ADREG => 1,
      ALUMODEREG => 0,
      AMULTSEL => "A",
      AREG => 2,
      AUTORESET_PATDET => "NO_RESET",
      AUTORESET_PRIORITY => "RESET",
      A_INPUT => "DIRECT",
      BCASCREG => 1,
      BMULTSEL => "B",
      BREG => 1,
      B_INPUT => "DIRECT",
      CARRYINREG => 0,
      CARRYINSELREG => 0,
      CREG => 1,
      DREG => 1,
      INMODEREG => 0,
      MASK => X"3FFFFFFFFFFF",
      MREG => 0,
      OPMODEREG => 0,
      PATTERN => X"000000000000",
      PREADDINSEL => "A",
      PREG => 0,
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
      A(29 downto 25) => B"00000",
      A(24 downto 0) => D(24 downto 0),
      ACIN(29 downto 0) => B"000000000000000000000000000000",
      ACOUT(29 downto 0) => NLW_Product_mul_temp_ACOUT_UNCONNECTED(29 downto 0),
      ALUMODE(3 downto 0) => B"0000",
      B(17) => '0',
      B(16 downto 1) => B(15 downto 0),
      B(0) => HDL_Counter2_count_next(0),
      BCIN(17 downto 0) => B"000000000000000000",
      BCOUT(17 downto 0) => NLW_Product_mul_temp_BCOUT_UNCONNECTED(17 downto 0),
      C(47 downto 0) => B"000000000000000000000000000000000000000000000000",
      CARRYCASCIN => '0',
      CARRYCASCOUT => NLW_Product_mul_temp_CARRYCASCOUT_UNCONNECTED,
      CARRYIN => '0',
      CARRYINSEL(2 downto 0) => B"000",
      CARRYOUT(3 downto 0) => NLW_Product_mul_temp_CARRYOUT_UNCONNECTED(3 downto 0),
      CEA1 => E(0),
      CEA2 => E(0),
      CEAD => '0',
      CEALUMODE => '0',
      CEB1 => '0',
      CEB2 => CEB2,
      CEC => '0',
      CECARRYIN => '0',
      CECTRL => '0',
      CED => '0',
      CEINMODE => '0',
      CEM => '0',
      CEP => '0',
      CLK => IPCORE_CLK,
      D(26 downto 0) => B"000000000000000000000000000",
      INMODE(4 downto 0) => B"00000",
      MULTSIGNIN => '0',
      MULTSIGNOUT => NLW_Product_mul_temp_MULTSIGNOUT_UNCONNECTED,
      OPMODE(8 downto 0) => B"000000101",
      OVERFLOW => NLW_Product_mul_temp_OVERFLOW_UNCONNECTED,
      P(47) => Product_mul_temp_n_58,
      P(46) => Product_mul_temp_n_59,
      P(45) => Product_mul_temp_n_60,
      P(44) => Product_mul_temp_n_61,
      P(43) => Product_mul_temp_n_62,
      P(42) => Product_mul_temp_n_63,
      P(41) => Product_mul_temp_n_64,
      P(40) => Product_mul_temp_n_65,
      P(39) => Product_mul_temp_n_66,
      P(38) => Product_mul_temp_n_67,
      P(37) => Product_mul_temp_n_68,
      P(36) => Product_mul_temp_n_69,
      P(35) => Product_mul_temp_n_70,
      P(34) => Product_mul_temp_n_71,
      P(33) => Product_mul_temp_n_72,
      P(32) => Product_mul_temp_n_73,
      P(31) => Product_mul_temp_n_74,
      P(30) => Product_mul_temp_n_75,
      P(29) => Product_mul_temp_n_76,
      P(28) => Product_mul_temp_n_77,
      P(27) => Product_mul_temp_n_78,
      P(26) => Product_mul_temp_n_79,
      P(25) => Product_mul_temp_n_80,
      P(24) => Product_mul_temp_n_81,
      P(23) => Product_mul_temp_n_82,
      P(22) => Product_mul_temp_n_83,
      P(21) => Product_mul_temp_n_84,
      P(20) => Product_mul_temp_n_85,
      P(19) => Product_mul_temp_n_86,
      P(18) => Product_mul_temp_n_87,
      P(17) => Product_mul_temp_n_88,
      P(16) => Product_mul_temp_n_89,
      P(15) => Product_mul_temp_n_90,
      P(14 downto 9) => \^p\(5 downto 0),
      P(8) => Product_mul_temp_n_97,
      P(7) => Product_mul_temp_n_98,
      P(6) => Product_mul_temp_n_99,
      P(5) => Product_mul_temp_n_100,
      P(4) => Product_mul_temp_n_101,
      P(3) => Product_mul_temp_n_102,
      P(2) => Product_mul_temp_n_103,
      P(1) => Product_mul_temp_n_104,
      P(0) => Product_mul_temp_n_105,
      PATTERNBDETECT => NLW_Product_mul_temp_PATTERNBDETECT_UNCONNECTED,
      PATTERNDETECT => NLW_Product_mul_temp_PATTERNDETECT_UNCONNECTED,
      PCIN(47 downto 0) => B"000000000000000000000000000000000000000000000000",
      PCOUT(47 downto 0) => NLW_Product_mul_temp_PCOUT_UNCONNECTED(47 downto 0),
      RSTA => reset,
      RSTALLCARRYIN => '0',
      RSTALUMODE => '0',
      RSTB => reset,
      RSTC => '0',
      RSTCTRL => '0',
      RSTD => '0',
      RSTINMODE => '0',
      RSTM => '0',
      RSTP => '0',
      UNDERFLOW => NLW_Product_mul_temp_UNDERFLOW_UNCONNECTED,
      XOROUT(7 downto 0) => NLW_Product_mul_temp_XOROUT_UNCONNECTED(7 downto 0)
    );
\Product_mul_temp[-1111111102]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => Q(9),
      Q => \^product_mul_temp[-1111111102]_0\(0),
      R => reset
    );
\Product_mul_temp[-1111111103]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => Q(8),
      Q => \^product_mul_temp[-1111111103]_0\,
      R => reset
    );
\Product_mul_temp[-1111111104]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => Q(7),
      Q => \^product_mul_temp[-1111111104]_0\,
      R => reset
    );
\Product_mul_temp[-1111111105]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => Q(6),
      Q => \^product_mul_temp[-1111111105]_0\,
      R => reset
    );
\Product_mul_temp[-1111111106]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => Q(5),
      Q => \^product_mul_temp[-1111111106]_0\,
      R => reset
    );
\Product_mul_temp[-1111111107]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => Q(4),
      Q => \^product_mul_temp[-1111111107]_0\,
      R => reset
    );
\Product_mul_temp[-1111111108]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => Q(3),
      Q => \^product_mul_temp[-1111111108]_0\,
      R => reset
    );
\Product_mul_temp[-1111111109]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => Q(2),
      Q => \^product_mul_temp[-1111111109]_0\,
      R => reset
    );
\Product_mul_temp[-1111111110]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => Q(1),
      Q => \^product_mul_temp[-1111111110]_0\,
      R => reset
    );
\Product_mul_temp[-1111111111]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => Q(0),
      Q => \^product_mul_temp[-1111111111]_0\,
      R => reset
    );
\Product_mul_temp__0_carry\: unisim.vcomponents.CARRY8
     port map (
      CI => '0',
      CI_TOP => '0',
      CO(7) => \Product_mul_temp__0_carry_n_0\,
      CO(6) => \Product_mul_temp__0_carry_n_1\,
      CO(5) => \Product_mul_temp__0_carry_n_2\,
      CO(4) => \Product_mul_temp__0_carry_n_3\,
      CO(3) => \Product_mul_temp__0_carry_n_4\,
      CO(2) => \Product_mul_temp__0_carry_n_5\,
      CO(1) => \Product_mul_temp__0_carry_n_6\,
      CO(0) => \Product_mul_temp__0_carry_n_7\,
      DI(7) => \Product_mul_temp__0_carry_i_1_n_0\,
      DI(6) => \Product_mul_temp__0_carry_i_2_n_0\,
      DI(5) => \Product_mul_temp__0_carry_i_3_n_0\,
      DI(4) => \Product_mul_temp__0_carry_i_4_n_0\,
      DI(3) => \Product_mul_temp__0_carry_i_5_n_0\,
      DI(2) => \Product_mul_temp__0_carry_i_6_n_0\,
      DI(1) => \Product_mul_temp__0_carry_i_7_n_0\,
      DI(0) => '0',
      O(7 downto 0) => \Product_mul_temp__0\(7 downto 0),
      S(7) => \Product_mul_temp__0_carry_i_8_n_0\,
      S(6) => \Product_mul_temp__0_carry_i_9_n_0\,
      S(5) => \Product_mul_temp__0_carry_i_10_n_0\,
      S(4) => \Product_mul_temp__0_carry_i_11_n_0\,
      S(3) => \Product_mul_temp__0_carry_i_12_n_0\,
      S(2) => \Product_mul_temp__0_carry_i_13_n_0\,
      S(1) => \Product_mul_temp__0_carry_i_14_n_0\,
      S(0) => \Product_mul_temp__0_carry_i_15_n_0\
    );
\Product_mul_temp__0_carry__0\: unisim.vcomponents.CARRY8
     port map (
      CI => \Product_mul_temp__0_carry_n_0\,
      CI_TOP => '0',
      CO(7 downto 1) => \NLW_Product_mul_temp__0_carry__0_CO_UNCONNECTED\(7 downto 1),
      CO(0) => \Product_mul_temp__0_carry__0_n_7\,
      DI(7 downto 1) => B"0000000",
      DI(0) => \Product_mul_temp__0_carry__0_i_1_n_0\,
      O(7 downto 2) => \NLW_Product_mul_temp__0_carry__0_O_UNCONNECTED\(7 downto 2),
      O(1) => \Product_mul_temp__0_carry__0_n_14\,
      O(0) => \Product_mul_temp__0\(8),
      S(7 downto 2) => B"000000",
      S(1) => \Product_mul_temp__0_carry__0_i_2_n_0\,
      S(0) => \Product_mul_temp__0_carry__0_i_3_n_0\
    );
\Product_mul_temp__0_carry__0_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"F888800080008000"
    )
        port map (
      I0 => HDL_Counter2_count_reg(11),
      I1 => \^product_mul_temp[-1111111105]_0\,
      I2 => \^product_mul_temp[-1111111104]_0\,
      I3 => HDL_Counter2_count_reg(10),
      I4 => \^product_mul_temp[-1111111106]_0\,
      I5 => HDL_Counter2_count_reg(12),
      O => \Product_mul_temp__0_carry__0_i_1_n_0\
    );
\Product_mul_temp__0_carry__0_i_2\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"6A95"
    )
        port map (
      I0 => \Product_mul_temp__0_carry__0_i_4_n_0\,
      I1 => \^product_mul_temp[-1111111102]_0\(0),
      I2 => HDL_Counter2_count_reg(10),
      I3 => \Product_mul_temp__0_carry__0_i_5_n_0\,
      O => \Product_mul_temp__0_carry__0_i_2_n_0\
    );
\Product_mul_temp__0_carry__0_i_3\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"956A6A956A956A95"
    )
        port map (
      I0 => \Product_mul_temp__0_carry__0_i_1_n_0\,
      I1 => HDL_Counter2_count_reg(11),
      I2 => \^product_mul_temp[-1111111104]_0\,
      I3 => \Product_mul_temp__0_carry__0_i_6_n_0\,
      I4 => \^product_mul_temp[-1111111103]_0\,
      I5 => HDL_Counter2_count_reg(10),
      O => \Product_mul_temp__0_carry__0_i_3_n_0\
    );
\Product_mul_temp__0_carry__0_i_4\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"7888"
    )
        port map (
      I0 => HDL_Counter2_count_reg(12),
      I1 => \^product_mul_temp[-1111111104]_0\,
      I2 => HDL_Counter2_count_reg(11),
      I3 => \^product_mul_temp[-1111111103]_0\,
      O => \Product_mul_temp__0_carry__0_i_4_n_0\
    );
\Product_mul_temp__0_carry__0_i_5\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"F888800080008000"
    )
        port map (
      I0 => HDL_Counter2_count_reg(11),
      I1 => \^product_mul_temp[-1111111104]_0\,
      I2 => \^product_mul_temp[-1111111105]_0\,
      I3 => HDL_Counter2_count_reg(12),
      I4 => \^product_mul_temp[-1111111103]_0\,
      I5 => HDL_Counter2_count_reg(10),
      O => \Product_mul_temp__0_carry__0_i_5_n_0\
    );
\Product_mul_temp__0_carry__0_i_6\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"7"
    )
        port map (
      I0 => \^product_mul_temp[-1111111105]_0\,
      I1 => HDL_Counter2_count_reg(12),
      O => \Product_mul_temp__0_carry__0_i_6_n_0\
    );
\Product_mul_temp__0_carry_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"F880808088000000"
    )
        port map (
      I0 => HDL_Counter2_count_reg(11),
      I1 => \^product_mul_temp[-1111111106]_0\,
      I2 => \^product_mul_temp[-1111111105]_0\,
      I3 => HDL_Counter2_count_reg(12),
      I4 => \^product_mul_temp[-1111111107]_0\,
      I5 => HDL_Counter2_count_reg(10),
      O => \Product_mul_temp__0_carry_i_1_n_0\
    );
\Product_mul_temp__0_carry_i_10\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"956A6A956A956A95"
    )
        port map (
      I0 => \Product_mul_temp__0_carry_i_3_n_0\,
      I1 => HDL_Counter2_count_reg(11),
      I2 => \^product_mul_temp[-1111111107]_0\,
      I3 => \Product_mul_temp__0_carry_i_18_n_0\,
      I4 => \^product_mul_temp[-1111111106]_0\,
      I5 => HDL_Counter2_count_reg(10),
      O => \Product_mul_temp__0_carry_i_10_n_0\
    );
\Product_mul_temp__0_carry_i_11\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"956A6A6A6A959595"
    )
        port map (
      I0 => \Product_mul_temp__0_carry_i_4_n_0\,
      I1 => HDL_Counter2_count_reg(11),
      I2 => \^product_mul_temp[-1111111108]_0\,
      I3 => HDL_Counter2_count_reg(12),
      I4 => \^product_mul_temp[-1111111109]_0\,
      I5 => \Product_mul_temp__0_carry_i_19_n_0\,
      O => \Product_mul_temp__0_carry_i_11_n_0\
    );
\Product_mul_temp__0_carry_i_12\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"6A6A6A95C03FC03F"
    )
        port map (
      I0 => \^product_mul_temp[-1111111109]_0\,
      I1 => \^product_mul_temp[-1111111108]_0\,
      I2 => HDL_Counter2_count_reg(10),
      I3 => \Product_mul_temp__0_carry_i_20_n_0\,
      I4 => \^product_mul_temp[-1111111111]_0\,
      I5 => HDL_Counter2_count_reg(11),
      O => \Product_mul_temp__0_carry_i_12_n_0\
    );
\Product_mul_temp__0_carry_i_13\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"8777788878887888"
    )
        port map (
      I0 => \^product_mul_temp[-1111111111]_0\,
      I1 => HDL_Counter2_count_reg(12),
      I2 => \^product_mul_temp[-1111111110]_0\,
      I3 => HDL_Counter2_count_reg(11),
      I4 => HDL_Counter2_count_reg(10),
      I5 => \^product_mul_temp[-1111111109]_0\,
      O => \Product_mul_temp__0_carry_i_13_n_0\
    );
\Product_mul_temp__0_carry_i_14\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"7888"
    )
        port map (
      I0 => HDL_Counter2_count_reg(10),
      I1 => \^product_mul_temp[-1111111110]_0\,
      I2 => HDL_Counter2_count_reg(11),
      I3 => \^product_mul_temp[-1111111111]_0\,
      O => \Product_mul_temp__0_carry_i_14_n_0\
    );
\Product_mul_temp__0_carry_i_15\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"8"
    )
        port map (
      I0 => \^product_mul_temp[-1111111111]_0\,
      I1 => HDL_Counter2_count_reg(10),
      O => \Product_mul_temp__0_carry_i_15_n_0\
    );
\Product_mul_temp__0_carry_i_16\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"7"
    )
        port map (
      I0 => \^product_mul_temp[-1111111104]_0\,
      I1 => HDL_Counter2_count_reg(10),
      O => \Product_mul_temp__0_carry_i_16_n_0\
    );
\Product_mul_temp__0_carry_i_17\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"7"
    )
        port map (
      I0 => \^product_mul_temp[-1111111106]_0\,
      I1 => HDL_Counter2_count_reg(11),
      O => \Product_mul_temp__0_carry_i_17_n_0\
    );
\Product_mul_temp__0_carry_i_18\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"7"
    )
        port map (
      I0 => \^product_mul_temp[-1111111108]_0\,
      I1 => HDL_Counter2_count_reg(12),
      O => \Product_mul_temp__0_carry_i_18_n_0\
    );
\Product_mul_temp__0_carry_i_19\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"7"
    )
        port map (
      I0 => \^product_mul_temp[-1111111107]_0\,
      I1 => HDL_Counter2_count_reg(10),
      O => \Product_mul_temp__0_carry_i_19_n_0\
    );
\Product_mul_temp__0_carry_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"F888800080008000"
    )
        port map (
      I0 => \^product_mul_temp[-1111111107]_0\,
      I1 => HDL_Counter2_count_reg(11),
      I2 => \^product_mul_temp[-1111111108]_0\,
      I3 => HDL_Counter2_count_reg(12),
      I4 => \^product_mul_temp[-1111111106]_0\,
      I5 => HDL_Counter2_count_reg(10),
      O => \Product_mul_temp__0_carry_i_2_n_0\
    );
\Product_mul_temp__0_carry_i_20\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"7"
    )
        port map (
      I0 => \^product_mul_temp[-1111111110]_0\,
      I1 => HDL_Counter2_count_reg(12),
      O => \Product_mul_temp__0_carry_i_20_n_0\
    );
\Product_mul_temp__0_carry_i_3\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"F888800080008000"
    )
        port map (
      I0 => HDL_Counter2_count_reg(11),
      I1 => \^product_mul_temp[-1111111108]_0\,
      I2 => \^product_mul_temp[-1111111107]_0\,
      I3 => HDL_Counter2_count_reg(10),
      I4 => \^product_mul_temp[-1111111109]_0\,
      I5 => HDL_Counter2_count_reg(12),
      O => \Product_mul_temp__0_carry_i_3_n_0\
    );
\Product_mul_temp__0_carry_i_4\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"F880808088000000"
    )
        port map (
      I0 => HDL_Counter2_count_reg(11),
      I1 => \^product_mul_temp[-1111111109]_0\,
      I2 => \^product_mul_temp[-1111111108]_0\,
      I3 => HDL_Counter2_count_reg(12),
      I4 => \^product_mul_temp[-1111111110]_0\,
      I5 => HDL_Counter2_count_reg(10),
      O => \Product_mul_temp__0_carry_i_4_n_0\
    );
\Product_mul_temp__0_carry_i_5\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"8777788878887888"
    )
        port map (
      I0 => HDL_Counter2_count_reg(10),
      I1 => \^product_mul_temp[-1111111108]_0\,
      I2 => \^product_mul_temp[-1111111109]_0\,
      I3 => HDL_Counter2_count_reg(11),
      I4 => \^product_mul_temp[-1111111110]_0\,
      I5 => HDL_Counter2_count_reg(12),
      O => \Product_mul_temp__0_carry_i_5_n_0\
    );
\Product_mul_temp__0_carry_i_6\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"7888"
    )
        port map (
      I0 => HDL_Counter2_count_reg(11),
      I1 => \^product_mul_temp[-1111111110]_0\,
      I2 => HDL_Counter2_count_reg(12),
      I3 => \^product_mul_temp[-1111111111]_0\,
      O => \Product_mul_temp__0_carry_i_6_n_0\
    );
\Product_mul_temp__0_carry_i_7\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"8"
    )
        port map (
      I0 => \^product_mul_temp[-1111111110]_0\,
      I1 => HDL_Counter2_count_reg(10),
      O => \Product_mul_temp__0_carry_i_7_n_0\
    );
\Product_mul_temp__0_carry_i_8\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"956A6A6A6A959595"
    )
        port map (
      I0 => \Product_mul_temp__0_carry_i_1_n_0\,
      I1 => HDL_Counter2_count_reg(11),
      I2 => \^product_mul_temp[-1111111105]_0\,
      I3 => HDL_Counter2_count_reg(12),
      I4 => \^product_mul_temp[-1111111106]_0\,
      I5 => \Product_mul_temp__0_carry_i_16_n_0\,
      O => \Product_mul_temp__0_carry_i_8_n_0\
    );
\Product_mul_temp__0_carry_i_9\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"956A6A956A956A95"
    )
        port map (
      I0 => \Product_mul_temp__0_carry_i_2_n_0\,
      I1 => HDL_Counter2_count_reg(12),
      I2 => \^product_mul_temp[-1111111107]_0\,
      I3 => \Product_mul_temp__0_carry_i_17_n_0\,
      I4 => \^product_mul_temp[-1111111105]_0\,
      I5 => HDL_Counter2_count_reg(10),
      O => \Product_mul_temp__0_carry_i_9_n_0\
    );
Product_mul_temp_i_2: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => HDL_Counter2_count_reg_7_sn_1,
      O => HDL_Counter2_count_next(0)
    );
\Product_mul_temp_inferred__0/i__carry\: unisim.vcomponents.CARRY8
     port map (
      CI => '0',
      CI_TOP => '0',
      CO(7) => \Product_mul_temp_inferred__0/i__carry_n_0\,
      CO(6) => \Product_mul_temp_inferred__0/i__carry_n_1\,
      CO(5) => \Product_mul_temp_inferred__0/i__carry_n_2\,
      CO(4) => \Product_mul_temp_inferred__0/i__carry_n_3\,
      CO(3) => \Product_mul_temp_inferred__0/i__carry_n_4\,
      CO(2) => \Product_mul_temp_inferred__0/i__carry_n_5\,
      CO(1) => \Product_mul_temp_inferred__0/i__carry_n_6\,
      CO(0) => \Product_mul_temp_inferred__0/i__carry_n_7\,
      DI(7) => Product_mul_temp_n_81,
      DI(6) => Product_mul_temp_n_82,
      DI(5) => Product_mul_temp_n_83,
      DI(4) => Product_mul_temp_n_84,
      DI(3) => Product_mul_temp_n_85,
      DI(2) => Product_mul_temp_n_86,
      DI(1) => Product_mul_temp_n_87,
      DI(0) => Product_mul_temp_n_88,
      O(7 downto 0) => Product_mul_temp0_out(7 downto 0),
      S(7) => \i__carry_i_1__3_n_0\,
      S(6) => \i__carry_i_2__3_n_0\,
      S(5) => \i__carry_i_3__3_n_0\,
      S(4) => \i__carry_i_4__3_n_0\,
      S(3) => \i__carry_i_5__3_n_0\,
      S(2) => \i__carry_i_6__3_n_0\,
      S(1) => \i__carry_i_7__3_n_0\,
      S(0) => \i__carry_i_8__3_n_0\
    );
\Product_mul_temp_inferred__0/i__carry__0\: unisim.vcomponents.CARRY8
     port map (
      CI => \Product_mul_temp_inferred__0/i__carry_n_0\,
      CI_TOP => '0',
      CO(7 downto 1) => \NLW_Product_mul_temp_inferred__0/i__carry__0_CO_UNCONNECTED\(7 downto 1),
      CO(0) => \Product_mul_temp_inferred__0/i__carry__0_n_7\,
      DI(7 downto 1) => B"0000000",
      DI(0) => Product_mul_temp_n_80,
      O(7 downto 2) => \NLW_Product_mul_temp_inferred__0/i__carry__0_O_UNCONNECTED\(7 downto 2),
      O(1 downto 0) => Product_mul_temp0_out(9 downto 8),
      S(7 downto 2) => B"000000",
      S(1) => \i__carry__0_i_1__0_n_0\,
      S(0) => \i__carry__0_i_2_n_0\
    );
Switch6_out1_1_i_2: unisim.vcomponents.LUT6
    generic map(
      INIT => X"8000000000000000"
    )
        port map (
      I0 => Switch6_out1_1_i_3_n_0,
      I1 => Switch6_out1_1_i_4_n_0,
      I2 => Switch6_out1_1_i_5_n_0,
      I3 => Switch6_out1_1_i_6_n_0,
      I4 => Switch6_out1_1_i_7_n_0,
      I5 => Switch6_out1_1_i_8_n_0,
      O => Switch6_out1
    );
Switch6_out1_1_i_3: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0000000000000001"
    )
        port map (
      I0 => \^p\(2),
      I1 => \^p\(4),
      I2 => \^p\(5),
      I3 => Product_mul_temp_n_89,
      I4 => \^p\(1),
      I5 => \^p\(0),
      O => Switch6_out1_1_i_3_n_0
    );
Switch6_out1_1_i_4: unisim.vcomponents.LUT4
    generic map(
      INIT => X"0001"
    )
        port map (
      I0 => Product_mul_temp0_out(9),
      I1 => Product_mul_temp0_out(8),
      I2 => Product_mul_temp0_out(6),
      I3 => Product_mul_temp0_out(5),
      O => Switch6_out1_1_i_4_n_0
    );
Switch6_out1_1_i_5: unisim.vcomponents.LUT3
    generic map(
      INIT => X"01"
    )
        port map (
      I0 => Product_mul_temp0_out(3),
      I1 => Product_mul_temp0_out(2),
      I2 => Product_mul_temp0_out(0),
      O => Switch6_out1_1_i_5_n_0
    );
Switch6_out1_1_i_6: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0000230000002323"
    )
        port map (
      I0 => Product_mul_temp_n_89,
      I1 => Product_mul_temp0_out(0),
      I2 => Product_mul_temp_n_90,
      I3 => \^p\(4),
      I4 => \^p\(5),
      I5 => \^p\(3),
      O => Switch6_out1_1_i_6_n_0
    );
Switch6_out1_1_i_7: unisim.vcomponents.LUT3
    generic map(
      INIT => X"31"
    )
        port map (
      I0 => Product_mul_temp0_out(7),
      I1 => Product_mul_temp0_out(9),
      I2 => Product_mul_temp0_out(8),
      O => Switch6_out1_1_i_7_n_0
    );
Switch6_out1_1_i_8: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0000230000002323"
    )
        port map (
      I0 => Product_mul_temp0_out(5),
      I1 => Product_mul_temp0_out(6),
      I2 => Product_mul_temp0_out(4),
      I3 => Product_mul_temp0_out(2),
      I4 => Product_mul_temp0_out(3),
      I5 => Product_mul_temp0_out(1),
      O => Switch6_out1_1_i_8_n_0
    );
\Switch7_out12_carry__0_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FCFCC040FCFCC0F4"
    )
        port map (
      I0 => \^relational_operator_1_cast\(11),
      I1 => Product_mul_temp0_out(8),
      I2 => Product_mul_temp0_out(9),
      I3 => Switch7_out12_carry_0(0),
      I4 => Switch7_out12_carry(0),
      I5 => \^relational_operator_1_cast\(12),
      O => \U1_norm_1_reg[11]\(0)
    );
\Switch7_out12_carry__0_i_4\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0201000030CC32CD"
    )
        port map (
      I0 => \^relational_operator_1_cast\(12),
      I1 => Switch7_out12_carry(0),
      I2 => Switch7_out12_carry_0(0),
      I3 => Product_mul_temp0_out(9),
      I4 => \^relational_operator_1_cast\(11),
      I5 => Product_mul_temp0_out(8),
      O => \U1_norm_1_reg[12]\(0)
    );
Switch7_out12_carry_i_1: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FCFCFC40FCFCFCF4"
    )
        port map (
      I0 => \^relational_operator_1_cast\(9),
      I1 => Product_mul_temp0_out(6),
      I2 => Product_mul_temp0_out(7),
      I3 => Switch7_out12_carry(0),
      I4 => Switch7_out12_carry_0(0),
      I5 => \^relational_operator_1_cast\(10),
      O => \U1_norm_1_reg[9]\(5)
    );
Switch7_out12_carry_i_10: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0201000000FC02FD"
    )
        port map (
      I0 => \^relational_operator_1_cast\(8),
      I1 => Switch7_out12_carry_0(0),
      I2 => Switch7_out12_carry(0),
      I3 => Product_mul_temp0_out(5),
      I4 => \^relational_operator_1_cast\(7),
      I5 => Product_mul_temp0_out(4),
      O => \U1_norm_1_reg[10]\(4)
    );
Switch7_out12_carry_i_11: unisim.vcomponents.LUT6
    generic map(
      INIT => X"020D000C00F002F1"
    )
        port map (
      I0 => \^relational_operator_1_cast\(6),
      I1 => Switch7_out12_carry_0(0),
      I2 => Switch7_out12_carry(0),
      I3 => Product_mul_temp0_out(3),
      I4 => \^relational_operator_1_cast\(5),
      I5 => Product_mul_temp0_out(2),
      O => \U1_norm_1_reg[10]\(3)
    );
Switch7_out12_carry_i_12: unisim.vcomponents.LUT6
    generic map(
      INIT => X"020D000C00F002F1"
    )
        port map (
      I0 => \^relational_operator_1_cast\(4),
      I1 => Switch7_out12_carry_0(0),
      I2 => Switch7_out12_carry(0),
      I3 => Product_mul_temp0_out(1),
      I4 => \^relational_operator_1_cast\(3),
      I5 => Product_mul_temp0_out(0),
      O => \U1_norm_1_reg[10]\(2)
    );
Switch7_out12_carry_i_13: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0201000000FC02FD"
    )
        port map (
      I0 => \^relational_operator_1_cast\(2),
      I1 => Switch7_out12_carry_0(0),
      I2 => Switch7_out12_carry(0),
      I3 => Product_mul_temp_n_89,
      I4 => \^relational_operator_1_cast\(1),
      I5 => Product_mul_temp_n_90,
      O => \U1_norm_1_reg[10]\(1)
    );
Switch7_out12_carry_i_14: unisim.vcomponents.LUT5
    generic map(
      INIT => X"000C02F1"
    )
        port map (
      I0 => \^relational_operator_1_cast\(0),
      I1 => Switch7_out12_carry_0(0),
      I2 => Switch7_out12_carry(0),
      I3 => \^p\(5),
      I4 => \^p\(4),
      O => \U1_norm_1_reg[10]\(0)
    );
Switch7_out12_carry_i_2: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FCFCFC40FCFCFCF4"
    )
        port map (
      I0 => \^relational_operator_1_cast\(7),
      I1 => Product_mul_temp0_out(4),
      I2 => Product_mul_temp0_out(5),
      I3 => Switch7_out12_carry(0),
      I4 => Switch7_out12_carry_0(0),
      I5 => \^relational_operator_1_cast\(8),
      O => \U1_norm_1_reg[9]\(4)
    );
Switch7_out12_carry_i_3: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FCF0FC40FCF0FCF4"
    )
        port map (
      I0 => \^relational_operator_1_cast\(5),
      I1 => Product_mul_temp0_out(2),
      I2 => Product_mul_temp0_out(3),
      I3 => Switch7_out12_carry(0),
      I4 => Switch7_out12_carry_0(0),
      I5 => \^relational_operator_1_cast\(6),
      O => \U1_norm_1_reg[9]\(3)
    );
Switch7_out12_carry_i_4: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FCF0FC40FCF0FCF4"
    )
        port map (
      I0 => \^relational_operator_1_cast\(3),
      I1 => Product_mul_temp0_out(0),
      I2 => Product_mul_temp0_out(1),
      I3 => Switch7_out12_carry(0),
      I4 => Switch7_out12_carry_0(0),
      I5 => \^relational_operator_1_cast\(4),
      O => \U1_norm_1_reg[9]\(2)
    );
Switch7_out12_carry_i_5: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FCFCFC40FCFCFCF4"
    )
        port map (
      I0 => \^relational_operator_1_cast\(1),
      I1 => Product_mul_temp_n_90,
      I2 => Product_mul_temp_n_89,
      I3 => Switch7_out12_carry(0),
      I4 => Switch7_out12_carry_0(0),
      I5 => \^relational_operator_1_cast\(2),
      O => \U1_norm_1_reg[9]\(1)
    );
Switch7_out12_carry_i_7: unisim.vcomponents.LUT4
    generic map(
      INIT => X"E0EE"
    )
        port map (
      I0 => \^p\(3),
      I1 => \^p\(2),
      I2 => Switch7_out12_carry(0),
      I3 => Switch7_out12_carry_0(0),
      O => \U1_norm_1_reg[9]\(0)
    );
Switch7_out12_carry_i_9: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0201000000FC02FD"
    )
        port map (
      I0 => \^relational_operator_1_cast\(10),
      I1 => Switch7_out12_carry_0(0),
      I2 => Switch7_out12_carry(0),
      I3 => Product_mul_temp0_out(7),
      I4 => \^relational_operator_1_cast\(9),
      I5 => Product_mul_temp0_out(6),
      O => \U1_norm_1_reg[10]\(5)
    );
\Switch8_out12_carry__0_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"000000B8"
    )
        port map (
      I0 => \Delay1_out1_reg[13]_0\(13),
      I1 => \^allow_assymetrical_anew_reference_value__0\,
      I2 => \Delay1_out1_reg[13]\(13),
      I3 => Switch8_out12_carry(0),
      I4 => Switch8_out12_carry_0(0),
      O => \U2_norm_1_reg[13]_0\(1)
    );
\Switch8_out12_carry__0_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FCFCC040FCFCC0F4"
    )
        port map (
      I0 => \^u2_norm_1_reg[12]_0\(11),
      I1 => Product_mul_temp0_out(8),
      I2 => Product_mul_temp0_out(9),
      I3 => Switch8_out12_carry(0),
      I4 => Switch8_out12_carry_0(0),
      I5 => \^u2_norm_1_reg[12]_0\(12),
      O => \U2_norm_1_reg[13]_0\(0)
    );
\Switch8_out12_carry__0_i_4\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0201000030CC32CD"
    )
        port map (
      I0 => \^u2_norm_1_reg[12]_0\(12),
      I1 => Switch8_out12_carry_0(0),
      I2 => Switch8_out12_carry(0),
      I3 => Product_mul_temp0_out(9),
      I4 => \^u2_norm_1_reg[12]_0\(11),
      I5 => Product_mul_temp0_out(8),
      O => \U2_norm_1_reg[12]\(0)
    );
Switch8_out12_carry_i_1: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FCFCFC40FCFCFCF4"
    )
        port map (
      I0 => \^u2_norm_1_reg[12]_0\(9),
      I1 => Product_mul_temp0_out(6),
      I2 => Product_mul_temp0_out(7),
      I3 => Switch8_out12_carry_0(0),
      I4 => Switch8_out12_carry(0),
      I5 => \^u2_norm_1_reg[12]_0\(10),
      O => \U2_norm_1_reg[9]\(7)
    );
Switch8_out12_carry_i_10: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0201000000FC02FD"
    )
        port map (
      I0 => \^u2_norm_1_reg[12]_0\(8),
      I1 => Switch8_out12_carry(0),
      I2 => Switch8_out12_carry_0(0),
      I3 => Product_mul_temp0_out(5),
      I4 => \^u2_norm_1_reg[12]_0\(7),
      I5 => Product_mul_temp0_out(4),
      O => \U2_norm_1_reg[10]\(6)
    );
Switch8_out12_carry_i_11: unisim.vcomponents.LUT6
    generic map(
      INIT => X"020D000C00F002F1"
    )
        port map (
      I0 => \^u2_norm_1_reg[12]_0\(6),
      I1 => Switch8_out12_carry(0),
      I2 => Switch8_out12_carry_0(0),
      I3 => Product_mul_temp0_out(3),
      I4 => \^u2_norm_1_reg[12]_0\(5),
      I5 => Product_mul_temp0_out(2),
      O => \U2_norm_1_reg[10]\(5)
    );
Switch8_out12_carry_i_12: unisim.vcomponents.LUT6
    generic map(
      INIT => X"020D000C00F002F1"
    )
        port map (
      I0 => \^u2_norm_1_reg[12]_0\(4),
      I1 => Switch8_out12_carry(0),
      I2 => Switch8_out12_carry_0(0),
      I3 => Product_mul_temp0_out(1),
      I4 => \^u2_norm_1_reg[12]_0\(3),
      I5 => Product_mul_temp0_out(0),
      O => \U2_norm_1_reg[10]\(4)
    );
Switch8_out12_carry_i_13: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0201000000FC02FD"
    )
        port map (
      I0 => \^u2_norm_1_reg[12]_0\(2),
      I1 => Switch8_out12_carry(0),
      I2 => Switch8_out12_carry_0(0),
      I3 => Product_mul_temp_n_89,
      I4 => \^u2_norm_1_reg[12]_0\(1),
      I5 => Product_mul_temp_n_90,
      O => \U2_norm_1_reg[10]\(3)
    );
Switch8_out12_carry_i_14: unisim.vcomponents.LUT5
    generic map(
      INIT => X"000C02F1"
    )
        port map (
      I0 => \^u2_norm_1_reg[12]_0\(0),
      I1 => Switch8_out12_carry(0),
      I2 => Switch8_out12_carry_0(0),
      I3 => \^p\(5),
      I4 => \^p\(4),
      O => \U2_norm_1_reg[10]\(2)
    );
Switch8_out12_carry_i_15: unisim.vcomponents.LUT4
    generic map(
      INIT => X"200D"
    )
        port map (
      I0 => Switch8_out12_carry(0),
      I1 => Switch8_out12_carry_0(0),
      I2 => \^p\(2),
      I3 => \^p\(3),
      O => \U2_norm_1_reg[10]\(1)
    );
Switch8_out12_carry_i_16: unisim.vcomponents.LUT4
    generic map(
      INIT => X"020D"
    )
        port map (
      I0 => Switch8_out12_carry(0),
      I1 => Switch8_out12_carry_0(0),
      I2 => \^p\(0),
      I3 => \^p\(1),
      O => \U2_norm_1_reg[10]\(0)
    );
Switch8_out12_carry_i_2: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FCFCFC40FCFCFCF4"
    )
        port map (
      I0 => \^u2_norm_1_reg[12]_0\(7),
      I1 => Product_mul_temp0_out(4),
      I2 => Product_mul_temp0_out(5),
      I3 => Switch8_out12_carry_0(0),
      I4 => Switch8_out12_carry(0),
      I5 => \^u2_norm_1_reg[12]_0\(8),
      O => \U2_norm_1_reg[9]\(6)
    );
Switch8_out12_carry_i_3: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FCF0FC40FCF0FCF4"
    )
        port map (
      I0 => \^u2_norm_1_reg[12]_0\(5),
      I1 => Product_mul_temp0_out(2),
      I2 => Product_mul_temp0_out(3),
      I3 => Switch8_out12_carry_0(0),
      I4 => Switch8_out12_carry(0),
      I5 => \^u2_norm_1_reg[12]_0\(6),
      O => \U2_norm_1_reg[9]\(5)
    );
Switch8_out12_carry_i_4: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FCF0FC40FCF0FCF4"
    )
        port map (
      I0 => \^u2_norm_1_reg[12]_0\(3),
      I1 => Product_mul_temp0_out(0),
      I2 => Product_mul_temp0_out(1),
      I3 => Switch8_out12_carry_0(0),
      I4 => Switch8_out12_carry(0),
      I5 => \^u2_norm_1_reg[12]_0\(4),
      O => \U2_norm_1_reg[9]\(4)
    );
Switch8_out12_carry_i_5: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FCFCFC40FCFCFCF4"
    )
        port map (
      I0 => \^u2_norm_1_reg[12]_0\(1),
      I1 => Product_mul_temp_n_90,
      I2 => Product_mul_temp_n_89,
      I3 => Switch8_out12_carry_0(0),
      I4 => Switch8_out12_carry(0),
      I5 => \^u2_norm_1_reg[12]_0\(2),
      O => \U2_norm_1_reg[9]\(3)
    );
Switch8_out12_carry_i_6: unisim.vcomponents.LUT5
    generic map(
      INIT => X"ECE8ECEE"
    )
        port map (
      I0 => \^p\(4),
      I1 => \^p\(5),
      I2 => Switch8_out12_carry_0(0),
      I3 => Switch8_out12_carry(0),
      I4 => \^u2_norm_1_reg[12]_0\(0),
      O => \U2_norm_1_reg[9]\(2)
    );
Switch8_out12_carry_i_7: unisim.vcomponents.LUT4
    generic map(
      INIT => X"E0EE"
    )
        port map (
      I0 => \^p\(3),
      I1 => \^p\(2),
      I2 => Switch8_out12_carry_0(0),
      I3 => Switch8_out12_carry(0),
      O => \U2_norm_1_reg[9]\(1)
    );
Switch8_out12_carry_i_8: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FDD0"
    )
        port map (
      I0 => Switch8_out12_carry(0),
      I1 => Switch8_out12_carry_0(0),
      I2 => \^p\(0),
      I3 => \^p\(1),
      O => \U2_norm_1_reg[9]\(0)
    );
Switch8_out12_carry_i_9: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0201000000FC02FD"
    )
        port map (
      I0 => \^u2_norm_1_reg[12]_0\(10),
      I1 => Switch8_out12_carry(0),
      I2 => Switch8_out12_carry_0(0),
      I3 => Product_mul_temp0_out(7),
      I4 => \^u2_norm_1_reg[12]_0\(9),
      I5 => Product_mul_temp0_out(6),
      O => \U2_norm_1_reg[10]\(7)
    );
\Switch9_out12_carry__0_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"000000B8"
    )
        port map (
      I0 => \Delay2_out1_reg[13]_0\(13),
      I1 => \^allow_assymetrical_anew_reference_value__0\,
      I2 => \Delay2_out1_reg[13]\(13),
      I3 => Switch9_out12_carry(0),
      I4 => Switch9_out12_carry_0(0),
      O => \U3_norm_1_reg[13]_0\(1)
    );
\Switch9_out12_carry__0_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FCFCC040FCFCC0F4"
    )
        port map (
      I0 => \^u3_norm_1_reg[12]_0\(11),
      I1 => Product_mul_temp0_out(8),
      I2 => Product_mul_temp0_out(9),
      I3 => Switch9_out12_carry(0),
      I4 => Switch9_out12_carry_0(0),
      I5 => \^u3_norm_1_reg[12]_0\(12),
      O => \U3_norm_1_reg[13]_0\(0)
    );
\Switch9_out12_carry__0_i_4\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0201000030CC32CD"
    )
        port map (
      I0 => \^u3_norm_1_reg[12]_0\(12),
      I1 => Switch9_out12_carry_0(0),
      I2 => Switch9_out12_carry(0),
      I3 => Product_mul_temp0_out(9),
      I4 => \^u3_norm_1_reg[12]_0\(11),
      I5 => Product_mul_temp0_out(8),
      O => \U3_norm_1_reg[12]\(0)
    );
Switch9_out12_carry_i_1: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FCFCFC40FCFCFCF4"
    )
        port map (
      I0 => \^u3_norm_1_reg[12]_0\(9),
      I1 => Product_mul_temp0_out(6),
      I2 => Product_mul_temp0_out(7),
      I3 => Switch9_out12_carry_0(0),
      I4 => Switch9_out12_carry(0),
      I5 => \^u3_norm_1_reg[12]_0\(10),
      O => \U3_norm_1_reg[9]\(7)
    );
Switch9_out12_carry_i_10: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0201000000FC02FD"
    )
        port map (
      I0 => \^u3_norm_1_reg[12]_0\(8),
      I1 => Switch9_out12_carry(0),
      I2 => Switch9_out12_carry_0(0),
      I3 => Product_mul_temp0_out(5),
      I4 => \^u3_norm_1_reg[12]_0\(7),
      I5 => Product_mul_temp0_out(4),
      O => \U3_norm_1_reg[10]\(6)
    );
Switch9_out12_carry_i_11: unisim.vcomponents.LUT6
    generic map(
      INIT => X"020D000C00F002F1"
    )
        port map (
      I0 => \^u3_norm_1_reg[12]_0\(6),
      I1 => Switch9_out12_carry(0),
      I2 => Switch9_out12_carry_0(0),
      I3 => Product_mul_temp0_out(3),
      I4 => \^u3_norm_1_reg[12]_0\(5),
      I5 => Product_mul_temp0_out(2),
      O => \U3_norm_1_reg[10]\(5)
    );
Switch9_out12_carry_i_12: unisim.vcomponents.LUT6
    generic map(
      INIT => X"020D000C00F002F1"
    )
        port map (
      I0 => \^u3_norm_1_reg[12]_0\(4),
      I1 => Switch9_out12_carry(0),
      I2 => Switch9_out12_carry_0(0),
      I3 => Product_mul_temp0_out(1),
      I4 => \^u3_norm_1_reg[12]_0\(3),
      I5 => Product_mul_temp0_out(0),
      O => \U3_norm_1_reg[10]\(4)
    );
Switch9_out12_carry_i_13: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0201000000FC02FD"
    )
        port map (
      I0 => \^u3_norm_1_reg[12]_0\(2),
      I1 => Switch9_out12_carry(0),
      I2 => Switch9_out12_carry_0(0),
      I3 => Product_mul_temp_n_89,
      I4 => \^u3_norm_1_reg[12]_0\(1),
      I5 => Product_mul_temp_n_90,
      O => \U3_norm_1_reg[10]\(3)
    );
Switch9_out12_carry_i_14: unisim.vcomponents.LUT5
    generic map(
      INIT => X"000C02F1"
    )
        port map (
      I0 => \^u3_norm_1_reg[12]_0\(0),
      I1 => Switch9_out12_carry(0),
      I2 => Switch9_out12_carry_0(0),
      I3 => \^p\(5),
      I4 => \^p\(4),
      O => \U3_norm_1_reg[10]\(2)
    );
Switch9_out12_carry_i_15: unisim.vcomponents.LUT4
    generic map(
      INIT => X"200D"
    )
        port map (
      I0 => Switch9_out12_carry(0),
      I1 => Switch9_out12_carry_0(0),
      I2 => \^p\(2),
      I3 => \^p\(3),
      O => \U3_norm_1_reg[10]\(1)
    );
Switch9_out12_carry_i_16: unisim.vcomponents.LUT4
    generic map(
      INIT => X"020D"
    )
        port map (
      I0 => Switch9_out12_carry(0),
      I1 => Switch9_out12_carry_0(0),
      I2 => \^p\(0),
      I3 => \^p\(1),
      O => \U3_norm_1_reg[10]\(0)
    );
Switch9_out12_carry_i_2: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FCFCFC40FCFCFCF4"
    )
        port map (
      I0 => \^u3_norm_1_reg[12]_0\(7),
      I1 => Product_mul_temp0_out(4),
      I2 => Product_mul_temp0_out(5),
      I3 => Switch9_out12_carry_0(0),
      I4 => Switch9_out12_carry(0),
      I5 => \^u3_norm_1_reg[12]_0\(8),
      O => \U3_norm_1_reg[9]\(6)
    );
Switch9_out12_carry_i_3: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FCF0FC40FCF0FCF4"
    )
        port map (
      I0 => \^u3_norm_1_reg[12]_0\(5),
      I1 => Product_mul_temp0_out(2),
      I2 => Product_mul_temp0_out(3),
      I3 => Switch9_out12_carry_0(0),
      I4 => Switch9_out12_carry(0),
      I5 => \^u3_norm_1_reg[12]_0\(6),
      O => \U3_norm_1_reg[9]\(5)
    );
Switch9_out12_carry_i_4: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FCF0FC40FCF0FCF4"
    )
        port map (
      I0 => \^u3_norm_1_reg[12]_0\(3),
      I1 => Product_mul_temp0_out(0),
      I2 => Product_mul_temp0_out(1),
      I3 => Switch9_out12_carry_0(0),
      I4 => Switch9_out12_carry(0),
      I5 => \^u3_norm_1_reg[12]_0\(4),
      O => \U3_norm_1_reg[9]\(4)
    );
Switch9_out12_carry_i_5: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FCFCFC40FCFCFCF4"
    )
        port map (
      I0 => \^u3_norm_1_reg[12]_0\(1),
      I1 => Product_mul_temp_n_90,
      I2 => Product_mul_temp_n_89,
      I3 => Switch9_out12_carry_0(0),
      I4 => Switch9_out12_carry(0),
      I5 => \^u3_norm_1_reg[12]_0\(2),
      O => \U3_norm_1_reg[9]\(3)
    );
Switch9_out12_carry_i_6: unisim.vcomponents.LUT5
    generic map(
      INIT => X"ECE8ECEE"
    )
        port map (
      I0 => \^p\(4),
      I1 => \^p\(5),
      I2 => Switch9_out12_carry_0(0),
      I3 => Switch9_out12_carry(0),
      I4 => \^u3_norm_1_reg[12]_0\(0),
      O => \U3_norm_1_reg[9]\(2)
    );
Switch9_out12_carry_i_7: unisim.vcomponents.LUT4
    generic map(
      INIT => X"E0EE"
    )
        port map (
      I0 => \^p\(3),
      I1 => \^p\(2),
      I2 => Switch9_out12_carry_0(0),
      I3 => Switch9_out12_carry(0),
      O => \U3_norm_1_reg[9]\(1)
    );
Switch9_out12_carry_i_8: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FDD0"
    )
        port map (
      I0 => Switch9_out12_carry(0),
      I1 => Switch9_out12_carry_0(0),
      I2 => \^p\(0),
      I3 => \^p\(1),
      O => \U3_norm_1_reg[9]\(0)
    );
Switch9_out12_carry_i_9: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0201000000FC02FD"
    )
        port map (
      I0 => \^u3_norm_1_reg[12]_0\(10),
      I1 => Switch9_out12_carry(0),
      I2 => Switch9_out12_carry_0(0),
      I3 => Product_mul_temp0_out(7),
      I4 => \^u3_norm_1_reg[12]_0\(9),
      I5 => Product_mul_temp0_out(6),
      O => \U3_norm_1_reg[10]\(7)
    );
\i__carry__0_i_1__0\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"9"
    )
        port map (
      I0 => Product_mul_temp_n_79,
      I1 => \Product_mul_temp__0_carry__0_n_14\,
      O => \i__carry__0_i_1__0_n_0\
    );
\i__carry__0_i_2\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"6"
    )
        port map (
      I0 => Product_mul_temp_n_80,
      I1 => \Product_mul_temp__0\(8),
      O => \i__carry__0_i_2_n_0\
    );
\i__carry_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"22222222BBB222B2"
    )
        port map (
      I0 => Add_out1(13),
      I1 => \^u3_norm_1_reg[13]\,
      I2 => \Delay2_out1_reg[13]\(12),
      I3 => \^allow_assymetrical_anew_reference_value__0\,
      I4 => \Delay2_out1_reg[13]_0\(12),
      I5 => Add_out1(12),
      O => \Delay2_out1_reg[12]\(6)
    );
\i__carry_i_10\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"9990009000099909"
    )
        port map (
      I0 => \^u3_norm_1_reg[12]_0\(9),
      I1 => Add_out1(9),
      I2 => \Delay2_out1_reg[13]\(8),
      I3 => \^allow_assymetrical_anew_reference_value__0\,
      I4 => \Delay2_out1_reg[13]_0\(8),
      I5 => Add_out1(8),
      O => \Delay2_out1_reg[12]_0\(4)
    );
\i__carry_i_10__0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"9990009000099909"
    )
        port map (
      I0 => \^u2_norm_1_reg[12]_0\(9),
      I1 => Add_out1(9),
      I2 => \Delay1_out1_reg[13]\(8),
      I3 => \^allow_assymetrical_anew_reference_value__0\,
      I4 => \Delay1_out1_reg[13]_0\(8),
      I5 => Add_out1(8),
      O => \Delay1_out1_reg[12]_0\(4)
    );
\i__carry_i_10__1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"A95900000000A959"
    )
        port map (
      I0 => Add_out1(8),
      I1 => \Delay_out1_reg[13]\(8),
      I2 => \^allow_assymetrical_anew_reference_value__0\,
      I3 => \Delay_out1_reg[13]_0\(8),
      I4 => \^relational_operator_1_cast\(9),
      I5 => Add_out1(9),
      O => \Delay_out1_reg[12]_0\(4)
    );
\i__carry_i_11\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"9990009000099909"
    )
        port map (
      I0 => \^u3_norm_1_reg[12]_0\(7),
      I1 => Add_out1(7),
      I2 => \Delay2_out1_reg[13]\(6),
      I3 => \^allow_assymetrical_anew_reference_value__0\,
      I4 => \Delay2_out1_reg[13]_0\(6),
      I5 => Add_out1(6),
      O => \Delay2_out1_reg[12]_0\(3)
    );
\i__carry_i_11__0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"9990009000099909"
    )
        port map (
      I0 => \^u2_norm_1_reg[12]_0\(7),
      I1 => Add_out1(7),
      I2 => \Delay1_out1_reg[13]\(6),
      I3 => \^allow_assymetrical_anew_reference_value__0\,
      I4 => \Delay1_out1_reg[13]_0\(6),
      I5 => Add_out1(6),
      O => \Delay1_out1_reg[12]_0\(3)
    );
\i__carry_i_11__1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"A95900000000A959"
    )
        port map (
      I0 => Add_out1(6),
      I1 => \Delay_out1_reg[13]\(6),
      I2 => \^allow_assymetrical_anew_reference_value__0\,
      I3 => \Delay_out1_reg[13]_0\(6),
      I4 => \^relational_operator_1_cast\(7),
      I5 => Add_out1(7),
      O => \Delay_out1_reg[12]_0\(3)
    );
\i__carry_i_12\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"9990009000099909"
    )
        port map (
      I0 => \^u3_norm_1_reg[12]_0\(5),
      I1 => Add_out1(5),
      I2 => \Delay2_out1_reg[13]\(4),
      I3 => \^allow_assymetrical_anew_reference_value__0\,
      I4 => \Delay2_out1_reg[13]_0\(4),
      I5 => Add_out1(4),
      O => \Delay2_out1_reg[12]_0\(2)
    );
\i__carry_i_12__0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"9990009000099909"
    )
        port map (
      I0 => \^u2_norm_1_reg[12]_0\(5),
      I1 => Add_out1(5),
      I2 => \Delay1_out1_reg[13]\(4),
      I3 => \^allow_assymetrical_anew_reference_value__0\,
      I4 => \Delay1_out1_reg[13]_0\(4),
      I5 => Add_out1(4),
      O => \Delay1_out1_reg[12]_0\(2)
    );
\i__carry_i_12__1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"A95900000000A959"
    )
        port map (
      I0 => Add_out1(4),
      I1 => \Delay_out1_reg[13]\(4),
      I2 => \^allow_assymetrical_anew_reference_value__0\,
      I3 => \Delay_out1_reg[13]_0\(4),
      I4 => \^relational_operator_1_cast\(5),
      I5 => Add_out1(5),
      O => \Delay_out1_reg[12]_0\(2)
    );
\i__carry_i_13\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"9990009000099909"
    )
        port map (
      I0 => \^u3_norm_1_reg[12]_0\(3),
      I1 => Add_out1(3),
      I2 => \Delay2_out1_reg[13]\(2),
      I3 => \^allow_assymetrical_anew_reference_value__0\,
      I4 => \Delay2_out1_reg[13]_0\(2),
      I5 => Add_out1(2),
      O => \Delay2_out1_reg[12]_0\(1)
    );
\i__carry_i_13__0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"9990009000099909"
    )
        port map (
      I0 => \^u2_norm_1_reg[12]_0\(3),
      I1 => Add_out1(3),
      I2 => \Delay1_out1_reg[13]\(2),
      I3 => \^allow_assymetrical_anew_reference_value__0\,
      I4 => \Delay1_out1_reg[13]_0\(2),
      I5 => Add_out1(2),
      O => \Delay1_out1_reg[12]_0\(1)
    );
\i__carry_i_13__1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"A95900000000A959"
    )
        port map (
      I0 => Add_out1(2),
      I1 => \Delay_out1_reg[13]\(2),
      I2 => \^allow_assymetrical_anew_reference_value__0\,
      I3 => \Delay_out1_reg[13]_0\(2),
      I4 => \^relational_operator_1_cast\(3),
      I5 => Add_out1(3),
      O => \Delay_out1_reg[12]_0\(1)
    );
\i__carry_i_14\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"9990009000099909"
    )
        port map (
      I0 => \^u3_norm_1_reg[12]_0\(1),
      I1 => Add_out1(1),
      I2 => \Delay2_out1_reg[13]\(0),
      I3 => \^allow_assymetrical_anew_reference_value__0\,
      I4 => \Delay2_out1_reg[13]_0\(0),
      I5 => Add_out1(0),
      O => \Delay2_out1_reg[12]_0\(0)
    );
\i__carry_i_14__0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"9990009000099909"
    )
        port map (
      I0 => \^u2_norm_1_reg[12]_0\(1),
      I1 => Add_out1(1),
      I2 => \Delay1_out1_reg[13]\(0),
      I3 => \^allow_assymetrical_anew_reference_value__0\,
      I4 => \Delay1_out1_reg[13]_0\(0),
      I5 => Add_out1(0),
      O => \Delay1_out1_reg[12]_0\(0)
    );
\i__carry_i_14__1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"A95900000000A959"
    )
        port map (
      I0 => Add_out1(0),
      I1 => \Delay_out1_reg[13]\(0),
      I2 => \^allow_assymetrical_anew_reference_value__0\,
      I3 => \Delay_out1_reg[13]_0\(0),
      I4 => \^relational_operator_1_cast\(1),
      I5 => Add_out1(1),
      O => \Delay_out1_reg[12]_0\(0)
    );
\i__carry_i_1__0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"22222222BBB222B2"
    )
        port map (
      I0 => Add_out1(13),
      I1 => \^u2_norm_1_reg[13]\,
      I2 => \Delay1_out1_reg[13]\(12),
      I3 => \^allow_assymetrical_anew_reference_value__0\,
      I4 => \Delay1_out1_reg[13]_0\(12),
      I5 => Add_out1(12),
      O => \Delay1_out1_reg[12]\(6)
    );
\i__carry_i_1__1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"22222222BBB222B2"
    )
        port map (
      I0 => Add_out1(13),
      I1 => \^relational_operator_1_cast\(13),
      I2 => \Delay_out1_reg[13]\(12),
      I3 => \^allow_assymetrical_anew_reference_value__0\,
      I4 => \Delay_out1_reg[13]_0\(12),
      I5 => Add_out1(12),
      O => \Delay_out1_reg[12]\(6)
    );
\i__carry_i_1__3\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"6"
    )
        port map (
      I0 => Product_mul_temp_n_81,
      I1 => \Product_mul_temp__0\(7),
      O => \i__carry_i_1__3_n_0\
    );
\i__carry_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"22222222BBB222B2"
    )
        port map (
      I0 => \^u3_norm_1_reg[12]_0\(11),
      I1 => Add_out1(11),
      I2 => \Delay2_out1_reg[13]\(10),
      I3 => \^allow_assymetrical_anew_reference_value__0\,
      I4 => \Delay2_out1_reg[13]_0\(10),
      I5 => Add_out1(10),
      O => \Delay2_out1_reg[12]\(5)
    );
\i__carry_i_2__0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"22222222BBB222B2"
    )
        port map (
      I0 => \^u2_norm_1_reg[12]_0\(11),
      I1 => Add_out1(11),
      I2 => \Delay1_out1_reg[13]\(10),
      I3 => \^allow_assymetrical_anew_reference_value__0\,
      I4 => \Delay1_out1_reg[13]_0\(10),
      I5 => Add_out1(10),
      O => \Delay1_out1_reg[12]\(5)
    );
\i__carry_i_2__1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"22222222BBB222B2"
    )
        port map (
      I0 => \^relational_operator_1_cast\(11),
      I1 => Add_out1(11),
      I2 => \Delay_out1_reg[13]\(10),
      I3 => \^allow_assymetrical_anew_reference_value__0\,
      I4 => \Delay_out1_reg[13]_0\(10),
      I5 => Add_out1(10),
      O => \Delay_out1_reg[12]\(5)
    );
\i__carry_i_2__3\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"6"
    )
        port map (
      I0 => Product_mul_temp_n_82,
      I1 => \Product_mul_temp__0\(6),
      O => \i__carry_i_2__3_n_0\
    );
\i__carry_i_3\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"22222222BBB222B2"
    )
        port map (
      I0 => \^u3_norm_1_reg[12]_0\(9),
      I1 => Add_out1(9),
      I2 => \Delay2_out1_reg[13]\(8),
      I3 => \^allow_assymetrical_anew_reference_value__0\,
      I4 => \Delay2_out1_reg[13]_0\(8),
      I5 => Add_out1(8),
      O => \Delay2_out1_reg[12]\(4)
    );
\i__carry_i_3__0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"22222222BBB222B2"
    )
        port map (
      I0 => \^u2_norm_1_reg[12]_0\(9),
      I1 => Add_out1(9),
      I2 => \Delay1_out1_reg[13]\(8),
      I3 => \^allow_assymetrical_anew_reference_value__0\,
      I4 => \Delay1_out1_reg[13]_0\(8),
      I5 => Add_out1(8),
      O => \Delay1_out1_reg[12]\(4)
    );
\i__carry_i_3__1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"22222222BBB222B2"
    )
        port map (
      I0 => \^relational_operator_1_cast\(9),
      I1 => Add_out1(9),
      I2 => \Delay_out1_reg[13]\(8),
      I3 => \^allow_assymetrical_anew_reference_value__0\,
      I4 => \Delay_out1_reg[13]_0\(8),
      I5 => Add_out1(8),
      O => \Delay_out1_reg[12]\(4)
    );
\i__carry_i_3__3\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"6"
    )
        port map (
      I0 => Product_mul_temp_n_83,
      I1 => \Product_mul_temp__0\(5),
      O => \i__carry_i_3__3_n_0\
    );
\i__carry_i_4\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"22222222BBB222B2"
    )
        port map (
      I0 => \^u3_norm_1_reg[12]_0\(7),
      I1 => Add_out1(7),
      I2 => \Delay2_out1_reg[13]\(6),
      I3 => \^allow_assymetrical_anew_reference_value__0\,
      I4 => \Delay2_out1_reg[13]_0\(6),
      I5 => Add_out1(6),
      O => \Delay2_out1_reg[12]\(3)
    );
\i__carry_i_4__0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"22222222BBB222B2"
    )
        port map (
      I0 => \^u2_norm_1_reg[12]_0\(7),
      I1 => Add_out1(7),
      I2 => \Delay1_out1_reg[13]\(6),
      I3 => \^allow_assymetrical_anew_reference_value__0\,
      I4 => \Delay1_out1_reg[13]_0\(6),
      I5 => Add_out1(6),
      O => \Delay1_out1_reg[12]\(3)
    );
\i__carry_i_4__1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"22222222BBB222B2"
    )
        port map (
      I0 => \^relational_operator_1_cast\(7),
      I1 => Add_out1(7),
      I2 => \Delay_out1_reg[13]\(6),
      I3 => \^allow_assymetrical_anew_reference_value__0\,
      I4 => \Delay_out1_reg[13]_0\(6),
      I5 => Add_out1(6),
      O => \Delay_out1_reg[12]\(3)
    );
\i__carry_i_4__3\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"6"
    )
        port map (
      I0 => Product_mul_temp_n_84,
      I1 => \Product_mul_temp__0\(4),
      O => \i__carry_i_4__3_n_0\
    );
\i__carry_i_5\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"22222222BBB222B2"
    )
        port map (
      I0 => \^u3_norm_1_reg[12]_0\(5),
      I1 => Add_out1(5),
      I2 => \Delay2_out1_reg[13]\(4),
      I3 => \^allow_assymetrical_anew_reference_value__0\,
      I4 => \Delay2_out1_reg[13]_0\(4),
      I5 => Add_out1(4),
      O => \Delay2_out1_reg[12]\(2)
    );
\i__carry_i_5__0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"22222222BBB222B2"
    )
        port map (
      I0 => \^u2_norm_1_reg[12]_0\(5),
      I1 => Add_out1(5),
      I2 => \Delay1_out1_reg[13]\(4),
      I3 => \^allow_assymetrical_anew_reference_value__0\,
      I4 => \Delay1_out1_reg[13]_0\(4),
      I5 => Add_out1(4),
      O => \Delay1_out1_reg[12]\(2)
    );
\i__carry_i_5__1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"22222222BBB222B2"
    )
        port map (
      I0 => \^relational_operator_1_cast\(5),
      I1 => Add_out1(5),
      I2 => \Delay_out1_reg[13]\(4),
      I3 => \^allow_assymetrical_anew_reference_value__0\,
      I4 => \Delay_out1_reg[13]_0\(4),
      I5 => Add_out1(4),
      O => \Delay_out1_reg[12]\(2)
    );
\i__carry_i_5__3\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"6"
    )
        port map (
      I0 => Product_mul_temp_n_85,
      I1 => \Product_mul_temp__0\(3),
      O => \i__carry_i_5__3_n_0\
    );
\i__carry_i_6\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"22222222BBB222B2"
    )
        port map (
      I0 => \^u3_norm_1_reg[12]_0\(3),
      I1 => Add_out1(3),
      I2 => \Delay2_out1_reg[13]\(2),
      I3 => \^allow_assymetrical_anew_reference_value__0\,
      I4 => \Delay2_out1_reg[13]_0\(2),
      I5 => Add_out1(2),
      O => \Delay2_out1_reg[12]\(1)
    );
\i__carry_i_6__0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"22222222BBB222B2"
    )
        port map (
      I0 => \^u2_norm_1_reg[12]_0\(3),
      I1 => Add_out1(3),
      I2 => \Delay1_out1_reg[13]\(2),
      I3 => \^allow_assymetrical_anew_reference_value__0\,
      I4 => \Delay1_out1_reg[13]_0\(2),
      I5 => Add_out1(2),
      O => \Delay1_out1_reg[12]\(1)
    );
\i__carry_i_6__1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"22222222BBB222B2"
    )
        port map (
      I0 => \^relational_operator_1_cast\(3),
      I1 => Add_out1(3),
      I2 => \Delay_out1_reg[13]\(2),
      I3 => \^allow_assymetrical_anew_reference_value__0\,
      I4 => \Delay_out1_reg[13]_0\(2),
      I5 => Add_out1(2),
      O => \Delay_out1_reg[12]\(1)
    );
\i__carry_i_6__3\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"6"
    )
        port map (
      I0 => Product_mul_temp_n_86,
      I1 => \Product_mul_temp__0\(2),
      O => \i__carry_i_6__3_n_0\
    );
\i__carry_i_7\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"22222222BBB222B2"
    )
        port map (
      I0 => \^u3_norm_1_reg[12]_0\(1),
      I1 => Add_out1(1),
      I2 => \Delay2_out1_reg[13]\(0),
      I3 => \^allow_assymetrical_anew_reference_value__0\,
      I4 => \Delay2_out1_reg[13]_0\(0),
      I5 => Add_out1(0),
      O => \Delay2_out1_reg[12]\(0)
    );
\i__carry_i_7__0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"22222222BBB222B2"
    )
        port map (
      I0 => \^u2_norm_1_reg[12]_0\(1),
      I1 => Add_out1(1),
      I2 => \Delay1_out1_reg[13]\(0),
      I3 => \^allow_assymetrical_anew_reference_value__0\,
      I4 => \Delay1_out1_reg[13]_0\(0),
      I5 => Add_out1(0),
      O => \Delay1_out1_reg[12]\(0)
    );
\i__carry_i_7__1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"22222222BBB222B2"
    )
        port map (
      I0 => \^relational_operator_1_cast\(1),
      I1 => Add_out1(1),
      I2 => \Delay_out1_reg[13]\(0),
      I3 => \^allow_assymetrical_anew_reference_value__0\,
      I4 => \Delay_out1_reg[13]_0\(0),
      I5 => Add_out1(0),
      O => \Delay_out1_reg[12]\(0)
    );
\i__carry_i_7__3\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"6"
    )
        port map (
      I0 => Product_mul_temp_n_87,
      I1 => \Product_mul_temp__0\(1),
      O => \i__carry_i_7__3_n_0\
    );
\i__carry_i_8\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"9990009000099909"
    )
        port map (
      I0 => \^u3_norm_1_reg[13]\,
      I1 => Add_out1(13),
      I2 => \Delay2_out1_reg[13]\(12),
      I3 => \^allow_assymetrical_anew_reference_value__0\,
      I4 => \Delay2_out1_reg[13]_0\(12),
      I5 => Add_out1(12),
      O => \Delay2_out1_reg[12]_0\(6)
    );
\i__carry_i_8__0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"9990009000099909"
    )
        port map (
      I0 => \^u2_norm_1_reg[13]\,
      I1 => Add_out1(13),
      I2 => \Delay1_out1_reg[13]\(12),
      I3 => \^allow_assymetrical_anew_reference_value__0\,
      I4 => \Delay1_out1_reg[13]_0\(12),
      I5 => Add_out1(12),
      O => \Delay1_out1_reg[12]_0\(6)
    );
\i__carry_i_8__1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"A95900000000A959"
    )
        port map (
      I0 => Add_out1(12),
      I1 => \Delay_out1_reg[13]\(12),
      I2 => \^allow_assymetrical_anew_reference_value__0\,
      I3 => \Delay_out1_reg[13]_0\(12),
      I4 => \^relational_operator_1_cast\(13),
      I5 => Add_out1(13),
      O => \Delay_out1_reg[12]_0\(6)
    );
\i__carry_i_8__3\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"6"
    )
        port map (
      I0 => Product_mul_temp_n_88,
      I1 => \Product_mul_temp__0\(0),
      O => \i__carry_i_8__3_n_0\
    );
\i__carry_i_9\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"9990009000099909"
    )
        port map (
      I0 => \^u3_norm_1_reg[12]_0\(11),
      I1 => Add_out1(11),
      I2 => \Delay2_out1_reg[13]\(10),
      I3 => \^allow_assymetrical_anew_reference_value__0\,
      I4 => \Delay2_out1_reg[13]_0\(10),
      I5 => Add_out1(10),
      O => \Delay2_out1_reg[12]_0\(5)
    );
\i__carry_i_9__0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"9990009000099909"
    )
        port map (
      I0 => \^u2_norm_1_reg[12]_0\(11),
      I1 => Add_out1(11),
      I2 => \Delay1_out1_reg[13]\(10),
      I3 => \^allow_assymetrical_anew_reference_value__0\,
      I4 => \Delay1_out1_reg[13]_0\(10),
      I5 => Add_out1(10),
      O => \Delay1_out1_reg[12]_0\(5)
    );
\i__carry_i_9__1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"A95900000000A959"
    )
        port map (
      I0 => Add_out1(10),
      I1 => \Delay_out1_reg[13]\(10),
      I2 => \^allow_assymetrical_anew_reference_value__0\,
      I3 => \Delay_out1_reg[13]_0\(10),
      I4 => \^relational_operator_1_cast\(11),
      I5 => Add_out1(11),
      O => \Delay_out1_reg[12]_0\(5)
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity zusys_PWM_and_SS_control_V_0_2_PWM_and_SS_control_V3_ip_src_LimitPulseWidth is
  port (
    \min_pulse_width_AXI_1_reg[1]\ : out STD_LOGIC_VECTOR ( 0 to 0 );
    \min_pulse_width_AXI_1_reg[1]_0\ : out STD_LOGIC;
    \Delay_out1_reg[12]\ : out STD_LOGIC_VECTOR ( 0 to 0 );
    Add_out1 : out STD_LOGIC_VECTOR ( 13 downto 0 );
    \Delay2_out1_reg[13]\ : out STD_LOGIC_VECTOR ( 0 to 0 );
    DI : out STD_LOGIC_VECTOR ( 6 downto 0 );
    Saturation_out1 : out STD_LOGIC_VECTOR ( 12 downto 0 );
    \Delay1_out1_reg[13]\ : out STD_LOGIC_VECTOR ( 0 to 0 );
    \Delay1_out1_reg[10]\ : out STD_LOGIC_VECTOR ( 6 downto 0 );
    \U1_norm_1_reg[13]\ : out STD_LOGIC_VECTOR ( 0 to 0 );
    \Delay_out1_reg[13]\ : out STD_LOGIC_VECTOR ( 0 to 0 );
    \Delay_out1_reg[0]\ : out STD_LOGIC_VECTOR ( 1 downto 0 );
    HDL_Counter2_count_reg_11_sp_1 : out STD_LOGIC;
    \HDL_Counter2_count_reg[11]_0\ : out STD_LOGIC;
    \HDL_Counter2_count_reg[16]\ : out STD_LOGIC;
    HDL_Counter2_count_reg_1_sp_1 : out STD_LOGIC;
    IPCORE_CLK : out STD_LOGIC_VECTOR ( 1 downto 0 );
    \T_carrier_us_AXI_1_reg[24]\ : out STD_LOGIC_VECTOR ( 0 to 0 );
    \min_pulse_width_AXI_1_reg[17]\ : out STD_LOGIC_VECTOR ( 0 to 0 );
    \min_pulse_width_AXI_1_reg[17]_0\ : out STD_LOGIC_VECTOR ( 0 to 0 );
    S : in STD_LOGIC_VECTOR ( 0 to 0 );
    Switch7_out12_carry_i_7 : in STD_LOGIC_VECTOR ( 0 to 0 );
    Switch7_out12_carry_i_7_0 : in STD_LOGIC_VECTOR ( 0 to 0 );
    Switch7_out12_carry_i_7_1 : in STD_LOGIC_VECTOR ( 6 downto 0 );
    Switch7_out12_carry_i_7_2 : in STD_LOGIC_VECTOR ( 6 downto 0 );
    Q : in STD_LOGIC_VECTOR ( 17 downto 0 );
    \Switch9_out12_carry__0\ : in STD_LOGIC_VECTOR ( 0 to 0 );
    \Switch9_out12_carry__0_0\ : in STD_LOGIC_VECTOR ( 0 to 0 );
    \Switch9_out12_carry__0_1\ : in STD_LOGIC_VECTOR ( 6 downto 0 );
    \Allow_assymetrical_anew_reference_value__0\ : in STD_LOGIC;
    \Switch9_out12_carry__0_2\ : in STD_LOGIC_VECTOR ( 6 downto 0 );
    D : in STD_LOGIC_VECTOR ( 5 downto 0 );
    \Switch8_out12_carry__0\ : in STD_LOGIC_VECTOR ( 0 to 0 );
    \Switch8_out12_carry__0_0\ : in STD_LOGIC_VECTOR ( 0 to 0 );
    \Switch8_out12_carry__0_1\ : in STD_LOGIC_VECTOR ( 6 downto 0 );
    \Switch8_out12_carry__0_2\ : in STD_LOGIC_VECTOR ( 6 downto 0 );
    Logical_Operator_out10_carry_0 : in STD_LOGIC_VECTOR ( 5 downto 0 );
    \Switch7_out12_carry__0\ : in STD_LOGIC_VECTOR ( 6 downto 0 );
    \Switch7_out12_carry__0_0\ : in STD_LOGIC_VECTOR ( 6 downto 0 );
    Logical_Operator_out10_carry_1 : in STD_LOGIC_VECTOR ( 5 downto 0 );
    P : in STD_LOGIC_VECTOR ( 5 downto 0 );
    HDL_Counter2_count_reg : in STD_LOGIC_VECTOR ( 11 downto 0 );
    Counter_Ctrl_out4_1_reg : in STD_LOGIC;
    Counter_Ctrl_out4_1_reg_0 : in STD_LOGIC;
    Counter_Ctrl_out4_1_reg_1 : in STD_LOGIC;
    \Delay_out1[13]_i_2_0\ : in STD_LOGIC;
    \Delay_out1[13]_i_2_1\ : in STD_LOGIC;
    \Delay_out1[13]_i_2_2\ : in STD_LOGIC;
    \Delay_out1[13]_i_2_3\ : in STD_LOGIC;
    Counter_Ctrl_out3_1_reg : in STD_LOGIC_VECTOR ( 0 to 0 )
  );
end zusys_PWM_and_SS_control_V_0_2_PWM_and_SS_control_V3_ip_src_LimitPulseWidth;

architecture STRUCTURE of zusys_PWM_and_SS_control_V_0_2_PWM_and_SS_control_V3_ip_src_LimitPulseWidth is
  signal Counter_Ctrl_out4_1_i_5_n_0 : STD_LOGIC;
  signal Counter_Ctrl_out4_1_i_6_n_0 : STD_LOGIC;
  signal Counter_Ctrl_out4_1_i_7_n_0 : STD_LOGIC;
  signal \Delay_out1[13]_i_3_n_0\ : STD_LOGIC;
  signal \Delay_out1[13]_i_4_n_0\ : STD_LOGIC;
  signal \^delay_out1_reg[12]\ : STD_LOGIC_VECTOR ( 0 to 0 );
  signal \^hdl_counter2_count_reg[11]_0\ : STD_LOGIC;
  signal HDL_Counter2_count_reg_11_sn_1 : STD_LOGIC;
  signal HDL_Counter2_count_reg_1_sn_1 : STD_LOGIC;
  signal \Logical_Operator_out10_carry_i_11__1_n_0\ : STD_LOGIC;
  signal \Logical_Operator_out10_carry_i_12__1_n_0\ : STD_LOGIC;
  signal \Logical_Operator_out10_carry_i_13__1_n_0\ : STD_LOGIC;
  signal \Logical_Operator_out10_carry_i_14__1_n_0\ : STD_LOGIC;
  signal \Logical_Operator_out10_carry_i_15__1_n_0\ : STD_LOGIC;
  signal Logical_Operator_out10_carry_i_16_n_0 : STD_LOGIC;
  signal Logical_Operator_out10_carry_i_17_n_0 : STD_LOGIC;
  signal \Logical_Operator_out10_carry_i_3__1_n_0\ : STD_LOGIC;
  signal \Logical_Operator_out10_carry_i_4__1_n_0\ : STD_LOGIC;
  signal \Logical_Operator_out10_carry_i_5__1_n_0\ : STD_LOGIC;
  signal \Logical_Operator_out10_carry_i_6__1_n_0\ : STD_LOGIC;
  signal \Logical_Operator_out10_carry_i_7__1_n_0\ : STD_LOGIC;
  signal Logical_Operator_out10_carry_i_8_n_0 : STD_LOGIC;
  signal \Logical_Operator_out10_carry_i_9__2_n_0\ : STD_LOGIC;
  signal Logical_Operator_out10_carry_n_1 : STD_LOGIC;
  signal Logical_Operator_out10_carry_n_2 : STD_LOGIC;
  signal Logical_Operator_out10_carry_n_3 : STD_LOGIC;
  signal Logical_Operator_out10_carry_n_4 : STD_LOGIC;
  signal Logical_Operator_out10_carry_n_5 : STD_LOGIC;
  signal Logical_Operator_out10_carry_n_6 : STD_LOGIC;
  signal Logical_Operator_out10_carry_n_7 : STD_LOGIC;
  signal \Logical_Operator_out10_inferred__0/i__carry_n_2\ : STD_LOGIC;
  signal \Logical_Operator_out10_inferred__0/i__carry_n_3\ : STD_LOGIC;
  signal \Logical_Operator_out10_inferred__0/i__carry_n_4\ : STD_LOGIC;
  signal \Logical_Operator_out10_inferred__0/i__carry_n_5\ : STD_LOGIC;
  signal \Logical_Operator_out10_inferred__0/i__carry_n_6\ : STD_LOGIC;
  signal \Logical_Operator_out10_inferred__0/i__carry_n_7\ : STD_LOGIC;
  signal \Logical_Operator_out1__0\ : STD_LOGIC;
  signal \^saturation_out1\ : STD_LOGIC_VECTOR ( 12 downto 0 );
  signal Saturation_out110_in : STD_LOGIC;
  signal \Saturation_out11_inferred__0/i__carry_n_0\ : STD_LOGIC;
  signal \Saturation_out11_inferred__0/i__carry_n_1\ : STD_LOGIC;
  signal \Saturation_out11_inferred__0/i__carry_n_2\ : STD_LOGIC;
  signal \Saturation_out11_inferred__0/i__carry_n_3\ : STD_LOGIC;
  signal \Saturation_out11_inferred__0/i__carry_n_4\ : STD_LOGIC;
  signal \Saturation_out11_inferred__0/i__carry_n_5\ : STD_LOGIC;
  signal \Saturation_out11_inferred__0/i__carry_n_6\ : STD_LOGIC;
  signal \Saturation_out11_inferred__0/i__carry_n_7\ : STD_LOGIC;
  signal Switch7_out12_carry_i_17_n_0 : STD_LOGIC;
  signal \i__carry_i_10__2_n_0\ : STD_LOGIC;
  signal \i__carry_i_11__2_n_0\ : STD_LOGIC;
  signal \i__carry_i_12__2_n_0\ : STD_LOGIC;
  signal \i__carry_i_13__2_n_0\ : STD_LOGIC;
  signal \i__carry_i_14__2_n_0\ : STD_LOGIC;
  signal \i__carry_i_15_n_0\ : STD_LOGIC;
  signal \i__carry_i_16__0_n_0\ : STD_LOGIC;
  signal \i__carry_i_16__0_n_1\ : STD_LOGIC;
  signal \i__carry_i_16__0_n_2\ : STD_LOGIC;
  signal \i__carry_i_16__0_n_3\ : STD_LOGIC;
  signal \i__carry_i_16__0_n_4\ : STD_LOGIC;
  signal \i__carry_i_16__0_n_5\ : STD_LOGIC;
  signal \i__carry_i_16__0_n_6\ : STD_LOGIC;
  signal \i__carry_i_16__0_n_7\ : STD_LOGIC;
  signal \i__carry_i_16_n_0\ : STD_LOGIC;
  signal \i__carry_i_17_n_0\ : STD_LOGIC;
  signal \i__carry_i_17_n_1\ : STD_LOGIC;
  signal \i__carry_i_17_n_2\ : STD_LOGIC;
  signal \i__carry_i_17_n_3\ : STD_LOGIC;
  signal \i__carry_i_17_n_4\ : STD_LOGIC;
  signal \i__carry_i_17_n_5\ : STD_LOGIC;
  signal \i__carry_i_17_n_6\ : STD_LOGIC;
  signal \i__carry_i_17_n_7\ : STD_LOGIC;
  signal \i__carry_i_18_n_0\ : STD_LOGIC;
  signal \i__carry_i_19_n_0\ : STD_LOGIC;
  signal \i__carry_i_1__2_n_0\ : STD_LOGIC;
  signal \i__carry_i_20_n_0\ : STD_LOGIC;
  signal \i__carry_i_21_n_0\ : STD_LOGIC;
  signal \i__carry_i_22_n_0\ : STD_LOGIC;
  signal \i__carry_i_23_n_0\ : STD_LOGIC;
  signal \i__carry_i_24_n_0\ : STD_LOGIC;
  signal \i__carry_i_25_n_0\ : STD_LOGIC;
  signal \i__carry_i_26_n_0\ : STD_LOGIC;
  signal \i__carry_i_27_n_0\ : STD_LOGIC;
  signal \i__carry_i_28_n_0\ : STD_LOGIC;
  signal \i__carry_i_29_n_0\ : STD_LOGIC;
  signal \i__carry_i_2__2_n_0\ : STD_LOGIC;
  signal \i__carry_i_30_n_0\ : STD_LOGIC;
  signal \i__carry_i_31_n_0\ : STD_LOGIC;
  signal \i__carry_i_32_n_0\ : STD_LOGIC;
  signal \i__carry_i_33_n_0\ : STD_LOGIC;
  signal \i__carry_i_34_n_0\ : STD_LOGIC;
  signal \i__carry_i_35_n_0\ : STD_LOGIC;
  signal \i__carry_i_3__2_n_0\ : STD_LOGIC;
  signal \i__carry_i_4__2_n_0\ : STD_LOGIC;
  signal \i__carry_i_5__2_n_0\ : STD_LOGIC;
  signal \i__carry_i_6__2_n_0\ : STD_LOGIC;
  signal \i__carry_i_7__2_n_0\ : STD_LOGIC;
  signal \i__carry_i_8__2_n_0\ : STD_LOGIC;
  signal \i__carry_i_9__2_n_0\ : STD_LOGIC;
  signal \^min_pulse_width_axi_1_reg[1]\ : STD_LOGIC_VECTOR ( 0 to 0 );
  signal \^min_pulse_width_axi_1_reg[1]_0\ : STD_LOGIC;
  signal NLW_Logical_Operator_out10_carry_O_UNCONNECTED : STD_LOGIC_VECTOR ( 7 downto 0 );
  signal \NLW_Logical_Operator_out10_inferred__0/i__carry_CO_UNCONNECTED\ : STD_LOGIC_VECTOR ( 7 to 7 );
  signal \NLW_Logical_Operator_out10_inferred__0/i__carry_O_UNCONNECTED\ : STD_LOGIC_VECTOR ( 7 downto 0 );
  signal \NLW_Saturation_out11_inferred__0/i__carry_O_UNCONNECTED\ : STD_LOGIC_VECTOR ( 7 downto 0 );
  signal \NLW_Saturation_out11_inferred__0/i__carry__0_CO_UNCONNECTED\ : STD_LOGIC_VECTOR ( 7 downto 1 );
  signal \NLW_Saturation_out11_inferred__0/i__carry__0_O_UNCONNECTED\ : STD_LOGIC_VECTOR ( 7 downto 0 );
  signal \NLW_i__carry_i_15__0_CO_UNCONNECTED\ : STD_LOGIC_VECTOR ( 7 downto 0 );
  signal \NLW_i__carry_i_15__0_O_UNCONNECTED\ : STD_LOGIC_VECTOR ( 7 downto 1 );
  signal \NLW_i__carry_i_17_O_UNCONNECTED\ : STD_LOGIC_VECTOR ( 2 downto 0 );
  attribute SOFT_HLUTNM : string;
  attribute SOFT_HLUTNM of Counter_Ctrl_out4_1_i_2 : label is "soft_lutpair15";
  attribute SOFT_HLUTNM of \Delay_out1[13]_i_4\ : label is "soft_lutpair15";
  attribute COMPARATOR_THRESHOLD : integer;
  attribute COMPARATOR_THRESHOLD of Logical_Operator_out10_carry : label is 11;
  attribute SOFT_HLUTNM of Logical_Operator_out10_carry_i_18 : label is "soft_lutpair16";
  attribute SOFT_HLUTNM of Logical_Operator_out10_carry_i_20 : label is "soft_lutpair18";
  attribute SOFT_HLUTNM of Logical_Operator_out10_carry_i_21 : label is "soft_lutpair16";
  attribute SOFT_HLUTNM of Logical_Operator_out10_carry_i_22 : label is "soft_lutpair19";
  attribute SOFT_HLUTNM of Logical_Operator_out10_carry_i_23 : label is "soft_lutpair18";
  attribute SOFT_HLUTNM of Logical_Operator_out10_carry_i_24 : label is "soft_lutpair20";
  attribute SOFT_HLUTNM of Logical_Operator_out10_carry_i_25 : label is "soft_lutpair19";
  attribute SOFT_HLUTNM of Logical_Operator_out10_carry_i_26 : label is "soft_lutpair21";
  attribute SOFT_HLUTNM of Logical_Operator_out10_carry_i_27 : label is "soft_lutpair20";
  attribute SOFT_HLUTNM of Logical_Operator_out10_carry_i_28 : label is "soft_lutpair22";
  attribute SOFT_HLUTNM of Logical_Operator_out10_carry_i_29 : label is "soft_lutpair21";
  attribute SOFT_HLUTNM of Logical_Operator_out10_carry_i_31 : label is "soft_lutpair22";
  attribute COMPARATOR_THRESHOLD of \Logical_Operator_out10_inferred__0/i__carry\ : label is 11;
  attribute COMPARATOR_THRESHOLD of \Saturation_out11_inferred__0/i__carry\ : label is 11;
  attribute COMPARATOR_THRESHOLD of \Saturation_out11_inferred__0/i__carry__0\ : label is 11;
  attribute SOFT_HLUTNM of Switch7_out12_carry_i_17 : label is "soft_lutpair17";
  attribute SOFT_HLUTNM of Switch7_out12_carry_i_18 : label is "soft_lutpair17";
  attribute ADDER_THRESHOLD : integer;
  attribute ADDER_THRESHOLD of \i__carry_i_15__0\ : label is 35;
  attribute ADDER_THRESHOLD of \i__carry_i_16__0\ : label is 35;
  attribute ADDER_THRESHOLD of \i__carry_i_17\ : label is 35;
begin
  \Delay_out1_reg[12]\(0) <= \^delay_out1_reg[12]\(0);
  \HDL_Counter2_count_reg[11]_0\ <= \^hdl_counter2_count_reg[11]_0\;
  HDL_Counter2_count_reg_11_sp_1 <= HDL_Counter2_count_reg_11_sn_1;
  HDL_Counter2_count_reg_1_sp_1 <= HDL_Counter2_count_reg_1_sn_1;
  Saturation_out1(12 downto 0) <= \^saturation_out1\(12 downto 0);
  \min_pulse_width_AXI_1_reg[1]\(0) <= \^min_pulse_width_axi_1_reg[1]\(0);
  \min_pulse_width_AXI_1_reg[1]_0\ <= \^min_pulse_width_axi_1_reg[1]_0\;
Counter_Ctrl_out4_1_i_2: unisim.vcomponents.LUT4
    generic map(
      INIT => X"080A"
    )
        port map (
      I0 => Counter_Ctrl_out4_1_i_5_n_0,
      I1 => HDL_Counter2_count_reg(9),
      I2 => HDL_Counter2_count_reg(10),
      I3 => HDL_Counter2_count_reg(8),
      O => \HDL_Counter2_count_reg[16]\
    );
Counter_Ctrl_out4_1_i_3: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0000000200000000"
    )
        port map (
      I0 => Counter_Ctrl_out4_1_i_6_n_0,
      I1 => HDL_Counter2_count_reg(0),
      I2 => Counter_Ctrl_out4_1_reg,
      I3 => Counter_Ctrl_out4_1_reg_0,
      I4 => Counter_Ctrl_out4_1_reg_1,
      I5 => Counter_Ctrl_out4_1_i_7_n_0,
      O => HDL_Counter2_count_reg_1_sn_1
    );
Counter_Ctrl_out4_1_i_4: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0000000000000001"
    )
        port map (
      I0 => HDL_Counter2_count_reg(4),
      I1 => HDL_Counter2_count_reg(6),
      I2 => HDL_Counter2_count_reg(7),
      I3 => HDL_Counter2_count_reg(9),
      I4 => HDL_Counter2_count_reg(11),
      I5 => HDL_Counter2_count_reg(10),
      O => \^hdl_counter2_count_reg[11]_0\
    );
Counter_Ctrl_out4_1_i_5: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0000230000002323"
    )
        port map (
      I0 => HDL_Counter2_count_reg(6),
      I1 => HDL_Counter2_count_reg(7),
      I2 => HDL_Counter2_count_reg(5),
      I3 => HDL_Counter2_count_reg(3),
      I4 => HDL_Counter2_count_reg(4),
      I5 => HDL_Counter2_count_reg(2),
      O => Counter_Ctrl_out4_1_i_5_n_0
    );
Counter_Ctrl_out4_1_i_6: unisim.vcomponents.LUT4
    generic map(
      INIT => X"0001"
    )
        port map (
      I0 => HDL_Counter2_count_reg(3),
      I1 => HDL_Counter2_count_reg(1),
      I2 => \Delay_out1[13]_i_2_0\,
      I3 => \Delay_out1[13]_i_2_2\,
      O => Counter_Ctrl_out4_1_i_6_n_0
    );
Counter_Ctrl_out4_1_i_7: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0000230000002323"
    )
        port map (
      I0 => \Delay_out1[13]_i_2_0\,
      I1 => HDL_Counter2_count_reg(1),
      I2 => \Delay_out1[13]_i_2_1\,
      I3 => Counter_Ctrl_out4_1_reg_0,
      I4 => \Delay_out1[13]_i_2_2\,
      I5 => \Delay_out1[13]_i_2_3\,
      O => Counter_Ctrl_out4_1_i_7_n_0
    );
\Delay_out1[13]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"8000000000000000"
    )
        port map (
      I0 => \^hdl_counter2_count_reg[11]_0\,
      I1 => Counter_Ctrl_out4_1_i_6_n_0,
      I2 => \Delay_out1[13]_i_3_n_0\,
      I3 => Counter_Ctrl_out4_1_i_7_n_0,
      I4 => \Delay_out1[13]_i_4_n_0\,
      I5 => Counter_Ctrl_out4_1_i_5_n_0,
      O => HDL_Counter2_count_reg_11_sn_1
    );
\Delay_out1[13]_i_3\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"0001"
    )
        port map (
      I0 => HDL_Counter2_count_reg(0),
      I1 => Counter_Ctrl_out4_1_reg,
      I2 => Counter_Ctrl_out4_1_reg_0,
      I3 => Counter_Ctrl_out4_1_reg_1,
      O => \Delay_out1[13]_i_3_n_0\
    );
\Delay_out1[13]_i_4\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"31"
    )
        port map (
      I0 => HDL_Counter2_count_reg(8),
      I1 => HDL_Counter2_count_reg(10),
      I2 => HDL_Counter2_count_reg(9),
      O => \Delay_out1[13]_i_4_n_0\
    );
Logical_Operator_out10_carry: unisim.vcomponents.CARRY8
     port map (
      CI => \^min_pulse_width_axi_1_reg[1]_0\,
      CI_TOP => '0',
      CO(7) => \^min_pulse_width_axi_1_reg[1]\(0),
      CO(6) => Logical_Operator_out10_carry_n_1,
      CO(5) => Logical_Operator_out10_carry_n_2,
      CO(4) => Logical_Operator_out10_carry_n_3,
      CO(3) => Logical_Operator_out10_carry_n_4,
      CO(2) => Logical_Operator_out10_carry_n_5,
      CO(1) => Logical_Operator_out10_carry_n_6,
      CO(0) => Logical_Operator_out10_carry_n_7,
      DI(7) => Switch7_out12_carry_i_7(0),
      DI(6) => \Logical_Operator_out10_carry_i_3__1_n_0\,
      DI(5) => \Logical_Operator_out10_carry_i_4__1_n_0\,
      DI(4) => \Logical_Operator_out10_carry_i_5__1_n_0\,
      DI(3) => \Logical_Operator_out10_carry_i_6__1_n_0\,
      DI(2) => \Logical_Operator_out10_carry_i_7__1_n_0\,
      DI(1) => Logical_Operator_out10_carry_i_8_n_0,
      DI(0) => \Logical_Operator_out10_carry_i_9__2_n_0\,
      O(7 downto 0) => NLW_Logical_Operator_out10_carry_O_UNCONNECTED(7 downto 0),
      S(7) => Switch7_out12_carry_i_7_0(0),
      S(6) => \Logical_Operator_out10_carry_i_11__1_n_0\,
      S(5) => \Logical_Operator_out10_carry_i_12__1_n_0\,
      S(4) => \Logical_Operator_out10_carry_i_13__1_n_0\,
      S(3) => \Logical_Operator_out10_carry_i_14__1_n_0\,
      S(2) => \Logical_Operator_out10_carry_i_15__1_n_0\,
      S(1) => Logical_Operator_out10_carry_i_16_n_0,
      S(0) => Logical_Operator_out10_carry_i_17_n_0
    );
\Logical_Operator_out10_carry_i_11__1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"A95900000000A959"
    )
        port map (
      I0 => \^saturation_out1\(10),
      I1 => \Switch7_out12_carry__0_0\(5),
      I2 => \Allow_assymetrical_anew_reference_value__0\,
      I3 => \Switch7_out12_carry__0\(5),
      I4 => Logical_Operator_out10_carry_1(5),
      I5 => \^saturation_out1\(11),
      O => \Logical_Operator_out10_carry_i_11__1_n_0\
    );
\Logical_Operator_out10_carry_i_12__1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"A95900000000A959"
    )
        port map (
      I0 => \^saturation_out1\(8),
      I1 => \Switch7_out12_carry__0_0\(4),
      I2 => \Allow_assymetrical_anew_reference_value__0\,
      I3 => \Switch7_out12_carry__0\(4),
      I4 => Logical_Operator_out10_carry_1(4),
      I5 => \^saturation_out1\(9),
      O => \Logical_Operator_out10_carry_i_12__1_n_0\
    );
\Logical_Operator_out10_carry_i_13__1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"A95900000000A959"
    )
        port map (
      I0 => \^saturation_out1\(6),
      I1 => \Switch7_out12_carry__0_0\(3),
      I2 => \Allow_assymetrical_anew_reference_value__0\,
      I3 => \Switch7_out12_carry__0\(3),
      I4 => Logical_Operator_out10_carry_1(3),
      I5 => \^saturation_out1\(7),
      O => \Logical_Operator_out10_carry_i_13__1_n_0\
    );
\Logical_Operator_out10_carry_i_14__1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"A95900000000A959"
    )
        port map (
      I0 => \^saturation_out1\(4),
      I1 => \Switch7_out12_carry__0_0\(2),
      I2 => \Allow_assymetrical_anew_reference_value__0\,
      I3 => \Switch7_out12_carry__0\(2),
      I4 => Logical_Operator_out10_carry_1(2),
      I5 => \^saturation_out1\(5),
      O => \Logical_Operator_out10_carry_i_14__1_n_0\
    );
\Logical_Operator_out10_carry_i_15__1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"A95900000000A959"
    )
        port map (
      I0 => \^saturation_out1\(2),
      I1 => \Switch7_out12_carry__0_0\(1),
      I2 => \Allow_assymetrical_anew_reference_value__0\,
      I3 => \Switch7_out12_carry__0\(1),
      I4 => Logical_Operator_out10_carry_1(1),
      I5 => \^saturation_out1\(3),
      O => \Logical_Operator_out10_carry_i_15__1_n_0\
    );
Logical_Operator_out10_carry_i_16: unisim.vcomponents.LUT6
    generic map(
      INIT => X"A95900000000A959"
    )
        port map (
      I0 => \^saturation_out1\(0),
      I1 => \Switch7_out12_carry__0_0\(0),
      I2 => \Allow_assymetrical_anew_reference_value__0\,
      I3 => \Switch7_out12_carry__0\(0),
      I4 => Logical_Operator_out10_carry_1(0),
      I5 => \^saturation_out1\(1),
      O => Logical_Operator_out10_carry_i_16_n_0
    );
\Logical_Operator_out10_carry_i_16__1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"EEEF"
    )
        port map (
      I0 => Q(17),
      I1 => Saturation_out110_in,
      I2 => Q(3),
      I3 => Q(2),
      O => \min_pulse_width_AXI_1_reg[17]\(0)
    );
\Logical_Operator_out10_carry_i_16__2\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"EEEF"
    )
        port map (
      I0 => Q(17),
      I1 => Saturation_out110_in,
      I2 => Q(3),
      I3 => Q(2),
      O => \min_pulse_width_AXI_1_reg[17]_0\(0)
    );
Logical_Operator_out10_carry_i_17: unisim.vcomponents.LUT4
    generic map(
      INIT => X"EEEF"
    )
        port map (
      I0 => Q(17),
      I1 => Saturation_out110_in,
      I2 => Q(3),
      I3 => Q(2),
      O => Logical_Operator_out10_carry_i_17_n_0
    );
Logical_Operator_out10_carry_i_18: unisim.vcomponents.LUT3
    generic map(
      INIT => X"F2"
    )
        port map (
      I0 => Q(16),
      I1 => Q(17),
      I2 => Saturation_out110_in,
      O => \^saturation_out1\(12)
    );
\Logical_Operator_out10_carry_i_1__2\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"000E"
    )
        port map (
      I0 => Q(1),
      I1 => Q(0),
      I2 => Q(17),
      I3 => Saturation_out110_in,
      O => \^min_pulse_width_axi_1_reg[1]_0\
    );
Logical_Operator_out10_carry_i_2: unisim.vcomponents.LUT6
    generic map(
      INIT => X"222222B2B2B222B2"
    )
        port map (
      I0 => \^saturation_out1\(11),
      I1 => D(5),
      I2 => \^saturation_out1\(10),
      I3 => \Switch9_out12_carry__0_1\(5),
      I4 => \Allow_assymetrical_anew_reference_value__0\,
      I5 => \Switch9_out12_carry__0_2\(5),
      O => DI(6)
    );
Logical_Operator_out10_carry_i_20: unisim.vcomponents.LUT3
    generic map(
      INIT => X"02"
    )
        port map (
      I0 => Q(15),
      I1 => Q(17),
      I2 => Saturation_out110_in,
      O => \^saturation_out1\(11)
    );
Logical_Operator_out10_carry_i_21: unisim.vcomponents.LUT3
    generic map(
      INIT => X"02"
    )
        port map (
      I0 => Q(14),
      I1 => Q(17),
      I2 => Saturation_out110_in,
      O => \^saturation_out1\(10)
    );
Logical_Operator_out10_carry_i_22: unisim.vcomponents.LUT3
    generic map(
      INIT => X"02"
    )
        port map (
      I0 => Q(13),
      I1 => Q(17),
      I2 => Saturation_out110_in,
      O => \^saturation_out1\(9)
    );
Logical_Operator_out10_carry_i_23: unisim.vcomponents.LUT3
    generic map(
      INIT => X"02"
    )
        port map (
      I0 => Q(12),
      I1 => Q(17),
      I2 => Saturation_out110_in,
      O => \^saturation_out1\(8)
    );
Logical_Operator_out10_carry_i_24: unisim.vcomponents.LUT3
    generic map(
      INIT => X"02"
    )
        port map (
      I0 => Q(11),
      I1 => Q(17),
      I2 => Saturation_out110_in,
      O => \^saturation_out1\(7)
    );
Logical_Operator_out10_carry_i_25: unisim.vcomponents.LUT3
    generic map(
      INIT => X"02"
    )
        port map (
      I0 => Q(10),
      I1 => Q(17),
      I2 => Saturation_out110_in,
      O => \^saturation_out1\(6)
    );
Logical_Operator_out10_carry_i_26: unisim.vcomponents.LUT3
    generic map(
      INIT => X"02"
    )
        port map (
      I0 => Q(9),
      I1 => Q(17),
      I2 => Saturation_out110_in,
      O => \^saturation_out1\(5)
    );
Logical_Operator_out10_carry_i_27: unisim.vcomponents.LUT3
    generic map(
      INIT => X"02"
    )
        port map (
      I0 => Q(8),
      I1 => Q(17),
      I2 => Saturation_out110_in,
      O => \^saturation_out1\(4)
    );
Logical_Operator_out10_carry_i_28: unisim.vcomponents.LUT3
    generic map(
      INIT => X"02"
    )
        port map (
      I0 => Q(7),
      I1 => Q(17),
      I2 => Saturation_out110_in,
      O => \^saturation_out1\(3)
    );
Logical_Operator_out10_carry_i_29: unisim.vcomponents.LUT3
    generic map(
      INIT => X"02"
    )
        port map (
      I0 => Q(6),
      I1 => Q(17),
      I2 => Saturation_out110_in,
      O => \^saturation_out1\(2)
    );
\Logical_Operator_out10_carry_i_2__0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"222222B2B2B222B2"
    )
        port map (
      I0 => \^saturation_out1\(11),
      I1 => Logical_Operator_out10_carry_0(5),
      I2 => \^saturation_out1\(10),
      I3 => \Switch8_out12_carry__0_1\(5),
      I4 => \Allow_assymetrical_anew_reference_value__0\,
      I5 => \Switch8_out12_carry__0_2\(5),
      O => \Delay1_out1_reg[10]\(6)
    );
Logical_Operator_out10_carry_i_3: unisim.vcomponents.LUT6
    generic map(
      INIT => X"222222B2B2B222B2"
    )
        port map (
      I0 => \^saturation_out1\(9),
      I1 => D(4),
      I2 => \^saturation_out1\(8),
      I3 => \Switch9_out12_carry__0_1\(4),
      I4 => \Allow_assymetrical_anew_reference_value__0\,
      I5 => \Switch9_out12_carry__0_2\(4),
      O => DI(5)
    );
Logical_Operator_out10_carry_i_30: unisim.vcomponents.LUT3
    generic map(
      INIT => X"02"
    )
        port map (
      I0 => Q(5),
      I1 => Q(17),
      I2 => Saturation_out110_in,
      O => \^saturation_out1\(1)
    );
Logical_Operator_out10_carry_i_31: unisim.vcomponents.LUT3
    generic map(
      INIT => X"02"
    )
        port map (
      I0 => Q(4),
      I1 => Q(17),
      I2 => Saturation_out110_in,
      O => \^saturation_out1\(0)
    );
\Logical_Operator_out10_carry_i_3__0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"222222B2B2B222B2"
    )
        port map (
      I0 => \^saturation_out1\(9),
      I1 => Logical_Operator_out10_carry_0(4),
      I2 => \^saturation_out1\(8),
      I3 => \Switch8_out12_carry__0_1\(4),
      I4 => \Allow_assymetrical_anew_reference_value__0\,
      I5 => \Switch8_out12_carry__0_2\(4),
      O => \Delay1_out1_reg[10]\(5)
    );
\Logical_Operator_out10_carry_i_3__1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"222222B2B2B222B2"
    )
        port map (
      I0 => \^saturation_out1\(11),
      I1 => Logical_Operator_out10_carry_1(5),
      I2 => \^saturation_out1\(10),
      I3 => \Switch7_out12_carry__0_0\(5),
      I4 => \Allow_assymetrical_anew_reference_value__0\,
      I5 => \Switch7_out12_carry__0\(5),
      O => \Logical_Operator_out10_carry_i_3__1_n_0\
    );
Logical_Operator_out10_carry_i_4: unisim.vcomponents.LUT6
    generic map(
      INIT => X"222222B2B2B222B2"
    )
        port map (
      I0 => \^saturation_out1\(7),
      I1 => D(3),
      I2 => \^saturation_out1\(6),
      I3 => \Switch9_out12_carry__0_1\(3),
      I4 => \Allow_assymetrical_anew_reference_value__0\,
      I5 => \Switch9_out12_carry__0_2\(3),
      O => DI(4)
    );
\Logical_Operator_out10_carry_i_4__0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"222222B2B2B222B2"
    )
        port map (
      I0 => \^saturation_out1\(7),
      I1 => Logical_Operator_out10_carry_0(3),
      I2 => \^saturation_out1\(6),
      I3 => \Switch8_out12_carry__0_1\(3),
      I4 => \Allow_assymetrical_anew_reference_value__0\,
      I5 => \Switch8_out12_carry__0_2\(3),
      O => \Delay1_out1_reg[10]\(4)
    );
\Logical_Operator_out10_carry_i_4__1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"222222B2B2B222B2"
    )
        port map (
      I0 => \^saturation_out1\(9),
      I1 => Logical_Operator_out10_carry_1(4),
      I2 => \^saturation_out1\(8),
      I3 => \Switch7_out12_carry__0_0\(4),
      I4 => \Allow_assymetrical_anew_reference_value__0\,
      I5 => \Switch7_out12_carry__0\(4),
      O => \Logical_Operator_out10_carry_i_4__1_n_0\
    );
Logical_Operator_out10_carry_i_5: unisim.vcomponents.LUT6
    generic map(
      INIT => X"222222B2B2B222B2"
    )
        port map (
      I0 => \^saturation_out1\(5),
      I1 => D(2),
      I2 => \^saturation_out1\(4),
      I3 => \Switch9_out12_carry__0_1\(2),
      I4 => \Allow_assymetrical_anew_reference_value__0\,
      I5 => \Switch9_out12_carry__0_2\(2),
      O => DI(3)
    );
\Logical_Operator_out10_carry_i_5__0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"222222B2B2B222B2"
    )
        port map (
      I0 => \^saturation_out1\(5),
      I1 => Logical_Operator_out10_carry_0(2),
      I2 => \^saturation_out1\(4),
      I3 => \Switch8_out12_carry__0_1\(2),
      I4 => \Allow_assymetrical_anew_reference_value__0\,
      I5 => \Switch8_out12_carry__0_2\(2),
      O => \Delay1_out1_reg[10]\(3)
    );
\Logical_Operator_out10_carry_i_5__1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"222222B2B2B222B2"
    )
        port map (
      I0 => \^saturation_out1\(7),
      I1 => Logical_Operator_out10_carry_1(3),
      I2 => \^saturation_out1\(6),
      I3 => \Switch7_out12_carry__0_0\(3),
      I4 => \Allow_assymetrical_anew_reference_value__0\,
      I5 => \Switch7_out12_carry__0\(3),
      O => \Logical_Operator_out10_carry_i_5__1_n_0\
    );
Logical_Operator_out10_carry_i_6: unisim.vcomponents.LUT6
    generic map(
      INIT => X"222222B2B2B222B2"
    )
        port map (
      I0 => \^saturation_out1\(3),
      I1 => D(1),
      I2 => \^saturation_out1\(2),
      I3 => \Switch9_out12_carry__0_1\(1),
      I4 => \Allow_assymetrical_anew_reference_value__0\,
      I5 => \Switch9_out12_carry__0_2\(1),
      O => DI(2)
    );
\Logical_Operator_out10_carry_i_6__0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"222222B2B2B222B2"
    )
        port map (
      I0 => \^saturation_out1\(3),
      I1 => Logical_Operator_out10_carry_0(1),
      I2 => \^saturation_out1\(2),
      I3 => \Switch8_out12_carry__0_1\(1),
      I4 => \Allow_assymetrical_anew_reference_value__0\,
      I5 => \Switch8_out12_carry__0_2\(1),
      O => \Delay1_out1_reg[10]\(2)
    );
\Logical_Operator_out10_carry_i_6__1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"222222B2B2B222B2"
    )
        port map (
      I0 => \^saturation_out1\(5),
      I1 => Logical_Operator_out10_carry_1(2),
      I2 => \^saturation_out1\(4),
      I3 => \Switch7_out12_carry__0_0\(2),
      I4 => \Allow_assymetrical_anew_reference_value__0\,
      I5 => \Switch7_out12_carry__0\(2),
      O => \Logical_Operator_out10_carry_i_6__1_n_0\
    );
Logical_Operator_out10_carry_i_7: unisim.vcomponents.LUT6
    generic map(
      INIT => X"222222B2B2B222B2"
    )
        port map (
      I0 => \^saturation_out1\(1),
      I1 => D(0),
      I2 => \^saturation_out1\(0),
      I3 => \Switch9_out12_carry__0_1\(0),
      I4 => \Allow_assymetrical_anew_reference_value__0\,
      I5 => \Switch9_out12_carry__0_2\(0),
      O => DI(1)
    );
\Logical_Operator_out10_carry_i_7__0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"222222B2B2B222B2"
    )
        port map (
      I0 => \^saturation_out1\(1),
      I1 => Logical_Operator_out10_carry_0(0),
      I2 => \^saturation_out1\(0),
      I3 => \Switch8_out12_carry__0_1\(0),
      I4 => \Allow_assymetrical_anew_reference_value__0\,
      I5 => \Switch8_out12_carry__0_2\(0),
      O => \Delay1_out1_reg[10]\(1)
    );
\Logical_Operator_out10_carry_i_7__1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"222222B2B2B222B2"
    )
        port map (
      I0 => \^saturation_out1\(3),
      I1 => Logical_Operator_out10_carry_1(1),
      I2 => \^saturation_out1\(2),
      I3 => \Switch7_out12_carry__0_0\(1),
      I4 => \Allow_assymetrical_anew_reference_value__0\,
      I5 => \Switch7_out12_carry__0\(1),
      O => \Logical_Operator_out10_carry_i_7__1_n_0\
    );
Logical_Operator_out10_carry_i_8: unisim.vcomponents.LUT6
    generic map(
      INIT => X"222222B2B2B222B2"
    )
        port map (
      I0 => \^saturation_out1\(1),
      I1 => Logical_Operator_out10_carry_1(0),
      I2 => \^saturation_out1\(0),
      I3 => \Switch7_out12_carry__0_0\(0),
      I4 => \Allow_assymetrical_anew_reference_value__0\,
      I5 => \Switch7_out12_carry__0\(0),
      O => Logical_Operator_out10_carry_i_8_n_0
    );
\Logical_Operator_out10_carry_i_8__1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"000E"
    )
        port map (
      I0 => Q(2),
      I1 => Q(3),
      I2 => Saturation_out110_in,
      I3 => Q(17),
      O => DI(0)
    );
\Logical_Operator_out10_carry_i_8__2\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"000E"
    )
        port map (
      I0 => Q(2),
      I1 => Q(3),
      I2 => Saturation_out110_in,
      I3 => Q(17),
      O => \Delay1_out1_reg[10]\(0)
    );
\Logical_Operator_out10_carry_i_9__2\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"000E"
    )
        port map (
      I0 => Q(2),
      I1 => Q(3),
      I2 => Saturation_out110_in,
      I3 => Q(17),
      O => \Logical_Operator_out10_carry_i_9__2_n_0\
    );
\Logical_Operator_out10_inferred__0/i__carry\: unisim.vcomponents.CARRY8
     port map (
      CI => '0',
      CI_TOP => '0',
      CO(7) => \NLW_Logical_Operator_out10_inferred__0/i__carry_CO_UNCONNECTED\(7),
      CO(6) => \^delay_out1_reg[12]\(0),
      CO(5) => \Logical_Operator_out10_inferred__0/i__carry_n_2\,
      CO(4) => \Logical_Operator_out10_inferred__0/i__carry_n_3\,
      CO(3) => \Logical_Operator_out10_inferred__0/i__carry_n_4\,
      CO(2) => \Logical_Operator_out10_inferred__0/i__carry_n_5\,
      CO(1) => \Logical_Operator_out10_inferred__0/i__carry_n_6\,
      CO(0) => \Logical_Operator_out10_inferred__0/i__carry_n_7\,
      DI(7) => '0',
      DI(6 downto 0) => Switch7_out12_carry_i_7_1(6 downto 0),
      O(7 downto 0) => \NLW_Logical_Operator_out10_inferred__0/i__carry_O_UNCONNECTED\(7 downto 0),
      S(7) => '0',
      S(6 downto 0) => Switch7_out12_carry_i_7_2(6 downto 0)
    );
\Period_CenterMax0_carry__0_i_1\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => Counter_Ctrl_out3_1_reg(0),
      O => \T_carrier_us_AXI_1_reg[24]\(0)
    );
\Saturation_out11_inferred__0/i__carry\: unisim.vcomponents.CARRY8
     port map (
      CI => '0',
      CI_TOP => '0',
      CO(7) => \Saturation_out11_inferred__0/i__carry_n_0\,
      CO(6) => \Saturation_out11_inferred__0/i__carry_n_1\,
      CO(5) => \Saturation_out11_inferred__0/i__carry_n_2\,
      CO(4) => \Saturation_out11_inferred__0/i__carry_n_3\,
      CO(3) => \Saturation_out11_inferred__0/i__carry_n_4\,
      CO(2) => \Saturation_out11_inferred__0/i__carry_n_5\,
      CO(1) => \Saturation_out11_inferred__0/i__carry_n_6\,
      CO(0) => \Saturation_out11_inferred__0/i__carry_n_7\,
      DI(7) => \i__carry_i_1__2_n_0\,
      DI(6) => \i__carry_i_2__2_n_0\,
      DI(5) => \i__carry_i_3__2_n_0\,
      DI(4) => \i__carry_i_4__2_n_0\,
      DI(3) => \i__carry_i_5__2_n_0\,
      DI(2) => \i__carry_i_6__2_n_0\,
      DI(1) => \i__carry_i_7__2_n_0\,
      DI(0) => \i__carry_i_8__2_n_0\,
      O(7 downto 0) => \NLW_Saturation_out11_inferred__0/i__carry_O_UNCONNECTED\(7 downto 0),
      S(7) => \i__carry_i_9__2_n_0\,
      S(6) => \i__carry_i_10__2_n_0\,
      S(5) => \i__carry_i_11__2_n_0\,
      S(4) => \i__carry_i_12__2_n_0\,
      S(3) => \i__carry_i_13__2_n_0\,
      S(2) => \i__carry_i_14__2_n_0\,
      S(1) => \i__carry_i_15_n_0\,
      S(0) => \i__carry_i_16_n_0\
    );
\Saturation_out11_inferred__0/i__carry__0\: unisim.vcomponents.CARRY8
     port map (
      CI => \Saturation_out11_inferred__0/i__carry_n_0\,
      CI_TOP => '0',
      CO(7 downto 1) => \NLW_Saturation_out11_inferred__0/i__carry__0_CO_UNCONNECTED\(7 downto 1),
      CO(0) => Saturation_out110_in,
      DI(7 downto 0) => B"00000000",
      O(7 downto 0) => \NLW_Saturation_out11_inferred__0/i__carry__0_O_UNCONNECTED\(7 downto 0),
      S(7 downto 1) => B"0000000",
      S(0) => S(0)
    );
\Switch7_out12_carry__0_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"000000B8"
    )
        port map (
      I0 => \Switch7_out12_carry__0\(6),
      I1 => \Allow_assymetrical_anew_reference_value__0\,
      I2 => \Switch7_out12_carry__0_0\(6),
      I3 => \^delay_out1_reg[12]\(0),
      I4 => \^min_pulse_width_axi_1_reg[1]\(0),
      O => \U1_norm_1_reg[13]\(0)
    );
\Switch7_out12_carry__0_i_3\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"EEEFFFEF"
    )
        port map (
      I0 => \^min_pulse_width_axi_1_reg[1]\(0),
      I1 => \^delay_out1_reg[12]\(0),
      I2 => \Switch7_out12_carry__0_0\(6),
      I3 => \Allow_assymetrical_anew_reference_value__0\,
      I4 => \Switch7_out12_carry__0\(6),
      O => \Delay_out1_reg[13]\(0)
    );
Switch7_out12_carry_i_15: unisim.vcomponents.LUT4
    generic map(
      INIT => X"200D"
    )
        port map (
      I0 => \^delay_out1_reg[12]\(0),
      I1 => \^min_pulse_width_axi_1_reg[1]\(0),
      I2 => P(2),
      I3 => P(3),
      O => IPCORE_CLK(1)
    );
Switch7_out12_carry_i_16: unisim.vcomponents.LUT4
    generic map(
      INIT => X"020D"
    )
        port map (
      I0 => \^delay_out1_reg[12]\(0),
      I1 => \^min_pulse_width_axi_1_reg[1]\(0),
      I2 => P(0),
      I3 => P(1),
      O => IPCORE_CLK(0)
    );
Switch7_out12_carry_i_17: unisim.vcomponents.LUT3
    generic map(
      INIT => X"8A"
    )
        port map (
      I0 => P(4),
      I1 => \^min_pulse_width_axi_1_reg[1]\(0),
      I2 => \^delay_out1_reg[12]\(0),
      O => Switch7_out12_carry_i_17_n_0
    );
Switch7_out12_carry_i_18: unisim.vcomponents.LUT2
    generic map(
      INIT => X"E"
    )
        port map (
      I0 => \^delay_out1_reg[12]\(0),
      I1 => \^min_pulse_width_axi_1_reg[1]\(0),
      O => \Logical_Operator_out1__0\
    );
Switch7_out12_carry_i_6: unisim.vcomponents.LUT6
    generic map(
      INIT => X"E8E8E8EEEEEEE8EE"
    )
        port map (
      I0 => Switch7_out12_carry_i_17_n_0,
      I1 => P(5),
      I2 => \Logical_Operator_out1__0\,
      I3 => \Switch7_out12_carry__0_0\(0),
      I4 => \Allow_assymetrical_anew_reference_value__0\,
      I5 => \Switch7_out12_carry__0\(0),
      O => \Delay_out1_reg[0]\(1)
    );
Switch7_out12_carry_i_8: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FDD0"
    )
        port map (
      I0 => \^delay_out1_reg[12]\(0),
      I1 => \^min_pulse_width_axi_1_reg[1]\(0),
      I2 => P(0),
      I3 => P(1),
      O => \Delay_out1_reg[0]\(0)
    );
\Switch8_out12_carry__0_i_3\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"EEEFFFEF"
    )
        port map (
      I0 => \Switch8_out12_carry__0\(0),
      I1 => \Switch8_out12_carry__0_0\(0),
      I2 => \Switch8_out12_carry__0_1\(6),
      I3 => \Allow_assymetrical_anew_reference_value__0\,
      I4 => \Switch8_out12_carry__0_2\(6),
      O => \Delay1_out1_reg[13]\(0)
    );
\Switch9_out12_carry__0_i_3\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"EEEFFFEF"
    )
        port map (
      I0 => \Switch9_out12_carry__0\(0),
      I1 => \Switch9_out12_carry__0_0\(0),
      I2 => \Switch9_out12_carry__0_1\(6),
      I3 => \Allow_assymetrical_anew_reference_value__0\,
      I4 => \Switch9_out12_carry__0_2\(6),
      O => \Delay2_out1_reg[13]\(0)
    );
\i__carry_i_10__2\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => Q(13),
      I1 => Q(12),
      O => \i__carry_i_10__2_n_0\
    );
\i__carry_i_11__2\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => Q(11),
      I1 => Q(10),
      O => \i__carry_i_11__2_n_0\
    );
\i__carry_i_12__2\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => Q(9),
      I1 => Q(8),
      O => \i__carry_i_12__2_n_0\
    );
\i__carry_i_13__2\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => Q(7),
      I1 => Q(6),
      O => \i__carry_i_13__2_n_0\
    );
\i__carry_i_14__2\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => Q(5),
      I1 => Q(4),
      O => \i__carry_i_14__2_n_0\
    );
\i__carry_i_15\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => Q(3),
      I1 => Q(2),
      O => \i__carry_i_15_n_0\
    );
\i__carry_i_15__0\: unisim.vcomponents.CARRY8
     port map (
      CI => \i__carry_i_16__0_n_0\,
      CI_TOP => '0',
      CO(7 downto 0) => \NLW_i__carry_i_15__0_CO_UNCONNECTED\(7 downto 0),
      DI(7 downto 0) => B"00000000",
      O(7 downto 1) => \NLW_i__carry_i_15__0_O_UNCONNECTED\(7 downto 1),
      O(0) => Add_out1(13),
      S(7 downto 1) => B"0000000",
      S(0) => \i__carry_i_18_n_0\
    );
\i__carry_i_16\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => Q(1),
      I1 => Q(0),
      O => \i__carry_i_16_n_0\
    );
\i__carry_i_16__0\: unisim.vcomponents.CARRY8
     port map (
      CI => \i__carry_i_17_n_0\,
      CI_TOP => '0',
      CO(7) => \i__carry_i_16__0_n_0\,
      CO(6) => \i__carry_i_16__0_n_1\,
      CO(5) => \i__carry_i_16__0_n_2\,
      CO(4) => \i__carry_i_16__0_n_3\,
      CO(3) => \i__carry_i_16__0_n_4\,
      CO(2) => \i__carry_i_16__0_n_5\,
      CO(1) => \i__carry_i_16__0_n_6\,
      CO(0) => \i__carry_i_16__0_n_7\,
      DI(7) => \i__carry_i_19_n_0\,
      DI(6 downto 0) => B"0000000",
      O(7 downto 0) => Add_out1(12 downto 5),
      S(7) => Q(16),
      S(6) => \i__carry_i_20_n_0\,
      S(5) => \i__carry_i_21_n_0\,
      S(4) => \i__carry_i_22_n_0\,
      S(3) => \i__carry_i_23_n_0\,
      S(2) => \i__carry_i_24_n_0\,
      S(1) => \i__carry_i_25_n_0\,
      S(0) => \i__carry_i_26_n_0\
    );
\i__carry_i_17\: unisim.vcomponents.CARRY8
     port map (
      CI => \i__carry_i_27_n_0\,
      CI_TOP => '0',
      CO(7) => \i__carry_i_17_n_0\,
      CO(6) => \i__carry_i_17_n_1\,
      CO(5) => \i__carry_i_17_n_2\,
      CO(4) => \i__carry_i_17_n_3\,
      CO(3) => \i__carry_i_17_n_4\,
      CO(2) => \i__carry_i_17_n_5\,
      CO(1) => \i__carry_i_17_n_6\,
      CO(0) => \i__carry_i_17_n_7\,
      DI(7 downto 0) => B"00000000",
      O(7 downto 3) => Add_out1(4 downto 0),
      O(2 downto 0) => \NLW_i__carry_i_17_O_UNCONNECTED\(2 downto 0),
      S(7) => \i__carry_i_28_n_0\,
      S(6) => \i__carry_i_29_n_0\,
      S(5) => \i__carry_i_30_n_0\,
      S(4) => \i__carry_i_31_n_0\,
      S(3) => \i__carry_i_32_n_0\,
      S(2) => \i__carry_i_33_n_0\,
      S(1) => \i__carry_i_34_n_0\,
      S(0) => \i__carry_i_35_n_0\
    );
\i__carry_i_18\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => Q(17),
      O => \i__carry_i_18_n_0\
    );
\i__carry_i_19\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => Q(16),
      O => \i__carry_i_19_n_0\
    );
\i__carry_i_1__2\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"E"
    )
        port map (
      I0 => Q(14),
      I1 => Q(15),
      O => \i__carry_i_1__2_n_0\
    );
\i__carry_i_20\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => Q(15),
      O => \i__carry_i_20_n_0\
    );
\i__carry_i_21\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => Q(14),
      O => \i__carry_i_21_n_0\
    );
\i__carry_i_22\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => Q(13),
      O => \i__carry_i_22_n_0\
    );
\i__carry_i_23\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => Q(12),
      O => \i__carry_i_23_n_0\
    );
\i__carry_i_24\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => Q(11),
      O => \i__carry_i_24_n_0\
    );
\i__carry_i_25\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => Q(10),
      O => \i__carry_i_25_n_0\
    );
\i__carry_i_26\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => Q(9),
      O => \i__carry_i_26_n_0\
    );
\i__carry_i_27\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => Q(0),
      O => \i__carry_i_27_n_0\
    );
\i__carry_i_28\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => Q(8),
      O => \i__carry_i_28_n_0\
    );
\i__carry_i_29\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => Q(7),
      O => \i__carry_i_29_n_0\
    );
\i__carry_i_2__2\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"E"
    )
        port map (
      I0 => Q(12),
      I1 => Q(13),
      O => \i__carry_i_2__2_n_0\
    );
\i__carry_i_30\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => Q(6),
      O => \i__carry_i_30_n_0\
    );
\i__carry_i_31\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => Q(5),
      O => \i__carry_i_31_n_0\
    );
\i__carry_i_32\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => Q(4),
      O => \i__carry_i_32_n_0\
    );
\i__carry_i_33\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => Q(3),
      O => \i__carry_i_33_n_0\
    );
\i__carry_i_34\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => Q(2),
      O => \i__carry_i_34_n_0\
    );
\i__carry_i_35\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => Q(1),
      O => \i__carry_i_35_n_0\
    );
\i__carry_i_3__2\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"E"
    )
        port map (
      I0 => Q(10),
      I1 => Q(11),
      O => \i__carry_i_3__2_n_0\
    );
\i__carry_i_4__2\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"E"
    )
        port map (
      I0 => Q(8),
      I1 => Q(9),
      O => \i__carry_i_4__2_n_0\
    );
\i__carry_i_5__2\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"E"
    )
        port map (
      I0 => Q(6),
      I1 => Q(7),
      O => \i__carry_i_5__2_n_0\
    );
\i__carry_i_6__2\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"E"
    )
        port map (
      I0 => Q(4),
      I1 => Q(5),
      O => \i__carry_i_6__2_n_0\
    );
\i__carry_i_7__2\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"E"
    )
        port map (
      I0 => Q(2),
      I1 => Q(3),
      O => \i__carry_i_7__2_n_0\
    );
\i__carry_i_8__2\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"E"
    )
        port map (
      I0 => Q(0),
      I1 => Q(1),
      O => \i__carry_i_8__2_n_0\
    );
\i__carry_i_9__2\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => Q(15),
      I1 => Q(14),
      O => \i__carry_i_9__2_n_0\
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity zusys_PWM_and_SS_control_V_0_2_PWM_and_SS_control_V3_ip_src_LimitPulseWidth1 is
  port (
    \min_pulse_width_AXI_1_reg[1]\ : out STD_LOGIC_VECTOR ( 0 to 0 );
    \Delay1_out1_reg[12]\ : out STD_LOGIC_VECTOR ( 0 to 0 );
    Switch8_out12_carry_i_7 : in STD_LOGIC;
    DI : in STD_LOGIC_VECTOR ( 7 downto 0 );
    S : in STD_LOGIC_VECTOR ( 7 downto 0 );
    Switch8_out12_carry_i_7_0 : in STD_LOGIC_VECTOR ( 6 downto 0 );
    Switch8_out12_carry_i_7_1 : in STD_LOGIC_VECTOR ( 6 downto 0 )
  );
end zusys_PWM_and_SS_control_V_0_2_PWM_and_SS_control_V3_ip_src_LimitPulseWidth1;

architecture STRUCTURE of zusys_PWM_and_SS_control_V_0_2_PWM_and_SS_control_V3_ip_src_LimitPulseWidth1 is
  signal Logical_Operator_out10_carry_n_1 : STD_LOGIC;
  signal Logical_Operator_out10_carry_n_2 : STD_LOGIC;
  signal Logical_Operator_out10_carry_n_3 : STD_LOGIC;
  signal Logical_Operator_out10_carry_n_4 : STD_LOGIC;
  signal Logical_Operator_out10_carry_n_5 : STD_LOGIC;
  signal Logical_Operator_out10_carry_n_6 : STD_LOGIC;
  signal Logical_Operator_out10_carry_n_7 : STD_LOGIC;
  signal \Logical_Operator_out10_inferred__0/i__carry_n_2\ : STD_LOGIC;
  signal \Logical_Operator_out10_inferred__0/i__carry_n_3\ : STD_LOGIC;
  signal \Logical_Operator_out10_inferred__0/i__carry_n_4\ : STD_LOGIC;
  signal \Logical_Operator_out10_inferred__0/i__carry_n_5\ : STD_LOGIC;
  signal \Logical_Operator_out10_inferred__0/i__carry_n_6\ : STD_LOGIC;
  signal \Logical_Operator_out10_inferred__0/i__carry_n_7\ : STD_LOGIC;
  signal NLW_Logical_Operator_out10_carry_O_UNCONNECTED : STD_LOGIC_VECTOR ( 7 downto 0 );
  signal \NLW_Logical_Operator_out10_inferred__0/i__carry_CO_UNCONNECTED\ : STD_LOGIC_VECTOR ( 7 to 7 );
  signal \NLW_Logical_Operator_out10_inferred__0/i__carry_O_UNCONNECTED\ : STD_LOGIC_VECTOR ( 7 downto 0 );
  attribute COMPARATOR_THRESHOLD : integer;
  attribute COMPARATOR_THRESHOLD of Logical_Operator_out10_carry : label is 11;
  attribute COMPARATOR_THRESHOLD of \Logical_Operator_out10_inferred__0/i__carry\ : label is 11;
begin
Logical_Operator_out10_carry: unisim.vcomponents.CARRY8
     port map (
      CI => Switch8_out12_carry_i_7,
      CI_TOP => '0',
      CO(7) => \min_pulse_width_AXI_1_reg[1]\(0),
      CO(6) => Logical_Operator_out10_carry_n_1,
      CO(5) => Logical_Operator_out10_carry_n_2,
      CO(4) => Logical_Operator_out10_carry_n_3,
      CO(3) => Logical_Operator_out10_carry_n_4,
      CO(2) => Logical_Operator_out10_carry_n_5,
      CO(1) => Logical_Operator_out10_carry_n_6,
      CO(0) => Logical_Operator_out10_carry_n_7,
      DI(7 downto 0) => DI(7 downto 0),
      O(7 downto 0) => NLW_Logical_Operator_out10_carry_O_UNCONNECTED(7 downto 0),
      S(7 downto 0) => S(7 downto 0)
    );
\Logical_Operator_out10_inferred__0/i__carry\: unisim.vcomponents.CARRY8
     port map (
      CI => '0',
      CI_TOP => '0',
      CO(7) => \NLW_Logical_Operator_out10_inferred__0/i__carry_CO_UNCONNECTED\(7),
      CO(6) => \Delay1_out1_reg[12]\(0),
      CO(5) => \Logical_Operator_out10_inferred__0/i__carry_n_2\,
      CO(4) => \Logical_Operator_out10_inferred__0/i__carry_n_3\,
      CO(3) => \Logical_Operator_out10_inferred__0/i__carry_n_4\,
      CO(2) => \Logical_Operator_out10_inferred__0/i__carry_n_5\,
      CO(1) => \Logical_Operator_out10_inferred__0/i__carry_n_6\,
      CO(0) => \Logical_Operator_out10_inferred__0/i__carry_n_7\,
      DI(7) => '0',
      DI(6 downto 0) => Switch8_out12_carry_i_7_0(6 downto 0),
      O(7 downto 0) => \NLW_Logical_Operator_out10_inferred__0/i__carry_O_UNCONNECTED\(7 downto 0),
      S(7) => '0',
      S(6 downto 0) => Switch8_out12_carry_i_7_1(6 downto 0)
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity zusys_PWM_and_SS_control_V_0_2_PWM_and_SS_control_V3_ip_src_LimitPulseWidth2 is
  port (
    \min_pulse_width_AXI_1_reg[1]\ : out STD_LOGIC_VECTOR ( 0 to 0 );
    \Delay2_out1_reg[12]\ : out STD_LOGIC_VECTOR ( 0 to 0 );
    Switch9_out12_carry_i_7 : in STD_LOGIC;
    DI : in STD_LOGIC_VECTOR ( 7 downto 0 );
    S : in STD_LOGIC_VECTOR ( 7 downto 0 );
    Switch9_out12_carry_i_7_0 : in STD_LOGIC_VECTOR ( 6 downto 0 );
    Switch9_out12_carry_i_7_1 : in STD_LOGIC_VECTOR ( 6 downto 0 )
  );
end zusys_PWM_and_SS_control_V_0_2_PWM_and_SS_control_V3_ip_src_LimitPulseWidth2;

architecture STRUCTURE of zusys_PWM_and_SS_control_V_0_2_PWM_and_SS_control_V3_ip_src_LimitPulseWidth2 is
  signal Logical_Operator_out10_carry_n_1 : STD_LOGIC;
  signal Logical_Operator_out10_carry_n_2 : STD_LOGIC;
  signal Logical_Operator_out10_carry_n_3 : STD_LOGIC;
  signal Logical_Operator_out10_carry_n_4 : STD_LOGIC;
  signal Logical_Operator_out10_carry_n_5 : STD_LOGIC;
  signal Logical_Operator_out10_carry_n_6 : STD_LOGIC;
  signal Logical_Operator_out10_carry_n_7 : STD_LOGIC;
  signal \Logical_Operator_out10_inferred__0/i__carry_n_2\ : STD_LOGIC;
  signal \Logical_Operator_out10_inferred__0/i__carry_n_3\ : STD_LOGIC;
  signal \Logical_Operator_out10_inferred__0/i__carry_n_4\ : STD_LOGIC;
  signal \Logical_Operator_out10_inferred__0/i__carry_n_5\ : STD_LOGIC;
  signal \Logical_Operator_out10_inferred__0/i__carry_n_6\ : STD_LOGIC;
  signal \Logical_Operator_out10_inferred__0/i__carry_n_7\ : STD_LOGIC;
  signal NLW_Logical_Operator_out10_carry_O_UNCONNECTED : STD_LOGIC_VECTOR ( 7 downto 0 );
  signal \NLW_Logical_Operator_out10_inferred__0/i__carry_CO_UNCONNECTED\ : STD_LOGIC_VECTOR ( 7 to 7 );
  signal \NLW_Logical_Operator_out10_inferred__0/i__carry_O_UNCONNECTED\ : STD_LOGIC_VECTOR ( 7 downto 0 );
  attribute COMPARATOR_THRESHOLD : integer;
  attribute COMPARATOR_THRESHOLD of Logical_Operator_out10_carry : label is 11;
  attribute COMPARATOR_THRESHOLD of \Logical_Operator_out10_inferred__0/i__carry\ : label is 11;
begin
Logical_Operator_out10_carry: unisim.vcomponents.CARRY8
     port map (
      CI => Switch9_out12_carry_i_7,
      CI_TOP => '0',
      CO(7) => \min_pulse_width_AXI_1_reg[1]\(0),
      CO(6) => Logical_Operator_out10_carry_n_1,
      CO(5) => Logical_Operator_out10_carry_n_2,
      CO(4) => Logical_Operator_out10_carry_n_3,
      CO(3) => Logical_Operator_out10_carry_n_4,
      CO(2) => Logical_Operator_out10_carry_n_5,
      CO(1) => Logical_Operator_out10_carry_n_6,
      CO(0) => Logical_Operator_out10_carry_n_7,
      DI(7 downto 0) => DI(7 downto 0),
      O(7 downto 0) => NLW_Logical_Operator_out10_carry_O_UNCONNECTED(7 downto 0),
      S(7 downto 0) => S(7 downto 0)
    );
\Logical_Operator_out10_inferred__0/i__carry\: unisim.vcomponents.CARRY8
     port map (
      CI => '0',
      CI_TOP => '0',
      CO(7) => \NLW_Logical_Operator_out10_inferred__0/i__carry_CO_UNCONNECTED\(7),
      CO(6) => \Delay2_out1_reg[12]\(0),
      CO(5) => \Logical_Operator_out10_inferred__0/i__carry_n_2\,
      CO(4) => \Logical_Operator_out10_inferred__0/i__carry_n_3\,
      CO(3) => \Logical_Operator_out10_inferred__0/i__carry_n_4\,
      CO(2) => \Logical_Operator_out10_inferred__0/i__carry_n_5\,
      CO(1) => \Logical_Operator_out10_inferred__0/i__carry_n_6\,
      CO(0) => \Logical_Operator_out10_inferred__0/i__carry_n_7\,
      DI(7) => '0',
      DI(6 downto 0) => Switch9_out12_carry_i_7_0(6 downto 0),
      O(7 downto 0) => \NLW_Logical_Operator_out10_inferred__0/i__carry_O_UNCONNECTED\(7 downto 0),
      S(7) => '0',
      S(6 downto 0) => Switch9_out12_carry_i_7_1(6 downto 0)
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity zusys_PWM_and_SS_control_V_0_2_PWM_and_SS_control_V3_ip_src_VSI_Control_Signal_Switch is
  port (
    Q : out STD_LOGIC_VECTOR ( 1 downto 0 );
    SS0_OUT : out STD_LOGIC;
    SS1_OUT : out STD_LOGIC;
    SS2_OUT : out STD_LOGIC;
    SS3_OUT : out STD_LOGIC;
    SS4_OUT : out STD_LOGIC;
    SS5_OUT : out STD_LOGIC;
    reset : in STD_LOGIC;
    E : in STD_LOGIC_VECTOR ( 0 to 0 );
    \reduced_reg_1_reg[0][1]_0\ : in STD_LOGIC_VECTOR ( 1 downto 0 );
    IPCORE_CLK : in STD_LOGIC;
    SS0_IN_External : in STD_LOGIC;
    \reduced_reg_reg[0][1]_0\ : in STD_LOGIC_VECTOR ( 1 downto 0 );
    SS1_IN_External : in STD_LOGIC;
    SS2_IN_External : in STD_LOGIC;
    \reduced_reg_2_reg[0][1]_0\ : in STD_LOGIC_VECTOR ( 1 downto 0 );
    SS3_IN_External : in STD_LOGIC;
    SS4_IN_External : in STD_LOGIC;
    \reduced_reg_3_reg[0][1]_0\ : in STD_LOGIC_VECTOR ( 1 downto 0 );
    SS5_IN_External : in STD_LOGIC;
    GenPWM_out1 : in STD_LOGIC;
    GenPWM_out2 : in STD_LOGIC;
    GenPWM_out3 : in STD_LOGIC;
    GenPWM_out4 : in STD_LOGIC;
    GenPWM_out5 : in STD_LOGIC;
    GenPWM_out6 : in STD_LOGIC
  );
end zusys_PWM_and_SS_control_V_0_2_PWM_and_SS_control_V3_ip_src_VSI_Control_Signal_Switch;

architecture STRUCTURE of zusys_PWM_and_SS_control_V_0_2_PWM_and_SS_control_V3_ip_src_VSI_Control_Signal_Switch is
  signal \^q\ : STD_LOGIC_VECTOR ( 1 downto 0 );
  signal delayMatch12_reg : STD_LOGIC_VECTOR ( 1 to 1 );
  signal \delayMatch12_reg_reg_n_0_[0]\ : STD_LOGIC;
  signal delayMatch15_reg : STD_LOGIC_VECTOR ( 1 to 1 );
  signal \delayMatch15_reg_reg_n_0_[0]\ : STD_LOGIC;
  signal delayMatch3_reg : STD_LOGIC_VECTOR ( 1 to 1 );
  signal \delayMatch3_reg_reg_n_0_[0]\ : STD_LOGIC;
  signal delayMatch6_reg : STD_LOGIC_VECTOR ( 1 to 1 );
  signal \delayMatch6_reg_reg_n_0_[0]\ : STD_LOGIC;
  signal delayMatch9_reg : STD_LOGIC_VECTOR ( 1 to 1 );
  signal \delayMatch9_reg_reg_n_0_[0]\ : STD_LOGIC;
  signal delayMatch_reg : STD_LOGIC_VECTOR ( 1 to 1 );
  signal \delayMatch_reg_reg[0]_0\ : STD_LOGIC_VECTOR ( 1 downto 0 );
  signal \delayMatch_reg_reg_n_0_[0]\ : STD_LOGIC;
  signal \reduced_reg_2_reg[0]_2\ : STD_LOGIC_VECTOR ( 1 downto 0 );
  signal \reduced_reg_2_reg_n_0_[1][0]\ : STD_LOGIC;
  signal \reduced_reg_2_reg_n_0_[1][1]\ : STD_LOGIC;
  signal \reduced_reg_3_reg[0]_3\ : STD_LOGIC_VECTOR ( 1 downto 0 );
  signal \reduced_reg_3_reg_n_0_[1][0]\ : STD_LOGIC;
  signal \reduced_reg_3_reg_n_0_[1][1]\ : STD_LOGIC;
  signal \reduced_reg_reg[0]_1\ : STD_LOGIC_VECTOR ( 1 downto 0 );
  signal \reduced_reg_reg_n_0_[1][0]\ : STD_LOGIC;
  signal \reduced_reg_reg_n_0_[1][1]\ : STD_LOGIC;
begin
  Q(1 downto 0) <= \^q\(1 downto 0);
Switch10_out1: unisim.vcomponents.LUT5
    generic map(
      INIT => X"000000E2"
    )
        port map (
      I0 => GenPWM_out5,
      I1 => \^q\(1),
      I2 => delayMatch12_reg(1),
      I3 => \reduced_reg_3_reg_n_0_[1][0]\,
      I4 => \reduced_reg_3_reg_n_0_[1][1]\,
      O => SS4_OUT
    );
Switch11_out1: unisim.vcomponents.LUT5
    generic map(
      INIT => X"000000E2"
    )
        port map (
      I0 => GenPWM_out6,
      I1 => \^q\(1),
      I2 => delayMatch15_reg(1),
      I3 => \reduced_reg_3_reg_n_0_[1][0]\,
      I4 => \reduced_reg_3_reg_n_0_[1][1]\,
      O => SS5_OUT
    );
Switch6_out1: unisim.vcomponents.LUT5
    generic map(
      INIT => X"000000E2"
    )
        port map (
      I0 => GenPWM_out1,
      I1 => \^q\(1),
      I2 => delayMatch_reg(1),
      I3 => \reduced_reg_reg_n_0_[1][0]\,
      I4 => \reduced_reg_reg_n_0_[1][1]\,
      O => SS0_OUT
    );
Switch7_out1: unisim.vcomponents.LUT5
    generic map(
      INIT => X"000000E2"
    )
        port map (
      I0 => GenPWM_out2,
      I1 => \^q\(1),
      I2 => delayMatch3_reg(1),
      I3 => \reduced_reg_reg_n_0_[1][0]\,
      I4 => \reduced_reg_reg_n_0_[1][1]\,
      O => SS1_OUT
    );
Switch8_out1: unisim.vcomponents.LUT5
    generic map(
      INIT => X"000000E2"
    )
        port map (
      I0 => GenPWM_out3,
      I1 => \^q\(1),
      I2 => delayMatch6_reg(1),
      I3 => \reduced_reg_2_reg_n_0_[1][0]\,
      I4 => \reduced_reg_2_reg_n_0_[1][1]\,
      O => SS2_OUT
    );
Switch9_out1: unisim.vcomponents.LUT5
    generic map(
      INIT => X"000000E2"
    )
        port map (
      I0 => GenPWM_out4,
      I1 => \^q\(1),
      I2 => delayMatch9_reg(1),
      I3 => \reduced_reg_2_reg_n_0_[1][0]\,
      I4 => \reduced_reg_2_reg_n_0_[1][1]\,
      O => SS3_OUT
    );
\delayMatch12_reg_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => SS4_IN_External,
      Q => \delayMatch12_reg_reg_n_0_[0]\,
      R => reset
    );
\delayMatch12_reg_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => \delayMatch12_reg_reg_n_0_[0]\,
      Q => delayMatch12_reg(1),
      R => reset
    );
\delayMatch15_reg_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => SS5_IN_External,
      Q => \delayMatch15_reg_reg_n_0_[0]\,
      R => reset
    );
\delayMatch15_reg_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => \delayMatch15_reg_reg_n_0_[0]\,
      Q => delayMatch15_reg(1),
      R => reset
    );
\delayMatch3_reg_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => SS1_IN_External,
      Q => \delayMatch3_reg_reg_n_0_[0]\,
      R => reset
    );
\delayMatch3_reg_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => \delayMatch3_reg_reg_n_0_[0]\,
      Q => delayMatch3_reg(1),
      R => reset
    );
\delayMatch6_reg_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => SS2_IN_External,
      Q => \delayMatch6_reg_reg_n_0_[0]\,
      R => reset
    );
\delayMatch6_reg_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => \delayMatch6_reg_reg_n_0_[0]\,
      Q => delayMatch6_reg(1),
      R => reset
    );
\delayMatch9_reg_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => SS3_IN_External,
      Q => \delayMatch9_reg_reg_n_0_[0]\,
      R => reset
    );
\delayMatch9_reg_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => \delayMatch9_reg_reg_n_0_[0]\,
      Q => delayMatch9_reg(1),
      R => reset
    );
\delayMatch_reg_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => SS0_IN_External,
      Q => \delayMatch_reg_reg_n_0_[0]\,
      R => reset
    );
\delayMatch_reg_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => \delayMatch_reg_reg_n_0_[0]\,
      Q => delayMatch_reg(1),
      R => reset
    );
\reduced_reg_1_reg[0][0]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => \reduced_reg_1_reg[0][1]_0\(0),
      Q => \delayMatch_reg_reg[0]_0\(0),
      R => reset
    );
\reduced_reg_1_reg[0][1]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => \reduced_reg_1_reg[0][1]_0\(1),
      Q => \delayMatch_reg_reg[0]_0\(1),
      R => reset
    );
\reduced_reg_1_reg[1][0]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => \delayMatch_reg_reg[0]_0\(0),
      Q => \^q\(0),
      R => reset
    );
\reduced_reg_1_reg[1][1]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => \delayMatch_reg_reg[0]_0\(1),
      Q => \^q\(1),
      R => reset
    );
\reduced_reg_2_reg[0][0]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => \reduced_reg_2_reg[0][1]_0\(0),
      Q => \reduced_reg_2_reg[0]_2\(0),
      R => reset
    );
\reduced_reg_2_reg[0][1]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => \reduced_reg_2_reg[0][1]_0\(1),
      Q => \reduced_reg_2_reg[0]_2\(1),
      R => reset
    );
\reduced_reg_2_reg[1][0]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => \reduced_reg_2_reg[0]_2\(0),
      Q => \reduced_reg_2_reg_n_0_[1][0]\,
      R => reset
    );
\reduced_reg_2_reg[1][1]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => \reduced_reg_2_reg[0]_2\(1),
      Q => \reduced_reg_2_reg_n_0_[1][1]\,
      R => reset
    );
\reduced_reg_3_reg[0][0]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => \reduced_reg_3_reg[0][1]_0\(0),
      Q => \reduced_reg_3_reg[0]_3\(0),
      R => reset
    );
\reduced_reg_3_reg[0][1]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => \reduced_reg_3_reg[0][1]_0\(1),
      Q => \reduced_reg_3_reg[0]_3\(1),
      R => reset
    );
\reduced_reg_3_reg[1][0]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => \reduced_reg_3_reg[0]_3\(0),
      Q => \reduced_reg_3_reg_n_0_[1][0]\,
      R => reset
    );
\reduced_reg_3_reg[1][1]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => \reduced_reg_3_reg[0]_3\(1),
      Q => \reduced_reg_3_reg_n_0_[1][1]\,
      R => reset
    );
\reduced_reg_reg[0][0]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => \reduced_reg_reg[0][1]_0\(0),
      Q => \reduced_reg_reg[0]_1\(0),
      R => reset
    );
\reduced_reg_reg[0][1]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => \reduced_reg_reg[0][1]_0\(1),
      Q => \reduced_reg_reg[0]_1\(1),
      R => reset
    );
\reduced_reg_reg[1][0]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => \reduced_reg_reg[0]_1\(0),
      Q => \reduced_reg_reg_n_0_[1][0]\,
      R => reset
    );
\reduced_reg_reg[1][1]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => \reduced_reg_reg[0]_1\(1),
      Q => \reduced_reg_reg_n_0_[1][1]\,
      R => reset
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity zusys_PWM_and_SS_control_V_0_2_PWM_and_SS_control_V3_ip_axi_lite is
  port (
    FSM_sequential_axi_lite_rstate_reg : out STD_LOGIC;
    reset : out STD_LOGIC;
    CEA1 : out STD_LOGIC;
    write_PWM_en_AXI : out STD_LOGIC;
    AXI4_Lite_ARREADY : out STD_LOGIC;
    Q : out STD_LOGIC_VECTOR ( 1 downto 0 );
    AXI4_Lite_AWREADY : out STD_LOGIC;
    CEB2 : out STD_LOGIC;
    \write_reg_Mode_AXI_reg[1]\ : out STD_LOGIC_VECTOR ( 1 downto 0 );
    \write_reg_Scal_f_carrier_AXI_reg[24]\ : out STD_LOGIC_VECTOR ( 24 downto 0 );
    \write_reg_Scal_T_carrier_AXI_reg[24]\ : out STD_LOGIC_VECTOR ( 24 downto 0 );
    \write_reg_PWM_min_pulse_width_AXI_reg[17]\ : out STD_LOGIC_VECTOR ( 17 downto 0 );
    \write_reg_m_u1_norm_AXI_reg[13]\ : out STD_LOGIC_VECTOR ( 13 downto 0 );
    \write_reg_m_u2_norm_AXI_reg[13]\ : out STD_LOGIC_VECTOR ( 13 downto 0 );
    \write_reg_m_u3_norm_AXI_reg[13]\ : out STD_LOGIC_VECTOR ( 13 downto 0 );
    \write_reg_TriState_HB1_AXI_reg[1]\ : out STD_LOGIC_VECTOR ( 1 downto 0 );
    \write_reg_TriState_HB2_AXI_reg[1]\ : out STD_LOGIC_VECTOR ( 1 downto 0 );
    \write_reg_TriState_HB3_AXI_reg[1]\ : out STD_LOGIC_VECTOR ( 1 downto 0 );
    AXI4_Lite_RDATA : out STD_LOGIC_VECTOR ( 26 downto 0 );
    AXI4_Lite_ACLK : in STD_LOGIC;
    PWM_en_rd_AXI_sig : in STD_LOGIC;
    AXI4_Lite_ARVALID : in STD_LOGIC;
    AXI4_Lite_ARADDR : in STD_LOGIC_VECTOR ( 13 downto 0 );
    AXI4_Lite_RREADY : in STD_LOGIC;
    AXI4_Lite_AWVALID : in STD_LOGIC;
    AXI4_Lite_WVALID : in STD_LOGIC;
    AXI4_Lite_ARESETN : in STD_LOGIC;
    PWM_en_AXI_1 : in STD_LOGIC;
    IPCORE_RESETN : in STD_LOGIC;
    AXI4_Lite_BREADY : in STD_LOGIC;
    AXI4_Lite_WSTRB : in STD_LOGIC_VECTOR ( 3 downto 0 );
    AXI4_Lite_AWADDR : in STD_LOGIC_VECTOR ( 13 downto 0 );
    AXI4_Lite_WDATA : in STD_LOGIC_VECTOR ( 24 downto 0 );
    D : in STD_LOGIC_VECTOR ( 24 downto 0 );
    \read_reg_PWM_T_carrier_us_rd_AXI_reg[24]\ : in STD_LOGIC_VECTOR ( 24 downto 0 );
    \read_reg_PWM_min_pulse_width_rd_AXI_reg[17]\ : in STD_LOGIC_VECTOR ( 17 downto 0 );
    \read_reg_Mode_rd_AXI_reg[1]\ : in STD_LOGIC_VECTOR ( 1 downto 0 )
  );
end zusys_PWM_and_SS_control_V_0_2_PWM_and_SS_control_V3_ip_axi_lite;

architecture STRUCTURE of zusys_PWM_and_SS_control_V_0_2_PWM_and_SS_control_V3_ip_axi_lite is
  signal \^cea1\ : STD_LOGIC;
  signal read_reg_Mode_rd_AXI : STD_LOGIC_VECTOR ( 1 downto 0 );
  signal read_reg_PWM_T_carrier_us_rd_AXI : STD_LOGIC_VECTOR ( 24 downto 0 );
  signal read_reg_PWM_en_rd_AXI : STD_LOGIC;
  signal read_reg_PWM_f_carrier_kHz_rd_AXI : STD_LOGIC_VECTOR ( 24 downto 0 );
  signal read_reg_PWM_min_pulse_width_rd_AXI : STD_LOGIC_VECTOR ( 17 downto 0 );
  signal read_reg_ip_timestamp : STD_LOGIC_VECTOR ( 30 to 30 );
  signal reg_enb_Mode_AXI : STD_LOGIC;
  signal reg_enb_PWM_min_pulse_width_AXI : STD_LOGIC;
  signal reg_enb_Scal_T_carrier_AXI : STD_LOGIC;
  signal reg_enb_Scal_f_carrier_AXI : STD_LOGIC;
  signal reg_enb_TriState_HB1_AXI : STD_LOGIC;
  signal reg_enb_TriState_HB2_AXI : STD_LOGIC;
  signal reg_enb_TriState_HB3_AXI : STD_LOGIC;
  signal reg_enb_m_u1_norm_AXI : STD_LOGIC;
  signal reg_enb_m_u2_norm_AXI : STD_LOGIC;
  signal reg_enb_m_u3_norm_AXI : STD_LOGIC;
  signal \^reset\ : STD_LOGIC;
  signal u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_1 : STD_LOGIC;
  signal u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_10 : STD_LOGIC;
  signal u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_11 : STD_LOGIC;
  signal u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_12 : STD_LOGIC;
  signal u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_13 : STD_LOGIC;
  signal u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_14 : STD_LOGIC;
  signal u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_15 : STD_LOGIC;
  signal u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_16 : STD_LOGIC;
  signal u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_17 : STD_LOGIC;
  signal u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_18 : STD_LOGIC;
  signal u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_19 : STD_LOGIC;
  signal u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_2 : STD_LOGIC;
  signal u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_20 : STD_LOGIC;
  signal u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_21 : STD_LOGIC;
  signal u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_22 : STD_LOGIC;
  signal u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_23 : STD_LOGIC;
  signal u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_24 : STD_LOGIC;
  signal u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_25 : STD_LOGIC;
  signal u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_26 : STD_LOGIC;
  signal u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_27 : STD_LOGIC;
  signal u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_3 : STD_LOGIC;
  signal u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_4 : STD_LOGIC;
  signal u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_5 : STD_LOGIC;
  signal u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_6 : STD_LOGIC;
  signal u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_7 : STD_LOGIC;
  signal u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_8 : STD_LOGIC;
  signal u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_9 : STD_LOGIC;
  signal \^write_pwm_en_axi\ : STD_LOGIC;
begin
  CEA1 <= \^cea1\;
  reset <= \^reset\;
  write_PWM_en_AXI <= \^write_pwm_en_axi\;
u_PWM_and_SS_control_V3_ip_addr_decoder_inst: entity work.zusys_PWM_and_SS_control_V_0_2_PWM_and_SS_control_V3_ip_addr_decoder
     port map (
      AXI4_Lite_ACLK => AXI4_Lite_ACLK,
      CEA1 => \^cea1\,
      CEB2 => CEB2,
      D(24 downto 0) => D(24 downto 0),
      E(0) => reg_enb_Mode_AXI,
      PWM_en_AXI_1 => PWM_en_AXI_1,
      PWM_en_rd_AXI_sig => PWM_en_rd_AXI_sig,
      Q(24) => u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_2,
      Q(23) => u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_3,
      Q(22) => u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_4,
      Q(21) => u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_5,
      Q(20) => u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_6,
      Q(19) => u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_7,
      Q(18) => u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_8,
      Q(17) => u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_9,
      Q(16) => u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_10,
      Q(15) => u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_11,
      Q(14) => u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_12,
      Q(13) => u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_13,
      Q(12) => u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_14,
      Q(11) => u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_15,
      Q(10) => u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_16,
      Q(9) => u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_17,
      Q(8) => u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_18,
      Q(7) => u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_19,
      Q(6) => u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_20,
      Q(5) => u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_21,
      Q(4) => u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_22,
      Q(3) => u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_23,
      Q(2) => u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_24,
      Q(1) => u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_25,
      Q(0) => u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_26,
      SR(0) => \^reset\,
      \read_reg_Mode_rd_AXI_reg[1]_0\(1 downto 0) => read_reg_Mode_rd_AXI(1 downto 0),
      \read_reg_Mode_rd_AXI_reg[1]_1\(1 downto 0) => \read_reg_Mode_rd_AXI_reg[1]\(1 downto 0),
      \read_reg_PWM_T_carrier_us_rd_AXI_reg[24]_0\(24 downto 0) => read_reg_PWM_T_carrier_us_rd_AXI(24 downto 0),
      \read_reg_PWM_T_carrier_us_rd_AXI_reg[24]_1\(24 downto 0) => \read_reg_PWM_T_carrier_us_rd_AXI_reg[24]\(24 downto 0),
      read_reg_PWM_en_rd_AXI => read_reg_PWM_en_rd_AXI,
      \read_reg_PWM_f_carrier_kHz_rd_AXI_reg[24]_0\(24 downto 0) => read_reg_PWM_f_carrier_kHz_rd_AXI(24 downto 0),
      \read_reg_PWM_min_pulse_width_rd_AXI_reg[17]_0\(17 downto 0) => read_reg_PWM_min_pulse_width_rd_AXI(17 downto 0),
      \read_reg_PWM_min_pulse_width_rd_AXI_reg[17]_1\(17 downto 0) => \read_reg_PWM_min_pulse_width_rd_AXI_reg[17]\(17 downto 0),
      read_reg_ip_timestamp(0) => read_reg_ip_timestamp(30),
      write_PWM_en_AXI => \^write_pwm_en_axi\,
      \write_reg_Mode_AXI_reg[1]_0\(1 downto 0) => \write_reg_Mode_AXI_reg[1]\(1 downto 0),
      write_reg_PWM_en_AXI_reg_0 => u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_27,
      \write_reg_PWM_min_pulse_width_AXI_reg[17]_0\(17 downto 0) => \write_reg_PWM_min_pulse_width_AXI_reg[17]\(17 downto 0),
      \write_reg_PWM_min_pulse_width_AXI_reg[17]_1\(0) => reg_enb_PWM_min_pulse_width_AXI,
      \write_reg_Scal_T_carrier_AXI_reg[24]_0\(24 downto 0) => \write_reg_Scal_T_carrier_AXI_reg[24]\(24 downto 0),
      \write_reg_Scal_T_carrier_AXI_reg[24]_1\(0) => reg_enb_Scal_T_carrier_AXI,
      \write_reg_Scal_f_carrier_AXI_reg[24]_0\(24 downto 0) => \write_reg_Scal_f_carrier_AXI_reg[24]\(24 downto 0),
      \write_reg_Scal_f_carrier_AXI_reg[24]_1\(0) => reg_enb_Scal_f_carrier_AXI,
      \write_reg_TriState_HB1_AXI_reg[1]_0\(1 downto 0) => \write_reg_TriState_HB1_AXI_reg[1]\(1 downto 0),
      \write_reg_TriState_HB1_AXI_reg[1]_1\(0) => reg_enb_TriState_HB1_AXI,
      \write_reg_TriState_HB2_AXI_reg[1]_0\(1 downto 0) => \write_reg_TriState_HB2_AXI_reg[1]\(1 downto 0),
      \write_reg_TriState_HB2_AXI_reg[1]_1\(0) => reg_enb_TriState_HB2_AXI,
      \write_reg_TriState_HB3_AXI_reg[1]_0\(1 downto 0) => \write_reg_TriState_HB3_AXI_reg[1]\(1 downto 0),
      \write_reg_TriState_HB3_AXI_reg[1]_1\(0) => reg_enb_TriState_HB3_AXI,
      write_reg_axi_enable_reg_0 => u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_1,
      \write_reg_m_u1_norm_AXI_reg[13]_0\(13 downto 0) => \write_reg_m_u1_norm_AXI_reg[13]\(13 downto 0),
      \write_reg_m_u1_norm_AXI_reg[13]_1\(0) => reg_enb_m_u1_norm_AXI,
      \write_reg_m_u2_norm_AXI_reg[13]_0\(13 downto 0) => \write_reg_m_u2_norm_AXI_reg[13]\(13 downto 0),
      \write_reg_m_u2_norm_AXI_reg[13]_1\(0) => reg_enb_m_u2_norm_AXI,
      \write_reg_m_u3_norm_AXI_reg[13]_0\(13 downto 0) => \write_reg_m_u3_norm_AXI_reg[13]\(13 downto 0),
      \write_reg_m_u3_norm_AXI_reg[13]_1\(0) => reg_enb_m_u3_norm_AXI
    );
u_PWM_and_SS_control_V3_ip_axi_lite_module_inst: entity work.zusys_PWM_and_SS_control_V_0_2_PWM_and_SS_control_V3_ip_axi_lite_module
     port map (
      AXI4_Lite_ACLK => AXI4_Lite_ACLK,
      AXI4_Lite_ARADDR(13 downto 0) => AXI4_Lite_ARADDR(13 downto 0),
      \AXI4_Lite_ARADDR[3]\(0) => reg_enb_TriState_HB3_AXI,
      \AXI4_Lite_ARADDR[3]_0\(0) => reg_enb_m_u3_norm_AXI,
      \AXI4_Lite_ARADDR[3]_1\(0) => reg_enb_m_u2_norm_AXI,
      \AXI4_Lite_ARADDR[3]_2\(0) => reg_enb_PWM_min_pulse_width_AXI,
      \AXI4_Lite_ARADDR[3]_3\(0) => reg_enb_Scal_f_carrier_AXI,
      \AXI4_Lite_ARADDR[4]\(0) => reg_enb_m_u1_norm_AXI,
      \AXI4_Lite_ARADDR[6]\(0) => reg_enb_TriState_HB2_AXI,
      \AXI4_Lite_ARADDR[6]_0\(0) => reg_enb_TriState_HB1_AXI,
      AXI4_Lite_ARESETN => AXI4_Lite_ARESETN,
      AXI4_Lite_ARREADY => AXI4_Lite_ARREADY,
      AXI4_Lite_ARVALID => AXI4_Lite_ARVALID,
      AXI4_Lite_AWADDR(13 downto 0) => AXI4_Lite_AWADDR(13 downto 0),
      AXI4_Lite_AWREADY => AXI4_Lite_AWREADY,
      AXI4_Lite_AWVALID => AXI4_Lite_AWVALID,
      AXI4_Lite_BREADY => AXI4_Lite_BREADY,
      AXI4_Lite_RDATA(26 downto 0) => AXI4_Lite_RDATA(26 downto 0),
      \AXI4_Lite_RDATA_tmp_reg[1]_0\(1 downto 0) => read_reg_Mode_rd_AXI(1 downto 0),
      \AXI4_Lite_RDATA_tmp_reg[24]_0\(24 downto 0) => read_reg_PWM_f_carrier_kHz_rd_AXI(24 downto 0),
      \AXI4_Lite_RDATA_tmp_reg[24]_1\(24 downto 0) => read_reg_PWM_T_carrier_us_rd_AXI(24 downto 0),
      \AXI4_Lite_RDATA_tmp_reg[30]_0\(17 downto 0) => read_reg_PWM_min_pulse_width_rd_AXI(17 downto 0),
      AXI4_Lite_RREADY => AXI4_Lite_RREADY,
      AXI4_Lite_WDATA(24 downto 0) => AXI4_Lite_WDATA(24 downto 0),
      AXI4_Lite_WSTRB(3 downto 0) => AXI4_Lite_WSTRB(3 downto 0),
      AXI4_Lite_WVALID => AXI4_Lite_WVALID,
      CEA1 => \^cea1\,
      E(0) => reg_enb_Mode_AXI,
      \FSM_onehot_axi_lite_wstate_reg[2]_0\(1 downto 0) => Q(1 downto 0),
      FSM_sequential_axi_lite_rstate_reg_0 => FSM_sequential_axi_lite_rstate_reg,
      IPCORE_RESETN => IPCORE_RESETN,
      Q(24) => u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_2,
      Q(23) => u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_3,
      Q(22) => u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_4,
      Q(21) => u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_5,
      Q(20) => u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_6,
      Q(19) => u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_7,
      Q(18) => u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_8,
      Q(17) => u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_9,
      Q(16) => u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_10,
      Q(15) => u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_11,
      Q(14) => u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_12,
      Q(13) => u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_13,
      Q(12) => u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_14,
      Q(11) => u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_15,
      Q(10) => u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_16,
      Q(9) => u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_17,
      Q(8) => u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_18,
      Q(7) => u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_19,
      Q(6) => u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_20,
      Q(5) => u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_21,
      Q(4) => u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_22,
      Q(3) => u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_23,
      Q(2) => u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_24,
      Q(1) => u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_25,
      Q(0) => u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_26,
      read_reg_PWM_en_rd_AXI => read_reg_PWM_en_rd_AXI,
      read_reg_ip_timestamp(0) => read_reg_ip_timestamp(30),
      reset => \^reset\,
      \waddr_reg[3]_0\(0) => reg_enb_Scal_T_carrier_AXI,
      \wdata_reg[0]_0\ => u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_1,
      \wdata_reg[0]_1\ => u_PWM_and_SS_control_V3_ip_axi_lite_module_inst_n_27,
      write_PWM_en_AXI => \^write_pwm_en_axi\
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity zusys_PWM_and_SS_control_V_0_2_PWM_and_SS_control_V3_ip_src_GenPWM is
  port (
    PWM_en_AXI_1_reg_0 : out STD_LOGIC;
    GenPWM_out1 : out STD_LOGIC;
    GenPWM_out2 : out STD_LOGIC;
    GenPWM_out3 : out STD_LOGIC;
    GenPWM_out4 : out STD_LOGIC;
    GenPWM_out5 : out STD_LOGIC;
    GenPWM_out6 : out STD_LOGIC;
    PWM_en_rd_AXI_sig : out STD_LOGIC;
    PWM_enb_out : out STD_LOGIC;
    Triangular_Max : out STD_LOGIC;
    Triangular_Min : out STD_LOGIC;
    \Product_mul_temp[-1111111111]\ : out STD_LOGIC;
    \Product_mul_temp[-1111111110]\ : out STD_LOGIC;
    \Product_mul_temp[-1111111109]\ : out STD_LOGIC;
    \Product_mul_temp[-1111111108]\ : out STD_LOGIC;
    \Product_mul_temp[-1111111107]\ : out STD_LOGIC;
    \Product_mul_temp[-1111111106]\ : out STD_LOGIC;
    \Product_mul_temp[-1111111105]\ : out STD_LOGIC;
    \Product_mul_temp[-1111111104]\ : out STD_LOGIC;
    \Product_mul_temp[-1111111103]\ : out STD_LOGIC;
    \f_carrier_kHz_AXI_2_reg[24]_0\ : out STD_LOGIC_VECTOR ( 15 downto 0 );
    DI : out STD_LOGIC_VECTOR ( 1 downto 0 );
    \HDL_Counter2_count_reg[2]_0\ : out STD_LOGIC;
    \HDL_Counter2_count_reg[3]_0\ : out STD_LOGIC;
    \HDL_Counter2_count_reg[4]_0\ : out STD_LOGIC;
    \HDL_Counter2_count_reg[5]_0\ : out STD_LOGIC;
    \HDL_Counter2_count_reg[6]_0\ : out STD_LOGIC;
    \HDL_Counter2_count_reg[7]_0\ : out STD_LOGIC;
    S : out STD_LOGIC_VECTOR ( 7 downto 0 );
    \HDL_Counter2_count_reg[0]_0\ : out STD_LOGIC_VECTOR ( 0 to 0 );
    Q : out STD_LOGIC_VECTOR ( 24 downto 0 );
    \min_pulse_width_AXI_2_reg[17]_0\ : out STD_LOGIC_VECTOR ( 17 downto 0 );
    reset : in STD_LOGIC;
    E : in STD_LOGIC_VECTOR ( 0 to 0 );
    IPCORE_CLK : in STD_LOGIC;
    CEB2 : in STD_LOGIC;
    B : in STD_LOGIC_VECTOR ( 7 downto 0 );
    D : in STD_LOGIC_VECTOR ( 24 downto 0 );
    write_PWM_en_AXI : in STD_LOGIC;
    CO : in STD_LOGIC_VECTOR ( 0 to 0 );
    \T_carrier_us_AXI_1_reg[24]_0\ : in STD_LOGIC_VECTOR ( 24 downto 0 );
    \min_pulse_width_AXI_1_reg[17]_0\ : in STD_LOGIC_VECTOR ( 17 downto 0 );
    \U1_norm_1_reg[13]_0\ : in STD_LOGIC_VECTOR ( 13 downto 0 );
    \U2_norm_1_reg[13]_0\ : in STD_LOGIC_VECTOR ( 13 downto 0 );
    \U3_norm_1_reg[13]_0\ : in STD_LOGIC_VECTOR ( 13 downto 0 )
  );
end zusys_PWM_and_SS_control_V_0_2_PWM_and_SS_control_V3_ip_src_GenPWM;

architecture STRUCTURE of zusys_PWM_and_SS_control_V_0_2_PWM_and_SS_control_V3_ip_src_GenPWM is
  signal Add_out1 : STD_LOGIC_VECTOR ( 17 downto 4 );
  signal \Allow_assymetrical_anew_reference_value__0\ : STD_LOGIC;
  signal Counter_Ctrl_out3 : STD_LOGIC;
  signal Counter_Ctrl_out4 : STD_LOGIC;
  signal \^di\ : STD_LOGIC_VECTOR ( 1 downto 0 );
  signal Delay1_out1 : STD_LOGIC_VECTOR ( 13 downto 0 );
  signal Delay2_out1 : STD_LOGIC_VECTOR ( 13 downto 0 );
  signal Delay_out1 : STD_LOGIC_VECTOR ( 13 downto 0 );
  signal Demux1_out2_i_1_n_0 : STD_LOGIC;
  signal Demux2_out2_i_1_n_0 : STD_LOGIC;
  signal Demux_out2_i_1_n_0 : STD_LOGIC;
  signal HDL_Counter2_count_next : STD_LOGIC_VECTOR ( 16 downto 9 );
  signal \HDL_Counter2_count_next_carry__0_n_1\ : STD_LOGIC;
  signal \HDL_Counter2_count_next_carry__0_n_2\ : STD_LOGIC;
  signal \HDL_Counter2_count_next_carry__0_n_3\ : STD_LOGIC;
  signal \HDL_Counter2_count_next_carry__0_n_4\ : STD_LOGIC;
  signal \HDL_Counter2_count_next_carry__0_n_5\ : STD_LOGIC;
  signal \HDL_Counter2_count_next_carry__0_n_6\ : STD_LOGIC;
  signal \HDL_Counter2_count_next_carry__0_n_7\ : STD_LOGIC;
  signal HDL_Counter2_count_reg : STD_LOGIC_VECTOR ( 19 downto 1 );
  signal \^hdl_counter2_count_reg[2]_0\ : STD_LOGIC;
  signal \^hdl_counter2_count_reg[3]_0\ : STD_LOGIC;
  signal \^hdl_counter2_count_reg[4]_0\ : STD_LOGIC;
  signal \^hdl_counter2_count_reg[5]_0\ : STD_LOGIC;
  signal \^hdl_counter2_count_reg[6]_0\ : STD_LOGIC;
  signal \^hdl_counter2_count_reg[7]_0\ : STD_LOGIC;
  signal \^pwm_en_axi_1_reg_0\ : STD_LOGIC;
  signal Relational_Operator1_relop1 : STD_LOGIC;
  signal Relational_Operator1_relop1_1 : STD_LOGIC;
  signal Relational_Operator1_relop1_3 : STD_LOGIC;
  signal Relational_Operator1_relop1_5 : STD_LOGIC;
  signal Relational_Operator2_relop1 : STD_LOGIC;
  signal Relational_Operator_1_cast : STD_LOGIC_VECTOR ( 17 downto 4 );
  signal Relational_Operator_relop1 : STD_LOGIC;
  signal Relational_Operator_relop1_0 : STD_LOGIC;
  signal Relational_Operator_relop1_2 : STD_LOGIC;
  signal Relational_Operator_relop1_4 : STD_LOGIC;
  signal Saturation_out1 : STD_LOGIC_VECTOR ( 16 downto 4 );
  signal Switch3_out1_0 : STD_LOGIC;
  signal Switch4_out1_0 : STD_LOGIC;
  signal Switch5_out1_0 : STD_LOGIC;
  signal Switch6_out1 : STD_LOGIC;
  signal \Switch7_out12_carry__0_n_7\ : STD_LOGIC;
  signal Switch7_out12_carry_n_0 : STD_LOGIC;
  signal Switch7_out12_carry_n_1 : STD_LOGIC;
  signal Switch7_out12_carry_n_2 : STD_LOGIC;
  signal Switch7_out12_carry_n_3 : STD_LOGIC;
  signal Switch7_out12_carry_n_4 : STD_LOGIC;
  signal Switch7_out12_carry_n_5 : STD_LOGIC;
  signal Switch7_out12_carry_n_6 : STD_LOGIC;
  signal Switch7_out12_carry_n_7 : STD_LOGIC;
  signal \Switch8_out12_carry__0_n_7\ : STD_LOGIC;
  signal Switch8_out12_carry_n_0 : STD_LOGIC;
  signal Switch8_out12_carry_n_1 : STD_LOGIC;
  signal Switch8_out12_carry_n_2 : STD_LOGIC;
  signal Switch8_out12_carry_n_3 : STD_LOGIC;
  signal Switch8_out12_carry_n_4 : STD_LOGIC;
  signal Switch8_out12_carry_n_5 : STD_LOGIC;
  signal Switch8_out12_carry_n_6 : STD_LOGIC;
  signal Switch8_out12_carry_n_7 : STD_LOGIC;
  signal \Switch9_out12_carry__0_n_7\ : STD_LOGIC;
  signal Switch9_out12_carry_n_0 : STD_LOGIC;
  signal Switch9_out12_carry_n_1 : STD_LOGIC;
  signal Switch9_out12_carry_n_2 : STD_LOGIC;
  signal Switch9_out12_carry_n_3 : STD_LOGIC;
  signal Switch9_out12_carry_n_4 : STD_LOGIC;
  signal Switch9_out12_carry_n_5 : STD_LOGIC;
  signal Switch9_out12_carry_n_6 : STD_LOGIC;
  signal Switch9_out12_carry_n_7 : STD_LOGIC;
  signal T_carrier_us : STD_LOGIC_VECTOR ( 24 downto 0 );
  signal U1_norm_1 : STD_LOGIC_VECTOR ( 13 downto 0 );
  signal U2_norm_1 : STD_LOGIC_VECTOR ( 13 downto 0 );
  signal U3_norm_1 : STD_LOGIC_VECTOR ( 13 downto 0 );
  signal f_carrier_kHz : STD_LOGIC_VECTOR ( 24 downto 0 );
  signal \i__carry__0_i_1_n_0\ : STD_LOGIC;
  signal min_pulse_width : STD_LOGIC_VECTOR ( 17 downto 0 );
  signal u_Counter_Ctrl_n_0 : STD_LOGIC;
  signal u_Counter_Ctrl_n_1 : STD_LOGIC;
  signal u_Counter_Ctrl_n_100 : STD_LOGIC;
  signal u_Counter_Ctrl_n_101 : STD_LOGIC;
  signal u_Counter_Ctrl_n_102 : STD_LOGIC;
  signal u_Counter_Ctrl_n_103 : STD_LOGIC;
  signal u_Counter_Ctrl_n_104 : STD_LOGIC;
  signal u_Counter_Ctrl_n_105 : STD_LOGIC;
  signal u_Counter_Ctrl_n_106 : STD_LOGIC;
  signal u_Counter_Ctrl_n_107 : STD_LOGIC;
  signal u_Counter_Ctrl_n_108 : STD_LOGIC;
  signal u_Counter_Ctrl_n_109 : STD_LOGIC;
  signal u_Counter_Ctrl_n_110 : STD_LOGIC;
  signal u_Counter_Ctrl_n_111 : STD_LOGIC;
  signal u_Counter_Ctrl_n_112 : STD_LOGIC;
  signal u_Counter_Ctrl_n_113 : STD_LOGIC;
  signal u_Counter_Ctrl_n_114 : STD_LOGIC;
  signal u_Counter_Ctrl_n_115 : STD_LOGIC;
  signal u_Counter_Ctrl_n_116 : STD_LOGIC;
  signal u_Counter_Ctrl_n_117 : STD_LOGIC;
  signal u_Counter_Ctrl_n_118 : STD_LOGIC;
  signal u_Counter_Ctrl_n_119 : STD_LOGIC;
  signal u_Counter_Ctrl_n_120 : STD_LOGIC;
  signal u_Counter_Ctrl_n_121 : STD_LOGIC;
  signal u_Counter_Ctrl_n_122 : STD_LOGIC;
  signal u_Counter_Ctrl_n_123 : STD_LOGIC;
  signal u_Counter_Ctrl_n_124 : STD_LOGIC;
  signal u_Counter_Ctrl_n_125 : STD_LOGIC;
  signal u_Counter_Ctrl_n_126 : STD_LOGIC;
  signal u_Counter_Ctrl_n_127 : STD_LOGIC;
  signal u_Counter_Ctrl_n_128 : STD_LOGIC;
  signal u_Counter_Ctrl_n_129 : STD_LOGIC;
  signal u_Counter_Ctrl_n_130 : STD_LOGIC;
  signal u_Counter_Ctrl_n_131 : STD_LOGIC;
  signal u_Counter_Ctrl_n_132 : STD_LOGIC;
  signal u_Counter_Ctrl_n_133 : STD_LOGIC;
  signal u_Counter_Ctrl_n_134 : STD_LOGIC;
  signal u_Counter_Ctrl_n_135 : STD_LOGIC;
  signal u_Counter_Ctrl_n_136 : STD_LOGIC;
  signal u_Counter_Ctrl_n_137 : STD_LOGIC;
  signal u_Counter_Ctrl_n_138 : STD_LOGIC;
  signal u_Counter_Ctrl_n_139 : STD_LOGIC;
  signal u_Counter_Ctrl_n_140 : STD_LOGIC;
  signal u_Counter_Ctrl_n_141 : STD_LOGIC;
  signal u_Counter_Ctrl_n_142 : STD_LOGIC;
  signal u_Counter_Ctrl_n_143 : STD_LOGIC;
  signal u_Counter_Ctrl_n_144 : STD_LOGIC;
  signal u_Counter_Ctrl_n_145 : STD_LOGIC;
  signal u_Counter_Ctrl_n_146 : STD_LOGIC;
  signal u_Counter_Ctrl_n_147 : STD_LOGIC;
  signal u_Counter_Ctrl_n_148 : STD_LOGIC;
  signal u_Counter_Ctrl_n_149 : STD_LOGIC;
  signal u_Counter_Ctrl_n_150 : STD_LOGIC;
  signal u_Counter_Ctrl_n_151 : STD_LOGIC;
  signal u_Counter_Ctrl_n_152 : STD_LOGIC;
  signal u_Counter_Ctrl_n_153 : STD_LOGIC;
  signal u_Counter_Ctrl_n_154 : STD_LOGIC;
  signal u_Counter_Ctrl_n_155 : STD_LOGIC;
  signal u_Counter_Ctrl_n_156 : STD_LOGIC;
  signal u_Counter_Ctrl_n_157 : STD_LOGIC;
  signal u_Counter_Ctrl_n_158 : STD_LOGIC;
  signal u_Counter_Ctrl_n_159 : STD_LOGIC;
  signal u_Counter_Ctrl_n_160 : STD_LOGIC;
  signal u_Counter_Ctrl_n_161 : STD_LOGIC;
  signal u_Counter_Ctrl_n_162 : STD_LOGIC;
  signal u_Counter_Ctrl_n_163 : STD_LOGIC;
  signal u_Counter_Ctrl_n_164 : STD_LOGIC;
  signal u_Counter_Ctrl_n_17 : STD_LOGIC;
  signal u_Counter_Ctrl_n_179 : STD_LOGIC;
  signal u_Counter_Ctrl_n_18 : STD_LOGIC;
  signal u_Counter_Ctrl_n_180 : STD_LOGIC;
  signal u_Counter_Ctrl_n_181 : STD_LOGIC;
  signal u_Counter_Ctrl_n_182 : STD_LOGIC;
  signal u_Counter_Ctrl_n_183 : STD_LOGIC;
  signal u_Counter_Ctrl_n_184 : STD_LOGIC;
  signal u_Counter_Ctrl_n_185 : STD_LOGIC;
  signal u_Counter_Ctrl_n_186 : STD_LOGIC;
  signal u_Counter_Ctrl_n_187 : STD_LOGIC;
  signal u_Counter_Ctrl_n_188 : STD_LOGIC;
  signal u_Counter_Ctrl_n_189 : STD_LOGIC;
  signal u_Counter_Ctrl_n_19 : STD_LOGIC;
  signal u_Counter_Ctrl_n_190 : STD_LOGIC;
  signal u_Counter_Ctrl_n_191 : STD_LOGIC;
  signal u_Counter_Ctrl_n_192 : STD_LOGIC;
  signal u_Counter_Ctrl_n_193 : STD_LOGIC;
  signal u_Counter_Ctrl_n_194 : STD_LOGIC;
  signal u_Counter_Ctrl_n_195 : STD_LOGIC;
  signal u_Counter_Ctrl_n_196 : STD_LOGIC;
  signal u_Counter_Ctrl_n_197 : STD_LOGIC;
  signal u_Counter_Ctrl_n_198 : STD_LOGIC;
  signal u_Counter_Ctrl_n_199 : STD_LOGIC;
  signal u_Counter_Ctrl_n_2 : STD_LOGIC;
  signal u_Counter_Ctrl_n_20 : STD_LOGIC;
  signal u_Counter_Ctrl_n_201 : STD_LOGIC;
  signal u_Counter_Ctrl_n_202 : STD_LOGIC;
  signal u_Counter_Ctrl_n_203 : STD_LOGIC;
  signal u_Counter_Ctrl_n_204 : STD_LOGIC;
  signal u_Counter_Ctrl_n_21 : STD_LOGIC;
  signal u_Counter_Ctrl_n_22 : STD_LOGIC;
  signal u_Counter_Ctrl_n_23 : STD_LOGIC;
  signal u_Counter_Ctrl_n_24 : STD_LOGIC;
  signal u_Counter_Ctrl_n_26 : STD_LOGIC;
  signal u_Counter_Ctrl_n_27 : STD_LOGIC;
  signal u_Counter_Ctrl_n_28 : STD_LOGIC;
  signal u_Counter_Ctrl_n_29 : STD_LOGIC;
  signal u_Counter_Ctrl_n_3 : STD_LOGIC;
  signal u_Counter_Ctrl_n_30 : STD_LOGIC;
  signal u_Counter_Ctrl_n_31 : STD_LOGIC;
  signal u_Counter_Ctrl_n_32 : STD_LOGIC;
  signal u_Counter_Ctrl_n_33 : STD_LOGIC;
  signal u_Counter_Ctrl_n_34 : STD_LOGIC;
  signal u_Counter_Ctrl_n_35 : STD_LOGIC;
  signal u_Counter_Ctrl_n_36 : STD_LOGIC;
  signal u_Counter_Ctrl_n_37 : STD_LOGIC;
  signal u_Counter_Ctrl_n_38 : STD_LOGIC;
  signal u_Counter_Ctrl_n_39 : STD_LOGIC;
  signal u_Counter_Ctrl_n_4 : STD_LOGIC;
  signal u_Counter_Ctrl_n_40 : STD_LOGIC;
  signal u_Counter_Ctrl_n_41 : STD_LOGIC;
  signal u_Counter_Ctrl_n_42 : STD_LOGIC;
  signal u_Counter_Ctrl_n_43 : STD_LOGIC;
  signal u_Counter_Ctrl_n_44 : STD_LOGIC;
  signal u_Counter_Ctrl_n_45 : STD_LOGIC;
  signal u_Counter_Ctrl_n_49 : STD_LOGIC;
  signal u_Counter_Ctrl_n_5 : STD_LOGIC;
  signal u_Counter_Ctrl_n_50 : STD_LOGIC;
  signal u_Counter_Ctrl_n_51 : STD_LOGIC;
  signal u_Counter_Ctrl_n_52 : STD_LOGIC;
  signal u_Counter_Ctrl_n_53 : STD_LOGIC;
  signal u_Counter_Ctrl_n_54 : STD_LOGIC;
  signal u_Counter_Ctrl_n_55 : STD_LOGIC;
  signal u_Counter_Ctrl_n_56 : STD_LOGIC;
  signal u_Counter_Ctrl_n_58 : STD_LOGIC;
  signal u_Counter_Ctrl_n_59 : STD_LOGIC;
  signal u_Counter_Ctrl_n_60 : STD_LOGIC;
  signal u_Counter_Ctrl_n_61 : STD_LOGIC;
  signal u_Counter_Ctrl_n_62 : STD_LOGIC;
  signal u_Counter_Ctrl_n_63 : STD_LOGIC;
  signal u_Counter_Ctrl_n_64 : STD_LOGIC;
  signal u_Counter_Ctrl_n_65 : STD_LOGIC;
  signal u_Counter_Ctrl_n_66 : STD_LOGIC;
  signal u_Counter_Ctrl_n_67 : STD_LOGIC;
  signal u_Counter_Ctrl_n_68 : STD_LOGIC;
  signal u_Counter_Ctrl_n_69 : STD_LOGIC;
  signal u_Counter_Ctrl_n_70 : STD_LOGIC;
  signal u_Counter_Ctrl_n_71 : STD_LOGIC;
  signal u_Counter_Ctrl_n_72 : STD_LOGIC;
  signal u_Counter_Ctrl_n_73 : STD_LOGIC;
  signal u_Counter_Ctrl_n_74 : STD_LOGIC;
  signal u_Counter_Ctrl_n_75 : STD_LOGIC;
  signal u_Counter_Ctrl_n_76 : STD_LOGIC;
  signal u_Counter_Ctrl_n_77 : STD_LOGIC;
  signal u_Counter_Ctrl_n_78 : STD_LOGIC;
  signal u_Counter_Ctrl_n_79 : STD_LOGIC;
  signal u_Counter_Ctrl_n_80 : STD_LOGIC;
  signal u_Counter_Ctrl_n_81 : STD_LOGIC;
  signal u_Counter_Ctrl_n_82 : STD_LOGIC;
  signal u_Counter_Ctrl_n_83 : STD_LOGIC;
  signal u_Counter_Ctrl_n_84 : STD_LOGIC;
  signal u_Counter_Ctrl_n_85 : STD_LOGIC;
  signal u_Counter_Ctrl_n_86 : STD_LOGIC;
  signal u_Counter_Ctrl_n_87 : STD_LOGIC;
  signal u_Counter_Ctrl_n_88 : STD_LOGIC;
  signal u_Counter_Ctrl_n_89 : STD_LOGIC;
  signal u_Counter_Ctrl_n_90 : STD_LOGIC;
  signal u_Counter_Ctrl_n_91 : STD_LOGIC;
  signal u_Counter_Ctrl_n_92 : STD_LOGIC;
  signal u_Counter_Ctrl_n_93 : STD_LOGIC;
  signal u_Counter_Ctrl_n_94 : STD_LOGIC;
  signal u_Counter_Ctrl_n_95 : STD_LOGIC;
  signal u_Counter_Ctrl_n_96 : STD_LOGIC;
  signal u_Counter_Ctrl_n_97 : STD_LOGIC;
  signal u_Counter_Ctrl_n_98 : STD_LOGIC;
  signal u_Counter_Ctrl_n_99 : STD_LOGIC;
  signal u_LimitPulseWidth_n_1 : STD_LOGIC;
  signal u_LimitPulseWidth_n_17 : STD_LOGIC;
  signal u_LimitPulseWidth_n_18 : STD_LOGIC;
  signal u_LimitPulseWidth_n_19 : STD_LOGIC;
  signal u_LimitPulseWidth_n_20 : STD_LOGIC;
  signal u_LimitPulseWidth_n_21 : STD_LOGIC;
  signal u_LimitPulseWidth_n_22 : STD_LOGIC;
  signal u_LimitPulseWidth_n_23 : STD_LOGIC;
  signal u_LimitPulseWidth_n_24 : STD_LOGIC;
  signal u_LimitPulseWidth_n_38 : STD_LOGIC;
  signal u_LimitPulseWidth_n_39 : STD_LOGIC;
  signal u_LimitPulseWidth_n_40 : STD_LOGIC;
  signal u_LimitPulseWidth_n_41 : STD_LOGIC;
  signal u_LimitPulseWidth_n_42 : STD_LOGIC;
  signal u_LimitPulseWidth_n_43 : STD_LOGIC;
  signal u_LimitPulseWidth_n_44 : STD_LOGIC;
  signal u_LimitPulseWidth_n_45 : STD_LOGIC;
  signal u_LimitPulseWidth_n_46 : STD_LOGIC;
  signal u_LimitPulseWidth_n_47 : STD_LOGIC;
  signal u_LimitPulseWidth_n_48 : STD_LOGIC;
  signal u_LimitPulseWidth_n_49 : STD_LOGIC;
  signal u_LimitPulseWidth_n_50 : STD_LOGIC;
  signal u_LimitPulseWidth_n_51 : STD_LOGIC;
  signal u_LimitPulseWidth_n_52 : STD_LOGIC;
  signal u_LimitPulseWidth_n_53 : STD_LOGIC;
  signal u_LimitPulseWidth_n_54 : STD_LOGIC;
  signal u_LimitPulseWidth_n_55 : STD_LOGIC;
  signal u_LimitPulseWidth_n_56 : STD_LOGIC;
  signal u_LimitPulseWidth_n_57 : STD_LOGIC;
  signal u_LimitPulseWidth_n_58 : STD_LOGIC;
  signal \NLW_HDL_Counter2_count_next_carry__0_CO_UNCONNECTED\ : STD_LOGIC_VECTOR ( 7 to 7 );
  signal NLW_Switch7_out12_carry_O_UNCONNECTED : STD_LOGIC_VECTOR ( 7 downto 0 );
  signal \NLW_Switch7_out12_carry__0_CO_UNCONNECTED\ : STD_LOGIC_VECTOR ( 7 downto 2 );
  signal \NLW_Switch7_out12_carry__0_O_UNCONNECTED\ : STD_LOGIC_VECTOR ( 7 downto 0 );
  signal NLW_Switch8_out12_carry_O_UNCONNECTED : STD_LOGIC_VECTOR ( 7 downto 0 );
  signal \NLW_Switch8_out12_carry__0_CO_UNCONNECTED\ : STD_LOGIC_VECTOR ( 7 downto 2 );
  signal \NLW_Switch8_out12_carry__0_O_UNCONNECTED\ : STD_LOGIC_VECTOR ( 7 downto 0 );
  signal NLW_Switch9_out12_carry_O_UNCONNECTED : STD_LOGIC_VECTOR ( 7 downto 0 );
  signal \NLW_Switch9_out12_carry__0_CO_UNCONNECTED\ : STD_LOGIC_VECTOR ( 7 downto 2 );
  signal \NLW_Switch9_out12_carry__0_O_UNCONNECTED\ : STD_LOGIC_VECTOR ( 7 downto 0 );
  attribute SOFT_HLUTNM : string;
  attribute SOFT_HLUTNM of Demux1_out1_i_1 : label is "soft_lutpair24";
  attribute SOFT_HLUTNM of Demux1_out2_i_1 : label is "soft_lutpair24";
  attribute SOFT_HLUTNM of Demux2_out1_i_1 : label is "soft_lutpair25";
  attribute SOFT_HLUTNM of Demux2_out2_i_1 : label is "soft_lutpair25";
  attribute SOFT_HLUTNM of Demux_out1_i_1 : label is "soft_lutpair23";
  attribute SOFT_HLUTNM of Demux_out2_i_1 : label is "soft_lutpair23";
  attribute COMPARATOR_THRESHOLD : integer;
  attribute COMPARATOR_THRESHOLD of Switch7_out12_carry : label is 11;
  attribute COMPARATOR_THRESHOLD of \Switch7_out12_carry__0\ : label is 11;
  attribute COMPARATOR_THRESHOLD of Switch8_out12_carry : label is 11;
  attribute COMPARATOR_THRESHOLD of \Switch8_out12_carry__0\ : label is 11;
  attribute COMPARATOR_THRESHOLD of Switch9_out12_carry : label is 11;
  attribute COMPARATOR_THRESHOLD of \Switch9_out12_carry__0\ : label is 11;
begin
  DI(1 downto 0) <= \^di\(1 downto 0);
  \HDL_Counter2_count_reg[2]_0\ <= \^hdl_counter2_count_reg[2]_0\;
  \HDL_Counter2_count_reg[3]_0\ <= \^hdl_counter2_count_reg[3]_0\;
  \HDL_Counter2_count_reg[4]_0\ <= \^hdl_counter2_count_reg[4]_0\;
  \HDL_Counter2_count_reg[5]_0\ <= \^hdl_counter2_count_reg[5]_0\;
  \HDL_Counter2_count_reg[6]_0\ <= \^hdl_counter2_count_reg[6]_0\;
  \HDL_Counter2_count_reg[7]_0\ <= \^hdl_counter2_count_reg[7]_0\;
  PWM_en_AXI_1_reg_0 <= \^pwm_en_axi_1_reg_0\;
Counter_Ctrl_out3_1_reg: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => Counter_Ctrl_out3,
      Q => Triangular_Max,
      R => reset
    );
Counter_Ctrl_out4_1_i_1: unisim.vcomponents.LUT4
    generic map(
      INIT => X"0080"
    )
        port map (
      I0 => u_LimitPulseWidth_n_52,
      I1 => u_LimitPulseWidth_n_53,
      I2 => u_LimitPulseWidth_n_51,
      I3 => HDL_Counter2_count_reg(19),
      O => Counter_Ctrl_out4
    );
Counter_Ctrl_out4_1_reg: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => Counter_Ctrl_out4,
      Q => Triangular_Min,
      R => reset
    );
\Delay1_out1_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => u_Counter_Ctrl_n_134,
      Q => Delay1_out1(0),
      R => reset
    );
\Delay1_out1_reg[10]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => u_Counter_Ctrl_n_124,
      Q => Delay1_out1(10),
      R => reset
    );
\Delay1_out1_reg[11]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => u_Counter_Ctrl_n_123,
      Q => Delay1_out1(11),
      R => reset
    );
\Delay1_out1_reg[12]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => u_Counter_Ctrl_n_122,
      Q => Delay1_out1(12),
      R => reset
    );
\Delay1_out1_reg[13]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => u_Counter_Ctrl_n_111,
      Q => Delay1_out1(13),
      R => reset
    );
\Delay1_out1_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => u_Counter_Ctrl_n_133,
      Q => Delay1_out1(1),
      R => reset
    );
\Delay1_out1_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => u_Counter_Ctrl_n_132,
      Q => Delay1_out1(2),
      R => reset
    );
\Delay1_out1_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => u_Counter_Ctrl_n_131,
      Q => Delay1_out1(3),
      R => reset
    );
\Delay1_out1_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => u_Counter_Ctrl_n_130,
      Q => Delay1_out1(4),
      R => reset
    );
\Delay1_out1_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => u_Counter_Ctrl_n_129,
      Q => Delay1_out1(5),
      R => reset
    );
\Delay1_out1_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => u_Counter_Ctrl_n_128,
      Q => Delay1_out1(6),
      R => reset
    );
\Delay1_out1_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => u_Counter_Ctrl_n_127,
      Q => Delay1_out1(7),
      R => reset
    );
\Delay1_out1_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => u_Counter_Ctrl_n_126,
      Q => Delay1_out1(8),
      R => reset
    );
\Delay1_out1_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => u_Counter_Ctrl_n_125,
      Q => Delay1_out1(9),
      R => reset
    );
\Delay2_out1_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => u_Counter_Ctrl_n_80,
      Q => Delay2_out1(0),
      R => reset
    );
\Delay2_out1_reg[10]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => u_Counter_Ctrl_n_70,
      Q => Delay2_out1(10),
      R => reset
    );
\Delay2_out1_reg[11]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => u_Counter_Ctrl_n_69,
      Q => Delay2_out1(11),
      R => reset
    );
\Delay2_out1_reg[12]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => u_Counter_Ctrl_n_68,
      Q => Delay2_out1(12),
      R => reset
    );
\Delay2_out1_reg[13]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => u_Counter_Ctrl_n_56,
      Q => Delay2_out1(13),
      R => reset
    );
\Delay2_out1_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => u_Counter_Ctrl_n_79,
      Q => Delay2_out1(1),
      R => reset
    );
\Delay2_out1_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => u_Counter_Ctrl_n_78,
      Q => Delay2_out1(2),
      R => reset
    );
\Delay2_out1_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => u_Counter_Ctrl_n_77,
      Q => Delay2_out1(3),
      R => reset
    );
\Delay2_out1_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => u_Counter_Ctrl_n_76,
      Q => Delay2_out1(4),
      R => reset
    );
\Delay2_out1_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => u_Counter_Ctrl_n_75,
      Q => Delay2_out1(5),
      R => reset
    );
\Delay2_out1_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => u_Counter_Ctrl_n_74,
      Q => Delay2_out1(6),
      R => reset
    );
\Delay2_out1_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => u_Counter_Ctrl_n_73,
      Q => Delay2_out1(7),
      R => reset
    );
\Delay2_out1_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => u_Counter_Ctrl_n_72,
      Q => Delay2_out1(8),
      R => reset
    );
\Delay2_out1_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => u_Counter_Ctrl_n_71,
      Q => Delay2_out1(9),
      R => reset
    );
\Delay_out1_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => Relational_Operator_1_cast(4),
      Q => Delay_out1(0),
      R => reset
    );
\Delay_out1_reg[10]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => Relational_Operator_1_cast(14),
      Q => Delay_out1(10),
      R => reset
    );
\Delay_out1_reg[11]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => Relational_Operator_1_cast(15),
      Q => Delay_out1(11),
      R => reset
    );
\Delay_out1_reg[12]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => Relational_Operator_1_cast(16),
      Q => Delay_out1(12),
      R => reset
    );
\Delay_out1_reg[13]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => Relational_Operator_1_cast(17),
      Q => Delay_out1(13),
      R => reset
    );
\Delay_out1_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => Relational_Operator_1_cast(5),
      Q => Delay_out1(1),
      R => reset
    );
\Delay_out1_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => Relational_Operator_1_cast(6),
      Q => Delay_out1(2),
      R => reset
    );
\Delay_out1_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => Relational_Operator_1_cast(7),
      Q => Delay_out1(3),
      R => reset
    );
\Delay_out1_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => Relational_Operator_1_cast(8),
      Q => Delay_out1(4),
      R => reset
    );
\Delay_out1_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => Relational_Operator_1_cast(9),
      Q => Delay_out1(5),
      R => reset
    );
\Delay_out1_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => Relational_Operator_1_cast(10),
      Q => Delay_out1(6),
      R => reset
    );
\Delay_out1_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => Relational_Operator_1_cast(11),
      Q => Delay_out1(7),
      R => reset
    );
\Delay_out1_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => Relational_Operator_1_cast(12),
      Q => Delay_out1(8),
      R => reset
    );
\Delay_out1_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => Relational_Operator_1_cast(13),
      Q => Delay_out1(9),
      R => reset
    );
Demux1_out1_i_1: unisim.vcomponents.LUT2
    generic map(
      INIT => X"2"
    )
        port map (
      I0 => \^pwm_en_axi_1_reg_0\,
      I1 => Relational_Operator1_relop1,
      O => Switch4_out1_0
    );
Demux1_out1_reg: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => Switch4_out1_0,
      Q => GenPWM_out3,
      R => reset
    );
Demux1_out2_i_1: unisim.vcomponents.LUT2
    generic map(
      INIT => X"8"
    )
        port map (
      I0 => \^pwm_en_axi_1_reg_0\,
      I1 => Relational_Operator1_relop1,
      O => Demux1_out2_i_1_n_0
    );
Demux1_out2_reg: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => Demux1_out2_i_1_n_0,
      Q => GenPWM_out4,
      R => reset
    );
Demux2_out1_i_1: unisim.vcomponents.LUT2
    generic map(
      INIT => X"2"
    )
        port map (
      I0 => \^pwm_en_axi_1_reg_0\,
      I1 => Relational_Operator2_relop1,
      O => Switch5_out1_0
    );
Demux2_out1_reg: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => Switch5_out1_0,
      Q => GenPWM_out5,
      R => reset
    );
Demux2_out2_i_1: unisim.vcomponents.LUT2
    generic map(
      INIT => X"8"
    )
        port map (
      I0 => \^pwm_en_axi_1_reg_0\,
      I1 => Relational_Operator2_relop1,
      O => Demux2_out2_i_1_n_0
    );
Demux2_out2_reg: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => Demux2_out2_i_1_n_0,
      Q => GenPWM_out6,
      R => reset
    );
Demux_out1_i_1: unisim.vcomponents.LUT2
    generic map(
      INIT => X"2"
    )
        port map (
      I0 => \^pwm_en_axi_1_reg_0\,
      I1 => Relational_Operator_relop1,
      O => Switch3_out1_0
    );
Demux_out1_reg: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => Switch3_out1_0,
      Q => GenPWM_out1,
      R => reset
    );
Demux_out2_i_1: unisim.vcomponents.LUT2
    generic map(
      INIT => X"8"
    )
        port map (
      I0 => \^pwm_en_axi_1_reg_0\,
      I1 => Relational_Operator_relop1,
      O => Demux_out2_i_1_n_0
    );
Demux_out2_reg: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => Demux_out2_i_1_n_0,
      Q => GenPWM_out2,
      R => reset
    );
\HDL_Counter2_count_next_carry__0\: unisim.vcomponents.CARRY8
     port map (
      CI => CO(0),
      CI_TOP => '0',
      CO(7) => \NLW_HDL_Counter2_count_next_carry__0_CO_UNCONNECTED\(7),
      CO(6) => \HDL_Counter2_count_next_carry__0_n_1\,
      CO(5) => \HDL_Counter2_count_next_carry__0_n_2\,
      CO(4) => \HDL_Counter2_count_next_carry__0_n_3\,
      CO(3) => \HDL_Counter2_count_next_carry__0_n_4\,
      CO(2) => \HDL_Counter2_count_next_carry__0_n_5\,
      CO(1) => \HDL_Counter2_count_next_carry__0_n_6\,
      CO(0) => \HDL_Counter2_count_next_carry__0_n_7\,
      DI(7) => '0',
      DI(6 downto 0) => HDL_Counter2_count_reg(14 downto 8),
      O(7 downto 0) => HDL_Counter2_count_next(16 downto 9),
      S(7) => u_Counter_Ctrl_n_38,
      S(6) => u_Counter_Ctrl_n_39,
      S(5) => u_Counter_Ctrl_n_40,
      S(4) => u_Counter_Ctrl_n_41,
      S(3) => u_Counter_Ctrl_n_42,
      S(2) => u_Counter_Ctrl_n_43,
      S(1) => u_Counter_Ctrl_n_44,
      S(0) => u_Counter_Ctrl_n_45
    );
HDL_Counter2_count_next_carry_i_3: unisim.vcomponents.LUT2
    generic map(
      INIT => X"9"
    )
        port map (
      I0 => \^hdl_counter2_count_reg[7]_0\,
      I1 => HDL_Counter2_count_reg(8),
      O => S(7)
    );
HDL_Counter2_count_next_carry_i_4: unisim.vcomponents.LUT2
    generic map(
      INIT => X"9"
    )
        port map (
      I0 => \^hdl_counter2_count_reg[6]_0\,
      I1 => \^hdl_counter2_count_reg[7]_0\,
      O => S(6)
    );
HDL_Counter2_count_next_carry_i_5: unisim.vcomponents.LUT2
    generic map(
      INIT => X"9"
    )
        port map (
      I0 => \^hdl_counter2_count_reg[5]_0\,
      I1 => \^hdl_counter2_count_reg[6]_0\,
      O => S(5)
    );
HDL_Counter2_count_next_carry_i_6: unisim.vcomponents.LUT2
    generic map(
      INIT => X"9"
    )
        port map (
      I0 => \^hdl_counter2_count_reg[4]_0\,
      I1 => \^hdl_counter2_count_reg[5]_0\,
      O => S(4)
    );
HDL_Counter2_count_next_carry_i_7: unisim.vcomponents.LUT2
    generic map(
      INIT => X"9"
    )
        port map (
      I0 => \^hdl_counter2_count_reg[3]_0\,
      I1 => \^hdl_counter2_count_reg[4]_0\,
      O => S(3)
    );
HDL_Counter2_count_next_carry_i_8: unisim.vcomponents.LUT2
    generic map(
      INIT => X"9"
    )
        port map (
      I0 => \^hdl_counter2_count_reg[2]_0\,
      I1 => \^hdl_counter2_count_reg[3]_0\,
      O => S(2)
    );
\HDL_Counter2_count_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEB2,
      D => u_Counter_Ctrl_n_24,
      Q => \^di\(0),
      R => reset
    );
\HDL_Counter2_count_reg[10]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEB2,
      D => u_Counter_Ctrl_n_31,
      Q => HDL_Counter2_count_reg(10),
      R => reset
    );
\HDL_Counter2_count_reg[11]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEB2,
      D => u_Counter_Ctrl_n_30,
      Q => HDL_Counter2_count_reg(11),
      R => reset
    );
\HDL_Counter2_count_reg[12]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEB2,
      D => u_Counter_Ctrl_n_29,
      Q => HDL_Counter2_count_reg(12),
      R => reset
    );
\HDL_Counter2_count_reg[13]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEB2,
      D => u_Counter_Ctrl_n_28,
      Q => HDL_Counter2_count_reg(13),
      R => reset
    );
\HDL_Counter2_count_reg[14]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEB2,
      D => u_Counter_Ctrl_n_27,
      Q => HDL_Counter2_count_reg(14),
      R => reset
    );
\HDL_Counter2_count_reg[15]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEB2,
      D => u_Counter_Ctrl_n_26,
      Q => HDL_Counter2_count_reg(15),
      R => reset
    );
\HDL_Counter2_count_reg[16]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEB2,
      D => u_Counter_Ctrl_n_37,
      Q => HDL_Counter2_count_reg(16),
      R => reset
    );
\HDL_Counter2_count_reg[17]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEB2,
      D => u_Counter_Ctrl_n_36,
      Q => HDL_Counter2_count_reg(17),
      R => reset
    );
\HDL_Counter2_count_reg[18]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEB2,
      D => u_Counter_Ctrl_n_35,
      Q => HDL_Counter2_count_reg(18),
      R => reset
    );
\HDL_Counter2_count_reg[19]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEB2,
      D => u_Counter_Ctrl_n_34,
      Q => HDL_Counter2_count_reg(19),
      R => reset
    );
\HDL_Counter2_count_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEB2,
      D => u_Counter_Ctrl_n_23,
      Q => HDL_Counter2_count_reg(1),
      R => reset
    );
\HDL_Counter2_count_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEB2,
      D => u_Counter_Ctrl_n_22,
      Q => \^hdl_counter2_count_reg[2]_0\,
      R => reset
    );
\HDL_Counter2_count_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEB2,
      D => u_Counter_Ctrl_n_21,
      Q => \^hdl_counter2_count_reg[3]_0\,
      R => reset
    );
\HDL_Counter2_count_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEB2,
      D => u_Counter_Ctrl_n_20,
      Q => \^hdl_counter2_count_reg[4]_0\,
      R => reset
    );
\HDL_Counter2_count_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEB2,
      D => u_Counter_Ctrl_n_19,
      Q => \^hdl_counter2_count_reg[5]_0\,
      R => reset
    );
\HDL_Counter2_count_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEB2,
      D => u_Counter_Ctrl_n_18,
      Q => \^hdl_counter2_count_reg[6]_0\,
      R => reset
    );
\HDL_Counter2_count_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEB2,
      D => u_Counter_Ctrl_n_17,
      Q => \^hdl_counter2_count_reg[7]_0\,
      R => reset
    );
\HDL_Counter2_count_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEB2,
      D => u_Counter_Ctrl_n_33,
      Q => HDL_Counter2_count_reg(8),
      R => reset
    );
\HDL_Counter2_count_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEB2,
      D => u_Counter_Ctrl_n_32,
      Q => HDL_Counter2_count_reg(9),
      R => reset
    );
PWM_en_AXI_1_reg: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => write_PWM_en_AXI,
      Q => \^pwm_en_axi_1_reg_0\,
      R => reset
    );
PWM_en_AXI_2_reg: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => \^pwm_en_axi_1_reg_0\,
      Q => PWM_en_rd_AXI_sig,
      R => reset
    );
Switch6_out1_1_reg: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => Switch6_out1,
      Q => PWM_enb_out,
      R => reset
    );
Switch7_out12_carry: unisim.vcomponents.CARRY8
     port map (
      CI => '1',
      CI_TOP => '0',
      CO(7) => Switch7_out12_carry_n_0,
      CO(6) => Switch7_out12_carry_n_1,
      CO(5) => Switch7_out12_carry_n_2,
      CO(4) => Switch7_out12_carry_n_3,
      CO(3) => Switch7_out12_carry_n_4,
      CO(2) => Switch7_out12_carry_n_5,
      CO(1) => Switch7_out12_carry_n_6,
      CO(0) => Switch7_out12_carry_n_7,
      DI(7) => u_Counter_Ctrl_n_194,
      DI(6) => u_Counter_Ctrl_n_195,
      DI(5) => u_Counter_Ctrl_n_196,
      DI(4) => u_Counter_Ctrl_n_197,
      DI(3) => u_Counter_Ctrl_n_198,
      DI(2) => u_LimitPulseWidth_n_48,
      DI(1) => u_Counter_Ctrl_n_199,
      DI(0) => u_LimitPulseWidth_n_49,
      O(7 downto 0) => NLW_Switch7_out12_carry_O_UNCONNECTED(7 downto 0),
      S(7) => u_Counter_Ctrl_n_188,
      S(6) => u_Counter_Ctrl_n_189,
      S(5) => u_Counter_Ctrl_n_190,
      S(4) => u_Counter_Ctrl_n_191,
      S(3) => u_Counter_Ctrl_n_192,
      S(2) => u_Counter_Ctrl_n_193,
      S(1) => u_LimitPulseWidth_n_54,
      S(0) => u_LimitPulseWidth_n_55
    );
\Switch7_out12_carry__0\: unisim.vcomponents.CARRY8
     port map (
      CI => Switch7_out12_carry_n_0,
      CI_TOP => '0',
      CO(7 downto 2) => \NLW_Switch7_out12_carry__0_CO_UNCONNECTED\(7 downto 2),
      CO(1) => Relational_Operator_relop1,
      CO(0) => \Switch7_out12_carry__0_n_7\,
      DI(7 downto 2) => B"000000",
      DI(1) => u_LimitPulseWidth_n_46,
      DI(0) => u_Counter_Ctrl_n_187,
      O(7 downto 0) => \NLW_Switch7_out12_carry__0_O_UNCONNECTED\(7 downto 0),
      S(7 downto 2) => B"000000",
      S(1) => u_LimitPulseWidth_n_47,
      S(0) => u_Counter_Ctrl_n_186
    );
Switch8_out12_carry: unisim.vcomponents.CARRY8
     port map (
      CI => '1',
      CI_TOP => '0',
      CO(7) => Switch8_out12_carry_n_0,
      CO(6) => Switch8_out12_carry_n_1,
      CO(5) => Switch8_out12_carry_n_2,
      CO(4) => Switch8_out12_carry_n_3,
      CO(3) => Switch8_out12_carry_n_4,
      CO(2) => Switch8_out12_carry_n_5,
      CO(1) => Switch8_out12_carry_n_6,
      CO(0) => Switch8_out12_carry_n_7,
      DI(7) => u_Counter_Ctrl_n_150,
      DI(6) => u_Counter_Ctrl_n_151,
      DI(5) => u_Counter_Ctrl_n_152,
      DI(4) => u_Counter_Ctrl_n_153,
      DI(3) => u_Counter_Ctrl_n_154,
      DI(2) => u_Counter_Ctrl_n_155,
      DI(1) => u_Counter_Ctrl_n_156,
      DI(0) => u_Counter_Ctrl_n_157,
      O(7 downto 0) => NLW_Switch8_out12_carry_O_UNCONNECTED(7 downto 0),
      S(7) => u_Counter_Ctrl_n_142,
      S(6) => u_Counter_Ctrl_n_143,
      S(5) => u_Counter_Ctrl_n_144,
      S(4) => u_Counter_Ctrl_n_145,
      S(3) => u_Counter_Ctrl_n_146,
      S(2) => u_Counter_Ctrl_n_147,
      S(1) => u_Counter_Ctrl_n_148,
      S(0) => u_Counter_Ctrl_n_149
    );
\Switch8_out12_carry__0\: unisim.vcomponents.CARRY8
     port map (
      CI => Switch8_out12_carry_n_0,
      CI_TOP => '0',
      CO(7 downto 2) => \NLW_Switch8_out12_carry__0_CO_UNCONNECTED\(7 downto 2),
      CO(1) => Relational_Operator1_relop1,
      CO(0) => \Switch8_out12_carry__0_n_7\,
      DI(7 downto 2) => B"000000",
      DI(1) => u_Counter_Ctrl_n_119,
      DI(0) => u_Counter_Ctrl_n_120,
      O(7 downto 0) => \NLW_Switch8_out12_carry__0_O_UNCONNECTED\(7 downto 0),
      S(7 downto 2) => B"000000",
      S(1) => u_LimitPulseWidth_n_38,
      S(0) => u_Counter_Ctrl_n_121
    );
Switch9_out12_carry: unisim.vcomponents.CARRY8
     port map (
      CI => '1',
      CI_TOP => '0',
      CO(7) => Switch9_out12_carry_n_0,
      CO(6) => Switch9_out12_carry_n_1,
      CO(5) => Switch9_out12_carry_n_2,
      CO(4) => Switch9_out12_carry_n_3,
      CO(3) => Switch9_out12_carry_n_4,
      CO(2) => Switch9_out12_carry_n_5,
      CO(1) => Switch9_out12_carry_n_6,
      CO(0) => Switch9_out12_carry_n_7,
      DI(7) => u_Counter_Ctrl_n_96,
      DI(6) => u_Counter_Ctrl_n_97,
      DI(5) => u_Counter_Ctrl_n_98,
      DI(4) => u_Counter_Ctrl_n_99,
      DI(3) => u_Counter_Ctrl_n_100,
      DI(2) => u_Counter_Ctrl_n_101,
      DI(1) => u_Counter_Ctrl_n_102,
      DI(0) => u_Counter_Ctrl_n_103,
      O(7 downto 0) => NLW_Switch9_out12_carry_O_UNCONNECTED(7 downto 0),
      S(7) => u_Counter_Ctrl_n_88,
      S(6) => u_Counter_Ctrl_n_89,
      S(5) => u_Counter_Ctrl_n_90,
      S(4) => u_Counter_Ctrl_n_91,
      S(3) => u_Counter_Ctrl_n_92,
      S(2) => u_Counter_Ctrl_n_93,
      S(1) => u_Counter_Ctrl_n_94,
      S(0) => u_Counter_Ctrl_n_95
    );
\Switch9_out12_carry__0\: unisim.vcomponents.CARRY8
     port map (
      CI => Switch9_out12_carry_n_0,
      CI_TOP => '0',
      CO(7 downto 2) => \NLW_Switch9_out12_carry__0_CO_UNCONNECTED\(7 downto 2),
      CO(1) => Relational_Operator2_relop1,
      CO(0) => \Switch9_out12_carry__0_n_7\,
      DI(7 downto 2) => B"000000",
      DI(1) => u_Counter_Ctrl_n_65,
      DI(0) => u_Counter_Ctrl_n_66,
      O(7 downto 0) => \NLW_Switch9_out12_carry__0_O_UNCONNECTED\(7 downto 0),
      S(7 downto 2) => B"000000",
      S(1) => u_LimitPulseWidth_n_17,
      S(0) => u_Counter_Ctrl_n_67
    );
\T_carrier_us_AXI_1_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => \T_carrier_us_AXI_1_reg[24]_0\(0),
      Q => T_carrier_us(0),
      R => reset
    );
\T_carrier_us_AXI_1_reg[10]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => \T_carrier_us_AXI_1_reg[24]_0\(10),
      Q => T_carrier_us(10),
      R => reset
    );
\T_carrier_us_AXI_1_reg[11]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => \T_carrier_us_AXI_1_reg[24]_0\(11),
      Q => T_carrier_us(11),
      R => reset
    );
\T_carrier_us_AXI_1_reg[12]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => \T_carrier_us_AXI_1_reg[24]_0\(12),
      Q => T_carrier_us(12),
      R => reset
    );
\T_carrier_us_AXI_1_reg[13]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => \T_carrier_us_AXI_1_reg[24]_0\(13),
      Q => T_carrier_us(13),
      R => reset
    );
\T_carrier_us_AXI_1_reg[14]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => \T_carrier_us_AXI_1_reg[24]_0\(14),
      Q => T_carrier_us(14),
      R => reset
    );
\T_carrier_us_AXI_1_reg[15]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => \T_carrier_us_AXI_1_reg[24]_0\(15),
      Q => T_carrier_us(15),
      R => reset
    );
\T_carrier_us_AXI_1_reg[16]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => \T_carrier_us_AXI_1_reg[24]_0\(16),
      Q => T_carrier_us(16),
      R => reset
    );
\T_carrier_us_AXI_1_reg[17]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => \T_carrier_us_AXI_1_reg[24]_0\(17),
      Q => T_carrier_us(17),
      R => reset
    );
\T_carrier_us_AXI_1_reg[18]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => \T_carrier_us_AXI_1_reg[24]_0\(18),
      Q => T_carrier_us(18),
      R => reset
    );
\T_carrier_us_AXI_1_reg[19]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => \T_carrier_us_AXI_1_reg[24]_0\(19),
      Q => T_carrier_us(19),
      R => reset
    );
\T_carrier_us_AXI_1_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => \T_carrier_us_AXI_1_reg[24]_0\(1),
      Q => T_carrier_us(1),
      R => reset
    );
\T_carrier_us_AXI_1_reg[20]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => \T_carrier_us_AXI_1_reg[24]_0\(20),
      Q => T_carrier_us(20),
      R => reset
    );
\T_carrier_us_AXI_1_reg[21]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => \T_carrier_us_AXI_1_reg[24]_0\(21),
      Q => T_carrier_us(21),
      R => reset
    );
\T_carrier_us_AXI_1_reg[22]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => \T_carrier_us_AXI_1_reg[24]_0\(22),
      Q => T_carrier_us(22),
      R => reset
    );
\T_carrier_us_AXI_1_reg[23]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => \T_carrier_us_AXI_1_reg[24]_0\(23),
      Q => T_carrier_us(23),
      R => reset
    );
\T_carrier_us_AXI_1_reg[24]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => \T_carrier_us_AXI_1_reg[24]_0\(24),
      Q => T_carrier_us(24),
      R => reset
    );
\T_carrier_us_AXI_1_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => \T_carrier_us_AXI_1_reg[24]_0\(2),
      Q => T_carrier_us(2),
      R => reset
    );
\T_carrier_us_AXI_1_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => \T_carrier_us_AXI_1_reg[24]_0\(3),
      Q => T_carrier_us(3),
      R => reset
    );
\T_carrier_us_AXI_1_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => \T_carrier_us_AXI_1_reg[24]_0\(4),
      Q => T_carrier_us(4),
      R => reset
    );
\T_carrier_us_AXI_1_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => \T_carrier_us_AXI_1_reg[24]_0\(5),
      Q => T_carrier_us(5),
      R => reset
    );
\T_carrier_us_AXI_1_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => \T_carrier_us_AXI_1_reg[24]_0\(6),
      Q => T_carrier_us(6),
      R => reset
    );
\T_carrier_us_AXI_1_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => \T_carrier_us_AXI_1_reg[24]_0\(7),
      Q => T_carrier_us(7),
      R => reset
    );
\T_carrier_us_AXI_1_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => \T_carrier_us_AXI_1_reg[24]_0\(8),
      Q => T_carrier_us(8),
      R => reset
    );
\T_carrier_us_AXI_1_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => \T_carrier_us_AXI_1_reg[24]_0\(9),
      Q => T_carrier_us(9),
      R => reset
    );
\T_carrier_us_AXI_2_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => T_carrier_us(0),
      Q => Q(0),
      R => reset
    );
\T_carrier_us_AXI_2_reg[10]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => T_carrier_us(10),
      Q => Q(10),
      R => reset
    );
\T_carrier_us_AXI_2_reg[11]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => T_carrier_us(11),
      Q => Q(11),
      R => reset
    );
\T_carrier_us_AXI_2_reg[12]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => T_carrier_us(12),
      Q => Q(12),
      R => reset
    );
\T_carrier_us_AXI_2_reg[13]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => T_carrier_us(13),
      Q => Q(13),
      R => reset
    );
\T_carrier_us_AXI_2_reg[14]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => T_carrier_us(14),
      Q => Q(14),
      R => reset
    );
\T_carrier_us_AXI_2_reg[15]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => T_carrier_us(15),
      Q => Q(15),
      R => reset
    );
\T_carrier_us_AXI_2_reg[16]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => T_carrier_us(16),
      Q => Q(16),
      R => reset
    );
\T_carrier_us_AXI_2_reg[17]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => T_carrier_us(17),
      Q => Q(17),
      R => reset
    );
\T_carrier_us_AXI_2_reg[18]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => T_carrier_us(18),
      Q => Q(18),
      R => reset
    );
\T_carrier_us_AXI_2_reg[19]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => T_carrier_us(19),
      Q => Q(19),
      R => reset
    );
\T_carrier_us_AXI_2_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => T_carrier_us(1),
      Q => Q(1),
      R => reset
    );
\T_carrier_us_AXI_2_reg[20]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => T_carrier_us(20),
      Q => Q(20),
      R => reset
    );
\T_carrier_us_AXI_2_reg[21]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => T_carrier_us(21),
      Q => Q(21),
      R => reset
    );
\T_carrier_us_AXI_2_reg[22]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => T_carrier_us(22),
      Q => Q(22),
      R => reset
    );
\T_carrier_us_AXI_2_reg[23]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => T_carrier_us(23),
      Q => Q(23),
      R => reset
    );
\T_carrier_us_AXI_2_reg[24]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => T_carrier_us(24),
      Q => Q(24),
      R => reset
    );
\T_carrier_us_AXI_2_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => T_carrier_us(2),
      Q => Q(2),
      R => reset
    );
\T_carrier_us_AXI_2_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => T_carrier_us(3),
      Q => Q(3),
      R => reset
    );
\T_carrier_us_AXI_2_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => T_carrier_us(4),
      Q => Q(4),
      R => reset
    );
\T_carrier_us_AXI_2_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => T_carrier_us(5),
      Q => Q(5),
      R => reset
    );
\T_carrier_us_AXI_2_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => T_carrier_us(6),
      Q => Q(6),
      R => reset
    );
\T_carrier_us_AXI_2_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => T_carrier_us(7),
      Q => Q(7),
      R => reset
    );
\T_carrier_us_AXI_2_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => T_carrier_us(8),
      Q => Q(8),
      R => reset
    );
\T_carrier_us_AXI_2_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => T_carrier_us(9),
      Q => Q(9),
      R => reset
    );
\U1_norm_1_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => \U1_norm_1_reg[13]_0\(0),
      Q => U1_norm_1(0),
      R => reset
    );
\U1_norm_1_reg[10]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => \U1_norm_1_reg[13]_0\(10),
      Q => U1_norm_1(10),
      R => reset
    );
\U1_norm_1_reg[11]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => \U1_norm_1_reg[13]_0\(11),
      Q => U1_norm_1(11),
      R => reset
    );
\U1_norm_1_reg[12]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => \U1_norm_1_reg[13]_0\(12),
      Q => U1_norm_1(12),
      R => reset
    );
\U1_norm_1_reg[13]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => \U1_norm_1_reg[13]_0\(13),
      Q => U1_norm_1(13),
      R => reset
    );
\U1_norm_1_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => \U1_norm_1_reg[13]_0\(1),
      Q => U1_norm_1(1),
      R => reset
    );
\U1_norm_1_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => \U1_norm_1_reg[13]_0\(2),
      Q => U1_norm_1(2),
      R => reset
    );
\U1_norm_1_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => \U1_norm_1_reg[13]_0\(3),
      Q => U1_norm_1(3),
      R => reset
    );
\U1_norm_1_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => \U1_norm_1_reg[13]_0\(4),
      Q => U1_norm_1(4),
      R => reset
    );
\U1_norm_1_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => \U1_norm_1_reg[13]_0\(5),
      Q => U1_norm_1(5),
      R => reset
    );
\U1_norm_1_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => \U1_norm_1_reg[13]_0\(6),
      Q => U1_norm_1(6),
      R => reset
    );
\U1_norm_1_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => \U1_norm_1_reg[13]_0\(7),
      Q => U1_norm_1(7),
      R => reset
    );
\U1_norm_1_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => \U1_norm_1_reg[13]_0\(8),
      Q => U1_norm_1(8),
      R => reset
    );
\U1_norm_1_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => \U1_norm_1_reg[13]_0\(9),
      Q => U1_norm_1(9),
      R => reset
    );
\U2_norm_1_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => \U2_norm_1_reg[13]_0\(0),
      Q => U2_norm_1(0),
      R => reset
    );
\U2_norm_1_reg[10]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => \U2_norm_1_reg[13]_0\(10),
      Q => U2_norm_1(10),
      R => reset
    );
\U2_norm_1_reg[11]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => \U2_norm_1_reg[13]_0\(11),
      Q => U2_norm_1(11),
      R => reset
    );
\U2_norm_1_reg[12]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => \U2_norm_1_reg[13]_0\(12),
      Q => U2_norm_1(12),
      R => reset
    );
\U2_norm_1_reg[13]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => \U2_norm_1_reg[13]_0\(13),
      Q => U2_norm_1(13),
      R => reset
    );
\U2_norm_1_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => \U2_norm_1_reg[13]_0\(1),
      Q => U2_norm_1(1),
      R => reset
    );
\U2_norm_1_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => \U2_norm_1_reg[13]_0\(2),
      Q => U2_norm_1(2),
      R => reset
    );
\U2_norm_1_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => \U2_norm_1_reg[13]_0\(3),
      Q => U2_norm_1(3),
      R => reset
    );
\U2_norm_1_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => \U2_norm_1_reg[13]_0\(4),
      Q => U2_norm_1(4),
      R => reset
    );
\U2_norm_1_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => \U2_norm_1_reg[13]_0\(5),
      Q => U2_norm_1(5),
      R => reset
    );
\U2_norm_1_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => \U2_norm_1_reg[13]_0\(6),
      Q => U2_norm_1(6),
      R => reset
    );
\U2_norm_1_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => \U2_norm_1_reg[13]_0\(7),
      Q => U2_norm_1(7),
      R => reset
    );
\U2_norm_1_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => \U2_norm_1_reg[13]_0\(8),
      Q => U2_norm_1(8),
      R => reset
    );
\U2_norm_1_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => \U2_norm_1_reg[13]_0\(9),
      Q => U2_norm_1(9),
      R => reset
    );
\U3_norm_1_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => \U3_norm_1_reg[13]_0\(0),
      Q => U3_norm_1(0),
      R => reset
    );
\U3_norm_1_reg[10]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => \U3_norm_1_reg[13]_0\(10),
      Q => U3_norm_1(10),
      R => reset
    );
\U3_norm_1_reg[11]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => \U3_norm_1_reg[13]_0\(11),
      Q => U3_norm_1(11),
      R => reset
    );
\U3_norm_1_reg[12]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => \U3_norm_1_reg[13]_0\(12),
      Q => U3_norm_1(12),
      R => reset
    );
\U3_norm_1_reg[13]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => \U3_norm_1_reg[13]_0\(13),
      Q => U3_norm_1(13),
      R => reset
    );
\U3_norm_1_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => \U3_norm_1_reg[13]_0\(1),
      Q => U3_norm_1(1),
      R => reset
    );
\U3_norm_1_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => \U3_norm_1_reg[13]_0\(2),
      Q => U3_norm_1(2),
      R => reset
    );
\U3_norm_1_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => \U3_norm_1_reg[13]_0\(3),
      Q => U3_norm_1(3),
      R => reset
    );
\U3_norm_1_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => \U3_norm_1_reg[13]_0\(4),
      Q => U3_norm_1(4),
      R => reset
    );
\U3_norm_1_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => \U3_norm_1_reg[13]_0\(5),
      Q => U3_norm_1(5),
      R => reset
    );
\U3_norm_1_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => \U3_norm_1_reg[13]_0\(6),
      Q => U3_norm_1(6),
      R => reset
    );
\U3_norm_1_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => \U3_norm_1_reg[13]_0\(7),
      Q => U3_norm_1(7),
      R => reset
    );
\U3_norm_1_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => \U3_norm_1_reg[13]_0\(8),
      Q => U3_norm_1(8),
      R => reset
    );
\U3_norm_1_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => \U3_norm_1_reg[13]_0\(9),
      Q => U3_norm_1(9),
      R => reset
    );
\f_carrier_kHz_AXI_1_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => D(0),
      Q => f_carrier_kHz(0),
      R => reset
    );
\f_carrier_kHz_AXI_1_reg[10]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => D(10),
      Q => f_carrier_kHz(10),
      R => reset
    );
\f_carrier_kHz_AXI_1_reg[11]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => D(11),
      Q => f_carrier_kHz(11),
      R => reset
    );
\f_carrier_kHz_AXI_1_reg[12]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => D(12),
      Q => f_carrier_kHz(12),
      R => reset
    );
\f_carrier_kHz_AXI_1_reg[13]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => D(13),
      Q => f_carrier_kHz(13),
      R => reset
    );
\f_carrier_kHz_AXI_1_reg[14]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => D(14),
      Q => f_carrier_kHz(14),
      R => reset
    );
\f_carrier_kHz_AXI_1_reg[15]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => D(15),
      Q => f_carrier_kHz(15),
      R => reset
    );
\f_carrier_kHz_AXI_1_reg[16]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => D(16),
      Q => f_carrier_kHz(16),
      R => reset
    );
\f_carrier_kHz_AXI_1_reg[17]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => D(17),
      Q => f_carrier_kHz(17),
      R => reset
    );
\f_carrier_kHz_AXI_1_reg[18]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => D(18),
      Q => f_carrier_kHz(18),
      R => reset
    );
\f_carrier_kHz_AXI_1_reg[19]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => D(19),
      Q => f_carrier_kHz(19),
      R => reset
    );
\f_carrier_kHz_AXI_1_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => D(1),
      Q => f_carrier_kHz(1),
      R => reset
    );
\f_carrier_kHz_AXI_1_reg[20]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => D(20),
      Q => f_carrier_kHz(20),
      R => reset
    );
\f_carrier_kHz_AXI_1_reg[21]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => D(21),
      Q => f_carrier_kHz(21),
      R => reset
    );
\f_carrier_kHz_AXI_1_reg[22]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => D(22),
      Q => f_carrier_kHz(22),
      R => reset
    );
\f_carrier_kHz_AXI_1_reg[23]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => D(23),
      Q => f_carrier_kHz(23),
      R => reset
    );
\f_carrier_kHz_AXI_1_reg[24]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => D(24),
      Q => f_carrier_kHz(24),
      R => reset
    );
\f_carrier_kHz_AXI_1_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => D(2),
      Q => f_carrier_kHz(2),
      R => reset
    );
\f_carrier_kHz_AXI_1_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => D(3),
      Q => f_carrier_kHz(3),
      R => reset
    );
\f_carrier_kHz_AXI_1_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => D(4),
      Q => f_carrier_kHz(4),
      R => reset
    );
\f_carrier_kHz_AXI_1_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => D(5),
      Q => f_carrier_kHz(5),
      R => reset
    );
\f_carrier_kHz_AXI_1_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => D(6),
      Q => f_carrier_kHz(6),
      R => reset
    );
\f_carrier_kHz_AXI_1_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => D(7),
      Q => f_carrier_kHz(7),
      R => reset
    );
\f_carrier_kHz_AXI_1_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => D(8),
      Q => f_carrier_kHz(8),
      R => reset
    );
\f_carrier_kHz_AXI_1_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => D(9),
      Q => f_carrier_kHz(9),
      R => reset
    );
\f_carrier_kHz_AXI_2_reg[10]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => f_carrier_kHz(10),
      Q => \f_carrier_kHz_AXI_2_reg[24]_0\(1),
      R => reset
    );
\f_carrier_kHz_AXI_2_reg[11]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => f_carrier_kHz(11),
      Q => \f_carrier_kHz_AXI_2_reg[24]_0\(2),
      R => reset
    );
\f_carrier_kHz_AXI_2_reg[12]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => f_carrier_kHz(12),
      Q => \f_carrier_kHz_AXI_2_reg[24]_0\(3),
      R => reset
    );
\f_carrier_kHz_AXI_2_reg[13]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => f_carrier_kHz(13),
      Q => \f_carrier_kHz_AXI_2_reg[24]_0\(4),
      R => reset
    );
\f_carrier_kHz_AXI_2_reg[14]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => f_carrier_kHz(14),
      Q => \f_carrier_kHz_AXI_2_reg[24]_0\(5),
      R => reset
    );
\f_carrier_kHz_AXI_2_reg[15]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => f_carrier_kHz(15),
      Q => \f_carrier_kHz_AXI_2_reg[24]_0\(6),
      R => reset
    );
\f_carrier_kHz_AXI_2_reg[16]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => f_carrier_kHz(16),
      Q => \f_carrier_kHz_AXI_2_reg[24]_0\(7),
      R => reset
    );
\f_carrier_kHz_AXI_2_reg[17]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => f_carrier_kHz(17),
      Q => \f_carrier_kHz_AXI_2_reg[24]_0\(8),
      R => reset
    );
\f_carrier_kHz_AXI_2_reg[18]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => f_carrier_kHz(18),
      Q => \f_carrier_kHz_AXI_2_reg[24]_0\(9),
      R => reset
    );
\f_carrier_kHz_AXI_2_reg[19]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => f_carrier_kHz(19),
      Q => \f_carrier_kHz_AXI_2_reg[24]_0\(10),
      R => reset
    );
\f_carrier_kHz_AXI_2_reg[20]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => f_carrier_kHz(20),
      Q => \f_carrier_kHz_AXI_2_reg[24]_0\(11),
      R => reset
    );
\f_carrier_kHz_AXI_2_reg[21]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => f_carrier_kHz(21),
      Q => \f_carrier_kHz_AXI_2_reg[24]_0\(12),
      R => reset
    );
\f_carrier_kHz_AXI_2_reg[22]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => f_carrier_kHz(22),
      Q => \f_carrier_kHz_AXI_2_reg[24]_0\(13),
      R => reset
    );
\f_carrier_kHz_AXI_2_reg[23]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => f_carrier_kHz(23),
      Q => \f_carrier_kHz_AXI_2_reg[24]_0\(14),
      R => reset
    );
\f_carrier_kHz_AXI_2_reg[24]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => f_carrier_kHz(24),
      Q => \f_carrier_kHz_AXI_2_reg[24]_0\(15),
      R => reset
    );
\i__carry__0_i_1\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"2"
    )
        port map (
      I0 => min_pulse_width(16),
      I1 => min_pulse_width(17),
      O => \i__carry__0_i_1_n_0\
    );
\min_pulse_width_AXI_1_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => \min_pulse_width_AXI_1_reg[17]_0\(0),
      Q => min_pulse_width(0),
      R => reset
    );
\min_pulse_width_AXI_1_reg[10]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => \min_pulse_width_AXI_1_reg[17]_0\(10),
      Q => min_pulse_width(10),
      R => reset
    );
\min_pulse_width_AXI_1_reg[11]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => \min_pulse_width_AXI_1_reg[17]_0\(11),
      Q => min_pulse_width(11),
      R => reset
    );
\min_pulse_width_AXI_1_reg[12]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => \min_pulse_width_AXI_1_reg[17]_0\(12),
      Q => min_pulse_width(12),
      R => reset
    );
\min_pulse_width_AXI_1_reg[13]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => \min_pulse_width_AXI_1_reg[17]_0\(13),
      Q => min_pulse_width(13),
      R => reset
    );
\min_pulse_width_AXI_1_reg[14]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => \min_pulse_width_AXI_1_reg[17]_0\(14),
      Q => min_pulse_width(14),
      R => reset
    );
\min_pulse_width_AXI_1_reg[15]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => \min_pulse_width_AXI_1_reg[17]_0\(15),
      Q => min_pulse_width(15),
      R => reset
    );
\min_pulse_width_AXI_1_reg[16]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => \min_pulse_width_AXI_1_reg[17]_0\(16),
      Q => min_pulse_width(16),
      R => reset
    );
\min_pulse_width_AXI_1_reg[17]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => \min_pulse_width_AXI_1_reg[17]_0\(17),
      Q => min_pulse_width(17),
      R => reset
    );
\min_pulse_width_AXI_1_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => \min_pulse_width_AXI_1_reg[17]_0\(1),
      Q => min_pulse_width(1),
      R => reset
    );
\min_pulse_width_AXI_1_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => \min_pulse_width_AXI_1_reg[17]_0\(2),
      Q => min_pulse_width(2),
      R => reset
    );
\min_pulse_width_AXI_1_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => \min_pulse_width_AXI_1_reg[17]_0\(3),
      Q => min_pulse_width(3),
      R => reset
    );
\min_pulse_width_AXI_1_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => \min_pulse_width_AXI_1_reg[17]_0\(4),
      Q => min_pulse_width(4),
      R => reset
    );
\min_pulse_width_AXI_1_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => \min_pulse_width_AXI_1_reg[17]_0\(5),
      Q => min_pulse_width(5),
      R => reset
    );
\min_pulse_width_AXI_1_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => \min_pulse_width_AXI_1_reg[17]_0\(6),
      Q => min_pulse_width(6),
      R => reset
    );
\min_pulse_width_AXI_1_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => \min_pulse_width_AXI_1_reg[17]_0\(7),
      Q => min_pulse_width(7),
      R => reset
    );
\min_pulse_width_AXI_1_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => \min_pulse_width_AXI_1_reg[17]_0\(8),
      Q => min_pulse_width(8),
      R => reset
    );
\min_pulse_width_AXI_1_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => \min_pulse_width_AXI_1_reg[17]_0\(9),
      Q => min_pulse_width(9),
      R => reset
    );
\min_pulse_width_AXI_2_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => min_pulse_width(0),
      Q => \min_pulse_width_AXI_2_reg[17]_0\(0),
      R => reset
    );
\min_pulse_width_AXI_2_reg[10]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => min_pulse_width(10),
      Q => \min_pulse_width_AXI_2_reg[17]_0\(10),
      R => reset
    );
\min_pulse_width_AXI_2_reg[11]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => min_pulse_width(11),
      Q => \min_pulse_width_AXI_2_reg[17]_0\(11),
      R => reset
    );
\min_pulse_width_AXI_2_reg[12]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => min_pulse_width(12),
      Q => \min_pulse_width_AXI_2_reg[17]_0\(12),
      R => reset
    );
\min_pulse_width_AXI_2_reg[13]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => min_pulse_width(13),
      Q => \min_pulse_width_AXI_2_reg[17]_0\(13),
      R => reset
    );
\min_pulse_width_AXI_2_reg[14]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => min_pulse_width(14),
      Q => \min_pulse_width_AXI_2_reg[17]_0\(14),
      R => reset
    );
\min_pulse_width_AXI_2_reg[15]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => min_pulse_width(15),
      Q => \min_pulse_width_AXI_2_reg[17]_0\(15),
      R => reset
    );
\min_pulse_width_AXI_2_reg[16]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => min_pulse_width(16),
      Q => \min_pulse_width_AXI_2_reg[17]_0\(16),
      R => reset
    );
\min_pulse_width_AXI_2_reg[17]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => min_pulse_width(17),
      Q => \min_pulse_width_AXI_2_reg[17]_0\(17),
      R => reset
    );
\min_pulse_width_AXI_2_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => min_pulse_width(1),
      Q => \min_pulse_width_AXI_2_reg[17]_0\(1),
      R => reset
    );
\min_pulse_width_AXI_2_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => min_pulse_width(2),
      Q => \min_pulse_width_AXI_2_reg[17]_0\(2),
      R => reset
    );
\min_pulse_width_AXI_2_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => min_pulse_width(3),
      Q => \min_pulse_width_AXI_2_reg[17]_0\(3),
      R => reset
    );
\min_pulse_width_AXI_2_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => min_pulse_width(4),
      Q => \min_pulse_width_AXI_2_reg[17]_0\(4),
      R => reset
    );
\min_pulse_width_AXI_2_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => min_pulse_width(5),
      Q => \min_pulse_width_AXI_2_reg[17]_0\(5),
      R => reset
    );
\min_pulse_width_AXI_2_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => min_pulse_width(6),
      Q => \min_pulse_width_AXI_2_reg[17]_0\(6),
      R => reset
    );
\min_pulse_width_AXI_2_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => min_pulse_width(7),
      Q => \min_pulse_width_AXI_2_reg[17]_0\(7),
      R => reset
    );
\min_pulse_width_AXI_2_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => min_pulse_width(8),
      Q => \min_pulse_width_AXI_2_reg[17]_0\(8),
      R => reset
    );
\min_pulse_width_AXI_2_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => min_pulse_width(9),
      Q => \min_pulse_width_AXI_2_reg[17]_0\(9),
      R => reset
    );
u_Counter_Ctrl: entity work.zusys_PWM_and_SS_control_V_0_2_PWM_and_SS_control_V3_ip_src_Counter_Ctrl
     port map (
      Add_out1(13 downto 0) => Add_out1(17 downto 4),
      \Allow_assymetrical_anew_reference_value__0\ => \Allow_assymetrical_anew_reference_value__0\,
      B(15 downto 8) => HDL_Counter2_count_next(16 downto 9),
      B(7 downto 0) => B(7 downto 0),
      CEB2 => CEB2,
      CO(0) => Counter_Ctrl_out3,
      D(24 downto 0) => D(24 downto 0),
      DI(0) => \^di\(1),
      \Delay1_out1_reg[12]\(6) => u_Counter_Ctrl_n_104,
      \Delay1_out1_reg[12]\(5) => u_Counter_Ctrl_n_105,
      \Delay1_out1_reg[12]\(4) => u_Counter_Ctrl_n_106,
      \Delay1_out1_reg[12]\(3) => u_Counter_Ctrl_n_107,
      \Delay1_out1_reg[12]\(2) => u_Counter_Ctrl_n_108,
      \Delay1_out1_reg[12]\(1) => u_Counter_Ctrl_n_109,
      \Delay1_out1_reg[12]\(0) => u_Counter_Ctrl_n_110,
      \Delay1_out1_reg[12]_0\(6) => u_Counter_Ctrl_n_112,
      \Delay1_out1_reg[12]_0\(5) => u_Counter_Ctrl_n_113,
      \Delay1_out1_reg[12]_0\(4) => u_Counter_Ctrl_n_114,
      \Delay1_out1_reg[12]_0\(3) => u_Counter_Ctrl_n_115,
      \Delay1_out1_reg[12]_0\(2) => u_Counter_Ctrl_n_116,
      \Delay1_out1_reg[12]_0\(1) => u_Counter_Ctrl_n_117,
      \Delay1_out1_reg[12]_0\(0) => u_Counter_Ctrl_n_118,
      \Delay1_out1_reg[12]_1\(6) => u_Counter_Ctrl_n_135,
      \Delay1_out1_reg[12]_1\(5) => u_Counter_Ctrl_n_136,
      \Delay1_out1_reg[12]_1\(4) => u_Counter_Ctrl_n_137,
      \Delay1_out1_reg[12]_1\(3) => u_Counter_Ctrl_n_138,
      \Delay1_out1_reg[12]_1\(2) => u_Counter_Ctrl_n_139,
      \Delay1_out1_reg[12]_1\(1) => u_Counter_Ctrl_n_140,
      \Delay1_out1_reg[12]_1\(0) => u_Counter_Ctrl_n_141,
      \Delay1_out1_reg[12]_2\(0) => u_Counter_Ctrl_n_202,
      \Delay1_out1_reg[13]\(13 downto 0) => Delay1_out1(13 downto 0),
      \Delay1_out1_reg[13]_0\(13 downto 0) => U2_norm_1(13 downto 0),
      \Delay2_out1_reg[12]\(6) => u_Counter_Ctrl_n_49,
      \Delay2_out1_reg[12]\(5) => u_Counter_Ctrl_n_50,
      \Delay2_out1_reg[12]\(4) => u_Counter_Ctrl_n_51,
      \Delay2_out1_reg[12]\(3) => u_Counter_Ctrl_n_52,
      \Delay2_out1_reg[12]\(2) => u_Counter_Ctrl_n_53,
      \Delay2_out1_reg[12]\(1) => u_Counter_Ctrl_n_54,
      \Delay2_out1_reg[12]\(0) => u_Counter_Ctrl_n_55,
      \Delay2_out1_reg[12]_0\(6) => u_Counter_Ctrl_n_58,
      \Delay2_out1_reg[12]_0\(5) => u_Counter_Ctrl_n_59,
      \Delay2_out1_reg[12]_0\(4) => u_Counter_Ctrl_n_60,
      \Delay2_out1_reg[12]_0\(3) => u_Counter_Ctrl_n_61,
      \Delay2_out1_reg[12]_0\(2) => u_Counter_Ctrl_n_62,
      \Delay2_out1_reg[12]_0\(1) => u_Counter_Ctrl_n_63,
      \Delay2_out1_reg[12]_0\(0) => u_Counter_Ctrl_n_64,
      \Delay2_out1_reg[12]_1\(6) => u_Counter_Ctrl_n_81,
      \Delay2_out1_reg[12]_1\(5) => u_Counter_Ctrl_n_82,
      \Delay2_out1_reg[12]_1\(4) => u_Counter_Ctrl_n_83,
      \Delay2_out1_reg[12]_1\(3) => u_Counter_Ctrl_n_84,
      \Delay2_out1_reg[12]_1\(2) => u_Counter_Ctrl_n_85,
      \Delay2_out1_reg[12]_1\(1) => u_Counter_Ctrl_n_86,
      \Delay2_out1_reg[12]_1\(0) => u_Counter_Ctrl_n_87,
      \Delay2_out1_reg[12]_2\(0) => u_Counter_Ctrl_n_201,
      \Delay2_out1_reg[13]\(13 downto 0) => Delay2_out1(13 downto 0),
      \Delay2_out1_reg[13]_0\(13 downto 0) => U3_norm_1(13 downto 0),
      \Delay2_out1_reg[13]_1\ => u_LimitPulseWidth_n_50,
      Delay6_out1_reg_0 => \^hdl_counter2_count_reg[2]_0\,
      Delay6_out1_reg_1 => \^hdl_counter2_count_reg[3]_0\,
      \Delay_out1_reg[12]\(6) => u_Counter_Ctrl_n_158,
      \Delay_out1_reg[12]\(5) => u_Counter_Ctrl_n_159,
      \Delay_out1_reg[12]\(4) => u_Counter_Ctrl_n_160,
      \Delay_out1_reg[12]\(3) => u_Counter_Ctrl_n_161,
      \Delay_out1_reg[12]\(2) => u_Counter_Ctrl_n_162,
      \Delay_out1_reg[12]\(1) => u_Counter_Ctrl_n_163,
      \Delay_out1_reg[12]\(0) => u_Counter_Ctrl_n_164,
      \Delay_out1_reg[12]_0\(6) => u_Counter_Ctrl_n_179,
      \Delay_out1_reg[12]_0\(5) => u_Counter_Ctrl_n_180,
      \Delay_out1_reg[12]_0\(4) => u_Counter_Ctrl_n_181,
      \Delay_out1_reg[12]_0\(3) => u_Counter_Ctrl_n_182,
      \Delay_out1_reg[12]_0\(2) => u_Counter_Ctrl_n_183,
      \Delay_out1_reg[12]_0\(1) => u_Counter_Ctrl_n_184,
      \Delay_out1_reg[12]_0\(0) => u_Counter_Ctrl_n_185,
      \Delay_out1_reg[12]_1\(0) => u_Counter_Ctrl_n_203,
      \Delay_out1_reg[12]_2\(0) => u_Counter_Ctrl_n_204,
      \Delay_out1_reg[13]\(13 downto 0) => Delay_out1(13 downto 0),
      \Delay_out1_reg[13]_0\(13 downto 0) => U1_norm_1(13 downto 0),
      E(0) => E(0),
      HDL_Counter2_count_reg(12 downto 1) => HDL_Counter2_count_reg(19 downto 8),
      HDL_Counter2_count_reg(0) => HDL_Counter2_count_reg(1),
      \HDL_Counter2_count_reg[0]\(7) => u_Counter_Ctrl_n_26,
      \HDL_Counter2_count_reg[0]\(6) => u_Counter_Ctrl_n_27,
      \HDL_Counter2_count_reg[0]\(5) => u_Counter_Ctrl_n_28,
      \HDL_Counter2_count_reg[0]\(4) => u_Counter_Ctrl_n_29,
      \HDL_Counter2_count_reg[0]\(3) => u_Counter_Ctrl_n_30,
      \HDL_Counter2_count_reg[0]\(2) => u_Counter_Ctrl_n_31,
      \HDL_Counter2_count_reg[0]\(1) => u_Counter_Ctrl_n_32,
      \HDL_Counter2_count_reg[0]\(0) => u_Counter_Ctrl_n_33,
      \HDL_Counter2_count_reg[0]_0\(3) => u_Counter_Ctrl_n_34,
      \HDL_Counter2_count_reg[0]_0\(2) => u_Counter_Ctrl_n_35,
      \HDL_Counter2_count_reg[0]_0\(1) => u_Counter_Ctrl_n_36,
      \HDL_Counter2_count_reg[0]_0\(0) => u_Counter_Ctrl_n_37,
      \HDL_Counter2_count_reg[0]_1\(0) => \HDL_Counter2_count_reg[0]_0\(0),
      \HDL_Counter2_count_reg[0]_2\(1 downto 0) => S(1 downto 0),
      \HDL_Counter2_count_reg[15]\(7) => u_Counter_Ctrl_n_38,
      \HDL_Counter2_count_reg[15]\(6) => u_Counter_Ctrl_n_39,
      \HDL_Counter2_count_reg[15]\(5) => u_Counter_Ctrl_n_40,
      \HDL_Counter2_count_reg[15]\(4) => u_Counter_Ctrl_n_41,
      \HDL_Counter2_count_reg[15]\(3) => u_Counter_Ctrl_n_42,
      \HDL_Counter2_count_reg[15]\(2) => u_Counter_Ctrl_n_43,
      \HDL_Counter2_count_reg[15]\(1) => u_Counter_Ctrl_n_44,
      \HDL_Counter2_count_reg[15]\(0) => u_Counter_Ctrl_n_45,
      \HDL_Counter2_count_reg[7]_0\ => \^hdl_counter2_count_reg[7]_0\,
      \HDL_Counter2_count_reg[7]_1\ => \^hdl_counter2_count_reg[6]_0\,
      \HDL_Counter2_count_reg[7]_2\ => \^hdl_counter2_count_reg[5]_0\,
      \HDL_Counter2_count_reg[7]_3\ => \^hdl_counter2_count_reg[4]_0\,
      HDL_Counter2_count_reg_7_sp_1 => \^di\(0),
      IPCORE_CLK => IPCORE_CLK,
      \Logical_Operator_out10_carry__0_0\(24 downto 0) => T_carrier_us(24 downto 0),
      O(7) => u_Counter_Ctrl_n_17,
      O(6) => u_Counter_Ctrl_n_18,
      O(5) => u_Counter_Ctrl_n_19,
      O(4) => u_Counter_Ctrl_n_20,
      O(3) => u_Counter_Ctrl_n_21,
      O(2) => u_Counter_Ctrl_n_22,
      O(1) => u_Counter_Ctrl_n_23,
      O(0) => u_Counter_Ctrl_n_24,
      P(5) => u_Counter_Ctrl_n_0,
      P(4) => u_Counter_Ctrl_n_1,
      P(3) => u_Counter_Ctrl_n_2,
      P(2) => u_Counter_Ctrl_n_3,
      P(1) => u_Counter_Ctrl_n_4,
      P(0) => u_Counter_Ctrl_n_5,
      \Product_mul_temp[-1111111102]_0\(0) => \f_carrier_kHz_AXI_2_reg[24]_0\(0),
      \Product_mul_temp[-1111111103]_0\ => \Product_mul_temp[-1111111103]\,
      \Product_mul_temp[-1111111104]_0\ => \Product_mul_temp[-1111111104]\,
      \Product_mul_temp[-1111111105]_0\ => \Product_mul_temp[-1111111105]\,
      \Product_mul_temp[-1111111106]_0\ => \Product_mul_temp[-1111111106]\,
      \Product_mul_temp[-1111111107]_0\ => \Product_mul_temp[-1111111107]\,
      \Product_mul_temp[-1111111108]_0\ => \Product_mul_temp[-1111111108]\,
      \Product_mul_temp[-1111111109]_0\ => \Product_mul_temp[-1111111109]\,
      \Product_mul_temp[-1111111110]_0\ => \Product_mul_temp[-1111111110]\,
      \Product_mul_temp[-1111111111]_0\ => \Product_mul_temp[-1111111111]\,
      Q(9 downto 0) => f_carrier_kHz(9 downto 0),
      Relational_Operator_1_cast(13 downto 0) => Relational_Operator_1_cast(17 downto 4),
      S(0) => u_LimitPulseWidth_n_56,
      Saturation_out1(12 downto 0) => Saturation_out1(16 downto 4),
      Switch6_out1 => Switch6_out1,
      Switch7_out12_carry(0) => Relational_Operator1_relop1_1,
      Switch7_out12_carry_0(0) => Relational_Operator_relop1_0,
      Switch7_out12_carry_i_6 => u_LimitPulseWidth_n_51,
      Switch7_out12_carry_i_6_0 => u_LimitPulseWidth_n_53,
      Switch7_out12_carry_i_6_1 => u_LimitPulseWidth_n_52,
      Switch8_out12_carry(0) => Relational_Operator_relop1_2,
      Switch8_out12_carry_0(0) => Relational_Operator1_relop1_3,
      Switch9_out12_carry(0) => Relational_Operator_relop1_4,
      Switch9_out12_carry_0(0) => Relational_Operator1_relop1_5,
      \U1_norm_1_reg[10]\(5) => u_Counter_Ctrl_n_188,
      \U1_norm_1_reg[10]\(4) => u_Counter_Ctrl_n_189,
      \U1_norm_1_reg[10]\(3) => u_Counter_Ctrl_n_190,
      \U1_norm_1_reg[10]\(2) => u_Counter_Ctrl_n_191,
      \U1_norm_1_reg[10]\(1) => u_Counter_Ctrl_n_192,
      \U1_norm_1_reg[10]\(0) => u_Counter_Ctrl_n_193,
      \U1_norm_1_reg[11]\(0) => u_Counter_Ctrl_n_187,
      \U1_norm_1_reg[12]\(0) => u_Counter_Ctrl_n_186,
      \U1_norm_1_reg[9]\(5) => u_Counter_Ctrl_n_194,
      \U1_norm_1_reg[9]\(4) => u_Counter_Ctrl_n_195,
      \U1_norm_1_reg[9]\(3) => u_Counter_Ctrl_n_196,
      \U1_norm_1_reg[9]\(2) => u_Counter_Ctrl_n_197,
      \U1_norm_1_reg[9]\(1) => u_Counter_Ctrl_n_198,
      \U1_norm_1_reg[9]\(0) => u_Counter_Ctrl_n_199,
      \U2_norm_1_reg[10]\(7) => u_Counter_Ctrl_n_142,
      \U2_norm_1_reg[10]\(6) => u_Counter_Ctrl_n_143,
      \U2_norm_1_reg[10]\(5) => u_Counter_Ctrl_n_144,
      \U2_norm_1_reg[10]\(4) => u_Counter_Ctrl_n_145,
      \U2_norm_1_reg[10]\(3) => u_Counter_Ctrl_n_146,
      \U2_norm_1_reg[10]\(2) => u_Counter_Ctrl_n_147,
      \U2_norm_1_reg[10]\(1) => u_Counter_Ctrl_n_148,
      \U2_norm_1_reg[10]\(0) => u_Counter_Ctrl_n_149,
      \U2_norm_1_reg[12]\(0) => u_Counter_Ctrl_n_121,
      \U2_norm_1_reg[12]_0\(12) => u_Counter_Ctrl_n_122,
      \U2_norm_1_reg[12]_0\(11) => u_Counter_Ctrl_n_123,
      \U2_norm_1_reg[12]_0\(10) => u_Counter_Ctrl_n_124,
      \U2_norm_1_reg[12]_0\(9) => u_Counter_Ctrl_n_125,
      \U2_norm_1_reg[12]_0\(8) => u_Counter_Ctrl_n_126,
      \U2_norm_1_reg[12]_0\(7) => u_Counter_Ctrl_n_127,
      \U2_norm_1_reg[12]_0\(6) => u_Counter_Ctrl_n_128,
      \U2_norm_1_reg[12]_0\(5) => u_Counter_Ctrl_n_129,
      \U2_norm_1_reg[12]_0\(4) => u_Counter_Ctrl_n_130,
      \U2_norm_1_reg[12]_0\(3) => u_Counter_Ctrl_n_131,
      \U2_norm_1_reg[12]_0\(2) => u_Counter_Ctrl_n_132,
      \U2_norm_1_reg[12]_0\(1) => u_Counter_Ctrl_n_133,
      \U2_norm_1_reg[12]_0\(0) => u_Counter_Ctrl_n_134,
      \U2_norm_1_reg[13]\ => u_Counter_Ctrl_n_111,
      \U2_norm_1_reg[13]_0\(1) => u_Counter_Ctrl_n_119,
      \U2_norm_1_reg[13]_0\(0) => u_Counter_Ctrl_n_120,
      \U2_norm_1_reg[9]\(7) => u_Counter_Ctrl_n_150,
      \U2_norm_1_reg[9]\(6) => u_Counter_Ctrl_n_151,
      \U2_norm_1_reg[9]\(5) => u_Counter_Ctrl_n_152,
      \U2_norm_1_reg[9]\(4) => u_Counter_Ctrl_n_153,
      \U2_norm_1_reg[9]\(3) => u_Counter_Ctrl_n_154,
      \U2_norm_1_reg[9]\(2) => u_Counter_Ctrl_n_155,
      \U2_norm_1_reg[9]\(1) => u_Counter_Ctrl_n_156,
      \U2_norm_1_reg[9]\(0) => u_Counter_Ctrl_n_157,
      \U3_norm_1_reg[10]\(7) => u_Counter_Ctrl_n_88,
      \U3_norm_1_reg[10]\(6) => u_Counter_Ctrl_n_89,
      \U3_norm_1_reg[10]\(5) => u_Counter_Ctrl_n_90,
      \U3_norm_1_reg[10]\(4) => u_Counter_Ctrl_n_91,
      \U3_norm_1_reg[10]\(3) => u_Counter_Ctrl_n_92,
      \U3_norm_1_reg[10]\(2) => u_Counter_Ctrl_n_93,
      \U3_norm_1_reg[10]\(1) => u_Counter_Ctrl_n_94,
      \U3_norm_1_reg[10]\(0) => u_Counter_Ctrl_n_95,
      \U3_norm_1_reg[12]\(0) => u_Counter_Ctrl_n_67,
      \U3_norm_1_reg[12]_0\(12) => u_Counter_Ctrl_n_68,
      \U3_norm_1_reg[12]_0\(11) => u_Counter_Ctrl_n_69,
      \U3_norm_1_reg[12]_0\(10) => u_Counter_Ctrl_n_70,
      \U3_norm_1_reg[12]_0\(9) => u_Counter_Ctrl_n_71,
      \U3_norm_1_reg[12]_0\(8) => u_Counter_Ctrl_n_72,
      \U3_norm_1_reg[12]_0\(7) => u_Counter_Ctrl_n_73,
      \U3_norm_1_reg[12]_0\(6) => u_Counter_Ctrl_n_74,
      \U3_norm_1_reg[12]_0\(5) => u_Counter_Ctrl_n_75,
      \U3_norm_1_reg[12]_0\(4) => u_Counter_Ctrl_n_76,
      \U3_norm_1_reg[12]_0\(3) => u_Counter_Ctrl_n_77,
      \U3_norm_1_reg[12]_0\(2) => u_Counter_Ctrl_n_78,
      \U3_norm_1_reg[12]_0\(1) => u_Counter_Ctrl_n_79,
      \U3_norm_1_reg[12]_0\(0) => u_Counter_Ctrl_n_80,
      \U3_norm_1_reg[13]\ => u_Counter_Ctrl_n_56,
      \U3_norm_1_reg[13]_0\(1) => u_Counter_Ctrl_n_65,
      \U3_norm_1_reg[13]_0\(0) => u_Counter_Ctrl_n_66,
      \U3_norm_1_reg[9]\(7) => u_Counter_Ctrl_n_96,
      \U3_norm_1_reg[9]\(6) => u_Counter_Ctrl_n_97,
      \U3_norm_1_reg[9]\(5) => u_Counter_Ctrl_n_98,
      \U3_norm_1_reg[9]\(4) => u_Counter_Ctrl_n_99,
      \U3_norm_1_reg[9]\(3) => u_Counter_Ctrl_n_100,
      \U3_norm_1_reg[9]\(2) => u_Counter_Ctrl_n_101,
      \U3_norm_1_reg[9]\(1) => u_Counter_Ctrl_n_102,
      \U3_norm_1_reg[9]\(0) => u_Counter_Ctrl_n_103,
      reset => reset
    );
u_LimitPulseWidth: entity work.zusys_PWM_and_SS_control_V_0_2_PWM_and_SS_control_V3_ip_src_LimitPulseWidth
     port map (
      Add_out1(13 downto 0) => Add_out1(17 downto 4),
      \Allow_assymetrical_anew_reference_value__0\ => \Allow_assymetrical_anew_reference_value__0\,
      Counter_Ctrl_out3_1_reg(0) => T_carrier_us(24),
      Counter_Ctrl_out4_1_reg => \^di\(0),
      Counter_Ctrl_out4_1_reg_0 => \^hdl_counter2_count_reg[4]_0\,
      Counter_Ctrl_out4_1_reg_1 => \^hdl_counter2_count_reg[2]_0\,
      D(5) => u_Counter_Ctrl_n_69,
      D(4) => u_Counter_Ctrl_n_71,
      D(3) => u_Counter_Ctrl_n_73,
      D(2) => u_Counter_Ctrl_n_75,
      D(1) => u_Counter_Ctrl_n_77,
      D(0) => u_Counter_Ctrl_n_79,
      DI(6) => u_LimitPulseWidth_n_18,
      DI(5) => u_LimitPulseWidth_n_19,
      DI(4) => u_LimitPulseWidth_n_20,
      DI(3) => u_LimitPulseWidth_n_21,
      DI(2) => u_LimitPulseWidth_n_22,
      DI(1) => u_LimitPulseWidth_n_23,
      DI(0) => u_LimitPulseWidth_n_24,
      \Delay1_out1_reg[10]\(6) => u_LimitPulseWidth_n_39,
      \Delay1_out1_reg[10]\(5) => u_LimitPulseWidth_n_40,
      \Delay1_out1_reg[10]\(4) => u_LimitPulseWidth_n_41,
      \Delay1_out1_reg[10]\(3) => u_LimitPulseWidth_n_42,
      \Delay1_out1_reg[10]\(2) => u_LimitPulseWidth_n_43,
      \Delay1_out1_reg[10]\(1) => u_LimitPulseWidth_n_44,
      \Delay1_out1_reg[10]\(0) => u_LimitPulseWidth_n_45,
      \Delay1_out1_reg[13]\(0) => u_LimitPulseWidth_n_38,
      \Delay2_out1_reg[13]\(0) => u_LimitPulseWidth_n_17,
      \Delay_out1[13]_i_2_0\ => \^hdl_counter2_count_reg[7]_0\,
      \Delay_out1[13]_i_2_1\ => \^hdl_counter2_count_reg[6]_0\,
      \Delay_out1[13]_i_2_2\ => \^hdl_counter2_count_reg[5]_0\,
      \Delay_out1[13]_i_2_3\ => \^hdl_counter2_count_reg[3]_0\,
      \Delay_out1_reg[0]\(1) => u_LimitPulseWidth_n_48,
      \Delay_out1_reg[0]\(0) => u_LimitPulseWidth_n_49,
      \Delay_out1_reg[12]\(0) => Relational_Operator_relop1_0,
      \Delay_out1_reg[13]\(0) => u_LimitPulseWidth_n_47,
      HDL_Counter2_count_reg(11 downto 1) => HDL_Counter2_count_reg(18 downto 8),
      HDL_Counter2_count_reg(0) => HDL_Counter2_count_reg(1),
      \HDL_Counter2_count_reg[11]_0\ => u_LimitPulseWidth_n_51,
      \HDL_Counter2_count_reg[16]\ => u_LimitPulseWidth_n_52,
      HDL_Counter2_count_reg_11_sp_1 => u_LimitPulseWidth_n_50,
      HDL_Counter2_count_reg_1_sp_1 => u_LimitPulseWidth_n_53,
      IPCORE_CLK(1) => u_LimitPulseWidth_n_54,
      IPCORE_CLK(0) => u_LimitPulseWidth_n_55,
      Logical_Operator_out10_carry_0(5) => u_Counter_Ctrl_n_123,
      Logical_Operator_out10_carry_0(4) => u_Counter_Ctrl_n_125,
      Logical_Operator_out10_carry_0(3) => u_Counter_Ctrl_n_127,
      Logical_Operator_out10_carry_0(2) => u_Counter_Ctrl_n_129,
      Logical_Operator_out10_carry_0(1) => u_Counter_Ctrl_n_131,
      Logical_Operator_out10_carry_0(0) => u_Counter_Ctrl_n_133,
      Logical_Operator_out10_carry_1(5) => Relational_Operator_1_cast(15),
      Logical_Operator_out10_carry_1(4) => Relational_Operator_1_cast(13),
      Logical_Operator_out10_carry_1(3) => Relational_Operator_1_cast(11),
      Logical_Operator_out10_carry_1(2) => Relational_Operator_1_cast(9),
      Logical_Operator_out10_carry_1(1) => Relational_Operator_1_cast(7),
      Logical_Operator_out10_carry_1(0) => Relational_Operator_1_cast(5),
      P(5) => u_Counter_Ctrl_n_0,
      P(4) => u_Counter_Ctrl_n_1,
      P(3) => u_Counter_Ctrl_n_2,
      P(2) => u_Counter_Ctrl_n_3,
      P(1) => u_Counter_Ctrl_n_4,
      P(0) => u_Counter_Ctrl_n_5,
      Q(17 downto 0) => min_pulse_width(17 downto 0),
      S(0) => \i__carry__0_i_1_n_0\,
      Saturation_out1(12 downto 0) => Saturation_out1(16 downto 4),
      \Switch7_out12_carry__0\(6) => U1_norm_1(13),
      \Switch7_out12_carry__0\(5) => U1_norm_1(10),
      \Switch7_out12_carry__0\(4) => U1_norm_1(8),
      \Switch7_out12_carry__0\(3) => U1_norm_1(6),
      \Switch7_out12_carry__0\(2) => U1_norm_1(4),
      \Switch7_out12_carry__0\(1) => U1_norm_1(2),
      \Switch7_out12_carry__0\(0) => U1_norm_1(0),
      \Switch7_out12_carry__0_0\(6) => Delay_out1(13),
      \Switch7_out12_carry__0_0\(5) => Delay_out1(10),
      \Switch7_out12_carry__0_0\(4) => Delay_out1(8),
      \Switch7_out12_carry__0_0\(3) => Delay_out1(6),
      \Switch7_out12_carry__0_0\(2) => Delay_out1(4),
      \Switch7_out12_carry__0_0\(1) => Delay_out1(2),
      \Switch7_out12_carry__0_0\(0) => Delay_out1(0),
      Switch7_out12_carry_i_7(0) => u_Counter_Ctrl_n_203,
      Switch7_out12_carry_i_7_0(0) => u_Counter_Ctrl_n_204,
      Switch7_out12_carry_i_7_1(6) => u_Counter_Ctrl_n_158,
      Switch7_out12_carry_i_7_1(5) => u_Counter_Ctrl_n_159,
      Switch7_out12_carry_i_7_1(4) => u_Counter_Ctrl_n_160,
      Switch7_out12_carry_i_7_1(3) => u_Counter_Ctrl_n_161,
      Switch7_out12_carry_i_7_1(2) => u_Counter_Ctrl_n_162,
      Switch7_out12_carry_i_7_1(1) => u_Counter_Ctrl_n_163,
      Switch7_out12_carry_i_7_1(0) => u_Counter_Ctrl_n_164,
      Switch7_out12_carry_i_7_2(6) => u_Counter_Ctrl_n_179,
      Switch7_out12_carry_i_7_2(5) => u_Counter_Ctrl_n_180,
      Switch7_out12_carry_i_7_2(4) => u_Counter_Ctrl_n_181,
      Switch7_out12_carry_i_7_2(3) => u_Counter_Ctrl_n_182,
      Switch7_out12_carry_i_7_2(2) => u_Counter_Ctrl_n_183,
      Switch7_out12_carry_i_7_2(1) => u_Counter_Ctrl_n_184,
      Switch7_out12_carry_i_7_2(0) => u_Counter_Ctrl_n_185,
      \Switch8_out12_carry__0\(0) => Relational_Operator1_relop1_3,
      \Switch8_out12_carry__0_0\(0) => Relational_Operator_relop1_2,
      \Switch8_out12_carry__0_1\(6) => Delay1_out1(13),
      \Switch8_out12_carry__0_1\(5) => Delay1_out1(10),
      \Switch8_out12_carry__0_1\(4) => Delay1_out1(8),
      \Switch8_out12_carry__0_1\(3) => Delay1_out1(6),
      \Switch8_out12_carry__0_1\(2) => Delay1_out1(4),
      \Switch8_out12_carry__0_1\(1) => Delay1_out1(2),
      \Switch8_out12_carry__0_1\(0) => Delay1_out1(0),
      \Switch8_out12_carry__0_2\(6) => U2_norm_1(13),
      \Switch8_out12_carry__0_2\(5) => U2_norm_1(10),
      \Switch8_out12_carry__0_2\(4) => U2_norm_1(8),
      \Switch8_out12_carry__0_2\(3) => U2_norm_1(6),
      \Switch8_out12_carry__0_2\(2) => U2_norm_1(4),
      \Switch8_out12_carry__0_2\(1) => U2_norm_1(2),
      \Switch8_out12_carry__0_2\(0) => U2_norm_1(0),
      \Switch9_out12_carry__0\(0) => Relational_Operator1_relop1_5,
      \Switch9_out12_carry__0_0\(0) => Relational_Operator_relop1_4,
      \Switch9_out12_carry__0_1\(6) => Delay2_out1(13),
      \Switch9_out12_carry__0_1\(5) => Delay2_out1(10),
      \Switch9_out12_carry__0_1\(4) => Delay2_out1(8),
      \Switch9_out12_carry__0_1\(3) => Delay2_out1(6),
      \Switch9_out12_carry__0_1\(2) => Delay2_out1(4),
      \Switch9_out12_carry__0_1\(1) => Delay2_out1(2),
      \Switch9_out12_carry__0_1\(0) => Delay2_out1(0),
      \Switch9_out12_carry__0_2\(6) => U3_norm_1(13),
      \Switch9_out12_carry__0_2\(5) => U3_norm_1(10),
      \Switch9_out12_carry__0_2\(4) => U3_norm_1(8),
      \Switch9_out12_carry__0_2\(3) => U3_norm_1(6),
      \Switch9_out12_carry__0_2\(2) => U3_norm_1(4),
      \Switch9_out12_carry__0_2\(1) => U3_norm_1(2),
      \Switch9_out12_carry__0_2\(0) => U3_norm_1(0),
      \T_carrier_us_AXI_1_reg[24]\(0) => u_LimitPulseWidth_n_56,
      \U1_norm_1_reg[13]\(0) => u_LimitPulseWidth_n_46,
      \min_pulse_width_AXI_1_reg[17]\(0) => u_LimitPulseWidth_n_57,
      \min_pulse_width_AXI_1_reg[17]_0\(0) => u_LimitPulseWidth_n_58,
      \min_pulse_width_AXI_1_reg[1]\(0) => Relational_Operator1_relop1_1,
      \min_pulse_width_AXI_1_reg[1]_0\ => u_LimitPulseWidth_n_1
    );
u_LimitPulseWidth1: entity work.zusys_PWM_and_SS_control_V_0_2_PWM_and_SS_control_V3_ip_src_LimitPulseWidth1
     port map (
      DI(7) => u_Counter_Ctrl_n_202,
      DI(6) => u_LimitPulseWidth_n_39,
      DI(5) => u_LimitPulseWidth_n_40,
      DI(4) => u_LimitPulseWidth_n_41,
      DI(3) => u_LimitPulseWidth_n_42,
      DI(2) => u_LimitPulseWidth_n_43,
      DI(1) => u_LimitPulseWidth_n_44,
      DI(0) => u_LimitPulseWidth_n_45,
      \Delay1_out1_reg[12]\(0) => Relational_Operator_relop1_2,
      S(7) => u_Counter_Ctrl_n_135,
      S(6) => u_Counter_Ctrl_n_136,
      S(5) => u_Counter_Ctrl_n_137,
      S(4) => u_Counter_Ctrl_n_138,
      S(3) => u_Counter_Ctrl_n_139,
      S(2) => u_Counter_Ctrl_n_140,
      S(1) => u_Counter_Ctrl_n_141,
      S(0) => u_LimitPulseWidth_n_58,
      Switch8_out12_carry_i_7 => u_LimitPulseWidth_n_1,
      Switch8_out12_carry_i_7_0(6) => u_Counter_Ctrl_n_104,
      Switch8_out12_carry_i_7_0(5) => u_Counter_Ctrl_n_105,
      Switch8_out12_carry_i_7_0(4) => u_Counter_Ctrl_n_106,
      Switch8_out12_carry_i_7_0(3) => u_Counter_Ctrl_n_107,
      Switch8_out12_carry_i_7_0(2) => u_Counter_Ctrl_n_108,
      Switch8_out12_carry_i_7_0(1) => u_Counter_Ctrl_n_109,
      Switch8_out12_carry_i_7_0(0) => u_Counter_Ctrl_n_110,
      Switch8_out12_carry_i_7_1(6) => u_Counter_Ctrl_n_112,
      Switch8_out12_carry_i_7_1(5) => u_Counter_Ctrl_n_113,
      Switch8_out12_carry_i_7_1(4) => u_Counter_Ctrl_n_114,
      Switch8_out12_carry_i_7_1(3) => u_Counter_Ctrl_n_115,
      Switch8_out12_carry_i_7_1(2) => u_Counter_Ctrl_n_116,
      Switch8_out12_carry_i_7_1(1) => u_Counter_Ctrl_n_117,
      Switch8_out12_carry_i_7_1(0) => u_Counter_Ctrl_n_118,
      \min_pulse_width_AXI_1_reg[1]\(0) => Relational_Operator1_relop1_3
    );
u_LimitPulseWidth2: entity work.zusys_PWM_and_SS_control_V_0_2_PWM_and_SS_control_V3_ip_src_LimitPulseWidth2
     port map (
      DI(7) => u_Counter_Ctrl_n_201,
      DI(6) => u_LimitPulseWidth_n_18,
      DI(5) => u_LimitPulseWidth_n_19,
      DI(4) => u_LimitPulseWidth_n_20,
      DI(3) => u_LimitPulseWidth_n_21,
      DI(2) => u_LimitPulseWidth_n_22,
      DI(1) => u_LimitPulseWidth_n_23,
      DI(0) => u_LimitPulseWidth_n_24,
      \Delay2_out1_reg[12]\(0) => Relational_Operator_relop1_4,
      S(7) => u_Counter_Ctrl_n_81,
      S(6) => u_Counter_Ctrl_n_82,
      S(5) => u_Counter_Ctrl_n_83,
      S(4) => u_Counter_Ctrl_n_84,
      S(3) => u_Counter_Ctrl_n_85,
      S(2) => u_Counter_Ctrl_n_86,
      S(1) => u_Counter_Ctrl_n_87,
      S(0) => u_LimitPulseWidth_n_57,
      Switch9_out12_carry_i_7 => u_LimitPulseWidth_n_1,
      Switch9_out12_carry_i_7_0(6) => u_Counter_Ctrl_n_49,
      Switch9_out12_carry_i_7_0(5) => u_Counter_Ctrl_n_50,
      Switch9_out12_carry_i_7_0(4) => u_Counter_Ctrl_n_51,
      Switch9_out12_carry_i_7_0(3) => u_Counter_Ctrl_n_52,
      Switch9_out12_carry_i_7_0(2) => u_Counter_Ctrl_n_53,
      Switch9_out12_carry_i_7_0(1) => u_Counter_Ctrl_n_54,
      Switch9_out12_carry_i_7_0(0) => u_Counter_Ctrl_n_55,
      Switch9_out12_carry_i_7_1(6) => u_Counter_Ctrl_n_58,
      Switch9_out12_carry_i_7_1(5) => u_Counter_Ctrl_n_59,
      Switch9_out12_carry_i_7_1(4) => u_Counter_Ctrl_n_60,
      Switch9_out12_carry_i_7_1(3) => u_Counter_Ctrl_n_61,
      Switch9_out12_carry_i_7_1(2) => u_Counter_Ctrl_n_62,
      Switch9_out12_carry_i_7_1(1) => u_Counter_Ctrl_n_63,
      Switch9_out12_carry_i_7_1(0) => u_Counter_Ctrl_n_64,
      \min_pulse_width_AXI_1_reg[1]\(0) => Relational_Operator1_relop1_5
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity zusys_PWM_and_SS_control_V_0_2_PWM_and_SS_control_V3_ip_src_PWM_and_Switching_Signal_Control is
  port (
    PWM_en_AXI_1_reg : out STD_LOGIC;
    PWM_en_rd_AXI_sig : out STD_LOGIC;
    PWM_enb_out : out STD_LOGIC;
    Triangular_Max : out STD_LOGIC;
    Triangular_Min : out STD_LOGIC;
    \Product_mul_temp[-1111111111]\ : out STD_LOGIC;
    \Product_mul_temp[-1111111110]\ : out STD_LOGIC;
    \Product_mul_temp[-1111111109]\ : out STD_LOGIC;
    \Product_mul_temp[-1111111108]\ : out STD_LOGIC;
    \Product_mul_temp[-1111111107]\ : out STD_LOGIC;
    \Product_mul_temp[-1111111106]\ : out STD_LOGIC;
    \Product_mul_temp[-1111111105]\ : out STD_LOGIC;
    \Product_mul_temp[-1111111104]\ : out STD_LOGIC;
    \Product_mul_temp[-1111111103]\ : out STD_LOGIC;
    \f_carrier_kHz_AXI_2_reg[24]\ : out STD_LOGIC_VECTOR ( 15 downto 0 );
    \HDL_Counter2_count_reg[0]\ : out STD_LOGIC;
    \HDL_Counter2_count_reg[2]\ : out STD_LOGIC;
    \HDL_Counter2_count_reg[3]\ : out STD_LOGIC;
    \HDL_Counter2_count_reg[4]\ : out STD_LOGIC;
    \HDL_Counter2_count_reg[5]\ : out STD_LOGIC;
    \HDL_Counter2_count_reg[6]\ : out STD_LOGIC;
    \HDL_Counter2_count_reg[7]\ : out STD_LOGIC;
    DI : out STD_LOGIC_VECTOR ( 0 to 0 );
    S : out STD_LOGIC_VECTOR ( 7 downto 0 );
    \HDL_Counter2_count_reg[0]_0\ : out STD_LOGIC_VECTOR ( 0 to 0 );
    Q : out STD_LOGIC_VECTOR ( 24 downto 0 );
    \min_pulse_width_AXI_2_reg[17]\ : out STD_LOGIC_VECTOR ( 17 downto 0 );
    \reduced_reg_1_reg[1][1]\ : out STD_LOGIC_VECTOR ( 1 downto 0 );
    SS0_OUT : out STD_LOGIC;
    SS1_OUT : out STD_LOGIC;
    SS2_OUT : out STD_LOGIC;
    SS3_OUT : out STD_LOGIC;
    SS4_OUT : out STD_LOGIC;
    SS5_OUT : out STD_LOGIC;
    reset : in STD_LOGIC;
    E : in STD_LOGIC_VECTOR ( 0 to 0 );
    IPCORE_CLK : in STD_LOGIC;
    CEB2 : in STD_LOGIC;
    B : in STD_LOGIC_VECTOR ( 7 downto 0 );
    D : in STD_LOGIC_VECTOR ( 24 downto 0 );
    write_PWM_en_AXI : in STD_LOGIC;
    CO : in STD_LOGIC_VECTOR ( 0 to 0 );
    \T_carrier_us_AXI_1_reg[24]\ : in STD_LOGIC_VECTOR ( 24 downto 0 );
    \min_pulse_width_AXI_1_reg[17]\ : in STD_LOGIC_VECTOR ( 17 downto 0 );
    \reduced_reg_1_reg[0][1]\ : in STD_LOGIC_VECTOR ( 1 downto 0 );
    SS0_IN_External : in STD_LOGIC;
    \reduced_reg_reg[0][1]\ : in STD_LOGIC_VECTOR ( 1 downto 0 );
    SS1_IN_External : in STD_LOGIC;
    SS2_IN_External : in STD_LOGIC;
    \reduced_reg_2_reg[0][1]\ : in STD_LOGIC_VECTOR ( 1 downto 0 );
    SS3_IN_External : in STD_LOGIC;
    SS4_IN_External : in STD_LOGIC;
    \reduced_reg_3_reg[0][1]\ : in STD_LOGIC_VECTOR ( 1 downto 0 );
    SS5_IN_External : in STD_LOGIC;
    \U1_norm_1_reg[13]\ : in STD_LOGIC_VECTOR ( 13 downto 0 );
    m_u1_norm : in STD_LOGIC_VECTOR ( 13 downto 0 );
    \U2_norm_1_reg[13]\ : in STD_LOGIC_VECTOR ( 13 downto 0 );
    m_u2_norm : in STD_LOGIC_VECTOR ( 13 downto 0 );
    \U3_norm_1_reg[13]\ : in STD_LOGIC_VECTOR ( 13 downto 0 );
    m_u3_norm : in STD_LOGIC_VECTOR ( 13 downto 0 )
  );
end zusys_PWM_and_SS_control_V_0_2_PWM_and_SS_control_V3_ip_src_PWM_and_Switching_Signal_Control;

architecture STRUCTURE of zusys_PWM_and_SS_control_V_0_2_PWM_and_SS_control_V3_ip_src_PWM_and_Switching_Signal_Control is
  signal GenPWM_out1 : STD_LOGIC;
  signal GenPWM_out2 : STD_LOGIC;
  signal GenPWM_out3 : STD_LOGIC;
  signal GenPWM_out4 : STD_LOGIC;
  signal GenPWM_out5 : STD_LOGIC;
  signal GenPWM_out6 : STD_LOGIC;
  signal U1_norm : STD_LOGIC_VECTOR ( 13 downto 0 );
  signal U2_norm : STD_LOGIC_VECTOR ( 13 downto 0 );
  signal U3_norm : STD_LOGIC_VECTOR ( 13 downto 0 );
begin
\U1_norm_1[0]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FE02"
    )
        port map (
      I0 => \U1_norm_1_reg[13]\(0),
      I1 => \reduced_reg_1_reg[0][1]\(0),
      I2 => \reduced_reg_1_reg[0][1]\(1),
      I3 => m_u1_norm(0),
      O => U1_norm(0)
    );
\U1_norm_1[10]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FE02"
    )
        port map (
      I0 => \U1_norm_1_reg[13]\(10),
      I1 => \reduced_reg_1_reg[0][1]\(0),
      I2 => \reduced_reg_1_reg[0][1]\(1),
      I3 => m_u1_norm(10),
      O => U1_norm(10)
    );
\U1_norm_1[11]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FE02"
    )
        port map (
      I0 => \U1_norm_1_reg[13]\(11),
      I1 => \reduced_reg_1_reg[0][1]\(0),
      I2 => \reduced_reg_1_reg[0][1]\(1),
      I3 => m_u1_norm(11),
      O => U1_norm(11)
    );
\U1_norm_1[12]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FE02"
    )
        port map (
      I0 => \U1_norm_1_reg[13]\(12),
      I1 => \reduced_reg_1_reg[0][1]\(0),
      I2 => \reduced_reg_1_reg[0][1]\(1),
      I3 => m_u1_norm(12),
      O => U1_norm(12)
    );
\U1_norm_1[13]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FE02"
    )
        port map (
      I0 => \U1_norm_1_reg[13]\(13),
      I1 => \reduced_reg_1_reg[0][1]\(0),
      I2 => \reduced_reg_1_reg[0][1]\(1),
      I3 => m_u1_norm(13),
      O => U1_norm(13)
    );
\U1_norm_1[1]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FE02"
    )
        port map (
      I0 => \U1_norm_1_reg[13]\(1),
      I1 => \reduced_reg_1_reg[0][1]\(0),
      I2 => \reduced_reg_1_reg[0][1]\(1),
      I3 => m_u1_norm(1),
      O => U1_norm(1)
    );
\U1_norm_1[2]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FE02"
    )
        port map (
      I0 => \U1_norm_1_reg[13]\(2),
      I1 => \reduced_reg_1_reg[0][1]\(0),
      I2 => \reduced_reg_1_reg[0][1]\(1),
      I3 => m_u1_norm(2),
      O => U1_norm(2)
    );
\U1_norm_1[3]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FE02"
    )
        port map (
      I0 => \U1_norm_1_reg[13]\(3),
      I1 => \reduced_reg_1_reg[0][1]\(0),
      I2 => \reduced_reg_1_reg[0][1]\(1),
      I3 => m_u1_norm(3),
      O => U1_norm(3)
    );
\U1_norm_1[4]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FE02"
    )
        port map (
      I0 => \U1_norm_1_reg[13]\(4),
      I1 => \reduced_reg_1_reg[0][1]\(0),
      I2 => \reduced_reg_1_reg[0][1]\(1),
      I3 => m_u1_norm(4),
      O => U1_norm(4)
    );
\U1_norm_1[5]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FE02"
    )
        port map (
      I0 => \U1_norm_1_reg[13]\(5),
      I1 => \reduced_reg_1_reg[0][1]\(0),
      I2 => \reduced_reg_1_reg[0][1]\(1),
      I3 => m_u1_norm(5),
      O => U1_norm(5)
    );
\U1_norm_1[6]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FE02"
    )
        port map (
      I0 => \U1_norm_1_reg[13]\(6),
      I1 => \reduced_reg_1_reg[0][1]\(0),
      I2 => \reduced_reg_1_reg[0][1]\(1),
      I3 => m_u1_norm(6),
      O => U1_norm(6)
    );
\U1_norm_1[7]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FE02"
    )
        port map (
      I0 => \U1_norm_1_reg[13]\(7),
      I1 => \reduced_reg_1_reg[0][1]\(0),
      I2 => \reduced_reg_1_reg[0][1]\(1),
      I3 => m_u1_norm(7),
      O => U1_norm(7)
    );
\U1_norm_1[8]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FE02"
    )
        port map (
      I0 => \U1_norm_1_reg[13]\(8),
      I1 => \reduced_reg_1_reg[0][1]\(0),
      I2 => \reduced_reg_1_reg[0][1]\(1),
      I3 => m_u1_norm(8),
      O => U1_norm(8)
    );
\U1_norm_1[9]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FE02"
    )
        port map (
      I0 => \U1_norm_1_reg[13]\(9),
      I1 => \reduced_reg_1_reg[0][1]\(0),
      I2 => \reduced_reg_1_reg[0][1]\(1),
      I3 => m_u1_norm(9),
      O => U1_norm(9)
    );
\U2_norm_1[0]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FE02"
    )
        port map (
      I0 => \U2_norm_1_reg[13]\(0),
      I1 => \reduced_reg_1_reg[0][1]\(0),
      I2 => \reduced_reg_1_reg[0][1]\(1),
      I3 => m_u2_norm(0),
      O => U2_norm(0)
    );
\U2_norm_1[10]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FE02"
    )
        port map (
      I0 => \U2_norm_1_reg[13]\(10),
      I1 => \reduced_reg_1_reg[0][1]\(0),
      I2 => \reduced_reg_1_reg[0][1]\(1),
      I3 => m_u2_norm(10),
      O => U2_norm(10)
    );
\U2_norm_1[11]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FE02"
    )
        port map (
      I0 => \U2_norm_1_reg[13]\(11),
      I1 => \reduced_reg_1_reg[0][1]\(0),
      I2 => \reduced_reg_1_reg[0][1]\(1),
      I3 => m_u2_norm(11),
      O => U2_norm(11)
    );
\U2_norm_1[12]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FE02"
    )
        port map (
      I0 => \U2_norm_1_reg[13]\(12),
      I1 => \reduced_reg_1_reg[0][1]\(0),
      I2 => \reduced_reg_1_reg[0][1]\(1),
      I3 => m_u2_norm(12),
      O => U2_norm(12)
    );
\U2_norm_1[13]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FE02"
    )
        port map (
      I0 => \U2_norm_1_reg[13]\(13),
      I1 => \reduced_reg_1_reg[0][1]\(0),
      I2 => \reduced_reg_1_reg[0][1]\(1),
      I3 => m_u2_norm(13),
      O => U2_norm(13)
    );
\U2_norm_1[1]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FE02"
    )
        port map (
      I0 => \U2_norm_1_reg[13]\(1),
      I1 => \reduced_reg_1_reg[0][1]\(0),
      I2 => \reduced_reg_1_reg[0][1]\(1),
      I3 => m_u2_norm(1),
      O => U2_norm(1)
    );
\U2_norm_1[2]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FE02"
    )
        port map (
      I0 => \U2_norm_1_reg[13]\(2),
      I1 => \reduced_reg_1_reg[0][1]\(0),
      I2 => \reduced_reg_1_reg[0][1]\(1),
      I3 => m_u2_norm(2),
      O => U2_norm(2)
    );
\U2_norm_1[3]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FE02"
    )
        port map (
      I0 => \U2_norm_1_reg[13]\(3),
      I1 => \reduced_reg_1_reg[0][1]\(0),
      I2 => \reduced_reg_1_reg[0][1]\(1),
      I3 => m_u2_norm(3),
      O => U2_norm(3)
    );
\U2_norm_1[4]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FE02"
    )
        port map (
      I0 => \U2_norm_1_reg[13]\(4),
      I1 => \reduced_reg_1_reg[0][1]\(0),
      I2 => \reduced_reg_1_reg[0][1]\(1),
      I3 => m_u2_norm(4),
      O => U2_norm(4)
    );
\U2_norm_1[5]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FE02"
    )
        port map (
      I0 => \U2_norm_1_reg[13]\(5),
      I1 => \reduced_reg_1_reg[0][1]\(0),
      I2 => \reduced_reg_1_reg[0][1]\(1),
      I3 => m_u2_norm(5),
      O => U2_norm(5)
    );
\U2_norm_1[6]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FE02"
    )
        port map (
      I0 => \U2_norm_1_reg[13]\(6),
      I1 => \reduced_reg_1_reg[0][1]\(0),
      I2 => \reduced_reg_1_reg[0][1]\(1),
      I3 => m_u2_norm(6),
      O => U2_norm(6)
    );
\U2_norm_1[7]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FE02"
    )
        port map (
      I0 => \U2_norm_1_reg[13]\(7),
      I1 => \reduced_reg_1_reg[0][1]\(0),
      I2 => \reduced_reg_1_reg[0][1]\(1),
      I3 => m_u2_norm(7),
      O => U2_norm(7)
    );
\U2_norm_1[8]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FE02"
    )
        port map (
      I0 => \U2_norm_1_reg[13]\(8),
      I1 => \reduced_reg_1_reg[0][1]\(0),
      I2 => \reduced_reg_1_reg[0][1]\(1),
      I3 => m_u2_norm(8),
      O => U2_norm(8)
    );
\U2_norm_1[9]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FE02"
    )
        port map (
      I0 => \U2_norm_1_reg[13]\(9),
      I1 => \reduced_reg_1_reg[0][1]\(0),
      I2 => \reduced_reg_1_reg[0][1]\(1),
      I3 => m_u2_norm(9),
      O => U2_norm(9)
    );
\U3_norm_1[0]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FE02"
    )
        port map (
      I0 => \U3_norm_1_reg[13]\(0),
      I1 => \reduced_reg_1_reg[0][1]\(0),
      I2 => \reduced_reg_1_reg[0][1]\(1),
      I3 => m_u3_norm(0),
      O => U3_norm(0)
    );
\U3_norm_1[10]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FE02"
    )
        port map (
      I0 => \U3_norm_1_reg[13]\(10),
      I1 => \reduced_reg_1_reg[0][1]\(0),
      I2 => \reduced_reg_1_reg[0][1]\(1),
      I3 => m_u3_norm(10),
      O => U3_norm(10)
    );
\U3_norm_1[11]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FE02"
    )
        port map (
      I0 => \U3_norm_1_reg[13]\(11),
      I1 => \reduced_reg_1_reg[0][1]\(0),
      I2 => \reduced_reg_1_reg[0][1]\(1),
      I3 => m_u3_norm(11),
      O => U3_norm(11)
    );
\U3_norm_1[12]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FE02"
    )
        port map (
      I0 => \U3_norm_1_reg[13]\(12),
      I1 => \reduced_reg_1_reg[0][1]\(0),
      I2 => \reduced_reg_1_reg[0][1]\(1),
      I3 => m_u3_norm(12),
      O => U3_norm(12)
    );
\U3_norm_1[13]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FE02"
    )
        port map (
      I0 => \U3_norm_1_reg[13]\(13),
      I1 => \reduced_reg_1_reg[0][1]\(0),
      I2 => \reduced_reg_1_reg[0][1]\(1),
      I3 => m_u3_norm(13),
      O => U3_norm(13)
    );
\U3_norm_1[1]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FE02"
    )
        port map (
      I0 => \U3_norm_1_reg[13]\(1),
      I1 => \reduced_reg_1_reg[0][1]\(0),
      I2 => \reduced_reg_1_reg[0][1]\(1),
      I3 => m_u3_norm(1),
      O => U3_norm(1)
    );
\U3_norm_1[2]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FE02"
    )
        port map (
      I0 => \U3_norm_1_reg[13]\(2),
      I1 => \reduced_reg_1_reg[0][1]\(0),
      I2 => \reduced_reg_1_reg[0][1]\(1),
      I3 => m_u3_norm(2),
      O => U3_norm(2)
    );
\U3_norm_1[3]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FE02"
    )
        port map (
      I0 => \U3_norm_1_reg[13]\(3),
      I1 => \reduced_reg_1_reg[0][1]\(0),
      I2 => \reduced_reg_1_reg[0][1]\(1),
      I3 => m_u3_norm(3),
      O => U3_norm(3)
    );
\U3_norm_1[4]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FE02"
    )
        port map (
      I0 => \U3_norm_1_reg[13]\(4),
      I1 => \reduced_reg_1_reg[0][1]\(0),
      I2 => \reduced_reg_1_reg[0][1]\(1),
      I3 => m_u3_norm(4),
      O => U3_norm(4)
    );
\U3_norm_1[5]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FE02"
    )
        port map (
      I0 => \U3_norm_1_reg[13]\(5),
      I1 => \reduced_reg_1_reg[0][1]\(0),
      I2 => \reduced_reg_1_reg[0][1]\(1),
      I3 => m_u3_norm(5),
      O => U3_norm(5)
    );
\U3_norm_1[6]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FE02"
    )
        port map (
      I0 => \U3_norm_1_reg[13]\(6),
      I1 => \reduced_reg_1_reg[0][1]\(0),
      I2 => \reduced_reg_1_reg[0][1]\(1),
      I3 => m_u3_norm(6),
      O => U3_norm(6)
    );
\U3_norm_1[7]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FE02"
    )
        port map (
      I0 => \U3_norm_1_reg[13]\(7),
      I1 => \reduced_reg_1_reg[0][1]\(0),
      I2 => \reduced_reg_1_reg[0][1]\(1),
      I3 => m_u3_norm(7),
      O => U3_norm(7)
    );
\U3_norm_1[8]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FE02"
    )
        port map (
      I0 => \U3_norm_1_reg[13]\(8),
      I1 => \reduced_reg_1_reg[0][1]\(0),
      I2 => \reduced_reg_1_reg[0][1]\(1),
      I3 => m_u3_norm(8),
      O => U3_norm(8)
    );
\U3_norm_1[9]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FE02"
    )
        port map (
      I0 => \U3_norm_1_reg[13]\(9),
      I1 => \reduced_reg_1_reg[0][1]\(0),
      I2 => \reduced_reg_1_reg[0][1]\(1),
      I3 => m_u3_norm(9),
      O => U3_norm(9)
    );
u_GenPWM: entity work.zusys_PWM_and_SS_control_V_0_2_PWM_and_SS_control_V3_ip_src_GenPWM
     port map (
      B(7 downto 0) => B(7 downto 0),
      CEB2 => CEB2,
      CO(0) => CO(0),
      D(24 downto 0) => D(24 downto 0),
      DI(1) => DI(0),
      DI(0) => \HDL_Counter2_count_reg[0]\,
      E(0) => E(0),
      GenPWM_out1 => GenPWM_out1,
      GenPWM_out2 => GenPWM_out2,
      GenPWM_out3 => GenPWM_out3,
      GenPWM_out4 => GenPWM_out4,
      GenPWM_out5 => GenPWM_out5,
      GenPWM_out6 => GenPWM_out6,
      \HDL_Counter2_count_reg[0]_0\(0) => \HDL_Counter2_count_reg[0]_0\(0),
      \HDL_Counter2_count_reg[2]_0\ => \HDL_Counter2_count_reg[2]\,
      \HDL_Counter2_count_reg[3]_0\ => \HDL_Counter2_count_reg[3]\,
      \HDL_Counter2_count_reg[4]_0\ => \HDL_Counter2_count_reg[4]\,
      \HDL_Counter2_count_reg[5]_0\ => \HDL_Counter2_count_reg[5]\,
      \HDL_Counter2_count_reg[6]_0\ => \HDL_Counter2_count_reg[6]\,
      \HDL_Counter2_count_reg[7]_0\ => \HDL_Counter2_count_reg[7]\,
      IPCORE_CLK => IPCORE_CLK,
      PWM_en_AXI_1_reg_0 => PWM_en_AXI_1_reg,
      PWM_en_rd_AXI_sig => PWM_en_rd_AXI_sig,
      PWM_enb_out => PWM_enb_out,
      \Product_mul_temp[-1111111103]\ => \Product_mul_temp[-1111111103]\,
      \Product_mul_temp[-1111111104]\ => \Product_mul_temp[-1111111104]\,
      \Product_mul_temp[-1111111105]\ => \Product_mul_temp[-1111111105]\,
      \Product_mul_temp[-1111111106]\ => \Product_mul_temp[-1111111106]\,
      \Product_mul_temp[-1111111107]\ => \Product_mul_temp[-1111111107]\,
      \Product_mul_temp[-1111111108]\ => \Product_mul_temp[-1111111108]\,
      \Product_mul_temp[-1111111109]\ => \Product_mul_temp[-1111111109]\,
      \Product_mul_temp[-1111111110]\ => \Product_mul_temp[-1111111110]\,
      \Product_mul_temp[-1111111111]\ => \Product_mul_temp[-1111111111]\,
      Q(24 downto 0) => Q(24 downto 0),
      S(7 downto 0) => S(7 downto 0),
      \T_carrier_us_AXI_1_reg[24]_0\(24 downto 0) => \T_carrier_us_AXI_1_reg[24]\(24 downto 0),
      Triangular_Max => Triangular_Max,
      Triangular_Min => Triangular_Min,
      \U1_norm_1_reg[13]_0\(13 downto 0) => U1_norm(13 downto 0),
      \U2_norm_1_reg[13]_0\(13 downto 0) => U2_norm(13 downto 0),
      \U3_norm_1_reg[13]_0\(13 downto 0) => U3_norm(13 downto 0),
      \f_carrier_kHz_AXI_2_reg[24]_0\(15 downto 0) => \f_carrier_kHz_AXI_2_reg[24]\(15 downto 0),
      \min_pulse_width_AXI_1_reg[17]_0\(17 downto 0) => \min_pulse_width_AXI_1_reg[17]\(17 downto 0),
      \min_pulse_width_AXI_2_reg[17]_0\(17 downto 0) => \min_pulse_width_AXI_2_reg[17]\(17 downto 0),
      reset => reset,
      write_PWM_en_AXI => write_PWM_en_AXI
    );
u_VSI_Control_Signal_Switch: entity work.zusys_PWM_and_SS_control_V_0_2_PWM_and_SS_control_V3_ip_src_VSI_Control_Signal_Switch
     port map (
      E(0) => E(0),
      GenPWM_out1 => GenPWM_out1,
      GenPWM_out2 => GenPWM_out2,
      GenPWM_out3 => GenPWM_out3,
      GenPWM_out4 => GenPWM_out4,
      GenPWM_out5 => GenPWM_out5,
      GenPWM_out6 => GenPWM_out6,
      IPCORE_CLK => IPCORE_CLK,
      Q(1 downto 0) => \reduced_reg_1_reg[1][1]\(1 downto 0),
      SS0_IN_External => SS0_IN_External,
      SS0_OUT => SS0_OUT,
      SS1_IN_External => SS1_IN_External,
      SS1_OUT => SS1_OUT,
      SS2_IN_External => SS2_IN_External,
      SS2_OUT => SS2_OUT,
      SS3_IN_External => SS3_IN_External,
      SS3_OUT => SS3_OUT,
      SS4_IN_External => SS4_IN_External,
      SS4_OUT => SS4_OUT,
      SS5_IN_External => SS5_IN_External,
      SS5_OUT => SS5_OUT,
      \reduced_reg_1_reg[0][1]_0\(1 downto 0) => \reduced_reg_1_reg[0][1]\(1 downto 0),
      \reduced_reg_2_reg[0][1]_0\(1 downto 0) => \reduced_reg_2_reg[0][1]\(1 downto 0),
      \reduced_reg_3_reg[0][1]_0\(1 downto 0) => \reduced_reg_3_reg[0][1]\(1 downto 0),
      \reduced_reg_reg[0][1]_0\(1 downto 0) => \reduced_reg_reg[0][1]\(1 downto 0),
      reset => reset
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity zusys_PWM_and_SS_control_V_0_2_PWM_and_SS_control_V3_ip_dut is
  port (
    PWM_en_AXI_1 : out STD_LOGIC;
    PWM_en_rd_AXI_sig : out STD_LOGIC;
    PWM_enb_out : out STD_LOGIC;
    Triangular_Max : out STD_LOGIC;
    Triangular_Min : out STD_LOGIC;
    \f_carrier_kHz_AXI_2_reg[24]\ : out STD_LOGIC_VECTOR ( 24 downto 0 );
    DI : out STD_LOGIC_VECTOR ( 1 downto 0 );
    \HDL_Counter2_count_reg[2]\ : out STD_LOGIC;
    \HDL_Counter2_count_reg[3]\ : out STD_LOGIC;
    \HDL_Counter2_count_reg[4]\ : out STD_LOGIC;
    \HDL_Counter2_count_reg[5]\ : out STD_LOGIC;
    \HDL_Counter2_count_reg[6]\ : out STD_LOGIC;
    \HDL_Counter2_count_reg[7]\ : out STD_LOGIC;
    S : out STD_LOGIC_VECTOR ( 7 downto 0 );
    \HDL_Counter2_count_reg[0]\ : out STD_LOGIC_VECTOR ( 0 to 0 );
    Q : out STD_LOGIC_VECTOR ( 24 downto 0 );
    \min_pulse_width_AXI_2_reg[17]\ : out STD_LOGIC_VECTOR ( 17 downto 0 );
    \reduced_reg_1_reg[1][1]\ : out STD_LOGIC_VECTOR ( 1 downto 0 );
    SS0_OUT : out STD_LOGIC;
    SS1_OUT : out STD_LOGIC;
    SS2_OUT : out STD_LOGIC;
    SS3_OUT : out STD_LOGIC;
    SS4_OUT : out STD_LOGIC;
    SS5_OUT : out STD_LOGIC;
    reset : in STD_LOGIC;
    E : in STD_LOGIC_VECTOR ( 0 to 0 );
    IPCORE_CLK : in STD_LOGIC;
    CEB2 : in STD_LOGIC;
    B : in STD_LOGIC_VECTOR ( 7 downto 0 );
    D : in STD_LOGIC_VECTOR ( 24 downto 0 );
    write_PWM_en_AXI : in STD_LOGIC;
    CO : in STD_LOGIC_VECTOR ( 0 to 0 );
    \T_carrier_us_AXI_1_reg[24]\ : in STD_LOGIC_VECTOR ( 24 downto 0 );
    \min_pulse_width_AXI_1_reg[17]\ : in STD_LOGIC_VECTOR ( 17 downto 0 );
    \reduced_reg_1_reg[0][1]\ : in STD_LOGIC_VECTOR ( 1 downto 0 );
    SS0_IN_External : in STD_LOGIC;
    \reduced_reg_reg[0][1]\ : in STD_LOGIC_VECTOR ( 1 downto 0 );
    SS1_IN_External : in STD_LOGIC;
    SS2_IN_External : in STD_LOGIC;
    \reduced_reg_2_reg[0][1]\ : in STD_LOGIC_VECTOR ( 1 downto 0 );
    SS3_IN_External : in STD_LOGIC;
    SS4_IN_External : in STD_LOGIC;
    \reduced_reg_3_reg[0][1]\ : in STD_LOGIC_VECTOR ( 1 downto 0 );
    SS5_IN_External : in STD_LOGIC;
    \U1_norm_1_reg[13]\ : in STD_LOGIC_VECTOR ( 13 downto 0 );
    m_u1_norm : in STD_LOGIC_VECTOR ( 13 downto 0 );
    \U2_norm_1_reg[13]\ : in STD_LOGIC_VECTOR ( 13 downto 0 );
    m_u2_norm : in STD_LOGIC_VECTOR ( 13 downto 0 );
    \U3_norm_1_reg[13]\ : in STD_LOGIC_VECTOR ( 13 downto 0 );
    m_u3_norm : in STD_LOGIC_VECTOR ( 13 downto 0 )
  );
end zusys_PWM_and_SS_control_V_0_2_PWM_and_SS_control_V3_ip_dut;

architecture STRUCTURE of zusys_PWM_and_SS_control_V_0_2_PWM_and_SS_control_V3_ip_dut is
begin
u_PWM_and_SS_control_V3_ip_src_PWM_and_Switching_Signal_Control: entity work.zusys_PWM_and_SS_control_V_0_2_PWM_and_SS_control_V3_ip_src_PWM_and_Switching_Signal_Control
     port map (
      B(7 downto 0) => B(7 downto 0),
      CEB2 => CEB2,
      CO(0) => CO(0),
      D(24 downto 0) => D(24 downto 0),
      DI(0) => DI(1),
      E(0) => E(0),
      \HDL_Counter2_count_reg[0]\ => DI(0),
      \HDL_Counter2_count_reg[0]_0\(0) => \HDL_Counter2_count_reg[0]\(0),
      \HDL_Counter2_count_reg[2]\ => \HDL_Counter2_count_reg[2]\,
      \HDL_Counter2_count_reg[3]\ => \HDL_Counter2_count_reg[3]\,
      \HDL_Counter2_count_reg[4]\ => \HDL_Counter2_count_reg[4]\,
      \HDL_Counter2_count_reg[5]\ => \HDL_Counter2_count_reg[5]\,
      \HDL_Counter2_count_reg[6]\ => \HDL_Counter2_count_reg[6]\,
      \HDL_Counter2_count_reg[7]\ => \HDL_Counter2_count_reg[7]\,
      IPCORE_CLK => IPCORE_CLK,
      PWM_en_AXI_1_reg => PWM_en_AXI_1,
      PWM_en_rd_AXI_sig => PWM_en_rd_AXI_sig,
      PWM_enb_out => PWM_enb_out,
      \Product_mul_temp[-1111111103]\ => \f_carrier_kHz_AXI_2_reg[24]\(8),
      \Product_mul_temp[-1111111104]\ => \f_carrier_kHz_AXI_2_reg[24]\(7),
      \Product_mul_temp[-1111111105]\ => \f_carrier_kHz_AXI_2_reg[24]\(6),
      \Product_mul_temp[-1111111106]\ => \f_carrier_kHz_AXI_2_reg[24]\(5),
      \Product_mul_temp[-1111111107]\ => \f_carrier_kHz_AXI_2_reg[24]\(4),
      \Product_mul_temp[-1111111108]\ => \f_carrier_kHz_AXI_2_reg[24]\(3),
      \Product_mul_temp[-1111111109]\ => \f_carrier_kHz_AXI_2_reg[24]\(2),
      \Product_mul_temp[-1111111110]\ => \f_carrier_kHz_AXI_2_reg[24]\(1),
      \Product_mul_temp[-1111111111]\ => \f_carrier_kHz_AXI_2_reg[24]\(0),
      Q(24 downto 0) => Q(24 downto 0),
      S(7 downto 0) => S(7 downto 0),
      SS0_IN_External => SS0_IN_External,
      SS0_OUT => SS0_OUT,
      SS1_IN_External => SS1_IN_External,
      SS1_OUT => SS1_OUT,
      SS2_IN_External => SS2_IN_External,
      SS2_OUT => SS2_OUT,
      SS3_IN_External => SS3_IN_External,
      SS3_OUT => SS3_OUT,
      SS4_IN_External => SS4_IN_External,
      SS4_OUT => SS4_OUT,
      SS5_IN_External => SS5_IN_External,
      SS5_OUT => SS5_OUT,
      \T_carrier_us_AXI_1_reg[24]\(24 downto 0) => \T_carrier_us_AXI_1_reg[24]\(24 downto 0),
      Triangular_Max => Triangular_Max,
      Triangular_Min => Triangular_Min,
      \U1_norm_1_reg[13]\(13 downto 0) => \U1_norm_1_reg[13]\(13 downto 0),
      \U2_norm_1_reg[13]\(13 downto 0) => \U2_norm_1_reg[13]\(13 downto 0),
      \U3_norm_1_reg[13]\(13 downto 0) => \U3_norm_1_reg[13]\(13 downto 0),
      \f_carrier_kHz_AXI_2_reg[24]\(15 downto 0) => \f_carrier_kHz_AXI_2_reg[24]\(24 downto 9),
      m_u1_norm(13 downto 0) => m_u1_norm(13 downto 0),
      m_u2_norm(13 downto 0) => m_u2_norm(13 downto 0),
      m_u3_norm(13 downto 0) => m_u3_norm(13 downto 0),
      \min_pulse_width_AXI_1_reg[17]\(17 downto 0) => \min_pulse_width_AXI_1_reg[17]\(17 downto 0),
      \min_pulse_width_AXI_2_reg[17]\(17 downto 0) => \min_pulse_width_AXI_2_reg[17]\(17 downto 0),
      \reduced_reg_1_reg[0][1]\(1 downto 0) => \reduced_reg_1_reg[0][1]\(1 downto 0),
      \reduced_reg_1_reg[1][1]\(1 downto 0) => \reduced_reg_1_reg[1][1]\(1 downto 0),
      \reduced_reg_2_reg[0][1]\(1 downto 0) => \reduced_reg_2_reg[0][1]\(1 downto 0),
      \reduced_reg_3_reg[0][1]\(1 downto 0) => \reduced_reg_3_reg[0][1]\(1 downto 0),
      \reduced_reg_reg[0][1]\(1 downto 0) => \reduced_reg_reg[0][1]\(1 downto 0),
      reset => reset,
      write_PWM_en_AXI => write_PWM_en_AXI
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity zusys_PWM_and_SS_control_V_0_2_PWM_and_SS_control_V3_ip is
  port (
    FSM_sequential_axi_lite_rstate_reg : out STD_LOGIC;
    PWM_enb_out : out STD_LOGIC;
    Triangular_Max : out STD_LOGIC;
    Triangular_Min : out STD_LOGIC;
    \HDL_Counter2_count_reg[7]\ : out STD_LOGIC_VECTOR ( 6 downto 0 );
    DI : out STD_LOGIC_VECTOR ( 1 downto 0 );
    S : out STD_LOGIC_VECTOR ( 7 downto 0 );
    Q : out STD_LOGIC_VECTOR ( 1 downto 0 );
    AXI4_Lite_RDATA : out STD_LOGIC_VECTOR ( 26 downto 0 );
    SS0_OUT : out STD_LOGIC;
    SS1_OUT : out STD_LOGIC;
    SS2_OUT : out STD_LOGIC;
    SS3_OUT : out STD_LOGIC;
    SS4_OUT : out STD_LOGIC;
    SS5_OUT : out STD_LOGIC;
    AXI4_Lite_ARREADY : out STD_LOGIC;
    AXI4_Lite_AWREADY : out STD_LOGIC;
    AXI4_Lite_ACLK : in STD_LOGIC;
    IPCORE_CLK : in STD_LOGIC;
    B : in STD_LOGIC_VECTOR ( 7 downto 0 );
    CO : in STD_LOGIC_VECTOR ( 0 to 0 );
    AXI4_Lite_AWADDR : in STD_LOGIC_VECTOR ( 13 downto 0 );
    AXI4_Lite_WDATA : in STD_LOGIC_VECTOR ( 24 downto 0 );
    SS0_IN_External : in STD_LOGIC;
    SS1_IN_External : in STD_LOGIC;
    SS2_IN_External : in STD_LOGIC;
    SS3_IN_External : in STD_LOGIC;
    SS4_IN_External : in STD_LOGIC;
    SS5_IN_External : in STD_LOGIC;
    AXI4_Lite_ARVALID : in STD_LOGIC;
    AXI4_Lite_ARADDR : in STD_LOGIC_VECTOR ( 13 downto 0 );
    AXI4_Lite_RREADY : in STD_LOGIC;
    AXI4_Lite_AWVALID : in STD_LOGIC;
    AXI4_Lite_WVALID : in STD_LOGIC;
    AXI4_Lite_ARESETN : in STD_LOGIC;
    IPCORE_RESETN : in STD_LOGIC;
    AXI4_Lite_BREADY : in STD_LOGIC;
    AXI4_Lite_WSTRB : in STD_LOGIC_VECTOR ( 3 downto 0 );
    m_u1_norm : in STD_LOGIC_VECTOR ( 13 downto 0 );
    m_u2_norm : in STD_LOGIC_VECTOR ( 13 downto 0 );
    m_u3_norm : in STD_LOGIC_VECTOR ( 13 downto 0 )
  );
end zusys_PWM_and_SS_control_V_0_2_PWM_and_SS_control_V3_ip;

architecture STRUCTURE of zusys_PWM_and_SS_control_V_0_2_PWM_and_SS_control_V3_ip is
  signal Mode_rd_AXI_sig : STD_LOGIC_VECTOR ( 1 downto 0 );
  signal PWM_T_carrier_us_rd_AXI_sig : STD_LOGIC_VECTOR ( 24 downto 0 );
  signal PWM_en_rd_AXI_sig : STD_LOGIC;
  signal PWM_f_carrier_kHz_rd_AXI_sig : STD_LOGIC_VECTOR ( 24 downto 10 );
  signal PWM_min_pulse_width_rd_AXI_sig : STD_LOGIC_VECTOR ( 17 downto 0 );
  signal reset : STD_LOGIC;
  signal u_PWM_and_SS_control_V3_ip_axi_lite_inst_n_8 : STD_LOGIC;
  signal u_PWM_and_SS_control_V3_ip_dut_inst_n_20 : STD_LOGIC;
  signal u_PWM_and_SS_control_V3_ip_dut_inst_n_21 : STD_LOGIC;
  signal u_PWM_and_SS_control_V3_ip_dut_inst_n_22 : STD_LOGIC;
  signal u_PWM_and_SS_control_V3_ip_dut_inst_n_23 : STD_LOGIC;
  signal u_PWM_and_SS_control_V3_ip_dut_inst_n_24 : STD_LOGIC;
  signal u_PWM_and_SS_control_V3_ip_dut_inst_n_25 : STD_LOGIC;
  signal u_PWM_and_SS_control_V3_ip_dut_inst_n_26 : STD_LOGIC;
  signal u_PWM_and_SS_control_V3_ip_dut_inst_n_27 : STD_LOGIC;
  signal u_PWM_and_SS_control_V3_ip_dut_inst_n_28 : STD_LOGIC;
  signal u_PWM_and_SS_control_V3_ip_dut_inst_n_29 : STD_LOGIC;
  signal \u_PWM_and_SS_control_V3_ip_src_PWM_and_Switching_Signal_Control/u_GenPWM/PWM_en_AXI_1\ : STD_LOGIC;
  signal write_Mode_AXI : STD_LOGIC_VECTOR ( 1 downto 0 );
  signal write_PWM_en_AXI : STD_LOGIC;
  signal write_PWM_min_pulse_width_AXI : STD_LOGIC_VECTOR ( 17 downto 0 );
  signal write_Scal_T_carrier_AXI : STD_LOGIC_VECTOR ( 24 downto 0 );
  signal write_Scal_f_carrier_AXI : STD_LOGIC_VECTOR ( 24 downto 0 );
  signal write_TriState_HB1_AXI : STD_LOGIC_VECTOR ( 1 downto 0 );
  signal write_TriState_HB2_AXI : STD_LOGIC_VECTOR ( 1 downto 0 );
  signal write_TriState_HB3_AXI : STD_LOGIC_VECTOR ( 1 downto 0 );
  signal write_axi_enable : STD_LOGIC;
  signal write_m_u1_norm_AXI : STD_LOGIC_VECTOR ( 13 downto 0 );
  signal write_m_u2_norm_AXI : STD_LOGIC_VECTOR ( 13 downto 0 );
  signal write_m_u3_norm_AXI : STD_LOGIC_VECTOR ( 13 downto 0 );
begin
u_PWM_and_SS_control_V3_ip_axi_lite_inst: entity work.zusys_PWM_and_SS_control_V_0_2_PWM_and_SS_control_V3_ip_axi_lite
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
      AXI4_Lite_RDATA(26 downto 0) => AXI4_Lite_RDATA(26 downto 0),
      AXI4_Lite_RREADY => AXI4_Lite_RREADY,
      AXI4_Lite_WDATA(24 downto 0) => AXI4_Lite_WDATA(24 downto 0),
      AXI4_Lite_WSTRB(3 downto 0) => AXI4_Lite_WSTRB(3 downto 0),
      AXI4_Lite_WVALID => AXI4_Lite_WVALID,
      CEA1 => write_axi_enable,
      CEB2 => u_PWM_and_SS_control_V3_ip_axi_lite_inst_n_8,
      D(24 downto 10) => PWM_f_carrier_kHz_rd_AXI_sig(24 downto 10),
      D(9) => u_PWM_and_SS_control_V3_ip_dut_inst_n_20,
      D(8) => u_PWM_and_SS_control_V3_ip_dut_inst_n_21,
      D(7) => u_PWM_and_SS_control_V3_ip_dut_inst_n_22,
      D(6) => u_PWM_and_SS_control_V3_ip_dut_inst_n_23,
      D(5) => u_PWM_and_SS_control_V3_ip_dut_inst_n_24,
      D(4) => u_PWM_and_SS_control_V3_ip_dut_inst_n_25,
      D(3) => u_PWM_and_SS_control_V3_ip_dut_inst_n_26,
      D(2) => u_PWM_and_SS_control_V3_ip_dut_inst_n_27,
      D(1) => u_PWM_and_SS_control_V3_ip_dut_inst_n_28,
      D(0) => u_PWM_and_SS_control_V3_ip_dut_inst_n_29,
      FSM_sequential_axi_lite_rstate_reg => FSM_sequential_axi_lite_rstate_reg,
      IPCORE_RESETN => IPCORE_RESETN,
      PWM_en_AXI_1 => \u_PWM_and_SS_control_V3_ip_src_PWM_and_Switching_Signal_Control/u_GenPWM/PWM_en_AXI_1\,
      PWM_en_rd_AXI_sig => PWM_en_rd_AXI_sig,
      Q(1 downto 0) => Q(1 downto 0),
      \read_reg_Mode_rd_AXI_reg[1]\(1 downto 0) => Mode_rd_AXI_sig(1 downto 0),
      \read_reg_PWM_T_carrier_us_rd_AXI_reg[24]\(24 downto 0) => PWM_T_carrier_us_rd_AXI_sig(24 downto 0),
      \read_reg_PWM_min_pulse_width_rd_AXI_reg[17]\(17 downto 0) => PWM_min_pulse_width_rd_AXI_sig(17 downto 0),
      reset => reset,
      write_PWM_en_AXI => write_PWM_en_AXI,
      \write_reg_Mode_AXI_reg[1]\(1 downto 0) => write_Mode_AXI(1 downto 0),
      \write_reg_PWM_min_pulse_width_AXI_reg[17]\(17 downto 0) => write_PWM_min_pulse_width_AXI(17 downto 0),
      \write_reg_Scal_T_carrier_AXI_reg[24]\(24 downto 0) => write_Scal_T_carrier_AXI(24 downto 0),
      \write_reg_Scal_f_carrier_AXI_reg[24]\(24 downto 0) => write_Scal_f_carrier_AXI(24 downto 0),
      \write_reg_TriState_HB1_AXI_reg[1]\(1 downto 0) => write_TriState_HB1_AXI(1 downto 0),
      \write_reg_TriState_HB2_AXI_reg[1]\(1 downto 0) => write_TriState_HB2_AXI(1 downto 0),
      \write_reg_TriState_HB3_AXI_reg[1]\(1 downto 0) => write_TriState_HB3_AXI(1 downto 0),
      \write_reg_m_u1_norm_AXI_reg[13]\(13 downto 0) => write_m_u1_norm_AXI(13 downto 0),
      \write_reg_m_u2_norm_AXI_reg[13]\(13 downto 0) => write_m_u2_norm_AXI(13 downto 0),
      \write_reg_m_u3_norm_AXI_reg[13]\(13 downto 0) => write_m_u3_norm_AXI(13 downto 0)
    );
u_PWM_and_SS_control_V3_ip_dut_inst: entity work.zusys_PWM_and_SS_control_V_0_2_PWM_and_SS_control_V3_ip_dut
     port map (
      B(7 downto 0) => B(7 downto 0),
      CEB2 => u_PWM_and_SS_control_V3_ip_axi_lite_inst_n_8,
      CO(0) => CO(0),
      D(24 downto 0) => write_Scal_f_carrier_AXI(24 downto 0),
      DI(1) => DI(0),
      DI(0) => \HDL_Counter2_count_reg[7]\(0),
      E(0) => write_axi_enable,
      \HDL_Counter2_count_reg[0]\(0) => DI(1),
      \HDL_Counter2_count_reg[2]\ => \HDL_Counter2_count_reg[7]\(1),
      \HDL_Counter2_count_reg[3]\ => \HDL_Counter2_count_reg[7]\(2),
      \HDL_Counter2_count_reg[4]\ => \HDL_Counter2_count_reg[7]\(3),
      \HDL_Counter2_count_reg[5]\ => \HDL_Counter2_count_reg[7]\(4),
      \HDL_Counter2_count_reg[6]\ => \HDL_Counter2_count_reg[7]\(5),
      \HDL_Counter2_count_reg[7]\ => \HDL_Counter2_count_reg[7]\(6),
      IPCORE_CLK => IPCORE_CLK,
      PWM_en_AXI_1 => \u_PWM_and_SS_control_V3_ip_src_PWM_and_Switching_Signal_Control/u_GenPWM/PWM_en_AXI_1\,
      PWM_en_rd_AXI_sig => PWM_en_rd_AXI_sig,
      PWM_enb_out => PWM_enb_out,
      Q(24 downto 0) => PWM_T_carrier_us_rd_AXI_sig(24 downto 0),
      S(7 downto 0) => S(7 downto 0),
      SS0_IN_External => SS0_IN_External,
      SS0_OUT => SS0_OUT,
      SS1_IN_External => SS1_IN_External,
      SS1_OUT => SS1_OUT,
      SS2_IN_External => SS2_IN_External,
      SS2_OUT => SS2_OUT,
      SS3_IN_External => SS3_IN_External,
      SS3_OUT => SS3_OUT,
      SS4_IN_External => SS4_IN_External,
      SS4_OUT => SS4_OUT,
      SS5_IN_External => SS5_IN_External,
      SS5_OUT => SS5_OUT,
      \T_carrier_us_AXI_1_reg[24]\(24 downto 0) => write_Scal_T_carrier_AXI(24 downto 0),
      Triangular_Max => Triangular_Max,
      Triangular_Min => Triangular_Min,
      \U1_norm_1_reg[13]\(13 downto 0) => write_m_u1_norm_AXI(13 downto 0),
      \U2_norm_1_reg[13]\(13 downto 0) => write_m_u2_norm_AXI(13 downto 0),
      \U3_norm_1_reg[13]\(13 downto 0) => write_m_u3_norm_AXI(13 downto 0),
      \f_carrier_kHz_AXI_2_reg[24]\(24 downto 10) => PWM_f_carrier_kHz_rd_AXI_sig(24 downto 10),
      \f_carrier_kHz_AXI_2_reg[24]\(9) => u_PWM_and_SS_control_V3_ip_dut_inst_n_20,
      \f_carrier_kHz_AXI_2_reg[24]\(8) => u_PWM_and_SS_control_V3_ip_dut_inst_n_21,
      \f_carrier_kHz_AXI_2_reg[24]\(7) => u_PWM_and_SS_control_V3_ip_dut_inst_n_22,
      \f_carrier_kHz_AXI_2_reg[24]\(6) => u_PWM_and_SS_control_V3_ip_dut_inst_n_23,
      \f_carrier_kHz_AXI_2_reg[24]\(5) => u_PWM_and_SS_control_V3_ip_dut_inst_n_24,
      \f_carrier_kHz_AXI_2_reg[24]\(4) => u_PWM_and_SS_control_V3_ip_dut_inst_n_25,
      \f_carrier_kHz_AXI_2_reg[24]\(3) => u_PWM_and_SS_control_V3_ip_dut_inst_n_26,
      \f_carrier_kHz_AXI_2_reg[24]\(2) => u_PWM_and_SS_control_V3_ip_dut_inst_n_27,
      \f_carrier_kHz_AXI_2_reg[24]\(1) => u_PWM_and_SS_control_V3_ip_dut_inst_n_28,
      \f_carrier_kHz_AXI_2_reg[24]\(0) => u_PWM_and_SS_control_V3_ip_dut_inst_n_29,
      m_u1_norm(13 downto 0) => m_u1_norm(13 downto 0),
      m_u2_norm(13 downto 0) => m_u2_norm(13 downto 0),
      m_u3_norm(13 downto 0) => m_u3_norm(13 downto 0),
      \min_pulse_width_AXI_1_reg[17]\(17 downto 0) => write_PWM_min_pulse_width_AXI(17 downto 0),
      \min_pulse_width_AXI_2_reg[17]\(17 downto 0) => PWM_min_pulse_width_rd_AXI_sig(17 downto 0),
      \reduced_reg_1_reg[0][1]\(1 downto 0) => write_Mode_AXI(1 downto 0),
      \reduced_reg_1_reg[1][1]\(1 downto 0) => Mode_rd_AXI_sig(1 downto 0),
      \reduced_reg_2_reg[0][1]\(1 downto 0) => write_TriState_HB2_AXI(1 downto 0),
      \reduced_reg_3_reg[0][1]\(1 downto 0) => write_TriState_HB3_AXI(1 downto 0),
      \reduced_reg_reg[0][1]\(1 downto 0) => write_TriState_HB1_AXI(1 downto 0),
      reset => reset,
      write_PWM_en_AXI => write_PWM_en_AXI
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity zusys_PWM_and_SS_control_V_0_2 is
  port (
    IPCORE_CLK : in STD_LOGIC;
    IPCORE_RESETN : in STD_LOGIC;
    m_u1_norm : in STD_LOGIC_VECTOR ( 13 downto 0 );
    m_u2_norm : in STD_LOGIC_VECTOR ( 13 downto 0 );
    m_u3_norm : in STD_LOGIC_VECTOR ( 13 downto 0 );
    SS0_IN_External : in STD_LOGIC;
    SS1_IN_External : in STD_LOGIC;
    SS2_IN_External : in STD_LOGIC;
    SS3_IN_External : in STD_LOGIC;
    SS4_IN_External : in STD_LOGIC;
    SS5_IN_External : in STD_LOGIC;
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
    SS0_OUT : out STD_LOGIC;
    SS1_OUT : out STD_LOGIC;
    SS2_OUT : out STD_LOGIC;
    SS3_OUT : out STD_LOGIC;
    SS4_OUT : out STD_LOGIC;
    SS5_OUT : out STD_LOGIC;
    PWM_enb_out : out STD_LOGIC;
    Triangular_Max : out STD_LOGIC;
    Triangular_Min : out STD_LOGIC;
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
  attribute NotValidForBitStream of zusys_PWM_and_SS_control_V_0_2 : entity is true;
  attribute CHECK_LICENSE_TYPE : string;
  attribute CHECK_LICENSE_TYPE of zusys_PWM_and_SS_control_V_0_2 : entity is "zusys_PWM_and_SS_control_V_0_0,PWM_and_SS_control_V3_ip,{}";
  attribute downgradeipidentifiedwarnings : string;
  attribute downgradeipidentifiedwarnings of zusys_PWM_and_SS_control_V_0_2 : entity is "yes";
  attribute ip_definition_source : string;
  attribute ip_definition_source of zusys_PWM_and_SS_control_V_0_2 : entity is "package_project";
  attribute x_core_info : string;
  attribute x_core_info of zusys_PWM_and_SS_control_V_0_2 : entity is "PWM_and_SS_control_V3_ip,Vivado 2020.1.1";
end zusys_PWM_and_SS_control_V_0_2;

architecture STRUCTURE of zusys_PWM_and_SS_control_V_0_2 is
  signal \<const0>\ : STD_LOGIC;
  signal \^axi4_lite_rdata\ : STD_LOGIC_VECTOR ( 29 downto 0 );
  signal U0_n_11 : STD_LOGIC;
  signal U0_n_12 : STD_LOGIC;
  signal U0_n_13 : STD_LOGIC;
  signal U0_n_14 : STD_LOGIC;
  signal U0_n_15 : STD_LOGIC;
  signal U0_n_16 : STD_LOGIC;
  signal U0_n_17 : STD_LOGIC;
  signal U0_n_18 : STD_LOGIC;
  signal U0_n_19 : STD_LOGIC;
  signal U0_n_20 : STD_LOGIC;
  signal \u_PWM_and_SS_control_V3_ip_dut_inst/u_PWM_and_SS_control_V3_ip_src_PWM_and_Switching_Signal_Control/u_GenPWM/HDL_Counter2_count_next\ : STD_LOGIC_VECTOR ( 8 downto 1 );
  signal \u_PWM_and_SS_control_V3_ip_dut_inst/u_PWM_and_SS_control_V3_ip_src_PWM_and_Switching_Signal_Control/u_GenPWM/HDL_Counter2_count_reg\ : STD_LOGIC_VECTOR ( 7 downto 0 );
  signal \u_PWM_and_SS_control_V3_ip_src_PWM_and_Switching_Signal_Control/u_GenPWM/HDL_Counter2_count_next_carry_n_0\ : STD_LOGIC;
  signal \u_PWM_and_SS_control_V3_ip_src_PWM_and_Switching_Signal_Control/u_GenPWM/HDL_Counter2_count_next_carry_n_1\ : STD_LOGIC;
  signal \u_PWM_and_SS_control_V3_ip_src_PWM_and_Switching_Signal_Control/u_GenPWM/HDL_Counter2_count_next_carry_n_2\ : STD_LOGIC;
  signal \u_PWM_and_SS_control_V3_ip_src_PWM_and_Switching_Signal_Control/u_GenPWM/HDL_Counter2_count_next_carry_n_3\ : STD_LOGIC;
  signal \u_PWM_and_SS_control_V3_ip_src_PWM_and_Switching_Signal_Control/u_GenPWM/HDL_Counter2_count_next_carry_n_4\ : STD_LOGIC;
  signal \u_PWM_and_SS_control_V3_ip_src_PWM_and_Switching_Signal_Control/u_GenPWM/HDL_Counter2_count_next_carry_n_5\ : STD_LOGIC;
  signal \u_PWM_and_SS_control_V3_ip_src_PWM_and_Switching_Signal_Control/u_GenPWM/HDL_Counter2_count_next_carry_n_6\ : STD_LOGIC;
  signal \u_PWM_and_SS_control_V3_ip_src_PWM_and_Switching_Signal_Control/u_GenPWM/HDL_Counter2_count_next_carry_n_7\ : STD_LOGIC;
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
  AXI4_Lite_RDATA(31) <= \^axi4_lite_rdata\(27);
  AXI4_Lite_RDATA(30) <= \^axi4_lite_rdata\(29);
  AXI4_Lite_RDATA(29) <= \^axi4_lite_rdata\(29);
  AXI4_Lite_RDATA(28) <= \^axi4_lite_rdata\(29);
  AXI4_Lite_RDATA(27) <= \^axi4_lite_rdata\(27);
  AXI4_Lite_RDATA(26) <= \^axi4_lite_rdata\(29);
  AXI4_Lite_RDATA(25) <= \^axi4_lite_rdata\(29);
  AXI4_Lite_RDATA(24 downto 0) <= \^axi4_lite_rdata\(24 downto 0);
  AXI4_Lite_RRESP(1) <= \<const0>\;
  AXI4_Lite_RRESP(0) <= \<const0>\;
GND: unisim.vcomponents.GND
     port map (
      G => \<const0>\
    );
U0: entity work.zusys_PWM_and_SS_control_V_0_2_PWM_and_SS_control_V3_ip
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
      AXI4_Lite_RDATA(26) => \^axi4_lite_rdata\(27),
      AXI4_Lite_RDATA(25) => \^axi4_lite_rdata\(29),
      AXI4_Lite_RDATA(24 downto 0) => \^axi4_lite_rdata\(24 downto 0),
      AXI4_Lite_RREADY => AXI4_Lite_RREADY,
      AXI4_Lite_WDATA(24 downto 0) => AXI4_Lite_WDATA(24 downto 0),
      AXI4_Lite_WSTRB(3 downto 0) => AXI4_Lite_WSTRB(3 downto 0),
      AXI4_Lite_WVALID => AXI4_Lite_WVALID,
      B(7 downto 0) => \u_PWM_and_SS_control_V3_ip_dut_inst/u_PWM_and_SS_control_V3_ip_src_PWM_and_Switching_Signal_Control/u_GenPWM/HDL_Counter2_count_next\(8 downto 1),
      CO(0) => \u_PWM_and_SS_control_V3_ip_src_PWM_and_Switching_Signal_Control/u_GenPWM/HDL_Counter2_count_next_carry_n_0\,
      DI(1) => U0_n_11,
      DI(0) => U0_n_12,
      FSM_sequential_axi_lite_rstate_reg => AXI4_Lite_RVALID,
      \HDL_Counter2_count_reg[7]\(6 downto 1) => \u_PWM_and_SS_control_V3_ip_dut_inst/u_PWM_and_SS_control_V3_ip_src_PWM_and_Switching_Signal_Control/u_GenPWM/HDL_Counter2_count_reg\(7 downto 2),
      \HDL_Counter2_count_reg[7]\(0) => \u_PWM_and_SS_control_V3_ip_dut_inst/u_PWM_and_SS_control_V3_ip_src_PWM_and_Switching_Signal_Control/u_GenPWM/HDL_Counter2_count_reg\(0),
      IPCORE_CLK => IPCORE_CLK,
      IPCORE_RESETN => IPCORE_RESETN,
      PWM_enb_out => PWM_enb_out,
      Q(1) => AXI4_Lite_BVALID,
      Q(0) => AXI4_Lite_WREADY,
      S(7) => U0_n_13,
      S(6) => U0_n_14,
      S(5) => U0_n_15,
      S(4) => U0_n_16,
      S(3) => U0_n_17,
      S(2) => U0_n_18,
      S(1) => U0_n_19,
      S(0) => U0_n_20,
      SS0_IN_External => SS0_IN_External,
      SS0_OUT => SS0_OUT,
      SS1_IN_External => SS1_IN_External,
      SS1_OUT => SS1_OUT,
      SS2_IN_External => SS2_IN_External,
      SS2_OUT => SS2_OUT,
      SS3_IN_External => SS3_IN_External,
      SS3_OUT => SS3_OUT,
      SS4_IN_External => SS4_IN_External,
      SS4_OUT => SS4_OUT,
      SS5_IN_External => SS5_IN_External,
      SS5_OUT => SS5_OUT,
      Triangular_Max => Triangular_Max,
      Triangular_Min => Triangular_Min,
      m_u1_norm(13 downto 0) => m_u1_norm(13 downto 0),
      m_u2_norm(13 downto 0) => m_u2_norm(13 downto 0),
      m_u3_norm(13 downto 0) => m_u3_norm(13 downto 0)
    );
\u_PWM_and_SS_control_V3_ip_src_PWM_and_Switching_Signal_Control/u_GenPWM/HDL_Counter2_count_next_carry\: unisim.vcomponents.CARRY8
     port map (
      CI => \u_PWM_and_SS_control_V3_ip_dut_inst/u_PWM_and_SS_control_V3_ip_src_PWM_and_Switching_Signal_Control/u_GenPWM/HDL_Counter2_count_reg\(0),
      CI_TOP => '0',
      CO(7) => \u_PWM_and_SS_control_V3_ip_src_PWM_and_Switching_Signal_Control/u_GenPWM/HDL_Counter2_count_next_carry_n_0\,
      CO(6) => \u_PWM_and_SS_control_V3_ip_src_PWM_and_Switching_Signal_Control/u_GenPWM/HDL_Counter2_count_next_carry_n_1\,
      CO(5) => \u_PWM_and_SS_control_V3_ip_src_PWM_and_Switching_Signal_Control/u_GenPWM/HDL_Counter2_count_next_carry_n_2\,
      CO(4) => \u_PWM_and_SS_control_V3_ip_src_PWM_and_Switching_Signal_Control/u_GenPWM/HDL_Counter2_count_next_carry_n_3\,
      CO(3) => \u_PWM_and_SS_control_V3_ip_src_PWM_and_Switching_Signal_Control/u_GenPWM/HDL_Counter2_count_next_carry_n_4\,
      CO(2) => \u_PWM_and_SS_control_V3_ip_src_PWM_and_Switching_Signal_Control/u_GenPWM/HDL_Counter2_count_next_carry_n_5\,
      CO(1) => \u_PWM_and_SS_control_V3_ip_src_PWM_and_Switching_Signal_Control/u_GenPWM/HDL_Counter2_count_next_carry_n_6\,
      CO(0) => \u_PWM_and_SS_control_V3_ip_src_PWM_and_Switching_Signal_Control/u_GenPWM/HDL_Counter2_count_next_carry_n_7\,
      DI(7 downto 2) => \u_PWM_and_SS_control_V3_ip_dut_inst/u_PWM_and_SS_control_V3_ip_src_PWM_and_Switching_Signal_Control/u_GenPWM/HDL_Counter2_count_reg\(7 downto 2),
      DI(1) => U0_n_11,
      DI(0) => U0_n_12,
      O(7 downto 0) => \u_PWM_and_SS_control_V3_ip_dut_inst/u_PWM_and_SS_control_V3_ip_src_PWM_and_Switching_Signal_Control/u_GenPWM/HDL_Counter2_count_next\(8 downto 1),
      S(7) => U0_n_13,
      S(6) => U0_n_14,
      S(5) => U0_n_15,
      S(4) => U0_n_16,
      S(3) => U0_n_17,
      S(2) => U0_n_18,
      S(1) => U0_n_19,
      S(0) => U0_n_20
    );
end STRUCTURE;
