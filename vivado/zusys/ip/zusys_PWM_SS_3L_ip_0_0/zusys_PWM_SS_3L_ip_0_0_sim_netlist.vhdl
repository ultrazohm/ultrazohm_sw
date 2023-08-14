-- Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
-- --------------------------------------------------------------------------------
-- Tool Version: Vivado v.2020.1.1 (win64) Build 2960000 Wed Aug  5 22:57:20 MDT 2020
-- Date        : Fri Jan 28 14:47:54 2022
-- Host        : enc177112 running 64-bit major release  (build 9200)
-- Command     : write_vhdl -force -mode funcsim
--               c:/GIT/UltraZohm/software/ultrazohm_sw_develop/vivado/zusys/ip/zusys_PWM_SS_3L_ip_0_0/zusys_PWM_SS_3L_ip_0_0_sim_netlist.vhdl
-- Design      : zusys_PWM_SS_3L_ip_0_0
-- Purpose     : This VHDL netlist is a functional simulation representation of the design and should not be modified or
--               synthesized. This netlist cannot be used for SDF annotated simulation.
-- Device      : xczu9eg-ffvc900-1-e
-- --------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity zusys_PWM_SS_3L_ip_0_0_PWM_SS_3L_ip_addr_decoder is
  port (
    read_reg_ip_timestamp : out STD_LOGIC_VECTOR ( 0 to 0 );
    CEP : out STD_LOGIC;
    write_PWM_en_AXI : out STD_LOGIC;
    data_reg_axi_enable_1_1_reg_0 : out STD_LOGIC;
    \data_reg_PWM_counter_max_value_int_AXI_1_1_reg[19]_0\ : out STD_LOGIC_VECTOR ( 19 downto 0 );
    \data_reg_PWM_min_pulse_width_0to1_AXI_1_1_reg[13]_0\ : out STD_LOGIC_VECTOR ( 13 downto 0 );
    \data_reg_Mode_AXI_1_1_reg[1]_0\ : out STD_LOGIC_VECTOR ( 1 downto 0 );
    \data_reg_TriState_HB1_AXI_1_1_reg[1]_0\ : out STD_LOGIC_VECTOR ( 1 downto 0 );
    \data_reg_TriState_HB2_AXI_1_1_reg[1]_0\ : out STD_LOGIC_VECTOR ( 1 downto 0 );
    \data_reg_TriState_HB3_AXI_1_1_reg[1]_0\ : out STD_LOGIC_VECTOR ( 1 downto 0 );
    \data_reg_m_u1_norm_AXI_1_1_reg[13]_0\ : out STD_LOGIC_VECTOR ( 13 downto 0 );
    \data_reg_m_u2_norm_AXI_1_1_reg[13]_0\ : out STD_LOGIC_VECTOR ( 13 downto 0 );
    \data_reg_m_u3_norm_AXI_1_1_reg[13]_0\ : out STD_LOGIC_VECTOR ( 13 downto 0 );
    RSTP : in STD_LOGIC;
    AXI4_Lite_ACLK : in STD_LOGIC;
    data_reg_axi_enable_1_1_reg_1 : in STD_LOGIC;
    data_reg_PWM_en_AXI_1_1_reg_0 : in STD_LOGIC;
    \HDL_Counter2_count_reg[19]\ : in STD_LOGIC;
    E : in STD_LOGIC_VECTOR ( 0 to 0 );
    Q : in STD_LOGIC_VECTOR ( 19 downto 0 );
    \data_reg_PWM_min_pulse_width_0to1_AXI_1_1_reg[13]_1\ : in STD_LOGIC_VECTOR ( 0 to 0 );
    \data_reg_Mode_AXI_1_1_reg[1]_1\ : in STD_LOGIC_VECTOR ( 0 to 0 );
    \data_reg_TriState_HB1_AXI_1_1_reg[1]_1\ : in STD_LOGIC_VECTOR ( 0 to 0 );
    \data_reg_TriState_HB2_AXI_1_1_reg[1]_1\ : in STD_LOGIC_VECTOR ( 0 to 0 );
    \data_reg_TriState_HB3_AXI_1_1_reg[1]_1\ : in STD_LOGIC_VECTOR ( 0 to 0 );
    \data_reg_m_u1_norm_AXI_1_1_reg[13]_1\ : in STD_LOGIC_VECTOR ( 0 to 0 );
    \data_reg_m_u2_norm_AXI_1_1_reg[13]_1\ : in STD_LOGIC_VECTOR ( 0 to 0 );
    \data_reg_m_u3_norm_AXI_1_1_reg[13]_1\ : in STD_LOGIC_VECTOR ( 0 to 0 )
  );
  attribute ORIG_REF_NAME : string;
  attribute ORIG_REF_NAME of zusys_PWM_SS_3L_ip_0_0_PWM_SS_3L_ip_addr_decoder : entity is "PWM_SS_3L_ip_addr_decoder";
end zusys_PWM_SS_3L_ip_0_0_PWM_SS_3L_ip_addr_decoder;

architecture STRUCTURE of zusys_PWM_SS_3L_ip_0_0_PWM_SS_3L_ip_addr_decoder is
  signal \^cep\ : STD_LOGIC;
begin
  CEP <= \^cep\;
\HDL_Counter2_count[0]_i_1\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"8"
    )
        port map (
      I0 => \^cep\,
      I1 => \HDL_Counter2_count_reg[19]\,
      O => data_reg_axi_enable_1_1_reg_0
    );
\data_reg_Mode_AXI_1_1_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \data_reg_Mode_AXI_1_1_reg[1]_1\(0),
      D => Q(0),
      Q => \data_reg_Mode_AXI_1_1_reg[1]_0\(0),
      R => RSTP
    );
\data_reg_Mode_AXI_1_1_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \data_reg_Mode_AXI_1_1_reg[1]_1\(0),
      D => Q(1),
      Q => \data_reg_Mode_AXI_1_1_reg[1]_0\(1),
      R => RSTP
    );
\data_reg_PWM_counter_max_value_int_AXI_1_1_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => E(0),
      D => Q(0),
      Q => \data_reg_PWM_counter_max_value_int_AXI_1_1_reg[19]_0\(0),
      R => RSTP
    );
\data_reg_PWM_counter_max_value_int_AXI_1_1_reg[10]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => E(0),
      D => Q(10),
      Q => \data_reg_PWM_counter_max_value_int_AXI_1_1_reg[19]_0\(10),
      R => RSTP
    );
\data_reg_PWM_counter_max_value_int_AXI_1_1_reg[11]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => E(0),
      D => Q(11),
      Q => \data_reg_PWM_counter_max_value_int_AXI_1_1_reg[19]_0\(11),
      R => RSTP
    );
\data_reg_PWM_counter_max_value_int_AXI_1_1_reg[12]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => E(0),
      D => Q(12),
      Q => \data_reg_PWM_counter_max_value_int_AXI_1_1_reg[19]_0\(12),
      R => RSTP
    );
\data_reg_PWM_counter_max_value_int_AXI_1_1_reg[13]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => E(0),
      D => Q(13),
      Q => \data_reg_PWM_counter_max_value_int_AXI_1_1_reg[19]_0\(13),
      R => RSTP
    );
\data_reg_PWM_counter_max_value_int_AXI_1_1_reg[14]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => E(0),
      D => Q(14),
      Q => \data_reg_PWM_counter_max_value_int_AXI_1_1_reg[19]_0\(14),
      R => RSTP
    );
\data_reg_PWM_counter_max_value_int_AXI_1_1_reg[15]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => E(0),
      D => Q(15),
      Q => \data_reg_PWM_counter_max_value_int_AXI_1_1_reg[19]_0\(15),
      R => RSTP
    );
\data_reg_PWM_counter_max_value_int_AXI_1_1_reg[16]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => E(0),
      D => Q(16),
      Q => \data_reg_PWM_counter_max_value_int_AXI_1_1_reg[19]_0\(16),
      R => RSTP
    );
\data_reg_PWM_counter_max_value_int_AXI_1_1_reg[17]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => E(0),
      D => Q(17),
      Q => \data_reg_PWM_counter_max_value_int_AXI_1_1_reg[19]_0\(17),
      R => RSTP
    );
\data_reg_PWM_counter_max_value_int_AXI_1_1_reg[18]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => E(0),
      D => Q(18),
      Q => \data_reg_PWM_counter_max_value_int_AXI_1_1_reg[19]_0\(18),
      R => RSTP
    );
\data_reg_PWM_counter_max_value_int_AXI_1_1_reg[19]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => E(0),
      D => Q(19),
      Q => \data_reg_PWM_counter_max_value_int_AXI_1_1_reg[19]_0\(19),
      R => RSTP
    );
\data_reg_PWM_counter_max_value_int_AXI_1_1_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => E(0),
      D => Q(1),
      Q => \data_reg_PWM_counter_max_value_int_AXI_1_1_reg[19]_0\(1),
      R => RSTP
    );
\data_reg_PWM_counter_max_value_int_AXI_1_1_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => E(0),
      D => Q(2),
      Q => \data_reg_PWM_counter_max_value_int_AXI_1_1_reg[19]_0\(2),
      R => RSTP
    );
\data_reg_PWM_counter_max_value_int_AXI_1_1_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => E(0),
      D => Q(3),
      Q => \data_reg_PWM_counter_max_value_int_AXI_1_1_reg[19]_0\(3),
      R => RSTP
    );
\data_reg_PWM_counter_max_value_int_AXI_1_1_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => E(0),
      D => Q(4),
      Q => \data_reg_PWM_counter_max_value_int_AXI_1_1_reg[19]_0\(4),
      R => RSTP
    );
\data_reg_PWM_counter_max_value_int_AXI_1_1_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => E(0),
      D => Q(5),
      Q => \data_reg_PWM_counter_max_value_int_AXI_1_1_reg[19]_0\(5),
      R => RSTP
    );
\data_reg_PWM_counter_max_value_int_AXI_1_1_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => E(0),
      D => Q(6),
      Q => \data_reg_PWM_counter_max_value_int_AXI_1_1_reg[19]_0\(6),
      R => RSTP
    );
\data_reg_PWM_counter_max_value_int_AXI_1_1_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => E(0),
      D => Q(7),
      Q => \data_reg_PWM_counter_max_value_int_AXI_1_1_reg[19]_0\(7),
      R => RSTP
    );
\data_reg_PWM_counter_max_value_int_AXI_1_1_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => E(0),
      D => Q(8),
      Q => \data_reg_PWM_counter_max_value_int_AXI_1_1_reg[19]_0\(8),
      R => RSTP
    );
\data_reg_PWM_counter_max_value_int_AXI_1_1_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => E(0),
      D => Q(9),
      Q => \data_reg_PWM_counter_max_value_int_AXI_1_1_reg[19]_0\(9),
      R => RSTP
    );
data_reg_PWM_en_AXI_1_1_reg: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => data_reg_PWM_en_AXI_1_1_reg_0,
      Q => write_PWM_en_AXI,
      R => RSTP
    );
\data_reg_PWM_min_pulse_width_0to1_AXI_1_1_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \data_reg_PWM_min_pulse_width_0to1_AXI_1_1_reg[13]_1\(0),
      D => Q(0),
      Q => \data_reg_PWM_min_pulse_width_0to1_AXI_1_1_reg[13]_0\(0),
      R => RSTP
    );
\data_reg_PWM_min_pulse_width_0to1_AXI_1_1_reg[10]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \data_reg_PWM_min_pulse_width_0to1_AXI_1_1_reg[13]_1\(0),
      D => Q(10),
      Q => \data_reg_PWM_min_pulse_width_0to1_AXI_1_1_reg[13]_0\(10),
      R => RSTP
    );
\data_reg_PWM_min_pulse_width_0to1_AXI_1_1_reg[11]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \data_reg_PWM_min_pulse_width_0to1_AXI_1_1_reg[13]_1\(0),
      D => Q(11),
      Q => \data_reg_PWM_min_pulse_width_0to1_AXI_1_1_reg[13]_0\(11),
      R => RSTP
    );
\data_reg_PWM_min_pulse_width_0to1_AXI_1_1_reg[12]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \data_reg_PWM_min_pulse_width_0to1_AXI_1_1_reg[13]_1\(0),
      D => Q(12),
      Q => \data_reg_PWM_min_pulse_width_0to1_AXI_1_1_reg[13]_0\(12),
      R => RSTP
    );
\data_reg_PWM_min_pulse_width_0to1_AXI_1_1_reg[13]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \data_reg_PWM_min_pulse_width_0to1_AXI_1_1_reg[13]_1\(0),
      D => Q(13),
      Q => \data_reg_PWM_min_pulse_width_0to1_AXI_1_1_reg[13]_0\(13),
      R => RSTP
    );
\data_reg_PWM_min_pulse_width_0to1_AXI_1_1_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \data_reg_PWM_min_pulse_width_0to1_AXI_1_1_reg[13]_1\(0),
      D => Q(1),
      Q => \data_reg_PWM_min_pulse_width_0to1_AXI_1_1_reg[13]_0\(1),
      R => RSTP
    );
\data_reg_PWM_min_pulse_width_0to1_AXI_1_1_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \data_reg_PWM_min_pulse_width_0to1_AXI_1_1_reg[13]_1\(0),
      D => Q(2),
      Q => \data_reg_PWM_min_pulse_width_0to1_AXI_1_1_reg[13]_0\(2),
      R => RSTP
    );
\data_reg_PWM_min_pulse_width_0to1_AXI_1_1_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \data_reg_PWM_min_pulse_width_0to1_AXI_1_1_reg[13]_1\(0),
      D => Q(3),
      Q => \data_reg_PWM_min_pulse_width_0to1_AXI_1_1_reg[13]_0\(3),
      R => RSTP
    );
\data_reg_PWM_min_pulse_width_0to1_AXI_1_1_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \data_reg_PWM_min_pulse_width_0to1_AXI_1_1_reg[13]_1\(0),
      D => Q(4),
      Q => \data_reg_PWM_min_pulse_width_0to1_AXI_1_1_reg[13]_0\(4),
      R => RSTP
    );
\data_reg_PWM_min_pulse_width_0to1_AXI_1_1_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \data_reg_PWM_min_pulse_width_0to1_AXI_1_1_reg[13]_1\(0),
      D => Q(5),
      Q => \data_reg_PWM_min_pulse_width_0to1_AXI_1_1_reg[13]_0\(5),
      R => RSTP
    );
\data_reg_PWM_min_pulse_width_0to1_AXI_1_1_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \data_reg_PWM_min_pulse_width_0to1_AXI_1_1_reg[13]_1\(0),
      D => Q(6),
      Q => \data_reg_PWM_min_pulse_width_0to1_AXI_1_1_reg[13]_0\(6),
      R => RSTP
    );
\data_reg_PWM_min_pulse_width_0to1_AXI_1_1_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \data_reg_PWM_min_pulse_width_0to1_AXI_1_1_reg[13]_1\(0),
      D => Q(7),
      Q => \data_reg_PWM_min_pulse_width_0to1_AXI_1_1_reg[13]_0\(7),
      R => RSTP
    );
\data_reg_PWM_min_pulse_width_0to1_AXI_1_1_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \data_reg_PWM_min_pulse_width_0to1_AXI_1_1_reg[13]_1\(0),
      D => Q(8),
      Q => \data_reg_PWM_min_pulse_width_0to1_AXI_1_1_reg[13]_0\(8),
      R => RSTP
    );
\data_reg_PWM_min_pulse_width_0to1_AXI_1_1_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \data_reg_PWM_min_pulse_width_0to1_AXI_1_1_reg[13]_1\(0),
      D => Q(9),
      Q => \data_reg_PWM_min_pulse_width_0to1_AXI_1_1_reg[13]_0\(9),
      R => RSTP
    );
\data_reg_TriState_HB1_AXI_1_1_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \data_reg_TriState_HB1_AXI_1_1_reg[1]_1\(0),
      D => Q(0),
      Q => \data_reg_TriState_HB1_AXI_1_1_reg[1]_0\(0),
      R => RSTP
    );
\data_reg_TriState_HB1_AXI_1_1_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \data_reg_TriState_HB1_AXI_1_1_reg[1]_1\(0),
      D => Q(1),
      Q => \data_reg_TriState_HB1_AXI_1_1_reg[1]_0\(1),
      R => RSTP
    );
\data_reg_TriState_HB2_AXI_1_1_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \data_reg_TriState_HB2_AXI_1_1_reg[1]_1\(0),
      D => Q(0),
      Q => \data_reg_TriState_HB2_AXI_1_1_reg[1]_0\(0),
      R => RSTP
    );
\data_reg_TriState_HB2_AXI_1_1_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \data_reg_TriState_HB2_AXI_1_1_reg[1]_1\(0),
      D => Q(1),
      Q => \data_reg_TriState_HB2_AXI_1_1_reg[1]_0\(1),
      R => RSTP
    );
\data_reg_TriState_HB3_AXI_1_1_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \data_reg_TriState_HB3_AXI_1_1_reg[1]_1\(0),
      D => Q(0),
      Q => \data_reg_TriState_HB3_AXI_1_1_reg[1]_0\(0),
      R => RSTP
    );
\data_reg_TriState_HB3_AXI_1_1_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \data_reg_TriState_HB3_AXI_1_1_reg[1]_1\(0),
      D => Q(1),
      Q => \data_reg_TriState_HB3_AXI_1_1_reg[1]_0\(1),
      R => RSTP
    );
data_reg_axi_enable_1_1_reg: unisim.vcomponents.FDSE
     port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => data_reg_axi_enable_1_1_reg_1,
      Q => \^cep\,
      S => RSTP
    );
\data_reg_m_u1_norm_AXI_1_1_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \data_reg_m_u1_norm_AXI_1_1_reg[13]_1\(0),
      D => Q(0),
      Q => \data_reg_m_u1_norm_AXI_1_1_reg[13]_0\(0),
      R => RSTP
    );
\data_reg_m_u1_norm_AXI_1_1_reg[10]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \data_reg_m_u1_norm_AXI_1_1_reg[13]_1\(0),
      D => Q(10),
      Q => \data_reg_m_u1_norm_AXI_1_1_reg[13]_0\(10),
      R => RSTP
    );
\data_reg_m_u1_norm_AXI_1_1_reg[11]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \data_reg_m_u1_norm_AXI_1_1_reg[13]_1\(0),
      D => Q(11),
      Q => \data_reg_m_u1_norm_AXI_1_1_reg[13]_0\(11),
      R => RSTP
    );
\data_reg_m_u1_norm_AXI_1_1_reg[12]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \data_reg_m_u1_norm_AXI_1_1_reg[13]_1\(0),
      D => Q(12),
      Q => \data_reg_m_u1_norm_AXI_1_1_reg[13]_0\(12),
      R => RSTP
    );
\data_reg_m_u1_norm_AXI_1_1_reg[13]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \data_reg_m_u1_norm_AXI_1_1_reg[13]_1\(0),
      D => Q(13),
      Q => \data_reg_m_u1_norm_AXI_1_1_reg[13]_0\(13),
      R => RSTP
    );
\data_reg_m_u1_norm_AXI_1_1_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \data_reg_m_u1_norm_AXI_1_1_reg[13]_1\(0),
      D => Q(1),
      Q => \data_reg_m_u1_norm_AXI_1_1_reg[13]_0\(1),
      R => RSTP
    );
\data_reg_m_u1_norm_AXI_1_1_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \data_reg_m_u1_norm_AXI_1_1_reg[13]_1\(0),
      D => Q(2),
      Q => \data_reg_m_u1_norm_AXI_1_1_reg[13]_0\(2),
      R => RSTP
    );
\data_reg_m_u1_norm_AXI_1_1_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \data_reg_m_u1_norm_AXI_1_1_reg[13]_1\(0),
      D => Q(3),
      Q => \data_reg_m_u1_norm_AXI_1_1_reg[13]_0\(3),
      R => RSTP
    );
\data_reg_m_u1_norm_AXI_1_1_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \data_reg_m_u1_norm_AXI_1_1_reg[13]_1\(0),
      D => Q(4),
      Q => \data_reg_m_u1_norm_AXI_1_1_reg[13]_0\(4),
      R => RSTP
    );
\data_reg_m_u1_norm_AXI_1_1_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \data_reg_m_u1_norm_AXI_1_1_reg[13]_1\(0),
      D => Q(5),
      Q => \data_reg_m_u1_norm_AXI_1_1_reg[13]_0\(5),
      R => RSTP
    );
\data_reg_m_u1_norm_AXI_1_1_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \data_reg_m_u1_norm_AXI_1_1_reg[13]_1\(0),
      D => Q(6),
      Q => \data_reg_m_u1_norm_AXI_1_1_reg[13]_0\(6),
      R => RSTP
    );
\data_reg_m_u1_norm_AXI_1_1_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \data_reg_m_u1_norm_AXI_1_1_reg[13]_1\(0),
      D => Q(7),
      Q => \data_reg_m_u1_norm_AXI_1_1_reg[13]_0\(7),
      R => RSTP
    );
\data_reg_m_u1_norm_AXI_1_1_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \data_reg_m_u1_norm_AXI_1_1_reg[13]_1\(0),
      D => Q(8),
      Q => \data_reg_m_u1_norm_AXI_1_1_reg[13]_0\(8),
      R => RSTP
    );
\data_reg_m_u1_norm_AXI_1_1_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \data_reg_m_u1_norm_AXI_1_1_reg[13]_1\(0),
      D => Q(9),
      Q => \data_reg_m_u1_norm_AXI_1_1_reg[13]_0\(9),
      R => RSTP
    );
\data_reg_m_u2_norm_AXI_1_1_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \data_reg_m_u2_norm_AXI_1_1_reg[13]_1\(0),
      D => Q(0),
      Q => \data_reg_m_u2_norm_AXI_1_1_reg[13]_0\(0),
      R => RSTP
    );
\data_reg_m_u2_norm_AXI_1_1_reg[10]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \data_reg_m_u2_norm_AXI_1_1_reg[13]_1\(0),
      D => Q(10),
      Q => \data_reg_m_u2_norm_AXI_1_1_reg[13]_0\(10),
      R => RSTP
    );
\data_reg_m_u2_norm_AXI_1_1_reg[11]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \data_reg_m_u2_norm_AXI_1_1_reg[13]_1\(0),
      D => Q(11),
      Q => \data_reg_m_u2_norm_AXI_1_1_reg[13]_0\(11),
      R => RSTP
    );
\data_reg_m_u2_norm_AXI_1_1_reg[12]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \data_reg_m_u2_norm_AXI_1_1_reg[13]_1\(0),
      D => Q(12),
      Q => \data_reg_m_u2_norm_AXI_1_1_reg[13]_0\(12),
      R => RSTP
    );
\data_reg_m_u2_norm_AXI_1_1_reg[13]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \data_reg_m_u2_norm_AXI_1_1_reg[13]_1\(0),
      D => Q(13),
      Q => \data_reg_m_u2_norm_AXI_1_1_reg[13]_0\(13),
      R => RSTP
    );
\data_reg_m_u2_norm_AXI_1_1_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \data_reg_m_u2_norm_AXI_1_1_reg[13]_1\(0),
      D => Q(1),
      Q => \data_reg_m_u2_norm_AXI_1_1_reg[13]_0\(1),
      R => RSTP
    );
\data_reg_m_u2_norm_AXI_1_1_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \data_reg_m_u2_norm_AXI_1_1_reg[13]_1\(0),
      D => Q(2),
      Q => \data_reg_m_u2_norm_AXI_1_1_reg[13]_0\(2),
      R => RSTP
    );
\data_reg_m_u2_norm_AXI_1_1_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \data_reg_m_u2_norm_AXI_1_1_reg[13]_1\(0),
      D => Q(3),
      Q => \data_reg_m_u2_norm_AXI_1_1_reg[13]_0\(3),
      R => RSTP
    );
\data_reg_m_u2_norm_AXI_1_1_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \data_reg_m_u2_norm_AXI_1_1_reg[13]_1\(0),
      D => Q(4),
      Q => \data_reg_m_u2_norm_AXI_1_1_reg[13]_0\(4),
      R => RSTP
    );
\data_reg_m_u2_norm_AXI_1_1_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \data_reg_m_u2_norm_AXI_1_1_reg[13]_1\(0),
      D => Q(5),
      Q => \data_reg_m_u2_norm_AXI_1_1_reg[13]_0\(5),
      R => RSTP
    );
\data_reg_m_u2_norm_AXI_1_1_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \data_reg_m_u2_norm_AXI_1_1_reg[13]_1\(0),
      D => Q(6),
      Q => \data_reg_m_u2_norm_AXI_1_1_reg[13]_0\(6),
      R => RSTP
    );
\data_reg_m_u2_norm_AXI_1_1_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \data_reg_m_u2_norm_AXI_1_1_reg[13]_1\(0),
      D => Q(7),
      Q => \data_reg_m_u2_norm_AXI_1_1_reg[13]_0\(7),
      R => RSTP
    );
\data_reg_m_u2_norm_AXI_1_1_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \data_reg_m_u2_norm_AXI_1_1_reg[13]_1\(0),
      D => Q(8),
      Q => \data_reg_m_u2_norm_AXI_1_1_reg[13]_0\(8),
      R => RSTP
    );
\data_reg_m_u2_norm_AXI_1_1_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \data_reg_m_u2_norm_AXI_1_1_reg[13]_1\(0),
      D => Q(9),
      Q => \data_reg_m_u2_norm_AXI_1_1_reg[13]_0\(9),
      R => RSTP
    );
\data_reg_m_u3_norm_AXI_1_1_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \data_reg_m_u3_norm_AXI_1_1_reg[13]_1\(0),
      D => Q(0),
      Q => \data_reg_m_u3_norm_AXI_1_1_reg[13]_0\(0),
      R => RSTP
    );
\data_reg_m_u3_norm_AXI_1_1_reg[10]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \data_reg_m_u3_norm_AXI_1_1_reg[13]_1\(0),
      D => Q(10),
      Q => \data_reg_m_u3_norm_AXI_1_1_reg[13]_0\(10),
      R => RSTP
    );
\data_reg_m_u3_norm_AXI_1_1_reg[11]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \data_reg_m_u3_norm_AXI_1_1_reg[13]_1\(0),
      D => Q(11),
      Q => \data_reg_m_u3_norm_AXI_1_1_reg[13]_0\(11),
      R => RSTP
    );
\data_reg_m_u3_norm_AXI_1_1_reg[12]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \data_reg_m_u3_norm_AXI_1_1_reg[13]_1\(0),
      D => Q(12),
      Q => \data_reg_m_u3_norm_AXI_1_1_reg[13]_0\(12),
      R => RSTP
    );
\data_reg_m_u3_norm_AXI_1_1_reg[13]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \data_reg_m_u3_norm_AXI_1_1_reg[13]_1\(0),
      D => Q(13),
      Q => \data_reg_m_u3_norm_AXI_1_1_reg[13]_0\(13),
      R => RSTP
    );
\data_reg_m_u3_norm_AXI_1_1_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \data_reg_m_u3_norm_AXI_1_1_reg[13]_1\(0),
      D => Q(1),
      Q => \data_reg_m_u3_norm_AXI_1_1_reg[13]_0\(1),
      R => RSTP
    );
\data_reg_m_u3_norm_AXI_1_1_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \data_reg_m_u3_norm_AXI_1_1_reg[13]_1\(0),
      D => Q(2),
      Q => \data_reg_m_u3_norm_AXI_1_1_reg[13]_0\(2),
      R => RSTP
    );
\data_reg_m_u3_norm_AXI_1_1_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \data_reg_m_u3_norm_AXI_1_1_reg[13]_1\(0),
      D => Q(3),
      Q => \data_reg_m_u3_norm_AXI_1_1_reg[13]_0\(3),
      R => RSTP
    );
\data_reg_m_u3_norm_AXI_1_1_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \data_reg_m_u3_norm_AXI_1_1_reg[13]_1\(0),
      D => Q(4),
      Q => \data_reg_m_u3_norm_AXI_1_1_reg[13]_0\(4),
      R => RSTP
    );
\data_reg_m_u3_norm_AXI_1_1_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \data_reg_m_u3_norm_AXI_1_1_reg[13]_1\(0),
      D => Q(5),
      Q => \data_reg_m_u3_norm_AXI_1_1_reg[13]_0\(5),
      R => RSTP
    );
\data_reg_m_u3_norm_AXI_1_1_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \data_reg_m_u3_norm_AXI_1_1_reg[13]_1\(0),
      D => Q(6),
      Q => \data_reg_m_u3_norm_AXI_1_1_reg[13]_0\(6),
      R => RSTP
    );
\data_reg_m_u3_norm_AXI_1_1_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \data_reg_m_u3_norm_AXI_1_1_reg[13]_1\(0),
      D => Q(7),
      Q => \data_reg_m_u3_norm_AXI_1_1_reg[13]_0\(7),
      R => RSTP
    );
\data_reg_m_u3_norm_AXI_1_1_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \data_reg_m_u3_norm_AXI_1_1_reg[13]_1\(0),
      D => Q(8),
      Q => \data_reg_m_u3_norm_AXI_1_1_reg[13]_0\(8),
      R => RSTP
    );
\data_reg_m_u3_norm_AXI_1_1_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => \data_reg_m_u3_norm_AXI_1_1_reg[13]_1\(0),
      D => Q(9),
      Q => \data_reg_m_u3_norm_AXI_1_1_reg[13]_0\(9),
      R => RSTP
    );
\read_reg_ip_timestamp_reg[30]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => '1',
      Q => read_reg_ip_timestamp(0),
      R => RSTP
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity zusys_PWM_SS_3L_ip_0_0_PWM_SS_3L_ip_axi_lite_module is
  port (
    FSM_sequential_axi_lite_rstate_reg_0 : out STD_LOGIC;
    AXI4_Lite_RDATA : out STD_LOGIC_VECTOR ( 0 to 0 );
    soft_reset : out STD_LOGIC;
    \AXI4_Lite_ARADDR[3]\ : out STD_LOGIC_VECTOR ( 0 to 0 );
    \AXI4_Lite_ARADDR[3]_0\ : out STD_LOGIC_VECTOR ( 0 to 0 );
    \AXI4_Lite_ARADDR[3]_1\ : out STD_LOGIC_VECTOR ( 0 to 0 );
    \AXI4_Lite_ARADDR[3]_2\ : out STD_LOGIC_VECTOR ( 0 to 0 );
    \AXI4_Lite_ARADDR[3]_3\ : out STD_LOGIC_VECTOR ( 0 to 0 );
    E : out STD_LOGIC_VECTOR ( 0 to 0 );
    \AXI4_Lite_ARADDR[6]\ : out STD_LOGIC_VECTOR ( 0 to 0 );
    \AXI4_Lite_ARADDR[6]_0\ : out STD_LOGIC_VECTOR ( 0 to 0 );
    \AXI4_Lite_ARADDR[6]_1\ : out STD_LOGIC_VECTOR ( 0 to 0 );
    AXI4_Lite_ARREADY : out STD_LOGIC;
    AXI4_Lite_AWREADY : out STD_LOGIC;
    reset_in : out STD_LOGIC;
    Q : out STD_LOGIC_VECTOR ( 19 downto 0 );
    \FSM_onehot_axi_lite_wstate_reg[2]_0\ : out STD_LOGIC_VECTOR ( 1 downto 0 );
    \wdata_reg[0]_0\ : out STD_LOGIC;
    \wdata_reg[0]_1\ : out STD_LOGIC;
    AXI4_Lite_ACLK : in STD_LOGIC;
    AXI4_Lite_ARADDR : in STD_LOGIC_VECTOR ( 13 downto 0 );
    AXI4_Lite_ARVALID : in STD_LOGIC;
    read_reg_ip_timestamp : in STD_LOGIC_VECTOR ( 0 to 0 );
    AXI4_Lite_RREADY : in STD_LOGIC;
    AXI4_Lite_AWVALID : in STD_LOGIC;
    AXI4_Lite_ARESETN : in STD_LOGIC;
    IPCORE_RESETN : in STD_LOGIC;
    AXI4_Lite_BREADY : in STD_LOGIC;
    AXI4_Lite_WVALID : in STD_LOGIC;
    AXI4_Lite_WSTRB : in STD_LOGIC_VECTOR ( 3 downto 0 );
    CEP : in STD_LOGIC;
    write_PWM_en_AXI : in STD_LOGIC;
    AXI4_Lite_AWADDR : in STD_LOGIC_VECTOR ( 13 downto 0 );
    AXI4_Lite_WDATA : in STD_LOGIC_VECTOR ( 19 downto 0 )
  );
  attribute ORIG_REF_NAME : string;
  attribute ORIG_REF_NAME of zusys_PWM_SS_3L_ip_0_0_PWM_SS_3L_ip_axi_lite_module : entity is "PWM_SS_3L_ip_axi_lite_module";
end zusys_PWM_SS_3L_ip_0_0_PWM_SS_3L_ip_axi_lite_module;

architecture STRUCTURE of zusys_PWM_SS_3L_ip_0_0_PWM_SS_3L_ip_axi_lite_module is
  signal \^axi4_lite_arready\ : STD_LOGIC;
  signal \^axi4_lite_rdata\ : STD_LOGIC_VECTOR ( 0 to 0 );
  signal \AXI4_Lite_RDATA_tmp[30]_i_1_n_0\ : STD_LOGIC;
  signal \AXI4_Lite_RDATA_tmp[30]_i_2_n_0\ : STD_LOGIC;
  signal \AXI4_Lite_RDATA_tmp[30]_i_3_n_0\ : STD_LOGIC;
  signal \AXI4_Lite_RDATA_tmp[30]_i_4_n_0\ : STD_LOGIC;
  signal \AXI4_Lite_RDATA_tmp[30]_i_5_n_0\ : STD_LOGIC;
  signal \AXI4_Lite_RDATA_tmp[30]_i_6_n_0\ : STD_LOGIC;
  signal \^fsm_onehot_axi_lite_wstate_reg[2]_0\ : STD_LOGIC_VECTOR ( 1 downto 0 );
  signal \FSM_onehot_axi_lite_wstate_reg_n_0_[0]\ : STD_LOGIC;
  signal \^fsm_sequential_axi_lite_rstate_reg_0\ : STD_LOGIC;
  signal \^q\ : STD_LOGIC_VECTOR ( 19 downto 0 );
  signal aw_transfer : STD_LOGIC;
  signal axi_lite_rstate_next : STD_LOGIC;
  signal axi_lite_wstate_next : STD_LOGIC_VECTOR ( 2 downto 0 );
  signal \data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_10_n_0\ : STD_LOGIC;
  signal \data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_11_n_0\ : STD_LOGIC;
  signal \data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_2_n_0\ : STD_LOGIC;
  signal \data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_3_n_0\ : STD_LOGIC;
  signal \data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_4_n_0\ : STD_LOGIC;
  signal \data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_5_n_0\ : STD_LOGIC;
  signal \data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_6_n_0\ : STD_LOGIC;
  signal \data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_7_n_0\ : STD_LOGIC;
  signal \data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_8_n_0\ : STD_LOGIC;
  signal \data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_9_n_0\ : STD_LOGIC;
  signal data_reg_PWM_en_AXI_1_1_i_2_n_0 : STD_LOGIC;
  signal data_reg_PWM_en_AXI_1_1_i_3_n_0 : STD_LOGIC;
  signal data_reg_PWM_en_AXI_1_1_i_4_n_0 : STD_LOGIC;
  signal data_reg_axi_enable_1_1_i_2_n_0 : STD_LOGIC;
  signal data_reg_axi_enable_1_1_i_3_n_0 : STD_LOGIC;
  signal data_reg_axi_enable_1_1_i_4_n_0 : STD_LOGIC;
  signal reset : STD_LOGIC;
  signal sel0 : STD_LOGIC_VECTOR ( 13 downto 0 );
  signal \^soft_reset\ : STD_LOGIC;
  signal soft_reset_i_1_n_0 : STD_LOGIC;
  signal soft_reset_i_2_n_0 : STD_LOGIC;
  signal soft_reset_i_3_n_0 : STD_LOGIC;
  signal soft_reset_i_4_n_0 : STD_LOGIC;
  signal soft_reset_i_5_n_0 : STD_LOGIC;
  signal top_wr_enb : STD_LOGIC;
  signal w_transfer : STD_LOGIC;
  signal w_transfer_and_wstrb : STD_LOGIC;
  attribute SOFT_HLUTNM : string;
  attribute SOFT_HLUTNM of AXI4_Lite_ARREADY_INST_0 : label is "soft_lutpair7";
  attribute SOFT_HLUTNM of AXI4_Lite_AWREADY_INST_0 : label is "soft_lutpair8";
  attribute SOFT_HLUTNM of \AXI4_Lite_RDATA_tmp[30]_i_5\ : label is "soft_lutpair6";
  attribute SOFT_HLUTNM of \FSM_onehot_axi_lite_wstate[0]_i_1\ : label is "soft_lutpair8";
  attribute FSM_ENCODED_STATES : string;
  attribute FSM_ENCODED_STATES of \FSM_onehot_axi_lite_wstate_reg[0]\ : label is "iSTATE:010,iSTATE0:100,iSTATE1:001";
  attribute FSM_ENCODED_STATES of \FSM_onehot_axi_lite_wstate_reg[1]\ : label is "iSTATE:010,iSTATE0:100,iSTATE1:001";
  attribute FSM_ENCODED_STATES of \FSM_onehot_axi_lite_wstate_reg[2]\ : label is "iSTATE:010,iSTATE0:100,iSTATE1:001";
  attribute SOFT_HLUTNM of FSM_sequential_axi_lite_rstate_i_1 : label is "soft_lutpair7";
  attribute FSM_ENCODED_STATES of FSM_sequential_axi_lite_rstate_reg : label is "iSTATE:0,iSTATE0:1";
  attribute SOFT_HLUTNM of \data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_1\ : label is "soft_lutpair2";
  attribute SOFT_HLUTNM of \data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_10\ : label is "soft_lutpair6";
  attribute SOFT_HLUTNM of \data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_2\ : label is "soft_lutpair9";
  attribute SOFT_HLUTNM of \data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_3\ : label is "soft_lutpair9";
  attribute SOFT_HLUTNM of \data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_4\ : label is "soft_lutpair4";
  attribute SOFT_HLUTNM of \data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_7\ : label is "soft_lutpair5";
  attribute SOFT_HLUTNM of data_reg_PWM_en_AXI_1_1_i_3 : label is "soft_lutpair5";
  attribute SOFT_HLUTNM of \data_reg_PWM_min_pulse_width_0to1_AXI_1_1[13]_i_1\ : label is "soft_lutpair1";
  attribute SOFT_HLUTNM of \data_reg_TriState_HB1_AXI_1_1[1]_i_1\ : label is "soft_lutpair3";
  attribute SOFT_HLUTNM of \data_reg_TriState_HB2_AXI_1_1[1]_i_1\ : label is "soft_lutpair3";
  attribute SOFT_HLUTNM of \data_reg_TriState_HB3_AXI_1_1[1]_i_1\ : label is "soft_lutpair2";
  attribute SOFT_HLUTNM of data_reg_axi_enable_1_1_i_3 : label is "soft_lutpair4";
  attribute SOFT_HLUTNM of \data_reg_m_u1_norm_AXI_1_1[13]_i_1\ : label is "soft_lutpair1";
  attribute SOFT_HLUTNM of \data_reg_m_u2_norm_AXI_1_1[13]_i_1\ : label is "soft_lutpair0";
  attribute SOFT_HLUTNM of \data_reg_m_u3_norm_AXI_1_1[13]_i_1\ : label is "soft_lutpair0";
begin
  AXI4_Lite_ARREADY <= \^axi4_lite_arready\;
  AXI4_Lite_RDATA(0) <= \^axi4_lite_rdata\(0);
  \FSM_onehot_axi_lite_wstate_reg[2]_0\(1 downto 0) <= \^fsm_onehot_axi_lite_wstate_reg[2]_0\(1 downto 0);
  FSM_sequential_axi_lite_rstate_reg_0 <= \^fsm_sequential_axi_lite_rstate_reg_0\;
  Q(19 downto 0) <= \^q\(19 downto 0);
  soft_reset <= \^soft_reset\;
AXI4_Lite_ARREADY_INST_0: unisim.vcomponents.LUT3
    generic map(
      INIT => X"04"
    )
        port map (
      I0 => \^fsm_sequential_axi_lite_rstate_reg_0\,
      I1 => \FSM_onehot_axi_lite_wstate_reg_n_0_[0]\,
      I2 => AXI4_Lite_AWVALID,
      O => \^axi4_lite_arready\
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
\AXI4_Lite_RDATA_tmp[30]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"10FFFFFF10000000"
    )
        port map (
      I0 => \AXI4_Lite_RDATA_tmp[30]_i_2_n_0\,
      I1 => \AXI4_Lite_RDATA_tmp[30]_i_3_n_0\,
      I2 => \AXI4_Lite_RDATA_tmp[30]_i_4_n_0\,
      I3 => AXI4_Lite_ARVALID,
      I4 => \^axi4_lite_arready\,
      I5 => \^axi4_lite_rdata\(0),
      O => \AXI4_Lite_RDATA_tmp[30]_i_1_n_0\
    );
\AXI4_Lite_RDATA_tmp[30]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFFFFFFFFBBFCB8"
    )
        port map (
      I0 => AXI4_Lite_ARADDR(6),
      I1 => AXI4_Lite_ARVALID,
      I2 => sel0(6),
      I3 => AXI4_Lite_ARADDR(7),
      I4 => sel0(7),
      I5 => data_reg_PWM_en_AXI_1_1_i_3_n_0,
      O => \AXI4_Lite_RDATA_tmp[30]_i_2_n_0\
    );
\AXI4_Lite_RDATA_tmp[30]_i_3\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFFFFFFFFBBFCB8"
    )
        port map (
      I0 => AXI4_Lite_ARADDR(8),
      I1 => AXI4_Lite_ARVALID,
      I2 => sel0(8),
      I3 => AXI4_Lite_ARADDR(9),
      I4 => sel0(9),
      I5 => \AXI4_Lite_RDATA_tmp[30]_i_5_n_0\,
      O => \AXI4_Lite_RDATA_tmp[30]_i_3_n_0\
    );
\AXI4_Lite_RDATA_tmp[30]_i_4\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"00001000"
    )
        port map (
      I0 => data_reg_axi_enable_1_1_i_3_n_0,
      I1 => \AXI4_Lite_RDATA_tmp[30]_i_6_n_0\,
      I2 => \data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_2_n_0\,
      I3 => read_reg_ip_timestamp(0),
      I4 => \data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_3_n_0\,
      O => \AXI4_Lite_RDATA_tmp[30]_i_4_n_0\
    );
\AXI4_Lite_RDATA_tmp[30]_i_5\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFFACCFA"
    )
        port map (
      I0 => sel0(11),
      I1 => AXI4_Lite_ARADDR(11),
      I2 => sel0(10),
      I3 => AXI4_Lite_ARVALID,
      I4 => AXI4_Lite_ARADDR(10),
      O => \AXI4_Lite_RDATA_tmp[30]_i_5_n_0\
    );
\AXI4_Lite_RDATA_tmp[30]_i_6\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFFACCFA"
    )
        port map (
      I0 => sel0(12),
      I1 => AXI4_Lite_ARADDR(12),
      I2 => sel0(13),
      I3 => AXI4_Lite_ARVALID,
      I4 => AXI4_Lite_ARADDR(13),
      O => \AXI4_Lite_RDATA_tmp[30]_i_6_n_0\
    );
\AXI4_Lite_RDATA_tmp_reg[30]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => \AXI4_Lite_RDATA_tmp[30]_i_1_n_0\,
      Q => \^axi4_lite_rdata\(0),
      R => reset
    );
\FSM_onehot_axi_lite_wstate[0]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FF8F8888"
    )
        port map (
      I0 => AXI4_Lite_BREADY,
      I1 => \^fsm_onehot_axi_lite_wstate_reg[2]_0\(1),
      I2 => AXI4_Lite_AWVALID,
      I3 => \^fsm_sequential_axi_lite_rstate_reg_0\,
      I4 => \FSM_onehot_axi_lite_wstate_reg_n_0_[0]\,
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
      INIT => X"44F44444"
    )
        port map (
      I0 => AXI4_Lite_WVALID,
      I1 => \^fsm_onehot_axi_lite_wstate_reg[2]_0\(0),
      I2 => AXI4_Lite_AWVALID,
      I3 => \^fsm_sequential_axi_lite_rstate_reg_0\,
      I4 => \FSM_onehot_axi_lite_wstate_reg_n_0_[0]\,
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
\data_reg_Mode_AXI_1_1[1]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"00000400"
    )
        port map (
      I0 => \data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_5_n_0\,
      I1 => \data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_6_n_0\,
      I2 => \data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_2_n_0\,
      I3 => \data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_3_n_0\,
      I4 => \data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_4_n_0\,
      O => \AXI4_Lite_ARADDR[6]_1\(0)
    );
\data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"00080000"
    )
        port map (
      I0 => \data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_2_n_0\,
      I1 => \data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_3_n_0\,
      I2 => \data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_4_n_0\,
      I3 => \data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_5_n_0\,
      I4 => \data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_6_n_0\,
      O => E(0)
    );
\data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_10\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"B8"
    )
        port map (
      I0 => AXI4_Lite_ARADDR(11),
      I1 => AXI4_Lite_ARVALID,
      I2 => sel0(11),
      O => \data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_10_n_0\
    );
\data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_11\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"B8"
    )
        port map (
      I0 => AXI4_Lite_ARADDR(7),
      I1 => AXI4_Lite_ARVALID,
      I2 => sel0(7),
      O => \data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_11_n_0\
    );
\data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_2\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"B8"
    )
        port map (
      I0 => AXI4_Lite_ARADDR(1),
      I1 => AXI4_Lite_ARVALID,
      I2 => sel0(1),
      O => \data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_2_n_0\
    );
\data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_3\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"B8"
    )
        port map (
      I0 => AXI4_Lite_ARADDR(0),
      I1 => AXI4_Lite_ARVALID,
      I2 => sel0(0),
      O => \data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_3_n_0\
    );
\data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_4\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"B8"
    )
        port map (
      I0 => AXI4_Lite_ARADDR(2),
      I1 => AXI4_Lite_ARVALID,
      I2 => sel0(2),
      O => \data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_4_n_0\
    );
\data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_5\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFFFFFF47034400"
    )
        port map (
      I0 => AXI4_Lite_ARADDR(4),
      I1 => AXI4_Lite_ARVALID,
      I2 => sel0(4),
      I3 => AXI4_Lite_ARADDR(3),
      I4 => sel0(3),
      I5 => \data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_7_n_0\,
      O => \data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_5_n_0\
    );
\data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_6\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"00004000"
    )
        port map (
      I0 => \AXI4_Lite_RDATA_tmp[30]_i_6_n_0\,
      I1 => \data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_8_n_0\,
      I2 => \data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_9_n_0\,
      I3 => top_wr_enb,
      I4 => data_reg_PWM_en_AXI_1_1_i_3_n_0,
      O => \data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_6_n_0\
    );
\data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_7\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"B8"
    )
        port map (
      I0 => AXI4_Lite_ARADDR(5),
      I1 => AXI4_Lite_ARVALID,
      I2 => sel0(5),
      O => \data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_7_n_0\
    );
\data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_8\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0000000003000355"
    )
        port map (
      I0 => sel0(9),
      I1 => AXI4_Lite_ARADDR(9),
      I2 => AXI4_Lite_ARADDR(10),
      I3 => AXI4_Lite_ARVALID,
      I4 => sel0(10),
      I5 => \data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_10_n_0\,
      O => \data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_8_n_0\
    );
\data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_9\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0000000047440300"
    )
        port map (
      I0 => AXI4_Lite_ARADDR(8),
      I1 => AXI4_Lite_ARVALID,
      I2 => sel0(8),
      I3 => sel0(6),
      I4 => AXI4_Lite_ARADDR(6),
      I5 => \data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_11_n_0\,
      O => \data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_9_n_0\
    );
data_reg_PWM_en_AXI_1_1_i_1: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFEFFFFF00200000"
    )
        port map (
      I0 => \^q\(0),
      I1 => data_reg_axi_enable_1_1_i_2_n_0,
      I2 => data_reg_PWM_en_AXI_1_1_i_2_n_0,
      I3 => data_reg_PWM_en_AXI_1_1_i_3_n_0,
      I4 => data_reg_PWM_en_AXI_1_1_i_4_n_0,
      I5 => write_PWM_en_AXI,
      O => \wdata_reg[0]_1\
    );
data_reg_PWM_en_AXI_1_1_i_2: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0000005044440050"
    )
        port map (
      I0 => \data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_2_n_0\,
      I1 => AXI4_Lite_ARADDR(6),
      I2 => sel0(6),
      I3 => sel0(7),
      I4 => AXI4_Lite_ARVALID,
      I5 => AXI4_Lite_ARADDR(7),
      O => data_reg_PWM_en_AXI_1_1_i_2_n_0
    );
data_reg_PWM_en_AXI_1_1_i_3: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFFACCFA"
    )
        port map (
      I0 => sel0(5),
      I1 => AXI4_Lite_ARADDR(5),
      I2 => sel0(4),
      I3 => AXI4_Lite_ARVALID,
      I4 => AXI4_Lite_ARADDR(4),
      O => data_reg_PWM_en_AXI_1_1_i_3_n_0
    );
data_reg_PWM_en_AXI_1_1_i_4: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0004000000040404"
    )
        port map (
      I0 => \data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_3_n_0\,
      I1 => top_wr_enb,
      I2 => \data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_4_n_0\,
      I3 => AXI4_Lite_ARADDR(3),
      I4 => AXI4_Lite_ARVALID,
      I5 => sel0(3),
      O => data_reg_PWM_en_AXI_1_1_i_4_n_0
    );
\data_reg_PWM_min_pulse_width_0to1_AXI_1_1[13]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"00001000"
    )
        port map (
      I0 => \data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_2_n_0\,
      I1 => \data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_3_n_0\,
      I2 => \data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_4_n_0\,
      I3 => \data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_6_n_0\,
      I4 => \data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_5_n_0\,
      O => \AXI4_Lite_ARADDR[3]_2\(0)
    );
\data_reg_TriState_HB1_AXI_1_1[1]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"00020000"
    )
        port map (
      I0 => \data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_5_n_0\,
      I1 => \data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_4_n_0\,
      I2 => \data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_3_n_0\,
      I3 => \data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_2_n_0\,
      I4 => \data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_6_n_0\,
      O => \AXI4_Lite_ARADDR[6]\(0)
    );
\data_reg_TriState_HB2_AXI_1_1[1]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"00200000"
    )
        port map (
      I0 => \data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_5_n_0\,
      I1 => \data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_4_n_0\,
      I2 => \data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_3_n_0\,
      I3 => \data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_2_n_0\,
      I4 => \data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_6_n_0\,
      O => \AXI4_Lite_ARADDR[6]_0\(0)
    );
\data_reg_TriState_HB3_AXI_1_1[1]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"02000000"
    )
        port map (
      I0 => \data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_2_n_0\,
      I1 => \data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_3_n_0\,
      I2 => \data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_4_n_0\,
      I3 => \data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_5_n_0\,
      I4 => \data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_6_n_0\,
      O => \AXI4_Lite_ARADDR[3]_3\(0)
    );
data_reg_axi_enable_1_1_i_1: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFEFFFF00020000"
    )
        port map (
      I0 => \^q\(0),
      I1 => \AXI4_Lite_RDATA_tmp[30]_i_2_n_0\,
      I2 => data_reg_axi_enable_1_1_i_2_n_0,
      I3 => data_reg_axi_enable_1_1_i_3_n_0,
      I4 => data_reg_axi_enable_1_1_i_4_n_0,
      I5 => CEP,
      O => \wdata_reg[0]_0\
    );
data_reg_axi_enable_1_1_i_2: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFFFFFFFFBBFCB8"
    )
        port map (
      I0 => AXI4_Lite_ARADDR(13),
      I1 => AXI4_Lite_ARVALID,
      I2 => sel0(13),
      I3 => AXI4_Lite_ARADDR(12),
      I4 => sel0(12),
      I5 => \AXI4_Lite_RDATA_tmp[30]_i_3_n_0\,
      O => data_reg_axi_enable_1_1_i_2_n_0
    );
data_reg_axi_enable_1_1_i_3: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFFACCFA"
    )
        port map (
      I0 => sel0(3),
      I1 => AXI4_Lite_ARADDR(3),
      I2 => sel0(2),
      I3 => AXI4_Lite_ARVALID,
      I4 => AXI4_Lite_ARADDR(2),
      O => data_reg_axi_enable_1_1_i_3_n_0
    );
data_reg_axi_enable_1_1_i_4: unisim.vcomponents.LUT6
    generic map(
      INIT => X"000000A0888800A0"
    )
        port map (
      I0 => top_wr_enb,
      I1 => AXI4_Lite_ARADDR(0),
      I2 => sel0(0),
      I3 => sel0(1),
      I4 => AXI4_Lite_ARVALID,
      I5 => AXI4_Lite_ARADDR(1),
      O => data_reg_axi_enable_1_1_i_4_n_0
    );
\data_reg_m_u1_norm_AXI_1_1[13]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"00004000"
    )
        port map (
      I0 => \data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_2_n_0\,
      I1 => \data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_3_n_0\,
      I2 => \data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_4_n_0\,
      I3 => \data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_6_n_0\,
      I4 => \data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_5_n_0\,
      O => \AXI4_Lite_ARADDR[3]_1\(0)
    );
\data_reg_m_u2_norm_AXI_1_1[13]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"00002000"
    )
        port map (
      I0 => \data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_2_n_0\,
      I1 => \data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_3_n_0\,
      I2 => \data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_4_n_0\,
      I3 => \data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_6_n_0\,
      I4 => \data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_5_n_0\,
      O => \AXI4_Lite_ARADDR[3]_0\(0)
    );
\data_reg_m_u3_norm_AXI_1_1[13]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"00008000"
    )
        port map (
      I0 => \data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_2_n_0\,
      I1 => \data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_3_n_0\,
      I2 => \data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_4_n_0\,
      I3 => \data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_6_n_0\,
      I4 => \data_reg_PWM_counter_max_value_int_AXI_1_1[19]_i_5_n_0\,
      O => \AXI4_Lite_ARADDR[3]\(0)
    );
reset_pipe_i_1: unisim.vcomponents.LUT3
    generic map(
      INIT => X"DF"
    )
        port map (
      I0 => AXI4_Lite_ARESETN,
      I1 => \^soft_reset\,
      I2 => IPCORE_RESETN,
      O => reset_in
    );
soft_reset_i_1: unisim.vcomponents.LUT5
    generic map(
      INIT => X"0A020000"
    )
        port map (
      I0 => soft_reset_i_2_n_0,
      I1 => sel0(9),
      I2 => sel0(11),
      I3 => sel0(10),
      I4 => soft_reset_i_3_n_0,
      O => soft_reset_i_1_n_0
    );
soft_reset_i_2: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0000000000000008"
    )
        port map (
      I0 => soft_reset_i_4_n_0,
      I1 => soft_reset_i_5_n_0,
      I2 => sel0(1),
      I3 => sel0(0),
      I4 => sel0(4),
      I5 => sel0(2),
      O => soft_reset_i_2_n_0
    );
soft_reset_i_3: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0000230000002323"
    )
        port map (
      I0 => sel0(7),
      I1 => sel0(8),
      I2 => sel0(6),
      I3 => sel0(4),
      I4 => sel0(5),
      I5 => sel0(3),
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
soft_reset_i_5: unisim.vcomponents.LUT4
    generic map(
      INIT => X"0001"
    )
        port map (
      I0 => sel0(10),
      I1 => sel0(8),
      I2 => sel0(7),
      I3 => sel0(5),
      O => soft_reset_i_5_n_0
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
\wdata[19]_i_1\: unisim.vcomponents.LUT2
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
      R => reset
    );
\wdata_reg[10]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => w_transfer,
      D => AXI4_Lite_WDATA(10),
      Q => \^q\(10),
      R => reset
    );
\wdata_reg[11]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => w_transfer,
      D => AXI4_Lite_WDATA(11),
      Q => \^q\(11),
      R => reset
    );
\wdata_reg[12]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => w_transfer,
      D => AXI4_Lite_WDATA(12),
      Q => \^q\(12),
      R => reset
    );
\wdata_reg[13]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => w_transfer,
      D => AXI4_Lite_WDATA(13),
      Q => \^q\(13),
      R => reset
    );
\wdata_reg[14]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => w_transfer,
      D => AXI4_Lite_WDATA(14),
      Q => \^q\(14),
      R => reset
    );
\wdata_reg[15]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => w_transfer,
      D => AXI4_Lite_WDATA(15),
      Q => \^q\(15),
      R => reset
    );
\wdata_reg[16]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => w_transfer,
      D => AXI4_Lite_WDATA(16),
      Q => \^q\(16),
      R => reset
    );
\wdata_reg[17]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => w_transfer,
      D => AXI4_Lite_WDATA(17),
      Q => \^q\(17),
      R => reset
    );
\wdata_reg[18]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => w_transfer,
      D => AXI4_Lite_WDATA(18),
      Q => \^q\(18),
      R => reset
    );
\wdata_reg[19]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => w_transfer,
      D => AXI4_Lite_WDATA(19),
      Q => \^q\(19),
      R => reset
    );
\wdata_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => w_transfer,
      D => AXI4_Lite_WDATA(1),
      Q => \^q\(1),
      R => reset
    );
\wdata_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => w_transfer,
      D => AXI4_Lite_WDATA(2),
      Q => \^q\(2),
      R => reset
    );
\wdata_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => w_transfer,
      D => AXI4_Lite_WDATA(3),
      Q => \^q\(3),
      R => reset
    );
\wdata_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => w_transfer,
      D => AXI4_Lite_WDATA(4),
      Q => \^q\(4),
      R => reset
    );
\wdata_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => w_transfer,
      D => AXI4_Lite_WDATA(5),
      Q => \^q\(5),
      R => reset
    );
\wdata_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => w_transfer,
      D => AXI4_Lite_WDATA(6),
      Q => \^q\(6),
      R => reset
    );
\wdata_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => w_transfer,
      D => AXI4_Lite_WDATA(7),
      Q => \^q\(7),
      R => reset
    );
\wdata_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => w_transfer,
      D => AXI4_Lite_WDATA(8),
      Q => \^q\(8),
      R => reset
    );
\wdata_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => w_transfer,
      D => AXI4_Lite_WDATA(9),
      Q => \^q\(9),
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
      I4 => AXI4_Lite_WVALID,
      I5 => \^fsm_onehot_axi_lite_wstate_reg[2]_0\(0),
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
entity zusys_PWM_SS_3L_ip_0_0_PWM_SS_3L_ip_reset_sync is
  port (
    RSTP : out STD_LOGIC;
    reset_out_reg_0 : out STD_LOGIC;
    reset_in : in STD_LOGIC;
    IPCORE_CLK : in STD_LOGIC;
    CEP : in STD_LOGIC;
    IPCORE_RESETN : in STD_LOGIC;
    soft_reset : in STD_LOGIC;
    AXI4_Lite_ARESETN : in STD_LOGIC
  );
  attribute ORIG_REF_NAME : string;
  attribute ORIG_REF_NAME of zusys_PWM_SS_3L_ip_0_0_PWM_SS_3L_ip_reset_sync : entity is "PWM_SS_3L_ip_reset_sync";
end zusys_PWM_SS_3L_ip_0_0_PWM_SS_3L_ip_reset_sync;

architecture STRUCTURE of zusys_PWM_SS_3L_ip_0_0_PWM_SS_3L_ip_reset_sync is
  signal \^rstp\ : STD_LOGIC;
  signal reset_out_i_1_n_0 : STD_LOGIC;
  signal reset_pipe : STD_LOGIC;
begin
  RSTP <= \^rstp\;
\maximum_counter_value_1[8]_i_1\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"E"
    )
        port map (
      I0 => \^rstp\,
      I1 => CEP,
      O => reset_out_reg_0
    );
reset_out_i_1: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FBFF"
    )
        port map (
      I0 => reset_pipe,
      I1 => IPCORE_RESETN,
      I2 => soft_reset,
      I3 => AXI4_Lite_ARESETN,
      O => reset_out_i_1_n_0
    );
reset_out_reg: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => '1',
      D => reset_out_i_1_n_0,
      Q => \^rstp\,
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
entity zusys_PWM_SS_3L_ip_0_0_PWM_SS_3L_ip_src_Chose_SS is
  port (
    delayMatch_1_reg_1 : out STD_LOGIC_VECTOR ( 0 to 0 );
    delayMatch_1_reg : out STD_LOGIC_VECTOR ( 0 to 0 );
    delayMatch3_1_reg_1 : out STD_LOGIC_VECTOR ( 0 to 0 );
    delayMatch3_1_reg : out STD_LOGIC_VECTOR ( 0 to 0 );
    delayMatch6_1_reg_1 : out STD_LOGIC_VECTOR ( 0 to 0 );
    delayMatch6_1_reg : out STD_LOGIC_VECTOR ( 0 to 0 );
    SSa2_OUT : out STD_LOGIC;
    SSa1_OUT : out STD_LOGIC;
    SSb2_OUT : out STD_LOGIC;
    SSb1_OUT : out STD_LOGIC;
    SSc2_OUT : out STD_LOGIC;
    SSc1_OUT : out STD_LOGIC;
    RSTP : in STD_LOGIC;
    CEP : in STD_LOGIC;
    IPCORE_CLK : in STD_LOGIC;
    \reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2_0\ : in STD_LOGIC_VECTOR ( 0 to 0 );
    \delayMatch2_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2_0\ : in STD_LOGIC_VECTOR ( 1 downto 0 );
    \delayMatch5_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2_0\ : in STD_LOGIC_VECTOR ( 1 downto 0 );
    \delayMatch8_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2_0\ : in STD_LOGIC_VECTOR ( 1 downto 0 );
    Demux_out3 : in STD_LOGIC_VECTOR ( 0 to 1 );
    Demux_out2 : in STD_LOGIC_VECTOR ( 0 to 1 );
    Demux_out1 : in STD_LOGIC_VECTOR ( 0 to 1 );
    Q : in STD_LOGIC_VECTOR ( 1 downto 0 );
    SSb1_OUT_0 : in STD_LOGIC_VECTOR ( 1 downto 0 );
    SSc1_OUT_0 : in STD_LOGIC_VECTOR ( 1 downto 0 )
  );
  attribute ORIG_REF_NAME : string;
  attribute ORIG_REF_NAME of zusys_PWM_SS_3L_ip_0_0_PWM_SS_3L_ip_src_Chose_SS : entity is "PWM_SS_3L_ip_src_Chose_SS";
end zusys_PWM_SS_3L_ip_0_0_PWM_SS_3L_ip_src_Chose_SS;

architecture STRUCTURE of zusys_PWM_SS_3L_ip_0_0_PWM_SS_3L_ip_src_Chose_SS is
  signal SSa_IN_External_2 : STD_LOGIC_VECTOR ( 0 to 1 );
  signal SSb_IN_External_2 : STD_LOGIC_VECTOR ( 0 to 1 );
  signal SSc_IN_External_2 : STD_LOGIC_VECTOR ( 0 to 1 );
  signal \delayMatch2_reg_reg[2][0]_srl3___U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_1_n_0\ : STD_LOGIC;
  signal \delayMatch2_reg_reg[2][1]_srl3___U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_1_n_0\ : STD_LOGIC;
  signal \delayMatch2_reg_reg[3][0]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2_n_0\ : STD_LOGIC;
  signal \delayMatch2_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2_n_0\ : STD_LOGIC;
  signal \delayMatch2_reg_reg_gate__0_n_0\ : STD_LOGIC;
  signal delayMatch2_reg_reg_gate_n_0 : STD_LOGIC;
  signal \delayMatch2_reg_reg_n_0_[4][0]\ : STD_LOGIC;
  signal \delayMatch2_reg_reg_n_0_[4][1]\ : STD_LOGIC;
  signal \^delaymatch3_1_reg\ : STD_LOGIC_VECTOR ( 0 to 0 );
  signal \^delaymatch3_1_reg_1\ : STD_LOGIC_VECTOR ( 0 to 0 );
  signal \delayMatch5_reg_reg[2][0]_srl3___U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_1_n_0\ : STD_LOGIC;
  signal \delayMatch5_reg_reg[2][1]_srl3___U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_1_n_0\ : STD_LOGIC;
  signal \delayMatch5_reg_reg[3][0]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2_n_0\ : STD_LOGIC;
  signal \delayMatch5_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2_n_0\ : STD_LOGIC;
  signal \delayMatch5_reg_reg_gate__0_n_0\ : STD_LOGIC;
  signal delayMatch5_reg_reg_gate_n_0 : STD_LOGIC;
  signal \delayMatch5_reg_reg_n_0_[4][0]\ : STD_LOGIC;
  signal \delayMatch5_reg_reg_n_0_[4][1]\ : STD_LOGIC;
  signal \^delaymatch6_1_reg\ : STD_LOGIC_VECTOR ( 0 to 0 );
  signal \^delaymatch6_1_reg_1\ : STD_LOGIC_VECTOR ( 0 to 0 );
  signal \delayMatch8_reg_reg[2][0]_srl3___U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_1_n_0\ : STD_LOGIC;
  signal \delayMatch8_reg_reg[2][1]_srl3___U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_1_n_0\ : STD_LOGIC;
  signal \delayMatch8_reg_reg[3][0]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2_n_0\ : STD_LOGIC;
  signal \delayMatch8_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2_n_0\ : STD_LOGIC;
  signal \delayMatch8_reg_reg_gate__0_n_0\ : STD_LOGIC;
  signal delayMatch8_reg_reg_gate_n_0 : STD_LOGIC;
  signal \delayMatch8_reg_reg_n_0_[4][0]\ : STD_LOGIC;
  signal \delayMatch8_reg_reg_n_0_[4][1]\ : STD_LOGIC;
  signal \^delaymatch_1_reg\ : STD_LOGIC_VECTOR ( 0 to 0 );
  signal \^delaymatch_1_reg_1\ : STD_LOGIC_VECTOR ( 0 to 0 );
  signal \reduced_reg_reg[2][1]_srl3___U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_1_n_0\ : STD_LOGIC;
  signal \reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2_n_0\ : STD_LOGIC;
  signal reduced_reg_reg_gate_n_0 : STD_LOGIC;
  signal reduced_reg_reg_r_0_n_0 : STD_LOGIC;
  signal reduced_reg_reg_r_1_n_0 : STD_LOGIC;
  signal reduced_reg_reg_r_2_n_0 : STD_LOGIC;
  signal reduced_reg_reg_r_n_0 : STD_LOGIC;
  signal switch_compare_1 : STD_LOGIC;
  attribute srl_bus_name : string;
  attribute srl_bus_name of \delayMatch2_reg_reg[2][0]_srl3___U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_1\ : label is "\U0/u_PWM_SS_3L_ip_dut_inst/u_PWM_SS_3L_ip_src_PWM_SS_Ctrl/u_Chose_SS/delayMatch2_reg_reg[2] ";
  attribute srl_name : string;
  attribute srl_name of \delayMatch2_reg_reg[2][0]_srl3___U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_1\ : label is "\U0/u_PWM_SS_3L_ip_dut_inst/u_PWM_SS_3L_ip_src_PWM_SS_Ctrl/u_Chose_SS/delayMatch2_reg_reg[2][0]_srl3___U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_1 ";
  attribute srl_bus_name of \delayMatch2_reg_reg[2][1]_srl3___U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_1\ : label is "\U0/u_PWM_SS_3L_ip_dut_inst/u_PWM_SS_3L_ip_src_PWM_SS_Ctrl/u_Chose_SS/delayMatch2_reg_reg[2] ";
  attribute srl_name of \delayMatch2_reg_reg[2][1]_srl3___U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_1\ : label is "\U0/u_PWM_SS_3L_ip_dut_inst/u_PWM_SS_3L_ip_src_PWM_SS_Ctrl/u_Chose_SS/delayMatch2_reg_reg[2][1]_srl3___U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_1 ";
  attribute SOFT_HLUTNM : string;
  attribute SOFT_HLUTNM of delayMatch2_reg_reg_gate : label is "soft_lutpair10";
  attribute SOFT_HLUTNM of \delayMatch2_reg_reg_gate__0\ : label is "soft_lutpair11";
  attribute srl_bus_name of \delayMatch5_reg_reg[2][0]_srl3___U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_1\ : label is "\U0/u_PWM_SS_3L_ip_dut_inst/u_PWM_SS_3L_ip_src_PWM_SS_Ctrl/u_Chose_SS/delayMatch5_reg_reg[2] ";
  attribute srl_name of \delayMatch5_reg_reg[2][0]_srl3___U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_1\ : label is "\U0/u_PWM_SS_3L_ip_dut_inst/u_PWM_SS_3L_ip_src_PWM_SS_Ctrl/u_Chose_SS/delayMatch5_reg_reg[2][0]_srl3___U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_1 ";
  attribute srl_bus_name of \delayMatch5_reg_reg[2][1]_srl3___U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_1\ : label is "\U0/u_PWM_SS_3L_ip_dut_inst/u_PWM_SS_3L_ip_src_PWM_SS_Ctrl/u_Chose_SS/delayMatch5_reg_reg[2] ";
  attribute srl_name of \delayMatch5_reg_reg[2][1]_srl3___U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_1\ : label is "\U0/u_PWM_SS_3L_ip_dut_inst/u_PWM_SS_3L_ip_src_PWM_SS_Ctrl/u_Chose_SS/delayMatch5_reg_reg[2][1]_srl3___U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_1 ";
  attribute SOFT_HLUTNM of delayMatch5_reg_reg_gate : label is "soft_lutpair11";
  attribute SOFT_HLUTNM of \delayMatch5_reg_reg_gate__0\ : label is "soft_lutpair12";
  attribute srl_bus_name of \delayMatch8_reg_reg[2][0]_srl3___U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_1\ : label is "\U0/u_PWM_SS_3L_ip_dut_inst/u_PWM_SS_3L_ip_src_PWM_SS_Ctrl/u_Chose_SS/delayMatch8_reg_reg[2] ";
  attribute srl_name of \delayMatch8_reg_reg[2][0]_srl3___U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_1\ : label is "\U0/u_PWM_SS_3L_ip_dut_inst/u_PWM_SS_3L_ip_src_PWM_SS_Ctrl/u_Chose_SS/delayMatch8_reg_reg[2][0]_srl3___U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_1 ";
  attribute srl_bus_name of \delayMatch8_reg_reg[2][1]_srl3___U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_1\ : label is "\U0/u_PWM_SS_3L_ip_dut_inst/u_PWM_SS_3L_ip_src_PWM_SS_Ctrl/u_Chose_SS/delayMatch8_reg_reg[2] ";
  attribute srl_name of \delayMatch8_reg_reg[2][1]_srl3___U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_1\ : label is "\U0/u_PWM_SS_3L_ip_dut_inst/u_PWM_SS_3L_ip_src_PWM_SS_Ctrl/u_Chose_SS/delayMatch8_reg_reg[2][1]_srl3___U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_1 ";
  attribute SOFT_HLUTNM of delayMatch8_reg_reg_gate : label is "soft_lutpair12";
  attribute srl_bus_name of \reduced_reg_reg[2][1]_srl3___U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_1\ : label is "\U0/u_PWM_SS_3L_ip_dut_inst/u_PWM_SS_3L_ip_src_PWM_SS_Ctrl/u_Chose_SS/reduced_reg_reg[2] ";
  attribute srl_name of \reduced_reg_reg[2][1]_srl3___U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_1\ : label is "\U0/u_PWM_SS_3L_ip_dut_inst/u_PWM_SS_3L_ip_src_PWM_SS_Ctrl/u_Chose_SS/reduced_reg_reg[2][1]_srl3___U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_1 ";
  attribute SOFT_HLUTNM of reduced_reg_reg_gate : label is "soft_lutpair10";
begin
  delayMatch3_1_reg(0) <= \^delaymatch3_1_reg\(0);
  delayMatch3_1_reg_1(0) <= \^delaymatch3_1_reg_1\(0);
  delayMatch6_1_reg(0) <= \^delaymatch6_1_reg\(0);
  delayMatch6_1_reg_1(0) <= \^delaymatch6_1_reg_1\(0);
  delayMatch_1_reg(0) <= \^delaymatch_1_reg\(0);
  delayMatch_1_reg_1(0) <= \^delaymatch_1_reg_1\(0);
SSa1_OUT_INST_0: unisim.vcomponents.LUT5
    generic map(
      INIT => X"000000E2"
    )
        port map (
      I0 => Q(1),
      I1 => switch_compare_1,
      I2 => SSa_IN_External_2(0),
      I3 => \delayMatch2_reg_reg_n_0_[4][0]\,
      I4 => \delayMatch2_reg_reg_n_0_[4][1]\,
      O => SSa1_OUT
    );
SSa2_OUT_INST_0: unisim.vcomponents.LUT5
    generic map(
      INIT => X"000000E2"
    )
        port map (
      I0 => Q(0),
      I1 => switch_compare_1,
      I2 => SSa_IN_External_2(1),
      I3 => \delayMatch2_reg_reg_n_0_[4][0]\,
      I4 => \delayMatch2_reg_reg_n_0_[4][1]\,
      O => SSa2_OUT
    );
SSb1_OUT_INST_0: unisim.vcomponents.LUT5
    generic map(
      INIT => X"000000E2"
    )
        port map (
      I0 => SSb1_OUT_0(1),
      I1 => switch_compare_1,
      I2 => SSb_IN_External_2(0),
      I3 => \delayMatch5_reg_reg_n_0_[4][0]\,
      I4 => \delayMatch5_reg_reg_n_0_[4][1]\,
      O => SSb1_OUT
    );
SSb2_OUT_INST_0: unisim.vcomponents.LUT5
    generic map(
      INIT => X"000000E2"
    )
        port map (
      I0 => SSb1_OUT_0(0),
      I1 => switch_compare_1,
      I2 => SSb_IN_External_2(1),
      I3 => \delayMatch5_reg_reg_n_0_[4][0]\,
      I4 => \delayMatch5_reg_reg_n_0_[4][1]\,
      O => SSb2_OUT
    );
SSc1_OUT_INST_0: unisim.vcomponents.LUT5
    generic map(
      INIT => X"000000E2"
    )
        port map (
      I0 => SSc1_OUT_0(1),
      I1 => switch_compare_1,
      I2 => SSc_IN_External_2(0),
      I3 => \delayMatch8_reg_reg_n_0_[4][0]\,
      I4 => \delayMatch8_reg_reg_n_0_[4][1]\,
      O => SSc1_OUT
    );
SSc2_OUT_INST_0: unisim.vcomponents.LUT5
    generic map(
      INIT => X"000000E2"
    )
        port map (
      I0 => SSc1_OUT_0(0),
      I1 => switch_compare_1,
      I2 => SSc_IN_External_2(1),
      I3 => \delayMatch8_reg_reg_n_0_[4][0]\,
      I4 => \delayMatch8_reg_reg_n_0_[4][1]\,
      O => SSc2_OUT
    );
\delayMatch2_reg_reg[2][0]_srl3___U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_1\: unisim.vcomponents.SRL16E
     port map (
      A0 => '0',
      A1 => '1',
      A2 => '0',
      A3 => '0',
      CE => CEP,
      CLK => IPCORE_CLK,
      D => \delayMatch2_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2_0\(0),
      Q => \delayMatch2_reg_reg[2][0]_srl3___U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_1_n_0\
    );
\delayMatch2_reg_reg[2][1]_srl3___U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_1\: unisim.vcomponents.SRL16E
     port map (
      A0 => '0',
      A1 => '1',
      A2 => '0',
      A3 => '0',
      CE => CEP,
      CLK => IPCORE_CLK,
      D => \delayMatch2_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2_0\(1),
      Q => \delayMatch2_reg_reg[2][1]_srl3___U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_1_n_0\
    );
\delayMatch2_reg_reg[3][0]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \delayMatch2_reg_reg[2][0]_srl3___U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_1_n_0\,
      Q => \delayMatch2_reg_reg[3][0]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2_n_0\,
      R => '0'
    );
\delayMatch2_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \delayMatch2_reg_reg[2][1]_srl3___U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_1_n_0\,
      Q => \delayMatch2_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2_n_0\,
      R => '0'
    );
\delayMatch2_reg_reg[4][0]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \delayMatch2_reg_reg_gate__0_n_0\,
      Q => \delayMatch2_reg_reg_n_0_[4][0]\,
      R => RSTP
    );
\delayMatch2_reg_reg[4][1]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => delayMatch2_reg_reg_gate_n_0,
      Q => \delayMatch2_reg_reg_n_0_[4][1]\,
      R => RSTP
    );
delayMatch2_reg_reg_gate: unisim.vcomponents.LUT2
    generic map(
      INIT => X"8"
    )
        port map (
      I0 => \delayMatch2_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2_n_0\,
      I1 => reduced_reg_reg_r_2_n_0,
      O => delayMatch2_reg_reg_gate_n_0
    );
\delayMatch2_reg_reg_gate__0\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"8"
    )
        port map (
      I0 => \delayMatch2_reg_reg[3][0]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2_n_0\,
      I1 => reduced_reg_reg_r_2_n_0,
      O => \delayMatch2_reg_reg_gate__0_n_0\
    );
\delayMatch3_1_reg_1_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => Demux_out2(1),
      Q => \^delaymatch3_1_reg_1\(0),
      R => RSTP
    );
\delayMatch3_1_reg_1_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \^delaymatch3_1_reg_1\(0),
      Q => SSb_IN_External_2(1),
      R => RSTP
    );
\delayMatch3_1_reg_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => Demux_out2(0),
      Q => \^delaymatch3_1_reg\(0),
      R => RSTP
    );
\delayMatch3_1_reg_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \^delaymatch3_1_reg\(0),
      Q => SSb_IN_External_2(0),
      R => RSTP
    );
\delayMatch5_reg_reg[2][0]_srl3___U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_1\: unisim.vcomponents.SRL16E
     port map (
      A0 => '0',
      A1 => '1',
      A2 => '0',
      A3 => '0',
      CE => CEP,
      CLK => IPCORE_CLK,
      D => \delayMatch5_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2_0\(0),
      Q => \delayMatch5_reg_reg[2][0]_srl3___U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_1_n_0\
    );
\delayMatch5_reg_reg[2][1]_srl3___U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_1\: unisim.vcomponents.SRL16E
     port map (
      A0 => '0',
      A1 => '1',
      A2 => '0',
      A3 => '0',
      CE => CEP,
      CLK => IPCORE_CLK,
      D => \delayMatch5_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2_0\(1),
      Q => \delayMatch5_reg_reg[2][1]_srl3___U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_1_n_0\
    );
\delayMatch5_reg_reg[3][0]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \delayMatch5_reg_reg[2][0]_srl3___U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_1_n_0\,
      Q => \delayMatch5_reg_reg[3][0]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2_n_0\,
      R => '0'
    );
\delayMatch5_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \delayMatch5_reg_reg[2][1]_srl3___U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_1_n_0\,
      Q => \delayMatch5_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2_n_0\,
      R => '0'
    );
\delayMatch5_reg_reg[4][0]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \delayMatch5_reg_reg_gate__0_n_0\,
      Q => \delayMatch5_reg_reg_n_0_[4][0]\,
      R => RSTP
    );
\delayMatch5_reg_reg[4][1]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => delayMatch5_reg_reg_gate_n_0,
      Q => \delayMatch5_reg_reg_n_0_[4][1]\,
      R => RSTP
    );
delayMatch5_reg_reg_gate: unisim.vcomponents.LUT2
    generic map(
      INIT => X"8"
    )
        port map (
      I0 => \delayMatch5_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2_n_0\,
      I1 => reduced_reg_reg_r_2_n_0,
      O => delayMatch5_reg_reg_gate_n_0
    );
\delayMatch5_reg_reg_gate__0\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"8"
    )
        port map (
      I0 => \delayMatch5_reg_reg[3][0]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2_n_0\,
      I1 => reduced_reg_reg_r_2_n_0,
      O => \delayMatch5_reg_reg_gate__0_n_0\
    );
\delayMatch6_1_reg_1_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => Demux_out3(1),
      Q => \^delaymatch6_1_reg_1\(0),
      R => RSTP
    );
\delayMatch6_1_reg_1_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \^delaymatch6_1_reg_1\(0),
      Q => SSc_IN_External_2(1),
      R => RSTP
    );
\delayMatch6_1_reg_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => Demux_out3(0),
      Q => \^delaymatch6_1_reg\(0),
      R => RSTP
    );
\delayMatch6_1_reg_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \^delaymatch6_1_reg\(0),
      Q => SSc_IN_External_2(0),
      R => RSTP
    );
\delayMatch8_reg_reg[2][0]_srl3___U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_1\: unisim.vcomponents.SRL16E
     port map (
      A0 => '0',
      A1 => '1',
      A2 => '0',
      A3 => '0',
      CE => CEP,
      CLK => IPCORE_CLK,
      D => \delayMatch8_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2_0\(0),
      Q => \delayMatch8_reg_reg[2][0]_srl3___U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_1_n_0\
    );
\delayMatch8_reg_reg[2][1]_srl3___U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_1\: unisim.vcomponents.SRL16E
     port map (
      A0 => '0',
      A1 => '1',
      A2 => '0',
      A3 => '0',
      CE => CEP,
      CLK => IPCORE_CLK,
      D => \delayMatch8_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2_0\(1),
      Q => \delayMatch8_reg_reg[2][1]_srl3___U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_1_n_0\
    );
\delayMatch8_reg_reg[3][0]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \delayMatch8_reg_reg[2][0]_srl3___U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_1_n_0\,
      Q => \delayMatch8_reg_reg[3][0]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2_n_0\,
      R => '0'
    );
\delayMatch8_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \delayMatch8_reg_reg[2][1]_srl3___U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_1_n_0\,
      Q => \delayMatch8_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2_n_0\,
      R => '0'
    );
\delayMatch8_reg_reg[4][0]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \delayMatch8_reg_reg_gate__0_n_0\,
      Q => \delayMatch8_reg_reg_n_0_[4][0]\,
      R => RSTP
    );
\delayMatch8_reg_reg[4][1]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => delayMatch8_reg_reg_gate_n_0,
      Q => \delayMatch8_reg_reg_n_0_[4][1]\,
      R => RSTP
    );
delayMatch8_reg_reg_gate: unisim.vcomponents.LUT2
    generic map(
      INIT => X"8"
    )
        port map (
      I0 => \delayMatch8_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2_n_0\,
      I1 => reduced_reg_reg_r_2_n_0,
      O => delayMatch8_reg_reg_gate_n_0
    );
\delayMatch8_reg_reg_gate__0\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"8"
    )
        port map (
      I0 => \delayMatch8_reg_reg[3][0]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2_n_0\,
      I1 => reduced_reg_reg_r_2_n_0,
      O => \delayMatch8_reg_reg_gate__0_n_0\
    );
\delayMatch_1_reg_1_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => Demux_out1(1),
      Q => \^delaymatch_1_reg_1\(0),
      R => RSTP
    );
\delayMatch_1_reg_1_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \^delaymatch_1_reg_1\(0),
      Q => SSa_IN_External_2(1),
      R => RSTP
    );
\delayMatch_1_reg_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => Demux_out1(0),
      Q => \^delaymatch_1_reg\(0),
      R => RSTP
    );
\delayMatch_1_reg_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \^delaymatch_1_reg\(0),
      Q => SSa_IN_External_2(0),
      R => RSTP
    );
\reduced_reg_reg[2][1]_srl3___U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_1\: unisim.vcomponents.SRL16E
     port map (
      A0 => '0',
      A1 => '1',
      A2 => '0',
      A3 => '0',
      CE => CEP,
      CLK => IPCORE_CLK,
      D => \reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2_0\(0),
      Q => \reduced_reg_reg[2][1]_srl3___U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_1_n_0\
    );
\reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \reduced_reg_reg[2][1]_srl3___U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_1_n_0\,
      Q => \reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2_n_0\,
      R => '0'
    );
\reduced_reg_reg[4][1]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => reduced_reg_reg_gate_n_0,
      Q => switch_compare_1,
      R => RSTP
    );
reduced_reg_reg_gate: unisim.vcomponents.LUT2
    generic map(
      INIT => X"8"
    )
        port map (
      I0 => \reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2_n_0\,
      I1 => reduced_reg_reg_r_2_n_0,
      O => reduced_reg_reg_gate_n_0
    );
reduced_reg_reg_r: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => '1',
      Q => reduced_reg_reg_r_n_0,
      R => RSTP
    );
reduced_reg_reg_r_0: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => reduced_reg_reg_r_n_0,
      Q => reduced_reg_reg_r_0_n_0,
      R => RSTP
    );
reduced_reg_reg_r_1: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => reduced_reg_reg_r_0_n_0,
      Q => reduced_reg_reg_r_1_n_0,
      R => RSTP
    );
reduced_reg_reg_r_2: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => reduced_reg_reg_r_1_n_0,
      Q => reduced_reg_reg_r_2_n_0,
      R => RSTP
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity zusys_PWM_SS_3L_ip_0_0_PWM_SS_3L_ip_src_Counter_Ctrl is
  port (
    Counter_Ctrl_out3 : out STD_LOGIC_VECTOR ( 20 downto 0 );
    CO : out STD_LOGIC_VECTOR ( 0 to 0 );
    O : out STD_LOGIC_VECTOR ( 7 downto 0 );
    \HDL_Counter2_count_reg[0]\ : out STD_LOGIC_VECTOR ( 7 downto 0 );
    \HDL_Counter2_count_reg[0]_0\ : out STD_LOGIC_VECTOR ( 3 downto 0 );
    RSTP : in STD_LOGIC;
    CEP : in STD_LOGIC;
    IPCORE_CLK : in STD_LOGIC;
    HDL_Counter2_count_reg : in STD_LOGIC_VECTOR ( 19 downto 0 );
    S : in STD_LOGIC_VECTOR ( 3 downto 0 );
    Counter_Ctrl_out4_1_reg : in STD_LOGIC_VECTOR ( 6 downto 0 );
    maximum_counter_value_1 : in STD_LOGIC_VECTOR ( 19 downto 0 )
  );
  attribute ORIG_REF_NAME : string;
  attribute ORIG_REF_NAME of zusys_PWM_SS_3L_ip_0_0_PWM_SS_3L_ip_src_Counter_Ctrl : entity is "PWM_SS_3L_ip_src_Counter_Ctrl";
end zusys_PWM_SS_3L_ip_0_0_PWM_SS_3L_ip_src_Counter_Ctrl;

architecture STRUCTURE of zusys_PWM_SS_3L_ip_0_0_PWM_SS_3L_ip_src_Counter_Ctrl is
  signal \Add1_out1_carry__0_i_1_n_0\ : STD_LOGIC;
  signal \Add1_out1_carry__0_i_2_n_0\ : STD_LOGIC;
  signal \Add1_out1_carry__0_i_3_n_0\ : STD_LOGIC;
  signal \Add1_out1_carry__0_i_4_n_0\ : STD_LOGIC;
  signal \Add1_out1_carry__0_i_5_n_0\ : STD_LOGIC;
  signal \Add1_out1_carry__0_i_6_n_0\ : STD_LOGIC;
  signal \Add1_out1_carry__0_i_7_n_0\ : STD_LOGIC;
  signal \Add1_out1_carry__0_i_8_n_0\ : STD_LOGIC;
  signal \Add1_out1_carry__0_n_0\ : STD_LOGIC;
  signal \Add1_out1_carry__0_n_1\ : STD_LOGIC;
  signal \Add1_out1_carry__0_n_2\ : STD_LOGIC;
  signal \Add1_out1_carry__0_n_3\ : STD_LOGIC;
  signal \Add1_out1_carry__0_n_4\ : STD_LOGIC;
  signal \Add1_out1_carry__0_n_5\ : STD_LOGIC;
  signal \Add1_out1_carry__0_n_6\ : STD_LOGIC;
  signal \Add1_out1_carry__0_n_7\ : STD_LOGIC;
  signal \Add1_out1_carry__1_n_4\ : STD_LOGIC;
  signal \Add1_out1_carry__1_n_5\ : STD_LOGIC;
  signal \Add1_out1_carry__1_n_6\ : STD_LOGIC;
  signal \Add1_out1_carry__1_n_7\ : STD_LOGIC;
  signal Add1_out1_carry_i_1_n_0 : STD_LOGIC;
  signal Add1_out1_carry_i_2_n_0 : STD_LOGIC;
  signal Add1_out1_carry_i_3_n_0 : STD_LOGIC;
  signal Add1_out1_carry_i_4_n_0 : STD_LOGIC;
  signal Add1_out1_carry_i_5_n_0 : STD_LOGIC;
  signal Add1_out1_carry_i_6_n_0 : STD_LOGIC;
  signal Add1_out1_carry_i_7_n_0 : STD_LOGIC;
  signal Add1_out1_carry_i_8_n_0 : STD_LOGIC;
  signal Add1_out1_carry_n_0 : STD_LOGIC;
  signal Add1_out1_carry_n_1 : STD_LOGIC;
  signal Add1_out1_carry_n_2 : STD_LOGIC;
  signal Add1_out1_carry_n_3 : STD_LOGIC;
  signal Add1_out1_carry_n_4 : STD_LOGIC;
  signal Add1_out1_carry_n_5 : STD_LOGIC;
  signal Add1_out1_carry_n_6 : STD_LOGIC;
  signal Add1_out1_carry_n_7 : STD_LOGIC;
  signal Delay6_out1 : STD_LOGIC;
  signal Delay6_out1_i_2_n_0 : STD_LOGIC;
  signal Delay6_out1_i_3_n_0 : STD_LOGIC;
  signal Delay6_out1_i_4_n_0 : STD_LOGIC;
  signal Delay6_out1_i_5_n_0 : STD_LOGIC;
  signal Delay6_out1_i_6_n_0 : STD_LOGIC;
  signal \HDL_Counter2_count[0]_i_10_n_0\ : STD_LOGIC;
  signal \HDL_Counter2_count[0]_i_11_n_0\ : STD_LOGIC;
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
  signal \HDL_Counter2_count_reg[0]_i_2_n_0\ : STD_LOGIC;
  signal \HDL_Counter2_count_reg[0]_i_2_n_1\ : STD_LOGIC;
  signal \HDL_Counter2_count_reg[0]_i_2_n_2\ : STD_LOGIC;
  signal \HDL_Counter2_count_reg[0]_i_2_n_3\ : STD_LOGIC;
  signal \HDL_Counter2_count_reg[0]_i_2_n_4\ : STD_LOGIC;
  signal \HDL_Counter2_count_reg[0]_i_2_n_5\ : STD_LOGIC;
  signal \HDL_Counter2_count_reg[0]_i_2_n_6\ : STD_LOGIC;
  signal \HDL_Counter2_count_reg[0]_i_2_n_7\ : STD_LOGIC;
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
  signal \Logical_Operator_out10_carry__0_i_1_n_0\ : STD_LOGIC;
  signal \Logical_Operator_out10_carry__0_i_2_n_0\ : STD_LOGIC;
  signal \Logical_Operator_out10_carry__0_i_3_n_0\ : STD_LOGIC;
  signal \Logical_Operator_out10_carry__0_i_4_n_0\ : STD_LOGIC;
  signal \Logical_Operator_out10_carry__0_n_7\ : STD_LOGIC;
  signal \Logical_Operator_out10_carry_i_10__2_n_0\ : STD_LOGIC;
  signal \Logical_Operator_out10_carry_i_11__2_n_0\ : STD_LOGIC;
  signal \Logical_Operator_out10_carry_i_12__2_n_0\ : STD_LOGIC;
  signal \Logical_Operator_out10_carry_i_13__2_n_0\ : STD_LOGIC;
  signal \Logical_Operator_out10_carry_i_14__2_n_0\ : STD_LOGIC;
  signal Logical_Operator_out10_carry_i_15_n_0 : STD_LOGIC;
  signal Logical_Operator_out10_carry_i_16_n_0 : STD_LOGIC;
  signal \Logical_Operator_out10_carry_i_1__2_n_0\ : STD_LOGIC;
  signal \Logical_Operator_out10_carry_i_2__2_n_0\ : STD_LOGIC;
  signal \Logical_Operator_out10_carry_i_3__2_n_0\ : STD_LOGIC;
  signal \Logical_Operator_out10_carry_i_4__2_n_0\ : STD_LOGIC;
  signal \Logical_Operator_out10_carry_i_5__2_n_0\ : STD_LOGIC;
  signal \Logical_Operator_out10_carry_i_6__2_n_0\ : STD_LOGIC;
  signal \Logical_Operator_out10_carry_i_7__2_n_0\ : STD_LOGIC;
  signal \Logical_Operator_out10_carry_i_8__2_n_0\ : STD_LOGIC;
  signal \Logical_Operator_out10_carry_i_9__2_n_0\ : STD_LOGIC;
  signal Logical_Operator_out10_carry_n_0 : STD_LOGIC;
  signal Logical_Operator_out10_carry_n_1 : STD_LOGIC;
  signal Logical_Operator_out10_carry_n_2 : STD_LOGIC;
  signal Logical_Operator_out10_carry_n_3 : STD_LOGIC;
  signal Logical_Operator_out10_carry_n_4 : STD_LOGIC;
  signal Logical_Operator_out10_carry_n_5 : STD_LOGIC;
  signal Logical_Operator_out10_carry_n_6 : STD_LOGIC;
  signal Logical_Operator_out10_carry_n_7 : STD_LOGIC;
  signal Period_Center0_carry_n_2 : STD_LOGIC;
  signal Period_Center0_carry_n_3 : STD_LOGIC;
  signal Period_Center0_carry_n_4 : STD_LOGIC;
  signal Period_Center0_carry_n_5 : STD_LOGIC;
  signal Period_Center0_carry_n_6 : STD_LOGIC;
  signal Period_Center0_carry_n_7 : STD_LOGIC;
  signal Relational_Operator4_relop1 : STD_LOGIC;
  signal direction_ctrl : STD_LOGIC;
  signal \NLW_Add1_out1_carry__1_CO_UNCONNECTED\ : STD_LOGIC_VECTOR ( 7 downto 4 );
  signal \NLW_Add1_out1_carry__1_O_UNCONNECTED\ : STD_LOGIC_VECTOR ( 7 downto 5 );
  signal \NLW_HDL_Counter2_count_reg[16]_i_1_CO_UNCONNECTED\ : STD_LOGIC_VECTOR ( 7 downto 3 );
  signal \NLW_HDL_Counter2_count_reg[16]_i_1_O_UNCONNECTED\ : STD_LOGIC_VECTOR ( 7 downto 4 );
  signal NLW_Logical_Operator_out10_carry_O_UNCONNECTED : STD_LOGIC_VECTOR ( 7 downto 0 );
  signal \NLW_Logical_Operator_out10_carry__0_CO_UNCONNECTED\ : STD_LOGIC_VECTOR ( 7 downto 2 );
  signal \NLW_Logical_Operator_out10_carry__0_O_UNCONNECTED\ : STD_LOGIC_VECTOR ( 7 downto 0 );
  signal NLW_Period_Center0_carry_CO_UNCONNECTED : STD_LOGIC_VECTOR ( 7 to 7 );
  signal NLW_Period_Center0_carry_O_UNCONNECTED : STD_LOGIC_VECTOR ( 7 downto 0 );
  attribute ADDER_THRESHOLD : integer;
  attribute ADDER_THRESHOLD of \HDL_Counter2_count_reg[0]_i_2\ : label is 16;
  attribute ADDER_THRESHOLD of \HDL_Counter2_count_reg[16]_i_1\ : label is 16;
  attribute ADDER_THRESHOLD of \HDL_Counter2_count_reg[8]_i_1\ : label is 16;
  attribute COMPARATOR_THRESHOLD : integer;
  attribute COMPARATOR_THRESHOLD of Logical_Operator_out10_carry : label is 11;
  attribute COMPARATOR_THRESHOLD of \Logical_Operator_out10_carry__0\ : label is 11;
begin
Add1_out1_carry: unisim.vcomponents.CARRY8
     port map (
      CI => '1',
      CI_TOP => '0',
      CO(7) => Add1_out1_carry_n_0,
      CO(6) => Add1_out1_carry_n_1,
      CO(5) => Add1_out1_carry_n_2,
      CO(4) => Add1_out1_carry_n_3,
      CO(3) => Add1_out1_carry_n_4,
      CO(2) => Add1_out1_carry_n_5,
      CO(1) => Add1_out1_carry_n_6,
      CO(0) => Add1_out1_carry_n_7,
      DI(7 downto 0) => HDL_Counter2_count_reg(7 downto 0),
      O(7 downto 0) => Counter_Ctrl_out3(7 downto 0),
      S(7) => Add1_out1_carry_i_1_n_0,
      S(6) => Add1_out1_carry_i_2_n_0,
      S(5) => Add1_out1_carry_i_3_n_0,
      S(4) => Add1_out1_carry_i_4_n_0,
      S(3) => Add1_out1_carry_i_5_n_0,
      S(2) => Add1_out1_carry_i_6_n_0,
      S(1) => Add1_out1_carry_i_7_n_0,
      S(0) => Add1_out1_carry_i_8_n_0
    );
\Add1_out1_carry__0\: unisim.vcomponents.CARRY8
     port map (
      CI => Add1_out1_carry_n_0,
      CI_TOP => '0',
      CO(7) => \Add1_out1_carry__0_n_0\,
      CO(6) => \Add1_out1_carry__0_n_1\,
      CO(5) => \Add1_out1_carry__0_n_2\,
      CO(4) => \Add1_out1_carry__0_n_3\,
      CO(3) => \Add1_out1_carry__0_n_4\,
      CO(2) => \Add1_out1_carry__0_n_5\,
      CO(1) => \Add1_out1_carry__0_n_6\,
      CO(0) => \Add1_out1_carry__0_n_7\,
      DI(7 downto 0) => HDL_Counter2_count_reg(15 downto 8),
      O(7 downto 0) => Counter_Ctrl_out3(15 downto 8),
      S(7) => \Add1_out1_carry__0_i_1_n_0\,
      S(6) => \Add1_out1_carry__0_i_2_n_0\,
      S(5) => \Add1_out1_carry__0_i_3_n_0\,
      S(4) => \Add1_out1_carry__0_i_4_n_0\,
      S(3) => \Add1_out1_carry__0_i_5_n_0\,
      S(2) => \Add1_out1_carry__0_i_6_n_0\,
      S(1) => \Add1_out1_carry__0_i_7_n_0\,
      S(0) => \Add1_out1_carry__0_i_8_n_0\
    );
\Add1_out1_carry__0_i_1\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"9"
    )
        port map (
      I0 => HDL_Counter2_count_reg(15),
      I1 => maximum_counter_value_1(15),
      O => \Add1_out1_carry__0_i_1_n_0\
    );
\Add1_out1_carry__0_i_2\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"9"
    )
        port map (
      I0 => HDL_Counter2_count_reg(14),
      I1 => maximum_counter_value_1(14),
      O => \Add1_out1_carry__0_i_2_n_0\
    );
\Add1_out1_carry__0_i_3\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"9"
    )
        port map (
      I0 => HDL_Counter2_count_reg(13),
      I1 => maximum_counter_value_1(13),
      O => \Add1_out1_carry__0_i_3_n_0\
    );
\Add1_out1_carry__0_i_4\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"9"
    )
        port map (
      I0 => HDL_Counter2_count_reg(12),
      I1 => maximum_counter_value_1(12),
      O => \Add1_out1_carry__0_i_4_n_0\
    );
\Add1_out1_carry__0_i_5\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"9"
    )
        port map (
      I0 => HDL_Counter2_count_reg(11),
      I1 => maximum_counter_value_1(11),
      O => \Add1_out1_carry__0_i_5_n_0\
    );
\Add1_out1_carry__0_i_6\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"9"
    )
        port map (
      I0 => HDL_Counter2_count_reg(10),
      I1 => maximum_counter_value_1(10),
      O => \Add1_out1_carry__0_i_6_n_0\
    );
\Add1_out1_carry__0_i_7\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"9"
    )
        port map (
      I0 => HDL_Counter2_count_reg(9),
      I1 => maximum_counter_value_1(9),
      O => \Add1_out1_carry__0_i_7_n_0\
    );
\Add1_out1_carry__0_i_8\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"9"
    )
        port map (
      I0 => HDL_Counter2_count_reg(8),
      I1 => maximum_counter_value_1(8),
      O => \Add1_out1_carry__0_i_8_n_0\
    );
\Add1_out1_carry__1\: unisim.vcomponents.CARRY8
     port map (
      CI => \Add1_out1_carry__0_n_0\,
      CI_TOP => '0',
      CO(7 downto 4) => \NLW_Add1_out1_carry__1_CO_UNCONNECTED\(7 downto 4),
      CO(3) => \Add1_out1_carry__1_n_4\,
      CO(2) => \Add1_out1_carry__1_n_5\,
      CO(1) => \Add1_out1_carry__1_n_6\,
      CO(0) => \Add1_out1_carry__1_n_7\,
      DI(7 downto 4) => B"0000",
      DI(3 downto 0) => HDL_Counter2_count_reg(19 downto 16),
      O(7 downto 5) => \NLW_Add1_out1_carry__1_O_UNCONNECTED\(7 downto 5),
      O(4 downto 0) => Counter_Ctrl_out3(20 downto 16),
      S(7 downto 4) => B"0001",
      S(3 downto 0) => S(3 downto 0)
    );
Add1_out1_carry_i_1: unisim.vcomponents.LUT2
    generic map(
      INIT => X"9"
    )
        port map (
      I0 => HDL_Counter2_count_reg(7),
      I1 => maximum_counter_value_1(7),
      O => Add1_out1_carry_i_1_n_0
    );
Add1_out1_carry_i_2: unisim.vcomponents.LUT2
    generic map(
      INIT => X"9"
    )
        port map (
      I0 => HDL_Counter2_count_reg(6),
      I1 => maximum_counter_value_1(6),
      O => Add1_out1_carry_i_2_n_0
    );
Add1_out1_carry_i_3: unisim.vcomponents.LUT2
    generic map(
      INIT => X"9"
    )
        port map (
      I0 => HDL_Counter2_count_reg(5),
      I1 => maximum_counter_value_1(5),
      O => Add1_out1_carry_i_3_n_0
    );
Add1_out1_carry_i_4: unisim.vcomponents.LUT2
    generic map(
      INIT => X"9"
    )
        port map (
      I0 => HDL_Counter2_count_reg(4),
      I1 => maximum_counter_value_1(4),
      O => Add1_out1_carry_i_4_n_0
    );
Add1_out1_carry_i_5: unisim.vcomponents.LUT2
    generic map(
      INIT => X"9"
    )
        port map (
      I0 => HDL_Counter2_count_reg(3),
      I1 => maximum_counter_value_1(3),
      O => Add1_out1_carry_i_5_n_0
    );
Add1_out1_carry_i_6: unisim.vcomponents.LUT2
    generic map(
      INIT => X"9"
    )
        port map (
      I0 => HDL_Counter2_count_reg(2),
      I1 => maximum_counter_value_1(2),
      O => Add1_out1_carry_i_6_n_0
    );
Add1_out1_carry_i_7: unisim.vcomponents.LUT2
    generic map(
      INIT => X"9"
    )
        port map (
      I0 => HDL_Counter2_count_reg(1),
      I1 => maximum_counter_value_1(1),
      O => Add1_out1_carry_i_7_n_0
    );
Add1_out1_carry_i_8: unisim.vcomponents.LUT2
    generic map(
      INIT => X"9"
    )
        port map (
      I0 => HDL_Counter2_count_reg(0),
      I1 => maximum_counter_value_1(0),
      O => Add1_out1_carry_i_8_n_0
    );
Delay6_out1_i_1: unisim.vcomponents.LUT5
    generic map(
      INIT => X"55550001"
    )
        port map (
      I0 => Relational_Operator4_relop1,
      I1 => Delay6_out1_i_2_n_0,
      I2 => Delay6_out1_i_3_n_0,
      I3 => HDL_Counter2_count_reg(0),
      I4 => Delay6_out1,
      O => direction_ctrl
    );
Delay6_out1_i_2: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFFFFFFE"
    )
        port map (
      I0 => HDL_Counter2_count_reg(13),
      I1 => HDL_Counter2_count_reg(10),
      I2 => HDL_Counter2_count_reg(15),
      I3 => HDL_Counter2_count_reg(12),
      I4 => Delay6_out1_i_4_n_0,
      O => Delay6_out1_i_2_n_0
    );
Delay6_out1_i_3: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFFFFFFE"
    )
        port map (
      I0 => HDL_Counter2_count_reg(3),
      I1 => HDL_Counter2_count_reg(2),
      I2 => HDL_Counter2_count_reg(18),
      I3 => Delay6_out1_i_5_n_0,
      I4 => Delay6_out1_i_6_n_0,
      O => Delay6_out1_i_3_n_0
    );
Delay6_out1_i_4: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FFFE"
    )
        port map (
      I0 => HDL_Counter2_count_reg(8),
      I1 => HDL_Counter2_count_reg(11),
      I2 => HDL_Counter2_count_reg(6),
      I3 => HDL_Counter2_count_reg(9),
      O => Delay6_out1_i_4_n_0
    );
Delay6_out1_i_5: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FFFE"
    )
        port map (
      I0 => HDL_Counter2_count_reg(4),
      I1 => HDL_Counter2_count_reg(7),
      I2 => HDL_Counter2_count_reg(1),
      I3 => HDL_Counter2_count_reg(5),
      O => Delay6_out1_i_5_n_0
    );
Delay6_out1_i_6: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FFFE"
    )
        port map (
      I0 => HDL_Counter2_count_reg(16),
      I1 => HDL_Counter2_count_reg(19),
      I2 => HDL_Counter2_count_reg(14),
      I3 => HDL_Counter2_count_reg(17),
      O => Delay6_out1_i_6_n_0
    );
Delay6_out1_reg: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => direction_ctrl,
      Q => Delay6_out1,
      R => RSTP
    );
\HDL_Counter2_count[0]_i_10\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"55550001AAAAFFFE"
    )
        port map (
      I0 => Relational_Operator4_relop1,
      I1 => Delay6_out1_i_2_n_0,
      I2 => Delay6_out1_i_3_n_0,
      I3 => HDL_Counter2_count_reg(0),
      I4 => Delay6_out1,
      I5 => HDL_Counter2_count_reg(1),
      O => \HDL_Counter2_count[0]_i_10_n_0\
    );
\HDL_Counter2_count[0]_i_11\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"AA55FF01"
    )
        port map (
      I0 => Relational_Operator4_relop1,
      I1 => Delay6_out1_i_2_n_0,
      I2 => Delay6_out1_i_3_n_0,
      I3 => HDL_Counter2_count_reg(0),
      I4 => Delay6_out1,
      O => \HDL_Counter2_count[0]_i_11_n_0\
    );
\HDL_Counter2_count[0]_i_3\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"AAAAFFFE"
    )
        port map (
      I0 => Relational_Operator4_relop1,
      I1 => Delay6_out1_i_2_n_0,
      I2 => Delay6_out1_i_3_n_0,
      I3 => HDL_Counter2_count_reg(0),
      I4 => Delay6_out1,
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
      I3 => HDL_Counter2_count_reg(0),
      I4 => Delay6_out1,
      I5 => HDL_Counter2_count_reg(7),
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
      I3 => HDL_Counter2_count_reg(0),
      I4 => Delay6_out1,
      I5 => HDL_Counter2_count_reg(6),
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
      I3 => HDL_Counter2_count_reg(0),
      I4 => Delay6_out1,
      I5 => HDL_Counter2_count_reg(5),
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
      I3 => HDL_Counter2_count_reg(0),
      I4 => Delay6_out1,
      I5 => HDL_Counter2_count_reg(4),
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
      I3 => HDL_Counter2_count_reg(0),
      I4 => Delay6_out1,
      I5 => HDL_Counter2_count_reg(3),
      O => \HDL_Counter2_count[0]_i_8_n_0\
    );
\HDL_Counter2_count[0]_i_9\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"55550001AAAAFFFE"
    )
        port map (
      I0 => Relational_Operator4_relop1,
      I1 => Delay6_out1_i_2_n_0,
      I2 => Delay6_out1_i_3_n_0,
      I3 => HDL_Counter2_count_reg(0),
      I4 => Delay6_out1,
      I5 => HDL_Counter2_count_reg(2),
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
      I3 => HDL_Counter2_count_reg(0),
      I4 => Delay6_out1,
      I5 => HDL_Counter2_count_reg(19),
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
      I3 => HDL_Counter2_count_reg(0),
      I4 => Delay6_out1,
      I5 => HDL_Counter2_count_reg(18),
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
      I3 => HDL_Counter2_count_reg(0),
      I4 => Delay6_out1,
      I5 => HDL_Counter2_count_reg(17),
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
      I3 => HDL_Counter2_count_reg(0),
      I4 => Delay6_out1,
      I5 => HDL_Counter2_count_reg(16),
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
      I3 => HDL_Counter2_count_reg(0),
      I4 => Delay6_out1,
      I5 => HDL_Counter2_count_reg(15),
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
      I3 => HDL_Counter2_count_reg(0),
      I4 => Delay6_out1,
      I5 => HDL_Counter2_count_reg(14),
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
      I3 => HDL_Counter2_count_reg(0),
      I4 => Delay6_out1,
      I5 => HDL_Counter2_count_reg(13),
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
      I3 => HDL_Counter2_count_reg(0),
      I4 => Delay6_out1,
      I5 => HDL_Counter2_count_reg(12),
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
      I3 => HDL_Counter2_count_reg(0),
      I4 => Delay6_out1,
      I5 => HDL_Counter2_count_reg(11),
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
      I3 => HDL_Counter2_count_reg(0),
      I4 => Delay6_out1,
      I5 => HDL_Counter2_count_reg(10),
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
      I3 => HDL_Counter2_count_reg(0),
      I4 => Delay6_out1,
      I5 => HDL_Counter2_count_reg(9),
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
      I3 => HDL_Counter2_count_reg(0),
      I4 => Delay6_out1,
      I5 => HDL_Counter2_count_reg(8),
      O => \HDL_Counter2_count[8]_i_9_n_0\
    );
\HDL_Counter2_count_reg[0]_i_2\: unisim.vcomponents.CARRY8
     port map (
      CI => \HDL_Counter2_count[0]_i_3_n_0\,
      CI_TOP => '0',
      CO(7) => \HDL_Counter2_count_reg[0]_i_2_n_0\,
      CO(6) => \HDL_Counter2_count_reg[0]_i_2_n_1\,
      CO(5) => \HDL_Counter2_count_reg[0]_i_2_n_2\,
      CO(4) => \HDL_Counter2_count_reg[0]_i_2_n_3\,
      CO(3) => \HDL_Counter2_count_reg[0]_i_2_n_4\,
      CO(2) => \HDL_Counter2_count_reg[0]_i_2_n_5\,
      CO(1) => \HDL_Counter2_count_reg[0]_i_2_n_6\,
      CO(0) => \HDL_Counter2_count_reg[0]_i_2_n_7\,
      DI(7) => \HDL_Counter2_count[0]_i_3_n_0\,
      DI(6) => \HDL_Counter2_count[0]_i_3_n_0\,
      DI(5) => \HDL_Counter2_count[0]_i_3_n_0\,
      DI(4) => \HDL_Counter2_count[0]_i_3_n_0\,
      DI(3) => \HDL_Counter2_count[0]_i_3_n_0\,
      DI(2) => \HDL_Counter2_count[0]_i_3_n_0\,
      DI(1) => \HDL_Counter2_count[0]_i_3_n_0\,
      DI(0) => HDL_Counter2_count_reg(0),
      O(7 downto 0) => O(7 downto 0),
      S(7) => \HDL_Counter2_count[0]_i_4_n_0\,
      S(6) => \HDL_Counter2_count[0]_i_5_n_0\,
      S(5) => \HDL_Counter2_count[0]_i_6_n_0\,
      S(4) => \HDL_Counter2_count[0]_i_7_n_0\,
      S(3) => \HDL_Counter2_count[0]_i_8_n_0\,
      S(2) => \HDL_Counter2_count[0]_i_9_n_0\,
      S(1) => \HDL_Counter2_count[0]_i_10_n_0\,
      S(0) => \HDL_Counter2_count[0]_i_11_n_0\
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
      DI(2) => \HDL_Counter2_count[0]_i_3_n_0\,
      DI(1) => \HDL_Counter2_count[0]_i_3_n_0\,
      DI(0) => \HDL_Counter2_count[0]_i_3_n_0\,
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
      CI => \HDL_Counter2_count_reg[0]_i_2_n_0\,
      CI_TOP => '0',
      CO(7) => \HDL_Counter2_count_reg[8]_i_1_n_0\,
      CO(6) => \HDL_Counter2_count_reg[8]_i_1_n_1\,
      CO(5) => \HDL_Counter2_count_reg[8]_i_1_n_2\,
      CO(4) => \HDL_Counter2_count_reg[8]_i_1_n_3\,
      CO(3) => \HDL_Counter2_count_reg[8]_i_1_n_4\,
      CO(2) => \HDL_Counter2_count_reg[8]_i_1_n_5\,
      CO(1) => \HDL_Counter2_count_reg[8]_i_1_n_6\,
      CO(0) => \HDL_Counter2_count_reg[8]_i_1_n_7\,
      DI(7) => \HDL_Counter2_count[0]_i_3_n_0\,
      DI(6) => \HDL_Counter2_count[0]_i_3_n_0\,
      DI(5) => \HDL_Counter2_count[0]_i_3_n_0\,
      DI(4) => \HDL_Counter2_count[0]_i_3_n_0\,
      DI(3) => \HDL_Counter2_count[0]_i_3_n_0\,
      DI(2) => \HDL_Counter2_count[0]_i_3_n_0\,
      DI(1) => \HDL_Counter2_count[0]_i_3_n_0\,
      DI(0) => \HDL_Counter2_count[0]_i_3_n_0\,
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
      DI(7) => \Logical_Operator_out10_carry_i_1__2_n_0\,
      DI(6) => \Logical_Operator_out10_carry_i_2__2_n_0\,
      DI(5) => \Logical_Operator_out10_carry_i_3__2_n_0\,
      DI(4) => \Logical_Operator_out10_carry_i_4__2_n_0\,
      DI(3) => \Logical_Operator_out10_carry_i_5__2_n_0\,
      DI(2) => \Logical_Operator_out10_carry_i_6__2_n_0\,
      DI(1) => \Logical_Operator_out10_carry_i_7__2_n_0\,
      DI(0) => \Logical_Operator_out10_carry_i_8__2_n_0\,
      O(7 downto 0) => NLW_Logical_Operator_out10_carry_O_UNCONNECTED(7 downto 0),
      S(7) => \Logical_Operator_out10_carry_i_9__2_n_0\,
      S(6) => \Logical_Operator_out10_carry_i_10__2_n_0\,
      S(5) => \Logical_Operator_out10_carry_i_11__2_n_0\,
      S(4) => \Logical_Operator_out10_carry_i_12__2_n_0\,
      S(3) => \Logical_Operator_out10_carry_i_13__2_n_0\,
      S(2) => \Logical_Operator_out10_carry_i_14__2_n_0\,
      S(1) => Logical_Operator_out10_carry_i_15_n_0,
      S(0) => Logical_Operator_out10_carry_i_16_n_0
    );
\Logical_Operator_out10_carry__0\: unisim.vcomponents.CARRY8
     port map (
      CI => Logical_Operator_out10_carry_n_0,
      CI_TOP => '0',
      CO(7 downto 2) => \NLW_Logical_Operator_out10_carry__0_CO_UNCONNECTED\(7 downto 2),
      CO(1) => Relational_Operator4_relop1,
      CO(0) => \Logical_Operator_out10_carry__0_n_7\,
      DI(7 downto 2) => B"000000",
      DI(1) => \Logical_Operator_out10_carry__0_i_1_n_0\,
      DI(0) => \Logical_Operator_out10_carry__0_i_2_n_0\,
      O(7 downto 0) => \NLW_Logical_Operator_out10_carry__0_O_UNCONNECTED\(7 downto 0),
      S(7 downto 2) => B"000000",
      S(1) => \Logical_Operator_out10_carry__0_i_3_n_0\,
      S(0) => \Logical_Operator_out10_carry__0_i_4_n_0\
    );
\Logical_Operator_out10_carry__0_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"22B2"
    )
        port map (
      I0 => HDL_Counter2_count_reg(19),
      I1 => maximum_counter_value_1(19),
      I2 => HDL_Counter2_count_reg(18),
      I3 => maximum_counter_value_1(18),
      O => \Logical_Operator_out10_carry__0_i_1_n_0\
    );
\Logical_Operator_out10_carry__0_i_2\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"22B2"
    )
        port map (
      I0 => HDL_Counter2_count_reg(17),
      I1 => maximum_counter_value_1(17),
      I2 => HDL_Counter2_count_reg(16),
      I3 => maximum_counter_value_1(16),
      O => \Logical_Operator_out10_carry__0_i_2_n_0\
    );
\Logical_Operator_out10_carry__0_i_3\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"9009"
    )
        port map (
      I0 => HDL_Counter2_count_reg(18),
      I1 => maximum_counter_value_1(18),
      I2 => HDL_Counter2_count_reg(19),
      I3 => maximum_counter_value_1(19),
      O => \Logical_Operator_out10_carry__0_i_3_n_0\
    );
\Logical_Operator_out10_carry__0_i_4\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"9009"
    )
        port map (
      I0 => HDL_Counter2_count_reg(16),
      I1 => maximum_counter_value_1(16),
      I2 => HDL_Counter2_count_reg(17),
      I3 => maximum_counter_value_1(17),
      O => \Logical_Operator_out10_carry__0_i_4_n_0\
    );
\Logical_Operator_out10_carry_i_10__2\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"9009"
    )
        port map (
      I0 => HDL_Counter2_count_reg(12),
      I1 => maximum_counter_value_1(12),
      I2 => HDL_Counter2_count_reg(13),
      I3 => maximum_counter_value_1(13),
      O => \Logical_Operator_out10_carry_i_10__2_n_0\
    );
\Logical_Operator_out10_carry_i_11__2\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"9009"
    )
        port map (
      I0 => HDL_Counter2_count_reg(10),
      I1 => maximum_counter_value_1(10),
      I2 => HDL_Counter2_count_reg(11),
      I3 => maximum_counter_value_1(11),
      O => \Logical_Operator_out10_carry_i_11__2_n_0\
    );
\Logical_Operator_out10_carry_i_12__2\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"9009"
    )
        port map (
      I0 => HDL_Counter2_count_reg(9),
      I1 => maximum_counter_value_1(9),
      I2 => HDL_Counter2_count_reg(8),
      I3 => maximum_counter_value_1(8),
      O => \Logical_Operator_out10_carry_i_12__2_n_0\
    );
\Logical_Operator_out10_carry_i_13__2\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"9009"
    )
        port map (
      I0 => HDL_Counter2_count_reg(6),
      I1 => maximum_counter_value_1(6),
      I2 => HDL_Counter2_count_reg(7),
      I3 => maximum_counter_value_1(7),
      O => \Logical_Operator_out10_carry_i_13__2_n_0\
    );
\Logical_Operator_out10_carry_i_14__2\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"9009"
    )
        port map (
      I0 => HDL_Counter2_count_reg(4),
      I1 => maximum_counter_value_1(4),
      I2 => HDL_Counter2_count_reg(5),
      I3 => maximum_counter_value_1(5),
      O => \Logical_Operator_out10_carry_i_14__2_n_0\
    );
Logical_Operator_out10_carry_i_15: unisim.vcomponents.LUT4
    generic map(
      INIT => X"9009"
    )
        port map (
      I0 => HDL_Counter2_count_reg(3),
      I1 => maximum_counter_value_1(3),
      I2 => HDL_Counter2_count_reg(2),
      I3 => maximum_counter_value_1(2),
      O => Logical_Operator_out10_carry_i_15_n_0
    );
Logical_Operator_out10_carry_i_16: unisim.vcomponents.LUT4
    generic map(
      INIT => X"9009"
    )
        port map (
      I0 => HDL_Counter2_count_reg(0),
      I1 => maximum_counter_value_1(0),
      I2 => HDL_Counter2_count_reg(1),
      I3 => maximum_counter_value_1(1),
      O => Logical_Operator_out10_carry_i_16_n_0
    );
\Logical_Operator_out10_carry_i_1__2\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"22B2"
    )
        port map (
      I0 => HDL_Counter2_count_reg(15),
      I1 => maximum_counter_value_1(15),
      I2 => HDL_Counter2_count_reg(14),
      I3 => maximum_counter_value_1(14),
      O => \Logical_Operator_out10_carry_i_1__2_n_0\
    );
\Logical_Operator_out10_carry_i_2__2\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"22B2"
    )
        port map (
      I0 => HDL_Counter2_count_reg(13),
      I1 => maximum_counter_value_1(13),
      I2 => HDL_Counter2_count_reg(12),
      I3 => maximum_counter_value_1(12),
      O => \Logical_Operator_out10_carry_i_2__2_n_0\
    );
\Logical_Operator_out10_carry_i_3__2\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"22B2"
    )
        port map (
      I0 => HDL_Counter2_count_reg(11),
      I1 => maximum_counter_value_1(11),
      I2 => HDL_Counter2_count_reg(10),
      I3 => maximum_counter_value_1(10),
      O => \Logical_Operator_out10_carry_i_3__2_n_0\
    );
\Logical_Operator_out10_carry_i_4__2\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"22B2"
    )
        port map (
      I0 => HDL_Counter2_count_reg(9),
      I1 => maximum_counter_value_1(9),
      I2 => HDL_Counter2_count_reg(8),
      I3 => maximum_counter_value_1(8),
      O => \Logical_Operator_out10_carry_i_4__2_n_0\
    );
\Logical_Operator_out10_carry_i_5__2\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"22B2"
    )
        port map (
      I0 => HDL_Counter2_count_reg(7),
      I1 => maximum_counter_value_1(7),
      I2 => HDL_Counter2_count_reg(6),
      I3 => maximum_counter_value_1(6),
      O => \Logical_Operator_out10_carry_i_5__2_n_0\
    );
\Logical_Operator_out10_carry_i_6__2\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"22B2"
    )
        port map (
      I0 => HDL_Counter2_count_reg(5),
      I1 => maximum_counter_value_1(5),
      I2 => HDL_Counter2_count_reg(4),
      I3 => maximum_counter_value_1(4),
      O => \Logical_Operator_out10_carry_i_6__2_n_0\
    );
\Logical_Operator_out10_carry_i_7__2\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"22B2"
    )
        port map (
      I0 => HDL_Counter2_count_reg(3),
      I1 => maximum_counter_value_1(3),
      I2 => HDL_Counter2_count_reg(2),
      I3 => maximum_counter_value_1(2),
      O => \Logical_Operator_out10_carry_i_7__2_n_0\
    );
\Logical_Operator_out10_carry_i_8__2\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"22B2"
    )
        port map (
      I0 => HDL_Counter2_count_reg(1),
      I1 => maximum_counter_value_1(1),
      I2 => HDL_Counter2_count_reg(0),
      I3 => maximum_counter_value_1(0),
      O => \Logical_Operator_out10_carry_i_8__2_n_0\
    );
\Logical_Operator_out10_carry_i_9__2\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"9009"
    )
        port map (
      I0 => HDL_Counter2_count_reg(15),
      I1 => maximum_counter_value_1(15),
      I2 => HDL_Counter2_count_reg(14),
      I3 => maximum_counter_value_1(14),
      O => \Logical_Operator_out10_carry_i_9__2_n_0\
    );
Period_Center0_carry: unisim.vcomponents.CARRY8
     port map (
      CI => '1',
      CI_TOP => '0',
      CO(7) => NLW_Period_Center0_carry_CO_UNCONNECTED(7),
      CO(6) => CO(0),
      CO(5) => Period_Center0_carry_n_2,
      CO(4) => Period_Center0_carry_n_3,
      CO(3) => Period_Center0_carry_n_4,
      CO(2) => Period_Center0_carry_n_5,
      CO(1) => Period_Center0_carry_n_6,
      CO(0) => Period_Center0_carry_n_7,
      DI(7 downto 0) => B"00000000",
      O(7 downto 0) => NLW_Period_Center0_carry_O_UNCONNECTED(7 downto 0),
      S(7) => '0',
      S(6 downto 0) => Counter_Ctrl_out4_1_reg(6 downto 0)
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity zusys_PWM_SS_3L_ip_0_0_PWM_SS_3L_ip_src_LimitPulseWidth_a is
  port (
    \min_pulse_width_AXI_1_reg[4]\ : out STD_LOGIC;
    \delayMatch1_reg_reg[1][13]\ : out STD_LOGIC;
    \OR_out1__0\ : out STD_LOGIC;
    B : out STD_LOGIC_VECTOR ( 13 downto 0 );
    HDL_Counter2_count_reg_11_sp_1 : out STD_LOGIC;
    \delayMatch1_reg_reg[1][11]\ : out STD_LOGIC;
    \delayMatch1_reg_reg[1][9]\ : out STD_LOGIC;
    \delayMatch1_reg_reg[1][7]\ : out STD_LOGIC;
    \delayMatch1_reg_reg[1][5]\ : out STD_LOGIC;
    \delayMatch1_reg_reg[1][3]\ : out STD_LOGIC;
    \delayMatch1_reg_reg[1][1]\ : out STD_LOGIC;
    \HDL_Counter2_count_reg[11]_0\ : out STD_LOGIC;
    \min_pulse_width_AXI_1_reg[0]\ : out STD_LOGIC;
    \min_pulse_width_AXI_1_reg[5]\ : out STD_LOGIC;
    \min_pulse_width_AXI_1_reg[8]\ : out STD_LOGIC;
    \min_pulse_width_AXI_1_reg[9]\ : out STD_LOGIC;
    \min_pulse_width_AXI_1_reg[10]\ : out STD_LOGIC;
    RSTP : in STD_LOGIC;
    CEP : in STD_LOGIC;
    IPCORE_CLK : in STD_LOGIC;
    Q : in STD_LOGIC_VECTOR ( 13 downto 0 );
    \minus_out1_1_reg[12]_0\ : in STD_LOGIC;
    \Delay_out1_reg[13]\ : in STD_LOGIC_VECTOR ( 13 downto 0 );
    \Delay_out1_reg[13]_0\ : in STD_LOGIC_VECTOR ( 13 downto 0 );
    D : in STD_LOGIC_VECTOR ( 0 to 0 );
    HDL_Counter2_count_reg : in STD_LOGIC_VECTOR ( 11 downto 0 );
    CO : in STD_LOGIC_VECTOR ( 0 to 0 );
    \Delay_out1_reg[0]\ : in STD_LOGIC;
    \Delay_out1_reg[0]_0\ : in STD_LOGIC;
    \Delay_out1_reg[13]_1\ : in STD_LOGIC;
    \Delay_out1_reg[13]_2\ : in STD_LOGIC;
    \Delay_out1_reg[13]_3\ : in STD_LOGIC
  );
  attribute ORIG_REF_NAME : string;
  attribute ORIG_REF_NAME of zusys_PWM_SS_3L_ip_0_0_PWM_SS_3L_ip_src_LimitPulseWidth_a : entity is "PWM_SS_3L_ip_src_LimitPulseWidth_a";
end zusys_PWM_SS_3L_ip_0_0_PWM_SS_3L_ip_src_LimitPulseWidth_a;

architecture STRUCTURE of zusys_PWM_SS_3L_ip_0_0_PWM_SS_3L_ip_src_LimitPulseWidth_a is
  signal Add1_out1 : STD_LOGIC_VECTOR ( 13 downto 11 );
  signal Add1_out1_1 : STD_LOGIC_VECTOR ( 13 downto 0 );
  signal \Add1_out1_1[13]_i_2_n_0\ : STD_LOGIC;
  signal \Add1_out1_1[13]_i_3__1_n_0\ : STD_LOGIC;
  signal \Add1_out1_1[13]_i_4_n_0\ : STD_LOGIC;
  signal \Add1_out1_1_reg[13]_i_1_n_6\ : STD_LOGIC;
  signal \Add1_out1_1_reg[13]_i_1_n_7\ : STD_LOGIC;
  signal Add2_out1 : STD_LOGIC_VECTOR ( 13 downto 1 );
  signal Add2_out1_1 : STD_LOGIC_VECTOR ( 13 downto 1 );
  signal \Add2_out1_1[13]_i_2_n_0\ : STD_LOGIC;
  signal \Add2_out1_1[13]_i_3_n_0\ : STD_LOGIC;
  signal \Add2_out1_1[13]_i_4_n_0\ : STD_LOGIC;
  signal \Add2_out1_1[13]_i_5_n_0\ : STD_LOGIC;
  signal \Add2_out1_1[8]_i_10_n_0\ : STD_LOGIC;
  signal \Add2_out1_1[8]_i_2_n_0\ : STD_LOGIC;
  signal \Add2_out1_1[8]_i_3_n_0\ : STD_LOGIC;
  signal \Add2_out1_1[8]_i_4_n_0\ : STD_LOGIC;
  signal \Add2_out1_1[8]_i_5_n_0\ : STD_LOGIC;
  signal \Add2_out1_1[8]_i_6_n_0\ : STD_LOGIC;
  signal \Add2_out1_1[8]_i_7_n_0\ : STD_LOGIC;
  signal \Add2_out1_1[8]_i_8_n_0\ : STD_LOGIC;
  signal \Add2_out1_1[8]_i_9_n_0\ : STD_LOGIC;
  signal \Add2_out1_1_reg[13]_i_1_n_4\ : STD_LOGIC;
  signal \Add2_out1_1_reg[13]_i_1_n_5\ : STD_LOGIC;
  signal \Add2_out1_1_reg[13]_i_1_n_6\ : STD_LOGIC;
  signal \Add2_out1_1_reg[13]_i_1_n_7\ : STD_LOGIC;
  signal \Add2_out1_1_reg[8]_i_1_n_0\ : STD_LOGIC;
  signal \Add2_out1_1_reg[8]_i_1_n_1\ : STD_LOGIC;
  signal \Add2_out1_1_reg[8]_i_1_n_2\ : STD_LOGIC;
  signal \Add2_out1_1_reg[8]_i_1_n_3\ : STD_LOGIC;
  signal \Add2_out1_1_reg[8]_i_1_n_4\ : STD_LOGIC;
  signal \Add2_out1_1_reg[8]_i_1_n_5\ : STD_LOGIC;
  signal \Add2_out1_1_reg[8]_i_1_n_6\ : STD_LOGIC;
  signal \Add2_out1_1_reg[8]_i_1_n_7\ : STD_LOGIC;
  signal \Delay_out1[13]_i_3_n_0\ : STD_LOGIC;
  signal \Delay_out1[13]_i_4_n_0\ : STD_LOGIC;
  signal \^hdl_counter2_count_reg[11]_0\ : STD_LOGIC;
  signal HDL_Counter2_count_reg_11_sn_1 : STD_LOGIC;
  signal \Logical_Operator1_out10_carry_i_10__1_n_0\ : STD_LOGIC;
  signal \Logical_Operator1_out10_carry_i_11__1_n_0\ : STD_LOGIC;
  signal \Logical_Operator1_out10_carry_i_12__1_n_0\ : STD_LOGIC;
  signal \Logical_Operator1_out10_carry_i_13__1_n_0\ : STD_LOGIC;
  signal \Logical_Operator1_out10_carry_i_14__1_n_0\ : STD_LOGIC;
  signal \Logical_Operator1_out10_carry_i_1__1_n_0\ : STD_LOGIC;
  signal \Logical_Operator1_out10_carry_i_2__1_n_0\ : STD_LOGIC;
  signal \Logical_Operator1_out10_carry_i_3__1_n_0\ : STD_LOGIC;
  signal \Logical_Operator1_out10_carry_i_4__1_n_0\ : STD_LOGIC;
  signal \Logical_Operator1_out10_carry_i_5__1_n_0\ : STD_LOGIC;
  signal \Logical_Operator1_out10_carry_i_6__1_n_0\ : STD_LOGIC;
  signal \Logical_Operator1_out10_carry_i_7__1_n_0\ : STD_LOGIC;
  signal \Logical_Operator1_out10_carry_i_8__1_n_0\ : STD_LOGIC;
  signal \Logical_Operator1_out10_carry_i_9__1_n_0\ : STD_LOGIC;
  signal Logical_Operator1_out10_carry_n_2 : STD_LOGIC;
  signal Logical_Operator1_out10_carry_n_3 : STD_LOGIC;
  signal Logical_Operator1_out10_carry_n_4 : STD_LOGIC;
  signal Logical_Operator1_out10_carry_n_5 : STD_LOGIC;
  signal Logical_Operator1_out10_carry_n_6 : STD_LOGIC;
  signal Logical_Operator1_out10_carry_n_7 : STD_LOGIC;
  signal \Logical_Operator1_out10_inferred__0/i__carry_n_2\ : STD_LOGIC;
  signal \Logical_Operator1_out10_inferred__0/i__carry_n_3\ : STD_LOGIC;
  signal \Logical_Operator1_out10_inferred__0/i__carry_n_4\ : STD_LOGIC;
  signal \Logical_Operator1_out10_inferred__0/i__carry_n_5\ : STD_LOGIC;
  signal \Logical_Operator1_out10_inferred__0/i__carry_n_6\ : STD_LOGIC;
  signal \Logical_Operator1_out10_inferred__0/i__carry_n_7\ : STD_LOGIC;
  signal \Logical_Operator_out10_carry_i_10__1_n_0\ : STD_LOGIC;
  signal \Logical_Operator_out10_carry_i_11__1_n_0\ : STD_LOGIC;
  signal \Logical_Operator_out10_carry_i_12__1_n_0\ : STD_LOGIC;
  signal \Logical_Operator_out10_carry_i_13__1_n_0\ : STD_LOGIC;
  signal \Logical_Operator_out10_carry_i_14__1_n_0\ : STD_LOGIC;
  signal \Logical_Operator_out10_carry_i_1__1_n_0\ : STD_LOGIC;
  signal \Logical_Operator_out10_carry_i_2__1_n_0\ : STD_LOGIC;
  signal \Logical_Operator_out10_carry_i_3__1_n_0\ : STD_LOGIC;
  signal \Logical_Operator_out10_carry_i_4__1_n_0\ : STD_LOGIC;
  signal \Logical_Operator_out10_carry_i_5__1_n_0\ : STD_LOGIC;
  signal \Logical_Operator_out10_carry_i_6__1_n_0\ : STD_LOGIC;
  signal \Logical_Operator_out10_carry_i_7__1_n_0\ : STD_LOGIC;
  signal \Logical_Operator_out10_carry_i_8__1_n_0\ : STD_LOGIC;
  signal \Logical_Operator_out10_carry_i_9__1_n_0\ : STD_LOGIC;
  signal Logical_Operator_out10_carry_n_2 : STD_LOGIC;
  signal Logical_Operator_out10_carry_n_3 : STD_LOGIC;
  signal Logical_Operator_out10_carry_n_4 : STD_LOGIC;
  signal Logical_Operator_out10_carry_n_5 : STD_LOGIC;
  signal Logical_Operator_out10_carry_n_6 : STD_LOGIC;
  signal Logical_Operator_out10_carry_n_7 : STD_LOGIC;
  signal \Logical_Operator_out11_carry_i_1__1_n_0\ : STD_LOGIC;
  signal \Logical_Operator_out11_carry_i_2__1_n_0\ : STD_LOGIC;
  signal \Logical_Operator_out11_carry_i_3__1_n_0\ : STD_LOGIC;
  signal \Logical_Operator_out11_carry_i_4__1_n_0\ : STD_LOGIC;
  signal \Logical_Operator_out11_carry_i_5__1_n_0\ : STD_LOGIC;
  signal \Logical_Operator_out11_carry_i_6__1_n_0\ : STD_LOGIC;
  signal \Logical_Operator_out11_carry_i_7__1_n_0\ : STD_LOGIC;
  signal \Logical_Operator_out11_carry_i_8__1_n_0\ : STD_LOGIC;
  signal \Logical_Operator_out11_carry_i_9__1_n_0\ : STD_LOGIC;
  signal Logical_Operator_out11_carry_n_2 : STD_LOGIC;
  signal Logical_Operator_out11_carry_n_3 : STD_LOGIC;
  signal Logical_Operator_out11_carry_n_4 : STD_LOGIC;
  signal Logical_Operator_out11_carry_n_5 : STD_LOGIC;
  signal Logical_Operator_out11_carry_n_6 : STD_LOGIC;
  signal Logical_Operator_out11_carry_n_7 : STD_LOGIC;
  signal \Logical_Operator_out1__1\ : STD_LOGIC;
  signal \^or_out1__0\ : STD_LOGIC;
  signal Relational_Operator1_relop1 : STD_LOGIC;
  signal Relational_Operator2_relop1 : STD_LOGIC;
  signal Relational_Operator3_relop1 : STD_LOGIC;
  signal Relational_Operator_relop1 : STD_LOGIC;
  signal Saturation1_out1 : STD_LOGIC_VECTOR ( 12 downto 0 );
  signal Saturation1_out110_in : STD_LOGIC;
  signal Saturation1_out1_1 : STD_LOGIC_VECTOR ( 12 downto 11 );
  signal \^delaymatch1_reg_reg[1][11]\ : STD_LOGIC;
  signal \^delaymatch1_reg_reg[1][13]\ : STD_LOGIC;
  signal \^delaymatch1_reg_reg[1][1]\ : STD_LOGIC;
  signal \^delaymatch1_reg_reg[1][3]\ : STD_LOGIC;
  signal \^delaymatch1_reg_reg[1][5]\ : STD_LOGIC;
  signal \^delaymatch1_reg_reg[1][7]\ : STD_LOGIC;
  signal \^delaymatch1_reg_reg[1][9]\ : STD_LOGIC;
  signal \i__carry_i_10_n_0\ : STD_LOGIC;
  signal \i__carry_i_11_n_0\ : STD_LOGIC;
  signal \i__carry_i_12_n_0\ : STD_LOGIC;
  signal \i__carry_i_13_n_0\ : STD_LOGIC;
  signal \i__carry_i_14_n_0\ : STD_LOGIC;
  signal \i__carry_i_1__1_n_0\ : STD_LOGIC;
  signal \i__carry_i_2__1_n_0\ : STD_LOGIC;
  signal \i__carry_i_3__1_n_0\ : STD_LOGIC;
  signal \i__carry_i_4__1_n_0\ : STD_LOGIC;
  signal \i__carry_i_5__1_n_0\ : STD_LOGIC;
  signal \i__carry_i_6__1_n_0\ : STD_LOGIC;
  signal \i__carry_i_7__1_n_0\ : STD_LOGIC;
  signal \i__carry_i_8__1_n_0\ : STD_LOGIC;
  signal \i__carry_i_9__1_n_0\ : STD_LOGIC;
  signal \^min_pulse_width_axi_1_reg[0]\ : STD_LOGIC;
  signal \^min_pulse_width_axi_1_reg[10]\ : STD_LOGIC;
  signal \^min_pulse_width_axi_1_reg[4]\ : STD_LOGIC;
  signal \^min_pulse_width_axi_1_reg[5]\ : STD_LOGIC;
  signal \^min_pulse_width_axi_1_reg[8]\ : STD_LOGIC;
  signal \^min_pulse_width_axi_1_reg[9]\ : STD_LOGIC;
  signal minus_out1 : STD_LOGIC_VECTOR ( 13 downto 1 );
  signal minus_out1_1 : STD_LOGIC_VECTOR ( 13 downto 1 );
  signal \minus_out1_1[11]_i_3_n_0\ : STD_LOGIC;
  signal \minus_out1_1[13]_i_10__0_n_0\ : STD_LOGIC;
  signal \minus_out1_1[13]_i_11__0_n_0\ : STD_LOGIC;
  signal \minus_out1_1[13]_i_12__0_n_0\ : STD_LOGIC;
  signal \minus_out1_1[13]_i_13__0_n_0\ : STD_LOGIC;
  signal \minus_out1_1[13]_i_14__0_n_0\ : STD_LOGIC;
  signal \minus_out1_1[13]_i_15__1_n_0\ : STD_LOGIC;
  signal \minus_out1_1[13]_i_16_n_0\ : STD_LOGIC;
  signal \minus_out1_1[13]_i_4__0_n_0\ : STD_LOGIC;
  signal \minus_out1_1[13]_i_5__0_n_0\ : STD_LOGIC;
  signal \minus_out1_1[13]_i_6__0_n_0\ : STD_LOGIC;
  signal \minus_out1_1[13]_i_7__0_n_0\ : STD_LOGIC;
  signal \minus_out1_1[13]_i_8_n_0\ : STD_LOGIC;
  signal \minus_out1_1[13]_i_9_n_0\ : STD_LOGIC;
  signal \minus_out1_1[5]_i_3_n_0\ : STD_LOGIC;
  signal \minus_out1_1_reg[13]_i_3_n_2\ : STD_LOGIC;
  signal \minus_out1_1_reg[13]_i_3_n_3\ : STD_LOGIC;
  signal \minus_out1_1_reg[13]_i_3_n_4\ : STD_LOGIC;
  signal \minus_out1_1_reg[13]_i_3_n_5\ : STD_LOGIC;
  signal \minus_out1_1_reg[13]_i_3_n_6\ : STD_LOGIC;
  signal \minus_out1_1_reg[13]_i_3_n_7\ : STD_LOGIC;
  signal modulating_signal_in_clock_cycles_1_reg_i_17_n_0 : STD_LOGIC;
  signal modulating_signal_in_clock_cycles_1_reg_i_18_n_0 : STD_LOGIC;
  signal \NLW_Add1_out1_1_reg[13]_i_1_CO_UNCONNECTED\ : STD_LOGIC_VECTOR ( 7 downto 2 );
  signal \NLW_Add1_out1_1_reg[13]_i_1_O_UNCONNECTED\ : STD_LOGIC_VECTOR ( 7 downto 3 );
  signal \NLW_Add2_out1_1_reg[13]_i_1_CO_UNCONNECTED\ : STD_LOGIC_VECTOR ( 7 downto 4 );
  signal \NLW_Add2_out1_1_reg[13]_i_1_O_UNCONNECTED\ : STD_LOGIC_VECTOR ( 7 downto 5 );
  signal NLW_Logical_Operator1_out10_carry_CO_UNCONNECTED : STD_LOGIC_VECTOR ( 7 to 7 );
  signal NLW_Logical_Operator1_out10_carry_O_UNCONNECTED : STD_LOGIC_VECTOR ( 7 downto 0 );
  signal \NLW_Logical_Operator1_out10_inferred__0/i__carry_CO_UNCONNECTED\ : STD_LOGIC_VECTOR ( 7 to 7 );
  signal \NLW_Logical_Operator1_out10_inferred__0/i__carry_O_UNCONNECTED\ : STD_LOGIC_VECTOR ( 7 downto 0 );
  signal NLW_Logical_Operator_out10_carry_CO_UNCONNECTED : STD_LOGIC_VECTOR ( 7 to 7 );
  signal NLW_Logical_Operator_out10_carry_O_UNCONNECTED : STD_LOGIC_VECTOR ( 7 downto 0 );
  signal NLW_Logical_Operator_out11_carry_CO_UNCONNECTED : STD_LOGIC_VECTOR ( 7 to 7 );
  signal NLW_Logical_Operator_out11_carry_O_UNCONNECTED : STD_LOGIC_VECTOR ( 7 downto 0 );
  signal \NLW_minus_out1_1_reg[13]_i_3_CO_UNCONNECTED\ : STD_LOGIC_VECTOR ( 7 to 7 );
  signal \NLW_minus_out1_1_reg[13]_i_3_O_UNCONNECTED\ : STD_LOGIC_VECTOR ( 7 downto 0 );
  attribute SOFT_HLUTNM : string;
  attribute SOFT_HLUTNM of \Add1_out1_1[0]_i_1\ : label is "soft_lutpair20";
  attribute SOFT_HLUTNM of \Add1_out1_1[10]_i_1\ : label is "soft_lutpair25";
  attribute SOFT_HLUTNM of \Add1_out1_1[1]_i_1\ : label is "soft_lutpair21";
  attribute SOFT_HLUTNM of \Add1_out1_1[2]_i_1\ : label is "soft_lutpair21";
  attribute SOFT_HLUTNM of \Add1_out1_1[3]_i_1\ : label is "soft_lutpair22";
  attribute SOFT_HLUTNM of \Add1_out1_1[4]_i_1\ : label is "soft_lutpair22";
  attribute SOFT_HLUTNM of \Add1_out1_1[5]_i_1\ : label is "soft_lutpair23";
  attribute SOFT_HLUTNM of \Add1_out1_1[6]_i_1\ : label is "soft_lutpair13";
  attribute SOFT_HLUTNM of \Add1_out1_1[7]_i_1\ : label is "soft_lutpair23";
  attribute SOFT_HLUTNM of \Add1_out1_1[8]_i_1\ : label is "soft_lutpair24";
  attribute SOFT_HLUTNM of \Add1_out1_1[9]_i_1\ : label is "soft_lutpair24";
  attribute ADDER_THRESHOLD : integer;
  attribute ADDER_THRESHOLD of \Add1_out1_1_reg[13]_i_1\ : label is 35;
  attribute ADDER_THRESHOLD of \Add2_out1_1_reg[13]_i_1\ : label is 35;
  attribute ADDER_THRESHOLD of \Add2_out1_1_reg[8]_i_1\ : label is 35;
  attribute COMPARATOR_THRESHOLD : integer;
  attribute COMPARATOR_THRESHOLD of Logical_Operator1_out10_carry : label is 11;
  attribute COMPARATOR_THRESHOLD of \Logical_Operator1_out10_inferred__0/i__carry\ : label is 11;
  attribute COMPARATOR_THRESHOLD of Logical_Operator_out10_carry : label is 11;
  attribute COMPARATOR_THRESHOLD of Logical_Operator_out11_carry : label is 11;
  attribute SOFT_HLUTNM of \Saturation1_out1_1[11]_i_1\ : label is "soft_lutpair25";
  attribute SOFT_HLUTNM of \Saturation1_out1_1[12]_i_1__1\ : label is "soft_lutpair18";
  attribute SOFT_HLUTNM of \minus_out1_1[10]_i_1__1\ : label is "soft_lutpair19";
  attribute SOFT_HLUTNM of \minus_out1_1[11]_i_1__1\ : label is "soft_lutpair20";
  attribute SOFT_HLUTNM of \minus_out1_1[12]_i_1\ : label is "soft_lutpair14";
  attribute SOFT_HLUTNM of \minus_out1_1[13]_i_1\ : label is "soft_lutpair14";
  attribute SOFT_HLUTNM of \minus_out1_1[1]_i_1\ : label is "soft_lutpair16";
  attribute SOFT_HLUTNM of \minus_out1_1[2]_i_1__1\ : label is "soft_lutpair16";
  attribute SOFT_HLUTNM of \minus_out1_1[3]_i_1__1\ : label is "soft_lutpair15";
  attribute SOFT_HLUTNM of \minus_out1_1[5]_i_2\ : label is "soft_lutpair15";
  attribute SOFT_HLUTNM of \minus_out1_1[6]_i_1__1\ : label is "soft_lutpair18";
  attribute SOFT_HLUTNM of \minus_out1_1[7]_i_1\ : label is "soft_lutpair13";
  attribute SOFT_HLUTNM of \minus_out1_1[9]_i_1__1\ : label is "soft_lutpair19";
  attribute COMPARATOR_THRESHOLD of \minus_out1_1_reg[13]_i_3\ : label is 11;
  attribute SOFT_HLUTNM of modulating_signal_in_clock_cycles_1_reg_i_15 : label is "soft_lutpair17";
  attribute SOFT_HLUTNM of modulating_signal_in_clock_cycles_1_reg_i_18 : label is "soft_lutpair17";
begin
  \HDL_Counter2_count_reg[11]_0\ <= \^hdl_counter2_count_reg[11]_0\;
  HDL_Counter2_count_reg_11_sp_1 <= HDL_Counter2_count_reg_11_sn_1;
  \OR_out1__0\ <= \^or_out1__0\;
  \delayMatch1_reg_reg[1][11]\ <= \^delaymatch1_reg_reg[1][11]\;
  \delayMatch1_reg_reg[1][13]\ <= \^delaymatch1_reg_reg[1][13]\;
  \delayMatch1_reg_reg[1][1]\ <= \^delaymatch1_reg_reg[1][1]\;
  \delayMatch1_reg_reg[1][3]\ <= \^delaymatch1_reg_reg[1][3]\;
  \delayMatch1_reg_reg[1][5]\ <= \^delaymatch1_reg_reg[1][5]\;
  \delayMatch1_reg_reg[1][7]\ <= \^delaymatch1_reg_reg[1][7]\;
  \delayMatch1_reg_reg[1][9]\ <= \^delaymatch1_reg_reg[1][9]\;
  \min_pulse_width_AXI_1_reg[0]\ <= \^min_pulse_width_axi_1_reg[0]\;
  \min_pulse_width_AXI_1_reg[10]\ <= \^min_pulse_width_axi_1_reg[10]\;
  \min_pulse_width_AXI_1_reg[4]\ <= \^min_pulse_width_axi_1_reg[4]\;
  \min_pulse_width_AXI_1_reg[5]\ <= \^min_pulse_width_axi_1_reg[5]\;
  \min_pulse_width_AXI_1_reg[8]\ <= \^min_pulse_width_axi_1_reg[8]\;
  \min_pulse_width_AXI_1_reg[9]\ <= \^min_pulse_width_axi_1_reg[9]\;
\Add1_out1_1[0]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"02"
    )
        port map (
      I0 => Q(0),
      I1 => Saturation1_out110_in,
      I2 => Q(13),
      O => Saturation1_out1(0)
    );
\Add1_out1_1[10]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"02"
    )
        port map (
      I0 => Q(10),
      I1 => Saturation1_out110_in,
      I2 => Q(13),
      O => Saturation1_out1(10)
    );
\Add1_out1_1[13]_i_2\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"BA"
    )
        port map (
      I0 => Saturation1_out110_in,
      I1 => Q(13),
      I2 => Q(12),
      O => \Add1_out1_1[13]_i_2_n_0\
    );
\Add1_out1_1[13]_i_3__1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"0D"
    )
        port map (
      I0 => Q(12),
      I1 => Q(13),
      I2 => Saturation1_out110_in,
      O => \Add1_out1_1[13]_i_3__1_n_0\
    );
\Add1_out1_1[13]_i_4\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"02"
    )
        port map (
      I0 => Q(11),
      I1 => Saturation1_out110_in,
      I2 => Q(13),
      O => \Add1_out1_1[13]_i_4_n_0\
    );
\Add1_out1_1[1]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"02"
    )
        port map (
      I0 => Q(1),
      I1 => Saturation1_out110_in,
      I2 => Q(13),
      O => Saturation1_out1(1)
    );
\Add1_out1_1[2]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"02"
    )
        port map (
      I0 => Q(2),
      I1 => Saturation1_out110_in,
      I2 => Q(13),
      O => Saturation1_out1(2)
    );
\Add1_out1_1[3]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"02"
    )
        port map (
      I0 => Q(3),
      I1 => Saturation1_out110_in,
      I2 => Q(13),
      O => Saturation1_out1(3)
    );
\Add1_out1_1[4]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"02"
    )
        port map (
      I0 => Q(4),
      I1 => Saturation1_out110_in,
      I2 => Q(13),
      O => Saturation1_out1(4)
    );
\Add1_out1_1[5]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"02"
    )
        port map (
      I0 => Q(5),
      I1 => Saturation1_out110_in,
      I2 => Q(13),
      O => Saturation1_out1(5)
    );
\Add1_out1_1[6]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"02"
    )
        port map (
      I0 => Q(6),
      I1 => Saturation1_out110_in,
      I2 => Q(13),
      O => Saturation1_out1(6)
    );
\Add1_out1_1[7]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"02"
    )
        port map (
      I0 => Q(7),
      I1 => Saturation1_out110_in,
      I2 => Q(13),
      O => Saturation1_out1(7)
    );
\Add1_out1_1[8]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"02"
    )
        port map (
      I0 => Q(8),
      I1 => Saturation1_out110_in,
      I2 => Q(13),
      O => Saturation1_out1(8)
    );
\Add1_out1_1[9]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"02"
    )
        port map (
      I0 => Q(9),
      I1 => Saturation1_out110_in,
      I2 => Q(13),
      O => Saturation1_out1(9)
    );
\Add1_out1_1_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => Saturation1_out1(0),
      Q => Add1_out1_1(0),
      R => RSTP
    );
\Add1_out1_1_reg[10]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => Saturation1_out1(10),
      Q => Add1_out1_1(10),
      R => RSTP
    );
\Add1_out1_1_reg[11]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => Add1_out1(11),
      Q => Add1_out1_1(11),
      R => RSTP
    );
\Add1_out1_1_reg[12]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => Add1_out1(12),
      Q => Add1_out1_1(12),
      R => RSTP
    );
\Add1_out1_1_reg[13]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => Add1_out1(13),
      Q => Add1_out1_1(13),
      R => RSTP
    );
\Add1_out1_1_reg[13]_i_1\: unisim.vcomponents.CARRY8
     port map (
      CI => '0',
      CI_TOP => '0',
      CO(7 downto 2) => \NLW_Add1_out1_1_reg[13]_i_1_CO_UNCONNECTED\(7 downto 2),
      CO(1) => \Add1_out1_1_reg[13]_i_1_n_6\,
      CO(0) => \Add1_out1_1_reg[13]_i_1_n_7\,
      DI(7 downto 2) => B"000000",
      DI(1) => \Add1_out1_1[13]_i_2_n_0\,
      DI(0) => '0',
      O(7 downto 3) => \NLW_Add1_out1_1_reg[13]_i_1_O_UNCONNECTED\(7 downto 3),
      O(2 downto 0) => Add1_out1(13 downto 11),
      S(7 downto 2) => B"000001",
      S(1) => \Add1_out1_1[13]_i_3__1_n_0\,
      S(0) => \Add1_out1_1[13]_i_4_n_0\
    );
\Add1_out1_1_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => Saturation1_out1(1),
      Q => Add1_out1_1(1),
      R => RSTP
    );
\Add1_out1_1_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => Saturation1_out1(2),
      Q => Add1_out1_1(2),
      R => RSTP
    );
\Add1_out1_1_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => Saturation1_out1(3),
      Q => Add1_out1_1(3),
      R => RSTP
    );
\Add1_out1_1_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => Saturation1_out1(4),
      Q => Add1_out1_1(4),
      R => RSTP
    );
\Add1_out1_1_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => Saturation1_out1(5),
      Q => Add1_out1_1(5),
      R => RSTP
    );
\Add1_out1_1_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => Saturation1_out1(6),
      Q => Add1_out1_1(6),
      R => RSTP
    );
\Add1_out1_1_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => Saturation1_out1(7),
      Q => Add1_out1_1(7),
      R => RSTP
    );
\Add1_out1_1_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => Saturation1_out1(8),
      Q => Add1_out1_1(8),
      R => RSTP
    );
\Add1_out1_1_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => Saturation1_out1(9),
      Q => Add1_out1_1(9),
      R => RSTP
    );
\Add2_out1_1[13]_i_2\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"BA"
    )
        port map (
      I0 => Saturation1_out110_in,
      I1 => Q(13),
      I2 => Q(12),
      O => \Add2_out1_1[13]_i_2_n_0\
    );
\Add2_out1_1[13]_i_3\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"EF"
    )
        port map (
      I0 => Q(13),
      I1 => Saturation1_out110_in,
      I2 => Q(11),
      O => \Add2_out1_1[13]_i_3_n_0\
    );
\Add2_out1_1[13]_i_4\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"EF"
    )
        port map (
      I0 => Q(13),
      I1 => Saturation1_out110_in,
      I2 => Q(10),
      O => \Add2_out1_1[13]_i_4_n_0\
    );
\Add2_out1_1[13]_i_5\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"EF"
    )
        port map (
      I0 => Q(13),
      I1 => Saturation1_out110_in,
      I2 => Q(9),
      O => \Add2_out1_1[13]_i_5_n_0\
    );
\Add2_out1_1[8]_i_10\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"EF"
    )
        port map (
      I0 => Q(13),
      I1 => Saturation1_out110_in,
      I2 => Q(1),
      O => \Add2_out1_1[8]_i_10_n_0\
    );
\Add2_out1_1[8]_i_2\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"EF"
    )
        port map (
      I0 => Q(13),
      I1 => Saturation1_out110_in,
      I2 => Q(0),
      O => \Add2_out1_1[8]_i_2_n_0\
    );
\Add2_out1_1[8]_i_3\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"EF"
    )
        port map (
      I0 => Q(13),
      I1 => Saturation1_out110_in,
      I2 => Q(8),
      O => \Add2_out1_1[8]_i_3_n_0\
    );
\Add2_out1_1[8]_i_4\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"EF"
    )
        port map (
      I0 => Q(13),
      I1 => Saturation1_out110_in,
      I2 => Q(7),
      O => \Add2_out1_1[8]_i_4_n_0\
    );
\Add2_out1_1[8]_i_5\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"EF"
    )
        port map (
      I0 => Q(13),
      I1 => Saturation1_out110_in,
      I2 => Q(6),
      O => \Add2_out1_1[8]_i_5_n_0\
    );
\Add2_out1_1[8]_i_6\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"EF"
    )
        port map (
      I0 => Q(13),
      I1 => Saturation1_out110_in,
      I2 => Q(5),
      O => \Add2_out1_1[8]_i_6_n_0\
    );
\Add2_out1_1[8]_i_7\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"EF"
    )
        port map (
      I0 => Q(13),
      I1 => Saturation1_out110_in,
      I2 => Q(4),
      O => \Add2_out1_1[8]_i_7_n_0\
    );
\Add2_out1_1[8]_i_8\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"EF"
    )
        port map (
      I0 => Q(13),
      I1 => Saturation1_out110_in,
      I2 => Q(3),
      O => \Add2_out1_1[8]_i_8_n_0\
    );
\Add2_out1_1[8]_i_9\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"EF"
    )
        port map (
      I0 => Q(13),
      I1 => Saturation1_out110_in,
      I2 => Q(2),
      O => \Add2_out1_1[8]_i_9_n_0\
    );
\Add2_out1_1_reg[10]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => Add2_out1(10),
      Q => Add2_out1_1(10),
      R => RSTP
    );
\Add2_out1_1_reg[11]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => Add2_out1(11),
      Q => Add2_out1_1(11),
      R => RSTP
    );
\Add2_out1_1_reg[12]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => Add2_out1(12),
      Q => Add2_out1_1(12),
      R => RSTP
    );
\Add2_out1_1_reg[13]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => Add2_out1(13),
      Q => Add2_out1_1(13),
      R => RSTP
    );
\Add2_out1_1_reg[13]_i_1\: unisim.vcomponents.CARRY8
     port map (
      CI => \Add2_out1_1_reg[8]_i_1_n_0\,
      CI_TOP => '0',
      CO(7 downto 4) => \NLW_Add2_out1_1_reg[13]_i_1_CO_UNCONNECTED\(7 downto 4),
      CO(3) => \Add2_out1_1_reg[13]_i_1_n_4\,
      CO(2) => \Add2_out1_1_reg[13]_i_1_n_5\,
      CO(1) => \Add2_out1_1_reg[13]_i_1_n_6\,
      CO(0) => \Add2_out1_1_reg[13]_i_1_n_7\,
      DI(7 downto 0) => B"00001000",
      O(7 downto 5) => \NLW_Add2_out1_1_reg[13]_i_1_O_UNCONNECTED\(7 downto 5),
      O(4 downto 0) => Add2_out1(13 downto 9),
      S(7 downto 4) => B"0001",
      S(3) => \Add2_out1_1[13]_i_2_n_0\,
      S(2) => \Add2_out1_1[13]_i_3_n_0\,
      S(1) => \Add2_out1_1[13]_i_4_n_0\,
      S(0) => \Add2_out1_1[13]_i_5_n_0\
    );
\Add2_out1_1_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => Add2_out1(1),
      Q => Add2_out1_1(1),
      R => RSTP
    );
\Add2_out1_1_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => Add2_out1(2),
      Q => Add2_out1_1(2),
      R => RSTP
    );
\Add2_out1_1_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => Add2_out1(3),
      Q => Add2_out1_1(3),
      R => RSTP
    );
\Add2_out1_1_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => Add2_out1(4),
      Q => Add2_out1_1(4),
      R => RSTP
    );
\Add2_out1_1_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => Add2_out1(5),
      Q => Add2_out1_1(5),
      R => RSTP
    );
\Add2_out1_1_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => Add2_out1(6),
      Q => Add2_out1_1(6),
      R => RSTP
    );
\Add2_out1_1_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => Add2_out1(7),
      Q => Add2_out1_1(7),
      R => RSTP
    );
\Add2_out1_1_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => Add2_out1(8),
      Q => Add2_out1_1(8),
      R => RSTP
    );
\Add2_out1_1_reg[8]_i_1\: unisim.vcomponents.CARRY8
     port map (
      CI => \Add2_out1_1[8]_i_2_n_0\,
      CI_TOP => '0',
      CO(7) => \Add2_out1_1_reg[8]_i_1_n_0\,
      CO(6) => \Add2_out1_1_reg[8]_i_1_n_1\,
      CO(5) => \Add2_out1_1_reg[8]_i_1_n_2\,
      CO(4) => \Add2_out1_1_reg[8]_i_1_n_3\,
      CO(3) => \Add2_out1_1_reg[8]_i_1_n_4\,
      CO(2) => \Add2_out1_1_reg[8]_i_1_n_5\,
      CO(1) => \Add2_out1_1_reg[8]_i_1_n_6\,
      CO(0) => \Add2_out1_1_reg[8]_i_1_n_7\,
      DI(7 downto 0) => B"00000000",
      O(7 downto 0) => Add2_out1(8 downto 1),
      S(7) => \Add2_out1_1[8]_i_3_n_0\,
      S(6) => \Add2_out1_1[8]_i_4_n_0\,
      S(5) => \Add2_out1_1[8]_i_5_n_0\,
      S(4) => \Add2_out1_1[8]_i_6_n_0\,
      S(3) => \Add2_out1_1[8]_i_7_n_0\,
      S(2) => \Add2_out1_1[8]_i_8_n_0\,
      S(1) => \Add2_out1_1[8]_i_9_n_0\,
      S(0) => \Add2_out1_1[8]_i_10_n_0\
    );
\Add2_out1_1_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => Add2_out1(9),
      Q => Add2_out1_1(9),
      R => RSTP
    );
Counter_Ctrl_out5_1_i_4: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0000000000000001"
    )
        port map (
      I0 => HDL_Counter2_count_reg(4),
      I1 => HDL_Counter2_count_reg(5),
      I2 => HDL_Counter2_count_reg(6),
      I3 => HDL_Counter2_count_reg(8),
      I4 => HDL_Counter2_count_reg(10),
      I5 => HDL_Counter2_count_reg(9),
      O => \^hdl_counter2_count_reg[11]_0\
    );
\Delay_out1[11]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AAAAFFBFAAAA0080"
    )
        port map (
      I0 => \Delay_out1_reg[13]_0\(11),
      I1 => HDL_Counter2_count_reg_11_sn_1,
      I2 => D(0),
      I3 => HDL_Counter2_count_reg(11),
      I4 => CO(0),
      I5 => \Delay_out1_reg[13]\(11),
      O => \^delaymatch1_reg_reg[1][11]\
    );
\Delay_out1[13]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AAAAFFBFAAAA0080"
    )
        port map (
      I0 => \Delay_out1_reg[13]_0\(13),
      I1 => HDL_Counter2_count_reg_11_sn_1,
      I2 => D(0),
      I3 => HDL_Counter2_count_reg(11),
      I4 => CO(0),
      I5 => \Delay_out1_reg[13]\(13),
      O => \^delaymatch1_reg_reg[1][13]\
    );
\Delay_out1[13]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"8000000000000000"
    )
        port map (
      I0 => \^hdl_counter2_count_reg[11]_0\,
      I1 => \Delay_out1_reg[13]_1\,
      I2 => \Delay_out1[13]_i_3_n_0\,
      I3 => \Delay_out1_reg[13]_2\,
      I4 => \Delay_out1[13]_i_4_n_0\,
      I5 => \Delay_out1_reg[13]_3\,
      O => HDL_Counter2_count_reg_11_sn_1
    );
\Delay_out1[13]_i_3\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"0001"
    )
        port map (
      I0 => HDL_Counter2_count_reg(1),
      I1 => HDL_Counter2_count_reg(0),
      I2 => HDL_Counter2_count_reg(3),
      I3 => HDL_Counter2_count_reg(2),
      O => \Delay_out1[13]_i_3_n_0\
    );
\Delay_out1[13]_i_4\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"31"
    )
        port map (
      I0 => HDL_Counter2_count_reg(7),
      I1 => HDL_Counter2_count_reg(9),
      I2 => HDL_Counter2_count_reg(8),
      O => \Delay_out1[13]_i_4_n_0\
    );
\Delay_out1[1]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AAAAFFBFAAAA0080"
    )
        port map (
      I0 => \Delay_out1_reg[13]_0\(1),
      I1 => HDL_Counter2_count_reg_11_sn_1,
      I2 => D(0),
      I3 => HDL_Counter2_count_reg(11),
      I4 => CO(0),
      I5 => \Delay_out1_reg[13]\(1),
      O => \^delaymatch1_reg_reg[1][1]\
    );
\Delay_out1[3]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AAAAFFBFAAAA0080"
    )
        port map (
      I0 => \Delay_out1_reg[13]_0\(3),
      I1 => HDL_Counter2_count_reg_11_sn_1,
      I2 => D(0),
      I3 => HDL_Counter2_count_reg(11),
      I4 => CO(0),
      I5 => \Delay_out1_reg[13]\(3),
      O => \^delaymatch1_reg_reg[1][3]\
    );
\Delay_out1[5]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AAAAFFBFAAAA0080"
    )
        port map (
      I0 => \Delay_out1_reg[13]_0\(5),
      I1 => HDL_Counter2_count_reg_11_sn_1,
      I2 => D(0),
      I3 => HDL_Counter2_count_reg(11),
      I4 => CO(0),
      I5 => \Delay_out1_reg[13]\(5),
      O => \^delaymatch1_reg_reg[1][5]\
    );
\Delay_out1[7]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AAAAFFBFAAAA0080"
    )
        port map (
      I0 => \Delay_out1_reg[13]_0\(7),
      I1 => HDL_Counter2_count_reg_11_sn_1,
      I2 => D(0),
      I3 => HDL_Counter2_count_reg(11),
      I4 => CO(0),
      I5 => \Delay_out1_reg[13]\(7),
      O => \^delaymatch1_reg_reg[1][7]\
    );
\Delay_out1[9]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AAAAFFBFAAAA0080"
    )
        port map (
      I0 => \Delay_out1_reg[13]_0\(9),
      I1 => HDL_Counter2_count_reg_11_sn_1,
      I2 => D(0),
      I3 => HDL_Counter2_count_reg(11),
      I4 => CO(0),
      I5 => \Delay_out1_reg[13]\(9),
      O => \^delaymatch1_reg_reg[1][9]\
    );
Logical_Operator1_out10_carry: unisim.vcomponents.CARRY8
     port map (
      CI => '0',
      CI_TOP => '0',
      CO(7) => NLW_Logical_Operator1_out10_carry_CO_UNCONNECTED(7),
      CO(6) => Relational_Operator_relop1,
      CO(5) => Logical_Operator1_out10_carry_n_2,
      CO(4) => Logical_Operator1_out10_carry_n_3,
      CO(3) => Logical_Operator1_out10_carry_n_4,
      CO(2) => Logical_Operator1_out10_carry_n_5,
      CO(1) => Logical_Operator1_out10_carry_n_6,
      CO(0) => Logical_Operator1_out10_carry_n_7,
      DI(7) => '0',
      DI(6) => \Logical_Operator1_out10_carry_i_1__1_n_0\,
      DI(5) => \Logical_Operator1_out10_carry_i_2__1_n_0\,
      DI(4) => \Logical_Operator1_out10_carry_i_3__1_n_0\,
      DI(3) => \Logical_Operator1_out10_carry_i_4__1_n_0\,
      DI(2) => \Logical_Operator1_out10_carry_i_5__1_n_0\,
      DI(1) => \Logical_Operator1_out10_carry_i_6__1_n_0\,
      DI(0) => \Logical_Operator1_out10_carry_i_7__1_n_0\,
      O(7 downto 0) => NLW_Logical_Operator1_out10_carry_O_UNCONNECTED(7 downto 0),
      S(7) => '0',
      S(6) => \Logical_Operator1_out10_carry_i_8__1_n_0\,
      S(5) => \Logical_Operator1_out10_carry_i_9__1_n_0\,
      S(4) => \Logical_Operator1_out10_carry_i_10__1_n_0\,
      S(3) => \Logical_Operator1_out10_carry_i_11__1_n_0\,
      S(2) => \Logical_Operator1_out10_carry_i_12__1_n_0\,
      S(1) => \Logical_Operator1_out10_carry_i_13__1_n_0\,
      S(0) => \Logical_Operator1_out10_carry_i_14__1_n_0\
    );
\Logical_Operator1_out10_carry_i_10__1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"A95900000000A959"
    )
        port map (
      I0 => minus_out1_1(8),
      I1 => \Delay_out1_reg[13]\(8),
      I2 => \^or_out1__0\,
      I3 => \Delay_out1_reg[13]_0\(8),
      I4 => \^delaymatch1_reg_reg[1][9]\,
      I5 => minus_out1_1(9),
      O => \Logical_Operator1_out10_carry_i_10__1_n_0\
    );
\Logical_Operator1_out10_carry_i_11__1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"A95900000000A959"
    )
        port map (
      I0 => minus_out1_1(6),
      I1 => \Delay_out1_reg[13]\(6),
      I2 => \^or_out1__0\,
      I3 => \Delay_out1_reg[13]_0\(6),
      I4 => \^delaymatch1_reg_reg[1][7]\,
      I5 => minus_out1_1(7),
      O => \Logical_Operator1_out10_carry_i_11__1_n_0\
    );
\Logical_Operator1_out10_carry_i_12__1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"A95900000000A959"
    )
        port map (
      I0 => minus_out1_1(4),
      I1 => \Delay_out1_reg[13]\(4),
      I2 => \^or_out1__0\,
      I3 => \Delay_out1_reg[13]_0\(4),
      I4 => \^delaymatch1_reg_reg[1][5]\,
      I5 => minus_out1_1(5),
      O => \Logical_Operator1_out10_carry_i_12__1_n_0\
    );
\Logical_Operator1_out10_carry_i_13__1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"A95900000000A959"
    )
        port map (
      I0 => minus_out1_1(2),
      I1 => \Delay_out1_reg[13]\(2),
      I2 => \^or_out1__0\,
      I3 => \Delay_out1_reg[13]_0\(2),
      I4 => \^delaymatch1_reg_reg[1][3]\,
      I5 => minus_out1_1(3),
      O => \Logical_Operator1_out10_carry_i_13__1_n_0\
    );
\Logical_Operator1_out10_carry_i_14__1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"E21D00000000E21D"
    )
        port map (
      I0 => \Delay_out1_reg[13]\(0),
      I1 => \^or_out1__0\,
      I2 => \Delay_out1_reg[13]_0\(0),
      I3 => Add1_out1_1(0),
      I4 => \^delaymatch1_reg_reg[1][1]\,
      I5 => minus_out1_1(1),
      O => \Logical_Operator1_out10_carry_i_14__1_n_0\
    );
\Logical_Operator1_out10_carry_i_1__1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"22222222BBB222B2"
    )
        port map (
      I0 => minus_out1_1(13),
      I1 => \^delaymatch1_reg_reg[1][13]\,
      I2 => \Delay_out1_reg[13]\(12),
      I3 => \^or_out1__0\,
      I4 => \Delay_out1_reg[13]_0\(12),
      I5 => minus_out1_1(12),
      O => \Logical_Operator1_out10_carry_i_1__1_n_0\
    );
\Logical_Operator1_out10_carry_i_2__1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"22222222BBB222B2"
    )
        port map (
      I0 => \^delaymatch1_reg_reg[1][11]\,
      I1 => minus_out1_1(11),
      I2 => \Delay_out1_reg[13]\(10),
      I3 => \^or_out1__0\,
      I4 => \Delay_out1_reg[13]_0\(10),
      I5 => minus_out1_1(10),
      O => \Logical_Operator1_out10_carry_i_2__1_n_0\
    );
\Logical_Operator1_out10_carry_i_3__1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"22222222BBB222B2"
    )
        port map (
      I0 => \^delaymatch1_reg_reg[1][9]\,
      I1 => minus_out1_1(9),
      I2 => \Delay_out1_reg[13]\(8),
      I3 => \^or_out1__0\,
      I4 => \Delay_out1_reg[13]_0\(8),
      I5 => minus_out1_1(8),
      O => \Logical_Operator1_out10_carry_i_3__1_n_0\
    );
\Logical_Operator1_out10_carry_i_4__1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"22222222BBB222B2"
    )
        port map (
      I0 => \^delaymatch1_reg_reg[1][7]\,
      I1 => minus_out1_1(7),
      I2 => \Delay_out1_reg[13]\(6),
      I3 => \^or_out1__0\,
      I4 => \Delay_out1_reg[13]_0\(6),
      I5 => minus_out1_1(6),
      O => \Logical_Operator1_out10_carry_i_4__1_n_0\
    );
\Logical_Operator1_out10_carry_i_5__1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"22222222BBB222B2"
    )
        port map (
      I0 => \^delaymatch1_reg_reg[1][5]\,
      I1 => minus_out1_1(5),
      I2 => \Delay_out1_reg[13]\(4),
      I3 => \^or_out1__0\,
      I4 => \Delay_out1_reg[13]_0\(4),
      I5 => minus_out1_1(4),
      O => \Logical_Operator1_out10_carry_i_5__1_n_0\
    );
\Logical_Operator1_out10_carry_i_6__1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"22222222BBB222B2"
    )
        port map (
      I0 => \^delaymatch1_reg_reg[1][3]\,
      I1 => minus_out1_1(3),
      I2 => \Delay_out1_reg[13]\(2),
      I3 => \^or_out1__0\,
      I4 => \Delay_out1_reg[13]_0\(2),
      I5 => minus_out1_1(2),
      O => \Logical_Operator1_out10_carry_i_6__1_n_0\
    );
\Logical_Operator1_out10_carry_i_7__1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"7577755510111000"
    )
        port map (
      I0 => minus_out1_1(1),
      I1 => Add1_out1_1(0),
      I2 => \Delay_out1_reg[13]_0\(0),
      I3 => \^or_out1__0\,
      I4 => \Delay_out1_reg[13]\(0),
      I5 => \^delaymatch1_reg_reg[1][1]\,
      O => \Logical_Operator1_out10_carry_i_7__1_n_0\
    );
\Logical_Operator1_out10_carry_i_8__1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"A95900000000A959"
    )
        port map (
      I0 => minus_out1_1(12),
      I1 => \Delay_out1_reg[13]\(12),
      I2 => \^or_out1__0\,
      I3 => \Delay_out1_reg[13]_0\(12),
      I4 => \^delaymatch1_reg_reg[1][13]\,
      I5 => minus_out1_1(13),
      O => \Logical_Operator1_out10_carry_i_8__1_n_0\
    );
\Logical_Operator1_out10_carry_i_9__1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"A95900000000A959"
    )
        port map (
      I0 => minus_out1_1(10),
      I1 => \Delay_out1_reg[13]\(10),
      I2 => \^or_out1__0\,
      I3 => \Delay_out1_reg[13]_0\(10),
      I4 => \^delaymatch1_reg_reg[1][11]\,
      I5 => minus_out1_1(11),
      O => \Logical_Operator1_out10_carry_i_9__1_n_0\
    );
\Logical_Operator1_out10_inferred__0/i__carry\: unisim.vcomponents.CARRY8
     port map (
      CI => '0',
      CI_TOP => '0',
      CO(7) => \NLW_Logical_Operator1_out10_inferred__0/i__carry_CO_UNCONNECTED\(7),
      CO(6) => Relational_Operator1_relop1,
      CO(5) => \Logical_Operator1_out10_inferred__0/i__carry_n_2\,
      CO(4) => \Logical_Operator1_out10_inferred__0/i__carry_n_3\,
      CO(3) => \Logical_Operator1_out10_inferred__0/i__carry_n_4\,
      CO(2) => \Logical_Operator1_out10_inferred__0/i__carry_n_5\,
      CO(1) => \Logical_Operator1_out10_inferred__0/i__carry_n_6\,
      CO(0) => \Logical_Operator1_out10_inferred__0/i__carry_n_7\,
      DI(7) => '0',
      DI(6) => \i__carry_i_1__1_n_0\,
      DI(5) => \i__carry_i_2__1_n_0\,
      DI(4) => \i__carry_i_3__1_n_0\,
      DI(3) => \i__carry_i_4__1_n_0\,
      DI(2) => \i__carry_i_5__1_n_0\,
      DI(1) => \i__carry_i_6__1_n_0\,
      DI(0) => \i__carry_i_7__1_n_0\,
      O(7 downto 0) => \NLW_Logical_Operator1_out10_inferred__0/i__carry_O_UNCONNECTED\(7 downto 0),
      S(7) => '0',
      S(6) => \i__carry_i_8__1_n_0\,
      S(5) => \i__carry_i_9__1_n_0\,
      S(4) => \i__carry_i_10_n_0\,
      S(3) => \i__carry_i_11_n_0\,
      S(2) => \i__carry_i_12_n_0\,
      S(1) => \i__carry_i_13_n_0\,
      S(0) => \i__carry_i_14_n_0\
    );
Logical_Operator_out10_carry: unisim.vcomponents.CARRY8
     port map (
      CI => '0',
      CI_TOP => '0',
      CO(7) => NLW_Logical_Operator_out10_carry_CO_UNCONNECTED(7),
      CO(6) => Relational_Operator3_relop1,
      CO(5) => Logical_Operator_out10_carry_n_2,
      CO(4) => Logical_Operator_out10_carry_n_3,
      CO(3) => Logical_Operator_out10_carry_n_4,
      CO(2) => Logical_Operator_out10_carry_n_5,
      CO(1) => Logical_Operator_out10_carry_n_6,
      CO(0) => Logical_Operator_out10_carry_n_7,
      DI(7) => '0',
      DI(6) => \Logical_Operator_out10_carry_i_1__1_n_0\,
      DI(5) => \Logical_Operator_out10_carry_i_2__1_n_0\,
      DI(4) => \Logical_Operator_out10_carry_i_3__1_n_0\,
      DI(3) => \Logical_Operator_out10_carry_i_4__1_n_0\,
      DI(2) => \Logical_Operator_out10_carry_i_5__1_n_0\,
      DI(1) => \Logical_Operator_out10_carry_i_6__1_n_0\,
      DI(0) => \Logical_Operator_out10_carry_i_7__1_n_0\,
      O(7 downto 0) => NLW_Logical_Operator_out10_carry_O_UNCONNECTED(7 downto 0),
      S(7) => '0',
      S(6) => \Logical_Operator_out10_carry_i_8__1_n_0\,
      S(5) => \Logical_Operator_out10_carry_i_9__1_n_0\,
      S(4) => \Logical_Operator_out10_carry_i_10__1_n_0\,
      S(3) => \Logical_Operator_out10_carry_i_11__1_n_0\,
      S(2) => \Logical_Operator_out10_carry_i_12__1_n_0\,
      S(1) => \Logical_Operator_out10_carry_i_13__1_n_0\,
      S(0) => \Logical_Operator_out10_carry_i_14__1_n_0\
    );
\Logical_Operator_out10_carry_i_10__1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"A95900000000A959"
    )
        port map (
      I0 => Add2_out1_1(8),
      I1 => \Delay_out1_reg[13]\(8),
      I2 => \^or_out1__0\,
      I3 => \Delay_out1_reg[13]_0\(8),
      I4 => \^delaymatch1_reg_reg[1][9]\,
      I5 => Add2_out1_1(9),
      O => \Logical_Operator_out10_carry_i_10__1_n_0\
    );
\Logical_Operator_out10_carry_i_11__1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"A95900000000A959"
    )
        port map (
      I0 => Add2_out1_1(6),
      I1 => \Delay_out1_reg[13]\(6),
      I2 => \^or_out1__0\,
      I3 => \Delay_out1_reg[13]_0\(6),
      I4 => \^delaymatch1_reg_reg[1][7]\,
      I5 => Add2_out1_1(7),
      O => \Logical_Operator_out10_carry_i_11__1_n_0\
    );
\Logical_Operator_out10_carry_i_12__1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"A95900000000A959"
    )
        port map (
      I0 => Add2_out1_1(4),
      I1 => \Delay_out1_reg[13]\(4),
      I2 => \^or_out1__0\,
      I3 => \Delay_out1_reg[13]_0\(4),
      I4 => \^delaymatch1_reg_reg[1][5]\,
      I5 => Add2_out1_1(5),
      O => \Logical_Operator_out10_carry_i_12__1_n_0\
    );
\Logical_Operator_out10_carry_i_13__1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"A95900000000A959"
    )
        port map (
      I0 => Add2_out1_1(2),
      I1 => \Delay_out1_reg[13]\(2),
      I2 => \^or_out1__0\,
      I3 => \Delay_out1_reg[13]_0\(2),
      I4 => \^delaymatch1_reg_reg[1][3]\,
      I5 => Add2_out1_1(3),
      O => \Logical_Operator_out10_carry_i_13__1_n_0\
    );
\Logical_Operator_out10_carry_i_14__1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"E21D00000000E21D"
    )
        port map (
      I0 => \Delay_out1_reg[13]\(0),
      I1 => \^or_out1__0\,
      I2 => \Delay_out1_reg[13]_0\(0),
      I3 => Add1_out1_1(0),
      I4 => \^delaymatch1_reg_reg[1][1]\,
      I5 => Add2_out1_1(1),
      O => \Logical_Operator_out10_carry_i_14__1_n_0\
    );
\Logical_Operator_out10_carry_i_1__1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"22222222BBB222B2"
    )
        port map (
      I0 => Add2_out1_1(13),
      I1 => \^delaymatch1_reg_reg[1][13]\,
      I2 => \Delay_out1_reg[13]\(12),
      I3 => \^or_out1__0\,
      I4 => \Delay_out1_reg[13]_0\(12),
      I5 => Add2_out1_1(12),
      O => \Logical_Operator_out10_carry_i_1__1_n_0\
    );
\Logical_Operator_out10_carry_i_2__1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"22222222BBB222B2"
    )
        port map (
      I0 => \^delaymatch1_reg_reg[1][11]\,
      I1 => Add2_out1_1(11),
      I2 => \Delay_out1_reg[13]\(10),
      I3 => \^or_out1__0\,
      I4 => \Delay_out1_reg[13]_0\(10),
      I5 => Add2_out1_1(10),
      O => \Logical_Operator_out10_carry_i_2__1_n_0\
    );
\Logical_Operator_out10_carry_i_3__1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"22222222BBB222B2"
    )
        port map (
      I0 => \^delaymatch1_reg_reg[1][9]\,
      I1 => Add2_out1_1(9),
      I2 => \Delay_out1_reg[13]\(8),
      I3 => \^or_out1__0\,
      I4 => \Delay_out1_reg[13]_0\(8),
      I5 => Add2_out1_1(8),
      O => \Logical_Operator_out10_carry_i_3__1_n_0\
    );
\Logical_Operator_out10_carry_i_4__1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"22222222BBB222B2"
    )
        port map (
      I0 => \^delaymatch1_reg_reg[1][7]\,
      I1 => Add2_out1_1(7),
      I2 => \Delay_out1_reg[13]\(6),
      I3 => \^or_out1__0\,
      I4 => \Delay_out1_reg[13]_0\(6),
      I5 => Add2_out1_1(6),
      O => \Logical_Operator_out10_carry_i_4__1_n_0\
    );
\Logical_Operator_out10_carry_i_5__1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"22222222BBB222B2"
    )
        port map (
      I0 => \^delaymatch1_reg_reg[1][5]\,
      I1 => Add2_out1_1(5),
      I2 => \Delay_out1_reg[13]\(4),
      I3 => \^or_out1__0\,
      I4 => \Delay_out1_reg[13]_0\(4),
      I5 => Add2_out1_1(4),
      O => \Logical_Operator_out10_carry_i_5__1_n_0\
    );
\Logical_Operator_out10_carry_i_6__1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"22222222BBB222B2"
    )
        port map (
      I0 => \^delaymatch1_reg_reg[1][3]\,
      I1 => Add2_out1_1(3),
      I2 => \Delay_out1_reg[13]\(2),
      I3 => \^or_out1__0\,
      I4 => \Delay_out1_reg[13]_0\(2),
      I5 => Add2_out1_1(2),
      O => \Logical_Operator_out10_carry_i_6__1_n_0\
    );
\Logical_Operator_out10_carry_i_7__1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"7577755510111000"
    )
        port map (
      I0 => Add2_out1_1(1),
      I1 => Add1_out1_1(0),
      I2 => \Delay_out1_reg[13]_0\(0),
      I3 => \^or_out1__0\,
      I4 => \Delay_out1_reg[13]\(0),
      I5 => \^delaymatch1_reg_reg[1][1]\,
      O => \Logical_Operator_out10_carry_i_7__1_n_0\
    );
\Logical_Operator_out10_carry_i_8__1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"A95900000000A959"
    )
        port map (
      I0 => Add2_out1_1(12),
      I1 => \Delay_out1_reg[13]\(12),
      I2 => \^or_out1__0\,
      I3 => \Delay_out1_reg[13]_0\(12),
      I4 => \^delaymatch1_reg_reg[1][13]\,
      I5 => Add2_out1_1(13),
      O => \Logical_Operator_out10_carry_i_8__1_n_0\
    );
\Logical_Operator_out10_carry_i_9__1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"A95900000000A959"
    )
        port map (
      I0 => Add2_out1_1(10),
      I1 => \Delay_out1_reg[13]\(10),
      I2 => \^or_out1__0\,
      I3 => \Delay_out1_reg[13]_0\(10),
      I4 => \^delaymatch1_reg_reg[1][11]\,
      I5 => Add2_out1_1(11),
      O => \Logical_Operator_out10_carry_i_9__1_n_0\
    );
Logical_Operator_out11_carry: unisim.vcomponents.CARRY8
     port map (
      CI => '0',
      CI_TOP => '0',
      CO(7) => NLW_Logical_Operator_out11_carry_CO_UNCONNECTED(7),
      CO(6) => Relational_Operator2_relop1,
      CO(5) => Logical_Operator_out11_carry_n_2,
      CO(4) => Logical_Operator_out11_carry_n_3,
      CO(3) => Logical_Operator_out11_carry_n_4,
      CO(2) => Logical_Operator_out11_carry_n_5,
      CO(1) => Logical_Operator_out11_carry_n_6,
      CO(0) => Logical_Operator_out11_carry_n_7,
      DI(7) => '0',
      DI(6) => \Logical_Operator_out11_carry_i_1__1_n_0\,
      DI(5) => \Logical_Operator_out11_carry_i_2__1_n_0\,
      DI(4) => \i__carry_i_3__1_n_0\,
      DI(3) => \i__carry_i_4__1_n_0\,
      DI(2) => \i__carry_i_5__1_n_0\,
      DI(1) => \i__carry_i_6__1_n_0\,
      DI(0) => \i__carry_i_7__1_n_0\,
      O(7 downto 0) => NLW_Logical_Operator_out11_carry_O_UNCONNECTED(7 downto 0),
      S(7) => '0',
      S(6) => \Logical_Operator_out11_carry_i_3__1_n_0\,
      S(5) => \Logical_Operator_out11_carry_i_4__1_n_0\,
      S(4) => \Logical_Operator_out11_carry_i_5__1_n_0\,
      S(3) => \Logical_Operator_out11_carry_i_6__1_n_0\,
      S(2) => \Logical_Operator_out11_carry_i_7__1_n_0\,
      S(1) => \Logical_Operator_out11_carry_i_8__1_n_0\,
      S(0) => \Logical_Operator_out11_carry_i_9__1_n_0\
    );
\Logical_Operator_out11_carry_i_1__1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"222222B2B2B222B2"
    )
        port map (
      I0 => \^delaymatch1_reg_reg[1][13]\,
      I1 => Add1_out1_1(13),
      I2 => Add1_out1_1(12),
      I3 => \Delay_out1_reg[13]\(12),
      I4 => \^or_out1__0\,
      I5 => \Delay_out1_reg[13]_0\(12),
      O => \Logical_Operator_out11_carry_i_1__1_n_0\
    );
\Logical_Operator_out11_carry_i_2__1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"222222B2B2B222B2"
    )
        port map (
      I0 => Add1_out1_1(11),
      I1 => \^delaymatch1_reg_reg[1][11]\,
      I2 => Add1_out1_1(10),
      I3 => \Delay_out1_reg[13]\(10),
      I4 => \^or_out1__0\,
      I5 => \Delay_out1_reg[13]_0\(10),
      O => \Logical_Operator_out11_carry_i_2__1_n_0\
    );
\Logical_Operator_out11_carry_i_3__1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"A95900000000A959"
    )
        port map (
      I0 => Add1_out1_1(12),
      I1 => \Delay_out1_reg[13]\(12),
      I2 => \^or_out1__0\,
      I3 => \Delay_out1_reg[13]_0\(12),
      I4 => \^delaymatch1_reg_reg[1][13]\,
      I5 => Add1_out1_1(13),
      O => \Logical_Operator_out11_carry_i_3__1_n_0\
    );
\Logical_Operator_out11_carry_i_4__1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"A95900000000A959"
    )
        port map (
      I0 => Add1_out1_1(10),
      I1 => \Delay_out1_reg[13]\(10),
      I2 => \^or_out1__0\,
      I3 => \Delay_out1_reg[13]_0\(10),
      I4 => \^delaymatch1_reg_reg[1][11]\,
      I5 => Add1_out1_1(11),
      O => \Logical_Operator_out11_carry_i_4__1_n_0\
    );
\Logical_Operator_out11_carry_i_5__1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"A95900000000A959"
    )
        port map (
      I0 => Add1_out1_1(8),
      I1 => \Delay_out1_reg[13]\(8),
      I2 => \^or_out1__0\,
      I3 => \Delay_out1_reg[13]_0\(8),
      I4 => \^delaymatch1_reg_reg[1][9]\,
      I5 => Add1_out1_1(9),
      O => \Logical_Operator_out11_carry_i_5__1_n_0\
    );
\Logical_Operator_out11_carry_i_6__1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"A95900000000A959"
    )
        port map (
      I0 => Add1_out1_1(6),
      I1 => \Delay_out1_reg[13]\(6),
      I2 => \^or_out1__0\,
      I3 => \Delay_out1_reg[13]_0\(6),
      I4 => \^delaymatch1_reg_reg[1][7]\,
      I5 => Add1_out1_1(7),
      O => \Logical_Operator_out11_carry_i_6__1_n_0\
    );
\Logical_Operator_out11_carry_i_7__1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"A95900000000A959"
    )
        port map (
      I0 => Add1_out1_1(4),
      I1 => \Delay_out1_reg[13]\(4),
      I2 => \^or_out1__0\,
      I3 => \Delay_out1_reg[13]_0\(4),
      I4 => \^delaymatch1_reg_reg[1][5]\,
      I5 => Add1_out1_1(5),
      O => \Logical_Operator_out11_carry_i_7__1_n_0\
    );
\Logical_Operator_out11_carry_i_8__1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"A95900000000A959"
    )
        port map (
      I0 => Add1_out1_1(2),
      I1 => \Delay_out1_reg[13]\(2),
      I2 => \^or_out1__0\,
      I3 => \Delay_out1_reg[13]_0\(2),
      I4 => \^delaymatch1_reg_reg[1][3]\,
      I5 => Add1_out1_1(3),
      O => \Logical_Operator_out11_carry_i_8__1_n_0\
    );
\Logical_Operator_out11_carry_i_9__1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"E21D00000000E21D"
    )
        port map (
      I0 => \Delay_out1_reg[13]\(0),
      I1 => \^or_out1__0\,
      I2 => \Delay_out1_reg[13]_0\(0),
      I3 => Add1_out1_1(0),
      I4 => \^delaymatch1_reg_reg[1][1]\,
      I5 => Add1_out1_1(1),
      O => \Logical_Operator_out11_carry_i_9__1_n_0\
    );
\Saturation1_out1_1[11]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"02"
    )
        port map (
      I0 => Q(11),
      I1 => Saturation1_out110_in,
      I2 => Q(13),
      O => Saturation1_out1(11)
    );
\Saturation1_out1_1[12]_i_1__1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"BA"
    )
        port map (
      I0 => Saturation1_out110_in,
      I1 => Q(13),
      I2 => Q(12),
      O => Saturation1_out1(12)
    );
\Saturation1_out1_1_reg[11]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => Saturation1_out1(11),
      Q => Saturation1_out1_1(11),
      R => RSTP
    );
\Saturation1_out1_1_reg[12]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => Saturation1_out1(12),
      Q => Saturation1_out1_1(12),
      R => RSTP
    );
\i__carry_i_10\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"A95900000000A959"
    )
        port map (
      I0 => Add1_out1_1(8),
      I1 => \Delay_out1_reg[13]\(8),
      I2 => \^or_out1__0\,
      I3 => \Delay_out1_reg[13]_0\(8),
      I4 => \^delaymatch1_reg_reg[1][9]\,
      I5 => Add1_out1_1(9),
      O => \i__carry_i_10_n_0\
    );
\i__carry_i_11\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"A95900000000A959"
    )
        port map (
      I0 => Add1_out1_1(6),
      I1 => \Delay_out1_reg[13]\(6),
      I2 => \^or_out1__0\,
      I3 => \Delay_out1_reg[13]_0\(6),
      I4 => \^delaymatch1_reg_reg[1][7]\,
      I5 => Add1_out1_1(7),
      O => \i__carry_i_11_n_0\
    );
\i__carry_i_12\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"A95900000000A959"
    )
        port map (
      I0 => Add1_out1_1(4),
      I1 => \Delay_out1_reg[13]\(4),
      I2 => \^or_out1__0\,
      I3 => \Delay_out1_reg[13]_0\(4),
      I4 => \^delaymatch1_reg_reg[1][5]\,
      I5 => Add1_out1_1(5),
      O => \i__carry_i_12_n_0\
    );
\i__carry_i_13\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"A95900000000A959"
    )
        port map (
      I0 => Add1_out1_1(2),
      I1 => \Delay_out1_reg[13]\(2),
      I2 => \^or_out1__0\,
      I3 => \Delay_out1_reg[13]_0\(2),
      I4 => \^delaymatch1_reg_reg[1][3]\,
      I5 => Add1_out1_1(3),
      O => \i__carry_i_13_n_0\
    );
\i__carry_i_14\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"E21D00000000E21D"
    )
        port map (
      I0 => \Delay_out1_reg[13]\(0),
      I1 => \^or_out1__0\,
      I2 => \Delay_out1_reg[13]_0\(0),
      I3 => Add1_out1_1(0),
      I4 => \^delaymatch1_reg_reg[1][1]\,
      I5 => Add1_out1_1(1),
      O => \i__carry_i_14_n_0\
    );
\i__carry_i_1__1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"AAAEEEAE"
    )
        port map (
      I0 => \^delaymatch1_reg_reg[1][13]\,
      I1 => Saturation1_out1_1(12),
      I2 => \Delay_out1_reg[13]\(12),
      I3 => \^or_out1__0\,
      I4 => \Delay_out1_reg[13]_0\(12),
      O => \i__carry_i_1__1_n_0\
    );
\i__carry_i_2__1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"222222B2B2B222B2"
    )
        port map (
      I0 => Saturation1_out1_1(11),
      I1 => \^delaymatch1_reg_reg[1][11]\,
      I2 => Add1_out1_1(10),
      I3 => \Delay_out1_reg[13]\(10),
      I4 => \^or_out1__0\,
      I5 => \Delay_out1_reg[13]_0\(10),
      O => \i__carry_i_2__1_n_0\
    );
\i__carry_i_3__1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"222222B2B2B222B2"
    )
        port map (
      I0 => Add1_out1_1(9),
      I1 => \^delaymatch1_reg_reg[1][9]\,
      I2 => Add1_out1_1(8),
      I3 => \Delay_out1_reg[13]\(8),
      I4 => \^or_out1__0\,
      I5 => \Delay_out1_reg[13]_0\(8),
      O => \i__carry_i_3__1_n_0\
    );
\i__carry_i_4__1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"222222B2B2B222B2"
    )
        port map (
      I0 => Add1_out1_1(7),
      I1 => \^delaymatch1_reg_reg[1][7]\,
      I2 => Add1_out1_1(6),
      I3 => \Delay_out1_reg[13]\(6),
      I4 => \^or_out1__0\,
      I5 => \Delay_out1_reg[13]_0\(6),
      O => \i__carry_i_4__1_n_0\
    );
\i__carry_i_5__1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"222222B2B2B222B2"
    )
        port map (
      I0 => Add1_out1_1(5),
      I1 => \^delaymatch1_reg_reg[1][5]\,
      I2 => Add1_out1_1(4),
      I3 => \Delay_out1_reg[13]\(4),
      I4 => \^or_out1__0\,
      I5 => \Delay_out1_reg[13]_0\(4),
      O => \i__carry_i_5__1_n_0\
    );
\i__carry_i_6__1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"222222B2B2B222B2"
    )
        port map (
      I0 => Add1_out1_1(3),
      I1 => \^delaymatch1_reg_reg[1][3]\,
      I2 => Add1_out1_1(2),
      I3 => \Delay_out1_reg[13]\(2),
      I4 => \^or_out1__0\,
      I5 => \Delay_out1_reg[13]_0\(2),
      O => \i__carry_i_6__1_n_0\
    );
\i__carry_i_7__1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"222222B2B2B222B2"
    )
        port map (
      I0 => Add1_out1_1(1),
      I1 => \^delaymatch1_reg_reg[1][1]\,
      I2 => Add1_out1_1(0),
      I3 => \Delay_out1_reg[13]\(0),
      I4 => \^or_out1__0\,
      I5 => \Delay_out1_reg[13]_0\(0),
      O => \i__carry_i_7__1_n_0\
    );
\i__carry_i_8__1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"0000A959"
    )
        port map (
      I0 => Saturation1_out1_1(12),
      I1 => \Delay_out1_reg[13]\(12),
      I2 => \^or_out1__0\,
      I3 => \Delay_out1_reg[13]_0\(12),
      I4 => \^delaymatch1_reg_reg[1][13]\,
      O => \i__carry_i_8__1_n_0\
    );
\i__carry_i_9__1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"A95900000000A959"
    )
        port map (
      I0 => Add1_out1_1(10),
      I1 => \Delay_out1_reg[13]\(10),
      I2 => \^or_out1__0\,
      I3 => \Delay_out1_reg[13]_0\(10),
      I4 => \^delaymatch1_reg_reg[1][11]\,
      I5 => Saturation1_out1_1(11),
      O => \i__carry_i_9__1_n_0\
    );
\minus_out1_1[10]_i_1__1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"02"
    )
        port map (
      I0 => \^min_pulse_width_axi_1_reg[9]\,
      I1 => Saturation1_out110_in,
      I2 => Q(13),
      O => minus_out1(10)
    );
\minus_out1_1[10]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"00000001FFFFFFFE"
    )
        port map (
      I0 => Q(9),
      I1 => Q(7),
      I2 => \^min_pulse_width_axi_1_reg[4]\,
      I3 => Q(6),
      I4 => Q(8),
      I5 => Q(10),
      O => \^min_pulse_width_axi_1_reg[9]\
    );
\minus_out1_1[11]_i_1__1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"02"
    )
        port map (
      I0 => \^min_pulse_width_axi_1_reg[10]\,
      I1 => Saturation1_out110_in,
      I2 => Q(13),
      O => minus_out1(11)
    );
\minus_out1_1[11]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"00000001FFFFFFFE"
    )
        port map (
      I0 => Q(10),
      I1 => Q(8),
      I2 => \minus_out1_1[11]_i_3_n_0\,
      I3 => Q(7),
      I4 => Q(9),
      I5 => Q(11),
      O => \^min_pulse_width_axi_1_reg[10]\
    );
\minus_out1_1[11]_i_3\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFFFFFFFFFFFFFE"
    )
        port map (
      I0 => Q(5),
      I1 => Q(3),
      I2 => \^min_pulse_width_axi_1_reg[0]\,
      I3 => Q(2),
      I4 => Q(4),
      I5 => Q(6),
      O => \minus_out1_1[11]_i_3_n_0\
    );
\minus_out1_1[12]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFFF001E"
    )
        port map (
      I0 => \minus_out1_1_reg[12]_0\,
      I1 => Q(11),
      I2 => Q(12),
      I3 => Q(13),
      I4 => Saturation1_out110_in,
      O => minus_out1(12)
    );
\minus_out1_1[13]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFFF00FE"
    )
        port map (
      I0 => Q(11),
      I1 => \minus_out1_1_reg[12]_0\,
      I2 => Q(12),
      I3 => Q(13),
      I4 => Saturation1_out110_in,
      O => minus_out1(13)
    );
\minus_out1_1[13]_i_10__0\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"2"
    )
        port map (
      I0 => Q(12),
      I1 => Q(13),
      O => \minus_out1_1[13]_i_10__0_n_0\
    );
\minus_out1_1[13]_i_11__0\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => Q(10),
      I1 => Q(11),
      O => \minus_out1_1[13]_i_11__0_n_0\
    );
\minus_out1_1[13]_i_12__0\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => Q(8),
      I1 => Q(9),
      O => \minus_out1_1[13]_i_12__0_n_0\
    );
\minus_out1_1[13]_i_13__0\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => Q(6),
      I1 => Q(7),
      O => \minus_out1_1[13]_i_13__0_n_0\
    );
\minus_out1_1[13]_i_14__0\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => Q(4),
      I1 => Q(5),
      O => \minus_out1_1[13]_i_14__0_n_0\
    );
\minus_out1_1[13]_i_15__1\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => Q(2),
      I1 => Q(3),
      O => \minus_out1_1[13]_i_15__1_n_0\
    );
\minus_out1_1[13]_i_16\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => Q(1),
      I1 => Q(0),
      O => \minus_out1_1[13]_i_16_n_0\
    );
\minus_out1_1[13]_i_4__0\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"E"
    )
        port map (
      I0 => Q(10),
      I1 => Q(11),
      O => \minus_out1_1[13]_i_4__0_n_0\
    );
\minus_out1_1[13]_i_5__0\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"E"
    )
        port map (
      I0 => Q(8),
      I1 => Q(9),
      O => \minus_out1_1[13]_i_5__0_n_0\
    );
\minus_out1_1[13]_i_6__0\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"E"
    )
        port map (
      I0 => Q(6),
      I1 => Q(7),
      O => \minus_out1_1[13]_i_6__0_n_0\
    );
\minus_out1_1[13]_i_7__0\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"E"
    )
        port map (
      I0 => Q(4),
      I1 => Q(5),
      O => \minus_out1_1[13]_i_7__0_n_0\
    );
\minus_out1_1[13]_i_8\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"E"
    )
        port map (
      I0 => Q(2),
      I1 => Q(3),
      O => \minus_out1_1[13]_i_8_n_0\
    );
\minus_out1_1[13]_i_9\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"E"
    )
        port map (
      I0 => Q(0),
      I1 => Q(1),
      O => \minus_out1_1[13]_i_9_n_0\
    );
\minus_out1_1[1]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"0006"
    )
        port map (
      I0 => Q(1),
      I1 => Q(0),
      I2 => Saturation1_out110_in,
      I3 => Q(13),
      O => minus_out1(1)
    );
\minus_out1_1[2]_i_1__1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"00000056"
    )
        port map (
      I0 => Q(2),
      I1 => Q(0),
      I2 => Q(1),
      I3 => Saturation1_out110_in,
      I4 => Q(13),
      O => minus_out1(2)
    );
\minus_out1_1[3]_i_1__1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"00005556"
    )
        port map (
      I0 => Q(3),
      I1 => Q(1),
      I2 => Q(0),
      I3 => Q(2),
      I4 => \minus_out1_1[5]_i_3_n_0\,
      O => minus_out1(3)
    );
\minus_out1_1[4]_i_1__1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0000000055555556"
    )
        port map (
      I0 => Q(4),
      I1 => Q(2),
      I2 => Q(0),
      I3 => Q(1),
      I4 => Q(3),
      I5 => \minus_out1_1[5]_i_3_n_0\,
      O => minus_out1(4)
    );
\minus_out1_1[5]_i_1__1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0000000055555556"
    )
        port map (
      I0 => Q(5),
      I1 => Q(3),
      I2 => \^min_pulse_width_axi_1_reg[0]\,
      I3 => Q(2),
      I4 => Q(4),
      I5 => \minus_out1_1[5]_i_3_n_0\,
      O => minus_out1(5)
    );
\minus_out1_1[5]_i_2\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"E"
    )
        port map (
      I0 => Q(0),
      I1 => Q(1),
      O => \^min_pulse_width_axi_1_reg[0]\
    );
\minus_out1_1[5]_i_3\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"E"
    )
        port map (
      I0 => Q(13),
      I1 => Saturation1_out110_in,
      O => \minus_out1_1[5]_i_3_n_0\
    );
\minus_out1_1[6]_i_1__1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"02"
    )
        port map (
      I0 => \^min_pulse_width_axi_1_reg[5]\,
      I1 => Saturation1_out110_in,
      I2 => Q(13),
      O => minus_out1(6)
    );
\minus_out1_1[6]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"00000001FFFFFFFE"
    )
        port map (
      I0 => Q(5),
      I1 => Q(3),
      I2 => \^min_pulse_width_axi_1_reg[0]\,
      I3 => Q(2),
      I4 => Q(4),
      I5 => Q(6),
      O => \^min_pulse_width_axi_1_reg[5]\
    );
\minus_out1_1[7]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"0000001E"
    )
        port map (
      I0 => Q(6),
      I1 => \^min_pulse_width_axi_1_reg[4]\,
      I2 => Q(7),
      I3 => Saturation1_out110_in,
      I4 => Q(13),
      O => minus_out1(7)
    );
\minus_out1_1[8]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"00000000000001FE"
    )
        port map (
      I0 => Q(7),
      I1 => \^min_pulse_width_axi_1_reg[4]\,
      I2 => Q(6),
      I3 => Q(8),
      I4 => Saturation1_out110_in,
      I5 => Q(13),
      O => minus_out1(8)
    );
\minus_out1_1[8]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFFFFFFFFFFFFFE"
    )
        port map (
      I0 => Q(4),
      I1 => Q(2),
      I2 => Q(0),
      I3 => Q(1),
      I4 => Q(3),
      I5 => Q(5),
      O => \^min_pulse_width_axi_1_reg[4]\
    );
\minus_out1_1[9]_i_1__1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"02"
    )
        port map (
      I0 => \^min_pulse_width_axi_1_reg[8]\,
      I1 => Saturation1_out110_in,
      I2 => Q(13),
      O => minus_out1(9)
    );
\minus_out1_1[9]_i_2\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"0001FFFE"
    )
        port map (
      I0 => Q(8),
      I1 => Q(6),
      I2 => \^min_pulse_width_axi_1_reg[4]\,
      I3 => Q(7),
      I4 => Q(9),
      O => \^min_pulse_width_axi_1_reg[8]\
    );
\minus_out1_1_reg[10]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => minus_out1(10),
      Q => minus_out1_1(10),
      R => RSTP
    );
\minus_out1_1_reg[11]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => minus_out1(11),
      Q => minus_out1_1(11),
      R => RSTP
    );
\minus_out1_1_reg[12]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => minus_out1(12),
      Q => minus_out1_1(12),
      R => RSTP
    );
\minus_out1_1_reg[13]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => minus_out1(13),
      Q => minus_out1_1(13),
      R => RSTP
    );
\minus_out1_1_reg[13]_i_3\: unisim.vcomponents.CARRY8
     port map (
      CI => '0',
      CI_TOP => '0',
      CO(7) => \NLW_minus_out1_1_reg[13]_i_3_CO_UNCONNECTED\(7),
      CO(6) => Saturation1_out110_in,
      CO(5) => \minus_out1_1_reg[13]_i_3_n_2\,
      CO(4) => \minus_out1_1_reg[13]_i_3_n_3\,
      CO(3) => \minus_out1_1_reg[13]_i_3_n_4\,
      CO(2) => \minus_out1_1_reg[13]_i_3_n_5\,
      CO(1) => \minus_out1_1_reg[13]_i_3_n_6\,
      CO(0) => \minus_out1_1_reg[13]_i_3_n_7\,
      DI(7 downto 6) => B"00",
      DI(5) => \minus_out1_1[13]_i_4__0_n_0\,
      DI(4) => \minus_out1_1[13]_i_5__0_n_0\,
      DI(3) => \minus_out1_1[13]_i_6__0_n_0\,
      DI(2) => \minus_out1_1[13]_i_7__0_n_0\,
      DI(1) => \minus_out1_1[13]_i_8_n_0\,
      DI(0) => \minus_out1_1[13]_i_9_n_0\,
      O(7 downto 0) => \NLW_minus_out1_1_reg[13]_i_3_O_UNCONNECTED\(7 downto 0),
      S(7) => '0',
      S(6) => \minus_out1_1[13]_i_10__0_n_0\,
      S(5) => \minus_out1_1[13]_i_11__0_n_0\,
      S(4) => \minus_out1_1[13]_i_12__0_n_0\,
      S(3) => \minus_out1_1[13]_i_13__0_n_0\,
      S(2) => \minus_out1_1[13]_i_14__0_n_0\,
      S(1) => \minus_out1_1[13]_i_15__1_n_0\,
      S(0) => \minus_out1_1[13]_i_16_n_0\
    );
\minus_out1_1_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => minus_out1(1),
      Q => minus_out1_1(1),
      R => RSTP
    );
\minus_out1_1_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => minus_out1(2),
      Q => minus_out1_1(2),
      R => RSTP
    );
\minus_out1_1_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => minus_out1(3),
      Q => minus_out1_1(3),
      R => RSTP
    );
\minus_out1_1_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => minus_out1(4),
      Q => minus_out1_1(4),
      R => RSTP
    );
\minus_out1_1_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => minus_out1(5),
      Q => minus_out1_1(5),
      R => RSTP
    );
\minus_out1_1_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => minus_out1(6),
      Q => minus_out1_1(6),
      R => RSTP
    );
\minus_out1_1_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => minus_out1(7),
      Q => minus_out1_1(7),
      R => RSTP
    );
\minus_out1_1_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => minus_out1(8),
      Q => minus_out1_1(8),
      R => RSTP
    );
\minus_out1_1_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => minus_out1(9),
      Q => minus_out1_1(9),
      R => RSTP
    );
\modulating_signal_in_clock_cycles_1_reg_i_10__1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFFF4540"
    )
        port map (
      I0 => \Logical_Operator_out1__1\,
      I1 => \Delay_out1_reg[13]_0\(4),
      I2 => \^or_out1__0\,
      I3 => \Delay_out1_reg[13]\(4),
      I4 => modulating_signal_in_clock_cycles_1_reg_i_17_n_0,
      O => B(4)
    );
\modulating_signal_in_clock_cycles_1_reg_i_11__1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"BABBBAAA"
    )
        port map (
      I0 => modulating_signal_in_clock_cycles_1_reg_i_18_n_0,
      I1 => \Logical_Operator_out1__1\,
      I2 => \Delay_out1_reg[13]_0\(3),
      I3 => \^or_out1__0\,
      I4 => \Delay_out1_reg[13]\(3),
      O => B(3)
    );
\modulating_signal_in_clock_cycles_1_reg_i_12__1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFFF4540"
    )
        port map (
      I0 => \Logical_Operator_out1__1\,
      I1 => \Delay_out1_reg[13]_0\(2),
      I2 => \^or_out1__0\,
      I3 => \Delay_out1_reg[13]\(2),
      I4 => modulating_signal_in_clock_cycles_1_reg_i_17_n_0,
      O => B(2)
    );
\modulating_signal_in_clock_cycles_1_reg_i_13__1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFFF4540"
    )
        port map (
      I0 => \Logical_Operator_out1__1\,
      I1 => \Delay_out1_reg[13]_0\(1),
      I2 => \^or_out1__0\,
      I3 => \Delay_out1_reg[13]\(1),
      I4 => modulating_signal_in_clock_cycles_1_reg_i_17_n_0,
      O => B(1)
    );
\modulating_signal_in_clock_cycles_1_reg_i_14__1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"00FFFFFFB8B8B8B8"
    )
        port map (
      I0 => \Delay_out1_reg[13]_0\(0),
      I1 => \^or_out1__0\,
      I2 => \Delay_out1_reg[13]\(0),
      I3 => Relational_Operator1_relop1,
      I4 => Relational_Operator_relop1,
      I5 => \Logical_Operator_out1__1\,
      O => B(0)
    );
modulating_signal_in_clock_cycles_1_reg_i_15: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FEEE"
    )
        port map (
      I0 => Relational_Operator2_relop1,
      I1 => Relational_Operator3_relop1,
      I2 => Relational_Operator_relop1,
      I3 => Relational_Operator1_relop1,
      O => \Logical_Operator_out1__1\
    );
modulating_signal_in_clock_cycles_1_reg_i_16: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFFFFFF00008000"
    )
        port map (
      I0 => \^hdl_counter2_count_reg[11]_0\,
      I1 => \Delay_out1_reg[0]\,
      I2 => \Delay_out1_reg[0]_0\,
      I3 => D(0),
      I4 => HDL_Counter2_count_reg(11),
      I5 => CO(0),
      O => \^or_out1__0\
    );
modulating_signal_in_clock_cycles_1_reg_i_17: unisim.vcomponents.LUT3
    generic map(
      INIT => X"70"
    )
        port map (
      I0 => Relational_Operator1_relop1,
      I1 => Relational_Operator_relop1,
      I2 => Relational_Operator2_relop1,
      O => modulating_signal_in_clock_cycles_1_reg_i_17_n_0
    );
modulating_signal_in_clock_cycles_1_reg_i_18: unisim.vcomponents.LUT4
    generic map(
      INIT => X"0070"
    )
        port map (
      I0 => Relational_Operator1_relop1,
      I1 => Relational_Operator_relop1,
      I2 => Relational_Operator3_relop1,
      I3 => Relational_Operator2_relop1,
      O => modulating_signal_in_clock_cycles_1_reg_i_18_n_0
    );
\modulating_signal_in_clock_cycles_1_reg_i_1__1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFFF4540"
    )
        port map (
      I0 => \Logical_Operator_out1__1\,
      I1 => \Delay_out1_reg[13]_0\(13),
      I2 => \^or_out1__0\,
      I3 => \Delay_out1_reg[13]\(13),
      I4 => modulating_signal_in_clock_cycles_1_reg_i_17_n_0,
      O => B(13)
    );
\modulating_signal_in_clock_cycles_1_reg_i_2__1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"BABBBAAA"
    )
        port map (
      I0 => modulating_signal_in_clock_cycles_1_reg_i_18_n_0,
      I1 => \Logical_Operator_out1__1\,
      I2 => \Delay_out1_reg[13]_0\(12),
      I3 => \^or_out1__0\,
      I4 => \Delay_out1_reg[13]\(12),
      O => B(12)
    );
\modulating_signal_in_clock_cycles_1_reg_i_3__1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFFF4540"
    )
        port map (
      I0 => \Logical_Operator_out1__1\,
      I1 => \Delay_out1_reg[13]_0\(11),
      I2 => \^or_out1__0\,
      I3 => \Delay_out1_reg[13]\(11),
      I4 => modulating_signal_in_clock_cycles_1_reg_i_17_n_0,
      O => B(11)
    );
\modulating_signal_in_clock_cycles_1_reg_i_4__1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFFF4540"
    )
        port map (
      I0 => \Logical_Operator_out1__1\,
      I1 => \Delay_out1_reg[13]_0\(10),
      I2 => \^or_out1__0\,
      I3 => \Delay_out1_reg[13]\(10),
      I4 => modulating_signal_in_clock_cycles_1_reg_i_17_n_0,
      O => B(10)
    );
\modulating_signal_in_clock_cycles_1_reg_i_5__1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFFF4540"
    )
        port map (
      I0 => \Logical_Operator_out1__1\,
      I1 => \Delay_out1_reg[13]_0\(9),
      I2 => \^or_out1__0\,
      I3 => \Delay_out1_reg[13]\(9),
      I4 => modulating_signal_in_clock_cycles_1_reg_i_17_n_0,
      O => B(9)
    );
\modulating_signal_in_clock_cycles_1_reg_i_6__1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFFF4540"
    )
        port map (
      I0 => \Logical_Operator_out1__1\,
      I1 => \Delay_out1_reg[13]_0\(8),
      I2 => \^or_out1__0\,
      I3 => \Delay_out1_reg[13]\(8),
      I4 => modulating_signal_in_clock_cycles_1_reg_i_17_n_0,
      O => B(8)
    );
\modulating_signal_in_clock_cycles_1_reg_i_7__1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFFF4540"
    )
        port map (
      I0 => \Logical_Operator_out1__1\,
      I1 => \Delay_out1_reg[13]_0\(7),
      I2 => \^or_out1__0\,
      I3 => \Delay_out1_reg[13]\(7),
      I4 => modulating_signal_in_clock_cycles_1_reg_i_17_n_0,
      O => B(7)
    );
\modulating_signal_in_clock_cycles_1_reg_i_8__1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFFF4540"
    )
        port map (
      I0 => \Logical_Operator_out1__1\,
      I1 => \Delay_out1_reg[13]_0\(6),
      I2 => \^or_out1__0\,
      I3 => \Delay_out1_reg[13]\(6),
      I4 => modulating_signal_in_clock_cycles_1_reg_i_17_n_0,
      O => B(6)
    );
\modulating_signal_in_clock_cycles_1_reg_i_9__1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"BABBBAAA"
    )
        port map (
      I0 => modulating_signal_in_clock_cycles_1_reg_i_18_n_0,
      I1 => \Logical_Operator_out1__1\,
      I2 => \Delay_out1_reg[13]_0\(5),
      I3 => \^or_out1__0\,
      I4 => \Delay_out1_reg[13]\(5),
      O => B(5)
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity zusys_PWM_SS_3L_ip_0_0_PWM_SS_3L_ip_src_LimitPulseWidth_b is
  port (
    \delayMatch3_reg_reg[1][13]\ : out STD_LOGIC;
    PWM_en_AXI_2_reg : out STD_LOGIC;
    B : out STD_LOGIC_VECTOR ( 13 downto 0 );
    \delayMatch3_reg_reg[1][11]\ : out STD_LOGIC;
    \delayMatch3_reg_reg[1][9]\ : out STD_LOGIC;
    \delayMatch3_reg_reg[1][7]\ : out STD_LOGIC;
    \delayMatch3_reg_reg[1][5]\ : out STD_LOGIC;
    \delayMatch3_reg_reg[1][3]\ : out STD_LOGIC;
    \delayMatch3_reg_reg[1][1]\ : out STD_LOGIC;
    RSTP : in STD_LOGIC;
    CEP : in STD_LOGIC;
    IPCORE_CLK : in STD_LOGIC;
    Q : in STD_LOGIC_VECTOR ( 13 downto 0 );
    \minus_out1_1_reg[7]_0\ : in STD_LOGIC;
    \minus_out1_1_reg[12]_0\ : in STD_LOGIC;
    \Delay1_out1_reg[13]\ : in STD_LOGIC_VECTOR ( 13 downto 0 );
    \Delay1_out1_reg[13]_0\ : in STD_LOGIC_VECTOR ( 13 downto 0 );
    \Delay1_out1_reg[13]_1\ : in STD_LOGIC;
    D : in STD_LOGIC_VECTOR ( 0 to 0 );
    HDL_Counter2_count_reg : in STD_LOGIC_VECTOR ( 0 to 0 );
    CO : in STD_LOGIC_VECTOR ( 0 to 0 );
    \Delay1_out1_reg[0]\ : in STD_LOGIC;
    \Delay1_out1_reg[0]_0\ : in STD_LOGIC;
    \Delay1_out1_reg[0]_1\ : in STD_LOGIC;
    \minus_out1_1_reg[5]_0\ : in STD_LOGIC;
    \minus_out1_1_reg[6]_0\ : in STD_LOGIC;
    \minus_out1_1_reg[9]_0\ : in STD_LOGIC;
    \minus_out1_1_reg[10]_0\ : in STD_LOGIC;
    \minus_out1_1_reg[11]_0\ : in STD_LOGIC
  );
  attribute ORIG_REF_NAME : string;
  attribute ORIG_REF_NAME of zusys_PWM_SS_3L_ip_0_0_PWM_SS_3L_ip_src_LimitPulseWidth_b : entity is "PWM_SS_3L_ip_src_LimitPulseWidth_b";
end zusys_PWM_SS_3L_ip_0_0_PWM_SS_3L_ip_src_LimitPulseWidth_b;

architecture STRUCTURE of zusys_PWM_SS_3L_ip_0_0_PWM_SS_3L_ip_src_LimitPulseWidth_b is
  signal Add1_out1 : STD_LOGIC_VECTOR ( 13 downto 11 );
  signal Add1_out1_1 : STD_LOGIC_VECTOR ( 13 downto 0 );
  signal \Add1_out1_1[13]_i_2__0_n_0\ : STD_LOGIC;
  signal \Add1_out1_1[13]_i_3__0_n_0\ : STD_LOGIC;
  signal \Add1_out1_1[13]_i_4__0_n_0\ : STD_LOGIC;
  signal \Add1_out1_1_reg[13]_i_1__0_n_6\ : STD_LOGIC;
  signal \Add1_out1_1_reg[13]_i_1__0_n_7\ : STD_LOGIC;
  signal Add2_out1 : STD_LOGIC_VECTOR ( 13 downto 1 );
  signal Add2_out1_1 : STD_LOGIC_VECTOR ( 13 downto 1 );
  signal \Add2_out1_1[13]_i_2__0_n_0\ : STD_LOGIC;
  signal \Add2_out1_1[13]_i_3__0_n_0\ : STD_LOGIC;
  signal \Add2_out1_1[13]_i_4__0_n_0\ : STD_LOGIC;
  signal \Add2_out1_1[13]_i_5__0_n_0\ : STD_LOGIC;
  signal \Add2_out1_1[8]_i_10__0_n_0\ : STD_LOGIC;
  signal \Add2_out1_1[8]_i_2__0_n_0\ : STD_LOGIC;
  signal \Add2_out1_1[8]_i_3__0_n_0\ : STD_LOGIC;
  signal \Add2_out1_1[8]_i_4__0_n_0\ : STD_LOGIC;
  signal \Add2_out1_1[8]_i_5__0_n_0\ : STD_LOGIC;
  signal \Add2_out1_1[8]_i_6__0_n_0\ : STD_LOGIC;
  signal \Add2_out1_1[8]_i_7__0_n_0\ : STD_LOGIC;
  signal \Add2_out1_1[8]_i_8__0_n_0\ : STD_LOGIC;
  signal \Add2_out1_1[8]_i_9__0_n_0\ : STD_LOGIC;
  signal \Add2_out1_1_reg[13]_i_1__0_n_4\ : STD_LOGIC;
  signal \Add2_out1_1_reg[13]_i_1__0_n_5\ : STD_LOGIC;
  signal \Add2_out1_1_reg[13]_i_1__0_n_6\ : STD_LOGIC;
  signal \Add2_out1_1_reg[13]_i_1__0_n_7\ : STD_LOGIC;
  signal \Add2_out1_1_reg[8]_i_1__0_n_0\ : STD_LOGIC;
  signal \Add2_out1_1_reg[8]_i_1__0_n_1\ : STD_LOGIC;
  signal \Add2_out1_1_reg[8]_i_1__0_n_2\ : STD_LOGIC;
  signal \Add2_out1_1_reg[8]_i_1__0_n_3\ : STD_LOGIC;
  signal \Add2_out1_1_reg[8]_i_1__0_n_4\ : STD_LOGIC;
  signal \Add2_out1_1_reg[8]_i_1__0_n_5\ : STD_LOGIC;
  signal \Add2_out1_1_reg[8]_i_1__0_n_6\ : STD_LOGIC;
  signal \Add2_out1_1_reg[8]_i_1__0_n_7\ : STD_LOGIC;
  signal \Logical_Operator1_out10_carry_i_10__0_n_0\ : STD_LOGIC;
  signal \Logical_Operator1_out10_carry_i_11__0_n_0\ : STD_LOGIC;
  signal \Logical_Operator1_out10_carry_i_12__0_n_0\ : STD_LOGIC;
  signal \Logical_Operator1_out10_carry_i_13__0_n_0\ : STD_LOGIC;
  signal \Logical_Operator1_out10_carry_i_14__0_n_0\ : STD_LOGIC;
  signal \Logical_Operator1_out10_carry_i_1__0_n_0\ : STD_LOGIC;
  signal \Logical_Operator1_out10_carry_i_2__0_n_0\ : STD_LOGIC;
  signal \Logical_Operator1_out10_carry_i_3__0_n_0\ : STD_LOGIC;
  signal \Logical_Operator1_out10_carry_i_4__0_n_0\ : STD_LOGIC;
  signal \Logical_Operator1_out10_carry_i_5__0_n_0\ : STD_LOGIC;
  signal \Logical_Operator1_out10_carry_i_6__0_n_0\ : STD_LOGIC;
  signal \Logical_Operator1_out10_carry_i_7__0_n_0\ : STD_LOGIC;
  signal \Logical_Operator1_out10_carry_i_8__0_n_0\ : STD_LOGIC;
  signal \Logical_Operator1_out10_carry_i_9__0_n_0\ : STD_LOGIC;
  signal Logical_Operator1_out10_carry_n_2 : STD_LOGIC;
  signal Logical_Operator1_out10_carry_n_3 : STD_LOGIC;
  signal Logical_Operator1_out10_carry_n_4 : STD_LOGIC;
  signal Logical_Operator1_out10_carry_n_5 : STD_LOGIC;
  signal Logical_Operator1_out10_carry_n_6 : STD_LOGIC;
  signal Logical_Operator1_out10_carry_n_7 : STD_LOGIC;
  signal \Logical_Operator1_out10_inferred__0/i__carry_n_2\ : STD_LOGIC;
  signal \Logical_Operator1_out10_inferred__0/i__carry_n_3\ : STD_LOGIC;
  signal \Logical_Operator1_out10_inferred__0/i__carry_n_4\ : STD_LOGIC;
  signal \Logical_Operator1_out10_inferred__0/i__carry_n_5\ : STD_LOGIC;
  signal \Logical_Operator1_out10_inferred__0/i__carry_n_6\ : STD_LOGIC;
  signal \Logical_Operator1_out10_inferred__0/i__carry_n_7\ : STD_LOGIC;
  signal \Logical_Operator_out10_carry_i_10__0_n_0\ : STD_LOGIC;
  signal \Logical_Operator_out10_carry_i_11__0_n_0\ : STD_LOGIC;
  signal \Logical_Operator_out10_carry_i_12__0_n_0\ : STD_LOGIC;
  signal \Logical_Operator_out10_carry_i_13__0_n_0\ : STD_LOGIC;
  signal \Logical_Operator_out10_carry_i_14__0_n_0\ : STD_LOGIC;
  signal \Logical_Operator_out10_carry_i_1__0_n_0\ : STD_LOGIC;
  signal \Logical_Operator_out10_carry_i_2__0_n_0\ : STD_LOGIC;
  signal \Logical_Operator_out10_carry_i_3__0_n_0\ : STD_LOGIC;
  signal \Logical_Operator_out10_carry_i_4__0_n_0\ : STD_LOGIC;
  signal \Logical_Operator_out10_carry_i_5__0_n_0\ : STD_LOGIC;
  signal \Logical_Operator_out10_carry_i_6__0_n_0\ : STD_LOGIC;
  signal \Logical_Operator_out10_carry_i_7__0_n_0\ : STD_LOGIC;
  signal \Logical_Operator_out10_carry_i_8__0_n_0\ : STD_LOGIC;
  signal \Logical_Operator_out10_carry_i_9__0_n_0\ : STD_LOGIC;
  signal Logical_Operator_out10_carry_n_2 : STD_LOGIC;
  signal Logical_Operator_out10_carry_n_3 : STD_LOGIC;
  signal Logical_Operator_out10_carry_n_4 : STD_LOGIC;
  signal Logical_Operator_out10_carry_n_5 : STD_LOGIC;
  signal Logical_Operator_out10_carry_n_6 : STD_LOGIC;
  signal Logical_Operator_out10_carry_n_7 : STD_LOGIC;
  signal \Logical_Operator_out11_carry_i_1__0_n_0\ : STD_LOGIC;
  signal \Logical_Operator_out11_carry_i_2__0_n_0\ : STD_LOGIC;
  signal \Logical_Operator_out11_carry_i_3__0_n_0\ : STD_LOGIC;
  signal \Logical_Operator_out11_carry_i_4__0_n_0\ : STD_LOGIC;
  signal \Logical_Operator_out11_carry_i_5__0_n_0\ : STD_LOGIC;
  signal \Logical_Operator_out11_carry_i_6__0_n_0\ : STD_LOGIC;
  signal \Logical_Operator_out11_carry_i_7__0_n_0\ : STD_LOGIC;
  signal \Logical_Operator_out11_carry_i_8__0_n_0\ : STD_LOGIC;
  signal \Logical_Operator_out11_carry_i_9__0_n_0\ : STD_LOGIC;
  signal Logical_Operator_out11_carry_n_2 : STD_LOGIC;
  signal Logical_Operator_out11_carry_n_3 : STD_LOGIC;
  signal Logical_Operator_out11_carry_n_4 : STD_LOGIC;
  signal Logical_Operator_out11_carry_n_5 : STD_LOGIC;
  signal Logical_Operator_out11_carry_n_6 : STD_LOGIC;
  signal Logical_Operator_out11_carry_n_7 : STD_LOGIC;
  signal \Logical_Operator_out1__1\ : STD_LOGIC;
  signal \^pwm_en_axi_2_reg\ : STD_LOGIC;
  signal Relational_Operator1_relop1 : STD_LOGIC;
  signal Relational_Operator2_relop1 : STD_LOGIC;
  signal Relational_Operator3_relop1 : STD_LOGIC;
  signal Relational_Operator_relop1 : STD_LOGIC;
  signal Saturation1_out1 : STD_LOGIC_VECTOR ( 12 downto 0 );
  signal Saturation1_out110_in : STD_LOGIC;
  signal Saturation1_out1_1 : STD_LOGIC_VECTOR ( 12 downto 11 );
  signal \^delaymatch3_reg_reg[1][11]\ : STD_LOGIC;
  signal \^delaymatch3_reg_reg[1][13]\ : STD_LOGIC;
  signal \^delaymatch3_reg_reg[1][1]\ : STD_LOGIC;
  signal \^delaymatch3_reg_reg[1][3]\ : STD_LOGIC;
  signal \^delaymatch3_reg_reg[1][5]\ : STD_LOGIC;
  signal \^delaymatch3_reg_reg[1][7]\ : STD_LOGIC;
  signal \^delaymatch3_reg_reg[1][9]\ : STD_LOGIC;
  signal \i__carry_i_10__0_n_0\ : STD_LOGIC;
  signal \i__carry_i_11__0_n_0\ : STD_LOGIC;
  signal \i__carry_i_12__0_n_0\ : STD_LOGIC;
  signal \i__carry_i_13__0_n_0\ : STD_LOGIC;
  signal \i__carry_i_14__0_n_0\ : STD_LOGIC;
  signal \i__carry_i_1__0_n_0\ : STD_LOGIC;
  signal \i__carry_i_2__0_n_0\ : STD_LOGIC;
  signal \i__carry_i_3__0_n_0\ : STD_LOGIC;
  signal \i__carry_i_4__0_n_0\ : STD_LOGIC;
  signal \i__carry_i_5__0_n_0\ : STD_LOGIC;
  signal \i__carry_i_6__0_n_0\ : STD_LOGIC;
  signal \i__carry_i_7__0_n_0\ : STD_LOGIC;
  signal \i__carry_i_8__0_n_0\ : STD_LOGIC;
  signal \i__carry_i_9__0_n_0\ : STD_LOGIC;
  signal minus_out1 : STD_LOGIC_VECTOR ( 13 downto 1 );
  signal minus_out1_1 : STD_LOGIC_VECTOR ( 13 downto 1 );
  signal \minus_out1_1[13]_i_10__1_n_0\ : STD_LOGIC;
  signal \minus_out1_1[13]_i_11__1_n_0\ : STD_LOGIC;
  signal \minus_out1_1[13]_i_12__1_n_0\ : STD_LOGIC;
  signal \minus_out1_1[13]_i_13__1_n_0\ : STD_LOGIC;
  signal \minus_out1_1[13]_i_14__1_n_0\ : STD_LOGIC;
  signal \minus_out1_1[13]_i_15__0_n_0\ : STD_LOGIC;
  signal \minus_out1_1[13]_i_3__0_n_0\ : STD_LOGIC;
  signal \minus_out1_1[13]_i_4__1_n_0\ : STD_LOGIC;
  signal \minus_out1_1[13]_i_5__1_n_0\ : STD_LOGIC;
  signal \minus_out1_1[13]_i_6__1_n_0\ : STD_LOGIC;
  signal \minus_out1_1[13]_i_7__1_n_0\ : STD_LOGIC;
  signal \minus_out1_1[13]_i_8__0_n_0\ : STD_LOGIC;
  signal \minus_out1_1[13]_i_9__1_n_0\ : STD_LOGIC;
  signal \minus_out1_1[5]_i_2__0_n_0\ : STD_LOGIC;
  signal \minus_out1_1_reg[13]_i_2_n_2\ : STD_LOGIC;
  signal \minus_out1_1_reg[13]_i_2_n_3\ : STD_LOGIC;
  signal \minus_out1_1_reg[13]_i_2_n_4\ : STD_LOGIC;
  signal \minus_out1_1_reg[13]_i_2_n_5\ : STD_LOGIC;
  signal \minus_out1_1_reg[13]_i_2_n_6\ : STD_LOGIC;
  signal \minus_out1_1_reg[13]_i_2_n_7\ : STD_LOGIC;
  signal \modulating_signal_in_clock_cycles_1_reg_i_17__0_n_0\ : STD_LOGIC;
  signal \modulating_signal_in_clock_cycles_1_reg_i_18__0_n_0\ : STD_LOGIC;
  signal \NLW_Add1_out1_1_reg[13]_i_1__0_CO_UNCONNECTED\ : STD_LOGIC_VECTOR ( 7 downto 2 );
  signal \NLW_Add1_out1_1_reg[13]_i_1__0_O_UNCONNECTED\ : STD_LOGIC_VECTOR ( 7 downto 3 );
  signal \NLW_Add2_out1_1_reg[13]_i_1__0_CO_UNCONNECTED\ : STD_LOGIC_VECTOR ( 7 downto 4 );
  signal \NLW_Add2_out1_1_reg[13]_i_1__0_O_UNCONNECTED\ : STD_LOGIC_VECTOR ( 7 downto 5 );
  signal NLW_Logical_Operator1_out10_carry_CO_UNCONNECTED : STD_LOGIC_VECTOR ( 7 to 7 );
  signal NLW_Logical_Operator1_out10_carry_O_UNCONNECTED : STD_LOGIC_VECTOR ( 7 downto 0 );
  signal \NLW_Logical_Operator1_out10_inferred__0/i__carry_CO_UNCONNECTED\ : STD_LOGIC_VECTOR ( 7 to 7 );
  signal \NLW_Logical_Operator1_out10_inferred__0/i__carry_O_UNCONNECTED\ : STD_LOGIC_VECTOR ( 7 downto 0 );
  signal NLW_Logical_Operator_out10_carry_CO_UNCONNECTED : STD_LOGIC_VECTOR ( 7 to 7 );
  signal NLW_Logical_Operator_out10_carry_O_UNCONNECTED : STD_LOGIC_VECTOR ( 7 downto 0 );
  signal NLW_Logical_Operator_out11_carry_CO_UNCONNECTED : STD_LOGIC_VECTOR ( 7 to 7 );
  signal NLW_Logical_Operator_out11_carry_O_UNCONNECTED : STD_LOGIC_VECTOR ( 7 downto 0 );
  signal \NLW_minus_out1_1_reg[13]_i_2_CO_UNCONNECTED\ : STD_LOGIC_VECTOR ( 7 to 7 );
  signal \NLW_minus_out1_1_reg[13]_i_2_O_UNCONNECTED\ : STD_LOGIC_VECTOR ( 7 downto 0 );
  attribute SOFT_HLUTNM : string;
  attribute SOFT_HLUTNM of \Add1_out1_1[0]_i_1__0\ : label is "soft_lutpair32";
  attribute SOFT_HLUTNM of \Add1_out1_1[10]_i_1__0\ : label is "soft_lutpair37";
  attribute SOFT_HLUTNM of \Add1_out1_1[1]_i_1__0\ : label is "soft_lutpair33";
  attribute SOFT_HLUTNM of \Add1_out1_1[2]_i_1__0\ : label is "soft_lutpair33";
  attribute SOFT_HLUTNM of \Add1_out1_1[3]_i_1__0\ : label is "soft_lutpair34";
  attribute SOFT_HLUTNM of \Add1_out1_1[4]_i_1__0\ : label is "soft_lutpair34";
  attribute SOFT_HLUTNM of \Add1_out1_1[5]_i_1__0\ : label is "soft_lutpair35";
  attribute SOFT_HLUTNM of \Add1_out1_1[6]_i_1__0\ : label is "soft_lutpair26";
  attribute SOFT_HLUTNM of \Add1_out1_1[7]_i_1__0\ : label is "soft_lutpair35";
  attribute SOFT_HLUTNM of \Add1_out1_1[8]_i_1__0\ : label is "soft_lutpair36";
  attribute SOFT_HLUTNM of \Add1_out1_1[9]_i_1__0\ : label is "soft_lutpair36";
  attribute ADDER_THRESHOLD : integer;
  attribute ADDER_THRESHOLD of \Add1_out1_1_reg[13]_i_1__0\ : label is 35;
  attribute ADDER_THRESHOLD of \Add2_out1_1_reg[13]_i_1__0\ : label is 35;
  attribute ADDER_THRESHOLD of \Add2_out1_1_reg[8]_i_1__0\ : label is 35;
  attribute COMPARATOR_THRESHOLD : integer;
  attribute COMPARATOR_THRESHOLD of Logical_Operator1_out10_carry : label is 11;
  attribute COMPARATOR_THRESHOLD of \Logical_Operator1_out10_inferred__0/i__carry\ : label is 11;
  attribute COMPARATOR_THRESHOLD of Logical_Operator_out10_carry : label is 11;
  attribute COMPARATOR_THRESHOLD of Logical_Operator_out11_carry : label is 11;
  attribute SOFT_HLUTNM of \Saturation1_out1_1[11]_i_1__0\ : label is "soft_lutpair37";
  attribute SOFT_HLUTNM of \Saturation1_out1_1[12]_i_1__0\ : label is "soft_lutpair30";
  attribute SOFT_HLUTNM of \minus_out1_1[10]_i_1__0\ : label is "soft_lutpair31";
  attribute SOFT_HLUTNM of \minus_out1_1[11]_i_1__0\ : label is "soft_lutpair32";
  attribute SOFT_HLUTNM of \minus_out1_1[12]_i_1__0\ : label is "soft_lutpair27";
  attribute SOFT_HLUTNM of \minus_out1_1[13]_i_1__0\ : label is "soft_lutpair27";
  attribute SOFT_HLUTNM of \minus_out1_1[1]_i_1__0\ : label is "soft_lutpair28";
  attribute SOFT_HLUTNM of \minus_out1_1[2]_i_1__0\ : label is "soft_lutpair28";
  attribute SOFT_HLUTNM of \minus_out1_1[6]_i_1__0\ : label is "soft_lutpair30";
  attribute SOFT_HLUTNM of \minus_out1_1[7]_i_1__0\ : label is "soft_lutpair26";
  attribute SOFT_HLUTNM of \minus_out1_1[9]_i_1__0\ : label is "soft_lutpair31";
  attribute COMPARATOR_THRESHOLD of \minus_out1_1_reg[13]_i_2\ : label is 11;
  attribute SOFT_HLUTNM of \modulating_signal_in_clock_cycles_1_reg_i_15__0\ : label is "soft_lutpair29";
  attribute SOFT_HLUTNM of \modulating_signal_in_clock_cycles_1_reg_i_18__0\ : label is "soft_lutpair29";
begin
  PWM_en_AXI_2_reg <= \^pwm_en_axi_2_reg\;
  \delayMatch3_reg_reg[1][11]\ <= \^delaymatch3_reg_reg[1][11]\;
  \delayMatch3_reg_reg[1][13]\ <= \^delaymatch3_reg_reg[1][13]\;
  \delayMatch3_reg_reg[1][1]\ <= \^delaymatch3_reg_reg[1][1]\;
  \delayMatch3_reg_reg[1][3]\ <= \^delaymatch3_reg_reg[1][3]\;
  \delayMatch3_reg_reg[1][5]\ <= \^delaymatch3_reg_reg[1][5]\;
  \delayMatch3_reg_reg[1][7]\ <= \^delaymatch3_reg_reg[1][7]\;
  \delayMatch3_reg_reg[1][9]\ <= \^delaymatch3_reg_reg[1][9]\;
\Add1_out1_1[0]_i_1__0\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"02"
    )
        port map (
      I0 => Q(0),
      I1 => Saturation1_out110_in,
      I2 => Q(13),
      O => Saturation1_out1(0)
    );
\Add1_out1_1[10]_i_1__0\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"02"
    )
        port map (
      I0 => Q(10),
      I1 => Saturation1_out110_in,
      I2 => Q(13),
      O => Saturation1_out1(10)
    );
\Add1_out1_1[13]_i_2__0\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"BA"
    )
        port map (
      I0 => Saturation1_out110_in,
      I1 => Q(13),
      I2 => Q(12),
      O => \Add1_out1_1[13]_i_2__0_n_0\
    );
\Add1_out1_1[13]_i_3__0\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"0D"
    )
        port map (
      I0 => Q(12),
      I1 => Q(13),
      I2 => Saturation1_out110_in,
      O => \Add1_out1_1[13]_i_3__0_n_0\
    );
\Add1_out1_1[13]_i_4__0\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"02"
    )
        port map (
      I0 => Q(11),
      I1 => Saturation1_out110_in,
      I2 => Q(13),
      O => \Add1_out1_1[13]_i_4__0_n_0\
    );
\Add1_out1_1[1]_i_1__0\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"02"
    )
        port map (
      I0 => Q(1),
      I1 => Saturation1_out110_in,
      I2 => Q(13),
      O => Saturation1_out1(1)
    );
\Add1_out1_1[2]_i_1__0\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"02"
    )
        port map (
      I0 => Q(2),
      I1 => Saturation1_out110_in,
      I2 => Q(13),
      O => Saturation1_out1(2)
    );
\Add1_out1_1[3]_i_1__0\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"02"
    )
        port map (
      I0 => Q(3),
      I1 => Saturation1_out110_in,
      I2 => Q(13),
      O => Saturation1_out1(3)
    );
\Add1_out1_1[4]_i_1__0\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"02"
    )
        port map (
      I0 => Q(4),
      I1 => Saturation1_out110_in,
      I2 => Q(13),
      O => Saturation1_out1(4)
    );
\Add1_out1_1[5]_i_1__0\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"02"
    )
        port map (
      I0 => Q(5),
      I1 => Saturation1_out110_in,
      I2 => Q(13),
      O => Saturation1_out1(5)
    );
\Add1_out1_1[6]_i_1__0\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"02"
    )
        port map (
      I0 => Q(6),
      I1 => Saturation1_out110_in,
      I2 => Q(13),
      O => Saturation1_out1(6)
    );
\Add1_out1_1[7]_i_1__0\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"02"
    )
        port map (
      I0 => Q(7),
      I1 => Saturation1_out110_in,
      I2 => Q(13),
      O => Saturation1_out1(7)
    );
\Add1_out1_1[8]_i_1__0\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"02"
    )
        port map (
      I0 => Q(8),
      I1 => Saturation1_out110_in,
      I2 => Q(13),
      O => Saturation1_out1(8)
    );
\Add1_out1_1[9]_i_1__0\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"02"
    )
        port map (
      I0 => Q(9),
      I1 => Saturation1_out110_in,
      I2 => Q(13),
      O => Saturation1_out1(9)
    );
\Add1_out1_1_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => Saturation1_out1(0),
      Q => Add1_out1_1(0),
      R => RSTP
    );
\Add1_out1_1_reg[10]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => Saturation1_out1(10),
      Q => Add1_out1_1(10),
      R => RSTP
    );
\Add1_out1_1_reg[11]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => Add1_out1(11),
      Q => Add1_out1_1(11),
      R => RSTP
    );
\Add1_out1_1_reg[12]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => Add1_out1(12),
      Q => Add1_out1_1(12),
      R => RSTP
    );
\Add1_out1_1_reg[13]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => Add1_out1(13),
      Q => Add1_out1_1(13),
      R => RSTP
    );
\Add1_out1_1_reg[13]_i_1__0\: unisim.vcomponents.CARRY8
     port map (
      CI => '0',
      CI_TOP => '0',
      CO(7 downto 2) => \NLW_Add1_out1_1_reg[13]_i_1__0_CO_UNCONNECTED\(7 downto 2),
      CO(1) => \Add1_out1_1_reg[13]_i_1__0_n_6\,
      CO(0) => \Add1_out1_1_reg[13]_i_1__0_n_7\,
      DI(7 downto 2) => B"000000",
      DI(1) => \Add1_out1_1[13]_i_2__0_n_0\,
      DI(0) => '0',
      O(7 downto 3) => \NLW_Add1_out1_1_reg[13]_i_1__0_O_UNCONNECTED\(7 downto 3),
      O(2 downto 0) => Add1_out1(13 downto 11),
      S(7 downto 2) => B"000001",
      S(1) => \Add1_out1_1[13]_i_3__0_n_0\,
      S(0) => \Add1_out1_1[13]_i_4__0_n_0\
    );
\Add1_out1_1_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => Saturation1_out1(1),
      Q => Add1_out1_1(1),
      R => RSTP
    );
\Add1_out1_1_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => Saturation1_out1(2),
      Q => Add1_out1_1(2),
      R => RSTP
    );
\Add1_out1_1_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => Saturation1_out1(3),
      Q => Add1_out1_1(3),
      R => RSTP
    );
\Add1_out1_1_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => Saturation1_out1(4),
      Q => Add1_out1_1(4),
      R => RSTP
    );
\Add1_out1_1_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => Saturation1_out1(5),
      Q => Add1_out1_1(5),
      R => RSTP
    );
\Add1_out1_1_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => Saturation1_out1(6),
      Q => Add1_out1_1(6),
      R => RSTP
    );
\Add1_out1_1_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => Saturation1_out1(7),
      Q => Add1_out1_1(7),
      R => RSTP
    );
\Add1_out1_1_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => Saturation1_out1(8),
      Q => Add1_out1_1(8),
      R => RSTP
    );
\Add1_out1_1_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => Saturation1_out1(9),
      Q => Add1_out1_1(9),
      R => RSTP
    );
\Add2_out1_1[13]_i_2__0\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"BA"
    )
        port map (
      I0 => Saturation1_out110_in,
      I1 => Q(13),
      I2 => Q(12),
      O => \Add2_out1_1[13]_i_2__0_n_0\
    );
\Add2_out1_1[13]_i_3__0\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"EF"
    )
        port map (
      I0 => Q(13),
      I1 => Saturation1_out110_in,
      I2 => Q(11),
      O => \Add2_out1_1[13]_i_3__0_n_0\
    );
\Add2_out1_1[13]_i_4__0\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"EF"
    )
        port map (
      I0 => Q(13),
      I1 => Saturation1_out110_in,
      I2 => Q(10),
      O => \Add2_out1_1[13]_i_4__0_n_0\
    );
\Add2_out1_1[13]_i_5__0\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"EF"
    )
        port map (
      I0 => Q(13),
      I1 => Saturation1_out110_in,
      I2 => Q(9),
      O => \Add2_out1_1[13]_i_5__0_n_0\
    );
\Add2_out1_1[8]_i_10__0\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"EF"
    )
        port map (
      I0 => Q(13),
      I1 => Saturation1_out110_in,
      I2 => Q(1),
      O => \Add2_out1_1[8]_i_10__0_n_0\
    );
\Add2_out1_1[8]_i_2__0\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"EF"
    )
        port map (
      I0 => Q(13),
      I1 => Saturation1_out110_in,
      I2 => Q(0),
      O => \Add2_out1_1[8]_i_2__0_n_0\
    );
\Add2_out1_1[8]_i_3__0\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"EF"
    )
        port map (
      I0 => Q(13),
      I1 => Saturation1_out110_in,
      I2 => Q(8),
      O => \Add2_out1_1[8]_i_3__0_n_0\
    );
\Add2_out1_1[8]_i_4__0\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"EF"
    )
        port map (
      I0 => Q(13),
      I1 => Saturation1_out110_in,
      I2 => Q(7),
      O => \Add2_out1_1[8]_i_4__0_n_0\
    );
\Add2_out1_1[8]_i_5__0\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"EF"
    )
        port map (
      I0 => Q(13),
      I1 => Saturation1_out110_in,
      I2 => Q(6),
      O => \Add2_out1_1[8]_i_5__0_n_0\
    );
\Add2_out1_1[8]_i_6__0\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"EF"
    )
        port map (
      I0 => Q(13),
      I1 => Saturation1_out110_in,
      I2 => Q(5),
      O => \Add2_out1_1[8]_i_6__0_n_0\
    );
\Add2_out1_1[8]_i_7__0\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"EF"
    )
        port map (
      I0 => Q(13),
      I1 => Saturation1_out110_in,
      I2 => Q(4),
      O => \Add2_out1_1[8]_i_7__0_n_0\
    );
\Add2_out1_1[8]_i_8__0\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"EF"
    )
        port map (
      I0 => Q(13),
      I1 => Saturation1_out110_in,
      I2 => Q(3),
      O => \Add2_out1_1[8]_i_8__0_n_0\
    );
\Add2_out1_1[8]_i_9__0\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"EF"
    )
        port map (
      I0 => Q(13),
      I1 => Saturation1_out110_in,
      I2 => Q(2),
      O => \Add2_out1_1[8]_i_9__0_n_0\
    );
\Add2_out1_1_reg[10]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => Add2_out1(10),
      Q => Add2_out1_1(10),
      R => RSTP
    );
\Add2_out1_1_reg[11]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => Add2_out1(11),
      Q => Add2_out1_1(11),
      R => RSTP
    );
\Add2_out1_1_reg[12]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => Add2_out1(12),
      Q => Add2_out1_1(12),
      R => RSTP
    );
\Add2_out1_1_reg[13]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => Add2_out1(13),
      Q => Add2_out1_1(13),
      R => RSTP
    );
\Add2_out1_1_reg[13]_i_1__0\: unisim.vcomponents.CARRY8
     port map (
      CI => \Add2_out1_1_reg[8]_i_1__0_n_0\,
      CI_TOP => '0',
      CO(7 downto 4) => \NLW_Add2_out1_1_reg[13]_i_1__0_CO_UNCONNECTED\(7 downto 4),
      CO(3) => \Add2_out1_1_reg[13]_i_1__0_n_4\,
      CO(2) => \Add2_out1_1_reg[13]_i_1__0_n_5\,
      CO(1) => \Add2_out1_1_reg[13]_i_1__0_n_6\,
      CO(0) => \Add2_out1_1_reg[13]_i_1__0_n_7\,
      DI(7 downto 0) => B"00001000",
      O(7 downto 5) => \NLW_Add2_out1_1_reg[13]_i_1__0_O_UNCONNECTED\(7 downto 5),
      O(4 downto 0) => Add2_out1(13 downto 9),
      S(7 downto 4) => B"0001",
      S(3) => \Add2_out1_1[13]_i_2__0_n_0\,
      S(2) => \Add2_out1_1[13]_i_3__0_n_0\,
      S(1) => \Add2_out1_1[13]_i_4__0_n_0\,
      S(0) => \Add2_out1_1[13]_i_5__0_n_0\
    );
\Add2_out1_1_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => Add2_out1(1),
      Q => Add2_out1_1(1),
      R => RSTP
    );
\Add2_out1_1_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => Add2_out1(2),
      Q => Add2_out1_1(2),
      R => RSTP
    );
\Add2_out1_1_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => Add2_out1(3),
      Q => Add2_out1_1(3),
      R => RSTP
    );
\Add2_out1_1_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => Add2_out1(4),
      Q => Add2_out1_1(4),
      R => RSTP
    );
\Add2_out1_1_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => Add2_out1(5),
      Q => Add2_out1_1(5),
      R => RSTP
    );
\Add2_out1_1_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => Add2_out1(6),
      Q => Add2_out1_1(6),
      R => RSTP
    );
\Add2_out1_1_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => Add2_out1(7),
      Q => Add2_out1_1(7),
      R => RSTP
    );
\Add2_out1_1_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => Add2_out1(8),
      Q => Add2_out1_1(8),
      R => RSTP
    );
\Add2_out1_1_reg[8]_i_1__0\: unisim.vcomponents.CARRY8
     port map (
      CI => \Add2_out1_1[8]_i_2__0_n_0\,
      CI_TOP => '0',
      CO(7) => \Add2_out1_1_reg[8]_i_1__0_n_0\,
      CO(6) => \Add2_out1_1_reg[8]_i_1__0_n_1\,
      CO(5) => \Add2_out1_1_reg[8]_i_1__0_n_2\,
      CO(4) => \Add2_out1_1_reg[8]_i_1__0_n_3\,
      CO(3) => \Add2_out1_1_reg[8]_i_1__0_n_4\,
      CO(2) => \Add2_out1_1_reg[8]_i_1__0_n_5\,
      CO(1) => \Add2_out1_1_reg[8]_i_1__0_n_6\,
      CO(0) => \Add2_out1_1_reg[8]_i_1__0_n_7\,
      DI(7 downto 0) => B"00000000",
      O(7 downto 0) => Add2_out1(8 downto 1),
      S(7) => \Add2_out1_1[8]_i_3__0_n_0\,
      S(6) => \Add2_out1_1[8]_i_4__0_n_0\,
      S(5) => \Add2_out1_1[8]_i_5__0_n_0\,
      S(4) => \Add2_out1_1[8]_i_6__0_n_0\,
      S(3) => \Add2_out1_1[8]_i_7__0_n_0\,
      S(2) => \Add2_out1_1[8]_i_8__0_n_0\,
      S(1) => \Add2_out1_1[8]_i_9__0_n_0\,
      S(0) => \Add2_out1_1[8]_i_10__0_n_0\
    );
\Add2_out1_1_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => Add2_out1(9),
      Q => Add2_out1_1(9),
      R => RSTP
    );
\Delay1_out1[11]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AAAAFFBFAAAA0080"
    )
        port map (
      I0 => \Delay1_out1_reg[13]_0\(11),
      I1 => \Delay1_out1_reg[13]_1\,
      I2 => D(0),
      I3 => HDL_Counter2_count_reg(0),
      I4 => CO(0),
      I5 => \Delay1_out1_reg[13]\(11),
      O => \^delaymatch3_reg_reg[1][11]\
    );
\Delay1_out1[13]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AAAAFFBFAAAA0080"
    )
        port map (
      I0 => \Delay1_out1_reg[13]_0\(13),
      I1 => \Delay1_out1_reg[13]_1\,
      I2 => D(0),
      I3 => HDL_Counter2_count_reg(0),
      I4 => CO(0),
      I5 => \Delay1_out1_reg[13]\(13),
      O => \^delaymatch3_reg_reg[1][13]\
    );
\Delay1_out1[1]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AAAAFFBFAAAA0080"
    )
        port map (
      I0 => \Delay1_out1_reg[13]_0\(1),
      I1 => \Delay1_out1_reg[13]_1\,
      I2 => D(0),
      I3 => HDL_Counter2_count_reg(0),
      I4 => CO(0),
      I5 => \Delay1_out1_reg[13]\(1),
      O => \^delaymatch3_reg_reg[1][1]\
    );
\Delay1_out1[3]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AAAAFFBFAAAA0080"
    )
        port map (
      I0 => \Delay1_out1_reg[13]_0\(3),
      I1 => \Delay1_out1_reg[13]_1\,
      I2 => D(0),
      I3 => HDL_Counter2_count_reg(0),
      I4 => CO(0),
      I5 => \Delay1_out1_reg[13]\(3),
      O => \^delaymatch3_reg_reg[1][3]\
    );
\Delay1_out1[5]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AAAAFFBFAAAA0080"
    )
        port map (
      I0 => \Delay1_out1_reg[13]_0\(5),
      I1 => \Delay1_out1_reg[13]_1\,
      I2 => D(0),
      I3 => HDL_Counter2_count_reg(0),
      I4 => CO(0),
      I5 => \Delay1_out1_reg[13]\(5),
      O => \^delaymatch3_reg_reg[1][5]\
    );
\Delay1_out1[7]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AAAAFFBFAAAA0080"
    )
        port map (
      I0 => \Delay1_out1_reg[13]_0\(7),
      I1 => \Delay1_out1_reg[13]_1\,
      I2 => D(0),
      I3 => HDL_Counter2_count_reg(0),
      I4 => CO(0),
      I5 => \Delay1_out1_reg[13]\(7),
      O => \^delaymatch3_reg_reg[1][7]\
    );
\Delay1_out1[9]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AAAAFFBFAAAA0080"
    )
        port map (
      I0 => \Delay1_out1_reg[13]_0\(9),
      I1 => \Delay1_out1_reg[13]_1\,
      I2 => D(0),
      I3 => HDL_Counter2_count_reg(0),
      I4 => CO(0),
      I5 => \Delay1_out1_reg[13]\(9),
      O => \^delaymatch3_reg_reg[1][9]\
    );
Logical_Operator1_out10_carry: unisim.vcomponents.CARRY8
     port map (
      CI => '0',
      CI_TOP => '0',
      CO(7) => NLW_Logical_Operator1_out10_carry_CO_UNCONNECTED(7),
      CO(6) => Relational_Operator_relop1,
      CO(5) => Logical_Operator1_out10_carry_n_2,
      CO(4) => Logical_Operator1_out10_carry_n_3,
      CO(3) => Logical_Operator1_out10_carry_n_4,
      CO(2) => Logical_Operator1_out10_carry_n_5,
      CO(1) => Logical_Operator1_out10_carry_n_6,
      CO(0) => Logical_Operator1_out10_carry_n_7,
      DI(7) => '0',
      DI(6) => \Logical_Operator1_out10_carry_i_1__0_n_0\,
      DI(5) => \Logical_Operator1_out10_carry_i_2__0_n_0\,
      DI(4) => \Logical_Operator1_out10_carry_i_3__0_n_0\,
      DI(3) => \Logical_Operator1_out10_carry_i_4__0_n_0\,
      DI(2) => \Logical_Operator1_out10_carry_i_5__0_n_0\,
      DI(1) => \Logical_Operator1_out10_carry_i_6__0_n_0\,
      DI(0) => \Logical_Operator1_out10_carry_i_7__0_n_0\,
      O(7 downto 0) => NLW_Logical_Operator1_out10_carry_O_UNCONNECTED(7 downto 0),
      S(7) => '0',
      S(6) => \Logical_Operator1_out10_carry_i_8__0_n_0\,
      S(5) => \Logical_Operator1_out10_carry_i_9__0_n_0\,
      S(4) => \Logical_Operator1_out10_carry_i_10__0_n_0\,
      S(3) => \Logical_Operator1_out10_carry_i_11__0_n_0\,
      S(2) => \Logical_Operator1_out10_carry_i_12__0_n_0\,
      S(1) => \Logical_Operator1_out10_carry_i_13__0_n_0\,
      S(0) => \Logical_Operator1_out10_carry_i_14__0_n_0\
    );
\Logical_Operator1_out10_carry_i_10__0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"A95900000000A959"
    )
        port map (
      I0 => minus_out1_1(8),
      I1 => \Delay1_out1_reg[13]\(8),
      I2 => \^pwm_en_axi_2_reg\,
      I3 => \Delay1_out1_reg[13]_0\(8),
      I4 => \^delaymatch3_reg_reg[1][9]\,
      I5 => minus_out1_1(9),
      O => \Logical_Operator1_out10_carry_i_10__0_n_0\
    );
\Logical_Operator1_out10_carry_i_11__0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"A95900000000A959"
    )
        port map (
      I0 => minus_out1_1(6),
      I1 => \Delay1_out1_reg[13]\(6),
      I2 => \^pwm_en_axi_2_reg\,
      I3 => \Delay1_out1_reg[13]_0\(6),
      I4 => \^delaymatch3_reg_reg[1][7]\,
      I5 => minus_out1_1(7),
      O => \Logical_Operator1_out10_carry_i_11__0_n_0\
    );
\Logical_Operator1_out10_carry_i_12__0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"A95900000000A959"
    )
        port map (
      I0 => minus_out1_1(4),
      I1 => \Delay1_out1_reg[13]\(4),
      I2 => \^pwm_en_axi_2_reg\,
      I3 => \Delay1_out1_reg[13]_0\(4),
      I4 => \^delaymatch3_reg_reg[1][5]\,
      I5 => minus_out1_1(5),
      O => \Logical_Operator1_out10_carry_i_12__0_n_0\
    );
\Logical_Operator1_out10_carry_i_13__0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"A95900000000A959"
    )
        port map (
      I0 => minus_out1_1(2),
      I1 => \Delay1_out1_reg[13]\(2),
      I2 => \^pwm_en_axi_2_reg\,
      I3 => \Delay1_out1_reg[13]_0\(2),
      I4 => \^delaymatch3_reg_reg[1][3]\,
      I5 => minus_out1_1(3),
      O => \Logical_Operator1_out10_carry_i_13__0_n_0\
    );
\Logical_Operator1_out10_carry_i_14__0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"E21D00000000E21D"
    )
        port map (
      I0 => \Delay1_out1_reg[13]\(0),
      I1 => \^pwm_en_axi_2_reg\,
      I2 => \Delay1_out1_reg[13]_0\(0),
      I3 => Add1_out1_1(0),
      I4 => \^delaymatch3_reg_reg[1][1]\,
      I5 => minus_out1_1(1),
      O => \Logical_Operator1_out10_carry_i_14__0_n_0\
    );
\Logical_Operator1_out10_carry_i_1__0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"22222222BBB222B2"
    )
        port map (
      I0 => minus_out1_1(13),
      I1 => \^delaymatch3_reg_reg[1][13]\,
      I2 => \Delay1_out1_reg[13]\(12),
      I3 => \^pwm_en_axi_2_reg\,
      I4 => \Delay1_out1_reg[13]_0\(12),
      I5 => minus_out1_1(12),
      O => \Logical_Operator1_out10_carry_i_1__0_n_0\
    );
\Logical_Operator1_out10_carry_i_2__0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"22222222BBB222B2"
    )
        port map (
      I0 => \^delaymatch3_reg_reg[1][11]\,
      I1 => minus_out1_1(11),
      I2 => \Delay1_out1_reg[13]\(10),
      I3 => \^pwm_en_axi_2_reg\,
      I4 => \Delay1_out1_reg[13]_0\(10),
      I5 => minus_out1_1(10),
      O => \Logical_Operator1_out10_carry_i_2__0_n_0\
    );
\Logical_Operator1_out10_carry_i_3__0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"22222222BBB222B2"
    )
        port map (
      I0 => \^delaymatch3_reg_reg[1][9]\,
      I1 => minus_out1_1(9),
      I2 => \Delay1_out1_reg[13]\(8),
      I3 => \^pwm_en_axi_2_reg\,
      I4 => \Delay1_out1_reg[13]_0\(8),
      I5 => minus_out1_1(8),
      O => \Logical_Operator1_out10_carry_i_3__0_n_0\
    );
\Logical_Operator1_out10_carry_i_4__0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"22222222BBB222B2"
    )
        port map (
      I0 => \^delaymatch3_reg_reg[1][7]\,
      I1 => minus_out1_1(7),
      I2 => \Delay1_out1_reg[13]\(6),
      I3 => \^pwm_en_axi_2_reg\,
      I4 => \Delay1_out1_reg[13]_0\(6),
      I5 => minus_out1_1(6),
      O => \Logical_Operator1_out10_carry_i_4__0_n_0\
    );
\Logical_Operator1_out10_carry_i_5__0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"22222222BBB222B2"
    )
        port map (
      I0 => \^delaymatch3_reg_reg[1][5]\,
      I1 => minus_out1_1(5),
      I2 => \Delay1_out1_reg[13]\(4),
      I3 => \^pwm_en_axi_2_reg\,
      I4 => \Delay1_out1_reg[13]_0\(4),
      I5 => minus_out1_1(4),
      O => \Logical_Operator1_out10_carry_i_5__0_n_0\
    );
\Logical_Operator1_out10_carry_i_6__0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"22222222BBB222B2"
    )
        port map (
      I0 => \^delaymatch3_reg_reg[1][3]\,
      I1 => minus_out1_1(3),
      I2 => \Delay1_out1_reg[13]\(2),
      I3 => \^pwm_en_axi_2_reg\,
      I4 => \Delay1_out1_reg[13]_0\(2),
      I5 => minus_out1_1(2),
      O => \Logical_Operator1_out10_carry_i_6__0_n_0\
    );
\Logical_Operator1_out10_carry_i_7__0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"7577755510111000"
    )
        port map (
      I0 => minus_out1_1(1),
      I1 => Add1_out1_1(0),
      I2 => \Delay1_out1_reg[13]_0\(0),
      I3 => \^pwm_en_axi_2_reg\,
      I4 => \Delay1_out1_reg[13]\(0),
      I5 => \^delaymatch3_reg_reg[1][1]\,
      O => \Logical_Operator1_out10_carry_i_7__0_n_0\
    );
\Logical_Operator1_out10_carry_i_8__0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"A95900000000A959"
    )
        port map (
      I0 => minus_out1_1(12),
      I1 => \Delay1_out1_reg[13]\(12),
      I2 => \^pwm_en_axi_2_reg\,
      I3 => \Delay1_out1_reg[13]_0\(12),
      I4 => \^delaymatch3_reg_reg[1][13]\,
      I5 => minus_out1_1(13),
      O => \Logical_Operator1_out10_carry_i_8__0_n_0\
    );
\Logical_Operator1_out10_carry_i_9__0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"A95900000000A959"
    )
        port map (
      I0 => minus_out1_1(10),
      I1 => \Delay1_out1_reg[13]\(10),
      I2 => \^pwm_en_axi_2_reg\,
      I3 => \Delay1_out1_reg[13]_0\(10),
      I4 => \^delaymatch3_reg_reg[1][11]\,
      I5 => minus_out1_1(11),
      O => \Logical_Operator1_out10_carry_i_9__0_n_0\
    );
\Logical_Operator1_out10_inferred__0/i__carry\: unisim.vcomponents.CARRY8
     port map (
      CI => '0',
      CI_TOP => '0',
      CO(7) => \NLW_Logical_Operator1_out10_inferred__0/i__carry_CO_UNCONNECTED\(7),
      CO(6) => Relational_Operator1_relop1,
      CO(5) => \Logical_Operator1_out10_inferred__0/i__carry_n_2\,
      CO(4) => \Logical_Operator1_out10_inferred__0/i__carry_n_3\,
      CO(3) => \Logical_Operator1_out10_inferred__0/i__carry_n_4\,
      CO(2) => \Logical_Operator1_out10_inferred__0/i__carry_n_5\,
      CO(1) => \Logical_Operator1_out10_inferred__0/i__carry_n_6\,
      CO(0) => \Logical_Operator1_out10_inferred__0/i__carry_n_7\,
      DI(7) => '0',
      DI(6) => \i__carry_i_1__0_n_0\,
      DI(5) => \i__carry_i_2__0_n_0\,
      DI(4) => \i__carry_i_3__0_n_0\,
      DI(3) => \i__carry_i_4__0_n_0\,
      DI(2) => \i__carry_i_5__0_n_0\,
      DI(1) => \i__carry_i_6__0_n_0\,
      DI(0) => \i__carry_i_7__0_n_0\,
      O(7 downto 0) => \NLW_Logical_Operator1_out10_inferred__0/i__carry_O_UNCONNECTED\(7 downto 0),
      S(7) => '0',
      S(6) => \i__carry_i_8__0_n_0\,
      S(5) => \i__carry_i_9__0_n_0\,
      S(4) => \i__carry_i_10__0_n_0\,
      S(3) => \i__carry_i_11__0_n_0\,
      S(2) => \i__carry_i_12__0_n_0\,
      S(1) => \i__carry_i_13__0_n_0\,
      S(0) => \i__carry_i_14__0_n_0\
    );
Logical_Operator_out10_carry: unisim.vcomponents.CARRY8
     port map (
      CI => '0',
      CI_TOP => '0',
      CO(7) => NLW_Logical_Operator_out10_carry_CO_UNCONNECTED(7),
      CO(6) => Relational_Operator3_relop1,
      CO(5) => Logical_Operator_out10_carry_n_2,
      CO(4) => Logical_Operator_out10_carry_n_3,
      CO(3) => Logical_Operator_out10_carry_n_4,
      CO(2) => Logical_Operator_out10_carry_n_5,
      CO(1) => Logical_Operator_out10_carry_n_6,
      CO(0) => Logical_Operator_out10_carry_n_7,
      DI(7) => '0',
      DI(6) => \Logical_Operator_out10_carry_i_1__0_n_0\,
      DI(5) => \Logical_Operator_out10_carry_i_2__0_n_0\,
      DI(4) => \Logical_Operator_out10_carry_i_3__0_n_0\,
      DI(3) => \Logical_Operator_out10_carry_i_4__0_n_0\,
      DI(2) => \Logical_Operator_out10_carry_i_5__0_n_0\,
      DI(1) => \Logical_Operator_out10_carry_i_6__0_n_0\,
      DI(0) => \Logical_Operator_out10_carry_i_7__0_n_0\,
      O(7 downto 0) => NLW_Logical_Operator_out10_carry_O_UNCONNECTED(7 downto 0),
      S(7) => '0',
      S(6) => \Logical_Operator_out10_carry_i_8__0_n_0\,
      S(5) => \Logical_Operator_out10_carry_i_9__0_n_0\,
      S(4) => \Logical_Operator_out10_carry_i_10__0_n_0\,
      S(3) => \Logical_Operator_out10_carry_i_11__0_n_0\,
      S(2) => \Logical_Operator_out10_carry_i_12__0_n_0\,
      S(1) => \Logical_Operator_out10_carry_i_13__0_n_0\,
      S(0) => \Logical_Operator_out10_carry_i_14__0_n_0\
    );
\Logical_Operator_out10_carry_i_10__0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"A95900000000A959"
    )
        port map (
      I0 => Add2_out1_1(8),
      I1 => \Delay1_out1_reg[13]\(8),
      I2 => \^pwm_en_axi_2_reg\,
      I3 => \Delay1_out1_reg[13]_0\(8),
      I4 => \^delaymatch3_reg_reg[1][9]\,
      I5 => Add2_out1_1(9),
      O => \Logical_Operator_out10_carry_i_10__0_n_0\
    );
\Logical_Operator_out10_carry_i_11__0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"A95900000000A959"
    )
        port map (
      I0 => Add2_out1_1(6),
      I1 => \Delay1_out1_reg[13]\(6),
      I2 => \^pwm_en_axi_2_reg\,
      I3 => \Delay1_out1_reg[13]_0\(6),
      I4 => \^delaymatch3_reg_reg[1][7]\,
      I5 => Add2_out1_1(7),
      O => \Logical_Operator_out10_carry_i_11__0_n_0\
    );
\Logical_Operator_out10_carry_i_12__0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"A95900000000A959"
    )
        port map (
      I0 => Add2_out1_1(4),
      I1 => \Delay1_out1_reg[13]\(4),
      I2 => \^pwm_en_axi_2_reg\,
      I3 => \Delay1_out1_reg[13]_0\(4),
      I4 => \^delaymatch3_reg_reg[1][5]\,
      I5 => Add2_out1_1(5),
      O => \Logical_Operator_out10_carry_i_12__0_n_0\
    );
\Logical_Operator_out10_carry_i_13__0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"A95900000000A959"
    )
        port map (
      I0 => Add2_out1_1(2),
      I1 => \Delay1_out1_reg[13]\(2),
      I2 => \^pwm_en_axi_2_reg\,
      I3 => \Delay1_out1_reg[13]_0\(2),
      I4 => \^delaymatch3_reg_reg[1][3]\,
      I5 => Add2_out1_1(3),
      O => \Logical_Operator_out10_carry_i_13__0_n_0\
    );
\Logical_Operator_out10_carry_i_14__0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"E21D00000000E21D"
    )
        port map (
      I0 => \Delay1_out1_reg[13]\(0),
      I1 => \^pwm_en_axi_2_reg\,
      I2 => \Delay1_out1_reg[13]_0\(0),
      I3 => Add1_out1_1(0),
      I4 => \^delaymatch3_reg_reg[1][1]\,
      I5 => Add2_out1_1(1),
      O => \Logical_Operator_out10_carry_i_14__0_n_0\
    );
\Logical_Operator_out10_carry_i_1__0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"22222222BBB222B2"
    )
        port map (
      I0 => Add2_out1_1(13),
      I1 => \^delaymatch3_reg_reg[1][13]\,
      I2 => \Delay1_out1_reg[13]\(12),
      I3 => \^pwm_en_axi_2_reg\,
      I4 => \Delay1_out1_reg[13]_0\(12),
      I5 => Add2_out1_1(12),
      O => \Logical_Operator_out10_carry_i_1__0_n_0\
    );
\Logical_Operator_out10_carry_i_2__0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"22222222BBB222B2"
    )
        port map (
      I0 => \^delaymatch3_reg_reg[1][11]\,
      I1 => Add2_out1_1(11),
      I2 => \Delay1_out1_reg[13]\(10),
      I3 => \^pwm_en_axi_2_reg\,
      I4 => \Delay1_out1_reg[13]_0\(10),
      I5 => Add2_out1_1(10),
      O => \Logical_Operator_out10_carry_i_2__0_n_0\
    );
\Logical_Operator_out10_carry_i_3__0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"22222222BBB222B2"
    )
        port map (
      I0 => \^delaymatch3_reg_reg[1][9]\,
      I1 => Add2_out1_1(9),
      I2 => \Delay1_out1_reg[13]\(8),
      I3 => \^pwm_en_axi_2_reg\,
      I4 => \Delay1_out1_reg[13]_0\(8),
      I5 => Add2_out1_1(8),
      O => \Logical_Operator_out10_carry_i_3__0_n_0\
    );
\Logical_Operator_out10_carry_i_4__0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"22222222BBB222B2"
    )
        port map (
      I0 => \^delaymatch3_reg_reg[1][7]\,
      I1 => Add2_out1_1(7),
      I2 => \Delay1_out1_reg[13]\(6),
      I3 => \^pwm_en_axi_2_reg\,
      I4 => \Delay1_out1_reg[13]_0\(6),
      I5 => Add2_out1_1(6),
      O => \Logical_Operator_out10_carry_i_4__0_n_0\
    );
\Logical_Operator_out10_carry_i_5__0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"22222222BBB222B2"
    )
        port map (
      I0 => \^delaymatch3_reg_reg[1][5]\,
      I1 => Add2_out1_1(5),
      I2 => \Delay1_out1_reg[13]\(4),
      I3 => \^pwm_en_axi_2_reg\,
      I4 => \Delay1_out1_reg[13]_0\(4),
      I5 => Add2_out1_1(4),
      O => \Logical_Operator_out10_carry_i_5__0_n_0\
    );
\Logical_Operator_out10_carry_i_6__0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"22222222BBB222B2"
    )
        port map (
      I0 => \^delaymatch3_reg_reg[1][3]\,
      I1 => Add2_out1_1(3),
      I2 => \Delay1_out1_reg[13]\(2),
      I3 => \^pwm_en_axi_2_reg\,
      I4 => \Delay1_out1_reg[13]_0\(2),
      I5 => Add2_out1_1(2),
      O => \Logical_Operator_out10_carry_i_6__0_n_0\
    );
\Logical_Operator_out10_carry_i_7__0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"7577755510111000"
    )
        port map (
      I0 => Add2_out1_1(1),
      I1 => Add1_out1_1(0),
      I2 => \Delay1_out1_reg[13]_0\(0),
      I3 => \^pwm_en_axi_2_reg\,
      I4 => \Delay1_out1_reg[13]\(0),
      I5 => \^delaymatch3_reg_reg[1][1]\,
      O => \Logical_Operator_out10_carry_i_7__0_n_0\
    );
\Logical_Operator_out10_carry_i_8__0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"A95900000000A959"
    )
        port map (
      I0 => Add2_out1_1(12),
      I1 => \Delay1_out1_reg[13]\(12),
      I2 => \^pwm_en_axi_2_reg\,
      I3 => \Delay1_out1_reg[13]_0\(12),
      I4 => \^delaymatch3_reg_reg[1][13]\,
      I5 => Add2_out1_1(13),
      O => \Logical_Operator_out10_carry_i_8__0_n_0\
    );
\Logical_Operator_out10_carry_i_9__0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"A95900000000A959"
    )
        port map (
      I0 => Add2_out1_1(10),
      I1 => \Delay1_out1_reg[13]\(10),
      I2 => \^pwm_en_axi_2_reg\,
      I3 => \Delay1_out1_reg[13]_0\(10),
      I4 => \^delaymatch3_reg_reg[1][11]\,
      I5 => Add2_out1_1(11),
      O => \Logical_Operator_out10_carry_i_9__0_n_0\
    );
Logical_Operator_out11_carry: unisim.vcomponents.CARRY8
     port map (
      CI => '0',
      CI_TOP => '0',
      CO(7) => NLW_Logical_Operator_out11_carry_CO_UNCONNECTED(7),
      CO(6) => Relational_Operator2_relop1,
      CO(5) => Logical_Operator_out11_carry_n_2,
      CO(4) => Logical_Operator_out11_carry_n_3,
      CO(3) => Logical_Operator_out11_carry_n_4,
      CO(2) => Logical_Operator_out11_carry_n_5,
      CO(1) => Logical_Operator_out11_carry_n_6,
      CO(0) => Logical_Operator_out11_carry_n_7,
      DI(7) => '0',
      DI(6) => \Logical_Operator_out11_carry_i_1__0_n_0\,
      DI(5) => \Logical_Operator_out11_carry_i_2__0_n_0\,
      DI(4) => \i__carry_i_3__0_n_0\,
      DI(3) => \i__carry_i_4__0_n_0\,
      DI(2) => \i__carry_i_5__0_n_0\,
      DI(1) => \i__carry_i_6__0_n_0\,
      DI(0) => \i__carry_i_7__0_n_0\,
      O(7 downto 0) => NLW_Logical_Operator_out11_carry_O_UNCONNECTED(7 downto 0),
      S(7) => '0',
      S(6) => \Logical_Operator_out11_carry_i_3__0_n_0\,
      S(5) => \Logical_Operator_out11_carry_i_4__0_n_0\,
      S(4) => \Logical_Operator_out11_carry_i_5__0_n_0\,
      S(3) => \Logical_Operator_out11_carry_i_6__0_n_0\,
      S(2) => \Logical_Operator_out11_carry_i_7__0_n_0\,
      S(1) => \Logical_Operator_out11_carry_i_8__0_n_0\,
      S(0) => \Logical_Operator_out11_carry_i_9__0_n_0\
    );
\Logical_Operator_out11_carry_i_1__0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"222222B2B2B222B2"
    )
        port map (
      I0 => \^delaymatch3_reg_reg[1][13]\,
      I1 => Add1_out1_1(13),
      I2 => Add1_out1_1(12),
      I3 => \Delay1_out1_reg[13]\(12),
      I4 => \^pwm_en_axi_2_reg\,
      I5 => \Delay1_out1_reg[13]_0\(12),
      O => \Logical_Operator_out11_carry_i_1__0_n_0\
    );
\Logical_Operator_out11_carry_i_2__0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"222222B2B2B222B2"
    )
        port map (
      I0 => Add1_out1_1(11),
      I1 => \^delaymatch3_reg_reg[1][11]\,
      I2 => Add1_out1_1(10),
      I3 => \Delay1_out1_reg[13]\(10),
      I4 => \^pwm_en_axi_2_reg\,
      I5 => \Delay1_out1_reg[13]_0\(10),
      O => \Logical_Operator_out11_carry_i_2__0_n_0\
    );
\Logical_Operator_out11_carry_i_3__0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"A95900000000A959"
    )
        port map (
      I0 => Add1_out1_1(12),
      I1 => \Delay1_out1_reg[13]\(12),
      I2 => \^pwm_en_axi_2_reg\,
      I3 => \Delay1_out1_reg[13]_0\(12),
      I4 => \^delaymatch3_reg_reg[1][13]\,
      I5 => Add1_out1_1(13),
      O => \Logical_Operator_out11_carry_i_3__0_n_0\
    );
\Logical_Operator_out11_carry_i_4__0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"A95900000000A959"
    )
        port map (
      I0 => Add1_out1_1(10),
      I1 => \Delay1_out1_reg[13]\(10),
      I2 => \^pwm_en_axi_2_reg\,
      I3 => \Delay1_out1_reg[13]_0\(10),
      I4 => \^delaymatch3_reg_reg[1][11]\,
      I5 => Add1_out1_1(11),
      O => \Logical_Operator_out11_carry_i_4__0_n_0\
    );
\Logical_Operator_out11_carry_i_5__0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"A95900000000A959"
    )
        port map (
      I0 => Add1_out1_1(8),
      I1 => \Delay1_out1_reg[13]\(8),
      I2 => \^pwm_en_axi_2_reg\,
      I3 => \Delay1_out1_reg[13]_0\(8),
      I4 => \^delaymatch3_reg_reg[1][9]\,
      I5 => Add1_out1_1(9),
      O => \Logical_Operator_out11_carry_i_5__0_n_0\
    );
\Logical_Operator_out11_carry_i_6__0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"A95900000000A959"
    )
        port map (
      I0 => Add1_out1_1(6),
      I1 => \Delay1_out1_reg[13]\(6),
      I2 => \^pwm_en_axi_2_reg\,
      I3 => \Delay1_out1_reg[13]_0\(6),
      I4 => \^delaymatch3_reg_reg[1][7]\,
      I5 => Add1_out1_1(7),
      O => \Logical_Operator_out11_carry_i_6__0_n_0\
    );
\Logical_Operator_out11_carry_i_7__0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"A95900000000A959"
    )
        port map (
      I0 => Add1_out1_1(4),
      I1 => \Delay1_out1_reg[13]\(4),
      I2 => \^pwm_en_axi_2_reg\,
      I3 => \Delay1_out1_reg[13]_0\(4),
      I4 => \^delaymatch3_reg_reg[1][5]\,
      I5 => Add1_out1_1(5),
      O => \Logical_Operator_out11_carry_i_7__0_n_0\
    );
\Logical_Operator_out11_carry_i_8__0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"A95900000000A959"
    )
        port map (
      I0 => Add1_out1_1(2),
      I1 => \Delay1_out1_reg[13]\(2),
      I2 => \^pwm_en_axi_2_reg\,
      I3 => \Delay1_out1_reg[13]_0\(2),
      I4 => \^delaymatch3_reg_reg[1][3]\,
      I5 => Add1_out1_1(3),
      O => \Logical_Operator_out11_carry_i_8__0_n_0\
    );
\Logical_Operator_out11_carry_i_9__0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"E21D00000000E21D"
    )
        port map (
      I0 => \Delay1_out1_reg[13]\(0),
      I1 => \^pwm_en_axi_2_reg\,
      I2 => \Delay1_out1_reg[13]_0\(0),
      I3 => Add1_out1_1(0),
      I4 => \^delaymatch3_reg_reg[1][1]\,
      I5 => Add1_out1_1(1),
      O => \Logical_Operator_out11_carry_i_9__0_n_0\
    );
\Saturation1_out1_1[11]_i_1__0\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"02"
    )
        port map (
      I0 => Q(11),
      I1 => Saturation1_out110_in,
      I2 => Q(13),
      O => Saturation1_out1(11)
    );
\Saturation1_out1_1[12]_i_1__0\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"BA"
    )
        port map (
      I0 => Saturation1_out110_in,
      I1 => Q(13),
      I2 => Q(12),
      O => Saturation1_out1(12)
    );
\Saturation1_out1_1_reg[11]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => Saturation1_out1(11),
      Q => Saturation1_out1_1(11),
      R => RSTP
    );
\Saturation1_out1_1_reg[12]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => Saturation1_out1(12),
      Q => Saturation1_out1_1(12),
      R => RSTP
    );
\i__carry_i_10__0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"A95900000000A959"
    )
        port map (
      I0 => Add1_out1_1(8),
      I1 => \Delay1_out1_reg[13]\(8),
      I2 => \^pwm_en_axi_2_reg\,
      I3 => \Delay1_out1_reg[13]_0\(8),
      I4 => \^delaymatch3_reg_reg[1][9]\,
      I5 => Add1_out1_1(9),
      O => \i__carry_i_10__0_n_0\
    );
\i__carry_i_11__0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"A95900000000A959"
    )
        port map (
      I0 => Add1_out1_1(6),
      I1 => \Delay1_out1_reg[13]\(6),
      I2 => \^pwm_en_axi_2_reg\,
      I3 => \Delay1_out1_reg[13]_0\(6),
      I4 => \^delaymatch3_reg_reg[1][7]\,
      I5 => Add1_out1_1(7),
      O => \i__carry_i_11__0_n_0\
    );
\i__carry_i_12__0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"A95900000000A959"
    )
        port map (
      I0 => Add1_out1_1(4),
      I1 => \Delay1_out1_reg[13]\(4),
      I2 => \^pwm_en_axi_2_reg\,
      I3 => \Delay1_out1_reg[13]_0\(4),
      I4 => \^delaymatch3_reg_reg[1][5]\,
      I5 => Add1_out1_1(5),
      O => \i__carry_i_12__0_n_0\
    );
\i__carry_i_13__0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"A95900000000A959"
    )
        port map (
      I0 => Add1_out1_1(2),
      I1 => \Delay1_out1_reg[13]\(2),
      I2 => \^pwm_en_axi_2_reg\,
      I3 => \Delay1_out1_reg[13]_0\(2),
      I4 => \^delaymatch3_reg_reg[1][3]\,
      I5 => Add1_out1_1(3),
      O => \i__carry_i_13__0_n_0\
    );
\i__carry_i_14__0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"E21D00000000E21D"
    )
        port map (
      I0 => \Delay1_out1_reg[13]\(0),
      I1 => \^pwm_en_axi_2_reg\,
      I2 => \Delay1_out1_reg[13]_0\(0),
      I3 => Add1_out1_1(0),
      I4 => \^delaymatch3_reg_reg[1][1]\,
      I5 => Add1_out1_1(1),
      O => \i__carry_i_14__0_n_0\
    );
\i__carry_i_1__0\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"AAAEEEAE"
    )
        port map (
      I0 => \^delaymatch3_reg_reg[1][13]\,
      I1 => Saturation1_out1_1(12),
      I2 => \Delay1_out1_reg[13]\(12),
      I3 => \^pwm_en_axi_2_reg\,
      I4 => \Delay1_out1_reg[13]_0\(12),
      O => \i__carry_i_1__0_n_0\
    );
\i__carry_i_2__0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"222222B2B2B222B2"
    )
        port map (
      I0 => Saturation1_out1_1(11),
      I1 => \^delaymatch3_reg_reg[1][11]\,
      I2 => Add1_out1_1(10),
      I3 => \Delay1_out1_reg[13]\(10),
      I4 => \^pwm_en_axi_2_reg\,
      I5 => \Delay1_out1_reg[13]_0\(10),
      O => \i__carry_i_2__0_n_0\
    );
\i__carry_i_3__0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"222222B2B2B222B2"
    )
        port map (
      I0 => Add1_out1_1(9),
      I1 => \^delaymatch3_reg_reg[1][9]\,
      I2 => Add1_out1_1(8),
      I3 => \Delay1_out1_reg[13]\(8),
      I4 => \^pwm_en_axi_2_reg\,
      I5 => \Delay1_out1_reg[13]_0\(8),
      O => \i__carry_i_3__0_n_0\
    );
\i__carry_i_4__0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"222222B2B2B222B2"
    )
        port map (
      I0 => Add1_out1_1(7),
      I1 => \^delaymatch3_reg_reg[1][7]\,
      I2 => Add1_out1_1(6),
      I3 => \Delay1_out1_reg[13]\(6),
      I4 => \^pwm_en_axi_2_reg\,
      I5 => \Delay1_out1_reg[13]_0\(6),
      O => \i__carry_i_4__0_n_0\
    );
\i__carry_i_5__0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"222222B2B2B222B2"
    )
        port map (
      I0 => Add1_out1_1(5),
      I1 => \^delaymatch3_reg_reg[1][5]\,
      I2 => Add1_out1_1(4),
      I3 => \Delay1_out1_reg[13]\(4),
      I4 => \^pwm_en_axi_2_reg\,
      I5 => \Delay1_out1_reg[13]_0\(4),
      O => \i__carry_i_5__0_n_0\
    );
\i__carry_i_6__0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"222222B2B2B222B2"
    )
        port map (
      I0 => Add1_out1_1(3),
      I1 => \^delaymatch3_reg_reg[1][3]\,
      I2 => Add1_out1_1(2),
      I3 => \Delay1_out1_reg[13]\(2),
      I4 => \^pwm_en_axi_2_reg\,
      I5 => \Delay1_out1_reg[13]_0\(2),
      O => \i__carry_i_6__0_n_0\
    );
\i__carry_i_7__0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"222222B2B2B222B2"
    )
        port map (
      I0 => Add1_out1_1(1),
      I1 => \^delaymatch3_reg_reg[1][1]\,
      I2 => Add1_out1_1(0),
      I3 => \Delay1_out1_reg[13]\(0),
      I4 => \^pwm_en_axi_2_reg\,
      I5 => \Delay1_out1_reg[13]_0\(0),
      O => \i__carry_i_7__0_n_0\
    );
\i__carry_i_8__0\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"0000A959"
    )
        port map (
      I0 => Saturation1_out1_1(12),
      I1 => \Delay1_out1_reg[13]\(12),
      I2 => \^pwm_en_axi_2_reg\,
      I3 => \Delay1_out1_reg[13]_0\(12),
      I4 => \^delaymatch3_reg_reg[1][13]\,
      O => \i__carry_i_8__0_n_0\
    );
\i__carry_i_9__0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"A95900000000A959"
    )
        port map (
      I0 => Add1_out1_1(10),
      I1 => \Delay1_out1_reg[13]\(10),
      I2 => \^pwm_en_axi_2_reg\,
      I3 => \Delay1_out1_reg[13]_0\(10),
      I4 => \^delaymatch3_reg_reg[1][11]\,
      I5 => Saturation1_out1_1(11),
      O => \i__carry_i_9__0_n_0\
    );
\minus_out1_1[10]_i_1__0\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"02"
    )
        port map (
      I0 => \minus_out1_1_reg[10]_0\,
      I1 => Saturation1_out110_in,
      I2 => Q(13),
      O => minus_out1(10)
    );
\minus_out1_1[11]_i_1__0\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"02"
    )
        port map (
      I0 => \minus_out1_1_reg[11]_0\,
      I1 => Saturation1_out110_in,
      I2 => Q(13),
      O => minus_out1(11)
    );
\minus_out1_1[12]_i_1__0\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFFF001E"
    )
        port map (
      I0 => \minus_out1_1_reg[12]_0\,
      I1 => Q(11),
      I2 => Q(12),
      I3 => Q(13),
      I4 => Saturation1_out110_in,
      O => minus_out1(12)
    );
\minus_out1_1[13]_i_10__1\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => Q(10),
      I1 => Q(11),
      O => \minus_out1_1[13]_i_10__1_n_0\
    );
\minus_out1_1[13]_i_11__1\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => Q(8),
      I1 => Q(9),
      O => \minus_out1_1[13]_i_11__1_n_0\
    );
\minus_out1_1[13]_i_12__1\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => Q(6),
      I1 => Q(7),
      O => \minus_out1_1[13]_i_12__1_n_0\
    );
\minus_out1_1[13]_i_13__1\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => Q(4),
      I1 => Q(5),
      O => \minus_out1_1[13]_i_13__1_n_0\
    );
\minus_out1_1[13]_i_14__1\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => Q(2),
      I1 => Q(3),
      O => \minus_out1_1[13]_i_14__1_n_0\
    );
\minus_out1_1[13]_i_15__0\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => Q(1),
      I1 => Q(0),
      O => \minus_out1_1[13]_i_15__0_n_0\
    );
\minus_out1_1[13]_i_1__0\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFFF00FE"
    )
        port map (
      I0 => Q(11),
      I1 => \minus_out1_1_reg[12]_0\,
      I2 => Q(12),
      I3 => Q(13),
      I4 => Saturation1_out110_in,
      O => minus_out1(13)
    );
\minus_out1_1[13]_i_3__0\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"E"
    )
        port map (
      I0 => Q(10),
      I1 => Q(11),
      O => \minus_out1_1[13]_i_3__0_n_0\
    );
\minus_out1_1[13]_i_4__1\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"E"
    )
        port map (
      I0 => Q(8),
      I1 => Q(9),
      O => \minus_out1_1[13]_i_4__1_n_0\
    );
\minus_out1_1[13]_i_5__1\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"E"
    )
        port map (
      I0 => Q(6),
      I1 => Q(7),
      O => \minus_out1_1[13]_i_5__1_n_0\
    );
\minus_out1_1[13]_i_6__1\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"E"
    )
        port map (
      I0 => Q(4),
      I1 => Q(5),
      O => \minus_out1_1[13]_i_6__1_n_0\
    );
\minus_out1_1[13]_i_7__1\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"E"
    )
        port map (
      I0 => Q(2),
      I1 => Q(3),
      O => \minus_out1_1[13]_i_7__1_n_0\
    );
\minus_out1_1[13]_i_8__0\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"E"
    )
        port map (
      I0 => Q(0),
      I1 => Q(1),
      O => \minus_out1_1[13]_i_8__0_n_0\
    );
\minus_out1_1[13]_i_9__1\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"2"
    )
        port map (
      I0 => Q(12),
      I1 => Q(13),
      O => \minus_out1_1[13]_i_9__1_n_0\
    );
\minus_out1_1[1]_i_1__0\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"0006"
    )
        port map (
      I0 => Q(1),
      I1 => Q(0),
      I2 => Saturation1_out110_in,
      I3 => Q(13),
      O => minus_out1(1)
    );
\minus_out1_1[2]_i_1__0\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"00000056"
    )
        port map (
      I0 => Q(2),
      I1 => Q(0),
      I2 => Q(1),
      I3 => Saturation1_out110_in,
      I4 => Q(13),
      O => minus_out1(2)
    );
\minus_out1_1[3]_i_1__0\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"00005556"
    )
        port map (
      I0 => Q(3),
      I1 => Q(1),
      I2 => Q(0),
      I3 => Q(2),
      I4 => \minus_out1_1[5]_i_2__0_n_0\,
      O => minus_out1(3)
    );
\minus_out1_1[4]_i_1__0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0000000055555556"
    )
        port map (
      I0 => Q(4),
      I1 => Q(2),
      I2 => Q(0),
      I3 => Q(1),
      I4 => Q(3),
      I5 => \minus_out1_1[5]_i_2__0_n_0\,
      O => minus_out1(4)
    );
\minus_out1_1[5]_i_1__0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0000000055555556"
    )
        port map (
      I0 => Q(5),
      I1 => Q(3),
      I2 => \minus_out1_1_reg[5]_0\,
      I3 => Q(2),
      I4 => Q(4),
      I5 => \minus_out1_1[5]_i_2__0_n_0\,
      O => minus_out1(5)
    );
\minus_out1_1[5]_i_2__0\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"E"
    )
        port map (
      I0 => Q(13),
      I1 => Saturation1_out110_in,
      O => \minus_out1_1[5]_i_2__0_n_0\
    );
\minus_out1_1[6]_i_1__0\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"02"
    )
        port map (
      I0 => \minus_out1_1_reg[6]_0\,
      I1 => Saturation1_out110_in,
      I2 => Q(13),
      O => minus_out1(6)
    );
\minus_out1_1[7]_i_1__0\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"0000001E"
    )
        port map (
      I0 => Q(6),
      I1 => \minus_out1_1_reg[7]_0\,
      I2 => Q(7),
      I3 => Saturation1_out110_in,
      I4 => Q(13),
      O => minus_out1(7)
    );
\minus_out1_1[8]_i_1__0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"00000000000001FE"
    )
        port map (
      I0 => Q(7),
      I1 => \minus_out1_1_reg[7]_0\,
      I2 => Q(6),
      I3 => Q(8),
      I4 => Saturation1_out110_in,
      I5 => Q(13),
      O => minus_out1(8)
    );
\minus_out1_1[9]_i_1__0\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"02"
    )
        port map (
      I0 => \minus_out1_1_reg[9]_0\,
      I1 => Saturation1_out110_in,
      I2 => Q(13),
      O => minus_out1(9)
    );
\minus_out1_1_reg[10]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => minus_out1(10),
      Q => minus_out1_1(10),
      R => RSTP
    );
\minus_out1_1_reg[11]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => minus_out1(11),
      Q => minus_out1_1(11),
      R => RSTP
    );
\minus_out1_1_reg[12]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => minus_out1(12),
      Q => minus_out1_1(12),
      R => RSTP
    );
\minus_out1_1_reg[13]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => minus_out1(13),
      Q => minus_out1_1(13),
      R => RSTP
    );
\minus_out1_1_reg[13]_i_2\: unisim.vcomponents.CARRY8
     port map (
      CI => '0',
      CI_TOP => '0',
      CO(7) => \NLW_minus_out1_1_reg[13]_i_2_CO_UNCONNECTED\(7),
      CO(6) => Saturation1_out110_in,
      CO(5) => \minus_out1_1_reg[13]_i_2_n_2\,
      CO(4) => \minus_out1_1_reg[13]_i_2_n_3\,
      CO(3) => \minus_out1_1_reg[13]_i_2_n_4\,
      CO(2) => \minus_out1_1_reg[13]_i_2_n_5\,
      CO(1) => \minus_out1_1_reg[13]_i_2_n_6\,
      CO(0) => \minus_out1_1_reg[13]_i_2_n_7\,
      DI(7 downto 6) => B"00",
      DI(5) => \minus_out1_1[13]_i_3__0_n_0\,
      DI(4) => \minus_out1_1[13]_i_4__1_n_0\,
      DI(3) => \minus_out1_1[13]_i_5__1_n_0\,
      DI(2) => \minus_out1_1[13]_i_6__1_n_0\,
      DI(1) => \minus_out1_1[13]_i_7__1_n_0\,
      DI(0) => \minus_out1_1[13]_i_8__0_n_0\,
      O(7 downto 0) => \NLW_minus_out1_1_reg[13]_i_2_O_UNCONNECTED\(7 downto 0),
      S(7) => '0',
      S(6) => \minus_out1_1[13]_i_9__1_n_0\,
      S(5) => \minus_out1_1[13]_i_10__1_n_0\,
      S(4) => \minus_out1_1[13]_i_11__1_n_0\,
      S(3) => \minus_out1_1[13]_i_12__1_n_0\,
      S(2) => \minus_out1_1[13]_i_13__1_n_0\,
      S(1) => \minus_out1_1[13]_i_14__1_n_0\,
      S(0) => \minus_out1_1[13]_i_15__0_n_0\
    );
\minus_out1_1_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => minus_out1(1),
      Q => minus_out1_1(1),
      R => RSTP
    );
\minus_out1_1_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => minus_out1(2),
      Q => minus_out1_1(2),
      R => RSTP
    );
\minus_out1_1_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => minus_out1(3),
      Q => minus_out1_1(3),
      R => RSTP
    );
\minus_out1_1_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => minus_out1(4),
      Q => minus_out1_1(4),
      R => RSTP
    );
\minus_out1_1_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => minus_out1(5),
      Q => minus_out1_1(5),
      R => RSTP
    );
\minus_out1_1_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => minus_out1(6),
      Q => minus_out1_1(6),
      R => RSTP
    );
\minus_out1_1_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => minus_out1(7),
      Q => minus_out1_1(7),
      R => RSTP
    );
\minus_out1_1_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => minus_out1(8),
      Q => minus_out1_1(8),
      R => RSTP
    );
\minus_out1_1_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => minus_out1(9),
      Q => minus_out1_1(9),
      R => RSTP
    );
\modulating_signal_in_clock_cycles_1_reg_i_10__0\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFFF4540"
    )
        port map (
      I0 => \Logical_Operator_out1__1\,
      I1 => \Delay1_out1_reg[13]_0\(4),
      I2 => \^pwm_en_axi_2_reg\,
      I3 => \Delay1_out1_reg[13]\(4),
      I4 => \modulating_signal_in_clock_cycles_1_reg_i_17__0_n_0\,
      O => B(4)
    );
\modulating_signal_in_clock_cycles_1_reg_i_11__0\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"BABBBAAA"
    )
        port map (
      I0 => \modulating_signal_in_clock_cycles_1_reg_i_18__0_n_0\,
      I1 => \Logical_Operator_out1__1\,
      I2 => \Delay1_out1_reg[13]_0\(3),
      I3 => \^pwm_en_axi_2_reg\,
      I4 => \Delay1_out1_reg[13]\(3),
      O => B(3)
    );
\modulating_signal_in_clock_cycles_1_reg_i_12__0\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFFF4540"
    )
        port map (
      I0 => \Logical_Operator_out1__1\,
      I1 => \Delay1_out1_reg[13]_0\(2),
      I2 => \^pwm_en_axi_2_reg\,
      I3 => \Delay1_out1_reg[13]\(2),
      I4 => \modulating_signal_in_clock_cycles_1_reg_i_17__0_n_0\,
      O => B(2)
    );
\modulating_signal_in_clock_cycles_1_reg_i_13__0\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFFF4540"
    )
        port map (
      I0 => \Logical_Operator_out1__1\,
      I1 => \Delay1_out1_reg[13]_0\(1),
      I2 => \^pwm_en_axi_2_reg\,
      I3 => \Delay1_out1_reg[13]\(1),
      I4 => \modulating_signal_in_clock_cycles_1_reg_i_17__0_n_0\,
      O => B(1)
    );
\modulating_signal_in_clock_cycles_1_reg_i_14__0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"00FFFFFFB8B8B8B8"
    )
        port map (
      I0 => \Delay1_out1_reg[13]_0\(0),
      I1 => \^pwm_en_axi_2_reg\,
      I2 => \Delay1_out1_reg[13]\(0),
      I3 => Relational_Operator1_relop1,
      I4 => Relational_Operator_relop1,
      I5 => \Logical_Operator_out1__1\,
      O => B(0)
    );
\modulating_signal_in_clock_cycles_1_reg_i_15__0\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FEEE"
    )
        port map (
      I0 => Relational_Operator2_relop1,
      I1 => Relational_Operator3_relop1,
      I2 => Relational_Operator_relop1,
      I3 => Relational_Operator1_relop1,
      O => \Logical_Operator_out1__1\
    );
\modulating_signal_in_clock_cycles_1_reg_i_16__0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFFFFFF00008000"
    )
        port map (
      I0 => \Delay1_out1_reg[0]\,
      I1 => \Delay1_out1_reg[0]_0\,
      I2 => \Delay1_out1_reg[0]_1\,
      I3 => D(0),
      I4 => HDL_Counter2_count_reg(0),
      I5 => CO(0),
      O => \^pwm_en_axi_2_reg\
    );
\modulating_signal_in_clock_cycles_1_reg_i_17__0\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"70"
    )
        port map (
      I0 => Relational_Operator1_relop1,
      I1 => Relational_Operator_relop1,
      I2 => Relational_Operator2_relop1,
      O => \modulating_signal_in_clock_cycles_1_reg_i_17__0_n_0\
    );
\modulating_signal_in_clock_cycles_1_reg_i_18__0\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"0070"
    )
        port map (
      I0 => Relational_Operator1_relop1,
      I1 => Relational_Operator_relop1,
      I2 => Relational_Operator3_relop1,
      I3 => Relational_Operator2_relop1,
      O => \modulating_signal_in_clock_cycles_1_reg_i_18__0_n_0\
    );
\modulating_signal_in_clock_cycles_1_reg_i_1__0\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFFF4540"
    )
        port map (
      I0 => \Logical_Operator_out1__1\,
      I1 => \Delay1_out1_reg[13]_0\(13),
      I2 => \^pwm_en_axi_2_reg\,
      I3 => \Delay1_out1_reg[13]\(13),
      I4 => \modulating_signal_in_clock_cycles_1_reg_i_17__0_n_0\,
      O => B(13)
    );
\modulating_signal_in_clock_cycles_1_reg_i_2__0\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"BABBBAAA"
    )
        port map (
      I0 => \modulating_signal_in_clock_cycles_1_reg_i_18__0_n_0\,
      I1 => \Logical_Operator_out1__1\,
      I2 => \Delay1_out1_reg[13]_0\(12),
      I3 => \^pwm_en_axi_2_reg\,
      I4 => \Delay1_out1_reg[13]\(12),
      O => B(12)
    );
\modulating_signal_in_clock_cycles_1_reg_i_3__0\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFFF4540"
    )
        port map (
      I0 => \Logical_Operator_out1__1\,
      I1 => \Delay1_out1_reg[13]_0\(11),
      I2 => \^pwm_en_axi_2_reg\,
      I3 => \Delay1_out1_reg[13]\(11),
      I4 => \modulating_signal_in_clock_cycles_1_reg_i_17__0_n_0\,
      O => B(11)
    );
\modulating_signal_in_clock_cycles_1_reg_i_4__0\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFFF4540"
    )
        port map (
      I0 => \Logical_Operator_out1__1\,
      I1 => \Delay1_out1_reg[13]_0\(10),
      I2 => \^pwm_en_axi_2_reg\,
      I3 => \Delay1_out1_reg[13]\(10),
      I4 => \modulating_signal_in_clock_cycles_1_reg_i_17__0_n_0\,
      O => B(10)
    );
\modulating_signal_in_clock_cycles_1_reg_i_5__0\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFFF4540"
    )
        port map (
      I0 => \Logical_Operator_out1__1\,
      I1 => \Delay1_out1_reg[13]_0\(9),
      I2 => \^pwm_en_axi_2_reg\,
      I3 => \Delay1_out1_reg[13]\(9),
      I4 => \modulating_signal_in_clock_cycles_1_reg_i_17__0_n_0\,
      O => B(9)
    );
\modulating_signal_in_clock_cycles_1_reg_i_6__0\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFFF4540"
    )
        port map (
      I0 => \Logical_Operator_out1__1\,
      I1 => \Delay1_out1_reg[13]_0\(8),
      I2 => \^pwm_en_axi_2_reg\,
      I3 => \Delay1_out1_reg[13]\(8),
      I4 => \modulating_signal_in_clock_cycles_1_reg_i_17__0_n_0\,
      O => B(8)
    );
\modulating_signal_in_clock_cycles_1_reg_i_7__0\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFFF4540"
    )
        port map (
      I0 => \Logical_Operator_out1__1\,
      I1 => \Delay1_out1_reg[13]_0\(7),
      I2 => \^pwm_en_axi_2_reg\,
      I3 => \Delay1_out1_reg[13]\(7),
      I4 => \modulating_signal_in_clock_cycles_1_reg_i_17__0_n_0\,
      O => B(7)
    );
\modulating_signal_in_clock_cycles_1_reg_i_8__0\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFFF4540"
    )
        port map (
      I0 => \Logical_Operator_out1__1\,
      I1 => \Delay1_out1_reg[13]_0\(6),
      I2 => \^pwm_en_axi_2_reg\,
      I3 => \Delay1_out1_reg[13]\(6),
      I4 => \modulating_signal_in_clock_cycles_1_reg_i_17__0_n_0\,
      O => B(6)
    );
\modulating_signal_in_clock_cycles_1_reg_i_9__0\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"BABBBAAA"
    )
        port map (
      I0 => \modulating_signal_in_clock_cycles_1_reg_i_18__0_n_0\,
      I1 => \Logical_Operator_out1__1\,
      I2 => \Delay1_out1_reg[13]_0\(5),
      I3 => \^pwm_en_axi_2_reg\,
      I4 => \Delay1_out1_reg[13]\(5),
      O => B(5)
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity zusys_PWM_SS_3L_ip_0_0_PWM_SS_3L_ip_src_LimitPulseWidth_c is
  port (
    \min_pulse_width_AXI_1_reg[9]\ : out STD_LOGIC;
    \delayMatch5_reg_reg[1][13]\ : out STD_LOGIC;
    PWM_en_AXI_2_reg : out STD_LOGIC;
    B : out STD_LOGIC_VECTOR ( 13 downto 0 );
    \delayMatch5_reg_reg[1][11]\ : out STD_LOGIC;
    \delayMatch5_reg_reg[1][9]\ : out STD_LOGIC;
    \delayMatch5_reg_reg[1][7]\ : out STD_LOGIC;
    \delayMatch5_reg_reg[1][5]\ : out STD_LOGIC;
    \delayMatch5_reg_reg[1][3]\ : out STD_LOGIC;
    \delayMatch5_reg_reg[1][1]\ : out STD_LOGIC;
    HDL_Counter2_count_reg_16_sp_1 : out STD_LOGIC;
    HDL_Counter2_count_reg_13_sp_1 : out STD_LOGIC;
    HDL_Counter2_count_reg_1_sp_1 : out STD_LOGIC;
    HDL_Counter2_count_reg_10_sp_1 : out STD_LOGIC;
    HDL_Counter2_count_reg_7_sp_1 : out STD_LOGIC;
    \HDL_Counter2_count_reg[18]\ : out STD_LOGIC_VECTOR ( 6 downto 0 );
    RSTP : in STD_LOGIC;
    CEP : in STD_LOGIC;
    IPCORE_CLK : in STD_LOGIC;
    Q : in STD_LOGIC_VECTOR ( 13 downto 0 );
    \minus_out1_1_reg[7]_0\ : in STD_LOGIC;
    CO : in STD_LOGIC_VECTOR ( 0 to 0 );
    \Delay2_out1_reg[13]\ : in STD_LOGIC_VECTOR ( 13 downto 0 );
    \Delay2_out1_reg[13]_0\ : in STD_LOGIC_VECTOR ( 13 downto 0 );
    \Delay2_out1_reg[13]_1\ : in STD_LOGIC;
    D : in STD_LOGIC_VECTOR ( 0 to 0 );
    HDL_Counter2_count_reg : in STD_LOGIC_VECTOR ( 19 downto 0 );
    \Delay2_out1_reg[13]_2\ : in STD_LOGIC_VECTOR ( 0 to 0 );
    maximum_counter_value_1 : in STD_LOGIC_VECTOR ( 19 downto 0 );
    \Delay2_out1_reg[0]\ : in STD_LOGIC;
    \minus_out1_1_reg[5]_0\ : in STD_LOGIC;
    \minus_out1_1_reg[6]_0\ : in STD_LOGIC;
    \minus_out1_1_reg[9]_0\ : in STD_LOGIC;
    \minus_out1_1_reg[10]_0\ : in STD_LOGIC;
    \minus_out1_1_reg[11]_0\ : in STD_LOGIC
  );
  attribute ORIG_REF_NAME : string;
  attribute ORIG_REF_NAME of zusys_PWM_SS_3L_ip_0_0_PWM_SS_3L_ip_src_LimitPulseWidth_c : entity is "PWM_SS_3L_ip_src_LimitPulseWidth_c";
end zusys_PWM_SS_3L_ip_0_0_PWM_SS_3L_ip_src_LimitPulseWidth_c;

architecture STRUCTURE of zusys_PWM_SS_3L_ip_0_0_PWM_SS_3L_ip_src_LimitPulseWidth_c is
  signal Add1_out1 : STD_LOGIC_VECTOR ( 13 downto 11 );
  signal Add1_out1_1 : STD_LOGIC_VECTOR ( 13 downto 0 );
  signal \Add1_out1_1[13]_i_2__1_n_0\ : STD_LOGIC;
  signal \Add1_out1_1[13]_i_3_n_0\ : STD_LOGIC;
  signal \Add1_out1_1[13]_i_4__1_n_0\ : STD_LOGIC;
  signal \Add1_out1_1_reg[13]_i_1__1_n_6\ : STD_LOGIC;
  signal \Add1_out1_1_reg[13]_i_1__1_n_7\ : STD_LOGIC;
  signal Add2_out1 : STD_LOGIC_VECTOR ( 13 downto 1 );
  signal Add2_out1_1 : STD_LOGIC_VECTOR ( 13 downto 1 );
  signal \Add2_out1_1[13]_i_2__1_n_0\ : STD_LOGIC;
  signal \Add2_out1_1[13]_i_3__1_n_0\ : STD_LOGIC;
  signal \Add2_out1_1[13]_i_4__1_n_0\ : STD_LOGIC;
  signal \Add2_out1_1[13]_i_5__1_n_0\ : STD_LOGIC;
  signal \Add2_out1_1[8]_i_10__1_n_0\ : STD_LOGIC;
  signal \Add2_out1_1[8]_i_2__1_n_0\ : STD_LOGIC;
  signal \Add2_out1_1[8]_i_3__1_n_0\ : STD_LOGIC;
  signal \Add2_out1_1[8]_i_4__1_n_0\ : STD_LOGIC;
  signal \Add2_out1_1[8]_i_5__1_n_0\ : STD_LOGIC;
  signal \Add2_out1_1[8]_i_6__1_n_0\ : STD_LOGIC;
  signal \Add2_out1_1[8]_i_7__1_n_0\ : STD_LOGIC;
  signal \Add2_out1_1[8]_i_8__1_n_0\ : STD_LOGIC;
  signal \Add2_out1_1[8]_i_9__1_n_0\ : STD_LOGIC;
  signal \Add2_out1_1_reg[13]_i_1__1_n_4\ : STD_LOGIC;
  signal \Add2_out1_1_reg[13]_i_1__1_n_5\ : STD_LOGIC;
  signal \Add2_out1_1_reg[13]_i_1__1_n_6\ : STD_LOGIC;
  signal \Add2_out1_1_reg[13]_i_1__1_n_7\ : STD_LOGIC;
  signal \Add2_out1_1_reg[8]_i_1__1_n_0\ : STD_LOGIC;
  signal \Add2_out1_1_reg[8]_i_1__1_n_1\ : STD_LOGIC;
  signal \Add2_out1_1_reg[8]_i_1__1_n_2\ : STD_LOGIC;
  signal \Add2_out1_1_reg[8]_i_1__1_n_3\ : STD_LOGIC;
  signal \Add2_out1_1_reg[8]_i_1__1_n_4\ : STD_LOGIC;
  signal \Add2_out1_1_reg[8]_i_1__1_n_5\ : STD_LOGIC;
  signal \Add2_out1_1_reg[8]_i_1__1_n_6\ : STD_LOGIC;
  signal \Add2_out1_1_reg[8]_i_1__1_n_7\ : STD_LOGIC;
  signal HDL_Counter2_count_reg_10_sn_1 : STD_LOGIC;
  signal HDL_Counter2_count_reg_13_sn_1 : STD_LOGIC;
  signal HDL_Counter2_count_reg_16_sn_1 : STD_LOGIC;
  signal HDL_Counter2_count_reg_1_sn_1 : STD_LOGIC;
  signal HDL_Counter2_count_reg_7_sn_1 : STD_LOGIC;
  signal Logical_Operator1_out10_carry_i_10_n_0 : STD_LOGIC;
  signal Logical_Operator1_out10_carry_i_11_n_0 : STD_LOGIC;
  signal Logical_Operator1_out10_carry_i_12_n_0 : STD_LOGIC;
  signal Logical_Operator1_out10_carry_i_13_n_0 : STD_LOGIC;
  signal Logical_Operator1_out10_carry_i_14_n_0 : STD_LOGIC;
  signal Logical_Operator1_out10_carry_i_1_n_0 : STD_LOGIC;
  signal Logical_Operator1_out10_carry_i_2_n_0 : STD_LOGIC;
  signal Logical_Operator1_out10_carry_i_3_n_0 : STD_LOGIC;
  signal Logical_Operator1_out10_carry_i_4_n_0 : STD_LOGIC;
  signal Logical_Operator1_out10_carry_i_5_n_0 : STD_LOGIC;
  signal Logical_Operator1_out10_carry_i_6_n_0 : STD_LOGIC;
  signal Logical_Operator1_out10_carry_i_7_n_0 : STD_LOGIC;
  signal Logical_Operator1_out10_carry_i_8_n_0 : STD_LOGIC;
  signal Logical_Operator1_out10_carry_i_9_n_0 : STD_LOGIC;
  signal Logical_Operator1_out10_carry_n_2 : STD_LOGIC;
  signal Logical_Operator1_out10_carry_n_3 : STD_LOGIC;
  signal Logical_Operator1_out10_carry_n_4 : STD_LOGIC;
  signal Logical_Operator1_out10_carry_n_5 : STD_LOGIC;
  signal Logical_Operator1_out10_carry_n_6 : STD_LOGIC;
  signal Logical_Operator1_out10_carry_n_7 : STD_LOGIC;
  signal \Logical_Operator1_out10_inferred__0/i__carry_n_2\ : STD_LOGIC;
  signal \Logical_Operator1_out10_inferred__0/i__carry_n_3\ : STD_LOGIC;
  signal \Logical_Operator1_out10_inferred__0/i__carry_n_4\ : STD_LOGIC;
  signal \Logical_Operator1_out10_inferred__0/i__carry_n_5\ : STD_LOGIC;
  signal \Logical_Operator1_out10_inferred__0/i__carry_n_6\ : STD_LOGIC;
  signal \Logical_Operator1_out10_inferred__0/i__carry_n_7\ : STD_LOGIC;
  signal Logical_Operator_out10_carry_i_10_n_0 : STD_LOGIC;
  signal Logical_Operator_out10_carry_i_11_n_0 : STD_LOGIC;
  signal Logical_Operator_out10_carry_i_12_n_0 : STD_LOGIC;
  signal Logical_Operator_out10_carry_i_13_n_0 : STD_LOGIC;
  signal Logical_Operator_out10_carry_i_14_n_0 : STD_LOGIC;
  signal Logical_Operator_out10_carry_i_1_n_0 : STD_LOGIC;
  signal Logical_Operator_out10_carry_i_2_n_0 : STD_LOGIC;
  signal Logical_Operator_out10_carry_i_3_n_0 : STD_LOGIC;
  signal Logical_Operator_out10_carry_i_4_n_0 : STD_LOGIC;
  signal Logical_Operator_out10_carry_i_5_n_0 : STD_LOGIC;
  signal Logical_Operator_out10_carry_i_6_n_0 : STD_LOGIC;
  signal Logical_Operator_out10_carry_i_7_n_0 : STD_LOGIC;
  signal Logical_Operator_out10_carry_i_8_n_0 : STD_LOGIC;
  signal Logical_Operator_out10_carry_i_9_n_0 : STD_LOGIC;
  signal Logical_Operator_out10_carry_n_2 : STD_LOGIC;
  signal Logical_Operator_out10_carry_n_3 : STD_LOGIC;
  signal Logical_Operator_out10_carry_n_4 : STD_LOGIC;
  signal Logical_Operator_out10_carry_n_5 : STD_LOGIC;
  signal Logical_Operator_out10_carry_n_6 : STD_LOGIC;
  signal Logical_Operator_out10_carry_n_7 : STD_LOGIC;
  signal Logical_Operator_out11_carry_i_1_n_0 : STD_LOGIC;
  signal Logical_Operator_out11_carry_i_2_n_0 : STD_LOGIC;
  signal Logical_Operator_out11_carry_i_3_n_0 : STD_LOGIC;
  signal Logical_Operator_out11_carry_i_4_n_0 : STD_LOGIC;
  signal Logical_Operator_out11_carry_i_5_n_0 : STD_LOGIC;
  signal Logical_Operator_out11_carry_i_6_n_0 : STD_LOGIC;
  signal Logical_Operator_out11_carry_i_7_n_0 : STD_LOGIC;
  signal Logical_Operator_out11_carry_i_8_n_0 : STD_LOGIC;
  signal Logical_Operator_out11_carry_i_9_n_0 : STD_LOGIC;
  signal Logical_Operator_out11_carry_n_2 : STD_LOGIC;
  signal Logical_Operator_out11_carry_n_3 : STD_LOGIC;
  signal Logical_Operator_out11_carry_n_4 : STD_LOGIC;
  signal Logical_Operator_out11_carry_n_5 : STD_LOGIC;
  signal Logical_Operator_out11_carry_n_6 : STD_LOGIC;
  signal Logical_Operator_out11_carry_n_7 : STD_LOGIC;
  signal \Logical_Operator_out1__1\ : STD_LOGIC;
  signal \^pwm_en_axi_2_reg\ : STD_LOGIC;
  signal Relational_Operator1_relop1 : STD_LOGIC;
  signal Relational_Operator2_relop1 : STD_LOGIC;
  signal Relational_Operator3_relop1 : STD_LOGIC;
  signal Relational_Operator_relop1 : STD_LOGIC;
  signal Saturation1_out1 : STD_LOGIC_VECTOR ( 12 downto 0 );
  signal Saturation1_out1_1 : STD_LOGIC_VECTOR ( 12 downto 11 );
  signal \^delaymatch5_reg_reg[1][11]\ : STD_LOGIC;
  signal \^delaymatch5_reg_reg[1][13]\ : STD_LOGIC;
  signal \^delaymatch5_reg_reg[1][1]\ : STD_LOGIC;
  signal \^delaymatch5_reg_reg[1][3]\ : STD_LOGIC;
  signal \^delaymatch5_reg_reg[1][5]\ : STD_LOGIC;
  signal \^delaymatch5_reg_reg[1][7]\ : STD_LOGIC;
  signal \^delaymatch5_reg_reg[1][9]\ : STD_LOGIC;
  signal \i__carry_i_10__1_n_0\ : STD_LOGIC;
  signal \i__carry_i_11__1_n_0\ : STD_LOGIC;
  signal \i__carry_i_12__1_n_0\ : STD_LOGIC;
  signal \i__carry_i_13__1_n_0\ : STD_LOGIC;
  signal \i__carry_i_14__1_n_0\ : STD_LOGIC;
  signal \i__carry_i_1_n_0\ : STD_LOGIC;
  signal \i__carry_i_2_n_0\ : STD_LOGIC;
  signal \i__carry_i_3_n_0\ : STD_LOGIC;
  signal \i__carry_i_4_n_0\ : STD_LOGIC;
  signal \i__carry_i_5_n_0\ : STD_LOGIC;
  signal \i__carry_i_6_n_0\ : STD_LOGIC;
  signal \i__carry_i_7_n_0\ : STD_LOGIC;
  signal \i__carry_i_8_n_0\ : STD_LOGIC;
  signal \i__carry_i_9_n_0\ : STD_LOGIC;
  signal \^min_pulse_width_axi_1_reg[9]\ : STD_LOGIC;
  signal minus_out1 : STD_LOGIC_VECTOR ( 13 downto 1 );
  signal minus_out1_1 : STD_LOGIC_VECTOR ( 13 downto 1 );
  signal \minus_out1_1[5]_i_2__1_n_0\ : STD_LOGIC;
  signal \modulating_signal_in_clock_cycles_1_reg_i_17__1_n_0\ : STD_LOGIC;
  signal \modulating_signal_in_clock_cycles_1_reg_i_18__1_n_0\ : STD_LOGIC;
  signal \NLW_Add1_out1_1_reg[13]_i_1__1_CO_UNCONNECTED\ : STD_LOGIC_VECTOR ( 7 downto 2 );
  signal \NLW_Add1_out1_1_reg[13]_i_1__1_O_UNCONNECTED\ : STD_LOGIC_VECTOR ( 7 downto 3 );
  signal \NLW_Add2_out1_1_reg[13]_i_1__1_CO_UNCONNECTED\ : STD_LOGIC_VECTOR ( 7 downto 4 );
  signal \NLW_Add2_out1_1_reg[13]_i_1__1_O_UNCONNECTED\ : STD_LOGIC_VECTOR ( 7 downto 5 );
  signal NLW_Logical_Operator1_out10_carry_CO_UNCONNECTED : STD_LOGIC_VECTOR ( 7 to 7 );
  signal NLW_Logical_Operator1_out10_carry_O_UNCONNECTED : STD_LOGIC_VECTOR ( 7 downto 0 );
  signal \NLW_Logical_Operator1_out10_inferred__0/i__carry_CO_UNCONNECTED\ : STD_LOGIC_VECTOR ( 7 to 7 );
  signal \NLW_Logical_Operator1_out10_inferred__0/i__carry_O_UNCONNECTED\ : STD_LOGIC_VECTOR ( 7 downto 0 );
  signal NLW_Logical_Operator_out10_carry_CO_UNCONNECTED : STD_LOGIC_VECTOR ( 7 to 7 );
  signal NLW_Logical_Operator_out10_carry_O_UNCONNECTED : STD_LOGIC_VECTOR ( 7 downto 0 );
  signal NLW_Logical_Operator_out11_carry_CO_UNCONNECTED : STD_LOGIC_VECTOR ( 7 to 7 );
  signal NLW_Logical_Operator_out11_carry_O_UNCONNECTED : STD_LOGIC_VECTOR ( 7 downto 0 );
  attribute SOFT_HLUTNM : string;
  attribute SOFT_HLUTNM of \Add1_out1_1[0]_i_1__1\ : label is "soft_lutpair44";
  attribute SOFT_HLUTNM of \Add1_out1_1[10]_i_1__1\ : label is "soft_lutpair49";
  attribute SOFT_HLUTNM of \Add1_out1_1[1]_i_1__1\ : label is "soft_lutpair45";
  attribute SOFT_HLUTNM of \Add1_out1_1[2]_i_1__1\ : label is "soft_lutpair45";
  attribute SOFT_HLUTNM of \Add1_out1_1[3]_i_1__1\ : label is "soft_lutpair46";
  attribute SOFT_HLUTNM of \Add1_out1_1[4]_i_1__1\ : label is "soft_lutpair46";
  attribute SOFT_HLUTNM of \Add1_out1_1[5]_i_1__1\ : label is "soft_lutpair47";
  attribute SOFT_HLUTNM of \Add1_out1_1[6]_i_1__1\ : label is "soft_lutpair38";
  attribute SOFT_HLUTNM of \Add1_out1_1[7]_i_1__1\ : label is "soft_lutpair47";
  attribute SOFT_HLUTNM of \Add1_out1_1[8]_i_1__1\ : label is "soft_lutpair48";
  attribute SOFT_HLUTNM of \Add1_out1_1[9]_i_1__1\ : label is "soft_lutpair48";
  attribute ADDER_THRESHOLD : integer;
  attribute ADDER_THRESHOLD of \Add1_out1_1_reg[13]_i_1__1\ : label is 35;
  attribute ADDER_THRESHOLD of \Add2_out1_1_reg[13]_i_1__1\ : label is 35;
  attribute ADDER_THRESHOLD of \Add2_out1_1_reg[8]_i_1__1\ : label is 35;
  attribute COMPARATOR_THRESHOLD : integer;
  attribute COMPARATOR_THRESHOLD of Logical_Operator1_out10_carry : label is 11;
  attribute COMPARATOR_THRESHOLD of \Logical_Operator1_out10_inferred__0/i__carry\ : label is 11;
  attribute COMPARATOR_THRESHOLD of Logical_Operator_out10_carry : label is 11;
  attribute COMPARATOR_THRESHOLD of Logical_Operator_out11_carry : label is 11;
  attribute SOFT_HLUTNM of \Saturation1_out1_1[11]_i_1__1\ : label is "soft_lutpair49";
  attribute SOFT_HLUTNM of \Saturation1_out1_1[12]_i_1\ : label is "soft_lutpair42";
  attribute SOFT_HLUTNM of \minus_out1_1[10]_i_1\ : label is "soft_lutpair43";
  attribute SOFT_HLUTNM of \minus_out1_1[11]_i_1\ : label is "soft_lutpair44";
  attribute SOFT_HLUTNM of \minus_out1_1[12]_i_1__1\ : label is "soft_lutpair39";
  attribute SOFT_HLUTNM of \minus_out1_1[13]_i_1__1\ : label is "soft_lutpair39";
  attribute SOFT_HLUTNM of \minus_out1_1[1]_i_1__1\ : label is "soft_lutpair40";
  attribute SOFT_HLUTNM of \minus_out1_1[2]_i_1\ : label is "soft_lutpair40";
  attribute SOFT_HLUTNM of \minus_out1_1[6]_i_1\ : label is "soft_lutpair42";
  attribute SOFT_HLUTNM of \minus_out1_1[7]_i_1__1\ : label is "soft_lutpair38";
  attribute SOFT_HLUTNM of \minus_out1_1[9]_i_1\ : label is "soft_lutpair43";
  attribute SOFT_HLUTNM of \modulating_signal_in_clock_cycles_1_reg_i_15__1\ : label is "soft_lutpair41";
  attribute SOFT_HLUTNM of \modulating_signal_in_clock_cycles_1_reg_i_18__1\ : label is "soft_lutpair41";
begin
  HDL_Counter2_count_reg_10_sp_1 <= HDL_Counter2_count_reg_10_sn_1;
  HDL_Counter2_count_reg_13_sp_1 <= HDL_Counter2_count_reg_13_sn_1;
  HDL_Counter2_count_reg_16_sp_1 <= HDL_Counter2_count_reg_16_sn_1;
  HDL_Counter2_count_reg_1_sp_1 <= HDL_Counter2_count_reg_1_sn_1;
  HDL_Counter2_count_reg_7_sp_1 <= HDL_Counter2_count_reg_7_sn_1;
  PWM_en_AXI_2_reg <= \^pwm_en_axi_2_reg\;
  \delayMatch5_reg_reg[1][11]\ <= \^delaymatch5_reg_reg[1][11]\;
  \delayMatch5_reg_reg[1][13]\ <= \^delaymatch5_reg_reg[1][13]\;
  \delayMatch5_reg_reg[1][1]\ <= \^delaymatch5_reg_reg[1][1]\;
  \delayMatch5_reg_reg[1][3]\ <= \^delaymatch5_reg_reg[1][3]\;
  \delayMatch5_reg_reg[1][5]\ <= \^delaymatch5_reg_reg[1][5]\;
  \delayMatch5_reg_reg[1][7]\ <= \^delaymatch5_reg_reg[1][7]\;
  \delayMatch5_reg_reg[1][9]\ <= \^delaymatch5_reg_reg[1][9]\;
  \min_pulse_width_AXI_1_reg[9]\ <= \^min_pulse_width_axi_1_reg[9]\;
\Add1_out1_1[0]_i_1__1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"02"
    )
        port map (
      I0 => Q(0),
      I1 => CO(0),
      I2 => Q(13),
      O => Saturation1_out1(0)
    );
\Add1_out1_1[10]_i_1__1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"02"
    )
        port map (
      I0 => Q(10),
      I1 => CO(0),
      I2 => Q(13),
      O => Saturation1_out1(10)
    );
\Add1_out1_1[13]_i_2__1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"BA"
    )
        port map (
      I0 => CO(0),
      I1 => Q(13),
      I2 => Q(12),
      O => \Add1_out1_1[13]_i_2__1_n_0\
    );
\Add1_out1_1[13]_i_3\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"0D"
    )
        port map (
      I0 => Q(12),
      I1 => Q(13),
      I2 => CO(0),
      O => \Add1_out1_1[13]_i_3_n_0\
    );
\Add1_out1_1[13]_i_4__1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"02"
    )
        port map (
      I0 => Q(11),
      I1 => CO(0),
      I2 => Q(13),
      O => \Add1_out1_1[13]_i_4__1_n_0\
    );
\Add1_out1_1[1]_i_1__1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"02"
    )
        port map (
      I0 => Q(1),
      I1 => CO(0),
      I2 => Q(13),
      O => Saturation1_out1(1)
    );
\Add1_out1_1[2]_i_1__1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"02"
    )
        port map (
      I0 => Q(2),
      I1 => CO(0),
      I2 => Q(13),
      O => Saturation1_out1(2)
    );
\Add1_out1_1[3]_i_1__1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"02"
    )
        port map (
      I0 => Q(3),
      I1 => CO(0),
      I2 => Q(13),
      O => Saturation1_out1(3)
    );
\Add1_out1_1[4]_i_1__1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"02"
    )
        port map (
      I0 => Q(4),
      I1 => CO(0),
      I2 => Q(13),
      O => Saturation1_out1(4)
    );
\Add1_out1_1[5]_i_1__1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"02"
    )
        port map (
      I0 => Q(5),
      I1 => CO(0),
      I2 => Q(13),
      O => Saturation1_out1(5)
    );
\Add1_out1_1[6]_i_1__1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"02"
    )
        port map (
      I0 => Q(6),
      I1 => CO(0),
      I2 => Q(13),
      O => Saturation1_out1(6)
    );
\Add1_out1_1[7]_i_1__1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"02"
    )
        port map (
      I0 => Q(7),
      I1 => CO(0),
      I2 => Q(13),
      O => Saturation1_out1(7)
    );
\Add1_out1_1[8]_i_1__1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"02"
    )
        port map (
      I0 => Q(8),
      I1 => CO(0),
      I2 => Q(13),
      O => Saturation1_out1(8)
    );
\Add1_out1_1[9]_i_1__1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"02"
    )
        port map (
      I0 => Q(9),
      I1 => CO(0),
      I2 => Q(13),
      O => Saturation1_out1(9)
    );
\Add1_out1_1_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => Saturation1_out1(0),
      Q => Add1_out1_1(0),
      R => RSTP
    );
\Add1_out1_1_reg[10]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => Saturation1_out1(10),
      Q => Add1_out1_1(10),
      R => RSTP
    );
\Add1_out1_1_reg[11]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => Add1_out1(11),
      Q => Add1_out1_1(11),
      R => RSTP
    );
\Add1_out1_1_reg[12]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => Add1_out1(12),
      Q => Add1_out1_1(12),
      R => RSTP
    );
\Add1_out1_1_reg[13]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => Add1_out1(13),
      Q => Add1_out1_1(13),
      R => RSTP
    );
\Add1_out1_1_reg[13]_i_1__1\: unisim.vcomponents.CARRY8
     port map (
      CI => '0',
      CI_TOP => '0',
      CO(7 downto 2) => \NLW_Add1_out1_1_reg[13]_i_1__1_CO_UNCONNECTED\(7 downto 2),
      CO(1) => \Add1_out1_1_reg[13]_i_1__1_n_6\,
      CO(0) => \Add1_out1_1_reg[13]_i_1__1_n_7\,
      DI(7 downto 2) => B"000000",
      DI(1) => \Add1_out1_1[13]_i_2__1_n_0\,
      DI(0) => '0',
      O(7 downto 3) => \NLW_Add1_out1_1_reg[13]_i_1__1_O_UNCONNECTED\(7 downto 3),
      O(2 downto 0) => Add1_out1(13 downto 11),
      S(7 downto 2) => B"000001",
      S(1) => \Add1_out1_1[13]_i_3_n_0\,
      S(0) => \Add1_out1_1[13]_i_4__1_n_0\
    );
\Add1_out1_1_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => Saturation1_out1(1),
      Q => Add1_out1_1(1),
      R => RSTP
    );
\Add1_out1_1_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => Saturation1_out1(2),
      Q => Add1_out1_1(2),
      R => RSTP
    );
\Add1_out1_1_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => Saturation1_out1(3),
      Q => Add1_out1_1(3),
      R => RSTP
    );
\Add1_out1_1_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => Saturation1_out1(4),
      Q => Add1_out1_1(4),
      R => RSTP
    );
\Add1_out1_1_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => Saturation1_out1(5),
      Q => Add1_out1_1(5),
      R => RSTP
    );
\Add1_out1_1_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => Saturation1_out1(6),
      Q => Add1_out1_1(6),
      R => RSTP
    );
\Add1_out1_1_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => Saturation1_out1(7),
      Q => Add1_out1_1(7),
      R => RSTP
    );
\Add1_out1_1_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => Saturation1_out1(8),
      Q => Add1_out1_1(8),
      R => RSTP
    );
\Add1_out1_1_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => Saturation1_out1(9),
      Q => Add1_out1_1(9),
      R => RSTP
    );
\Add2_out1_1[13]_i_2__1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"BA"
    )
        port map (
      I0 => CO(0),
      I1 => Q(13),
      I2 => Q(12),
      O => \Add2_out1_1[13]_i_2__1_n_0\
    );
\Add2_out1_1[13]_i_3__1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"EF"
    )
        port map (
      I0 => Q(13),
      I1 => CO(0),
      I2 => Q(11),
      O => \Add2_out1_1[13]_i_3__1_n_0\
    );
\Add2_out1_1[13]_i_4__1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"EF"
    )
        port map (
      I0 => Q(13),
      I1 => CO(0),
      I2 => Q(10),
      O => \Add2_out1_1[13]_i_4__1_n_0\
    );
\Add2_out1_1[13]_i_5__1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"EF"
    )
        port map (
      I0 => Q(13),
      I1 => CO(0),
      I2 => Q(9),
      O => \Add2_out1_1[13]_i_5__1_n_0\
    );
\Add2_out1_1[8]_i_10__1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"EF"
    )
        port map (
      I0 => Q(13),
      I1 => CO(0),
      I2 => Q(1),
      O => \Add2_out1_1[8]_i_10__1_n_0\
    );
\Add2_out1_1[8]_i_2__1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"EF"
    )
        port map (
      I0 => Q(13),
      I1 => CO(0),
      I2 => Q(0),
      O => \Add2_out1_1[8]_i_2__1_n_0\
    );
\Add2_out1_1[8]_i_3__1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"EF"
    )
        port map (
      I0 => Q(13),
      I1 => CO(0),
      I2 => Q(8),
      O => \Add2_out1_1[8]_i_3__1_n_0\
    );
\Add2_out1_1[8]_i_4__1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"EF"
    )
        port map (
      I0 => Q(13),
      I1 => CO(0),
      I2 => Q(7),
      O => \Add2_out1_1[8]_i_4__1_n_0\
    );
\Add2_out1_1[8]_i_5__1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"EF"
    )
        port map (
      I0 => Q(13),
      I1 => CO(0),
      I2 => Q(6),
      O => \Add2_out1_1[8]_i_5__1_n_0\
    );
\Add2_out1_1[8]_i_6__1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"EF"
    )
        port map (
      I0 => Q(13),
      I1 => CO(0),
      I2 => Q(5),
      O => \Add2_out1_1[8]_i_6__1_n_0\
    );
\Add2_out1_1[8]_i_7__1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"EF"
    )
        port map (
      I0 => Q(13),
      I1 => CO(0),
      I2 => Q(4),
      O => \Add2_out1_1[8]_i_7__1_n_0\
    );
\Add2_out1_1[8]_i_8__1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"EF"
    )
        port map (
      I0 => Q(13),
      I1 => CO(0),
      I2 => Q(3),
      O => \Add2_out1_1[8]_i_8__1_n_0\
    );
\Add2_out1_1[8]_i_9__1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"EF"
    )
        port map (
      I0 => Q(13),
      I1 => CO(0),
      I2 => Q(2),
      O => \Add2_out1_1[8]_i_9__1_n_0\
    );
\Add2_out1_1_reg[10]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => Add2_out1(10),
      Q => Add2_out1_1(10),
      R => RSTP
    );
\Add2_out1_1_reg[11]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => Add2_out1(11),
      Q => Add2_out1_1(11),
      R => RSTP
    );
\Add2_out1_1_reg[12]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => Add2_out1(12),
      Q => Add2_out1_1(12),
      R => RSTP
    );
\Add2_out1_1_reg[13]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => Add2_out1(13),
      Q => Add2_out1_1(13),
      R => RSTP
    );
\Add2_out1_1_reg[13]_i_1__1\: unisim.vcomponents.CARRY8
     port map (
      CI => \Add2_out1_1_reg[8]_i_1__1_n_0\,
      CI_TOP => '0',
      CO(7 downto 4) => \NLW_Add2_out1_1_reg[13]_i_1__1_CO_UNCONNECTED\(7 downto 4),
      CO(3) => \Add2_out1_1_reg[13]_i_1__1_n_4\,
      CO(2) => \Add2_out1_1_reg[13]_i_1__1_n_5\,
      CO(1) => \Add2_out1_1_reg[13]_i_1__1_n_6\,
      CO(0) => \Add2_out1_1_reg[13]_i_1__1_n_7\,
      DI(7 downto 0) => B"00001000",
      O(7 downto 5) => \NLW_Add2_out1_1_reg[13]_i_1__1_O_UNCONNECTED\(7 downto 5),
      O(4 downto 0) => Add2_out1(13 downto 9),
      S(7 downto 4) => B"0001",
      S(3) => \Add2_out1_1[13]_i_2__1_n_0\,
      S(2) => \Add2_out1_1[13]_i_3__1_n_0\,
      S(1) => \Add2_out1_1[13]_i_4__1_n_0\,
      S(0) => \Add2_out1_1[13]_i_5__1_n_0\
    );
\Add2_out1_1_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => Add2_out1(1),
      Q => Add2_out1_1(1),
      R => RSTP
    );
\Add2_out1_1_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => Add2_out1(2),
      Q => Add2_out1_1(2),
      R => RSTP
    );
\Add2_out1_1_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => Add2_out1(3),
      Q => Add2_out1_1(3),
      R => RSTP
    );
\Add2_out1_1_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => Add2_out1(4),
      Q => Add2_out1_1(4),
      R => RSTP
    );
\Add2_out1_1_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => Add2_out1(5),
      Q => Add2_out1_1(5),
      R => RSTP
    );
\Add2_out1_1_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => Add2_out1(6),
      Q => Add2_out1_1(6),
      R => RSTP
    );
\Add2_out1_1_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => Add2_out1(7),
      Q => Add2_out1_1(7),
      R => RSTP
    );
\Add2_out1_1_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => Add2_out1(8),
      Q => Add2_out1_1(8),
      R => RSTP
    );
\Add2_out1_1_reg[8]_i_1__1\: unisim.vcomponents.CARRY8
     port map (
      CI => \Add2_out1_1[8]_i_2__1_n_0\,
      CI_TOP => '0',
      CO(7) => \Add2_out1_1_reg[8]_i_1__1_n_0\,
      CO(6) => \Add2_out1_1_reg[8]_i_1__1_n_1\,
      CO(5) => \Add2_out1_1_reg[8]_i_1__1_n_2\,
      CO(4) => \Add2_out1_1_reg[8]_i_1__1_n_3\,
      CO(3) => \Add2_out1_1_reg[8]_i_1__1_n_4\,
      CO(2) => \Add2_out1_1_reg[8]_i_1__1_n_5\,
      CO(1) => \Add2_out1_1_reg[8]_i_1__1_n_6\,
      CO(0) => \Add2_out1_1_reg[8]_i_1__1_n_7\,
      DI(7 downto 0) => B"00000000",
      O(7 downto 0) => Add2_out1(8 downto 1),
      S(7) => \Add2_out1_1[8]_i_3__1_n_0\,
      S(6) => \Add2_out1_1[8]_i_4__1_n_0\,
      S(5) => \Add2_out1_1[8]_i_5__1_n_0\,
      S(4) => \Add2_out1_1[8]_i_6__1_n_0\,
      S(3) => \Add2_out1_1[8]_i_7__1_n_0\,
      S(2) => \Add2_out1_1[8]_i_8__1_n_0\,
      S(1) => \Add2_out1_1[8]_i_9__1_n_0\,
      S(0) => \Add2_out1_1[8]_i_10__1_n_0\
    );
\Add2_out1_1_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => Add2_out1(9),
      Q => Add2_out1_1(9),
      R => RSTP
    );
Counter_Ctrl_out5_1_i_2: unisim.vcomponents.LUT4
    generic map(
      INIT => X"080A"
    )
        port map (
      I0 => HDL_Counter2_count_reg_13_sn_1,
      I1 => HDL_Counter2_count_reg(16),
      I2 => HDL_Counter2_count_reg(17),
      I3 => HDL_Counter2_count_reg(15),
      O => HDL_Counter2_count_reg_16_sn_1
    );
Counter_Ctrl_out5_1_i_3: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0000000200000000"
    )
        port map (
      I0 => HDL_Counter2_count_reg_10_sn_1,
      I1 => HDL_Counter2_count_reg(1),
      I2 => HDL_Counter2_count_reg(0),
      I3 => HDL_Counter2_count_reg(4),
      I4 => HDL_Counter2_count_reg(2),
      I5 => HDL_Counter2_count_reg_7_sn_1,
      O => HDL_Counter2_count_reg_1_sn_1
    );
Counter_Ctrl_out5_1_i_5: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0000230000002323"
    )
        port map (
      I0 => HDL_Counter2_count_reg(13),
      I1 => HDL_Counter2_count_reg(14),
      I2 => HDL_Counter2_count_reg(12),
      I3 => HDL_Counter2_count_reg(10),
      I4 => HDL_Counter2_count_reg(11),
      I5 => HDL_Counter2_count_reg(9),
      O => HDL_Counter2_count_reg_13_sn_1
    );
Counter_Ctrl_out5_1_i_6: unisim.vcomponents.LUT4
    generic map(
      INIT => X"0001"
    )
        port map (
      I0 => HDL_Counter2_count_reg(10),
      I1 => HDL_Counter2_count_reg(8),
      I2 => HDL_Counter2_count_reg(7),
      I3 => HDL_Counter2_count_reg(5),
      O => HDL_Counter2_count_reg_10_sn_1
    );
Counter_Ctrl_out5_1_i_7: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0000230000002323"
    )
        port map (
      I0 => HDL_Counter2_count_reg(7),
      I1 => HDL_Counter2_count_reg(8),
      I2 => HDL_Counter2_count_reg(6),
      I3 => HDL_Counter2_count_reg(4),
      I4 => HDL_Counter2_count_reg(5),
      I5 => HDL_Counter2_count_reg(3),
      O => HDL_Counter2_count_reg_7_sn_1
    );
\Delay2_out1[11]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AAAAFFBFAAAA0080"
    )
        port map (
      I0 => \Delay2_out1_reg[13]_0\(11),
      I1 => \Delay2_out1_reg[13]_1\,
      I2 => D(0),
      I3 => HDL_Counter2_count_reg(19),
      I4 => \Delay2_out1_reg[13]_2\(0),
      I5 => \Delay2_out1_reg[13]\(11),
      O => \^delaymatch5_reg_reg[1][11]\
    );
\Delay2_out1[13]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AAAAFFBFAAAA0080"
    )
        port map (
      I0 => \Delay2_out1_reg[13]_0\(13),
      I1 => \Delay2_out1_reg[13]_1\,
      I2 => D(0),
      I3 => HDL_Counter2_count_reg(19),
      I4 => \Delay2_out1_reg[13]_2\(0),
      I5 => \Delay2_out1_reg[13]\(13),
      O => \^delaymatch5_reg_reg[1][13]\
    );
\Delay2_out1[1]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AAAAFFBFAAAA0080"
    )
        port map (
      I0 => \Delay2_out1_reg[13]_0\(1),
      I1 => \Delay2_out1_reg[13]_1\,
      I2 => D(0),
      I3 => HDL_Counter2_count_reg(19),
      I4 => \Delay2_out1_reg[13]_2\(0),
      I5 => \Delay2_out1_reg[13]\(1),
      O => \^delaymatch5_reg_reg[1][1]\
    );
\Delay2_out1[3]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AAAAFFBFAAAA0080"
    )
        port map (
      I0 => \Delay2_out1_reg[13]_0\(3),
      I1 => \Delay2_out1_reg[13]_1\,
      I2 => D(0),
      I3 => HDL_Counter2_count_reg(19),
      I4 => \Delay2_out1_reg[13]_2\(0),
      I5 => \Delay2_out1_reg[13]\(3),
      O => \^delaymatch5_reg_reg[1][3]\
    );
\Delay2_out1[5]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AAAAFFBFAAAA0080"
    )
        port map (
      I0 => \Delay2_out1_reg[13]_0\(5),
      I1 => \Delay2_out1_reg[13]_1\,
      I2 => D(0),
      I3 => HDL_Counter2_count_reg(19),
      I4 => \Delay2_out1_reg[13]_2\(0),
      I5 => \Delay2_out1_reg[13]\(5),
      O => \^delaymatch5_reg_reg[1][5]\
    );
\Delay2_out1[7]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AAAAFFBFAAAA0080"
    )
        port map (
      I0 => \Delay2_out1_reg[13]_0\(7),
      I1 => \Delay2_out1_reg[13]_1\,
      I2 => D(0),
      I3 => HDL_Counter2_count_reg(19),
      I4 => \Delay2_out1_reg[13]_2\(0),
      I5 => \Delay2_out1_reg[13]\(7),
      O => \^delaymatch5_reg_reg[1][7]\
    );
\Delay2_out1[9]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AAAAFFBFAAAA0080"
    )
        port map (
      I0 => \Delay2_out1_reg[13]_0\(9),
      I1 => \Delay2_out1_reg[13]_1\,
      I2 => D(0),
      I3 => HDL_Counter2_count_reg(19),
      I4 => \Delay2_out1_reg[13]_2\(0),
      I5 => \Delay2_out1_reg[13]\(9),
      O => \^delaymatch5_reg_reg[1][9]\
    );
Logical_Operator1_out10_carry: unisim.vcomponents.CARRY8
     port map (
      CI => '0',
      CI_TOP => '0',
      CO(7) => NLW_Logical_Operator1_out10_carry_CO_UNCONNECTED(7),
      CO(6) => Relational_Operator_relop1,
      CO(5) => Logical_Operator1_out10_carry_n_2,
      CO(4) => Logical_Operator1_out10_carry_n_3,
      CO(3) => Logical_Operator1_out10_carry_n_4,
      CO(2) => Logical_Operator1_out10_carry_n_5,
      CO(1) => Logical_Operator1_out10_carry_n_6,
      CO(0) => Logical_Operator1_out10_carry_n_7,
      DI(7) => '0',
      DI(6) => Logical_Operator1_out10_carry_i_1_n_0,
      DI(5) => Logical_Operator1_out10_carry_i_2_n_0,
      DI(4) => Logical_Operator1_out10_carry_i_3_n_0,
      DI(3) => Logical_Operator1_out10_carry_i_4_n_0,
      DI(2) => Logical_Operator1_out10_carry_i_5_n_0,
      DI(1) => Logical_Operator1_out10_carry_i_6_n_0,
      DI(0) => Logical_Operator1_out10_carry_i_7_n_0,
      O(7 downto 0) => NLW_Logical_Operator1_out10_carry_O_UNCONNECTED(7 downto 0),
      S(7) => '0',
      S(6) => Logical_Operator1_out10_carry_i_8_n_0,
      S(5) => Logical_Operator1_out10_carry_i_9_n_0,
      S(4) => Logical_Operator1_out10_carry_i_10_n_0,
      S(3) => Logical_Operator1_out10_carry_i_11_n_0,
      S(2) => Logical_Operator1_out10_carry_i_12_n_0,
      S(1) => Logical_Operator1_out10_carry_i_13_n_0,
      S(0) => Logical_Operator1_out10_carry_i_14_n_0
    );
Logical_Operator1_out10_carry_i_1: unisim.vcomponents.LUT6
    generic map(
      INIT => X"22222222BBB222B2"
    )
        port map (
      I0 => minus_out1_1(13),
      I1 => \^delaymatch5_reg_reg[1][13]\,
      I2 => \Delay2_out1_reg[13]\(12),
      I3 => \^pwm_en_axi_2_reg\,
      I4 => \Delay2_out1_reg[13]_0\(12),
      I5 => minus_out1_1(12),
      O => Logical_Operator1_out10_carry_i_1_n_0
    );
Logical_Operator1_out10_carry_i_10: unisim.vcomponents.LUT6
    generic map(
      INIT => X"A95900000000A959"
    )
        port map (
      I0 => minus_out1_1(8),
      I1 => \Delay2_out1_reg[13]\(8),
      I2 => \^pwm_en_axi_2_reg\,
      I3 => \Delay2_out1_reg[13]_0\(8),
      I4 => \^delaymatch5_reg_reg[1][9]\,
      I5 => minus_out1_1(9),
      O => Logical_Operator1_out10_carry_i_10_n_0
    );
Logical_Operator1_out10_carry_i_11: unisim.vcomponents.LUT6
    generic map(
      INIT => X"A95900000000A959"
    )
        port map (
      I0 => minus_out1_1(6),
      I1 => \Delay2_out1_reg[13]\(6),
      I2 => \^pwm_en_axi_2_reg\,
      I3 => \Delay2_out1_reg[13]_0\(6),
      I4 => \^delaymatch5_reg_reg[1][7]\,
      I5 => minus_out1_1(7),
      O => Logical_Operator1_out10_carry_i_11_n_0
    );
Logical_Operator1_out10_carry_i_12: unisim.vcomponents.LUT6
    generic map(
      INIT => X"A95900000000A959"
    )
        port map (
      I0 => minus_out1_1(4),
      I1 => \Delay2_out1_reg[13]\(4),
      I2 => \^pwm_en_axi_2_reg\,
      I3 => \Delay2_out1_reg[13]_0\(4),
      I4 => \^delaymatch5_reg_reg[1][5]\,
      I5 => minus_out1_1(5),
      O => Logical_Operator1_out10_carry_i_12_n_0
    );
Logical_Operator1_out10_carry_i_13: unisim.vcomponents.LUT6
    generic map(
      INIT => X"A95900000000A959"
    )
        port map (
      I0 => minus_out1_1(2),
      I1 => \Delay2_out1_reg[13]\(2),
      I2 => \^pwm_en_axi_2_reg\,
      I3 => \Delay2_out1_reg[13]_0\(2),
      I4 => \^delaymatch5_reg_reg[1][3]\,
      I5 => minus_out1_1(3),
      O => Logical_Operator1_out10_carry_i_13_n_0
    );
Logical_Operator1_out10_carry_i_14: unisim.vcomponents.LUT6
    generic map(
      INIT => X"E21D00000000E21D"
    )
        port map (
      I0 => \Delay2_out1_reg[13]\(0),
      I1 => \^pwm_en_axi_2_reg\,
      I2 => \Delay2_out1_reg[13]_0\(0),
      I3 => Add1_out1_1(0),
      I4 => \^delaymatch5_reg_reg[1][1]\,
      I5 => minus_out1_1(1),
      O => Logical_Operator1_out10_carry_i_14_n_0
    );
Logical_Operator1_out10_carry_i_2: unisim.vcomponents.LUT6
    generic map(
      INIT => X"22222222BBB222B2"
    )
        port map (
      I0 => \^delaymatch5_reg_reg[1][11]\,
      I1 => minus_out1_1(11),
      I2 => \Delay2_out1_reg[13]\(10),
      I3 => \^pwm_en_axi_2_reg\,
      I4 => \Delay2_out1_reg[13]_0\(10),
      I5 => minus_out1_1(10),
      O => Logical_Operator1_out10_carry_i_2_n_0
    );
Logical_Operator1_out10_carry_i_3: unisim.vcomponents.LUT6
    generic map(
      INIT => X"22222222BBB222B2"
    )
        port map (
      I0 => \^delaymatch5_reg_reg[1][9]\,
      I1 => minus_out1_1(9),
      I2 => \Delay2_out1_reg[13]\(8),
      I3 => \^pwm_en_axi_2_reg\,
      I4 => \Delay2_out1_reg[13]_0\(8),
      I5 => minus_out1_1(8),
      O => Logical_Operator1_out10_carry_i_3_n_0
    );
Logical_Operator1_out10_carry_i_4: unisim.vcomponents.LUT6
    generic map(
      INIT => X"22222222BBB222B2"
    )
        port map (
      I0 => \^delaymatch5_reg_reg[1][7]\,
      I1 => minus_out1_1(7),
      I2 => \Delay2_out1_reg[13]\(6),
      I3 => \^pwm_en_axi_2_reg\,
      I4 => \Delay2_out1_reg[13]_0\(6),
      I5 => minus_out1_1(6),
      O => Logical_Operator1_out10_carry_i_4_n_0
    );
Logical_Operator1_out10_carry_i_5: unisim.vcomponents.LUT6
    generic map(
      INIT => X"22222222BBB222B2"
    )
        port map (
      I0 => \^delaymatch5_reg_reg[1][5]\,
      I1 => minus_out1_1(5),
      I2 => \Delay2_out1_reg[13]\(4),
      I3 => \^pwm_en_axi_2_reg\,
      I4 => \Delay2_out1_reg[13]_0\(4),
      I5 => minus_out1_1(4),
      O => Logical_Operator1_out10_carry_i_5_n_0
    );
Logical_Operator1_out10_carry_i_6: unisim.vcomponents.LUT6
    generic map(
      INIT => X"22222222BBB222B2"
    )
        port map (
      I0 => \^delaymatch5_reg_reg[1][3]\,
      I1 => minus_out1_1(3),
      I2 => \Delay2_out1_reg[13]\(2),
      I3 => \^pwm_en_axi_2_reg\,
      I4 => \Delay2_out1_reg[13]_0\(2),
      I5 => minus_out1_1(2),
      O => Logical_Operator1_out10_carry_i_6_n_0
    );
Logical_Operator1_out10_carry_i_7: unisim.vcomponents.LUT6
    generic map(
      INIT => X"7577755510111000"
    )
        port map (
      I0 => minus_out1_1(1),
      I1 => Add1_out1_1(0),
      I2 => \Delay2_out1_reg[13]_0\(0),
      I3 => \^pwm_en_axi_2_reg\,
      I4 => \Delay2_out1_reg[13]\(0),
      I5 => \^delaymatch5_reg_reg[1][1]\,
      O => Logical_Operator1_out10_carry_i_7_n_0
    );
Logical_Operator1_out10_carry_i_8: unisim.vcomponents.LUT6
    generic map(
      INIT => X"A95900000000A959"
    )
        port map (
      I0 => minus_out1_1(12),
      I1 => \Delay2_out1_reg[13]\(12),
      I2 => \^pwm_en_axi_2_reg\,
      I3 => \Delay2_out1_reg[13]_0\(12),
      I4 => \^delaymatch5_reg_reg[1][13]\,
      I5 => minus_out1_1(13),
      O => Logical_Operator1_out10_carry_i_8_n_0
    );
Logical_Operator1_out10_carry_i_9: unisim.vcomponents.LUT6
    generic map(
      INIT => X"A95900000000A959"
    )
        port map (
      I0 => minus_out1_1(10),
      I1 => \Delay2_out1_reg[13]\(10),
      I2 => \^pwm_en_axi_2_reg\,
      I3 => \Delay2_out1_reg[13]_0\(10),
      I4 => \^delaymatch5_reg_reg[1][11]\,
      I5 => minus_out1_1(11),
      O => Logical_Operator1_out10_carry_i_9_n_0
    );
\Logical_Operator1_out10_inferred__0/i__carry\: unisim.vcomponents.CARRY8
     port map (
      CI => '0',
      CI_TOP => '0',
      CO(7) => \NLW_Logical_Operator1_out10_inferred__0/i__carry_CO_UNCONNECTED\(7),
      CO(6) => Relational_Operator1_relop1,
      CO(5) => \Logical_Operator1_out10_inferred__0/i__carry_n_2\,
      CO(4) => \Logical_Operator1_out10_inferred__0/i__carry_n_3\,
      CO(3) => \Logical_Operator1_out10_inferred__0/i__carry_n_4\,
      CO(2) => \Logical_Operator1_out10_inferred__0/i__carry_n_5\,
      CO(1) => \Logical_Operator1_out10_inferred__0/i__carry_n_6\,
      CO(0) => \Logical_Operator1_out10_inferred__0/i__carry_n_7\,
      DI(7) => '0',
      DI(6) => \i__carry_i_1_n_0\,
      DI(5) => \i__carry_i_2_n_0\,
      DI(4) => \i__carry_i_3_n_0\,
      DI(3) => \i__carry_i_4_n_0\,
      DI(2) => \i__carry_i_5_n_0\,
      DI(1) => \i__carry_i_6_n_0\,
      DI(0) => \i__carry_i_7_n_0\,
      O(7 downto 0) => \NLW_Logical_Operator1_out10_inferred__0/i__carry_O_UNCONNECTED\(7 downto 0),
      S(7) => '0',
      S(6) => \i__carry_i_8_n_0\,
      S(5) => \i__carry_i_9_n_0\,
      S(4) => \i__carry_i_10__1_n_0\,
      S(3) => \i__carry_i_11__1_n_0\,
      S(2) => \i__carry_i_12__1_n_0\,
      S(1) => \i__carry_i_13__1_n_0\,
      S(0) => \i__carry_i_14__1_n_0\
    );
Logical_Operator_out10_carry: unisim.vcomponents.CARRY8
     port map (
      CI => '0',
      CI_TOP => '0',
      CO(7) => NLW_Logical_Operator_out10_carry_CO_UNCONNECTED(7),
      CO(6) => Relational_Operator3_relop1,
      CO(5) => Logical_Operator_out10_carry_n_2,
      CO(4) => Logical_Operator_out10_carry_n_3,
      CO(3) => Logical_Operator_out10_carry_n_4,
      CO(2) => Logical_Operator_out10_carry_n_5,
      CO(1) => Logical_Operator_out10_carry_n_6,
      CO(0) => Logical_Operator_out10_carry_n_7,
      DI(7) => '0',
      DI(6) => Logical_Operator_out10_carry_i_1_n_0,
      DI(5) => Logical_Operator_out10_carry_i_2_n_0,
      DI(4) => Logical_Operator_out10_carry_i_3_n_0,
      DI(3) => Logical_Operator_out10_carry_i_4_n_0,
      DI(2) => Logical_Operator_out10_carry_i_5_n_0,
      DI(1) => Logical_Operator_out10_carry_i_6_n_0,
      DI(0) => Logical_Operator_out10_carry_i_7_n_0,
      O(7 downto 0) => NLW_Logical_Operator_out10_carry_O_UNCONNECTED(7 downto 0),
      S(7) => '0',
      S(6) => Logical_Operator_out10_carry_i_8_n_0,
      S(5) => Logical_Operator_out10_carry_i_9_n_0,
      S(4) => Logical_Operator_out10_carry_i_10_n_0,
      S(3) => Logical_Operator_out10_carry_i_11_n_0,
      S(2) => Logical_Operator_out10_carry_i_12_n_0,
      S(1) => Logical_Operator_out10_carry_i_13_n_0,
      S(0) => Logical_Operator_out10_carry_i_14_n_0
    );
Logical_Operator_out10_carry_i_1: unisim.vcomponents.LUT6
    generic map(
      INIT => X"22222222BBB222B2"
    )
        port map (
      I0 => Add2_out1_1(13),
      I1 => \^delaymatch5_reg_reg[1][13]\,
      I2 => \Delay2_out1_reg[13]\(12),
      I3 => \^pwm_en_axi_2_reg\,
      I4 => \Delay2_out1_reg[13]_0\(12),
      I5 => Add2_out1_1(12),
      O => Logical_Operator_out10_carry_i_1_n_0
    );
Logical_Operator_out10_carry_i_10: unisim.vcomponents.LUT6
    generic map(
      INIT => X"A95900000000A959"
    )
        port map (
      I0 => Add2_out1_1(8),
      I1 => \Delay2_out1_reg[13]\(8),
      I2 => \^pwm_en_axi_2_reg\,
      I3 => \Delay2_out1_reg[13]_0\(8),
      I4 => \^delaymatch5_reg_reg[1][9]\,
      I5 => Add2_out1_1(9),
      O => Logical_Operator_out10_carry_i_10_n_0
    );
Logical_Operator_out10_carry_i_11: unisim.vcomponents.LUT6
    generic map(
      INIT => X"A95900000000A959"
    )
        port map (
      I0 => Add2_out1_1(6),
      I1 => \Delay2_out1_reg[13]\(6),
      I2 => \^pwm_en_axi_2_reg\,
      I3 => \Delay2_out1_reg[13]_0\(6),
      I4 => \^delaymatch5_reg_reg[1][7]\,
      I5 => Add2_out1_1(7),
      O => Logical_Operator_out10_carry_i_11_n_0
    );
Logical_Operator_out10_carry_i_12: unisim.vcomponents.LUT6
    generic map(
      INIT => X"A95900000000A959"
    )
        port map (
      I0 => Add2_out1_1(4),
      I1 => \Delay2_out1_reg[13]\(4),
      I2 => \^pwm_en_axi_2_reg\,
      I3 => \Delay2_out1_reg[13]_0\(4),
      I4 => \^delaymatch5_reg_reg[1][5]\,
      I5 => Add2_out1_1(5),
      O => Logical_Operator_out10_carry_i_12_n_0
    );
Logical_Operator_out10_carry_i_13: unisim.vcomponents.LUT6
    generic map(
      INIT => X"A95900000000A959"
    )
        port map (
      I0 => Add2_out1_1(2),
      I1 => \Delay2_out1_reg[13]\(2),
      I2 => \^pwm_en_axi_2_reg\,
      I3 => \Delay2_out1_reg[13]_0\(2),
      I4 => \^delaymatch5_reg_reg[1][3]\,
      I5 => Add2_out1_1(3),
      O => Logical_Operator_out10_carry_i_13_n_0
    );
Logical_Operator_out10_carry_i_14: unisim.vcomponents.LUT6
    generic map(
      INIT => X"E21D00000000E21D"
    )
        port map (
      I0 => \Delay2_out1_reg[13]\(0),
      I1 => \^pwm_en_axi_2_reg\,
      I2 => \Delay2_out1_reg[13]_0\(0),
      I3 => Add1_out1_1(0),
      I4 => \^delaymatch5_reg_reg[1][1]\,
      I5 => Add2_out1_1(1),
      O => Logical_Operator_out10_carry_i_14_n_0
    );
Logical_Operator_out10_carry_i_2: unisim.vcomponents.LUT6
    generic map(
      INIT => X"22222222BBB222B2"
    )
        port map (
      I0 => \^delaymatch5_reg_reg[1][11]\,
      I1 => Add2_out1_1(11),
      I2 => \Delay2_out1_reg[13]\(10),
      I3 => \^pwm_en_axi_2_reg\,
      I4 => \Delay2_out1_reg[13]_0\(10),
      I5 => Add2_out1_1(10),
      O => Logical_Operator_out10_carry_i_2_n_0
    );
Logical_Operator_out10_carry_i_3: unisim.vcomponents.LUT6
    generic map(
      INIT => X"22222222BBB222B2"
    )
        port map (
      I0 => \^delaymatch5_reg_reg[1][9]\,
      I1 => Add2_out1_1(9),
      I2 => \Delay2_out1_reg[13]\(8),
      I3 => \^pwm_en_axi_2_reg\,
      I4 => \Delay2_out1_reg[13]_0\(8),
      I5 => Add2_out1_1(8),
      O => Logical_Operator_out10_carry_i_3_n_0
    );
Logical_Operator_out10_carry_i_4: unisim.vcomponents.LUT6
    generic map(
      INIT => X"22222222BBB222B2"
    )
        port map (
      I0 => \^delaymatch5_reg_reg[1][7]\,
      I1 => Add2_out1_1(7),
      I2 => \Delay2_out1_reg[13]\(6),
      I3 => \^pwm_en_axi_2_reg\,
      I4 => \Delay2_out1_reg[13]_0\(6),
      I5 => Add2_out1_1(6),
      O => Logical_Operator_out10_carry_i_4_n_0
    );
Logical_Operator_out10_carry_i_5: unisim.vcomponents.LUT6
    generic map(
      INIT => X"22222222BBB222B2"
    )
        port map (
      I0 => \^delaymatch5_reg_reg[1][5]\,
      I1 => Add2_out1_1(5),
      I2 => \Delay2_out1_reg[13]\(4),
      I3 => \^pwm_en_axi_2_reg\,
      I4 => \Delay2_out1_reg[13]_0\(4),
      I5 => Add2_out1_1(4),
      O => Logical_Operator_out10_carry_i_5_n_0
    );
Logical_Operator_out10_carry_i_6: unisim.vcomponents.LUT6
    generic map(
      INIT => X"22222222BBB222B2"
    )
        port map (
      I0 => \^delaymatch5_reg_reg[1][3]\,
      I1 => Add2_out1_1(3),
      I2 => \Delay2_out1_reg[13]\(2),
      I3 => \^pwm_en_axi_2_reg\,
      I4 => \Delay2_out1_reg[13]_0\(2),
      I5 => Add2_out1_1(2),
      O => Logical_Operator_out10_carry_i_6_n_0
    );
Logical_Operator_out10_carry_i_7: unisim.vcomponents.LUT6
    generic map(
      INIT => X"7577755510111000"
    )
        port map (
      I0 => Add2_out1_1(1),
      I1 => Add1_out1_1(0),
      I2 => \Delay2_out1_reg[13]_0\(0),
      I3 => \^pwm_en_axi_2_reg\,
      I4 => \Delay2_out1_reg[13]\(0),
      I5 => \^delaymatch5_reg_reg[1][1]\,
      O => Logical_Operator_out10_carry_i_7_n_0
    );
Logical_Operator_out10_carry_i_8: unisim.vcomponents.LUT6
    generic map(
      INIT => X"A95900000000A959"
    )
        port map (
      I0 => Add2_out1_1(12),
      I1 => \Delay2_out1_reg[13]\(12),
      I2 => \^pwm_en_axi_2_reg\,
      I3 => \Delay2_out1_reg[13]_0\(12),
      I4 => \^delaymatch5_reg_reg[1][13]\,
      I5 => Add2_out1_1(13),
      O => Logical_Operator_out10_carry_i_8_n_0
    );
Logical_Operator_out10_carry_i_9: unisim.vcomponents.LUT6
    generic map(
      INIT => X"A95900000000A959"
    )
        port map (
      I0 => Add2_out1_1(10),
      I1 => \Delay2_out1_reg[13]\(10),
      I2 => \^pwm_en_axi_2_reg\,
      I3 => \Delay2_out1_reg[13]_0\(10),
      I4 => \^delaymatch5_reg_reg[1][11]\,
      I5 => Add2_out1_1(11),
      O => Logical_Operator_out10_carry_i_9_n_0
    );
Logical_Operator_out11_carry: unisim.vcomponents.CARRY8
     port map (
      CI => '0',
      CI_TOP => '0',
      CO(7) => NLW_Logical_Operator_out11_carry_CO_UNCONNECTED(7),
      CO(6) => Relational_Operator2_relop1,
      CO(5) => Logical_Operator_out11_carry_n_2,
      CO(4) => Logical_Operator_out11_carry_n_3,
      CO(3) => Logical_Operator_out11_carry_n_4,
      CO(2) => Logical_Operator_out11_carry_n_5,
      CO(1) => Logical_Operator_out11_carry_n_6,
      CO(0) => Logical_Operator_out11_carry_n_7,
      DI(7) => '0',
      DI(6) => Logical_Operator_out11_carry_i_1_n_0,
      DI(5) => Logical_Operator_out11_carry_i_2_n_0,
      DI(4) => \i__carry_i_3_n_0\,
      DI(3) => \i__carry_i_4_n_0\,
      DI(2) => \i__carry_i_5_n_0\,
      DI(1) => \i__carry_i_6_n_0\,
      DI(0) => \i__carry_i_7_n_0\,
      O(7 downto 0) => NLW_Logical_Operator_out11_carry_O_UNCONNECTED(7 downto 0),
      S(7) => '0',
      S(6) => Logical_Operator_out11_carry_i_3_n_0,
      S(5) => Logical_Operator_out11_carry_i_4_n_0,
      S(4) => Logical_Operator_out11_carry_i_5_n_0,
      S(3) => Logical_Operator_out11_carry_i_6_n_0,
      S(2) => Logical_Operator_out11_carry_i_7_n_0,
      S(1) => Logical_Operator_out11_carry_i_8_n_0,
      S(0) => Logical_Operator_out11_carry_i_9_n_0
    );
Logical_Operator_out11_carry_i_1: unisim.vcomponents.LUT6
    generic map(
      INIT => X"222222B2B2B222B2"
    )
        port map (
      I0 => \^delaymatch5_reg_reg[1][13]\,
      I1 => Add1_out1_1(13),
      I2 => Add1_out1_1(12),
      I3 => \Delay2_out1_reg[13]\(12),
      I4 => \^pwm_en_axi_2_reg\,
      I5 => \Delay2_out1_reg[13]_0\(12),
      O => Logical_Operator_out11_carry_i_1_n_0
    );
Logical_Operator_out11_carry_i_2: unisim.vcomponents.LUT6
    generic map(
      INIT => X"222222B2B2B222B2"
    )
        port map (
      I0 => Add1_out1_1(11),
      I1 => \^delaymatch5_reg_reg[1][11]\,
      I2 => Add1_out1_1(10),
      I3 => \Delay2_out1_reg[13]\(10),
      I4 => \^pwm_en_axi_2_reg\,
      I5 => \Delay2_out1_reg[13]_0\(10),
      O => Logical_Operator_out11_carry_i_2_n_0
    );
Logical_Operator_out11_carry_i_3: unisim.vcomponents.LUT6
    generic map(
      INIT => X"A95900000000A959"
    )
        port map (
      I0 => Add1_out1_1(12),
      I1 => \Delay2_out1_reg[13]\(12),
      I2 => \^pwm_en_axi_2_reg\,
      I3 => \Delay2_out1_reg[13]_0\(12),
      I4 => \^delaymatch5_reg_reg[1][13]\,
      I5 => Add1_out1_1(13),
      O => Logical_Operator_out11_carry_i_3_n_0
    );
Logical_Operator_out11_carry_i_4: unisim.vcomponents.LUT6
    generic map(
      INIT => X"A95900000000A959"
    )
        port map (
      I0 => Add1_out1_1(10),
      I1 => \Delay2_out1_reg[13]\(10),
      I2 => \^pwm_en_axi_2_reg\,
      I3 => \Delay2_out1_reg[13]_0\(10),
      I4 => \^delaymatch5_reg_reg[1][11]\,
      I5 => Add1_out1_1(11),
      O => Logical_Operator_out11_carry_i_4_n_0
    );
Logical_Operator_out11_carry_i_5: unisim.vcomponents.LUT6
    generic map(
      INIT => X"A95900000000A959"
    )
        port map (
      I0 => Add1_out1_1(8),
      I1 => \Delay2_out1_reg[13]\(8),
      I2 => \^pwm_en_axi_2_reg\,
      I3 => \Delay2_out1_reg[13]_0\(8),
      I4 => \^delaymatch5_reg_reg[1][9]\,
      I5 => Add1_out1_1(9),
      O => Logical_Operator_out11_carry_i_5_n_0
    );
Logical_Operator_out11_carry_i_6: unisim.vcomponents.LUT6
    generic map(
      INIT => X"A95900000000A959"
    )
        port map (
      I0 => Add1_out1_1(6),
      I1 => \Delay2_out1_reg[13]\(6),
      I2 => \^pwm_en_axi_2_reg\,
      I3 => \Delay2_out1_reg[13]_0\(6),
      I4 => \^delaymatch5_reg_reg[1][7]\,
      I5 => Add1_out1_1(7),
      O => Logical_Operator_out11_carry_i_6_n_0
    );
Logical_Operator_out11_carry_i_7: unisim.vcomponents.LUT6
    generic map(
      INIT => X"A95900000000A959"
    )
        port map (
      I0 => Add1_out1_1(4),
      I1 => \Delay2_out1_reg[13]\(4),
      I2 => \^pwm_en_axi_2_reg\,
      I3 => \Delay2_out1_reg[13]_0\(4),
      I4 => \^delaymatch5_reg_reg[1][5]\,
      I5 => Add1_out1_1(5),
      O => Logical_Operator_out11_carry_i_7_n_0
    );
Logical_Operator_out11_carry_i_8: unisim.vcomponents.LUT6
    generic map(
      INIT => X"A95900000000A959"
    )
        port map (
      I0 => Add1_out1_1(2),
      I1 => \Delay2_out1_reg[13]\(2),
      I2 => \^pwm_en_axi_2_reg\,
      I3 => \Delay2_out1_reg[13]_0\(2),
      I4 => \^delaymatch5_reg_reg[1][3]\,
      I5 => Add1_out1_1(3),
      O => Logical_Operator_out11_carry_i_8_n_0
    );
Logical_Operator_out11_carry_i_9: unisim.vcomponents.LUT6
    generic map(
      INIT => X"E21D00000000E21D"
    )
        port map (
      I0 => \Delay2_out1_reg[13]\(0),
      I1 => \^pwm_en_axi_2_reg\,
      I2 => \Delay2_out1_reg[13]_0\(0),
      I3 => Add1_out1_1(0),
      I4 => \^delaymatch5_reg_reg[1][1]\,
      I5 => Add1_out1_1(1),
      O => Logical_Operator_out11_carry_i_9_n_0
    );
Period_Center0_carry_i_1: unisim.vcomponents.LUT4
    generic map(
      INIT => X"9009"
    )
        port map (
      I0 => HDL_Counter2_count_reg(18),
      I1 => maximum_counter_value_1(18),
      I2 => HDL_Counter2_count_reg(19),
      I3 => maximum_counter_value_1(19),
      O => \HDL_Counter2_count_reg[18]\(6)
    );
Period_Center0_carry_i_2: unisim.vcomponents.LUT6
    generic map(
      INIT => X"9009000000009009"
    )
        port map (
      I0 => maximum_counter_value_1(17),
      I1 => HDL_Counter2_count_reg(17),
      I2 => maximum_counter_value_1(16),
      I3 => HDL_Counter2_count_reg(16),
      I4 => HDL_Counter2_count_reg(15),
      I5 => maximum_counter_value_1(15),
      O => \HDL_Counter2_count_reg[18]\(5)
    );
Period_Center0_carry_i_3: unisim.vcomponents.LUT6
    generic map(
      INIT => X"9009000000009009"
    )
        port map (
      I0 => maximum_counter_value_1(13),
      I1 => HDL_Counter2_count_reg(13),
      I2 => maximum_counter_value_1(14),
      I3 => HDL_Counter2_count_reg(14),
      I4 => HDL_Counter2_count_reg(12),
      I5 => maximum_counter_value_1(12),
      O => \HDL_Counter2_count_reg[18]\(4)
    );
Period_Center0_carry_i_4: unisim.vcomponents.LUT6
    generic map(
      INIT => X"9009000000009009"
    )
        port map (
      I0 => maximum_counter_value_1(11),
      I1 => HDL_Counter2_count_reg(11),
      I2 => maximum_counter_value_1(10),
      I3 => HDL_Counter2_count_reg(10),
      I4 => HDL_Counter2_count_reg(9),
      I5 => maximum_counter_value_1(9),
      O => \HDL_Counter2_count_reg[18]\(3)
    );
Period_Center0_carry_i_5: unisim.vcomponents.LUT6
    generic map(
      INIT => X"9009000000009009"
    )
        port map (
      I0 => maximum_counter_value_1(7),
      I1 => HDL_Counter2_count_reg(7),
      I2 => maximum_counter_value_1(8),
      I3 => HDL_Counter2_count_reg(8),
      I4 => HDL_Counter2_count_reg(6),
      I5 => maximum_counter_value_1(6),
      O => \HDL_Counter2_count_reg[18]\(2)
    );
Period_Center0_carry_i_6: unisim.vcomponents.LUT6
    generic map(
      INIT => X"9009000000009009"
    )
        port map (
      I0 => maximum_counter_value_1(5),
      I1 => HDL_Counter2_count_reg(5),
      I2 => maximum_counter_value_1(4),
      I3 => HDL_Counter2_count_reg(4),
      I4 => HDL_Counter2_count_reg(3),
      I5 => maximum_counter_value_1(3),
      O => \HDL_Counter2_count_reg[18]\(1)
    );
Period_Center0_carry_i_7: unisim.vcomponents.LUT6
    generic map(
      INIT => X"9009000000009009"
    )
        port map (
      I0 => maximum_counter_value_1(1),
      I1 => HDL_Counter2_count_reg(1),
      I2 => maximum_counter_value_1(2),
      I3 => HDL_Counter2_count_reg(2),
      I4 => HDL_Counter2_count_reg(0),
      I5 => maximum_counter_value_1(0),
      O => \HDL_Counter2_count_reg[18]\(0)
    );
\Saturation1_out1_1[11]_i_1__1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"02"
    )
        port map (
      I0 => Q(11),
      I1 => CO(0),
      I2 => Q(13),
      O => Saturation1_out1(11)
    );
\Saturation1_out1_1[12]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"BA"
    )
        port map (
      I0 => CO(0),
      I1 => Q(13),
      I2 => Q(12),
      O => Saturation1_out1(12)
    );
\Saturation1_out1_1_reg[11]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => Saturation1_out1(11),
      Q => Saturation1_out1_1(11),
      R => RSTP
    );
\Saturation1_out1_1_reg[12]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => Saturation1_out1(12),
      Q => Saturation1_out1_1(12),
      R => RSTP
    );
\i__carry_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"AAAEEEAE"
    )
        port map (
      I0 => \^delaymatch5_reg_reg[1][13]\,
      I1 => Saturation1_out1_1(12),
      I2 => \Delay2_out1_reg[13]\(12),
      I3 => \^pwm_en_axi_2_reg\,
      I4 => \Delay2_out1_reg[13]_0\(12),
      O => \i__carry_i_1_n_0\
    );
\i__carry_i_10__1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"A95900000000A959"
    )
        port map (
      I0 => Add1_out1_1(8),
      I1 => \Delay2_out1_reg[13]\(8),
      I2 => \^pwm_en_axi_2_reg\,
      I3 => \Delay2_out1_reg[13]_0\(8),
      I4 => \^delaymatch5_reg_reg[1][9]\,
      I5 => Add1_out1_1(9),
      O => \i__carry_i_10__1_n_0\
    );
\i__carry_i_11__1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"A95900000000A959"
    )
        port map (
      I0 => Add1_out1_1(6),
      I1 => \Delay2_out1_reg[13]\(6),
      I2 => \^pwm_en_axi_2_reg\,
      I3 => \Delay2_out1_reg[13]_0\(6),
      I4 => \^delaymatch5_reg_reg[1][7]\,
      I5 => Add1_out1_1(7),
      O => \i__carry_i_11__1_n_0\
    );
\i__carry_i_12__1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"A95900000000A959"
    )
        port map (
      I0 => Add1_out1_1(4),
      I1 => \Delay2_out1_reg[13]\(4),
      I2 => \^pwm_en_axi_2_reg\,
      I3 => \Delay2_out1_reg[13]_0\(4),
      I4 => \^delaymatch5_reg_reg[1][5]\,
      I5 => Add1_out1_1(5),
      O => \i__carry_i_12__1_n_0\
    );
\i__carry_i_13__1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"A95900000000A959"
    )
        port map (
      I0 => Add1_out1_1(2),
      I1 => \Delay2_out1_reg[13]\(2),
      I2 => \^pwm_en_axi_2_reg\,
      I3 => \Delay2_out1_reg[13]_0\(2),
      I4 => \^delaymatch5_reg_reg[1][3]\,
      I5 => Add1_out1_1(3),
      O => \i__carry_i_13__1_n_0\
    );
\i__carry_i_14__1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"E21D00000000E21D"
    )
        port map (
      I0 => \Delay2_out1_reg[13]\(0),
      I1 => \^pwm_en_axi_2_reg\,
      I2 => \Delay2_out1_reg[13]_0\(0),
      I3 => Add1_out1_1(0),
      I4 => \^delaymatch5_reg_reg[1][1]\,
      I5 => Add1_out1_1(1),
      O => \i__carry_i_14__1_n_0\
    );
\i__carry_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"222222B2B2B222B2"
    )
        port map (
      I0 => Saturation1_out1_1(11),
      I1 => \^delaymatch5_reg_reg[1][11]\,
      I2 => Add1_out1_1(10),
      I3 => \Delay2_out1_reg[13]\(10),
      I4 => \^pwm_en_axi_2_reg\,
      I5 => \Delay2_out1_reg[13]_0\(10),
      O => \i__carry_i_2_n_0\
    );
\i__carry_i_3\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"222222B2B2B222B2"
    )
        port map (
      I0 => Add1_out1_1(9),
      I1 => \^delaymatch5_reg_reg[1][9]\,
      I2 => Add1_out1_1(8),
      I3 => \Delay2_out1_reg[13]\(8),
      I4 => \^pwm_en_axi_2_reg\,
      I5 => \Delay2_out1_reg[13]_0\(8),
      O => \i__carry_i_3_n_0\
    );
\i__carry_i_4\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"222222B2B2B222B2"
    )
        port map (
      I0 => Add1_out1_1(7),
      I1 => \^delaymatch5_reg_reg[1][7]\,
      I2 => Add1_out1_1(6),
      I3 => \Delay2_out1_reg[13]\(6),
      I4 => \^pwm_en_axi_2_reg\,
      I5 => \Delay2_out1_reg[13]_0\(6),
      O => \i__carry_i_4_n_0\
    );
\i__carry_i_5\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"222222B2B2B222B2"
    )
        port map (
      I0 => Add1_out1_1(5),
      I1 => \^delaymatch5_reg_reg[1][5]\,
      I2 => Add1_out1_1(4),
      I3 => \Delay2_out1_reg[13]\(4),
      I4 => \^pwm_en_axi_2_reg\,
      I5 => \Delay2_out1_reg[13]_0\(4),
      O => \i__carry_i_5_n_0\
    );
\i__carry_i_6\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"222222B2B2B222B2"
    )
        port map (
      I0 => Add1_out1_1(3),
      I1 => \^delaymatch5_reg_reg[1][3]\,
      I2 => Add1_out1_1(2),
      I3 => \Delay2_out1_reg[13]\(2),
      I4 => \^pwm_en_axi_2_reg\,
      I5 => \Delay2_out1_reg[13]_0\(2),
      O => \i__carry_i_6_n_0\
    );
\i__carry_i_7\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"222222B2B2B222B2"
    )
        port map (
      I0 => Add1_out1_1(1),
      I1 => \^delaymatch5_reg_reg[1][1]\,
      I2 => Add1_out1_1(0),
      I3 => \Delay2_out1_reg[13]\(0),
      I4 => \^pwm_en_axi_2_reg\,
      I5 => \Delay2_out1_reg[13]_0\(0),
      O => \i__carry_i_7_n_0\
    );
\i__carry_i_8\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"0000A959"
    )
        port map (
      I0 => Saturation1_out1_1(12),
      I1 => \Delay2_out1_reg[13]\(12),
      I2 => \^pwm_en_axi_2_reg\,
      I3 => \Delay2_out1_reg[13]_0\(12),
      I4 => \^delaymatch5_reg_reg[1][13]\,
      O => \i__carry_i_8_n_0\
    );
\i__carry_i_9\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"A95900000000A959"
    )
        port map (
      I0 => Add1_out1_1(10),
      I1 => \Delay2_out1_reg[13]\(10),
      I2 => \^pwm_en_axi_2_reg\,
      I3 => \Delay2_out1_reg[13]_0\(10),
      I4 => \^delaymatch5_reg_reg[1][11]\,
      I5 => Saturation1_out1_1(11),
      O => \i__carry_i_9_n_0\
    );
\minus_out1_1[10]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"02"
    )
        port map (
      I0 => \minus_out1_1_reg[10]_0\,
      I1 => CO(0),
      I2 => Q(13),
      O => minus_out1(10)
    );
\minus_out1_1[11]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"02"
    )
        port map (
      I0 => \minus_out1_1_reg[11]_0\,
      I1 => CO(0),
      I2 => Q(13),
      O => minus_out1(11)
    );
\minus_out1_1[12]_i_1__1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFFF001E"
    )
        port map (
      I0 => \^min_pulse_width_axi_1_reg[9]\,
      I1 => Q(11),
      I2 => Q(12),
      I3 => Q(13),
      I4 => CO(0),
      O => minus_out1(12)
    );
\minus_out1_1[13]_i_1__1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFFF00FE"
    )
        port map (
      I0 => Q(11),
      I1 => \^min_pulse_width_axi_1_reg[9]\,
      I2 => Q(12),
      I3 => Q(13),
      I4 => CO(0),
      O => minus_out1(13)
    );
\minus_out1_1[13]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFFFFFFFFFFFFFE"
    )
        port map (
      I0 => Q(9),
      I1 => Q(7),
      I2 => \minus_out1_1_reg[7]_0\,
      I3 => Q(6),
      I4 => Q(8),
      I5 => Q(10),
      O => \^min_pulse_width_axi_1_reg[9]\
    );
\minus_out1_1[1]_i_1__1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"0006"
    )
        port map (
      I0 => Q(1),
      I1 => Q(0),
      I2 => CO(0),
      I3 => Q(13),
      O => minus_out1(1)
    );
\minus_out1_1[2]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"00000056"
    )
        port map (
      I0 => Q(2),
      I1 => Q(0),
      I2 => Q(1),
      I3 => CO(0),
      I4 => Q(13),
      O => minus_out1(2)
    );
\minus_out1_1[3]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"00005556"
    )
        port map (
      I0 => Q(3),
      I1 => Q(1),
      I2 => Q(0),
      I3 => Q(2),
      I4 => \minus_out1_1[5]_i_2__1_n_0\,
      O => minus_out1(3)
    );
\minus_out1_1[4]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0000000055555556"
    )
        port map (
      I0 => Q(4),
      I1 => Q(2),
      I2 => Q(0),
      I3 => Q(1),
      I4 => Q(3),
      I5 => \minus_out1_1[5]_i_2__1_n_0\,
      O => minus_out1(4)
    );
\minus_out1_1[5]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0000000055555556"
    )
        port map (
      I0 => Q(5),
      I1 => Q(3),
      I2 => \minus_out1_1_reg[5]_0\,
      I3 => Q(2),
      I4 => Q(4),
      I5 => \minus_out1_1[5]_i_2__1_n_0\,
      O => minus_out1(5)
    );
\minus_out1_1[5]_i_2__1\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"E"
    )
        port map (
      I0 => Q(13),
      I1 => CO(0),
      O => \minus_out1_1[5]_i_2__1_n_0\
    );
\minus_out1_1[6]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"02"
    )
        port map (
      I0 => \minus_out1_1_reg[6]_0\,
      I1 => CO(0),
      I2 => Q(13),
      O => minus_out1(6)
    );
\minus_out1_1[7]_i_1__1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"0000001E"
    )
        port map (
      I0 => Q(6),
      I1 => \minus_out1_1_reg[7]_0\,
      I2 => Q(7),
      I3 => CO(0),
      I4 => Q(13),
      O => minus_out1(7)
    );
\minus_out1_1[8]_i_1__1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"00000000000001FE"
    )
        port map (
      I0 => Q(7),
      I1 => \minus_out1_1_reg[7]_0\,
      I2 => Q(6),
      I3 => Q(8),
      I4 => CO(0),
      I5 => Q(13),
      O => minus_out1(8)
    );
\minus_out1_1[9]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"02"
    )
        port map (
      I0 => \minus_out1_1_reg[9]_0\,
      I1 => CO(0),
      I2 => Q(13),
      O => minus_out1(9)
    );
\minus_out1_1_reg[10]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => minus_out1(10),
      Q => minus_out1_1(10),
      R => RSTP
    );
\minus_out1_1_reg[11]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => minus_out1(11),
      Q => minus_out1_1(11),
      R => RSTP
    );
\minus_out1_1_reg[12]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => minus_out1(12),
      Q => minus_out1_1(12),
      R => RSTP
    );
\minus_out1_1_reg[13]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => minus_out1(13),
      Q => minus_out1_1(13),
      R => RSTP
    );
\minus_out1_1_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => minus_out1(1),
      Q => minus_out1_1(1),
      R => RSTP
    );
\minus_out1_1_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => minus_out1(2),
      Q => minus_out1_1(2),
      R => RSTP
    );
\minus_out1_1_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => minus_out1(3),
      Q => minus_out1_1(3),
      R => RSTP
    );
\minus_out1_1_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => minus_out1(4),
      Q => minus_out1_1(4),
      R => RSTP
    );
\minus_out1_1_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => minus_out1(5),
      Q => minus_out1_1(5),
      R => RSTP
    );
\minus_out1_1_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => minus_out1(6),
      Q => minus_out1_1(6),
      R => RSTP
    );
\minus_out1_1_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => minus_out1(7),
      Q => minus_out1_1(7),
      R => RSTP
    );
\minus_out1_1_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => minus_out1(8),
      Q => minus_out1_1(8),
      R => RSTP
    );
\minus_out1_1_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => minus_out1(9),
      Q => minus_out1_1(9),
      R => RSTP
    );
modulating_signal_in_clock_cycles_1_reg_i_1: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFFF4540"
    )
        port map (
      I0 => \Logical_Operator_out1__1\,
      I1 => \Delay2_out1_reg[13]_0\(13),
      I2 => \^pwm_en_axi_2_reg\,
      I3 => \Delay2_out1_reg[13]\(13),
      I4 => \modulating_signal_in_clock_cycles_1_reg_i_17__1_n_0\,
      O => B(13)
    );
modulating_signal_in_clock_cycles_1_reg_i_10: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFFF4540"
    )
        port map (
      I0 => \Logical_Operator_out1__1\,
      I1 => \Delay2_out1_reg[13]_0\(4),
      I2 => \^pwm_en_axi_2_reg\,
      I3 => \Delay2_out1_reg[13]\(4),
      I4 => \modulating_signal_in_clock_cycles_1_reg_i_17__1_n_0\,
      O => B(4)
    );
modulating_signal_in_clock_cycles_1_reg_i_11: unisim.vcomponents.LUT5
    generic map(
      INIT => X"BABBBAAA"
    )
        port map (
      I0 => \modulating_signal_in_clock_cycles_1_reg_i_18__1_n_0\,
      I1 => \Logical_Operator_out1__1\,
      I2 => \Delay2_out1_reg[13]_0\(3),
      I3 => \^pwm_en_axi_2_reg\,
      I4 => \Delay2_out1_reg[13]\(3),
      O => B(3)
    );
modulating_signal_in_clock_cycles_1_reg_i_12: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFFF4540"
    )
        port map (
      I0 => \Logical_Operator_out1__1\,
      I1 => \Delay2_out1_reg[13]_0\(2),
      I2 => \^pwm_en_axi_2_reg\,
      I3 => \Delay2_out1_reg[13]\(2),
      I4 => \modulating_signal_in_clock_cycles_1_reg_i_17__1_n_0\,
      O => B(2)
    );
modulating_signal_in_clock_cycles_1_reg_i_13: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFFF4540"
    )
        port map (
      I0 => \Logical_Operator_out1__1\,
      I1 => \Delay2_out1_reg[13]_0\(1),
      I2 => \^pwm_en_axi_2_reg\,
      I3 => \Delay2_out1_reg[13]\(1),
      I4 => \modulating_signal_in_clock_cycles_1_reg_i_17__1_n_0\,
      O => B(1)
    );
modulating_signal_in_clock_cycles_1_reg_i_14: unisim.vcomponents.LUT6
    generic map(
      INIT => X"00FFFFFFB8B8B8B8"
    )
        port map (
      I0 => \Delay2_out1_reg[13]_0\(0),
      I1 => \^pwm_en_axi_2_reg\,
      I2 => \Delay2_out1_reg[13]\(0),
      I3 => Relational_Operator1_relop1,
      I4 => Relational_Operator_relop1,
      I5 => \Logical_Operator_out1__1\,
      O => B(0)
    );
\modulating_signal_in_clock_cycles_1_reg_i_15__1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FEEE"
    )
        port map (
      I0 => Relational_Operator2_relop1,
      I1 => Relational_Operator3_relop1,
      I2 => Relational_Operator_relop1,
      I3 => Relational_Operator1_relop1,
      O => \Logical_Operator_out1__1\
    );
\modulating_signal_in_clock_cycles_1_reg_i_16__1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFFFFFF00008000"
    )
        port map (
      I0 => \Delay2_out1_reg[0]\,
      I1 => HDL_Counter2_count_reg_1_sn_1,
      I2 => HDL_Counter2_count_reg_16_sn_1,
      I3 => D(0),
      I4 => HDL_Counter2_count_reg(19),
      I5 => \Delay2_out1_reg[13]_2\(0),
      O => \^pwm_en_axi_2_reg\
    );
\modulating_signal_in_clock_cycles_1_reg_i_17__1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"70"
    )
        port map (
      I0 => Relational_Operator1_relop1,
      I1 => Relational_Operator_relop1,
      I2 => Relational_Operator2_relop1,
      O => \modulating_signal_in_clock_cycles_1_reg_i_17__1_n_0\
    );
\modulating_signal_in_clock_cycles_1_reg_i_18__1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"0070"
    )
        port map (
      I0 => Relational_Operator1_relop1,
      I1 => Relational_Operator_relop1,
      I2 => Relational_Operator3_relop1,
      I3 => Relational_Operator2_relop1,
      O => \modulating_signal_in_clock_cycles_1_reg_i_18__1_n_0\
    );
modulating_signal_in_clock_cycles_1_reg_i_2: unisim.vcomponents.LUT5
    generic map(
      INIT => X"BABBBAAA"
    )
        port map (
      I0 => \modulating_signal_in_clock_cycles_1_reg_i_18__1_n_0\,
      I1 => \Logical_Operator_out1__1\,
      I2 => \Delay2_out1_reg[13]_0\(12),
      I3 => \^pwm_en_axi_2_reg\,
      I4 => \Delay2_out1_reg[13]\(12),
      O => B(12)
    );
modulating_signal_in_clock_cycles_1_reg_i_3: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFFF4540"
    )
        port map (
      I0 => \Logical_Operator_out1__1\,
      I1 => \Delay2_out1_reg[13]_0\(11),
      I2 => \^pwm_en_axi_2_reg\,
      I3 => \Delay2_out1_reg[13]\(11),
      I4 => \modulating_signal_in_clock_cycles_1_reg_i_17__1_n_0\,
      O => B(11)
    );
modulating_signal_in_clock_cycles_1_reg_i_4: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFFF4540"
    )
        port map (
      I0 => \Logical_Operator_out1__1\,
      I1 => \Delay2_out1_reg[13]_0\(10),
      I2 => \^pwm_en_axi_2_reg\,
      I3 => \Delay2_out1_reg[13]\(10),
      I4 => \modulating_signal_in_clock_cycles_1_reg_i_17__1_n_0\,
      O => B(10)
    );
modulating_signal_in_clock_cycles_1_reg_i_5: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFFF4540"
    )
        port map (
      I0 => \Logical_Operator_out1__1\,
      I1 => \Delay2_out1_reg[13]_0\(9),
      I2 => \^pwm_en_axi_2_reg\,
      I3 => \Delay2_out1_reg[13]\(9),
      I4 => \modulating_signal_in_clock_cycles_1_reg_i_17__1_n_0\,
      O => B(9)
    );
modulating_signal_in_clock_cycles_1_reg_i_6: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFFF4540"
    )
        port map (
      I0 => \Logical_Operator_out1__1\,
      I1 => \Delay2_out1_reg[13]_0\(8),
      I2 => \^pwm_en_axi_2_reg\,
      I3 => \Delay2_out1_reg[13]\(8),
      I4 => \modulating_signal_in_clock_cycles_1_reg_i_17__1_n_0\,
      O => B(8)
    );
modulating_signal_in_clock_cycles_1_reg_i_7: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFFF4540"
    )
        port map (
      I0 => \Logical_Operator_out1__1\,
      I1 => \Delay2_out1_reg[13]_0\(7),
      I2 => \^pwm_en_axi_2_reg\,
      I3 => \Delay2_out1_reg[13]\(7),
      I4 => \modulating_signal_in_clock_cycles_1_reg_i_17__1_n_0\,
      O => B(7)
    );
modulating_signal_in_clock_cycles_1_reg_i_8: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFFF4540"
    )
        port map (
      I0 => \Logical_Operator_out1__1\,
      I1 => \Delay2_out1_reg[13]_0\(6),
      I2 => \^pwm_en_axi_2_reg\,
      I3 => \Delay2_out1_reg[13]\(6),
      I4 => \modulating_signal_in_clock_cycles_1_reg_i_17__1_n_0\,
      O => B(6)
    );
modulating_signal_in_clock_cycles_1_reg_i_9: unisim.vcomponents.LUT5
    generic map(
      INIT => X"BABBBAAA"
    )
        port map (
      I0 => \modulating_signal_in_clock_cycles_1_reg_i_18__1_n_0\,
      I1 => \Logical_Operator_out1__1\,
      I2 => \Delay2_out1_reg[13]_0\(5),
      I3 => \^pwm_en_axi_2_reg\,
      I4 => \Delay2_out1_reg[13]\(5),
      O => B(5)
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity zusys_PWM_SS_3L_ip_0_0_PWM_SS_3L_ip_src_Modulator_a is
  port (
    \reduced_reg_1_reg[1]_9\ : out STD_LOGIC_VECTOR ( 20 downto 0 );
    D : out STD_LOGIC_VECTOR ( 1 downto 0 );
    S : out STD_LOGIC_VECTOR ( 3 downto 0 );
    DI : out STD_LOGIC_VECTOR ( 0 to 0 );
    \reduced_reg_1_reg[1][20]_0\ : out STD_LOGIC_VECTOR ( 0 to 0 );
    \reduced_reg_reg[1][14]_0\ : out STD_LOGIC_VECTOR ( 7 downto 0 );
    \reduced_reg_reg[1][14]_1\ : out STD_LOGIC_VECTOR ( 7 downto 0 );
    \reduced_reg_reg[1][18]_0\ : out STD_LOGIC_VECTOR ( 1 downto 0 );
    \reduced_reg_reg[1][18]_1\ : out STD_LOGIC_VECTOR ( 1 downto 0 );
    \reduced_reg_reg[1][14]_2\ : out STD_LOGIC_VECTOR ( 7 downto 0 );
    \reduced_reg_reg[1][14]_3\ : out STD_LOGIC_VECTOR ( 7 downto 0 );
    \reduced_reg_reg[1][18]_2\ : out STD_LOGIC_VECTOR ( 1 downto 0 );
    \reduced_reg_reg[1][18]_3\ : out STD_LOGIC_VECTOR ( 1 downto 0 );
    CEP : in STD_LOGIC;
    IPCORE_CLK : in STD_LOGIC;
    RSTP : in STD_LOGIC;
    B : in STD_LOGIC_VECTOR ( 13 downto 0 );
    maximum_counter_value_1 : in STD_LOGIC_VECTOR ( 19 downto 0 );
    HDL_Counter2_count_reg : in STD_LOGIC_VECTOR ( 19 downto 0 );
    Counter_Ctrl_out3 : in STD_LOGIC_VECTOR ( 20 downto 0 );
    P : in STD_LOGIC_VECTOR ( 20 downto 0 );
    \AND_out10_carry__0_0\ : in STD_LOGIC_VECTOR ( 20 downto 0 )
  );
  attribute ORIG_REF_NAME : string;
  attribute ORIG_REF_NAME of zusys_PWM_SS_3L_ip_0_0_PWM_SS_3L_ip_src_Modulator_a : entity is "PWM_SS_3L_ip_src_Modulator_a";
end zusys_PWM_SS_3L_ip_0_0_PWM_SS_3L_ip_src_Modulator_a;

architecture STRUCTURE of zusys_PWM_SS_3L_ip_0_0_PWM_SS_3L_ip_src_Modulator_a is
  signal \AND_out10_carry__0_i_1_n_0\ : STD_LOGIC;
  signal \AND_out10_carry__0_i_2_n_0\ : STD_LOGIC;
  signal \AND_out10_carry__0_i_3_n_0\ : STD_LOGIC;
  signal \AND_out10_carry__0_i_4_n_0\ : STD_LOGIC;
  signal \AND_out10_carry__0_i_5_n_0\ : STD_LOGIC;
  signal \AND_out10_carry__0_i_6_n_0\ : STD_LOGIC;
  signal \AND_out10_carry__0_n_6\ : STD_LOGIC;
  signal \AND_out10_carry__0_n_7\ : STD_LOGIC;
  signal AND_out10_carry_i_10_n_0 : STD_LOGIC;
  signal AND_out10_carry_i_11_n_0 : STD_LOGIC;
  signal AND_out10_carry_i_12_n_0 : STD_LOGIC;
  signal AND_out10_carry_i_13_n_0 : STD_LOGIC;
  signal AND_out10_carry_i_14_n_0 : STD_LOGIC;
  signal AND_out10_carry_i_15_n_0 : STD_LOGIC;
  signal AND_out10_carry_i_16_n_0 : STD_LOGIC;
  signal AND_out10_carry_i_1_n_0 : STD_LOGIC;
  signal AND_out10_carry_i_2_n_0 : STD_LOGIC;
  signal AND_out10_carry_i_3_n_0 : STD_LOGIC;
  signal AND_out10_carry_i_4_n_0 : STD_LOGIC;
  signal AND_out10_carry_i_5_n_0 : STD_LOGIC;
  signal AND_out10_carry_i_6_n_0 : STD_LOGIC;
  signal AND_out10_carry_i_7_n_0 : STD_LOGIC;
  signal AND_out10_carry_i_8_n_0 : STD_LOGIC;
  signal AND_out10_carry_i_9_n_0 : STD_LOGIC;
  signal AND_out10_carry_n_0 : STD_LOGIC;
  signal AND_out10_carry_n_1 : STD_LOGIC;
  signal AND_out10_carry_n_2 : STD_LOGIC;
  signal AND_out10_carry_n_3 : STD_LOGIC;
  signal AND_out10_carry_n_4 : STD_LOGIC;
  signal AND_out10_carry_n_5 : STD_LOGIC;
  signal AND_out10_carry_n_6 : STD_LOGIC;
  signal AND_out10_carry_n_7 : STD_LOGIC;
  signal \AND_out10_inferred__0/i__carry__0_n_6\ : STD_LOGIC;
  signal \AND_out10_inferred__0/i__carry__0_n_7\ : STD_LOGIC;
  signal \AND_out10_inferred__0/i__carry_n_0\ : STD_LOGIC;
  signal \AND_out10_inferred__0/i__carry_n_1\ : STD_LOGIC;
  signal \AND_out10_inferred__0/i__carry_n_2\ : STD_LOGIC;
  signal \AND_out10_inferred__0/i__carry_n_3\ : STD_LOGIC;
  signal \AND_out10_inferred__0/i__carry_n_4\ : STD_LOGIC;
  signal \AND_out10_inferred__0/i__carry_n_5\ : STD_LOGIC;
  signal \AND_out10_inferred__0/i__carry_n_6\ : STD_LOGIC;
  signal \AND_out10_inferred__0/i__carry_n_7\ : STD_LOGIC;
  signal Relational_Operator1_relop1 : STD_LOGIC;
  signal Relational_Operator_relop1 : STD_LOGIC;
  signal \i__carry__0_i_1_n_0\ : STD_LOGIC;
  signal \i__carry__0_i_2_n_0\ : STD_LOGIC;
  signal \i__carry__0_i_3_n_0\ : STD_LOGIC;
  signal \i__carry__0_i_4_n_0\ : STD_LOGIC;
  signal \i__carry__0_i_5_n_0\ : STD_LOGIC;
  signal \i__carry_i_10__2_n_0\ : STD_LOGIC;
  signal \i__carry_i_11__2_n_0\ : STD_LOGIC;
  signal \i__carry_i_12__2_n_0\ : STD_LOGIC;
  signal \i__carry_i_13__2_n_0\ : STD_LOGIC;
  signal \i__carry_i_14__2_n_0\ : STD_LOGIC;
  signal \i__carry_i_15_n_0\ : STD_LOGIC;
  signal \i__carry_i_16_n_0\ : STD_LOGIC;
  signal \i__carry_i_1__2_n_0\ : STD_LOGIC;
  signal \i__carry_i_2__2_n_0\ : STD_LOGIC;
  signal \i__carry_i_3__2_n_0\ : STD_LOGIC;
  signal \i__carry_i_4__2_n_0\ : STD_LOGIC;
  signal \i__carry_i_5__2_n_0\ : STD_LOGIC;
  signal \i__carry_i_6__2_n_0\ : STD_LOGIC;
  signal \i__carry_i_7__2_n_0\ : STD_LOGIC;
  signal \i__carry_i_8__2_n_0\ : STD_LOGIC;
  signal \i__carry_i_9__2_n_0\ : STD_LOGIC;
  signal \modulating_signal_in_clock_cycles_1_reg__0\ : STD_LOGIC_VECTOR ( 20 downto 0 );
  signal modulating_signal_in_clock_cycles_1_reg_n_100 : STD_LOGIC;
  signal modulating_signal_in_clock_cycles_1_reg_n_101 : STD_LOGIC;
  signal modulating_signal_in_clock_cycles_1_reg_n_102 : STD_LOGIC;
  signal modulating_signal_in_clock_cycles_1_reg_n_103 : STD_LOGIC;
  signal modulating_signal_in_clock_cycles_1_reg_n_104 : STD_LOGIC;
  signal modulating_signal_in_clock_cycles_1_reg_n_105 : STD_LOGIC;
  signal modulating_signal_in_clock_cycles_1_reg_n_94 : STD_LOGIC;
  signal modulating_signal_in_clock_cycles_1_reg_n_95 : STD_LOGIC;
  signal modulating_signal_in_clock_cycles_1_reg_n_96 : STD_LOGIC;
  signal modulating_signal_in_clock_cycles_1_reg_n_97 : STD_LOGIC;
  signal modulating_signal_in_clock_cycles_1_reg_n_98 : STD_LOGIC;
  signal modulating_signal_in_clock_cycles_1_reg_n_99 : STD_LOGIC;
  signal \reduced_reg_1_reg[0]_7\ : STD_LOGIC_VECTOR ( 20 downto 0 );
  signal \^reduced_reg_1_reg[1]_9\ : STD_LOGIC_VECTOR ( 20 downto 0 );
  signal \reduced_reg_reg[0]_6\ : STD_LOGIC_VECTOR ( 19 downto 0 );
  signal \reduced_reg_reg[1]_8\ : STD_LOGIC_VECTOR ( 19 downto 0 );
  signal NLW_AND_out10_carry_O_UNCONNECTED : STD_LOGIC_VECTOR ( 7 downto 0 );
  signal \NLW_AND_out10_carry__0_CO_UNCONNECTED\ : STD_LOGIC_VECTOR ( 7 downto 3 );
  signal \NLW_AND_out10_carry__0_O_UNCONNECTED\ : STD_LOGIC_VECTOR ( 7 downto 0 );
  signal \NLW_AND_out10_inferred__0/i__carry_O_UNCONNECTED\ : STD_LOGIC_VECTOR ( 7 downto 0 );
  signal \NLW_AND_out10_inferred__0/i__carry__0_CO_UNCONNECTED\ : STD_LOGIC_VECTOR ( 7 downto 3 );
  signal \NLW_AND_out10_inferred__0/i__carry__0_O_UNCONNECTED\ : STD_LOGIC_VECTOR ( 7 downto 0 );
  signal NLW_modulating_signal_in_clock_cycles_1_reg_CARRYCASCOUT_UNCONNECTED : STD_LOGIC;
  signal NLW_modulating_signal_in_clock_cycles_1_reg_MULTSIGNOUT_UNCONNECTED : STD_LOGIC;
  signal NLW_modulating_signal_in_clock_cycles_1_reg_OVERFLOW_UNCONNECTED : STD_LOGIC;
  signal NLW_modulating_signal_in_clock_cycles_1_reg_PATTERNBDETECT_UNCONNECTED : STD_LOGIC;
  signal NLW_modulating_signal_in_clock_cycles_1_reg_PATTERNDETECT_UNCONNECTED : STD_LOGIC;
  signal NLW_modulating_signal_in_clock_cycles_1_reg_UNDERFLOW_UNCONNECTED : STD_LOGIC;
  signal NLW_modulating_signal_in_clock_cycles_1_reg_ACOUT_UNCONNECTED : STD_LOGIC_VECTOR ( 29 downto 0 );
  signal NLW_modulating_signal_in_clock_cycles_1_reg_BCOUT_UNCONNECTED : STD_LOGIC_VECTOR ( 17 downto 0 );
  signal NLW_modulating_signal_in_clock_cycles_1_reg_CARRYOUT_UNCONNECTED : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal NLW_modulating_signal_in_clock_cycles_1_reg_P_UNCONNECTED : STD_LOGIC_VECTOR ( 47 downto 33 );
  signal NLW_modulating_signal_in_clock_cycles_1_reg_PCOUT_UNCONNECTED : STD_LOGIC_VECTOR ( 47 downto 0 );
  signal NLW_modulating_signal_in_clock_cycles_1_reg_XOROUT_UNCONNECTED : STD_LOGIC_VECTOR ( 7 downto 0 );
  attribute COMPARATOR_THRESHOLD : integer;
  attribute COMPARATOR_THRESHOLD of AND_out10_carry : label is 11;
  attribute COMPARATOR_THRESHOLD of \AND_out10_carry__0\ : label is 11;
  attribute COMPARATOR_THRESHOLD of \AND_out10_inferred__0/i__carry\ : label is 11;
  attribute COMPARATOR_THRESHOLD of \AND_out10_inferred__0/i__carry__0\ : label is 11;
  attribute SOFT_HLUTNM : string;
  attribute SOFT_HLUTNM of \Switch3_out1_1[0]_i_2\ : label is "soft_lutpair50";
  attribute SOFT_HLUTNM of \Switch3_out1_1[1]_i_1\ : label is "soft_lutpair50";
  attribute KEEP_HIERARCHY : string;
  attribute KEEP_HIERARCHY of modulating_signal_in_clock_cycles_1_reg : label is "yes";
begin
  \reduced_reg_1_reg[1]_9\(20 downto 0) <= \^reduced_reg_1_reg[1]_9\(20 downto 0);
AND_out10_carry: unisim.vcomponents.CARRY8
     port map (
      CI => '1',
      CI_TOP => '0',
      CO(7) => AND_out10_carry_n_0,
      CO(6) => AND_out10_carry_n_1,
      CO(5) => AND_out10_carry_n_2,
      CO(4) => AND_out10_carry_n_3,
      CO(3) => AND_out10_carry_n_4,
      CO(2) => AND_out10_carry_n_5,
      CO(1) => AND_out10_carry_n_6,
      CO(0) => AND_out10_carry_n_7,
      DI(7) => AND_out10_carry_i_1_n_0,
      DI(6) => AND_out10_carry_i_2_n_0,
      DI(5) => AND_out10_carry_i_3_n_0,
      DI(4) => AND_out10_carry_i_4_n_0,
      DI(3) => AND_out10_carry_i_5_n_0,
      DI(2) => AND_out10_carry_i_6_n_0,
      DI(1) => AND_out10_carry_i_7_n_0,
      DI(0) => AND_out10_carry_i_8_n_0,
      O(7 downto 0) => NLW_AND_out10_carry_O_UNCONNECTED(7 downto 0),
      S(7) => AND_out10_carry_i_9_n_0,
      S(6) => AND_out10_carry_i_10_n_0,
      S(5) => AND_out10_carry_i_11_n_0,
      S(4) => AND_out10_carry_i_12_n_0,
      S(3) => AND_out10_carry_i_13_n_0,
      S(2) => AND_out10_carry_i_14_n_0,
      S(1) => AND_out10_carry_i_15_n_0,
      S(0) => AND_out10_carry_i_16_n_0
    );
\AND_out10_carry__0\: unisim.vcomponents.CARRY8
     port map (
      CI => AND_out10_carry_n_0,
      CI_TOP => '0',
      CO(7 downto 3) => \NLW_AND_out10_carry__0_CO_UNCONNECTED\(7 downto 3),
      CO(2) => Relational_Operator1_relop1,
      CO(1) => \AND_out10_carry__0_n_6\,
      CO(0) => \AND_out10_carry__0_n_7\,
      DI(7 downto 3) => B"00000",
      DI(2) => \AND_out10_carry__0_i_1_n_0\,
      DI(1) => \AND_out10_carry__0_i_2_n_0\,
      DI(0) => \AND_out10_carry__0_i_3_n_0\,
      O(7 downto 0) => \NLW_AND_out10_carry__0_O_UNCONNECTED\(7 downto 0),
      S(7 downto 3) => B"00000",
      S(2) => \AND_out10_carry__0_i_4_n_0\,
      S(1) => \AND_out10_carry__0_i_5_n_0\,
      S(0) => \AND_out10_carry__0_i_6_n_0\
    );
\AND_out10_carry__0_i_1\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"2"
    )
        port map (
      I0 => \^reduced_reg_1_reg[1]_9\(20),
      I1 => \modulating_signal_in_clock_cycles_1_reg__0\(20),
      O => \AND_out10_carry__0_i_1_n_0\
    );
\AND_out10_carry__0_i_1__0\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"2"
    )
        port map (
      I0 => \^reduced_reg_1_reg[1]_9\(20),
      I1 => P(20),
      O => DI(0)
    );
\AND_out10_carry__0_i_1__1\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"2"
    )
        port map (
      I0 => \^reduced_reg_1_reg[1]_9\(20),
      I1 => \AND_out10_carry__0_0\(20),
      O => \reduced_reg_1_reg[1][20]_0\(0)
    );
\AND_out10_carry__0_i_2\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"2F02"
    )
        port map (
      I0 => \modulating_signal_in_clock_cycles_1_reg__0\(18),
      I1 => \^reduced_reg_1_reg[1]_9\(18),
      I2 => \^reduced_reg_1_reg[1]_9\(19),
      I3 => \modulating_signal_in_clock_cycles_1_reg__0\(19),
      O => \AND_out10_carry__0_i_2_n_0\
    );
\AND_out10_carry__0_i_3\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"2F02"
    )
        port map (
      I0 => \modulating_signal_in_clock_cycles_1_reg__0\(16),
      I1 => \^reduced_reg_1_reg[1]_9\(16),
      I2 => \^reduced_reg_1_reg[1]_9\(17),
      I3 => \modulating_signal_in_clock_cycles_1_reg__0\(17),
      O => \AND_out10_carry__0_i_3_n_0\
    );
\AND_out10_carry__0_i_4\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"9"
    )
        port map (
      I0 => \modulating_signal_in_clock_cycles_1_reg__0\(20),
      I1 => \^reduced_reg_1_reg[1]_9\(20),
      O => \AND_out10_carry__0_i_4_n_0\
    );
\AND_out10_carry__0_i_5\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"9009"
    )
        port map (
      I0 => \modulating_signal_in_clock_cycles_1_reg__0\(18),
      I1 => \^reduced_reg_1_reg[1]_9\(18),
      I2 => \modulating_signal_in_clock_cycles_1_reg__0\(19),
      I3 => \^reduced_reg_1_reg[1]_9\(19),
      O => \AND_out10_carry__0_i_5_n_0\
    );
\AND_out10_carry__0_i_6\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"9009"
    )
        port map (
      I0 => \modulating_signal_in_clock_cycles_1_reg__0\(16),
      I1 => \^reduced_reg_1_reg[1]_9\(16),
      I2 => \modulating_signal_in_clock_cycles_1_reg__0\(17),
      I3 => \^reduced_reg_1_reg[1]_9\(17),
      O => \AND_out10_carry__0_i_6_n_0\
    );
AND_out10_carry_i_1: unisim.vcomponents.LUT4
    generic map(
      INIT => X"2F02"
    )
        port map (
      I0 => \modulating_signal_in_clock_cycles_1_reg__0\(14),
      I1 => \^reduced_reg_1_reg[1]_9\(14),
      I2 => \^reduced_reg_1_reg[1]_9\(15),
      I3 => \modulating_signal_in_clock_cycles_1_reg__0\(15),
      O => AND_out10_carry_i_1_n_0
    );
AND_out10_carry_i_10: unisim.vcomponents.LUT4
    generic map(
      INIT => X"9009"
    )
        port map (
      I0 => \modulating_signal_in_clock_cycles_1_reg__0\(12),
      I1 => \^reduced_reg_1_reg[1]_9\(12),
      I2 => \modulating_signal_in_clock_cycles_1_reg__0\(13),
      I3 => \^reduced_reg_1_reg[1]_9\(13),
      O => AND_out10_carry_i_10_n_0
    );
AND_out10_carry_i_11: unisim.vcomponents.LUT4
    generic map(
      INIT => X"9009"
    )
        port map (
      I0 => \modulating_signal_in_clock_cycles_1_reg__0\(10),
      I1 => \^reduced_reg_1_reg[1]_9\(10),
      I2 => \modulating_signal_in_clock_cycles_1_reg__0\(11),
      I3 => \^reduced_reg_1_reg[1]_9\(11),
      O => AND_out10_carry_i_11_n_0
    );
AND_out10_carry_i_12: unisim.vcomponents.LUT4
    generic map(
      INIT => X"9009"
    )
        port map (
      I0 => \modulating_signal_in_clock_cycles_1_reg__0\(8),
      I1 => \^reduced_reg_1_reg[1]_9\(8),
      I2 => \modulating_signal_in_clock_cycles_1_reg__0\(9),
      I3 => \^reduced_reg_1_reg[1]_9\(9),
      O => AND_out10_carry_i_12_n_0
    );
AND_out10_carry_i_13: unisim.vcomponents.LUT4
    generic map(
      INIT => X"9009"
    )
        port map (
      I0 => \modulating_signal_in_clock_cycles_1_reg__0\(6),
      I1 => \^reduced_reg_1_reg[1]_9\(6),
      I2 => \modulating_signal_in_clock_cycles_1_reg__0\(7),
      I3 => \^reduced_reg_1_reg[1]_9\(7),
      O => AND_out10_carry_i_13_n_0
    );
AND_out10_carry_i_14: unisim.vcomponents.LUT4
    generic map(
      INIT => X"9009"
    )
        port map (
      I0 => \modulating_signal_in_clock_cycles_1_reg__0\(4),
      I1 => \^reduced_reg_1_reg[1]_9\(4),
      I2 => \modulating_signal_in_clock_cycles_1_reg__0\(5),
      I3 => \^reduced_reg_1_reg[1]_9\(5),
      O => AND_out10_carry_i_14_n_0
    );
AND_out10_carry_i_15: unisim.vcomponents.LUT4
    generic map(
      INIT => X"9009"
    )
        port map (
      I0 => \modulating_signal_in_clock_cycles_1_reg__0\(2),
      I1 => \^reduced_reg_1_reg[1]_9\(2),
      I2 => \modulating_signal_in_clock_cycles_1_reg__0\(3),
      I3 => \^reduced_reg_1_reg[1]_9\(3),
      O => AND_out10_carry_i_15_n_0
    );
AND_out10_carry_i_16: unisim.vcomponents.LUT4
    generic map(
      INIT => X"9009"
    )
        port map (
      I0 => \modulating_signal_in_clock_cycles_1_reg__0\(0),
      I1 => \^reduced_reg_1_reg[1]_9\(0),
      I2 => \modulating_signal_in_clock_cycles_1_reg__0\(1),
      I3 => \^reduced_reg_1_reg[1]_9\(1),
      O => AND_out10_carry_i_16_n_0
    );
AND_out10_carry_i_2: unisim.vcomponents.LUT4
    generic map(
      INIT => X"2F02"
    )
        port map (
      I0 => \modulating_signal_in_clock_cycles_1_reg__0\(12),
      I1 => \^reduced_reg_1_reg[1]_9\(12),
      I2 => \^reduced_reg_1_reg[1]_9\(13),
      I3 => \modulating_signal_in_clock_cycles_1_reg__0\(13),
      O => AND_out10_carry_i_2_n_0
    );
AND_out10_carry_i_3: unisim.vcomponents.LUT4
    generic map(
      INIT => X"2F02"
    )
        port map (
      I0 => \modulating_signal_in_clock_cycles_1_reg__0\(10),
      I1 => \^reduced_reg_1_reg[1]_9\(10),
      I2 => \^reduced_reg_1_reg[1]_9\(11),
      I3 => \modulating_signal_in_clock_cycles_1_reg__0\(11),
      O => AND_out10_carry_i_3_n_0
    );
AND_out10_carry_i_4: unisim.vcomponents.LUT4
    generic map(
      INIT => X"2F02"
    )
        port map (
      I0 => \modulating_signal_in_clock_cycles_1_reg__0\(8),
      I1 => \^reduced_reg_1_reg[1]_9\(8),
      I2 => \^reduced_reg_1_reg[1]_9\(9),
      I3 => \modulating_signal_in_clock_cycles_1_reg__0\(9),
      O => AND_out10_carry_i_4_n_0
    );
AND_out10_carry_i_5: unisim.vcomponents.LUT4
    generic map(
      INIT => X"2F02"
    )
        port map (
      I0 => \modulating_signal_in_clock_cycles_1_reg__0\(6),
      I1 => \^reduced_reg_1_reg[1]_9\(6),
      I2 => \^reduced_reg_1_reg[1]_9\(7),
      I3 => \modulating_signal_in_clock_cycles_1_reg__0\(7),
      O => AND_out10_carry_i_5_n_0
    );
AND_out10_carry_i_6: unisim.vcomponents.LUT4
    generic map(
      INIT => X"2F02"
    )
        port map (
      I0 => \modulating_signal_in_clock_cycles_1_reg__0\(4),
      I1 => \^reduced_reg_1_reg[1]_9\(4),
      I2 => \^reduced_reg_1_reg[1]_9\(5),
      I3 => \modulating_signal_in_clock_cycles_1_reg__0\(5),
      O => AND_out10_carry_i_6_n_0
    );
AND_out10_carry_i_7: unisim.vcomponents.LUT4
    generic map(
      INIT => X"2F02"
    )
        port map (
      I0 => \modulating_signal_in_clock_cycles_1_reg__0\(2),
      I1 => \^reduced_reg_1_reg[1]_9\(2),
      I2 => \^reduced_reg_1_reg[1]_9\(3),
      I3 => \modulating_signal_in_clock_cycles_1_reg__0\(3),
      O => AND_out10_carry_i_7_n_0
    );
AND_out10_carry_i_8: unisim.vcomponents.LUT4
    generic map(
      INIT => X"2F02"
    )
        port map (
      I0 => \modulating_signal_in_clock_cycles_1_reg__0\(0),
      I1 => \^reduced_reg_1_reg[1]_9\(0),
      I2 => \^reduced_reg_1_reg[1]_9\(1),
      I3 => \modulating_signal_in_clock_cycles_1_reg__0\(1),
      O => AND_out10_carry_i_8_n_0
    );
AND_out10_carry_i_9: unisim.vcomponents.LUT4
    generic map(
      INIT => X"9009"
    )
        port map (
      I0 => \modulating_signal_in_clock_cycles_1_reg__0\(14),
      I1 => \^reduced_reg_1_reg[1]_9\(14),
      I2 => \modulating_signal_in_clock_cycles_1_reg__0\(15),
      I3 => \^reduced_reg_1_reg[1]_9\(15),
      O => AND_out10_carry_i_9_n_0
    );
\AND_out10_inferred__0/i__carry\: unisim.vcomponents.CARRY8
     port map (
      CI => '1',
      CI_TOP => '0',
      CO(7) => \AND_out10_inferred__0/i__carry_n_0\,
      CO(6) => \AND_out10_inferred__0/i__carry_n_1\,
      CO(5) => \AND_out10_inferred__0/i__carry_n_2\,
      CO(4) => \AND_out10_inferred__0/i__carry_n_3\,
      CO(3) => \AND_out10_inferred__0/i__carry_n_4\,
      CO(2) => \AND_out10_inferred__0/i__carry_n_5\,
      CO(1) => \AND_out10_inferred__0/i__carry_n_6\,
      CO(0) => \AND_out10_inferred__0/i__carry_n_7\,
      DI(7) => \i__carry_i_1__2_n_0\,
      DI(6) => \i__carry_i_2__2_n_0\,
      DI(5) => \i__carry_i_3__2_n_0\,
      DI(4) => \i__carry_i_4__2_n_0\,
      DI(3) => \i__carry_i_5__2_n_0\,
      DI(2) => \i__carry_i_6__2_n_0\,
      DI(1) => \i__carry_i_7__2_n_0\,
      DI(0) => \i__carry_i_8__2_n_0\,
      O(7 downto 0) => \NLW_AND_out10_inferred__0/i__carry_O_UNCONNECTED\(7 downto 0),
      S(7) => \i__carry_i_9__2_n_0\,
      S(6) => \i__carry_i_10__2_n_0\,
      S(5) => \i__carry_i_11__2_n_0\,
      S(4) => \i__carry_i_12__2_n_0\,
      S(3) => \i__carry_i_13__2_n_0\,
      S(2) => \i__carry_i_14__2_n_0\,
      S(1) => \i__carry_i_15_n_0\,
      S(0) => \i__carry_i_16_n_0\
    );
\AND_out10_inferred__0/i__carry__0\: unisim.vcomponents.CARRY8
     port map (
      CI => \AND_out10_inferred__0/i__carry_n_0\,
      CI_TOP => '0',
      CO(7 downto 3) => \NLW_AND_out10_inferred__0/i__carry__0_CO_UNCONNECTED\(7 downto 3),
      CO(2) => Relational_Operator_relop1,
      CO(1) => \AND_out10_inferred__0/i__carry__0_n_6\,
      CO(0) => \AND_out10_inferred__0/i__carry__0_n_7\,
      DI(7 downto 3) => B"00000",
      DI(2) => \modulating_signal_in_clock_cycles_1_reg__0\(20),
      DI(1) => \i__carry__0_i_1_n_0\,
      DI(0) => \i__carry__0_i_2_n_0\,
      O(7 downto 0) => \NLW_AND_out10_inferred__0/i__carry__0_O_UNCONNECTED\(7 downto 0),
      S(7 downto 3) => B"00000",
      S(2) => \i__carry__0_i_3_n_0\,
      S(1) => \i__carry__0_i_4_n_0\,
      S(0) => \i__carry__0_i_5_n_0\
    );
\Add1_out1_carry__1_i_1\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"9"
    )
        port map (
      I0 => HDL_Counter2_count_reg(19),
      I1 => maximum_counter_value_1(19),
      O => S(3)
    );
\Add1_out1_carry__1_i_2\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"9"
    )
        port map (
      I0 => HDL_Counter2_count_reg(18),
      I1 => maximum_counter_value_1(18),
      O => S(2)
    );
\Add1_out1_carry__1_i_3\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"9"
    )
        port map (
      I0 => HDL_Counter2_count_reg(17),
      I1 => maximum_counter_value_1(17),
      O => S(1)
    );
\Add1_out1_carry__1_i_4\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"9"
    )
        port map (
      I0 => HDL_Counter2_count_reg(16),
      I1 => maximum_counter_value_1(16),
      O => S(0)
    );
\Switch3_out1_1[0]_i_2\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"2"
    )
        port map (
      I0 => Relational_Operator1_relop1,
      I1 => Relational_Operator_relop1,
      O => D(1)
    );
\Switch3_out1_1[1]_i_1\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"2"
    )
        port map (
      I0 => Relational_Operator1_relop1,
      O => D(0)
    );
\i__carry__0_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"2F02"
    )
        port map (
      I0 => \reduced_reg_reg[1]_8\(18),
      I1 => \modulating_signal_in_clock_cycles_1_reg__0\(18),
      I2 => \modulating_signal_in_clock_cycles_1_reg__0\(19),
      I3 => \reduced_reg_reg[1]_8\(19),
      O => \i__carry__0_i_1_n_0\
    );
\i__carry__0_i_1__0\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"2F02"
    )
        port map (
      I0 => \reduced_reg_reg[1]_8\(18),
      I1 => P(18),
      I2 => P(19),
      I3 => \reduced_reg_reg[1]_8\(19),
      O => \reduced_reg_reg[1][18]_1\(1)
    );
\i__carry__0_i_1__1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"2F02"
    )
        port map (
      I0 => \reduced_reg_reg[1]_8\(18),
      I1 => \AND_out10_carry__0_0\(18),
      I2 => \AND_out10_carry__0_0\(19),
      I3 => \reduced_reg_reg[1]_8\(19),
      O => \reduced_reg_reg[1][18]_3\(1)
    );
\i__carry__0_i_2\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"2F02"
    )
        port map (
      I0 => \reduced_reg_reg[1]_8\(16),
      I1 => \modulating_signal_in_clock_cycles_1_reg__0\(16),
      I2 => \modulating_signal_in_clock_cycles_1_reg__0\(17),
      I3 => \reduced_reg_reg[1]_8\(17),
      O => \i__carry__0_i_2_n_0\
    );
\i__carry__0_i_2__0\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"2F02"
    )
        port map (
      I0 => \reduced_reg_reg[1]_8\(16),
      I1 => P(16),
      I2 => P(17),
      I3 => \reduced_reg_reg[1]_8\(17),
      O => \reduced_reg_reg[1][18]_1\(0)
    );
\i__carry__0_i_2__1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"2F02"
    )
        port map (
      I0 => \reduced_reg_reg[1]_8\(16),
      I1 => \AND_out10_carry__0_0\(16),
      I2 => \AND_out10_carry__0_0\(17),
      I3 => \reduced_reg_reg[1]_8\(17),
      O => \reduced_reg_reg[1][18]_3\(0)
    );
\i__carry__0_i_3\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => \modulating_signal_in_clock_cycles_1_reg__0\(20),
      O => \i__carry__0_i_3_n_0\
    );
\i__carry__0_i_4\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"9009"
    )
        port map (
      I0 => \reduced_reg_reg[1]_8\(18),
      I1 => \modulating_signal_in_clock_cycles_1_reg__0\(18),
      I2 => \reduced_reg_reg[1]_8\(19),
      I3 => \modulating_signal_in_clock_cycles_1_reg__0\(19),
      O => \i__carry__0_i_4_n_0\
    );
\i__carry__0_i_4__0\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"9009"
    )
        port map (
      I0 => \reduced_reg_reg[1]_8\(18),
      I1 => P(18),
      I2 => \reduced_reg_reg[1]_8\(19),
      I3 => P(19),
      O => \reduced_reg_reg[1][18]_0\(1)
    );
\i__carry__0_i_4__1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"9009"
    )
        port map (
      I0 => \reduced_reg_reg[1]_8\(18),
      I1 => \AND_out10_carry__0_0\(18),
      I2 => \reduced_reg_reg[1]_8\(19),
      I3 => \AND_out10_carry__0_0\(19),
      O => \reduced_reg_reg[1][18]_2\(1)
    );
\i__carry__0_i_5\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"9009"
    )
        port map (
      I0 => \reduced_reg_reg[1]_8\(16),
      I1 => \modulating_signal_in_clock_cycles_1_reg__0\(16),
      I2 => \reduced_reg_reg[1]_8\(17),
      I3 => \modulating_signal_in_clock_cycles_1_reg__0\(17),
      O => \i__carry__0_i_5_n_0\
    );
\i__carry__0_i_5__0\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"9009"
    )
        port map (
      I0 => \reduced_reg_reg[1]_8\(16),
      I1 => P(16),
      I2 => \reduced_reg_reg[1]_8\(17),
      I3 => P(17),
      O => \reduced_reg_reg[1][18]_0\(0)
    );
\i__carry__0_i_5__1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"9009"
    )
        port map (
      I0 => \reduced_reg_reg[1]_8\(16),
      I1 => \AND_out10_carry__0_0\(16),
      I2 => \reduced_reg_reg[1]_8\(17),
      I3 => \AND_out10_carry__0_0\(17),
      O => \reduced_reg_reg[1][18]_2\(0)
    );
\i__carry_i_10__2\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"9009"
    )
        port map (
      I0 => \reduced_reg_reg[1]_8\(12),
      I1 => \modulating_signal_in_clock_cycles_1_reg__0\(12),
      I2 => \reduced_reg_reg[1]_8\(13),
      I3 => \modulating_signal_in_clock_cycles_1_reg__0\(13),
      O => \i__carry_i_10__2_n_0\
    );
\i__carry_i_10__3\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"9009"
    )
        port map (
      I0 => \reduced_reg_reg[1]_8\(12),
      I1 => P(12),
      I2 => \reduced_reg_reg[1]_8\(13),
      I3 => P(13),
      O => \reduced_reg_reg[1][14]_0\(6)
    );
\i__carry_i_10__4\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"9009"
    )
        port map (
      I0 => \reduced_reg_reg[1]_8\(12),
      I1 => \AND_out10_carry__0_0\(12),
      I2 => \reduced_reg_reg[1]_8\(13),
      I3 => \AND_out10_carry__0_0\(13),
      O => \reduced_reg_reg[1][14]_2\(6)
    );
\i__carry_i_11__2\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"9009"
    )
        port map (
      I0 => \reduced_reg_reg[1]_8\(10),
      I1 => \modulating_signal_in_clock_cycles_1_reg__0\(10),
      I2 => \reduced_reg_reg[1]_8\(11),
      I3 => \modulating_signal_in_clock_cycles_1_reg__0\(11),
      O => \i__carry_i_11__2_n_0\
    );
\i__carry_i_11__3\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"9009"
    )
        port map (
      I0 => \reduced_reg_reg[1]_8\(10),
      I1 => P(10),
      I2 => \reduced_reg_reg[1]_8\(11),
      I3 => P(11),
      O => \reduced_reg_reg[1][14]_0\(5)
    );
\i__carry_i_11__4\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"9009"
    )
        port map (
      I0 => \reduced_reg_reg[1]_8\(10),
      I1 => \AND_out10_carry__0_0\(10),
      I2 => \reduced_reg_reg[1]_8\(11),
      I3 => \AND_out10_carry__0_0\(11),
      O => \reduced_reg_reg[1][14]_2\(5)
    );
\i__carry_i_12__2\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"9009"
    )
        port map (
      I0 => \reduced_reg_reg[1]_8\(8),
      I1 => \modulating_signal_in_clock_cycles_1_reg__0\(8),
      I2 => \reduced_reg_reg[1]_8\(9),
      I3 => \modulating_signal_in_clock_cycles_1_reg__0\(9),
      O => \i__carry_i_12__2_n_0\
    );
\i__carry_i_12__3\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"9009"
    )
        port map (
      I0 => \reduced_reg_reg[1]_8\(8),
      I1 => P(8),
      I2 => \reduced_reg_reg[1]_8\(9),
      I3 => P(9),
      O => \reduced_reg_reg[1][14]_0\(4)
    );
\i__carry_i_12__4\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"9009"
    )
        port map (
      I0 => \reduced_reg_reg[1]_8\(8),
      I1 => \AND_out10_carry__0_0\(8),
      I2 => \reduced_reg_reg[1]_8\(9),
      I3 => \AND_out10_carry__0_0\(9),
      O => \reduced_reg_reg[1][14]_2\(4)
    );
\i__carry_i_13__2\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"9009"
    )
        port map (
      I0 => \reduced_reg_reg[1]_8\(6),
      I1 => \modulating_signal_in_clock_cycles_1_reg__0\(6),
      I2 => \reduced_reg_reg[1]_8\(7),
      I3 => \modulating_signal_in_clock_cycles_1_reg__0\(7),
      O => \i__carry_i_13__2_n_0\
    );
\i__carry_i_13__3\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"9009"
    )
        port map (
      I0 => \reduced_reg_reg[1]_8\(6),
      I1 => P(6),
      I2 => \reduced_reg_reg[1]_8\(7),
      I3 => P(7),
      O => \reduced_reg_reg[1][14]_0\(3)
    );
\i__carry_i_13__4\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"9009"
    )
        port map (
      I0 => \reduced_reg_reg[1]_8\(6),
      I1 => \AND_out10_carry__0_0\(6),
      I2 => \reduced_reg_reg[1]_8\(7),
      I3 => \AND_out10_carry__0_0\(7),
      O => \reduced_reg_reg[1][14]_2\(3)
    );
\i__carry_i_14__2\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"9009"
    )
        port map (
      I0 => \reduced_reg_reg[1]_8\(4),
      I1 => \modulating_signal_in_clock_cycles_1_reg__0\(4),
      I2 => \reduced_reg_reg[1]_8\(5),
      I3 => \modulating_signal_in_clock_cycles_1_reg__0\(5),
      O => \i__carry_i_14__2_n_0\
    );
\i__carry_i_14__3\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"9009"
    )
        port map (
      I0 => \reduced_reg_reg[1]_8\(4),
      I1 => P(4),
      I2 => \reduced_reg_reg[1]_8\(5),
      I3 => P(5),
      O => \reduced_reg_reg[1][14]_0\(2)
    );
\i__carry_i_14__4\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"9009"
    )
        port map (
      I0 => \reduced_reg_reg[1]_8\(4),
      I1 => \AND_out10_carry__0_0\(4),
      I2 => \reduced_reg_reg[1]_8\(5),
      I3 => \AND_out10_carry__0_0\(5),
      O => \reduced_reg_reg[1][14]_2\(2)
    );
\i__carry_i_15\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"9009"
    )
        port map (
      I0 => \reduced_reg_reg[1]_8\(2),
      I1 => \modulating_signal_in_clock_cycles_1_reg__0\(2),
      I2 => \reduced_reg_reg[1]_8\(3),
      I3 => \modulating_signal_in_clock_cycles_1_reg__0\(3),
      O => \i__carry_i_15_n_0\
    );
\i__carry_i_15__0\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"9009"
    )
        port map (
      I0 => \reduced_reg_reg[1]_8\(2),
      I1 => P(2),
      I2 => \reduced_reg_reg[1]_8\(3),
      I3 => P(3),
      O => \reduced_reg_reg[1][14]_0\(1)
    );
\i__carry_i_15__1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"9009"
    )
        port map (
      I0 => \reduced_reg_reg[1]_8\(2),
      I1 => \AND_out10_carry__0_0\(2),
      I2 => \reduced_reg_reg[1]_8\(3),
      I3 => \AND_out10_carry__0_0\(3),
      O => \reduced_reg_reg[1][14]_2\(1)
    );
\i__carry_i_16\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"9009"
    )
        port map (
      I0 => \reduced_reg_reg[1]_8\(0),
      I1 => \modulating_signal_in_clock_cycles_1_reg__0\(0),
      I2 => \reduced_reg_reg[1]_8\(1),
      I3 => \modulating_signal_in_clock_cycles_1_reg__0\(1),
      O => \i__carry_i_16_n_0\
    );
\i__carry_i_16__0\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"9009"
    )
        port map (
      I0 => \reduced_reg_reg[1]_8\(0),
      I1 => P(0),
      I2 => \reduced_reg_reg[1]_8\(1),
      I3 => P(1),
      O => \reduced_reg_reg[1][14]_0\(0)
    );
\i__carry_i_16__1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"9009"
    )
        port map (
      I0 => \reduced_reg_reg[1]_8\(0),
      I1 => \AND_out10_carry__0_0\(0),
      I2 => \reduced_reg_reg[1]_8\(1),
      I3 => \AND_out10_carry__0_0\(1),
      O => \reduced_reg_reg[1][14]_2\(0)
    );
\i__carry_i_1__2\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"2F02"
    )
        port map (
      I0 => \reduced_reg_reg[1]_8\(14),
      I1 => \modulating_signal_in_clock_cycles_1_reg__0\(14),
      I2 => \modulating_signal_in_clock_cycles_1_reg__0\(15),
      I3 => \reduced_reg_reg[1]_8\(15),
      O => \i__carry_i_1__2_n_0\
    );
\i__carry_i_1__3\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"2F02"
    )
        port map (
      I0 => \reduced_reg_reg[1]_8\(14),
      I1 => P(14),
      I2 => P(15),
      I3 => \reduced_reg_reg[1]_8\(15),
      O => \reduced_reg_reg[1][14]_1\(7)
    );
\i__carry_i_1__4\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"2F02"
    )
        port map (
      I0 => \reduced_reg_reg[1]_8\(14),
      I1 => \AND_out10_carry__0_0\(14),
      I2 => \AND_out10_carry__0_0\(15),
      I3 => \reduced_reg_reg[1]_8\(15),
      O => \reduced_reg_reg[1][14]_3\(7)
    );
\i__carry_i_2__2\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"2F02"
    )
        port map (
      I0 => \reduced_reg_reg[1]_8\(12),
      I1 => \modulating_signal_in_clock_cycles_1_reg__0\(12),
      I2 => \modulating_signal_in_clock_cycles_1_reg__0\(13),
      I3 => \reduced_reg_reg[1]_8\(13),
      O => \i__carry_i_2__2_n_0\
    );
\i__carry_i_2__3\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"2F02"
    )
        port map (
      I0 => \reduced_reg_reg[1]_8\(12),
      I1 => P(12),
      I2 => P(13),
      I3 => \reduced_reg_reg[1]_8\(13),
      O => \reduced_reg_reg[1][14]_1\(6)
    );
\i__carry_i_2__4\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"2F02"
    )
        port map (
      I0 => \reduced_reg_reg[1]_8\(12),
      I1 => \AND_out10_carry__0_0\(12),
      I2 => \AND_out10_carry__0_0\(13),
      I3 => \reduced_reg_reg[1]_8\(13),
      O => \reduced_reg_reg[1][14]_3\(6)
    );
\i__carry_i_3__2\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"2F02"
    )
        port map (
      I0 => \reduced_reg_reg[1]_8\(10),
      I1 => \modulating_signal_in_clock_cycles_1_reg__0\(10),
      I2 => \modulating_signal_in_clock_cycles_1_reg__0\(11),
      I3 => \reduced_reg_reg[1]_8\(11),
      O => \i__carry_i_3__2_n_0\
    );
\i__carry_i_3__3\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"2F02"
    )
        port map (
      I0 => \reduced_reg_reg[1]_8\(10),
      I1 => P(10),
      I2 => P(11),
      I3 => \reduced_reg_reg[1]_8\(11),
      O => \reduced_reg_reg[1][14]_1\(5)
    );
\i__carry_i_3__4\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"2F02"
    )
        port map (
      I0 => \reduced_reg_reg[1]_8\(10),
      I1 => \AND_out10_carry__0_0\(10),
      I2 => \AND_out10_carry__0_0\(11),
      I3 => \reduced_reg_reg[1]_8\(11),
      O => \reduced_reg_reg[1][14]_3\(5)
    );
\i__carry_i_4__2\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"2F02"
    )
        port map (
      I0 => \reduced_reg_reg[1]_8\(8),
      I1 => \modulating_signal_in_clock_cycles_1_reg__0\(8),
      I2 => \modulating_signal_in_clock_cycles_1_reg__0\(9),
      I3 => \reduced_reg_reg[1]_8\(9),
      O => \i__carry_i_4__2_n_0\
    );
\i__carry_i_4__3\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"2F02"
    )
        port map (
      I0 => \reduced_reg_reg[1]_8\(8),
      I1 => P(8),
      I2 => P(9),
      I3 => \reduced_reg_reg[1]_8\(9),
      O => \reduced_reg_reg[1][14]_1\(4)
    );
\i__carry_i_4__4\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"2F02"
    )
        port map (
      I0 => \reduced_reg_reg[1]_8\(8),
      I1 => \AND_out10_carry__0_0\(8),
      I2 => \AND_out10_carry__0_0\(9),
      I3 => \reduced_reg_reg[1]_8\(9),
      O => \reduced_reg_reg[1][14]_3\(4)
    );
\i__carry_i_5__2\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"2F02"
    )
        port map (
      I0 => \reduced_reg_reg[1]_8\(6),
      I1 => \modulating_signal_in_clock_cycles_1_reg__0\(6),
      I2 => \modulating_signal_in_clock_cycles_1_reg__0\(7),
      I3 => \reduced_reg_reg[1]_8\(7),
      O => \i__carry_i_5__2_n_0\
    );
\i__carry_i_5__3\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"2F02"
    )
        port map (
      I0 => \reduced_reg_reg[1]_8\(6),
      I1 => P(6),
      I2 => P(7),
      I3 => \reduced_reg_reg[1]_8\(7),
      O => \reduced_reg_reg[1][14]_1\(3)
    );
\i__carry_i_5__4\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"2F02"
    )
        port map (
      I0 => \reduced_reg_reg[1]_8\(6),
      I1 => \AND_out10_carry__0_0\(6),
      I2 => \AND_out10_carry__0_0\(7),
      I3 => \reduced_reg_reg[1]_8\(7),
      O => \reduced_reg_reg[1][14]_3\(3)
    );
\i__carry_i_6__2\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"2F02"
    )
        port map (
      I0 => \reduced_reg_reg[1]_8\(4),
      I1 => \modulating_signal_in_clock_cycles_1_reg__0\(4),
      I2 => \modulating_signal_in_clock_cycles_1_reg__0\(5),
      I3 => \reduced_reg_reg[1]_8\(5),
      O => \i__carry_i_6__2_n_0\
    );
\i__carry_i_6__3\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"2F02"
    )
        port map (
      I0 => \reduced_reg_reg[1]_8\(4),
      I1 => P(4),
      I2 => P(5),
      I3 => \reduced_reg_reg[1]_8\(5),
      O => \reduced_reg_reg[1][14]_1\(2)
    );
\i__carry_i_6__4\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"2F02"
    )
        port map (
      I0 => \reduced_reg_reg[1]_8\(4),
      I1 => \AND_out10_carry__0_0\(4),
      I2 => \AND_out10_carry__0_0\(5),
      I3 => \reduced_reg_reg[1]_8\(5),
      O => \reduced_reg_reg[1][14]_3\(2)
    );
\i__carry_i_7__2\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"2F02"
    )
        port map (
      I0 => \reduced_reg_reg[1]_8\(2),
      I1 => \modulating_signal_in_clock_cycles_1_reg__0\(2),
      I2 => \modulating_signal_in_clock_cycles_1_reg__0\(3),
      I3 => \reduced_reg_reg[1]_8\(3),
      O => \i__carry_i_7__2_n_0\
    );
\i__carry_i_7__3\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"2F02"
    )
        port map (
      I0 => \reduced_reg_reg[1]_8\(2),
      I1 => P(2),
      I2 => P(3),
      I3 => \reduced_reg_reg[1]_8\(3),
      O => \reduced_reg_reg[1][14]_1\(1)
    );
\i__carry_i_7__4\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"2F02"
    )
        port map (
      I0 => \reduced_reg_reg[1]_8\(2),
      I1 => \AND_out10_carry__0_0\(2),
      I2 => \AND_out10_carry__0_0\(3),
      I3 => \reduced_reg_reg[1]_8\(3),
      O => \reduced_reg_reg[1][14]_3\(1)
    );
\i__carry_i_8__2\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"2F02"
    )
        port map (
      I0 => \reduced_reg_reg[1]_8\(0),
      I1 => \modulating_signal_in_clock_cycles_1_reg__0\(0),
      I2 => \modulating_signal_in_clock_cycles_1_reg__0\(1),
      I3 => \reduced_reg_reg[1]_8\(1),
      O => \i__carry_i_8__2_n_0\
    );
\i__carry_i_8__3\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"2F02"
    )
        port map (
      I0 => \reduced_reg_reg[1]_8\(0),
      I1 => P(0),
      I2 => P(1),
      I3 => \reduced_reg_reg[1]_8\(1),
      O => \reduced_reg_reg[1][14]_1\(0)
    );
\i__carry_i_8__4\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"2F02"
    )
        port map (
      I0 => \reduced_reg_reg[1]_8\(0),
      I1 => \AND_out10_carry__0_0\(0),
      I2 => \AND_out10_carry__0_0\(1),
      I3 => \reduced_reg_reg[1]_8\(1),
      O => \reduced_reg_reg[1][14]_3\(0)
    );
\i__carry_i_9__2\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"9009"
    )
        port map (
      I0 => \reduced_reg_reg[1]_8\(14),
      I1 => \modulating_signal_in_clock_cycles_1_reg__0\(14),
      I2 => \reduced_reg_reg[1]_8\(15),
      I3 => \modulating_signal_in_clock_cycles_1_reg__0\(15),
      O => \i__carry_i_9__2_n_0\
    );
\i__carry_i_9__3\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"9009"
    )
        port map (
      I0 => \reduced_reg_reg[1]_8\(14),
      I1 => P(14),
      I2 => \reduced_reg_reg[1]_8\(15),
      I3 => P(15),
      O => \reduced_reg_reg[1][14]_0\(7)
    );
\i__carry_i_9__4\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"9009"
    )
        port map (
      I0 => \reduced_reg_reg[1]_8\(14),
      I1 => \AND_out10_carry__0_0\(14),
      I2 => \reduced_reg_reg[1]_8\(15),
      I3 => \AND_out10_carry__0_0\(15),
      O => \reduced_reg_reg[1][14]_2\(7)
    );
modulating_signal_in_clock_cycles_1_reg: unisim.vcomponents.DSP48E2
    generic map(
      ACASCREG => 1,
      ADREG => 1,
      ALUMODEREG => 0,
      AMULTSEL => "A",
      AREG => 1,
      AUTORESET_PATDET => "NO_RESET",
      AUTORESET_PRIORITY => "RESET",
      A_INPUT => "DIRECT",
      BCASCREG => 1,
      BMULTSEL => "B",
      BREG => 1,
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
      A(29 downto 20) => B"0000000000",
      A(19 downto 0) => maximum_counter_value_1(19 downto 0),
      ACIN(29 downto 0) => B"000000000000000000000000000000",
      ACOUT(29 downto 0) => NLW_modulating_signal_in_clock_cycles_1_reg_ACOUT_UNCONNECTED(29 downto 0),
      ALUMODE(3 downto 0) => B"0000",
      B(17) => B(13),
      B(16) => B(13),
      B(15) => B(13),
      B(14) => B(13),
      B(13 downto 0) => B(13 downto 0),
      BCIN(17 downto 0) => B"000000000000000000",
      BCOUT(17 downto 0) => NLW_modulating_signal_in_clock_cycles_1_reg_BCOUT_UNCONNECTED(17 downto 0),
      C(47 downto 0) => B"000000000000000000000000000000000000000000000000",
      CARRYCASCIN => '0',
      CARRYCASCOUT => NLW_modulating_signal_in_clock_cycles_1_reg_CARRYCASCOUT_UNCONNECTED,
      CARRYIN => '0',
      CARRYINSEL(2 downto 0) => B"000",
      CARRYOUT(3 downto 0) => NLW_modulating_signal_in_clock_cycles_1_reg_CARRYOUT_UNCONNECTED(3 downto 0),
      CEA1 => '0',
      CEA2 => CEP,
      CEAD => '0',
      CEALUMODE => '0',
      CEB1 => '0',
      CEB2 => CEP,
      CEC => '0',
      CECARRYIN => '0',
      CECTRL => '0',
      CED => '0',
      CEINMODE => '0',
      CEM => '0',
      CEP => CEP,
      CLK => IPCORE_CLK,
      D(26 downto 0) => B"000000000000000000000000000",
      INMODE(4 downto 0) => B"00000",
      MULTSIGNIN => '0',
      MULTSIGNOUT => NLW_modulating_signal_in_clock_cycles_1_reg_MULTSIGNOUT_UNCONNECTED,
      OPMODE(8 downto 0) => B"000000101",
      OVERFLOW => NLW_modulating_signal_in_clock_cycles_1_reg_OVERFLOW_UNCONNECTED,
      P(47 downto 33) => NLW_modulating_signal_in_clock_cycles_1_reg_P_UNCONNECTED(47 downto 33),
      P(32 downto 12) => \modulating_signal_in_clock_cycles_1_reg__0\(20 downto 0),
      P(11) => modulating_signal_in_clock_cycles_1_reg_n_94,
      P(10) => modulating_signal_in_clock_cycles_1_reg_n_95,
      P(9) => modulating_signal_in_clock_cycles_1_reg_n_96,
      P(8) => modulating_signal_in_clock_cycles_1_reg_n_97,
      P(7) => modulating_signal_in_clock_cycles_1_reg_n_98,
      P(6) => modulating_signal_in_clock_cycles_1_reg_n_99,
      P(5) => modulating_signal_in_clock_cycles_1_reg_n_100,
      P(4) => modulating_signal_in_clock_cycles_1_reg_n_101,
      P(3) => modulating_signal_in_clock_cycles_1_reg_n_102,
      P(2) => modulating_signal_in_clock_cycles_1_reg_n_103,
      P(1) => modulating_signal_in_clock_cycles_1_reg_n_104,
      P(0) => modulating_signal_in_clock_cycles_1_reg_n_105,
      PATTERNBDETECT => NLW_modulating_signal_in_clock_cycles_1_reg_PATTERNBDETECT_UNCONNECTED,
      PATTERNDETECT => NLW_modulating_signal_in_clock_cycles_1_reg_PATTERNDETECT_UNCONNECTED,
      PCIN(47 downto 0) => B"000000000000000000000000000000000000000000000000",
      PCOUT(47 downto 0) => NLW_modulating_signal_in_clock_cycles_1_reg_PCOUT_UNCONNECTED(47 downto 0),
      RSTA => RSTP,
      RSTALLCARRYIN => '0',
      RSTALUMODE => '0',
      RSTB => RSTP,
      RSTC => '0',
      RSTCTRL => '0',
      RSTD => '0',
      RSTINMODE => '0',
      RSTM => '0',
      RSTP => RSTP,
      UNDERFLOW => NLW_modulating_signal_in_clock_cycles_1_reg_UNDERFLOW_UNCONNECTED,
      XOROUT(7 downto 0) => NLW_modulating_signal_in_clock_cycles_1_reg_XOROUT_UNCONNECTED(7 downto 0)
    );
\reduced_reg_1_reg[0][0]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => Counter_Ctrl_out3(0),
      Q => \reduced_reg_1_reg[0]_7\(0),
      R => RSTP
    );
\reduced_reg_1_reg[0][10]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => Counter_Ctrl_out3(10),
      Q => \reduced_reg_1_reg[0]_7\(10),
      R => RSTP
    );
\reduced_reg_1_reg[0][11]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => Counter_Ctrl_out3(11),
      Q => \reduced_reg_1_reg[0]_7\(11),
      R => RSTP
    );
\reduced_reg_1_reg[0][12]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => Counter_Ctrl_out3(12),
      Q => \reduced_reg_1_reg[0]_7\(12),
      R => RSTP
    );
\reduced_reg_1_reg[0][13]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => Counter_Ctrl_out3(13),
      Q => \reduced_reg_1_reg[0]_7\(13),
      R => RSTP
    );
\reduced_reg_1_reg[0][14]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => Counter_Ctrl_out3(14),
      Q => \reduced_reg_1_reg[0]_7\(14),
      R => RSTP
    );
\reduced_reg_1_reg[0][15]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => Counter_Ctrl_out3(15),
      Q => \reduced_reg_1_reg[0]_7\(15),
      R => RSTP
    );
\reduced_reg_1_reg[0][16]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => Counter_Ctrl_out3(16),
      Q => \reduced_reg_1_reg[0]_7\(16),
      R => RSTP
    );
\reduced_reg_1_reg[0][17]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => Counter_Ctrl_out3(17),
      Q => \reduced_reg_1_reg[0]_7\(17),
      R => RSTP
    );
\reduced_reg_1_reg[0][18]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => Counter_Ctrl_out3(18),
      Q => \reduced_reg_1_reg[0]_7\(18),
      R => RSTP
    );
\reduced_reg_1_reg[0][19]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => Counter_Ctrl_out3(19),
      Q => \reduced_reg_1_reg[0]_7\(19),
      R => RSTP
    );
\reduced_reg_1_reg[0][1]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => Counter_Ctrl_out3(1),
      Q => \reduced_reg_1_reg[0]_7\(1),
      R => RSTP
    );
\reduced_reg_1_reg[0][20]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => Counter_Ctrl_out3(20),
      Q => \reduced_reg_1_reg[0]_7\(20),
      R => RSTP
    );
\reduced_reg_1_reg[0][2]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => Counter_Ctrl_out3(2),
      Q => \reduced_reg_1_reg[0]_7\(2),
      R => RSTP
    );
\reduced_reg_1_reg[0][3]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => Counter_Ctrl_out3(3),
      Q => \reduced_reg_1_reg[0]_7\(3),
      R => RSTP
    );
\reduced_reg_1_reg[0][4]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => Counter_Ctrl_out3(4),
      Q => \reduced_reg_1_reg[0]_7\(4),
      R => RSTP
    );
\reduced_reg_1_reg[0][5]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => Counter_Ctrl_out3(5),
      Q => \reduced_reg_1_reg[0]_7\(5),
      R => RSTP
    );
\reduced_reg_1_reg[0][6]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => Counter_Ctrl_out3(6),
      Q => \reduced_reg_1_reg[0]_7\(6),
      R => RSTP
    );
\reduced_reg_1_reg[0][7]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => Counter_Ctrl_out3(7),
      Q => \reduced_reg_1_reg[0]_7\(7),
      R => RSTP
    );
\reduced_reg_1_reg[0][8]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => Counter_Ctrl_out3(8),
      Q => \reduced_reg_1_reg[0]_7\(8),
      R => RSTP
    );
\reduced_reg_1_reg[0][9]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => Counter_Ctrl_out3(9),
      Q => \reduced_reg_1_reg[0]_7\(9),
      R => RSTP
    );
\reduced_reg_1_reg[1][0]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \reduced_reg_1_reg[0]_7\(0),
      Q => \^reduced_reg_1_reg[1]_9\(0),
      R => RSTP
    );
\reduced_reg_1_reg[1][10]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \reduced_reg_1_reg[0]_7\(10),
      Q => \^reduced_reg_1_reg[1]_9\(10),
      R => RSTP
    );
\reduced_reg_1_reg[1][11]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \reduced_reg_1_reg[0]_7\(11),
      Q => \^reduced_reg_1_reg[1]_9\(11),
      R => RSTP
    );
\reduced_reg_1_reg[1][12]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \reduced_reg_1_reg[0]_7\(12),
      Q => \^reduced_reg_1_reg[1]_9\(12),
      R => RSTP
    );
\reduced_reg_1_reg[1][13]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \reduced_reg_1_reg[0]_7\(13),
      Q => \^reduced_reg_1_reg[1]_9\(13),
      R => RSTP
    );
\reduced_reg_1_reg[1][14]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \reduced_reg_1_reg[0]_7\(14),
      Q => \^reduced_reg_1_reg[1]_9\(14),
      R => RSTP
    );
\reduced_reg_1_reg[1][15]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \reduced_reg_1_reg[0]_7\(15),
      Q => \^reduced_reg_1_reg[1]_9\(15),
      R => RSTP
    );
\reduced_reg_1_reg[1][16]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \reduced_reg_1_reg[0]_7\(16),
      Q => \^reduced_reg_1_reg[1]_9\(16),
      R => RSTP
    );
\reduced_reg_1_reg[1][17]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \reduced_reg_1_reg[0]_7\(17),
      Q => \^reduced_reg_1_reg[1]_9\(17),
      R => RSTP
    );
\reduced_reg_1_reg[1][18]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \reduced_reg_1_reg[0]_7\(18),
      Q => \^reduced_reg_1_reg[1]_9\(18),
      R => RSTP
    );
\reduced_reg_1_reg[1][19]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \reduced_reg_1_reg[0]_7\(19),
      Q => \^reduced_reg_1_reg[1]_9\(19),
      R => RSTP
    );
\reduced_reg_1_reg[1][1]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \reduced_reg_1_reg[0]_7\(1),
      Q => \^reduced_reg_1_reg[1]_9\(1),
      R => RSTP
    );
\reduced_reg_1_reg[1][20]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \reduced_reg_1_reg[0]_7\(20),
      Q => \^reduced_reg_1_reg[1]_9\(20),
      R => RSTP
    );
\reduced_reg_1_reg[1][2]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \reduced_reg_1_reg[0]_7\(2),
      Q => \^reduced_reg_1_reg[1]_9\(2),
      R => RSTP
    );
\reduced_reg_1_reg[1][3]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \reduced_reg_1_reg[0]_7\(3),
      Q => \^reduced_reg_1_reg[1]_9\(3),
      R => RSTP
    );
\reduced_reg_1_reg[1][4]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \reduced_reg_1_reg[0]_7\(4),
      Q => \^reduced_reg_1_reg[1]_9\(4),
      R => RSTP
    );
\reduced_reg_1_reg[1][5]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \reduced_reg_1_reg[0]_7\(5),
      Q => \^reduced_reg_1_reg[1]_9\(5),
      R => RSTP
    );
\reduced_reg_1_reg[1][6]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \reduced_reg_1_reg[0]_7\(6),
      Q => \^reduced_reg_1_reg[1]_9\(6),
      R => RSTP
    );
\reduced_reg_1_reg[1][7]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \reduced_reg_1_reg[0]_7\(7),
      Q => \^reduced_reg_1_reg[1]_9\(7),
      R => RSTP
    );
\reduced_reg_1_reg[1][8]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \reduced_reg_1_reg[0]_7\(8),
      Q => \^reduced_reg_1_reg[1]_9\(8),
      R => RSTP
    );
\reduced_reg_1_reg[1][9]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \reduced_reg_1_reg[0]_7\(9),
      Q => \^reduced_reg_1_reg[1]_9\(9),
      R => RSTP
    );
\reduced_reg_reg[0][0]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => HDL_Counter2_count_reg(0),
      Q => \reduced_reg_reg[0]_6\(0),
      R => RSTP
    );
\reduced_reg_reg[0][10]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => HDL_Counter2_count_reg(10),
      Q => \reduced_reg_reg[0]_6\(10),
      R => RSTP
    );
\reduced_reg_reg[0][11]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => HDL_Counter2_count_reg(11),
      Q => \reduced_reg_reg[0]_6\(11),
      R => RSTP
    );
\reduced_reg_reg[0][12]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => HDL_Counter2_count_reg(12),
      Q => \reduced_reg_reg[0]_6\(12),
      R => RSTP
    );
\reduced_reg_reg[0][13]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => HDL_Counter2_count_reg(13),
      Q => \reduced_reg_reg[0]_6\(13),
      R => RSTP
    );
\reduced_reg_reg[0][14]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => HDL_Counter2_count_reg(14),
      Q => \reduced_reg_reg[0]_6\(14),
      R => RSTP
    );
\reduced_reg_reg[0][15]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => HDL_Counter2_count_reg(15),
      Q => \reduced_reg_reg[0]_6\(15),
      R => RSTP
    );
\reduced_reg_reg[0][16]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => HDL_Counter2_count_reg(16),
      Q => \reduced_reg_reg[0]_6\(16),
      R => RSTP
    );
\reduced_reg_reg[0][17]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => HDL_Counter2_count_reg(17),
      Q => \reduced_reg_reg[0]_6\(17),
      R => RSTP
    );
\reduced_reg_reg[0][18]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => HDL_Counter2_count_reg(18),
      Q => \reduced_reg_reg[0]_6\(18),
      R => RSTP
    );
\reduced_reg_reg[0][19]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => HDL_Counter2_count_reg(19),
      Q => \reduced_reg_reg[0]_6\(19),
      R => RSTP
    );
\reduced_reg_reg[0][1]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => HDL_Counter2_count_reg(1),
      Q => \reduced_reg_reg[0]_6\(1),
      R => RSTP
    );
\reduced_reg_reg[0][2]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => HDL_Counter2_count_reg(2),
      Q => \reduced_reg_reg[0]_6\(2),
      R => RSTP
    );
\reduced_reg_reg[0][3]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => HDL_Counter2_count_reg(3),
      Q => \reduced_reg_reg[0]_6\(3),
      R => RSTP
    );
\reduced_reg_reg[0][4]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => HDL_Counter2_count_reg(4),
      Q => \reduced_reg_reg[0]_6\(4),
      R => RSTP
    );
\reduced_reg_reg[0][5]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => HDL_Counter2_count_reg(5),
      Q => \reduced_reg_reg[0]_6\(5),
      R => RSTP
    );
\reduced_reg_reg[0][6]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => HDL_Counter2_count_reg(6),
      Q => \reduced_reg_reg[0]_6\(6),
      R => RSTP
    );
\reduced_reg_reg[0][7]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => HDL_Counter2_count_reg(7),
      Q => \reduced_reg_reg[0]_6\(7),
      R => RSTP
    );
\reduced_reg_reg[0][8]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => HDL_Counter2_count_reg(8),
      Q => \reduced_reg_reg[0]_6\(8),
      R => RSTP
    );
\reduced_reg_reg[0][9]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => HDL_Counter2_count_reg(9),
      Q => \reduced_reg_reg[0]_6\(9),
      R => RSTP
    );
\reduced_reg_reg[1][0]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \reduced_reg_reg[0]_6\(0),
      Q => \reduced_reg_reg[1]_8\(0),
      R => RSTP
    );
\reduced_reg_reg[1][10]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \reduced_reg_reg[0]_6\(10),
      Q => \reduced_reg_reg[1]_8\(10),
      R => RSTP
    );
\reduced_reg_reg[1][11]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \reduced_reg_reg[0]_6\(11),
      Q => \reduced_reg_reg[1]_8\(11),
      R => RSTP
    );
\reduced_reg_reg[1][12]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \reduced_reg_reg[0]_6\(12),
      Q => \reduced_reg_reg[1]_8\(12),
      R => RSTP
    );
\reduced_reg_reg[1][13]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \reduced_reg_reg[0]_6\(13),
      Q => \reduced_reg_reg[1]_8\(13),
      R => RSTP
    );
\reduced_reg_reg[1][14]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \reduced_reg_reg[0]_6\(14),
      Q => \reduced_reg_reg[1]_8\(14),
      R => RSTP
    );
\reduced_reg_reg[1][15]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \reduced_reg_reg[0]_6\(15),
      Q => \reduced_reg_reg[1]_8\(15),
      R => RSTP
    );
\reduced_reg_reg[1][16]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \reduced_reg_reg[0]_6\(16),
      Q => \reduced_reg_reg[1]_8\(16),
      R => RSTP
    );
\reduced_reg_reg[1][17]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \reduced_reg_reg[0]_6\(17),
      Q => \reduced_reg_reg[1]_8\(17),
      R => RSTP
    );
\reduced_reg_reg[1][18]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \reduced_reg_reg[0]_6\(18),
      Q => \reduced_reg_reg[1]_8\(18),
      R => RSTP
    );
\reduced_reg_reg[1][19]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \reduced_reg_reg[0]_6\(19),
      Q => \reduced_reg_reg[1]_8\(19),
      R => RSTP
    );
\reduced_reg_reg[1][1]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \reduced_reg_reg[0]_6\(1),
      Q => \reduced_reg_reg[1]_8\(1),
      R => RSTP
    );
\reduced_reg_reg[1][2]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \reduced_reg_reg[0]_6\(2),
      Q => \reduced_reg_reg[1]_8\(2),
      R => RSTP
    );
\reduced_reg_reg[1][3]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \reduced_reg_reg[0]_6\(3),
      Q => \reduced_reg_reg[1]_8\(3),
      R => RSTP
    );
\reduced_reg_reg[1][4]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \reduced_reg_reg[0]_6\(4),
      Q => \reduced_reg_reg[1]_8\(4),
      R => RSTP
    );
\reduced_reg_reg[1][5]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \reduced_reg_reg[0]_6\(5),
      Q => \reduced_reg_reg[1]_8\(5),
      R => RSTP
    );
\reduced_reg_reg[1][6]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \reduced_reg_reg[0]_6\(6),
      Q => \reduced_reg_reg[1]_8\(6),
      R => RSTP
    );
\reduced_reg_reg[1][7]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \reduced_reg_reg[0]_6\(7),
      Q => \reduced_reg_reg[1]_8\(7),
      R => RSTP
    );
\reduced_reg_reg[1][8]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \reduced_reg_reg[0]_6\(8),
      Q => \reduced_reg_reg[1]_8\(8),
      R => RSTP
    );
\reduced_reg_reg[1][9]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \reduced_reg_reg[0]_6\(9),
      Q => \reduced_reg_reg[1]_8\(9),
      R => RSTP
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity zusys_PWM_SS_3L_ip_0_0_PWM_SS_3L_ip_src_Modulator_b is
  port (
    P : out STD_LOGIC_VECTOR ( 20 downto 0 );
    D : out STD_LOGIC_VECTOR ( 1 downto 0 );
    CEP : in STD_LOGIC;
    IPCORE_CLK : in STD_LOGIC;
    RSTP : in STD_LOGIC;
    B : in STD_LOGIC_VECTOR ( 13 downto 0 );
    maximum_counter_value_1 : in STD_LOGIC_VECTOR ( 19 downto 0 );
    DI : in STD_LOGIC_VECTOR ( 0 to 0 );
    \AND_out10_inferred__0/i__carry__0_0\ : in STD_LOGIC_VECTOR ( 7 downto 0 );
    \AND_out10_inferred__0/i__carry__0_1\ : in STD_LOGIC_VECTOR ( 7 downto 0 );
    \Switch4_out1_1_reg[0]\ : in STD_LOGIC_VECTOR ( 1 downto 0 );
    \Switch4_out1_1_reg[0]_0\ : in STD_LOGIC_VECTOR ( 1 downto 0 );
    \reduced_reg_1_reg[1]_9\ : in STD_LOGIC_VECTOR ( 20 downto 0 )
  );
  attribute ORIG_REF_NAME : string;
  attribute ORIG_REF_NAME of zusys_PWM_SS_3L_ip_0_0_PWM_SS_3L_ip_src_Modulator_b : entity is "PWM_SS_3L_ip_src_Modulator_b";
end zusys_PWM_SS_3L_ip_0_0_PWM_SS_3L_ip_src_Modulator_b;

architecture STRUCTURE of zusys_PWM_SS_3L_ip_0_0_PWM_SS_3L_ip_src_Modulator_b is
  signal \AND_out10_carry__0_i_2__0_n_0\ : STD_LOGIC;
  signal \AND_out10_carry__0_i_3__0_n_0\ : STD_LOGIC;
  signal \AND_out10_carry__0_i_4__0_n_0\ : STD_LOGIC;
  signal \AND_out10_carry__0_i_5__0_n_0\ : STD_LOGIC;
  signal \AND_out10_carry__0_i_6__0_n_0\ : STD_LOGIC;
  signal \AND_out10_carry__0_n_6\ : STD_LOGIC;
  signal \AND_out10_carry__0_n_7\ : STD_LOGIC;
  signal \AND_out10_carry_i_10__0_n_0\ : STD_LOGIC;
  signal \AND_out10_carry_i_11__0_n_0\ : STD_LOGIC;
  signal \AND_out10_carry_i_12__0_n_0\ : STD_LOGIC;
  signal \AND_out10_carry_i_13__0_n_0\ : STD_LOGIC;
  signal \AND_out10_carry_i_14__0_n_0\ : STD_LOGIC;
  signal \AND_out10_carry_i_15__0_n_0\ : STD_LOGIC;
  signal \AND_out10_carry_i_16__0_n_0\ : STD_LOGIC;
  signal \AND_out10_carry_i_1__0_n_0\ : STD_LOGIC;
  signal \AND_out10_carry_i_2__0_n_0\ : STD_LOGIC;
  signal \AND_out10_carry_i_3__0_n_0\ : STD_LOGIC;
  signal \AND_out10_carry_i_4__0_n_0\ : STD_LOGIC;
  signal \AND_out10_carry_i_5__0_n_0\ : STD_LOGIC;
  signal \AND_out10_carry_i_6__0_n_0\ : STD_LOGIC;
  signal \AND_out10_carry_i_7__0_n_0\ : STD_LOGIC;
  signal \AND_out10_carry_i_8__0_n_0\ : STD_LOGIC;
  signal \AND_out10_carry_i_9__0_n_0\ : STD_LOGIC;
  signal AND_out10_carry_n_0 : STD_LOGIC;
  signal AND_out10_carry_n_1 : STD_LOGIC;
  signal AND_out10_carry_n_2 : STD_LOGIC;
  signal AND_out10_carry_n_3 : STD_LOGIC;
  signal AND_out10_carry_n_4 : STD_LOGIC;
  signal AND_out10_carry_n_5 : STD_LOGIC;
  signal AND_out10_carry_n_6 : STD_LOGIC;
  signal AND_out10_carry_n_7 : STD_LOGIC;
  signal \AND_out10_inferred__0/i__carry__0_n_6\ : STD_LOGIC;
  signal \AND_out10_inferred__0/i__carry__0_n_7\ : STD_LOGIC;
  signal \AND_out10_inferred__0/i__carry_n_0\ : STD_LOGIC;
  signal \AND_out10_inferred__0/i__carry_n_1\ : STD_LOGIC;
  signal \AND_out10_inferred__0/i__carry_n_2\ : STD_LOGIC;
  signal \AND_out10_inferred__0/i__carry_n_3\ : STD_LOGIC;
  signal \AND_out10_inferred__0/i__carry_n_4\ : STD_LOGIC;
  signal \AND_out10_inferred__0/i__carry_n_5\ : STD_LOGIC;
  signal \AND_out10_inferred__0/i__carry_n_6\ : STD_LOGIC;
  signal \AND_out10_inferred__0/i__carry_n_7\ : STD_LOGIC;
  signal \^p\ : STD_LOGIC_VECTOR ( 20 downto 0 );
  signal Relational_Operator1_relop1 : STD_LOGIC;
  signal Relational_Operator_relop1 : STD_LOGIC;
  signal \i__carry__0_i_3__0_n_0\ : STD_LOGIC;
  signal modulating_signal_in_clock_cycles_1_reg_n_100 : STD_LOGIC;
  signal modulating_signal_in_clock_cycles_1_reg_n_101 : STD_LOGIC;
  signal modulating_signal_in_clock_cycles_1_reg_n_102 : STD_LOGIC;
  signal modulating_signal_in_clock_cycles_1_reg_n_103 : STD_LOGIC;
  signal modulating_signal_in_clock_cycles_1_reg_n_104 : STD_LOGIC;
  signal modulating_signal_in_clock_cycles_1_reg_n_105 : STD_LOGIC;
  signal modulating_signal_in_clock_cycles_1_reg_n_94 : STD_LOGIC;
  signal modulating_signal_in_clock_cycles_1_reg_n_95 : STD_LOGIC;
  signal modulating_signal_in_clock_cycles_1_reg_n_96 : STD_LOGIC;
  signal modulating_signal_in_clock_cycles_1_reg_n_97 : STD_LOGIC;
  signal modulating_signal_in_clock_cycles_1_reg_n_98 : STD_LOGIC;
  signal modulating_signal_in_clock_cycles_1_reg_n_99 : STD_LOGIC;
  signal NLW_AND_out10_carry_O_UNCONNECTED : STD_LOGIC_VECTOR ( 7 downto 0 );
  signal \NLW_AND_out10_carry__0_CO_UNCONNECTED\ : STD_LOGIC_VECTOR ( 7 downto 3 );
  signal \NLW_AND_out10_carry__0_O_UNCONNECTED\ : STD_LOGIC_VECTOR ( 7 downto 0 );
  signal \NLW_AND_out10_inferred__0/i__carry_O_UNCONNECTED\ : STD_LOGIC_VECTOR ( 7 downto 0 );
  signal \NLW_AND_out10_inferred__0/i__carry__0_CO_UNCONNECTED\ : STD_LOGIC_VECTOR ( 7 downto 3 );
  signal \NLW_AND_out10_inferred__0/i__carry__0_O_UNCONNECTED\ : STD_LOGIC_VECTOR ( 7 downto 0 );
  signal NLW_modulating_signal_in_clock_cycles_1_reg_CARRYCASCOUT_UNCONNECTED : STD_LOGIC;
  signal NLW_modulating_signal_in_clock_cycles_1_reg_MULTSIGNOUT_UNCONNECTED : STD_LOGIC;
  signal NLW_modulating_signal_in_clock_cycles_1_reg_OVERFLOW_UNCONNECTED : STD_LOGIC;
  signal NLW_modulating_signal_in_clock_cycles_1_reg_PATTERNBDETECT_UNCONNECTED : STD_LOGIC;
  signal NLW_modulating_signal_in_clock_cycles_1_reg_PATTERNDETECT_UNCONNECTED : STD_LOGIC;
  signal NLW_modulating_signal_in_clock_cycles_1_reg_UNDERFLOW_UNCONNECTED : STD_LOGIC;
  signal NLW_modulating_signal_in_clock_cycles_1_reg_ACOUT_UNCONNECTED : STD_LOGIC_VECTOR ( 29 downto 0 );
  signal NLW_modulating_signal_in_clock_cycles_1_reg_BCOUT_UNCONNECTED : STD_LOGIC_VECTOR ( 17 downto 0 );
  signal NLW_modulating_signal_in_clock_cycles_1_reg_CARRYOUT_UNCONNECTED : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal NLW_modulating_signal_in_clock_cycles_1_reg_P_UNCONNECTED : STD_LOGIC_VECTOR ( 47 downto 33 );
  signal NLW_modulating_signal_in_clock_cycles_1_reg_PCOUT_UNCONNECTED : STD_LOGIC_VECTOR ( 47 downto 0 );
  signal NLW_modulating_signal_in_clock_cycles_1_reg_XOROUT_UNCONNECTED : STD_LOGIC_VECTOR ( 7 downto 0 );
  attribute COMPARATOR_THRESHOLD : integer;
  attribute COMPARATOR_THRESHOLD of AND_out10_carry : label is 11;
  attribute COMPARATOR_THRESHOLD of \AND_out10_carry__0\ : label is 11;
  attribute COMPARATOR_THRESHOLD of \AND_out10_inferred__0/i__carry\ : label is 11;
  attribute COMPARATOR_THRESHOLD of \AND_out10_inferred__0/i__carry__0\ : label is 11;
  attribute SOFT_HLUTNM : string;
  attribute SOFT_HLUTNM of \Switch4_out1_1[0]_i_1\ : label is "soft_lutpair51";
  attribute SOFT_HLUTNM of \Switch4_out1_1[1]_i_1\ : label is "soft_lutpair51";
  attribute KEEP_HIERARCHY : string;
  attribute KEEP_HIERARCHY of modulating_signal_in_clock_cycles_1_reg : label is "yes";
begin
  P(20 downto 0) <= \^p\(20 downto 0);
AND_out10_carry: unisim.vcomponents.CARRY8
     port map (
      CI => '1',
      CI_TOP => '0',
      CO(7) => AND_out10_carry_n_0,
      CO(6) => AND_out10_carry_n_1,
      CO(5) => AND_out10_carry_n_2,
      CO(4) => AND_out10_carry_n_3,
      CO(3) => AND_out10_carry_n_4,
      CO(2) => AND_out10_carry_n_5,
      CO(1) => AND_out10_carry_n_6,
      CO(0) => AND_out10_carry_n_7,
      DI(7) => \AND_out10_carry_i_1__0_n_0\,
      DI(6) => \AND_out10_carry_i_2__0_n_0\,
      DI(5) => \AND_out10_carry_i_3__0_n_0\,
      DI(4) => \AND_out10_carry_i_4__0_n_0\,
      DI(3) => \AND_out10_carry_i_5__0_n_0\,
      DI(2) => \AND_out10_carry_i_6__0_n_0\,
      DI(1) => \AND_out10_carry_i_7__0_n_0\,
      DI(0) => \AND_out10_carry_i_8__0_n_0\,
      O(7 downto 0) => NLW_AND_out10_carry_O_UNCONNECTED(7 downto 0),
      S(7) => \AND_out10_carry_i_9__0_n_0\,
      S(6) => \AND_out10_carry_i_10__0_n_0\,
      S(5) => \AND_out10_carry_i_11__0_n_0\,
      S(4) => \AND_out10_carry_i_12__0_n_0\,
      S(3) => \AND_out10_carry_i_13__0_n_0\,
      S(2) => \AND_out10_carry_i_14__0_n_0\,
      S(1) => \AND_out10_carry_i_15__0_n_0\,
      S(0) => \AND_out10_carry_i_16__0_n_0\
    );
\AND_out10_carry__0\: unisim.vcomponents.CARRY8
     port map (
      CI => AND_out10_carry_n_0,
      CI_TOP => '0',
      CO(7 downto 3) => \NLW_AND_out10_carry__0_CO_UNCONNECTED\(7 downto 3),
      CO(2) => Relational_Operator1_relop1,
      CO(1) => \AND_out10_carry__0_n_6\,
      CO(0) => \AND_out10_carry__0_n_7\,
      DI(7 downto 3) => B"00000",
      DI(2) => DI(0),
      DI(1) => \AND_out10_carry__0_i_2__0_n_0\,
      DI(0) => \AND_out10_carry__0_i_3__0_n_0\,
      O(7 downto 0) => \NLW_AND_out10_carry__0_O_UNCONNECTED\(7 downto 0),
      S(7 downto 3) => B"00000",
      S(2) => \AND_out10_carry__0_i_4__0_n_0\,
      S(1) => \AND_out10_carry__0_i_5__0_n_0\,
      S(0) => \AND_out10_carry__0_i_6__0_n_0\
    );
\AND_out10_carry__0_i_2__0\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"2F02"
    )
        port map (
      I0 => \^p\(18),
      I1 => \reduced_reg_1_reg[1]_9\(18),
      I2 => \reduced_reg_1_reg[1]_9\(19),
      I3 => \^p\(19),
      O => \AND_out10_carry__0_i_2__0_n_0\
    );
\AND_out10_carry__0_i_3__0\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"2F02"
    )
        port map (
      I0 => \^p\(16),
      I1 => \reduced_reg_1_reg[1]_9\(16),
      I2 => \reduced_reg_1_reg[1]_9\(17),
      I3 => \^p\(17),
      O => \AND_out10_carry__0_i_3__0_n_0\
    );
\AND_out10_carry__0_i_4__0\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"9"
    )
        port map (
      I0 => \^p\(20),
      I1 => \reduced_reg_1_reg[1]_9\(20),
      O => \AND_out10_carry__0_i_4__0_n_0\
    );
\AND_out10_carry__0_i_5__0\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"9009"
    )
        port map (
      I0 => \^p\(18),
      I1 => \reduced_reg_1_reg[1]_9\(18),
      I2 => \^p\(19),
      I3 => \reduced_reg_1_reg[1]_9\(19),
      O => \AND_out10_carry__0_i_5__0_n_0\
    );
\AND_out10_carry__0_i_6__0\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"9009"
    )
        port map (
      I0 => \^p\(16),
      I1 => \reduced_reg_1_reg[1]_9\(16),
      I2 => \^p\(17),
      I3 => \reduced_reg_1_reg[1]_9\(17),
      O => \AND_out10_carry__0_i_6__0_n_0\
    );
\AND_out10_carry_i_10__0\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"9009"
    )
        port map (
      I0 => \^p\(12),
      I1 => \reduced_reg_1_reg[1]_9\(12),
      I2 => \^p\(13),
      I3 => \reduced_reg_1_reg[1]_9\(13),
      O => \AND_out10_carry_i_10__0_n_0\
    );
\AND_out10_carry_i_11__0\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"9009"
    )
        port map (
      I0 => \^p\(10),
      I1 => \reduced_reg_1_reg[1]_9\(10),
      I2 => \^p\(11),
      I3 => \reduced_reg_1_reg[1]_9\(11),
      O => \AND_out10_carry_i_11__0_n_0\
    );
\AND_out10_carry_i_12__0\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"9009"
    )
        port map (
      I0 => \^p\(8),
      I1 => \reduced_reg_1_reg[1]_9\(8),
      I2 => \^p\(9),
      I3 => \reduced_reg_1_reg[1]_9\(9),
      O => \AND_out10_carry_i_12__0_n_0\
    );
\AND_out10_carry_i_13__0\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"9009"
    )
        port map (
      I0 => \^p\(6),
      I1 => \reduced_reg_1_reg[1]_9\(6),
      I2 => \^p\(7),
      I3 => \reduced_reg_1_reg[1]_9\(7),
      O => \AND_out10_carry_i_13__0_n_0\
    );
\AND_out10_carry_i_14__0\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"9009"
    )
        port map (
      I0 => \^p\(4),
      I1 => \reduced_reg_1_reg[1]_9\(4),
      I2 => \^p\(5),
      I3 => \reduced_reg_1_reg[1]_9\(5),
      O => \AND_out10_carry_i_14__0_n_0\
    );
\AND_out10_carry_i_15__0\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"9009"
    )
        port map (
      I0 => \^p\(2),
      I1 => \reduced_reg_1_reg[1]_9\(2),
      I2 => \^p\(3),
      I3 => \reduced_reg_1_reg[1]_9\(3),
      O => \AND_out10_carry_i_15__0_n_0\
    );
\AND_out10_carry_i_16__0\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"9009"
    )
        port map (
      I0 => \^p\(0),
      I1 => \reduced_reg_1_reg[1]_9\(0),
      I2 => \^p\(1),
      I3 => \reduced_reg_1_reg[1]_9\(1),
      O => \AND_out10_carry_i_16__0_n_0\
    );
\AND_out10_carry_i_1__0\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"2F02"
    )
        port map (
      I0 => \^p\(14),
      I1 => \reduced_reg_1_reg[1]_9\(14),
      I2 => \reduced_reg_1_reg[1]_9\(15),
      I3 => \^p\(15),
      O => \AND_out10_carry_i_1__0_n_0\
    );
\AND_out10_carry_i_2__0\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"2F02"
    )
        port map (
      I0 => \^p\(12),
      I1 => \reduced_reg_1_reg[1]_9\(12),
      I2 => \reduced_reg_1_reg[1]_9\(13),
      I3 => \^p\(13),
      O => \AND_out10_carry_i_2__0_n_0\
    );
\AND_out10_carry_i_3__0\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"2F02"
    )
        port map (
      I0 => \^p\(10),
      I1 => \reduced_reg_1_reg[1]_9\(10),
      I2 => \reduced_reg_1_reg[1]_9\(11),
      I3 => \^p\(11),
      O => \AND_out10_carry_i_3__0_n_0\
    );
\AND_out10_carry_i_4__0\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"2F02"
    )
        port map (
      I0 => \^p\(8),
      I1 => \reduced_reg_1_reg[1]_9\(8),
      I2 => \reduced_reg_1_reg[1]_9\(9),
      I3 => \^p\(9),
      O => \AND_out10_carry_i_4__0_n_0\
    );
\AND_out10_carry_i_5__0\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"2F02"
    )
        port map (
      I0 => \^p\(6),
      I1 => \reduced_reg_1_reg[1]_9\(6),
      I2 => \reduced_reg_1_reg[1]_9\(7),
      I3 => \^p\(7),
      O => \AND_out10_carry_i_5__0_n_0\
    );
\AND_out10_carry_i_6__0\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"2F02"
    )
        port map (
      I0 => \^p\(4),
      I1 => \reduced_reg_1_reg[1]_9\(4),
      I2 => \reduced_reg_1_reg[1]_9\(5),
      I3 => \^p\(5),
      O => \AND_out10_carry_i_6__0_n_0\
    );
\AND_out10_carry_i_7__0\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"2F02"
    )
        port map (
      I0 => \^p\(2),
      I1 => \reduced_reg_1_reg[1]_9\(2),
      I2 => \reduced_reg_1_reg[1]_9\(3),
      I3 => \^p\(3),
      O => \AND_out10_carry_i_7__0_n_0\
    );
\AND_out10_carry_i_8__0\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"2F02"
    )
        port map (
      I0 => \^p\(0),
      I1 => \reduced_reg_1_reg[1]_9\(0),
      I2 => \reduced_reg_1_reg[1]_9\(1),
      I3 => \^p\(1),
      O => \AND_out10_carry_i_8__0_n_0\
    );
\AND_out10_carry_i_9__0\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"9009"
    )
        port map (
      I0 => \^p\(14),
      I1 => \reduced_reg_1_reg[1]_9\(14),
      I2 => \^p\(15),
      I3 => \reduced_reg_1_reg[1]_9\(15),
      O => \AND_out10_carry_i_9__0_n_0\
    );
\AND_out10_inferred__0/i__carry\: unisim.vcomponents.CARRY8
     port map (
      CI => '1',
      CI_TOP => '0',
      CO(7) => \AND_out10_inferred__0/i__carry_n_0\,
      CO(6) => \AND_out10_inferred__0/i__carry_n_1\,
      CO(5) => \AND_out10_inferred__0/i__carry_n_2\,
      CO(4) => \AND_out10_inferred__0/i__carry_n_3\,
      CO(3) => \AND_out10_inferred__0/i__carry_n_4\,
      CO(2) => \AND_out10_inferred__0/i__carry_n_5\,
      CO(1) => \AND_out10_inferred__0/i__carry_n_6\,
      CO(0) => \AND_out10_inferred__0/i__carry_n_7\,
      DI(7 downto 0) => \AND_out10_inferred__0/i__carry__0_0\(7 downto 0),
      O(7 downto 0) => \NLW_AND_out10_inferred__0/i__carry_O_UNCONNECTED\(7 downto 0),
      S(7 downto 0) => \AND_out10_inferred__0/i__carry__0_1\(7 downto 0)
    );
\AND_out10_inferred__0/i__carry__0\: unisim.vcomponents.CARRY8
     port map (
      CI => \AND_out10_inferred__0/i__carry_n_0\,
      CI_TOP => '0',
      CO(7 downto 3) => \NLW_AND_out10_inferred__0/i__carry__0_CO_UNCONNECTED\(7 downto 3),
      CO(2) => Relational_Operator_relop1,
      CO(1) => \AND_out10_inferred__0/i__carry__0_n_6\,
      CO(0) => \AND_out10_inferred__0/i__carry__0_n_7\,
      DI(7 downto 3) => B"00000",
      DI(2) => \^p\(20),
      DI(1 downto 0) => \Switch4_out1_1_reg[0]\(1 downto 0),
      O(7 downto 0) => \NLW_AND_out10_inferred__0/i__carry__0_O_UNCONNECTED\(7 downto 0),
      S(7 downto 3) => B"00000",
      S(2) => \i__carry__0_i_3__0_n_0\,
      S(1 downto 0) => \Switch4_out1_1_reg[0]_0\(1 downto 0)
    );
\Switch4_out1_1[0]_i_1\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"2"
    )
        port map (
      I0 => Relational_Operator1_relop1,
      I1 => Relational_Operator_relop1,
      O => D(1)
    );
\Switch4_out1_1[1]_i_1\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"2"
    )
        port map (
      I0 => Relational_Operator1_relop1,
      O => D(0)
    );
\i__carry__0_i_3__0\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => \^p\(20),
      O => \i__carry__0_i_3__0_n_0\
    );
modulating_signal_in_clock_cycles_1_reg: unisim.vcomponents.DSP48E2
    generic map(
      ACASCREG => 1,
      ADREG => 1,
      ALUMODEREG => 0,
      AMULTSEL => "A",
      AREG => 1,
      AUTORESET_PATDET => "NO_RESET",
      AUTORESET_PRIORITY => "RESET",
      A_INPUT => "DIRECT",
      BCASCREG => 1,
      BMULTSEL => "B",
      BREG => 1,
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
      A(29 downto 20) => B"0000000000",
      A(19 downto 0) => maximum_counter_value_1(19 downto 0),
      ACIN(29 downto 0) => B"000000000000000000000000000000",
      ACOUT(29 downto 0) => NLW_modulating_signal_in_clock_cycles_1_reg_ACOUT_UNCONNECTED(29 downto 0),
      ALUMODE(3 downto 0) => B"0000",
      B(17) => B(13),
      B(16) => B(13),
      B(15) => B(13),
      B(14) => B(13),
      B(13 downto 0) => B(13 downto 0),
      BCIN(17 downto 0) => B"000000000000000000",
      BCOUT(17 downto 0) => NLW_modulating_signal_in_clock_cycles_1_reg_BCOUT_UNCONNECTED(17 downto 0),
      C(47 downto 0) => B"000000000000000000000000000000000000000000000000",
      CARRYCASCIN => '0',
      CARRYCASCOUT => NLW_modulating_signal_in_clock_cycles_1_reg_CARRYCASCOUT_UNCONNECTED,
      CARRYIN => '0',
      CARRYINSEL(2 downto 0) => B"000",
      CARRYOUT(3 downto 0) => NLW_modulating_signal_in_clock_cycles_1_reg_CARRYOUT_UNCONNECTED(3 downto 0),
      CEA1 => '0',
      CEA2 => CEP,
      CEAD => '0',
      CEALUMODE => '0',
      CEB1 => '0',
      CEB2 => CEP,
      CEC => '0',
      CECARRYIN => '0',
      CECTRL => '0',
      CED => '0',
      CEINMODE => '0',
      CEM => '0',
      CEP => CEP,
      CLK => IPCORE_CLK,
      D(26 downto 0) => B"000000000000000000000000000",
      INMODE(4 downto 0) => B"00000",
      MULTSIGNIN => '0',
      MULTSIGNOUT => NLW_modulating_signal_in_clock_cycles_1_reg_MULTSIGNOUT_UNCONNECTED,
      OPMODE(8 downto 0) => B"000000101",
      OVERFLOW => NLW_modulating_signal_in_clock_cycles_1_reg_OVERFLOW_UNCONNECTED,
      P(47 downto 33) => NLW_modulating_signal_in_clock_cycles_1_reg_P_UNCONNECTED(47 downto 33),
      P(32 downto 12) => \^p\(20 downto 0),
      P(11) => modulating_signal_in_clock_cycles_1_reg_n_94,
      P(10) => modulating_signal_in_clock_cycles_1_reg_n_95,
      P(9) => modulating_signal_in_clock_cycles_1_reg_n_96,
      P(8) => modulating_signal_in_clock_cycles_1_reg_n_97,
      P(7) => modulating_signal_in_clock_cycles_1_reg_n_98,
      P(6) => modulating_signal_in_clock_cycles_1_reg_n_99,
      P(5) => modulating_signal_in_clock_cycles_1_reg_n_100,
      P(4) => modulating_signal_in_clock_cycles_1_reg_n_101,
      P(3) => modulating_signal_in_clock_cycles_1_reg_n_102,
      P(2) => modulating_signal_in_clock_cycles_1_reg_n_103,
      P(1) => modulating_signal_in_clock_cycles_1_reg_n_104,
      P(0) => modulating_signal_in_clock_cycles_1_reg_n_105,
      PATTERNBDETECT => NLW_modulating_signal_in_clock_cycles_1_reg_PATTERNBDETECT_UNCONNECTED,
      PATTERNDETECT => NLW_modulating_signal_in_clock_cycles_1_reg_PATTERNDETECT_UNCONNECTED,
      PCIN(47 downto 0) => B"000000000000000000000000000000000000000000000000",
      PCOUT(47 downto 0) => NLW_modulating_signal_in_clock_cycles_1_reg_PCOUT_UNCONNECTED(47 downto 0),
      RSTA => RSTP,
      RSTALLCARRYIN => '0',
      RSTALUMODE => '0',
      RSTB => RSTP,
      RSTC => '0',
      RSTCTRL => '0',
      RSTD => '0',
      RSTINMODE => '0',
      RSTM => '0',
      RSTP => RSTP,
      UNDERFLOW => NLW_modulating_signal_in_clock_cycles_1_reg_UNDERFLOW_UNCONNECTED,
      XOROUT(7 downto 0) => NLW_modulating_signal_in_clock_cycles_1_reg_XOROUT_UNCONNECTED(7 downto 0)
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity zusys_PWM_SS_3L_ip_0_0_PWM_SS_3L_ip_src_Modulator_c is
  port (
    P : out STD_LOGIC_VECTOR ( 20 downto 0 );
    D : out STD_LOGIC_VECTOR ( 1 downto 0 );
    CEP : in STD_LOGIC;
    IPCORE_CLK : in STD_LOGIC;
    RSTP : in STD_LOGIC;
    B : in STD_LOGIC_VECTOR ( 13 downto 0 );
    maximum_counter_value_1 : in STD_LOGIC_VECTOR ( 19 downto 0 );
    \Switch5_out1_1_reg[1]\ : in STD_LOGIC_VECTOR ( 0 to 0 );
    \AND_out10_inferred__0/i__carry__0_0\ : in STD_LOGIC_VECTOR ( 7 downto 0 );
    \AND_out10_inferred__0/i__carry__0_1\ : in STD_LOGIC_VECTOR ( 7 downto 0 );
    \Switch5_out1_1_reg[0]\ : in STD_LOGIC_VECTOR ( 1 downto 0 );
    \Switch5_out1_1_reg[0]_0\ : in STD_LOGIC_VECTOR ( 1 downto 0 );
    \reduced_reg_1_reg[1]_9\ : in STD_LOGIC_VECTOR ( 20 downto 0 )
  );
  attribute ORIG_REF_NAME : string;
  attribute ORIG_REF_NAME of zusys_PWM_SS_3L_ip_0_0_PWM_SS_3L_ip_src_Modulator_c : entity is "PWM_SS_3L_ip_src_Modulator_c";
end zusys_PWM_SS_3L_ip_0_0_PWM_SS_3L_ip_src_Modulator_c;

architecture STRUCTURE of zusys_PWM_SS_3L_ip_0_0_PWM_SS_3L_ip_src_Modulator_c is
  signal \AND_out10_carry__0_i_2__1_n_0\ : STD_LOGIC;
  signal \AND_out10_carry__0_i_3__1_n_0\ : STD_LOGIC;
  signal \AND_out10_carry__0_i_4__1_n_0\ : STD_LOGIC;
  signal \AND_out10_carry__0_i_5__1_n_0\ : STD_LOGIC;
  signal \AND_out10_carry__0_i_6__1_n_0\ : STD_LOGIC;
  signal \AND_out10_carry__0_n_6\ : STD_LOGIC;
  signal \AND_out10_carry__0_n_7\ : STD_LOGIC;
  signal \AND_out10_carry_i_10__1_n_0\ : STD_LOGIC;
  signal \AND_out10_carry_i_11__1_n_0\ : STD_LOGIC;
  signal \AND_out10_carry_i_12__1_n_0\ : STD_LOGIC;
  signal \AND_out10_carry_i_13__1_n_0\ : STD_LOGIC;
  signal \AND_out10_carry_i_14__1_n_0\ : STD_LOGIC;
  signal \AND_out10_carry_i_15__1_n_0\ : STD_LOGIC;
  signal \AND_out10_carry_i_16__1_n_0\ : STD_LOGIC;
  signal \AND_out10_carry_i_1__1_n_0\ : STD_LOGIC;
  signal \AND_out10_carry_i_2__1_n_0\ : STD_LOGIC;
  signal \AND_out10_carry_i_3__1_n_0\ : STD_LOGIC;
  signal \AND_out10_carry_i_4__1_n_0\ : STD_LOGIC;
  signal \AND_out10_carry_i_5__1_n_0\ : STD_LOGIC;
  signal \AND_out10_carry_i_6__1_n_0\ : STD_LOGIC;
  signal \AND_out10_carry_i_7__1_n_0\ : STD_LOGIC;
  signal \AND_out10_carry_i_8__1_n_0\ : STD_LOGIC;
  signal \AND_out10_carry_i_9__1_n_0\ : STD_LOGIC;
  signal AND_out10_carry_n_0 : STD_LOGIC;
  signal AND_out10_carry_n_1 : STD_LOGIC;
  signal AND_out10_carry_n_2 : STD_LOGIC;
  signal AND_out10_carry_n_3 : STD_LOGIC;
  signal AND_out10_carry_n_4 : STD_LOGIC;
  signal AND_out10_carry_n_5 : STD_LOGIC;
  signal AND_out10_carry_n_6 : STD_LOGIC;
  signal AND_out10_carry_n_7 : STD_LOGIC;
  signal \AND_out10_inferred__0/i__carry__0_n_6\ : STD_LOGIC;
  signal \AND_out10_inferred__0/i__carry__0_n_7\ : STD_LOGIC;
  signal \AND_out10_inferred__0/i__carry_n_0\ : STD_LOGIC;
  signal \AND_out10_inferred__0/i__carry_n_1\ : STD_LOGIC;
  signal \AND_out10_inferred__0/i__carry_n_2\ : STD_LOGIC;
  signal \AND_out10_inferred__0/i__carry_n_3\ : STD_LOGIC;
  signal \AND_out10_inferred__0/i__carry_n_4\ : STD_LOGIC;
  signal \AND_out10_inferred__0/i__carry_n_5\ : STD_LOGIC;
  signal \AND_out10_inferred__0/i__carry_n_6\ : STD_LOGIC;
  signal \AND_out10_inferred__0/i__carry_n_7\ : STD_LOGIC;
  signal \^p\ : STD_LOGIC_VECTOR ( 20 downto 0 );
  signal Relational_Operator1_relop1 : STD_LOGIC;
  signal Relational_Operator_relop1 : STD_LOGIC;
  signal \i__carry__0_i_3__1_n_0\ : STD_LOGIC;
  signal modulating_signal_in_clock_cycles_1_reg_n_100 : STD_LOGIC;
  signal modulating_signal_in_clock_cycles_1_reg_n_101 : STD_LOGIC;
  signal modulating_signal_in_clock_cycles_1_reg_n_102 : STD_LOGIC;
  signal modulating_signal_in_clock_cycles_1_reg_n_103 : STD_LOGIC;
  signal modulating_signal_in_clock_cycles_1_reg_n_104 : STD_LOGIC;
  signal modulating_signal_in_clock_cycles_1_reg_n_105 : STD_LOGIC;
  signal modulating_signal_in_clock_cycles_1_reg_n_94 : STD_LOGIC;
  signal modulating_signal_in_clock_cycles_1_reg_n_95 : STD_LOGIC;
  signal modulating_signal_in_clock_cycles_1_reg_n_96 : STD_LOGIC;
  signal modulating_signal_in_clock_cycles_1_reg_n_97 : STD_LOGIC;
  signal modulating_signal_in_clock_cycles_1_reg_n_98 : STD_LOGIC;
  signal modulating_signal_in_clock_cycles_1_reg_n_99 : STD_LOGIC;
  signal NLW_AND_out10_carry_O_UNCONNECTED : STD_LOGIC_VECTOR ( 7 downto 0 );
  signal \NLW_AND_out10_carry__0_CO_UNCONNECTED\ : STD_LOGIC_VECTOR ( 7 downto 3 );
  signal \NLW_AND_out10_carry__0_O_UNCONNECTED\ : STD_LOGIC_VECTOR ( 7 downto 0 );
  signal \NLW_AND_out10_inferred__0/i__carry_O_UNCONNECTED\ : STD_LOGIC_VECTOR ( 7 downto 0 );
  signal \NLW_AND_out10_inferred__0/i__carry__0_CO_UNCONNECTED\ : STD_LOGIC_VECTOR ( 7 downto 3 );
  signal \NLW_AND_out10_inferred__0/i__carry__0_O_UNCONNECTED\ : STD_LOGIC_VECTOR ( 7 downto 0 );
  signal NLW_modulating_signal_in_clock_cycles_1_reg_CARRYCASCOUT_UNCONNECTED : STD_LOGIC;
  signal NLW_modulating_signal_in_clock_cycles_1_reg_MULTSIGNOUT_UNCONNECTED : STD_LOGIC;
  signal NLW_modulating_signal_in_clock_cycles_1_reg_OVERFLOW_UNCONNECTED : STD_LOGIC;
  signal NLW_modulating_signal_in_clock_cycles_1_reg_PATTERNBDETECT_UNCONNECTED : STD_LOGIC;
  signal NLW_modulating_signal_in_clock_cycles_1_reg_PATTERNDETECT_UNCONNECTED : STD_LOGIC;
  signal NLW_modulating_signal_in_clock_cycles_1_reg_UNDERFLOW_UNCONNECTED : STD_LOGIC;
  signal NLW_modulating_signal_in_clock_cycles_1_reg_ACOUT_UNCONNECTED : STD_LOGIC_VECTOR ( 29 downto 0 );
  signal NLW_modulating_signal_in_clock_cycles_1_reg_BCOUT_UNCONNECTED : STD_LOGIC_VECTOR ( 17 downto 0 );
  signal NLW_modulating_signal_in_clock_cycles_1_reg_CARRYOUT_UNCONNECTED : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal NLW_modulating_signal_in_clock_cycles_1_reg_P_UNCONNECTED : STD_LOGIC_VECTOR ( 47 downto 33 );
  signal NLW_modulating_signal_in_clock_cycles_1_reg_PCOUT_UNCONNECTED : STD_LOGIC_VECTOR ( 47 downto 0 );
  signal NLW_modulating_signal_in_clock_cycles_1_reg_XOROUT_UNCONNECTED : STD_LOGIC_VECTOR ( 7 downto 0 );
  attribute COMPARATOR_THRESHOLD : integer;
  attribute COMPARATOR_THRESHOLD of AND_out10_carry : label is 11;
  attribute COMPARATOR_THRESHOLD of \AND_out10_carry__0\ : label is 11;
  attribute COMPARATOR_THRESHOLD of \AND_out10_inferred__0/i__carry\ : label is 11;
  attribute COMPARATOR_THRESHOLD of \AND_out10_inferred__0/i__carry__0\ : label is 11;
  attribute SOFT_HLUTNM : string;
  attribute SOFT_HLUTNM of \Switch5_out1_1[0]_i_1\ : label is "soft_lutpair52";
  attribute SOFT_HLUTNM of \Switch5_out1_1[1]_i_1\ : label is "soft_lutpair52";
  attribute KEEP_HIERARCHY : string;
  attribute KEEP_HIERARCHY of modulating_signal_in_clock_cycles_1_reg : label is "yes";
begin
  P(20 downto 0) <= \^p\(20 downto 0);
AND_out10_carry: unisim.vcomponents.CARRY8
     port map (
      CI => '1',
      CI_TOP => '0',
      CO(7) => AND_out10_carry_n_0,
      CO(6) => AND_out10_carry_n_1,
      CO(5) => AND_out10_carry_n_2,
      CO(4) => AND_out10_carry_n_3,
      CO(3) => AND_out10_carry_n_4,
      CO(2) => AND_out10_carry_n_5,
      CO(1) => AND_out10_carry_n_6,
      CO(0) => AND_out10_carry_n_7,
      DI(7) => \AND_out10_carry_i_1__1_n_0\,
      DI(6) => \AND_out10_carry_i_2__1_n_0\,
      DI(5) => \AND_out10_carry_i_3__1_n_0\,
      DI(4) => \AND_out10_carry_i_4__1_n_0\,
      DI(3) => \AND_out10_carry_i_5__1_n_0\,
      DI(2) => \AND_out10_carry_i_6__1_n_0\,
      DI(1) => \AND_out10_carry_i_7__1_n_0\,
      DI(0) => \AND_out10_carry_i_8__1_n_0\,
      O(7 downto 0) => NLW_AND_out10_carry_O_UNCONNECTED(7 downto 0),
      S(7) => \AND_out10_carry_i_9__1_n_0\,
      S(6) => \AND_out10_carry_i_10__1_n_0\,
      S(5) => \AND_out10_carry_i_11__1_n_0\,
      S(4) => \AND_out10_carry_i_12__1_n_0\,
      S(3) => \AND_out10_carry_i_13__1_n_0\,
      S(2) => \AND_out10_carry_i_14__1_n_0\,
      S(1) => \AND_out10_carry_i_15__1_n_0\,
      S(0) => \AND_out10_carry_i_16__1_n_0\
    );
\AND_out10_carry__0\: unisim.vcomponents.CARRY8
     port map (
      CI => AND_out10_carry_n_0,
      CI_TOP => '0',
      CO(7 downto 3) => \NLW_AND_out10_carry__0_CO_UNCONNECTED\(7 downto 3),
      CO(2) => Relational_Operator1_relop1,
      CO(1) => \AND_out10_carry__0_n_6\,
      CO(0) => \AND_out10_carry__0_n_7\,
      DI(7 downto 3) => B"00000",
      DI(2) => \Switch5_out1_1_reg[1]\(0),
      DI(1) => \AND_out10_carry__0_i_2__1_n_0\,
      DI(0) => \AND_out10_carry__0_i_3__1_n_0\,
      O(7 downto 0) => \NLW_AND_out10_carry__0_O_UNCONNECTED\(7 downto 0),
      S(7 downto 3) => B"00000",
      S(2) => \AND_out10_carry__0_i_4__1_n_0\,
      S(1) => \AND_out10_carry__0_i_5__1_n_0\,
      S(0) => \AND_out10_carry__0_i_6__1_n_0\
    );
\AND_out10_carry__0_i_2__1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"2F02"
    )
        port map (
      I0 => \^p\(18),
      I1 => \reduced_reg_1_reg[1]_9\(18),
      I2 => \reduced_reg_1_reg[1]_9\(19),
      I3 => \^p\(19),
      O => \AND_out10_carry__0_i_2__1_n_0\
    );
\AND_out10_carry__0_i_3__1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"2F02"
    )
        port map (
      I0 => \^p\(16),
      I1 => \reduced_reg_1_reg[1]_9\(16),
      I2 => \reduced_reg_1_reg[1]_9\(17),
      I3 => \^p\(17),
      O => \AND_out10_carry__0_i_3__1_n_0\
    );
\AND_out10_carry__0_i_4__1\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"9"
    )
        port map (
      I0 => \^p\(20),
      I1 => \reduced_reg_1_reg[1]_9\(20),
      O => \AND_out10_carry__0_i_4__1_n_0\
    );
\AND_out10_carry__0_i_5__1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"9009"
    )
        port map (
      I0 => \^p\(18),
      I1 => \reduced_reg_1_reg[1]_9\(18),
      I2 => \^p\(19),
      I3 => \reduced_reg_1_reg[1]_9\(19),
      O => \AND_out10_carry__0_i_5__1_n_0\
    );
\AND_out10_carry__0_i_6__1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"9009"
    )
        port map (
      I0 => \^p\(16),
      I1 => \reduced_reg_1_reg[1]_9\(16),
      I2 => \^p\(17),
      I3 => \reduced_reg_1_reg[1]_9\(17),
      O => \AND_out10_carry__0_i_6__1_n_0\
    );
\AND_out10_carry_i_10__1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"9009"
    )
        port map (
      I0 => \^p\(12),
      I1 => \reduced_reg_1_reg[1]_9\(12),
      I2 => \^p\(13),
      I3 => \reduced_reg_1_reg[1]_9\(13),
      O => \AND_out10_carry_i_10__1_n_0\
    );
\AND_out10_carry_i_11__1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"9009"
    )
        port map (
      I0 => \^p\(10),
      I1 => \reduced_reg_1_reg[1]_9\(10),
      I2 => \^p\(11),
      I3 => \reduced_reg_1_reg[1]_9\(11),
      O => \AND_out10_carry_i_11__1_n_0\
    );
\AND_out10_carry_i_12__1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"9009"
    )
        port map (
      I0 => \^p\(8),
      I1 => \reduced_reg_1_reg[1]_9\(8),
      I2 => \^p\(9),
      I3 => \reduced_reg_1_reg[1]_9\(9),
      O => \AND_out10_carry_i_12__1_n_0\
    );
\AND_out10_carry_i_13__1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"9009"
    )
        port map (
      I0 => \^p\(6),
      I1 => \reduced_reg_1_reg[1]_9\(6),
      I2 => \^p\(7),
      I3 => \reduced_reg_1_reg[1]_9\(7),
      O => \AND_out10_carry_i_13__1_n_0\
    );
\AND_out10_carry_i_14__1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"9009"
    )
        port map (
      I0 => \^p\(4),
      I1 => \reduced_reg_1_reg[1]_9\(4),
      I2 => \^p\(5),
      I3 => \reduced_reg_1_reg[1]_9\(5),
      O => \AND_out10_carry_i_14__1_n_0\
    );
\AND_out10_carry_i_15__1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"9009"
    )
        port map (
      I0 => \^p\(2),
      I1 => \reduced_reg_1_reg[1]_9\(2),
      I2 => \^p\(3),
      I3 => \reduced_reg_1_reg[1]_9\(3),
      O => \AND_out10_carry_i_15__1_n_0\
    );
\AND_out10_carry_i_16__1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"9009"
    )
        port map (
      I0 => \^p\(0),
      I1 => \reduced_reg_1_reg[1]_9\(0),
      I2 => \^p\(1),
      I3 => \reduced_reg_1_reg[1]_9\(1),
      O => \AND_out10_carry_i_16__1_n_0\
    );
\AND_out10_carry_i_1__1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"2F02"
    )
        port map (
      I0 => \^p\(14),
      I1 => \reduced_reg_1_reg[1]_9\(14),
      I2 => \reduced_reg_1_reg[1]_9\(15),
      I3 => \^p\(15),
      O => \AND_out10_carry_i_1__1_n_0\
    );
\AND_out10_carry_i_2__1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"2F02"
    )
        port map (
      I0 => \^p\(12),
      I1 => \reduced_reg_1_reg[1]_9\(12),
      I2 => \reduced_reg_1_reg[1]_9\(13),
      I3 => \^p\(13),
      O => \AND_out10_carry_i_2__1_n_0\
    );
\AND_out10_carry_i_3__1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"2F02"
    )
        port map (
      I0 => \^p\(10),
      I1 => \reduced_reg_1_reg[1]_9\(10),
      I2 => \reduced_reg_1_reg[1]_9\(11),
      I3 => \^p\(11),
      O => \AND_out10_carry_i_3__1_n_0\
    );
\AND_out10_carry_i_4__1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"2F02"
    )
        port map (
      I0 => \^p\(8),
      I1 => \reduced_reg_1_reg[1]_9\(8),
      I2 => \reduced_reg_1_reg[1]_9\(9),
      I3 => \^p\(9),
      O => \AND_out10_carry_i_4__1_n_0\
    );
\AND_out10_carry_i_5__1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"2F02"
    )
        port map (
      I0 => \^p\(6),
      I1 => \reduced_reg_1_reg[1]_9\(6),
      I2 => \reduced_reg_1_reg[1]_9\(7),
      I3 => \^p\(7),
      O => \AND_out10_carry_i_5__1_n_0\
    );
\AND_out10_carry_i_6__1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"2F02"
    )
        port map (
      I0 => \^p\(4),
      I1 => \reduced_reg_1_reg[1]_9\(4),
      I2 => \reduced_reg_1_reg[1]_9\(5),
      I3 => \^p\(5),
      O => \AND_out10_carry_i_6__1_n_0\
    );
\AND_out10_carry_i_7__1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"2F02"
    )
        port map (
      I0 => \^p\(2),
      I1 => \reduced_reg_1_reg[1]_9\(2),
      I2 => \reduced_reg_1_reg[1]_9\(3),
      I3 => \^p\(3),
      O => \AND_out10_carry_i_7__1_n_0\
    );
\AND_out10_carry_i_8__1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"2F02"
    )
        port map (
      I0 => \^p\(0),
      I1 => \reduced_reg_1_reg[1]_9\(0),
      I2 => \reduced_reg_1_reg[1]_9\(1),
      I3 => \^p\(1),
      O => \AND_out10_carry_i_8__1_n_0\
    );
\AND_out10_carry_i_9__1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"9009"
    )
        port map (
      I0 => \^p\(14),
      I1 => \reduced_reg_1_reg[1]_9\(14),
      I2 => \^p\(15),
      I3 => \reduced_reg_1_reg[1]_9\(15),
      O => \AND_out10_carry_i_9__1_n_0\
    );
\AND_out10_inferred__0/i__carry\: unisim.vcomponents.CARRY8
     port map (
      CI => '1',
      CI_TOP => '0',
      CO(7) => \AND_out10_inferred__0/i__carry_n_0\,
      CO(6) => \AND_out10_inferred__0/i__carry_n_1\,
      CO(5) => \AND_out10_inferred__0/i__carry_n_2\,
      CO(4) => \AND_out10_inferred__0/i__carry_n_3\,
      CO(3) => \AND_out10_inferred__0/i__carry_n_4\,
      CO(2) => \AND_out10_inferred__0/i__carry_n_5\,
      CO(1) => \AND_out10_inferred__0/i__carry_n_6\,
      CO(0) => \AND_out10_inferred__0/i__carry_n_7\,
      DI(7 downto 0) => \AND_out10_inferred__0/i__carry__0_0\(7 downto 0),
      O(7 downto 0) => \NLW_AND_out10_inferred__0/i__carry_O_UNCONNECTED\(7 downto 0),
      S(7 downto 0) => \AND_out10_inferred__0/i__carry__0_1\(7 downto 0)
    );
\AND_out10_inferred__0/i__carry__0\: unisim.vcomponents.CARRY8
     port map (
      CI => \AND_out10_inferred__0/i__carry_n_0\,
      CI_TOP => '0',
      CO(7 downto 3) => \NLW_AND_out10_inferred__0/i__carry__0_CO_UNCONNECTED\(7 downto 3),
      CO(2) => Relational_Operator_relop1,
      CO(1) => \AND_out10_inferred__0/i__carry__0_n_6\,
      CO(0) => \AND_out10_inferred__0/i__carry__0_n_7\,
      DI(7 downto 3) => B"00000",
      DI(2) => \^p\(20),
      DI(1 downto 0) => \Switch5_out1_1_reg[0]\(1 downto 0),
      O(7 downto 0) => \NLW_AND_out10_inferred__0/i__carry__0_O_UNCONNECTED\(7 downto 0),
      S(7 downto 3) => B"00000",
      S(2) => \i__carry__0_i_3__1_n_0\,
      S(1 downto 0) => \Switch5_out1_1_reg[0]_0\(1 downto 0)
    );
\Switch5_out1_1[0]_i_1\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"2"
    )
        port map (
      I0 => Relational_Operator1_relop1,
      I1 => Relational_Operator_relop1,
      O => D(1)
    );
\Switch5_out1_1[1]_i_1\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"2"
    )
        port map (
      I0 => Relational_Operator1_relop1,
      O => D(0)
    );
\i__carry__0_i_3__1\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => \^p\(20),
      O => \i__carry__0_i_3__1_n_0\
    );
modulating_signal_in_clock_cycles_1_reg: unisim.vcomponents.DSP48E2
    generic map(
      ACASCREG => 1,
      ADREG => 1,
      ALUMODEREG => 0,
      AMULTSEL => "A",
      AREG => 1,
      AUTORESET_PATDET => "NO_RESET",
      AUTORESET_PRIORITY => "RESET",
      A_INPUT => "DIRECT",
      BCASCREG => 1,
      BMULTSEL => "B",
      BREG => 1,
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
      A(29 downto 20) => B"0000000000",
      A(19 downto 0) => maximum_counter_value_1(19 downto 0),
      ACIN(29 downto 0) => B"000000000000000000000000000000",
      ACOUT(29 downto 0) => NLW_modulating_signal_in_clock_cycles_1_reg_ACOUT_UNCONNECTED(29 downto 0),
      ALUMODE(3 downto 0) => B"0000",
      B(17) => B(13),
      B(16) => B(13),
      B(15) => B(13),
      B(14) => B(13),
      B(13 downto 0) => B(13 downto 0),
      BCIN(17 downto 0) => B"000000000000000000",
      BCOUT(17 downto 0) => NLW_modulating_signal_in_clock_cycles_1_reg_BCOUT_UNCONNECTED(17 downto 0),
      C(47 downto 0) => B"000000000000000000000000000000000000000000000000",
      CARRYCASCIN => '0',
      CARRYCASCOUT => NLW_modulating_signal_in_clock_cycles_1_reg_CARRYCASCOUT_UNCONNECTED,
      CARRYIN => '0',
      CARRYINSEL(2 downto 0) => B"000",
      CARRYOUT(3 downto 0) => NLW_modulating_signal_in_clock_cycles_1_reg_CARRYOUT_UNCONNECTED(3 downto 0),
      CEA1 => '0',
      CEA2 => CEP,
      CEAD => '0',
      CEALUMODE => '0',
      CEB1 => '0',
      CEB2 => CEP,
      CEC => '0',
      CECARRYIN => '0',
      CECTRL => '0',
      CED => '0',
      CEINMODE => '0',
      CEM => '0',
      CEP => CEP,
      CLK => IPCORE_CLK,
      D(26 downto 0) => B"000000000000000000000000000",
      INMODE(4 downto 0) => B"00000",
      MULTSIGNIN => '0',
      MULTSIGNOUT => NLW_modulating_signal_in_clock_cycles_1_reg_MULTSIGNOUT_UNCONNECTED,
      OPMODE(8 downto 0) => B"000000101",
      OVERFLOW => NLW_modulating_signal_in_clock_cycles_1_reg_OVERFLOW_UNCONNECTED,
      P(47 downto 33) => NLW_modulating_signal_in_clock_cycles_1_reg_P_UNCONNECTED(47 downto 33),
      P(32 downto 12) => \^p\(20 downto 0),
      P(11) => modulating_signal_in_clock_cycles_1_reg_n_94,
      P(10) => modulating_signal_in_clock_cycles_1_reg_n_95,
      P(9) => modulating_signal_in_clock_cycles_1_reg_n_96,
      P(8) => modulating_signal_in_clock_cycles_1_reg_n_97,
      P(7) => modulating_signal_in_clock_cycles_1_reg_n_98,
      P(6) => modulating_signal_in_clock_cycles_1_reg_n_99,
      P(5) => modulating_signal_in_clock_cycles_1_reg_n_100,
      P(4) => modulating_signal_in_clock_cycles_1_reg_n_101,
      P(3) => modulating_signal_in_clock_cycles_1_reg_n_102,
      P(2) => modulating_signal_in_clock_cycles_1_reg_n_103,
      P(1) => modulating_signal_in_clock_cycles_1_reg_n_104,
      P(0) => modulating_signal_in_clock_cycles_1_reg_n_105,
      PATTERNBDETECT => NLW_modulating_signal_in_clock_cycles_1_reg_PATTERNBDETECT_UNCONNECTED,
      PATTERNDETECT => NLW_modulating_signal_in_clock_cycles_1_reg_PATTERNDETECT_UNCONNECTED,
      PCIN(47 downto 0) => B"000000000000000000000000000000000000000000000000",
      PCOUT(47 downto 0) => NLW_modulating_signal_in_clock_cycles_1_reg_PCOUT_UNCONNECTED(47 downto 0),
      RSTA => RSTP,
      RSTALLCARRYIN => '0',
      RSTALUMODE => '0',
      RSTB => RSTP,
      RSTC => '0',
      RSTCTRL => '0',
      RSTD => '0',
      RSTINMODE => '0',
      RSTM => '0',
      RSTP => RSTP,
      UNDERFLOW => NLW_modulating_signal_in_clock_cycles_1_reg_UNDERFLOW_UNCONNECTED,
      XOROUT(7 downto 0) => NLW_modulating_signal_in_clock_cycles_1_reg_XOROUT_UNCONNECTED(7 downto 0)
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity zusys_PWM_SS_3L_ip_0_0_PWM_SS_3L_ip_axi_lite is
  port (
    FSM_sequential_axi_lite_rstate_reg : out STD_LOGIC;
    CEP : out STD_LOGIC;
    write_PWM_en_AXI : out STD_LOGIC;
    AXI4_Lite_RDATA : out STD_LOGIC_VECTOR ( 0 to 0 );
    soft_reset : out STD_LOGIC;
    data_reg_axi_enable_1_1_reg : out STD_LOGIC;
    AXI4_Lite_ARREADY : out STD_LOGIC;
    AXI4_Lite_AWREADY : out STD_LOGIC;
    reset_in : out STD_LOGIC;
    Q : out STD_LOGIC_VECTOR ( 1 downto 0 );
    \data_reg_PWM_counter_max_value_int_AXI_1_1_reg[19]\ : out STD_LOGIC_VECTOR ( 19 downto 0 );
    \data_reg_PWM_min_pulse_width_0to1_AXI_1_1_reg[13]\ : out STD_LOGIC_VECTOR ( 13 downto 0 );
    \data_reg_Mode_AXI_1_1_reg[1]\ : out STD_LOGIC_VECTOR ( 1 downto 0 );
    \data_reg_TriState_HB1_AXI_1_1_reg[1]\ : out STD_LOGIC_VECTOR ( 1 downto 0 );
    \data_reg_TriState_HB2_AXI_1_1_reg[1]\ : out STD_LOGIC_VECTOR ( 1 downto 0 );
    \data_reg_TriState_HB3_AXI_1_1_reg[1]\ : out STD_LOGIC_VECTOR ( 1 downto 0 );
    \data_reg_m_u1_norm_AXI_1_1_reg[13]\ : out STD_LOGIC_VECTOR ( 13 downto 0 );
    \data_reg_m_u2_norm_AXI_1_1_reg[13]\ : out STD_LOGIC_VECTOR ( 13 downto 0 );
    \data_reg_m_u3_norm_AXI_1_1_reg[13]\ : out STD_LOGIC_VECTOR ( 13 downto 0 );
    AXI4_Lite_ACLK : in STD_LOGIC;
    RSTP : in STD_LOGIC;
    AXI4_Lite_ARADDR : in STD_LOGIC_VECTOR ( 13 downto 0 );
    AXI4_Lite_ARVALID : in STD_LOGIC;
    \HDL_Counter2_count_reg[19]\ : in STD_LOGIC;
    AXI4_Lite_RREADY : in STD_LOGIC;
    AXI4_Lite_AWVALID : in STD_LOGIC;
    AXI4_Lite_ARESETN : in STD_LOGIC;
    IPCORE_RESETN : in STD_LOGIC;
    AXI4_Lite_BREADY : in STD_LOGIC;
    AXI4_Lite_WVALID : in STD_LOGIC;
    AXI4_Lite_WSTRB : in STD_LOGIC_VECTOR ( 3 downto 0 );
    AXI4_Lite_AWADDR : in STD_LOGIC_VECTOR ( 13 downto 0 );
    AXI4_Lite_WDATA : in STD_LOGIC_VECTOR ( 19 downto 0 )
  );
  attribute ORIG_REF_NAME : string;
  attribute ORIG_REF_NAME of zusys_PWM_SS_3L_ip_0_0_PWM_SS_3L_ip_axi_lite : entity is "PWM_SS_3L_ip_axi_lite";
end zusys_PWM_SS_3L_ip_0_0_PWM_SS_3L_ip_axi_lite;

architecture STRUCTURE of zusys_PWM_SS_3L_ip_0_0_PWM_SS_3L_ip_axi_lite is
  signal \^cep\ : STD_LOGIC;
  signal read_reg_ip_timestamp : STD_LOGIC_VECTOR ( 30 to 30 );
  signal reg_enb_Mode_AXI_1_1 : STD_LOGIC;
  signal reg_enb_PWM_counter_max_value_int_AXI_1_1 : STD_LOGIC;
  signal reg_enb_PWM_min_pulse_width_0to1_AXI_1_1 : STD_LOGIC;
  signal reg_enb_TriState_HB1_AXI_1_1 : STD_LOGIC;
  signal reg_enb_TriState_HB2_AXI_1_1 : STD_LOGIC;
  signal reg_enb_TriState_HB3_AXI_1_1 : STD_LOGIC;
  signal reg_enb_m_u1_norm_AXI_1_1 : STD_LOGIC;
  signal reg_enb_m_u2_norm_AXI_1_1 : STD_LOGIC;
  signal reg_enb_m_u3_norm_AXI_1_1 : STD_LOGIC;
  signal u_PWM_SS_3L_ip_axi_lite_module_inst_n_15 : STD_LOGIC;
  signal u_PWM_SS_3L_ip_axi_lite_module_inst_n_16 : STD_LOGIC;
  signal u_PWM_SS_3L_ip_axi_lite_module_inst_n_17 : STD_LOGIC;
  signal u_PWM_SS_3L_ip_axi_lite_module_inst_n_18 : STD_LOGIC;
  signal u_PWM_SS_3L_ip_axi_lite_module_inst_n_19 : STD_LOGIC;
  signal u_PWM_SS_3L_ip_axi_lite_module_inst_n_20 : STD_LOGIC;
  signal u_PWM_SS_3L_ip_axi_lite_module_inst_n_21 : STD_LOGIC;
  signal u_PWM_SS_3L_ip_axi_lite_module_inst_n_22 : STD_LOGIC;
  signal u_PWM_SS_3L_ip_axi_lite_module_inst_n_23 : STD_LOGIC;
  signal u_PWM_SS_3L_ip_axi_lite_module_inst_n_24 : STD_LOGIC;
  signal u_PWM_SS_3L_ip_axi_lite_module_inst_n_25 : STD_LOGIC;
  signal u_PWM_SS_3L_ip_axi_lite_module_inst_n_26 : STD_LOGIC;
  signal u_PWM_SS_3L_ip_axi_lite_module_inst_n_27 : STD_LOGIC;
  signal u_PWM_SS_3L_ip_axi_lite_module_inst_n_28 : STD_LOGIC;
  signal u_PWM_SS_3L_ip_axi_lite_module_inst_n_29 : STD_LOGIC;
  signal u_PWM_SS_3L_ip_axi_lite_module_inst_n_30 : STD_LOGIC;
  signal u_PWM_SS_3L_ip_axi_lite_module_inst_n_31 : STD_LOGIC;
  signal u_PWM_SS_3L_ip_axi_lite_module_inst_n_32 : STD_LOGIC;
  signal u_PWM_SS_3L_ip_axi_lite_module_inst_n_33 : STD_LOGIC;
  signal u_PWM_SS_3L_ip_axi_lite_module_inst_n_34 : STD_LOGIC;
  signal u_PWM_SS_3L_ip_axi_lite_module_inst_n_37 : STD_LOGIC;
  signal u_PWM_SS_3L_ip_axi_lite_module_inst_n_38 : STD_LOGIC;
  signal \^write_pwm_en_axi\ : STD_LOGIC;
begin
  CEP <= \^cep\;
  write_PWM_en_AXI <= \^write_pwm_en_axi\;
u_PWM_SS_3L_ip_addr_decoder_inst: entity work.zusys_PWM_SS_3L_ip_0_0_PWM_SS_3L_ip_addr_decoder
     port map (
      AXI4_Lite_ACLK => AXI4_Lite_ACLK,
      CEP => \^cep\,
      E(0) => reg_enb_PWM_counter_max_value_int_AXI_1_1,
      \HDL_Counter2_count_reg[19]\ => \HDL_Counter2_count_reg[19]\,
      Q(19) => u_PWM_SS_3L_ip_axi_lite_module_inst_n_15,
      Q(18) => u_PWM_SS_3L_ip_axi_lite_module_inst_n_16,
      Q(17) => u_PWM_SS_3L_ip_axi_lite_module_inst_n_17,
      Q(16) => u_PWM_SS_3L_ip_axi_lite_module_inst_n_18,
      Q(15) => u_PWM_SS_3L_ip_axi_lite_module_inst_n_19,
      Q(14) => u_PWM_SS_3L_ip_axi_lite_module_inst_n_20,
      Q(13) => u_PWM_SS_3L_ip_axi_lite_module_inst_n_21,
      Q(12) => u_PWM_SS_3L_ip_axi_lite_module_inst_n_22,
      Q(11) => u_PWM_SS_3L_ip_axi_lite_module_inst_n_23,
      Q(10) => u_PWM_SS_3L_ip_axi_lite_module_inst_n_24,
      Q(9) => u_PWM_SS_3L_ip_axi_lite_module_inst_n_25,
      Q(8) => u_PWM_SS_3L_ip_axi_lite_module_inst_n_26,
      Q(7) => u_PWM_SS_3L_ip_axi_lite_module_inst_n_27,
      Q(6) => u_PWM_SS_3L_ip_axi_lite_module_inst_n_28,
      Q(5) => u_PWM_SS_3L_ip_axi_lite_module_inst_n_29,
      Q(4) => u_PWM_SS_3L_ip_axi_lite_module_inst_n_30,
      Q(3) => u_PWM_SS_3L_ip_axi_lite_module_inst_n_31,
      Q(2) => u_PWM_SS_3L_ip_axi_lite_module_inst_n_32,
      Q(1) => u_PWM_SS_3L_ip_axi_lite_module_inst_n_33,
      Q(0) => u_PWM_SS_3L_ip_axi_lite_module_inst_n_34,
      RSTP => RSTP,
      \data_reg_Mode_AXI_1_1_reg[1]_0\(1 downto 0) => \data_reg_Mode_AXI_1_1_reg[1]\(1 downto 0),
      \data_reg_Mode_AXI_1_1_reg[1]_1\(0) => reg_enb_Mode_AXI_1_1,
      \data_reg_PWM_counter_max_value_int_AXI_1_1_reg[19]_0\(19 downto 0) => \data_reg_PWM_counter_max_value_int_AXI_1_1_reg[19]\(19 downto 0),
      data_reg_PWM_en_AXI_1_1_reg_0 => u_PWM_SS_3L_ip_axi_lite_module_inst_n_38,
      \data_reg_PWM_min_pulse_width_0to1_AXI_1_1_reg[13]_0\(13 downto 0) => \data_reg_PWM_min_pulse_width_0to1_AXI_1_1_reg[13]\(13 downto 0),
      \data_reg_PWM_min_pulse_width_0to1_AXI_1_1_reg[13]_1\(0) => reg_enb_PWM_min_pulse_width_0to1_AXI_1_1,
      \data_reg_TriState_HB1_AXI_1_1_reg[1]_0\(1 downto 0) => \data_reg_TriState_HB1_AXI_1_1_reg[1]\(1 downto 0),
      \data_reg_TriState_HB1_AXI_1_1_reg[1]_1\(0) => reg_enb_TriState_HB1_AXI_1_1,
      \data_reg_TriState_HB2_AXI_1_1_reg[1]_0\(1 downto 0) => \data_reg_TriState_HB2_AXI_1_1_reg[1]\(1 downto 0),
      \data_reg_TriState_HB2_AXI_1_1_reg[1]_1\(0) => reg_enb_TriState_HB2_AXI_1_1,
      \data_reg_TriState_HB3_AXI_1_1_reg[1]_0\(1 downto 0) => \data_reg_TriState_HB3_AXI_1_1_reg[1]\(1 downto 0),
      \data_reg_TriState_HB3_AXI_1_1_reg[1]_1\(0) => reg_enb_TriState_HB3_AXI_1_1,
      data_reg_axi_enable_1_1_reg_0 => data_reg_axi_enable_1_1_reg,
      data_reg_axi_enable_1_1_reg_1 => u_PWM_SS_3L_ip_axi_lite_module_inst_n_37,
      \data_reg_m_u1_norm_AXI_1_1_reg[13]_0\(13 downto 0) => \data_reg_m_u1_norm_AXI_1_1_reg[13]\(13 downto 0),
      \data_reg_m_u1_norm_AXI_1_1_reg[13]_1\(0) => reg_enb_m_u1_norm_AXI_1_1,
      \data_reg_m_u2_norm_AXI_1_1_reg[13]_0\(13 downto 0) => \data_reg_m_u2_norm_AXI_1_1_reg[13]\(13 downto 0),
      \data_reg_m_u2_norm_AXI_1_1_reg[13]_1\(0) => reg_enb_m_u2_norm_AXI_1_1,
      \data_reg_m_u3_norm_AXI_1_1_reg[13]_0\(13 downto 0) => \data_reg_m_u3_norm_AXI_1_1_reg[13]\(13 downto 0),
      \data_reg_m_u3_norm_AXI_1_1_reg[13]_1\(0) => reg_enb_m_u3_norm_AXI_1_1,
      read_reg_ip_timestamp(0) => read_reg_ip_timestamp(30),
      write_PWM_en_AXI => \^write_pwm_en_axi\
    );
u_PWM_SS_3L_ip_axi_lite_module_inst: entity work.zusys_PWM_SS_3L_ip_0_0_PWM_SS_3L_ip_axi_lite_module
     port map (
      AXI4_Lite_ACLK => AXI4_Lite_ACLK,
      AXI4_Lite_ARADDR(13 downto 0) => AXI4_Lite_ARADDR(13 downto 0),
      \AXI4_Lite_ARADDR[3]\(0) => reg_enb_m_u3_norm_AXI_1_1,
      \AXI4_Lite_ARADDR[3]_0\(0) => reg_enb_m_u2_norm_AXI_1_1,
      \AXI4_Lite_ARADDR[3]_1\(0) => reg_enb_m_u1_norm_AXI_1_1,
      \AXI4_Lite_ARADDR[3]_2\(0) => reg_enb_PWM_min_pulse_width_0to1_AXI_1_1,
      \AXI4_Lite_ARADDR[3]_3\(0) => reg_enb_TriState_HB3_AXI_1_1,
      \AXI4_Lite_ARADDR[6]\(0) => reg_enb_TriState_HB1_AXI_1_1,
      \AXI4_Lite_ARADDR[6]_0\(0) => reg_enb_TriState_HB2_AXI_1_1,
      \AXI4_Lite_ARADDR[6]_1\(0) => reg_enb_Mode_AXI_1_1,
      AXI4_Lite_ARESETN => AXI4_Lite_ARESETN,
      AXI4_Lite_ARREADY => AXI4_Lite_ARREADY,
      AXI4_Lite_ARVALID => AXI4_Lite_ARVALID,
      AXI4_Lite_AWADDR(13 downto 0) => AXI4_Lite_AWADDR(13 downto 0),
      AXI4_Lite_AWREADY => AXI4_Lite_AWREADY,
      AXI4_Lite_AWVALID => AXI4_Lite_AWVALID,
      AXI4_Lite_BREADY => AXI4_Lite_BREADY,
      AXI4_Lite_RDATA(0) => AXI4_Lite_RDATA(0),
      AXI4_Lite_RREADY => AXI4_Lite_RREADY,
      AXI4_Lite_WDATA(19 downto 0) => AXI4_Lite_WDATA(19 downto 0),
      AXI4_Lite_WSTRB(3 downto 0) => AXI4_Lite_WSTRB(3 downto 0),
      AXI4_Lite_WVALID => AXI4_Lite_WVALID,
      CEP => \^cep\,
      E(0) => reg_enb_PWM_counter_max_value_int_AXI_1_1,
      \FSM_onehot_axi_lite_wstate_reg[2]_0\(1 downto 0) => Q(1 downto 0),
      FSM_sequential_axi_lite_rstate_reg_0 => FSM_sequential_axi_lite_rstate_reg,
      IPCORE_RESETN => IPCORE_RESETN,
      Q(19) => u_PWM_SS_3L_ip_axi_lite_module_inst_n_15,
      Q(18) => u_PWM_SS_3L_ip_axi_lite_module_inst_n_16,
      Q(17) => u_PWM_SS_3L_ip_axi_lite_module_inst_n_17,
      Q(16) => u_PWM_SS_3L_ip_axi_lite_module_inst_n_18,
      Q(15) => u_PWM_SS_3L_ip_axi_lite_module_inst_n_19,
      Q(14) => u_PWM_SS_3L_ip_axi_lite_module_inst_n_20,
      Q(13) => u_PWM_SS_3L_ip_axi_lite_module_inst_n_21,
      Q(12) => u_PWM_SS_3L_ip_axi_lite_module_inst_n_22,
      Q(11) => u_PWM_SS_3L_ip_axi_lite_module_inst_n_23,
      Q(10) => u_PWM_SS_3L_ip_axi_lite_module_inst_n_24,
      Q(9) => u_PWM_SS_3L_ip_axi_lite_module_inst_n_25,
      Q(8) => u_PWM_SS_3L_ip_axi_lite_module_inst_n_26,
      Q(7) => u_PWM_SS_3L_ip_axi_lite_module_inst_n_27,
      Q(6) => u_PWM_SS_3L_ip_axi_lite_module_inst_n_28,
      Q(5) => u_PWM_SS_3L_ip_axi_lite_module_inst_n_29,
      Q(4) => u_PWM_SS_3L_ip_axi_lite_module_inst_n_30,
      Q(3) => u_PWM_SS_3L_ip_axi_lite_module_inst_n_31,
      Q(2) => u_PWM_SS_3L_ip_axi_lite_module_inst_n_32,
      Q(1) => u_PWM_SS_3L_ip_axi_lite_module_inst_n_33,
      Q(0) => u_PWM_SS_3L_ip_axi_lite_module_inst_n_34,
      read_reg_ip_timestamp(0) => read_reg_ip_timestamp(30),
      reset_in => reset_in,
      soft_reset => soft_reset,
      \wdata_reg[0]_0\ => u_PWM_SS_3L_ip_axi_lite_module_inst_n_37,
      \wdata_reg[0]_1\ => u_PWM_SS_3L_ip_axi_lite_module_inst_n_38,
      write_PWM_en_AXI => \^write_pwm_en_axi\
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity zusys_PWM_SS_3L_ip_0_0_PWM_SS_3L_ip_src_GenPWM is
  port (
    PWM_en_AXI_2_reg_0 : out STD_LOGIC;
    D : out STD_LOGIC_VECTOR ( 0 to 0 );
    GenPWM_out5 : out STD_LOGIC;
    Q : out STD_LOGIC_VECTOR ( 1 downto 0 );
    \Switch4_out1_1_reg[0]_0\ : out STD_LOGIC_VECTOR ( 1 downto 0 );
    \Switch5_out1_1_reg[0]_0\ : out STD_LOGIC_VECTOR ( 1 downto 0 );
    Demux_out1 : out STD_LOGIC_VECTOR ( 0 to 1 );
    Demux_out2 : out STD_LOGIC_VECTOR ( 0 to 1 );
    Demux_out3 : out STD_LOGIC_VECTOR ( 0 to 1 );
    RSTP : in STD_LOGIC;
    CEP : in STD_LOGIC;
    IPCORE_CLK : in STD_LOGIC;
    write_PWM_en_AXI : in STD_LOGIC;
    \HDL_Counter2_count_reg[19]_0\ : in STD_LOGIC;
    \max_counter_value_1_reg[19]_0\ : in STD_LOGIC_VECTOR ( 19 downto 0 );
    \maximum_counter_value_1_reg[8]_0\ : in STD_LOGIC;
    \delayMatch1_reg_reg[0][13]_0\ : in STD_LOGIC_VECTOR ( 13 downto 0 );
    \min_pulse_width_AXI_1_reg[13]_0\ : in STD_LOGIC_VECTOR ( 13 downto 0 );
    \delayMatch3_reg_reg[0][13]_0\ : in STD_LOGIC_VECTOR ( 13 downto 0 );
    \delayMatch5_reg_reg[0][13]_0\ : in STD_LOGIC_VECTOR ( 13 downto 0 );
    Mux_out1 : in STD_LOGIC_VECTOR ( 0 to 5 );
    delayMatch_1_reg : in STD_LOGIC_VECTOR ( 0 to 0 );
    delayMatch_1_reg_1 : in STD_LOGIC_VECTOR ( 0 to 0 );
    delayMatch3_1_reg : in STD_LOGIC_VECTOR ( 0 to 0 );
    delayMatch3_1_reg_1 : in STD_LOGIC_VECTOR ( 0 to 0 );
    delayMatch6_1_reg : in STD_LOGIC_VECTOR ( 0 to 0 );
    delayMatch6_1_reg_1 : in STD_LOGIC_VECTOR ( 0 to 0 )
  );
  attribute ORIG_REF_NAME : string;
  attribute ORIG_REF_NAME of zusys_PWM_SS_3L_ip_0_0_PWM_SS_3L_ip_src_GenPWM : entity is "PWM_SS_3L_ip_src_GenPWM";
end zusys_PWM_SS_3L_ip_0_0_PWM_SS_3L_ip_src_GenPWM;

architecture STRUCTURE of zusys_PWM_SS_3L_ip_0_0_PWM_SS_3L_ip_src_GenPWM is
  signal Counter_Ctrl_out3 : STD_LOGIC_VECTOR ( 20 downto 0 );
  signal Counter_Ctrl_out4 : STD_LOGIC;
  signal Counter_Ctrl_out5 : STD_LOGIC;
  signal Delay1_out1 : STD_LOGIC_VECTOR ( 13 downto 0 );
  signal \Delay1_out1[0]_i_1_n_0\ : STD_LOGIC;
  signal \Delay1_out1[10]_i_1_n_0\ : STD_LOGIC;
  signal \Delay1_out1[12]_i_1_n_0\ : STD_LOGIC;
  signal \Delay1_out1[2]_i_1_n_0\ : STD_LOGIC;
  signal \Delay1_out1[4]_i_1_n_0\ : STD_LOGIC;
  signal \Delay1_out1[6]_i_1_n_0\ : STD_LOGIC;
  signal \Delay1_out1[8]_i_1_n_0\ : STD_LOGIC;
  signal Delay2_out1 : STD_LOGIC_VECTOR ( 13 downto 0 );
  signal \Delay2_out1[0]_i_1_n_0\ : STD_LOGIC;
  signal \Delay2_out1[10]_i_1_n_0\ : STD_LOGIC;
  signal \Delay2_out1[12]_i_1_n_0\ : STD_LOGIC;
  signal \Delay2_out1[2]_i_1_n_0\ : STD_LOGIC;
  signal \Delay2_out1[4]_i_1_n_0\ : STD_LOGIC;
  signal \Delay2_out1[6]_i_1_n_0\ : STD_LOGIC;
  signal \Delay2_out1[8]_i_1_n_0\ : STD_LOGIC;
  signal Delay_out1 : STD_LOGIC_VECTOR ( 13 downto 0 );
  signal \Delay_out1[0]_i_1_n_0\ : STD_LOGIC;
  signal \Delay_out1[10]_i_1_n_0\ : STD_LOGIC;
  signal \Delay_out1[12]_i_1_n_0\ : STD_LOGIC;
  signal \Delay_out1[2]_i_1_n_0\ : STD_LOGIC;
  signal \Delay_out1[4]_i_1_n_0\ : STD_LOGIC;
  signal \Delay_out1[6]_i_1_n_0\ : STD_LOGIC;
  signal \Delay_out1[8]_i_1_n_0\ : STD_LOGIC;
  signal \^genpwm_out5\ : STD_LOGIC;
  signal HDL_Counter2_count_reg : STD_LOGIC_VECTOR ( 19 downto 0 );
  signal LimitPulseWidth_a_out1 : STD_LOGIC_VECTOR ( 13 downto 0 );
  signal LimitPulseWidth_b_out1 : STD_LOGIC_VECTOR ( 13 downto 0 );
  signal LimitPulseWidth_c_out1 : STD_LOGIC_VECTOR ( 13 downto 0 );
  signal Modulator_a_out1 : STD_LOGIC_VECTOR ( 1 to 1 );
  signal Modulator_b_out1 : STD_LOGIC_VECTOR ( 1 to 1 );
  signal Modulator_c_out1 : STD_LOGIC_VECTOR ( 1 to 1 );
  signal \OR_out1__0\ : STD_LOGIC;
  signal PWM_en_AXI_1 : STD_LOGIC;
  signal \^pwm_en_axi_2_reg_0\ : STD_LOGIC;
  signal Saturation1_out110_in : STD_LOGIC;
  signal Switch5_out1_1 : STD_LOGIC;
  signal \delayMatch1_reg_reg[0]_0\ : STD_LOGIC_VECTOR ( 13 downto 0 );
  signal \delayMatch1_reg_reg[1]_1\ : STD_LOGIC_VECTOR ( 13 downto 0 );
  signal \delayMatch3_reg_reg[0]_2\ : STD_LOGIC_VECTOR ( 13 downto 0 );
  signal \delayMatch3_reg_reg[1]_3\ : STD_LOGIC_VECTOR ( 13 downto 0 );
  signal \delayMatch5_reg_reg[0]_4\ : STD_LOGIC_VECTOR ( 13 downto 0 );
  signal \delayMatch5_reg_reg[1]_5\ : STD_LOGIC_VECTOR ( 13 downto 0 );
  signal max_counter_value_1 : STD_LOGIC_VECTOR ( 19 downto 0 );
  signal maximum_counter_value10_in : STD_LOGIC;
  signal \maximum_counter_value1__14\ : STD_LOGIC;
  signal maximum_counter_value_1 : STD_LOGIC_VECTOR ( 19 downto 0 );
  signal \maximum_counter_value_1[13]_i_1_n_0\ : STD_LOGIC;
  signal \maximum_counter_value_1[15]_i_1_n_0\ : STD_LOGIC;
  signal \maximum_counter_value_1[16]_i_1_n_0\ : STD_LOGIC;
  signal \maximum_counter_value_1[17]_i_1_n_0\ : STD_LOGIC;
  signal \maximum_counter_value_1[18]_i_1_n_0\ : STD_LOGIC;
  signal \maximum_counter_value_1[18]_i_2_n_0\ : STD_LOGIC;
  signal \maximum_counter_value_1[18]_i_3_n_0\ : STD_LOGIC;
  signal \maximum_counter_value_1[19]_i_1_n_0\ : STD_LOGIC;
  signal \maximum_counter_value_1[2]_i_1_n_0\ : STD_LOGIC;
  signal \maximum_counter_value_1[4]_i_1_n_0\ : STD_LOGIC;
  signal \maximum_counter_value_1[6]_i_1_n_0\ : STD_LOGIC;
  signal \maximum_counter_value_1[7]_i_1_n_0\ : STD_LOGIC;
  signal \maximum_counter_value_1[7]_i_2_n_0\ : STD_LOGIC;
  signal \maximum_counter_value_1[8]_i_10_n_0\ : STD_LOGIC;
  signal \maximum_counter_value_1[8]_i_11_n_0\ : STD_LOGIC;
  signal \maximum_counter_value_1[8]_i_12_n_0\ : STD_LOGIC;
  signal \maximum_counter_value_1[8]_i_5_n_0\ : STD_LOGIC;
  signal \maximum_counter_value_1[8]_i_6_n_0\ : STD_LOGIC;
  signal \maximum_counter_value_1[8]_i_7_n_0\ : STD_LOGIC;
  signal \maximum_counter_value_1[8]_i_8_n_0\ : STD_LOGIC;
  signal \maximum_counter_value_1[8]_i_9_n_0\ : STD_LOGIC;
  signal min_pulse_width : STD_LOGIC_VECTOR ( 13 downto 0 );
  signal \minus_out1_1[13]_i_10_n_0\ : STD_LOGIC;
  signal \minus_out1_1[13]_i_11_n_0\ : STD_LOGIC;
  signal \minus_out1_1[13]_i_12_n_0\ : STD_LOGIC;
  signal \minus_out1_1[13]_i_13_n_0\ : STD_LOGIC;
  signal \minus_out1_1[13]_i_14_n_0\ : STD_LOGIC;
  signal \minus_out1_1[13]_i_15_n_0\ : STD_LOGIC;
  signal \minus_out1_1[13]_i_3_n_0\ : STD_LOGIC;
  signal \minus_out1_1[13]_i_4_n_0\ : STD_LOGIC;
  signal \minus_out1_1[13]_i_5_n_0\ : STD_LOGIC;
  signal \minus_out1_1[13]_i_6_n_0\ : STD_LOGIC;
  signal \minus_out1_1[13]_i_7_n_0\ : STD_LOGIC;
  signal \minus_out1_1[13]_i_8__1_n_0\ : STD_LOGIC;
  signal \minus_out1_1[13]_i_9__0_n_0\ : STD_LOGIC;
  signal \minus_out1_1_reg[13]_i_2__0_n_2\ : STD_LOGIC;
  signal \minus_out1_1_reg[13]_i_2__0_n_3\ : STD_LOGIC;
  signal \minus_out1_1_reg[13]_i_2__0_n_4\ : STD_LOGIC;
  signal \minus_out1_1_reg[13]_i_2__0_n_5\ : STD_LOGIC;
  signal \minus_out1_1_reg[13]_i_2__0_n_6\ : STD_LOGIC;
  signal \minus_out1_1_reg[13]_i_2__0_n_7\ : STD_LOGIC;
  signal \modulating_signal_in_clock_cycles_1_reg__0\ : STD_LOGIC_VECTOR ( 20 downto 0 );
  signal \modulating_signal_in_clock_cycles_1_reg__0_0\ : STD_LOGIC_VECTOR ( 20 downto 0 );
  signal p_1_in : STD_LOGIC_VECTOR ( 8 downto 5 );
  signal reduced_reg : STD_LOGIC_VECTOR ( 1 to 1 );
  signal \reduced_reg_1_reg[1]_9\ : STD_LOGIC_VECTOR ( 20 downto 0 );
  signal \reduced_reg__0\ : STD_LOGIC_VECTOR ( 0 to 0 );
  signal u_Counter_Ctrl_n_22 : STD_LOGIC;
  signal u_Counter_Ctrl_n_23 : STD_LOGIC;
  signal u_Counter_Ctrl_n_24 : STD_LOGIC;
  signal u_Counter_Ctrl_n_25 : STD_LOGIC;
  signal u_Counter_Ctrl_n_26 : STD_LOGIC;
  signal u_Counter_Ctrl_n_27 : STD_LOGIC;
  signal u_Counter_Ctrl_n_28 : STD_LOGIC;
  signal u_Counter_Ctrl_n_29 : STD_LOGIC;
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
  signal u_Counter_Ctrl_n_40 : STD_LOGIC;
  signal u_Counter_Ctrl_n_41 : STD_LOGIC;
  signal u_LimitPulseWidth_a_n_0 : STD_LOGIC;
  signal u_LimitPulseWidth_a_n_1 : STD_LOGIC;
  signal u_LimitPulseWidth_a_n_17 : STD_LOGIC;
  signal u_LimitPulseWidth_a_n_18 : STD_LOGIC;
  signal u_LimitPulseWidth_a_n_19 : STD_LOGIC;
  signal u_LimitPulseWidth_a_n_20 : STD_LOGIC;
  signal u_LimitPulseWidth_a_n_21 : STD_LOGIC;
  signal u_LimitPulseWidth_a_n_22 : STD_LOGIC;
  signal u_LimitPulseWidth_a_n_23 : STD_LOGIC;
  signal u_LimitPulseWidth_a_n_24 : STD_LOGIC;
  signal u_LimitPulseWidth_a_n_25 : STD_LOGIC;
  signal u_LimitPulseWidth_a_n_26 : STD_LOGIC;
  signal u_LimitPulseWidth_a_n_27 : STD_LOGIC;
  signal u_LimitPulseWidth_a_n_28 : STD_LOGIC;
  signal u_LimitPulseWidth_a_n_29 : STD_LOGIC;
  signal u_LimitPulseWidth_b_n_0 : STD_LOGIC;
  signal u_LimitPulseWidth_b_n_1 : STD_LOGIC;
  signal u_LimitPulseWidth_b_n_16 : STD_LOGIC;
  signal u_LimitPulseWidth_b_n_17 : STD_LOGIC;
  signal u_LimitPulseWidth_b_n_18 : STD_LOGIC;
  signal u_LimitPulseWidth_b_n_19 : STD_LOGIC;
  signal u_LimitPulseWidth_b_n_20 : STD_LOGIC;
  signal u_LimitPulseWidth_b_n_21 : STD_LOGIC;
  signal u_LimitPulseWidth_c_n_0 : STD_LOGIC;
  signal u_LimitPulseWidth_c_n_1 : STD_LOGIC;
  signal u_LimitPulseWidth_c_n_17 : STD_LOGIC;
  signal u_LimitPulseWidth_c_n_18 : STD_LOGIC;
  signal u_LimitPulseWidth_c_n_19 : STD_LOGIC;
  signal u_LimitPulseWidth_c_n_2 : STD_LOGIC;
  signal u_LimitPulseWidth_c_n_20 : STD_LOGIC;
  signal u_LimitPulseWidth_c_n_21 : STD_LOGIC;
  signal u_LimitPulseWidth_c_n_22 : STD_LOGIC;
  signal u_LimitPulseWidth_c_n_23 : STD_LOGIC;
  signal u_LimitPulseWidth_c_n_24 : STD_LOGIC;
  signal u_LimitPulseWidth_c_n_25 : STD_LOGIC;
  signal u_LimitPulseWidth_c_n_26 : STD_LOGIC;
  signal u_LimitPulseWidth_c_n_27 : STD_LOGIC;
  signal u_LimitPulseWidth_c_n_28 : STD_LOGIC;
  signal u_LimitPulseWidth_c_n_29 : STD_LOGIC;
  signal u_LimitPulseWidth_c_n_30 : STD_LOGIC;
  signal u_LimitPulseWidth_c_n_31 : STD_LOGIC;
  signal u_LimitPulseWidth_c_n_32 : STD_LOGIC;
  signal u_LimitPulseWidth_c_n_33 : STD_LOGIC;
  signal u_LimitPulseWidth_c_n_34 : STD_LOGIC;
  signal u_Modulator_a_n_21 : STD_LOGIC;
  signal u_Modulator_a_n_23 : STD_LOGIC;
  signal u_Modulator_a_n_24 : STD_LOGIC;
  signal u_Modulator_a_n_25 : STD_LOGIC;
  signal u_Modulator_a_n_26 : STD_LOGIC;
  signal u_Modulator_a_n_27 : STD_LOGIC;
  signal u_Modulator_a_n_28 : STD_LOGIC;
  signal u_Modulator_a_n_29 : STD_LOGIC;
  signal u_Modulator_a_n_30 : STD_LOGIC;
  signal u_Modulator_a_n_31 : STD_LOGIC;
  signal u_Modulator_a_n_32 : STD_LOGIC;
  signal u_Modulator_a_n_33 : STD_LOGIC;
  signal u_Modulator_a_n_34 : STD_LOGIC;
  signal u_Modulator_a_n_35 : STD_LOGIC;
  signal u_Modulator_a_n_36 : STD_LOGIC;
  signal u_Modulator_a_n_37 : STD_LOGIC;
  signal u_Modulator_a_n_38 : STD_LOGIC;
  signal u_Modulator_a_n_39 : STD_LOGIC;
  signal u_Modulator_a_n_40 : STD_LOGIC;
  signal u_Modulator_a_n_41 : STD_LOGIC;
  signal u_Modulator_a_n_42 : STD_LOGIC;
  signal u_Modulator_a_n_43 : STD_LOGIC;
  signal u_Modulator_a_n_44 : STD_LOGIC;
  signal u_Modulator_a_n_45 : STD_LOGIC;
  signal u_Modulator_a_n_46 : STD_LOGIC;
  signal u_Modulator_a_n_47 : STD_LOGIC;
  signal u_Modulator_a_n_48 : STD_LOGIC;
  signal u_Modulator_a_n_49 : STD_LOGIC;
  signal u_Modulator_a_n_50 : STD_LOGIC;
  signal u_Modulator_a_n_51 : STD_LOGIC;
  signal u_Modulator_a_n_52 : STD_LOGIC;
  signal u_Modulator_a_n_53 : STD_LOGIC;
  signal u_Modulator_a_n_54 : STD_LOGIC;
  signal u_Modulator_a_n_55 : STD_LOGIC;
  signal u_Modulator_a_n_56 : STD_LOGIC;
  signal u_Modulator_a_n_57 : STD_LOGIC;
  signal u_Modulator_a_n_58 : STD_LOGIC;
  signal u_Modulator_a_n_59 : STD_LOGIC;
  signal u_Modulator_a_n_60 : STD_LOGIC;
  signal u_Modulator_a_n_61 : STD_LOGIC;
  signal u_Modulator_a_n_62 : STD_LOGIC;
  signal u_Modulator_a_n_63 : STD_LOGIC;
  signal u_Modulator_a_n_64 : STD_LOGIC;
  signal u_Modulator_a_n_65 : STD_LOGIC;
  signal u_Modulator_a_n_66 : STD_LOGIC;
  signal u_Modulator_a_n_67 : STD_LOGIC;
  signal u_Modulator_a_n_68 : STD_LOGIC;
  signal u_Modulator_b_n_21 : STD_LOGIC;
  signal u_Modulator_c_n_21 : STD_LOGIC;
  signal \NLW_minus_out1_1_reg[13]_i_2__0_CO_UNCONNECTED\ : STD_LOGIC_VECTOR ( 7 to 7 );
  signal \NLW_minus_out1_1_reg[13]_i_2__0_O_UNCONNECTED\ : STD_LOGIC_VECTOR ( 7 downto 0 );
  attribute SOFT_HLUTNM : string;
  attribute SOFT_HLUTNM of \Delay1_out1[10]_i_1\ : label is "soft_lutpair60";
  attribute SOFT_HLUTNM of \Delay1_out1[12]_i_1\ : label is "soft_lutpair60";
  attribute SOFT_HLUTNM of \Delay1_out1[2]_i_1\ : label is "soft_lutpair62";
  attribute SOFT_HLUTNM of \Delay1_out1[4]_i_1\ : label is "soft_lutpair62";
  attribute SOFT_HLUTNM of \Delay1_out1[6]_i_1\ : label is "soft_lutpair61";
  attribute SOFT_HLUTNM of \Delay1_out1[8]_i_1\ : label is "soft_lutpair61";
  attribute SOFT_HLUTNM of \Delay2_out1[10]_i_1\ : label is "soft_lutpair57";
  attribute SOFT_HLUTNM of \Delay2_out1[12]_i_1\ : label is "soft_lutpair57";
  attribute SOFT_HLUTNM of \Delay2_out1[2]_i_1\ : label is "soft_lutpair59";
  attribute SOFT_HLUTNM of \Delay2_out1[4]_i_1\ : label is "soft_lutpair59";
  attribute SOFT_HLUTNM of \Delay2_out1[6]_i_1\ : label is "soft_lutpair58";
  attribute SOFT_HLUTNM of \Delay2_out1[8]_i_1\ : label is "soft_lutpair58";
  attribute SOFT_HLUTNM of \Delay_out1[10]_i_1\ : label is "soft_lutpair63";
  attribute SOFT_HLUTNM of \Delay_out1[12]_i_1\ : label is "soft_lutpair63";
  attribute SOFT_HLUTNM of \Delay_out1[2]_i_1\ : label is "soft_lutpair65";
  attribute SOFT_HLUTNM of \Delay_out1[4]_i_1\ : label is "soft_lutpair65";
  attribute SOFT_HLUTNM of \Delay_out1[6]_i_1\ : label is "soft_lutpair64";
  attribute SOFT_HLUTNM of \Delay_out1[8]_i_1\ : label is "soft_lutpair64";
  attribute SOFT_HLUTNM of \delayMatch3_1_reg[0]_i_1\ : label is "soft_lutpair69";
  attribute SOFT_HLUTNM of \delayMatch3_1_reg_1[0]_i_1\ : label is "soft_lutpair69";
  attribute SOFT_HLUTNM of \delayMatch6_1_reg[0]_i_1\ : label is "soft_lutpair70";
  attribute SOFT_HLUTNM of \delayMatch6_1_reg_1[0]_i_1\ : label is "soft_lutpair70";
  attribute SOFT_HLUTNM of \delayMatch_1_reg[0]_i_1\ : label is "soft_lutpair68";
  attribute SOFT_HLUTNM of \delayMatch_1_reg_1[0]_i_1\ : label is "soft_lutpair68";
  attribute SOFT_HLUTNM of \maximum_counter_value_1[13]_i_1\ : label is "soft_lutpair71";
  attribute SOFT_HLUTNM of \maximum_counter_value_1[15]_i_1\ : label is "soft_lutpair55";
  attribute SOFT_HLUTNM of \maximum_counter_value_1[16]_i_1\ : label is "soft_lutpair56";
  attribute SOFT_HLUTNM of \maximum_counter_value_1[17]_i_1\ : label is "soft_lutpair71";
  attribute SOFT_HLUTNM of \maximum_counter_value_1[2]_i_1\ : label is "soft_lutpair66";
  attribute SOFT_HLUTNM of \maximum_counter_value_1[4]_i_1\ : label is "soft_lutpair66";
  attribute SOFT_HLUTNM of \maximum_counter_value_1[5]_i_1\ : label is "soft_lutpair54";
  attribute SOFT_HLUTNM of \maximum_counter_value_1[6]_i_1\ : label is "soft_lutpair67";
  attribute SOFT_HLUTNM of \maximum_counter_value_1[7]_i_2\ : label is "soft_lutpair67";
  attribute SOFT_HLUTNM of \maximum_counter_value_1[8]_i_11\ : label is "soft_lutpair53";
  attribute SOFT_HLUTNM of \maximum_counter_value_1[8]_i_12\ : label is "soft_lutpair55";
  attribute SOFT_HLUTNM of \maximum_counter_value_1[8]_i_2\ : label is "soft_lutpair54";
  attribute SOFT_HLUTNM of \maximum_counter_value_1[8]_i_4\ : label is "soft_lutpair53";
  attribute SOFT_HLUTNM of \maximum_counter_value_1[8]_i_7\ : label is "soft_lutpair56";
  attribute COMPARATOR_THRESHOLD : integer;
  attribute COMPARATOR_THRESHOLD of \minus_out1_1_reg[13]_i_2__0\ : label is 11;
begin
  GenPWM_out5 <= \^genpwm_out5\;
  PWM_en_AXI_2_reg_0 <= \^pwm_en_axi_2_reg_0\;
Counter_Ctrl_out4_1_reg: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => Counter_Ctrl_out4,
      Q => D(0),
      R => RSTP
    );
Counter_Ctrl_out5_1_i_1: unisim.vcomponents.LUT5
    generic map(
      INIT => X"40000000"
    )
        port map (
      I0 => HDL_Counter2_count_reg(19),
      I1 => \^pwm_en_axi_2_reg_0\,
      I2 => u_LimitPulseWidth_c_n_23,
      I3 => u_LimitPulseWidth_c_n_25,
      I4 => u_LimitPulseWidth_a_n_24,
      O => Counter_Ctrl_out5
    );
Counter_Ctrl_out5_1_reg: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => Counter_Ctrl_out5,
      Q => \^genpwm_out5\,
      R => RSTP
    );
\Delay1_out1[0]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"B8"
    )
        port map (
      I0 => \delayMatch3_reg_reg[1]_3\(0),
      I1 => u_LimitPulseWidth_b_n_1,
      I2 => Delay1_out1(0),
      O => \Delay1_out1[0]_i_1_n_0\
    );
\Delay1_out1[10]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"B8"
    )
        port map (
      I0 => \delayMatch3_reg_reg[1]_3\(10),
      I1 => u_LimitPulseWidth_b_n_1,
      I2 => Delay1_out1(10),
      O => \Delay1_out1[10]_i_1_n_0\
    );
\Delay1_out1[12]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"B8"
    )
        port map (
      I0 => \delayMatch3_reg_reg[1]_3\(12),
      I1 => u_LimitPulseWidth_b_n_1,
      I2 => Delay1_out1(12),
      O => \Delay1_out1[12]_i_1_n_0\
    );
\Delay1_out1[2]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"B8"
    )
        port map (
      I0 => \delayMatch3_reg_reg[1]_3\(2),
      I1 => u_LimitPulseWidth_b_n_1,
      I2 => Delay1_out1(2),
      O => \Delay1_out1[2]_i_1_n_0\
    );
\Delay1_out1[4]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"B8"
    )
        port map (
      I0 => \delayMatch3_reg_reg[1]_3\(4),
      I1 => u_LimitPulseWidth_b_n_1,
      I2 => Delay1_out1(4),
      O => \Delay1_out1[4]_i_1_n_0\
    );
\Delay1_out1[6]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"B8"
    )
        port map (
      I0 => \delayMatch3_reg_reg[1]_3\(6),
      I1 => u_LimitPulseWidth_b_n_1,
      I2 => Delay1_out1(6),
      O => \Delay1_out1[6]_i_1_n_0\
    );
\Delay1_out1[8]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"B8"
    )
        port map (
      I0 => \delayMatch3_reg_reg[1]_3\(8),
      I1 => u_LimitPulseWidth_b_n_1,
      I2 => Delay1_out1(8),
      O => \Delay1_out1[8]_i_1_n_0\
    );
\Delay1_out1_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \Delay1_out1[0]_i_1_n_0\,
      Q => Delay1_out1(0),
      R => RSTP
    );
\Delay1_out1_reg[10]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \Delay1_out1[10]_i_1_n_0\,
      Q => Delay1_out1(10),
      R => RSTP
    );
\Delay1_out1_reg[11]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => u_LimitPulseWidth_b_n_16,
      Q => Delay1_out1(11),
      R => RSTP
    );
\Delay1_out1_reg[12]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \Delay1_out1[12]_i_1_n_0\,
      Q => Delay1_out1(12),
      R => RSTP
    );
\Delay1_out1_reg[13]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => u_LimitPulseWidth_b_n_0,
      Q => Delay1_out1(13),
      R => RSTP
    );
\Delay1_out1_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => u_LimitPulseWidth_b_n_21,
      Q => Delay1_out1(1),
      R => RSTP
    );
\Delay1_out1_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \Delay1_out1[2]_i_1_n_0\,
      Q => Delay1_out1(2),
      R => RSTP
    );
\Delay1_out1_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => u_LimitPulseWidth_b_n_20,
      Q => Delay1_out1(3),
      R => RSTP
    );
\Delay1_out1_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \Delay1_out1[4]_i_1_n_0\,
      Q => Delay1_out1(4),
      R => RSTP
    );
\Delay1_out1_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => u_LimitPulseWidth_b_n_19,
      Q => Delay1_out1(5),
      R => RSTP
    );
\Delay1_out1_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \Delay1_out1[6]_i_1_n_0\,
      Q => Delay1_out1(6),
      R => RSTP
    );
\Delay1_out1_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => u_LimitPulseWidth_b_n_18,
      Q => Delay1_out1(7),
      R => RSTP
    );
\Delay1_out1_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \Delay1_out1[8]_i_1_n_0\,
      Q => Delay1_out1(8),
      R => RSTP
    );
\Delay1_out1_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => u_LimitPulseWidth_b_n_17,
      Q => Delay1_out1(9),
      R => RSTP
    );
\Delay2_out1[0]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"B8"
    )
        port map (
      I0 => \delayMatch5_reg_reg[1]_5\(0),
      I1 => u_LimitPulseWidth_c_n_2,
      I2 => Delay2_out1(0),
      O => \Delay2_out1[0]_i_1_n_0\
    );
\Delay2_out1[10]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"B8"
    )
        port map (
      I0 => \delayMatch5_reg_reg[1]_5\(10),
      I1 => u_LimitPulseWidth_c_n_2,
      I2 => Delay2_out1(10),
      O => \Delay2_out1[10]_i_1_n_0\
    );
\Delay2_out1[12]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"B8"
    )
        port map (
      I0 => \delayMatch5_reg_reg[1]_5\(12),
      I1 => u_LimitPulseWidth_c_n_2,
      I2 => Delay2_out1(12),
      O => \Delay2_out1[12]_i_1_n_0\
    );
\Delay2_out1[2]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"B8"
    )
        port map (
      I0 => \delayMatch5_reg_reg[1]_5\(2),
      I1 => u_LimitPulseWidth_c_n_2,
      I2 => Delay2_out1(2),
      O => \Delay2_out1[2]_i_1_n_0\
    );
\Delay2_out1[4]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"B8"
    )
        port map (
      I0 => \delayMatch5_reg_reg[1]_5\(4),
      I1 => u_LimitPulseWidth_c_n_2,
      I2 => Delay2_out1(4),
      O => \Delay2_out1[4]_i_1_n_0\
    );
\Delay2_out1[6]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"B8"
    )
        port map (
      I0 => \delayMatch5_reg_reg[1]_5\(6),
      I1 => u_LimitPulseWidth_c_n_2,
      I2 => Delay2_out1(6),
      O => \Delay2_out1[6]_i_1_n_0\
    );
\Delay2_out1[8]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"B8"
    )
        port map (
      I0 => \delayMatch5_reg_reg[1]_5\(8),
      I1 => u_LimitPulseWidth_c_n_2,
      I2 => Delay2_out1(8),
      O => \Delay2_out1[8]_i_1_n_0\
    );
\Delay2_out1_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \Delay2_out1[0]_i_1_n_0\,
      Q => Delay2_out1(0),
      R => RSTP
    );
\Delay2_out1_reg[10]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \Delay2_out1[10]_i_1_n_0\,
      Q => Delay2_out1(10),
      R => RSTP
    );
\Delay2_out1_reg[11]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => u_LimitPulseWidth_c_n_17,
      Q => Delay2_out1(11),
      R => RSTP
    );
\Delay2_out1_reg[12]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \Delay2_out1[12]_i_1_n_0\,
      Q => Delay2_out1(12),
      R => RSTP
    );
\Delay2_out1_reg[13]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => u_LimitPulseWidth_c_n_1,
      Q => Delay2_out1(13),
      R => RSTP
    );
\Delay2_out1_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => u_LimitPulseWidth_c_n_22,
      Q => Delay2_out1(1),
      R => RSTP
    );
\Delay2_out1_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \Delay2_out1[2]_i_1_n_0\,
      Q => Delay2_out1(2),
      R => RSTP
    );
\Delay2_out1_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => u_LimitPulseWidth_c_n_21,
      Q => Delay2_out1(3),
      R => RSTP
    );
\Delay2_out1_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \Delay2_out1[4]_i_1_n_0\,
      Q => Delay2_out1(4),
      R => RSTP
    );
\Delay2_out1_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => u_LimitPulseWidth_c_n_20,
      Q => Delay2_out1(5),
      R => RSTP
    );
\Delay2_out1_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \Delay2_out1[6]_i_1_n_0\,
      Q => Delay2_out1(6),
      R => RSTP
    );
\Delay2_out1_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => u_LimitPulseWidth_c_n_19,
      Q => Delay2_out1(7),
      R => RSTP
    );
\Delay2_out1_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \Delay2_out1[8]_i_1_n_0\,
      Q => Delay2_out1(8),
      R => RSTP
    );
\Delay2_out1_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => u_LimitPulseWidth_c_n_18,
      Q => Delay2_out1(9),
      R => RSTP
    );
\Delay_out1[0]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"B8"
    )
        port map (
      I0 => \delayMatch1_reg_reg[1]_1\(0),
      I1 => \OR_out1__0\,
      I2 => Delay_out1(0),
      O => \Delay_out1[0]_i_1_n_0\
    );
\Delay_out1[10]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"B8"
    )
        port map (
      I0 => \delayMatch1_reg_reg[1]_1\(10),
      I1 => \OR_out1__0\,
      I2 => Delay_out1(10),
      O => \Delay_out1[10]_i_1_n_0\
    );
\Delay_out1[12]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"B8"
    )
        port map (
      I0 => \delayMatch1_reg_reg[1]_1\(12),
      I1 => \OR_out1__0\,
      I2 => Delay_out1(12),
      O => \Delay_out1[12]_i_1_n_0\
    );
\Delay_out1[2]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"B8"
    )
        port map (
      I0 => \delayMatch1_reg_reg[1]_1\(2),
      I1 => \OR_out1__0\,
      I2 => Delay_out1(2),
      O => \Delay_out1[2]_i_1_n_0\
    );
\Delay_out1[4]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"B8"
    )
        port map (
      I0 => \delayMatch1_reg_reg[1]_1\(4),
      I1 => \OR_out1__0\,
      I2 => Delay_out1(4),
      O => \Delay_out1[4]_i_1_n_0\
    );
\Delay_out1[6]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"B8"
    )
        port map (
      I0 => \delayMatch1_reg_reg[1]_1\(6),
      I1 => \OR_out1__0\,
      I2 => Delay_out1(6),
      O => \Delay_out1[6]_i_1_n_0\
    );
\Delay_out1[8]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"B8"
    )
        port map (
      I0 => \delayMatch1_reg_reg[1]_1\(8),
      I1 => \OR_out1__0\,
      I2 => Delay_out1(8),
      O => \Delay_out1[8]_i_1_n_0\
    );
\Delay_out1_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \Delay_out1[0]_i_1_n_0\,
      Q => Delay_out1(0),
      R => RSTP
    );
\Delay_out1_reg[10]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \Delay_out1[10]_i_1_n_0\,
      Q => Delay_out1(10),
      R => RSTP
    );
\Delay_out1_reg[11]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => u_LimitPulseWidth_a_n_18,
      Q => Delay_out1(11),
      R => RSTP
    );
\Delay_out1_reg[12]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \Delay_out1[12]_i_1_n_0\,
      Q => Delay_out1(12),
      R => RSTP
    );
\Delay_out1_reg[13]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => u_LimitPulseWidth_a_n_1,
      Q => Delay_out1(13),
      R => RSTP
    );
\Delay_out1_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => u_LimitPulseWidth_a_n_23,
      Q => Delay_out1(1),
      R => RSTP
    );
\Delay_out1_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \Delay_out1[2]_i_1_n_0\,
      Q => Delay_out1(2),
      R => RSTP
    );
\Delay_out1_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => u_LimitPulseWidth_a_n_22,
      Q => Delay_out1(3),
      R => RSTP
    );
\Delay_out1_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \Delay_out1[4]_i_1_n_0\,
      Q => Delay_out1(4),
      R => RSTP
    );
\Delay_out1_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => u_LimitPulseWidth_a_n_21,
      Q => Delay_out1(5),
      R => RSTP
    );
\Delay_out1_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \Delay_out1[6]_i_1_n_0\,
      Q => Delay_out1(6),
      R => RSTP
    );
\Delay_out1_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => u_LimitPulseWidth_a_n_20,
      Q => Delay_out1(7),
      R => RSTP
    );
\Delay_out1_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \Delay_out1[8]_i_1_n_0\,
      Q => Delay_out1(8),
      R => RSTP
    );
\Delay_out1_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => u_LimitPulseWidth_a_n_19,
      Q => Delay_out1(9),
      R => RSTP
    );
\HDL_Counter2_count_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => \HDL_Counter2_count_reg[19]_0\,
      D => u_Counter_Ctrl_n_29,
      Q => HDL_Counter2_count_reg(0),
      R => RSTP
    );
\HDL_Counter2_count_reg[10]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => \HDL_Counter2_count_reg[19]_0\,
      D => u_Counter_Ctrl_n_35,
      Q => HDL_Counter2_count_reg(10),
      R => RSTP
    );
\HDL_Counter2_count_reg[11]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => \HDL_Counter2_count_reg[19]_0\,
      D => u_Counter_Ctrl_n_34,
      Q => HDL_Counter2_count_reg(11),
      R => RSTP
    );
\HDL_Counter2_count_reg[12]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => \HDL_Counter2_count_reg[19]_0\,
      D => u_Counter_Ctrl_n_33,
      Q => HDL_Counter2_count_reg(12),
      R => RSTP
    );
\HDL_Counter2_count_reg[13]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => \HDL_Counter2_count_reg[19]_0\,
      D => u_Counter_Ctrl_n_32,
      Q => HDL_Counter2_count_reg(13),
      R => RSTP
    );
\HDL_Counter2_count_reg[14]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => \HDL_Counter2_count_reg[19]_0\,
      D => u_Counter_Ctrl_n_31,
      Q => HDL_Counter2_count_reg(14),
      R => RSTP
    );
\HDL_Counter2_count_reg[15]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => \HDL_Counter2_count_reg[19]_0\,
      D => u_Counter_Ctrl_n_30,
      Q => HDL_Counter2_count_reg(15),
      R => RSTP
    );
\HDL_Counter2_count_reg[16]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => \HDL_Counter2_count_reg[19]_0\,
      D => u_Counter_Ctrl_n_41,
      Q => HDL_Counter2_count_reg(16),
      R => RSTP
    );
\HDL_Counter2_count_reg[17]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => \HDL_Counter2_count_reg[19]_0\,
      D => u_Counter_Ctrl_n_40,
      Q => HDL_Counter2_count_reg(17),
      R => RSTP
    );
\HDL_Counter2_count_reg[18]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => \HDL_Counter2_count_reg[19]_0\,
      D => u_Counter_Ctrl_n_39,
      Q => HDL_Counter2_count_reg(18),
      R => RSTP
    );
\HDL_Counter2_count_reg[19]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => \HDL_Counter2_count_reg[19]_0\,
      D => u_Counter_Ctrl_n_38,
      Q => HDL_Counter2_count_reg(19),
      R => RSTP
    );
\HDL_Counter2_count_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => \HDL_Counter2_count_reg[19]_0\,
      D => u_Counter_Ctrl_n_28,
      Q => HDL_Counter2_count_reg(1),
      R => RSTP
    );
\HDL_Counter2_count_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => \HDL_Counter2_count_reg[19]_0\,
      D => u_Counter_Ctrl_n_27,
      Q => HDL_Counter2_count_reg(2),
      R => RSTP
    );
\HDL_Counter2_count_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => \HDL_Counter2_count_reg[19]_0\,
      D => u_Counter_Ctrl_n_26,
      Q => HDL_Counter2_count_reg(3),
      R => RSTP
    );
\HDL_Counter2_count_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => \HDL_Counter2_count_reg[19]_0\,
      D => u_Counter_Ctrl_n_25,
      Q => HDL_Counter2_count_reg(4),
      R => RSTP
    );
\HDL_Counter2_count_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => \HDL_Counter2_count_reg[19]_0\,
      D => u_Counter_Ctrl_n_24,
      Q => HDL_Counter2_count_reg(5),
      R => RSTP
    );
\HDL_Counter2_count_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => \HDL_Counter2_count_reg[19]_0\,
      D => u_Counter_Ctrl_n_23,
      Q => HDL_Counter2_count_reg(6),
      R => RSTP
    );
\HDL_Counter2_count_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => \HDL_Counter2_count_reg[19]_0\,
      D => u_Counter_Ctrl_n_22,
      Q => HDL_Counter2_count_reg(7),
      R => RSTP
    );
\HDL_Counter2_count_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => \HDL_Counter2_count_reg[19]_0\,
      D => u_Counter_Ctrl_n_37,
      Q => HDL_Counter2_count_reg(8),
      R => RSTP
    );
\HDL_Counter2_count_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => \HDL_Counter2_count_reg[19]_0\,
      D => u_Counter_Ctrl_n_36,
      Q => HDL_Counter2_count_reg(9),
      R => RSTP
    );
PWM_en_AXI_1_reg: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => write_PWM_en_AXI,
      Q => PWM_en_AXI_1,
      R => RSTP
    );
PWM_en_AXI_2_reg: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => PWM_en_AXI_1,
      Q => \^pwm_en_axi_2_reg_0\,
      R => RSTP
    );
\Switch3_out1_1[0]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"F4"
    )
        port map (
      I0 => reduced_reg(1),
      I1 => CEP,
      I2 => RSTP,
      O => Switch5_out1_1
    );
\Switch3_out1_1_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => u_Modulator_a_n_21,
      Q => Q(1),
      R => Switch5_out1_1
    );
\Switch3_out1_1_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => Modulator_a_out1(1),
      Q => Q(0),
      R => Switch5_out1_1
    );
\Switch4_out1_1_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => u_Modulator_b_n_21,
      Q => \Switch4_out1_1_reg[0]_0\(1),
      R => Switch5_out1_1
    );
\Switch4_out1_1_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => Modulator_b_out1(1),
      Q => \Switch4_out1_1_reg[0]_0\(0),
      R => Switch5_out1_1
    );
\Switch5_out1_1_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => u_Modulator_c_n_21,
      Q => \Switch5_out1_1_reg[0]_0\(1),
      R => Switch5_out1_1
    );
\Switch5_out1_1_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => Modulator_c_out1(1),
      Q => \Switch5_out1_1_reg[0]_0\(0),
      R => Switch5_out1_1
    );
\delayMatch1_reg_reg[0][0]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \delayMatch1_reg_reg[0][13]_0\(0),
      Q => \delayMatch1_reg_reg[0]_0\(0),
      R => RSTP
    );
\delayMatch1_reg_reg[0][10]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \delayMatch1_reg_reg[0][13]_0\(10),
      Q => \delayMatch1_reg_reg[0]_0\(10),
      R => RSTP
    );
\delayMatch1_reg_reg[0][11]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \delayMatch1_reg_reg[0][13]_0\(11),
      Q => \delayMatch1_reg_reg[0]_0\(11),
      R => RSTP
    );
\delayMatch1_reg_reg[0][12]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \delayMatch1_reg_reg[0][13]_0\(12),
      Q => \delayMatch1_reg_reg[0]_0\(12),
      R => RSTP
    );
\delayMatch1_reg_reg[0][13]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \delayMatch1_reg_reg[0][13]_0\(13),
      Q => \delayMatch1_reg_reg[0]_0\(13),
      R => RSTP
    );
\delayMatch1_reg_reg[0][1]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \delayMatch1_reg_reg[0][13]_0\(1),
      Q => \delayMatch1_reg_reg[0]_0\(1),
      R => RSTP
    );
\delayMatch1_reg_reg[0][2]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \delayMatch1_reg_reg[0][13]_0\(2),
      Q => \delayMatch1_reg_reg[0]_0\(2),
      R => RSTP
    );
\delayMatch1_reg_reg[0][3]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \delayMatch1_reg_reg[0][13]_0\(3),
      Q => \delayMatch1_reg_reg[0]_0\(3),
      R => RSTP
    );
\delayMatch1_reg_reg[0][4]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \delayMatch1_reg_reg[0][13]_0\(4),
      Q => \delayMatch1_reg_reg[0]_0\(4),
      R => RSTP
    );
\delayMatch1_reg_reg[0][5]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \delayMatch1_reg_reg[0][13]_0\(5),
      Q => \delayMatch1_reg_reg[0]_0\(5),
      R => RSTP
    );
\delayMatch1_reg_reg[0][6]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \delayMatch1_reg_reg[0][13]_0\(6),
      Q => \delayMatch1_reg_reg[0]_0\(6),
      R => RSTP
    );
\delayMatch1_reg_reg[0][7]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \delayMatch1_reg_reg[0][13]_0\(7),
      Q => \delayMatch1_reg_reg[0]_0\(7),
      R => RSTP
    );
\delayMatch1_reg_reg[0][8]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \delayMatch1_reg_reg[0][13]_0\(8),
      Q => \delayMatch1_reg_reg[0]_0\(8),
      R => RSTP
    );
\delayMatch1_reg_reg[0][9]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \delayMatch1_reg_reg[0][13]_0\(9),
      Q => \delayMatch1_reg_reg[0]_0\(9),
      R => RSTP
    );
\delayMatch1_reg_reg[1][0]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \delayMatch1_reg_reg[0]_0\(0),
      Q => \delayMatch1_reg_reg[1]_1\(0),
      R => RSTP
    );
\delayMatch1_reg_reg[1][10]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \delayMatch1_reg_reg[0]_0\(10),
      Q => \delayMatch1_reg_reg[1]_1\(10),
      R => RSTP
    );
\delayMatch1_reg_reg[1][11]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \delayMatch1_reg_reg[0]_0\(11),
      Q => \delayMatch1_reg_reg[1]_1\(11),
      R => RSTP
    );
\delayMatch1_reg_reg[1][12]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \delayMatch1_reg_reg[0]_0\(12),
      Q => \delayMatch1_reg_reg[1]_1\(12),
      R => RSTP
    );
\delayMatch1_reg_reg[1][13]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \delayMatch1_reg_reg[0]_0\(13),
      Q => \delayMatch1_reg_reg[1]_1\(13),
      R => RSTP
    );
\delayMatch1_reg_reg[1][1]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \delayMatch1_reg_reg[0]_0\(1),
      Q => \delayMatch1_reg_reg[1]_1\(1),
      R => RSTP
    );
\delayMatch1_reg_reg[1][2]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \delayMatch1_reg_reg[0]_0\(2),
      Q => \delayMatch1_reg_reg[1]_1\(2),
      R => RSTP
    );
\delayMatch1_reg_reg[1][3]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \delayMatch1_reg_reg[0]_0\(3),
      Q => \delayMatch1_reg_reg[1]_1\(3),
      R => RSTP
    );
\delayMatch1_reg_reg[1][4]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \delayMatch1_reg_reg[0]_0\(4),
      Q => \delayMatch1_reg_reg[1]_1\(4),
      R => RSTP
    );
\delayMatch1_reg_reg[1][5]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \delayMatch1_reg_reg[0]_0\(5),
      Q => \delayMatch1_reg_reg[1]_1\(5),
      R => RSTP
    );
\delayMatch1_reg_reg[1][6]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \delayMatch1_reg_reg[0]_0\(6),
      Q => \delayMatch1_reg_reg[1]_1\(6),
      R => RSTP
    );
\delayMatch1_reg_reg[1][7]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \delayMatch1_reg_reg[0]_0\(7),
      Q => \delayMatch1_reg_reg[1]_1\(7),
      R => RSTP
    );
\delayMatch1_reg_reg[1][8]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \delayMatch1_reg_reg[0]_0\(8),
      Q => \delayMatch1_reg_reg[1]_1\(8),
      R => RSTP
    );
\delayMatch1_reg_reg[1][9]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \delayMatch1_reg_reg[0]_0\(9),
      Q => \delayMatch1_reg_reg[1]_1\(9),
      R => RSTP
    );
\delayMatch3_1_reg[0]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"B8"
    )
        port map (
      I0 => Mux_out1(2),
      I1 => \^genpwm_out5\,
      I2 => delayMatch3_1_reg(0),
      O => Demux_out2(0)
    );
\delayMatch3_1_reg_1[0]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"B8"
    )
        port map (
      I0 => Mux_out1(3),
      I1 => \^genpwm_out5\,
      I2 => delayMatch3_1_reg_1(0),
      O => Demux_out2(1)
    );
\delayMatch3_reg_reg[0][0]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \delayMatch3_reg_reg[0][13]_0\(0),
      Q => \delayMatch3_reg_reg[0]_2\(0),
      R => RSTP
    );
\delayMatch3_reg_reg[0][10]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \delayMatch3_reg_reg[0][13]_0\(10),
      Q => \delayMatch3_reg_reg[0]_2\(10),
      R => RSTP
    );
\delayMatch3_reg_reg[0][11]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \delayMatch3_reg_reg[0][13]_0\(11),
      Q => \delayMatch3_reg_reg[0]_2\(11),
      R => RSTP
    );
\delayMatch3_reg_reg[0][12]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \delayMatch3_reg_reg[0][13]_0\(12),
      Q => \delayMatch3_reg_reg[0]_2\(12),
      R => RSTP
    );
\delayMatch3_reg_reg[0][13]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \delayMatch3_reg_reg[0][13]_0\(13),
      Q => \delayMatch3_reg_reg[0]_2\(13),
      R => RSTP
    );
\delayMatch3_reg_reg[0][1]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \delayMatch3_reg_reg[0][13]_0\(1),
      Q => \delayMatch3_reg_reg[0]_2\(1),
      R => RSTP
    );
\delayMatch3_reg_reg[0][2]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \delayMatch3_reg_reg[0][13]_0\(2),
      Q => \delayMatch3_reg_reg[0]_2\(2),
      R => RSTP
    );
\delayMatch3_reg_reg[0][3]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \delayMatch3_reg_reg[0][13]_0\(3),
      Q => \delayMatch3_reg_reg[0]_2\(3),
      R => RSTP
    );
\delayMatch3_reg_reg[0][4]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \delayMatch3_reg_reg[0][13]_0\(4),
      Q => \delayMatch3_reg_reg[0]_2\(4),
      R => RSTP
    );
\delayMatch3_reg_reg[0][5]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \delayMatch3_reg_reg[0][13]_0\(5),
      Q => \delayMatch3_reg_reg[0]_2\(5),
      R => RSTP
    );
\delayMatch3_reg_reg[0][6]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \delayMatch3_reg_reg[0][13]_0\(6),
      Q => \delayMatch3_reg_reg[0]_2\(6),
      R => RSTP
    );
\delayMatch3_reg_reg[0][7]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \delayMatch3_reg_reg[0][13]_0\(7),
      Q => \delayMatch3_reg_reg[0]_2\(7),
      R => RSTP
    );
\delayMatch3_reg_reg[0][8]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \delayMatch3_reg_reg[0][13]_0\(8),
      Q => \delayMatch3_reg_reg[0]_2\(8),
      R => RSTP
    );
\delayMatch3_reg_reg[0][9]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \delayMatch3_reg_reg[0][13]_0\(9),
      Q => \delayMatch3_reg_reg[0]_2\(9),
      R => RSTP
    );
\delayMatch3_reg_reg[1][0]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \delayMatch3_reg_reg[0]_2\(0),
      Q => \delayMatch3_reg_reg[1]_3\(0),
      R => RSTP
    );
\delayMatch3_reg_reg[1][10]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \delayMatch3_reg_reg[0]_2\(10),
      Q => \delayMatch3_reg_reg[1]_3\(10),
      R => RSTP
    );
\delayMatch3_reg_reg[1][11]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \delayMatch3_reg_reg[0]_2\(11),
      Q => \delayMatch3_reg_reg[1]_3\(11),
      R => RSTP
    );
\delayMatch3_reg_reg[1][12]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \delayMatch3_reg_reg[0]_2\(12),
      Q => \delayMatch3_reg_reg[1]_3\(12),
      R => RSTP
    );
\delayMatch3_reg_reg[1][13]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \delayMatch3_reg_reg[0]_2\(13),
      Q => \delayMatch3_reg_reg[1]_3\(13),
      R => RSTP
    );
\delayMatch3_reg_reg[1][1]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \delayMatch3_reg_reg[0]_2\(1),
      Q => \delayMatch3_reg_reg[1]_3\(1),
      R => RSTP
    );
\delayMatch3_reg_reg[1][2]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \delayMatch3_reg_reg[0]_2\(2),
      Q => \delayMatch3_reg_reg[1]_3\(2),
      R => RSTP
    );
\delayMatch3_reg_reg[1][3]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \delayMatch3_reg_reg[0]_2\(3),
      Q => \delayMatch3_reg_reg[1]_3\(3),
      R => RSTP
    );
\delayMatch3_reg_reg[1][4]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \delayMatch3_reg_reg[0]_2\(4),
      Q => \delayMatch3_reg_reg[1]_3\(4),
      R => RSTP
    );
\delayMatch3_reg_reg[1][5]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \delayMatch3_reg_reg[0]_2\(5),
      Q => \delayMatch3_reg_reg[1]_3\(5),
      R => RSTP
    );
\delayMatch3_reg_reg[1][6]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \delayMatch3_reg_reg[0]_2\(6),
      Q => \delayMatch3_reg_reg[1]_3\(6),
      R => RSTP
    );
\delayMatch3_reg_reg[1][7]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \delayMatch3_reg_reg[0]_2\(7),
      Q => \delayMatch3_reg_reg[1]_3\(7),
      R => RSTP
    );
\delayMatch3_reg_reg[1][8]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \delayMatch3_reg_reg[0]_2\(8),
      Q => \delayMatch3_reg_reg[1]_3\(8),
      R => RSTP
    );
\delayMatch3_reg_reg[1][9]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \delayMatch3_reg_reg[0]_2\(9),
      Q => \delayMatch3_reg_reg[1]_3\(9),
      R => RSTP
    );
\delayMatch5_reg_reg[0][0]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \delayMatch5_reg_reg[0][13]_0\(0),
      Q => \delayMatch5_reg_reg[0]_4\(0),
      R => RSTP
    );
\delayMatch5_reg_reg[0][10]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \delayMatch5_reg_reg[0][13]_0\(10),
      Q => \delayMatch5_reg_reg[0]_4\(10),
      R => RSTP
    );
\delayMatch5_reg_reg[0][11]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \delayMatch5_reg_reg[0][13]_0\(11),
      Q => \delayMatch5_reg_reg[0]_4\(11),
      R => RSTP
    );
\delayMatch5_reg_reg[0][12]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \delayMatch5_reg_reg[0][13]_0\(12),
      Q => \delayMatch5_reg_reg[0]_4\(12),
      R => RSTP
    );
\delayMatch5_reg_reg[0][13]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \delayMatch5_reg_reg[0][13]_0\(13),
      Q => \delayMatch5_reg_reg[0]_4\(13),
      R => RSTP
    );
\delayMatch5_reg_reg[0][1]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \delayMatch5_reg_reg[0][13]_0\(1),
      Q => \delayMatch5_reg_reg[0]_4\(1),
      R => RSTP
    );
\delayMatch5_reg_reg[0][2]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \delayMatch5_reg_reg[0][13]_0\(2),
      Q => \delayMatch5_reg_reg[0]_4\(2),
      R => RSTP
    );
\delayMatch5_reg_reg[0][3]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \delayMatch5_reg_reg[0][13]_0\(3),
      Q => \delayMatch5_reg_reg[0]_4\(3),
      R => RSTP
    );
\delayMatch5_reg_reg[0][4]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \delayMatch5_reg_reg[0][13]_0\(4),
      Q => \delayMatch5_reg_reg[0]_4\(4),
      R => RSTP
    );
\delayMatch5_reg_reg[0][5]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \delayMatch5_reg_reg[0][13]_0\(5),
      Q => \delayMatch5_reg_reg[0]_4\(5),
      R => RSTP
    );
\delayMatch5_reg_reg[0][6]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \delayMatch5_reg_reg[0][13]_0\(6),
      Q => \delayMatch5_reg_reg[0]_4\(6),
      R => RSTP
    );
\delayMatch5_reg_reg[0][7]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \delayMatch5_reg_reg[0][13]_0\(7),
      Q => \delayMatch5_reg_reg[0]_4\(7),
      R => RSTP
    );
\delayMatch5_reg_reg[0][8]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \delayMatch5_reg_reg[0][13]_0\(8),
      Q => \delayMatch5_reg_reg[0]_4\(8),
      R => RSTP
    );
\delayMatch5_reg_reg[0][9]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \delayMatch5_reg_reg[0][13]_0\(9),
      Q => \delayMatch5_reg_reg[0]_4\(9),
      R => RSTP
    );
\delayMatch5_reg_reg[1][0]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \delayMatch5_reg_reg[0]_4\(0),
      Q => \delayMatch5_reg_reg[1]_5\(0),
      R => RSTP
    );
\delayMatch5_reg_reg[1][10]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \delayMatch5_reg_reg[0]_4\(10),
      Q => \delayMatch5_reg_reg[1]_5\(10),
      R => RSTP
    );
\delayMatch5_reg_reg[1][11]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \delayMatch5_reg_reg[0]_4\(11),
      Q => \delayMatch5_reg_reg[1]_5\(11),
      R => RSTP
    );
\delayMatch5_reg_reg[1][12]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \delayMatch5_reg_reg[0]_4\(12),
      Q => \delayMatch5_reg_reg[1]_5\(12),
      R => RSTP
    );
\delayMatch5_reg_reg[1][13]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \delayMatch5_reg_reg[0]_4\(13),
      Q => \delayMatch5_reg_reg[1]_5\(13),
      R => RSTP
    );
\delayMatch5_reg_reg[1][1]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \delayMatch5_reg_reg[0]_4\(1),
      Q => \delayMatch5_reg_reg[1]_5\(1),
      R => RSTP
    );
\delayMatch5_reg_reg[1][2]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \delayMatch5_reg_reg[0]_4\(2),
      Q => \delayMatch5_reg_reg[1]_5\(2),
      R => RSTP
    );
\delayMatch5_reg_reg[1][3]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \delayMatch5_reg_reg[0]_4\(3),
      Q => \delayMatch5_reg_reg[1]_5\(3),
      R => RSTP
    );
\delayMatch5_reg_reg[1][4]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \delayMatch5_reg_reg[0]_4\(4),
      Q => \delayMatch5_reg_reg[1]_5\(4),
      R => RSTP
    );
\delayMatch5_reg_reg[1][5]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \delayMatch5_reg_reg[0]_4\(5),
      Q => \delayMatch5_reg_reg[1]_5\(5),
      R => RSTP
    );
\delayMatch5_reg_reg[1][6]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \delayMatch5_reg_reg[0]_4\(6),
      Q => \delayMatch5_reg_reg[1]_5\(6),
      R => RSTP
    );
\delayMatch5_reg_reg[1][7]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \delayMatch5_reg_reg[0]_4\(7),
      Q => \delayMatch5_reg_reg[1]_5\(7),
      R => RSTP
    );
\delayMatch5_reg_reg[1][8]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \delayMatch5_reg_reg[0]_4\(8),
      Q => \delayMatch5_reg_reg[1]_5\(8),
      R => RSTP
    );
\delayMatch5_reg_reg[1][9]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \delayMatch5_reg_reg[0]_4\(9),
      Q => \delayMatch5_reg_reg[1]_5\(9),
      R => RSTP
    );
\delayMatch6_1_reg[0]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"B8"
    )
        port map (
      I0 => Mux_out1(4),
      I1 => \^genpwm_out5\,
      I2 => delayMatch6_1_reg(0),
      O => Demux_out3(0)
    );
\delayMatch6_1_reg_1[0]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"B8"
    )
        port map (
      I0 => Mux_out1(5),
      I1 => \^genpwm_out5\,
      I2 => delayMatch6_1_reg_1(0),
      O => Demux_out3(1)
    );
\delayMatch_1_reg[0]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"B8"
    )
        port map (
      I0 => Mux_out1(0),
      I1 => \^genpwm_out5\,
      I2 => delayMatch_1_reg(0),
      O => Demux_out1(0)
    );
\delayMatch_1_reg_1[0]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"B8"
    )
        port map (
      I0 => Mux_out1(1),
      I1 => \^genpwm_out5\,
      I2 => delayMatch_1_reg_1(0),
      O => Demux_out1(1)
    );
\max_counter_value_1_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \max_counter_value_1_reg[19]_0\(0),
      Q => max_counter_value_1(0),
      R => RSTP
    );
\max_counter_value_1_reg[10]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \max_counter_value_1_reg[19]_0\(10),
      Q => max_counter_value_1(10),
      R => RSTP
    );
\max_counter_value_1_reg[11]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \max_counter_value_1_reg[19]_0\(11),
      Q => max_counter_value_1(11),
      R => RSTP
    );
\max_counter_value_1_reg[12]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \max_counter_value_1_reg[19]_0\(12),
      Q => max_counter_value_1(12),
      R => RSTP
    );
\max_counter_value_1_reg[13]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \max_counter_value_1_reg[19]_0\(13),
      Q => max_counter_value_1(13),
      R => RSTP
    );
\max_counter_value_1_reg[14]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \max_counter_value_1_reg[19]_0\(14),
      Q => max_counter_value_1(14),
      R => RSTP
    );
\max_counter_value_1_reg[15]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \max_counter_value_1_reg[19]_0\(15),
      Q => max_counter_value_1(15),
      R => RSTP
    );
\max_counter_value_1_reg[16]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \max_counter_value_1_reg[19]_0\(16),
      Q => max_counter_value_1(16),
      R => RSTP
    );
\max_counter_value_1_reg[17]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \max_counter_value_1_reg[19]_0\(17),
      Q => max_counter_value_1(17),
      R => RSTP
    );
\max_counter_value_1_reg[18]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \max_counter_value_1_reg[19]_0\(18),
      Q => max_counter_value_1(18),
      R => RSTP
    );
\max_counter_value_1_reg[19]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \max_counter_value_1_reg[19]_0\(19),
      Q => max_counter_value_1(19),
      R => RSTP
    );
\max_counter_value_1_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \max_counter_value_1_reg[19]_0\(1),
      Q => max_counter_value_1(1),
      R => RSTP
    );
\max_counter_value_1_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \max_counter_value_1_reg[19]_0\(2),
      Q => max_counter_value_1(2),
      R => RSTP
    );
\max_counter_value_1_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \max_counter_value_1_reg[19]_0\(3),
      Q => max_counter_value_1(3),
      R => RSTP
    );
\max_counter_value_1_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \max_counter_value_1_reg[19]_0\(4),
      Q => max_counter_value_1(4),
      R => RSTP
    );
\max_counter_value_1_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \max_counter_value_1_reg[19]_0\(5),
      Q => max_counter_value_1(5),
      R => RSTP
    );
\max_counter_value_1_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \max_counter_value_1_reg[19]_0\(6),
      Q => max_counter_value_1(6),
      R => RSTP
    );
\max_counter_value_1_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \max_counter_value_1_reg[19]_0\(7),
      Q => max_counter_value_1(7),
      R => RSTP
    );
\max_counter_value_1_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \max_counter_value_1_reg[19]_0\(8),
      Q => max_counter_value_1(8),
      R => RSTP
    );
\max_counter_value_1_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \max_counter_value_1_reg[19]_0\(9),
      Q => max_counter_value_1(9),
      R => RSTP
    );
\maximum_counter_value_1[13]_i_1\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"8"
    )
        port map (
      I0 => \maximum_counter_value_1[18]_i_3_n_0\,
      I1 => max_counter_value_1(13),
      O => \maximum_counter_value_1[13]_i_1_n_0\
    );
\maximum_counter_value_1[15]_i_1\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"8"
    )
        port map (
      I0 => \maximum_counter_value_1[18]_i_3_n_0\,
      I1 => max_counter_value_1(15),
      O => \maximum_counter_value_1[15]_i_1_n_0\
    );
\maximum_counter_value_1[16]_i_1\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"8"
    )
        port map (
      I0 => \maximum_counter_value_1[18]_i_3_n_0\,
      I1 => max_counter_value_1(16),
      O => \maximum_counter_value_1[16]_i_1_n_0\
    );
\maximum_counter_value_1[17]_i_1\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"8"
    )
        port map (
      I0 => \maximum_counter_value_1[18]_i_3_n_0\,
      I1 => max_counter_value_1(17),
      O => \maximum_counter_value_1[17]_i_1_n_0\
    );
\maximum_counter_value_1[18]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"08"
    )
        port map (
      I0 => maximum_counter_value10_in,
      I1 => CEP,
      I2 => RSTP,
      O => \maximum_counter_value_1[18]_i_1_n_0\
    );
\maximum_counter_value_1[18]_i_2\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"8"
    )
        port map (
      I0 => \maximum_counter_value_1[18]_i_3_n_0\,
      I1 => max_counter_value_1(18),
      O => \maximum_counter_value_1[18]_i_2_n_0\
    );
\maximum_counter_value_1[18]_i_3\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"00000000FFFFFFF7"
    )
        port map (
      I0 => \maximum_counter_value_1[8]_i_9_n_0\,
      I1 => \maximum_counter_value_1[8]_i_8_n_0\,
      I2 => max_counter_value_1(9),
      I3 => max_counter_value_1(10),
      I4 => max_counter_value_1(11),
      I5 => RSTP,
      O => \maximum_counter_value_1[18]_i_3_n_0\
    );
\maximum_counter_value_1[19]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FFA8"
    )
        port map (
      I0 => CEP,
      I1 => \maximum_counter_value1__14\,
      I2 => maximum_counter_value10_in,
      I3 => RSTP,
      O => \maximum_counter_value_1[19]_i_1_n_0\
    );
\maximum_counter_value_1[2]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"10"
    )
        port map (
      I0 => RSTP,
      I1 => maximum_counter_value10_in,
      I2 => max_counter_value_1(2),
      O => \maximum_counter_value_1[2]_i_1_n_0\
    );
\maximum_counter_value_1[4]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"10"
    )
        port map (
      I0 => RSTP,
      I1 => maximum_counter_value10_in,
      I2 => max_counter_value_1(4),
      O => \maximum_counter_value_1[4]_i_1_n_0\
    );
\maximum_counter_value_1[5]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"0F0E"
    )
        port map (
      I0 => max_counter_value_1(5),
      I1 => maximum_counter_value10_in,
      I2 => RSTP,
      I3 => \maximum_counter_value1__14\,
      O => p_1_in(5)
    );
\maximum_counter_value_1[6]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"10"
    )
        port map (
      I0 => RSTP,
      I1 => maximum_counter_value10_in,
      I2 => max_counter_value_1(6),
      O => \maximum_counter_value_1[6]_i_1_n_0\
    );
\maximum_counter_value_1[7]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"0020"
    )
        port map (
      I0 => \maximum_counter_value1__14\,
      I1 => maximum_counter_value10_in,
      I2 => CEP,
      I3 => RSTP,
      O => \maximum_counter_value_1[7]_i_1_n_0\
    );
\maximum_counter_value_1[7]_i_2\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"10"
    )
        port map (
      I0 => RSTP,
      I1 => maximum_counter_value10_in,
      I2 => max_counter_value_1(7),
      O => \maximum_counter_value_1[7]_i_2_n_0\
    );
\maximum_counter_value_1[8]_i_10\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"7"
    )
        port map (
      I0 => max_counter_value_1(8),
      I1 => max_counter_value_1(5),
      O => \maximum_counter_value_1[8]_i_10_n_0\
    );
\maximum_counter_value_1[8]_i_11\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => max_counter_value_1(10),
      I1 => max_counter_value_1(11),
      O => \maximum_counter_value_1[8]_i_11_n_0\
    );
\maximum_counter_value_1[8]_i_12\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"0001"
    )
        port map (
      I0 => max_counter_value_1(15),
      I1 => max_counter_value_1(14),
      I2 => max_counter_value_1(13),
      I3 => max_counter_value_1(12),
      O => \maximum_counter_value_1[8]_i_12_n_0\
    );
\maximum_counter_value_1[8]_i_2\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"0F0E"
    )
        port map (
      I0 => max_counter_value_1(8),
      I1 => maximum_counter_value10_in,
      I2 => RSTP,
      I3 => \maximum_counter_value1__14\,
      O => p_1_in(8)
    );
\maximum_counter_value_1[8]_i_3\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFFFFFFFFA80000"
    )
        port map (
      I0 => max_counter_value_1(13),
      I1 => \maximum_counter_value_1[8]_i_5_n_0\,
      I2 => \maximum_counter_value_1[8]_i_6_n_0\,
      I3 => max_counter_value_1(14),
      I4 => \maximum_counter_value_1[8]_i_7_n_0\,
      I5 => max_counter_value_1(19),
      O => maximum_counter_value10_in
    );
\maximum_counter_value_1[8]_i_4\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"01000000"
    )
        port map (
      I0 => max_counter_value_1(11),
      I1 => max_counter_value_1(10),
      I2 => max_counter_value_1(9),
      I3 => \maximum_counter_value_1[8]_i_8_n_0\,
      I4 => \maximum_counter_value_1[8]_i_9_n_0\,
      O => \maximum_counter_value1__14\
    );
\maximum_counter_value_1[8]_i_5\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0000FFFF0000FFFE"
    )
        port map (
      I0 => max_counter_value_1(4),
      I1 => max_counter_value_1(1),
      I2 => max_counter_value_1(3),
      I3 => max_counter_value_1(2),
      I4 => \maximum_counter_value_1[8]_i_10_n_0\,
      I5 => max_counter_value_1(0),
      O => \maximum_counter_value_1[8]_i_5_n_0\
    );
\maximum_counter_value_1[8]_i_6\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFFFDFDFFFDFDFD"
    )
        port map (
      I0 => \maximum_counter_value_1[8]_i_11_n_0\,
      I1 => max_counter_value_1(9),
      I2 => max_counter_value_1(12),
      I3 => max_counter_value_1(7),
      I4 => max_counter_value_1(8),
      I5 => max_counter_value_1(6),
      O => \maximum_counter_value_1[8]_i_6_n_0\
    );
\maximum_counter_value_1[8]_i_7\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"8000"
    )
        port map (
      I0 => max_counter_value_1(16),
      I1 => max_counter_value_1(15),
      I2 => max_counter_value_1(18),
      I3 => max_counter_value_1(17),
      O => \maximum_counter_value_1[8]_i_7_n_0\
    );
\maximum_counter_value_1[8]_i_8\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"00010000"
    )
        port map (
      I0 => max_counter_value_1(16),
      I1 => max_counter_value_1(17),
      I2 => max_counter_value_1(18),
      I3 => max_counter_value_1(19),
      I4 => \maximum_counter_value_1[8]_i_12_n_0\,
      O => \maximum_counter_value_1[8]_i_8_n_0\
    );
\maximum_counter_value_1[8]_i_9\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFFFFFF1FFFFFFF"
    )
        port map (
      I0 => max_counter_value_1(2),
      I1 => max_counter_value_1(3),
      I2 => max_counter_value_1(7),
      I3 => max_counter_value_1(6),
      I4 => max_counter_value_1(4),
      I5 => \maximum_counter_value_1[8]_i_10_n_0\,
      O => \maximum_counter_value_1[8]_i_9_n_0\
    );
\maximum_counter_value_1_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => max_counter_value_1(0),
      Q => maximum_counter_value_1(0),
      R => \maximum_counter_value_1[19]_i_1_n_0\
    );
\maximum_counter_value_1_reg[10]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => max_counter_value_1(10),
      Q => maximum_counter_value_1(10),
      R => \maximum_counter_value_1[19]_i_1_n_0\
    );
\maximum_counter_value_1_reg[11]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => max_counter_value_1(11),
      Q => maximum_counter_value_1(11),
      R => \maximum_counter_value_1[19]_i_1_n_0\
    );
\maximum_counter_value_1_reg[12]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => max_counter_value_1(12),
      Q => maximum_counter_value_1(12),
      R => \maximum_counter_value_1[19]_i_1_n_0\
    );
\maximum_counter_value_1_reg[13]\: unisim.vcomponents.FDSE
     port map (
      C => IPCORE_CLK,
      CE => \maximum_counter_value_1_reg[8]_0\,
      D => \maximum_counter_value_1[13]_i_1_n_0\,
      Q => maximum_counter_value_1(13),
      S => \maximum_counter_value_1[18]_i_1_n_0\
    );
\maximum_counter_value_1_reg[14]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => max_counter_value_1(14),
      Q => maximum_counter_value_1(14),
      R => \maximum_counter_value_1[19]_i_1_n_0\
    );
\maximum_counter_value_1_reg[15]\: unisim.vcomponents.FDSE
     port map (
      C => IPCORE_CLK,
      CE => \maximum_counter_value_1_reg[8]_0\,
      D => \maximum_counter_value_1[15]_i_1_n_0\,
      Q => maximum_counter_value_1(15),
      S => \maximum_counter_value_1[18]_i_1_n_0\
    );
\maximum_counter_value_1_reg[16]\: unisim.vcomponents.FDSE
     port map (
      C => IPCORE_CLK,
      CE => \maximum_counter_value_1_reg[8]_0\,
      D => \maximum_counter_value_1[16]_i_1_n_0\,
      Q => maximum_counter_value_1(16),
      S => \maximum_counter_value_1[18]_i_1_n_0\
    );
\maximum_counter_value_1_reg[17]\: unisim.vcomponents.FDSE
     port map (
      C => IPCORE_CLK,
      CE => \maximum_counter_value_1_reg[8]_0\,
      D => \maximum_counter_value_1[17]_i_1_n_0\,
      Q => maximum_counter_value_1(17),
      S => \maximum_counter_value_1[18]_i_1_n_0\
    );
\maximum_counter_value_1_reg[18]\: unisim.vcomponents.FDSE
     port map (
      C => IPCORE_CLK,
      CE => \maximum_counter_value_1_reg[8]_0\,
      D => \maximum_counter_value_1[18]_i_2_n_0\,
      Q => maximum_counter_value_1(18),
      S => \maximum_counter_value_1[18]_i_1_n_0\
    );
\maximum_counter_value_1_reg[19]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => max_counter_value_1(19),
      Q => maximum_counter_value_1(19),
      R => \maximum_counter_value_1[19]_i_1_n_0\
    );
\maximum_counter_value_1_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => max_counter_value_1(1),
      Q => maximum_counter_value_1(1),
      R => \maximum_counter_value_1[19]_i_1_n_0\
    );
\maximum_counter_value_1_reg[2]\: unisim.vcomponents.FDSE
     port map (
      C => IPCORE_CLK,
      CE => \maximum_counter_value_1_reg[8]_0\,
      D => \maximum_counter_value_1[2]_i_1_n_0\,
      Q => maximum_counter_value_1(2),
      S => \maximum_counter_value_1[7]_i_1_n_0\
    );
\maximum_counter_value_1_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => max_counter_value_1(3),
      Q => maximum_counter_value_1(3),
      R => \maximum_counter_value_1[19]_i_1_n_0\
    );
\maximum_counter_value_1_reg[4]\: unisim.vcomponents.FDSE
     port map (
      C => IPCORE_CLK,
      CE => \maximum_counter_value_1_reg[8]_0\,
      D => \maximum_counter_value_1[4]_i_1_n_0\,
      Q => maximum_counter_value_1(4),
      S => \maximum_counter_value_1[7]_i_1_n_0\
    );
\maximum_counter_value_1_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => \maximum_counter_value_1_reg[8]_0\,
      D => p_1_in(5),
      Q => maximum_counter_value_1(5),
      R => '0'
    );
\maximum_counter_value_1_reg[6]\: unisim.vcomponents.FDSE
     port map (
      C => IPCORE_CLK,
      CE => \maximum_counter_value_1_reg[8]_0\,
      D => \maximum_counter_value_1[6]_i_1_n_0\,
      Q => maximum_counter_value_1(6),
      S => \maximum_counter_value_1[7]_i_1_n_0\
    );
\maximum_counter_value_1_reg[7]\: unisim.vcomponents.FDSE
     port map (
      C => IPCORE_CLK,
      CE => \maximum_counter_value_1_reg[8]_0\,
      D => \maximum_counter_value_1[7]_i_2_n_0\,
      Q => maximum_counter_value_1(7),
      S => \maximum_counter_value_1[7]_i_1_n_0\
    );
\maximum_counter_value_1_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => \maximum_counter_value_1_reg[8]_0\,
      D => p_1_in(8),
      Q => maximum_counter_value_1(8),
      R => '0'
    );
\maximum_counter_value_1_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => max_counter_value_1(9),
      Q => maximum_counter_value_1(9),
      R => \maximum_counter_value_1[19]_i_1_n_0\
    );
\min_pulse_width_AXI_1_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \min_pulse_width_AXI_1_reg[13]_0\(0),
      Q => min_pulse_width(0),
      R => RSTP
    );
\min_pulse_width_AXI_1_reg[10]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \min_pulse_width_AXI_1_reg[13]_0\(10),
      Q => min_pulse_width(10),
      R => RSTP
    );
\min_pulse_width_AXI_1_reg[11]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \min_pulse_width_AXI_1_reg[13]_0\(11),
      Q => min_pulse_width(11),
      R => RSTP
    );
\min_pulse_width_AXI_1_reg[12]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \min_pulse_width_AXI_1_reg[13]_0\(12),
      Q => min_pulse_width(12),
      R => RSTP
    );
\min_pulse_width_AXI_1_reg[13]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \min_pulse_width_AXI_1_reg[13]_0\(13),
      Q => min_pulse_width(13),
      R => RSTP
    );
\min_pulse_width_AXI_1_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \min_pulse_width_AXI_1_reg[13]_0\(1),
      Q => min_pulse_width(1),
      R => RSTP
    );
\min_pulse_width_AXI_1_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \min_pulse_width_AXI_1_reg[13]_0\(2),
      Q => min_pulse_width(2),
      R => RSTP
    );
\min_pulse_width_AXI_1_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \min_pulse_width_AXI_1_reg[13]_0\(3),
      Q => min_pulse_width(3),
      R => RSTP
    );
\min_pulse_width_AXI_1_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \min_pulse_width_AXI_1_reg[13]_0\(4),
      Q => min_pulse_width(4),
      R => RSTP
    );
\min_pulse_width_AXI_1_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \min_pulse_width_AXI_1_reg[13]_0\(5),
      Q => min_pulse_width(5),
      R => RSTP
    );
\min_pulse_width_AXI_1_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \min_pulse_width_AXI_1_reg[13]_0\(6),
      Q => min_pulse_width(6),
      R => RSTP
    );
\min_pulse_width_AXI_1_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \min_pulse_width_AXI_1_reg[13]_0\(7),
      Q => min_pulse_width(7),
      R => RSTP
    );
\min_pulse_width_AXI_1_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \min_pulse_width_AXI_1_reg[13]_0\(8),
      Q => min_pulse_width(8),
      R => RSTP
    );
\min_pulse_width_AXI_1_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \min_pulse_width_AXI_1_reg[13]_0\(9),
      Q => min_pulse_width(9),
      R => RSTP
    );
\minus_out1_1[13]_i_10\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => min_pulse_width(10),
      I1 => min_pulse_width(11),
      O => \minus_out1_1[13]_i_10_n_0\
    );
\minus_out1_1[13]_i_11\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => min_pulse_width(8),
      I1 => min_pulse_width(9),
      O => \minus_out1_1[13]_i_11_n_0\
    );
\minus_out1_1[13]_i_12\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => min_pulse_width(6),
      I1 => min_pulse_width(7),
      O => \minus_out1_1[13]_i_12_n_0\
    );
\minus_out1_1[13]_i_13\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => min_pulse_width(4),
      I1 => min_pulse_width(5),
      O => \minus_out1_1[13]_i_13_n_0\
    );
\minus_out1_1[13]_i_14\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => min_pulse_width(2),
      I1 => min_pulse_width(3),
      O => \minus_out1_1[13]_i_14_n_0\
    );
\minus_out1_1[13]_i_15\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => min_pulse_width(1),
      I1 => min_pulse_width(0),
      O => \minus_out1_1[13]_i_15_n_0\
    );
\minus_out1_1[13]_i_3\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"E"
    )
        port map (
      I0 => min_pulse_width(10),
      I1 => min_pulse_width(11),
      O => \minus_out1_1[13]_i_3_n_0\
    );
\minus_out1_1[13]_i_4\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"E"
    )
        port map (
      I0 => min_pulse_width(8),
      I1 => min_pulse_width(9),
      O => \minus_out1_1[13]_i_4_n_0\
    );
\minus_out1_1[13]_i_5\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"E"
    )
        port map (
      I0 => min_pulse_width(6),
      I1 => min_pulse_width(7),
      O => \minus_out1_1[13]_i_5_n_0\
    );
\minus_out1_1[13]_i_6\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"E"
    )
        port map (
      I0 => min_pulse_width(4),
      I1 => min_pulse_width(5),
      O => \minus_out1_1[13]_i_6_n_0\
    );
\minus_out1_1[13]_i_7\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"E"
    )
        port map (
      I0 => min_pulse_width(2),
      I1 => min_pulse_width(3),
      O => \minus_out1_1[13]_i_7_n_0\
    );
\minus_out1_1[13]_i_8__1\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"E"
    )
        port map (
      I0 => min_pulse_width(0),
      I1 => min_pulse_width(1),
      O => \minus_out1_1[13]_i_8__1_n_0\
    );
\minus_out1_1[13]_i_9__0\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"2"
    )
        port map (
      I0 => min_pulse_width(12),
      I1 => min_pulse_width(13),
      O => \minus_out1_1[13]_i_9__0_n_0\
    );
\minus_out1_1_reg[13]_i_2__0\: unisim.vcomponents.CARRY8
     port map (
      CI => '0',
      CI_TOP => '0',
      CO(7) => \NLW_minus_out1_1_reg[13]_i_2__0_CO_UNCONNECTED\(7),
      CO(6) => Saturation1_out110_in,
      CO(5) => \minus_out1_1_reg[13]_i_2__0_n_2\,
      CO(4) => \minus_out1_1_reg[13]_i_2__0_n_3\,
      CO(3) => \minus_out1_1_reg[13]_i_2__0_n_4\,
      CO(2) => \minus_out1_1_reg[13]_i_2__0_n_5\,
      CO(1) => \minus_out1_1_reg[13]_i_2__0_n_6\,
      CO(0) => \minus_out1_1_reg[13]_i_2__0_n_7\,
      DI(7 downto 6) => B"00",
      DI(5) => \minus_out1_1[13]_i_3_n_0\,
      DI(4) => \minus_out1_1[13]_i_4_n_0\,
      DI(3) => \minus_out1_1[13]_i_5_n_0\,
      DI(2) => \minus_out1_1[13]_i_6_n_0\,
      DI(1) => \minus_out1_1[13]_i_7_n_0\,
      DI(0) => \minus_out1_1[13]_i_8__1_n_0\,
      O(7 downto 0) => \NLW_minus_out1_1_reg[13]_i_2__0_O_UNCONNECTED\(7 downto 0),
      S(7) => '0',
      S(6) => \minus_out1_1[13]_i_9__0_n_0\,
      S(5) => \minus_out1_1[13]_i_10_n_0\,
      S(4) => \minus_out1_1[13]_i_11_n_0\,
      S(3) => \minus_out1_1[13]_i_12_n_0\,
      S(2) => \minus_out1_1[13]_i_13_n_0\,
      S(1) => \minus_out1_1[13]_i_14_n_0\,
      S(0) => \minus_out1_1[13]_i_15_n_0\
    );
\reduced_reg_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \^pwm_en_axi_2_reg_0\,
      Q => \reduced_reg__0\(0),
      R => RSTP
    );
\reduced_reg_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \reduced_reg__0\(0),
      Q => reduced_reg(1),
      R => RSTP
    );
u_Counter_Ctrl: entity work.zusys_PWM_SS_3L_ip_0_0_PWM_SS_3L_ip_src_Counter_Ctrl
     port map (
      CEP => CEP,
      CO(0) => Counter_Ctrl_out4,
      Counter_Ctrl_out3(20 downto 0) => Counter_Ctrl_out3(20 downto 0),
      Counter_Ctrl_out4_1_reg(6) => u_LimitPulseWidth_c_n_28,
      Counter_Ctrl_out4_1_reg(5) => u_LimitPulseWidth_c_n_29,
      Counter_Ctrl_out4_1_reg(4) => u_LimitPulseWidth_c_n_30,
      Counter_Ctrl_out4_1_reg(3) => u_LimitPulseWidth_c_n_31,
      Counter_Ctrl_out4_1_reg(2) => u_LimitPulseWidth_c_n_32,
      Counter_Ctrl_out4_1_reg(1) => u_LimitPulseWidth_c_n_33,
      Counter_Ctrl_out4_1_reg(0) => u_LimitPulseWidth_c_n_34,
      HDL_Counter2_count_reg(19 downto 0) => HDL_Counter2_count_reg(19 downto 0),
      \HDL_Counter2_count_reg[0]\(7) => u_Counter_Ctrl_n_30,
      \HDL_Counter2_count_reg[0]\(6) => u_Counter_Ctrl_n_31,
      \HDL_Counter2_count_reg[0]\(5) => u_Counter_Ctrl_n_32,
      \HDL_Counter2_count_reg[0]\(4) => u_Counter_Ctrl_n_33,
      \HDL_Counter2_count_reg[0]\(3) => u_Counter_Ctrl_n_34,
      \HDL_Counter2_count_reg[0]\(2) => u_Counter_Ctrl_n_35,
      \HDL_Counter2_count_reg[0]\(1) => u_Counter_Ctrl_n_36,
      \HDL_Counter2_count_reg[0]\(0) => u_Counter_Ctrl_n_37,
      \HDL_Counter2_count_reg[0]_0\(3) => u_Counter_Ctrl_n_38,
      \HDL_Counter2_count_reg[0]_0\(2) => u_Counter_Ctrl_n_39,
      \HDL_Counter2_count_reg[0]_0\(1) => u_Counter_Ctrl_n_40,
      \HDL_Counter2_count_reg[0]_0\(0) => u_Counter_Ctrl_n_41,
      IPCORE_CLK => IPCORE_CLK,
      O(7) => u_Counter_Ctrl_n_22,
      O(6) => u_Counter_Ctrl_n_23,
      O(5) => u_Counter_Ctrl_n_24,
      O(4) => u_Counter_Ctrl_n_25,
      O(3) => u_Counter_Ctrl_n_26,
      O(2) => u_Counter_Ctrl_n_27,
      O(1) => u_Counter_Ctrl_n_28,
      O(0) => u_Counter_Ctrl_n_29,
      RSTP => RSTP,
      S(3) => u_Modulator_a_n_23,
      S(2) => u_Modulator_a_n_24,
      S(1) => u_Modulator_a_n_25,
      S(0) => u_Modulator_a_n_26,
      maximum_counter_value_1(19 downto 0) => maximum_counter_value_1(19 downto 0)
    );
u_LimitPulseWidth_a: entity work.zusys_PWM_SS_3L_ip_0_0_PWM_SS_3L_ip_src_LimitPulseWidth_a
     port map (
      B(13 downto 0) => LimitPulseWidth_a_out1(13 downto 0),
      CEP => CEP,
      CO(0) => Counter_Ctrl_out4,
      D(0) => \^pwm_en_axi_2_reg_0\,
      \Delay_out1_reg[0]\ => u_LimitPulseWidth_c_n_25,
      \Delay_out1_reg[0]_0\ => u_LimitPulseWidth_c_n_23,
      \Delay_out1_reg[13]\(13 downto 0) => Delay_out1(13 downto 0),
      \Delay_out1_reg[13]_0\(13 downto 0) => \delayMatch1_reg_reg[1]_1\(13 downto 0),
      \Delay_out1_reg[13]_1\ => u_LimitPulseWidth_c_n_26,
      \Delay_out1_reg[13]_2\ => u_LimitPulseWidth_c_n_27,
      \Delay_out1_reg[13]_3\ => u_LimitPulseWidth_c_n_24,
      HDL_Counter2_count_reg(11 downto 5) => HDL_Counter2_count_reg(19 downto 13),
      HDL_Counter2_count_reg(4) => HDL_Counter2_count_reg(11),
      HDL_Counter2_count_reg(3) => HDL_Counter2_count_reg(4),
      HDL_Counter2_count_reg(2 downto 0) => HDL_Counter2_count_reg(2 downto 0),
      \HDL_Counter2_count_reg[11]_0\ => u_LimitPulseWidth_a_n_24,
      HDL_Counter2_count_reg_11_sp_1 => u_LimitPulseWidth_a_n_17,
      IPCORE_CLK => IPCORE_CLK,
      \OR_out1__0\ => \OR_out1__0\,
      Q(13 downto 0) => min_pulse_width(13 downto 0),
      RSTP => RSTP,
      \delayMatch1_reg_reg[1][11]\ => u_LimitPulseWidth_a_n_18,
      \delayMatch1_reg_reg[1][13]\ => u_LimitPulseWidth_a_n_1,
      \delayMatch1_reg_reg[1][1]\ => u_LimitPulseWidth_a_n_23,
      \delayMatch1_reg_reg[1][3]\ => u_LimitPulseWidth_a_n_22,
      \delayMatch1_reg_reg[1][5]\ => u_LimitPulseWidth_a_n_21,
      \delayMatch1_reg_reg[1][7]\ => u_LimitPulseWidth_a_n_20,
      \delayMatch1_reg_reg[1][9]\ => u_LimitPulseWidth_a_n_19,
      \min_pulse_width_AXI_1_reg[0]\ => u_LimitPulseWidth_a_n_25,
      \min_pulse_width_AXI_1_reg[10]\ => u_LimitPulseWidth_a_n_29,
      \min_pulse_width_AXI_1_reg[4]\ => u_LimitPulseWidth_a_n_0,
      \min_pulse_width_AXI_1_reg[5]\ => u_LimitPulseWidth_a_n_26,
      \min_pulse_width_AXI_1_reg[8]\ => u_LimitPulseWidth_a_n_27,
      \min_pulse_width_AXI_1_reg[9]\ => u_LimitPulseWidth_a_n_28,
      \minus_out1_1_reg[12]_0\ => u_LimitPulseWidth_c_n_0
    );
u_LimitPulseWidth_b: entity work.zusys_PWM_SS_3L_ip_0_0_PWM_SS_3L_ip_src_LimitPulseWidth_b
     port map (
      B(13 downto 0) => LimitPulseWidth_b_out1(13 downto 0),
      CEP => CEP,
      CO(0) => Counter_Ctrl_out4,
      D(0) => \^pwm_en_axi_2_reg_0\,
      \Delay1_out1_reg[0]\ => u_LimitPulseWidth_a_n_24,
      \Delay1_out1_reg[0]_0\ => u_LimitPulseWidth_c_n_25,
      \Delay1_out1_reg[0]_1\ => u_LimitPulseWidth_c_n_23,
      \Delay1_out1_reg[13]\(13 downto 0) => Delay1_out1(13 downto 0),
      \Delay1_out1_reg[13]_0\(13 downto 0) => \delayMatch3_reg_reg[1]_3\(13 downto 0),
      \Delay1_out1_reg[13]_1\ => u_LimitPulseWidth_a_n_17,
      HDL_Counter2_count_reg(0) => HDL_Counter2_count_reg(19),
      IPCORE_CLK => IPCORE_CLK,
      PWM_en_AXI_2_reg => u_LimitPulseWidth_b_n_1,
      Q(13 downto 0) => min_pulse_width(13 downto 0),
      RSTP => RSTP,
      \delayMatch3_reg_reg[1][11]\ => u_LimitPulseWidth_b_n_16,
      \delayMatch3_reg_reg[1][13]\ => u_LimitPulseWidth_b_n_0,
      \delayMatch3_reg_reg[1][1]\ => u_LimitPulseWidth_b_n_21,
      \delayMatch3_reg_reg[1][3]\ => u_LimitPulseWidth_b_n_20,
      \delayMatch3_reg_reg[1][5]\ => u_LimitPulseWidth_b_n_19,
      \delayMatch3_reg_reg[1][7]\ => u_LimitPulseWidth_b_n_18,
      \delayMatch3_reg_reg[1][9]\ => u_LimitPulseWidth_b_n_17,
      \minus_out1_1_reg[10]_0\ => u_LimitPulseWidth_a_n_28,
      \minus_out1_1_reg[11]_0\ => u_LimitPulseWidth_a_n_29,
      \minus_out1_1_reg[12]_0\ => u_LimitPulseWidth_c_n_0,
      \minus_out1_1_reg[5]_0\ => u_LimitPulseWidth_a_n_25,
      \minus_out1_1_reg[6]_0\ => u_LimitPulseWidth_a_n_26,
      \minus_out1_1_reg[7]_0\ => u_LimitPulseWidth_a_n_0,
      \minus_out1_1_reg[9]_0\ => u_LimitPulseWidth_a_n_27
    );
u_LimitPulseWidth_c: entity work.zusys_PWM_SS_3L_ip_0_0_PWM_SS_3L_ip_src_LimitPulseWidth_c
     port map (
      B(13 downto 0) => LimitPulseWidth_c_out1(13 downto 0),
      CEP => CEP,
      CO(0) => Saturation1_out110_in,
      D(0) => \^pwm_en_axi_2_reg_0\,
      \Delay2_out1_reg[0]\ => u_LimitPulseWidth_a_n_24,
      \Delay2_out1_reg[13]\(13 downto 0) => Delay2_out1(13 downto 0),
      \Delay2_out1_reg[13]_0\(13 downto 0) => \delayMatch5_reg_reg[1]_5\(13 downto 0),
      \Delay2_out1_reg[13]_1\ => u_LimitPulseWidth_a_n_17,
      \Delay2_out1_reg[13]_2\(0) => Counter_Ctrl_out4,
      HDL_Counter2_count_reg(19 downto 0) => HDL_Counter2_count_reg(19 downto 0),
      \HDL_Counter2_count_reg[18]\(6) => u_LimitPulseWidth_c_n_28,
      \HDL_Counter2_count_reg[18]\(5) => u_LimitPulseWidth_c_n_29,
      \HDL_Counter2_count_reg[18]\(4) => u_LimitPulseWidth_c_n_30,
      \HDL_Counter2_count_reg[18]\(3) => u_LimitPulseWidth_c_n_31,
      \HDL_Counter2_count_reg[18]\(2) => u_LimitPulseWidth_c_n_32,
      \HDL_Counter2_count_reg[18]\(1) => u_LimitPulseWidth_c_n_33,
      \HDL_Counter2_count_reg[18]\(0) => u_LimitPulseWidth_c_n_34,
      HDL_Counter2_count_reg_10_sp_1 => u_LimitPulseWidth_c_n_26,
      HDL_Counter2_count_reg_13_sp_1 => u_LimitPulseWidth_c_n_24,
      HDL_Counter2_count_reg_16_sp_1 => u_LimitPulseWidth_c_n_23,
      HDL_Counter2_count_reg_1_sp_1 => u_LimitPulseWidth_c_n_25,
      HDL_Counter2_count_reg_7_sp_1 => u_LimitPulseWidth_c_n_27,
      IPCORE_CLK => IPCORE_CLK,
      PWM_en_AXI_2_reg => u_LimitPulseWidth_c_n_2,
      Q(13 downto 0) => min_pulse_width(13 downto 0),
      RSTP => RSTP,
      \delayMatch5_reg_reg[1][11]\ => u_LimitPulseWidth_c_n_17,
      \delayMatch5_reg_reg[1][13]\ => u_LimitPulseWidth_c_n_1,
      \delayMatch5_reg_reg[1][1]\ => u_LimitPulseWidth_c_n_22,
      \delayMatch5_reg_reg[1][3]\ => u_LimitPulseWidth_c_n_21,
      \delayMatch5_reg_reg[1][5]\ => u_LimitPulseWidth_c_n_20,
      \delayMatch5_reg_reg[1][7]\ => u_LimitPulseWidth_c_n_19,
      \delayMatch5_reg_reg[1][9]\ => u_LimitPulseWidth_c_n_18,
      maximum_counter_value_1(19 downto 0) => maximum_counter_value_1(19 downto 0),
      \min_pulse_width_AXI_1_reg[9]\ => u_LimitPulseWidth_c_n_0,
      \minus_out1_1_reg[10]_0\ => u_LimitPulseWidth_a_n_28,
      \minus_out1_1_reg[11]_0\ => u_LimitPulseWidth_a_n_29,
      \minus_out1_1_reg[5]_0\ => u_LimitPulseWidth_a_n_25,
      \minus_out1_1_reg[6]_0\ => u_LimitPulseWidth_a_n_26,
      \minus_out1_1_reg[7]_0\ => u_LimitPulseWidth_a_n_0,
      \minus_out1_1_reg[9]_0\ => u_LimitPulseWidth_a_n_27
    );
u_Modulator_a: entity work.zusys_PWM_SS_3L_ip_0_0_PWM_SS_3L_ip_src_Modulator_a
     port map (
      \AND_out10_carry__0_0\(20 downto 0) => \modulating_signal_in_clock_cycles_1_reg__0_0\(20 downto 0),
      B(13 downto 0) => LimitPulseWidth_a_out1(13 downto 0),
      CEP => CEP,
      Counter_Ctrl_out3(20 downto 0) => Counter_Ctrl_out3(20 downto 0),
      D(1) => u_Modulator_a_n_21,
      D(0) => Modulator_a_out1(1),
      DI(0) => u_Modulator_a_n_27,
      HDL_Counter2_count_reg(19 downto 0) => HDL_Counter2_count_reg(19 downto 0),
      IPCORE_CLK => IPCORE_CLK,
      P(20 downto 0) => \modulating_signal_in_clock_cycles_1_reg__0\(20 downto 0),
      RSTP => RSTP,
      S(3) => u_Modulator_a_n_23,
      S(2) => u_Modulator_a_n_24,
      S(1) => u_Modulator_a_n_25,
      S(0) => u_Modulator_a_n_26,
      maximum_counter_value_1(19 downto 0) => maximum_counter_value_1(19 downto 0),
      \reduced_reg_1_reg[1][20]_0\(0) => u_Modulator_a_n_28,
      \reduced_reg_1_reg[1]_9\(20 downto 0) => \reduced_reg_1_reg[1]_9\(20 downto 0),
      \reduced_reg_reg[1][14]_0\(7) => u_Modulator_a_n_29,
      \reduced_reg_reg[1][14]_0\(6) => u_Modulator_a_n_30,
      \reduced_reg_reg[1][14]_0\(5) => u_Modulator_a_n_31,
      \reduced_reg_reg[1][14]_0\(4) => u_Modulator_a_n_32,
      \reduced_reg_reg[1][14]_0\(3) => u_Modulator_a_n_33,
      \reduced_reg_reg[1][14]_0\(2) => u_Modulator_a_n_34,
      \reduced_reg_reg[1][14]_0\(1) => u_Modulator_a_n_35,
      \reduced_reg_reg[1][14]_0\(0) => u_Modulator_a_n_36,
      \reduced_reg_reg[1][14]_1\(7) => u_Modulator_a_n_37,
      \reduced_reg_reg[1][14]_1\(6) => u_Modulator_a_n_38,
      \reduced_reg_reg[1][14]_1\(5) => u_Modulator_a_n_39,
      \reduced_reg_reg[1][14]_1\(4) => u_Modulator_a_n_40,
      \reduced_reg_reg[1][14]_1\(3) => u_Modulator_a_n_41,
      \reduced_reg_reg[1][14]_1\(2) => u_Modulator_a_n_42,
      \reduced_reg_reg[1][14]_1\(1) => u_Modulator_a_n_43,
      \reduced_reg_reg[1][14]_1\(0) => u_Modulator_a_n_44,
      \reduced_reg_reg[1][14]_2\(7) => u_Modulator_a_n_49,
      \reduced_reg_reg[1][14]_2\(6) => u_Modulator_a_n_50,
      \reduced_reg_reg[1][14]_2\(5) => u_Modulator_a_n_51,
      \reduced_reg_reg[1][14]_2\(4) => u_Modulator_a_n_52,
      \reduced_reg_reg[1][14]_2\(3) => u_Modulator_a_n_53,
      \reduced_reg_reg[1][14]_2\(2) => u_Modulator_a_n_54,
      \reduced_reg_reg[1][14]_2\(1) => u_Modulator_a_n_55,
      \reduced_reg_reg[1][14]_2\(0) => u_Modulator_a_n_56,
      \reduced_reg_reg[1][14]_3\(7) => u_Modulator_a_n_57,
      \reduced_reg_reg[1][14]_3\(6) => u_Modulator_a_n_58,
      \reduced_reg_reg[1][14]_3\(5) => u_Modulator_a_n_59,
      \reduced_reg_reg[1][14]_3\(4) => u_Modulator_a_n_60,
      \reduced_reg_reg[1][14]_3\(3) => u_Modulator_a_n_61,
      \reduced_reg_reg[1][14]_3\(2) => u_Modulator_a_n_62,
      \reduced_reg_reg[1][14]_3\(1) => u_Modulator_a_n_63,
      \reduced_reg_reg[1][14]_3\(0) => u_Modulator_a_n_64,
      \reduced_reg_reg[1][18]_0\(1) => u_Modulator_a_n_45,
      \reduced_reg_reg[1][18]_0\(0) => u_Modulator_a_n_46,
      \reduced_reg_reg[1][18]_1\(1) => u_Modulator_a_n_47,
      \reduced_reg_reg[1][18]_1\(0) => u_Modulator_a_n_48,
      \reduced_reg_reg[1][18]_2\(1) => u_Modulator_a_n_65,
      \reduced_reg_reg[1][18]_2\(0) => u_Modulator_a_n_66,
      \reduced_reg_reg[1][18]_3\(1) => u_Modulator_a_n_67,
      \reduced_reg_reg[1][18]_3\(0) => u_Modulator_a_n_68
    );
u_Modulator_b: entity work.zusys_PWM_SS_3L_ip_0_0_PWM_SS_3L_ip_src_Modulator_b
     port map (
      \AND_out10_inferred__0/i__carry__0_0\(7) => u_Modulator_a_n_37,
      \AND_out10_inferred__0/i__carry__0_0\(6) => u_Modulator_a_n_38,
      \AND_out10_inferred__0/i__carry__0_0\(5) => u_Modulator_a_n_39,
      \AND_out10_inferred__0/i__carry__0_0\(4) => u_Modulator_a_n_40,
      \AND_out10_inferred__0/i__carry__0_0\(3) => u_Modulator_a_n_41,
      \AND_out10_inferred__0/i__carry__0_0\(2) => u_Modulator_a_n_42,
      \AND_out10_inferred__0/i__carry__0_0\(1) => u_Modulator_a_n_43,
      \AND_out10_inferred__0/i__carry__0_0\(0) => u_Modulator_a_n_44,
      \AND_out10_inferred__0/i__carry__0_1\(7) => u_Modulator_a_n_29,
      \AND_out10_inferred__0/i__carry__0_1\(6) => u_Modulator_a_n_30,
      \AND_out10_inferred__0/i__carry__0_1\(5) => u_Modulator_a_n_31,
      \AND_out10_inferred__0/i__carry__0_1\(4) => u_Modulator_a_n_32,
      \AND_out10_inferred__0/i__carry__0_1\(3) => u_Modulator_a_n_33,
      \AND_out10_inferred__0/i__carry__0_1\(2) => u_Modulator_a_n_34,
      \AND_out10_inferred__0/i__carry__0_1\(1) => u_Modulator_a_n_35,
      \AND_out10_inferred__0/i__carry__0_1\(0) => u_Modulator_a_n_36,
      B(13 downto 0) => LimitPulseWidth_b_out1(13 downto 0),
      CEP => CEP,
      D(1) => u_Modulator_b_n_21,
      D(0) => Modulator_b_out1(1),
      DI(0) => u_Modulator_a_n_27,
      IPCORE_CLK => IPCORE_CLK,
      P(20 downto 0) => \modulating_signal_in_clock_cycles_1_reg__0\(20 downto 0),
      RSTP => RSTP,
      \Switch4_out1_1_reg[0]\(1) => u_Modulator_a_n_47,
      \Switch4_out1_1_reg[0]\(0) => u_Modulator_a_n_48,
      \Switch4_out1_1_reg[0]_0\(1) => u_Modulator_a_n_45,
      \Switch4_out1_1_reg[0]_0\(0) => u_Modulator_a_n_46,
      maximum_counter_value_1(19 downto 0) => maximum_counter_value_1(19 downto 0),
      \reduced_reg_1_reg[1]_9\(20 downto 0) => \reduced_reg_1_reg[1]_9\(20 downto 0)
    );
u_Modulator_c: entity work.zusys_PWM_SS_3L_ip_0_0_PWM_SS_3L_ip_src_Modulator_c
     port map (
      \AND_out10_inferred__0/i__carry__0_0\(7) => u_Modulator_a_n_57,
      \AND_out10_inferred__0/i__carry__0_0\(6) => u_Modulator_a_n_58,
      \AND_out10_inferred__0/i__carry__0_0\(5) => u_Modulator_a_n_59,
      \AND_out10_inferred__0/i__carry__0_0\(4) => u_Modulator_a_n_60,
      \AND_out10_inferred__0/i__carry__0_0\(3) => u_Modulator_a_n_61,
      \AND_out10_inferred__0/i__carry__0_0\(2) => u_Modulator_a_n_62,
      \AND_out10_inferred__0/i__carry__0_0\(1) => u_Modulator_a_n_63,
      \AND_out10_inferred__0/i__carry__0_0\(0) => u_Modulator_a_n_64,
      \AND_out10_inferred__0/i__carry__0_1\(7) => u_Modulator_a_n_49,
      \AND_out10_inferred__0/i__carry__0_1\(6) => u_Modulator_a_n_50,
      \AND_out10_inferred__0/i__carry__0_1\(5) => u_Modulator_a_n_51,
      \AND_out10_inferred__0/i__carry__0_1\(4) => u_Modulator_a_n_52,
      \AND_out10_inferred__0/i__carry__0_1\(3) => u_Modulator_a_n_53,
      \AND_out10_inferred__0/i__carry__0_1\(2) => u_Modulator_a_n_54,
      \AND_out10_inferred__0/i__carry__0_1\(1) => u_Modulator_a_n_55,
      \AND_out10_inferred__0/i__carry__0_1\(0) => u_Modulator_a_n_56,
      B(13 downto 0) => LimitPulseWidth_c_out1(13 downto 0),
      CEP => CEP,
      D(1) => u_Modulator_c_n_21,
      D(0) => Modulator_c_out1(1),
      IPCORE_CLK => IPCORE_CLK,
      P(20 downto 0) => \modulating_signal_in_clock_cycles_1_reg__0_0\(20 downto 0),
      RSTP => RSTP,
      \Switch5_out1_1_reg[0]\(1) => u_Modulator_a_n_67,
      \Switch5_out1_1_reg[0]\(0) => u_Modulator_a_n_68,
      \Switch5_out1_1_reg[0]_0\(1) => u_Modulator_a_n_65,
      \Switch5_out1_1_reg[0]_0\(0) => u_Modulator_a_n_66,
      \Switch5_out1_1_reg[1]\(0) => u_Modulator_a_n_28,
      maximum_counter_value_1(19 downto 0) => maximum_counter_value_1(19 downto 0),
      \reduced_reg_1_reg[1]_9\(20 downto 0) => \reduced_reg_1_reg[1]_9\(20 downto 0)
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity zusys_PWM_SS_3L_ip_0_0_PWM_SS_3L_ip_src_PWM_SS_Ctrl is
  port (
    D : out STD_LOGIC_VECTOR ( 0 to 0 );
    Period_Center : out STD_LOGIC;
    Period_Start : out STD_LOGIC;
    SSa2_OUT : out STD_LOGIC;
    SSa1_OUT : out STD_LOGIC;
    SSb2_OUT : out STD_LOGIC;
    SSb1_OUT : out STD_LOGIC;
    SSc2_OUT : out STD_LOGIC;
    SSc1_OUT : out STD_LOGIC;
    RSTP : in STD_LOGIC;
    CEP : in STD_LOGIC;
    IPCORE_CLK : in STD_LOGIC;
    \reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2\ : in STD_LOGIC_VECTOR ( 1 downto 0 );
    \delayMatch2_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2\ : in STD_LOGIC_VECTOR ( 1 downto 0 );
    \delayMatch5_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2\ : in STD_LOGIC_VECTOR ( 1 downto 0 );
    \delayMatch8_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2\ : in STD_LOGIC_VECTOR ( 1 downto 0 );
    write_PWM_en_AXI : in STD_LOGIC;
    \HDL_Counter2_count_reg[19]\ : in STD_LOGIC;
    \max_counter_value_1_reg[19]\ : in STD_LOGIC_VECTOR ( 19 downto 0 );
    \maximum_counter_value_1_reg[8]\ : in STD_LOGIC;
    \min_pulse_width_AXI_1_reg[13]\ : in STD_LOGIC_VECTOR ( 13 downto 0 );
    SSc2_IN_External : in STD_LOGIC;
    SSc1_IN_External : in STD_LOGIC;
    SSb2_IN_External : in STD_LOGIC;
    SSb1_IN_External : in STD_LOGIC;
    SSa2_IN_External : in STD_LOGIC;
    SSa1_IN_External : in STD_LOGIC;
    \delayMatch1_reg_reg[0][13]\ : in STD_LOGIC_VECTOR ( 13 downto 0 );
    m_u1_norm : in STD_LOGIC_VECTOR ( 13 downto 0 );
    \delayMatch3_reg_reg[0][13]\ : in STD_LOGIC_VECTOR ( 13 downto 0 );
    m_u2_norm : in STD_LOGIC_VECTOR ( 13 downto 0 );
    \delayMatch5_reg_reg[0][13]\ : in STD_LOGIC_VECTOR ( 13 downto 0 );
    m_u3_norm : in STD_LOGIC_VECTOR ( 13 downto 0 )
  );
  attribute ORIG_REF_NAME : string;
  attribute ORIG_REF_NAME of zusys_PWM_SS_3L_ip_0_0_PWM_SS_3L_ip_src_PWM_SS_Ctrl : entity is "PWM_SS_3L_ip_src_PWM_SS_Ctrl";
end zusys_PWM_SS_3L_ip_0_0_PWM_SS_3L_ip_src_PWM_SS_Ctrl;

architecture STRUCTURE of zusys_PWM_SS_3L_ip_0_0_PWM_SS_3L_ip_src_PWM_SS_Ctrl is
  signal Demux_out1 : STD_LOGIC_VECTOR ( 0 to 1 );
  signal Demux_out2 : STD_LOGIC_VECTOR ( 0 to 1 );
  signal Demux_out3 : STD_LOGIC_VECTOR ( 0 to 1 );
  signal GenPWM_out1 : STD_LOGIC_VECTOR ( 0 to 1 );
  signal GenPWM_out2 : STD_LOGIC_VECTOR ( 0 to 1 );
  signal GenPWM_out3 : STD_LOGIC_VECTOR ( 0 to 1 );
  signal GenPWM_out4 : STD_LOGIC;
  signal GenPWM_out5 : STD_LOGIC;
  signal Mux_out1 : STD_LOGIC_VECTOR ( 0 to 5 );
  signal U1_norm : STD_LOGIC_VECTOR ( 13 downto 0 );
  signal U2_norm : STD_LOGIC_VECTOR ( 13 downto 0 );
  signal U3_norm : STD_LOGIC_VECTOR ( 13 downto 0 );
  signal delayMatch1_reg : STD_LOGIC_VECTOR ( 0 to 0 );
  signal delayMatch2_reg : STD_LOGIC_VECTOR ( 0 to 0 );
  signal delayMatch3_1_reg : STD_LOGIC_VECTOR ( 0 to 0 );
  signal delayMatch3_1_reg_1 : STD_LOGIC_VECTOR ( 0 to 0 );
  signal delayMatch6_1_reg : STD_LOGIC_VECTOR ( 0 to 0 );
  signal delayMatch6_1_reg_1 : STD_LOGIC_VECTOR ( 0 to 0 );
  signal delayMatch_1_reg : STD_LOGIC_VECTOR ( 0 to 0 );
  signal delayMatch_1_reg_1 : STD_LOGIC_VECTOR ( 0 to 0 );
  signal \delayMatch_1_reg_1__0\ : STD_LOGIC_VECTOR ( 0 to 1 );
  signal delayMatch_1_reg_2 : STD_LOGIC_VECTOR ( 0 to 1 );
  signal delayMatch_1_reg_3 : STD_LOGIC_VECTOR ( 0 to 1 );
  signal delayMatch_1_reg_4 : STD_LOGIC_VECTOR ( 0 to 1 );
  signal delayMatch_1_reg_5 : STD_LOGIC_VECTOR ( 0 to 1 );
  signal \delayMatch_1_reg__0\ : STD_LOGIC_VECTOR ( 0 to 1 );
begin
\delayMatch1_reg[0][0]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FE02"
    )
        port map (
      I0 => \delayMatch1_reg_reg[0][13]\(0),
      I1 => \reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2\(0),
      I2 => \reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2\(1),
      I3 => m_u1_norm(0),
      O => U1_norm(0)
    );
\delayMatch1_reg[0][10]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FE02"
    )
        port map (
      I0 => \delayMatch1_reg_reg[0][13]\(10),
      I1 => \reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2\(0),
      I2 => \reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2\(1),
      I3 => m_u1_norm(10),
      O => U1_norm(10)
    );
\delayMatch1_reg[0][11]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FE02"
    )
        port map (
      I0 => \delayMatch1_reg_reg[0][13]\(11),
      I1 => \reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2\(0),
      I2 => \reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2\(1),
      I3 => m_u1_norm(11),
      O => U1_norm(11)
    );
\delayMatch1_reg[0][12]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FE02"
    )
        port map (
      I0 => \delayMatch1_reg_reg[0][13]\(12),
      I1 => \reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2\(0),
      I2 => \reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2\(1),
      I3 => m_u1_norm(12),
      O => U1_norm(12)
    );
\delayMatch1_reg[0][13]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FE02"
    )
        port map (
      I0 => \delayMatch1_reg_reg[0][13]\(13),
      I1 => \reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2\(0),
      I2 => \reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2\(1),
      I3 => m_u1_norm(13),
      O => U1_norm(13)
    );
\delayMatch1_reg[0][1]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FE02"
    )
        port map (
      I0 => \delayMatch1_reg_reg[0][13]\(1),
      I1 => \reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2\(0),
      I2 => \reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2\(1),
      I3 => m_u1_norm(1),
      O => U1_norm(1)
    );
\delayMatch1_reg[0][2]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FE02"
    )
        port map (
      I0 => \delayMatch1_reg_reg[0][13]\(2),
      I1 => \reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2\(0),
      I2 => \reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2\(1),
      I3 => m_u1_norm(2),
      O => U1_norm(2)
    );
\delayMatch1_reg[0][3]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FE02"
    )
        port map (
      I0 => \delayMatch1_reg_reg[0][13]\(3),
      I1 => \reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2\(0),
      I2 => \reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2\(1),
      I3 => m_u1_norm(3),
      O => U1_norm(3)
    );
\delayMatch1_reg[0][4]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FE02"
    )
        port map (
      I0 => \delayMatch1_reg_reg[0][13]\(4),
      I1 => \reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2\(0),
      I2 => \reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2\(1),
      I3 => m_u1_norm(4),
      O => U1_norm(4)
    );
\delayMatch1_reg[0][5]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FE02"
    )
        port map (
      I0 => \delayMatch1_reg_reg[0][13]\(5),
      I1 => \reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2\(0),
      I2 => \reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2\(1),
      I3 => m_u1_norm(5),
      O => U1_norm(5)
    );
\delayMatch1_reg[0][6]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FE02"
    )
        port map (
      I0 => \delayMatch1_reg_reg[0][13]\(6),
      I1 => \reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2\(0),
      I2 => \reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2\(1),
      I3 => m_u1_norm(6),
      O => U1_norm(6)
    );
\delayMatch1_reg[0][7]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FE02"
    )
        port map (
      I0 => \delayMatch1_reg_reg[0][13]\(7),
      I1 => \reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2\(0),
      I2 => \reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2\(1),
      I3 => m_u1_norm(7),
      O => U1_norm(7)
    );
\delayMatch1_reg[0][8]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FE02"
    )
        port map (
      I0 => \delayMatch1_reg_reg[0][13]\(8),
      I1 => \reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2\(0),
      I2 => \reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2\(1),
      I3 => m_u1_norm(8),
      O => U1_norm(8)
    );
\delayMatch1_reg[0][9]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FE02"
    )
        port map (
      I0 => \delayMatch1_reg_reg[0][13]\(9),
      I1 => \reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2\(0),
      I2 => \reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2\(1),
      I3 => m_u1_norm(9),
      O => U1_norm(9)
    );
\delayMatch1_reg_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => GenPWM_out4,
      Q => delayMatch1_reg(0),
      R => RSTP
    );
\delayMatch1_reg_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => delayMatch1_reg(0),
      Q => Period_Center,
      R => RSTP
    );
\delayMatch2_reg_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => GenPWM_out5,
      Q => delayMatch2_reg(0),
      R => RSTP
    );
\delayMatch2_reg_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => delayMatch2_reg(0),
      Q => Period_Start,
      R => RSTP
    );
\delayMatch3_reg[0][0]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FE02"
    )
        port map (
      I0 => \delayMatch3_reg_reg[0][13]\(0),
      I1 => \reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2\(0),
      I2 => \reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2\(1),
      I3 => m_u2_norm(0),
      O => U2_norm(0)
    );
\delayMatch3_reg[0][10]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FE02"
    )
        port map (
      I0 => \delayMatch3_reg_reg[0][13]\(10),
      I1 => \reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2\(0),
      I2 => \reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2\(1),
      I3 => m_u2_norm(10),
      O => U2_norm(10)
    );
\delayMatch3_reg[0][11]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FE02"
    )
        port map (
      I0 => \delayMatch3_reg_reg[0][13]\(11),
      I1 => \reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2\(0),
      I2 => \reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2\(1),
      I3 => m_u2_norm(11),
      O => U2_norm(11)
    );
\delayMatch3_reg[0][12]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FE02"
    )
        port map (
      I0 => \delayMatch3_reg_reg[0][13]\(12),
      I1 => \reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2\(0),
      I2 => \reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2\(1),
      I3 => m_u2_norm(12),
      O => U2_norm(12)
    );
\delayMatch3_reg[0][13]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FE02"
    )
        port map (
      I0 => \delayMatch3_reg_reg[0][13]\(13),
      I1 => \reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2\(0),
      I2 => \reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2\(1),
      I3 => m_u2_norm(13),
      O => U2_norm(13)
    );
\delayMatch3_reg[0][1]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FE02"
    )
        port map (
      I0 => \delayMatch3_reg_reg[0][13]\(1),
      I1 => \reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2\(0),
      I2 => \reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2\(1),
      I3 => m_u2_norm(1),
      O => U2_norm(1)
    );
\delayMatch3_reg[0][2]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FE02"
    )
        port map (
      I0 => \delayMatch3_reg_reg[0][13]\(2),
      I1 => \reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2\(0),
      I2 => \reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2\(1),
      I3 => m_u2_norm(2),
      O => U2_norm(2)
    );
\delayMatch3_reg[0][3]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FE02"
    )
        port map (
      I0 => \delayMatch3_reg_reg[0][13]\(3),
      I1 => \reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2\(0),
      I2 => \reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2\(1),
      I3 => m_u2_norm(3),
      O => U2_norm(3)
    );
\delayMatch3_reg[0][4]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FE02"
    )
        port map (
      I0 => \delayMatch3_reg_reg[0][13]\(4),
      I1 => \reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2\(0),
      I2 => \reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2\(1),
      I3 => m_u2_norm(4),
      O => U2_norm(4)
    );
\delayMatch3_reg[0][5]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FE02"
    )
        port map (
      I0 => \delayMatch3_reg_reg[0][13]\(5),
      I1 => \reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2\(0),
      I2 => \reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2\(1),
      I3 => m_u2_norm(5),
      O => U2_norm(5)
    );
\delayMatch3_reg[0][6]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FE02"
    )
        port map (
      I0 => \delayMatch3_reg_reg[0][13]\(6),
      I1 => \reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2\(0),
      I2 => \reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2\(1),
      I3 => m_u2_norm(6),
      O => U2_norm(6)
    );
\delayMatch3_reg[0][7]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FE02"
    )
        port map (
      I0 => \delayMatch3_reg_reg[0][13]\(7),
      I1 => \reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2\(0),
      I2 => \reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2\(1),
      I3 => m_u2_norm(7),
      O => U2_norm(7)
    );
\delayMatch3_reg[0][8]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FE02"
    )
        port map (
      I0 => \delayMatch3_reg_reg[0][13]\(8),
      I1 => \reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2\(0),
      I2 => \reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2\(1),
      I3 => m_u2_norm(8),
      O => U2_norm(8)
    );
\delayMatch3_reg[0][9]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FE02"
    )
        port map (
      I0 => \delayMatch3_reg_reg[0][13]\(9),
      I1 => \reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2\(0),
      I2 => \reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2\(1),
      I3 => m_u2_norm(9),
      O => U2_norm(9)
    );
\delayMatch5_reg[0][0]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FE02"
    )
        port map (
      I0 => \delayMatch5_reg_reg[0][13]\(0),
      I1 => \reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2\(0),
      I2 => \reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2\(1),
      I3 => m_u3_norm(0),
      O => U3_norm(0)
    );
\delayMatch5_reg[0][10]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FE02"
    )
        port map (
      I0 => \delayMatch5_reg_reg[0][13]\(10),
      I1 => \reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2\(0),
      I2 => \reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2\(1),
      I3 => m_u3_norm(10),
      O => U3_norm(10)
    );
\delayMatch5_reg[0][11]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FE02"
    )
        port map (
      I0 => \delayMatch5_reg_reg[0][13]\(11),
      I1 => \reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2\(0),
      I2 => \reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2\(1),
      I3 => m_u3_norm(11),
      O => U3_norm(11)
    );
\delayMatch5_reg[0][12]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FE02"
    )
        port map (
      I0 => \delayMatch5_reg_reg[0][13]\(12),
      I1 => \reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2\(0),
      I2 => \reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2\(1),
      I3 => m_u3_norm(12),
      O => U3_norm(12)
    );
\delayMatch5_reg[0][13]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FE02"
    )
        port map (
      I0 => \delayMatch5_reg_reg[0][13]\(13),
      I1 => \reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2\(0),
      I2 => \reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2\(1),
      I3 => m_u3_norm(13),
      O => U3_norm(13)
    );
\delayMatch5_reg[0][1]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FE02"
    )
        port map (
      I0 => \delayMatch5_reg_reg[0][13]\(1),
      I1 => \reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2\(0),
      I2 => \reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2\(1),
      I3 => m_u3_norm(1),
      O => U3_norm(1)
    );
\delayMatch5_reg[0][2]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FE02"
    )
        port map (
      I0 => \delayMatch5_reg_reg[0][13]\(2),
      I1 => \reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2\(0),
      I2 => \reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2\(1),
      I3 => m_u3_norm(2),
      O => U3_norm(2)
    );
\delayMatch5_reg[0][3]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FE02"
    )
        port map (
      I0 => \delayMatch5_reg_reg[0][13]\(3),
      I1 => \reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2\(0),
      I2 => \reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2\(1),
      I3 => m_u3_norm(3),
      O => U3_norm(3)
    );
\delayMatch5_reg[0][4]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FE02"
    )
        port map (
      I0 => \delayMatch5_reg_reg[0][13]\(4),
      I1 => \reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2\(0),
      I2 => \reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2\(1),
      I3 => m_u3_norm(4),
      O => U3_norm(4)
    );
\delayMatch5_reg[0][5]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FE02"
    )
        port map (
      I0 => \delayMatch5_reg_reg[0][13]\(5),
      I1 => \reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2\(0),
      I2 => \reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2\(1),
      I3 => m_u3_norm(5),
      O => U3_norm(5)
    );
\delayMatch5_reg[0][6]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FE02"
    )
        port map (
      I0 => \delayMatch5_reg_reg[0][13]\(6),
      I1 => \reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2\(0),
      I2 => \reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2\(1),
      I3 => m_u3_norm(6),
      O => U3_norm(6)
    );
\delayMatch5_reg[0][7]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FE02"
    )
        port map (
      I0 => \delayMatch5_reg_reg[0][13]\(7),
      I1 => \reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2\(0),
      I2 => \reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2\(1),
      I3 => m_u3_norm(7),
      O => U3_norm(7)
    );
\delayMatch5_reg[0][8]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FE02"
    )
        port map (
      I0 => \delayMatch5_reg_reg[0][13]\(8),
      I1 => \reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2\(0),
      I2 => \reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2\(1),
      I3 => m_u3_norm(8),
      O => U3_norm(8)
    );
\delayMatch5_reg[0][9]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FE02"
    )
        port map (
      I0 => \delayMatch5_reg_reg[0][13]\(9),
      I1 => \reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2\(0),
      I2 => \reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2\(1),
      I3 => m_u3_norm(9),
      O => U3_norm(9)
    );
\delayMatch_1_reg_1_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => SSa2_IN_External,
      Q => \delayMatch_1_reg_1__0\(0),
      R => RSTP
    );
\delayMatch_1_reg_1_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \delayMatch_1_reg_1__0\(0),
      Q => \delayMatch_1_reg_1__0\(1),
      R => RSTP
    );
\delayMatch_1_reg_1_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \delayMatch_1_reg_1__0\(1),
      Q => Mux_out1(1),
      R => RSTP
    );
\delayMatch_1_reg_2_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => SSb1_IN_External,
      Q => delayMatch_1_reg_2(0),
      R => RSTP
    );
\delayMatch_1_reg_2_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => delayMatch_1_reg_2(0),
      Q => delayMatch_1_reg_2(1),
      R => RSTP
    );
\delayMatch_1_reg_2_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => delayMatch_1_reg_2(1),
      Q => Mux_out1(2),
      R => RSTP
    );
\delayMatch_1_reg_3_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => SSb2_IN_External,
      Q => delayMatch_1_reg_3(0),
      R => RSTP
    );
\delayMatch_1_reg_3_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => delayMatch_1_reg_3(0),
      Q => delayMatch_1_reg_3(1),
      R => RSTP
    );
\delayMatch_1_reg_3_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => delayMatch_1_reg_3(1),
      Q => Mux_out1(3),
      R => RSTP
    );
\delayMatch_1_reg_4_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => SSc1_IN_External,
      Q => delayMatch_1_reg_4(0),
      R => RSTP
    );
\delayMatch_1_reg_4_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => delayMatch_1_reg_4(0),
      Q => delayMatch_1_reg_4(1),
      R => RSTP
    );
\delayMatch_1_reg_4_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => delayMatch_1_reg_4(1),
      Q => Mux_out1(4),
      R => RSTP
    );
\delayMatch_1_reg_5_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => SSc2_IN_External,
      Q => delayMatch_1_reg_5(0),
      R => RSTP
    );
\delayMatch_1_reg_5_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => delayMatch_1_reg_5(0),
      Q => delayMatch_1_reg_5(1),
      R => RSTP
    );
\delayMatch_1_reg_5_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => delayMatch_1_reg_5(1),
      Q => Mux_out1(5),
      R => RSTP
    );
\delayMatch_1_reg_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => SSa1_IN_External,
      Q => \delayMatch_1_reg__0\(0),
      R => RSTP
    );
\delayMatch_1_reg_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \delayMatch_1_reg__0\(0),
      Q => \delayMatch_1_reg__0\(1),
      R => RSTP
    );
\delayMatch_1_reg_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => CEP,
      D => \delayMatch_1_reg__0\(1),
      Q => Mux_out1(0),
      R => RSTP
    );
u_Chose_SS: entity work.zusys_PWM_SS_3L_ip_0_0_PWM_SS_3L_ip_src_Chose_SS
     port map (
      CEP => CEP,
      Demux_out1(0 to 1) => Demux_out1(0 to 1),
      Demux_out2(0 to 1) => Demux_out2(0 to 1),
      Demux_out3(0 to 1) => Demux_out3(0 to 1),
      IPCORE_CLK => IPCORE_CLK,
      Q(1) => GenPWM_out1(0),
      Q(0) => GenPWM_out1(1),
      RSTP => RSTP,
      SSa1_OUT => SSa1_OUT,
      SSa2_OUT => SSa2_OUT,
      SSb1_OUT => SSb1_OUT,
      SSb1_OUT_0(1) => GenPWM_out2(0),
      SSb1_OUT_0(0) => GenPWM_out2(1),
      SSb2_OUT => SSb2_OUT,
      SSc1_OUT => SSc1_OUT,
      SSc1_OUT_0(1) => GenPWM_out3(0),
      SSc1_OUT_0(0) => GenPWM_out3(1),
      SSc2_OUT => SSc2_OUT,
      \delayMatch2_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2_0\(1 downto 0) => \delayMatch2_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2\(1 downto 0),
      delayMatch3_1_reg(0) => delayMatch3_1_reg(0),
      delayMatch3_1_reg_1(0) => delayMatch3_1_reg_1(0),
      \delayMatch5_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2_0\(1 downto 0) => \delayMatch5_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2\(1 downto 0),
      delayMatch6_1_reg(0) => delayMatch6_1_reg(0),
      delayMatch6_1_reg_1(0) => delayMatch6_1_reg_1(0),
      \delayMatch8_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2_0\(1 downto 0) => \delayMatch8_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2\(1 downto 0),
      delayMatch_1_reg(0) => delayMatch_1_reg(0),
      delayMatch_1_reg_1(0) => delayMatch_1_reg_1(0),
      \reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2_0\(0) => \reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2\(1)
    );
u_GenPWM: entity work.zusys_PWM_SS_3L_ip_0_0_PWM_SS_3L_ip_src_GenPWM
     port map (
      CEP => CEP,
      D(0) => GenPWM_out4,
      Demux_out1(0 to 1) => Demux_out1(0 to 1),
      Demux_out2(0 to 1) => Demux_out2(0 to 1),
      Demux_out3(0 to 1) => Demux_out3(0 to 1),
      GenPWM_out5 => GenPWM_out5,
      \HDL_Counter2_count_reg[19]_0\ => \HDL_Counter2_count_reg[19]\,
      IPCORE_CLK => IPCORE_CLK,
      Mux_out1(0 to 5) => Mux_out1(0 to 5),
      PWM_en_AXI_2_reg_0 => D(0),
      Q(1) => GenPWM_out1(0),
      Q(0) => GenPWM_out1(1),
      RSTP => RSTP,
      \Switch4_out1_1_reg[0]_0\(1) => GenPWM_out2(0),
      \Switch4_out1_1_reg[0]_0\(0) => GenPWM_out2(1),
      \Switch5_out1_1_reg[0]_0\(1) => GenPWM_out3(0),
      \Switch5_out1_1_reg[0]_0\(0) => GenPWM_out3(1),
      \delayMatch1_reg_reg[0][13]_0\(13 downto 0) => U1_norm(13 downto 0),
      delayMatch3_1_reg(0) => delayMatch3_1_reg(0),
      delayMatch3_1_reg_1(0) => delayMatch3_1_reg_1(0),
      \delayMatch3_reg_reg[0][13]_0\(13 downto 0) => U2_norm(13 downto 0),
      \delayMatch5_reg_reg[0][13]_0\(13 downto 0) => U3_norm(13 downto 0),
      delayMatch6_1_reg(0) => delayMatch6_1_reg(0),
      delayMatch6_1_reg_1(0) => delayMatch6_1_reg_1(0),
      delayMatch_1_reg(0) => delayMatch_1_reg(0),
      delayMatch_1_reg_1(0) => delayMatch_1_reg_1(0),
      \max_counter_value_1_reg[19]_0\(19 downto 0) => \max_counter_value_1_reg[19]\(19 downto 0),
      \maximum_counter_value_1_reg[8]_0\ => \maximum_counter_value_1_reg[8]\,
      \min_pulse_width_AXI_1_reg[13]_0\(13 downto 0) => \min_pulse_width_AXI_1_reg[13]\(13 downto 0),
      write_PWM_en_AXI => write_PWM_en_AXI
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity zusys_PWM_SS_3L_ip_0_0_PWM_SS_3L_ip_dut is
  port (
    PWM_en_AXI_2_reg : out STD_LOGIC;
    Period_Center : out STD_LOGIC;
    Period_Start : out STD_LOGIC;
    SSa2_OUT : out STD_LOGIC;
    SSa1_OUT : out STD_LOGIC;
    SSb2_OUT : out STD_LOGIC;
    SSb1_OUT : out STD_LOGIC;
    SSc2_OUT : out STD_LOGIC;
    SSc1_OUT : out STD_LOGIC;
    RSTP : in STD_LOGIC;
    CEP : in STD_LOGIC;
    IPCORE_CLK : in STD_LOGIC;
    \reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2\ : in STD_LOGIC_VECTOR ( 1 downto 0 );
    \delayMatch2_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2\ : in STD_LOGIC_VECTOR ( 1 downto 0 );
    \delayMatch5_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2\ : in STD_LOGIC_VECTOR ( 1 downto 0 );
    \delayMatch8_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2\ : in STD_LOGIC_VECTOR ( 1 downto 0 );
    write_PWM_en_AXI : in STD_LOGIC;
    \HDL_Counter2_count_reg[19]\ : in STD_LOGIC;
    D : in STD_LOGIC_VECTOR ( 19 downto 0 );
    \maximum_counter_value_1_reg[8]\ : in STD_LOGIC;
    \min_pulse_width_AXI_1_reg[13]\ : in STD_LOGIC_VECTOR ( 13 downto 0 );
    SSc2_IN_External : in STD_LOGIC;
    SSc1_IN_External : in STD_LOGIC;
    SSb2_IN_External : in STD_LOGIC;
    SSb1_IN_External : in STD_LOGIC;
    SSa2_IN_External : in STD_LOGIC;
    SSa1_IN_External : in STD_LOGIC;
    \delayMatch1_reg_reg[0][13]\ : in STD_LOGIC_VECTOR ( 13 downto 0 );
    m_u1_norm : in STD_LOGIC_VECTOR ( 13 downto 0 );
    \delayMatch3_reg_reg[0][13]\ : in STD_LOGIC_VECTOR ( 13 downto 0 );
    m_u2_norm : in STD_LOGIC_VECTOR ( 13 downto 0 );
    \delayMatch5_reg_reg[0][13]\ : in STD_LOGIC_VECTOR ( 13 downto 0 );
    m_u3_norm : in STD_LOGIC_VECTOR ( 13 downto 0 )
  );
  attribute ORIG_REF_NAME : string;
  attribute ORIG_REF_NAME of zusys_PWM_SS_3L_ip_0_0_PWM_SS_3L_ip_dut : entity is "PWM_SS_3L_ip_dut";
end zusys_PWM_SS_3L_ip_0_0_PWM_SS_3L_ip_dut;

architecture STRUCTURE of zusys_PWM_SS_3L_ip_0_0_PWM_SS_3L_ip_dut is
begin
u_PWM_SS_3L_ip_src_PWM_SS_Ctrl: entity work.zusys_PWM_SS_3L_ip_0_0_PWM_SS_3L_ip_src_PWM_SS_Ctrl
     port map (
      CEP => CEP,
      D(0) => PWM_en_AXI_2_reg,
      \HDL_Counter2_count_reg[19]\ => \HDL_Counter2_count_reg[19]\,
      IPCORE_CLK => IPCORE_CLK,
      Period_Center => Period_Center,
      Period_Start => Period_Start,
      RSTP => RSTP,
      SSa1_IN_External => SSa1_IN_External,
      SSa1_OUT => SSa1_OUT,
      SSa2_IN_External => SSa2_IN_External,
      SSa2_OUT => SSa2_OUT,
      SSb1_IN_External => SSb1_IN_External,
      SSb1_OUT => SSb1_OUT,
      SSb2_IN_External => SSb2_IN_External,
      SSb2_OUT => SSb2_OUT,
      SSc1_IN_External => SSc1_IN_External,
      SSc1_OUT => SSc1_OUT,
      SSc2_IN_External => SSc2_IN_External,
      SSc2_OUT => SSc2_OUT,
      \delayMatch1_reg_reg[0][13]\(13 downto 0) => \delayMatch1_reg_reg[0][13]\(13 downto 0),
      \delayMatch2_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2\(1 downto 0) => \delayMatch2_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2\(1 downto 0),
      \delayMatch3_reg_reg[0][13]\(13 downto 0) => \delayMatch3_reg_reg[0][13]\(13 downto 0),
      \delayMatch5_reg_reg[0][13]\(13 downto 0) => \delayMatch5_reg_reg[0][13]\(13 downto 0),
      \delayMatch5_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2\(1 downto 0) => \delayMatch5_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2\(1 downto 0),
      \delayMatch8_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2\(1 downto 0) => \delayMatch8_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2\(1 downto 0),
      m_u1_norm(13 downto 0) => m_u1_norm(13 downto 0),
      m_u2_norm(13 downto 0) => m_u2_norm(13 downto 0),
      m_u3_norm(13 downto 0) => m_u3_norm(13 downto 0),
      \max_counter_value_1_reg[19]\(19 downto 0) => D(19 downto 0),
      \maximum_counter_value_1_reg[8]\ => \maximum_counter_value_1_reg[8]\,
      \min_pulse_width_AXI_1_reg[13]\(13 downto 0) => \min_pulse_width_AXI_1_reg[13]\(13 downto 0),
      \reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2\(1 downto 0) => \reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2\(1 downto 0),
      write_PWM_en_AXI => write_PWM_en_AXI
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity zusys_PWM_SS_3L_ip_0_0_PWM_SS_3L_ip is
  port (
    AXI4_Lite_RVALID : out STD_LOGIC;
    AXI4_Lite_BVALID : out STD_LOGIC;
    AXI4_Lite_WREADY : out STD_LOGIC;
    Period_Center : out STD_LOGIC;
    Period_Start : out STD_LOGIC;
    AXI4_Lite_ARREADY : out STD_LOGIC;
    AXI4_Lite_AWREADY : out STD_LOGIC;
    SSa2_OUT : out STD_LOGIC;
    SSa1_OUT : out STD_LOGIC;
    SSb2_OUT : out STD_LOGIC;
    SSb1_OUT : out STD_LOGIC;
    SSc2_OUT : out STD_LOGIC;
    SSc1_OUT : out STD_LOGIC;
    AXI4_Lite_RDATA : out STD_LOGIC_VECTOR ( 0 to 0 );
    IPCORE_CLK : in STD_LOGIC;
    AXI4_Lite_ARADDR : in STD_LOGIC_VECTOR ( 13 downto 0 );
    AXI4_Lite_ARVALID : in STD_LOGIC;
    AXI4_Lite_ACLK : in STD_LOGIC;
    AXI4_Lite_AWADDR : in STD_LOGIC_VECTOR ( 13 downto 0 );
    AXI4_Lite_WDATA : in STD_LOGIC_VECTOR ( 19 downto 0 );
    SSc2_IN_External : in STD_LOGIC;
    SSc1_IN_External : in STD_LOGIC;
    SSb2_IN_External : in STD_LOGIC;
    SSb1_IN_External : in STD_LOGIC;
    SSa2_IN_External : in STD_LOGIC;
    SSa1_IN_External : in STD_LOGIC;
    AXI4_Lite_RREADY : in STD_LOGIC;
    AXI4_Lite_AWVALID : in STD_LOGIC;
    AXI4_Lite_ARESETN : in STD_LOGIC;
    IPCORE_RESETN : in STD_LOGIC;
    AXI4_Lite_BREADY : in STD_LOGIC;
    AXI4_Lite_WVALID : in STD_LOGIC;
    AXI4_Lite_WSTRB : in STD_LOGIC_VECTOR ( 3 downto 0 );
    m_u1_norm : in STD_LOGIC_VECTOR ( 13 downto 0 );
    m_u2_norm : in STD_LOGIC_VECTOR ( 13 downto 0 );
    m_u3_norm : in STD_LOGIC_VECTOR ( 13 downto 0 )
  );
  attribute ORIG_REF_NAME : string;
  attribute ORIG_REF_NAME of zusys_PWM_SS_3L_ip_0_0_PWM_SS_3L_ip : entity is "PWM_SS_3L_ip";
end zusys_PWM_SS_3L_ip_0_0_PWM_SS_3L_ip;

architecture STRUCTURE of zusys_PWM_SS_3L_ip_0_0_PWM_SS_3L_ip is
  signal Mode_AXI : STD_LOGIC_VECTOR ( 1 downto 0 );
  signal TriState_HB1_AXI : STD_LOGIC_VECTOR ( 1 downto 0 );
  signal TriState_HB2_AXI : STD_LOGIC_VECTOR ( 1 downto 0 );
  signal TriState_HB3_AXI : STD_LOGIC_VECTOR ( 1 downto 0 );
  signal m_u1_norm_AXI : STD_LOGIC_VECTOR ( 13 downto 0 );
  signal m_u2_norm_AXI : STD_LOGIC_VECTOR ( 13 downto 0 );
  signal m_u3_norm_AXI : STD_LOGIC_VECTOR ( 13 downto 0 );
  signal reset : STD_LOGIC;
  signal reset_in : STD_LOGIC;
  signal u_PWM_SS_3L_ip_axi_lite_inst_n_5 : STD_LOGIC;
  signal \u_PWM_SS_3L_ip_axi_lite_module_inst/soft_reset\ : STD_LOGIC;
  signal u_PWM_SS_3L_ip_dut_inst_n_0 : STD_LOGIC;
  signal u_PWM_SS_3L_ip_reset_sync_inst_n_1 : STD_LOGIC;
  signal write_PWM_counter_max_value_int_AXI : STD_LOGIC_VECTOR ( 19 downto 0 );
  signal write_PWM_en_AXI : STD_LOGIC;
  signal write_PWM_min_pulse_width_0to1_AXI : STD_LOGIC_VECTOR ( 13 downto 0 );
  signal write_axi_enable : STD_LOGIC;
begin
u_PWM_SS_3L_ip_axi_lite_inst: entity work.zusys_PWM_SS_3L_ip_0_0_PWM_SS_3L_ip_axi_lite
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
      AXI4_Lite_RDATA(0) => AXI4_Lite_RDATA(0),
      AXI4_Lite_RREADY => AXI4_Lite_RREADY,
      AXI4_Lite_WDATA(19 downto 0) => AXI4_Lite_WDATA(19 downto 0),
      AXI4_Lite_WSTRB(3 downto 0) => AXI4_Lite_WSTRB(3 downto 0),
      AXI4_Lite_WVALID => AXI4_Lite_WVALID,
      CEP => write_axi_enable,
      FSM_sequential_axi_lite_rstate_reg => AXI4_Lite_RVALID,
      \HDL_Counter2_count_reg[19]\ => u_PWM_SS_3L_ip_dut_inst_n_0,
      IPCORE_RESETN => IPCORE_RESETN,
      Q(1) => AXI4_Lite_BVALID,
      Q(0) => AXI4_Lite_WREADY,
      RSTP => reset,
      \data_reg_Mode_AXI_1_1_reg[1]\(1 downto 0) => Mode_AXI(1 downto 0),
      \data_reg_PWM_counter_max_value_int_AXI_1_1_reg[19]\(19 downto 0) => write_PWM_counter_max_value_int_AXI(19 downto 0),
      \data_reg_PWM_min_pulse_width_0to1_AXI_1_1_reg[13]\(13 downto 0) => write_PWM_min_pulse_width_0to1_AXI(13 downto 0),
      \data_reg_TriState_HB1_AXI_1_1_reg[1]\(1 downto 0) => TriState_HB1_AXI(1 downto 0),
      \data_reg_TriState_HB2_AXI_1_1_reg[1]\(1 downto 0) => TriState_HB2_AXI(1 downto 0),
      \data_reg_TriState_HB3_AXI_1_1_reg[1]\(1 downto 0) => TriState_HB3_AXI(1 downto 0),
      data_reg_axi_enable_1_1_reg => u_PWM_SS_3L_ip_axi_lite_inst_n_5,
      \data_reg_m_u1_norm_AXI_1_1_reg[13]\(13 downto 0) => m_u1_norm_AXI(13 downto 0),
      \data_reg_m_u2_norm_AXI_1_1_reg[13]\(13 downto 0) => m_u2_norm_AXI(13 downto 0),
      \data_reg_m_u3_norm_AXI_1_1_reg[13]\(13 downto 0) => m_u3_norm_AXI(13 downto 0),
      reset_in => reset_in,
      soft_reset => \u_PWM_SS_3L_ip_axi_lite_module_inst/soft_reset\,
      write_PWM_en_AXI => write_PWM_en_AXI
    );
u_PWM_SS_3L_ip_dut_inst: entity work.zusys_PWM_SS_3L_ip_0_0_PWM_SS_3L_ip_dut
     port map (
      CEP => write_axi_enable,
      D(19 downto 0) => write_PWM_counter_max_value_int_AXI(19 downto 0),
      \HDL_Counter2_count_reg[19]\ => u_PWM_SS_3L_ip_axi_lite_inst_n_5,
      IPCORE_CLK => IPCORE_CLK,
      PWM_en_AXI_2_reg => u_PWM_SS_3L_ip_dut_inst_n_0,
      Period_Center => Period_Center,
      Period_Start => Period_Start,
      RSTP => reset,
      SSa1_IN_External => SSa1_IN_External,
      SSa1_OUT => SSa1_OUT,
      SSa2_IN_External => SSa2_IN_External,
      SSa2_OUT => SSa2_OUT,
      SSb1_IN_External => SSb1_IN_External,
      SSb1_OUT => SSb1_OUT,
      SSb2_IN_External => SSb2_IN_External,
      SSb2_OUT => SSb2_OUT,
      SSc1_IN_External => SSc1_IN_External,
      SSc1_OUT => SSc1_OUT,
      SSc2_IN_External => SSc2_IN_External,
      SSc2_OUT => SSc2_OUT,
      \delayMatch1_reg_reg[0][13]\(13 downto 0) => m_u1_norm_AXI(13 downto 0),
      \delayMatch2_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2\(1 downto 0) => TriState_HB1_AXI(1 downto 0),
      \delayMatch3_reg_reg[0][13]\(13 downto 0) => m_u2_norm_AXI(13 downto 0),
      \delayMatch5_reg_reg[0][13]\(13 downto 0) => m_u3_norm_AXI(13 downto 0),
      \delayMatch5_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2\(1 downto 0) => TriState_HB2_AXI(1 downto 0),
      \delayMatch8_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2\(1 downto 0) => TriState_HB3_AXI(1 downto 0),
      m_u1_norm(13 downto 0) => m_u1_norm(13 downto 0),
      m_u2_norm(13 downto 0) => m_u2_norm(13 downto 0),
      m_u3_norm(13 downto 0) => m_u3_norm(13 downto 0),
      \maximum_counter_value_1_reg[8]\ => u_PWM_SS_3L_ip_reset_sync_inst_n_1,
      \min_pulse_width_AXI_1_reg[13]\(13 downto 0) => write_PWM_min_pulse_width_0to1_AXI(13 downto 0),
      \reduced_reg_reg[3][1]_U0_u_PWM_SS_3L_ip_dut_inst_u_PWM_SS_3L_ip_src_PWM_SS_Ctrl_u_Chose_SS_reduced_reg_reg_r_2\(1 downto 0) => Mode_AXI(1 downto 0),
      write_PWM_en_AXI => write_PWM_en_AXI
    );
u_PWM_SS_3L_ip_reset_sync_inst: entity work.zusys_PWM_SS_3L_ip_0_0_PWM_SS_3L_ip_reset_sync
     port map (
      AXI4_Lite_ARESETN => AXI4_Lite_ARESETN,
      CEP => write_axi_enable,
      IPCORE_CLK => IPCORE_CLK,
      IPCORE_RESETN => IPCORE_RESETN,
      RSTP => reset,
      reset_in => reset_in,
      reset_out_reg_0 => u_PWM_SS_3L_ip_reset_sync_inst_n_1,
      soft_reset => \u_PWM_SS_3L_ip_axi_lite_module_inst/soft_reset\
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity zusys_PWM_SS_3L_ip_0_0 is
  port (
    IPCORE_CLK : in STD_LOGIC;
    IPCORE_RESETN : in STD_LOGIC;
    m_u1_norm : in STD_LOGIC_VECTOR ( 13 downto 0 );
    m_u2_norm : in STD_LOGIC_VECTOR ( 13 downto 0 );
    m_u3_norm : in STD_LOGIC_VECTOR ( 13 downto 0 );
    SSa1_IN_External : in STD_LOGIC;
    SSa2_IN_External : in STD_LOGIC;
    SSb1_IN_External : in STD_LOGIC;
    SSb2_IN_External : in STD_LOGIC;
    SSc1_IN_External : in STD_LOGIC;
    SSc2_IN_External : in STD_LOGIC;
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
    SSa1_OUT : out STD_LOGIC;
    SSa2_OUT : out STD_LOGIC;
    SSb1_OUT : out STD_LOGIC;
    SSb2_OUT : out STD_LOGIC;
    SSc1_OUT : out STD_LOGIC;
    SSc2_OUT : out STD_LOGIC;
    Period_Center : out STD_LOGIC;
    Period_Start : out STD_LOGIC;
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
  attribute NotValidForBitStream of zusys_PWM_SS_3L_ip_0_0 : entity is true;
  attribute CHECK_LICENSE_TYPE : string;
  attribute CHECK_LICENSE_TYPE of zusys_PWM_SS_3L_ip_0_0 : entity is "zusys_PWM_SS_3L_ip_0_0,PWM_SS_3L_ip,{}";
  attribute downgradeipidentifiedwarnings : string;
  attribute downgradeipidentifiedwarnings of zusys_PWM_SS_3L_ip_0_0 : entity is "yes";
  attribute ip_definition_source : string;
  attribute ip_definition_source of zusys_PWM_SS_3L_ip_0_0 : entity is "package_project";
  attribute x_core_info : string;
  attribute x_core_info of zusys_PWM_SS_3L_ip_0_0 : entity is "PWM_SS_3L_ip,Vivado 2020.1.1";
end zusys_PWM_SS_3L_ip_0_0;

architecture STRUCTURE of zusys_PWM_SS_3L_ip_0_0 is
  signal \<const0>\ : STD_LOGIC;
  signal \^axi4_lite_rdata\ : STD_LOGIC_VECTOR ( 29 to 29 );
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
  AXI4_Lite_RDATA(31) <= \<const0>\;
  AXI4_Lite_RDATA(30) <= \^axi4_lite_rdata\(29);
  AXI4_Lite_RDATA(29) <= \^axi4_lite_rdata\(29);
  AXI4_Lite_RDATA(28) <= \^axi4_lite_rdata\(29);
  AXI4_Lite_RDATA(27) <= \<const0>\;
  AXI4_Lite_RDATA(26) <= \^axi4_lite_rdata\(29);
  AXI4_Lite_RDATA(25) <= \^axi4_lite_rdata\(29);
  AXI4_Lite_RDATA(24) <= \^axi4_lite_rdata\(29);
  AXI4_Lite_RDATA(23) <= \<const0>\;
  AXI4_Lite_RDATA(22) <= \^axi4_lite_rdata\(29);
  AXI4_Lite_RDATA(21) <= \^axi4_lite_rdata\(29);
  AXI4_Lite_RDATA(20) <= \^axi4_lite_rdata\(29);
  AXI4_Lite_RDATA(19) <= \<const0>\;
  AXI4_Lite_RDATA(18) <= \<const0>\;
  AXI4_Lite_RDATA(17) <= \^axi4_lite_rdata\(29);
  AXI4_Lite_RDATA(16) <= \^axi4_lite_rdata\(29);
  AXI4_Lite_RDATA(15) <= \^axi4_lite_rdata\(29);
  AXI4_Lite_RDATA(14) <= \<const0>\;
  AXI4_Lite_RDATA(13) <= \<const0>\;
  AXI4_Lite_RDATA(12) <= \<const0>\;
  AXI4_Lite_RDATA(11) <= \^axi4_lite_rdata\(29);
  AXI4_Lite_RDATA(10) <= \^axi4_lite_rdata\(29);
  AXI4_Lite_RDATA(9) <= \^axi4_lite_rdata\(29);
  AXI4_Lite_RDATA(8) <= \<const0>\;
  AXI4_Lite_RDATA(7) <= \<const0>\;
  AXI4_Lite_RDATA(6) <= \<const0>\;
  AXI4_Lite_RDATA(5) <= \^axi4_lite_rdata\(29);
  AXI4_Lite_RDATA(4) <= \<const0>\;
  AXI4_Lite_RDATA(3) <= \<const0>\;
  AXI4_Lite_RDATA(2) <= \^axi4_lite_rdata\(29);
  AXI4_Lite_RDATA(1) <= \^axi4_lite_rdata\(29);
  AXI4_Lite_RDATA(0) <= \^axi4_lite_rdata\(29);
  AXI4_Lite_RRESP(1) <= \<const0>\;
  AXI4_Lite_RRESP(0) <= \<const0>\;
GND: unisim.vcomponents.GND
     port map (
      G => \<const0>\
    );
U0: entity work.zusys_PWM_SS_3L_ip_0_0_PWM_SS_3L_ip
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
      AXI4_Lite_RDATA(0) => \^axi4_lite_rdata\(29),
      AXI4_Lite_RREADY => AXI4_Lite_RREADY,
      AXI4_Lite_RVALID => AXI4_Lite_RVALID,
      AXI4_Lite_WDATA(19 downto 0) => AXI4_Lite_WDATA(19 downto 0),
      AXI4_Lite_WREADY => AXI4_Lite_WREADY,
      AXI4_Lite_WSTRB(3 downto 0) => AXI4_Lite_WSTRB(3 downto 0),
      AXI4_Lite_WVALID => AXI4_Lite_WVALID,
      IPCORE_CLK => IPCORE_CLK,
      IPCORE_RESETN => IPCORE_RESETN,
      Period_Center => Period_Center,
      Period_Start => Period_Start,
      SSa1_IN_External => SSa1_IN_External,
      SSa1_OUT => SSa1_OUT,
      SSa2_IN_External => SSa2_IN_External,
      SSa2_OUT => SSa2_OUT,
      SSb1_IN_External => SSb1_IN_External,
      SSb1_OUT => SSb1_OUT,
      SSb2_IN_External => SSb2_IN_External,
      SSb2_OUT => SSb2_OUT,
      SSc1_IN_External => SSc1_IN_External,
      SSc1_OUT => SSc1_OUT,
      SSc2_IN_External => SSc2_IN_External,
      SSc2_OUT => SSc2_OUT,
      m_u1_norm(13 downto 0) => m_u1_norm(13 downto 0),
      m_u2_norm(13 downto 0) => m_u2_norm(13 downto 0),
      m_u3_norm(13 downto 0) => m_u3_norm(13 downto 0)
    );
end STRUCTURE;
